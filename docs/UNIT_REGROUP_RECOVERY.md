# Unit regroup recovery before class extraction

Track: Win95 reconstruction. Frontier: assembly-backed prerequisites for the
requested behavior-class migration. This batch changes only
`UnitStack_RegroupWithOtherStackByHealth` at `0x4582B0`; it does not migrate that
identity or change the 13-method, 145-translation-unit inventory.

The recovered function now uses its saved first stack index instead of an
undefined register local. Both movement calls pass zero for a proven-unused
context. Health comparison uses the original signed-byte ordering, and packed
word accesses use alignment-one alias types. The unusual repeated adjacent-pair
comparison loop is preserved. Reads of `gameData` remain at their original
positions across movement and execution callbacks.

The evidence is the original instruction stream, including the saved index at
`0x4582BB`, and 4,096 original-measured scenarios in each GCC 13 / Clang 18 O0/O2
profile. The public asset-free fixture compares returns, two complete 4,096-byte
arenas, the 404-byte path buffer and callback order. The movement and lifecycle
callees are scripted boundaries: this does not prove their own pathfinding,
allocation, destruction or fact behavior. Confidence in the bounded repair is
high; campaign completion is unchanged.

Validation from the repository root in WSL:

```sh
python3 tools/update_split_manifest_hashes.py --update --only UnitStack_RegroupWithOtherStackByHealth
python3 tests/tools/test_unit_regroup_recovery.py
python3 artifacts/cpp-classes/20260913/validate-stage.py regroup-recovery --reference-dir artifacts/cpp-classes/20260908/origin-latest-reference --evidence-dir artifacts/cpp-classes/20260913/regroup-integration --allowances data/class_migration_latest_origin_text_additions.json
```

All four focused profiles, both production builds, strict cumulative
symbol/storage/initialization comparisons and all eight asset-free gates pass.
The one current canonical hash is updated; historical hashes and ratchet
baselines remain unchanged. Durable local evidence is under
`artifacts/cpp-classes/20260913/regroup-integration/` and
`artifacts/cpp-classes/20260913/copy-descriptor-audit/`. The public fixture pins
the measured output hashes and requires no original executable or retail data.

The separate proposed stack-copy repair remains unapplied. Original writable
copy descriptors at `0x50F090` and `0x50F0B0` supply callbacks and strides sampled
once per helper call. No gameplay writer was found, but immutability is unproved.
Hardcoded loops would remove that interface. Preserve this unresolved contract
until procedural descriptor dispatch is recovered; stock-descriptor test passes
alone do not justify advancing the copy family.
