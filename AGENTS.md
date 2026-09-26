# AGENTS

## 1. Mission

The end goal of this repository is a **complete, maintainable C++ reimplementation
of the original Win95 Clash game**, with behavior validated against the original
binary.

- The canonical product is the GNU++20 implementation under `src/`, running on
  the SDL-backed platform layer.
- `clash95.exe`, `clash95.asm`, `clash95.map`, decompiler output, and captured
  original-game traces are evidence and validation oracles. They are not the
  final runtime implementation.
- Recover every gameplay, UI, AI, persistence, rendering, input, audio, video,
  timing, campaign, and supporting runtime behavior needed to reproduce the
  original game.
- Replace decompiler-shaped code progressively with readable, typed, structured
  C++ without changing proven behavior.
- Keep the final runtime portable: original game semantics belong in recovered
  C++ logic; SDL owns the host/platform boundary.
- Campaign-route recovery is an acceptance and regression harness for the C++
  reimplementation, not a substitute for completing the implementation itself.

See `docs/PROJECT_TRACKS.md` for the current frontiers and validated baselines.
Those tracks describe how progress is proved; this file defines the final
destination.

## 1a. Definition Of Done

Do not call the project complete until all of the following are true:

1. The game runs from the C++ implementation without executing, linking, loading,
   patching, or delegating behavior to the original executable or recovered
   machine code. Retail data/assets may still be required when they are part of
   the original game installation.
2. Every original function identity in `data/recovered_sources.json` is
   accounted for as one of:
   - an implemented C++ function or method;
   - intentionally folded, inlined, or merged into clearer C++ with provenance
     retained;
   - proven dead/unreachable for the shipped game and explicitly recorded.
3. Reached decompiler artifacts are eliminated, and the final convergence pass
   removes remaining semantic placeholders, unexplained control-flow scars,
   raw-global ownership ambiguity, and compile-only behavior from production
   paths.
4. No reachable gameplay/runtime behavior depends on inert compatibility stubs.
   `src/compatibility/` contains only narrowly justified compatibility support,
   while `src/platform/` contains only host adaptation.
5. Stable state is represented by evidence-backed C++ types, enums, classes,
   ownership boundaries, and APIs rather than anonymous offsets and unrelated
   globals wherever the original layout has been sufficiently recovered.
6. The complete original user flow is reproducible through the C++ executable:
   startup, menus, both campaigns, tactical battles, strategic AI, save/load,
   mission advancement, map interaction, multiplayer-map flows supported by the
   original, configuration, input, rendering, audio, and video behavior.
7. Both campaigns complete from the real Campaign menu through natural objective
   completion and automatic advancement, without route-only shortcuts or direct
   mission boot as acceptance proof.
8. Visual and behavioral milestones have durable original-vs-C++ evidence where
   practical, including exact state markers and frame comparisons for presented
   output.
9. Supported compiler builds, asset-free public tests, local asset-backed smoke
   tests, regression routes, and the relevant semantic/parity gates are green.
10. Documentation, manifests, structure metadata, tests, and source organization
    describe the final C++ implementation rather than obsolete decompiler-era
    structure.

Full reimplementation does **not** require preserving one C++ function per
original machine-code function. Clearer class methods, helpers, and merged
implementation units are preferred once behavior and provenance remain
traceable.

## 1b. Start Each Session

1. Inspect `git status --short --branch` and `git diff --stat`; preserve existing
   working changes, untracked diagnostics, stashes, and other agents' worktrees.
2. Read `docs/PROJECT_TRACKS.md` and `docs/STATUS.md`, especially "Next Target".
   Route env files in `tests/first_campaign_arc_routes/` are the machine-readable
   campaign status. `.agent/state.json` is historical context, not a work queue.
3. Select one explicit frontier before editing. Prefer work that either advances a
   validated runtime blocker or removes a concrete obstacle to the full C++
   reimplementation. Follow `docs/BUILD_AND_TEST.md`.
4. Run builds and tests in Linux/WSL from the repository root. On this Windows
   checkout the WSL path is `/mnt/c/Users/andrz/git/clash-disassembly`. Runtime
   work must remain headless as required in section 10a.

The tracked `.codex/config.toml` selects GPT-6 Astra for trusted project sessions.
Reasoning effort, permissions, and authentication remain user settings.

## 2. Current Repo Reality

### Win95 C++ reconstruction

- The `sub_XXXXXX` placeholder-rename campaign is complete and all `JUMPOUT`
  control-flow scars are recovered into assembly-backed source (counts and current
  state in `docs/STATUS.md`).
