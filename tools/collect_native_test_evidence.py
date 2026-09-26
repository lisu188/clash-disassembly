#!/usr/bin/env python3
"""Retain native registrations and reconcile CTest output without changing tests.

Run ``registry --binary B --root R --output E`` before CTest, then
``reconcile --evidence E --log LastTest.log --ctest-exit-code STATUS``.
Collector success means complete evidence, not a passing native test suite.
"""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import subprocess
import sys
import time


NAME = r"[A-Za-z_][A-Za-z_0-9]*\.[A-Za-z_][A-Za-z_0-9]*"
SUMMARY = re.compile(r"^== (\d+) passed, (\d+) failed, (\d+) crashed, (\d+) total ==$")
EXCEPTION = re.compile(rf"^(FAIL  |CRASH |ERROR )({NAME})(?P<detail>(?:[: \t].*)?)$")
EXCEPTION_MARKER = re.compile(r"(?:FAIL|CRASH|ERROR)(?=\s|$)")
GDB_SCRIPT = '''set pagination off
set confirm off
set debuginfod enabled off
set environment SDL_VIDEODRIVER dummy
set environment SDL_AUDIODRIVER dummy
break main
run --help
python
import json, os
count = int(gdb.parse_and_eval('g_clash_test_count'))
assert 0 < count <= 40000
table = gdb.parse_and_eval('g_clash_tests')
names = [table[index]['name'].string() for index in range(count)]
assert len(names) == len(set(names))
with open(os.environ['CLASH95_REF_REGISTRY'], 'x') as output:
    json.dump({'count': count, 'names': names}, output, indent=2)
    output.write('\\n')
print('Captured %d unique registered cases at main entry' % count)
end
quit
'''


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def write_json(path: Path, value: object) -> None:
    with path.open("x", encoding="utf-8", newline="\n") as stream:
        json.dump(value, stream, indent=2)
        stream.write("\n")


def git_head(root: Path) -> str:
    result = subprocess.run(["git", "-C", str(root), "rev-parse", "HEAD"],
                            capture_output=True, text=True, check=True, timeout=15)
    revision = result.stdout.strip()
    if not re.fullmatch(r"[0-9a-f]{40}", revision):
        raise ValueError("Git HEAD is not a complete SHA-1 commit identity")
    return revision


def registry_names(registry: object) -> list[str]:
    if not isinstance(registry, dict):
        raise ValueError("registry must be an object")
    count, names = registry.get("count"), registry.get("names")
    if type(count) is not int or not 0 < count <= 40000 or not isinstance(names, list):
        raise ValueError("invalid registry count or names")
    if len(names) != count or any(not isinstance(n, str) or not re.fullmatch(NAME, n) for n in names):
        raise ValueError("registry count/name mismatch")
    if len(set(names)) != count:
        raise ValueError("duplicate registered names")
    return names


def ctest_output(text: str, binary: str) -> tuple[str, str, list[str]]:
    """Require one complete unit CTest record bound to the captured binary."""
    tests = re.findall(r"^\d+/\d+ Test: (.+)$", text, re.MULTILINE)
    if tests != ["clash95_unit_tests"]:
        raise ValueError("LastTest.log must contain exactly the native unit CTest")
    commands = re.findall(r"^Command: (.+)$", text, re.MULTILINE)
    if len(commands) != 1:
        raise ValueError("missing or duplicate CTest command")
    command = shlex.split(commands[0])
    if command.count(binary) != 1:
        raise ValueError("CTest command does not name the captured binary exactly once")
    outputs = re.findall(r"^Output:\n-+\n(.*?)^<end of output>$", text,
                         re.MULTILINE | re.DOTALL)
    results = re.findall(r"^Test (Passed|Failed)\.$", text, re.MULTILINE)
    if len(outputs) != 1 or len(results) != 1:
        raise ValueError("missing or duplicate complete CTest output/result")
    return outputs[0], results[0], command


