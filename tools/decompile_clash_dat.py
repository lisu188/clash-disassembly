#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import struct
from collections import Counter
from pathlib import Path

HEADER = b"\x01\x02\x03\x04CLIPS\x00"
SECTION_COUNT = 11
EXPR_SIZE = 14
RULE_RECORD_SIZE = 44
JOIN_RECORD_SIZE = 32


def cstr(blob: bytes) -> str:
    return blob.split(b"\0", 1)[0].decode("latin1")


def read_section(buf: bytes, offset: int) -> tuple[str, int, int, int]:
    name = cstr(buf[offset : offset + 20])
    size = struct.unpack_from("<I", buf, offset + 20)[0]
    payload = offset + 24
    return name, size, payload, payload + size


def split_cstrings(blob: bytes) -> list[str]:
    return [item.decode("latin1") for item in blob.split(b"\0") if item]


def parse_bsave(path: Path) -> dict:
    data = path.read_bytes()
    if not data.startswith(HEADER):
        raise ValueError("not a CLIPS binary image")

    offset = len(HEADER)
    version_end = data.index(b"\0", offset)
    version = data[offset:version_end].decode("latin1")
    offset = version_end + 1

    function_count, function_bytes = struct.unpack_from("<II", data, offset)
    offset += 8
    functions = split_cstrings(data[offset : offset + function_bytes])
    offset += function_bytes

    symbol_count, symbol_bytes = struct.unpack_from("<II", data, offset)
    offset += 8
    symbols = split_cstrings(data[offset : offset + symbol_bytes])
    offset += symbol_bytes

    float_count = struct.unpack_from("<I", data, offset)[0]
    offset += 4
    floats = list(struct.unpack_from("<" + "d" * float_count, data, offset))
    offset += 8 * float_count

    integer_count = struct.unpack_from("<I", data, offset)[0]
    offset += 4
    integers = list(struct.unpack_from("<" + "i" * integer_count, data, offset))
    offset += 4 * integer_count

    bitmap_count, bitmap_bytes = struct.unpack_from("<II", data, offset)
    offset += 8
    bitmap_blob = data[offset : offset + bitmap_bytes]
    offset += bitmap_bytes
    bitmaps = []
    bitmap_offset = 0
    for _ in range(bitmap_count):
        size = bitmap_blob[bitmap_offset]
        bitmap_offset += 1
        bitmaps.append(bitmap_blob[bitmap_offset : bitmap_offset + size])
        bitmap_offset += size
    if bitmap_offset != bitmap_bytes:
        raise ValueError("bitmap table does not consume its declared byte count")

    expression_count = struct.unpack_from("<I", data, offset)[0]
    offset += 4

    storage_sections = []
    for _ in range(SECTION_COUNT):
        name, size, payload, end = read_section(data, offset)
        storage_sections.append({"offset": offset, "name": name, "size": size, "payload": payload, "end": end})
        offset = end

    if data[offset : offset + len(HEADER)] != HEADER:
        raise ValueError("missing CLIPS separator before expression table")
    offset += 20

    expression_start = offset
    expressions = [struct.unpack_from("<Hiii", data, expression_start + i * EXPR_SIZE) for i in range(expression_count)]
    offset = expression_start + expression_count * EXPR_SIZE

    constraint_bytes = data[offset : offset + 4]
    offset += 4

    data_sections = []
    for _ in range(SECTION_COUNT):
        name, size, payload, end = read_section(data, offset)
        data_sections.append({"offset": offset, "name": name, "size": size, "payload": payload, "end": end})
        offset = end

    if data[offset : offset + len(HEADER)] != HEADER:
        raise ValueError("missing trailing CLIPS separator")

    storage_by_name = {item["name"]: item for item in storage_sections}
    data_by_name = {item["name"]: item for item in data_sections}

    module_count, rule_count, join_count = struct.unpack_from("<3i", data, storage_by_name["defrule"]["payload"])
    rule_payload = data_by_name["defrule"]["payload"]
    rule_records_start = rule_payload + 12
    rules = []
    for index in range(rule_count):
        values = struct.unpack_from("<11i", data, rule_records_start + index * RULE_RECORD_SIZE)
        rules.append(
            {
                "index": index,
                "name_symbol": values[0],
                "name": symbols[values[0]],
                "module": values[1],
                "next": values[2],
                "salience": values[3],
                "local_var_count": values[4],
                "complexity_flags": values[5],
                "dynamic_salience_expr": values[6],
                "actions_expr": values[7],
                "logical_join": values[8],
                "last_join": values[9],
                "disjunct": values[10],
            }
        )

    join_records_start = rule_records_start + rule_count * RULE_RECORD_SIZE
    joins = []
    for index in range(join_count):
        values = struct.unpack_from("<8i", data, join_records_start + index * JOIN_RECORD_SIZE)
        joins.append({"index": index, "raw": list(values)})

    template_count = struct.unpack_from("<3i", data, storage_by_name["deftemplate"]["payload"])[0]
    template_payload = data_by_name["deftemplate"]["payload"]
    templates = []
    for index in range(template_count):
        values = struct.unpack_from("<6i", data, template_payload + 12 + index * 24)
        templates.append({"index": index, "name_symbol": values[0], "name": symbols[values[0]], "raw": list(values)})

    global_count = struct.unpack_from("<2i", data, storage_by_name["defglobal"]["payload"])[0]
    global_payload = data_by_name["defglobal"]["payload"]
    globals_ = []
    for index in range(global_count):
        values = struct.unpack_from("<4i", data, global_payload + 12 + index * 16)
        globals_.append(
            {
                "index": index,
                "name_symbol": values[0],
                "name": symbols[values[0]],
                "module": values[1],
                "next": values[2],
                "initial_expr": values[3],
            }
        )

    deffunction_count = struct.unpack_from("<2i", data, storage_by_name["deffunctions"]["payload"])[1]
    deffunction_payload = data_by_name["deffunctions"]["payload"]
    deffunctions = []
    for index in range(deffunction_count):
        values = struct.unpack_from("<8i", data, deffunction_payload + 12 + index * 32)
        deffunctions.append(
            {
                "index": index,
                "name_symbol": values[0],
                "name": symbols[values[0]],
                "module": values[1],
                "next": values[2],
                "min_params": values[3],
                "max_params": values[4],
                "local_var_count": values[5],
                "packed_type": values[6],
                "code_expr": values[7],
            }
        )

    return {
        "source": path.name,
        "file_size": len(data),
        "version": version,
        "function_count": function_count,
        "functions": functions,
        "symbol_count": symbol_count,
        "symbols": symbols,
        "floats": floats,
        "integers": integers,
        "bitmaps": bitmaps,
        "expression_count": expression_count,
        "expressions": expressions,
        "constraint_bytes": constraint_bytes.hex(),
        "storage_sections": storage_sections,
        "data_sections": data_sections,
        "rule_counts": {"modules": module_count, "rules": rule_count, "joins": join_count},
        "rules": rules,
        "joins": joins,
        "templates": templates,
        "globals": globals_,
        "deffunctions": deffunctions,
    }


