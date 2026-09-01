#!/usr/bin/env python3
"""Typed recovery of the serialized CLIPS deftemplate records in CLASH.DAT."""
from __future__ import annotations

from dataclasses import asdict, dataclass


@dataclass(frozen=True)
class DeftemplateRecord:
    index: int
    name: str
    name_symbol: int
    which_module: int
    next: int
    slot_list: int
    implied: bool
    number_of_slots: int
    pattern_network: int
    raw_flags: int

    def as_json(self) -> dict:
        return asdict(self)


def decode_deftemplate(item: dict) -> DeftemplateRecord:
    # bsaveDeftemplate is 24 bytes on the target Win32 ABI:
    #   bsaveConstructHeader { name, whichModule, next } = 12 bytes
    #   slotList                                     = 4 bytes
    #   implied:1, numberOfSlots:15 (+ unused bits)  = 4 bytes
    #   patternNetwork                               = 4 bytes
    raw = item["raw"]
    if len(raw) != 6:
        raise ValueError(f"expected 6 dwords in bsaveDeftemplate, got {len(raw)}")
    flags = raw[4] & 0xFFFFFFFF
    return DeftemplateRecord(
        index=item["index"],
        name=item["name"],
        name_symbol=raw[0],
        which_module=raw[1],
        next=raw[2],
        slot_list=raw[3],
        implied=bool(flags & 1),
        number_of_slots=(flags >> 1) & 0x7FFF,
        pattern_network=raw[5],
        raw_flags=flags,
    )


def decode_deftemplates(ir: dict) -> list[DeftemplateRecord]:
    return [decode_deftemplate(item) for item in ir["templates"]]


def deftemplate_report(ir: dict) -> dict:
    templates = decode_deftemplates(ir)
    return {
        "count": len(templates),
        "implied_count": sum(item.implied for item in templates),
        "explicit_count": sum(not item.implied for item in templates),
        "serialized_slot_count": sum(item.number_of_slots for item in templates),
        "all_slot_lists_null": all(item.slot_list == -1 for item in templates),
        "templates": [item.as_json() for item in templates],
    }
