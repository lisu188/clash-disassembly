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

### Batch 7: `MapTile_IsBareBridgeCrossingRoadOverlayCandidate`

The predicate at `0x424120` now reads four named `MapTileRecord` neighbors,
reduces the loaded values directly and checks the center's named overlay and
terrain fields. Removed repeated raw reads, register temporaries and a redundant
result variable. The original north/south/west/east load order and center checks
remain explicit. Both dimension comparisons now spell out their existing
unsigned conversion, removing signed-comparison warnings without widening the
original equality-only border checks.

Original instructions at `0x42422F..0x4242BD` reduce only `877..948` modulo six.
Raw values `0..5` still qualify through the direction-specific sets; `949` stays
outside the reduction. The center's empty sentinel belongs to overlay field
`+2`, independently of its Road field `+4`; terrain remains `603..610`.
Reusing `Map_NormalizeRoadOverlayTileId`, strengthening the border checks or
inventing graphical names for the six remainders would alter or overstate the
recovered contract, so those alternatives remain rejected.

Track: Win95 reconstruction, the reached mission-05 Road helper family.
Evidence is the original `sub_424120` assembly, matching local PE instruction
bytes, existing tile layout assertions and its two recovered Road callers.
No public symbol, ABI, layout, constant, initializer or legacy hash changes.
The manifest still contains 4157 identities; this is its only changed body hash.
No behavioral blocker or campaign milestone is claimed by this readability edit.

Unchanged original instructions run directly in a freestanding i386 probe,
without replacement callees. The frozen before and actual after bodies match
all 1,677,926 original results on GCC 13 and Clang 18 at O0/O2. This includes
all uint16 values independently in each neighbor at four positions, all center
terrain/overlay values with each connecting direction, 38,416 mixed-neighbor
tuples and all center Road values. Poisoned unrelated fields, nonsquare and
synthetic uint32 dimensions, protected border pages and a null `gameData` on
the first short-circuit path also pass. The arena stays read-only during calls
and the `gameData` value remains unchanged.

Confidence is high within those tested domains and the reviewed original
control flow. The test does not exhaust every simultaneous field combination
or establish arbitrary invalid-address/overflow behavior. Original load order
is separately visible in the assembly. The exact 586 instruction bytes end at
`0x42436A`; the six following padding bytes are identified separately.

The asset-free regression in `tests/tools/test_bare_bridge_candidate.py` runs
the actual body against a digest of 600 original-measured results, with field
isolation, range boundaries, all six remainder classes and nonsquare maps.
Thirteen separate protected-page guard cases use assembly-backed zero returns;
the provenance distinguishes them from the measured stream. Those cases cover
null `gameData`, skipped height reads, unsigned subtraction wraparound and both
signed integer extremes. All four strict compiler profiles pass with warnings
as errors and trapping UBSan, excluding only packed-record alignment. Complete
arena contents and the global pointer remain unchanged. Public tests require
neither retail assets nor original instruction bytes.
The private supplement also executes all 13 guard cases against the original,
with identical zero returns. Four bounded original instruction traces confirm
the neighbor and center-field read order, including the row-zero short circuit.

Both incremental GCC 13 and Clang 18 builds and all four public asset-free CTest
gates per compiler pass. The compile commands are unchanged, only the intended
object changes, and all other 145 compiled objects retain their hashes. In the
affected TU, the other 35 executable sections retain identical instructions and
relocations. The predicate shrinks from 829 to 694 bytes under GCC and 780 to 700
under Clang in the supported Debug builds. All recovered archive identities and
data names, classes, sizes and relative order remain unchanged. Scoped warnings
decrease from 26 to 24 GCC and 37 to 35 Clang, exactly the two explicit unsigned
comparisons; no warning, link or header baseline is raised.
Raw link checks retain 428 GCC / 680 Clang differences, and the header ratchet
retains its existing 14 failures. Manifest, split-source, generated metadata,
header/include freshness and whitespace checks pass.
The final full tooling suite passes all 139 tests in 16.437 seconds, with both
new public regression files unchanged throughout the run.

The existing batch-6 first-Road replay and frame comparisons remain the runtime
baseline. This predicate is outside the frozen 718-function native coverage set;
no native fixture or shared-state header changes. The bounded original-function
proof and collateral-object checks validate this refactor without another
coverage run or route/frame capture. No fresh runtime or visual result is claimed.

Private source freezes, original measurements, scope review, compiler checks
and exact commands are retained under
artifacts/readability/road-functions-20260906/batch-07/.

Reproduce from the WSL repository root:

```sh
python3 -m unittest discover -s tests/tools -p test_bare_bridge_candidate.py -v
python3 tools/update_split_manifest_hashes.py
python3 tools/audit_split_sources.py
```

The private original probe is at
artifacts/readability/road-functions-20260906/batch-07/original-proof/validate_original.py.
Its case, result and command files record the measured phases and exact commands.
Build commands and comparisons are in that batch's build-validation directory;
metadata commands are at
artifacts/readability/road-functions-20260906/batch-07/run-metadata.sh.
These private local scripts are absent from clean checkouts.

### Batch 8: `RoadBuildMode_BuildInSelectedDirection`

The callback at `0x4254E0` now reads the existing, pinned
`WorldMapActionWidgetRecord::default_sprite_index` instead of a raw DWORD at
an integer widget alias plus 16. The typed pointer and selector read remain
after the press animation, which pumps events. The current selected unit is
still read afterward; the callback clears the overlay hook, calls `Road_Build`,
installs the highlight hook and returns the viewport redraw result in order.
Removed stale register diagnostics and retained unresolved forwarded arguments.

The original jump table maps sprite selectors `0x1B..0x1E` to the existing
directions WEST=0, SOUTH=2, EAST=4 and NORTH=6. The typed field is signed, while
the former raw load was unsigned; all 32-bit patterns have the same four-case
classification. Unsupported selectors retain the canonical `-1` fallback.
Original incoming EDX controls that default but is absent from the recovered
ABI, so original fidelity is not claimed for that path. The comment retains
this ambiguity without asserting that the path is unreachable.

Track: Win95 reconstruction, the reached Road handler family. Evidence includes
the original function and jump table, the existing 53-byte widget layout, the
animation implementation and the installed callback fields. This is the tenth
individually reviewed Road helper; only its canonical body hash changes.
All 4157 identities, signatures, layouts and legacy hashes remain unchanged.

The private probe executes the unchanged original callback and four-entry jump
table against three explicit recording boundaries: animation, Road construction
and redraw. All 128 valid-selector traces match both the frozen before and
actual after bodies on GCC 13 and Clang 18 at O0/O2. Another 112 unsupported
selector cases preserve the frozen C++ behavior in the same four profiles;
these are deliberately separate from original-fidelity claims.
The asset-free regression in `tests/tools/test_road_direction_dispatch.py`
retains those traces as data and checks every named field in all four strict
compiler profiles, with warnings as errors and trapping UBSan except packed
alignment. It uses the actual native callee signatures, including the
animation's `uintptr_t` widget parameter.

Each trace records call order, widget arguments, selected unit, direction,
forwarded DWORD and eight finite binary64 patterns, hook transitions, final
state and the redraw return. Animation changes the selector and selected unit;
construction and redraw also mutate observed state to catch cached values or
late hook restores. Symbol addresses are compared through explicit hook
identities and a checked callback low-byte match; raw addresses differ across
executables. Widget bytes and unrelated test state remain as expected.
These checks establish the handler's call contract, without proving the three
instrumented callees' gameplay, animation or rendering behavior. NaNs,
infinities and arbitrary invalid widget pointers are outside this fixture.
Confidence is high for the bounded refactor, with the original default path
and the richer meanings of the forwarded arguments still unresolved.

Both supported incremental builds and all eight public asset-free gates pass.
Only this handler's executable section changes: GCC remains 203 bytes and Clang
changes from 220 to 219. The other 145 compiled objects and 35 neighboring
executable sections retain identical bytes, instructions and relocations.
Linked data classes, sizes and order remain unchanged. Scoped warnings stay
24 GCC / 35 Clang, with existing raw link/header ratchet failures retained and
no baseline changes. No new native coverage, route replay or frame claim is
made; batch 6 remains the runtime baseline and the turn-7 frontier is unchanged.
The final full tooling suite passes all 141 tests in 25.543 seconds. Manifest,
split-source and generated metadata/header/include checks pass; raw link
differences remain 428 GCC / 680 Clang and the header ratchet retains its 14
known failures. Final production and new public-test files remain frozen.

Private source freezes, original evidence, callback traces and build commands
are retained under artifacts/readability/road-functions-20260906/batch-08/.
The original-proof directory records capture, original measurement, canonical
comparison and exact command files; build-validation records the incremental
builds, public gates and tooling suite. Reproduce the focused public test with:

```sh
python3 -m unittest discover -s tests/tools -p test_road_direction_dispatch.py -v
```

### Batch 9: Road exit callbacks

Reviewed `RoadBuildMode_RequestExitAfterWidgetPress` (`0x4250F0`) and
`RoadBuildMode_RequestExit` (`0x425110`) individually. The pressed callback now
names its widget and animation result, initializes that result directly and
retains the call, exit-request store and return in their original order. The
direct callback already expresses its single flag assignment clearly and is
unchanged. These bring the Road family review to twelve functions.

The declaration database and generated headers now carry the pressed callback's
`widget` name and the previously reviewed normalizer's `overlayTileId` name.
Only these two parameter identifiers change; types, signatures and the complete
remaining declaration payload are unchanged. The normalizer body is unchanged.
One canonical body hash changes; all 4157 identities and legacy hashes remain.

Track: Win95 reconstruction, the reached Road handler family. Original bytes at
both entries and animation's EDX save/restore establish that the pressed callback
writes one after animation and returns its EAX result. This preserves the flag
write even if animation callbacks change it during the call. The exact reviewed
source operations and target code bytes, relocations and normalized disassembly
are identical before/after on GCC 13 and Clang 18 at O0/O2. No new behavioral
harness is warranted for these local names and direct initialization.

Both supported builds, all eight public asset-free gates and 52 targeted
declaration/header/tooling tests pass. All 146 objects retain identical
instructions and relocations; loaded code/data bytes and all defined symbol
addresses, sizes and classes remain identical. Only debug/source metadata,
the build ID and ELF section-table offset differ. Warnings do not increase
across the 140 rebuilt canonical sources; this TU retains 24 GCC / 35 Clang
warnings. Manifest, split-source and generated metadata/header/include checks
pass. Raw link differences remain 428 GCC / 680 Clang, and the header ratchet
retains its 14 known failures without baseline changes.

Confidence is high for this bounded contract. The forwarded `a2` meaning is
still unresolved: the animation currently ignores it and uses a fixed 20-tick
deadline, so naming it as a delay would exceed the evidence. No ABI or layout
changes, or runtime/campaign blocker removal, are claimed. Batch 6 remains the first-Road runtime
baseline; the turn-7 continuation frontier is unchanged. No new coverage, route
replay, rendering or visual-fidelity claim is made.

Private original extraction, source freezes, compile commands and declaration
comparisons are retained under
artifacts/readability/road-functions-20260906/batch-09/original-proof/.
Build commands and results are in that batch's build-validation directory;
static gate commands are in
artifacts/readability/road-functions-20260906/batch-09/run-metadata.sh.
The private scripts are absent from clean checkouts. Public generation checks:

```sh
python3 tools/update_split_manifest_hashes.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
```

### Batch 10: `RoadBuildMode_HighlightBuildableAdjacentTile`

The callback at `0x425120` now has four flat adjacency branches, typed signed
stack-coordinate reads and explicit eligibility stages. It reuses the existing
DWORD viewport and stack-address macros, names each stage's result and removes
the combined assignment/short-circuit expression and stale decompiler comments.
The bridge AP check still falls through to ordinary movement checks when it
fails. Every selected-stack/game-state read after a callee remains fresh.

Its return is deliberately not a boolean. Nonadjacent inputs return either
the original game-state-plus-stack-stride base or the signed selected column.
Other failures return zero movement cost, the castle query result, insufficient
AP or surface class 185. Success returns the widget refresh result after setting
the accumulated target flag. Rejections never clear that flag, and mutations
made by refresh remain visible after return.

Marker coordinates are still written before eligibility checks. The north X/Y
fields alias entries 43/44 of the live approach scan. The bounce view also shares
this backing, so each direction retains the original bounce-read and marker-store
order. No early screen/bounce reads, independent marker storage, frame clamp or
new direction convention is introduced. The guarded table initializer remains
the first operation. Unsigned viewport subtraction/shift and the subsequent
signed marker expressions preserve their existing types.

