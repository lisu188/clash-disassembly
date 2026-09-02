#!/usr/bin/env python3

from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_source_index import scan_definitions

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/units/004115E0_00412BE0_units_002.c"
TEST = ROOT / "tests/unit/cases/test_cov10.c"

REPLACEMENTS = {
    "Unit_CheckLowMorale": r'''void  Unit_CheckLowMorale(_BYTE *stackPtr, double a2)
{
  UnitStackRecord *stack = (UnitStackRecord *)(void *)stackPtr;
  UnitStackRecord *stackCopy;
  UnitSlotRecord *slot;
  int anyDisbanded; // esi
  int slotIndex; // ebx
  int wasLowMorale; // eax
  int disbandRollMax; // eax
  char slotFlags; // dh
  int stackRow; // ebx
  int disbandedFlag; // ebx
  _BYTE v15[725]; // [esp+0h] [ebp-300h] BYREF
  int v16[3]; // [esp+2D8h] [ebp-28h]
  int v17[7]; // [esp+2E4h] [ebp-1Ch] BYREF

  qmemcpy(v15, stackPtr, UNIT_STACK_STRIDE);
  stackCopy = (UnitStackRecord *)(void *)v15;
  v17[0] = 0;
  anyDisbanded = 0;
  slot = stackCopy->unit_slots;
  slotIndex = 0;
  do
  {
    if ( slot->unit_type_id == -1 )
      break;
    if ( !slot->morale )
    {
      wasLowMorale = (slot->state_flags & UNIT_SLOT_FLAG_LOW_MORALE) != 0;
      slot->state_flags &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      disbandRollMax = wasLowMorale ? 200 : 100;
      if ( Rng_RandRange(0, disbandRollMax) < 0x32 )
      {
        if ( Rng_RandRange(0, 100) >= 0x32 )
        {
          anyDisbanded = 1;
          Debug_Log(0, slotIndex, (DWORD)(intptr_t)stackPtr, (int)(intptr_t)aUnit_checklo_0);
          slot->unit_type_id = -1;
          v17[0] = 1;
        }
        else
        {
          Debug_Log(0, slotIndex, (DWORD)(intptr_t)stackPtr, (int)(intptr_t)aUnit_checklowm);
          slotFlags = slot->state_flags;
          slot->current_action_points = 0;
          slot->state_flags = slotFlags | UNIT_SLOT_FLAG_LOW_MORALE;
        }
      }
    }
    ++slotIndex;
    ++slot;
  }
  while ( slotIndex < 10 );
  if ( anyDisbanded && *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * stack->owner_player_index + 140051) )
  {
    stackRow = stack->tile_row;
    UI_CenterWorldMapViewportOnRectIfFit(stackRow, stack->tile_column, stack->tile_column - 5, stackRow);
    v16[0] = (int)(intptr_t)g_Text_UnitDisbandedLowMoraleMessages[0];
    v16[1] = (int)(intptr_t)g_Text_UnitDisbandedLowMoraleMessages[1];
    v16[2] = (int)(intptr_t)g_Text_UnitDisbandedLowMoraleMessages[2];
    UI_ShowInfoWindow(v16[(unsigned __int8)g_LanguageIndex], 0, 0, (DWORD)(intptr_t)stackPtr, (int)(intptr_t)v17, (int)(intptr_t)&g_Text_UnitDisbandedLowMoraleMessages[3]);
    UI_StartWorldMapUnitAttentionFlash(
      *(unsigned __int16 *)(uintptr_t)(gameData + TILE_ROW_STRIDE * stack->tile_row + 2 * stack->tile_column + TILE_MAP_OFFSET),
      stack->tile_column,
      stack->tile_row);
    while ( UI_IsWorldMapUnitAttentionFlashActive() )
      WorldMap_RedrawFrame(stackRow);
  }
  disbandedFlag = v17[0];
  qmemcpy(stackPtr, v15, 0x2D4u);
  stackPtr[724] = v15[724];
  if ( disbandedFlag )
  {
    Unit_CompactSquad((__int16 *)stackPtr, 0, a2);
    Rules_LinkArmyFinalize((__int16 *)stackPtr, a2);
    Rules_LinkArmyFact((__int16 *)stackPtr, 0, 0, a2, 0, (DWORD)(intptr_t)stackPtr);
  }
}''',
    "UnitStack_ApplyPlagueAttritionToPeasantCargo": r'''signed int  UnitStack_ApplyPlagueAttritionToPeasantCargo(__int16 *stackPtr, DWORD a2, double a3)
{
  UnitStackRecord *stack = (UnitStackRecord *)(void *)stackPtr;
  UnitSlotRecord *slot;
  int anyRemoved; // esi
  int i; // ebx
  signed int result; // eax
  char attritionLoss; // al
  char newQuantity; // dl
  int v10; // edx
  int v11; // ecx

  slot = stack->unit_slots;
  anyRemoved = 0;
  for ( i = 0; i < 10; ++i )
  {
    result = slot->unit_type_id;
    if ( result == -1 )
      break;
    if ( result == UNIT_TYPE_PEASANT_CARGO && (slot->state_flags & UNIT_SLOT_FLAG_PLAGUE) != 0 )
    {
      attritionLoss = Rng_RandRange(15, 25);
      newQuantity = slot->current_health_percent - attritionLoss;
      result = newQuantity;
      slot->current_health_percent = newQuantity;
      if ( newQuantity <= 0 )
      {
        anyRemoved = 1;
        slot->unit_type_id = -1;
      }
    }
    ++slot;
  }
  if ( anyRemoved )
  {
    Unit_CompactSquad(stackPtr, (int)(intptr_t)slot, a3);
    Rules_LinkArmyFinalize(stackPtr, a3);
    if ( stack->unit_slots[0].unit_type_id != -1 )
      Rules_LinkArmyFact(stackPtr, v10, v11, a3, i, a2);
    return Rules_SyncArmyFactStrength(stackPtr, v10, v11, i, a2, a3);
  }
  return result;
}''',
}


def replace_definitions(text: str) -> str:
    definitions = {definition.name: definition for definition in scan_definitions(text, set(REPLACEMENTS))}
    missing = set(REPLACEMENTS) - set(definitions)
    if missing:
        raise SystemExit(f"missing definitions: {sorted(missing)}")
    for name, definition in sorted(definitions.items(), key=lambda item: item[1].start, reverse=True):
        text = text[:definition.start] + REPLACEMENTS[name] + text[definition.end:]
    return text


def main() -> int:
    source_text = SOURCE.read_text(encoding="utf-8")
    migrated = replace_definitions(source_text)
    if migrated == source_text:
        raise SystemExit("unit source migration made no changes")
    SOURCE.write_text(migrated, encoding="utf-8", newline="\n")

    test_text = TEST.read_text(encoding="utf-8")
    old = "TOUCH(Rules_FindFactByIndex());"
    new = "TOUCH(Rules_FindFactByIndex(0));"
    if test_text.count(old) != 1:
        raise SystemExit(f"expected one stale Rules_FindFactByIndex call, found {test_text.count(old)}")
    TEST.write_text(test_text.replace(old, new), encoding="utf-8", newline="\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
