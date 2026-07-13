/* Tactical battle interaction, simulation, rendering, and outcomes.
 * Original function-marker range: 0x0042CB50..0x00433820.
 * Included by clash95.c; not a standalone translation unit. */

//----- (0042CB50) --------------------------------------------------------
__int16 UnitBattle_HandleBattlefieldInteraction()
{
  DWORD v0; // ebp
  unsigned int v1; // eax
  DWORD v2; // esi
  int v3; // edi
  int v4; // ecx
  int v5; // ebp
  int v6; // edx
  void *v7; // ecx
  int v8; // ebx
  int v9; // esi
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v19; // ecx
  int *v20; // ecx
  int *v21; // eax
  __int16 v22; // bx
  int v23; // ecx
  void (*v24)(void); // edx
  int v26; // [esp+0h] [ebp-20h]

  v7 = &g_CursorDesc_Default;
  v0 = ((dword_544CFC >> byte_54512C)
      - 32
      - (__CFSHL__(((dword_544CFC >> byte_54512C) - 32) >> 31, 6)
       + (((dword_544CFC >> byte_54512C) - 32) >> 31 << 6))) >> 6;
  v1 = ((dword_544D00 >> byte_54512C)
      - 16
      - (__CFSHL__(((dword_544D00 >> byte_54512C) - 16) >> 31, 6)
       + (((dword_544D00 >> byte_54512C) - 16) >> 31 << 6))) >> 6;
  v2 = v0 + *(_DWORD *)(g_MapData + 808);
  v3 = v1 + *(_DWORD *)(g_MapData + 812);
  if ( v0 <= 6 && v1 <= 6 )
  {
    if ( DD_IsLost((int)g_RenderState) )
    {
      v4 = *(__int16 *)(g_MapData + 40 * v2 + 2 * v3 + 1534);
      if ( v4 == -1 )
      {
        if ( *(_BYTE *)(v3 + 20 * v2 + g_MapData + 3134) )
          UnitBattle_ShowWallInfoPopup(100, 100, v3, v2, v0);
      }
      else
      {
        Unit_Info(100, 100, 0, (unsigned __int8 *)(g_MapData + 852 + 31 * v4), v0, 0);
      }
    }
    v5 = *(__int16 *)(g_MapData + 40 * v2 + 2 * v3 + 1534);
    if ( DD_IsLost((int)g_RenderState) || DD_IsFlipping((int)g_RenderState) )
      Diagnostics_TraceBattlefieldClickEvent("tile_input", v0, v1, v2, v3, v5);
    if ( v5 == -1 || *(unsigned __int8 *)(31 * v5 + g_MapData + 854) != g_CurrentPlayerIndex )
    {
      if ( !dword_53205C || v5 == -1 || *(unsigned __int8 *)(g_MapData + 31 * v5 + 854) == g_CurrentPlayerIndex )
      {
        if ( v5 == -1 || *(_WORD *)(31 * g_SelectedUnitIndex + g_MapData + 852) == UNIT_TYPE_RAM )
        {
          if ( *(_BYTE *)(g_MapData + 20 * v2 + v3 + 3134) )
          {
            if ( dword_53205C )
            {
              if ( UnitBattle_IsTileWithinRange(g_SelectedUnitIndex, v2, v3)
                && (v17 = g_MapData + 31 * g_SelectedUnitIndex, *(unsigned __int8 *)(v17 + 860) >= 5u)
                && (unsigned __int8)(2 * *(_BYTE *)(v17 + 864)) >> 5 < (*(_BYTE *)(v17 + 864) & 3) + 1 )
              {
                if ( DD_IsFlipping((int)g_RenderState) )
                {
                  Audio_PlayUnitMoveOrderSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
                  dword_5437A4 = v3;
                  Diagnostics_TraceWorldMapActionEvent("battle_wall_shot_enter", g_SelectedUnitIndex, v2, v3, 0);
                  UnitBattle_ShotWall(g_SelectedUnitIndex, v2);
                  Diagnostics_TraceWorldMapActionEvent("battle_wall_shot_return", g_SelectedUnitIndex, v2, v3, 0);
                  Render_Begin((int)g_RenderState, 0);
                }
              }
              else
              {
                v7 = &g_CursorDesc_Blocked;
              }
            }
            else
            {
              v14 = *(unsigned __int16 *)(31 * g_SelectedUnitIndex + g_MapData + 856) - v2;
              if ( v14 <= 0 )
                v14 = v2 - *(unsigned __int16 *)(31 * g_SelectedUnitIndex + g_MapData + 856);
              if ( v14 != 1 || *(unsigned __int16 *)(31 * g_SelectedUnitIndex + g_MapData + 858) != v3 )
              {
                BattleLog_Disable();
                Diagnostics_TraceWorldMapActionEvent("battle_wall_move_track_enter", g_SelectedUnitIndex, v2, v3, v5);
                v20 = UnitBattle_MoveTrackNearWall(g_SelectedUnitIndex, v2, v3, v5);
                Diagnostics_TraceWorldMapActionEvent("battle_wall_move_track_return", g_SelectedUnitIndex, v2, v3, v5);
                BattleLog_Enable();
                if ( v20 )
                {
                  v26 = v20[1];
                  if ( HIWORD(v26) + 5 <= (int)*(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860) )
                    v7 = &g_CursorDesc_Attack;
                  else
                    v7 = &g_CursorDesc_Blocked;
                  nfree_((int)(uintptr_t)v20);
                }
                else
                {
                  v26 = 1000 << 16;
                  v7 = &g_CursorDesc_Blocked;
                }
              }
              else
              {
                v26 = 0;
                if ( *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860) >= 5u )
                  v7 = &g_CursorDesc_Attack;
                else
                  v7 = &g_CursorDesc_Blocked;
              }
              Diagnostics_TraceWorldMapActionEvent(
                "battle_wall_selected_state",
                g_SelectedUnitIndex,
                *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852),
                (*(unsigned __int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 856) << 8)
                  | *(unsigned __int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 858),
                *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 864));
              Diagnostics_TraceWorldMapActionEvent(
                "battle_wall_move_track_cost",
                g_SelectedUnitIndex,
                HIWORD(v26),
                *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860),
                v5);
              if ( DD_IsFlipping((int)g_RenderState) && v7 == &g_CursorDesc_Attack )
              {
                Audio_PlayUnitMoveOrderSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
                Diagnostics_TraceWorldMapActionEvent("battle_wall_attack_enter", g_SelectedUnitIndex, v2, v3, 0);
                UnitBattle_AttackWall(g_SelectedUnitIndex, v2, 0, v3);
                Diagnostics_TraceWorldMapActionEvent("battle_wall_attack_return", g_SelectedUnitIndex, v2, v3, 0);
                Render_Begin((int)g_RenderState, 0);
              }
            }
          }
          else
          {
            BattleLog_Disable();
            Diagnostics_TraceWorldMapActionEvent("battle_move_track_enter", g_SelectedUnitIndex, v2, v3, v5);
            v20 = UnitBattle_MoveTrack(g_SelectedUnitIndex, v2, v2, v3, v5);
            Diagnostics_TraceWorldMapActionEvent("battle_move_track_return", g_SelectedUnitIndex, v2, v3, v5);
            BattleLog_Enable();
            if ( v20 )
            {
              v26 = v20[1];
              nfree_((int)(uintptr_t)v20);
            }
            else
            {
              v26 = 1000 << 16;
            }
            Diagnostics_TraceWorldMapActionEvent(
              "battle_move_track_cost",
              g_SelectedUnitIndex,
              HIWORD(v26),
              *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860),
              v5);
            if ( HIWORD(v26) <= (int)*(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860) )
            {
              if ( DD_IsFlipping((int)g_RenderState) )
              {
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_track_enter", g_SelectedUnitIndex, v2, v3, v5);
                v21 = UnitBattle_MoveTrack(g_SelectedUnitIndex, v2, v2, v3, v5);
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_track_return", g_SelectedUnitIndex, v2, v3, v5);
                v22 = g_MapData;
                *(_DWORD *)(31 * g_SelectedUnitIndex + g_MapData + 875) = v21;
                Audio_PlayUnitMoveOrderSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_enter", g_SelectedUnitIndex, v2, v3, v5);
                UnitBattle_Move(g_SelectedUnitIndex, 0, 0, 0);
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_return", g_SelectedUnitIndex, v2, v3, v5);
                Render_Begin((int)g_RenderState, 0);
              }
              else
              {
                Diagnostics_TraceWorldMapActionEvent("battle_move_execute_no_flip", g_SelectedUnitIndex, v2, v3, v5);
              }
            }
            else
            {
              v7 = &g_CursorDesc_Blocked;
              Diagnostics_TraceWorldMapActionEvent("battle_move_insufficient_ap", g_SelectedUnitIndex, HIWORD(v26), *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860), v5);
            }
          }
          goto LABEL_13;
        }
        if ( DD_IsLost((int)g_RenderState) )
          Unit_Info(100, 100, 0, (unsigned __int8 *)(g_MapData + 852 + 31 * v5), v5, 0);
        BattleLog_Disable();
        v20 = UnitBattle_MoveTrackNear(g_SelectedUnitIndex, v2, v3, v5);
        BattleLog_Enable();
        if ( v20 )
        {
          v26 = v20[0] ? v20[1] : 0;
          if ( HIWORD(v26) + 5 <= (int)*(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860) )
            v7 = &g_CursorDesc_Attack;
          else
            v7 = &g_CursorDesc_Blocked;
          nfree_((int)(uintptr_t)v20);
          if ( DD_IsFlipping((int)g_RenderState) && v7 == &g_CursorDesc_Attack )
          {
            UnitBattle_Attack(g_SelectedUnitIndex, v5, dword_532060);
            if ( *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852) == -1 )
              UnitBattle_SelectNextControllableUnit(0, v12, v3);
            Render_Begin((int)g_RenderState, 0);
          }
          goto LABEL_13;
        }
      }
      else if ( UnitBattle_IsUnitWithinRange(g_SelectedUnitIndex, v5) )
      {
        v13 = g_MapData + 31 * g_SelectedUnitIndex;
        if ( *(unsigned __int8 *)(v13 + 860) >= 5u
          && (unsigned __int8)(2 * *(_BYTE *)(v13 + 864)) >> 5 < (*(_BYTE *)(v13 + 864) & 3) + 1 )
        {
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            UnitBattle_Shot(v7, v5);
            Render_Begin((int)g_RenderState, 0);
          }
          goto LABEL_13;
        }
      }
      v7 = &g_CursorDesc_Blocked;
    }
    else if ( DD_IsFlipping((int)g_RenderState) )
    {
      v8 = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(v6 + g_MapData + 854) == g_CurrentPlayerIndex )
      {
        v9 = g_SelectedUnitIndex;
        if ( v5 != g_SelectedUnitIndex )
        {
          g_SelectedUnitIndex = v5;
          UnitBattle_RefreshSelectedActionButtons();
          UnitBattle_RedrawUnitFootprint(v9);
          UnitBattle_RedrawUnitFootprint(v5);
          UnitBattle_DrawSelectedUnitPanel(0, 1, v8, v3);
          Audio_PlayUnitActivateSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
        }
      }
    }
