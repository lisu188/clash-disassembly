"""IDAPython: seed a master map into a database copy and optionally fix GetToken."""
import json
import os

import ida_auto
import ida_funcs
import ida_name
import ida_pro
import idc

GETTOKEN_EA = 0xE1E30
GETTOKEN_PROTOTYPE = "void __cdecl GetToken(char *logicalName, void *theToken);"


def parse_args():
    argv = list(idc.ARGV)
    fix_gettoken = "--fix-dos-gettoken" in argv[1:]
    positional = [value for value in argv[1:] if value != "--fix-dos-gettoken"]
    if len(positional) != 2:
        raise SystemExit("usage: seed_names.py <map.json> <report.json> [--fix-dos-gettoken]")
    return os.path.abspath(positional[0]), os.path.abspath(positional[1]), fix_gettoken


def load_rows(path):
    with open(path, encoding="utf-8") as source:
        data = json.load(source)
    if isinstance(data, dict) and "rows" in data:
        data = data["rows"]
    if isinstance(data, dict):
        rows = []
        for ea, value in data.items():
            row = dict(value) if isinstance(value, dict) else {"name": value}
            row.setdefault("ea", ea)
            rows.append(row)
        return rows
    return data


def main():
    map_path, report_path, fix_gettoken = parse_args()
    ida_auto.auto_wait()
    applied = []
    skipped = []
    collisions = []
    unresolved = []
    for row in sorted(load_rows(map_path), key=lambda value: int(str(value["ea"]), 0)):
        ea = int(str(row["ea"]), 0)
        name = row["name"]
        function = ida_funcs.get_func(ea)
        if not function:
            unresolved.append({"ea": hex(ea), "name": name, "why": "no function"})
            continue
        if function.start_ea != ea:
            unresolved.append({"ea": hex(ea), "name": name, "why": "ea not function start", "start": hex(function.start_ea)})
            continue
        current = ida_funcs.get_func_name(ea)
        if current == name:
            skipped.append({"ea": hex(ea), "name": name, "why": "already named"})
            continue
        if idc.set_name(ea, name, ida_name.SN_CHECK | ida_name.SN_NOWARN):
            applied.append({"ea": hex(ea), "name": name, "used": name})
            continue
        alternate = "%s_%X" % (name, ea)
        forced = False
        if not idc.set_name(ea, alternate, ida_name.SN_CHECK | ida_name.SN_NOWARN):
            forced = True
            if not idc.set_name(ea, alternate, ida_name.SN_FORCE | ida_name.SN_NOWARN):
                unresolved.append({"ea": hex(ea), "name": name, "why": "rename failed", "attempted": alternate})
                continue
        collisions.append({"ea": hex(ea), "wanted": name, "used": alternate, "forced": forced})

    gettoken = {"requested": fix_gettoken, "ea": hex(GETTOKEN_EA), "prototype": GETTOKEN_PROTOTYPE, "applied": None}
    if fix_gettoken:
        gettoken["applied"] = bool(idc.SetType(GETTOKEN_EA, GETTOKEN_PROTOTYPE))
    report = {
        "schema": 1,
        "database": idc.get_idb_path(),
        "applied": applied,
        "skipped": skipped,
        "collisions": collisions,
        "unresolved": unresolved,
        "gettoken_fix": gettoken,
    }
    with open(report_path, "w", encoding="utf-8") as output:
        json.dump(report, output, indent=2, sort_keys=True)
        output.write("\n")
    idc.save_database(idc.get_idb_path(), 0)
    ok = not unresolved and (not fix_gettoken or gettoken["applied"])
    print("SEED applied=%d skipped=%d collisions=%d unresolved=%d gettoken=%s" % (
        len(applied), len(skipped), len(collisions), len(unresolved), gettoken["applied"]
    ))
    ida_pro.qexit(0 if ok else 2)


try:
    main()
except BaseException as error:
    print("seed_names failed: %r" % (error,))
    ida_pro.qexit(1)
