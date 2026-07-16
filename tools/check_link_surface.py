#!/usr/bin/env python3
"""Linked-binary symbol-surface and data-layout gate.

Closes the one verification gap left after the GNU C17 cutover: the manifest
body-hash audit proves per-function source identity and obj_diff_gate.sh proves
per-TU instruction identity, but nothing pinned the LINKED artifact — which
symbols survive --gc-sections, their section classes, and (critically) the
address ORDER and sizes of data/BSS symbols. Global storage lives in the single
recovered-state TU precisely because recovered code may depend on physical data
adjacency; this gate makes any layout drift visible.

What is pinned, per compiler profile (gcc / clang):
  - text symbols: presence + symbol class only (body edits do not trip the gate;
    adding/removing/renaming a linked function does);
  - data symbols (classes b/B/d/D/r/R and common): presence + class + SIZE +
    their ADDRESS-ORDERED per-class sequence (the data-layout pin);
  - toolchain artifacts (gcov/CRT/linker symbols) are excluded by pattern.

Cross-check (independent of the baseline): every manifest function must be
defined exactly once in libclash95_recovered.a — 'external'/'internal' linkage
as a global symbol, 'static'/'test-visible-static' as a local symbol (in
production builds CLASH95_TEST_VISIBLE expands to static). This catches a
function silently dropped from, duplicated in, or linkage-flipped by a refactor
before the executable gate even runs.

Usage:
  python3 tools/check_link_surface.py BINARY --lib ARCHIVE --compiler gcc \
      [--baseline data/link_surface_baseline.json] --mode check|update|report

Modes mirror check_recovered_warnings.py: 'check' fails on ANY profile
difference; 'update' rewrites the profile for the given compiler (run only on a
reviewed, clean, full build); 'report' prints the diff without failing.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
DEFAULT_BASELINE = REPO / "data" / "link_surface_baseline.json"
MANIFEST = REPO / "data" / "recovered_sources.json"

SCHEMA_VERSION = 1

DATA_CLASSES = set("bBdDrRgGsS")  # bss, data, rodata, small-data variants
COMMON_CLASSES = set("cC")

# Toolchain/CRT/instrumentation artifacts excluded from the recovered surface.
# Names carrying a glibc version suffix (stderr@GLIBC_2.2.5 copy relocations)
# and linker-script/crt symbols (_DYNAMIC, __abi_tag, frame markers) are
# binutils/glibc-version dependent - pinning them makes the baseline break on
# toolchain image bumps with zero repo change.
ARTIFACT_RE = re.compile(
    r"^(_GLOBAL_|__gcov|__llvm|_IO_|__libc|__x86|_dl_|__dso_handle$|__TMC|"
    r"__bss_start$|_edata$|_end$|_init$|_fini$|_start$|__data_start$|"
    r"data_start$|__init_array|__fini_array|__frame_dummy|frame_dummy$|"
    r"register_tm_clones$|deregister_tm_clones$|__do_global|completed\.|"
    r"__stack_chk|_ITM_|__gmon|__odr_asan|\.L|"
    r"_DYNAMIC$|__abi_tag$|__GNU_EH_FRAME_HDR$|__FRAME_END__$)"
    r"|@"
)


def run_nm(path: Path, extra: list[str] | None = None) -> str:
    cmd = ["nm", "--defined-only", "--print-size", "--format=bsd"]
    if extra:
        cmd.extend(extra)
    cmd.append(str(path))
    proc = subprocess.run(cmd, capture_output=True, text=True)
    if proc.returncode != 0:
        raise SystemExit(f"nm failed on {path}: {proc.stderr.strip()}")
    return proc.stdout


NM_LINE = re.compile(
    r"^(?P<addr>[0-9a-fA-F]+)\s+(?:(?P<size>[0-9a-fA-F]+)\s+)?"
    r"(?P<cls>[A-Za-z])\s+(?P<name>\S+)$"
)


def parse_nm(text: str):
    """Yield (addr:int, size:int, cls:str, name:str) for defined symbols."""
    for line in text.splitlines():
        line = line.strip()
        if not line or line.endswith(":") or "file format" in line:
            continue
        m = NM_LINE.match(line)
        if not m:
            continue
        yield (
            int(m.group("addr"), 16),
            int(m.group("size") or "0", 16),
            m.group("cls"),
            m.group("name"),
        )


def executable_profile(binary: Path) -> dict:
    """Build the pinned profile of the linked executable."""
    text_syms = []
    data_rows = []  # (addr, size, cls, name)
    for addr, size, cls, name in parse_nm(run_nm(binary)):
        if ARTIFACT_RE.search(name):
            continue
        if cls in ("t", "T"):
            text_syms.append(f"{name} {cls}")
        elif cls in DATA_CLASSES or cls in COMMON_CLASSES:
            data_rows.append((addr, size, cls, name))
    data_rows.sort(key=lambda r: (r[2].lower(), r[0]))
    ordered: dict[str, list[str]] = {}
    for addr, size, cls, name in data_rows:
        ordered.setdefault(cls.lower(), []).append(f"{name} {cls} {size}")
    return {
        "text": sorted(text_syms),
        "data_ordered": ordered,
        "counts": {
            "text": len(text_syms),
            "data": sum(len(v) for v in ordered.values()),
        },
    }


def library_crosscheck(archive: Path) -> list[str]:
    """Manifest-vs-archive check; returns a list of error strings."""
    manifest = json.loads(MANIFEST.read_text(encoding="utf-8"))
    expect_global = {}
    expect_local = {}
    for rec in manifest["functions"]:
        name = rec["name"]
        if rec["linkage"] in ("external", "internal"):
            expect_global[name] = rec["linkage"]
        else:  # static, test-visible-static (production => static)
            expect_local[name] = rec["linkage"]

    defined_global: dict[str, int] = {}
    defined_local: dict[str, int] = {}
    for _addr, _size, cls, name in parse_nm(run_nm(archive)):
        if cls in ("T", "D", "B", "R", "G", "S", "C"):
            defined_global[name] = defined_global.get(name, 0) + 1
        elif cls in ("t", "d", "b", "r", "g", "s"):
            defined_local[name] = defined_local.get(name, 0) + 1

    errors = []
    for name, linkage in sorted(expect_global.items()):
        n = defined_global.get(name, 0)
        if n != 1:
            errors.append(
                f"manifest {linkage} function {name!r}: defined {n}x as a "
                f"global in {archive.name} (want exactly 1)"
            )
    for name, linkage in sorted(expect_local.items()):
        n = defined_local.get(name, 0)
        if n != 1:
            errors.append(
                f"manifest {linkage} function {name!r}: defined {n}x as a "
                f"local in {archive.name} (want exactly 1)"
            )
    return errors


def empty_baseline() -> dict:
    return {"schema_version": SCHEMA_VERSION, "profiles": {}}


def load_baseline(path: Path, allow_missing: bool) -> dict:
    if not path.exists():
        if allow_missing:
            return empty_baseline()
        raise SystemExit(f"baseline missing: {path} (seed with --mode update)")
    data = json.loads(path.read_text(encoding="utf-8"))
    if data.get("schema_version") != SCHEMA_VERSION:
        raise SystemExit(
            f"baseline schema {data.get('schema_version')} != {SCHEMA_VERSION}"
        )
    return data


def diff_profiles(base: dict, cur: dict) -> list[str]:
    """Multiset-aware profile diff. Duplicate local symbols are real in this
    binary (e.g. several TUs each define a local NtCurrentTeb), so plain set
    comparison would silently pass multiplicity drift."""
    from collections import Counter

    problems = []
    b_text, c_text = Counter(base.get("text", [])), Counter(cur["text"])
    for sym in sorted(c_text - b_text):
        problems.append(
            f"NEW text symbol: {sym} (x{(c_text - b_text)[sym]})")
    for sym in sorted(b_text - c_text):
        problems.append(
            f"MISSING text symbol: {sym} (x{(b_text - c_text)[sym]})")
    b_data = base.get("data_ordered", {})
    c_data = cur["data_ordered"]
    for cls in sorted(set(b_data) | set(c_data)):
        b_seq = b_data.get(cls, [])
        c_seq = c_data.get(cls, [])
        if b_seq == c_seq:
            continue
        b_cnt, c_cnt = Counter(b_seq), Counter(c_seq)
        for sym in sorted(c_cnt - b_cnt):
            problems.append(f"NEW/changed data symbol [{cls}]: {sym}")
        for sym in sorted(b_cnt - c_cnt):
            problems.append(f"MISSING/changed data symbol [{cls}]: {sym}")
        if b_cnt == c_cnt:
            problems.append(
                f"data ORDER changed in class [{cls}] "
                f"({len(b_seq)} symbols, same multiset, different sequence)"
            )
    return problems


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("binary", type=Path, help="linked clash95_bootstrap")
    ap.add_argument("--lib", type=Path, required=True,
                    help="libclash95_recovered.a for the manifest cross-check")
    ap.add_argument("--compiler", required=True, choices=("gcc", "clang"))
    ap.add_argument("--baseline", type=Path, default=DEFAULT_BASELINE)
    ap.add_argument("--mode", choices=("check", "update", "report"),
                    default="check")
    args = ap.parse_args()

    lib_errors = library_crosscheck(args.lib)
    for err in lib_errors:
        print(f"CROSSCHECK: {err}")

    current = executable_profile(args.binary)
    baseline = load_baseline(args.baseline, allow_missing=args.mode == "update")

    if args.mode == "update":
        if lib_errors:
            print(f"refusing to update baseline: {len(lib_errors)} "
                  "manifest cross-check error(s)")
            return 1
        baseline["profiles"][args.compiler] = current
        args.baseline.parent.mkdir(parents=True, exist_ok=True)
        args.baseline.write_text(
            json.dumps(baseline, indent=1, sort_keys=True) + "\n",
            encoding="utf-8",
        )
        print(
            f"updated link-surface baseline [{args.compiler}]: "
            f"{current['counts']['text']} text, "
            f"{current['counts']['data']} data symbols -> {args.baseline}"
        )
        return 0

    profile = baseline["profiles"].get(args.compiler)
    if profile is None:
        print(f"{args.compiler} link-surface profile is unseeded; "
              "run with --mode update on a reviewed clean build")
        return 0 if args.mode == "report" else 1

    problems = diff_profiles(profile, current)
    for p in problems[:80]:
        print(p)
    if len(problems) > 80:
        print(f"... and {len(problems) - 80} more")

    ok = not problems and not lib_errors
    print(
        f"link-surface [{args.compiler}]: "
        f"{'PASS' if ok else 'FAIL'} "
        f"(text={current['counts']['text']}, data={current['counts']['data']}, "
        f"diffs={len(problems)}, crosscheck_errors={len(lib_errors)})"
    )
    if args.mode == "report":
        return 0
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