LABEL_13:
    LOWORD(v1) = RenderState_SelectCursorDescriptor((int)g_RenderState, (int)v7);
  }
  return v1;
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
__int16 UnitBattle_EnableSelectedChargeMode()
{
  dword_532060 = 1;
  dword_532074 = Time_Now(2, 1);
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
__int16 UnitBattle_RefreshSelectedUnitUI()
{
  dword_532060 = 0;
  g_UnitBattleChargeButtonState = 1;
  UIWidget_RefreshActionButtonState((int)&g_UnitBattleChargeButtonWidget, 1);
  return UnitBattle_RedrawUnitFootprint(g_SelectedUnitIndex);
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514BEA: using guessed type int dword_514BEA;
// 532060: using guessed type int dword_532060;

//----- (0042D2C0) --------------------------------------------------------
int UnitBattle_RefreshSelectedActionButtons()
{
  void *v0; // ebx
  int result; // eax
  int selected_type_offset;

  v0 = g_RenderDevice;
  g_RenderDevice = &unk_51D4C0;
  if ( dword_532060 )
    UnitBattle_RefreshSelectedUnitUI();
  selected_type_offset = 88 * *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  if ( !g_UnitTypeMaxRange_512582[selected_type_offset] )
  {
    dword_53205C = 0;
    g_UnitBattleShootButtonState = 1;
    goto LABEL_6;
  }
  if ( !g_UnitTypeBaseMeleeAttack_51257E[selected_type_offset] )
  {
    g_UnitBattleShootButtonState = 2;
    dword_53205C = 1;
LABEL_6:
    result = UIWidget_RefreshActionButtonState((uintptr_t)&g_UnitBattleActionWidgetTable, 1);
    g_RenderDevice = v0;
    return result;
  }
  dword_53205C = 1;
  g_UnitBattleShootButtonState = 2;
  result = UIWidget_RefreshActionButtonState((uintptr_t)&g_UnitBattleActionWidgetTable, 1);
  g_RenderDevice = v0;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514B80: using guessed type int dword_514B80;
// 532048: using guessed type int g_MapData;
// 53205C: using guessed type int dword_53205C;
// 532060: using guessed type int dword_532060;

//----- (0042D3A0) --------------------------------------------------------
int  UnitBattle_SelectNextControllableUnit(int a1, int a2, char a3)
{
  int i; // ecx
  int v4; // edx
  int v5; // ebx
  int v6; // ecx
  int v7; // edx
  int result; // eax

  Diagnostics_TraceWorldMapActionEvent("battle_action_next_unit_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, a2);
  if ( a1 )
    UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  for ( i = (g_SelectedUnitIndex + 1) % 22; i != g_SelectedUnitIndex; i = (i + 1) % 22 )
  {
    v4 = 31 * i + g_MapData;
    if ( *(__int16 *)(v4 + 852) != -1 && *(unsigned __int8 *)(v4 + 854) == g_CurrentPlayerIndex )
      break;
  }
  v5 = g_MapData;
  g_SelectedUnitIndex = i;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_action_next_unit_selected",
    g_SelectedUnitIndex,
    *(unsigned __int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 856),
    *(unsigned __int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 858),
    0);
  if ( !UnitBattle_IsTileInViewport(
          *(unsigned __int16 *)(g_MapData + 31 * i + 856),
          *(unsigned __int16 *)(g_MapData + 31 * i + 858)) )
    UnitBattle_CenterViewOnUnit(i);
  UnitBattle_RefreshSelectedActionButtons();
  UnitBattle_RedrawVisibleGrid();
  UnitBattle_DrawSelectedUnitPanel(0, 1, v5, a3);
  v7 = g_MapData + 31 * g_SelectedUnitIndex;
  result = *(__int16 *)(v7 + 852);
  if ( result != -1 )
  {
    if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(v7 + 854) + 140051) )
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

  Diagnostics_TraceWorldMapActionEvent("battle_action_shoot_toggle_enter", g_SelectedUnitIndex, dword_53205C, (int)widget, 0);
  type_offset = 88 * *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  result = (unsigned __int8)g_UnitTypeBaseMeleeAttack_51257E[type_offset];
  if ( g_UnitTypeBaseMeleeAttack_51257E[type_offset] )
  {
    result = (unsigned __int8)g_UnitTypeMaxRange_512582[type_offset];
    if ( g_UnitTypeMaxRange_512582[type_offset] )
    {
      result = Render_Begin((int)g_RenderState, 0);
      LOBYTE(dword_53205C) = dword_53205C ^ 1;
      if ( dword_53205C )
      {
        if ( widget )
          *(_DWORD *)(widget + 8) = 2;
        if ( dword_532060 )
          result = UnitBattle_RefreshSelectedUnitUI();
      }
      else
      {
        if ( widget )
          *(_DWORD *)(widget + 8) = 1;
      }
      Diagnostics_TraceWorldMapActionEvent("battle_action_shoot_toggle_done", g_SelectedUnitIndex, dword_53205C, result, 0);
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
int  UnitBattle_HandleRetreatAction(int a1, int a2, char a3, DWORD a4)
{
  int result; // eax
  _DWORD v6[4]; // [esp+0h] [ebp-10h] BYREF

  UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  result = g_MapData;
  if ( g_CurrentPlayerIndex != *(_DWORD *)(g_MapData + 840) || *(_DWORD *)(g_MapData + 848) )
  {
    v6[0] = g_UnitBattleRetreatMessageStrings[0];
    v6[1] = g_UnitBattleRetreatMessageStrings[1];
    v6[2] = g_UnitBattleRetreatMessageStrings[2];
    result = UnitBattle_ShowCurrentPlayerPromptDialog((int)v6, a3, a4);
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

  Diagnostics_TraceWorldMapActionEvent("battle_action_charge_toggle_enter", g_SelectedUnitIndex, dword_532060, (int)widget, 0);
  type_offset = 88 * *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852);
  result = (unsigned __int8)g_UnitTypeBaseMeleeAttack_51257E[type_offset];
  if ( g_UnitTypeBaseMeleeAttack_51257E[type_offset] )
  {
    Render_Begin((int)g_RenderState, 0);
    LOBYTE(dword_532060) = dword_532060 ^ 1;
    dword_532074 = Time_Now(0, 0);
    result = UnitBattle_RedrawUnitNeighborhood(g_SelectedUnitIndex);
    if ( dword_532060 )
    {
      result = Audio_PlaySoundEffectByName(aBattleSzarza, 64);
      if ( widget )
        *(_DWORD *)(widget + 8) = 2;
      if ( dword_53205C )
      {
        dword_53205C = 0;
        g_UnitBattleShootButtonState = 1;
        return UIWidget_RefreshActionButtonState((uintptr_t)g_UnitBattleActionWidgetTable, 1);
      }
    }
    else
    {
      if ( widget )
        *(_DWORD *)(widget + 8) = 1;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_action_charge_toggle_done", g_SelectedUnitIndex, dword_532060, result, 0);
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
int  UnitBattle_HandlePrepareDefenceAction(int a1, int a2, DWORD a3, char a4, char a5)
{
  int v6; // ebx
  int result; // eax
  int v8; // ecx
  int v9[6]; // [esp+0h] [ebp-18h]

  Diagnostics_TraceWorldMapActionEvent("battle_action_prepare_defence_enter", g_SelectedUnitIndex, a1, a2, 0);
  v9[4] = a2;
  v6 = g_MapData;
  result = 31 * g_SelectedUnitIndex;
  if ( (*(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 874) & 1) == 0 )
  {
    UIWidget_PlayPressedReleaseAnimationWithDelay(a1, g_SelectedUnitIndex);
    if ( !UnitBattle_Defence(g_SelectedUnitIndex, 0, a3) )
    {
      v9[0] = (int)g_UnitBattlePrepareDefenceMessageStrings[0];
      v9[1] = (int)g_UnitBattlePrepareDefenceMessageStrings[1];
      v9[2] = (int)g_UnitBattlePrepareDefenceMessageStrings[2];
      Tooltip_ShowText(3, (char *)v9[(unsigned __int8)g_LanguageIndex], a5);
    }
    UnitBattle_RedrawVisibleGrid();
    Diagnostics_TraceWorldMapActionEvent(
      "battle_action_prepare_defence_done",
      g_SelectedUnitIndex,
      *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 860),
      *(unsigned __int8 *)(g_MapData + 31 * g_SelectedUnitIndex + 864),
      0);
    return UnitBattle_DrawSelectedUnitPanel(0, 1, v6, a4);
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
  Render_Begin((int)g_RenderState, 0);
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
int  UnitBattle_ShowPlayerMessageBanner(int a1, int a2, int a3, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  _DWORD *v6; // eax
  void *v7; // ecx
  int v8; // ecx
  _DWORD *Surface; // eax
  DWORD v10; // ebp
  int SpriteForChar; // eax
  int v12; // edi
  int v13; // edx
  int v14; // ebx
  int v15; // esi
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v21[3]; // [esp+1Ch] [ebp-48h]
  int v22[2]; // [esp+28h] [ebp-3Ch] BYREF
  int (*v23)(); // [esp+30h] [ebp-34h]
  int v24; // [esp+34h] [ebp-30h]
  int v25; // [esp+38h] [ebp-2Ch]
  int v26; // [esp+3Ch] [ebp-28h]
  int v27; // [esp+40h] [ebp-24h]
  int v28; // [esp+44h] [ebp-20h]
  int v29; // [esp+48h] [ebp-1Ch]
  void *v30; // [esp+4Ch] [ebp-18h]
  int v31; // [esp+50h] [ebp-14h]
  int flip_wait_pumps;

  v29 = a1;
  v27 = a2;
  v22[1] = a3;
  Diagnostics_TraceWorldMapActionEvent("battle_banner_enter", a1, a2, a3, (int)a4);
  v24 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v23 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v4, a3, a4, (int)aSetrhS08x_9);
  Render_Pump();
  v6 = (_DWORD *)Mem_Alloc(4112, v5, a3, a4);
  if ( v6 )
    v6 = DLXSpriteSet_Load(v6, "okno1.s32");
  v22[0] = (int)v6;
  Render_ReleaseSurface(8, a4);
  Render_ReleaseSurface(7, a4);
  v30 = g_RenderDevice;
  g_RenderDevice = &unk_51D4C0;
  v31 = (448 - (unsigned __int16)DLX_GetSpriteHeight(v22[0], 0)) / 2 + 32;
  v28 = (480 - (unsigned __int16)DLX_GetSpriteWidth(v22[0], 0)) / 2;
  v26 = v31 + (unsigned __int16)DLX_GetSpriteHeight(v22[0], 0) - 1;
  v25 = v28 + (unsigned __int16)DLX_GetSpriteWidth(v22[0], 0) - 1;
  Surface = (_DWORD *)Mem_Alloc(188, v8, v31, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, v26 - v31 + 1, v25 - v28 + 1);
  v10 = (DWORD)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)v28, (unsigned __int16)v31, v26, v25, 0, 0);
  SpriteForChar = DLX_GetSpriteForChar(v22[0], v27);
  Compat_RenderDeviceDrawMenuSprite(v28, v31, SpriteForChar, 1);
  Render_ReleaseSurface(7, v10);
  v21[0] = (int)g_UnitBattlePlayerLabelStrings[0];
  v21[1] = (int)g_UnitBattlePlayerLabelStrings[1];
  v21[2] = (int)g_UnitBattlePlayerLabelStrings[2];
  v12 = v21[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(v12, v31, v26, v28 + 40, 3, v12);
  Render_ReleaseSurface(8, v10);
  v14 = v26;
  v15 = v31;
  UI_DrawTextFmt(v12, v31, v26, v28 + 55, 3, PLAYER_DATA(v27) + PLAYER_DISPLAY_NAME_OFFSET);
  UI_DrawTextFmt(v29, v15, v14, v28 + 100, 3, v29);
  Render_Present((int)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent("battle_banner_after_present", a1, a2, v22[1], v10);
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  if ( v22[1] )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_banner_before_flip_wait", a1, a2, DD_IsFlipping((int)g_RenderState), v10);
    Render_Begin((int)g_RenderState, 0);
    flip_wait_pumps = 0;
    while ( !DD_IsFlipping((int)g_RenderState) && flip_wait_pumps < 8 )
    {
      DD_Pump((int)g_RenderState, 0);
      ++flip_wait_pumps;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_banner_after_flip_wait", a1, a2, DD_IsFlipping((int)g_RenderState), flip_wait_pumps);
    if ( v10 )
    {
      if ( DD_IsFlipping((int)g_RenderState) )
        Render_Begin((int)g_RenderState, 0);
      Render_Pump();
      Render_FillRect((_DWORD *)v10, 0, 0, 0, v26 - v31, v25 - v28, v31, v28);
      Diagnostics_TraceWorldMapActionEvent("battle_banner_after_restore", a1, a2, v10, 0);
    }
  }
  Compat_InvokeCompactSurfaceDestructor(v10, 2);
  Diagnostics_TraceWorldMapActionEvent("battle_banner_after_surface_release", a1, a2, v10, 0);
  RenderState_WarpCursorAndPump(g_RenderState, 0x140u, 0xF0u);
  Debug_Log(v19, (char)g_RenderHook, v10, (int)aUnsetrh08x_8);
  g_RenderHook = v23;
  Render_SetResourceHandle((int)&unk_51D4C0, v24);
  Render_Present((int)g_RenderState);
  g_RenderDevice = v30;
  Diagnostics_TraceWorldMapActionEvent("battle_banner_done", a1, a2, (int)(uintptr_t)g_RenderDevice, 0);
  return DLXSpriteSet_ReleaseAndClear(v22);
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
int  UnitBattleDialog_SelectAffirmativeResponse(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_UnitBattlePromptDialogResult = v4;
  return result;
}
// 42DABB: variable 'v4' is possibly undefined
// 532080: using guessed type int g_UnitBattlePromptDialogResult;

//----- (0042DAD0) --------------------------------------------------------
int  UnitBattleDialog_SelectNegativeResponse(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_UnitBattlePromptDialogResult = v4;
  return result;
}
// 42DAD8: variable 'v4' is possibly undefined
// 532080: using guessed type int g_UnitBattlePromptDialogResult;

//----- (0042DAE0) --------------------------------------------------------
int  UnitBattle_ShowCurrentPlayerPromptDialog(int a1, char a2, DWORD a3)
{
  int v4; // ecx
  _DWORD *v5; // eax
  _DWORD *Surface; // eax
  DWORD v7; // ebp
  int SpriteForChar; // eax
  int v9; // edi
  int v10; // esi
  _DWORD v12[40]; // [esp+0h] [ebp-E0h] BYREF
  int v13[3]; // [esp+A0h] [ebp-40h]
  _DWORD *v14; // [esp+ACh] [ebp-34h] BYREF
  void *v15; // [esp+B0h] [ebp-30h]
  int v16; // [esp+B4h] [ebp-2Ch]
  int v17; // [esp+B8h] [ebp-28h]
  int v18; // [esp+BCh] [ebp-24h]
  int v19; // [esp+C0h] [ebp-20h]
  int v20; // [esp+C4h] [ebp-1Ch]

  v17 = a1;
  Render_Pump();
  v5 = (_DWORD *)Mem_Alloc(4112, v4, a2, a3);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a2);
  v14 = v5;
  Render_ReleaseSurface(8, a3);
  Render_ReleaseSurface(7, a3);
  v15 = g_RenderDevice;
  g_RenderDevice = &unk_51D4C0;
  v18 = (448 - (unsigned __int16)DLX_GetSpriteHeight((int)v14, 0)) / 2 + 32;
  v19 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v14, 0)) / 2;
  v16 = v18 + (unsigned __int16)DLX_GetSpriteHeight((int)v14, 0) - 1;
  v20 = v19 + (unsigned __int16)DLX_GetSpriteWidth((int)v14, 0) - 1;
  qmemcpy(v12, &g_UnitBattlePlayerPromptDialogTemplate, 0x9Fu);
  v12[0] = v18 + 232;
  v12[1] = v19 + 108;
  v12[3] = &v14;
  *(_DWORD *)((char *)&v12[13] + 1) = v18 + 27;
  *(_DWORD *)((char *)&v12[14] + 1) = v19 + 108;
  *(_DWORD *)((char *)&v12[16] + 1) = &v14;
  Surface = (_DWORD *)Mem_Alloc(188, 0, v19, a3);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, v16 - v18 + 1, v20 - v19 + 1);
  v7 = (DWORD)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)v19, (unsigned __int16)v18, v16, v20, 0, 0);
  SpriteForChar = DLX_GetSpriteForChar((int)v14, g_CurrentPlayerIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    v19,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(7, v7);
  v13[0] = (int)g_UnitBattlePlayerPromptLabelStrings[0];
  v13[1] = (int)g_UnitBattlePlayerPromptLabelStrings[1];
  v13[2] = (int)g_UnitBattlePlayerPromptLabelStrings[2];
  v9 = v16;
  UI_DrawTextFmt(v16, v18, v16, v19 + 40, 3, v13[(unsigned __int8)g_LanguageIndex]);
  Render_ReleaseSurface(8, v7);
  v10 = v18;
  UI_DrawTextFmt(v9, v18, v9, v19 + 55, 3, PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_DISPLAY_NAME_OFFSET);
  UI_DrawTextFmt(v17, v10, v9, v19 + 100, 3, *(_DWORD *)(v17 + 4 * (unsigned __int8)g_LanguageIndex));
  UIWidgetTable_InitDrawStates(v12);
  Render_Present((int)g_RenderState);
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  while ( UIWidgetTable_PollHoverAndActions(v12, v7) != 3 )
    DD_Pump((int)g_RenderState, (char)g_RenderState);
  Render_Pump();
  Render_FillRect((_DWORD *)v7, 0, 0, 0, v16 - v18, v20 - v19, v18, v19);
  if ( v7 )
    (**(void (***)(void))(v7 + 184))();
  RenderState_WarpCursorAndPump(g_RenderState, 0x140u, 0xF0u);
  Render_Present((int)g_RenderState);
  g_RenderDevice = v15;
  DLXSpriteSet_ReleaseAndClear((int *)&v14);
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
int  UnitBattle_AnimateSelectedUnitPanel(int a1, int a2, int a3)
{
  int v4; // eax
  char v5; // dl
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  int v9; // edi
  int v10; // ecx
  unsigned int v11; // eax
  unsigned int v12; // edx
  int v13; // esi
  unsigned int v14; // eax
  int v15; // eax
  int v16; // ebx
  int result; // eax
  __int16 SpriteHeight; // ax
  unsigned __int16 v19; // [esp+Ch] [ebp-34h]
  unsigned __int16 v20; // [esp+10h] [ebp-30h]
  unsigned __int16 v21; // [esp+14h] [ebp-2Ch]
  int v22; // [esp+1Ch] [ebp-24h]
  int v23; // [esp+20h] [ebp-20h]
  int i; // [esp+24h] [ebp-1Ch]
  int j; // [esp+24h] [ebp-1Ch]

  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
  UnitBattle_DrawSelectedUnitPanel(g_MapData + 852 + 31 * g_SelectedUnitIndex, 0, a2, a3);
  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_after_panel", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
  Render_Pump();
  g_RenderDevice = &unk_51D4C0;
  for ( i = 0; i < 6; ++i )
  {
    v4 = i;
    byte_532088[i] = i;
    v5 = -(char)i;
    byte_532088[v4] = v5;
  }
  v6 = 31 * g_SelectedUnitIndex + g_MapData;
  v7 = *(_BYTE *)(v6 + 864) & 3;
  g_UnitBattlePanelVolleyIconChar = 9 * v7;
  v8 = *(char *)(v6 + 863);
  if ( (unsigned int)v8 <= 4 )
  {
    g_UnitBattlePanelMoraleIconChar = 72;
  }
  else if ( v8 < 5 || v8 > 10 )
  {
    if ( v8 < 11 || v8 > 15 )
      g_UnitBattlePanelMoraleIconChar = 45;
    else
      g_UnitBattlePanelMoraleIconChar = 54;
  }
  else
  {
    g_UnitBattlePanelMoraleIconChar = 63;
  }
  v9 = 0;
  v23 = Time_Now(0, 0);
  v22 = 0;
  do
  {
    v12 = v23 + 8;
    do
      v11 = Time_Now(0, 0);
    while ( v11 < v12 );
    v23 = Time_Now(0, 0);
    v13 = 0;
    for ( j = 0; j < 6; ++j )
    {
      v14 = byte_532088[j];
      if ( v14 > 8 )
      {
        if ( byte_532088[j] >= 9 && !a1 )
        {
          v21 = g_UnitBattlePanelStatIconY[v13];
          v20 = g_UnitBattlePanelStatIconX[v13];
          v19 = v21 + DLX_GetSpriteWidth(dword_532054, 0) + 1;
          SpriteHeight = DLX_GetSpriteHeight(dword_532054, 0);
          Render_FillRect(
            (_DWORD *)dword_5202E0,
            0,
            (unsigned __int16)g_UnitBattlePanelStatIconY[v13],
            (unsigned __int16)g_UnitBattlePanelStatIconX[v13],
            g_UnitBattlePanelStatIconX[v13] + SpriteHeight + 1,
            v19,
            v20,
            v21);
        }
      }
      else
      {
        if ( !a1 )
          v14 = 8 - v14;
        v9 = DLX_GetSpriteForChar(dword_532054, v14 + (unsigned __int8)g_UnitBattlePanelQuantityIconCharBase[j]);
        Compat_RenderDeviceDrawMenuSprite(-1, -1, v9, 1);
      }
      v15 = j;
      v13 += 2;
      byte_532088[v15] = byte_532088[j] + 1;
    }
    v16 = v22 + 1;
    v22 = v16;
  }
  while ( v16 < 15 );
  result = Render_Present((int)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_after_present", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
  if ( !a1 )
  {
    result = UnitBattle_DrawSelectedUnitPanel(0, 1, v16, v9);
    Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_exit", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, result);
    return result;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_panel_anim_exit", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, result);
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
  int v3; // eax

  if ( dword_544CFC >> byte_54512C < 535
    || dword_544D00 >> byte_54512C < 30
    || dword_544CFC >> byte_54512C > 623
    || dword_544D00 >> byte_54512C > 83 )
  {
    if ( dword_544CFC >> byte_54512C < 499
      || dword_544D00 >> byte_54512C < 91
      || dword_544CFC >> byte_54512C > 623
      || dword_544D00 >> byte_54512C > 137 )
    {
      if ( dword_544CFC >> byte_54512C < 499
        || dword_544D00 >> byte_54512C < 145
        || dword_544CFC >> byte_54512C > 623
        || dword_544D00 >> byte_54512C > 179 )
      {
        if ( dword_544CFC >> byte_54512C < 499
          || dword_544D00 >> byte_54512C < 179
          || dword_544CFC >> byte_54512C > 623
          || dword_544D00 >> byte_54512C > 213 )
        {
          if ( dword_544CFC >> byte_54512C < 499
            || dword_544D00 >> byte_54512C < 213
            || dword_544CFC >> byte_54512C > 623
            || dword_544D00 >> byte_54512C > 247 )
          {
            if ( dword_544CFC >> byte_54512C < 499
              || dword_544D00 >> byte_54512C < 247
              || dword_544CFC >> byte_54512C > 623
              || dword_544D00 >> byte_54512C > 281 )
            {
              if ( dword_544CFC >> byte_54512C < 499
                || dword_544D00 >> byte_54512C < 281
                || dword_544CFC >> byte_54512C > 623
                || dword_544D00 >> byte_54512C > 315 )
              {
                if ( dword_544CFC >> byte_54512C < 499
                  || dword_544D00 >> byte_54512C < 315
                  || dword_544CFC >> byte_54512C > 623
                  || dword_544D00 >> byte_54512C > 349 )
                {
                  v3 = -1;
                }
                else
                {
                  v3 = 7;
                }
              }
              else
              {
                v3 = 6;
              }
            }
            else
            {
              v3 = 5;
            }
          }
          else
          {
            v3 = 4;
          }
        }
        else
        {
          v3 = 3;
        }
      }
      else
      {
        v3 = 2;
      }
    }
    else
    {
      v3 = 1;
    }
  }
  else
  {
    v3 = 0;
  }
  if ( v3 != g_UnitActionTooltipLastShownAction && (g_UnitBattleExitButtonState & 4) == 0 )
  {
    g_UnitActionTooltipLastShownAction = v3;
    if ( v3 == -1 )
    {
      LOWORD(v3) = UnitBattle_DrawSelectedUnitPanel(0, 1, a2, a3);
    }
    else
    {
      Tooltip_ShowText(3, (&g_UnitActionTooltipTexts[3 * v3])[(unsigned __int8)g_LanguageIndex], a1);
      LOWORD(v3) = RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
    }
  }
  return v3;
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
signed int  UnitBattle_RunTurnLoop(int a1, DWORD a2)
{
  int v2; // edx
  int v3; // eax
  int v4; // ebx
  DWORD v5; // ebp
  int v6; // ecx
  int v8[9]; // [esp+0h] [ebp-24h] BYREF

  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, (int)a2);
  g_SelectedUnitIndex = *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_restore_selected", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  Diagnostics_TraceBattleUnitSnapshot("turn_loop_after_restore_selected");
  if ( *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852) == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_selected_empty", g_SelectedUnitIndex, *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852), 0, 0);
    v2 = g_SelectedUnitIndex + 1;
    if ( g_SelectedUnitIndex + 1 != g_SelectedUnitIndex )
    {
      a1 = g_SelectedUnitIndex;
      do
      {
        v3 = g_MapData + 31 * v2;
        if ( *(__int16 *)(v3 + 852) != -1 && *(unsigned __int8 *)(v3 + 854) == g_CurrentPlayerIndex )
          break;
        v2 = (v2 + 1) % 22;
      }
      while ( v2 != g_SelectedUnitIndex );
    }
    g_SelectedUnitIndex = v2;
    Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_find_selected", g_SelectedUnitIndex, a1, *(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852), 0);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_before_action_buttons", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  UnitBattle_RefreshSelectedActionButtons();
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_action_buttons", g_SelectedUnitIndex, g_CurrentPlayerIndex, 0, 0);
  *(_DWORD *)(g_MapData + 808) = *(unsigned __int8 *)(g_MapData + 2 * g_CurrentPlayerIndex + 3934);
  *(_DWORD *)(g_MapData + 812) = *(unsigned __int8 *)(g_MapData + 2 * g_CurrentPlayerIndex + 3935);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_before_grid", g_SelectedUnitIndex, *(_DWORD *)(g_MapData + 808), *(_DWORD *)(g_MapData + 812), 0);
  UnitBattle_RedrawVisibleGrid();
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_grid", g_SelectedUnitIndex, *(_DWORD *)(g_MapData + 808), *(_DWORD *)(g_MapData + 812), 0);
  UnitBattle_DrawSelectedUnitPanel(0, 1, a1, (int)v8);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_panel", g_SelectedUnitIndex, a1, (int)(uintptr_t)v8, 0);
  v8[0] = (int)g_BattleYourTurnBannerTexts[0];
  v8[1] = (int)g_BattleYourTurnBannerTexts[1];
  v8[2] = (int)g_BattleYourTurnBannerTexts[2];
  v4 = 1;
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_before_banner", g_SelectedUnitIndex, g_CurrentPlayerIndex, v8[(unsigned __int8)g_LanguageIndex], (int)a2);
  UnitBattle_ShowPlayerMessageBanner(v8[(unsigned __int8)g_LanguageIndex], g_CurrentPlayerIndex, 1, a2);
  Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_banner", g_SelectedUnitIndex, g_CurrentPlayerIndex, g_BattleLoopExitCode, 0);
  v5 = g_BattleLoopExitCode;
  g_UnitBattleActionLoopExitRequested = 0;
  Diagnostics_PrimeBattleSafeCursorOnTurnLoop();
  if ( !g_BattleLoopExitCode )
  {
    while ( !g_UnitBattleActionLoopExitRequested )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_iter_top", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, (int)v5);
      UnitBattle_UpdateActionTooltip(0, v4, 0);
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_tooltip", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_UpdateIdleAnimatedUnits();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_idle_anim", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      Battle_RunInputScriptStep();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_input_script", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      DD_Pump((int)g_RenderState, v4);
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_pump", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_HandleBattlefieldInteraction();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_interaction", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_UpdateViewportFromInputAndGetHoveredSlot(v6);
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_hover", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      UnitBattle_HandleManualRotateAndMoveInput();
      Diagnostics_TraceWorldMapActionEvent("battle_turn_loop_after_input_widgets", g_SelectedUnitIndex, g_CurrentPlayerIndex, v4, 0);
      if ( UIWidgetTable_PollHoverAndActions(g_UnitBattleActionWidgetTable, v5) == 1 )
      {
        v4 = (int)(uintptr_t)UnitType_GetLocalizedName(
          (unit_type)*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
        Tooltip_ShowText(3, (char *)v4, v8[0]);
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
        int a1,
        int a2,
        int a3,
        unsigned __int8 *a4,
        DWORD a5)
{
  _WORD *v5; // edx
  int i; // eax
  _WORD *v7; // edx
  int j; // eax
  char *v9; // eax
  unsigned __int8 *v10; // ebx
  int k; // edx
  int v12; // ecx
  int v13; // esi
  char *v14; // edi
  char *v15; // esi
  char *v16; // edi
  char *v17; // esi
  int v18; // eax
  _WORD *v19; // edx

  Debug_Log(a3, a1, a5, (int)aHandlebattlere);
  Battle_RestoreSavedActionPointsBeforeResultCopy();
  v5 = (_WORD *)(a1 + 6);
  for ( i = 0; i < 10; ++i )
  {
    *v5 = -1;
    v5 = (_WORD *)((char *)v5 + 31);
  }
  if ( a2 )
  {
    v7 = (_WORD *)(a2 + 6);
    for ( j = 0; j < 10; ++j )
    {
      *v7 = -1;
      v7 = (_WORD *)((char *)v7 + 31);
    }
  }
  else
  {
    v18 = 0;
    v19 = a4 + 18;
    do
    {
      ++v18;
      *v19 = -1;
      v19 = (_WORD *)((char *)v19 + 31);
    }
    while ( v18 < 12 );
  }
  v9 = (char *)(a1 + 6);
  if ( a2 )
    v10 = (unsigned __int8 *)(a2 + 6);
  else
    v10 = a4 + 18;
  for ( k = 0; k != 682; k += 31 )
  {
    v12 = g_MapData;
    v13 = k + g_MapData;
    if ( *(__int16 *)(k + g_MapData + 852) != -1 )
    {
      if ( *(unsigned __int8 *)(v13 + 854) == *(_DWORD *)(g_MapData + 836) )
      {
        v14 = v9;
        v15 = (char *)(v13 + 852);
        v9 += 31;
      }
      else
      {
        v14 = (char *)v10;
        v15 = (char *)(v13 + 852);
        v10 += 31;
      }
      qmemcpy(v14, v15, 0x1Cu);
      v17 = v15 + 28;
      v16 = v14 + 28;
      v12 = 0;
      *(_WORD *)v16 = *(_WORD *)v17;
      v16[2] = v17[2];
    }
  }
  Debug_Log(v12, (char)v10, a5, (int)aHandlebattle_0);
  Unit_DebugDumpFormationSizes(a1, a5);
  if ( a2 )
    Unit_DebugDumpFormationSizes(a2, a5);
  else
    Building_DebugDump(a4, (char)v10, a5);
}
// 42E5D1: variable 'v5' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042E6F0) --------------------------------------------------------
int UnitBattle_TemporarilyClearGateBlocker()
{
  int result; // eax
  char v1; // bl

  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    result = *(_DWORD *)(g_MapData + 828) + g_MapData + 20 * *(_DWORD *)(g_MapData + 824);
    v1 = *(_BYTE *)(result + 3134);
    if ( v1 )
    {
      *(_DWORD *)(g_MapData + 832) = v1;
      result = *(_DWORD *)(g_MapData + 828) + g_MapData + 20 * *(_DWORD *)(g_MapData + 824);
      *(_BYTE *)(result + 3134) = 0;
    }
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042E770) --------------------------------------------------------
char UnitBattle_RestoreGateBlocker()
{
  char result; // al

  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    result = *(_BYTE *)(g_MapData + 832);
    *(_BYTE *)(g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + *(_DWORD *)(g_MapData + 828) + 3134) = result;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042E7C0) --------------------------------------------------------
int  UnitBattle_OverrideControllerOrderBits(int a1, int a2, int a3, int a4)
{
  int v6; // edx
  int result; // eax
  int v8; // ecx

  v6 = 0;
  result = 0;
  do
  {
    v8 = g_MapData;
    *(_DWORD *)&dword_532090[v6] = *(_BYTE *)(g_MapData + result + 864) & 3;
    if ( *(unsigned __int8 *)(v8 + result + 854) == a1 && a2
      || *(unsigned __int8 *)(g_MapData + result + 854) == a4 && a3 )
    {
      *(_BYTE *)(g_MapData + result + 864) |= 3u;
    }
    v6 += 4;
    result += 31;
  }
  while ( v6 != 88 );
  return result;
}
// 42E7C0: could not find valid save-restore pair for ebx
// 532048: using guessed type int g_MapData;

//----- (0042E860) --------------------------------------------------------
int UnitBattle_RestoreControllerOrderBits()
{
  int v0; // edx
  int v1; // ecx
  int result; // eax
  char v3; // bl
  char v4; // bh

  v0 = 0;
  v1 = 0;
  do
  {
    result = g_MapData;
    v3 = dword_532090[v0] & 3;
    v4 = *(_BYTE *)(v1 + g_MapData + 864);
    v1 += 31;
    v4 &= 0xFCu;
    *(_BYTE *)(v1 + g_MapData + 833) = v4;
    v0 += 4;
    *(_BYTE *)(v1 + result + 833) = v3 | v4;
  }
  while ( v0 != 88 );
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0042E8B0) --------------------------------------------------------
int *UnitBattle_InitBattleScreenFrame()
{
  void *v0; // edx
  int SpriteForChar; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // edi
  int v6; // edx

  Palette_ApplyDefaultPalette((int *)&unk_51D4C0);
  g_RenderDevice = v0;
  SpriteForChar = DLX_GetSpriteForChar(dword_5202BC, 0);
  Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  v2 = DLX_GetSpriteForChar(dword_5202BC, 1);
  Compat_RenderDeviceDrawMenuSprite(0, 0, v2, 1);
  v3 = DLX_GetSpriteForChar(dword_5202BC, 2);
  Compat_RenderDeviceDrawMenuSprite(243, 0, v3, 1);
  v4 = DLX_GetSpriteForChar(dword_5202BC, 3);
  v5 = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(243, 0, v4, 1);
  UIWidgetTable_InitDrawStates(g_UnitBattleActionWidgetTable);
  UnitBattle_DrawSelectedUnitPanel(0, v6, 20, v5);
  UnitBattle_RedrawVisibleGrid();
  return Palette_FadeInFromBlack((int *)&unk_51D4C0, (unsigned __int8 *)dword_5202F4, 20);
}
// 42E8C9: variable 'v0' is possibly undefined
// 42E9B6: variable 'v6' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514B78: using guessed type _DWORD dword_514B78[2];
// 5202BC: using guessed type int dword_5202BC;
// 5202F4: using guessed type int dword_5202F4;

//----- (0042E9E0) --------------------------------------------------------
DWORD  Battle_RunTacticalCombat(
        __int16 *a1,
        __int16 *a2,
        int a3,
        unsigned __int8 *a4,
        DWORD a5,
        int a6)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  unsigned __int8 v9; // al
  _DWORD *v10; // eax
  _DWORD *v11; // eax
  int v12; // ecx
  _DWORD *v13; // eax
  int v14; // ecx
  _DWORD *v15; // eax
  _DWORD *v16; // eax
  int SpriteForChar; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // edx
  unsigned int v22; // ecx
  unsigned __int8 v23; // al
  int v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // eax
  int i; // edx
  int v30; // eax
  int j; // edx
  int v32; // ecx
  int v33; // ecx
  int k; // eax
  int v35; // ecx
  int v36; // ecx
  unsigned __int8 *v37; // esi
  int v38; // edx
  __int16 *v39; // esi
  signed int v40; // eax
  DWORD v41; // ebp
  char *v42; // esi
  char *v43; // edi
  char v44; // al
  char v45; // al
  int v46; // ecx
  int v47; // ebx
  int v48; // edx
  int v49; // ecx
  BOOL v50; // edi
  int v51; // ecx
  DWORD v52; // ebp
  int v53; // ecx
  int v54; // esi
  signed int v55; // esi
  int m; // eax
  int v57; // edx
  int v58; // ecx
  int v59; // ecx
  DWORD v60; // ebp
  int v61; // ecx
  char v62; // bl
  unsigned __int8 *v63; // edi
  int v64; // ecx
  int v65; // ecx
  int v66; // ecx
  int v68; // eax
  int v69; // ecx
  char v70[100]; // [esp+Ch] [ebp-A8h] BYREF
  int v71[3]; // [esp+70h] [ebp-44h]
  int v72; // [esp+7Ch] [ebp-38h] BYREF
  int v73; // [esp+80h] [ebp-34h] BYREF
  unsigned __int8 *v74; // [esp+84h] [ebp-30h]
  int v75; // [esp+88h] [ebp-2Ch]
  int v76; // [esp+8Ch] [ebp-28h]
  int (*v77)(); // [esp+90h] [ebp-24h]
  int v78; // [esp+94h] [ebp-20h]
  int v79; // [esp+98h] [ebp-1Ch]
  int v80; // [esp+9Ch] [ebp-18h]
  __int16 *v81; // [esp+A0h] [ebp-14h]
  __int16 *v82; // [esp+A4h] [ebp-10h]
  const char *battle_background_resource;
  int battle_map_bytes_read;

  v81 = a1;
  v82 = a2;
  v74 = a4;
  v75 = a3;
  Diagnostics_ResetFrameDumpOnBattleEnter();
  Debug_Log(a3, (char)a4, a5, (int)aBattle_0);
  Battle_StoreLastOutcomeValue(1);
  Debug_Log(v6, (char)a4, a5, (int)aNewBattle_0);
  v79 = Render_SetResourceHandle((int)&unk_51D4C0, (char *)UnitBattle_InitBattleScreenFrame == (char *)Render_DefaultRH);
  v77 = g_RenderHook;
  g_RenderHook = (int (*)())UnitBattle_InitBattleScreenFrame;
  Debug_Log(v7, (char)a4, a5, (int)aSetrhS08x_8);
  v76 = Audio_PauseMusicAndPlayLoopedSound(aBattle_1, 1);
  DLXSpriteSet_ReleaseAndClear(&dword_5202C0);
  v9 = *(_BYTE *)(gameData + 140016);
  battle_background_resource = 0;
  if ( !v9 )
    battle_background_resource = aBattleBat_bkg1;
  else if ( v9 <= 1u )
    battle_background_resource = aBattleBat_bkg2;
  else if ( v9 == 2 )
    battle_background_resource = aBattleBat_bkg3;
  if ( battle_background_resource )
  {
    v10 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( v10 )
      v10 = DLXSpriteSet_Load(v10, battle_background_resource);
  }
  else
  {
    v10 = 0;
  }
  g_BattleHudSprites = (int)v10;
  v11 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( v11 )
    v11 = DLXSpriteSet_Load(v11, aBattleButtons_);
  dword_532050 = (int)v11;
  v13 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( v13 )
    v13 = DLXSpriteSet_Load(v13, aBattleFr_anim_);
  dword_532054 = (int)v13;
  v15 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( v15 )
    v15 = DLXSpriteSet_Load(v15, aBattleTrupki_s);
  dword_532058 = (int)v15;
  g_UnitActionTooltipLastShownAction = -1;
  g_UnitFadeAnimUnitIndex = -1;
  g_ActiveUnitMoveTileIndex = -1;
  g_UnitBattleExitButtonOverlaySpriteIndex = (unsigned __int8)g_LanguageIndex + 13;
  g_UnitBattleAnimatingUnitIndex = -1;
  v16 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( v16 )
    v16 = DLXSpriteSet_Load(v16, aBattleFrame_s3);
  dword_5202BC = (int)v16;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_resources", dword_5202BC, g_BattleHudSprites, dword_532050, dword_532054);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v16, 0);
  Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  v18 = DLX_GetSpriteForChar(dword_5202BC, 1);
  Compat_RenderDeviceDrawMenuSprite(0, 0, v18, 1);
  v19 = DLX_GetSpriteForChar(dword_5202BC, 2);
  Compat_RenderDeviceDrawMenuSprite(243, 0, v19, 1);
  v20 = DLX_GetSpriteForChar(dword_5202BC, 3);
  Compat_RenderDeviceDrawMenuSprite(243, 0, v20, 1);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_frame_draw", dword_5202BC, SpriteForChar, v18, v19);
  Tooltip_CaptureBackdrop(160, 473, 7, 467, 76);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_backdrop", 0, 0, 0, 0);
  g_MapData = (int)nmalloc_(0xF7C, 4);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_state_alloc", g_MapData, 0xF7C, 0, 0);
  if ( !g_MapData )
  {
    Debug_Log(0, 211, (DWORD)&unk_51D4C0, (int)aNotEnoughMem_9);
    App_RequestQuit((int)aNotEnoughMe_10);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_player_state", g_MapData, (int)v81, (int)v82, 0);
  v78 = g_CurrentPlayerIndex;
  g_CurrentPlayerIndex = *((unsigned __int8 *)v81 + 4);
  *(_DWORD *)(g_MapData + 836) = g_CurrentPlayerIndex;
  if ( v82 )
    v23 = *((_BYTE *)v82 + 4);
  else
    v23 = v74[2];
  *(_DWORD *)(g_MapData + 840) = v23;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_players", *(_DWORD *)(g_MapData + 836), *(_DWORD *)(g_MapData + 840), 0, 0);
  *(_DWORD *)(1423 * *(_DWORD *)(g_MapData + 836) + gameData + 140077) = 0;
  *(_DWORD *)(gameData + 1423 * *(_DWORD *)(g_MapData + 840) + 140077) = 0;
  *(_DWORD *)(1423 * *(_DWORD *)(g_MapData + 836) + gameData + 140073) = 0;
  *(_DWORD *)(gameData + 1423 * *(_DWORD *)(g_MapData + 840) + 140073) = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_player_counters", *(_DWORD *)(g_MapData + 836), *(_DWORD *)(g_MapData + 840), 0, 0);
  if ( *((_BYTE *)v81 + 720) )
  {
    *(_DWORD *)(g_MapData + 844) = *((unsigned __int8 *)v81 + 4);
  }
  else if ( v82 && *((_BYTE *)v82 + 720) )
  {
    *(_DWORD *)(g_MapData + 844) = *((unsigned __int8 *)v82 + 4);
  }
  else
  {
    *(_DWORD *)(g_MapData + 844) = -1;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_castle_owner", *(_DWORD *)(g_MapData + 844), 0, 0, 0);
  if ( v82 )
    v24 = *v82;
  else
    v24 = *v74;
  if ( v82 )
    v25 = v82[1];
  else
    v25 = v74[1];
  v26 = *v81;
  if ( v26 >= v24 )
  {
    if ( v26 <= v24 )
    {
      if ( v81[1] >= v25 )
      {
        v25 = 1;
        g_DefenderStartsOnLeft = 1;
        g_AttackerStartsOnLeft = 0;
      }
      else
      {
        g_AttackerStartsOnLeft = 1;
        g_DefenderStartsOnLeft = 0;
      }
    }
    else
    {
      g_DefenderStartsOnLeft = 1;
      g_AttackerStartsOnLeft = 0;
    }
  }
  else
  {
    v25 = 0;
    g_AttackerStartsOnLeft = 1;
    g_DefenderStartsOnLeft = 0;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_orientation", g_AttackerStartsOnLeft, g_DefenderStartsOnLeft, v24, v25);
  if ( v82 )
    BattleMapFileName(v70, *v82, v82[1]);
  else
    BattleMap_GetOutcomeVariantFileName(v70, g_DefenderStartsOnLeft, v74[1]);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_name", g_AttackerStartsOnLeft, g_DefenderStartsOnLeft, v25, 0);
  v73 = FileSystem_ResolveReadPath(v70, 1);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_open", v73, 0, 0, 0);
  battle_map_bytes_read = Compat_QueryRead(v73, (void *)(uintptr_t)(unsigned int)g_MapData, 0x320);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_read", v73, battle_map_bytes_read, 0x320, 0);
  Compat_FileSystemQueryRelease(v27, &v73);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_map_close", v73, 0, 0, 0);
  v28 = 0;
  for ( i = 0; i < 800; i += 40 )
  {
    if ( *(__int16 *)(g_MapData + i) == -1 )
      break;
    ++v28;
  }
  *(_DWORD *)(g_MapData + 804) = v28;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_row_count", v28, i, *(__int16 *)g_MapData, 0);
  v30 = 0;
  for ( j = 0; j < 40; j += 2 )
  {
    v32 = *(__int16 *)(g_MapData + j);
    if ( v32 == -1 )
      break;
    ++v30;
  }
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_col_count", v30, j, *(__int16 *)g_MapData, 0);
  *(_DWORD *)(g_MapData + 800) = 7;
  *(_DWORD *)(g_MapData + 808) = 0;
  *(_DWORD *)(g_MapData + 812) = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_dims_store", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), 0, 0);
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0x5FE), -1, 0x320);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_overlay_clear", g_MapData, 0x5FE, 0x320, 0);
  for ( k = UNIT_STACK_SLOT_STRIDE; k <= 0x2AA; k += UNIT_STACK_SLOT_STRIDE )
    *(_WORD *)(g_MapData + k + 0x335) = -1;
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_slot_sentinels", k, 0, 0, 0);
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0xC3E), 0, 0x190);
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0xDCE), 0, 0x190);
  *(_DWORD *)(g_MapData + 828) = -1;
  memset((void *)(uintptr_t)(unsigned int)(g_MapData + 0x91E), -1, 0x320);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_grid_clears", g_MapData, *(_DWORD *)(g_MapData + 828), 0, 0);
  v37 = v74;
  *(_DWORD *)(g_MapData + 816) = 5;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_pathing", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), *(_DWORD *)(g_MapData + 816), 0);
  UnitBattle_InitPathingTables();
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_pathing", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), g_TilePassabilityMask[0], 0);
  if ( v37 )
    Battle_LoadWallSegmentsFromBuildingRecord((int)v37);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_building_setup", (int)(uintptr_t)v37, *(_DWORD *)(g_MapData + 848), 0, 0);
  *(_DWORD *)(g_MapData + 848) = v74 == 0;
  g_RenderDevice = &unk_51D4C0;
  UIWidgetTable_InitDrawStates(g_UnitBattleActionWidgetTable);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_ui_sync", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), 0, 0);
  UnitBattle_RedrawVisibleGrid();
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_first_grid_draw", *(_DWORD *)(g_MapData + 800), *(_DWORD *)(g_MapData + 804), 0, 0);
  *(_DWORD *)(g_MapData + 824) = 0;
  *(_DWORD *)(g_MapData + 832) = 0;
  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    for ( ; ; ++*(_DWORD *)(g_MapData + 824) )
    {
      if ( *(_DWORD *)(g_MapData + 824) >= *(_DWORD *)(g_MapData + 804) )
        App_RequestQuit((int)aBattleActiveTi);
      v38 = g_MapData + 20 * *(_DWORD *)(g_MapData + 824);
      if ( *(_BYTE *)(v38 + 3534) )
        break;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_init_after_active_tile", *(_DWORD *)(g_MapData + 824), v38, *(_BYTE *)(v38 + 3534), 0);
    *(_DWORD *)(g_MapData + 832) = *(char *)(*(_DWORD *)(g_MapData + 828) + v38 + 3134);
    Diagnostics_TraceWorldMapActionEvent("battle_init_after_active_cost", *(_DWORD *)(g_MapData + 832), *(_DWORD *)(g_MapData + 828), 0, 0);
  }
  else
  {
    Diagnostics_TraceWorldMapActionEvent("battle_init_no_active_gate", *(_DWORD *)(g_MapData + 824), *(_DWORD *)(g_MapData + 828), 0, 0);
  }
  v39 = v82;
  v80 = Unit_GetSquadCount((int)v81);
  if ( v39 )
    v40 = Unit_GetSquadCount((int)v39);
  else
    v40 = Building_CountGarrison((int)v74);
  v41 = v40;
  if ( v82 )
    v42 = (char *)(v82 + 3);
  else
    v42 = (char *)(v74 + 18);
  v43 = (char *)(v81 + 3);
  Battle_DeploySideUnitsByRoleBuckets((char *)v81 + 6, v80, v42, g_AttackerStartsOnLeft, v40);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_init_after_deploy_attacker",
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 836)),
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 840)),
    Diagnostics_CountBattleUnitsTotal(),
    g_SelectedUnitIndex);
  Battle_DeploySideUnitsByRoleBuckets(v42, v41, v43, g_DefenderStartsOnLeft, v80);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_init_after_deploy_defender",
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 836)),
    Diagnostics_CountBattleUnitsForOwner(*(_DWORD *)(g_MapData + 840)),
    Diagnostics_CountBattleUnitsTotal(),
    g_SelectedUnitIndex);
  Diagnostics_TraceBattleUnitSnapshot("after_deploy_defender");
  UnitBattle_OverrideControllerOrderBits(*(_DWORD *)(g_MapData + 836), v75, a6, *(_DWORD *)(g_MapData + 840));
  if ( g_AttackerStartsOnLeft )
    v44 = 0;
  else
    v44 = *(_DWORD *)(g_MapData + 804) - 7;
  *(_BYTE *)(g_MapData + 2 * *(_DWORD *)(g_MapData + 836) + 3934) = v44;
  if ( g_DefenderStartsOnLeft )
    v45 = 0;
  else
    v45 = *(_DWORD *)(g_MapData + 804) - 7;
  *(_BYTE *)(g_MapData + 2 * *(_DWORD *)(g_MapData + 840) + 3934) = v45;
  v46 = 2 * *(_DWORD *)(g_MapData + 840) + g_MapData;
  *(_BYTE *)(v46 + 3935) = (*(_DWORD *)(g_MapData + 800) - 7) / 2;
  *(_BYTE *)(g_MapData + 2 * *(_DWORD *)(g_MapData + 836) + 3935) = *(_BYTE *)(v46 + 3935);
  g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 836);
  dword_53205C = 0;
  g_BattleLoopExitCode = 0;
  g_SelectedUnitIndex = *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944);
  UnitBattle_RedrawVisibleGrid();
  Diagnostics_TraceWorldMapActionEvent(
    "battle_init_after_selected_grid_draw",
    g_SelectedUnitIndex,
    g_CurrentPlayerIndex,
    *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944),
    0);
  v47 = 20;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_selected_panel", g_SelectedUnitIndex, v48, (int)(uintptr_t)v43, v47);
  UnitBattle_DrawSelectedUnitPanel(0, v48, 20, (int)v43);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_selected_panel", g_SelectedUnitIndex, v48, (int)(uintptr_t)v43, v47);
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_palette_ramp", dword_5202F4, (int)(uintptr_t)&unk_51D4C0, 20, 0);
  Palette_FadeInFromBlack((int *)&unk_51D4C0, (unsigned __int8 *)dword_5202F4, 20);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_palette_ramp", dword_5202F4, (int)(uintptr_t)&unk_51D4C0, 20, 0);
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_palette_cache", dword_5202F4, v49, (int)v41, 0);
  Palette_LoadOrBuildBlendLookupTable(aMainmap_3, dword_5202F4, v49, v41);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_palette_cache", dword_5202F4, v49, (int)v41, 0);
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_cursor_mode", (int)(uintptr_t)g_RenderState, (int)(uintptr_t)&g_CursorDesc_ActionBusy, dword_545150, 0);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_cursor_mode", (int)(uintptr_t)g_RenderState, (int)(uintptr_t)&g_CursorDesc_ActionBusy, dword_545150, 0);
  dword_545150 = (int)&g_CursorDesc_Default;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_present", (int)(uintptr_t)g_RenderState, dword_545150, 0, 0);
  Render_Present((int)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_present", (int)(uintptr_t)g_RenderState, dword_545150, 0, 0);
  v50 = PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) == 0;
  Debug_Log(v51, 20, v41, (int)aStart_0);
  v52 = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_init_before_log_units", g_CurrentPlayerIndex, v47, v52, 0);
  Battle_LogAllUnits(v53, 20, 0);
  Diagnostics_TraceWorldMapActionEvent("battle_init_after_log_units", g_CurrentPlayerIndex, v47, v52, 0);
  while ( 1 )
  {
    v54 = *(_DWORD *)(g_MapData + 828);
    if ( v54 != -1 )
    {
      if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 840) )
      {
        *(_DWORD *)(g_MapData + 832) = *(char *)(v54 + g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + 3134);
        *(_BYTE *)(*(_DWORD *)(g_MapData + 828) + g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + 3134) = 0;
      }
      else
      {
        *(_BYTE *)(v54 + g_MapData + 20 * *(_DWORD *)(g_MapData + 824) + 3134) = *(_BYTE *)(g_MapData + 832);
      }
    }
    if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
    {
      if ( v50 )
        UnitBattle_AnimateSelectedUnitPanel(0, v47, v50);
      v55 = UnitBattle_RunTurnLoop(v47, v52);
      v50 = 0;
    }
    else
    {
      if ( !v50 )
        UnitBattle_AnimateSelectedUnitPanel(1, v47, 0);
      v50 = 1;
      v55 = UnitBattle_RunAiTurnForSide(g_CurrentPlayerIndex);
      if ( !Battle_HasUnitsForBothSides() )
        v55 = 1;
    }
    for ( m = 0; m != 682; m += 31 )
    {
      v57 = m + g_MapData;
      v58 = *(__int16 *)(m + g_MapData + 852);
      if ( v58 != -1 )
      {
        v47 = *(unsigned __int8 *)(v57 + 854);
        if ( v47 == g_CurrentPlayerIndex )
        {
          *(_BYTE *)(v57 + 860) = g_UnitTypeBaseActionPoints_512580[88 * v58];
          *(_BYTE *)(g_MapData + m + 864) &= 0x8Fu;
        }
      }
    }
    if ( v55 )
      break;
    v68 = PLAYER_DATA(g_CurrentPlayerIndex);
    if ( *(_DWORD *)(v68 + PLAYER_BATTLE_IDLE_FLAG_OFFSET) )
      *(_DWORD *)(v68 + PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET) = 0;
    else
      ++*(_DWORD *)(v68 + PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET);
    v69 = g_CurrentPlayerIndex;
    if ( *(int *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET) >= 2 )
      GodAnger(g_CurrentPlayerIndex, g_CurrentPlayerIndex, v47);
    *(_DWORD *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_BATTLE_IDLE_FLAG_OFFSET) = 0;
    *(_DWORD *)(4 * g_CurrentPlayerIndex + g_MapData + 3944) = g_SelectedUnitIndex;
    *(_BYTE *)(g_MapData + 2 * g_CurrentPlayerIndex + 3934) = *(_BYTE *)(g_MapData + 808);
    *(_BYTE *)(g_MapData + 2 * g_CurrentPlayerIndex + 3935) = *(_BYTE *)(g_MapData + 812);
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 844) )
    {
      if ( v52 )
      {
        if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836) )
          g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 840);
        else
          g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 836);
        v52 = 0;
      }
      else
      {
        v52 = 1;
      }
    }
    else
    {
      v69 = *(_DWORD *)(g_MapData + 836);
      if ( g_CurrentPlayerIndex == v69 )
        g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 840);
      else
        g_CurrentPlayerIndex = *(_DWORD *)(g_MapData + 836);
    }
    g_SelectedUnitIndex = *(_DWORD *)(g_MapData + 4 * g_CurrentPlayerIndex + 3944);
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836) )
      Battle_NewTurn(v69, v47, v52);
  }
  UnitBattle_RestoreControllerOrderBits();
  Debug_Log(v59, v47, v52, (int)aEndOfBattle);
  v60 = 0;
  if ( Battle_HasUnitsForBothSides() )
  {
    Battle_ApplyPeriodicDamageToSideUnits(g_CurrentPlayerIndex);
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 836) )
      v60 = 1;
    else
      v60 = 2;
  }
  v62 = (char)v74;
  v63 = v74;
  HandleBattleResults((int)v81, (int)v82, v61, v74, v60);
  if ( v63 )
    Battle_SaveWallSegmentsToBuildingRecord((int)v63);
  if ( v60 == 2 && *(_DWORD *)(1423 * *(_DWORD *)(g_MapData + 840) + gameData + 140051)
    || v60 == 1 && *(_DWORD *)(gameData + 1423 * *(_DWORD *)(g_MapData + 836) + 140051) )
  {
    v71[0] = (int)g_BattleForcedRetreatOutcomeTexts[0];
    v71[1] = (int)g_BattleForcedRetreatOutcomeTexts[1];
    v71[2] = (int)g_BattleForcedRetreatOutcomeTexts[2];
    UI_ShowInfoWindow(v71[(unsigned __int8)g_LanguageIndex], 0, v64, v60, (int)&v72, (int)&g_BattleForcedRetreatOutcomeTexts[3]);
  }
  Render_Pump();
  Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
  DLXSpriteSet_ReleaseAndClear(&dword_5202BC);
  DLXSpriteSet_ReleaseAndClear(&g_BattleHudSprites);
  DLXSpriteSet_ReleaseAndClear(&dword_532050);
  DLXSpriteSet_ReleaseAndClear(&dword_532054);
  DLXSpriteSet_ReleaseAndClear(&dword_532058);
  nfree_(g_MapData);
  g_MapData = 0;
  Tooltip_ReleaseBackdropSurface();
  TextSprite_ReleaseAllResourceSlots();
  UnitSpriteCache_FreeAllEntries(v66, v60);
  CSS_EmptySampleCache();
  g_SelectedUnitIndex = -1;
  g_CurrentPlayerIndex = v78;
  CSS_EmptySampleCache();
  Audio_ResumeMusicAndStopLoopedSound(v76);
  Battle_StoreLastOutcomeValue(0);
  Debug_Log((int)g_RenderHook, v62, v60, (int)aUnsetrh08x_9);
  g_RenderHook = v77;
  Render_SetResourceHandle((int)&unk_51D4C0, v79);
  return v60;
}
// 42E9E0: could not find valid save-restore pair for ebx
// 42F75C: conditional instruction was optimized away because esi.4==0
// 42EA1B: variable 'v6' is possibly undefined
// 42EA6B: variable 'v7' is possibly undefined
// 42EAAF: variable 'v8' is possibly undefined
// 42EAE9: variable 'v12' is possibly undefined
// 42EB06: variable 'v14' is possibly undefined
// 42EC77: variable 'v21' is possibly undefined
// 42EC86: variable 'v22' is possibly undefined
// 42EE2D: variable 'v27' is possibly undefined
// 42EEEB: variable 'v33' is possibly undefined
// 42EF01: variable 'v35' is possibly undefined
// 42EF29: variable 'v36' is possibly undefined
// 42F2B1: variable 'v48' is possibly undefined
// 42F2D1: variable 'v49' is possibly undefined
// 42F31C: variable 'v51' is possibly undefined
// 42F326: variable 'v53' is possibly undefined
// 42F41D: variable 'v59' is possibly undefined
// 42F46C: variable 'v61' is possibly undefined
// 42F4DC: variable 'v64' is possibly undefined
// 42F531: variable 'v65' is possibly undefined
// 42F547: variable 'v66' is possibly undefined
// 42F755: variable 'v69' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 514B78: using guessed type _DWORD dword_514B78[2];
// 514C99: using guessed type int dword_514C99;
// 514E28: using guessed type int dword_514E28;
// 514E38: using guessed type char *off_514E38[3];
// 514E44: using guessed type int dword_514E44;
// 514E48: using guessed type int dword_514E48;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202BC: using guessed type int dword_5202BC;
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202F4: using guessed type int dword_5202F4;
// 532048: using guessed type int g_MapData;
// 53204C: using guessed type int g_BattleHudSprites;
// 532050: using guessed type int dword_532050;
// 532054: using guessed type int dword_532054;
// 532058: using guessed type int dword_532058;
// 53205C: using guessed type int dword_53205C;
// 532064: using guessed type int g_BattleLoopExitCode;
// 53206C: using guessed type int g_AttackerStartsOnLeft;
// 532070: using guessed type int g_DefenderStartsOnLeft;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (0042F7C0) --------------------------------------------------------
int  UnitBattle_GetSpriteVerticalOffsetPx(int a1)
{
  return (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *(__int16 *)(g_MapData + 31 * a1 + 852)];
}
// 532048: using guessed type int g_MapData;

