# Human-readable C++ recovery

The readability track turns evidence-backed decompiler output into ordinary maintainable C++ without changing retail behavior.

## Rules

1. Prefer recovered structs and enums over raw offsets and magic numbers.
2. Keep unknown bytes explicitly unknown until evidence supports a semantic name.
3. Pin every recovered binary layout with `CLASH95_STATIC_ASSERT` checks for size and important offsets.
4. Rename locals and parameters only when data flow or call-site evidence supports the meaning.
5. Preserve original control flow unless a structured rewrite is demonstrably equivalent.
6. Keep SDL/platform adaptation separate from recovered gameplay semantics.
7. Validate readability changes with the existing build, unit, route, and frame-comparison gates appropriate to the touched code.

## Current first target: UnitStack

The canonical typed model already lives in generated `src/recovered_structs.h`, sourced from `RECOVERED_STRUCTURES.json`. Readability work must reuse that model rather than create subsystem-local duplicate overlays.

The recovered `UnitStackRecord` is a packed 725-byte record with layout pins for:

- `tile_row` at `+0`
- `tile_column` at `+2`
- `owner_player_index` at `+4`
- `facing_direction` at `+5`
- ten typed `UnitSlotRecord` entries at `+6`
- typed `QueuedPathBuffer` at `+316`
- `is_hidden_on_world_map` at `+720`
- four unrecovered tail bytes at `+721..+724`

`UnitSlotRecord` is also already partially recovered: unit type, owner, action points, health, fatigue, morale, stance/state flags and selected runtime state fields have pinned offsets. Unknown spans remain explicit byte arrays.

The migration is incremental: replace `int stackPtr`, `__int16 *stackPtr`, `UNIT_STACK_*` field macros, and raw `stack + offset` expressions with `UnitStackRecord *` and `UnitSlotRecord *` access where doing so is layout-equivalent. ABI-facing signatures stay unchanged until all cross-subsystem callers are understood.

`UNIT_STACK_RECORD(index)` is the common typed view of a strategic stack table entry. `UNIT_SLOT_FLAG_READY` names the previously raw bit used symmetrically by the ready-state readers and writers.

### Pathing batch

The first typed-access batch covers the pathing frontier in `src/units/00414390_00416750_units_004.cpp`:

- `Path_InsertBridgeCornerWaypoints`
- `Unit_MoveTrack`
- `Unit_MoveTrackNearTile`
- `Building_GenerateApproachTrack`
- `Building_GenerateNearApproachTrack`

These functions obtain strategic stack position through `UnitStackRecord` and `stack->tile_row` / `stack->tile_column` instead of repeating 725-byte record arithmetic or raw `+0` / `+2` accesses. Existing ABI-facing signatures are deliberately retained; casts remain only at boundaries that have not yet been migrated.

### Core unit batch

The second batch converts the reached core unit paths in `src/units/0040F510_00411560_units_001.cpp`:

- stack allocation and initialization in `Unit_Create`
- army-fact link/unlink helpers
- unit-stack kill and tile removal
- empty-stack detection
- stack vision radius and reveal propagation
- ready-flag query/set/clear using typed `UnitSlotRecord::state_flags`
- camera centering from typed stack coordinates
- fatigue-based action-point calculation using `UnitSlotRecord::unit_type_id` and `fatigue`

The old `145 * 5`, `+6`, `+10`, `+13`, 31-byte slot stepping, and equivalent raw record expressions are removed from these functions where a pinned field already exists. The original loops, termination conditions and ABI-facing calls remain intact.

`data/recovered_sources.json` records the new canonical hashes for readability-preserving function bodies, and `src/recovered_layout.h` is regenerated when a new recovered constant is named. The split-source audit therefore continues to detect unrelated drift.

## Validation

The first pathing batch compiles and links successfully under both GCC 13 and Clang 18. The repository's current `main` baseline still fails later CI gates for the pre-existing generated-header surface ratchet, compiler-warning ratchet and split-unit harness debt; those failures are tracked separately from readability work.

## Readability audit

Run:

```sh
python3 tools/audit_c_readability.py
```

The audit counts common decompiler debt and ranks the highest-debt source files. It is a prioritization metric, not an acceptance gate: counts must never be reduced by speculative renaming or semantic rewrites.

## Function review: Road helpers, 2026-09-06

Track: Win95 reconstruction. Review the reached mission-05 Road family one
function at a time, retaining the original-matching first-construction endpoint
as the runtime baseline. This work improves readability; it does not promote a
campaign route or resolve the turn-7 continuation blocker.

### Batch 1: `MapTile_HasAlignedBridgeApproachRoadOverlay`

