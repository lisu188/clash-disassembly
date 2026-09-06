# Campaign mission completion notes

Objectives decoded from `Mission_CheckObjectiveComplete`
(`src/strategic/004589C0_004602F0_strategic_004.cpp`),
switch on `ACTIVE_MISSION_INDEX`. Difficulty and tractability of the 14 partial missions:

| M | case | objective | tractable? |
|--:|--|--|--|
| 05 | 5 | eliminate all player-3 stacks+building | conquest (hard; see mission_05_WORKLOG.md) |
| 06 | 6 | castle @(90,41) owned by player 0 | capture (combat) |
| 07 | 7 | 4 hidden treasures collected + visible enemies killed | combat |
| 08 | 8 | castle @(30,23) garrison not SPECIAL_FOOT_PERSONAGE | combat |
| 09 | 9 | eliminate players 1..4 (`PLAYER_IS_ACTIVE` scan, offsets 1423..7115) | conquest (hard; first-campaign finale) |
| 10 | A | eliminate all player-2 stacks | conquest (hard) |
| 11 | B | religious site @(2,44) == EMPTY_CULT_PLACE | shrine (like M01; movement) |
| 12 | C | castle @(59,14) owned by player 1 (the human) | capture (crash resolved; see below) |
| 13 | D | GAME_TURN_COUNTER > 10 (survive) | **COMPLETE** (turn-advance, like M03) |
| 14 | E | castle @(52,24) owned by player 1 (the human) | capture; **fails at turn > 20** (case 0xE, strategic_004.c:1155) |
| 15 | F | eliminate all player-4 stacks | conquest (hard) |
| 16 | 10 | castle @(91,43) owned by player 1 (the human) | capture |
| 17 | 11 | 4 hidden treasures + kill visible non-player-1 | combat |
| 18 | 12 | castle @(85,38) garrison has >=6 SPECIAL_*_PERSONAGE | combat/garrison |
| 19 | 13 | eliminate players 0,2,3,4 (`PLAYER_IS_ACTIVE` scan skips player 1) | conquest (hard; second-campaign finale) |

Second-campaign correction (source-verified): `Scenario_LoadMissionByIndex`
cases 10..19 set `PLAYER_HAS_HUMAN_CONTROLLER(1) = 1`
(`src/strategic/00460360_00460910_strategic_005.cpp:603+`) — the human is
**player 1** in missions 10..19, so the "castle owned by player 1" objectives
in 12/14/16 are ordinary human capture missions, not ally-AI-dependent ones.
The 140024-region per-player dwords are the `PLAYER_IS_ACTIVE` flags
(`src/recovered_types.h:286`), zeroed on player elimination, which resolves
mission 09/19 objectives to standard conquest: case 9 scans offsets
1423..7115 (players 1..4); case 0x13 checks player 0 then 2846..7115
(players 2..4), skipping the human at offset 1423
(`src/strategic/004589C0_004602F0_strategic_004.cpp:933,1079`).

**Completed this session: mission 13** (`mission_13_turn_survival_route.script`, adapted
from the complete mission 03; key fix = replace racy `wait_log playgame_before_human_turn`
per-turn waits with fixed delays, since mission 13's turn events fire before the wait
registers). Campaign: 6/20 complete.

The remaining 14 are combat/capture routes (multi-session, iterative per
`mission_05_WORKLOG.md`) except the two survival missions (03, 13) now both done.

Mission 05 latest update (2026-09-06): both repaired compiler builds now
replay the seven-leg approach and actual Building → Road action to `(49,50)`,
turn 6, with 2 AP, roads 867/879 and 228 matching visibility tiles. The original
uses real Load of an unchanged engine-authored turn-6 checkpoint. All ten unit
slots and the complete visibility bitmap agree before/after construction.
Use `mission_05_first_road_probe.env`; normal refresh and the remaining bridge
are next. The separate original reaches `(47,58)` on turn 10; C++ arrival,
tactical entry and objective remain unproven. Historical transfer-based crossing
claims remain superseded. Mission 05 stays partial and direct-route completion
stays 6/20. See `mission_05_WORKLOG.md`.

Previous mission 05 update (2026-09-06): fresh original-backed fog validation rejects
the historical march's first destination `(47,58)` from the verified turn-1
state. The nine-turn arrival is retained as history, not a current validated
starting point. The visible-first-leg probe reaches `(67,47)` for 20 AP, and
the new visible-second-leg probe reaches `(63,49)` in turn 2 for 18 AP.
Both legs match the original's path, occupied-unit state and complete
visibility bitmap after the reveal and route-driver repairs. The reached
nation-score accumulator is also repaired; exact live inputs match original
instruction results, and both compiler builds complete this prefix. New partial
third/fourth/fifth probes extend it to `(55,53)` in turn 5 with 15 AP, an empty
path and 179 visible tiles matching the original. They include the natural
turn 4 AP stop at `(56,52)` and ordinary turn 5 queued-path resumption. The End
Turn fixture now waits for menu readiness before clicking; all failed earlier runs
remain recorded. Continue through accepted destinations and normal turn refresh
before tactical entry.
The 6/20 direct-route completion count is unchanged.

Mission 12 crash triage (2026-07-16, resolved): the reported turn-advance
SIGSEGV was NOT game code. The mission-state sampler
(`src/instrumentation/runtime_mission_trace.cpp`) still declared
`extern unsigned char gameData[]` and walked tables from the symbol's own
address, but the recovered state stores the game-state block as a 32-bit
pointer (`int gameData;`); the sampler's building walk started 16 bytes past
the mapped BSS and killed the process from its own thread whenever tracing
was enabled. With the sampler fixed to resolve the stored pointer, a
gdb-wrapped 40-turn end-turn probe (`mission_12_turn_advance_probe.script`)
completed with no fault and live `[mission-state]` evidence
(`artifacts/campaign-routes/mission-12/20260716T142538Z-77806`): players 1
and 2 active, target castle = building 0 at (59,14) garrison 1, eight
player-2 stacks (min_ap 20..26). Mission 12 is an ordinary capture route.
The July-13 `first_ap=255` metadata smell on unit types 15/16 remains a
separate open item for the unit-metadata tail recovery.

## Mission 10/11 AI-opponent unblock (2026-07-17, commit d8259eb)

Missions 10 and 11 hung after the human ended turn 1: the recovered
Scenario_LoadMissionByIndex cases 10/11 had dropped the asm's
PLAYER_HAS_HUMAN_CONTROLLER(2)=0 store (and religion(1)=0), and since
PlayerRuntimeState_ResetDefaults defaults every player to human=1, the AI
opponent (player 2) was treated as human and its turn waited for input
forever (world_003.c:339 -> WorldMap_RunHumanTurnLoop). Fixed to mirror the
asm store sequence; runtime-verified that player 2 now takes an AI turn.
Missions 10/11 are now PLAYABLE. Completing mission 11 (march the builder-led
stack from (22,15) to the cult place (2,44) and enter it -> EMPTY_CULT_PLACE)
is now route-tuning: use world_select_stack 0 per-turn resume
(mission_11_shrine_route), but each turn now includes player-2's AI turn, so
full runs take ~40 min wall-clock. Note case 12-19 already had their clears
(audited); only 10 and 11 were affected.