- `clash95_bootstrap` compiles, links, boots through the authentic SDL-backed
  runtime, reaches responsive menus, and runs validated gameplay routes.
- The canonical implementation is in the 12 manifest-backed subsystem directories
  directly under `src/`: 4,157 historical identities in 148 independently
  compiled GNU++20 translation units, including the current class-migrated
  sources.
- The unified source, recovered include-C fragments, and compatibility symlinks
  were removed after the recorded parity gate.
- Broad placeholder renaming is no longer the main frontier. Remaining work is
  behavioral recovery, class/type/ownership migration, compatibility removal,
  subsystem completion, and full-game parity validation.
- Existing class extraction is progress toward the final architecture, not a
  completion milestone by itself.

### Campaign validation

- Missions `00..04` and `13` are complete through their canonical direct-route
  gates (6/20).
- Missions `05..12` and `14..19` remain partial direct-load probes.
- Mission `05` is the first active campaign blocker.
- Full Campaign-menu entry and automatic mission advancement remain unproven.

## 3. Current Blocker Families

- Mission `05` now has an original-matching C++ first Road endpoint `(49,50)`
  on turn 6, with 2 AP, no active path, roads 867/879 and 228 visibility tiles.
  Both supported builds replay the seven-leg approach and actual Building → Road
  action. The original uses real Load restarts from unchanged engine-authored
  turn-5/turn-6 checkpoints; continuous original turn-1 replay is not claimed.
  Use `tests/first_campaign_arc_routes/mission_05_first_road_probe.env`.
  Normal turn refresh and Road continuation through `(48,50)` to `(45,50)`
  are the next C++ frontier. Do not revive removed manual crossing exceptions or
  builder-transfer shortcuts. The separate original reaches `(47,58)` on turn
  10, but C++ arrival, stack-19 tactical entry and owner-3 elimination remain
  unproven. Follow `docs/STATUS.md` "Next Target".
- Full-menu campaign progression and automatic mission advancement are not yet
  validated.
- `CSS_Init` and its quarantined legacy audio/device table remain broader startup
  debt.
- Reached allocator, file-handle, event, thread, and CRT compatibility stubs may
  still approximate original behavior.
- The class/type migration is incomplete; substantial recovered code still
  reflects original global-state and decompiler-era structure.

## 4. Practical Priority Order

`docs/PROJECT_TRACKS.md` owns the current immediate sequence. Within and between
those frontiers, prefer changes that move the repository toward the Definition of
Done rather than changes that only make the decompiled form prettier.

The long-term order is:

1. Keep both supported builds, public CI, split-source audits, and validated
   runtime behavior green.
2. Recover blockers on authentic user-visible paths and turn each recovered path
   into a regression test.
3. Convert proven function families and state blocks into maintainable C++ types,
   methods, ownership boundaries, constants, and APIs.
4. Replace reached compatibility approximations with real behavior and reduce
   platform leakage until the SDL seam contains only host adaptation.
5. Complete every gameplay/UI/persistence/media subsystem and validate it against
   the original.
6. Complete both campaigns from the real menu and close all remaining whole-game
   parity gaps.
7. Perform a final identity/debt convergence pass so every original identity and
   every production stub/placeholder is accounted for.

## 5. Scope

- **C++ implementation scope:** all original game logic required to run Clash,
  including startup, UI, strategic world, units, buildings, battles, campaign,
  AI/CLIPS integration, rendering, persistence, media, input, and runtime
  services.
- **Architecture scope:** evidence-backed classes, structs, enums, constants,
  ownership, resource lifetime, subsystem APIs, and source boundaries that make
  the result maintainable without obscuring original behavior.
- **Platform scope:** SDL-backed window, render, timing, input, and audio
  adaptation, isolated from gameplay semantics.
- **Campaign scope:** authentic menu, mission, battle, objective, failure,
  persistence, and automatic-advance behavior with log and frame evidence.
- **Also in scope:** unit registries, stats, structures, tables, save formats,
  config loaders, AI scripting APIs, serialization, and retail-data decoding.
- **Out of scope:** speculative rewrites, cosmetic churn without debt reduction,
  fake/demo loops, objective-state shortcuts, or behavior changes made only for
  convenience.

## 6. Evidence Order

1. `clash95.map` for public symbol spelling and segment-relative addresses.
2. `clash95.asm`, the manifest-backed recovered subsystem sources directly under
   `src/`, and live route evidence for behavior.
