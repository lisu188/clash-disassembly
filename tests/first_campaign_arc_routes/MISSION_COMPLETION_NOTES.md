# Campaign mission completion notes

Objectives decoded from `Mission_CheckObjectiveComplete`
(`src/strategic/004589C0_004602F0_strategic_004.c`),
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
| 12 | C | castle @(59,14) owned by player 1 (the human) | **CRASHES** (SIGSEGV in turn-advance) |
| 13 | D | GAME_TURN_COUNTER > 10 (survive) | **COMPLETE** (turn-advance, like M03) |
| 14 | E | castle @(52,24) owned by player 1 (the human) | capture; **fails at turn > 20** (case 0xE, strategic_004.c:1155) |
| 15 | F | eliminate all player-4 stacks | conquest (hard) |
| 16 | 10 | castle @(91,43) owned by player 1 (the human) | capture |
| 17 | 11 | 4 hidden treasures + kill visible non-player-1 | combat |
| 18 | 12 | castle @(85,38) garrison has >=6 SPECIAL_*_PERSONAGE | combat/garrison |
| 19 | 13 | eliminate players 0,2,3,4 (`PLAYER_IS_ACTIVE` scan skips player 1) | conquest (hard; second-campaign finale) |

Second-campaign correction (source-verified): `Scenario_LoadMissionByIndex`
cases 10..19 set `PLAYER_HAS_HUMAN_CONTROLLER(1) = 1`
(`src/strategic/00460360_00460910_strategic_005.c:603+`) — the human is
**player 1** in missions 10..19, so the "castle owned by player 1" objectives
in 12/14/16 are ordinary human capture missions, not ally-AI-dependent ones.
The 140024-region per-player dwords are the `PLAYER_IS_ACTIVE` flags
(`src/recovered_types.h:286`), zeroed on player elimination, which resolves
mission 09/19 objectives to standard conquest: case 9 scans offsets
1423..7115 (players 1..4); case 0x13 checks player 0 then 2846..7115
(players 2..4), skipping the human at offset 1423
(`src/strategic/004589C0_004602F0_strategic_004.c:933,1079`).

**Completed this session: mission 13** (`mission_13_turn_survival_route.script`, adapted
from the complete mission 03; key fix = replace racy `wait_log playgame_before_human_turn`
per-turn waits with fixed delays, since mission 13's turn events fire before the wait
registers). Campaign: 6/20 complete.

The remaining 14 are combat/capture routes (multi-session, iterative per
`mission_05_WORKLOG.md`) except the two survival missions (03, 13) now both done.
Mission 12 has a runtime crash (SIGSEGV) during turn-advance to investigate separately.