//----- (0042F7F0) --------------------------------------------------------
int  UnitBattle_InitUnitFadeAnimation(int a1, int a2, int a3, int a4)
{
  int result; // eax

  g_UnitFadeAnimUnitIndex = a1;
  dword_5320F4 = a2;
  g_UnitFadeAnimTargetOffset = a4;
  g_UnitFadeAnimStepRate = a3;
  result = Time_Now(a3, a2);
  dword_5320F8 = result;
  return result;
}
// 514E48: using guessed type int dword_514E48;
// 514E4C: using guessed type int dword_514E4C;
// 514E50: using guessed type int dword_514E50;
// 5320F4: using guessed type int dword_5320F4;
// 5320F8: using guessed type int dword_5320F8;

//----- (0042F820) --------------------------------------------------------
int  UnitBattle_DrawUnitSprite(int a1, int a2, int a3, int a4)
{
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int SpriteForChar; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int result; // eax
  int v15; // edx
  int v16; // esi
  int v17; // ecx
  int v18; // edi
  int v19; // ecx
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // [esp-8h] [ebp-3Ch]
  int v28; // [esp+8h] [ebp-2Ch]
  int v29; // [esp+10h] [ebp-24h]
  int v30; // [esp+24h] [ebp-10h]
  int v32; // [esp+30h] [ebp-4h]
  _DWORD savedregs[3]; // [esp+34h] [ebp+0h] BYREF

  if ( a1 == -1 )
    goto LABEL_13;
  v5 = g_MapData + 31 * a1;
  v6 = *(__int16 *)(v5 + 852);
  if ( v6 == -1 )
    goto LABEL_13;
  v28 = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * v6];
  if ( g_ActiveUnitMoveTileIndex == -1 || a1 != g_ActiveUnitMoveTileIndex )
  {
    if ( g_UnitBattleAnimatingUnitIndex == -1 || a1 != g_UnitBattleAnimatingUnitIndex )
    {
      SpriteForChar = UnitSpriteCache_FindEntryOrLoad(
                        *(unsigned __int16 *)(g_MapData + 31 * a1 + 852),
                        *(_BYTE *)(g_MapData + 31 * a1 + 854),
                        *(_BYTE *)(g_MapData + 31 * a1 + 869) & 7,
                        *(_BYTE *)(g_MapData + 31 * a1 + 855));
      goto LABEL_7;
    }
    v7 = 8 * *(unsigned __int8 *)(31 * g_UnitBattleAnimatingUnitIndex + g_MapData + 855) + dword_5320EC;
    v8 = dword_5320F0;
  }
  else
  {
    v7 = g_UnitBattleAnimFrameCount * *(unsigned __int8 *)(v5 + 855) + dword_523F7C;
    v8 = dword_523F78;
  }
  SpriteForChar = DLX_GetSpriteForChar(v8, v7);
