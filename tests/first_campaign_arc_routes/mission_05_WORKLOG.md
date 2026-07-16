# Mission 05 conquest route — worklog

Goal: recover an authentic route that reaches `mission_objective_complete` for mission
05 (`Mission_CheckObjectiveComplete` case 5). Status: **in progress** (route authoring).

## Current proven route milestone (2026-07-14)

The earlier one-turn tactical entry was diagnostic evidence built on a false
unit-metadata reconstruction. The original `byte_512570+` globals are fields
inside a 35-record table with an 88-byte stride; the one-element placeholders
made stack 4 appear to have `255` AP and eventually supplied an invalid attack
frame count. A direct first exchange then crashed after requesting sprite
character `50`. That route is retained as rejected pre-repair calibration, not
as an authentic Mission 05 milestone.

The executable-backed `+8..+37` metadata core now gives stack 4 a mixed-stack
AP floor of `20`. The passing `mission_05_march_probe` proves the corrected
first leg:

- direct stack selection logs
  `selected_stack_changed selected=4 a=71 b=44`;
- the same click at `(200,260)` builds the 33-node, 156-point path to `(47,58)`;
- the first turn stops normally at `(67,47)` with `0` AP and 29 queued nodes:
  `unit_move_stop_ap selected=4 a=0 b=3 c=29` and
  `unit_move_after_path_state selected=4 a=67 b=47 c=29`;
- a fresh nonblank frame and failure-safe marker are retained at
  `artifacts/campaign-routes/mission-05/20260714T153032Z-79880/summary.txt`.

The multi-turn probe establishes the authentic continuation rule from
`Unit_NewTurn` and the original assembly: new-turn processing only auto-runs a
queued path when a slot's ready bit is already set; it does not set that bit.
Mission 05 therefore requires real player input to reselect stack 4 and click
its centered tile each turn. Turns 2..6 resume through Next Unit. At turn 7 the
stack reaches `(47,50)`, where Next Unit's stricter one-step neighbor heuristic
rejects it, so the route pans to it and selects it directly. Turn 8 reaches
`(47,57)` with one four-point step left; turn 9 supplies the final AP refresh.
The complete replay passes with 145 routed inputs, nine objective-blocked
checks, no friendly-attack failure marker, and
`unit_move_after_path_state selected=4 a=47 b=58 c=0`. Its final checkpoint is
nonblank (`288723` nonblack pixels, `169` colors). Durable evidence is at
`artifacts/campaign-routes/mission-05/20260714T155159Z-98803/summary.txt`.

The current blocker is revalidating tactical entry and the first exchange only
after the corrected multi-turn arrival. The pre-repair tactical/autoresolve
scripts remain quarantined calibration files until their strategic prefix is
replaced. After stack 19, the authentic route must still clear stacks
`16..18`, `20`, owner-3 building 4, and remote stack `21` without attacking
owners `1` or `2`.

## Objective (from `src/strategic/004589C0_004602F0_strategic_004.c` case 5, nonzero-language branch)
Eliminate **every player-3 (Agordeh) world stack and building**. Two loops:
- LABEL_35 (`UNIT_RECORD` 0..99): a personage/stack record with `type<4`, alive
  (`+16 != -1`), owner==3 blocks.
- LABEL_42 (725-stride world records 0..499): a record with `+147180 <= 0x28`
  (alive) and `+147178 == 3` (owner 3) blocks.
Failure predicate: `Mission05_MarkFailureOnFriendlyAttack` — player 0 must **not**
attack players 1 or 2.

## Battlefield at mission load (from `[world_units]` trace, verified run 20260713T105904Z)
Player 0 (attacker) — clustered NE:
| stack idx | tile (row,col) | type | ap |
|--:|--:|--:|--:|
| 0 | 70,47 | 2 | 20 |
| 1 | 71,47 | 5 | 20 |
| 2 | 72,47 | 9 | 24 |
| 3 | 73,47 | 5 | 26 |
| 4 | 71,44 | 17 | 20 (mixed-stack floor) |
| 5 | 72,44 | 1 | 20 |

