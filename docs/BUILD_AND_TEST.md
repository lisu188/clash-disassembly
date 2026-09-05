# Build And Test

Run commands from the repository root in Linux or WSL. For the Windows checkout,
start a WSL shell and use `/mnt/c/Users/andrz/git/clash-disassembly`. Keep runtime
execution headless; never launch either game binary on the host desktop.

## Prerequisites

The build requires CMake 3.28+, Ninja, pkg-config, Python 3, SDL2 and X11
development libraries, and a GNU C17 compiler. Public CI checks GCC 13 and
Clang 18. On Ubuntu 24.04/WSL the build packages are:

```sh
sudo apt-get update
sudo apt-get install -y cmake ninja-build pkg-config python3 \
  gcc-13 clang-18 libsdl2-dev libx11-dev
```

The current WSL environment has CMake 3.28.3, GCC 13.3.0, Clang 18.1.3,
Ninja 1.11.1, SDL2 2.30.0, X11 1.8.7, and Python 3.12.3.
Runtime probes additionally use Xvfb, xauth, and xdotool; original-binary frame
comparison uses Wine with 32-bit support, ImageMagick `import`, and `xwd`
(`x11-apps`). These tools are installed locally. Actual boot, menu, and campaign
work also requires the retail game data at `/mnt/c/clash`; an empty directory
does not suffice. Public CI must neither require nor publish those assets.

## Original Wine Capture Environment

For a writable private runtime session, set `CLASH95_GAME_ROOT` to an existing
absolute Linux directory containing the runtime assets and its own `save/`
directory. A valid override owns relative lookups, including case folding,
even when a matching cwd path exists. Unset or invalid values retain the
`/mnt/c/clash` default. Explicit absolute paths and symlinks retain their usual
meaning; the selector is not a filesystem sandbox. Do not symlink writable
saves into the retail installation. The asset-free regression and verified
engine-authored mission05 snapshot are documented under
`artifacts/structure-recovery/tactical-validation-20260905/asset-root.md`.

On this WSL installation, run an unchanged copy of the original executable
from a unique Linux-native directory, with an isolated 32-bit Wine prefix and
the documented CD drive mapping. Running its executable directly from the
Windows-backed filesystem mapped zero bytes at the sampled entrypoint; the
same bytes map correctly from Linux-native storage. A Wine virtual desktop
(`wine explorer /desktop=ClashOriginal,640x480 'C:\clash\clash95.exe'`) inside
Xvfb also avoids the observed `DDERR_UNSUPPORTED` mode-switch failure.

The proven capture setup, executable hashes, cleanup and actual game-client
captures are recorded in
`artifacts/structure-recovery/linux-validation-20260905/original/`, particularly
the capture script
`artifacts/structure-recovery/linux-validation-20260905/original/capture_original_virtual_desktop.sh`.
That script makes a fresh native session,
retains its path, restores the owned prefix's `C:\clash` mapping on exit, and
leaves installed executable bytes unchanged. Preserve the retail installation
and prior evidence when adapting it for another state. A displayed menu alone
does not prove tactical or campaign fidelity.

## Build

Build both supported compiler profiles, including the separate test executable.
Use fresh build directories for a baseline run; `--clean-first` also ensures the
warning check sees the full compiler output when reusing these directories.

```sh
set -euo pipefail
for cc in gcc-13 clang-18; do
  build_dir="build/$cc"
  compiler_id="${cc%-*}"
  CC="$cc" cmake -S . -B "$build_dir" -G Ninja -DCMAKE_BUILD_TYPE=Debug
  if ! cmake --build "$build_dir" --clean-first \
    --target clash95_recovered clash95_bootstrap runtime_mission_trace_tests \
    clash95_split_audit -j2 >"$build_dir/compiler.log" 2>&1; then
    tail -n 200 "$build_dir/compiler.log"
    exit 1
  fi
  python3 tools/check_recovered_warnings.py "$build_dir/compiler.log" \
    --compiler "$compiler_id" --mode check
  python3 tools/check_link_surface.py "$build_dir/bin/clash95_bootstrap" \
    --lib "$build_dir/lib/libclash95_recovered.a" \
    --compiler "$compiler_id" --mode check
done
```

Do not raise the warning or linked-symbol/layout baselines merely to pass these
checks. The supported recovered code still has explicitly ratcheted warnings;
support and test code build with warnings as errors.

## Asset-Free Tests

