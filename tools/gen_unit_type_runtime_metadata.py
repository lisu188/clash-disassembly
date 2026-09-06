#!/usr/bin/env python3
"""Render original unit metadata bytes and native pointer target resolution.

Normal generation uses checked-in evidence only. --verify-exe optionally
corroborates all 40 physical records and pointed-to strings against a local PE;
retail files are never required by public CI.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[1]
DATA = ROOT / "data/unit_type_runtime_metadata.json"
STATE = ROOT / "src/state/00000000_0054FFFF_recovered_state.cpp"
if not STATE.exists():
    STATE = STATE.with_suffix(".c")
BASE_VA = 0x00512568
STRIDE = 88
CAPACITY = 40
TYPE_COUNT = 35
POINTERS_BEGIN = "/* UNIT_METADATA_POINTERS_BEGIN -- generated; do not edit */"
POINTERS_END = "/* UNIT_METADATA_POINTERS_END */"
TABLE_RE = re.compile(
    r"(?:CLASH95_INTERNAL )?const UnitTypeRuntimeCoreMetadataRecord "
    r"g_UnitTypeRuntimeCoreMetadata\[[^\]]+\] =\n\{.*?\n\};", re.S)


def pe_offset(image: bytes, va: int) -> int:
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe:pe + 4] != b"PE\0\0":
        raise ValueError("not a PE image")
    count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    optional = pe + 24
    if struct.unpack_from("<H", image, optional)[0] != 0x10B:
        raise ValueError("expected original PE32 image")
    image_base = struct.unpack_from("<I", image, optional + 28)[0]
    for i in range(count):
        section = optional + optional_size + 40 * i
        _, rva, raw_size, raw = struct.unpack_from("<IIII", image, section + 8)
        delta = va - image_base - rva
        if 0 <= delta < raw_size:
            return raw + delta
    raise ValueError(f"VA {va:#x} is not backed by file bytes")


def pe_records(image: bytes) -> list[dict]:
    def string_bytes(va):
        start = pe_offset(image, va)
        return image[start:image.index(0, start, start + 256)]

    records = []
    for i in range(CAPACITY):
        start = pe_offset(image, BASE_VA + STRIDE * i)
        raw = image[start:start + STRIDE]
        if len(raw) != STRIDE:
            raise ValueError("truncated metadata record")
        stem_va = struct.unpack_from("<I", raw, 81)[0]
        stem = None
        if stem_va:
            stem = string_bytes(stem_va).decode("ascii")
        names_va, resource_va = struct.unpack_from("<II", raw)
        name_vas = list(struct.unpack_from("<III", image, pe_offset(image, names_va))) if names_va else []
        records.append({"id": i, "bytes_hex": raw.hex(), "movement_sound_stem": stem,
                        "localized_name_vas": name_vas,
                        "localized_name_bytes_hex": [string_bytes(va).hex() for va in name_vas],
                        "resource_key": string_bytes(resource_va).decode("ascii") if resource_va else None})
    return records


def load_records() -> list[dict]:
    data = json.loads(DATA.read_text(encoding="utf-8"))
    if (data["schema_version"] != 2 or int(data["base_va"], 0) != BASE_VA
            or data["stride"] != STRIDE or data["physical_record_count"] != CAPACITY
            or data["initialized_type_count"] != TYPE_COUNT
            or int(data["following_symbol_va"], 0) != BASE_VA + STRIDE * CAPACITY):
        raise ValueError("metadata dimensions disagree with original table layout")
    records = data["records"]
    if len(records) != CAPACITY or [r["id"] for r in records] != list(range(CAPACITY)):
        raise ValueError("expected 40 consecutive physical metadata slots")
    raw = [bytes.fromhex(r["bytes_hex"]) for r in records]
    if any(len(r) != STRIDE for r in raw):
        raise ValueError("metadata stride must be 88")
    if any(any(r) for r in raw[TYPE_COUNT:]):
        raise ValueError("five reserved metadata slots must remain zero")
    if hashlib.sha256(b"".join(raw)).hexdigest() != data["table_sha256"]:
        raise ValueError("metadata bytes differ from recorded evidence hash")
    triplets = {}
    strings = {}
    for row, record in zip(raw, records):
        if (struct.unpack_from("<I", row, 81)[0] == 0) != (record["movement_sound_stem"] is None):
            raise ValueError("movement stem disagrees with original pointer presence")
        names_va, resource_va = struct.unpack_from("<II", row)
        if (resource_va == 0) != (record["resource_key"] is None):
            raise ValueError("resource key disagrees with original pointer presence")
        names = record["localized_name_bytes_hex"]
        name_vas = record["localized_name_vas"]
        if len(names) != (3 if names_va else 0) or len(name_vas) != len(names):
            raise ValueError("expected three localized strings for each initialized type")
        if names_va and triplets.setdefault(names_va, name_vas) != name_vas:
            raise ValueError("shared localized triplet has conflicting pointers")
        for va, text in zip(name_vas, names):
            decoded = bytes.fromhex(text)
            if not va or not decoded or b'\0' in decoded or strings.setdefault(va, text) != text:
                raise ValueError("localized string evidence is empty, malformed or conflicting")
        for name in ["movement_sound_stem", "resource_key"]:
            if record[name] is not None:
                record[name].encode("ascii")
                if not record[name] or '\0' in record[name]:
                    raise ValueError("empty or embedded NUL in resource string")
    if len(triplets) != 34 or len(strings) != 102:
        raise ValueError("expected 34 original triplets and 102 localized strings")
    return records


def array(values) -> str:
    return "{ " + ", ".join(str(v) for v in values) + " }"


def render_table(records: list[dict]) -> str:
    # The generated prior extern declaration owns hidden visibility in C/C++.
    lines = ["const UnitTypeRuntimeCoreMetadataRecord "
             "g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_METADATA_CAPACITY] =", "{"]
    for record in records:
        i = record["id"]
        row = bytes.fromhex(record["bytes_hex"])
        if i >= TYPE_COUNT:
            lines.append(f"  /* reserved original slot {i}; retain every zero byte */")
        dword = lambda off: f"0x{struct.unpack_from('<I', row, off)[0]:08X}"
        core = [dword(0), dword(4), *(str(v) for v in row[8:11]), array(row[11:15]),
                *(str(v) for v in row[15:18]), dword(18), *(str(v) for v in row[22:30]),
                array(row[30:38])]
        tail = [array(row[38:70]), *(str(v) for v in row[70:73]),
                str(struct.unpack_from("<H", row, 73)[0]), *(str(v) for v in row[75:81]),
                dword(81), *(str(v) for v in row[85:88])]
        lines.append("  { " + ", ".join(core) + ",")
        lines.append("    " + ", ".join(tail) + " },")
    return "\n".join(lines + ["};"])


def c_string(raw: bytes) -> str:
    # Fixed-width octal escapes preserve original font bytes without UTF-8 recoding
    # or the unbounded digit consumption of C hexadecimal escapes.
    return '"' + ''.join(chr(b) if 32 <= b < 127 and b not in (34, 92)
                         else f'\\{b:03o}' for b in raw) + '"'


def render_pointers(records: list[dict]) -> str:
    lines = [POINTERS_BEGIN,
             "/* Native pointers resolve +0, +4 and +81; packed records retain original VAs. */"]
    emitted = set()
    for record in records:
        va = struct.unpack_from("<I", bytes.fromhex(record["bytes_hex"]))[0]
        if va and va not in emitted:
            names = ', '.join('(char *)' + c_string(bytes.fromhex(text)) for text in record['localized_name_bytes_hex'])
            lines.append(f'static char *const g_UnitTypeNames_{va:08X}[3] '
                         f'CLASH95_LOCAL_SYMBOL(g_UnitTypeNames_{va:08X}) = {{ {names} }};')
            emitted.add(va)
    lines += ["const UnitTypeRuntimePointerRecord "
              "g_UnitTypeRuntimePointers[UNIT_TYPE_METADATA_CAPACITY] =", "{"]
    for record in records:
        va = struct.unpack_from("<I", bytes.fromhex(record["bytes_hex"]))[0]
        names = f'g_UnitTypeNames_{va:08X}' if va else 'NULL'
        text = lambda name: '(char *)' + c_string(record[name].encode('ascii')) if record[name] is not None else 'NULL'
        lines.append(f"  {{ {names}, {text('resource_key')}, {text('movement_sound_stem')} }},")
    return "\n".join(lines + ["};", POINTERS_END])


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--write", action="store_true")
    mode.add_argument("--check", action="store_true")
    parser.add_argument("--verify-exe", type=Path)
    args = parser.parse_args()
    records = load_records()
    if args.verify_exe:
        if pe_records(args.verify_exe.read_bytes()) != records:
            raise ValueError("original PE metadata/stem strings disagree with evidence")
        print("original PE match: 3520 record bytes, all localized names, resource keys and movement stems")
    state = STATE.read_text(encoding="utf-8")
    if len(TABLE_RE.findall(state)) != 1:
        raise ValueError("expected exactly one runtime metadata table")
    state_new = TABLE_RE.sub(lambda _: render_table(records), state)
    pointers_re = re.compile(re.escape(POINTERS_BEGIN) + r".*?" + re.escape(POINTERS_END), re.S)
    if len(pointers_re.findall(state_new)) != 1:
        raise ValueError("expected exactly one native-pointer generated block")
    state_new = pointers_re.sub(lambda _: render_pointers(records), state_new)
    stale = []
    for target, old, new in [(STATE, state, state_new)]:
        if args.write:
            target.write_text(new, encoding="utf-8", newline="\n")
        elif old != new:
            stale.append(str(target.relative_to(ROOT)))
    if stale:
        print("STALE:", *stale)
        return 1
    print("unit metadata: 35 initialized types, 5 reserved slots, stride 88")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
