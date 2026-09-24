# Game-system class migration

Track: Win95 reconstruction. Frontier: UnitStack AP-spending extraction.
Thirty-one identities have canonical methods: 28 in six class-named sources
and three AP operations in their original TU pending relocation.
The ordered manifest contains 147 translation units,
including the independently recovered Road ownership change from main.
This migration is in progress. The completed GNU++20 language
cutover is documented separately in [CPP_MIGRATION.md](CPP_MIGRATION.md).

The initial reference is `6f7537268e784c538133b714e3ccb77cf54052e4`; the
[2026-09-08 origin refresh](CPP_CLASS_ORIGIN_REFRESH.md) records the newer
integration reference and separate comparisons. Original packed
records, globals, low32 handles, callback tables, save bytes and explicit
lifecycles remain authoritative. Classes describe the reconstruction's
organization, not proven original C++ object layouts. The migration does not
advance campaign or visual-fidelity claims.

The three AP-spending operations pass eight actual-source profiles, both
production builds, strict surface comparisons and eight asset-free gates.
Distinct algorithms and callback contexts remain; the original adapters and
direct methods match the frozen repaired functions and original measurements.
See [UNIT_STACK_AP_CLASSES.md](UNIT_STACK_AP_CLASSES.md).

The plague setter extraction passes eight actual-source compiler profiles,
both production builds, strict surface comparisons and eight asset-free gates.
Its original adapter and direct method match the frozen repaired implementation
and original measurements. The separately validated relocation preserves the
body hash and passes the same gates. See [UNIT_STACK_PLAGUE_CLASS.md](UNIT_STACK_PLAGUE_CLASS.md).

The three personage/order queries pass eight actual-source compiler profiles,
both production builds, strict surface comparisons and eight asset-free gates.
Their direct method dependency and original adapters are validated separately.
The subsequent unchanged-body relocation passes the same gates.
See [UNIT_STACK_PERSONAGE_CLASSES.md](UNIT_STACK_PERSONAGE_CLASSES.md).

The explicit initializer passes its actual-source differential fixture, both
production builds, strict surface comparisons and eight asset-free gates.
Construction remains binding-only; initialization is an explicit method call.
See [UNIT_SLOT_INITIALIZER_CLASS.md](UNIT_SLOT_INITIALIZER_CLASS.md).

The four UnitSlot predicates/order methods pass exhaustive actual-source tests,
both production builds, strict storage/initialization/symbol comparisons and
eight asset-free gates. The initial source-order failure and unchanged-body
placement correction remain recorded in [UNIT_SLOT_CLASS_MIGRATION.md](UNIT_SLOT_CLASS_MIGRATION.md).

The two separately repaired UnitStack strength/cargo methods pass both focused
comparisons in eight compiler profiles, both production builds, strict surface
checks and eight asset-free gates. See [UNIT_STACK_REGISTER_CLASSES.md](UNIT_STACK_REGISTER_CLASSES.md).

The two GameRandom methods and the direct UnitTurn caller pass focused
before/after comparisons, both production builds, exact symbol/storage and
initialization checks, and all eight asset-free gates. The RNG behavioral repairs
were committed separately before extraction; relocation passes the same gates.
See
[GAME_RANDOM_CLASSES.md](GAME_RANDOM_CLASSES.md) for evidence and limits.

## Inventory and implementation rules

`data/game_class_registry.json` assigns all 4,157 recovered identities:
1,849 intended game methods across 116 classes, 22 retained utilities/boundaries
and 2,286 excluded library implementations. Each procedural disposition has a
rationale. Six declaration-database helpers are tracked separately without
invented addresses. The five rendering helpers historically filed under `clips`
are game functions; CLIPS implementations filed under `media` remain procedural.
Assignment is architectural intent, not proof that a family has migrated.