3. Struct layouts, lookup tables, arrays, enums, switch dispatch, and shared-state
   access patterns.
4. Call graph neighborhoods, strings, resource keys, and local installed game
   data.
5. Existing recovered artifacts and rename logs.
6. External terminology only as secondary confirmation.

The C++ implementation may become structurally cleaner than the original binary,
but behavioral claims still require this evidence chain.

## 7. Local Game-File Corroboration

- The installed game files under `/mnt/c/clash` are the runtime asset root for
  asset-dependent route work.
- `/mnt/c/clash/Manual.pdf` may provide secondary terminology and UI-flow
  evidence.
- Local assets corroborate code evidence; they do not replace control-flow or
  data-flow proof.
- Public CI must not require or publish retail assets.
- The original executable may be used as a local comparison oracle, never as a
  production dependency of the reimplementation.

## 7a. Clash Deluxe / clash.y0.pl Corroboration

- Historical-site recovery metadata lives in `research/clash_y0/`; refresh it with `tools/scrape_clash_y0.py`. The raw mirror belongs under ignored `artifacts/` and must not become a public dependency or be committed as third-party site/game content.
- `Clash Deluxe 0.1` is secondary differential evidence. Its author reported changing specific values at specific addresses in `CLASH.EXE` with a hex editor, including unit stats/morale/terrain bonuses, queen-request costs, workshop/forge prices, licence and production costs, and text fixes.
- Establish the executable lineage before interpreting byte offsets. `CLASH.EXE` may be a DOS-family executable; do not assume offsets or layouts match Win95 `clash95.exe`.
- For a matching original/Deluxe pair, hash both, diff changed byte spans, and use the documented rebalance categories to prioritize candidate constants/records. Then prove semantics against `clash95.asm`, recovered source/data flow, structures and runtime evidence before promoting a name or behavior.
- If the Deluxe binary is not byte-compatible with Win95, use its value ordering, table shape and changed-value relationships only as semantic corroboration. Record nonmatches and rejected cross-version candidates.
- See `docs/CLASH_DELUXE_RESEARCH.md` for sources, recovery commands, generated manifests and confidence limits.

## 8. Confidence Rules

- **High:** multiple independent signals align.
- **Medium:** strongly suggested but not fully proven.
- **Low:** ambiguous or speculative; never present it as fact.
- Record rejected and uncertain candidates, not only confirmations.
- Never silently upgrade inferred semantics to confirmed semantics.
- Prefer small behavior-preserving repairs over rich guessed abstractions.

## 9. C++ Reimplementation Rules

- Treat recovered behavior as the specification and C++ as the destination.
- Prefer structured control flow over decompiler labels/gotos once equivalence is
  proved.
- Replace magic values with evidence-backed enums/constants and raw state offsets
  with typed fields once layout confidence is sufficient.
- Recover coherent classes/state owners from whole function families; do not
  create thin classes that merely hide anonymous globals.
- Prefer explicit ownership and RAII for new host-side resources. Do not change
  original gameplay lifetime semantics merely to modernize syntax.
- Standard containers, algorithms, smart pointers, references, and stronger types
  are welcome when equivalence is demonstrated and binary-layout compatibility is
  not required at that boundary.
- Preserve packed/on-disk/original-memory layouts where save formats, data files,
  ABI observation, or comparison tooling requires exact representation; isolate
  those layouts behind typed accessors.
- Remove obsolete compatibility helpers when their last caller has a proven C++
  replacement. Never leave two competing implementations active.
- Keep provenance searchable when folding or merging original functions. Update
  `data/recovered_sources.json` or the appropriate mapping artifact when source
  ownership changes.
- Add or strengthen tests before/with risky structural migrations. A refactor is
  not accepted merely because it compiles.
- Do not preserve ugly decompiler structure solely for textual fidelity after
  semantics are understood; preserve behavior, evidence, and traceability.

## 10. SDL Platform Rule

- SDL remains the final platform, window, render, timing, input, and audio layer.
- Keep original gameplay behavior separate from platform glue.
- Contain Win32-era assumptions behind `src/platform/platform_sdl.h` and
  `src/platform/platform_sdl_runtime.cpp`.
- Put inert compile-only scaffolding in
  `src/compatibility/decomp_runtime_stubs.cpp` only temporarily, and remove or
  replace it as soon as its behavior becomes reachable or understood.
- A live process or dummy window is not sufficient proof; inspect actual
  presented frames for visual milestones.

## 10a. Mandatory Frame Comparison Against the Original

