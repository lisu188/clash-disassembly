# Header surface baseline synchronization — 2026-09-24

## Scope

This batch synchronizes the header/coupling ratchet after the reviewed C++20,
class-extraction and Road-ownership migrations that landed after the previous
baseline commit `8e5ff4f568689fe58dd812fc61e1dfefe3682b56` from 2026-07-18.

It is not a blind baseline raise. The class-header policy false positive was
removed first, generated-header and TU-include freshness are unchanged, the
shared-global count remains exactly 244, and the public builds, asset-free
CTest gates and coverage gate already pass on the pre-synchronization tree.

## Public API delta

Exactly five functions are public that were not public in the July baseline:

| Home | Function | Reason |
| --- | --- | --- |
| buildings | `WorldMap_EnsureBuilderWidgetTables` | Required cold initializer after Road widget ownership moved from world to buildings; removing the world call breaks cold initialization. |
| media | `Rules_EnsureFactPatternEntityRecord` | Existing helper is defined in media and used by the CLIPS initialization TU; its helper classification and source ownership are validated. |
| persistence | `saveGame` | Original save writer is used by the retained route-harness save command to create engine-authored checkpoints. |
| render | `Render_SetResourceHandle` | Canonical identity at 0x00404A40 replaced raw/legacy access while the historical alias remains internal. |
| state | `UnitSlot_BorrowTypeMetadata` | Narrow accessor for the immutable 40-row unit metadata table used by canonical UnitSlot methods; storage remains state-owned. |

No other subsystem API count grows.

## Peer-edge delta

The exact generated dependency-set comparison against the July source gives the
following additions:

- `Render_SetResourceHandle` adds one render dependency for battle, buildings,
  persistence, runtime, strategic, units and world.
- Typed surface dispatch adds `RenderSurface_InvokeSlot0` to battle and
  strategic, `RenderSurface_InvokeSlot36` to render and strategic, and
  `RenderSurface_InvokeSlot48LoadPCX` to strategic. These replace raw vtable
  dispatches; for example the battle dialog destructor call and strategic team
  screen calls become explicit typed helpers.
- `Runtime_InitCompactEvalDescriptor` adds clips -> state and repairs the
  recovered deffunction descriptor before registration.
- Relocating the validated GameRandom methods into their core class source adds
  core -> buildings via `Time_Now` and core -> units via `Debug_Log`; the
  method bodies and service calls are unchanged.
- Road widget ownership adds buildings -> units via `UI_DrawWidgetIcon` and
  world -> buildings via `WorldMap_EnsureBuilderWidgetTables`.
- `Rules_EnsureFactPatternEntityRecord` adds clips -> media.
- UnitSlot/class readability adds units -> state via
  `UnitSlot_BorrowTypeMetadata` and `UnitType_GetLocalizedName`.
- The route save probe adds world -> persistence via `saveGame`.

The same comparison removes world -> units dependencies on
`Pathing_DisableBridgeCrossings` and `Pathing_EnableBridgeCrossings`; the
unsupported manual bridge exceptions remain removed.

## Evidence

The old and current generated surfaces were recomputed from preprocessed TU
usage, not inferred from counts. The current numeric surface has five API-count
increases, 18 peer-edge count increases and no shared-global increase. The
pre-synchronization CI for PR #150 confirms that the earlier `UnitStack.hpp`
policy error is gone; Markdown validation, the declaration/header tooling suite,
coverage, both supported builds, warning gates and both compilers' asset-free
CTest gates pass. Only the historical header and linked-symbol ratchets remain.

Relevant existing proof is retained in
`docs/HUMAN_READABILITY.md`,
`docs/CPP_CLASS_SEPTEMBER_INTEGRATION.md`,
`docs/CPP_CLASS_ORIGIN_REFRESH.md`,
`docs/UNIT_SLOT_AP_CLASSES.md` and
`docs/ASTRA_READINESS.md`.

This synchronization changes only the ratchet reference and documentation. It
does not change production C++, runtime behavior, route status or visual claims.
