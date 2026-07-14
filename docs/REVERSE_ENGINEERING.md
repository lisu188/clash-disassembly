# Reverse Engineering

This file is the working guide for contributors recovering `clash95` from the original binary artifacts and the current `clash-disassembly` repo.

It is intentionally practical. The goal is not to restate everything already known, but to keep future reverse-engineering work consistent, evidence-driven, and easy to merge.

## Current Rule Summary

- `clash95.asm` is authoritative behavioral evidence and must not be edited.
- `clash95.c` changes should be small, reached, and backed by assembly or live
  route evidence.
- Platform portability belongs behind `platform_sdl.h` and
  `platform_sdl_runtime.c`.
- Historical progress and rename evidence live in `docs/archive/`.
- If a change would remove evidence, keep the file and document the deferred
  cleanup instead.

---

## 1. Source-of-truth order

When two sources disagree, prefer them in this order:

1. **`clash95.map`**
   - Canonical for public symbol spellings and segment-relative addresses.
   - If a name exists here, preserve it somewhere even if a better semantic alias is introduced.

2. **`clash95.asm` and `clash95.c`**
   - Canonical for control flow, constants, strings, offsets, table walks, and calling patterns.
   - Use these to prove behavior, not the decompiler's guessed variable names.

3. **Repo recovery artifacts**
   - `RECOVERED_STRUCTURES.json`
   - `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
   - `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md`
   - `docs/archive/COMPILATION_PROGRESS.md`

4. **Portability / compatibility seam**
   - `platform_sdl.h`
   - `platform_sdl_runtime.c`
   - `compat/decomp_runtime_stubs.c`
   - `CMakeLists.txt`

Rule of thumb:
- **map names** tell you what existed publicly,
- **asm/c** tell you what the code actually does,
- **repo recovery files** tell you what the current project already considers stable,
- **SDL / compat files** tell you where to place shims instead of burying semantics in fake Win32 code.

---

## 2. Evidence grades to use in commits and PRs

Use these words consistently:

- **map-confirmed**: exact public symbol exists in `clash95.map`.
- **repo-confirmed**: a rename or struct already exists in `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md` or `RECOVERED_STRUCTURES.json`.
- **behavior-confirmed**: behavior is supported by at least two independent signals (for example asm + strings, or callers + table layout).
- **inferred**: plausible semantic name, but still only backed by one strong line of evidence.
- **compile-fix**: a change that restores buildability but does **not** prove original semantics.

Do **not** silently upgrade an inferred name into a confirmed one.

---

## 3. Naming rules

### 3.1 Keep public names alive

If `clash95.map` already exposes a public symbol, do not erase it from history.

Good pattern:
- keep the map name as the canonical address anchor,
- add the semantic alias in comments, wrappers, or rename-log entries,
- let grep find both.

Example:
- `Port_GetSupply` is public and should remain searchable,
- but current recovery strongly supports the semantic alias `Port_CollectReinforcementShipment`.

### 3.2 Prefix families

Use subsystem prefixes consistently:

- `Render_...`
- `UI_...`
- `Unit_...` / `UnitStack_...` / `UnitBattle_...` / `UnitSlots_...`
- `Building_...` / `BuildingGarrisonDialog_...` / `CastleProduction_...`
- `Port_...`
- `WorldMap_...`
- `Battle_...`
- `Platform_...` / `InputBackend_...`
- `Rules_...`
- `Lexer_...` / `Parser_...` / `AST_...` / `Compiler_...`
- `Module_...` / `Class_...` / `Method_...` / `Symbol_...`

### 3.3 Type naming

Use these suffixes deliberately:

- `...Record` for repeated fixed-stride entries in arrays
- `...State` for one shared runtime/modal block
- `...Table` for descriptor tables or lookup slabs
- `...Entry` for one row in a table
- `g_...` for globals

### 3.4 Conservative names beat wrong names

If a field or helper is clearly real but not fully understood, use names like:

- `unnamed_resource_state`
- `aux_context`
- `visual_class_index`
- `pending_exit_countdown`

Do **not** promote a guess just because it "looks likely."

### 3.5 Constant and enum families (magic-number campaign)

Numeric literals are named with `SCREAMING_SNAKE_CASE` `#define`s at the top of
`src/clash95_prelude.inc.c`, subsystem-prefixed like the function/global
families: `UNIT_STACK_`, `BUILDING_`, `BUILDING_ADDON_FLAG_`, `PLAYER_`,
`MAP_`, `PORT_`, `TILE_`, `TILE_OVERLAY_`, `TILE_OCCUPANT_`, `SCREEN_`, etc.
Offsets/strides get an accessor macro (`UNIT_STACK(i)`, `BUILDING_RECORD(i)`).

