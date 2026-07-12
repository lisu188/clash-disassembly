"""Seed a {ea -> name} map into an IDA database by integer address (headless).
Usage: idat.exe -A -S"seed_names.py <map.json> <report.json>" -Llog db.i64

map.json: [{"ea":"0x10464","name":"main"}, ...]  (ea hex string or int)
Reports applied/skipped/collisions/unresolved and re-suffixes collisions with
the hex address (mirrors tools/apply_sub_renames.py policy). Saves the DB."""
import ida_auto, ida_funcs, ida_name, idc, ida_pro, ida_idaapi
import json, sys

def get_args():
    # IDA passes script args after the script name in idc.ARGV
    argv = idc.ARGV
    if len(argv) >= 3:
        return argv[1], argv[2]
    return (r"C:\Clash\work\dos_seed_names.json",
            r"C:\Clash\work\seed_report.json")

def main():
    map_path, report_path = get_args()
    ida_auto.auto_wait()
    rows = json.load(open(map_path, encoding="utf-8"))
    applied = []; skipped = []; collisions = []; unresolved = []
    for r in rows:
        ea = r["ea"]
        ea = int(ea, 16) if isinstance(ea, str) else int(ea)
        name = r["name"]
        f = ida_funcs.get_func(ea)
        if not f:
            unresolved.append({"ea": hex(ea), "name": name, "why": "no function"})
            continue
        if f.start_ea != ea:
            unresolved.append({"ea": hex(ea), "name": name,
                               "why": "ea not func start (start=%s)" % hex(f.start_ea)})
            continue
        cur = ida_funcs.get_func_name(ea)
        if cur == name:
            skipped.append({"ea": hex(ea), "name": name, "why": "already named"})
            continue
        # SN_CHECK validates identifier + uniqueness; on failure suffix with addr
        if idc.set_name(ea, name, ida_name.SN_CHECK | ida_name.SN_NOWARN):
            applied.append({"ea": hex(ea), "name": name})
        else:
            alt = "%s_%X" % (name, ea)
            if idc.set_name(ea, alt, ida_name.SN_CHECK | ida_name.SN_NOWARN):
                collisions.append({"ea": hex(ea), "wanted": name, "used": alt})
            else:
                # last resort force
                idc.set_name(ea, alt, ida_name.SN_FORCE | ida_name.SN_NOWARN)
                collisions.append({"ea": hex(ea), "wanted": name, "used": alt, "forced": True})
    rep = dict(applied=len(applied), skipped=len(skipped),
               collisions=collisions, unresolved=unresolved)
    json.dump(rep, open(report_path, "w"), indent=1)
    # persist DB
    idc.save_database(idc.get_idb_path(), 0)
    print("SEED: applied=%d skipped=%d collisions=%d unresolved=%d" %
          (len(applied), len(skipped), len(collisions), len(unresolved)))
    ida_pro.qexit(0 if not unresolved else 2)

main()