The separate support registry now assigns 459 exact definitions outside this
historical registry: 456 translation-unit bodies and three header bodies, with
154 planned runtime methods and 305 retained utilities/boundaries. The latter
include 39 explicitly retained diagnostic utilities. Each entry records current
and immutable-origin body/signature hashes, ownership, rationale and constraints;
the source audit rejects missing or unclassified definitions in its six-file
scope. The 4,157-identity inventory alone cannot establish completion of the
entire requested scope.
See [CPP_CLASS_PLATFORM_INVENTORY.md](CPP_CLASS_PLATFORM_INVENTORY.md).

Schema 3 of `data/recovered_sources.json` retains historical identities,
addresses, linkage and hashes. The canonical body has its own qualified name,
source and hash; an ABI adapter has a separate source and hash. The shared
definition resolver distinguishes the two and rejects duplicate or missing
definitions. Namespace-qualified, non-overloaded, non-template out-of-line
methods retain their original leaf names. Source, header, coverage, declaration,
literal and global tooling use the same definition resolver.

`src/sources.cmake` is checked against the manifest's implementation, adapter and
state-source inventory. Existing source order is a storage contract: append new
class sources without sorting old anchors. C++ headers are separately audited
through their include closure. They cannot hide recovered behavior, canonical
dependencies or foreign state behind inline helpers or macros.

Record constructors only bind borrowed bytes. Services must bind live state
without caching a `gameData` value across load/reallocation. Explicit original
construct/destroy/reset routines remain operations; destructors perform no game
actions. Original callbacks remain free functions with their original ABI. No
native virtual layout, exceptions, RTTI or serialization replacement is added.

## Pilot

Four canonical bodies now belong to `clash95::UnitStack` and
`clash95::QueuedPath`:

- `UnitStack_GetMinCurrentActionPoints`
- `UnitStack_HasReadyUnits`
- `UnitStack_HasBuilder`
- `QueuedPath_StartsAtTile`

Their original functions remain at their original translation-unit anchors and
bind the proven receiver before calling the method. The builder adapter resolves
the current stack address on every call. The algorithms retain slot-0 AP
initialization, sentinel handling, the first-waypoint query and original widths.
The class files are `src/units/UnitStack.cpp` and `src/units/QueuedPath.cpp`; the
manifest-backed source inventory currently contains 142 translation units.

Extraction was validated before relocation. The production-source differential
test compiles frozen reference bodies, actual current canonical methods and ABI
adapters on GCC 13 and Clang 18 at `-O0` and `-O2`. Each profile checks 6,176 stack
and 38,928 path cases, including 16 byte alignments, sentinel holes, byte extremes,
negative/large path counts, complete records and surrounding guard bytes. All
four profiles pass both before and after source relocation.
The final pilot uses alignment-one alias views for its packed 16/32-bit loads.
All four differential profiles pass with alignment trapping enabled on methods
and adapters. Every runtime-allocated ELF section matches the route-tested
binary exactly (25 GCC sections, 24 Clang sections; only diagnostic build IDs
are excluded), including executable bytes, data, addresses and initialization.

Both extracted production builds preserve all legacy archive identities, named
storage, relative data order and initialization profiles. Only explicitly
reviewed method and borrowing-constructor text additions are permitted by
`data/class_migration_text_additions.json`. Historical ratchets are unchanged.

The first relocated GCC comparison correctly rejected a source-list reorder
that moved two pre-existing local statics. Original source order has been
restored; fresh GCC and Clang builds now pass both migration surface comparisons
and all eight asset-free gates. The manifest now pins the exact ordered inventory
so future source synchronization rejects that reorder before compiling.

## Evidence and current limits

The next extraction completes `QueuedPath` with
`QueuedPath_StartsInBuildingFootprint`. After its independent extraction gate,
the unchanged body was relocated into
[QueuedPath.cpp](../src/units/QueuedPath.cpp). The object borrows a live
`gameData` reference as well as the path bytes; holding an object across state
rebinding observes the new building table. The original 1x1/2x2 footprint
branches, byte comparisons and early-return order remain intact.

