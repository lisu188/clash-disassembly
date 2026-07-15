#!/usr/bin/env python3
"""Compare split and unified-oracle object code by recovered function identity.

The comparator consumes an existing CMake build containing both object models.
It normalizes link-dependent addresses and relocation *kinds* while retaining
instruction operands, relocation targets, and symbol names.  This makes a
translation-unit split comparable without hiding changed constants or calls.
"""

from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "data" / "recovered_sources.json"
DEFAULT_EXCEPTIONS = ROOT / "data" / "split_disassembly_exceptions.json"
FUNCTION_HEADER_RE = re.compile(r"^[0-9A-Fa-f]+ <([^>]+)>:$")
LINE_ADDRESS_RE = re.compile(r"^\s*[0-9A-Fa-f]+:\s*")
TARGET_ADDRESS_RE = re.compile(r"\b(?:0x)?[0-9A-Fa-f]+\s+(?=<[^>]+>)")
RIP_DISPLACEMENT_RE = re.compile(r"-?0x[0-9A-Fa-f]+(?=\(%rip\))")
COMMENT_ADDRESS_RE = re.compile(r"#\s*(?:0x)?[0-9A-Fa-f]+\s*(?=<[^>]+>)")
RELOCATION_RE = re.compile(r"^R_[A-Za-z0-9_]+\s+(.*)$")


class ComparisonError(RuntimeError):
    pass


def command_output(command: list[str]) -> str:
    try:
        result = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=False,
        )
    except FileNotFoundError as error:
        raise ComparisonError(f"required tool is unavailable: {command[0]}") from error
    if result.returncode:
        raise ComparisonError(
            f"{' '.join(command)} failed ({result.returncode}): {result.stderr.strip()}"
        )
    return result.stdout


def normalize_disassembly_line(raw: str) -> str:
    line = LINE_ADDRESS_RE.sub("", raw.rstrip())
    relocation = RELOCATION_RE.match(line)
    if relocation:
        target = relocation.group(1)
        target = re.sub(
            r"^(\.(?:rodata|data|bss)(?:\.[A-Za-z0-9_.]+)?)[+-]0x[0-9A-Fa-f]+$",
            r"\1",
            target,
        )
        target = re.sub(r"^\.(?:text|rodata|data|bss)\.([A-Za-z_].*)$", r"\1", target)
        target = re.sub(r"([A-Za-z_][A-Za-z0-9_.$@]*)(?:[+-]0x[0-9A-Fa-f]+)$", r"\1", target)
        # GCC numbers function-local static symbols in whole-TU discovery
        # order. Splitting changes only that private suffix.
        target = re.sub(r"\.\d+$", ".LOCAL", target)
        return "RELOC " + target
    line = RIP_DISPLACEMENT_RE.sub("<RIP_DISP>", line)
    line = COMMENT_ADDRESS_RE.sub("# ", line)
    line = TARGET_ADDRESS_RE.sub("", line)
    line = re.sub(r"<([^+>]+)\+0x[0-9A-Fa-f]+>", r"<\1>", line)
    line = re.sub(r"^sub\s+\$0x[0-9A-Fa-f]+,%rsp$", "sub    $<FRAME>,%rsp", line.strip())
    return line.strip()


def object_functions(path: Path, objdump: str) -> dict[str, tuple[str, ...]]:
    output = command_output([objdump, "-dr", "--no-show-raw-insn", str(path)])
    functions: dict[str, list[str]] = {}
    current: list[str] | None = None
    for raw in output.splitlines():
        header = FUNCTION_HEADER_RE.match(raw.strip())
        if header:
            name = header.group(1)
            if name in functions:
                raise ComparisonError(f"duplicate function symbol {name!r} in {path}")
            current = []
            functions[name] = current
            continue
        if current is None or not raw.strip() or raw.startswith("Disassembly of section"):
            continue
        current.append(normalize_disassembly_line(raw))
    return {name: tuple(lines) for name, lines in functions.items()}


