# UnitStack AP-spending class extraction

Track: Win95 reconstruction. The three separately
[repaired AP operations](UNIT_STACK_AP_SPENDING_REPAIR.md) become explicit
UnitStack methods with their recovered names:

- `UnitStack_SpendActionPointsClamped`
- `UnitStack_SubtractActionPointsFloorZero`
- `UnitStack_SpendActionPointsUnchecked`

Each method removes only the proven stack receiver and binds the same pointer
or int representation locally. Amount types, signedness, return values, uncertain
DWORD/double context arguments and the three distinct algorithms remain intact.
The first two retain their exact `Rules_LinkArmyFact` calls and callback order;
the unchecked operation retains its wrapped byte subtraction and low32 return.
Construction only borrows the address. Original-signature free functions remain
thin adapters. No already migrated method calls these three operations, so no
additional direct-call conversion is needed in this batch.

Frozen repaired functions, actual adapters and direct methods match all 36,432
original-measured cases in eight GCC 13 / Clang 18 O0/O2 signed/unsigned-char
UBSan profiles for each prepared stage. Comparisons include complete 800-byte
arenas, return bits, callback-time bytes, callback arguments and return
propagation. Six additional non-crashing controls reject omitted method actions
or adapters forwarding the wrong amount. The actual integrated extraction
fixture also passes all eight profiles. Its original output SHA256 remains
`24804fda6893fb9ba7d6b275bd40f471ecf864159847ed951efb0aff50501b18`.
The controlled fact callback does not establish full CLIPS behavior.

All 24 prepared affected-TU compiles preserve named storage, initialization,
existing symbol counts and all unrelated executable symbols. Exactly three
method symbols are added. Two unchanged-source callers have expected compiler
optimization changes. One Clang O2 raw-data comparison initially failed and is
retained: seven relocation addends in the anonymous 112-byte queued-path jump
table move to their corresponding code blocks. Raw bytes, section order,
alignment, relocation types and named storage remain exact. Four redraw targets
have identical instruction blocks and map to the same shared animation block;
the other three entries map that shared block. This is a specific explanation
of compiler code addresses, not a general data allowance or complete instruction
equivalence claim for the optimized caller. The production checker is unchanged.

Both integrated production builds, strict symbol/storage/initialization
comparisons and all eight asset-free extraction gates pass. There are 31 canonical
methods, with these three still in their original TU pending relocation. All
4,157 identities, 147 translation units and six class sources remain. All five
comparison inventories enumerate only the three new method symbols; historical
ratchet baselines remain unchanged.

Measured GCC executable lines are clamped 13 to 14, floor-zero 13 to 14 and
unchecked 10 to 11; each adapter has two. Only floor-zero belongs to the frozen
718-function set, adding one canonical executable line to its denominator.
Adapters are not counted as implementations. Fresh integrated native coverage
and runtime validation remain separate requirements.

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_unit_stack_ap_spending.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py ap-extraction \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260924/ap-class-integration \
  --allowances data/class_migration_september_main_text_additions.json
```

The integrated directory retains focused results and individual production
steps. The sealed preparation and exact jump-table explanation are under
`artifacts/cpp-classes/20260919/ap-spending-class-preparation/continuation-20260924/`.
Its evidence seal SHA256 is
`da2c029e5a020770532b3ec536ccb949e86600c3729257d5fa2de92e50702b9f`.
Earlier raw comparison failures and corrected evidence-script stops remain
recorded. The incoming rendering constants and rules-validation tooling from
main `35f3adb` are included in the integrated extraction.
