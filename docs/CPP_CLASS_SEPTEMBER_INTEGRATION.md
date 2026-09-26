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

## September 26 origin and hosted validation review

Track: Win95 reconstruction, validating the 33-method class checkpoint.
`e896279` integrates origin `44928710be14842127d9c581e2e67dfff2d65e09`,
including the selected-slot predicate, strategic-AI projection repair, DLX
extent names and the explicitly unvalidated Mission 05 bridge-probe draft.
Only the status prepend conflicts; all incoming and class entries are retained.
The class-header parameter checker correction remains, alongside origin's
declaration-only parameter rename. The main checkout's unrelated working changes
are preserved.

Read-only integrated audits pass: 4,157 canonical identities, 33 adapters, 147
TUs, the unchanged 718-function selection, all canonical hashes, and the DAT
contract (16-byte label, 586,398-byte payload, 586,414-byte file). The nine
workflow tests, three Markdown tests and five slot-override tests pass in WSL,
including all thirteen strategic activation witnesses. These small checks do
not substitute for integrated builds or runtime evidence.

The earlier exact relocated class head `e188e2c` has a completed
[hosted run](https://github.com/lisu188/clash-disassembly/actions/runs/35970985364):

- Both supported production builds, warning checks, all eight asset-free gates
  and both 12-test runner-policy suites pass.
- The complete tooling run executes 560 tests with three workflow-condition
  failures. They match the exact incoming `c9c0fa7`
  [comparison run](https://github.com/lisu188/clash-disassembly/actions/runs/35965496476).
  Origin's later AI validation commit corrects their prerequisite assertions;
  the actual CLIPS prerequisites remain in the workflow.
- The hosted GameRandom fixture passes. The interrupted local run's FAIL marker
  has no retained traceback, so its cause remains unresolved. All three pinned
  reference-file hashes match; a hosted pass does not erase the local failure.
- GCC coverage passes at 6,168 / 6,659 executable lines (92.63%), with all 718
  functions reached and zero uncovered. The exact hosted comparator measures
  6,168 / 6,656: executable lines increase by three, covered lines have no net
  increase, and fully covered functions change from 585 to 584. The three
  prepared receiver-binding additions explain the expected denominator change,
  but summary-only CI output cannot establish the integrated per-function
  change or explain the unchanged numerator. These are not the older local
  6,165 / 6,656 measurements.
- The historical raw link gates remain failed: GCC differences change from
  453 to 463 and Clang from 705 to 715, with zero cross-check errors. GCC's
  visible additions are exactly the ten expected methods. The Clang diagnostic
  list is truncated before those names, so those logs alone do not establish
  the complete symbol comparison.

The original remote jobs retained only pre-execution compiler logs for native
coverage. They did not retain all 718 coverage rows or individual native
outcomes. A new detailed run can compare current inputs, but cannot reconstruct
the lost details of those historical runs. The review and artifact inventories
are retained under `artifacts/cpp-classes/20260926/ci-review/`; the comparison
receipt SHA256 is
`3d8396daba96c927bfbe553bee229c32febf9acf48515cb1e8e7e83515188be2`.

### Detailed integrated candidate and current-main reference

The later checkpoint `212bb559c322634f8e69ab0ae664440d24bf8df7`
integrates origin `26f5f35`, including the independently validated player-info
sprite loader repair. No class identity is added by that incoming repair.
[Candidate run 36263284415](https://github.com/lisu188/clash-disassembly/actions/runs/36263284415)
checks out PR merge `ae962e6cb74c30bc7f9871c424a195737474d6f0`, whose tree
is byte-identical to the candidate head. The source comparison pins tree
`18f7074899bc21388200694b67edb948efe7b700` and both merge parents.

[Reference run 36263644099](https://github.com/lisu188/clash-disassembly/actions/runs/36263644099)
uses `2c93086d32354b698fdcf3aace285aba135d1227`: current main `26f5f35`
plus the same nine diagnostic files as the candidate. Its production sources,
data, CMake inputs and native fixtures are unchanged from main. The exact
source proof is retained under
`artifacts/cpp-classes/20260926/native-reference/source-comparison.json`.

Both runs pass both production builds, warnings, all eight asset-free gates and
both runner-policy suites. Candidate tooling passes all 597 tests; current
header, activation and Markdown checks also pass. Reference tooling passes
585 tests; its three inherited mission-05 Markdown links still fail. Historical
raw link-surface failures remain in both runs; those ratchets are not reseeded.

Every ordered native registration and selected coverage identity matches:

| Compiler | Reference pass/fail/crash | Candidate pass/fail/crash | Reference covered/executable | Candidate covered/executable |
| --- | --- | --- | --- | --- |
| GCC 13 | 1100/0/516 | 1100/0/516 | 6165/6656 | 6170/6659 |
| Clang 18 | 1099/1/516 | 1101/1/514 | 6811/7345 | 6814/7348 |

GCC outcomes are identical for all 1,616 cases. Clang changes three cases from
CRASH to PASS: `cov12_crt.to_upper_in_place_nonempty`,
`cov2_08_tzdaylight.a1_flag_set_jumps_to_shared_tail`, and
`cov4_03_crt.tz_year_starts_in_daylight_goto_label6`. It also changes
`cov3_07_definstances.delete_record_not_bloaded_retry_for_luck` from **PASS to
CRASH**. That fixture and production body are byte-identical between reference
and candidate and exercise uninitialized recovered locals. This establishes
susceptibility, not the precise cause; the observed regression remains open.
Separate hosted runs do not establish identical address layout or scheduling.

Clang retains `cov5_01_getallowedattrtoken.allowed_symbols` at expected 2,
actual -1, and the same eight zero-covered functions. Both profiles exceed the
unchanged 89.7% floor and retain all 718 nonempty coverage rows, but Clang fails
the zero-uncovered requirement. GCC passes that requirement. Individual crashes
remain visible even where the native runner's existing policy permits them.

Both executable denominators increase by exactly three: one covered receiver
binding in each of `UnitSlot_InitFromType`,
`UnitStack_SubtractActionPointsFloorZero`, and
`UnitStack_HasSpecialPersonageUnits`. The remaining GCC covered delta is +2 in
`Building_UpdatePlagueState`. Other Clang covered deltas are +3 in
`CRT_ToUpperInPlace`, -1 in `Defgeneric_ClearDefgenericsReady`, and -2 in
`Definstances_DeleteRecord`. These observations do not explain the lost detail
from the older summary-only runs or resolve the interrupted local RNG failure.
The complete comparison is retained in
`artifacts/cpp-classes/20260926/ci-review/reference2c93086d/hosted-reference-comparison.json`.

### Native log framing correction

The candidate Clang collector originally failed on one complete CRASH record
joined to a concurrent diagnostic; reference GCC failed on two such records.
The actual logs and failed receipts remain unchanged. The collector now accepts
at most one complete exception suffix using the existing registered-name,
ordering and exact-total checks. It preserves the full joined line and prefix
as unattributed diagnostics. Ambiguous markers, malformed or foreign records,
duplicates, late exceptions and inconsistent totals still fail collection.
Plain-text log framing cannot independently authenticate a status-shaped string;
no signal, missing outcome or diagnostic-prefix ownership is inferred.

All 19 focused Python tests pass in WSL on the final files:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/dev/shm python3 -m unittest discover -s tests/tools -p test_native_test_evidence.py -v
git diff --check -- tools/collect_native_test_evidence.py tests/tools/test_native_test_evidence.py
```

The final review receipt is
`artifacts/cpp-classes/20260926/ci-review/collector-final-review.json`.
Offline reconciliations on the retained candidate Clang and reference GCC logs
recover complete 1101/1/514 and 1100/0/516 counts respectively. They pin their
original evidence and tool hashes but do not rerun native tests or assert fresh
hosted binary/HEAD verification. Exact hosted validation of the final parser
remained pending at that checkpoint. Collection success is not native-suite
success.

### Exact hosted validation of the collector correction

[Run 36266431294](https://github.com/lisu188/clash-disassembly/actions/runs/36266431294)
validates head `12ff25bc1a62d4036850f4db53f016d849234fea` through merge
`66bbded1499acbe4318f218aee05cac6c6fa1971`, with an identical tree. The
hosted tool hash matches the final focused-test receipt. Both collectors
successfully retain all 1,616 outcomes and exercise actual joined records:
GCC `cov2_08_crtexcfilter.cold_call`, and Clang
`cov21_messagehandler.register_system_handlers`. Their prefixes remain
unattributed; the earlier failed receipts are not replaced.

Both production builds, warning checks, all eight asset-free gates and both
runner-policy suites pass. All 600 tooling tests pass in 277.493 seconds;
Markdown, current header and strategic activation checks also pass. GCC retains
exactly 1100/0/516 native outcomes and 6170/6659 coverage. Clang records
1100/1/515; all 718 coverage rows are identical to the earlier candidate,
including 6814/7348 covered/executable lines and eight uncovered functions.

`cov20_crt.tz_year_starts_label6_a1_flag_set` changes from PASS to CRASH against
both the earlier candidate and current-main reference. The earlier
Definstances PASS-to-CRASH observation also persists against the reference.
No production or native fixture files changed from `212bb55`. This establishes
an outcome variation with unchanged source, not its precise cause or a resolved
regression. The Clang assertion, zero-uncovered gate and both historical raw
link checks still fail. The draft is not ready for migration acceptance.

Logs, exact checkout/tool identities, original collection receipts, all native
rows and coverage comparisons are retained under
`artifacts/cpp-classes/20260926/ci-review/integrated12ff25b/`. This follow-up
changes validation tooling and documentation only; it adds no class method,
runtime or campaign milestone.

### Native variation evidence boundary

A later read-only audit finds the same native executable SHA256,
`78556a4c5825fee1599671f285df6ac80115642c68dc6c0ccef164867da367e2`, in
the hosted capture receipts for both candidate runs above. The timezone case
passes in the first and crashes in the second, establishing an outcome variation
without a change to those executable bytes. The executables were not downloaded
and rehashed locally; the capture receipts and preserved collector outcomes are
the evidence. This does not resolve the candidate-versus-main comparison.

Both target fixtures discard the function result rather than asserting behavior.
The relevant procedural source, fixtures and runner are identical to the
reference, and original assembly confirms missing register dataflow in both
recoveries. However, the runner's CRASH outcome conflates caught faults, its
one-second alarm, abnormal exits and possible coverage-dump failures. It retains
no signal or faulting instruction. No precise cause is established and neither
unfavorable observation is waived. Exact receipt hashes, raw lines, source blob
comparisons and the bounded diagnostic plan remain under
`artifacts/cpp-classes/20260926/native-variation-audit/`.

### Incoming header baseline change

Origin commit `6ad7f2d` independently reseeds the header baseline and documents
its dependency reasons. The five API additions match the tracked old/current
sets; eighteen peer-edge rows increase, one decreases, and shared globals stay
244. Integrating that published history does not repair the earlier 23 numeric
failures: they become acceptable because the thresholds change. Retain the
earlier frozen baseline and raw failure records for migration comparison;
a pass against origin's new baseline is not class-behavior validation. The
incoming record does not retain the complete old/current preprocessed member
sets claimed in its narrative. No class batch reseeds the link, warning or
coverage baselines.

### Resource and runtime limits

The user-required disk threshold is now less than 90% used on both the output
filesystem and the Windows volume backing WSL, in addition to existing reserves.
The initial host-capacity hold is retained in the earlier receipts. A later
September 26 check observes 88.555% used and 114.4 GB free, allowing bounded
local work to resume without weakening any guard. Fresh sequential GCC/Clang
builds, warnings and all eight asset-free gates pass at `9a74d4c`; all 859 frozen
inputs remain unchanged. The earlier audit timeouts remain distinct outcomes.
The subsequent original-paired first-Road replays also pass their bounded state
checks, with full payload and unmasked frame differences explicitly retained.
See [the fresh checkpoint report](CPP_CLASS_FIRST_ROAD_REVALIDATION.md#september-26-33-method-checkpoint).
No installed tool or runtime asset is removed to obtain room.
Verified cache cleanup and archive-member restoration maps are retained under
`artifacts/cpp-classes/20260926/disk-cleanup/`.

The full migration and full C++ reimplementation remain incomplete. GCC native
outcomes now match the current-main reference; Clang differences and failures
remain unresolved. The first-Road comparison is now refreshed for the 33-method
checkpoint. The default smoke suite, six completed-route regressions and later
class-batch acceptance remain required. No campaign or visual-fidelity milestone
advances.
