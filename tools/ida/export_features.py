"""IDAPython: export deterministic per-function structural and literal features."""
import json
import os

import ida_auto
import ida_funcs
import ida_gdl
import ida_nalt
import ida_pro
import idautils
import idc


def get_output_path():
    argv = list(idc.ARGV)
    if len(argv) != 2:
        raise SystemExit("usage: export_features.py <output.json>")
    return os.path.abspath(argv[1])


def decode_string(ea):
    string_type = ida_nalt.get_str_type(ea)
    if string_type is None or string_type < 0:
        return None
    value = idc.get_strlit_contents(ea, -1, string_type)
    if value is None:
        return None
    if isinstance(value, bytes):
        try:
            return value.decode("utf-8")
        except UnicodeDecodeError:
            return value.decode("latin-1", errors="replace")
    return str(value)


def main():
    output_path = get_output_path()
    ida_auto.auto_wait()
    rows = []
    for ea in idautils.Functions():
        function = ida_funcs.get_func(ea)
        if not function:
            continue
        try:
            basic_blocks = ida_gdl.FlowChart(function).size
        except Exception:
            basic_blocks = 0
        callees = set()
        data_refs = set()
        literals = set()
        for item in idautils.FuncItems(ea):
            for target in idautils.CodeRefsFrom(item, 0):
                target_function = ida_funcs.get_func(target)
                if target_function and target_function.start_ea != function.start_ea:
                    callees.add(target_function.start_ea)
            for target in idautils.DataRefsFrom(item):
                data_refs.add(target)
                literal = decode_string(target)
                if literal:
                    literals.add(literal)
        callers = set()
        for source in idautils.CodeRefsTo(ea, 0):
            caller = ida_funcs.get_func(source)
            if caller and caller.start_ea != function.start_ea:
                callers.add(caller.start_ea)
        rows.append({
            "ea": "0x%X" % ea,
            "name": ida_funcs.get_func_name(ea),
            "size": function.end_ea - function.start_ea,
            "bb": basic_blocks,
            "callees": ["0x%X" % value for value in sorted(callees)],
            "callers": ["0x%X" % value for value in sorted(callers)],
            "data_refs": ["0x%X" % value for value in sorted(data_refs)],
            "literals": sorted(literals),
        })
    payload = {
        "schema": 1,
        "database": idc.get_idb_path(),
        "functions": rows,
    }
    with open(output_path, "w", encoding="utf-8") as output:
        json.dump(payload, output, indent=2, sort_keys=True)
        output.write("\n")
    print("exported features for %d functions to %s" % (len(rows), output_path))
    ida_pro.qexit(0)


try:
    main()
except BaseException as error:
    print("export_features failed: %r" % (error,))
    ida_pro.qexit(1)