Player 3 (target) — cluster SW + one remote:
| stack idx | tile (row,col) | type | note |
|--:|--:|--:|--|
| 16 | 41,56 | 20 | cluster |
| 17 | 42,56 | 21 | cluster |
| 18 | 43,56 | 21 | cluster |
| 19 | 44,56 | 2 | cluster (type<4 → also a LABEL_35 blocker) |
| 20 | 42,53 | 10 | cluster |
| 21 | 87,66 | 21 | **remote** |
Plus **player-3 building index 4** (the persistent `objective_blocked a=4 b=3`).

Players 1 (tiles ~56,23 / 73,23) and 2 (tiles ~67-70,79 / 73,63 / 59,50): **do not attack.**

Confirmed: advancing turns without combat does NOT complete it — the blocker index
is stable across turns (no AI attrition of player 3). Player 0 must destroy them.

## Distances / plan
Player-0 cluster ~(71,46) → player-3 cluster ~(42,55): ~29 tiles W + 9 S. Remote
target (87,66) is ~40 tiles SE of the cluster. So: several turns of world movement to
close, then ~5 tactical stack battles at the cluster + 1 building capture, then a long
march to (87,66) for the last stack. Comparable to mission 04 (347 inputs).

## Input mechanics (from complete routes mission_00/mission_02)
- World: `click 496 416` = next-unit cycle; `click <mmX> <mmY>` on the minimap pans the
  view; `click <sx> <sy>` sets a move path to the tile under the cursor
  (`tile_input cursor=sx,sy tile=R,C` reports the mapping — use it to calibrate). End
  turn via the top-menu end-turn control; units advance along the path over turns.
- Battle: raw `click <sx> <sy> <reads>` + `key <scan> <reads>` sequences drive the
  attacker across the battlefield onto the defender (see `mission_00_stack9_battle.script`).
- Low-level game format (`CLASH95_WORLD_INPUT_SCRIPT` / `CLASH95_BATTLE_INPUT_SCRIPT`,
  parsed by `WorldMap_/Battle_RunInputScriptStep`): `wait N` / `move R C` / `down R C`
  / `up R C` / `click R C [reads]` / `key scan [reads]` / `pulse dx dy b1 b2 reads`.

## Historical calibration results (superseded AP/table state)

The sections below preserve the July 13 route-discovery chronology. Any `255`
AP or one-turn tactical statement in them predates the executable-backed
metadata core above and must not be used as current acceptance evidence.

### Run 20260713T110709Z (`mission_05_opening_probe`)
- `click 496 416` (next-unit) selects **stack idx4 @ (71,44)** — the mobile stack
  (`next_unit_selected selected=4 a=71 b=44 c=6`). Good starting unit.
- Screen→tile at the default post-load view (`left=67 top=41`, isometric):
  `(300,250)→(71,44)`, `(200,300)→(69,45)`, `(400,200)→(72,43)`, `(470,150)→(73,43)`.
  Approx: `row-col ≈ x/40 + 19`, `row+col ≈ ~115` (near-constant in y) — i.e. lower
  screen-x ⇒ lower row + higher col (the direction toward player 3 at 42,56).
  `tile_input` also reports `own_stack/enemy_stack/building/in_bounds` per tile —
  use `enemy_stack=1` to confirm a click lands on a player-3 stack before committing.
- The **default view shows player-0's area only**; player 3 is off-screen NW. Panning
  is required. `(470,150)` is NOT the minimap (it resolved to a world tile) — the
  minimap hot-region still needs locating (try the screen corners; mission_02 used
  `click 475 153` for its minimap but the panel layout differs per resolution/mission).

