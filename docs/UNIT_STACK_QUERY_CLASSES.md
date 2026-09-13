# UnitStack plague and morale queries

Track: Win95 reconstruction; frontier: behavior-preserving class migration.
`UnitStack_HasPlague` and `UnitStack_HasLowMoraleUnit` become const methods on
the existing non-owning UnitStack view, with retained original-signature
adapters. Extraction places each method immediately after its adapter in
units_002. The proven integer receiver becomes a local `(int)address_`; the
remaining statements retain their original order, widths and signed results.

The queries inspect packed slot records and stop at the first sentinel. They
introduce no callbacks, allocation, release, RNG use, storage accessor, cached
game state or initialization. The constructor remains binding-only. Ordinary
function pointers continue to address the adapters.

Each extraction and relocation fixture runs 62,140 cases in eight profiles:
GCC 13/Clang 18, O0/O2, default and unsigned char. It compares frozen production
bodies, manifest-resolved methods and adapters, with all 800 record/guard bytes.
Cases cover flags, slot prefixes, all 16 alignments, protected-page sentinels
and records spanning the signed address boundary. Thirty-two deliberate bad
controls are rejected. The preparation's 24 full-TU object compilations retain
named storage, relative order, data sections/relocations, initializer records
and existing symbols. Only the two enumerated method symbols are added.

Both identities lie outside the frozen 718-function set. The methods add two
receiver-binding executable lines outside that set; its membership, 89.7% floor
and zero-uncovered requirement remain unchanged. These bounded comparisons do
not establish whole-game or campaign equivalence.

Integration takes source and test hunks from the sealed package and updates
only these two manifest mappings. Existing historical fields and unrelated
AP/UnitTurn changes are preserved. The exact two method additions extend all
four current migration comparison inventories; no baseline is raised. No
class source, TU, binding or generated public-header visibility is added.

Commands from the repository root in WSL:

```sh
python3 artifacts/cpp-classes/20260913/apply-unit-stack-query-metadata.py extraction
python3 artifacts/cpp-classes/20260913/generate-with-stable-mtimes.py
python3 tools/migrate_pure_coverage_metadata.py
python3 tests/tools/test_class_unit_stack_flags.py
python3 artifacts/cpp-classes/20260913/validate-stage.py unit-stack-query-extraction --reference-dir artifacts/cpp-classes/20260913/published-main-reference --evidence-dir artifacts/cpp-classes/20260913/unit-stack-query-integration --allowances data/class_migration_published_main_text_additions.json
```

Durable evidence is under
`artifacts/cpp-classes/20260913/unit-stack-flags-preparation/` and
`artifacts/cpp-classes/20260913/unit-stack-query-integration/`.

The preparation also found separate setter defects: the plague setter returns
a pointer six bytes above the original result, and both spent-turn setters
overflow signed address arithmetic for valid records crossing INT_MAX. The
query migration leaves those setters unchanged. The artifact package retains
the original-measured return corpus, all eight old-body failures, individual
UBSan outcomes and a separately reviewable plague-return repair. No receiver
domain is narrowed to hide these findings.

The root extraction passes the actual-source fixture in all eight profiles,
both production builds, strict symbol/storage/initialization comparisons and
all eight asset-free gates. It has **23 canonical methods**, with the two new
queries still in the original TU pending separate relocation; six class-named
files and 146 recovered TUs remain. Header generation produces no changed bytes.
