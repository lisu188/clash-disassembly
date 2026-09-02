# Human-readable C recovery

The readability track turns evidence-backed decompiler output into ordinary maintainable C without changing retail behavior.

## Rules

1. Prefer recovered structs and enums over raw offsets and magic numbers.
2. Keep unknown bytes explicitly unknown until evidence supports a semantic name.
3. Pin every recovered binary layout with `_Static_assert` checks for size and important offsets.
4. Rename locals and parameters only when data flow or call-site evidence supports the meaning.
5. Preserve original control flow unless a structured rewrite is demonstrably equivalent.
6. Keep SDL/platform adaptation separate from recovered gameplay semantics.
7. Validate readability changes with the existing build, unit, route, and frame-comparison gates appropriate to the touched code.

## Current first target: UnitStack

`src/units/unit_stack_record.h` introduces the first typed overlay for the 725-byte strategic unit-stack record. Only fields whose offsets are already established are named:

- `tile_row` at `+0`
- `tile_column` at `+2`
- `owner_index` at `+4`
- `facing` at `+5`
- ten 31-byte unit slots at `+6`
- the 404-byte queued-path region at `+316`

The remaining five bytes stay `unknown_tail`. Unit-slot internals remain opaque until their individual fields are migrated with equivalent evidence.

The migration is incremental: replace `int stackPtr`, `__int16 *stackPtr`, `UNIT_STACK_*` field macros, and raw `stack + offset` expressions with `UnitStackRecord *` access where doing so is layout-equivalent and does not alter ABI-facing function signatures prematurely.

### First migrated call sites

The first typed-access batch covers the pathing frontier in `src/units/00414390_00416750_units_004.c`:

- `Path_InsertBridgeCornerWaypoints`
- `Unit_MoveTrack`
- `Unit_MoveTrackNearTile`
- `Building_GenerateApproachTrack`
- `Building_GenerateNearApproachTrack`

These functions now obtain strategic stack position through `UnitStack_RecordAt()` and `stack->tile_row` / `stack->tile_column` instead of repeating 725-byte record arithmetic or raw `+0` / `+2` accesses. Existing ABI-facing signatures are deliberately retained; casts remain only at boundaries that have not yet been migrated.

`data/recovered_sources.json` retains the legacy body hashes and records the new canonical hashes for these readability-preserving bodies, so the split-source audit continues to detect unrelated drift.

## Readability audit

Run:

```sh
python3 tools/audit_c_readability.py
```

The audit counts common decompiler debt and ranks the highest-debt source files. It is a prioritization metric, not an acceptance gate: counts must never be reduced by speculative renaming or semantic rewrites.

## Next migration batches

1. Extend `UnitStackRecord` use through the remaining `src/units/` position/owner/facing accessors while preserving external signatures.
2. Recover typed fields inside `UnitStackSlotRecord` and pin each offset.
3. Introduce equivalent evidence-backed overlays for `Player` and `Building`.
4. Convert gameplay APIs to typed pointers only after all cross-subsystem call sites are understood.
5. Replace second-generation mechanical function names and decompiler locals after the underlying state model is stable.
