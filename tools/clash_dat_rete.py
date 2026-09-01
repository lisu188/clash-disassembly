#!/usr/bin/env python3
"""Typed CLIPS 6.00 RETE recovery for the retail CLASH.DAT image."""
from __future__ import annotations

from dataclasses import asdict, dataclass
from pathlib import Path
import struct

JOIN_FLAG_MASK = 0x3FFF
FACT_PATTERN_RECORD_SIZE = 32
OBJECT_ALPHA_RECORD_SIZE = 28
OBJECT_PATTERN_RECORD_SIZE = 32


@dataclass(frozen=True)
class JoinNode:
    index: int
    first_join: bool
    logical_join: bool
    join_from_the_right: bool
    pattern_is_negated: bool
    rhs_type: int
    depth: int
    network_test: int
    right_side_entry_structure: int
    next_level: int
    last_level: int
    right_drive_node: int
    right_match_node: int
    rule_to_activate: int
    raw_flags: int
    unused_flag_bits: int

    def as_json(self) -> dict:
        return asdict(self)


@dataclass(frozen=True)
class FactPatternNode:
    index: int
    entry_join: int
    singlefield_node: bool
    multifield_node: bool
    stop_node: bool
    begin_slot: bool
    end_slot: bool
    which_slot: int
    which_field: int
    leave_fields: int
    network_test: int
    next_level: int
    last_level: int
    left_node: int
    right_node: int
    template: str | None = None

    def as_json(self) -> dict:
        return asdict(self)


@dataclass(frozen=True)
class ObjectAlphaNode:
    index: int
    entry_join: int
    raw_header_flags: int
    class_bitmap: int
    slot_bitmap: int
    pattern_node: int
    next_alpha: int
    next_terminal: int

    def as_json(self) -> dict:
        return asdict(self)


@dataclass(frozen=True)
class ObjectPatternNode:
    index: int
    multifield_node: bool
    end_slot: bool
    which_field: int
    leave_fields: int
    slot_name_id: int
    network_test: int
    next_level: int
    last_level: int
    left_node: int
    right_node: int
    alpha_node: int
    raw_flags: int

    def as_json(self) -> dict:
        return asdict(self)


def _section(ir: dict, name: str, kind: str = "data") -> dict:
    key = "data_sections" if kind == "data" else "storage_sections"
    for item in ir[key]:
        if item["name"] == name:
            return item
    raise KeyError(f"missing {kind} section {name!r}")


def decode_join(item: dict) -> JoinNode:
    raw = item["raw"]
    if len(raw) != 8:
        raise ValueError(f"join {item['index']} has {len(raw)} dwords, expected 8")
    flags = raw[0] & 0xFFFFFFFF
    return JoinNode(
        index=item["index"],
        first_join=bool(flags & 0x1),
        logical_join=bool(flags & 0x2),
        join_from_the_right=bool(flags & 0x4),
        pattern_is_negated=bool(flags & 0x8),
        rhs_type=(flags >> 4) & 0x7,
        depth=(flags >> 7) & 0x7F,
        network_test=raw[1],
        right_side_entry_structure=raw[2],
        next_level=raw[3],
        last_level=raw[4],
        right_drive_node=raw[5],
        right_match_node=raw[6],
        rule_to_activate=raw[7],
        raw_flags=flags,
        unused_flag_bits=flags & ~JOIN_FLAG_MASK,
    )


def decode_joins(ir: dict) -> list[JoinNode]:
    return [decode_join(item) for item in ir["joins"]]


def _fact_pattern_count(data: bytes, ir: dict) -> int:
    storage = _section(ir, "facts", "storage")
    if storage["size"] != 4:
        raise ValueError(f"unexpected facts storage size {storage['size']}")
    return struct.unpack_from("<i", data, storage["payload"])[0]


def _template_roots(ir: dict) -> dict[str, int]:
    result = {}
    for item in ir["templates"]:
        raw = item["raw"]
        if len(raw) != 6:
            raise ValueError("deftemplate record is not the expected 24-byte form")
        result[item["name"]] = raw[5]
    return result


