# Source Map

This map classifies the tracked repository sources after the source-hygiene
pass. It is meant to keep future recovery work focused without hiding evidence.

## Classification Table

| Path | Classification | Notes |
| --- | --- | --- |
| `clash95.asm` | authoritative evidence | Behavioral source of truth. Do not edit, reformat, split, or compact. |
| `clash95.exe` | authoritative evidence | Original binary corroboration. Retained even though generated executables are ignored. |
| `clash95.map` | authoritative evidence | Symbol/order corroboration for recovered names and call surfaces. |
| `clash95.c` | recovered source | Main recovered implementation. Edit only with assembly-backed, route-validated changes. |
| `bootstrap_main.c` | required build source | Host entry wrapper for the recovered boot path. |
| `CMakeLists.txt` | required build source | Defines `clash95_recovered`, `clash95_bootstrap`, and CTest route gates. |
| `platform_sdl.h`, `platform_sdl_runtime.c` | platform-only support | SDL/X11 bridge for display, timing, input, and frame dumping. |
| `compat/` | compatibility support | Runtime shims for decompiler, Win32, DirectDraw, Watcom, and CRT-like behavior. |
| `defs.h`, `windows.h` | compatibility support | Top-level include shims needed by recovered code and legacy include paths. |
| `tests/` | test-only support | Smoke tests, real-input route harnesses, frame metrics, route env files, and route scripts. |
| `tools/` | host utility support | Inspection utilities such as save-format dumping; not linked into gameplay. |
| `RECOVERED_STRUCTURES.json` | generated metadata | Structured recovery metadata. Validate with `python3 -m json.tool`. |
| `UNIT_TYPES_AND_STATS.json` | generated metadata | Unit/stat recovery metadata. Validate with `python3 -m json.tool`. |
| `LINK_SURFACE_AUDIT.csv`, `data/*.csv` | generated metadata | Audit/crosswalk evidence used to guide recovery. |
| `COMPILATION_PROGRESS.md` | progress log | Required durable progress log. Keep newest entry near the top. |
| `REVERSE_ENGINEERING_RENAME_LOG.md` | progress log | Semantic rename evidence; append only when names or recovery notes change. |
| `UNIT_TYPES_AND_STATS_REPORT.md` | progress report | Human-readable report backing the unit/stat JSON. |
| `DISASSEMBLY_GUIDE.md`, `RENAME_PROGRESS.md`, `RUNTIME_WRAPPER_STATUS.md`, `STRUCT_RECOVERY_NOTES.md` | progress docs | Historical and current reverse-engineering notes. Retain as evidence. |
| `.agent/state.json`, `.agent/wiki/` | progress sidecar | Durable agent notes. Some entries are stale, but they preserve recovery reasoning. |
| `.agents/skills/` | agent-only support | Local skill instructions used by future agents; not part of the build. |

## Deleted In This Pass

| Path | Reason |
| --- | --- |
| `.codex-loop/*` | Empty JSONL files and failed launcher stderr logs. The retained `.agent/wiki/log.md` already records that these were stale and not live evidence. |
| `include/clash95/cpp/*.hpp` | Unused C++ wrapper headers from the removed C++ regeneration track. They were not referenced by CMake, tests, or active source; underlying evidence remains in `clash95.asm`, `clash95.map`, and `clash95.c`. |

## Protected Large Files

| Path | Reason retained |
| --- | --- |
| `clash95.asm` | Primary behavioral source of truth. |
| `clash95.c` | Current recovered implementation and build input. |
| `clash95.exe` | Original binary evidence. |
| `clash95.map` | Symbol and address evidence. |
| `COMPILATION_PROGRESS.md` | Required durable recovery log, despite size. |
| `REVERSE_ENGINEERING_RENAME_LOG.md` | Required rename/evidence log, despite size. |

## Deferred Compaction

| Candidate | Why deferred | Evidence needed |
| --- | --- | --- |
| Split `clash95.c` | It contains recovered gameplay logic with assembly-derived control flow and offsets. Splitting risks reference drift. | A stable convention for generated recovered-source partitions plus full route validation after each partition. |
| Move top-level compatibility shims into `compat/` | Include path and decompiler scars still assume top-level `defs.h`/`windows.h`. | Proven include rewrite with no recovered-source semantic edits and full build/test pass. |
| Move `.agent/wiki/` under `docs/` | The files are durable but may be consumed by future agent tooling at their hidden path. | Confirmation that no local workflow expects `.agent/wiki/*`, then link updates. |
| Trim progress logs | Old entries contain route evidence, failed hypotheses, and validation history. | A generated index that preserves commit/date/source provenance before any archival or truncation. |
| Consolidate route wrappers further | `tests/run_campaign_route_script_smoke.sh` already centralizes frame checks; wrapper duplication is small and route-sensitive. | Reached-route proof that each wrapper's environment propagation remains unchanged. |

## Provenance Rules

- Keep assembly-derived offsets/macros until enough callsites prove a structure
  promotion.
- Do not delete route scripts merely because a newer route exists; older scripts
  can be diagnostic evidence for blocked paths.
- Ignore generated artifacts by default, then force-add only intentionally
  curated evidence with a note in this file or the milestone index.
