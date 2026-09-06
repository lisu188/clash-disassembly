# Main integration, 2026-09-06

Track: Win95 reconstruction. Frontier: integrate the completed GNU++20 migration,
original-backed mission-05 recoveries, and upstream strategic-AI recovery into
`main`. This batch does not extend a campaign route or claim new visual fidelity.

## Integrated work

- `4992d72` records the existing migration and runtime recovery: 140 recovered
  GNU++20 translation units, all 4,157 identities, support/native-test migration,
  original-backed formatter, visibility, turn-score and builder-Road repairs,
  and their retained tests, partial probes and documentation.
- `227ae34` merges upstream `8e0b181` (PR #87). Git carries its two strategic
  function repairs and body hashes into the renamed `.cpp` file. The evaluator
  consumes the real priority return value, and regrouping preserves the original
  signed-byte comparisons. Matcher provenance and completeness tooling remain
  included. See [STRATEGIC_AI_DATAFLOW.md](STRATEGIC_AI_DATAFLOW.md).
- The incoming strategic fixture now compiles its extracted production bodies
  as GNU++20. All prior assertions remain; GCC 13 and Clang 18 each cover O0/O2
  and signed/unsigned plain-char modes. No additional gameplay repair or function
  rename was introduced while resolving the integration.

The canonical source audit and both subsystem-header freshness checks pass
without regeneration. No compiler-warning, header, link or coverage baseline
was raised.

## Validation

Fresh builds use the repository as their source directory, with Linux-native
output under `/tmp/clash-integration-merge-main-20260906/clash-disassembly/build/`
to conserve Windows disk space. All commands run from
`/mnt/c/Users/andrz/git/clash-disassembly` in WSL.

| Gate | Result |
| --- | --- |
| GCC 13 / Clang 18 compile and link | Both pass |
| Recovered warning checks | Pass: 6,618 / 6,628 warnings |
| Four explicit asset-free CTest gates | 4/4 pass on each compiler |
| Python tooling suite | 120/120 pass on the final repeat |
| Focused strategic regression | 13/13 tests; eight native configurations pass |
| Native unit harness, final restored-source run | 1,061 pass, zero assertion failures, 528 isolated crashes, 1,589 total |
| Frozen coverage gate | 6,169/6,662 lines (92.60%); all 718 functions covered |
| Default GCC headless CTest suite | 11 pass, two known first-mission selection failures, eight opt-in skips |
| Split, save, AI data/source contracts, JSON, generated metadata, links and shell syntax | Pass |
| Raw linked-symbol/layout ratchets | Retained failures: GCC 427 / Clang 679 differences; zero archive crosscheck errors |
| Header-surface ratchet | Retained 14 differences |

The native wrapper tolerates isolated crashes; its pass is not crash-free
acceptance. The warning checks pass, but the header/link failures keep the full
GitHub CI workflow from being green. The separately documented runtime and
campaign limitations remain in [STATUS.md](STATUS.md) and
[UNIT_TESTING.md](UNIT_TESTING.md).

The first full tooling run timed out in the viewport fixture's outer five-second
deadline while three builds ran concurrently. The unchanged 17-test viewport
suite then passed, and the same 160-attempt case passed three repeats in
1.10–1.13 seconds. The final full suite passed after the builds settled. No
timeout or assertion was weakened; the failed log remains retained.

The final default smoke suite uses each wrapper's own Xvfb display. Playability
and attack still fail waiting for `next_unit_selected selected=1 a=31 b=44`.
Menu Exit and castle economy pass in this run; this observation does not prove
the historical timing failures fixed. An initial invocation incorrectly forced
SDL dummy video for wrappers that need an Xvfb window; its four window-discovery
failures are retained as a validation setup error, not gameplay evidence.

The transient unfinished header edit described below triggered an input-hash
check. After preserving that edit and restoring the committed header, both
compiler rebuilds reproduce the tested executable and archive hashes exactly.
All 297 tracked build inputs match the original freeze. The rebuilt coverage
executable differed, so its native suite and coverage measurement were repeated
against the restored source rather than relying on the earlier native run.
The initial run had 1,059 passes and 530 isolated crashes; both runs and their
case-by-case comparison remain retained. This variation is not reported as two
recovered runtime contracts.

Exact local validation drivers and logs are under
`artifacts/integration/merge-main-20260906/`:

```sh
bash artifacts/integration/merge-main-20260906/builds/validate.sh
bash artifacts/integration/merge-main-20260906/builds/stabilize-restored-header.sh
bash artifacts/integration/merge-main-20260906/builds/final-coverage.sh
python3 artifacts/integration/merge-main-20260906/repo_checks.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
python3 -m unittest discover -s tests/tools -p 'test_*.py'
```

The build driver records each expanded compiler, CMake, CTest, warning/link
and coverage command in its profile logs. The repository results JSON records
every metadata/tooling command and exit; `tooling-final.log` supersedes only the
initial load-sensitive tooling result. These ignored local evidence files are
absent from clean checkouts; public commands remain in
[BUILD_AND_TEST.md](BUILD_AND_TEST.md).

## Preserved unfinished work and history

All historical local branch tips and WSL worktree commits were already integrated.
Fresh GitHub inspection found no open PRs; the new PR #87 branch tree exactly
matches its upstream merge. Eighteen historical remote heads correspond to
confirmed merged PRs; the other old refs contain superseded layouts, removed
temporary workflows or an empty net change. Re-merging those old implementations
would not recover missing completed work. The three stashes' route commands are
already present. The detailed audit is
`artifacts/integration/merge-main-20260906/history-audit.md`.

At the user's direction, the unfinished HD/resizable-window experiment remains
in `/home/andrz/wt-hd1`. Other diagnostic worktrees, all stashes and prior evidence
are retained. Windows' historical "prunable" labels do not mean the WSL
worktrees are missing.

A separate magic-number cleanup task was interrupted while this integration
ran. Its only new checkout change was an unfinished `src/recovered_types.h` edit.
The complete file was copied and SHA256-verified in
`.worktrees/preserved-magic-numbers-20260906`, on branch
`codex/preserve-magic-numbers-20260906`, before restoring the integration checkout
to its committed header. The exact patch also remains in
`artifacts/integration/merge-main-20260906/interrupted-magic-numbers.patch`.
That unfinished cleanup is preserved for its owning task and is not part of this
completed-work merge.

Confidence is high for the ancestry, exact input checks and reported validation
outcomes. The highest compared mission-05 endpoint remains the first Road action
at `(49,50)` on turn 6, with 2 AP and 228 visible tiles. Mission 05 stays partial;
direct-route completion remains 6/20, and full-menu advancement is unproven.
