# Campaign mission completion notes

Objectives decoded from `Mission_CheckObjectiveComplete`
(`src/strategic/004589C0_004602F0_strategic_004.c`),
switch on `ACTIVE_MISSION_INDEX`. Difficulty and tractability of the 15 partial missions:

| M | case | objective | tractable? |
|--:|--|--|--|
| 05 | 5 | eliminate all player-3 stacks+building | conquest (hard; see mission_05_WORKLOG.md) |
| 06 | 6 | castle @(90,41) owned by player 0 | capture (combat) |
| 07 | 7 | 4 hidden treasures collected + visible enemies killed | combat |
| 08 | 8 | castle @(30,23) garrison not SPECIAL_FOOT_PERSONAGE | combat |
| 09 | 9 | per-player flags at gameData+140024+1423k == 0 (k=1..4) | NOT passive (17 turns, unmet) |
| 10 | A | eliminate all player-2 stacks | conquest (hard) |
| 11 | B | religious site @(2,44) == EMPTY_CULT_PLACE | shrine (like M01; movement) |
| 12 | C | castle @(59,14) owned by player 1 (ally) | **CRASHES** (SIGSEGV in turn-advance) |
| 13 | D | GAME_TURN_COUNTER > 10 (survive) | **COMPLETE** (turn-advance, like M03) |
| 14 | E | castle @(52,24) owned by player 1 (ally) | ally doesn't capture passively |
| 15 | F | eliminate all player-4 stacks | conquest (hard) |
| 16 | 10 | castle @(91,43) owned by player 1 (ally) | ally does not capture passively |
| 17 | 11 | 4 hidden treasures + kill visible non-player-1 | combat |
| 18 | 12 | castle @(85,38) garrison has >=6 SPECIAL_*_PERSONAGE | combat/garrison |
| 19 | 13 | per-player flags (140024) all 0 | unclear |

**Completed this session: mission 13** (`mission_13_turn_survival_route.script`, adapted
from the complete mission 03; key fix = replace racy `wait_log playgame_before_human_turn`
per-turn waits with fixed delays, since mission 13's turn events fire before the wait
registers). Campaign: 6/20 complete.

The remaining 14 are combat/capture routes (multi-session, iterative per
`mission_05_WORKLOG.md`) except the two survival missions (03, 13) now both done.
Mission 12 has a runtime crash (SIGSEGV) during turn-advance to investigate separately.