def merge_functions(
    paths: list[Path], objdump: str, wanted: set[str]
) -> dict[str, tuple[str, ...]]:
    merged: dict[str, tuple[str, ...]] = {}
    owners: dict[str, Path] = {}
    for path in paths:
        for name, body in object_functions(path, objdump).items():
            if name not in wanted:
                continue
            if name in merged:
                raise ComparisonError(
                    f"function symbol {name!r} appears in both {owners[name]} and {path}"
                )
            merged[name] = body
            owners[name] = path
    return merged


def recovered_objects(build_dir: Path) -> list[Path]:
    object_dirs = sorted(
        path
        for path in (build_dir / "CMakeFiles").glob(
            "clash95_recovered_*_objects.dir"
        )
        if path.name != "clash95_recovered_coverage_objects.dir"
    )
    objects = sorted(path for directory in object_dirs for path in directory.rglob("*.o"))
    if not objects:
        raise ComparisonError(f"no split recovered objects found below {build_dir}")
    return objects


def oracle_object(build_dir: Path) -> Path:
    candidates = sorted(
        (build_dir / "CMakeFiles" / "clash95_unified_oracle_objects.dir").rglob("*.o")
    )
    if len(candidates) != 1:
        raise ComparisonError(
            f"expected one unified-oracle object below {build_dir}, found {len(candidates)}"
        )
    return candidates[0]


def default_symbol_surface(executable: Path, readelf: str) -> set[tuple[str, str, str]]:
    output = command_output([readelf, "-Ws", str(executable)])
    symbols: set[tuple[str, str, str]] = set()
    for raw in output.splitlines():
        fields = raw.split()
        if len(fields) < 8 or not fields[0].endswith(":"):
            continue
        symbol_type, binding, visibility, section, name = (
            fields[3],
            fields[4],
            fields[5],
            fields[6],
            fields[7],
        )
        if binding not in {"GLOBAL", "WEAK"} or visibility != "DEFAULT" or section == "UND":
            continue
        symbols.add((name, symbol_type, binding))
    return symbols


def function_digest(body: tuple[str, ...]) -> str:
    return hashlib.sha256("\n".join(body).encode("utf-8")).hexdigest()


def load_exceptions(path: Path) -> dict[str, dict[str, str]]:
    if not path.exists():
        return {}
    payload = json.loads(path.read_text(encoding="utf-8"))
    if payload.get("schema_version") != 1 or not isinstance(payload.get("exceptions"), list):
        raise ComparisonError(f"invalid disassembly exception document: {path}")
    result: dict[str, dict[str, str]] = {}
    for record in payload["exceptions"]:
        if not isinstance(record, dict) or not all(
            isinstance(record.get(field), str) and record[field]
            for field in ("name", "reason", "oracle_sha256", "split_sha256")
        ):
            raise ComparisonError(f"invalid disassembly exception record in {path}")
        if record["name"] in result:
            raise ComparisonError(f"duplicate disassembly exception: {record['name']}")
        result[record["name"]] = record
    return result


def exception_reason(name: str) -> str:
    if name in {
        "Battle_RunTacticalCombat",
        "Building_GetInto",
        "Castle_OpenManagementScreen",
    }:
        return (
            "The unified TU constant-folds a comparison between two distinct "
            "function addresses; the split TU emits the equivalent runtime comparison."
        )
    return (
        "GNU C17 requires a cross-TU declaration where the GNU89 oracle used "
        "definition order or an implicit/comment-only declaration; this changes "
        "host-width extension or register allocation without changing body tokens."
    )


