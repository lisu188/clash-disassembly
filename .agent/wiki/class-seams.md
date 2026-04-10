# Class Seams

- Existing conservative executable-regeneration seams remain:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- New class/runtime seam work this batch:
  - `src_cpp/csync_object.cpp` now exports `CSyncObject_Unlock` with the original C ABI and delegates into the conservative `CSyncObject` wrapper
- Current frontier notes:
  - the contained authentic load-game lane is still carried by recovered C menu/save helpers, not by a broader class-runtime splice
  - the current broader contained crash is at `parse-make-instance-before-class-lookup` on `oddzial`, and the guarded trace now proves `sub_4B0480` is failing because `dword_51AD68` is still null
  - `sub_4B0940`, `sub_499990`, and now `sub_4996D0` all link in retained probes
  - the parser-export entrypoints `Lexer_ParseSlotConstraint`, `Lexer_ParseFieldSpec`, `Lexer_ValidateMessageHandler`, `Lexer_ParseDefglobal`, `Lexer_ParseRuleRHS`, and `Lexer_ParseDeclareOptions` are now map-backed names bound onto existing recovered bodies rather than live retained blockers
  - the next honest class/runtime widening is no longer the slot/parser export band; those public names are now rebound onto local recovered bodies and the low-risk file/runtime wrappers are settled
  - the retained startup-prelude widening is now blocked by the remaining x87-heavy math/runtime helpers under `sub_451E46`, not by the class seam or `clash95_cpp_core`
  - do not try to “fix” that by splicing `Rules_ShowBanner_StrategicClash` or bare `sub_499990` into the contained post-save lane
  - the next honest class/runtime widening belongs to the broader startup-prelude chain `sub_451E46 -> sub_47D0E0 -> sub_47C850`, not to the stable contained `sub_444490` wedge
- The world-map top-menu path still touches the raw `DLXSpriteSet` seam through `WorldMap_LoadResources` / `WorldMapTopMenu_LoadSpriteSet`, but the live frontier remains in recovered C save/load and boot-path helpers rather than the C++ seam library.