Rules for introducing a named constant:

- **Two independent signals** for `behavior-confirmed` (e.g. a switch that maps
  a code to a named result, plus a write path or a corroborating artifact);
  one signal → conservative name or defer (§3.4). Record deferred/ambiguous
  candidates.
- **Exact-literal spelling**: the `#define` body matches the dominant call-site
  lexeme (hex stays hex) so substitution is preprocessor-token-identical and
  provably value-preserving.
- **No blanket sweeps**: every replacement site is context-gated. Small,
  collision-prone literals (bit flags, tiny offsets) are bound to a specific
  field or expression shape via `regex`/tier-3 co-occurrence rules, never
  replaced by bare value.

Tooling under `tools/`: `tools/literal_common.py` (lexer/classifier),
`tools/constants_manifest.json` (value→name gating), `tools/literal_inventory.py`
(evidence census), `tools/apply_literal_names.py` (gated substitution + `--plan`),
`tools/gen_constant_guard.py` (compile-time `NAME==value` pins in
`src/core/005_constant_guard.inc.c`), and `tools/pp_token_gate.sh` /
`tools/pp_token_diff.py` (the preprocessed-token-identity gate that stands in for
the binary-diff check this repo lacks; `--allow` verifies declared respellings).
Provenance ledger: `docs/archive/win95_constants_rename_accum.jsonl`; per-batch
rules under `docs/archive/literal_rules/`; narrative in
`docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`.

---

## 4. Current repo seam: where different kinds of work belong

The current build surface already separates three kinds of work:

### 4.1 Recovered gameplay / original logic

Put semantic recovery here:
- `clash95.c`

Typical changes:
- renames,
- struct field names,
- state-block recovery,
- replacing bad decompiler expressions with behavior-preserving C.

### 4.2 Platform / portability shim

Put non-original compatibility glue here:
- `platform_sdl.h`
- `platform_sdl_runtime.c`

Typical changes:
- Win32-to-SDL handle/type compatibility,
- message queue / timing shim behavior,
- fake or translated runtime services.

Current repo examples worth preserving:
- `platform_sdl.h` already maps old handle types like `HWND` to `SDL_Window *` and `HDC` to `SDL_Surface *`.
- `platform_sdl_runtime.c` already provides a Win32-like queue surface with `PeekMessageA`, `PostQuitMessage`, and queue timestamps sourced from `timeGetTime()`.

### 4.3 Inert stubs and compile unblockers

Put placeholder-only scaffolding here:
- `compat/decomp_runtime_stubs.c`

Typical changes:
- dummy unresolved weak symbols,
- temporary no-op support for code paths not yet semantically recovered.

**Important:**
If a change explains the original game's behavior, it belongs in the recovered logic path, not in the shim.

---

## 5. Stable anchor symbols worth building around

These are high-value anchors because they already connect map labels, decompiled bodies, and repo-side recovery.

