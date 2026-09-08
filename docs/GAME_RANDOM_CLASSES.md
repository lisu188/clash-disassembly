# GameRandom class extraction

Track: Win95 reconstruction, requested behavior-class migration. The separately
committed GameRandom recovery at 79d700c86e253180b1bb81c0a2833b48ae5fe1ba is the
frozen reference. This batch adds behavior classes without changing the repaired
RNG contracts. No campaign, runtime or visual milestone is advanced.

## Behavior and original storage

The two canonical operations, initRandomSeed and Rng_RandRange, are const methods
of clash95::GameRandom. Extraction keeps their bodies beside the original
adapters in src/units/00414390_00416750_units_004.cpp. Each original free-function
signature and linkage remains, with used/retain attributes protecting the ABI
entry point. The methods retain parameter types, names, wrapping arithmetic,
clock/log call order and current zero-range compatibility behavior.

GameRandom borrows exactly char (&format)[29] and int &state. Its constructor
only binds these references, and destruction is trivial. The registered borrow()
factory remains at the original units004 anchor and binds ::aRandom_initSee and
::g_RngState in the registry's canonical sorted order. The existing 29-byte
format and four-byte seed stay in their original state translation unit; no
storage, initialization, release or lazy action moves into the class.

UnitTurn::Unit_UpdatePerTurn calls GameRandom::borrow().Rng_RandRange directly.
Its own five existing bindings remain unchanged. Other procedural callers still
use the original adapters; clock and logging remain procedural boundaries.
No class caches gameData, introduces virtual dispatch, RTTI, exceptions, a
serialization format or an owning replacement for the original records.

The manifest retains all 4,157 identities and historical hashes. Extraction
maps two identities to their qualified methods and separately hashes both
adapters; the direct UnitTurn call changes only that method's current hash.
The separate class binding registry adds one address-free factory and its hash.
The ordered source count remains 144 for extraction. No ratchet baseline changes.

## Validation

Run headlessly in WSL from the repository root:

    python3 -m unittest discover -s tests/tools -p test_class_game_random.py -v
    python3 -m unittest discover -s tests/tools -p test_game_random_recovery.py -v
    python3 -m unittest discover -s tests/tools -p test_class_unit_turn.py -v
    python3 tools/audit_split_sources.py
    python3 tools/gen_subsystem_headers.py --check --check-tu-includes
    python3 tools/class_source_inventory.py

All three focused gates pass GCC 13 / Clang 18 at O0 and O2. The new migration
gate compares actual canonical methods, adapters and borrowing factories with
hash-pinned repaired free bodies at the reference commit. Actual Debug_Log is
compiled in its own translation unit; the wrapper records its arguments and
forwards to the actual logger. Clock boundaries preserve the recovered clock's
effects. No replacement RNG algorithm is used as the migration reference.

Each profile passes 69,737 scenarios: 729 range/seed extremes, 65,536 generated
range cases, 400 initializer cases across logging flags, 1,024 independent live
bindings and 2,048 composed actual UnitTurn/GameRandom damage cases. Returns,
complete 64-byte seed and format backing images, exact bound format pointers,
clock count/order and logging arguments match. Objects retained across external
state/format writes observe the new bytes. Constructor/factory/destructor checks
verify no state or callback changes. The composed caller checks complete
4,096-byte backing images at all 16 packed alignments.

The earlier recovery gate still compiles the actual class methods and original
adapters and passes 68,932 scenarios plus 4,096 sequence steps per profile.
Its unrepaired negative controls remain. The existing UnitTurn gate retains
4,096 regen, 6,144 damage and 336 turn cases, including arbitrary instrumented
RNG-boundary returns; that gate's explicit GameRandom boundary mock is separate
from the new gate's actual composed implementations.

Three deliberate migration defects each compile and fail all four profiles:
copying the seed instead of binding it, bypassing the bound seed with a global,
and bypassing the bound format with a global. The failures occur at the expected
complete-byte/live-binding/pointer assertions. The old char-subscript warning
in both actual and frozen UnitTurn damage bodies remains visible; only that
preexisting warning is permitted in those fixture translation units.

The source audit, exact factory validation and generated include checks pass.
Across before/extraction/relocation, all 28 complete translation-unit compilation
checks pass. Every named object, its bytes/relocations/alignment and initializer
inventory agrees in all compiler profiles; there are no removed text symbols.
Exact new text consists of the two methods, borrow factory and compiler-emitted
O0 constructor aliases. Production link, strict full-binary storage/symbol
comparison, full tooling/native/coverage and runtime gates remain coordinator
integration work; historical failures and individual crashes remain visible.

The coordinator repeated all three focused gates and source/inventory checks
against the applied extraction. The first complete header audit rejected the
prototype parameter names `a1` and `a2`, which collide with legacy global names
in its conservative dependency scan. The header now uses `arg_0` and `arg_1`,
matching existing class headers; canonical body names, signatures and hashes
are unchanged. Both audit attempts remain in the integration evidence.

Both production builds, exact linked/archive text allowances, named storage,
relative storage order and initialization comparisons pass against the frozen
1b8b4b8 upstream reference with the existing cumulative migration allowances.
All eight asset-free gates pass. The incremental build changes only units004
and UnitTurn objects per profile; no clean build or warning-total claim follows.
Evidence and exact commands are under
`artifacts/cpp-classes/20260908/game-random/*game-random-extraction*`.
The header dependency policy passes after the parameter-name adjustment; its
historical numerical ratchet failures remain reported without a baseline update.

## Rejected synthetic callback contract

An exploratory fixture changed RNG state inside Time_Now and exposed unspecified
operand evaluation order in the unchanged seed + Time_Now expression. Actual
Time_Now reads its performance counter and Frequency and does not change RNG
state. The final fixture preserves those effects and exercises external writes
between operations. No arbitrary reentrant RNG writes inside a clock call are
claimed equivalent, and no speculative production repair was made. The rejected
harness and its failed results are retained as evidence.

## Preparation evidence

Scratch /var/tmp/clash95-game-random-class-6qaw9jbq contains the frozen reference,
separate stage patches, metadata/generated-include review deltas, exact commands,
positive/negative logs, object comparisons and failed preparation attempts.
The first composed compile retained a historical UnitTurn warning under Werror;
its narrowly scoped warning treatment leaves the production body unchanged.
An initial source layout was rejected by the canonical definition-order audit;
placing each extracted method beside its adapter restored the manifest order.
Preserve the evidence before deleting temporary working data.
