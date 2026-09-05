# Astra repository readiness — 2026-09-05

Track: Win95 reconstruction, repository and toolchain readiness. Starting HEAD:
`47b1aab`. The setup and conflict repair are complete; full readiness is **not
yet established**. The initial audit preserved existing gameplay and canonical
metadata; the declaration-only continuation is recorded below.
Campaign-route validation remains a separate track with 6/20 complete direct
routes, unproven Campaign-menu entry, and unproven automatic advancement.

Subsequent structure-recovery validation is recorded in [STATUS.md](STATUS.md).
It restores generated-header freshness, validates the metadata with GCC/Clang
and unit coverage, and resolves original Wine startup/display issues for fresh
headless menu capture. The earlier blocked attempts below remain historical;
warning, header-surface and linked-layout ratchets still require review.

## Changes and preservation

- Added tracked `.codex/config.toml` selecting `gpt-6-astra`. Reasoning effort,
  authentication, and permissions remain user settings. The installed Codex
  CLI accepted the configuration and loaded the repository instructions.
- Backed up the index, Git config, working/index patches, affected files, and
  stash/worktree references before repairing the failed autostash reapplication.
  All 77 conflicts had stage 3 equal to stage 1 after CRLF/LF normalization,
  and stage 2 equal to HEAD. Resolved them to stage 2 and removed 58 verified
  staged changes containing only line-ending differences.
- Set repository-local `core.autocrlf=false` and added explicit LF policies for
  source/configuration/documentation. `text=auto` preserves historical CRLF
  blobs without a mass renormalization; assembly/map reference dumps stay `-text`.
- Verified all four mission-11 work-file hashes and every stash/worktree
  reference are unchanged. No stash was dropped, worktree pruned, commit made,
  or push performed. Mission-11 route scripts pass command/arity/conditional
  checks, and their env files pass shell syntax checks; their status is partial.
- Updated agent onboarding, build/test instructions, live source counts, route
  directory references, and broken documentation references. The legacy agent
  snapshot is explicitly historical, with its original contents preserved.
- Repaired stale unit-test callers of already recovered explicit parameters;
  no production function, global, table, type, or field was renamed or recovered.

These private local artifacts are absent from clean checkouts. The backup is
under `artifacts/astra-readiness/before/`, and the exact recovery script is
artifacts/astra-readiness/recover_checkout.py. Preservation proof is in
artifacts/astra-readiness/preservation.json; Codex validation is in
artifacts/astra-readiness/codex-config-check.json.

## Validation results

All commands below run from the repository root inside Ubuntu WSL, using CMake
3.28.3, GCC 13, Clang 18, SDL2 2.30.0, X11 1.8.7, and Python 3.12.3. Complete
logs and command runners are retained under `artifacts/astra-readiness/`.

| Gate | Result and evidence |
| --- | --- |
| Git preservation | PASS: zero unmerged entries/conflict markers; original mission-11 hashes, stashes and worktrees retained. |
| Source manifest | PASS: 140 translation units, 4,157 functions, 4,007 ordered address markers. |
| Python, JSON, frozen pure metadata, save contract, constant guard, Markdown, shell syntax, whitespace | PASS; individual command logs under `artifacts/astra-readiness/static/`. |
| GCC and Clang compile/link | PASS: both fresh builds produce the recovered archive, bootstrap, trace tests and split-audit target. |
| Asset-free CTest | PASS: all four explicit CI tests on each compiler. |
| Unit suite and coverage | PASS: unit suite completed in 178.49 seconds; 6,137/6,645 executable lines (92.36%), all 718 frozen functions exercised, zero uncovered. Existing 89.7% floor unchanged. |
| Warning ratchets | FAIL: GCC 9,437 total and Clang 9,482 total; six categories increase in each profile despite lower totals. Existing saved baselines remain 9,763 and 9,809. |
| Header freshness/coupling | FAIL: declaration data and generated headers disagree; regenerated usage exposes pre-existing API/peer-edge increases. Unsafe regeneration was reverted. |
| Linked symbols/data | FAIL: 149 GCC differences, 55 Clang differences, zero archive/binary crosscheck errors. Existing baselines predate recovered symbol/layout changes. |
| Default local CTest | 11 passed, 8 opt-in probes skipped, 2 failed. Both failures expect the first next-unit click to select stack 1 at (31,44); the observed runtime selects stack 0 at (30,44). |
| Main-menu exit | PASS with an inspected, nonblank settled presented frame. |
| Mission 13 | PASS twice through the canonical direct route; one completion marker at turn 11 in each replay. No route promotion. |
| Fresh original frame comparison | BLOCKED: both Wine configurations fault before a game window appears. No same-state pixel comparison or fidelity claim is possible. |

