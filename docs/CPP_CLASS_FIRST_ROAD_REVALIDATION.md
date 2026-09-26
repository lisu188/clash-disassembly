# Nineteen-method first-Road revalidation

Track: Win95 reconstruction; frontier: runtime regression evidence for the
behavior-class migration. This report is pinned to `366278b` (19 methods,
146 recovered TUs). It does not validate later AP or stack-query changes.
Both uninstrumented production binaries pass the full mission-05 first-Road
probe on their first attempts in this series.

Each reconstruction uses Xvfb, dummy audio, a private native Linux game/cwd/tmp
directory and the canonical route's unchanged 0.18-second clicks and 0.005-second
pan hold. Frame retention uses stride 128. The native-directory environment is
recorded explicitly; it differs from the earlier Windows-backed failed Clang
attempts. All 920 frozen source hashes and both binary hashes remain unchanged.
Raw logs, saves and frames were archived, copied to workspace and hash-verified
before each owned native temporary directory was removed.

The route reaches turn 6 at `(50,50)` with 6 AP, performs the actual Building
to Road action and finishes at `(49,50)` with 2 AP and an empty path. Before
and after the action, both compiler runs match the fresh original in all 310
unit-slot bytes, all 1,300 visibility bytes and all six probed Road words.
The resulting Road overlays are 867/879 and 228 visibility tiles are set.
The other 499 stacks, all 100 buildings and money remain unchanged across the
reconstruction's Road action.

The original runs headlessly under Wine from an unchanged executable and a
private prefix. Its real Load menu reads the unchanged engine-authored turn-6
DAT/FAC checkpoint. Three separate attempts remain retained:

1. The first Load click left the main menu visible; the state guard rejected
   mission 0/turn 0. It is a failed capture, not matching-state evidence.
2. The second attempt loaded the correct checkpoint, but the fixed capture
   delay caught the Road transition: header `(50,50)` with 3 AP while occupancy
   had already changed. The endpoint guard rejected it.
3. The final attempt used the same gameplay actions and added only read-only
   endpoint polling before capture. It reached the complete turn-6 endpoint.

The fresh original executable SHA-256 is
`500055d77d03d514e8d3168506bd10f67cd8569bcc450604ff8192f46cdaf3ae`.
The final original frame SHA-256 is
`ff60ee32cbb5f981f53bb454a1eefd8545cd6c12dd118a6b71f92d82b2669284`.
All three original attempts preserve executable, checkpoint and template hashes.
No save bytes or gameplay state were edited to obtain the endpoint. Continuous
original turn-1 replay remains outside this real-Load comparison.

The fresh pairs align viewport `(47,48)`, cursor `(192,176)` and the endpoint
state. Pixel metrics are over complete 640 by 480 images, without masks,
cropping or resizing:

| Reconstruction | Different pixels | Percentage | Mean absolute RGB-channel difference |
| --- | ---: | ---: | ---: |
| GCC 13 | 287,443 | 93.5686849% | 11.2428038 |
| Clang 18 | 286,557 | 93.2802734% | 11.2657378 |

These frames do not establish visual equivalence. The original's coordinate
labels, unit panel, sprite presentation and reconstructed text/HUD differences
remain visible. No pixels are waived as acceptable by this report. Whole stack
and game payload differences are also enumerated: the selected stack differs
in its four-byte trailing instance handle; the complete game payload differs
by 704/699 bytes before and 1,062 bytes after the action for GCC/Clang against
this fresh original. Matching selected fields are not a whole-payload claim.

Cross-run GCC comparisons against the earlier `be837d1` checkpoint retain
429/428 differing payload bytes before/after, although the selected stack's
725 bytes match. Source writers show that RNG consumes wall-clock input and
population/port updates consume that RNG. This is a supported variability
path, not proof of the cause of every individual byte difference. All offsets
remain available for later recovery.

Durable evidence, exact commands, source/binary freezes, raw archives, state
markers, pair images and full byte/pixel metrics are under
`artifacts/cpp-classes/20260913/runtime-19-methods/`. The entry points are
run.py, fresh-original.py, verify.py and compare-fresh.py in that directory.
The comparison receipts retain exact attempted commands and temporary-path
provenance. The earlier failed Clang runs and input-wait investigation remain
separate in `runtime-before-units/` and `input-wait-audit/` under the same dated
artifact root. Passing this series does not erase them.

