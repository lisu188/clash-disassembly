/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (0043A8B0) --------------------------------------------------------
signed int  UnitBattle_SelectAiActionForUnit(int unitIndex, int side)
{
  int unitRecordAddr; // eax
  int bestScore; // ebx
  int scanRow; // esi
  int scanCol; // eax
  int colByteOffset; // edx
  int scoreGridOffset; // ecx
  int cellStateBase; // ebp
  int attemptCount; // eax
  int rangedUnitRecord; // eax
  int targetCol; // ebp
  int unitRecordByteOffset; // ecx
  int unitRecordPtr; // edi
  int v15; // ecx
  int remainingMove; // eax
  int cellStateByteOffset; // ecx
  int *movePath; // edi
  DWORD scanSide; // ebp
  int recordOffset; // edx
  int i; // eax
  int recordAddr; // ecx
  int rowTileOffset; // esi
  int altMovePath; // ecx
  int j; // eax
  int moveAttemptCount; // eax
  int v27; // ecx
  int unitRecordForTrackCheck; // edx
  int trackUnitIndex; // eax
  int trackTargetCol; // ebx
  int *trackResult; // eax
  int *trackPath; // esi
  int unitRecordForForceTrack; // eax
  int unitRecordForFallback; // eax
  int unitRecordForPathTrace; // eax
  int maxMove; // edx
  int pathNodeCount; // edx
  int pathTopIndex; // eax
  int v39; // edx
  int moveCost; // edx
  int moveAllowance; // eax
  int *walkPath; // ecx
  int unitRecordForWalk; // eax
  int unitRecordOffset; // esi
  int walkTopIndex; // edi
  int walkUnitRecord; // eax
  int occupantAtTile; // edx
  int occupantSide; // eax
  int v49; // ecx
  WCIsvListBase *v50; // ecx
  bool shouldRetry; // bl
  int v52; // ecx
  int savedOccupants[66]; // [esp+0h] [ebp-164h]
  int candidateListCopy; // [esp+108h] [ebp-5Ch] BYREF
  void **candidateListVtable; // [esp+10Ch] [ebp-58h]
  int v56; // [esp+110h] [ebp-54h]
  int v57; // [esp+114h] [ebp-50h]
  int v58; // [esp+118h] [ebp-4Ch]
  int v59; // [esp+11Ch] [ebp-48h]
  int trackStep; // [esp+120h] [ebp-44h]
  int rowByteOffset; // [esp+124h] [ebp-40h]
  int savedRow; // [esp+128h] [ebp-3Ch]
  int sideCopy; // [esp+12Ch] [ebp-38h]
  int savedUnitCol; // [esp+130h] [ebp-34h]
  int savedUnitRow; // [esp+134h] [ebp-30h]
  int pathStep; // [esp+138h] [ebp-2Ch]
  int targetRow; // [esp+13Ch] [ebp-28h]
  int unitIndexCopy; // [esp+140h] [ebp-24h]
  int savedCol; // [esp+144h] [ebp-20h]
  int pathNode; // [esp+148h] [ebp-1Ch]
  int unitIndexSaved; // [esp+14Ch] [ebp-18h]

  unitIndexCopy = unitIndex;
  sideCopy = side;
  g_BattleTargetTileCol = -1;
  g_UnitBattleScanTileRow = -1;
  unitRecordAddr = g_MapData + 31 * unitIndex;
  bestScore = 0;
  if ( g_UnitTypeRole[88 * *(__int16 *)(unitRecordAddr + 852)] == 4
    && (*(_BYTE *)(unitRecordAddr + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordAddr + 864)) >> 5) <= 0 )
  {
    g_BattleCellStateGrid[801 * unitIndexCopy - 42] = 5;
    return 1;
  }
  scanRow = 0;
  rowByteOffset = 0;
  while ( scanRow < *(_DWORD *)(g_MapData + 804) )
  {
    scanCol = 0;
    colByteOffset = 0;
    while ( scanCol < *(_DWORD *)(g_MapData + 800) )
    {
      scoreGridOffset = colByteOffset + rowByteOffset + 3204 * unitIndexCopy;
      if ( bestScore > *(int *)((char *)g_UnitBattleTileScoreGrid + scoreGridOffset) )
      {
        g_UnitBattleScanTileRow = scanRow;
        g_BattleTargetTileCol = scanCol;
        bestScore = *(int *)((char *)g_UnitBattleTileScoreGrid + scoreGridOffset);
      }
      colByteOffset += 8;
      ++scanCol;
    }
    ++scanRow;
    rowByteOffset += 160;
  }
  if ( g_UnitBattleAiCurrentPlanMode == 2 || g_UnitBattleAiCurrentPlanMode == 6 )
  {
    g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 6;
    return 1;
  }
  cellStateBase = 801 * unitIndexCopy;
  if ( bestScore < 0 )
  {
    rangedUnitRecord = 31 * unitIndexCopy + g_MapData;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(rangedUnitRecord + 852)] )
    {
      if ( (*(_BYTE *)(rangedUnitRecord + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(rangedUnitRecord + 864)) >> 5) > 0 )
      {
        LOBYTE(bestScore) = g_BattleTargetTileCol;
        if ( UnitBattle_IsTileWithinRange(unitIndexCopy, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
        {
          if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
            && *(unsigned __int8 *)(g_MapData + 31 * unitIndexCopy + 854) == *(_DWORD *)(g_MapData + 836)
            && *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534) == -1 )
          {
            g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + cellStateBase] = 8;
            return 1;
          }
          else
          {
            g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 1;
            return 1;
          }
        }
      }
    }
    targetCol = g_BattleTargetTileCol;
    unitIndexSaved = unitIndexCopy;
    targetRow = g_UnitBattleScanTileRow;
    Debug_Log(31 * unitIndexCopy, bestScore, g_BattleTargetTileCol, (int)aOddzial_w_zasi);
    unitRecordPtr = g_MapData + 852 + unitRecordByteOffset;
    if ( UnitBattle_IsTileWithinRange(unitIndexCopy, targetRow, targetCol)
      && (*(_BYTE *)(g_MapData + v15 + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(g_MapData + v15 + 864)) >> 5) > 0 )
    {
      goto LABEL_24;
    }
    v27 = targetRow;
    if ( *(char *)(g_MapData + 20 * targetRow + targetCol + 3134) <= 0 )
    {
      trackUnitIndex = unitIndexSaved;
      trackTargetCol = targetCol;
    }
    else
    {
      if ( *(__int16 *)(g_MapData + 40 * targetRow + 2 * targetCol + 1534) == -1
        || (v27 = unitIndexSaved, unitRecordForTrackCheck = 31 * unitIndexSaved + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(unitRecordForTrackCheck + 852)] & 1) == 0)
        && (v27 = (*(_BYTE *)(unitRecordForTrackCheck + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForTrackCheck + 864)) >> 5), v27 <= 0) )
      {
        trackResult = UnitBattle_MoveTrackNearWall(unitIndexSaved, targetRow, targetCol, targetCol);
LABEL_58:
        trackPath = trackResult;
        if ( !trackResult )
        {
          unitRecordForForceTrack = g_MapData + 31 * unitIndexSaved;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForForceTrack + 852)] )
          {
            if ( (*(_BYTE *)(unitRecordForForceTrack + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForForceTrack + 864)) >> 5) > 0 )
              trackPath = UnitBattle_MoveTrackForce(unitIndexSaved, targetCol, targetCol);
          }
        }
        if ( !trackPath )
          goto LABEL_63;
        if ( *trackPath )
        {
          unitRecordForPathTrace = g_MapData + 31 * unitIndexSaved;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForPathTrace + 852)]
            && (*(_BYTE *)(unitRecordForPathTrace + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForPathTrace + 864)) >> 5) > 0 )
          {
            savedRow = *(unsigned __int16 *)(unitRecordPtr + 4);
            HIWORD(pathNode) = 0;
            pathNodeCount = *trackPath;
            savedCol = *(unsigned __int16 *)(unitRecordPtr + 6);
            if ( pathNodeCount )
            {
              while ( !UnitBattle_IsTileWithinRange(unitIndexSaved, targetRow, targetCol) )
              {
                pathTopIndex = *trackPath - 1;
                *trackPath = pathTopIndex;
                pathNode = trackPath[pathTopIndex + 1];
                if ( HIWORD(pathNode) > (int)*(unsigned __int8 *)(unitRecordPtr + 8) )
                  goto LABEL_86;
                *(_WORD *)(unitRecordPtr + 4) = (unsigned __int8)pathNode;
                *(_WORD *)(unitRecordPtr + 6) = BYTE1(pathNode);
                if ( !*trackPath )
                  goto LABEL_80;
              }
              *(_WORD *)(unitRecordPtr + 4) = savedRow;
              *(_WORD *)(unitRecordPtr + 6) = savedCol;
              j__nfree_();
              LOWORD(moveCost) = HIWORD(pathNode);
              moveAllowance = *(unsigned __int8 *)(unitRecordPtr + 8);
              if ( moveAllowance <= moveCost )
                goto LABEL_63;
              remainingMove = moveAllowance - moveCost;
              goto LABEL_25;
            }
LABEL_80:
            if ( UnitBattle_IsTileWithinRange(unitIndexSaved, targetRow, targetCol) )
            {
              *(_WORD *)(unitRecordPtr + 4) = savedRow;
              *(_WORD *)(unitRecordPtr + 6) = savedCol;
              if ( *(unsigned __int8 *)(unitRecordPtr + 8) > (int)HIWORD(pathNode) )
              {
                j__nfree_();
                remainingMove = *(unsigned __int8 *)(unitRecordPtr + 8) - v39;
LABEL_25:
                if ( remainingMove >= 5 )
                {
                  if ( *(char *)(g_BattleTargetTileCol + g_MapData + 20 * g_UnitBattleScanTileRow + 3134) > 0
                    && *(unsigned __int8 *)(g_MapData + 31 * unitIndexCopy + 854) == *(_DWORD *)(g_MapData + 836)
                    && *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534) == -1 )
                  {
                    cellStateByteOffset = 160 * g_UnitBattleScanTileRow + 3204 * unitIndexCopy;
                    *(int *)((char *)&g_BattleCellStateGrid[2 * g_BattleTargetTileCol] + cellStateByteOffset) = 8;
                  }
                  else
                  {
                    cellStateByteOffset = 160 * g_UnitBattleScanTileRow + 3204 * unitIndexCopy;
                    *(int *)((char *)&g_BattleCellStateGrid[2 * g_BattleTargetTileCol] + cellStateByteOffset) = 1;
                  }
                  goto LABEL_30;
                }
LABEL_63:
                unitRecordForFallback = g_MapData + 31 * unitIndexCopy;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForFallback + 852)]
                  && (*(_BYTE *)(unitRecordForFallback + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForFallback + 864)) >> 5) <= 0 )
                {
                  g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 5;
                  return 1;
                }
                cellStateByteOffset = 3204 * unitIndexCopy;
                g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 7;