- Any visual-fidelity claim (title, menus, world map, battle, dialogs) must be
  backed by a side-by-side frame comparison between the reconstruction and the
  ORIGINAL `clash95.exe` rendering the same state.
- The original runs headless under Wine inside WSL Xvfb (32-bit prefix with a
  dosdevices drive mapping so `DetectGameCDPath` finds the install; capture via
  ImageMagick `import`/`xwd` against the Xvfb display). Never launch either
  binary on the host desktop and never open image viewers; all captures stay
  headless files under `artifacts/`.
- The reconstruction side uses the existing
  `CLASH95_DUMP_PRESENTED_FRAMES_PREFIX` presented-frame dumps from its own
  Xvfb runs.
- Record for every comparison: both frame files, the pixel metrics
  (`tests/frame_metrics.py` or an equivalent mean-abs-diff/nonmatching-pixel
  count), the game state markers proving both sides show the same state, and
  the exact commands. Known acceptable differences (palette timing, cursor,
  AVI frames) must be listed explicitly, not glossed over.
- New route promotions and startup/rendering recoveries that touch presented
  output should include at least one fresh comparison pair as evidence.

## 11. Workflow

- Work on one explicit frontier per batch, but choose frontiers that close
  measurable full-reimplementation debt.
- Keep integration frequent: fetch origin and integrate `origin/main` at session
  start, between completed batches, and before publishing. Merge completed,
  validated work into `main` promptly, push it, and refresh the active worktree
  from the resulting main. This is the user's standing preference; no separate
  merge confirmation is needed for authorized work. Preserve other agents'
  changes and coordinate access to a shared main checkout; do not force-push or
  reset away unrelated work.
- Delegate independent evidence gathering, bounded audits, and validation when
  useful. Give each editing agent disjoint file ownership before it writes;
  never let concurrent agents modify the same files or shared Git index.
- The coordinating agent owns integration, evidence review, and final relevant
  gates. Subagent findings must retain source locations, commands, confidence,
  and unresolved candidates; delegation does not establish behavioral proof.
- Recover whole function families and contiguous state blocks rather than isolated
  names when practical, then migrate the proven family toward coherent C++.
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
  - focused unit/semantic comparisons;
  - route objective/failure markers;
  - current nonblank frame evidence;
  - repeatable regression runs.

## 12. Progress Language

Use status words narrowly:

- **decompiled**: a decompiler emitted a body.
- **named**: an identity has an evidence-backed semantic name.
- **buildable**: the reconstructed target compiles and links.
- **runnable**: the executable reaches a verified authentic runtime state.
- **typed**: a function family/state block uses evidence-backed C++ types and
  ownership rather than anonymous raw layout.
- **reimplemented**: behavior is expressed as maintainable production C++ with no
  reachable decompiler/compatibility placeholder on that path and with provenance
  retained.
- **parity-validated**: the C++ path has relevant original-vs-reimplementation
  behavioral evidence.
- **route-complete** and **campaign-complete** retain the definitions in
  `docs/PROJECT_TRACKS.md`.

No earlier status implies a later one.

## 13. Required Outputs

After each batch, record:

- current frontier and which Definition-of-Done gap it reduces;
- blockers removed;
- evidence used and confidence level;
- compile/link/runtime or regeneration status;
- highest authentic runtime and C++ migration milestone reached;
- functions, globals, tables, structures, fields, or compatibility behavior
  recovered/migrated;
- original identities folded or moved, with provenance;
- stubs/placeholders removed or remaining on the touched path;
- rejected and ambiguous candidates deferred;
- exact validation commands and durable evidence locations.

Update only the artifacts affected by the batch. Do not manufacture placeholder
structure or semantic entries to make reports look complete.

## 14. Do-Not Rules

- Do not invent semantics absent evidence.
- Do not let external terminology override implementation proof.
- Do not conflate decompiled, named, buildable, runnable, typed, reimplemented,
  parity-validated, route-complete, and campaign-complete.
- Do not optimize for decompiler resemblance when semantics are already proven and
  clearer C++ can preserve them.
- Do not drift into unrelated cleanup while an active frontier is blocked.
- Do not accept semantic drift merely because code compiles or links.
- Do not replace authentic recovered flow with fake demo behavior.
- Do not promote direct mission boot as final campaign acceptance.
- Do not hide original behavior in SDL/platform glue or leave reachable behavior
  as a compatibility no-op.
- Do not remove historical evidence unless a documented replacement supersedes
  it.
