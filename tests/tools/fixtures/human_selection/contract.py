"""Small measured-original wire contract for human-player selection cleanup."""
import struct

CALLS = {"refresh_bar": 1, "sync_selection": 2}
STATE_FIELDS = ["arena", "player", "selected"] + [
    f"arena{arena}_player{player}_controller"
    for arena in range(2)
    for player in range(2)
] + [
    f"arena{arena}_stack{stack}_unit{unit}"
    for arena in range(2)
    for stack in range(2)
    for unit in range(2)
]
STATE = {name: index for index, name in enumerate(STATE_FIELDS)}
ARGUMENTS = {
    "refresh_bar": ["validated entry arena identity", "zero (no native context argument)"],
    "sync_selection": ["validated entry arena identity", "opaque context bits"],
}
HEADER_WORDS = 2
STATE_WORDS = len(STATE_FIELDS)
EVENT_WORDS = 1 + 2 + STATE_WORDS
FINAL_WORDS = STATE_WORDS + 2
ARENA_BYTES = 150200
MASK = 0xffffffff


def event(name, **changes):
    return {
        "id": CALLS[name],
        "changes": [[STATE[key], value & MASK] for key, value in changes.items()],
    }


def case(
    name, events, *, arena=0, player=0, selected=0, controller=1, first=17,
    second=0xffff, context=0x40, defined_before=True, before_expected_match=True,
    category="caller", **changes,
):
    values = [arena, player, selected, 1, 1, 1, 1] + [17, 0xffff] * 4
    values[3 + 2 * (arena % 2) + (player & 1)] = controller
    if selected in (0, 1, 0x80000000, 0x80000001):
        index = 7 + 4 * (arena % 2) + 2 * (selected & 1)
        values[index:index + 2] = [first, second]
    for key, value in changes.items():
        values[STATE[key]] = value
    return {
        "name": name,
        "header": [context & MASK, len(events)],
        "state": [value & MASK for value in values],
        "events": events,
        "defined_before": defined_before,
        "before_expected_match": before_expected_match,
        "category": category,
    }


def cases():
    result = []
    for selected in (-1, 0, 0x70000000):
        result.append(case(
            f"nonhuman-selected-{selected & MASK:08x}", [], selected=selected,
            controller=0, first=0xffff, category="nonhuman",
        ))
    for controller in (1, 2, 0x100, 0x80000000, 0xffffffff):
        result.append(case(
            f"human-dword-{controller:08x}",
            [event("refresh_bar"), event("sync_selection")],
            selected=-1, controller=controller, context=controller,
            category="controller-width",
        ))
    for first in (0xffff, 0, 17, 0x7fff, 0x8000, 0xfffe):
        events = ([event("refresh_bar")] if first == 0xffff else []) + [event("sync_selection")]
        result.append(case(
            f"first-signed-word-{first:04x}", events, first=first,
            second=17 if first == 0xffff else 0xffff, context=0x80000000 + first,
            category="first-slot",
        ))
    result.append(case(
        "other-arena-player-stack", [event("sync_selection")],
        arena=1, player=1, selected=1, context=0xffffffff, category="indexing",
    ))
    result.append(case(
        "refresh-mutates-live-state",
        [
            event(
                "refresh_bar", arena=1, player=1, selected=1,
                arena1_player1_controller=0, arena1_stack1_unit0=0xffff,
            ),
            event(
                "sync_selection", arena=0, player=0, selected=0,
                arena0_player0_controller=2,
            ),
        ],
        first=0xffff, context=0xdeadbeef, category="snapshot",
    ))
    result.append(case(
        "absent-refresh-mutates-arena",
        [
            event("refresh_bar", arena=1, selected=0),
            event("sync_selection", selected=1),
        ],
        selected=-1, context=0x87654321, category="snapshot",
    ))
    result.append(case(
        "direct-sync-mutations-retained",
        [event(
            "sync_selection", arena=1, player=1, selected=-1,
            arena1_player1_controller=0xffffffff,
        )],
        context=0x12345678, category="final-state",
    ))
    result.append(case(
        "wrapped-controller-rejection", [], arena=2, player=0x80000000,
        selected=0x70000000, controller=0, defined_before=False,
        category="wrapped-address",
    ))
    result.append(case(
        "wrapped-first-slot-kept", [event("sync_selection")],
        arena=2, player=0x80000000, selected=0x80000001, first=0xfffe,
        context=0x80000000, defined_before=False, category="wrapped-address",
    ))
    result.append(case(
        "wrapped-first-slot-cleared",
        [
            event("refresh_bar", arena=1, player=1, selected=0),
            event("sync_selection"),
        ],
        arena=3, player=0x80000001, selected=0x80000000, first=0xffff,
        context=0xffffffff, defined_before=False, category="wrapped-address",
    ))
    result.append(case(
        "negative-base-pointer-adaptation",
        [event("refresh_bar"), event("sync_selection")],
        arena=4, player=1 << 20, selected=-1, context=0x98765432,
        before_expected_match=False, category="pointer-adaptation",
    ))
    assert len({item["name"] for item in result}) == len(result)
    return result


def pack_inputs(records):
    words = [len(records)]
    for record in records:
        assert len(record["header"]) == HEADER_WORDS and len(record["state"]) == STATE_WORDS
        assert record["header"][1] == len(record["events"])
        words += record["header"] + record["state"]
        for item in record["events"]:
            words += [item["id"], len(item["changes"])]
            for field, value in item["changes"]:
                words += [field, value]
    return struct.pack("<" + "I" * len(words), *(value & MASK for value in words))


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