LABEL_30:
                movePath = (int *)UnitBattle_MoveTrackNear(unitIndexCopy, cellStateByteOffset, g_BattleTargetTileCol, targetCol);
                if ( !movePath )
                  movePath = UnitBattle_MoveTrackForce(unitIndexCopy, g_BattleTargetTileCol, targetCol);
                if ( movePath && *movePath )
                {
                  scanSide = sideCopy;
                  recordOffset = 0;
                  for ( i = 0; i != 66; i += 3 )
                  {
                    savedOccupants[i] = -1;
                    recordAddr = g_MapData + recordOffset;
                    if ( *(unsigned __int8 *)(g_MapData + recordOffset + 854) == scanSide && *(__int16 *)(recordAddr + 852) != -1 )
                    {
                      savedOccupants[i] = *(__int16 *)(40 * *(unsigned __int16 *)(recordAddr + 856)
                                          + g_MapData
                                          + 2 * *(unsigned __int16 *)(recordAddr + 858)
                                          + 1534);
                      savedOccupants[i + 1] = *(unsigned __int16 *)(g_MapData + recordOffset + 856);
                      savedOccupants[i + 2] = *(unsigned __int16 *)(g_MapData + recordOffset + 858);
                      rowTileOffset = 40 * *(unsigned __int16 *)(g_MapData + recordOffset + 856);
                      recordAddr = rowTileOffset + g_MapData;
                      *(_WORD *)(rowTileOffset + g_MapData + 2 * *(unsigned __int16 *)(g_MapData + recordOffset + 858) + 1534) = -1;
                    }
                    recordOffset += 31;
                  }
                  altMovePath = UnitBattle_MoveTrackNear(unitIndexCopy, recordAddr, g_BattleTargetTileCol, scanSide);
                  for ( j = 0; j != 66; j += 3 )
                  {
                    if ( savedOccupants[j] != -1 )
                      *(_WORD *)(40 * savedOccupants[j + 1] + g_MapData + 2 * savedOccupants[j + 2] + 1534) = savedOccupants[j];
                  }
                  moveAttemptCount = g_BattleAiActionAttemptCount++;
                  if ( moveAttemptCount > 20 )
                  {
                    g_BattleCellStateGrid[801 * unitIndexCopy + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol] = 5;
                    if ( altMovePath )
                      j__nfree_();
LABEL_123:
                    j__nfree_();
                    return 1;
                  }
                  trackStep = movePath[1];
                  if ( !altMovePath )
                    return 0;
                  pathStep = *(_DWORD *)(altMovePath + 4);
                  j__nfree_();
                  if ( HIWORD(pathStep) < HIWORD(trackStep) )
                  {
                    unitRecordForWalk = g_MapData + 31 * unitIndexCopy;
                    savedUnitRow = *(unsigned __int16 *)(unitRecordForWalk + 856);
                    savedUnitCol = *(unsigned __int16 *)(unitRecordForWalk + 858);
                    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordForWalk + 852)]
                      && (*(_BYTE *)(unitRecordForWalk + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(unitRecordForWalk + 864)) >> 5) > 0
                      && UnitBattle_IsTileWithinRange(unitIndexCopy, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
                    {
                      return 1;
                    }
                    unitRecordOffset = 31 * unitIndexCopy;
                    while ( walkPath && *walkPath )
                    {
                      UnitBattle_UpdateIdleAnimatedUnits();
                      walkTopIndex = *walkPath - 1;
                      *walkPath = walkTopIndex;
                      pathStep = walkPath[walkTopIndex + 1];
                      walkUnitRecord = unitRecordOffset + g_MapData;
                      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordOffset + g_MapData + 852)]
                        && (*(_BYTE *)(walkUnitRecord + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(walkUnitRecord + 864)) >> 5) > 0 )
                      {
                        *(_WORD *)(walkUnitRecord + 856) = (unsigned __int8)pathStep;
                        *(_WORD *)(g_MapData + unitRecordOffset + 858) = BYTE1(pathStep);
                        if ( *(__int16 *)(40 * (unsigned __int8)pathStep + g_MapData + 2 * BYTE1(pathStep) + 1534) == -1
                          && UnitBattle_IsTileWithinRange(unitIndexCopy, g_UnitBattleScanTileRow, g_BattleTargetTileCol) )
                        {
                          *(_WORD *)(unitRecordOffset + g_MapData + 856) = savedUnitRow;
                          *(_WORD *)(g_MapData + unitRecordOffset + 858) = savedUnitCol;
                          if ( !walkPath )
                            return 1;
                          goto LABEL_123;
                        }
                        *(_WORD *)(unitRecordOffset + g_MapData + 856) = savedUnitRow;
                        *(_WORD *)(unitRecordOffset + g_MapData + 858) = savedUnitCol;
                      }
                      occupantAtTile = *(__int16 *)(g_MapData + 40 * (unsigned __int8)pathStep + 2 * BYTE1(pathStep) + 1534);
                      if ( occupantAtTile != -1 )
                      {
                        occupantSide = *(unsigned __int8 *)(31 * occupantAtTile + g_MapData + 854);
                        if ( occupantSide == sideCopy )
                        {
                          candidateListCopy = 0;
                          v56 = sideCopy ^ occupantSide;
                          v57 = 0;
                          v58 = 0;
                          candidateListVtable = &g_WCIsvListBaseVariant124_Vtable;
                          v59 = 0;
                          WCIsvListBase_CopyAppendAll(&candidateListCopy, &g_UnitBattleAiCandidateQueue, (int)walkPath);
                          candidateListVtable = &g_WCIsvListBaseVariant134_Vtable;
                          shouldRetry = WCIsvListBase_PopUntilMatchOrEmpty(v49, (int)&candidateListCopy) && g_BattleAiActionAttemptCount < 20;
                          WCIsvListBase_DestroyElementsAndDtor(v50, (int)&candidateListCopy);
                          if ( shouldRetry )
                          {
                            if ( v52 )
                              j__nfree_();
                            return 0;
                          }
                          if ( !v52 )
                            return 1;
                        }
                        else if ( !walkPath )
                        {
                          return 1;
                        }
                        goto LABEL_123;
                      }
                    }
                  }
                  if ( walkPath )
                    goto LABEL_123;
                }
                else if ( movePath )
                {
                  j__nfree_();
                  return 1;
                }
                return 1;
              }
            }
            else
            {
LABEL_86:
              *(_WORD *)(unitRecordPtr + 4) = savedRow;
              *(_WORD *)(unitRecordPtr + 6) = savedCol;
            }
          }
          else if ( *trackPath )
          {
            pathNode = trackPath[1];
            j__nfree_();
            LOBYTE(maxMove) = *(_BYTE *)(unitRecordPtr + 8);
            if ( maxMove <= HIWORD(pathNode) )
              goto LABEL_63;
            remainingMove = maxMove - HIWORD(pathNode);
            goto LABEL_25;
          }
          j__nfree_();
          goto LABEL_63;
        }
        j__nfree_();
