/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004382E0) --------------------------------------------------------
signed int  UnitBattle_ScoreAiActionGridForUnit(int unitIndex, int side, int a3, signed int advanceDir)
{
  int v5; // ecx
  int scoreGridUnitBase; // edi
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edi
  int v12; // ecx
  int advanceOffset6; // esi
  int v14; // ecx
  int i; // ecx
  int scanRecordPtr; // eax
  int *scanTrackPath; // eax
  int pathNode; // ecx
  int v19; // ecx
  int v20; // edi
  int scoreRowByteOffset; // ebx
  int occupantCellPtr; // eax
  __int16 v23; // dx
  int *v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // eax
  int v29; // ecx
  DWORD v30; // ebp
  int unitRecordPtr; // esi
  int v32; // ecx
  int v33; // edx
  int moveScoreDelta; // edx
  int v35; // ebp
  int v36; // ebx
  int v37; // ecx
  int v38; // esi
  int v39; // edi
  int v40; // ecx
  int v41; // edx
  int v42; // ecx
  __int64 v43; // rtt
  int v44; // edx
  int v45; // eax
  int v46; // esi
  int v47; // eax
  int v48; // edi
  int v49; // edx
  int v50; // esi
  int v51; // edx
  int v52; // ecx
  int v53; // esi
  int v54; // eax
  int v55; // edi
  int v56; // edx
  int v57; // esi
  int v58; // edx
  int v59; // ecx
  int v60; // esi
  int v61; // eax
  int v62; // edi
  int v63; // esi
  BOOL v64; // eax
  int v65; // ecx
  int v66; // esi
  int v67; // edx
  int v68; // ecx
  int v69; // edx
  int v70; // eax
  int v71; // esi
  int v72; // ecx
  int v73; // edx
  DWORD v74; // ebp
  int v75; // edi
  int v76; // ebx
  int v77; // esi
  int v78; // edx
  int v79; // ecx
  int v80; // ebp
  int v81; // edx
  int v82; // eax
  int trackRowArg; // ecx
  int v84; // eax
  int trackColArg; // ebx
  int *trackPath; // eax
  int *trackPathPtr; // ecx
  int v88; // eax
  int v89; // eax
  int v90; // edx
  int *v91; // ecx
  int v92; // edx
  int v93; // eax
  int v94; // edx
  int v95; // eax
  int *v96; // eax
  int *v97; // ecx
  int v98; // edx
  int v99; // eax
  int v100; // edx
  int *v101; // ecx
  int v102; // edx
  int v103; // eax
  int v104; // edx
  int v105; // ecx
  int *v106; // eax
  int *v107; // ecx
  int v108; // edx
  int *v109; // ecx
  int v110; // edx
  int v111; // eax
  int v112; // edx
  int v113; // ecx
  int *v114; // eax
  int *v115; // ecx
  int v116; // edx
  int *v117; // ecx
  int v118; // edx
  int v119; // eax
  int v120; // edx
  int v121; // edx
  int *v122; // eax
  int *v123; // ecx
  int v124; // eax
  int v125; // edx
  int *v126; // ecx
  int v127; // edx
  int v128; // ebx
  int v129; // edx
  int v130; // ecx
  int *v131; // eax
  int *v132; // ecx
  int v133; // ebx
  int v134; // ebx
  int v135; // edx
  int *v136; // ecx
  int v137; // edx
  int v138; // ebx
  int v139; // edx
  int v140; // ebx
  int v141; // eax
  __int16 v142; // dx
  int tileScore; // ebp
  int *v144; // eax
  int v145; // ecx
  int v146; // edx
  int v147; // eax
  int v148; // eax
  int v149; // ecx
  int actingUnitPtr; // esi
  int v151; // edx
  int v152; // ecx
  int v153; // edx
  int v154; // ecx
  int v155; // eax
  int v156; // ebx
  int *v157; // eax
  int *v158; // ecx
  int v159; // eax
  int v160; // eax
  int v161; // edx
  int *v162; // ecx
  int v163; // edx
  int v164; // eax
  int v165; // ebx
  int v166; // edx
  int result; // [esp+0h] [ebp-E0h]
  __int16 savedOccupant; // [esp+Ch] [ebp-D4h]
  __int16 v169; // [esp+10h] [ebp-D0h]
  int enemyRow; // [esp+14h] [ebp-CCh]
  DWORD targetRow; // [esp+18h] [ebp-C8h]
  int enemyCol; // [esp+1Ch] [ebp-C4h]
  int v173; // [esp+20h] [ebp-C0h]
  int v174; // [esp+20h] [ebp-C0h]
  int unitScoreBase; // [esp+28h] [ebp-B8h]
  __int16 v176; // [esp+2Ch] [ebp-B4h]
  int enemyScanOffset; // [esp+30h] [ebp-B0h]
  DWORD enemyIndex; // [esp+34h] [ebp-ACh]
  int unitRecordOffset; // [esp+3Ch] [ebp-A4h]
  int pathCost; // [esp+40h] [ebp-A0h]
  int pathEntry; // [esp+40h] [ebp-A0h]
  __int16 savedUnitRow; // [esp+50h] [ebp-90h]
  __int16 savedUnitCol; // [esp+54h] [ebp-8Ch]
  int targetCol; // [esp+64h] [ebp-7Ch]
  int actingUnitOffset; // [esp+6Ch] [ebp-74h]
  __int16 v187; // [esp+70h] [ebp-70h]
  __int16 v188; // [esp+74h] [ebp-6Ch]
  __int16 v189; // [esp+78h] [ebp-68h]
  __int16 v190; // [esp+7Ch] [ebp-64h]
  __int16 v191; // [esp+80h] [ebp-60h]
  __int16 v192; // [esp+84h] [ebp-5Ch]
  __int16 v193; // [esp+88h] [ebp-58h]
  int scoreGridBase; // [esp+8Ch] [ebp-54h]
  __int16 v195; // [esp+90h] [ebp-50h]
  __int16 v196; // [esp+94h] [ebp-4Ch]
  __int16 v197; // [esp+98h] [ebp-48h]
  __int16 savedTileOccupant; // [esp+A0h] [ebp-40h]
  int v199; // [esp+A4h] [ebp-3Ch]
  int v200; // [esp+A4h] [ebp-3Ch]
  int v201; // [esp+A8h] [ebp-38h]
  int v202; // [esp+A8h] [ebp-38h]
  int v203; // [esp+ACh] [ebp-34h]
  int v204; // [esp+ACh] [ebp-34h]
  int enemyRecordOffset; // [esp+B4h] [ebp-2Ch]
  int v206; // [esp+B8h] [ebp-28h]
  int v207; // [esp+B8h] [ebp-28h]
  int trackTargetCol; // [esp+BCh] [ebp-24h]
  int v209; // [esp+C0h] [ebp-20h]
  int v210; // [esp+C0h] [ebp-20h]
  int enemyScanIndex; // [esp+C4h] [ebp-1Ch]

  result = 1;
  switch ( g_UnitBattleAiCurrentPlanMode )
  {
    case BATTLE_AI_PLAN_HOLD:
    case BATTLE_AI_PLAN_DISENGAGE:
      goto LABEL_29;
    case BATTLE_AI_PLAN_ADVANCE:
      unitScoreBase = 801 * unitIndex;
      enemyScanIndex = 0;
      enemyScanOffset = 0;
      actingUnitOffset = 31 * unitIndex;
      do
      {
        if ( *(__int16 *)(uintptr_t)(enemyScanOffset + g_MapData + 852) != -1 && *(unsigned __int8 *)(uintptr_t)(enemyScanOffset + g_MapData + 854) != side )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          result = 0;
          targetRow = *(unsigned __int16 *)(uintptr_t)(g_MapData + enemyScanOffset + 856);
          targetCol = *(unsigned __int16 *)(uintptr_t)(g_MapData + enemyScanOffset + 858);
          v140 = 160 * targetRow + unitScoreBase * 4;
          v141 = 2 * targetCol + g_MapData + 40 * targetRow;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * targetCol] + v140) -= g_UnitBattleAiRoleScoreWeights[(unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)(uintptr_t)(g_MapData + enemyScanOffset + 852)]];
          v142 = *(_WORD *)(uintptr_t)(v141 + 1534);
          *(_WORD *)(uintptr_t)(v141 + 1534) = -1;
          savedTileOccupant = v142;
          tileScore = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * targetCol] + v140) - 800;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * targetCol] + v140) = tileScore;
          v144 = UnitBattle_EstimateDamageScoreAgainstUnit(unitIndex, enemyScanIndex);
          v146 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) - 15 * (_DWORD)(intptr_t)v144;
          v147 = enemyScanOffset + g_MapData;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) = v146;
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v145] + v140) = v146 - 2 * *(unsigned __int8 *)(uintptr_t)(v147 + 860);
          v148 = UnitBattle_ScoreTileAgainstRangedUnitsOfSide(enemyScanIndex, side, tileScore);
          *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v149] + v140) -= 2 * v148;
          trackTargetCol = v149;
          Debug_Log(v149, v140, targetRow, (int)(intptr_t)aOddzial_w_zasi);
          actingUnitPtr = actingUnitOffset + g_MapData + 852;
          if ( UnitBattle_IsTileWithinRange(unitIndex, v151, v152)
            && (*(_BYTE *)(uintptr_t)(actingUnitOffset + g_MapData + 864) & 3)
             + 1
             - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(actingUnitOffset + g_MapData + 864)) >> 5) > 0 )
          {
            v153 = 0;
LABEL_278:
            LOBYTE(v153) = *(_BYTE *)(uintptr_t)(actingUnitPtr + 8);
            goto LABEL_279;
          }
          v154 = trackTargetCol;
          if ( *(char *)(uintptr_t)(trackTargetCol + g_MapData + 20 * targetRow + 3134) <= 0 )
          {
            v156 = trackTargetCol;
          }
          else
          {
            v154 = g_MapData + 40 * targetRow;
            if ( *(__int16 *)(uintptr_t)(v154 + 2 * trackTargetCol + 1534) == -1
              || (v155 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v155 + 852)] & 1) == 0)
              && (*(_BYTE *)(uintptr_t)(v155 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v155 + 864)) >> 5) <= 0 )
            {
              v157 = UnitBattle_MoveTrackNearWall(unitIndex, targetRow, trackTargetCol, targetRow);
              goto LABEL_289;
            }
            v156 = trackTargetCol;
          }
          v157 = (int *)UnitBattle_MoveTrackNear(unitIndex, v154, v156, targetRow);
