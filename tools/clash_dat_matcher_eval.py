#!/usr/bin/env python3
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Any

from clash_dat_primitives import decode_primitive


SUPPORTED_FACT_MATCHER_PRIMITIVE_TYPES = frozenset({24, 25, 28, 31, 33})


@dataclass(frozen=True)
class FactMatcherContext:
    fields: tuple[Any, ...]
    globals: dict[str, Any] = field(default_factory=dict)
    pattern_fields: dict[int, tuple[Any, ...]] = field(default_factory=dict)


def clips_truth(value: Any) -> bool:
    return value is not False and value != "FALSE"


def _args(ir: dict, start: int) -> list[int]:
    if start == -1:
        return []
    result: list[int] = []
    seen: set[int] = set()
    current = start
    expressions = ir["expressions"]
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in expression sibling chain at {current}")
        if not 0 <= current < len(expressions):
            raise ValueError(f"expression sibling chain points outside array: {current}")
        seen.add(current)
        result.append(current)
        current = expressions[current][3]
    return result


def _field_from_selector(fields: tuple[Any, ...], decoded: dict[str, Any]) -> Any:
    if int(decoded["which_slot"]) != 0:
        raise NotImplementedError("fact matcher oracle currently supports ordered slot 0 only")
    from_beginning = bool(decoded["from_beginning"])
    from_end = bool(decoded["from_end"])
    begin = int(decoded["begin_offset"])
    end = int(decoded["end_offset"])
    if from_beginning and from_end:
        stop = len(fields) - end
        if begin > stop:
            return tuple()
        return tuple(fields[begin:stop])
    if from_beginning:
        return fields[begin]
    if from_end:
        return fields[len(fields) - 1 - end]
    raise ValueError("invalid compiled fact selector with neither direction bit set")


def _field_at(fields: tuple[Any, ...], from_beginning: bool, offset: int) -> Any:
    return fields[offset] if from_beginning else fields[len(fields) - 1 - offset]


def _joined_fact_fields(context: FactMatcherContext, raw_pattern: int) -> tuple[Any, ...]:
    if raw_pattern in context.pattern_fields:
        return context.pattern_fields[raw_pattern]
    if raw_pattern + 1 in context.pattern_fields:
        return context.pattern_fields[raw_pattern + 1]
    raise KeyError(f"missing joined fact fields for pattern {raw_pattern}")


def _eval_function(name: str, values: list[Any]) -> Any:
    if name == "and":
        return all(clips_truth(value) for value in values)
    if name == "or":
        return any(clips_truth(value) for value in values)
    if name == "not":
        if len(values) != 1:
            raise ValueError("not expects one argument")
        return not clips_truth(values[0])
    if name in ("=", "eq"):
        if len(values) < 2:
            raise ValueError(f"{name} expects at least two arguments")
        return all(values[0] == value for value in values[1:])
    if name in ("<>", "neq"):
        if len(values) != 2:
            raise ValueError(f"{name} expects two arguments")
        return values[0] != values[1]
    if name == ">":
        return all(left > right for left, right in zip(values, values[1:]))
    if name == "<":
        return all(left < right for left, right in zip(values, values[1:]))
    if name == ">=":
        return all(left >= right for left, right in zip(values, values[1:]))
    if name == "<=":
        return all(left <= right for left, right in zip(values, values[1:]))
    if name == "+":
        return sum(values)
    if name == "*":
        result: Any = 1
        for value in values:
            result *= value
        return result
    if name == "-":
        if len(values) == 1:
            return -values[0]
        if not values:
            raise ValueError("- expects at least one argument")
        result = values[0]
        for value in values[1:]:
            result -= value
        return result
    if name == "/":
        if len(values) < 2:
            raise ValueError("/ expects at least two arguments")
        result = values[0]
        for value in values[1:]:
            result /= value
        return result
    raise NotImplementedError(f"compiled matcher function not supported by oracle: {name}")