LABEL_7:
  v29 = SpriteForChar;
  if ( g_UnitFadeAnimUnitIndex == -1 )
    dword_5320F8 = 0;
  if ( a1 == g_SelectedUnitIndex && dword_532060 )
  {
    v12 = Time_Now(v11, v10);
    v13 = Math_SinDegreesQ16(2 * (v12 - dword_532074) - 90);
    Sprite_DrawSimpleIgnoringRect(v29, a2, a3 + a4 - v28, a3, a2 + 63, a3 + 63, ((50 * v13) >> 16) + 50, 0, 0, 200, 1u);
  }
  else if ( a1 == g_UnitFadeAnimUnitIndex )
  {
    if ( !dword_5320F8 )
      dword_5320F8 = Time_Now(v11, v10);
    v26 = g_UnitFadeAnimStepRate * (Time_Now(v11, v10) - dword_5320F8) + dword_5320F4;
    dword_5320F4 = v26;
    if ( v26 > g_UnitFadeAnimTargetOffset )
      dword_5320F4 = g_UnitFadeAnimTargetOffset;
    if ( dword_5320F4 < 0 )
      dword_5320F4 = 0;
    dword_5320F8 = Time_Now(g_UnitFadeAnimTargetOffset, v26);
    Sprite_DrawSimpleTrackingOffset(v29, a2, a3 + a4 - v28, a3, a2 + 63, a3 + 63, dword_5320F4, 1u);
  }
  else
  {
    Compat_RenderDeviceDrawMenuSprite(a2, a3 + a4 - v28, SpriteForChar, 1);
  }
  TextSprite_ActivateResourceSlot(0, 1, (DWORD)savedregs);
LABEL_13:
  result = UnitBattle_CountAdjacentEnemies(31 * a1 + g_MapData + 852);
  v16 = result;
  if ( !v17 && !a4 && result >= 3 )
  {
    v32 = 0;
    v30 = v15;
    v18 = 0;
    do
    {
      if ( v16 > 6 )
        v16 = 6;
      result = *(__int16 *)(g_MapData
                          + 40 * (Map_NeighborDX[v18] + *(unsigned __int16 *)(g_MapData + v30 + 856))
                          + 2 * (Map_NeighborDY[v18] + *(unsigned __int16 *)(g_MapData + v30 + 858))
                          + 1534);
      if ( result != -1 )
      {
        v19 = 31 * result + g_MapData;
        if ( *(_BYTE *)(v19 + 854) != *(_BYTE *)(g_MapData + v30 + 854) && result != g_ActiveUnitMoveTileIndex )
        {
          v20 = Time_Now(v19, 10 * v16);
          v21 = Math_SinDegreesQ16(v16 * v20);
          v27 = v22 + 120 + ((v22 * v21) >> 16);
          if ( *(unsigned __int8 *)(v30 + g_MapData + 854) == *(_DWORD *)(g_MapData + 836) )
            v23 = 17;
          else
            v23 = 25;
          v24 = DLX_GetSpriteForChar(dword_5202C8, v23 + v32);
          result = Sprite_DrawSimpleTrackingOffset(v24, v25, a3, a3, a2 + 63, a3 + 63, v27, 1u);
        }
      }
      v18 += 2;
      ++v32;
    }
    while ( v32 < 8 );
  }
  return result;
}
// 42F8DE: variable 'v11' is possibly undefined
// 42F8DE: variable 'v10' is possibly undefined
// 42F95F: variable 'v17' is possibly undefined
// 42F987: variable 'v15' is possibly undefined
// 42FA1E: variable 'v22' is possibly undefined
// 42FA77: variable 'v25' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 514E44: using guessed type int dword_514E44;
// 514E48: using guessed type int dword_514E48;
// 514E4C: using guessed type int dword_514E4C;
// 514E50: using guessed type int dword_514E50;
// 5202C8: using guessed type int dword_5202C8;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 532048: using guessed type int g_MapData;
// 532060: using guessed type int dword_532060;
// 532074: using guessed type int dword_532074;
// 5320EC: using guessed type int dword_5320EC;
// 5320F0: using guessed type int dword_5320F0;
// 5320F4: using guessed type int dword_5320F4;
// 5320F8: using guessed type int dword_5320F8;

