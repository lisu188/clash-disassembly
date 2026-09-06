/* Generated from src/recovered/battle/0042CB50_battle.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "battle_internal.h"
#include "battle_state.h"
#include "battle_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0042CB50) --------------------------------------------------------
__int16 UnitBattle_HandleBattlefieldInteraction(void)
{
  DWORD localTileRow; // ebp
  unsigned int localTileCol; // eax
  DWORD tileRow; // esi
  int tileCol; // edi
  int hoveredUnitIndex; // ecx
  int targetUnitIndex; // ebp
  int targetUnitRecordOffset; // edx
  void *cursorDesc; // ecx
  int currentPlayer; // ebx
  int prevSelectedUnitIndex; // esi
  int v10 CLASH95_UNUSED; // ecx
  int v11 CLASH95_UNUSED; // ecx
  int v12; // ecx
  int shooterUnitRecord; // eax
  int rowDelta; // eax
  int v15 CLASH95_UNUSED; // ecx
  int v16 CLASH95_UNUSED; // ecx
  int wallShooterUnitRecord; // eax
  int v18 CLASH95_UNUSED; // ecx
  int v19 CLASH95_UNUSED; // ecx
  int *moveTrackResult; // ecx
  int *moveTrackPath; // eax
  __int16 v22 CLASH95_UNUSED; // bx
  int v23 CLASH95_UNUSED; // ecx
  void (*v24)(void); // edx
  int pathCostPacked; // [esp+0h] [ebp-20h]

  cursorDesc = &g_CursorDesc_Default;
  localTileRow = ((g_MouseCursorRawX >> g_CursorCoordShift)
      - 32
      - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
       + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6;
  localTileCol = ((g_MouseCursorRawY >> g_CursorCoordShift)
      - 16
      - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
       + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6;
  tileRow = localTileRow + *(_DWORD *)(uintptr_t)(g_MapData + 808);
  tileCol = localTileCol + *(_DWORD *)(uintptr_t)(g_MapData + 812);
  if ( localTileRow <= 6 && localTileCol <= 6 )
  {
    if ( DD_IsLost((int)(intptr_t)g_RenderState) )
    {
      hoveredUnitIndex = *(__int16 *)(uintptr_t)(g_MapData + 40 * tileRow + 2 * tileCol + 1534);
      if ( hoveredUnitIndex == -1 )
      {
        if ( *(_BYTE *)(uintptr_t)(tileCol + 20 * tileRow + g_MapData + 3134) )
          UnitBattle_ShowWallInfoPopup(100, 100, tileCol, tileRow, localTileRow);
      }
      else
      {
        Unit_Info(100, 100, 0, (unsigned __int8 *)(uintptr_t)(g_MapData + 852 + 31 * hoveredUnitIndex), localTileRow, 0);
      }
    }
    targetUnitIndex = *(__int16 *)(uintptr_t)(g_MapData + 40 * tileRow + 2 * tileCol + 1534);
    if ( DD_IsLost((int)(intptr_t)g_RenderState) || DD_IsFlipping((int)(intptr_t)g_RenderState) )
      Diagnostics_TraceBattlefieldClickEvent("tile_input", localTileRow, localTileCol, tileRow, tileCol, targetUnitIndex);
    if ( targetUnitIndex == -1 || *(unsigned __int8 *)(uintptr_t)(31 * targetUnitIndex + g_MapData + 854) != g_CurrentPlayerIndex )
    {
      if ( !g_Battle_ShootModeEnabled || targetUnitIndex == -1 || *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * targetUnitIndex + 854) == g_CurrentPlayerIndex )
      {
        if ( targetUnitIndex == -1 || *(_WORD *)(uintptr_t)(31 * g_SelectedUnitIndex + g_MapData + 852) == UNIT_TYPE_RAM )
        {
          if ( *(_BYTE *)(uintptr_t)(g_MapData + 20 * tileRow + tileCol + 3134) )
          {
            if ( g_Battle_ShootModeEnabled )
            {
              if ( UnitBattle_IsTileWithinRange(g_SelectedUnitIndex, tileRow, tileCol)
                && (wallShooterUnitRecord = g_MapData + 31 * g_SelectedUnitIndex, *(unsigned __int8 *)(uintptr_t)(wallShooterUnitRecord + 860) >= 5u)
                && (unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(wallShooterUnitRecord + 864)) >> 5 < (*(_BYTE *)(uintptr_t)(wallShooterUnitRecord + 864) & 3) + 1 )
              {
                if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
                {
                  Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852));
                  g_BattleTargetTileCol = tileCol;
                  Diagnostics_TraceWorldMapActionEvent("battle_wall_shot_enter", g_SelectedUnitIndex, tileRow, tileCol, 0);
                  UnitBattle_ShotWall(g_SelectedUnitIndex, tileRow);
                  Diagnostics_TraceWorldMapActionEvent("battle_wall_shot_return", g_SelectedUnitIndex, tileRow, tileCol, 0);
                  Render_Begin((int)(intptr_t)g_RenderState, 0);
                }
              }
              else
              {
                cursorDesc = &g_CursorDesc_Blocked;
              }
            }
            else
            {
              rowDelta = *(unsigned __int16 *)(uintptr_t)(31 * g_SelectedUnitIndex + g_MapData + 856) - tileRow;
              if ( rowDelta <= 0 )
                rowDelta = tileRow - *(unsigned __int16 *)(uintptr_t)(31 * g_SelectedUnitIndex + g_MapData + 856);
              if ( rowDelta != 1 || *(unsigned __int16 *)(uintptr_t)(31 * g_SelectedUnitIndex + g_MapData + 858) != tileCol )
              {
                BattleLog_Disable();
                Diagnostics_TraceWorldMapActionEvent("battle_wall_move_track_enter", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                moveTrackResult = UnitBattle_MoveTrackNearWall(g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                Diagnostics_TraceWorldMapActionEvent("battle_wall_move_track_return", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                BattleLog_Enable();
                if ( moveTrackResult )
                {
                  pathCostPacked = moveTrackResult[1];
                  if ( HIWORD(pathCostPacked) + 5 <= (int)*(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860) )
                    cursorDesc = &g_CursorDesc_Attack;
                  else
                    cursorDesc = &g_CursorDesc_Blocked;
                  nfree_((int)(uintptr_t)moveTrackResult);
                }
                else
                {
                  pathCostPacked = 1000 << 16;
                  cursorDesc = &g_CursorDesc_Blocked;
                }
              }
              else
              {
                pathCostPacked = 0;
                if ( *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860) >= 5u )
                  cursorDesc = &g_CursorDesc_Attack;
                else
                  cursorDesc = &g_CursorDesc_Blocked;
              }
              Diagnostics_TraceWorldMapActionEvent(
                "battle_wall_selected_state",
                g_SelectedUnitIndex,
                *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852),
                (*(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 856) << 8)
                  | *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 858),
                *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 864));
              Diagnostics_TraceWorldMapActionEvent(
                "battle_wall_move_track_cost",
                g_SelectedUnitIndex,
                HIWORD(pathCostPacked),
                *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860),
                targetUnitIndex);
              if ( DD_IsFlipping((int)(intptr_t)g_RenderState) && cursorDesc == &g_CursorDesc_Attack )
              {
                Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852));
                Diagnostics_TraceWorldMapActionEvent("battle_wall_attack_enter", g_SelectedUnitIndex, tileRow, tileCol, 0);
                UnitBattle_AttackWall(g_SelectedUnitIndex, tileRow, 0, tileCol);
                Diagnostics_TraceWorldMapActionEvent("battle_wall_attack_return", g_SelectedUnitIndex, tileRow, tileCol, 0);
                Render_Begin((int)(intptr_t)g_RenderState, 0);
              }
            }
          }
          else
          {
            BattleLog_Disable();
            Diagnostics_TraceWorldMapActionEvent("battle_move_track_enter", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
            moveTrackResult = UnitBattle_MoveTrack(g_SelectedUnitIndex, tileRow, tileRow, tileCol, targetUnitIndex);
            Diagnostics_TraceWorldMapActionEvent("battle_move_track_return", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
            BattleLog_Enable();
            if ( moveTrackResult )
            {
              pathCostPacked = moveTrackResult[1];
              nfree_((int)(uintptr_t)moveTrackResult);
            }
            else
            {
              pathCostPacked = 1000 << 16;
            }
            Diagnostics_TraceWorldMapActionEvent(
              "battle_move_track_cost",
              g_SelectedUnitIndex,
              HIWORD(pathCostPacked),
              *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860),
              targetUnitIndex);
            if ( HIWORD(pathCostPacked) <= (int)*(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860) )
            {
              if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
              {
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_track_enter", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                moveTrackPath = UnitBattle_MoveTrack(g_SelectedUnitIndex, tileRow, tileRow, tileCol, targetUnitIndex);
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_track_return", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                v22 = g_MapData;
                *(_DWORD *)(uintptr_t)(31 * g_SelectedUnitIndex + g_MapData + 875) = (_DWORD)(uintptr_t)(moveTrackPath);
                Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852));
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_enter", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                UnitBattle_Move(g_SelectedUnitIndex, 0, 0, 0);
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_return", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
                Render_Begin((int)(intptr_t)g_RenderState, 0);
              }
              else
              {
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_no_flip", g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
              }
            }
            else
            {
              cursorDesc = &g_CursorDesc_Blocked;
              Diagnostics_TraceWorldMapActionEvent("battle_move_insufficient_ap", g_SelectedUnitIndex, HIWORD(pathCostPacked), *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860), targetUnitIndex);
            }
          }
          goto LABEL_13;
        }
        if ( DD_IsLost((int)(intptr_t)g_RenderState) )
          Unit_Info(100, 100, 0, (unsigned __int8 *)(uintptr_t)(g_MapData + 852 + 31 * targetUnitIndex), targetUnitIndex, 0);
        BattleLog_Disable();
        moveTrackResult = UnitBattle_MoveTrackNear(g_SelectedUnitIndex, tileRow, tileCol, targetUnitIndex);
        BattleLog_Enable();
        if ( moveTrackResult )
        {
          pathCostPacked = moveTrackResult[0] ? moveTrackResult[1] : 0;
          if ( HIWORD(pathCostPacked) + 5 <= (int)*(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860) )
            cursorDesc = &g_CursorDesc_Attack;
          else
            cursorDesc = &g_CursorDesc_Blocked;
          nfree_((int)(uintptr_t)moveTrackResult);
          if ( DD_IsFlipping((int)(intptr_t)g_RenderState) && cursorDesc == &g_CursorDesc_Attack )
          {
            UnitBattle_Attack(g_SelectedUnitIndex, targetUnitIndex, g_UnitBattleChargeModeActive_532060);
            if ( *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852) == -1 )
              UnitBattle_SelectNextControllableUnit(0, v12, tileCol);
            Render_Begin((int)(intptr_t)g_RenderState, 0);
          }
          goto LABEL_13;
        }
      }
      else if ( UnitBattle_IsUnitWithinRange(g_SelectedUnitIndex, targetUnitIndex) )
      {
        shooterUnitRecord = g_MapData + 31 * g_SelectedUnitIndex;
        if ( *(unsigned __int8 *)(uintptr_t)(shooterUnitRecord + 860) >= 5u
          && (unsigned __int8)(2 * *(_BYTE *)(uintptr_t)(shooterUnitRecord + 864)) >> 5 < (*(_BYTE *)(uintptr_t)(shooterUnitRecord + 864) & 3) + 1 )
        {
          if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
          {
            UnitBattle_Shot((int)(intptr_t)(cursorDesc), targetUnitIndex);
            Render_Begin((int)(intptr_t)g_RenderState, 0);
          }
          goto LABEL_13;
        }
      }
      cursorDesc = &g_CursorDesc_Blocked;
    }
    else if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
    {
      currentPlayer = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(uintptr_t)(targetUnitRecordOffset + g_MapData + 854) == g_CurrentPlayerIndex )
      {
        prevSelectedUnitIndex = g_SelectedUnitIndex;
        if ( targetUnitIndex != g_SelectedUnitIndex )
        {
          g_SelectedUnitIndex = targetUnitIndex;
          UnitBattle_RefreshSelectedActionButtons();
          UnitBattle_RedrawUnitFootprint(prevSelectedUnitIndex);
          UnitBattle_RedrawUnitFootprint(targetUnitIndex);
          UnitBattle_DrawSelectedUnitPanel(0, 1, currentPlayer, tileCol);
          Audio_PlayUnitActivateSound(*(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852));
        }
      }
    }
LABEL_13:
    LOWORD(localTileCol) = RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)cursorDesc);
  }
  return localTileCol;
}
// 42CBA8: simplified comparisons for 'ebp.4': <0 || >=7 became >=7u
// 42CBB1: simplified comparisons for 'eax.4': >=0 && <7 became <7u
// 42CC78: variable 'v6' is possibly undefined
// 42CCE5: variable 'v7' is possibly undefined
// 42CDCE: variable 'v10' is possibly undefined
// 42CDDE: variable 'v11' is possibly undefined
// 42CE8B: variable 'v12' is possibly undefined
// 42D044: variable 'v15' is possibly undefined
// 42D07D: variable 'v16' is possibly undefined
// 42D14E: variable 'v18' is possibly undefined
// 42D172: variable 'v19' is possibly undefined
// 42D180: variable 'v20' is possibly undefined
// 42D234: variable 'v23' is possibly undefined
// 42D23E: variable 'v24' is possibly undefined
// 429740: using guessed type int __fastcall UnitBattle_Shot(_DWORD, _DWORD);
// 429BD0: using guessed type int __fastcall UnitBattle_ShotWall(_DWORD, _DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;
// 53205C: using guessed type int dword_53205C;
// 532060: using guessed type int dword_532060;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0042D250) --------------------------------------------------------
__int16 UnitBattle_EnableSelectedChargeMode(void)
{
  g_UnitBattleChargeModeActive_532060 = 1;
  g_UnitBattleChargeModeStartTick_532074 = Time_Now(2, 1);
  g_UnitBattleChargeButtonState = 2;
  UIWidget_RefreshActionButtonState((uintptr_t)&g_UnitBattleChargeButtonWidget, 2);
  return UnitBattle_RedrawUnitFootprint(g_SelectedUnitIndex);
}
// 42D271: variable 'v1' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514BEA: using guessed type int dword_514BEA;
// 532060: using guessed type int dword_532060;
// 532074: using guessed type int dword_532074;

//----- (0042D290) --------------------------------------------------------
__int16 UnitBattle_RefreshSelectedUnitUI(void)
{
  g_UnitBattleChargeModeActive_532060 = 0;
  g_UnitBattleChargeButtonState = 1;
  UIWidget_RefreshActionButtonState((int)(intptr_t)&g_UnitBattleChargeButtonWidget, 1);
  return UnitBattle_RedrawUnitFootprint(g_SelectedUnitIndex);
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514BEA: using guessed type int dword_514BEA;
// 532060: using guessed type int dword_532060;

//----- (0042D2C0) --------------------------------------------------------
int UnitBattle_RefreshSelectedActionButtons(void)
{
  void *savedRenderDevice; // ebx
  int result; // eax
  int selected_type_offset;

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  if ( g_UnitBattleChargeModeActive_532060 )
    UnitBattle_RefreshSelectedUnitUI();
  selected_type_offset = 88 * *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  if ( !g_UnitTypeMaxRange_512582[selected_type_offset] )
  {
    g_Battle_ShootModeEnabled = 0;
    g_UnitBattleShootButtonState = 1;
    goto LABEL_6;
  }
  if ( !g_UnitTypeBaseMeleeAttack_51257E[selected_type_offset] )
  {
    g_UnitBattleShootButtonState = 2;
    g_Battle_ShootModeEnabled = 1;
LABEL_6:
    result = UIWidget_RefreshActionButtonState((uintptr_t)&g_UnitBattleActionWidgetTable, 1);
    g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
    return result;
  }
  g_Battle_ShootModeEnabled = 1;
  g_UnitBattleShootButtonState = 2;
  result = UIWidget_RefreshActionButtonState((uintptr_t)&g_UnitBattleActionWidgetTable, 1);
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514B80: using guessed type int dword_514B80;
// 532048: using guessed type int g_MapData;
// 53205C: using guessed type int dword_53205C;
// 532060: using guessed type int dword_532060;

//----- (0042D3A0) --------------------------------------------------------
int  UnitBattle_SelectNextControllableUnit(int widget, int a2, char a3)
{
  int i; // ecx
  int unitRecord; // edx
  int mapData; // ebx
  int v6 CLASH95_UNUSED; // ecx
  int selectedUnitRecord; // edx
  int result; // eax

  Diagnostics_TraceWorldMapActionEvent("battle_action_next_unit_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, widget, a2);
  if ( widget )
    UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  for ( i = (g_SelectedUnitIndex + 1) % 22; i != g_SelectedUnitIndex; i = (i + 1) % 22 )
  {
    unitRecord = 31 * i + g_MapData;
    if ( *(__int16 *)(uintptr_t)(unitRecord + 852) != -1 && *(unsigned __int8 *)(uintptr_t)(unitRecord + 854) == g_CurrentPlayerIndex )
      break;
  }
  mapData = g_MapData;
  g_SelectedUnitIndex = i;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_action_next_unit_selected",
    g_SelectedUnitIndex,
    *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 856),
    *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 858),
    0);
  if ( !UnitBattle_IsTileInViewport(
          *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * i + 856),
          *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * i + 858)) )
    UnitBattle_CenterViewOnUnit(i);
  UnitBattle_RefreshSelectedActionButtons();
  UnitBattle_RedrawVisibleGrid();
  UnitBattle_DrawSelectedUnitPanel(0, 1, mapData, a3);
  selectedUnitRecord = g_MapData + 31 * g_SelectedUnitIndex;
  result = *(__int16 *)(uintptr_t)(selectedUnitRecord + 852);
  if ( result != -1 )
  {
    if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(selectedUnitRecord + 854) + 140051) )
      return Audio_PlayUnitActivateSound(result);
  }
  return result;
}
// 42D43B: variable 'v6' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;

//----- (0042D4E0) --------------------------------------------------------
int UnitBattle_ToggleSelectedShootingMode(uintptr_t widget, int a2, DWORD a3, char a4, double a5)
{
  int type_offset; // eax
  int result; // eax

  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;

  Diagnostics_TraceWorldMapActionEvent("battle_action_shoot_toggle_enter", g_SelectedUnitIndex, g_Battle_ShootModeEnabled, (int)widget, 0);
  type_offset = 88 * *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  result = (unsigned __int8)g_UnitTypeBaseMeleeAttack_51257E[type_offset];
  if ( g_UnitTypeBaseMeleeAttack_51257E[type_offset] )
  {
    result = (unsigned __int8)g_UnitTypeMaxRange_512582[type_offset];
    if ( g_UnitTypeMaxRange_512582[type_offset] )
    {
      result = Render_Begin((int)(intptr_t)g_RenderState, 0);
      LOBYTE(g_Battle_ShootModeEnabled) = g_Battle_ShootModeEnabled ^ 1;
      if ( g_Battle_ShootModeEnabled )
      {
        if ( widget )
          *(_DWORD *)(widget + 8) = 2;
        if ( g_UnitBattleChargeModeActive_532060 )
          result = UnitBattle_RefreshSelectedUnitUI();
      }
      else
      {
        if ( widget )
          *(_DWORD *)(widget + 8) = 1;
      }
      Diagnostics_TraceWorldMapActionEvent("battle_action_shoot_toggle_done", g_SelectedUnitIndex, g_Battle_ShootModeEnabled, result, 0);
    }
  }
  return result;
}
// 42D53C: variable 'v2' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 532048: using guessed type int g_MapData;
// 53205C: using guessed type int dword_53205C;
// 532060: using guessed type int dword_532060;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042D560) --------------------------------------------------------
int  UnitBattle_HandleRetreatAction(int widget, int unitIndex, char promptSpriteName, DWORD a4)
{
  int result; // eax
  _DWORD promptStrings[4]; // [esp+0h] [ebp-10h] BYREF

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, unitIndex);
  result = g_MapData;
  if ( g_CurrentPlayerIndex != *(_DWORD *)(uintptr_t)(g_MapData + 840) || *(_DWORD *)(uintptr_t)(g_MapData + 848) )
  {
    promptStrings[0] = (_DWORD)(uintptr_t)(g_UnitBattleRetreatMessageStrings[0]);
    promptStrings[1] = (_DWORD)(uintptr_t)(g_UnitBattleRetreatMessageStrings[1]);
    promptStrings[2] = (_DWORD)(uintptr_t)(g_UnitBattleRetreatMessageStrings[2]);
    result = UnitBattle_ShowCurrentPlayerPromptDialog((int)(intptr_t)promptStrings, promptSpriteName, a4);
    g_BattleLoopExitCode = result;
  }
  return result;
}
// 514B5C: using guessed type char *off_514B5C[6];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;
// 532064: using guessed type int g_BattleLoopExitCode;

//----- (0042D5B0) --------------------------------------------------------
int UnitBattle_ToggleSelectedChargeMode(uintptr_t widget, int a2, DWORD a3, char a4, double a5)
{
  int result; // eax
  int type_offset; // eax

  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;

  Diagnostics_TraceWorldMapActionEvent("battle_action_charge_toggle_enter", g_SelectedUnitIndex, g_UnitBattleChargeModeActive_532060, (int)widget, 0);
  type_offset = 88 * *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  result = (unsigned __int8)g_UnitTypeBaseMeleeAttack_51257E[type_offset];
  if ( g_UnitTypeBaseMeleeAttack_51257E[type_offset] )
  {
    Render_Begin((int)(intptr_t)g_RenderState, 0);
    LOBYTE(g_UnitBattleChargeModeActive_532060) = g_UnitBattleChargeModeActive_532060 ^ 1;
    g_UnitBattleChargeModeStartTick_532074 = Time_Now(0, 0);
    result = UnitBattle_RedrawUnitNeighborhood(g_SelectedUnitIndex);
    if ( g_UnitBattleChargeModeActive_532060 )
    {
      result = Audio_PlaySoundEffectByName(aBattleSzarza, 64);
      if ( widget )
        *(_DWORD *)(widget + 8) = 2;
      if ( g_Battle_ShootModeEnabled )
      {
        g_Battle_ShootModeEnabled = 0;
        g_UnitBattleShootButtonState = 1;
        return UIWidget_RefreshActionButtonState((uintptr_t)g_UnitBattleActionWidgetTable, 1);
      }
    }
    else
    {
      if ( widget )
        *(_DWORD *)(widget + 8) = 1;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_action_charge_toggle_done", g_SelectedUnitIndex, g_UnitBattleChargeModeActive_532060, result, 0);
  }
  return result;
}
// 42D5F7: variable 'v3' is possibly undefined
// 42D5F7: variable 'v2' is possibly undefined
// 42D614: variable 'v4' is possibly undefined
// 42D62E: variable 'v5' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514B78: using guessed type _DWORD dword_514B78[2];
// 514B80: using guessed type int dword_514B80;
// 532048: using guessed type int g_MapData;
// 53205C: using guessed type int dword_53205C;
// 532060: using guessed type int dword_532060;
// 532074: using guessed type int dword_532074;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042D670) --------------------------------------------------------
int  UnitBattle_HandlePrepareDefenceAction(int widget, int a2, DWORD a3, char a4, char a5)
{
  int mapData; // ebx
  int result; // eax
  int v8 CLASH95_UNUSED; // ecx
  int defenceMessageStrings[6]; // [esp+0h] [ebp-18h]

  Diagnostics_TraceWorldMapActionEvent("battle_action_prepare_defence_enter", g_SelectedUnitIndex, widget, a2, 0);
  defenceMessageStrings[4] = a2;
  mapData = g_MapData;
  result = 31 * g_SelectedUnitIndex;
  if ( (*(_BYTE *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 874) & 1) == 0 )
  {
    UIWidget_PlayPressedReleaseAnimationWithDelay(widget, g_SelectedUnitIndex);
    if ( !UnitBattle_Defence(g_SelectedUnitIndex, 0, a3) )
    {
      defenceMessageStrings[0] = (int)(intptr_t)g_UnitBattlePrepareDefenceMessageStrings[0];
      defenceMessageStrings[1] = (int)(intptr_t)g_UnitBattlePrepareDefenceMessageStrings[1];
      defenceMessageStrings[2] = (int)(intptr_t)g_UnitBattlePrepareDefenceMessageStrings[2];
      Tooltip_ShowText(3, (char *)(uintptr_t)defenceMessageStrings[(unsigned __int8)g_LanguageIndex], a5);
    }
    UnitBattle_RedrawVisibleGrid();
    Diagnostics_TraceWorldMapActionEvent(
      "battle_action_prepare_defence_done",
      g_SelectedUnitIndex,
      *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 860),
      *(unsigned __int8 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 864),
      0);
    return UnitBattle_DrawSelectedUnitPanel(0, 1, mapData, a4);
  }
  return result;
}
// 42D6A8: variable 'v8' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514B68: using guessed type char *off_514B68[3];
// 532048: using guessed type int g_MapData;

//----- (0042D6F0) --------------------------------------------------------
int UnitBattle_RequestActionLoopExit(uintptr_t widget, int a2, DWORD a3, char a4, double a5)
{
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;

  Diagnostics_TraceWorldMapActionEvent("battle_action_loop_exit_requested", g_SelectedUnitIndex, g_CurrentPlayerIndex, (int)widget, 0);
  g_UnitBattleActionLoopExitRequested = 1;
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  if ( widget )
  {
    *(_BYTE *)(widget + 8) &= ~4u;
    return UIWidget_RefreshActionButtonState(widget, 1);
  }
  return 0;
}
// 42D70B: variable 'v1' is possibly undefined
// 532068: using guessed type int g_UnitBattleActionLoopExitRequested;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042D730) --------------------------------------------------------
int  UnitBattle_ShowPlayerMessageBanner(int messageText, int playerIndex, int doFlipWait, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  _DWORD *windowSpriteSet; // eax
  void *v7 CLASH95_UNUSED; // ecx
  int v8; // ecx
  _DWORD *Surface; // eax
  DWORD bannerSurface; // ebp
  int SpriteForChar; // eax
  int labelText; // edi
  int v13 CLASH95_UNUSED; // edx
  int msgTextBottom; // ebx
  int msgTextTop; // esi
  int v16 CLASH95_UNUSED; // ecx
  int v17 CLASH95_UNUSED; // ecx
  int v18 CLASH95_UNUSED; // ecx
  int v19; // ecx
  int playerLabelStrings[3]; // [esp+1Ch] [ebp-48h]
  int spriteSetSlot[2]; // [esp+28h] [ebp-3Ch] BYREF
  int (*savedRenderHook)(int, char, DWORD); // [esp+30h] [ebp-34h]
  int savedResourceHandle; // [esp+34h] [ebp-30h]
  int windowRight; // [esp+38h] [ebp-2Ch]
  int windowBottom; // [esp+3Ch] [ebp-28h]
  int savedPlayerIndex; // [esp+40h] [ebp-24h]
  int windowLeft; // [esp+44h] [ebp-20h]
  int savedMessageText; // [esp+48h] [ebp-1Ch]
  void *savedRenderDevice; // [esp+4Ch] [ebp-18h]
  int windowTop; // [esp+50h] [ebp-14h]
  int flip_wait_pumps;

  savedMessageText = messageText;
  savedPlayerIndex = playerIndex;
  spriteSetSlot[1] = doFlipWait;
  Diagnostics_TraceWorldMapActionEvent("battle_banner_enter", messageText, playerIndex, doFlipWait, (int)a4);
  savedResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = Render_DefaultRH;
  Debug_Log(v4, doFlipWait, a4, (int)(intptr_t)aSetrhS08x_9);
  Render_Pump();
  windowSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v5, doFlipWait, a4);
  if ( windowSpriteSet )
    windowSpriteSet = DLXSpriteSet_Load(windowSpriteSet, "okno1.s32");
  spriteSetSlot[0] = (int)(intptr_t)windowSpriteSet;
  Render_ReleaseSurface(8, a4);
  Render_ReleaseSurface(7, a4);
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  windowTop = (448 - (unsigned __int16)DLX_GetSpriteHeight(spriteSetSlot[0], 0)) / 2 + 32;
  windowLeft = (480 - (unsigned __int16)DLX_GetSpriteWidth(spriteSetSlot[0], 0)) / 2;
  windowBottom = windowTop + (unsigned __int16)DLX_GetSpriteHeight(spriteSetSlot[0], 0) - 1;
  windowRight = windowLeft + (unsigned __int16)DLX_GetSpriteWidth(spriteSetSlot[0], 0) - 1;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v8, windowTop, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, windowBottom - windowTop + 1, windowRight - windowLeft + 1);
  bannerSurface = (DWORD)(intptr_t)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)windowLeft, (unsigned __int16)windowTop, windowBottom, windowRight, 0, 0);
  SpriteForChar = DLX_GetSpriteForChar(spriteSetSlot[0], savedPlayerIndex);
  Compat_RenderDeviceDrawMenuSprite(windowLeft, windowTop, SpriteForChar, 1);
  Render_ReleaseSurface(7, bannerSurface);
  playerLabelStrings[0] = (int)(intptr_t)g_UnitBattlePlayerLabelStrings[0];
  playerLabelStrings[1] = (int)(intptr_t)g_UnitBattlePlayerLabelStrings[1];
  playerLabelStrings[2] = (int)(intptr_t)g_UnitBattlePlayerLabelStrings[2];
  labelText = playerLabelStrings[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(labelText, windowTop, windowBottom, windowLeft + 40, 3, (const char*)(intptr_t)(labelText));
  Render_ReleaseSurface(8, bannerSurface);
  msgTextBottom = windowBottom;
  msgTextTop = windowTop;
  UI_DrawTextFmt(labelText, windowTop, windowBottom, windowLeft + 55, 3, (const char*)(intptr_t)(PLAYER_DATA(savedPlayerIndex) + PLAYER_DISPLAY_NAME_OFFSET));
  UI_DrawTextFmt(savedMessageText, msgTextTop, msgTextBottom, windowLeft + 100, 3, (const char*)(intptr_t)(savedMessageText));
  Render_Present((int)(intptr_t)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent("battle_banner_after_present", messageText, playerIndex, spriteSetSlot[1], bannerSurface);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  if ( spriteSetSlot[1] )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_banner_before_flip_wait", messageText, playerIndex, DD_IsFlipping((int)(intptr_t)g_RenderState), bannerSurface);
    Render_Begin((int)(intptr_t)g_RenderState, 0);
    flip_wait_pumps = 0;
    while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) && flip_wait_pumps < 8 )
    {
      DD_Pump((int)(intptr_t)g_RenderState, 0);
      ++flip_wait_pumps;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_banner_after_flip_wait", messageText, playerIndex, DD_IsFlipping((int)(intptr_t)g_RenderState), flip_wait_pumps);
    if ( bannerSurface )
    {
      if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
        Render_Begin((int)(intptr_t)g_RenderState, 0);
      Render_Pump();
      Render_FillRect((_DWORD *)(uintptr_t)bannerSurface, 0, 0, 0, windowBottom - windowTop, windowRight - windowLeft, windowTop, windowLeft);
      Diagnostics_TraceWorldMapActionEvent("battle_banner_after_restore", messageText, playerIndex, bannerSurface, 0);
    }
  }
  Compat_InvokeCompactSurfaceDestructor(bannerSurface, 2);
  Diagnostics_TraceWorldMapActionEvent("battle_banner_after_surface_release", messageText, playerIndex, bannerSurface, 0);
  RenderState_WarpCursorAndPump(g_RenderState, 0x140u, 0xF0u);
  Debug_Log(v19, (char)(intptr_t)g_RenderHook, bannerSurface, (int)(intptr_t)aUnsetrh08x_8);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, savedResourceHandle);
  Render_Present((int)(intptr_t)g_RenderState);
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  Diagnostics_TraceWorldMapActionEvent("battle_banner_done", messageText, playerIndex, (int)(uintptr_t)g_RenderDevice, 0);
  return DLXSpriteSet_ReleaseAndClear(spriteSetSlot);
}
// 42D782: variable 'v4' is possibly undefined
// 42D799: variable 'v5' is possibly undefined
// 42D7D8: variable 'v7' is possibly undefined
// 42D85E: variable 'v8' is possibly undefined
// 42D945: variable 'v13' is possibly undefined
// 42D9A0: variable 'v16' is possibly undefined
// 42D9BB: variable 'v17' is possibly undefined
// 42D9C8: variable 'v18' is possibly undefined
// 42DA52: variable 'v19' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514CEC: using guessed type char *off_514CEC[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (0042DAB0) --------------------------------------------------------
int  UnitBattleDialog_SelectAffirmativeResponse(int widget, int unitIndex)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, unitIndex);
  g_UnitBattlePromptDialogResult = v4;
  return result;
}
// 42DABB: variable 'v4' is possibly undefined
// 532080: using guessed type int g_UnitBattlePromptDialogResult;

//----- (0042DAD0) --------------------------------------------------------
int  UnitBattleDialog_SelectNegativeResponse(int widget, int unitIndex)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, unitIndex);
  g_UnitBattlePromptDialogResult = v4;
  return result;
}
// 42DAD8: variable 'v4' is possibly undefined
// 532080: using guessed type int g_UnitBattlePromptDialogResult;

//----- (0042DAE0) --------------------------------------------------------
int  UnitBattle_ShowCurrentPlayerPromptDialog(int messageStrings, char spriteName, DWORD a3)
{
  int v4; // ecx
  _DWORD *spriteSetAlloc; // eax
  _DWORD *Surface; // eax
  DWORD dialogSurface; // ebp
  int SpriteForChar; // eax
  int v9; // edi
  int v10; // esi
  _DWORD widgetTable[40]; // [esp+0h] [ebp-E0h] BYREF
  int labelText[3]; // [esp+A0h] [ebp-40h]
  _DWORD *spriteSet; // [esp+ACh] [ebp-34h] BYREF
  void *savedRenderDevice; // [esp+B0h] [ebp-30h]
  int windowBottom; // [esp+B4h] [ebp-2Ch]
  int savedMessageStrings; // [esp+B8h] [ebp-28h]
  int windowTop; // [esp+BCh] [ebp-24h]
  int windowLeft; // [esp+C0h] [ebp-20h]
  int windowRight; // [esp+C4h] [ebp-1Ch]

  savedMessageStrings = messageStrings;
  Render_Pump();
  spriteSetAlloc = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v4, spriteName, a3);
  if ( spriteSetAlloc )
    spriteSetAlloc = DLXSpriteSet_Load(spriteSetAlloc, (const void*)(intptr_t)(spriteName));
  spriteSet = spriteSetAlloc;
  Render_ReleaseSurface(8, a3);
  Render_ReleaseSurface(7, a3);
  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  windowTop = (448 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0)) / 2 + 32;
  windowLeft = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0)) / 2;
  windowBottom = windowTop + (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)spriteSet, 0) - 1;
  windowRight = windowLeft + (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)spriteSet, 0) - 1;
  qmemcpy(widgetTable, &g_UnitBattlePlayerPromptDialogTemplate, 0x9Fu);
  widgetTable[0] = windowTop + 232;
  widgetTable[1] = windowLeft + 108;
  widgetTable[3] = (_DWORD)(uintptr_t)(&spriteSet);
  *(_DWORD *)((char *)&widgetTable[13] + 1) = windowTop + 27;
  *(_DWORD *)((char *)&widgetTable[14] + 1) = windowLeft + 108;
  *(_DWORD *)((char *)&widgetTable[16] + 1) = (_DWORD)(uintptr_t)(&spriteSet);
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, windowLeft, a3);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, windowBottom - windowTop + 1, windowRight - windowLeft + 1);
  dialogSurface = (DWORD)(intptr_t)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)windowLeft, (unsigned __int16)windowTop, windowBottom, windowRight, 0, 0);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)spriteSet, g_CurrentPlayerIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    windowLeft,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(7, dialogSurface);
  labelText[0] = (int)(intptr_t)g_UnitBattlePlayerPromptLabelStrings[0];
  labelText[1] = (int)(intptr_t)g_UnitBattlePlayerPromptLabelStrings[1];
  labelText[2] = (int)(intptr_t)g_UnitBattlePlayerPromptLabelStrings[2];
  v9 = windowBottom;
  UI_DrawTextFmt(windowBottom, windowTop, windowBottom, windowLeft + 40, 3, (const char*)(intptr_t)(labelText[(unsigned __int8)g_LanguageIndex]));
  Render_ReleaseSurface(8, dialogSurface);
  v10 = windowTop;
  UI_DrawTextFmt(v9, windowTop, v9, windowLeft + 55, 3, (const char*)(intptr_t)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_DISPLAY_NAME_OFFSET));
  UI_DrawTextFmt(savedMessageStrings, v10, v9, windowLeft + 100, 3, (const char*)(uintptr_t)(*(_DWORD *)(uintptr_t)(savedMessageStrings + 4 * (unsigned __int8)g_LanguageIndex)));
  UIWidgetTable_InitDrawStates(widgetTable);
  Render_Present((int)(intptr_t)g_RenderState);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
  while ( UIWidgetTable_PollHoverAndActions(widgetTable, dialogSurface) != 3 )
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)g_RenderState);
  Render_Pump();
  Render_FillRect((_DWORD *)(uintptr_t)dialogSurface, 0, 0, 0, windowBottom - windowTop, windowRight - windowLeft, windowTop, windowLeft);
  if ( dialogSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)(unsigned int)dialogSurface, 2);
  RenderState_WarpCursorAndPump(g_RenderState, 0x140u, 0xF0u);
  Render_Present((int)(intptr_t)g_RenderState);
  g_RenderDevice = (_UNKNOWN*)(savedRenderDevice);
  DLXSpriteSet_ReleaseAndClear((int *)&spriteSet);
  return g_UnitBattlePromptDialogResult;
}
// 42DB02: variable 'v4' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514D98: using guessed type char *off_514D98[2];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532080: using guessed type int g_UnitBattlePromptDialogResult;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (0042DEC0) --------------------------------------------------------
int  UnitBattle_AnimateSelectedUnitPanel(int aiMode, int a2, int a3)
{
  int v4; // eax
  char v5; // dl
  int unitRecord; // ecx
  int volleyCount; // edx
  int moraleValue; // eax
  int lastSprite; // edi
  int v10 CLASH95_UNUSED; // ecx
  unsigned int now; // eax
  unsigned int frameDeadline; // edx
  int iconArrayIndex; // esi
  unsigned int animCounter; // eax
  int v15; // eax
  int v16; // ebx
  int result; // eax
  __int16 SpriteHeight; // ax
  unsigned __int16 iconRight; // [esp+Ch] [ebp-34h]
  unsigned __int16 iconX; // [esp+10h] [ebp-30h]
  unsigned __int16 iconY; // [esp+14h] [ebp-2Ch]
  int frameCounter; // [esp+1Ch] [ebp-24h]
  int animStartTime; // [esp+20h] [ebp-20h]
  int i; // [esp+24h] [ebp-1Ch]
  int j; // [esp+24h] [ebp-1Ch]

  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, aiMode, 0);
  UnitBattle_DrawSelectedUnitPanel(g_MapData + 852 + 31 * g_SelectedUnitIndex, 0, a2, a3);
  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_after_panel", g_SelectedUnitIndex, g_CurrentPlayerIndex, aiMode, 0);
  Render_Pump();
  g_RenderDevice = (_UNKNOWN*)(&g_MainRenderDevice);
  for ( i = 0; i < 6; ++i )
  {
    v4 = i;
    g_UnitBattlePanelStatAnimCounters[i] = i;
    v5 = -(char)i;
    g_UnitBattlePanelStatAnimCounters[v4] = v5;
  }
  unitRecord = 31 * g_SelectedUnitIndex + g_MapData;
  volleyCount = *(_BYTE *)(uintptr_t)(unitRecord + 864) & 3;
  g_UnitBattlePanelVolleyIconChar = 9 * volleyCount;
  moraleValue = *(char *)(uintptr_t)(unitRecord + 863);
  if ( (unsigned int)moraleValue <= 4 )
  {
    g_UnitBattlePanelMoraleIconChar = 72;
  }
  else if ( moraleValue < 5 || moraleValue > 10 )
  {
    if ( moraleValue < 11 || moraleValue > 15 )
      g_UnitBattlePanelMoraleIconChar = 45;
    else
      g_UnitBattlePanelMoraleIconChar = 54;
  }
  else
  {
    g_UnitBattlePanelMoraleIconChar = 63;
  }
  lastSprite = 0;
  animStartTime = Time_Now(0, 0);
  frameCounter = 0;
  do
  {
    frameDeadline = animStartTime + 8;
    do
      now = Time_Now(0, 0);
    while ( now < frameDeadline );
    animStartTime = Time_Now(0, 0);
    iconArrayIndex = 0;
    for ( j = 0; j < 6; ++j )
    {
      animCounter = g_UnitBattlePanelStatAnimCounters[j];
      if ( animCounter > 8 )
      {
        if ( g_UnitBattlePanelStatAnimCounters[j] >= 9 && !aiMode )
        {
          iconY = g_UnitBattlePanelStatIconY[iconArrayIndex];
          iconX = g_UnitBattlePanelStatIconX[iconArrayIndex];
          iconRight = iconY + DLX_GetSpriteWidth(g_BattleUnitPanelIconSpriteSet, 0) + 1;
          SpriteHeight = DLX_GetSpriteHeight(g_BattleUnitPanelIconSpriteSet, 0);
          Render_FillRect(
            (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
            0,
            (unsigned __int16)g_UnitBattlePanelStatIconY[iconArrayIndex],
            (unsigned __int16)g_UnitBattlePanelStatIconX[iconArrayIndex],
            g_UnitBattlePanelStatIconX[iconArrayIndex] + SpriteHeight + 1,
            iconRight,
            iconX,
            iconY);
        }
      }
      else
      {
        if ( !aiMode )
          animCounter = 8 - animCounter;
        lastSprite = DLX_GetSpriteForChar(g_BattleUnitPanelIconSpriteSet, animCounter + (unsigned __int8)g_UnitBattlePanelQuantityIconCharBase[j]);
        Compat_RenderDeviceDrawMenuSprite(-1, -1, lastSprite, 1);
      }
      v15 = j;
      iconArrayIndex += 2;
      g_UnitBattlePanelStatAnimCounters[v15] = g_UnitBattlePanelStatAnimCounters[j] + 1;
    }
    v16 = frameCounter + 1;
    frameCounter = v16;
  }
  while ( v16 < 15 );
  result = Render_Present((int)(intptr_t)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_after_present", g_SelectedUnitIndex, g_CurrentPlayerIndex, aiMode, 0);
  if ( !aiMode )
  {
    result = UnitBattle_DrawSelectedUnitPanel(0, 1, v16, lastSprite);
    Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_exit", g_SelectedUnitIndex, g_CurrentPlayerIndex, aiMode, result);
    return result;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_exit", g_SelectedUnitIndex, g_CurrentPlayerIndex, aiMode, result);
  return result;
}
// 42DF62: simplified comparisons for 'eax.4': >=0 && <5 became <5u
// 42DFC3: simplified comparisons for 'eax.4': <0 || >=9 became >=9u
// 42DF9C: variable 'v10' is possibly undefined
// 42DFA3: variable 'v12' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514DA4: using guessed type __int16 word_514DA4[];
// 514DA6: using guessed type __int16 word_514DA6[];
// 514DC3: using guessed type char byte_514DC3;
// 514DC4: using guessed type char byte_514DC4;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 532054: using guessed type int dword_532054;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042E160) --------------------------------------------------------
__int16  UnitBattle_UpdateActionTooltip(char a1, int a2, int a3)
{
  int hoveredAction; // eax

  if ( g_MouseCursorRawX >> g_CursorCoordShift < 535
    || g_MouseCursorRawY >> g_CursorCoordShift < 30
    || g_MouseCursorRawX >> g_CursorCoordShift > 623
    || g_MouseCursorRawY >> g_CursorCoordShift > 83 )
  {
    if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
      || g_MouseCursorRawY >> g_CursorCoordShift < 91
      || g_MouseCursorRawX >> g_CursorCoordShift > 623
      || g_MouseCursorRawY >> g_CursorCoordShift > 137 )
    {
      if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
        || g_MouseCursorRawY >> g_CursorCoordShift < 145
        || g_MouseCursorRawX >> g_CursorCoordShift > 623
        || g_MouseCursorRawY >> g_CursorCoordShift > 179 )
      {
        if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
          || g_MouseCursorRawY >> g_CursorCoordShift < 179
          || g_MouseCursorRawX >> g_CursorCoordShift > 623
          || g_MouseCursorRawY >> g_CursorCoordShift > 213 )
        {
          if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
            || g_MouseCursorRawY >> g_CursorCoordShift < 213
            || g_MouseCursorRawX >> g_CursorCoordShift > 623
            || g_MouseCursorRawY >> g_CursorCoordShift > 247 )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
              || g_MouseCursorRawY >> g_CursorCoordShift < 247
              || g_MouseCursorRawX >> g_CursorCoordShift > 623
              || g_MouseCursorRawY >> g_CursorCoordShift > 281 )
            {
              if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
                || g_MouseCursorRawY >> g_CursorCoordShift < 281
                || g_MouseCursorRawX >> g_CursorCoordShift > 623
                || g_MouseCursorRawY >> g_CursorCoordShift > 315 )
              {
                if ( g_MouseCursorRawX >> g_CursorCoordShift < 499
                  || g_MouseCursorRawY >> g_CursorCoordShift < 315
                  || g_MouseCursorRawX >> g_CursorCoordShift > 623
                  || g_MouseCursorRawY >> g_CursorCoordShift > 349 )
                {
                  hoveredAction = -1;
                }
                else
                {
                  hoveredAction = 7;
                }
              }
              else
              {
                hoveredAction = 6;
              }
            }
            else
            {
              hoveredAction = 5;
            }
          }
          else
          {
            hoveredAction = 4;
          }
        }
        else
        {
          hoveredAction = 3;
        }
      }
      else
      {
        hoveredAction = 2;
      }
    }
    else
    {
      hoveredAction = 1;
    }
  }
  else
  {
    hoveredAction = 0;
  }
  if ( hoveredAction != g_UnitActionTooltipLastShownAction && (g_UnitBattleExitButtonState & 4) == 0 )
  {
    g_UnitActionTooltipLastShownAction = hoveredAction;
    if ( hoveredAction == -1 )
    {
      LOWORD(hoveredAction) = UnitBattle_DrawSelectedUnitPanel(0, 1, a2, a3);
    }
    else
    {
      Tooltip_ShowText(3, (&g_UnitActionTooltipTexts[3 * hoveredAction])[(unsigned __int8)g_LanguageIndex], a1);
      LOWORD(hoveredAction) = RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, g_ActiveCursorDescriptor);
    }
  }
  return hoveredAction;
}
// 511130: using guessed type char g_LanguageIndex;
// 514C89: using guessed type char byte_514C89;
// 514DC8: using guessed type char *off_514DC8[24];
// 514E28: using guessed type int dword_514E28;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (0042E3C0) --------------------------------------------------------
signed int  UnitBattle_RunTurnLoop(int a1, DWORD phaseFlag)
{
  int slotIndex; // edx
  int unitRecord; // eax
  int v4; // ebx
  DWORD loopExitCode; // ebp
  int v6; // ecx
  int bannerTexts[9]; // [esp+0h] [ebp-24h] BYREF

  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, (int)phaseFlag);
  g_SelectedUnitIndex = *(_DWORD *)(uintptr_t)(g_MapData + 4 * g_CurrentPlayerIndex + 3944);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_restore_selected", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  Diagnostics_TraceBattleUnitSnapshot("turn_loop_after_restore_selected");
  if ( *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852) == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_selected_empty", g_SelectedUnitIndex, *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852), 0, 0);
    slotIndex = g_SelectedUnitIndex + 1;
    if ( g_SelectedUnitIndex + 1 != g_SelectedUnitIndex )
    {
      a1 = g_SelectedUnitIndex;
      do
      {
        unitRecord = g_MapData + 31 * slotIndex;
        if ( *(__int16 *)(uintptr_t)(unitRecord + 852) != -1 && *(unsigned __int8 *)(uintptr_t)(unitRecord + 854) == g_CurrentPlayerIndex )
          break;
        slotIndex = (slotIndex + 1) % 22;
      }
      while ( slotIndex != g_SelectedUnitIndex );
    }
    g_SelectedUnitIndex = slotIndex;
    Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_find_selected", g_SelectedUnitIndex, a1, *(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852), 0);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_before_action_buttons", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  UnitBattle_RefreshSelectedActionButtons();
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_action_buttons", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  *(_DWORD *)(uintptr_t)(g_MapData + 808) = *(unsigned __int8 *)(uintptr_t)(g_MapData + 2 * g_CurrentPlayerIndex + 3934);
  *(_DWORD *)(uintptr_t)(g_MapData + 812) = *(unsigned __int8 *)(uintptr_t)(g_MapData + 2 * g_CurrentPlayerIndex + 3935);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_before_grid", g_SelectedUnitIndex, *(_DWORD *)(uintptr_t)(g_MapData + 808), *(_DWORD *)(uintptr_t)(g_MapData + 812), 0);
  UnitBattle_RedrawVisibleGrid();
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_grid", g_SelectedUnitIndex, *(_DWORD *)(uintptr_t)(g_MapData + 808), *(_DWORD *)(uintptr_t)(g_MapData + 812), 0);
  UnitBattle_DrawSelectedUnitPanel(0, 1, a1, (int)(intptr_t)bannerTexts);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_panel", g_SelectedUnitIndex, a1, (int)(uintptr_t)bannerTexts, 0);
  bannerTexts[0] = (int)(intptr_t)g_BattleYourTurnBannerTexts[0];
  bannerTexts[1] = (int)(intptr_t)g_BattleYourTurnBannerTexts[1];
  bannerTexts[2] = (int)(intptr_t)g_BattleYourTurnBannerTexts[2];
  v4 = 1;
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_before_banner", g_SelectedUnitIndex, g_CurrentPlayerIndex, bannerTexts[(unsigned __int8)g_LanguageIndex], (int)phaseFlag);
  UnitBattle_ShowPlayerMessageBanner(bannerTexts[(unsigned __int8)g_LanguageIndex], g_CurrentPlayerIndex, 1, phaseFlag);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_banner", g_SelectedUnitIndex, g_CurrentPlayerIndex, g_BattleLoopExitCode, 0);
  loopExitCode = g_BattleLoopExitCode;
  g_UnitBattleActionLoopExitRequested = 0;
  Diagnostics_PrimeBattleSafeCursorOnTurnLoop();
  if ( !g_BattleLoopExitCode )
  {
    while ( !g_UnitBattleActionLoopExitRequested )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_iter_top", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, (int)loopExitCode);
      UnitBattle_UpdateActionTooltip(0, v4, 0);
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_tooltip", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_UpdateIdleAnimatedUnits();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_idle_anim", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      Battle_RunInputScriptStep();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_input_script", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      DD_Pump((int)(intptr_t)g_RenderState, v4);
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_pump", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_HandleBattlefieldInteraction();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_interaction", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_UpdateViewportFromInputAndGetHoveredSlot(v6);
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_hover", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_HandleManualRotateAndMoveInput();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_input_widgets", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      if ( UIWidgetTable_PollHoverAndActions((_DWORD*)(g_UnitBattleActionWidgetTable), loopExitCode) == 1 )
      {
        v4 = (int)(uintptr_t)UnitType_GetLocalizedName(
          (unit_type)*(__int16 *)(uintptr_t)(g_MapData + 31 * g_SelectedUnitIndex + 852));
        Tooltip_ShowText(3, (char *)(uintptr_t)v4, bannerTexts[0]);
      }
      if ( !Battle_HasUnitsForBothSides() )
      {
        g_BattleLoopExitCode = 1;
        return 1;
      }
      if ( g_BattleLoopExitCode )
        return g_BattleLoopExitCode;
    }
  }
  return g_BattleLoopExitCode;
}
// 42E4F2: variable 'v6' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 514B78: using guessed type _DWORD dword_514B78[2];
// 514E2C: using guessed type char *off_514E2C[6];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 532048: using guessed type int g_MapData;
// 532064: using guessed type int g_BattleLoopExitCode;
// 532068: using guessed type int g_UnitBattleActionLoopExitRequested;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042E5A0) --------------------------------------------------------
void  HandleBattleResults(
        int attackerFormation,
        int defenderFormation,
        int a3,
        unsigned __int8 *buildingRecord,
        DWORD battleOutcome)
{
  _WORD *attackerSentinelPtr; // edx
  int i; // eax
  _WORD *defenderSentinelPtr; // edx
  int j; // eax
  char *attackerDest; // eax
  unsigned __int8 *defenderDest; // ebx
  int k; // edx
  int v12; // ecx
  int unitRecord; // esi
  char *destRecord; // edi
  char *srcRecord; // esi
  char *destTail; // edi
  char *srcTail; // esi
  int sentinelIndex; // eax
  _WORD *buildingSentinelPtr; // edx

  Debug_Log(a3, attackerFormation, battleOutcome, (int)(intptr_t)aHandlebattlere);
  Battle_RestoreSavedActionPointsBeforeResultCopy();
  attackerSentinelPtr = (_WORD *)(uintptr_t)(attackerFormation + 6);
  for ( i = 0; i < 10; ++i )
  {
    *attackerSentinelPtr = -1;
    attackerSentinelPtr = (_WORD *)((char *)attackerSentinelPtr + 31);
  }
  if ( defenderFormation )
  {
    defenderSentinelPtr = (_WORD *)(uintptr_t)(defenderFormation + 6);
    for ( j = 0; j < 10; ++j )
    {
      *defenderSentinelPtr = -1;
      defenderSentinelPtr = (_WORD *)((char *)defenderSentinelPtr + 31);
    }
  }
  else
  {
    sentinelIndex = 0;
    buildingSentinelPtr = (_WORD*)(buildingRecord + 18);
    do
    {
      ++sentinelIndex;
      *buildingSentinelPtr = -1;
      buildingSentinelPtr = (_WORD *)((char *)buildingSentinelPtr + 31);
    }
    while ( sentinelIndex < 12 );
  }
  attackerDest = (char *)(uintptr_t)(attackerFormation + 6);
  if ( defenderFormation )
    defenderDest = (unsigned __int8 *)(uintptr_t)(defenderFormation + 6);
  else
    defenderDest = buildingRecord + 18;
  for ( k = 0; k != 682; k += 31 )
  {
    v12 = g_MapData;
    unitRecord = k + g_MapData;
    if ( *(__int16 *)(uintptr_t)(k + g_MapData + 852) != -1 )
    {
      if ( *(unsigned __int8 *)(uintptr_t)(unitRecord + 854) == *(_DWORD *)(uintptr_t)(g_MapData + 836) )
      {
        destRecord = attackerDest;
        srcRecord = (char *)(uintptr_t)(unitRecord + 852);
        attackerDest += 31;
      }
      else
      {
        destRecord = (char *)defenderDest;
        srcRecord = (char *)(uintptr_t)(unitRecord + 852);
        defenderDest += 31;
      }
      qmemcpy(destRecord, srcRecord, 0x1Cu);
      srcTail = srcRecord + 28;
      destTail = destRecord + 28;
      v12 = 0;
      *(_WORD *)destTail = *(_WORD *)srcTail;
      destTail[2] = srcTail[2];
    }
  }
  Debug_Log(v12, (char)(intptr_t)defenderDest, battleOutcome, (int)(intptr_t)aHandlebattle_0);
  Unit_DebugDumpFormationSizes(attackerFormation, battleOutcome);
  if ( defenderFormation )
    Unit_DebugDumpFormationSizes(defenderFormation, battleOutcome);
  else
    Building_DebugDump(buildingRecord, (char)(intptr_t)defenderDest, battleOutcome);
}
// 42E5D1: variable 'v5' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042E6F0) --------------------------------------------------------
int UnitBattle_TemporarilyClearGateBlocker(void)
{
  int result; // eax
  char gateBlockerCost; // bl

  if ( *(_DWORD *)(uintptr_t)(g_MapData + 828) != -1 )
  {
    result = *(_DWORD *)(uintptr_t)(g_MapData + 828) + g_MapData + 20 * *(_DWORD *)(uintptr_t)(g_MapData + 824);
    gateBlockerCost = *(_BYTE *)(uintptr_t)(result + 3134);
    if ( gateBlockerCost )
    {
      *(_DWORD *)(uintptr_t)(g_MapData + 832) = gateBlockerCost;
      result = *(_DWORD *)(uintptr_t)(g_MapData + 828) + g_MapData + 20 * *(_DWORD *)(uintptr_t)(g_MapData + 824);
      *(_BYTE *)(uintptr_t)(result + 3134) = 0;
    }
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042E770) --------------------------------------------------------
char UnitBattle_RestoreGateBlocker(void)
{
  char result; // al

  if ( *(_DWORD *)(uintptr_t)(g_MapData + 828) != -1 )
  {
    result = *(_BYTE *)(uintptr_t)(g_MapData + 832);
    *(_BYTE *)(uintptr_t)(g_MapData + 20 * *(_DWORD *)(uintptr_t)(g_MapData + 824) + *(_DWORD *)(uintptr_t)(g_MapData + 828) + 3134) = result;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042E7C0) --------------------------------------------------------
int  UnitBattle_OverrideControllerOrderBits(int playerAIndex, int overrideA, int overrideB, int playerBIndex)
{
  int backupIndex; // edx
  int result; // eax
  int mapData; // ecx

  backupIndex = 0;
  result = 0;
  do
  {
    mapData = g_MapData;
    *(_DWORD *)&g_BattleUnitOrderBitsBackup[backupIndex] = *(_BYTE *)(uintptr_t)(g_MapData + result + 864) & 3;
    if ( *(unsigned __int8 *)(uintptr_t)(mapData + result + 854) == playerAIndex && overrideA
      || *(unsigned __int8 *)(uintptr_t)(g_MapData + result + 854) == playerBIndex && overrideB )
    {
      *(_BYTE *)(uintptr_t)(g_MapData + result + 864) |= 3u;
    }
    backupIndex += 4;
    result += 31;
  }
  while ( backupIndex != 88 );
  return result;
}
// 42E7C0: could not find valid save-restore pair for ebx
// 532048: using guessed type int g_MapData;

//----- (0042E860) --------------------------------------------------------
int UnitBattle_RestoreControllerOrderBits(void)
{
  int backupIndex; // edx
  int recordOffset; // ecx
  int result; // eax
  char savedOrderBits; // bl
  char currentBits; // bh

  backupIndex = 0;
  recordOffset = 0;
  do
  {
    result = g_MapData;
    savedOrderBits = g_BattleUnitOrderBitsBackup[backupIndex] & 3;
    currentBits = *(_BYTE *)(uintptr_t)(recordOffset + g_MapData + 864);
    recordOffset += 31;
    currentBits &= 0xFCu;
    *(_BYTE *)(uintptr_t)(recordOffset + g_MapData + 833) = currentBits;
    backupIndex += 4;
    *(_BYTE *)(uintptr_t)(recordOffset + result + 833) = savedOrderBits | currentBits;
  }
  while ( backupIndex != 88 );
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042E8B0) --------------------------------------------------------
int *UnitBattle_InitBattleScreenFrame(void)
{
  void *v0; // edx
  int SpriteForChar; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // edx

  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  g_RenderDevice = (_UNKNOWN*)(v0);
  SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 0);
  Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  v2 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 1);
  Compat_RenderDeviceDrawMenuSprite(0, 0, v2, 1);
  v3 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 2);
  Compat_RenderDeviceDrawMenuSprite(243, 0, v3, 1);
  v4 = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 3);
  v5 = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(243, 0, v4, 1);
  UIWidgetTable_InitDrawStates((_DWORD*)(g_UnitBattleActionWidgetTable));
  UnitBattle_DrawSelectedUnitPanel(0, v6, 20, v5);
  UnitBattle_RedrawVisibleGrid();
  return Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr, 20);
}
// 42E8C9: variable 'v0' is possibly undefined
// 42E9B6: variable 'v6' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514B78: using guessed type _DWORD dword_514B78[2];
// 5202BC: using guessed type int dword_5202BC;
// 5202F4: using guessed type int dword_5202F4;
