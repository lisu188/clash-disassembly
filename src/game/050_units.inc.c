/* Strategic units, stacks, movement, fatigue, morale, and path execution.
 * Original function-marker range: 0x0040F510..0x0041C8B0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (0040F510) --------------------------------------------------------
signed int  Unit_Create(a1, a2, a3, a4, a5)
unit_type a1;
int a2;
int a3;
char a4;
int a5;
{
  int v7; // esi
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // esi
  int v12; // ecx
  int v13; // edi
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  v7 = 0;
  Debug_Log(a3, a4, a1, (int)aUnit_createDDD);
  v8 = 0;
  v9 = 0;
  do
  {
    v10 = *(__int16 *)(gameData + v9 + 147180);
    if ( v10 == -1 )
      v8 = 1;
    v9 += 725;
    ++v7;
  }
  while ( v9 < 362500 && !v8 );
  v11 = v7 - 1;
  if ( v8 )
  {
    if ( UnitStack_IsIndexOnMap(v11) )
      Debug_Log(v12, a4, a1, (int)aUnit_createErr);
    v13 = (int)UNIT_STACK(v11);
    v14 = 200 * a3 + gameData;
    if ( *(unsigned __int16 *)(v14 + 2 * a5 + 556374) == 0xFFFF )
    {
      if ( a1 == -1 || Map_GetUnitTileMoveCostOrZero(a1, a2, a5, a3) )
      {
        UnitStack_ResetRecord(v13, a1, a2);
        UNIT_STACK_TILE_ROW(v13) = a3;
        UNIT_STACK_TILE_COLUMN(v13) = a5;
        UNIT_STACK_FACING(v13) = a4;
        v16 = gameData;
        *(_WORD *)(TILE_INDEX(a3, a5)) = v11;
        UnitStack_UpdateVision(v11);
        Rules_CreateArmyFact((__int16 *)v13, v11, v16, a2, a1);
        Debug_Log(v17, a2, a1, (int)aUnit_createOk0);
        return 1;
      }
      else
      {
        Debug_Log(v15, a3, a1, (int)aUnit_createE_2);
        return 0;
      }
    }
    else
    {
      Debug_Log(v14, a4, a1, (int)aUnit_createE_1);
      return 0;
    }
  }
  else
  {
    Debug_Log(v10, a4, a1, (int)aUnit_createE_0);
    return 0;
  }
}
// 40F510: could not find valid save-restore pair for ebx
// 40F56A: variable 'v8' is possibly undefined
// 40F586: variable 'v12' is possibly undefined
// 40F678: variable 'v17' is possibly undefined
// 40F6C3: variable 'v15' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0040F6E0) --------------------------------------------------------
unsigned int  UnitStack_LinkArmyFact(__int16 *a1, char a2, DWORD a3)
{
  return Rules_CreateArmyFact(a1, *(unsigned __int16 *)(TILE_INDEX(*a1, a1[1])), (int)a1, a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (0040F730) --------------------------------------------------------
int  Unit_Kill(int a1, char a2, DWORD a3, double a4)
{
  int row;
  int column;
  int slot_ordinal;
  _WORD *slot_type;

  Debug_Log(a1, a2, a3, (int)aUnit_kill0x08x);
  Unit_DebugDumpFormationSizes(a1, a3);
  Rules_RetractArmyFact((_DWORD *)a1, 0, a1, a4);
  row = UNIT_STACK_TILE_ROW(a1);
  column = UNIT_STACK_TILE_COLUMN(a1);
  Diagnostics_TraceWorldMapActionEvent(
    "unit_kill",
    Diagnostics_UnitStackIndexFromRecord(a1),
    row,
    column,
    Unit_GetSquadCount(a1));
  *(_WORD *)(TILE_INDEX(row, column)) = -1;
  slot_ordinal = 1;
  slot_type = (_WORD *)UNIT_STACK_SLOT(a1, 0);
  do
  {
    ++slot_ordinal;
    *slot_type = -1;
    slot_type = (_WORD *)((char *)slot_type + UNIT_STACK_SLOT_STRIDE);
  }
  while ( slot_ordinal < UNIT_STACK_SLOT_COUNT );
  MiniMap_DrawTileCell((void *)row, column);
  return MiniMap_RedrawTileRect(row, column, column, row);
}
// 5202E4: using guessed type int gameData;

//----- (0040F7C0) --------------------------------------------------------
int  UnitStack_KillByIndex(int stackIndex, char killReason, DWORD a3, double a4)
{
  return Unit_Kill((int)UNIT_STACK(stackIndex), killReason, a3, a4);
}

//----- (0040F800) --------------------------------------------------------
__int16 * UnitStack_RemoveFromTile(__int16 *stack, double a2)
{
  int stackPtr; // ecx
  int row; // edx
  int column; // edx

  stackPtr = (int)stack;
  row = UNIT_STACK_TILE_ROW(stackPtr);
  if ( row >= 0 && row <= *(_DWORD *)(gameData + 140000) - 1 )
  {
    column = UNIT_STACK_TILE_COLUMN(stackPtr);
    if ( column >= 0 && column <= *(_DWORD *)(gameData + 140004) - 1 )
    {
      Rules_RetractArmyFact((_DWORD *)stackPtr, column, stackPtr, a2);
      *(_WORD *)(TILE_INDEX(row, column)) = -1;
      MiniMap_DrawTileCell((void *)row, column);
      return (__int16 *)MiniMap_RedrawTileRect(row, column, column, row);
    }
  }
  return stack;
}

__int16 * Rules_UnlinkArmyFact(__int16 *result, double a2)
{
  return UnitStack_RemoveFromTile(result, a2);
}
// 40F83A: variable 'v5' is possibly undefined
// 40F87B: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0040F890) --------------------------------------------------------
__int16 * UnitStack_UnlinkIfEmpty(__int16 *result, double a2)
{
  if ( result[3] == -1 )
    return Rules_UnlinkArmyFact(result, a2);
  return result;
}

__int16 * Rules_LinkArmyFinalize(__int16 *result, double a2)
{
  return UnitStack_UnlinkIfEmpty(result, a2);
}

//----- (0040F8B0) --------------------------------------------------------
int  UnitStack_GetVisionRadius(int a1)
{
  int v1; // edx
  __int16 *v2; // eax
  int v3; // ebx
  int i; // edx
  int v5; // ecx
  int v6; // ecx

  v1 = 88 * *(__int16 *)(a1 + 6);
  v2 = (__int16 *)(a1 + 37);
  v3 = (unsigned __int8)g_UnitTypeVisionRadius[v1];
  for ( i = 1; i < 10; ++i )
  {
    v5 = *v2;
    if ( v5 == -1 )
      break;
    v6 = (unsigned __int8)g_UnitTypeVisionRadius[88 * v5];
    if ( v6 > v3 )
      v3 = v6;
    v2 = (__int16 *)((char *)v2 + 31);
  }
  return v3;
}

//----- (0040F900) --------------------------------------------------------
signed int  UnitStack_UpdateVision(int stackIndex)
{
  int stackPtr; // esi
  int originRow; // edi
  int originColumn; // ebx
  int radius; // ebp
  int previousPlayer; // ecx
  int updated; // edx
  int row; // ecx
  int column; // eax

  stackPtr = (int)UNIT_STACK(stackIndex);
  if ( *(__int16 *)UNIT_STACK_SLOT(stackPtr, 0) == -1 )
    return 0;
  originRow = UNIT_STACK_TILE_ROW(stackPtr);
  originColumn = UNIT_STACK_TILE_COLUMN(stackPtr);
  radius = UnitStack_GetVisionRadius(stackPtr);
  previousPlayer = g_CurrentPlayerIndex;
  g_CurrentPlayerIndex = UNIT_STACK_OWNER_INDEX(stackPtr);
  updated = 0;
  for ( row = originRow - radius; row < originRow + radius; ++row )
  {
    for ( column = originColumn - radius; column < originColumn + radius; ++column )
    {
      int distance = (column - originColumn) * (column - originColumn)
                   + (row - originRow) * (row - originRow);
      if ( Math_CeilSqrt(distance) <= radius && Map_RevealTileWithPropagation(row, column, g_CurrentPlayerIndex) )
        updated = 1;
    }
  }
  g_CurrentPlayerIndex = previousPlayer;
  return updated;
}

//----- (0040F9F0) --------------------------------------------------------
signed int  UnitStack_HasReadyUnits(int stackPtr)
{
  char *slotPtr; // edx
  int slotIndex; // ecx

  slotPtr = (char *)UNIT_STACK_SLOT(stackPtr, 0);
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    if ( *(_WORD *)slotPtr == -1 )
      return 0;
    if ( (slotPtr[13] & 1) != 0 )
      return 1;
    slotPtr += UNIT_STACK_SLOT_STRIDE;
  }
  return 0;
}

//----- (0040FA20) --------------------------------------------------------
__int16 * UnitStack_ClearReadyFlags(int stackPtr)
{
  char *slotPtr; // edx
  int slotIndex; // ecx

  slotPtr = (char *)UNIT_STACK_SLOT(stackPtr, 0);
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    if ( *(_WORD *)slotPtr == -1 )
      break;
    slotPtr[13] &= ~1u;
    slotPtr += UNIT_STACK_SLOT_STRIDE;
  }
  return (__int16 *)stackPtr;
}

//----- (0040FA50) --------------------------------------------------------
__int16 * UnitStack_SetReadyFlags(int stackPtr)
{
  char *slotPtr; // edx
  int slotIndex; // ecx

  slotPtr = (char *)UNIT_STACK_SLOT(stackPtr, 0);
  for ( slotIndex = 0; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
  {
    if ( *(_WORD *)slotPtr == -1 )
      break;
    slotPtr[13] |= 1u;
    slotPtr += UNIT_STACK_SLOT_STRIDE;
  }
  return (__int16 *)stackPtr;
}

//----- (0040FA80) --------------------------------------------------------
signed int  Facing_DirectionFromDelta8(int a1, int a2)
{
  if ( a1 <= 0 )
  {
    if ( a1 < 0 )
    {
      if ( a2 < 0 )
      {
        return 7;
      }
      else if ( a2 )
      {
        return 5;
      }
      else
      {
        return 6;
      }
    }
    else if ( a2 < 0 )
    {
      return 0;
    }
    else
    {
      return 4;
    }
  }
  else if ( a2 < 0 )
  {
    return 1;
  }
  else if ( a2 )
  {
    return 3;
  }
  else
  {
    return 2;
  }
}

//----- (0040FAD0) --------------------------------------------------------
int  Camera_CenterOnUnit(int a1)
{
  int v1; // eax
  int v2; // ebx
  int v3; // esi

  v1 = 725 * a1;
  *(_DWORD *)(gameData + 140008) = *(__int16 *)(gameData + v1 + 147174) - 4;
  *(_DWORD *)(gameData + 140012) = *(__int16 *)(gameData + v1 + 147176) - 3;
  if ( *(int *)(gameData + 140008) < 0 )
    *(_DWORD *)(gameData + 140008) = 0;
  if ( *(int *)(gameData + 140012) < 0 )
    *(_DWORD *)(gameData + 140012) = 0;
  v2 = *(_DWORD *)(gameData + 140000);
  if ( *(_DWORD *)(gameData + 140008) + 9 > v2 )
    *(_DWORD *)(gameData + 140008) = v2 - 9;
  v3 = *(_DWORD *)(gameData + 140004);
  if ( *(_DWORD *)(gameData + 140012) + 7 > v3 )
    *(_DWORD *)(gameData + 140012) = v3 - 7;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;

//----- (0040FDB0) --------------------------------------------------------
int  UnitSlot_CalcActionPointsFromFatigue(__int16 *a1)
{
  int unit_type; // eax
  int v2; // ecx
  int result; // eax
  int v4; // ecx

  unit_type = *a1;
  if ( unit_type < 0 || unit_type >= UNIT_TYPE_COUNT )
    return 0;
  v2 = *((char *)a1 + 10);
  result = (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unit_type];
  if ( v2 >= 80 && v2 <= 89 )
    return (192 * result - (__CFSHL__((192 * result) >> 31, 8) + ((192 * result) >> 31 << 8))) >> 8;
  v4 = *((char *)a1 + 10);
  if ( v4 >= 90 && v4 <= 99 )
    return ((result << 7) - (__CFSHL__(result << 7 >> 31, 8) + (result << 7 >> 31 << 8))) >> 8;
  if ( *((_BYTE *)a1 + 10) == 100 )
    return 0;
  return result;
}

//----- (0040FE60) --------------------------------------------------------
int  UnitSlot_GetBaseActionPoints(__int16 *a1)
{
  return (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * *a1];
}

//----- (0040FE80) --------------------------------------------------------
int  UnitStack_GetMinBaseActionPoints(int a1)
{
  __int16 *slot_record; // edx
  int min_base_action_points; // ebx
  int slot_base_action_points; // eax
  int slot_index; // ecx

  min_base_action_points = UnitSlot_GetBaseActionPoints((__int16 *)(a1 + UNIT_STACK_SLOT_BASE_OFFSET));
  slot_record = (__int16 *)(a1 + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE);
  slot_index = 1;
  while ( slot_index < UNIT_STACK_SLOT_COUNT )
  {
    if ( *slot_record == -1 )
      break;
    slot_base_action_points = UnitSlot_GetBaseActionPoints(slot_record);
    if ( slot_base_action_points < min_base_action_points )
      min_base_action_points = slot_base_action_points;
    slot_record = (__int16 *)((char *)slot_record + UNIT_STACK_SLOT_STRIDE);
    ++slot_index;
  }
  return min_base_action_points;
}

//----- (0040FEC0) --------------------------------------------------------
__int16 * UnitStack_ClearRemainingActionPoints(__int16 *result, DWORD a2, double a3)
{
  __int16 *v3; // ebx
  __int16 *v4; // eax
  int i; // edx
  int v6; // ecx

  v3 = result;
  if ( result )
  {
    v4 = result + 3;
    for ( i = 0; i < 10; ++i )
    {
      v6 = *v4;
      if ( v6 == -1 )
        break;
      v4 = (__int16 *)((char *)v4 + 31);
      *((_BYTE *)v4 - 23) = 0;
    }
    return (__int16 *)Rules_LinkArmyFact(v3, i, v6, a3, (char)v3, a2);
  }
  return result;
}

//----- (0040FEF0) --------------------------------------------------------
signed int WorldMap_HandleViewportScrollKeys()
{
  int v0; // edx
  int v2; // ecx
  int v3; // ebx
  int v4; // esi
  int v5; // ecx

  if ( Input_IsKeyPressed(203) )
  {
    v0 = *(_DWORD *)(gameData + 140008);
    if ( v0 > 0 )
    {
      *(_DWORD *)(gameData + 140008) = v0 - 1;
LABEL_4:
      WorldMap_RedrawViewport(1);
      dword_5202F0 = 1;
      return 1;
    }
  }
  if ( Input_IsKeyPressed(205) && (v2 = *(_DWORD *)(gameData + 140008), *(_DWORD *)(gameData + 140000) - 9 > v2) )
  {
    *(_DWORD *)(gameData + 140008) = v2 + 1;
    WorldMap_RedrawViewport(1);
    dword_5202F0 = 1;
    return 1;
  }
  else if ( Input_IsKeyPressed(200) && (v3 = *(_DWORD *)(gameData + 140012), v3 > 0) )
  {
    *(_DWORD *)(gameData + 140012) = v3 - 1;
    WorldMap_RedrawViewport(1);
    dword_5202F0 = v5;
    return v5;
  }
  else
  {
    if ( Input_IsKeyPressed(208) )
    {
      v4 = *(_DWORD *)(gameData + 140012);
      if ( *(_DWORD *)(gameData + 140004) - 7 > v4 )
      {
        *(_DWORD *)(gameData + 140012) = v4 + 1;
        goto LABEL_4;
      }
    }
    return 0;
  }
}
// 40FFEB: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202F0: using guessed type int dword_5202F0;

//----- (00410010) --------------------------------------------------------
signed int  UnitStack_GetMinCurrentActionPoints(intptr_t a1)
{
  __int16 *v1; // eax
  int v2; // edx
  int v3; // ebx

  v1 = (__int16 *)(a1 + 37);
  v2 = 1;
  v3 = *((unsigned __int8 *)v1 - 23);
  do
  {
    if ( *v1 == -1 )
      break;
    if ( v3 > *((unsigned __int8 *)v1 + 8) )
      v3 = *((unsigned __int8 *)v1 + 8);
    ++v2;
    v1 = (__int16 *)((char *)v1 + 31);
  }
  while ( v2 < 10 );
  return v3;
}

//----- (004100B0) --------------------------------------------------------
signed int  UnitStack_GetMaxOrderTier(intptr_t a1)
{
  intptr_t slot_record; // eax
  int max_order_tier; // ebx
  int i; // edx

  if ( UnitStack_HasSpecialPersonageUnits(a1) )
    return 3;
  slot_record = a1;
  max_order_tier = 0;
  for ( i = 0; i < UNIT_STACK_SLOT_COUNT; ++i )
  {
    if ( *(__int16 *)(slot_record + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
      break;
    if ( (*(_BYTE *)(slot_record + 18) & 3) > max_order_tier )
      max_order_tier = *(_BYTE *)(slot_record + 18) & 3;
    slot_record += UNIT_STACK_SLOT_STRIDE;
  }
  return max_order_tier;
}

//----- (00410100) --------------------------------------------------------
signed int  UnitStack_HasPlagueFlag(int a1)
{
  int v1; // edx

  v1 = 0;
  while ( 1 )
  {
    if ( *(__int16 *)(a1 + 6) == -1 )
      return 0;
    if ( (*(_BYTE *)(a1 + 19) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
      break;
    ++v1;
    a1 += 31;
    if ( v1 >= 10 )
      return 0;
  }
  return 1;
}

//----- (00410130) --------------------------------------------------------
signed int  UnitStack_SpendActionPointsClamped(__int16 *a1, int a2, DWORD a3, double a4)
{
  __int16 *v5; // eax
  int i; // ecx
  int v7; // ebx
  char v8; // bl

  v5 = a1 + 3;
  for ( i = 0; i < 10; ++i )
  {
    v7 = *v5;
    if ( v7 == -1 )
      break;
    if ( *((unsigned __int8 *)v5 + 8) < a2 )
      a2 = *((unsigned __int8 *)v5 + 8);
    v8 = *((_BYTE *)v5 + 8);
    v5 = (__int16 *)((char *)v5 + 31);
    LOBYTE(v7) = v8 - a2;
    *((_BYTE *)v5 - 23) = v7;
  }
  return Rules_LinkArmyFact(a1, a2, i, a4, v7, a3);
}

//----- (00410170) --------------------------------------------------------
int  UnitStack_SpendActionPointsUnchecked(int a1, char a2)
{
  int slotPtr; // eax
  int slotIndex; // edx

  slotPtr = a1 + 6;
  slotIndex = 0;
  while ( slotIndex < 10 )
  {
    if ( *(__int16 *)slotPtr == -1 )
      break;
    *(_BYTE *)(slotPtr + 8) -= a2;
    slotPtr += 31;
    ++slotIndex;
  }
  return slotPtr;
}

//----- (004101A0) --------------------------------------------------------
signed int  UnitStack_SubtractActionPointsFloorZero(__int16 *a1, int a2, DWORD a3, double a4)
{
  __int16 *v6; // eax
  int i; // edx
  int v8; // ebx

  v6 = a1 + 3;
  for ( i = 0; i < 10; ++i )
  {
    v8 = *v6;
    if ( v8 == -1 )
      break;
    v8 = *((unsigned __int8 *)v6 + 8);
    if ( v8 <= a2 )
    {
      *((_BYTE *)v6 + 8) = 0;
    }
    else
    {
      LOBYTE(v8) = v8 - a2;
      *((_BYTE *)v6 + 8) = v8;
    }
    v6 = (__int16 *)((char *)v6 + 31);
  }
  return Rules_LinkArmyFact(a1, i, a2, a4, v8, a3);
}

//----- (004101E0) --------------------------------------------------------
signed int  UnitStack_SpendActionPointsByIndexClamped(int a1, int a2, DWORD a3, double a4)
{
  return UnitStack_SpendActionPointsClamped((__int16 *)(725 * a1 + gameData + 147174), a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00410260) --------------------------------------------------------
signed int  UnitStack_CanReachQueuedPathTileWithFogOverlay(__int16 *a1, int a2)
{
  signed int v6; // esi
  int v7; // [esp+0h] [ebp-1A8h]
  int v8[100]; // [esp+4h] [ebp-1A4h]
  int v9; // [esp+194h] [ebp-14h]
  int v10; // [esp+1A0h] [ebp-8h]

  v10 = a2;
  (void)v10;
  if ( Map_ClassifyFogOfWarOverlayForPlayer(*a1, a1[1], VIEWED_PLAYER_INDEX) )
    return 1;
  v6 = UnitStack_GetMinCurrentActionPoints((intptr_t)a1);
  v7 = *(_DWORD *)((char *)a1 + UNIT_STACK_PATH_OFFSET);
  qmemcpy(v8, (char *)a1 + UNIT_STACK_PATH_OFFSET + 4, sizeof(v8));
  do
  {
    if ( v7 )
    {
      v9 = v8[--v7];
      if ( v6 >= HIWORD(v9) )
        continue;
    }
    return 0;
  }
  while ( !Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)v9, BYTE1(v9), VIEWED_PLAYER_INDEX) );
  return 1;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00410330) --------------------------------------------------------
void  UnitStack_ExecuteQueuedPath(unsigned int a1, int a2, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int v6; // ecx
  __int16 *v7; // esi
  int v8; // ebx
  signed int v9; // ebp
  signed int v10; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // ebx
  int v14; // eax
  DWORD v15; // ebp
  int v16; // edx
  int v17; // ecx
  _DWORD *v18; // ecx
  int v19; // edi
  char v20; // bl
  int v21; // ecx
  _DWORD *v22; // eax
  signed int v23; // eax
  int v24; // edx
  unsigned int v25; // eax
  int v26; // eax
  int v27; // edi
  int *v28; // ebp
  int v29; // ebx
  int v30; // edi
  signed int v31; // ebp
  unsigned int v32; // eax
  int v33; // eax
  DWORD v34; // ebp
  int v35; // edi
  int v36; // ecx
  int v37; // ecx
  int v38; // eax
  DWORD v39; // ebp
  __int16 *v40; // edi
  int v41; // edx
  int v42; // edx
  int v43; // ecx
  int v44; // edx
  unsigned int v45; // ecx
  char *v46; // ebp
  void *v47; // ebp
  signed int v48; // edi
  signed int v49; // ecx
  signed int v50; // ecx
  signed int v51; // ecx
  signed int v52; // edx
  signed int v53; // edi
  int v54; // edx
  int v55; // ecx
  int v56; // ecx
  unsigned int v57; // eax
  unsigned int v58; // ecx
  int v59; // edi
  int *v60; // ecx
  int v61; // ebp
  int v62; // ecx
  int v63; // edx
  int v64; // edi
  int v65; // ebp
  int v66; // ebx
  int v67; // eax
  int v68; // edx
  int v69; // eax
  int v70; // eax
  int v71; // edx
  int v72; // eax
  int v73; // edx
  int v74; // ecx
  int v75; // eax
  unsigned __int8 v76; // dl
  char v77; // al
  int v78; // ecx
  int v79; // ebx
  int v80; // edx
  int v81; // edx
  int v82; // ebx
  int v83; // ebp
  int v84; // eax
  __int16 i; // si
  int v86; // edx
  char v87[100]; // [esp+0h] [ebp-CCh] BYREF
  int v88; // [esp+64h] [ebp-68h]
  int v89; // [esp+68h] [ebp-64h]
  int v90; // [esp+6Ch] [ebp-60h]
  int v91; // [esp+70h] [ebp-5Ch]
  int v92; // [esp+74h] [ebp-58h]
  signed int v93; // [esp+78h] [ebp-54h]
  signed int v94; // [esp+7Ch] [ebp-50h]
  int *v95; // [esp+80h] [ebp-4Ch]
  int v96; // [esp+84h] [ebp-48h]
  signed int v97; // [esp+88h] [ebp-44h]
  int v98; // [esp+8Ch] [ebp-40h]
  int v99; // [esp+90h] [ebp-3Ch]
  int v100; // [esp+94h] [ebp-38h]
  int v101; // [esp+98h] [ebp-34h]
  char *v102; // [esp+9Ch] [ebp-30h]
  char *v103; // [esp+A0h] [ebp-2Ch]
  int *v104; // [esp+A4h] [ebp-28h]
  int v105; // [esp+A8h] [ebp-24h]
  int v106; // [esp+ACh] [ebp-20h]
  unsigned int v107; // [esp+B0h] [ebp-1Ch]
  int v108; // [esp+B4h] [ebp-18h]
  BOOL v109; // [esp+B8h] [ebp-14h]

  v107 = a1;
  v101 = a2;
  Debug_Log(a1, a3, a4, (int)aUnit_moveDD);
  Render_DrawSprite_v3(v107, a4);
  v7 = (__int16 *)UNIT_STACK(v107);
  v8 = *((_DWORD *)v7 + 79);
  v104 = (int *)(v7 + 158);
  if ( v8 )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    {
      v105 = v104[v8];
      Diagnostics_TraceWorldMapActionEvent(
        "unit_move_execute_path_next",
        v107,
        (unsigned __int8)v105,
        BYTE1(v105),
        HIWORD(v105));
      v105 = v104[1];
      Diagnostics_TraceWorldMapActionEvent(
        "unit_move_execute_path_first",
        v107,
        (unsigned __int8)v105,
        BYTE1(v105),
        HIWORD(v105));
    }
    v9 = (signed int)v104;
    v96 = 0;
    v89 = v104[1];
    v94 = *v7;
    v10 = *(_DWORD *)(gameData + 140008);
    v93 = v7[1];
    v109 = 1;
    if ( v94 >= v10 )
    {
      v9 = v94;
      if ( v10 + 9 > v94 )
      {
        v9 = *(_DWORD *)(gameData + 140012);
        if ( v93 >= v9
          && v9 + 7 > v93
          && (unsigned __int8)v89 >= *(int *)(gameData + 140008)
          && (unsigned __int8)v89 < v10 + 9
          && BYTE1(v89) >= *(int *)(gameData + 140012) )
        {
          v109 = BYTE1(v89) >= v9 + 7;
        }
      }
    }
    if ( v101 )
    {
      if ( !UnitStack_CanReachQueuedPathTileWithFogOverlay(v7, v101) )
        v101 = 0;
    }
    else
    {
      v109 = 0;
    }
    dword_523F78 = 0;
    if ( v101 && !*(_DWORD *)(gameData + 147159) )
    {
      v20 = *((_BYTE *)v7 + 4);
      Unit_BuildGoSpriteFilePath(v87, *((_BYTE *)v7 + 6), v20);
      v22 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
      if ( v22 )
        v22 = DLXSpriteSet_Load(v22, v87);
      dword_523F78 = (int)v22;
      dword_523F7C = 0;
      g_ActiveUnitMoveTileIndex = v107;
    }
    dword_523F74 = 0;
    dword_523F70 = 0;
    if ( v101 )
      WorldMap_RedrawViewport(1);
    v92 = dword_544D14;
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    v11 = v107;
    *((_BYTE *)v7 + 720) = 0;
    UnitStack_RevealHiddenEnemiesAndAttackAdjacent(v11, a5);
    Trap_TriggerAtStackTile(v107, a4, a5);
    v106 = 1;
    v13 = *v104;
    v100 = 0;
    if ( v13 )
    {
      v91 = 725 * v107;
      v95 = (int *)(v7 + 158);
      while ( 1 )
      {
        if ( v96 )
          goto LABEL_21;
        v105 = v104[*v104];
        v23 = UnitStack_GetMinCurrentActionPoints((intptr_t)v7);
        v24 = HIWORD(v105) - v100;
        if ( v23 - v24 < 0 )
        {
          Diagnostics_TraceWorldMapActionEvent("unit_move_stop_ap", v107, v23, v24, *v104);
          goto LABEL_21;
        }
        v25 = *(unsigned __int16 *)(TILE_INDEX((unsigned __int8)v105, BYTE1(v105))) - 0x8000;
        if ( v25 > 0x64
          || (v26 = UNIT_RECORD(v25), (unsigned int)*(char *)(v26 + 4) >= 4)
          || *(__int16 *)(v26 + 16) == -1 )
        {
          UnitStack_SpendActionPointsUnchecked((int)v7, BYTE2(v105) - v100);
          UnitStack_SetSpentTurnFlag((int)v7);
        }
        v27 = *v104 - 1;
        v28 = v104;
        *v104 = v27;
        v105 = v28[v27 + 1];
        v100 = HIWORD(v105);
        if ( v109 )
        {
          v29 = *(_DWORD *)(gameData + 140008);
          if ( (unsigned __int8)v105 < v29
            || (unsigned __int8)v105 >= v29 + 9
            || (v30 = *(_DWORD *)(gameData + 140012), BYTE1(v105) < v30)
            || BYTE1(v105) >= v30 + 7 )
          {
            if ( Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)v105, BYTE1(v105), VIEWED_PLAYER_INDEX) )
              Camera_CenterOnUnit(v107);
          }
        }
        v13 = 200 * (unsigned __int8)v105;
        v31 = 2 * BYTE1(v105);
        v32 = *(unsigned __int16 *)(gameData + v13 + v31 + 556374) - 0x8000;
        if ( v32 <= 0x64 )
        {
          v99 = 467 * v32;
          v33 = UNIT_RECORD(v32);
          if ( (unsigned int)*(char *)(v33 + 4) < 4 && *(__int16 *)(v33 + 16) != -1 )
            break;
        }
        v34 = BYTE1(v105);
        v35 = (unsigned __int8)v105;
        if ( MapTile_GetReligiousSiteCategory((unsigned __int8)v105, BYTE1(v105)) )
        {
          Audio_StopUnitMoveSound();
          LOBYTE(v13) = v34;
          Temple_UnitGetInto(v107, v35, v34, v34, a5);
          *v95 = 0;
          goto LABEL_21;
        }
        LOBYTE(v13) = v34;
        v36 = UnitStack_GetTileMoveCostOrZero(v7, v35, 0, v34);
        if ( !v36 && UnitStack_HasBuilder(v107) && Map_GetBridgeCrossingCostOrZero(v35, v34) )
        {
          if ( Diagnostics_IsWorldMapClickTraceEnabled() )
            Diagnostics_TraceWorldMapActionEvent("unit_move_bridge_execute_allow", v107, v35, v34, HIWORD(v105));
          v36 = 1;
        }
        if ( !v36 )
        {
          if ( *(_DWORD *)(1423 * *((unsigned __int8 *)v7 + 4) + gameData + 140051) || !Map_GetBridgeCrossingCostOrZero(v35, v34) )
          {
            *((_DWORD *)v7 + 79) = 0;
          }
          else
          {
            v59 = *v95;
            if ( *v95 < 100 )
            {
              v60 = v95;
              *v95 = v59 + 1;
              v60[v59 + 1] = v105;
              UnitStack_ClearReadyFlags((int)v7);
              goto LABEL_21;
            }
          }
          UnitStack_ClearReadyFlags((int)v7);
          goto LABEL_21;
        }
        *((_BYTE *)v7 + 5) = Facing_DirectionFromDelta8(v35 - *v7, v34 - v7[1]);
        v38 = *((unsigned __int8 *)v7 + 5);
        v108 = v38;
        if ( v38 == 6 || v38 == 2 )
          dword_523F74 = 0;
        if ( !v108 || v108 == 4 )
          dword_523F70 = 0;
        if ( !*(_DWORD *)(gameData + 147159) )
        {
          if ( v101 )
          {
            v61 = BYTE1(v105);
            if ( Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)v105, BYTE1(v105), VIEWED_PLAYER_INDEX) )
            {
              v62 = (unsigned __int8)v105;
              v63 = *(__int16 *)(v91 + gameData + 147174);
              v64 = (v62 - v63) << 6;
              v65 = (v61 - *(__int16 *)(v91 + gameData + 147176)) << 6;
              v66 = Time_Now(v62, v63);
              while ( 1 )
              {
                v67 = dword_523F70;
                if ( dword_523F70 <= 0 )
                  v67 = -dword_523F70;
                v68 = v67;
                v69 = v64 <= 0 ? -v64 : v64;
                if ( v68 >= v69 )
                {
                  v70 = dword_523F74;
                  if ( dword_523F74 <= 0 )
                    v70 = -dword_523F74;
                  v71 = v70;
                  v72 = v65 <= 0 ? -v65 : v65;
                  if ( v71 >= v72 )
                    break;
                }
                DD_Pump((int)g_RenderState, v66);
                if ( WorldMap_HandleViewportScrollKeys() )
                {
                  v109 = 0;
                }
                else
                {
                  WorldMap_RedrawFrame(v66);
                  v73 = 88 * v7[3];
                  LOBYTE(v73) = g_UnitTypeMoveAnimationTickIntervalMs[v73];
                  v75 = Time_Now(v74, v73);
                  if ( v75 - v66 >= (unsigned int)v76 )
                  {
                    v77 = dword_523F68++;
                    if ( (v77 & 1) != 0 )
                    {
                      dword_523F7C = ((_BYTE)dword_523F7C + 1) & 7;
                      Audio_PlayWorldMapUnitMoveSound(*v7, v7[1], dword_523F7C, v7[3]);
                    }
                    if ( v106 )
                    {
                      v78 = -1;
                      do
                      {
                        v79 = -1;
                        do
                        {
                          v80 = v79 + v7[1];
                          ++v79;
                          WorldMap_RedrawTileIfVisible(v78 + *v7, v80);
                        }
                        while ( v79 <= 1 );
                        ++v78;
                      }
                      while ( v78 <= 1 );
                    }
                    else if ( Unit_GetSpriteVerticalOffsetPx(v107) )
                    {
                      Map_RedrawUnitNeighborhoodByIndex(v107);
                    }
                    else
                    {
                      v82 = v108;
                      WorldMap_RedrawTileIfVisible(*v7, v7[1]);
                      if ( v82 == 4 || v82 == 5 || v82 == 3 || v82 == 6 || v82 == 2 )
                        WorldMap_RedrawTileIfVisible(*v7, v7[1] + 1);
                      if ( !v108 || v108 == 7 || v108 == 1 )
                        WorldMap_RedrawTileIfVisible(*v7, v7[1] - 1);
                      if ( v108 == 2 || v108 == 3 || v108 == 1 || v108 == 4 )
                        WorldMap_RedrawTileIfVisible(*v7 + 1, v7[1]);
                      if ( v108 == 6 || v108 == 5 || v108 == 7 )
                        WorldMap_RedrawTileIfVisible(*v7 - 1, v7[1]);
                      v78 = v108;
                      switch ( v108 )
                      {
                        case 3:
                          WorldMap_RedrawTileIfVisible(*v7 + 1, v7[1] + 1);
                          break;
                        case 1:
                          WorldMap_RedrawTileIfVisible(*v7 + 1, v7[1] - 1);
                          break;
                        case 5:
                          WorldMap_RedrawTileIfVisible(*v7 - 1, v7[1] + 1);
                          break;
                        case 7:
                          WorldMap_RedrawTileIfVisible(*v7 - 1, v7[1] - 1);
                          break;
                      }
                    }
                    dword_523F70 += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * v7[3]]
                                  * Map_NeighborDX[2 * *((unsigned __int8 *)v7 + 5)];
                    v81 = *((unsigned __int8 *)v7 + 5);
                    dword_523F74 += Map_NeighborDY[2 * v81] * (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * v7[3]];
                    v66 = Time_Now(v78, v81);
                    v106 = 0;
                  }
                }
              }
            }
          }
        }
        dword_523F70 %= 64;
        v90 = (unsigned __int8)v105;
        v103 = (char *)(unsigned __int8)v105;
        v98 = v101;
        v39 = BYTE1(v105);
        v40 = (__int16 *)(gameData + 147174 + v91);
        dword_523F74 %= 64;
        v41 = BYTE1(v105) - v40[1];
        v88 = *v40;
        *((_BYTE *)v40 + 5) = Facing_DirectionFromDelta8((unsigned __int8)v105 - v88, v41);
        v42 = 200 * v90;
        *(_WORD *)(2 * v40[1] + gameData + 200 * *v40 + 556374) = -1;
        v43 = v107;
        v13 = v39;
        *(_WORD *)(v42 + gameData + 2 * v39 + 556374) = v107;
        *v40 = (__int16)v103;
        v40[1] = v39;
        if ( Trap_TriggerAtStackTile(v43, a4, a5) )
          UnitStack_ClearRemainingActionPoints(v40, v39, a5);
        v45 = v107;
        if ( v45 <= 0x1F4 )
        {
          v44 = 725 * v45;
          if ( (unsigned int)*(__int16 *)(725 * v45 + gameData + 147180) <= 0x28 )
          {
            UnitStack_RevealHiddenEnemiesAndAttackAdjacent(v45, a5);
            if ( v45 <= 0x1F4 && (unsigned int)*(__int16 *)(v44 + gameData + 147180) <= 0x28 )
            {
              v46 = v103;
              v97 = UnitStack_UpdateVision(v45);
              v47 = v46 + 1;
              MiniMap_DrawTileCell(v103, v13);
              MiniMap_DrawTileCell(v47, v13);
              v48 = v13 - 1;
              v102 = v103 - 1;
              MiniMap_DrawTileCell(v103 - 1, v13);
              MiniMap_DrawTileCell(v103, v13 - 1);
              MiniMap_DrawTileCell(v47, v13 - 1);
              MiniMap_DrawTileCell(v102, v13 - 1);
              MiniMap_DrawTileCell(v103, v49);
              MiniMap_DrawTileCell(v47, v50);
              v13 = v98;
              MiniMap_DrawTileCell(v102, v51);
              if ( v13 )
              {
                LOBYTE(v13) = (_BYTE)v47;
                v52 = v48;
                g_RenderDevice = (_UNKNOWN *)dword_5202E0;
                v53 = v97;
                MiniMap_RedrawTileRect((int)v102, v52, v45, (int)v47);
                if ( v53 )
                  WorldMap_RedrawViewport(1);
              }
            }
          }
        }
        if ( v101 && *(_DWORD *)(gameData + 147159) )
        {
          Time_Now(v45, v44);
          v13 = (int)g_RenderState;
          WorldMap_RedrawViewport(1);
          v56 = v55 + 10;
          while ( 1 )
          {
            v57 = Time_Now(v56, v54);
            if ( v57 >= v58 )
              break;
            DD_Pump((int)g_RenderState, (char)g_RenderState);
            WorldMap_RedrawFrame((int)g_RenderState);
          }
        }
        if ( v107 <= 0x1F4 && (unsigned int)*(__int16 *)(v91 + gameData + 147174 + 6) <= 0x28 )
        {
          v83 = *v104;
          v106 = 1;
          if ( v83 )
            continue;
        }
        goto LABEL_21;
      }
      if ( *(_BYTE *)(v99 + gameData + 509676) != *((_BYTE *)v7 + 4) || *v104 )
      {
        *((_DWORD *)v7 + 79) = 0;
        UnitStack_ClearReadyFlags((int)v7);
      }
      else
      {
        Audio_StopUnitMoveSound();
        if ( Building_CanAcceptUnitStack(v107, *(unsigned __int16 *)(v13 + gameData + v31 + 556374) - 0x8000) )
          Building_UnitGetInto(v107, *(unsigned __int16 *)(v13 + gameData + v31 + 556374) - 0x8000, v13, v31, a5);
        else
          *(_DWORD *)(gameData + 725 * v107 + 147490) = 0;
      }
    }
LABEL_21:
    v14 = gameData + 725 * v107;
    v15 = v94;
    v16 = *(__int16 *)(v14 + 147174);
    if ( v16 != v94 || (v16 = v93, *(__int16 *)(v14 + 147176) != v93) )
      Rules_LinkArmyFact(v7, v16, gameData, a5, v13, v94);
    Audio_StopUnitMoveSound();
    dword_523F74 = 0;
    dword_523F70 = 0;
    v18 = v7 + 158;
    v19 = *((_DWORD *)v7 + 79);
    if ( v19 )
    {
      v84 = v19 - 1;
      for ( i = v100; v84 >= 0; v18[v86 + 1] = v89 )
      {
        v86 = *v18 - 1 - v84;
        v89 = v18[v86 + 1];
        HIWORD(v89) -= i;
        --v84;
      }
    }
    else
    {
      UnitStack_ClearReadyFlags((int)v7);
    }
    if ( dword_523F78 )
      DLXSpriteSet_ReleaseAndClear(&dword_523F78);
    g_ActiveUnitMoveTileIndex = -1;
    if ( v101 )
    {
      UnitStackSelection_RefreshForSelectedStack(v15);
      WorldMap_RedrawViewport(1);
    }
    RenderState_SelectCursorDescriptor((int)g_RenderState, v92);
    WorldMap_SyncSelectionForHumanPlayer(v15);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_move_after_path_state",
      v107,
      *v7,
      v7[1],
      *((_DWORD *)v7 + 79));
    Diagnostics_TraceWorldMapActionEvent(
      "unit_move_after_path_ap",
      v107,
      UnitStack_GetMinCurrentActionPoints((intptr_t)v7),
      0,
      0);
  }
}
// 4106F5: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 410718: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 4107F4: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 410825: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 410B09: simplified comparisons for 'ecx.4': <0 || >=1F5 became >=1F5u
// 410B30: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 410B48: simplified comparisons for 'ecx.4': <0 || >=1F5 became >=1F5u
// 410B69: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 411076: simplified comparisons for '%var_1C.4': <0 || >=1F5 became >=1F5u
// 41109E: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41035B: variable 'v5' is possibly undefined
// 410385: variable 'v6' is possibly undefined
// 4104F4: variable 'v12' is possibly undefined
// 410595: variable 'v17' is possibly undefined
// 410646: variable 'v21' is possibly undefined
// 4106B6: variable 'v24' is possibly undefined
// 410999: variable 'v37' is possibly undefined
// 4109B6: variable 'v36' is possibly undefined
// 410B09: variable 'v45' is possibly undefined
// 410B5F: variable 'v44' is possibly undefined
// 410BEF: variable 'v49' is possibly undefined
// 410BF8: variable 'v50' is possibly undefined
// 410C0D: variable 'v51' is possibly undefined
// 410C7D: variable 'v55' is possibly undefined
// 410C80: variable 'v56' is possibly undefined
// 410C80: variable 'v54' is possibly undefined
// 410C87: variable 'v58' is possibly undefined
// 410D7A: variable 'v62' is possibly undefined
// 410E07: variable 'v74' is possibly undefined
// 410E0C: variable 'v76' is possibly undefined
// 410E77: variable 'v78' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512360: using guessed type int dword_512360;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 519808: using guessed type int dword_519808;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 523F68: using guessed type int dword_523F68;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D14: using guessed type int dword_544D14;

//----- (00411120) --------------------------------------------------------
int  UnitStats_CalcEffectiveMeleeAttack(char *a1, int a2)
{
  int v2; // ebx

  if ( a2 )
    v2 = 3;
  else
    v2 = UNIT_SLOT_STATUS_LEVEL(a1);
  return (v2 + (unsigned __int8)g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * *(__int16 *)a1] + a1[11] / 5) * a1[9] / 100;
}

//----- (00411180) --------------------------------------------------------
int  UnitStats_GetMeleeIconIndex(__int16 *a1)
{
  return UNIT_SLOT_STATUS_LEVEL(a1) + (unsigned __int8)g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * *a1] + *((char *)a1 + 11) / 5;
}

//----- (004111C0) --------------------------------------------------------
int  UnitStats_CalcEffectiveDefensePower(char *a1, int a2)
{
  int v2; // ebx
  int v3; // esi

  v2 = (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * *(__int16 *)a1];
  if ( (a1[22] & 1) != 0 )
    v2 = (320 * v2 - (__CFSHL__((320 * v2) >> 31, 8) + ((320 * v2) >> 31 << 8))) >> 8;
  if ( a2 )
    v3 = 3;
  else
    v3 = UNIT_SLOT_STATUS_LEVEL(a1);
  return (v3 + v2 + a1[11] / 5) * a1[9] / 100;
}

//----- (00411240) --------------------------------------------------------
int  UnitStats_GetDefenseIconIndex(__int16 *a1)
{
  return UNIT_SLOT_STATUS_LEVEL(a1) + (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * *a1] + *((char *)a1 + 11) / 5;
}

//----- (00411280) --------------------------------------------------------
int  UnitStats_CalcEffectiveShotPower(__int16 *a1)
{
  return ((unsigned __int8)g_UnitTypeBaseShotPower[UNIT_TYPE_METADATA_STRIDE * *a1] + *((char *)a1 + 11) / 10) * *((char *)a1 + 9) / 100;
}

//----- (004112C0) --------------------------------------------------------
int  UnitStats_GetBaseShotPower(__int16 *a1)
{
  return (unsigned __int8)g_UnitTypeBaseShotPower[UNIT_TYPE_METADATA_STRIDE * *a1] + *((char *)a1 + 11) / 10;
}

//----- (004112F0) --------------------------------------------------------
int  UnitStats_CalcEffectiveWallAttack(char *a1, int a2)
{
  int v2; // ebx

  if ( a2 )
    v2 = 3;
  else
    v2 = UNIT_SLOT_STATUS_LEVEL(a1);
  return (v2 + (unsigned __int8)g_UnitTypeBaseWallAttack[UNIT_TYPE_METADATA_STRIDE * *(__int16 *)a1] + a1[11] / 5) * a1[9] / 100;
}

//----- (00411350) --------------------------------------------------------
signed int  Debug_LogUnitSquadDetails(int a1, DWORD a2)
{
  signed int result; // eax
  signed int v4; // ecx

  Debug_Log(0, a1, a2, (int)aUnitD0x08x);
  v4 = 0;
  for ( result = Unit_GetSquadCount(a1); v4 < result; result = Unit_GetSquadCount(a1) )
  {
    Debug_Log(v4 + 1, a1, a2, (int)a15sPl1dP);
    ++v4;
  }
  return result;
}

signed int Unit_DebugDumpFormationSizes(int a1, DWORD a2)
{
  return Debug_LogUnitSquadDetails(a1, a2);
}
// 4113B7: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00411420) --------------------------------------------------------
signed int  Unit_DebugDumpFormationSizesForStackIndex(int a1, DWORD a2)
{
  return Unit_DebugDumpFormationSizes(725 * a1 + gameData + 147174, a2);
}

signed int Render_DrawSprite_v3(int a1, DWORD a2)
{
  return Unit_DebugDumpFormationSizesForStackIndex(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (00411460) --------------------------------------------------------
signed int  LogAllUnits(int a1, char a2, DWORD a3)
{
  int v4; // ecx
  int v5; // edx
  signed int result; // eax

  Debug_Log(a1, a2, a3, (int)aLogallunits);
  v4 = 0;
  v5 = gameData + 147174;
  do
  {
    result = *(__int16 *)(v5 + 6);
    if ( result != -1 )
      result = Unit_DebugDumpFormationSizes(v5, a3);
    ++v4;
    v5 += 725;
  }
  while ( v4 < 500 );
  return result;
}
// 411489: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004114B0) --------------------------------------------------------
signed int  Unit_CompactSquad(__int16 *a1, int a2, double a3)
{
  int changed;
  int read_index;
  int write_index;

  (void)a2;

  changed = 0;
  write_index = 0;
  for ( read_index = 0; read_index < UNIT_STACK_SLOT_COUNT; ++read_index )
  {
    int source_slot = UNIT_STACK_SLOT((int)a1, read_index);
    if ( *(__int16 *)source_slot == -1 )
      continue;
    if ( write_index != read_index )
    {
      qmemcpy(
        (void *)UNIT_STACK_SLOT((int)a1, write_index),
        (const void *)source_slot,
        UNIT_STACK_SLOT_STRIDE);
      changed = 1;
    }
    ++write_index;
  }
  while ( write_index < UNIT_STACK_SLOT_COUNT )
  {
    int slot = UNIT_STACK_SLOT((int)a1, write_index);
    if ( *(__int16 *)slot != -1 )
      changed = 1;
    *(__int16 *)slot = -1;
    ++write_index;
  }
  if ( changed )
    Rules_LinkArmyFact(a1, 0, 0, a3, 0, (DWORD)a1);
  return Rules_SyncArmyFactStrength(a1, 0, 0, 0, (DWORD)a1, a3);
}

//----- (00411560) --------------------------------------------------------
_WORD * UnitSlots_RemoveGaps(_WORD *result, int a2)
{
  int v2; // ebx
  int v3; // ebp
  int v4; // edx
  void *v5; // edi
  int i; // [esp+0h] [ebp-20h]
  _WORD *v7; // [esp+4h] [ebp-1Ch]
  __int16 *v8; // [esp+8h] [ebp-18h]

  v7 = result;
  v2 = a2 - 1;
  v3 = 0;
  v8 = result;
  for ( i = 0; v2 > i; ++i )
  {
    if ( *v8 == -1 )
    {
      v4 = v3;
      result = (_WORD *)((char *)v7 + 31 * v3);
      while ( v4 < v2 )
      {
        v5 = result;
        ++v4;
        result = (_WORD *)((char *)result + 31);
        qmemcpy(v5, result, 0x1Fu);
      }
      *result = -1;
    }
    else
    {
      result = (__int16 *)((char *)v8 + 31);
      ++v3;
      v8 = (__int16 *)((char *)v8 + 31);
    }
  }
  return result;
}

//----- (004115E0) --------------------------------------------------------
void  Unit_CheckLowMorale(_BYTE *a1, double a2)
{
  int v3; // esi
  __int16 *v4; // ecx
  int v5; // ebx
  int v6; // eax
  int v7; // eax
  char v9; // dh
  int v10; // ebx
  int v12; // ebx
  _BYTE v15[725]; // [esp+0h] [ebp-300h] BYREF
  int v16[3]; // [esp+2D8h] [ebp-28h]
  int v17[7]; // [esp+2E4h] [ebp-1Ch] BYREF

  qmemcpy(v15, a1, 0x2D5u);
  v17[0] = 0;
  v3 = 0;
  v4 = (__int16 *)&v15[6];
  v5 = 0;
  do
  {
    if ( *v4 == -1 )
      break;
    if ( !*((_BYTE *)v4 + 11) )
    {
      v6 = (*((_BYTE *)v4 + 13) & UNIT_SLOT_FLAG_LOW_MORALE) != 0;
      *((_BYTE *)v4 + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      v7 = v6 ? 200 : 100;
      if ( Rng_RandRange(0, v7) < 0x32 )
      {
        if ( Rng_RandRange(0, 100) >= 0x32 )
        {
          v3 = 1;
          Debug_Log(0, v5, (DWORD)a1, (int)aUnit_checklo_0);
          *v4 = -1;
          v17[0] = 1;
        }
        else
        {
          Debug_Log(0, v5, (DWORD)a1, (int)aUnit_checklowm);
          v9 = *((_BYTE *)v4 + 13);
          *((_BYTE *)v4 + 8) = 0;
          *((_BYTE *)v4 + 13) = v9 | UNIT_SLOT_FLAG_LOW_MORALE;
        }
      }
    }
    ++v5;
    v4 = (__int16 *)((char *)v4 + 31);
  }
  while ( v5 < 10 );
  if ( v3 && *(_DWORD *)(gameData + 1423 * (unsigned __int8)a1[4] + 140051) )
  {
    v10 = *(__int16 *)a1;
    UI_CenterWorldMapViewportOnRectIfFit(v10, *((__int16 *)a1 + 1), *((__int16 *)a1 + 1) - 5, v10);
    v16[0] = (int)g_Text_UnitDisbandedLowMoraleMessages[0];
    v16[1] = (int)g_Text_UnitDisbandedLowMoraleMessages[1];
    v16[2] = (int)g_Text_UnitDisbandedLowMoraleMessages[2];
    UI_ShowInfoWindow(v16[(unsigned __int8)g_LanguageIndex], 0, 0, (DWORD)a1, (int)v17, (int)&g_Text_UnitDisbandedLowMoraleMessages[3]);
    UI_StartWorldMapUnitAttentionFlash(
      *(unsigned __int16 *)(gameData + 200 * *(__int16 *)a1 + 2 * *((__int16 *)a1 + 1) + 556374),
      *((__int16 *)a1 + 1),
      *(__int16 *)a1);
    while ( UI_IsWorldMapUnitAttentionFlashActive() )
      WorldMap_RedrawFrame(v10);
  }
  v12 = v17[0];
  qmemcpy(a1, v15, 0x2D4u);
  a1[724] = v15[724];
  if ( v12 )
  {
    Unit_CompactSquad((__int16 *)a1, 0, a2);
    Rules_LinkArmyFinalize((__int16 *)a1, a2);
    Rules_LinkArmyFact((__int16 *)a1, 0, 0, a2, 0, (DWORD)a1);
  }
}
// 4116CD: variable 'v8' is possibly undefined
// 4116D2: variable 'v4' is possibly undefined
// 411743: variable 'v11' is possibly undefined
// 4117F5: variable 'v13' is possibly undefined
// 4117F5: variable 'v14' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 512368: using guessed type char *off_512368[3];
// 5202E4: using guessed type int gameData;

//----- (00411810) --------------------------------------------------------
signed int  UnitStack_ApplyPlagueAttritionToPeasantCargo(__int16 *a1, DWORD a2, double a3)
{
  __int16 *v4; // ecx
  int v5; // esi
  int i; // ebx
  signed int result; // eax
  char v8; // al
  char v9; // dl
  int v10; // edx
  int v11; // ecx

  v4 = a1 + 3;
  v5 = 0;
  for ( i = 0; i < 10; ++i )
  {
    result = *v4;
    if ( result == -1 )
      break;
    if ( result == UNIT_TYPE_PEASANT_CARGO && (*((_BYTE *)v4 + 13) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
    {
      v8 = Rng_RandRange(15, 25);
      v9 = *((_BYTE *)v4 + 9) - v8;
      result = v9;
      *((_BYTE *)v4 + 9) = v9;
      if ( v9 <= 0 )
      {
        v5 = 1;
        *v4 = -1;
      }
    }
    v4 = (__int16 *)((char *)v4 + 31);
  }
  if ( v5 )
  {
    Unit_CompactSquad(a1, (int)v4, a3);
    Rules_LinkArmyFinalize(a1, a3);
    if ( a1[3] != -1 )
      Rules_LinkArmyFact(a1, v10, v11, a3, i, a2);
    return Rules_SyncArmyFactStrength(a1, v10, v11, i, a2, a3);
  }
  return result;
}
// 411840: variable 'v4' is possibly undefined
// 411887: variable 'v10' is possibly undefined
// 411887: variable 'v11' is possibly undefined

//----- (004118A0) --------------------------------------------------------
BOOL  UnitSlot_ShouldGainFatigueFromLowActionPoints(int a1)
{
  return *(unsigned __int8 *)(a1 + 8) <= 3u && (*(_BYTE *)(a1 + 13) & UNIT_SLOT_FLAG_LOW_MORALE) == 0;
}

//----- (004118C0) --------------------------------------------------------
BOOL  UnitSlot_CanRecoverFatigue(int a1)
{
  return (*(_BYTE *)(a1 + 13) & UNIT_SLOT_FLAG_SPENT_TURN) == 0;
}

//----- (004118D0) --------------------------------------------------------
BOOL  UnitSlot_HasSevereFatigue(int a1)
{
  return *(char *)(a1 + 10) >= 80;
}

//----- (004118E0) --------------------------------------------------------
signed int  Unit_NewTurn(int a1, char a2, DWORD a3, double a4)
{
  int v4; // esi
  int v5; // ebx
  int v6; // edx
  int v7; // ecx
  char v8; // al
  unsigned int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int i; // [esp+0h] [ebp-20h]
  unsigned int v14; // [esp+4h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)aUnit_newturn);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
  v14 = 0;
  for ( i = 0; ; i += 725 )
  {
    if ( *(__int16 *)(gameData + i + 147180) == -1 || *(unsigned __int8 *)(gameData + i + 147178) != g_CurrentPlayerIndex )
      goto LABEL_16;
    v4 = gameData + 147174 + i;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_stack",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      *(_DWORD *)(v4 + 316));
    UnitStack_AdjustFatigueByPredicate((__int16 *)v4, -20, UnitSlot_CanRecoverFatigue, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_recover_fatigue",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      *(_DWORD *)(v4 + 316));
    if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(v4 + 4) + 140051) )
    {
      UnitStack_AdjustFatigueByPredicate((__int16 *)v4, 10, UnitSlot_ShouldGainFatigueFromLowActionPoints, 0xFFFFFFFF, a4);
      UnitStack_AdjustMoraleByPredicate((__int16 *)v4, -1, UnitSlot_HasSevereFatigue, 0xFFFFFFFF, a4);
    }
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_human_fatigue",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      *(_DWORD *)(v4 + 316));
    UnitStack_ClearSpentTurnFlag(v4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_clear_spent",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      *(_DWORD *)(v4 + 316));
    v5 = 0;
    v6 = v4;
    do
    {
      v7 = *(__int16 *)(v6 + 6);
      if ( v7 == -1 )
        break;
      if ( v7 < 0 || v7 >= UNIT_TYPE_COUNT )
      {
        *(_WORD *)(v6 + 6) = -1;
        break;
      }
      v6 += 31;
      v8 = UnitSlot_CalcActionPointsFromFatigue((__int16 *)(v4 + 6 + 31 * v5++));
      *(_BYTE *)(v6 - 17) = v8;
    }
    while ( v5 < 10 );
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ap",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      v5);
    Rules_LinkArmyFact((__int16 *)v4, v6, v7, a4, v5, 0xFFFFFFFF);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_rules_fact",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      v5);
    Unit_CheckLowMorale((_BYTE *)v4, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_low_morale",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      v5);
    UnitStack_ApplyPlagueAttritionToPeasantCargo((__int16 *)v4, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_plague",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      v5);
    if ( !UnitStack_HasReadyUnits(v4) )
      goto LABEL_16;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ready_check",
      (int)v14,
      *(__int16 *)v4,
      *(__int16 *)(v4 + 2),
      v5);
    v9 = *(unsigned __int16 *)(gameData
                             + 200 * (unsigned __int8)*(_DWORD *)(v4 + 320)
                             + 2 * (unsigned __int8)BYTE1(*(_DWORD *)(v4 + 320))
                             + 556374)
       - 0x8000;
    if ( v9 <= 0x64 )
    {
      v5 = 467 * v9;
      v10 = UNIT_RECORD(v9);
      if ( (unsigned int)*(char *)(v10 + 4) < 4
        && *(__int16 *)(v10 + 16) != -1
        && *(_BYTE *)(v5 + gameData + 509676) != *(_BYTE *)(v4 + 4) )
      {
        break;
      }
    }
    if ( *(_DWORD *)(v4 + 316) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_before_path",
        (int)v14,
        *(__int16 *)v4,
        *(__int16 *)(v4 + 2),
        *(_DWORD *)(v4 + 316));
      UnitStack_ExecuteQueuedPath(v14, 0, v5, 0xFFFFFFFF, a4);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_after_path",
        (int)v14,
        *(__int16 *)v4,
        *(__int16 *)(v4 + 2),
        *(_DWORD *)(v4 + 316));
    }
    else
      UnitStack_ClearReadyFlags(v4);
LABEL_16:
    v11 = i + 725;
    v5 = v14 + 1;
    v14 = v5;
    if ( v5 >= 500 )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
      return LogAllUnits(v11, v5, 0xFFFFFFFF);
    }
  }
  UnitStack_ClearReadyFlags(v4);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done_enemy_contact", (int)v14, *(__int16 *)v4, *(__int16 *)(v4 + 2), v5);
  return LogAllUnits(v11, v5, 0xFFFFFFFF);
}
// 4119FD: simplified comparisons for 'edx.4': <0 || >=65 became >=65u
// 411A18: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 41194F: variable 'a4' is possibly undefined
// 4119A2: variable 'v7' is possibly undefined
// 411A67: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00411AB0) --------------------------------------------------------
signed int  UnitStack_HasBuilder(int a1)
{
  __int16 *v1; // edx
  int v2; // eax
  int v3; // ecx

  v1 = (__int16 *)(725 * a1 + gameData + 147174 + 6);
  v2 = 0;
  while ( 1 )
  {
    v3 = *v1;
    if ( v3 == -1 )
      return 0;
    if ( v3 == UNIT_TYPE_BUILDER )
      break;
    ++v2;
    v1 = (__int16 *)((char *)v1 + 31);
    if ( v2 >= 10 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00411B30) --------------------------------------------------------
__int16  Map_RedrawUnitFootprintByIndex(int a1)
{
  __int16 *unit_stack; // ecx
  int result; // eax
  int unit_type; // eax
  int unit_metadata_offset; // eax
  int x; // eax
  int y; // edx

  unit_stack = (__int16 *)(gameData + 147174 + 725 * a1);
  x = unit_stack[0];
  y = unit_stack[1];
  result = WorldMap_RedrawTileIfVisible(x, y);
  unit_type = unit_stack[3];
  unit_metadata_offset = 88 * unit_type;
  if ( g_UnitTypeSpriteVerticalOffsetPx[unit_metadata_offset] )
  {
    if ( (unsigned __int16)unit_type >= 0x1Bu )
    {
      if ( (unsigned __int16)unit_type > 0x1Bu )
      {
        if ( (unsigned __int16)unit_type == 0x1E )
        {
          WorldMap_RedrawTileIfVisible(x + 1, y);
          WorldMap_RedrawTileIfVisible(x, y - 1);
          WorldMap_RedrawTileIfVisible(x - 1, y);
          result = WorldMap_RedrawTileIfVisible(x, y + 1);
        }
      }
      else
      {
        switch ( *((_BYTE *)unit_stack + 5) )
        {
          case 0:
          case 4:
            WorldMap_RedrawTileIfVisible(x - 1, y);
            result = WorldMap_RedrawTileIfVisible(x + 1, y);
            break;
          case 1:
            WorldMap_RedrawTileIfVisible(x + 1, y);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          case 2:
          case 6:
            WorldMap_RedrawTileIfVisible(x, y - 1);
            result = WorldMap_RedrawTileIfVisible(x, y + 1);
            break;
          case 3:
            WorldMap_RedrawTileIfVisible(x + 1, y);
            WorldMap_RedrawTileIfVisible(x, y + 1);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          case 5:
            WorldMap_RedrawTileIfVisible(x - 1, y);
            WorldMap_RedrawTileIfVisible(x, y + 1);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          case 7:
            WorldMap_RedrawTileIfVisible(x - 1, y);
            result = WorldMap_RedrawTileIfVisible(x, y - 1);
            break;
          default:
            return result;
        }
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00411CB0) --------------------------------------------------------
int  Map_RedrawUnitNeighborhoodByIndex(int a1)
{
  int result; // eax
  __int16 *unit_stack; // ecx
  int x; // eax
  int y; // edx

  unit_stack = (__int16 *)(725 * a1 + gameData + 147174);
  x = unit_stack[0];
  y = unit_stack[1];
  result = WorldMap_RedrawTileIfVisible(x, y);
  result = Unit_GetSpriteVerticalOffsetPx(a1);
  if ( result )
  {
    WorldMap_RedrawTileIfVisible(x, y - 1);
    WorldMap_RedrawTileIfVisible(x, y + 1);
    WorldMap_RedrawTileIfVisible(x - 1, y);
    WorldMap_RedrawTileIfVisible(x + 1, y);
    WorldMap_RedrawTileIfVisible(x - 1, y - 1);
    WorldMap_RedrawTileIfVisible(x - 1, y + 1);
    WorldMap_RedrawTileIfVisible(x + 1, y - 1);
    return WorldMap_RedrawTileIfVisible(x + 1, y + 1);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00411D70) --------------------------------------------------------
void Map_UpdateIdleAnimatedUnits()
{
  int v0; // ecx
  int v1; // edx
  int v2; // eax
  int v3; // eax
  unsigned int v4; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx

  v0 = 0;
  v1 = gameData + 147174;
  do
  {
    v2 = *(__int16 *)(v1 + 6);
    if ( v2 != -1 )
    {
      v3 = 88 * v2;
      if ( (g_UnitTypeHasIdleAnimationFlags[v3] & 1) != 0 )
      {
        v4 = (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[v3] + *(_DWORD *)(v1 + 24);
        if ( v4 < Time_Now(v0, v1) )
        {
          v5 = Time_Now(v0, v1);
          *(_DWORD *)(v1 + 24) = v5;
          LOBYTE(v5) = ((*(_BYTE *)(v1 + 23) & 7) + 1) & 7;
          BYTE1(v5) = *(_BYTE *)(v1 + 23) & 0xF8;
          *(_BYTE *)(v1 + 23) = BYTE1(v5);
          BYTE1(v5) |= v5;
          *(_BYTE *)(v1 + 23) = BYTE1(v5);
          *(_BYTE *)(v1 + 23) = BYTE1(v5) & 0xF8;
          *(_BYTE *)(v1 + 23) = BYTE1(v5);
          Map_RedrawUnitFootprintByIndex(v0);
        }
      }
    }
    ++v0;
    v1 += 725;
  }
  while ( v0 < 500 );
  UI_UpdateWorldMapUnitAttentionFlash();
  UI_UpdateUnitBlinkFlash(0, 0);
}
// 5202E4: using guessed type int gameData;

//----- (00411E20) --------------------------------------------------------
int  Unit_GetSpriteVerticalOffsetPx(int a1)
{
  return (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(gameData + 725 * a1 + 147180)];
}
// 5202E4: using guessed type int gameData;

//----- (00411E60) --------------------------------------------------------
signed int  Unit_AttemptNeighborMove(int a1)
{
  int stack_offset; // edx
  signed int available_action_points; // ebp
  int direction_index; // esi
  int neighbor_column; // edx
  int neighbor_row; // ecx
  int *queued_path; // eax
  int last_path_step; // edx
  unsigned __int16 required_action_points; // ax
  int stack_record; // eax

  stack_offset = UNIT_STACK_STRIDE * a1;
  stack_record = gameData + UNIT_STACK_TABLE_OFFSET + stack_offset;
  available_action_points = UnitStack_GetMinCurrentActionPoints(stack_record);
  if ( available_action_points < 3 )
    return 0;
  direction_index = 0;
  while ( direction_index < 16 )
  {
    neighbor_column = Map_NeighborDY[direction_index] + *(__int16 *)(stack_record + 2);
    neighbor_row = Map_NeighborDX[direction_index] + *(__int16 *)stack_record;
    if ( neighbor_row >= 0 && neighbor_row < MAP_WIDTH_TILES && neighbor_column >= 0 && neighbor_column < MAP_HEIGHT_TILES )
    {
      queued_path = Unit_MoveTrack(
                      a1,
                      *(__int16 *)stack_record,
                      *(__int16 *)stack_record + Map_NeighborDX[direction_index],
                      *(__int16 *)(stack_record + 2),
                      available_action_points,
                      *(__int16 *)(stack_record + 2) + Map_NeighborDY[direction_index]);
      if ( queued_path )
      {
        last_path_step = queued_path[*queued_path];
        j__nfree_(queued_path);
        required_action_points = HIWORD(last_path_step);
        if ( available_action_points >= required_action_points )
          return 1;
      }
    }
    direction_index += 2;
  }
  return 0;
}
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (00411F60) --------------------------------------------------------
BOOL  UnitStack_CanExecuteQueuedPathNow(int a1)
{
  int v2; // eax
  int v3; // edx
  int v4; // eax
  BOOL result; // eax
  unsigned __int16 v6; // si

  v2 = gameData + 147174 + 725 * a1;
  v3 = *(_DWORD *)(v2 + 316);
  v4 = v2 + 316;
  result = 0;
  if ( v3 )
  {
    v6 = HIWORD(*(_DWORD *)(v4 + 4 * (v3 - 1) + 4));
    if ( UnitStack_GetMinCurrentActionPoints(gameData + 147174 + 725 * a1) >= v6 )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00412000) --------------------------------------------------------
void * UnitSlots_ExtractSpecialEntries(char *a1, int a2, char *a3)
{
  int v5; // edx
  int v6; // eax
  int v7; // ebx
  _WORD *v8; // eax
  void *result; // eax
  int v11; // [esp+8h] [ebp-14h]

  v11 = a2;
  v5 = 0;
  while ( v5 < v11 )
  {
    v6 = *(__int16 *)a1;
    if ( v6 == -1 )
      break;
    if ( v6 == UNIT_TYPE_GOLD_CARGO
      || v6 == UNIT_TYPE_PEASANT_CARGO
      || v6 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      || v6 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      v7 = 0;
      qmemcpy(a3, a1, 0x1Fu);
      a3 += 31;
      v8 = a1;
      if ( v11 - v5 - 1 > 0 )
      {
        do
        {
          qmemcpy(v8, (char *)v8 + 31, 0x1Fu);
          ++v7;
          v8 = (_WORD *)((char *)v8 + 31);
        }
        while ( v7 < v11 - v5 - 1 );
      }
      *v8 = -1;
      --v11;
    }
    else
    {
      a1 += 31;
      ++v5;
    }
  }
  result = a3;
  *(_WORD *)a3 = -1;
  return result;
}

void * UnitSlots_ExtractSpecialEntriesForBuildingAttack(char *a1, int a2, char *a3)
{
  return UnitSlots_ExtractSpecialEntries(a1, a2, a3);
}

//----- (004120B0) --------------------------------------------------------
int  UnitSlots_AppendEntries(char *a1, char *a2)
{
  char *v2; // esi
  int v3; // ecx
  char *v4; // edi
  int result; // eax

  v2 = a2;
  while ( *(__int16 *)a1 != -1 )
    a1 += 31;
  v3 = 0;
  while ( *(__int16 *)a2 != -1 )
  {
    a2 += 31;
    ++v3;
  }
  v4 = a1;
  result = 31 * v3;
  qmemcpy(v4, v2, 31 * v3);
  return result;
}

int  UnitSlots_AppendEntriesForBuildingAttack(char *a1, char *a2)
{
  return UnitSlots_AppendEntries(a1, a2);
}

//----- (00412100) --------------------------------------------------------
signed int  UnitStack_HasNormalCombatUnits(intptr_t a1)
{
  signed int result; // eax
  intptr_t slot_record; // edx
  signed int squad_count; // esi
  signed int has_normal_unit; // ebx
  signed int slot_index; // ecx
  int unit_type; // eax

  if ( *(__int16 *)(a1 + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
    return 0;
  result = Unit_GetSquadCount(a1);
  squad_count = result;
  if ( result )
  {
    slot_record = a1;
    has_normal_unit = 0;
    slot_index = 0;
    if ( result > 0 )
    {
      while ( !has_normal_unit )
      {
        unit_type = *(__int16 *)(slot_record + UNIT_STACK_SLOT_BASE_OFFSET);
        if ( unit_type == UNIT_TYPE_GOLD_CARGO
          || unit_type == UNIT_TYPE_PEASANT_CARGO
          || unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          || unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          ++slot_index;
          slot_record += UNIT_STACK_SLOT_STRIDE;
          if ( slot_index >= squad_count )
            return has_normal_unit;
        }
        else
        {
          has_normal_unit = 1;
          ++slot_index;
          slot_record += UNIT_STACK_SLOT_STRIDE;
          if ( slot_index >= squad_count )
            return 1;
        }
      }
    }
    return has_normal_unit;
  }
  return result;
}

//----- (00412170) --------------------------------------------------------
signed int  UnitStack_HasGoldCargo(int a1)
{
  int v1; // edx
  int v2; // ecx

  v1 = 0;
  while ( 1 )
  {
    v2 = *(__int16 *)(a1 + 6);
    if ( v2 == -1 )
      return 0;
    if ( v2 == UNIT_TYPE_GOLD_CARGO )
      break;
    ++v1;
    a1 += 31;
    if ( v1 >= 10 )
      return 0;
  }
  return 1;
}

//----- (004121A0) --------------------------------------------------------
signed int  UnitStack_HasPeasantCargo(int a1)
{
  int v1; // edx
  int v2; // ecx

  v1 = 0;
  while ( 1 )
  {
    v2 = *(__int16 *)(a1 + 6);
    if ( v2 == -1 )
      return 0;
    if ( v2 == UNIT_TYPE_PEASANT_CARGO )
      break;
    ++v1;
    a1 += 31;
    if ( v1 >= 10 )
      return 0;
  }
  return 1;
}

//----- (004121D0) --------------------------------------------------------
signed int  UnitStack_NormalizePeasantCargo(__int16 *a1, DWORD a2, double a3)
{
  __int16 *v3; // ecx
  int v4; // esi
  int v5; // edx
  int i; // ebx
  int v7; // eax
  __int16 *v8; // edx
  int j; // ecx
  __int16 *v10; // ecx
  int v11; // eax
  __int16 *v12; // ebx
  signed int v13; // edi
  int v14; // edx
  int v15; // eax
  __int64 v16; // rtt
  int v17; // ebx
  int v18; // ebp
  char v21; // [esp+4h] [ebp-18h]

  v3 = a1 + 3;
  v4 = 0;
  v5 = 0;
  for ( i = 0; i < 10; ++i )
  {
    v7 = *v3;
    if ( v7 == -1 )
      break;
    if ( v7 == UNIT_TYPE_PEASANT_CARGO )
    {
      ++v5;
      v4 += *((char *)v3 + 9);
    }
    v3 = (__int16 *)((char *)v3 + 31);
  }
  v21 = UnitStack_GetMinCurrentActionPoints((intptr_t)a1);
  if ( (int)v8 > v4 )
  {
    v10 = a1;
    v11 = 0;
    v12 = a1 + 3;
    do
    {
      if ( *v12 == -1 )
        break;
      if ( v10[3] == UNIT_TYPE_PEASANT_CARGO )
        v10[3] = -1;
      v10 = (__int16 *)((char *)v10 + 31);
      ++v11;
      v12 = (__int16 *)((char *)v12 + 31);
    }
    while ( v11 < 10 );
    Unit_CompactSquad(a1, (int)v10, a3);
    v13 = Unit_GetSquadCount((int)a1);
    v15 = v4 / 100;
    v17 = 0;
    for ( j = (int)a1 + 31 * v13; ; *(_BYTE *)(j - 17) = v21 )
    {
      v18 = v17 + v13;
      if ( v17 >= v15 )
        break;
      j += 31;
      *(_WORD *)(j - 25) = UNIT_TYPE_PEASANT_CARGO;
      *(_BYTE *)(j - 16) = 100;
      *(_BYTE *)(j - 15) = 0;
      *(_BYTE *)(j - 14) = 10;
      ++v17;
    }
    LOBYTE(i) = 100;
    *(_BYTE *)(j + 14) = v21;
    *(_WORD *)(j + 6) = UNIT_TYPE_PEASANT_CARGO;
    *(_BYTE *)(j + 15) = v4 % 100;
    v8 = a1;
    *(_BYTE *)(j + 16) = 0;
    a2 = (DWORD)a1 + 31 * v18 + 31;
    *(_BYTE *)(j + 17) = 10;
    *(_WORD *)(a2 + 6) = -1;
  }
  return Rules_SyncArmyFactStrength(a1, (int)v8, j, i, a2, a3);
}
// 412213: variable 'v8' is possibly undefined
// 41224F: variable 'v14' is possibly undefined
// 4122E3: variable 'j' is possibly undefined

//----- (00412300) --------------------------------------------------------
__int16 * UnitStack_CaptureDefeatedStack(
        __int16 *a1,
        signed int a2,
        int a3,
        int a4,
        double a5)
{
  __int16 *winner_stack;
  __int16 *defeated_stack;
  unsigned char winner_owner;
  signed int defeated_had_plague;
  int slot_index;
  int unit_type;
  int winner_count;
  int defeated_count;
  __int16 *result;

  Debug_Log(a3, a4, (DWORD)a1, (int)aUnit_capture0x);
  winner_stack = a1;
  defeated_stack = (__int16 *)a2;
  if ( !winner_stack || !defeated_stack )
    return winner_stack;

  winner_owner = UNIT_STACK_OWNER_INDEX((int)winner_stack);
  Diagnostics_TraceWorldMapActionEvent(
    "capture_defeated_stack_enter",
    Diagnostics_UnitStackIndexFromRecord((int)winner_stack),
    Diagnostics_UnitStackIndexFromRecord((int)defeated_stack),
    winner_owner,
    Unit_GetSquadCount((int)defeated_stack));
  defeated_had_plague = UnitStack_HasPlagueFlag((int)defeated_stack);
  for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
  {
    __int16 *slot = (__int16 *)UNIT_STACK_SLOT((int)defeated_stack, slot_index);
    unit_type = *slot;
    if ( unit_type == -1 )
      break;
    if ( unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      Prisoner_QueueCapturedUnit(
        *slot,
        *((unsigned __int8 *)slot + 2),
        slot[2],
        winner_owner,
        (DWORD)winner_stack,
        slot[3]);
      *slot = -1;
    }
  }

  Unit_CompactSquad(defeated_stack, 0, a5);
  if ( defeated_stack[3] == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_empty_before_owner",
      Diagnostics_UnitStackIndexFromRecord((int)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)defeated_stack),
      winner_owner,
      0);
    return Rules_UnlinkArmyFact(defeated_stack, a5);
  }

  defeated_count = Unit_GetSquadCount((int)defeated_stack);
  for ( slot_index = 0; slot_index < defeated_count; ++slot_index )
  {
    char *slot = (char *)UNIT_STACK_SLOT((int)defeated_stack, slot_index);
    slot[2] = winner_owner;
  }
  UNIT_STACK_OWNER_INDEX((int)defeated_stack) = winner_owner;
  Diagnostics_TraceWorldMapActionEvent(
    "capture_defeated_stack_owner_changed",
    Diagnostics_UnitStackIndexFromRecord((int)winner_stack),
    Diagnostics_UnitStackIndexFromRecord((int)defeated_stack),
    winner_owner,
    defeated_count);
  UnitStack_ClearReadyFlags((int)defeated_stack);
  Unit_CompactSquad(defeated_stack, 0, a5);
  if ( defeated_stack[3] == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_empty_after_owner",
      Diagnostics_UnitStackIndexFromRecord((int)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)defeated_stack),
      winner_owner,
      0);
    return Rules_UnlinkArmyFact(defeated_stack, a5);
  }

  UnitStack_NormalizePeasantCargo(defeated_stack, (DWORD)winner_stack, a5);
  Rules_SyncArmyFactOwner(defeated_stack, winner_owner, (DWORD)winner_stack, a5);

  winner_count = Unit_GetSquadCount((int)winner_stack);
  defeated_count = Unit_GetSquadCount((int)defeated_stack);
  if ( winner_count + defeated_count <= UNIT_STACK_SLOT_COUNT
    && UnitStack_GetMoveCostToTileIgnoringOccupancy(defeated_stack, *winner_stack, winner_stack[1]) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_merge_kill",
      Diagnostics_UnitStackIndexFromRecord((int)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)defeated_stack),
      winner_count,
      defeated_count);
    qmemcpy(
      (void *)UNIT_STACK_SLOT((int)winner_stack, winner_count),
      (const void *)UNIT_STACK_SLOT((int)defeated_stack, 0),
      UNIT_STACK_SLOT_STRIDE * defeated_count);
    if ( winner_count + defeated_count < UNIT_STACK_SLOT_COUNT )
      *(__int16 *)UNIT_STACK_SLOT((int)winner_stack, winner_count + defeated_count) = -1;
    Unit_Kill((int)defeated_stack, 0, (DWORD)winner_stack, a5);
    Rules_LinkArmyFact(winner_stack, 0, 0, a5, 0, (DWORD)winner_stack);
    result = (__int16 *)Rules_SyncArmyFactStrength(winner_stack, 0, 0, 0, (DWORD)winner_stack, a5);
  }
  else
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      char *slot = (char *)UNIT_STACK_SLOT((int)defeated_stack, slot_index);
      if ( *(__int16 *)slot == -1 )
        break;
      slot[2] = winner_owner;
    }
    UNIT_STACK_OWNER_INDEX((int)defeated_stack) = winner_owner;
    if ( *(_DWORD *)UNIT_STACK_PATH_BUFFER((int)defeated_stack) )
      *(_DWORD *)UNIT_STACK_PATH_BUFFER((int)defeated_stack) = 0;
    Diagnostics_TraceWorldMapActionEvent(
      "capture_defeated_stack_retained",
      Diagnostics_UnitStackIndexFromRecord((int)winner_stack),
      Diagnostics_UnitStackIndexFromRecord((int)defeated_stack),
      winner_owner,
      Unit_GetSquadCount((int)defeated_stack));
    result = (__int16 *)Rules_SyncArmyFactOwner(defeated_stack, winner_owner, (DWORD)winner_stack, a5);
  }
  if ( defeated_had_plague )
  {
    for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
    {
      __int16 *slot = (__int16 *)UNIT_STACK_SLOT((int)winner_stack, slot_index);
      unit_type = *slot;
      if ( unit_type == -1 )
        break;
      if ( unit_type == UNIT_TYPE_PEASANT_CARGO )
        *((_BYTE *)slot + 13) |= UNIT_SLOT_FLAG_PLAGUE;
    }
    return Trap_HurtStack(winner_stack, 0, (DWORD)winner_stack, a5);
  }
  return result;
}

//----- (00412520) --------------------------------------------------------
int  Unit_CreateNearbyUnitGroup(int a1, int a2, unsigned __int8 *a3, double a4)
{
  unsigned __int8 *v4; // ebp
  signed int v5; // edi
  int v6; // esi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // edx
  unsigned __int8 *i; // eax
  int v12; // ebx
  int v13; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // [esp-4h] [ebp-24h]
  int v19; // [esp+0h] [ebp-20h]
  int v20; // [esp+4h] [ebp-1Ch]

  v4 = a3;
  v5 = 0;
  Debug_Log(a1, (char)a3, (DWORD)a3, (int)aUnitCreateNearbyUnitGroup);
  v6 = 0;
  v20 = 0;
  do
  {
    v7 = Map_NeighborDX[v6];
    v8 = Map_NeighborDY[v6] + a2;
    v9 = v7 + a1;
    if ( v7 + a1 >= 0 )
    {
      v7 = gameData;
      if ( v9 < *(_DWORD *)(gameData + 140000) && v8 >= 0 && v8 < *(_DWORD *)(gameData + 140004) )
      {
        LOBYTE(a3) = -1;
        if ( !Trap_GetTileOwnerMask(v9, v8, -1) )
        {
          v18 = Map_NeighborDY[v6] + a2;
          LOBYTE(a3) = Rng_RandRange(0, 7);
          v5 = Unit_Create(*(__int16 *)v4, v4[2], v13, (char)a3, v18);
          if ( v5 )
            break;
        }
      }
    }
    v6 += 2;
    ++v20;
  }
  while ( v6 < 16 );
  if ( v5 )
  {
    v10 = 0;
    v19 = 725
        * *(unsigned __int16 *)(gameData
                              + 200 * (Map_NeighborDX[2 * v20] + a1)
                              + 2 * (Map_NeighborDY[2 * v20] + a2)
                              + 556374)
        + gameData
        + 147174;
    for ( i = v4; ; i += 31 )
    {
      v12 = 31 * v10;
      if ( *(__int16 *)i == -1 )
        break;
      ++v10;
    }
    qmemcpy((void *)(v19 + 6), v4, 31 * v10);
    if ( v10 < 9 )
    {
      v12 += v19;
      *(_WORD *)(v12 + 6) = -1;
    }
    Rules_LinkArmyFact((__int16 *)v19, v10, 0, a4, v12, (DWORD)v4);
    Rules_SyncArmyFactStrength((__int16 *)v19, v15, v16, v12, (DWORD)v4, a4);
    Debug_Log(v17, v12, v19, (int)aUnit_createn_1);
    Unit_DebugDumpFormationSizes(v19, v19);
    return v19;
  }
  else
  {
    Debug_Log(v7, (char)a3, (DWORD)v4, (int)aUnit_createn_0);
    return 0;
  }
}
// 4126A1: variable 'v13' is possibly undefined
// 4126BA: variable 'v7' is possibly undefined
// 412704: variable 'v15' is possibly undefined
// 412704: variable 'v16' is possibly undefined
// 412723: variable 'v17' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (004127A0) --------------------------------------------------------
int  UnitSlot_AdjustFatigueByPredicate(int a1, int a2, BOOL ( *a3)(int a1))
{
  int result; // eax
  signed char v4; // cl

  result = a3(a1);
  if ( result )
  {
    result = *(__int16 *)a1;
    if ( result != UNIT_TYPE_GOLD_CARGO
      && result != UNIT_TYPE_PEASANT_CARGO
      && result != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      && result != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      v4 = a2 + *(char *)(a1 + 10);
      *(_BYTE *)(a1 + 10) = v4;
      if ( v4 < 0 )
        *(_BYTE *)(a1 + 10) = 0;
      if ( *(char *)(a1 + 10) > 100 )
        *(_BYTE *)(a1 + 10) = 100;
      return *(char *)(a1 + 10);
    }
  }
  return result;
}

static BOOL UnitSlot_PredicateAlways(int a1)
{
  (void)a1;
  return 1;
}

//----- (004127F0) --------------------------------------------------------
signed int  UnitStack_AdjustFatigueByPredicate(
        __int16 *a1,
        int a2,
        BOOL ( *a3)(int a1),
        DWORD a4,
        double a5)
{
  __int16 *v6; // edx
  int v7; // ecx
  int v10; // eax
  signed int result; // eax
  char v13; // [esp+0h] [ebp-8h]

  v13 = a2;
  if ( a2 <= 0 || (result = UnitStack_HasSpecialPersonageUnits((intptr_t)a1)) == 0 )
  {
    v6 = a1 + 3;
    v7 = 0;
    while ( v7 < 10 )
    {
      if ( *v6 == -1 )
        break;
      if ( a3((int)v6) )
      {
        v10 = *v6;
        if ( v10 != UNIT_TYPE_GOLD_CARGO
          && v10 != UNIT_TYPE_PEASANT_CARGO
          && v10 != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          && v10 != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          int fatigue = (signed char)*((char *)v6 + 10) + (signed char)v13;
          *((_BYTE *)v6 + 10) = (unsigned char)fatigue;
          if ( fatigue < 0 )
            *((_BYTE *)v6 + 10) = 0;
          if ( *((char *)v6 + 10) > 100 )
            *((_BYTE *)v6 + 10) = 100;
        }
      }
      ++v7;
      v6 = (__int16 *)((char *)v6 + 31);
    }
    return Rules_SyncArmyFactStrength(a1, (int)v6, v7, (char)a3, a4, a5);
  }
  return result;
}

//----- (00412880) --------------------------------------------------------
int  UnitSlot_AdjustMoraleByPredicate(int a1, int a2, BOOL ( *a3)(int a1))
{
  int result; // eax
  int unit_type; // eax
  int morale; // eax

  result = a3(a1);
  if ( result )
  {
    unit_type = *(__int16 *)a1;
    if ( unit_type != UNIT_TYPE_GOLD_CARGO
      && unit_type != UNIT_TYPE_PEASANT_CARGO
      && unit_type != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      && unit_type != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      morale = *(char *)(a1 + 11) + a2;
      *(_BYTE *)(a1 + 11) = morale;
      if ( a2 > 0 )
        *(_BYTE *)(a1 + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      if ( *(char *)(a1 + 11) < 0 )
        *(_BYTE *)(a1 + 11) = 0;
      if ( *(char *)(a1 + 11) > 20 )
        *(_BYTE *)(a1 + 11) = 20;
      return *(char *)(a1 + 11);
    }
  }
  return result;
}

//----- (004128E0) --------------------------------------------------------
signed int  UnitStack_AdjustMoraleByPredicate(
        __int16 *a1,
        int a2,
        BOOL ( *a3)(int a1),
        DWORD a4,
        double a5)
{
  __int16 *v6; // edx
  int v7; // ecx
  int v10; // eax
  signed int result; // eax

  if ( a2 >= 0 || (result = UnitStack_HasSpecialPersonageUnits((intptr_t)a1)) == 0 )
  {
    v6 = a1 + 3;
    v7 = 0;
    while ( v7 < 10 )
    {
      if ( *v6 == -1 )
        break;
      if ( a3((int)v6) )
      {
        v10 = *v6;
        if ( v10 != UNIT_TYPE_GOLD_CARGO
          && v10 != UNIT_TYPE_PEASANT_CARGO
          && v10 != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          && v10 != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          *((_BYTE *)v6 + 11) += a2;
          if ( a2 > 0 )
            *((_BYTE *)v6 + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
          if ( *((char *)v6 + 11) < 0 )
            *((_BYTE *)v6 + 11) = 0;
          if ( *((char *)v6 + 11) > 20 )
            *((_BYTE *)v6 + 11) = 20;
        }
      }
      ++v7;
      v6 = (__int16 *)((char *)v6 + 31);
    }
    return Rules_SyncArmyFactStrength(a1, (int)v6, v7, (char)a3, a4, a5);
  }
  return result;
}

//----- (00412970) --------------------------------------------------------
int  UnitSlot_CycleOrderState(int result)
{
  char v1; // dl
  char v2; // dh
  char v3; // bl

  v1 = (UNIT_SLOT_ORDER_STATE(result) + 1) & 3;
  v2 = *(_BYTE *)(result + 12) & 0xF3;
  *(_BYTE *)(result + 12) = v2;
  v3 = (4 * v1) | v2;
  *(_BYTE *)(result + 12) = v3;
  if ( (unsigned __int8)((unsigned __int8)(16 * v3) >> 6) > 2u )
  {
    *(_BYTE *)(result + 12) = v3 & 0xF3;
    if ( (v2 & 3u) < 3 )
    {
      *(_BYTE *)(result + 12) = v3 & 0xF0;
      *(_BYTE *)(result + 12) = ((v2 & 3) + 1) & 3 | ((4 * v1) | v2) & 0xF0;
    }
  }
  return result;
}

//----- (004129E0) --------------------------------------------------------
signed int  UnitStack_CycleAllSlotOrders(__int16 *a1, DWORD a2, double a3)
{
  int stack_record; // edi
  int slot_index; // edx
  int slot_cursor; // ecx
  int slot_type; // ebx

  stack_record = (int)(uintptr_t)a1;
  slot_index = 0;
  slot_cursor = stack_record;
  do
  {
    slot_type = *(__int16 *)(uintptr_t)(unsigned int)(slot_cursor + UNIT_STACK_SLOT_BASE_OFFSET);
    if ( slot_type == -1 )
      return Rules_SyncArmyFactStrength(a1, slot_index, slot_cursor, -1, a2, a3);
    UnitSlot_CycleOrderState(UNIT_STACK_SLOT(stack_record, slot_index));
    ++slot_index;
    slot_cursor += UNIT_STACK_SLOT_STRIDE;
  }
  while ( slot_index < UNIT_STACK_SLOT_COUNT );
  return Rules_SyncArmyFactStrength(a1, slot_index, slot_cursor, slot_type, a2, a3);
}

//----- (00412A30) --------------------------------------------------------
__int16 * UnitStack_SetSpentTurnFlag(int a1)
{
  __int16 *result; // eax
  int i; // edx
  char v3; // bl

  result = (__int16 *)(a1 + 6);
  for ( i = 0; i < 10; ++i )
  {
    if ( *result == -1 )
      break;
    v3 = *((_BYTE *)result + 13);
    result = (__int16 *)((char *)result + 31);
    *((_BYTE *)result - 18) = v3 | UNIT_SLOT_FLAG_SPENT_TURN;
  }
  return result;
}

//----- (00412A60) --------------------------------------------------------
__int16 * UnitStack_ClearSpentTurnFlag(int a1)
{
  __int16 *result; // eax
  int i; // edx
  char v3; // bl

  result = (__int16 *)(a1 + 6);
  for ( i = 0; i < 10; ++i )
  {
    if ( *result == -1 )
      break;
    v3 = *((_BYTE *)result + 13);
    result = (__int16 *)((char *)result + 31);
    *((_BYTE *)result - 18) = v3 & ~UNIT_SLOT_FLAG_SPENT_TURN;
  }
  return result;
}

//----- (00412A90) --------------------------------------------------------
int  UnitStack_SetPlagueFlag(int result)
{
  int i; // edx
  char v2; // bl

  for ( i = 0; i < 10; ++i )
  {
    if ( *(__int16 *)(result + 6) == -1 )
      break;
    v2 = *(_BYTE *)(result + 19);
    result += 31;
    *(_BYTE *)(result - 12) = v2 | 8;
  }
  return result;
}

//----- (00412AC0) --------------------------------------------------------
signed int  UnitStack_HasPlague(int a1)
{
  int v1; // edx

  v1 = 0;
  while ( 1 )
  {
    if ( *(__int16 *)(a1 + 6) == -1 )
      return 0;
    if ( (*(_BYTE *)(a1 + 19) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
      break;
    ++v1;
    a1 += 31;
    if ( v1 >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412AF0) --------------------------------------------------------
signed int  UnitStack_HasLowMoraleUnit(int a1)
{
  __int16 *v1; // eax
  int v2; // edx

  v1 = (__int16 *)(a1 + 6);
  v2 = 0;
  while ( 1 )
  {
    if ( *v1 == -1 )
      return 0;
    if ( (*((_BYTE *)v1 + 13) & UNIT_SLOT_FLAG_LOW_MORALE) != 0 )
      break;
    ++v2;
    v1 = (__int16 *)((char *)v1 + 31);
    if ( v2 >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412B20) --------------------------------------------------------
int  UnitStackSelection_BuildSelectedSlotIndexList(int result, int a2, int *a3)
{
  int v3; // esi
  int *v5; // edx
  int i; // [esp+0h] [ebp-Ch]

  v3 = result;
  for ( i = 0; a2 > i; ++i )
  {
    if ( *(_DWORD *)(v3 + 4 * i) )
    {
      v5 = a3++;
      *v5 = i;
    }
    result = i;
  }
  *a3 = -1;
  return result;
}

//----- (00412B60) --------------------------------------------------------
signed int  UnitStack_HasSpecialPersonageUnits(intptr_t a1)
{
  int v2; // ecx
  int v3; // eax

  v2 = 0;
  while ( 1 )
  {
    v3 = *(__int16 *)(a1 + 6);
    if ( v3 == -1 )
      return 0;
    if ( v3 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v3 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      break;
    ++v2;
    a1 += 31;
    if ( v2 >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412B90) --------------------------------------------------------
int  UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(char *a1, int a2, int a3)
{
  int v5; // ebx
  int v6; // eax
  char *v7; // edx
  int v8; // ecx

  v5 = 0;
  v6 = 0;
  if ( a2 > 0 )
  {
    v7 = a1;
    do
    {
      if ( v5 )
        break;
      v8 = *(__int16 *)v7;
      if ( v8 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v8 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        v5 = 1;
      ++v6;
      v7 += 31;
    }
    while ( v6 < a2 );
  }
  return UnitSlots_CalcCombatStrengthScore(a1, a2, v5, a3);
}
// 412B90: could not find valid save-restore pair for ebx

//----- (00412BE0) --------------------------------------------------------
int  UnitStack_CalcMilitaryStrength(int a1)
{
  signed int v1; // eax
  int v2; // edx

  v1 = Unit_GetSquadCount(a1);
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)(v2 + 6), v1, 0);
}
// 412BEA: variable 'v2' is possibly undefined

//----- (00412C00) --------------------------------------------------------
int  Building_CalcGarrisonStrength(int a1, signed int a2)
{
  int v2; // ebx
  int v3; // edx
  int v4; // eax
  char *v5; // ecx

  v2 = Building_CalcWallDefenseBonus(a1, a2);
  v4 = Building_CountGarrison(v3);
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(v5, v4, v2);
}
// 412C11: variable 'v3' is possibly undefined
// 412C1A: variable 'v5' is possibly undefined

//----- (00412C30) --------------------------------------------------------
int  Player_CalcMilitaryStrength(signed int a1)
{
  int v2; // ecx
  int v3; // edx
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int i; // ebx
  int v8; // edx
  int v9; // eax
  int v10; // ecx

  v2 = 0;
  v3 = 0;
LABEL_2:
  v4 = UNIT_RECORD(v3);
  if ( (unsigned int)*(char *)(v4 + 4) < 4
    && *(__int16 *)(v4 + 16) != -1
    && *(unsigned __int8 *)(gameData + 467 * v3 + 509676) == a1 )
  {
    v5 = Building_CalcGarrisonStrength(UNIT_RECORD(v3), a1);
    v2 = v5 + v6;
  }
  while ( ++v3 < 100 )
  {
    if ( v3 >= 0 )
      goto LABEL_2;
  }
  for ( i = 0; i < 500; ++i )
  {
    v8 = gameData + 725 * i;
    if ( a1 == *(unsigned __int8 *)(v8 + 147178) && *(__int16 *)(v8 + 147180) != -1 )
    {
      v9 = UnitStack_CalcMilitaryStrength(gameData + 147174 + 725 * i);
      v2 = v9 + v10;
    }
  }
  return v2;
}
// 412C9C: conditional instruction was optimized away because edx.4<64u
// 412C56: simplified comparisons for 'ebx.4': <0 || >=4 became >=4u
// 412C8D: variable 'v6' is possibly undefined
// 412C8F: variable 'v3' is possibly undefined
// 412CE8: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00412D00) --------------------------------------------------------
_DWORD * UnitTrackElementStack_BuildBlank(_DWORD *result)
{
  *result = 0;
  return result;
}

//----- (00412D20) --------------------------------------------------------
int  UnitStack_CopyFromTemplate(int a1, int a2, int a3)
{
  int v4; // eax
  int result; // eax
  int v7; // [esp-8h] [ebp-Ch]

  *(_WORD *)a1 = *(_WORD *)a2;
  *(_WORD *)(a1 + 2) = *(_WORD *)(a2 + 2);
  *(_BYTE *)(a1 + 4) = *(_BYTE *)(a2 + 4);
  *(_BYTE *)(a1 + 5) = *(_BYTE *)(a2 + 5);
  *(_DWORD *)(_wcpp_4_copy_array__(a3) + 310) = *(_DWORD *)(a2 + 316);
  v4 = _wcpp_4_copy_array__(v7);
  *(_BYTE *)(v4 + 400) = *(_BYTE *)(a2 + 720);
  result = v4 - 320;
  *(_DWORD *)(result + 721) = *(_DWORD *)(a2 + 721);
  return result;
}
// 412D20: could not find valid save-restore pair for esi
// 412D74: variable 'v7' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00412DA0) --------------------------------------------------------
int  BattleUnitEntry_CopyMergingPackedFlags(int result, int a2)
{
  char v2; // bl
  char v3; // cl
  char v4; // bh
  char v5; // cl
  char v6; // bl
  char v7; // cl
  char v8; // ch
  char v9; // bl
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  char v14; // bl
  char v15; // bh

  *(_WORD *)result = *(_WORD *)a2;
  *(_BYTE *)(result + 2) = *(_BYTE *)(a2 + 2);
  *(_BYTE *)(result + 3) = *(_BYTE *)(a2 + 3);
  *(_WORD *)(result + 4) = *(_WORD *)(a2 + 4);
  *(_WORD *)(result + 6) = *(_WORD *)(a2 + 6);
  *(_BYTE *)(result + 8) = *(_BYTE *)(a2 + 8);
  *(_BYTE *)(result + 9) = *(_BYTE *)(a2 + 9);
  *(_BYTE *)(result + 10) = *(_BYTE *)(a2 + 10);
  *(_BYTE *)(result + 11) = *(_BYTE *)(a2 + 11);
  v2 = *(_BYTE *)(result + 12) & 0xFC;
  v3 = *(_BYTE *)(a2 + 12) & 3;
  *(_BYTE *)(result + 12) = v2;
  v4 = v3 | v2;
  *(_BYTE *)(result + 12) = v3 | v2;
  v5 = *(_BYTE *)(a2 + 12) & 0xC;
  *(_BYTE *)(result + 12) = v4 & 0xF3;
  v6 = v5 | v4 & 0xF3;
  *(_BYTE *)(result + 12) = v6;
  v7 = *(_BYTE *)(a2 + 12) & 0x70;
  *(_BYTE *)(result + 12) = v6 & 0x8F;
  v8 = v7 | v6 & 0x8F;
  v9 = *(_BYTE *)(result + 13);
  *(_BYTE *)(result + 12) = v8;
  v10 = *(_DWORD *)(a2 + 13);
  *(_BYTE *)(result + 13) = v9 & 0xFE;
  *(_DWORD *)(result + 13) |= v10 & 1;
  v11 = *(_DWORD *)(a2 + 13);
  *(_BYTE *)(result + 13) &= ~2u;
  *(_DWORD *)(result + 13) |= v11 & 2;
  v12 = *(_DWORD *)(a2 + 13);
  *(_BYTE *)(result + 13) &= ~4u;
  *(_DWORD *)(result + 13) |= v12 & 4;
  v13 = *(_DWORD *)(a2 + 13);
  *(_BYTE *)(result + 13) &= ~8u;
  *(_DWORD *)(result + 13) |= v13 & 8;
  LOBYTE(v13) = *(_BYTE *)(a2 + 17) & 7;
  v14 = *(_BYTE *)(result + 17) & 0xF8;
  *(_BYTE *)(result + 17) = v14;
  *(_BYTE *)(result + 17) = v13 | v14;
  *(_DWORD *)(result + 18) = *(_DWORD *)(a2 + 18);
  v15 = *(_BYTE *)(result + 22) & 0xFE;
  LOBYTE(v13) = *(_BYTE *)(a2 + 22) & 1;
  *(_BYTE *)(result + 22) = v15;
  *(_BYTE *)(result + 22) = v13 | v15;
  *(_DWORD *)(result + 23) = *(_DWORD *)(a2 + 23);
  *(_DWORD *)(result + 27) = *(_DWORD *)(a2 + 27);
  return result;
}

//----- (00412EB0) --------------------------------------------------------
int  UnitTrackElementStack_CopyFromTemplate(_DWORD *a1, _DWORD *a2, int a3)
{
  *a1 = *a2;
  return _wcpp_4_copy_array__(a3) - 4;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00412EE0) --------------------------------------------------------
int  UnitTrackElement_CopyFromTemplate(int result, int a2)
{
  *(_BYTE *)result = *(_BYTE *)a2;
  *(_BYTE *)(result + 1) = *(_BYTE *)(a2 + 1);
  *(_WORD *)(result + 2) = *(_WORD *)(a2 + 2);
  return result;
}

//----- (00412F00) --------------------------------------------------------
int UnitSpriteCache_ClearAllEntries()
{
  int result; // eax

  for ( result = 0; result != UNIT_SPRITE_CACHE_BYTES; result += UNIT_SPRITE_CACHE_RECORD_STRIDE )
    *(int *)(void *)(g_UnitSpriteCacheRecords + result) = -1;
  return result;
}
// 523F78: using guessed type int dword_523F78;

//----- (00412F30) --------------------------------------------------------
int  UnitSpriteCache_GetOrLoadEntry(
        unsigned __int16 a1,
        char a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5,
        signed int a6)
{
  int record_index;
  int record_offset;
  int sprite_record;
  unsigned int oldest_tick;
  int oldest_index;
  char path[100]; // [esp+0h] [ebp-78h] BYREF

  (void)a5;
  (void)a6;

  record_index = 0;
  while ( record_index < UNIT_SPRITE_CACHE_RECORD_COUNT
       && *(int *)(void *)(g_UnitSpriteCacheRecords + record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE) != -1 )
    ++record_index;

  if ( record_index == UNIT_SPRITE_CACHE_RECORD_COUNT )
  {
    oldest_tick = 0xFFFFFFFFu;
    oldest_index = 0;
    for ( record_index = 0; record_index < UNIT_SPRITE_CACHE_RECORD_COUNT; ++record_index )
    {
      record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
      if ( oldest_tick > *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) )
      {
        oldest_tick = *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11);
        oldest_index = record_index;
      }
    }
    record_index = oldest_index;
    record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
    sprite_record = *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7);
    if ( sprite_record )
      nfree_(sprite_record);
    *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7) = 0;
  }

  record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
  *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset) = (unsigned __int16)a1;
  g_UnitSpriteCacheRecords[record_offset + 4] = a2;
  g_UnitSpriteCacheRecords[record_offset + 5] = a4;
  g_UnitSpriteCacheRecords[record_offset + 6] = a3;
  *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) = Time_Now(0, 0);

  Unit_BuildGoSpriteFilePath(path, (unsigned __int8)a1, a2);
  sprite_record = Mem_Alloc(22, 0, 0, 0);
  if ( sprite_record )
    sprite_record = DLXSprite_LoadCachedEntry(sprite_record, path, a3 + 8 * a4);
  *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7) = sprite_record;
  return sprite_record;
}

int  Unit_SetFlag(unsigned __int16 a1, char a2, unsigned __int8 a3, unsigned __int8 a4, DWORD a5, signed int a6)
{
  return UnitSpriteCache_GetOrLoadEntry(a1, a2, a3, a4, a5, a6);
}
// 412FB8: variable 'v11' is possibly undefined
// 412FDB: variable 'v7' is possibly undefined
// 41300C: variable 'v15' is possibly undefined
// 413024: variable 'v16' is possibly undefined
// 413041: variable 'v18' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 523F88: using guessed type int dword_523F88;
// 523F8F: using guessed type int dword_523F8F;
// 523F93: using guessed type int dword_523F93;

//----- (00413080) --------------------------------------------------------
int  UnitSpriteCache_FindEntryOrLoad(signed int a1, char a2, unsigned __int8 a3, unsigned __int8 a4)
{
  int record_index;
  int record_offset;

  for ( record_index = 0; record_index < UNIT_SPRITE_CACHE_RECORD_COUNT; ++record_index )
  {
    record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
    if ( *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset) == (unsigned __int16)a1
      && g_UnitSpriteCacheRecords[record_offset + 4] == (unsigned char)a2
      && g_UnitSpriteCacheRecords[record_offset + 5] == a4
      && g_UnitSpriteCacheRecords[record_offset + 6] == a3 )
    {
      *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) = Time_Now(0, 0);
      return *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7);
    }
  }
  return Unit_SetFlag(a1, a2, a3, a4, 0, 0);
}
// 4130CF: variable 'v12' is possibly undefined
// 523F88: using guessed type int dword_523F88;
// 523F8F: using guessed type int dword_523F8F;
// 523F93: using guessed type int dword_523F93;

//----- (00413120) --------------------------------------------------------
void  UnitSpriteCache_FreeAllEntries(int a1, DWORD a2)
{
  int i; // edx
  int sprite_record; // ecx

  Debug_Log(a1, -1, a2, (int)aUnitscache_cle);
  for ( i = 0; i != UNIT_SPRITE_CACHE_BYTES; i += UNIT_SPRITE_CACHE_RECORD_STRIDE )
  {
    if ( *(int *)(void *)(g_UnitSpriteCacheRecords + i) == -1 )
      continue;
    sprite_record = *(int *)(void *)(g_UnitSpriteCacheRecords + i + 7);
    *(int *)(void *)(g_UnitSpriteCacheRecords + i) = -1;
    if ( sprite_record )
    {
      nfree_(sprite_record);
      *(int *)(void *)(g_UnitSpriteCacheRecords + i + 7) = 0;
    }
  }
}
// 413166: variable 'v3' is possibly undefined
// 41316B: variable 'v5' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 523F88: using guessed type int dword_523F88;
// 523F8F: using guessed type int dword_523F8F;

//----- (00413180) --------------------------------------------------------
int UnitSpriteCache_CountActiveEntries()
{
  int v0; // edx
  int i; // eax

  v0 = 0;
  for ( i = 0; i != 1500; i += 15 )
  {
    if ( *(int *)((char *)&dword_523F88 + i) != -1 )
      ++v0;
  }
  return v0;
}
// 523F88: using guessed type int dword_523F88;

static const char *UnitType_GetResourceKey(int unit_type)
{
  static const char *resource_keys[35] = {
    "peon",
    "infl",
    "infh",
    "sprl",
    "sprh",
    "cavl",
    "cavh",
    "ryc",
    "drag",
    "arch",
    "kusza",
    "muszk",
    "katap",
    "taran",
    "armat",
    "lesn",
    "goral",
    "budow",
    "worm",
    "slon",
    "cykl",
    "trol",
    "scorp",
    "szk",
    "mag",
    "duch",
    "orzel",
    "pegaz",
    "skrz",
    "wazka",
    "smok",
    "gold",
    "peas",
    "specm",
    "speck"
  };

  if ( unit_type < 0 || unit_type >= (int)(sizeof(resource_keys) / sizeof(resource_keys[0])) )
    return "peon";
  return resource_keys[unit_type];
}

//----- (004131B0) --------------------------------------------------------
char  Unit_BuildGoSpriteFilePath(char *a1, unsigned __int8 a2, char a3)
{
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char result; // al
  _BYTE v19[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_go;
  v4 = a1;
  v19[0] = a3 + 49;
  v19[1] = 0;
  do
  {
    v5 = *v3;
    *v4 = *v3;
    if ( !v5 )
      break;
    v6 = v3[1];
    v3 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = (char *)UnitType_GetResourceKey(a2);
  v8 = &a1[strlen(a1)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  v11 = v19;
  v12 = &a1[strlen(a1)];
  do
  {
    v13 = *v11;
    *v12 = *v11;
    if ( !v13 )
      break;
    v14 = v11[1];
    v11 += 2;
    v12[1] = v14;
    v12 += 2;
  }
  while ( v14 );
  v15 = a_s32;
  v16 = &a1[strlen(a1)];
  do
  {
    result = *v15;
    *v16 = *v15;
    if ( !result )
      break;
    result = v15[1];
    v15 += 2;
    v16[1] = result;
    v16 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413270) --------------------------------------------------------
char  UI_BeginUnitInfo(char *a1, unsigned __int8 a2, char a3)
{
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char v17; // al
  char v18; // al
  char *v19; // esi
  char *v20; // edi
  char result; // al
  _BYTE v23[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_i;
  v4 = a1;
  v23[0] = a3 + 49;
  v23[1] = 0;
  do
  {
    v5 = *v3;
    *v4 = *v3;
    if ( !v5 )
      break;
    v6 = v3[1];
    v3 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = (char *)UnitType_GetResourceKey(a2);
  v8 = &a1[strlen(a1)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  v11 = v23;
  v12 = &a1[strlen(a1)];
  do
  {
    v13 = *v11;
    *v12 = *v11;
    if ( !v13 )
      break;
    v14 = v11[1];
    v11 += 2;
    v12[1] = v14;
    v12 += 2;
  }
  while ( v14 );
  v15 = a_i;
  v16 = &a1[strlen(a1)];
  do
  {
    v17 = *v15;
    *v16 = *v15;
    if ( !v17 )
      break;
    v18 = v15[1];
    v15 += 2;
    v16[1] = v18;
    v16 += 2;
  }
  while ( v18 );
  v19 = a_s32_0;
  v20 = &a1[strlen(a1)];
  do
  {
    result = *v19;
    *v20 = *v19;
    if ( !result )
      break;
    result = v19[1];
    v19 += 2;
    v20[1] = result;
    v20 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413350) --------------------------------------------------------
char  Unit_BuildGarrisonSlotIconSpritePath(char *a1, unsigned __int8 a2, int a3)
{
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  char *v8; // esi
  char *v9; // edi
  char v10; // al
  char v11; // al
  char *v12; // esi
  char *v13; // edi
  char v14; // al
  char v15; // al
  char *v16; // esi
  char *v17; // edi
  char v18; // al
  char v19; // al
  char *v20; // esi
  char *v21; // edi
  char result; // al
  char v23[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  v4 = aUnits_i_0;
  v5 = a1;
  strcpy(v23, "g");
  do
  {
    v6 = *v4;
    *v5 = *v4;
    if ( !v6 )
      break;
    v7 = v4[1];
    v4 += 2;
    v5[1] = v7;
    v5 += 2;
  }
  while ( v7 );
  v8 = (char *)UnitType_GetResourceKey(a2);
  v9 = &a1[strlen(a1)];
  do
  {
    v10 = *v8;
    *v9 = *v8;
    if ( !v10 )
      break;
    v11 = v8[1];
    v8 += 2;
    v9[1] = v11;
    v9 += 2;
  }
  while ( v11 );
  v12 = v23;
  v13 = &a1[strlen(a1)];
  do
  {
    v14 = *v12;
    *v13 = *v12;
    if ( !v14 )
      break;
    v15 = v12[1];
    v12 += 2;
    v13[1] = v15;
    v13 += 2;
  }
  while ( v15 );
  v16 = a_i_0;
  v17 = &a1[strlen(a1)];
  do
  {
    v18 = *v16;
    *v17 = *v16;
    if ( !v18 )
      break;
    v19 = v16[1];
    v16 += 2;
    v17[1] = v19;
    v17 += 2;
  }
  while ( v19 );
  v20 = a_s32_4;
  v21 = &a1[strlen(a1)];
  do
  {
    result = *v20;
    *v21 = *v20;
    if ( !result )
      break;
    result = v20[1];
    v20 += 2;
    v21[1] = result;
    v21 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413430) --------------------------------------------------------
char  Unit_BuildSelectedUnitPanelIconSpritePath(char *a1, unsigned __int8 a2, int a3)
{
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  char *v8; // esi
  char *v9; // edi
  char v10; // al
  char v11; // al
  char *v12; // esi
  char *v13; // edi
  char v14; // al
  char v15; // al
  char *v16; // esi
  char *v17; // edi
  char v18; // al
  char v19; // al
  char *v20; // esi
  char *v21; // edi
  char result; // al
  char v23[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  v4 = aUnits_i_1;
  v5 = a1;
  strcpy(v23, "c");
  do
  {
    v6 = *v4;
    *v5 = *v4;
    if ( !v6 )
      break;
    v7 = v4[1];
    v4 += 2;
    v5[1] = v7;
    v5 += 2;
  }
  while ( v7 );
  v8 = (char *)UnitType_GetResourceKey(a2);
  v9 = &a1[strlen(a1)];
  do
  {
    v10 = *v8;
    *v9 = *v8;
    if ( !v10 )
      break;
    v11 = v8[1];
    v8 += 2;
    v9[1] = v11;
    v9 += 2;
  }
  while ( v11 );
  v12 = v23;
  v13 = &a1[strlen(a1)];
  do
  {
    v14 = *v12;
    *v13 = *v12;
    if ( !v14 )
      break;
    v15 = v12[1];
    v12 += 2;
    v13[1] = v15;
    v13 += 2;
  }
  while ( v15 );
  v16 = a_i_1;
  v17 = &a1[strlen(a1)];
  do
  {
    v18 = *v16;
    *v17 = *v16;
    if ( !v18 )
      break;
    v19 = v16[1];
    v16 += 2;
    v17[1] = v19;
    v17 += 2;
  }
  while ( v19 );
  v20 = a_s32_5;
  v21 = &a1[strlen(a1)];
  do
  {
    result = *v20;
    *v21 = *v20;
    if ( !result )
      break;
    result = v20[1];
    v20 += 2;
    v21[1] = result;
    v21 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413510) --------------------------------------------------------
char  Unit_BuildSelectedUnitPanelIconPalettePath(char *a1, unsigned __int8 a2, int a3)
{
  char *v4; // esi
  char *v5; // edi
  char v6; // al
  char v7; // al
  char *v8; // esi
  char *v9; // edi
  char v10; // al
  char v11; // al
  char *v12; // esi
  char *v13; // edi
  char v14; // al
  char v15; // al
  char *v16; // esi
  char *v17; // edi
  char v18; // al
  char v19; // al
  char *v20; // esi
  char *v21; // edi
  char result; // al
  char v23[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  v4 = aUnits_i_2;
  v5 = a1;
  strcpy(v23, "c");
  do
  {
    v6 = *v4;
    *v5 = *v4;
    if ( !v6 )
      break;
    v7 = v4[1];
    v4 += 2;
    v5[1] = v7;
    v5 += 2;
  }
  while ( v7 );
  v8 = (char *)UnitType_GetResourceKey(a2);
  v9 = &a1[strlen(a1)];
  do
  {
    v10 = *v8;
    *v9 = *v8;
    if ( !v10 )
      break;
    v11 = v8[1];
    v8 += 2;
    v9[1] = v11;
    v9 += 2;
  }
  while ( v11 );
  v12 = v23;
  v13 = &a1[strlen(a1)];
  do
  {
    v14 = *v12;
    *v13 = *v12;
    if ( !v14 )
      break;
    v15 = v12[1];
    v12 += 2;
    v13[1] = v15;
    v13 += 2;
  }
  while ( v15 );
  v16 = a_i_2;
  v17 = &a1[strlen(a1)];
  do
  {
    v18 = *v16;
    *v17 = *v16;
    if ( !v18 )
      break;
    v19 = v16[1];
    v16 += 2;
    v17[1] = v19;
    v17 += 2;
  }
  while ( v19 );
  v20 = a_pal;
  v21 = &a1[strlen(a1)];
  do
  {
    result = *v20;
    *v21 = *v20;
    if ( !result )
      break;
    result = v20[1];
    v20 += 2;
    v21[1] = result;
    v21 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (004135F0) --------------------------------------------------------
char  Unit_BuildAttackAnimSpritePath(char *a1, unsigned __int8 a2, char a3)
{
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char v17; // al
  char v18; // al
  char *v19; // esi
  char *v20; // edi
  char result; // al
  _BYTE v23[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_at_1;
  v4 = a1;
  v23[0] = a3 + 49;
  v23[1] = 0;
  do
  {
    v5 = *v3;
    *v4 = *v3;
    if ( !v5 )
      break;
    v6 = v3[1];
    v3 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = (char *)UnitType_GetResourceKey(a2);
  v8 = &a1[strlen(a1)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  v11 = v23;
  v12 = &a1[strlen(a1)];
  do
  {
    v13 = *v11;
    *v12 = *v11;
    if ( !v13 )
      break;
    v14 = v11[1];
    v11 += 2;
    v12[1] = v14;
    v12 += 2;
  }
  while ( v14 );
  v15 = a_a;
  v16 = &a1[strlen(a1)];
  do
  {
    v17 = *v15;
    *v16 = *v15;
    if ( !v17 )
      break;
    v18 = v15[1];
    v15 += 2;
    v16[1] = v18;
    v16 += 2;
  }
  while ( v18 );
  v19 = a_s32_3;
  v20 = &a1[strlen(a1)];
  do
  {
    result = *v19;
    *v20 = *v19;
    if ( !result )
      break;
    result = v19[1];
    v19 += 2;
    v20[1] = result;
    v20 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (004136D0) --------------------------------------------------------
char  Unit_BuildShotAnimSpritePath(char *a1, unsigned __int8 a2, char a3)
{
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char v17; // al
  char v18; // al
  char *v19; // esi
  char *v20; // edi
  char result; // al
  _BYTE v23[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_at;
  v4 = a1;
  v23[0] = a3 + 49;
  v23[1] = 0;
  do
  {
    v5 = *v3;
    *v4 = *v3;
    if ( !v5 )
      break;
    v6 = v3[1];
    v3 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = (char *)UnitType_GetResourceKey(a2);
  v8 = &a1[strlen(a1)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  v11 = v23;
  v12 = &a1[strlen(a1)];
  do
  {
    v13 = *v11;
    *v12 = *v11;
    if ( !v13 )
      break;
    v14 = v11[1];
    v11 += 2;
    v12[1] = v14;
    v12 += 2;
  }
  while ( v14 );
  v15 = a_s;
  v16 = &a1[strlen(a1)];
  do
  {
    v17 = *v15;
    *v16 = *v15;
    if ( !v17 )
      break;
    v18 = v15[1];
    v15 += 2;
    v16[1] = v18;
    v16 += 2;
  }
  while ( v18 );
  v19 = a_s32_1;
  v20 = &a1[strlen(a1)];
  do
  {
    result = *v19;
    *v20 = *v19;
    if ( !result )
      break;
    result = v19[1];
    v19 += 2;
    v20[1] = result;
    v20 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (004137B0) --------------------------------------------------------
char  Unit_BuildShotAnimPaletteSpritePath(char *a1, unsigned __int8 a2)
{
  char *v2; // esi
  char *v3; // edi
  char v4; // al
  char v5; // al
  char *v6; // esi
  char *v7; // edi
  char v8; // al
  char v9; // al
  char *v10; // esi
  char *v11; // edi
  char v12; // al
  char v13; // al
  char *v14; // esi
  char *v15; // edi
  char result; // al

  v2 = aUnits_at_0;
  v3 = a1;
  do
  {
    v4 = *v2;
    *v3 = *v2;
    if ( !v4 )
      break;
    v5 = v2[1];
    v2 += 2;
    v3[1] = v5;
    v3 += 2;
  }
  while ( v5 );
  v6 = (char *)UnitType_GetResourceKey(a2);
  v7 = &a1[strlen(a1)];
  do
  {
    v8 = *v6;
    *v7 = *v6;
    if ( !v8 )
      break;
    v9 = v6[1];
    v6 += 2;
    v7[1] = v9;
    v7 += 2;
  }
  while ( v9 );
  v10 = aUnitSpritePaletteSuffix;
  v11 = &a1[strlen(a1)];
  do
  {
    v12 = *v10;
    *v11 = *v10;
    if ( !v12 )
      break;
    v13 = v10[1];
    v10 += 2;
    v11[1] = v13;
    v11 += 2;
  }
  while ( v13 );
  v14 = a_s32_2;
  v15 = &a1[strlen(a1)];
  do
  {
    result = *v14;
    *v15 = *v14;
    if ( !result )
      break;
    result = v14[1];
    v14 += 2;
    v15[1] = result;
    v15 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413860) --------------------------------------------------------
void  Unit_BuildBigInfoGraphicPath(char *a1, unsigned __int8 a2, int a3)
{
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  char *v11; // esi
  char *v12; // edi
  char v13; // al
  char v14; // al
  char *v15; // esi
  char *v16; // edi
  char v17; // al
  char v18; // al
  int v20[7]; // [esp+0h] [ebp-1Ch]

  v20[5] = a3;
  v20[0] = (int)g_LanguageDirectoryNames[0];
  v20[1] = (int)g_LanguageDirectoryNames[1];
  v20[2] = (int)g_LanguageDirectoryNames[2];
  v3 = aBiginfo_;
  v4 = a1;
  do
  {
    v5 = *v3;
    *v4 = *v3;
    if ( !v5 )
      break;
    v6 = v3[1];
    v3 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = (char *)v20[(unsigned __int8)g_LanguageIndex];
  v8 = &a1[strlen(a1)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  v11 = (char *)UnitType_GetResourceKey(a2);
  v12 = &a1[strlen(a1)];
  do
  {
    v13 = *v11;
    *v12 = *v11;
    if ( !v13 )
      break;
    v14 = v11[1];
    v11 += 2;
    v12[1] = v14;
    v12 += 2;
  }
  while ( v14 );
  v15 = a_gfx_1;
  v16 = &a1[strlen(a1)];
  do
  {
    v17 = *v15;
    *v16 = *v15;
    if ( !v17 )
      break;
    v18 = v15[1];
    v15 += 2;
    v16[1] = v18;
    v16 += 2;
  }
  while ( v18 );
  // 413915: falls through to the shared register-restore epilogue at 413918
  // (pop edi/esi/ecx/ebx; retn) shared with sub_413920; in C this is the return.
  return;
}
// 413915: control flows out of bounds to 413918
// 511130: using guessed type char g_LanguageIndex;
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 513328: using guessed type char *off_513328[3];

//----- (00413920) --------------------------------------------------------
signed int  UnitStack_BuildMergedTerrainMoveProfile(intptr_t a1, intptr_t a2)
{
  intptr_t slot_record; // esi
  signed int squad_count; // eax
  _BYTE *merged_profile; // ecx
  signed int slot_index; // edx
  int move_profile_offset; // ebx
  int unit_type_id; // eax
  unsigned char candidate_cost; // bl

  *(_DWORD *)(a1 + 4) = aUcatblad;
  memset((void *)(a1 + 29), 1, 9);
  merged_profile = (_BYTE *)a1;
  slot_record = a2;
  slot_index = 0;
  while ( 1 )
  {
    squad_count = Unit_GetSquadCount(a2);
    if ( slot_index >= squad_count )
      break;
    unit_type_id = *(__int16 *)(slot_record + 6);
    for ( move_profile_offset = 29; move_profile_offset <= 37; ++move_profile_offset )
    {
      candidate_cost = move_profile_offset == 29
                     ? UnitType_GetRoadMoveCost(unit_type_id)
                     : UnitType_GetWorldMoveCost(unit_type_id, move_profile_offset - 30);
      if ( (merged_profile[move_profile_offset] < candidate_cost
         || !candidate_cost)
        && merged_profile[move_profile_offset] )
      {
        merged_profile[move_profile_offset] = candidate_cost;
      }
    }
    slot_record += UNIT_STACK_SLOT_STRIDE;
    ++slot_index;
  }
  return squad_count;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (00413B10) --------------------------------------------------------
signed int Map_InitTerrainMoveTableOffsets()
{
  int terrain_id;

  /*
   * `sub_413B10` writes `dword_524568[eax]` starting at offset `+4`, so the
   * 1024-entry terrain-id lookup table actually begins at `0x52456C`.
   */
  for ( terrain_id = 0; terrain_id <= 3; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 4; terrain_id <= 6; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  g_TerrainMoveProfileOffsets[7] = TERRAIN_MOVE_PROFILE_SWAMP;
  for ( terrain_id = 8; terrain_id <= 15; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 16; terrain_id <= 19; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 20; terrain_id <= 31; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_B;
  for ( terrain_id = 32; terrain_id <= 44; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 45; terrain_id <= 160; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_FOREST;
  for ( terrain_id = 161; terrain_id <= 185; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_HILLS;
  for ( terrain_id = 186; terrain_id <= 221; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_MOUNTAINS;
  for ( terrain_id = 222; terrain_id <= 706; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_WATER;
  for ( terrain_id = 707; terrain_id <= 710; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 711; terrain_id <= 714; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 715; terrain_id <= 745; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_WATER;
  for ( terrain_id = 746; terrain_id <= 750; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_MOUNTAINS;
  for ( terrain_id = 751; terrain_id <= 753; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 754; terrain_id <= 756; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 757; terrain_id <= 770; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_WATER;
  for ( terrain_id = 771; terrain_id < 1024; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  return 1024;
}
// 524568: using guessed type int dword_524568;

//----- (00413DD0) --------------------------------------------------------
int  Map_GetUnitTileMoveCostOrZero(int a1, int a2, int a3, int a4)
{
  unsigned int v7; // edx
  int v8; // eax
  int v10; // edi
  unsigned __int16 *v11; // ecx
  unsigned __int16 *v12; // ecx

  v7 = *(unsigned __int16 *)(2 * a3 + gameData + 200 * a4 + 556374);
  if ( (unsigned __int16)v7 != 0xFFFF )
  {
    if ( v7 >= 0x8000 )
      return 0;
    v8 = gameData + 725 * v7;
    if ( !*(_BYTE *)(v8 + 147894) || *(unsigned __int8 *)(v8 + 147178) == a1 )
      return 0;
  }
  if ( ((1 << a1) & TILE_TRAP_OWNER_MASK(a4, a3)) == 1 << a1 || MapTile_GetReligiousSiteCategory(a4, a3) )
    return 0;
  v10 = 88 * a2;
  v11 = TILE_TERRAIN_RECORD(a4, a3);
  if ( v11[2] != 0xFFFF )
    return UnitType_GetRoadMoveCost(a2);
  if ( !g_PathingAllowBridgeCrossings )
    return UnitType_GetWorldMoveCost(a2, g_TerrainMoveProfileOffsets[*v11]);
  return Map_GetBridgeCrossingCostOrZero(a4, a3)
      || UnitType_GetWorldMoveCost(a2, g_TerrainMoveProfileOffsets[*v11]);
}
// 413E1D: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00413F50) --------------------------------------------------------
signed int  UnitStack_GetTileMoveCostFromMergedProfileOrZero(__int16 *a1, intptr_t a2, int a3, int a4)
{
  int tile_index_ptr; // eax
  unsigned int occupant_stack_index; // edx
  int occupant_stack; // eax
  signed int result; // eax
  unsigned __int16 *terrain_record; // edi

  tile_index_ptr = TILE_INDEX(a4, a3);
  occupant_stack_index = *(unsigned __int16 *)tile_index_ptr;
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF
      || (occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index, !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720))
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)a1 + 4) )
    {
      if ( *a1 != a4 || a1[1] != a3 )
        return 0;
    }
  }
  occupant_stack_index = *(unsigned __int16 *)TILE_INDEX(a4, a3);
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index >= 0x8000 )
      return 0;
    occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index;
    if ( !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720)
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)a1 + 4) )
      return 0;
  }
  if ( ((1 << *((_BYTE *)a1 + 4)) & TILE_TRAP_OWNER_MASK(a4, a3)) == 1 << *((_BYTE *)a1 + 4)
    || MapTile_GetReligiousSiteCategory(a4, a3) )
  {
    return 0;
  }
  terrain_record = TILE_TERRAIN_RECORD(a4, a3);
  if ( terrain_record[2] != 0xFFFF )
    return *(unsigned __int8 *)(a2 + 29);
  if ( !g_PathingAllowBridgeCrossings )
    return *(unsigned __int8 *)(g_TerrainMoveProfileOffsets[*terrain_record] + a2 + 30);
  result = Map_GetBridgeCrossingCostOrZero(a4, a3);
  if ( !result )
    return *(unsigned __int8 *)(g_TerrainMoveProfileOffsets[*terrain_record] + a2 + 30);
  return result;
}
// 41402D: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00414150) --------------------------------------------------------
signed int  UnitStack_GetTileMoveCostOrZero(__int16 *a1, int a2, int a3, int a4)
{
  unsigned int occupant_stack_index; // edx
  int occupant_stack; // eax
  int tile_index_ptr; // eax
  signed int result; // eax
  unsigned __int16 *terrain_record; // ecx
  _BYTE merged_profile[96]; // [esp-1Ch] [ebp-64h] BYREF
  int v16; // [esp+44h] [ebp-4h]

  v16 = a3;
  tile_index_ptr = TILE_INDEX(a2, a4);
  occupant_stack_index = *(unsigned __int16 *)tile_index_ptr;
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF
      || (occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index, !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720))
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)a1 + 4) )
    {
      if ( *a1 != a2 || a1[1] != a4 )
        return 0;
    }
  }
  UnitStack_BuildMergedTerrainMoveProfile((intptr_t)merged_profile, (intptr_t)a1);
  occupant_stack_index = *(unsigned __int16 *)TILE_INDEX(a2, a4);
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF )
      return 0;
    occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index;
    if ( !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720)
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)a1 + 4) )
      return 0;
  }
  if ( ((1 << *((_BYTE *)a1 + 4)) & TILE_TRAP_OWNER_MASK(a2, a4)) == 1 << *((_BYTE *)a1 + 4)
    || MapTile_GetReligiousSiteCategory(a2, a4) )
  {
    return 0;
  }
  terrain_record = TILE_TERRAIN_RECORD(a2, a4);
  if ( terrain_record[2] != 0xFFFF )
    return merged_profile[29];
  if ( !g_PathingAllowBridgeCrossings )
    return (unsigned __int8)merged_profile[g_TerrainMoveProfileOffsets[*terrain_record] + 30];
  result = Map_GetBridgeCrossingCostOrZero(a2, a4);
  if ( !result )
    return (unsigned __int8)merged_profile[g_TerrainMoveProfileOffsets[*terrain_record] + 30];
  return result;
}
// 414194: conditional instruction was optimized away because edx.4<FFFFu
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00414350) --------------------------------------------------------
signed int  UnitStack_GetMoveCostToTile(int a1, int a2, int a3)
{
  return UnitStack_GetTileMoveCostOrZero((__int16 *)(gameData + 147174 + 725 * a1), a2, a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00414390) --------------------------------------------------------
signed int  UnitStack_GetMoveCostToTileIgnoringOccupancy(__int16 *a1, int a2, int a3)
{
  int v5; // ebp
  int v6; // edx
  __int16 v7; // di
  signed int result; // eax

  v5 = 2 * a3;
  v6 = gameData + 200 * a2 + v5 + 556374;
  v7 = *(_WORD *)v6;
  *(_WORD *)v6 = -1;
  result = UnitStack_GetTileMoveCostOrZero(a1, a2, 2 * a3, a3);
  *(_WORD *)v6 = v7;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00414400) --------------------------------------------------------
int * Path_InsertBridgeCornerWaypoints(int a1, char a2, int *a3)
{
  int scratch_path[101];
  int scratch_waypoint;
  int current_waypoint;
  int previous_waypoint;
  int current_row;
  int current_column;
  int previous_row;
  int previous_column;
  int row_delta;
  int column_delta;
  int corner_waypoint;
  int overflow;

  (void)a2;
  if ( !a3 || UnitStack_HasOnlyFlyingUnits(a1) )
    return a3;
  scratch_path[0] = 0;
  scratch_waypoint = 0;
  LOBYTE(scratch_waypoint) = *(_BYTE *)a1;
  BYTE1(scratch_waypoint) = *(_BYTE *)(a1 + 2);
  HIWORD(scratch_waypoint) = 0;
  if ( scratch_path[0] < 100 )
    scratch_path[++scratch_path[0]] = scratch_waypoint;
  while ( *a3 )
  {
    current_waypoint = a3[*a3];
    --*a3;
    if ( scratch_path[0] < 100 )
      scratch_path[++scratch_path[0]] = current_waypoint;
  }
  overflow = 0;
  while ( scratch_path[0] > 1 )
  {
    current_waypoint = scratch_path[scratch_path[0]];
    --scratch_path[0];
    previous_waypoint = scratch_path[scratch_path[0]];
    current_row = (unsigned __int8)current_waypoint;
    current_column = BYTE1(current_waypoint);
    previous_row = (unsigned __int8)previous_waypoint;
    previous_column = BYTE1(previous_waypoint);
    row_delta = previous_row - current_row;
    if ( row_delta < 0 )
      row_delta = -row_delta;
    column_delta = previous_column - current_column;
    if ( column_delta < 0 )
      column_delta = -column_delta;
    if ( row_delta == 1
      && column_delta == 1
      && TILE_TERRAIN_RECORD(previous_row, previous_column)[2] != 0xFFFF
      && TILE_TERRAIN_RECORD(current_row, current_column)[2] != 0xFFFF
      && (TILE_TERRAIN_RECORD(current_row, previous_column)[2] != 0xFFFF
       || TILE_TERRAIN_RECORD(previous_row, current_column)[2] != 0xFFFF)
      && (UnitStack_GetTileMoveCostOrZero((__int16 *)a1, current_row, 0, previous_column)
       || UnitStack_GetTileMoveCostOrZero((__int16 *)a1, previous_row, 0, current_column)) )
    {
      if ( *a3 < 100 )
        a3[++*a3] = current_waypoint;
      if ( 100 - *a3 <= 2 )
      {
        overflow = 1;
        break;
      }
      corner_waypoint = current_waypoint;
      if ( TILE_TERRAIN_RECORD(current_row, previous_column)[2] != 0xFFFF
        && UnitStack_GetTileMoveCostOrZero((__int16 *)a1, current_row, 0, previous_column) )
      {
        BYTE1(corner_waypoint) = previous_column;
      }
      else if ( TILE_TERRAIN_RECORD(previous_row, current_column)[2] != 0xFFFF
             && UnitStack_GetTileMoveCostOrZero((__int16 *)a1, previous_row, 0, current_column) )
      {
        LOBYTE(corner_waypoint) = previous_row;
      }
      else
      {
        continue;
      }
      HIWORD(corner_waypoint) = (HIWORD(current_waypoint) + HIWORD(previous_waypoint)) / 2;
      if ( *a3 < 100 )
        a3[++*a3] = corner_waypoint;
      if ( 100 - *a3 <= 2 )
      {
        overflow = 1;
        break;
      }
    }
    else
    {
      if ( *a3 < 100 )
        a3[++*a3] = current_waypoint;
      if ( 100 - *a3 <= 2 )
      {
        overflow = 1;
        break;
      }
    }
  }
  if ( overflow )
  {
    j__nfree_(a3);
    return 0;
  }
  return a3;
}
// 5202E4: using guessed type int gameData;

//----- (004147A0) --------------------------------------------------------
int * Unit_MoveTrack(int a1, int a2, int a3, int a4, DWORD a5, int a6)
{
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // esi
  int *result; // eax
  int v11; // edx
  int v12; // eax
  DWORD v13; // ebp
  int v14; // edx
  __int64 v15; // rax
  unsigned int v16; // ecx
  unsigned int v17; // ecx
  int v18; // ebp
  int v19; // esi
  int v20; // edi
  char v21; // al
  int v22; // ebx
  int v23; // esi
  int v24; // ebp
  int v25; // eax
  int i; // esi
  int v27; // ebx
  int v28; // ecx
  int v29; // eax
  int v30; // ecx
  unsigned __int16 *v31; // eax
  int *v32; // ebp
  unsigned __int16 v33; // dx
  int *v34; // eax
  unsigned __int8 v35; // dl
  int v36; // esi
  int v37; // ebx
  int v38; // edx
  int v39; // eax
  int v40; // eax
  _WORD *v41; // edx
  int v43; // eax
  char v44; // bl
  int v45; // ecx
  unsigned __int16 *v46; // edi
  _WORD *v47; // edx
  __int16 v48; // bx
  int v49; // ecx
  _BYTE v50[88]; // [esp+0h] [ebp-104h] BYREF
  int v51; // [esp+58h] [ebp-ACh]
  int v52; // [esp+5Ch] [ebp-A8h]
  int v53; // [esp+60h] [ebp-A4h]
  int v54; // [esp+64h] [ebp-A0h]
  int v55; // [esp+68h] [ebp-9Ch]
  BOOL v56; // [esp+6Ch] [ebp-98h]
  int v57; // [esp+70h] [ebp-94h] BYREF
  int v58; // [esp+74h] [ebp-90h] BYREF
  __int16 *v59; // [esp+78h] [ebp-8Ch]
  int v60; // [esp+7Ch] [ebp-88h]
  int v61; // [esp+80h] [ebp-84h]
  int v62; // [esp+84h] [ebp-80h]
  int v63; // [esp+88h] [ebp-7Ch]
  int v64; // [esp+8Ch] [ebp-78h]
  int v65; // [esp+90h] [ebp-74h]
  int v66; // [esp+94h] [ebp-70h]
  int v67; // [esp+98h] [ebp-6Ch] BYREF
  int v68; // [esp+9Ch] [ebp-68h] BYREF
  int v69; // [esp+A0h] [ebp-64h]
  int v70; // [esp+A4h] [ebp-60h]
  int v71; // [esp+A8h] [ebp-5Ch]
  int v72; // [esp+ACh] [ebp-58h]
  int v73; // [esp+B0h] [ebp-54h]
  int v74; // [esp+B4h] [ebp-50h]
  int v75; // [esp+B8h] [ebp-4Ch]
  int v76; // [esp+BCh] [ebp-48h]
  int v77; // [esp+C0h] [ebp-44h]
  int v78; // [esp+C4h] [ebp-40h]
  int v79; // [esp+C8h] [ebp-3Ch]
  int v80; // [esp+CCh] [ebp-38h]
  int v81; // [esp+D0h] [ebp-34h]
  int v82; // [esp+D4h] [ebp-30h]
  int v83; // [esp+D8h] [ebp-2Ch]
  int v84; // [esp+DCh] [ebp-28h]
  int v85; // [esp+E0h] [ebp-24h]
  int v86; // [esp+E4h] [ebp-20h]
  int v87; // [esp+E8h] [ebp-1Ch]
  int v88; // [esp+ECh] [ebp-18h]
  unsigned __int16 *v89; // [esp+F0h] [ebp-14h]
  unsigned __int8 v90; // [esp+F4h] [ebp-10h]
  unsigned __int8 v91; // [esp+F8h] [ebp-Ch]

  v51 = a1;
  v52 = a2;
  v53 = a4;
  v54 = a3;
  Debug_Log(a3, a4, a5, (int)aUnit_movetrack);
  v6 = a3;
  if ( v6 < 0 )
    return 0;
  v7 = v6;
  v8 = *(_DWORD *)(gameData + 140000);
  if ( v7 >= v8 )
    return 0;
  if ( a6 < 0 )
    return 0;
  v9 = *(_DWORD *)(gameData + 140004);
  if ( a6 >= v9 || v7 >= v8 || a6 >= v9 )
    return 0;
  result = (int *)UnitStack_GetMoveCostToTile(v51, v7, a6);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent(
      result ? "unit_move_target_cost" : "unit_move_target_blocked",
      v51,
      v7,
      a6,
      (int)result);
  if ( result )
  {
    v55 = dword_544D14;
    v56 = dword_544D14 != (_DWORD)&g_CursorDesc_Busy;
    if ( dword_544D10 )
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    v11 = 2 * v53;
    v12 = 2 * v53 + gameData + 200 * v52;
    LOWORD(v11) = *(_WORD *)(v12 + 556374);
    *(_WORD *)(v12 + 556374) = -1;
    v13 = v51;
    v87 = v11;
    v59 = (__int16 *)(725 * v51 + gameData + 147174);
    UnitStack_BuildMergedTerrainMoveProfile((intptr_t)v50, (intptr_t)v59);
    v57 = nmalloc_(0x4E20, 4);
    if ( !v57 )
    {
      Debug_Log(0, a6, v13, (int)aNotEnoughMem_3);
      App_RequestQuit((int)aNotEnoughMem_4);
    }
    v58 = nmalloc_(0x10000, 4);
    if ( !v58 )
    {
      Debug_Log(0, a6, v13, (int)aNotEnoughMem_5);
      App_RequestQuit((int)aNotEnoughMem_6);
    }
    v18 = 0;
    v83 = 0;
    v84 = 0;
    while ( v18 < *(_DWORD *)(gameData + 140000) )
    {
      v19 = 0;
      v69 = v84;
      v20 = 0;
      v70 = v83;
      while ( v19 < *(_DWORD *)(gameData + 140004) )
      {
        *(_WORD *)(v20 + v69 + v57) = -2;
        v21 = UnitStack_GetTileMoveCostFromMergedProfileOrZero(v59, (intptr_t)v50, v19++, v18);
        v20 += 2;
        *(_BYTE *)(v19 + v70 + v58 - 1) = v21;
      }
      ++v18;
      v83 += 256;
      v84 += 200;
    }
    if ( v52 >= v54 )
    {
      v61 = v52;
      v60 = v54;
    }
    else
    {
      v60 = v52;
      v61 = v54;
    }
    v22 = a6;
    if ( v53 >= a6 )
    {
      v63 = v53;
      v62 = a6;
    }
    else
    {
      v62 = v53;
      v63 = a6;
    }
    *(_WORD *)(200 * v52 + v57 + 2 * v53) = 0;
    v74 = 200 * v54;
    v65 = 25;
    v75 = 2 * a6;
    while ( 1 )
    {
      v23 = v61;
      DD_Pump((int)g_RenderState, v22);
      WorldMap_RedrawFrameForAIWhenEnabled(v22);
      v22 = 0;
      v64 = 0;
      v71 = v60;
      if ( v60 <= v23 )
      {
        v86 = 200 * v60;
        do
        {
          v24 = v62;
          if ( v62 <= v63 )
          {
            v80 = v86;
            v82 = v86;
            v85 = 2 * v62;
            do
            {
              v25 = *(unsigned __int16 *)(v85 + v82 + v57);
              if ( v25 != 65534 && v25 != 0xFFFF )
              {
                v81 = v85;
                for ( i = 0; i != 16; i += 2 )
                {
                  v27 = Map_NeighborDX[i] + v71;
                  v28 = v24 + Map_NeighborDY[i];
                  if ( v27 >= v60 && v27 <= v61 && v28 >= v62 && v28 <= v63 )
                  {
                    LOWORD(v29) = *(unsigned __int8 *)(v58 + (v27 << 8) + v28);
                    if ( (_BYTE)v29 )
                    {
                      if ( v27 != v71 && v28 != v24 )
                        v29 = (23 * (unsigned __int16)v29
                             - (__CFSHL__((23 * (unsigned __int16)v29) >> 31, 4)
                              + 16 * ((23 * (unsigned __int16)v29) >> 31))) >> 4;
                      v46 = (unsigned __int16 *)(v81 + v80 + v57);
                      v72 = *v46;
                      v73 = (unsigned __int16)v29 + v72;
                      v47 = (_WORD *)(v57 + 200 * v27 + 2 * v28);
                      if ( (unsigned __int16)*v47 > v73 )
                      {
                        v48 = *v46;
                        v64 = 1;
                        *v47 = v48 + v29;
                      }
                    }
                    else
                    {
                      *(_WORD *)(v57 + 200 * v27 + 2 * v28) = -1;
                    }
                  }
                }
              }
              v22 = v63;
              ++v24;
              v85 += 2;
            }
            while ( v24 <= v63 );
          }
          v86 += 200;
          ++v71;
        }
        while ( v71 <= v61 );
      }
      v30 = v64;
      if ( !v64 )
      {
        if ( *(unsigned __int16 *)(v75 + v74 + v57) != 65534 )
          break;
        if ( --v60 < 0 )
          v60 = v64;
        v49 = *(_DWORD *)(gameData + 140000);
        if ( ++v61 >= v49 )
          v61 = v49 - 1;
        if ( --v62 < 0 )
          v62 = 0;
        v30 = *(_DWORD *)(gameData + 140004);
        if ( ++v63 >= v30 )
          v63 = v30 - 1;
        v22 = v65 - 1;
        v65 = v22;
        if ( v22 == -1 )
          break;
      }
    }
    v31 = (unsigned __int16 *)(2 * a6 + v57 + 200 * v54);
    v32 = 0;
    v33 = *v31;
    v66 = 0;
    if ( v33 != 65534 )
    {
      LOWORD(v31) = *v31;
      v91 = v54;
      v89 = v31;
      v34 = (int *)Mem_Alloc(404, v30, v57, 0);
      v90 = a6;
      if ( v34 )
        *v34 = 0;
      HIWORD(v76) = HIWORD(dword_525570);
      LOBYTE(v76) = v91;
      v32 = v34;
      BYTE1(v76) = v90;
      v36 = *v34;
      HIWORD(v76) = (_WORD)v89;
      if ( v36 < 100 )
      {
        v30 = 4 * v36;
        *v34 = v36 + 1;
        v34[v36 + 1] = v76;
      }
      while ( (_WORD)v89 )
      {
        v37 = -1;
        v88 = (unsigned __int16)v89;
        do
        {
          v30 = -1;
          do
          {
            v79 = v90;
            v38 = v90 + v30;
            v39 = v91 + v37;
            if ( v39 >= 0
              && v39 < *(_DWORD *)(gameData + 140000)
              && v38 >= 0
              && v38 < *(_DWORD *)(gameData + 140004)
              && (unsigned __int16)v88 > *(_WORD *)(v57 + 200 * v39 + 2 * v38) )
            {
              LOWORD(v40) = *(unsigned __int8 *)(v79 + v58 + (v91 << 8));
              if ( v37 && v30 )
                v40 = (23 * (unsigned __int16)v40
                     - (__CFSHL__((23 * (unsigned __int16)v40) >> 31, 4)
                      + 16 * ((23 * (unsigned __int16)v40) >> 31))) >> 4;
              v41 = (_WORD *)(v57 + 200 * (v37 + v91) + 2 * (v30 + v90));
              v40 = (unsigned __int16)v40;
              if ( (unsigned __int16)*v41 == (unsigned __int16)v89 - (unsigned __int16)v40 )
              {
                v77 = v37;
                LOWORD(v40) = *v41;
                v78 = v30;
                v88 = v40;
              }
            }
            ++v30;
          }
          while ( v30 <= 1 );
          ++v37;
        }
        while ( v37 <= 1 );
        v91 += v77;
        LOBYTE(v76) = v91;
        v90 += v78;
        BYTE1(v76) = v90;
        v89 = (unsigned __int16 *)*(unsigned __int16 *)(200 * v91 + v57 + 2 * v90);
        HIWORD(v76) = (_WORD)v89;
        v43 = *v32;
        if ( 100 - *v32 <= 2 )
        {
          v66 = 1;
          break;
        }
        if ( v43 < 100 )
        {
          *v32 = v43 + 1;
          v32[v43 + 1] = v76;
        }
      }
      --*v32;
    }
    else if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_move_track_unreachable", v51, v54, a6, v65);
    }
    if ( v66 && v32 )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_overflow", v51, v54, a6, *v32);
      j__nfree_(v32);
      v32 = 0;
    }
    v44 = v52;
    *(_WORD *)(TILE_INDEX(v52, v53)) = v87;
    nfree_(v57);
    v57 = 0;
    nfree_(v58);
    v58 = 0;
    if ( v32 )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      {
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_built", v51, v54, a6, *v32);
        if ( *v32 )
        {
          int raw_count = *v32;
          int raw_sample_index;
          int raw_waypoint;

          raw_sample_index = raw_count;
          raw_waypoint = v32[raw_sample_index];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_raw_sample",
            v51,
            (unsigned __int8)raw_waypoint,
            BYTE1(raw_waypoint),
            raw_sample_index);
          raw_sample_index = raw_count * 3 / 4;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = v32[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              v51,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_sample_index = raw_count / 2;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = v32[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              v51,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_sample_index = raw_count / 4;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = v32[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              v51,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_waypoint = v32[1];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_raw_sample",
            v51,
            (unsigned __int8)raw_waypoint,
            BYTE1(raw_waypoint),
            1);
        }
      }
      v32 = Path_InsertBridgeCornerWaypoints(gameData + 147174 + 725 * v51, v44, v32);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      {
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_ready", v51, v54, a6, v32 ? *v32 : -1);
        if ( v32 && *v32 )
        {
          v45 = v32[*v32];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_next",
            v51,
            (unsigned __int8)v45,
            BYTE1(v45),
            HIWORD(v45));
          v45 = v32[1];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_first",
            v51,
            (unsigned __int8)v45,
            BYTE1(v45),
            HIWORD(v45));
        }
      }
    }
    if ( v56 && dword_544D10 )
      RenderState_SelectCursorDescriptor((int)g_RenderState, v55);
    return v32;
  }
  return result;
}
// 414801: conditional instruction was optimized away because edx.4>=0
// 414805: conditional instruction was optimized away because %arg_0.4>=0
// 4147D7: variable 'v6' is possibly undefined
// 4148F7: variable 'v14' is possibly undefined
// 414909: variable 'v16' is possibly undefined
// 414945: variable 'v17' is possibly undefined
// 414D58: variable 'v35' is possibly undefined
// 414FA3: variable 'v30' is possibly undefined
// 414FB0: variable 'v45' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 519808: using guessed type int dword_519808;
// 5202E4: using guessed type int gameData;
// 525570: using guessed type int dword_525570;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;
// 544D14: using guessed type int dword_544D14;

//----- (00415210) --------------------------------------------------------
_DWORD * Unit_MoveTrackNearTile(int a1, int a2, int a3, int a4, DWORD a5)
{
  int stack_record;
  int source_row;
  int source_column;
  int row_delta;
  int column_delta;
  __int16 saved_tile_occupant;
  int *raw_path;
  int *reverse_path;

  (void)a3;
  Debug_Log(a1, a4, a5, (int)aUnit_movetra_1);
  if ( a2 < 0 || a2 >= *(_DWORD *)(gameData + 140000) || a4 < 0 || a4 >= *(_DWORD *)(gameData + 140004) )
    return 0;

  stack_record = UNIT_STACK(a1);
  source_row = UNIT_STACK_TILE_ROW(stack_record);
  source_column = UNIT_STACK_TILE_COLUMN(stack_record);
  row_delta = source_row - a2;
  if ( row_delta < 0 )
    row_delta = -row_delta;
  column_delta = source_column - a4;
  if ( column_delta < 0 )
    column_delta = -column_delta;
  if ( row_delta == 0 && column_delta == 0 )
  {
    raw_path = (int *)Mem_Alloc(404, gameData, a4, a5);
    if ( raw_path )
      *raw_path = 0;
    return (_DWORD *)raw_path;
  }

  saved_tile_occupant = *(__int16 *)(TILE_INDEX(a2, a4));
  *(_WORD *)(TILE_INDEX(a2, a4)) = -1;
  WorldMap_DisableFrameRedraw();
  raw_path = Unit_MoveTrack(a1, source_row, a2, source_column, a4, a4);
  if ( raw_path )
  {
    reverse_path = (int *)Mem_Alloc(404, (int)raw_path, source_column, a4);
    if ( reverse_path )
    {
      *reverse_path = 0;
      while ( *raw_path )
      {
        int raw_count = *raw_path - 1;
        int step = raw_path[raw_count + 1];

        *raw_path = raw_count;
        if ( *reverse_path < 100 )
        {
          int reverse_count = *reverse_path;

          *reverse_path = reverse_count + 1;
          reverse_path[reverse_count + 1] = step;
        }
      }
      --*reverse_path;
      while ( *reverse_path > 0 )
      {
        int reverse_count = *reverse_path - 1;
        int step = reverse_path[reverse_count + 1];

        *reverse_path = reverse_count;
        if ( *raw_path < 100 )
        {
          int raw_count = *raw_path;

          *raw_path = raw_count + 1;
          raw_path[raw_count + 1] = step;
        }
      }
      nfree_((int)reverse_path);
    }
  }
  *(_WORD *)(TILE_INDEX(a2, a4)) = saved_tile_occupant;
  Render_LoadResourceSprite_v2();
  return (_DWORD *)raw_path;
}
// 415210: could not find valid save-restore pair for ebx
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00415450) --------------------------------------------------------
int * Building_GenerateApproachTrack(int a1, int a2, int a3, char a4, DWORD a5)
{
  int building_record;
  int building_row;
  int building_column;
  int building_kind;
  int stack_record;
  int source_row;
  int source_column;
  __int16 saved_origin_surface;
  unsigned __int16 building_tile;
  int *raw_path;
  int *reverse_path;

  (void)a3;
  (void)a4;
  Debug_Log(a1, (char)a2, a5, (int)aUnit_movetra_0);

  building_record = BUILDING_RECORD(a2);
  building_row = *(unsigned __int8 *)building_record;
  building_column = *(unsigned __int8 *)(building_record + 1);
  building_kind = *(signed char *)(building_record + 4);
  building_tile = (unsigned __int16)(a2 + 0x8000);

  *(_WORD *)(TILE_INDEX(building_row, building_column)) = -1;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(TILE_INDEX(building_row + 1, building_column)) = -1;
    *(_WORD *)(TILE_INDEX(building_row + 1, building_column + 1)) = -1;
    *(_WORD *)(TILE_INDEX(building_row, building_column + 1)) = -1;
  }

  saved_origin_surface = *(__int16 *)(gameData
                                    + TILE_TERRAIN_ROW_STRIDE * building_row
                                    + TILE_TERRAIN_RECORD_STRIDE * building_column
                                    + 4);
  *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) = 872;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) = 872;
    *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) = 872;
    *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) = 872;
  }

  WorldMap_DisableFrameRedraw();
  stack_record = UNIT_STACK(a1);
  source_row = UNIT_STACK_TILE_ROW(stack_record);
  source_column = UNIT_STACK_TILE_COLUMN(stack_record);
  raw_path = Unit_MoveTrack(a1, source_row, building_row, source_column, building_kind, building_column);
  if ( raw_path )
  {
    reverse_path = (int *)(uintptr_t)(unsigned int)Mem_Alloc(404, (int)(uintptr_t)raw_path, source_column, building_kind);
    if ( reverse_path )
    {
      *reverse_path = 0;
      while ( *raw_path )
      {
        int raw_count = *raw_path - 1;
        int step = raw_path[raw_count + 1];

        *raw_path = raw_count;
        if ( *reverse_path < 100 )
        {
          int reverse_count = *reverse_path;

          *reverse_path = reverse_count + 1;
          reverse_path[reverse_count + 1] = step;
        }
      }
      while ( *reverse_path > 1 )
      {
        int step = reverse_path[*reverse_path - 1];
        int step_row = (unsigned __int8)step;
        int step_column = BYTE1(step);

        if ( step_row == building_row && step_column == building_column )
        {
          --*reverse_path;
          continue;
        }
        if ( (building_kind == 1 || building_kind == 2)
          && step_row >= building_row
          && step_row <= building_row + 1
          && step_column >= building_column
          && step_column <= building_column + 1 )
        {
          --*reverse_path;
          continue;
        }
        break;
      }
      while ( *reverse_path )
      {
        int reverse_count = *reverse_path - 1;
        int step = reverse_path[reverse_count + 1];

        *reverse_path = reverse_count;
        if ( *raw_path < 100 )
        {
          int raw_count = *raw_path;

          *raw_path = raw_count + 1;
          raw_path[raw_count + 1] = step;
        }
      }
      nfree_((int)(uintptr_t)reverse_path);
    }
  }

  Render_LoadResourceSprite_v2();
  *(_WORD *)(TILE_INDEX(building_row, building_column)) = building_tile;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(TILE_INDEX(building_row + 1, building_column)) = building_tile;
    *(_WORD *)(TILE_INDEX(building_row + 1, building_column + 1)) = building_tile;
    *(_WORD *)(TILE_INDEX(building_row, building_column + 1)) = building_tile;
  }
  *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) =
    saved_origin_surface;
  if ( building_kind == 1 || building_kind == 2 )
  {
    *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * building_column + 4) =
      -1;
    *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * building_row + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) =
      -1;
    *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * (building_row + 1) + TILE_TERRAIN_RECORD_STRIDE * (building_column + 1) + 4) =
      -1;
  }

  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent(
      "building_path_ready",
      a1,
      building_row,
      building_column,
      raw_path ? *raw_path : -1);
  return raw_path;
}
// 415450: asm-backed rewrite; clears/restores building footprint around Unit_MoveTrack.
// 5202E4: using guessed type int gameData;

//----- (00415970) --------------------------------------------------------
int  Building_GenerateNearApproachTrack(int a1, int a2, int a3, char a4, DWORD a5)
{
  int v5; // edi
  DWORD v6; // ebp
  __int64 v7; // rdi
  int v8; // eax
  int v9; // edx
  int v10; // ebx
  int *v11; // ecx
  int *v12; // eax
  int *v13; // ecx
  int *v14; // edx
  int v15; // ebx
  int v16; // eax
  int v17; // ecx
  int v19; // eax
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // ebx
  __int16 v26; // [esp+8h] [ebp-28h]
  int v27; // [esp+18h] [ebp-18h]

  v26 = a2;
  v5 = 467 * a2;
  Debug_Log(a3, a4, a5, (int)aUnit_movetra_3);
  HIDWORD(v7) = *(unsigned __int8 *)(gameData + v5 + 509674);
  v6 = *(char *)(gameData + v5 + 509678);
  LODWORD(v7) = *(unsigned __int8 *)(gameData + v5 + 509675);
  *(_WORD *)(TILE_INDEX(HIDWORD(v7), v7)) = -1;
  if ( v6 == 1 || v6 == 2 )
  {
    v8 = 200 * (HIDWORD(v7) + 1);
    *(_WORD *)(v8 + gameData + 2 * v7 + 556374) = -1;
    *(_WORD *)(gameData + v8 + 2 * v7 + 556376) = -1;
    *(_WORD *)(gameData + 200 * HIDWORD(v7) + 2 * v7 + 556376) = -1;
  }
  WorldMap_DisableFrameRedraw();
  v9 *= 145;
  v10 = *(__int16 *)(gameData + 5 * v9 + 147176);
  v11 = Unit_MoveTrack(a1, *(__int16 *)(gameData + 5 * v9 + 147174), SHIDWORD(v7), v10, v6, v7);
  if ( v11 )
  {
    v12 = (int *)Mem_Alloc(404, (int)v11, v10, v6);
    v14 = v12;
    if ( v12 )
      *v12 = 0;
    for ( ; *v13; v14[v20 + 1] = v27 )
    {
      while ( 1 )
      {
        v19 = *v13 - 1;
        *v13 = v19;
        v20 = *v14;
        v27 = v13[v19 + 1];
        if ( *v14 < 100 )
          break;
        if ( !*v13 )
          goto LABEL_8;
      }
      *v14 = v20 + 1;
    }
LABEL_8:
    while ( *v14 > 1 )
    {
      v21 = v14[*v14 - 1];
      if ( v7 != __PAIR64__((unsigned __int8)v21, BYTE1(v21)) )
      {
        if ( v6 != 1 && v6 != 2 )
          break;
        if ( SHIDWORD(v7) > (unsigned __int8)v21 )
          break;
        if ( (unsigned __int8)v21 > HIDWORD(v7) + 1 )
          break;
        v22 = BYTE1(v21);
        if ( (int)v7 > v22 || v22 > (int)v7 + 1 )
          break;
      }
      --*v14;
    }
    if ( *v14 )
      --*v14;
    while ( 1 )
    {
      v15 = *v14;
      if ( !*v14 )
        break;
      *v14 = v15 - 1;
      v23 = v14[v15];
      v24 = *v13;
      if ( *v13 < 100 )
      {
        *v13 = v24 + 1;
        v13[v24 + 1] = v23;
      }
    }
    j__nfree_();
  }
  *(_WORD *)(2 * v7 + gameData + 200 * HIDWORD(v7) + 556374) = v26 + 0x8000;
  if ( v6 == 1 || v6 == 2 )
  {
    v16 = 200 * (HIDWORD(v7) + 1);
    *(_WORD *)(v16 + gameData + 2 * v7 + 556374) = v26 + 0x8000;
    *(_WORD *)(gameData + v16 + 2 * v7 + 556376) = v26 + 0x8000;
    *(_WORD *)(gameData + 200 * HIDWORD(v7) + 2 * v7 + 556376) = v26 + 0x8000;
  }
  Render_LoadResourceSprite_v2();
  return v17;
}
// 415A64: variable 'v9' is possibly undefined
// 415AAD: variable 'v13' is possibly undefined
// 415BA0: variable 'v17' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00415C90) --------------------------------------------------------
void  Pathing_EnableBridgeCrossings(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)aTrack_bridgeso);
  g_PathingAllowBridgeCrossings = 1;
}
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00415CB0) --------------------------------------------------------
void  Pathing_DisableBridgeCrossings(int a1, char a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)aTrack_bridge_0);
  g_PathingAllowBridgeCrossings = 0;
}
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00415CD0) --------------------------------------------------------
BOOL  QueuedPath_StartsAtTile(_DWORD *a1, int a2, int a3)
{
  int v3; // eax

  if ( !*a1 )
    return 0;
  v3 = a1[1];
  return (unsigned __int8)v3 == a2 && BYTE1(v3) == a3;
}

//----- (00415D00) --------------------------------------------------------
BOOL  QueuedPath_StartsInBuildingFootprint(_DWORD *a1, int a2)
{
  unsigned __int8 *v3; // eax
  int v4; // edx
  BOOL result; // eax
  unsigned __int8 v6; // bh

  v3 = (unsigned __int8 *)(UNIT_RECORD(a2));
  if ( !*a1 )
    return 0;
  v4 = a1[1];
  if ( !v3[4] )
    return (_WORD)v4 == *(_WORD *)v3;
  result = 0;
  if ( (unsigned __int8)v4 >= *v3 && (unsigned __int8)v4 <= *v3 + 1 )
  {
    v6 = v3[1];
    if ( BYTE1(v4) >= v6 && BYTE1(v4) <= v6 + 1 )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00415D80) --------------------------------------------------------
int  Math_SinDegreesQ16(signed int a1)
{
  int v1; // edx
  int v3; // edx

  v1 = a1;
  if ( a1 < 0 )
  {
    v3 = -a1;
    if ( -a1 >= 360 )
      v3 %= 360;
    return -g_MathSinTableQ16[v3];
  }
  else
  {
    if ( a1 >= 360 )
      v1 = a1 % 360;
    return g_MathSinTableQ16[v1];
  }
}
// 513434: using guessed type int dword_513434[363];

//----- (00415DD0) --------------------------------------------------------
void  initRandomSeed(char a1, DWORD a2)
{
  int v2; // ecx

  dword_525578 = time_();
  Debug_Log(v2, a1, a2, (int)aRandom_initSee);
}
// 415DE2: variable 'v2' is possibly undefined
// 47627F: using guessed type int time_(void);
// 525578: using guessed type int dword_525578;

//----- (00415DF0) --------------------------------------------------------
unsigned int  Rng_RandRange(int a1, int a2)
{
  unsigned int range;
  unsigned int seed;
  int result;

  dword_525578 ^= Time_Now(0, 0) + 0x34523471u;
  seed = (unsigned int)dword_525578 + 0x83356532u * (unsigned int)Time_Now(0, 0);
  dword_525578 = (int)seed;
  range = (unsigned int)((__int64)a2 + 1 - a1);
  if ( !range )
    return (unsigned int)a1;
  result = (int)(seed % range) + a1;
  return (unsigned int)result;
}
// 525578: using guessed type int dword_525578;

//----- (00415E40) --------------------------------------------------------
signed int  Math_CeilSqrt(signed int a1)
{
  int v2; // eax
  int v3; // ecx

  if ( a1 < 4 )
    return 1;
  v2 = a1 / 20 + 2;
  v3 = v2;
  do
  {
    while ( 1 )
    {
      v3 = (v3 + v2) / 2;
      v2 = a1 / v3;
      if ( v3 - a1 / v3 <= 0 )
        break;
      if ( v3 - a1 / v3 <= 1 )
        return v3;
    }
  }
  while ( a1 / v3 - v3 > 1 );
  return v3;
}

//----- (00415EA0) --------------------------------------------------------
__int16  WorldMap_DrawUnitStackOverlayGlyph(int a1, int a2, unsigned __int16 *a3)
{
  unsigned int v3; // eax
  int sprite; // eax

  v3 = *a3;
  if ( v3 >= 0x2D && *a3 <= 0x58u )
  {
    LOWORD(v3) = a3[2];
    if ( (unsigned __int16)v3 == 0xFFFF )
    {
      TextSprite_SetStyleFlag(1);
      sprite = DLX_GetSpriteForChar(dword_5202D8, *a3 - 45);
      LOWORD(v3) = Compat_RenderDeviceDrawMenuSprite(a1, a2, sprite, 1);
    }
  }
  return v3;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202D8: using guessed type int dword_5202D8;

//----- (00415F20) --------------------------------------------------------
int  WorldMap_DrawUnitStackWithOverlays(int result, int a2, int a3, int a4, unsigned __int16 *a5)
{
  int v7; // eax
  int v8; // ebp
  int SpriteForChar; // eax
  int v10; // ebx
  int v11; // eax
  int v12; // eax
  DWORD v13; // ebp
  int v14; // ecx
  signed int v15; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // [esp+64h] [ebp-20h]
  int v23; // [esp+6Ch] [ebp-18h]
  int v24; // [esp+74h] [ebp-10h]

  v24 = result;
  if ( result < 0x8000 )
  {
    result = gameData + 725 * result;
    if ( *(__int16 *)(result + 147180) != -1 )
    {
      if ( !*(_BYTE *)(result + 147894) || (result = *(unsigned __int8 *)(result + 147178), result == g_CurrentPlayerIndex) )
      {
        v7 = gameData + 725 * v24;
        v8 = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(v7 + 147180)];
        if ( g_ActiveUnitMoveTileIndex == -1 || g_ActiveUnitMoveTileIndex != v24 )
          SpriteForChar = UnitSpriteCache_FindEntryOrLoad(
                            *(unsigned __int16 *)(gameData + 725 * v24 + 147180),
                            *(_BYTE *)(gameData + 725 * v24 + 147178),
                            *(_BYTE *)(gameData + 725 * v24 + 147197) & 7,
                            *(_BYTE *)(gameData + 725 * v24 + 147179));
        else
          SpriteForChar = DLX_GetSpriteForChar(dword_523F78, 8 * *(unsigned __int8 *)(v7 + 147179) + dword_523F7C);
        v23 = SpriteForChar;
        v22 = a2 + 63;
        v10 = a3 + a4 - v8;
        if ( v24 == g_WorldMapAttentionFlashUnitIndex )
        {
          v11 = Time_Now(a3 + 63, v8);
          v12 = Math_SinDegreesQ16(30 * (g_WorldMapAttentionFlashStartTick - v11));
          v13 = a2 + 63;
          Sprite_DrawSimpleTrackingOffset(
            v23,
            a2,
            v10,
            a3,
            v22,
            v14,
            ((126 * v12 - (__CFSHL__((126 * v12) >> 31, 16) + ((126 * v12) >> 31 << 16))) >> 16) + 128,
            1u);
        }
        else
        {
          v13 = gameData;
          if ( *(_BYTE *)(725 * v24 + gameData + 147894) )
          {
            Sprite_DrawSimpleTrackingOffset(SpriteForChar, a2, v10, a3, v22, a3 + 63, 128, 1u);
          }
          else
          {
            Compat_RenderDeviceDrawMenuSprite(a2, v10, SpriteForChar, 1);
          }
        }
        if ( (g_UnitTypeFlags[22 * *(__int16 *)(gameData + 725 * v24 + 147180)] & 1) == 0 )
          WorldMap_DrawUnitStackOverlayGlyph(a2, a3, a5);
        v15 = Unit_GetSquadCount(725 * v24 + gameData + 147174);
        if ( v15 > 1 )
        {
          v16 = DLX_GetSpriteForChar(dword_5202C8, v15 + 5);
          Compat_RenderDeviceDrawMenuSprite(a2 + 12, v10 + 48, v16, 1);
        }
        if ( UnitStack_HasLowMoraleUnit(725 * v24 + gameData + 147174) )
        {
          v18 = DLX_GetSpriteForChar(dword_5202C8, 33);
          Compat_RenderDeviceDrawMenuSprite(a2 + 30, v10 + 48, v18, 1);
        }
        if ( *(_BYTE *)(gameData + 725 * v24 + 147894) )
        {
          v20 = DLX_GetSpriteForChar(dword_5202C8, 39);
          Compat_RenderDeviceDrawMenuSprite(a2 + 10, v10 + 5, v20, 1);
        }
        if ( v24 == g_UnitBlinkFlashUnitIndex )
        {
          v20 = DLX_GetSpriteForChar(dword_5202D0, dword_5269A4);
          Compat_RenderDeviceDrawMenuSprite(a2, a3, v20, 1);
        }
        result = gameData;
        if ( *(_DWORD *)(gameData + 147155) )
        {
          TextSprite_ActivateResourceSlot(3, 76, v13);
          return UI_DrawText(a2 + 20, a3 + 25, (int)aD_0);
        }
      }
    }
  }
  return result;
}
// 415F37: simplified comparisons for 'eax.4': ==FFFF || >=8000 became >=8000
// 416096: variable 'v14' is possibly undefined
// 41615F: variable 'v17' is possibly undefined
// 4161ED: variable 'v19' is possibly undefined
// 416268: variable 'v21' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512360: using guessed type int dword_512360;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;
// 5139F8: using guessed type int dword_5139F8;
// 5202C8: using guessed type int dword_5202C8;
// 5202D0: using guessed type int dword_5202D0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 52699C: using guessed type int g_WorldMapAttentionFlashStartTick;
// 5269A4: using guessed type int dword_5269A4;

//----- (004163F0) --------------------------------------------------------
unsigned int __thiscall Map_InitBuildingSwayJitterOffsets(void *this)
{
  int offset;
  unsigned int result;

  (void)this;
  offset = 0;
  do
  {
    byte_5269B8[offset] = Rng_RandRange(-20, 20);
    offset += 2;
    result = Rng_RandRange(-20, 20);
    byte_5269B7[offset] = result;
  }
  while ( offset != 30 );
  return result;
}

//----- (00416430) --------------------------------------------------------
unsigned __int8 *__thiscall Map_UpdateConstructionSiteSwayAnimation(void *this)
{
  unsigned __int8 *result; // eax
  unsigned int now; // eax
  int offset; // ecx
  int building_offset; // ecx
  unsigned __int8 *building_record; // eax
  char v9; // al
  char v10; // al

  (void)this;
  now = Time_Now(0, 0);
  result = (unsigned __int8 *)now;
  if ( (unsigned int)(dword_526980 + 20) <= now )
  {
    dword_526980 = Time_Now(0, 0);
    for ( offset = 0; offset != 30; offset += 2 )
    {
      if ( Rng_RandRange(0, 20) > 0x11 )
      {
        if ( byte_5269B8[offset] <= 10 || Rng_RandRange(0, 10) <= 5 )
        {
          if ( byte_5269B8[offset] >= -10 || Rng_RandRange(0, 10) <= 5 )
          {
            v9 = Rng_RandRange(-1, 1);
            byte_5269B8[offset] += v9;
          }
          else
          {
            ++byte_5269B8[offset];
          }
        }
        else
        {
          --byte_5269B8[offset];
        }
        if ( byte_5269B9[offset] <= 10 || Rng_RandRange(0, 10) <= 5 )
        {
          if ( byte_5269B9[offset] >= -10 || Rng_RandRange(0, 10) <= 5 )
          {
            v10 = Rng_RandRange(-1, 1);
            byte_5269B9[offset] += v10;
          }
          else
          {
            ++byte_5269B9[offset];
          }
        }
        else
        {
          --byte_5269B9[offset];
        }
      }
    }
    for ( building_offset = 0; building_offset != 46700; building_offset += 467 )
    {
      building_record = (unsigned __int8 *)(building_offset + gameData + 509674);
      result = building_record;
      if ( *(__int16 *)(building_record + 16) == -1 )
      {
        if ( building_record[4] )
        {
          WorldMap_RedrawTileIfVisible(building_record[0] + 1, building_record[1]);
          WorldMap_RedrawTileIfVisible(building_record[0], building_record[1]);
          WorldMap_RedrawTileIfVisible(building_record[0] + 1, building_record[1] + 1);
          result = (unsigned __int8 *)WorldMap_RedrawTileIfVisible(
                                        building_record[0],
                                        building_record[1] + 1);
        }
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 526980: using guessed type int dword_526980;

//----- (00416610) --------------------------------------------------------
unsigned int __thiscall Map_UpdateIdleAnimatedBuildings(void *this)
{
  unsigned int result; // eax
  int building_offset; // ecx
  unsigned __int8 *building_record; // eax
  unsigned __int8 building_kind; // dl

  (void)this;
  result = Time_Now(0, 0);
  if ( (unsigned int)(dword_526984 + 10) <= result )
  {
    dword_526984 = Time_Now(0, 0);
    dword_526998 = ((_BYTE)dword_526998 + 1) & 0xF;
    for ( building_offset = 0; building_offset != 46700; building_offset += 467 )
    {
      building_record = (unsigned __int8 *)(building_offset + gameData + 509674);
      result = (unsigned int)building_record;
      if ( *(char *)(building_record + 4) != -1 && !*(_WORD *)(building_record + 16) )
      {
        building_kind = building_record[4];
        if ( building_kind )
        {
          if ( building_kind <= 2u )
          {
            WorldMap_RedrawTileIfVisible(building_record[0], building_record[1]);
            WorldMap_RedrawTileIfVisible(building_record[0] + 1, building_record[1]);
            WorldMap_RedrawTileIfVisible(building_record[0], building_record[1] + 1);
            result = WorldMap_RedrawTileIfVisible(
                       building_record[0] + 1,
                       building_record[1] + 1);
          }
        }
        else
        {
          result = WorldMap_RedrawTileIfVisible(building_record[0], building_record[1]);
        }
      }
    }
  }
  return result;
}
// 416738: simplified comparisons for 'dl.1': <2u || ==2 became <3u
// 5202E4: using guessed type int gameData;
// 526984: using guessed type int dword_526984;
// 526998: using guessed type int dword_526998;

//----- (00416750) --------------------------------------------------------
int  WorldMap_DrawUnitAttentionFlashGlow(int a1, int a2, unsigned int a3)
{
  int i; // esi
  int v4; // eax
  int v5; // ebx
  int v6; // edx
  int SpriteForChar; // eax
  int result; // eax
  int v9; // edx
  int v10; // [esp-8h] [ebp-20h]
  int v11; // [esp+8h] [ebp-10h]

  v11 = a2;
  if ( a3 >= 2 )
  {
    v9 = a2 - 64;
    if ( a3 <= 2 )
    {
      v11 = v9;
    }
    else if ( a3 == 3 )
    {
      v11 = v9;
    }
  }
  for ( i = 0; i != 30; i += 2 )
  {
    v4 = byte_5269B8[i];
    v5 = v11 + byte_5269B9[i] + 52;
    if ( v4 <= 0 )
      v4 = -v4;
    v6 = byte_5269B9[i];
    if ( v6 <= 0 )
      v6 = -v6;
    v10 = 50 - (v4 + v6) / 3;
    SpriteForChar = DLX_GetSpriteForChar(dword_5202C8, 36);
    result = Sprite_DrawSimpleTrackingOffset(SpriteForChar, a1, v5, a2, a1 + 63, a2 + 63, v10, 1u);
  }
  return result;
}
// 5202C8: using guessed type int dword_5202C8;

//----- (00416850) --------------------------------------------------------
int  WorldMap_DrawMapTile(unsigned __int16 a1, unsigned __int16 a2, unsigned __int16 *a3)
{
  int v3; // edi
  signed int v4; // esi
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebx
  __int16 v13; // ax
  int v14; // edx
  int v15; // ebp
  int v16; // ecx
  int v17; // ebp
  __int16 v18; // ax
  int v19; // edx
  int v20; // ecx
  __int16 v21; // ax
  int v22; // edx
  int v23; // ebx
  int v24; // ebp
  int v25; // ebp
  int v26; // ecx
  __int16 v27; // ax
  int v28; // edx
  int v29; // ecx
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  signed int v37; // eax
  int v38; // eax
  int v39; // eax
  int v40; // ebx
  int v41; // edx
  int v42; // edx
  int v43; // eax
  DWORD v44; // ebp
  signed int v45; // edx
  unsigned __int8 *v46; // eax
  int v47; // eax
  DWORD v48; // ebp
  int v49; // ecx
  int v50; // edx
  _DWORD *v51; // ecx
  int v52; // eax
  int v53; // edx
  int v54; // edx
  int v55; // eax
  int v56; // ecx
  char v57; // dl
  int v58; // eax
  int v59; // eax
  int v60; // eax
  int v61; // eax
  int SpriteForChar; // eax
  int v63; // eax
  int v64; // eax
  unsigned __int16 v65; // ax
  int v66; // eax
  unsigned __int16 v67; // ax
  int v68; // eax
  unsigned __int16 v69; // ax
  int v70; // eax
  __int16 v71; // ax
  int v72; // eax
  int v73; // eax
  unsigned __int8 *v74; // eax
  int v75; // edx
  int v76; // eax
  int v77; // eax
  int v78; // eax
  int v79; // eax
  int v80; // eax
  int v81; // eax
  int v82; // eax
  int v83; // eax
  unsigned __int16 v84; // dx
  int v85; // eax
  int v86; // ebx
  int v87; // eax
  _DWORD *v88; // edx
  int v89; // ecx
  int v90; // edx
  int v91; // eax
  int v92; // ecx
  signed int v94; // [esp+C4h] [ebp-94h]
  int v95; // [esp+C8h] [ebp-90h]
  int v96; // [esp+CCh] [ebp-8Ch]
  int v97; // [esp+D0h] [ebp-88h]
  int v98; // [esp+D4h] [ebp-84h]
  int v99; // [esp+D8h] [ebp-80h]
  int v100; // [esp+DCh] [ebp-7Ch]
  int v101; // [esp+E4h] [ebp-74h]
  int v102; // [esp+F0h] [ebp-68h]
  int v103; // [esp+F4h] [ebp-64h]
  _DWORD *v104; // [esp+100h] [ebp-58h]
  int v105; // [esp+104h] [ebp-54h]
  int v106; // [esp+108h] [ebp-50h]
  int v107; // [esp+10Ch] [ebp-4Ch]
  int v108; // [esp+124h] [ebp-34h]
  __int16 v109; // [esp+130h] [ebp-28h]
  __int16 v112; // [esp+13Ch] [ebp-1Ch]
  __int16 v113; // [esp+140h] [ebp-18h]
  __int16 v114; // [esp+144h] [ebp-14h]
  int building_flag_variant;
  int building_flag_x;
  static const unsigned char building_flag_x_offsets[10] = { 0x38, 0x3C, 0x3E, 0x41, 0x41, 0x21, 0x21, 0x21, 0x23, 0x20 };

  v3 = ((int)a3 - gameData) / 14 / 100;
  v4 = ((int)a3 - gameData) / 14 % 100;
  v95 = (unsigned __int16)(a2 + 63);
  v96 = (unsigned __int16)(a1 + 63);
  v97 = a2;
  v98 = a1;
  if ( MiniMap_IsSpanWithinViewportBounds(a1, a2 + 63) )
    goto LABEL_2;
  v94 = Map_ClassifyFogOfWarOverlayForPlayer(v3, v4, VIEWED_PLAYER_INDEX);
  if ( !v94 )
  {
    Compat_RenderDeviceFillSolidRect(v98, v97, v96, v95, 1u);
    goto LABEL_2;
  }
  if ( *(_BYTE *)(gameData + 140016) == 2 )
  {
    v61 = *a3;
    if ( v61 != 0xFFFF )
    {
      SpriteForChar = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v61]);
      Compat_RenderDeviceDrawMenuSprite(v98, v97, SpriteForChar, 0);
    }
    v63 = a3[1];
    if ( v63 != 0xFFFF )
    {
      v64 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v63]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v64, 1);
    }
  }
  else
  {
    if ( *a3 != 0xFFFF && (*a3 < 0xCFu || *a3 > 0xD2u) )
    {
      HIWORD(v58) = 0;
      if ( *a3 != 187 )
      {
        LOWORD(v58) = *a3;
        v59 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v58]);
        Compat_RenderDeviceDrawMenuSprite(a1, a2, v59, 0);
      }
    }
    if ( a3[1] != 0xFFFF && (a3[1] < 0xD3u || a3[1] > 0xD7u) )
    {
      v60 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[a3[1]]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v60, 1);
    }
  }
  v6 = a3[2];
  if ( v6 != 0xFFFF )
  {
    v7 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v6]);
    Compat_RenderDeviceDrawMenuSprite(a1, a2, v7, 1);
  }
  v8 = ACTIVE_MISSION_INDEX;
  if ( v8 == 7 )
  {
    WorldMap_DrawMission07TreasureMarker(v3, v4);
  }
  else if ( v8 == 17 )
  {
    WorldMap_DrawMission17TreasureMarker(v3, v4);
  }
  if ( a3[2] < 0x362u || a3[2] > 0x36Cu )
  {
    if ( v4 <= 0 )
      v65 = -1;
    else
      v65 = *(a3 - 5);
    if ( v65 >= 0x364u && v65 <= 0x369u || v65 == 866 )
    {
      v66 = DLX_GetSpriteForChar(dword_5202C0, 863);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v66, 1);
    }
    if ( v4 >= 99 )
      v67 = -1;
    else
      v67 = a3[9];
    if ( v67 >= 0x367u && v67 <= 0x36Cu || v67 == 866 )
    {
      v68 = DLX_GetSpriteForChar(dword_5202C0, 862);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v68, 1);
    }
    if ( v3 <= 0 )
      v69 = -1;
    else
      v69 = *(a3 - 698);
    if ( v69 >= 0x363u && v69 <= 0x365u || v69 == 871 || v69 == 872 || v69 == 874 || v69 == 875 )
    {
      v70 = DLX_GetSpriteForChar(dword_5202C0, 864);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v70, 1);
    }
    if ( v3 >= 99 )
      v71 = -1;
    else
      v71 = a3[702];
    if ( v71 == 873 || v71 == 875 || v71 == 876 || v71 == 867 || v71 == 869 || v71 == 870 || v71 == 872 )
    {
      v72 = DLX_GetSpriteForChar(dword_5202C0, 865);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v72, 1);
    }
    if ( v4 >= 2 )
    {
      v73 = *(unsigned __int16 *)(2 * v4 + 200 * v3 + gameData + 556370);
      if ( (unsigned __int16)v73 >= 0x8000u && *(unsigned __int16 *)(2 * v4 + 200 * v3 + gameData + 556370) != 0xFFFF )
      {
        v74 = (unsigned __int8 *)(gameData + 509674 + 467 * (v73 - 0x8000));
        v75 = (char)v74[4];
        if ( (v75 == 2 || v75 == 1) && *v74 == v3 && v74[1] == v4 - 2 && !*((_WORD *)v74 + 8) )
        {
          v76 = DLX_GetSpriteForChar(dword_5202C0, 863);
          Compat_RenderDeviceDrawMenuSprite(a1, a2, v76, 1);
        }
      }
    }
  }
  if ( ((1 << g_CurrentPlayerIndex) & *(unsigned __int8 *)(v4 + gameData + 100 * v3 + 576374)) == 1 << g_CurrentPlayerIndex )
  {
    v9 = DLX_GetSpriteForChar(dword_5202C8, 6);
    Compat_RenderDeviceDrawMenuSprite(a1, a2, v9, 1);
  }
  v99 = 0;
  v100 = *(unsigned __int16 *)(TILE_INDEX(v3, v4));
  v101 = 0;
  if ( g_ActiveUnitMoveTileIndex == v100 )
    v101 = dword_523F74;
  if ( *(unsigned __int16 *)(TILE_INDEX(v3, v4)) <= 0x7FFFu
    && (g_UnitTypeFlags[22 * *(__int16 *)(gameData + 725 * v100 + 147180)] & 1) != 0 )
  {
    v99 = 1;
    v10 = a3[1];
    if ( v10 != 0xFFFF && a3[1] >= 0xD3u && a3[1] <= 0xD7u )
    {
      v11 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v10]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v11, 1);
    }
    if ( *a3 != 0xFFFF && (*a3 >= 0xCFu && *a3 <= 0xD2u || *a3 == 187) )
    {
      v77 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[*a3]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v77, 1);
    }
    WorldMap_DrawUnitStackWithOverlays(v100, a1, a2, v101, a3);
  }
  else
  {
    WorldMap_DrawUnitStackWithOverlays(v100, a1, a2, v101, a3);
    v77 = a3[1];
    if ( v77 != 0xFFFF && a3[1] >= 0xD3u && a3[1] <= 0xD7u )
    {
      v78 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v77]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v78, 1);
    }
    if ( *a3 != 0xFFFF && (*a3 >= 0xCFu && *a3 <= 0xD2u || *a3 == 187) )
    {
      v79 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[*a3]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v79, 1);
    }
  }
  v12 = 0;
  if ( v4 > 0 )
  {
    v13 = *(_WORD *)(200 * v3 + gameData + 2 * v4 + 556372);
    v109 = v13;
    if ( v13 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v13) )
      {
        if ( v14 == g_ActiveUnitMoveTileIndex )
          v12 = dword_523F74;
        WorldMap_DrawUnitStackWithOverlays(v109, a1, a2, v12 - 64, (unsigned __int16 *)(1400 * v3 + gameData + 14 * (v4 - 1)));
        v99 = 1;
      }
    }
  }
  if ( v4 > 0 && v3 > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v15 = *(__int16 *)(200 * (v3 - 1) + gameData + 2 * v4 + 556372);
    if ( v15 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v15, a1, a2, dword_523F74 - 64, (unsigned __int16 *)(gameData + 1400 * v16 + 14 * (v4 - 1)));
        v99 = 1;
      }
    }
  }
  if ( v4 < *(_DWORD *)(gameData + 140004) - 1 && v3 < *(_DWORD *)(gameData + 140000) && g_ActiveUnitMoveTileIndex != -1 )
  {
    v17 = *(__int16 *)(200 * (v3 + 1) + gameData + 2 * v4 + 556376);
    if ( v17 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v17, a1, a2, dword_523F74 + 64, (unsigned __int16 *)(gameData + 1400 * (v3 + 1) + 14 * (v4 + 1)));
        v99 = 1;
      }
    }
  }
  if ( v3 > 0 )
  {
    v18 = *(_WORD *)(TILE_INDEX((v3 - 1), v4));
    v113 = v18;
    if ( v18 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v18) )
      {
        v20 = 0;
        if ( v19 == g_ActiveUnitMoveTileIndex )
          v20 = dword_523F74;
        WorldMap_DrawUnitStackWithOverlays(v113, a1, a2, v20, (unsigned __int16 *)(gameData + 1400 * (v3 - 1) + 14 * v4));
        v99 = 1;
      }
    }
  }
  if ( v4 < *(_DWORD *)(gameData + 140004) - 1 )
  {
    v21 = *(_WORD *)(200 * v3 + gameData + 2 * v4 + 556376);
    v112 = v21;
    if ( v21 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v21) )
      {
        v23 = 0;
        if ( v22 == g_ActiveUnitMoveTileIndex )
          v23 = dword_523F74;
        WorldMap_DrawUnitStackWithOverlays(v112, a1, a2, v23 + 64, (unsigned __int16 *)(1400 * v3 + gameData + 14 * (v4 + 1)));
        v99 = 1;
      }
    }
  }
  if ( v4 < *(_DWORD *)(gameData + 140004) - 1 && v3 > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v24 = *(__int16 *)(200 * (v3 - 1) + gameData + 2 * v4 + 556376);
    if ( v24 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v24, a1, a2, dword_523F74 + 64, (unsigned __int16 *)(1400 * (v3 - 1) + gameData + 14 * (v4 + 1)));
        v99 = 1;
      }
    }
  }
  if ( v4 > 0 && v3 < *(_DWORD *)(gameData + 140000) - 1 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v25 = *(__int16 *)(200 * (v3 + 1) + gameData + 2 * v4 + 556372);
    if ( v25 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v25, a1, a2, dword_523F74 - 64, (unsigned __int16 *)(gameData + 1400 * v26 + 14 * (v4 - 1)));
        v99 = 1;
      }
    }
  }
  if ( v3 < *(_DWORD *)(gameData + 140000) - 1 )
  {
    v27 = *(_WORD *)(200 * (v3 + 1) + gameData + 2 * v4 + 556374);
    v114 = v27;
    if ( v27 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v27) )
      {
        v29 = 0;
        if ( v28 == g_ActiveUnitMoveTileIndex )
          v29 = dword_523F74;
        WorldMap_DrawUnitStackWithOverlays(v114, a1, a2, v29, (unsigned __int16 *)(1400 * (v3 + 1) + gameData + 14 * v4));
        v99 = 1;
      }
    }
  }
  if ( g_ActiveUnitMoveTileIndex != -1 )
  {
    if ( v4 > 0 )
    {
      v30 = *(unsigned __int16 *)(200 * v3 + gameData + 2 * v4 + 556372);
      if ( v30 != 0xFFFF && dword_523F74 > 0 && v30 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v30, a1, a2, dword_523F74 - 64, a3);
    }
    if ( v4 < *(_DWORD *)(gameData + 140004) - 1 )
    {
      v31 = *(unsigned __int16 *)(200 * v3 + gameData + 2 * v4 + 556376);
      if ( v31 != 0xFFFF && dword_523F74 < 0 && v31 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v31, a1, a2, dword_523F74 + 64, a3);
    }
    if ( v3 > 0 )
    {
      v32 = *(unsigned __int16 *)(TILE_INDEX((v3 - 1), v4));
      if ( v32 != 0xFFFF && dword_523F70 > 0 && v32 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v32, a1, a2, dword_523F74, a3);
    }
    if ( v3 < *(_DWORD *)(gameData + 140000) - 1 )
    {
      v33 = *(unsigned __int16 *)(200 * (v3 + 1) + gameData + 2 * v4 + 556374);
      if ( v33 != 0xFFFF && dword_523F70 < 0 && v33 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v33, a1, a2, dword_523F74, a3);
    }
    if ( v3 > 0 && v4 > 0 )
    {
      v34 = *(unsigned __int16 *)(gameData + 200 * (v3 - 1) + 2 * v4 + 556372);
      if ( v34 != 0xFFFF && dword_523F74 > 0 && dword_523F70 > 0 && v34 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v34, a1, a2, dword_523F74 - 64, a3);
    }
    if ( v3 > 0 && v4 < *(_DWORD *)(gameData + 140004) )
    {
      v35 = *(unsigned __int16 *)(200 * (v3 - 1) + gameData + 2 * v4 + 556376);
      if ( v35 != 0xFFFF && dword_523F74 < 0 && dword_523F70 > 0 && v35 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v35, a1, a2, dword_523F74 + 64, a3);
    }
    if ( v4 > 0 && v3 < *(_DWORD *)(gameData + 140000) )
    {
      v36 = *(unsigned __int16 *)(200 * (v3 + 1) + gameData + 2 * v4 + 556372);
      if ( v36 != 0xFFFF && dword_523F74 > 0 && dword_523F70 < 0 && v36 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v36, a1, a2, dword_523F74 - 64, a3);
    }
    v37 = *(_DWORD *)(gameData + 140000);
    if ( v4 < v37 && v3 < v37 )
    {
      v38 = *(unsigned __int16 *)(200 * (v3 + 1) + gameData + 2 * v4 + 556376);
      if ( v38 != 0xFFFF && dword_523F74 < 0 && dword_523F70 < 0 && v38 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v38, a1, a2, dword_523F74 + 64, a3);
    }
  }
  v39 = *(unsigned __int16 *)(TILE_INDEX(v3, v4));
  if ( (unsigned __int16)v39 >= 0x8000u && *(unsigned __int16 *)(TILE_INDEX(v3, v4)) != 0xFFFF )
  {
    v40 = v39 - 0x8000;
    v41 = 467 * (v39 - 0x8000);
    v102 = v41 + gameData + 509674;
    v42 = gameData + v41;
    v43 = *(__int16 *)(v102 + 16);
    v44 = *(char *)(v42 + 509678);
    if ( v43 != -1 )
      v43 = 3 * ((unsigned __int16)g_BuildingTypeMaxHitPoints[v44] - *(__int16 *)(v42 + 509690)) / (unsigned __int16)g_BuildingTypeMaxHitPoints[v44];
    v45 = v43;
    v46 = (unsigned __int8 *)(467 * v40 + gameData);
    v103 = v3 + 2 * (v4 - v46[509675]) - v46[509674];
    v47 = BuildingSpriteCache_GetOrLoadEntry(v44, v46[509676], v45, v46[509677], v103);
    Compat_RenderDeviceDrawMenuSprite(a1, a2, v47, 1);
    if ( *(__int16 *)(v102 + 16) == -1 && *(_BYTE *)(v102 + 4) )
    {
      WorldMap_DrawUnitAttentionFlashGlow(a1, a2, v103);
    }
    else if ( !*(_WORD *)(v102 + 16) )
    {
      if ( *(_BYTE *)(v102 + 4) )
        v79 = 0;
      else
        v79 = 5;
      v108 = (unsigned __int8)g_BuildingFlagYOffsets[2 * *(unsigned __int8 *)(v102 + 3) + 2 * v79]
           + ((*(unsigned __int8 *)(v102 + 1) - *(_DWORD *)(gameData + 140012)) << 6)
           + 16;
      if ( *(_BYTE *)(v102 + 4) )
        building_flag_variant = 0;
      else
        building_flag_variant = 80;
      building_flag_x = building_flag_x_offsets[*(unsigned __int8 *)(v102 + 3) + (building_flag_variant ? 5 : 0)]
                      + ((*(unsigned __int8 *)v102 - *(_DWORD *)(gameData + 140008)) << 6)
                      + 32;
      v81 = DLX_GetSpriteForChar(dword_5202D4, 16 * *(unsigned __int8 *)(v102 + 2) + building_flag_variant + dword_526998);
      Compat_RenderDeviceDrawMenuSprite(building_flag_x, v108, v81, 1);
    }
  }
  if ( !v99 && *(_BYTE *)(gameData + 140016) != 2 )
  {
    v82 = a3[1];
    if ( v82 != 0xFFFF && a3[1] >= 0xD3u && a3[1] <= 0xD7u )
    {
      v83 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v82]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v83, 1);
    }
    v84 = *a3;
    if ( *a3 != 0xFFFF && (*a3 >= 0xCFu && *a3 <= 0xD2u || v84 == 187) )
    {
      v85 = DLX_GetSpriteForChar(dword_5202C0, (unsigned __int16)word_522B38[v84]);
      Compat_RenderDeviceDrawMenuSprite(a1, a2, v85, 1);
    }
  }
  v48 = g_ActiveUnitMoveTileIndex;
  if ( g_ActiveUnitMoveTileIndex == -1 && g_SelectedUnitIndex != -1 )
  {
    v49 = 725 * g_SelectedUnitIndex + gameData + 147174;
    v50 = *(_DWORD *)(v49 + 316);
    v51 = (_DWORD *)(v49 + 316);
    if ( v50 )
    {
      if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      {
        v86 = -1;
        v87 = *v51 - 1;
        v104 = v51;
        if ( v87 >= 0 )
        {
          v48 = 4 * v87;
          v88 = v51;
          do
          {
            v105 = v88[1];
            if ( (unsigned __int8)v105 == v3 )
            {
              v89 = v3 ^ (unsigned __int8)v105;
              LOBYTE(v89) = BYTE1(v88[1]);
              if ( v89 == v4 )
                break;
            }
            --v87;
            ++v88;
          }
          while ( v87 >= 0 );
        }
        v90 = *v104 - 1;
        if ( v87 == v90 )
        {
          v86 = 64;
        }
        else
        {
          if ( v87 >= 0 )
          {
            v105 = v104[v90 - v87 + 1];
            v107 = v104[v90 - (v87 + 1) + 1];
            if ( v87 <= 0 )
            {
              LOBYTE(v106) = *(_BYTE *)(gameData + 725 * g_SelectedUnitIndex + 147174);
              BYTE1(v106) = *(_BYTE *)(gameData + 725 * g_SelectedUnitIndex + 147176);
            }
            else
            {
              v106 = v104[*v104 - v87 + 1];
            }
            v48 = 8 * Facing_DirectionFromDelta8((unsigned __int8)v106 - (unsigned __int8)v105, BYTE1(v106) - BYTE1(v105));
            v86 = Facing_DirectionFromDelta8((unsigned __int8)v107 - (unsigned __int8)v105, BYTE1(v107) - v92) + v48;
          }
          if ( v86 == -1 )
            goto LABEL_133;
        }
        if ( HIWORD(v105) > UnitStack_GetMinCurrentActionPoints(gameData + 147174 + 725 * g_SelectedUnitIndex) )
          v86 += 65;
        v91 = DLX_GetSpriteForChar(dword_5202CC, v86);
        Compat_RenderDeviceDrawMenuSprite(a1, a2, v91, 1);
        if ( !v99 )
          WorldMap_DrawUnitStackOverlayGlyph(a1, a2, a3);
      }
    }
  }
LABEL_133:
  if ( v100 == g_SelectedUnitIndex && g_ActiveUnitMoveTileIndex == -1 && PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
  {
    v52 = DLX_GetSpriteForChar(dword_5202C8, *(unsigned __int8 *)(gameData + 140016) == 1);
    Compat_RenderDeviceDrawMenuSprite(a1, a2, v52, 1);
  }
  if ( v3 == dword_5269A8 && v4 == dword_5269AC )
  {
    v52 = DLX_GetSpriteForChar(dword_5202D0, dword_5269B0 + 12);
    Compat_RenderDeviceDrawMenuSprite(a1, a2, v52, 1);
  }
  v53 = ACTIVE_MISSION_INDEX;
  if ( v53 == 1 )
  {
    WorldMap_DrawMission01ShrineMarker(v3, v4, a2, a1);
  }
  else if ( v53 == 11 )
  {
    WorldMap_DrawMission11ShrineMarker(v3, v4, a2, a1);
  }
  if ( v94 != -1 )
  {
    TextSprite_SetStyleFlag(1);
    v55 = DLX_GetSpriteForChar(g_FogOverlaySpriteSet, v94);
    Compat_RenderDeviceDrawMenuSprite(a1, a2, v55, 1);
  }
  UI_DrawTileHighlightOverlay(v3, v4, a2, a1);
  if ( dword_52698C )
    dword_52698C(v56, v4);
  if ( *(_DWORD *)(gameData + 147155) )
  {
    if ( *(_BYTE *)(gameData + 140016) == 1 )
      v57 = -9;
    else
      v57 = 76;
    TextSprite_ActivateResourceSlot(3, v57, v48);
    UI_DrawText(a1, a2, (int)aDD_0);
  }
LABEL_2:
  if ( *(_DWORD *)(gameData + 147151) )
  {
    if ( v4 > *(_DWORD *)(gameData + 140012) )
      Compat_RenderDeviceFillSolidRect(a1, a2, (unsigned __int16)(a1 + 63), a2, 1u);
    if ( v3 > *(_DWORD *)(gameData + 140008) )
      Compat_RenderDeviceFillSolidRect(a1, a2, a1, (unsigned __int16)(a2 + 63), 1u);
  }
  return MiniMap_BlitDirtyRectAndDrawViewportBox(a1, a2, a2 + 63, a1 + 63);
}
// 416BC0: conditional instruction was optimized away because %var_7C.4<10000u
// 416D71: variable 'v14' is possibly undefined
// 416E66: variable 'v16' is possibly undefined
// 416FE5: variable 'v19' is possibly undefined
// 4170BC: variable 'v22' is possibly undefined
// 41729A: variable 'v26' is possibly undefined
// 41734F: variable 'v28' is possibly undefined
// 4179CD: variable 'v54' is possibly undefined
// 417A33: variable 'v56' is possibly undefined
// 41854D: variable 'v105' is possibly undefined
// 418668: variable 'v92' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 513A70: using guessed type __int16 word_513A70[4];
// 5202C0: using guessed type int dword_5202C0;
// 5202C4: using guessed type int g_FogOverlaySpriteSet;
// 5202C8: using guessed type int dword_5202C8;
// 5202CC: using guessed type int dword_5202CC;
// 5202D0: using guessed type int dword_5202D0;
// 5202D4: using guessed type int dword_5202D4;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 522B38: using guessed type __int16 word_522B38[223];
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);
// 526998: using guessed type int dword_526998;
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418700) --------------------------------------------------------
int  WorldMap_RedrawViewport(int a1)
{
  int v2; // edi
  int v3; // ecx
  int v4; // esi
  int result; // eax
  int v6; // edi
  unsigned __int16 v7; // si
  int v8; // ebp
  int v9; // esi
  unsigned __int16 v10; // [esp+4h] [ebp-2Ch]
  int v11; // [esp+8h] [ebp-28h]
  int v12; // [esp+10h] [ebp-20h]

  v2 = 0;
  g_RenderDevice = (_UNKNOWN *)dword_5202E0;
  v10 = 16;
  do
  {
    v3 = 0;
    v4 = 32;
    do
    {
      result = WorldMap_DrawMapTile(
                 v4,
                 v10,
                 (unsigned __int16 *)(gameData
                                    + 1400 * (v3 + *(_DWORD *)(gameData + 140008))
                                    + 14 * (v2 + *(_DWORD *)(gameData + 140012))));
      ++v3;
      v4 += 64;
    }
    while ( v3 < 9 );
    ++v2;
    v10 += 64;
  }
  while ( v2 < 6 );
  if ( !dword_526994 )
  {
    v3 = 0;
    v9 = 32;
    do
    {
      result = WorldMap_DrawMapTile(
                 v9,
                 ((_WORD)v2 << 6) + 16,
                 (unsigned __int16 *)(14 * (v2 + *(_DWORD *)(gameData + 140012))
                                    + gameData
                                    + 1400 * (v3 + *(_DWORD *)(gameData + 140008))));
      ++v3;
      v9 += 64;
    }
    while ( v3 < 6 );
  }
  if ( dword_526990 )
    result = dword_526990();
  if ( a1 )
  {
    v12 = dword_544CFC >> byte_54512C;
    LOWORD(v3) = *(_WORD *)(dword_544D14 + 12);
    v6 = v3 + (dword_544CFC >> byte_54512C);
    v11 = dword_544D00 >> byte_54512C;
    v7 = *(_WORD *)(dword_544D14 + 16) + (dword_544D00 >> byte_54512C);
    v8 = dword_544D10;
    if ( (unsigned __int16)(dword_544CFC >> byte_54512C) < 0x20u )
    {
      LOWORD(v12) = 32;
      if ( dword_544D10 )
        Render_Pump();
    }
    if ( (unsigned __int16)v6 <= 0x20u )
    {
      LOWORD(v6) = 33;
      if ( v8 )
        Render_Pump();
    }
    if ( (unsigned __int16)v6 > 0x25Fu )
    {
      LOWORD(v6) = 607;
      if ( v8 )
        Render_Pump();
    }
    if ( (unsigned __int16)v12 >= 0x25Fu )
    {
      LOWORD(v12) = 606;
      if ( v8 )
        Render_Pump();
    }
    if ( (unsigned __int16)v11 < 0x10u )
    {
      LOWORD(v11) = 16;
      if ( v8 )
        Render_Pump();
    }
    if ( v7 > 0x1CFu )
    {
      v7 = 463;
      if ( v8 )
        Render_Pump();
    }
    if ( dword_544CFC >> byte_54512C < 52 || dword_544D00 >> byte_54512C < 36 )
      Render_Pump();
    Render_FillRect((_DWORD *)dword_5202E0, 0, 16, 32, 0x25Fu, v11, 0x20u, 0x10u);
    Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v11, 32, v12, v7, 0x20u, v11);
    if ( dword_544CFC >> byte_54512C >= 52 && dword_544D00 >> byte_54512C >= 36 )
      Input_Flush();
    result = Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v11, (unsigned __int16)v12, v6, v7, v12, v11);
    if ( v8 )
      result = Render_Present((int)&g_RenderState);
    if ( (unsigned __int16)v6 != 607 )
      result = Render_FillRect(
                 (_DWORD *)dword_5202E0,
                 0,
                 (unsigned __int16)v11,
                 (unsigned __int16)v6,
                 0x25Fu,
                 v7,
                 v6,
                 v11);
    if ( v7 != 463 )
      return Render_FillRect((_DWORD *)dword_5202E0, 0, v7, 32, 0x25Fu, 0x1CFu, 0x20u, v7);
  }
  return result;
}
// 418742: variable 'v3' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526990: using guessed type int (*dword_526990)(void);
// 526994: using guessed type int dword_526994;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D10: using guessed type int dword_544D10;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00418A90) --------------------------------------------------------
int  WorldMap_RedrawTileIfVisible(int result, int a2)
{
  int v2; // ebx
  unsigned __int16 v3; // si
  unsigned __int16 v4; // di
  int v5; // ebp

  if ( result < *(_DWORD *)(gameData + 140008) + 9
    && a2 < *(_DWORD *)(gameData + 140012) + 7
    && result >= *(_DWORD *)(gameData + 140008) )
  {
    v2 = *(_DWORD *)(gameData + 140012);
    if ( a2 >= v2
      && (a2 != v2 + 6 || result - *(_DWORD *)(gameData + 140008) < 6)
      && (a2 != *(_DWORD *)(gameData + 140012) + 6 || !dword_526994) )
    {
      v3 = (((_WORD)result - *(_WORD *)(gameData + 140008)) << 6) + 32;
      v4 = (((_WORD)a2 - *(_WORD *)(gameData + 140012)) << 6) + 16;
      g_RenderDevice = (_UNKNOWN *)dword_5202E0;
      WorldMap_DrawMapTile(v3, v4, (unsigned __int16 *)(14 * a2 + gameData + 1400 * result));
      v5 = dword_544D10;
      RenderState_PumpIfRectInViewBounds(g_RenderState, v3, v3 + 64, v4, v4 + 64);
      result = Render_FillRect((_DWORD *)dword_5202E0, 0, v4, v3, v3 + 63, v4 + 63, v3, v4);
      if ( v5 )
        return Render_Present((int)g_RenderState);
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 526994: using guessed type int dword_526994;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00418C00) --------------------------------------------------------
int  UI_CenterWorldMapViewportOnRectIfFit(int result, int a2, int a3, int a4)
{
  int v4; // ecx
  int v5; // ebx

  if ( a4 - result <= 9 && a3 - a2 <= 7 )
  {
    *(_DWORD *)(gameData + 140008) = (a4 + result) / 2 - 3;
    *(_DWORD *)(gameData + 140012) = (a3 + a2) / 2 - 3;
    v4 = *(_DWORD *)(gameData + 140000);
    if ( *(_DWORD *)(gameData + 140008) + 9 >= v4 )
      *(_DWORD *)(gameData + 140008) = v4 - 10;
    v5 = *(_DWORD *)(gameData + 140004);
    if ( *(_DWORD *)(gameData + 140012) + 7 >= v5 )
      *(_DWORD *)(gameData + 140012) = v5 - 8;
    if ( *(int *)(gameData + 140008) < 0 )
      *(_DWORD *)(gameData + 140008) = 0;
    if ( *(int *)(gameData + 140012) < 0 )
      *(_DWORD *)(gameData + 140012) = 0;
    return WorldMap_RedrawViewport(1);
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00418CE0) --------------------------------------------------------
int  UI_CenterWorldMapViewportOnTile(int a1, int a2)
{
  int v2; // ecx
  int v3; // ebx

  *(_DWORD *)(gameData + 140008) = a1 - 3;
  *(_DWORD *)(gameData + 140012) = a2 - 3;
  v2 = *(_DWORD *)(gameData + 140000);
  if ( *(_DWORD *)(gameData + 140008) + 9 >= v2 )
    *(_DWORD *)(gameData + 140008) = v2 - 10;
  v3 = *(_DWORD *)(gameData + 140004);
  if ( *(_DWORD *)(gameData + 140012) + 7 >= v3 )
    *(_DWORD *)(gameData + 140012) = v3 - 8;
  if ( *(int *)(gameData + 140008) < 0 )
    *(_DWORD *)(gameData + 140008) = 0;
  if ( *(int *)(gameData + 140012) < 0 )
    *(_DWORD *)(gameData + 140012) = 0;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;

//----- (00418D90) --------------------------------------------------------
int  UI_StartWorldMapUnitAttentionFlash(int a1, int a2, int a3)
{
  int result; // eax

  g_WorldMapAttentionFlashUnitIndex = a1;
  result = Time_Now(a3, a2);
  g_WorldMapAttentionFlashStartTick = result;
  return result;
}
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;
// 52699C: using guessed type int g_WorldMapAttentionFlashStartTick;

//----- (00418DA0) --------------------------------------------------------
void UI_UpdateWorldMapUnitAttentionFlash()
{
  int v0; // edx
  int v1; // ecx
  int v2; // eax

  if ( g_WorldMapAttentionFlashUnitIndex != -1 )
  {
    WorldMap_RedrawTileIfVisible(
      *(__int16 *)(gameData + 725 * g_WorldMapAttentionFlashUnitIndex + 147174),
      *(__int16 *)(gameData + 725 * g_WorldMapAttentionFlashUnitIndex + 147176));
    if ( (unsigned int)(30 * (Time_Now(v1, v0) - g_WorldMapAttentionFlashStartTick)) >= 0x708 )
    {
      v2 = g_WorldMapAttentionFlashUnitIndex;
      g_WorldMapAttentionFlashUnitIndex = -1;
      Map_RedrawUnitFootprintByIndex(v2);
    }
  }
}
// 418DE4: variable 'v1' is possibly undefined
// 418DE4: variable 'v0' is possibly undefined
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;
// 5202E4: using guessed type int gameData;
// 52699C: using guessed type int g_WorldMapAttentionFlashStartTick;

//----- (00418E20) --------------------------------------------------------
BOOL UI_IsWorldMapUnitAttentionFlashActive()
{
  return g_WorldMapAttentionFlashUnitIndex != -1;
}
// 5139F4: using guessed type int g_WorldMapAttentionFlashUnitIndex;

//----- (00418E30) --------------------------------------------------------
int  UI_StartUnitBlinkFlash(int a1, int a2, int a3)
{
  int result; // eax

  g_UnitBlinkFlashUnitIndex = a1;
  result = Time_Now(a3, a2);
  dword_5269A0 = result;
  dword_5269A4 = 0;
  return result;
}
// 5139F8: using guessed type int dword_5139F8;
// 5269A0: using guessed type int dword_5269A0;
// 5269A4: using guessed type int dword_5269A4;

//----- (00418E50) --------------------------------------------------------
void __fastcall UI_UpdateUnitBlinkFlash(int a1, int a2)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax

  if ( g_UnitBlinkFlashUnitIndex != -1 && Time_Now(a1, a2) > (unsigned int)(dword_5269A0 + 10) )
  {
    v3 = Time_Now(v2, dword_5269A0 + 10);
    dword_5269A4 += (v3 - dword_5269A0) / 0xAu;
    dword_5269A0 = Time_Now(10, (v3 - dword_5269A0) % 0xAu);
    v4 = g_UnitBlinkFlashUnitIndex;
    if ( dword_5269A4 >= 12 )
      g_UnitBlinkFlashUnitIndex = -1;
    Map_RedrawUnitFootprintByIndex(v4);
  }
}
// 418E70: variable 'v2' is possibly undefined
// 5139F8: using guessed type int dword_5139F8;
// 5269A0: using guessed type int dword_5269A0;
// 5269A4: using guessed type int dword_5269A4;

//----- (00418EC0) --------------------------------------------------------
int  UI_StartTileBlinkFlash(int a1, int a2, int a3)
{
  int result; // eax

  dword_5269AC = a2;
  dword_5269A8 = a1;
  dword_5269B0 = 0;
  result = Time_Now(a3, 0);
  unk_5269B4 = result;
  return result;
}
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418EE0) --------------------------------------------------------
void __fastcall UI_UpdateTileBlinkFlash(int a1, int a2)
{
  int v2; // ecx
  int v3; // eax
  int v4; // eax

  if ( dword_5269A8 != -1 && Time_Now(a1, a2) > (unsigned int)(unk_5269B4 + 10) )
  {
    v3 = Time_Now(v2, unk_5269B4 + 10);
    dword_5269B0 += (v3 - unk_5269B4) / 0xAu;
    unk_5269B4 = Time_Now(10, (v3 - unk_5269B4) % 0xAu);
    v4 = dword_5269A8;
    if ( dword_5269B0 >= 8 )
      dword_5269A8 = -1;
    WorldMap_RedrawTileIfVisible(v4, dword_5269AC);
  }
}
// 418F00: variable 'v2' is possibly undefined
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418F60) --------------------------------------------------------
signed int  UI_HighlightTile(int a1, int a2)
{
  signed int slot_index; // eax

  slot_index = 0;
  while ( a1 != g_TileHighlightSlots[slot_index].tile_x || a2 != g_TileHighlightSlots[slot_index].tile_y )
  {
    ++slot_index;
    if ( slot_index >= 8 )
    {
      slot_index = 0;
      if ( g_TileHighlightSlots[0].tile_x == -1 )
      {
LABEL_8:
        g_TileHighlightSlots[slot_index].tile_x = a1;
        g_TileHighlightSlots[slot_index].tile_y = a2;
      }
      else
      {
        while ( 1 )
        {
          ++slot_index;
          if ( slot_index >= 8 )
            break;
          if ( g_TileHighlightSlots[slot_index].tile_x == -1 )
            goto LABEL_8;
        }
      }
      return 8 * slot_index;
    }
  }
  return 8 * slot_index;
}

//----- (00418FE0) --------------------------------------------------------
int __thiscall UI_ClearTileHighlight(void *this)
{
  (void)this;
  memset(g_TileHighlightSlots, 0xFF, sizeof(g_TileHighlightSlots));
  return (int)g_TileHighlightSlots;
}

//----- (00419000) --------------------------------------------------------
// positive sp value has been detected, the output may be wrong!
int  UI_DrawTileHighlightOverlay(int a1, int a2, int a3, int a4)
{
  int slot_index; // eax
  unsigned __int16 SpriteWidth; // ax
  unsigned __int16 SpriteHeight; // ax
  int centered_x; // esi
  int centered_y; // edi
  int SpriteForChar; // eax

  if ( g_ActiveUnitMoveTileIndex != -1 )
    return Noop_WorldMapFrameRedrawHook();
  slot_index = 0;
  while ( a1 != g_TileHighlightSlots[slot_index].tile_x || a2 != g_TileHighlightSlots[slot_index].tile_y )
  {
    ++slot_index;
    if ( slot_index >= 8 )
      return Noop_WorldMapFrameRedrawHook();
  }
  SpriteWidth = DLX_GetSpriteWidth(dword_5202C8, 0x28u);
  centered_x = a3 + (64 - SpriteWidth) / 2;
  SpriteHeight = DLX_GetSpriteHeight(dword_5202C8, 0x28u);
  centered_y = a4 + (64 - SpriteHeight) / 2;
  SpriteForChar = DLX_GetSpriteForChar(dword_5202C8, 40);
  return Sprite_DrawSimpleTrackingOffset(SpriteForChar, centered_y, centered_x, a3, a4 + 63, a3 + 63, 80, 1u);
}
// 4190A8: positive sp value 8 has been found
// 419030: using guessed type int nullsub_1(void);
// 512360: using guessed type int dword_512360;
// 5202C8: using guessed type int dword_5202C8;

//----- (004190B0) --------------------------------------------------------
void BattleLog_Disable()
{
  battleLogEnabled = 0;
}
// 5139FC: using guessed type int battleLogEnabled;

//----- (004190C0) --------------------------------------------------------
void BattleLog_Enable()
{
  battleLogEnabled = 1;
}
// 5139FC: using guessed type int battleLogEnabled;

//----- (004190D0) --------------------------------------------------------
void  createLogFiles(int a1, int a2, DWORD a3)
{
  FILE *log_file;

  (void)a1;
  (void)a2;
  (void)a3;
  if ( logEnabled )
  {
    log_file = fopen(aClash_log, "wb");
    if ( log_file )
      fclose(log_file);
    log_file = fopen(aBattle_log, "wb");
    if ( log_file )
      fclose(log_file);
    dword_526A20 = 0;
  }
}
// 526A1C: using guessed type int logEnabled;
// 526A20: using guessed type int dword_526A20;

//----- (00419110) --------------------------------------------------------
int  Battle_StoreLastOutcomeValue(int result)
{
  dword_526A20 = result;
  return result;
}
// 526A20: using guessed type int dword_526A20;

static int Compat_RenderDeviceDrawMenuSprite(int left, int top, int sprite_for_char, unsigned char draw_mode);

static int Compat_CountPrintfArgs32(const char *format)
{
  int count;

  count = 0;
  while ( format && *format )
  {
    if ( *format++ != '%' )
      continue;
    if ( *format == '%' )
    {
      ++format;
      continue;
    }
    while ( *format == '#' || *format == '0' || *format == '-' || *format == ' ' || *format == '+' )
      ++format;
    if ( *format == '*' )
    {
      ++count;
      ++format;
    }
    else
    {
      while ( *format >= '0' && *format <= '9' )
        ++format;
    }
    if ( *format == '.' )
    {
      ++format;
      if ( *format == '*' )
      {
        ++count;
        ++format;
      }
      else
      {
        while ( *format >= '0' && *format <= '9' )
          ++format;
      }
    }
    if ( *format == 'I' && format[1] == '6' && format[2] == '4' )
      format += 3;
    else if ( *format == 'h' || *format == 'l' || *format == 'L' || *format == 'N' || *format == 'F' || *format == 'w' )
    {
      if ( (*format == 'h' && format[1] == 'h') || (*format == 'l' && format[1] == 'l') )
        ++format;
      ++format;
    }
    if ( *format )
    {
      ++count;
      ++format;
    }
  }
  return count;
}

//----- (00419120) --------------------------------------------------------
void  Debug_Log(int a1, char a2, DWORD a3, int a4, ...)
{
  const CHAR *log_path;
  unsigned __int8 *open_mode;
  int output_handle;
  const char *format;
  unsigned int centiseconds;
  unsigned int seconds;
  unsigned int minutes;
  int low32_line_ptr;
  char *line_buffer;
  int line_length;

  if ( !logEnabled || !battleLogEnabled )
    return;

  /*
   * The Watcom-style formatter/stream path under `sub_476301` / `sub_488DF2`
   * is still being re-emitted for x86_64. Keep runtime-side sprite/resource
   * probes alive by neutralizing logging rather than crashing inside that
   * auxiliary path.
   */
  return;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5139FC: using guessed type int battleLogEnabled;
// 526A1C: using guessed type int logEnabled;
// 526A20: using guessed type int dword_526A20;

//----- (004191F0) --------------------------------------------------------
unsigned __int16 * UI_DrawWidgetIcon(unsigned __int16 *result, int a2)
{
  unsigned char *widget;
  int left;
  int top;
  int flags;
  unsigned int sprite_set_holder;
  unsigned int sprite_set;
  int sprite_index;
  int overlay_sprite_index;
  int sprite_for_char;

  widget = (unsigned char *)result;
  left = *(_DWORD *)(widget + 0);
  top = *(_DWORD *)(widget + 4);
  flags = *(_DWORD *)(widget + 8);
  sprite_set_holder = *(_DWORD *)(widget + 12);
  sprite_set = sprite_set_holder ? *(_DWORD *)(uintptr_t)sprite_set_holder : 0;
  sprite_index = (flags & 1) != 0 ? *(_DWORD *)(widget + 16) : *(_DWORD *)(widget + 20);
  overlay_sprite_index = *(_DWORD *)(widget + 24);
  if ( sprite_set && sprite_index != -1 )
  {
    sprite_for_char = DLX_GetSpriteForChar(sprite_set, sprite_index);
    Compat_RenderDeviceDrawMenuSprite(left, top, sprite_for_char, 0);
    if ( (flags & 4) != 0 && overlay_sprite_index != -1 )
    {
      sprite_for_char = DLX_GetSpriteForChar(sprite_set, overlay_sprite_index);
      Compat_RenderDeviceDrawMenuSprite(left, top, sprite_for_char, 1);
    }
    if ( a2 && g_RenderDevice != &unk_51D4C0 )
    {
      Render_FillRect(
        g_RenderDevice,
        0,
        (unsigned __int16)top,
        (unsigned __int16)left,
        (unsigned __int16)(top + DLX_GetSpriteHeight(sprite_set, sprite_index) - 1),
        (unsigned __int16)(left + DLX_GetSpriteWidth(sprite_set, sprite_index) - 1),
        (unsigned __int16)left,
        (unsigned __int16)top);
    }
    if ( g_RenderDevice == &unk_51D4C0 && dword_544D10 )
      return (unsigned __int16 *)Render_Present((int)g_RenderState);
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

static int Compat_RenderDeviceFillSolidRect(
        unsigned __int16 left,
        unsigned __int16 top,
        unsigned __int16 right,
        unsigned __int16 bottom,
        unsigned char color)
{
  _DWORD *surface;
  unsigned char *surface_pixels;
  int pitch;
  int surface_width;
  int surface_height;
  int row;

  if ( !g_RenderDevice )
    return 0;
  surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
  if ( !surface || !RenderSurface_IsLinearSoftware(surface) )
    return 0;
  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  if ( !surface_pixels )
    return 0;

  pitch = *(unsigned __int16 *)surface;
  surface_width = *(unsigned __int16 *)surface;
  surface_height = *((unsigned __int16 *)surface + 1);
  if ( left > right || top > bottom || left >= surface_width || top >= surface_height )
    return 0;
  if ( right >= surface_width )
    right = surface_width - 1;
  if ( bottom >= surface_height )
    bottom = surface_height - 1;

  for ( row = top; row <= bottom; ++row )
    memset(surface_pixels + row * pitch + left, color, right - left + 1);
  return 0;
}

static int Compat_RenderSurfaceCopyRect(
        _DWORD *source,
        _DWORD *destination,
        int source_left,
        int source_top,
        int source_right,
        int source_bottom,
        int destination_left,
        int destination_top)
{
  _DWORD *source_surface;
  _DWORD *destination_surface;
  unsigned char *source_pixels;
  unsigned char *destination_pixels;
  int source_pitch;
  int destination_pitch;
  int source_width;
  int source_height;
  int destination_width;
  int destination_height;
  int copy_width;
  int copy_height;
  int row;

  if ( !source )
    source = &unk_51D4C0;
  if ( !destination )
    destination = &unk_51D4C0;
  source_surface = RenderSurface_ResolvePrimaryCompanion(source);
  destination_surface = RenderSurface_ResolvePrimaryCompanion(destination);
  if ( !source_surface || !destination_surface
    || !RenderSurface_IsLinearSoftware(source_surface)
    || !RenderSurface_IsLinearSoftware(destination_surface) )
  {
    return 0;
  }

  source_pixels = (unsigned char *)(uintptr_t)(unsigned int)source_surface[1];
  destination_pixels = (unsigned char *)(uintptr_t)(unsigned int)destination_surface[1];
  if ( !source_pixels || !destination_pixels )
    return 0;

  source_pitch = *(unsigned __int16 *)source_surface;
  destination_pitch = *(unsigned __int16 *)destination_surface;
  source_width = source_pitch;
  destination_width = destination_pitch;
  source_height = *((unsigned __int16 *)source_surface + 1);
  destination_height = *((unsigned __int16 *)destination_surface + 1);
  copy_width = source_right - source_left + 1;
  copy_height = source_bottom - source_top + 1;
  if ( copy_width <= 0 || copy_height <= 0 )
    return 1;

  if ( source_left < 0 )
  {
    destination_left -= source_left;
    copy_width += source_left;
    source_left = 0;
  }
  if ( source_top < 0 )
  {
    destination_top -= source_top;
    copy_height += source_top;
    source_top = 0;
  }
  if ( destination_left < 0 )
  {
    source_left -= destination_left;
    copy_width += destination_left;
    destination_left = 0;
  }
  if ( destination_top < 0 )
  {
    source_top -= destination_top;
    copy_height += destination_top;
    destination_top = 0;
  }
  if ( source_left >= source_width || source_top >= source_height
    || destination_left >= destination_width || destination_top >= destination_height )
  {
    return 1;
  }
  if ( source_left + copy_width > source_width )
    copy_width = source_width - source_left;
  if ( destination_left + copy_width > destination_width )
    copy_width = destination_width - destination_left;
  if ( source_top + copy_height > source_height )
    copy_height = source_height - source_top;
  if ( destination_top + copy_height > destination_height )
    copy_height = destination_height - destination_top;
  if ( copy_width <= 0 || copy_height <= 0 )
    return 1;

  for ( row = 0; row < copy_height; ++row )
    memmove(
      destination_pixels + (destination_top + row) * destination_pitch + destination_left,
      source_pixels + (source_top + row) * source_pitch + source_left,
      copy_width);
  return 1;
}

static int Compat_RenderDeviceDrawMenuSprite(int left, int top, int sprite_for_char, unsigned char draw_mode)
{
  _DWORD *surface;
  unsigned char *surface_pixels;
  unsigned char *stream;
  unsigned char *stream_base;
  unsigned char *stream_end;
  int pitch;
  int surface_width;
  int surface_height;
  int width;
  int height;
  int format;
  int entry_size;
  int row;

  if ( !g_RenderDevice || !sprite_for_char )
    return 0;
  surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
  if ( !surface || !RenderSurface_IsLinearSoftware(surface) )
    return 0;
  surface_pixels = (unsigned char *)(uintptr_t)(unsigned int)surface[1];
  if ( !surface_pixels )
    return 0;

  /*
   * Several recovered callers still reach the generic `sub_402E80` decoder,
   * but that path is polluted by x86-sized helper objects that are unsafe on
   * x86-64. The reached menu/frame/glyph sprites use the simple format-0
   * stream: literal runs, compressed back-references to prior literal runs,
   * and high-bit transparent skips. Decode that narrow shape directly into the
   * SDL-backed linear surface until the broader decoder scaffolding is safe.
   */
  width = *(unsigned __int16 *)(uintptr_t)sprite_for_char;
  height = *(unsigned __int16 *)(uintptr_t)(sprite_for_char + 2);
  format = *(unsigned __int16 *)(uintptr_t)(sprite_for_char + 4);
  if ( format != 0 || width <= 0 || height <= 0 )
    return 0;

  stream = (unsigned char *)(uintptr_t)(unsigned int)*(unsigned int *)(uintptr_t)(sprite_for_char + 10);
  if ( !stream )
    return 0;
  entry_size = *(int *)(uintptr_t)(sprite_for_char + 14);
  if ( entry_size <= 10 )
    return 0;
  stream_base = stream;
  stream_end = stream + (entry_size - 10);
  pitch = *(unsigned __int16 *)surface;
  surface_width = *(unsigned __int16 *)surface;
  surface_height = *((unsigned __int16 *)surface + 1);

  for ( row = 0; row < height; ++row )
  {
    int column;
    unsigned char *destination_row;

    if ( top + row < 0 || top + row >= surface_height )
      return 0;
    destination_row = surface_pixels + (top + row) * pitch;
    column = 0;
    while ( column < width )
    {
      unsigned char opcode;
      unsigned int run_length;

      if ( stream >= stream_end )
        return 0;
      opcode = *stream++;
      if ( (opcode & 0x80u) != 0 )
      {
        run_length = opcode & 0x7F;
        if ( run_length > (unsigned int)(width - column) )
          run_length = width - column;
        if ( !draw_mode )
        {
          unsigned int i;

          for ( i = 0; i < run_length; ++i )
          {
            int destination_x;

            destination_x = left + column + (int)i;
            if ( destination_x >= 0 && destination_x < surface_width )
              destination_row[destination_x] = (unsigned char)byte_51E265;
          }
        }
        column += run_length;
        continue;
      }

      if ( opcode )
      {
        unsigned int i;

        run_length = opcode;
        if ( run_length > (unsigned int)(width - column) )
          run_length = width - column;
        if ( stream + run_length > stream_end )
          return 0;
        for ( i = 0; i < run_length; ++i )
        {
          int destination_x;

          destination_x = left + column + (int)i;
          if ( destination_x >= 0 && destination_x < surface_width )
            destination_row[destination_x] = stream[i];
        }
        stream += run_length;
        column += run_length;
        continue;
      }

      {
        unsigned int back_offset;
        unsigned char *copy_source;
        unsigned int i;

        if ( stream + 4 > stream_end )
          return 0;
        back_offset = (unsigned int)stream[0]
                    | ((unsigned int)stream[1] << 8)
                    | ((unsigned int)stream[2] << 16)
                    | ((unsigned int)stream[3] << 24);
        if ( back_offset == 0 || back_offset > (unsigned int)(stream - stream_base) )
          return 0;
        copy_source = stream - back_offset;
        stream += 4;
        run_length = *copy_source++;
        if ( !run_length )
          return 0;
        if ( run_length > (unsigned int)(width - column) )
          run_length = width - column;
        if ( copy_source + run_length > stream_end )
          return 0;
        for ( i = 0; i < run_length; ++i )
        {
          int destination_x;

          destination_x = left + column + (int)i;
          if ( destination_x >= 0 && destination_x < surface_width )
            destination_row[destination_x] = copy_source[i];
        }
        column += run_length;
      }
    }
  }

  return 0;
}

//----- (00419410) --------------------------------------------------------
int  UI_DrawWidgetIconWithTransition(unsigned __int16 *a1, int a2, int a3, DWORD a4)
{
  int result; // eax
  unsigned char *widget; // edi
  int left; // ebx
  int top; // ebx
  int flags; // edx
  unsigned int sprite_set_holder; // esi
  unsigned int sprite_set; // esi
  int overlay_sprite_index; // esi
  __int16 SpriteHeight; // ax
  int v7; // ecx
  _DWORD *Surface; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  void *v11; // ebp
  int v12; // edi
  void *v13; // eax
  int SpriteForChar; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  unsigned int v19; // ebp
  int v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  int v25; // eax
  unsigned __int16 v26; // [esp+18h] [ebp-4Ch]
  void *v27; // [esp+1Ch] [ebp-48h]
  unsigned int v28; // [esp+20h] [ebp-44h]
  __int16 SpriteWidth; // [esp+24h] [ebp-40h]
  int v30; // [esp+28h] [ebp-3Ch]
  int v31; // [esp+2Ch] [ebp-38h]
  int v33; // [esp+3Ch] [ebp-28h]
  int v34; // [esp+40h] [ebp-24h]
  __int16 v35; // [esp+48h] [ebp-1Ch]
  unsigned __int16 v36; // [esp+4Ch] [ebp-18h]
  unsigned __int16 v37; // [esp+50h] [ebp-14h]

  widget = (unsigned char *)a1;
  v28 = a3;
  left = *(_DWORD *)(widget + 0);
  top = *(_DWORD *)(widget + 4);
  flags = widget[8];
  sprite_set_holder = *(_DWORD *)(widget + 12);
  if ( sprite_set_holder )
    sprite_set = *(_DWORD *)(uintptr_t)sprite_set_holder;
  else
    sprite_set = 0;
  overlay_sprite_index = *(_DWORD *)(widget + 24);
  if ( (a1[4] & 1) != 0 )
    result = *((_DWORD *)a1 + 4);
  else
    result = *((_DWORD *)a1 + 5);
  v30 = result;
  if ( !a2 )
  {
    if ( !sprite_set || v30 == -1 )
      return result;
    v25 = DLX_GetSpriteForChar(sprite_set, v30);
    result = Compat_RenderDeviceDrawMenuSprite(left, top, v25, 0);
    if ( (flags & 4) != 0 && overlay_sprite_index != -1 )
    {
      v24 = DLX_GetSpriteForChar(sprite_set, overlay_sprite_index);
      result = Compat_RenderDeviceDrawMenuSprite(left, top, v24, 1);
    }
    return result;
  }
  if ( result != -1 )
  {
    v33 = dword_544D10;
    if ( a2 && dword_544D10 )
    {
      v26 = a1[2] + DLX_GetSpriteWidth(sprite_set, result) - 1;
      SpriteHeight = DLX_GetSpriteHeight(sprite_set, v30);
      LOWORD(a3) = a1[2];
      RenderState_PumpIfRectInViewBounds(g_RenderState, *a1, *a1 + SpriteHeight - 1, a3, v26);
    }
    if ( a2 )
    {
      _DWORD *menu_surface;

      menu_surface = RenderSurface_ResolvePrimaryCompanion((_DWORD *)g_RenderDevice);
      if ( menu_surface && RenderSurface_IsLinearSoftware(menu_surface) )
      {
        v25 = DLX_GetSpriteForChar(sprite_set, v30);
        result = Compat_RenderDeviceDrawMenuSprite(left, top, v25, 0);
        if ( (a1[4] & 4) != 0 && *((_DWORD *)a1 + 6) != -1 )
        {
          v24 = DLX_GetSpriteForChar(sprite_set, *((_DWORD *)a1 + 6));
          result = Compat_RenderDeviceDrawMenuSprite(left, top, v24, 1);
        }
        if ( v33 )
          return Render_Present((int)g_RenderState);
        return result;
      }
    }
    if ( a2 )
    {
      v35 = DLX_GetSpriteHeight(sprite_set, v30);
      SpriteWidth = DLX_GetSpriteWidth(sprite_set, v30);
      Surface = (_DWORD *)Mem_Alloc(188, v7, a3, a4);
      if ( Surface )
      {
        LOBYTE(a3) = SpriteWidth;
        Surface = Render_CreateSurface((int)Surface, v35, SpriteWidth);
      }
      v34 = (int)Surface;
      v10 = (_DWORD *)Mem_Alloc(188, v9, a3, a4);
      if ( v10 )
        v10 = Render_CreateSurface((int)v10, v35, SpriteWidth);
      v11 = v10;
      v12 = (int)v10;
      Render_FillRect(g_RenderDevice, (_DWORD *)v34, a1[2], *a1, v35 + *a1 - 1, SpriteWidth + a1[2] - 1, 0, 0);
      v13 = g_RenderDevice;
      g_RenderDevice = v11;
      v27 = v13;
      SpriteForChar = DLX_GetSpriteForChar(sprite_set, v30);
      Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 0);
      g_RenderDevice = v27;
      v17 = Time_Now(v16, v15);
      v19 = v17 + v28;
      v31 = v17;
      v20 = v28;
      v37 = v35 - 1;
      v36 = SpriteWidth - 1;
      while ( Time_Now(v18, v20) < v19 )
      {
        v22 = Time_Now(v21, v31);
        Render_BlendSurfaceRect(0, v34, 0, v12, 0, v37, v36, *a1, a1[2], 255 * (v22 - v23) / v28);
        if ( dword_526A30 )
          dword_526A30();
      }
      result = Render_FillRect((_DWORD *)v12, 0, 0, 0, v37, v36, *a1, a1[2]);
      if ( g_RenderDevice != &unk_51D4C0 )
        result = Render_FillRect((_DWORD *)v12, g_RenderDevice, 0, 0, v37, v36, *a1, a1[2]);
      if ( v34 )
        result = RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)v34, 2);
      if ( v12 )
        result = RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)v12, 2);
    }
    else
    {
      v25 = DLX_GetSpriteForChar(sprite_set, v30);
      result = Compat_RenderDeviceDrawMenuSprite(left, top, v25, 0);
    }
    if ( (a1[4] & 4) != 0 && *((_DWORD *)a1 + 6) != -1 )
    {
      v24 = DLX_GetSpriteForChar(sprite_set, *((_DWORD *)a1 + 6));
      result = Compat_RenderDeviceDrawMenuSprite(left, top, v24, 1);
    }
    if ( a2 && v33 )
      return Render_Present((int)g_RenderState);
  }
  return result;
}
// 4194DD: variable 'v7' is possibly undefined
// 419502: variable 'v9' is possibly undefined
// 4195B5: variable 'v16' is possibly undefined
// 4195B5: variable 'v15' is possibly undefined
// 4195DA: variable 'v18' is possibly undefined
// 4195DA: variable 'v20' is possibly undefined
// 4195E7: variable 'v21' is possibly undefined
// 4195EC: variable 'v23' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 526A30: using guessed type int (*dword_526A30)(void);
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00419770) --------------------------------------------------------
int  UI_DrawWidgetIconTransitionSlow(unsigned __int16 *a1, int a2, DWORD a3)
{
  return UI_DrawWidgetIconWithTransition(a1, a2, 20, a3);
}

//----- (00419780) --------------------------------------------------------
int  UI_DrawWidgetIconTransitionFast(unsigned __int16 *a1, int a2, DWORD a3)
{
  return UI_DrawWidgetIconWithTransition(a1, a2, 10, a3);
}

static int UI_InvokeWidgetTransitionCallback(uintptr_t widget, int callback_arg)
{
  unsigned int callback;

  callback = *(_DWORD *)(widget + 28);
  if ( !callback )
    return 0;
  return ((int (__cdecl *)(uintptr_t, int, DWORD))(uintptr_t)callback)(widget, callback_arg, 0);
}

static int UI_InvokeWidgetActionCallback(uintptr_t widget)
{
  unsigned int callback;

  callback = *(_DWORD *)(widget + 32);
  if ( !callback )
    return 0;
  return ((int (__cdecl *)(uintptr_t, int, DWORD, char, double))(uintptr_t)callback)(widget, 0, 0, 0, 0.0);
}

static unsigned int Compat_WidgetPackedField(uintptr_t widget, unsigned int field_offset)
{
  return (unsigned int)*(_DWORD *)(widget + field_offset);
}

static unsigned int Compat_WidgetSpriteSetHandle(uintptr_t widget)
{
  unsigned int sprite_set_holder;

  sprite_set_holder = Compat_WidgetPackedField(widget, 12);
  if ( !sprite_set_holder )
    return 0;
  return (unsigned int)*(_DWORD *)(uintptr_t)sprite_set_holder;
}

static const char *Compat_WidgetPackedString(uintptr_t widget, unsigned int field_offset)
{
  return (const char *)(uintptr_t)Compat_WidgetPackedField(widget, field_offset);
}

//----- (00419790) --------------------------------------------------------
int  UI_SetActiveWidgetTable(int result)
{
  dword_526A2C = result;
  return result;
}
// 526A2C: using guessed type int dword_526A2C;

//----- (004197A0) --------------------------------------------------------
BOOL  UIWidget_ShowTextWithFadeTransition(uintptr_t a1, DWORD a2)
{
  int v2; // ebx
  int TextXOffset; // eax
  int v4; // edx
  int v5; // edx
  int v6; // ecx
  int v7; // ebx
  int v8; // edx
  _DWORD *Surface; // eax
  int v10; // ecx
  int v11; // esi
  _DWORD *v12; // eax
  _DWORD *v13; // ebp
  int v14; // edi
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  DWORD v24; // ebp
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // eax
  int v29; // edx
  int v31; // [esp+0h] [ebp-64h]
  int v32; // [esp+4h] [ebp-60h]
  int v33; // [esp+8h] [ebp-5Ch]
  int v34; // [esp+Ch] [ebp-58h]
  void *v35; // [esp+24h] [ebp-40h]
  DWORD v37; // [esp+2Ch] [ebp-38h]
  int v38; // [esp+30h] [ebp-34h]
  int v39; // [esp+34h] [ebp-30h]
  unsigned __int16 v40; // [esp+3Ch] [ebp-28h]
  unsigned __int16 v41; // [esp+40h] [ebp-24h]
  unsigned __int16 v42; // [esp+44h] [ebp-20h]
  unsigned __int16 v43; // [esp+48h] [ebp-1Ch]

  v31 = dword_520728;
  Render_ReleaseSurface(dword_526A2C, a2);
  v35 = g_RenderDevice;
  v38 = dword_544D00 >> byte_54512C;
  v2 = dword_544CFC >> byte_54512C;
  v32 = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)(a1 + 4 * (unsigned __int8)g_LanguageIndex + 36))
      + (dword_544CFC >> byte_54512C);
  TextXOffset = UI_GetTextXOffset(dword_520728);
  v5 = TextXOffset + v4;
  v37 = v2;
  v6 = v32;
  v39 = v5;
  if ( v2 + *(_DWORD *)(dword_544D14 + 12) > v32 )
    v32 = v2 + *(_DWORD *)(dword_544D14 + 12);
  v7 = *(_DWORD *)(dword_544D14 + 16);
  if ( v38 + v7 > v5 )
    v39 = v38 + v7;
  if ( v32 > 639 )
  {
    a2 = v37 - (v32 - 639);
    v37 = a2;
    LOWORD(v32) = 639;
  }
  v8 = v39;
  if ( v39 > 479 )
  {
    LOBYTE(v7) = -33;
    v6 = v38 - (v39 - 479);
    LOWORD(v39) = 479;
    v38 -= v8 - 479;
  }
  Surface = (_DWORD *)Mem_Alloc(188, v6, v7, a2);
  if ( Surface )
  {
    LOWORD(v7) = v39 - v38 + 1;
    Surface = Render_CreateSurface((int)Surface, v32 - v37 + 1, v7);
  }
  v11 = (int)Surface;
  v12 = (_DWORD *)Mem_Alloc(188, v10, v7, a2);
  if ( v12 )
    v12 = Render_CreateSurface((int)v12, v32 - v37 + 1, v39 - v38 + 1);
  v13 = v12;
  Render_FillRect(0, (_DWORD *)v11, (unsigned __int16)v38, (unsigned __int16)v37, v32, v39, 0, 0);
  Render_SaveBackbuffer((int)&unk_51D4C0);
  Render_Pump();
  Render_FillRect(0, v13, (unsigned __int16)v38, (unsigned __int16)v37, v32, v39, 0, 0);
  v14 = (int)v13;
  Render_Present((int)&g_RenderState);
  g_RenderDevice = v13;
  UI_DrawText(0, 0, *(_DWORD *)(a1 + 4 * (unsigned __int8)g_LanguageIndex + 36));
  v34 = Time_Now(v16, v15);
  v18 = 30;
  v43 = v32 - v37;
  v40 = v39 - v38;
  while ( Time_Now(v17, v18) < (unsigned int)(v34 + 30) )
  {
    v20 = Time_Now(v34, v19);
    Render_BlendSurfaceRect(0, v11, 0, (int)v13, 0, v43, v40, v37, v38, 255 * (v20 - v21) / 0x1Eu);
  }
  Render_FillRect(v13, 0, 0, 0, v43, v40, v37, v38);
  Render_FlipRect((int)&g_RenderState, 0);
  v33 = Time_Now(v23, v22);
  v24 = v33 + 30;
  v25 = v37;
  v26 = v38;
  v42 = v32 - v37;
  v41 = v39 - v38;
  while ( Time_Now(v25, v26) < v24 )
  {
    v28 = Time_Now(v27, v33);
    Render_BlendSurfaceRect(0, v14, 0, v11, 0, v42, v41, v37, v38, 255 * (v28 - v29) / 0x1Eu);
  }
  Render_FillRect((_DWORD *)v11, 0, 0, 0, v42, v41, v37, v38);
  if ( v11 )
    (**(void (__cdecl ***)(int))(v11 + 184))(v31);
  if ( v14 )
    (**(void (***)(void))(v14 + 184))();
  Render_ReleaseSurface(v31, v24);
  g_RenderDevice = v35;
  return Render_Begin((int)&g_RenderState, 0);
}
// 419827: variable 'v4' is possibly undefined
// 4198E5: variable 'v10' is possibly undefined
// 4199BE: variable 'v16' is possibly undefined
// 4199BE: variable 'v15' is possibly undefined
// 4199EC: variable 'v17' is possibly undefined
// 4199EC: variable 'v18' is possibly undefined
// 4199F9: variable 'v19' is possibly undefined
// 4199FE: variable 'v21' is possibly undefined
// 419A80: variable 'v23' is possibly undefined
// 419A80: variable 'v22' is possibly undefined
// 419AB0: variable 'v25' is possibly undefined
// 419AB0: variable 'v26' is possibly undefined
// 419ABD: variable 'v27' is possibly undefined
// 419AC2: variable 'v29' is possibly undefined
// 419B4B: variable 'v31' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520728: using guessed type int dword_520728;
// 526A2C: using guessed type int dword_526A2C;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00419B80) --------------------------------------------------------
signed int  UIWidget_PollHitHoverAndClick(uintptr_t a1, DWORD a2)
{
  int v3; // esi
  int v4; // eax
  int v5; // eax
  int sprite_set_handle;
  uintptr_t v7; // eax
  uintptr_t v8; // eax
  int v9; // ecx
  int queen_widget_index;
  int queen_widget_sprite;
  int queen_widget_width;
  int queen_widget_height;
  int queen_cursor_x;
  int queen_cursor_y;
  char v10; // [esp+0h] [ebp-18h]

  v3 = 0;
  sprite_set_handle = Compat_WidgetSpriteSetHandle(a1);
  if ( g_QueenMarriageProposalWidgetTableBase
    && a1 >= g_QueenMarriageProposalWidgetTableBase
    && a1 < g_QueenMarriageProposalWidgetTableBase + 2 * 53
    && (DD_IsFlipping((int)g_RenderState) || DD_IsLost((int)g_RenderState)) )
  {
    queen_cursor_x = dword_544CFC >> byte_54512C;
    queen_cursor_y = dword_544D00 >> byte_54512C;
    queen_widget_index = (int)((a1 - g_QueenMarriageProposalWidgetTableBase) / 53);
    queen_widget_sprite = *(_DWORD *)(a1 + 20) == -1 ? *(_DWORD *)(a1 + 16) : *(_DWORD *)(a1 + 20);
    queen_widget_width = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteWidth(sprite_set_handle, queen_widget_sprite) : 0;
    queen_widget_height = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, queen_widget_sprite) : 0;
    if ( getenv("CLASH95_TRACE_QUEEN_WIDGET_VERBOSE")
      || (queen_cursor_x >= *(_DWORD *)a1
       && queen_cursor_y >= *(_DWORD *)(a1 + 4)
       && queen_cursor_x < *(_DWORD *)a1 + queen_widget_height
       && queen_cursor_y < *(_DWORD *)(a1 + 4) + queen_widget_width) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "queen_widget_probe",
        queen_widget_index,
        *(_DWORD *)a1,
        *(_DWORD *)(a1 + 4),
        *(_DWORD *)(a1 + 8));
      Diagnostics_TraceWorldMapActionEvent(
        "queen_widget_bounds",
        queen_widget_index,
        queen_widget_height,
        queen_widget_width,
        *(_DWORD *)(a1 + 32));
    }
  }
  if ( a1 >= (uintptr_t)BuildingGarrisonDialogActions
    && a1 < (uintptr_t)(BuildingGarrisonDialogActions
                      + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_GARRISON_DIALOG_WIDGET_COUNT)
    && (DD_IsFlipping((int)g_RenderState) || DD_IsLost((int)g_RenderState) || getenv("CLASH95_TRACE_GARRISON_WIDGET_VERBOSE")) )
  {
    int garrison_cursor_x = dword_544CFC >> byte_54512C;
    int garrison_cursor_y = dword_544D00 >> byte_54512C;
    int garrison_widget_index = (int)((a1 - (uintptr_t)BuildingGarrisonDialogActions) / WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
    int garrison_widget_sprite = *(_DWORD *)(a1 + 20) == -1 ? *(_DWORD *)(a1 + 16) : *(_DWORD *)(a1 + 20);
    int garrison_widget_width = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteWidth(sprite_set_handle, garrison_widget_sprite) : 0;
    int garrison_widget_height = sprite_set_handle ? (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, garrison_widget_sprite) : 0;
    int garrison_widget_inside = garrison_cursor_x >= *(_DWORD *)a1
                              && garrison_cursor_y >= *(_DWORD *)(a1 + 4)
                              && garrison_cursor_x < *(_DWORD *)a1 + garrison_widget_height
                              && garrison_cursor_y < *(_DWORD *)(a1 + 4) + garrison_widget_width;

    if ( getenv("CLASH95_TRACE_GARRISON_WIDGET_VERBOSE") || garrison_widget_inside )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "garrison_widget_probe",
        garrison_widget_index,
        *(_DWORD *)a1,
        *(_DWORD *)(a1 + 4),
        *(_DWORD *)(a1 + 8));
      Diagnostics_TraceWorldMapActionEvent(
        "garrison_widget_bounds",
        garrison_widget_index,
        garrison_widget_height,
        garrison_widget_width,
        garrison_widget_inside);
    }
  }
  if ( dword_544CFC >> byte_54512C < *(_DWORD *)a1 || dword_544D00 >> byte_54512C < *(_DWORD *)(a1 + 4) )
    goto LABEL_29;
  v4 = *(_DWORD *)(a1 + 20) == -1 ? *(_DWORD *)(a1 + 16) : *(_DWORD *)(a1 + 20);
  if ( dword_544CFC >> byte_54512C >= *(_DWORD *)a1
                                    + (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, v4)
                                    - 1 )
    goto LABEL_29;
  v5 = *(_DWORD *)(a1 + 20);
  if ( v5 == -1 )
    v5 = *(_DWORD *)(a1 + 16);
  if ( dword_544D00 >> byte_54512C >= *(_DWORD *)(a1 + 4)
                                    + (unsigned __int16)DLX_GetSpriteWidth(sprite_set_handle, v5)
                                    - 1 )
  {
LABEL_29:
    if ( (*(_BYTE *)(a1 + 8) & 4) == 0 )
      goto LABEL_34;
    v8 = a1 + 4 * (unsigned __int8)g_LanguageIndex;
    v9 = *(_DWORD *)(v8 + 36);
    if ( v9 && *(_BYTE *)(a1 + 48) == 1 )
      Tooltip_RestoreIfTextMatches(v9, v9);
    v3 = 1;
    *(_BYTE *)(a1 + 8) &= ~4u;
LABEL_23:
    if ( *(_DWORD *)(a1 + 24) == -1 )
      return v3;
    UI_InvokeWidgetTransitionCallback(a1, 1);
    return v3;
  }
  if ( (uintptr_t)a1 >= (uintptr_t)g_WorldMapActionButtonWidgetTable
    && (uintptr_t)a1 < (uintptr_t)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * WORLD_MAP_ACTION_WIDGET_COUNT)
    && (DD_IsFlipping((int)g_RenderState) || DD_IsLost((int)g_RenderState)) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "action_widget_hit",
      (int)(((uintptr_t)a1 - (uintptr_t)g_WorldMapActionButtonWidgetTable) / WORLD_MAP_ACTION_WIDGET_RECORD_SIZE),
      *(_DWORD *)a1,
      *(_DWORD *)(a1 + 4),
      *(_DWORD *)(a1 + 8));
  }
  if ( DD_IsLost((int)g_RenderState) && *(_BYTE *)(a1 + 48) == 2 )
    UIWidget_ShowTextWithFadeTransition(a1, a2);
  if ( DD_IsFlipping((int)g_RenderState) && *(_DWORD *)(a1 + 32) )
  {
    if ( a1 >= (uintptr_t)BuildingGarrisonDialogActions
      && a1 < (uintptr_t)(BuildingGarrisonDialogActions
                        + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_GARRISON_DIALOG_WIDGET_COUNT) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "garrison_widget_action",
        (int)((a1 - (uintptr_t)BuildingGarrisonDialogActions) / WORLD_MAP_ACTION_WIDGET_RECORD_SIZE),
        *(_DWORD *)a1,
        *(_DWORD *)(a1 + 4),
        *(_DWORD *)(a1 + 32));
    }
    if ( g_QueenMarriageProposalWidgetTableBase
      && a1 >= g_QueenMarriageProposalWidgetTableBase
      && a1 < g_QueenMarriageProposalWidgetTableBase + 2 * 53 )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "queen_widget_action",
        (int)((a1 - g_QueenMarriageProposalWidgetTableBase) / 53),
        *(_DWORD *)a1,
        *(_DWORD *)(a1 + 4),
        *(_DWORD *)(a1 + 32));
    }
    UI_InvokeWidgetActionCallback(a1);
    if ( (*(_BYTE *)(a1 + 8) & 1) != 0 )
      v3 = 3;
    if ( (*(_BYTE *)(a1 + 8) & 2) != 0 )
    {
      v3 = 4;
LABEL_18:
      UI_InvokeWidgetTransitionCallback(a1, 1);
      return v3;
    }
    goto LABEL_34;
  }
  if ( (*(_BYTE *)(a1 + 8) & 4) == 0 )
  {
    v7 = a1 + 4 * (unsigned __int8)g_LanguageIndex;
    if ( *(_DWORD *)(v7 + 36) && *(_BYTE *)(a1 + 48) == 1 )
      Tooltip_ShowText(3, (char *)Compat_WidgetPackedString(a1, 36 + 4 * (unsigned __int8)g_LanguageIndex), v10);
    v3 = 2;
    *(_BYTE *)(a1 + 8) |= 4u;
    goto LABEL_23;
  }
LABEL_34:
  if ( v3 == 3 )
    goto LABEL_18;
  return v3;
}
// 419CA2: conditional instruction was optimized away because esi.4 is in (==0|==3)
// 419D3F: conditional instruction was optimized away because esi.4 is in (==0|==3)
// 419D48: conditional instruction was optimized away because esi.4 is in (==0|==3)
// 419CE5: variable 'v10' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00419D60) --------------------------------------------------------
int  UIWidget_RefreshActionButtonState(uintptr_t result, int a2)
{
  if ( result == (uintptr_t)g_WorldMapActionButtonWidgetTable
    || result == (uintptr_t)(g_WorldMapActionButtonWidgetTable + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 3) )
  {
    WorldMap_EnsureActionButtonWidgetTable();
  }
  if ( UnitBattle_IsActionButtonWidgetAddress(result) )
    UnitBattle_EnsureActionButtonWidgetTable();
  if ( *(int *)result < 640 )
    return UI_InvokeWidgetTransitionCallback(result, a2);
  return (int)result;
}

//----- (00419D80) --------------------------------------------------------
_DWORD * UIWidgetTable_InitDrawStates(_DWORD *result)
{
  unsigned char *widget;

  if ( (uintptr_t)result == (uintptr_t)g_WorldMapActionButtonWidgetTable )
    WorldMap_EnsureActionButtonWidgetTable();
  if ( (uintptr_t)result == (uintptr_t)g_UnitBattleActionWidgetTable )
    UnitBattle_EnsureActionButtonWidgetTable();
  widget = (unsigned char *)result;
  if ( *(_DWORD *)widget == -1 )
    return result;
  do
  {
    while ( *(int *)widget >= 640 )
    {
      widget += 53;
      if ( *(_DWORD *)widget == -1 )
        return result;
    }
    UI_InvokeWidgetTransitionCallback((uintptr_t)widget, 0);
    widget += 53;
  }
  while ( *(_DWORD *)widget != -1 );
  return result;
}

//----- (00419DC0) --------------------------------------------------------
signed int  UIWidgetTable_PollHoverAndActions(_DWORD *a1, DWORD a2)
{
  uintptr_t widget; // edx
  int has_tooltip; // ebx
  signed int result; // ecx
  signed int widget_result; // eax

  if ( (uintptr_t)a1 == (uintptr_t)g_WorldMapActionButtonWidgetTable )
    WorldMap_EnsureActionButtonWidgetTable();
  if ( (uintptr_t)a1 == (uintptr_t)g_UnitBattleActionWidgetTable )
    UnitBattle_EnsureActionButtonWidgetTable();
  widget = (uintptr_t)a1;
  has_tooltip = 0;
  result = 0;
  if ( *a1 != -1 )
  {
    do
    {
      widget_result = UIWidget_PollHitHoverAndClick(widget, a2);
      if ( widget_result > result )
        result = widget_result;
      if ( (*(_BYTE *)(widget + 8) & 4) != 0 )
        has_tooltip = 1;
      widget += 53;
    }
    while ( *(_DWORD *)widget != -1 );
  }
  if ( !dword_526A24 && has_tooltip )
  {
    dword_526A34 = dword_544D14;
    RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
    dword_526A24 = 1;
    return result;
  }
  if ( !dword_526A24 || has_tooltip )
    return result;
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_526A34);
  dword_526A24 = 0;
  return result;
}
// 419DDB: variable 'v4' is possibly undefined
// 419DDF: variable 'v6' is possibly undefined
// 419E53: variable 'v9' is possibly undefined
// 526A24: using guessed type int dword_526A24;
// 526A34: using guessed type int dword_526A34;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D14: using guessed type int dword_544D14;
// 545150: using guessed type int dword_545150;

//----- (00419E60) --------------------------------------------------------
int  UIWidget_PlayPressedReleaseAnimationWithDelay(uintptr_t a1, int a2)
{
  unsigned int deadline; // ecx

  (void)a2;
  if ( *(_DWORD *)(a1 + 49) )
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(a1, 49));
  *(_DWORD *)(a1 + 8) = 6;
  UIWidget_RefreshActionButtonState(a1, 1);
  deadline = Time_Now(0, 0) + 20;
  while ( Time_Now(0, 0) < deadline )
    DD_Pump((int)g_RenderState, 0);
  Render_Begin((int)g_RenderState, 0);
  *(_DWORD *)(a1 + 8) = 5;
  return UIWidget_RefreshActionButtonState(a1, 1);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00419ED0) --------------------------------------------------------
int  UIWidget_PlayPressedReleaseAnimation(uintptr_t a1)
{
  if ( *(_DWORD *)(a1 + 49) )
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(a1, 49));
  *(_DWORD *)(a1 + 8) = 6;
  UIWidget_RefreshActionButtonState(a1, 1);
  Render_Begin((int)g_RenderState, 0);
  *(_DWORD *)(a1 + 8) = 5;
  return UIWidget_RefreshActionButtonState(a1, 1);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00419F20) --------------------------------------------------------
int  UIWidget_ShowPressedState(uintptr_t a1)
{
  if ( *(_DWORD *)(a1 + 49) )
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(a1, 49));
  *(_DWORD *)(a1 + 8) = 6;
  return UIWidget_RefreshActionButtonState(a1, 1);
}

//----- (00419F50) --------------------------------------------------------
int  UIWidget_ShowReleasedState(uintptr_t a1, int a2)
{
  (void)a2;
  *(_DWORD *)(a1 + 8) = 5;
  return UIWidget_RefreshActionButtonState(a1, 1);
}

//----- (00419F70) --------------------------------------------------------
int  UI_DrawUnitInfoPane(
        int a1,
        int a2,
        int a3,
        __int16 *a4,
        DWORD a5,
        int a6)
{
  int v6; // edi
  _DWORD *v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int SpriteForChar; // eax
  DWORD v13; // ebp
  int v14; // ecx
  _DWORD *Surface; // esi
  __int16 v16; // bx
  __int16 SpriteHeight; // ax
  int v18; // eax
  __int16 v19; // ax
  int v20; // esi
  int v21; // edx
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // eax
  unsigned __int8 v26; // al
  int v27; // edx
  int v28; // eax
  int v29; // esi
  int v30; // eax
  int v31; // ecx
  int v32; // eax
  int v33; // eax
  int v34; // eax
  unsigned __int16 v35; // cx
  unsigned __int16 v36; // si
  int v37; // ebx
  int v38; // ecx
  int v39; // eax
  unsigned __int16 v41; // [esp+64h] [ebp-40h]
  _DWORD *v42; // [esp+70h] [ebp-34h] BYREF
  int v43; // [esp+74h] [ebp-30h]
  int v44; // [esp+78h] [ebp-2Ch]
  int v45; // [esp+7Ch] [ebp-28h]
  DWORD v46; // [esp+80h] [ebp-24h]
  void *v47; // [esp+84h] [ebp-20h]
  int v48; // [esp+88h] [ebp-1Ch]
  char *(**v49)[102]; // [esp+8Ch] [ebp-18h]
  int v50; // [esp+90h] [ebp-14h]
  __int16 *v51; // [esp+94h] [ebp-10h]

  v6 = a6;
  v50 = a1;
  v44 = a2;
  v51 = a4;
  v49 = &g_UnitTypeMetadataRecords + 22 * *a4;
  v7 = (_DWORD *)Mem_Alloc(4112, a3, (char)a4, a5);
  if ( v7 )
    v7 = DLXSpriteSet_Load(v7, (char)a4);
  v42 = v7;
  Render_ReleaseSurface(7, a5);
  if ( *(unsigned __int8 *)(v9 + 2) == g_CurrentPlayerIndex )
  {
    if ( v8 )
      DLXSpriteSet_DrawText((int)v42, 0, v8, (unsigned __int8 *)dword_5202F4);
    v10 = (int)v42;
    v11 = 0;
  }
  else
  {
    if ( v8 )
      DLXSpriteSet_DrawText((int)v42, 1, v8, (unsigned __int8 *)dword_5202F4);
    v11 = 1;
    v10 = (int)v42;
  }
  SpriteForChar = DLX_GetSpriteForChar(v10, v11);
  v13 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(v13 + 52))(
    v44,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    0);
  if ( *((char *)v51 + 9) < 100 )
  {
    v47 = g_RenderDevice;
    Surface = (_DWORD *)Mem_Alloc(188, v14, v50, v13);
    if ( Surface )
    {
      v16 = DLX_GetSpriteWidth((int)v42, 2u) + 1;
      SpriteHeight = DLX_GetSpriteHeight((int)v42, 2u);
      Surface = Render_CreateSurface((int)Surface, SpriteHeight + 1, v16);
    }
    g_RenderDevice = Surface;
    v18 = DLX_GetSpriteForChar((int)v42, 2);
    v13 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(v13 + 52))(
      0,
      v18,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    g_RenderDevice = v47;
    v41 = 106 * (100 - *((char *)v51 + 9)) / 100 + 5;
    v19 = DLX_GetSpriteHeight((int)v42, 2u);
    Render_FillRect(Surface, g_RenderDevice, 5, 0, v19 - 1, v41, v50 + 42, v44 + 5);
    if ( Surface )
      (*(void (**)(void))Surface[46])();
  }
  UI_DrawTextFmt(a6, v50 + 64, v50 + 192, v44 + 5, 3, (int)(**v49)[(unsigned __int8)g_LanguageIndex]);
  if ( *((unsigned __int8 *)v51 + 2) == g_CurrentPlayerIndex )
  {
    v48 = v44 + 95;
    v43 = v50 + 85;
    v20 = v50 + 105;
    if ( *((_BYTE *)v49 + 25) )
    {
      if ( *((_BYTE *)v49 + 22) )
      {
        UI_IconIndexFromStats(v51);
        UI_DrawTextFmt(a6, v43, v20, v44 + 74, 2, (int)aD_12);
        Unit_GetBaseC(v51);
        v13 = v48;
        UI_DrawTextFmt(a6, v43, v20, v48, 2, (int)aD_13);
      }
      else
      {
        DLX_GetSpriteForChar((int)v42, 10);
        v46 = *((_DWORD *)g_RenderDevice + 46);
        v13 = v46;
        (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(v46 + 52))(-1, -1, -1, -1, 1, 0, 0);
        Unit_GetBaseC(v51);
        UI_DrawTextFmt(a6, v43, v20, v48, 2, (int)aD_2);
      }
    }
    else
    {
      DLX_GetSpriteForChar((int)v42, 9);
      (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      UI_IconIndexFromStats(v51);
      v13 = v48;
      UI_DrawTextFmt(a6, v43, v20, v48, 2, (int)aD_1);
    }
    UI_DrawTextFmt(a6, v50 + 85, v50 + 105, v44 + 50, 2, (int)aD_14);
    if ( (unsigned int)*(char *)(v21 + 11) > 4 )
    {
      v32 = *((char *)v51 + 11);
      if ( v32 < 11 || v32 > 15 )
      {
        v33 = *((char *)v51 + 11);
        if ( v33 < 16 || v33 > 20 )
          goto LABEL_19;
        v22 = 3;
      }
      else
      {
        v22 = 4;
      }
    }
    else
    {
      v22 = 5;
    }
    v23 = DLX_GetSpriteForChar((int)v42, v22);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      v44 + 21,
      v23,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
LABEL_19:
    if ( *((char *)v51 + 11) >= 1 )
      v24 = 7;
    else
      v24 = 13;
    Render_ReleaseSurface(v24, v13);
    UI_DrawTextFmt(a6, v50 + 132, v50 + 148, v44 + 50, 2, (int)aD_15);
    if ( *((char *)v51 + 10) <= 90 )
      v25 = 7;
    else
      v25 = 13;
    Render_ReleaseSurface(v25, v13);
    UI_DrawTextFmt(a6, v50 + 160, v50 + 191, v44 + 50, 2, (int)aD_16);
    Render_ReleaseSurface(7, v13);
    Unit_CalcIndexB(v51);
    UI_DrawTextFmt(a6, v50 + 132, v50 + 148, v44 + 95, 2, (int)aD_17);
    v26 = v51[6] & 3;
    if ( v26 )
    {
      if ( v26 <= 1u )
      {
        v27 = 7;
      }
      else
      {
        if ( v26 != 3 )
        {
LABEL_26:
          v6 = 0;
          v29 = v44 + 71;
          v45 = v50 + 178;
          while ( v6 <= (unsigned __int8)(16 * *((_BYTE *)v51 + 12)) >> 6 )
          {
            v30 = DLX_GetSpriteForChar((int)v42, 14);
            v31 = v29;
            v13 = *((_DWORD *)g_RenderDevice + 46);
            ++v6;
            v29 += 10;
            (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v13 + 52))(
              v31,
              v30,
              -1,
              -1,
              -1,
              -1,
              1,
              0,
              0);
          }
          goto LABEL_47;
        }
        v27 = 8;
      }
    }
    else
    {
      v27 = 6;
    }
    v28 = DLX_GetSpriteForChar((int)v42, v27);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      v44 + 65,
      v28,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    goto LABEL_26;
  }
LABEL_47:
  v34 = *v51;
  if ( v34 == UNIT_TYPE_FORESTER )
  {
    v35 = 11;
  }
  else if ( v34 == UNIT_TYPE_GORAL )
  {
    v35 = 12;
  }
  else
  {
    if ( (*((_BYTE *)v49 + 18) & 1) == 0 )
      goto LABEL_50;
    v35 = 13;
  }
  v36 = v35;
  v37 = (33 - (unsigned __int16)DLX_GetSpriteWidth((int)v42, v35)) / 2 + 76 + v44;
  v6 = (34 - (unsigned __int16)DLX_GetSpriteHeight((int)v42, v36)) / 2 + 8 + v50;
  v39 = DLX_GetSpriteForChar((int)v42, v38);
  v13 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v13 + 52))(
    v37,
    v39,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
LABEL_50:
  Render_ReleaseSurface(7, v13);
  UI_DrawTextFmt(v6, v50 + 41, v50 + 70, v44 + 98, 3, (int)aD_18);
  Render_ReleaseSurface(7, v13);
  return DLXSpriteSet_ReleaseAndClear((int *)&v42);
}
// 41A23D: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 419FBC: variable 'v9' is possibly undefined
// 419FCD: variable 'v8' is possibly undefined
// 41A031: variable 'v14' is possibly undefined
// 41A234: variable 'v21' is possibly undefined
// 41A5E6: variable 'v38' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;

//----- (0041A690) --------------------------------------------------------
int  Unit_Info(
        int a1,
        int a2,
        int a3,
        unsigned __int8 *a4,
        DWORD a5,
        DWORD a6)
{
  int v8; // ecx
  int v9; // eax
  char v10; // bl
  int v11; // ecx
  _DWORD *v12; // eax
  int v13; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int v16; // ebp
  int v17; // esi
  int v18; // ecx
  int v19; // ecx
  unsigned int v20; // eax
  unsigned int v21; // edx
  int v22; // ecx
  int v23; // eax
  int v25; // ecx
  char v26[100]; // [esp+0h] [ebp-8Ch] BYREF
  _DWORD *v27; // [esp+64h] [ebp-28h] BYREF
  int v28; // [esp+68h] [ebp-24h]
  int v29; // [esp+6Ch] [ebp-20h]
  _DWORD *v30; // [esp+70h] [ebp-1Ch]
  int v31; // [esp+74h] [ebp-18h]
  int v32; // [esp+78h] [ebp-14h]
  int v33; // [esp+7Ch] [ebp-10h]

  v31 = a1;
  v28 = a2;
  Debug_Log(a2, (char)a4, a5, (int)aUnit_infoDD0x0);
  v9 = *(__int16 *)a4;
  if ( v9 == UNIT_TYPE_PEASANT_CARGO
    || v9 == UNIT_TYPE_GOLD_CARGO
    || v9 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
    || v9 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    return UI_DrawSpecialUnitInfoPane(v31, v28, v8, a4, a5, a3);
  v10 = a4[2];
  UI_BeginUnitInfo(v26, *a4, v10);
  v12 = (_DWORD *)Mem_Alloc(4112, v11, v10, a5);
  if ( v12 )
    v12 = DLXSpriteSet_Load(v12, v10);
  v27 = v12;
  if ( a6 )
  {
    v10 = dword_5202F4;
    DLXSpriteSet_DrawText((int)v12, 0, a6, (unsigned __int8 *)dword_5202F4);
  }
  Render_Pump();
  Surface = (_DWORD *)Mem_Alloc(188, v13, v10, a6);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 201, 116);
  v30 = Surface;
  Render_FillRect(0, Surface, (unsigned __int16)v28, (unsigned __int16)v31, v31 + 200, v28 + 115, 0, 0);
  g_RenderDevice = &unk_51D4C0;
  UI_DrawUnitInfoPane(v31, v28, a6, (__int16 *)a4, a6, a3);
  SpriteForChar = DLX_GetSpriteForChar((int)v27, 0);
  v16 = v28 + 5;
  v29 = *((_DWORD *)g_RenderDevice + 46);
  v32 = v31 + 11;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v29 + 52))(
    v28 + 5,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v17 = 0;
  g_RenderDevice = &unk_51D4C0;
  v33 = Time_Now(v18, (int)&unk_51D4C0);
  while ( DD_IsLost((int)g_RenderState) || DD_IsFlipping((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, a6);
    if ( !a6 )
    {
      v20 = Time_Now(v19, v33 + 10);
      if ( v21 < v20 )
      {
        v33 = Time_Now(v22, v21);
        v17 = (v17 + 1) % 8;
        v23 = DLX_GetSpriteForChar((int)v27, v17);
        v29 = *((_DWORD *)g_RenderDevice + 46);
        (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v29 + 52))(
          v16,
          v23,
          -1,
          -1,
          -1,
          -1,
          1,
          0,
          0);
      }
    }
  }
  Render_FillRect(v30, 0, 0, 0, 0xC8u, 0x73u, v31, v28);
  Render_Present((int)g_RenderState);
  if ( v25 )
    (**(void (***)(void))(v25 + 184))();
  return DLXSpriteSet_ReleaseAndClear((int *)&v27);
}
// 41A6FD: variable 'v11' is possibly undefined
// 41A73A: variable 'v13' is possibly undefined
// 41A817: variable 'v18' is possibly undefined
// 41A850: variable 'v19' is possibly undefined
// 41A857: variable 'v21' is possibly undefined
// 41A859: variable 'v22' is possibly undefined
// 41A8C1: variable 'v8' is possibly undefined
// 41A91B: variable 'v25' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0041A960) --------------------------------------------------------
int  UI_DrawSpecialUnitInfoPane(
        int a1,
        int a2,
        int a3,
        unsigned __int8 *a4,
        DWORD a5,
        int a6)
{
  _DWORD *v7; // eax
  char v8; // bl
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  DWORD v14; // ebp
  int v15; // eax
  int v16; // edi
  char *v17; // ebx
  int v18; // edx
  int v19; // ecx
  int v20; // edi
  int v21; // esi
  int v22; // ecx
  unsigned int v23; // eax
  unsigned int v24; // edx
  int v25; // ecx
  int v26; // eax
  int v27; // eax
  _DWORD *v28; // esi
  char v30[100]; // [esp+0h] [ebp-90h] BYREF
  _DWORD *v31; // [esp+64h] [ebp-2Ch] BYREF
  _DWORD *v32; // [esp+68h] [ebp-28h] BYREF
  _DWORD *v33; // [esp+6Ch] [ebp-24h]
  int v34; // [esp+70h] [ebp-20h]
  int v35; // [esp+74h] [ebp-1Ch]
  int v36; // [esp+78h] [ebp-18h]
  int v37; // [esp+7Ch] [ebp-14h]

  v35 = a1;
  v34 = a2;
  v7 = (_DWORD *)Mem_Alloc(4112, a3, (char)a4, a5);
  if ( v7 )
    v7 = DLXSpriteSet_Load(v7, (char)a4);
  v31 = v7;
  v8 = a4[2];
  UI_BeginUnitInfo(v30, *a4, v8);
  v10 = (_DWORD *)Mem_Alloc(4112, v9, v8, a5);
  if ( v10 )
    v10 = DLXSpriteSet_Load(v10, v8);
  v32 = v10;
  Render_Pump();
  Surface = (_DWORD *)Mem_Alloc(188, v11, v8, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 201, 116);
  v33 = Surface;
  Render_FillRect(0, Surface, (unsigned __int16)v34, (unsigned __int16)v35, v35 + 200, v34 + 115, 0, 0);
  g_RenderDevice = &unk_51D4C0;
  Render_ReleaseSurface(7, a5);
  SpriteForChar = DLX_GetSpriteForChar((int)v31, 24);
  v14 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v14 + 52))(
    v34,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  switch ( *(_WORD *)a4 )
  {
    case UNIT_TYPE_GOLD_CARGO:
      a6 = 26;
      break;
    case UNIT_TYPE_PEASANT_CARGO:
      a6 = 25;
      break;
    case UNIT_TYPE_SPECIAL_FOOT_PERSONAGE:
    case UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE:
      a6 = 28;
      break;
    default:
      break;
  }
  v15 = DLX_GetSpriteForChar((int)v31, a6);
  v16 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v16 + 52))(
    v34 + 20,
    v15,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(15, v14);
  UI_DrawTextFmt(v16, v35 + 120, v35 + 173, v34 + 30, 2, (int)aD_19);
  Render_ReleaseSurface(7, v14);
  UI_DrawTextFmt(v16, v35 + 15, v35 + 88, v34 + 32, 2, (int)aD_20);
  v17 = (**(&g_UnitTypeMetadataRecords + 22 * *(__int16 *)a4))[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(v16, v35 + 64, v35 + 162, v34 + 8, 3, (int)v17);
  if ( (a4[13] & 8) != 0 )
  {
    v27 = DLX_GetSpriteForChar((int)v31, 27);
    LOBYTE(v17) = v35 - 105;
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      v34 + 52,
      v27,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  v20 = Time_Now(v19, v18);
  v37 = v35 + 11;
  v21 = 0;
  v36 = v34 + 5;
  while ( DD_IsLost((int)g_RenderState) || DD_IsFlipping((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, (char)v17);
    v23 = Time_Now(v22, v20 + 10);
    if ( v24 < v23 )
    {
      v20 = Time_Now(v25, v24);
      v21 = (v21 + 1) % 8;
      v26 = DLX_GetSpriteForChar((int)v32, v21);
      LOBYTE(v17) = v37;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        v36,
        v26,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
    }
  }
  Render_FillRect(v33, 0, 0, 0, 0xC8u, 0x73u, v35, v34);
  v28 = v33;
  Render_Present((int)g_RenderState);
  if ( v28 )
    (*(void (**)(void))v28[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&v31);
  return DLXSpriteSet_ReleaseAndClear((int *)&v32);
}
// 41A99F: variable 'v9' is possibly undefined
// 41A9C2: variable 'v11' is possibly undefined
// 41AB96: variable 'v19' is possibly undefined
// 41AB96: variable 'v18' is possibly undefined
// 41ABD6: variable 'v22' is possibly undefined
// 41ABDD: variable 'v24' is possibly undefined
// 41ABDF: variable 'v25' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0041AD20) --------------------------------------------------------
void  Unit_Attack(int a1, int a2, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  __int16 *v8; // ebp
  int v9; // eax
  BOOL v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  _DWORD *v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edx
  unsigned __int8 *v18; // esi
  signed int v19; // eax
  unsigned __int8 *v20; // ebx
  signed int v21; // eax
  int v22; // ecx
  BOOL v23; // eax
  __int16 *v24; // ebx
  signed int v25; // eax
  int v26; // ecx
  BOOL v27; // ecx
  BOOL v28; // edx
  int v29; // ecx
  const char *v30; // eax
  DWORD v31; // edi
  signed int v32; // eax
  int v33; // ecx
  int v34; // ecx
  int v35; // edx
  int v36; // ecx
  unsigned __int8 v37; // al
  _DWORD *v38; // eax
  _DWORD *v39; // eax
  int v40; // ecx
  int v41; // esi
  int v42; // ecx
  signed int v43; // eax
  _WORD *v44; // ecx
  int v45; // ecx
  int v46; // ecx
  int v47; // eax
  int v48; // edx
  signed int v49; // ecx
  int v50; // edx
  int v51; // eax
  int v52; // edx
  signed int v53; // ecx
  signed int v54; // [esp-10h] [ebp-368h]
  int v55; // [esp-Ch] [ebp-364h]
  char v56[404]; // [esp+0h] [ebp-358h] BYREF
  unsigned __int8 v57[404]; // [esp+194h] [ebp-1C4h] BYREF
  int v58; // [esp+328h] [ebp-30h]
  unsigned __int8 *v59; // [esp+32Ch] [ebp-2Ch]
  int v60; // [esp+330h] [ebp-28h]
  int v61; // [esp+334h] [ebp-24h]
  __int16 *v62; // [esp+338h] [ebp-20h]
  int v63; // [esp+33Ch] [ebp-1Ch]
  int v64; // [esp+340h] [ebp-18h]
  int v65; // recovered autoresolve-return probe

  v64 = a1;
  v58 = a2;
  v65 = 0;
  Debug_Log(a1, a3, a4, (int)aUnit_attackDD);
  Render_DrawSprite_v3(v64, a4);
  Render_DrawSprite_v3(v58, a4);
  v8 = (__int16 *)UNIT_STACK(v64);
  v9 = 1423 * *((unsigned __int8 *)v8 + 4);
  v62 = (__int16 *)(725 * v58 + gameData + 147174);
  Diagnostics_TraceWorldMapActionEvent("unit_attack_enter", v64, v58, *v62, v62[1]);
  v10 = *(_DWORD *)(gameData + v9 + 140051) && *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v62 + 4) + 140051);
  v59 = (unsigned __int8 *)v10;
  v63 = 0;
  if ( UnitStack_HasNormalCombatUnits((intptr_t)v8) )
  {
    v12 = *v8 - *v62;
    if ( v12 <= 0 )
      v12 = *v62 - *v8;
    if ( v12 <= 1 )
    {
      v13 = v8[1] - v62[1];
      if ( v13 <= 0 )
        v13 = v62[1] - v8[1];
      if ( v13 <= 1 )
        goto LABEL_22;
    }
    v14 = Unit_MoveTrackNearTile(v64, *v62, (int)v8, v62[1], (DWORD)v8);
    Diagnostics_TraceWorldMapActionEvent(v14 ? "unit_attack_track" : "unit_attack_no_track", v64, v58, *v62, v62[1]);
    if ( v14 )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_attack_track_state",
        v64,
        v58,
        v14[0],
        v14[0] > 0 ? HIWORD(v14[v14[0]]) : 0);
      qmemcpy(v8 + 158, v14, 0x194u);
      UnitStack_ExecuteQueuedPath(v64, 1, (_BYTE)v8 + 60, (DWORD)v8, a5);
      Diagnostics_TraceWorldMapActionEvent("unit_attack_after_track", v64, v58, *v8, v8[1]);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_attack_after_track_state",
        v64,
        v58,
        *((_DWORD *)v8 + 79),
        UnitStack_GetMinCurrentActionPoints((intptr_t)v8));
      if ( !*((_DWORD *)v8 + 79) && (unsigned int)v8[3] <= 0x28 )
      {
        v15 = *v8 - *v62;
        if ( v15 <= 0 )
          v15 = *v62 - *v8;
        if ( v15 <= 1 )
        {
          v16 = v8[1] - v62[1];
          if ( v16 <= 0 )
            v16 = v62[1] - v8[1];
          if ( v16 <= 1 )
          {
LABEL_22:
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_adjacent",
              v64,
              v58,
              Unit_GetSquadCount((int)v8),
              Unit_GetSquadCount((int)v62));
            UnitStack_SetSpentTurnFlag((int)v8);
            UnitStack_AdjustFatigueByPredicate(v8, 10, UnitSlot_PredicateAlways, (DWORD)v8, a5);
            UnitStack_AdjustFatigueByPredicate(v62, 10, UnitSlot_PredicateAlways, (DWORD)v8, a5);
            if ( ACTIVE_MISSION_INDEX == 15 )
              Mission_MarkObjective15CompleteOnAttack(*((unsigned __int8 *)v8 + 4), *((unsigned __int8 *)v62 + 4));
            if ( ACTIVE_MISSION_INDEX == 5 )
              Mission05_MarkFailureOnFriendlyAttack(*((unsigned __int8 *)v8 + 4), *((unsigned __int8 *)v62 + 4));
            v18 = (unsigned __int8 *)UnitStack_HasSpecialPersonageUnits((intptr_t)v8);
            v60 = UnitStack_HasSpecialPersonageUnits((intptr_t)v62);
            v19 = Unit_GetSquadCount((int)v8);
            UnitSlots_ExtractSpecialEntries((char *)v8 + 6, v19, v56);
            v20 = v57;
            v21 = Unit_GetSquadCount((int)v62);
            UnitSlots_ExtractSpecialEntries((char *)v62 + 6, v21, (char *)v57);
            v23 = *(_DWORD *)(1423 * *((unsigned __int8 *)v8 + 4) + gameData + 140051)
               || *(_DWORD *)(1423 * *((unsigned __int8 *)v62 + 4) + gameData + 140051);
            if ( v23 && Unit_GetSquadCount((int)v8) && Unit_GetSquadCount((int)v62) )
            {
              v24 = v62;
              v21 = Unit_GetSquadCount((int)v62);
              v20 = (unsigned __int8 *)(v24 + 3);
              v25 = Unit_GetSquadCount((int)v8);
              v27 = UI_PromptLeadTroopsPersonally((int)(v8 + 3), v25, v21, (int)v20, (DWORD)v8, (int)(v8 + 3), 0) == 0;
            }
            else
            {
              v27 = 0;
            }
            v33 = dword_51D01C || v27;
            if ( v33 )
            {
              if ( *((_BYTE *)v8 + 720) )
              {
                v28 = Unit_GetSquadCount((int)v62) == 0;
                v30 = aAtak_zas;
              }
              else
              {
                v28 = Unit_GetSquadCount((int)v62) == 0;
                v30 = aBattle;
              }
              Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_transition_enter", v64, v58, v28, 0);
              Win_PlayModeChangeFrameTransition(v30, v28, v29, (char)v20, (DWORD)v8);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_transition_return", v64, v58, v28, 0);
            }
            v31 = 0;
            v32 = Unit_GetSquadCount((int)v62);
            v61 = 0;
            if ( v32 <= 0 )
            {
LABEL_48:
              if ( v31 )
              {
                if ( v31 == 1 )
                {
                  UnitSlots_AppendEntries((char *)v62 + 6, (char *)v57);
                  if ( *(__int16 *)v56 != -1 )
                  {
                    v51 = Unit_CreateNearbyUnitGroup(*v62, v62[1], (unsigned __int8 *)v56, a5);
                    if ( (UnitStack_HasPeasantCargo(v51) || UnitStack_HasGoldCargo(v51))
                      && *(unsigned __int8 *)(v51 + 4) == *(_DWORD *)(gameData + 147143) )
                    {
                      v63 = 1;
                    }
                    UnitStack_CaptureDefeatedStack(v62, v51, v51, (int)v56, a5);
                  }
                  UnitStack_AdjustMoraleByPredicate(v8, -5, UnitSlot_PredicateAlways, (DWORD)v8, a5);
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(v62, 4, UnitSlot_PredicateAlways, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v62, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v62, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v62, (DWORD)v8, a5);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v8 + 4) + 141441);
                  ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v62 + 4) + 141441);
                }
                else if ( v31 == 2 )
                {
                  UnitSlots_AppendEntries((char *)v8 + 6, v56);
                  if ( *(__int16 *)v56 != -1 )
                  {
                    v47 = Unit_CreateNearbyUnitGroup(*v8, v8[1], v57, a5);
                    if ( (UnitStack_HasPeasantCargo(v47) || UnitStack_HasGoldCargo(v47))
                      && *(unsigned __int8 *)(v47 + 4) == *(_DWORD *)(gameData + 147143) )
                    {
                      v63 = 1;
                    }
                    UnitStack_CaptureDefeatedStack(v8, v47, v47, (int)v57, a5);
                  }
                  UnitStack_AdjustMoraleByPredicate(v62, -5, UnitSlot_PredicateAlways, (DWORD)v8, a5);
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(v8, 4, UnitSlot_PredicateAlways, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v8, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v8, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v8, (DWORD)v8, a5);
                  UnitStack_SubtractActionPointsFloorZero(v8, 10, (DWORD)v8, a5);
                  ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v8 + 4) + 141441);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v62 + 4) + 141441);
                }
                goto LABEL_52;
              }
LABEL_49:
              UnitSlots_AppendEntries((char *)v8 + 6, v56);
              UnitSlots_AppendEntries((char *)v62 + 6, (char *)v57);
              if ( UnitStack_HasNormalCombatUnits((intptr_t)v62) || !UnitStack_HasNormalCombatUnits((intptr_t)v8) )
              {
                if ( UnitStack_HasNormalCombatUnits((intptr_t)v62) && !UnitStack_HasNormalCombatUnits((intptr_t)v8) )
                {
                  if ( (unsigned int)v8[3] <= 0x28 )
                  {
                    if ( (UnitStack_HasPeasantCargo((int)v8) || UnitStack_HasGoldCargo((int)v8))
                      && *((unsigned __int8 *)v62 + 4) == *(_DWORD *)(gameData + 147143) )
                    {
                      v63 = 1;
                    }
                    UnitStack_CaptureDefeatedStack(v62, (signed int)v8, v46, (int)v20, a5);
                  }
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(v62, 4, UnitSlot_PredicateAlways, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v62, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v62, (DWORD)v8, a5);
                  UnitStack_CycleAllSlotOrders(v62, (DWORD)v8, a5);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v8 + 4) + 141441);
                  ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v62 + 4) + 141441);
                }
              }
              else
              {
                if ( (unsigned int)v62[3] <= 0x28 )
                {
                  if ( (UnitStack_HasPeasantCargo((int)v62) || UnitStack_HasGoldCargo((int)v62))
                    && *((unsigned __int8 *)v8 + 4) == *(_DWORD *)(gameData + 147143) )
                  {
                    v63 = 1;
                  }
                  UnitStack_CaptureDefeatedStack(v8, (signed int)v62, v45, (int)v20, a5);
                }
                v20 = (unsigned __int8 *)CSyncObject_Unlock;
                UnitStack_AdjustMoraleByPredicate(v8, 4, UnitSlot_PredicateAlways, (DWORD)v8, a5);
                UnitStack_CycleAllSlotOrders(v8, (DWORD)v8, a5);
                UnitStack_CycleAllSlotOrders(v8, (DWORD)v8, a5);
                UnitStack_CycleAllSlotOrders(v8, (DWORD)v8, a5);
                ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v8 + 4) + 141441);
                --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v62 + 4) + 141441);
              }
LABEL_52:
              if ( v8[3] == -1 )
                Rules_UnlinkArmyFact(v8, a5);
              if ( v62[3] == -1 )
                Rules_UnlinkArmyFact(v62, a5);
              WorldMap_SyncSelectionForHumanPlayer((DWORD)v8);
              v41 = v61;
              UnitStackSelection_RefreshForSelectedStack((DWORD)v8);
              if ( v41 )
                WorldMap_RenderHook((DWORD)v8);
              else
                WorldMap_RedrawViewport(1);
              if ( v63 )
                Win_PlayModeChangeFrameTransition(aChlop, 1, v42, (char)v20, (DWORD)v8);
              if ( v65 )
                Diagnostics_TraceWorldMapActionEvent("unit_attack_autoresolve_return", v64, v58, *v8, v8[1]);
              Render_DrawSprite_v3(v64, (DWORD)v8);
              Render_DrawSprite_v3(v58, (DWORD)v8);
              return;
            }
            if ( !v33 )
            {
              v55 = v60;
              v20 = v18;
              v54 = Unit_GetSquadCount((int)v62);
              v43 = Unit_GetSquadCount((int)v8);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_autoresolve", v64, v58, v43, v54);
              v65 = 1;
              CalculateBattleResult(v8 + 3, v43, v62 + 3, (int)v18, (DWORD)v8, v54, v55, 0, 0);
              Diagnostics_TraceWorldMapActionEvent(
                "unit_attack_autoresolve_done",
                v64,
                v58,
                Unit_GetSquadCount((int)v8),
                Unit_GetSquadCount((int)v62));
              goto LABEL_49;
            }
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_prepare", v64, v58, v33, 0);
            Render_Pump();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_render_pump", v64, v58, 0, 0);
            Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_unlock", v64, v58, 0, 0);
            DLXSpriteSet_ReleaseAndClear(&dword_5202BC);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_frame_free", v64, v58, 0, 0);
            BuildingSpriteCache_Clear();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_building_cache_clear", v64, v58, 0, 0);
            UnitSpriteCache_FreeAllEntries(v34, (DWORD)v8);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_unit_cache_clear", v64, v58, 0, 0);
            CSS_EmptySampleCache();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_sample_clear", v64, v58, 0, 0);
            TextSprite_ReleaseAllResourceSlots();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_text_enddraw", v64, v58, 0, 0);
            v54 = Unit_GetSquadCount((int)v62);
            v43 = Unit_GetSquadCount((int)v8);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_battle_enter", v64, v58, v43, v54);
            Battle_ResetInputScriptReader();
            v31 = Battle_RunTacticalCombat(
                    (__int16 *)(gameData + 147174 + 725 * v64),
                    (__int16 *)(gameData + 147174 + 725 * v58),
                    (int)v18,
                    0,
                    (DWORD)v8,
                    v60);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_battle_return", v64, v58, v31, 0);
            v37 = *(_BYTE *)(gameData + 140016);
            if ( dword_5202C0 )
              DLXSpriteSet_ReleaseAndClear(&dword_5202C0);
            if ( v37 == 0 )
            {
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v8);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr1.s32");
              dword_5202C0 = (int)v38;
            }
            else if ( v37 == 1 )
            {
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v8);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr2.s32");
              dword_5202C0 = (int)v38;
            }
            else if ( v37 == 2 )
            {
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v8);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr3.s32");
              dword_5202C0 = (int)v38;
            }
            v39 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v8);
            if ( v39 )
              v39 = DLXSpriteSet_Load(v39, "frame.s32");
            dword_5202BC = (int)v39;
            Tooltip_CaptureBackdrop(160, 473, 3, 467, 76);
            Palette_LoadOrBuildBlendLookupTable(aMainmap_0, dword_5202F4, 1, (DWORD)v8);
            v61 = 1;
            goto LABEL_48;
          }
        }
      }
    }
  }
}
// 41AEB1: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41B401: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41B4CA: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41AD4C: variable 'v5' is possibly undefined
// 41AD5A: variable 'v6' is possibly undefined
// 41AD82: variable 'v7' is possibly undefined
// 41AE60: variable 'v11' is possibly undefined
// 41AF0E: variable 'v17' is possibly undefined
// 41AFC1: variable 'v22' is possibly undefined
// 41B03E: variable 'v26' is possibly undefined
// 41B085: variable 'v29' is possibly undefined
// 41B0A9: variable 'v33' is possibly undefined
// 41B0D7: variable 'v34' is possibly undefined
// 41B110: variable 'v35' is possibly undefined
// 41B17B: variable 'v36' is possibly undefined
// 41B1E7: variable 'v40' is possibly undefined
// 41B2B0: variable 'v42' is possibly undefined
// 41B3DB: variable 'v44' is possibly undefined
// 41B442: variable 'v45' is possibly undefined
// 41B50E: variable 'v46' is possibly undefined
// 41B5F0: variable 'v49' is possibly undefined
// 41B652: variable 'v50' is possibly undefined
// 41B6E9: variable 'v53' is possibly undefined
// 41B798: variable 'v52' is possibly undefined
// 41B7AC: variable 'v48' is possibly undefined
// 51D01C: using guessed type int dword_51D01C;
// 5202BC: using guessed type int dword_5202BC;
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;
// 5202F4: using guessed type int dword_5202F4;

//----- (0041B7D0) --------------------------------------------------------
void  Unit_AttackBuilding(int a1, int a2, char a3, DWORD a4, double a5)
{
  unsigned __int8 *v7; // ebp
  BOOL v8; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  const void *v13; // eax
  int v16; // edi
  BOOL v19; // eax
  signed int v23; // eax
  signed int v25; // esi
  signed int v26; // eax
  int v28; // eax
  int v30; // ecx
  int v32; // ebx
  int v33; // ecx
  unsigned __int8 *v34; // ebx
  int v35; // ecx
  DWORD v36; // esi
  unsigned __int8 v37; // al
  _DWORD *v38; // eax
  _DWORD *v39; // eax
  char v40; // bl
  int v41; // ecx
  DWORD v42; // ebp
  __int16 *v43; // esi
  signed int v44; // eax
  _WORD *v45; // ecx
  int v48; // edx
  int v51; // [esp-10h] [ebp-364h]
  int v52; // [esp-Ch] [ebp-360h]
  int v53; // [esp-8h] [ebp-35Ch]
  char v54[404]; // [esp+0h] [ebp-354h] BYREF
  char v55[404]; // [esp+194h] [ebp-1C0h] BYREF
  BOOL v56; // [esp+328h] [ebp-2Ch]
  int v57; // [esp+32Ch] [ebp-28h]
  DWORD v58; // [esp+330h] [ebp-24h]
  int v59; // [esp+334h] [ebp-20h]
  int v60; // [esp+338h] [ebp-1Ch]
  __int16 *v61; // [esp+33Ch] [ebp-18h]

  v60 = a1;
  v59 = a2;
  Debug_Log(a1, a3, a4, (int)aUnit_attackbui);
  Render_DrawSprite_v3(v60, 467 * v59);
  v61 = (__int16 *)UNIT_STACK(v60);
  v7 = (unsigned __int8 *)(UNIT_RECORD(v59));
  v8 = PLAYER_HAS_HUMAN_CONTROLLER(UNIT_STACK_OWNER_INDEX((int)v61)) && PLAYER_HAS_HUMAN_CONTROLLER(v7[2]);
  v56 = v8;
  if ( UnitStack_HasNormalCombatUnits((intptr_t)v61) )
  {
    v10 = *v61 - *v7;
    if ( v10 <= 0 )
      v10 = *v7 - *v61;
    if ( v10 <= 1 )
    {
      v11 = v7[1];
      v12 = v61[1] - v11;
      if ( v12 <= 0 )
        v12 = v11 - v61[1];
      if ( v12 <= 1 )
        goto LABEL_15;
    }
    v13 = (const void *)Building_GenerateApproachTrack(v60, v59, 0, 0, 0);
    if ( v13 )
    {
      qmemcpy(v61 + 158, v13, 0x194u);
      UnitStack_ExecuteQueuedPath(v60, 1, (_BYTE)v61 + 60, (DWORD)v7, a5);
      if ( !*((_DWORD *)v61 + 79) )
      {
LABEL_15:
        if ( UnitStack_GetMinCurrentActionPoints((intptr_t)v61) >= 5 )
        {
          UnitStack_SpendActionPointsByIndexClamped(v60, 5, (DWORD)v7, a5);
          UnitStack_SetSpentTurnFlag((int)v61);
          UnitStack_AdjustFatigueByPredicate(v61, 10, UnitSlot_PredicateAlways, (DWORD)v7, a5);
          if ( ACTIVE_MISSION_INDEX == 15 )
            Mission_MarkObjective15CompleteOnAttack(*((unsigned __int8 *)v61 + 4), v7[2]);
          if ( ACTIVE_MISSION_INDEX == 5 )
            Mission05_MarkFailureOnFriendlyAttack(*((unsigned __int8 *)v61 + 4), v7[2]);
          v16 = UnitStack_HasSpecialPersonageUnits((intptr_t)v61);
          v57 = Building_HasSpecialPersonageGarrisonEntries((int)v7);
          v19 = PLAYER_HAS_HUMAN_CONTROLLER(UNIT_STACK_OWNER_INDEX((int)v61)) || PLAYER_HAS_HUMAN_CONTROLLER(v7[2]);
          if ( !v19 || Building_CountGarrison((int)v7) == Building_CountNonCombatGarrisonEntries((int)v7) )
          {
            v25 = 0;
          }
          else
          {
            v23 = Unit_GetSquadCount((int)v61);
            v25 = UI_PromptLeadTroopsPersonally((int)(v61 + 3), v23, 12, (int)(v7 + 18), (DWORD)v7, v16, 1) == 0;
          }
          Diagnostics_TraceWorldMapActionEvent("unit_attack_building_prompt_result", v60, v59, v25, dword_51D01C);
          if ( dword_51D01C )
          {
            v25 = 1;
          }
          else if ( !v25 )
          {
LABEL_28:
            v58 = 0;
            if ( !Building_CountGarrison(UNIT_RECORD(v59)) )
            {
              UnitStack_AdjustMoraleByPredicate(v61, 4, UnitSlot_PredicateAlways, (DWORD)v7, a5);
              UnitStack_CycleAllSlotOrders(v61, (DWORD)v7, a5);
              UnitStack_CycleAllSlotOrders(v61, (DWORD)v7, a5);
              UnitStack_CycleAllSlotOrders(v61, (DWORD)v7, a5);
              Unit_CaptureBuilding(v60, v59, 0, v25, a5);
              ++*(_WORD *)(1423 * *((unsigned __int8 *)v61 + 4) + gameData + 141441);
              --*(_WORD *)(1423 * v7[2] + gameData + 141441);
LABEL_47:
              if ( v61[3] == -1 )
                Rules_UnlinkArmyFact(v61, a5);
              WorldMap_SyncSelectionForHumanPlayer((DWORD)v7);
              v42 = v58;
              UnitStackSelection_RefreshForSelectedStack(v58);
              if ( v42 )
                WorldMap_RenderHook(v42);
              Render_DrawSprite_v3(v60, v42);
              return;
            }
            Building_CompactGarrison(v7, (unsigned __int8 *)v61, a5);
            v26 = Unit_GetSquadCount((int)v61);
            UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)v61 + 6, v26, v54);
            v28 = Building_CountGarrison((int)v7);
            UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)v7 + 18, v28, v55);
            Building_CompactGarrison(v7, v7 + 18, a5);
            for ( v30 = 0; v30 < 12; ++v30 )
            {
              Building_ClearGarrisonTrainingTimer((int)v7, v30);
              Building_ClearGarrisonRepairTimer((int)v7, v30);
            }
            v32 = 467 * v59;
            if ( !v25 )
            {
              v53 = v32 + gameData + 509674;
              v52 = v57;
              v51 = Building_CountGarrison(v53);
              v43 = v61 + 3;
              v40 = (char)v16;
              v44 = Unit_GetSquadCount((int)v61);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_building_autoresolve", v60, v59, v44, v51);
              CalculateBattleResult(v43, v44, v45, v16, (DWORD)v7, v51, v52, v53, 0);
              Diagnostics_TraceWorldMapActionEvent(
                "unit_attack_building_autoresolve_done",
                v60,
                v59,
                Unit_GetSquadCount((int)v61),
                Building_CountGarrison(v53));
              v36 = 0;
LABEL_42:
              UnitSlots_AppendEntriesForBuildingAttack((char *)v61 + 6, v54);
              if ( v36 )
              {
                if ( v36 == 1 )
                {
                  UnitStack_AdjustMoraleByPredicate(v61, -5, UnitSlot_PredicateAlways, (DWORD)v7, a5);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)v61 + 4) + 141441);
                  ++*(_WORD *)(gameData + 1423 * v7[2] + 141441);
                  Building_AdjustAllGarrisonMoraleByDelta((int)v7, 4);
                  Building_CycleAllGarrisonOrdersOnce((int)v7);
                  Building_CycleAllGarrisonOrdersOnce((int)v7);
                  Building_CycleAllGarrisonOrdersOnce((int)v7);
                }
              }
              else if ( Building_CountGarrison(UNIT_RECORD(v59))
                     || !UnitStack_HasNormalCombatUnits(725 * v60 + gameData + 147174) )
              {
                if ( Building_CountGarrison(UNIT_RECORD(v59))
                  && !UnitStack_HasNormalCombatUnits(725 * v60 + gameData + 147174) )
                {
                  UnitSlots_AppendEntriesForBuildingAttack((char *)v7 + 18, v55);
                  UnitStack_KillByIndex(v60, v40, (DWORD)v7, a5);
                  --*(_WORD *)(gameData + 1423 * *(unsigned __int8 *)(v48 + 4) + 141441);
                  ++*(_WORD *)(1423 * v7[2] + gameData + 141441);
                  Building_AdjustAllGarrisonMoraleByDelta((int)v7, 4);
                  Building_CycleAllGarrisonOrdersOnce((int)v7);
                  Building_CycleAllGarrisonOrdersOnce((int)v7);
                  Building_CycleAllGarrisonOrdersOnce((int)v7);
                }
                else if ( !Building_CountGarrison(UNIT_RECORD(v59))
                       && !UnitStack_HasNormalCombatUnits(725 * v60 + gameData + 147174) )
                {
                  UnitStack_KillByIndex(v60, v40, (DWORD)v7, a5);
                }
              }
              else
              {
                UnitStack_AdjustMoraleByPredicate(v61, 4, UnitSlot_PredicateAlways, (DWORD)v7, a5);
                UnitStack_CycleAllSlotOrders(v61, (DWORD)v7, a5);
                UnitStack_CycleAllSlotOrders(v61, (DWORD)v7, a5);
                UnitStack_CycleAllSlotOrders(v61, (DWORD)v7, a5);
                Unit_CaptureBuilding(v60, v59, 0, 0, a5);
                ++*(_WORD *)(1423 * *((unsigned __int8 *)v61 + 4) + gameData + 141441);
                --*(_WORD *)(1423 * v7[2] + gameData + 141441);
              }
              goto LABEL_47;
            }
            Render_Pump();
            Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
            DLXSpriteSet_ReleaseAndClear(&dword_5202BC);
            BuildingSpriteCache_Clear();
            UnitSpriteCache_FreeAllEntries(v33, (DWORD)v7);
            CSS_EmptySampleCache();
            TextSprite_ReleaseAllResourceSlots();
            v34 = (unsigned __int8 *)(gameData + 509674 + v32);
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_building_battle_enter",
              v60,
              v59,
              Unit_GetSquadCount((int)v61),
              Building_CountGarrison((int)v7));
            v36 = Battle_RunTacticalCombat((__int16 *)(725 * v60 + gameData + 147174), 0, (int)v16, v34, (DWORD)v7, v57);
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_building_battle_return",
              v60,
              v59,
              v36,
              Building_CountGarrison((int)v7));
            v37 = *(_BYTE *)(gameData + 140016);
            if ( v37 == 0 )
            {
              if ( dword_5202C0 )
                DLXSpriteSet_ReleaseAndClear(&dword_5202C0);
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v7);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr1.s32");
              dword_5202C0 = (int)v38;
            }
            else if ( v37 == 1 )
            {
              if ( dword_5202C0 )
                DLXSpriteSet_ReleaseAndClear(&dword_5202C0);
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v7);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr2.s32");
              dword_5202C0 = (int)v38;
            }
            else if ( v37 == 2 )
            {
              if ( dword_5202C0 )
                DLXSpriteSet_ReleaseAndClear(&dword_5202C0);
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v7);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr3.s32");
              dword_5202C0 = (int)v38;
            }
            v39 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)v7);
            if ( v39 )
              v39 = DLXSpriteSet_Load(v39, "frame.s32");
            v40 = -45;
            dword_5202BC = (int)v39;
            Tooltip_CaptureBackdrop(160, 473, 3, 467, 76);
            Palette_LoadOrBuildBlendLookupTable(aMainmap_1, dword_5202F4, 1, (DWORD)v7);
            v58 = 1;
            if ( v56 )
              UI_LoadTurnBannerGfx(211, (DWORD)v7);
            goto LABEL_42;
          }
          Win_PlayModeChangeFrameTransition(aAtak_zam, 0, 0, 0, 0);
          goto LABEL_28;
        }
      }
    }
  }
}
// 41BB63: variable 'v33' is possibly undefined
// 41BBEA: variable 'v35' is possibly undefined
// 41BC45: variable 'v41' is possibly undefined
// 41BE69: variable 'v45' is possibly undefined
// 41BF5D: variable 'v48' is possibly undefined
// 51D01C: using guessed type int dword_51D01C;
// 5202BC: using guessed type int dword_5202BC;
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;
// 5202F4: using guessed type int dword_5202F4;

//----- (0041C100) --------------------------------------------------------
int  UnitSlots_CalcCombatStrengthScore(char *a1, int a2, int a3, int a4)
{
  unsigned int v6; // eax
  int v7; // edi
  char *(**v8)[102]; // ecx
  int v9; // eax
  int v11; // ebp
  int v13; // eax
  int v15; // edi
  int v16; // edx
  __int64 v17; // rax
  int v18; // eax
  int v19; // edi
  int v20; // edx
  int v23; // [esp+8h] [ebp-14h]
  int v24;

  v23 = 0;
  while ( --a2 != -1 )
  {
    while ( 1 )
    {
      v6 = *(__int16 *)a1;
      if ( v6 <= 0x28 )
        break;
      a1 += 31;
    }
    v7 = 0;
    v8 = &g_UnitTypeMetadataRecords + 22 * v6;
    if ( v6 == 13 )
    {
      if ( a4 )
      {
        v9 = Unit_CalcEffectivenessD(a1, a3);
        v7 = v9 * (*((unsigned __int8 *)v8 + 24) / 5) / 2;
      }
      else
      {
        v7 = 1;
      }
      goto LABEL_8;
    }
    if ( *((_BYTE *)v8 + 22) && !*((_BYTE *)v8 + 25) )
    {
      v15 = *((unsigned __int8 *)v8 + 24) / 5 - 1;
      if ( (*((_BYTE *)v8 + 18) & 1) == 0 )
        v15 -= 2 * a4 / 100;
      v16 = Unit_CalcEffectivenessA(a1, a3) * v15 + v23;
      a1 += 31;
      v23 = v16;
    }
    else if ( *((_BYTE *)v8 + 22) || !*((_BYTE *)v8 + 25) )
    {
      if ( !*((_BYTE *)v8 + 22) || !*((_BYTE *)v8 + 25) )
        goto LABEL_8;
      v11 = (a1[12] & 3) + 1;
      if ( v11 >= *((unsigned __int8 *)v8 + 24) / 5 )
        v11 = *((unsigned __int8 *)v8 + 24) / 5;
      v7 = Unit_CalcEffectivenessC((__int16 *)a1) * v11;
      v24 = *((unsigned __int8 *)v8 + 24) / 5 - v11 - 1;
      if ( v24 > 0 )
      {
        v13 = Unit_CalcEffectivenessA(a1, a3);
        a1 += 31;
        v23 += v24 * v13 + v7;
      }
      else
      {
LABEL_8:
        a1 += 31;
        v23 += v7;
      }
    }
    else
    {
      v17 = 6 - *((unsigned __int8 *)v8 + 26);
      v18 = *((unsigned __int8 *)v8 + 24) / 5 - (((int)v17 - HIDWORD(v17)) >> 1);
      if ( (a1[12] & 3) + 1 < v18 )
        v18 = (a1[12] & 3) + 1;
      v19 = v18;
      if ( v18 >= 3 )
        v19 = v18 + 2;
      v20 = Unit_CalcEffectivenessC((__int16 *)a1) * v19 + v23;
      a1 += 31;
      v23 = v20;
    }
  }
  return v23;
}
// 41C143: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (0041C300) --------------------------------------------------------
int  UnitSlots_CalcDefenseScore(char *a1, int a2, int a3)
{
  int i; // ebx
  int v7; // eax

  for ( i = 0; --a2 != -1; i += v7 )
  {
    while ( (unsigned int)*(__int16 *)a1 > 0x28 )
      a1 += 31;
    v7 = Unit_CalcEffectivenessB(a1, a3);
    a1 += 31;
  }
  return (300 * i - (__CFSHL__((300 * i) >> 31, 8) + ((300 * i) >> 31 << 8))) >> 8;
}
// 41C316: simplified comparisons for 'eax.4': >=0 && <29 became <29u

//----- (0041C360) --------------------------------------------------------
int  Building_ApplySiegeDamageToWallSections(int a1, signed int a2)
{
  signed int v3; // ebx
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  unsigned int v8; // ebx
  char v9; // dl
  int v10; // ecx
  int v11; // ecx

  v3 = a2;
  result = a2 / 100;
  v5 = a2 / 100;
  if ( a2 / 100 > 2 )
    v5 = 2;
  while ( v5 )
  {
    result = Rng_RandRange(0, 6);
    v6 = *(unsigned __int8 *)(a1 + result + 422);
    *(_BYTE *)(a1 + result + 422) = 0;
    v3 -= v6;
  }
  if ( v3 )
  {
    do
      v8 = Rng_RandRange(0, 6);
    while ( !*(_BYTE *)(a1 + v8 + 422) && v7 + 1 < 6 );
    result = Rng_RandRange(10, 25);
    v9 = result;
    v11 = *(unsigned __int8 *)(v10 + 422);
    if ( result > v11 )
      v9 = v11;
    *(_BYTE *)(a1 + v8 + 422) -= v9;
  }
  return result;
}
// 41C37E: variable 'v5' is possibly undefined
// 41C3CA: variable 'v7' is possibly undefined
// 41C3E4: variable 'v10' is possibly undefined

//----- (0041C410) --------------------------------------------------------
int  Building_CalcWallDefenseBonus(int a1, signed int a2)
{
  int v3; // eax
  int v4; // ecx
  int i; // edx
  int v6; // ecx
  int v7; // edi
  int j; // edx
  int v9; // eax

  v3 = 100;
  v4 = a1;
  for ( i = 0; i < 7; ++i )
  {
    if ( *(unsigned __int8 *)(v4 + 422) < v3 )
    {
      v3 = *(unsigned __int8 *)(v4 + 422);
      a2 = i;
    }
    ++v4;
  }
  v6 = a1;
  v7 = v3;
  for ( j = 0; j < 7; ++j )
  {
    if ( *(unsigned __int8 *)(v6 + 422) < v3 && j != a2 )
      v3 = *(unsigned __int8 *)(v6 + 422);
    ++v6;
  }
  v9 = (v3 + v7) / 2 * (unsigned __int16)g_WallKindDefenseFactor[2 * *(unsigned __int8 *)(a1 + 421)];
  return (v9 - (__CFSHL__(v9 >> 31, 8) + (v9 >> 31 << 8))) >> 8;
}
// 513A78: using guessed type __int16 word_513A78[];

//----- (0041C4A0) --------------------------------------------------------
int  CalculateBattleResult(
        _WORD *a1,
        int a2,
        _WORD *a3,
        int a4,
        DWORD a5,
        int a6,
        int a7,
        int a8,
        int a9)
{
  char v48[12]; // [esp+0h] [ebp-40h]
  _WORD *v49; // [esp+Ch] [ebp-34h]
  int v50; // [esp+10h] [ebp-30h]
  signed int v51; // [esp+14h] [ebp-2Ch]
  signed int v52; // [esp+18h] [ebp-28h]
  int v53; // [esp+1Ch] [ebp-24h]
  signed int v54; // [esp+20h] [ebp-20h]
  int v55; // [esp+24h] [ebp-1Ch]
  _WORD *v56; // [esp+28h] [ebp-18h]
  __int16 *v57; // [esp+2Ch] [ebp-14h]
  int v58; // [esp+30h] [ebp-10h]
  int defender_combat;
  int defender_score;
  int wall_defense_bonus;
  int i;
  int selected_slot;
  int selected_priority;
  int slot_priority;
  int old_quantity;
  int new_quantity;
  int loss_delta;
  int slot_index;
  int applied_loss;

  v49 = a1;
  v53 = a4;
  Battle_StoreLastOutcomeValue(1);
  Debug_Log(0, 0, a5, (int)aNewBattle);
  Debug_Log((int)v49, (char)a2, a5, (int)aCalculatebattl, (int)v49, a2, v53, (int)a3, a6, a7, a8, a9);
  Debug_Log(0, 0, a5, (int)aJednostka1);
  Debug_Log(0, 0, a5, (int)aJednostka2);
  if ( a8 )
    wall_defense_bonus = Building_CalcWallDefenseBonus(a8, (signed int)a3);
  else
    wall_defense_bonus = 0;
  v50 = UnitSlots_CalcCombatStrengthScore((char *)v49, a2, v53, wall_defense_bonus);
  defender_combat = UnitSlots_CalcCombatStrengthScore((char *)a3, a6, a7, 0);
  v54 = v50 - UnitSlots_CalcDefenseScore((char *)a3, a6, a7);
  defender_score = defender_combat - UnitSlots_CalcDefenseScore((char *)v49, a2, v53);
  Debug_Log(v54, 0, a5, (int)aAs1D, v54);
  Debug_Log(defender_score, 0, a5, (int)aAs2D, defender_score);
  if ( v54 < 0 )
    v54 = 0;
  if ( defender_score < 0 )
    defender_score = 0;
  if ( !v54 )
    v54 = 1;
  if ( !defender_score )
    defender_score = 1;
  if ( defender_score == v54 )
    ++v54;
  if ( a9 )
    v54 = 135 * v54 / 100;
  if ( defender_score > v54 )
    v51 = defender_score;
  else
    v51 = v54;
  if ( defender_score > v54 )
    v52 = v54;
  else
    v52 = defender_score;
  if ( defender_score > v54 )
    v57 = (__int16 *)a3;
  else
    v57 = (__int16 *)v49;
  if ( defender_score > v54 )
    v56 = v49;
  else
    v56 = a3;
  if ( defender_score > v54 )
    v55 = a2;
  else
    v55 = a6;
  if ( defender_score > v54 )
    a2 = a6;
  v58 = 0;
  for ( i = 0; i < a2; ++i )
    v58 += *((signed char *)v57 + 31 * i + 9);
  v58 = v58 * v52 / v51;
  Debug_Log(v58, (char)v51, a5, (int)aSum_quantDAtt_, v58);
  while ( v58 > 0 )
  {
    applied_loss = 0;
    memset(v48, 0, sizeof(v48));
    while ( v58 > 0 )
    {
      for ( slot_index = 0; slot_index < a2 && slot_index < (int)sizeof(v48) && v48[slot_index]; ++slot_index )
        ;
      if ( slot_index >= a2 || slot_index >= (int)sizeof(v48) )
        break;
      selected_slot = -1;
      selected_priority = 0;
      for ( i = 0; i < a2 && i < (int)sizeof(v48); ++i )
      {
        slot_priority = (unsigned __int8)unit_stats[88 * *(__int16 *)((char *)v57 + 31 * i)];
        if ( slot_priority > selected_priority && !v48[i] )
        {
          selected_priority = slot_priority;
          selected_slot = i;
        }
      }
      if ( selected_slot < 0 )
      {
        v58 = 0;
        break;
      }
      old_quantity = *((signed char *)v57 + 31 * selected_slot + 9);
      new_quantity = old_quantity - selected_priority;
      if ( new_quantity < 0 )
        new_quantity = 0;
      new_quantity -= Rng_RandRange(0, 10);
      loss_delta = old_quantity - new_quantity;
      v58 -= loss_delta;
      if ( v58 < 0 )
        new_quantity -= v58;
      if ( new_quantity < 0 )
        new_quantity = 0;
      if ( loss_delta > 0 )
        applied_loss = 1;
      *((_BYTE *)v57 + 31 * selected_slot + 9) = new_quantity;
      v48[selected_slot] = 1;
    }
    if ( !applied_loss )
      break;
  }
  Debug_Log(0, 0, a5, (int)aJednostkaZwyci);
  for ( i = 0; i < a2; ++i )
  {
    if ( !*((_BYTE *)v57 + 31 * i + 9) )
      *(__int16 *)((char *)v57 + 31 * i) = -1;
  }
  UnitSlots_RemoveGaps((_WORD *)v57, a2);
  if ( a8 )
    Building_ApplySiegeDamageToWallSections(a8, v54);
  for ( i = 0; i < v55; ++i )
  {
    *v56 = -1;
    v56 = (_WORD *)((char *)v56 + 31);
  }
  return Battle_StoreLastOutcomeValue(0);
}
// 41C719: conditional instruction was optimized away because esi.4>=1
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (0041C8B0) --------------------------------------------------------
signed int  UI_PromptLeadTroopsPersonally(
        int a1,
        int a2,
        int a3,
        int a4,
        DWORD a5,
        int a6,
        int a7)
{
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // eax
  void *v10; // ecx
  int SpriteForChar; // eax
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int v15; // esi
  unsigned __int8 *v16; // edi
  char v17; // bl
  int v18; // ecx
  _DWORD *v19; // eax
  int v20; // eax
  int v21; // esi
  unsigned __int8 *v22; // edi
  char v23; // bl
  int v24; // ecx
  _DWORD *v25; // eax
  int v26; // eax
  int v27; // ebx
  int v28; // edi
  int v29; // ebx
  int v30; // edi
  signed int v31; // ebp
  unsigned __int16 SpriteHeight; // ax
  int v33; // edx
  int v34; // esi
  unsigned __int16 v35; // cx
  unsigned __int16 v36; // bx
  __int16 SpriteWidth; // ax
  __int16 v38; // cx
  __int16 v39; // ax
  int v40; // ecx
  unsigned __int16 v42; // [esp-Ch] [ebp-140h]
  unsigned __int16 v43; // [esp-8h] [ebp-13Ch]
  unsigned __int16 v44; // [esp-4h] [ebp-138h]
  char v45[100]; // [esp+0h] [ebp-134h] BYREF
  char v46[100]; // [esp+64h] [ebp-D0h] BYREF
  int v47[3]; // [esp+C8h] [ebp-6Ch]
  _DWORD *v48; // [esp+D4h] [ebp-60h] BYREF
  _DWORD *v49; // [esp+D8h] [ebp-5Ch] BYREF
  _DWORD *v50; // [esp+DCh] [ebp-58h] BYREF
  int v51; // [esp+E0h] [ebp-54h]
  int (*v52)(); // [esp+E4h] [ebp-50h]
  int v53; // [esp+E8h] [ebp-4Ch]
  int v54; // [esp+ECh] [ebp-48h]
  int v55; // [esp+F0h] [ebp-44h]
  int v56; // [esp+F4h] [ebp-40h]
  int v57; // [esp+F8h] [ebp-3Ch]
  int v58; // [esp+FCh] [ebp-38h]
  int v59; // [esp+100h] [ebp-34h]
  int v60; // [esp+104h] [ebp-30h]
  int v61; // [esp+108h] [ebp-2Ch]
  int v62; // [esp+10Ch] [ebp-28h]
  int v63; // [esp+110h] [ebp-24h]
  int v64; // [esp+114h] [ebp-20h]
  int v65; // [esp+118h] [ebp-1Ch]
  int v66; // [esp+11Ch] [ebp-18h]
  int v67; // [esp+120h] [ebp-14h]
  int v68; // [esp+124h] [ebp-10h]

  v64 = a1;
  v61 = a2;
  v63 = a4;
  v60 = a3;
  v53 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v52 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(0, a4, a5, (int)aSetrhS08x_3);
  v9 = (_DWORD *)Mem_Alloc(4112, 0, a4, a5);
  if ( v9 )
    v9 = DLXSpriteSet_Load(v9, "auto.s32");
  v48 = v9;
  Render_Pump();
  g_RenderDevice = &unk_51D4C0;
  v55 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v48, 0)) / 2;
  v54 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v48, 0)) / 2;
  SpriteForChar = DLX_GetSpriteForChar((int)v48, 0);
  Compat_RenderDeviceDrawMenuSprite(v54, v55, SpriteForChar, 1);
  if ( a7 )
  {
    v12 = DLX_GetSpriteForChar((int)v48, 3);
    Compat_RenderDeviceDrawMenuSprite(v54 + 59, v55 + 441, v12, 1);
  }
  Render_ReleaseSurface(7, a5);
  UI_DrawTextFmt(a6, v55 + 42, v55 + 166, v54 + 85, 3, 1423 * *(unsigned __int8 *)(v64 + 2) + gameData + 140024 + 4);
  UI_DrawTextFmt(a6, v55 + 395, v55 + 518, v54 + 85, 3, 1423 * *(unsigned __int8 *)(v63 + 2) + gameData + 140024 + 4);
  v15 = 0;
  if ( v61 > 0 )
  {
    v57 = v54 + 110;
    v16 = (unsigned __int8 *)v64;
    v58 = v55 + 18;
    do
    {
      if ( *(__int16 *)v16 != -1 )
      {
        v17 = *(_BYTE *)(v64 + 2);
        UI_BeginUnitInfo(v45, *v16, v17);
        v19 = (_DWORD *)Mem_Alloc(4112, v18, v17, a5);
        if ( v19 )
          v19 = DLXSpriteSet_Load(v19, v45);
        v65 = 76 * ((v15 - (__CFSHL__(v15 >> 31, 2) + 4 * (v15 >> 31))) >> 2) + v57;
        v67 = 48 * (v15 % 4) + v58;
        v49 = v19;
        v20 = DLX_GetSpriteForChar((int)v19, 0);
        Compat_RenderDeviceDrawMenuSprite(v65, v67, v20, 1);
        if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(v64 + 2) + 140051) )
          UI_DrawTextFmt((int)v16, v67, v67 + 32, v65 + 50, 3, (int)aD_3);
        DLXSpriteSet_ReleaseAndClear((int *)&v49);
      }
      a5 = v61;
      ++v15;
      v16 += 31;
    }
    while ( v15 < v61 );
  }
  v21 = 0;
  if ( v60 > 0 )
  {
    v59 = v54 + 110;
    v22 = (unsigned __int8 *)v63;
    v56 = v55 + 371;
    do
    {
      if ( *(__int16 *)v22 != -1 )
      {
        v23 = *(_BYTE *)(v63 + 2);
        UI_BeginUnitInfo(v46, *v22, v23);
        v25 = (_DWORD *)Mem_Alloc(4112, v24, v23, a5);
        if ( v25 )
          v25 = DLXSpriteSet_Load(v25, v46);
        v66 = 76 * ((v21 - (__CFSHL__(v21 >> 31, 2) + 4 * (v21 >> 31))) >> 2) + v59;
        v68 = 48 * (v21 % 4) + v56;
        v50 = v25;
        v26 = DLX_GetSpriteForChar((int)v25, 0);
        Compat_RenderDeviceDrawMenuSprite(v66, v68, v26, 1);
        if ( *(_DWORD *)(1423 * *(unsigned __int8 *)(v63 + 2) + gameData + 140051) )
          UI_DrawTextFmt((int)v22, v68, v68 + 32, v66 + 50, 3, (int)aD_4);
        DLXSpriteSet_ReleaseAndClear((int *)&v50);
      }
      a5 = v60;
      ++v21;
      v22 += 31;
    }
    while ( v21 < v60 );
  }
  v47[0] = (int)g_LeadTroopsPersonallyPromptTexts[0];
  v47[1] = (int)g_LeadTroopsPersonallyPromptTexts[1];
  v47[2] = (int)g_LeadTroopsPersonallyPromptTexts[2];
  Render_ReleaseSurface(17, a5);
  UI_DrawTextFmt((int)&v48, v55 + 160, v55 + 390, v54 + 10, 6, v47[(unsigned __int8)g_LanguageIndex]);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  v27 = v54;
  v28 = v55;
  Render_Present((int)g_RenderState);
  v29 = v27 + 61;
  v30 = v28 + 279;
  v62 = v55 + 201;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_prompt_layout_primary",
    v62,
    v29,
    v62 + (unsigned __int16)DLX_GetSpriteHeight((int)v48, 1u),
    v29 + (unsigned __int16)DLX_GetSpriteWidth((int)v48, 1u));
  Diagnostics_TraceWorldMapActionEvent(
    "battle_prompt_layout_secondary",
    v30,
    v29,
    v30 + (unsigned __int16)DLX_GetSpriteHeight((int)v48, 2u),
    v29 + (unsigned __int16)DLX_GetSpriteWidth((int)v48, 2u));
  while ( 1 )
  {
    do
    {
      WorldMap_RunInputScriptStep();
      DD_Pump((int)g_RenderState, v29);
    }
    while ( !DD_IsFlipping((int)g_RenderState) );
    v31 = v29 + (unsigned __int16)DLX_GetSpriteWidth((int)v48, 1u);
    SpriteHeight = DLX_GetSpriteHeight((int)v48, 1u);
    if ( dword_544CFC >> byte_54512C >= v62
      && dword_544D00 >> byte_54512C >= v29
      && dword_544CFC >> byte_54512C <= SpriteHeight + v62
      && dword_544D00 >> byte_54512C <= v31 )
    {
      break;
    }
    v31 = v29 + (unsigned __int16)DLX_GetSpriteWidth((int)v48, 2u);
    v33 = v30 + (unsigned __int16)DLX_GetSpriteHeight((int)v48, 2u);
    if ( dword_544CFC >> byte_54512C >= v30
      && dword_544D00 >> byte_54512C >= v29
      && dword_544CFC >> byte_54512C <= v33
      && dword_544D00 >> byte_54512C <= v31 )
    {
      v34 = 1;
      Audio_PlayButtonSound(aMale);
      goto LABEL_34;
    }
  }
  Audio_PlayButtonSound(aMale_0);
  v34 = 0;
LABEL_34:
  Render_Pump();
  Debug_Log(0, v29, v31, (int)aUnsetrh08x_3);
  g_RenderHook = v52;
  Render_SetResourceHandle((int)&unk_51D4C0, v53);
  SpriteWidth = DLX_GetSpriteWidth((int)v48, 0);
  v39 = DLX_GetSpriteHeight((int)v48, 0);
  Render_FillRect((_DWORD *)dword_5202E0, 0, v54, v55, v55 + v39, v54 + SpriteWidth, v55, v54);
  Render_Present((int)g_RenderState);
  DLXSpriteSet_ReleaseAndClear((int *)&v48);
  return v34;
}
// 41C91A: variable 'v7' is possibly undefined
// 41C927: variable 'v8' is possibly undefined
// 41C959: variable 'v10' is possibly undefined
// 41CA4A: variable 'v13' is possibly undefined
// 41CACF: variable 'v14' is possibly undefined
// 41CB39: variable 'v18' is possibly undefined
// 41CCB4: variable 'v24' is possibly undefined
// 41CF9E: variable 'v35' is possibly undefined
// 41CFBD: variable 'v38' is possibly undefined
// 41CFDB: variable 'v40' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513A00: using guessed type char *off_513A00[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

static int g_BuildingNewOverrideActive;
static int g_BuildingNewOverrideRow;
static int g_BuildingNewOverrideColumn;

