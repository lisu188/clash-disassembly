#!/usr/bin/env python3
"""Asset-free, original-measured call traces of the actual Road modal loop.

Callees are scripted recording/mutating boundaries, not gameplay simulations.
The real guarded widget initializer and packed production layouts are included.
Original clock input registers have no semantics; native arguments must be 0,0.
"""
from pathlib import Path
import hashlib
import json
import shutil
import struct
import subprocess
import tempfile
import unittest

import test_builder_road as builder_road

SOURCE = builder_road.REPO / "src/buildings/00425540_00426FC0_buildings_006.cpp"
FUNCTION = "Builder_StartRoadBuildMode"
CALLS = ("surface", "cursor", "viewport", "pump", "scroll", "frame", "clock",
         "tile", "poll", "select", "begin", "flipping", "build", "refresh")
STATE_FIELDS = ("arena", "selected", "exit", "target", "tick", "frame", "cursor",
                "hook", "control", "north_flags", "east_flags", "south_flags",
                "west_flags", "raw_x", "raw_y", "shift", "render277",
                "view_left0", "view_top0", "view_left1", "view_top1") + tuple(
    f"{axis}{arena}_{slot}" for arena in range(2) for slot in range(4)
    for axis in ("row", "column"))
# Each event has six observation words: ordinary arguments except pump, whose
# slots are render identity, full carried EBX/native argument, and ABI BL byte.
EVENT_WORDS = 1 + 6 + len(STATE_FIELDS)
FINAL_WORDS = 1 + len(STATE_FIELDS) + 5
MAX_EVENTS = 96
ARENA_BYTES = 150200


def event(call, result=0, **mutations):
    return dict(call=call, result=result & 0xFFFFFFFF,
                mutations={key: value & 0xFFFFFFFF for key, value in mutations.items()})


def default_state():
    state = dict.fromkeys(STATE_FIELDS, 0)
    state.update(exit=7, target=9, tick=100, frame=7, cursor=1, hook=1,
                 control=13, north_flags=21, east_flags=22, south_flags=23,
                 west_flags=24, raw_x=32, raw_y=16, render277=0xA1B2C300)
    for arena in range(2):
        for slot in range(4):
            state[f"row{arena}_{slot}"] = 10 + arena * 30 + slot * 3
            state[f"column{arena}_{slot}"] = 20 + arena * 40 + slot * 5
        state[f"view_left{arena}"] = state[f"row{arena}_0"]
        state[f"view_top{arena}"] = state[f"column{arena}_0"]
    return state