| Address | Existing symbol | Preferred interpretation | Why it matters |
|---|---|---|---|
| `0001:00000A40` | `Render_LoadResourceBackbuffer` | canonical render bootstrap anchor | Early rendering and surface setup |
| `0001:00004A90` | `DLXSpriteSet_Load` | real class-like asset loader | Stable graphics/class seam |
| `0001:00004EC0` | `DLX_GetSpriteForChar` | text/sprite lookup | Helps recover font/sprite records |
| `0001:00004F00` | `DLXSpriteSet_DrawText` | text rendering via sprite set | Bridges UI text and graphics data |
| `0001:00005740` | `Render_DrawSprite` | core sprite blit path | Central graphics xref hub |
| `0001:0000AE50` | `UI_DrawText` | public UI text draw entry | Good UI/string anchor |
| `0001:0000E510` | `Unit_Create` | strategic unit stack creation | Root of unit lifecycle |
| `0001:000108E0` | `Unit_NewTurn` | per-turn strategic refresh | Pulls many unit/runtime fields together |
| `0001:000137A0` | `Unit_MoveTrack` | strategic movement execution | Best pathfinding/state consumer |
| `0001:00017F60` | `UI_HighlightTile` | highlight-table entrypoint | Clean UI state anchor |
| `0001:00017FE0` | `UI_ClearTileHighlight` | highlight teardown | Pairs with tile highlight table recovery |
| `0001:0001C030` | `Building_New` | building creation | Root of building/runtime recovery |
| `0001:00034580` | `UI_GetGridIndexFromMouse` | castle licence-grid hit test | Useful modal-UI anchor |
| `0001:00034620` | `UI_HandleClickDispatch` | action-box / grid dispatch hub | Central UI routing point |
| `0001:0003D850` | `Building_BuyAddon` | castle/addon economy mutation | Links production UI to building state |
| `0001:0003DB50` | `Building_CountGarrison` | garrison slot counting | Core building-slot semantics |
| `0001:00041D90` | `Port_FindAndInit` | port runtime bootstrap | Seeds port state and shoreline visuals |
| `0001:00042550` | `Port_GetSupply` | **prefer semantic alias:** `Port_CollectReinforcementShipment` | Port reinforcement and spawn-ring logic |
| `0001:00060520` | `Input_Init` | input subsystem init | Ties into platform/input state block |
| `0001:00060530` | `Input_Shutdown` | input teardown | Paired lifecycle anchor |
| `0001:000607C0` | `Win_WndProc` | **prefer semantic alias:** `Platform_MainWindowProc` | Main platform window proc |
| `0001:00060A20` | `Win_CreateMainWindow` | **prefer semantic alias:** `Platform_CreateMainWindow` | Platform bootstrap |
| `0001:000627B0` | `CAviDecompressor` ctor | real class seam | Stable video/media cluster |
| `0001:00063250` | `CAviDecompressor::Frames` | trusted accessor family | Good offset-recovery target |
| `0001:000632B0` | `CAviDecompressor::Initialized` | trusted accessor family | Confirms internal readiness state |
| `0001:00063570` | `CAviDecompressor::TimeMs` | trusted timing accessor | Useful for media-state layout |
| `0001:00080550` | `Lexer_ParseValueList` | parser/DSL anchor | Good grammar-level entrypoint |
| `0001:00080C20` | `Parser_ReportError` | parser diagnostics | Stable error/report path |
| `0001:00080D70` | `Str_Intern` | symbol/string runtime anchor | Important shared runtime primitive |
| `0001:00090580` | `Module_BeginEnum` | object-system enumeration start | Compiler/meta-runtime seam |
| `0001:000907C0` | `Module_NextEnum` | object-system enumeration | Same family as above |
| `0001:000907D0` | `Module_GetName` | module metadata access | Useful for class/module struct recovery |
| `0001:000933E0` | `AST_NewNode` | AST allocation semantic anchor | One of the safest parser names |
| `0001:00093720` | `IO_OutWriteToken` | code/output emission | Proves text-generation path |
| `0001:000937D0` | `IO_OutNewline` | output formatting | Pair with token emission |
| `0001:00093870` | `AST_Append` | output/AST composition helper | Important but still nuanced semantics |
| `0001:00095000` | `Event_ClearHandlers` | event-table lifecycle | Good state reset anchor |
| `0001:00095030` | `Event_InitHandlers` | event-table init | Pairs with clear/init block |
| `0001:00096750` | `Class_NextMethod` | class metadata enumeration | Object model seam |
| `0001:000A8750` | `Symbol_LookupInModule` | symbol resolver | Compiler/runtime bridge |
| `0001:000ABB00` | `Compiler_WriteHeaders` | compiler output header pass | Backend anchor |
| `0001:000ABB60` | `Compiler_MarkAndEmit` | backend dependency / emit pass | Highest-value compiler emission anchor |
| `0001:000C72D0` | `Method_FindByIndex` | class/method metadata lookup | Works with module/class enumeration |

Recover clusters around these anchors, not isolated leaf functions.

---

## 6. Repo-backed semantic aliases that are safe to propagate

These are already strong enough to reuse consistently in comments, wrappers, logs, and future refactors.

