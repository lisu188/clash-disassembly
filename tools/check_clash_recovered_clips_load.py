#!/usr/bin/env python3
"""Run a CLIPS 6.x parser/load smoke test over generated CLASH_recovered.clp."""
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
COUNT_RE = re.compile(r"^CLASH_(DEFRULES|DEFGLOBALS|DEFFUNCTIONS|DEFCLASSES)=([0-9]+)$", re.MULTILINE)
ERROR_MARKERS = (
    "\nERROR:\n",
    "[PRNTUTIL",
    "[EXPRNPSR",
    "[PRCCODE",
    "[OBJRTBLD",
    "[ARGACCES",
    "[MSGPSR",
)


def _clips_string(path: Path) -> str:
    return str(path).replace("\\", "/").replace('"', '\\"')


def run_load_test(source: Path, clips_exe: str) -> tuple[str, dict[str, int]]:
    ir = parse_bsave(source)
    program, manifest = render_recovered_program(source, ir)
    with tempfile.TemporaryDirectory(prefix="clash-clips-load-") as tmp_name:
        tmp = Path(tmp_name)
        recovered = tmp / "CLASH_recovered.clp"
        batch = tmp / "load.clp"
        recovered.write_text(program, encoding="utf-8")
        recovered_arg = _clips_string(recovered)
        batch.write_text(
            "\n".join([
                "(clear)",
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
            raise AssertionError(f"CLIPS did not finish the load command\n{output}")
        if any(marker in output for marker in ERROR_MARKERS):
            raise AssertionError(f"CLIPS reported parser/construct diagnostics\n{output}")

        counts = {name.lower(): int(value) for name, value in COUNT_RE.findall(output)}
        expected = {
            "defrules": manifest["rules"],
            "defglobals": manifest["defglobals"],
            "deffunctions": manifest["deffunctions"],
        }
        for key, value in expected.items():
            if counts.get(key) != value:
                raise AssertionError(f"CLIPS construct count mismatch for {key}: {counts.get(key)} != {value}\n{output}")
        if counts.get("defclasses", 0) < len(manifest["game_defclasses_emitted"]):
            raise AssertionError("CLIPS loaded fewer defclasses than the recovered game class set\n" + output)
        return output, counts


def main() -> int:
    parser = argparse.ArgumentParser(description="Load generated CLASH_recovered.clp in CLIPS 6.x")
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clips", default=os.environ.get("CLIPS", "clips"))
    args = parser.parse_args()
    clips_exe = shutil.which(args.clips) if os.path.sep not in args.clips else args.clips
    if not clips_exe or not Path(clips_exe).exists():
        raise SystemExit(f"CLIPS executable not found: {args.clips}")
    output, counts = run_load_test(Path(args.input), clips_exe)
    print("CLASH_recovered.clp CLIPS load contract: PASS")
    print(" ".join([
        f"defrules={counts.get('defrules')}",
        f"defglobals={counts.get('defglobals')}",
        f"deffunctions={counts.get('deffunctions')}",
        f"defclasses={counts.get('defclasses')}",
    ]))
    parser_lines = [line for line in output.splitlines() if line.startswith("[")]
    if parser_lines:
        print("CLIPS diagnostics:")
        print("\n".join(parser_lines))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
