# UnitSlot action-point classes

Track: Win95 reconstruction; frontier: behavior-preserving class extraction.
`UnitSlot_CalcActionPointsFromFatigue` and `UnitSlot_GetBaseActionPoints` now
have canonical const methods and original-signature adapters. Extraction keeps
the methods immediately after their adapters in units_001. `UnitTurn` calls
the AP method directly, preserving its existing slot expression and
post-increment. The constructor still only binds the record address.

The narrow `UnitSlot_BorrowTypeMetadata` helper returns the existing immutable
40-row metadata table. Its 3,520 bytes, 88-byte rows, linkage, initializer and
relative storage order remain in the original state TU. The helper has its own
retained-boundary classification and declaration; it is not a new recovered
identity or an owning replacement. No gameData pointer is cached.

The fatigue calculation retains its current signed-type guard for `0..34`,
unsigned AP, thresholds and integer arithmetic. That guard is an existing
reconstruction difference from the original and is not repaired here. The base
AP getter keeps its unguarded access, with an alignment-safe signed word load;
its differential domain is all 40 actual storage rows. No behavior is invented
for out-of-range getter indices. The original names and parameter widths remain.

The actual-source fixture compiles manifest-resolved methods, adapters, helper
and the immutable table in separate translation units. Frozen pre-migration
bodies have independent file and body hashes. Each GCC 13/Clang 18 O0/O2 profile
checks 7,143,424 cases: all 16 alignments, low32 and native pointer receivers,
signed type-word guards, AP/fatigue combinations, all getter rows, callback and
direct calls, full guarded slot arenas and complete table bytes. UBSan checks
the actual methods; the frozen reference getter alone retains an exemption for
its old unaligned read.

The composed UnitTurn fixture now compares the actual turn and AP methods with
both frozen bodies. Each profile retains its 4,096 regeneration, 6,144 damage
and 336 turn scenarios, full affected bytes, callback/RNG order and live binding
changes. Other service boundaries remain instrumented; this is bounded parity
evidence, not whole-game equivalence.

Preparation retains 60 full-TU object compilations across three source stages
and four compiler profiles, twelve negative controls and twelve relocatable
links. Named storage, data bytes/relocations, relative order and initialization
remain unchanged. New text is exactly two AP methods and the accessor. At O0,
existing constructor archive copies grow from one to three and coalesce when
linked. Existing adapter/caller changes and unwind metadata are enumerated;
the exact migration surface checker remains unchanged.

The frozen 718-function inventory gains **one executable line**, in GetBase
(2 to 3). Calc gains one line outside that set. This is a source-extraction line
measurement; it does not establish full native coverage. Neither the 718 set,
89.7% floor nor zero-uncovered requirement changes.

Preparation evidence is under
`artifacts/cpp-classes/20260913/unit-slot-ap-preparation/`. The first Windows Git
transport check rejected six new-file entries lacking `new file mode` metadata;
no production source was changed by that attempt. A separate transport copy
adds only those headers, passes Git's check, and leaves the sealed original
package unchanged. Both checks and hashes are retained under
`artifacts/cpp-classes/20260913/unit-slot-ap-transport/`.

Integration commands from the repository root in WSL:

```sh
python3 artifacts/cpp-classes/20260913/unit-slot-ap-preparation/apply_metadata.py . extraction --write
python3 artifacts/cpp-classes/20260913/append-ap-published-allowances.py
python3 artifacts/cpp-classes/20260913/generate-with-stable-mtimes.py
python3 tools/migrate_pure_coverage_metadata.py
python3 tests/tools/test_class_unit_slot_ap.py
python3 tests/tools/test_class_unit_turn.py
python3 artifacts/cpp-classes/20260913/validate-stage.py unit-slot-ap-extraction --reference-dir artifacts/cpp-classes/20260913/published-main-reference --evidence-dir artifacts/cpp-classes/20260913/unit-slot-ap-integration --allowances data/class_migration_published_main_text_additions.json
```

The generated-byte-preserving wrapper restores timestamps only for files whose
bytes remain identical. The public generator and source audit still own the
generated declarations, includes and dependencies. Full integration results
are retained under `artifacts/cpp-classes/20260913/unit-slot-ap-integration/`.
The earlier 19-method tooling/metadata checkpoint is described separately in
[CPP_CLASS_RESUMED_VALIDATION.md](CPP_CLASS_RESUMED_VALIDATION.md).

The extraction passes both actual-source tests, both production builds, both
strict current-main surface comparisons and all eight asset-free gates. There
are now **21 canonical methods**, with the two AP methods still in their
original TU at this extraction stage. Six class-named files and the 146-TU
inventory remain. No historical numerical ratchet is raised.
