#!/usr/bin/env python3
"""Freeze/check a C++ class migration without replacing historical ratchets.

Snapshots pin the complete legacy archive identity set, linked text (including
weak definitions), named object storage/relocations, and initializer sections.
The check accepts only individually enumerated new method/accessor text symbols;
it never rewrites a snapshot or accepts data/initializer changes by allowance.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

from check_link_surface import ARTIFACT_RE, parse_nm, run_nm

SCHEMA_VERSION = 1
TEXT_CLASSES = frozenset("tTwW")
DATA_CLASSES = frozenset("bBdDrRgGsScCvV")
INIT_SECTIONS = frozenset((".init_array", ".fini_array", ".preinit_array", ".ctors", ".dtors"))
ROOT = Path(__file__).resolve().parents[1]


class SurfaceError(ValueError):
    """A malformed input or unsupported artifact cannot establish parity."""


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def command(*args: str) -> bytes:
    completed = subprocess.run(args, capture_output=True, check=False)
    if completed.returncode:
        raise SurfaceError(f"{' '.join(args)}: {completed.stderr.decode(errors='replace').strip()}")
    return completed.stdout


def text_counts(rows) -> list[dict]:
    counts = Counter((name, kind) for _, _, kind, name in rows
                     if kind in TEXT_CLASSES and not ARTIFACT_RE.search(name))
    return [{"name": name, "class": kind, "count": count}
            for (name, kind), count in sorted(counts.items())]


def as_counter(rows: list[dict]) -> Counter:
    result = Counter()
    for row in rows:
        key = (row["name"], row["class"])
        count = row["count"]
        if not isinstance(count, int) or isinstance(count, bool) or count < 1:
            raise SurfaceError(f"invalid symbol multiplicity: {row!r}")
        if key in result:
            raise SurfaceError(f"duplicate symbol row: {key!r}")
        result[key] = count
    return result


def manifest_identities(manifest: dict, expected_count: int = 4157) -> list[dict]:
    identities = [{"name": row["name"], "linkage": row["linkage"],
                   "original_address": row["original_address"]}
                  for row in manifest["functions"]]
    if len(identities) != expected_count or len({row["name"] for row in identities}) != expected_count:
        raise SurfaceError(f"expected exactly {expected_count} unique recovered identities")
    if any(row["linkage"] not in ("external", "internal", "static", "test-visible-static") for row in identities):
        raise SurfaceError("unknown legacy linkage")
    return sorted(identities, key=lambda row: row["name"])


def archive_identity_errors(identities: list[dict], rows) -> list[str]:
    definitions = Counter((name, kind) for _, _, kind, name in rows)
    errors = []
    for identity in identities:
        name = identity["name"]
        kind = "T" if identity["linkage"] in ("external", "internal") else "t"
        found = {cls: count for (symbol, cls), count in definitions.items() if symbol == name}
        if found != {kind: 1}:
            errors.append(f"legacy {name}: expected exactly one {kind}, found {found}")
    return errors


class Elf64:
    """Small ELF64 little-endian reader; unsupported formats fail closed."""

    def __init__(self, blob: bytes):
        self.blob = blob
        if blob[:6] != b"\x7fELF\x02\x01":
            raise SurfaceError("expected a little-endian ELF64 artifact")
        header = struct.unpack_from("<HHIQQQIHHHHHH", blob, 16)
        self.elf_type, self.machine = header[:2]
        if self.machine != 62:
            raise SurfaceError("only the supported x86-64 build profile is understood")
        section_offset, section_stride, section_count, names_index = header[5], header[10], header[11], header[12]
        self.sections = []
        for index in range(section_count):
            values = struct.unpack_from("<IIQQQQIIQQ", blob, section_offset + index * section_stride)
            keys = ("name_offset", "type", "flags", "address", "offset", "size", "link", "info", "alignment", "entry_size")
            self.sections.append(dict(zip(keys, values)))
        names = self.section_bytes(names_index)
        for section in self.sections:
            section["name"] = self.string(names, section["name_offset"])
        self.symbols = {}
        for index, section in enumerate(self.sections):
            if section["type"] not in (2, 11):
                continue
            strings = self.section_bytes(section["link"])
            table = []
            for offset in range(section["offset"], section["offset"] + section["size"], section["entry_size"]):
                name, info, other, section_index, value, size = struct.unpack_from("<IBBHQQ", blob, offset)
                table.append({"name": self.string(strings, name), "binding": info >> 4,
                              "type": info & 15, "visibility": other, "section": section_index,
                              "value": value, "size": size})
            self.symbols[index] = table

    @staticmethod
    def string(table: bytes, offset: int) -> str:
        return table[offset:table.find(b"\0", offset)].decode("utf-8", errors="surrogateescape")

    def section_bytes(self, index: int) -> bytes:
        section = self.sections[index]
        if section["type"] == 8:
            return bytes(section["size"])
        return self.blob[section["offset"]:section["offset"] + section["size"]]

    def relocations(self, section_index: int, start: int, size: int) -> list[dict]:
        found = []
        widths = {1: 8, 2: 4, 4: 4, 6: 8, 7: 8, 8: 8, 9: 4, 10: 4, 11: 4,
                  12: 2, 13: 2, 14: 1, 15: 1, 24: 8, 25: 8, 41: 4, 42: 4}
        for section in self.sections:
            if section["type"] not in (4, 9) or section["info"] != section_index:
                continue
            for offset in range(section["offset"], section["offset"] + section["size"], section["entry_size"]):
                address, info = struct.unpack_from("<QQ", self.blob, offset)
                if not start <= address < start + size:
                    continue
                kind = info & 0xffffffff
                if kind not in widths:
                    raise SurfaceError(f"unsupported data relocation type {kind}")
                target = self.symbols[section["link"]][info >> 32]
                target_name = target["name"]
                if not target_name and target["section"] < len(self.sections):
                    target_name = self.sections[target["section"]]["name"]
                addend = struct.unpack_from("<q", self.blob, offset + 16)[0] if section["type"] == 4 else None
                found.append({"offset": address - start, "width": widths[kind], "type": kind,
                              "target": target_name, "addend": addend})
        return sorted(found, key=lambda row: (row["offset"], row["target"]))

    def payload(self, section_index: int, offset: int, size: int) -> dict:
        section = self.sections[section_index]
        relocations = self.relocations(section_index, offset, size)
        data = bytearray(self.section_bytes(section_index)[offset:offset + size])
        for relocation in relocations:
            begin, width = relocation["offset"], relocation["width"]
            if begin + width > size:
                raise SurfaceError("relocation crosses named storage boundary")
            # REL addends live in the bytes and must remain visible in the hash.
            if relocation["addend"] is not None:
                data[begin:begin + width] = bytes(width)
        return {"sha256": sha256(data), "relocations": relocations,
                "section_type": section["type"], "section_flags": section["flags"],
                "alignment": section["alignment"]}

    def named_storage(self) -> list[dict]:
        rows = []
        for table_index, symbols in self.symbols.items():
            if self.sections[table_index]["type"] != 2:
                continue
            for symbol in symbols:
                if symbol["type"] not in (1, 6) or not symbol["name"] or ARTIFACT_RE.search(symbol["name"]):
                    continue
                index = symbol["section"]
                if index == 0:
                    continue
                row = {key: symbol[key] for key in ("name", "binding", "type", "visibility", "size")}
                if index == 0xfff2:
                    row.update({"common_alignment": symbol["value"]})
                elif index >= len(self.sections):
                    raise SurfaceError(f"unsupported named storage section for {symbol['name']}")
                else:
                    section = self.sections[index]
                    relative = symbol["value"] - section["address"]
                    row.update(self.payload(index, relative, symbol["size"]))
                rows.append(row)
        return sorted(rows, key=lambda row: json.dumps(row, sort_keys=True))

    def initializers(self) -> list[dict]:
        rows = []
        exact_symbols = {}
        for symbols in self.symbols.values():
            for symbol in symbols:
                if symbol["name"] and symbol["section"]:
                    exact_symbols.setdefault(symbol["value"], set()).add(symbol["name"])
        for index, section in enumerate(self.sections):
            if not any(section["name"] == name or section["name"].startswith(name + ".") for name in INIT_SECTIONS):
                continue
            row = {"name": section["name"], "size": section["size"], "alignment": section["alignment"]}
            if self.elf_type == 1:
                row.update(self.payload(index, 0, section["size"]))
            else:
                data = self.section_bytes(index)
                if len(data) % 8:
                    raise SurfaceError("unaligned linked initializer section")
                row["entries"] = [sorted(exact_symbols[value]) if value in exact_symbols else {"raw": value}
                                  for (value,) in struct.iter_unpack("<Q", data)]
            rows.append(row)
        return rows


def archive_storage(archive: Path) -> tuple[list[dict], list[dict]]:
    members = command("ar", "t", str(archive)).decode().splitlines()
    if len(members) != len(set(members)):
        raise SurfaceError("duplicate archive member names cannot be inspected unambiguously")
    storage, initializers = [], []
    for member in members:
        elf = Elf64(command("ar", "p", str(archive), member))
        storage.extend(elf.named_storage())
        initializers.extend(elf.initializers())
    # Storage membership is independent of CMake object/class source filenames.
    return (sorted(storage, key=lambda row: json.dumps(row, sort_keys=True)),
            sorted(initializers, key=lambda row: json.dumps(row, sort_keys=True)))


def make_snapshot(binary: Path, archive: Path, manifest_path: Path, compiler: str) -> dict:
    identities = manifest_identities(json.loads(manifest_path.read_text()))
    archive_rows = list(parse_nm(run_nm(archive)))
    errors = archive_identity_errors(identities, archive_rows)
    if errors:
        raise SurfaceError("\n".join(errors))
    binary_rows = list(parse_nm(run_nm(binary)))
    data_rows = sorted(((address, size, kind, name) for address, size, kind, name in binary_rows
                        if kind in DATA_CLASSES and not ARTIFACT_RE.search(name)), key=lambda row: (row[2].lower(), row[0], row[3]))
    storage, initializers = archive_storage(archive)
    return {"schema_version": SCHEMA_VERSION, "compiler": compiler,
            "provenance": {"binary": str(binary.resolve()), "archive": str(archive.resolve()),
                           "binary_sha256": sha256(binary.read_bytes()), "archive_sha256": sha256(archive.read_bytes()),
                           "manifest_sha256": sha256(manifest_path.read_bytes())},
            "legacy_identities": identities, "linked_text": text_counts(binary_rows),
            "archive_text": text_counts(archive_rows),
            "linked_data_ordered": [{"name": name, "class": kind, "size": size}
                                    for _, size, kind, name in data_rows],
            "archive_storage": storage, "archive_initializers": initializers,
            "linked_initializers": Elf64(binary.read_bytes()).initializers()}


def allowed_text(document: dict, field: str) -> Counter:
    rows = document.get(field, [])
    for row in rows:
        if set(row) != {"name", "class", "count", "kind", "reason"}:
            raise SurfaceError("allowances require exact name/class/count/kind/reason fields")
        if row["class"] not in TEXT_CLASSES or row["kind"] not in ("method", "accessor", "adapter"):
            raise SurfaceError(f"invalid text allowance: {row!r}")
        if not isinstance(row["reason"], str) or not row["reason"].strip():
            raise SurfaceError("every added symbol needs a review reason")
        if any(char in row["name"] for char in "*?[]"):
            raise SurfaceError("wildcard allowances are forbidden")
    return as_counter(rows)


def compare_snapshots(base: dict, current: dict, allowances: dict | None = None) -> dict:
    if base.get("schema_version") != SCHEMA_VERSION or current.get("schema_version") != SCHEMA_VERSION:
        raise SurfaceError("unsupported snapshot schema")
    if base["compiler"] != current["compiler"]:
        raise SurfaceError("compiler profiles must match")
    allowances = allowances or {}
    if set(allowances) - {"linked_text", "archive_text"}:
        raise SurfaceError("only exact text additions can be allowed")
    errors, text_delta = [], {}
    for field in ("linked_text", "archive_text"):
        before, after = as_counter(base[field]), as_counter(current[field])
        added, removed = after - before, before - after
        permitted = allowed_text(allowances, field)
        text_delta[field] = {"added": [{"name": name, "class": kind, "count": count} for (name, kind), count in sorted(added.items())],
                             "removed": [{"name": name, "class": kind, "count": count} for (name, kind), count in sorted(removed.items())]}
        for symbol, count in sorted(removed.items()):
            errors.append(f"{field}: removed {symbol!r} x{count}")
        for symbol, count in sorted((added - permitted).items()):
            errors.append(f"{field}: unreviewed addition {symbol!r} x{count}")
        for symbol, count in sorted((permitted - added).items()):
            errors.append(f"{field}: stale/overbroad allowance {symbol!r} x{count}")
    differences = {}
    for field in ("legacy_identities", "linked_data_ordered", "archive_storage", "archive_initializers", "linked_initializers"):
        if base[field] != current[field]:
            before = Counter(json.dumps(row, sort_keys=True) for row in base[field])
            after = Counter(json.dumps(row, sort_keys=True) for row in current[field])
            differences[field] = {"removed": [json.loads(row) for row in (before - after).elements()],
                                  "added": [json.loads(row) for row in (after - before).elements()],
                                  "order_changed": before == after}
            errors.append(f"{field}: changed")
    return {"ok": not errors, "errors": errors, "text_delta": text_delta, "differences": differences}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=("snapshot", "check"))
    parser.add_argument("binary", type=Path)
    parser.add_argument("--lib", type=Path, required=True)
    parser.add_argument("--compiler", choices=("gcc", "clang"), required=True)
    parser.add_argument("--manifest", type=Path, default=ROOT / "data/recovered_sources.json")
    parser.add_argument("--snapshot", type=Path, required=True)
    parser.add_argument("--allowances", type=Path)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    try:
        current = make_snapshot(args.binary, args.lib, args.manifest, args.compiler)
        if args.mode == "snapshot":
            if args.allowances or args.report:
                raise SurfaceError("snapshot mode does not consume allowances or reports")
            # A frozen reference is never overwritten, including by accident.
            with args.snapshot.open("x", encoding="utf-8") as output:
                json.dump(current, output, indent=2)
                output.write("\n")
            print(f"snapshot: {args.snapshot}; {len(current['legacy_identities'])} legacy identities")
            return 0
        baseline = json.loads(args.snapshot.read_text())
        permitted = {}
        if args.allowances:
            document = json.loads(args.allowances.read_text())
            if document.get("schema_version") != SCHEMA_VERSION:
                raise SurfaceError("unsupported allowances schema")
            permitted = document["profiles"][args.compiler]
        report = compare_snapshots(baseline, current, permitted)
        report["current_provenance"] = current["provenance"]
        if args.report:
            args.report.write_text(json.dumps(report, indent=2) + "\n")
        print(f"class migration surface: {'PASS' if report['ok'] else 'FAIL'}")
        for error in report["errors"][:30]:
            print(error)
        if len(report["errors"]) > 30:
            print(f"... {len(report['errors']) - 30} further errors; inspect --report")
        return 0 if report["ok"] else 1
    except (SurfaceError, OSError, KeyError, ValueError, struct.error) as error:
        print(f"class migration surface: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
