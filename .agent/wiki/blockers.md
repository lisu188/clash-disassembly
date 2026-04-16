# Current Blockers

## Active Full-Route Blockers
- The default executable route is now `main -> App_WinMain`; host-side menu/startup probe modes are not active selectors anymore.
- Lowercase `r` is now the first finite recovered startup/shutdown route: it enters early startup and runtime/render init, skips the game-entry handoff, shuts down, and exits `0`.
- The default no-arg route currently exits early through the intro AVI/CD path (`Video_Avi_playIn -> App_RequestQuit`) with `[platform_sdl] Clash: Clash CD not found!`; the old full-route liveness smoke is no longer green until that path is recovered.
- `CSS_Init` remains skipped because the retained DirectSound-era device table is not recovered safely enough for x86-64 execution under the SDL runtime seam.
- The broader playable session milestone after the full default startup route is still open.

## Recently Removed
- Authentic finite shutdown is recovered for the lowercase `r` command route and is covered by `clash95_r_command_shutdown_smoke`.
- `createLogFiles` no longer depends on malformed decompiler locals around the old stream-open corridor.
- The retained log-file creation side effect is restored: when `logEnabled` is set, it truncates/creates `clash.log` and `battle.log`, closes both files, and clears `dword_526A20`.
- The stale menu-capture CTest was replaced with a full-route live-loop smoke aligned to the current default startup path.
- Bootstrap-only switches and menu-probe environment controls no longer decide startup behavior.

## Historical Retained Gameplay Frontier
- The deeper `WorldMap_RunHumanTurnLoop` / `WorldMap_HandleTileHoverAndClick` work remains useful historical context, but it is not the active front-end blocker for the current full-route startup slice.
- If gameplay/session widening resumes, continue from the reduced `Unit_AttackBuilding` outcome-resolution tail inside `sub_4084A0`, with `sub_451F70` still secondary.
