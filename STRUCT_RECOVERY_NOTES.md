# Structure recovery notes

This batch does not reopen the major recovered state slabs. The current executable-regeneration work is building on them, not replacing them.

## Stable state blocks already good enough to build on

- `BattleRuntimeState`
- `BattlePathingTables`
- `BuildingGarrisonDialogState`
- `CastleProductionPanelState`
- `InputBackendState`
- `MiniMapState`
- `TooltipBackdropState`
- `UnitStackSelectionState`

These already exist in `RECOVERED_STRUCTURES.json` and remain the canonical typed state clusters for the recovered C baseline.

## Why there was no JSON churn this batch

- The current batch is about making the executable path explicit and adding the first conservative C++ class seams.
- The most evidence-rich new lift this round is class-oriented:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- None of those required tightening `RECOVERED_STRUCTURES.json` yet because the C++ wrappers are still raw-handle views rather than committed ABI/layout claims.

## Latest structure maintenance

- `BuildingSpriteCacheEntry` remains the same 50-entry, 13-byte cache record, but the C backing storage now reflects that evidence directly: `byte_5438E8[650]` owns the slab and the nearby key/handle/timestamp labels are offset aliases inside it.
- This was a host-layout correction, not a new semantic field claim. The change prevents the recovered cache reset/load paths from overlapping `dword_543CC8` in the x86-64 executable.

## Latest direct-game liveness maintenance

- No recovered structure JSON changes were needed for the latest direct `a` route step.
- The new fill helper is a reached render-surface host-width repair for `sub_416850`, not a new state layout or field claim.

## Latest world-map action-widget maintenance

- `RECOVERED_STRUCTURES.json` now records `WorldMapActionWidgetRecord`.
- This is a real structure update: the weak symbols around `dword_511D40` were not independent globals, but one packed 0x35-byte table with six world-map action records plus a terminator.
- The record layout reuses the already recovered menu-button field order, but this table has a distinct owner and button set: map mode, next unit, next building, join units, building, and ambush.
- The building-button action callback remains quarantined in C until the authentic building/treasure-placement link surface is recovered; that quarantine does not change the record layout evidence.

## Latest minimap table maintenance

- `RECOVERED_STRUCTURES.json` now records `MiniMapTerrainColorTableFamily`.
- This is a real storage/layout update: `byte_523350`, `unk_523750`, and `unk_523B50` are three adjacent 0x400-byte terrain-color tables, not standalone one-byte weak globals.
- The evidence comes from `sub_40CE70` asm offsets up through `+0x303` and from the live `/A0` crash where the undersized C globals let minimap fills overwrite the terrain movement offset table.
- The helper repair is host-width containment, not a new gameplay semantic claim: `MiniMap_DrawTileCell` now writes into the recovered linear software surface directly because the original minimap surface uses compact 32-bit vtable entries.

## Latest unit-stack maintenance

- `RECOVERED_STRUCTURES.json` keeps the existing `UnitStackRecord` and `UnitSlotRecord` layouts.
- The latest `/A0` fix strengthens the existing evidence rather than adding a new structure: `Unit_AddToGroup` copies `source_count * 31` bytes from `source_stack + 6` into `target_stack + 6 + target_count * 31`, matching the documented ten-slot `UnitSlotRecord[10]` layout.
- `Unit_Kill` also corroborates the same stack layout by clearing slot type words at `stack + 6` with a `31`-byte stride after removing the stack from `TILE_INDEX(row, column)`.
- No new field names were promoted; the third `Unit_AddToGroup` argument and the deeper rules fact failure remain under-labeled runtime behavior rather than structure claims.

## Latest CTest maintenance

- No `RECOVERED_STRUCTURES.json` change was needed for the direct `/A0` CTest promotion.
- The new tests cover the already-recorded scenario-start and unit-stack liveness milestone; they do not add new structure layout evidence or new field semantics.

## What is ready for typed C++ views now

- `DLXSpriteSet`
  - map-confirmed method family
  - good wrapper candidate
  - not yet a full layout claim
- `CAviDecompressor`
  - map-confirmed ctor/dtor/accessor family
  - strong class seam
  - still needs tighter internal-field recovery before a full layout struct is honest
- `CSyncObject`
  - unlock seam is map-confirmed
  - current evidence only supports a minimal raw-handle class view

## Near-term structure work that would materially help the executable path

1. Tighten the `CAviDecompressor` raw layout using the accessor family.
2. Continue freezing high-value `BattleRuntimeState` fields around actor selection and per-side turn state.
3. Finish the remaining ambiguous renderer/animation bytes in `BuildingGarrisonDialogState` when those paths block executable progress.
4. Keep `InputBackendState` as the typed landing zone for backend cleanup instead of re-splitting it into loose globals.

## Latest low32 allocator maintenance

- `RECOVERED_STRUCTURES.json` now records `CompatLow32ArenaBlock` as a host runtime allocator record.
- This is not an original gameplay structure claim: it documents the current compatibility allocation shape needed to keep preserved 32-bit pointer storage viable during direct `/A0` startup.
- The latest `/A0` fixes also strengthen the existing `UnitStackRecord` / `UnitSlotRecord` evidence through recovered slot predicate and sentinel handling, but they do not add new fields or rename any ambiguous top-bit/status lanes.

## Latest world-view theme maintenance

- `RECOVERED_STRUCTURES.json` now records `WorldViewState.map_theme_index` at `gameData + 140016`.
- This field is not a new unit/stat semantic claim. It is the shared world-map theme selector used by `PlayGame` for `backgr1/2/3.s32`, `treemas1/2/3.s32`, and main-map music selection, and it corroborates the earlier minimap terrain-color table selector evidence.
- The exact designer-facing labels for values `0`, `1`, and `2` remain deferred; current naming intentionally stops at the implementation-proven theme selector role.

## Latest minimap frame maintenance

- `RECOVERED_STRUCTURES.json` now notes that `MiniMap_CreateSurface` draws sprite char `4` as the minimap frame after allocating the backing surface.
- This strengthens the existing `MiniMapState` evidence only; it does not add a new struct field.
- The generic `sub_402E80` sprite decoder remains broader than this evidence. Current recovery covers the unclipped format-0 minimap frame call shape only.

## Latest SIGTERM teardown maintenance

- No new original gameplay structure or unit/stat layout was promoted for the SIGTERM teardown guard.
- `RECOVERED_STRUCTURES.json` now records one additional render-wrapper evidence note: after `Render_BeginModeSwitch` clears the primary compact handle, a `Render_FillRect` primary fallback with no companion and no handle has no recoverable copy target.
- This is host/runtime containment around the existing render-surface record, not a new field claim.
