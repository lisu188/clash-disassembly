#!/usr/bin/env python3
"""Decode CLIPS 6.00 defclass/slot records used by CLASH.DAT object patterns."""
from __future__ import annotations

from dataclasses import asdict, dataclass
from pathlib import Path
import struct

CLASS_RECORD_SIZE = 76
SLOT_NAME_RECORD_SIZE = 16
SLOT_DESCRIPTOR_RECORD_SIZE = 24
HANDLER_RECORD_SIZE = 28


@dataclass(frozen=True)
class ClassRecord:
    index: int
    name_symbol: int
    name: str
    module: int
    next: int
    flags: int
    class_id: int
    direct_superclass_count: int
    superclass_list_index: int
    direct_subclass_count: int
    subclass_list_index: int
    all_superclass_count: int
    all_superclass_list_index: int
    slot_count: int
    instance_slot_count: int
    local_instance_slot_count: int
    max_slot_name_id: int
    handler_count: int
    slots_index: int
    instance_template_index: int
    slot_name_map_index: int
    handlers_index: int
    scope_bitmap: int

    def as_json(self) -> dict:
        return asdict(self)


@dataclass(frozen=True)
class SlotNameRecord:
    index: int
    slot_name_id: int
    hash_index: int
    name_symbol: int
    name: str
    put_handler_symbol: int
    put_handler_name: str

    def as_json(self) -> dict:
        return asdict(self)


@dataclass(frozen=True)
class SlotDescriptorRecord:
    index: int
    flags: int
    defining_class_index: int
    slot_name_record_index: int
    slot_name_id: int
    slot_name: str
    default_expression: int
    constraint_index: int
    override_message_symbol: int
    override_message_name: str

    def as_json(self) -> dict:
        return asdict(self)


def _section(ir: dict, name: str, kind: str = "data") -> dict:
    key = "data_sections" if kind == "data" else "storage_sections"
    for item in ir[key]:
        if item["name"] == name:
            return item
    raise KeyError(f"missing {kind} section {name!r}")


def _bitmap_bytes(ir: dict, index: int) -> bytes:
    item = ir["bitmaps"][index]
    if isinstance(item, bytes):
        return item
    if isinstance(item, str):
        return bytes.fromhex(item)
    if isinstance(item, dict) and "hex" in item:
        return bytes.fromhex(item["hex"])
    raise TypeError(f"unsupported bitmap representation at {index}: {type(item)!r}")


def decode_id_bitmap(blob: bytes) -> tuple[int, list[int]]:
    """Decode CLIPS class/slot bitmap: uint16 max-id followed by packed bits."""
    if len(blob) < 3:
        raise ValueError(f"CLIPS id bitmap is too short: {len(blob)}")
    max_id = struct.unpack_from("<H", blob, 0)[0]
    expected = 2 + (max_id >> 3) + 1
    if len(blob) != expected:
        raise ValueError(f"bitmap max-id {max_id} expects {expected} bytes, got {len(blob)}")
    ids = [
        item_id
        for item_id in range(max_id + 1)
        if blob[2 + (item_id >> 3)] & (1 << (item_id & 7))
    ]
    return max_id, ids


