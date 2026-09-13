# UnitSlot fatigue and order-state classes

Track: Win95 reconstruction; frontier: behavior-class extraction after the
published-main refresh. Four recovered identities now have canonical `UnitSlot`
methods: `UnitSlot_ShouldGainFatigueFromLowActionPoints`,
`UnitSlot_CanRecoverFatigue`, `UnitSlot_HasSevereFatigue`, and
`UnitSlot_CycleOrderState`. The first stage keeps methods in the existing
units_002 translation unit, with original-signature C-linkage adapters at their
address markers. This is 17 implemented identities; relocation is a separate
stage, and the inventory still has 145 translation units at extraction.

The view binds only an `intptr_t` address. Construction writes no record bytes
and destruction performs no action. The original integer receiver is recreated
locally, including the pointer-valued return from order cycling. Unsigned AP,
signed fatigue, state-bit tests and each staged stance-byte write are preserved.
Original callback pointers remain ordinary free functions; `UnitTurn` retains
these predicate callbacks. No allocation, RNG, table replacement, cached
`gameData`, storage binding or static initialization is introduced.

The actual-source test resolves both roles from the manifest and compiles the
canonical methods and ABI adapters separately. Frozen references are the exact
production definitions at `c65e476`, independently hash-pinned. GCC 13 and
Clang 18 O0/O2 with UBSan each cover 1,048,576 byte scenarios over all 16
alignments, invoking all four operations via direct methods and original
callback pointers and comparing complete 256-byte arenas. One view remains
bound while its backing changes. Ten negative controls are rejected.

The preparation's four-profile full-TU comparison preserves all existing
symbols, named storage, allocated data bytes/relocations and initializer records.
Only explicitly enumerated method and trivial constructor text is added.
At O2 relocation may change the unchanged `UnitStack_CycleAllSlotOrders` caller
from an inlined operation to a call; the preparation retains that disassembly.
These checks establish bounded migration parity, not whole-game equivalence.

The first root production attempt linked but failed the definition-order audit:
the prepared extraction appended the four methods at the end of the old TU.
Moving each unchanged method immediately after its own adapter satisfies the
manifest's ordered-definition contract. Exact canonical and adapter hashes did
not change. The initial failure and ordered retry remain separate logs.
The ordered extraction passes both production builds, strict current-main
symbol/storage/initialization comparisons and all eight asset-free gates.

The frozen 718-function set contains severe fatigue and order cycling. Actual
GCC gcov inspection counts 3 to 4 and 13 to 14 executable lines respectively:
**two added executable receiver-binding lines**, with no identity removed.
The 89.7% floor and zero-uncovered requirement remain unchanged. Full native
coverage outcomes are recorded separately; this line inventory is not a full
coverage pass.

Commands from the repository root in WSL:

```sh
python3 artifacts/cpp-classes/20260913/unit-slot-preparation/apply_metadata.py . extraction --write
python3 tools/gen_subsystem_headers.py --write --write-tu-includes all
python3 tools/migrate_pure_coverage_metadata.py
python3 tests/tools/test_class_unit_slot.py
python3 artifacts/cpp-classes/20260913/validate-stage.py unit-slot-extraction --reference-dir artifacts/cpp-classes/20260913/published-main-reference --evidence-dir artifacts/cpp-classes/20260913/unit-slot-integration --allowances data/class_migration_published_main_text_additions.json
```

Durable preparation, full-TU checks and negative-control evidence are under
`artifacts/cpp-classes/20260913/unit-slot-preparation/`; root integration logs
are under `artifacts/cpp-classes/20260913/unit-slot-integration/`. No historical
ratchet is raised. The earlier first-Road runtime checkpoint predates this
extraction and is not claimed as validation of these new methods. The remaining
UnitSlot families, campaign continuation and known rendering defects remain
separate work.
