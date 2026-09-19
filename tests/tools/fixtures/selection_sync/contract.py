"""Measured-original wire contract for current selection synchronization.

Count results and boundary mutations are stimuli. Expected output bytes must
come from the unchanged original caller, not from these case declarations.
"""

import struct


CALLS = {"count": 1, "end": 2, "begin": 3, "refresh": 4}
STATE_FIELDS = ["arena", "selected", "active"]
STATE = {name: index for index, name in enumerate(STATE_FIELDS)}
ARGUMENTS = {
    "count": ["validated canonical arena identity", "canonical slot bits (-1, 0, 1)"],
    "end": ["validated entry/table pointer tag", "zero"],
    "begin": ["opaque context bits", "zero"],
    "refresh": ["opaque context bits", "zero"],
}
HEADER_FIELDS = ["entry_pointer_bits", "context", "event_count"]
HEADER_WORDS = 3
STATE_WORDS = len(STATE_FIELDS)
EVENT_WORDS = 1 + 2 + 1 + STATE_WORDS
FINAL_WORDS = STATE_WORDS
ARENA_BYTES = 150200
STACK_TABLE_OFFSET = 147174
STACK_STRIDE = 725
CANONICAL_SLOTS = [-1, 0, 1]
MASK = 0xffffffff


def event(name, result=0, **changes):
    return {
        "id": CALLS[name],
        "result": result & MASK,
        "changes": [[STATE[field], value & MASK] for field, value in changes.items()],
    }


def case(
    name, events, *, arena=0, selected=0, active=-1,
    entry_pointer=0x12345678, context=0x40, category="caller",
    defined_before=True, before_expected_match=True, before_reasons=(),
    address_model="backed canonical stack", **notes,
):
    return {
        "name": name,
        "header": [entry_pointer & MASK, context & MASK, len(events)],
        "state": [arena, selected & MASK, active & MASK],
        "events": events,
        "category": category,
        "defined_before": defined_before,
        "before_expected_match": before_expected_match,
        "before_reasons": list(before_reasons),
        "address_model": address_model,
        "notes": notes,
    }