LABEL_289:
          v158 = v157;
          if ( !v157 )
          {
            v159 = g_MapData + 31 * unitIndex;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v159 + 852)] )
            {
              if ( (*(_BYTE *)(uintptr_t)(v159 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v159 + 864)) >> 5) > 0 )
                v158 = UnitBattle_MoveTrackForce(unitIndex, trackTargetCol, targetRow);
            }
          }
          if ( !v158 )
            goto LABEL_294;
          if ( !*v158 )
          {
            j__nfree_();
            goto LABEL_278;
          }
          v160 = 31 * unitIndex + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v160 + 852)]
            && (*(_BYTE *)(uintptr_t)(v160 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v160 + 864)) >> 5) > 0 )
          {
            v176 = *(_WORD *)(uintptr_t)(actingUnitPtr + 4);
            HIWORD(v174) = 0;
            v169 = *(_WORD *)(uintptr_t)(actingUnitPtr + 6);
            if ( *v158 )
            {
              while ( !UnitBattle_IsTileWithinRange(unitIndex, targetRow, trackTargetCol) )
              {
                v165 = *v162 - 1;
                *v162 = v165;
                v174 = v162[v165 + 1];
                if ( HIWORD(v174) > (int)*(unsigned __int8 *)(uintptr_t)(actingUnitPtr + 8) )
                  goto LABEL_317;
                *(_WORD *)(uintptr_t)(actingUnitPtr + 4) = (unsigned __int8)v174;
                *(_WORD *)(uintptr_t)(actingUnitPtr + 6) = BYTE1(v174);
                if ( !*v162 )
                  goto LABEL_314;
              }
              *(_WORD *)(uintptr_t)(actingUnitPtr + 4) = v176;
              *(_WORD *)(uintptr_t)(actingUnitPtr + 6) = v169;
              j__nfree_();
              LOWORD(v163) = HIWORD(v174);
              v164 = *(unsigned __int8 *)(uintptr_t)(actingUnitPtr + 8);
              if ( v164 > v163 )
              {
                v153 = v164 - v163;
                goto LABEL_279;
              }
LABEL_311:
              v153 = 0;
              goto LABEL_280;
            }
LABEL_314:
            if ( !UnitBattle_IsTileWithinRange(unitIndex, targetRow, trackTargetCol) )
            {
LABEL_317:
              *(_WORD *)(uintptr_t)(actingUnitPtr + 4) = v176;
              *(_WORD *)(uintptr_t)(actingUnitPtr + 6) = v169;
              j__nfree_();
              goto LABEL_280;
            }
            *(_WORD *)(uintptr_t)(actingUnitPtr + 4) = v176;
            *(_WORD *)(uintptr_t)(actingUnitPtr + 6) = v169;
            if ( *(unsigned __int8 *)(uintptr_t)(actingUnitPtr + 8) > (int)HIWORD(v174) )
            {
              j__nfree_();
              v153 = *(unsigned __int8 *)(uintptr_t)(actingUnitPtr + 8) - v166;
LABEL_279:
              if ( v153 > -1 )
              {
LABEL_280:
                g_UnitBattleTileScoreGrid[40 * targetRow + 2 * targetCol + unitScoreBase] -= 5 * (v153 / 5);
LABEL_281:
                *(_WORD *)(uintptr_t)(40 * targetRow + g_MapData + 2 * targetCol + 1534) = savedTileOccupant;
                goto LABEL_282;
              }
LABEL_294:
              g_UnitBattleTileScoreGrid[40 * targetRow + 2 * targetCol + unitScoreBase] += 700;
              goto LABEL_281;
            }
          }
          else if ( *v158 )
          {
            v173 = v158[1];
            j__nfree_();
            LOBYTE(v161) = *(_BYTE *)(uintptr_t)(actingUnitPtr + 8);
            if ( v161 <= HIWORD(v173) )
            {
              v153 = 0;
              goto LABEL_280;
            }
            v153 = v161 - HIWORD(v173);
            goto LABEL_279;
          }
          j__nfree_();
          goto LABEL_311;
        }