Track: Win95 reconstruction, reached mission-05 Road helpers. This is the
thirteenth individually reviewed function. The original instructions, pinned
stack/widget layouts and shared Road aliases support these changes; only this
function's canonical body hash changes. Signatures, layouts, all 4157 identities
and legacy hashes remain unchanged. Surface class 185 and the castle query's
mode 2 are retained without assigning richer semantics.

All 291 original-instruction traces match the frozen before and actual after
bodies under GCC 13 and Clang 18 at O0/O2: 2328 comparisons, each covering the
full call contract and shared state. The unchanged 938 original instruction
bytes execute against explicit recording/mutating eligibility, AP, movement,
castle, surface and refresh boundaries. All seven return categories and twelve
call sequences are covered, including the eight-call bare-bridge AP fallback.
The original uses static PE tables; the native fixture executes the actual
guarded initializer and verifies every relocated pointer identity.

Each 427-word trace retains boundary arguments/order, selected unit/game-state
changes, accumulated target state, marker/approach words and the complete Road
and Builder table bytes. Both game arenas must remain unchanged. Cases cover
the four marker choices, signed coordinate limits, DWORD viewport wrapping,
live bounce frames including overlapping north 9/10, east 23, south 36 and west
49, cold/warm initialization and protected viewport pages for nonadjacent exits.
Only genuine pointer returns are normalized; raw helper returns resembling
addresses remain integers and have dedicated cases. The complete measured
497028-byte trace hashes to
`1d8e6f8a84eb8a9295750490b2d82598f8da63eb8924793216de98d6bf0e56cd`.
Two south/frame-36 cases use distinct high X bits so that moving the bounce
read before the X store would change its value by 4660; this makes that access
order observable in the permanent regression.

Confidence is high within the tested call contract and defined arithmetic
domain. The probes exclude invalid pointers, out-of-backing frame reads, signed
coordinate/marker overflow and overflowing move-cost-plus-one arithmetic.
Instrumented callees do not establish their gameplay or rendering behavior.
The former body retains its existing logical-parentheses warning in the private
comparison; the refactored body compiles with strict warnings and trapping UBSan
apart from the established packed-alignment exception.

Both supported builds and all eight public asset-free gates pass. Only the
target's executable section changes: GCC 1147 to 1086 bytes and Clang 1137 to
1084. The other 35 executable sections in the TU and all 145 other compiled
objects remain identical. Ordinary object data and linked data classes, sizes
and order remain unchanged, with all 4157 recovered identities and zero library
crosscheck errors. Scoped warnings fall from 24 to 23 under GCC and 35 to 33
under Clang as the combined logical expression disappears. Manifest, split-source
and generated metadata/header/include checks pass. Existing link/header ratchet
failures remain without baseline changes.

Private candidate review, frozen before/after bodies, original evidence and
validation commands are retained under
artifacts/readability/road-functions-20260906/batch-10/.
The candidate-audit, original-proof, test-audit and build-validation directories
record their respective evidence and limits. These private scripts are absent
from clean checkouts. Batch 6 remains the first-Road runtime baseline and normal
turn-7 refresh/continuation remains the campaign frontier; this refactor adds no
route, rendering or visual-fidelity claim.

The final full tooling suite passes all 143 tests in 27.007 seconds, including
the 291-case public regression in four strict compiler profiles. Its provenance
stores 59 deduplicated table states and reconstructs the exact measured stream;
every boundary field and table byte is still compared. All 348 production/tooling
input hashes and final binary bindings remain stable through validation.
The host drive filled after those checks. In-place NTFS compression preserved
the build/evidence files, and an already-authorized Ubuntu restart restored
writable WSL. Post-recovery checks confirm all 348 input hashes, both binaries
and archives, and all eight private probe/trace pairs remain exact; all eight
public gates pass again. Recovery commands and integrity results are retained
under this batch's disk-recovery directory and check-after-recovery scripts.
The public regression extracts the actual production body:

```sh
python3 -m unittest discover -s tests/tools -p test_road_adjacent_highlight.py -v
```

### Batch 11: Builder_StartRoadBuildMode

Track: Win95 reconstruction, reached mission-05 Road mode. Reviewed
`Builder_StartRoadBuildMode` (`0x425540`) as the fourteenth Road-family function.
The entry guard, modal loop and shared cleanup now use named locals, typed stack
coordinates and widget flags, and flat direction checks. The carried frame-call
argument still receives either the animation index or hovered row delta; these
are two uses of the original EBX local. Callback order, fresh selected-stack
reads between redraws, late exit checks, raw returns and finite-double forwarding
remain intact. The two `Time_Now(0, 0)` calls were already repaired upstream in
the integrated `e13abc0` baseline and are retained.

Original instructions also establish two arithmetic repairs. The timer threshold
now subtracts ten in unsigned 32 bits before its strict unsigned comparison.
Cursor shifts use the captured unsigned byte masked to five bits, subtract their
origins with 32-bit wrap, and divide signed offsets by 64 toward zero. This
matches the original SAR/sign-compensation sequence for all scalar bit patterns.
The old carry macro promoted the final shift to unsigned: with raw X -32,
shift zero and origin 32, it produced 67108863 instead of the original -1.
That defined negative-coordinate mismatch is distinct from the old overflowing
signed subtraction and invalid shift-count cases. This batch therefore includes
an original-backed behavior repair, without changing the global carry macro.

The frozen `e13abc0` before body confirms the distinction in all four compiler
profiles: 171 of the 429 scenarios have defined old arithmetic, with 116 complete
traces matching the original and 55 differing because of the cursor defect.
The remaining 258 scenarios are excluded from old-body equivalence claims for
undefined timer or cursor arithmetic. All 429 actual-after traces match the
original; the original instructions are the acceptance reference for repairs.

The regression executes the actual production body and real guarded initializer
against 429 original-measured scripted cases under GCC 13 and Clang 18 at O0/O2.
The unchanged 780 original instruction bytes run at their original addresses,
with fourteen callees replaced by explicit recording/mutating boundaries.
Each profile agrees on 6760 boundary events, 37 state fields, raw return values
and final whole-region memory fingerprints. Those 32-bit fingerprints cover
both game arenas, render storage and normalized Road/Builder tables; they are
not literal byte-by-byte memory comparisons. The public fixture stores SHA-256
digests of the measured case traces and requires the same encoded inputs.

Cases exercise all 256 shift-byte patterns, signed pixel boundaries, viewport
wrap, four directional markers, continuation and failure, two clock samples,
callback-mutated selection/state, truthy non-Boolean returns and cold/warm
initialization. Six compiled negative controls reject signed timer subtraction,
unmasked shifts, lost carried row state, premature exit, clock-sample reuse and
cached stack reads across redraws. The three original clock/register pins remain;
the obsolete source-shape assertion is superseded by the measured loop contract.

Confidence is high for this bounded call/storage contract and the scalar
arithmetic proof. The original render array's overlapping shift byte is
normalized separately from the native standalone shift global; all actual shift
values are checked. Native diagnostics and initializer calls are checked as
native additions, without inventing original counterparts. Full original EBX
observations establish the carried local, not a newly recovered `DD_Pump` ABI.
The fixtures use valid low-address backing and finite binary64 inputs; invalid
pointers, NaNs, infinities and altered floating-point environments remain outside
the proof. Instrumented callees do not establish their gameplay or rendering.

One canonical manifest body hash changes; all 4157 identities, legacy hashes,
signatures and layouts remain. The separate first-Road runtime baseline from
batch 6 and mission-05 normal turn-7 refresh/continuation frontier are unchanged.
This batch adds no route or visual-fidelity claim.

Both supported incremental builds and all eight public asset-free gates pass.
Only this function's executable section changes: GCC 1443 to 1293 bytes, Clang
1462 to 1403. The other 12 executable sections and 145 compiled objects remain
exact, as do ordinary object data and linked data classes, sizes and order.
There are zero library crosscheck errors. Scoped warnings fall from 33 to 32
under each compiler. Manifest, split-source and generated metadata/header/include
checks pass. Existing raw link differences remain 428 GCC / 680 Clang, and the
header ratchet retains its 14 failures without baseline changes.

The integrated upstream baseline passes 254 tooling tests after installing its
missing Clang sanitizer runtime. The prerequisite list now includes
`libclang-rt-18-dev`. Both the initial dependency failure and successful repaired
baseline remain under this batch's build-validation/upstream-e13abc0 directory.
The final full tooling suite passes all 255 tests in 78.136 seconds, with the
production inputs, public fixture files and both binaries/archives frozen and
unchanged through validation.

After publishing Road commit `3cbbcb4`, integrated concurrent DLX work from
`18b6ace` with both histories retained. The separate integration builds and all
eight public gates pass. Only the incoming render object changes; the Road
object and all 144 other objects remain exact. Linked data and all recovered
identities remain unchanged, with zero crosscheck errors. The scoped audit
against that incoming main still finds only the Road function's current body
hash changed. Integration commands and bindings are retained in this batch's
integration-18b6ace and build-validation/integration-18b6ace directories.
The integrated full tooling suite passes all 255 tests in 113.784 seconds,
including the final provenance clarification. Metadata checks retain the same
14 header-ratchet failures and 428/680 raw link differences.

Private source freezes, original bytes, arithmetic audit, comparison streams,
negative controls and exact commands are retained under
artifacts/readability/road-functions-20260906/batch-11/.
Its original-proof, cursor-audit, test-audit, scope-audit, metadata and
build-validation directories record their respective evidence and limits;
private scripts are absent from clean checkouts. Reproduce the public regression
from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_road_build_mode.py -v
python3 -m unittest discover -s tests/tools -p test_road_mode_timing.py -v
```

### Batch 12: Road_Build

Track: Win95 reconstruction, reached mission-05 Road construction and movement.
Reviewed `Road_Build` (`0x424400`) as the fifteenth Road-family function. Four
explicit direction cases now select the target coordinates and origin road ID,
then enter a shared construction phase. This removes cross-case gotos and the
deeply nested movement tail. Named locals and existing packed stack/tile fields
replace register aliases and raw position/overlay reads. The twelve known
bridge-approach mappings are expressed directly, with their unresolved fallback
documented at the declaration. No signature, helper, layout or global changes.

All four connection queries still run before invalid-direction rejection.
Initial coordinates remain snapshots taken after logging; subsequent callbacks
retain their separate game-state and stack reloads. Both provisional bridge
conditions remain sequential. Saved overlay zero still suppresses restoration,
and the target's turn DWORD is never rolled back. Target rebuild/restoration,
the four otherwise-unused connection calls and changes surviving a null path
are preserved. The movement tail copies exactly 404 bytes before the legacy
free boundary, then executes the path, spends one construction AP and refreshes
the panel. Opaque forwarded arguments and the existing path-address width remain.

The required AP calculation now adds in unsigned 32 bits and then interprets the
result as signed. This recovers the original wrapping INC followed by signed
comparison, including `INT_MAX` move cost. It is an original-backed arithmetic
repair, not a claim of equivalence for the old signed-overflow cases.

All 494 original-measured scenarios match the actual refactored body under GCC
13 and Clang 18 at O0/O2: 1976 after comparisons and 8591 boundaries per profile.
The frozen before body matches all 492 scenarios with defined old arithmetic in
each profile; two `INT_MAX` cases are excluded from before-equivalence claims.
The probe executes 2748 unchanged original instruction bytes and the original
direction jump table against seventeen explicit recording/mutating callee
boundaries. Cases cover direction/truth combinations, invalid directions,
known approach mappings, bare and sequential crossings, failure gates, overlay
restoration, timestamp persistence, live state changes and null/nonnull paths.

Eight compiled negative controls reject signed AP overflow, the wrong rollback
sentinel, mutually exclusive bridge checks, a short path copy, a cached copy
destination, premature invalid-direction rejection, reloading the carried
execution column and removing the otherwise-unused target connection calls.

At the free boundary, the native probe compares both game arenas byte for byte
against their state after the path return plus exactly the intended 404-byte
copy. Other whole-region and queued-path observations use 32-bit memory
fingerprints; they are not literal byte-by-byte comparisons. The public fixture
stores SHA-256 digests of the complete measured case traces. Log and free
boundaries explicitly distinguish original register/stack observations from
the current native compatibility interfaces. Full carried-register observations
do not establish richer callee argument semantics or allocator recovery.

An unresolved original domain remains: a true approach predicate can reach an
overlay outside the twelve mapping assignments. The original then reads an
uninitialized stack slot, and current C++ also lacks a defined fallback. Two
original-only runs with the same scripted input and different incoming stack
values produce road words 4951 and 9320, confirming conditional stack dependence.
They do not establish retail reachability and are excluded from the accepted
native cases. The public fixture permits only the retained uninitialized
diagnostic naming this local; it does not initialize it to manufacture a clean
result.
Confidence is high within the documented mapping, valid backing and arithmetic
domains. Overlapping path buffers, invalid addresses, NaNs, infinities and
altered floating-point environments remain outside the proof. Callee gameplay,
the inert free stub and this unresolved mapping still require separate recovery.

Both supported builds and all eight public asset-free gates pass. Only this
function's executable section changes: GCC 2877 to 3209 bytes, Clang 3260 to
3166. The other 35 executable sections, ordinary allocated data and 145 other
objects remain exact. Linked data classes, sizes and order and all 4157 recovered
identities remain; library crosschecks report zero errors. Scoped warnings stay
23 under GCC and fall from 33 to 26 under Clang. One canonical body hash changes;
legacy hashes and frozen baselines remain. Manifest, split-source and generated
metadata/header/include checks pass. Raw link differences remain 428/680 and
the header ratchet retains its 14 existing failures.

The final full tooling suite passes all 257 tests in 82.104 seconds. The actual
production source, manifest, public regression/provenance and both binaries and
archives remain frozen through validation.

Private source/original freezes, boundary contracts, candidate review, measured
traces, counterexamples and exact commands are retained under
artifacts/readability/road-functions-20260906/batch-12/.
The candidate-audit, original-proof, test-audit, scope-audit, metadata and
build-validation directories record their respective evidence and limits;
private scripts are absent from clean checkouts. The existing first-Road
runtime milestone and normal turn-7 refresh/continuation frontier remain
unchanged. No new route, rendering or visual-fidelity claim follows. Reproduce
the public regression from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_road_build.py -v
```

