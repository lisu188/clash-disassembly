# WorldMap visibility class extraction

Track: Win95 reconstruction, behavior-preserving class migration. Three existing
visibility operations now have canonical `clash95::WorldMap` methods, with thin
original-signature adapters in the original world translation unit. This is the
extraction stage; relocation into WorldMap.cpp remains separate work.

| Recovered identity | Original address | Prepared canonical executable lines |
| --- | --- | --- |
| `Map_RevealTileWithPropagation` | `0x0040EDE0` | 29 to 29 |
| `Map_IsTileVisibleToPlayer` | `0x0040F060` | 8 to 8 |
| `Map_ClassifyFogOfWarOverlayForPlayer` | `0x0040F0C0` | 44 to 44 |

The private constructor binds a reference to the existing `int gameData`
variable. Every operation reads its current value, including after callbacks
replace the arena. The class does not retain an arena pointer across loading.
All three arguments, return types, byte calculations and operation order remain.
Recursive reveal and sibling visibility calls go directly to methods; minimap
drawing and text styling remain procedural boundaries. Construction and
destruction perform no game action or allocation.

The current integration starts at `9a74d4c9b486e15495d5a48fea7b3dd81f46eb5d`.
Exactly 22 implementation, fixture and metadata files change: 21 sealed recipe
outputs and the regenerated classifier descriptor in `tests/unit/pure_set.json`.
All 4,157 historical identities and their order remain. The prior 33 methods are
unchanged, making 36 canonical methods across the unchanged 147-TU inventory.
The manifest records the three canonical bodies and distinct adapter hashes;
the factory is a binding, not an additional historical identity.

Both GCC 13 and Clang 18 pass O0/O2, signed/unsigned-char actual-source profiles
with UBSan traps: eight profiles and 24 fixture binaries. Frozen procedural,
actual adapter and direct-method lanes compare 2,034 reveal cases, 33,792 fog
cases and explicit binding/lifecycle checks per profile. The comparisons retain
complete affected bytes, return values, recursive callback and query order,
held-object arena replacement, callback-time replacement and inert lifecycle.
They use frozen reconstruction source, not execution of the original binary.
Classifier arithmetic extremes outside the existing proven domain remain outside
this fixture's claims.

The current extraction also passes five metadata gates, 129 focused tooling
tests and six public fixture entry-point tests, with no skips. Both fresh
production builds, warning checks, strict migration/storage comparisons and all
eight asset-free gates pass. All 870 frozen inputs remain unchanged during
validation. Strict comparisons use exact incoming 33-method binaries and only
enumerated method/factory/constructor text additions; named storage bytes,
alignment, relative order, relocations and initialization remain unchanged.
No storage allowance, ratchet reseed or dynamic initialization is introduced.

The raw historical link ratchets still fail. GCC differences increase from 463
to 467 and Clang from 715 to 719, exactly the four new strong method/factory
symbols per compiler. All original differences and complete current profiles
remain recorded; archive cross-check errors are zero. The narrow strict migration
comparison passes independently of these unchanged historical gates.

Only the classifier belongs to the fixed 718-function coverage set. Its
implementation descriptor now resolves the method. Prepared gcov accounting at
pin `705fc0f` measured the unchanged line counts above, with zero executable-line
delta inside the 718 set. Current method bodies match that prepared recipe;
the full native coverage matrix is now recorded below. The 89.7% floor and
zero-uncovered requirement remain unchanged.

The exact integrated extraction at `9123e70` was validated by
[hosted run 36269978257](https://github.com/lisu188/clash-disassembly/actions/runs/36269978257).
Its actual PR merge `2653041b483452871f239b8d7f2b937de4298b40` has the same
tree as the requested head. All 602 tooling tests, both production builds,
warning checks, eight asset-free gates and both native outcome collectors pass.
Each collector retains all 1,616 ordered outcomes and all 718 coverage rows.
The run fails overall: Clang's assertion and zero-uncovered gate and both raw
historical link gates still fail.

GCC records 1,100 passes, no assertion failures and 516 isolated crashes, with
6,169/6,659 covered/executable lines and zero uncovered functions. Clang records
1,097 passes, one assertion failure and 518 isolated crashes, with 6,808/7,348
lines and the same eight uncovered functions. Both percentage floors pass.
Both executable denominators are unchanged from the prior `12ff25b` checkpoint;
the visibility extraction adds no executable line to the selected set.

GCC loses one covered line in the unchanged procedural
`Map_RevealTilesInRadius2ForPlayer` (13/15 to 12/15). That function calls the
class-backed reveal operation and contains an existing uninitialized loop
cursor; all three of its native cases still crash. The retained coverage has
aggregate rows, not per-line counters, so the missing line and cause remain
unknown. Clang loses six covered lines across two unchanged CRT functions.
Three additional Clang cases crash compared with `12ff25b`, but all three also
crashed in the incoming-main reference. The two unfavorable changes against
that reference remain unresolved. These observations are not waived as
historical merely because the procedural source is unchanged.

Exact checkout identities, all native outcomes, coverage deltas and source
comparisons remain under
`artifacts/cpp-classes/20260926/ci-review/integrated9123e70/`. This extraction
run does not validate the subsequent source relocation or runtime behavior.

Preparation was independently reproduced and tested for extraction and relocation
in [hosted run 36267455378](https://github.com/lisu188/clash-disassembly/actions/runs/36267455378).
That older-pin preparation is distinct from the fresh current integration above.
The original resource hold, initial local Git-path preflight failure before any
source write, and all historical failures remain recorded. The local retry uses
Windows Git for read-only worktree checks; no Git metadata or global safe-directory
setting changed.

Durable current evidence is under
`artifacts/cpp-classes/20260926/visibility-extraction/`, including the exact
commands, input freeze, compiler products, raw profiles, complete fixture intake
and independent review. Its 652-file seal SHA256 is
`51dfaf34c9e67b00f857d3489b2936c8a03875261627baf454f1d32aee041797`.
The sequential validation entry point was:

```sh
python3 -B artifacts/cpp-classes/20260926/visibility-extraction/run_validation.py
```

The retained one-shot recipe and validator require fresh guarded output paths;
do not rerun them over sealed evidence. Both filesystems stayed below the 90%
usage threshold with an additional 2-GiB reserve. Relevant runtime gates,
relocation validation and the unresolved native observations remain outstanding.
The [33-method first-Road comparison](CPP_CLASS_FIRST_ROAD_REVALIDATION.md#september-26-33-method-checkpoint)
is a baseline, not runtime validation of these three new methods. No visual or
campaign milestone is promoted.