LABEL_282:
        enemyScanOffset += 31;
        ++enemyScanIndex;
      }
      while ( enemyScanIndex < 22 );
      return result;
    case BATTLE_AI_PLAN_RANGED_ENGAGE:
    case BATTLE_AI_PLAN_INITIAL_SWEEP:
      if ( side == *(_DWORD *)(uintptr_t)(g_MapData + 836) )
      {
        if ( g_AttackerStartsOnLeft == 1 )
          advanceDir = 1;
        else
          advanceDir = -1;
      }
      if ( side == *(_DWORD *)(uintptr_t)(g_MapData + 840) )
      {
        if ( g_DefenderStartsOnLeft == 1 )
          advanceDir = 1;
        else
          advanceDir = -1;
      }
      scoreGridUnitBase = 801 * unitIndex;
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 852),
             *(unsigned __int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 856) + 3 * advanceDir,
             *(unsigned __int16 *)(uintptr_t)(31 * unitIndex + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[120 * advanceDir
                   + 40 * *(unsigned __int16 *)(uintptr_t)(g_MapData + v5 + 856)
                   + 2 * *(unsigned __int16 *)(uintptr_t)(g_MapData + v5 + 858)
                   + scoreGridUnitBase] -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(uintptr_t)(v5 + g_MapData + 852),
             4 * advanceDir + *(unsigned __int16 *)(uintptr_t)(v5 + g_MapData + 856),
             *(unsigned __int16 *)(uintptr_t)(v5 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[160 * advanceDir
                   + 40 * *(unsigned __int16 *)(uintptr_t)(g_MapData + v8 + 856)
                   + 2 * *(unsigned __int16 *)(uintptr_t)(g_MapData + v8 + 858)
                   + scoreGridUnitBase] -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(uintptr_t)(v8 + g_MapData + 852),
             2 * advanceDir + *(unsigned __int16 *)(uintptr_t)(v8 + g_MapData + 856),
             *(unsigned __int16 *)(uintptr_t)(v8 + g_MapData + 858)) )
      {
        v10 = g_MapData + v9;
        v11 = 160 * (*(unsigned __int16 *)(uintptr_t)(v10 + 856) + 2 * advanceDir) + scoreGridUnitBase * 4;
        *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * *(unsigned __int16 *)(uintptr_t)(v10 + 858)] + v11) -= 500;
        return 0;
      }
      if ( UnitBattle_GetTileMoveCostOrZero(
             *(__int16 *)(uintptr_t)(v9 + g_MapData + 852),
             5 * advanceDir + *(unsigned __int16 *)(uintptr_t)(v9 + g_MapData + 856),
             *(unsigned __int16 *)(uintptr_t)(v9 + g_MapData + 858)) )
      {
        g_UnitBattleTileScoreGrid[200 * advanceDir
                   + 40 * *(unsigned __int16 *)(uintptr_t)(g_MapData + v12 + 856)
                   + 2 * *(unsigned __int16 *)(uintptr_t)(g_MapData + v12 + 858)
                   + scoreGridUnitBase] -= 500;
        return 0;
      }
      a3 = *(unsigned __int16 *)(uintptr_t)(v12 + g_MapData + 856);
      advanceOffset6 = 6 * advanceDir;
      if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)(uintptr_t)(v12 + g_MapData + 852), advanceOffset6 + a3, *(unsigned __int16 *)(uintptr_t)(v12 + g_MapData + 858)) )
      {
        v19 = g_MapData + v14;
        v20 = 160 * (advanceOffset6 + *(unsigned __int16 *)(uintptr_t)(v19 + 856)) + scoreGridUnitBase * 4;
        *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * *(unsigned __int16 *)(uintptr_t)(v19 + 858)] + v20) -= 500;
        return 0;
      }
      for ( i = 0; i < 682; i += 31 )
      {
        scanRecordPtr = i + g_MapData;
        if ( *(__int16 *)(uintptr_t)(i + g_MapData + 852) != -1 && *(unsigned __int8 *)(uintptr_t)(scanRecordPtr + 854) != side )
        {
          scanTrackPath = (int *)UnitBattle_MoveTrackNear(unitIndex, i, *(unsigned __int16 *)(uintptr_t)(scanRecordPtr + 858), a3);
          if ( scanTrackPath && *scanTrackPath > 3 )
          {
            pathNode = scanTrackPath[*scanTrackPath - 3];
            g_UnitBattleTileScoreGrid[801 * unitIndex + 40 * (unsigned __int8)pathNode + 2 * BYTE1(pathNode)] -= 500;
            j__nfree_();
            return 0;
          }
          if ( scanTrackPath )
            j__nfree_();
        }
      }
LABEL_29:
      scoreGridBase = 801 * unitIndex;
      enemyIndex = 0;
      enemyRecordOffset = 0;
      unitRecordOffset = 31 * unitIndex;
      break;
    default:
      return result;
  }
  while ( 1 )
  {
    if ( *(__int16 *)(uintptr_t)(enemyRecordOffset + g_MapData + 852) == -1 || *(unsigned __int8 *)(uintptr_t)(enemyRecordOffset + g_MapData + 854) == side )
      goto LABEL_39;
    UnitBattle_UpdateIdleAnimatedUnits();
    enemyRow = *(unsigned __int16 *)(uintptr_t)(g_MapData + enemyRecordOffset + 856);
    enemyCol = *(unsigned __int16 *)(uintptr_t)(g_MapData + enemyRecordOffset + 858);
    result = 0;
    scoreRowByteOffset = 160 * enemyRow + scoreGridBase * 4;
    occupantCellPtr = 40 * enemyRow + g_MapData + 2 * enemyCol;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * enemyCol] + scoreRowByteOffset) -= g_UnitBattleAiRoleScoreWeights[(unsigned __int8)g_UnitTypeRole[88
                                                                                               * *(__int16 *)(uintptr_t)(g_MapData + enemyRecordOffset + 852)]];
    v23 = *(_WORD *)(uintptr_t)(occupantCellPtr + 1534);
    *(_WORD *)(uintptr_t)(occupantCellPtr + 1534) = -1;
    savedOccupant = v23;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * enemyCol] + scoreRowByteOffset) -= 800;
    v24 = UnitBattle_EstimateDamageScoreAgainstUnit(unitIndex, enemyIndex);
    v26 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + scoreRowByteOffset) - 15 * (_DWORD)(intptr_t)v24;
    v27 = enemyRecordOffset + g_MapData;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + scoreRowByteOffset) = v26;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v25] + scoreRowByteOffset) = v26 - 2 * *(unsigned __int8 *)(uintptr_t)(v27 + 860);
    v28 = UnitBattle_ScoreTileAgainstRangedUnitsOfSide(enemyIndex, side, a3);
    v30 = *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v29] + scoreRowByteOffset) - 2 * v28;
    *(int *)((char *)&g_UnitBattleTileScoreGrid[2 * v29] + scoreRowByteOffset) = v30;
    Debug_Log(v29, scoreRowByteOffset, v30, (int)(intptr_t)aOddzial_w_zasi);
    unitRecordPtr = unitRecordOffset + g_MapData + 852;
    a3 = v32;
    if ( UnitBattle_IsTileWithinRange(unitIndex, v33, v32)
      && (*(_BYTE *)(uintptr_t)(unitRecordOffset + g_MapData + 864) & 3)
       + 1
       - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(unitRecordOffset + g_MapData + 864)) >> 5) > 0 )
    {
      moveScoreDelta = 0;
LABEL_35:
      LOBYTE(moveScoreDelta) = *(_BYTE *)(uintptr_t)(unitRecordPtr + 8);
      goto LABEL_36;
    }
    trackRowArg = enemyRow;
    if ( *(char *)(uintptr_t)(g_MapData + 20 * enemyRow + a3 + 3134) <= 0 )
    {
      trackColArg = a3;
    }
    else
    {
      trackRowArg = g_MapData + 40 * enemyRow;
      if ( *(__int16 *)(uintptr_t)(trackRowArg + 2 * a3 + 1534) == -1
        || (v84 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v84 + 852)] & 1) == 0)
        && (*(_BYTE *)(uintptr_t)(v84 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v84 + 864)) >> 5) <= 0 )
      {
        trackPath = UnitBattle_MoveTrackNearWall(unitIndex, enemyRow, a3, a3);
        goto LABEL_83;
      }
      trackColArg = a3;
    }
    trackPath = (int *)UnitBattle_MoveTrackNear(unitIndex, trackRowArg, trackColArg, a3);
