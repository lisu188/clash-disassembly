# SDL Seam

- The current contained and retained frontiers are still below SDL.
- Current evidence:
  - `clash95_bootstrap` default run stays alive for `1s`
  - `--authentic-startup-prelude` stays alive for `2s`
  - the corrected post-confirm contained probes (`CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm`) still reproduce `oddzial` with broader rules and `MAIN` without them
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, and `PlayGame_Dispatch` now link and stay alive under `timeout 1s`
  - the old retained `sub_40D330` / `sub_44C2A0` gap plus the next retained `mapK2`, `mapK3`, `mapK4`, and `mapK5` cases were resolved entirely in recovered C without touching `platform_sdl_runtime.c`
- Next likely SDL-facing work is still later input/present fidelity, not the current mission-loader or class/bload blocker; the next retained blocker is `mapK6`, still below SDL.
