# Class migration: origin refresh, 2026-09-08

Track: Win95 reconstruction; frontier: integrate current recovery work into the
ongoing behavior-class migration. This is an integration checkpoint, not migration
completion. There are 11 canonical methods in four class-named sources and 144
manifest-ordered recovered translation units. All 4,157 historical identities
remain: 1,849 intended game methods, 22 retained boundaries/utilities and 2,286
excluded implementations across 116 intended owners. Five address-free boundary
helpers are inventoried separately.

The incoming reference is `e13abc0266707de6291be39fdea28dca4f3e7e2b`; the migration
parent is `505869e5449eb49246c6d02d4daa29a3459d794d`. The later remote tip
`1b8b4b8e25558a5b0494c2889f11a1368b65eeef` was observed while validation ran and is
not represented by this checkpoint's frozen binaries. Original/main was refreshed
independently; no force update, discarded worktree or reset of existing changes
was needed.

## Reconciled source and provenance

Incoming numeric naming, assembly-backed Road/CLIPS repairs, byte-view helpers
and native runner changes are retained. Three already migrated methods receive
the corresponding upstream named constants; their class implementations remain
canonical. Original function names, signatures, storage anchors and the separately
validated sine and unused logging-context repairs remain intact.

The upstream rename at `0x00404A40` is canonical `Render_SetResourceHandle`.
`Surface_SwapDirtyTrackingFlag` remains an explicitly registered historical alias
with its exact ABI and a single forwarding body. The removed duplicate support
implementation stays removed. The manifest records original-name history and
separate alias source/body hashes. Alias validation checks metadata, declarations,
argument order, ABI types and signedness, the exact forwarding body and unique
canonical target. An alias is neither a recovered implementation nor another
coverage identity.

The scoped hash updater and readability runner now resolve class methods,
adapters and historical aliases together. They retain schema 3, reject unselected
body drift and validate all proposed writes first. Unsupported class-backed
identity renames fail before mutation. The source audit and class catalog invoke
the same alias checks. Disposition synchronization uses canonical declarations
when validating bindings and preserves alias history.

The initial merge reconstruction omitted eight leading linker-retention
attributes because they fall outside the indexed definition body. The strict
linked-symbol comparison caught the resulting missing ready-unit export. All
eight exact annotations were restored; the failing attempt remains evidence.

## Validation and retained failures

Both clean production builds pass. GCC 13 reports 6,582 warnings and Clang 18
reports 6,591, within unchanged ratchets. After restoring the annotations, both
strict migration comparisons and all eight asset-free gates pass. The comparisons
use the exact incoming reference and enumerate only the 11 methods, borrowing
constructors/factory and historical alias as permitted text additions. Storage,
initialization, identity and ordering checks have no allowances.

The existing header baseline remains frozen. Incoming baseline increases are
retained as an explicit comparison artifact, not adopted to make checks pass.
The exact-origin raw link ratchets still report 428 GCC and 680 Clang differences;
the header ratchet still reports 14. These historical failures are not hidden by
the stronger migration-specific comparisons.

Actual-method differential tests pass for the unit queries, queued paths, world
geometry and unit turns. The separate sine and logging-context recovery tests
also pass. The first full tooling run reports 472 passes and one error out of
473 tests: the disposition-sync fixture omitted canonical declarations required
by the new binding validation. The API, CLI and fixture now provide them; the
four relevant integration tests pass on retry. The initial result remains saved.
The alias validator has 29 passing tests and the combined migration-runner suite
has 37 passing tests, including actual class and ABI compilation.
After integrating the exact support inventory into the source audit, the full
suite passes all 503 tests. The inventory separately assigns 459 support
definitions: 154 planned runtime methods and 305 retained utilities/boundaries.

Full native testing uses a separately frozen 847-file working-merge snapshot.
Native outcomes, including crashes, are compared by case identity with an exact
779-file upstream snapshot. Coverage retains the same 718 identities, 89.7% floor
and zero-uncovered requirement. The merged GCC measurement is 6,161/6,652
(92.62%), compared with upstream 6,160/6,651: one covered receiver-binding line
was added. Counts alone do not waive individual outcome changes.

The merged GCC default native run matches every upstream case: 1,087 passes,
zero assertion failures and 527 crashes. Its strict run reports one additional
crash in the diagnostic full-world trace case. Nine isolated repetitions per
binary all pass and produce identical 596,607-byte logs. With an intentionally
slow stderr reader, both unchanged binaries instead receive SIGALRM while blocked
in the same `fprintf` write and report a crash. The runner uses a one-second
alarm. This establishes watchdog sensitivity; the signal from the earlier
untraced full-suite observation remains unknown. No timeout or runner was changed.

Merged Clang reports 1,087/1/526 (pass/assertion/crash) in default mode and
1,086/1/527 in strict mode. Every case outcome was already observed in the four
unchanged upstream Clang runs. All per-run outcomes and 54 upstream variable
cases remain visible; matching one observed variant is not a parity waiver.

Runtime evidence is tied to its copied binary hash, not a moving worktree. Fresh
replays use private save/config directories and headless Xvfb. The periodic frame
stride is explicitly changed from 32 to 128 in a separate capture-only fixture;
route actions and explicit checkpoints are unchanged. Prior eight-method runtime
evidence is retained without attributing it to this eleven-method build.

## Commands and durable evidence

From the migration worktree root in WSL:

```sh
python3 artifacts/cpp-classes/20260906/pilot/validate-stage.py refresh-retained \
  --reference-dir artifacts/cpp-classes/20260908/origin-reference \
  --evidence-dir artifacts/cpp-classes/20260908/refresh \
  --allowances data/class_migration_origin_text_additions.json
python3 -m unittest discover -s tests/tools
python3 -m unittest discover -s tests/tools -p test_class_manifest_integration.py
python3 tools/sync_game_class_manifest.py
python3 tools/update_split_manifest_hashes.py
python3 tools/game_class_catalog.py
python3 tools/audit_split_sources.py
python3 artifacts/cpp-classes/20260908/refreshed-runtime/run.py gcc13 first-road
```

The dated local evidence root is `artifacts/cpp-classes/20260908/`:

- `refresh/`: integration inventory, exact commands, first failures, retries,
  method differentials, hashes, compiler warnings and strict comparisons.
- `origin-reference/`: frozen source, both production profiles and all gates.
- `origin-reference-native/`: full upstream per-case results, coverage and
  repeated Clang observations. Its source-unmodified Clang launcher strips only
  unsupported `-fprofile-abs-path`; the original build failure remains recorded.
- `refreshed-native/`: before/archive/after source hashes and merged native runs.
- `refreshed-runtime/`: copied production binaries, private runtime roots,
  unaltered saves, checkpoint frames, capture setting, archive hashes and logs.

This batch does not resolve all family readiness contracts, visual defects,
mission-05 continuation or campaign progression. Class assignment and byte-view
helpers are not counted as canonical behavior migration.