def evaluate_expression(ir: dict, expression_index: int, context: FactMatcherContext) -> Any:
    if not 0 <= expression_index < len(ir["expressions"]):
        raise ValueError(f"expression index outside array: {expression_index}")
    type_id, value, arg, _next = ir["expressions"][expression_index]

    if type_id == 0:
        return ir["floats"][value]
    if type_id == 1:
        return ir["integers"][value]
    if type_id == 2:
        return ir["symbols"][value]
    if type_id == 3:
        return ir["symbols"][value]
    if type_id == 10:
        name = ir["functions"][value]
        return _eval_function(
            name,
            [evaluate_expression(ir, child, context) for child in _args(ir, arg)],
        )
    if type_id == 13:
        name = ir["symbols"][value]
        if name not in context.globals:
            raise KeyError(f"missing global value for {name}")
        return context.globals[name]
    if type_id == 60:
        name = ir["globals"][value]["name"]
        if name not in context.globals:
            raise KeyError(f"missing global value for {name}")
        return context.globals[name]

    decoded = decode_primitive(ir["expressions"][expression_index], ir, expression_index)
    if decoded is None:
        raise NotImplementedError(f"compiled matcher primitive type {type_id} is not decoded")

    fields = decoded.fields
    if type_id == 24:
        if int(fields["slot1"]) != 0 or int(fields["slot2"]) != 0:
            raise NotImplementedError("fact join oracle currently supports ordered slot 0 only")
        left = _field_at(
            context.fields,
            bool(fields["from_beginning1"]),
            int(fields["offset1"]),
        )
        previous = _joined_fact_fields(context, int(fields["pattern2"]))
        right = _field_at(
            previous,
            bool(fields["from_beginning2"]),
            int(fields["offset2"]),
        )
        passed = bool(fields["pass"])
        failed = bool(fields["fail"])
        if passed and not failed:
            return left == right
        if failed and not passed:
            return left != right
        raise NotImplementedError("FACT_JN_CMP2 pass/fail mode is not a simple equality test")

    if type_id == 25:
        if int(fields["which_slot"]) != 0:
            raise NotImplementedError("fact slot-length oracle supports ordered slot 0 only")
        length = len(context.fields)
        minimum = int(fields["min_length"])
        return length == minimum if bool(fields["exactly"]) else length >= minimum

    if type_id == 28:
        return _field_from_selector(context.fields, fields)

    if type_id == 31:
        order = int(fields["source_pattern_ordinal"])
        selected = context.pattern_fields.get(order)
        if selected is None:
            raise KeyError(f"missing FACT_JN_VAR3 fields for pattern {order}")
        return _field_from_selector(selected, fields)

    if type_id == 33:
        if int(fields["which_slot"]) != 0:
            raise NotImplementedError("fact constant oracle supports ordered slot 0 only")
        offset = int(fields["offset"])
        target = context.fields[offset] if bool(fields["from_beginning"]) else context.fields[len(context.fields) - 1 - offset]
        children = _args(ir, arg)
        if len(children) != 1:
            raise ValueError(f"FACT_PN_CONSTANT2 expects one argument, found {len(children)}")
        expected = evaluate_expression(ir, children[0], context)
        equal = target == expected
        return equal if bool(fields["test_for_equality"]) else not equal

    raise NotImplementedError(f"compiled matcher primitive not supported by fact oracle: {decoded.type_name}")


def evaluate_fact_condition(ir: dict, condition: dict, context: FactMatcherContext) -> bool:
    if condition["kind"] != "fact":
        raise ValueError("fact matcher oracle received a non-fact condition")
    tests = [int(index) for index in condition.get("alpha_test_indices", ())]
    join_test = int(condition.get("join_test_index", -1))
    if join_test != -1:
        tests.append(join_test)
    matched = all(clips_truth(evaluate_expression(ir, index, context)) for index in tests)
    return not matched if bool(condition.get("negated")) else matched