| Legacy symbol | Preferred semantic name | Confidence |
|---|---|---|
| `Port_GetSupply` | `Port_CollectReinforcementShipment` | High |
| `Win_WndProc` | `Platform_MainWindowProc` | High |
| `Win_CreateMainWindow` | `Platform_CreateMainWindow` | High |
| `sub_461B30` | `Platform_PumpMessagesAndBlitFrame` | High |
| `sub_4084A0` | `WorldMap_HandleTileHoverAndClick` | Medium |
| `sub_42CB50` | `UnitBattle_HandleBattlefieldInteraction` | High |
| `sub_42E9E0` | `Battle_RunTacticalCombat` | High |
| `sub_435280` | `CastleProduction_DrawProductionStatus` | High |
| `sub_435640` | `CastleProduction_SelectPreviousAvailableUnit` | High |
| `sub_435680` | `CastleProduction_SelectNextAvailableUnit` | High |
| `sub_4356C0` | `CastleProduction_HandleBuyLicenceAction` | High |
| `sub_4338C0` | `BuildingGarrisonDialog_RequestClose` | High |
| `sub_4338E0` | `BuildingGarrisonDialog_ShowProductionDialog` | High |
| `sub_433A40` | `BuildingGarrisonDialog_ToggleRepairSelectedUnits` | High |
| `sub_433AC0` | `BuildingGarrisonDialog_ToggleTrainingSelectedUnits` | High |
| `sub_433B40` | `BuildingGarrisonDialog_BeginSelectedUnitsExit` | High |
| `sub_433BF0` | `BuildingGarrisonDialog_TickAnimations` | High |
| `sub_412B20` | `UnitStackSelection_BuildSelectedSlotIndexList` | High |

When adopting one of these, also update cross-references nearby so the whole family uses the same vocabulary.

---

## 7. Stable recovered structures already worth treating as real

These are the highest-value state/layout recoveries already in the repo. Build new work on top of them instead of starting from raw globals every time.

### 7.1 Strategic / world state

- **`UnitTypeMetadataRecord`**
  - 88-byte per-type metadata record.
  - Current repo work already reconstructs the 35-entry roster and uses a strict "two independent signals" rule before promoting names.
  - This is the right home for per-type sprite folders, movement costs, morale/AP defaults, and visual-class-like fields.

- **`UnitStackRecord`**
  - Stable strategic stack record with stride `725`.
  - Treat the 10-slot strategic squad layout as real until disproven.

- **`MergedTerrainMoveProfile`**
  - 9-byte merged movement slice derived from unit-type metadata.
  - Important for strategic movement/pathfinding and for understanding why mixed stacks behave the way they do.

- **`UnitStackSelectionState`**
  - Shared modal state for the world-map split/selection panel.
  - Good target when cleaning up the "move selected members" flow.

- **`PortRuntimeState`** and **`PortSpawnOffset`**
  - Port logic is no longer just loose globals.
  - Treat the port as a real runtime block plus a 12-entry spawn ring around the 2x2 footprint.

### 7.2 Battle state

- **`BattleRuntimeState`**
  - Shared tactical battle runtime block.
  - Known high-value fields already include viewport tiles, side ids, 22 battle-unit entries, a 20x20 occupant grid, wall hitpoints, and overlay planes.

- **`BattleUnitEntry`**
  - 31-byte tactical unit entry.
  - Good next target for exact per-slot animation, AP, health, and facing semantics.

- **`BattlePathingTables`**
  - Shared tactical movement scratch state.
  - Contains a precomputed tile move-cost grid, airborne-type cost table, and ignore-occupancy flag.

### 7.3 Castle / UI state

- **`BuildingGarrisonDialogState`**
  - Real modal state cluster.
  - Includes 12-slot selection bitmap, selected slot, sprite handles, and leave-barracks countdown.

- **`CastleManagementScreenState`**
  - Shared castle-screen modal state.
  - Use it when touching castle/building management flow instead of scattering globals.

- **`CastleProductionPanelState`**
  - Shared production/licence modal state.
  - Best place to continue recovering available-unit selection and licence-animation behavior.

- **`MiniMapState`**
  - Shared minimap rect, surface, scale, and draw-layer state.

- **`TooltipBackdropState`**
  - Saved-surface + rect + resource-handle tooltip block.
  - Strong evidence, low ambiguity.

### 7.4 Platform / input state

- **`InputBackendState`**
  - 320-byte DirectInput-backed runtime block.
  - Existing repo recovery already ties keyboard/mouse/joystick pointers, polled state, and presence flags into one stable block.

### 7.5 Still intentionally conservative

These names/fields are useful, but should stay conservative until another pass tightens them:

- `UnitType33_SpecialFootPersonage` and `UnitType34_SpecialMountedPersonage`
- `UnitTypeMetadataRecord.visual_class_index`
- `BuildingGarrisonDialogState.unnamed_resource_state`
- `BuildingGarrisonDialogState.unnamed_slot_animation_state`
- `TooltipBackdropState.aux_context`
- the exact semantic boundary of `AST_Append`

If you improve one of these, document the new evidence explicitly instead of silently renaming it everywhere.

---

## 8. Unit-type rules that should shape future disassembly

The unit-type work is already much stronger than "just folder order." Build on that.

### 8.1 Proven facts

- The per-unit-type metadata family is an 88-byte record.
- The current recovered roster spans **35 unit types**.
- Types `31` and `32` are special cargo-style entries (`GoldCargo`, `PeasantCargo`) and should not be treated as ordinary combat units.
- Types `33` and `34` are best handled as **special personage** entries until stronger evidence narrows the role further.

### 8.2 Practical consequence

Do not let combat, capture, port, or strength-scoring code assume that every slot with a unit id is a normal battlefield unit.

A lot of late-game confusion comes from mixing these four special entries into generic "unit" logic.

---

## 9. High-return work queues

If you are choosing where to spend time, this is the order with the best payoff.

### Queue A - world map interaction and strategic loop

Targets:
- `sub_4084A0` -> `WorldMap_HandleTileHoverAndClick`
- `Unit_Create`
- `Unit_NewTurn`
- `Unit_MoveTrack`
- `UI_HighlightTile` / `UI_ClearTileHighlight`
- top-menu cluster around `sub_40E8B0`

Why first:
- touches most player-visible strategic behavior,
- drives stack movement, fog, hover text, split panels, and context actions,
- provides callers for a large number of still-anonymous helpers.

### Queue B - battle turn flow and runtime block

Targets:
- `sub_42E9E0` -> `Battle_RunTacticalCombat`
- `sub_42CB50` -> `UnitBattle_HandleBattlefieldInteraction`
- `BattleRuntimeState`
- `BattleUnitEntry`
- `BattlePathingTables`

Why first:
- battle code has a coherent runtime slab already,
- field recovery immediately improves many functions at once,
- good payoff for viewport, pathing, wall, and result-pack code.

### Queue C - castle / garrison / production UI family

Targets:
- `sub_4338C0` / `4338E0` / `433A40` / `433AC0` / `433B40` / `433BF0`
- `sub_435280` / `435640` / `435680` / `4356C0`
- `Building_BuyAddon`
- `Building_CountGarrison`
- `Building_OnGarrisonChange`

Why first:
- the action tables and modal state blocks are already strong,
- this family is currently easy to rename incorrectly if done one function at a time,
- recovering the whole cluster will reduce UI churn and duplicate naming.

### Queue D - port reinforcement and shoreline logic

Targets:
- `Port_FindAndInit`
- `Port_GetSupply` -> `Port_CollectReinforcementShipment`
- `Port_BuildShorePieces`
- port spawn-ring tables and shoreline variant tiles

Why first:
- good example of decompiler-split globals that are really one runtime block + one table,
- high gameplay value,
- currently one of the cleanest wins for turning globals into real structs.

### Queue E - platform loop, input backend, and AVI/video seam

Targets:
- `Win_WndProc` -> `Platform_MainWindowProc`
- `Win_CreateMainWindow` -> `Platform_CreateMainWindow`
- `sub_461B30` -> `Platform_PumpMessagesAndBlitFrame`
- `InputBackendState`
- `CAviDecompressor` family
- `DLXSpriteSet` family

Why first:
- the repo already has a platform compatibility seam,
- these helpers are class/state oriented and reward offset recovery,
- the SDL shim is the right place to quarantine non-original host behavior.

### Queue F - rules engine / object system / compiler front-end

Targets:
- `Module_BeginEnum`, `Module_NextEnum`, `Module_GetName`
- `Class_NextMethod`, `Method_FindByIndex`
- `Symbol_LookupInModule`
- `AST_NewNode`, `AST_Append`, `AST_Free`
- `IO_OutWriteToken`, `IO_OutNewline`
- `Compiler_WriteHeaders`, `Compiler_MarkAndEmit`

Why first:
- this area has unusually strong semantic names already,
- the object-system/compiler seam is central enough that one good struct pass helps a wide area,
- backend emission and module/class enumeration make excellent "anchor families" for future parser work.

