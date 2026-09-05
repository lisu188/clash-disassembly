#!/usr/bin/env python3
"""Recover CLIPS 6.00 defmessage-handler records and source-like bodies from CLASH.DAT.

The 28-byte bsave handler layout is grounded in the recovered
Class_BsaveWriteSlotRecords implementation and the CLIPS 6.x HANDLER structure:

    uint32 flags          # bit0=system, bits1..2=type
    int32  minParams      # includes implicit ?self
    int32  maxParams      # same as minParams, or -1 for wildcard
    int32  localVarCount
    int32  nameSymbol
    int32  classIndex
    int32  actionsExpr

Original parameter spellings are not retained by BSAVE.  The renderer therefore
uses stable ?p1..?pN / $?pN names while preserving exact arity and handler type.
"""
from __future__ import annotations

from dataclasses import asdict, dataclass
from pathlib import Path
import re

from clash_dat_classes import parse_defclass
from clash_dat_handler_slots import decode_handler_reference
from clash_dat_primitives import decode_primitive
from decompile_clash_dat import bitmap_int, parse_bsave

HANDLER_TYPES = ("around", "before", "primary", "after")


@dataclass(frozen=True)
class MessageHandlerRecord:
    index: int
    class_index: int
    class_name: str
    name_symbol: int
    name: str
    system: bool
    handler_type_id: int
    handler_type: str
    min_params: int
    max_params: int
    local_var_count: int
    actions_expr: int
    dispatch_order: int | None

    @property
    def explicit_min_params(self) -> int:
        return max(0, self.min_params - 1)

    @property
    def variadic(self) -> bool:
        return self.max_params == -1

    @property
    def explicit_max_params(self) -> int | None:
        return None if self.variadic else max(0, self.max_params - 1)

    def as_json(self) -> dict:
        result = asdict(self)
        result["explicit_min_params"] = self.explicit_min_params
        result["explicit_max_params"] = self.explicit_max_params
        result["variadic"] = self.variadic
        return result


def recover_message_handlers(path: Path, ir: dict) -> dict:
    classes = parse_defclass(path, ir)
    raw_handlers = classes["handlers"]
    handler_map = classes["handler_map"]
    class_records = classes["classes"]

    owners: dict[int, int] = {}
    dispatch: dict[int, int] = {}
    for cls in class_records:
        start = cls["handlers_index"]
        count = cls["handler_count"]
        if count == 0:
            if start not in (-1, 0):
                raise ValueError(f"class {cls['name']} has zero handlers but handlers_index={start}")
            continue
        if start < 0 or start + count > len(raw_handlers):
            raise ValueError(f"class {cls['name']} handler range is outside the bsave handler array")
        for local_index in range(count):
            global_index = start + local_index
            if global_index in owners:
                raise ValueError(f"handler {global_index} has multiple owning classes")
            owners[global_index] = cls["index"]

        # handlerOrderMap is stored per class and contains local handler indices.
        if start + count <= len(handler_map):
            for order, local_handler_index in enumerate(handler_map[start : start + count]):
                if 0 <= local_handler_index < count:
                    dispatch[start + local_handler_index] = order

    if len(owners) != len(raw_handlers):
        missing = sorted(set(range(len(raw_handlers))) - set(owners))
        raise ValueError(f"handlers not owned by a defclass: {missing}")

    result: list[MessageHandlerRecord] = []
    for index, raw in enumerate(raw_handlers):
        if len(raw) != 7:
            raise ValueError(f"handler {index} has {len(raw)} dwords, expected 7")
        flags, min_params, max_params, local_var_count, name_symbol, class_index, actions_expr = raw
        owner_index = owners[index]
        if class_index != owner_index:
            raise ValueError(
                f"handler {index} class index {class_index} != owning class range {owner_index}"
            )
        if not 0 <= class_index < len(class_records):
            raise ValueError(f"handler {index} references bad class index {class_index}")
        if not 0 <= name_symbol < len(ir["symbols"]):
            raise ValueError(f"handler {index} references bad name symbol {name_symbol}")
        handler_type_id = (flags >> 1) & 0x3
        if max_params != -1 and max_params != min_params:
            raise ValueError(
                f"handler {index} has unsupported min/max pair {min_params}/{max_params}; "
                "CLIPS handler dispatch expects exact or wildcard arity"
            )
        if min_params < 1:
            raise ValueError(f"handler {index} minParams={min_params} does not include implicit ?self")
        result.append(
            MessageHandlerRecord(
                index=index,
                class_index=class_index,
                class_name=class_records[class_index]["name"],
                name_symbol=name_symbol,
                name=ir["symbols"][name_symbol],
                system=bool(flags & 0x1),
                handler_type_id=handler_type_id,
                handler_type=HANDLER_TYPES[handler_type_id],
                min_params=min_params,
                max_params=max_params,
                local_var_count=local_var_count,
                actions_expr=actions_expr,
                dispatch_order=dispatch.get(index),
            )
        )

    return {
        "count": len(result),
        "system_count": sum(item.system for item in result),
        "user_count": sum(not item.system for item in result),
        "variadic_count": sum(item.variadic for item in result),
        "type_counts": {
            name: sum(item.handler_type == name for item in result)
            for name in HANDLER_TYPES
        },
        "class_counts": {
            cls["name"]: sum(item.class_index == cls["index"] for item in result)
            for cls in class_records
            if any(item.class_index == cls["index"] for item in result)
        },
        "handlers": [item.as_json() for item in result],
        "class_report": classes,
    }