def bitmap_int(bitmaps: list[bytes], index: int) -> int | None:
    if not 0 <= index < len(bitmaps) or len(bitmaps[index]) != 4:
        return None
    return struct.unpack("<i", bitmaps[index])[0]


def render_clips(ir: dict) -> str:
    functions = ir["functions"]
    symbols = ir["symbols"]
    floats = ir["floats"]
    integers = ir["integers"]
    bitmaps = ir["bitmaps"]
    expressions = ir["expressions"]
    templates = ir["templates"]
    globals_ = ir["globals"]
    deffunctions = ir["deffunctions"]
    rules = ir["rules"]

    template_names = [item["name"] for item in templates]
    global_names = [item["name"] for item in globals_]
    deffunction_names = [item["name"] for item in deffunctions]

    def siblings(start: int) -> list[int]:
        result = []
        seen = set()
        current = start
        while current != -1 and current not in seen and 0 <= current < len(expressions):
            seen.add(current)
            result.append(current)
            current = expressions[current][3]
        return result

    def quote(value: str) -> str:
        return '"' + value.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\r", "\\r") + '"'

    def primitive(type_id: int, value: int) -> str:
        decoded = bitmap_int(bitmaps, value)
        if decoded is not None:
            return f"?prim{type_id}_{decoded}"
        if 0 <= value < len(bitmaps):
            return f"?prim{type_id}_b{value}"
        return f"?prim{type_id}_{value}"

    def node(index: int) -> str:
        if index == -1:
            return "nil"
        if not 0 <= index < len(expressions):
            return f"<bad-expr:{index}>"
        type_id, value, arg, _ = expressions[index]
        args = siblings(arg) if arg != -1 else []

        if type_id == 0:
            return repr(floats[value]) if 0 <= value < len(floats) else f"<float:{value}>"
        if type_id == 1:
            return str(integers[value]) if 0 <= value < len(integers) else f"<integer:{value}>"
        if type_id == 2:
            return symbols[value] if 0 <= value < len(symbols) else f"<symbol:{value}>"
        if type_id == 3:
            return quote(symbols[value]) if 0 <= value < len(symbols) else f"<string:{value}>"
        if type_id == 8:
            return f"[{symbols[value]}]" if 0 <= value < len(symbols) else f"<instance-name:{value}>"
        if type_id == 10:
            name = functions[value] if 0 <= value < len(functions) else f"<function:{value}>"
            rendered = [node(item) for item in args]
            if name == "assert" and len(args) >= 2 and expressions[args[0]][0] == 35 and expressions[args[1]][0] == 34:
                template_index = expressions[args[0]][1]
                template_name = template_names[template_index] if 0 <= template_index < len(template_names) else f"template#{template_index}"
                fields = [node(item) for item in siblings(expressions[args[1]][2])]
                return "(assert (" + " ".join([template_name] + fields) + "))"
            return "(" + " ".join([name] + rendered) + ")"
        if type_id == 12:
            name = deffunction_names[value] if 0 <= value < len(deffunction_names) else f"deffunction#{value}"
            return "(" + " ".join([name] + [node(item) for item in args]) + ")"
        if type_id == 13:
            name = symbols[value] if 0 <= value < len(symbols) else f"global#{value}"
            return f"?*{name}*"
        if type_id == 35:
            return template_names[value] if 0 <= value < len(template_names) else f"<deftemplate:{value}>"
        if type_id == 57:
            return f"<defclass:{value}>"
        if type_id == 60:
            return f"?*{global_names[value]}*" if 0 <= value < len(global_names) else f"<defglobal:{value}>"
        if type_id == 65:
            decoded = bitmap_int(bitmaps, value)
            return f"?p{decoded}" if decoded is not None else primitive(type_id, value)
        if type_id == 66:
            decoded = bitmap_int(bitmaps, value)
            return f"$?p{decoded}" if decoded is not None else primitive(type_id, value)
        if type_id == 67:
            if args and expressions[args[0]][0] == 2:
                symbol_index = expressions[args[0]][1]
                if 0 <= symbol_index < len(symbols):
                    return "?" + symbols[symbol_index]
            return primitive(type_id, value)
        if type_id == 68:
            decoded = bitmap_int(bitmaps, value)
            target = f"?local{decoded}" if decoded is not None else primitive(type_id, value)
            return "(bind " + " ".join([target] + [node(item) for item in args]) + ")"
        if type_id == 34:
            return "(fields " + " ".join(node(item) for item in args) + ")"
        if args:
            return "(prim-" + str(type_id) + ":" + str(value) + " " + " ".join(node(item) for item in args) + ")"
        return primitive(type_id, value)

    def action_list(root: int) -> list[str]:
        if root == -1:
            return []
        type_id, value, arg, _ = expressions[root]
        if type_id == 10 and 0 <= value < len(functions) and functions[value] == "progn":
            return [node(item) for item in siblings(arg)]
        return [node(root)]

    lines = [
        ";;; Generated from CLASH.DAT by tools/decompile_clash_dat.py",
        f";;; CLIPS binary version: {ir['version']}",
        f";;; functions={ir['function_count']} symbols={ir['symbol_count']} expressions={ir['expression_count']}",
        f";;; rules={ir['rule_counts']['rules']} joins={ir['rule_counts']['joins']} deftemplates={len(templates)} deffunctions={len(deffunctions)} defglobals={len(globals_)}",
        ";;; RHS and deffunction expression trees are reconstructed from the binary expression table.",
        ";;; Original rule LHS syntax and original RHS pattern-variable names are not preserved by BSAVE.",
        ";;; ?prim* placeholders represent unresolved compiled CLIPS primitive accessors.",
        "",
        ";;; DEFGLOBALS",
        "(defglobal",
    ]
    for item in globals_:
        lines.append(f"  ?*{item['name']}* = {node(item['initial_expr'])}")
    lines.extend([")", "", ";;; DEFTEMPLATES"])
    for item in templates:
        lines.append(f";;; (deftemplate {item['name']})")
    lines.extend(["", ";;; DEFFUNCTIONS"])
    for item in deffunctions:
        params = " ".join(f"?p{i}" for i in range(1, item["max_params"] + 1))
        lines.append(f"(deffunction {item['name']} ({params})")
        for action in action_list(item["code_expr"]):
            lines.append("  " + action)
        lines.extend([")", ""])
    lines.append(";;; DEFRULES")
    for item in rules:
        lines.append(f"(defrule {item['name']}")
        lines.append(f"  (declare (salience {item['salience']}))")
        if item["dynamic_salience_expr"] != -1:
            lines.append(f"  ;;; dynamic-salience {node(item['dynamic_salience_expr'])}")
        lines.append(f"  ;;; LHS unavailable as original source; RETE terminal join #{item['last_join']}")
        lines.append("  =>")
        for action in action_list(item["actions_expr"]):
            lines.append("  " + action)
        lines.extend([")", ""])
    return "\n".join(lines)


