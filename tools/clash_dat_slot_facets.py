#!/usr/bin/env python3
"""Recover source-level CLIPS defclass slot facets from retail CLASH.DAT.

The 24-byte BSAVE slot descriptor stores a compacted subset of the live CLIPS
slotDescriptor bitfield.  Recovered Class_BsaveWriteHandlerRecords /
Class_BloadRefreshHandlerRecord code proves the bit mapping, while the serialized
default expression/value and override-message symbol allow a source-equivalent
slot declaration to be emitted without claiming the original pretty-print form.
"""
from __future__ import annotations

from dataclasses import asdict, dataclass
import struct

from clash_dat_lhs import render_expression


@dataclass(frozen=True)
class SlotFacets:
    shared: bool
    multiple: bool
    composite: bool
    no_inherit: bool
    no_write: bool
    initialize_only: bool
    dynamic_default: bool
    no_default: bool
    reactive: bool
    public_visibility: bool
    create_read_accessor: bool
    create_write_accessor: bool

    def as_json(self) -> dict:
        return asdict(self)


def decode_slot_flags(flags: int) -> SlotFacets:
    """Decode the compact 12-bit CLIPS 6.00 BSAVE slot flag word.

    Live slotDescriptor.defaultSpecified and overrideMessageSpecified are not
    serialized as flags.  noDefault is moved from live bit 8 to BSAVE bit 7;
    reactive/public/create-accessor live bits 9..12 are compacted to bits 8..11.
    """
    flags &= 0xFFFFFFFF
    return SlotFacets(
        shared=bool(flags & (1 << 0)),
        multiple=bool(flags & (1 << 1)),
        composite=bool(flags & (1 << 2)),
        no_inherit=bool(flags & (1 << 3)),
        no_write=bool(flags & (1 << 4)),
        initialize_only=bool(flags & (1 << 5)),
        dynamic_default=bool(flags & (1 << 6)),
        no_default=bool(flags & (1 << 7)),
        reactive=bool(flags & (1 << 8)),
        public_visibility=bool(flags & (1 << 9)),
        create_read_accessor=bool(flags & (1 << 10)),
        create_write_accessor=bool(flags & (1 << 11)),
    )


def constraint_count(ir: dict) -> int:
    raw = bytes.fromhex(ir["constraint_bytes"])
    if len(raw) != 4:
        raise ValueError(f"constraint count field must be 4 bytes, got {len(raw)}")
    return struct.unpack("<I", raw)[0]


def _siblings(ir: dict, start: int) -> list[int]:
    expressions = ir["expressions"]
    result = []
    seen: set[int] = set()
    current = start
    while current != -1:
        if current in seen:
            raise ValueError(f"cycle in expression sibling chain at {current}")
        if not 0 <= current < len(expressions):
            raise ValueError(f"expression sibling chain points outside table: {current}")
        seen.add(current)
        result.append(current)
        current = expressions[current][3]
    return result


def _render_default(desc: dict, facets: SlotFacets, ir: dict, class_report: dict) -> tuple[str, list[str]]:
    if facets.no_default:
        return "(default ?NONE)", []

    root = desc["default_expression"]
    if root == -1:
        # A final bloaded descriptor normally has either noDefault or a serialized
        # static/dynamic default.  Keep a source-equivalent derive marker if an
        # unusual image omits the expression rather than inventing a value.
        return "(default ?DERIVE)", []

    indices = _siblings(ir, root)
    values = [render_expression(ir, index, class_report) for index in indices]
    keyword = "default-dynamic" if facets.dynamic_default else "default"
    return "(" + keyword + " " + " ".join(values) + ")", values


def _access_value(facets: SlotFacets) -> str:
    if facets.initialize_only:
        return "initialize-only"
    if facets.no_write:
        return "read-only"
    return "read-write"


def _create_accessor_value(facets: SlotFacets) -> str:
    if facets.create_read_accessor and facets.create_write_accessor:
        return "read-write"
    if facets.create_read_accessor:
        return "read"
    if facets.create_write_accessor:
        return "write"
    return "NONE"


