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
