# UnitTurn behavior-class migration

Track: Win95 runtime reconstruction. Frontier: preserve the complete three-body
UnitTurn family while moving behavior into a borrowing C++ class. Date:
2026-09-06. This is separate from campaign-route progress and from the earlier
GNU++20 language cutover.

## Repaired reference and migration stages

The reference is recovery commit
`356a9ad14e37e4325dec056348aae52f5edb7e18`. Its only Unit_NewTurn behavior repair
replaces an indeterminate, discarded enemy-exit logging context with zero.
[UNIT_NEW_TURN_LOGGING_CONTEXT.md](UNIT_NEW_TURN_LOGGING_CONTEXT.md) records the
original instructions, actual logging callees and independent recovery gate.
Class extraction does not absorb that repair into an unexplained rewrite.

| Original identity | Method | Preserved behavior |
| --- | --- | --- |
| `0x0041E6D0` | `Unit_NewTurnRegen` | Seven building bytes and their countdown handling, including the original returned pointer. |
| `0x0041E730` | `Unit_UpdatePerTurn` | Building hit-point damage calculation, seven ordered RNG calls when applicable, original narrowed stores and return value. |
| `0x004118E0` | `Unit_NewTurn` | Ordered 500-stack turn scan, fatigue/morale/AP updates, rule and diagnostic boundaries, readiness, enemy contact and queued-path decisions. |

Extraction first places each canonical `clash95::UnitTurn` body beside its
original free ABI adapter in the address-named units/buildings translation
units. The adapter borrows live state and calls the method. Original identity,
linkage, adapter body and canonical body remain separately indexed and hashed.
Only after extraction parity may the three canonical methods move to
`src/units/UnitTurn.cpp`; the legacy adapters and borrowing factory retain their
original anchors. Relocation is a separate change and gate, with source order
preserved by the coordinator.

At this document's initial review, root has integrated the extracted bodies;
root production extraction gates and independent relocation gates are pending.
The archived scratch extraction and relocation comparisons already pass, but
those prepared results do not establish acceptance of the integrated build.
No UnitTurn runtime or visual milestone is claimed here.

## Live bindings and ownership

`src/units/UnitTurn.hpp` declares the three methods, `borrow()`, an empty-bodied
borrowing constructor and five reference fields. It includes only the narrow
recovered scalar types header. The registered out-of-line factory binds:

| Reference | Existing storage and purpose |
| --- | --- |
| `state_field_0_` | `aUnit_newturn`, a 15-byte logging string array. |
| `state_field_1_` | `g_BuildingTypeMaxHitPoints`, the existing four-word table. |
| `state_field_2_` | `g_CurrentPlayerIndex`, read at the original decision points. |
| `state_field_3_` | `g_SelectedUnitIndex`, read at the original diagnostic points. |
| `state_field_4_` | `gameData`, the existing integer holding the current world address. |

These are references to the storage locations, including a reference to the
`gameData` address variable, not a copy of its current pointer value. A retained
service therefore sees later global changes. The existing local `stackPtr`
still retains its original per-iteration value: replacing all its accesses with
new global lookups would change callback behavior and is not part of migration.
The `GAME_TURN_COUNTER` and `UNIT_RECORD` expansions keep their original offsets,
widths, evaluation points and live `gameData` accesses through the binding.

The class allocates no records, owns no world or table storage, and introduces
no static initialization. The factory stays at the original buildings anchor;
all five dependencies are enumerated in `class_bindings`. Its header contains
no global-reading inline behavior. Array sizes, stack/slot strides, serialized
bytes and the existing integer-address ABI remain unchanged.

## Packed access and direct class interaction

The migrated Unit_NewTurn and Unit_UpdatePerTurn methods use local same-width
`aligned(1), may_alias` scalar views for the existing packed 16/32-bit accesses.
They preserve signedness, narrowing, arithmetic, offsets and loops. The new
views express the packed alignment contract; they do not re-layout records or
claim portable replacement of the Win95 integer-address ABI. Alignment traps
cover the migrated methods and adapters on supported Linux x86-64 GCC/Clang;
unmigrated external services remain separate contracts.