LABEL_24:
        remainingMove = *(unsigned __int8 *)(unitRecordPtr + 8);
        goto LABEL_25;
      }
      trackUnitIndex = unitIndexSaved;
      trackTargetCol = targetCol;
    }
    trackResult = (int *)UnitBattle_MoveTrackNear(trackUnitIndex, v27, trackTargetCol, targetCol);
    goto LABEL_58;
  }
  attemptCount = g_BattleAiActionAttemptCount++;
  if ( attemptCount < 20 )
    return 0;
  g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + cellStateBase] = 5;
  return 1;
}
// 43ADF3: conditional instruction was optimized away because edi.4!=0
// 43B385: conditional instruction was optimized away because edi.4!=0
// 43B3AC: conditional instruction was optimized away because edi.4!=0
// 43AB26: variable 'v13' is possibly undefined
// 43AB44: variable 'v15' is possibly undefined
// 43B152: variable 'v36' is possibly undefined
// 43B272: variable 'v39' is possibly undefined
// 43B2B3: variable 'v40' is possibly undefined
// 43B452: variable 'v42' is possibly undefined
// 43B6D6: variable 'v49' is possibly undefined
// 43B6F6: variable 'v50' is possibly undefined
// 43B701: variable 'v52' is possibly undefined
// 50F124: using guessed type void *off_50F124;
// 50F134: using guessed type void *off_50F134;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532448: using guessed type int dword_532448[];
// 53244C: using guessed type int dword_53244C[17621];
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;
// 5437A8: using guessed type int dword_5437A8;
// 5437C0: using guessed type int dword_5437C0;

//----- (0043B740) --------------------------------------------------------
int  UnitBattle_ApproachToSafeDistance(int unitIndex, int a2, char a3, int a4)
{
  int v4; // edx
  int v5; // edx
  int mapScanBase; // ecx
  __int16 targetCol; // bx
  int nearTrackPtr; // eax
  int v9; // ecx
  int v10; // ebx
  int v12; // eax
  int *v13; // eax
  _DWORD *trackPath; // eax
  int occupantRecordOffset; // edx
  int enemyIndex; // edi
  int enemyRecordPtr; // esi
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // eax
  int *enemyTrack; // eax
  int *enemyTrackPath; // ecx
  int enemyMapBase; // eax
  int enemyRecordBase; // eax
  int v26; // edx
  int *v27; // ecx
  int v28; // edx
  int v29; // eax
  int v30; // eax
  int v31; // edx
  int *v32; // eax
  int trackStep; // [esp+4h] [ebp-40h]
  int movePoints; // [esp+8h] [ebp-3Ch]
  int effectiveness; // [esp+10h] [ebp-34h]
  int unitRecordPtr; // [esp+14h] [ebp-30h]
  __int16 savedCol; // [esp+18h] [ebp-2Ch]
  __int16 savedRow; // [esp+1Ch] [ebp-28h]
  int enemyPathStep; // [esp+24h] [ebp-20h]
  int pathStep; // [esp+24h] [ebp-20h]
  unsigned __int8 destRow; // [esp+28h] [ebp-1Ch]
  unsigned __int8 destCol; // [esp+2Ch] [ebp-18h]

  Debug_Log(a2, a3, a4, (int)aPodejdz_na_bez);
  v5 = 31 * v4 + g_MapData + 852;
  movePoints = *(unsigned __int8 *)(v5 + 8);
  unitRecordPtr = v5;
  mapScanBase = 40 * g_UnitBattleScanTileRow + g_MapData;
  if ( *(__int16 *)(mapScanBase + 2 * g_BattleTargetTileCol + 1534) == -1 )
  {
    targetCol = g_BattleTargetTileCol;
    nearTrackPtr = UnitBattle_MoveTrackNear(unitIndex, mapScanBase, g_BattleTargetTileCol, a4);
    *(_DWORD *)(unitRecordPtr + 23) = nearTrackPtr;
    if ( !nearTrackPtr )
    {
      targetCol = g_BattleTargetTileCol;
      *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, g_BattleTargetTileCol, a4);
    }
    if ( *(_DWORD *)(unitRecordPtr + 23) )
      UnitBattle_Move(unitIndex, v9, targetCol, a4);
    v10 = *(_DWORD *)(unitRecordPtr + 23);
    if ( v10 )
      goto LABEL_7;
    goto LABEL_8;
  }
  LOWORD(v10) = g_BattleTargetTileCol;
  v12 = UnitBattle_MoveTrackNear(unitIndex, mapScanBase, g_BattleTargetTileCol, a4);
  *(_DWORD *)(unitRecordPtr + 23) = v12;
  if ( !v12 )
  {
    LOWORD(v10) = g_BattleTargetTileCol;
    *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, g_BattleTargetTileCol, a4);
  }
  if ( *(_DWORD *)(unitRecordPtr + 23) )
  {
    a4 = 0;
    destRow = -1;
    HIWORD(trackStep) = 0;
    effectiveness = 0;
    while ( 1 )
    {
      if ( !**(_DWORD **)(unitRecordPtr + 23) || HIWORD(trackStep) + 5 > movePoints )
      {
        if ( *(_DWORD *)(unitRecordPtr + 23) )
          j__nfree_();
        v9 = destRow;
        *(_DWORD *)(unitRecordPtr + 23) = 0;
        if ( destRow != 255 )
        {
          LOWORD(v10) = destCol;
          v13 = UnitBattle_MoveTrack(unitIndex, destRow, destRow, destCol, a4);
          *(_DWORD *)(unitRecordPtr + 23) = v13;
          if ( !v13 )
          {
            LOWORD(v10) = destCol;
            *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, destCol, a4);
          }
        }
        if ( *(_DWORD *)(unitRecordPtr + 23) )
          UnitBattle_Move(unitIndex, v9, v10, a4);
        if ( !*(_DWORD *)(unitRecordPtr + 23) )
          goto LABEL_8;
LABEL_7:
        j__nfree_();
        *(_DWORD *)(unitRecordPtr + 23) = 0;
LABEL_8:
        UnitBattle_Defence(v9, v10, a4);
        return 0;
      }
      UnitBattle_UpdateIdleAnimatedUnits();
      trackPath = *(_DWORD **)(unitRecordPtr + 23);
      a4 = *trackPath - 1;
      *trackPath = a4;
      trackStep = trackPath[a4 + 1];
      if ( HIWORD(trackStep) + 5 <= movePoints )
      {
        destCol = BYTE1(trackPath[a4 + 1]);
        destRow = trackPath[a4 + 1];
      }
      occupantRecordOffset = 31 * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534);
      v10 = (unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)(g_MapData + occupantRecordOffset + 852)];
      if ( v10 != 4 )
        break;
