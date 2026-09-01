#!/usr/bin/env python3
"""Render packed CLIPS expressions back to legal source syntax.

CLIPS BSAVE preserves expression trees, but several parser special forms do not
round-trip through a generic `(function arg...)` printer. In particular `if`
stores its THEN/ELSE branches as `progn` nodes while textual CLIPS requires the
`then`/`else` keywords. This renderer keeps the generic expression recovery in
one place and allows context-specific primitive resolvers for handlers and rule
RHS actions.
"""
from __future__ import annotations

from collections.abc import Callable

from decompile_clash_dat import bitmap_int

PrimitiveResolver = Callable[[int, int, int, list[int], "SourceExpressionRenderer"], str | None]


class SourceExpressionRenderer:
    def __init__(self, ir: dict, primitive_resolver: PrimitiveResolver | None = None):
        self.ir = ir
        self.expressions = ir["expressions"]
        self.functions = ir["functions"]
        self.symbols = ir["symbols"]
        self.floats = ir["floats"]
        self.integers = ir["integers"]
        self.bitmaps = ir["bitmaps"]
        self.templates = [item["name"] for item in ir["templates"]]
        self.globals = [item["name"] for item in ir["globals"]]
        self.deffunctions = [item["name"] for item in ir["deffunctions"]]
        self.primitive_resolver = primitive_resolver
        self._stack: set[int] = set()

    def siblings(self, start: int) -> list[int]:
        result: list[int] = []
        seen: set[int] = set()
        current = start
        while current != -1:
            if current in seen:
                raise ValueError(f"cycle in expression sibling chain at {current}")
            if not 0 <= current < len(self.expressions):
                raise ValueError(f"expression sibling chain points outside array: {current}")
            seen.add(current)
            result.append(current)
            current = self.expressions[current][3]
        return result

    @staticmethod
    def quote(value: str) -> str:
        return '"' + value.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n").replace("\r", "\\r") + '"'

    def primitive_placeholder(self, type_id: int, value: int) -> str:
        decoded = bitmap_int(self.bitmaps, value)
        if decoded is not None:
            return f"?prim{type_id}_{decoded}"
        if 0 <= value < len(self.bitmaps):
            return f"?prim{type_id}_b{value}"
        return f"?prim{type_id}_{value}"

    def _progn_actions(self, expr_index: int) -> list[str]:
        type_id, value, arg, _next = self.expressions[expr_index]
        if type_id == 10 and 0 <= value < len(self.functions) and self.functions[value] == "progn":
            return [self.node(item) for item in self.siblings(arg)] if arg != -1 else []
        return [self.node(expr_index)]

    def _render_if(self, args: list[int]) -> str:
        if len(args) not in (2, 3):
            return "(if " + " ".join(self.node(item) for item in args) + ")"
        condition = self.node(args[0])
        then_actions = self._progn_actions(args[1])
        pieces = ["(if", condition, "then"] + then_actions
        if len(args) == 3:
            pieces += ["else"] + self._progn_actions(args[2])
        return " ".join(pieces) + ")"

    def node(self, index: int) -> str:
        if index == -1:
            return "nil"
        if not 0 <= index < len(self.expressions):
            return f"<bad-expr:{index}>"
        if index in self._stack:
            return f"<cycle:{index}>"
        self._stack.add(index)
        try:
            type_id, value, arg, _next = self.expressions[index]
            args = self.siblings(arg) if arg != -1 else []

            if self.primitive_resolver is not None:
                resolved = self.primitive_resolver(index, type_id, value, args, self)
                if resolved is not None:
                    return resolved

            if type_id == 0:
                return repr(self.floats[value]) if 0 <= value < len(self.floats) else f"<float:{value}>"
            if type_id == 1:
                return str(self.integers[value]) if 0 <= value < len(self.integers) else f"<integer:{value}>"
            if type_id == 2:
                return self.symbols[value] if 0 <= value < len(self.symbols) else f"<symbol:{value}>"
            if type_id == 3:
                return self.quote(self.symbols[value]) if 0 <= value < len(self.symbols) else f"<string:{value}>"
            if type_id == 8:
                return f"[{self.symbols[value]}]" if 0 <= value < len(self.symbols) else f"<instance-name:{value}>"
            if type_id == 10:
                name = self.functions[value] if 0 <= value < len(self.functions) else f"<function:{value}>"
                if name == "if":
                    return self._render_if(args)
                if name == "assert" and len(args) >= 2 and self.expressions[args[0]][0] == 35 and self.expressions[args[1]][0] == 34:
                    template_index = self.expressions[args[0]][1]
                    template_name = self.templates[template_index] if 0 <= template_index < len(self.templates) else f"template#{template_index}"
                    fields = [self.node(item) for item in self.siblings(self.expressions[args[1]][2])]
                    return "(assert (" + " ".join([template_name] + fields) + "))"
                return "(" + " ".join([name] + [self.node(item) for item in args]) + ")"
            if type_id == 12:
                name = self.deffunctions[value] if 0 <= value < len(self.deffunctions) else f"deffunction#{value}"
                return "(" + " ".join([name] + [self.node(item) for item in args]) + ")"
            if type_id == 13:
                name = self.symbols[value] if 0 <= value < len(self.symbols) else f"global#{value}"
                return f"?*{name}*"
            if type_id == 35:
                return self.templates[value] if 0 <= value < len(self.templates) else f"<deftemplate:{value}>"
            if type_id == 57:
                return f"<defclass:{value}>"
            if type_id == 60:
                return f"?*{self.globals[value]}*" if 0 <= value < len(self.globals) else f"<defglobal:{value}>"
            if type_id == 65:
                decoded = bitmap_int(self.bitmaps, value)
                return f"?p{decoded}" if decoded is not None else self.primitive_placeholder(type_id, value)
            if type_id == 66:
                decoded = bitmap_int(self.bitmaps, value)
                return f"$?p{decoded}" if decoded is not None else self.primitive_placeholder(type_id, value)
            if type_id == 67:
                if args and self.expressions[args[0]][0] == 2:
                    symbol_index = self.expressions[args[0]][1]
                    if 0 <= symbol_index < len(self.symbols):
                        return "?" + self.symbols[symbol_index]
                return self.primitive_placeholder(type_id, value)
            if type_id == 68:
                decoded = bitmap_int(self.bitmaps, value)
                target = f"?local{decoded}" if decoded is not None else self.primitive_placeholder(type_id, value)
                return "(bind " + " ".join([target] + [self.node(item) for item in args]) + ")"
            if type_id == 34:
                return "(fields " + " ".join(self.node(item) for item in args) + ")"

            if args:
                return "(prim-" + str(type_id) + ":" + str(value) + " " + " ".join(self.node(item) for item in args) + ")"
            return self.primitive_placeholder(type_id, value)
        finally:
            self._stack.remove(index)

    def action_list(self, root: int) -> list[str]:
        if root == -1:
            return []
        type_id, value, arg, _next = self.expressions[root]
        if type_id == 10 and 0 <= value < len(self.functions) and self.functions[value] == "progn":
            return [self.node(item) for item in self.siblings(arg)] if arg != -1 else []
        return [self.node(root)]
