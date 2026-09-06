#!/usr/bin/env python3
"""Source-like LHS reconstruction from the CLASH.DAT RETE network."""
from __future__ import annotations

from dataclasses import asdict, dataclass
from pathlib import Path

from clash_dat_classes import decode_class_bitmap, decode_slot_bitmap, parse_defclass
from clash_dat_primitives import decode_primitive
from clash_dat_rete import rete_report
from decompile_clash_dat import bitmap_int


@dataclass(frozen=True)
class RecoveredCondition:
    order: int
    join_index: int
    depth: int
    negated: bool
    kind: str
    pattern: str
    pattern_node: int
    alpha_tests: tuple[str, ...]
    join_test: str | None
    classes: tuple[str, ...] = ()
    tested_slots: tuple[str, ...] = ()
    alpha_test_indices: tuple[int, ...] = ()
    join_test_index: int = -1

    def as_json(self) -> dict:
        return asdict(self)


def _siblings(ir: dict, start: int) -> list[int]:
    result = []
    seen = set()
    current = start
    expressions = ir["expressions"]
    while current != -1 and current not in seen and 0 <= current < len(expressions):
        seen.add(current)
        result.append(current)
        current = expressions[current][3]
    return result


def _quote(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\r", "\\r") + '"'


def render_expression(ir: dict, index: int, class_report: dict | None = None) -> str:
    """Render one compiled expression using semantic primitive decoders where known."""
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
            if isinstance(blob, bytes):
                raw = blob.hex()
            elif isinstance(blob, dict):
                raw = blob.get("hex", str(blob))
            else:
                raw = str(blob)
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
            type_id, value, arg, _ = expressions[expr_index]
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
                if class_report is not None and 0 <= value < len(class_report["classes"]):
                    return class_report["classes"][value]["name"]
                return f"defclass#{value}"
            if type_id == 60:
                return f"?*{global_names[value]}*" if 0 <= value < len(global_names) else f"defglobal#{value}"
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

            decoded = decode_primitive(expressions[expr_index], ir, expr_index)
            if decoded is not None:
                semantic = decoded.semantic
                if class_report is not None and type_id == 47:
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

            if type_id in (58, 59):
                op = "handler-get" if type_id == 58 else "handler-put"
                return f"{op}({primitive(type_id, value)})"
            if args:
                return f"{primitive(type_id, value)}(" + ", ".join(node(item) for item in args) + ")"
            return primitive(type_id, value)
        finally:
            stack.remove(expr_index)

    return node(index)


def _pattern_test_indices(node_index: int, nodes: list[dict]) -> list[int]:
    by_index = {item["index"]: item for item in nodes}
    current = node_index
    reverse = []
    seen = set()
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in pattern last-level chain at {current}")
        if current not in by_index:
            raise ValueError(f"pattern last-level chain points outside node array: {current}")
        seen.add(current)
        node = by_index[current]
        if node["network_test"] != -1:
            reverse.append(node["network_test"])
        current = node["last_level"]
    return list(reversed(reverse))


def recover_rule_lhs(path: Path, ir: dict) -> dict:
    rete = rete_report(path, ir)
    classes = parse_defclass(path, ir)
    fact_nodes = rete["fact_patterns"]
    object_nodes = rete["object_patterns"]

    rules = []
    for rule in rete["rules"]:
        conditions: list[RecoveredCondition] = []
        for order, join in enumerate(rule["join_path"], start=1):
            rhs = join["rhs"]
            alpha_tests: list[str] = []
            alpha_test_indices: list[int] = []
            class_names: tuple[str, ...] = ()
            tested_slots: tuple[str, ...] = ()

            if rhs["kind"] == "fact":
                pattern = f"({rhs['template']} ...)"
                pattern_node = rhs["pattern_node"]
                for expr_index in _pattern_test_indices(pattern_node, fact_nodes):
                    alpha_test_indices.append(expr_index)
                    alpha_tests.append(render_expression(ir, expr_index, classes))
            else:
                class_bitmap = decode_class_bitmap(ir, rhs["class_bitmap"], classes)
                slot_bitmap = decode_slot_bitmap(ir, rhs["slot_bitmap"], classes)
                class_names = tuple(class_bitmap["names"])
                tested_slots = tuple(slot_bitmap["names"])
                class_form = class_names[0] if len(class_names) == 1 else "{" + "|".join(class_names) + "}"
                pattern = f"(object (is-a {class_form}) ...)"
                pattern_node = rhs["pattern_node"]
                if pattern_node != -1:
                    for expr_index in _pattern_test_indices(pattern_node, object_nodes):
                        alpha_test_indices.append(expr_index)
                        alpha_tests.append(render_expression(ir, expr_index, classes))

            join_test = None
            if join["network_test"] != -1:
                join_test = render_expression(ir, join["network_test"], classes)

            conditions.append(
                RecoveredCondition(
                    order=order,
                    join_index=join["index"],
                    depth=join["depth"],
                    negated=join["pattern_is_negated"],
                    kind=rhs["kind"],
                    pattern=pattern,
                    pattern_node=pattern_node,
                    alpha_tests=tuple(alpha_tests),
                    alpha_test_indices=tuple(alpha_test_indices),
                    join_test_index=join["network_test"],
                    join_test=join_test,
                    classes=class_names,
                    tested_slots=tested_slots,
                )
            )

        source_rule = ir["rules"][rule["index"]]
        rules.append(
            {
                "index": rule["index"],
                "name": rule["name"],
                "salience": source_rule["salience"],
                "dynamic_salience_expr": source_rule["dynamic_salience_expr"],
                "actions_expr": source_rule["actions_expr"],
                "last_join": rule["last_join"],
                "conditions": [item.as_json() for item in conditions],
            }
        )

    return {
        "rule_count": len(rules),
        "condition_occurrence_count": sum(len(item["conditions"]) for item in rules),
        "class_report": classes,
        "rules": rules,
    }


def render_rule(rule: dict, ir: dict, class_report: dict) -> str:
    lines = [f"(defrule {rule['name']}"]
    if rule["salience"] != 0:
        lines.append(f"  (declare (salience {rule['salience']}))")
    if rule["dynamic_salience_expr"] != -1:
        lines.append(
            "  ;;; dynamic-salience "
            + render_expression(ir, rule["dynamic_salience_expr"], class_report)
        )
    lines.append("  ;;; normalized source-like LHS recovered from RETE; `...` marks source fields/variable names not preserved by BSAVE")
    for condition in rule["conditions"]:
        form = condition["pattern"]
        if condition["negated"]:
            form = f"(not {form})"
        lines.append(f"  {form} ; J{condition['join_index']} depth={condition['depth']}")
        if condition["tested_slots"]:
            lines.append("    ;;; object slots referenced by alpha bitmap: " + ", ".join(condition["tested_slots"]))
        for alpha in condition["alpha_tests"]:
            lines.append("    ;;; alpha-test: " + alpha)
        if condition["join_test"] is not None:
            lines.append("    ;;; join-test: " + condition["join_test"])
    lines.append("  =>")
    lines.append(f"  ;;; RHS expression root {rule['actions_expr']} is reconstructed by tools/decompile_clash_dat.py")
    lines.append(")")
    return "\n".join(lines)


def render_recovered_lhs(report: dict, ir: dict) -> str:
    header = [
        ";;; CLASH.DAT normalized LHS recovery",
        ";;; Generated from the compiled CLIPS 6.00 RETE/fact/object pattern networks.",
        ";;; This is source-like evidence, not a claim that original variable names survived BSAVE.",
        f";;; rules={report['rule_count']} condition-occurrences={report['condition_occurrence_count']}",
        "",
    ]
    body = [render_rule(rule, ir, report["class_report"]) for rule in report["rules"]]
    return "\n\n".join(["\n".join(header)] + body) + "\n"
