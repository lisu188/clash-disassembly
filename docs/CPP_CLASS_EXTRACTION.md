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

`CAviDecompressorMutableView` adds only the reached writes already present in `CAviDecompressor_InitOverlays`, `CAviDecompressor_InitPos`, and `CAviDecompressor_InitRect`. It preserves their field widths and write order and uses `memcpy` stores for the unaligned destination rectangle.

Neither AVI view owns the object or defines native constructors, destructors, or virtual methods. Existing ABI-facing recovered functions remain the runtime entrypoints for this batch.

### `PathEntryLayout` / `PathEntryArrayLayout`

`src/core/path_entry_model.h` records the object-storage shape proven by the existing copy construction, destruction, growth, removal, vtable initialization, and 16-byte element stepping.

`PathEntryLayout` is 16 bytes. The embedded two-DWORD text holder at `+4` is supported by `Compat_StringHolderGetText` / `Compat_StringHolderCopyText` use and the `g_PathEntry_Vtable` assignments. The DWORDs at `+0` and `+12` remain deliberately generic because their higher-level meaning is not yet proven.

`PathEntryArrayLayout` is 20 bytes with the storage handle at `+0`, an unresolved DWORD at `+4`, element count at `+8`, capacity at `+12`, and vtable handle at `+16`. The count/capacity interpretation is supported by iteration bounds and `16 * capacity + 4` allocation behavior.

These are layout models, not a claim that the original compiler used the same modern C++ declaration syntax or inheritance graph.

### `DLXSpriteSetView`

`src/render/dlx_sprite_set_view.h` models the map-confirmed `DLXSpriteSet` object as a non-owning 32-bit storage view. `DLXSpriteSet_Load`, destroy/copy construction, save, character lookup, and release all corroborate the same trailing metadata layout.

The proven object footprint is 4112 bytes: sprite handles occupy the leading DWORD table, followed by the data-buffer handle at byte `4096`, entry count at `4100`, file size at `4104`, and vtable handle at `4108`. The loader's recovered loop admits at most 1023 directory entries. `DLXSpriteSet_GetLastCharIndex` intentionally reads the low 16 bits of the entry-count field; the view preserves that behavior through `serializedEntryCount()` rather than silently widening it.

`DLXSpriteSetMutableView` provides explicit writes for sprite handles and the four proven trailing fields. It does not allocate or free anything; the recovered load/copy/destroy functions still own those lifecycle contracts.

Neither DLX view claims ownership of sprite handles or the backing data allocation. Destruction and copying remain in the recovered ABI functions until their exact allocation and flag contracts are migrated with original-backed tests.

### `WCIsvListBaseView`

`src/buildings/wcisv_list_view.h` reuses the existing `WCCompatListBase` and `WCCompatLink` layouts instead of introducing duplicate storage. This family has stronger original-class evidence than the generic game-state records: `clash95.map` names `WCIsvListBase` methods directly, the recovered ctor/dtor variants establish the object lifecycle and vtable transitions, and the basic list operations independently consume the same fields.

The recovered list object is exactly 24 bytes:

- head link handle at `+0`;
- vtable handle at `+4`;
- tail link handle at `+8`;
- element count at `+12`;
- allocator callback handle at `+16`;
- deallocator callback handle at `+20`.

Each link node is exactly 8 bytes with the next-link handle at `+0` and stored value at `+4`. `WCIsvListBase_AllocLinkNode` allocates eight bytes, `base_insert` and `base_sget` maintain head/tail/count, `AppendValue` and `PopFrontValue` use the node value, and `ReleaseLinkNode` independently consumes the deallocator field at `+20`.

`WCIsvListBaseView` and `WCIsvListBaseMutableView` are non-owning views over those already-recovered bytes. They do not replace the existing allocation, destruction, list traversal, or virtual-dispatch functions. The compatibility storage remains authoritative until a separately validated body migration is performed.

## Candidate audit

Run:

```sh
python3 tools/audit_cpp_class_candidates.py
```

The audit ranks symbol families using class-shaped evidence: vtable mentions, constructor/destructor names, `thiscall`, Watcom array runtime helpers, family size, and cross-file presence. JSON output is available with `--json`.

The score is a review queue, not a proof threshold. A high score means the family deserves manual map/assembly/layout review before extraction.

## Next targets

1. Convert the small `CAviDecompressor` accessor family to use `CAviDecompressorView` after original-vs-recovered output comparison and manifest hash updates are prepared.
2. Migrate `CAviDecompressor_InitOverlays`, `CAviDecompressor_InitPos`, and `CAviDecompressor_InitRect` to `CAviDecompressorMutableView` in the same separately validated body-change campaign.
3. Use `DLXSpriteSetView` / `DLXSpriteSetMutableView` to drive a separately validated cleanup of the load/save/get-character family without changing ownership semantics.
4. Migrate the bounded `WCIsvListBase` basic helpers (`base_next`, `base_insert`, `base_sget`, allocation/release, append/pop) to the typed view after original-backed equivalence checks.
5. Keep `CSyncObject` deferred until more than the map-confirmed `Unlock` seam and current placeholder storage are recovered.
6. Continue typed `UnitStackRecord` / `UnitSlotRecord` adoption as record readability work, without misclassifying the strategic save-state slab as an original C++ class.

## Validation rules

- No behavior change is accepted solely to make code more object-oriented.
- No native `virtual` dispatch is introduced until the exact original object and vtable layout is proven and host-width-safe.
- Low32 handles stay 32-bit storage.
- Unaligned original fields use byte-safe loads/stores.
- Unknown fields keep neutral names.
- Existing free-function ABI remains until every cross-subsystem caller is understood.
- Canonical recovered function bodies require the normal split-manifest, compiler, original-instruction, unit, and runtime gates before migration to a class view.