def cases():
    records = [
        case(
            "absent-inactive", [], selected=-1, active=-1,
            entry_pointer=0, context=0, category="absent",
        ),
        case(
            "absent-active-null-entry",
            [event("end", arena=1, selected=1, active=-1)],
            selected=-1, active=0, entry_pointer=0, category="absent",
        ),
        case(
            "absent-active-high-entry", [event("end")],
            selected=-1, active=1, entry_pointer=0x87654321,
            context=0xffffffff, category="absent",
        ),
        case(
            "absent-active-all-ones-entry", [event("end")],
            selected=-1, active=2, entry_pointer=0xffffffff, category="absent",
        ),
        case(
            "singleton-active-same-stack", [event("count", 1), event("end")],
            active=0, category="singleton", before_expected_match=False,
            before_reasons=("defined singleton End forwards entry instead of table base",),
        ),
        case(
            "singleton-other-arena-terminal-mutations",
            [event("count", 1), event("end", arena=0, selected=-1, active=1)],
            arena=1, selected=1, active=0, category="singleton",
            before_expected_match=False,
            before_reasons=("defined singleton End forwards entry instead of table base",),
        ),
        case(
            "singleton-inactive-continues-to-second",
            [event("count", 1), event("count", 2), event("begin")],
            context=0, category="begin",
        ),
        case(
            "zero-first-ten-second-begins",
            [event("count", 0), event("count", 10), event("begin", arena=1, selected=1, active=1)],
            category="begin",
        ),
        case(
            "multi-inactive-begins",
            [event("count", 2), event("count", 2), event("begin")],
            context=0x80000000, category="begin",
        ),
        case(
            "equal-active-skips-third", [event("count", 2), event("count", 2)],
            active=0, category="third-gate",
        ),
        case(
            "different-active-refreshes",
            [event("count", 2), event("count", 2), event("count", 2),
             event("refresh", arena=1, selected=-1, active=0)],
            active=1, context=0xffffffff, category="refresh",
        ),
        case(
            "third-zero-does-not-refresh",
            [event("count", 2), event("count", 2), event("count", 0)],
            active=1, category="refresh",
        ),
        case(
            "third-one-does-not-refresh",
            [event("count", 0), event("count", 1), event("count", 1)],
            active=1, category="refresh",
        ),
        case(
            "second-negative-inactive-does-not-begin",
            [event("count", 0), event("count", -1), event("count", 0)],
            category="signed-count", synthetic_negative_count=True,
        ),
        case(
            "second-int-min-allows-third-refresh",
            [event("count", 0), event("count", 0x80000000), event("count", 2), event("refresh")],
            active=1, category="signed-count", synthetic_negative_count=True,
        ),
        case(
            "third-negative-does-not-refresh",
            [event("count", 0), event("count", 0), event("count", -1)],
            active=1, category="signed-count", synthetic_negative_count=True,
        ),
        case(
            "third-int-min-does-not-refresh",
            [event("count", 2), event("count", 0), event("count", 0x80000000)],
            active=1, category="signed-count", synthetic_negative_count=True,
        ),
        case(
            "first-query-mutates-arena-and-selection",
            [event("count", 0, arena=1, selected=1), event("count", 2), event("begin")],
            category="live-query",
        ),
        case(
            "singleton-reads-mutated-active",
            [event("count", 1, active=2), event("end")],
            category="live-query", before_expected_match=False,
            before_reasons=("defined singleton End forwards entry instead of table base",),
        ),
        case(
            "singleton-retains-pre-query-table-base",
            [event("count", 1, arena=1, selected=1, active=2), event("end")],
            category="saved-table", before_expected_match=False,
            before_reasons=("defined singleton End forwards entry instead of saved table base",),
        ),
        case(
            "second-query-mutates-equality-to-skip-third",
            [event("count", 0), event("count", 0, arena=1, selected=1, active=1)],
            category="live-query",
        ),
        case(
            "second-query-mutates-begin-gate-and-third-address",
            [event("count", 0), event("count", 2, arena=1, selected=0, active=1),
             event("count", 2), event("refresh")],
            category="live-query",
        ),
        case(
            "third-query-equality-mutation-does-not-recheck",
            [event("count", 0), event("count", 0), event("count", 2, active=0), event("refresh")],
            active=1, category="live-query",
        ),
        case(
            "second-query-selection-minus-one-is-not-reguarded",
            [event("count", 0), event("count", 0, selected=-1), event("count", 2), event("refresh")],
            active=0, category="live-query",
            address_model="backed bytes before stack table; synthetic slot -1 is never dereferenced",
        ),
        case(
            "wrapped-first-query-singleton-end", [event("count", 1), event("end")],
            arena=2, selected=0x80000000, active=0, category="wrapped-address",
            defined_before=False, before_expected_match=False,
            before_reasons=("first query signed stride multiplication overflow",
                            "independent singleton End argument difference"),
            address_model="paired wrapping reaches backed arena0 slot0",
        ),
        case(
            "wrapped-second-query-begin",
            [event("count", 0, arena=3, selected=0x80000001), event("count", 10), event("begin")],
            category="wrapped-address", defined_before=False, before_expected_match=False,
            before_reasons=("second query signed stride multiplication overflow",),
            address_model="paired wrapping reaches backed arena1 slot1",
        ),
        case(
            "wrapped-third-query-refresh",
            [event("count", 0), event("count", 0, arena=2, selected=0x80000000),
             event("count", 2), event("refresh")],
            active=1, category="wrapped-address", defined_before=False, before_expected_match=False,
            before_reasons=("third query signed stride multiplication overflow",),
            address_model="paired wrapping reaches backed arena0 slot0",
        ),
        case(
            "negative-count-pointer-width-adaptation",
            [event("count", 2), event("count", 2), event("begin")],
            arena=2, selected=0, category="pointer-adaptation",
            before_expected_match=False,
            before_reasons=("defined negative int to intptr_t sign extension",),
            address_model="unbacked high count pointer observed only at recording boundary",
        ),
    ]
    assert len(records) == 28
    assert len({record["name"] for record in records}) == len(records)
    return records


def pack_inputs(records):
    words = [len(records)]
    for record in records:
        assert len(record["header"]) == HEADER_WORDS
        assert len(record["state"]) == STATE_WORDS
        assert record["header"][2] == len(record["events"])
        words += record["header"] + record["state"]
        for item in record["events"]:
            words += [item["id"], item["result"], len(item["changes"])]
            for field, value in item["changes"]:
                words += [field, value]
    return struct.pack("<" + "I" * len(words), *(word & MASK for word in words))


def decode_output(payload, records):
    offset = 0
    traces = []
    for record in records:
        size = 4 * (EVENT_WORDS * len(record["events"]) + FINAL_WORDS)
        trace = payload[offset:offset + size]
        if len(trace) != size:
            raise ValueError(f"short output for {record['name']}")
        traces.append(trace)
        offset += size
    if offset != len(payload):
        raise ValueError("trailing output")
    return traces
