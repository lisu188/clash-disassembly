#!/usr/bin/env python3

from __future__ import annotations

import argparse
from pathlib import Path

SOURCE = Path("src/units/00414390_00416750_units_004.c")
INCLUDE_MARKER = "/* CLASH95_GENERATED_INCLUDES_END */\n"
TYPED_INCLUDE = '#include "unit_stack_record.h"\n'
MIGRATION_SENTINEL = "/* CLASH95_UNIT_STACK_READABILITY_MIGRATED */"


def replace_once(text: str, old: str, new: str, label: str) -> str:
    count = text.count(old)
    if count != 1:
        raise SystemExit(f"{label}: expected exactly one match, found {count}")
    return text.replace(old, new, 1)


def replace_first(text: str, old: str, new: str, label: str) -> str:
    count = text.count(old)
    if count < 1:
        raise SystemExit(f"{label}: expected at least one match, found {count}")
    return text.replace(old, new, 1)


def migrate(text: str) -> str:
    if MIGRATION_SENTINEL in text:
        return text

    if TYPED_INCLUDE not in text:
        text = replace_once(
            text,
            INCLUDE_MARKER,
            INCLUDE_MARKER + "\n" + TYPED_INCLUDE + MIGRATION_SENTINEL + "\n",
            "typed UnitStack include",
        )
    else:
        text = replace_once(
            text,
            TYPED_INCLUDE,
            TYPED_INCLUDE + MIGRATION_SENTINEL + "\n",
            "UnitStack migration sentinel",
        )

    text = replace_once(
        text,
        "int * Path_InsertBridgeCornerWaypoints(int stackRecord, char a2, int *pathBuffer)\n{\n  int scratch_path[101];",
        "int * Path_InsertBridgeCornerWaypoints(int stackRecord, char a2, int *pathBuffer)\n{\n  UnitStackRecord *stack;\n  int scratch_path[101];",
        "Path_InsertBridgeCornerWaypoints typed local",
    )
    text = replace_once(
        text,
        "  (void)a2;\n  if ( !pathBuffer || UnitStack_HasOnlyFlyingUnits(stackRecord) )",
        "  (void)a2;\n  stack = (UnitStackRecord *)(uintptr_t)stackRecord;\n  if ( !pathBuffer || UnitStack_HasOnlyFlyingUnits(stackRecord) )",
        "Path_InsertBridgeCornerWaypoints typed initialization",
    )
    text = replace_once(
        text,
        "  LOBYTE(scratch_waypoint) = *(_BYTE *)(uintptr_t)stackRecord;\n  BYTE1(scratch_waypoint) = *(_BYTE *)(uintptr_t)(stackRecord + 2);",
        "  LOBYTE(scratch_waypoint) = (unsigned __int8)stack->tile_row;\n  BYTE1(scratch_waypoint) = (unsigned __int8)stack->tile_column;",
        "Path_InsertBridgeCornerWaypoints start position",
    )
    text = text.replace(
        "UnitStack_GetTileMoveCostOrZero((__int16 *)(uintptr_t)stackRecord,",
        "UnitStack_GetTileMoveCostOrZero((__int16 *)stack,",
    )

    text = replace_once(
        text,
        "  __int16 *stackRecord; // [esp+78h] [ebp-8Ch]",
        "  UnitStackRecord *stackRecord; // recovered 725-byte strategic stack record",
        "Unit_MoveTrack typed stack local",
    )
    text = replace_once(
        text,
        "    stackRecord = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex_l + gameData + UNIT_STACK_TABLE_OFFSET);",
        "    stackRecord = UnitStack_RecordAt(stackIndex_l);",
        "Unit_MoveTrack typed stack lookup",
    )
    text = replace_once(
        text,
        "tileMoveCost = UnitStack_GetTileMoveCostFromMergedProfileOrZero(stackRecord, (intptr_t)mergedProfile, gridInitColumn++, gridInitRow);",
        "tileMoveCost = UnitStack_GetTileMoveCostFromMergedProfileOrZero((__int16 *)stackRecord, (intptr_t)mergedProfile, gridInitColumn++, gridInitRow);",
        "Unit_MoveTrack typed compatibility call",
    )
    text = replace_once(
        text,
        "pathResult = Path_InsertBridgeCornerWaypoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex_l, sourceRowByte, pathResult);",
        "pathResult = Path_InsertBridgeCornerWaypoints((int)(intptr_t)stackRecord, sourceRowByte, pathResult);",
        "Unit_MoveTrack typed bridge path call",
    )

    text = replace_once(
        text,
        "_DWORD * Unit_MoveTrackNearTile(int stackIndex, int targetRow, int a3, int targetColumn, DWORD a5)\n{\n  int stack_record;",
        "_DWORD * Unit_MoveTrackNearTile(int stackIndex, int targetRow, int a3, int targetColumn, DWORD a5)\n{\n  UnitStackRecord *stack;",
        "Unit_MoveTrackNearTile typed local",
    )
    text = replace_first(
        text,
        "  stack_record = UNIT_STACK(stackIndex);\n  source_row = UNIT_STACK_TILE_ROW(stack_record);\n  source_column = UNIT_STACK_TILE_COLUMN(stack_record);",
        "  stack = UnitStack_RecordAt(stackIndex);\n  source_row = stack->tile_row;\n  source_column = stack->tile_column;",
        "Unit_MoveTrackNearTile typed position",
    )

    text = replace_once(
        text,
        "int * Building_GenerateApproachTrack(int stackIndex, int buildingIndex, int a3, char a4, DWORD a5)\n{\n  int building_record;\n  int building_row;\n  int building_column;\n  int building_kind;\n  int stack_record;",
        "int * Building_GenerateApproachTrack(int stackIndex, int buildingIndex, int a3, char a4, DWORD a5)\n{\n  int building_record;\n  int building_row;\n  int building_column;\n  int building_kind;\n  UnitStackRecord *stack;",
        "Building_GenerateApproachTrack typed local",
    )
    text = replace_first(
        text,
        "  stack_record = UNIT_STACK(stackIndex);\n  source_row = UNIT_STACK_TILE_ROW(stack_record);\n  source_column = UNIT_STACK_TILE_COLUMN(stack_record);",
        "  stack = UnitStack_RecordAt(stackIndex);\n  source_row = stack->tile_row;\n  source_column = stack->tile_column;",
        "Building_GenerateApproachTrack typed position",
    )

    text = replace_once(
        text,
        "  int stackRecordIndex; // edx\n  int sourceColumn; // ebx",
        "  UnitStackRecord *stack;\n  int sourceColumn; // ebx",
        "Building_GenerateNearApproachTrack typed local",
    )
    old_near_block = """  /*
   * asm loc_415A4D (clash95.asm, sub_415970):
   *     mov  edx, [esp+30h+var_2C]   ; edx = stackIndex (param 1)
   *     call sub_40AEB0              ; WorldMap_DisableFrameRedraw -- Watcom
   *                                  ; register convention, pushes/pops edx
   *     lea  eax, [edx*8] / add eax, edx / shl eax, 4 / add eax, edx  ; 145*s
   *     mov  edx, eax / lea eax, [eax*4] / add eax, edx               ; 725*s
   *     mov  ecx, ds:gameData / add eax, ecx
   * i.e. gameData + UNIT_STACK_STRIDE(725) * stackIndex. The decompiler treated
   * edx as clobbered by the call, so `stackRecordIndex` was multiplied out of
   * an unassigned local and the unit-stack record was read from garbage.
   */
  WorldMap_DisableFrameRedraw();
  /* loc_415A4D: `mov edx,[esp+var_2C]` then edx*145 - the cursor is the stack
     index; IDA never initialised stackRecordIndex. */
  stackRecordIndex = stackIndex;
  stackRecordIndex *= 145;
  sourceColumn = *(__int16 *)(uintptr_t)(gameData + 5 * stackRecordIndex + 147176);
  rawPath = Unit_MoveTrack(stackIndex, *(__int16 *)(uintptr_t)(gameData + 5 * stackRecordIndex + UNIT_STACK_TABLE_OFFSET), SHIDWORD(buildingRowCol), sourceColumn, buildingKind, buildingRowCol);
"""
    new_near_block = """  /* 00415A4D computes gameData + 725 * stackIndex before reading
     the stack row and column. The typed overlay expresses that recovered layout
     directly while preserving the original call sequence. */
  WorldMap_DisableFrameRedraw();
  stack = UnitStack_RecordAt(stackIndex);
  sourceColumn = stack->tile_column;
  rawPath = Unit_MoveTrack(
              stackIndex,
              stack->tile_row,
              SHIDWORD(buildingRowCol),
              sourceColumn,
              buildingKind,
              (int)buildingRowCol);
"""
    text = replace_once(
        text,
        old_near_block,
        new_near_block,
        "Building_GenerateNearApproachTrack typed stack lookup",
    )

    return text


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    original = SOURCE.read_text(encoding="utf-8")
    migrated = migrate(original)

    if args.check:
        if MIGRATION_SENTINEL not in original or migrated != original:
            raise SystemExit("UnitStack readability migration is not applied")
        return

    if migrated != original:
        SOURCE.write_text(migrated, encoding="utf-8")


if __name__ == "__main__":
    main()
