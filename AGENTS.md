# AGENTS

## 1. Mission

- Recover the Win95 Clash binary into readable, evidence-backed C and
  structured recovery artifacts.
- Keep the Win95 reconstruction buildable and increasingly behaviorally faithful
  under the SDL-backed runtime.
- Recover campaign behavior through authentic routes rather than state shortcuts.
- Keep the two project tracks separate: Win95 runtime reconstruction and
  campaign-route validation.

See `docs/PROJECT_TRACKS.md` for the current boundaries, baselines, and completion
language for each track.

## 2. Current Repo Reality

### Win95 reconstruction

- The `sub_XXXXXX` placeholder-rename campaign is complete and all `JUMPOUT`
  control-flow scars are recovered into assembly-backed C (counts and current
  state in `docs/STATUS.md`).
- `clash95_bootstrap` compiles, links, boots through the authentic SDL-backed
  runtime, reaches responsive menus, and runs validated gameplay routes.
- Broad placeholder renaming is no longer the main frontier. Remaining work is
  reached behavioral recovery, structure recovery, compatibility cleanup, and
  campaign validation.

### Campaign validation

- Missions `00..04` are complete through their canonical direct-route gates.
- Missions `05..19` remain partial direct-load probes.
- Mission `05` is the first active campaign blocker.
- Full Campaign-menu entry and automatic mission advancement remain unproven.

## 3. Current Blocker Families

- Mission `05` lacks enough strategic-turn and AI-state observability to recover
  the smallest authentic owner-3 elimination route safely.
- Full-menu campaign progression and automatic mission advancement are not yet
  validated.
- `CSS_Init` and its quarantined legacy audio/device table remain broader startup
  debt.
- Reached allocator, file-handle, event, thread, and CRT compatibility stubs may
  still approximate original behavior.

## 4. Practical Priority Order

The current priority sequence is maintained in one place:
`docs/PROJECT_TRACKS.md` → "Immediate priority sequence". Follow it there rather
than a copy kept in sync by hand.

## 5. Scope

- **Win95 scope:** assembly-backed source recovery, SDL platform containment,
  runtime helper recovery, typed state/record recovery, build/link fidelity, and
  reached gameplay behavior.
- **Campaign scope:** authentic menu, mission, battle, objective, failure,
  persistence, and automatic-advance behavior with log and frame evidence.
- **Also in scope:** unit registries, stats, structures, tables, save formats,
  config loaders, AI scripting APIs, and serialization when they support a
  current frontier.
- **Out of scope:** speculative rewrites, cosmetic cleanup, fake/demo loops,
  objective-state shortcuts, or behavior changes made only for convenience.

## 6. Evidence Order

1. `clash95.map` for public symbol spelling and segment-relative addresses.
2. `clash95.asm`, `clash95.c`, and live route evidence for behavior.
3. Struct layouts, lookup tables, arrays, enums, switch dispatch, and shared-state
   access patterns.
4. Call graph neighborhoods, strings, resource keys, and local installed game
   data.
5. Existing recovered artifacts and rename logs.
6. External terminology only as secondary confirmation.

## 7. Local Game-File Corroboration

- The installed game files under `/mnt/c/clash` are the runtime asset root for
  asset-dependent route work.
- `/mnt/c/clash/Manual.pdf` may provide secondary terminology and UI-flow
  evidence.
- Local assets corroborate code evidence; they do not replace control-flow or
  data-flow proof.
- Public CI must not require or publish retail assets.

## 8. Confidence Rules

- **High:** multiple independent signals align.
- **Medium:** strongly suggested but not fully proven.
- **Low:** ambiguous or speculative; never present it as fact.
- Record rejected and uncertain candidates, not only confirmations.
- Never silently upgrade inferred semantics to confirmed semantics.
- Prefer small behavior-preserving repairs over rich guessed abstractions.

## 9. SDL Platform Rule

- SDL remains the final platform, window, render, timing, input, and audio layer.
- Keep original gameplay behavior separate from platform glue.
- Contain Win32-era assumptions behind `platform_sdl.h` and
  `platform_sdl_runtime.c`.
- Put inert compile-only scaffolding in `compat/decomp_runtime_stubs.c` and replace
  it only when reached behavior is understood.
- A live process or dummy window is not sufficient proof; inspect actual
  presented frames for visual milestones.

## 10. Workflow

- Work on one explicit track and frontier per batch.
- Recover whole function families and contiguous state blocks rather than isolated
  names when practical.
- Revisit earlier conclusions when stronger evidence appears.
- Continue existing progress artifacts rather than recreating them:
  - `docs/STATUS.md`
  - `docs/archive/COMPILATION_PROGRESS.md`
  - `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
  - `RECOVERED_STRUCTURES.json`
  - `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md`
  - `UNIT_TYPES_AND_STATS.json`
- Validate each batch with the cheapest meaningful checks, then the relevant
  track-specific gate:
  - formatting and JSON checks;
  - compile and link checks;
  - executable smoke tests;
  - route objective/failure markers;
  - current nonblank frame evidence;
  - repeatable regression runs.

## 11. Required Outputs

After each batch, record:

- track and current frontier;
- blockers removed;
- evidence used and confidence level;
- compile/link/runtime or regeneration status;
- highest authentic runtime or naming milestone reached;
- renamed functions, globals, tables, structures, or fields;
- rejected and ambiguous candidates deferred;
- exact validation commands and durable evidence locations.

Update only the artifacts affected by the batch. Do not manufacture placeholder
structure or semantic entries to make reports look complete.

## 12. Do-Not Rules

- Do not invent semantics absent evidence.
- Do not let external terminology override implementation proof.
- Do not conflate decompiled, named, buildable, runnable, route-complete, and
  campaign-complete.
- Do not drift into unrelated cleanup while an active frontier is blocked.
- Do not accept semantic drift merely because code compiles or links.
- Do not replace authentic recovered flow with fake demo behavior.
- Do not promote direct mission boot as final campaign acceptance.
- Do not remove historical evidence unless a documented replacement supersedes
  it.