#### Provenance: the rules engine is CLIPS 6.0

The entire Queue F area (rules engine, COOL object system, and the
constructs-to-C / bsave compiler front-end) is an embedded copy of **CLIPS
6.0** - NASA's *C Language Integrated Production System* expert-system shell.
The `Module_*`, `Class_*`, `Method_*`, `Instance_*`, `Deffunction_*`,
`Defgeneric_*`, `MessageHandler_*`, `Deftemplate_*`, `Defrule_*`, `AST_*`, and
`Compiler_*` families are not game-authored - they are the CLIPS 6.0 public API
and internals. The rename evidence notes that hedge with "CLIPS-like" all refer
to this same shell; treat CLIPS 6.0 as their authoritative external reference.

The version labels across the CLIPS docs are consistent once the binary is fixed:
this `clash95` (Win95) engine is **CLIPS 6.0** (the `"V6.00"` stamp below), and
the public **6.30** core source is used only as a stand-in where 6.0 source is not
distributed.

Concrete in-repo evidence (all verifiable by grep against `clash95.c`):

- **Version stamp `"V6.00"`** (`off_51A1C4`, `clash95.c:11924`) is used as the
  bload/bsave version magic: written into the binary constructs image and
  `strcmp`-verified on load (`clash95.c:95445-95446`, `118409`). A second
  bsave subsystem stamps the same string via `off_51AD24` (`clash95.c:12182`,
  used at `137555`, `137897-137898`). This is exactly CLIPS 6.0's
  `VERSION_STRING "6.00"` binary-image version check.
- **Standard CLIPS routers** `wwarning`, `werror`, `wtrace`, `wdialog`,
  `wclips`, `wdisplay` (`off_51A610..51A620`, `clash95.c:12039-12043`) - the
  CLIPS logical-name constants `WWARNING/WERROR/WTRACE/WDIALOG/WCLIPS/WDISPLAY`.
- **Product strings**: `"CLIPS> "` prompt (`clash95.c:6456`), `"clips.hlp"`
  (`7258`), `#include "clips.h"` code-generation header (`7309`),
  `"***CLIPSFNXARGS***"` external-function arg marker (`7761`),
  `"\n*** CLIPS SYSTEM ERROR ***\n"` (`6335`), and the
  `"   PeriodicCleanup(CLIPS_TRUE,CLIPS_FALSE);\n"` GC banner (`7363`).

Practical consequence for future recovery: when a Queue F function's role is
unclear, match its shape and strings against the CLIPS 6.0 source (public;
function names such as `EnvReset`, `Bload`, `Bsave`, `IncrementSymbolCount`,
`FindDefmodule`, `NextDefclass`, `PrintRouter`, `PeriodicCleanup` are stable
anchors). This upgrades many of the honest "low"-confidence mechanical
descriptions in `docs/archive/SUB_RENAME_INDEX.md` to citable identifications
without needing the retail game assets.

The game exposes its strategic AI to the CLIPS rule base through a fixed set of
host functions registered with `DefineFunction2`; the decoded registration
table (H/L command name, C-name, return type, arity, address) is documented in
`docs/AI_SCRIPTING_API.md`.

A first string-anchored cross-reference pass (recovered name vs. CLIPS 6.30
core source) is recorded in `docs/archive/CLIPS_SOURCE_CROSSREF.md`. It found
zero mis-named string-anchored Queue F functions and made one low->high
refinement (`Defgeneric_EmitQualifiedNameBanner` ->
`Defgeneric_CreateDefaultPPForm`). Note that most low-confidence Queue F
functions carry no string literals (trivial accessors, refcount helpers,
vtable-slot thunks, Watcom destructors) and are not resolvable by string
anchoring; their honest mechanical descriptions are correct as-is.

---

## 10. Function-family recovery strategy

Recover these together, not one by one.

### 10.1 Garrison dialog family

Work as one cluster:
- `BuildingGarrisonDialog_RequestClose`
- `...ShowProductionDialog`
- `...ToggleRepairSelectedUnits`
- `...ToggleTrainingSelectedUnits`
- `...BeginSelectedUnitsExit`
- `...TickAnimations`
- `BuildingGarrisonDialogActions`
- `BuildingGarrisonDialogState`

### 10.2 Castle production family

Work as one cluster:
- `CastleProduction_DrawProductionStatus`
- `...SelectPreviousAvailableUnit`
- `...SelectNextAvailableUnit`
- `...HandleBuyLicenceAction`
- `CastleProductionPanelState`

