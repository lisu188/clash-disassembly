# Class Seams

- Existing conservative executable-regeneration seams remain:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- New class/runtime seam work this batch:
  - `src_cpp/csync_object.cpp` now exports `CSyncObject_Unlock` with the original C ABI and delegates into the conservative `CSyncObject` wrapper
- Current frontier notes:
  - the contained authentic load-game lane is still carried by recovered C save/load helpers, not by a broader class-runtime splice
  - the current broader contained crash is at `parse-make-instance-before-class-lookup` on `oddzial`
  - do not try to “fix” that by splicing `Rules_ShowBanner_StrategicClash` or bare `sub_499990` into the contained post-save lane
  - the next honest class/runtime widening belongs to the broader startup-prelude chain `sub_451E46 -> sub_47D0E0 -> sub_47C850`, not to the stable contained `sub_444490` wedge
- The world-map top-menu path still touches the raw `DLXSpriteSet` seam through `WorldMap_LoadResources` / `WorldMapTopMenu_LoadSpriteSet`, but the live frontier remains in recovered C save/load and boot-path helpers rather than the C++ seam library.