LABEL_35:
      if ( v9 * effectiveness > 20 )
      {
        if ( destRow == 255 )
        {
          a4 = *(_DWORD *)(unitRecordPtr + 23);
          if ( !a4 )
            goto LABEL_8;
        }
        else
        {
          if ( *(_DWORD *)(unitRecordPtr + 23) )
            j__nfree_();
          LOWORD(v10) = destCol;
          *(_DWORD *)(unitRecordPtr + 23) = 0;
          v32 = UnitBattle_MoveTrack(unitIndex, destRow, destRow, destCol, a4);
          *(_DWORD *)(unitRecordPtr + 23) = v32;
          if ( !v32 )
          {
            LOWORD(v10) = destCol;
            *(_DWORD *)(unitRecordPtr + 23) = UnitBattle_MoveTrackForce(unitIndex, destCol, a4);
          }
          if ( *(_DWORD *)(unitRecordPtr + 23) )
            UnitBattle_Move(unitIndex, v9, v10, a4);
          if ( !*(_DWORD *)(unitRecordPtr + 23) )
            goto LABEL_8;
        }
        goto LABEL_7;
      }
    }
    effectiveness = Unit_CalcEffectivenessA((char *)(occupantRecordOffset + g_MapData + 852), 0);
    if ( effectiveness < Unit_CalcEffectivenessC((__int16 *)(31
                                                 * *(__int16 *)(g_MapData
                                                              + 40 * g_UnitBattleScanTileRow
                                                              + 2 * g_BattleTargetTileCol
                                                              + 1534)
                                                 + g_MapData
                                                 + 852)) )
      effectiveness = Unit_CalcEffectivenessC((__int16 *)(31
                                              * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534)
                                              + g_MapData
                                              + 852));
    LOWORD(v10) = BYTE1(trackStep);
    enemyIndex = *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534);
    Debug_Log(enemyIndex, SBYTE1(trackStep), a4, (int)aOddzial_w_zasi);
    enemyRecordPtr = g_MapData + 852 + 31 * enemyIndex;
    a4 = v18;
    if ( UnitBattle_IsTileWithinRange(v19, v18, BYTE1(trackStep))
      && (*(_BYTE *)(31 * enemyIndex + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(31 * enemyIndex + g_MapData + 864)) >> 5) > 0 )
    {
      v20 = 0;
LABEL_33:
      LOBYTE(v20) = *(_BYTE *)(enemyRecordPtr + 8);
LABEL_34:
      v9 = v20 / 5;
      goto LABEL_35;
    }
    if ( *(char *)(BYTE1(trackStep) + g_MapData + 20 * a4 + 3134) <= 0 )
    {
      v10 = BYTE1(trackStep);
    }
    else
    {
      if ( *(__int16 *)(g_MapData + 40 * a4 + 2 * BYTE1(trackStep) + 1534) == -1
        || (v21 = 31 * enemyIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(v21 + 852)] & 1) == 0)
        && (*(_BYTE *)(v21 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(v21 + 864)) >> 5) <= 0 )
      {
        LOWORD(v10) = BYTE1(trackStep);
        enemyTrack = UnitBattle_MoveTrackNearWall(enemyIndex, a4, BYTE1(trackStep), a4);
        goto LABEL_44;
      }
      v10 = BYTE1(trackStep);
    }
    enemyTrack = (int *)UnitBattle_MoveTrackNear(enemyIndex, BYTE1(trackStep), v10, a4);
LABEL_44:
    enemyTrackPath = enemyTrack;
    if ( !enemyTrack )
    {
      enemyMapBase = 31 * enemyIndex + g_MapData;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyMapBase + 852)] )
      {
        if ( (*(_BYTE *)(enemyMapBase + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyMapBase + 864)) >> 5) > 0 )
        {
          LOWORD(v10) = BYTE1(trackStep);
          enemyTrackPath = UnitBattle_MoveTrackForce(enemyIndex, BYTE1(trackStep), a4);
        }
      }
    }
    if ( !enemyTrackPath )
    {
      v20 = -1;
      goto LABEL_34;
    }
    if ( !*enemyTrackPath )
    {
      j__nfree_();
      goto LABEL_33;
    }
    enemyRecordBase = g_MapData + 31 * enemyIndex;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyRecordBase + 852)]
      && (*(_BYTE *)(enemyRecordBase + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyRecordBase + 864)) >> 5) > 0 )
    {
      savedRow = *(_WORD *)(enemyRecordPtr + 4);
      HIWORD(pathStep) = 0;
      savedCol = *(_WORD *)(enemyRecordPtr + 6);
      if ( *enemyTrackPath )
      {
        while ( 1 )
        {
          LOWORD(v10) = BYTE1(trackStep);
          if ( UnitBattle_IsTileWithinRange(enemyIndex, a4, BYTE1(trackStep)) )
            break;
          v30 = *v27 - 1;
          *v27 = v30;
          pathStep = v27[v30 + 1];
          if ( HIWORD(pathStep) > (int)*(unsigned __int8 *)(enemyRecordPtr + 8) )
            goto LABEL_72;
          *(_WORD *)(enemyRecordPtr + 4) = (unsigned __int8)pathStep;
          *(_WORD *)(enemyRecordPtr + 6) = BYTE1(pathStep);
          if ( !*v27 )
            goto LABEL_69;
        }
        *(_WORD *)(enemyRecordPtr + 4) = savedRow;
        *(_WORD *)(enemyRecordPtr + 6) = savedCol;
        j__nfree_();
        LOWORD(v28) = HIWORD(pathStep);
        v29 = *(unsigned __int8 *)(enemyRecordPtr + 8);
        if ( v29 > v28 )
        {
          v20 = v29 - v28;
          goto LABEL_34;
        }
LABEL_66:
        v20 = 0;
        goto LABEL_34;
      }
LABEL_69:
      LOWORD(v10) = BYTE1(trackStep);
      if ( !UnitBattle_IsTileWithinRange(enemyIndex, a4, BYTE1(trackStep)) )
      {
LABEL_72:
        *(_WORD *)(enemyRecordPtr + 4) = savedRow;
        *(_WORD *)(enemyRecordPtr + 6) = savedCol;
        j__nfree_();
        goto LABEL_34;
      }
      *(_WORD *)(enemyRecordPtr + 4) = savedRow;
      *(_WORD *)(enemyRecordPtr + 6) = savedCol;
      if ( *(unsigned __int8 *)(enemyRecordPtr + 8) > (int)HIWORD(pathStep) )
      {
        j__nfree_();
        v20 = *(unsigned __int8 *)(enemyRecordPtr + 8) - v31;
        goto LABEL_34;
      }
    }
    else if ( *enemyTrackPath )
    {
      enemyPathStep = enemyTrackPath[1];
      j__nfree_();
      LOBYTE(v26) = *(_BYTE *)(enemyRecordPtr + 8);
      if ( v26 <= HIWORD(enemyPathStep) )
        v20 = 0;
      else
        v20 = v26 - HIWORD(enemyPathStep);
      goto LABEL_34;
    }
    j__nfree_();
    goto LABEL_66;
  }
  return 0;
}
// 43B76C: variable 'v4' is possibly undefined
// 43B7F1: variable 'v9' is possibly undefined
// 43B8C0: variable 'v43' is possibly undefined
// 43BA5B: variable 'v18' is possibly undefined
// 43BA5D: variable 'v19' is possibly undefined
// 43BAAC: variable 'v20' is possibly undefined
// 43BC59: variable 'v26' is possibly undefined
// 43BCF5: variable 'v28' is possibly undefined
// 43BD15: variable 'v27' is possibly undefined
// 43BD8E: variable 'v31' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;