def reconcile_output(registry: object, text: str, mode: str = "default") -> dict:
    """Keep exception details; assign silent PASS only after exact reconciliation."""
    names = registry_names(registry)
    known_names = set(names)
    if mode not in ("default", "strict"):
        raise ValueError("unknown native runner mode")
    summaries, observed, other = [], {}, []
    for number, raw in enumerate(text.splitlines(), 1):
        summary = SUMMARY.fullmatch(raw)
        if summary:
            summaries.append((number, tuple(map(int, summary.groups()))))
            continue
        if raw.startswith("=="):
            raise ValueError(f"malformed summary at output line {number}")
        # Concurrent diagnostics can precede a complete exception report on the
        # same line. Accept only one complete exception suffix, with the same
        # registered-name and total checks as a standalone report. Multiple
        # status markers are ambiguous, even within otherwise valid detail.
        markers = list(EXCEPTION_MARKER.finditer(raw))
        if len(markers) > 1:
            raise ValueError(f"multiple exception markers at output line {number}")
        start = markers[0].start() if markers else 0
        exception = EXCEPTION.fullmatch(raw[start:]) if markers else None
        if exception:
            status, name = exception.group(1).strip(), exception.group(2)
            if name not in known_names:
                raise ValueError(f"foreign exception name: {name}")
            if name in observed:
                raise ValueError(f"duplicate exception name: {name}")
            observed[name] = {"outcome": status, "output_line": number,
                              "raw": raw, "reported_detail": exception.group("detail")}
            if start:
                # Retain the entire joined line and its prefix without assigning
                # that diagnostic to this exception or another worker's case.
                other.append({"output_line": number, "raw": raw,
                              "interleaved_prefix": raw[:start]})
        elif markers:
            raise ValueError(f"malformed exception at output line {number}")
        elif raw:
            # Sixteen workers can interleave CHECK diagnostics. Do not guess
            # which exception owns an unlabelled assertion or signal message.
            other.append({"output_line": number, "raw": raw})
    if len(summaries) != 1:
        raise ValueError("expected exactly one complete native summary")
    summary_line, totals = summaries[0]
    if any(row["output_line"] > summary_line for row in observed.values()):
        raise ValueError("exception after final native summary")
    passed, failed, crashed, total = totals
    counts = Counter(row["outcome"] for row in observed.values())
    expected = (len(names) - len(observed), counts["FAIL"] + counts["ERROR"],
                counts["CRASH"], len(names))
    if totals != expected or passed + failed + crashed != total:
        raise ValueError(f"native totals {totals} do not match registry/exceptions {expected}")
    return {
        "counts": dict(passed=passed, failed=failed, crashed=crashed, total=total),
        "mode": mode,
        "runner_policy_would_succeed": failed == 0 and (mode != "strict" or crashed == 0),
        "cases": [dict(index=i, name=name, outcome=observed.get(name, {}).get("outcome", "PASS"),
                       **({"exception": observed[name]} if name in observed else {}))
                  for i, name in enumerate(names)],
        "unattributed_diagnostics": other,
        "pass_resolution": "Actual binary registrations minus exceptions, reconciled to every native total.",
        "signal_limit": "The runner does not emit the specific caught signal. Raw reported details are retained; no signal or cross-worker attribution is invented.",
    }


def capture_registry(args: argparse.Namespace) -> int:
    evidence = args.output.resolve()
    evidence.mkdir(parents=True, exist_ok=False)
    receipt = {"schema_version": 1, "stage": "registry", "complete": False,
               "collection_started_unix_ns": time.time_ns()}
    try:
        root, binary = args.root.resolve(strict=True), args.binary.resolve(strict=True)
        receipt.update(root=str(root), binary=str(binary), git_head=git_head(root),
                       binary_sha256=sha256(binary))
        script = evidence / "capture-registry.gdb"
        script.write_text(GDB_SCRIPT, encoding="utf-8", newline="\n")
        command = [args.gdb, "-nx", "-batch", "-x", str(script), str(binary)]
        receipt.update(command=command, script_sha256=sha256(script))
        env = dict(os.environ, CLASH95_REF_REGISTRY=str(evidence / "registry.json"))
        try:
            result = subprocess.run(command, cwd=root, env=env, capture_output=True,
                                    timeout=args.timeout)
            stdout, stderr = result.stdout, result.stderr
            receipt["gdb_exit_code"] = result.returncode
        except subprocess.TimeoutExpired as error:
            stdout, stderr = error.stdout or b"", error.stderr or b""
            receipt["gdb_timeout_seconds"] = args.timeout
            raise
        finally:
            if "stdout" in locals():
                (evidence / "registry.stdout.log").write_bytes(stdout)
                (evidence / "registry.stderr.log").write_bytes(stderr)
        if result.returncode:
            raise ValueError(f"GDB registry capture returned {result.returncode}")
        registry = json.loads((evidence / "registry.json").read_text(encoding="utf-8"))
        receipt["count"] = len(registry_names(registry))
        if sha256(binary) != receipt["binary_sha256"] or git_head(root) != receipt["git_head"]:
            raise ValueError("binary or Git HEAD changed during registry capture")
        receipt.update(complete=True, registry_sha256=sha256(evidence / "registry.json"))
    except Exception as error:
        receipt["error"] = f"{type(error).__name__}: {error}"
    write_json(evidence / "capture.json", receipt)
    print(json.dumps(receipt))
    return 0 if receipt["complete"] else 1


