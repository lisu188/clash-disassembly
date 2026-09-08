#!/usr/bin/env python3
"""Apply one exact, hash-pinned readability migration to canonical split source."""

from __future__ import annotations

import argparse
import hashlib
import json
import posixpath
import re
from pathlib import Path

from split_source_index import TOKEN_RE, body_sha256, scan_definitions
from recovered_implementation import manifest_targets


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


def source_path_within_root(root: Path, source: str) -> Path:
    path = (root / source).resolve()
    if not path.is_relative_to((root / "src").resolve()):
        raise ValueError("migration source escapes src/")
    return path


def canonical_targets(root: Path, payload: dict) -> dict[str, tuple[str, str]]:
    """Resolve historical spec names, never a method's compatibility adapter."""
    manifest_path = root / "data/recovered_sources.json"
    if not manifest_path.exists():
        # Preserve small schema-1 fixture / standalone free-function use.
        return {record["name"]: (payload["source"], record["name"])
                for record in payload["functions"]}
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    targets = manifest_targets(manifest)
    by_identity = {target.identity: target for target in targets
                   if target.role == "canonical"}
    records = manifest["functions"]
    lookup = {}
    for record in records:
        aliases = record.get("historical_names", [])
        if (not isinstance(aliases, list) or
                not all(isinstance(name, str) and
                        re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name) for name in aliases) or
                len(set(aliases)) != len(aliases)):
            raise ValueError(f"{record['name']}: invalid historical_names")
        for name in [record["name"], *aliases]:
            lookup.setdefault(name, []).append(record)
    result = {}
    for spec in payload["functions"]:
        name = spec["name"]
        matches = lookup.get(name, [])
        if not matches:
            raise ValueError(f"{name}: historical identity is absent from manifest")
        if len(matches) != 1:
            raise ValueError(f"{name}: ambiguous historical identity in manifest")
        record = matches[0]
        target = by_identity[record["name"]]
        allowed_sources = {target.source}
        if record.get("adapter") is not None:
            allowed_sources.add(record["adapter"]["source"])
        compatibility_aliases = record.get("compatibility_aliases", [])
        if not isinstance(compatibility_aliases, list) or not all(
                isinstance(alias, dict) for alias in compatibility_aliases):
            raise ValueError(f"{record['name']}: invalid compatibility_aliases")
        alias_matches = [alias for alias in compatibility_aliases if alias.get("name") == name]
        if len(alias_matches) > 1:
            raise ValueError(f"{name}: ambiguous compatibility alias in manifest")
        if alias_matches:
            alias_source = alias_matches[0].get("source")
            if not isinstance(alias_source, str):
                raise ValueError(f"{name}: invalid compatibility alias source")
            source_path_within_root(root, alias_source)
            allowed_sources.add(alias_source)
        if payload["source"] not in allowed_sources:
            raise ValueError(f"{name}: spec source is neither canonical nor adapter source "
                             "nor a matching historical alias source")
        source_path_within_root(root, target.source)
        result[name] = (target.source, target.name)
    return result


def apply_migration(root: Path, spec_path: Path, write: bool) -> tuple[list[str], list[str]]:
    root = root.resolve()
    payload = load_spec(root, spec_path)
    source_path_within_root(root, payload["source"])
    targets = canonical_targets(root, payload)
    originals = {source: source_path_within_root(root, source).read_text(encoding="utf-8")
                 for source, _ in targets.values()}
    texts = dict(originals)
    records = {record["name"]: record for record in payload["functions"]}
    by_name = {}
    for source, text in texts.items():
        names = {qualified for path, qualified in targets.values() if path == source}
        for definition in scan_definitions(text, names):
            by_name.setdefault((source, definition.name), []).append(definition)

    replacements = {}
    changed_functions: list[str] = []
    for name, record in records.items():
        source, qualified = targets[name]
        matches = by_name.get((source, qualified), [])
        if len(matches) != 1:
            raise ValueError(f"{name}: expected one canonical definition of {qualified}, "
                             f"found {len(matches)}")
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
        current = body_sha256(texts[source], definition)
        replacement_digest = body_text_sha256(replacement_body)
        if current == replacement_digest:
            continue
        if current != expected:
            raise ValueError(
                f"{name}: current body hash {current} matches neither expected "
                f"{expected} nor replacement {replacement_digest}"
            )
        replacements.setdefault(source, []).append(
            (definition.opening_brace, definition.end, replacement_body))
        changed_functions.append(name)

    for source, edits in replacements.items():
        text = texts[source]
        for start, end, body in sorted(edits, reverse=True):
            text = text[:start] + body + text[end:]
        texts[source] = text

    added_includes: list[str] = []
    for source in texts:
        text = texts[source]
        for include in payload.get("includes", []):
            # Spec includes belong to the historical source's directory. Keep
            # that target when a class was relocated to another subsystem.
            include_source = posixpath.join(posixpath.dirname(payload["source"]), include)
            source_path_within_root(root, include_source)
            relative_include = posixpath.relpath(include_source, posixpath.dirname(source))
            directive = f'#include "{relative_include}"'
            if directive in text:
                continue
            marker = text.find(MARK_END)
            if marker < 0:
                raise ValueError("canonical source is missing the generated include marker")
            insert_at = marker + len(MARK_END)
            text = text[:insert_at] + "\n" + directive + text[insert_at:]
            if relative_include not in added_includes:
                added_includes.append(relative_include)
        texts[source] = text

    # Validate every staged source before performing any writes. One bad body
    # in a multi-class spec must not partially apply the other replacements.
    for name, record in records.items():
        source, qualified = targets[name]
        final_definitions = scan_definitions(texts[source], {qualified})
        replacement_digest = body_text_sha256(record["replacement_body"])
        if (len(final_definitions) != 1 or
                body_sha256(texts[source], final_definitions[0]) != replacement_digest):
            raise ValueError(f"{name}: replacement verification failed")

    if write:
        for source, text in texts.items():
            if text != originals[source]:
                source_path_within_root(root, source).write_text(
                    text, encoding="utf-8", newline="\n")

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