The six completed direct-route gates, whole-game equivalence, mission-05
completion and automatic campaign advancement are not promoted by this probe.
Later class batches require their own relevant validation.

## September 26: 33-method checkpoint

The fresh replay pins `9a74d4c9b486e15495d5a48fea7b3dd81f46eb5d`, with
33 canonical methods in six class sources and 147 recovered translation units.
Fresh GCC 13 and Clang 18 production builds, warning checks and all eight
asset-free gates pass. Their source audits complete within the unchanged
timeout; the earlier timeouts remain recorded separately. All 859 frozen inputs
remain unchanged throughout the builds and runtime runs.

Both production executables pass the canonical mission-05 first-Road route in
headless WSL, using private native game/save/cwd directories, dummy audio,
unchanged route inputs and frame stride 32. They reach turn 6, `(49,50)`, 2 AP,
an empty path and roads 867/879. Before and after the Road action, comparison
against the fresh original passes all 310 slot bytes, all 1,300 visibility bytes
and all six Road words. The endpoint visibility has 228 set tiles and SHA256
`6a3c5de203b5c40db4ab8c442f3a65017cd0eee2fb9971d727148d012a7fd4b0`.
Both transitions preserve the other 499 stack records, all 100 building records
and their money entries. These checks do not establish whole-game-byte equality.

The first fresh original attempt fails when its read-only observer cannot open
`/proc/PID/mem`; the wrapper's zero exit does not override `workflow_pass=false`.
The separate root-context retry uses a new private Wine prefix with matching
ownership and succeeds without changing global ptrace policy. It performs real
Load of the unchanged engine-authored turn-6 DAT/FAC checkpoint and the actual
Road action. Executable, checkpoint and prefix-template hashes remain unchanged.
This is not continuous original turn-1 replay. The failed attempt's raw capture,
log and verified archive remain; its temporary prefix was later observed absent
despite the wrapper recording no removal, with no cause established.

Both pairs align viewport `(47,48)`, cursor `(192,176)`, selected stack 4 and the
verified endpoint. Complete 640-by-480 frames give these unmasked metrics:

| Reconstruction | Different pixels | Percentage | Mean absolute RGB-channel difference |
| --- | ---: | ---: | ---: |
| GCC 13 | 286,486 | 93.25716146% | 11.15446181 |
| Clang 18 | 287,316 | 93.52734375% | 11.28456272 |

No resizing, cropping, masking or acceptable-difference waiver is applied.
Original tile-coordinate labels, upper-right fog differences and the original
unit portraits versus overlapping reconstruction text remain visible. Visual
equivalence is not established. Whole-game payload differences against the
original remain 684/1,048 bytes before/after for GCC and 698/1,057 for Clang.
The two reconstruction payloads differ by 322/325 bytes before/after. All offsets
and values are retained without normalizing unknown bytes or attributing every
difference to RNG.

Evidence is retained under `artifacts/cpp-classes/20260926/local-current33/`
and `artifacts/cpp-classes/20260926/runtime-current33/`. The former contains the
859-input freeze, build receipts and exact binary hashes; the latter contains
per-attempt commands, unchanged orchestration scripts, raw archives, observed
saves, endpoint verification and comparison-fresh-original.json for each
compiler. The fresh original frame SHA256 is
`88adfa9c1d135ac59ae8d6733e833103990ce72ceda2832b273a9763e29ed783`.
The retained scripts reject reuse of completed output directories. Their actual
entry points, run sequentially with the recorded working directories, were:

```sh
python3 -B artifacts/cpp-classes/20260926/local-current33/run-validation.py
python3 -B artifacts/cpp-classes/20260926/runtime-current33/run-first-road.py gcc13
python3 -B artifacts/cpp-classes/20260926/runtime-current33/run-first-road.py clang18
python3 -B artifacts/cpp-classes/20260926/runtime-current33/fresh-original.py \
  --attempt fresh-original-endpoint-root --guard-load-menu --wait-road-endpoint
```

The final command runs in the recorded root process context, headlessly; each
verify.py invocation pins the successful fresh-original directory explicitly.
The 90%-usage threshold, additional 2-GiB reserve and 3-GiB per-runtime budget
remain enforced. No runtime guard fires. Original failure diagnostics remain
distinct from the successful retry. The default smoke suite, six completed
direct-route gates, unresolved native/coverage failures and broader migration
acceptance remain outstanding; no campaign milestone is promoted.