LABEL_83:
    trackPathPtr = trackPath;
    if ( !trackPath )
    {
      v88 = 31 * unitIndex + g_MapData;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v88 + 852)] )
      {
        if ( (*(_BYTE *)(uintptr_t)(v88 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v88 + 864)) >> 5) > 0 )
          trackPathPtr = UnitBattle_MoveTrackForce(unitIndex, a3, a3);
      }
    }
    if ( !trackPathPtr )
    {
LABEL_88:
      g_UnitBattleTileScoreGrid[40 * enemyRow + 2 * enemyCol + scoreGridBase] += 700;
      goto LABEL_38;
    }
    if ( !*trackPathPtr )
    {
      j__nfree_();
      goto LABEL_35;
    }
    v89 = g_MapData + 31 * unitIndex;
    if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v89 + 852)]
      && (*(_BYTE *)(uintptr_t)(v89 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v89 + 864)) >> 5) > 0 )
    {
      savedUnitRow = *(_WORD *)(uintptr_t)(unitRecordPtr + 4);
      HIWORD(pathEntry) = 0;
      savedUnitCol = *(_WORD *)(uintptr_t)(unitRecordPtr + 6);
      if ( *trackPathPtr )
      {
        while ( !UnitBattle_IsTileWithinRange(unitIndex, enemyRow, a3) )
        {
          v93 = *v91 - 1;
          *v91 = v93;
          pathEntry = v91[v93 + 1];
          if ( HIWORD(pathEntry) > (int)*(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8) )
            goto LABEL_111;
          *(_WORD *)(uintptr_t)(unitRecordPtr + 4) = (unsigned __int8)pathEntry;
          *(_WORD *)(uintptr_t)(unitRecordPtr + 6) = BYTE1(pathEntry);
          if ( !*v91 )
            goto LABEL_108;
        }
        *(_WORD *)(uintptr_t)(unitRecordPtr + 4) = savedUnitRow;
        *(_WORD *)(uintptr_t)(unitRecordPtr + 6) = savedUnitCol;
        j__nfree_();
        LOBYTE(v92) = *(_BYTE *)(uintptr_t)(unitRecordPtr + 8);
        if ( v92 <= HIWORD(pathEntry) )
          goto LABEL_105;
        moveScoreDelta = v92 - HIWORD(pathEntry);
      }
      else
      {
LABEL_108:
        if ( !UnitBattle_IsTileWithinRange(unitIndex, enemyRow, a3) )
        {
LABEL_111:
          *(_WORD *)(uintptr_t)(unitRecordPtr + 4) = savedUnitRow;
          *(_WORD *)(uintptr_t)(unitRecordPtr + 6) = savedUnitCol;
          j__nfree_();
          goto LABEL_37;
        }
        *(_WORD *)(uintptr_t)(unitRecordPtr + 4) = savedUnitRow;
        *(_WORD *)(uintptr_t)(unitRecordPtr + 6) = savedUnitCol;
        if ( *(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8) <= (int)HIWORD(pathEntry) )
        {
LABEL_104:
          j__nfree_();
LABEL_105:
          moveScoreDelta = 0;
          goto LABEL_37;
        }
        j__nfree_();
        moveScoreDelta = *(unsigned __int8 *)(uintptr_t)(unitRecordPtr + 8) - v94;
      }
    }
    else
    {
      if ( !*trackPathPtr )
        goto LABEL_104;
      pathCost = trackPathPtr[1];
      j__nfree_();
      LOBYTE(v90) = *(_BYTE *)(uintptr_t)(unitRecordPtr + 8);
      if ( v90 <= HIWORD(pathCost) )
      {
        moveScoreDelta = 0;
        goto LABEL_37;
      }
      moveScoreDelta = v90 - HIWORD(pathCost);
    }
LABEL_36:
    if ( moveScoreDelta <= -1 )
      goto LABEL_88;
LABEL_37:
    g_UnitBattleTileScoreGrid[40 * enemyRow + 2 * enemyCol + scoreGridBase] -= 5 * (moveScoreDelta / 5);
LABEL_38:
    *(_WORD *)(uintptr_t)(g_MapData + 40 * enemyRow + 2 * enemyCol + 1534) = savedOccupant;
