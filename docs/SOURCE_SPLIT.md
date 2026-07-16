# Recovered GNU C17 Source Split

## Current state

The source split reached final repository cutover on 2026-07-15. The recovered
implementation used by `clash95_recovered` and `clash95_bootstrap` is canonical
only as **138 independently compiled GNU C17 translation units** in 12 subsystem
directories directly under `src/`:

- 136 address-ordered function-family files;
- one prelude/helper translation unit;
- one quarantined recovered-state translation unit.

`data/recovered_sources.json` records **4,070 recovered functions** and **3,920
original address-marker chunks**. Marker chunks and function records are
related evidence sets, not a one-to-one count. The root unified source, GNU89
oracle targets, recovered include-C fragments, and compatibility source symlinks
were removed. No production source includes another `.c` file.

This cutover changes source ownership and build structure, not recovered game
semantics or campaign status.

## Layout and ownership

Function files are grouped by subsystem, original address order, and bounded
dependency family. Their names encode the first and last original addresses,
for example:

```text
src/battle/0042CB50_0042E8B0_battle_001.c
```

`src/sources.cmake` assigns the files to 12 subsystem object
libraries:

- core, render, world, units, buildings, and battle;
- persistence, strategic, CLIPS, media, legacy runtime, and state.

Global storage has one definition in the recovered-state translation unit.
Ambiguous adjacency-dependent declarations remain together there rather than
being resized or scattered without map or assembly evidence.

The former recovered-internal migration umbrella is gone: every TU now
includes a generated, marker-delimited block of narrowed headers — its own
subsystem's internal header (which pulls the api header, the measured public
surface — e.g. `src/battle/battle_internal.h` pulling
`src/battle/battle_api.h`) and its state header (state-owned globals whose
only consumer is that subsystem, e.g. `src/battle/battle_state.h`),
`src/state/state_shared.h` where a multi-subsystem global is referenced, the
api headers of exactly the peers it calls, `src/recovered_legacy_imports.h` where
a legacy CRT/Win32 import is referenced, and `src/recovered_types.h` +
`src/recovered_layout.h` via the block. All of this is generated from
`data/recovered_decls.json` (the verbatim declaration database) and a
preprocessed usage scan by `tools/gen_subsystem_headers.py`; the measured
surface lives in `data/subsystem_api.json`. `src/recovered_all.h` aggregates
everything for `tests/unit` only. No stable external library API is
introduced. Cross-family helpers have hidden visibility. Seventeen helpers
remain production-only `static` functions, and 30 frozen pure helpers use
`CLASH95_TEST_VISIBLE` (declared in `src/recovered_test_seams.h`), which is
`static` in production and external only when `CLASH95_TESTING` is enabled.

## Authoritative metadata

`data/recovered_sources.json` is the source of truth for implementation
identity. Each function record includes its name, original address/range,
subsystem, canonical source, historical source path and line, linkage, state
owner, canonical body hash, and legacy mechanical-move hash. Schema 2 marks the
split as canonical.

`docs/SOURCE_PATH_MAP.csv` is the durable old-to-new path record. Its legacy
paths intentionally do not exist after cutover. Historical reports may still
quote unified-era paths and line numbers; live tooling must resolve functions
through the JSON manifest.

## Audit and change policy

`tools/audit_split_sources.py` validates the canonical tree directly:

- every manifest function has exactly one definition in its assigned source;
- canonical body-token hashes and original identities remain stable;
- original address and translation-unit ordering remain valid;
- source counts and translation-unit line limits agree with the manifest;
- production sources do not include `.c` files;
- removed unified, fragment, wrapper, and symlink paths do not return.

`tools/check_link_surface.py` additionally pins the LINKED artifact per compiler
(`data/link_surface_baseline.json`): which recovered symbols survive
`--gc-sections`, their classes, data/BSS symbol sizes, and the address-ordered
data-symbol sequence — the physical-adjacency property the quarantined state
translation unit exists to protect. It also cross-checks every manifest function
against `libclash95_recovered.a` (external/internal exactly once as a global;
static/test-visible exactly once as a local). It runs in CI for both compilers;
re-seed only with `--mode update` on a reviewed clean build. The preprocessed-
token and object-diff snapshot gates intentionally stay manual-loop tools: their
baselines are large transient artifacts and any legitimate edit re-baselines
them, so CI relies on the manifest hash audit, this link-surface gate, the
warning ratchet, and the coverage floor instead.

Typical static checks are:

```sh
python3 tools/audit_split_sources.py
python3 tools/migrate_pure_coverage_metadata.py --check
python3 tools/check_save_format_contract.py
python3 tools/check_link_surface.py build/bin/clash95_bootstrap \
  --lib build/lib/libclash95_recovered.a --compiler gcc --mode check
bash tools/pp_token_gate.sh --snapshot /tmp/clash95-split.i
bash tools/obj_diff_gate.sh --snapshot /tmp/clash95-split.asm
git diff --check
```