### 10.3 Platform/message loop family

Work as one cluster:
- `Platform_MainWindowProc`
- `Platform_CreateMainWindow`
- `Platform_PumpMessagesAndBlitFrame`
- `InputBackendState`
- SDL message queue shim

### 10.4 Compiler/object-system family

Work as one cluster:
- `Module_*`
- `Class_*`
- `Method_*`
- `Symbol_*`
- `AST_*`
- `Compiler_*`

A family rename that leaves neighbors anonymous is often worse than waiting one more pass.

---

## 11. Common traps to avoid

### 11.1 Decompiler names that are probably wrong

Examples already corrected by repo work:
- `Input_MousePresent` is really an OS/version test, not mouse presence.
- `Input_MouseAcquire` is also an OS/version test, not a real acquire call.
- `Port_GetSupply` is not a passive getter.

### 11.2 Compile-fix drift

A build-unblocking name is not automatically a semantic name.

If you only proved "this compiles now," keep the change in the compat/stub lane or label it clearly as a compile fix.

### 11.3 Overnaming special-unit slots

Types `31..34` break naive combat assumptions.
Do not rename helpers as "normal unit" logic until you verify they exclude cargo/personage cases.

### 11.4 Treating split globals as unrelated

The decompiler repeatedly split contiguous blocks into parallel arrays or unrelated globals.

Before inventing new names, ask whether you are really looking at:
- one runtime block,
- one repeated record family,
- or one action table.

---

## 12. Minimum bar for a good rename PR

A rename PR is good when it does all of this:

1. Preserves the original map/decompiler name somewhere searchable.
2. States the new semantic name.
3. Gives the evidence source(s): callers, strings, table shape, field offsets, or state-block usage.
4. Updates adjacent family names if the rename affects them.
5. Updates `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`.
6. Updates `RECOVERED_STRUCTURES.json` if a struct boundary or field meaning was involved.
7. Does not move original semantics into the SDL shim or compat stubs.

If a rename does not clear that bar, leave it in comments or notes until the next pass.

---

## 13. Suggested good next tasks for contributors

These are good starter tasks because each unlocks multiple nearby symbols.

- [ ] Verify and document the full caller/callee family around `sub_4084A0` / `WorldMap_HandleTileHoverAndClick`.
- [ ] Promote `sub_461B30` consistently as `Platform_PumpMessagesAndBlitFrame` and align its callers with the SDL queue shim.
- [ ] Freeze the remaining obvious fields in `BattleRuntimeState` around selection, current actor, and per-side turn state.
- [ ] Finish the `BuildingGarrisonDialogState` unnamed renderer/animation fields and tie them to action callbacks.
- [ ] Lift the castle production callbacks into one coherent enum/table-driven UI layer.
- [ ] Tighten the `CAviDecompressor` raw layout using the accessor family instead of ad-hoc offsets.
- [ ] Continue the object-system/compiler pass starting at `Module_BeginEnum` -> `Class_NextMethod` -> `Method_FindByIndex` -> `Symbol_LookupInModule` -> `Compiler_WriteHeaders` / `Compiler_MarkAndEmit`.
- [ ] Resolve remaining medium-confidence unit metadata bytes only after checking at least two independent signals.

---

## 14. Short glossary for this repo

- **public symbol**: a name present in `clash95.map`
- **semantic alias**: a recovered name that describes behavior better than the map or decompiler label
- **state block**: one contiguous group of globals functioning as a single runtime object
- **record family**: a repeated fixed-stride layout indexed by id or slot
- **compile fix**: change required for buildability, not yet for historical truth
- **portability seam**: intentionally non-original host glue that adapts old Win32/DirectDraw style code to the current repo runtime

---

## 15. File references to keep nearby while working

- `clash95.map`
- `clash95.asm`
- `clash95.c`
- `RECOVERED_STRUCTURES.json`
- `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md`
- `docs/archive/COMPILATION_PROGRESS.md`
- `platform_sdl.h`
- `platform_sdl_runtime.c`
- `compat/decomp_runtime_stubs.c`
- `CMakeLists.txt`

If you only keep one mental model while disassembling, keep this one:

> **Recover whole families and whole state blocks.**
> The project is already far enough along that isolated anonymous-function renames are usually less useful than one careful pass over a subsystem boundary.