Coverage initially could not compile because tests still omitted the recovered
fact-index and argument-count parameters. The repaired callers and valid
fixtures now compile and pass. Final evidence is in
`artifacts/astra-readiness/coverage/compiler-callers.log`,
`artifacts/astra-readiness/coverage/unit-tests.log`, and
`artifacts/astra-readiness/coverage/measurement.log`. Earlier failing compiler
logs are retained as history; the passing measurement preserves the frozen
89.7% / 718-function / zero-uncovered requirements.

Exact build and test drivers:

```sh
bash artifacts/astra-readiness/build_profile.sh gcc
bash artifacts/astra-readiness/build_profile.sh clang
bash artifacts/astra-readiness/remaining_gates.sh
bash artifacts/astra-readiness/coverage.sh
python3 artifacts/astra-readiness/validate_static.py
python3 artifacts/astra-readiness/check_preservation.py
```

The build-profile driver intentionally exits at the failed warning gate.
The remaining-gates driver records subsequent link-surface, asset-free and
default-CTest exit codes independently; consult each result rather than the
driver's final shell exit code.

## Runtime evidence and limits

All reconstruction runtime runs use GCC binary SHA256
`694e8aaca0391127ea59f6eabe69fbd47470d90ba67ab0912d3f5edb2f7577e4`.
The settled menu frame has 296,141 nonblack pixels and 186 colors. Mission 13's
second replay uses observer-only stride 30 / limit 256 to avoid the default
frame cap exhausting early; it retains 62 frames, 61 changed pairs, five
distinct checkpoints, and a fresh late-route frame with 301,085 nonblack pixels.

Both fresh original Wine runs exit 5 at `004EA00F`, writing `E107100E`, before
rendering. Captures are uniformly black. The executable hash matches the
installed original, and the isolated 32-bit prefix has a CD-ROM drive mapping.
Default and builtin DirectDraw give the same fault. This is a blocker, not an
accepted visual difference. Comparison metrics remain null; historical original
captures have not been substituted for the required fresh pair.

Exact commands, both original failures, input/state markers, hashes, and frame
paths are in the private local report at
artifacts/astra-readiness/runtime/README.md. The original prefix
copy, session files, retail assets and captures remain ignored and unpublished.
No binary or image viewer was launched on the host desktop.

## Deferred work and approval boundary

The declaration comparison identifies 31 mismatched records and two existing
helpers absent from metadata. The review-only proposal and dedicated backup
are private local outputs at artifacts/astra-readiness/declaration-sync.json,
artifacts/astra-readiness/recovered_decls.proposed.json, and
artifacts/astra-readiness/recovered_decls.before.json. Missing helpers still
need proper metadata representation; the proposal is not a complete migration.

Automatic approval review rejected modifying the canonical declaration database
as beyond the approved derived-file regeneration scope, citing signature/layout
risk and the need for explicit approval or stronger evidence and a backup.
The attempted regeneration was reverted, the dedicated backup/comparison was
prepared without canonical writes, and approval for extending the work was
requested. All canonical source/metadata and all ratchet baselines remain
unchanged. Do not run the generation script blindly against the stale database.

Some warning increases are mechanical width casts or unused-local annotations;
others identify genuine DATA_OBJECT buffer/range defects and an incomplete
in-game settings widget table. They require their own assembly-backed recovery,
not blanket warning suppression. Exact source sites, assembly addresses and
rejected shortcuts are recorded in
the private local report at artifacts/astra-readiness/deferred-warning-recovery.md.
The mission-00 expectation mismatch and
original Wine startup also remain unresolved. No speculative cause is claimed.