//----- (0043BE50) --------------------------------------------------------
int  UnitBattle_ExecuteAiActionForUnit(int unitIndex, int side, DWORD gameContext)
{
  DWORD unitRecordOffset; // ebx
  DWORD cellStateBase; // edi
  int v6; // ecx
  int result; // eax
  __int16 targetCol; // bx
  int *v9; // eax
  int v10; // ecx
  __int16 meleeTargetCol; // bx
  int v12; // eax
  int v13; // ecx
  int targetStrength; // ebp
  int ownStrength; // edi
  int targetRemaining; // ebp
  int ownRemaining; // edi
  DWORD wallUnitRecordOffset; // edi
  int v19; // ecx
  int ownLoss; // [esp+0h] [ebp-2Ch] BYREF
  int targetLoss; // [esp+4h] [ebp-28h] BYREF
  int netExchange; // [esp+8h] [ebp-24h]
  signed int actionResult; // [esp+Ch] [ebp-20h]
  DWORD meleeUnitRecordOffset; // [esp+10h] [ebp-1Ch]
  __int16 *unitRecord; // [esp+14h] [ebp-18h]

  unitRecordOffset = 31 * unitIndex;
  unitRecord = (__int16 *)(31 * unitIndex + g_MapData + 852);
  cellStateBase = 801 * unitIndex;
  actionResult = 0;
  UnitBattle_UpdateIdleAnimatedUnits();
  v6 = g_UnitBattleScanTileRow;
  switch ( g_BattleCellStateGrid[40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + cellStateBase] )
  {
    case BATTLE_AI_CELL_MELEE:
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(unitRecordOffset + g_MapData + 852)] )
      {
        v6 = (unitRecord[6] & 3) + 1 - ((unsigned __int8)(2 * *((_BYTE *)unitRecord + 12)) >> 5);
        if ( v6 > 0 )
          goto LABEL_4;
      }
      meleeTargetCol = g_BattleTargetTileCol;
      v12 = UnitBattle_MoveTrackNear(unitIndex, v6, g_BattleTargetTileCol, gameContext);
      *(_DWORD *)((char *)unitRecord + 23) = v12;
      if ( v12 )
        UnitBattle_Move(unitIndex, v13, meleeTargetCol, gameContext);
      if ( *(_DWORD *)((char *)unitRecord + 23) )
      {
        j__nfree_();
        *(_DWORD *)((char *)unitRecord + 23) = 0;
      }
      meleeUnitRecordOffset = 31 * unitIndex;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        targetStrength = *(char *)(31 * *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534)
                      + g_MapData
                      + 861);
        ownStrength = *((char *)unitRecord + 9);
        UnitBattle_CalcMeleeExchange(unitIndex, *(__int16 *)(g_MapData + 40 * g_UnitBattleScanTileRow + 2 * g_BattleTargetTileCol + 1534), &targetLoss, &ownLoss, 0);
        netExchange = targetStrength - targetLoss - (ownStrength - ownLoss);
        UnitBattle_CalcMeleeExchange(unitIndex, *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534), &targetLoss, &ownLoss, 1);
        targetRemaining = targetStrength - targetLoss;
        ownRemaining = ownStrength - ownLoss;
        if ( targetRemaining <= 0 && ownRemaining <= 0
          || !UnitBattle_Attack(
                unitIndex,
                *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534),
                targetRemaining - ownRemaining > netExchange)
          || *(__int16 *)(g_MapData + meleeUnitRecordOffset + 852) == -1 )
        {
          goto LABEL_5;
        }
      }
      while ( *(__int16 *)(40 * g_UnitBattleScanTileRow + g_MapData + 2 * g_BattleTargetTileCol + 1534) != -1 );
      if ( *(unsigned __int8 *)(g_MapData + meleeUnitRecordOffset + 860) <= 4u )
        goto LABEL_5;
      actionResult = 1;
      result = 1;
      break;
    case BATTLE_AI_CELL_NOOP:
      result = 0;
      break;
    case BATTLE_AI_CELL_FORCE_MOVE:
      targetCol = g_BattleTargetTileCol;
      v9 = UnitBattle_MoveTrackForce(unitIndex, g_BattleTargetTileCol, gameContext);
      *(_DWORD *)((char *)unitRecord + 23) = v9;
      if ( v9 )
        UnitBattle_Move(unitIndex, v10, targetCol, gameContext);
      if ( *(_DWORD *)((char *)unitRecord + 23) )
      {
        j__nfree_();
        *(_DWORD *)((char *)unitRecord + 23) = 0;
      }
      result = 0;
      break;
    case BATTLE_AI_CELL_KITE:
      result = UnitBattle_ApproachToSafeDistance(unitIndex, g_UnitBattleScanTileRow, unitRecordOffset, gameContext);
      break;
    case BATTLE_AI_CELL_SHOOT:
      if ( g_UnitTypeMaxRange_512582[88 * *unitRecord] && (unitRecord[6] & 3) + 1 - ((unsigned __int8)(2 * *((_BYTE *)unitRecord + 12)) >> 5) > 0 )
      {
LABEL_4:
        UnitBattle_UpdateIdleAnimatedUnits();
        actionResult = UnitBattle_MoveShootingUnit(unitIndex, side, unitRecordOffset, gameContext);
        goto LABEL_5;
      }
      wallUnitRecordOffset = 31 * unitIndex;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( !UnitBattle_AttackWall(unitIndex, g_UnitBattleScanTileRow, v19, g_BattleTargetTileCol) || *(__int16 *)(g_MapData + wallUnitRecordOffset + 852) == -1 )
          goto LABEL_5;
      }
      while ( *(_BYTE *)(g_BattleTargetTileCol + 20 * g_UnitBattleScanTileRow + g_MapData + 3134) );
      if ( *(unsigned __int8 *)(g_MapData + wallUnitRecordOffset + 860) <= 4u )
        goto LABEL_5;
      actionResult = 1;
      result = 1;
      break;
    default:
LABEL_5:
      result = actionResult;
      break;
  }
  return result;
}
// 43BF67: variable 'v10' is possibly undefined
// 43BF9E: variable 'v13' is possibly undefined
// 43C147: variable 'v19' is possibly undefined
// 532048: using guessed type int g_MapData;
// 532448: using guessed type int dword_532448[];
// 5437A0: using guessed type int dword_5437A0;
// 5437A4: using guessed type int dword_5437A4;