LABEL_39:
    enemyRecordOffset += 31;
    if ( (int)++enemyIndex >= 22 )
    {
      v35 = g_UnitBattleWallScanTileRow;
      if ( g_UnitBattleWallScanTileRow <= 0 || *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * unitIndex + 856) == g_UnitBattleWallScanTileRow )
        return result;
      v36 = g_BattleWallScanColumn;
      if ( *(char *)(uintptr_t)(g_BattleWallScanColumn + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
        goto LABEL_49;
      Debug_Log(31 * unitIndex, g_BattleWallScanColumn, g_UnitBattleWallScanTileRow, (int)(intptr_t)aOddzial_w_zasi);
      v38 = v37 + g_MapData + 852;
      v39 = v36;
      if ( UnitBattle_IsTileWithinRange(unitIndex, v35, v36)
        && (*(_BYTE *)(uintptr_t)(v40 + g_MapData + 864) & 3)
         + 1
         - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v40 + g_MapData + 864)) >> 5) > 0 )
      {
        v41 = 0;
        goto LABEL_46;
      }
      if ( *(char *)(uintptr_t)(v36 + g_MapData + 20 * v35 + 3134) <= 0
        || *(__int16 *)(uintptr_t)(g_MapData + 40 * v35 + 2 * v36 + 1534) != -1
        && ((v95 = g_MapData + 31 * unitIndex, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v95 + 852)] & 1) != 0)
         || (*(_BYTE *)(uintptr_t)(v95 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v95 + 864)) >> 5) > 0) )
      {
        v96 = (int *)UnitBattle_MoveTrackNear(unitIndex, g_MapData, v36, v35);
      }
      else
      {
        v96 = UnitBattle_MoveTrackNearWall(unitIndex, v35, v36, v35);
      }
      v97 = v96;
      if ( !v96 )
      {
        LOBYTE(v36) = g_MapData;
        v98 = g_MapData + 31 * unitIndex;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v98 + 852)] )
        {
          v36 = *(_BYTE *)(uintptr_t)(v98 + 864) & 3;
          if ( v36 + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v98 + 864)) >> 5) > 0 )
          {
            LOBYTE(v36) = v39;
            v97 = UnitBattle_MoveTrackForce(unitIndex, v39, v35);
          }
        }
      }
      if ( !v97 )
      {
LABEL_49:
        g_BattleWallScanTileX = g_BattleWallScanColumn + 1;
        if ( *(char *)(uintptr_t)(g_BattleWallScanColumn + 1 + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
          goto LABEL_56;
        v48 = g_UnitBattleWallScanTileRow;
        Debug_Log(g_MapData, v36, v35, (int)(intptr_t)aOddzial_w_zasi);
        v35 = v49;
        v50 = 31 * unitIndex + g_MapData + 852;
        if ( UnitBattle_IsTileWithinRange(unitIndex, v48, v49) )
        {
          LOBYTE(v36) = 31 * unitIndex;
          if ( (*(_BYTE *)(uintptr_t)(31 * unitIndex + g_MapData + 864) & 3)
             + 1
             - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(31 * unitIndex + g_MapData + 864)) >> 5) > 0 )
          {
            v51 = 0;
            goto LABEL_53;
          }
        }
        v105 = g_MapData;
        if ( *(char *)(uintptr_t)(g_MapData + 20 * v48 + v35 + 3134) <= 0
          || *(__int16 *)(uintptr_t)(g_MapData + 40 * v48 + 2 * v35 + 1534) != -1
          && ((v105 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v105 + 852)] & 1) != 0)
           || (*(_BYTE *)(uintptr_t)(v105 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v105 + 864)) >> 5) > 0) )
        {
          LOBYTE(v36) = v35;
          v106 = (int *)UnitBattle_MoveTrackNear(unitIndex, v105, v35, v35);
        }
        else
        {
          LOBYTE(v36) = v35;
          v106 = UnitBattle_MoveTrackNearWall(unitIndex, v48, v35, v35);
        }
        v107 = v106;
        if ( !v106 )
        {
          v36 = 31 * unitIndex + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v36 + 852)] )
          {
            if ( (*(_BYTE *)(uintptr_t)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v36 + 864)) >> 5) > 0 )
            {
              LOBYTE(v36) = v35;
              v107 = UnitBattle_MoveTrackForce(unitIndex, v35, v35);
            }
          }
        }
        if ( !v107 )
        {
LABEL_56:
          g_BattleWallScanTileX = g_BattleWallScanColumn - 1;
          if ( *(char *)(uintptr_t)(g_BattleWallScanColumn - 1 + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
            goto LABEL_63;
          v55 = g_UnitBattleWallScanTileRow;
          Debug_Log(g_MapData, v36, v35, (int)(intptr_t)aOddzial_w_zasi);
          v35 = v56;
          v57 = 31 * unitIndex + g_MapData + 852;
          if ( UnitBattle_IsTileWithinRange(unitIndex, v55, v56) )
          {
            LOBYTE(v36) = 31 * unitIndex;
            if ( (*(_BYTE *)(uintptr_t)(31 * unitIndex + g_MapData + 864) & 3)
               + 1
               - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(31 * unitIndex + g_MapData + 864)) >> 5) > 0 )
            {
              v58 = 0;
              goto LABEL_60;
            }
          }
          v113 = g_MapData;
          if ( *(char *)(uintptr_t)(g_MapData + 20 * v55 + v35 + 3134) <= 0
            || *(__int16 *)(uintptr_t)(g_MapData + 40 * v55 + 2 * v35 + 1534) != -1
            && ((v113 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v113 + 852)] & 1) != 0)
             || (*(_BYTE *)(uintptr_t)(v113 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v113 + 864)) >> 5) > 0) )
          {
            LOBYTE(v36) = v35;
            v114 = (int *)UnitBattle_MoveTrackNear(unitIndex, v113, v35, v35);
          }
          else
          {
            LOBYTE(v36) = v35;
            v114 = UnitBattle_MoveTrackNearWall(unitIndex, v55, v35, v35);
          }
          v115 = v114;
          if ( !v114 )
          {
            v36 = 31 * unitIndex + g_MapData;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v36 + 852)] )
            {
              if ( (*(_BYTE *)(uintptr_t)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v36 + 864)) >> 5) > 0 )
              {
                LOBYTE(v36) = v35;
                v115 = UnitBattle_MoveTrackForce(unitIndex, v35, v35);
              }
            }
          }
          if ( !v115 )
          {
LABEL_63:
            g_BattleWallScanTileX = g_BattleWallScanColumn + 2;
            if ( *(char *)(uintptr_t)(g_BattleWallScanColumn + 2 + g_MapData + 20 * g_UnitBattleWallScanTileRow + 3134) <= 0 )
              goto LABEL_70;
            v35 = g_UnitBattleWallScanTileRow;
            v62 = g_BattleWallScanColumn + 2;
            v36 = g_BattleWallScanColumn + 2;
            Debug_Log(unitIndex, g_BattleWallScanColumn + 2, g_UnitBattleWallScanTileRow, (int)(intptr_t)aOddzial_w_zasi);
            v63 = g_MapData + 852;
            v64 = UnitBattle_IsTileWithinRange(unitIndex, v35, v36);
            v66 = v65 + v63;
            if ( v64
              && (*(_BYTE *)(uintptr_t)(v65 + g_MapData + 864) & 3)
               + 1
               - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v65 + g_MapData + 864)) >> 5) > 0 )
            {
              v67 = 0;
              goto LABEL_67;
            }
            if ( *(char *)(uintptr_t)(v62 + g_MapData + 20 * v35 + 3134) <= 0
              || *(__int16 *)(uintptr_t)(g_MapData + 40 * v35 + 2 * v62 + 1534) != -1
              && ((v65 = unitIndex, v121 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v121 + 852)] & 1) != 0)
               || (*(_BYTE *)(uintptr_t)(v121 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v121 + 864)) >> 5) > 0) )
            {
              LOBYTE(v36) = v62;
              v122 = (int *)UnitBattle_MoveTrackNear(unitIndex, v65, v62, v35);
            }
            else
            {
              LOBYTE(v36) = v62;
              v122 = UnitBattle_MoveTrackNearWall(unitIndex, v35, v62, v35);
            }
            v123 = v122;
            if ( !v122 )
            {
              LOBYTE(v36) = g_MapData;
              v124 = g_MapData + 31 * unitIndex;
              if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v124 + 852)] )
              {
                if ( (*(_BYTE *)(uintptr_t)(v124 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v124 + 864)) >> 5) > 0 )
                {
                  LOBYTE(v36) = v62;
                  v123 = UnitBattle_MoveTrackForce(unitIndex, v62, v35);
                }
              }
            }
            if ( !v123 )
            {
LABEL_70:
              g_BattleWallScanTileX = g_BattleWallScanColumn - 2;
              v71 = g_BattleWallScanColumn - 2;
              v72 = g_BattleWallScanColumn - 2 + 20 * g_UnitBattleWallScanTileRow + g_MapData;
              if ( *(char *)(uintptr_t)(v72 + 3134) <= 0 )
                return result;
              Debug_Log(v72, v36, v35, (int)(intptr_t)aOddzial_w_zasi);
              v74 = v73;
              v75 = v71;
              v76 = v71;
              v77 = 31 * unitIndex + g_MapData + 852;
              if ( UnitBattle_IsTileWithinRange(unitIndex, v73, v76)
                && (*(_BYTE *)(uintptr_t)(31 * unitIndex + g_MapData + 864) & 3)
                 + 1
                 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(31 * unitIndex + g_MapData + 864)) >> 5) > 0 )
              {
                v78 = 0;
                goto LABEL_74;
              }
              v130 = g_MapData;
              if ( *(char *)(uintptr_t)(v75 + g_MapData + 20 * v74 + 3134) <= 0
                || *(__int16 *)(uintptr_t)(g_MapData + 40 * v74 + 2 * v75 + 1534) != -1
                && ((v130 = 31 * unitIndex + g_MapData, (g_UnitTypeFlags[22 * *(__int16 *)(uintptr_t)(v130 + 852)] & 1) != 0)
                 || (*(_BYTE *)(uintptr_t)(v130 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v130 + 864)) >> 5) > 0) )
              {
                v131 = (int *)UnitBattle_MoveTrackNear(unitIndex, v130, v75, v74);
              }
              else
              {
                v131 = UnitBattle_MoveTrackNearWall(unitIndex, v74, v75, v74);
              }
              v132 = v131;
              if ( !v131 )
              {
                v133 = 31 * unitIndex + g_MapData;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v133 + 852)] )
                {
                  if ( (*(_BYTE *)(uintptr_t)(v133 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v133 + 864)) >> 5) > 0 )
                    v132 = UnitBattle_MoveTrackForce(unitIndex, v75, v74);
                }
              }
              if ( !v132 )
                return result;
              if ( *v132 )
              {
                v134 = 31 * unitIndex + g_MapData;
                if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v134 + 852)]
                  && (*(_BYTE *)(uintptr_t)(v134 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v134 + 864)) >> 5) > 0 )
                {
                  v192 = *(_WORD *)(uintptr_t)(v77 + 4);
                  v195 = *(_WORD *)(uintptr_t)(v77 + 6);
                  HIWORD(v210) = 0;
                  if ( *v132 )
                  {
                    while ( !UnitBattle_IsTileWithinRange(unitIndex, v74, v75) )
                    {
                      v138 = *v136 - 1;
                      *v136 = v138;
                      v210 = v136[v138 + 1];
                      if ( HIWORD(v210) > (int)*(unsigned __int8 *)(uintptr_t)(v77 + 8) )
                        goto LABEL_271;
                      *(_WORD *)(uintptr_t)(v77 + 4) = (unsigned __int8)v210;
                      *(_WORD *)(uintptr_t)(v77 + 6) = BYTE1(v210);
                      if ( !*v136 )
                        goto LABEL_268;
                    }
                    *(_WORD *)(uintptr_t)(v77 + 4) = v192;
                    *(_WORD *)(uintptr_t)(v77 + 6) = v195;
                    j__nfree_();
                    LOBYTE(v137) = *(_BYTE *)(uintptr_t)(v77 + 8);
                    if ( v137 > HIWORD(v210) )
                    {
                      v78 = v137 - HIWORD(v210);
                      goto LABEL_75;
                    }
LABEL_265:
                    v78 = 0;
LABEL_76:
                    v79 = 8 * g_BattleWallScanTileX + 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow;
                    v80 = *(int *)((char *)g_UnitBattleTileScoreGrid + v79) - 640 - 5 * (v78 / 5);
                    v81 = g_BattleWallScanTileX;
                    v82 = g_MapData + 20 * g_UnitBattleWallScanTileRow;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) -= 640;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) = v80;
                    *(int *)((char *)g_UnitBattleTileScoreGrid + v79) = *(char *)(uintptr_t)(v81 + v82 + 3134) + v80;
                    return result;
                  }
