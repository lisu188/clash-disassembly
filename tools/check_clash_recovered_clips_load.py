#!/usr/bin/env python3
"""Run a stock CLIPS 6.x load smoke test over generated CLASH_recovered.clp.

The retail image was built for the game's embedded CLIPS environment, which
registers native C functions before loading CLASH.DAT. Stock CLIPS does not know
those host functions. For a standalone parser/load contract this harness derives
the host-function slice directly from the BSAVE function table and defines
wildcard deffunction stubs in a separate temporary file. The generated recovered
source itself remains free of test-only stubs.
"""
from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

from decompile_clash_dat import parse_bsave
from generate_clash_recovered_constraints import render_recovered_program

DONE_RE = re.compile(r"^CLASH_LOAD_DONE$", re.MULTILINE)
COUNT_RE = re.compile(
    r"^CLASH_(STUB_DEFFUNCTIONS|DEFRULES|DEFGLOBALS|DEFFUNCTIONS|DEFCLASSES)=([0-9]+)$",
    re.MULTILINE,
)
ERROR_MARKERS = (
    "\nERROR:\n",
    "[PRNTUTIL",
    "[EXPRNPSR",
    "[PRCCODE",
    "[OBJRTBLD",
    "[ARGACCES",
    "[MSGPSR",
    "[CSTRCPSR",
    "[RULEPSR",
)


def _clips_string(path: Path) -> str:
    return str(path).replace("\\", "/").replace('"', '\\"')


def _host_function_names(ir: dict) -> list[str]:
    """Return the exact native game-function slice serialized in CLASH.DAT.

    The retail function table has CLIPS built-ins through `assert`, then the
    game's registered host/native functions, then resumes the stock math/function
    table at `**`. This ordering is part of the binary evidence and is locked by
    the standalone load contract rather than maintained as a hand-written list.
    """
    functions = list(ir["functions"])
    try:
        start = functions.index("assert") + 1
        end = functions.index("**")
    except ValueError as exc:
        raise AssertionError("retail function-table host-function boundaries changed") from exc
    names = functions[start:end]
    if len(names) != 82:
        raise AssertionError(f"expected 82 retail host functions, found {len(names)}")
    recovered_deffunctions = {item["name"] for item in ir["deffunctions"]}
    overlap = recovered_deffunctions.intersection(names)
    if overlap:
        raise AssertionError(f"host-function slice overlaps recovered deffunctions: {sorted(overlap)}")
    if len(set(names)) != len(names):
        raise AssertionError("duplicate host function names in retail function table")
    return names


def _render_host_stubs(ir: dict) -> tuple[str, list[str]]:
    names = _host_function_names(ir)
    lines = [
        ";;; Standalone CLIPS parser/load harness only.",
        ";;; These names are native C functions in the embedded game runtime.",
    ]
    for name in names:
        lines.append(f"(deffunction {name} ($?args) FALSE)")
    lines.append("")
    return "\n".join(lines), names


def run_load_test(source: Path, clips_exe: str) -> tuple[str, dict[str, int]]:
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)
    stub_source, stub_names = _render_host_stubs(ir)

    with tempfile.TemporaryDirectory(prefix="clash-clips-load-") as tmp_name:
        tmp = Path(tmp_name)
        recovered = tmp / "CLASH_recovered.clp"
        stubs = tmp / "host_stubs.clp"
        batch = tmp / "load.clp"
        recovered.write_text(program, encoding="utf-8")
        stubs.write_text(stub_source, encoding="utf-8")
        recovered_arg = _clips_string(recovered)
        stubs_arg = _clips_string(stubs)
        batch.write_text(
            "\n".join([
                "(clear)",
                '(printout t "CLASH_STUB_LOAD_BEGIN" crlf)',
                f'(load "{stubs_arg}")',
                '(printout t "CLASH_STUB_DEFFUNCTIONS=" (length$ (get-deffunction-list)) crlf)',
                '(printout t "CLASH_LOAD_BEGIN" crlf)',
                f'(load "{recovered_arg}")',
                '(printout t "CLASH_LOAD_DONE" crlf)',
                '(printout t "CLASH_DEFRULES=" (length$ (get-defrule-list)) crlf)',
                '(printout t "CLASH_DEFGLOBALS=" (length$ (get-defglobal-list)) crlf)',
                '(printout t "CLASH_DEFFUNCTIONS=" (length$ (get-deffunction-list)) crlf)',
                '(printout t "CLASH_DEFCLASSES=" (length$ (get-defclass-list)) crlf)',
                "(exit)",
                "",
            ]),
            encoding="utf-8",
        )
        proc = subprocess.run(
            [clips_exe, "-f2", str(batch)],
            cwd=tmp,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="replace",
            check=False,
            timeout=60,
        )
        output = proc.stdout
        if proc.returncode != 0:
            raise AssertionError(f"CLIPS exited with {proc.returncode}\n{output}")
        if not DONE_RE.search(output):
            raise AssertionError(f"CLIPS did not finish the recovered-source load command\n{output}")
        if any(marker in output for marker in ERROR_MARKERS):
            raise AssertionError(f"CLIPS reported parser/construct diagnostics\n{output}")

        counts = {name.lower(): int(value) for name, value in COUNT_RE.findall(output)}
        stub_count = counts.get("stub_deffunctions")
        if stub_count != len(stub_names):
            raise AssertionError(f"CLIPS host-stub count mismatch: {stub_count} != {len(stub_names)}\n{output}")

        expected = {
            "defrules": manifest["rules"],
            "defglobals": manifest["defglobals"],
            "deffunctions": len(stub_names) + manifest["deffunctions"],
        }
        for key, value in expected.items():
            if counts.get(key) != value:
                raise AssertionError(f"CLIPS construct count mismatch for {key}: {counts.get(key)} != {value}\n{output}")
        if counts.get("defclasses", 0) < len(manifest["game_defclasses_emitted"]):
            raise AssertionError("CLIPS loaded fewer defclasses than the recovered game class set\n" + output)
        return output, counts


def main() -> int:
    parser = argparse.ArgumentParser(description="Load generated CLASH_recovered.clp in stock CLIPS 6.x")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clips", default=os.environ.get("CLIPS", "clips"))
    args = parser.parse_args()
    clips_exe = shutil.which(args.clips) if os.path.sep not in args.clips else args.clips
    if not clips_exe or not Path(clips_exe).exists():
        raise SystemExit(f"CLIPS executable not found: {args.clips}")
    output, counts = run_load_test(Path(args.input), clips_exe)
    print("CLASH_recovered.clp stock-CLIPS load contract: PASS")
    print(" ".join([
        f"host-stubs={counts.get('stub_deffunctions')}",
        f"defrules={counts.get('defrules')}",
        f"defglobals={counts.get('defglobals')}",
        f"deffunctions-total={counts.get('deffunctions')}",
        f"defclasses={counts.get('defclasses')}",
    ]))
    parser_lines = [line for line in output.splitlines() if line.startswith("[")]
    if parser_lines:
        print("CLIPS diagnostics:")
        print("\n".join(parser_lines))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
