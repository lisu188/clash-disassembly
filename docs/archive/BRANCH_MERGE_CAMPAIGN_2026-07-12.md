# Branch Merge Campaign — 2026-07-12

All work scattered across remote branches and the WSL working clone was consolidated
into `main`: **48 merge commits**, zero remote branches left ahead of main, WSL build
green throughout (per-merge build gates), clash95.c left with **0 conflict markers and
0 JUMPOUT scars**.

## Inputs
- 44 pre-existing remote branches (8 already contained in main).
- 12 refs recovered from the WSL clone `~/git/clash-disassembly`: 10 locally-unique
  branches, the uncommitted mission-04/05 WIP (committed as `4f01973`), and the
  2026-07-05 stash preserved as `wsl-stash-pre-merge-2026-07-05`.

## Method
Every branch was analyzed by an independent agent (unique commits, semantic
contribution, supersession vs main's rename waves, conflict surface), with adversarial
verification before any branch could be ruled "fully superseded". Merge strategies:

| Strategy | Count | Meaning |
|---|---:|---|
| Already contained | 8 | tip reachable from main; no action |
| `-s ours` (superseded) | 37 | every unique change verified present in main in equal-or-better form; merged for ancestry only (incl. the stash, superseded by its newer twin) |
| Clean merge | 1 | CLIPS-6.0 engine identification & 6.30 source cross-check |
| Docs union | 3 | main's tree kept; unique log entries / artifacts union-appended |
| Re-expression | 6 | branch's novel semantics re-applied onto main's current symbol names, conflict-by-conflict |

## Highest-value content landed via re-expression
- **All 17 JUMPOUT control-flow scars eliminated** (asm-backed): 7 epilogue fixes +
  10 audio-mixer thunks upgraded to true signatures delegating to two extracted
  span-dispatch helpers (`Audio_MixVoiceSpanDispatch_46BB40/46BB9A`).
- **Technology-level correction**: player offsets +47/+48 and the level-up notice were
  misnamed as "faction color"; renamed per the game's own string evidence
  (`PLAYER_TECH_LEVEL_OFFSET`, `UI_ShowTechnologyLevelUpIfChanged`, …).
- **Mission-04 post-breach line**: battle-anim value fix (`v101`), fog-overlay sprite fix
  (`v94`), 100 Hz timer fix, 64-bit CLIPS parser pointer-safety rewrites, down/up input
  script commands, trace hooks, multiplayer-map probe harness (+847-line smoke runner).
- **Exact DOS errno table** (`k_DosErrnoMap`, asm-verified) and prisoner-action enum.
- **Garrison service-state semantics** (offset +390 masks/accessor) and
  `QUEEN_RELATIONSHIP_STATE_CHILDBIRTH_PENDING`.
- **19 global renames** incl. `g_MapData` (987 uses) and `g_TilePassabilityMask`.
- CLIPS 6.0 identification docs (`docs/AI_SCRIPTING_API.md`, CLIPS source cross-ref).

## Verified-discard record
Superseded branches' contributions were spot-verified against main before discard
(string-anchored symbol counts, tree-hash equivalence for pre-rebase/pre-squash twins,
and a final uniqueness sweep for files absent from main). Two supersession verdicts
were overturned during verification and their unique artifacts preserved
(`docs/archive/RENAME_PROGRESS_WAVE4_PROPOSALS.md`, Batch-125/consolidation log entries).
