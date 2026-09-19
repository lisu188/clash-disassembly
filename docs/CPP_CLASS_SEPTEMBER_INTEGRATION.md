# September 19 class and main integration

Track: Win95 reconstruction; frontier: integrate the validated UnitSlot and
UnitStack batches with published main `02c00bf`. The result retains all 4,157
historical identities and 23 canonical methods in six class-named sources.
The ordered source inventory grows from 146 to 147 because main independently
moved Road widget initialization to its buildings owner and renamed the old
world anchor. Class migration introduces no additional TU in this merge.

The incoming movement, queued-path bridge, temple march, builder-menu and human
selection recoveries are preserved. The class branch's identity changes and
incoming identity changes have no overlap. Merge conflicts were architecture
counts and the class-progress introduction; the manifest conflict was only its
top-level source count. Header/dependency regeneration changes no merged bytes.

Both clean supported production builds, frozen warning checks, all eight
asset-free gates and strict migration comparisons pass. Current-main comparison
inputs are independently frozen production artifacts from `5f3da7b`; all 374
native input hashes match `02c00bf` exactly. The intervening commits concern CI
and an asset-free native regression. Executable, archive, manifest and snapshot
hashes are checked before copying the reference into this task's evidence.

Using the updated reference matters: main independently changed bootstrap
command-line symbol spelling and Road initializer ownership. Those main changes
are not class-migration allowances. The strict comparison still rejects lost
identities, unexpected text, changed named storage and initialization changes.
`data/class_migration_september_main_text_additions.json` contains only the
previously reviewed class method/accessor/constructor additions; older reference
inventories remain retained unchanged by this integration.

The full tooling retry passes all 540 tests. The initial run's four failures
were the GCC/Clang, O0/O2 forms of the composed turn logging fixture: after the
direct class call, its extracted source omitted the canonical fatigue/AP
dependency. The fixture now compiles that actual method and observes the
immutable metadata-table accessor. Its slot type and map row are distinct, so
using the wrong receiver cannot accidentally satisfy the expected AP result.
All 799 hashed source, test, tool, data and CMake inputs remain unchanged across
the successful run. The initial failed output remains beside the retry.

Eleven source/metadata checks and the Markdown check in the actual Git worktree
pass. The unchanged header ratchet reports 23 numeric differences; the raw GCC
and Clang link ratchets report 453 and 705 differences respectively, with zero
crosscheck errors. The strict migration comparisons pass independently; they do
not turn those historical raw-ratchet failures into passes. Complete metrics
and logs are retained under `main-02c-integration/metadata/`.

Main also adds two native AP tests that attempted to write an immutable metadata
table. The coordinated test-only correction reads its existing base AP and
checks the fatigue thresholds against that value. The table and production
behavior remain unchanged. This correction occurred after the tooling retry.
Both native executables now compile from the exact committed source and both
new cases pass in default and strict modes on each compiler.

Main's temporary CI diagnostic commit used update mode for the header and link
ratchets. This integration restores check mode against the unchanged tracked
baselines. Current metrics are still uploaded, but as separate diagnostic JSON
files. The link diagnostic's update command explicitly targets that separate
file; it cannot reseed the authoritative baseline. Existing ratchet failures
remain failures, even when the stricter migration comparison passes.

The resumed source, fixture and metadata evidence is under
`artifacts/cpp-classes/20260919/`. Its relevant directories are integration-audit,
published-main-reference and main-02c-integration. Exact commands are recorded
by the scripts in that dated directory and the per-profile step receipts.

Commands from the repository root in WSL:

```sh
python3 artifacts/cpp-classes/20260913/generate-with-stable-mtimes.py
python3 artifacts/cpp-classes/20260919/build-integrated-main.py
python3 artifacts/cpp-classes/20260919/import-main-reference.py
python3 artifacts/cpp-classes/20260919/run-integrated-tooling.py
python3 artifacts/cpp-classes/20260919/run-integrated-tooling.py composed-ap-retry
python3 artifacts/cpp-classes/20260919/check-integrated-metadata.py
```

The import and build scripts expect fresh output destinations. Their retained
receipts, rather than rerunning over those destinations, identify completed
attempts. The strict surface command uses the current production binary/archive,
the imported per-compiler snapshot and the September text inventory above.

