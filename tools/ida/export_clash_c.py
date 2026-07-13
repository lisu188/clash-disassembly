"""IDAPython: export all functions to one C file and write a deterministic report."""
import json
import os
import re

import ida_auto
import ida_hexrays
import ida_pro
import idautils
import idc

MARKER_RE = re.compile(r"(?m)^//----- \(([0-9A-Fa-f]+)\) -+")
ERROR_RE = re.compile(r"(?m)^#error\s+(.+)$")


def parse_args():
    argv = list(idc.ARGV)
    if len(argv) != 3:
        raise SystemExit("usage: export_clash_c.py <output.c> <report.json>")
    return os.path.abspath(argv[1]), os.path.abspath(argv[2])


def associate_failures(text):
    markers = list(MARKER_RE.finditer(text))
    failures = []
    summary_errors = []
    for error in ERROR_RE.finditer(text):
        message = error.group(1).strip()
        if "there were" in message.lower() or "failures during decompilation" in message.lower():
            summary_errors.append(message)
            continue
        previous = [marker for marker in markers if marker.start() < error.start()]
        if previous:
            failures.append("0x%X" % int(previous[-1].group(1), 16))
        else:
            summary_errors.append(message)
    return sorted(set(failures)), summary_errors


def main():
    output_path, report_path = parse_args()
    ida_auto.auto_wait()
    if not ida_hexrays.init_hexrays_plugin():
        raise RuntimeError("Hex-Rays initialization failed")
    total = sum(1 for _ in idautils.Functions())
    try:
        flags = ida_hexrays.VDRUN_NEWFILE | ida_hexrays.VDRUN_SILENT | ida_hexrays.VDRUN_MAYSTOP
    except AttributeError:
        flags = 0
    result = ida_hexrays.decompile_many(output_path, None, flags)
    with open(output_path, "r", encoding="utf-8", errors="replace") as source:
        text = source.read()
    markers = ["0x%X" % int(value, 16) for value in MARKER_RE.findall(text)]
    failures, summary_errors = associate_failures(text)
    report = {
        "schema": 1,
        "database": idc.get_idb_path(),
        "output": output_path,
        "decompile_many_result": result,
        "database_function_count": total,
        "marker_count": len(markers),
        "marker_addresses": markers,
        "failed_functions": failures,
        "summary_errors": summary_errors,
        "output_bytes": len(text.encode("utf-8")),
    }
    with open(report_path, "w", encoding="utf-8") as output:
        json.dump(report, output, indent=2, sort_keys=True)
        output.write("\n")
    print("EXPORT markers=%d failures=%d summary_errors=%d" % (len(markers), len(failures), len(summary_errors)))
    ida_pro.qexit(0)


try:
    main()
except BaseException as error:
    print("export_clash_c failed: %r" % (error,))
    ida_pro.qexit(1)
