# SDL Seam

- The just-cleared load-menu row-resource and row-draw blockers were not SDL seam failures.
- `platform_sdl_runtime.c` remained unchanged through this batch.
- Current evidence:
  - `clash95_bootstrap` default run stays alive for `1s`
  - `--authentic-startup-prelude` stays alive for `2s`
  - contained widened load-menu row draws, slot-hover selection, and slot-click/confirm all complete under the existing SDL seam
  - contained post-confirm `WorldMap_Initialize` and `.dat` / `.fac` session-load in `sub_444490` also complete under the existing SDL seam
  - the explicit broader contained probe now reaches `parse-make-instance-before-class-lookup` on `oddzial`
  - the retained broader startup-prelude slice is currently blocked on the wider runtime/class/parser surface below SDL, not on `platform_sdl_runtime.c`
- Next likely SDL-facing work is still later input/present fidelity, not the cleared row-resource corridor, the newly-proven confirm lane, or the first post-save handoff.