The actual canonical method and adapter match a hashed frozen reference on
26,880 cases per GCC 13 / Clang 18 optimization profile. Checks cover all 16
alignments, guarded full state images, signed indices, coordinate extremes,
path-count/high-bit cases and every state rebinding. Alignment traps are enabled.
Both production builds, exact migration surface comparisons and all eight
asset-free gates pass before relocation. The only newly reviewed text changes
are the second query and its two-argument borrowing constructor. Evidence is in
`pilot/*queued-path-extraction*`; the expanded tooling run passes 244 tests.
This fifth identity is outside the unchanged 718-function coverage set.
The relocation repeat passes the same differential, both production builds,
both exact surface comparisons and all eight asset-free gates. It adds no
translation unit; the ordered inventory remains 142. `QueuedPath` is the first
fully extracted and relocated class (2/2 assigned identities); the three
`UnitStack` queries remain a partial family.

A fresh five-method native matrix now passes both compiler builds. Clang's
1,059 passes, one existing assertion failure and 529 crashes match the frozen
baseline exactly. GCC records 1,060 passes, zero assertions and 529 crashes;
the unchanged excluded `cov23_strtoulongradix.hex_digit_expect_crash` happens
to pass in this run, with no new crash identities. This is not a claimed
behavioral recovery. GCC coverage is 6,170/6,663 (92.60%); only the covered
`QueuedPath_StartsAtTile` receiver-binding line differs from the frozen line
counts. All 718 identities have coverage. Exact commands, failed initial
build-directory/CLI attempts, source hashes and full native outcomes are in
`queued-path-native/`. The full tooling suite now passes 245 tests.
The unchanged raw link ratchets remain red at 432 GCC / 684 Clang differences:
each is its historical 427/679 plus exactly the five reviewed canonical method
symbols. The private pilot/queued-path-raw-link-delta.json enumerates those
additions.
The stronger migration comparison passes with explicit method/constructor
allowances and no storage, initialization, legacy identity or order changes.
The header ratchet still has exactly 14 historical differences.

Borrowing factories are now audited separately from recovered identities.
The registry records their source, ordered canonical globals and body hash;
catalog and source audits reject duplicates, unregistered qualified methods,
relocated storage anchors, stale hashes and factories that do more than bind
the recorded references. Factories never count toward recovered coverage.

The remaining stack family has four assembly-confirmed recovery blockers;
see [CPP_CLASS_MIGRATION_BLOCKERS.md](CPP_CLASS_MIGRATION_BLOCKERS.md).
Those repairs must remain separate from architectural extraction.

Private evidence lives under `artifacts/cpp-classes/20260906/` (not present in
clean checkouts). Frozen baseline inputs and hashes, both compiler builds,
per-gate outputs, complete native outcomes and failed attempts are retained.

| Gate | Frozen reference | Extracted pilot |
| --- | --- | --- |
| GCC 13 / Clang 18 production build | Both pass | Both pass |
| Four asset-free gates per compiler | 8/8 pass | 8/8 pass after relocation |
| Historical identities | 4,157 retained | 4,157 retained |
| GCC native cases | 1,059 pass / 0 assert fail / 530 crash | Identical outcomes and crash identities |
| GCC coverage | 6,169/6,662 (92.60%) | 6,168/6,663 (92.57%) |
| Clang native cases | 1,059 pass / 1 assert fail / 529 crash | Pending |
| Historical raw link ratchet | GCC 427 / Clang 679 differences | Remains reported separately |
| Historical header ratchet | 14 differences | No baseline increase authorized |

Coverage retains the exact 718-function set, the 89.7% floor and zero-uncovered
requirement. The pilot adds one covered receiver-binding executable line in
`QueuedPath_StartsAtTile`; the unchanged `Building_UpdatePlagueState` accounts
for two previously variable uncovered lines in this run. A required identity
with zero executable lines is now an error. The baseline Clang assertion is
`cov5_01_getallowedattrtoken.allowed_symbols` (returns -1, expected 2), not a
class-migration regression. Native wrappers tolerate isolated crashes; their
success is not crash-free acceptance.

