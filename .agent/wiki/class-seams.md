# Class Seams

- Existing conservative executable-regeneration seams remain:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- Current frontier notes:
  - the contained authentic load-game lane is still carried by recovered C menu/save helpers, not by a broader class-runtime splice
  - the current broader contained crash is still at `parse-make-instance-before-class-lookup` on `oddzial`
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, and `PlayGame_Dispatch` now all link
  - the old retained `sub_40D330` / `sub_44C2A0` gap was confirmed again to be pure recovered-C mission/minimap/view-state work, not `src_cpp`
  - `mapK2`, `mapK3`, `mapK4`, `mapK5`, and `mapK6` were also confirmed and recovered as pure recovered-C mission setup; the next honest class/runtime widening is still not a signal to move behavior into `src_cpp`, and the live retained blocker is now the remaining mission-case recovery starting with `mapK7`