The function at `0x424020` now uses the existing, layout-pinned `MapTileRecord`
for terrain and overlay reads, one first-match loop instead of duplicate
counters, and explicit failure returns. The original scan covers 48 live DWORDs,
including aliased marker data. It must not become a constant bridge-ID list.
The first matching index still chooses row alignment below six and column
alignment otherwise; terrain IDs `603..610` remain the accepted range.

Evidence: `clash95.asm` routine `sub_424020`, the canonical body in
`src/buildings/00422B50_004254E0_buildings_005.cpp`, the size/offset assertions in
`src/recovered_structs.h`, and the existing original-measured fixtures in
`tests/tools/fixtures/builder_road/`. Confidence is high for this bounded
behavior-preserving change. No public symbols, signatures, layouts, constants,
or legacy hashes change; only this canonical body hash changes.

The existing 672-case regression passes GCC 13 and Clang 18 at O0/O2, including
636 bridge cases with every scan position, duplicate matches and live aliases.
All 120 tooling tests pass. Manifest, split-source, generated-header and include
freshness checks pass. The header ratchet retains its 14 existing failures.
Fresh GCC/Clang compile and link builds and all four public CTest gates pass.
Warning totals are 6618/6628, exactly matching freshly built untouched source.
Raw link ratchets reproduce 427/679 existing differences with zero manifest
cross-check errors. No baseline is raised.
Before/after linked symbol names/classes and data sizes/order match, as do all
4157 recovered archive entries. Only the reviewed function changes size
(GCC 299 to 227 bytes; Clang 360 to 289), shifting later text addresses.
The default headless GCC smoke retains 10 passes, three documented first-marker
failures and eight skips. Playability/attack still wait for
`next_unit_selected selected=1 a=31 b=44`; castle economy still waits for
`human_turn_enter idx=1 owner=0 tile=31,44`.

Normalized object comparison covers all 35 text sections in the touched TU for
four compiler profiles. Only this predicate changes, plus its existing inlined
copies in `Road_Build` and `RoadBuildMode_HighlightBuildableAdjacentTile` under
Clang O2. Independent review verifies scan order, first-match exits, unsigned
word reads, call order and the unchanged AP fallback. Machine-code identity is
not claimed for a structured rewrite.

Exact local commands, source freezes, compiler snapshots and diffs are retained
under `artifacts/readability/road-functions-20260906/`, including the baseline
source freeze and batch-01 validation/build scripts. The comparison script is
artifacts/readability/road-functions-20260906/batch-01/compare_objects.py;
the check runner is
artifacts/readability/road-functions-20260906/batch-01/validate.sh.
These private local scripts are absent from clean checkouts.
Reproduce the focused gate from the WSL repository root with:

```sh
python3 -m unittest discover -s tests/tools -p test_builder_road.py -v
python3 tools/update_split_manifest_hashes.py
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
```

Deferred: larger Road modal functions need separate input/rendering review.
Row/column names remain unchanged because UI-axis terminology is inconsistent.
The proposed selector parameter name `delayTicks` was rejected: the called
animation helper ignores that argument and uses a fixed 20-tick delay. No new
visual-fidelity, mission-arrival or campaign-completion claim follows.

### Batch 2: `Map_GetBridgeCrossingCostOrZero`

The helper at `0x424370` now reads the existing `MapTileRecord::terrain_tile_id`
once and returns its unchanged cost: five for terrain `603..610`, zero otherwise.
This replaces decompiler byte-offset temporaries and a repeated raw word read.
The field is terrain at offset zero; historical references to an overlay do not
justify renaming it. One canonical body hash changes; ABI and layouts stay fixed.

The original routine and two alignment bytes at `0x424370..0x4243D8` are byte-identical
in the installed and repository executables, despite different whole-PE hashes.
It ran at its original address in a freestanding 32-bit adapter with no replaced
callees. All 65,536 terrain values at eight valid map positions produce 524,288
original results. Both the frozen prior body and the new typed body match every
result under GCC 13 and Clang 18 at O0/O2. The map arena is read-only during
calls; the game-data pointer and the C++ arena contents remain unchanged.

Confidence is high for valid map positions and signed-low32 game-data addresses.
The proof covers the entire terrain-word domain, not invalid pointers, coordinate
overflow or full gameplay. Original bytes and outputs remain private artifacts.
Their code SHA256 is
`4c91b72f92a5e530563ac24931828e38371a7b37e38ac77e69e2fe9fce98b6a1`.
The actual-source equivalence check, frozen bodies, original adapter, exhaustive
results and exact compiler commands are retained under
`artifacts/readability/road-functions-20260906/batch-02/`.