### Batch 13: UnitStack_MoveOneTileInDirection

Track: Win95 reconstruction, reached Road and queued-movement fallback family.
Reviewed `UnitStack_MoveOneTileInDirection` (`0x424EC0`) as the sixteenth
Road-family function. Existing packed stack fields and named source/target
coordinates replace register aliases and raw reads. A null path returns early;
the successful path clearly copies, frees, executes and refreshes the panel.
The copy reloads gameData after path generation and retains the caller's stack
index, captured source column and opaque forwarded arguments.

The original sets EDX to 1 before copying the path. Its real free thunk and
free body preserve EDX through their normal return, proving the animation
argument at the subsequent execution call. Passing 1 removes the undefined
decompiler local. This requests animation; the executor can still disable it
under its own visibility rules. Target-coordinate additions now use unsigned
32-bit arithmetic followed by signed interpretation, matching the original ADD
instructions when live neighbor deltas overflow signed arithmetic.

All 230 original-measured scenarios match the actual refactored body under GCC
13 and Clang 18 at O0/O2: 920 comparisons and 629 call boundaries per profile.
The probe executes 162 unchanged original instruction bytes against four
explicit recording/mutating boundaries. The 89 defined null-path scenarios also
match the unchanged before body in all four profiles. Before equivalence excludes
133 nonnull paths with the undefined animation local and eight additional null
paths with signed coordinate overflow. Original/after is the acceptance reference
for those repairs; no initialized substitute for the old body is used.

Cases cover all 32 backed doubled-index table accesses, signed coordinates and
char conversion, distinct and wrapping live deltas, finite binary64 forwarding,
null/nonnull paths and state mutations at each call. At the free boundary both
probes check both game arenas byte for byte against the post-path state plus
exactly the intended 404-byte copy. Other whole-region and queued-path
observations use 32-bit fingerprints; the public fixture stores SHA-256 digests
of complete measured traces. These are distinct forms of evidence.

Ten compiled negative controls reject lost selection, incorrect animation,
cached destination, short copy, reloaded source column, wrong table stride,
wrong unit-index forwarding, wrong success return and signed addition on each
coordinate axis. The overflow controls run under the same UBSan checks as the
actual body; alignment checks are disabled for the recovered packed layout.

The original neighbor windows overlap by one DWORD; their 64 physical words
match the two current native initializers. The fixture explicitly projects
those words into both separate native arrays and checks every native cell.
This establishes the helper's accesses for indexes 0..31, not global array
aliasing. No clamp, mask, new direction policy or storage change is introduced.
Original free-register checks are separate from the native no-argument inert
free seam; allocator behavior is not recovered by the recorder.

Confidence is high within valid positive signed-low32, nonoverlapping backing
and finite binary64 inputs. Invalid indexes/addresses, unrelated address
overflow, NaNs, infinities and altered floating-point environments are outside
the proof. Instrumented callees do not establish their gameplay or rendered
output. No signature, public name, layout, global or table changes; only this
canonical manifest body hash changes and all 4157 identities remain.

Both supported builds and all eight public asset-free gates pass. Only this
function's executable section changes: GCC 286 to 303 bytes, Clang 263 to 281.
The other 35 executable sections, ordinary allocated data and 145 other objects
remain exact. Linked data classes, sizes and order remain unchanged; library
crosschecks report zero errors. Scoped warnings fall from 23 to 22 under GCC
and 26 to 25 under Clang, removing this function's undefined-argument diagnostic.
Manifest, split-source and generated metadata/header/include checks pass.
Existing raw link differences remain 428 GCC / 680 Clang and the header ratchet
retains its 14 failures. Frozen baselines and legacy hashes remain unchanged.

The final full tooling suite passes all 259 tests in 146.455 seconds. The
production inputs, public regression/provenance and both binaries and archives
remain frozen through validation.

Private source/original freezes, original free-register evidence, measured
traces, before-domain classification and exact commands are retained under
artifacts/readability/road-functions-20260906/batch-13/.
Its candidate-audit, original-proof, test-audit, scope-audit, metadata and
build-validation directories record their respective evidence and limits;
private scripts are absent from clean checkouts. The separate first-Road
runtime milestone and normal turn-7 refresh/continuation frontier are unchanged.
No new route or visual-fidelity claim follows. Reproduce the public regression
from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_one_tile_movement.py -v
```

### Batch 14: Rules_BuildRoadOrStepTowardQueuedPath

Track: Win95 reconstruction, Road and queued-path orchestration. Reviewed
`Rules_BuildRoadOrStepTowardQueuedPath` (`0x454AE0`) as the seventeenth
Road-family function. Typed stack fields, named waypoint decoding and deltas
replace repeated raw expressions. Four diagonal cases select horizontal and
vertical attempts, and one shared loop expresses the original Road-then-move
or movement-only policy.
This removes duplicated switches, register aliases and cross-branch gotos.

The original initializes ECX from the input stack index at entry. Each of its
five callees preserves that register on normal return, proving the index used
for every query/action and final clear. The refactor uses the input directly,
replacing the undefined cur_stack_index local. This is an original-backed
repair; only empty-path inputs have a defined unchanged-before reference.

An empty path still returns 1 without callbacks or writes. Nonempty paths read
the final waypoint, obtain a direction, then reload coordinates for the owner
query. The bridge query remains conditional on a nonzero owner result. The
chosen policy and direction stay fixed across action callbacks, while the final
path-count clear reloads gameData and retains the original input index. Every
nonempty route returns 0, even after successful movement; only the four-byte
count is cleared and all waypoint data remains.

Each diagonal tries its horizontal component before its vertical fallback.
Road-first attempts call Road, then move only on zero; any nonzero action
result stops further attempts. Road receives the chosen step direction and
the separate low byte of the original Facing result, together with unchanged
opaque a2 and finite a3. Other raw directions retain the original default
dispatch without a new clamp or mask. The real Facing helper returns 0..7;
scripted values outside that range describe only a conditional caller contract.

All 255 original-measured scenarios match the actual refactored body under GCC
13 and Clang 18 at O0/O2: 1020 comparisons and 1275 call boundaries per profile.
The probe executes 573 unchanged original instruction bytes and the two original
switch tables, totaling 56 bytes, against five recording/mutating callee entries.
There are 241 empty-path or Direction8 cases and 14 separately labeled cases
with scripted raw Facing values outside 0..7. The latter do not establish that
the real Facing or movement callees support those values.
All nine empty-path cases also match the unchanged before body in four compiler
profiles. The 246 nonempty cases are excluded from before equivalence because
they read the undefined index; no initialized substitute is used as an oracle.
Twenty-one of those same cases also overflow the old signed count arithmetic.

Cases cover every count 0..100, 24 backed raw-count cases, coordinate and
waypoint widths, cost-byte independence, owner/bridge short-circuiting, each
possible stopping point,
truthy non-Boolean results and live changes at every callback. Both recorders
compare the final two game arenas byte for byte against their post-last-call
state plus exactly the four-byte count clear. Empty cases require byte equality
with the initial arenas. Arguments and 42 mutable state fields are recorded as
raw 32-bit words; eight queued-path observations and the final arena summaries
use 32-bit fingerprints. The public fixture stores SHA-256 digests of measured
traces. These are separate checks rather than universal byte-equivalence claims.

Fourteen compiled negative controls reject the wrong carried index, cached owner
coordinates or cleanup backing, reversed fallback order, broken bridge
short-circuiting, first-waypoint selection, signed target-byte interpretation,
wrong Road byte forwarding, whole-path erasure, wrong return and treating only
1 as truthy. The expanded controls also reject a capacity clamp, unwrapped
address arithmetic and restoring typed-array indexing. No compilation failure
is counted as a behavioral rejection.

The waypoint address preserves the original 32-bit scaled-address wrap, using
a named byte offset and a four-byte copy into a local PathWaypoint. An initial
typed-array candidate passed conventional counts but lost readable raw aliases:
original count `0x40000001` reads waypoint 0, while `0x40000000` reads the count
word itself. Fresh original counterprobes confirmed both before publication.
The revised address calculation also retains backed reads for counts 101/102
and `0xFFFFFFFF`, without inventing a capacity clamp. Their game/save-state
reachability is not established. Initial evidence remains preserved and is
superseded by the expanded proof; the first 231 case traces remain exact.

Decoded waypoint coordinates are unsigned bytes and stack coordinates are
signed16, so their deltas fit signed32. The source record and resolved four-byte
address must have valid backing. Invalid indexes, unrepresentable source-record
addresses and asynchronous mutation remain outside this recovery. No public
name, signature, layout, global, helper or
source table changes; only the target's canonical body hash changes and all 4157
recovered identities remain.
Confidence is high within this documented caller/storage domain. Scripted
callees do not establish pathfinding, Road construction, movement or rendering;
NaNs, infinities and altered floating-point environments remain outside the
finite-bit forwarding checks.

Both supported builds and all eight public asset-free gates pass. Only this
function's executable section changes: GCC 1227 to 641 bytes, Clang 1021 to
621. The 61 neighboring executable sections and 145 other objects remain exact.
Scoped warnings fall from 39 to 38 under GCC and 40 to 39 under Clang, removing
the undefined-index diagnostic. Library crosschecks report zero errors; all
linked symbol classes, sizes and order remain unchanged.

Clang also replaces the target's two native compiler switch tables with one,
shrinking its local dispatch data from 112 to 56 bytes. Every relocation in
both versions points inside this function. The initial blanket allocated-data
comparison correctly flagged this difference and remains preserved; the scoped
audit accepts only this proven local dispatch change. All other allocated
object data is identical. Linked checks preserve named data classes, sizes and
order; the final local dispatch table is checked against its target-relative
object relocations. Original executable/table proof bytes are unchanged. Manifest,
split-source and generated metadata/header/include checks pass. Raw link
differences remain 428 GCC / 680 Clang and the header ratchet retains its 14
existing failures without reseeding any baseline.

Private source/original freezes, register-preservation evidence, switch-table
decoding, candidate review and exact commands are retained under
artifacts/readability/road-functions-20260906/batch-14/.
Its candidate-audit, test-plan, original-proof, test-audit, scope-audit, metadata
and build-validation directories record their respective evidence and limits;
their raw-count-revision subdirectories contain the final expanded comparisons.
The final revised full tooling suite passes all 261 tests in 90.397 seconds.
All 399 production/tooling inputs, the public regression/provenance and both
binaries and archives remain frozen through that run and final verification.
Private scripts are absent from clean checkouts. The separate first-Road runtime
milestone and normal turn-7 refresh/continuation frontier remain unchanged.
This caller recovery adds no campaign or visual-fidelity claim. Reproduce the
public regression from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_road_path_fallback.py -v
```

### Batch 15: Rules_IsQueuedPathTargetBridgeCrossing

Track: Win95 reconstruction, Road/queued-path query orchestration. Reviewed
`Rules_IsQueuedPathTargetBridgeCrossing` (`0x454A20`) as the eighteenth
Road-family function. The function now reads the existing typed stack/path,
copies the target waypoint into a named `PathWaypoint`, and directly normalizes
the bridge-cost result. Repeated offset expressions and register aliases are
removed. The empty-path return remains zero with no call or write.

