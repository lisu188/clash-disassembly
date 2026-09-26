# UnitStack personage query class migration

Track: Win95 reconstruction; frontier: behavior-preserving extraction of
`UnitStack_GetMaxOrderTier`, `UnitStack_HasNormalCombatUnits` and
`UnitStack_HasSpecialPersonageUnits`.

All three identities have canonical `UnitStack` methods and original-signature
adapters. The max-order method calls the special-personage method directly.
`Unit_GetSquadCount` remains an actual procedural boundary, including its signed
return contract. Objects only borrow existing records. Two word scans use
alignment-one aliases; the existing packed special-personage scan is unchanged.
No class, accessor, storage, allocation, TU or historical identity is added.

## Extraction evidence

The public actual-source fixture compiles the methods, adapters, frozen free
functions, actual squad-count helper and real class header. All eight GCC 13 /
Clang 18 O0/O2 signed/unsigned-char profiles pass. Each checks 87,184 scenarios
against fresh unchanged original instructions: three return registers and all
800 surrounding bytes, every signed 16-bit type word, all 16 packed alignments,
sentinel positions, order-byte values and records crossing `INT_MAX`.
Eleven guard-page cases and 176 controlled helper-return scenarios additionally
check receiver, call order, call-time bytes and constructor inactivity. A failing
legacy special-personage adapter detects accidental adapter re-entry.

Sixteen deliberate negative controls fail as intended. Thirty-six preparation
full-TU compiles preserve named storage, allocated non-code bytes, relative order
and initialization sections. Existing optimized caller text changes are recorded;
they do not authorize source or behavior changes in those callers.

Both production builds, strict symbol/storage/initialization comparisons and
all eight asset-free gates pass after extraction. All 4,157 identities remain.
There are 27 canonical methods: 24 in six class-named files and these three
temporarily in their original unit translation units. The inventory stays at
147 TUs. Historical hashes and ratchet baselines are unchanged.

The same 718-function coverage set includes only the special-personage query
from this family. Its executable lines change from 9 to 10. The other two
queries change 12 to 13 and 27 to 28 outside that set. These are measured
preparation deltas, not a new integrated coverage result. The earlier integrated
runtime/native evidence remains pinned to the 23-method checkpoint.

## Relocation and limits

Relocation into `src/units/UnitStack.cpp` passes as a separate stage after
extraction commit `f56a28b`. All three canonical body hashes remain identical.
The actual-source fixture again passes all eight profiles; both production
builds, strict surface comparisons and all eight asset-free gates pass. All 27
methods now occupy six class-named files, with the same 147-TU inventory.
Canonical hash, coverage mapping and Markdown checks also pass. This evidence
establishes neither campaign completion nor visual equivalence.
Nearby morale, plague and spent-turn repairs remain separate behavioral work.

## Reproduction and retained evidence

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_class_unit_stack_personage.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py unit-stack-personage-extraction \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260919/unit-stack-personage-integration \
  --allowances data/class_migration_september_main_text_additions.json
```

The production logs are under the indicated evidence directory. The sealed
preparation at `artifacts/cpp-classes/20260919/unit-stack-personage-33a5959/`
contains 375 exact inputs from commit `33a5959`, original-instruction provenance,
all stage/profile and negative-control results, object comparisons and patch
round-trip checks. Public fixtures contain generated inputs and hashes, not
retail executable bytes. The original observation output SHA256 is
`27fbceb574174691525f81fb61ab4121064418190a0ff057ae6efb664b2d51a8`.