The already migrated readiness query is called directly:

```cpp
clash95::UnitStack(stackPtr).UnitStack_HasReadyUnits()
```

UnitStack borrows the same current stack address. Its real query scans at most
ten packed slots, stops at the `-1` sentinel and returns on the ready flag.
The old free adapter performs only the corresponding class call. There is no
callback or ownership effect to preserve at that adapter boundary. The class
header is included explicitly; this proven interaction does not route through
the free adapter. Other turn services and predicate function pointers keep
their existing procedural boundaries until their own families are recovered.

## Focused differential evidence

`tests/tools/test_class_unit_turn.py` invokes the production-resolving fixture
in `tests/tools/fixtures/class_unit_turn/`. The fixture indexes current canonical
methods, free adapters and the registered borrowing factory through the
manifest/registry, verifies body hashes, and compares against three frozen
references from the repaired commit. It also compiles the actual UnitStack
readiness canonical method and actual free adapter. The old reference calls
the adapter; the migrated body calls the method directly. No fake readiness
implementation or artificial readiness event remains.

Each GCC 13 and Clang 18 profile at O0 and O2 checks both direct method and free
adapter entry paths:

| Cases per profile | Inputs and complete observations |
| --- | --- |
| 4,096 regeneration cases | All 256 countdown byte values at 16 alignments; returned pointer, all 1,024 guarded building bytes and bound globals. |
| 6,144 damage cases | Four building types, eight signed hit-point values and 12 RNG sequences at 16 alignments; all seven damage bytes, full guarded region, return value, RNG arguments/results/count/order and bound table. |
| 336 turn cases | 21 world scenarios at 16 alignments; both guarded world buffers, all bound globals, returns and ordered callback/predicate/RNG observations. |

The two world allocations contain 589,824 bytes each, plus guards; the fixture
compares the full 1,179,840-byte allocation span. Cases cover absent/foreign
stacks, first and final stack positions, ten-slot limits, invalid types,
readiness in later/last slots, readiness after a sentinel, queued paths and
enemy building contact. Instrumented callbacks change the live world-address
variable or current-player/selection variables mid-turn while the same service
instance remains alive. Complete byte comparisons retain effects in both the
old and newly selected world buffers.

The frozen references retain their original unaligned x86 accesses and alone
are exempted from alignment sanitization. Migrated methods/adapters execute
with `-fsanitize=alignment -fsanitize-undefined-trap-on-error`. Zero maximum HP
and invalid building-table indexes are outside this fixture's source
preconditions. Instrumented external services make ordering and arguments
observable; they do not establish correctness of those services or the entire
game. No production allocation/release behavior is invented; fixture mmap
storage is only test setup.

The independent logging recovery regression remains 32 cases per profile:
four first-stack enemy exits plus 28 logging-context extremes. It compiles
actual Unit_NewTurn, LogAllUnits, Debug_Log and readiness bodies in separate
translation units. Linker wrapping observes the zero context and forwards to
the real logging body; all 589,824 world bytes and actual callback order are
checked. Poisoned automatic locals make the unrepaired control fail all four
profiles. See the recovery document for its separate production gates.

## Durable preparation, reproduction and acceptance limits

Prepared evidence is retained under
`artifacts/cpp-classes/20260906/unit-turn/`: `preparation.tar.gz`, `summary.json`
and `README.md`. The archive SHA-256 is
`ba9176c6a9853bc9c552f3fac90a60cf6b9b694dd64d6df16078e433d73d091a`.
The original scratch root was `/var/tmp/clash95-class-unit-turn-20260906/`;
its continued existence is not required for the durable evidence.

Final preparation records inside the archive include:

- `evidence/direct-ready-extraction/summary.json` and
  `evidence/direct-ready-relocation/summary.json`: all four profiles pass.
- `evidence/direct-ready-integration-test/summary.json`: the maintained wrapper
  passes against the prepared class source.
- `evidence/direct-ready-translation-unit-builds.json`: ten affected whole-TU
  compiler/source combinations pass at O0 across GCC and Clang.