## Next steps
1. **Minimap located** (from `checkpoint-mission05-open-00-start.bmp`): it's the small
   globe icon in the HUD at approx screen **(430, 407)**, bottom-center. Confirm it pans
   (watch for a `left/top` change in the next `tile_input`), then calibrate the SW view.
   HUD note: player-0's red stacks render at the bottom-center of the world view; a
   **central castle** sits at ~screen (340,270) — verify its `building_owner`.
   **RESOLVED (run 20260713T111323Z):** the central castle is **player-0's OWN**
   building (`building_idx=0 building_owner=0 building_kind=2` at tile 71,45) — **no
   shortcut**; player-3 building idx4 is at their SW cluster, so the full march is
   required. Also: clicking the HUD globe at (420,400)/(430,407) produced **0
   `minimap_update`** — that is not the pan hot-region. Next: try world-edge scroll
   (cursor to screen borders) or the low-level `move R C` toward off-screen tiles, and
   check whether `autoresolve` (which complete routes deliberately avoid, per
   `mission_00_stack9`) can win the stack battles to avoid hand-tuning all 6.
2. March the mobile stack(s) to the cluster over N turns.
3. Author + tune one tactical battle per player-3 stack (win by contact, autoresolve off).
4. Capture player-3 building idx4; then march to (87,66) for stack 21.
5. Expect `mission_objective_complete selected=-1 a=5`; flip `mission_05.env` to complete.

## Pan calibration attempts (run 20260713T111724Z) — BOTH FAILED
- Solved the view transform: `R ≈ 0.005x - 0.01y + 72`, `C ≈ 0.0075x + 0.035y + 33`.
  Player 3 (42,56) → screen ≈ (-3280,+1360): far off-view, so **panning is mandatory**.
- Keyboard arrows (scan 203 left / 200 up, ×200 reads) did **not** move the view origin
  (`left=67 top=42` constant). Minimap globe (420-430,400-407) also did not pan.
- **Unsolved pan levers to try next:** (a) edge-scroll — hold the SDL cursor at a screen
  border (may need a `pulse`/`delta` that keeps the cursor pinned, not a click); (b)
  right-button drag; (c) find the true minimap panel (probe the full bottom HUD strip
  y>430 and the corners for a `minimap_update`); (d) a low-level `move R C` toward an
  off-screen tile may auto-scroll the view to follow the cursor. Panning must be solved
  before the march; then autoresolve (vs hand-tuned battles) is the next question.

## Pan/selection attempts 2-3 (runs ...112138Z, ...) — still blocked
- `world_pan_viewport` IS the pan cmd (harness presses arrow keys 205/203/208/200 until
  the `[world_cursor]` left/top reaches target). mission_04 datum: select stack0
  (`platform_up 320 368` → `selected_stack_changed selected=0 a=41 b=50`) THEN
  `world_pan_viewport 47 65 160`. So **a stack must be selected before panning.**
- My selection attempts failed: `platform_up 300 250` hit tile (71,45) which has
  `own_stack=0` (my stacks are at cols 44 & 47, not 45). Transform to hit a real stack,
  e.g. idx1 @ tile(71,47): screen ≈ (420,310); idx4 @ (71,44): ≈ (300,250) but the
  mapping drifts run-to-run (saw (300,250)→(71,44) then →(71,45)), so selection needs
  a verify-and-retry loop (click, check `selected_stack_changed`, nudge, repeat).
- Net: **pan still unsolved for mission 05** after 3 runs — blocked on reliable stack
  selection first. This is the crux of why each mission is many iterations.

## PAN MECHANISM SOLVED (run 20260713T112647Z)
**`next-unit` (click 496 416) to select a stack, THEN `world_pan_viewport` — pans.**
With idx4 selected (`next_unit_selected selected=4`), the viewport moved
`left 67→65→63 top 42→41` in the correct direction toward player 3 (rows 41-44).
Earlier pan failures were solely the missing selection.
- Direction: decreasing `left` heads toward player 3; est. target for the player-3
  view ≈ **left~38, top~53** (extrapolating tile(71,44)@view(67,42) → tile(42,55)).
- Caveat: the harness `world_pan_viewport` loop stalled after ~3 steps (its per-step
  `move 319 239` cursor-reprobe timed out on a long pan). Fix for next run: pan in
  smaller increments (several `world_pan_viewport` calls of a few steps each), or raise
  the route timeout well above the ~(steps × 6s) the reprobe loop needs (~25 steps → 150s+).