All 35 TU text sections are compared at O0/O2 in both compilers; only this
function changes. Both incremental builds and the four public CTests pass.
Linked symbol/data profiles and all 4157 archive identities match batch 1;
source-attributed warning categories are unchanged (19 GCC / 39 Clang; the full
affected compilation blocks contain 28/39, including header diagnostics), without
claiming incremental logs as a fresh whole-build warning count. Manifest,
split-source, headers/includes and the existing builder regression pass.
Changed non-archive Markdown passes the path check; the whole-tree check flags
the preceding integration report's private history-audit path in this worktree.
No baseline is raised, and no new runtime milestone is claimed.

No public rename, new constant or new semantic layout is introduced. The next
candidates are the Road normalization and connection helpers; larger
input/rendering functions remain separately scoped.

### Batch 3: `Map_NormalizeRoadOverlayTileId`

Renamed the input `result` to `overlayTileId` without changing its `int` type,
bounds, arithmetic, lookup or returns. All four directional-connection callers
read the unsigned road/bridge word at tile offset four before calling this
helper. Original `sub_423FC0` in `clash95.asm` confirms the fallback input and
the existing remapping branches. Confidence is high for this parameter name.

All 35 text sections of the containing TU have identical normalized instructions
and relocations in GCC 13 and Clang 18 at O0/O2. One canonical body hash changes;
declarations, layout and function identity remain unchanged. Evidence and exact
commands are under `artifacts/readability/road-functions-20260906/batch-03/`.
Both incremental builds and all four public CTests pass. The complete linked
`.text` sections are byte-identical to batch 2 in both Debug profiles; all 4157
archive identities, linked profiles and affected compilation warning counts
(28 GCC / 39 Clang, including headers) are unchanged. Existing raw link/header
ratchet failures remain separate; no baseline is raised.

Deferred recovery: the original lookup for IDs `819..861` addresses
`0x51423C..0x514290`, within the live Road backing region. The canonical
expression still indexes beyond the separate `UI_Locale_BuildingNames_I` pointer
array. This naming-only batch preserves that legacy defect and does not claim
lookup fidelity. Names implying localized strings, immutable Road constants or
animation semantics were rejected. Recover this storage relationship separately
with original-backed evidence; retain the current campaign/runtime milestones.

### Batch 4: `Map_RebuildRoadOverlayAtTile`

Reviewed `0x423E90` against its original instruction sequence and complete
27-entry connection table. Replaced four redundant column copies and staged
decompiler masks with one named mask, preserving separate west, south, east,
north calls and weights `8/4/2/1`. The existing `MapTileRecord` exposes the
road/bridge word. The function still loads the table and then `gameData` after
the probes, writes the low 16 bits of a nonzero sprite (or `0xFFFF` for zero),
and returns the row base rather than the tile address. Removed obsolete
undefined-local comments. Confidence is high for this bounded refactor.

Unchanged original rebuild, four directional queries and normalizer run
together in a native 32-bit adapter at their original addresses. Both PEs have
identical code/table bytes. The 1,024 cases cover 16 input connection masks at
eight interior positions, using the retail table and seven uniform replacement
profiles, including negative and nonzero high-word values. Frozen-before and
actual-after bodies match original returns and tile words in GCC/Clang O0/O2.
All remaining arena bytes, all 27 table entries and the game-data pointer stay
unchanged. Static assembly/source review supplies the call-order proof; there
is no instrumented call trace. The known `819..861` lookup defect and building
shortcut are outside this fixture's scope.

Both builds and four public CTests pass; manifest, header/include freshness and
the existing builder regression pass. All 4157 archive identities and linked
profiles remain unchanged; scoped warnings stay 28 GCC / 39 Clang. Only this
function changes in the Debug objects (219 to 181 bytes GCC, 216 to 192 Clang).
Existing link/header and private-artifact Markdown failures remain separate.
No new route, visual or campaign milestone is claimed.

Exact commands, source freezes, original binaries, comparisons and independent
reviews remain under `artifacts/readability/road-functions-20260906/batch-04/`.
The original probe's first Clang attempt lacked the optional UBSan runtime;
the retained final run uses trap-mode UBSan in both compilers. No sanitizer
check is removed except the already documented packed-alignment exclusion.

## Next migration batches

1. Continue through the remaining `src/units/` functions that manually step `UnitSlotRecord` at 31-byte intervals.
2. Replace remaining raw position/owner/facing accesses across `world/`, `buildings/` and `strategic/` with the canonical `UnitStackRecord` view.
3. Extend the same approach to the existing typed `PlayerRuntimeState` and building overlays.
4. Convert gameplay APIs to typed pointers only after all cross-subsystem call sites are understood.
5. Replace second-generation mechanical function names and decompiler locals after the underlying state model is stable.