def reconcile_run(args: argparse.Namespace) -> int:
    evidence = args.evidence.resolve(strict=True)
    # Never overwrite a failed attempt. A subsequent run needs new evidence.
    for name in ("LastTest.log", "cases.json", "reconciliation.json"):
        if (evidence / name).exists():
            raise ValueError(f"evidence already exists: {evidence / name}")
    receipt = {"schema_version": 1, "stage": "reconcile", "complete": False,
               "ctest_exit_code": args.ctest_exit_code, "mode": args.mode,
               "collection_success_is_not_native_success": True}
    try:
        # Preserve bytes before parsing, pin checks or any possible rejection.
        with args.log.open("rb") as source, (evidence / "LastTest.log").open("xb") as copy:
            shutil.copyfileobj(source, copy)
        receipt.update(log_source=str(args.log.resolve()), log_sha256=sha256(evidence / "LastTest.log"))
        capture = json.loads((evidence / "capture.json").read_text(encoding="utf-8"))
        if capture.get("complete") is not True:
            raise ValueError("registry capture is incomplete")
        receipt["log_mtime_ns"] = args.log.stat().st_mtime_ns
        if receipt["log_mtime_ns"] < capture["collection_started_unix_ns"]:
            raise ValueError("CTest log predates registry capture")
        root, binary = Path(capture["root"]), Path(capture["binary"])
        if git_head(root) != capture["git_head"] or sha256(binary) != capture["binary_sha256"]:
            raise ValueError("binary or Git HEAD differs from registry capture")
        if sha256(evidence / "registry.json") != capture["registry_sha256"]:
            raise ValueError("captured registry bytes changed")
        registry = json.loads((evidence / "registry.json").read_text(encoding="utf-8"))
        raw = (evidence / "LastTest.log").read_bytes().decode("utf-8", errors="replace")
        output, result, command = ctest_output(raw.replace("\r\n", "\n"), str(binary))
        cases = reconcile_output(registry, output, args.mode)
        if result == "Passed" and not cases["runner_policy_would_succeed"]:
            raise ValueError("CTest passed despite a failing native summary")
        if args.ctest_exit_code == 0 and result != "Passed":
            raise ValueError("CTest exit zero contradicts its failed test result")
        if git_head(root) != capture["git_head"] or sha256(binary) != capture["binary_sha256"]:
            raise ValueError("binary or Git HEAD changed during reconciliation")
        cases.update(git_head=capture["git_head"], binary_sha256=capture["binary_sha256"],
                     registry_sha256=capture["registry_sha256"], log_sha256=receipt["log_sha256"],
                     ctest_exit_code=args.ctest_exit_code, ctest_result=result, command=command,
                     collection_success_is_not_native_success=True)
        write_json(evidence / "cases.json", cases)
        receipt.update(complete=True, cases_sha256=sha256(evidence / "cases.json"),
                       counts=cases["counts"], git_head=capture["git_head"],
                       binary_sha256=capture["binary_sha256"])
    except Exception as error:
        receipt["error"] = f"{type(error).__name__}: {error}"
    write_json(evidence / "reconciliation.json", receipt)
    print(json.dumps(receipt))
    return 0 if receipt["complete"] else 1


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    stages = parser.add_subparsers(dest="stage", required=True)
    capture = stages.add_parser("registry", help="capture actual registrations without running tests")
    capture.add_argument("--binary", type=Path, required=True)
    capture.add_argument("--root", type=Path, required=True)
    capture.add_argument("--output", type=Path, required=True)
    capture.add_argument("--gdb", default="gdb")
    capture.add_argument("--timeout", type=int, choices=range(1, 241), default=30, metavar="SECONDS")
    capture.set_defaults(operation=capture_registry)
    reconcile = stages.add_parser("reconcile", help="retain and reconcile a complete native CTest log")
    reconcile.add_argument("--evidence", type=Path, required=True)
    reconcile.add_argument("--log", type=Path, required=True)
    reconcile.add_argument("--ctest-exit-code", type=int, choices=range(256), required=True, metavar="STATUS")
    reconcile.add_argument("--mode", choices=("default", "strict"), default="default")
    reconcile.set_defaults(operation=reconcile_run)
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    try:
        return args.operation(args)
    except (OSError, ValueError) as error:
        print(f"native evidence: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