def cases():
    records = []
    finite_bits = (0, 0x8000000000000000, 0x3FF8000000000000,
                   0xC002000000000000, 1, 0x0010000000000000,
                   0x7FEFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF)

    def add(name, events, initial=None, cold=False, pattern=0):
        state = default_state()
        state.update(initial or {})
        if cold:
            # The native handler reconstructs static original data on entry.
            road = (builder_road.FIXTURES / "original-road.bin").read_bytes()
            for field, offset in (("control", 392), ("north_flags", 180),
                                  ("east_flags", 233), ("south_flags", 286),
                                  ("west_flags", 339)):
                state[field] = struct.unpack_from("<I", road, offset)[0]
        records.append(dict(name=name, cold=int(cold),
                            a1=(0, 0xFFFFFFFF, 0x80000000, 0x12345678,
                                0x55555555, 0xAAAAAAAA, 0x01020304, 0x7FFFFFFF)[pattern],
                            a2_bits=finite_bits[pattern],
                            initial={key: value & 0xFFFFFFFF for key, value in state.items()},
                            events=events))

    def entry(**changes):
        return [event("surface", 2), event("cursor", 0x1234), event("viewport", -71, **changes)]

    def cleanup(**changes):
        return [event("refresh", 0x12340000, **changes), event("viewport", 0x87654321)]

    def loop(*, clock=100, poll=1, flip=0, changes=None):
        return [event("pump", 91), event("scroll", -92), event("frame", 93),
                event("clock", clock), event("poll", poll),
                *([] if poll else [event("cursor", 0x4567), event("select", 0)]),
                event("flipping", flip, **(changes or {}))]

    for cold in (False, True):
        add(f"surface-rejection-cold-{int(cold)}", [event("surface", 185)], cold=cold)
        add(f"initial-redraw-exit-cold-{int(cold)}", entry(exit=4) + cleanup(), cold=cold)
    add("cleanup-callback-state-survives", entry(exit=4) + [
        event("refresh", -77, exit=0, target=0x76543210, hook=1, cursor=1,
              control=81, selected=3, arena=1, frame=0x1234, tick=0x80000000),
        event("viewport", 0, exit=0x123, target=8, hook=1, cursor=2, control=99)])
    add("surface-and-cursor-mutations", [event("surface", -31, selected=2, arena=1,
        target=11, tick=200, frame=4), event("cursor", -2, exit=8, target=13,
        hook=1, cursor=1, control=91), event("viewport", 7, exit=1)] + cleanup())
    for source in ("pump", "scroll", "frame", "clock", "poll", "cursor", "select", "flipping"):
        events = loop(poll=0)
        next(item for item in events if item["call"] == source)["mutations"]["exit"] = 17
        add("late-exit-from-" + source, entry() + events + cleanup())
    add("friendly-selection-immediate-cleanup", entry() + loop(poll=0)[:-2]
        + [event("select", 1, exit=0), event("begin", -2, target=93)] + cleanup())
    add("persistent-animation-then-hover-then-no-flip", entry() + [
        event("pump"), event("scroll"), event("frame"), event("clock", 111),
        event("clock", 118), event("tile"), event("tile"), event("tile"), event("tile"),
        event("poll", 1), event("flipping", 0)] + loop(clock=118, flip=1, changes={"raw_x": 672})
        + loop(clock=118, changes={"exit": 1}) + cleanup())
    add("fresh-state-at-every-animation-redraw", entry() + [
        event("pump"), event("scroll"), event("frame"), event("clock", 200, tick=189),
        event("clock", 217, selected=1, row0_1=32767, column0_1=-32768, frame=0xFF),
        event("tile", 1, selected=2, arena=1, row1_2=-32768, column1_2=32767),
        event("tile", 2, selected=3, row1_3=13, column1_3=27),
        event("tile", 3, selected=0, arena=0, row0_0=-31, column0_0=-47),
        event("tile", 4, frame=0xFFFFFF00, target=0x8888), event("poll", 1),
        event("flipping", 0, exit=1)] + cleanup())
    timer_pairs = ((0, 0), (9, 0), (10, 0), (11, 0), (110, 100), (111, 100),
                   (0x80000000, 0), (0x80000009, 0x7FFFFFFF),
                   (0xFFFFFFFF, 0xFFFFFFF4), (0, 0xFFFFFFFF))
    for sample, tick in timer_pairs:
        for mutation in (False, True):
            compared_tick = (tick ^ 0x80000000) if mutation else tick
            body = [event("pump"), event("scroll"), event("frame"),
                    event("clock", sample, **({"tick": compared_tick} if mutation else {}))]
            if ((sample - 10) & 0xFFFFFFFF) > compared_tick:
                body += [event("clock", 0xFEDCBA98), *[event("tile") for _ in range(4)]]
            body += [event("poll", 1), event("flipping", 0, exit=1)]
            add(f"timer-{sample:08x}-{tick:08x}-reload-{int(mutation)}", entry() + body + cleanup(), {"tick": tick})
    for direction, dx, dy in (("north", 0, -1), ("east", 1, 0), ("south", 0, 1), ("west", -1, 0)):
        for pattern in range(8):
            for keep_target in (False, True):
                extra = loop(changes={"exit": 1}) if keep_target else []
                add(f"build-{direction}-finite-{pattern}-continue-{int(keep_target)}",
                    entry() + loop(flip=1) + [event("build", 0x98765432,
                    target=0x2345, selected=3, hook=1, cursor=1),
                    event("viewport", -321, target=5 if keep_target else 0)] + extra + cleanup(),
                    {"raw_x": 32 + 64 * dx, "raw_y": 16 + 64 * dy}, pattern=pattern)
    add("build-and-redraw-late-exit", entry() + loop(flip=1) + [
        event("build", 7, exit=33, target=34), event("viewport", 8, target=35)] + cleanup(),
        {"raw_y": -48})
    # All shift-byte patterns exercise x86's five-bit mask. A second iteration
    # exposes the full row delta through pump/frame, even when no marker exists.
    raw_patterns = (0x80000000, 0x8000001F, 0x80000020, 31, 0xFFFFFFE0,
                    0xFFFFFFFF, 64, 0x7FFFFFFF, 160, 0, 0x80000010, 0xFFFFFFF0)
    for shift in range(256):
        raw_x, raw_y = raw_patterns[shift % len(raw_patterns)], raw_patterns[(shift + 5) % len(raw_patterns)]
        add(f"cursor-shift-byte-{shift:02x}", entry() + loop(flip=1)
            + loop(changes={"exit": 1}) + cleanup(),
            {"shift": shift, "raw_x": raw_x, "raw_y": raw_y,
             "view_left0": 0x81234567, "view_top0": 0x76543210,
             "row0_0": -32768, "column0_0": 32767})
    # Force the final cursor result to each exact neighbor. This makes column
    # rounding/wrapping observable as marker identity, not merely as a branch
    # that happens to reject every large input. This arithmetic only generates
    # inputs; golden results still come from unchanged original instructions.
    def signed(value):
        return value if value < 0x80000000 else value - 0x100000000

    def quotient(raw, shift, origin):
        pixel = signed(((signed(raw) >> (shift & 31)) - origin) & 0xFFFFFFFF)
        return -(abs(pixel) // 64) if pixel < 0 else pixel // 64

    directions = ((0, -1), (1, 0), (0, 1), (-1, 0))
    for index in range(48):
        shift = (0, 1, 31, 32, 33, 255)[index % 6]
        raw_x = raw_patterns[index % len(raw_patterns)]
        raw_y = raw_patterns[(index // 4 + 3) % len(raw_patterns)]
        dx, dy = directions[index % 4]
        row, column = ((-32768, 32767), (32767, -32768))[index % 2]
        add(f"cursor-exact-marker-boundary-{index}", entry() + loop(flip=1)
            + [event("build", -93), event("viewport", -94)] + cleanup(),
            {"shift": shift, "raw_x": raw_x, "raw_y": raw_y,
             "row0_0": row, "column0_0": column,
             "view_left0": row + dx - quotient(raw_x, shift, 32),
             "view_top0": column + dy - quotient(raw_y, shift, 16)})
    for dx, dy in ((0, 0), (-1, -1), (-1, 1), (1, -1), (1, 1),
                   (-2, 0), (2, 0), (0, -2), (0, 2), (-2, -2), (2, 2)):
        add(f"nonmarker-delta-{dx}-{dy}", entry() + loop(flip=1)
            + loop(changes={"exit": 1}) + cleanup(),
            {"raw_x": 32 + 64 * dx, "raw_y": 16 + 64 * dy})
    for truthy in (0xFFFFFFFF, 0x80000000):
        add(f"truthy-poll-and-flip-{truthy:x}", entry() + loop(poll=truthy, flip=truthy)
            + [event("build"), event("viewport")] + cleanup(), {"raw_x": 96})
        add(f"truthy-friendly-selection-{truthy:x}", entry() + loop(poll=0)[:-2]
            + [event("select", truthy), event("begin")] + cleanup())
    add("selected-state-changes-at-every-boundary", [
        event("surface", 1, arena=1, selected=1), event("cursor", 1, arena=0, selected=2),
        event("viewport", 1, arena=1, selected=3),
        event("pump", 1, arena=0, selected=0), event("scroll", 1, arena=1, selected=1),
        event("frame", 1, arena=0, selected=2), event("clock", 200, arena=1, selected=3),
        event("clock", 220, arena=0, selected=0, frame=0x102),
        event("tile", 1, arena=1, selected=1), event("tile", 1, arena=0, selected=2),
        event("tile", 1, arena=1, selected=3), event("tile", 1, arena=0, selected=0),
        event("poll", 0, arena=1, selected=1, cursor=1),
        event("cursor", 1, arena=0, selected=2, cursor=2),
        event("select", 0, arena=1, selected=3),
        event("flipping", 1, arena=0, selected=2, view_left0=17, view_top0=30,
              raw_x=32, raw_y=16, shift=32),
        event("build", 0, arena=1, selected=1, target=0xFFFF),
        event("viewport", 1, arena=0, selected=2, target=1, exit=19),
        event("refresh", 1, arena=1, selected=3), event("viewport", -7, arena=0, selected=0)])
    for result in (0, 1, 0xFFFFFFFF, 0x80000000, 0x7FFFFFFF, 0x5142B8, 0x513670):
        add(f"raw-final-redraw-result-{result:08x}", entry(exit=1)
            + [event("refresh", 0xDEADBEEF), event("viewport", result)])
    assert len({record["name"] for record in records}) == len(records)
    assert all(len(record["events"]) <= MAX_EVENTS for record in records)
    return records


def encode_cases(records):
    words = [len(records)]
    for case in records:
        words += [case["cold"], case["a1"], case["a2_bits"] & 0xFFFFFFFF,
                  case["a2_bits"] >> 32, len(case["events"])]
        words += [case["initial"][field] for field in STATE_FIELDS]
        for boundary in case["events"]:
            words += [CALLS.index(boundary["call"]) + 1, boundary["result"], len(boundary["mutations"])]
            for field, value in boundary["mutations"].items():
                words += [STATE_FIELDS.index(field), value]
    return struct.pack(f"<{len(words)}I", *words)


def split_output(data, records):
    position = 0
    for case in records:
        size = 4 * (len(case["events"]) * EVENT_WORDS + FINAL_WORDS)
        if position + size > len(data):
            raise AssertionError("incomplete trace for " + case["name"])
        yield data[position:position + size]
        position += size
    if position != len(data):
        raise AssertionError("unexpected trailing trace bytes")


def harness_source(body=None):
    _, road, builder, relocations = builder_road.fixtures()
    symbols = {item["canonical_symbol"] for item in relocations if item.get("canonical_symbol")}
    symbols.difference_update(("g_ActionButtonSpriteSet", "RoadBuildMode_BuildInSelectedDirection"))
    spies = "\n".join("static int " + name + "() { fail(\"address-only callback invoked\"); }"
                      for name in sorted(symbols))
    masks = {"road": bytearray(len(road)), "builder": bytearray(len(builder))}
    checks, fields = [], []
    for index, item in enumerate(relocations):
        table = "builder" if item["table"] == "builder-widgets" else "road"
        actual = "g_UI_YesNoDims" if table == "builder" else "g_RoadBuildData"
        offset = item["region_offset"]
        original = int(item["original_pointer"], 16)
        masks[table][offset:offset + 4] = b"\1" * 4
        fields.append(f"{{{int(table == 'builder')}, {offset}, {original}U}}")
        field = f"{actual} + {offset}"
        if item.get("canonical_symbol"):
            checks.append(f"check_pointer({field}, (uintptr_t)&{item['canonical_symbol']});")
        elif "raw_hex" in item:
            checks.append(builder_road.byte_array(f"text_{index}", bytes.fromhex(item["raw_hex"]) + b"\0"))
            checks.append(f"check_text({field}, text_{index}, sizeof text_{index});")
        else:
            assert original == 0
            checks.append(f"check_pointer({field}, 0);")
    data = "".join(builder_road.byte_array(name, values) for name, values in (
        ("original_road", road), ("original_builder", builder),
        ("road_pointer_mask", masks["road"]), ("builder_pointer_mask", masks["builder"])))
    initializer = builder_road.extract(builder_road.WORLD2, "WorldMap_EnsureBuilderWidgetTables")
    if body is None:
        body = builder_road.extract(SOURCE, FUNCTION)
    return (HARNESS.replace("@STATE_ENUM@", ", ".join("S_" + key.upper() for key in STATE_FIELDS))
            .replace("@CALL_ENUM@", ", ".join("C_" + key.upper() for key in CALLS))
            .replace("@SPIES@", spies).replace("@INITIALIZER@", initializer).replace("@BODY@", body)
            .replace("@DATA@", data).replace("@POINTER_FIELDS@", ",\n".join(fields))
            .replace("@POINTER_CHECKS@", "\n".join(checks)))


HARNESS = r'''
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

enum StateField { @STATE_ENUM@, STATE_WORDS };
enum Call { C_UNUSED, @CALL_ENUM@ };
static_assert(STATE_WORDS == 37 && sizeof(UnitStackRecord) == 725);
static_assert(sizeof(WorldMapActionWidgetRecord) == 53);
static_assert(std::endian::native == std::endian::little);
using OverlayHook = int (__fastcall *)(_DWORD, _DWORD);
int gameData, g_SelectedUnitIndex, g_ActionButtonSpriteSet;
int g_BuilderRoadWidgetsInitialized, g_ActiveCursorDescriptor;
int g_RoadBuildModeExitRequested, g_RoadBuildModeHasBuildTarget;
int g_RoadBuildModeLastAnimationTick, g_RoadBuildModeAnimationFrameIndex;
int g_CursorDesc_Default[10], g_CursorDesc_ActionBusy[10];
char g_CursorCoordShift;
_DWORD g_RenderState[286];
OverlayHook g_WorldMapTileOverlayDrawHook;
alignas(4) _BYTE g_RoadBuildData[ROAD_BUILD_DATA_BYTES];
alignas(4) _BYTE g_UI_YesNoDims[BUILDER_ACTION_WIDGET_TABLE_BYTES];
alignas(16) static unsigned char arenas[2][150200];
static unsigned char road_reference[706], builder_reference[322];
static unsigned int case_index, event_index, diagnostic_calls, zero_clock_calls;
static unsigned int expected_clock_calls;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call, result; std::vector<Mutation> mutations; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "case=%u event=%u: %s\n", case_index, event_index, message);
  std::exit(1);
}

static uint32_t read_word(const void *address) {
  uint32_t result;
  std::memcpy(&result, address, 4);
  return result;
}
static void write_word(void *address, uint32_t value) { std::memcpy(address, &value, 4); }
static int initial_hook(_DWORD, _DWORD) { fail("initial hook invoked"); }
static int RoadBuildMode_HighlightBuildableAdjacentTile(_DWORD, _DWORD) { fail("highlight invoked"); }
static uint32_t cursor_class(uint32_t value) {
  if (!value) return 0;
  if (value == (uintptr_t)g_CursorDesc_Default) return 1;
  if (value == (uintptr_t)g_CursorDesc_ActionBusy) return 2;
  fail("unknown cursor pointer");
}
static int cursor_pointer(uint32_t value) {
  if (!value) return 0;
  if (value == 1) return (int)(uintptr_t)g_CursorDesc_Default;
  if (value == 2) return (int)(uintptr_t)g_CursorDesc_ActionBusy;
  fail("invalid cursor class");
}
static uint32_t hook_class() {
  if (!g_WorldMapTileOverlayDrawHook) return 0;
  if (g_WorldMapTileOverlayDrawHook == initial_hook) return 1;
  if (g_WorldMapTileOverlayDrawHook == RoadBuildMode_HighlightBuildableAdjacentTile) return 2;
  fail("unknown overlay hook");
}
static uint32_t get_state(uint32_t field) {
  const uint32_t marker_offsets[] = {180, 233, 286, 339};
  if (field >= S_ROW0_0 && field < STATE_WORDS) {
    const uint32_t index = field - S_ROW0_0;
    int16_t coordinate;
    std::memcpy(&coordinate, arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, 2);
    return (uint32_t)(int32_t)coordinate;
  }
  if (field >= S_VIEW_LEFT0 && field <= S_VIEW_TOP1) {
    const uint32_t index = field - S_VIEW_LEFT0;
    return read_word(arenas[index / 2] + MAP_VIEW_LEFT_OFFSET + (index % 2) * 4);
  }
  if (field >= S_NORTH_FLAGS && field <= S_WEST_FLAGS)
    return read_word(g_RoadBuildData + marker_offsets[field - S_NORTH_FLAGS]);
  switch (field) {
    case S_ARENA:
      if (gameData == (int)(uintptr_t)arenas[0]) return 0;
      if (gameData == (int)(uintptr_t)arenas[1]) return 1;
      fail("unknown game-state pointer");
    case S_SELECTED: return g_SelectedUnitIndex;
    case S_EXIT: return g_RoadBuildModeExitRequested;
    case S_TARGET: return g_RoadBuildModeHasBuildTarget;
    case S_TICK: return g_RoadBuildModeLastAnimationTick;
    case S_FRAME: return g_RoadBuildModeAnimationFrameIndex;
    case S_CURSOR: return cursor_class(g_ActiveCursorDescriptor);
    case S_HOOK: return hook_class();
    case S_CONTROL: return g_RoadBuildModeControlWidgetState;
    case S_RAW_X: return g_MouseCursorRawX;
    case S_RAW_Y: return g_MouseCursorRawY;
    case S_SHIFT: return (uint8_t)g_CursorCoordShift;
    case S_RENDER277: return g_RenderState[277] & 0xFFFFFF00u;
    default: fail("invalid state field");
  }
}
static void set_state(uint32_t field, uint32_t value) {
  const uint32_t marker_offsets[] = {180, 233, 286, 339};
  if (field >= S_ROW0_0 && field < STATE_WORDS) {
    const uint32_t index = field - S_ROW0_0;
    const uint16_t coordinate = (uint16_t)value;
    std::memcpy(arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, &coordinate, 2);
    return;
  }
  if (field >= S_VIEW_LEFT0 && field <= S_VIEW_TOP1) {
    const uint32_t index = field - S_VIEW_LEFT0;
    write_word(arenas[index / 2] + MAP_VIEW_LEFT_OFFSET + (index % 2) * 4, value);
    return;
  }
  if (field >= S_NORTH_FLAGS && field <= S_WEST_FLAGS) {
    write_word(g_RoadBuildData + marker_offsets[field - S_NORTH_FLAGS], value);
    return;
  }
  switch (field) {
    case S_ARENA:
      if (value > 1) fail("unbacked arena index");
      gameData = (int)(uintptr_t)arenas[value]; return;
    case S_SELECTED:
      if (value > 3) fail("unbacked selected index");
      g_SelectedUnitIndex = (int32_t)value; return;
    case S_EXIT: g_RoadBuildModeExitRequested = (int32_t)value; return;
    case S_TARGET: g_RoadBuildModeHasBuildTarget = (int32_t)value; return;
    case S_TICK: g_RoadBuildModeLastAnimationTick = (int32_t)value; return;
    case S_FRAME: g_RoadBuildModeAnimationFrameIndex = (int32_t)value; return;
    case S_CURSOR: g_ActiveCursorDescriptor = cursor_pointer(value); return;
    case S_HOOK:
      if (value > 2) fail("invalid hook class");
      g_WorldMapTileOverlayDrawHook = value == 1 ? initial_hook
          : value == 2 ? RoadBuildMode_HighlightBuildableAdjacentTile : nullptr; return;
    case S_CONTROL: g_RoadBuildModeControlWidgetState = (int32_t)value; return;
    case S_RAW_X: g_MouseCursorRawX = (int32_t)value; return;
    case S_RAW_Y: g_MouseCursorRawY = (int32_t)value; return;
    case S_SHIFT: g_CursorCoordShift = (char)(uint8_t)value; return;
    case S_RENDER277: g_RenderState[277] = (value & 0xFFFFFF00u) | 0xA5u; return;
    default: fail("invalid mutation field");
  }
}
static void snapshot() {
  for (uint32_t field = 0; field < STATE_WORDS; ++field) output.push_back(get_state(field));
}
static uint32_t boundary(uint32_t call, uint32_t a0=0, uint32_t a1=0,
                         uint32_t a2=0, uint32_t a3=0, uint32_t a4=0, uint32_t a5=0) {
  if (event_index >= script.size() || script[event_index].call != call) {
    std::fprintf(stderr, "actual call=%u expected=%u\n", call,
                 event_index < script.size() ? script[event_index].call : 0);
    fail("unexpected callee order");
  }
  output.insert(output.end(), {call, a0, a1, a2, a3, a4, a5});
  snapshot();
  const Event &item = script[event_index++];
  for (const Mutation &mutation : item.mutations) set_state(mutation.field, mutation.value);
  return item.result;
}
static uint32_t render_identity(int value) {
  if ((uint32_t)value != (uintptr_t)g_RenderState) fail("render argument is not the actual render state");
  return 1;
}
static uint32_t control_identity(uintptr_t value) {
  if (value != (uintptr_t)g_RoadBuildModeControlWidgets) fail("control argument is not its shared backing");
  return 1;
}
static signed int Map_GetTileSurfaceClassOrUnexplored(int row, signed int column) {
  return (int32_t)boundary(C_SURFACE, row, column);
}
static __int16 RenderState_SelectCursorDescriptor(int state, int cursor) {
  return (__int16)boundary(C_CURSOR, render_identity(state), cursor_class(cursor));
}
static int WorldMap_RedrawViewport(int present) { return (int32_t)boundary(C_VIEWPORT, present); }
static void Diagnostics_TraceWorldMapActionEvent(const char *stage, int selected, int control, int target, int detail) {
  if (++diagnostic_calls != 1 || event_index != 3 || script[2].call != C_VIEWPORT
      || std::strcmp(stage, "road_mode_enter") || selected != g_SelectedUnitIndex
      || control != g_RoadBuildModeControlWidgetState || target != g_RoadBuildModeHasBuildTarget || detail)
    fail("native entry diagnostic timing or arguments differ");
}
static unsigned int DD_Pump(int state, int carried, ...) {
  return boundary(C_PUMP, render_identity(state), carried, (uint8_t)carried);
}
static int WorldMap_HandleScrollKeysAndIdle(signed int argument, ...) {
  return (int32_t)boundary(C_SCROLL, argument);
}
static int WorldMap_RedrawFrame(int argument, ...) { return (int32_t)boundary(C_FRAME, argument); }
static int __fastcall Time_Now(int a1, int a2) {
  if (a1 || a2) fail("native ignored clock arguments must be explicit zeros");
  ++zero_clock_calls;
  return (int32_t)boundary(C_CLOCK);
}
static int WorldMap_RedrawTileIfVisible(int row, int column) { return (int32_t)boundary(C_TILE, row, column); }
static signed int UIWidgetTable_PollHoverAndActions(_DWORD *table, DWORD context) {
  return (int32_t)boundary(C_POLL, control_identity((uintptr_t)table), context);
}
static BOOL UI_TrySelectFriendlyStackUnderCursor(void) { return (int32_t)boundary(C_SELECT); }
static BOOL Render_Begin(int state, void (*callback)(void), ...) {
  if (callback) fail("Render_Begin callback must remain null");
  return (int32_t)boundary(C_BEGIN, render_identity(state), 0);
}
static BOOL DD_IsFlipping(int state) { return (int32_t)boundary(C_FLIPPING, render_identity(state)); }
static int RoadBuildMode_BuildInSelectedDirection(int widget, DWORD context, double value) {
  uint32_t marker = 0;
  const int offsets[] = {172, 225, 278, 331};
  for (uint32_t index = 0; index < 4; ++index)
    if ((uint32_t)widget == (uintptr_t)(g_RoadBuildData + offsets[index])) marker = index + 1;
  if (!marker) fail("build marker is not its actual shared record");
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_BUILD, marker, context, (uint32_t)bits, (uint32_t)(bits >> 32));
}
static int UIWidget_RefreshActionButtonState(uintptr_t widget, int argument) {
  return (int32_t)boundary(C_REFRESH, control_identity(widget), argument);
}
@SPIES@
@INITIALIZER@
@BODY@
@DATA@
struct PointerField { uint32_t table, offset, original; };
static const PointerField pointer_fields[] = {@POINTER_FIELDS@};
static void check_pointer(const void *field, uintptr_t expected) {
  if (expected > INT_MAX || read_word(field) != expected) fail("initializer symbol identity");
}
static void check_text(const void *field, const void *expected, size_t bytes) {
  const uintptr_t value = read_word(field);
  if (value < 0x10000 || value > INT_MAX || std::memcmp((const void *)value, expected, bytes))
    fail("initializer text identity");
}
static uint32_t hash_bytes(const void *address, size_t bytes) {
  const unsigned char *data = (const unsigned char *)address;
  uint32_t result = 2166136261u;
  for (size_t index = 0; index < bytes; ++index) result = (result ^ data[index]) * 16777619u;
  return result;
}
static void check_initialized_tables() {
  if (g_BuilderRoadWidgetsInitialized != 1) fail("initializer guard");
  for (size_t i = 0; i < sizeof original_road; ++i)
    if (!road_pointer_mask[i] && g_RoadBuildData[i] != original_road[i]) fail("initializer Road byte");
  for (size_t i = 0; i < sizeof original_builder; ++i)
    if (!builder_pointer_mask[i] && g_UI_YesNoDims[i] != original_builder[i]) fail("initializer Builder byte");
  @POINTER_CHECKS@
}
static void capture_initializer() {
  std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
  std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
  g_BuilderRoadWidgetsInitialized = 0;
  WorldMap_EnsureBuilderWidgetTables();
  check_initialized_tables();
  std::memcpy(road_reference, g_RoadBuildData, sizeof road_reference);
  std::memcpy(builder_reference, g_UI_YesNoDims, sizeof builder_reference);
}
static uint32_t read_input() {
  uint32_t result;
  if (std::fread(&result, 4, 1, stdin) != 1) fail("incomplete input fixture");
  return result;
}
static void finish(uint32_t result) {
  if (event_index != script.size()) fail("missing callee event");
  const bool accepted = script.front().result != 185;
  if (diagnostic_calls != (unsigned)accepted || zero_clock_calls != expected_clock_calls)
    fail("native-only diagnostic/clock contract");
  if (g_BuilderRoadWidgetsInitialized != 1) fail("initializer guard after handler");
  if ((g_RenderState[277] & 255) != 0xA5u) fail("native separate shift changed render byte");
  for (int value : g_CursorDesc_Default) if (value != 0x35353535) fail("default cursor storage modified");
  for (int value : g_CursorDesc_ActionBusy) if (value != 0x46464646) fail("busy cursor storage modified");
  output.push_back(result);
  snapshot();
  unsigned char road[706], builder[322], render[sizeof g_RenderState];
  std::memcpy(road, g_RoadBuildData, sizeof road);
  std::memcpy(builder, g_UI_YesNoDims, sizeof builder);
  for (const PointerField &field : pointer_fields) {
    unsigned char *actual = field.table ? g_UI_YesNoDims : g_RoadBuildData;
    const unsigned char *reference = field.table ? builder_reference : road_reference;
    if (read_word(actual + field.offset) != read_word(reference + field.offset)) fail("relocated pointer modified");
    write_word((field.table ? builder : road) + field.offset, field.original);
  }
  std::memcpy(render, g_RenderState, sizeof render);
  render[277 * 4] = 0;
  output.push_back(hash_bytes(road, sizeof road));
  output.push_back(hash_bytes(builder, sizeof builder));
  output.push_back(hash_bytes(arenas[0], sizeof arenas[0]));
  output.push_back(hash_bytes(arenas[1], sizeof arenas[1]));
  output.push_back(hash_bytes(render, sizeof render));
}
int main() {
  if ((uintptr_t)arenas + sizeof arenas > INT_MAX || (uintptr_t)g_RenderState + sizeof g_RenderState > INT_MAX)
    fail("fixture storage must fit positive signed low32");
  capture_initializer();
  const unsigned int count = read_input();
  for (case_index = 0; case_index < count; ++case_index) {
    const uint32_t cold = read_input(), context = read_input();
    const uint32_t low = read_input(), high = read_input(), events = read_input();
    if (!events || events > 96) fail("invalid event count");
    std::memcpy(g_RoadBuildData, road_reference, sizeof road_reference);
    std::memcpy(g_UI_YesNoDims, builder_reference, sizeof builder_reference);
    g_BuilderRoadWidgetsInitialized = 1;
    std::memset(arenas, 0x5A, sizeof arenas);
    std::memset(g_RenderState, 0xA5, sizeof g_RenderState);
    std::memset(g_CursorDesc_Default, 0x35, sizeof g_CursorDesc_Default);
    std::memset(g_CursorDesc_ActionBusy, 0x46, sizeof g_CursorDesc_ActionBusy);
    for (uint32_t field = 0; field < STATE_WORDS; ++field) set_state(field, read_input());
    if (cold) {
      std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
      std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
      g_BuilderRoadWidgetsInitialized = 0;
    }
    script.clear(); output.clear();
    event_index = diagnostic_calls = zero_clock_calls = expected_clock_calls = 0;
    for (uint32_t index = 0; index < events; ++index) {
      Event item;
      item.call = read_input(); item.result = read_input();
      const uint32_t mutations = read_input();
      if (mutations > STATE_WORDS) fail("invalid mutation count");
      if (item.call == C_CLOCK) ++expected_clock_calls;
      for (uint32_t mutation = 0; mutation < mutations; ++mutation) {
        const uint32_t field = read_input(), value = read_input();
        item.mutations.push_back({field, value});
      }
      script.push_back(item);
    }
    const double value = std::bit_cast<double>((uint64_t)low | ((uint64_t)high << 32));
    finish((uint32_t)Builder_StartRoadBuildMode(context, value));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace output failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing input bytes");
}
'''


class RoadBuildModeTest(unittest.TestCase):
    def check_compiler(self, candidates):
        compiler = next((shutil.which(name) for name in candidates if shutil.which(name)), None)
        if compiler is None:
            self.skipTest("required C++ compiler unavailable: " + ", ".join(candidates))
        provenance = json.loads((builder_road.FIXTURES / "build-mode-provenance.json").read_text())
        self.assertEqual(provenance["state_fields"], list(STATE_FIELDS))
        self.assertEqual(provenance["calls"], list(CALLS))
        self.assertEqual(provenance["event_words"], EVENT_WORDS)
        self.assertEqual(provenance["final_words"], FINAL_WORDS)
        records = cases()
        encoded = encode_cases(records)
        self.assertEqual(hashlib.sha256(encoded).hexdigest(), provenance["input_sha256"])
        self.assertEqual(len(records), len(provenance["case_trace_sha256"]))
        with tempfile.TemporaryDirectory(prefix="clash95-road-mode-") as temporary:
            directory = Path(temporary)
            source = directory / "road_mode.cpp"
            source.write_text(harness_source())
            for optimization in ("-O0", "-O2"):
                with self.subTest(compiler=compiler, optimization=optimization):
                    executable = directory / ("road-mode-" + optimization[1:])
                    command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", optimization,
                               "-fno-exceptions", "-fno-rtti", "-fno-pie", "-no-pie",
                               "-Wall", "-Wextra", "-Werror", "-fsanitize=undefined",
                               "-fno-sanitize=alignment", "-fsanitize-undefined-trap-on-error",
                               "-isystem", str(builder_road.REPO / "src"), str(source), "-o", str(executable)]
                    built = subprocess.run(command, capture_output=True, text=True, timeout=60)
                    self.assertEqual(built.returncode, 0, " ".join(command) + "\n" + built.stderr)
                    run = subprocess.run([str(executable)], input=encoded, capture_output=True, timeout=60)
                    self.assertEqual(run.returncode, 0, run.stderr.decode())
                    self.assertEqual(run.stderr, b"")
                    for case, observed, expected in zip(records, split_output(run.stdout, records),
                                                       provenance["case_trace_sha256"], strict=True):
                        self.assertEqual(hashlib.sha256(observed).hexdigest(), expected,
                                         case["name"] + ": original event/state/memory trace differs")
                    self.assertEqual(hashlib.sha256(run.stdout).hexdigest(), provenance["output_sha256"])

    def test_gcc_original_road_modal_contract(self):
        self.check_compiler(("g++-13", "g++"))

    def test_clang_original_road_modal_contract(self):
        self.check_compiler(("clang++-18", "clang++"))


if __name__ == "__main__":
    unittest.main()