def parse_defclass(path: Path, ir: dict) -> dict:
    data = path.read_bytes()
    storage = _section(ir, "defclass", "storage")
    if storage["size"] != 36:
        raise ValueError(f"unexpected defclass storage size {storage['size']}")

    counts = struct.unpack_from("<9i", data, storage["payload"])
    (
        module_count,
        class_count,
        class_link_count,
        slot_name_count,
        slot_descriptor_count,
        instance_template_link_count,
        slot_name_map_count,
        handler_count,
        max_class_id_count,
    ) = counts

    section = _section(ir, "defclass")
    expected = (
        12 * module_count
        + CLASS_RECORD_SIZE * class_count
        + 4 * class_link_count
        + SLOT_NAME_RECORD_SIZE * slot_name_count
        + SLOT_DESCRIPTOR_RECORD_SIZE * slot_descriptor_count
        + 4 * instance_template_link_count
        + 4 * slot_name_map_count
        + HANDLER_RECORD_SIZE * handler_count
        + 4 * handler_count
    )
    if section["size"] != expected:
        raise ValueError(f"defclass data size {section['size']} != expected {expected}")

    offset = section["payload"]
    modules = [struct.unpack_from("<3i", data, offset + 12 * i) for i in range(module_count)]
    offset += 12 * module_count

    classes: list[ClassRecord] = []
    for index in range(class_count):
        record = data[offset + index * CLASS_RECORD_SIZE : offset + (index + 1) * CLASS_RECORD_SIZE]
        name_symbol, module, next_index = struct.unpack_from("<3i", record, 0)
        classes.append(
            ClassRecord(
                index=index,
                name_symbol=name_symbol,
                name=ir["symbols"][name_symbol],
                module=module,
                next=next_index,
                flags=struct.unpack_from("<I", record, 12)[0],
                class_id=struct.unpack_from("<H", record, 16)[0],
                direct_superclass_count=struct.unpack_from("<H", record, 18)[0],
                superclass_list_index=struct.unpack_from("<i", record, 20)[0],
                direct_subclass_count=struct.unpack_from("<H", record, 24)[0],
                subclass_list_index=struct.unpack_from("<i", record, 26)[0],
                all_superclass_count=struct.unpack_from("<H", record, 30)[0],
                all_superclass_list_index=struct.unpack_from("<i", record, 32)[0],
                slot_count=struct.unpack_from("<i", record, 36)[0],
                local_instance_slot_count=struct.unpack_from("<i", record, 40)[0],
                instance_slot_count=struct.unpack_from("<i", record, 44)[0],
                max_slot_name_id=struct.unpack_from("<i", record, 48)[0],
                handler_count=struct.unpack_from("<i", record, 52)[0],
                slots_index=struct.unpack_from("<i", record, 56)[0],
                instance_template_index=struct.unpack_from("<i", record, 60)[0],
                slot_name_map_index=struct.unpack_from("<i", record, 64)[0],
                handlers_index=struct.unpack_from("<i", record, 68)[0],
                scope_bitmap=struct.unpack_from("<i", record, 72)[0],
            )
        )
    offset += CLASS_RECORD_SIZE * class_count

    class_links = list(struct.unpack_from("<" + "i" * class_link_count, data, offset)) if class_link_count else []
    offset += 4 * class_link_count

    slot_names: list[SlotNameRecord] = []
    for index in range(slot_name_count):
        slot_name_id, hash_index, name_symbol, put_symbol = struct.unpack_from(
            "<4i", data, offset + index * SLOT_NAME_RECORD_SIZE
        )
        slot_names.append(
            SlotNameRecord(
                index=index,
                slot_name_id=slot_name_id,
                hash_index=hash_index,
                name_symbol=name_symbol,
                name=ir["symbols"][name_symbol],
                put_handler_symbol=put_symbol,
                put_handler_name=ir["symbols"][put_symbol],
            )
        )
    offset += SLOT_NAME_RECORD_SIZE * slot_name_count

    slot_descriptors: list[SlotDescriptorRecord] = []
    for index in range(slot_descriptor_count):
        flags, defining_class, slot_name_record, default_expr, constraint, override_symbol = struct.unpack_from(
            "<6i", data, offset + index * SLOT_DESCRIPTOR_RECORD_SIZE
        )
        if not 0 <= slot_name_record < len(slot_names):
            raise ValueError(f"slot descriptor {index} references bad slot-name record {slot_name_record}")
        slot_name = slot_names[slot_name_record]
        slot_descriptors.append(
            SlotDescriptorRecord(
                index=index,
                flags=flags & 0xFFFFFFFF,
                defining_class_index=defining_class,
                slot_name_record_index=slot_name_record,
                slot_name_id=slot_name.slot_name_id,
                slot_name=slot_name.name,
                default_expression=default_expr,
                constraint_index=constraint,
                override_message_symbol=override_symbol,
                override_message_name=ir["symbols"][override_symbol],
            )
        )
    offset += SLOT_DESCRIPTOR_RECORD_SIZE * slot_descriptor_count

    instance_template_links = list(struct.unpack_from("<" + "i" * instance_template_link_count, data, offset)) if instance_template_link_count else []
    offset += 4 * instance_template_link_count
    slot_name_map = list(struct.unpack_from("<" + "i" * slot_name_map_count, data, offset)) if slot_name_map_count else []
    offset += 4 * slot_name_map_count

    handlers = [
        list(struct.unpack_from("<7i", data, offset + index * HANDLER_RECORD_SIZE))
        for index in range(handler_count)
    ]
    offset += HANDLER_RECORD_SIZE * handler_count
    handler_map = list(struct.unpack_from("<" + "i" * handler_count, data, offset)) if handler_count else []
    offset += 4 * handler_count

    if offset != section["end"]:
        raise ValueError(f"defclass parser ended at {offset:#x}, section ends at {section['end']:#x}")

    class_by_id = {item.class_id: item for item in classes}
    slot_name_by_id = {item.slot_name_id: item for item in slot_names}

    declared_slots = {}
    for cls in classes:
        if cls.slots_index == -1:
            declared_slots[cls.name] = []
            continue
        end = cls.slots_index + cls.slot_count
        if end > len(slot_descriptors):
            raise ValueError(f"class {cls.name} slot range exceeds slot descriptor array")
        declared_slots[cls.name] = [item.slot_name for item in slot_descriptors[cls.slots_index:end]]

    return {
        "counts": {
            "modules": module_count,
            "classes": class_count,
            "class_links": class_link_count,
            "slot_names": slot_name_count,
            "slot_descriptors": slot_descriptor_count,
            "instance_template_links": instance_template_link_count,
            "slot_name_map": slot_name_map_count,
            "handlers": handler_count,
            "max_class_id_count": max_class_id_count,
        },
        "modules": [list(item) for item in modules],
        "classes": [item.as_json() for item in classes],
        "class_links": class_links,
        "slot_names": [item.as_json() for item in slot_names],
        "slot_descriptors": [item.as_json() for item in slot_descriptors],
        "instance_template_links": instance_template_links,
        "slot_name_map": slot_name_map,
        "handlers": handlers,
        "handler_map": handler_map,
        "declared_slots": declared_slots,
        "class_name_by_id": {item_id: item.name for item_id, item in class_by_id.items()},
        "slot_name_by_id": {item_id: item.name for item_id, item in slot_name_by_id.items()},
    }


def decode_class_bitmap(ir: dict, bitmap_index: int, class_report: dict) -> dict:
    max_id, ids = decode_id_bitmap(_bitmap_bytes(ir, bitmap_index))
    names = [class_report["class_name_by_id"].get(item_id, f"class#{item_id}") for item_id in ids]
    return {"bitmap_index": bitmap_index, "max_id": max_id, "ids": ids, "names": names}


def decode_slot_bitmap(ir: dict, bitmap_index: int, class_report: dict) -> dict:
    max_id, ids = decode_id_bitmap(_bitmap_bytes(ir, bitmap_index))
    names = [class_report["slot_name_by_id"].get(item_id, f"system-slot#{item_id}") for item_id in ids]
    return {"bitmap_index": bitmap_index, "max_id": max_id, "ids": ids, "names": names}
