/* Strategic units, stacks, movement, fatigue, morale, and path execution.
 * Original function-marker range: 0x0040F510..0x0041C8B0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (0040F510) --------------------------------------------------------
signed int  Unit_Create(a1, a2, tileRow, facing, tileColumn)
unit_type a1;
int a2;
int tileRow;
char facing;
int tileColumn;
{
  int stackScanCount; // esi
  int foundFreeStack; // edx
  int stackScanOffset; // eax
  int stackTypeWord; // ecx
  int stackIndex; // esi
  int v12; // ecx
  int stackPtr; // edi
  int tileRowBase; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx

  stackScanCount = 0;
  Debug_Log(tileRow, facing, a1, (int)aUnit_createDDD);
  foundFreeStack = 0;
  stackScanOffset = 0;
  do
  {
    stackTypeWord = *(__int16 *)(gameData + stackScanOffset + 147180);
    if ( stackTypeWord == -1 )
      foundFreeStack = 1;
    stackScanOffset += 725;
    ++stackScanCount;
  }
  while ( stackScanOffset < 362500 && !foundFreeStack );
  stackIndex = stackScanCount - 1;
  if ( foundFreeStack )
  {
    if ( UnitStack_IsIndexOnMap(stackIndex) )
      Debug_Log(v12, facing, a1, (int)aUnit_createErr);
    stackPtr = (int)UNIT_STACK(stackIndex);
    tileRowBase = 200 * tileRow + gameData;
    if ( *(unsigned __int16 *)(tileRowBase + 2 * tileColumn + 556374) == 0xFFFF )
    {
      if ( a1 == -1 || Map_GetUnitTileMoveCostOrZero(a1, a2, tileColumn, tileRow) )
      {
        UnitStack_ResetRecord(stackPtr, a1, a2);
        UNIT_STACK_TILE_ROW(stackPtr) = tileRow;
        UNIT_STACK_TILE_COLUMN(stackPtr) = tileColumn;
        UNIT_STACK_FACING(stackPtr) = facing;
        v16 = gameData;
        *(_WORD *)(TILE_INDEX(tileRow, tileColumn)) = stackIndex;
        UnitStack_UpdateVision(stackIndex);
        Rules_CreateArmyFact((__int16 *)stackPtr, stackIndex, v16, a2, a1);
        Debug_Log(v17, a2, a1, (int)aUnit_createOk0);
        return 1;
      }
      else
      {
        Debug_Log(v15, tileRow, a1, (int)aUnit_createE_2);
        return 0;
      }
    }
    else
    {
      Debug_Log(tileRowBase, facing, a1, (int)aUnit_createE_1);
      return 0;
    }
  }
  else
  {
    Debug_Log(stackTypeWord, facing, a1, (int)aUnit_createE_0);
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
int  Unit_Kill(int stackRecord, char killReason, DWORD a3, double a4)
{
  int row;
  int column;
  int slot_ordinal;
  _WORD *slot_type;

  Debug_Log(stackRecord, killReason, a3, (int)aUnit_kill0x08x);
  Unit_DebugDumpFormationSizes(stackRecord, a3);
  Rules_RetractArmyFact((_DWORD *)stackRecord, 0, stackRecord, a4);
  row = UNIT_STACK_TILE_ROW(stackRecord);
  column = UNIT_STACK_TILE_COLUMN(stackRecord);
  Diagnostics_TraceWorldMapActionEvent(
    "unit_kill",
    Diagnostics_UnitStackIndexFromRecord(stackRecord),
    row,
    column,
    Unit_GetSquadCount(stackRecord));
  *(_WORD *)(TILE_INDEX(row, column)) = -1;
  slot_ordinal = 1;
  slot_type = (_WORD *)UNIT_STACK_SLOT(stackRecord, 0);
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
int  UnitStack_GetVisionRadius(int stackPtr)
{
  int unitMetadataOffset; // edx
  __int16 *slotPtr; // eax
  int maxRadius; // ebx
  int i; // edx
  int slotType; // ecx
  int slotRadius; // ecx

  unitMetadataOffset = 88 * *(__int16 *)(stackPtr + 6);
  slotPtr = (__int16 *)(stackPtr + 37);
  maxRadius = (unsigned __int8)g_UnitTypeVisionRadius[unitMetadataOffset];
  for ( i = 1; i < 10; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    slotRadius = (unsigned __int8)g_UnitTypeVisionRadius[88 * slotType];
    if ( slotRadius > maxRadius )
      maxRadius = slotRadius;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  return maxRadius;
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
signed int  Facing_DirectionFromDelta8(int deltaRow, int deltaColumn)
{
  if ( deltaRow <= 0 )
  {
    if ( deltaRow < 0 )
    {
      if ( deltaColumn < 0 )
      {
        return 7;
      }
      else if ( deltaColumn )
      {
        return 5;
      }
      else
      {
        return 6;
      }
    }
    else if ( deltaColumn < 0 )
    {
      return 0;
    }
    else
    {
      return 4;
    }
  }
  else if ( deltaColumn < 0 )
  {
    return 1;
  }
  else if ( deltaColumn )
  {
    return 3;
  }
  else
  {
    return 2;
  }
}

//----- (0040FAD0) --------------------------------------------------------
int  Camera_CenterOnUnit(int stackIndex)
{
  int stackByteOffset; // eax
  int mapWidthTiles; // ebx
  int mapHeightTiles; // esi

  stackByteOffset = 725 * stackIndex;
  *(_DWORD *)(gameData + 140008) = *(__int16 *)(gameData + stackByteOffset + 147174) - 4;
  *(_DWORD *)(gameData + 140012) = *(__int16 *)(gameData + stackByteOffset + 147176) - 3;
  if ( *(int *)(gameData + 140008) < 0 )
    *(_DWORD *)(gameData + 140008) = 0;
  if ( *(int *)(gameData + 140012) < 0 )
    *(_DWORD *)(gameData + 140012) = 0;
  mapWidthTiles = *(_DWORD *)(gameData + 140000);
  if ( *(_DWORD *)(gameData + 140008) + 9 > mapWidthTiles )
    *(_DWORD *)(gameData + 140008) = mapWidthTiles - 9;
  mapHeightTiles = *(_DWORD *)(gameData + 140004);
  if ( *(_DWORD *)(gameData + 140012) + 7 > mapHeightTiles )
    *(_DWORD *)(gameData + 140012) = mapHeightTiles - 7;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;

//----- (0040FDB0) --------------------------------------------------------
int  UnitSlot_CalcActionPointsFromFatigue(__int16 *slotPtr)
{
  int unit_type; // eax
  int fatigueLevel; // ecx
  int result; // eax
  int v4; // ecx

  unit_type = *slotPtr;
  if ( unit_type < 0 || unit_type >= UNIT_TYPE_COUNT )
    return 0;
  fatigueLevel = *((char *)slotPtr + 10);
  result = (unsigned __int8)g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unit_type];
  if ( fatigueLevel >= 80 && fatigueLevel <= 89 )
    return (192 * result - (__CFSHL__((192 * result) >> 31, 8) + ((192 * result) >> 31 << 8))) >> 8;
  v4 = *((char *)slotPtr + 10);
  if ( v4 >= 90 && v4 <= 99 )
    return ((result << 7) - (__CFSHL__(result << 7 >> 31, 8) + (result << 7 >> 31 << 8))) >> 8;
  if ( *((_BYTE *)slotPtr + 10) == 100 )
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
  __int16 *stackPtr; // ebx
  __int16 *slotPtr; // eax
  int i; // edx
  int slotType; // ecx

  stackPtr = result;
  if ( result )
  {
    slotPtr = result + 3;
    for ( i = 0; i < 10; ++i )
    {
      slotType = *slotPtr;
      if ( slotType == -1 )
        break;
      slotPtr = (__int16 *)((char *)slotPtr + 31);
      *((_BYTE *)slotPtr - 23) = 0;
    }
    return (__int16 *)Rules_LinkArmyFact(stackPtr, i, slotType, a3, (char)stackPtr, a2);
  }
  return result;
}

//----- (0040FEF0) --------------------------------------------------------
signed int WorldMap_HandleViewportScrollKeys()
{
  int viewportXLeft; // edx
  int viewportXRight; // ecx
  int viewportYUp; // ebx
  int viewportYDown; // esi
  int v5; // ecx

  if ( Input_IsKeyPressed(203) )
  {
    viewportXLeft = *(_DWORD *)(gameData + 140008);
    if ( viewportXLeft > 0 )
    {
      *(_DWORD *)(gameData + 140008) = viewportXLeft - 1;
LABEL_4:
      WorldMap_RedrawViewport(1);
      g_WorldMapViewportScrolledFlag = 1;
      return 1;
    }
  }
  if ( Input_IsKeyPressed(205) && (viewportXRight = *(_DWORD *)(gameData + 140008), *(_DWORD *)(gameData + 140000) - 9 > viewportXRight) )
  {
    *(_DWORD *)(gameData + 140008) = viewportXRight + 1;
    WorldMap_RedrawViewport(1);
    g_WorldMapViewportScrolledFlag = 1;
    return 1;
  }
  else if ( Input_IsKeyPressed(200) && (viewportYUp = *(_DWORD *)(gameData + 140012), viewportYUp > 0) )
  {
    *(_DWORD *)(gameData + 140012) = viewportYUp - 1;
    WorldMap_RedrawViewport(1);
    g_WorldMapViewportScrolledFlag = v5;
    return v5;
  }
  else
  {
    if ( Input_IsKeyPressed(208) )
    {
      viewportYDown = *(_DWORD *)(gameData + 140012);
      if ( *(_DWORD *)(gameData + 140004) - 7 > viewportYDown )
      {
        *(_DWORD *)(gameData + 140012) = viewportYDown + 1;
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
signed int  UnitStack_GetMinCurrentActionPoints(intptr_t stackPtr)
{
  __int16 *slotPtr; // eax
  int slotIndex; // edx
  int minActionPoints; // ebx

  slotPtr = (__int16 *)(stackPtr + 37);
  slotIndex = 1;
  minActionPoints = *((unsigned __int8 *)slotPtr - 23);
  do
  {
    if ( *slotPtr == -1 )
      break;
    if ( minActionPoints > *((unsigned __int8 *)slotPtr + 8) )
      minActionPoints = *((unsigned __int8 *)slotPtr + 8);
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  while ( slotIndex < 10 );
  return minActionPoints;
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
signed int  UnitStack_HasPlagueFlag(int stackPtr)
{
  int slotIndex; // edx

  slotIndex = 0;
  while ( 1 )
  {
    if ( *(__int16 *)(stackPtr + 6) == -1 )
      return 0;
    if ( (*(_BYTE *)(stackPtr + 19) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00410130) --------------------------------------------------------
signed int  UnitStack_SpendActionPointsClamped(__int16 *stackPtr, int spendAmount, DWORD a3, double a4)
{
  __int16 *slotPtr; // eax
  int i; // ecx
  int slotType; // ebx
  char currentActionPoints; // bl

  slotPtr = stackPtr + 3;
  for ( i = 0; i < 10; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    if ( *((unsigned __int8 *)slotPtr + 8) < spendAmount )
      spendAmount = *((unsigned __int8 *)slotPtr + 8);
    currentActionPoints = *((_BYTE *)slotPtr + 8);
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    LOBYTE(slotType) = currentActionPoints - spendAmount;
    *((_BYTE *)slotPtr - 23) = slotType;
  }
  return Rules_LinkArmyFact(stackPtr, spendAmount, i, a4, slotType, a3);
}

//----- (00410170) --------------------------------------------------------
int  UnitStack_SpendActionPointsUnchecked(int stackPtr, char spendAmount)
{
  int slotPtr; // eax
  int slotIndex; // edx

  slotPtr = stackPtr + 6;
  slotIndex = 0;
  while ( slotIndex < 10 )
  {
    if ( *(__int16 *)slotPtr == -1 )
      break;
    *(_BYTE *)(slotPtr + 8) -= spendAmount;
    slotPtr += 31;
    ++slotIndex;
  }
  return slotPtr;
}

//----- (004101A0) --------------------------------------------------------
signed int  UnitStack_SubtractActionPointsFloorZero(__int16 *stackPtr, int subtractAmount, DWORD a3, double a4)
{
  __int16 *slotPtr; // eax
  int i; // edx
  int currentActionPoints; // ebx

  slotPtr = stackPtr + 3;
  for ( i = 0; i < 10; ++i )
  {
    currentActionPoints = *slotPtr;
    if ( currentActionPoints == -1 )
      break;
    currentActionPoints = *((unsigned __int8 *)slotPtr + 8);
    if ( currentActionPoints <= subtractAmount )
    {
      *((_BYTE *)slotPtr + 8) = 0;
    }
    else
    {
      LOBYTE(currentActionPoints) = currentActionPoints - subtractAmount;
      *((_BYTE *)slotPtr + 8) = currentActionPoints;
    }
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  return Rules_LinkArmyFact(stackPtr, i, subtractAmount, a4, currentActionPoints, a3);
}

//----- (004101E0) --------------------------------------------------------
signed int  UnitStack_SpendActionPointsByIndexClamped(int a1, int a2, DWORD a3, double a4)
{
  return UnitStack_SpendActionPointsClamped((__int16 *)(725 * a1 + gameData + 147174), a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00410260) --------------------------------------------------------
signed int  UnitStack_CanReachQueuedPathTileWithFogOverlay(__int16 *stackPtr, int a2)
{
  signed int minActionPoints; // esi
  int pathLength; // [esp+0h] [ebp-1A8h]
  int pathSteps[100]; // [esp+4h] [ebp-1A4h]
  int pathStep; // [esp+194h] [ebp-14h]
  int v10; // [esp+1A0h] [ebp-8h]

  v10 = a2;
  (void)v10;
  if ( Map_ClassifyFogOfWarOverlayForPlayer(*stackPtr, stackPtr[1], VIEWED_PLAYER_INDEX) )
    return 1;
  minActionPoints = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
  pathLength = *(_DWORD *)((char *)stackPtr + UNIT_STACK_PATH_OFFSET);
  qmemcpy(pathSteps, (char *)stackPtr + UNIT_STACK_PATH_OFFSET + 4, sizeof(pathSteps));
  do
  {
    if ( pathLength )
    {
      pathStep = pathSteps[--pathLength];
      if ( minActionPoints >= HIWORD(pathStep) )
        continue;
    }
    return 0;
  }
  while ( !Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)pathStep, BYTE1(pathStep), VIEWED_PLAYER_INDEX) );
  return 1;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00410330) --------------------------------------------------------
void  UnitStack_ExecuteQueuedPath(unsigned int stackIndexArg, int animateArg, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int v6; // ecx
  __int16 *stackPtr; // esi
  int pathLength; // ebx
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
  int savedCursorDescriptor; // [esp+74h] [ebp-58h]
  signed int v93; // [esp+78h] [ebp-54h]
  signed int v94; // [esp+7Ch] [ebp-50h]
  int *v95; // [esp+80h] [ebp-4Ch]
  int v96; // [esp+84h] [ebp-48h]
  signed int v97; // [esp+88h] [ebp-44h]
  int v98; // [esp+8Ch] [ebp-40h]
  int v99; // [esp+90h] [ebp-3Ch]
  int prevCumulativeCost; // [esp+94h] [ebp-38h]
  int animate; // [esp+98h] [ebp-34h]
  char *v102; // [esp+9Ch] [ebp-30h]
  char *v103; // [esp+A0h] [ebp-2Ch]
  int *pathBuffer; // [esp+A4h] [ebp-28h]
  int v105; // [esp+A8h] [ebp-24h]
  int v106; // [esp+ACh] [ebp-20h]
  unsigned int stackIndex; // [esp+B0h] [ebp-1Ch]
  int v108; // [esp+B4h] [ebp-18h]
  BOOL followInViewport; // [esp+B8h] [ebp-14h]

  stackIndex = stackIndexArg;
  animate = animateArg;
  Debug_Log(stackIndexArg, a3, a4, (int)aUnit_moveDD);
  Render_DrawSprite_v3(stackIndex, a4);
  stackPtr = (__int16 *)UNIT_STACK(stackIndex);
  pathLength = *((_DWORD *)stackPtr + 79);
  pathBuffer = (int *)(stackPtr + 158);
  if ( pathLength )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    {
      v105 = pathBuffer[pathLength];
      Diagnostics_TraceWorldMapActionEvent(
        "unit_move_execute_path_next",
        stackIndex,
        (unsigned __int8)v105,
        BYTE1(v105),
        HIWORD(v105));
      v105 = pathBuffer[1];
      Diagnostics_TraceWorldMapActionEvent(
        "unit_move_execute_path_first",
        stackIndex,
        (unsigned __int8)v105,
        BYTE1(v105),
        HIWORD(v105));
    }
    v9 = (signed int)pathBuffer;
    v96 = 0;
    v89 = pathBuffer[1];
    v94 = *stackPtr;
    v10 = *(_DWORD *)(gameData + 140008);
    v93 = stackPtr[1];
    followInViewport = 1;
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
          followInViewport = BYTE1(v89) >= v9 + 7;
        }
      }
    }
    if ( animate )
    {
      if ( !UnitStack_CanReachQueuedPathTileWithFogOverlay(stackPtr, animate) )
        animate = 0;
    }
    else
    {
      followInViewport = 0;
    }
    g_ActiveUnitAnimSpriteSet = 0;
    if ( animate && !*(_DWORD *)(gameData + 147159) )
    {
      v20 = *((_BYTE *)stackPtr + 4);
      Unit_BuildGoSpriteFilePath(v87, *((_BYTE *)stackPtr + 6), v20);
      v22 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
      if ( v22 )
        v22 = DLXSpriteSet_Load(v22, v87);
      g_ActiveUnitAnimSpriteSet = (int)v22;
      g_UnitAnimFrameIndex = 0;
      g_ActiveUnitMoveTileIndex = stackIndex;
    }
    g_UnitMoveAnimOffsetY = 0;
    g_UnitMoveAnimOffsetX = 0;
    if ( animate )
      WorldMap_RedrawViewport(1);
    savedCursorDescriptor = g_ActiveCursorDescriptorPtr;
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    v11 = stackIndex;
    *((_BYTE *)stackPtr + 720) = 0;
    UnitStack_RevealHiddenEnemiesAndAttackAdjacent(v11, a5);
    Trap_TriggerAtStackTile(stackIndex, a4, a5);
    v106 = 1;
    v13 = *pathBuffer;
    prevCumulativeCost = 0;
    if ( v13 )
    {
      v91 = 725 * stackIndex;
      v95 = (int *)(stackPtr + 158);
      while ( 1 )
      {
        if ( v96 )
          goto LABEL_21;
        v105 = pathBuffer[*pathBuffer];
        v23 = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
        v24 = HIWORD(v105) - prevCumulativeCost;
        if ( v23 - v24 < 0 )
        {
          Diagnostics_TraceWorldMapActionEvent("unit_move_stop_ap", stackIndex, v23, v24, *pathBuffer);
          goto LABEL_21;
        }
        v25 = *(unsigned __int16 *)(TILE_INDEX((unsigned __int8)v105, BYTE1(v105))) - 0x8000;
        if ( v25 > 0x64
          || (v26 = UNIT_RECORD(v25), (unsigned int)*(char *)(v26 + 4) >= 4)
          || *(__int16 *)(v26 + 16) == -1 )
        {
          UnitStack_SpendActionPointsUnchecked((int)stackPtr, BYTE2(v105) - prevCumulativeCost);
          UnitStack_SetSpentTurnFlag((int)stackPtr);
        }
        v27 = *pathBuffer - 1;
        v28 = pathBuffer;
        *pathBuffer = v27;
        v105 = v28[v27 + 1];
        prevCumulativeCost = HIWORD(v105);
        if ( followInViewport )
        {
          v29 = *(_DWORD *)(gameData + 140008);
          if ( (unsigned __int8)v105 < v29
            || (unsigned __int8)v105 >= v29 + 9
            || (v30 = *(_DWORD *)(gameData + 140012), BYTE1(v105) < v30)
            || BYTE1(v105) >= v30 + 7 )
          {
            if ( Map_ClassifyFogOfWarOverlayForPlayer((unsigned __int8)v105, BYTE1(v105), VIEWED_PLAYER_INDEX) )
              Camera_CenterOnUnit(stackIndex);
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
          Temple_UnitGetInto(stackIndex, v35, v34, v34, a5);
          *v95 = 0;
          goto LABEL_21;
        }
        LOBYTE(v13) = v34;
        v36 = UnitStack_GetTileMoveCostOrZero(stackPtr, v35, 0, v34);
        if ( !v36 && UnitStack_HasBuilder(stackIndex) && Map_GetBridgeCrossingCostOrZero(v35, v34) )
        {
          if ( Diagnostics_IsWorldMapClickTraceEnabled() )
            Diagnostics_TraceWorldMapActionEvent("unit_move_bridge_execute_allow", stackIndex, v35, v34, HIWORD(v105));
          v36 = 1;
        }
        if ( !v36 )
        {
          if ( *(_DWORD *)(1423 * *((unsigned __int8 *)stackPtr + 4) + gameData + 140051) || !Map_GetBridgeCrossingCostOrZero(v35, v34) )
          {
            *((_DWORD *)stackPtr + 79) = 0;
          }
          else
          {
            v59 = *v95;
            if ( *v95 < 100 )
            {
              v60 = v95;
              *v95 = v59 + 1;
              v60[v59 + 1] = v105;
              UnitStack_ClearReadyFlags((int)stackPtr);
              goto LABEL_21;
            }
          }
          UnitStack_ClearReadyFlags((int)stackPtr);
          goto LABEL_21;
        }
        *((_BYTE *)stackPtr + 5) = Facing_DirectionFromDelta8(v35 - *stackPtr, v34 - stackPtr[1]);
        v38 = *((unsigned __int8 *)stackPtr + 5);
        v108 = v38;
        if ( v38 == 6 || v38 == 2 )
          g_UnitMoveAnimOffsetY = 0;
        if ( !v108 || v108 == 4 )
          g_UnitMoveAnimOffsetX = 0;
        if ( !*(_DWORD *)(gameData + 147159) )
        {
          if ( animate )
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
                v67 = g_UnitMoveAnimOffsetX;
                if ( g_UnitMoveAnimOffsetX <= 0 )
                  v67 = -g_UnitMoveAnimOffsetX;
                v68 = v67;
                v69 = v64 <= 0 ? -v64 : v64;
                if ( v68 >= v69 )
                {
                  v70 = g_UnitMoveAnimOffsetY;
                  if ( g_UnitMoveAnimOffsetY <= 0 )
                    v70 = -g_UnitMoveAnimOffsetY;
                  v71 = v70;
                  v72 = v65 <= 0 ? -v65 : v65;
                  if ( v71 >= v72 )
                    break;
                }
                DD_Pump((int)g_RenderState, v66);
                if ( WorldMap_HandleViewportScrollKeys() )
                {
                  followInViewport = 0;
                }
                else
                {
                  WorldMap_RedrawFrame(v66);
                  v73 = 88 * stackPtr[3];
                  LOBYTE(v73) = g_UnitTypeMoveAnimationTickIntervalMs[v73];
                  v75 = Time_Now(v74, v73);
                  if ( v75 - v66 >= (unsigned int)v76 )
                  {
                    v77 = g_WorldMapUnitWalkStepCounter++;
                    if ( (v77 & 1) != 0 )
                    {
                      g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
                      Audio_PlayWorldMapUnitMoveSound(*stackPtr, stackPtr[1], g_UnitAnimFrameIndex, stackPtr[3]);
                    }
                    if ( v106 )
                    {
                      v78 = -1;
                      do
                      {
                        v79 = -1;
                        do
                        {
                          v80 = v79 + stackPtr[1];
                          ++v79;
                          WorldMap_RedrawTileIfVisible(v78 + *stackPtr, v80);
                        }
                        while ( v79 <= 1 );
                        ++v78;
                      }
                      while ( v78 <= 1 );
                    }
                    else if ( Unit_GetSpriteVerticalOffsetPx(stackIndex) )
                    {
                      Map_RedrawUnitNeighborhoodByIndex(stackIndex);
                    }
                    else
                    {
                      v82 = v108;
                      WorldMap_RedrawTileIfVisible(*stackPtr, stackPtr[1]);
                      if ( v82 == 4 || v82 == 5 || v82 == 3 || v82 == 6 || v82 == 2 )
                        WorldMap_RedrawTileIfVisible(*stackPtr, stackPtr[1] + 1);
                      if ( !v108 || v108 == 7 || v108 == 1 )
                        WorldMap_RedrawTileIfVisible(*stackPtr, stackPtr[1] - 1);
                      if ( v108 == 2 || v108 == 3 || v108 == 1 || v108 == 4 )
                        WorldMap_RedrawTileIfVisible(*stackPtr + 1, stackPtr[1]);
                      if ( v108 == 6 || v108 == 5 || v108 == 7 )
                        WorldMap_RedrawTileIfVisible(*stackPtr - 1, stackPtr[1]);
                      v78 = v108;
                      switch ( v108 )
                      {
                        case 3:
                          WorldMap_RedrawTileIfVisible(*stackPtr + 1, stackPtr[1] + 1);
                          break;
                        case 1:
                          WorldMap_RedrawTileIfVisible(*stackPtr + 1, stackPtr[1] - 1);
                          break;
                        case 5:
                          WorldMap_RedrawTileIfVisible(*stackPtr - 1, stackPtr[1] + 1);
                          break;
                        case 7:
                          WorldMap_RedrawTileIfVisible(*stackPtr - 1, stackPtr[1] - 1);
                          break;
                      }
                    }
                    g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * stackPtr[3]]
                                  * Map_NeighborDX[2 * *((unsigned __int8 *)stackPtr + 5)];
                    v81 = *((unsigned __int8 *)stackPtr + 5);
                    g_UnitMoveAnimOffsetY += Map_NeighborDY[2 * v81] * (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * stackPtr[3]];
                    v66 = Time_Now(v78, v81);
                    v106 = 0;
                  }
                }
              }
            }
          }
        }
        g_UnitMoveAnimOffsetX %= 64;
        v90 = (unsigned __int8)v105;
        v103 = (char *)(unsigned __int8)v105;
        v98 = animate;
        v39 = BYTE1(v105);
        v40 = (__int16 *)(gameData + 147174 + v91);
        g_UnitMoveAnimOffsetY %= 64;
        v41 = BYTE1(v105) - v40[1];
        v88 = *v40;
        *((_BYTE *)v40 + 5) = Facing_DirectionFromDelta8((unsigned __int8)v105 - v88, v41);
        v42 = 200 * v90;
        *(_WORD *)(2 * v40[1] + gameData + 200 * *v40 + 556374) = -1;
        v43 = stackIndex;
        v13 = v39;
        *(_WORD *)(v42 + gameData + 2 * v39 + 556374) = stackIndex;
        *v40 = (__int16)v103;
        v40[1] = v39;
        if ( Trap_TriggerAtStackTile(v43, a4, a5) )
          UnitStack_ClearRemainingActionPoints(v40, v39, a5);
        v45 = stackIndex;
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
                g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
                v53 = v97;
                MiniMap_RedrawTileRect((int)v102, v52, v45, (int)v47);
                if ( v53 )
                  WorldMap_RedrawViewport(1);
              }
            }
          }
        }
        if ( animate && *(_DWORD *)(gameData + 147159) )
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
        if ( stackIndex <= 0x1F4 && (unsigned int)*(__int16 *)(v91 + gameData + 147174 + 6) <= 0x28 )
        {
          v83 = *pathBuffer;
          v106 = 1;
          if ( v83 )
            continue;
        }
        goto LABEL_21;
      }
      if ( *(_BYTE *)(v99 + gameData + 509676) != *((_BYTE *)stackPtr + 4) || *pathBuffer )
      {
        *((_DWORD *)stackPtr + 79) = 0;
        UnitStack_ClearReadyFlags((int)stackPtr);
      }
      else
      {
        Audio_StopUnitMoveSound();
        if ( Building_CanAcceptUnitStack(stackIndex, *(unsigned __int16 *)(v13 + gameData + v31 + 556374) - 0x8000) )
          Building_UnitGetInto(stackIndex, *(unsigned __int16 *)(v13 + gameData + v31 + 556374) - 0x8000, v13, v31, a5);
        else
          *(_DWORD *)(gameData + 725 * stackIndex + 147490) = 0;
      }
    }
LABEL_21:
    v14 = gameData + 725 * stackIndex;
    v15 = v94;
    v16 = *(__int16 *)(v14 + 147174);
    if ( v16 != v94 || (v16 = v93, *(__int16 *)(v14 + 147176) != v93) )
      Rules_LinkArmyFact(stackPtr, v16, gameData, a5, v13, v94);
    Audio_StopUnitMoveSound();
    g_UnitMoveAnimOffsetY = 0;
    g_UnitMoveAnimOffsetX = 0;
    v18 = stackPtr + 158;
    v19 = *((_DWORD *)stackPtr + 79);
    if ( v19 )
    {
      v84 = v19 - 1;
      for ( i = prevCumulativeCost; v84 >= 0; v18[v86 + 1] = v89 )
      {
        v86 = *v18 - 1 - v84;
        v89 = v18[v86 + 1];
        HIWORD(v89) -= i;
        --v84;
      }
    }
    else
    {
      UnitStack_ClearReadyFlags((int)stackPtr);
    }
    if ( g_ActiveUnitAnimSpriteSet )
      DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
    g_ActiveUnitMoveTileIndex = -1;
    if ( animate )
    {
      UnitStackSelection_RefreshForSelectedStack(v15);
      WorldMap_RedrawViewport(1);
    }
    RenderState_SelectCursorDescriptor((int)g_RenderState, savedCursorDescriptor);
    WorldMap_SyncSelectionForHumanPlayer(v15);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_move_after_path_state",
      stackIndex,
      *stackPtr,
      stackPtr[1],
      *((_DWORD *)stackPtr + 79));
    Diagnostics_TraceWorldMapActionEvent(
      "unit_move_after_path_ap",
      stackIndex,
      UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr),
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
int  UnitStats_CalcEffectiveMeleeAttack(char *slotPtr, int forceMaxLevel)
{
  int level; // ebx

  if ( forceMaxLevel )
    level = 3;
  else
    level = UNIT_SLOT_STATUS_LEVEL(slotPtr);
  return (level + (unsigned __int8)g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * *(__int16 *)slotPtr] + slotPtr[11] / 5) * slotPtr[9] / 100;
}

//----- (00411180) --------------------------------------------------------
int  UnitStats_GetMeleeIconIndex(__int16 *a1)
{
  return UNIT_SLOT_STATUS_LEVEL(a1) + (unsigned __int8)g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * *a1] + *((char *)a1 + 11) / 5;
}

//----- (004111C0) --------------------------------------------------------
int  UnitStats_CalcEffectiveDefensePower(char *slotPtr, int forceMaxLevel)
{
  int baseDefense; // ebx
  int level; // esi

  baseDefense = (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * *(__int16 *)slotPtr];
  if ( (slotPtr[22] & 1) != 0 )
    baseDefense = (320 * baseDefense - (__CFSHL__((320 * baseDefense) >> 31, 8) + ((320 * baseDefense) >> 31 << 8))) >> 8;
  if ( forceMaxLevel )
    level = 3;
  else
    level = UNIT_SLOT_STATUS_LEVEL(slotPtr);
  return (level + baseDefense + slotPtr[11] / 5) * slotPtr[9] / 100;
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
int  UnitStats_CalcEffectiveWallAttack(char *slotPtr, int forceMaxLevel)
{
  int level; // ebx

  if ( forceMaxLevel )
    level = 3;
  else
    level = UNIT_SLOT_STATUS_LEVEL(slotPtr);
  return (level + (unsigned __int8)g_UnitTypeBaseWallAttack[UNIT_TYPE_METADATA_STRIDE * *(__int16 *)slotPtr] + slotPtr[11] / 5) * slotPtr[9] / 100;
}

//----- (00411350) --------------------------------------------------------
signed int  Debug_LogUnitSquadDetails(int stackPtr, DWORD a2)
{
  signed int result; // eax
  signed int squadIndex; // ecx

  Debug_Log(0, stackPtr, a2, (int)aUnitD0x08x);
  squadIndex = 0;
  for ( result = Unit_GetSquadCount(stackPtr); squadIndex < result; result = Unit_GetSquadCount(stackPtr) )
  {
    Debug_Log(squadIndex + 1, stackPtr, a2, (int)a15sPl1dP);
    ++squadIndex;
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
  int stackIndex; // ecx
  int stackPtr; // edx
  signed int result; // eax

  Debug_Log(a1, a2, a3, (int)aLogallunits);
  stackIndex = 0;
  stackPtr = gameData + 147174;
  do
  {
    result = *(__int16 *)(stackPtr + 6);
    if ( result != -1 )
      result = Unit_DebugDumpFormationSizes(stackPtr, a3);
    ++stackIndex;
    stackPtr += 725;
  }
  while ( stackIndex < 500 );
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
_WORD * UnitSlots_RemoveGaps(_WORD *result, int slotCount)
{
  int lastIndex; // ebx
  int keptCount; // ebp
  int shiftIndex; // edx
  void *shiftDst; // edi
  int i; // [esp+0h] [ebp-20h]
  _WORD *slotArrayBase; // [esp+4h] [ebp-1Ch]
  __int16 *slotCursor; // [esp+8h] [ebp-18h]

  slotArrayBase = result;
  lastIndex = slotCount - 1;
  keptCount = 0;
  slotCursor = result;
  for ( i = 0; lastIndex > i; ++i )
  {
    if ( *slotCursor == -1 )
    {
      shiftIndex = keptCount;
      result = (_WORD *)((char *)slotArrayBase + 31 * keptCount);
      while ( shiftIndex < lastIndex )
      {
        shiftDst = result;
        ++shiftIndex;
        result = (_WORD *)((char *)result + 31);
        qmemcpy(shiftDst, result, 0x1Fu);
      }
      *result = -1;
    }
    else
    {
      result = (__int16 *)((char *)slotCursor + 31);
      ++keptCount;
      slotCursor = (__int16 *)((char *)slotCursor + 31);
    }
  }
  return result;
}

//----- (004115E0) --------------------------------------------------------
void  Unit_CheckLowMorale(_BYTE *stackPtr, double a2)
{
  int anyDisbanded; // esi
  __int16 *slotPtr; // ecx
  int slotIndex; // ebx
  int wasLowMorale; // eax
  int disbandRollMax; // eax
  char slotFlags; // dh
  int stackRow; // ebx
  int disbandedFlag; // ebx
  _BYTE v15[725]; // [esp+0h] [ebp-300h] BYREF
  int v16[3]; // [esp+2D8h] [ebp-28h]
  int v17[7]; // [esp+2E4h] [ebp-1Ch] BYREF

  qmemcpy(v15, stackPtr, 0x2D5u);
  v17[0] = 0;
  anyDisbanded = 0;
  slotPtr = (__int16 *)&v15[6];
  slotIndex = 0;
  do
  {
    if ( *slotPtr == -1 )
      break;
    if ( !*((_BYTE *)slotPtr + 11) )
    {
      wasLowMorale = (*((_BYTE *)slotPtr + 13) & UNIT_SLOT_FLAG_LOW_MORALE) != 0;
      *((_BYTE *)slotPtr + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      disbandRollMax = wasLowMorale ? 200 : 100;
      if ( Rng_RandRange(0, disbandRollMax) < 0x32 )
      {
        if ( Rng_RandRange(0, 100) >= 0x32 )
        {
          anyDisbanded = 1;
          Debug_Log(0, slotIndex, (DWORD)stackPtr, (int)aUnit_checklo_0);
          *slotPtr = -1;
          v17[0] = 1;
        }
        else
        {
          Debug_Log(0, slotIndex, (DWORD)stackPtr, (int)aUnit_checklowm);
          slotFlags = *((_BYTE *)slotPtr + 13);
          *((_BYTE *)slotPtr + 8) = 0;
          *((_BYTE *)slotPtr + 13) = slotFlags | UNIT_SLOT_FLAG_LOW_MORALE;
        }
      }
    }
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  while ( slotIndex < 10 );
  if ( anyDisbanded && *(_DWORD *)(gameData + 1423 * (unsigned __int8)stackPtr[4] + 140051) )
  {
    stackRow = *(__int16 *)stackPtr;
    UI_CenterWorldMapViewportOnRectIfFit(stackRow, *((__int16 *)stackPtr + 1), *((__int16 *)stackPtr + 1) - 5, stackRow);
    v16[0] = (int)g_Text_UnitDisbandedLowMoraleMessages[0];
    v16[1] = (int)g_Text_UnitDisbandedLowMoraleMessages[1];
    v16[2] = (int)g_Text_UnitDisbandedLowMoraleMessages[2];
    UI_ShowInfoWindow(v16[(unsigned __int8)g_LanguageIndex], 0, 0, (DWORD)stackPtr, (int)v17, (int)&g_Text_UnitDisbandedLowMoraleMessages[3]);
    UI_StartWorldMapUnitAttentionFlash(
      *(unsigned __int16 *)(gameData + 200 * *(__int16 *)stackPtr + 2 * *((__int16 *)stackPtr + 1) + 556374),
      *((__int16 *)stackPtr + 1),
      *(__int16 *)stackPtr);
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
    Rules_LinkArmyFact((__int16 *)stackPtr, 0, 0, a2, 0, (DWORD)stackPtr);
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
signed int  UnitStack_ApplyPlagueAttritionToPeasantCargo(__int16 *stackPtr, DWORD a2, double a3)
{
  __int16 *slotPtr; // ecx
  int anyRemoved; // esi
  int i; // ebx
  signed int result; // eax
  char attritionLoss; // al
  char newQuantity; // dl
  int v10; // edx
  int v11; // ecx

  slotPtr = stackPtr + 3;
  anyRemoved = 0;
  for ( i = 0; i < 10; ++i )
  {
    result = *slotPtr;
    if ( result == -1 )
      break;
    if ( result == UNIT_TYPE_PEASANT_CARGO && (*((_BYTE *)slotPtr + 13) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
    {
      attritionLoss = Rng_RandRange(15, 25);
      newQuantity = *((_BYTE *)slotPtr + 9) - attritionLoss;
      result = newQuantity;
      *((_BYTE *)slotPtr + 9) = newQuantity;
      if ( newQuantity <= 0 )
      {
        anyRemoved = 1;
        *slotPtr = -1;
      }
    }
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  if ( anyRemoved )
  {
    Unit_CompactSquad(stackPtr, (int)slotPtr, a3);
    Rules_LinkArmyFinalize(stackPtr, a3);
    if ( stackPtr[3] != -1 )
      Rules_LinkArmyFact(stackPtr, v10, v11, a3, i, a2);
    return Rules_SyncArmyFactStrength(stackPtr, v10, v11, i, a2, a3);
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
  int stackPtr; // esi
  int slotIndex; // ebx
  int slotCursor; // edx
  int slotType; // ecx
  char actionPoints; // al
  unsigned int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int i; // [esp+0h] [ebp-20h]
  unsigned int stackIndex; // [esp+4h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)aUnit_newturn);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
  stackIndex = 0;
  for ( i = 0; ; i += 725 )
  {
    if ( *(__int16 *)(gameData + i + 147180) == -1 || *(unsigned __int8 *)(gameData + i + 147178) != g_CurrentPlayerIndex )
      goto LABEL_16;
    stackPtr = gameData + 147174 + i;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_stack",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      *(_DWORD *)(stackPtr + 316));
    UnitStack_AdjustFatigueByPredicate((__int16 *)stackPtr, -20, UnitSlot_CanRecoverFatigue, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_recover_fatigue",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      *(_DWORD *)(stackPtr + 316));
    if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(stackPtr + 4) + 140051) )
    {
      UnitStack_AdjustFatigueByPredicate((__int16 *)stackPtr, 10, UnitSlot_ShouldGainFatigueFromLowActionPoints, 0xFFFFFFFF, a4);
      UnitStack_AdjustMoraleByPredicate((__int16 *)stackPtr, -1, UnitSlot_HasSevereFatigue, 0xFFFFFFFF, a4);
    }
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_human_fatigue",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      *(_DWORD *)(stackPtr + 316));
    UnitStack_ClearSpentTurnFlag(stackPtr);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_clear_spent",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      *(_DWORD *)(stackPtr + 316));
    slotIndex = 0;
    slotCursor = stackPtr;
    do
    {
      slotType = *(__int16 *)(slotCursor + 6);
      if ( slotType == -1 )
        break;
      if ( slotType < 0 || slotType >= UNIT_TYPE_COUNT )
      {
        *(_WORD *)(slotCursor + 6) = -1;
        break;
      }
      slotCursor += 31;
      actionPoints = UnitSlot_CalcActionPointsFromFatigue((__int16 *)(stackPtr + 6 + 31 * slotIndex++));
      *(_BYTE *)(slotCursor - 17) = actionPoints;
    }
    while ( slotIndex < 10 );
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ap",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      slotIndex);
    Rules_LinkArmyFact((__int16 *)stackPtr, slotCursor, slotType, a4, slotIndex, 0xFFFFFFFF);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_rules_fact",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      slotIndex);
    Unit_CheckLowMorale((_BYTE *)stackPtr, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_low_morale",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      slotIndex);
    UnitStack_ApplyPlagueAttritionToPeasantCargo((__int16 *)stackPtr, 0xFFFFFFFF, a4);
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_plague",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      slotIndex);
    if ( !UnitStack_HasReadyUnits(stackPtr) )
      goto LABEL_16;
    Diagnostics_TraceWorldMapActionEvent(
      "unit_new_turn_after_ready_check",
      (int)stackIndex,
      *(__int16 *)stackPtr,
      *(__int16 *)(stackPtr + 2),
      slotIndex);
    v9 = *(unsigned __int16 *)(gameData
                             + 200 * (unsigned __int8)*(_DWORD *)(stackPtr + 320)
                             + 2 * (unsigned __int8)BYTE1(*(_DWORD *)(stackPtr + 320))
                             + 556374)
       - 0x8000;
    if ( v9 <= 0x64 )
    {
      slotIndex = 467 * v9;
      v10 = UNIT_RECORD(v9);
      if ( (unsigned int)*(char *)(v10 + 4) < 4
        && *(__int16 *)(v10 + 16) != -1
        && *(_BYTE *)(slotIndex + gameData + 509676) != *(_BYTE *)(stackPtr + 4) )
      {
        break;
      }
    }
    if ( *(_DWORD *)(stackPtr + 316) )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_before_path",
        (int)stackIndex,
        *(__int16 *)stackPtr,
        *(__int16 *)(stackPtr + 2),
        *(_DWORD *)(stackPtr + 316));
      UnitStack_ExecuteQueuedPath(stackIndex, 0, slotIndex, 0xFFFFFFFF, a4);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_new_turn_after_path",
        (int)stackIndex,
        *(__int16 *)stackPtr,
        *(__int16 *)(stackPtr + 2),
        *(_DWORD *)(stackPtr + 316));
    }
    else
      UnitStack_ClearReadyFlags(stackPtr);
LABEL_16:
    v11 = i + 725;
    slotIndex = stackIndex + 1;
    stackIndex = slotIndex;
    if ( slotIndex >= 500 )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, (unsigned __int8)a2);
      return LogAllUnits(v11, slotIndex, 0xFFFFFFFF);
    }
  }
  UnitStack_ClearReadyFlags(stackPtr);
  Diagnostics_TraceWorldMapActionEvent("unit_new_turn_done_enemy_contact", (int)stackIndex, *(__int16 *)stackPtr, *(__int16 *)(stackPtr + 2), slotIndex);
  return LogAllUnits(v11, slotIndex, 0xFFFFFFFF);
}
// 4119FD: simplified comparisons for 'edx.4': <0 || >=65 became >=65u
// 411A18: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 41194F: variable 'a4' is possibly undefined
// 4119A2: variable 'v7' is possibly undefined
// 411A67: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00411AB0) --------------------------------------------------------
signed int  UnitStack_HasBuilder(int stackIndex)
{
  __int16 *slotPtr; // edx
  int slotIndex; // eax
  int slotType; // ecx

  slotPtr = (__int16 *)(725 * stackIndex + gameData + 147174 + 6);
  slotIndex = 0;
  while ( 1 )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_BUILDER )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00411B30) --------------------------------------------------------
__int16  Map_RedrawUnitFootprintByIndex(int stackIndex)
{
  __int16 *unit_stack; // ecx
  int result; // eax
  int unit_type; // eax
  int unit_metadata_offset; // eax
  int x; // eax
  int y; // edx

  unit_stack = (__int16 *)(gameData + 147174 + 725 * stackIndex);
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
int  Map_RedrawUnitNeighborhoodByIndex(int stackIndex)
{
  int result; // eax
  __int16 *unit_stack; // ecx
  int x; // eax
  int y; // edx

  unit_stack = (__int16 *)(725 * stackIndex + gameData + 147174);
  x = unit_stack[0];
  y = unit_stack[1];
  result = WorldMap_RedrawTileIfVisible(x, y);
  result = Unit_GetSpriteVerticalOffsetPx(stackIndex);
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
  int stackIndex; // ecx
  int stackPtr; // edx
  int unitType; // eax
  int metadataOffset; // eax
  unsigned int nextAnimTick; // ebx
  int now; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx

  stackIndex = 0;
  stackPtr = gameData + 147174;
  do
  {
    unitType = *(__int16 *)(stackPtr + 6);
    if ( unitType != -1 )
    {
      metadataOffset = 88 * unitType;
      if ( (g_UnitTypeHasIdleAnimationFlags[metadataOffset] & 1) != 0 )
      {
        nextAnimTick = (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[metadataOffset] + *(_DWORD *)(stackPtr + 24);
        if ( nextAnimTick < Time_Now(stackIndex, stackPtr) )
        {
          now = Time_Now(stackIndex, stackPtr);
          *(_DWORD *)(stackPtr + 24) = now;
          LOBYTE(now) = ((*(_BYTE *)(stackPtr + 23) & 7) + 1) & 7;
          BYTE1(now) = *(_BYTE *)(stackPtr + 23) & 0xF8;
          *(_BYTE *)(stackPtr + 23) = BYTE1(now);
          BYTE1(now) |= now;
          *(_BYTE *)(stackPtr + 23) = BYTE1(now);
          *(_BYTE *)(stackPtr + 23) = BYTE1(now) & 0xF8;
          *(_BYTE *)(stackPtr + 23) = BYTE1(now);
          Map_RedrawUnitFootprintByIndex(stackIndex);
        }
      }
    }
    ++stackIndex;
    stackPtr += 725;
  }
  while ( stackIndex < 500 );
  UI_UpdateWorldMapUnitAttentionFlash();
  UI_UpdateUnitBlinkFlash(0, 0);
}
// 5202E4: using guessed type int gameData;

//----- (00411E20) --------------------------------------------------------
int  Unit_GetSpriteVerticalOffsetPx(int stackIndex)
{
  return (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(gameData + 725 * stackIndex + 147180)];
}
// 5202E4: using guessed type int gameData;

//----- (00411E60) --------------------------------------------------------
signed int  Unit_AttemptNeighborMove(int stackIndex)
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

  stack_offset = UNIT_STACK_STRIDE * stackIndex;
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
                      stackIndex,
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
BOOL  UnitStack_CanExecuteQueuedPathNow(int stackIndex)
{
  int stackPtr; // eax
  int pathLength; // edx
  int pathBufferPtr; // eax
  BOOL result; // eax
  unsigned __int16 lastStepActionPoints; // si

  stackPtr = gameData + 147174 + 725 * stackIndex;
  pathLength = *(_DWORD *)(stackPtr + 316);
  pathBufferPtr = stackPtr + 316;
  result = 0;
  if ( pathLength )
  {
    lastStepActionPoints = HIWORD(*(_DWORD *)(pathBufferPtr + 4 * (pathLength - 1) + 4));
    if ( UnitStack_GetMinCurrentActionPoints(gameData + 147174 + 725 * stackIndex) >= lastStepActionPoints )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00412000) --------------------------------------------------------
void * UnitSlots_ExtractSpecialEntries(char *slotArray, int slotCount, char *extractedOut)
{
  int slotIndex; // edx
  int slotType; // eax
  int shiftIndex; // ebx
  _WORD *shiftCursor; // eax
  void *result; // eax
  int remainingCount; // [esp+8h] [ebp-14h]

  remainingCount = slotCount;
  slotIndex = 0;
  while ( slotIndex < remainingCount )
  {
    slotType = *(__int16 *)slotArray;
    if ( slotType == -1 )
      break;
    if ( slotType == UNIT_TYPE_GOLD_CARGO
      || slotType == UNIT_TYPE_PEASANT_CARGO
      || slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      shiftIndex = 0;
      qmemcpy(extractedOut, slotArray, 0x1Fu);
      extractedOut += 31;
      shiftCursor = slotArray;
      if ( remainingCount - slotIndex - 1 > 0 )
      {
        do
        {
          qmemcpy(shiftCursor, (char *)shiftCursor + 31, 0x1Fu);
          ++shiftIndex;
          shiftCursor = (_WORD *)((char *)shiftCursor + 31);
        }
        while ( shiftIndex < remainingCount - slotIndex - 1 );
      }
      *shiftCursor = -1;
      --remainingCount;
    }
    else
    {
      slotArray += 31;
      ++slotIndex;
    }
  }
  result = extractedOut;
  *(_WORD *)extractedOut = -1;
  return result;
}

void * UnitSlots_ExtractSpecialEntriesForBuildingAttack(char *a1, int a2, char *a3)
{
  return UnitSlots_ExtractSpecialEntries(a1, a2, a3);
}

//----- (004120B0) --------------------------------------------------------
int  UnitSlots_AppendEntries(char *destSlots, char *srcSlots)
{
  char *srcStart; // esi
  int srcCount; // ecx
  char *destAppendPtr; // edi
  int result; // eax

  srcStart = srcSlots;
  while ( *(__int16 *)destSlots != -1 )
    destSlots += 31;
  srcCount = 0;
  while ( *(__int16 *)srcSlots != -1 )
  {
    srcSlots += 31;
    ++srcCount;
  }
  destAppendPtr = destSlots;
  result = 31 * srcCount;
  qmemcpy(destAppendPtr, srcStart, 31 * srcCount);
  return result;
}

int  UnitSlots_AppendEntriesForBuildingAttack(char *a1, char *a2)
{
  return UnitSlots_AppendEntries(a1, a2);
}

//----- (00412100) --------------------------------------------------------
signed int  UnitStack_HasNormalCombatUnits(intptr_t stackPtr)
{
  signed int result; // eax
  intptr_t slot_record; // edx
  signed int squad_count; // esi
  signed int has_normal_unit; // ebx
  signed int slot_index; // ecx
  int unit_type; // eax

  if ( *(__int16 *)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
    return 0;
  result = Unit_GetSquadCount(stackPtr);
  squad_count = result;
  if ( result )
  {
    slot_record = stackPtr;
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
signed int  UnitStack_HasGoldCargo(int stackPtr)
{
  int slotIndex; // edx
  int slotType; // ecx

  slotIndex = 0;
  while ( 1 )
  {
    slotType = *(__int16 *)(stackPtr + 6);
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_GOLD_CARGO )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (004121A0) --------------------------------------------------------
signed int  UnitStack_HasPeasantCargo(int stackPtr)
{
  int slotIndex; // edx
  int slotType; // ecx

  slotIndex = 0;
  while ( 1 )
  {
    slotType = *(__int16 *)(stackPtr + 6);
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_PEASANT_CARGO )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (004121D0) --------------------------------------------------------
signed int  UnitStack_NormalizePeasantCargo(__int16 *stackPtr, DWORD a2, double a3)
{
  __int16 *slotPtr; // ecx
  int totalPeasantQuantity; // esi
  int peasantSlotCount; // edx
  int i; // ebx
  int slotType; // eax
  __int16 *v8; // edx
  int j; // ecx
  __int16 *clearCursor; // ecx
  int clearIndex; // eax
  __int16 *clearSlotPtr; // ebx
  signed int squadCount; // edi
  int v14; // edx
  int fullCargoUnits; // eax
  __int64 v16; // rtt
  int addedIndex; // ebx
  int v18; // ebp
  char minActionPoints; // [esp+4h] [ebp-18h]

  slotPtr = stackPtr + 3;
  totalPeasantQuantity = 0;
  peasantSlotCount = 0;
  for ( i = 0; i < 10; ++i )
  {
    slotType = *slotPtr;
    if ( slotType == -1 )
      break;
    if ( slotType == UNIT_TYPE_PEASANT_CARGO )
    {
      ++peasantSlotCount;
      totalPeasantQuantity += *((char *)slotPtr + 9);
    }
    slotPtr = (__int16 *)((char *)slotPtr + 31);
  }
  minActionPoints = UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr);
  if ( (int)v8 > totalPeasantQuantity )
  {
    clearCursor = stackPtr;
    clearIndex = 0;
    clearSlotPtr = stackPtr + 3;
    do
    {
      if ( *clearSlotPtr == -1 )
        break;
      if ( clearCursor[3] == UNIT_TYPE_PEASANT_CARGO )
        clearCursor[3] = -1;
      clearCursor = (__int16 *)((char *)clearCursor + 31);
      ++clearIndex;
      clearSlotPtr = (__int16 *)((char *)clearSlotPtr + 31);
    }
    while ( clearIndex < 10 );
    Unit_CompactSquad(stackPtr, (int)clearCursor, a3);
    squadCount = Unit_GetSquadCount((int)stackPtr);
    fullCargoUnits = totalPeasantQuantity / 100;
    addedIndex = 0;
    for ( j = (int)stackPtr + 31 * squadCount; ; *(_BYTE *)(j - 17) = minActionPoints )
    {
      v18 = addedIndex + squadCount;
      if ( addedIndex >= fullCargoUnits )
        break;
      j += 31;
      *(_WORD *)(j - 25) = UNIT_TYPE_PEASANT_CARGO;
      *(_BYTE *)(j - 16) = 100;
      *(_BYTE *)(j - 15) = 0;
      *(_BYTE *)(j - 14) = 10;
      ++addedIndex;
    }
    LOBYTE(i) = 100;
    *(_BYTE *)(j + 14) = minActionPoints;
    *(_WORD *)(j + 6) = UNIT_TYPE_PEASANT_CARGO;
    *(_BYTE *)(j + 15) = totalPeasantQuantity % 100;
    v8 = stackPtr;
    *(_BYTE *)(j + 16) = 0;
    a2 = (DWORD)stackPtr + 31 * v18 + 31;
    *(_BYTE *)(j + 17) = 10;
    *(_WORD *)(a2 + 6) = -1;
  }
  return Rules_SyncArmyFactStrength(stackPtr, (int)v8, j, i, a2, a3);
}
// 412213: variable 'v8' is possibly undefined
// 41224F: variable 'v14' is possibly undefined
// 4122E3: variable 'j' is possibly undefined

//----- (00412300) --------------------------------------------------------
__int16 * UnitStack_CaptureDefeatedStack(
        __int16 *winnerStack,
        signed int defeatedStackPtr,
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

  Debug_Log(a3, a4, (DWORD)winnerStack, (int)aUnit_capture0x);
  winner_stack = winnerStack;
  defeated_stack = (__int16 *)defeatedStackPtr;
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
int  Unit_CreateNearbyUnitGroup(int originRow, int originColumn, unsigned __int8 *sourceSlots, double a4)
{
  unsigned __int8 *sourceSlotsPtr; // ebp
  signed int createSucceeded; // edi
  int neighborIndex; // esi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int slotCount; // edx
  unsigned __int8 *i; // eax
  int slotByteOffset; // ebx
  int v13; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // [esp-4h] [ebp-24h]
  int targetStackPtr; // [esp+0h] [ebp-20h]
  int neighborOrdinal; // [esp+4h] [ebp-1Ch]

  sourceSlotsPtr = sourceSlots;
  createSucceeded = 0;
  Debug_Log(originRow, (char)sourceSlots, (DWORD)sourceSlots, (int)aUnitCreateNearbyUnitGroup);
  neighborIndex = 0;
  neighborOrdinal = 0;
  do
  {
    v7 = Map_NeighborDX[neighborIndex];
    v8 = Map_NeighborDY[neighborIndex] + originColumn;
    v9 = v7 + originRow;
    if ( v7 + originRow >= 0 )
    {
      v7 = gameData;
      if ( v9 < *(_DWORD *)(gameData + 140000) && v8 >= 0 && v8 < *(_DWORD *)(gameData + 140004) )
      {
        LOBYTE(sourceSlots) = -1;
        if ( !Trap_GetTileOwnerMask(v9, v8, -1) )
        {
          v18 = Map_NeighborDY[neighborIndex] + originColumn;
          LOBYTE(sourceSlots) = Rng_RandRange(0, 7);
          createSucceeded = Unit_Create(*(__int16 *)sourceSlotsPtr, sourceSlotsPtr[2], v13, (char)sourceSlots, v18);
          if ( createSucceeded )
            break;
        }
      }
    }
    neighborIndex += 2;
    ++neighborOrdinal;
  }
  while ( neighborIndex < 16 );
  if ( createSucceeded )
  {
    slotCount = 0;
    targetStackPtr = 725
        * *(unsigned __int16 *)(gameData
                              + 200 * (Map_NeighborDX[2 * neighborOrdinal] + originRow)
                              + 2 * (Map_NeighborDY[2 * neighborOrdinal] + originColumn)
                              + 556374)
        + gameData
        + 147174;
    for ( i = sourceSlotsPtr; ; i += 31 )
    {
      slotByteOffset = 31 * slotCount;
      if ( *(__int16 *)i == -1 )
        break;
      ++slotCount;
    }
    qmemcpy((void *)(targetStackPtr + 6), sourceSlotsPtr, 31 * slotCount);
    if ( slotCount < 9 )
    {
      slotByteOffset += targetStackPtr;
      *(_WORD *)(slotByteOffset + 6) = -1;
    }
    Rules_LinkArmyFact((__int16 *)targetStackPtr, slotCount, 0, a4, slotByteOffset, (DWORD)sourceSlotsPtr);
    Rules_SyncArmyFactStrength((__int16 *)targetStackPtr, v15, v16, slotByteOffset, (DWORD)sourceSlotsPtr, a4);
    Debug_Log(v17, slotByteOffset, targetStackPtr, (int)aUnit_createn_1);
    Unit_DebugDumpFormationSizes(targetStackPtr, targetStackPtr);
    return targetStackPtr;
  }
  else
  {
    Debug_Log(v7, (char)sourceSlots, (DWORD)sourceSlotsPtr, (int)aUnit_createn_0);
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
int  UnitSlot_AdjustFatigueByPredicate(int slotPtr, int fatigueDelta, BOOL ( *predicate)(int slotPtr))
{
  int result; // eax
  signed char newFatigue; // cl

  result = predicate(slotPtr);
  if ( result )
  {
    result = *(__int16 *)slotPtr;
    if ( result != UNIT_TYPE_GOLD_CARGO
      && result != UNIT_TYPE_PEASANT_CARGO
      && result != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      && result != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      newFatigue = fatigueDelta + *(char *)(slotPtr + 10);
      *(_BYTE *)(slotPtr + 10) = newFatigue;
      if ( newFatigue < 0 )
        *(_BYTE *)(slotPtr + 10) = 0;
      if ( *(char *)(slotPtr + 10) > 100 )
        *(_BYTE *)(slotPtr + 10) = 100;
      return *(char *)(slotPtr + 10);
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
        __int16 *stackPtr,
        int fatigueDelta,
        BOOL ( *predicate)(int stackPtr),
        DWORD a4,
        double a5)
{
  __int16 *slotPtr; // edx
  int slotIndex; // ecx
  int slotType; // eax
  signed int result; // eax
  char fatigueDeltaByte; // [esp+0h] [ebp-8h]

  fatigueDeltaByte = fatigueDelta;
  if ( fatigueDelta <= 0 || (result = UnitStack_HasSpecialPersonageUnits((intptr_t)stackPtr)) == 0 )
  {
    slotPtr = stackPtr + 3;
    slotIndex = 0;
    while ( slotIndex < 10 )
    {
      if ( *slotPtr == -1 )
        break;
      if ( predicate((int)slotPtr) )
      {
        slotType = *slotPtr;
        if ( slotType != UNIT_TYPE_GOLD_CARGO
          && slotType != UNIT_TYPE_PEASANT_CARGO
          && slotType != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          && slotType != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          int fatigue = (signed char)*((char *)slotPtr + 10) + (signed char)fatigueDeltaByte;
          *((_BYTE *)slotPtr + 10) = (unsigned char)fatigue;
          if ( fatigue < 0 )
            *((_BYTE *)slotPtr + 10) = 0;
          if ( *((char *)slotPtr + 10) > 100 )
            *((_BYTE *)slotPtr + 10) = 100;
        }
      }
      ++slotIndex;
      slotPtr = (__int16 *)((char *)slotPtr + 31);
    }
    return Rules_SyncArmyFactStrength(stackPtr, (int)slotPtr, slotIndex, (char)predicate, a4, a5);
  }
  return result;
}

//----- (00412880) --------------------------------------------------------
int  UnitSlot_AdjustMoraleByPredicate(int slotPtr, int moraleDelta, BOOL ( *predicate)(int slotPtr))
{
  int result; // eax
  int unit_type; // eax
  int morale; // eax

  result = predicate(slotPtr);
  if ( result )
  {
    unit_type = *(__int16 *)slotPtr;
    if ( unit_type != UNIT_TYPE_GOLD_CARGO
      && unit_type != UNIT_TYPE_PEASANT_CARGO
      && unit_type != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
      && unit_type != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      morale = *(char *)(slotPtr + 11) + moraleDelta;
      *(_BYTE *)(slotPtr + 11) = morale;
      if ( moraleDelta > 0 )
        *(_BYTE *)(slotPtr + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
      if ( *(char *)(slotPtr + 11) < 0 )
        *(_BYTE *)(slotPtr + 11) = 0;
      if ( *(char *)(slotPtr + 11) > 20 )
        *(_BYTE *)(slotPtr + 11) = 20;
      return *(char *)(slotPtr + 11);
    }
  }
  return result;
}

//----- (004128E0) --------------------------------------------------------
signed int  UnitStack_AdjustMoraleByPredicate(
        __int16 *stackPtr,
        int moraleDelta,
        BOOL ( *predicate)(int stackPtr),
        DWORD a4,
        double a5)
{
  __int16 *slotPtr; // edx
  int slotIndex; // ecx
  int slotType; // eax
  signed int result; // eax

  if ( moraleDelta >= 0 || (result = UnitStack_HasSpecialPersonageUnits((intptr_t)stackPtr)) == 0 )
  {
    slotPtr = stackPtr + 3;
    slotIndex = 0;
    while ( slotIndex < 10 )
    {
      if ( *slotPtr == -1 )
        break;
      if ( predicate((int)slotPtr) )
      {
        slotType = *slotPtr;
        if ( slotType != UNIT_TYPE_GOLD_CARGO
          && slotType != UNIT_TYPE_PEASANT_CARGO
          && slotType != UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
          && slotType != UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        {
          *((_BYTE *)slotPtr + 11) += moraleDelta;
          if ( moraleDelta > 0 )
            *((_BYTE *)slotPtr + 13) &= ~UNIT_SLOT_FLAG_LOW_MORALE;
          if ( *((char *)slotPtr + 11) < 0 )
            *((_BYTE *)slotPtr + 11) = 0;
          if ( *((char *)slotPtr + 11) > 20 )
            *((_BYTE *)slotPtr + 11) = 20;
        }
      }
      ++slotIndex;
      slotPtr = (__int16 *)((char *)slotPtr + 31);
    }
    return Rules_SyncArmyFactStrength(stackPtr, (int)slotPtr, slotIndex, (char)predicate, a4, a5);
  }
  return result;
}

//----- (00412970) --------------------------------------------------------
int  UnitSlot_CycleOrderState(int result)
{
  char nextOrderState; // dl
  char clearedFlags; // dh
  char updatedFlags; // bl

  nextOrderState = (UNIT_SLOT_ORDER_STATE(result) + 1) & 3;
  clearedFlags = *(_BYTE *)(result + 12) & 0xF3;
  *(_BYTE *)(result + 12) = clearedFlags;
  updatedFlags = (4 * nextOrderState) | clearedFlags;
  *(_BYTE *)(result + 12) = updatedFlags;
  if ( (unsigned __int8)((unsigned __int8)(16 * updatedFlags) >> 6) > 2u )
  {
    *(_BYTE *)(result + 12) = updatedFlags & 0xF3;
    if ( (clearedFlags & 3u) < 3 )
    {
      *(_BYTE *)(result + 12) = updatedFlags & 0xF0;
      *(_BYTE *)(result + 12) = ((clearedFlags & 3) + 1) & 3 | ((4 * nextOrderState) | clearedFlags) & 0xF0;
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
__int16 * UnitStack_SetSpentTurnFlag(int stackPtr)
{
  __int16 *result; // eax
  int i; // edx
  char slotFlags; // bl

  result = (__int16 *)(stackPtr + 6);
  for ( i = 0; i < 10; ++i )
  {
    if ( *result == -1 )
      break;
    slotFlags = *((_BYTE *)result + 13);
    result = (__int16 *)((char *)result + 31);
    *((_BYTE *)result - 18) = slotFlags | UNIT_SLOT_FLAG_SPENT_TURN;
  }
  return result;
}

//----- (00412A60) --------------------------------------------------------
__int16 * UnitStack_ClearSpentTurnFlag(int stackPtr)
{
  __int16 *result; // eax
  int i; // edx
  char slotFlags; // bl

  result = (__int16 *)(stackPtr + 6);
  for ( i = 0; i < 10; ++i )
  {
    if ( *result == -1 )
      break;
    slotFlags = *((_BYTE *)result + 13);
    result = (__int16 *)((char *)result + 31);
    *((_BYTE *)result - 18) = slotFlags & ~UNIT_SLOT_FLAG_SPENT_TURN;
  }
  return result;
}

//----- (00412A90) --------------------------------------------------------
int  UnitStack_SetPlagueFlag(int result)
{
  int i; // edx
  char slotFlags; // bl

  for ( i = 0; i < 10; ++i )
  {
    if ( *(__int16 *)(result + 6) == -1 )
      break;
    slotFlags = *(_BYTE *)(result + 19);
    result += 31;
    *(_BYTE *)(result - 12) = slotFlags | 8;
  }
  return result;
}

//----- (00412AC0) --------------------------------------------------------
signed int  UnitStack_HasPlague(int stackPtr)
{
  int slotIndex; // edx

  slotIndex = 0;
  while ( 1 )
  {
    if ( *(__int16 *)(stackPtr + 6) == -1 )
      return 0;
    if ( (*(_BYTE *)(stackPtr + 19) & UNIT_SLOT_FLAG_PLAGUE) != 0 )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412AF0) --------------------------------------------------------
signed int  UnitStack_HasLowMoraleUnit(int stackPtr)
{
  __int16 *slotPtr; // eax
  int slotIndex; // edx

  slotPtr = (__int16 *)(stackPtr + 6);
  slotIndex = 0;
  while ( 1 )
  {
    if ( *slotPtr == -1 )
      return 0;
    if ( (*((_BYTE *)slotPtr + 13) & UNIT_SLOT_FLAG_LOW_MORALE) != 0 )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + 31);
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412B20) --------------------------------------------------------
int  UnitStackSelection_BuildSelectedSlotIndexList(int result, int slotCount, int *selectedOut)
{
  int selectionFlags; // esi
  int *outCursor; // edx
  int i; // [esp+0h] [ebp-Ch]

  selectionFlags = result;
  for ( i = 0; slotCount > i; ++i )
  {
    if ( *(_DWORD *)(selectionFlags + 4 * i) )
    {
      outCursor = selectedOut++;
      *outCursor = i;
    }
    result = i;
  }
  *selectedOut = -1;
  return result;
}

//----- (00412B60) --------------------------------------------------------
signed int  UnitStack_HasSpecialPersonageUnits(intptr_t stackPtr)
{
  int slotIndex; // ecx
  int slotType; // eax

  slotIndex = 0;
  while ( 1 )
  {
    slotType = *(__int16 *)(stackPtr + 6);
    if ( slotType == -1 )
      return 0;
    if ( slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      break;
    ++slotIndex;
    stackPtr += 31;
    if ( slotIndex >= 10 )
      return 0;
  }
  return 1;
}

//----- (00412B90) --------------------------------------------------------
int  UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(char *slotArray, int slotCount, int wallDefenseBonus)
{
  int hasSpecialPersonage; // ebx
  int slotIndex; // eax
  char *slotCursor; // edx
  int slotType; // ecx

  hasSpecialPersonage = 0;
  slotIndex = 0;
  if ( slotCount > 0 )
  {
    slotCursor = slotArray;
    do
    {
      if ( hasSpecialPersonage )
        break;
      slotType = *(__int16 *)slotCursor;
      if ( slotType == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slotType == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        hasSpecialPersonage = 1;
      ++slotIndex;
      slotCursor += 31;
    }
    while ( slotIndex < slotCount );
  }
  return UnitSlots_CalcCombatStrengthScore(slotArray, slotCount, hasSpecialPersonage, wallDefenseBonus);
}
// 412B90: could not find valid save-restore pair for ebx

//----- (00412BE0) --------------------------------------------------------
int  UnitStack_CalcMilitaryStrength(int stackPtr)
{
  signed int squadCount; // eax
  int v2; // edx

  squadCount = Unit_GetSquadCount(stackPtr);
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)(v2 + 6), squadCount, 0);
}
// 412BEA: variable 'v2' is possibly undefined

//----- (00412C00) --------------------------------------------------------
int  Building_CalcGarrisonStrength(int buildingRecord, signed int a2)
{
  int wallDefenseBonus; // ebx
  int v3; // edx
  int garrisonCount; // eax
  char *garrisonSlots; // ecx

  wallDefenseBonus = Building_CalcWallDefenseBonus(buildingRecord, a2);
  garrisonCount = Building_CountGarrison(v3);
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(garrisonSlots, garrisonCount, wallDefenseBonus);
}
// 412C11: variable 'v3' is possibly undefined
// 412C1A: variable 'v5' is possibly undefined

//----- (00412C30) --------------------------------------------------------
int  Player_CalcMilitaryStrength(signed int playerIndex)
{
  int totalStrength; // ecx
  int buildingIndex; // edx
  int v4; // eax
  int buildingStrength; // eax
  int v6; // ecx
  int i; // ebx
  int stackRecordBase; // edx
  int stackStrength; // eax
  int v10; // ecx

  totalStrength = 0;
  buildingIndex = 0;
LABEL_2:
  v4 = UNIT_RECORD(buildingIndex);
  if ( (unsigned int)*(char *)(v4 + 4) < 4
    && *(__int16 *)(v4 + 16) != -1
    && *(unsigned __int8 *)(gameData + 467 * buildingIndex + 509676) == playerIndex )
  {
    buildingStrength = Building_CalcGarrisonStrength(UNIT_RECORD(buildingIndex), playerIndex);
    totalStrength = buildingStrength + v6;
  }
  while ( ++buildingIndex < 100 )
  {
    if ( buildingIndex >= 0 )
      goto LABEL_2;
  }
  for ( i = 0; i < 500; ++i )
  {
    stackRecordBase = gameData + 725 * i;
    if ( playerIndex == *(unsigned __int8 *)(stackRecordBase + 147178) && *(__int16 *)(stackRecordBase + 147180) != -1 )
    {
      stackStrength = UnitStack_CalcMilitaryStrength(gameData + 147174 + 725 * i);
      totalStrength = stackStrength + v10;
    }
  }
  return totalStrength;
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
int  UnitStack_CopyFromTemplate(int destStack, int srcStack, int a3)
{
  int v4; // eax
  int result; // eax
  int v7; // [esp-8h] [ebp-Ch]

  *(_WORD *)destStack = *(_WORD *)srcStack;
  *(_WORD *)(destStack + 2) = *(_WORD *)(srcStack + 2);
  *(_BYTE *)(destStack + 4) = *(_BYTE *)(srcStack + 4);
  *(_BYTE *)(destStack + 5) = *(_BYTE *)(srcStack + 5);
  *(_DWORD *)(_wcpp_4_copy_array__(a3) + 310) = *(_DWORD *)(srcStack + 316);
  v4 = _wcpp_4_copy_array__(v7);
  *(_BYTE *)(v4 + 400) = *(_BYTE *)(srcStack + 720);
  result = v4 - 320;
  *(_DWORD *)(result + 721) = *(_DWORD *)(srcStack + 721);
  return result;
}
// 412D20: could not find valid save-restore pair for esi
// 412D74: variable 'v7' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00412DA0) --------------------------------------------------------
int  BattleUnitEntry_CopyMergingPackedFlags(int result, int srcEntry)
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

  *(_WORD *)result = *(_WORD *)srcEntry;
  *(_BYTE *)(result + 2) = *(_BYTE *)(srcEntry + 2);
  *(_BYTE *)(result + 3) = *(_BYTE *)(srcEntry + 3);
  *(_WORD *)(result + 4) = *(_WORD *)(srcEntry + 4);
  *(_WORD *)(result + 6) = *(_WORD *)(srcEntry + 6);
  *(_BYTE *)(result + 8) = *(_BYTE *)(srcEntry + 8);
  *(_BYTE *)(result + 9) = *(_BYTE *)(srcEntry + 9);
  *(_BYTE *)(result + 10) = *(_BYTE *)(srcEntry + 10);
  *(_BYTE *)(result + 11) = *(_BYTE *)(srcEntry + 11);
  v2 = *(_BYTE *)(result + 12) & 0xFC;
  v3 = *(_BYTE *)(srcEntry + 12) & 3;
  *(_BYTE *)(result + 12) = v2;
  v4 = v3 | v2;
  *(_BYTE *)(result + 12) = v3 | v2;
  v5 = *(_BYTE *)(srcEntry + 12) & 0xC;
  *(_BYTE *)(result + 12) = v4 & 0xF3;
  v6 = v5 | v4 & 0xF3;
  *(_BYTE *)(result + 12) = v6;
  v7 = *(_BYTE *)(srcEntry + 12) & 0x70;
  *(_BYTE *)(result + 12) = v6 & 0x8F;
  v8 = v7 | v6 & 0x8F;
  v9 = *(_BYTE *)(result + 13);
  *(_BYTE *)(result + 12) = v8;
  v10 = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) = v9 & 0xFE;
  *(_DWORD *)(result + 13) |= v10 & 1;
  v11 = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) &= ~2u;
  *(_DWORD *)(result + 13) |= v11 & 2;
  v12 = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) &= ~4u;
  *(_DWORD *)(result + 13) |= v12 & 4;
  v13 = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) &= ~8u;
  *(_DWORD *)(result + 13) |= v13 & 8;
  LOBYTE(v13) = *(_BYTE *)(srcEntry + 17) & 7;
  v14 = *(_BYTE *)(result + 17) & 0xF8;
  *(_BYTE *)(result + 17) = v14;
  *(_BYTE *)(result + 17) = v13 | v14;
  *(_DWORD *)(result + 18) = *(_DWORD *)(srcEntry + 18);
  v15 = *(_BYTE *)(result + 22) & 0xFE;
  LOBYTE(v13) = *(_BYTE *)(srcEntry + 22) & 1;
  *(_BYTE *)(result + 22) = v15;
  *(_BYTE *)(result + 22) = v13 | v15;
  *(_DWORD *)(result + 23) = *(_DWORD *)(srcEntry + 23);
  *(_DWORD *)(result + 27) = *(_DWORD *)(srcEntry + 27);
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
        unsigned __int16 unitType,
        char ownerColor,
        unsigned __int8 animFrame,
        unsigned __int8 facing,
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
  *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset) = (unsigned __int16)unitType;
  g_UnitSpriteCacheRecords[record_offset + 4] = ownerColor;
  g_UnitSpriteCacheRecords[record_offset + 5] = facing;
  g_UnitSpriteCacheRecords[record_offset + 6] = animFrame;
  *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) = Time_Now(0, 0);

  Unit_BuildGoSpriteFilePath(path, (unsigned __int8)unitType, ownerColor);
  sprite_record = Mem_Alloc(22, 0, 0, 0);
  if ( sprite_record )
    sprite_record = DLXSprite_LoadCachedEntry(sprite_record, path, animFrame + 8 * facing);
  *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7) = sprite_record;
  return sprite_record;
}

int  Unit_SetFlag(unsigned __int16 unitType, char ownerColor, unsigned __int8 animFrame, unsigned __int8 facing, DWORD a5, signed int a6)
{
  return UnitSpriteCache_GetOrLoadEntry(unitType, ownerColor, animFrame, facing, a5, a6);
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
int  UnitSpriteCache_FindEntryOrLoad(signed int unitType, char ownerColor, unsigned __int8 animFrame, unsigned __int8 facing)
{
  int record_index;
  int record_offset;

  for ( record_index = 0; record_index < UNIT_SPRITE_CACHE_RECORD_COUNT; ++record_index )
  {
    record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
    if ( *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset) == (unsigned __int16)unitType
      && g_UnitSpriteCacheRecords[record_offset + 4] == (unsigned char)ownerColor
      && g_UnitSpriteCacheRecords[record_offset + 5] == facing
      && g_UnitSpriteCacheRecords[record_offset + 6] == animFrame )
    {
      *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) = Time_Now(0, 0);
      return *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7);
    }
  }
  return Unit_SetFlag(unitType, ownerColor, animFrame, facing, 0, 0);
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
    if ( *(int *)((char *)&g_UnitSpriteCacheTableBase + i) != -1 )
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
char  Unit_BuildGoSpriteFilePath(char *destPath, unsigned __int8 unitType, char variantDigit)
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
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_go;
  v4 = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
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
  v7 = (char *)UnitType_GetResourceKey(unitType);
  v8 = &destPath[strlen(destPath)];
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
  v11 = variantSuffix;
  v12 = &destPath[strlen(destPath)];
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
  v16 = &destPath[strlen(destPath)];
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
char  UI_BeginUnitInfo(char *destPath, unsigned __int8 unitType, char variantDigit)
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
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_i;
  v4 = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
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
  v7 = (char *)UnitType_GetResourceKey(unitType);
  v8 = &destPath[strlen(destPath)];
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
  v11 = variantSuffix;
  v12 = &destPath[strlen(destPath)];
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
  v16 = &destPath[strlen(destPath)];
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
  v20 = &destPath[strlen(destPath)];
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
char  Unit_BuildGarrisonSlotIconSpritePath(char *destPath, unsigned __int8 unitType, int a3)
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
  char prefixBuffer[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  v4 = aUnits_i_0;
  v5 = destPath;
  strcpy(prefixBuffer, "g");
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
  v8 = (char *)UnitType_GetResourceKey(unitType);
  v9 = &destPath[strlen(destPath)];
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
  v12 = prefixBuffer;
  v13 = &destPath[strlen(destPath)];
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
  v17 = &destPath[strlen(destPath)];
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
  v21 = &destPath[strlen(destPath)];
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
char  Unit_BuildSelectedUnitPanelIconSpritePath(char *destPath, unsigned __int8 unitType, int a3)
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
  char prefixBuffer[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  v4 = aUnits_i_1;
  v5 = destPath;
  strcpy(prefixBuffer, "c");
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
  v8 = (char *)UnitType_GetResourceKey(unitType);
  v9 = &destPath[strlen(destPath)];
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
  v12 = prefixBuffer;
  v13 = &destPath[strlen(destPath)];
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
  v17 = &destPath[strlen(destPath)];
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
  v21 = &destPath[strlen(destPath)];
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
char  Unit_BuildSelectedUnitPanelIconPalettePath(char *destPath, unsigned __int8 unitType, int a3)
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
  char prefixBuffer[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  v4 = aUnits_i_2;
  v5 = destPath;
  strcpy(prefixBuffer, "c");
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
  v8 = (char *)UnitType_GetResourceKey(unitType);
  v9 = &destPath[strlen(destPath)];
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
  v12 = prefixBuffer;
  v13 = &destPath[strlen(destPath)];
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
  v17 = &destPath[strlen(destPath)];
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
  v21 = &destPath[strlen(destPath)];
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
char  Unit_BuildAttackAnimSpritePath(char *destPath, unsigned __int8 unitType, char variantDigit)
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
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_at_1;
  v4 = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
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
  v7 = (char *)UnitType_GetResourceKey(unitType);
  v8 = &destPath[strlen(destPath)];
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
  v11 = variantSuffix;
  v12 = &destPath[strlen(destPath)];
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
  v16 = &destPath[strlen(destPath)];
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
  v20 = &destPath[strlen(destPath)];
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
char  Unit_BuildShotAnimSpritePath(char *destPath, unsigned __int8 unitType, char variantDigit)
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
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  v3 = aUnits_at;
  v4 = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
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
  v7 = (char *)UnitType_GetResourceKey(unitType);
  v8 = &destPath[strlen(destPath)];
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
  v11 = variantSuffix;
  v12 = &destPath[strlen(destPath)];
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
  v16 = &destPath[strlen(destPath)];
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
  v20 = &destPath[strlen(destPath)];
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
char  Unit_BuildShotAnimPaletteSpritePath(char *destPath, unsigned __int8 unitType)
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
  v3 = destPath;
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
  v6 = (char *)UnitType_GetResourceKey(unitType);
  v7 = &destPath[strlen(destPath)];
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
  v11 = &destPath[strlen(destPath)];
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
  v15 = &destPath[strlen(destPath)];
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
void  Unit_BuildBigInfoGraphicPath(char *destPath, unsigned __int8 unitType, int a3)
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
  int languageDirNames[7]; // [esp+0h] [ebp-1Ch]

  languageDirNames[5] = a3;
  languageDirNames[0] = (int)g_LanguageDirectoryNames[0];
  languageDirNames[1] = (int)g_LanguageDirectoryNames[1];
  languageDirNames[2] = (int)g_LanguageDirectoryNames[2];
  v3 = aBiginfo_;
  v4 = destPath;
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
  v7 = (char *)languageDirNames[(unsigned __int8)g_LanguageIndex];
  v8 = &destPath[strlen(destPath)];
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
  v11 = (char *)UnitType_GetResourceKey(unitType);
  v12 = &destPath[strlen(destPath)];
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
  v16 = &destPath[strlen(destPath)];
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
int  Map_GetUnitTileMoveCostOrZero(int playerIndex, int unitType, int tileColumn, int tileRow)
{
  unsigned int tileOccupant; // edx
  int occupantStackRecord; // eax
  int unitMetadataOffset; // edi
  unsigned __int16 *terrainRecord; // ecx
  unsigned __int16 *v12; // ecx

  tileOccupant = *(unsigned __int16 *)(2 * tileColumn + gameData + 200 * tileRow + 556374);
  if ( (unsigned __int16)tileOccupant != 0xFFFF )
  {
    if ( tileOccupant >= 0x8000 )
      return 0;
    occupantStackRecord = gameData + 725 * tileOccupant;
    if ( !*(_BYTE *)(occupantStackRecord + 147894) || *(unsigned __int8 *)(occupantStackRecord + 147178) == playerIndex )
      return 0;
  }
  if ( ((1 << playerIndex) & TILE_TRAP_OWNER_MASK(tileRow, tileColumn)) == 1 << playerIndex || MapTile_GetReligiousSiteCategory(tileRow, tileColumn) )
    return 0;
  unitMetadataOffset = 88 * unitType;
  terrainRecord = TILE_TERRAIN_RECORD(tileRow, tileColumn);
  if ( terrainRecord[2] != 0xFFFF )
    return UnitType_GetRoadMoveCost(unitType);
  if ( !g_PathingAllowBridgeCrossings )
    return UnitType_GetWorldMoveCost(unitType, g_TerrainMoveProfileOffsets[*terrainRecord]);
  return Map_GetBridgeCrossingCostOrZero(tileRow, tileColumn)
      || UnitType_GetWorldMoveCost(unitType, g_TerrainMoveProfileOffsets[*terrainRecord]);
}
// 413E1D: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00413F50) --------------------------------------------------------
signed int  UnitStack_GetTileMoveCostFromMergedProfileOrZero(__int16 *stackPtr, intptr_t mergedProfile, int tileColumn, int tileRow)
{
  int tile_index_ptr; // eax
  unsigned int occupant_stack_index; // edx
  int occupant_stack; // eax
  signed int result; // eax
  unsigned __int16 *terrain_record; // edi

  tile_index_ptr = TILE_INDEX(tileRow, tileColumn);
  occupant_stack_index = *(unsigned __int16 *)tile_index_ptr;
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF
      || (occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index, !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720))
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
    {
      if ( *stackPtr != tileRow || stackPtr[1] != tileColumn )
        return 0;
    }
  }
  occupant_stack_index = *(unsigned __int16 *)TILE_INDEX(tileRow, tileColumn);
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index >= 0x8000 )
      return 0;
    occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index;
    if ( !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720)
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
      return 0;
  }
  if ( ((1 << *((_BYTE *)stackPtr + 4)) & TILE_TRAP_OWNER_MASK(tileRow, tileColumn)) == 1 << *((_BYTE *)stackPtr + 4)
    || MapTile_GetReligiousSiteCategory(tileRow, tileColumn) )
  {
    return 0;
  }
  terrain_record = TILE_TERRAIN_RECORD(tileRow, tileColumn);
  if ( terrain_record[2] != 0xFFFF )
    return *(unsigned __int8 *)(mergedProfile + 29);
  if ( !g_PathingAllowBridgeCrossings )
    return *(unsigned __int8 *)(g_TerrainMoveProfileOffsets[*terrain_record] + mergedProfile + 30);
  result = Map_GetBridgeCrossingCostOrZero(tileRow, tileColumn);
  if ( !result )
    return *(unsigned __int8 *)(g_TerrainMoveProfileOffsets[*terrain_record] + mergedProfile + 30);
  return result;
}
// 41402D: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00414150) --------------------------------------------------------
signed int  UnitStack_GetTileMoveCostOrZero(__int16 *stackPtr, int tileRow, int a3, int tileColumn)
{
  unsigned int occupant_stack_index; // edx
  int occupant_stack; // eax
  int tile_index_ptr; // eax
  signed int result; // eax
  unsigned __int16 *terrain_record; // ecx
  _BYTE merged_profile[96]; // [esp-1Ch] [ebp-64h] BYREF
  int v16; // [esp+44h] [ebp-4h]

  v16 = a3;
  tile_index_ptr = TILE_INDEX(tileRow, tileColumn);
  occupant_stack_index = *(unsigned __int16 *)tile_index_ptr;
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF
      || (occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index, !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720))
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
    {
      if ( *stackPtr != tileRow || stackPtr[1] != tileColumn )
        return 0;
    }
  }
  UnitStack_BuildMergedTerrainMoveProfile((intptr_t)merged_profile, (intptr_t)stackPtr);
  occupant_stack_index = *(unsigned __int16 *)TILE_INDEX(tileRow, tileColumn);
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF )
      return 0;
    occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index;
    if ( !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720)
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
      return 0;
  }
  if ( ((1 << *((_BYTE *)stackPtr + 4)) & TILE_TRAP_OWNER_MASK(tileRow, tileColumn)) == 1 << *((_BYTE *)stackPtr + 4)
    || MapTile_GetReligiousSiteCategory(tileRow, tileColumn) )
  {
    return 0;
  }
  terrain_record = TILE_TERRAIN_RECORD(tileRow, tileColumn);
  if ( terrain_record[2] != 0xFFFF )
    return merged_profile[29];
  if ( !g_PathingAllowBridgeCrossings )
    return (unsigned __int8)merged_profile[g_TerrainMoveProfileOffsets[*terrain_record] + 30];
  result = Map_GetBridgeCrossingCostOrZero(tileRow, tileColumn);
  if ( !result )
    return (unsigned __int8)merged_profile[g_TerrainMoveProfileOffsets[*terrain_record] + 30];
  return result;
}
// 414194: conditional instruction was optimized away because edx.4<FFFFu
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00414350) --------------------------------------------------------
signed int  UnitStack_GetMoveCostToTile(int stackIndex, int tileRow, int tileColumn)
{
  return UnitStack_GetTileMoveCostOrZero((__int16 *)(gameData + 147174 + 725 * stackIndex), tileRow, tileRow, tileColumn);
}
// 5202E4: using guessed type int gameData;

//----- (00414390) --------------------------------------------------------
signed int  UnitStack_GetMoveCostToTileIgnoringOccupancy(__int16 *stackPtr, int tileRow, int tileColumn)
{
  int columnByteOffset; // ebp
  int tileSurfacePtr; // edx
  __int16 savedTileOccupant; // di
  signed int result; // eax

  columnByteOffset = 2 * tileColumn;
  tileSurfacePtr = gameData + 200 * tileRow + columnByteOffset + 556374;
  savedTileOccupant = *(_WORD *)tileSurfacePtr;
  *(_WORD *)tileSurfacePtr = -1;
  result = UnitStack_GetTileMoveCostOrZero(stackPtr, tileRow, 2 * tileColumn, tileColumn);
  *(_WORD *)tileSurfacePtr = savedTileOccupant;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00414400) --------------------------------------------------------
int * Path_InsertBridgeCornerWaypoints(int stackRecord, char a2, int *pathBuffer)
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
  if ( !pathBuffer || UnitStack_HasOnlyFlyingUnits(stackRecord) )
    return pathBuffer;
  scratch_path[0] = 0;
  scratch_waypoint = 0;
  LOBYTE(scratch_waypoint) = *(_BYTE *)stackRecord;
  BYTE1(scratch_waypoint) = *(_BYTE *)(stackRecord + 2);
  HIWORD(scratch_waypoint) = 0;
  if ( scratch_path[0] < 100 )
    scratch_path[++scratch_path[0]] = scratch_waypoint;
  while ( *pathBuffer )
  {
    current_waypoint = pathBuffer[*pathBuffer];
    --*pathBuffer;
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
      && (UnitStack_GetTileMoveCostOrZero((__int16 *)stackRecord, current_row, 0, previous_column)
       || UnitStack_GetTileMoveCostOrZero((__int16 *)stackRecord, previous_row, 0, current_column)) )
    {
      if ( *pathBuffer < 100 )
        pathBuffer[++*pathBuffer] = current_waypoint;
      if ( 100 - *pathBuffer <= 2 )
      {
        overflow = 1;
        break;
      }
      corner_waypoint = current_waypoint;
      if ( TILE_TERRAIN_RECORD(current_row, previous_column)[2] != 0xFFFF
        && UnitStack_GetTileMoveCostOrZero((__int16 *)stackRecord, current_row, 0, previous_column) )
      {
        BYTE1(corner_waypoint) = previous_column;
      }
      else if ( TILE_TERRAIN_RECORD(previous_row, current_column)[2] != 0xFFFF
             && UnitStack_GetTileMoveCostOrZero((__int16 *)stackRecord, previous_row, 0, current_column) )
      {
        LOBYTE(corner_waypoint) = previous_row;
      }
      else
      {
        continue;
      }
      HIWORD(corner_waypoint) = (HIWORD(current_waypoint) + HIWORD(previous_waypoint)) / 2;
      if ( *pathBuffer < 100 )
        pathBuffer[++*pathBuffer] = corner_waypoint;
      if ( 100 - *pathBuffer <= 2 )
      {
        overflow = 1;
        break;
      }
    }
    else
    {
      if ( *pathBuffer < 100 )
        pathBuffer[++*pathBuffer] = current_waypoint;
      if ( 100 - *pathBuffer <= 2 )
      {
        overflow = 1;
        break;
      }
    }
  }
  if ( overflow )
  {
    j__nfree_(pathBuffer);
    return 0;
  }
  return pathBuffer;
}
// 5202E4: using guessed type int gameData;

//----- (004147A0) --------------------------------------------------------
int * Unit_MoveTrack(int stackIndex, int sourceRow, int targetRow, int sourceColumn, DWORD availableActionPoints, int targetColumn)
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
  int *pathResult; // ebp
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
  _BYTE mergedProfile[88]; // [esp+0h] [ebp-104h] BYREF
  int stackIndex_l; // [esp+58h] [ebp-ACh]
  int sourceRow_l; // [esp+5Ch] [ebp-A8h]
  int sourceColumn_l; // [esp+60h] [ebp-A4h]
  int targetRow_l; // [esp+64h] [ebp-A0h]
  int savedCursorDescriptor; // [esp+68h] [ebp-9Ch]
  BOOL v56; // [esp+6Ch] [ebp-98h]
  int distanceGrid; // [esp+70h] [ebp-94h] BYREF
  int tileCostGrid; // [esp+74h] [ebp-90h] BYREF
  __int16 *stackRecord; // [esp+78h] [ebp-8Ch]
  int v60; // [esp+7Ch] [ebp-88h]
  int v61; // [esp+80h] [ebp-84h]
  int v62; // [esp+84h] [ebp-80h]
  int v63; // [esp+88h] [ebp-7Ch]
  int v64; // [esp+8Ch] [ebp-78h]
  int v65; // [esp+90h] [ebp-74h]
  int overflowFlag; // [esp+94h] [ebp-70h]
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
  int savedOccupant; // [esp+E8h] [ebp-1Ch]
  int v88; // [esp+ECh] [ebp-18h]
  unsigned __int16 *v89; // [esp+F0h] [ebp-14h]
  unsigned __int8 v90; // [esp+F4h] [ebp-10h]
  unsigned __int8 v91; // [esp+F8h] [ebp-Ch]

  stackIndex_l = stackIndex;
  sourceRow_l = sourceRow;
  sourceColumn_l = sourceColumn;
  targetRow_l = targetRow;
  Debug_Log(targetRow, sourceColumn, availableActionPoints, (int)aUnit_movetrack);
  v6 = targetRow;
  if ( v6 < 0 )
    return 0;
  v7 = v6;
  v8 = *(_DWORD *)(gameData + 140000);
  if ( v7 >= v8 )
    return 0;
  if ( targetColumn < 0 )
    return 0;
  v9 = *(_DWORD *)(gameData + 140004);
  if ( targetColumn >= v9 || v7 >= v8 || targetColumn >= v9 )
    return 0;
  result = (int *)UnitStack_GetMoveCostToTile(stackIndex_l, v7, targetColumn);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    Diagnostics_TraceWorldMapActionEvent(
      result ? "unit_move_target_cost" : "unit_move_target_blocked",
      stackIndex_l,
      v7,
      targetColumn,
      (int)result);
  if ( result )
  {
    savedCursorDescriptor = g_ActiveCursorDescriptorPtr;
    v56 = g_ActiveCursorDescriptorPtr != (_DWORD)&g_CursorDesc_Busy;
    if ( g_CursorOverlayPresented )
      RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
    v11 = 2 * sourceColumn_l;
    v12 = 2 * sourceColumn_l + gameData + 200 * sourceRow_l;
    LOWORD(v11) = *(_WORD *)(v12 + 556374);
    *(_WORD *)(v12 + 556374) = -1;
    v13 = stackIndex_l;
    savedOccupant = v11;
    stackRecord = (__int16 *)(725 * stackIndex_l + gameData + 147174);
    UnitStack_BuildMergedTerrainMoveProfile((intptr_t)mergedProfile, (intptr_t)stackRecord);
    distanceGrid = nmalloc_(0x4E20, 4);
    if ( !distanceGrid )
    {
      Debug_Log(0, targetColumn, v13, (int)aNotEnoughMem_3);
      App_RequestQuit((int)aNotEnoughMem_4);
    }
    tileCostGrid = nmalloc_(0x10000, 4);
    if ( !tileCostGrid )
    {
      Debug_Log(0, targetColumn, v13, (int)aNotEnoughMem_5);
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
        *(_WORD *)(v20 + v69 + distanceGrid) = -2;
        v21 = UnitStack_GetTileMoveCostFromMergedProfileOrZero(stackRecord, (intptr_t)mergedProfile, v19++, v18);
        v20 += 2;
        *(_BYTE *)(v19 + v70 + tileCostGrid - 1) = v21;
      }
      ++v18;
      v83 += 256;
      v84 += 200;
    }
    if ( sourceRow_l >= targetRow_l )
    {
      v61 = sourceRow_l;
      v60 = targetRow_l;
    }
    else
    {
      v60 = sourceRow_l;
      v61 = targetRow_l;
    }
    v22 = targetColumn;
    if ( sourceColumn_l >= targetColumn )
    {
      v63 = sourceColumn_l;
      v62 = targetColumn;
    }
    else
    {
      v62 = sourceColumn_l;
      v63 = targetColumn;
    }
    *(_WORD *)(200 * sourceRow_l + distanceGrid + 2 * sourceColumn_l) = 0;
    v74 = 200 * targetRow_l;
    v65 = 25;
    v75 = 2 * targetColumn;
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
              v25 = *(unsigned __int16 *)(v85 + v82 + distanceGrid);
              if ( v25 != 65534 && v25 != 0xFFFF )
              {
                v81 = v85;
                for ( i = 0; i != 16; i += 2 )
                {
                  v27 = Map_NeighborDX[i] + v71;
                  v28 = v24 + Map_NeighborDY[i];
                  if ( v27 >= v60 && v27 <= v61 && v28 >= v62 && v28 <= v63 )
                  {
                    LOWORD(v29) = *(unsigned __int8 *)(tileCostGrid + (v27 << 8) + v28);
                    if ( (_BYTE)v29 )
                    {
                      if ( v27 != v71 && v28 != v24 )
                        v29 = (23 * (unsigned __int16)v29
                             - (__CFSHL__((23 * (unsigned __int16)v29) >> 31, 4)
                              + 16 * ((23 * (unsigned __int16)v29) >> 31))) >> 4;
                      v46 = (unsigned __int16 *)(v81 + v80 + distanceGrid);
                      v72 = *v46;
                      v73 = (unsigned __int16)v29 + v72;
                      v47 = (_WORD *)(distanceGrid + 200 * v27 + 2 * v28);
                      if ( (unsigned __int16)*v47 > v73 )
                      {
                        v48 = *v46;
                        v64 = 1;
                        *v47 = v48 + v29;
                      }
                    }
                    else
                    {
                      *(_WORD *)(distanceGrid + 200 * v27 + 2 * v28) = -1;
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
        if ( *(unsigned __int16 *)(v75 + v74 + distanceGrid) != 65534 )
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
    v31 = (unsigned __int16 *)(2 * targetColumn + distanceGrid + 200 * targetRow_l);
    pathResult = 0;
    v33 = *v31;
    overflowFlag = 0;
    if ( v33 != 65534 )
    {
      LOWORD(v31) = *v31;
      v91 = targetRow_l;
      v89 = v31;
      v34 = (int *)Mem_Alloc(404, v30, distanceGrid, 0);
      v90 = targetColumn;
      if ( v34 )
        *v34 = 0;
      HIWORD(v76) = HIWORD(g_UnitPathfindingScratchDword);
      LOBYTE(v76) = v91;
      pathResult = v34;
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
              && (unsigned __int16)v88 > *(_WORD *)(distanceGrid + 200 * v39 + 2 * v38) )
            {
              LOWORD(v40) = *(unsigned __int8 *)(v79 + tileCostGrid + (v91 << 8));
              if ( v37 && v30 )
                v40 = (23 * (unsigned __int16)v40
                     - (__CFSHL__((23 * (unsigned __int16)v40) >> 31, 4)
                      + 16 * ((23 * (unsigned __int16)v40) >> 31))) >> 4;
              v41 = (_WORD *)(distanceGrid + 200 * (v37 + v91) + 2 * (v30 + v90));
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
        v89 = (unsigned __int16 *)*(unsigned __int16 *)(200 * v91 + distanceGrid + 2 * v90);
        HIWORD(v76) = (_WORD)v89;
        v43 = *pathResult;
        if ( 100 - *pathResult <= 2 )
        {
          overflowFlag = 1;
          break;
        }
        if ( v43 < 100 )
        {
          *pathResult = v43 + 1;
          pathResult[v43 + 1] = v76;
        }
      }
      --*pathResult;
    }
    else if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    {
      Diagnostics_TraceWorldMapActionEvent("unit_move_track_unreachable", stackIndex_l, targetRow_l, targetColumn, v65);
    }
    if ( overflowFlag && pathResult )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_overflow", stackIndex_l, targetRow_l, targetColumn, *pathResult);
      j__nfree_(pathResult);
      pathResult = 0;
    }
    v44 = sourceRow_l;
    *(_WORD *)(TILE_INDEX(sourceRow_l, sourceColumn_l)) = savedOccupant;
    nfree_(distanceGrid);
    distanceGrid = 0;
    nfree_(tileCostGrid);
    tileCostGrid = 0;
    if ( pathResult )
    {
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      {
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_built", stackIndex_l, targetRow_l, targetColumn, *pathResult);
        if ( *pathResult )
        {
          int raw_count = *pathResult;
          int raw_sample_index;
          int raw_waypoint;

          raw_sample_index = raw_count;
          raw_waypoint = pathResult[raw_sample_index];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_raw_sample",
            stackIndex_l,
            (unsigned __int8)raw_waypoint,
            BYTE1(raw_waypoint),
            raw_sample_index);
          raw_sample_index = raw_count * 3 / 4;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = pathResult[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              stackIndex_l,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_sample_index = raw_count / 2;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = pathResult[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              stackIndex_l,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_sample_index = raw_count / 4;
          if ( raw_sample_index > 0 && raw_sample_index < raw_count )
          {
            raw_waypoint = pathResult[raw_sample_index];
            Diagnostics_TraceWorldMapActionEvent(
              "unit_move_track_raw_sample",
              stackIndex_l,
              (unsigned __int8)raw_waypoint,
              BYTE1(raw_waypoint),
              raw_sample_index);
          }
          raw_waypoint = pathResult[1];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_raw_sample",
            stackIndex_l,
            (unsigned __int8)raw_waypoint,
            BYTE1(raw_waypoint),
            1);
        }
      }
      pathResult = Path_InsertBridgeCornerWaypoints(gameData + 147174 + 725 * stackIndex_l, v44, pathResult);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      {
        Diagnostics_TraceWorldMapActionEvent("unit_move_track_ready", stackIndex_l, targetRow_l, targetColumn, pathResult ? *pathResult : -1);
        if ( pathResult && *pathResult )
        {
          v45 = pathResult[*pathResult];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_next",
            stackIndex_l,
            (unsigned __int8)v45,
            BYTE1(v45),
            HIWORD(v45));
          v45 = pathResult[1];
          Diagnostics_TraceWorldMapActionEvent(
            "unit_move_track_first",
            stackIndex_l,
            (unsigned __int8)v45,
            BYTE1(v45),
            HIWORD(v45));
        }
      }
    }
    if ( v56 && g_CursorOverlayPresented )
      RenderState_SelectCursorDescriptor((int)g_RenderState, savedCursorDescriptor);
    return pathResult;
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
_DWORD * Unit_MoveTrackNearTile(int stackIndex, int targetRow, int a3, int targetColumn, DWORD a5)
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
  Debug_Log(stackIndex, targetColumn, a5, (int)aUnit_movetra_1);
  if ( targetRow < 0 || targetRow >= *(_DWORD *)(gameData + 140000) || targetColumn < 0 || targetColumn >= *(_DWORD *)(gameData + 140004) )
    return 0;

  stack_record = UNIT_STACK(stackIndex);
  source_row = UNIT_STACK_TILE_ROW(stack_record);
  source_column = UNIT_STACK_TILE_COLUMN(stack_record);
  row_delta = source_row - targetRow;
  if ( row_delta < 0 )
    row_delta = -row_delta;
  column_delta = source_column - targetColumn;
  if ( column_delta < 0 )
    column_delta = -column_delta;
  if ( row_delta == 0 && column_delta == 0 )
  {
    raw_path = (int *)Mem_Alloc(404, gameData, targetColumn, a5);
    if ( raw_path )
      *raw_path = 0;
    return (_DWORD *)raw_path;
  }

  saved_tile_occupant = *(__int16 *)(TILE_INDEX(targetRow, targetColumn));
  *(_WORD *)(TILE_INDEX(targetRow, targetColumn)) = -1;
  WorldMap_DisableFrameRedraw();
  raw_path = Unit_MoveTrack(stackIndex, source_row, targetRow, source_column, targetColumn, targetColumn);
  if ( raw_path )
  {
    reverse_path = (int *)Mem_Alloc(404, (int)raw_path, source_column, targetColumn);
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
  *(_WORD *)(TILE_INDEX(targetRow, targetColumn)) = saved_tile_occupant;
  Render_LoadResourceSprite_v2();
  return (_DWORD *)raw_path;
}
// 415210: could not find valid save-restore pair for ebx
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00415450) --------------------------------------------------------
int * Building_GenerateApproachTrack(int stackIndex, int buildingIndex, int a3, char a4, DWORD a5)
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
  Debug_Log(stackIndex, (char)buildingIndex, a5, (int)aUnit_movetra_0);

  building_record = BUILDING_RECORD(buildingIndex);
  building_row = *(unsigned __int8 *)building_record;
  building_column = *(unsigned __int8 *)(building_record + 1);
  building_kind = *(signed char *)(building_record + 4);
  building_tile = (unsigned __int16)(buildingIndex + 0x8000);

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
  stack_record = UNIT_STACK(stackIndex);
  source_row = UNIT_STACK_TILE_ROW(stack_record);
  source_column = UNIT_STACK_TILE_COLUMN(stack_record);
  raw_path = Unit_MoveTrack(stackIndex, source_row, building_row, source_column, building_kind, building_column);
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
      stackIndex,
      building_row,
      building_column,
      raw_path ? *raw_path : -1);
  return raw_path;
}
// 415450: asm-backed rewrite; clears/restores building footprint around Unit_MoveTrack.
// 5202E4: using guessed type int gameData;

//----- (00415970) --------------------------------------------------------
int  Building_GenerateNearApproachTrack(int stackIndex, int buildingIndex, int a3, char a4, DWORD a5)
{
  int buildingRecordOffset; // edi
  DWORD buildingKind; // ebp
  __int64 v7; // rdi
  int v8; // eax
  int v9; // edx
  int sourceColumn; // ebx
  int *rawPath; // ecx
  int *v12; // eax
  int *v13; // ecx
  int *reversePath; // edx
  int v15; // ebx
  int v16; // eax
  int v17; // ecx
  int v19; // eax
  int v20; // ebx
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // ebx
  __int16 buildingIndexWord; // [esp+8h] [ebp-28h]
  int v27; // [esp+18h] [ebp-18h]

  buildingIndexWord = buildingIndex;
  buildingRecordOffset = 467 * buildingIndex;
  Debug_Log(a3, a4, a5, (int)aUnit_movetra_3);
  HIDWORD(v7) = *(unsigned __int8 *)(gameData + buildingRecordOffset + 509674);
  buildingKind = *(char *)(gameData + buildingRecordOffset + 509678);
  LODWORD(v7) = *(unsigned __int8 *)(gameData + buildingRecordOffset + 509675);
  *(_WORD *)(TILE_INDEX(HIDWORD(v7), v7)) = -1;
  if ( buildingKind == 1 || buildingKind == 2 )
  {
    v8 = 200 * (HIDWORD(v7) + 1);
    *(_WORD *)(v8 + gameData + 2 * v7 + 556374) = -1;
    *(_WORD *)(gameData + v8 + 2 * v7 + 556376) = -1;
    *(_WORD *)(gameData + 200 * HIDWORD(v7) + 2 * v7 + 556376) = -1;
  }
  WorldMap_DisableFrameRedraw();
  v9 *= 145;
  sourceColumn = *(__int16 *)(gameData + 5 * v9 + 147176);
  rawPath = Unit_MoveTrack(stackIndex, *(__int16 *)(gameData + 5 * v9 + 147174), SHIDWORD(v7), sourceColumn, buildingKind, v7);
  if ( rawPath )
  {
    v12 = (int *)Mem_Alloc(404, (int)rawPath, sourceColumn, buildingKind);
    reversePath = v12;
    if ( v12 )
      *v12 = 0;
    for ( ; *v13; reversePath[v20 + 1] = v27 )
    {
      while ( 1 )
      {
        v19 = *v13 - 1;
        *v13 = v19;
        v20 = *reversePath;
        v27 = v13[v19 + 1];
        if ( *reversePath < 100 )
          break;
        if ( !*v13 )
          goto LABEL_8;
      }
      *reversePath = v20 + 1;
    }
LABEL_8:
    while ( *reversePath > 1 )
    {
      v21 = reversePath[*reversePath - 1];
      if ( v7 != __PAIR64__((unsigned __int8)v21, BYTE1(v21)) )
      {
        if ( buildingKind != 1 && buildingKind != 2 )
          break;
        if ( SHIDWORD(v7) > (unsigned __int8)v21 )
          break;
        if ( (unsigned __int8)v21 > HIDWORD(v7) + 1 )
          break;
        v22 = BYTE1(v21);
        if ( (int)v7 > v22 || v22 > (int)v7 + 1 )
          break;
      }
      --*reversePath;
    }
    if ( *reversePath )
      --*reversePath;
    while ( 1 )
    {
      v15 = *reversePath;
      if ( !*reversePath )
        break;
      *reversePath = v15 - 1;
      v23 = reversePath[v15];
      v24 = *v13;
      if ( *v13 < 100 )
      {
        *v13 = v24 + 1;
        v13[v24 + 1] = v23;
      }
    }
    j__nfree_();
  }
  *(_WORD *)(2 * v7 + gameData + 200 * HIDWORD(v7) + 556374) = buildingIndexWord + 0x8000;
  if ( buildingKind == 1 || buildingKind == 2 )
  {
    v16 = 200 * (HIDWORD(v7) + 1);
    *(_WORD *)(v16 + gameData + 2 * v7 + 556374) = buildingIndexWord + 0x8000;
    *(_WORD *)(gameData + v16 + 2 * v7 + 556376) = buildingIndexWord + 0x8000;
    *(_WORD *)(gameData + 200 * HIDWORD(v7) + 2 * v7 + 556376) = buildingIndexWord + 0x8000;
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
BOOL  QueuedPath_StartsAtTile(_DWORD *pathBuffer, int tileRow, int tileColumn)
{
  int firstStep; // eax

  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  return (unsigned __int8)firstStep == tileRow && BYTE1(firstStep) == tileColumn;
}

//----- (00415D00) --------------------------------------------------------
BOOL  QueuedPath_StartsInBuildingFootprint(_DWORD *pathBuffer, int buildingIndex)
{
  unsigned __int8 *buildingRecord; // eax
  int firstStep; // edx
  BOOL result; // eax
  unsigned __int8 buildingColumn; // bh

  buildingRecord = (unsigned __int8 *)(UNIT_RECORD(buildingIndex));
  if ( !*pathBuffer )
    return 0;
  firstStep = pathBuffer[1];
  if ( !buildingRecord[4] )
    return (_WORD)firstStep == *(_WORD *)buildingRecord;
  result = 0;
  if ( (unsigned __int8)firstStep >= *buildingRecord && (unsigned __int8)firstStep <= *buildingRecord + 1 )
  {
    buildingColumn = buildingRecord[1];
    if ( BYTE1(firstStep) >= buildingColumn && BYTE1(firstStep) <= buildingColumn + 1 )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00415D80) --------------------------------------------------------
int  Math_SinDegreesQ16(signed int degrees)
{
  int angle; // edx
  int absAngle; // edx

  angle = degrees;
  if ( degrees < 0 )
  {
    absAngle = -degrees;
    if ( -degrees >= 360 )
      absAngle %= 360;
    return -g_MathSinTableQ16[absAngle];
  }
  else
  {
    if ( degrees >= 360 )
      angle = degrees % 360;
    return g_MathSinTableQ16[angle];
  }
}
// 513434: using guessed type int dword_513434[363];

//----- (00415DD0) --------------------------------------------------------
void  initRandomSeed(char a1, DWORD a2)
{
  int v2; // ecx

  g_RngState = time_();
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

  g_RngState ^= Time_Now(0, 0) + 0x34523471u;
  seed = (unsigned int)g_RngState + 0x83356532u * (unsigned int)Time_Now(0, 0);
  g_RngState = (int)seed;
  range = (unsigned int)((__int64)a2 + 1 - a1);
  if ( !range )
    return (unsigned int)a1;
  result = (int)(seed % range) + a1;
  return (unsigned int)result;
}
// 525578: using guessed type int dword_525578;

//----- (00415E40) --------------------------------------------------------
signed int  Math_CeilSqrt(signed int value)
{
  int quotient; // eax
  int estimate; // ecx

  if ( value < 4 )
    return 1;
  quotient = value / 20 + 2;
  estimate = quotient;
  do
  {
    while ( 1 )
    {
      estimate = (estimate + quotient) / 2;
      quotient = value / estimate;
      if ( estimate - value / estimate <= 0 )
        break;
      if ( estimate - value / estimate <= 1 )
        return estimate;
    }
  }
  while ( value / estimate - estimate > 1 );
  return estimate;
}

//----- (00415EA0) --------------------------------------------------------
__int16  WorldMap_DrawUnitStackOverlayGlyph(int screenX, int screenY, unsigned __int16 *tilePtr)
{
  unsigned int glyphCode; // eax
  int sprite; // eax

  glyphCode = *tilePtr;
  if ( glyphCode >= 0x2D && *tilePtr <= 0x58u )
  {
    LOWORD(glyphCode) = tilePtr[2];
    if ( (unsigned __int16)glyphCode == 0xFFFF )
    {
      TextSprite_SetStyleFlag(1);
      sprite = DLX_GetSpriteForChar(g_TreeSpriteSet, *tilePtr - 45);
      LOWORD(glyphCode) = Compat_RenderDeviceDrawMenuSprite(screenX, screenY, sprite, 1);
    }
  }
  return glyphCode;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202D8: using guessed type int dword_5202D8;

//----- (00415F20) --------------------------------------------------------
int  WorldMap_DrawUnitStackWithOverlays(int result, int screenX, int screenY, int animOffsetY, unsigned __int16 *tilePtr)
{
  int v7; // eax
  int spriteVerticalOffset; // ebp
  int SpriteForChar; // eax
  int drawY; // ebx
  int v11; // eax
  int v12; // eax
  DWORD v13; // ebp
  int v14; // ecx
  signed int squadCount; // eax
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // eax
  int v21; // ecx
  int v22; // [esp+64h] [ebp-20h]
  int v23; // [esp+6Ch] [ebp-18h]
  int stackIndex; // [esp+74h] [ebp-10h]

  stackIndex = result;
  if ( result < 0x8000 )
  {
    result = gameData + 725 * result;
    if ( *(__int16 *)(result + 147180) != -1 )
    {
      if ( !*(_BYTE *)(result + 147894) || (result = *(unsigned __int8 *)(result + 147178), result == g_CurrentPlayerIndex) )
      {
        v7 = gameData + 725 * stackIndex;
        spriteVerticalOffset = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(v7 + 147180)];
        if ( g_ActiveUnitMoveTileIndex == -1 || g_ActiveUnitMoveTileIndex != stackIndex )
          SpriteForChar = UnitSpriteCache_FindEntryOrLoad(
                            *(unsigned __int16 *)(gameData + 725 * stackIndex + 147180),
                            *(_BYTE *)(gameData + 725 * stackIndex + 147178),
                            *(_BYTE *)(gameData + 725 * stackIndex + 147197) & 7,
                            *(_BYTE *)(gameData + 725 * stackIndex + 147179));
        else
          SpriteForChar = DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, 8 * *(unsigned __int8 *)(v7 + 147179) + g_UnitAnimFrameIndex);
        v23 = SpriteForChar;
        v22 = screenX + 63;
        drawY = screenY + animOffsetY - spriteVerticalOffset;
        if ( stackIndex == g_WorldMapAttentionFlashUnitIndex )
        {
          v11 = Time_Now(screenY + 63, spriteVerticalOffset);
          v12 = Math_SinDegreesQ16(30 * (g_WorldMapAttentionFlashStartTick - v11));
          v13 = screenX + 63;
          Sprite_DrawSimpleTrackingOffset(
            v23,
            screenX,
            drawY,
            screenY,
            v22,
            v14,
            ((126 * v12 - (__CFSHL__((126 * v12) >> 31, 16) + ((126 * v12) >> 31 << 16))) >> 16) + 128,
            1u);
        }
        else
        {
          v13 = gameData;
          if ( *(_BYTE *)(725 * stackIndex + gameData + 147894) )
          {
            Sprite_DrawSimpleTrackingOffset(SpriteForChar, screenX, drawY, screenY, v22, screenY + 63, 128, 1u);
          }
          else
          {
            Compat_RenderDeviceDrawMenuSprite(screenX, drawY, SpriteForChar, 1);
          }
        }
        if ( (g_UnitTypeFlags[22 * *(__int16 *)(gameData + 725 * stackIndex + 147180)] & 1) == 0 )
          WorldMap_DrawUnitStackOverlayGlyph(screenX, screenY, tilePtr);
        squadCount = Unit_GetSquadCount(725 * stackIndex + gameData + 147174);
        if ( squadCount > 1 )
        {
          v16 = DLX_GetSpriteForChar(g_MarksSpriteSet, squadCount + 5);
          Compat_RenderDeviceDrawMenuSprite(screenX + 12, drawY + 48, v16, 1);
        }
        if ( UnitStack_HasLowMoraleUnit(725 * stackIndex + gameData + 147174) )
        {
          v18 = DLX_GetSpriteForChar(g_MarksSpriteSet, 33);
          Compat_RenderDeviceDrawMenuSprite(screenX + 30, drawY + 48, v18, 1);
        }
        if ( *(_BYTE *)(gameData + 725 * stackIndex + 147894) )
        {
          v20 = DLX_GetSpriteForChar(g_MarksSpriteSet, 39);
          Compat_RenderDeviceDrawMenuSprite(screenX + 10, drawY + 5, v20, 1);
        }
        if ( stackIndex == g_UnitBlinkFlashUnitIndex )
        {
          v20 = DLX_GetSpriteForChar(g_WhirlSpriteSet, g_UnitBlinkFlashFrame);
          Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v20, 1);
        }
        result = gameData;
        if ( *(_DWORD *)(gameData + 147155) )
        {
          TextSprite_ActivateResourceSlot(3, 76, v13);
          return UI_DrawText(screenX + 20, screenY + 25, (int)aD_0);
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
    g_BuildingSwayJitterOffsetsX[offset] = Rng_RandRange(-20, 20);
    offset += 2;
    result = Rng_RandRange(-20, 20);
    g_BuildingSwayJitterOffsetsOdd[offset] = result;
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
  if ( (unsigned int)(g_MapConstructionSwayAnimLastTick + 20) <= now )
  {
    g_MapConstructionSwayAnimLastTick = Time_Now(0, 0);
    for ( offset = 0; offset != 30; offset += 2 )
    {
      if ( Rng_RandRange(0, 20) > 0x11 )
      {
        if ( g_BuildingSwayJitterOffsetsX[offset] <= 10 || Rng_RandRange(0, 10) <= 5 )
        {
          if ( g_BuildingSwayJitterOffsetsX[offset] >= -10 || Rng_RandRange(0, 10) <= 5 )
          {
            v9 = Rng_RandRange(-1, 1);
            g_BuildingSwayJitterOffsetsX[offset] += v9;
          }
          else
          {
            ++g_BuildingSwayJitterOffsetsX[offset];
          }
        }
        else
        {
          --g_BuildingSwayJitterOffsetsX[offset];
        }
        if ( g_BuildingSwayJitterOffsetsY[offset] <= 10 || Rng_RandRange(0, 10) <= 5 )
        {
          if ( g_BuildingSwayJitterOffsetsY[offset] >= -10 || Rng_RandRange(0, 10) <= 5 )
          {
            v10 = Rng_RandRange(-1, 1);
            g_BuildingSwayJitterOffsetsY[offset] += v10;
          }
          else
          {
            ++g_BuildingSwayJitterOffsetsY[offset];
          }
        }
        else
        {
          --g_BuildingSwayJitterOffsetsY[offset];
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
  if ( (unsigned int)(g_MapIdleBuildingAnimLastTick + 10) <= result )
  {
    g_MapIdleBuildingAnimLastTick = Time_Now(0, 0);
    g_MapFlagAnimationFrame = ((_BYTE)g_MapFlagAnimationFrame + 1) & 0xF;
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
int  WorldMap_DrawUnitAttentionFlashGlow(int screenX, int screenY, unsigned int buildingPhase)
{
  int i; // esi
  int jitterX; // eax
  int drawY; // ebx
  int jitterY; // edx
  int SpriteForChar; // eax
  int result; // eax
  int v9; // edx
  int alpha; // [esp-8h] [ebp-20h]
  int v11; // [esp+8h] [ebp-10h]

  v11 = screenY;
  if ( buildingPhase >= 2 )
  {
    v9 = screenY - 64;
    if ( buildingPhase <= 2 )
    {
      v11 = v9;
    }
    else if ( buildingPhase == 3 )
    {
      v11 = v9;
    }
  }
  for ( i = 0; i != 30; i += 2 )
  {
    jitterX = g_BuildingSwayJitterOffsetsX[i];
    drawY = v11 + g_BuildingSwayJitterOffsetsY[i] + 52;
    if ( jitterX <= 0 )
      jitterX = -jitterX;
    jitterY = g_BuildingSwayJitterOffsetsY[i];
    if ( jitterY <= 0 )
      jitterY = -jitterY;
    alpha = 50 - (jitterX + jitterY) / 3;
    SpriteForChar = DLX_GetSpriteForChar(g_MarksSpriteSet, 36);
    result = Sprite_DrawSimpleTrackingOffset(SpriteForChar, screenX, drawY, screenY, screenX + 63, screenY + 63, alpha, 1u);
  }
  return result;
}
// 5202C8: using guessed type int dword_5202C8;

//----- (00416850) --------------------------------------------------------
int  WorldMap_DrawMapTile(unsigned __int16 screenX, unsigned __int16 screenY, unsigned __int16 *tilePtr)
{
  int tileRow; // edi
  signed int tileColumn; // esi
  int v6; // eax
  int v7; // eax
  int missionIndex; // ebx
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
  signed int fogOverlayClass; // [esp+C4h] [ebp-94h]
  int v95; // [esp+C8h] [ebp-90h]
  int v96; // [esp+CCh] [ebp-8Ch]
  int v97; // [esp+D0h] [ebp-88h]
  int v98; // [esp+D4h] [ebp-84h]
  int drewOverlaySprite; // [esp+D8h] [ebp-80h]
  int stackIndex; // [esp+DCh] [ebp-7Ch]
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

  tileRow = ((int)tilePtr - gameData) / 14 / 100;
  tileColumn = ((int)tilePtr - gameData) / 14 % 100;
  v95 = (unsigned __int16)(screenY + 63);
  v96 = (unsigned __int16)(screenX + 63);
  v97 = screenY;
  v98 = screenX;
  if ( MiniMap_IsSpanWithinViewportBounds(screenX, screenY + 63) )
    goto LABEL_2;
  fogOverlayClass = Map_ClassifyFogOfWarOverlayForPlayer(tileRow, tileColumn, VIEWED_PLAYER_INDEX);
  if ( !fogOverlayClass )
  {
    Compat_RenderDeviceFillSolidRect(v98, v97, v96, v95, 1u);
    goto LABEL_2;
  }
  if ( *(_BYTE *)(gameData + 140016) == 2 )
  {
    v61 = *tilePtr;
    if ( v61 != 0xFFFF )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v61]);
      Compat_RenderDeviceDrawMenuSprite(v98, v97, SpriteForChar, 0);
    }
    v63 = tilePtr[1];
    if ( v63 != 0xFFFF )
    {
      v64 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v63]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v64, 1);
    }
  }
  else
  {
    if ( *tilePtr != 0xFFFF && (*tilePtr < 0xCFu || *tilePtr > 0xD2u) )
    {
      HIWORD(v58) = 0;
      if ( *tilePtr != 187 )
      {
        LOWORD(v58) = *tilePtr;
        v59 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v58]);
        Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v59, 0);
      }
    }
    if ( tilePtr[1] != 0xFFFF && (tilePtr[1] < 0xD3u || tilePtr[1] > 0xD7u) )
    {
      v60 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[tilePtr[1]]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v60, 1);
    }
  }
  v6 = tilePtr[2];
  if ( v6 != 0xFFFF )
  {
    v7 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v6]);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v7, 1);
  }
  missionIndex = ACTIVE_MISSION_INDEX;
  if ( missionIndex == 7 )
  {
    WorldMap_DrawMission07TreasureMarker(tileRow, tileColumn);
  }
  else if ( missionIndex == 17 )
  {
    WorldMap_DrawMission17TreasureMarker(tileRow, tileColumn);
  }
  if ( tilePtr[2] < 0x362u || tilePtr[2] > 0x36Cu )
  {
    if ( tileColumn <= 0 )
      v65 = -1;
    else
      v65 = *(tilePtr - 5);
    if ( v65 >= 0x364u && v65 <= 0x369u || v65 == 866 )
    {
      v66 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 863);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v66, 1);
    }
    if ( tileColumn >= 99 )
      v67 = -1;
    else
      v67 = tilePtr[9];
    if ( v67 >= 0x367u && v67 <= 0x36Cu || v67 == 866 )
    {
      v68 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 862);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v68, 1);
    }
    if ( tileRow <= 0 )
      v69 = -1;
    else
      v69 = *(tilePtr - 698);
    if ( v69 >= 0x363u && v69 <= 0x365u || v69 == 871 || v69 == 872 || v69 == 874 || v69 == 875 )
    {
      v70 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 864);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v70, 1);
    }
    if ( tileRow >= 99 )
      v71 = -1;
    else
      v71 = tilePtr[702];
    if ( v71 == 873 || v71 == 875 || v71 == 876 || v71 == 867 || v71 == 869 || v71 == 870 || v71 == 872 )
    {
      v72 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 865);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v72, 1);
    }
    if ( tileColumn >= 2 )
    {
      v73 = *(unsigned __int16 *)(2 * tileColumn + 200 * tileRow + gameData + 556370);
      if ( (unsigned __int16)v73 >= 0x8000u && *(unsigned __int16 *)(2 * tileColumn + 200 * tileRow + gameData + 556370) != 0xFFFF )
      {
        v74 = (unsigned __int8 *)(gameData + 509674 + 467 * (v73 - 0x8000));
        v75 = (char)v74[4];
        if ( (v75 == 2 || v75 == 1) && *v74 == tileRow && v74[1] == tileColumn - 2 && !*((_WORD *)v74 + 8) )
        {
          v76 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 863);
          Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v76, 1);
        }
      }
    }
  }
  if ( ((1 << g_CurrentPlayerIndex) & *(unsigned __int8 *)(tileColumn + gameData + 100 * tileRow + 576374)) == 1 << g_CurrentPlayerIndex )
  {
    v9 = DLX_GetSpriteForChar(g_MarksSpriteSet, 6);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v9, 1);
  }
  drewOverlaySprite = 0;
  stackIndex = *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn));
  v101 = 0;
  if ( g_ActiveUnitMoveTileIndex == stackIndex )
    v101 = g_UnitMoveAnimOffsetY;
  if ( *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn)) <= 0x7FFFu
    && (g_UnitTypeFlags[22 * *(__int16 *)(gameData + 725 * stackIndex + 147180)] & 1) != 0 )
  {
    drewOverlaySprite = 1;
    v10 = tilePtr[1];
    if ( v10 != 0xFFFF && tilePtr[1] >= 0xD3u && tilePtr[1] <= 0xD7u )
    {
      v11 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v10]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v11, 1);
    }
    if ( *tilePtr != 0xFFFF && (*tilePtr >= 0xCFu && *tilePtr <= 0xD2u || *tilePtr == 187) )
    {
      v77 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[*tilePtr]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v77, 1);
    }
    WorldMap_DrawUnitStackWithOverlays(stackIndex, screenX, screenY, v101, tilePtr);
  }
  else
  {
    WorldMap_DrawUnitStackWithOverlays(stackIndex, screenX, screenY, v101, tilePtr);
    v77 = tilePtr[1];
    if ( v77 != 0xFFFF && tilePtr[1] >= 0xD3u && tilePtr[1] <= 0xD7u )
    {
      v78 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v77]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v78, 1);
    }
    if ( *tilePtr != 0xFFFF && (*tilePtr >= 0xCFu && *tilePtr <= 0xD2u || *tilePtr == 187) )
    {
      v79 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[*tilePtr]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v79, 1);
    }
  }
  v12 = 0;
  if ( tileColumn > 0 )
  {
    v13 = *(_WORD *)(200 * tileRow + gameData + 2 * tileColumn + 556372);
    v109 = v13;
    if ( v13 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v13) )
      {
        if ( v14 == g_ActiveUnitMoveTileIndex )
          v12 = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(v109, screenX, screenY, v12 - 64, (unsigned __int16 *)(1400 * tileRow + gameData + 14 * (tileColumn - 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn > 0 && tileRow > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v15 = *(__int16 *)(200 * (tileRow - 1) + gameData + 2 * tileColumn + 556372);
    if ( v15 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v15, screenX, screenY, g_UnitMoveAnimOffsetY - 64, (unsigned __int16 *)(gameData + 1400 * v16 + 14 * (tileColumn - 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn < *(_DWORD *)(gameData + 140004) - 1 && tileRow < *(_DWORD *)(gameData + 140000) && g_ActiveUnitMoveTileIndex != -1 )
  {
    v17 = *(__int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556376);
    if ( v17 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v17, screenX, screenY, g_UnitMoveAnimOffsetY + 64, (unsigned __int16 *)(gameData + 1400 * (tileRow + 1) + 14 * (tileColumn + 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileRow > 0 )
  {
    v18 = *(_WORD *)(TILE_INDEX((tileRow - 1), tileColumn));
    v113 = v18;
    if ( v18 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v18) )
      {
        v20 = 0;
        if ( v19 == g_ActiveUnitMoveTileIndex )
          v20 = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(v113, screenX, screenY, v20, (unsigned __int16 *)(gameData + 1400 * (tileRow - 1) + 14 * tileColumn));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn < *(_DWORD *)(gameData + 140004) - 1 )
  {
    v21 = *(_WORD *)(200 * tileRow + gameData + 2 * tileColumn + 556376);
    v112 = v21;
    if ( v21 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v21) )
      {
        v23 = 0;
        if ( v22 == g_ActiveUnitMoveTileIndex )
          v23 = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(v112, screenX, screenY, v23 + 64, (unsigned __int16 *)(1400 * tileRow + gameData + 14 * (tileColumn + 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn < *(_DWORD *)(gameData + 140004) - 1 && tileRow > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v24 = *(__int16 *)(200 * (tileRow - 1) + gameData + 2 * tileColumn + 556376);
    if ( v24 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v24, screenX, screenY, g_UnitMoveAnimOffsetY + 64, (unsigned __int16 *)(1400 * (tileRow - 1) + gameData + 14 * (tileColumn + 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileColumn > 0 && tileRow < *(_DWORD *)(gameData + 140000) - 1 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v25 = *(__int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556372);
    if ( v25 == g_ActiveUnitMoveTileIndex )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
      {
        WorldMap_DrawUnitStackWithOverlays(v25, screenX, screenY, g_UnitMoveAnimOffsetY - 64, (unsigned __int16 *)(gameData + 1400 * v26 + 14 * (tileColumn - 1)));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( tileRow < *(_DWORD *)(gameData + 140000) - 1 )
  {
    v27 = *(_WORD *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556374);
    v114 = v27;
    if ( v27 >= 0 )
    {
      if ( Unit_GetSpriteVerticalOffsetPx(v27) )
      {
        v29 = 0;
        if ( v28 == g_ActiveUnitMoveTileIndex )
          v29 = g_UnitMoveAnimOffsetY;
        WorldMap_DrawUnitStackWithOverlays(v114, screenX, screenY, v29, (unsigned __int16 *)(1400 * (tileRow + 1) + gameData + 14 * tileColumn));
        drewOverlaySprite = 1;
      }
    }
  }
  if ( g_ActiveUnitMoveTileIndex != -1 )
  {
    if ( tileColumn > 0 )
    {
      v30 = *(unsigned __int16 *)(200 * tileRow + gameData + 2 * tileColumn + 556372);
      if ( v30 != 0xFFFF && g_UnitMoveAnimOffsetY > 0 && v30 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v30, screenX, screenY, g_UnitMoveAnimOffsetY - 64, tilePtr);
    }
    if ( tileColumn < *(_DWORD *)(gameData + 140004) - 1 )
    {
      v31 = *(unsigned __int16 *)(200 * tileRow + gameData + 2 * tileColumn + 556376);
      if ( v31 != 0xFFFF && g_UnitMoveAnimOffsetY < 0 && v31 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v31, screenX, screenY, g_UnitMoveAnimOffsetY + 64, tilePtr);
    }
    if ( tileRow > 0 )
    {
      v32 = *(unsigned __int16 *)(TILE_INDEX((tileRow - 1), tileColumn));
      if ( v32 != 0xFFFF && g_UnitMoveAnimOffsetX > 0 && v32 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v32, screenX, screenY, g_UnitMoveAnimOffsetY, tilePtr);
    }
    if ( tileRow < *(_DWORD *)(gameData + 140000) - 1 )
    {
      v33 = *(unsigned __int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556374);
      if ( v33 != 0xFFFF && g_UnitMoveAnimOffsetX < 0 && v33 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v33, screenX, screenY, g_UnitMoveAnimOffsetY, tilePtr);
    }
    if ( tileRow > 0 && tileColumn > 0 )
    {
      v34 = *(unsigned __int16 *)(gameData + 200 * (tileRow - 1) + 2 * tileColumn + 556372);
      if ( v34 != 0xFFFF && g_UnitMoveAnimOffsetY > 0 && g_UnitMoveAnimOffsetX > 0 && v34 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v34, screenX, screenY, g_UnitMoveAnimOffsetY - 64, tilePtr);
    }
    if ( tileRow > 0 && tileColumn < *(_DWORD *)(gameData + 140004) )
    {
      v35 = *(unsigned __int16 *)(200 * (tileRow - 1) + gameData + 2 * tileColumn + 556376);
      if ( v35 != 0xFFFF && g_UnitMoveAnimOffsetY < 0 && g_UnitMoveAnimOffsetX > 0 && v35 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v35, screenX, screenY, g_UnitMoveAnimOffsetY + 64, tilePtr);
    }
    if ( tileColumn > 0 && tileRow < *(_DWORD *)(gameData + 140000) )
    {
      v36 = *(unsigned __int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556372);
      if ( v36 != 0xFFFF && g_UnitMoveAnimOffsetY > 0 && g_UnitMoveAnimOffsetX < 0 && v36 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v36, screenX, screenY, g_UnitMoveAnimOffsetY - 64, tilePtr);
    }
    v37 = *(_DWORD *)(gameData + 140000);
    if ( tileColumn < v37 && tileRow < v37 )
    {
      v38 = *(unsigned __int16 *)(200 * (tileRow + 1) + gameData + 2 * tileColumn + 556376);
      if ( v38 != 0xFFFF && g_UnitMoveAnimOffsetY < 0 && g_UnitMoveAnimOffsetX < 0 && v38 == g_ActiveUnitMoveTileIndex )
        WorldMap_DrawUnitStackWithOverlays(v38, screenX, screenY, g_UnitMoveAnimOffsetY + 64, tilePtr);
    }
  }
  v39 = *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn));
  if ( (unsigned __int16)v39 >= 0x8000u && *(unsigned __int16 *)(TILE_INDEX(tileRow, tileColumn)) != 0xFFFF )
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
    v103 = tileRow + 2 * (tileColumn - v46[509675]) - v46[509674];
    v47 = BuildingSpriteCache_GetOrLoadEntry(v44, v46[509676], v45, v46[509677], v103);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v47, 1);
    if ( *(__int16 *)(v102 + 16) == -1 && *(_BYTE *)(v102 + 4) )
    {
      WorldMap_DrawUnitAttentionFlashGlow(screenX, screenY, v103);
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
      v81 = DLX_GetSpriteForChar(g_FlagSpriteSet, 16 * *(unsigned __int8 *)(v102 + 2) + building_flag_variant + g_MapFlagAnimationFrame);
      Compat_RenderDeviceDrawMenuSprite(building_flag_x, v108, v81, 1);
    }
  }
  if ( !drewOverlaySprite && *(_BYTE *)(gameData + 140016) != 2 )
  {
    v82 = tilePtr[1];
    if ( v82 != 0xFFFF && tilePtr[1] >= 0xD3u && tilePtr[1] <= 0xD7u )
    {
      v83 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v82]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v83, 1);
    }
    v84 = *tilePtr;
    if ( *tilePtr != 0xFFFF && (*tilePtr >= 0xCFu && *tilePtr <= 0xD2u || v84 == 187) )
    {
      v85 = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, (unsigned __int16)g_Font_GlyphRemapTable[v84]);
      Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v85, 1);
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
            if ( (unsigned __int8)v105 == tileRow )
            {
              v89 = tileRow ^ (unsigned __int8)v105;
              LOBYTE(v89) = BYTE1(v88[1]);
              if ( v89 == tileColumn )
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
        v91 = DLX_GetSpriteForChar(g_MovePathStepSpriteSet, v86);
        Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v91, 1);
        if ( !drewOverlaySprite )
          WorldMap_DrawUnitStackOverlayGlyph(screenX, screenY, tilePtr);
      }
    }
  }
LABEL_133:
  if ( stackIndex == g_SelectedUnitIndex && g_ActiveUnitMoveTileIndex == -1 && PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
  {
    v52 = DLX_GetSpriteForChar(g_MarksSpriteSet, *(unsigned __int8 *)(gameData + 140016) == 1);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v52, 1);
  }
  if ( tileRow == g_BlinkFlashTileX && tileColumn == g_BlinkFlashTileY )
  {
    v52 = DLX_GetSpriteForChar(g_WhirlSpriteSet, g_TileBlinkFlashFrame + 12);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v52, 1);
  }
  v53 = ACTIVE_MISSION_INDEX;
  if ( v53 == 1 )
  {
    WorldMap_DrawMission01ShrineMarker(tileRow, tileColumn, screenY, screenX);
  }
  else if ( v53 == 11 )
  {
    WorldMap_DrawMission11ShrineMarker(tileRow, tileColumn, screenY, screenX);
  }
  if ( fogOverlayClass != -1 )
  {
    TextSprite_SetStyleFlag(1);
    v55 = DLX_GetSpriteForChar(g_FogOverlaySpriteSet, fogOverlayClass);
    Compat_RenderDeviceDrawMenuSprite(screenX, screenY, v55, 1);
  }
  UI_DrawTileHighlightOverlay(tileRow, tileColumn, screenY, screenX);
  if ( g_WorldMapTileOverlayDrawHook )
    g_WorldMapTileOverlayDrawHook(v56, tileColumn);
  if ( *(_DWORD *)(gameData + 147155) )
  {
    if ( *(_BYTE *)(gameData + 140016) == 1 )
      v57 = -9;
    else
      v57 = 76;
    TextSprite_ActivateResourceSlot(3, v57, v48);
    UI_DrawText(screenX, screenY, (int)aDD_0);
  }
LABEL_2:
  if ( *(_DWORD *)(gameData + 147151) )
  {
    if ( tileColumn > *(_DWORD *)(gameData + 140012) )
      Compat_RenderDeviceFillSolidRect(screenX, screenY, (unsigned __int16)(screenX + 63), screenY, 1u);
    if ( tileRow > *(_DWORD *)(gameData + 140008) )
      Compat_RenderDeviceFillSolidRect(screenX, screenY, screenX, (unsigned __int16)(screenY + 63), 1u);
  }
  return MiniMap_BlitDirtyRectAndDrawViewportBox(screenX, screenY, screenY + 63, screenX + 63);
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
int  WorldMap_RedrawViewport(int presentCursorOverlay)
{
  int rowIndex; // edi
  int colIndex; // ecx
  int screenX; // esi
  int result; // eax
  int v6; // edi
  unsigned __int16 v7; // si
  int v8; // ebp
  int v9; // esi
  unsigned __int16 screenY; // [esp+4h] [ebp-2Ch]
  int v11; // [esp+8h] [ebp-28h]
  int v12; // [esp+10h] [ebp-20h]

  rowIndex = 0;
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  screenY = 16;
  do
  {
    colIndex = 0;
    screenX = 32;
    do
    {
      result = WorldMap_DrawMapTile(
                 screenX,
                 screenY,
                 (unsigned __int16 *)(gameData
                                    + 1400 * (colIndex + *(_DWORD *)(gameData + 140008))
                                    + 14 * (rowIndex + *(_DWORD *)(gameData + 140012))));
      ++colIndex;
      screenX += 64;
    }
    while ( colIndex < 9 );
    ++rowIndex;
    screenY += 64;
  }
  while ( rowIndex < 6 );
  if ( !g_UnitStackSelectionModeActive )
  {
    colIndex = 0;
    v9 = 32;
    do
    {
      result = WorldMap_DrawMapTile(
                 v9,
                 ((_WORD)rowIndex << 6) + 16,
                 (unsigned __int16 *)(14 * (rowIndex + *(_DWORD *)(gameData + 140012))
                                    + gameData
                                    + 1400 * (colIndex + *(_DWORD *)(gameData + 140008))));
      ++colIndex;
      v9 += 64;
    }
    while ( colIndex < 6 );
  }
  if ( g_WorldMapDrawExtensionHook )
    result = g_WorldMapDrawExtensionHook();
  if ( presentCursorOverlay )
  {
    v12 = g_MouseCursorRawX >> g_CursorCoordShift;
    LOWORD(colIndex) = *(_WORD *)(g_ActiveCursorDescriptorPtr + 12);
    v6 = colIndex + (g_MouseCursorRawX >> g_CursorCoordShift);
    v11 = g_MouseCursorRawY >> g_CursorCoordShift;
    v7 = *(_WORD *)(g_ActiveCursorDescriptorPtr + 16) + (g_MouseCursorRawY >> g_CursorCoordShift);
    v8 = g_CursorOverlayPresented;
    if ( (unsigned __int16)(g_MouseCursorRawX >> g_CursorCoordShift) < 0x20u )
    {
      LOWORD(v12) = 32;
      if ( g_CursorOverlayPresented )
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
    if ( g_MouseCursorRawX >> g_CursorCoordShift < 52 || g_MouseCursorRawY >> g_CursorCoordShift < 36 )
      Render_Pump();
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 16, 32, 0x25Fu, v11, 0x20u, 0x10u);
    Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)v11, 32, v12, v7, 0x20u, v11);
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= 52 && g_MouseCursorRawY >> g_CursorCoordShift >= 36 )
      Input_Flush();
    result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)v11, (unsigned __int16)v12, v6, v7, v12, v11);
    if ( v8 )
      result = Render_Present((int)&g_RenderState);
    if ( (unsigned __int16)v6 != 607 )
      result = Render_FillRect(
                 (_DWORD *)g_PrimaryRenderSurface,
                 0,
                 (unsigned __int16)v11,
                 (unsigned __int16)v6,
                 0x25Fu,
                 v7,
                 v6,
                 v11);
    if ( v7 != 463 )
      return Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, v7, 32, 0x25Fu, 0x1CFu, 0x20u, v7);
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
int  WorldMap_RedrawTileIfVisible(int result, int tileColumn)
{
  int v2; // ebx
  unsigned __int16 screenX; // si
  unsigned __int16 screenY; // di
  int cursorPresented; // ebp

  if ( result < *(_DWORD *)(gameData + 140008) + 9
    && tileColumn < *(_DWORD *)(gameData + 140012) + 7
    && result >= *(_DWORD *)(gameData + 140008) )
  {
    v2 = *(_DWORD *)(gameData + 140012);
    if ( tileColumn >= v2
      && (tileColumn != v2 + 6 || result - *(_DWORD *)(gameData + 140008) < 6)
      && (tileColumn != *(_DWORD *)(gameData + 140012) + 6 || !g_UnitStackSelectionModeActive) )
    {
      screenX = (((_WORD)result - *(_WORD *)(gameData + 140008)) << 6) + 32;
      screenY = (((_WORD)tileColumn - *(_WORD *)(gameData + 140012)) << 6) + 16;
      g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
      WorldMap_DrawMapTile(screenX, screenY, (unsigned __int16 *)(14 * tileColumn + gameData + 1400 * result));
      cursorPresented = g_CursorOverlayPresented;
      RenderState_PumpIfRectInViewBounds(g_RenderState, screenX, screenX + 64, screenY, screenY + 64);
      result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, screenY, screenX, screenX + 63, screenY + 63, screenX, screenY);
      if ( cursorPresented )
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
int  UI_CenterWorldMapViewportOnRectIfFit(int result, int rectColMin, int rectColMax, int rectRowMax)
{
  int mapWidthTiles; // ecx
  int mapHeightTiles; // ebx

  if ( rectRowMax - result <= 9 && rectColMax - rectColMin <= 7 )
  {
    *(_DWORD *)(gameData + 140008) = (rectRowMax + result) / 2 - 3;
    *(_DWORD *)(gameData + 140012) = (rectColMax + rectColMin) / 2 - 3;
    mapWidthTiles = *(_DWORD *)(gameData + 140000);
    if ( *(_DWORD *)(gameData + 140008) + 9 >= mapWidthTiles )
      *(_DWORD *)(gameData + 140008) = mapWidthTiles - 10;
    mapHeightTiles = *(_DWORD *)(gameData + 140004);
    if ( *(_DWORD *)(gameData + 140012) + 7 >= mapHeightTiles )
      *(_DWORD *)(gameData + 140012) = mapHeightTiles - 8;
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
int  UI_CenterWorldMapViewportOnTile(int tileRow, int tileColumn)
{
  int mapWidthTiles; // ecx
  int mapHeightTiles; // ebx

  *(_DWORD *)(gameData + 140008) = tileRow - 3;
  *(_DWORD *)(gameData + 140012) = tileColumn - 3;
  mapWidthTiles = *(_DWORD *)(gameData + 140000);
  if ( *(_DWORD *)(gameData + 140008) + 9 >= mapWidthTiles )
    *(_DWORD *)(gameData + 140008) = mapWidthTiles - 10;
  mapHeightTiles = *(_DWORD *)(gameData + 140004);
  if ( *(_DWORD *)(gameData + 140012) + 7 >= mapHeightTiles )
    *(_DWORD *)(gameData + 140012) = mapHeightTiles - 8;
  if ( *(int *)(gameData + 140008) < 0 )
    *(_DWORD *)(gameData + 140008) = 0;
  if ( *(int *)(gameData + 140012) < 0 )
    *(_DWORD *)(gameData + 140012) = 0;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;

//----- (00418D90) --------------------------------------------------------
int  UI_StartWorldMapUnitAttentionFlash(int unitIndex, int a2, int a3)
{
  int result; // eax

  g_WorldMapAttentionFlashUnitIndex = unitIndex;
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
  int flashUnitIndex; // eax

  if ( g_WorldMapAttentionFlashUnitIndex != -1 )
  {
    WorldMap_RedrawTileIfVisible(
      *(__int16 *)(gameData + 725 * g_WorldMapAttentionFlashUnitIndex + 147174),
      *(__int16 *)(gameData + 725 * g_WorldMapAttentionFlashUnitIndex + 147176));
    if ( (unsigned int)(30 * (Time_Now(v1, v0) - g_WorldMapAttentionFlashStartTick)) >= 0x708 )
    {
      flashUnitIndex = g_WorldMapAttentionFlashUnitIndex;
      g_WorldMapAttentionFlashUnitIndex = -1;
      Map_RedrawUnitFootprintByIndex(flashUnitIndex);
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
int  UI_StartUnitBlinkFlash(int unitIndex, int a2, int a3)
{
  int result; // eax

  g_UnitBlinkFlashUnitIndex = unitIndex;
  result = Time_Now(a3, a2);
  g_UnitBlinkFlashTickTime = result;
  g_UnitBlinkFlashFrame = 0;
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
  int flashUnitIndex; // eax

  if ( g_UnitBlinkFlashUnitIndex != -1 && Time_Now(a1, a2) > (unsigned int)(g_UnitBlinkFlashTickTime + 10) )
  {
    v3 = Time_Now(v2, g_UnitBlinkFlashTickTime + 10);
    g_UnitBlinkFlashFrame += (v3 - g_UnitBlinkFlashTickTime) / 0xAu;
    g_UnitBlinkFlashTickTime = Time_Now(10, (v3 - g_UnitBlinkFlashTickTime) % 0xAu);
    flashUnitIndex = g_UnitBlinkFlashUnitIndex;
    if ( g_UnitBlinkFlashFrame >= 12 )
      g_UnitBlinkFlashUnitIndex = -1;
    Map_RedrawUnitFootprintByIndex(flashUnitIndex);
  }
}
// 418E70: variable 'v2' is possibly undefined
// 5139F8: using guessed type int dword_5139F8;
// 5269A0: using guessed type int dword_5269A0;
// 5269A4: using guessed type int dword_5269A4;

//----- (00418EC0) --------------------------------------------------------
int  UI_StartTileBlinkFlash(int tileX, int tileY, int a3)
{
  int result; // eax

  g_BlinkFlashTileY = tileY;
  g_BlinkFlashTileX = tileX;
  g_TileBlinkFlashFrame = 0;
  result = Time_Now(a3, 0);
  g_TileBlinkFlashTickTime = result;
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
  int tileX; // eax

  if ( g_BlinkFlashTileX != -1 && Time_Now(a1, a2) > (unsigned int)(g_TileBlinkFlashTickTime + 10) )
  {
    v3 = Time_Now(v2, g_TileBlinkFlashTickTime + 10);
    g_TileBlinkFlashFrame += (v3 - g_TileBlinkFlashTickTime) / 0xAu;
    g_TileBlinkFlashTickTime = Time_Now(10, (v3 - g_TileBlinkFlashTickTime) % 0xAu);
    tileX = g_BlinkFlashTileX;
    if ( g_TileBlinkFlashFrame >= 8 )
      g_BlinkFlashTileX = -1;
    WorldMap_RedrawTileIfVisible(tileX, g_BlinkFlashTileY);
  }
}
// 418F00: variable 'v2' is possibly undefined
// 5269A8: using guessed type int dword_5269A8;
// 5269AC: using guessed type int dword_5269AC;
// 5269B0: using guessed type int dword_5269B0;

//----- (00418F60) --------------------------------------------------------
signed int  UI_HighlightTile(int tileX, int tileY)
{
  signed int slot_index; // eax

  slot_index = 0;
  while ( tileX != g_TileHighlightSlots[slot_index].tile_x || tileY != g_TileHighlightSlots[slot_index].tile_y )
  {
    ++slot_index;
    if ( slot_index >= 8 )
    {
      slot_index = 0;
      if ( g_TileHighlightSlots[0].tile_x == -1 )
      {
LABEL_8:
        g_TileHighlightSlots[slot_index].tile_x = tileX;
        g_TileHighlightSlots[slot_index].tile_y = tileY;
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
int  UI_DrawTileHighlightOverlay(int tileX, int tileY, int screenLeft, int screenTop)
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
  while ( tileX != g_TileHighlightSlots[slot_index].tile_x || tileY != g_TileHighlightSlots[slot_index].tile_y )
  {
    ++slot_index;
    if ( slot_index >= 8 )
      return Noop_WorldMapFrameRedrawHook();
  }
  SpriteWidth = DLX_GetSpriteWidth(g_MarksSpriteSet, 0x28u);
  centered_x = screenLeft + (64 - SpriteWidth) / 2;
  SpriteHeight = DLX_GetSpriteHeight(g_MarksSpriteSet, 0x28u);
  centered_y = screenTop + (64 - SpriteHeight) / 2;
  SpriteForChar = DLX_GetSpriteForChar(g_MarksSpriteSet, 40);
  return Sprite_DrawSimpleTrackingOffset(SpriteForChar, centered_y, centered_x, screenLeft, screenTop + 63, screenLeft + 63, 80, 1u);
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
    g_BattleInProgressFlag = 0;
  }
}
// 526A1C: using guessed type int logEnabled;
// 526A20: using guessed type int dword_526A20;

//----- (00419110) --------------------------------------------------------
int  Battle_StoreLastOutcomeValue(int result)
{
  g_BattleInProgressFlag = result;
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
    if ( a2 && g_RenderDevice != &g_MainRenderDevice )
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
    if ( g_RenderDevice == &g_MainRenderDevice && g_CursorOverlayPresented )
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
    source = &g_MainRenderDevice;
  if ( !destination )
    destination = &g_MainRenderDevice;
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
              destination_row[destination_x] = (unsigned char)g_Render_BackgroundColorIndex;
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
    v33 = g_CursorOverlayPresented;
    if ( a2 && g_CursorOverlayPresented )
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
        if ( g_ActiveDialogAnimationTickHook )
          g_ActiveDialogAnimationTickHook();
      }
      result = Render_FillRect((_DWORD *)v12, 0, 0, 0, v37, v36, *a1, a1[2]);
      if ( g_RenderDevice != &g_MainRenderDevice )
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
  g_ActiveWidgetSpriteTableIndex = result;
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

  v31 = g_ActiveTextSpriteSlot;
  Render_ReleaseSurface(g_ActiveWidgetSpriteTableIndex, a2);
  v35 = g_RenderDevice;
  v38 = g_MouseCursorRawY >> g_CursorCoordShift;
  v2 = g_MouseCursorRawX >> g_CursorCoordShift;
  v32 = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)(a1 + 4 * (unsigned __int8)g_LanguageIndex + 36))
      + (g_MouseCursorRawX >> g_CursorCoordShift);
  TextXOffset = UI_GetTextXOffset(g_ActiveTextSpriteSlot);
  v5 = TextXOffset + v4;
  v37 = v2;
  v6 = v32;
  v39 = v5;
  if ( v2 + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12) > v32 )
    v32 = v2 + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12);
  v7 = *(_DWORD *)(g_ActiveCursorDescriptorPtr + 16);
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
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
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
    queen_cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    queen_cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
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
    int garrison_cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    int garrison_cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
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
  if ( g_MouseCursorRawX >> g_CursorCoordShift < *(_DWORD *)a1 || g_MouseCursorRawY >> g_CursorCoordShift < *(_DWORD *)(a1 + 4) )
    goto LABEL_29;
  v4 = *(_DWORD *)(a1 + 20) == -1 ? *(_DWORD *)(a1 + 16) : *(_DWORD *)(a1 + 20);
  if ( g_MouseCursorRawX >> g_CursorCoordShift >= *(_DWORD *)a1
                                    + (unsigned __int16)DLX_GetSpriteHeight(sprite_set_handle, v4)
                                    - 1 )
    goto LABEL_29;
  v5 = *(_DWORD *)(a1 + 20);
  if ( v5 == -1 )
    v5 = *(_DWORD *)(a1 + 16);
  if ( g_MouseCursorRawY >> g_CursorCoordShift >= *(_DWORD *)(a1 + 4)
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
  if ( !g_TooltipCursorActive && has_tooltip )
  {
    g_SavedCursorDescriptor = g_ActiveCursorDescriptorPtr;
    RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
    g_TooltipCursorActive = 1;
    return result;
  }
  if ( !g_TooltipCursorActive || has_tooltip )
    return result;
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_SavedCursorDescriptor);
  g_TooltipCursorActive = 0;
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
        __int16 *slotRecordArg,
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
  int panelTop; // [esp+78h] [ebp-2Ch]
  int v45; // [esp+7Ch] [ebp-28h]
  DWORD v46; // [esp+80h] [ebp-24h]
  void *v47; // [esp+84h] [ebp-20h]
  int v48; // [esp+88h] [ebp-1Ch]
  char *(**unitMetadata)[102]; // [esp+8Ch] [ebp-18h]
  int panelLeft; // [esp+90h] [ebp-14h]
  __int16 *slotRecord; // [esp+94h] [ebp-10h]

  v6 = a6;
  panelLeft = a1;
  panelTop = a2;
  slotRecord = slotRecordArg;
  unitMetadata = &g_UnitTypeMetadataRecords + 22 * *slotRecordArg;
  v7 = (_DWORD *)Mem_Alloc(4112, a3, (char)slotRecordArg, a5);
  if ( v7 )
    v7 = DLXSpriteSet_Load(v7, (char)slotRecordArg);
  v42 = v7;
  Render_ReleaseSurface(7, a5);
  if ( *(unsigned __int8 *)(v9 + 2) == g_CurrentPlayerIndex )
  {
    if ( v8 )
      DLXSpriteSet_DrawText((int)v42, 0, v8, (unsigned __int8 *)g_MapPalettePtr);
    v10 = (int)v42;
    v11 = 0;
  }
  else
  {
    if ( v8 )
      DLXSpriteSet_DrawText((int)v42, 1, v8, (unsigned __int8 *)g_MapPalettePtr);
    v11 = 1;
    v10 = (int)v42;
  }
  SpriteForChar = DLX_GetSpriteForChar(v10, v11);
  v13 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(v13 + 52))(
    panelTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    0);
  if ( *((char *)slotRecord + 9) < 100 )
  {
    v47 = g_RenderDevice;
    Surface = (_DWORD *)Mem_Alloc(188, v14, panelLeft, v13);
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
    v41 = 106 * (100 - *((char *)slotRecord + 9)) / 100 + 5;
    v19 = DLX_GetSpriteHeight((int)v42, 2u);
    Render_FillRect(Surface, g_RenderDevice, 5, 0, v19 - 1, v41, panelLeft + 42, panelTop + 5);
    if ( Surface )
      (*(void (**)(void))Surface[46])();
  }
  UI_DrawTextFmt(a6, panelLeft + 64, panelLeft + 192, panelTop + 5, 3, (int)(**unitMetadata)[(unsigned __int8)g_LanguageIndex]);
  if ( *((unsigned __int8 *)slotRecord + 2) == g_CurrentPlayerIndex )
  {
    v48 = panelTop + 95;
    v43 = panelLeft + 85;
    v20 = panelLeft + 105;
    if ( *((_BYTE *)unitMetadata + 25) )
    {
      if ( *((_BYTE *)unitMetadata + 22) )
      {
        UI_IconIndexFromStats(slotRecord);
        UI_DrawTextFmt(a6, v43, v20, panelTop + 74, 2, (int)aD_12);
        Unit_GetBaseC(slotRecord);
        v13 = v48;
        UI_DrawTextFmt(a6, v43, v20, v48, 2, (int)aD_13);
      }
      else
      {
        DLX_GetSpriteForChar((int)v42, 10);
        v46 = *((_DWORD *)g_RenderDevice + 46);
        v13 = v46;
        (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(v46 + 52))(-1, -1, -1, -1, 1, 0, 0);
        Unit_GetBaseC(slotRecord);
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
      UI_IconIndexFromStats(slotRecord);
      v13 = v48;
      UI_DrawTextFmt(a6, v43, v20, v48, 2, (int)aD_1);
    }
    UI_DrawTextFmt(a6, panelLeft + 85, panelLeft + 105, panelTop + 50, 2, (int)aD_14);
    if ( (unsigned int)*(char *)(v21 + 11) > 4 )
    {
      v32 = *((char *)slotRecord + 11);
      if ( v32 < 11 || v32 > 15 )
      {
        v33 = *((char *)slotRecord + 11);
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
      panelTop + 21,
      v23,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
LABEL_19:
    if ( *((char *)slotRecord + 11) >= 1 )
      v24 = 7;
    else
      v24 = 13;
    Render_ReleaseSurface(v24, v13);
    UI_DrawTextFmt(a6, panelLeft + 132, panelLeft + 148, panelTop + 50, 2, (int)aD_15);
    if ( *((char *)slotRecord + 10) <= 90 )
      v25 = 7;
    else
      v25 = 13;
    Render_ReleaseSurface(v25, v13);
    UI_DrawTextFmt(a6, panelLeft + 160, panelLeft + 191, panelTop + 50, 2, (int)aD_16);
    Render_ReleaseSurface(7, v13);
    Unit_CalcIndexB(slotRecord);
    UI_DrawTextFmt(a6, panelLeft + 132, panelLeft + 148, panelTop + 95, 2, (int)aD_17);
    v26 = slotRecord[6] & 3;
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
          v29 = panelTop + 71;
          v45 = panelLeft + 178;
          while ( v6 <= (unsigned __int8)(16 * *((_BYTE *)slotRecord + 12)) >> 6 )
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
      panelTop + 65,
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
  v34 = *slotRecord;
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
    if ( (*((_BYTE *)unitMetadata + 18) & 1) == 0 )
      goto LABEL_50;
    v35 = 13;
  }
  v36 = v35;
  v37 = (33 - (unsigned __int16)DLX_GetSpriteWidth((int)v42, v35)) / 2 + 76 + panelTop;
  v6 = (34 - (unsigned __int16)DLX_GetSpriteHeight((int)v42, v36)) / 2 + 8 + panelLeft;
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
  UI_DrawTextFmt(v6, panelLeft + 41, panelLeft + 70, panelTop + 98, 3, (int)aD_18);
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
        unsigned __int8 *unitRecord,
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
  int animFrameIndex; // esi
  int v18; // ecx
  int v19; // ecx
  unsigned int v20; // eax
  unsigned int v21; // edx
  int v22; // ecx
  int v23; // eax
  int v25; // ecx
  char v26[100]; // [esp+0h] [ebp-8Ch] BYREF
  _DWORD *spriteSet; // [esp+64h] [ebp-28h] BYREF
  int screenTop; // [esp+68h] [ebp-24h]
  int v29; // [esp+6Ch] [ebp-20h]
  _DWORD *v30; // [esp+70h] [ebp-1Ch]
  int screenLeft; // [esp+74h] [ebp-18h]
  int v32; // [esp+78h] [ebp-14h]
  int lastAnimTick; // [esp+7Ch] [ebp-10h]

  screenLeft = a1;
  screenTop = a2;
  Debug_Log(a2, (char)unitRecord, a5, (int)aUnit_infoDD0x0);
  v9 = *(__int16 *)unitRecord;
  if ( v9 == UNIT_TYPE_PEASANT_CARGO
    || v9 == UNIT_TYPE_GOLD_CARGO
    || v9 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE
    || v9 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    return UI_DrawSpecialUnitInfoPane(screenLeft, screenTop, v8, unitRecord, a5, a3);
  v10 = unitRecord[2];
  UI_BeginUnitInfo(v26, *unitRecord, v10);
  v12 = (_DWORD *)Mem_Alloc(4112, v11, v10, a5);
  if ( v12 )
    v12 = DLXSpriteSet_Load(v12, v10);
  spriteSet = v12;
  if ( a6 )
  {
    v10 = g_MapPalettePtr;
    DLXSpriteSet_DrawText((int)v12, 0, a6, (unsigned __int8 *)g_MapPalettePtr);
  }
  Render_Pump();
  Surface = (_DWORD *)Mem_Alloc(188, v13, v10, a6);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 201, 116);
  v30 = Surface;
  Render_FillRect(0, Surface, (unsigned __int16)screenTop, (unsigned __int16)screenLeft, screenLeft + 200, screenTop + 115, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  UI_DrawUnitInfoPane(screenLeft, screenTop, a6, (__int16 *)unitRecord, a6, a3);
  SpriteForChar = DLX_GetSpriteForChar((int)spriteSet, 0);
  v16 = screenTop + 5;
  v29 = *((_DWORD *)g_RenderDevice + 46);
  v32 = screenLeft + 11;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v29 + 52))(
    screenTop + 5,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  animFrameIndex = 0;
  g_RenderDevice = &g_MainRenderDevice;
  lastAnimTick = Time_Now(v18, (int)&g_MainRenderDevice);
  while ( DD_IsLost((int)g_RenderState) || DD_IsFlipping((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, a6);
    if ( !a6 )
    {
      v20 = Time_Now(v19, lastAnimTick + 10);
      if ( v21 < v20 )
      {
        lastAnimTick = Time_Now(v22, v21);
        animFrameIndex = (animFrameIndex + 1) % 8;
        v23 = DLX_GetSpriteForChar((int)spriteSet, animFrameIndex);
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
  Render_FillRect(v30, 0, 0, 0, 0xC8u, 0x73u, screenLeft, screenTop);
  Render_Present((int)g_RenderState);
  if ( v25 )
    (**(void (***)(void))(v25 + 184))();
  return DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
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
        unsigned __int8 *unitRecord,
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
  int animFrameIndex; // esi
  int v22; // ecx
  unsigned int v23; // eax
  unsigned int v24; // edx
  int v25; // ecx
  int v26; // eax
  int v27; // eax
  _DWORD *v28; // esi
  char v30[100]; // [esp+0h] [ebp-90h] BYREF
  _DWORD *iconSpriteSet; // [esp+64h] [ebp-2Ch] BYREF
  _DWORD *animSpriteSet; // [esp+68h] [ebp-28h] BYREF
  _DWORD *surface; // [esp+6Ch] [ebp-24h]
  int screenTop; // [esp+70h] [ebp-20h]
  int screenLeft; // [esp+74h] [ebp-1Ch]
  int v36; // [esp+78h] [ebp-18h]
  int v37; // [esp+7Ch] [ebp-14h]

  screenLeft = a1;
  screenTop = a2;
  v7 = (_DWORD *)Mem_Alloc(4112, a3, (char)unitRecord, a5);
  if ( v7 )
    v7 = DLXSpriteSet_Load(v7, (char)unitRecord);
  iconSpriteSet = v7;
  v8 = unitRecord[2];
  UI_BeginUnitInfo(v30, *unitRecord, v8);
  v10 = (_DWORD *)Mem_Alloc(4112, v9, v8, a5);
  if ( v10 )
    v10 = DLXSpriteSet_Load(v10, v8);
  animSpriteSet = v10;
  Render_Pump();
  Surface = (_DWORD *)Mem_Alloc(188, v11, v8, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 201, 116);
  surface = Surface;
  Render_FillRect(0, Surface, (unsigned __int16)screenTop, (unsigned __int16)screenLeft, screenLeft + 200, screenTop + 115, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(7, a5);
  SpriteForChar = DLX_GetSpriteForChar((int)iconSpriteSet, 24);
  v14 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v14 + 52))(
    screenTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  switch ( *(_WORD *)unitRecord )
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
  v15 = DLX_GetSpriteForChar((int)iconSpriteSet, a6);
  v16 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v16 + 52))(
    screenTop + 20,
    v15,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(15, v14);
  UI_DrawTextFmt(v16, screenLeft + 120, screenLeft + 173, screenTop + 30, 2, (int)aD_19);
  Render_ReleaseSurface(7, v14);
  UI_DrawTextFmt(v16, screenLeft + 15, screenLeft + 88, screenTop + 32, 2, (int)aD_20);
  v17 = (**(&g_UnitTypeMetadataRecords + 22 * *(__int16 *)unitRecord))[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(v16, screenLeft + 64, screenLeft + 162, screenTop + 8, 3, (int)v17);
  if ( (unitRecord[13] & 8) != 0 )
  {
    v27 = DLX_GetSpriteForChar((int)iconSpriteSet, 27);
    LOBYTE(v17) = screenLeft - 105;
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      screenTop + 52,
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
  v37 = screenLeft + 11;
  animFrameIndex = 0;
  v36 = screenTop + 5;
  while ( DD_IsLost((int)g_RenderState) || DD_IsFlipping((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, (char)v17);
    v23 = Time_Now(v22, v20 + 10);
    if ( v24 < v23 )
    {
      v20 = Time_Now(v25, v24);
      animFrameIndex = (animFrameIndex + 1) % 8;
      v26 = DLX_GetSpriteForChar((int)animSpriteSet, animFrameIndex);
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
  Render_FillRect(surface, 0, 0, 0, 0xC8u, 0x73u, screenLeft, screenTop);
  v28 = surface;
  Render_Present((int)g_RenderState);
  if ( v28 )
    (*(void (**)(void))v28[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&iconSpriteSet);
  return DLXSpriteSet_ReleaseAndClear((int *)&animSpriteSet);
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

// Test hook: CLASH95_FORCE_AUTORESOLVE routes combats through the authentic
// autoresolve path (CalculateBattleResult) even under direct-boot, where
// dword_51D01C otherwise forces manual tactical battles. This exercises the same
// recovered battle-resolution the real menu path uses, letting campaign-route
// probes resolve combats without hand-authored battlefield input.
static int Diagnostics_ForceAutoresolveEnabled(void)
{
  static int checked;
  static int enabled;
  if ( !checked )
  {
    const char *value = getenv("CLASH95_FORCE_AUTORESOLVE");
    enabled = value && *value;
    checked = 1;
  }
  return enabled;
}

//----- (0041AD20) --------------------------------------------------------
void  Unit_Attack(int attackerIndex, int defenderIndex, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  __int16 *attackerStack; // ebp
  int v9; // eax
  BOOL v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  _DWORD *v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edx
  unsigned __int8 *attackerHasSpecial; // esi
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
  DWORD battleWinner; // edi
  signed int v32; // eax
  int useManualBattle; // ecx
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
  char attackerSpecialEntries[404]; // [esp+0h] [ebp-358h] BYREF
  unsigned __int8 defenderSpecialEntries[404]; // [esp+194h] [ebp-1C4h] BYREF
  int defenderStackIndex; // [esp+328h] [ebp-30h]
  unsigned __int8 *bothPlayersHuman; // [esp+32Ch] [ebp-2Ch]
  int defenderHasSpecial; // [esp+330h] [ebp-28h]
  int v61; // [esp+334h] [ebp-24h]
  __int16 *defenderStack; // [esp+338h] [ebp-20h]
  int capturedCargoFlag; // [esp+33Ch] [ebp-1Ch]
  int attackerStackIndex; // [esp+340h] [ebp-18h]
  int autoresolveRan; // recovered autoresolve-return probe

  attackerStackIndex = attackerIndex;
  defenderStackIndex = defenderIndex;
  autoresolveRan = 0;
  Debug_Log(attackerIndex, a3, a4, (int)aUnit_attackDD);
  Render_DrawSprite_v3(attackerStackIndex, a4);
  Render_DrawSprite_v3(defenderStackIndex, a4);
  attackerStack = (__int16 *)UNIT_STACK(attackerStackIndex);
  v9 = 1423 * *((unsigned __int8 *)attackerStack + 4);
  defenderStack = (__int16 *)(725 * defenderStackIndex + gameData + 147174);
  Diagnostics_TraceWorldMapActionEvent("unit_attack_enter", attackerStackIndex, defenderStackIndex, *defenderStack, defenderStack[1]);
  v10 = *(_DWORD *)(gameData + v9 + 140051) && *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)defenderStack + 4) + 140051);
  bothPlayersHuman = (unsigned __int8 *)v10;
  capturedCargoFlag = 0;
  if ( UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
  {
    v12 = *attackerStack - *defenderStack;
    if ( v12 <= 0 )
      v12 = *defenderStack - *attackerStack;
    if ( v12 <= 1 )
    {
      v13 = attackerStack[1] - defenderStack[1];
      if ( v13 <= 0 )
        v13 = defenderStack[1] - attackerStack[1];
      if ( v13 <= 1 )
        goto LABEL_22;
    }
    v14 = Unit_MoveTrackNearTile(attackerStackIndex, *defenderStack, (int)attackerStack, defenderStack[1], (DWORD)attackerStack);
    Diagnostics_TraceWorldMapActionEvent(v14 ? "unit_attack_track" : "unit_attack_no_track", attackerStackIndex, defenderStackIndex, *defenderStack, defenderStack[1]);
    if ( v14 )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_attack_track_state",
        attackerStackIndex,
        defenderStackIndex,
        v14[0],
        v14[0] > 0 ? HIWORD(v14[v14[0]]) : 0);
      qmemcpy(attackerStack + 158, v14, 0x194u);
      UnitStack_ExecuteQueuedPath(attackerStackIndex, 1, (_BYTE)attackerStack + 60, (DWORD)attackerStack, a5);
      Diagnostics_TraceWorldMapActionEvent("unit_attack_after_track", attackerStackIndex, defenderStackIndex, *attackerStack, attackerStack[1]);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_attack_after_track_state",
        attackerStackIndex,
        defenderStackIndex,
        *((_DWORD *)attackerStack + 79),
        UnitStack_GetMinCurrentActionPoints((intptr_t)attackerStack));
      if ( !*((_DWORD *)attackerStack + 79) && (unsigned int)attackerStack[3] <= 0x28 )
      {
        v15 = *attackerStack - *defenderStack;
        if ( v15 <= 0 )
          v15 = *defenderStack - *attackerStack;
        if ( v15 <= 1 )
        {
          v16 = attackerStack[1] - defenderStack[1];
          if ( v16 <= 0 )
            v16 = defenderStack[1] - attackerStack[1];
          if ( v16 <= 1 )
          {
LABEL_22:
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_adjacent",
              attackerStackIndex,
              defenderStackIndex,
              Unit_GetSquadCount((int)attackerStack),
              Unit_GetSquadCount((int)defenderStack));
            UnitStack_SetSpentTurnFlag((int)attackerStack);
            UnitStack_AdjustFatigueByPredicate(attackerStack, 10, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
            UnitStack_AdjustFatigueByPredicate(defenderStack, 10, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
            if ( ACTIVE_MISSION_INDEX == 15 )
              Mission_MarkObjective15CompleteOnAttack(*((unsigned __int8 *)attackerStack + 4), *((unsigned __int8 *)defenderStack + 4));
            if ( ACTIVE_MISSION_INDEX == 5 )
              Mission05_MarkFailureOnFriendlyAttack(*((unsigned __int8 *)attackerStack + 4), *((unsigned __int8 *)defenderStack + 4));
            attackerHasSpecial = (unsigned __int8 *)UnitStack_HasSpecialPersonageUnits((intptr_t)attackerStack);
            defenderHasSpecial = UnitStack_HasSpecialPersonageUnits((intptr_t)defenderStack);
            v19 = Unit_GetSquadCount((int)attackerStack);
            UnitSlots_ExtractSpecialEntries((char *)attackerStack + 6, v19, attackerSpecialEntries);
            v20 = defenderSpecialEntries;
            v21 = Unit_GetSquadCount((int)defenderStack);
            UnitSlots_ExtractSpecialEntries((char *)defenderStack + 6, v21, (char *)defenderSpecialEntries);
            v23 = *(_DWORD *)(1423 * *((unsigned __int8 *)attackerStack + 4) + gameData + 140051)
               || *(_DWORD *)(1423 * *((unsigned __int8 *)defenderStack + 4) + gameData + 140051);
            if ( v23 && Unit_GetSquadCount((int)attackerStack) && Unit_GetSquadCount((int)defenderStack) )
            {
              v24 = defenderStack;
              v21 = Unit_GetSquadCount((int)defenderStack);
              v20 = (unsigned __int8 *)(v24 + 3);
              v25 = Unit_GetSquadCount((int)attackerStack);
              v27 = UI_PromptLeadTroopsPersonally((int)(attackerStack + 3), v25, v21, (int)v20, (DWORD)attackerStack, (int)(attackerStack + 3), 0) == 0;
            }
            else
            {
              v27 = 0;
            }
            useManualBattle = (g_ManualTacticalBattleEnabled || v27) && !Diagnostics_ForceAutoresolveEnabled();
            if ( useManualBattle )
            {
              if ( *((_BYTE *)attackerStack + 720) )
              {
                v28 = Unit_GetSquadCount((int)defenderStack) == 0;
                v30 = aAtak_zas;
              }
              else
              {
                v28 = Unit_GetSquadCount((int)defenderStack) == 0;
                v30 = aBattle;
              }
              Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_transition_enter", attackerStackIndex, defenderStackIndex, v28, 0);
              Win_PlayModeChangeFrameTransition(v30, v28, v29, (char)v20, (DWORD)attackerStack);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_transition_return", attackerStackIndex, defenderStackIndex, v28, 0);
            }
            battleWinner = 0;
            v32 = Unit_GetSquadCount((int)defenderStack);
            v61 = 0;
            if ( v32 <= 0 )
            {
LABEL_48:
              if ( battleWinner )
              {
                if ( battleWinner == 1 )
                {
                  UnitSlots_AppendEntries((char *)defenderStack + 6, (char *)defenderSpecialEntries);
                  if ( *(__int16 *)attackerSpecialEntries != -1 )
                  {
                    v51 = Unit_CreateNearbyUnitGroup(*defenderStack, defenderStack[1], (unsigned __int8 *)attackerSpecialEntries, a5);
                    if ( (UnitStack_HasPeasantCargo(v51) || UnitStack_HasGoldCargo(v51))
                      && *(unsigned __int8 *)(v51 + 4) == *(_DWORD *)(gameData + 147143) )
                    {
                      capturedCargoFlag = 1;
                    }
                    UnitStack_CaptureDefeatedStack(defenderStack, v51, v51, (int)attackerSpecialEntries, a5);
                  }
                  UnitStack_AdjustMoraleByPredicate(attackerStack, -5, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(defenderStack, 4, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)attackerStack, a5);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)defenderStack + 4) + 141441);
                }
                else if ( battleWinner == 2 )
                {
                  UnitSlots_AppendEntries((char *)attackerStack + 6, attackerSpecialEntries);
                  if ( *(__int16 *)attackerSpecialEntries != -1 )
                  {
                    v47 = Unit_CreateNearbyUnitGroup(*attackerStack, attackerStack[1], defenderSpecialEntries, a5);
                    if ( (UnitStack_HasPeasantCargo(v47) || UnitStack_HasGoldCargo(v47))
                      && *(unsigned __int8 *)(v47 + 4) == *(_DWORD *)(gameData + 147143) )
                    {
                      capturedCargoFlag = 1;
                    }
                    UnitStack_CaptureDefeatedStack(attackerStack, v47, v47, (int)defenderSpecialEntries, a5);
                  }
                  UnitStack_AdjustMoraleByPredicate(defenderStack, -5, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)attackerStack, a5);
                  UnitStack_SubtractActionPointsFloorZero(attackerStack, 10, (DWORD)attackerStack, a5);
                  ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)defenderStack + 4) + 141441);
                }
                goto LABEL_52;
              }
LABEL_49:
              UnitSlots_AppendEntries((char *)attackerStack + 6, attackerSpecialEntries);
              UnitSlots_AppendEntries((char *)defenderStack + 6, (char *)defenderSpecialEntries);
              if ( UnitStack_HasNormalCombatUnits((intptr_t)defenderStack) || !UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
              {
                if ( UnitStack_HasNormalCombatUnits((intptr_t)defenderStack) && !UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
                {
                  if ( (unsigned int)attackerStack[3] <= 0x28 )
                  {
                    if ( (UnitStack_HasPeasantCargo((int)attackerStack) || UnitStack_HasGoldCargo((int)attackerStack))
                      && *((unsigned __int8 *)defenderStack + 4) == *(_DWORD *)(gameData + 147143) )
                    {
                      capturedCargoFlag = 1;
                    }
                    UnitStack_CaptureDefeatedStack(defenderStack, (signed int)attackerStack, v46, (int)v20, a5);
                  }
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(defenderStack, 4, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)attackerStack, a5);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)defenderStack + 4) + 141441);
                }
              }
              else
              {
                if ( (unsigned int)defenderStack[3] <= 0x28 )
                {
                  if ( (UnitStack_HasPeasantCargo((int)defenderStack) || UnitStack_HasGoldCargo((int)defenderStack))
                    && *((unsigned __int8 *)attackerStack + 4) == *(_DWORD *)(gameData + 147143) )
                  {
                    capturedCargoFlag = 1;
                  }
                  UnitStack_CaptureDefeatedStack(attackerStack, (signed int)defenderStack, v45, (int)v20, a5);
                }
                v20 = (unsigned __int8 *)CSyncObject_Unlock;
                UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)attackerStack, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)attackerStack, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)attackerStack, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)attackerStack, a5);
                ++*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)attackerStack + 4) + 141441);
                --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)defenderStack + 4) + 141441);
              }
LABEL_52:
              if ( attackerStack[3] == -1 )
                Rules_UnlinkArmyFact(attackerStack, a5);
              if ( defenderStack[3] == -1 )
                Rules_UnlinkArmyFact(defenderStack, a5);
              WorldMap_SyncSelectionForHumanPlayer((DWORD)attackerStack);
              v41 = v61;
              UnitStackSelection_RefreshForSelectedStack((DWORD)attackerStack);
              if ( v41 )
                WorldMap_RenderHook((DWORD)attackerStack);
              else
                WorldMap_RedrawViewport(1);
              if ( capturedCargoFlag )
                Win_PlayModeChangeFrameTransition(aChlop, 1, v42, (char)v20, (DWORD)attackerStack);
              if ( autoresolveRan )
                Diagnostics_TraceWorldMapActionEvent("unit_attack_autoresolve_return", attackerStackIndex, defenderStackIndex, *attackerStack, attackerStack[1]);
              Render_DrawSprite_v3(attackerStackIndex, (DWORD)attackerStack);
              Render_DrawSprite_v3(defenderStackIndex, (DWORD)attackerStack);
              return;
            }
            if ( !useManualBattle )
            {
              v55 = defenderHasSpecial;
              v20 = attackerHasSpecial;
              v54 = Unit_GetSquadCount((int)defenderStack);
              v43 = Unit_GetSquadCount((int)attackerStack);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_autoresolve", attackerStackIndex, defenderStackIndex, v43, v54);
              autoresolveRan = 1;
              CalculateBattleResult(attackerStack + 3, v43, defenderStack + 3, (int)attackerHasSpecial, (DWORD)attackerStack, v54, v55, 0, 0);
              Diagnostics_TraceWorldMapActionEvent(
                "unit_attack_autoresolve_done",
                attackerStackIndex,
                defenderStackIndex,
                Unit_GetSquadCount((int)attackerStack),
                Unit_GetSquadCount((int)defenderStack));
              goto LABEL_49;
            }
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_prepare", attackerStackIndex, defenderStackIndex, useManualBattle, 0);
            Render_Pump();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_render_pump", attackerStackIndex, defenderStackIndex, 0, 0);
            Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_unlock", attackerStackIndex, defenderStackIndex, 0, 0);
            DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_frame_free", attackerStackIndex, defenderStackIndex, 0, 0);
            BuildingSpriteCache_Clear();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_building_cache_clear", attackerStackIndex, defenderStackIndex, 0, 0);
            UnitSpriteCache_FreeAllEntries(v34, (DWORD)attackerStack);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_unit_cache_clear", attackerStackIndex, defenderStackIndex, 0, 0);
            CSS_EmptySampleCache();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_sample_clear", attackerStackIndex, defenderStackIndex, 0, 0);
            TextSprite_ReleaseAllResourceSlots();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_text_enddraw", attackerStackIndex, defenderStackIndex, 0, 0);
            v54 = Unit_GetSquadCount((int)defenderStack);
            v43 = Unit_GetSquadCount((int)attackerStack);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_battle_enter", attackerStackIndex, defenderStackIndex, v43, v54);
            Battle_ResetInputScriptReader();
            battleWinner = Battle_RunTacticalCombat(
                    (__int16 *)(gameData + 147174 + 725 * attackerStackIndex),
                    (__int16 *)(gameData + 147174 + 725 * defenderStackIndex),
                    (int)attackerHasSpecial,
                    0,
                    (DWORD)attackerStack,
                    defenderHasSpecial);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_battle_return", attackerStackIndex, defenderStackIndex, battleWinner, 0);
            v37 = *(_BYTE *)(gameData + 140016);
            if ( g_WorldMapBackgroundSpriteSet )
              DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
            if ( v37 == 0 )
            {
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)attackerStack);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr1.s32");
              g_WorldMapBackgroundSpriteSet = (int)v38;
            }
            else if ( v37 == 1 )
            {
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)attackerStack);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr2.s32");
              g_WorldMapBackgroundSpriteSet = (int)v38;
            }
            else if ( v37 == 2 )
            {
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)attackerStack);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr3.s32");
              g_WorldMapBackgroundSpriteSet = (int)v38;
            }
            v39 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)attackerStack);
            if ( v39 )
              v39 = DLXSpriteSet_Load(v39, "frame.s32");
            g_ActiveUiSpriteSet = (int)v39;
            Tooltip_CaptureBackdrop(160, 473, 3, 467, 76);
            Palette_LoadOrBuildBlendLookupTable(aMainmap_0, g_MapPalettePtr, 1, (DWORD)attackerStack);
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
void  Unit_AttackBuilding(int attackerIndex, int buildingIndexArg, char a3, DWORD a4, double a5)
{
  unsigned __int8 *buildingRecord; // ebp
  BOOL v8; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  const void *v13; // eax
  int attackerHasSpecial; // edi
  BOOL v19; // eax
  signed int v23; // eax
  signed int useManualBattle; // esi
  signed int v26; // eax
  int v28; // eax
  int v30; // ecx
  int v32; // ebx
  int v33; // ecx
  unsigned __int8 *v34; // ebx
  int v35; // ecx
  DWORD battleWinner; // esi
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
  char attackerSpecialEntries[404]; // [esp+0h] [ebp-354h] BYREF
  char garrisonSpecialEntries[404]; // [esp+194h] [ebp-1C0h] BYREF
  BOOL bothPlayersHuman; // [esp+328h] [ebp-2Ch]
  int buildingHasSpecial; // [esp+32Ch] [ebp-28h]
  DWORD selectionRefreshIndex; // [esp+330h] [ebp-24h]
  int buildingIndex; // [esp+334h] [ebp-20h]
  int attackerStackIndex; // [esp+338h] [ebp-1Ch]
  __int16 *attackerStack; // [esp+33Ch] [ebp-18h]

  attackerStackIndex = attackerIndex;
  buildingIndex = buildingIndexArg;
  Debug_Log(attackerIndex, a3, a4, (int)aUnit_attackbui);
  Render_DrawSprite_v3(attackerStackIndex, 467 * buildingIndex);
  attackerStack = (__int16 *)UNIT_STACK(attackerStackIndex);
  buildingRecord = (unsigned __int8 *)(UNIT_RECORD(buildingIndex));
  v8 = PLAYER_HAS_HUMAN_CONTROLLER(UNIT_STACK_OWNER_INDEX((int)attackerStack)) && PLAYER_HAS_HUMAN_CONTROLLER(buildingRecord[2]);
  bothPlayersHuman = v8;
  if ( UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
  {
    v10 = *attackerStack - *buildingRecord;
    if ( v10 <= 0 )
      v10 = *buildingRecord - *attackerStack;
    if ( v10 <= 1 )
    {
      v11 = buildingRecord[1];
      v12 = attackerStack[1] - v11;
      if ( v12 <= 0 )
        v12 = v11 - attackerStack[1];
      if ( v12 <= 1 )
        goto LABEL_15;
    }
    v13 = (const void *)Building_GenerateApproachTrack(attackerStackIndex, buildingIndex, 0, 0, 0);
    if ( v13 )
    {
      qmemcpy(attackerStack + 158, v13, 0x194u);
      UnitStack_ExecuteQueuedPath(attackerStackIndex, 1, (_BYTE)attackerStack + 60, (DWORD)buildingRecord, a5);
      if ( !*((_DWORD *)attackerStack + 79) )
      {
LABEL_15:
        if ( UnitStack_GetMinCurrentActionPoints((intptr_t)attackerStack) >= 5 )
        {
          UnitStack_SpendActionPointsByIndexClamped(attackerStackIndex, 5, (DWORD)buildingRecord, a5);
          UnitStack_SetSpentTurnFlag((int)attackerStack);
          UnitStack_AdjustFatigueByPredicate(attackerStack, 10, UnitSlot_PredicateAlways, (DWORD)buildingRecord, a5);
          if ( ACTIVE_MISSION_INDEX == 15 )
            Mission_MarkObjective15CompleteOnAttack(*((unsigned __int8 *)attackerStack + 4), buildingRecord[2]);
          if ( ACTIVE_MISSION_INDEX == 5 )
            Mission05_MarkFailureOnFriendlyAttack(*((unsigned __int8 *)attackerStack + 4), buildingRecord[2]);
          attackerHasSpecial = UnitStack_HasSpecialPersonageUnits((intptr_t)attackerStack);
          buildingHasSpecial = Building_HasSpecialPersonageGarrisonEntries((int)buildingRecord);
          v19 = PLAYER_HAS_HUMAN_CONTROLLER(UNIT_STACK_OWNER_INDEX((int)attackerStack)) || PLAYER_HAS_HUMAN_CONTROLLER(buildingRecord[2]);
          if ( !v19 || Building_CountGarrison((int)buildingRecord) == Building_CountNonCombatGarrisonEntries((int)buildingRecord) )
          {
            useManualBattle = 0;
          }
          else
          {
            v23 = Unit_GetSquadCount((int)attackerStack);
            useManualBattle = UI_PromptLeadTroopsPersonally((int)(attackerStack + 3), v23, 12, (int)(buildingRecord + 18), (DWORD)buildingRecord, attackerHasSpecial, 1) == 0;
          }
          Diagnostics_TraceWorldMapActionEvent("unit_attack_building_prompt_result", attackerStackIndex, buildingIndex, useManualBattle, g_ManualTacticalBattleEnabled);
          if ( g_ManualTacticalBattleEnabled && !Diagnostics_ForceAutoresolveEnabled() )
          {
            useManualBattle = 1;
          }
          else if ( !useManualBattle )
          {
LABEL_28:
            selectionRefreshIndex = 0;
            if ( !Building_CountGarrison(UNIT_RECORD(buildingIndex)) )
            {
              UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)buildingRecord, a5);
              UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)buildingRecord, a5);
              UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)buildingRecord, a5);
              UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)buildingRecord, a5);
              Unit_CaptureBuilding(attackerStackIndex, buildingIndex, 0, useManualBattle, a5);
              ++*(_WORD *)(1423 * *((unsigned __int8 *)attackerStack + 4) + gameData + 141441);
              --*(_WORD *)(1423 * buildingRecord[2] + gameData + 141441);
LABEL_47:
              if ( attackerStack[3] == -1 )
                Rules_UnlinkArmyFact(attackerStack, a5);
              WorldMap_SyncSelectionForHumanPlayer((DWORD)buildingRecord);
              v42 = selectionRefreshIndex;
              UnitStackSelection_RefreshForSelectedStack(selectionRefreshIndex);
              if ( v42 )
                WorldMap_RenderHook(v42);
              Render_DrawSprite_v3(attackerStackIndex, v42);
              return;
            }
            Building_CompactGarrison(buildingRecord, (unsigned __int8 *)attackerStack, a5);
            v26 = Unit_GetSquadCount((int)attackerStack);
            UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)attackerStack + 6, v26, attackerSpecialEntries);
            v28 = Building_CountGarrison((int)buildingRecord);
            UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)buildingRecord + 18, v28, garrisonSpecialEntries);
            Building_CompactGarrison(buildingRecord, buildingRecord + 18, a5);
            for ( v30 = 0; v30 < 12; ++v30 )
            {
              Building_ClearGarrisonTrainingTimer((int)buildingRecord, v30);
              Building_ClearGarrisonRepairTimer((int)buildingRecord, v30);
            }
            v32 = 467 * buildingIndex;
            if ( !useManualBattle )
            {
              v53 = v32 + gameData + 509674;
              v52 = buildingHasSpecial;
              v51 = Building_CountGarrison(v53);
              v43 = attackerStack + 3;
              v40 = (char)attackerHasSpecial;
              v44 = Unit_GetSquadCount((int)attackerStack);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_building_autoresolve", attackerStackIndex, buildingIndex, v44, v51);
              CalculateBattleResult(v43, v44, v45, attackerHasSpecial, (DWORD)buildingRecord, v51, v52, v53, 0);
              Diagnostics_TraceWorldMapActionEvent(
                "unit_attack_building_autoresolve_done",
                attackerStackIndex,
                buildingIndex,
                Unit_GetSquadCount((int)attackerStack),
                Building_CountGarrison(v53));
              battleWinner = 0;
LABEL_42:
              UnitSlots_AppendEntriesForBuildingAttack((char *)attackerStack + 6, attackerSpecialEntries);
              if ( battleWinner )
              {
                if ( battleWinner == 1 )
                {
                  UnitStack_AdjustMoraleByPredicate(attackerStack, -5, UnitSlot_PredicateAlways, (DWORD)buildingRecord, a5);
                  --*(_WORD *)(gameData + 1423 * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  ++*(_WORD *)(gameData + 1423 * buildingRecord[2] + 141441);
                  Building_AdjustAllGarrisonMoraleByDelta((int)buildingRecord, 4);
                  Building_CycleAllGarrisonOrdersOnce((int)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)buildingRecord);
                }
              }
              else if ( Building_CountGarrison(UNIT_RECORD(buildingIndex))
                     || !UnitStack_HasNormalCombatUnits(725 * attackerStackIndex + gameData + 147174) )
              {
                if ( Building_CountGarrison(UNIT_RECORD(buildingIndex))
                  && !UnitStack_HasNormalCombatUnits(725 * attackerStackIndex + gameData + 147174) )
                {
                  UnitSlots_AppendEntriesForBuildingAttack((char *)buildingRecord + 18, garrisonSpecialEntries);
                  UnitStack_KillByIndex(attackerStackIndex, v40, (DWORD)buildingRecord, a5);
                  --*(_WORD *)(gameData + 1423 * *(unsigned __int8 *)(v48 + 4) + 141441);
                  ++*(_WORD *)(1423 * buildingRecord[2] + gameData + 141441);
                  Building_AdjustAllGarrisonMoraleByDelta((int)buildingRecord, 4);
                  Building_CycleAllGarrisonOrdersOnce((int)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)buildingRecord);
                }
                else if ( !Building_CountGarrison(UNIT_RECORD(buildingIndex))
                       && !UnitStack_HasNormalCombatUnits(725 * attackerStackIndex + gameData + 147174) )
                {
                  UnitStack_KillByIndex(attackerStackIndex, v40, (DWORD)buildingRecord, a5);
                }
              }
              else
              {
                UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)buildingRecord, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)buildingRecord, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)buildingRecord, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)buildingRecord, a5);
                Unit_CaptureBuilding(attackerStackIndex, buildingIndex, 0, 0, a5);
                ++*(_WORD *)(1423 * *((unsigned __int8 *)attackerStack + 4) + gameData + 141441);
                --*(_WORD *)(1423 * buildingRecord[2] + gameData + 141441);
              }
              goto LABEL_47;
            }
            Render_Pump();
            Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
            DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
            BuildingSpriteCache_Clear();
            UnitSpriteCache_FreeAllEntries(v33, (DWORD)buildingRecord);
            CSS_EmptySampleCache();
            TextSprite_ReleaseAllResourceSlots();
            v34 = (unsigned __int8 *)(gameData + 509674 + v32);
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_building_battle_enter",
              attackerStackIndex,
              buildingIndex,
              Unit_GetSquadCount((int)attackerStack),
              Building_CountGarrison((int)buildingRecord));
            battleWinner = Battle_RunTacticalCombat((__int16 *)(725 * attackerStackIndex + gameData + 147174), 0, (int)attackerHasSpecial, v34, (DWORD)buildingRecord, buildingHasSpecial);
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_building_battle_return",
              attackerStackIndex,
              buildingIndex,
              battleWinner,
              Building_CountGarrison((int)buildingRecord));
            v37 = *(_BYTE *)(gameData + 140016);
            if ( v37 == 0 )
            {
              if ( g_WorldMapBackgroundSpriteSet )
                DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)buildingRecord);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr1.s32");
              g_WorldMapBackgroundSpriteSet = (int)v38;
            }
            else if ( v37 == 1 )
            {
              if ( g_WorldMapBackgroundSpriteSet )
                DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)buildingRecord);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr2.s32");
              g_WorldMapBackgroundSpriteSet = (int)v38;
            }
            else if ( v37 == 2 )
            {
              if ( g_WorldMapBackgroundSpriteSet )
                DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
              v38 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)buildingRecord);
              if ( v38 )
                v38 = DLXSpriteSet_Load(v38, "backgr3.s32");
              g_WorldMapBackgroundSpriteSet = (int)v38;
            }
            v39 = (_DWORD *)Mem_Alloc(4112, 0, 0, (DWORD)buildingRecord);
            if ( v39 )
              v39 = DLXSpriteSet_Load(v39, "frame.s32");
            v40 = -45;
            g_ActiveUiSpriteSet = (int)v39;
            Tooltip_CaptureBackdrop(160, 473, 3, 467, 76);
            Palette_LoadOrBuildBlendLookupTable(aMainmap_1, g_MapPalettePtr, 1, (DWORD)buildingRecord);
            selectionRefreshIndex = 1;
            if ( bothPlayersHuman )
              UI_LoadTurnBannerGfx(211, (DWORD)buildingRecord);
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
int  UnitSlots_CalcCombatStrengthScore(char *slotArray, int slotCount, int statContext, int wallDefenseBonus)
{
  unsigned int unitType; // eax
  int unitScore; // edi
  char *(**unitMetadata)[102]; // ecx
  int v9; // eax
  int orderTier; // ebp
  int v13; // eax
  int v15; // edi
  int v16; // edx
  __int64 v17; // rax
  int v18; // eax
  int v19; // edi
  int v20; // edx
  int totalScore; // [esp+8h] [ebp-14h]
  int v24;

  totalScore = 0;
  while ( --slotCount != -1 )
  {
    while ( 1 )
    {
      unitType = *(__int16 *)slotArray;
      if ( unitType <= 0x28 )
        break;
      slotArray += 31;
    }
    unitScore = 0;
    unitMetadata = &g_UnitTypeMetadataRecords + 22 * unitType;
    if ( unitType == 13 )
    {
      if ( wallDefenseBonus )
      {
        v9 = Unit_CalcEffectivenessD(slotArray, statContext);
        unitScore = v9 * (*((unsigned __int8 *)unitMetadata + 24) / 5) / 2;
      }
      else
      {
        unitScore = 1;
      }
      goto LABEL_8;
    }
    if ( *((_BYTE *)unitMetadata + 22) && !*((_BYTE *)unitMetadata + 25) )
    {
      v15 = *((unsigned __int8 *)unitMetadata + 24) / 5 - 1;
      if ( (*((_BYTE *)unitMetadata + 18) & 1) == 0 )
        v15 -= 2 * wallDefenseBonus / 100;
      v16 = Unit_CalcEffectivenessA(slotArray, statContext) * v15 + totalScore;
      slotArray += 31;
      totalScore = v16;
    }
    else if ( *((_BYTE *)unitMetadata + 22) || !*((_BYTE *)unitMetadata + 25) )
    {
      if ( !*((_BYTE *)unitMetadata + 22) || !*((_BYTE *)unitMetadata + 25) )
        goto LABEL_8;
      orderTier = (slotArray[12] & 3) + 1;
      if ( orderTier >= *((unsigned __int8 *)unitMetadata + 24) / 5 )
        orderTier = *((unsigned __int8 *)unitMetadata + 24) / 5;
      unitScore = Unit_CalcEffectivenessC((__int16 *)slotArray) * orderTier;
      v24 = *((unsigned __int8 *)unitMetadata + 24) / 5 - orderTier - 1;
      if ( v24 > 0 )
      {
        v13 = Unit_CalcEffectivenessA(slotArray, statContext);
        slotArray += 31;
        totalScore += v24 * v13 + unitScore;
      }
      else
      {
LABEL_8:
        slotArray += 31;
        totalScore += unitScore;
      }
    }
    else
    {
      v17 = 6 - *((unsigned __int8 *)unitMetadata + 26);
      v18 = *((unsigned __int8 *)unitMetadata + 24) / 5 - (((int)v17 - HIDWORD(v17)) >> 1);
      if ( (slotArray[12] & 3) + 1 < v18 )
        v18 = (slotArray[12] & 3) + 1;
      v19 = v18;
      if ( v18 >= 3 )
        v19 = v18 + 2;
      v20 = Unit_CalcEffectivenessC((__int16 *)slotArray) * v19 + totalScore;
      slotArray += 31;
      totalScore = v20;
    }
  }
  return totalScore;
}
// 41C143: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (0041C300) --------------------------------------------------------
int  UnitSlots_CalcDefenseScore(char *slotArray, int slotCount, int statContext)
{
  int i; // ebx
  int slotDefense; // eax

  for ( i = 0; --slotCount != -1; i += slotDefense )
  {
    while ( (unsigned int)*(__int16 *)slotArray > 0x28 )
      slotArray += 31;
    slotDefense = Unit_CalcEffectivenessB(slotArray, statContext);
    slotArray += 31;
  }
  return (300 * i - (__CFSHL__((300 * i) >> 31, 8) + ((300 * i) >> 31 << 8))) >> 8;
}
// 41C316: simplified comparisons for 'eax.4': >=0 && <29 became <29u

//----- (0041C360) --------------------------------------------------------
int  Building_ApplySiegeDamageToWallSections(int buildingRecord, signed int siegeDamage)
{
  signed int remainingDamage; // ebx
  int result; // eax
  int sectionsToClear; // ecx
  int sectionHitPoints; // edx
  int v7; // ecx
  unsigned int sectionIndex; // ebx
  char damageAmount; // dl
  int v10; // ecx
  int v11; // ecx

  remainingDamage = siegeDamage;
  result = siegeDamage / 100;
  sectionsToClear = siegeDamage / 100;
  if ( siegeDamage / 100 > 2 )
    sectionsToClear = 2;
  while ( sectionsToClear )
  {
    result = Rng_RandRange(0, 6);
    sectionHitPoints = *(unsigned __int8 *)(buildingRecord + result + 422);
    *(_BYTE *)(buildingRecord + result + 422) = 0;
    remainingDamage -= sectionHitPoints;
  }
  if ( remainingDamage )
  {
    do
      sectionIndex = Rng_RandRange(0, 6);
    while ( !*(_BYTE *)(buildingRecord + sectionIndex + 422) && v7 + 1 < 6 );
    result = Rng_RandRange(10, 25);
    damageAmount = result;
    v11 = *(unsigned __int8 *)(v10 + 422);
    if ( result > v11 )
      damageAmount = v11;
    *(_BYTE *)(buildingRecord + sectionIndex + 422) -= damageAmount;
  }
  return result;
}
// 41C37E: variable 'v5' is possibly undefined
// 41C3CA: variable 'v7' is possibly undefined
// 41C3E4: variable 'v10' is possibly undefined

//----- (0041C410) --------------------------------------------------------
int  Building_CalcWallDefenseBonus(int buildingRecord, signed int weakestSection)
{
  int minSectionHP; // eax
  int v4; // ecx
  int i; // edx
  int v6; // ecx
  int firstMinHP; // edi
  int j; // edx
  int wallDefenseRaw; // eax

  minSectionHP = 100;
  v4 = buildingRecord;
  for ( i = 0; i < 7; ++i )
  {
    if ( *(unsigned __int8 *)(v4 + 422) < minSectionHP )
    {
      minSectionHP = *(unsigned __int8 *)(v4 + 422);
      weakestSection = i;
    }
    ++v4;
  }
  v6 = buildingRecord;
  firstMinHP = minSectionHP;
  for ( j = 0; j < 7; ++j )
  {
    if ( *(unsigned __int8 *)(v6 + 422) < minSectionHP && j != weakestSection )
      minSectionHP = *(unsigned __int8 *)(v6 + 422);
    ++v6;
  }
  wallDefenseRaw = (minSectionHP + firstMinHP) / 2 * (unsigned __int16)g_WallKindDefenseFactor[2 * *(unsigned __int8 *)(buildingRecord + 421)];
  return (wallDefenseRaw - (__CFSHL__(wallDefenseRaw >> 31, 8) + (wallDefenseRaw >> 31 << 8))) >> 8;
}
// 513A78: using guessed type __int16 word_513A78[];

//----- (0041C4A0) --------------------------------------------------------
int  CalculateBattleResult(
        _WORD *attackerSlots,
        int attackerCount,
        _WORD *defenderSlots,
        int attackerStatContext,
        DWORD a5,
        int defenderCount,
        int defenderStatContext,
        int buildingRecord,
        int applyAttackerBonus)
{
  char v48[12]; // [esp+0h] [ebp-40h]
  _WORD *v49; // [esp+Ch] [ebp-34h]
  int attackerCombatScore; // [esp+10h] [ebp-30h]
  signed int higherNetScore; // [esp+14h] [ebp-2Ch]
  signed int lowerNetScore; // [esp+18h] [ebp-28h]
  int v53; // [esp+1Ch] [ebp-24h]
  signed int attackerNetScore; // [esp+20h] [ebp-20h]
  int loserCount; // [esp+24h] [ebp-1Ch]
  _WORD *loserSlots; // [esp+28h] [ebp-18h]
  __int16 *winnerSlots; // [esp+2Ch] [ebp-14h]
  int casualtyBudget; // [esp+30h] [ebp-10h]
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

  v49 = attackerSlots;
  v53 = attackerStatContext;
  Battle_StoreLastOutcomeValue(1);
  Debug_Log(0, 0, a5, (int)aNewBattle);
  Debug_Log((int)v49, (char)attackerCount, a5, (int)aCalculatebattl, (int)v49, attackerCount, v53, (int)defenderSlots, defenderCount, defenderStatContext, buildingRecord, applyAttackerBonus);
  Debug_Log(0, 0, a5, (int)aJednostka1);
  Debug_Log(0, 0, a5, (int)aJednostka2);
  if ( buildingRecord )
    wall_defense_bonus = Building_CalcWallDefenseBonus(buildingRecord, (signed int)defenderSlots);
  else
    wall_defense_bonus = 0;
  attackerCombatScore = UnitSlots_CalcCombatStrengthScore((char *)v49, attackerCount, v53, wall_defense_bonus);
  defender_combat = UnitSlots_CalcCombatStrengthScore((char *)defenderSlots, defenderCount, defenderStatContext, 0);
  attackerNetScore = attackerCombatScore - UnitSlots_CalcDefenseScore((char *)defenderSlots, defenderCount, defenderStatContext);
  defender_score = defender_combat - UnitSlots_CalcDefenseScore((char *)v49, attackerCount, v53);
  Debug_Log(attackerNetScore, 0, a5, (int)aAs1D, attackerNetScore);
  Debug_Log(defender_score, 0, a5, (int)aAs2D, defender_score);
  if ( attackerNetScore < 0 )
    attackerNetScore = 0;
  if ( defender_score < 0 )
    defender_score = 0;
  if ( !attackerNetScore )
    attackerNetScore = 1;
  if ( !defender_score )
    defender_score = 1;
  if ( defender_score == attackerNetScore )
    ++attackerNetScore;
  if ( applyAttackerBonus )
    attackerNetScore = 135 * attackerNetScore / 100;
  if ( defender_score > attackerNetScore )
    higherNetScore = defender_score;
  else
    higherNetScore = attackerNetScore;
  if ( defender_score > attackerNetScore )
    lowerNetScore = attackerNetScore;
  else
    lowerNetScore = defender_score;
  if ( defender_score > attackerNetScore )
    winnerSlots = (__int16 *)defenderSlots;
  else
    winnerSlots = (__int16 *)v49;
  if ( defender_score > attackerNetScore )
    loserSlots = v49;
  else
    loserSlots = defenderSlots;
  if ( defender_score > attackerNetScore )
    loserCount = attackerCount;
  else
    loserCount = defenderCount;
  if ( defender_score > attackerNetScore )
    attackerCount = defenderCount;
  casualtyBudget = 0;
  for ( i = 0; i < attackerCount; ++i )
    casualtyBudget += *((signed char *)winnerSlots + 31 * i + 9);
  casualtyBudget = casualtyBudget * lowerNetScore / higherNetScore;
  Debug_Log(casualtyBudget, (char)higherNetScore, a5, (int)aSum_quantDAtt_, casualtyBudget);
  while ( casualtyBudget > 0 )
  {
    applied_loss = 0;
    memset(v48, 0, sizeof(v48));
    while ( casualtyBudget > 0 )
    {
      for ( slot_index = 0; slot_index < attackerCount && slot_index < (int)sizeof(v48) && v48[slot_index]; ++slot_index )
        ;
      if ( slot_index >= attackerCount || slot_index >= (int)sizeof(v48) )
        break;
      selected_slot = -1;
      selected_priority = 0;
      for ( i = 0; i < attackerCount && i < (int)sizeof(v48); ++i )
      {
        slot_priority = (unsigned __int8)unit_stats[88 * *(__int16 *)((char *)winnerSlots + 31 * i)];
        if ( slot_priority > selected_priority && !v48[i] )
        {
          selected_priority = slot_priority;
          selected_slot = i;
        }
      }
      if ( selected_slot < 0 )
      {
        casualtyBudget = 0;
        break;
      }
      old_quantity = *((signed char *)winnerSlots + 31 * selected_slot + 9);
      new_quantity = old_quantity - selected_priority;
      if ( new_quantity < 0 )
        new_quantity = 0;
      new_quantity -= Rng_RandRange(0, 10);
      loss_delta = old_quantity - new_quantity;
      casualtyBudget -= loss_delta;
      if ( casualtyBudget < 0 )
        new_quantity -= casualtyBudget;
      if ( new_quantity < 0 )
        new_quantity = 0;
      if ( loss_delta > 0 )
        applied_loss = 1;
      *((_BYTE *)winnerSlots + 31 * selected_slot + 9) = new_quantity;
      v48[selected_slot] = 1;
    }
    if ( !applied_loss )
      break;
  }
  Debug_Log(0, 0, a5, (int)aJednostkaZwyci);
  for ( i = 0; i < attackerCount; ++i )
  {
    if ( !*((_BYTE *)winnerSlots + 31 * i + 9) )
      *(__int16 *)((char *)winnerSlots + 31 * i) = -1;
  }
  UnitSlots_RemoveGaps((_WORD *)winnerSlots, attackerCount);
  if ( buildingRecord )
    Building_ApplySiegeDamageToWallSections(buildingRecord, attackerNetScore);
  for ( i = 0; i < loserCount; ++i )
  {
    *loserSlots = -1;
    loserSlots = (_WORD *)((char *)loserSlots + 31);
  }
  return Battle_StoreLastOutcomeValue(0);
}
// 41C719: conditional instruction was optimized away because esi.4>=1
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (0041C8B0) --------------------------------------------------------
signed int  UI_PromptLeadTroopsPersonally(
        int attackerSlots,
        int attackerCount,
        int defenderCount,
        int defenderSlots,
        DWORD a5,
        int a6,
        int showThirdOption)
{
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // eax
  void *v10; // ecx
  int SpriteForChar; // eax
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int attackerSlotIndex; // esi
  unsigned __int8 *v16; // edi
  char v17; // bl
  int v18; // ecx
  _DWORD *v19; // eax
  int v20; // eax
  int defenderSlotIndex; // esi
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
  int userChoice; // esi
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
  _DWORD *promptSpriteSet; // [esp+D4h] [ebp-60h] BYREF
  _DWORD *v49; // [esp+D8h] [ebp-5Ch] BYREF
  _DWORD *v50; // [esp+DCh] [ebp-58h] BYREF
  int v51; // [esp+E0h] [ebp-54h]
  int (*savedRenderHook)(); // [esp+E4h] [ebp-50h]
  int savedResourceHandle; // [esp+E8h] [ebp-4Ch]
  int panelLeft; // [esp+ECh] [ebp-48h]
  int panelTop; // [esp+F0h] [ebp-44h]
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

  v64 = attackerSlots;
  v61 = attackerCount;
  v63 = defenderSlots;
  v60 = defenderCount;
  savedResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(0, defenderSlots, a5, (int)aSetrhS08x_3);
  v9 = (_DWORD *)Mem_Alloc(4112, 0, defenderSlots, a5);
  if ( v9 )
    v9 = DLXSpriteSet_Load(v9, "auto.s32");
  promptSpriteSet = v9;
  Render_Pump();
  g_RenderDevice = &g_MainRenderDevice;
  panelTop = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)promptSpriteSet, 0)) / 2;
  panelLeft = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)promptSpriteSet, 0)) / 2;
  SpriteForChar = DLX_GetSpriteForChar((int)promptSpriteSet, 0);
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  if ( showThirdOption )
  {
    v12 = DLX_GetSpriteForChar((int)promptSpriteSet, 3);
    Compat_RenderDeviceDrawMenuSprite(panelLeft + 59, panelTop + 441, v12, 1);
  }
  Render_ReleaseSurface(7, a5);
  UI_DrawTextFmt(a6, panelTop + 42, panelTop + 166, panelLeft + 85, 3, 1423 * *(unsigned __int8 *)(v64 + 2) + gameData + 140024 + 4);
  UI_DrawTextFmt(a6, panelTop + 395, panelTop + 518, panelLeft + 85, 3, 1423 * *(unsigned __int8 *)(v63 + 2) + gameData + 140024 + 4);
  attackerSlotIndex = 0;
  if ( v61 > 0 )
  {
    v57 = panelLeft + 110;
    v16 = (unsigned __int8 *)v64;
    v58 = panelTop + 18;
    do
    {
      if ( *(__int16 *)v16 != -1 )
      {
        v17 = *(_BYTE *)(v64 + 2);
        UI_BeginUnitInfo(v45, *v16, v17);
        v19 = (_DWORD *)Mem_Alloc(4112, v18, v17, a5);
        if ( v19 )
          v19 = DLXSpriteSet_Load(v19, v45);
        v65 = 76 * ((attackerSlotIndex - (__CFSHL__(attackerSlotIndex >> 31, 2) + 4 * (attackerSlotIndex >> 31))) >> 2) + v57;
        v67 = 48 * (attackerSlotIndex % 4) + v58;
        v49 = v19;
        v20 = DLX_GetSpriteForChar((int)v19, 0);
        Compat_RenderDeviceDrawMenuSprite(v65, v67, v20, 1);
        if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(v64 + 2) + 140051) )
          UI_DrawTextFmt((int)v16, v67, v67 + 32, v65 + 50, 3, (int)aD_3);
        DLXSpriteSet_ReleaseAndClear((int *)&v49);
      }
      a5 = v61;
      ++attackerSlotIndex;
      v16 += 31;
    }
    while ( attackerSlotIndex < v61 );
  }
  defenderSlotIndex = 0;
  if ( v60 > 0 )
  {
    v59 = panelLeft + 110;
    v22 = (unsigned __int8 *)v63;
    v56 = panelTop + 371;
    do
    {
      if ( *(__int16 *)v22 != -1 )
      {
        v23 = *(_BYTE *)(v63 + 2);
        UI_BeginUnitInfo(v46, *v22, v23);
        v25 = (_DWORD *)Mem_Alloc(4112, v24, v23, a5);
        if ( v25 )
          v25 = DLXSpriteSet_Load(v25, v46);
        v66 = 76 * ((defenderSlotIndex - (__CFSHL__(defenderSlotIndex >> 31, 2) + 4 * (defenderSlotIndex >> 31))) >> 2) + v59;
        v68 = 48 * (defenderSlotIndex % 4) + v56;
        v50 = v25;
        v26 = DLX_GetSpriteForChar((int)v25, 0);
        Compat_RenderDeviceDrawMenuSprite(v66, v68, v26, 1);
        if ( *(_DWORD *)(1423 * *(unsigned __int8 *)(v63 + 2) + gameData + 140051) )
          UI_DrawTextFmt((int)v22, v68, v68 + 32, v66 + 50, 3, (int)aD_4);
        DLXSpriteSet_ReleaseAndClear((int *)&v50);
      }
      a5 = v60;
      ++defenderSlotIndex;
      v22 += 31;
    }
    while ( defenderSlotIndex < v60 );
  }
  v47[0] = (int)g_LeadTroopsPersonallyPromptTexts[0];
  v47[1] = (int)g_LeadTroopsPersonallyPromptTexts[1];
  v47[2] = (int)g_LeadTroopsPersonallyPromptTexts[2];
  Render_ReleaseSurface(17, a5);
  UI_DrawTextFmt((int)&promptSpriteSet, panelTop + 160, panelTop + 390, panelLeft + 10, 6, v47[(unsigned __int8)g_LanguageIndex]);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  v27 = panelLeft;
  v28 = panelTop;
  Render_Present((int)g_RenderState);
  v29 = v27 + 61;
  v30 = v28 + 279;
  v62 = panelTop + 201;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_prompt_layout_primary",
    v62,
    v29,
    v62 + (unsigned __int16)DLX_GetSpriteHeight((int)promptSpriteSet, 1u),
    v29 + (unsigned __int16)DLX_GetSpriteWidth((int)promptSpriteSet, 1u));
  Diagnostics_TraceWorldMapActionEvent(
    "battle_prompt_layout_secondary",
    v30,
    v29,
    v30 + (unsigned __int16)DLX_GetSpriteHeight((int)promptSpriteSet, 2u),
    v29 + (unsigned __int16)DLX_GetSpriteWidth((int)promptSpriteSet, 2u));
  while ( 1 )
  {
    do
    {
      WorldMap_RunInputScriptStep();
      DD_Pump((int)g_RenderState, v29);
    }
    while ( !DD_IsFlipping((int)g_RenderState) );
    v31 = v29 + (unsigned __int16)DLX_GetSpriteWidth((int)promptSpriteSet, 1u);
    SpriteHeight = DLX_GetSpriteHeight((int)promptSpriteSet, 1u);
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= v62
      && g_MouseCursorRawY >> g_CursorCoordShift >= v29
      && g_MouseCursorRawX >> g_CursorCoordShift <= SpriteHeight + v62
      && g_MouseCursorRawY >> g_CursorCoordShift <= v31 )
    {
      break;
    }
    v31 = v29 + (unsigned __int16)DLX_GetSpriteWidth((int)promptSpriteSet, 2u);
    v33 = v30 + (unsigned __int16)DLX_GetSpriteHeight((int)promptSpriteSet, 2u);
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= v30
      && g_MouseCursorRawY >> g_CursorCoordShift >= v29
      && g_MouseCursorRawX >> g_CursorCoordShift <= v33
      && g_MouseCursorRawY >> g_CursorCoordShift <= v31 )
    {
      userChoice = 1;
      Audio_PlayButtonSound(aMale);
      goto LABEL_34;
    }
  }
  Audio_PlayButtonSound(aMale_0);
  userChoice = 0;
LABEL_34:
  Render_Pump();
  Debug_Log(0, v29, v31, (int)aUnsetrh08x_3);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, savedResourceHandle);
  SpriteWidth = DLX_GetSpriteWidth((int)promptSpriteSet, 0);
  v39 = DLX_GetSpriteHeight((int)promptSpriteSet, 0);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, panelLeft, panelTop, panelTop + v39, panelLeft + SpriteWidth, panelTop, panelLeft);
  Render_Present((int)g_RenderState);
  DLXSpriteSet_ReleaseAndClear((int *)&promptSpriteSet);
  return userChoice;
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

