"""IDAPython: export per-function features for the CLIPS region (and whole DB) to
JSON: ea, size, basic-block count, #callees, #callers. Read-only; run on a copy."""
import json, ida_funcs, ida_gdl, idautils, ida_auto, idc

OUT = r"C:\Users\andrz\AppData\Local\Temp\claude\C--Users-andrz-git-clash-disassembly\d39f28bf-ad2c-497f-ab63-cd555e5653d7\scratchpad\dos_features.json"

def main():
    ida_auto.auto_wait()
    feats = {}
    for ea in idautils.Functions():
        f = ida_funcs.get_func(ea)
        if not f:
            continue
        size = f.end_ea - f.start_ea
        try:
            fc = ida_gdl.FlowChart(f)
            bb = fc.size
        except Exception:
            bb = 0
        callees = set()
        for item in idautils.FuncItems(ea):
            for xref in idautils.CodeRefsFrom(item, 0):
                tf = ida_funcs.get_func(xref)
                if tf and tf.start_ea != f.start_ea:
                    callees.add(tf.start_ea)
        ncallers = len(set(idautils.CodeRefsTo(ea, 0)))
        feats["0x%X" % ea] = {"size": size, "bb": bb,
                               "ncallees": len(callees), "ncallers": ncallers}
    json.dump(feats, open(OUT, "w"))
    print("exported features for", len(feats), "functions")
    idc.qexit(0)

main()
