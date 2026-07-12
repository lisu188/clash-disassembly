"""Baseline full-DB regen (#0): decompile ALL functions to one C file, no names
applied. Validates the whole export path and measures how many of the 5 original
#error failures Hex-Rays 9.0 now resolves. Writes to scratch (never the repo)."""
import ida_auto, ida_hexrays, idautils, ida_pro, re

OUT = r"C:\Users\andrz\AppData\Local\Temp\claude\C--Users-andrz-git-clash-disassembly\d39f28bf-ad2c-497f-ab63-cd555e5653d7\scratchpad\clash_regen_baseline.c"
LOG = r"C:\Users\andrz\AppData\Local\Temp\claude\C--Users-andrz-git-clash-disassembly\d39f28bf-ad2c-497f-ab63-cd555e5653d7\scratchpad\export_all_result.txt"

def main():
    ida_auto.auto_wait()
    log = open(LOG, "w", encoding="utf-8")
    ok = ida_hexrays.init_hexrays_plugin()
    total = sum(1 for _ in idautils.Functions())
    log.write("hexrays=%s total_functions=%d\n" % (ok, total)); log.flush()
    try:
        flags = ida_hexrays.VDRUN_NEWFILE | ida_hexrays.VDRUN_SILENT | ida_hexrays.VDRUN_MAYSTOP
    except AttributeError:
        flags = 0
    res = ida_hexrays.decompile_many(OUT, None, flags)   # None = all functions
    log.write("decompile_many(all) returned: %s\n" % res); log.flush()
    try:
        txt = open(OUT, "r", encoding="utf-8", errors="replace").read()
        markers = len(re.findall(r'(?m)^//----- \([0-9A-Fa-f]+\) -', txt))
        errors = len(re.findall(r'(?m)^#error', txt))
        log.write("output markers: %d\n" % markers)
        log.write("output #error count: %d\n" % errors)
        log.write("output bytes: %d\n" % len(txt))
        for ln in txt.splitlines():
            if ln.startswith("#error"):
                log.write("REMAINING_ERROR: %s\n" % ln)
    except Exception as e:
        log.write("readback error: %r\n" % e)
    log.close()
    ida_pro.qexit(0)

main()
