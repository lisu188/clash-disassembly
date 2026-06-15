# First Mission Stack6 Manual Probe

Current verified route evidence:

- The first-mission world-map route can reach the stack6 objective path after stack5 is handled.
- Autoresolve against stack6 can remove player stack 10 before the objective completes.
- Choosing the manual battle prompt for stack6 reaches the recovered tactical battle loop with nonblank SDL frames.

The current goal is to keep the route authentic while finding a tactical sequence that defeats or survives stack6. Do not bypass the recovered world-map attack, battle prompt, or tactical battle loop.

## Environment Check

These probes are intended to run inside the WSL repo workspace. Before chasing script failures, confirm the shell can see the distro and repo:

```bash
pwd
test -x build/bin/clash95_bootstrap
bash --version
```

From Windows, `wsl -l -v` must list the `Ubuntu` distro used by this repo. If `\\wsl.localhost\Ubuntu` is inaccessible or WSL reports no default distro, validate the environment before debugging the game route.

## Quick Run

```bash
bash tests/validate_stack6_probe_suite.sh build/bin/clash95_bootstrap
```

The focused runner enables the `stack6-manual` expected-log preset by default. Use `stack6-manual-actions` when the run should also require tactical next-unit and prepare-defence UI actions.

Run both candidate matrices after the focused probe with:

```bash
CLASH95_VALIDATE_STACK6_MATRICES=1 \
  bash tests/validate_stack6_probe_suite.sh build/bin/clash95_bootstrap
```

Dry-run syntax checks and matrix file discovery without launching the game:

```bash
CLASH95_VALIDATE_STACK6_DRY_RUN=1 \
  bash tests/validate_stack6_probe_suite.sh build/bin/clash95_bootstrap
```

After a run, summarize the kept artifact directory:

```bash
bash tests/summarize_stack6_probe_artifact.sh /tmp/clash95-first-mission-move.XXXXXX
```

## Leave Runtime Open

```bash
CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING=1 \
  bash tests/run_first_mission_stack6_manual_probe.sh build/bin/clash95_bootstrap
```

This leaves the authentic SDL process alive at the reached milestone for manual play or debugger attachment.

The focused runner sets `CLASH95_FIRST_MISSION_MOVE_LEAVE_RUNNING_EXPECT_PATTERN="manual battle input loop reached"` by default in this mode, so it should only leave the process alive after the stack6 tactical loop is reached. Override that variable for a different checkpoint.

## Tactical Sequence File

```bash
CLASH95_STACK6_CHASE_MANUAL_TACTICAL_SEQUENCE_FILE=tests/stack6_manual_tactical_sequence.example \
  bash tests/run_first_mission_stack6_manual_probe.sh build/bin/clash95_bootstrap
```

Sequence tokens:

- `wait,reads,gap`
- `key,scan_code,reads,expected_pattern,timeout,gap`
- `battle-click,x,y,expected_pattern,timeout,reads,gap`
- `pulse,dx,dy,expected_pattern,timeout,left,right,reads,gap`
- `next-unit`
- `defence`
- `shoot`
- `charge`
- `retreat`
- `exit`

Expected patterns in sequence tokens must be a single shell word. Use `CLASH95_STACK6_CHASE_MANUAL_BATTLE_EXPECT_PATTERN` or `CLASH95_FIRST_MISSION_MOVE_EXPECT_LOGS_FILE` for patterns containing spaces.

## Tactical Sequence Matrix

```bash
bash tests/run_first_mission_stack6_sequence_matrix.sh \
  build/bin/clash95_bootstrap \
  tests/stack6_sequences
```

The matrix runner executes the same authentic route once per sequence file. It is intentionally slow; the point is to gather comparable runtime evidence without editing the harness between candidates. By default it requires the broader `stack6-manual` milestone; named sequence steps still assert their own action markers.

Use `CLASH95_STACK6_SEQUENCE_MATRIX_STOP_ON_PASS=1` when searching for a stricter success pattern, for example a future stack6 objective advance or `mission_objective_complete`.
Use `CLASH95_STACK6_SEQUENCE_MATRIX_DRY_RUN=1` to list candidate files without launching the game.
The sequence matrix checks `CLASH95_STACK6_SEQUENCE_MATRIX_EXPECT_PATTERN` after each tactical sequence has run.

Generate a battlefield-click candidate set:

```bash
bash tests/generate_stack6_battlefield_click_sequences.sh /tmp/stack6-clicks
CLASH95_STACK6_SEQUENCE_MATRIX_EXPECT_PATTERN=mission_objective_complete \
CLASH95_STACK6_SEQUENCE_MATRIX_STOP_ON_PASS=1 \
  bash tests/run_first_mission_stack6_sequence_matrix.sh \
    build/bin/clash95_bootstrap \
    /tmp/stack6-clicks
```

The generator defaults to a coarse on-screen grid. Tune `CLASH95_STACK6_GENERATE_X_VALUES` and `CLASH95_STACK6_GENERATE_Y_VALUES` for narrower sweeps once frame evidence identifies the relevant battlefield region.

Use `CLASH95_STACK6_GENERATE_PRELUDE` to put setup steps before every generated click:

```bash
CLASH95_STACK6_GENERATE_PRELUDE="wait,20,0.4 next-unit" \
  bash tests/generate_stack6_battlefield_click_sequences.sh /tmp/stack6-clicks-after-next
```

```bash
CLASH95_STACK6_SEQUENCE_MATRIX_EXPECT_PATTERN=mission_objective_complete \
CLASH95_STACK6_SEQUENCE_MATRIX_STOP_ON_PASS=1 \
  bash tests/run_first_mission_stack6_sequence_matrix.sh \
    build/bin/clash95_bootstrap \
    tests/stack6_sequences
```

## Raw Battle Input Script

```bash
CLASH95_STACK6_CHASE_MANUAL_BATTLE_SCRIPT_FILE=tests/stack6_manual_battle_script.example \
  bash tests/run_first_mission_stack6_manual_probe.sh build/bin/clash95_bootstrap
```

Raw commands are appended to `CLASH95_BATTLE_INPUT_SCRIPT` after `battle_turn_loop_after_input_widgets` is reached.

## Raw Battle Script Matrix

```bash
bash tests/run_first_mission_stack6_battle_script_matrix.sh \
  build/bin/clash95_bootstrap \
  tests/stack6_battle_scripts
```

This uses the same authentic route as the tactical sequence matrix, but feeds raw `CLASH95_BATTLE_INPUT_SCRIPT` payloads after the recovered battle loop is reached.

Use `CLASH95_STACK6_BATTLE_SCRIPT_MATRIX_STOP_ON_PASS=1` to stop as soon as a raw battle-script candidate satisfies the configured expected logs.
Use `CLASH95_STACK6_BATTLE_SCRIPT_MATRIX_DRY_RUN=1` to list candidate files without launching the game.
The raw battle-script matrix checks `CLASH95_STACK6_BATTLE_SCRIPT_MATRIX_EXPECT_PATTERN` after each battle script is appended.

```bash
CLASH95_STACK6_BATTLE_SCRIPT_MATRIX_EXPECT_PATTERN=mission_objective_complete \
CLASH95_STACK6_BATTLE_SCRIPT_MATRIX_STOP_ON_PASS=1 \
  bash tests/run_first_mission_stack6_battle_script_matrix.sh \
    build/bin/clash95_bootstrap \
    tests/stack6_battle_scripts
```