Both relocated compiler profiles pass the first-Road and ordinary-water rejection
probes. First Road retains turn 6, `(49,50)`, AP 2, empty path, roads 867/879 and
228 visible tiles; rejection retains `(50,50)`, AP 6, empty path, unchanged road
words and 222 visible tiles. Every raw unit-slot byte and all 1,300 visibility
bytes match the original bounded reference. Rejection leaves the complete
725-byte stack record unchanged. Full-record equality to the original is not
claimed: unknown trailing bytes and inactive path storage differ and are listed
in `pilot-runtime-relocated/`. Initial truncated-BMP failures and two viewport
timing failures remain retained; native capture paths and supported shorter
host key holds allow successful retries. No new campaign endpoint or visual
equivalence is claimed. A fresh original-frame pair remains a final-stage gate.

The initial tooling review passed 177 tests. A fresh integrated run passed 234
tests after restart. Later alignment and header-layout checks pass independently;
the final expanded suite will be rerun before integration. Earlier filesystem
and type-alias audit failures remain retained. The header ratchet still reports
exactly 14 historical differences, with no new policy failures.

The authorized WSL restart restored filesystem writes and cleared `/tmp`.
Historical logs, snapshots, hashes, saves and frames remain in the worktree.
Production validation now uses persistent `/var/tmp` trees. Both reference
compiler builds were recreated from the unchanged Git commit; all 693 source
hashes and saved snapshots are unchanged, and both rebuilt reference profiles
pass the saved surface checks without allowances. See `baseline-rebuild/`.

The CMake coverage configuration now limits GCC-only `-fprofile-abs-path` to
GCC. The baseline Clang native run uses a privately extracted distro profiling
runtime with package/header provenance in the private baseline/README.md; no
system dependency installation or coverage stripping was used.

## Remaining sequence

`WorldGeometry` adds three extracted and relocated methods after its separately
committed sine-addressing recovery. Eight historical bodies are now class
methods in three class-named sources, with 143 ordered translation units.
Its production differential, build, storage and asset-free gates pass at both
stages. See [WORLD_GEOMETRY_CLASS_MIGRATION.md](WORLD_GEOMETRY_CLASS_MIGRATION.md).
The separate [unit-turn logging recovery](UNIT_NEW_TURN_LOGGING_CONTEXT.md)
prepares that next family. Native/runtime results above describe their stated
query-pilot snapshots, not untested later changes.

1. Continue class-boundary tooling and validate the next complete families.
2. Expand unit turns, world movement/visibility/selection and Road families.
3. Migrate buildings, special actions and tactical battle families.
4. Migrate strategic rules bridges, mission logic, persistence and menus.
5. Migrate rendering, resources and media.
6. Migrate application and SDL coordination, preserving startup/shutdown order.
7. Audit direct method calls, justified procedural exclusions, all storage and
   identities; run the complete compiler, native, tooling and headless matrix.

Every family needs a reviewed extraction followed by a reviewed relocation.
`tools/migrate_game_class_bodies.py` plans supported whole-class mechanical
transformations and refuses unresolved contracts; a successful dry run is not
behavioral validation. Retain ambiguous context arguments and callback ABI.
Unsupported contracts remain explicit blockers, not permission to guess.

Road work must preserve the 706-byte backing, overlapping lookup scan, live
markers, 53-byte widgets and four-byte callback entries. Relevant gates retain
ordinary-water rejection and the first-Road endpoint at turn 6, `(49,50)`, AP 2,
empty path, roads 867/879 and all 1,300 visibility bytes. Final acceptance also
requires the default smoke suite and six completed direct-route gates, without
claiming campaign completion.

## Reproducible checks

Run builds, tests and games headlessly in Linux/WSL from the repository root.
The source inventory and metadata checks are:

```sh
python3 tools/game_class_catalog.py --check
python3 tools/sync_game_class_manifest.py
python3 tools/class_source_inventory.py
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check --check-tu-includes
python3 -m unittest discover -s tests/tools
```

The evidence scripts contain exact compiler/build and route commands, immutable
input locations and per-attempt outputs. See [BUILD_AND_TEST.md](BUILD_AND_TEST.md)
for the full matrix. No retail assets belong in public CI or committed evidence.
