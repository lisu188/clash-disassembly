#!/usr/bin/env python3
"""Pin recovered translation-unit order and append new class sources explicitly.

The CMake inventory is the order authority when schema 3 is first initialized.
After that, source_inventory pins both group order and the existing prefix of
each group. Neither synchronization nor validation sorts translation units.
"""
from __future__ import annotations

import argparse
import copy
from dataclasses import dataclass
import json
from pathlib import Path, PurePosixPath
import re

from recovered_implementation import ImplementationError, manifest_sources


ROOT = Path(__file__).resolve().parents[1]
SUBSYSTEMS = frozenset({
    "battle", "buildings", "clips", "core", "media", "persistence",
    "render", "runtime", "state", "strategic", "units", "world",
})
GROUP_START = re.compile(r"[ \t]*set\([ \t]*CLASH95_SPLIT_([A-Z_]+)_SOURCES[ \t]*(?:#.*)?\Z")
GROUP_END = re.compile(r"[ \t]*\)[ \t]*(?:#.*)?\Z")
SOURCE_LINE = re.compile(
    r"(?P<indent>[ \t]*)(?P<prefix>\$\{CMAKE_CURRENT_SOURCE_DIR\}/)?"
    r"(?P<source>src/[^\s#()]+)[ \t]*(?:#.*)?\Z"
)


class SourceInventoryError(ValueError):
    """The explicit source order or its closed membership is invalid."""


@dataclass(frozen=True)
class _Group:
    name: str
    sources: tuple[str, ...]
    closing_offset: int
    indent: str
    prefix: str
    newline: str


def _source_group(source: object) -> str:
    if not isinstance(source, str) or "\\" in source or ":" in source:
        raise SourceInventoryError(f"invalid inventory source: {source!r}")
    path = PurePosixPath(source)
    if (path.is_absolute() or len(path.parts) < 3 or path.parts[0] != "src"
            or path.parts[1] not in SUBSYSTEMS or ".." in path.parts
            or str(path) != source or re.search(r"[\s#();$]", source)
            or path.suffix not in {".c", ".cpp", ".cc", ".cxx"}):
        raise SourceInventoryError(f"invalid inventory source: {source!r}")
    return path.parts[1]


def _validate_groups(inventory: object) -> list[dict]:
    if not isinstance(inventory, list) or not inventory:
        raise SourceInventoryError("source_inventory must be a nonempty ordered array")
    groups, sources, result = set(), set(), []
    for entry in inventory:
        if not isinstance(entry, dict) or set(entry) != {"group", "sources"}:
            raise SourceInventoryError("inventory entries require exactly group and sources")
        group = entry["group"]
        if not isinstance(group, str) or group not in SUBSYSTEMS:
            raise SourceInventoryError(f"foreign source group: {group!r}")
        if group in groups:
            raise SourceInventoryError(f"duplicate source group: {group}")
        groups.add(group)
        paths = entry["sources"]
        if not isinstance(paths, list) or not paths:
            raise SourceInventoryError(f"{group}: sources must be a nonempty ordered array")
        for source in paths:
            owner = _source_group(source)
            if source in sources:
                raise SourceInventoryError(f"duplicate inventory source: {source}")
            if owner != group:
                raise SourceInventoryError(f"{source}: belongs to {owner}, not {group}")
            sources.add(source)
        result.append({"group": group, "sources": list(paths)})
    return result


def _parse_cmake(text: str) -> tuple[_Group, ...]:
    groups = []
    current = None
    paths = []
    offset = 0
    indent, prefix, newline = "  ", "${CMAKE_CURRENT_SOURCE_DIR}/", "\n"
    for number, raw in enumerate(text.splitlines(keepends=True), 1):
        line = raw.rstrip("\r\n")
        ending = raw[len(line):]
        if not line.strip() or line.lstrip().startswith("#"):
            offset += len(raw)
            continue
        if current is None:
            match = GROUP_START.fullmatch(line)
            if match is None:
                raise SourceInventoryError(f"sources.cmake:{number}: unsupported inventory statement")
            current = match.group(1).lower()
            paths = []
            indent, prefix = "  ", "${CMAKE_CURRENT_SOURCE_DIR}/"
            newline = ending or "\n"
        elif GROUP_END.fullmatch(line):
            groups.append(_Group(current, tuple(paths), offset, indent, prefix, newline))
            current = None
        else:
            match = SOURCE_LINE.fullmatch(line)
            if match is None:
                raise SourceInventoryError(f"sources.cmake:{number}: invalid source entry")
            paths.append(match.group("source"))
            indent = match.group("indent")
            prefix = match.group("prefix") or ""
            newline = ending or newline
        offset += len(raw)
    if current is not None:
        raise SourceInventoryError(f"sources.cmake: unclosed source group {current}")
    _validate_groups([{"group": group.name, "sources": list(group.sources)} for group in groups])
    return tuple(groups)


def parse_cmake_inventory(text: str) -> list[dict]:
    """Read the supported explicit CMake set blocks in their original order."""
    return [{"group": group.name, "sources": list(group.sources)} for group in _parse_cmake(text)]


def _paths(inventory: list[dict]) -> list[str]:
    return [source for group in inventory for source in group["sources"]]