def recover_slot_facets(ir: dict, class_report: dict) -> dict:
    classes = class_report["classes"]
    descriptors = class_report["slot_descriptors"]
    slot_names = class_report["slot_names"]
    bsave_constraint_count = constraint_count(ir)

    recovered = []
    referenced_descriptors: set[int] = set()
    for cls in classes:
        start = cls["slots_index"]
        count = cls["slot_count"]
        if start == -1:
            if count != 0:
                raise ValueError(f"class {cls['name']} has slot_count={count} but slots_index=-1")
            continue
        if start < 0 or start + count > len(descriptors):
            raise ValueError(f"class {cls['name']} slot descriptor range is invalid")
        for local_index, descriptor_index in enumerate(range(start, start + count)):
            if descriptor_index in referenced_descriptors:
                raise ValueError(f"slot descriptor {descriptor_index} belongs to multiple class ranges")
            referenced_descriptors.add(descriptor_index)
            desc = descriptors[descriptor_index]
            if desc["defining_class_index"] != cls["index"]:
                raise ValueError(
                    f"slot descriptor {descriptor_index} class {desc['defining_class_index']} "
                    f"!= owner {cls['index']}"
                )
            facets = decode_slot_flags(desc["flags"])
            default_source, default_values = _render_default(desc, facets, ir, class_report)
            slot_name_record = slot_names[desc["slot_name_record_index"]]
            default_override = slot_name_record["put_handler_name"]
            override_name = desc["override_message_name"]
            constraint_index = desc["constraint_index"]
            if constraint_index != -1 and not 0 <= constraint_index < bsave_constraint_count:
                raise ValueError(
                    f"slot descriptor {descriptor_index} references constraint {constraint_index}, "
                    f"but BSAVE contains {bsave_constraint_count} constraints"
                )
            recovered.append(
                {
                    "descriptor_index": descriptor_index,
                    "class_index": cls["index"],
                    "class_name": cls["name"],
                    "class_slot_index": local_index,
                    "slot_name_id": desc["slot_name_id"],
                    "slot_name": desc["slot_name"],
                    "flags": desc["flags"],
                    "facets": facets.as_json(),
                    "form": "multislot" if facets.multiple else "slot",
                    "default_expression": desc["default_expression"],
                    "default_values": default_values,
                    "default_source": default_source,
                    "constraint_index": constraint_index,
                    "constraint_serialized": constraint_index != -1,
                    "override_message": override_name,
                    "default_override_message": default_override,
                    "override_message_is_default": override_name == default_override,
                }
            )

    if len(referenced_descriptors) != len(descriptors):
        missing = sorted(set(range(len(descriptors))) - referenced_descriptors)
        raise ValueError(f"unowned serialized slot descriptors: {missing}")

    return {
        "slot_count": len(recovered),
        "constraint_count": bsave_constraint_count,
        "constraint_serialization_status": (
            "serialized" if bsave_constraint_count else "not serialized (dynamic constraint checking disabled at BSAVE time)"
        ),
        "single_slot_count": sum(not item["facets"]["multiple"] for item in recovered),
        "multislot_count": sum(item["facets"]["multiple"] for item in recovered),
        "shared_count": sum(item["facets"]["shared"] for item in recovered),
        "composite_count": sum(item["facets"]["composite"] for item in recovered),
        "no_inherit_count": sum(item["facets"]["no_inherit"] for item in recovered),
        "read_only_count": sum(item["facets"]["no_write"] and not item["facets"]["initialize_only"] for item in recovered),
        "initialize_only_count": sum(item["facets"]["initialize_only"] for item in recovered),
        "dynamic_default_count": sum(item["facets"]["dynamic_default"] for item in recovered),
        "no_default_count": sum(item["facets"]["no_default"] for item in recovered),
        "reactive_count": sum(item["facets"]["reactive"] for item in recovered),
        "public_count": sum(item["facets"]["public_visibility"] for item in recovered),
        "create_read_accessor_count": sum(item["facets"]["create_read_accessor"] for item in recovered),
        "create_write_accessor_count": sum(item["facets"]["create_write_accessor"] for item in recovered),
        "custom_override_message_count": sum(not item["override_message_is_default"] for item in recovered),
        "slots": recovered,
    }


def _direct_superclasses(cls: dict, class_report: dict) -> list[str]:
    count = cls["direct_superclass_count"]
    start = cls["superclass_list_index"]
    if count == 0 or start == -1:
        return []
    links = class_report["class_links"]
    classes = class_report["classes"]
    result = []
    for class_index in links[start : start + count]:
        if 0 <= class_index < len(classes):
            result.append(classes[class_index]["name"])
        else:
            result.append(f"class#{class_index}")
    return result


def _render_slot(slot: dict) -> list[str]:
    facets = slot["facets"]
    lines = [f"  ({slot['form']} {slot['slot_name']}"]
    lines.append(f"    {slot['default_source']}")
    lines.append("    (storage " + ("shared" if facets["shared"] else "local") + ")")
    lines.append("    (access " + _access_value(SlotFacets(**facets)) + ")")
    lines.append("    (propagation " + ("no-inherit" if facets["no_inherit"] else "inherit") + ")")
    lines.append("    (source " + ("composite" if facets["composite"] else "exclusive") + ")")
    lines.append("    (pattern-match " + ("reactive" if facets["reactive"] else "non-reactive") + ")")
    lines.append("    (visibility " + ("public" if facets["public_visibility"] else "private") + ")")
    lines.append("    (create-accessor " + _create_accessor_value(SlotFacets(**facets)) + ")")
    if slot["override_message_is_default"]:
        lines.append("    (override-message DEFAULT)")
    else:
        lines.append(f"    (override-message {slot['override_message']})")
    if slot["constraint_serialized"]:
        lines.append(f"    ;;; serialized constraint record #{slot['constraint_index']} requires constraint facet rendering")
    lines.append("  )")
    return lines


def render_recovered_classes(ir: dict, class_report: dict, game_class_names: set[str]) -> tuple[str, dict]:
    report = recover_slot_facets(ir, class_report)
    by_class: dict[str, list[dict]] = {}
    for slot in report["slots"]:
        by_class.setdefault(slot["class_name"], []).append(slot)

    lines = [
        ";;; DEFCLASSES",
        ";;; Class inheritance, slot names, compact slot facets and serialized defaults are recovered from BSAVE.",
    ]
    if report["constraint_count"] == 0:
        lines.append(
            ";;; No constraint records were serialized; type/range/cardinality facets cannot be recovered from this image."
        )
    classes = {item["name"]: item for item in class_report["classes"]}
    for name in sorted(game_class_names, key=lambda n: classes[n]["index"] if n in classes else 10_000):
        if name not in classes:
            continue
        cls = classes[name]
        supers = _direct_superclasses(cls, class_report) or ["USER"]
        lines.append(f"(defclass {name}")
        lines.append("  (is-a " + " ".join(supers) + ")")
        for slot in by_class.get(name, []):
            lines.extend(_render_slot(slot))
        lines.append(")")
        lines.append("")
    return "\n".join(lines).rstrip(), report
