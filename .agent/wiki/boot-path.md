# Boot Path

## Current Route
- Canonical binary evidence still points at `start -> sub_486369 -> _WinMain@16`.
- The current repo executable route is:
  - `main`
  - `App_WinMain`
  - `Bootstrap_RunRecoveredEarlyStartupPrelude`
  - `Bootstrap_RunRecoveredRuntimeAndRenderInit`
  - `Bootstrap_RunRecoveredGameEntry`
  - `Bootstrap_RunMessageLoop`
- `main` now always compacts argv into `g_boot_command_line` and enters `App_WinMain(GetModuleHandleA(0), 0, g_boot_command_line, 0)`.

## Current Milestone
- `clash95_bootstrap` and `clash95_cpp_regen` both enter the recovered full-game route by default.
- The route reaches the live message/game loop and stays alive until an external timeout kills it.
- The retained log-file side effect is restored: `createLogFiles` creates/truncates `clash.log` and `battle.log` under the original `logEnabled` gate and clears `dword_526A20`.

## Removed Selectors
- Host-side bootstrap probe modes are no longer active:
  - `--authentic-startup-prelude`
  - `--authentic-video-init`
  - `--authentic-menu-probe`
  - `--platform-window-only`
- Menu-probe and capture environment controls are no longer active bootstrap selectors.
- The only tracked runtime `CLASH95_*` environment reads that remain intentional are SDL presented-frame dump diagnostics: `CLASH95_DUMP_PRESENTED_FRAMES_PREFIX` and the compatibility alias `CLASH95_SCREENSHOT_PREFIX`.

## Next Frontier (2026-04 snapshot)
- These goals reflect the April 2026 state; the playable-session widening has
  since landed (missions `00..04` are route-complete). The current frontier is
  mission 05 — see `docs/STATUS.md`. Still-true item: recover or safely
  quarantine the skipped `CSS_Init` DirectSound-era device-table path.