def _canonical_additions(manifest: dict) -> list[str]:
    # Manifest record encounter order is deterministic and does not replace any
    # previously recorded CMake order. ABI adapters and state cannot be appended
    # as if they were newly introduced class translation units.
    boundary_sources = {manifest.get("state_owner")}
    methods = []
    for record in manifest["functions"]:
        if record.get("adapter"):
            boundary_sources.add(record["adapter"]["source"])
        if record.get("implementation", {}).get("kind") == "method":
            if record["source"] not in methods:
                methods.append(record["source"])
        else:
            boundary_sources.add(record["source"])
    return [source for source in methods if source not in boundary_sources]


def resolve_source_inventory(
    manifest: dict, cmake_text: str, *, append_canonical: bool = False
) -> list[dict]:
    """Validate schema 3 order and membership, returning independent entries.

    Strict resolution requires an explicit inventory matching CMake exactly.
    append_canonical permits initial capture from CMake and appending only new
    method-only translation units to an already existing subsystem group.
    Existing explicit entries must still appear as the exact CMake prefix.
    """
    if manifest.get("schema_version") != 3:
        raise SourceInventoryError("explicit source inventory requires manifest schema 3")
    try:
        expected = set(manifest_sources(manifest))
    except (ImplementationError, KeyError, TypeError) as exc:
        raise SourceInventoryError(f"invalid manifest source membership: {exc}") from exc
    for source in expected:
        _source_group(source)
    inventory = parse_cmake_inventory(cmake_text)
    actual = set(_paths(inventory))
    foreign = actual - expected
    if foreign:
        raise SourceInventoryError(f"foreign CMake sources: {', '.join(sorted(foreign))}")
    additions = _canonical_additions(manifest)
    permitted = set(additions) if append_canonical else set()
    pinned = manifest.get("source_inventory")
    if pinned is None:
        if not append_canonical:
            raise SourceInventoryError("schema 3 source_inventory is missing")
    else:
        pinned = _validate_groups(pinned)
        pinned_sources = set(_paths(pinned))
        if pinned_sources - expected:
            raise SourceInventoryError("explicit source_inventory contains foreign sources")
        if [group["group"] for group in pinned] != [group["group"] for group in inventory]:
            raise SourceInventoryError("CMake group order differs from pinned source_inventory")
        for previous, current in zip(pinned, inventory):
            count = len(previous["sources"])
            if current["sources"][:count] != previous["sources"]:
                raise SourceInventoryError(
                    f"{current['group']}: CMake lost or reordered pinned inventory sources")
            unexpected = set(current["sources"][count:]) - permitted
            if unexpected:
                raise SourceInventoryError("CMake entries differ from pinned source_inventory")
    missing = expected - actual
    if missing - permitted:
        raise SourceInventoryError(f"missing source inventory entries: {', '.join(sorted(missing - permitted))}")
    by_group = {group["group"]: group["sources"] for group in inventory}
    for source in additions:
        if source not in missing:
            continue
        group = _source_group(source)
        if group not in by_group:
            raise SourceInventoryError(f"{source}: missing existing subsystem group {group}")
        by_group[group].append(source)
    if set(_paths(inventory)) != expected:
        raise SourceInventoryError("source inventory differs from the closed manifest source set")
    return inventory


def _append_cmake_sources(text: str, inventory: list[dict]) -> str:
    groups = _parse_cmake(text)
    edits = []
    for previous, current in zip(groups, inventory):
        added = current["sources"][len(previous.sources):]
        if added:
            insertion = "".join(
                previous.indent + previous.prefix + source + previous.newline for source in added)
            edits.append((previous.closing_offset, insertion))
    for offset, insertion in reversed(edits):
        text = text[:offset] + insertion + text[offset:]
    return text


def synchronize_source_inventory(manifest: dict, cmake_text: str) -> tuple[dict, str]:
    """Return an updated manifest and CMake text without mutating either input."""
    inventory = resolve_source_inventory(manifest, cmake_text, append_canonical=True)
    result = copy.deepcopy(manifest)
    result["source_inventory"] = inventory
    result["source_file_count"] = len(_paths(inventory))
    updated_cmake = _append_cmake_sources(cmake_text, inventory)
    resolve_source_inventory(result, updated_cmake)
    return result, updated_cmake


def _read_text(path: Path) -> str:
    with path.open(encoding="utf-8", newline="") as stream:
        return stream.read()


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--manifest", type=Path, default=Path("data/recovered_sources.json"))
    parser.add_argument("--sources", type=Path, default=Path("src/sources.cmake"))
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args(argv)
    manifest_path = args.root / args.manifest
    sources_path = args.root / args.sources
    try:
        original_manifest = _read_text(manifest_path)
        manifest = json.loads(original_manifest)
        cmake_text = _read_text(sources_path)
        result, updated_cmake = synchronize_source_inventory(manifest, cmake_text)
        changed = manifest != result or cmake_text != updated_cmake
        if changed and not args.write:
            print("source inventory is stale; rerun with --write")
            return 1
        if args.write:
            if manifest != result:
                newline = "\r\n" if "\r\n" in original_manifest else "\n"
                content = (json.dumps(result, indent=2) + "\n").replace("\n", newline)
                with manifest_path.open("w", encoding="utf-8", newline="") as stream:
                    stream.write(content)
            if cmake_text != updated_cmake:
                with sources_path.open("w", encoding="utf-8", newline="") as stream:
                    stream.write(updated_cmake)
    except (OSError, ValueError) as exc:
        print(f"source inventory: {exc}")
        return 1
    print(f"source inventory: {result['source_file_count']} sources in {len(result['source_inventory'])} ordered groups")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