LABEL_268:
                  if ( !UnitBattle_IsTileWithinRange(unitIndex, v74, v75) )
                  {
LABEL_271:
                    *(_WORD *)(uintptr_t)(v77 + 4) = v192;
                    *(_WORD *)(uintptr_t)(v77 + 6) = v195;
                    j__nfree_();
                    goto LABEL_76;
                  }
                  *(_WORD *)(uintptr_t)(v77 + 4) = v192;
                  *(_WORD *)(uintptr_t)(v77 + 6) = v195;
                  if ( *(unsigned __int8 *)(uintptr_t)(v77 + 8) > (int)HIWORD(v210) )
                  {
                    j__nfree_();
                    LOBYTE(v139) = *(_BYTE *)(uintptr_t)(v77 + 8);
                    v78 = v139 - HIWORD(v210);
                    goto LABEL_75;
                  }
                }
                else if ( *v132 )
                {
                  v209 = v132[1];
                  j__nfree_();
                  LOBYTE(v135) = *(_BYTE *)(uintptr_t)(v77 + 8);
                  if ( v135 > HIWORD(v209) )
                  {
                    v78 = v135 - HIWORD(v209);
                    goto LABEL_75;
                  }
                  v78 = 0;
                  goto LABEL_76;
                }
                j__nfree_();
                goto LABEL_265;
              }
              j__nfree_();
LABEL_74:
              LOBYTE(v78) = *(_BYTE *)(uintptr_t)(v77 + 8);
