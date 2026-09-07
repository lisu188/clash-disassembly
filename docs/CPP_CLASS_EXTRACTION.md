# C++ class extraction

This track recovers class-shaped code without converting uncertain binary layouts into speculative native C++ object models.

## Two different kinds of C++ types

### Original class seams

Treat a recovered family as an original-class candidate only when object evidence supports it. Strong signals include map-qualified methods, constructor/destructor families, vtable storage, `thiscall` calling convention, repeated member offsets, and Watcom C++ array-construction/destruction helpers.

An original-class candidate is still not permission to add native `virtual` methods, native pointer-sized fields, ownership, exceptions, RTTI, or automatic construction/destruction. Those changes can alter the 32-bit object layout and current low32 runtime contract.

### Modern views over recovered storage

Packed game-state records and low32 runtime objects can use non-owning C++ views even when the original type boundary is incomplete. Views may name proven fields and expose accessors, but they are adapters over existing bytes rather than claims about the original inheritance graph.

`UnitStackRecord`, `UnitSlotRecord`, `BattleUnitEntry`, and other generated packed records stay canonical in `RECOVERED_STRUCTURES.json` / `src/recovered_structs.h`. Do not duplicate them as unrelated native classes.

## First extracted seams

### `CAviDecompressorView`

`src/media/avi_decompressor_view.h` is the first new non-owning class view in this pass. The class family is unusually strong because `clash95.map` names the constructor and accessors directly, the recovered constructors allocate exactly 2236 bytes, the destructor family is present, and the accessor functions repeatedly read the same offsets.

The view currently exposes only fields supported by reached accessors and initialization code:

- stream scale at `+31`;
- stream rate at `+35`;
- frame count at `+43`;
- initialization-state words at `+7`, `+415`, `+1940`, and `+1944`;
- bitmap-header handle at `+151`;
- palette handle at `+1948`;
- decoded-frame index at `+2021`;
- accumulated sleep time at `+2038`;
- overlay and destination state at `+2050` and `+2062..+2075`;
- playing flag at `+2191`;
- frame-event handle at `+2196`;
- destruction dispatch handle at `+2232`.

Several offsets are intentionally unaligned. The view reads them with `memcpy`; replacing them with aligned native references or pointer casts would introduce undefined behavior on the host and would not describe the original packed layout honestly.

The view does not own the object and does not define native constructors, destructors, or virtual methods. Existing ABI-facing recovered functions remain the runtime entrypoints for this batch.

### `PathEntryLayout` / `PathEntryArrayLayout`

`src/core/path_entry_model.h` records the object-storage shape proven by the existing copy construction, destruction, growth, removal, vtable initialization, and 16-byte element stepping.

`PathEntryLayout` is 16 bytes. The embedded two-DWORD text holder at `+4` is supported by `Compat_StringHolderGetText` / `Compat_StringHolderCopyText` use and the `g_PathEntry_Vtable` assignments. The DWORDs at `+0` and `+12` remain deliberately generic because their higher-level meaning is not yet proven.

`PathEntryArrayLayout` is 20 bytes with the storage handle at `+0`, an unresolved DWORD at `+4`, element count at `+8`, capacity at `+12`, and vtable handle at `+16`. The count/capacity interpretation is supported by iteration bounds and `16 * capacity + 4` allocation behavior.

These are layout models, not a claim that the original compiler used the same modern C++ declaration syntax or inheritance graph.

## Candidate audit

Run:

```sh
python3 tools/audit_cpp_class_candidates.py
```

The audit ranks symbol families using class-shaped evidence: vtable mentions, constructor/destructor names, `thiscall`, Watcom array runtime helpers, family size, and cross-file presence. JSON output is available with `--json`.

The score is a review queue, not a proof threshold. A high score means the family deserves manual map/assembly/layout review before extraction.

## Next targets

1. Convert the small `CAviDecompressor` accessor family to use `CAviDecompressorView` after original-vs-recovered output comparison and manifest hash updates are prepared.
2. Recover a minimal write-capable AVI view for destination rectangle and overlay setters, keeping unaligned access explicit.
3. Review `DLXSpriteSet` from its map-confirmed load/save/draw method family.
4. Review `CSyncObject` only to the extent supported by its map-confirmed synchronization seam.
5. Continue typed `UnitStackRecord` / `UnitSlotRecord` adoption as record readability work, without misclassifying the strategic save-state slab as an original C++ class.
6. Use the audit to identify vtable/constructor/destructor clusters in render and media before touching broader CLIPS or gameplay families.

## Validation rules

- No behavior change is accepted solely to make code more object-oriented.
- No native `virtual` dispatch is introduced until the exact original object and vtable layout is proven and host-width-safe.
- Low32 handles stay 32-bit storage.
- Unaligned original fields use byte-safe loads/stores.
- Unknown fields keep neutral names.
- Existing free-function ABI remains until every cross-subsystem caller is understood.
- Canonical recovered function bodies require the normal split-manifest, compiler, original-instruction, unit, and runtime gates before migration to a class view.