def decode_fact_patterns(path: Path, ir: dict) -> list[FactPatternNode]:
    data = path.read_bytes()
    count = _fact_pattern_count(data, ir)
    section = _section(ir, "facts")
    if section["size"] != count * FACT_PATTERN_RECORD_SIZE:
        raise ValueError(
            f"facts section size {section['size']} != {count} * {FACT_PATTERN_RECORD_SIZE}"
        )

    raw_nodes = []
    for index in range(count):
        raw = struct.unpack_from(
            "<8i", data, section["payload"] + index * FACT_PATTERN_RECORD_SIZE
        )
        header_flags = raw[1] & 0xFFFFFFFF
        field_flags = raw[2] & 0xFFFFFFFF
        raw_nodes.append(
            FactPatternNode(
                index=index,
                entry_join=raw[0],
                singlefield_node=bool(header_flags & 0x01),
                multifield_node=bool(header_flags & 0x02),
                stop_node=bool(header_flags & 0x04),
                begin_slot=bool(header_flags & 0x40),
                end_slot=bool(header_flags & 0x80),
                which_slot=field_flags & 0xFF,
                which_field=(field_flags >> 8) & 0xFF,
                leave_fields=(field_flags >> 16) & 0xFF,
                network_test=raw[3],
                next_level=raw[4],
                last_level=raw[5],
                left_node=raw[6],
                right_node=raw[7],
            )
        )

    owners: dict[int, str] = {}
    by_index = {item.index: item for item in raw_nodes}
    for template, root in _template_roots(ir).items():
        if root == -1:
            continue
        stack = [root]
        seen: set[int] = set()
        while stack:
            current = stack.pop()
            if current == -1 or current in seen:
                continue
            if current not in by_index:
                raise ValueError(f"template {template} points outside fact network: {current}")
            seen.add(current)
            prior = owners.get(current)
            if prior is not None and prior != template:
                raise ValueError(f"fact node {current} belongs to both {prior} and {template}")
            owners[current] = template
            node = by_index[current]
            if node.next_level != -1:
                stack.append(node.next_level)
            if node.right_node != -1:
                stack.append(node.right_node)

    if len(owners) != count:
        missing = sorted(set(by_index) - set(owners))
        raise ValueError(f"{len(missing)} fact nodes are not reachable from a deftemplate: {missing}")

    return [
        FactPatternNode(**{**asdict(item), "template": owners[item.index]})
        for item in raw_nodes
    ]


def _object_counts(data: bytes, ir: dict) -> tuple[int, int]:
    storage = _section(ir, "object patterns", "storage")
    if storage["size"] != 8:
        raise ValueError(f"unexpected object-pattern storage size {storage['size']}")
    return struct.unpack_from("<2i", data, storage["payload"])


def decode_object_patterns(path: Path, ir: dict) -> tuple[list[ObjectAlphaNode], list[ObjectPatternNode]]:
    data = path.read_bytes()
    alpha_count, pattern_count = _object_counts(data, ir)
    section = _section(ir, "object patterns")
    expected = alpha_count * OBJECT_ALPHA_RECORD_SIZE + pattern_count * OBJECT_PATTERN_RECORD_SIZE
    if section["size"] != expected:
        raise ValueError(f"object-pattern section size {section['size']} != expected {expected}")

    offset = section["payload"]
    alphas = []
    for index in range(alpha_count):
        raw = struct.unpack_from("<7i", data, offset + index * OBJECT_ALPHA_RECORD_SIZE)
        alphas.append(
            ObjectAlphaNode(
                index=index,
                entry_join=raw[0],
                raw_header_flags=raw[1] & 0xFFFFFFFF,
                class_bitmap=raw[2],
                slot_bitmap=raw[3],
                pattern_node=raw[4],
                next_alpha=raw[5],
                next_terminal=raw[6],
            )
        )

    offset += alpha_count * OBJECT_ALPHA_RECORD_SIZE
    patterns = []
    for index in range(pattern_count):
        raw = struct.unpack_from("<8i", data, offset + index * OBJECT_PATTERN_RECORD_SIZE)
        flags = raw[0] & 0xFFFFFFFF
        patterns.append(
            ObjectPatternNode(
                index=index,
                multifield_node=bool(flags & 0x1),
                end_slot=bool(flags & 0x2),
                which_field=(flags >> 2) & 0xFF,
                leave_fields=(flags >> 10) & 0xFF,
                slot_name_id=raw[1],
                network_test=raw[2],
                next_level=raw[3],
                last_level=raw[4],
                left_node=raw[5],
                right_node=raw[6],
                alpha_node=raw[7],
                raw_flags=flags,
            )
        )
    return alphas, patterns


def _walk_right_match(entry_join: int, joins: list[JoinNode]) -> list[int]:
    result = []
    seen: set[int] = set()
    current = entry_join
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in rightMatchNode chain at join {current}")
        if not 0 <= current < len(joins):
            raise ValueError(f"rightMatchNode chain points outside join array: {current}")
        seen.add(current)
        result.append(current)
        current = joins[current].right_match_node
    return result


