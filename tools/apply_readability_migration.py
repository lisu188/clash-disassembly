#!/usr/bin/env python3
"""Apply one exact, hash-pinned readability migration to canonical split source."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

from split_source_index import TOKEN_RE, body_sha256, scan_definitions


ROOT = Path(__file__).resolve().parents[1]
MARK_END = "/* CLASH95_GENERATED_INCLUDES_END */"
VIEW_INCLUDE_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*_view\.h$")


def body_text_sha256(body: str) -> str:
    tokens = TOKEN_RE.findall(body)
    return hashlib.sha256("\n".join(tokens).encode("utf-8")).hexdigest()


def load_spec(root: Path, spec_path: Path) -> dict:
    if not spec_path.is_absolute():
        spec_path = root / spec_path
    payload = json.loads(spec_path.read_text(encoding="utf-8"))
    if payload.get("schema_version") != 1:
        raise ValueError("migration spec must use schema_version 1")
    source = payload.get("source")
    if not isinstance(source, str) or not source.startswith("src/") or not source.endswith(".cpp"):
        raise ValueError("migration source must be a canonical src/*.cpp path")
    functions = payload.get("functions")
    if not isinstance(functions, list) or not functions:
        raise ValueError("migration functions must be a non-empty array")
    names = [record.get("name") for record in functions]
    if not all(isinstance(name, str) and name for name in names):
        raise ValueError("every migration function needs a name")
    if len(names) != len(set(names)):
        raise ValueError("migration function names must be unique")
    includes = payload.get("includes", [])
    if not isinstance(includes, list) or not all(
        isinstance(include, str) and VIEW_INCLUDE_RE.fullmatch(include)
        for include in includes
    ):
        raise ValueError("migration includes must be local *_view.h basenames")
    return payload


def apply_migration(root: Path, spec_path: Path, write: bool) -> tuple[list[str], list[str]]:
    payload = load_spec(root, spec_path)
    source_path = (root / payload["source"]).resolve()
    source_root = (root / "src").resolve()
    if not source_path.is_relative_to(source_root):
        raise ValueError("migration source escapes src/")

    original = source_path.read_text(encoding="utf-8")
    text = original
    records = {record["name"]: record for record in payload["functions"]}
    definitions = scan_definitions(text, set(records))
    by_name: dict[str, list] = {name: [] for name in records}
    for definition in definitions:
        by_name[definition.name].append(definition)

    replacements: list[tuple[int, int, str, str]] = []
    changed_functions: list[str] = []
    for name, record in records.items():
        matches = by_name[name]
        if len(matches) != 1:
            raise ValueError(f"{name}: expected one canonical definition, found {len(matches)}")
        expected = record.get("expected_body_sha256")
        replacement_body = record.get("replacement_body")
        if not isinstance(expected, str) or not re.fullmatch(r"[0-9a-f]{64}", expected):
            raise ValueError(f"{name}: expected_body_sha256 must be a lowercase sha256")
        if not isinstance(replacement_body, str):
            raise ValueError(f"{name}: replacement_body must be a string")
        stripped = replacement_body.strip()
        if not (stripped.startswith("{") and stripped.endswith("}")):
            raise ValueError(f"{name}: replacement_body must contain the complete braced body")

        definition = matches[0]
        current = body_sha256(text, definition)
        replacement_digest = body_text_sha256(replacement_body)
        if current == replacement_digest:
            continue
        if current != expected:
            raise ValueError(
                f"{name}: current body hash {current} matches neither expected "
                f"{expected} nor replacement {replacement_digest}"
            )
        replacements.append(
            (definition.opening_brace, definition.end, replacement_body, name)
        )
        changed_functions.append(name)

    for start, end, replacement_body, _ in sorted(replacements, reverse=True):
        text = text[:start] + replacement_body + text[end:]

    added_includes: list[str] = []
    for include in payload.get("includes", []):
        directive = f'#include "{include}"'
        if directive in text:
            continue
        marker = text.find(MARK_END)
        if marker < 0:
            raise ValueError("canonical source is missing the generated include marker")
        insert_at = marker + len(MARK_END)
        text = text[:insert_at] + "\n" + directive + text[insert_at:]
        added_includes.append(include)

    final_definitions = scan_definitions(text, set(records))
    final_by_name = {definition.name: definition for definition in final_definitions}
    for name, record in records.items():
        replacement_digest = body_text_sha256(record["replacement_body"])
        definition = final_by_name.get(name)
        if definition is None or body_sha256(text, definition) != replacement_digest:
            raise ValueError(f"{name}: replacement verification failed")

    if write and text != original:
        source_path.write_text(text, encoding="utf-8", newline="\n")

    return changed_functions, added_includes


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("spec", type=Path)
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args()

    try:
        changed, includes = apply_migration(args.root.resolve(), args.spec, args.write)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"readability migration: FAIL: {exc}")
        return 1

    mode = "APPLIED" if args.write else "PLAN"
    print(
        f"readability migration: {mode}; "
        f"functions={','.join(changed) if changed else 'already-applied'}; "
        f"includes={','.join(includes) if includes else 'unchanged'}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