The original reads stable, nonvolatile count/base storage without an intervening
call or write. The refactor preserves its unsigned 32-bit waypoint-address
arithmetic, including backed raw counts that wrap to the count word, earlier
waypoints or adjacent bytes. It does not introduce a capacity clamp. Row and
column remain the first two unsigned bytes; the cost word is ignored. The
single bridge-cost call receives those two values, and every nonzero result
becomes exactly one. State changed by that call is retained without a late
read, path clear or other caller write.

The probe executes all 128 unchanged original instruction bytes, excluding the
following 56 bytes of the neighboring caller's switch tables. All 283 scenarios
match both the unchanged before body and the actual refactored body under GCC
13 and Clang 18 at O0/O2: 1132 comparisons for each version. They include nine
empty paths, every conventional count 0..100, 48 backed raw-count cases,
unsigned coordinate boundaries, cost-word independence and callback mutations.
The 274 call events record exact arguments and state. Both recorders compare
their complete game arenas and selected/base globals before and after the
callback, enforcing no caller writes. Path/arena fingerprints in the traces
are separate observations; the public fixture stores SHA-256 trace digests.

Twelve compiled negative controls reject incorrect empty returns, clamping,
waypoint choice, coordinate order/signedness, stack selection, normalization,
pre-call writes, post-call clearing, late count reads and unwrapped addresses.
Every control compiles before its runtime or trace rejection is counted.

The real bridge-cost implementation returns only zero or five. Seven scenarios
with other scripted results test the conditional normalization contract, not
additional real callee behavior. The source record and resolved four-byte
waypoint address require valid backing. Raw-count game/save reachability,
asynchronous mutation, invalid stack indexes and the real map's support for
every forwarded byte coordinate are not established by this caller fixture.
Confidence is high within this documented storage/call domain. No public name,
signature, layout, global or table changes; only the target's canonical body
hash changes and all 4157 recovered identities remain.

Both supported builds and all eight public asset-free gates pass. Target code
shrinks from 224 to 175 bytes under GCC and 224 to 143 under Clang. All 61
neighboring executable sections, the other 145 objects and ordinary allocated
data/relocations remain exact, including the neighboring caller's Clang switch
table. Scoped warnings remain 38 GCC / 39 Clang. Linked data classes, sizes and
order remain unchanged, with zero recovered-library crosscheck errors.
Manifest, split-source and generated metadata/header/include checks pass.
Raw link ratchets retain 428 GCC / 680 Clang differences and the header ratchet
retains its 14 existing failures; no baseline is raised.

The final full tooling suite passes all 263 tests in 79.401 seconds. All 401
production/tooling inputs, the public test/provenance pair, both executables and
archives, and all 146 objects per compiler remain frozen through final checks.

Private source/original freezes, exact commands, compiled negative controls and
validation reports are retained under
artifacts/readability/road-functions-20260906/batch-15/.
Its candidate-audit, original-proof/final-review, test-audit, scope-audit,
metadata and build-validation directories record the respective evidence and
limits. Private scripts are absent from clean checkouts. The separate first-Road
runtime baseline and normal turn-7 refresh/continuation frontier remain
unchanged. No new route or visual-fidelity claim follows. Reproduce the focused
public regression from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_queued_path_bridge_query.py -v
```

### Batch 15 integration with DLX and class recovery

Merged the published DLX/class checkpoint `b2f3764` with the bridge-query commit
`3ee98b4` at `70ed898`. The two documentation conflicts retain both histories.
Relative to incoming main, only the seven reviewed bridge-query files differ;
all other manifest records and schema fields remain identical. The schema-3
manifest retains 4157 historical identities, 144 ordered source files, 11
canonical class methods and the existing adapters/aliases.

Both clean combined builds and all eight explicit public CTests pass. Full
warning totals are 6579 GCC / 6581 Clang, exactly matching incoming categories.
Strict comparisons against the final incoming snapshots pass without additional
allowances: linked identities, named storage, data order and initialization
remain. In strategic002, only the query's code/instructions/relocations differ;
the 61 neighboring executable sections and ordinary allocated data remain exact,
including the Clang Road caller's 56-byte table and seven relocations. Unwind
and nonallocated debug metadata are excluded from that object comparison.

Manifest, split-source, coverage/save metadata, generators and class inventories
pass. The stricter incoming header limits remain, with their 22 existing
failures, and raw link differences remain 441 GCC / 693 Clang with zero library
crosscheck errors. No baseline is raised. The original bridge-query proof and
public regression bindings remain exact through integration.

All 518 combined tooling tests pass in 183.528 seconds with no skips. All 736
production/tooling inputs, both executables/archives, all 150 objects per
compiler and both compile-command files remain unchanged through that run.

Exact commands, source/reference freezes, scope checks and preserved comparison
reports are under
artifacts/readability/road-functions-20260906/batch-15/integration-validation/
and the sibling integration-scope directory. These private scripts are absent
from clean checkouts. Incoming first-Road replay/frame evidence remains tied to
its recorded `8e7b694` source checkpoint; this combined build adds no runtime,
visual-fidelity or campaign milestone claim.

### Batch 16: Move_CommitIfWithinCost

Track: Win95 reconstruction, upstream Road/queued-path orchestration. Reviewed
`Move_CommitIfWithinCost` (`0x454210`) as the nineteenth Road-family function.
The function now uses existing packed stack/path/unit fields, named coordinates,
explicit call phases and early exits. Original 32-bit address arithmetic replaces
signed intermediate addresses, with fresh game-data reads after Execute, the
bridge/Road phase and integer-node construction. No name, signature, layout or
shared table changes; only this function's canonical body hash changes, retaining
all 4157 historical identities and schema-3 method/adapter metadata.

The original forwards incoming EBP to both Execute and Road. The previous caller
instead passed the stack index as Execute's fourth argument. The recovered
caller now forwards its existing argument there. This is a defined discrepancy
at the call boundary; a reached gameplay effect is not established. The real
Execute implementation has its own register recovery, outside this batch.

The empty path returns zero without a callee call or world-state write. Every
nonempty path executes before the index check, which accepts 0..500 inclusive,
followed by the signed16 first-unit-type check accepting 0..40. These bounds
are preserved exactly; the unit-type registry count is not a substitute.
Any nonzero bridge result calls
Road, whose result is ignored. If fresh coordinates still equal the entry
coordinates, the caller interns zero, calls the PA slot writer and returns one.
The slot-put result is also ignored. The original 24-byte local value buffer
initializes only its type and integer-node words; the proven scalar consumer
chain uses only those words. The saved incoming ECX lies outside that buffer.
The existing four-byte record tail is copied as an instance argument without
claiming additional field ownership or structure semantics.

All 288 unchanged original instruction bytes execute in the retained proof.
The actual production body matches all 140 scenarios and 411 call events under
GCC 13 and Clang 18 at O0/O2: 560 comparisons. Per compiler profile, the unchanged
before body has 115 exact matches and 12 defined mismatches confined to Execute's
fourth argument. Thirteen high-address cases are excluded from before equivalence
for distinct reasons: ten signed-addition overflows and three negative-int
addresses sign-extended into invalid native pointers. Retained diagnostic probes
confirm both classes; the original and recovered caller execute all 13 with
backed storage. No patched before body serves as an oracle.

Two complete 0x90000-byte arenas at 0x10000000 and 0x7FFE0000 back records -1, 0,
1, 499, 500 and 501. Full arena byte comparisons and exact checks of gameData
and selection before every callback and return enforce absence of caller
world-state writes and preserve scripted mutations.
Compact path/arena fingerprints are separate observations. Required registers
and finite floating-point forwarding are checked at the recording boundaries.
Fifteen compiled negative controls are rejected. An initially surviving stale
post-query-base control exposed equal-coordinate test data; two appended cases
change the fresh arena's coordinates and reject it. That failed sensitivity
result remains preserved. Earlier input case payloads, excluding the changing
four-byte case-count header, and complete output trace prefixes remain exact.

Confidence is high within the documented backed-storage and caller domain.
Five recording boundaries replace actual movement, bridge query, Road building,
CLIPS interning and slot storage. Scripted non-Boolean returns, raw integer-node
words and mutations test conditional caller behavior, not additional real
callee behavior. Arbitrary unbacked indices, asynchronous/volatile mutation,
NaNs, infinities and altered floating-point environments remain outside this
proof. No runtime route, visual-fidelity or campaign milestone is promoted.

Both production builds and all eight explicit public CTests pass. Only the
target's code, instructions and relocations change: 433 to 468 bytes under GCC,
399 to 430 under Clang. The 61 neighboring executable sections, ordinary
allocated data/relocations, Clang's neighboring 56-byte Road dispatch table and
its seven relocations remain exact. All 149 other objects per compiler and both
compile-command files remain unchanged. Unwind and nonallocated debug metadata
are excluded from the object comparison. Strict linked class/storage/order and
initialization comparisons pass without allowances. Scoped warnings remain
38 GCC / 39 Clang; raw link ratchets retain 441 / 693 differences with zero
library crosscheck errors. Manifest, split-source, metadata, generators and
class inventories pass. All 22 existing header failures, their complete metrics
and stricter limits remain unchanged. No baseline is raised.

All 520 tooling tests pass in 172.354 seconds, with no skips. All 738
production/tooling inputs, both binaries and archives, all 150 objects per
compiler and both compile-command files remain frozen through the full run.

Private original/source freezes, exact commands, independent trace decoding,
before-domain diagnostics and compiled negative controls are retained under
artifacts/readability/road-functions-20260906/batch-16/.
The original-proof/fresh-coordinate-extension and test-audit directories bind
the actual source to the reviewed candidate and public fixture. The scope-audit,
metadata and build-validation directories record integration checks. Private
scripts are absent from clean checkouts. The public test requires only tracked
sources and its provenance JSON, with no retail assets or original executable.
Run it from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_movement_commit.py -v
```

### Published CI observation after batch 16