- **This unblocks the march**: once the view shows player 3, `world_click` a path tile
  toward them (verify `enemy_stack=1`/adjacency), end turn, repeat; then attempt
  autoresolve per stack. The selection→pan→march→battle loop is now unblocked end-to-end.

## STACK-19 ATTACK CALIBRATED FROM THE AUTHENTIC ARRIVAL (2026-07-16)

`mission_05_stack19_from_arrival_probe.{script,env}` composes the proven
145-input march via `include_script`, ends turn 9, reselects stack 4 on turn
10 (refreshed 20 AP), pans, and attacks stack 19. Two calibration facts:

- **Screen center resolves to tile `(left+4, top+3)`** (run 20260716T192728Z:
  pan target 44,56 put the center click on 48,59 and ordered a plain move).
  Pan to `left=40 top=53` puts stack 19's tile (44,56) under the center click,
  which then yields `enemy_attack_call selected=4 a=19 b=44 c=56`.
- Prerequisite: the world_pan_viewport regression was repaired first (commit
  7fabf98 — recovered scroll-gate init + `CLASH95_PAN_KEY_PULSE_READS` budget;
  the runtime drains ~10.6 input polls per frame).

**Autoresolve decision (run 20260716T194132Z-165364): REJECTED.** Forced
autoresolve of stack 4 (6 units, mixed, 20-AP floor) vs stack 19 (10 units):
`unit_attack_autoresolve selected=4 a=19 b=6 c=10` →
`unit_attack_autoresolve_done selected=4 a=19 b=0 c=10` — the attacker is
annihilated, the defender keeps all 10 units, and stack index 4 disappears
from the player-0 AP table while target_remaining stays 7. The route flow
itself (march → end-turn → reselect → pan → attack → battle prompt →
return) is deterministic across two consecutive full-chain passes.

**Cluster playbook consequence:** stacks 16-20 need manual tactical battles
(the mission-04 approach) and/or a multi-stack support march before contact;
single-stack autoresolve is not viable. Next: author the tactical-entry
branch at the battle prompt (battle-input channel) for stack 19 with stack 4,
or first mass stacks 0-3 at the (47,58) staging tile.

Note for trace consumers: the mission-state sampler's per-run log can be
capped by the durable-log head/tail retention; raise
`CLASH95_CAMPAIGN_ROUTE_LOG_TAIL_LINES` (this probe uses 20000) when the
post-battle table is the evidence.

## MANUAL TACTICAL ENTRY PROVEN (2026-07-16, run 20260716T194745Z-170502)

`mission_05_stack19_tactical_entry_probe.{script,env}`: the calibrated attack
chain with `click 276 158` (manual-battle button; autoresolve sits at
354,158) enters the stack-19 tactical battle deterministically:
`unit_attack_battle_enter selected=4 a=19` -> `battle_turn_loop_after_input_widgets
selected=5 a=0 b=1` + nonblank battlefield screenshot.

Opening deployment (`[battle_units] after_deploy_defender`):
- Player 0 (attacker, 6 units, row 14): idx0/1 type 1 ap=20 @(14,3),(14,4);
  idx2..5 type 17 ap=26 @(14,2),(14,5),(14,1),(14,6).
- Player 3 (defender, 10 units, rows 0-1): idx6 type 6 ap=32 @(1,3);
  idx7..11 type 20 ap=26 @(1,4),(1,2),(1,5),(1,1),(1,6);
  idx12..15 type 2 ap=20 @(1,0),(0,3),(0,4),(0,2).
- Initial selected unit after restore = idx 5; stray world-channel click
  residue produced harmless `battle_move_execute_no_flip selected=5 a=13 b=3
  c=-1` rejections (keep battle scripts free of leftover pulses).

