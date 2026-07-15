#!/usr/bin/env python3
"""Audit the canonical GNU C17 recovered-source split without an oracle TU."""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from split_source_index import Definition, body_sha256, scan_definitions


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = ROOT / "data" / "recovered_sources.json"
SPLIT_ROOT = ROOT / "src" / "recovered" / "split"
MARKER_RE = re.compile(r"(?m)^//----- \(([0-9A-Fa-f]{8})\) [-]+\r?$")
ORIGIN_RE = re.compile(
    r"Generated from ([^;\r\n]+); original address order retained\."
)
C_INCLUDE_RE = re.compile(
    r'^\s*#\s*include\s*[<"]([^>"\r\n]+\.c)[>"]', re.MULTILINE
)
SHA256_RE = re.compile(r"^[0-9a-f]{64}$")
IDENTIFIER_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
C_KEYWORDS = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "inline", "int", "long", "register", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while", "_Alignas",
    "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
    "_Noreturn", "_Static_assert", "_Thread_local",
}
VALID_LINKAGE = {"internal", "external", "static", "test-visible-static"}


@dataclass(frozen=True)
class Marker:
    address: str
    start_line: int
    end_line: int


class Audit:
    def __init__(self) -> None:
        self.errors: list[str] = []
        self.checks: Counter[str] = Counter()

    def require(self, condition: bool, message: str) -> bool:
        if not condition:
            self.errors.append(message)
            return False
        return True

    def check(self, category: str, count: int = 1) -> None:
        self.checks[category] += count


def rel(path: Path) -> str:
    return path.resolve().relative_to(ROOT.resolve()).as_posix()


def repo_path(value: Any, field: str, audit: Audit) -> Path | None:
    if not isinstance(value, str) or not value:
        audit.errors.append(f"{field} must be a repository-relative path")
        return None
    candidate = (ROOT / value).resolve()
    try:
        candidate.relative_to(ROOT.resolve())
    except ValueError:
        audit.errors.append(f"{field} escapes the repository: {value!r}")
        return None
    return candidate


def load_manifest(path: Path, audit: Audit) -> dict[str, Any] | None:
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, json.JSONDecodeError) as exc:
        audit.errors.append(f"cannot load manifest {path}: {exc}")
        return None
    if not isinstance(payload, dict):
        audit.errors.append("source manifest root must be an object")
        return None
    return payload


def markers(text: str) -> list[Marker]:
    matches = list(MARKER_RE.finditer(text))
    return [
        Marker(
            address=match.group(1).upper(),
            start_line=text.count("\n", 0, match.start()) + 1,
            end_line=(
                text.count("\n", 0, matches[index + 1].start()) + 1
                if index + 1 < len(matches)
                else len(text.splitlines()) + 1
            ),
        )
        for index, match in enumerate(matches)
    ]


def containing_marker(items: list[Marker], line: int) -> Marker | None:
    matches = [item for item in items if item.start_line <= line < item.end_line]
    return matches[0] if len(matches) == 1 else None


def has_dependency_exception(text: str) -> bool:
    directives = re.findall(
        r"(?m)^\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b", text
    )
    if any(item in {"if", "ifdef", "ifndef"} for item in directives):
        return True
    local_names = re.findall(
        r"(?m)^CLASH95_(?:LOCAL|TEST_VISIBLE)\b[^;{}]*\b([A-Za-z_]\w*)\s*\(",
        text,
    )
    return any(
        len(re.findall(rf"\b{re.escape(name)}\b", text)) > 1
        for name in local_names
    )


def audit_production_layout(audit: Audit) -> None:
    candidates = list(ROOT.glob("*.c")) + list(ROOT.glob("*.h"))
    candidates += list((ROOT / "src").rglob("*.c"))
    candidates += list((ROOT / "src").rglob("*.h"))
    for path in sorted(set(candidates)):
        try:
            text = path.read_text(encoding="utf-8")
        except (OSError, UnicodeError) as exc:
            audit.errors.append(f"cannot read production source {rel(path)}: {exc}")
            continue
        for match in C_INCLUDE_RE.finditer(text):
            line = text.count("\n", 0, match.start()) + 1
            audit.errors.append(
                f"production C inclusion: {rel(path)}:{line}: {match.group(1)}"
            )
    audit.require(not (ROOT / "clash95.c").exists(), "unified clash95.c still exists")
    legacy_fragments = sorted((ROOT / "src").rglob("*.inc.c"))
    audit.require(
        not legacy_fragments,
        "legacy recovered fragments still exist: "
        + ", ".join(rel(path) for path in legacy_fragments[:10]),
    )
    audit.check("production include policy", len(candidates))


