# UnitStack spent-turn class extraction and relocation

Track: Win95 reconstruction. The separately
[repaired spent-turn operations](UNIT_STACK_SPENT_TURN_REPAIR.md) become explicit
`UnitStack_SetSpentTurnFlag()` and `UnitStack_ClearSpentTurnFlag()` methods.
Each borrows the existing record, binds the original int receiver locally and
otherwise preserves the repaired body. Original-signature free adapters remain
at the original source anchor. Construction performs no game operation.

Both operations preserve zero-extended low32 entry addresses and the complete
native pointer result from modulo-32-bit `base + 6 + 31 * processed_slots`.
The sentinel scan, ten-slot limit, flag writes and untouched bytes remain.
`UnitTurn::Unit_NewTurn` calls the clear method directly; unmigrated callers
retain the original adapters. No callback table, heap ownership, serialization,
native virtual layout, destructor action or initialization is added.

The prepared extraction and relocation each pass eight GCC 13 / Clang 18
O0/O2 signed/unsigned-char UBSan profiles. Every profile compares 72,688
original-measured cases through frozen repaired functions, actual adapters and
direct methods, including full 800-byte arenas and full native pointer returns.
All profiles produce SHA256
`d4e6e644f18f2d9d5f4fbf8ac161913643491e98ac395bab14e24b0d8d7f2903`.
The original repair evidence and its failed historical probes remain separate.

The UnitTurn differential and logging fixtures now compile the real clear
operation. Their former replacement stubs are removed. The frozen turn
reference calls the independently pinned repaired procedural body. The logging
fixture seeds the spent flag and requires it cleared at the diagnostic boundary
before AP calculation or the later ready-flag operation can hide a missing
clear. Both prepared stages pass four turn profiles (4,096 regeneration, 6,144
damage and 336 whole-turn cases each) and four logging profiles (32 cases each),
preserving callback/RNG order and complete affected bytes. Eleven additional
non-crashing controls reject broken method actions, adapter calls, high-bit
returns and an omitted actual turn-clear call.

All 36 prepared affected-TU compiles preserve named storage, complete data
sections, relative order, initialization and existing symbol inventory. The
only new executable symbols are the two methods; changed existing text is
limited to the two adapters and direct UnitTurn caller. No initialization guard
or destructor registration appears. The 4,157 identities and 147-entry source
inventory remain. All five comparison inventories enumerate the two new method
symbols; historical baselines remain unchanged.

Integrated extraction passes all three focused suites, both production builds,
strict symbol/storage comparisons and all eight asset-free gates. The two methods
were then moved unchanged into `src/units/UnitStack.cpp`. The relocation passes
the same three focused suites, both production builds and both strict surface
comparisons. Six asset-free gates pass; each compiler's source audit reaches its
unchanged 60-second timeout. Sequential unchanged retries also time out. All four
failed attempts remain recorded; the relocation's remaining validation is pending
under concurrent filesystem/resource pressure. No timeout or baseline is raised.

All 33 current canonical methods reside in six class-named files. Measured canonical
executable lines change from nine to ten for each method and remain 94 for
`Unit_NewTurn`. All three identities are outside the fixed 718-function set, so
its executable-line denominator is unchanged. Full native coverage and runtime
validation remain separate requirements.

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_spent_turn_repair.py -v
python3 -m unittest discover -s tests/tools -p test_class_unit_turn.py -v
python3 -m unittest discover -s tests/tools -p test_unit_new_turn_logging_context.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py spent-extraction \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260924/spent-class-integration \
  --allowances data/class_migration_september_main_text_additions.json
python3 artifacts/cpp-classes/20260919/validate-incremental.py spent-relocation \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260924/spent-class-integration \
  --allowances data/class_migration_september_main_text_additions.json
python3 artifacts/cpp-classes/20260924/spent-class-integration/retry-source-audits.py
```

The integrated directory retains individual focused and production outcomes.
Preparation is under
`artifacts/cpp-classes/20260919/spent-turn-class-preparation/`, pinned to
`e1b3b50817c7591dde06bd3746c4d845b9d4837f`. Its seal SHA256 is
`6f61d372356c535936d0fecedefc9b17cd6396ab15743e0e99c5bec04290b425`.
Earlier evidence-script stops and subsequent corrections remain recorded.
Public fixtures contain no retail instruction bytes. These checks do not prove
records mapped across address zero, whole-game equivalence or campaign progress.
