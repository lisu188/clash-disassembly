# Roadmap

The repository has two active recovery tracks. See `docs/PROJECT_TRACKS.md` for
current baselines and completion language.

## Immediate Sequence

See `docs/PROJECT_TRACKS.md` → "Immediate priority sequence" for the current
ordered near-term steps. The per-track goals below are the longer-term view.

## Campaign Recovery

- First campaign: clear missions `00..09` from the real Campaign menu path.
- Second campaign: clear missions `10..19` from the real Campaign menu path.
- Treat direct mission boot as a diagnostic tool only.
- Promote route env files from `partial` to `complete` only after natural objective
  completion, absence of mission failure, deterministic checkpoints, repeatable
  regression success, and current nonblank frame evidence.
- Prove campaign persistence and automatic advancement separately from direct
  route completion.

## Win95 Runtime Recovery

- Keep `clash95_bootstrap` building cleanly under the SDL-backed runtime.
- Preserve menu, route, timing, input, rendering, save-format, and multiplayer-map
  milestones while fixing reached blockers.
- Continue replacing reached decompiler artifacts with assembly-backed recovered C.
- Inventory and replace compatibility stubs only when active routes reach them.
- Keep original game behavior out of platform and compile-only shims.
- Do not add fake loops, objective-state shortcuts, or host-specific behavior as
  acceptance proof.

## Semantic And Structure Recovery

- Recover whole function families and contiguous state blocks rather than isolated
  symbols when practical.
- Prioritize player, building, unit-stack, mission, and strategic-AI state needed
  by mission `05` and campaign advancement.
- Preserve raw offsets until typed overlays are supported by multiple callsites and
  compile-time layout checks.
- Keep ambiguous findings explicitly labeled in reports and JSON metadata.
- Continue broader unit, structure, rule, UI, save-format, and AI API recovery when
  implementation evidence is strong and it supports an active frontier.

## Validation Infrastructure

- Keep public CI asset-independent.
- Use a private or local asset-backed environment for menu, campaign, multiplayer,
  audio, and soak validation.
- Preserve frame-based validation for visual milestones.
- Keep artifact pruning enabled so long route investigations do not grow the
  checkout indefinitely.
- Record exact commands, durable evidence paths, and rejected or uncertain
  findings after every recovery batch.
