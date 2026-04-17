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