//----- (0043C1E0) --------------------------------------------------------
signed int  UnitBattle_BuildAiUnitQueueForCurrentMode(int side)
{
  int v1; // edx
  int v2; // ecx
  int bestEffectiveness; // esi
  int slotCounter; // ebx
  int slotByteOffset; // ecx
  int candidateId; // eax
  char *candidateRecord; // eax
  int k; // ecx
  int role4UnitId; // eax
  int m; // ecx
  signed int result; // eax
  int colIndex; // ebx
  int colByteOffset; // edx
  int writeOffset; // eax
  int tileAddr; // edi
  int occupantUnitIndex; // esi
  __int16 occupantId; // cx
  int nextOccupantCount; // edi
  int firstUnitRow; // ecx
  int j; // ebx
  int i; // ebx
  int slotCounter2; // ecx
  char *candidateRecord2; // eax
  int bestEffectiveness2; // esi
  int slotByteOffset2; // ebx
  int n; // ebx
  int role4UnitId2; // eax
  int ii; // ecx
  int rangedUnitId; // eax
  int candidateId2; // eax
  int candidateRecordOffset; // eax
  int hasMoreUnits; // ecx
  __int16 v33; // [esp+0h] [ebp-72h]
  WCIsvListBase *occupantUnitIds[5]; // [esp+2h] [ebp-70h]
  int rowByteOffsetCopy; // [esp+16h] [ebp-5Ch]
  int forwardUnitId; // [esp+1Ah] [ebp-58h]
  int reverseUnitId; // [esp+1Eh] [ebp-54h]
  int bestMeleeUnitId; // [esp+22h] [ebp-50h]
  int role4Id; // [esp+26h] [ebp-4Ch]
  int rangedId; // [esp+2Ah] [ebp-48h]
  int planRole4Id; // [esp+2Eh] [ebp-44h]
  int planRangedId; // [esp+32h] [ebp-40h]
  int bestUnitId; // [esp+36h] [ebp-3Ch]
  int rowIndex; // [esp+3Ah] [ebp-38h]
  int rowByteOffset; // [esp+3Eh] [ebp-34h]
  int sideCopy; // [esp+42h] [ebp-30h]
  int foundMeleeUnit; // [esp+46h] [ebp-2Ch]
  int foundUnit; // [esp+4Ah] [ebp-28h]
  int bestSlot; // [esp+4Eh] [ebp-24h]
  signed int bestSlot2; // [esp+52h] [ebp-20h]
  int occupantCount; // [esp+56h] [ebp-1Ch]

  sideCopy = side;
  WCIsvListBase_base_destroy((WCIsvListBase *)&g_UnitBattleAiCandidateQueue);
  memset(occupantUnitIds, 0xFF, 20);
  occupantCount = 0;
  rowIndex = 0;
  rowByteOffset = 0;
  while ( *(_DWORD *)(g_MapData + 804) - 1 >= rowIndex )
  {
    colIndex = 0;
    rowByteOffsetCopy = rowByteOffset;
    colByteOffset = 0;
    writeOffset = 2 * occupantCount;
    while ( colIndex <= *(_DWORD *)(g_MapData + 800) - 1 )
    {
      tileAddr = colByteOffset + g_MapData + rowByteOffsetCopy;
      occupantUnitIndex = *(__int16 *)(tileAddr + 1534);
      if ( occupantUnitIndex == -1 || *(unsigned __int8 *)(g_MapData + 31 * occupantUnitIndex + 854) != sideCopy )
      {
        colByteOffset += 2;
        ++colIndex;
      }
      else
      {
        occupantId = *(_WORD *)(tileAddr + 1534);
        writeOffset += 2;
        nextOccupantCount = occupantCount + 1;
        *(__int16 *)((char *)&v33 + writeOffset) = occupantId;
        occupantCount = nextOccupantCount;
        colByteOffset += 2;
        ++colIndex;
      }
    }
    rowByteOffset += 40;
    ++rowIndex;
  }
  if ( (unsigned int)g_UnitBattleAiCurrentPlanMode >= 2 )
  {
    if ( (unsigned int)g_UnitBattleAiCurrentPlanMode <= 2 || g_UnitBattleAiCurrentPlanMode == 6 )
    {
      firstUnitRow = *(unsigned __int16 *)(g_MapData + 31 * SLOWORD(occupantUnitIds[0]) + 856);
      if ( (unsigned __int16)firstUnitRow >= *(_DWORD *)(g_MapData + 804) / 2 )
      {
        for ( i = 0; i != 20; i += 2 )
        {
          result = *(__int16 *)((char *)occupantUnitIds + i);
          if ( result != -1 )
          {
            forwardUnitId = *(__int16 *)((char *)occupantUnitIds + i);
            result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, forwardUnitId);
          }
        }
      }
      else
      {
        for ( j = 18; j != -2; j -= 2 )
        {
          result = *(__int16 *)((char *)occupantUnitIds + j);
          if ( result != -1 )
          {
            reverseUnitId = *(__int16 *)((char *)occupantUnitIds + j);
            result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, reverseUnitId);
          }
        }
      }
      return result;
    }
  }
  else if ( !g_UnitBattleAiCurrentPlanMode )
  {
    do
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      bestEffectiveness = -1;
      foundMeleeUnit = 0;
      bestSlot = 0;
      slotCounter = 0;
      slotByteOffset = 0;
      do
      {
        candidateId = *(__int16 *)((char *)occupantUnitIds + slotByteOffset);
        if ( candidateId != -1 && !g_UnitTypeMaxRange_512582[88 * *(__int16 *)(31 * candidateId + g_MapData + 852)] )
        {
          foundMeleeUnit = 1;
          if ( bestEffectiveness < Unit_CalcEffectivenessA((char *)(31 * candidateId + g_MapData + 852), 0) )
          {
            candidateRecord = (char *)(31 * *(__int16 *)((char *)occupantUnitIds + slotByteOffset) + g_MapData + 852);
            bestSlot = slotCounter;
            bestEffectiveness = Unit_CalcEffectivenessA(candidateRecord, 0);
          }
        }
        ++slotCounter;
        slotByteOffset += 2;
      }
      while ( slotCounter < 10 );
      if ( *((__int16 *)occupantUnitIds + bestSlot) != -1 )
      {
        bestMeleeUnitId = *((__int16 *)occupantUnitIds + bestSlot);
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, bestMeleeUnitId);
      }
      *((_WORD *)occupantUnitIds + bestSlot) = -1;
    }
    while ( foundMeleeUnit );
    for ( k = 0; k != 20; k += 2 )
    {
      role4UnitId = *(__int16 *)((char *)occupantUnitIds + k);
      if ( role4UnitId != -1 && g_UnitTypeRole[88 * *(__int16 *)(31 * role4UnitId + g_MapData + 852)] == 4 )
      {
        role4Id = *(__int16 *)((char *)occupantUnitIds + k);
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, role4Id);
        *(_WORD *)((char *)occupantUnitIds + k) = -1;
      }
    }
    for ( m = 0; m != 20; m += 2 )
    {
      result = *(__int16 *)((char *)occupantUnitIds + m);
      if ( result != -1 )
      {
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(31 * result + g_MapData + 852)] )
        {
          rangedId = *(__int16 *)((char *)occupantUnitIds + m);
          result = WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, rangedId);
          *(_WORD *)((char *)occupantUnitIds + m) = -1;
        }
      }
    }
    return result;
  }
  for ( n = 0; n != 20; n += 2 )
  {
    role4UnitId2 = *(__int16 *)((char *)occupantUnitIds + n);
    if ( role4UnitId2 != -1 && g_UnitTypeRole[88 * *(__int16 *)(31 * role4UnitId2 + g_MapData + 852)] == 4 )
    {
      planRole4Id = *(__int16 *)((char *)occupantUnitIds + n);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, planRole4Id);
      *(_WORD *)((char *)occupantUnitIds + n) = -1;
    }
  }
  for ( ii = 0; ii != 20; ii += 2 )
  {
    rangedUnitId = *(__int16 *)((char *)occupantUnitIds + ii);
    if ( rangedUnitId != -1 && g_UnitTypeMaxRange_512582[88 * *(__int16 *)(g_MapData + 31 * rangedUnitId + 852)] )
    {
      planRangedId = *(__int16 *)((char *)occupantUnitIds + ii);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, planRangedId);
      *(_WORD *)((char *)occupantUnitIds + ii) = -1;
    }
  }
  do
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    bestEffectiveness2 = -1;
    foundUnit = 0;
    bestSlot2 = 0;
    slotCounter2 = 0;
    slotByteOffset2 = 0;
    while ( 1 )
    {
      candidateId2 = *(__int16 *)((char *)occupantUnitIds + slotByteOffset2);
      if ( candidateId2 != -1 )
        break;
LABEL_45:
      ++slotCounter2;
      slotByteOffset2 += 2;
      if ( slotCounter2 >= 10 )
        goto LABEL_63;
    }
    candidateRecordOffset = 31 * candidateId2;
    foundUnit = 1;
    if ( g_UnitTypeRole[88 * *(__int16 *)(g_MapData + candidateRecordOffset + 852)] != 4 )
    {
      if ( bestEffectiveness2 < Unit_CalcEffectivenessA((char *)(g_MapData + 852 + candidateRecordOffset), 0) )
      {
        candidateRecord2 = (char *)(31 * *(__int16 *)((char *)occupantUnitIds + slotByteOffset2) + g_MapData + 852);
        bestSlot2 = slotCounter2;
        bestEffectiveness2 = Unit_CalcEffectivenessA(candidateRecord2, 0);
      }
      goto LABEL_45;
    }
    bestSlot2 = slotCounter2;
