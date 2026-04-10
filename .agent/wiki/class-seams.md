# Class Seams

- Existing conservative executable-regeneration seams remain:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- New class/runtime seam work this batch:
  - `src_cpp/csync_object.cpp` still exports `CSyncObject_Unlock` with the original C ABI
- Current frontier notes:
  - the contained authentic load-game lane is still carried by recovered C menu/save helpers, not by a broader class-runtime splice
  - the current broader contained crash is still at `parse-make-instance-before-class-lookup` on `oddzial`, and the guarded trace still proves `sub_4B0480` is failing because `dword_51AD68` is null
  - retained probes for `sub_451E46`, `sub_460490`, `UI_StartAnims`, `sub_4B0940`, `sub_499990`, and `sub_4996D0` now all link
  - the parser-export entrypoints `Lexer_ParseSlotConstraint`, `Lexer_ParseFieldSpec`, `Lexer_ValidateMessageHandler`, `Lexer_ParseDefglobal`, `Lexer_ParseRuleRHS`, `Lexer_ParseDeclareOptions`, `Lexer_EmitSlotBinding`, `Lexer_BuildSlotNode`, and `Lexer_FindSymbolIndex` are now map-backed names bound onto existing recovered bodies rather than live retained blockers
  - the next honest class/runtime widening is no longer the slot/parser export band or the x87 math band
  - the next honest retained class/runtime widening belongs to the broader `PlayGame_Dispatch` surface, which currently fans into `_wcpp_4_static_init__`, front-end/world-map data tables, `Locale_DrawInteger`, `Rules_*`, `Render_DrawSprite_v3`, `WCIsvListBase_*`, and nearby `JUMPOUT`
  - do not try to “fix” that by splicing `Rules_ShowBanner_StrategicClash` or bare `sub_499990` into the contained post-save lane
  - the broader startup-prelude widening still belongs to the retained track, not to the stable contained `sub_444490` wedge
- The world-map top-menu path still touches the raw `DLXSpriteSet` seam through `WorldMap_LoadResources` / `WorldMapTopMenu_LoadSpriteSet`, but the live frontier remains in recovered C save/load and boot-path helpers rather than the C++ seam library.