LABEL_75:
              if ( v78 > -1 )
                goto LABEL_76;
              return result;
            }
            if ( !*v123 )
            {
              j__nfree_();
LABEL_67:
              LOBYTE(v67) = *(_BYTE *)(uintptr_t)(v66 + 8);
              goto LABEL_68;
            }
            v36 = 31 * unitIndex + g_MapData;
            if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v36 + 852)]
              && (*(_BYTE *)(uintptr_t)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v36 + 864)) >> 5) > 0 )
            {
              v196 = *(_WORD *)(uintptr_t)(v66 + 4);
              v189 = *(_WORD *)(uintptr_t)(v66 + 6);
              HIWORD(v200) = 0;
              if ( *v123 )
              {
                while ( 1 )
                {
                  LOBYTE(v36) = v62;
                  if ( UnitBattle_IsTileWithinRange(unitIndex, v35, v62) )
                    break;
                  v128 = *v126 - 1;
                  *v126 = v128;
                  v200 = v126[v128 + 1];
                  if ( HIWORD(v200) > (int)*(unsigned __int8 *)(uintptr_t)(v66 + 8) )
                    goto LABEL_239;
                  *(_WORD *)(uintptr_t)(v66 + 4) = (unsigned __int8)v200;
                  *(_WORD *)(uintptr_t)(v66 + 6) = BYTE1(v200);
                  if ( !*v126 )
                    goto LABEL_236;
                }
                *(_WORD *)(uintptr_t)(v66 + 4) = v196;
                *(_WORD *)(uintptr_t)(v66 + 6) = v189;
                j__nfree_();
                LOBYTE(v127) = *(_BYTE *)(uintptr_t)(v66 + 8);
                if ( v127 > HIWORD(v200) )
                {
                  v67 = v127 - HIWORD(v200);
                  goto LABEL_68;
                }
LABEL_233:
                v67 = 0;
LABEL_69:
                v68 = 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanTileX;
                v35 = *(int *)((char *)g_UnitBattleTileScoreGrid + v68) - 640 - 5 * (v67 / 5);
                v69 = g_BattleWallScanTileX;
                v70 = g_MapData + 20 * g_UnitBattleWallScanTileRow;
                *(int *)((char *)g_UnitBattleTileScoreGrid + v68) -= 640;
                *(int *)((char *)g_UnitBattleTileScoreGrid + v68) = v35;
                v36 = *(char *)(uintptr_t)(v69 + v70 + 3134) + v35;
                *(int *)((char *)g_UnitBattleTileScoreGrid + v68) = v36;
                goto LABEL_70;
              }
LABEL_236:
              if ( !UnitBattle_IsTileWithinRange(unitIndex, v35, v62) )
              {
LABEL_239:
                *(_WORD *)(uintptr_t)(v66 + 4) = v196;
                *(_WORD *)(uintptr_t)(v66 + 6) = v189;
                j__nfree_();
                goto LABEL_69;
              }
              *(_WORD *)(uintptr_t)(v66 + 4) = v196;
              *(_WORD *)(uintptr_t)(v66 + 6) = v189;
              v36 = HIWORD(v200);
              if ( *(unsigned __int8 *)(uintptr_t)(v66 + 8) > (int)HIWORD(v200) )
              {
                j__nfree_();
                LOBYTE(v129) = *(_BYTE *)(uintptr_t)(v66 + 8);
                v67 = v129 - HIWORD(v200);
                goto LABEL_68;
              }
            }
            else if ( *v123 )
            {
              v199 = v123[1];
              j__nfree_();
              LOBYTE(v125) = *(_BYTE *)(uintptr_t)(v66 + 8);
              if ( v125 <= HIWORD(v199) )
              {
                v67 = 0;
              }
              else
              {
                v67 = v125 - HIWORD(v199);
LABEL_68:
                if ( v67 <= -1 )
                  goto LABEL_70;
              }
              goto LABEL_69;
            }
            j__nfree_();
            goto LABEL_233;
          }
          if ( !*v115 )
          {
            j__nfree_();
LABEL_60:
            LOBYTE(v58) = *(_BYTE *)(uintptr_t)(v57 + 8);
            goto LABEL_61;
          }
          v36 = 31 * unitIndex + g_MapData;
          if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v36 + 852)]
            && (*(_BYTE *)(uintptr_t)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v36 + 864)) >> 5) > 0 )
          {
            v193 = *(_WORD *)(uintptr_t)(v57 + 4);
            HIWORD(v202) = 0;
            v191 = *(_WORD *)(uintptr_t)(v57 + 6);
            if ( *v115 )
            {
              while ( 1 )
              {
                LOBYTE(v36) = v35;
                if ( UnitBattle_IsTileWithinRange(unitIndex, v55, v35) )
                  break;
                v119 = *v117 - 1;
                *v117 = v119;
                v202 = v117[v119 + 1];
                if ( HIWORD(v202) > (int)*(unsigned __int8 *)(uintptr_t)(v57 + 8) )
                  goto LABEL_207;
                *(_WORD *)(uintptr_t)(v57 + 4) = (unsigned __int8)v202;
                *(_WORD *)(uintptr_t)(v57 + 6) = BYTE1(v202);
                if ( !*v117 )
                  goto LABEL_204;
              }
              *(_WORD *)(uintptr_t)(v57 + 4) = v193;
              *(_WORD *)(uintptr_t)(v57 + 6) = v191;
              j__nfree_();
              LOBYTE(v118) = *(_BYTE *)(uintptr_t)(v57 + 8);
              if ( v118 > HIWORD(v202) )
              {
                v58 = v118 - HIWORD(v202);
                goto LABEL_61;
              }
LABEL_201:
              v58 = 0;
LABEL_62:
              v59 = 160 * g_UnitBattleWallScanTileRow + 3204 * unitIndex + 8 * g_BattleWallScanTileX;
              *(int *)((char *)g_UnitBattleTileScoreGrid + v59) -= 640;
              v60 = *(int *)((char *)g_UnitBattleTileScoreGrid + v59) - 5 * (v58 / 5);
              LOBYTE(v36) = g_MapData;
              v61 = g_BattleWallScanTileX + g_MapData + 20 * g_UnitBattleWallScanTileRow;
              *(int *)((char *)g_UnitBattleTileScoreGrid + v59) = v60;
              v35 = v60 + *(char *)(uintptr_t)(v61 + 3134);
              *(int *)((char *)g_UnitBattleTileScoreGrid + v59) = v35;
              goto LABEL_63;
            }
LABEL_204:
            if ( !UnitBattle_IsTileWithinRange(unitIndex, v55, v35) )
            {
LABEL_207:
              *(_WORD *)(uintptr_t)(v57 + 4) = v193;
              *(_WORD *)(uintptr_t)(v57 + 6) = v191;
              j__nfree_();
              goto LABEL_62;
            }
            *(_WORD *)(uintptr_t)(v57 + 4) = v193;
            *(_WORD *)(uintptr_t)(v57 + 6) = v191;
            v36 = HIWORD(v202);
            if ( *(unsigned __int8 *)(uintptr_t)(v57 + 8) > (int)HIWORD(v202) )
            {
              j__nfree_();
              LOBYTE(v120) = *(_BYTE *)(uintptr_t)(v57 + 8);
              v58 = v120 - HIWORD(v202);
              goto LABEL_61;
            }
          }
          else if ( *v115 )
          {
            v201 = v115[1];
            j__nfree_();
            LOBYTE(v116) = *(_BYTE *)(uintptr_t)(v57 + 8);
            if ( v116 <= HIWORD(v201) )
            {
              v58 = 0;
            }
            else
            {
              v58 = v116 - HIWORD(v201);
LABEL_61:
              if ( v58 <= -1 )
                goto LABEL_63;
            }
            goto LABEL_62;
          }
          j__nfree_();
          goto LABEL_201;
        }
        if ( !*v107 )
        {
          j__nfree_();
LABEL_53:
          LOBYTE(v51) = *(_BYTE *)(uintptr_t)(v50 + 8);
          goto LABEL_54;
        }
        v36 = 31 * unitIndex + g_MapData;
        if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v36 + 852)]
          && (*(_BYTE *)(uintptr_t)(v36 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v36 + 864)) >> 5) > 0 )
        {
          v188 = *(_WORD *)(uintptr_t)(v50 + 4);
          HIWORD(v207) = 0;
          v187 = *(_WORD *)(uintptr_t)(v50 + 6);
          if ( *v107 )
          {
            while ( 1 )
            {
              LOBYTE(v36) = v35;
              if ( UnitBattle_IsTileWithinRange(unitIndex, v48, v35) )
                break;
              v111 = *v109 - 1;
              *v109 = v111;
              v207 = v109[v111 + 1];
              if ( HIWORD(v207) > (int)*(unsigned __int8 *)(uintptr_t)(v50 + 8) )
                goto LABEL_175;
              *(_WORD *)(uintptr_t)(v50 + 4) = (unsigned __int8)v207;
              *(_WORD *)(uintptr_t)(v50 + 6) = BYTE1(v207);
              if ( !*v109 )
                goto LABEL_172;
            }
            *(_WORD *)(uintptr_t)(v50 + 4) = v188;
            *(_WORD *)(uintptr_t)(v50 + 6) = v187;
            j__nfree_();
            LOBYTE(v110) = *(_BYTE *)(uintptr_t)(v50 + 8);
            if ( v110 > HIWORD(v207) )
            {
              v51 = v110 - HIWORD(v207);
              goto LABEL_54;
            }
LABEL_169:
            v51 = 0;
LABEL_55:
            v52 = 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanTileX;
            *(int *)((char *)g_UnitBattleTileScoreGrid + v52) -= 640;
            v53 = *(int *)((char *)g_UnitBattleTileScoreGrid + v52) - 5 * (v51 / 5);
            LOBYTE(v36) = g_MapData;
            v54 = g_BattleWallScanTileX + g_MapData + 20 * g_UnitBattleWallScanTileRow;
            *(int *)((char *)g_UnitBattleTileScoreGrid + v52) = v53;
            v35 = v53 + *(char *)(uintptr_t)(v54 + 3134);
            *(int *)((char *)g_UnitBattleTileScoreGrid + v52) = v35;
            goto LABEL_56;
          }
LABEL_172:
          if ( !UnitBattle_IsTileWithinRange(unitIndex, v48, v35) )
          {
LABEL_175:
            *(_WORD *)(uintptr_t)(v50 + 4) = v188;
            *(_WORD *)(uintptr_t)(v50 + 6) = v187;
            j__nfree_();
            goto LABEL_55;
          }
          *(_WORD *)(uintptr_t)(v50 + 4) = v188;
          *(_WORD *)(uintptr_t)(v50 + 6) = v187;
          v36 = HIWORD(v207);
          if ( *(unsigned __int8 *)(uintptr_t)(v50 + 8) > (int)HIWORD(v207) )
          {
            j__nfree_();
            LOBYTE(v112) = *(_BYTE *)(uintptr_t)(v50 + 8);
            v51 = v112 - HIWORD(v207);
            goto LABEL_54;
          }
        }
        else if ( *v107 )
        {
          v206 = v107[1];
          j__nfree_();
          LOBYTE(v108) = *(_BYTE *)(uintptr_t)(v50 + 8);
          if ( v108 <= HIWORD(v206) )
          {
            v51 = 0;
          }
          else
          {
            v51 = v108 - HIWORD(v206);
LABEL_54:
            if ( v51 <= -1 )
              goto LABEL_56;
          }
          goto LABEL_55;
        }
        j__nfree_();
        goto LABEL_169;
      }
      if ( !*v97 )
      {
        j__nfree_();
LABEL_46:
        LOBYTE(v41) = *(_BYTE *)(uintptr_t)(v38 + 8);
        goto LABEL_47;
      }
      LOBYTE(v36) = g_MapData;
      v99 = g_MapData + 31 * unitIndex;
      if ( g_UnitTypeMaxRange_512582[88 * *(__int16 *)(uintptr_t)(v99 + 852)]
        && (*(_BYTE *)(uintptr_t)(v99 + 864) & 3) + 1 - ((unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(v99 + 864)) >> 5) > 0 )
      {
        v197 = *(_WORD *)(uintptr_t)(v38 + 4);
        v190 = *(_WORD *)(uintptr_t)(v38 + 6);
        HIWORD(v204) = 0;
        if ( *v97 )
        {
          while ( 1 )
          {
            LOBYTE(v36) = v39;
            if ( UnitBattle_IsTileWithinRange(unitIndex, v35, v39) )
              break;
            v103 = *v101 - 1;
            *v101 = v103;
            v204 = v101[v103 + 1];
            if ( HIWORD(v204) > (int)*(unsigned __int8 *)(uintptr_t)(v38 + 8) )
              goto LABEL_143;
            *(_WORD *)(uintptr_t)(v38 + 4) = (unsigned __int8)v204;
            *(_WORD *)(uintptr_t)(v38 + 6) = BYTE1(v204);
            if ( !*v101 )
              goto LABEL_140;
          }
          *(_WORD *)(uintptr_t)(v38 + 4) = v197;
          *(_WORD *)(uintptr_t)(v38 + 6) = v190;
          j__nfree_();
          LOBYTE(v102) = *(_BYTE *)(uintptr_t)(v38 + 8);
          if ( v102 > HIWORD(v204) )
          {
            v41 = v102 - HIWORD(v204);
            goto LABEL_47;
          }
LABEL_137:
          v41 = 0;
LABEL_48:
          v42 = 3204 * unitIndex + 160 * g_UnitBattleWallScanTileRow + 8 * g_BattleWallScanColumn;
          v43 = v41;
          v44 = g_UnitBattleWallScanTileRow;
          v36 = *(int *)((char *)g_UnitBattleTileScoreGrid + v42) - 5 * (v43 / 5);
          v45 = 4 * g_UnitBattleWallScanTileRow;
          *(int *)((char *)g_UnitBattleTileScoreGrid + v42) = v36;
          v46 = v36 - 650;
          LOBYTE(v36) = g_MapData;
          v47 = g_BattleWallScanColumn + g_MapData + 4 * (v44 + v45);
          *(int *)((char *)g_UnitBattleTileScoreGrid + v42) = v46;
          v35 = v46 + *(char *)(uintptr_t)(v47 + 3134);
          *(int *)((char *)g_UnitBattleTileScoreGrid + v42) = v35;
          goto LABEL_49;
        }
LABEL_140:
        if ( !UnitBattle_IsTileWithinRange(unitIndex, v35, v39) )
        {
LABEL_143:
          *(_WORD *)(uintptr_t)(v38 + 4) = v197;
          *(_WORD *)(uintptr_t)(v38 + 6) = v190;
          j__nfree_();
          goto LABEL_48;
        }
        *(_WORD *)(uintptr_t)(v38 + 4) = v197;
        *(_WORD *)(uintptr_t)(v38 + 6) = v190;
        v36 = HIWORD(v204);
        if ( *(unsigned __int8 *)(uintptr_t)(v38 + 8) > (int)HIWORD(v204) )
        {
          j__nfree_();
          LOBYTE(v104) = *(_BYTE *)(uintptr_t)(v38 + 8);
          v41 = v104 - HIWORD(v204);
          goto LABEL_47;
        }
      }
      else if ( *v97 )
      {
        v203 = v97[1];
        j__nfree_();
        LOBYTE(v100) = *(_BYTE *)(uintptr_t)(v38 + 8);
        if ( v100 <= HIWORD(v203) )
        {
          v41 = 0;
        }
        else
        {
          v41 = v100 - HIWORD(v203);
LABEL_47:
          if ( v41 <= -1 )
            goto LABEL_49;
        }
        goto LABEL_48;
      }
      j__nfree_();
      goto LABEL_137;
    }
  }
}
// 438681: conditional instruction was optimized away because eax.4!=0
// 4383B1: variable 'v5' is possibly undefined
// 438441: variable 'v8' is possibly undefined
// 4384C7: variable 'v9' is possibly undefined
// 43855E: variable 'v12' is possibly undefined
// 4386A5: variable 'v14' is possibly undefined
// 438702: variable 'i' is possibly undefined
// 43882E: variable 'v25' is possibly undefined
// 438874: variable 'v29' is possibly undefined
// 4388BD: variable 'v32' is possibly undefined
// 4388BF: variable 'v33' is possibly undefined
// 438909: variable 'v34' is possibly undefined
// 438A03: variable 'v37' is possibly undefined
// 438A1E: variable 'v40' is possibly undefined
// 438A53: variable 'v41' is possibly undefined
// 438B49: variable 'v49' is possibly undefined
// 438BBB: variable 'v51' is possibly undefined
// 438CB7: variable 'v56' is possibly undefined
// 438D2A: variable 'v58' is possibly undefined
// 438E4C: variable 'v65' is possibly undefined
// 438E8F: variable 'v67' is possibly undefined
// 438F86: variable 'v73' is possibly undefined
// 438FFB: variable 'v78' is possibly undefined
// 439234: variable 'v90' is possibly undefined
// 4392D3: variable 'v92' is possibly undefined
// 4392F1: variable 'v91' is possibly undefined
// 43936D: variable 'v94' is possibly undefined
// 439514: variable 'v100' is possibly undefined
// 4395BC: variable 'v102' is possibly undefined
// 4395DA: variable 'v101' is possibly undefined
// 439665: variable 'v104' is possibly undefined
// 43980A: variable 'v108' is possibly undefined
// 4398A9: variable 'v110' is possibly undefined
// 4398C7: variable 'v109' is possibly undefined
// 43994F: variable 'v112' is possibly undefined
// 439AF1: variable 'v116' is possibly undefined
// 439B9C: variable 'v118' is possibly undefined
// 439BBA: variable 'v117' is possibly undefined
// 439C48: variable 'v120' is possibly undefined
// 439DF6: variable 'v125' is possibly undefined
// 439E9A: variable 'v127' is possibly undefined
// 439EB8: variable 'v126' is possibly undefined
// 439F45: variable 'v129' is possibly undefined
// 43A105: variable 'v135' is possibly undefined
// 43A1B3: variable 'v137' is possibly undefined
// 43A1D1: variable 'v136' is possibly undefined
// 43A264: variable 'v139' is possibly undefined
// 43A3B0: variable 'v145' is possibly undefined
// 43A3F6: variable 'v149' is possibly undefined
// 43A43F: variable 'v151' is possibly undefined
// 43A43F: variable 'v152' is possibly undefined
// 43A489: variable 'v153' is possibly undefined
// 43A69E: variable 'v161' is possibly undefined
// 43A73B: variable 'v163' is possibly undefined
// 43A75B: variable 'v162' is possibly undefined
// 43A7D7: variable 'v166' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 5159F0: using guessed type int dword_5159F0[8];
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 53206C: using guessed type int g_AttackerStartsOnLeft;
// 532070: using guessed type int g_DefenderStartsOnLeft;
// 53244C: using guessed type int dword_53244C[17621];
// 5437B0: using guessed type int dword_5437B0;
// 5437B4: using guessed type int dword_5437B4;
// 5437B8: using guessed type int dword_5437B8;

//----- (0043A800) --------------------------------------------------------
int  WCIsvListBase_TransferAllInto(int result, int destList)
{
  int v3; // ecx
  int v4; // ecx

  if ( *(_DWORD *)(uintptr_t)(result + 8) )
  {
    WCIsvListBase_PopFrontValue(result, destList);
    WCIsvListBase_TransferAllInto(v3, destList);
    return WCIsvListBase_AppendValue(destList, v4);
  }
  return result;
}
// 43A823: variable 'v3' is possibly undefined
// 43A82C: variable 'v4' is possibly undefined

//----- (0043A880) --------------------------------------------------------
signed int __fastcall WCIsvListBase_PopUntilMatchOrEmpty(int matchValue CLASH95_UNUSED, int list)
{
  int poppedValue; // eax
  int targetValue; // ecx

  if ( !*(_DWORD *)(uintptr_t)(list + 8) )
    return 0;
  while ( 1 )
  {
    poppedValue = WCIsvListBase_PopFrontValue(list, list);
    if ( poppedValue == targetValue )
      break;
    if ( !*(_DWORD *)(uintptr_t)(list + 8) )
      return 0;
  }
  return 1;
}
// 43A898: variable 'v4' is possibly undefined
