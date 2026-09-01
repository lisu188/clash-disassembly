#!/usr/bin/env python3
"""Decode the six-byte HANDLER_GET/HANDLER_PUT payloads in CLASH.DAT.

Recovered runtime evidence in MessageHandler_GetSelfSlotDirect and
MessageHandler_PutSelfSlotDirect shows an exact packed layout:

    uint16 class_id
    uint32 slot_name_id

The class id is resolved through the bloaded defclass id table and the slot id is
the global CLIPS slot-name id used by the class slot-name map.
"""
from __future__ import annotations

from dataclasses import asdict, dataclass
import struct

HANDLER_GET = 58
HANDLER_PUT = 59


@dataclass(frozen=True)
class HandlerSlotReference:
    expression_index: int
    type: int
    operation: str
    bitmap_index: int
    raw_hex: str
    class_id: int
    class_name: str
    slot_name_id: int
    slot_name: str

    @property
    def clips_target(self) -> str:
        return f"?self:{self.slot_name}"

    def as_json(self) -> dict:
        result = asdict(self)
        result["clips_target"] = self.clips_target
        return result


def decode_handler_payload(blob: bytes) -> tuple[int, int]:
    if len(blob) != 6:
        raise ValueError(f"direct handler slot payload must be 6 bytes, got {len(blob)}")
    return struct.unpack("<HI", blob)


def decode_handler_reference(
    expression_index: int,
    expression: tuple[int, int, int, int],
    ir: dict,
    class_report: dict,
) -> HandlerSlotReference | None:
    type_id, bitmap_index, _arg, _next = expression
    if type_id not in (HANDLER_GET, HANDLER_PUT):
        return None
    blob = ir["bitmaps"][bitmap_index]
    class_id, slot_name_id = decode_handler_payload(blob)
    class_name = class_report["class_name_by_id"].get(class_id, f"class#{class_id}")
    slot_name = class_report["slot_name_by_id"].get(slot_name_id, f"system-slot#{slot_name_id}")
    return HandlerSlotReference(
        expression_index=expression_index,
        type=type_id,
        operation="get" if type_id == HANDLER_GET else "put",
        bitmap_index=bitmap_index,
        raw_hex=blob.hex(),
        class_id=class_id,
        class_name=class_name,
        slot_name_id=slot_name_id,
        slot_name=slot_name,
    )


def decode_all_handler_references(ir: dict, class_report: dict) -> list[HandlerSlotReference]:
    result = []
    for index, expression in enumerate(ir["expressions"]):
        decoded = decode_handler_reference(index, expression, ir, class_report)
        if decoded is not None:
            result.append(decoded)
    return result


def handler_reference_report(ir: dict, class_report: dict) -> dict:
    refs = decode_all_handler_references(ir, class_report)
    return {
        "count": len(refs),
        "get_count": sum(item.type == HANDLER_GET for item in refs),
        "put_count": sum(item.type == HANDLER_PUT for item in refs),
        "classes": sorted({item.class_name for item in refs}),
        "slots": sorted({item.slot_name for item in refs}),
        "references": [item.as_json() for item in refs],
    }