Next: author the squad choreography from this table (battle_click/battle_key
on the battle channel; the quarantined probe's coordinates predate this
deployment and must be re-derived from the battlefield screenshot
checkpoint-mission05-stack19-tactical-open.bmp).

## BRIDGE-CROSSING MECHANIC DECODED (2026-07-16) - THE ARMY ROUTE ANSWER

Army waypoints to the SW cluster fail with `move_order_track_result c=-1`
for stacks 0/1 (heavy/cavalry) while builder stack 4 paths with c=33.
Source-traced root cause (no per-type water flag differs - all land types
have water=0 in `g_UnitTypeWorldMoveCosts`):

- Every pathfinding entry point brackets the search with
  `UnitStack_HasBuilder(stack)` -> `Pathing_EnableBridgeCrossings` /
  `Pathing_DisableBridgeCrossings` (world_001.c:939-955; strategic_002.c
  AI callers likewise). The `bridge_pathing_disable_move` marker is that
  bracket closing, not an error.
- The gate: `UnitStack_GetTileMoveCostFromMergedProfileOrZero`
  (units_003.c:1408-1413) - with `g_PathingAllowBridgeCrossings` set,
  `Map_GetBridgeCrossingCostOrZero` (buildings_005.c:867-878) returns cost 5
  for bridge terrain ids 0x25B..0x262; without it the water profile cost 0
  makes the tile a wall.
- `UnitStack_HasBuilder` (units_002.c:327-348) = any of the 10 slots holds
  UNIT_TYPE_BUILDER (17). The merged stack profile takes the most-restricted
  member, so composition cannot unlock water - only the builder flag opens
  bridges.
- Permanent fix: the builder action `Road_Build` (buildings_005.c:882) lays
  bridge road-overlay ids onto the tile record; the road branch
  (units_003.c:1406) then prices it for EVERY stack.
- Path length is uncapped for this purpose (buffer holds 100 waypoints);
  33 nodes is just the natural route.

Consequences for the completion route:
1. `mission_05_army_march_probe` as-written cannot work: (47,58)/(46,57)
   are across the water; no overland route exists for builder-less stacks.
2. Two authentic options: (a) transfer one builder from stack 4 into each
   combat stack (stack-merge/transfer UI - mechanics to discover), giving
   them temporary crossing rights; or (b) march stack 4 to the bridge site
   and Road_Build the permanent overlay, then march the army across.
3. `mission_05_pathing_class_probe` records the c=-1 evidence for stacks
   1 (cavalry lead) and 5; stack-5's leg needs next-unit cycling repair if
   rerun.

This also explains the original 33-node builder march: the route crosses
the bridge tiles that only stack 4 could enter.

## SPLIT/TRANSFER UI DECODED + BUILDER TRANSFER PROVEN (2026-07-16)

`mission_05_stack_transfer_probe.{script,env}` iterations 1-10 recovered the
unit-transfer mechanics end to end (code + live proof):

- Screen->tile transform near the pinned view (left,top):
  row ~= left + 4 + (x-320)/80, col ~= top + 3 + (y-240)/40 with isometric
  stagger - ALWAYS pin the view (world_pan_viewport) and verify targets with
  a world_move cursor sample first; the post-selection view drifts (67 vs 68)
  because selection auto-scrolls.
- next-unit order is stack 0..5 on turn 1 (5 clicks select stack 4);
  turn-2 cycling differs (first click landed on 2/3) - selection needs the
  marked-wait pattern per turn.
- (69,46) is a temple site: clicking it runs the temple pathing bracket
  (bridge_pathing_enable_temple / temple_track_request c=728 /
  temple_path_queued) - avoid in movement scripts.
- The bottom status panel (y~=400) shows the selected stack's slots at
  40px/portrait: x=160 -> slot 3, 200 -> 4, 240 -> 5; clicking toggles
  selection_slot_toggle (buildings_005.c:486-492).
- THE SPLIT FLOW (buildings_005.c:532-570): with slots toggled, a world
  click within distance<=1 of the selected stack fires
  selection_split_attempt -> Unit_MoveSelectionFromGroupToTile ->
  selection_split_done, moving the toggled units onto the target tile and
  merging into an own stack standing there.