def validate_range(record: dict[str, Any], name: str, audit: Audit) -> None:
    address = record.get("original_address")
    value = record.get("original_address_range")
    if not isinstance(value, dict):
        audit.errors.append(f"{name}: original_address_range must be an object")
        return
    start = value.get("start")
    end = value.get("end_exclusive")
    if address is None:
        audit.require(start is None and end is None, f"{name}: unaddressed range is not null")
        return
    audit.require(start == address, f"{name}: range start differs from original_address")
    if end is None:
        audit.check("open-ended address ranges")
        return
    try:
        audit.require(int(end, 16) > int(start, 16), f"{name}: invalid address range")
    except (TypeError, ValueError):
        audit.errors.append(f"{name}: address range is not hexadecimal")


def run(manifest_path: Path, max_lines: int, max_exception_lines: int) -> Audit:
    audit = Audit()
    manifest = load_manifest(manifest_path, audit)
    if manifest is None:
        return audit
    audit.require(manifest.get("schema_version") == 2, "manifest must use schema 2")
    audit.require(manifest.get("cutover") == "canonical-split", "manifest is not split-only")
    audit.require(manifest.get("language") == "GNU C17", "manifest language must be GNU C17")
    audit.require("oracle_manifest" not in manifest, "live oracle_manifest field remains")

    records = manifest.get("functions")
    if not isinstance(records, list):
        audit.errors.append("manifest functions must be an array")
        return audit
    audit.require(
        manifest.get("function_count") == len(records),
        f"function_count differs: {manifest.get('function_count')} != {len(records)}",
    )
    state_owner = repo_path(manifest.get("state_owner"), "state_owner", audit)

    generated = sorted(SPLIT_ROOT.rglob("*.c")) if SPLIT_ROOT.is_dir() else []
    audit.require(bool(generated), "canonical split contains no C sources")
    audit.require(
        manifest.get("source_file_count") == len(generated),
        f"source_file_count differs: {manifest.get('source_file_count')} != {len(generated)}",
    )
    if state_owner is not None:
        audit.require(state_owner in generated, "state_owner is not a canonical split source")

    names: set[str] = set()
    records_by_source: dict[str, list[dict[str, Any]]] = defaultdict(list)
    identities: set[tuple[str, int, str]] = set()
    for index, value in enumerate(records):
        if not isinstance(value, dict):
            audit.errors.append(f"functions[{index}] must be an object")
            continue
        name = value.get("name")
        source = value.get("source")
        origin = value.get("original_source")
        legacy = value.get("legacy_path")
        line = value.get("original_line")
        if not isinstance(name, str) or not IDENTIFIER_RE.fullmatch(name) or name in C_KEYWORDS:
            audit.errors.append(f"functions[{index}].name is invalid: {name!r}")
            continue
        audit.require(name not in names, f"duplicate function name: {name}")
        names.add(name)
        if not isinstance(source, str):
            audit.errors.append(f"{name}: source must be a path")
            continue
        records_by_source[source].append(value)
        audit.require(isinstance(origin, str) and bool(origin), f"{name}: missing historical origin")
        audit.require(legacy == origin, f"{name}: legacy_path differs from original_source")
        audit.require(isinstance(line, int) and line > 0, f"{name}: invalid original_line")
        identity = (str(origin), int(line or 0), name)
        audit.require(identity not in identities, f"duplicate historical identity: {identity}")
        identities.add(identity)
        audit.require(value.get("linkage") in VALID_LINKAGE, f"{name}: invalid linkage")
        for field in ("body_sha256", "legacy_body_sha256"):
            digest = value.get(field)
            audit.require(
                isinstance(digest, str) and bool(SHA256_RE.fullmatch(digest)),
                f"{name}: invalid {field}",
            )
        validate_range(value, name, audit)
        audit.require(value.get("state_owner") == manifest.get("state_owner"), f"{name}: state owner differs")

    indexed: dict[str, list[tuple[str, Definition, str]]] = defaultdict(list)
    total_markers = 0
    for path in generated:
        source = rel(path)
        text = path.read_text(encoding="utf-8")
        file_markers = markers(text)
        total_markers += len(file_markers)
        line_count = len(text.splitlines())
        if state_owner is None or path.resolve() != state_owner.resolve():
            audit.require(
                line_count <= max_lines
                or (line_count <= max_exception_lines and has_dependency_exception(text)),
                f"{source}: {line_count} lines exceeds permitted dependency limit",
            )
        origin_match = ORIGIN_RE.search(text[:512])
        if file_markers:
            audit.require(origin_match is not None, f"{source}: marker TU lacks historical origin")
            filename = path.name
            audit.require(file_markers[0].address in filename, f"{source}: first address absent from filename")
            audit.require(file_markers[-1].address in filename, f"{source}: last address absent from filename")
        definitions = scan_definitions(text, names)
        for definition in definitions:
            indexed[definition.name].append(
                (source, definition, body_sha256(text, definition))
            )
        assigned = records_by_source.get(source, [])
        audit.require(
            len(definitions) == len(assigned),
            f"{source}: indexed {len(definitions)} definitions, manifest assigns {len(assigned)}",
        )
        audit.require(
            [definition.name for definition in definitions]
            == [record.get("name") for record in assigned],
            f"{source}: definition order differs from the manifest",
        )
        by_name = {record["name"]: record for record in assigned}
        for definition in definitions:
            record = by_name.get(definition.name)
            if record is None:
                continue
            marker = containing_marker(file_markers, definition.line)
            expected_address = f"0x{marker.address}" if marker else None
            audit.require(
                record.get("original_address") == expected_address,
                f"{definition.name}: marker address differs from manifest",
            )
            if marker and origin_match:
                audit.require(
                    record.get("original_source") == origin_match.group(1).replace("\\", "/"),
                    f"{definition.name}: generated origin differs from manifest",
                )
        audit.check("canonical translation units")

    audit.require(
        manifest.get("address_marker_count") == total_markers,
        f"address_marker_count differs: {manifest.get('address_marker_count')} != {total_markers}",
    )
    audit.check("ordered address markers", total_markers)
    for record in records:
        if not isinstance(record, dict) or not isinstance(record.get("name"), str):
            continue
        name = record["name"]
        matches = indexed.get(name, [])
        if not audit.require(len(matches) == 1, f"{name}: found {len(matches)} canonical definitions"):
            continue
        source, _, digest = matches[0]
        audit.require(source == record.get("source"), f"{name}: source differs from manifest")
        audit.require(digest == record.get("body_sha256"), f"{name}: canonical body hash differs")
        audit.check("manifest functions")

    audit.require(len(indexed) == len(records), "not every manifest function was indexed once")
    audit_production_layout(audit)
    return audit


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument("--max-lines", type=int, default=1500)
    parser.add_argument("--max-exception-lines", type=int, default=2000)
    args = parser.parse_args()
    if args.max_lines < 1:
        parser.error("--max-lines must be positive")
    if args.max_exception_lines < args.max_lines:
        parser.error("--max-exception-lines must be >= --max-lines")
    manifest = args.manifest if args.manifest.is_absolute() else ROOT / args.manifest
    audit = run(manifest.resolve(), args.max_lines, args.max_exception_lines)
    if audit.errors:
        print(f"split source audit: FAIL ({len(audit.errors)} errors)")
        for error in audit.errors:
            print(f"  - {error}")
        return 1
    summary = ", ".join(
        f"{name}={count}" for name, count in sorted(audit.checks.items())
    )
    print(f"split source audit: PASS ({summary})")
    return 0


if __name__ == "__main__":
    sys.exit(main())