LABEL_63:
    if ( *((__int16 *)occupantUnitIds + bestSlot2) != -1 )
    {
      bestUnitId = *((__int16 *)occupantUnitIds + bestSlot2);
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, bestUnitId);
    }
    result = bestSlot2;
    hasMoreUnits = foundUnit;
    *((_WORD *)occupantUnitIds + bestSlot2) = -1;
  }
  while ( hasMoreUnits );
  return result;
}
// 43C351: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C3AE: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C591: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C5EE: conditional instruction was optimized away because eax.4 is in (<8000u|FFFF8000..FFFFFFFE)
// 43C203: variable 'v2' is possibly undefined
// 43C203: variable 'v1' is possibly undefined
// 43C2B4: variable 'v5' is possibly undefined
// 43C362: variable 'k' is possibly undefined
// 43C3BF: variable 'm' is possibly undefined
// 43C4B3: variable 'v19' is possibly undefined
// 43C51E: variable 'v22' is possibly undefined
// 43C5FF: variable 'ii' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 5437C0: using guessed type int dword_5437C0;

//----- (0043C6B0) --------------------------------------------------------
signed int  UnitBattle_ScanAiPlanRangeLine(int side, signed int scanDirection)
{
  int i; // eax
  int recordAddr; // edx
  int projectedRow; // edx
  int targetRow; // ebp
  int enemyRecordAddr; // ebx
  int targetCol; // ebx
  int recordBase; // esi
  int v9; // edx
  BOOL inRange; // eax
  int v11; // ecx
  int enemyRecord; // esi
  int v14; // ecx
  int enemyUnitRecord; // eax
  int *trackList; // eax
  int *track; // ecx
  int enemyUnitRecord2; // eax
  int enemyUnitRecord3; // eax
  int pathMoveCost; // edx
  int rangeValue; // eax
  int *v22; // ecx
  int trackIndex; // eax
  int v24; // edx
  int unitRange; // edx
  int firstTrackStep; // [esp+8h] [ebp-34h]
  int trackEntry; // [esp+8h] [ebp-34h]
  int enemyRecordOffset; // [esp+10h] [ebp-2Ch]
  int battle_width;
  int battle_height;
  __int16 savedTileRow; // [esp+14h] [ebp-28h]
  __int16 savedTileCol; // [esp+18h] [ebp-24h]
  int bestProjectedRow; // [esp+1Ch] [ebp-20h]
  int enemyUnitIndex; // [esp+20h] [ebp-1Ch]

  bestProjectedRow = -20;
  Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_enter", side, scanDirection, g_AttackerStartsOnLeft, g_DefenderStartsOnLeft);
  if ( *(_DWORD *)(g_MapData + 836) == side )
  {
    if ( g_AttackerStartsOnLeft )
      scanDirection = 1;
    else
      scanDirection = -1;
  }
  if ( side == *(_DWORD *)(g_MapData + 840) )
  {
    if ( g_DefenderStartsOnLeft )
      scanDirection = 1;
    else
      scanDirection = -1;
  }
  for ( i = 0; i != 682; i += 31 )
  {
    recordAddr = i + g_MapData;
    if ( *(__int16 *)(i + g_MapData + 852) != -1 && *(unsigned __int8 *)(recordAddr + 854) == side )
    {
      projectedRow = scanDirection * *(unsigned __int16 *)(recordAddr + 856);
      if ( projectedRow > bestProjectedRow )
        bestProjectedRow = projectedRow;
    }
  }
  enemyUnitIndex = 0;
  enemyRecordOffset = 0;
  targetRow = scanDirection * (bestProjectedRow + 3);
  battle_width = *(_DWORD *)(g_MapData + 800);
  battle_height = *(_DWORD *)(g_MapData + 804);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_ai_plan_range_line",
    side,
    targetRow,
    battle_width,
    battle_height);
  if ( targetRow < 0 || targetRow >= battle_height )
    return 0;
  while ( 1 )
  {
    enemyRecordAddr = g_MapData + enemyRecordOffset;
    if ( *(__int16 *)(g_MapData + enemyRecordOffset + 852) == -1 || *(unsigned __int8 *)(enemyRecordAddr + 854) == side )
      goto LABEL_23;
    targetCol = *(unsigned __int16 *)(enemyRecordAddr + 858);
    Diagnostics_TraceWorldMapActionEvent(
      "battle_ai_plan_range_candidate",
      enemyUnitIndex,
      targetRow,
      targetCol,
      *(__int16 *)(enemyRecordAddr + 852));
    if ( targetCol < 0 || targetCol >= battle_width )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_skip_oob_target", enemyUnitIndex, targetRow, targetCol, battle_width);
      goto LABEL_23;
    }
    if ( *(__int16 *)(40 * targetRow + g_MapData + 2 * targetCol + 1534) != -1 )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_target_occupied", enemyUnitIndex, targetRow, targetCol, 0);
      return 0;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_before_log", enemyUnitIndex, targetRow, targetCol, side);
    Debug_Log(side, targetCol, targetRow, (int)aOddzial_w_zasi);
    recordBase = g_MapData + 852;
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_before_range", enemyUnitIndex, targetRow, targetCol, side);
    inRange = UnitBattle_IsTileWithinRange(enemyUnitIndex, targetRow, targetCol);
    Diagnostics_TraceWorldMapActionEvent("battle_ai_plan_range_after_range", enemyUnitIndex, targetRow, targetCol, inRange);
    enemyRecord = g_MapData + enemyRecordOffset + 852;
    if ( inRange
      && (*(_BYTE *)(enemyRecordOffset + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(enemyRecordOffset + g_MapData + 864)) >> 5) > 0 )
    {
      goto LABEL_17;
    }
    v14 = targetCol;
    if ( *(char *)(targetCol + g_MapData + 20 * targetRow + 3134) <= 0
      || (v14 = g_MapData + 40 * targetRow, *(__int16 *)(v14 + 2 * targetCol + 1534) != -1)
      && ((enemyUnitRecord = 31 * enemyUnitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(enemyUnitRecord + 852)] & 1) != 0)
       || (v14 = (unsigned __int8)(2 * *(_BYTE *)(enemyUnitRecord + 864)) >> 5, (*(_BYTE *)(enemyUnitRecord + 864) & 3) + 1 - v14 > 0)) )
    {
      trackList = UnitBattle_MoveTrackNear(enemyUnitIndex, targetRow, targetCol, targetRow);
    }
    else
    {
      trackList = UnitBattle_MoveTrackNearWall(enemyUnitIndex, targetRow, targetCol, targetRow);
    }
    track = trackList;
    if ( !trackList )
    {
      enemyUnitRecord2 = g_MapData + 31 * enemyUnitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyUnitRecord2 + 852)] )
      {
        if ( (*(_BYTE *)(enemyUnitRecord2 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyUnitRecord2 + 864)) >> 5) > 0 )
          track = UnitBattle_MoveTrackForce(enemyUnitIndex, targetCol, targetRow);
      }
    }
    if ( !track )
      goto LABEL_23;
    if ( !*track )
    {
      nfree_((int)(uintptr_t)track);
LABEL_17:
      if ( *(_BYTE *)(enemyRecord + 8) )
        return 0;
      goto LABEL_23;
    }
    enemyUnitRecord3 = 31 * enemyUnitIndex + g_MapData;
    if ( !g_UnitTypeMaxRange_512582[88 * *(__int16 *)(enemyUnitRecord3 + 852)]
      || (*(_BYTE *)(enemyUnitRecord3 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(enemyUnitRecord3 + 864)) >> 5) <= 0 )
    {
      if ( !*track )
        goto LABEL_59;
      firstTrackStep = track[1];
      nfree_((int)(uintptr_t)track);
      LOWORD(pathMoveCost) = HIWORD(firstTrackStep);
      rangeValue = *(unsigned __int8 *)(enemyRecord + 8);
      if ( rangeValue > pathMoveCost && rangeValue - pathMoveCost > 0 )
        return 0;
      goto LABEL_23;
    }
    savedTileRow = *(_WORD *)(enemyRecord + 4);
    HIWORD(trackEntry) = 0;
    savedTileCol = *(_WORD *)(enemyRecord + 6);
    if ( *track )
      break;