def write_exceptions(
    path: Path,
    changed: list[str],
    oracle: dict[str, tuple[str, ...]],
    split: dict[str, tuple[str, ...]],
) -> None:
    payload = {
        "schema_version": 1,
        "normalization": "tools/compare_split_oracle.py",
        "exceptions": [
            {
                "name": name,
                "reason": exception_reason(name),
                "oracle_sha256": function_digest(oracle[name]),
                "split_sha256": function_digest(split[name]),
            }
            for name in changed
        ],
    }
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("build_dir", type=Path)
    parser.add_argument("--manifest", type=Path, default=MANIFEST)
    parser.add_argument("--objdump", default="objdump")
    parser.add_argument("--readelf", default="readelf")
    parser.add_argument("--max-diffs", type=int, default=10)
    parser.add_argument("--skip-symbols", action="store_true")
    parser.add_argument("--exceptions", type=Path, default=DEFAULT_EXCEPTIONS)
    parser.add_argument(
        "--update-exceptions",
        action="store_true",
        help="replace the reviewed normalized-difference hash list",
    )
    args = parser.parse_args()

    build_dir = args.build_dir.resolve()
    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    names = {record["name"] for record in manifest["functions"]}
    if len(names) != manifest.get("function_count"):
        raise ComparisonError("manifest function names are not unique")

    split = merge_functions(recovered_objects(build_dir), args.objdump, names)
    oracle = object_functions(oracle_object(build_dir), args.objdump)
    missing_split = sorted(names - split.keys())
    missing_oracle = sorted(names - oracle.keys())
    changed = sorted(name for name in names & split.keys() & oracle.keys() if split[name] != oracle[name])

    if args.update_exceptions:
        write_exceptions(args.exceptions, changed, oracle, split)
        print(f"wrote {len(changed)} normalized exceptions to {args.exceptions}")
        return 0
    exceptions = load_exceptions(args.exceptions)
    allowed = sorted(
        name
        for name in changed
        if name in exceptions
        and exceptions[name]["oracle_sha256"] == function_digest(oracle[name])
        and exceptions[name]["split_sha256"] == function_digest(split[name])
    )
    unexpected = sorted(set(changed) - set(allowed))
    stale = sorted(set(exceptions) - set(changed))

    symbol_only_split: list[tuple[str, str, str]] = []
    symbol_only_oracle: list[tuple[str, str, str]] = []
    if not args.skip_symbols:
        split_executable = build_dir / "bin" / "clash95_bootstrap"
        oracle_executable = build_dir / "bin" / "clash95_bootstrap_oracle"
        if not split_executable.is_file() or not oracle_executable.is_file():
            raise ComparisonError("both linked bootstrap executables are required")
        split_symbols = default_symbol_surface(split_executable, args.readelf)
        oracle_symbols = default_symbol_surface(oracle_executable, args.readelf)
        symbol_only_split = sorted(split_symbols - oracle_symbols)
        symbol_only_oracle = sorted(oracle_symbols - split_symbols)

    print(
        "split/oracle object parity: "
        f"functions={len(names)}, normalized_equal={len(names) - len(changed)}, "
        f"reviewed_differences={len(allowed)}, unexpected={len(unexpected)}, "
        f"missing_split={len(missing_split)}, missing_oracle={len(missing_oracle)}"
    )
    if not args.skip_symbols:
        print(
            "default-visible symbol parity: "
            f"split_only={len(symbol_only_split)}, oracle_only={len(symbol_only_oracle)}"
        )

    for label, values in (
        ("missing from split", missing_split),
        ("missing from oracle", missing_oracle),
        ("split-only symbols", [item[0] for item in symbol_only_split]),
        ("oracle-only symbols", [item[0] for item in symbol_only_oracle]),
        ("stale disassembly exceptions", stale),
    ):
        if values:
            print(f"{label}: {', '.join(values[: args.max_diffs])}")

    for name in unexpected[: args.max_diffs]:
        print(f"disassembly differs: {name}")
        difference = difflib.unified_diff(
            oracle[name], split[name], fromfile="oracle", tofile="split", lineterm=""
        )
        for line in list(difference)[:40]:
            print(line)

    return 1 if any(
        (
            missing_split,
            missing_oracle,
            unexpected,
            stale,
            symbol_only_split,
            symbol_only_oracle,
        )
    ) else 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (ComparisonError, OSError, json.JSONDecodeError) as error:
        raise SystemExit(str(error)) from error
