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
behavior remain unchanged. This correction occurred after the tooling retry;
the native executable and both new cases still require validation on the
committed integrated source.

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

The current GCC default smoke records 11 passes, two failures and eight skips.
The playability and attack probes both wait for selection of stack 1 at
`(31,44)`, while the accepted input selects stack 0 at `(30,44)`. Historical
reports retain the same failing expectation, but an identical-input run of the
exact main reference is still needed before attributing this outcome. An earlier
artifact-driver path error is retained separately and is not a game result.
See `artifacts/cpp-classes/20260919/integrated-runtime/` for frozen inputs, exact
commands, raw archives, screenshots and the failure audit.

Clang runtime, the six completed routes for both compilers and current native
coverage remain outstanding at this checkpoint. Work is paused at the coordinated
Ubuntu restart boundary; the prepared native runner requires an exact committed
revision and a 5 GiB host-disk reserve. Neither this integration nor any first-Road
endpoint establishes full migration, whole-game equivalence or campaign completion.
