# Current Blockers

## Active Full-Route Blockers
- The default executable route is now `main -> App_WinMain`; host-side menu/startup probe modes are not active selectors anymore.
- Lowercase `r` is now the first finite recovered startup/shutdown route: it enters early startup and runtime/render init, skips the game-entry handoff, shuts down, and exits `0`.
- The default no-arg route now reaches the recovered main-menu presentation/wait loop and passes `clash95_full_route_smoke`; this is a liveness milestone, not a finite recovered quit path.
- `CSS_Init` remains skipped because the retained DirectSound-era device table is not recovered safely enough for x86-64 execution under the SDL runtime seam.
- Deeper menu/session interactions, clean finite default-route shutdown, and the broader playable-turn milestone after the full default startup route are still open.

## Recently Removed
- The intro AVI/CD availability blocker is removed for the local install: direct loose AVI paths can satisfy `Win_BeginModeChange` when the recovered resource query misses them.
- The reached intro AVI constructor crash is removed: `CAviDecompressor` construction now shares the byte-offset initializer instead of repeating pointer-scaled event-handle setup on the 64-bit host.
- The first main-menu liveness path no longer depends on undefined widget-copy counts, truncated stack-local widget pointers, 8-byte reads from original 32-bit compact vtables, or the undefined `v24` wait-loop sentinel.
- Authentic finite shutdown is recovered for the lowercase `r` command route and is covered by `clash95_r_command_shutdown_smoke`.
- `createLogFiles` no longer depends on malformed decompiler locals around the old stream-open corridor.
- The retained log-file creation side effect is restored: when `logEnabled` is set, it truncates/creates `clash.log` and `battle.log`, closes both files, and clears `dword_526A20`.
- The stale menu-capture CTest was replaced with a full-route live-loop smoke aligned to the current default startup path.
- Bootstrap-only switches and menu-probe environment controls no longer decide startup behavior.

## Historical Retained Gameplay Frontier
- The deeper `WorldMap_RunHumanTurnLoop` / `WorldMap_HandleTileHoverAndClick` work remains useful historical context, but it is not the active front-end blocker for the current full-route startup slice.
- If gameplay/session widening resumes, continue from the reduced `Unit_AttackBuilding` outcome-resolution tail inside `sub_4084A0`, with `sub_451F70` still secondary.