def map_join_rhs(
    joins: list[JoinNode],
    fact_patterns: list[FactPatternNode],
    object_alphas: list[ObjectAlphaNode],
) -> dict[int, dict]:
    owners: dict[int, dict] = {}

    for pattern in fact_patterns:
        for join_index in _walk_right_match(pattern.entry_join, joins):
            owner = {
                "kind": "fact",
                "pattern_node": pattern.index,
                "template": pattern.template,
                "which_slot": pattern.which_slot,
                "which_field": pattern.which_field,
                "stop_node": pattern.stop_node,
            }
            if join_index in owners and owners[join_index] != owner:
                raise ValueError(f"join {join_index} has multiple RHS pattern owners")
            owners[join_index] = owner

    for alpha in object_alphas:
        for join_index in _walk_right_match(alpha.entry_join, joins):
            owner = {
                "kind": "object",
                "alpha_node": alpha.index,
                "pattern_node": alpha.pattern_node,
                "class_bitmap": alpha.class_bitmap,
                "slot_bitmap": alpha.slot_bitmap,
            }
            if join_index in owners and owners[join_index] != owner:
                raise ValueError(f"join {join_index} has multiple RHS pattern owners")
            owners[join_index] = owner

    return owners


def trace_rule_join_path(rule: dict, joins: list[JoinNode]) -> list[int]:
    current = rule["last_join"]
    reverse_path = []
    seen: set[int] = set()
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle tracing {rule['name']} at join {current}")
        if not 0 <= current < len(joins):
            raise ValueError(f"rule {rule['name']} points outside join array: {current}")
        seen.add(current)
        reverse_path.append(current)
        current = joins[current].last_level
    return list(reversed(reverse_path))


def rete_report(path: Path, ir: dict) -> dict:
    joins = decode_joins(ir)
    facts = decode_fact_patterns(path, ir)
    alphas, object_patterns = decode_object_patterns(path, ir)
    rhs = map_join_rhs(joins, facts, alphas)

    rules = []
    for rule in ir["rules"]:
        path_indices = trace_rule_join_path(rule, joins)
        rules.append(
            {
                "index": rule["index"],
                "name": rule["name"],
                "last_join": rule["last_join"],
                "join_path": [
                    {
                        **joins[index].as_json(),
                        "rhs": rhs.get(index),
                    }
                    for index in path_indices
                ],
            }
        )

    fact_owned = sum(1 for owner in rhs.values() if owner["kind"] == "fact")
    object_owned = sum(1 for owner in rhs.values() if owner["kind"] == "object")
    return {
        "join_count": len(joins),
        "fact_pattern_count": len(facts),
        "object_alpha_count": len(alphas),
        "object_pattern_count": len(object_patterns),
        "mapped_join_count": len(rhs),
        "fact_owned_join_count": fact_owned,
        "object_owned_join_count": object_owned,
        "joins": [{**item.as_json(), "rhs": rhs.get(item.index)} for item in joins],
        "fact_patterns": [item.as_json() for item in facts],
        "object_alphas": [item.as_json() for item in alphas],
        "object_patterns": [item.as_json() for item in object_patterns],
        "rules": rules,
    }


def _dot_escape(value: str) -> str:
    return value.replace("\\", "\\\\").replace('"', '\\"')


def render_rete_dot(report: dict) -> str:
    lines = [
        "digraph clash_rete {",
        "  rankdir=LR;",
        '  node [shape=box,fontname="monospace",fontsize=9];',
    ]

    for join in report["joins"]:
        owner = join.get("rhs")
        if owner is None:
            rhs = "unmapped"
        elif owner["kind"] == "fact":
            rhs = f"fact:{owner['template']}#fp{owner['pattern_node']}"
        else:
            rhs = f"object:alpha{owner['alpha_node']}/op{owner['pattern_node']}"
        neg = " NOT" if join["pattern_is_negated"] else ""
        label = _dot_escape(
            f"J{join['index']} d={join['depth']} rhs={join['rhs_type']}{neg}\\n"
            f"{rhs}\\ntest={join['network_test']}"
        )
        lines.append(f'  j{join["index"]} [label="{label}"];')
        if join["last_level"] != -1:
            lines.append(f'  j{join["last_level"]} -> j{join["index"]} [label="LHS"];')

    for rule in report["rules"]:
        rule_id = f"r{rule['index']}"
        lines.append(
            f'  {rule_id} [shape=ellipse,label="{_dot_escape(rule["name"])}"];'
        )
        lines.append(f'  j{rule["last_join"]} -> {rule_id} [label="activate"];')

    lines.append("}")
    return "\n".join(lines) + "\n"