Remote CI remains failed at the inherited header and linked-symbol ratchets.
The [6126b40 run](https://github.com/lisu188/clash-disassembly/actions/runs/34744304390)
and [preceding 1ca2457 run](https://github.com/lisu188/clash-disassembly/actions/runs/34743423928)
fail the same three steps. Both compiler builds, warning gates, all eight public
CTests, unit-runner policy tests and the separate coverage job pass. The later
run also passes all 520 tooling tests in 160.539 seconds.

All emitted CI failure rows match between the two runs: 15 printed header rows
and 80 printed link rows per compiler. Exact published header metadata recovers
the same complete 22 header failures; retained local binary snapshots reproduce
all 441 GCC / 693 Clang link differences and agree with the CI totals and every
printed row, with zero library crosscheck errors. The unprinted link rows are
local reconstruction evidence, not a complete remote CI log. No baseline or
workflow was changed for this observation.

The 6126b40 coverage job measures 6163 of 6652 lines (92.65%) across its fixed
718-function set, with 585 fully covered functions and zero uncovered functions.
The preceding run measures 6157 lines and 584 fully covered functions. These are
the coverage harness's scope and thresholds, not coverage of all 4157 recovered
identities. The complete CI workflow still requires genuine header-dependency
and linked-surface repairs before it can pass.

Run metadata, job logs, failed logs, normalized comparisons and exact commands
are retained under artifacts/readability/road-functions-20260906/batch-17/ci-observation/.

### Batch 17: Rules_MarchToTemple

Track: Win95 reconstruction, upstream Road/queued-path orchestration. Reviewed
`Rules_MarchToTemple` (`0x454330`) as the twentieth Road-family function.
Its name is the canonical source/manifest name; this address has no public map
entry. Named stack, waypoint, coordinate and generated-path values replace raw
accesses and register aliases. The two uninitialized ECX values are recovered
as the original stack byte offset at the post-Execute type read and PA call.
Unsigned arithmetic preserves original 32-bit addresses and distance behavior.
Only this body's canonical hash changes; all 4157 historical identities,
144 source entries and schema-3 method/adapter metadata remain.

Every nonzero entry count reads the first waypoint, independent of the count's
magnitude. The original row-first subtraction and absolute value wrap at 32
bits, with a signed comparison against one. INT_MIN remains negative and is
accepted by that comparison; widening the distance or saturating it changes
the recovered behavior. A far waypoint clears only the count DWORD. If a path
is then needed, a nonnull generated track is copied as exactly 404 bytes into
the fresh game-data base, followed by the existing free boundary. A null return
still permits generator changes to be observed by the final count read.

The final count and signed16 coordinates are read after generator/free. Execute
receives the index, animation flag one, the previous column's low byte, the
index again and the forwarded double. The index and signed first-type bounds
remain after Execute, accepting 0..500 and 0..40 respectively. The original
repeated type==-1 read remains before coordinate comparison, although no stable
synchronous state can satisfy it after the preceding type check. No invented
inter-read callback is used to exercise that branch. Unchanged coordinates
lead to integer-zero construction and a PA slot-writer call using a fresh
instance tail. Its separate third argument is the byte offset, not scalar type
one. Only the six-word local buffer's type/node fields are initialized and
consumed by the proven scalar chain; Put's result is ignored.

The retained probe executes all 604 unchanged original instruction bytes,
excluding the following four alignment bytes. All 224 scenarios and 514 call
events match the applied body under GCC 13 and Clang 18 at O0/O2: 896
comparisons. All 69 defined unchanged-before scenarios also match in those
profiles, giving 276 before comparisons. The first-defect exclusions partition
the other 155 cases: 25 signed-address additions, 119 uninitialized-v10 uses,
four signed absolute-value negations, four signed subtractions and three
negative-int addresses widened to invalid native pointers. Later overlapping
defects, including v13, remain recorded separately. A sanitizer's failure to
report a statically undefined expression does not make that case a valid before
oracle; the retained diagnostic limitations are explicit in the provenance.

Exact whole-arena comparisons and checks of gameData/selection admit only the
29 observed four-byte count clears and 50 complete path copies. Both entire
512-byte source-track regions, including their guards, are checked as well.
The two game arenas back records -1, 0, 1, 499, 500 and 501 across the signed
address boundary. Scripted changes distinguish fresh destination/count/type/
coordinate/instance reads after the relevant callbacks. Twenty-three compiled
negative controls are rejected with explicit first witnesses. Compact trace
fingerprints are separate from the literal full-buffer guards.

Original allocation dataflow corroborates a separate 404-byte result that the
bridge-corner helper returns unchanged or replaces with null. With a valid heap,
that allocation is disjoint from live game data. The copy proof assumes backed,
nonoverlapping regions and the original clear direction flag. The original-only
adapter verifies the returned pointer in EAX at free and the copy registers;
the common native free call has no arguments and the compatibility thunk is
inert. This batch therefore does not recover allocation release or claim full
generator/free equivalence. The actual generator, movement, CLIPS allocation/
storage, asynchronous state changes and altered floating-point environments
remain outside the recording boundaries. Finite double forwarding, conditional
raw node words and scripted mutations establish caller behavior only.

Confidence is high within that documented caller/storage domain. No public
symbol, signature, shared layout or table is renamed. The instance tail retains
its unresolved ownership semantics. No temple arrival, Road continuation,
runtime route, visual-fidelity or campaign milestone is promoted.

Both incremental compiler builds and all eight public CTests pass. Scoped
strategic warnings fall from 38 to 36 with GCC 13 and from 39 to 37 with Clang 18,
removing the two uninitialized values. Target code grows from 685 to 774 bytes
with GCC and from 651 to 722 with Clang. Only the target executable section,
instructions and relocations change; all 61 neighboring executable sections,
ordinary allocated data and the Clang Road table's 56 bytes/seven relocations
remain exact. All 149 other objects per compiler remain unchanged. Strict
class-aware linked comparisons pass without allowances. The complete inherited
22 header failures and raw 441 GCC / 693 Clang link differences remain, with
zero crosscheck errors; no baseline is raised. The earlier CI observation above
remains failed overall and these local comparisons do not promote it to green.

All 522 tooling tests pass in 161.964 seconds without skips. All 740 production
and tooling inputs, both binaries/archives, 150 objects per compiler, compile
commands and the 147-member archive ordering stay frozen through validation.

Private original/source freezes, exact commands, independent before-domain and
trace reviews, allocation-route corroboration and negative controls are under
artifacts/readability/road-functions-20260906/batch-17/.
The candidate-audit, original-proof, test-plan and test-audit directories retain
their respective proof and limits; scope-audit, metadata and build-validation
record integration. Private scripts are absent from clean checkouts. The public
regression uses tracked source and provenance without retail assets:

```sh
python3 -m unittest discover -s tests/tools -p test_temple_march.py -v
```

### Published CI observation after batch 17

The [4033aa8 CI run](https://github.com/lisu188/clash-disassembly/actions/runs/34746704424)
completes with the same three inherited failures as 6126b40: header coupling and
both linked-symbol ratchets. Both builds, all eight public CTests, unit-runner
policy checks and all 522 tooling tests pass; the tooling run takes 160.771
seconds. Complete compiler logs show warning totals fall from 6579 to 6577 for
GCC and 6581 to 6579 for Clang, with no increased warning category.

All 15 emitted header rows match; exact published metadata confirms all 22
header failures remain. All 80 emitted link rows per compiler and aggregate
441 GCC / 693 Clang differences match, with zero crosscheck errors. Downloaded
diagnostic logs agree with the workflow output. Unprinted remote link rows
remain uninspected. The separate coverage gate remains 6163/6652 lines (92.65%)
across its selected 718 functions: 585 fully covered, 133 partial, none uncovered.
This passing coverage job does not make overall CI green or cover all identities.

Full run/job metadata, logs, diagnostic artifacts, exact published inputs and
comparisons are retained under
artifacts/readability/road-functions-20260906/batch-17/ci-final-observation/.
No unexpected regression is found in this observation.

### Bootstrap command-line symbol and state scanner

Track: Win95 reconstruction, repair an inherited linked-symbol regression.
The private 1024-byte bootstrap command-line buffer now explicitly retains its
historical host-build assembler name, `g_boot_command_line`. The C++ name,
static linkage, type, array bound, declaration order and all consumers remain.
This name comes from the frozen host-build contract; it is not a newly recovered
retail Win95 public symbol. The existing GNU assembler-label style avoids adding
a broad recovered-ABI include to the bootstrap.

The first two builds compiled and linked the annotation, then failed their
embedded split audit: `declared_state_names` no longer recognized the buffer
when an assembler label followed its declarator. The existing inventory correctly
recorded its three bootstrap consumers. The scanner now removes explicit GNU
string-label clauses from its lexical declaration view after masking function
bodies. It preserves the original declaration matcher, ignores labels inside
comments/literals, and retains the C++ state name. Macro/expression labels and
arbitrary C++ declaration parsing remain outside this lexical scanner's scope.

Four new regression methods cover 18 scalar/array label cases across `asm`,
`__asm` and `__asm__`, function/prototype/local exclusions, direct-state drift,
and local-static constraints. The unchanged scanner fails the real inventory,
the direct-state fixture and all 18 supported-label cases. All 34 targeted tests
pass with the applied repair; every existing test body remains unchanged.
The actual state-name set gains only the missing buffer and the three inventory
errors disappear. Both the support inventory and recovered manifest remain
byte-identical. No identity, class mapping or Road-function count is changed.

Both final incremental builds pass, with no bootstrap diagnostics. Their native
objects and binaries are exactly those retained from the first attempts; only
the corrected embedded audit needed to rerun. Raw link differences fall from
441 to 439 GCC and 693 to 691 Clang, removing exactly the two missing/new buffer
name rows in each complete local comparison, with zero crosscheck errors.
The untouched strict checker reports the one expected `linked_data_ordered`
change at the same sequence position; all other fields compare exactly. This
raw failure remains recorded, and no data allowance or baseline update is used.

Independent ELF comparison confirms the buffer remains one local 1024-byte BSS
object at the same address and alignment in each profile, at ordered-data slot
1015. Literal runtime code/data, unwind/GOT/initializer bytes and all runtime
relocation tuples match under the single exact buffer/section name correspondence.
All other symbol tuples retain their sequence, and 26 corruption controls reject
changes to storage, code, relocations and ordering. Both build-ID descriptors
change while their note layout remains. Nonallocated symbol/string metadata
changes; Clang also changes DWARF/debug-string metadata, recorded separately.
The other 149 objects, complete recovered archive, its 147-member order and
compile commands remain exact. The first-Road runtime endpoint and campaign
frontier are unchanged; no new game process or visual milestone is claimed.

All eight public CTests and all 526 tooling tests pass; the full tooling run
takes 139.034 seconds without skips. All 740 production/tooling inputs and four
workflow files, both compiler output sets and 150 objects per compiler remain
frozen through final validation. Metadata and freshness checks pass apart from
the same complete 22 inherited header failures. The remaining raw link failures
are still visible; this repair does not make overall CI green.

The initial failed build/metadata attempts, revised freeze, parser regression
proof and exact commands are retained under
artifacts/readability/ci-bootstrap-command-line-20260913/.
The candidate-audit and state-name-parser-audit directories retain their original
planning states and actual follow-up proofs; build-validation, metadata-02 and
scope-audit-02 contain the integrated checks. Public regression reproduction:

```sh
python3 -m unittest discover -s tests/tools -p test_support_class_inventory.py -v
```

### Published CI observation after the bootstrap repair

The [a40417b CI run](https://github.com/lisu188/clash-disassembly/actions/runs/34747910860)
passes both builds, four asset-free CTests per compiler, the unit-runner policy
checks and all 526 tooling tests (169.218 seconds). The linked-symbol jobs report
439 GCC / 691 Clang differences with zero library crosscheck errors, matching
the complete local measurements. Overall CI still fails the header and both
linked-symbol ratchets; these passing build/test results do not resolve them.

The separate coverage job measures 6161/6652 lines (92.62%) across the same 718
selected functions: 584 fully covered, 134 partial and none uncovered. These are
this run's measurements; the earlier Temple run's 92.65% is retained separately.
Run metadata and complete job logs are retained under
artifacts/readability/ci-road-dependency-20260913/build-validation/ci-observation/.

### Road widget ownership and header dependencies

Track: Win95 reconstruction, inherited CI dependency repair. The complete
`WorldMap_EnsureBuilderWidgetTables` helper and original
`WorldMap_ComputeBuildMenuActionFromCursor` selector now reside together in
`src/buildings/0040A0A0_0040A0A0_buildings_001.cpp`. The Road consumers and
callbacks already belong to buildings. Their table initialization therefore
no longer exposes three Road callbacks through the buildings public interface
to world. The world menu still calls the same initializer at the same point.

Both names, signatures, linkage and complete bodies remain. The original
selector retains address 0x0040A0A0, its world-origin comment and all historical
manifest fields. The reconstruction helper gains no original identity. The
trimmed world file now ends at 0x0040A040. The explicit inventory appends the new
buildings TU and retains the existing order; its count increases 144 to 145.
Current manifest, declaration, class-registry and three coverage-source paths
follow the physical move. Historical evidence remains, with both relocations
recorded in `docs/SOURCE_PATH_MAP.csv`.

Source comparison preserves all 94 definitions in the affected files, all five
initializer call positions and every original body hash across 4,157 identities.
The initializer still copies 322 builder bytes and 706 Road bytes, relocates
42 then 70 pointer fields, and sets its single guard last. Its 19 text objects,
shared sound-string pointer, null fields, overlapping Road scan and warm-call
behavior remain. All state definitions stay in the existing state TU.

The full generated surface equals the reviewed transition. Nine of 70 compared
headers change, preserving the exact declarations and linkage. The existing
include-policy and visibility checks pass, and frozen limits remain unchanged.

| Metric | Before | After | Frozen limit |
| --- | ---: | ---: | ---: |
| World public functions | 53 | 52 | 52 |
| Buildings public functions | 161 | 159 | 158 |
| World to buildings function dependencies | 46 | 44 | 43 |
| Buildings to world function dependencies | 28 | 27 | 27 |
| Shared globals | 243 | 244 | 244 |
| Failing header metrics | 22 | 20 | 0 |

There are no new failing metric keys. Shared declaration visibility increases
11,933 to 12,038: 83 declarations in the new TU, plus one in each of 18 existing
buildings and four world consumers. This exposure change is retained explicitly.
The independent raw-source graph has the same inherited macro/alias limitations
before and after; emitted preprocessed metrics remain authoritative.

Historical emitted metadata at `8e5ff4f568689fe58dd812fc61e1dfefe3682b56`
attributes both remaining Road-related excess counts to the initializer's
required world-menu call. The current API and edge sets preserve the historical
158 and 43 members and add only that helper. Removing the call would violate
cold initialization. The next bounded review is the builder-menu handler in
place; moving its whole body merely to reduce counts would add other dependency
failures. Exact historical membership and rejected options are retained in
`residual-road-audit` under the batch evidence directory.

Four public fixture modules only change their extraction paths. Existing
fixtures check the original table bytes, pointer identities, selector/bridge
results, cold normalizer/highlight/modal entry, and warm mutations. They do not
execute a direct cold bridge-predicate call or the complete world builder-menu
handler. Unchanged caller bodies are checked separately. These fixtures provide
no new menu-runtime or campaign proof. The reviewed Road-function count remains
twenty, and the mission-05 frontier does not advance.

Source, provenance, complete header deltas and validation commands are retained
under artifacts/readability/ci-road-dependency-20260913/. The `provenance-plan`
directory preserves the original candidate; `generated-surface-audit`,
`move-proof`, `metadata`, and `build-validation` keep the separate proof scopes.
Both native builds pass with 151 active objects and 148 archive members per
compiler. Archive order changes only by renaming the trimmed world member and
inserting the new buildings member at zero-based position 39. Old world objects
remain as inactive build evidence. Of 149 common object paths, 148 Clang objects
and 106 GCC objects remain byte-identical; the remaining hashes require the
separate code/data comparison rather than an assumption of binary equivalence.
Warning totals remain 6577 GCC / 6579 Clang and pass their frozen ratchets.

Independent object comparison preserves all 148 unaffected objects' runtime
contents; GCC's 42 additional hash changes affect metadata only. Both moved
functions and their 21 local read-only objects retain code/data bytes, symbols
and relocations. The additional TU contributes an equivalent unwind header and
a GCC property note identical to the existing notes; the linked property note
is unchanged. Two GCC unwind records exchange four trailing decoded no-op bytes,
without changing their PC ranges or unwind instructions. The initial raw GCC
object failure and the explicit structural proof are both retained.

The linked comparison proves the exact 21-object block movement, with every
other ordered data row unchanged. It checks 203 GCC / 204 Clang relocation
fields in each before and after binary against actual symbol and PLT targets.
All 21 local byte extents remain distinct and exact, and all 16 shared sound
references retain their aliasing. The table and guard addresses and initial
bytes are unchanged. All 140 unaffected canonical sources remain byte-identical,
including the separate inventory-only state TU.

Historical raw link totals remain 439 GCC / 691 Clang with zero crosscheck
errors. Direct before/after comparison reports only read-only data order, with
the same symbol multiset. The unchanged strict checker records
`linked_data_ordered: changed`; all other fields compare exactly. This raw
failure is retained without allowances or baseline changes. All four asset-free
CTests pass under each compiler. Preprocessing preserves the 94 affected
definitions and 17 selected declarations in both profiles.

All 526 tooling tests pass in 154.156 seconds, with all 741 inputs and both
complete native output sets unchanged. All 151 compiler commands retain their
flags; only the reviewed source/output paths change. Complete warning logs
cover all 145 canonical TUs. An initial private inventory check incorrectly
assumed unique source paths for the separately compiled instrumentation
source; the corrected output-identity check and the failed attempt are retained.

The first isolated coverage build completed, but its CTest wrapper rejected the
`artifacts/` build location before executing fixtures. The unchanged wrapper
requires a path under `build/`. That attempt is retained; the replacement uses
`build/coverage-road-ownership-20260913`. The replacement build, coverage CTest
and frozen-floor measurement pass: 6161/6652 lines (92.62%), with all 718 selected
functions present, 584 fully covered, 134 partial and none uncovered. The 89.7%
floor and zero-uncovered requirement remain unchanged. These results validate
the bounded source move; they do not establish new game-route or visual proof.

### Published CI observation after Road widget ownership

The [438272e CI run](https://github.com/lisu188/clash-disassembly/actions/runs/34749418188)
passes both compiler builds, four asset-free CTests per compiler, unit-runner
policy checks and all 526 tooling tests (158.493 seconds). Overall CI still fails
the header and both linked-symbol ratchets. The complete logs report 439 GCC /
691 Clang link differences and zero library crosscheck errors.

This run's separate coverage job measures 6163/6652 lines (92.65%) across all
718 selected functions: 585 fully covered, 133 partial and none uncovered. The
local ownership batch's 92.62% and preceding remote results remain separate
measurements. Run metadata and all four complete job logs are retained under
artifacts/readability/road-functions-20260906/batch-18-menu/build-validation/ci-observation/.

### Batch 18: WorldMap_HandleBuilderActionMenu

Track: Win95 reconstruction, reached Road builder-menu lifecycle. The handler
at `0x40A0E0` now separates rejected input from the active menu, names the six
actions and carried arguments, and uses a structured loop in place of the
decompiler label. Its signature types and source ownership remain unchanged.
The physical widget order is Road, Trap, Dig, Keep, Fortress, Castle; their
action values remain 0, 2, 1, 3, 4, 5 respectively.

The no-builder branch forwards `delayTicks` to the info window instead of
reading uninitialized `v9`. Original animation, builder-query and button-sound
callees preserve incoming ECX along this branch. The three copied text DWORDs,
unsigned language byte, seven-element local backing and one-past-third pointer
arguments remain. Trap dispatch replaces uninitialized `v7` with zero only in
the native slot consumed by discarded logging arguments. This normalization
does not claim that original ECX literally contained zero.

All three construction branches now require `Building_New` to return exactly
one, matching the original comparison. The inspected real callee returns zero
or one; noncanonical returns used to distinguish this predicate are boundary
tests, not evidence of a reached gameplay defect. Stack addresses use explicit
32-bit wrapping arithmetic, and the existing packed `UnitStackRecord` provides
the signed row and column after Keep construction. Selection and arena values
are freshly loaded at their original callback boundaries.

The menu retains friendly-selection and poll/flipping short circuits, the
special -1 action path that skips the later flipping query, fresh action reads
after callbacks, and the carried frame argument between iterations. Its guarded
builder initialization, diagnostic placement, current-primary render-device
restore, main table initialization and raw final selection-refresh return stay
in order. No public symbol, global, table, layout or legacy identity is renamed.
Only this canonical body hash changes; all 26 other definitions in its TU remain
exact. The original instruction and assembly evidence is `clash95.asm:15044`
through the handler end, including the separate six-target jump table. Both
local PE copies agree on the 640-byte function range: 637 instruction bytes
ending at `0x40A35D`, followed by three alignment bytes. The separate jump table
contains 24 bytes at `0x40A0C0`.

Private batch evidence is retained under
artifacts/readability/road-functions-20260906/batch-18-menu/:
`preparation/` contains the source/assembly contract, `original-proof/` owns
the original-byte execution evidence, `regression/` owns the actual-source
comparison and `build-validation/` owns compiler and repository checks.
The private applied-source.json records the exact source and one-record metadata change.
The first application script stopped before writing because the scanner's
required second argument was omitted; its unchanged failed version is retained.
The corrected script passes the complete neighboring-definition comparison.

Original child-gameplay behavior, callee register outputs, x87 consumption,
authentic mouse interaction and rendered menu parity remain separate gates.
This batch does not advance the mission-05 first-Road endpoint or campaign
completion count. The next runtime frontier remains normal turn refresh and
Road continuation from `(49,50)` on turn 6.

The original-byte probe executes 62 scenarios and records 743 boundary events.
Both linked menu and jump-table sections are checked against the captured PE
bytes before execution. All 62 scenarios match the actual recovered C++ body
under GCC 13 and Clang 18 at O0/O2: 248 matching scenario executions. The four
native output hashes equal the original output SHA256
`2216468bbf0719c94e7096cdc3de8810bba70dff3f6f96f2cbcf483d239edb7c`.
Native probes use strict warnings and undefined-behavior trapping, excluding
packed alignment as required by the recovered layout. They execute the real
builder and main-table initializers, check poisoned cold buffers and preserved
warm state, and verify the original physical action order and pointer fields.

A separate 16-case original-callee probe verifies preservation of entry ECX
through the unchanged animation, builder-query and button-sound instructions.
It covers delay bits 0, 20, `0x80000000`, `0xFFFFFFFF`, audio enabled/disabled,
builder and no-builder paths, descriptor sounds and pump waiting. Inner recording
stubs deliberately clobber ECX where the original saves it. This supplements the
menu's explicit preserving-callee contract; it does not recover arbitrary action
callees' register outputs or x87 behavior.

The public regression is asset-free:

```sh
python3 -m unittest discover -s tests/tools -p test_builder_menu.py -v
```

It extracts the actual body and initialization helpers, then checks each trace
and the aggregate output against the measured original hashes in
`tests/tools/fixtures/builder_menu/provenance.json`. The main table's unchanged
initializer supplies its native reference bytes, with independent callback and
sentinel checks; this establishes initialization timing and preservation, not
a new original whole-main-table data oracle. Compiler, CTest, metadata and
private probe commands are retained in the corresponding evidence directories.

Both supported native builds and all eight asset-free CTests pass. Each compiler
retains 151 active objects and the same ordered 148 archive members; 150 objects
remain byte-identical. In world002, only the reviewed function's code and its
own jump-table relocations change. Independent ownership checks place all six
native table targets inside that function; 27 neighboring executable sections,
unrelated allocated contents and 26 neighboring unwind records remain exact.
The raw whole-object comparison remains false for the intentional target change.
Its narrowed ownership proof is separate; no generic comparison rule is relaxed.

Strict before/after linked comparisons pass without allowances. Historical raw
link rows remain exactly 439 GCC / 691 Clang with zero crosscheck errors. All
14 nonratchet metadata checks pass; the complete 20 header-failure rows, limits
and emitted surface remain unchanged. Incremental world002 warning totals are
4 GCC / 5 Clang, and both warning checks pass. The changed menu is outside the
selected 718-function coverage set; its selected neighboring callback and the
coverage metadata remain unchanged, so this batch does not rerun or substitute
a new coverage percentage for the existing local and remote measurements.

The untouched parent matches all 42 defined canonical scenarios in all four
compiler profiles. Its six defined noncanonical constructor-return scenarios
retain the expected first extra minimap or sound call; they are distinct from
the 14 excluded no-builder/Trap undefined-argument and wrapping-arithmetic
cases. The first parent harness builds reject its existing mixed `&&`/`||`
warning. Those attempts remain, and the corrected before-only compile policy
downgrades that warning and the existing uninitialized warnings while retaining
the exact parent body and sanitizer. Candidate builds retain warnings as errors.
All 18 targeted negative controls compile strictly and are rejected by native
checks or measured-original trace comparison. They discriminate skipped/eager
initialization, wrong action mapping, short circuits, stale callback state,
constructor predicates, missing cleanup and incorrect raw returns.

The full tooling suite passes all 528 tests in 148.633 seconds with no skips.
All 746 production/tooling inputs and both complete native artifact sets remain
frozen through validation. The public fixture adds two test methods; no existing
gate, baseline or coverage floor changes. Markdown links and whitespace checks
pass. The first link check identified the private applied-source report as an
unresolved public path; the corrected prose reference and failed log are retained.

### Published CI observation after the builder-menu review

The [ef47584 CI run](https://github.com/lisu188/clash-disassembly/actions/runs/34750672143)
passes both compiler builds, all eight native CTests and 528 tooling tests
(175.822 seconds). Its separate coverage job measures 6163/6652 lines (92.65%)
across all 718 selected functions: 585 fully covered, 133 partial, none uncovered.
Header and linked-symbol ratchets still fail; raw link rows remain 439 GCC /
691 Clang with zero library crosscheck errors. These remote measurements remain
separate from the preceding local batch, which did not rerun coverage.

Complete logs are retained under
artifacts/readability/road-functions-20260906/batch-19-selection/build-validation/ci-observation/.
The first GCC log fetch encountered an invalid local ZIP cache; the complete log
was retrieved through the job-log API. No CI job was restarted.

### Batch 19: WorldMap_SyncSelectionForHumanPlayer

Track: Win95 reconstruction, selection cleanup reached from the Road builder
menu. The function at `0x40A490` now names its entry context and arena snapshot,
returns early for a nonhuman controller, and uses the existing packed
`PlayerRuntimeState.controller_mode` and first `UnitSlotRecord.unit_type_id`.
The named clearing decision replaces the combined raw-offset expression.
Original 32-bit player and stack address arithmetic is explicit.

Every nonzero controller DWORD still takes the human path; this is not a
byte-sized flag test. Selection `-1` skips the unit-record read. Otherwise only
the first signed unit-type WORD equal to `-1` clears the selection. Other negative
types and later unit slots do not change this predicate. Clearing precedes the
action-bar refresh, and synchronization runs once for each human path. The
function retains its void return and opaque context argument.

The entry arena is intentionally retained across refresh. Original ECX is
loaded before the controller check and preserved on the refresh helper's
guaranteed no-selection branch. That branch saves ECX around cursor work, and
both widget-refresh wrappers save it across their indirect callbacks. A callback
can change global arena, player and selection state without changing the arena
argument forwarded to the final helper. The helper can still inspect those
live globals itself. This conclusion does not cover arbitrary selected-stack
calls to the refresh helper's different branch.

Evidence: `clash95.asm:15408`–15443 for the caller, 15282–15328 for the action
bar, 40260–40274 for the widget wrapper, and the existing packed layout/offset
assertions. Source, captured originals and bounded proof artifacts are retained
under artifacts/readability/road-functions-20260906/batch-19-selection/.
The source edit changes only this function, its stale annotations and its
canonical body hash. All 26 other definitions in world002, public signatures,
identities, layouts and source ownership remain. No gameplay, rendering or
campaign milestone is promoted.

The unchanged original caller records 28 callback events across 22 scenarios.
Its 102 instruction bytes end at `0x40A4F6`; the manifest range retains ten
following alignment bytes. Both local PE copies agree, and the embedded section
is verified before execution. The fixture keeps signed-arithmetic exclusions
separate from the parent's defined pointer-sign-extension difference: converting
a negative integer to an opaque native pointer is not itself signed overflow.

All 22 original traces match the extracted actual C++ body under GCC 13 and
Clang 18 at both `-O0` and `-O2`, with strict warnings and undefined-behavior
sanitization. The untouched parent matches the 18 defined equivalent scenarios
in all four profiles. Its separate negative-base case retains the expected
opaque-pointer sign extension; the three wrapping-index cases are excluded from
parent execution because its signed stride arithmetic overflows. These bounded
address cases establish original 32-bit semantics, not a reached gameplay bug.

A separate eight-case probe executes the actual original no-selection refresh
and widget wrapper. Their 151 and 18 instruction bytes and original widget-table
callback addresses are independently verified. Recording cursor and draw
callbacks deliberately overwrite ECX and change global arena state. The entry
arena and context survive every case, including both, neither or just one draw
callback passing the signed coordinate gate. This substantiates the snapshot
without assuming that the indirect draw callback preserves ECX.

Nine compiled negative controls are rejected. They distinguish an incorrect
live arena reload, controller/first-unit access widths, the wrong unit slot,
late selection clearing, lost context, an eager nonhuman stack read and signed
stride overflow. Guard pages make the specific rejected nonhuman read fail
deterministically. The measured caller has two semantic callback boundaries;
real child selection gameplay remains outside this fixture.

Both native builds pass. Only the reviewed function's executable section and
its instruction relocations change in world002; ordinary allocated data and
27 neighboring code sections remain exact. All 150 other objects are
byte-identical and the ordered 148 archive members remain. The ordinary object
comparison passes without the preceding menu batch's jump-table exception.
Strict linked comparisons pass without allowances. Historical raw link rows
remain 439 GCC / 691 Clang with zero crosscheck errors; all 14 nonratchet metadata
checks pass and the complete 20 header-failure rows remain unchanged.

All eight asset-free CTests pass. Incremental world002 warning counts remain
4 GCC / 5 Clang, and both warning gates pass. The reviewed function is outside
the selected 718-function coverage set; the selected neighboring callback,
coverage metadata and unit fixtures remain unchanged. No new coverage run or
percentage is claimed for this batch. The published ef47584 measurement above
remains separate.

The private validation preparation first rejected an expected source-proof key
that belonged to an earlier batch. The retained corrected driver consumes this
batch's exact 26-neighbor proof; the rejection occurred before either build.
No production repair, baseline update or gate exception was needed.

The public regression is asset-free:

```sh
python3 -B tests/tools/test_human_selection.py
```

Both test methods pass, executing the actual function under all four compiler
profiles. The fixture README and measured trace bindings are in
`tests/tools/fixtures/human_selection/`. Its readable Python contract has the
same syntax tree, 22 case records and packed input bytes as the retained private
measurement contract. Provenance binds both files separately; no expected
trace was regenerated from the candidate. The private original, regression and
build-validation directories retain exact commands and raw results.

Confidence is high within the stated caller and backed-address domains.
Public names and structure layouts remain unchanged; no uncertain field or
child-callee semantics are promoted by this review.

The full tooling suite passes all 530 tests in 240.450 seconds. All 750
production/tooling inputs and both complete native artifact sets remain
unchanged through that run. The four new public fixture/test files add two
test methods; existing checks, baselines and coverage policy remain. The
coordinating review verifies 203 original/regression evidence bindings, and
the Markdown link/path check passes.

### Published CI observation after human-player selection cleanup

The [5f3da7b CI run](https://github.com/lisu188/clash-disassembly/actions/runs/34751914714)
passes both builds, all eight native CTests and 530 tooling tests (174.539
seconds). Its separate coverage job measures 6163/6652 lines (92.65%) across
718 selected functions: 585 fully covered, 133 partial, none uncovered. Warning
gates pass. Only the inherited header and linked-symbol steps fail; raw link
differences remain 439 GCC / 691 Clang with zero library crosscheck errors.

Complete terminal metadata and job logs are retained under
artifacts/readability/road-functions-20260906/batch-20-selection-sync/build-validation/ci-observation/.
All logs were retrieved through the direct job APIs without a retrieval failure
or job restart. These remote results are separate from the preceding local
batch, which did not rerun coverage.

### Batch 20: UnitStackSelection_SyncForCurrentSelection

Track: Win95 reconstruction, selection synchronization reached from the Road
builder menu. The function at `0x40A500` now names its entry receiver, context,
query addresses and counts. Early returns replace the shared decompiler label.
It retains all three original Count calls, their signed comparisons, fresh
global reads at the later queries and the equality gate before the third call.
There is no new equality check after that call. Addresses use explicit original
32-bit arithmetic before widening to the native Count argument.

The two End paths have different original arguments. Missing selection forwards
entry ECX. A first count of exactly one with an active selection forwards the
stack-table base loaded before that count, `gameData + 147174` modulo 32 bits.
The old C++ shared the entry pointer between both calls. The refactor retains
the first table base across Count and forwards it only on the singleton path.
This is a defined argument-recovery correction. The reached original End,
highlight-clear helper and memset wrapper do not consume this receiver, so no
highlight or gameplay-state defect is claimed from the old argument difference.

The original Count leaf preserves ECX and EDX, scans up to ten signed unit-type
WORDs at 31-byte strides, and stops only at exact `-1`. It returns 0 through 10
without calling children or reading globals. A recorded Count boundary that
mutates caller globals or returns a negative value therefore tests the caller's
instruction contract beyond the real leaf's behavior. Those cases remain
separate from real-callee corroboration.

Evidence: `clash95.asm:15450`–15546 for the caller, 53539–53561 for Count,
55047–55060 for End, and 38800–38812 for highlight clearing. The map identifies
Count at `0x422B80` and the collapsed memset wrapper at `0x473FD8`. The caller's
old assembly label remains in the retained evidence; the current manifest
provides its canonical identity. Source, preparation and bounded proof artifacts
are retained under artifacts/readability/road-functions-20260906/batch-20-selection-sync/.

Only this function, three stale annotations and its canonical body hash change.
All 26 neighboring definitions, public signature types, layouts, identities and
source ownership remain. No field or global rename is inferred, and no runtime,
visual-fidelity or campaign milestone advances.

The unchanged original caller records 74 events across 28 bounded scenarios.
Its 247 instruction bytes end at `0x40A5F7`; nine following alignment bytes
remain in the verified section. Both local PE copies and the embedded linked
section agree byte-for-byte before execution. The fixture observes four
boundaries: Count, End, Begin and Refresh. Event records retain arguments,
scripted Count return and live state; the void caller has no fabricated integer
return field.

Both supported native builds pass. Only the target's code and instruction
relocations change in world002; 27 neighboring executable sections and ordinary
allocated data remain exact. All 150 other objects are byte-identical, and the
ordered 148 archive members remain. The ordinary object comparison and strict
before/after linked comparisons pass without exceptions or allowances. Complete
historical raw link rows remain 439 GCC / 691 Clang with zero crosscheck errors.
Incremental warnings remain 4 GCC / 5 Clang, with both warning gates passing.

All eight asset-free CTests and 14 nonratchet metadata checks pass. The complete
20 inherited header-failure rows remain unchanged. The target is outside the
selected 718-function coverage set. Before the September 19 upstream integration,
its selected neighboring callback, selected manifest rows and unit fixtures
were unchanged, so that initial validation did not rebuild coverage or claim
a new local percentage.

All 28 measured original traces match the actual extracted C++ body under
GCC 13 and Clang 18 at both `-O0` and `-O2`, with strict warnings and UBSan.
The unchanged parent matches 20 cases in every profile. Four defined singleton
cases differ in exactly one End argument word, with all other trace words
unchanged. A separate defined Count-pointer conversion case exposes sign
extension when an old signed address widens to native `intptr_t`; that high
pointer is only observed at the recording boundary. The three excluded parent
cases overflow signed stride multiplication at the first, second and third
query respectively. Defined pointer/argument differences are not classified
as arithmetic undefined behavior or presented as reached gameplay failures.

The separate real-Count supplement executes eight direct leaf cases and two
actual caller/singleton paths. Slot counts 0, 1, 2 and 10, the exact signed-WORD
sentinel and preserved ECX/EDX/context are observed, with unchanged arena bytes.
Both caller paths forward the saved table base to End. The reached End/highlight
receiver analysis remains a static proof; no new rendering experiment is implied.

Ten strictly compiled negative controls are rejected by an explicit boundary
assertion or measured trace mismatch. They discriminate cached counts and query
addresses, the wrong singleton receiver, a receiver recomputed after mutation,
unsigned count comparisons, an eager third query, a late equality recheck and
changed context. Compiler failures or process signals are not accepted as proof
that a control was caught.

On September 19 the worktree fast-forwarded from `5f3da7b` to `02c00bf`, preserving
this function and its manifest record. Upstream added an action-point contract
fixture and temporarily changed remote header/link steps to update diagnostic
baselines. The inherited workflow remains outside this refactor's diff. The
saved September 13 measurements remain unchanged and are bound to their original
source state; resumed checks verify that the candidate and retained artifacts
still match. The new unit fixture requires a fresh coverage measurement.
Remote CI green under the inherited diagnostic workflow does not establish
that the existing check-mode header/link differences have been repaired.

The first resumed coverage build rejected the new action-point fixture because
it writes to the immutable unit-type metadata table. The bounded test repair
reads the existing base AP and derives the full, three-quarter and half-AP
expectations from that value. Both writes are removed; fatigue thresholds,
invalid-type assertions and production behavior remain unchanged. The failed
build is retained under the batch's build-validation/resume-20260919/coverage/
directory. A later retry and full tooling run were stopped cleanly for the
user-authorized Ubuntu restart; their partial logs remain separate from any
completed validation result.

Ubuntu restarted successfully after the three coordinated tasks stopped their
active jobs. A fresh temporary write/read/unlink probe passed. The resumed
coverage build and canonical CTest complete; coverage measures 6161/6652 lines
(92.62%) across all 718 selected functions, none uncovered. The native runner
reports 1089 passes, no assertion failures and 527 isolated crashes among 1616
registered cases. Its successful wrapper exit is not an all-cases-pass claim.
The retained prior summary is 1087 passes, no assertion failures and 527
isolated crashes among 1614 cases. A separate strict filter executes exactly
the two new AP tests: both pass, with no failures or crashes. The initial
evidence parser expected per-case pass lines that this runner does not print;
a first focused retry also lacked its private coverage-shard parent directory.
Those postprocessing/setup failures remain recorded, and the corrected focused
invocation uses existing private directories without repeating the full suite.
All 527 crash identities match the retained baseline, and the complete coverage
report is byte-identical to the preceding local report.
The full tooling suite passes all 532 tests in 240.053 seconds, with all 755
production/tooling inputs and both native artifact sets unchanged. The
coordinating review verifies 274 original/regression artifact bindings.
The exact commands, coverage shards and interrupted attempts remain under
artifacts/readability/road-functions-20260906/batch-20-selection-sync/build-validation/resume-20260919/.

### Batch 20 integration with class main

The local merge `26c86a9` integrates the selection checkpoint `cdc6d07` with
published main `dd9bd1a`. Its production class reference is the immutable
`33a5959` snapshot; the later main commit adds documentation only. The combined
manifest retains 147 canonical TUs and all 4,157 identities, with exactly this
selection function's canonical body hash different from the class reference.
The shared AP fixture already equals main. No public symbol, layout, state
owner, neighboring function or additional gameplay behavior changes.

Both fresh GCC 13 and Clang 18 builds pass, each with 153 objects and 150 archive
members in unchanged order. Both warning gates pass with 6,569 recovered
warnings each. Strict linked-surface comparisons against the class reference
pass without allowances. Eight asset-free CTests and all 542 tooling tests pass;
the tooling run takes 398.998 seconds. Manifest, generated-header and TU-include
checks pass. All 807 production/tooling inputs and four workflow files remain
unchanged through validation; the coordinating review independently hashes all
807 inputs again.

Public baseline gates remain failed. The header report has 23 ratchet rows and
one include-policy error for the `DWORD a2` parameter in `UnitStack.hpp`.
The unchanged scanner treats that token as the recovered global `a2`; the
complete error lists reproduce against the frozen class source, with no
shared-state errors. Both the full raw link profiles and their difference rows
match the class reference: 453 GCC / 705 Clang, with zero archive crosscheck
errors. No baseline is reseeded and no policy is relaxed. The earlier 20-header
and 439/691-link measurements above belong to the pre-class checkpoint.

Coverage is explicitly reused from the sealed class default-worker shards.
All 718 selected implementations and their policy, fixture, runner and compiler
inputs are unchanged. The changed synchronization function has zero calls and
executed lines in every retained worker observation: 16 GCC and 16 Clang.
The selected neighbor retains its source location and reproduces 2/2 covered
lines with both pinned readers. Historical GCC coverage remains 6165/6656
lines (92.62%), no selected function uncovered, gate passing. Historical Clang
remains 6812/7345 (92.74%), eight functions uncovered, gate failing. This is a
bounded reuse proof, not a fresh coverage percentage or full native-suite run
for the merged tree. The historical native outcomes remain 1092 passes, zero
assertion failures and 524 crashes for GCC; 1092 passes, one assertion failure
and 523 crashes for Clang, out of 1616 cases each. Strict native outcomes are
carried as historical evidence only.

Commands, logs, exact input and output hashes, coverage attribution and the final
freeze are retained under
artifacts/readability/road-functions-20260906/batch-20-selection-sync/integration-validation/.
Its published-reference directory contains immutable compiler binaries,
archives, compile commands, manifest and input inventories for the next
integration. The initial preparation assertion, snapshot/report filename
collisions and stronger private empty-policy expectation remain in their failed
attempt directories; reporting recovery did not repeat the successful native
builds or CTests. Final documentation updates are recorded separately from the
validated production commit. Confidence is high for the bounded assembly-backed
refactor and measured integration comparisons. No new runtime, visual or
campaign milestone is claimed.

### Published CI after batch 20 integration

[CI run 35439348039](https://github.com/lisu188/clash-disassembly/actions/runs/35439348039)
completed for published main `a0dc2f0`. Both supported builds and warning gates,
all eight asset-free CTests, both runner-policy test sets and all 542 tooling
tests pass. The remote tooling suite takes 257.851 seconds. Fresh GCC coverage
measures 6167/6656 lines (92.65%) across all 718 selected functions, none
uncovered. This is a new CI measurement for the published selection/class merge;
it is separate from the local historical coverage reuse recorded above and does
not measure the next selected-slot refactor.

The overall run fails on the retained header and raw-link checks, plus two
Markdown references to private class evidence absent from the checkout. The
header output retains the `UnitStack.hpp` `a2` finding; raw link counts are
453 GCC / 705 Clang with zero archive crosscheck errors. The missing references
are the class native-baseline README and origin-refresh validation script,
also reproduced by the preceding local check in unchanged documents. The
successful native CTest wrapper is not an assertion that every isolated native
case passes. All four terminal job logs and run metadata are retained under
artifacts/readability/road-functions-20260906/batch-20-selection-sync/published-ci-a0dc2f0/.
No job was restarted.

### Batch 21: UnitStackSelection_HasSelectedSlots

Track: Win95 reconstruction, Road-family selection helpers. The predicate at
`0x423AC0` now uses an early inactive-selection return and a direct loop over
the existing ten-DWORD flag array. The byte-offset loop, pointer casts and one
stale guessed-type annotation are removed. Only active index `-1` returns
before the scan; every other index still scans flags in order. Any nonzero full
DWORD returns exactly one, all-zero flags return zero, and index ten is never
read. The public signature, globals and existing slot-count constant remain.

The original instruction sequence at `clash95.asm:54982` through line 55011,
the shared-state declarations and the existing ten-slot layout assertion agree
with the rewritten body. Independent review finds the applied body identical
to the reviewed candidate. All 34 neighboring definitions are byte-identical,
and the manifest changes only this canonical body hash. Confidence is high for
this bounded predicate; there are no unresolved semantic candidates here.

The manifest, generated-header and TU-include checks pass. Header metrics and
all 23 ratchet rows equal the published `a0dc2f0` reference; the separate
include-policy gate has not been rerun. After a coordinated disk reserve hold,
both incremental native builds and warning gates pass. Each compiler changes
exactly one object, preserves the other 152 and retains identical compile
commands. The warning comparison for the changed source file retains 13 GCC /
25 Clang diagnostics, with no new messages against its retained full-build log.
Both strict surface comparisons pass without
allowances, and all eight existing CTests pass. Complete raw profiles and their
453 GCC / 705 Clang failure rows remain exact. Archive membership (150 names)
and order are unchanged. Public raw-link gates remain failed; no baseline changes.

All 807 inputs remain stable through validation, and the immutable batch-20
reference is reverified unchanged. No full tooling or coverage run is repeated
for this source-only edit. The final validation freeze is under the batch's
validation directory. This is a validated task-branch checkpoint against
`a0dc2f0`; main integration with the neighboring task remains separate.

No test or oracle is added for this direct, behavior-preserving scan. The
function is outside the 718 selected coverage implementations. Its five selected
neighbors retain their bodies; the two following Road exit functions move nine
source lines earlier. No new coverage percentage or indirect non-execution
claim is made. Private review and exact command receipts are retained under
artifacts/readability/road-functions-20260906/batch-21-selected-slots/.
No runtime, visual or campaign milestone advances.

The neighboring Begin, End, ClearMask and Refresh helpers were also reviewed
against the original and retained unchanged. Their existing call ordering,
diagnostic placement and return contracts are already clear. In particular,
ClearMask returns the cleared-array pointer's low 32-bit integer result,
whereas Begin, End and Refresh return the viewport redraw result. Refresh
must not gain Begin's flag clear or mode writes. The bounded review is retained
under artifacts/readability/road-functions-20260906/selection-family-next-review/.

### Batch 21 integration with rules-engine main

On 2026-09-24, `8b8ccbe` integrates incoming main `35f3adb` with the selected-slot
predicate checkpoint. The incoming changes since the immutable F7 reference
are confined to rules-engine tooling, tests, CI and documentation; production
source, layouts, native fixtures and build definitions are unchanged. Original
assembly and a second source review still confirm the exact `-1` guard, ten
full-DWORD reads and 0/1 return. The production diff remains one function and
one current manifest hash, with all 34 neighboring definitions unchanged.

Fresh Debug builds with GCC 13 and Clang 18, both warning gates, strict surface
comparisons without allowances and all eight existing public CTests pass.
All 836 tracked nondocumentation inputs remain stable. Each build retains 153
objects. Complete raw executable profiles equal the immutable F7 reference;
the public link gates still fail with the same 453 GCC / 705 Clang rows and
zero library crosscheck errors. Header profiles equal exact incoming main:
23 ratchet rows, one `UnitStack.hpp` parameter-name policy finding, and no
visibility errors. No baseline, policy or allowed-difference list changes.

The current tooling suite runs 548 tests, reflecting six incoming strategic
test methods absent from the historical 542-test suite. Its first local run
finishes with five failures and four errors: three are the inherited workflow
condition subtests; the remainder affect five distinct methods because the
temporary directory was on the Windows-backed filesystem inside the source
root, or because existing time limits expired. All five methods pass when
rerun with a private Linux-native temporary directory, including both affected
Clang radix profiles. The original failed run is retained, not relabeled as
a passing full-suite run. All 273 tracked tooling/test files and the route/CI
inputs in the retry binding match incoming main byte for byte.

Source audit, frozen metadata, save contract, generated constants/structures/
unit metadata, generated headers and TU include checks pass. Four new strategic
gates pass: deffacts, matcher coverage, RETE path depth and reset agenda. The
activation-witness gate still fails at `ustaw_pa_object_match`, with no actual
activation where `ustaw_PA_0` is expected. The three workflow subtest failures
are the RETE, reset-agenda and activation-witness steps' CLIPS prerequisites
missing from the test's expected condition. Both these failures and the two
private Markdown-path failures reproduce incoming main.

[Incoming-main CI](https://github.com/lisu188/clash-disassembly/actions/runs/35779937637)
and [PR CI at the compiled head](https://github.com/lisu188/clash-disassembly/actions/runs/35963432266)
finish with the same failed steps. Each remote tooling run has exactly the
three workflow failures, and each separate split-unit coverage job succeeds.
These remote results do not establish fresh local coverage. No test is added
for the direct predicate loop, and no runtime, visual or campaign milestone
advances.

Exact commands, initial failed attempts, focused retries, full logs and input
bindings are retained under
artifacts/readability/road-functions-20260906/batch-21-selected-slots/integration-20260924/.
Its immutable native reference includes all raw objects, binaries, archives,
actual compiler/link recipes and source-input bytes; later documentation and
publication are bound separately to the compiled head. This integration
supersedes the preceding checkpoint's pending-main status without replacing
its historical measurements.

### Batch 22: UI_LoadCurrentPlayerInfoSpriteSet

Track: Win95 reconstruction, Road-family selection-panel prerequisites. The
loader at `0x423370` now names its filename, allocation address, sprite-set
pointer and retained logging inputs. It removes ghost copies and an
uninitialized allocator argument, while keeping the public types, 24-byte
filename buffer, 4112-byte allocation and existing outer-block free policy.
The original free, clear, format, allocate, conditional load, publish and return
order remains intact. The actual loader return value is still published and
returned; no destructor, retry or fallback is introduced.

Original `UI_SetCurrentPlayer` instructions at `clash95.asm:54311` through
54361 and the current allocator/loader implementations support the change.
Entry ECX is saved and overwritten; it is distinct from the allocator-call
register. Zero is used because the current `Mem_Alloc` discards that argument,
not because original ECX was proven zero. Unsigned 32-bit addition recovers the
original wrapping increment before signed filename formatting. Decoding the
allocation bits before widening and explicitly publishing the returned
pointer's low 32 bits remove implicit address conversions. These are bounded
arithmetic/address repairs, not claims that the old C++ had defined behavior
at every boundary. Ordinary current allocations remain in the signed-safe
low32 domain.

Independent review confirms the applied definition equals the reviewed
candidate. All 34 neighboring definitions and the public declaration remain
unchanged; only the selected current manifest hash changes. Confidence is high
for these source contracts. The original CRT's complete failure behavior and
nested allocation cleanup remain unproven. Two panel callers still evaluate
uninitialized context locals; those caller defects require the separate panel
repair. The neighboring free helper's empty-path return is also deferred.

The actual-source regression passes ten cases with GCC 13 and Clang 18 at O0
and O2: 40 executions with warnings as errors and undefined-behavior checking.
It observes helper order and global state, filename boundaries, allocation
size, conditional loading, forwarded logging arguments, returned pointer and
low32 publication. The old body is rejected for its uninitialized local under
all four compiler profiles. Five compiled mutations fail for the intended
reasons. Synthetic addresses are never dereferenced; wide synthetic return
values test truncation outside the production allocator's domain. This is
source/helper contract evidence, not original-executable or rendering proof.

The first fresh GCC production build stops with `Cannot allocate memory` while
compiling unchanged `src/units/UnitSlot.cpp`; there is no C++ diagnostic
identifying the loader as the failure. The failed log and completed objects
are retained.
The local retry is held while the coordinated compiler batch releases capacity;
the Clang production build and final native gates have not run. Production
validation and main integration remain pending for this draft checkpoint.
Exact commands, source bindings, failed old-source builds and mutation
diagnostics are retained under
artifacts/readability/road-functions-20260906/batch-22-player-info-loader/.
No runtime, visual or campaign milestone advances.

## Next migration batches

The bounded `DLXSprite_LoadCachedEntry` view migration is recorded in
[DLX_CACHED_ENTRY_RECOVERY.md](DLX_CACHED_ENTRY_RECOVERY.md), including the
actual-source fixture, retained compatibility differences and validation.

1. Continue through the remaining `src/units/` functions that manually step `UnitSlotRecord` at 31-byte intervals.
2. Replace remaining raw position/owner/facing accesses across `world/`, `buildings/` and `strategic/` with the canonical `UnitStackRecord` view.
3. Extend the same approach to the existing typed `PlayerRuntimeState` and building overlays.
4. Convert gameplay APIs to typed pointers only after all cross-subsystem call sites are understood.
5. Replace second-generation mechanical function names and decompiler locals after the underlying state model is stable.