The original-backed 19-method runtime evidence is independently re-audited and
documented in [CPP_CLASS_FIRST_ROAD_REVALIDATION.md](CPP_CLASS_FIRST_ROAD_REVALIDATION.md).
It remains pinned to that earlier source. The integrated GCC production build
also passes the complete first-Road replay: turn 6, `(49,50)`, AP 2, empty path,
roads 867/879, all 310 selected-slot bytes and all 1,300 visibility bytes match
the retained original. Its actual endpoint frame is retained with unmasked
metrics; the original frame used for that comparison is historical, not a new
September 19 original capture. No visual-equivalence claim follows.

Both current compiler default smoke runs record 11 passes, two failures and eight skips.
The playability and attack probes both wait for selection of stack 1 at
`(31,44)`, while the accepted input selects stack 0 at `(30,44)`. Historical
reports retain the same failing expectation. A fresh identical-input run of the
exact `02c00bf` GCC reference now reproduces all 21 outcomes and the same accepted
click/selection marker sequence as both class builds. This bounds the result as
preserved behavior; the expected-selection contract remains unresolved. An earlier
artifact-driver path error is retained separately and is not a game result.
See `artifacts/cpp-classes/20260919/integrated-runtime/` for frozen inputs, exact
commands, raw archives, screenshots and the failure audit.

Clang also passes the complete first-Road replay and the same bounded byte
comparisons. The full GCC/Clang save payloads still differ: 458 bytes before Road
and 464 afterward. Those complete differences are retained separately; matching
the named endpoint fields does not establish whole-save equality.

The coordinated Ubuntu restart completed with a writable root filesystem.
Current native/coverage validation runs from an independent exact archive and
Git index of `33a5959820dfcb70902183d9c094221c547b05fc`, with a 5 GiB host-disk
reserve. The first private-index freeze failed because normal Git staging would
normalize historical CRLF blobs; that pre-build failure is retained. The retry
stores raw blobs and proves exact source-tree/index-tree equality before building.
The six completed routes for both compilers remain outstanding. Neither this
integration nor any first-Road endpoint establishes full migration, whole-game
equivalence or campaign completion.

The native registration inventory contains all 1,614 prior cases plus the two
AP cases, with no removals. Per-case outcomes are retained separately for each
compiler and mode:

| Compiler / mode | Passed | Assertions | Isolated crashes | Wrapper exit |
| --- | ---: | ---: | ---: | ---: |
| GCC 13 default | 1,092 | 0 | 524 | 0 |
| GCC 13 strict | 1,092 | 0 | 524 | 1 |
| Clang 18 default | 1,092 | 1 | 523 | 1 |
| Clang 18 strict | 1,092 | 1 | 523 | 1 |

GCC's 1,614 historical case outcomes and Clang's strict outcomes are unchanged
from the sealed `be837d1` baseline. Four Clang default cases change from crash
to pass; these are the same four identities that differed between the older
default and strict runs. They are retained as observed variation, not credited
as repaired behavior. Clang's assertion remains
`cov5_01_getallowedattrtoken.allowed_symbols`.
Clang's strict run also retains 223 parent-path profiler write errors, compared
with 220 in the prior strict baseline; the current default run has none. Default
and strict worker shards are archived separately, and coverage reads default
only. These I/O diagnostics are not asserted to diagnose a filesystem fault.

GCC coverage passes: 6,165 / 6,656 executable lines (92.6231971154%), all 718
functions covered and zero uncovered. Both covered and executable counts grow
by four relative to `be837d1`; the inventory and 89.7% floor are unchanged.
The initial reader could not create filenames exceeding the filesystem limit.
The retry uses archived, hash-verified notes and default shards without a
rebuild or another native execution. Only reader output-filename options change;
the Source headers still resolve to the actual canonical definitions. Clang's
compatible-reader retry measures 6,812 / 7,345 lines (92.7433628319%), with the
same 718 identities and eight uncovered CLIPS functions as its earlier baseline.
Its zero-uncovered gate therefore still fails. Executable lines grow by four
and covered lines by thirteen; nine of the latter are in `CRT_ToUpperInPlace`,
`CRT_TzYearStartsInDaylightTime` and `Rules_FirstFunction`, with unchanged
executable denominators. The four +1 executable/covered changes on both compilers
are `UnitSlot_CycleOrderState`, `UnitSlot_GetBaseActionPoints`,
`UnitSlot_HasSevereFatigue` and `UnitStack_CalcMilitaryStrength`.