Confidence is high for the measured preservation, build, gate and runtime
results, supported by exact commands, hashes, logs and inspected presented
frames. Full readiness, visual fidelity, new campaign completion and corrected
gameplay behavior are explicitly unproven.

## Declaration continuation — 2026-09-05

Track: Win95 reconstruction, declaration metadata and header generation.
The 31 stale entries now match declarations already present in the canonical
headers and recovered C: 25 function signatures and six global declarations.
No production function, global, table, structure or field was renamed, and no
storage or gameplay implementation changed. The earlier review-only proposal
and approval-rejection record above remain historical evidence.

Two existing initialization helpers now use an explicit `helper` class with
their defining source and subsystem. `Options_RebuildMainMenuWidgetTemplates`
is defined in `src/persistence/00446230_00447840_persistence_003.c:1167` and
called from the neighboring persistence TU at line 515, so it belongs in the
internal header. `Rules_EnsureFactPatternEntityRecord` is defined in
`src/media/004790E0_0047AA80_media_012.c:1248` and called from
`src/clips/004B529A_004B75B0_clips_006.c:1025`, so it belongs in the media API
with its existing `CLASH95_INTERNAL` annotation. The generator validates their
source ownership, rejects unknown classes and manifest collisions, and includes
their definition sites in usage accounting. No original addresses were invented.

Confidence is high for the synchronization: every replacement is checked against
the existing header and canonical definition. Representative assembly checks
also establish the building record/index inputs (`clash95.asm:47878,129108`),
fact-index input (`192151,192158`), three argument-count inputs
(`204795,204847`), DATA_OBJECT output pointer (`253617,253625`), integer
comparison result (`258501,258569`) and object-slot output stores (`359687`).
The six globals agree with their definitions in the state TU at lines 1714,
10475, 10483, 11242, 11417 and 11545. This does not establish correctness of
unchanged wider callback or DATA_OBJECT contracts.

The backup, guarded synchronization script, exact before/after hashes and
160-file preservation record are under
`artifacts/astra-readiness/declaration-repair/`. Preserved files include all
140 recovered C TUs, the affected headers, source/surface metadata, warning,
link and header baselines, and all four mission-11 work files. The shared Git
index was not modified. JSON parsing, exact-change comparison, source/header
agreement and whitespace checks pass. Nine focused helper-metadata and header
placement tests were added in `tests/tools/test_gen_subsystem_headers.py` and
wired into CI, but have **not run**.

Linux validation is blocked before a WSL process can start:

```powershell
wsl --cd /mnt/c/Users/andrz/git/clash-disassembly -- python3 -m unittest discover -s tests/tools -p test_gen_subsystem_headers.py
# Wsl/Service/CreateInstance/E_ACCESSDENIED
node artifacts/astra-readiness/declaration-repair/sync_declarations.cjs --write
node artifacts/astra-readiness/declaration-repair/verify_evidence.cjs
git diff --check
```

The synchronization command records the one-time change and intentionally
rejects a replay against an already modified database. The evidence verifier
is repeatable. The failed test launch is retained in
`artifacts/astra-readiness/declaration-repair/wsl-tests.log`; before/after
staged-diff patches have identical hashes. When WSL is available, run from the
repository root:

```sh
python3 -m unittest discover -s tests/tools -p 'test_gen_subsystem_headers.py'
python3 tools/gen_subsystem_headers.py --report artifacts/astra-readiness/declaration-repair/surface-proposed.json
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
python3 tools/audit_header_surface.py --mode check
```

Full generation and build validation remain pending. The existing stale include
blocks and measured coupling increases still need review; helper accounting is
expected to expose the existing media API and `clips->media` dependency too.
Do not hide that dependency or raise any ratchet to make the check pass.
The highest authentic runtime milestone remains the prior menu and mission-13
replays; this batch makes no new runtime, frame-fidelity or route-completion claim.
