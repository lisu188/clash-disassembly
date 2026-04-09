# Boot Path

- Durable boot chain in repo:
  - `main`
  - `App_WinMain`
  - `Bootstrap_RunRecoveredStartupPrelude`
  - `Bootstrap_RunRecoveredRuntimeAndRenderInit`
  - contained probes such as `--authentic-startup-prelude` and `--authentic-menu-probe`
- Current contained menu milestone:
  - top-level `Load Game` click is stable
  - contained load-menu row resources load
  - contained load-menu row draws complete
  - contained slot-hover selection exits with `selected_slot = 0`, `confirm = 0`, `screen = 5`
  - contained slot-strip click plus bottom-row load confirm exits with `selected_slot = 0`, `confirm = 1`, `screen = 5`
  - contained `CSS_StopSound -> WorldMap_Initialize -> sub_444490` now returns
  - the contained probe reaches `load-menu-post-confirm-after-save` and returns to `main-after-menu-probe`
- Next boot-path frontier:
  - contained post-save `PlayGame` handoff after `sub_444490`
  - deferred save-slot repaint/name lane after the row draws