- `evidence/recovery-real-ready-{production,class,negative}/summary.json`:
  stronger actual-readiness recovery checks and expected unrepaired failures.
- `evidence/direct-ready-patch-checks.json`: separate repair, extraction and
  relocation patch checks; final method, adapter and factory hashes are in the
  sibling summary.

Earlier stubbed-readiness and 272-turn-case runs remain historical evidence;
they are superseded by the actual-readiness 336-case matrix above. The
independent integration review verified the three canonical hashes, three
adapter hashes and factory hash against the final preparation and found no new
behavior-contract concern. Tool capability limitations are not treated as
unresolved game semantics.

Run from the worktree root in Linux/WSL, without retail assets:

```sh
python3 -m unittest discover -s tests/tools -p test_class_unit_turn.py -v
python3 -m unittest discover -s tests/tools -p test_unit_new_turn_logging_context.py -v
```

For durable focused outputs, set `CLASH95_CLASS_UNIT_TURN_EVIDENCE` and
`CLASH95_RECOVERY_EVIDENCE` to distinct new Linux directories outside the source
root. The coordinator separately owns integrated extraction and relocation
production builds, exact legacy identity/linkage and named-storage/init/order
comparisons, header/manifest audits, warning checks and all eight asset-free
gates. Full native outcomes and authentic headless runtime/frame evidence
remain separate. No blanket ratchet reset or unenumerated symbol/storage change
is justified by these differential results.

## Integrated extraction

The integrated differential and separate recovery gate pass all four supported
compiler/optimization profiles. Header regeneration legitimately moved the
logging string's declaration to the buildings consumer slice. Both extraction
fixtures now read the factory's exact global declarations from the declaration
database; they no longer depend on that string leaking through a units header.
The first fixture compile failures are retained. Compiler failure details are
also included in the maintained differential's output.

The initial packed-view draft produced five new Clang alignment warnings at
legacy calls. All six affected argument casts now retain the original
`__int16 *` type, including the variadic rules boundary; alignment-one views
remain on direct packed loads/stores. This changes no pointer value, width or
call order. The final Unit_NewTurn method body hash is
`d8c36d5dd375e5df2ee5d00d729b749c9173f2bd41ad2b3a8c080d86744e02cb`.
The other two method hashes and all adapter/factory hashes are unchanged.
`boundary-cast-review.json` records the six exact calls and before/after hash.

Fresh clean GCC 13 and Clang 18 builds retain warning totals 6,618/6,628 and
pass the unchanged warning ratchets. The migration surface permits only the
three methods, one registered factory and trivial constructor variants.
Original identities, named storage, data order and initialization profiles
remain unchanged. Exact extraction commands, per-profile logs and comparisons
are `artifacts/cpp-classes/20260906/pilot/*unit-turn-extraction-boundary*`;
focused results and preserved initial failures are in the sibling `unit-turn/`.

## Integrated relocation

All three unchanged method bodies now live in `src/units/UnitTurn.cpp`, appended
to the existing units source group. The ordered inventory contains 144 sources;
all 4,157 historical identities remain. Adapters and the borrowing factory stay
in their original translation units. The archive gains one additional weak
UnitStack borrowing-constructor definition per compiler variant because the
direct readiness call moved to a new TU; linked constructor counts do not
change. The exact additions are enumerated, with no storage/init allowance.

The relocated differential passes all four profiles. The first recovery repeat
detected generated source changing while it ran and correctly rejected that
attempt; after generation finished, the stable repeat passes all four profiles.
Fresh clean GCC/Clang builds preserve warning totals 6,618/6,628. Both reviewed
surface comparisons and all eight asset-free gates pass. Commands and results
are `pilot/*unit-turn-relocation-resumed*`,
`pilot/*unit-turn-relocation-reviewed*`, and
`unit-turn/relocation-{differential,recovery-resumed}.log` under the same evidence
root. Validation resumed on 2026-09-08. These are pre-origin-refresh migration
results; the incoming origin integration and full native/runtime matrix have
their own gates.
