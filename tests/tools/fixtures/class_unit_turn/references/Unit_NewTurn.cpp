signed int  Unit_NewTurn(int a1, char a2, DWORD a3, double a4)
{
  int stackPtr; // esi
  int slotIndex; // ebx
  int slotCursor; // edx
  int slotType; // ecx
  char actionPoints; // al
  unsigned int buildingIndex; // edx
  int buildingRecord; // ecx
  int nextStackOffset; // ecx
  int i; // [esp+0h] [ebp-20h]
  unsigned int stackIndex; // [esp+4h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)(intptr_t)aUnit_newturn);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
  stackIndex = 0;
  for ( i = 0; ; i += UNIT_STACK_STRIDE )
  {
    if ( *(__int16 *)(uintptr_t)(gameData + i + 147180) == -1 || *(unsigned __int8 *)(uintptr_t)(gameData + i + 147178) != g_CurrentPlayerIndex )
      goto LABEL_16;
    stackPtr = gameData + UNIT_STACK_TABLE_OFFSET + i;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_stack",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    UnitStack_AdjustFatigueByPredicate((__int16 *)(uintptr_t)stackPtr, -20, UnitSlot_CanRecoverFatigue, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_recover_fatigue",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(stackPtr + 4) + 140051) )
    {
      UnitStack_AdjustFatigueByPredicate((__int16 *)(uintptr_t)stackPtr, 10, UnitSlot_ShouldGainFatigueFromLowActionPoints, 0xFFFFFFFF, a4);
      UnitStack_AdjustMoraleByPredicate((__int16 *)(uintptr_t)stackPtr, -1, UnitSlot_HasSevereFatigue, 0xFFFFFFFF, a4);
    }
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_human_fatigue",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    UnitStack_ClearSpentTurnFlag(stackPtr);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_clear_spent",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      *(_DWORD *)(uintptr_t)(stackPtr + 316));
    slotIndex = 0;
    slotCursor = stackPtr;
    do
    {
      slotType = *(__int16 *)(uintptr_t)(slotCursor + 6);
      if ( slotType == -1 )
        break;
      if ( slotType < 0 || slotType >= UNIT_TYPE_COUNT )
      {
        *(_WORD *)(uintptr_t)(slotCursor + 6) = -1;
        break;
      }
      slotCursor += 31;
      actionPoints = UnitSlot_CalcActionPointsFromFatigue((__int16 *)(uintptr_t)(stackPtr + 6 + 31 * slotIndex++));
      *(_BYTE *)(uintptr_t)(slotCursor - 17) = actionPoints;
    }
    while ( slotIndex < 10 );
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ap",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    Rules_LinkArmyFact((__int16 *)(uintptr_t)stackPtr, slotCursor, slotType, a4, slotIndex, 0xFFFFFFFF);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_rules_fact",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    Unit_CheckLowMorale((_BYTE *)(uintptr_t)stackPtr, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_low_morale",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    UnitStack_ApplyPlagueAttritionToPeasantCargo((__int16 *)(uintptr_t)stackPtr, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_plague",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    if ( !UnitStack_HasReadyUnits(stackPtr) )
      goto LABEL_16;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ready_check",
      (int)stackIndex,
      *(__int16 *)(uintptr_t)stackPtr,
      *(__int16 *)(uintptr_t)(stackPtr + 2),
      slotIndex);
    buildingIndex = *(unsigned __int16 *)(uintptr_t)(gameData
                             + TILE_ROW_STRIDE * (unsigned __int8)*(_DWORD *)(uintptr_t)(stackPtr + 320)
                             + 2 * (unsigned __int8)BYTE1(*(_DWORD *)(uintptr_t)(stackPtr + 320))
                             + TILE_MAP_OFFSET)
       - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( buildingIndex <= 0x64 )
    {
      slotIndex = BUILDING_RECORD_SIZE * buildingIndex;
      buildingRecord = UNIT_RECORD(buildingIndex);
      if ( (unsigned int)*(char *)(uintptr_t)(buildingRecord + 4) < 4
        && *(__int16 *)(uintptr_t)(buildingRecord + 16) != -1
        && *(_BYTE *)(uintptr_t)(slotIndex + gameData + 509676) != UNIT_STACK_OWNER_INDEX(stackPtr) )
      {
        break;
      }
    }
    if ( *(_DWORD *)(uintptr_t)(stackPtr + 316) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_before_path",
        (int)stackIndex,
        *(__int16 *)(uintptr_t)stackPtr,
        *(__int16 *)(uintptr_t)(stackPtr + 2),
        *(_DWORD *)(uintptr_t)(stackPtr + 316));
      UnitStack_ExecuteQueuedPath(stackIndex, 0, slotIndex, 0xFFFFFFFF, a4);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_after_path",
        (int)stackIndex,
        *(__int16 *)(uintptr_t)stackPtr,
        *(__int16 *)(uintptr_t)(stackPtr + 2),
        *(_DWORD *)(uintptr_t)(stackPtr + 316));
    }
    else
      UnitStack_ClearReadyFlags(stackPtr);
LABEL_16:
    nextStackOffset = i + 725;
    slotIndex = stackIndex + 1;
    stackIndex = slotIndex;
    if ( slotIndex >= 500 )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
      return LogAllUnits(nextStackOffset, slotIndex, 0xFFFFFFFF);
    }
  }
  UnitStack_ClearReadyFlags(stackPtr);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done_enemy_contact", (int)stackIndex, *(__int16 *)(uintptr_t)stackPtr, *(__int16 *)(uintptr_t)(stackPtr + 2), slotIndex);
  return LogAllUnits(0, slotIndex, 0xFFFFFFFF);
}
