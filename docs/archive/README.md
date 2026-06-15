# Archive

This directory holds historical reverse-engineering notes and large progress
logs that are still evidence but no longer belong in the repository root.

## Moved Historical Files

| Current path | Previous path | Classification |
| --- | --- | --- |
| `docs/archive/COMPILATION_PROGRESS.md` | `COMPILATION_PROGRESS.md` | Historical batch log and validation record |
| `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md` | `REVERSE_ENGINEERING_RENAME_LOG.md` | Confirmed rename and recovery log |
| `docs/archive/RENAME_PROGRESS.md` | `RENAME_PROGRESS.md` | Legacy rename progress notes |
| `docs/archive/RUNTIME_WRAPPER_STATUS.md` | `RUNTIME_WRAPPER_STATUS.md` | Legacy runtime wrapper status |
| `docs/archive/STRUCT_RECOVERY_NOTES.md` | `STRUCT_RECOVERY_NOTES.md` | Legacy structure notes |
| `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md` | `UNIT_TYPES_AND_STATS_REPORT.md` | Human-readable unit/stat report |
| `docs/archive/CONVERSATION_FINDINGS_GAP_AUDIT.md` | `docs/CONVERSATION_FINDINGS_GAP_AUDIT.md` | Historical gap audit |
| `docs/archive/source-map.md` | `docs/source-map.md` | Previous repository source map |

Historical entries inside these files may mention their old paths. Those entries
are preserved as history rather than rewritten.

## Merged Or Replaced

- Current status text is centralized in `docs/STATUS.md`.
- Build, CTest, route, soak, metadata, and Markdown-link commands are centralized
  in `docs/BUILD_AND_TEST.md`.
- The old milestone index is now `docs/RUNTIME_MILESTONES.md` with explicit
  command, evidence, and gap columns.
- The old disassembly guide is now `docs/REVERSE_ENGINEERING.md`.

## Removed

No tracked Markdown evidence was deleted in this pass.

## Deferred Cleanup

- `.agent/wiki/` was left in place because local agent tooling may consume it.
- Historical paths inside archive logs were left intact to preserve batch text.
- Route scripts and test harnesses were not moved; only their focused README
  notes moved to `docs/probes/`.
- The large progress logs were archived but not split or summarized further.

## Intentionally Retained Outside This Archive

- `README.md` remains the root entry point.
- `AGENTS.md` remains at the root so agent tooling and contributors can find the
  project instructions.
- `.agent/wiki/` remains in place because it may be consumed by local agent
  workflows.
- `.agents/skills/` remains in place because it defines local Codex skills.