def _siblings(ir: dict, start: int) -> list[int]:
    result: list[int] = []
    seen: set[int] = set()
    current = start
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in expression sibling chain at {current}")
        if not 0 <= current < len(ir["expressions"]):
            raise ValueError(f"expression sibling chain points outside array: {current}")
        seen.add(current)
        result.append(current)
        current = ir["expressions"][current][3]
    return result


def _quote(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\r", "\\r") + '"'


def render_handler_expression(ir: dict, index: int, class_report: dict) -> str:
    """Render one expression tree, including direct ?self:<slot> primitives."""
    expressions = ir["expressions"]
    functions = ir["functions"]
    symbols = ir["symbols"]
    floats = ir["floats"]
    integers = ir["integers"]
    bitmaps = ir["bitmaps"]
    template_names = [item["name"] for item in ir["templates"]]
    global_names = [item["name"] for item in ir["globals"]]
    deffunction_names = [item["name"] for item in ir["deffunctions"]]
    stack: set[int] = set()

    def primitive(type_id: int, value: int) -> str:
        decoded_int = bitmap_int(bitmaps, value)
        if decoded_int is not None:
            return f"prim{type_id}[{decoded_int}]"
        if 0 <= value < len(bitmaps):
            blob = bitmaps[value]
            raw = blob.hex() if isinstance(blob, bytes) else str(blob)
            return f"prim{type_id}[bitmap#{value}:{raw}]"
        return f"prim{type_id}[{value}]"

    def node(expr_index: int) -> str:
        if expr_index == -1:
            return "nil"
        if not 0 <= expr_index < len(expressions):
            return f"<bad-expr:{expr_index}>"
        if expr_index in stack:
            return f"<cycle:{expr_index}>"
        stack.add(expr_index)
        try:
            type_id, value, arg, _next = expressions[expr_index]
            args = _siblings(ir, arg) if arg != -1 else []

            if type_id == 0:
                return repr(floats[value]) if 0 <= value < len(floats) else f"<float:{value}>"
            if type_id == 1:
                return str(integers[value]) if 0 <= value < len(integers) else f"<integer:{value}>"
            if type_id == 2:
                return symbols[value] if 0 <= value < len(symbols) else f"<symbol:{value}>"
            if type_id == 3:
                return _quote(symbols[value]) if 0 <= value < len(symbols) else f"<string:{value}>"
            if type_id == 8:
                return f"[{symbols[value]}]" if 0 <= value < len(symbols) else f"<instance-name:{value}>"
            if type_id == 10:
                name = functions[value] if 0 <= value < len(functions) else f"function#{value}"
                return "(" + " ".join([name] + [node(item) for item in args]) + ")"
            if type_id == 12:
                name = deffunction_names[value] if 0 <= value < len(deffunction_names) else f"deffunction#{value}"
                return "(" + " ".join([name] + [node(item) for item in args]) + ")"
            if type_id == 13:
                name = symbols[value] if 0 <= value < len(symbols) else f"global#{value}"
                return f"?*{name}*"
            if type_id == 35:
                return template_names[value] if 0 <= value < len(template_names) else f"deftemplate#{value}"
            if type_id == 57:
                if 0 <= value < len(class_report["classes"]):
                    return class_report["classes"][value]["name"]
                return f"defclass#{value}"
            if type_id == 60:
                return f"?*{global_names[value]}*" if 0 <= value < len(global_names) else f"defglobal#{value}"
            if type_id == 65:
                decoded = bitmap_int(bitmaps, value)
                if decoded == 0:
                    return "?self"
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
            if type_id in (58, 59):
                ref = decode_handler_reference(expr_index, expressions[expr_index], ir, class_report)
                if ref is None:
                    return primitive(type_id, value)
                if type_id == 58:
                    return ref.clips_target
                return "(bind " + " ".join([ref.clips_target] + [node(item) for item in args]) + ")"

            decoded = decode_primitive(expressions[expr_index], ir, expr_index)
            if decoded is not None:
                semantic = decoded.semantic
                if type_id == 47:
                    slot_id = int(decoded.fields["which_slot"])
                    slot_name = class_report["slot_name_by_id"].get(slot_id, f"system-slot#{slot_id}")
                    pattern = int(decoded.fields["which_pattern"])
                    if decoded.fields["object_address"]:
                        semantic = f"object[p{pattern}]"
                    elif decoded.fields["all_fields"]:
                        semantic = f"object[p{pattern}].{slot_name}"
                    else:
                        semantic = f"object[p{pattern}].{slot_name}[{decoded.fields['which_field']}]"
                if args:
                    semantic += " args=(" + ", ".join(node(item) for item in args) + ")"
                return semantic

            if args:
                return f"{primitive(type_id, value)}(" + ", ".join(node(item) for item in args) + ")"
            return primitive(type_id, value)
        finally:
            stack.remove(expr_index)

    return node(index)


def _parameter_list(handler: dict) -> list[str]:
    explicit_count = max(0, int(handler["min_params"]) - 1)
    result = [f"?p{i}" for i in range(1, explicit_count + 1)]
    if int(handler["max_params"]) == -1:
        result.append(f"$?p{explicit_count + 1}")
    return result


def render_handler(handler: dict, ir: dict, class_report: dict) -> str:
    params = " ".join(_parameter_list(handler))
    lines = [
        f"(defmessage-handler {handler['class_name']} {handler['name']} {handler['handler_type']} ({params})"
    ]
    if handler["system"]:
        lines.append("  ;;; system/implicit handler in BSAVE; source form normalized by recovery tool")
    lines.append(
        f"  ;;; bsave handler#{handler['index']} actions={handler['actions_expr']} "
        f"locals={handler['local_var_count']} dispatch-order={handler['dispatch_order']}"
    )
    root = int(handler["actions_expr"])
    if root == -1:
        lines.append("  ;;; no action expression")
    else:
        for expr_index in _siblings(ir, root):
            lines.append("  " + render_handler_expression(ir, expr_index, class_report))
    lines.append(")")
    return "\n".join(lines)


def render_message_handlers(report: dict, ir: dict) -> str:
    header = [
        ";;; DEFMESSAGE-HANDLERS",
        ";;; Handler class/name/type/arity/actions are recovered from the defclass BSAVE records.",
        ";;; Parameter spellings are synthetic because BSAVE preserves parameter positions, not source names.",
        f";;; handlers={report['count']} system={report['system_count']} user={report['user_count']} variadic={report['variadic_count']}",
        "",
    ]
    body = [render_handler(item, ir, report["class_report"]) for item in report["handlers"]]
    return "\n\n".join(["\n".join(header)] + body) + "\n"


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    report = recover_message_handlers(source, ir)
    print(render_message_handlers(report, ir))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