LABEL_50:
    if ( !UnitBattle_IsTileWithinRange(enemyUnitIndex, targetRow, targetCol) )
    {
LABEL_58:
      *(_WORD *)(enemyRecord + 4) = savedTileRow;
      *(_WORD *)(enemyRecord + 6) = savedTileCol;
LABEL_59:
      nfree_((int)(uintptr_t)track);
      goto LABEL_23;
    }
    *(_WORD *)(enemyRecord + 4) = savedTileRow;
    *(_WORD *)(enemyRecord + 6) = savedTileCol;
    if ( *(unsigned __int8 *)(enemyRecord + 8) <= (int)HIWORD(trackEntry) )
      goto LABEL_59;
    nfree_((int)(uintptr_t)track);
    if ( *(unsigned __int8 *)(enemyRecord + 8) - HIWORD(trackEntry) > 0 )
      return 0;
LABEL_23:
    enemyRecordOffset += 31;
    if ( ++enemyUnitIndex >= 22 )
      return 1;
  }
  while ( !UnitBattle_IsTileWithinRange(enemyUnitIndex, targetRow, targetCol) )
  {
    trackIndex = *track - 1;
    *track = trackIndex;
    trackEntry = track[trackIndex + 1];
    if ( HIWORD(trackEntry) > (int)*(unsigned __int8 *)(enemyRecord + 8) )
      goto LABEL_58;
    *(_WORD *)(enemyRecord + 4) = (unsigned __int8)trackEntry;
    *(_WORD *)(enemyRecord + 6) = BYTE1(trackEntry);
    if ( !*track )
      goto LABEL_50;
  }
  *(_WORD *)(enemyRecord + 4) = savedTileRow;
  *(_WORD *)(enemyRecord + 6) = savedTileCol;
  nfree_((int)(uintptr_t)track);
  unitRange = *(unsigned __int8 *)(enemyRecord + 8);
  if ( unitRange <= HIWORD(trackEntry) || unitRange - HIWORD(trackEntry) <= 0 )
    goto LABEL_23;
  return 0;
}
// 43C807: variable 'v9' is possibly undefined
// 43C80C: variable 'v11' is possibly undefined
// 43C9FF: variable 'v20' is possibly undefined
// 43CA80: variable 'v22' is possibly undefined
// 43CB00: variable 'v24' is possibly undefined
// 43CB45: variable 'v25' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
// 53206C: using guessed type int g_AttackerStartsOnLeft;
// 532070: using guessed type int g_DefenderStartsOnLeft;

//----- (0043CB80) --------------------------------------------------------
void UnitBattle_ScanAiWallTargetColumns()
{
  int scanRow; // edx
  int rowByteOffset; // ecx
  int scanCol; // eax
  int scanRowByteOffset; // esi
  int tileAddr; // edx
  int battle_width;
  int battle_height;
  int wall_column;

  battle_width = *(_DWORD *)(g_MapData + 800);
  battle_height = *(_DWORD *)(g_MapData + 804);
  wall_column = *(_DWORD *)(g_MapData + 828);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_wall_scan_enter", wall_column, battle_width, battle_height, g_UnitBattleWallScanTileRow);
  if ( wall_column < 0 || wall_column >= battle_width || battle_width <= 2 || battle_height <= 2 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_ai_wall_scan_skip", wall_column, battle_width, battle_height, g_UnitBattleWallScanTileRow);
    return;
  }
  g_UnitBattleWallScanTileRow = 1;
  scanRow = 1;
  rowByteOffset = 20;
  while ( scanRow < battle_height - 1 )
  {
    if ( *(char *)(g_MapData + rowByteOffset + wall_column + 3135) > 0 )
      g_UnitBattleWallScanTileRow = scanRow;
    rowByteOffset += 20;
    ++scanRow;
  }
  g_BattleWallScanColumn = wall_column;
  g_BattleWallScanTileX = g_BattleWallScanColumn + 1;
  scanCol = 1;
  scanRowByteOffset = 20 * g_UnitBattleWallScanTileRow;
  while ( scanCol < battle_width - 1 )
  {
    tileAddr = g_MapData + scanRowByteOffset + scanCol;
    if ( *(char *)(tileAddr + 3134) >= 0 && *(_BYTE *)(tileAddr + 3134) < *(_BYTE *)(g_BattleWallScanColumn + g_MapData + scanRowByteOffset + 3134) )
    {
      g_BattleWallScanTileX = g_BattleWallScanColumn;
      g_BattleWallScanColumn = scanCol++;
    }
    else
    {
      ++scanCol;
    }
  }
  Diagnostics_TraceWorldMapActionEvent("battle_ai_wall_scan_exit", g_UnitBattleWallScanTileRow, g_BattleWallScanColumn, g_BattleWallScanTileX, 0);
  return;
}
// 43CBE0: control flows out of bounds to 43C853
// 532048: using guessed type int g_MapData;
// 5437B0: using guessed type int dword_5437B0;
// 5437B4: using guessed type int dword_5437B4;
// 5437B8: using guessed type int dword_5437B8;

//----- (0043CC50) --------------------------------------------------------
signed int  UnitBattle_SelectAiPlanMode(int side, signed int scanDirection)
{
  int sideCopy; // edx

  sideCopy = side;
  if ( g_UnitBattleAiTurnCounter <= 3 && UnitBattle_ScanAiPlanRangeLine(side, scanDirection) )
    return BATTLE_AI_PLAN_RANGED_ENGAGE;
  if ( *(int *)(g_MapData + 828) <= 0 )
    return BATTLE_AI_PLAN_DISENGAGE;
  if ( g_UnitBattleAiTurnCounter == 1 && sideCopy == *(_DWORD *)(g_MapData + 840) && g_UnitBattleAiCurrentPlanMode != 6 )
    return BATTLE_AI_PLAN_INITIAL_SWEEP;
  if ( sideCopy == *(_DWORD *)(g_MapData + 836) && g_UnitBattleAiTurnCounter < 3 )
    return BATTLE_AI_PLAN_HOLD;
  if ( sideCopy == *(_DWORD *)(g_MapData + 836) && g_UnitBattleAiTurnCounter >= 3 )
    return BATTLE_AI_PLAN_DISENGAGE;
  return BATTLE_AI_PLAN_ADVANCE;
}
// 43CC79: variable 'v2' is possibly undefined
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532078: using guessed type int dword_532078;
