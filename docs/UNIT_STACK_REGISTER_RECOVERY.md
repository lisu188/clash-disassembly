# UnitStack register contracts before class migration

Track: Win95 reconstruction; frontier: separate assembly-backed repairs before
extracting military-strength and peasant-cargo behavior. This batch changes two
existing implementations in `src/units/004115E0_00412BE0_units_002.cpp`; it does
not move their bodies or change their signatures, storage or save formats.

## Repairs and evidence

`UnitStack_CalcMilitaryStrength` now forwards the original stack's slot address
after counting its squads. Original instructions at `0x412BE3` preserve the
incoming stack in EDX; the count helper preserves EDX, and `0x412BEA` computes
its six-byte displacement with 32-bit wrapping. The previous C++ body used an
uninitialized temporary for that address. Count/score order, zero wall bonus and
the returned score remain. Confidence: high for this target's call contract;
the caller's other lost accumulators are separate recovery debt.

`UnitStack_NormalizePeasantCargo` now retains the threshold
`(peasantSlotCount - 1) * 100` across the AP query, matching `0x412201..0x412211`.
It consolidates only when this threshold is strictly greater than the signed
quantity total. Quantities use explicit signed bytes and packed type words use
alignment-one aliases. Clearing, compaction, remainder creation, sentinel writes
and unconditional final strength synchronization retain their order.

Two undefined final sync-context values become zero after tracing
`Rules_SyncArmyFactStrength` (`0x455070`), Ensure (`0x454ED0`) and Retract
(`0x452250`): these incoming slots do not influence this path. The actual army
identifier used by Create (`0x4521D0`) is rederived from occupancy and remains
unchanged. Other parameters and double-context bits are retained. Confidence:
high for the reviewed target and these ignored context slots.

## Validation and limits

The public test resolves actual canonical definitions through the shared
manifest indexer and checks their current body hashes. Its expected byte/call
contract is pinned to original-measured input/output stream hashes before it
can supply expectations. The private comparison executes original PE
instructions with controlled dependency hooks.

All 5,001 cases pass under GCC 13 and Clang 18 at O0/O2, with default and unsigned
`char`, UBSan traps and warnings as errors. The cases include 297 strength-call
contracts and 4,704 cargo inputs: signed extremes, threshold equality, sentinel
tails, partial writes, all eight packed alignments, complete 800-byte backing
images, returns and callback-time byte hashes. Negative controls reject wrong
slot displacement, equality handling and unsigned quantities. Nine provenance
controls include coordinated mutation of the model and production source.

The dependency hooks isolate these two implementations. They do not establish
equivalence of real compaction, scoring, fact-engine behavior or player totals.
The current `Unit_CompactSquad` stable filter differs from the original's
repeated shifts for some trailing bytes and fact callbacks. This is existing
original-equivalence debt, not permission to change that dependency during class
migration. No campaign, frame or whole-game equivalence claim follows.

Commands, from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_unit_stack_register_contracts.py -v
python3 artifacts/cpp-classes/20260906/pilot/validate-stage.py unit-register-recovery \
  --reference-dir artifacts/cpp-classes/20260908/origin-latest-reference \
  --evidence-dir artifacts/cpp-classes/20260908/unit-register-recovery \
  --allowances data/class_migration_latest_origin_text_additions.json
```

Original instruction ranges, rejected candidates, all individual failing
controls and the sealed preparation are retained in
`/var/tmp/clash95-register-contract-audit-20260908/REPORT.md` and its associated
evidence. Integrated test/build logs are under
`artifacts/cpp-classes/20260908/unit-register-recovery/`.

The integrated focused test, both production builds, exact legacy/text/storage
and initialization comparisons, and all eight asset-free gates pass. This is
the separate recovery checkpoint; neither repaired identity has moved to a
class in this batch. Historical warning/header/link ratchets are unchanged.
