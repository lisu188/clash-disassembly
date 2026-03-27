# Reverse Engineering Rename Log

## Batch 8 – Unit Stack Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_40F3C0 | UnitStack_IsIndexOnMap | Function | Unit Lifecycle | High | Walks the 200-column tile occupancy buffer at `gameData + 556374` to locate the stack id before reuse, proving it tests whether the stack id is already on the map. |
| sub_40F440 | UnitSlot_InitFromType | Function | Unit Lifecycle | High | Initializes a 31-byte slot entry with type id, owner, morale, action points, and veterancy from the per-unit tables, so it clearly seeds an individual unit slot. |
| sub_40F4D0 | UnitStack_ResetRecord | Function | Unit Lifecycle | High | Calls `UnitSlot_InitFromType` for the first slot, clears the remaining slots/path buffer, and stores the owner byte, matching a full reset of a stack record. |
| sub_40F7C0 | UnitStack_KillByIndex | Function | Unit Lifecycle | High | Thin wrapper that converts a stack index to its record pointer and forwards to `Unit_Kill`, so the rename documents that it kills stacks by index. |
| sub_40F800 | UnitStack_RemoveFromTile | Function | Unit Lifecycle | High | Validates row/column bounds, retracts army intel, zeros the tile entry, and updates fog-of-war, which is exactly the logic to remove a stack from its occupied tile. |
| sub_40F890 | UnitStack_UnlinkIfEmpty | Function | Unit Lifecycle | High | Checks whether the first slot’s unit type is -1 and, if so, calls `Rules_UnlinkArmyFact`; it only unlinks empty stacks. |
| sub_40F8B0 | UnitStack_GetVisionRadius | Function | Unit Lifecycle | Medium | Iterates every occupied slot, reads `byte_5125AE` for each unit type, and tracks the max value, yielding the stack’s vision range. |
| sub_40F900 | UnitStack_UpdateVision | Function | Unit Lifecycle | High | Uses the owning player id, stack tile, and `UnitStack_GetVisionRadius` to stamp fog-of-war via `sub_40EDE0`, so the rename reflects its vision-update role. |
| sub_40F9F0 | UnitStack_HasReadyUnits | Function | Unit Lifecycle | Medium | Scans up to 10 slots looking for bit0 set in the slot flag byte, returning 1 only if at least one squad member is marked ready — a readiness probe used in `Unit_NewTurn`. |
| sub_40FA20 | UnitStack_ClearReadyFlags | Function | Unit Lifecycle | Medium | Iterates every occupied slot and clears bit0 of the flag byte, which resets the per-turn “ready” state for the entire stack. |
| sub_40FA50 | UnitStack_SetReadyFlags | Function | Unit Lifecycle | Medium | Complement to the above that sets bit0 for each slot once the UI or turn logic re-enables the stack. |
| gameData + 147174 + 725 * index | UNIT_STACK(index) / UnitStackRecord | Recovered Struct | Unit Lifecycle | High | The code constantly adds 147174 + 725*index to reach stack entries (row, column, owner, slot array, path buffer). Exposing this as `UnitStackRecord` aligns with the per-stack macros and clarifies the recovered layout. |

## Deferred / Ambiguous
- *(none)*

## Batch 9 – Army Fact Wave
| Old Name / Pattern | New Name | Kind | Subsystem | Confidence | Evidence Summary |
|---|---|---|---|---|---|
| sub_40F6E0 | UnitStack_LinkArmyFact | Function | Unit Lifecycle | High | Wrapper invoked after stack creation and whenever an existing stack tile is re-linked; it passes the stack pointer and tile occupant id into the rules engine (`Rules_CreateArmyFact`) to register the squad in the fact database. |
| sub_4521D0 | Rules_CreateArmyFact | Function | Rules/Meta | High | Builds the "ODDZIAL" fact string, calls `Rules_AssertFact`, stores the returned handle at stack+721, and then calls `Rules_LinkArmyFact`; behavior matches an army-fact creation helper rather than an anonymous subroutine. |
