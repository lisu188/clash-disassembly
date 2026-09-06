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

### Batch 5: four directional Road queries

Reviewed each query against its own original routine and membership tests:

| Function | Original | Refactor |
| --- | --- | --- |
| `MapTile_HasNorthRoadConnection` | `0x423BB0` | Typed road/bridge field at `(row-1,column)`; original accepted IDs retained. |
| `MapTile_HasSouthRoadConnection` | `0x423C50` | Typed road/bridge field at `(row+1,column)`; original accepted IDs retained. |
| `MapTile_HasWestRoadConnection` | `0x423CF0` | Explicit building shortcut, then typed fallback at `(row,column-1)`. |
| `MapTile_HasEastRoadConnection` | `0x423E10` | Typed road/bridge field at `(row,column+1)` and explicit existing precedence. |

The west marker address uses the existing `TILE_INDEX(row,column-2)` macro,
equivalent to the former raw offset. Markers `0x8000..0xFFFE` alone permit a
building read. Signed type 2/1, unsigned row and unsigned column checks retain
their order. The original XOR clears equal row values before loading the column
byte, so direct byte access removes that decompiler artifact. The building match
returns before forming the fallback tile read. Building types remain numeric;
no speculative record type or global coordinate-name change is introduced.

The unchanged original queries and normalizer execute with their complete Road
backing. Per compiler profile, frozen-before and actual-after query sets each
match 1,056,520 original results; the shared unchanged normalizer matches 65,493.
This includes road-ID sweeps, asymmetric neighbor masks, every building type and
coordinate byte, and marker boundaries. The known `819..861` backing defect is
excluded explicitly: 688 sweep, 43 normalizer and 84 west cases. Their original
results are retained. Twelve successful building shortcuts run with both terrain
pages and the legacy lookup page inaccessible, proving neither read occurs.
The game arena is read-only during calls and the game-data pointer is unchanged.
All four GCC/Clang O0/O2 profiles pass. Confidence is high for these bounded
semantics; invalid pointers and arbitrary overflow are not covered.

Both builds and four public CTests pass. All 4157 archive identities and linked
profiles are preserved. Debug code differences are confined to these four
functions. Complete affected-compilation warnings decrease from 28 to 26 GCC
and 39 to 37 Clang, with no category increases. Manifest, headers/includes and
the existing builder regression pass. Existing ratchet/private-artifact failures
remain separate; no new runtime or campaign milestone is claimed.

Exact original and before/after commands, hashes, guards and all exclusions are
retained under `artifacts/readability/road-functions-20260906/batch-05-query-proof/`;
build, metadata and independent static reviews are under
`artifacts/readability/road-functions-20260906/batch-05/`. All 53 baseline query
evidence files are preserved unchanged. Four canonical body hashes change;
public identities and declarations remain fixed.

### Batch 6: shared Road normalization backing

Revisited `Map_NormalizeRoadOverlayTileId` (`0x423FC0`) to repair the separate
storage defect recorded in batches 3 and 5. Original instruction `0x42400E`
loads 43 unsigned words from `0x51423C..0x514290`. Those bytes are already in
the canonical shared `g_RoadBuildData` region at offset `0x30`; the old locale
pointer-array expression instead reads outside a separate 208-byte C++ object.
The corrected branch uses a named table offset/index and `memcpy` into a
`uint16_t`, retaining unsigned results and the existing live backing.

Only IDs `819..861` call the existing guarded builder/Road initializer. Its
templates and relocations use static bytes and addresses; no asset load,
callback, renderer or game-state read occurs. Pointer relocations start beyond
the lookup slice. Repeated calls preserve live lookup, widget and marker
mutations, including the lookup's overlap with the approach scan. Other
normalization branches retain their original expressions. No duplicate table,
locale interpretation or speculative animation semantics are introduced.

The actual corrected normalizer matches all 65,536 original uint16-domain
results in GCC 13 and Clang 18 at O0/O2. All 1,057,292 directional-query cases
now pass without the previous 688 sweep/84 west exclusions. Additional original
instruction probes cover 2,818,048 live unsigned-word mutations and 8,256
overlapping DWORD writes per profile. Real-initializer checks cover all 43 cold
lookup entries, cold nonlookup boundaries and warm-state preservation across
both complete backing arrays. All 91 preceding query-proof files remain intact.
Confidence is high for these measured contracts; arbitrary invalid pointers,
general overflow and broader construction behavior are outside the fixture.

