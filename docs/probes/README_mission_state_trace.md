# Mission state trace

`src/instrumentation/runtime_mission_trace.cpp` provides a read-only, opt-in sampler
for campaign route investigations. It does not modify objective state, ownership,
units, buildings, turn progression, input, or rendering.

The mission `05` route enables the sampler to expose the state that currently blocks natural completion: the active strategic turn plus every live building and world stack owned by player `3`.

## Enable the sampler

```sh
export CLASH95_TRACE_MISSION_STATE=1
export CLASH95_TRACE_MISSION_ID=5
export CLASH95_TRACE_MISSION_TARGET_PLAYER=3
export CLASH95_TRACE_MISSION_AP_PLAYER=0
export CLASH95_TRACE_MISSION_INTERVAL_MS=250
```

The mission and target-player values default to `5` and `3`. The AP player
defaults to the human controller for the traced mission (player `1` for
missions `10..19`, player `0` otherwise); `-1` disables the AP stack walk.
The interval accepts `20..10000` milliseconds.

The sampler resolves the game-state block through the recovered 32-bit
pointer store (`int gameData;` in the state TU) each sample; before the block
is allocated it idles. (An earlier revision read the symbol's own address as
if it were the block and never produced valid data after the pointer-store
recovery; with the current byte-exact BSS layout that read also ran past the
mapped region and crashed the process inside the sampler thread when the
building walk started.)

The route environment file `tests/first_campaign_arc_routes/mission_05.env` enables these settings automatically for the canonical partial probe.

## Output

The sampler emits only when two consecutive reads agree and the resulting fingerprint differs from the last emitted snapshot.

```text
[mission-state] sampler_start mission=5 target=3 ap_player=0 interval_ms=250
[mission-state] mission=5 turn=12 owner=1 target=3 buildings=1 stacks=2 garrison_units=4 world_units=7 target_remaining=3
[mission-state] players active=1,1,1,1,0 ap_player=0 ap_stacks=5
[mission-state] building index=4 owner=3 row=44 column=28 construction=0 garrison=4
[mission-state] stack index=6 owner=3 row=87 column=66 units=3 min_ap=0
[mission-state] ap_stack index=4 owner=0 row=47 column=58 units=2 min_ap=20
```

`target_remaining` is the number of live target-owned building and world-stack records. It is diagnostic evidence, not a replacement for `Mission_CheckObjectiveComplete` or the existing `mission_objective_complete` route marker.

`players active=` mirrors the five `PLAYER_IS_ACTIVE` dwords at
`gameData+140024` stride `1423` — the flags the mission `09`/`19` conquest
objectives scan and player elimination zeroes. `min_ap` is the minimum
occupied-slot action-point byte (`UNIT_SLOT_ACTION_POINTS`, slot offset `+8`)
for the stack; `ap_stack` lines list the AP player's stacks for route
action-point budgeting.

The sampler uses the maintained recovered layouts:

- `WorldViewState.active_mission_index`, `game_turn_counter`, and `turn_owner_player_index`;
- 100 `BuildingRecord` entries at stride `467`;
- 500 `UnitStackRecord` entries at stride `725`;
- 12 building-garrison slots and 10 world-stack slots at stride `31`.

## Validation

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target runtime_mission_trace_tests -j2
ctest --test-dir build -R '^runtime_mission_trace_tests$' --output-on-failure
```

The synthetic test verifies target-player filtering, mission/turn fields, building and stack counts, garrison and world-unit counts, the five player-active flags, AP-player stack collection and min-AP fingerprint sensitivity, AP-walk disablement, and invalid target/AP-player rejection.
