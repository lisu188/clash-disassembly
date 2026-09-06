# Human-readable C++ recovery

The readability track turns evidence-backed decompiler output into ordinary maintainable C++ without changing retail behavior.

## Rules

1. Prefer recovered structs and enums over raw offsets and magic numbers.
2. Keep unknown bytes explicitly unknown until evidence supports a semantic name.
3. Pin every recovered binary layout with `CLASH95_STATIC_ASSERT` checks for size and important offsets.
4. Rename locals and parameters only when data flow or call-site evidence supports the meaning.
5. Preserve original control flow unless a structured rewrite is demonstrably equivalent.
6. Keep SDL/platform adaptation separate from recovered gameplay semantics.
7. Validate readability changes with the existing build, unit, route, and frame-comparison gates appropriate to the touched code.

## Current first target: UnitStack

The canonical typed model already lives in generated `src/recovered_structs.h`, sourced from `RECOVERED_STRUCTURES.json`. Readability work must reuse that model rather than create subsystem-local duplicate overlays.

The recovered `UnitStackRecord` is a packed 725-byte record with layout pins for:

- `tile_row` at `+0`
- `tile_column` at `+2`
- `owner_player_index` at `+4`
- `facing_direction` at `+5`
- ten typed `UnitSlotRecord` entries at `+6`
- typed `QueuedPathBuffer` at `+316`
- `is_hidden_on_world_map` at `+720`
- four unrecovered tail bytes at `+721..+724`

`UnitSlotRecord` is also already partially recovered: unit type, owner, action points, health, fatigue, morale, stance/state flags and selected runtime state fields have pinned offsets. Unknown spans remain explicit byte arrays.

The migration is incremental: replace `int stackPtr`, `__int16 *stackPtr`, `UNIT_STACK_*` field macros, and raw `stack + offset` expressions with `UnitStackRecord *` and `UnitSlotRecord *` access where doing so is layout-equivalent. ABI-facing signatures stay unchanged until all cross-subsystem callers are understood.

`UNIT_STACK_RECORD(index)` is the common typed view of a strategic stack table entry. `UNIT_SLOT_FLAG_READY` names the previously raw bit used symmetrically by the ready-state readers and writers.

### Pathing batch

The first typed-access batch covers the pathing frontier in `src/units/00414390_00416750_units_004.cpp`:

- `Path_InsertBridgeCornerWaypoints`
- `Unit_MoveTrack`
- `Unit_MoveTrackNearTile`
- `Building_GenerateApproachTrack`
- `Building_GenerateNearApproachTrack`

These functions obtain strategic stack position through `UnitStackRecord` and `stack->tile_row` / `stack->tile_column` instead of repeating 725-byte record arithmetic or raw `+0` / `+2` accesses. Existing ABI-facing signatures are deliberately retained; casts remain only at boundaries that have not yet been migrated.

### Core unit batch

The second batch converts the reached core unit paths in `src/units/0040F510_00411560_units_001.cpp`:

- stack allocation and initialization in `Unit_Create`
- army-fact link/unlink helpers
- unit-stack kill and tile removal
- empty-stack detection
- stack vision radius and reveal propagation
- ready-flag query/set/clear using typed `UnitSlotRecord::state_flags`
- camera centering from typed stack coordinates
- fatigue-based action-point calculation using `UnitSlotRecord::unit_type_id` and `fatigue`

The old `145 * 5`, `+6`, `+10`, `+13`, 31-byte slot stepping, and equivalent raw record expressions are removed from these functions where a pinned field already exists. The original loops, termination conditions and ABI-facing calls remain intact.

`data/recovered_sources.json` records the new canonical hashes for readability-preserving function bodies, and `src/recovered_layout.h` is regenerated when a new recovered constant is named. The split-source audit therefore continues to detect unrelated drift.

## Validation

The first pathing batch compiles and links successfully under both GCC 13 and Clang 18. The repository's current `main` baseline still fails later CI gates for the pre-existing generated-header surface ratchet, compiler-warning ratchet and split-unit harness debt; those failures are tracked separately from readability work.

## Readability audit

Run:

```sh
python3 tools/audit_c_readability.py
```

The audit counts common decompiler debt and ranks the highest-debt source files. It is a prioritization metric, not an acceptance gate: counts must never be reduced by speculative renaming or semantic rewrites.

## Next migration batches

1. Continue through the remaining `src/units/` functions that manually step `UnitSlotRecord` at 31-byte intervals.
2. Replace remaining raw position/owner/facing accesses across `world/`, `buildings/` and `strategic/` with the canonical `UnitStackRecord` view.
3. Extend the same approach to the existing typed `PlayerRuntimeState` and building overlays.
4. Convert gameplay APIs to typed pointers only after all cross-subsystem call sites are understood.
5. Replace second-generation mechanical function names and decompiler locals after the underlying state model is stable.