GCC's filename adapter retains original arguments and adds `-x -s SOURCE_ROOT`.
LLVM's adapter retains all measurement inputs/options, adds `-x`, and omits only
the `-p`/`-l` output-filename formatting flags. The failed longer-name variants
remain recorded. Independent controls reproduce each entire sealed `be837d1`
coverage JSON exactly with these adapters. All 954 source hashes remain unchanged;
each successful current measurement records 192 reader calls and 2,176 emitted
Source headers. There are no zero-executable canonical methods. All failed
reader attempts and the first source-index freeze failure remain retained under
`artifacts/cpp-classes/20260919/runtime-native-preparation/`.

The supplementary six-route replay remains incomplete and pinned to the frozen
23-method binaries. Mission 13 passes on both compilers, with the first GCC
dark-frame failure retained separately from its unchanged passing repeat. The
exact-main control also passes. Concurrent live-window observations show that
stride-128 capture can leave the latest dumped frame stale; they do not prove
the precise cause of the earlier unobserved failure. Fresh nonblank human-turn
frames are retained, while the objective transition's actual black window and
older bright dump are reported separately.

Mission 00 fails on both compilers with the same selection-marker mismatch as
exact main. Mission 01's sparse initial black dump is reproduced on exact main
while a concurrent actual window is nonblank. Restoring capture cadence 1, with
unchanged route inputs, passes the initial and Stormus-exit checkpoints. Its
2 GiB RAM evidence guard then stops the run after 26.99 seconds of game activity;
this is a capacity stop, not a gameplay failure. All 1,751 raw members are
verified in the 176,949,336-byte archive. At the observed approximately 79.5 MB/s
raw rate, another blind 6 GiB attempt would be insufficient. Missions 02–04 and
Clang mission 01 remain unrun while transparent compression is assessed. No
route acceptance or campaign milestone is advanced by this partial matrix.

The detailed commands, attempts and capture investigation are in
`artifacts/cpp-classes/20260919/integrated-runtime/completed-routes/`. Lossless
cleanup recovered 1,095,121,878 bytes from 886 current and historical loose
BMP/log duplicates only after archive/member size and SHA verification. Existing
archives retain all raw bytes; screenshots, saves, binaries, source freezes and
reports stay available. Exact removal mappings are retained in that directory.

A read-only preflight of the next AP-spending family found additional inherited
boundary debt. On `INT_MIN` amounts, Clang diagnoses signed subtraction overflow
in both the clamped and floor-zero routines; GCC reaches an existing unaligned
sentinel load instead. Both compilers diagnose the unchecked routine's signed
slot-address overflow on a valid mapped record straddling `INT_MAX`. All twelve
individual build/run outcomes and exact canonical-body hashes are retained in
`artifacts/cpp-classes/20260919/ap-spending-boundary-audit/`. These three functions
remain unchanged. Their distinct AP algorithms require separate original-backed
arithmetic repairs before extraction; the migration does not narrow their public
input domains to hide the findings.

## Header parameter declaration correction

The integrated selection check reproduced a separate inherited policy error:
`UnitStack_NormalizePeasantCargo(DWORD a2, double a3)` declares a parameter named
`a2`, while the recovered declaration database also contains `extern char a2[3]`.
The token-only dependency check mistook the parameter declaration for use of that
global. The audit now masks only proven ordinary parameter declaration tokens.
The recovered parameter name stays unchanged. Default expressions, array bounds,
type tokens, qualified global references, other scopes and inline behavior remain
checked; ambiguous complex declarators remain conservative.

All 32 focused header-policy tests pass, including seven new regression methods.
The unchanged checker reproduces eight failing positive scenarios and the exact
production `a2` finding. The corrected current checker reports no class-header
policy error. Its overall check still fails on the same 23 numeric ratchet rows;
all rows are compared explicitly, and no baseline changes. The preparation and
integrated logs are retained under `artifacts/cpp-classes/20260919/` in
`header-policy-shadowing/` and `header-policy-integration/`. This tooling change
does not modify any canonical implementation, storage or runtime behavior.