//----- (0042FC30) --------------------------------------------------------
int  UnitBattle_DrawMovingUnitInAdjacentTile(int result, int a2, int a3, int a4)
{
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // [esp+0h] [ebp-10h]

  v11 = result;
  if ( g_ActiveUnitMoveTileIndex != -1 )
  {
    result = *(__int16 *)(g_MapData + 31 * g_ActiveUnitMoveTileIndex + 852);
    if ( result != 27 && result != 30 )
    {
      if ( a2 > 0 )
      {
        v6 = *(__int16 *)(g_MapData + 40 * v11 + 2 * a2 + 1532);
        if ( v6 != -1 && dword_523F74 > 0 && v6 == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(v6, a4, a3, dword_523F74 - 64);
      }
      if ( a2 < *(_DWORD *)(g_MapData + 804) - 1 )
      {
        v7 = *(__int16 *)(g_MapData + 40 * v11 + 2 * a2 + 1536);
        if ( v7 != -1 && dword_523F74 < 0 && v7 == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(v7, a4, a3, dword_523F74 + 64);
      }
      if ( v11 > 0 )
      {
        v8 = *(__int16 *)(g_MapData + 40 * (v11 - 1) + 2 * a2 + 1534);
        if ( v8 != -1 && dword_523F70 > 0 && v8 == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(v8, a4, a3, dword_523F74);
      }
      if ( *(_DWORD *)(g_MapData + 804) - 1 > v11 )
      {
        v9 = *(__int16 *)(40 * (v11 + 1) + g_MapData + 2 * a2 + 1534);
        if ( v9 != -1 && dword_523F70 < 0 && v9 == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(v9, a4, a3, dword_523F74);
      }
      if ( v11 > 0 && a2 > 0 )
      {
        v10 = *(__int16 *)(40 * (v11 - 1) + g_MapData + 2 * a2 + 1532);
        if ( v10 != -1 && dword_523F74 > 0 && dword_523F70 > 0 && v10 == g_ActiveUnitMoveTileIndex )
          UnitBattle_DrawUnitSprite(v10, a4, a3, dword_523F74 - 64);
      }
      result = v11;
      if ( v11 > 0 && a2 < *(_DWORD *)(g_MapData + 800) )
      {
        result = *(__int16 *)(40 * (v11 - 1) + g_MapData + 2 * a2 + 1536);
        if ( result != -1 && dword_523F74 < 0 && dword_523F70 > 0 && result == g_ActiveUnitMoveTileIndex )
          result = UnitBattle_DrawUnitSprite(result, a4, a3, dword_523F74 + 64);
      }
      if ( a2 > 0 )
      {
        result = v11;
        if ( v11 < *(_DWORD *)(g_MapData + 804) )
        {
          result = *(__int16 *)(40 * (v11 + 1) + g_MapData + 2 * a2 + 1532);
          if ( result != -1 && dword_523F74 > 0 && dword_523F70 < 0 && result == g_ActiveUnitMoveTileIndex )
            result = UnitBattle_DrawUnitSprite(result, a4, a3, dword_523F74 - 64);
        }
      }
      if ( a2 < *(_DWORD *)(g_MapData + 800) )
      {
        result = v11;
        if ( v11 < *(_DWORD *)(g_MapData + 804) )
        {
          result = *(__int16 *)(g_MapData + 40 * (v11 + 1) + 2 * a2 + 1536);
          if ( result != -1 && dword_523F74 < 0 && dword_523F70 < 0 && result == g_ActiveUnitMoveTileIndex )
            return UnitBattle_DrawUnitSprite(result, a4, a3, dword_523F74 + 64);
        }
      }
    }
  }
  return result;
}
// 512360: using guessed type int dword_512360;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 532048: using guessed type int g_MapData;

//----- (0042FFB0) --------------------------------------------------------
int  UnitBattle_DrawTileContents(int a1, int a2)
{
  int v2; // esi
  int SpriteForChar; // eax
  int v4; // eax
  int v5; // edx
  int v6; // eax
  char v7; // dl
  unsigned int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  unsigned int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // edi
  int v18; // edx
  int v19; // edi
  int v20; // edi
  int v21; // edx
  int v22; // edi
  int v23; // eax
  int v24; // ecx
  int v25; // edi
  int v26; // eax
  int v27; // edi
  int v28; // edi
  int v29; // edx
  int v30; // edi
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // ecx
  int result; // eax
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // ecx
  _BYTE *v40; // edx
  int v41; // [esp-8h] [ebp-38h]
  int v42; // [esp+0h] [ebp-30h]
  int v43; // [esp+8h] [ebp-28h]
  int v44; // [esp+10h] [ebp-20h]
  int v45; // [esp+14h] [ebp-1Ch]
  int v46; // [esp+18h] [ebp-18h]
  int v47; // [esp+1Ch] [ebp-14h]
  int v48; // [esp+20h] [ebp-10h]
  int v49; // [esp+24h] [ebp-Ch]

  v2 = ((a1 - *(_DWORD *)(g_MapData + 808)) << 6) + 32;
  v49 = ((a2 - *(_DWORD *)(g_MapData + 812)) << 6) + 16;
  if ( a1 < 0
    || a2 < 0
    || a1 >= *(_DWORD *)(g_MapData + 804)
    || a2 >= *(_DWORD *)(g_MapData + 800) )
    return 0;
  v42 = 40 * a1;
  v43 = 2 * a2;
  SpriteForChar = DLX_GetSpriteForChar(g_BattleHudSprites, *(__int16 *)(2 * a2 + 40 * a1 + g_MapData));
  Compat_RenderDeviceDrawMenuSprite(v2, v49, SpriteForChar, 1);
  v4 = v43 + v42 + g_MapData;
  v5 = *(char *)(v4 + 2334);
  if ( v5 != -1 )
  {
    v41 = *(unsigned __int8 *)(v4 + 2335);
    v36 = DLX_GetSpriteForChar(dword_532058, v5);
    Sprite_DrawSimpleTrackingOffset(v36, v2, v49, v49, v2 + 63, v49 + 63, v41, 1u);
  }
  if ( a2 != *(_DWORD *)(g_MapData + 828) )
  {
    v6 = a2 + g_MapData + 20 * a1;
    v7 = *(_BYTE *)(v6 + 3134);
    if ( v7 )
    {
      if ( v7 >= 33 )
        v47 = v7 < 66;
      else
        v47 = 2;
    }
    else
    {
      if ( !*(_BYTE *)(v6 + 3534) )
        goto LABEL_10;
      v47 = 3;
    }
    v8 = *(_DWORD *)(g_MapData + 820);
    if ( v8 )
    {
      if ( v8 <= 1 )
      {
        v47 += 412;
      }
      else if ( v8 == 2 )
      {
        v47 += 404;
      }
    }
    else
    {
      v47 += 420;
    }
    v9 = DLX_GetSpriteForChar(g_BattleHudSprites, v47);
    Compat_RenderDeviceDrawMenuSprite(v2, v49, v9, 1);
    dword_532104 = v47;
  }
LABEL_10:
  v10 = a2 + g_MapData + 20 * a1;
  v45 = 1;
  if ( *(_BYTE *)(v10 + 3534) && a2 == *(_DWORD *)(g_MapData + 828) )
  {
    if ( g_CurrentPlayerIndex == *(_DWORD *)(g_MapData + 840) )
      v11 = *(_DWORD *)(g_MapData + 832);
    else
      v11 = *(char *)(v10 + 3134);
    if ( v11 )
    {
      if ( v11 >= 33 )
        v48 = v11 < 66;
      else
        v48 = 2;
    }
    else if ( *(_BYTE *)(a2 + g_MapData + 20 * a1 + 3534) )
    {
      v48 = 3;
      v45 = 0;
    }
    v12 = *(_DWORD *)(g_MapData + 820);
    if ( v12 )
    {
      if ( v12 <= 1 )
      {
        v48 += 416;
      }
      else if ( v12 == 2 )
      {
        v48 += 408;
      }
    }
    else
    {
      v48 += 424;
    }
    if ( !v45 )
    {
      v38 = DLX_GetSpriteForChar(g_BattleHudSprites, v48);
      Compat_RenderDeviceDrawMenuSprite(v2, v49, v38, 1);
    }
    dword_532104 = v48;
  }
  if ( a1 > 0 )
  {
    v13 = g_MapData + 20 * (a1 - 1) + a2;
    if ( *(_BYTE *)(v13 + 3134) )
    {
      if ( a2 != *(_DWORD *)(g_MapData + 828) )
      {
        v14 = a2 <= 0 || *(_BYTE *)(v13 + 3133) && a2 - 1 != *(_DWORD *)(g_MapData + 828);
        goto LABEL_29;
      }
    }
  }
  if ( a1 > 0 )
  {
    v39 = a2 + g_MapData + 20 * (a1 - 1);
    if ( *(_BYTE *)(v39 + 3534) )
    {
      if ( a2 > 0 && *(_BYTE *)(v39 + 3133) && a2 - 1 != *(_DWORD *)(g_MapData + 828) )
      {
        v14 = 2;
LABEL_29:
        v15 = DLX_GetSpriteForChar(g_BattleHudSprites, v14 + 5 * *(_DWORD *)(g_MapData + 820) + 428);
        Compat_RenderDeviceDrawMenuSprite(v2, v49, v15, 1);
        goto LABEL_30;
      }
      if ( a2 == *(_DWORD *)(g_MapData + 828) && *(_DWORD *)(g_MapData + 832) )
      {
        v14 = 4;
        goto LABEL_29;
      }
    }
  }
  if ( a2 > 0 )
  {
    v40 = (_BYTE *)(a2 + g_MapData + 20 * a1);
    if ( !v40[3134]
      && v40[3534]
      && (v40[3133] || a2 - 1 == *(_DWORD *)(g_MapData + 828) && *(_DWORD *)(g_MapData + 832)) )
    {
      v14 = 3;
      goto LABEL_29;
    }
  }
LABEL_30:
  v46 = *(__int16 *)(40 * a1 + g_MapData + 2 * a2 + 1534);
  v44 = 0;
  if ( g_ActiveUnitMoveTileIndex == v46 )
    v44 = dword_523F74;
  if ( v46 != -1 && (g_UnitTypeFlags[22 * *(__int16 *)(g_MapData + 31 * v46 + 852)] & 1) == 0 )
    UnitBattle_DrawUnitSprite(v46, v2, v49, v44);
  UnitBattle_DrawMovingUnitInAdjacentTile(a1, a2, v49, v2);
  if ( *(_BYTE *)(a2 + g_MapData + 20 * a1 + 3534) && a2 == *(_DWORD *)(g_MapData + 828) && v45 )
  {
    v16 = DLX_GetSpriteForChar(g_BattleHudSprites, v48);
    Compat_RenderDeviceDrawMenuSprite(v2, v49, v16, 1);
  }
  if ( a2 > 0 )
  {
    v17 = *(__int16 *)(40 * a1 + g_MapData + 2 * a2 + 1532);
    if ( v17 != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(40 * a1 + g_MapData + 2 * a2 + 1532)) )
      {
        v18 = 0;
        if ( v17 == g_ActiveUnitMoveTileIndex )
          v18 = dword_523F74;
        UnitBattle_DrawUnitSprite(v17, v2, v49, v18 - 64);
      }
    }
  }
  if ( a2 > 0 && a1 > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v19 = *(__int16 *)(40 * (a1 - 1) + g_MapData + 2 * a2 + 1532);
    if ( v19 == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(v19, v2, v49, dword_523F74 - 64);
    }
  }
  if ( a2 < *(_DWORD *)(g_MapData + 800) && a1 < *(_DWORD *)(g_MapData + 804) && g_ActiveUnitMoveTileIndex != -1 )
  {
    v20 = *(__int16 *)(40 * (a1 + 1) + g_MapData + 2 * a2 + 1536);
    if ( v20 == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(v20, v2, v49, dword_523F74 + 64);
    }
  }
  if ( a1 > 0 )
  {
    v21 = 40 * (a1 - 1) + g_MapData;
    v22 = *(__int16 *)(v21 + 2 * a2 + 1534);
    if ( v22 != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(v21 + 2 * a2 + 1534)) )
      {
        v23 = 0;
        if ( v22 == g_ActiveUnitMoveTileIndex )
          v23 = dword_523F74;
        UnitBattle_DrawUnitSprite(v22, v2, v49, v23);
      }
    }
  }
  if ( v46 != -1 && (g_UnitTypeFlags[22 * *(__int16 *)(g_MapData + 31 * v46 + 852)] & 1) != 0 )
    UnitBattle_DrawUnitSprite(v46, v2, v49, v44);
  if ( a2 < *(_DWORD *)(g_MapData + 800) )
  {
    v24 = 40 * a1 + g_MapData;
    v25 = *(__int16 *)(v24 + 2 * a2 + 1536);
    if ( v25 != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(v24 + 2 * a2 + 1536)) )
      {
        v26 = 0;
        if ( v25 == g_ActiveUnitMoveTileIndex )
          v26 = dword_523F74;
        UnitBattle_DrawUnitSprite(v25, v2, v49, v26 + 64);
      }
    }
  }
  if ( a2 < *(_DWORD *)(g_MapData + 800) && a1 > 0 && g_ActiveUnitMoveTileIndex != -1 )
  {
    v27 = *(__int16 *)(40 * (a1 - 1) + g_MapData + 2 * a2 + 1536);
    if ( v27 == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(v27, v2, v49, dword_523F74 + 64);
    }
  }
  if ( a2 > 0 && a1 < *(_DWORD *)(g_MapData + 804) && g_ActiveUnitMoveTileIndex != -1 )
  {
    v28 = *(__int16 *)(40 * (a1 + 1) + g_MapData + 2 * a2 + 1532);
    if ( v28 == g_ActiveUnitMoveTileIndex )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(g_ActiveUnitMoveTileIndex) )
        UnitBattle_DrawUnitSprite(v28, v2, v49, dword_523F74 - 64);
    }
  }
  if ( a1 < *(_DWORD *)(g_MapData + 804) )
  {
    v29 = 40 * (a1 + 1) + g_MapData;
    v30 = *(__int16 *)(v29 + 2 * a2 + 1534);
    if ( v30 != -1 )
    {
      if ( UnitBattle_GetSpriteVerticalOffsetPx(*(__int16 *)(v29 + 2 * a2 + 1534)) )
      {
        v31 = 0;
        if ( v30 == g_ActiveUnitMoveTileIndex )
          v31 = dword_523F74;
        UnitBattle_DrawUnitSprite(v30, v2, v49, v31);
      }
    }
  }
  if ( a1 == g_UnitBattleShotProjectileTileX && a2 == g_UnitBattleShotProjectileTileY )
  {
    v32 = DLX_GetSpriteForChar(dword_5320FC, dword_532100);
    Compat_RenderDeviceDrawMenuSprite(v2, v49, v32, 1);
  }
  if ( v46 != -1 )
  {
    if ( *(unsigned __int8 *)(g_MapData + 31 * v46 + 854) == g_CurrentPlayerIndex
      && (*(_BYTE *)(g_MapData + 31 * v46 + 874) & 1) != 0 )
    {
      v32 = DLX_GetSpriteForChar(dword_5202C8, 16);
      Compat_RenderDeviceDrawMenuSprite(v2, v49 + 2, v32, 1);
    }
    if ( v46 == g_SelectedUnitIndex && g_ActiveUnitMoveTileIndex == -1 )
    {
      v33 = DLX_GetSpriteForChar(dword_5202C8, *(unsigned __int8 *)(gameData + 140016) == 1);
      Compat_RenderDeviceDrawMenuSprite(v2, v49, v33, 1);
    }
  }
  result = gameData;
  if ( *(_DWORD *)(gameData + 147151) )
  {
    if ( a2 > *(_DWORD *)(g_MapData + 812) )
      Compat_RenderDeviceFillSolidRect(v2, v49, (unsigned __int16)(v2 + 63), v49, 1u);
    result = g_MapData;
    if ( a1 > *(_DWORD *)(g_MapData + 808) )
      return Compat_RenderDeviceFillSolidRect(v2, v49, v2, (unsigned __int16)(v49 + 63), 1u);
  }
  return result;
}
// 430878: variable 'v37' is possibly undefined
// 430180: variable 'v48' is possibly undefined
// 4303A7: variable 'v18' is possibly undefined
// 43080C: variable 'v34' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 514E54: using guessed type int dword_514E54;
// 514E58: using guessed type int dword_514E58;
// 5202C8: using guessed type int dword_5202C8;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 532048: using guessed type int g_MapData;
// 53204C: using guessed type int g_BattleHudSprites;
// 532058: using guessed type int dword_532058;
// 5320FC: using guessed type int dword_5320FC;
// 532100: using guessed type int dword_532100;
// 532104: using guessed type int dword_532104;