- PROOF (run 20260716T202103Z-184484): stack 4 moved to (70,46); slot 5
  toggled; split-click on (70,47) fired selection_split_attempt/done; the
  turn-2 world_units table shows stack 0 slots 9 -> 10 and stack 4 slots
  6 -> 5. One unit transferred into the combat stack.

Remaining verification: whether the transferred slot was a Builder - the
one-marker test is `bridge_pathing_enable_move selected=0` on a cross-water
waypoint from stack 0 (fires only when UnitStack_HasBuilder). Iterations
9-10 stalled on turn-2 stack-0 selection (turn-2 next-unit cycling starts
mid-list and tile-click selection needs an existing selection for the pan);
next run selects stack 0 with the marked next-unit pattern before the
crossing waypoint. If slot 5 was not the builder, toggle slots 0-4 in turn.

Route plan once verified: transfer one builder each into stacks 0/1/3,
multi-turn march the builder-carrying army across the bridge to the SW
staging tiles, manual tactical battles per cyclop stack (autoresolve
rejected), capture building 4, then the remote stack 21 at (87,66).

## BUILDER TRANSFER + ARMY CROSSING PROVEN END-TO-END (2026-07-16)

Run 20260716T203603Z-191466 (`mission_05_stack_transfer_probe` iteration 14)
completes the whole unlock chain in one deterministic same-turn script:

1. select stack 4 (5x next-unit, marked wait);
2. center-click idiom: `world_pan_viewport (row-4) (col-3)` then
   `click 320 240` for every tile action (the view follows moving units, so
   re-pin before each targeted click - absolute coordinates are only valid
   immediately after a pan);
3. move stack 4 to (70,46); toggle BUILDER slot 0 (portrait x=40; slot 5 at
   x=240 is a LightInfantry - builders occupy the low slots, matching
   world `first=17`); split-click stack 0's tile -> selection_split_done;
4. same-turn: center-click stack 0's tile -> selected_stack_changed
   selected=0 (clicking another own stack's tile with a selection active
   selects it); pan 43 55; center-click ->
   `bridge_pathing_enable_move selected=0` +
   `move_order_track_result selected=0 a=47 b=58 c=32`.

The 10-slot combat stack (9 heavies + 1 builder) paths 32 nodes across the
water. Negative control retained: iteration 13 (slot 5 = light infantry)
got c=-1 with no bridge marker.

Completion-route assembly from here (all mechanics proven): transfer one
builder each into stacks 0/1/3 on turn 1, confirm the crossing waypoints,
multi-turn resume marches (existing per-turn playbook), then per-stack
manual tactical battles at the cluster, building 4 capture, and the remote
stack 21 leg.

## ARMY CROSSING IN MOTION (2026-07-16, run 20260716T204536Z-195584)

`mission_05_army_crossing_probe.{script,env}` = the proven iteration-14
unlock chain (builder transfer into stack 0) + per-turn resume marches.
Stack 0 (10 slots incl. the transferred builder) crossed the water it was
walled off from before the transfer:
  (70,47) -> ... -> (67,47) -> (51,49) -> (47,50)
i.e. it traversed the bridge tiles onto the SW side over ~6 turns. This
confirms the builder-transfer bridge unlock carries into a real multi-turn
march, not just a single waypoint query.

Failure point (script:132): a later turn's `next_unit_selected selected=0`
never fires - once stack 0 spends all AP for a turn, the next-unit cycle
SKIPS it (only ready stacks are in rotation), so the fixed single-click
resume lands on stack 1. This is the documented manual-reselection problem.
FIX for the next iteration: resume stack 0 by CENTER-CLICK on its current
tile (select-by-tile works regardless of AP/ready state, per the transfer
probe), not by next-unit cycling; read stack 0's live tile each turn from
the [mission-state]/[world_units] trace and pan+click it. Alternatively give
each combat stack a builder and march them together so a single next-unit
resume advances the whole column.
