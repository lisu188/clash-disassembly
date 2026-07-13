# Mission 05 conquest route — worklog

Goal: recover an authentic route that reaches `mission_objective_complete` for mission
05 (`Mission_CheckObjectiveComplete` case 5). Status: **in progress** (route authoring).

## Objective (from `src/rules/100_strategic.inc.c` case 5, nonzero-language branch)
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
| 0 | 70,47 | 2 | 0 |
| 1 | 71,47 | 5 | 0 |
| 2 | 72,47 | 9 | 0 |
| 3 | 73,47 | 5 | 0 |
| 4 | 71,44 | 17 | 255 (mobile) |
| 5 | 72,44 | 1 | 0 |

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

## Calibration results (run 20260713T110709Z, `mission_05_opening_probe`)
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
1. Locate the minimap hot-region (probe screen corners, watch for `minimap_update`
   instead of `tile_input`), OR pan by clicking near-edge tiles + end-turn to walk the
   view. Then calibrate screen→tile for the SW cluster view.
2. March the mobile stack(s) to the cluster over N turns.
3. Author + tune one tactical battle per player-3 stack (win by contact, autoresolve off).
4. Capture player-3 building idx4; then march to (87,66) for stack 21.
5. Expect `mission_objective_complete selected=-1 a=5`; flip `mission_05.env` to complete.