The checked-in split files are normal source files. A source move must update
`sources.cmake`, the manifest, and the path map together. Formatting, typing,
warning cleanup, and control-flow changes belong in separately validated
batches.

## Build and warning policy

Recovered objects use GNU C17 (`C_STANDARD 17`, extensions enabled). Implicit
declarations, implicit `int`, and missing returns are errors. Platform,
instrumentation, compatibility, bootstrap, and test support use the stricter
`-Wall -Wextra -Wpedantic -Werror` profile.

`data/recovered_warning_baseline.json` records the recovered-code diagnostic
ratchet, including diagnostics attributed to the private recovered headers
(`src/recovered_abi.h`, `src/recovered_types.h`, `src/recovered_layout.h`,
`src/recovered_legacy_imports.h`, `src/recovered_test_seams.h`,
`src/recovered_all.h`, and the generated per-subsystem headers under
`src/<subsystem>/`) and the shared compatibility ABI definitions.
The reviewed baselines are **146,171 GCC diagnostics in 25 categories** and
**147,027 Clang 18 diagnostics in 35 categories**; later cleanup may reduce a
category but may not increase it or add another one. This is substantial
cleanup debt and is not a zero-warning claim. Support implementations are
outside that baseline and remain strict-warning clean.

The reviewed 2026-07-16 compiler gate is reproduced with:

```sh
CC=gcc-13 cmake -S . -B build/gcc -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/gcc --target clash95_recovered clash95_bootstrap \
  runtime_mission_trace_tests clash95_split_audit -j2 \
  >compiler-gcc.log 2>&1
python3 tools/check_recovered_warnings.py compiler-gcc.log \
  --compiler gcc --mode check
ctest --test-dir build/gcc -R \
  '^(clash95_split_source_audit|clash95_pure_metadata_audit|clash95_save_format_contract|runtime_mission_trace_tests)$' \
  --output-on-failure

CC=clang-18 cmake -S . -B build/clang -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build/clang --target clash95_recovered clash95_bootstrap \
  runtime_mission_trace_tests clash95_split_audit -j2 \
  >compiler-clang.log 2>&1
python3 tools/check_recovered_warnings.py compiler-clang.log \
  --compiler clang --mode check
ctest --test-dir build/clang -R \
  '^(clash95_split_source_audit|clash95_pure_metadata_audit|clash95_save_format_contract|runtime_mission_trace_tests)$' \
  --output-on-failure
```

CI captures the corresponding complete compiler logs before running the split,
pure-metadata, save-contract, and mission-trace CTest gates.

The coverage build instruments the same 138 split sources and compiles every
test case independently. See `docs/UNIT_TESTING.md` for its runner and
per-worker coverage-shard design.

## Preserved parity evidence

Before removing the GNU89 oracle, the final GCC comparison resolved every one
of the 4,070 manifest functions in both models and compared the complete
default-visible symbol surface:

- 4,051 functions were normalized-disassembly identical;
- 19 functions had reviewed, exact-hash exceptions caused by required cross-TU
  declarations or unified-TU function-address constant folding;
- no function was missing or unexpected;
- no default-visible symbol existed on only one side.

The split and oracle executables also passed the same default-menu, shutdown,
`/A`, `/A0`, and castle-economy scripts. The split executable separately passed
the asset-backed save-slot verifier. The exact reviewed exception hashes and
reasons are retained in
`docs/archive/SPLIT_DISASSEMBLY_EXCEPTIONS.json`; the old-to-new paths remain
in `docs/SOURCE_PATH_MAP.csv`.

These results justify the repository cutover. They do not prove that future
semantic edits preserve behavior, and they do not advance campaign completion.

## Current validation and remaining debt

The split-only validation surface is:

```sh
cmake -S . -B build/cutover -DCMAKE_BUILD_TYPE=Debug
cmake --build build/cutover \
  --target clash95_recovered clash95_bootstrap \
           runtime_mission_trace_tests clash95_split_audit -j2
ctest --test-dir build/cutover --output-on-failure
```

The source audit, manifest-backed unit metadata, save-format contract, GCC
build, and selected SDL/runtime routes have passed during the migration and
cutover work. The following remain explicit debt:

- reduction and eventual elimination of the recovered warning inventory;
- completion of all long asset-backed campaign and multiplayer acceptance
  routes after the cutover;
- mission `05`, full Campaign-menu entry, and automatic mission advancement;
- narrower domain headers and further evidence-backed compatibility cleanup.

Without the in-tree oracle, future behavior changes must be justified by
`clash95.asm`, the canonical body/token/object snapshot gates, focused unit
tests, and the smallest relevant live route with current frame/log evidence.