These are the four explicit public CI gates. An `asset_free` label filter alone
does not include `runtime_mission_trace_tests`.

```sh
set -euo pipefail
for cc in gcc-13 clang-18; do
  ctest --test-dir "build/$cc" \
    -R '^(clash95_split_source_audit|clash95_pure_metadata_audit|clash95_save_format_contract|runtime_mission_trace_tests)$' \
    --output-on-failure
done
```

## Unit Coverage

The coverage harness also requires no retail assets. Match the frozen CI floor,
function count, and zero-uncovered requirement:

```sh
set -euo pipefail
CC=gcc-13 cmake -S . -B build/coverage -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DCLASH95_COVERAGE=ON
cmake --build build/coverage --target clash95_unit_tests -j2
ctest --test-dir build/coverage -R '^clash95_unit_tests$' --output-on-failure
python3 tools/measure_pure_coverage.py build/coverage \
  --minimum 89.7 --require-functions 718 --require-zero-uncovered --worst 10
```

Use the CTest wrapper to persist per-worker coverage shards. See
[UNIT_TESTING.md](UNIT_TESTING.md) for the coverage model and evidence rules.

## Default Local Smoke Suite

With the retail installation and runtime tools available:

```sh
ctest --test-dir build/gcc-13 --output-on-failure
```

This is broader than the asset-free CI gate. Boot smokes need retail assets;
save-DAT checks use installed save fixtures. CTest enables the castle-economy
regression automatically and skips other opt-in probes when their enabling
environment variables are absent. The wrappers use SDL dummy drivers or their
own Xvfb displays. A liveness-only smoke is not visual-fidelity evidence.

## Metadata And Formatting Checks

```sh
set -euo pipefail
python3 -m py_compile tools/*.py
for json_file in RECOVERED_STRUCTURES.json UNIT_TYPES_AND_STATS.json \
  data/recovered_sources.json data/recovered_warning_baseline.json \
  data/link_surface_baseline.json data/recovered_decls.json \
  data/subsystem_api.json data/header_surface_baseline.json \
  tests/unit/pure_function_aliases.json tests/unit/pure_set.json; do
  python3 -m json.tool "$json_file" >/dev/null
done
python3 tools/audit_split_sources.py
python3 tools/migrate_pure_coverage_metadata.py --check
python3 tools/check_save_format_contract.py
python3 tools/gen_constant_guard.py --check
python3 tools/gen_recovered_structs.py --check
python3 tools/gen_unit_type_runtime_metadata.py --check
python3 tools/audit_header_surface.py --mode check
python3 tests/check_markdown_links.py
git diff --check
```

Shell syntax checks for common route/probe scripts:

```sh
set -euo pipefail
for script in tests/run_campaign_route_script_smoke.sh \
  tests/run_campaign_route_regression.sh \
  tests/run_clash95_soak_probe.sh \
  tests/run_multiplayer_map_probe.sh \
  tests/prune_artifacts.sh; do
  bash -n "$script"
done
```

## Shared-State Header Rollout

Consumer layout is active as of 2026-09-05. Eleven generated shared-state
slices reduce declaration exposure from 32,776 to 11,994 across 136 consumer
TUs. All 45 tooling tests pass. GCC 13 and Clang 18 preserve all 140 normalized
recovered object disassemblies and linked symbol layouts. Existing header,
warning and link ratchet failures remain unchanged; their baselines were not
raised. Coverage passes at 92.40% across all 718 frozen functions. The default
headless CTest suite remains red: 10 pass, 3 failures reproduce against the
saved pre-rollout executable, and 8 opt-in tests skip. Evidence and exact commands are under
`artifacts/modularization/shared-state-20260905/rollout/`. The earlier WSL
access failure is retained as preparation history in the parent directory.

From the repository root in Linux/WSL, first run the tooling tests and record
the current generator freshness and existing header-ratchet failures:

```sh
python3 -m unittest discover -s tests/tools -p 'test_*.py'
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
python3 tools/audit_header_surface.py --mode check
```

For future changes, capture pre-change token/object snapshots using the
existing gates and a unique evidence directory under `artifacts/modularization/`.
Keep the top-level `shared_state_layout` field in `data/recovered_decls.json`
set to `"consumer"`, then regenerate the headers, measured surface and all TU include blocks from one
preprocessed usage scan:

```sh
python3 tools/gen_subsystem_headers.py --write --write-tu-includes all
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
python3 tools/audit_header_surface.py --mode check
python3 tools/audit_split_sources.py
python3 -m unittest discover -s tests/tools -p 'test_*.py'
```

The include writer validates every selected block before changing any TU and
preserves all bytes outside that block, including line endings. Review the
generated declaration removals in the token comparison: the complete header
token stream intentionally narrows, so blanket token equality is not the
acceptance claim. Recovered function tokens, declarations that remain visible,
and storage definitions must retain their prior meaning; review any object
differences explicitly. Do not refresh manifest body hashes for this rollout.

Run both compiler profiles, the four explicit asset-free CTest gates, unit
coverage and the applicable headless smoke checks documented above. Compare
old API/peer/shared-global metrics directly; narrowing exposure must not hide
existing dependency-limit failures or raise warning/link/header baselines.
Record the new visibility totals only after fresh regeneration. If presented
output is affected, also retain a fresh original/reconstruction frame pair as
required by AGENTS.md. Review these gates before accepting a new narrowing batch.

## Campaign Route Probes

Summarize route readiness without launching the game:

```sh
bash tests/summarize_campaign_arc_routes.sh
```

Run one opt-in route regression:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest --test-dir build/gcc-13 -R '^clash95_campaign_route_04_regression$' \
  --output-on-failure
```

All mission route env files, including the second campaign, live in
`tests/first_campaign_arc_routes/`. For a completed route without its own CTest
entry, such as mission `13`, call the same headless wrapper directly:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0 \
  bash tests/run_campaign_route_regression.sh \
  build/gcc-13/bin/clash95_bootstrap 13 tests/first_campaign_arc_routes/mission_13.env
```

Preserve log/objective/failure markers, current frames, and repeatable route
checkpoints before reporting route completion. Every visual-fidelity claim
requires a same-state original/reconstruction frame comparison under WSL Xvfb,
with pixel metrics and exact commands, as specified in
[AGENTS.md](../AGENTS.md#9a-mandatory-frame-comparison-against-the-original).
Keep frame evidence under `artifacts/`; do not open host image viewers.

Run the full campaign arc wrapper only after every required route is marked
`complete`:

```sh
bash tests/run_campaign_arc_build_probe.sh
```

Run an already-built binary through the campaign arc runner:

```sh
bash tests/run_campaign_arc_probe.sh build/gcc-13/bin/clash95_bootstrap
```

## Soak Probes

```sh
CLASH95_ENABLE_SOAK_PROBE=1 CLASH95_SOAK_DURATION_SECONDS=120 \
  ctest --test-dir build/gcc-13 -R '^clash95_soak_probe$' --output-on-failure
```

Useful `CLASH95_SOAK_SCENARIO` values include `world-map-pan`,
`castle-economy`, `first-mission-attack`, `campaign-route`, and
`multiplayer-map`.

## Multiplayer Map Probes

Run the default direct all-AI multiplayer map probe for `/A0`:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
  ctest --test-dir build/gcc-13 -R '^clash95_multiplayer_map_probe$' --output-on-failure
```

Run a wider map set:

```sh
CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1 \
CLASH95_MULTIPLAYER_MAP_IDS="0 1 2 3 4 5 6 7 8 9 10" \
  ctest --test-dir build/gcc-13 -R '^clash95_multiplayer_map_probe$' --output-on-failure
```

The probe is skipped by default. It launches Xvfb, follows the recovered `/A#`
multiplayer map path, checks bootstrap load/play markers, and validates a
nonblank presented frame. Details live in
`docs/probes/README_multiplayer_map_probe.md`.

## Important Environment Variables

- `CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1` enables route CTest probes.
- `CLASH95_ENABLE_SOAK_PROBE=1` enables soak probes.
- `CLASH95_ENABLE_MULTIPLAYER_MAP_PROBE=1` enables direct multiplayer map
  visual/liveness probes.
- `CLASH95_SCREENSHOT_PREFIX` and `CLASH95_DUMP_PRESENTED_FRAMES_PREFIX`
  capture frame evidence for visual validation.
- `CLASH95_ARTIFACT_PRUNE_AFTER_RUN=0` disables automatic artifact pruning for
  deep investigations.
- `CLASH95_ARTIFACT_PRUNE_MAX_BYTES` sets the repo-wide `artifacts/` cap used by
  the pruning helper.

Focused probe documentation lives in `docs/probes/`.