def serializable_ir(ir: dict) -> dict:
    result = dict(ir)
    result["bitmaps"] = [{"index": i, "size": len(blob), "hex": blob.hex()} for i, blob in enumerate(ir["bitmaps"])]
    result["expressions"] = [
        {"index": i, "type": item[0], "value": item[1], "arg": item[2], "next": item[3]}
        for i, item in enumerate(ir["expressions"])
    ]
    result["expression_type_histogram"] = {str(key): value for key, value in sorted(Counter(item[0] for item in ir["expressions"]).items())}
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", nargs="?", default="CLASH.DAT")
    parser.add_argument("--clp", default=None)
    parser.add_argument("--json", default=None)
    args = parser.parse_args()

    source = Path(args.input)
    ir = parse_bsave(source)
    clp_path = Path(args.clp) if args.clp else source.with_name(source.stem + "_decompiled.clp")
    json_path = Path(args.json) if args.json else source.with_name(source.stem + "_decompiled_ir.json")
    clp_path.write_text(render_clips(ir), encoding="utf-8")
    json_path.write_text(json.dumps(serializable_ir(ir), ensure_ascii=False, indent=2), encoding="utf-8")
    print(
        f"{source}: version={ir['version']} functions={ir['function_count']} symbols={ir['symbol_count']} "
        f"expressions={ir['expression_count']} rules={ir['rule_counts']['rules']} joins={ir['rule_counts']['joins']} "
        f"deftemplates={len(ir['templates'])} deffunctions={len(ir['deffunctions'])} defglobals={len(ir['globals'])}"
    )
    print(clp_path)
    print(json_path)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