//----- (00430B20) --------------------------------------------------------
int  UnitBattle_RedrawTile(int a1, int a2)
{
  int result; // eax
  void *v5; // ebp
  __int16 v6; // si
  __int16 v7; // bx
  unsigned __int16 v8; // di
  unsigned __int16 v9; // [esp+4h] [ebp-10h]

  result = g_MapData;
  v5 = g_RenderDevice;
  if ( a1 < *(_DWORD *)(g_MapData + 808) + 7
    && a2 < *(_DWORD *)(g_MapData + 812) + 7
    && a1 >= *(_DWORD *)(g_MapData + 808)
    && a2 >= *(_DWORD *)(g_MapData + 812) )
  {
    v6 = ((_WORD)a1 - *(_WORD *)(g_MapData + 808)) << 6;
    v7 = *(_WORD *)(g_MapData + 812);
    v9 = (((_WORD)a2 - v7) << 6) + 16;
    g_RenderDevice = (_UNKNOWN *)dword_5202E0;
    v8 = (((_WORD)a2 - v7) << 6) + 80;
    UnitBattle_DrawTileContents(a1, a2);
    RenderState_PumpIfRectInViewBounds(g_RenderState, v6 + 32, v6 + 96, v9, v8);
    Render_FillRect((_DWORD *)dword_5202E0, 0, v9, (unsigned __int16)(v6 + 32), v6 + 95, v9 + 63, v6 + 32, v9);
    result = Render_Present((int)g_RenderState);
    g_RenderDevice = v5;
  }
  return result;
}
// 430B20: could not find valid save-restore pair for ebx
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00430C20) --------------------------------------------------------
int UnitBattle_RedrawVisibleGrid()
{
  int i; // ebx
  int j; // ecx
  int v3; // edi
  int v4; // esi
  int v5; // ebp
  int result; // eax
  int v7; // [esp+4h] [ebp-20h]
  int v8; // [esp+8h] [ebp-1Ch]

  g_RenderDevice = (_UNKNOWN *)dword_5202E0;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_grid_redraw_enter",
    *(_DWORD *)(g_MapData + 808),
    *(_DWORD *)(g_MapData + 812),
    *(_DWORD *)(g_MapData + 800),
    *(_DWORD *)(g_MapData + 804));
  for ( i = *(_DWORD *)(g_MapData + 808); i < *(_DWORD *)(g_MapData + 808) + 7; ++i )
  {
    for ( j = *(_DWORD *)(g_MapData + 812); j < *(_DWORD *)(g_MapData + 812) + 7; ++j )
    {
      if ( Diagnostics_IsBattleTileDrawTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent(
          "battle_grid_before_tile",
          i,
          j,
          *(__int16 *)(g_MapData + 40 * i + 2 * j + 1534),
          g_SelectedUnitIndex);
      UnitBattle_DrawTileContents(i, j);
      if ( Diagnostics_IsBattleTileDrawTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent(
          "battle_grid_after_tile",
          i,
          j,
          *(__int16 *)(g_MapData + 40 * i + 2 * j + 1534),
          g_SelectedUnitIndex);
    }
  }
  v7 = dword_544CFC >> byte_54512C;
  v8 = dword_544D00 >> byte_54512C;
  v3 = (dword_544CFC >> byte_54512C) + *(_DWORD *)(dword_544D14 + 12);
  v4 = *(_DWORD *)(dword_544D14 + 16) + (dword_544D00 >> byte_54512C);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_redraw_after_tiles", v7, v8, v3, v4);
  if ( dword_544CFC >> byte_54512C >= 480 || v3 <= 32 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_full_restore", v7, v8, v3, v4);
    return Render_FillRect((_DWORD *)dword_5202E0, 0, 16, 32, 0x1DFu, 0x1CFu, 0x20u, 0x10u);
  }
  v5 = dword_544D10;
  if ( dword_544CFC >> byte_54512C < 32 )
  {
    LOWORD(v7) = 32;
    if ( dword_544D10 )
      Render_Pump();
  }
  if ( v3 > 479 )
  {
    v3 = 479;
    if ( v5 )
      Render_Pump();
  }
  if ( v8 < 16 )
  {
    LOWORD(v8) = 16;
    if ( v5 )
      Render_Pump();
  }
  if ( v4 > 463 )
  {
    v4 = 463;
    if ( v5 )
      Render_Pump();
  }
  Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_top", v7, v8, v3, v4);
  Render_FillRect((_DWORD *)dword_5202E0, 0, 16, 32, 0x1DFu, v8, 0x20u, 0x10u);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_top", v7, v8, v3, v4);
  Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v8, 32, v7, v4, 0x20u, v8);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_left", v7, v8, v3, v4);
  if ( v5 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_input_flush", v7, v8, v3, v4);
    Input_Flush();
    Diagnostics_TraceWorldMapActionEvent("battle_grid_after_input_flush", v7, v8, v3, v4);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_active", v7, v8, v3, v4);
  result = Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v8, (unsigned __int16)v7, v3, v4, v7, v8);
  Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_active", v7, v8, v3, v4);
  if ( v5 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_present", v7, v8, v3, v4);
    result = Render_Present((int)g_RenderState);
    Diagnostics_TraceWorldMapActionEvent("battle_grid_after_present", v7, v8, v3, v4);
  }
  if ( v3 != 479 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_right", v7, v8, v3, v4);
    result = Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v8, (unsigned __int16)v3, 0x1DFu, v4, v3, v8);
    Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_right", v7, v8, v3, v4);
  }
  if ( v4 != 463 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_grid_before_restore_bottom", v7, v8, v3, v4);
    if ( Compat_RenderSurfaceCopyRect((_DWORD *)dword_5202E0, 0, 32, (unsigned __int16)v4, 0x1DFu, 0x1CFu, 0x20u, v4) )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_grid_after_restore_bottom", v7, v8, v3, v4);
      return result;
    }
    Diagnostics_TraceWorldMapActionEvent("battle_grid_skip_restore_bottom", v7, v8, v3, v4);
    return result;
  }
  return result;
}
// 430CD0: conditional instruction was optimized away because edi.4>=21
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D10: using guessed type int dword_544D10;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00430F80) --------------------------------------------------------
int  UnitBattle_DrawSelectedUnitPanel(int result, int a2, int a3, int a4)
{
  __int16 *v4; // esi
  int SpriteForChar; // eax
  DWORD v6; // ebp
  int v7; // eax
  char v8; // bl
  int v9; // eax
  _DWORD *Surface; // edi
  void (__fastcall **surface_methods)(_DWORD *, int);
  __int16 v11; // bx
  __int16 SpriteHeight; // ax
  int v13; // eax
  int v14; // ecx
  _DWORD *v15; // eax
  int v16; // ecx
  DWORD v17; // ebp
  _DWORD *v18; // eax
  int v19; // edi
  int v20; // edx
  int v21; // eax
  unsigned __int8 v22; // al
  int v23; // edx
  int v24; // eax
  DWORD v25; // ebp
  int v26; // edi
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // edi
  int v31; // eax
  char v32; // bl
  int v33; // ecx
  _DWORD *v34; // eax
  int v35; // eax
  int v36; // edi
  unsigned __int16 v37; // cx
  char v38[92]; // [esp+B0h] [ebp-8Ch] BYREF
  int v39; // [esp+10Ch] [ebp-30h] BYREF
  int v40; // [esp+110h] [ebp-2Ch]
  void *v41; // [esp+114h] [ebp-28h]
  DWORD v42; // [esp+120h] [ebp-1Ch]
  int i; // [esp+124h] [ebp-18h]
  int v44; // [esp+128h] [ebp-14h]
  char *(**v45)[102]; // [esp+12Ch] [ebp-10h]
  _DWORD *v46; // [esp+130h] [ebp-Ch]
  int v47; // [esp+134h] [ebp-8h]

  v40 = a2;
  v4 = 0;
  if ( result )
  {
    v4 = (__int16 *)(uintptr_t)(unsigned int)result;
  }
  else if ( g_SelectedUnitIndex != -1 )
  {
    result = 31 * g_SelectedUnitIndex;
    v4 = (__int16 *)(uintptr_t)(unsigned int)(g_MapData + 852 + 31 * g_SelectedUnitIndex);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_panel_candidate", g_SelectedUnitIndex, result, (int)(uintptr_t)v4, 0);
  if ( v4 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_panel_before_slot_read", g_SelectedUnitIndex, result, (int)(uintptr_t)v4, 0);
    result = *v4;
    Diagnostics_TraceWorldMapActionEvent("battle_panel_after_slot_read", g_SelectedUnitIndex, result, (int)(uintptr_t)v4, 0);
    if ( result != -1 )
    {
      Diagnostics_TraceWorldMapActionEvent("battle_panel_enter", result, *((unsigned __int8 *)v4 + 2), *((char *)v4 + 9), *((unsigned __int8 *)v4 + 12) & 3);
      v41 = g_RenderDevice;
      g_RenderDevice = (_UNKNOWN *)dword_5202E0;
      SpriteForChar = DLX_GetSpriteForChar(dword_5202BC, 1);
      Compat_RenderDeviceDrawMenuSprite(335, 0, SpriteForChar, 1);
      v7 = DLX_GetSpriteForChar(dword_5202BC, 3);
      v8 = 79;
      Compat_RenderDeviceDrawMenuSprite(335, 243, v7, 1);
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_frame", *v4, (int)(uintptr_t)g_RenderDevice, SpriteForChar, v7);
      v9 = *((char *)v4 + 9);
      v45 = &g_UnitTypeMetadataRecords + 22 * *v4;
      dword_53210C = v9;
      v46 = g_RenderDevice;
      if ( v9 < 100 )
      {
        Diagnostics_TraceWorldMapActionEvent("battle_panel_before_fatigue", *v4, v9, (int)(uintptr_t)v46, 0);
        Surface = (_DWORD *)Mem_Alloc(188, v9, 79, v6);
        if ( Surface )
        {
          v11 = DLX_GetSpriteWidth(dword_5202BC, 0xAu) + 1;
          SpriteHeight = DLX_GetSpriteHeight(dword_5202BC, 0xAu);
          Surface = Render_CreateSurface((int)Surface, SpriteHeight + 1, v11);
        }
        if ( Surface )
        {
          g_RenderDevice = Surface;
          v13 = DLX_GetSpriteForChar(dword_5202BC, 10);
          Compat_RenderDeviceDrawMenuSprite(0, 0, v13, 1);
          v8 = 0;
          Render_FillRect(Surface, v46, 0, 0, 88 * (100 - dword_53210C) / 100, 0x38u, 0x216u, 0x1Au);
          Compat_InvokeCompactSurfaceDestructor((int)(uintptr_t)Surface, 2);
        }
        g_RenderDevice = v46;
        Diagnostics_TraceWorldMapActionEvent("battle_panel_after_fatigue", *v4, (int)(uintptr_t)Surface, (int)(uintptr_t)g_RenderDevice, 0);
      }
      Render_ReleaseSurface(7, 0);
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_release7", *v4, (int)(uintptr_t)g_RenderDevice, 0, 0);
      v15 = (_DWORD *)Mem_Alloc(188, v14, v8, v6);
      if ( v15 )
      {
        v8 = 21;
        v15 = Render_CreateSurface((int)v15, 119, 21);
      }
      v17 = (DWORD)v15;
      v18 = (_DWORD *)Mem_Alloc(188, v16, v8, (DWORD)v15);
      if ( v18 )
        v18 = Render_CreateSurface((int)v18, 119, 21);
      v19 = (int)v18;
      g_RenderDevice = (_UNKNOWN *)v17;
      Render_FillRect((_DWORD *)dword_5202E0, (_DWORD *)v17, 69, 500, 0x26Au, 0x59u, 0, 0);
      Render_FillRect((_DWORD *)dword_5202E0, (_DWORD *)v19, 69, 500, 0x26Au, 0x59u, 0, 0);
      v47 = v19;
      UI_DrawTextFmt(v19, 0, 118, 0, 2, (int)aD_48);
      /* The x86 iterator path in Render_BlendSurfaceRect is not yet safe on SDL/x86_64. */
      Render_FillRect((_DWORD *)v19, (_DWORD *)dword_5202E0, 0, 0, 0x76u, 0x14u, 0x1F4u, 0x45u);
      Compat_InvokeCompactSurfaceDestructor((int)(uintptr_t)v17, 2);
      Compat_InvokeCompactSurfaceDestructor(v47, 2);
      g_RenderDevice = (_UNKNOWN *)dword_5202E0;
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_ap_surfaces", *v4, (int)(uintptr_t)v17, v47, (int)(uintptr_t)g_RenderDevice);
      Render_ReleaseSurface(15, 0);
      UI_DrawTextFmt(v19, 500, 618, 106, 2, (int)aD_49);
      Render_ReleaseSurface(14, 0);
      Diagnostics_TraceWorldMapActionEvent("battle_panel_after_quantity", *v4, *((unsigned __int8 *)v4 + 8), dword_53210C, 0);
      if ( *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v4 + 2) + 140051) )
      {
        if ( *((_BYTE *)v45 + 22) )
        {
          UI_IconIndexFromStats(v4);
          UI_DrawTextFmt(v19, 500, 618, 151, 2, (int)aD_50);
        }
      }
      else
      {
        v19 = DLX_GetSpriteForChar(dword_532054, (unsigned __int8)g_UnitBattlePanelQuantityIconCharBase[0] + 8);
        Compat_RenderDeviceDrawMenuSprite(498, 143, v19, 1);
      }
      if ( *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v4 + 2) + 140051) )
      {
        Unit_CalcIndexB(v4);
        UI_DrawTextFmt(v19, 500, 618, 219, 2, (int)aD_51);
      }
      else
      {
        v19 = DLX_GetSpriteForChar(dword_532054, (unsigned __int8)g_UnitBattlePanelAttackIconChar + 8);
        Compat_RenderDeviceDrawMenuSprite(497, 211, v19, 1);
      }
      if ( *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v4 + 2) + 140051) )
      {
        if ( *((_BYTE *)v45 + 25) )
        {
          Unit_GetBaseC(v4);
          UI_DrawTextFmt(v19, 500, 618, 185, 2, (int)aD_52);
        }
      }
      else
      {
        v19 = DLX_GetSpriteForChar(dword_532054, (unsigned __int8)g_UnitBattlePanelDefenseIconChar + 8);
        Compat_RenderDeviceDrawMenuSprite(497, 177, v19, 1);
      }
      if ( (unsigned int)*((char *)v4 + 11) > 4 )
      {
        v28 = *((char *)v4 + 11);
        if ( v28 < 11 || v28 > 15 )
        {
          v29 = *((char *)v4 + 11);
          if ( v29 < 16 || v29 > 20 )
          {
LABEL_33:
            v22 = UNIT_SLOT_STATUS_LEVEL(v4);
            if ( v22 )
            {
              if ( v22 <= 1u )
              {
                v23 = 5;
              }
              else
              {
                if ( v22 != 3 )
                {
LABEL_36:
                  v25 = 0;
                  v44 = 0;
                  v26 = 618 - (unsigned __int16)DLX_GetSpriteHeight(dword_5202BC, 0xDu);
                  while ( UNIT_SLOT_ORDER_STATE(v4) >= v44 )
                  {
                    v27 = DLX_GetSpriteForChar(dword_5202BC, 13);
                    Compat_RenderDeviceDrawMenuSprite(v26, 255, v27, 1);
                    v25 = ++v44;
                    v26 -= (unsigned __int16)DLX_GetSpriteHeight(dword_5202BC, 0xDu) + 1;
                  }
                  v30 = 529;
                  if ( *(_DWORD *)(1423 * *((unsigned __int8 *)v4 + 2) + gameData + 140051) )
                  {
                    for ( i = 0; *((_BYTE *)v45 + 25); v30 += 12 )
                    {
                      if ( UNIT_SLOT_REMAINING_VOLLEYS(v4) <= i )
                        break;
                      v31 = DLX_GetSpriteForChar(dword_5202BC, 11);
                      Compat_RenderDeviceDrawMenuSprite(v30, 180, v31, 1);
                      ++i;
                    }
                  }
                  else
                  {
                    v30 = DLX_GetSpriteForChar(dword_532054, (unsigned __int8)g_UnitBattlePanelVolleyIconChar + 8);
                    Compat_RenderDeviceDrawMenuSprite(497, 245, v30, 1);
                  }
                  if ( *(_DWORD *)(1423 * *((unsigned __int8 *)v4 + 2) + gameData + 140051) )
                  {
                    UI_DrawTextFmt(v30, 500, 618, 287, 2, (int)aD_53);
                  }
                  else
                  {
                    v30 = DLX_GetSpriteForChar(dword_532054, (unsigned __int8)g_UnitBattlePanelMoraleIconChar + 8);
                    Compat_RenderDeviceDrawMenuSprite(497, 279, v30, 1);
                  }
                  if ( *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v4 + 2) + 140051) )
                  {
                    UI_DrawTextFmt(v30, 500, 618, 321, 2, (int)aD_54);
                  }
                  else
                  {
                    v30 = DLX_GetSpriteForChar(dword_532054, (unsigned __int8)g_UnitPanelRow3FallbackIconChar + 8);
                    Compat_RenderDeviceDrawMenuSprite(497, 313, v30, 1);
                  }
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_before_portrait", *v4, *((unsigned __int8 *)v4 + 2), (int)(uintptr_t)g_RenderDevice, 0);
                  v32 = *((_BYTE *)v4 + 2);
                  UI_BeginUnitInfo(v38, *(_BYTE *)v4, v32);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_path", *v4, v32, (unsigned char)v38[0], (unsigned char)v38[1]);
                  v34 = (_DWORD *)Mem_Alloc(4112, v33, v32, v25);
                  if ( v34 )
                    v34 = DLXSpriteSet_Load(v34, v38);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_portrait_load", *v4, (int)(uintptr_t)v34, 0, 0);
                  v35 = DLX_GetSpriteForChar((int)v34, 0);
                  Compat_RenderDeviceDrawMenuSprite(501, 24, v35, 1);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_portrait_draw", *v4, (int)(uintptr_t)v34, v35, 0);
                  v39 = (int)(uintptr_t)v34;
                  DLXSpriteSet_ReleaseAndClear(&v39);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_portrait_free", *v4, v39, 0, 0);
                  v36 = v40;
                  RenderState_PumpIfRectInViewBounds(g_RenderState, 0x1F2u, 0x270u, 0xAu, 0x162u);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_rect", *v4, v36, 0, 0);
                  if ( v36 )
                    Render_FillRect((_DWORD *)dword_5202E0, 0, 10, 498, 0x270u, 0x162u, 0x1F2u, 0xAu);
                  Render_Present((int)g_RenderState);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_present", *v4, 0, 0, 0);
                  Tooltip_ShowText(3, UnitType_GetLocalizedName((unit_type)*v4), 0);
                  Diagnostics_TraceWorldMapActionEvent("battle_panel_after_tooltip", *v4, (int)(uintptr_t)v41, 0, 0);
                  result = 0;
                  g_RenderDevice = v41;
                  return result;
                }
                v23 = 6;
              }
            }
            else
            {
              v23 = 4;
            }
            v24 = DLX_GetSpriteForChar(dword_5202BC, v23);
            Compat_RenderDeviceDrawMenuSprite(488, 243, v24, 1);
            goto LABEL_36;
          }
          v20 = 7;
        }
        else
        {
          v20 = 8;
        }
      }
      else
      {
        v20 = 9;
      }
      v21 = DLX_GetSpriteForChar(dword_5202BC, v20);
      Compat_RenderDeviceDrawMenuSprite(498, 279, v21, 1);
      goto LABEL_33;
    }
  }
  return result;
}
// 430F80: could not find valid save-restore pair for ebx
// 430F80: could not find valid save-restore pair for edi
// 4313BD: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 43117D: variable 'v14' is possibly undefined
// 43119C: variable 'v16' is possibly undefined
// 431780: variable 'v33' is possibly undefined
// 4317EE: variable 'v37' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 514DA4: using guessed type __int16 word_514DA4[];
// 514DA6: using guessed type __int16 word_514DA6[];
// 514DC1: using guessed type char byte_514DC1;
// 514DC2: using guessed type char byte_514DC2;
// 514DC3: using guessed type char byte_514DC3;
// 514DC4: using guessed type char byte_514DC4;
// 514DC5: using guessed type char byte_514DC5;
// 5202BC: using guessed type int dword_5202BC;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;
// 532054: using guessed type int dword_532054;
// 53210C: using guessed type int dword_53210C;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00431940) --------------------------------------------------------
int  UnitBattle_ShowWallInfoPopup(int a1, int a2, int a3, int a4, DWORD a5)
{
  _DWORD *v5; // eax
  int v6; // ecx
  _DWORD *Surface; // ebp
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v10; // edx
  int SpriteForChar; // eax
  int v12; // edx
  int v13; // eax
  int v14; // eax
  char v15; // bl
  __int16 v16; // ax
  int v17; // esi
  int v18; // edx
  int v19; // ecx
  int v20; // edi
  int v21; // ecx
  unsigned int v22; // eax
  unsigned int v23; // edx
  int v24; // ecx
  int v25; // eax
  int v26; // ebx
  __int16 v27; // ax
  __int16 v28; // cx
  __int16 v29; // ax
  int v30; // ecx
  _DWORD *v31; // ebp
  unsigned __int16 v33; // [esp+3Ch] [ebp-44h]
  unsigned __int16 v34; // [esp+3Ch] [ebp-44h]
  unsigned __int16 v35; // [esp+40h] [ebp-40h]
  unsigned __int16 v36; // [esp+40h] [ebp-40h]
  unsigned __int16 v37; // [esp+44h] [ebp-3Ch]
  unsigned __int16 v38; // [esp+44h] [ebp-3Ch]
  int v39[3]; // [esp+48h] [ebp-38h]
  _DWORD *v40; // [esp+54h] [ebp-2Ch] BYREF
  int v41; // [esp+58h] [ebp-28h]
  int v42; // [esp+5Ch] [ebp-24h]
  int v43; // [esp+60h] [ebp-20h]
  int v44; // [esp+64h] [ebp-1Ch]
  _DWORD *v45; // [esp+68h] [ebp-18h]
  int v46; // [esp+6Ch] [ebp-14h]
  int v47; // [esp+70h] [ebp-10h]

  v47 = a1;
  v43 = a2;
  v42 = a4;
  v46 = a3;
  v5 = (_DWORD *)Mem_Alloc(4112, a3, a4, a5);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a4);
  v40 = v5;
  Surface = (_DWORD *)Mem_Alloc(188, v6, a4, a5);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth(dword_5202BC, 0xCu);
    SpriteHeight = DLX_GetSpriteHeight(dword_5202BC, 0xCu);
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  }
  g_RenderDevice = Surface;
  Render_ReleaseSurface(7, (DWORD)Surface);
  SpriteForChar = DLX_GetSpriteForChar(dword_5202BC, v10);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    0,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v12 = *(_DWORD *)(g_MapData + 820) + 14;
  v45 = Surface;
  v13 = DLX_GetSpriteForChar(dword_5202BC, v12);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    17,
    v13,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v39[0] = (int)g_WallInfoPopupLabelTexts[0];
  v39[1] = (int)g_WallInfoPopupLabelTexts[1];
  v39[2] = (int)g_WallInfoPopupLabelTexts[2];
  UI_DrawTextFmt((int)&v40, 51, 189, 5, 3, v39[(unsigned __int8)g_LanguageIndex]);
  Render_ReleaseSurface(14, (DWORD)Surface);
  UI_DrawTextFmt((int)&v40, 0, 111, 53, 2, (int)aD_34);
  UI_DrawTextFmt((int)&v40, 0, 177, 53, 2, (int)aD_35);
  v14 = DLX_GetSpriteForChar((int)v40, 8 * *(_DWORD *)(g_MapData + 840));
  v15 = 0;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    5,
    v14,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_Pump();
  v37 = v43;
  v35 = v47;
  v33 = DLX_GetSpriteWidth(dword_5202BC, 0xCu) - 1;
  v16 = DLX_GetSpriteHeight(dword_5202BC, 0xCu);
  v17 = 0;
  Render_FillRect(Surface, 0, 0, 0, v16 - 1, v33, v35, v37);
  g_RenderDevice = &unk_51D4C0;
  v41 = Time_Now(v19, v18);
  v20 = v43 + 5;
  v44 = v47 + 11;
  while ( DD_IsLost((int)g_RenderState) )
  {
    DD_Pump((int)g_RenderState, v15);
    v22 = Time_Now(v21, v41 + 10);
    if ( v23 < v22 )
    {
      v41 = Time_Now(v24, v23);
      v17 = (v17 + 1) % 8;
      v25 = DLX_GetSpriteForChar((int)v40, v17 + 8 * *(_DWORD *)(g_MapData + 840));
      v15 = v44;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        v20,
        v25,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
    }
  }
  v38 = v43;
  v26 = (unsigned __int16)v47;
  v36 = v47;
  v27 = DLX_GetSpriteWidth(dword_5202BC, 0xCu);
  v34 = v28 + v27 - 1;
  v29 = DLX_GetSpriteHeight(dword_5202BC, 0xCu);
  Render_FillRect((_DWORD *)dword_5202E0, 0, v30, v26, v26 + v29 - 1, v34, v36, v38);
  v31 = v45;
  Render_Present((int)g_RenderState);
  if ( v31 )
    (*(void (**)(void))v31[46])();
  return DLXSpriteSet_ReleaseAndClear((int *)&v40);
}
// 431971: variable 'v6' is possibly undefined
// 4319C7: variable 'v10' is possibly undefined
// 431B6E: variable 'v19' is possibly undefined
// 431B6E: variable 'v18' is possibly undefined
// 431BAE: variable 'v21' is possibly undefined
// 431BB5: variable 'v23' is possibly undefined
// 431BB7: variable 'v24' is possibly undefined
// 431C46: variable 'v28' is possibly undefined
// 431C6E: variable 'v30' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 514E5C: using guessed type char *off_514E5C[2];
// 5202BC: using guessed type int dword_5202BC;
// 5202E0: using guessed type int dword_5202E0;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00431CC0) --------------------------------------------------------
__int16 UnitBattle_UpdateIdleAnimatedUnits()
{
  int slot_index;
  unsigned char *slot;
  int unit_type;
  unsigned int next_animation_tick;
  unsigned char animation_state;
  __int16 result;

  result = 0;
  slot = (unsigned char *)(uintptr_t)(unsigned int)(g_MapData + 0x354);
  for ( slot_index = 0; slot_index < 22; ++slot_index, slot += UNIT_STACK_SLOT_STRIDE )
  {
    unit_type = *(__int16 *)slot;
    if ( unit_type != -1 )
    {
      if ( (g_UnitTypeHasIdleAnimationFlags[88 * unit_type] & 1) != 0 )
      {
        next_animation_tick = *(unsigned int *)(slot + 0x12) + (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * unit_type];
        if ( next_animation_tick < Time_Now(slot_index, (int)(uintptr_t)slot) )
        {
          *(unsigned int *)(slot + 0x12) = Time_Now(slot_index, (int)(uintptr_t)slot);
          animation_state = slot[0x11] & 0xF8;
          slot[0x11] = animation_state | (((slot[0x11] & 7) + 1) & 7);
          result = UnitBattle_RedrawUnitFootprint(slot_index);
          continue;
        }
      }
    }
    result = UnitBattle_CountAdjacentEnemies((int)(uintptr_t)slot);
    if ( result >= 3 && unit_type != -1 )
    {
      next_animation_tick = *(unsigned int *)(slot + 0x12) + (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * unit_type];
      if ( next_animation_tick < Time_Now(slot_index, (int)(uintptr_t)slot) )
      {
        *(unsigned int *)(slot + 0x12) = Time_Now(slot_index, (int)(uintptr_t)slot);
        result = UnitBattle_RedrawUnitFootprint(slot_index);
      }
    }
  }
  if ( dword_532060 && g_SelectedUnitIndex != g_ActiveUnitMoveTileIndex )
    result = UnitBattle_RedrawUnitFootprint(g_SelectedUnitIndex);
  return result;
}
// 431D15: variable 'v6' is possibly undefined
// 431D15: variable 'v2' is possibly undefined
// 431D1A: variable 'v8' is possibly undefined
// 431D46: variable 'v10' is possibly undefined
// 431D50: variable 'v12' is possibly undefined
// 431DA6: variable 'v15' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 512360: using guessed type int dword_512360;
// 532048: using guessed type int g_MapData;
// 532060: using guessed type int dword_532060;

