# Game-system class migration

Track: Win95 reconstruction. Frontier: manifest/tooling foundation and the unit
query pilot. This migration is in progress. The completed GNU++20 language
cutover is documented separately in [CPP_MIGRATION.md](CPP_MIGRATION.md).

The reference is `6f7537268e784c538133b714e3ccb77cf54052e4`. Original packed
records, globals, low32 handles, callback tables, save bytes and explicit
lifecycles remain authoritative. Classes describe the reconstruction's
organization, not proven original C++ object layouts. The migration does not
advance campaign or visual-fidelity claims.

## Inventory and implementation rules

`data/game_class_registry.json` assigns all 4,157 recovered identities:
1,849 intended game methods across 116 classes, 22 retained utilities/boundaries
and 2,286 excluded library implementations. Each procedural disposition has a
rationale. Four declaration-database helpers are tracked separately without
invented addresses. The five rendering helpers historically filed under `clips`
are game functions; CLIPS implementations filed under `media` remain procedural.
Assignment is architectural intent, not proof that a family has migrated.

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
runtime with package/header provenance in `baseline/README.md`; no system
dependency installation or coverage stripping was used.

## Remaining sequence

1. Complete foundation and pilot extraction/relocation validation and commits.
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
