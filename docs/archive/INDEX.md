# Archive Index

These files preserve historical reverse-engineering evidence. They were moved
out of the repository root during the documentation consolidation pass, but
their batch entries and conclusions are intentionally kept intact.

## Consolidation Plan

The Markdown cleanup followed this classification:

- Current navigation and status docs stay in `README.md` and top-level
  `docs/*.md`.
- Long-running progress, rename, runtime-wrapper, structure, and unit/stat
  histories move to `docs/archive/` with dates, batch numbers, commands,
  artifact paths, and conclusions preserved.
- Focused route/probe notes move from `tests/README_*.md` to `docs/probes/`.
- Machine-readable evidence remains in place: `RECOVERED_STRUCTURES.json`,
  `UNIT_TYPES_AND_STATS.json`, CSV audits, route env files, and route scripts.
- Hidden agent/wiki Markdown under `.agent/` and `.agents/` is retained in
  place because it is tool/workflow context rather than public project
  navigation.
- Ignored local worktrees and generated artifacts are not part of the tracked
  documentation tree.

Two Markdown files are intentionally retained at the repository root:
`README.md` (public entrypoint) and `AGENTS.md` (tool/workflow context expected
by agents).

| Current path | Original path | Classification |
| --- | --- | --- |
| `docs/archive/COMPILATION_PROGRESS.md` | `COMPILATION_PROGRESS.md` | durable progress history |
| `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md` | `REVERSE_ENGINEERING_RENAME_LOG.md` | rename and recovery evidence |
| `docs/archive/RENAME_PROGRESS.md` | `RENAME_PROGRESS.md` | older rename progress history |
| `docs/archive/RUNTIME_WRAPPER_STATUS.md` | `RUNTIME_WRAPPER_STATUS.md` | runtime-wrapper status history |
| `docs/archive/STRUCT_RECOVERY_NOTES.md` | `STRUCT_RECOVERY_NOTES.md` | structure recovery notes |
| `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md` | `UNIT_TYPES_AND_STATS_REPORT.md` | unit/stat report history |
| `docs/archive/CONVERSATION_FINDINGS_GAP_AUDIT.md` | `docs/CONVERSATION_FINDINGS_GAP_AUDIT.md` | historical gap audit |
| `docs/archive/source-map.md` | `docs/source-map.md` | previous source-hygiene map |
| `docs/archive/RENAME_PROGRESS_WAVE4_PROPOSALS.md` | `RENAME_PROGRESS_WAVE4_PROPOSALS.md` | bulk wave-4 rename proposals (string-literal / host-function symbols) |

Historical entries may mention paths that were correct at the time they were
written. Prefer current docs in `docs/` for navigation, and preserve archived
paths when changing them would blur provenance.

## Active references kept under `docs/archive/`

A few files live under `docs/archive/` only to keep their established paths
stable; they are **live references**, not frozen history, and are linked from
the current docs:

| Path | Role | Linked from |
| --- | --- | --- |
| `docs/archive/SUB_RENAME_INDEX.md` | canonical `sub_XXXXXX` ↔ semantic-name grep index (both directions) | `docs/STATUS.md`, `docs/REVERSE_ENGINEERING.md` |
| `docs/archive/CLIPS_SOURCE_CROSSREF.md` | CLIPS engine source cross-reference (accuracy check) | `docs/STATUS.md`, `docs/REVERSE_ENGINEERING.md` |

## Current Public Docs

| Path | Classification |
| --- | --- |
| `README.md` | concise project entrypoint |
| `docs/STATUS.md` | current validated state and active blocker |
| `docs/ROADMAP.md` | near-term and long-term recovery goals |
| `docs/BUILD_AND_TEST.md` | build, CTest, route, validation, and env-var commands |
| `docs/RUNTIME_MILESTONES.md` | validated route/milestone table with gaps |
| `docs/REVERSE_ENGINEERING.md` | source-of-truth, naming, and patch policy |
| `docs/STRUCTURES.md` | structure/data recovery policy and metadata links |
| `docs/SAVE_DAT_FORMAT.md` | focused save-format evidence |
| `docs/artifacts.md` | artifact retention and pruning policy |
| `docs/probes/README_campaign_arc_probe.md` | full campaign route framework notes |
| `docs/probes/README_first_campaign_arc_probe.md` | first-campaign wrapper notes |
| `docs/probes/README_first_campaign_mission00_gate_probe.md` | mission-00 regression gate notes |
| `docs/probes/README_first_mission_stack6_probe.md` | historical stack6 probe notes |

## Retained In Place

| Path | Reason |
| --- | --- |
| `AGENTS.md` | repository operating instructions expected at root |
| `.agent/wiki/*.md` | tracked agent knowledge base; hidden by convention |
| `.agents/skills/recover-unit-types-and-stats/SKILL.md` | skill manifest/instructions; path is tool-owned |

## Removed Or Ignored Cleanup

No tracked Markdown evidence was deleted during this pass. Generated build
products, frame dumps, crash dumps, route artifacts, and accidental local
scratch are covered by `.gitignore` and the artifact pruning policy rather than
being promoted into documentation. The cleanup policy also ignores stray
root-level CMake/Ninja metadata and coverage output so build experiments do not
become evidence accidentally.

## Deferred Cleanup

- Do not rewrite archived absolute links or old command examples unless they
  block tooling; they preserve what was true when the batch was written.
- Do not move `.agent/wiki/` or `.agents/skills/` without confirming tool
  expectations.
- Do not compact the large historical logs further until a separate evidence
  index can prove no dates, commands, artifact paths, or conclusions are lost.