//----- (00431DE0) --------------------------------------------------------
__int16  UnitBattle_RedrawUnitFootprint(int a1)
{
  __int16 *slot;
  unsigned int unit_type;
  unsigned __int16 tile_x;
  unsigned __int16 tile_y;
  unsigned __int8 facing;
  __int16 result;

  slot = (__int16 *)(31 * a1 + g_MapData + 852);
  unit_type = (unsigned __int16)*slot;
  result = *slot;
  if ( unit_type <= 0x28 )
  {
    tile_x = (unsigned __int16)slot[2];
    tile_y = (unsigned __int16)slot[3];
    result = UnitBattle_RedrawTile(tile_x, tile_y);
    if ( g_UnitTypeSpriteVerticalOffsetPx[88 * unit_type] && unit_type >= 0x1B )
    {
      if ( unit_type == 0x1B )
      {
        facing = *((unsigned __int8 *)slot + 3);
        switch ( facing )
        {
          case 0:
          case 4:
            UnitBattle_RedrawTile(tile_x - 1, tile_y);
            result = UnitBattle_RedrawTile(tile_x + 1, tile_y);
            break;
          case 1:
            UnitBattle_RedrawTile(tile_x + 1, tile_y);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          case 2:
          case 6:
            UnitBattle_RedrawTile(tile_x, tile_y - 1);
            result = UnitBattle_RedrawTile(tile_x, tile_y + 1);
            break;
          case 3:
            UnitBattle_RedrawTile(tile_x + 1, tile_y);
            UnitBattle_RedrawTile(tile_x, tile_y + 1);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          case 5:
            UnitBattle_RedrawTile(tile_x - 1, tile_y);
            UnitBattle_RedrawTile(tile_x, tile_y + 1);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          case 7:
            UnitBattle_RedrawTile(tile_x - 1, tile_y);
            result = UnitBattle_RedrawTile(tile_x, tile_y - 1);
            break;
          default:
            break;
        }
      }
      else if ( unit_type == 30 )
      {
        UnitBattle_RedrawTile(tile_x + 1, tile_y);
        UnitBattle_RedrawTile(tile_x, tile_y - 1);
        UnitBattle_RedrawTile(tile_x - 1, tile_y);
        result = UnitBattle_RedrawTile(tile_x, tile_y + 1);
      }
    }
  }
  return result;
}
// 431DFC: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 431E17: variable 'v4' is possibly undefined
// 431E5E: variable 'v5' is possibly undefined
// 431E89: variable 'v6' is possibly undefined
// 431EB0: variable 'v7' is possibly undefined
// 431ED7: variable 'v8' is possibly undefined
// 431EE9: variable 'v9' is possibly undefined
// 431F10: variable 'v10' is possibly undefined
// 431F22: variable 'v11' is possibly undefined
// 431F49: variable 'v12' is possibly undefined
// 431F70: variable 'v13' is possibly undefined
// 431F7E: variable 'v14' is possibly undefined
// 431F94: variable 'v15' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00431FB0) --------------------------------------------------------
unsigned int  UnitBattle_RedrawUnitNeighborhood(int a1)
{
  __int16 *slot;
  unsigned int result;
  unsigned __int16 tile_x;
  unsigned __int16 tile_y;

  slot = (__int16 *)(31 * a1 + g_MapData + 852);
  result = (unsigned __int16)*slot;
  if ( result <= 0x28 )
  {
    tile_x = (unsigned __int16)slot[2];
    tile_y = (unsigned __int16)slot[3];
    UnitBattle_RedrawTile(tile_x, tile_y);
    result = UnitBattle_GetSpriteVerticalOffsetPx(a1);
    if ( result )
    {
      UnitBattle_RedrawTile(tile_x, tile_y - 1);
      UnitBattle_RedrawTile(tile_x, tile_y + 1);
      UnitBattle_RedrawTile(tile_x - 1, tile_y);
      UnitBattle_RedrawTile(tile_x + 1, tile_y);
      UnitBattle_RedrawTile(tile_x - 1, tile_y - 1);
      UnitBattle_RedrawTile(tile_x - 1, tile_y + 1);
      UnitBattle_RedrawTile(tile_x + 1, tile_y - 1);
      return UnitBattle_RedrawTile(tile_x + 1, tile_y + 1);
    }
  }
  return result;
}
// 431FCD: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 431FFC: variable 'v4' is possibly undefined
// 43200E: variable 'v5' is possibly undefined
// 43201C: variable 'v6' is possibly undefined
// 43202E: variable 'v7' is possibly undefined
// 432044: variable 'v8' is possibly undefined
// 432057: variable 'v9' is possibly undefined
// 43206A: variable 'v10' is possibly undefined
// 43207D: variable 'v11' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00432090) --------------------------------------------------------
int  BuildingGarrisonDialog_HandleExitButtonPress(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  unk_53211C = v4;
  return result;
}
// 43209B: variable 'v4' is possibly undefined

//----- (00432120) --------------------------------------------------------
__int16  Battle_PlaceReservedUnitSlotAtTile(int a1, int a2, int a3)
{
  int v3; // edi
  char v4; // al

  v3 = g_MapData + 1503;
  qmemcpy((void *)(g_MapData + 1503), (const void *)a1, 0x1Cu);
  v3 += 28;
  *(_WORD *)v3 = *(_WORD *)(a1 + 28);
  *(_BYTE *)(v3 + 2) = *(_BYTE *)(a1 + 30);
  *(_WORD *)(g_MapData + 1507) = a2;
  *(_WORD *)(g_MapData + 1509) = a3;
  if ( *(_DWORD *)(g_MapData + 804) / 2 < a2 )
    v4 = 6;
  else
    v4 = 2;
  *(_BYTE *)(g_MapData + 1506) = v4;
  *(_WORD *)(g_MapData + 40 * a2 + 2 * a3 + 1534) = 21;
  g_UnitFadeAnimUnitIndex = 21;
  return UnitBattle_RedrawUnitFootprint(21);
}
// 514E48: using guessed type int dword_514E48;
// 532048: using guessed type int g_MapData;

//----- (004321D0) --------------------------------------------------------
int Battle_ClearReservedUnitSlot()
{
  int result; // eax
  int v1; // ebx
  int v2; // ecx
  int v3; // edx
  bool v4; // si

  result = g_MapData;
  v1 = *(__int16 *)(g_MapData + 1503);
  if ( v1 != -1 )
  {
    v2 = *(unsigned __int16 *)(g_MapData + 1507);
    v3 = *(unsigned __int16 *)(g_MapData + 1509);
    v4 = g_UnitTypeSpriteVerticalOffsetPx[88 * v1] != 0;
    *(_WORD *)(g_MapData + 1503) = -1;
    *(_WORD *)(g_MapData + 40 * (unsigned __int16)v2 + 2 * (unsigned __int16)v3 + 1534) = -1;
    g_UnitFadeAnimUnitIndex = -1;
    if ( v4 )
      return UnitBattle_RedrawVisibleGrid();
    else
      return UnitBattle_RedrawTile(v2, v3);
  }
  return result;
}
// 514E48: using guessed type int dword_514E48;
// 532048: using guessed type int g_MapData;

//----- (00432770) --------------------------------------------------------
signed int Battle_RestoreSavedActionPointsBeforeResultCopy()
{
  signed int result; // eax
  int v1; // edx
  int v2; // ebx

  result = 0;
  v1 = 0;
  do
  {
    ++result;
    v2 = v1 + g_MapData;
    v1 += 31;
    *(_BYTE *)(v2 + 860) = g_BattleSavedActionPointsBySlot[result - 1];
  }
  while ( result < 22 );
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (004327B0) --------------------------------------------------------
signed int  Battle_PlaceUnit(unsigned __int8 *a1, int a2, char a3, int a4)
{
  int v5; // ecx
  int v6; // edx
  int i; // eax
  int v8; // eax
  int v9; // edi

  Debug_Log(a2, a4, (DWORD)a1, (int)aBattle_placeun);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_place_unit_enter",
    *(__int16 *)a1,
    a1[2],
    a2,
    a4);
  if ( *(__int16 *)(40 * a2 + g_MapData + 2 * a4 + 1534) != -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "battle_place_unit_occupied",
      *(__int16 *)a1,
      a2,
      a4,
      *(__int16 *)(40 * a2 + g_MapData + 2 * a4 + 1534));
    return 0;
  }
  v6 = 0;
  for ( i = 0; i < 682; i += 31 )
  {
    if ( *(__int16 *)(g_MapData + i + 852) == -1 )
      break;
    ++v6;
  }
  v8 = 31 * v6;
  qmemcpy((void *)(g_MapData + 31 * v6 + 852), a1, 0x1Fu);
  *(_WORD *)(g_MapData + v8 + 856) = a2;
  *(_WORD *)(g_MapData + v8 + 858) = a4;
  *(_BYTE *)(g_MapData + v8 + 855) = a3;
  g_BattleSavedActionPointsBySlot[v6] = a1[8];
  v9 = g_MapData;
  *(_BYTE *)(g_MapData + v8 + 860) = g_UnitTypeBaseActionPoints_512580[88 * *(__int16 *)a1];
  *(_BYTE *)(g_MapData + v8 + 874) &= ~1u;
  *(_BYTE *)(g_MapData + v8 + 864) &= 0x8Fu;
  *(_WORD *)(40 * a2 + g_MapData + 2 * a4 + 1534) = v6;
  *(_DWORD *)(g_MapData + 4 * a1[2] + 3944) = v6;
  g_SelectedUnitIndex = v6;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_place_unit_placed",
    v6,
    *(__int16 *)a1,
    a1[2],
    a2);
  UnitBattle_RedrawVisibleGrid();
  UnitBattle_DrawSelectedUnitPanel(0, 1, a4, v9);
  return 1;
}
// 4327DE: variable 'v5' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 532048: using guessed type int g_MapData;

//----- (00432910) --------------------------------------------------------
int BuildingGarrisonDialog_CountSelectedSlots()
{
  int v0; // edx
  int i; // eax

  v0 = 0;
  for ( i = 0; i != 12; ++i )
  {
    if ( g_BuildingGarrisonDialogSelectedSlots[i] )
      ++v0;
  }
  return v0;
}
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[];

//----- (00432940) --------------------------------------------------------
void * BuildingGarrisonDialog_DrawSlotGrid(int a1)
{
  int v1; // esi
  unsigned __int8 v2; // al
  int v3; // esi
  int v4; // edi
  int v5; // eax
  DWORD v6; // ebp
  int v7; // edx
  char v8; // cl
  int v9; // eax
  int v10; // eax
  int v11; // ebp
  int v12; // edi
  void *result; // eax
  int v14; // eax
  int SpriteForChar; // edx
  unsigned __int8 v16[4]; // [esp+74h] [ebp-38h] BYREF
  int v17; // [esp+78h] [ebp-34h]
  int v18; // [esp+7Ch] [ebp-30h]
  int v19; // [esp+80h] [ebp-2Ch]
  int v20; // [esp+84h] [ebp-28h]
  void *v21; // [esp+88h] [ebp-24h]
  int v22; // [esp+8Ch] [ebp-20h]
  int v23; // [esp+90h] [ebp-1Ch]
  int slot_record;
  int slot_status_bits;

  v23 = a1;
  v21 = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)dword_5321F8;
  v1 = *(_DWORD *)(dword_5321F8 + 184);
  v16[0] = -1;
  v16[1] = -1;
  v16[2] = -1;
  v16[3] = 0;
  v2 = Render_ApplyColorTripletBytes(g_BuildingGarrisonDialogResourceHandle, v16);
  Surface_DrawRectOutline((unsigned __int16 *)(uintptr_t)(unsigned int)dword_5321F8, 0, 32, 0, 63, (unsigned char)v2);
  v3 = 0;
  g_RenderDevice = (_UNKNOWN *)dword_5202E0;
  do
  {
    if ( v23 != -1 )
      v3 = v23;
    v17 = 71 * (v3 % 6) + 126;
    v4 = 131 * (v3 / 6) + 75;
    slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * v3 + 18;
    if ( UNIT_SLOT_TYPE(slot_record) == -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 15);
      Compat_RenderDeviceDrawMenuSprite(v17, v4, SpriteForChar, 1);
      goto LABEL_13;
    }
    v19 = 4 * v3;
    if ( !g_BuildingGarrisonDialogSlotSpriteSets[v3] )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 15);
      Compat_RenderDeviceDrawMenuSprite(v17, v4, SpriteForChar, 1);
      goto LABEL_13;
    }
    v5 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogSlotSpriteSets[v3], dword_5321C4[v3]);
    Compat_RenderDeviceDrawMenuSprite(v17, v4, v5, 1);
    v6 = *(int *)((char *)g_BuildingGarrisonDialogSelectedSlots + v19);
    if ( v6 )
    {
      v7 = 23;
    }
    else
    {
      if ( BuildingGarrisonDialog_CountSelectedSlots() < 10 )
        goto LABEL_8;
      v7 = 24;
    }
    SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, v7);
    Compat_RenderDeviceDrawMenuSprite(v17, v4, SpriteForChar, 1);
LABEL_8:
    Render_ReleaseSurface(5, v6);
    v8 = BUILDING_GARRISON_SERVICE_STATE(g_BuildingGarrisonDialogActiveBuilding, v3);
    v22 = v17 + 15;
    if ( (v8 & BUILDING_GARRISON_REPAIR_TURNS_MASK) != 0 )
    {
      v9 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 14);
      Compat_RenderDeviceDrawMenuSprite(v17, v4, v9, 1);
      slot_status_bits = (unsigned char)v8;
      UI_DrawText(v22, 131 * (v3 / 6) + 75, (int)aD_55, (slot_status_bits & BUILDING_GARRISON_REPAIR_TURNS_MASK) >> 3);
    }
    else if ( (v8 & BUILDING_GARRISON_TRAINING_TURNS_MASK) != 0 )
    {
      v14 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 13);
      Compat_RenderDeviceDrawMenuSprite(v17, v4, v14, 1);
      UI_DrawText(v22, 131 * (v3 / 6) + 75, (int)aD_56, (unsigned char)v8 & BUILDING_GARRISON_TRAINING_TURNS_MASK);
    }
    UI_DrawTextFmt(v4, v17, v17 + 33, 131 * (v3 / 6) + 125, 3, (int)aD_57, (signed char)UNIT_SLOT_HEALTH_PERCENT(slot_record));
    if ( g_BuildingGarrisonDialogPendingExitCountdown && g_BuildingGarrisonDialogSelectedSlots[v3] )
    {
      v10 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 22 - g_BuildingGarrisonDialogPendingExitCountdown);
      Compat_RenderDeviceDrawMenuSprite(v17, v4, v10, 1);
    }
LABEL_13:
    v18 = dword_544D10;
    v11 = (unsigned __int16)v17;
    v19 = (unsigned __int16)(v17 + 32);
    v20 = (unsigned __int16)v4;
    RenderState_PumpIfRectInViewBounds(g_RenderState, v17, v17 + 32, v4, 131 * (v3 / 6) + 138);
    v12 = 131 * (v3 / 6) + 139;
    Render_FillRect((_DWORD *)dword_5202E0, 0, v20, v11, v19, 131 * (v3 / 6) + 139, v11, v20);
    if ( v18 )
      Render_Present((int)g_RenderState);
    if ( v23 != -1 )
      break;
    ++v3;
  }
  while ( v3 < 12 );
  g_RenderDevice = &unk_51D4C0;
  Render_ReleaseSurface(5, (DWORD)&unk_51D4C0);
  UI_DrawTextFmt(v12, 545, 613, 53, 3, (int)aD_58, *(_DWORD *)(g_BuildingGarrisonDialogActiveBuilding + 438));
  result = v21;
  g_RenderDevice = v21;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 532144: using guessed type int dword_532144;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];