The new asset-free regression executes the canonical normalizer and initializer,
checks the original full-domain output digest, all 112 pointer relocations,
43 cold lookups, 344 warm mutations and live sprite-holder indirection. It
reuses existing data fixtures and publishes only new measurement provenance.
Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_road_normalization.py -v
python3 tools/update_split_manifest_hashes.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
```

Both compiler builds and all four public CTests pass. All 4157 recovered
identities remain. Removing the last false locale reference moves its generated
declaration to the state-local header and lets the linker discard exactly the
unused 208-byte pointer array; its canonical storage definition remains.
Surviving data names, classes, sizes and relative order are preserved. Raw link
ratchets therefore report 428 GCC / 680 Clang differences, one more than before;
no baseline is raised. Rebuilt-source warning categories do not increase. The
fresh default GCC headless suite retains 10 passes, three known failures and
eight skips, with the same selection/human-turn failure markers.

Both fresh first-Road replays retain the highest validated endpoint: turn 6,
stack 4 at `(49,50)`, 2 AP, empty path, roads 867/879 and 228 visible tiles.
All ten raw unit slots, checked state fields, the complete visibility bitmap,
six Road words and same-turn construction invariants match the fresh original.
Each run preserves 238 frozen inputs, nine route scripts, 20 engine-authored
DAT/FAC files and 15 frame checkpoints. The original uses real Load of the
unchanged turn-6 checkpoint; continuous original turn-1 replay is not claimed.

Fresh 640x480 pairs use viewport `(47,48)`, cursor `(192,176)` and selected
stack 4. Full unmasked MAD is 11.086158854 GCC / 11.312281901 Clang, with
285647 / 287265 differing pixels. Bridge placement aligns; missing coordinates,
displaced badges, absent unit/status panels, lower-text/map corruption and
fog/water differences remain. Both pairs were inspected. These route runs do
not establish that IDs `819..861` were reached; the original-instruction fixture
provides the direct branch proof. No route, visual or campaign milestone advances.

Private exact commands, hashes, initializer review, original measurements and
all attempts are retained under artifacts/readability/road-functions-20260906/batch-06/.

The repair commit `8df94c4` was then combined with upstream numeric-cleanup merge
`431e4c5`. The only merge conflict was the history-log prepend; both records
remain. Independent review verifies all 68 changed source/header/data files
against the exact expected union. Normalizer, query and initializer bodies
retain their original-validated hashes. No numeric-cleanup work is discarded.

Both integrated builds and all eight public asset-free gates pass; all 137
tooling tests pass. Defined symbols, all 4157 recovered identities, section
layouts and program headers match the repaired route-tested binaries. Every
code/data byte is identical; only GNU build-id bytes and the ELF section-table
offset differ. This establishes applicability of the retained fresh runtime
comparisons to the integrated production code without another route replay.
Final native coverage passes at 6167/6662 lines (92.57%), all 718 functions and
zero uncovered functions; the preintegration run was 6169/6662 (92.60%). No
coverage floor or warning/link/header baseline is raised.

The two-line coverage variation is confined to the unchanged
`Building_UpdatePlagueState` RNG-dependent outbreak branch: 17/19 versus 19/19
lines. Its existing fixture explicitly permits that branch not to fire across
20 calls. The integrated native run retains 1059 passes, zero assertion
failures and 530 isolated crashes out of 1589; coverage success does not mean
every native fixture succeeds.

The final coverage work encountered host disk-full and a read-only WSL
filesystem. Lossless NTFS compression of this batch's BMPs preserved all files,
and Ubuntu was restarted with explicit user approval. Write/compiler checks
then passed, coverage ran in an owned Linux-native build and the independent
runtime audit reverified every frozen input, save and checkpoint hash plus both
frame metrics. Failed/interrupted attempts remain recorded. Final metadata
checks pass except the existing 14 header-ratchet differences and the existing
Markdown reference to an absent private predecessor report. Whitespace checks
against incoming main pass; the retained incoming CRLF JSON is checked with
Git's `cr-at-eol` setting, consistent with `.gitattributes`.

Integration commands and raw results are under this batch's build-validation/
integration/, integration-audit/ and integration-metadata/ directories. The
parent gate script is artifacts/readability/road-functions-20260906/batch-06/integration-metadata.sh.

## Next migration batches

1. Continue through the remaining `src/units/` functions that manually step `UnitSlotRecord` at 31-byte intervals.
2. Replace remaining raw position/owner/facing accesses across `world/`, `buildings/` and `strategic/` with the canonical `UnitStackRecord` view.
3. Extend the same approach to the existing typed `PlayerRuntimeState` and building overlays.
4. Convert gameplay APIs to typed pointers only after all cross-subsystem call sites are understood.
5. Replace second-generation mechanical function names and decompiler locals after the underlying state model is stable.
