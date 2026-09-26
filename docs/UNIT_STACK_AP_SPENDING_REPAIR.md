# AP-spending arithmetic repair before class extraction

Track: Win95 reconstruction. The three AP-spending functions remain procedural
in this separately validated behavioral repair. Their signatures and distinct
algorithms are unchanged:

| Function | Preserved behavior | Representation repaired |
| --- | --- | --- |
| `UnitStack_SpendActionPointsClamped` | Signed comparison and running minimum amount, wrapped byte store, one fact callback | Alignment-safe sentinel read and defined unsigned subtraction before low-byte assignment |
| `UnitStack_SubtractActionPointsFloorZero` | Independent signed comparison per slot; zero branch preserves the old AP in callback context | Alignment-safe sentinel read and unsigned subtraction in the nonzero branch |
| `UnitStack_SpendActionPointsUnchecked` | Unclamped byte subtraction, no callback, low32 cursor return | Unsigned 32-bit cursor arithmetic and alignment-safe sentinel read |

The original instructions use byte subtraction and 32-bit address arithmetic.
The old reconstruction instead triggered signed overflow on `INT_MIN` amounts
or addresses crossing `INT_MAX`, and read unaligned sentinel words through an
aligned pointer type. The repair changes their representations without merging
the algorithms, changing character signedness, normalizing other negative type
words, or altering callback arguments and order.

Fresh original instruction execution establishes 35,280 initial cases and 1,152
additional address-boundary cases. All 36,432 cases pass eight GCC 13 / Clang 18
O0/O2 signed/unsigned-char UBSan profiles against the actual repaired definitions.
Comparisons include complete 800-byte arenas, returns, callback-time bytes,
receiver/context arguments, call order and callback return propagation. The
combined output SHA256 is
`24804fda6893fb9ba7d6b275bd40f471ecf864159847ed951efb0aff50501b18`.
Eleven negative controls reject arithmetic, alignment, sentinel, clamp and
callback-context regressions. Initial and supplementary original measurements
and old failing probes remain individually retained.

Both integrated production builds, strict symbol/storage/initialization
comparisons and all eight asset-free gates pass. The first Clang attempt stopped
before any step because the physical host disk reserve fell below 5 GiB. A
separate single-profile resume passes with the same guard and validation commands;
the initial empty-step result remains recorded. The incoming selection changes
are included in these builds. No historical baseline is updated.

All 4,157 identities, 147 TUs and 27 previously migrated methods remain. Only the
three current canonical body hashes change. Source line counts and the frozen
718-function metadata are unchanged; a new full native coverage measurement is
still separate. The original `Rules_LinkArmyFact` call is an explicit observation
boundary in this fixture, not proof of the complete CLIPS implementation. The
cases cover high-bit mapped handles, signed extremes, byte wrapping, sentinel
prefixes, 16 alignments and floating context values; they do not establish a
record crossing address zero, signaling-NaN behavior or live-game equivalence.

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_unit_stack_ap_spending.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py ap-spending-repair \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260919/ap-spending-integration \
  --allowances data/class_migration_september_main_text_additions.json
```

Logs are in the indicated integration directory. Sealed preparation is under
`artifacts/cpp-classes/20260919/ap-spending-repair/`. Its original evidence seal is
unchanged; the receipt at
artifacts/cpp-classes/20260919/ap-spending-repair/compaction-20260919/receipt.json
maps 813 verified members to six
lossless archives after removal of duplicate loose copies. This receipt is a
private local artifact, absent from clean checkouts. Original measured
corpora, provenance, patches and public fixtures remain directly available.
Public fixtures contain no retail executable bytes. Class extraction follows
as a separately reviewed stage and must exercise adapters and direct methods.