// 532194: using guessed type int g_BuildingGarrisonDialogSlotSpriteSets[];
// 5321C4: using guessed type int dword_5321C4[12];
// 5321F4: using guessed type int g_BuildingGarrisonDialogPendingExitCountdown;
// 5321F8: using guessed type int dword_5321F8;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00432D30) --------------------------------------------------------
int  BuildingGarrisonDialog_ReloadSlotSprite(int result, int a2, int a3, DWORD a4)
{
  int slot_index;
  int slot_record;
  int sprite_set;
  char sprite_path[104];

  (void)a2;
  (void)a3;
  slot_index = result;
  if ( slot_index == -1 )
    return 0;
  if ( g_BuildingGarrisonDialogSlotSpriteSets[slot_index] )
  {
    nfree_(g_BuildingGarrisonDialogSlotSpriteSets[slot_index]);
    g_BuildingGarrisonDialogSlotSpriteSets[slot_index] = 0;
  }
  slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * slot_index;
  if ( *(__int16 *)(slot_record + 18) == -1 )
    return 0;
  Unit_BuildGarrisonSlotIconSpritePath(sprite_path, *(_BYTE *)(slot_record + 18), slot_index);
  sprite_set = Mem_Alloc(4112, 0, 0, a4);
  if ( sprite_set )
    sprite_set = (int)DLXSpriteSet_Load((_DWORD *)sprite_set, sprite_path);
  g_BuildingGarrisonDialogSlotSpriteSets[slot_index] = sprite_set;
  return sprite_set;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532194: using guessed type int g_BuildingGarrisonDialogSlotSpriteSets[];

//----- (00432DC0) --------------------------------------------------------
void * BuildingGarrisonDialog_RebuildSlotSprites(int a1, DWORD a2)
{
  int i; // edx

  for ( i = 0; i < 12; ++i )
    BuildingGarrisonDialog_ReloadSlotSprite(i, i + 1, a1, a2);
  return BuildingGarrisonDialog_DrawSlotGrid(-1);
}

//----- (00432DF0) --------------------------------------------------------
void * BuildingGarrisonDialog_TickExitCountdown(int a1, double a2)
{
  int now;
  int i;
  int staged_slots[14];
  int staged_count;
  int countdown_frame;

  (void)a1;
  now = Time_Now(0, 0);
  if ( (unsigned int)now < (unsigned int)(dword_532138 + 10) )
    return (void *)(uintptr_t)(unsigned int)now;
  dword_532138 = now;
  for ( i = 0; i < 12; ++i )
    dword_5321C4[i] = (dword_5321C4[i] + 1) & 7;
  countdown_frame = g_BuildingGarrisonDialogPendingExitCountdown;
  if ( countdown_frame )
  {
    ++g_BuildingGarrisonDialogPendingExitCountdown;
    if ( countdown_frame == 7 )
    {
      staged_count = 0;
      g_BuildingGarrisonDialogPendingExitCountdown = 0;
      for ( i = 0; i < 12; ++i )
      {
        if ( g_BuildingGarrisonDialogSelectedSlots[i] )
          staged_slots[staged_count++] = i;
      }
      staged_slots[staged_count] = -1;
      if ( staged_count )
      {
        Building_UnitsLeave((unsigned __int8 *)g_BuildingGarrisonDialogActiveBuilding, staged_slots, a2);
        memset(g_BuildingGarrisonDialogSelectedSlots, 0, sizeof(g_BuildingGarrisonDialogSelectedSlots));
      }
    }
  }
  return BuildingGarrisonDialog_DrawSlotGrid(-1);
}
// 532138: using guessed type int dword_532138;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532158: using guessed type int g_BuildingGarrisonDialogSelectedSlots[12];
// 5321C0: using guessed type int dword_5321C0[];
// 5321C4: using guessed type int dword_5321C4[12];
// 5321F4: using guessed type int g_BuildingGarrisonDialogPendingExitCountdown;

//----- (00432ED0) --------------------------------------------------------
void *BuildingGarrisonDialog_DrawSelectedUnitPanel()
{
  int v0; // edi
  __int16 v1; // ax
  int v2; // eax
  void *result; // eax
  char v4; // al
  int v5; // edx
  int v6; // eax
  char *v7; // esi
  int v8; // edx
  int SpriteForChar; // eax
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  __int16 SpriteWidth; // ax
  __int16 SpriteHeight; // ax
  unsigned __int16 v16; // di
  unsigned __int16 v17; // si
  int v18; // eax
  unsigned __int16 v19; // ax
  __int16 v20; // ax
  int v21; // eax
  unsigned __int16 v22; // ax
  __int16 v23; // ax
  int v24; // edi
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // edi
  int v29; // edx
  int v30; // edi
  int v31; // esi
  unsigned __int8 v32; // al
  int v33; // edx
  int v34; // eax
  int v35; // esi
  int v36; // eax
  int v37; // eax
  int v38; // eax
  unsigned __int16 v39; // [esp-Ch] [ebp-38h]
  unsigned __int16 v40; // [esp-4h] [ebp-30h]
  unsigned __int16 v41; // [esp-4h] [ebp-30h]
  unsigned __int8 v42[2]; // [esp+0h] [ebp-2Ch] BYREF
  char v43[2]; // [esp+2h] [ebp-2Ah] BYREF
  int v44; // [esp+4h] [ebp-28h]
  int v45; // [esp+8h] [ebp-24h]
  __int16 *v46; // [esp+Ch] [ebp-20h]
  int v47; // [esp+10h] [ebp-1Ch]
  void *v48; // [esp+14h] [ebp-18h]
  int v49; // [esp+18h] [ebp-14h]
  int v50; // [esp+1Ch] [ebp-10h]
  int v51; // [esp+20h] [ebp-Ch]
  int v52; // [esp+24h] [ebp-8h]
  int v53; // [esp+28h] [ebp-4h]
  _DWORD savedregs[6]; // [esp+2Ch] [ebp+0h] BYREF
  const char *selected_unit_name;

  v48 = g_RenderDevice;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() && g_BuildingGarrisonDialogSelectedSlotIndex != -1 )
    fprintf(
      stderr,
      "[barracks] selected_panel_draw_enter selected=%d sprite_set=%08x\n",
      g_BuildingGarrisonDialogSelectedSlotIndex,
      g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedSlotIndex != -1
    && *(__int16 *)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18) != -1 )
  {
    g_RenderDevice = (_UNKNOWN *)dword_5202E0;
    v42[0] = -31;
    strcpy(v43, "d");
    v42[1] = -47;
    v4 = Render_ApplyColorTripletBytes(g_BuildingGarrisonDialogResourceHandle, v42);
    TextSprite_ActivateResourceSlot(3, v4, (DWORD)savedregs);
    v45 = 289;
    v46 = (__int16 *)(31
                    * g_BuildingGarrisonDialogSelectedSlotIndex
                    + g_BuildingGarrisonDialogActiveBuilding
                    + 18);
    v5 = 88 * *v46;
    v51 = 220;
    v6 = *(__int16 *)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
    v7 = (char *)&g_UnitTypeMetadataRecords + v5;
    if ( v6 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v6 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
      v8 = 33;
    else
      v8 = 10;
    selected_unit_name = UnitType_GetLocalizedName((unit_type)v6);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_draw_body type=%d frame_sprite=%d\n", v6, v8);
    SpriteForChar = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, v8);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_frame_sprite ptr=%08x\n", SpriteForChar);
    v10 = *((_DWORD *)g_RenderDevice + 46);
    Compat_RenderDeviceDrawMenuSprite(v45, v51, SpriteForChar, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_frame_drawn\n");
    Render_ReleaseSurface(7, 0);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_after_release7\n");
    v11 = *(__int16 *)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
    if ( v11 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v11 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
    {
      UI_DrawTextFmt(
        v10,
        v45 + 64,
        v45 + 162,
        v51 + 8,
        3,
        selected_unit_name);
      UI_DrawTextFmt(v10, v45 + 15, v45 + 88, v51 + 32, 2, (int)aD_67, (unsigned char)v7[24]);
      v12 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 34);
      Compat_RenderDeviceDrawMenuSprite(v45 + 93, v51 + 20, v12, 1);
LABEL_10:
      if ( !g_BuildingGarrisonDialogSelectedUnitSpriteSet )
      {
        if ( Diagnostics_IsWorldMapClickTraceEnabled() )
          fprintf(stderr, "[barracks] selected_panel_missing_unit_sprite selected=%d\n", g_BuildingGarrisonDialogSelectedSlotIndex);
        goto LABEL_4;
      }
      v13 = DLX_GetSpriteForChar(
              g_BuildingGarrisonDialogSelectedUnitSpriteSet,
              g_BuildingGarrisonDialogSelectedUnitAnimFrame);
      Compat_RenderDeviceDrawMenuSprite(v45 + 8, v51 + 6, v13, 0);
      v47 = dword_544D10;
      SpriteWidth = DLX_GetSpriteWidth(g_BuildingGarrisonDialogUiSpriteSet, 0xAu);
      v41 = v45 + 4 + SpriteWidth;
      SpriteHeight = DLX_GetSpriteHeight(g_BuildingGarrisonDialogUiSpriteSet, 0xAu);
      v16 = v51;
      v17 = v45;
      RenderState_PumpIfRectInViewBounds(g_RenderState, v51, v51 + 49 + SpriteHeight, v45, v41);
      v18 = *(__int16 *)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
      if ( v18 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v18 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        v19 = 33;
      else
        v19 = 10;
      v20 = DLX_GetSpriteWidth(g_BuildingGarrisonDialogUiSpriteSet, v19);
      v39 = v45 - 1 + v20;
      v21 = *(__int16 *)(g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex + 18);
      if ( v21 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v21 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        v22 = 33;
      else
        v22 = 10;
      v23 = DLX_GetSpriteHeight(g_BuildingGarrisonDialogUiSpriteSet, v22);
      Render_FillRect(
        (_DWORD *)dword_5202E0,
        &unk_51D4C0,
        (unsigned __int16)v51,
        (unsigned __int16)v45,
        v39,
        v51 + v23 - 1,
        v17,
        v16);
      if ( !v47 )
        goto LABEL_4;
      Render_Present((int)g_RenderState);
      result = v48;
      g_RenderDevice = v48;
      return result;
    }
    v24 = *((_DWORD *)g_RenderDevice + 46);
    UI_DrawTextFmt(v24, v45 + 64, v45 + 192, v51 + 5, 3, selected_unit_name);
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      fprintf(stderr, "[barracks] selected_panel_name_drawn name=%s\n", selected_unit_name);
    UI_DrawTextFmt(v24, v45 + 85, v45 + 105, v51 + 50, 2, (int)aD_59, (unsigned char)v7[24]);
    v29 = Unit_CalcIndexB(v46);
    UI_DrawTextFmt(v24, v45 + 132, v45 + 148, v51 + 95, 2, (int)aD_60, v29);
    if ( (unsigned int)*((char *)v46 + 11) > 4 )
    {
      v37 = *((char *)v46 + 11);
      if ( v37 >= 11 && v37 <= 15 )
      {
        v27 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 27);
        v26 = v51;
        v24 = *((_DWORD *)g_RenderDevice + 46);
      }
      else
      {
        v38 = *((char *)v46 + 11);
        if ( v38 < 16 || v38 > 20 )
          goto LABEL_22;
        v27 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 26);
        v26 = v51;
        v24 = *((_DWORD *)g_RenderDevice + 46);
      }
    }
    else
    {
      v25 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 28);
      v26 = v51;
      v44 = *((_DWORD *)g_RenderDevice + 46);
      v27 = v25;
      v24 = v44;
    }
    Compat_RenderDeviceDrawMenuSprite(v45 + 106, v26 + 21, v27, 0);
LABEL_22:
    UI_DrawTextFmt(v24, v45 + 132, v45 + 148, v51 + 50, 2, (int)aD_61, (signed char)UNIT_SLOT_MORALE((intptr_t)v46));
    v28 = v45;
    UI_DrawTextFmt(v24, v45 + 160, v45 + 191, v51 + 50, 2, (int)aD_62, (signed char)UNIT_SLOT_FATIGUE((intptr_t)v46));
    v30 = v28 + 105;
    v49 = v51 + 95;
    v50 = v45 + 85;
    if ( v7[25] )
    {
      if ( v7[22] )
      {
        v29 = UI_IconIndexFromStats(v46);
        v31 = v50;
        UI_DrawTextFmt(v30, v50, v30, v51 + 74, 2, (int)aD_65, v29);
        v29 = Unit_GetBaseC(v46);
        UI_DrawTextFmt(v30, v31, v30, v49, 2, (int)aD_66, v29);
      }
      else
      {
        v25 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 12);
        Compat_RenderDeviceDrawMenuSprite(v45 + 62, v51 + 65, v25, 1);
        v29 = Unit_GetBaseC(v46);
        UI_DrawTextFmt(v30, v50, v30, v49, 2, (int)aD_64, v29);
      }
    }
    else
    {
      v25 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 11);
      v44 = *((_DWORD *)g_RenderDevice + 46);
      Compat_RenderDeviceDrawMenuSprite(v45 + 62, v51 + 65, v25, 1);
      v29 = UI_IconIndexFromStats(v46);
      UI_DrawTextFmt(v30, v50, v30, v49, 2, (int)aD_63, v29);
    }
    v32 = v46[6] & 3;
    if ( v32 )
    {
      if ( v32 <= 1u )
      {
        v33 = 30;
      }
      else
      {
        if ( v32 != 3 )
        {
LABEL_28:
          v53 = 0;
          v35 = v51 + 71;
          v52 = v45 + 178;
          while ( (unsigned __int8)(16 * *((_BYTE *)v46 + 12)) >> 6 >= v53 )
          {
            v36 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 32);
            Compat_RenderDeviceDrawMenuSprite(v52, v35, v36, 1);
            v35 += 10;
            ++v53;
          }
          goto LABEL_10;
        }
        v33 = 31;
      }
    }
    else
    {
      v33 = 29;
    }
    v34 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, v33);
    Compat_RenderDeviceDrawMenuSprite(v45 + 149, v51 + 65, v34, 0);
    goto LABEL_28;
  }
  v0 = dword_544D10;
  g_RenderDevice = &unk_51D4C0;
  v40 = DLX_GetSpriteWidth(g_BuildingGarrisonDialogUiSpriteSet, 0x19u) + 289;
  v1 = DLX_GetSpriteHeight(g_BuildingGarrisonDialogUiSpriteSet, 0x19u);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xDCu, v1 + 220, 0x121u, v40);
  v2 = DLX_GetSpriteForChar(g_BuildingGarrisonDialogUiSpriteSet, 25);
  Compat_RenderDeviceDrawMenuSprite(289, 220, v2, 0);
  if ( !v0 )
  {
LABEL_4:
    result = v48;
    g_RenderDevice = v48;
    return result;
  }
  Render_Present((int)g_RenderState);
  result = v48;
  g_RenderDevice = v48;
  return result;
}
// 43334D: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 4333F6: variable 'v29' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 5202E0: using guessed type int dword_5202E0;
// 532144: using guessed type int dword_532144;
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 532188: using guessed type int g_BuildingGarrisonDialogSelectedSlotIndex;
// 53218C: using guessed type int g_BuildingGarrisonDialogSelectedUnitSpriteSet;
// 532190: using guessed type int g_BuildingGarrisonDialogSelectedUnitAnimFrame;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (004336C0) --------------------------------------------------------
void  BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets(int a1, char a2, DWORD a3)
{
  int slot_record;
  int sprite_set;
  int palette_entries[256];
  int palette_index;
  char asset_path[104];

  (void)a1;
  (void)a2;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[barracks] selected_assets_enter selected=%d current_sprite=%08x\n",
      g_BuildingGarrisonDialogSelectedSlotIndex,
      g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_BuildingGarrisonDialogSelectedUnitSpriteSet);
  if ( g_BuildingGarrisonDialogSelectedSlotIndex != -1 )
  {
    slot_record = g_BuildingGarrisonDialogActiveBuilding + 31 * g_BuildingGarrisonDialogSelectedSlotIndex;
    if ( *(__int16 *)(slot_record + 18) != -1 )
    {
      Unit_BuildSelectedUnitPanelIconSpritePath(asset_path, *(_BYTE *)(slot_record + 18), g_BuildingGarrisonDialogActiveBuilding);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[barracks] selected_assets_unit_path idx=%d type=%d path=%s\n",
          g_BuildingGarrisonDialogSelectedSlotIndex,
          *(__int16 *)(slot_record + 18),
          asset_path);
      sprite_set = Mem_Alloc(4112, 0, a2, a3);
      if ( sprite_set )
        sprite_set = (int)DLXSpriteSet_Load((_DWORD *)sprite_set, asset_path);
      g_BuildingGarrisonDialogSelectedUnitSpriteSet = sprite_set;
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_unit_loaded sprite_set=%08x\n", sprite_set);
      Unit_BuildSelectedUnitPanelIconPalettePath(asset_path, *(_BYTE *)(slot_record + 18), g_BuildingGarrisonDialogActiveBuilding);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_palette_path path=%s\n", asset_path);
      Compat_LoadPalCOLIntoTable(palette_entries, asset_path, a3);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_palette_loaded\n");
      for ( palette_index = 224; palette_index <= 255; ++palette_index )
        *(_DWORD *)(g_BuildingGarrisonDialogResourceHandle + 4 * palette_index) = palette_entries[palette_index];
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_palette_copied\n");
      Palette_ApplyWithBrightnessOffset((int *)&unk_51D4C0, (const void *)(uintptr_t)(unsigned int)g_BuildingGarrisonDialogResourceHandle);
      BuildingGarrisonDialog_DrawSelectedUnitPanel();
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_panel_drawn\n");
      BuildingGarrisonDialog_ReloadSlotSprite(g_BuildingGarrisonDialogSelectedSlotIndex, 0, 0, a3);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(stderr, "[barracks] selected_assets_slot_reloaded\n");
    }
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[barracks] selected_assets_done\n");
}
// 532150: using guessed type int g_BuildingGarrisonDialogActiveBuilding;
// 532154: using guessed type int dword_532154;
// 532188: using guessed type int g_BuildingGarrisonDialogSelectedSlotIndex;
// 53218C: using guessed type int g_BuildingGarrisonDialogSelectedUnitSpriteSet;

//----- (004337E0) --------------------------------------------------------
void *__thiscall BuildingGarrisonDialog_AnimateSelectedUnit(void *this)
{
  int now;

  (void)this;
  now = Time_Now(0, 0);
  if ( (unsigned int)now < (unsigned int)(dword_53213C + 10) )
    return (void *)(uintptr_t)(unsigned int)now;
  dword_53213C = now;
  g_BuildingGarrisonDialogSelectedUnitAnimFrame = ((_BYTE)g_BuildingGarrisonDialogSelectedUnitAnimFrame + 1) & 7;
  return BuildingGarrisonDialog_DrawSelectedUnitPanel();
}
// 53213C: using guessed type int dword_53213C;
// 532190: using guessed type int g_BuildingGarrisonDialogSelectedUnitAnimFrame;

//----- (00433820) --------------------------------------------------------
int BuildingGarrisonDialog_HitTestSlotGrid()
{
  int v0; // eax
  int v1; // ebx
  int v2; // ecx
  int v3; // eax

  v0 = dword_544CFC >> byte_54512C;
  if ( dword_544CFC >> byte_54512C >= 126
    && dword_544D00 >> byte_54512C >= 75
    && (v1 = (dword_544D00 >> byte_54512C) - 75, (v0 - 126) % 71 <= 33)
    && v1 % 131 <= 64
    && (v2 = (v0 - 126) / 71, v3 = v1 / 131, v2 < 6)
    && v3 <= 1 )
  {
    return v2 + 6 * v3;
  }
  else
  {
    return -1;
  }
}
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

