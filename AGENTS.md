# AGENTS

## 1. Mission
- Reverse-engineer this decompiled Clash-like codebase into a readable, buildable, and increasingly runnable C project.
- Long-term semantic goal: recover concrete unit types, categories, stats, and their relationships from implementation evidence.
- Current engineering goal: turn the recovered gameplay core into a real SDL-backed executable that enters the authentic boot path, reaches responsive menus, and eventually supports at least one narrow playable turn.

## 2. Current Repo Reality
- `clash95.c` already compiles cleanly enough for the repo's recovered static-library target.
- The project is much closer to a recovered gameplay core than to a playable port.
- Gameplay semantics are already moderately recovered across unit, battle, building, port, road, and prisoner systems.
- The main frontier is no longer parser triage; it is startup, link, runtime, and boot-path fidelity.
- The final platform target remains SDL. Do not reintroduce Win32 as the final runtime layer.

## 3. Current Blocker Families
- There is still no fully recovered `main` / `_WinMain@16` end-to-end executable path.
- `_wcpp_*` and related CRT/runtime glue families are still only partially understood.
- Quarantined allocator, file-handle, event, and thread stubs still stand in for real behavior in important areas.
- `JUMPOUT` control-flow scars still exist in meaningful boot/runtime paths.
- SDL containment exists, but the repo is not yet at "boot to menu and play a match."

## 4. Practical Priority Order
1. Produce a runnable executable binary.
2. Make it enter the authentic game boot path.
3. Make menus and UI responsive under SDL-backed input, timing, and rendering.
4. Make one narrow playable turn possible.
5. Continue semantic renaming and structure recovery where it directly supports those goals.
6. Continue broader unit/stat recovery when it is the highest-value safe frontier or when it clarifies the boot/menu/turn path.

## 5. Scope
- **In scope:** startup/entrypoint reconstruction, SDL seam work, build/link recovery, runtime helper recovery, menu/UI/event-loop behavior, session/game-start initialization, narrow playable-turn enablement, and semantic recovery of enums/registries/structs/tables/helpers that materially support those goals.
- **Also in scope:** unit type registries, spawn/factory logic, stat structs/tables, config loaders, targeting/scaling/serialization logic when they expose types or stats.
- **Out of scope:** unrelated refactors, speculative rewrites, cosmetic cleanup, behavior changes made only for convenience, or fake/demo loops that bypass authentic recovered game code.

## 6. Evidence Order
1. Corroborated behavior across `clash95.c`, `clash95.asm`, `clash95.map`, and `clash95.exe`.
2. Function bodies and direct data flow in `clash95.c`.
3. Struct layouts, lookup tables, arrays, enums, switch dispatch, and shared-state access patterns.
4. Call graph neighborhoods, strings, debug text, config/resource keys, and map ordering.
5. Existing recovered artifacts and prior rename logs.
6. External Clash terminology only as secondary confirmation.

## 7. Local Game-File Corroboration
- The installed game files can be inspected under `/mnt/c/clash` when local asset, config, resource, or text evidence is needed.
- Treat `/mnt/c/clash` as corroborating evidence, not as a replacement for function/data-flow proof from the recovered codebase.

## 8. Confidence Rules
- **High:** multiple independent signals align.
- **Medium:** strongly suggested but not fully proven.
- **Low:** ambiguous or speculative; never present it as fact.
- Mark every ambiguous finding explicitly as ambiguous.
- Prefer small, behavior-preserving repairs over rich guessed abstractions.

## 9. SDL Platform Rule
- SDL is the final platform, window, render, timing, and input layer.
- Keep gameplay code separated from platform glue.
- Replace or contain Win32-era assumptions behind the existing SDL seam in `platform_sdl.h` and `platform_sdl_runtime.c`.
- A dummy SDL window alone is not success; the goal is authentic recovered boot/runtime behavior.

## 10. Workflow
- Continue until canceled, safely exhausted, or blocked by concrete repo-wide limits.
- Revisit earlier conclusions when new evidence surfaces.
- Continue the existing progress artifacts rather than recreating them:
  - `COMPILATION_PROGRESS.md`
  - `REVERSE_ENGINEERING_RENAME_LOG.md`
  - `RECOVERED_STRUCTURES.json`
  - `UNIT_TYPES_AND_STATS_REPORT.md`
  - `UNIT_TYPES_AND_STATS.json`
- Prefer the current highest-value frontier in this order:
  1. executable/link blockers
  2. startup blockers
  3. SDL/platform blockers
  4. menu/UI blockers
  5. session-init blockers
  6. one-playable-turn blockers
  7. nearby semantic rename/structure recovery
- Validate after each batch with the cheapest meaningful checks available:
  - compile check
  - link/build check
  - executable launch smoke test
  - runtime milestone check

## 11. Required Outputs
- Maintain `COMPILATION_PROGRESS.md`.
- Maintain `REVERSE_ENGINEERING_RENAME_LOG.md`.
- Maintain `RECOVERED_STRUCTURES.json`.
- Maintain `UNIT_TYPES_AND_STATS_REPORT.md`.
- Maintain `UNIT_TYPES_AND_STATS.json`.
- After each batch, record:
  - current frontier
  - blockers removed
  - compile/link/runtime status
  - highest authentic runtime milestone reached
  - renamed functions/helpers/globals/tables/structs
  - ambiguous candidates deferred

## 12. Do-Not Rules
- Do not invent semantics absent code evidence.
- Do not let external terminology override implementation proof.
- Do not drift into unrelated cleanup while boot/runtime blockers remain.
- Do not treat "the static library compiles" as the final success condition.
- Do not accept semantic drift just because something links.
- Do not replace authentic recovered flow with a fake demo harness unless it is clearly quarantined as a temporary smoke-only step.
