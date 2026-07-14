/* Clash strategic rules integration, host functions, campaign, and AI.
 * Original function-marker range: 0x004506B0..0x004612E0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004506B0) --------------------------------------------------------
int  Queen_FindEligibleBirthHostBuilding(int a1)
{
  int v2; // eax
  int v3; // ebx
  int v4; // ecx

  v2 = 0;
LABEL_2:
  v3 = UNIT_RECORD(v2);
  if ( (unsigned int)*(char *)(v3 + 4) < 4 && *(__int16 *)(v3 + 16) != -1 )
  {
    v4 = *(char *)(gameData + BUILDING_RECORD_SIZE * v2 + 509678);
    if ( (v4 == 2 || v4 == 1) && *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v2 + 509676) == a1 )
      return UNIT_RECORD(v2);
  }
  while ( ++v2 < 100 )
  {
    if ( v2 >= 0 )
      goto LABEL_2;
  }
  return 0;
}
// 450722: conditional instruction was optimized away because eax.4<64u
// 4506D2: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;

//----- (00450760) --------------------------------------------------------
extern char aQueen_newtur_0[];
extern char aQueen_newtur_1[];
extern char aQueen_newtur_2[];
extern char aQueen_newtur_3[];
extern char aP_posla[];
extern char g_QueenDepartureEventMessageBuffer[];
extern char *g_QueenDepartureTexts[];
extern char *g_QueenCastleTreasuryTheftTexts[];
extern char *g_QueenCastleWellPoisoningTexts[];
extern char *g_QueenCastleArsonTexts[];
extern __int16 g_QueenWhimRecords_5191F0;

int  Queen_NewTurn(int a1, int a2, char a3, double a4)
{
  int result; // eax
  int v6; // ecx
  char *v7; // edi
  char *v8; // esi
  char v9; // al
  char v10; // al
  unsigned int v11; // kr04_4
  __int16 v12; // ax
  int v13; // ecx
  __int16 v14; // bx
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  __int16 v18; // ax
  int v19; // ecx
  __int16 v20; // dx
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  signed int v26; // eax
  int v27; // eax
  int v28; // edx
  int v29; // ecx
  signed int v30; // eax
  int v31; // edx
  int v32; // eax
  char v33; // bh
  int v34; // edx
  int v35; // ecx
  signed int v36; // eax
  int v37; // edx
  unsigned int v38; // eax
  int v39; // eax
  int v40; // ecx
  int v41; // ecx
  int v42; // eax
  int v43; // eax
  int v44; // [esp-4h] [ebp-1Ch]
  int v45[3]; // [esp+0h] [ebp-18h]
  int v46[3]; // [esp+Ch] [ebp-Ch]
  _DWORD savedregs[6]; // [esp+18h] [ebp+0h] BYREF

  result = gameData;
  if ( ACTIVE_MISSION_INDEX != 6 )
  {
    Debug_Log(a1, a2, (DWORD)savedregs, (int)aQueen_newturn, v45[0]);
    result = PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex);
    if ( result != -1 )
    {
      if ( PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) )
      {
        if ( result == QUEEN_RELATIONSHIP_STATE_CHILDBIRTH_PENDING )
        {
          Debug_Log(g_CurrentPlayerIndex, a2, (DWORD)savedregs, (int)aQueen_newturnN, v45[0]);
          a2 = (char)((Rng_RandRange(0, 100) <= 0x32) + 33);
          v21 = Queen_FindEligibleBirthHostBuilding(g_CurrentPlayerIndex);
          if ( v21 )
          {
            Building_CreateSpecialPersonageGarrisonUnit(v21, a2, v21, a2, a4);
            PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) = 5;
            if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
            {
              v45[0] = (int)g_QueenSonBirthTexts[0];
              v45[1] = (int)g_QueenSonBirthTexts[1];
              v45[2] = (int)g_QueenSonBirthTexts[2];
              v44 = v21 + 5;
              v46[0] = (int)g_QueenDaughterBirthTexts[0];
              v46[1] = (int)g_QueenDaughterBirthTexts[1];
              v46[2] = (int)g_QueenDaughterBirthTexts[2];
              if ( a2 == 33 )
                sprintf_(&g_QueenBirthMessageBuffer, (const char *)v45[(unsigned __int8)g_LanguageIndex], v44);
              else
                sprintf_(&g_QueenBirthMessageBuffer, (const char *)v46[(unsigned __int8)g_LanguageIndex], v44);
              UI_ShowInfoWindow((const char *)&g_QueenBirthMessageBuffer, 0, v23, (DWORD)savedregs, (int)savedregs, (int)&g_QueenDaughterBirthTexts[3]);
            }
          }
        }
        else if ( result == 1 )
        {
          Debug_Log(g_CurrentPlayerIndex, a2, (DWORD)savedregs, (int)aQueen_newturnK, v45[0]);
          PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) = -1;
          switch ( Rng_RandRange(0, 3) )
          {
            case 0u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_0, 0);
              v7 = g_QueenDepartureEventMessageBuffer;
              v8 = g_QueenDepartureTexts[(unsigned __int8)g_LanguageIndex];
              do
              {
                v9 = *v8;
                *v7 = *v8;
                if ( !v9 )
                  break;
                v10 = v8[1];
                v8 += 2;
                v7[1] = v10;
                v7 += 2;
              }
              while ( v10 );
              break;
            case 1u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_1, 1);
              v26 = Unit_FindById(g_CurrentPlayerIndex);
              if ( v26 != -1 )
              {
                v27 = BUILDING_RECORD_SIZE * v26;
                *(_DWORD *)(gameData + v27 + 510112) = 0;
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleTreasuryTheftTexts[(unsigned __int8)g_LanguageIndex],
                  gameData + BUILDING_TABLE_OFFSET + v27 + 5);
              }
              break;
            case 2u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_2, 2);
              v30 = Unit_FindById(g_CurrentPlayerIndex);
              if ( v30 != -1 )
              {
                v31 = BUILDING_RECORD_SIZE * v30;
                v32 = gameData + BUILDING_RECORD_SIZE * v30;
                v33 = *(_BYTE *)(v32 + 510109) & 0xF8;
                *(_BYTE *)(v32 + 510109) = v33;
                *(_BYTE *)(v32 + 510109) = v33 | 5;
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleWellPoisoningTexts[(unsigned __int8)g_LanguageIndex],
                  v31 + gameData + BUILDING_TABLE_OFFSET + 5);
              }
              break;
            case 3u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_3, 3);
              v36 = Unit_FindById(g_CurrentPlayerIndex);
              if ( v36 != -1 )
              {
                Building_Destroy(UNIT_RECORD(v36), a2, (DWORD)savedregs, a4);
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleArsonTexts[(unsigned __int8)g_LanguageIndex],
                  UNIT_RECORD(v36) + 5);
              }
              break;
            default:
              break;
          }
          v11 = strlen(g_QueenDepartureEventMessageBuffer) + 1;
          if ( v11 != 1 )
            Queen_ShowMessageDialog((int)g_QueenDepartureEventMessageBuffer, v11 - 1, a2, (DWORD)savedregs);
        }
        result = PLAYER_DATA(g_CurrentPlayerIndex);
        if ( GAME_TURN_COUNTER >= *(_WORD *)(result + 141445) )
        {
          if ( *(_DWORD *)(result + 140051) )
          {
            v38 = Rng_RandRange(0, 24);
            Debug_Log(v38, a2, (DWORD)savedregs, (int)aQueen_newturnZ, v38);
            v39 = Player_CalcAvailableStrongholdFunds(g_CurrentPlayerIndex);
            if ( Queen_ShowWhimDecisionDialog(
                   g_QueenWhimRecords[v38].texts[(unsigned __int8)g_LanguageIndex],
                   g_QueenWhimRecords[v38].required_stronghold_funds,
                   7 * v38,
                   v39,
                   (DWORD)savedregs) )
            {
              Player_SpendStrongholdFundsEvenly(g_CurrentPlayerIndex, g_QueenWhimRecords[v38].required_stronghold_funds);
              v42 = PLAYER_DATA(g_CurrentPlayerIndex);
              if ( *(char *)(v42 + 141443) < 9 )
                ++*(_BYTE *)(v42 + 141443);
            }
            else
            {
              v43 = PLAYER_DATA(g_CurrentPlayerIndex);
              if ( *(char *)(v43 + 141443) > 1 )
                --*(_BYTE *)(v43 + 141443);
            }
            goto LABEL_18;
          }
          if ( ACTIVE_MISSION_INDEX != 14 )
          {
            if ( *(char *)(result + 141443) < 9 )
              ++*(_BYTE *)(result + 141443);
LABEL_18:
            result = gameData;
            PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN(g_CurrentPlayerIndex) = GAME_TURN_COUNTER + Rng_RandRange(5, 8);
          }
        }
      }
      else
      {
        result = AI_TickNationPostTurn(g_CurrentPlayerIndex);
        if ( result >= 1000 )
        {
          PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) = Rng_RandRange(0, 8);
          v15 = 1;
          if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
          {
            Diagnostics_TraceWorldMapActionEvent(
              "queen_proposal_transition_enter",
              g_SelectedUnitIndex,
              result,
              ACTIVE_MISSION_INDEX,
              GAME_TURN_COUNTER);
            Win_PlayModeChangeFrameTransition((int)aP_posla, 1, gameData, a2, (DWORD)savedregs, a3);
            Diagnostics_TraceWorldMapActionEvent(
              "queen_proposal_dialog_enter",
              g_SelectedUnitIndex,
              result,
              ACTIVE_MISSION_INDEX,
              GAME_TURN_COUNTER);
            v15 = Queen_ShowMarriageProposalDialog(0, a2, (DWORD)savedregs);
            Diagnostics_TraceWorldMapActionEvent(
              "queen_proposal_dialog_return",
              g_SelectedUnitIndex,
              v15,
              ACTIVE_MISSION_INDEX,
              GAME_TURN_COUNTER);
          }
          v16 = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
          if ( v15 )
          {
            *(_BYTE *)(v16 + gameData + 141443) = 5;
            result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
            PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN(g_CurrentPlayerIndex) = GAME_TURN_COUNTER + Rng_RandRange(5, 8);
          }
          else
          {
            result = gameData;
            *(_BYTE *)(v16 + gameData + 141443) = -1;
          }
        }
      }
    }
  }
  return result;
}
// 450811: variable 'v6' is possibly undefined
// 4508D4: variable 'v13' is possibly undefined
// 450978: variable 'v17' is possibly undefined
// 4509A1: variable 'v19' is possibly undefined
// 450A58: variable 'v22' is possibly undefined
// 450A81: variable 'v23' is possibly undefined
// 450AAC: variable 'v24' is possibly undefined
// 450AAC: variable 'v25' is possibly undefined
// 450B18: variable 'v28' is possibly undefined
// 450B18: variable 'v29' is possibly undefined
// 450B94: variable 'v34' is possibly undefined
// 450B94: variable 'v35' is possibly undefined
// 450BC5: variable 'v37' is possibly undefined
// 450C21: variable 'v40' is possibly undefined
// 450C48: variable 'v41' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char byte_511130;
// 5191BC: using guessed type char *off_5191BC[12];
// 5191C8: using guessed type char *off_5191C8[9];
// 5191D4: using guessed type char *off_5191D4[6];
// 5191E0: using guessed type char *off_5191E0[3];
// 5191F0: using guessed type __int16 word_5191F0;
// 5191F2: using guessed type char *off_5191F2[3];
// 519350: using guessed type char *off_519350[9];
// 51935C: using guessed type char *off_51935C[6];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00450CE0) --------------------------------------------------------
int  Player_Surrender(int a1, int a2, DWORD a3, double a4)
{
  int v5; // edx
  int v6; // eax
  int v7; // edx
  int result; // eax

  Debug_Log(a2, a1, a3, (int)aPlayer_surrend);
LABEL_2:
  v6 = UNIT_RECORD(v5);
  if ( (unsigned int)*(char *)(v6 + 4) < 4
    && *(__int16 *)(v6 + 16) != -1
    && *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v5 + 509676) == a1 )
  {
    Building_Destroy(UNIT_RECORD(v5), a1, a3, a4);
  }
  while ( ++v5 < 100 )
  {
    if ( v5 >= 0 )
      goto LABEL_2;
  }
  v7 = 0;
LABEL_10:
  if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v7 + 147180) <= 0x28
    && *(unsigned __int8 *)(UNIT_STACK_STRIDE * v7 + gameData + 147178) == a1 )
  {
    UnitStack_KillByIndex(v7, a1, a3, a4);
  }
  while ( ++v7 < 500 )
  {
    if ( v7 >= 0 )
      goto LABEL_10;
  }
  result = gameData;
  *(_DWORD *)(PLAYER_DATA_STRIDE * a1 + gameData + PLAYER_RUNTIME_STATE_OFFSET) = 0;
  return result;
}
// 450D50: conditional instruction was optimized away because edx.4<64u
// 450DC7: conditional instruction was optimized away because edx.4<1F4u
// 450D0E: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 450D7F: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 450CF6: variable 'v5' is possibly undefined
// 450DB4: variable 'v7' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00450DF0) --------------------------------------------------------
int  AI_ComputeNationStrengthPercent(
        signed int a1,
        int a2,
        DWORD a3,
        double a4)
{
  signed int v4; // ecx
  int result; // eax
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // ebx
  signed int i; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ebx
  const char *v16; // edi
  int v17; // ecx
  _BYTE v18[200]; // [esp+0h] [ebp-E4h] BYREF
  int v19[7]; // [esp+C8h] [ebp-1Ch]

  v19[5] = a2;
  v4 = a1;
  result = 0;
LABEL_2:
  v6 = UNIT_RECORD(result);
  if ( (unsigned int)*(char *)(v6 + 4) >= 4
    || *(__int16 *)(v6 + 16) == -1
    || (v7 = gameData + BUILDING_RECORD_SIZE * result, !*(_BYTE *)(v7 + 509678))
    || *(unsigned __int8 *)(v7 + 509676) != v4 )
  {
    while ( ++result < 100 )
    {
      if ( result >= 0 )
        goto LABEL_2;
    }
    v8 = 0;
LABEL_10:
    if ( (unsigned int)*(__int16 *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + 6) > 0x28
      || *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * v8 + 147178) != v4
      || (result = UnitStack_HasBuilder(v8)) == 0 )
    {
      while ( ++v8 < 500 )
      {
        if ( v8 >= 0 )
          goto LABEL_10;
      }
      v9 = 0;
      for ( i = 0; i < 5; ++i )
      {
        if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * i + PLAYER_RUNTIME_STATE_OFFSET) )
        {
          v11 = Player_CalcMilitaryStrength(i);
          if ( v11 > v9 )
            v9 = v11;
        }
      }
      result = 100 * Player_CalcMilitaryStrength(v4) / v9;
      if ( result < 10 )
      {
        Player_Surrender(v12, v12, a3, a4);
        v14 = 0;
        for ( result = 0; result < 5; ++result )
        {
          v15 = gameData + PLAYER_DATA_STRIDE * result;
          if ( *(_DWORD *)(v15 + 140051) && *(_DWORD *)(v15 + 140024) )
            v14 = 1;
        }
        if ( v14 )
        {
          v19[0] = (int)g_AllyEliminatedNoticeTexts[0];
          v19[1] = (int)g_AllyEliminatedNoticeTexts[1];
          v19[2] = (int)g_AllyEliminatedNoticeTexts[2];
          v16 = (const char *)v19[(unsigned __int8)g_LanguageIndex];
          sprintf_(v18, v16, PLAYER_DATA_STRIDE * v13 + gameData + PLAYER_RUNTIME_STATE_OFFSET + 4);
          return UI_ShowInfoWindow((const char *)v18, 0, v17, a3, (int)v16, (int)&g_AllyEliminatedNoticeTexts[3]);
        }
      }
    }
  }
  return result;
}
// 450E62: conditional instruction was optimized away because eax.4<64u
// 450ED7: conditional instruction was optimized away because edx.4<1F4u
// 450E18: simplified comparisons for 'ebx.4': <0 || >=4 became >=4u
// 450E94: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 450EC2: variable 'v4' is possibly undefined
// 450EC4: variable 'v8' is possibly undefined
// 450F18: variable 'i' is possibly undefined
// 450F36: variable 'v12' is possibly undefined
// 450F73: variable 'v13' is possibly undefined
// 450FBA: variable 'v17' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 519368: using guessed type char *off_519368[3];
// 5202E4: using guessed type int gameData;

//----- (00450FD0) --------------------------------------------------------
int  Player_CheckForDefeatAndHandleElimination(int a1, DWORD a2)
{
  int v3; // edx
  int v4; // eax
  int v6; // edx
  int v7; // eax
  int v10; // eax
  int v11; // edx

  v3 = 0;
LABEL_2:
  if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v3 + 147180) <= 0x28 )
  {
    v4 = *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * v3 + 147178);
    if ( v4 == a1 )
      return a1 ^ v4;
  }
  while ( ++v3 < 500 )
  {
    if ( v3 >= 0 )
      goto LABEL_2;
  }
  v6 = 0;
LABEL_9:
  v7 = UNIT_RECORD(v6);
  if ( (unsigned int)*(char *)(v7 + 4) < 4
    && *(__int16 *)(v7 + 16) != -1
    && (*(_BYTE *)(gameData + BUILDING_RECORD_SIZE * v6 + 509678) || Building_CountGarrison(UNIT_RECORD(v6))) )
  {
    v4 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v6 + 509676);
    if ( v4 == a1 )
      return a1 ^ v4;
  }
  while ( ++v6 < 100 )
  {
    if ( v6 >= 0 )
      goto LABEL_9;
  }
  *(_DWORD *)(PLAYER_DATA_STRIDE * a1 + gameData + PLAYER_RUNTIME_STATE_OFFSET) = 0;
  Render_Pump();
  Audio_StopMainMusic();
  Video_PlayAviWithModeGuard((int)aArama1, aKon_por1);
  v10 = 0;
  while ( 1 )
  {
    v11 = gameData + PLAYER_DATA_STRIDE * v10;
    if ( *(_DWORD *)(v11 + 140024) )
    {
      if ( *(_DWORD *)(v11 + 140051) )
        break;
    }
    if ( ++v10 >= 5 )
      return 1;
  }
  Music_PlayMainMapTrack(*(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET), v11, gameData, a2);
  return 0;
}
// 451044: conditional instruction was optimized away because edx.4<1F4u
// 4510BC: conditional instruction was optimized away because edx.4<64u
// 451001: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 451069: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 451093: variable 'v6' is possibly undefined
// 451102: variable 'v9' is possibly undefined
// 451102: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00451150) --------------------------------------------------------
signed int  Player_CheckSoleSurvivorAndShowVictoryBanner(int a1)
{
  int v2; // eax
  int v3; // ecx
  signed int v4; // edx
  int v5; // ecx

  v2 = 0;
  v3 = PLAYER_DATA_STRIDE * a1;
  while ( !*(_DWORD *)(gameData + v2 + PLAYER_RUNTIME_STATE_OFFSET) || v2 == v3 )
  {
    v2 += PLAYER_DATA_STRIDE;
    if ( v2 >= 7115 )
    {
      Render_Pump();
      Audio_StopMainMusic();
      Palette_FadeOutToBlack((int *)&g_MainRenderDevice, v4);
      g_RenderDevice = &g_MainRenderDevice;
      (*(void (**)(void))(g_RenderDeviceDisplayContextPtr + 56))();
      Video_PlayAviWithModeGuard(v5, aZwy01);
      return 1;
    }
  }
  return 0;
}

signed int UI_CheckEndTurnHotkey(int a1)
{
  return Player_CheckSoleSurvivorAndShowVictoryBanner(a1);
}
// 45119B: variable 'v4' is possibly undefined
// 4511BB: variable 'v5' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 51D578: using guessed type int dword_51D578;
// 5202E4: using guessed type int gameData;

//----- (004511D0) --------------------------------------------------------
void  Options_ApplyInGameSliders(int a1, DWORD a2)
{
  *(_BYTE *)(gameData + 147173) = ((unsigned __int16)(((_WORD)g_OptionsInGameMusicVolumeRaw << 7)
                                                    - (__CFSHL__(g_OptionsInGameMusicVolumeRaw << 7 >> 31, 8)
                                                     + ((unsigned __int16)(g_OptionsInGameMusicVolumeRaw << 7 >> 31) << 8))) >> 8)
                                - 64;
  *(_BYTE *)(gameData + 147172) = (unsigned __int16)(16 * g_OptionsInGameSoundVolumeRaw
                                                   - (__CFSHL__((16 * g_OptionsInGameSoundVolumeRaw) >> 31, 8)
                                                    + ((unsigned __int16)((16 * g_OptionsInGameSoundVolumeRaw) >> 31) << 8))) >> 8;
  Options_ApplyRecordSettings(gameData + 147147, a1, a2);
}
// 51938C: using guessed type int dword_51938C;
// 5193D4: using guessed type int dword_5193D4;
// 5202E4: using guessed type int gameData;

//----- (00451230) --------------------------------------------------------
int  Options_HandleCloseButtonInGame(int a1)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_InGameOptionsDialogExitSignal = v3;
  return result;
}
// 45123B: variable 'v3' is possibly undefined
// 54453C: using guessed type int dword_54453C;

//----- (00451250) --------------------------------------------------------
unsigned __int16 * Options_InitInGameSlidersAndWidgets(int a1, int a2, DWORD a3)
{
  int v4; // ecx

  UIWidget_PlayPressedReleaseAnimation(a1);
  if ( (*(_BYTE *)(v4 - 98) & 2) == 0 )
  {
    *(_DWORD *)(v4 - 98) = 2;
    UIWidget_RefreshActionButtonState(v4 - 106, v4);
  }
  if ( (*(_BYTE *)(v4 - 151) & 2) == 0 )
  {
    *(_DWORD *)(v4 - 151) = 2;
    UIWidget_RefreshActionButtonState(v4 - 159, v4);
  }
  if ( (*(_BYTE *)(v4 - 204) & 2) == 0 )
  {
    *(_DWORD *)(v4 - 204) = 2;
    UIWidget_RefreshActionButtonState(v4 - 212, v4);
  }
  if ( (*(_BYTE *)(v4 - 257) & 1) == 0 )
  {
    *(_DWORD *)(v4 - 257) = 1;
    UIWidget_RefreshActionButtonState(v4 - 265, v4);
  }
  g_OptionsInGameMusicVolumeRaw = 128;
  g_OptionsInGameScrollSpeedRaw = 128;
  g_OptionsInGameSoundVolumeRaw = 128;
  return Options_DrawAllSliderThumbs(g_InGameSliderThumbPositions, a2, a3);
}
// 451259: variable 'v4' is possibly undefined
// 519380: using guessed type unsigned __int16 word_519380[6];
// 51938C: using guessed type int dword_51938C;
// 5193B0: using guessed type int dword_5193B0;
// 5193D4: using guessed type int dword_5193D4;

//----- (00451310) --------------------------------------------------------
BOOL  Options_ToggleCheckboxInGame(int a1)
{
  char v2; // dl

  v2 = *(_BYTE *)(a1 + 8) ^ 1;
  *(_BYTE *)(a1 + 8) = v2;
  *(_BYTE *)(a1 + 8) = v2 ^ 2;
  Audio_PlayButtonSound(*(char **)(a1 + 49));
  return Render_Begin((int)g_RenderState, 0);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00451340) --------------------------------------------------------
int  Options_RunInGameSettingsDialog(int a1, char a2, DWORD a3)
{
  _DWORD *v4; // eax
  int v5; // ebp
  int v6; // eax
  int v7; // ecx
  char *v8; // edi
  char *v9; // esi
  int v10; // ebx
  int v11; // eax
  int SpriteForChar; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  _BYTE v17[29]; // [esp+1h] [ebp-1B1h]
  int ( *v18)(int, char, DWORD); // [esp+1Eh] [ebp-194h]
  char v19[8]; // [esp+22h] [ebp-190h] BYREF
  int v20; // [esp+2Ah] [ebp-188h]
  _DWORD v21[11]; // [esp+32h] [ebp-180h]
  int v22; // [esp+5Fh] [ebp-153h]
  int v23; // [esp+94h] [ebp-11Eh]
  int v24; // [esp+C9h] [ebp-E9h]
  int (*v25)(); // [esp+196h] [ebp-1Ch]

  v4 = (_DWORD *)Mem_Alloc(4112, a1, a2, a3);
  if ( v4 )
    v4 = DLXSpriteSet_Load(v4, a2);
  g_InGameOptionsSpriteSet = (int)v4;
  v5 = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  v18 = Render_DefaultRH;
  *(_DWORD *)&v17[25] = aStdrh_19;
  v25 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(92, a2, v5, (int)aSetrhS08x_24);
  v6 = 0;
  qmemcpy(v19, &g_InGameSettingsButtonWidgetsTemplate, 4 * v7);
  v9 = (char *)&g_InGameSettingsButtonWidgetsTemplate + 4 * v7;
  v8 = &v19[4 * v7];
  *(_WORD *)v8 = *(_WORD *)v9;
  v8[2] = v9[2];
  do
  {
    *(_DWORD *)((char *)v21 + v6) += (unsigned __int8)g_LanguageIndex;
    v10 = *(_DWORD *)((char *)&v21[1] + v6);
    v6 += 53;
    *(_DWORD *)&v17[v6] = (unsigned __int8)g_LanguageIndex + v10;
  }
  while ( v6 != 212 );
  if ( *(_DWORD *)(gameData + 147159) )
    v20 = 2;
  if ( *(_DWORD *)(gameData + 147147) )
    v22 = 2;
  if ( *(_DWORD *)(gameData + 147163) )
    v23 = 2;
  if ( *(_DWORD *)(gameData + 147167) )
    v24 = 2;
  v11 = (*(char *)(gameData + 147173) << 8) + 0x4000;
  g_OptionsInGameMusicVolumeRaw = (v11 - (__CFSHL__(v11 >> 31, 7) + (v11 >> 31 << 7))) >> 7;
  g_OptionsInGameScrollSpeedRaw = ((*(unsigned __int8 *)(gameData + 147171) << 8)
                - (__CFSHL__(*(unsigned __int8 *)(gameData + 147171) << 8 >> 31, 4)
                 + 16 * (*(unsigned __int8 *)(gameData + 147171) << 8 >> 31))) >> 4;
  g_OptionsInGameSoundVolumeRaw = ((*(unsigned __int8 *)(gameData + 147172) << 8)
                - (__CFSHL__(*(unsigned __int8 *)(gameData + 147172) << 8 >> 31, 4)
                 + 16 * (*(unsigned __int8 *)(gameData + 147172) << 8 >> 31))) >> 4;
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar(g_InGameOptionsSpriteSet, (unsigned __int8)g_LanguageIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    82,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UIWidgetTable_InitDrawStates(v19);
  Options_DrawAllSliderThumbs(g_InGameSliderThumbPositions, 132, v5);
  g_InGameOptionsDialogExitSignal = v13;
  do
  {
    DD_Pump((int)g_RenderState, 132);
    UIWidgetTable_PollHoverAndActions(v19, v5);
    Options_AnimateAllSliderThumbs(g_InGameSliderThumbPositions);
  }
  while ( v14 == g_InGameOptionsDialogExitSignal );
  *(_DWORD *)(gameData + 147159) = v20 == 2;
  *(_DWORD *)(gameData + 147147) = v22 == 2;
  *(_DWORD *)(gameData + 147163) = v23 == 2;
  *(_DWORD *)(gameData + 147167) = v24 == 2;
  *(_BYTE *)(gameData + 147173) = ((unsigned __int16)(((_WORD)g_OptionsInGameMusicVolumeRaw << 7)
                                                    - (__CFSHL__(g_OptionsInGameMusicVolumeRaw << 7 >> 31, 8)
                                                     + ((unsigned __int16)(g_OptionsInGameMusicVolumeRaw << 7 >> 31) << 8))) >> 8)
                                - 64;
  *(_BYTE *)(gameData + 147171) = (unsigned __int16)(16 * g_OptionsInGameScrollSpeedRaw
                                                   - (__CFSHL__((16 * g_OptionsInGameScrollSpeedRaw) >> 31, 8)
                                                    + ((unsigned __int16)((16 * g_OptionsInGameScrollSpeedRaw) >> 31) << 8))) >> 8;
  *(_BYTE *)(gameData + 147172) = (unsigned __int16)(16 * g_OptionsInGameSoundVolumeRaw
                                                   - (__CFSHL__((16 * g_OptionsInGameSoundVolumeRaw) >> 31, 8)
                                                    + ((unsigned __int16)((16 * g_OptionsInGameSoundVolumeRaw) >> 31) << 8))) >> 8;
  Options_ApplyRecordSettings(gameData + 147147, v14, v5);
  Options_DestroySliderThumbList(g_InGameSliderThumbPositions);
  v18 = (int ( *)(int, char, DWORD))g_RenderHook;
  Debug_Log(v15, (char)g_RenderHook, v5, (int)aUnsetrh08x_24);
  g_RenderHook = v25;
  Render_SetResourceHandle((int)&g_MainRenderDevice, v5);
  WorldMap_RedrawViewport(1);
  return DLXSpriteSet_ReleaseAndClear(&g_InGameOptionsSpriteSet);
}
// 4513B8: variable 'v7' is possibly undefined
// 4514FE: variable 'v13' is possibly undefined
// 451524: variable 'v14' is possibly undefined
// 45161B: variable 'v15' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519380: using guessed type unsigned __int16 word_519380[6];
// 51938C: using guessed type int dword_51938C;
// 5193B0: using guessed type int dword_5193B0;
// 5193D4: using guessed type int dword_5193D4;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 54453C: using guessed type int dword_54453C;
// 544540: using guessed type int dword_544540;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00451690) --------------------------------------------------------
int Cheat_RevealMapForCurrentPlayer()
{
  Map_RevealAllTilesForPlayer(g_CurrentPlayerIndex);
  return WorldMap_RedrawViewport(1);
}
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004516B0) --------------------------------------------------------
void Cheat_FillSelectedSquadWithCannons()
{
  int i; // esi
  signed int v2; // eax
  signed int v3; // ecx

  if ( g_SelectedUnitIndex != -1 )
  {
    for ( i = 0; ; i += 31 )
    {
      v2 = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( v3 >= v2 )
        break;
      UnitSlot_InitFromType(
        i + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 6,
        UNIT_TYPE_CANNON,
        *(_BYTE *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147178));
    }
    WorldMap_RedrawViewport(1);
  }
}
// 4516DE: variable 'v3' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00451730) --------------------------------------------------------
signed int Cheat_ClearSelectedSquadDamageFlags()
{
  signed int result; // eax
  int v1; // edx
  signed int v2; // ecx

  if ( g_SelectedUnitIndex != -1 )
  {
    while ( 1 )
    {
      result = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( v2 >= result )
        break;
      *(_BYTE *)(v1 + UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147192) |= 3u;
      *(_BYTE *)(v1 + 31 + UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147161) = *(_BYTE *)(v1
                                                                              + UNIT_STACK_STRIDE * g_SelectedUnitIndex
                                                                              + gameData
                                                                              + 147192) & 0xF3;
    }
  }
  return result;
}
// 45175D: variable 'v2' is possibly undefined
// 451770: variable 'v1' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (004517B0) --------------------------------------------------------
void Cheat_ForceWinCurrentMission()
{
  g_CheatForceWinMissionFlag = 1;
}
// 5448A0: using guessed type int dword_5448A0;

//----- (004517C0) --------------------------------------------------------
void Cheat_HealSelectedSquadAndClearDamage()
{
  signed int v0; // eax
  int v1; // ecx
  signed int v2; // edx

  if ( g_SelectedUnitIndex != -1 )
  {
    while ( 1 )
    {
      v0 = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( v2 >= v0 )
        break;
      *(_BYTE *)(v1 + 31 + gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147158) = 100;
    }
  }
  // 4517CA: falls through to the shared epilogue loc_4517A0 (pop edx/ecx/ebx; retn)
  // shared with sub_451730; in C this is the function return.
  return;
}
// 4517CA: control flows out of bounds to 4517A0
// 4517ED: variable 'v2' is possibly undefined
// 4517FF: variable 'v1' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00451810) --------------------------------------------------------
int  Cheat_KillUnitOrBuildingUnderCursor(DWORD a1, double a2)
{
  int result; // eax
  unsigned int v3; // edx

  result = gameData
         + 200
         * ((((g_MouseCursorRawX >> g_CursorCoordShift)
            - 32
            - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
             + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
          + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET));
  v3 = *(unsigned __int16 *)(result
                           + 2
                           * ((((g_MouseCursorRawY >> g_CursorCoordShift)
                              - 16
                              - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                               + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
                            + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET))
                           + 556374);
  if ( (unsigned __int16)v3 != 0xFFFF )
  {
    if ( v3 > 0x1F4 || (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v3 + 147180) > 0x28 )
    {
      Building_Destroy(BUILDING_RECORD_SIZE * (v3 - 0x8000) + gameData + BUILDING_TABLE_OFFSET, gameData, a1, a2);
      return WorldMap_RedrawViewport(1);
    }
    else
    {
      UnitStack_KillByIndex(v3, gameData, a1, a2);
      return WorldMap_RedrawViewport(1);
    }
  }
  return result;
}
// 451891: simplified comparisons for 'edx.4': <0 || >=1F5 became >=1F5u
// 4518BE: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00451910) --------------------------------------------------------
int Cheat_TeleportSelectedUnitToCursor()
{
  int v0; // esi
  int result; // eax
  int v2; // edi

  v0 = (((g_MouseCursorRawX >> g_CursorCoordShift)
       - 32
       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
        + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
     + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
  result = ((g_MouseCursorRawY >> g_CursorCoordShift)
          - 16
          - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
           + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6;
  v2 = result + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
  if ( g_SelectedUnitIndex != -1 )
  {
    *(_WORD *)(200 * *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET)
             + gameData
             + 2 * *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176)
             + 556374) = -1;
    *(_WORD *)(TILE_INDEX(v0, v2)) = g_SelectedUnitIndex;
    *(_WORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET) = v0;
    *(_WORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176) = v2;
    return WorldMap_RedrawViewport(1);
  }
  return result;
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00451A60) --------------------------------------------------------
signed int Cheat_FillSelectedSquadWithPegasi()
{
  int i; // esi
  signed int result; // eax
  signed int v2; // ecx

  if ( g_SelectedUnitIndex != -1 )
  {
    for ( i = 0; ; i += 31 )
    {
      result = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( v2 >= result )
        break;
      UnitSlot_InitFromType(
        i + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 6,
        UNIT_TYPE_PEGASUS,
        *(_BYTE *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147178));
    }
  }
  return result;
}
// 451A8E: variable 'v2' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00451AE0) --------------------------------------------------------
int  Cheat_ShowDeveloperTeamImage(DWORD a1)
{
  void *v1; // ebx
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  unsigned __int8 *v5; // edi
  _DWORD *Surface; // eax
  _DWORD *v7; // esi
  _DWORD *v9; // [esp+0h] [ebp-1Ch]

  LOBYTE(v1) = 0;
  Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  v3 = Mem_Alloc(1024, v2, 0, a1);
  if ( v3 )
  {
    v1 = &g_Runtime_PaletteArrayCtorDescriptor;
    v3 = _wcpp_4_ctor_array__(v4, 256);
  }
  v5 = (unsigned __int8 *)v3;
  Surface = (_DWORD *)Mem_Alloc(188, v4, (char)v1, a1);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 640, 480);
  v7 = Surface;
  v9 = Surface;
  (*(void (__fastcall **)(_DWORD, char *))(Surface[46] + 48))(0, aTeam1_gfx);
  (*(void (**)(void))(v7[46] + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, v5, 20);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping((int)g_RenderState) )
    DD_Pump((int)g_RenderState, 20);
  Render_Begin((int)g_RenderState, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 0, 0, 0x27Fu, 0x1DFu, 0, 0);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, 20);
  if ( v9 )
    (*(void (**)(void))v9[46])();
  return j__nfree_();
}
// 451B1C: variable 'v2' is possibly undefined
// 451BB0: variable 'v4' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 5202E0: using guessed type int dword_5202E0;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00451C50) --------------------------------------------------------
void __noreturn Cheat_QuitWithJokeMessage()
{
  App_RequestQuit((int)aHeheNoBonus);
}

//----- (00451C60) --------------------------------------------------------
void Cheat_SetFactionColorAndCastleFlags()
{
  int v0; // eax
  int v1; // edx
  int v2; // edx
  char v3; // bl

  *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) = 3;
  v0 = 0;
  while ( 1 )
  {
    v1 = UNIT_RECORD(v0);
    if ( (unsigned int)*(char *)(v1 + 4) < 4 && *(__int16 *)(v1 + 16) != -1 )
    {
      v2 = gameData + BUILDING_RECORD_SIZE * v0;
      if ( *(unsigned __int8 *)(v2 + 509676) == g_CurrentPlayerIndex )
      {
        v3 = *(_BYTE *)(v2 + 510118) & 0xF8;
        *(_BYTE *)(v2 + 510118) = v3;
        *(_BYTE *)(v2 + 510118) = v3 | 3;
      }
    }
    do
    {
      if ( ++v0 >= 100 )
        // 451CE5: loop exit jumps to the shared epilogue loc_451C1C
        // (pop edx/ecx/ebx; retn) shared with sub_451AE0; in C this is the return.
        return;
    }
    while ( v0 < 0 );
  }
}
// 451CE5: control flows out of bounds to 451C1C
// 451CF2: conditional instruction was optimized away because eax.4<64u
// 451C97: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00451D00) --------------------------------------------------------
int  UI_ReadCheatString(char a1)
{
  int v1; // esi
  int result; // eax
  _BYTE *i; // esi
  signed int v4; // eax
  unsigned int v5; // ebx
  int v6; // ecx
  _BYTE *v7; // esi
  int v9; // ecx
  int v10; // ecx
  int v11; // ebx
  _BYTE v12[124]; // [esp+0h] [ebp-7Ch] BYREF

  if ( g_LanguageIndex == 2 )
    v1 = 25;
  else
    v1 = 46;
  result = Input_IsKeyPressed(v1);
  if ( result )
  {
    while ( Input_IsKeyPressed(v1) )
      DD_Pump((int)g_RenderState, a1);
    for ( i = v12; ; *(i - 1) = Input_KeyToChar(v5) )
    {
      while ( 1 )
      {
        v4 = Input_PopKey();
        v5 = v4;
        if ( v4 != -1 )
          break;
        DD_Pump((int)g_RenderState, -1);
      }
      v6 = v4;
      while ( 1 )
      {
        result = Input_IsKeyPressed(v6);
        if ( !result )
          break;
        DD_Pump((int)g_RenderState, v5);
      }
      if ( v5 == 28 )
        break;
      ++i;
    }
    *i = 0;
    BYTE1(result) = v12[0];
    v7 = v12;
    if ( v12[0] )
    {
      do
        *v7 ^= 0x32u;
      while ( *++v7 );
    }
    v9 = 0;
    if ( g_CheatTable )
    {
      do
      {
        result = strcmp_(v9, v12);
        if ( !result )
          result = (*(int (**)())((char *)&g_CheatCodeHandlerTable + v10))();
        v11 = *(int *)((char *)&g_CheatCodeStringTable + v10);
        v9 = v10 + 8;
      }
      while ( v11 );
    }
  }
  return result;
}
// 451D71: variable 'v6' is possibly undefined
// 451DE6: variable 'v10' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 519590: using guessed type char *g_CheatTable;
// 519594: using guessed type int (*off_519594)();
// 519598: using guessed type char *off_519598;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00451DF0) --------------------------------------------------------
signed int Rules_ShowBanner_StrategicClash()
{
  int v0; // ecx
  int v1; // edx
  _DWORD v3[6]; // [esp-18h] [ebp-18h] BYREF

  CRT_ProbeStackFrame(32);
  v3[4] = v0;
  v3[3] = v1;
  Rules_Clear();
  return Rules_Bload((int)aStrategClash_d, (DWORD)v3);
}
// 451DFB: variable 'v0' is possibly undefined
// 451DFC: variable 'v1' is possibly undefined
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (00451E20) --------------------------------------------------------
int Rules_ResetEngineOnLoad()
{
  int result; // eax

  CRT_ProbeStackFrame(32);
  Rules_Reset();
  return result;
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (00451E46) --------------------------------------------------------
signed int Rules_CompileStrategicRulesFile()
{
  int v0; // ecx
  int v1; // edx
  _DWORD v3[6]; // [esp-18h] [ebp-18h] BYREF

  CRT_ProbeStackFrame(32);
  v3[4] = v0;
  v3[3] = v1;
  Rules_InitializeEngine(v0, v1);
  Rules_SetStrategy(0);
  Rules_SetSalienceEvaluationMode(1);
  return Rules_Bload((int)aStrategClash_d, (DWORD)v3);
}
// 451E51: variable 'v0' is possibly undefined
// 451E52: variable 'v1' is possibly undefined
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);
// 47E7B0: using guessed type int __fastcall unknown_libname_7(int);

//----- (00451E87) --------------------------------------------------------
signed int Rules_RegisterAllHostFunctions()
{
  CRT_ProbeStackFrame(32);
  Rules_RegisterStrategicActionHostFunctions();
  Rules_RegisterBuildingHostFunctions();
  return Rules_RegisterArmyHostFunctions();
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (00451EC0) --------------------------------------------------------
int Rules_LogMissionSetupInfo()
{
  double formatted;
  int player_index;
  int player_offset;
  int player_record;
  char log_line[124];

  formatted = sprintf_(log_line, "(misja %d)", ACTIVE_MISSION_INDEX);
  Rules_Log(log_line, 0, formatted);
  player_index = 0;
  player_offset = 0;
  while ( player_index < 5 )
  {
    player_record = player_offset + gameData;
    if ( *(_DWORD *)(player_record + 140024) )
    {
      formatted = sprintf_(
                    log_line,
                    "(gameinfo gracz %d komputer %d inteligencja %d chrzesc %d)",
                    player_index,
                    1 - *(_DWORD *)(player_record + 140051),
                    *(_DWORD *)(player_record + 140055),
                    *(_DWORD *)(player_record + 140063));
      Rules_Log(log_line, 0, formatted);
    }
    ++player_index;
    player_offset += 1423;
  }
  return 0;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5202E4: using guessed type int gameData;

//----- (00451F70) --------------------------------------------------------
signed int Rules_ExecuteAITurn()
{
  double v1; // st7
  double v3; // st7
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  double v11; // st7
  int v13; // edx
  int v14; // eax
  int v15; // ebx
  int v16; // ecx
  double v17; // st7
  char v21[224]; // [esp+0h] [ebp-E0h] BYREF

  Diagnostics_TraceWorldMapActionEvent("ai_turn_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
  Map_RebuildCastleSiteAnchorCache();
  v1 = sprintf_(v21, "(tura %d)", *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET));
  g_AITurnLogFactHandle_Turn = (int)Rules_Log(v21, 0, v1);
  v3 = sprintf_(v21, "(gracz %d inteligencja %d)", g_CurrentPlayerIndex, PLAYER_AI_INTELLIGENCE(g_CurrentPlayerIndex));
  g_AITurnPlayerIntelligenceFactHandle = (int)Rules_Log(v21, 0, v3);
  memset(v21, 0, 0xC8);
  v7 = 0;
  v8 = 0;
LABEL_2:
  v9 = UNIT_RECORD(v8);
  if ( (unsigned int)*(char *)(v9 + 4) < 4 && *(__int16 *)(v9 + 16) != -1 )
  {
    v10 = gameData + BUILDING_RECORD_SIZE * v8;
    if ( *(unsigned __int8 *)(v10 + 509676) == g_CurrentPlayerIndex && *(_BYTE *)(v10 + 509678) == 2 )
      ++v7;
  }
  while ( ++v8 < 100 )
  {
    if ( v8 >= 0 )
      goto LABEL_2;
  }
  v11 = sprintf_(v21, "(ilosc-zamkow %d %d)", g_CurrentPlayerIndex, v7);
  g_AITurnCastleCountFactHandle = (int)Rules_Log(v21, 0, v11);
  v13 = 0;
  v14 = 0;
LABEL_11:
  v15 = UNIT_RECORD(v14);
  if ( (unsigned int)*(char *)(v15 + 4) < 4 && *(__int16 *)(v15 + 16) != -1 )
  {
    v16 = gameData + BUILDING_RECORD_SIZE * v14;
    if ( *(unsigned __int8 *)(v16 + 509676) == g_CurrentPlayerIndex && *(_BYTE *)(v16 + 509678) == 1 )
      ++v13;
  }
  while ( ++v14 < 100 )
  {
    if ( v14 >= 0 )
      goto LABEL_11;
  }
  v17 = sprintf_(v21, "(ilosc-twierdz %d %d)", g_CurrentPlayerIndex, v13);
  g_AiTurnFortressCountFactHandle = (int)Rules_Log(v21, 0, v17);
  Diagnostics_TraceWorldMapActionEvent("ai_turn_before_agenda", g_SelectedUnitIndex, g_CurrentPlayerIndex, v7, v13);
  Rules_RunAgendaLoop(-1, 0, 0.0);
  Diagnostics_TraceWorldMapActionEvent("ai_turn_after_agenda", g_SelectedUnitIndex, g_CurrentPlayerIndex, g_AITurnLogFactHandle_Turn, g_AiTurnFortressCountFactHandle);
  Rules_RetractFact(g_AITurnLogFactHandle_Turn, 0.0);
  Rules_RetractFact(g_AITurnPlayerIntelligenceFactHandle, 0.0);
  Rules_RetractFact(g_AITurnCastleCountFactHandle, 0.0);
  Diagnostics_TraceWorldMapActionEvent("ai_turn_before_cleanup_last_fact", g_SelectedUnitIndex, g_CurrentPlayerIndex, g_AiTurnFortressCountFactHandle, 0);
  return Rules_RetractFact(g_AiTurnFortressCountFactHandle, 0.0);
}
// 452060: conditional instruction was optimized away because eax.4<64u
// 4520F3: conditional instruction was optimized away because eax.4<64u
// 452016: simplified comparisons for 'ebx.4': <0 || >=4 became >=4u
// 4520A8: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 451FA7: variable 'v2' is possibly undefined
// 451FE7: variable 'v4' is possibly undefined
// 451FF3: variable 'v6' is possibly undefined
// 451FF3: variable 'v5' is possibly undefined
// 452082: variable 'v12' is possibly undefined
// 4520E4: variable 'v13' is possibly undefined
// 452113: variable 'v18' is possibly undefined
// 452122: variable 'v19' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 54454C: using guessed type int dword_54454C;
// 544550: using guessed type int dword_544550;
// 544554: using guessed type int dword_544554;
// 544558: using guessed type int dword_544558;

//----- (004521D0) --------------------------------------------------------
unsigned int  Rules_CreateArmyFact(a1, a2, a3, a4, a5)
__int16 *a1;
int a2;
int a3;
char a4;
DWORD a5;
{
  unsigned int result; // eax
  _DWORD *fact; // eax
  int trace_load_save; // eax
  char v15[1000]; // [esp+0h] [ebp-3ECh] BYREF

  trace_load_save = 0;
  result = a1[3];
  if ( result <= 0x28 )
  {
    ++g_RulesArmyFactCreatedCount;
    sprintf_(
      v15,
      "( ODDZIAL%d of oddzial (id %d)(gracz %d)(PA %d)(moc %d)(x %d)(y %d))",
      a2,
      a2,
      *((unsigned __int8 *)a1 + 4),
      100,
      100,
      *a1,
      a1[1]);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-create-army-fact %s\n", v15);
    Debug_Log(0, a4, a5, (int)aMkinstArmyS);
    fact = Rules_AssertFact(v15, 0, 0.0);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-create-army-after-assert fact=%p\n", fact);
    *(_DWORD *)((char *)a1 + 721) = fact;
    if ( !fact )
      return 0;
    return Rules_LinkArmyFact(a1, a2, a3, 0.0, a4, a5);
  }
  return result;
}
// 4521DF: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 452223: variable 'v9' is possibly undefined
// 45222D: variable 'v10' is possibly undefined
// 452232: variable 'v12' is possibly undefined
// 45223A: variable 'v13' is possibly undefined
// 45223A: variable 'v14' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5195F4: using guessed type int dword_5195F4;

//----- (00452250) --------------------------------------------------------
_DWORD * Rules_RetractArmyFact(_DWORD *result, int a2, int a3, double a4)
{
  __int16 *stack;
  char v8[1000]; // [esp+0h] [ebp-3F0h] BYREF
  int v9; // [esp+3E8h] [ebp-8h]
  int v10; // [esp+3ECh] [ebp-4h]

  stack = (__int16 *)result;
  v10 = a3;
  v9 = a2;
  if ( *(_DWORD *)((char *)result + 721) )
  {
    Rules_RetractFactById(*(_DWORD *)((char *)result + 721), a4);
    sprintf_(v8, "(usunieto armie %d )", *(unsigned __int16 *)(TILE_INDEX(*stack, stack[1])));
    result = Rules_Log(v8, 0, a4);
    *(_DWORD *)((char *)stack + 721) = 0;
  }
  else
  {
    *(_DWORD *)((char *)stack + 721) = 0;
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5202E4: using guessed type int gameData;

//----- (00452390) --------------------------------------------------------
signed int Rules_RegisterStrategicActionHostFunctions()
{
  CRT_ProbeStackFrame(36);
  Rules_RegisterHostFunction(aSwiatynia, 105, (int)aSwiatynia00, (int)&Rules_HostTemple, (int)a22i_1);
  Rules_RegisterHostFunction(aKop_skarb, 105, (int)aKop_skarb00, (int)&Rules_HostDigTreasure, (int)a11i);
  Rules_RegisterHostFunction(aPobierz_oddz_0, 105, (int)aPobierz_oddzia, (int)&Rules_HostCollectPortSupply, (int)a00i);
  Rules_RegisterHostFunction(aPelny_port, 98, (int)aPelny_port00, (int)&Rules_HostPortHasSupplyReady, (int)a00i);
  Rules_RegisterHostFunction(aJest_pracown_0, 98, (int)aJest_pracownik, (int)&Rules_HostArmyHasBuilder, (int)a11i);
  Rules_RegisterHostFunction(aJednostka_bi_0, 98, (int)aJednostka_bite, (int)&Rules_HostArmyHasNormalCombatUnits, (int)a11i);
  Rules_RegisterHostFunction(aJest_droga, 98, (int)aJest_droga00, (int)&Rules_HostRoadExists, (int)a33i);
  Rules_RegisterHostFunction(aJest_droga_w_0, 98, (int)aJest_droga_w_p, (int)&Rules_HostRoadExistsNearby, (int)a33i);
  Rules_RegisterHostFunction(aJest_droga_w_2, 98, (int)aJest_droga_w_1, (int)&Rules_HostRoadExistsNearCastle, (int)a33i);
  Rules_RegisterHostFunction(aJest_droga_d_0, 98, (int)aJest_droga_do_, (int)&Rules_HostRoadExistsToPort, (int)a33i);
  Rules_RegisterHostFunction(aJest_droga_d_2, 98, (int)aJest_droga_d_1, (int)&Rules_HostRoadExistsToCastle, (int)a33i);
  Rules_RegisterHostFunction(aJest_droga_d_4, 98, (int)aJest_droga_d_3, (int)&Rules_HostRoadExistsToTemple, (int)a33i);
  Rules_RegisterHostFunction(aOddzial_w_za_1, 98, (int)aOddzial_w_za_0, (int)&Rules_HostTroopInArmyRange, (int)a33i);
  Rules_RegisterHostFunction(aBudowla_w_za_0, 98, (int)aBudowla_w_zasi, (int)&Rules_HostBuildingInArmyRange, (int)a33i);
  Rules_RegisterHostFunction(aOdleglosc_od_0, 105, (int)aOdleglosc_od_o, (int)&Rules_HostDistanceToObject, (int)a33i);
  Rules_RegisterHostFunction(aSwiatynia_w__0, 98, (int)aSwiatynia_w_za, (int)&Rules_HostTempleInArmyRange, (int)a33i);
  Rules_RegisterHostFunction(aSwiatynia_ok, 98, (int)aSwiatynia_ok00, (int)&Rules_HostTempleOk, (int)a33i);
  Rules_RegisterHostFunction(aMaszeruj, 105, (int)aMaszeruj00, (int)&Rules_HostMarch, (int)a33i);
  Rules_RegisterHostFunction(aMaszeruj_do__0, 105, (int)aMaszeruj_do_sw, (int)&Rules_HostMarchToTemple, (int)a33i);
  Rules_RegisterHostFunction(aMaszeruj_bli_0, 105, (int)aMaszeruj_blisk, (int)&Rules_HostMarchNear, (int)a33i);
  Rules_RegisterHostFunction(aAtakuj_oddzi_0, 105, (int)aAtakuj_oddzial, (int)&Rules_HostAttackTroop, (int)a22i_1);
  Rules_RegisterHostFunction(aPrzejmuj_odd_0, 105, (int)aPrzejmuj_oddzi, (int)&Rules_HostCaptureTroop, (int)a22i_1);
  Rules_RegisterHostFunction(aUkryj_oddzial, 105, (int)aUkryj_oddzial0, (int)&Rules_HostHideTroop, (int)a33i);
  Rules_RegisterHostFunction(aJest_armia, 98, (int)aJest_armia00, (int)&Rules_HostArmyExists, (int)a11i);
  Rules_RegisterHostFunction(aLiczba_jedno_0, 105, (int)aLiczba_jednost, (int)&Rules_HostUnitCountInTroop, (int)a11i);
  Rules_RegisterHostFunction(aAtakuj_budow_0, 105, (int)aAtakuj_budowle, (int)&Rules_HostAttackBuilding, (int)a22i_1);
  Rules_RegisterHostFunction(aJest_brod, 98, (int)aJest_brod00, (int)&Rules_HostFordExists, (int)a11i);
  Rules_RegisterHostFunction(aBuduj_droge, 98, (int)aBuduj_droge00, (int)&Rules_HostBuildRoad, (int)a11i);
  Rules_RegisterHostFunction(aBuduj_pulapke, 105, (int)aBuduj_pulapke0, (int)&Rules_HostBuildTrap, (int)a33i);
  return Rules_RegisterHostFunction(aUnit_canmove, 105, (int)aUnit_canmove00, (int)&Rules_HostUnitCanMove, (int)a11i);
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (004530A0) --------------------------------------------------------
signed int  Rules_PortCollectSupply(int a1, char a2, DWORD a3, double a4)
{
  Port_CollectReinforcementShipment(a1, a2, a3, a4);
  return 1;
}

int Rules_HostCollectPortSupply(void)
{
  return Rules_PortCollectSupply(0, 0, 0, 0.0);
}

int Rules_HostPortHasSupplyReady(void)
{
  return Port_IsReinforcementReady();
}

int Rules_HostArmyHasBuilder(int a1, double a2)
{
  (void)a1;
  return UnitStack_HasBuilder(Rules_RtnLong(1, 0, a2));
}

int Rules_HostArmyHasNormalCombatUnits(int a1, double a2)
{
  (void)a1;
  return Rules_UnitStackHasNormalCombatUnits(Rules_RtnLong(1, 0, a2));
}

//----- (004530D0) --------------------------------------------------------
signed int  Rules_UnitStackHasNormalCombatUnits(int a1)
{
  return UnitStack_HasNormalCombatUnits(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00453110) --------------------------------------------------------
signed int  Rules_QueuePathToTile(int a1, int a2, int a3, DWORD a4)
{
  int v5; // ecx
  int *v6; // ebx
  int v7; // ecx
  int v8; // edx
  int v10; // [esp+0h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v10 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    if ( !abs32(a2 - (unsigned __int8)v10) && !abs32(a3 - BYTE1(v10)) )
      return 1;
  }
  if ( UnitStack_HasBuilder(a1) )
    Pathing_EnableBridgeCrossings(v5, a3, a4);
  v6 = Unit_MoveTrack(
         a1,
         *(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + UNIT_STACK_TABLE_OFFSET),
         v5,
         *(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + 147176),
         a4,
         a3);
  Pathing_DisableBridgeCrossings(v7, (char)v6, a4);
  if ( !v8 )
    return 0;
  if ( *(_DWORD *)(UNIT_STACK_STRIDE * a1 + gameData + 147490) )
    *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) = 0;
  qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 316), v6, 0x194u);
  j__nfree_();
  return 1;
}
// 453152: variable 'v5' is possibly undefined
// 453191: variable 'v7' is possibly undefined
// 453198: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004532A0) --------------------------------------------------------
signed int  Rules_QueuePathNearTile(int a1, int a2, int a3, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  _DWORD *v8; // ebx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v13; // [esp+0h] [ebp-14h]

  Debug_Log(a1, a3, a4, (int)aJest_droga_w_3);
  if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v6 + 316) )
  {
    v13 = *(_DWORD *)(UNIT_STACK_STRIDE * v5 + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( (int)abs32(a2 - (unsigned __int8)v13) < 2 )
    {
      a4 = BYTE1(v13);
      if ( (int)abs32(a3 - BYTE1(v13)) > 2 )
      {
        if ( a2 != (unsigned __int8)v13 )
          return 1;
        if ( a3 != BYTE1(v13) )
          return 1;
      }
    }
  }
  if ( UnitStack_HasBuilder(v5) )
    Pathing_EnableBridgeCrossings(v7, a3, a4);
  v8 = Unit_MoveTrackNearTile(v7, a2, v7, a3, a4);
  Pathing_DisableBridgeCrossings(v9, (char)v8, a4);
  if ( v11 )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v10 + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v10 + 147490) = 0;
    qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v10 + 316), v8, 0x194u);
    j__nfree_();
    return 1;
  }
  return 0;
}
// 4532D7: variable 'v6' is possibly undefined
// 4532F3: variable 'v5' is possibly undefined
// 4532FC: variable 'v7' is possibly undefined
// 45330E: variable 'v9' is possibly undefined
// 453315: variable 'v11' is possibly undefined
// 453338: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453440) --------------------------------------------------------
signed int  Rules_QueuePathNearCastle(int a1, int a2, int a3, DWORD a4)
{
  int v5; // ecx
  const void *v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v11; // [esp+0h] [ebp-14h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v11 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    a4 = (unsigned __int8)v11;
    if ( (int)abs32(a2 - (unsigned __int8)v11) < 3 && (int)abs32(a3 - BYTE1(v11)) < 3 )
    {
      if ( a2 != (unsigned __int8)v11 )
        return 1;
      if ( a3 != BYTE1(v11) )
        return 1;
    }
  }
  if ( UnitStack_HasBuilder(a1) )
    Pathing_EnableBridgeCrossings(v5, a3, a4);
  v6 = (const void *)Building_GenerateNearApproachTrack(v5, *(unsigned __int16 *)(TILE_INDEX(a2, a3)) - 0x8000, v5, a3, a4);
  Pathing_DisableBridgeCrossings(v7, (char)v6, a4);
  if ( v9 )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + 316), v6, 0x194u);
    j__nfree_();
    return 1;
  }
  return 0;
}
// 453483: variable 'v5' is possibly undefined
// 4534C4: variable 'v7' is possibly undefined
// 4534CB: variable 'v9' is possibly undefined
// 4534EE: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453600) --------------------------------------------------------
signed int  Rules_QueuePathToPort(int a1, int a2, int a3, DWORD a4)
{
  int v4; // esi
  int v5; // ecx
  int *v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx

  v4 = a3;
  LOBYTE(a3) = gameData;
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    a3 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    if ( !abs32(a2 - (unsigned __int8)a3) && !abs32(v4 - BYTE1(a3)) )
      return 1;
  }
  if ( UnitStack_HasBuilder(a1) )
    Pathing_EnableBridgeCrossings(v5, a3, a4);
  v6 = Port_GenerateApproachTrack(v5);
  Pathing_DisableBridgeCrossings(v7, (char)v6, a4);
  if ( !v9 )
    return 0;
  if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v8 + 316) )
    *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) = 0;
  qmemcpy((void *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + 316), v6, 0x194u);
  j__nfree_();
  return 1;
}
// 453641: variable 'v5' is possibly undefined
// 453651: variable 'v7' is possibly undefined
// 453658: variable 'v9' is possibly undefined
// 45367B: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453770) --------------------------------------------------------
signed int  Rules_QueuePathToCastle(int a1, int a2, int a3, DWORD a4)
{
  int v5; // ecx
  const void *v6; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v11; // [esp+0h] [ebp-14h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v11 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    a4 = (unsigned __int8)v11;
    if ( (int)abs32(a2 - (unsigned __int8)v11) < 2 && (int)abs32(a3 - BYTE1(v11)) < 2 )
    {
      if ( a2 != (unsigned __int8)v11 )
        return 1;
      if ( a3 != BYTE1(v11) )
        return 1;
    }
  }
  if ( UnitStack_HasBuilder(a1) )
    Pathing_EnableBridgeCrossings(v5, a3, a4);
  v6 = (const void *)Building_GenerateApproachTrack(
                       v5,
                       *(unsigned __int16 *)(TILE_INDEX(a2, a3)) - 0x8000,
                       v5,
                       a3,
                       a4);
  Pathing_DisableBridgeCrossings(v7, (char)v6, a4);
  if ( v9 )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + 316), v6, 0x194u);
    j__nfree_();
    return 1;
  }
  return 0;
}
// 4537B3: variable 'v5' is possibly undefined
// 4537F4: variable 'v7' is possibly undefined
// 4537FB: variable 'v9' is possibly undefined
// 45381E: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453930) --------------------------------------------------------
signed int  Move_IsAtTargetOrCanStay(int a1, int a2, int a3)
{
  signed int result; // eax
  int v4; // ecx
  int v5; // [esp+0h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v5 = *(_DWORD *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( !abs32(a2 - (unsigned __int8)v5) && !abs32(a3 - BYTE1(v5)) )
      return 1;
  }
  result = (signed int)Temple_GenerateApproachTrack(a1, a2, a1, a3);
  if ( result )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v4 + 316) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v4 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v4 + gameData + UNIT_STACK_TABLE_OFFSET + 316), (const void *)result, 0x194u);
    j__nfree_();
    return 1;
  }
  return result;
}
// 453993: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453A90) --------------------------------------------------------
signed int  Move_TryApproachTarget(int a1, DWORD a2, int a3)
{
  signed int result; // eax
  int v4; // ecx
  const void *v5; // ebp
  signed int v6; // eax
  signed int v7; // edx
  int v8; // ebx
  unsigned __int16 v9; // di
  int v10; // ecx
  int v11; // [esp+4h] [ebp-14h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490)
    && (v11 = *(_DWORD *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET + 320), (int)abs32(a2 - (unsigned __int8)v11) <= 2)
    && (int)abs32(a3 - BYTE1(v11)) <= 2 )
  {
    v6 = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
    return v6 >= v7;
  }
  else
  {
    result = Building_GenerateApproachTrack(a1, *(unsigned __int16 *)(TILE_INDEX(a2, a3)) - 0x8000, a1, a3, a2);
    v5 = (const void *)result;
    if ( result )
    {
      v8 = UNIT_STACK_STRIDE * v4;
      v9 = HIWORD(*(_DWORD *)(result + 4));
      if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * v4 + gameData + UNIT_STACK_TABLE_OFFSET) < v9 )
      {
        j__nfree_();
        return 0;
      }
      else
      {
        if ( *(_DWORD *)(v8 + gameData + 147490) )
          *(_DWORD *)(UNIT_STACK_STRIDE * v10 + gameData + UNIT_STACK_TABLE_OFFSET + 316) = 0;
        qmemcpy((void *)(UNIT_STACK_STRIDE * v10 + gameData + UNIT_STACK_TABLE_OFFSET + 316), v5, 0x194u);
        j__nfree_();
        return 1;
      }
    }
  }
  return result;
}
// 453B90: variable 'v7' is possibly undefined
// 453BCF: variable 'v4' is possibly undefined
// 453C5D: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453C90) --------------------------------------------------------
signed int  Rules_QueuePathIntoArmyRange(int a1, int a2, int a3, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  signed int result; // eax
  int v8; // ecx
  const void *v9; // ebp
  signed int v10; // eax
  signed int v11; // edx
  int v12; // ebx
  unsigned __int16 v13; // di
  int v14; // ecx
  int v15; // [esp+4h] [ebp-14h]

  Debug_Log(a1, a3, a4, (int)aOddzial_w_za_2);
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v6 + 147490)
    && (a4 = UNIT_STACK_STRIDE * v5, v15 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v5 + 320), (int)abs32(a2 - (unsigned __int8)v15) <= 1)
    && (int)abs32(a3 - BYTE1(v15)) <= 1 )
  {
    v10 = UnitStack_GetMinCurrentActionPoints(a4 + gameData + UNIT_STACK_TABLE_OFFSET);
    return v10 >= v11;
  }
  else
  {
    result = (signed int)Unit_MoveTrackNearTile(v5, a2, v5, a3, a4);
    v9 = (const void *)result;
    if ( result )
    {
      v12 = UNIT_STACK_STRIDE * v8;
      v13 = HIWORD(*(_DWORD *)(result + 4));
      if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET) < v13 )
      {
        j__nfree_();
        return 0;
      }
      else
      {
        if ( *(_DWORD *)(v12 + gameData + 147490) )
          *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v14 + 147490) = 0;
        qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v14 + 316), v9, 0x194u);
        j__nfree_();
        return 1;
      }
    }
  }
  return result;
}
// 453CC7: variable 'v6' is possibly undefined
// 453CDB: variable 'v5' is possibly undefined
// 453D69: variable 'v11' is possibly undefined
// 453DA8: variable 'v8' is possibly undefined
// 453E38: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453E60) --------------------------------------------------------
signed int  Rules_GetPathDistanceToObject(int a1, int a2, int a3, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int *Track; // eax
  int v11; // edx
  int v12; // [esp+0h] [ebp-14h]

  Debug_Log(a2, a3, a4, (int)aOdleglosc_od_1);
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v6 + 147490) )
  {
    a4 = gameData;
    v12 = *(_DWORD *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( (int)abs32(v5 - (unsigned __int8)v12) <= 1 && (int)abs32(a3 - BYTE1(v12)) <= 1 )
      return *(_DWORD *)(UNIT_STACK_STRIDE * a1 + gameData + 147490);
  }
  if ( MapTile_GetReligiousSiteCategory(v5, a3) )
  {
    Track = Temple_GenerateApproachTrack(a1, v7, v7, a3);
  }
  else if ( MapTile_HasHiddenTreasure(v7, a3) )
  {
    Track = Unit_MoveTrack(
              a1,
              *(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + UNIT_STACK_TABLE_OFFSET),
              v8,
              *(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + 147176),
              a4,
              a3);
  }
  else if ( v8 == PORT_ROW && a3 == PORT_COLUMN )
  {
    Track = Port_GenerateApproachTrack(a1);
  }
  else
  {
    Track = Unit_MoveTrackNearTile(a1, v8, v8, a3, a4);
  }
  if ( !Track )
    return 1000;
  j__nfree_();
  return v11;
}
// 453E97: variable 'v6' is possibly undefined
// 453EAB: variable 'v5' is possibly undefined
// 453EBC: variable 'v7' is possibly undefined
// 453EFC: variable 'v8' is possibly undefined
// 453FD0: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453FE0) --------------------------------------------------------
BOOL  Rules_IsTempleWithinArmyRange(int a1, int a2, int a3)
{
  int *Track; // edx
  BOOL result; // eax
  signed int v6; // eax
  signed int v7; // edx
  int v8; // [esp+4h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v8 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    if ( (int)abs32(a2 - (unsigned __int8)v8) > 1 || (int)abs32(a3 - BYTE1(v8)) > 1 )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) = 0;
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    Track = Temple_GenerateApproachTrack(a1, a2, a2, a3);
    if ( Track )
    {
      qmemcpy((void *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET + 316), Track, 0x194u);
      j__nfree_();
    }
  }
  result = 0;
  if ( *(_DWORD *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET + 316) )
  {
    v6 = UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1);
    if ( v6 >= v7 )
      return 1;
  }
  return result;
}
// 454198: variable 'v7' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004541B0) --------------------------------------------------------
BOOL  Player_CanEnterReligiousSiteTile(int a1, int a2, int a3)
{
  int v4; // ecx

  return MapTile_GetReligiousSiteCategory(a2, a3) == RELIGIOUS_SITE_CATEGORY_SHRINE && PLAYER_RELIGION_FLAG(a1)
      || MapTile_GetReligiousSiteCategory(v4, a3) == RELIGIOUS_SITE_CATEGORY_CULT_PLACE && !PLAYER_RELIGION_FLAG(a1);
}
// 4541E6: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454210) --------------------------------------------------------
signed int  Move_CommitIfWithinCost(
        unsigned int a1,
        int a2,
        DWORD a3,
        double a4)
{
  int v6; // ebx
  int v7; // eax
  int v8; // esi
  int v9; // edi
  unsigned int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  _DWORD v15[9]; // [esp-4h] [ebp-24h] BYREF

  v15[8] = a2;
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
    return 0;
  v6 = UNIT_STACK_STRIDE * a1;
  v7 = gameData + UNIT_STACK_STRIDE * a1;
  v8 = *(__int16 *)(v7 + 147174);
  v9 = *(__int16 *)(v7 + 147176);
  UnitStack_ExecuteQueuedPath(a1, 1, -43 * a1, a3, a4);
  if ( v10 > 0x1F4 || (unsigned int)*(__int16 *)(v6 + gameData + 147180) > 0x28 )
    return 1;
  if ( Rules_IsQueuedPathTargetBridgeCrossing(v10) )
    Rules_BuildRoadOrStepTowardQueuedPath(v11, a3, a4);
  v12 = gameData + UNIT_STACK_STRIDE * v11;
  if ( v8 == *(__int16 *)(v12 + 147174) && v9 == *(__int16 *)(v12 + 147176) )
  {
    v15[1] = 1;
    v15[2] = Rules_AddIntegerValue(0);
    Rules_PutInstanceSlotValue(*(_DWORD *)(v13 + gameData + 147895), aPa, v14, v15, a4);
  }
  return 1;
}
// 454284: simplified comparisons for 'ecx.4': <0 || >=1F5 became >=1F5u
// 45429D: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 454284: variable 'v10' is possibly undefined
// 4542BD: variable 'v11' is possibly undefined
// 454313: variable 'v13' is possibly undefined
// 45431F: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454330) --------------------------------------------------------
signed int  Rules_MarchToTemple(unsigned int a1, int a2, int a3, double a4)
{
  int *Track; // edx
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // ecx
  int v11; // ebp
  int v12; // eax
  int v13; // ecx
  _DWORD v14[6]; // [esp+0h] [ebp-28h] BYREF
  int v15; // [esp+18h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v15 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    if ( (int)abs32(a2 - (unsigned __int8)v15) > 1 || (int)abs32(a3 - BYTE1(v15)) > 1 )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) = 0;
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    Track = Temple_GenerateApproachTrack(a1, a2, a2, a3);
    if ( Track )
    {
      qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 316), Track, 0x194u);
      j__nfree_();
    }
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
    return 0;
  v7 = gameData + UNIT_STACK_STRIDE * a1;
  v8 = *(__int16 *)(v7 + 147174);
  v9 = *(__int16 *)(v7 + 147176);
  UnitStack_ExecuteQueuedPath(a1, 1, v9, a1, a4);
  if ( a1 <= 0x1F4 && (unsigned int)*(__int16 *)(v10 + gameData + 147180) <= 0x28 )
  {
    v11 = UNIT_STACK_STRIDE * a1;
    v12 = gameData + v11;
    if ( *(__int16 *)(gameData + v11 + 147180) == -1 )
      return 0;
    if ( v8 == *(__int16 *)(v12 + 147174) && v9 == *(__int16 *)(v12 + 147176) )
    {
      v14[1] = 1;
      v14[2] = Rules_AddIntegerValue(0);
      Rules_PutInstanceSlotValue(*(_DWORD *)(gameData + v11 + 147895), aPa_0, v13, v14, a4);
    }
  }
  return 1;
}
// 4544DF: simplified comparisons for 'ebp.4': <0 || >=1F5 became >=1F5u
// 454500: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 4544F6: variable 'v10' is possibly undefined
// 45457B: variable 'v13' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454590) --------------------------------------------------------
signed int  Rules_MarchNearTile(DWORD a1, int a2, int a3, double a4)
{
  int v5; // ecx
  int v6; // edx
  _DWORD *v7; // edx
  DWORD v9; // eax
  int v10; // edi
  int v11; // ebx
  int v12; // ecx
  DWORD v13; // ebp
  int v14; // ecx
  _DWORD v15[6]; // [esp+4h] [ebp-28h] BYREF
  int v16; // [esp+1Ch] [ebp-10h]

  Debug_Log(a2, a3, a1, (int)aMaszeruj_bli_1);
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v6 + 147490) )
  {
    v16 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320);
    if ( (int)abs32(v5 - (unsigned __int8)v16) > 1 || (int)abs32(a3 - BYTE1(v16)) > 1 )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) = 0;
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
  {
    v7 = Unit_MoveTrackNearTile(a1, v5, v5, a3, a1);
    if ( v7 )
    {
      qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 316), v7, 0x194u);
      j__nfree_();
    }
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
    return 0;
  v9 = gameData + UNIT_STACK_STRIDE * a1;
  v10 = *(__int16 *)(v9 + 147174);
  v11 = *(__int16 *)(v9 + 147176);
  UnitStack_ExecuteQueuedPath(a1, 1, v11, a1, a4);
  if ( a1 <= 0x1F4 && (unsigned int)*(__int16 *)(v12 + gameData + 147180) <= 0x28 )
  {
    v13 = UNIT_STACK_STRIDE * a1;
    if ( v10 == *(__int16 *)(gameData + v13 + UNIT_STACK_TABLE_OFFSET) && v11 == *(__int16 *)(gameData + v13 + 147176) )
    {
      v15[1] = 1;
      v15[2] = Rules_AddIntegerValue(0);
      Rules_PutInstanceSlotValue(*(_DWORD *)(gameData + v13 + 147895), aPa_1, v14, v15, a4);
    }
  }
  return 1;
}
// 45474F: simplified comparisons for 'ebp.4': <0 || >=1F5 became >=1F5u
// 454770: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 4545C6: variable 'v6' is possibly undefined
// 454607: variable 'v5' is possibly undefined
// 454766: variable 'v12' is possibly undefined
// 4547D7: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004547F0) --------------------------------------------------------
signed int  Rules_HostUnitAttack(int a1, int a2, char a3, DWORD a4, double a5)
{
  Unit_Attack(a1, a2, a3, a4, a5);
  return 1;
}

//----- (00454800) --------------------------------------------------------
signed int  Rules_HostUnitCaptureDefeatedStack(int a1, int a2, double a3)
{
  UnitStack_CaptureDefeatedStack(
    (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1),
    gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a2,
    gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a2,
    a1,
    a3);
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00454860) --------------------------------------------------------
signed int  Rules_HostUnitMoveAndHide(unsigned int a1, unsigned int a2, DWORD a3, double a4)
{
  DWORD v5; // esi
  signed int result; // eax
  char v7; // bl
  int v8; // edx
  unsigned __int64 v9; // [esp+4h] [ebp-18h]

  v9 = __PAIR64__(a1, a2);
  v5 = UNIT_STACK_STRIDE * a3;
  result = (signed int)Unit_MoveTrack(
                         a3,
                         *(__int16 *)(gameData + UNIT_STACK_STRIDE * a3 + UNIT_STACK_TABLE_OFFSET),
                         a1,
                         *(__int16 *)(gameData + UNIT_STACK_STRIDE * a3 + 147176),
                         a3,
                         a2);
  v7 = result;
  if ( result )
  {
    if ( *(_DWORD *)(v5 + gameData + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * a3 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * a3 + gameData + UNIT_STACK_TABLE_OFFSET + 316), (const void *)result, 0x194u);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(a3, v8, v7, a3, a4);
    if ( __PAIR64__(*(__int16 *)(UNIT_STACK_STRIDE * a3 + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(UNIT_STACK_STRIDE * a3 + gameData + 147176)) == v9 )
    {
      UnitStack_TryHide(a3, v9, a3, a4);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 454915: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454990) --------------------------------------------------------
signed int  Rules_HostUnitAttackBuilding(int a1, int a2, char a3, DWORD a4, double a5)
{
  Unit_AttackBuilding(a1, a2, a3, a4, a5);
  return 1;
}

//----- (004549A0) --------------------------------------------------------
BOOL  UnitStack_HasNormalCombatUnitsByIndex(int a1)
{
  return UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1) != 0;
}
// 5202E4: using guessed type int gameData;

//----- (004549E0) --------------------------------------------------------
signed int  UnitStack_GetSquadCountByIndex(int a1)
{
  return Unit_GetSquadCount(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00454A20) --------------------------------------------------------
signed int  Rules_IsQueuedPathTargetBridgeCrossing(int a1)
{
  signed int result; // eax
  int v2; // ebx

  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490) )
    return 0;
  v2 = gameData + UNIT_STACK_TABLE_OFFSET;
  result = Map_GetBridgeCrossingCostOrZero(
             (unsigned __int8)*(_DWORD *)(v2 + UNIT_STACK_STRIDE * a1 + 4 * (*(_DWORD *)(v2 + UNIT_STACK_STRIDE * a1 + 316) - 1) + 320),
             (unsigned __int8)BYTE1(*(_DWORD *)(v2 + UNIT_STACK_STRIDE * a1 + 4 * (*(_DWORD *)(v2 + UNIT_STACK_STRIDE * a1 + 316) - 1) + 320)));
  if ( result )
    return 1;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00454AE0) --------------------------------------------------------
signed int  Rules_BuildRoadOrStepTowardQueuedPath(int a1, DWORD a2, double a3)
{
  int v3; // esi
  int v4; // eax
  int v5; // ebx
  int v6; // eax
  int v8; // ebx
  signed int v9; // edi
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  signed int v13; // eax
  int v14; // edx

  v3 = UNIT_STACK_STRIDE * a1;
  v4 = UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET;
  v5 = *(_DWORD *)(v4 + 316);
  v6 = v4 + 316;
  if ( !v5 )
    return 1;
  v8 = *(_DWORD *)(v6 + 4 * (v5 - 1) + 4);
  v9 = Facing_DirectionFromDelta8(
         (unsigned __int8)v8 - *(__int16 *)(gameData + v3 + UNIT_STACK_TABLE_OFFSET),
         BYTE1(v8) - *(__int16 *)(gameData + v3 + 147176));
  if ( Map_TileHasOwner(*(__int16 *)(v3 + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(v3 + gameData + 147176))
    && !Rules_IsQueuedPathTargetBridgeCrossing(v10) )
  {
    switch ( v9 )
    {
      case 1:
        v13 = UnitStack_MoveOneTileInDirection(v10, 0, a3);
        goto LABEL_10;
      case 3:
        v13 = UnitStack_MoveOneTileInDirection(v10, 4, a3);
LABEL_10:
        if ( v13 )
          goto LABEL_13;
        v14 = 2;
        break;
      case 5:
        if ( UnitStack_MoveOneTileInDirection(v10, 4, a3) )
          goto LABEL_13;
        v14 = 6;
        break;
      case 7:
        if ( UnitStack_MoveOneTileInDirection(v10, 0, a3) )
          goto LABEL_13;
        v14 = 6;
        break;
      default:
        v14 = v9;
        break;
    }
LABEL_12:
    UnitStack_MoveOneTileInDirection(v10, v14, a3);
  }
  else
  {
    switch ( v9 )
    {
      case 1:
        if ( !Road_Build(v10, 0, v9, a2, a3) )
        {
          v11 = v10;
          v12 = 0;
          goto LABEL_8;
        }
        break;
      case 3:
        if ( !Road_Build(v10, 4, v9, a2, a3) )
        {
          v12 = 4;
          v11 = v10;
LABEL_8:
          if ( !UnitStack_MoveOneTileInDirection(v11, v12, a3) )
          {
            v13 = Road_Build(v10, 2, v9, a2, a3);
            goto LABEL_10;
          }
        }
        break;
      case 5:
        if ( !Road_Build(v10, 4, v9, a2, a3)
          && !UnitStack_MoveOneTileInDirection(v10, 4, a3)
          && !Road_Build(v10, 6, v9, a2, a3) )
        {
          v14 = 6;
          goto LABEL_12;
        }
        break;
      case 7:
        if ( !Road_Build(v10, 0, v9, a2, a3)
          && !UnitStack_MoveOneTileInDirection(v10, 0, a3)
          && !Road_Build(v10, 6, v9, a2, a3) )
        {
          v14 = 6;
          goto LABEL_12;
        }
        break;
      default:
        if ( !Road_Build(v10, v9, v9, a2, a3) )
        {
          v14 = v9;
          goto LABEL_12;
        }
        break;
    }
  }
LABEL_13:
  *(_DWORD *)(UNIT_STACK_STRIDE * v10 + gameData + UNIT_STACK_TABLE_OFFSET + 316) = 0;
  return 0;
}
// 454B74: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454D20) --------------------------------------------------------
int  Rules_BuildTrapNearTile(DWORD a1, int a2, DWORD a3, double a4)
{
  int v5; // edx
  int v6; // ecx
  int result; // eax
  char v8; // bl
  int v9; // edx
  __int64 v10; // rax
  __int64 v11; // rax

  Debug_Log(a1, a3, a3, (int)aBuduj_pulapke2);
  result = (int)Unit_MoveTrackNearTile(a3, v6, v6, v5, a3);
  v8 = result;
  if ( result )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a3 + 316) )
      *(_DWORD *)(UNIT_STACK_STRIDE * a3 + gameData + UNIT_STACK_TABLE_OFFSET + 316) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * a3 + gameData + UNIT_STACK_TABLE_OFFSET + 316), (const void *)result, 0x194u);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(a3, v9, v8, a3, a4);
    v10 = (int)(*(__int16 *)(UNIT_STACK_STRIDE * a3 + gameData + UNIT_STACK_TABLE_OFFSET) - a1);
    if ( (int)((HIDWORD(v10) ^ v10) - HIDWORD(v10)) >= 2 )
      return 0;
    v11 = *(__int16 *)(UNIT_STACK_STRIDE * a3 + gameData + 147176) - a2;
    if ( (int)((HIDWORD(v11) ^ v11) - HIDWORD(v11)) >= 2 )
    {
      return 0;
    }
    else
    {
      Trap_New(a1, a2, a1, a3, a4);
      return 1;
    }
  }
  return result;
}
// 454D49: variable 'v6' is possibly undefined
// 454D49: variable 'v5' is possibly undefined
// 454DD0: variable 'v9' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454E70) --------------------------------------------------------
int  UnitStack_CalcArmyFactStrength(int a1)
{
  int total_strength;
  signed int i;
  char *unit_slot;
  int melee_strength;
  int shot_strength;

  total_strength = 0;
  unit_slot = (char *)(uintptr_t)(unsigned int)(a1 + 6);
  for ( i = 0; i < Unit_GetSquadCount(a1); ++i )
  {
    melee_strength = Unit_CalcEffectivenessA(unit_slot, 0);
    shot_strength = Unit_CalcEffectivenessC((__int16 *)unit_slot);
    if ( melee_strength <= shot_strength )
      total_strength += shot_strength;
    else
      total_strength += melee_strength;
    unit_slot += 31;
  }
  return total_strength;
}
//----- (00454ED0) --------------------------------------------------------
signed int  Rules_EnsureArmyFactForStack(__int16 *a1, int a2, double a3, char a4, DWORD a5)
{
  if ( (unsigned int)a1[3] > 0x28 && *(_DWORD *)((char *)a1 + 721) )
  {
    Rules_RetractArmyFact(a1, a2, (int)a1, a3);
    return 1;
  }
  else if ( *(_DWORD *)((char *)a1 + 721) )
  {
    return 0;
  }
  else
  {
    Rules_CreateArmyFact((__int16 *)a1, *(unsigned __int16 *)(2 * a1[1] + gameData + 200 * *a1 + 556374), (int)a1, a4, a5);
    return 1;
  }
}
// 454ED9: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;

//----- (00454F50) --------------------------------------------------------
signed int  Rules_LinkArmyFact(
        __int16 *a1,
        int a2,
        int a3,
        double a4,
        char a5,
        DWORD a6)
{
  signed int result; // eax
  int stack_record; // ecx
  int fact; // eax
  int value; // ebx
  _DWORD pa_value[6]; // [esp+18h] [ebp-34h] BYREF
  _DWORD x_value[6]; // [esp+0h] [ebp-4Ch] BYREF
  _DWORD y_value[6]; // [esp+30h] [ebp-1Ch] BYREF

  (void)a3;
  stack_record = (int)(uintptr_t)a1;
  result = Rules_EnsureArmyFactForStack(a1, a2, a4, a5, a6);
  if ( !result )
  {
    result = *(__int16 *)((uintptr_t)(unsigned int)stack_record + 6);
    if ( result != -1 )
    {
      fact = *(_DWORD *)((uintptr_t)(unsigned int)stack_record + 721);
      Instance_SetModifiedFlag(0);
      pa_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)aPa_2, stack_record, pa_value);
      value = *(_DWORD *)((uintptr_t)(unsigned int)pa_value[2] + 16);
      if ( value != UnitStack_GetMinCurrentActionPoints(stack_record) )
      {
        pa_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(UnitStack_GetMinCurrentActionPoints(stack_record));
        Rules_PutInstanceSlotValue(fact, (_BYTE *)aPa_3, stack_record, pa_value, a4);
      }
      x_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)aXxyy, stack_record, x_value);
      result = *a1;
      if ( *(_DWORD *)((uintptr_t)(unsigned int)x_value[2] + 16) != result )
      {
        x_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(result);
        Rules_PutInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 2), stack_record, x_value, a4);
      }
      y_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 4), stack_record, y_value);
      result = a1[1];
      if ( *(_DWORD *)((uintptr_t)(unsigned int)y_value[2] + 16) != result )
      {
        y_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(result);
        Rules_PutInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 6), stack_record, y_value, a4);
      }
      return Instance_SetModifiedFlag(1);
    }
  }
  return result;
}
// 4FFF84: using guessed type wchar_t aXxyy[4];

//----- (00455070) --------------------------------------------------------
signed int  Rules_SyncArmyFactStrength(
        __int16 *a1,
        int a2,
        int a3,
        char a4,
        DWORD a5,
        double a6)
{
  signed int result; // eax
  int stack_record;
  int fact;
  int previous_strength;
  int current_strength;
  _DWORD moc_value[6];

  (void)a3;
  stack_record = (int)(uintptr_t)a1;
  result = Rules_EnsureArmyFactForStack(a1, a2, a6, a4, a5);
  if ( !result )
  {
    result = *(__int16 *)((uintptr_t)(unsigned int)stack_record + 6);
    if ( result != -1 )
    {
      fact = *(_DWORD *)((uintptr_t)(unsigned int)stack_record + 721);
      moc_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, aMoc, stack_record, moc_value);
      previous_strength = *(_DWORD *)((uintptr_t)(unsigned int)moc_value[2] + 16);
      current_strength = UnitStack_CalcArmyFactStrength(stack_record);
      result = current_strength;
      if ( previous_strength != current_strength )
      {
        moc_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(current_strength);
        return Rules_PutInstanceSlotValue(fact, aMoc_0, stack_record, moc_value, a6);
      }
    }
  }
  return result;
}
//----- (004550F0) --------------------------------------------------------
signed int  Rules_SyncArmyFactOwner(
        __int16 *a1,
        char a2,
        DWORD a3,
        double a4)
{
  signed int result; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  _DWORD v8[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Rules_EnsureArmyFactForStack(a1, (int)a1, a4, a2, a3);
  if ( !result )
  {
    result = *(__int16 *)(v5 + 6);
    if ( result != -1 )
    {
      v8[1] = 1;
      v8[2] = Rules_AddIntegerValue(*(unsigned __int8 *)(v5 + 4));
      return Rules_PutInstanceSlotValue(*(_DWORD *)(v6 + 721), aGracz, v7, v8, a4);
    }
  }
  return result;
}
// 4550FF: variable 'v5' is possibly undefined
// 45512A: variable 'v6' is possibly undefined
// 455135: variable 'v7' is possibly undefined

//----- (00455150) --------------------------------------------------------
signed int  Rules_SyncCastleFactOwner(int a1, int a2, double a3)
{
  int v5 = 0; // ecx
  int castle_fact; // eax
  int castle_owner; // eax
  int building_table_delta; // edx
  int building_index; // edx
  _DWORD v7[9]; // [esp-4h] [ebp-24h] BYREF

  (void)a2;
  v7[7] = a2;
  v7[1] = 1;
  castle_owner = *(unsigned __int8 *)(a1 + 2);
  v7[2] = (int)(uintptr_t)Rules_AddIntegerValue(castle_owner);
  castle_fact = *(_DWORD *)(a1 + 463);
  if ( !castle_fact )
  {
    building_index = -1;
    building_table_delta = a1 - (gameData + BUILDING_TABLE_OFFSET);
    if ( building_table_delta >= 0 && building_table_delta % BUILDING_RECORD_SIZE == 0 )
    {
      building_index = building_table_delta / BUILDING_RECORD_SIZE;
      if ( (unsigned int)building_index >= 100u )
        building_index = -1;
    }
    Diagnostics_TraceWorldMapActionEvent(
      "rules_sync_castle_fact_missing",
      g_SelectedUnitIndex,
      a1,
      building_index,
      castle_owner);
    if ( building_index >= 0 )
    {
      Rules_AssertCastleFact((unsigned __int8 *)a1, building_index);
      castle_fact = *(_DWORD *)(a1 + 463);
    }
  }
  Diagnostics_TraceWorldMapActionEvent(
    "rules_sync_castle_fact_owner",
    g_SelectedUnitIndex,
    a1,
    castle_fact,
    castle_owner);
  if ( !castle_fact )
  {
    Lexer_ErrorRecover(1);
    return 0;
  }
  return Rules_PutInstanceSlotValue(castle_fact, aGracz_0, v5, v7, a3);
}

//----- (004551A0) --------------------------------------------------------
_DWORD * Rules_LogTrapFact(int a1, int a2)
{
  double v3; // st7
  int v4; // ecx
  char v6[200]; // [esp+0h] [ebp-C8h] BYREF

  v3 = sprintf_(v6, "(pulapka %d %d)", a1, a2);
  return Rules_Log(v6, v4, v3);
}
// 4551BC: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004551D0) --------------------------------------------------------
_DWORD * Rules_RetractTrapFact(int a1, int a2)
{
  double v3; // st7
  int v4; // ecx
  char v6[200]; // [esp+0h] [ebp-C8h] BYREF

  v3 = sprintf_(v6, "(kasuj pulapke %d %d)", a1, a2);
  return Rules_Log(v6, v4, v3);
}
// 4551EC: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455200) --------------------------------------------------------
_DWORD * Rules_LogTempleFact(int a1, int a2)
{
  double v3; // st7
  int v4; // ecx
  char v6[200]; // [esp+0h] [ebp-C8h] BYREF

  v3 = sprintf_(v6, "(swiatynia %d %d)", a1, a2);
  return Rules_Log(v6, v4, v3);
}
// 45521C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455230) --------------------------------------------------------
_DWORD * Rules_LogTreasureFact(int a1, int a2)
{
  double v3; // st7
  int v4; // ecx
  char v6[200]; // [esp+0h] [ebp-C8h] BYREF

  v3 = sprintf_(v6, "(skarb %d %d)", a1, a2);
  return Rules_Log(v6, v4, v3);
}
// 45524C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455260) --------------------------------------------------------
_DWORD * Rules_RetractTreasureFact(a1, a2)
int a1;
int a2;
{
  double v3; // st7
  int v4; // ecx
  char v6[200]; // [esp+0h] [ebp-C8h] BYREF

  v3 = sprintf_(v6, "(kasuj skarb %d %d)", a1, a2);
  return Rules_Log(v6, v4, v3);
}
// 45527C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455290) --------------------------------------------------------
_DWORD * Rules_RetractTempleFact(int a1, int a2, char a3, DWORD a4)
{
  int v5; // edx
  int v6; // ecx
  double v7; // st7
  int v8; // ecx
  char v10[200]; // [esp+0h] [ebp-CCh] BYREF
  int v11; // [esp+C8h] [ebp-4h]

  v11 = a2;
  Debug_Log(a1, a3, a4, (int)aKasuj_swiatyni);
  v7 = sprintf_(v10, "(kasuj swiatynie %d %d)", v6, v5);
  return Rules_Log(v10, v8, v7);
}
// 4552B4: variable 'v6' is possibly undefined
// 4552B4: variable 'v5' is possibly undefined
// 4552BE: variable 'v8' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004552D0) --------------------------------------------------------
int  Rules_AssertCastleFact(unsigned __int8 *a1, int a2)
{
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  char *v7; // eax
  const char *v8; // eax
  double v9; // st7
  int v10 = 0; // ecx
  _DWORD *v11; // eax
  const char *v16; // [esp-18h] [ebp-400h]
  const char *v17; // [esp-14h] [ebp-3FCh]
  const char *v18; // [esp-10h] [ebp-3F8h]
  const char *v19; // [esp-Ch] [ebp-3F4h]
  int v20; // [esp-8h] [ebp-3F0h]
  int v21; // [esp-4h] [ebp-3ECh]
  char v22[1000]; // [esp+0h] [ebp-3E8h] BYREF

  v21 = a1[1];
  v20 = *a1;
  if ( (a1[416] & 2) != 0 )
    v4 = aTak;
  else
    v4 = aNie;
  v19 = v4;
  if ( (a1[416] & 0x10) != 0 )
    v5 = aTak_0;
  else
    v5 = aNie_0;
  v18 = v5;
  if ( (a1[416] & 4) != 0 )
    v6 = aTak_1;
  else
    v6 = aNie_1;
  v17 = v6;
  if ( (a1[416] & 8) != 0 )
    v7 = aTak_2;
  else
    v7 = aNie_2;
  v16 = v7;
  if ( (a1[416] & 1) != 0 )
    v8 = aTak_3;
  else
    v8 = aNie_3;
  v9 = sprintf_(
         v22,
         "( ZAMEK%d of zamek (id %d)(gracz %d)(szpital %s)(szkola %s)(warsztat %s)(kuznia %s)(koszary %s)(x %d)(y %d)(moc 0))",
         a2,
         a2,
         a1[2],
         v8,
         v16,
         v17,
         v18,
         v19,
         v20,
         v21);
  v11 = Rules_AssertFact(v22, v10, v9);
  *(_DWORD *)(a1 + 463) = (int)(uintptr_t)v11;
  return Building_OnGarrisonChange(a2, (int)(uintptr_t)a1, 0.0);
}
// 455361: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004553A0) --------------------------------------------------------
_DWORD * Rules_RetractCastleFact(unsigned __int8 *a1, double a2)
{
  unsigned __int8 *v2; // edx
  int v3; // ecx

  v2 = a1;
  if ( *(_DWORD *)(a1 + 463) )
    Rules_RetractFactById(*(_DWORD *)(a1 + 463), a2);
  v3 = *v2;
  *(_DWORD *)(v2 + 463) = 0;
  return Rules_LogCastleDestroyedFact(v2[2], *(unsigned __int16 *)(TILE_INDEX(v3, v2[1])) - 0x8000);
}
// 4553B0: variable 'v2' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00455410) --------------------------------------------------------
int Game_GetTurnNumber()
{
  return *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00455430) --------------------------------------------------------
_DWORD * Rules_OnCastleUpdate(int a1, char a2, DWORD a3, double a4)
{
  return Building_Destroy(UNIT_RECORD(a1), a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00455450) --------------------------------------------------------
BOOL  Building_TryStartUpgradeByIndex(int a1)
{
  return Building_TryStartUpgrade((unsigned __int8 *)(UNIT_RECORD(a1)));
}
// 5202E4: using guessed type int gameData;

//----- (00455470) --------------------------------------------------------
int  Building_GetTaxRateByIndex(int a1)
{
  return *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * a1 + 510110) & 0x3F;
}
// 5202E4: using guessed type int gameData;

//----- (00455490) --------------------------------------------------------
signed int  Building_BuildSchoolByIndex(int a1, char a2, DWORD a3)
{
  return Building_BuildSchool((char *)(UNIT_RECORD(a1)), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004554B0) --------------------------------------------------------
signed int  Building_BuildSmithsByIndex(char a1, DWORD a2)
{
  return Building_BuildSmiths(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (004554D0) --------------------------------------------------------
int  Building_GetWallStrengthByIndex(int a1)
{
  return *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * a1 + 510095);
}
// 5202E4: using guessed type int gameData;

//----- (004554F0) --------------------------------------------------------
int  Building_GetMoneyByIndex(int a1)
{
  return *(_DWORD *)(gameData + BUILDING_RECORD_SIZE * a1 + 510112);
}
// 5202E4: using guessed type int gameData;

//----- (00455510) --------------------------------------------------------
int  Building_GetCastleStrengthByIndex(int a1)
{
  return Building_GetTotalValue(UNIT_RECORD(a1));
}
// 5202E4: using guessed type int gameData;

//----- (00455530) --------------------------------------------------------
signed int  Building_BuildBarracksByIndex(int a1, char a2, DWORD a3)
{
  return Building_BuildBarracks(a1, a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455550) --------------------------------------------------------
signed int  Building_BuildHospitalByIndex(char a1, DWORD a2)
{
  return Building_BuildHospital(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (00455580) --------------------------------------------------------
int  Building_GetTechLevelByIndex(int a1)
{
  return *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * a1 + 510118) & 7;
}
// 5202E4: using guessed type int gameData;

//----- (004555A0) --------------------------------------------------------
int  Building_GetTypeByIndex(int a1)
{
  return *(char *)(gameData + BUILDING_RECORD_SIZE * a1 + 509678);
}
// 5202E4: using guessed type int gameData;

//----- (004555C0) --------------------------------------------------------
signed int  Building_BuildWorkshopByIndex(char a1, DWORD a2)
{
  return Building_BuildWorkshop(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (004555E0) --------------------------------------------------------
int  Building_GetSatisfactionByIndex(int a1)
{
  return *(char *)(gameData + BUILDING_RECORD_SIZE * a1 + 510108);
}
// 5202E4: using guessed type int gameData;

//----- (00455600) --------------------------------------------------------
int  Building_GetPeasantCountByIndex(int a1)
{
  int result; // eax

  LOWORD(result) = *(_WORD *)(gameData + BUILDING_RECORD_SIZE * a1 + 510104);
  BYTE1(result) &= 0xFu;
  return (unsigned __int16)result;
}
// 5202E4: using guessed type int gameData;

//----- (00455620) --------------------------------------------------------
BOOL  Building_HasProductionByIndex(int a1)
{
  return *(char *)(gameData + BUILDING_RECORD_SIZE * a1 + 510088) != -1;
}
// 5202E4: using guessed type int gameData;

//----- (00455650) --------------------------------------------------------
BOOL  Building_CanStartUpgradeByIndex(int a1)
{
  return Building_CanStartUpgrade((unsigned __int8 *)(UNIT_RECORD(a1)));
}
// 5202E4: using guessed type int gameData;

//----- (00455670) --------------------------------------------------------
int  Building_GetGarrisonCountByIndex(int a1)
{
  return Building_CountGarrison(UNIT_RECORD(a1));
}
// 5202E4: using guessed type int gameData;

//----- (00455690) --------------------------------------------------------
BOOL  Building_IsGarrisonFullByIndex(int a1)
{
  return Building_CountGarrison(UNIT_RECORD(a1)) == 12;
}
// 5202E4: using guessed type int gameData;

//----- (004556C0) --------------------------------------------------------
__int16  Building_RepairUnitByIndex(int a1, int a2, DWORD a3)
{
  return Building_RepairUnit(UNIT_RECORD(a1), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004556E0) --------------------------------------------------------
_BYTE * Building_TrainUnitByIndex(int a1, char a2, DWORD a3)
{
  return Building_TrainUnit(UNIT_RECORD(a1), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455700) --------------------------------------------------------
int  Building_SetUnitProductionByIndex(int a1, char a2, DWORD a3)
{
  return Building_SetUnitProduction(UNIT_RECORD(a1), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455720) --------------------------------------------------------
int  Building_RemoveUnitLicenceByIndex(int a1, unit_type a2, DWORD a3)
{
  return Building_RemoveUnitLicence(UNIT_RECORD(a1), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455740) --------------------------------------------------------
void  Building_AdjustTaxRateByIndex(int a1, int ebx0, float a3)
{
  double v3; // st7
  double v4; // st7
  int v5; // edx
  char v6; // ah
  float v7; // [esp+0h] [ebp-10h]

  v3 = (double)(*(_BYTE *)(BUILDING_RECORD_SIZE * a1 + gameData + 510110) & 0x3F) + a3;
  v7 = v3;
  if ( v3 <= g_Building_MaxTaxRate )
  {
    v4 = v7;
    _CHP(ebx0, LODWORD(v7));
    v6 = *(_BYTE *)(v5 + 510110) & 0xC0;
    *(_BYTE *)(v5 + 510110) = v6;
    *(_BYTE *)(v5 + 510110) = (int)v4 & 0x3F | v6;
  }
}
// 455791: variable 'v5' is possibly undefined
// 5000C6: using guessed type float flt_5000C6;
// 5202E4: using guessed type int gameData;

//----- (004557C0) --------------------------------------------------------
signed int  Building_HasUnitLicenceByIndex(int a1, unit_type a2)
{
  return Building_HasUnitLicence(UNIT_RECORD(a1), a2);
}
// 5202E4: using guessed type int gameData;

//----- (004557E0) --------------------------------------------------------
BOOL  Building_BuyUnitLicenceByIndex(int a1, unit_type a2, DWORD a3)
{
  return Building_BuyUnitLicence(UNIT_RECORD(a1), a2, gameData + BUILDING_TABLE_OFFSET, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455800) --------------------------------------------------------
BOOL  Building_CanBuyUnitLicenceByIndex(int a1, unit_type a2)
{
  return Building_IsUnitLicenceEligible((char *)(UNIT_RECORD(a1)), a2);
}
// 5202E4: using guessed type int gameData;

//----- (00455830) --------------------------------------------------------
BOOL  Rules_BuildCastle(int a1, DWORD a2, double a3, char *a4)
{
  return Building_New(a1, a2, a3, a4, 0);
}

//----- (00455850) --------------------------------------------------------
signed int  Building_FindUnitLicenceSlotIndexOrZero(int a1, unit_type a2)
{
  signed int result; // eax
  int v4; // ebx

  result = 0;
  v4 = BUILDING_RECORD_SIZE * a1;
  while ( *(char *)(v4 + gameData + result + 510076) != a2 )
  {
    if ( ++result >= 12 )
      return 0;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00455890) --------------------------------------------------------
signed int  Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero(int a1)
{
  signed int result; // eax
  int v3; // ecx
  int v4; // edx

  result = 0;
  v3 = BUILDING_RECORD_SIZE * a1;
  while ( 1 )
  {
    v4 = *(char *)(v3 + gameData + result + 510076);
    if ( v4 != -1 && v4 != UNIT_TYPE_PEASANT && v4 != UNIT_TYPE_BUILDER )
      break;
    if ( ++result >= 12 )
      return 0;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004558D0) --------------------------------------------------------
signed int  Building_UnitsLeaveReadyGarrisonSlots(int a1, int a2, double a3)
{
  int i; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ebx
  int v9; // esi
  int v11; // ecx
  int v13[10]; // [esp+4h] [ebp-44h] BYREF
  int v14; // [esp+2Ch] [ebp-1Ch]
  int v15; // [esp+30h] [ebp-18h]
  int v16; // [esp+40h] [ebp-8h]

  v16 = a2;
  v14 = a1;
  for ( i = 0; i != 10; v13[i - 1] = -1 )
    ++i;
  v5 = 0;
  v15 = BUILDING_RECORD_SIZE * v14;
  v6 = 0;
  v7 = 0;
  do
  {
    v8 = v15 + gameData;
    v9 = v15 + gameData + v6;
    if ( *(__int16 *)(v9 + 509692) != -1
      && *(_BYTE *)(v9 + 509701) == 100
      && !((unsigned __int8)(4 * *(_BYTE *)(v8 + v5 + 510064)) >> 5)
      && (*(_BYTE *)(v8 + v5 + 510064) & 7) == 0 )
    {
      v13[v7++] = v5;
    }
    ++v5;
    v6 += 31;
  }
  while ( v5 < 10 && v7 < 5 );
  if ( v13[0] == -1 )
    return 0;
  if ( Building_HasFreeAdjacentExitTile((unsigned __int8 *)(UNIT_RECORD(v14))) )
    return Building_UnitsLeave((unsigned __int8 *)(v11 + gameData + BUILDING_TABLE_OFFSET), v13, a3);
  return -1;
}
// 4559BC: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004559D0) --------------------------------------------------------
signed int  Building_HasTrainableIdleGarrisonUnit(int a1)
{
  int v2; // edx
  int v3; // eax
  int v4; // edi
  int v5; // esi

  v2 = 0;
  v3 = 0;
  v4 = BUILDING_RECORD_SIZE * a1;
  while ( 1 )
  {
    v5 = v4 + gameData + v2;
    if ( *(__int16 *)(v5 + 509692) != -1
      && (*(_BYTE *)(v5 + 509704) & 3u) < 2
      && (*(_BYTE *)(v4 + gameData + v3 + 510064) & 7) == 0 )
    {
      break;
    }
    ++v3;
    v2 += 31;
    if ( v3 >= 12 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00455A50) --------------------------------------------------------
signed int  Building_HasRepairableIdleGarrisonUnit(int a1)
{
  int v2; // edx
  int v3; // eax
  int v4; // edi
  int v5; // ebx

  v2 = 0;
  v3 = 0;
  v4 = BUILDING_RECORD_SIZE * a1;
  while ( 1 )
  {
    v5 = v4 + gameData + v2;
    if ( *(__int16 *)(v5 + 509692) != -1
      && *(char *)(v5 + 509701) < 50
      && !((unsigned __int8)(4 * *(_BYTE *)(v4 + gameData + v3 + 510064)) >> 5) )
    {
      break;
    }
    ++v3;
    v2 += 31;
    if ( v3 >= 12 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00455AD0) --------------------------------------------------------
int  Building_StartTrainingIdleGarrisonUnits(int a1)
{
  int v1; // ecx
  int v2; // ebx
  DWORD v3; // ebp
  DWORD v4; // edi
  int result; // eax

  v1 = 0;
  v2 = 0;
  v3 = BUILDING_RECORD_SIZE * a1;
  do
  {
    v4 = gameData + v3;
    result = v2 + gameData + v3;
    if ( *(__int16 *)(result + 509692) != -1 )
    {
      result = *(_BYTE *)(result + 509704) & 3;
      if ( result < 2 )
      {
        result = v1 + v4;
        if ( (*(_BYTE *)(v1 + v4 + 510064) & 7) == 0 )
        {
          result = (unsigned __int8)(4 * *(_BYTE *)(result + 510064)) >> 5;
          if ( !result )
            result = (int)Building_TrainUnit(v3 + gameData + BUILDING_TABLE_OFFSET, v2, v3);
        }
      }
    }
    ++v1;
    v2 += 31;
  }
  while ( v1 < 12 );
  return result;
}
// 455B40: variable 'v1' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00455B50) --------------------------------------------------------
__int16  Building_StartRepairIdleGarrisonUnits(int a1)
{
  int v1; // ecx
  int v2; // ebx
  int v3; // edi
  __int16 result; // ax
  int v5; // edx
  DWORD v6; // ebp
  int v7; // esi

  v1 = 0;
  v2 = 0;
  v3 = BUILDING_RECORD_SIZE * a1;
  do
  {
    result = gameData;
    v5 = v2 + v3 + gameData;
    v6 = *(__int16 *)(v5 + 509692);
    if ( v6 != -1 && *(char *)(v5 + 509701) <= 90 )
    {
      v7 = v1 + v3 + gameData;
      if ( (*(_BYTE *)(v7 + 510064) & 7) == 0 && !((unsigned __int8)(4 * *(_BYTE *)(v7 + 510064)) >> 5) )
        result = Building_RepairUnit(v3 + gameData + BUILDING_TABLE_OFFSET, v1, v6);
    }
    ++v1;
    v2 += 31;
  }
  while ( v1 < 12 );
  return result;
}
// 455BB8: variable 'v1' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00455BD0) --------------------------------------------------------
signed int  Building_UnitsLeaveByUnitType(int a1, unit_type a2, int a3, double a4)
{
  int i; // eax
  int v7; // edx
  int v8; // eax
  int v10; // edi
  int v12[14]; // [esp+4h] [ebp-38h] BYREF

  v12[12] = a3;
  for ( i = 0; i != 10; v12[i - 1] = -1 )
    ++i;
  v7 = 0;
  v8 = 0;
  while ( *(__int16 *)(BUILDING_RECORD_SIZE * a1 + gameData + v8 + 509692) != a2 )
  {
    v8 += 31;
    ++v7;
    if ( v8 >= 310 )
    {
      if ( v12[0] == -1 )
        return 0;
      goto LABEL_10;
    }
  }
  v12[0] = v7;
  if ( v7 == -1 )
    return 0;
LABEL_10:
  v10 = BUILDING_RECORD_SIZE * a1;
  if ( Building_HasFreeAdjacentExitTile((unsigned __int8 *)(v10 + gameData + BUILDING_TABLE_OFFSET)) )
    return Building_UnitsLeave((unsigned __int8 *)(v10 + gameData + BUILDING_TABLE_OFFSET), v12, a4);
  else
    return -1;
}
// 5202E4: using guessed type int gameData;

//----- (00455C90) --------------------------------------------------------
_DWORD * Rules_LogCastleSiteFact(int a1, int a2)
{
  char v6[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v6, "(zamek_place %d %d)", a1, a2);
  return Rules_Log(v6, 0, 0.0);
}

//----- (00455CC0) --------------------------------------------------------
_DWORD * Rules_LogBuildingTransferFact(int a1, int a2, int a3)
{
  char v7[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v7, "(budowanie transfer 0 0 %d %d %d)", a1, a2, a3);
  return Rules_Log(v7, 0, 0.0);
}

//----- (00455CF0) --------------------------------------------------------
_DWORD * Rules_LogNewCastleFact(int a1, int a2)
{
  char v6[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v6, "(powstal-nowy-zamek %d %d)", a1, a2);
  return Rules_Log(v6, 0, 0.0);
}

//----- (00455D20) --------------------------------------------------------
_DWORD * Rules_LogCastleDestroyedFact(int a1, int a2)
{
  char v6[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v6, "(zginal-zamek %d %d)", a1, a2);
  return Rules_Log(v6, 0, 0.0);
}

//----- (00455D50) --------------------------------------------------------
_DWORD * Rules_LogCastleSchemeFact(int a1, int a2)
{
  unsigned int scheme_index; // eax
  char v9[52]; // [esp+0h] [ebp-3Ch] BYREF

  scheme_index = Rng_RandRange(1, 3);
  sprintf_(v9, "(schemat %d %d %d)", a1, a2, scheme_index);
  return Rules_Log(v9, 0, 0.0);
}

//----- (00455D90) --------------------------------------------------------
_DWORD * Rules_LogBuildingCapturedFact(int a1, int a2, int a3)
{
  char v7[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v7, "(zdobyty %d %d %d)", a1, a2, a3);
  return Rules_Log(v7, 0, 0.0);
}

//----- (00455DC0) --------------------------------------------------------
_DWORD * Rules_LogCastleUnderConstructionFact(int a1)
{
  char v5[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v5, "(zamek w budowie %d)", a1);
  return Rules_Log(v5, 0, 0.0);
}

//----- (00455DF0) --------------------------------------------------------
_DWORD *__fastcall Rules_LogCastleBuiltFactAndScheme(int a1, int a2)
{
  char v7[52]; // [esp+0h] [ebp-38h] BYREF

  sprintf_(v7, "(zbudowano zamek %d)", a2);
  Rules_Log(v7, 0, 0.0);
  return Rules_LogCastleSchemeFact(a1, a2);
}

//----- (00455E20) --------------------------------------------------------
_DWORD * Rules_LogAssignedCastleFact(int a1, int a2)
{
  char v6[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v6, "(wyznaczony zamek %d %d)", a1, a2);
  return Rules_Log(v6, 0, 0.0);
}

//----- (00455E50) --------------------------------------------------------
_DWORD * Rules_LogAssignedPlayerFact(int a1, int a2)
{
  char v6[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(v6, "(wyznaczony gracz %d %d)", a1, a2);
  return Rules_Log(v6, 0, 0.0);
}

//----- (00455E80) --------------------------------------------------------
BOOL  Building_SelectedUnitLicenceMatchesTypeByIndex(int a1, unit_type a2)
{
  int v2; // ecx
  int v3; // eax

  v2 = BUILDING_RECORD_SIZE * a1 + gameData;
  v3 = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(v2 + 509674);
  return v3 != -1 && *(char *)(v2 + v3 + 510076) == a2;
}
// 5202E4: using guessed type int gameData;

//----- (00455EC0) --------------------------------------------------------
int  Player_GetInternedNameByIndex(int a1, int a2, int a3)
{
  char *v4; // edx
  char *v5; // esi
  int v6; // eax
  int v7; // ebx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx

  v4 = (char *)nmalloc_(a3, a2);
  v5 = v4;
  v6 = 0;
  v7 = PLAYER_DATA_STRIDE * a1;
  do
  {
    v8 = v7 + gameData;
    ++v4;
    LOBYTE(v8) = *(_BYTE *)(v7 + gameData + v6++ + 140028);
    *(v4 - 1) = v8;
  }
  while ( v6 <= 11 );
  v5[11] = 0;
  Str_Intern(v5, v8);
  nfree_(v9);
  return v10;
}
// 455F08: variable 'v9' is possibly undefined
// 455F0D: variable 'v10' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00455F20) --------------------------------------------------------
signed int  Building_HasGarrisonUnitTypeByIndex(int a1, unit_type a2)
{
  int v2; // ebx
  int v3; // eax

  v2 = BUILDING_RECORD_SIZE * a1;
  v3 = 0;
  while ( *(__int16 *)(v2 + gameData + v3 + 509692) != a2 )
  {
    v3 += 31;
    if ( v3 >= 310 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00455F60) --------------------------------------------------------
signed int  Map_IsCastleSiteDistanceMinimal(int a1, int a2, int a3, int a4)
{
  int slot; // edx
  float candidate_distance; // [esp+0h] [ebp-Ch]
  signed int minimum_distance; // [esp+4h] [ebp-8h]

  minimum_distance = Math_CeilSqrt((a1 - a4) * (a1 - a4) + (a2 - a3) * (a2 - a3));
  if ( g_CastleSiteAnchorRows[1] == -1 )
    return 1;
  for ( slot = 1; slot < CASTLE_SITE_ANCHOR_CACHE_COUNT && g_CastleSiteAnchorRows[slot] != -1; ++slot )
  {
    candidate_distance = (float)minimum_distance;
    if ( (double)Math_CeilSqrt(
                   (g_CastleSiteAnchorColumns[slot] - a3) * (g_CastleSiteAnchorColumns[slot] - a3)
                 + (g_CastleSiteAnchorRows[slot] - a4) * (g_CastleSiteAnchorRows[slot] - a4)) < candidate_distance )
      return 0;
  }
  return 1;
}

//----- (00455FF0) --------------------------------------------------------
void Map_RebuildCastleSiteAnchorCache()
{
  int anchor_slot;
  int row;
  int column;

  anchor_slot = 0;
  for ( row = 1; row < CASTLE_SITE_ANCHOR_CACHE_COUNT; ++row )
  {
    g_CastleSiteAnchorRows[row] = -1;
    g_CastleSiteAnchorColumns[row] = -1;
  }
  for ( row = 0; row < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET); ++row )
  {
    for ( column = 0; column < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET); ++column )
    {
      if ( MapTile_IsCastleFoundationAnchorTile(row, column, 2) )
      {
        if ( ++anchor_slot >= CASTLE_SITE_ANCHOR_CACHE_COUNT )
          return;
        g_CastleSiteAnchorRows[anchor_slot] = row;
        g_CastleSiteAnchorColumns[anchor_slot] = column;
      }
    }
  }
}
// 5202E4: using guessed type int gameData;
// 544570: using guessed type int g_CastleSiteAnchorRows[];
// 544574: using guessed type int g_CastleSiteAnchorColumns[];

//----- (00456070) --------------------------------------------------------
int  Building_CalcGarrisonFactStrength(int a1)
{
  int buildingOffset; // ebx
  int totalStrength; // edi
  int slotOffset; // ecx
  int slotPtr; // esi
  int meleeStrength; // eax
  int damageStrength; // eax

  buildingOffset = BUILDING_RECORD_SIZE * a1;
  totalStrength = 0;
  for ( slotOffset = 0; slotOffset != 372; slotOffset += 31 )
  {
    slotPtr = gameData + buildingOffset + 509692 + slotOffset;
    if ( *(__int16 *)slotPtr != -1 )
    {
      meleeStrength = Unit_CalcEffectivenessA((char *)slotPtr, 0);
      damageStrength = Unit_CalcEffectivenessC((__int16 *)slotPtr);
      if ( meleeStrength <= damageStrength )
        totalStrength += damageStrength;
      else
        totalStrength += meleeStrength;
    }
  }
  return totalStrength;
}
// 5202E4: using guessed type int gameData;

//----- (00456130) --------------------------------------------------------
int  Building_OnGarrisonChange(int a1, int a2, double a3)
{
  int v4; // esi
  int result; // eax
  int v6; // ebx
  _DWORD v9[2]; // [esp-4h] [ebp-28h] BYREF
  int *v10; // [esp+4h] [ebp-20h]
  int v11; // [esp+1Ch] [ebp-8h]

  v11 = a2;
  v4 = BUILDING_RECORD_SIZE * a1;
  result = BUILDING_RECORD_SIZE * a1 + gameData;
  if ( *(_DWORD *)(result + 510137) )
  {
    v9[1] = 1;
    Rules_GetInstanceSlotValue(*(_DWORD *)(result + 510137), aMoc_1, a1, v9);
    v6 = v10[4];
    result = Building_CalcGarrisonFactStrength(a1);
    if ( v6 != result )
    {
      v10 = Rules_AddIntegerValue(result);
      return Rules_PutInstanceSlotValue(*(_DWORD *)(v4 + gameData + 510137), aMoc_2, a2, v9, a3);
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004561B0) --------------------------------------------------------
signed int Rules_RegisterBuildingHostFunctions()
{
  CRT_ProbeStackFrame(36);
  Rules_RegisterHostFunction(aLeczenie, 118, (int)aLeczenie, (int)&Rules_HostHealing, (int)a11i_3);
  Rules_RegisterHostFunction(aSzkolenie, 118, (int)aSzkolenie, (int)&Rules_HostTraining, (int)a11i_3);
  Rules_RegisterHostFunction(aPalBudowle, 118, (int)aPalbudowle, (int)&Rules_HostBurnBuildings, (int)a11i_3);
  Rules_RegisterHostFunction(aUpgradeWall, 118, (int)aUpgradewall, (int)&Rules_HostUpgradeWall, (int)a11i_3);
  Rules_RegisterHostFunction(aZmienPodatek, 118, (int)aZmienpodatek, (int)&Rules_HostChangeTax, (int)a22iif);
  Rules_RegisterHostFunction(aRemoveLicence, 118, (int)aRemovelicence, (int)&Rules_HostRemoveLicence, (int)a22i);
  Rules_RegisterHostFunction(aZacznijLeczeni, 118, (int)aZacznijleczeni, (int)&Rules_HostStartHealing, (int)a22i);
  Rules_RegisterHostFunction(aZacznijSzkolen, 118, (int)aZacznijszkolen, (int)&Rules_HostStartTraining, (int)a22i);
  Rules_RegisterHostFunction(aZacznijProdukc, 118, (int)aZacznijprodukc, (int)&Rules_HostStartProduction, (int)a22i);
  Rules_RegisterHostFunction(aKupSzkola, 98, (int)aKupszkola, (int)&Rules_HostBuySchool, (int)a11i_3);
  Rules_RegisterHostFunction(aKupKuznia, 98, (int)aKupkuznia, (int)&Rules_HostBuyForge, (int)a11i_3);
  Rules_RegisterHostFunction(aIsLicence, 98, (int)aIslicence, (int)&Rules_HostIsLicence, (int)a22i);
  Rules_RegisterHostFunction(aBuyLicence, 98, (int)aBuylicence, (int)&Rules_HostBuyLicence, (int)a22i);
  Rules_RegisterHostFunction(aKupSzpital, 98, (int)aKupszpital, (int)&Rules_HostBuyHospital, (int)a11i_3);
  Rules_RegisterHostFunction(aBudujZamek, 98, (int)aBudujzamek, (int)&Rules_HostBuildCastle, (int)a55iiiiis);
  Rules_RegisterHostFunction(aKupKoszary, 98, (int)aKupkoszary, (int)&Rules_HostBuyBarracks, (int)a11i_3);
  Rules_RegisterHostFunction(aKupWarsztat, 98, (int)aKupwarsztat, (int)&Rules_HostBuyWorkshop, (int)a11i_3);
  Rules_RegisterHostFunction(aIsProduction, 98, (int)aIsproduction, (int)&Rules_HostIsProduction, (int)a11i_3);
  Rules_RegisterHostFunction(aCzyMinimalny, 98, (int)aCzyminimalny, (int)&Rules_HostIsMinimal, (int)a44i);
  Rules_RegisterHostFunction(aCanBuyLicence, 98, (int)aCanbuylicence, (int)&Rules_HostCanBuyLicence, (int)a22i);
  Rules_RegisterHostFunction(aIsProductionAn, 98, (int)aIsproductionan, (int)&Rules_HostIsProductionAny, (int)a22i);
  Rules_RegisterHostFunction(aMaxIloscOddzia, 98, (int)aMaxiloscoddzia, (int)&Rules_HostMaxTroopCount, (int)a11i_3);
  Rules_RegisterHostFunction(aJednostkiDoSzk, 98, (int)aJednostkidoszk, (int)&Rules_HostUnitsToSchool, (int)a11i_3);
  Rules_RegisterHostFunction(aJednostkiDoSzp, 98, (int)aJednostkidoszp, (int)&Rules_HostUnitsToHospital, (int)a11i_3);
  Rules_RegisterHostFunction(aJestJednostkaW, 98, (int)aJestjednostkaw, (int)&Rules_HostUnitInCastleExists, (int)a22i);
  Rules_RegisterHostFunction(aPodatek, 105, (int)aPodatek, (int)&Rules_HostTax, (int)a11i_3);
  Rules_RegisterHostFunction(aPieniadze, 105, (int)aPieniadze, (int)&Rules_HostMoney, (int)a11i_3);
  Rules_RegisterHostFunction(aSilaMurow, 105, (int)aSilamurow, (int)&Rules_HostWallStrength, (int)a11i_3);
  Rules_RegisterHostFunction(aSilaZamku, 105, (int)aSilazamku, (int)&Rules_HostCastleStrength, (int)a11i_3);
  Rules_RegisterHostFunction(aNumerTury, 105, (int)aNumertury, (int)&Rules_HostTurnNumber, (int)a00i_0);
  Rules_RegisterHostFunction(aPoziomTech, 105, (int)aPoziomtech, (int)&Rules_HostTechLevel, (int)a11i_3);
  Rules_RegisterHostFunction(aZadowolenie, 105, (int)aZadowolenie, (int)&Rules_HostHappiness, (int)a11i_3);
  Rules_RegisterHostFunction(aTypBudowli, 105, (int)aTypbudowli, (int)&Rules_HostBuildingType, (int)a11i_3);
  Rules_RegisterHostFunction(aSilaGracza, 105, (int)aSilagracza, (int)&Rules_HostPlayerStrength, (int)a11i_3);
  Rules_RegisterHostFunction(aIloscChlopow, 105, (int)aIloscchlopow, (int)&Rules_HostPeasantCount, (int)a11i_3);
  Rules_RegisterHostFunction(aLicencjaIndex, 105, (int)aLicencjaindex, (int)&Rules_HostLicenceIndex, (int)a22i);
  Rules_RegisterHostFunction(aLicencjaInd, 105, (int)aLicencjaind, (int)&Rules_HostLicenceInd, (int)a11i_3);
  Rules_RegisterHostFunction(aIloscOddzialow, 105, (int)aIloscoddzialow, (int)&Rules_HostTroopCount, (int)a11i_3);
  Rules_RegisterHostFunction(aCanUpgradeWall, 105, (int)aCanupgradewall, (int)&Rules_HostCanUpgradeWall, (int)a11i_3);
  Rules_RegisterHostFunction(aWyprowadzChlop, 105, (int)aWyprowadzchlop, (int)&Rules_HostLeadOutPeasants, (int)a44i);
  Rules_RegisterHostFunction(aWyprowadzenieO, 105, (int)aWyprowadzenieo, (int)&Rules_HostLeadOutTroop, (int)a22i);
  Rules_RegisterHostFunction(aWyprowadzeni_1, 105, (int)aWyprowadzeni_0, (int)&Rules_HostLeadOutTroops, (int)a11i_3);
  return Rules_RegisterHostFunction(aNazwaZamku, 115, (int)aNazwazamku, (int)&Rules_HostCastleName, (int)a11i_3);
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (004570E3) --------------------------------------------------------
signed int Rules_RegisterArmyHostFunctions()
{
  CRT_ProbeStackFrame(36);
  Rules_RegisterHostFunction(aWejdzDoZamku, 98, (int)aWejdzdozamku, (int)&Rules_HostEnterCastle, (int)a22i_0);
  Rules_RegisterHostFunction(aDolaczDoOddzia, 98, (int)aDolaczdoarmii, (int)&Rules_HostJoinTroop, (int)a22i_0);
  Rules_RegisterHostFunction(aPrzegrupujOddz, 98, (int)aPrzegrupujarmi, (int)&Rules_HostRegroupTroops, (int)a22i_0);
  Rules_RegisterHostFunction(aPrzegrupujZame, 98, (int)aPrzegrupujzame, (int)&Rules_HostRegroupCastle, (int)a22i_0);
  Rules_RegisterHostFunction(aLiczbaWolnychM, 105, (int)aLiczbawolnychm, (int)&Rules_HostCastleFreeSlotCount, (int)a11i_0);
  Rules_RegisterHostFunction(aZnajdzDrogeWPo, 98, (int)aZnajdzdrogewpo, (int)&Rules_HostFindRoadNearCastle, (int)a22i_0);
  Rules_RegisterHostFunction(aMocPrzeciwnika, 105, (int)aMocprzeciwnika, (int)&Rules_HostEnemyPowerAtWalls, (int)a11i_0);
  Rules_RegisterHostFunction(aStanOsobArmii, 105, (int)aStanosobarmii, (int)&Rules_HostArmyHeadcount, (int)a22i_0);
  Rules_RegisterHostFunction(aArmiaMaJednost, 98, (int)aArmiamajednost, (int)&Rules_HostArmyHasUnitsOfType, (int)a22i_0);
  Rules_RegisterHostFunction(aArmiaTylkoJedn, 98, (int)aArmiatylkojedn, (int)&Rules_HostArmyHasOnlyUnitType, (int)a22i_0);
  Rules_RegisterHostFunction(aMaJednostkiDoL, 98, (int)aMajednostkidol, (int)&Rules_HostHasUnitsToHeal, (int)a11i_0);
  Rules_RegisterHostFunction(aZnajdzZamekDoL, 98, (int)aZnajdzzamekdol, (int)&Rules_HostFindCastleForHealing, (int)a11i_0);
  Rules_RegisterHostFunction(aIdzDoLeczenia, 98, (int)aIdzdoleczenia, (int)&Rules_HostGoToHealing, (int)a11i_0);
  Rules_RegisterHostFunction(aJestZarazaWZam, 98, (int)aJestzarazawzam, (int)&Rules_HostPlagueInCastleExists, (int)a11i_0);
  Rules_RegisterHostFunction(aJestZarazaWOdd, 98, (int)aJestzarazawodd, (int)&Rules_HostPlagueInTroopExists, (int)a11i_0);
  Rules_RegisterHostFunction(aOdlaczJednostk, 98, (int)aOdlaczjednostk, (int)&Rules_HostDetachWeakUnits, (int)a11i_0);
  Rules_RegisterHostFunction(aOdlaczJednos_0, 98, (int)aOdlaczjednos_0, (int)&Rules_HostDetachUnitsOfType, (int)a22i_0);
  Rules_RegisterHostFunction(aMaszerujWzdluz, 98, (int)aMaszerujwzdluz, (int)&Rules_HostMarchAlongRoad, (int)a11i_0);
  return Rules_RegisterHostFunction(aZnajdzNajlepsz, 105, (int)aZnajdz_najleps, (int)&Rules_HostFindBest, (int)a55i);
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (004577F0) --------------------------------------------------------
signed int  UnitStack_HasUnitsNeedingHealing(int a1)
{
  int v1; // esi
  __int16 *v2; // eax
  int i; // edx
  int v4; // ecx

  v1 = 0;
  v2 = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 6);
  for ( i = 0; i < 10; ++i )
  {
    v4 = *v2;
    if ( v4 == -1 )
      break;
    if ( *((char *)v2 + 9) <= 50 && (unsigned __int8)g_UnitTypeRole[88 * v4] >= 3u )
      v1 = 1;
    v2 = (__int16 *)((char *)v2 + 31);
  }
  return v1;
}
// 5202E4: using guessed type int gameData;

//----- (00457860) --------------------------------------------------------
BOOL  UnitStack_FindPathToNearestHospitalCastle(DWORD a1)
{
  int v2; // edi
  int v3; // ebx
  int v4; // eax
  unsigned int v5; // ecx
  _DWORD *v6; // eax
  const void *v7; // esi
  int v8; // eax
  int v9; // ecx
  int v11; // [esp+0h] [ebp-28h]
  int v12; // [esp+8h] [ebp-20h]
  int v13; // [esp+Ch] [ebp-1Ch]

  v2 = -1;
  v3 = 0;
  v11 = gameData + BUILDING_TABLE_OFFSET;
LABEL_2:
  v4 = UNIT_RECORD(v3);
  v5 = *(char *)(v4 + 4);
  if ( v5 < 4 && *(__int16 *)(v4 + 16) != -1 && (*(_DWORD *)(v11 + 416) & 1) == 1 )
  {
    v6 = (_DWORD *)Building_GenerateApproachTrack(a1, v3, v5, v3, a1);
    v7 = v6;
    if ( v6 )
    {
      v13 = v6[1];
      if ( v2 == -1 )
      {
        qmemcpy((void *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET + 316), v6, 0x194u);
        v8 = HIWORD(v13);
      }
      else
      {
        if ( HIWORD(v13) >= v12 )
          goto LABEL_9;
        j__nfree_();
        qmemcpy((void *)(v9 + gameData + UNIT_STACK_TABLE_OFFSET + 316), v7, 0x194u);
        v8 = HIWORD(v13);
      }
      v2 = v3;
      v12 = v8;
LABEL_9:
      j__nfree_();
    }
  }
  while ( 1 )
  {
    ++v3;
    v11 += 467;
    if ( v3 >= 100 )
      return v2 != -1;
    if ( v3 >= 0 )
      goto LABEL_2;
  }
}
// 457945: conditional instruction was optimized away because ebx.4<64u
// 457899: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 45795C: variable 'v12' is possibly undefined
// 45797E: variable 'v9' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004579B0) --------------------------------------------------------
BOOL  UnitStack_ExecuteHealingPathAndCheckArrival(unsigned int a1, char a2, DWORD a3, double a4)
{
  int v4; // ecx

  UnitStack_ExecuteQueuedPath(a1, 1, a2, a3, a4);
  return *(__int16 *)(gameData + UNIT_STACK_STRIDE * v4 + 147180) == -1;
}
// 4579DE: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457A10) --------------------------------------------------------
const void * UnitStack_MoveToBuildingAndCheckArrival(unsigned int a1, int a2, double a3)
{
  unsigned int v4; // edi
  DWORD v5; // ebp
  const void *result; // eax
  int v7; // [esp+8h] [ebp-18h]

  v4 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * a2 + BUILDING_TABLE_OFFSET);
  v5 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * a2 + 509675);
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * a1 + 147490)
    || (v7 = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 320), (int)abs32(v4 - (unsigned __int8)v7) >= 3)
    || (int)abs32(v5 - BYTE1(v7)) >= 3
    || __PAIR64__(v5, v4) == __PAIR64__(BYTE1(v7), (unsigned __int8)v7) )
  {
    result = (const void *)Building_GenerateApproachTrack(a1, a2, a2, a1, v5);
    if ( !result )
      return result;
    qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 316), result, 0x194u);
    j__nfree_();
  }
  UnitStack_ExecuteQueuedPath(a1, 1, a1, v5, a3);
  return (const void *)(*(__int16 *)(gameData + UNIT_STACK_STRIDE * a1 + 147180) == -1);
}
// 457A65: conditional instruction was optimized away because %var_20.4==0
// 5202E4: using guessed type int gameData;

//----- (00457BA0) --------------------------------------------------------
int  UnitStack_QueuePathNearBuilding(int a1, int a2, char a3, DWORD a4)
{
  int result; // eax
  int v5; // ecx

  result = Building_GenerateNearApproachTrack(a1, a2, a1, a3, a4);
  if ( result )
  {
    qmemcpy((void *)(UNIT_STACK_STRIDE * v5 + gameData + UNIT_STACK_TABLE_OFFSET + 316), (const void *)result, 0x194u);
    j__nfree_();
    return 1;
  }
  return result;
}
// 457BD7: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457C00) --------------------------------------------------------
int  Building_GetMaxEnemyStrengthUnderWalls(int a1)
{
  int v1; // eax
  int v2; // edx
  int v3; // ecx
  int v4; // edi
  int v5; // edx
  int j; // ecx
  int v7; // ebx
  int v9; // [esp+4h] [ebp-38h]
  int v10; // [esp+8h] [ebp-34h]
  int i; // [esp+Ch] [ebp-30h]
  int v12; // [esp+10h] [ebp-2Ch]
  int v13; // [esp+1Ch] [ebp-20h]
  int v14; // [esp+20h] [ebp-1Ch]

  v1 = BUILDING_RECORD_SIZE * a1;
  v14 = 0;
  v2 = *(unsigned __int8 *)(gameData + v1 + BUILDING_TABLE_OFFSET);
  v3 = *(unsigned __int8 *)(gameData + v1 + 509675);
  v12 = v1;
  v4 = v2 - 1;
  v13 = v3 + 2;
  v9 = v2 + 2;
  v10 = v3 - 1;
  for ( i = 200 * (v2 - 1); v4 <= v9; i += 200 )
  {
    v5 = v10;
    for ( j = 2 * v10; v5 <= v13; j += 2 )
    {
      if ( v4 >= 0
        && v4 < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
        && v5 >= 0
        && v5 < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
        && *(unsigned __int16 *)(j + gameData + i + 556374) <= 0x1F4u
        && (unsigned int)*(__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(j + gameData + i + 556374) + 6) <= 0x28 )
      {
        v7 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(j + gameData + i + 556374);
        if ( *(_BYTE *)(gameData + v7 + 147178) != *(_BYTE *)(gameData + v12 + 509676)
          && UnitStack_CalcArmyFactStrength(gameData + UNIT_STACK_TABLE_OFFSET + v7) > v14 )
        {
          v14 = UnitStack_CalcArmyFactStrength(v7 + gameData + UNIT_STACK_TABLE_OFFSET);
        }
      }
      ++v5;
    }
    ++v4;
  }
  return v14;
}
// 457CF5: simplified comparisons for 'ebx.4': <0 || >=29 became >=29u
// 457D5E: variable 'v5' is possibly undefined
// 457D5F: variable 'j' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457DA0) --------------------------------------------------------
int  Building_GetPlagueState(int a1)
{
  return *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * a1 + 510109) & 7;
}
// 5202E4: using guessed type int gameData;

//----- (00457DC0) --------------------------------------------------------
signed int  UnitStack_HasPlagueByIndex(int a1)
{
  return UnitStack_HasPlague(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00457E00) --------------------------------------------------------
BOOL  Unit_ExecuteQueuedPathAndCheckFinished(unsigned int a1, char a2, DWORD a3, double a4)
{
  int v4; // ecx

  UnitStack_ExecuteQueuedPath(a1, 1, a2, a3, a4);
  return *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v4 + 147490) == 0;
}
// 457E2E: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457E50) --------------------------------------------------------
int  Script_UnitAddToGroup(unsigned int a1, int a2, DWORD a3, double a4)
{
  return Unit_AddToGroup(a1, a2, 0, a3, a4);
}

//----- (00457E60) --------------------------------------------------------
BOOL  UnitStack_DetachWeakUnitsToAdjacentTile(int a1, int a2, int a3, double a4)
{
  int v4; // ecx
  __int16 *v5; // eax
  int v6; // esi
  int i; // edx
  int j; // eax
  int v10; // esi
  _DWORD v12[10]; // [esp+4h] [ebp-50h] BYREF
  int v13; // [esp+2Ch] [ebp-28h]
  int v14; // [esp+30h] [ebp-24h]
  int v15; // [esp+34h] [ebp-20h]
  __int16 *v16; // [esp+38h] [ebp-1Ch]

  v13 = a1;
  v4 = 0;
  v16 = (__int16 *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
  v5 = v16 + 3;
  v6 = 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( *v5 == -1 )
      break;
    if ( *((char *)v5 + 9) <= 10 )
    {
      ++v4;
      ++v6;
      v12[v4 - 1] = i;
    }
    v5 = (__int16 *)((char *)v5 + 31);
  }
  if ( !v6 || v6 == Unit_GetSquadCount((int)v16) )
    return 0;
  for ( j = v6; j < 10; v12[j - 1] = -1 )
  {
    ++j;
    ++v6;
  }
  v14 = 0;
  v15 = -1;
  do
  {
    v10 = -1;
    do
    {
      if ( v15 || v10 )
      {
        a3 = v15 + *v16;
        a2 = v10 + v16[1];
        if ( a3 >= 0
          && a3 < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
          && a2 >= 0
          && a2 < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Map_GetUnitTileMoveCostOrZero(*((unsigned __int8 *)v16 + 4), 0, v10 + v16[1], v15 + *v16) )
        {
          v14 = 1;
        }
      }
      ++v10;
    }
    while ( v10 <= 1 && !v14 );
    ++v15;
  }
  while ( v15 <= 1 && !v14 );
  return v14 && Unit_MoveSelectionFromGroupToTile(v13, v12, a2, a3, a4, 0);
}
// 457F19: conditional instruction was optimized away because %var_24.4==0
// 5202E4: using guessed type int gameData;

//----- (00457FE0) --------------------------------------------------------
BOOL  UnitStack_DetachUnitTypeToAdjacentTile(int a1, unit_type a2, int a3, int a4, double a5)
{
  int v5; // esi
  __int16 *v6; // edx
  int v7; // ecx
  int i; // eax
  int v9; // ebx
  int j; // eax
  int v12; // esi
  _DWORD v14[10]; // [esp+4h] [ebp-50h] BYREF
  int v15; // [esp+2Ch] [ebp-28h]
  int v16; // [esp+30h] [ebp-24h]
  int v17; // [esp+34h] [ebp-20h]
  int v18; // [esp+38h] [ebp-1Ch]
  __int16 *v19; // [esp+3Ch] [ebp-18h]

  v15 = a1;
  v16 = a2;
  v5 = 0;
  v19 = (__int16 *)(UNIT_STACK_STRIDE * a1 + gameData + UNIT_STACK_TABLE_OFFSET);
  v6 = v19 + 3;
  v7 = 0;
  for ( i = 0; i < 10; ++i )
  {
    v9 = *v6;
    if ( v9 == -1 )
      break;
    if ( v9 == v16 )
    {
      ++v7;
      ++v5;
      v14[v7 - 1] = i;
    }
    v6 = (__int16 *)((char *)v6 + 31);
  }
  if ( !v5 || v5 == Unit_GetSquadCount((int)v19) )
    return 0;
  for ( j = v5; j < 10; v14[j - 1] = -1 )
  {
    ++j;
    ++v5;
  }
  v17 = 0;
  v18 = -1;
  do
  {
    v12 = -1;
    do
    {
      if ( v18 || v12 )
      {
        a3 = v18 + *v19;
        a4 = v12 + v19[1];
        if ( a3 >= 0
          && a3 < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
          && a4 >= 0
          && a4 < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Map_GetUnitTileMoveCostOrZero(*((unsigned __int8 *)v19 + 4), 0, v12 + v19[1], v18 + *v19) )
        {
          v17 = 1;
        }
      }
      ++v12;
    }
    while ( v12 <= 1 && !v17 );
    ++v18;
  }
  while ( v18 <= 1 && !v17 );
  return v17 && Unit_MoveSelectionFromGroupToTile(v15, v14, a4, a3, a5, 0);
}
// 458094: conditional instruction was optimized away because %var_20.4==0
// 5202E4: using guessed type int gameData;

//----- (00458160) --------------------------------------------------------
signed int  UnitStack_HasUnitType(int a1, unit_type a2)
{
  int v3; // edx
  __int16 *i; // eax
  int v5; // ecx

  v3 = 0;
  for ( i = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 6); ; i = (__int16 *)((char *)i + 31) )
  {
    v5 = *i;
    if ( v5 == -1 )
      return 0;
    if ( v5 == a2 )
      break;
    if ( ++v3 >= 10 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (004581C0) --------------------------------------------------------
signed int  UnitStack_HasOnlyUnitType(int a1, unit_type a2)
{
  int v3; // edx
  __int16 *i; // eax
  int v5; // ecx

  v3 = 0;
  for ( i = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 6); ; i = (__int16 *)((char *)i + 31) )
  {
    v5 = *i;
    if ( v5 == -1 )
      return 1;
    if ( v5 != a2 )
      break;
    if ( ++v3 >= 10 )
      return 1;
  }
  return 0;
}
// 5202E4: using guessed type int gameData;

int Rules_HostArmyHasOnlyUnitType(int a1, double a2)
{
  unit_type type;
  int army_index;

  (void)a1;
  type = (unit_type)Rules_RtnLong(2, 0, a2);
  army_index = Rules_RtnLong(1, 0, a2);
  return UnitStack_HasOnlyUnitType(army_index, type);
}

//----- (00458220) --------------------------------------------------------
signed int  UnitStack_GetHealthPercentAggregate(int a1, int a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  __int16 *v6; // eax
  int v7; // ebx

  v3 = gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * a1 + 6;
  v4 = 1;
  v5 = *(char *)(v3 + 9);
  v6 = (__int16 *)(v3 + 31);
  while ( *v6 != -1 )
  {
    if ( a2 < 0 )
    {
      v7 = *((char *)v6 + 9);
      if ( v5 >= v7 )
        goto LABEL_11;
    }
    else
    {
      if ( a2 <= 0 )
      {
        v5 += *((char *)v6 + 9);
        goto LABEL_6;
      }
      v7 = *((char *)v6 + 9);
      if ( v5 <= v7 )
LABEL_11:
        v5 = v7;
    }
LABEL_6:
    ++v4;
    v6 = (__int16 *)((char *)v6 + 31);
    if ( v4 >= 10 )
      break;
  }
  if ( !a2 )
    v5 /= v4;
  return v5;
}
// 5202E4: using guessed type int gameData;

//----- (004582B0) --------------------------------------------------------
int  UnitStack_RegroupWithOtherStackByHealth(int a1, int a2, char a3, DWORD a4, double a5)
{
  int v5; // edx
  int v6; // ecx
  int v7; // ebp
  __int64 v8; // rax
  int result; // eax
  int v10; // ebp
  int v11; // ebx
  __int64 v12; // rax
  __int64 v13; // rax
  __int64 v14; // rax
  int v15; // ebp
  int v16; // edx
  _BYTE *v17; // ebx
  __int16 *v18; // edx
  __int16 *v19; // edx
  int v20; // ebp
  _BYTE *v21; // ebx
  int v22; // ebx
  _BYTE *v23; // ebp
  int v24; // ebx
  _WORD *v25; // edx
  signed int v26; // ebp
  _WORD *v27; // edx
  _BYTE *v28; // ebx
  int v29; // ebp
  _BYTE *v30; // ebx
  _BYTE *v31; // edx
  _BYTE v32[620]; // [esp+0h] [ebp-2CCh] BYREF
  _BYTE v33[28]; // [esp+26Ch] [ebp-60h] BYREF
  _BYTE v34[3]; // [esp+288h] [ebp-44h] BYREF
  int v35; // [esp+28Ch] [ebp-40h]
  int v36; // [esp+290h] [ebp-3Ch]
  signed int v37; // [esp+294h] [ebp-38h]
  int v38; // [esp+298h] [ebp-34h]
  int v39; // [esp+29Ch] [ebp-30h]
  int v40; // [esp+2A0h] [ebp-2Ch]
  int v41; // [esp+2A4h] [ebp-28h]
  int v42; // [esp+2A8h] [ebp-24h]
  int v43; // [esp+2ACh] [ebp-20h]
  int v44; // [esp+2B0h] [ebp-1Ch]
  int v45; // [esp+2B4h] [ebp-18h]

  v35 = a1;
  v36 = a2;
  Debug_Log(a1, a3, a4, (int)aPrzegrupujar_0);
  v7 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * v5 + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v36 + UNIT_STACK_TABLE_OFFSET);
  if ( (int)abs32(v7) > 1
    || (v8 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * v5 + 147176) - *(__int16 *)(UNIT_STACK_STRIDE * v36 + gameData + 147176),
        (int)((HIDWORD(v8) ^ v8) - HIDWORD(v8)) > 1) )
  {
    result = (int)Unit_MoveTrackNearTile(
                    v35,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * v36 + UNIT_STACK_TABLE_OFFSET),
                    v6,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * v36 + 147176),
                    v7);
    if ( !result )
      return result;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v35 + gameData + UNIT_STACK_TABLE_OFFSET + 316), (const void *)result, 0x194u);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(v35, 1, -43 * v35, v7, a5);
  }
  v10 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * v35 + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v36 + UNIT_STACK_TABLE_OFFSET);
  if ( (int)abs32(v10) > 1
    || (v13 = *(__int16 *)(UNIT_STACK_STRIDE * v35 + gameData + 147176) - *(__int16 *)(UNIT_STACK_STRIDE * v36 + gameData + 147176),
        (int)((HIDWORD(v13) ^ v13) - HIDWORD(v13)) > 1) )
  {
    result = (int)Unit_MoveTrackNearTile(
                    v36,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * v35 + UNIT_STACK_TABLE_OFFSET),
                    v6,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * v35 + 147176),
                    v10);
    if ( !result )
      return result;
    qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v36 + 316), (const void *)result, 0x194u);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(v36, 1, -111 * v36, v10, a5);
  }
  v11 = UNIT_STACK_STRIDE * v35;
  v12 = *(__int16 *)(gameData + UNIT_STACK_STRIDE * v35 + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v36 + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(v12) ^ v12) - HIDWORD(v12)) > 1 )
    return 0;
  v14 = *(__int16 *)(gameData + v11 + 147176) - *(__int16 *)(UNIT_STACK_STRIDE * v36 + gameData + 147176);
  if ( (int)((HIDWORD(v14) ^ v14) - HIDWORD(v14)) > 1 )
    return 0;
  v15 = 0;
  v44 = 0;
  v16 = gameData + UNIT_STACK_TABLE_OFFSET + v11;
  v17 = v32;
  v18 = (__int16 *)(v16 + 6);
  do
  {
    if ( *v18 == -1 )
      break;
    qmemcpy(v17, v18, 0x1Cu);
    qmemcpy(v17 + 28, v18 + 14, 3u);
    ++v15;
    v18 = (__int16 *)((char *)v18 + 31);
    v17 += 31;
    ++v44;
  }
  while ( v15 < 10 );
  v19 = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v36 + 6);
  v20 = 0;
  v21 = &v32[31 * v44];
  do
  {
    if ( *v19 == -1 )
      break;
    qmemcpy(v21, v19, 0x1Cu);
    qmemcpy(v21 + 28, v19 + 14, 3u);
    ++v20;
    v19 = (__int16 *)((char *)v19 + 31);
    v21 += 31;
    ++v44;
  }
  while ( v20 < 10 );
  v43 = 0;
  if ( v44 > 1 )
  {
    v41 = 0;
    v39 = 31;
    v38 = v44 - 1;
    do
    {
      if ( v43 )
        break;
      v43 = 1;
      v29 = 1;
      if ( v44 > 1 )
      {
        v42 = v41;
        v45 = v39;
        do
        {
          if ( v32[31 * v42 + 9] > v32[v45 + 9] )
          {
            v43 = 0;
            v30 = &v32[31 * v42];
            qmemcpy(v33, v30, sizeof(v33));
            qmemcpy(v34, v30 + 28, sizeof(v34));
            v31 = &v32[v45];
            qmemcpy(v30, &v32[v45], 0x1Cu);
            qmemcpy(v30 + 28, v31 + 28, 3u);
            qmemcpy(v31, v33, 0x1Cu);
            qmemcpy(v31 + 28, v34, 3u);
          }
          ++v29;
        }
        while ( v29 < v44 );
      }
      v39 += 31;
      ++v41;
    }
    while ( v41 < v38 );
  }
  v40 = 0;
  if ( v44 > 0 )
  {
    v22 = 0;
    do
    {
      if ( (char)v32[v22 + 9] >= 8 )
        ++v40;
      v22 += 31;
    }
    while ( v22 < 31 * v44 );
  }
  if ( v40 > 10 )
    v40 = 10;
  if ( v44 - 10 > v40 )
    v40 = v44 - 10;
  v23 = v32;
  v24 = 0;
  v25 = (_WORD *)(UNIT_STACK_STRIDE * v35 + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  do
  {
    if ( v24 >= v40 )
    {
      *v25 = -1;
    }
    else
    {
      qmemcpy(v25, v23, 0x1Cu);
      qmemcpy(v25 + 14, v23 + 28, 3u);
    }
    v23 += 31;
    ++v24;
    v25 = (_WORD *)((char *)v25 + 31);
  }
  while ( v24 < 10 );
  v37 = v44 - v40;
  v26 = 0;
  v27 = (_WORD *)(UNIT_STACK_STRIDE * v36 + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  v28 = &v32[31 * v40];
  do
  {
    if ( v26 >= v37 )
    {
      *v27 = -1;
    }
    else
    {
      qmemcpy(v27, v28, 0x1Cu);
      qmemcpy(v27 + 14, v28 + 28, 3u);
    }
    v28 += 31;
    ++v26;
    v27 = (_WORD *)((char *)v27 + 31);
  }
  while ( v26 < 10 );
  if ( !v40 )
    UnitStack_KillByIndex(v35, (char)v28, v26, a5);
  if ( v40 == v44 )
    UnitStack_KillByIndex(v36, (char)v28, v26, a5);
  return 1;
}
// 4582F8: variable 'v5' is possibly undefined
// 45839D: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004589C0) --------------------------------------------------------
signed int  UnitStack_RegroupWithBuildingGarrisonByHealth(int a1, int a2, char a3, DWORD a4, double a5)
{
  int v5; // edi
  int v6; // ecx
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rax
  int v11; // ebx
  int v12; // ebp
  const void *v13; // eax
  int v14; // edx
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  int v20; // ebp
  _BYTE *v21; // ebx
  __int16 *v22; // edx
  int v23; // ebp
  __int16 *v24; // edx
  _BYTE *v25; // ebx
  int v26; // edx
  _BYTE *v27; // ebp
  int v28; // ebx
  _WORD *v29; // edx
  int v30; // ebx
  _WORD *v31; // edx
  _BYTE *v32; // ebp
  __int64 v34; // rax
  __int64 v35; // rax
  __int64 v36; // rax
  __int64 v37; // rax
  __int64 v38; // rax
  __int64 v39; // rax
  int v40; // ebp
  _BYTE *v41; // edx
  _BYTE *v42; // ebx
  _BYTE v43[684]; // [esp+0h] [ebp-30Ch] BYREF
  _BYTE v44[28]; // [esp+2ACh] [ebp-60h] BYREF
  _BYTE v45[3]; // [esp+2C8h] [ebp-44h] BYREF
  int v46; // [esp+2CCh] [ebp-40h]
  int v47; // [esp+2D0h] [ebp-3Ch]
  int v48; // [esp+2D4h] [ebp-38h]
  int v49; // [esp+2D8h] [ebp-34h]
  int v50; // [esp+2DCh] [ebp-30h]
  int v51; // [esp+2E0h] [ebp-2Ch]
  int v52; // [esp+2E4h] [ebp-28h]
  int v53; // [esp+2E8h] [ebp-24h]
  int v54; // [esp+2ECh] [ebp-20h]
  int v55; // [esp+2F0h] [ebp-1Ch]
  int v56; // [esp+2F4h] [ebp-18h]

  v47 = a1;
  v46 = a2;
  v5 = BUILDING_RECORD_SIZE * a2;
  Debug_Log(a1, a3, a4, (int)aPrzegrupujza_0);
  v7 = *(unsigned __int8 *)(gameData + v5 + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v6 + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(v7) ^ v7) - HIDWORD(v7)) > 1
    || (v8 = *(unsigned __int8 *)(v5 + gameData + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * v6 + gameData + 147176),
        (int)((HIDWORD(v8) ^ v8) - HIDWORD(v8)) > 1) )
  {
    v9 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( (int)((HIDWORD(v9) ^ v9) - HIDWORD(v9)) > 1
      || (v34 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + 147176),
          (int)((HIDWORD(v34) ^ v34) - HIDWORD(v34)) > 1) )
    {
      v10 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v47 + UNIT_STACK_TABLE_OFFSET);
      if ( (int)((HIDWORD(v10) ^ v10) - HIDWORD(v10)) > 1
        || (v35 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * v46 + gameData + 509675) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + 147176),
            (int)((HIDWORD(v35) ^ v35) - HIDWORD(v35)) > 1) )
      {
        v11 = UNIT_STACK_STRIDE * v47;
        v12 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v47 + UNIT_STACK_TABLE_OFFSET);
        if ( (int)abs32(v12) > 1
          || (v11 = *(__int16 *)(v11 + gameData + 147176),
              v36 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * v46 + gameData + 509675) + 1 - v11,
              (int)((HIDWORD(v36) ^ v36) - HIDWORD(v36)) > 1) )
        {
          v13 = (const void *)Building_GenerateNearApproachTrack(v47, v46, v6, v11, v12);
          if ( !v13 )
            return 0;
          qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v47 + 316), v13, 0x194u);
          j__nfree_();
          UnitStack_ExecuteQueuedPath(v47, v14, -111 * v47, v12, a5);
        }
      }
    }
  }
  v15 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v47 + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(v15) ^ v15) - HIDWORD(v15)) > 1
    || (v37 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * v46 + gameData + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + 147176),
        (int)((HIDWORD(v37) ^ v37) - HIDWORD(v37)) > 1) )
  {
    v16 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( (int)((HIDWORD(v16) ^ v16) - HIDWORD(v16)) > 1
      || (v38 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * v46 + gameData + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + 147176),
          (int)((HIDWORD(v38) ^ v38) - HIDWORD(v38)) > 1) )
    {
      v17 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v47 + UNIT_STACK_TABLE_OFFSET);
      if ( (int)((HIDWORD(v17) ^ v17) - HIDWORD(v17)) > 1
        || (v39 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + 509675) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + 147176),
            (int)((HIDWORD(v39) ^ v39) - HIDWORD(v39)) > 1) )
      {
        v18 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v46 + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v47 + UNIT_STACK_TABLE_OFFSET);
        if ( (int)((HIDWORD(v18) ^ v18) - HIDWORD(v18)) > 1 )
          return 0;
        v19 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * v46 + gameData + 509675) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * v47 + gameData + 147176);
        if ( (int)((HIDWORD(v19) ^ v19) - HIDWORD(v19)) > 1 )
          return 0;
      }
    }
  }
  v55 = 0;
  v20 = 0;
  v21 = v43;
  v22 = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v47 + 6);
  do
  {
    if ( *v22 == -1 )
      break;
    qmemcpy(v21, v22, 0x1Cu);
    qmemcpy(v21 + 28, v22 + 14, 3u);
    ++v20;
    v22 = (__int16 *)((char *)v22 + 31);
    v21 += 31;
    ++v55;
  }
  while ( v20 < 10 );
  v23 = 0;
  v24 = (__int16 *)(UNIT_RECORD(v46) + 18);
  v25 = &v43[31 * v55];
  do
  {
    if ( *v24 == -1 )
      break;
    qmemcpy(v25, v24, 0x1Cu);
    qmemcpy(v25 + 28, v24 + 14, 3u);
    ++v23;
    v24 = (__int16 *)((char *)v24 + 31);
    v25 += 31;
    ++v55;
  }
  while ( v23 < 12 );
  v50 = 0;
  if ( v55 > 1 )
  {
    v53 = 0;
    v51 = 31;
    v49 = v55 - 1;
    do
    {
      if ( v50 )
        break;
      v40 = 1;
      v50 = 1;
      if ( v55 > 1 )
      {
        v54 = v53;
        v56 = v51;
        do
        {
          if ( v43[31 * v54 + 9] > v43[v56 + 9] )
          {
            v50 = 0;
            v41 = &v43[31 * v54];
            qmemcpy(v44, v41, sizeof(v44));
            qmemcpy(v45, v41 + 28, sizeof(v45));
            v42 = &v43[v56];
            qmemcpy(v41, &v43[v56], 0x1Cu);
            qmemcpy(v41 + 28, v42 + 28, 3u);
            qmemcpy(v42, v44, 0x1Cu);
            qmemcpy(v42 + 28, v45, 3u);
          }
          ++v40;
        }
        while ( v40 < v55 );
      }
      v51 += 31;
      ++v53;
    }
    while ( v53 < v49 );
  }
  v26 = 0;
  v52 = 0;
  if ( v55 > 0 )
  {
    do
    {
      if ( (char)v43[v26 + 9] >= 8 )
        ++v52;
      v26 += 31;
    }
    while ( v26 < 31 * v55 );
  }
  if ( v52 > 10 )
    v52 = 10;
  if ( v55 - 12 > v52 )
    v52 = v55 - 12;
  v27 = v43;
  v28 = 0;
  v29 = (_WORD *)(UNIT_STACK_STRIDE * v47 + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  do
  {
    if ( v28 >= v52 )
    {
      *v29 = -1;
    }
    else
    {
      qmemcpy(v29, v27, 0x1Cu);
      qmemcpy(v29 + 14, v27 + 28, 3u);
    }
    v27 += 31;
    ++v28;
    v29 = (_WORD *)((char *)v29 + 31);
  }
  while ( v28 < 10 );
  v30 = 0;
  v48 = v55 - v52;
  v31 = (_WORD *)(UNIT_RECORD(v46) + 18);
  v32 = &v43[31 * v52];
  do
  {
    if ( v30 >= v48 )
    {
      *v31 = -1;
    }
    else
    {
      qmemcpy(v31, v32, 0x1Cu);
      qmemcpy(v31 + 14, v32 + 28, 3u);
    }
    v32 += 31;
    ++v30;
    v31 = (_WORD *)((char *)v31 + 31);
  }
  while ( v30 < 12 );
  if ( !v52 )
    UnitStack_KillByIndex(v47, v30, (DWORD)v32, a5);
  return 1;
}
// 458A0D: variable 'v6' is possibly undefined
// 458BBF: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00459230) --------------------------------------------------------
double  AI_CalcStrategicPriorityScore(int a1, DWORD a2, int a3, int a4, int a5)
{
  int v7; // ecx
  int v8; // ecx
  _BYTE v10[80]; // [esp+0h] [ebp-70h] BYREF
  int v11; // [esp+50h] [ebp-20h] BYREF
  float v12; // [esp+54h] [ebp-1Ch] BYREF
  int v13; // [esp+58h] [ebp-18h]
  float v14; // [esp+5Ch] [ebp-14h]
  signed int v15; // [esp+60h] [ebp-10h]

  v13 = a3;
  v14 = -1.0;
  v7 = IO_FOpen(aStrategprior, (unsigned __int8 *)aR, a3, a2);
  if ( v7 )
  {
    while ( fgets_(v10, 80, v7) )
    {
      sscanf_(v10, "%d %f", &v11, &v12);
      if ( a1 == v11 )
        v14 = v12;
    }
  }
  fclose_(v7);
  v15 = Math_CeilSqrt((v13 - a2) * (v13 - a2) + (a5 - a4) * (a5 - a4));
  return v14 / (double)v15;
}
// 459267: variable 'v7' is possibly undefined
// 4592B5: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4841D3: using guessed type int __fastcall fgets_(_DWORD, _DWORD);
// 48429C: using guessed type _DWORD sscanf_(_DWORD, _DWORD, ...);

//----- (004592E0) --------------------------------------------------------
void  AI_EvaluateStrategicTargetAtTile(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int *a7,
        int *a8,
        float *a9)
{
  int v11; // ebp
  int v12; // edi
  unsigned int v13; // eax
  int v14; // edx
  double v15; // st7
  int v16; // [esp+0h] [ebp-20h]
  float v18; // [esp+8h] [ebp-18h]

  v11 = -1;
  if ( a4 >= 0 && a4 < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) && a3 >= 0 && a3 < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
  {
    if ( *(unsigned __int16 *)(TILE_INDEX(a4, a3)) > 0x1F4u
      || (unsigned int)*(__int16 *)(gameData
                                  + UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(a4, a3))
                                  + 147180) > 0x28 )
    {
      v13 = *(unsigned __int16 *)(TILE_INDEX(a4, a3)) - 0x8000;
      if ( v13 > 0x64
        || (v14 = UNIT_RECORD(v13), (unsigned int)*(char *)(v14 + 4) >= 4)
        || *(__int16 *)(v14 + 16) == -1 )
      {
        if ( MapTile_HasHiddenTreasure(a4, a3) )
        {
          v12 = 3;
        }
        else
        {
          if ( !MapTile_GetReligiousSiteCategory(a4, a3) )
            return;
          v12 = 4;
        }
      }
      else
      {
        v12 = 1;
        v11 = *(unsigned __int16 *)(TILE_INDEX(a4, a3)) - 0x8000;
      }
    }
    else
    {
      v12 = 2;
      v11 = *(unsigned __int16 *)(TILE_INDEX(a4, a3));
    }
    if ( (a1 == -1 || v12 == a1)
      && (a2 == -1
       || (v12 != 1 || *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * v11 + 509676) == a2)
       && (v12 != 2 || *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * v11 + 147178) == a2)) )
    {
      AI_CalcStrategicPriorityScore(v12, a4, a5, a3, a6);
      v15 = (double)(int)_CHP(v16, a1);
      if ( v15 > *a9 )
      {
        *a7 = v12;
        *a8 = v11;
        v18 = v15;
        *a9 = v18;
      }
    }
  }
}
// 459389: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 459481: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 45949C: simplified comparisons for 'eax.4': <0 || >=4 became >=4u
// 459529: variable 'v16' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00459570) --------------------------------------------------------
int  AI_FindBestStrategicTargetNearTile(int a1, int a2, int a3, int a4, signed int a5)
{
  int v7; // esi
  int v8; // edi
  int v9; // ebx
  int v10; // ecx
  int v11; // [esp+0h] [ebp-48h] BYREF
  int v12; // [esp+4h] [ebp-44h] BYREF
  int v13; // [esp+8h] [ebp-40h] BYREF
  int v14; // [esp+Ch] [ebp-3Ch]
  int v15; // [esp+10h] [ebp-38h]
  int v16; // [esp+14h] [ebp-34h]
  int v17; // [esp+18h] [ebp-30h]
  signed int v18; // [esp+1Ch] [ebp-2Ch]
  int i; // [esp+20h] [ebp-28h]
  int v20; // [esp+24h] [ebp-24h]
  int v21; // [esp+28h] [ebp-20h]
  int v22; // [esp+2Ch] [ebp-1Ch]
  int v23; // [esp+30h] [ebp-18h]
  int v24; // [esp+34h] [ebp-14h]
  int v25; // [esp+38h] [ebp-10h]

  v23 = a2;
  v25 = a4;
  v24 = a3;
  v11 = -1;
  v12 = -1;
  v13 = -1082130432;
  v18 = 1;
  if ( a5 >= 1 )
  {
    v17 = v25 + 1;
    v16 = a3 - 1;
    v14 = v25 - 1;
    v15 = a3 + 1;
    do
    {
      v7 = v25 - v18;
      v8 = v18 + v24;
      for ( i = v17; v7 < i; ++v7 )
        AI_EvaluateStrategicTargetAtTile(a1, v23, v8, v7, v25, v24, &v11, &v12, (float *)&v13);
      v21 = v16;
      while ( v8 > v21 )
        AI_EvaluateStrategicTargetAtTile(a1, v23, v8--, v7, v25, v24, &v11, &v12, (float *)&v13);
      v20 = v14;
      while ( v7 > v20 )
      {
        v9 = v7--;
        AI_EvaluateStrategicTargetAtTile(a1, v23, v8, v9, v25, v24, &v11, &v12, (float *)&v13);
      }
      v22 = v15;
      while ( v8 < v22 )
      {
        v10 = v8++;
        AI_EvaluateStrategicTargetAtTile(a1, v23, v10, v7, v25, v24, &v11, &v12, (float *)&v13);
      }
      ++v17;
      --v16;
      --v14;
      ++v15;
      ++v18;
    }
    while ( v18 <= a5 );
  }
  if ( v11 == -1 )
    return -1;
  if ( v11 == 3 || v11 == 4 )
    return 100 * v11;
  return v12 + 100 * v11;
}

//----- (00459760) --------------------------------------------------------
signed int  createUnit(double a1, int a2, int a3, int a4, unit_type a5, unit_type a6, ...)
{
  va_list args;
  char v7; // bl
  int v8; // ecx
  unit_type next_unit_type; // eax
  DWORD v10; // ebp
  int slot_offset; // ecx
  int tile_offset; // [esp+0h] [ebp-1Ch]

  va_start(args, a6);
  Unit_Create(a5, a4, a2, 0, a1, a3);
  v7 = a4;
  slot_offset = 31;
  next_unit_type = a6;
  v10 = 200 * a2;
  tile_offset = 2 * a3;
  while ( next_unit_type != -1 )
  {
    v8 = *(unsigned __int16 *)(tile_offset + gameData + v10 + 556374);
    UnitSlot_InitFromType(slot_offset + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v8 + 6, next_unit_type, a4);
    next_unit_type = va_arg(args, int);
    slot_offset += 31;
  }
  va_end(args);
  return Rules_SyncArmyFactStrength(
           gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(tile_offset + gameData + v10 + 556374),
           145 * *(unsigned __int16 *)(tile_offset + gameData + v10 + 556374),
           gameData + UNIT_STACK_TABLE_OFFSET,
           v7,
           v10,
           a1);
}
// 5202E4: using guessed type int gameData;

//----- (00459860) --------------------------------------------------------
int  createCastle(
        double st7_0,
        int a2,
        int a3,
        int a4,
        int a5,
        char *a6,
        unit_type a7,
        unit_type a8,
        ...)
{
  va_list args;
  int v9; // eax
  int v10; // ecx
  unit_type next_unit_type; // eax
  int unit_index; // eax
  int tile_offset; // [esp+0h] [ebp-20h]
  DWORD v15; // [esp+4h] [ebp-1Ch]

  va_start(args, a8);
  Diagnostics_TraceBootstrapEvent("createCastle-unit-create");
  Unit_Create(a7, a4, a2, 0, a3);
  Diagnostics_TraceBootstrapEvent("createCastle-fill-slots");
  v15 = 200 * a2;
  next_unit_type = a8;
  v10 = 31;
  tile_offset = 2 * a3;
  while ( next_unit_type != -1 )
  {
    v9 = *(unsigned __int16 *)(tile_offset + gameData + v15 + 556374);
    UnitSlot_InitFromType(v10 + UNIT_STACK_STRIDE * v9 + gameData + UNIT_STACK_TABLE_OFFSET + 6, next_unit_type, a4);
    next_unit_type = va_arg(args, int);
    v10 += 31;
  }
  va_end(args);
  Rules_SyncArmyFactStrength(
    (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(tile_offset + gameData + v15 + 556374)),
    145 * *(unsigned __int16 *)(tile_offset + gameData + v15 + 556374),
    gameData + UNIT_STACK_TABLE_OFFSET,
    tile_offset,
    v15,
    st7_0);
  Diagnostics_TraceBootstrapEvent("createCastle-building-new");
  Building_New(a5, *(unsigned __int16 *)(tile_offset + v15 + gameData + 556374), st7_0, a6, 1);
  Diagnostics_TraceBootstrapEvent("createCastle-post-building-new");
  unit_index = *(unsigned __int16 *)(tile_offset + v15 + gameData + 556374) - 0x8000;
  *(_WORD *)(BUILDING_RECORD_SIZE * unit_index + gameData + 509690) = 0;
  Diagnostics_TraceBootstrapEvent("createCastle-update-per-turn");
  Unit_UpdatePerTurn(BUILDING_RECORD_SIZE * unit_index + gameData + BUILDING_TABLE_OFFSET, 0);
  Diagnostics_TraceBootstrapEvent("createCastle-log-facts");
  Building_LogBuiltCastleFacts(
    (unsigned __int8 *)(BUILDING_RECORD_SIZE * unit_index + gameData + BUILDING_TABLE_OFFSET));
  Diagnostics_TraceBootstrapEvent("createCastle-done");
  return unit_index;
}
// 5202E4: using guessed type int gameData;

//----- (00459ED0) --------------------------------------------------------
int  WorldMap_DrawMission01ShrineMarker(int result, int a2, int a3, int a4)
{
  int v6; // eax
  int SpriteForChar; // eax
  int v11; // [esp-14h] [ebp-18h]

  if ( result == 16 && a2 == 11 )
  {
    v6 = Time_Now(a3, 11);
    v11 = ((50 * Math_SinDegreesQ16(2 * v6 - 90)) >> 16) + 50;
    SpriteForChar = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 730);
    return Sprite_DrawSimpleIgnoringRect(SpriteForChar, a4, a3, a3, a4 + 63, a3 + 63, v11, 0, 0, 0, 1u);
  }
  return result;
}
// 5202C0: using guessed type int dword_5202C0;

//----- (0045B3C0) --------------------------------------------------------
int  Mission05_MarkFailureOnFriendlyAttack(int result, int target_owner_index)
{
  if ( g_LanguageIndex && !result && (target_owner_index == 1 || target_owner_index == 2) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "mission05_failure_friendly_attack",
      g_SelectedUnitIndex,
      result,
      target_owner_index,
      GAME_TURN_COUNTER);
    result = gameData;
    MISSION_FAILURE_FLAG = 1;
  }
  return result;
}
// 511130: using guessed type char g_LanguageIndex;
// 5202E4: using guessed type int gameData;

//----- (0045C000) --------------------------------------------------------
int  WorldMap_DrawMission07TreasureMarker(int result, int a2)
{
  int v2; // esi

  v2 = result;
  if ( result == 55 && a2 == 45 && (result = MapTile_HasHiddenTreasure(55, 45)) != 0
    || v2 == 50 && a2 == 27 && (result = MapTile_HasHiddenTreasure(50, 27)) != 0
    || v2 == 35 && a2 == 63 && (result = MapTile_HasHiddenTreasure(35, 63)) != 0 )
  {
    DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 962);
    return (*(int (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
             -1,
             -1,
             -1,
             -1,
             1,
             0,
             0);
  }
  else if ( v2 == 14 && a2 == 68 )
  {
    result = MapTile_HasHiddenTreasure(14, 68);
    if ( result )
    {
      DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 961);
      return (*(int (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
               -1,
               -1,
               -1,
               -1,
               1,
               0,
               0);
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202C0: using guessed type int dword_5202C0;

//----- (0045D430) --------------------------------------------------------
int  WorldMap_DrawMission11ShrineMarker(int result, int a2, int a3, int a4)
{
  int v6; // eax
  int SpriteForChar; // eax
  int v11; // [esp-Ch] [ebp-10h]

  if ( result == 2 && a2 == 44 )
  {
    v6 = Time_Now(a3, 44);
    v11 = ((50 * Math_SinDegreesQ16(2 * v6 - 90)) >> 16) + 50;
    SpriteForChar = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 738);
    return Sprite_DrawSimpleIgnoringRect(SpriteForChar, a4, a3, a3, a4 + 63, a3 + 63, 0, 0, v11, 0, 1u);
  }
  return result;
}
// 5202C0: using guessed type int dword_5202C0;

//----- (0045E630) --------------------------------------------------------
int  Mission_MarkObjective15CompleteOnAttack(int result, int a2)
{
  if ( result == 1 && (a2 == 2 || a2 == 3) )
  {
    result = gameData;
    MISSION_FAILURE_FLAG = 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0045F190) --------------------------------------------------------
int  WorldMap_DrawMission17TreasureMarker(int result, int a2)
{
  int v2; // esi

  v2 = result;
  if ( result == 50 && a2 == 34 && (result = MapTile_HasHiddenTreasure(50, 34)) != 0
    || v2 == 51 && a2 == 73 && (result = MapTile_HasHiddenTreasure(51, 73)) != 0
    || v2 == 77 && a2 == 34 && (result = MapTile_HasHiddenTreasure(77, 34)) != 0
    || v2 == 24 && a2 == 49 && (result = MapTile_HasHiddenTreasure(24, 49)) != 0 )
  {
    DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 962);
    return (*(int (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
             -1,
             -1,
             -1,
             -1,
             1,
             0,
             0);
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202C0: using guessed type int dword_5202C0;

static void Mission_TraceObjectiveBlocked(int mission_index, int detail_a, int detail_b, int detail_c)
{
  static int last_mission_index = -1;
  static int last_turn_counter = -1;
  static int last_detail_a = 0;
  static int last_detail_b = 0;
  static int last_detail_c = 0;

  if ( last_mission_index == mission_index
    && last_turn_counter == GAME_TURN_COUNTER
    && last_detail_a == detail_a
    && last_detail_b == detail_b
    && last_detail_c == detail_c )
  {
    return;
  }
  last_mission_index = mission_index;
  last_turn_counter = GAME_TURN_COUNTER;
  last_detail_a = detail_a;
  last_detail_b = detail_b;
  last_detail_c = detail_c;
  Diagnostics_TraceWorldMapActionEvent("mission_objective_blocked", mission_index, detail_a, detail_b, detail_c);
}

//----- (00460270) --------------------------------------------------------
BOOL  Mission_CheckObjectiveComplete(DWORD a1, double a2)
{
  static int mission0_last_blocker_index = -1;
  static int mission0_last_blocker_turn = -1;
  int v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // edx
  int v10; // edx
  BOOL v11; // eax
  BOOL v12; // edi
  int v13; // ecx
  int v14; // esi
  int v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  BOOL v25; // eax
  int v26; // ecx
  int v27; // esi
  int v28; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int v32; // ecx
  int i; // eax
  int v34; // edx
  int v35; // eax
  BOOL result; // eax

  if ( g_CheatForceWinMissionFlag )
  {
    result = 1;
    g_CheatForceWinMissionFlag = 0;
    return result;
  }
  switch ( ACTIVE_MISSION_INDEX )
  {
    case 0:
      v2 = 0;
LABEL_6:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v2 + 147180) <= 0x28
        && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v2 + 147178) == 1 )
      {
        if ( mission0_last_blocker_index != v2 || mission0_last_blocker_turn != GAME_TURN_COUNTER )
        {
          mission0_last_blocker_index = v2;
          mission0_last_blocker_turn = GAME_TURN_COUNTER;
          Diagnostics_TraceWorldMapActionEvent(
            "mission_objective_blocked",
            v2,
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * v2 + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * v2 + 147176),
            Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v2));
        }
        return 0;
      }
      while ( ++v2 < 500 )
      {
        if ( v2 >= 0 )
          goto LABEL_6;
      }
      return 1;
    case 1:
      if ( MapTile_GetReligiousSiteCategory(16, 11) == RELIGIOUS_SITE_CATEGORY_EMPTY_SHRINE )
        return 1;
      Mission_TraceObjectiveBlocked(1, 16, 11, MapTile_GetReligiousSiteCategory(16, 11));
      return 0;
    case 2:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 564710) - 0x8000) + gameData + 509676) == 0 )
        return 1;
      Mission_TraceObjectiveBlocked(
        2,
        41,
        68,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 564710) - 0x8000) + gameData + 509676));
      return 0;
    case 3:
    case 0xD:
      if ( *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) > 0xAu )
        return 1;
      Mission_TraceObjectiveBlocked(ACTIVE_MISSION_INDEX, *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET), 10, 0);
      return 0;
    case 4:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 567712) - 0x8000) + gameData + 509676) == 0 )
        return 1;
      Mission_TraceObjectiveBlocked(
        4,
        56,
        69,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 567712) - 0x8000) + gameData + 509676));
      return 0;
    case 5:
      v3 = (unsigned __int8)g_LanguageIndex;
      if ( g_LanguageIndex )
      {
        v8 = 0;
LABEL_35:
        v9 = UNIT_RECORD(v8);
        if ( (unsigned int)*(char *)(v9 + 4) >= 4
          || *(__int16 *)(v9 + 16) == -1
          || *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * v8 + 509676) != 3 )
        {
          while ( ++v8 < 100 )
          {
            if ( v8 >= 0 )
              goto LABEL_35;
          }
          v10 = 0;
LABEL_42:
          if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v10 + 147180) > 0x28
            || *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v10 + 147178) != 3 )
          {
            while ( ++v10 < 500 )
            {
              if ( v10 >= 0 )
                goto LABEL_42;
            }
            return 1;
          }
          Mission_TraceObjectiveBlocked(5, v10, *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v10 + 147178), Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v10));
          return 0;
        }
        Mission_TraceObjectiveBlocked(5, v8, *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * v8 + 509676), *(__int16 *)(v9 + 16));
        return 0;
      }
LABEL_18:
      v4 = UNIT_RECORD(v3);
      if ( (unsigned int)*(char *)(v4 + 4) < 4 && *(__int16 *)(v4 + 16) != -1 )
      {
        v5 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * v3 + gameData + 509676);
        if ( v5 == 1 || v5 == 2 )
        {
          Mission_TraceObjectiveBlocked(5, v3, v5, *(__int16 *)(v4 + 16));
          return 0;
        }
      }
      while ( ++v3 < 100 )
      {
        if ( v3 >= 0 )
          goto LABEL_18;
      }
      v6 = 0;
LABEL_27:
      if ( (unsigned int)*(__int16 *)(UNIT_STACK_STRIDE * v6 + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28 )
      {
        v7 = *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * v6 + 147178);
        if ( v7 == 1 || v7 == 2 )
        {
          Mission_TraceObjectiveBlocked(5, v6, v7, Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v6));
          return 0;
        }
      }
      while ( ++v6 < 500 )
      {
        if ( v6 >= 0 )
          goto LABEL_27;
      }
      return 1;
    case 6:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574456) - 0x8000) + gameData + 509676) == 0 )
        return 1;
      Mission_TraceObjectiveBlocked(
        6,
        90,
        41,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574456) - 0x8000) + gameData + 509676));
      return 0;
    case 7:
      v11 = !MapTile_HasHiddenTreasure(55, 45) && !MapTile_HasHiddenTreasure(50, 27) && !MapTile_HasHiddenTreasure(35, 63) && !MapTile_HasHiddenTreasure(14, 68);
      v12 = v11;
      if ( !v11 )
      {
        Mission_TraceObjectiveBlocked(
          7,
          55,
          45,
          (MapTile_HasHiddenTreasure(55, 45) ? 1 : 0)
            | (MapTile_HasHiddenTreasure(50, 27) ? 2 : 0)
            | (MapTile_HasHiddenTreasure(35, 63) ? 4 : 0)
            | (MapTile_HasHiddenTreasure(14, 68) ? 8 : 0));
        return v12;
      }
      v13 = 0;
      while ( 1 )
      {
        if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v13 + 147180) <= 0x28 )
        {
          v14 = UNIT_STACK_STRIDE * v13;
          v15 = gameData + UNIT_STACK_STRIDE * v13;
          if ( *(_BYTE *)(v15 + 147178) )
          {
            if ( Map_IsTileVisibleToPlayer(*(__int16 *)(v15 + 147174), *(__int16 *)(v15 + 147176), 0) )
            {
              Camera_CenterOnUnit(v13);
              Audio_PlayArtifactSound(0);
              UI_StartTileBlinkFlash(*(__int16 *)(v14 + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(v14 + gameData + 147176), v16);
              Unit_Kill(v14 + gameData + UNIT_STACK_TABLE_OFFSET, 0, a1, a2);
              Timer_BusyWaitWithCallback(100, v17, v18);
            }
          }
        }
        do
        {
          if ( ++v13 >= 500 )
            return v12;
        }
        while ( v13 < 0 );
      }
    case 8:
      v19 = 0;
      while ( *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 562420) - 0x8000) + gameData + v19 + 509692) == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE )
      {
        v19 += 31;
        if ( v19 >= 372 )
          return 1;
      }
      Mission_TraceObjectiveBlocked(8, 30, 23, v19 / 31);
      return 0;
    case 9:
      v20 = 1423;
      while ( !*(_DWORD *)(gameData + v20 + PLAYER_RUNTIME_STATE_OFFSET) )
      {
        v20 += PLAYER_DATA_STRIDE;
        if ( v20 >= 7115 )
          return 1;
      }
      Mission_TraceObjectiveBlocked(9, v20 / PLAYER_DATA_STRIDE, *(_DWORD *)(gameData + v20 + PLAYER_RUNTIME_STATE_OFFSET), 0);
      return 0;
    case 0xA:
      v21 = 0;
LABEL_75:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v21 + 147180) <= 0x28
        && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v21 + 147178) == 2 )
      {
        Mission_TraceObjectiveBlocked(
          10,
          v21,
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * v21 + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * v21 + 147176));
        return 0;
      }
      while ( ++v21 < 500 )
      {
        if ( v21 >= 0 )
          goto LABEL_75;
      }
      return 1;
    case 0xB:
      if ( MapTile_GetReligiousSiteCategory(2, 44) == RELIGIOUS_SITE_CATEGORY_EMPTY_CULT_PLACE )
        return 1;
      Mission_TraceObjectiveBlocked(11, 2, 44, MapTile_GetReligiousSiteCategory(2, 44));
      return 0;
    case 0xC:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 568202) - 0x8000) + gameData + 509676) == 1 )
        return 1;
      Mission_TraceObjectiveBlocked(
        12,
        59,
        14,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 568202) - 0x8000) + gameData + 509676));
      return 0;
    case 0xE:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 566822) - 0x8000) + gameData + 509676) == 1 )
        return 1;
      Mission_TraceObjectiveBlocked(
        14,
        52,
        24,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 566822) - 0x8000) + gameData + 509676));
      return 0;
    case 0xF:
      v22 = 0;
LABEL_86:
      v23 = UNIT_RECORD(v22);
      if ( (unsigned int)*(char *)(v23 + 4) < 4
        && *(__int16 *)(v23 + 16) != -1
        && *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * v22 + 509676) == 4 )
      {
        Mission_TraceObjectiveBlocked(15, v22, *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * v22 + 509676), *(__int16 *)(v23 + 16));
        return 0;
      }
      while ( ++v22 < 100 )
      {
        if ( v22 >= 0 )
          goto LABEL_86;
      }
      v24 = 0;
LABEL_94:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v24 + 147180) <= 0x28
        && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v24 + 147178) == 4 )
      {
        Mission_TraceObjectiveBlocked(
          15,
          v24,
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * v24 + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * v24 + 147176));
        return 0;
      }
      while ( ++v24 < 500 )
      {
        if ( v24 >= 0 )
          goto LABEL_94;
      }
      return 1;
    case 0x10:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574660) - 0x8000) + gameData + 509676) == 1 )
        return 1;
      Mission_TraceObjectiveBlocked(
        16,
        91,
        43,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574660) - 0x8000) + gameData + 509676));
      return 0;
    case 0x11:
      v25 = !MapTile_HasHiddenTreasure(50, 34) && !MapTile_HasHiddenTreasure(51, 73) && !MapTile_HasHiddenTreasure(77, 34) && !MapTile_HasHiddenTreasure(24, 49);
      v12 = v25;
      if ( !v25 )
      {
        Mission_TraceObjectiveBlocked(
          17,
          50,
          34,
          (MapTile_HasHiddenTreasure(50, 34) ? 1 : 0)
            | (MapTile_HasHiddenTreasure(51, 73) ? 2 : 0)
            | (MapTile_HasHiddenTreasure(77, 34) ? 4 : 0)
            | (MapTile_HasHiddenTreasure(24, 49) ? 8 : 0));
        return v12;
      }
      v26 = 0;
LABEL_105:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v26 + 147180) <= 0x28 )
      {
        v27 = UNIT_STACK_STRIDE * v26;
        v28 = gameData + UNIT_STACK_STRIDE * v26;
        if ( *(_BYTE *)(v28 + 147178) != 1 )
        {
          if ( Map_IsTileVisibleToPlayer(*(__int16 *)(v28 + 147174), *(__int16 *)(v28 + 147176), 1) )
          {
            Camera_CenterOnUnit(v26);
            Audio_PlayArtifactSound(0);
            UI_StartTileBlinkFlash(*(__int16 *)(v27 + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(v27 + gameData + 147176), v29);
            Unit_Kill(v27 + gameData + UNIT_STACK_TABLE_OFFSET, 1, a1, a2);
            Timer_BusyWaitWithCallback(100, v30, v31);
          }
        }
      }
      while ( ++v26 < 500 )
      {
        if ( v26 >= 0 )
          goto LABEL_105;
      }
      return v12;
    case 0x12:
      v32 = 0;
      for ( i = 0; i != 372; i += 31 )
      {
        v34 = *(__int16 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 573450) - 0x8000) + gameData + i + 509692);
        if ( v34 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v34 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
          ++v32;
      }
      if ( v32 >= 6 )
        return 1;
      Mission_TraceObjectiveBlocked(18, 85, 38, v32);
      return 0;
    case 0x13:
      if ( *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) )
      {
        Mission_TraceObjectiveBlocked(19, 0, *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET), 0);
        return 0;
      }
      v35 = 2846;
      while ( !*(_DWORD *)(gameData + v35 + PLAYER_RUNTIME_STATE_OFFSET) )
      {
        v35 += PLAYER_DATA_STRIDE;
        if ( v35 >= 7115 )
          return 1;
      }
      Mission_TraceObjectiveBlocked(19, v35 / PLAYER_DATA_STRIDE, *(_DWORD *)(gameData + v35 + PLAYER_RUNTIME_STATE_OFFSET), 0);
      return 0;
    default:
      return 0;
  }
}
// 459CC2: conditional instruction was optimized away because edx.4<1F4u
// 45B21C: conditional instruction was optimized away because eax.4<64u
// 45B29D: conditional instruction was optimized away because edx.4<1F4u
// 45B305: conditional instruction was optimized away because eax.4<64u
// 45B380: conditional instruction was optimized away because edx.4<1F4u
// 45BF9E: conditional instruction was optimized away because ecx.4<1F4u
// 45D242: conditional instruction was optimized away because edx.4<1F4u
// 45E5AA: conditional instruction was optimized away because eax.4<64u
// 45E623: conditional instruction was optimized away because edx.4<1F4u
// 45F136: conditional instruction was optimized away because ecx.4<1F4u
// 459C7E: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45B1DC: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 45B254: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45B2C6: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 45B334: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45BEF3: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45D1FE: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45E56F: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 45E5DF: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45F083: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45BF45: variable 'v13' is possibly undefined
// 45BF66: variable 'v16' is possibly undefined
// 45BF86: variable 'v17' is possibly undefined
// 45BF86: variable 'v18' is possibly undefined
// 45F0D9: variable 'v26' is possibly undefined
// 45F0FA: variable 'v29' is possibly undefined
// 45F11A: variable 'v30' is possibly undefined
// 45F11A: variable 'v31' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 5202E4: using guessed type int gameData;
// 5448A0: using guessed type int dword_5448A0;

//----- (004602F0) --------------------------------------------------------
int Mission_CheckFailureCondition()
{
  int result; // eax
  int v1; // ebx
  int v2; // edx
  int i; // esi
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int j; // ecx
  int v8; // edx
  int v9; // ebx
  int v10; // edx
  int k; // esi
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  int m; // ecx
  int v16; // edx

  switch ( ACTIVE_MISSION_INDEX )
  {
    case 3:
      return *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 560616) - 0x8000) + gameData + 509676) != 0;
    case 4:
    case 0xE:
      return *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) > 0x14u;
    case 5:
      result = (unsigned __int8)g_LanguageIndex;
      if ( g_LanguageIndex )
        return MISSION_FAILURE_FLAG;
      return result;
    case 8:
      v1 = 0;
      v2 = 0;
LABEL_7:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v2 + 147180) <= 0x28 && !*(_BYTE *)(gameData + UNIT_STACK_STRIDE * v2 + 147178) )
      {
        for ( i = 0; i < 10; ++i )
        {
          v4 = *(__int16 *)(UNIT_STACK_STRIDE * v2 + gameData + 31 * i + 147180);
          if ( v4 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v4 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
            ++v1;
        }
      }
      while ( ++v2 < 500 )
      {
        if ( v2 >= 0 )
          goto LABEL_7;
      }
      v5 = 0;
LABEL_19:
      v6 = UNIT_RECORD(v5);
      if ( (unsigned int)*(char *)(v6 + 4) < 4
        && *(__int16 *)(v6 + 16) != -1
        && !*(_BYTE *)(BUILDING_RECORD_SIZE * v5 + gameData + 509676) )
      {
        for ( j = 0; j < 12; ++j )
        {
          v8 = *(__int16 *)(31 * j + gameData + BUILDING_RECORD_SIZE * v5 + 509692);
          if ( v8 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v8 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
            ++v1;
        }
      }
      while ( ++v5 < 100 )
      {
        if ( v5 >= 0 )
          goto LABEL_19;
      }
      return v1 < 12;
    case 0xD:
      return *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 561026) - 0x8000) + gameData + 509676) != 1;
    case 0xF:
      return MISSION_FAILURE_FLAG;
    case 0x12:
      v9 = 0;
      v10 = 0;
      break;
    default:
      return 0;
  }
LABEL_34:
  if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * v10 + 147180) <= 0x28
    && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * v10 + 147178) == 1 )
  {
    for ( k = 0; k < 10; ++k )
    {
      v12 = *(__int16 *)(UNIT_STACK_STRIDE * v10 + gameData + 31 * k + 147180);
      if ( v12 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v12 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        ++v9;
    }
  }
  while ( ++v10 < 500 )
  {
    if ( v10 >= 0 )
      goto LABEL_34;
  }
  v13 = 0;
LABEL_46:
  v14 = UNIT_RECORD(v13);
  if ( (unsigned int)*(char *)(v14 + 4) < 4
    && *(__int16 *)(v14 + 16) != -1
    && *(_BYTE *)(BUILDING_RECORD_SIZE * v13 + gameData + 509676) == 1 )
  {
    for ( m = 0; m < 12; ++m )
    {
      v16 = *(__int16 *)(31 * m + gameData + BUILDING_RECORD_SIZE * v13 + 509692);
      if ( v16 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || v16 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        ++v9;
    }
  }
  while ( ++v13 < 100 )
  {
    if ( v13 >= 0 )
      goto LABEL_46;
  }
  return v9 < 6;
}
// 45C811: conditional instruction was optimized away because edx.4<1F4u
// 45C8A0: conditional instruction was optimized away because eax.4<64u
// 45FB44: conditional instruction was optimized away because edx.4<1F4u
// 45FBD6: conditional instruction was optimized away because eax.4<64u
// 45C792: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45C83C: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 45FAC2: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 45FB6F: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 511130: using guessed type char g_LanguageIndex;
// 5202E4: using guessed type int gameData;

//----- (00460360) --------------------------------------------------------
void Scenario_LoadMissionByIndex(int mission_index, double a2)
{
  int building_record; // eax
  unsigned __int16 building_word; // cx
  int castle_index; // eax
  int player_index; // edx
  unsigned __int16 stack_index; // ax
  int slot_index; // ecx

  Diagnostics_TraceWorldMapActionEvent("mission_load_enter", g_SelectedUnitIndex, mission_index, ACTIVE_MISSION_INDEX, 0);
  switch ( mission_index )
  {
    case 0:
      Diagnostics_TraceBootstrapEvent("mission0-load-map");
      Map_LoadFromFile((uintptr_t)"k_mapa1l.map");
      Diagnostics_TraceBootstrapEvent("mission0-reset-players");
      ACTIVE_MISSION_INDEX = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_MINIMAP_VISIBLE(0) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Bochuwit");
      Diagnostics_TraceBootstrapEvent("mission0-minimap-create");
      MiniMap_CreateSurface(a2);
      Diagnostics_TraceBootstrapEvent("mission0-create-castle");
      createCastle(a2, 30, 42, 0, 2, "Cantbelly", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      Diagnostics_TraceBootstrapEvent("mission0-create-player-stacks");
      createUnit(a2, 30, 44, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_SKELETON, -1);
      createUnit(a2, 31, 44, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 32, 44, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      Diagnostics_TraceBootstrapEvent("mission0-create-enemy-stacks");
      createUnit(a2, 46, 45, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 15, 6, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 48, 14, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, -1);
      Unit_Create(UNIT_TYPE_ARCHER, 1, 35, 0, 11);
      Unit_Create(UNIT_TYPE_ARCHER, 1, 49, 0, 39);
      Unit_Create(UNIT_TYPE_ARCHER, 1, 40, 0, 3);
      Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, 1, 19, 0, 12);
      Diagnostics_TraceBootstrapEvent("mission0-ai-init");
      Rules_LogMissionSetupInfo();
      Diagnostics_TraceBootstrapEvent("mission0-player-view");
      Game_InitPlayerViewState();
      Diagnostics_TraceBootstrapEvent("mission0-load-done");
      break;
    case 1:
      Map_LoadFromFile((uintptr_t)"k_mapa2l.map");
      ACTIVE_MISSION_INDEX = 1;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_MINIMAP_VISIBLE(0) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Ianos");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 44, 46, 0, 2, "Stormus", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 44, 48, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      castle_index = createCastle(a2, 1, 23, 1, 2, "Drakefly", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 1, 25, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 44, 24, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 18, 48, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 12, 0, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      PLAYER_CAMERA_LEFT(0) = 91;
      PLAYER_CAMERA_TOP(0) = 21;
      MAP_VIEW_LEFT = 90;
      MAP_VIEW_TOP = 21;
      break;
    case 2:
      Map_LoadFromFile((uintptr_t)"k_mapa3l.map");
      ACTIVE_MISSION_INDEX = 2;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_MINIMAP_VISIBLE(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Bochuwit");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 98, 24, 0, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 98, 25, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 97, 25, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 97, 24, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 98, 26, 0, UNIT_TYPE_RAM, -1);
      castle_index = createCastle(a2, 41, 68, 1, 2, "Treg Rock", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 83, 16, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 69, 46, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 87, 61, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 52, 58, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 40, 18, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 91, 6, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 85, 9, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 43, 52, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 68, 68, 1, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 35, 69, 1, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 94, 77, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 74, 31, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      PLAYER_CAMERA_LEFT(0) = 91;
      PLAYER_CAMERA_TOP(0) = 21;
      MAP_VIEW_LEFT = 90;
      MAP_VIEW_TOP = 21;
      break;
    case 3:
      Map_LoadFromFile((uintptr_t)"k_mapa4j.map");
      ACTIVE_MISSION_INDEX = 3;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "McDonowan");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Sir Wenom");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Lord Gorio");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 21, 21, 0, 1, "Ughuata", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) = 300;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 20, 20, 0, UNIT_TYPE_CATAPULT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 23, 20, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 20, 23, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      createUnit(a2, 23, 23, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(23, 23));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 9) = Rng_RandRange(5, 20);
      createUnit(a2, 22, 23, 0, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 41, 34, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 13, 31, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 15, 24, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 24, 13, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 37, 22, 1, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 12, 0, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(12, 0));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) = (*(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) & 0xFC) | 1;
      createUnit(a2, 10, 27, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 21, 48, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 29, 15, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 6, 20, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 1, 9, 2, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, -1);
      createUnit(a2, 40, 1, 2, UNIT_TYPE_PEGASUS, UNIT_TYPE_PEGASUS, UNIT_TYPE_WINGER, UNIT_TYPE_WINGER, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, -1);
      createUnit(a2, 23, 43, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      createUnit(a2, 39, 31, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(39, 31));
      *(_BYTE *)(UNIT_STACK(stack_index) + 204) |= 3u;
      createUnit(a2, 39, 35, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 49, 48, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 1, 47, 3, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 4:
      Map_LoadFromFile((uintptr_t)"k_mapa5j.map");
      ACTIVE_MISSION_INDEX = 4;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Agordeh II");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "McDonowan");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 41, 48, 0, 2, "Totaweon", UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 41, 50, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 42, 50, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 43, 50, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      castle_index = createCastle(a2, 56, 69, 1, 1, "Hopenberg", UNIT_TYPE_BUILDER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_WORD *)(building_record + 18) = 9;
      createUnit(a2, 56, 71, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      stack_index = *(unsigned __int16 *)(gameData + 567716);
      Building_UnitGetInto(stack_index, castle_index, 56, 71, a2);
      for ( slot_index = 0; slot_index < 12; ++slot_index )
        *(_BYTE *)(building_record + 31 * slot_index + 30) |= 3u;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 0)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 0)) = 0;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 1)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 1)) = 0;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 55, 71, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 56, 71, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 57, 71, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 32, 36, 2, 2, "Jolarion", UNIT_TYPE_BUILDER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      castle_index = createCastle(a2, 50, 23, 2, 2, "Akserion", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 50, 25, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      castle_index = createCastle(a2, 25, 48, 2, 2, "Bodeon", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 25, 50, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedCastleFact(*(unsigned __int16 *)(gameData + 567712) - 0x8000, 4);
      Game_InitPlayerViewState();
      break;
    case 5:
      Map_LoadFromFile((uintptr_t)"k_mapa6j.map");
      ACTIVE_MISSION_INDEX = 5;
      *(_BYTE *)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_RELIGION_FLAG(2) = 0;
      PLAYER_AI_INTELLIGENCE(1) = 1;
      PLAYER_AI_INTELLIGENCE(2) = 1;
      PLAYER_AI_INTELLIGENCE(3) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      if ( g_LanguageIndex )
      {
        strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Furd");
        strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Dulimam");
      }
      else
      {
        strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Wetus");
        strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Riludius");
      }
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Agordeh");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 71, 45, 0, 2, "Defambrion", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) += 200;
      createUnit(a2, 70, 47, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 71, 47, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PIKEMAN, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 72, 47, 0, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 73, 47, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 71, 44, 0, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 72, 44, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 56, 21, 1, 2, "Histone", UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 26, 41, 1, 2, "Katha Gha", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) = 1000;
      createUnit(a2, 56, 23, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 57, 23, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 58, 23, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 73, 23, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createCastle(a2, 68, 77, 2, 2, "Girock", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 67, 79, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 68, 79, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 73, 63, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 69, 79, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 70, 79, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 59, 50, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PIKEMAN, UNIT_TYPE_CROSSBOWER, -1);
      castle_index = createCastle(a2, 42, 54, 3, 2, "Ghih Up", UNIT_TYPE_BUILDER, -1);
      *(_WORD *)(BUILDING_RECORD(castle_index) + 18) = -1;
      createUnit(a2, 41, 56, 3, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, -1);
      createUnit(a2, 42, 56, 3, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 43, 56, 3, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, -1);
      createUnit(a2, 44, 56, 3, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 42, 53, 3, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, -1);
      stack_index = *(unsigned __int16 *)(gameData + 564880);
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 9) |= 3u;
      createUnit(a2, 87, 66, 3, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedPlayerFact(3, 5);
      Game_InitPlayerViewState();
      break;
    case 6:
      Map_LoadFromFile((uintptr_t)"k_mapa7z.map");
      ACTIVE_MISSION_INDEX = 6;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(2) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Walter");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Drebegen");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 13, 4, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 14, 4, 0, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 14, 3, 0, UNIT_TYPE_CANNON, -1);
      createCastle(a2, 30, 23, 1, 2, "Dragmounth", UNIT_TYPE_BUILDER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createCastle(a2, 54, 4, 1, 2, "Akserion", UNIT_TYPE_BUILDER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 30, 25, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 31, 25, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 54, 6, 1, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 85, 81, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 12, 92, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_RAM, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(12, 92));
      *(_BYTE *)(UNIT_STACK(stack_index) + 251) |= 3u;
      createUnit(a2, 17, 39, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 57, 38, 1, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, -1);
      createUnit(a2, 74, 71, 1, UNIT_TYPE_CANNON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(74, 71));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      Rules_SyncArmyFactStrength(
        (__int16 *)UNIT_STACK(stack_index),
        145 * stack_index,
        gameData + UNIT_STACK_TABLE_OFFSET,
        UNIT_STACK_OWNER_INDEX(UNIT_STACK(stack_index)),
        200 * UNIT_STACK_TILE_ROW(UNIT_STACK(stack_index)),
        a2);
      createUnit(a2, 82, 9, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(82, 9));
      Rules_SyncArmyFactStrength(
        (__int16 *)UNIT_STACK(stack_index),
        145 * stack_index,
        gameData + UNIT_STACK_TABLE_OFFSET,
        UNIT_STACK_OWNER_INDEX(UNIT_STACK(stack_index)),
        200 * UNIT_STACK_TILE_ROW(UNIT_STACK(stack_index)),
        a2);
      castle_index = createCastle(a2, 90, 41, 2, 2, "Ghettan", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 0)) = UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 0)) = 0;
      castle_index = createCastle(a2, 41, 67, 2, 2, "Bhua Rock", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) = 1000;
      castle_index = createCastle(a2, 5, 56, 2, 1, "Jolarion", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) = 2000;
      createUnit(a2, 41, 69, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 42, 69, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      PLAYER_CAMERA_LEFT(0) = 10;
      PLAYER_CAMERA_TOP(0) = 0;
      MAP_VIEW_LEFT = 10;
      MAP_VIEW_TOP = 0;
      break;
    case 7:
      Map_LoadFromFile((uintptr_t)"k_mapa8z.map");
      ACTIVE_MISSION_INDEX = 7;
      Rules_RetractTreasureFact(55, 45, a2);
      Rules_RetractTreasureFact(50, 27, a2);
      Rules_RetractTreasureFact(35, 63, a2);
      Rules_RetractTreasureFact(14, 68, a2);
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Uraken");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Wodar");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Richard V");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 56, 70, 0, 2, "Weghetown", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 1, 51, 0, 1, "Henrion", UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 56, 72, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_CATAPULT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 57, 72, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CATAPULT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 1, 53, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_RAM, UNIT_TYPE_MUSKETEER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 2, 53, 0, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 9, 25, 1, 2, "Moon Town", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 18, 34, 1, 2, "Gate Stone", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 9, 27, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 18, 36, 1, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_TROLL, UNIT_TYPE_GHOST, -1);
      createUnit(a2, 19, 36, 1, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_CYCLOP, -1);
      createCastle(a2, 43, 21, 2, 2, "Canoowar", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 54, 31, 2, 1, "Trungeon", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 42, 23, 2, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 43, 23, 2, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(43, 23));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 44, 23, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 45, 23, 2, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 54, 33, 2, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 55, 33, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 77, 39, 3, 2, "Leweburg", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 75, 67, 3, 1, "Defambrion", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 77, 41, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 78, 41, 3, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ELEPHANT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(78, 41));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 75, 69, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 76, 69, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(76, 69));
      for ( slot_index = 1; slot_index < 3; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      for ( slot_index = 3; slot_index < 5; ++slot_index )
      {
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) &= 0xFCu;
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index + 1) + 27) =
          *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) | 2;
      }
      createUnit(a2, 77, 69, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 8:
      Map_LoadFromFile((uintptr_t)"k_mapa9z.map");
      ACTIVE_MISSION_INDEX = 8;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_QUEEN_RELATIONSHIP_STATE(0) = 5;
      PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN(0) = 10;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Sir James");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Ruryk");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Riludius");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 8, 27, 0, 2, "Totaweon", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      castle_index = createCastle(a2, 30, 23, 0, 2, "Gordmouth", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) -= 100;
      createUnit(a2, 8, 29, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 9, 29, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createUnit(a2, 10, 29, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_WINGER, -1);
      createUnit(a2, 10, 14, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 11, 31, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 22, 29, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 30, 39, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 1, 28, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 8, 50, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 21, 57, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 21, 59, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 28, 57, 0, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createCastle(a2, 22, 77, 1, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 59, 66, 1, 2, "Ghettan", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 22, 79, 1, UNIT_TYPE_EAGLE, UNIT_TYPE_FLY, -1);
      createUnit(a2, 59, 68, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      createUnit(a2, 60, 68, 1, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createCastle(a2, 4, 62, 2, 2, "Hopenberg", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createCastle(a2, 84, 64, 2, 2, "Katha Gha", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 4, 64, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 5, 64, 2, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(5, 64));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 6, 64, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, -1);
      createUnit(a2, 84, 66, 2, UNIT_TYPE_WINGER, UNIT_TYPE_EAGLE, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_MUSKETEER, UNIT_TYPE_BUILDER, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(84, 66));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 85, 66, 2, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, -1);
      createUnit(a2, 86, 66, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createCastle(a2, 96, 86, 3, 2, "Werneom", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 95, 88, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_TROLL, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 96, 88, 3, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_ELEPHANT, -1);
      createUnit(a2, 97, 88, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_WIZARD, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(103, 0));
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 5) + 27) =
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 5) + 27) & 0xFC | 2;
      createUnit(a2, 96, 85, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(102, 69));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 27) |= 3u;
      createUnit(a2, 97, 85, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(102, 97));
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 27) =
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 27) & 0xFC | 2;
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 9:
      Map_LoadFromFile((uintptr_t)"k_map10l.map");
      ACTIVE_MISSION_INDEX = 9;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_AI_INTELLIGENCE(4) = 2;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Alan");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Twogor");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Drebegen");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Mieszko");
      strcpy((char *)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Chester");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 13, 3, 0, 2, "Gorendberg", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) -= 100;
      *(_BYTE *)(building_record + 444) = *(_BYTE *)(building_record + 444) & 0xF8 | 2;
      castle_index = createCastle(a2, 94, 95, 0, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) = 500;
      *(_BYTE *)(building_record + 444) = *(_BYTE *)(building_record + 444) & 0xF8 | 2;
      createUnit(a2, 13, 5, 0, UNIT_TYPE_FLY, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CATAPULT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 14, 5, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 94, 97, 0, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 95, 97, 0, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_DRAGON, -1);
      castle_index = createCastle(a2, 62, 53, 1, 2, "Ghettan", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) = 3000;
      createUnit(a2, 61, 55, 1, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 62, 55, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_WIZARD, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 63, 55, 1, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CANNON, UNIT_TYPE_EAGLE, -1);
      createUnit(a2, 64, 55, 1, UNIT_TYPE_DRAGON, UNIT_TYPE_PEGASUS, UNIT_TYPE_WINGER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 62, 52, 1, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_WIZARD, UNIT_TYPE_DRAGON, -1);
      createUnit(a2, 63, 52, 1, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, -1);
      castle_index = createCastle(a2, 58, 11, 2, 2, "Bhua Rock", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) = 3000;
      createUnit(a2, 57, 13, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_TROLL, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 58, 13, 2, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CANNON, UNIT_TYPE_WINGER, -1);
      createUnit(a2, 59, 13, 2, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 60, 13, 2, UNIT_TYPE_WINGER, UNIT_TYPE_PEGASUS, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_WIZARD, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 58, 10, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 58, 10, 2, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_DRAGON, -1);
      createCastle(a2, 95, 16, 3, 2, "Katha Gha", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 11, 41, 3, 2, "Stormus", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 95, 18, 3, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_TROLL, UNIT_TYPE_PEGASUS, -1);
      createUnit(a2, 96, 18, 3, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 11, 43, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 12, 43, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 32, 84, 4, 2, "Guluali", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) += 500;
      *(_BYTE *)(building_record + 444) = *(_BYTE *)(building_record + 444) & 0xF8 | 3;
      createUnit(a2, 31, 86, 4, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 32, 86, 4, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 33, 86, 4, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 34, 86, 4, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_PEGASUS, UNIT_TYPE_PEGASUS, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 32, 83, 4, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 10:
      Map_LoadFromFile((uintptr_t)"p_mapa1z.map");
      ACTIVE_MISSION_INDEX = 10;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      PLAYER_MINIMAP_VISIBLE(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Gaalaad");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 15, 31, 1, 2, "Timbran", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) -= 100;
      building_word = *(_WORD *)(building_record + 430);
      *(_WORD *)(building_record + 430) = (building_word & 0xF000) | (((building_word & 0xFFF) - 0x32) & 0xFFF);
      createUnit(a2, 15, 33, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 16, 33, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 17, 33, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 1, 22, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 27, 12, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 48, 20, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 34, 37, 2, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 11, 13, 2, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 4, 22, 2, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 10, 25, 2, UNIT_TYPE_LIGHT_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 11:
      Map_LoadFromFile((uintptr_t)"p_mapa2z.map");
      ACTIVE_MISSION_INDEX = 11;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Wetus");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 22, 13, 1, 2, "Gatgally", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 22, 15, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createCastle(a2, 34, 5, 2, 2, "Guluali", UNIT_TYPE_BUILDER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 33, 7, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 34, 7, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 35, 7, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 36, 7, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 12:
      Map_LoadFromFile((uintptr_t)"p_mapa3z.map");
      ACTIVE_MISSION_INDEX = 12;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Gaalaad");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 70, 81, 1, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 71, 81, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 69, 82, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 70, 82, 1, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 71, 83, 1, UNIT_TYPE_RAM, -1);
      castle_index = createCastle(a2, 59, 14, 2, 2, "Sarturia", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) = 5000;
      createUnit(a2, 67, 36, 2, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 25, 85, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 45, 73, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 69, 91, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 77, 64, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 36, 52, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 41, 49, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 62, 94, 2, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      MAP_VIEW_LEFT = 67;
      PLAYER_CAMERA_LEFT(1) = MAP_VIEW_LEFT;
      MAP_VIEW_TOP = 77;
      PLAYER_CAMERA_TOP(1) = MAP_VIEW_TOP;
      break;
    case 13:
      Map_LoadFromFile((uintptr_t)"p_mapa4l.map");
      ACTIVE_MISSION_INDEX = 13;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Leryks X");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Glazur");
      strcpy((char *)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Sir John");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 23, 26, 1, 2, "Ungught", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 22, 25, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 25, 25, 1, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 22, 28, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 25, 28, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(25, 28));
      for ( slot_index = 0; slot_index < UNIT_STACK_SLOT_COUNT; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 9) = Rng_RandRange(5, 20);
      createUnit(a2, 26, 28, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      createUnit(a2, 7, 15, 2, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 1, 1, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 26, 47, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 18, 38, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 35, 18, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 33, 35, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 45, 29, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 10, 33, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 26, 45, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 48, 8, 4, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      createUnit(a2, 21, 10, 4, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_CATAPULT, -1);
      createUnit(a2, 35, 17, 4, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 14:
      Map_LoadFromFile((uintptr_t)"p_mapa5l.map");
      ACTIVE_MISSION_INDEX = 14;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(2) = 0;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Uraken");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Wodar");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 50, 3, 1, 2, "Weghetown", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      building_record = BUILDING_RECORD(castle_index);
      building_word = *(_WORD *)(building_record + 430);
      *(_WORD *)(building_record + 430) = building_word & 0xF000;
      createUnit(a2, 50, 5, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 51, 5, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 52, 5, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 49, 5, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      castle_index = createCastle(a2, 52, 24, 2, 2, "Timbran", UNIT_TYPE_BUILDER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_WORD *)(building_record + 18) = 0xF;
      createUnit(a2, 52, 26, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(52, 26));
      Building_UnitGetInto(stack_index, castle_index, 52, 26, a2);
      for ( slot_index = 0; slot_index < 12; ++slot_index )
        *(_BYTE *)(building_record + 31 * slot_index + 30) =
          (*(_BYTE *)(building_record + 31 * slot_index + 30) & 0xFC) | 1;
      Building_OnGarrisonChange(castle_index, 0, a2);
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 0)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 0)) = 0;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 1)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 1)) = 0;
      BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(building_record, 2)) = UNIT_TYPE_SPECIAL_FOOT_PERSONAGE;
      BUILDING_PRISONER_OWNER(BUILDING_PRISONER_SLOT(building_record, 2)) = 0;
      Building_OnGarrisonChange(castle_index, 0, a2);
      createUnit(a2, 64, 4, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 50, 27, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      castle_index = createCastle(a2, 39, 18, 3, 2, "Fraggmeon", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) += 200;
      castle_index = createCastle(a2, 17, 34, 3, 2, "Eufurhon", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) += 200;
      createUnit(a2, 39, 20, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 40, 20, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 16, 36, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 17, 36, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 18, 36, 3, UNIT_TYPE_PIKEMAN, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 25, 4, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedCastleFact(*(unsigned __int16 *)(TILE_INDEX(52, 24)) - 0x8000, 14);
      Game_InitPlayerViewState();
      break;
    case 15:
      Map_LoadFromFile((uintptr_t)"p_mapa6l.map");
      ACTIVE_MISSION_INDEX = 15;
      *(_BYTE *)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_AI_INTELLIGENCE(4) = 2;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Frederic");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Sir James");
      strcpy((char *)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Agordeh");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 59, 9, 1, 2, "Defambrion", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) += 200;
      createCastle(a2, 50, 96, 1, 1, "Ghondur", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 59, 11, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 60, 11, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_PIKEMAN, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 61, 11, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 49, 98, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 50, 98, 1, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 51, 98, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 86, 55, 2, 2, "Histone", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 86, 57, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 87, 57, 2, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createCastle(a2, 79, 2, 3, 2, "Girock", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 78, 4, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 79, 4, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 80, 4, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 81, 4, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 80, 1, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      castle_index = createCastle(a2, 48, 38, 4, 2, "Ghih Up", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) = 1000;
      *(_WORD *)(building_record + 18) = -1;
      createUnit(a2, 48, 40, 4, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 49, 40, 4, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, -1);
      createUnit(a2, 50, 40, 4, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, -1);
      createUnit(a2, 48, 57, 4, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 18, 75, 4, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, -1);
      createUnit(a2, 37, 6, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      castle_index = createCastle(a2, 19, 32, 4, 2, "Guluali", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) = 2000;
      createUnit(a2, 19, 34, 4, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      Rules_LogMissionSetupInfo();
      Rules_LogAssignedPlayerFact(4, 15);
      Game_InitPlayerViewState();
      break;
    case 16:
      Map_LoadFromFile((uintptr_t)"p_mapa7j.map");
      ACTIVE_MISSION_INDEX = 16;
      *(_BYTE *)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 1;
      PLAYER_AI_INTELLIGENCE(3) = 2;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Kalev");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Ianos");
      MiniMap_CreateSurface(a2);
      createUnit(a2, 21, 35, 1, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 20, 36, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 22, 36, 1, UNIT_TYPE_CANNON, -1);
      createUnit(a2, 22, 36, 1, UNIT_TYPE_CANNON, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 91, 43, 2, 2, "Gwadat", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_BYTE *)(building_record + 444) = *(_BYTE *)(building_record + 444) & 0xF8 | 3;
      createCastle(a2, 54, 74, 2, 2, "Cantown", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 91, 45, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 92, 45, 2, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 93, 45, 2, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createUnit(a2, 54, 76, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, -1);
      createCastle(a2, 35, 3, 2, 3, "Thubeos", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 66, 45, 2, 3, "Akserion", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 35, 5, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 36, 5, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 66, 47, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 67, 47, 3, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_GORAL, -1);
      createUnit(a2, 21, 28, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 28, 76, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_SPEARMAN, UNIT_TYPE_HEAVY_SPEARMAN, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      MAP_VIEW_LEFT = 17;
      PLAYER_CAMERA_LEFT(1) = MAP_VIEW_LEFT;
      MAP_VIEW_TOP = 32;
      PLAYER_CAMERA_TOP(1) = MAP_VIEW_TOP;
      break;
    case 17:
      Map_LoadFromFile((uintptr_t)"p_mapa8j.map");
      ACTIVE_MISSION_INDEX = 17;
      *(_BYTE *)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
      Rules_RetractTreasureFact(50, 34, a2);
      Rules_RetractTreasureFact(51, 73, a2);
      Rules_RetractTreasureFact(77, 34, a2);
      Rules_RetractTreasureFact(24, 49, a2);
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_AI_INTELLIGENCE(2) = 2;
      PLAYER_AI_INTELLIGENCE(3) = 2;
      PLAYER_AI_INTELLIGENCE(4) = 2;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Lord Ruwe");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "McGregor");
      strcpy((char *)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Crowley");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 11, 45, 1, 2, "Stormus", UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 70, 20, 1, 1, "Dark Town", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) -= 100;
      createUnit(a2, 12, 47, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_CATAPULT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 22, 71, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 72, 22, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_RAM, UNIT_TYPE_MUSKETEER, UNIT_TYPE_ARCHER, -1);
      createCastle(a2, 32, 5, 2, 2, "Treg Rock", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 42, 27, 2, 2, "Bodeon", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 32, 7, 2, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      createUnit(a2, 33, 7, 2, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_SKELETON, -1);
      createUnit(a2, 34, 7, 2, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CANNON, -1);
      createCastle(a2, 25, 38, 3, 2, "Girock", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 61, 41, 3, 1, "Bodeon", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 25, 40, 3, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 26, 40, 3, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(26, 40));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      createUnit(a2, 60, 43, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 61, 43, 3, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_MUSKETEER, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(61, 43));
      for ( slot_index = 3; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      createUnit(a2, 62, 43, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 63, 43, 3, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a2, 62, 84, 4, 2, "Leweburg", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 58, 61, 4, 1, "Defambrion", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 62, 86, 4, UNIT_TYPE_FORESTER, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 63, 86, 4, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ELEPHANT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(63, 86));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      createUnit(a2, 56, 79, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 65, 44, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(65, 44));
      for ( slot_index = 2; slot_index < 4; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 3u;
      for ( slot_index = 4; slot_index < 6; ++slot_index )
      {
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) &= 0xFCu;
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 12) |= 2u;
      }
      createUnit(a2, 58, 63, 4, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 18:
      Map_LoadFromFile((uintptr_t)"p_mapa9j.map");
      ACTIVE_MISSION_INDEX = 18;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(3) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Drebegen");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Tubius");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Lord Gorio");
      strcpy((char *)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "McDan");
      MiniMap_CreateSurface(a2);
      createCastle(a2, 85, 38, 1, 2, "Cantbelly", UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 15, 23, 1, 2, "Stone Bell", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) -= 100;
      createUnit(a2, 85, 40, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 86, 40, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, -1);
      createUnit(a2, 15, 25, 1, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 16, 25, 1, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      createCastle(a2, 9, 89, 2, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 9, 91, 2, UNIT_TYPE_EAGLE, UNIT_TYPE_FLY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 10, 91, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      createUnit(a2, 11, 91, 2, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createCastle(a2, 6, 5, 3, 2, "Hopenberg", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createCastle(a2, 82, 55, 3, 2, "Katha Gha", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      createUnit(a2, 6, 7, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 7, 7, 3, UNIT_TYPE_FLY, UNIT_TYPE_FLY, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(7, 7));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      createUnit(a2, 82, 57, 3, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, -1);
      createUnit(a2, 83, 57, 3, UNIT_TYPE_WINGER, UNIT_TYPE_EAGLE, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_MUSKETEER, UNIT_TYPE_BUILDER, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(83, 57));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      createUnit(a2, 84, 57, 3, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_WORM, -1);
      createUnit(a2, 6, 91, 3, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createCastle(a2, 27, 49, 4, 2, "Werneom", UNIT_TYPE_BUILDER, -1);
      createCastle(a2, 48, 72, 4, 1, "Bokumia", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 27, 51, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_TROLL, UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 28, 51, 4, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_ELEPHANT, -1);
      createUnit(a2, 10, 51, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_WIZARD, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_SCORPION, UNIT_TYPE_CATAPULT, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(10, 51));
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) |= 3u;
      createUnit(a2, 48, 74, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(48, 74));
      for ( slot_index = 4; slot_index < 6; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      createUnit(a2, 49, 74, 4, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(49, 74));
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) &= 0xFCu;
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) |= 2u;
      castle_index = createCastle(a2, 62, 79, 0, 1, "Fhur Tao", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) += 200;
      createUnit(a2, 62, 81, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 63, 81, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a2, 61, 81, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      createUnit(a2, 70, 80, 0, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(70, 80));
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 28) &= 0xFCu;
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 1) + 28) |= 1u;
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) &= 0xFCu;
      *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), 2) + 28) |= 1u;
      createUnit(a2, 37, 29, 0, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      stack_index = *(unsigned __int16 *)(TILE_INDEX(37, 29));
      for ( slot_index = 0; slot_index < 5; ++slot_index )
        *(_BYTE *)(UNIT_STACK_SLOT(UNIT_STACK(stack_index), slot_index) + 28) |= 3u;
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    case 19:
      Map_LoadFromFile((uintptr_t)"p_map10z.map");
      ACTIVE_MISSION_INDEX = 19;
      for ( player_index = 0; player_index < 5; ++player_index )
        Game_ResetPlayerRuntimeStateByIndex(player_index);
      PLAYER_IS_ACTIVE(0) = 1;
      PLAYER_IS_ACTIVE(1) = 1;
      PLAYER_IS_ACTIVE(2) = 1;
      PLAYER_IS_ACTIVE(3) = 1;
      PLAYER_IS_ACTIVE(4) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(0) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(1) = 1;
      PLAYER_HAS_HUMAN_CONTROLLER(2) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(3) = 0;
      PLAYER_HAS_HUMAN_CONTROLLER(4) = 0;
      PLAYER_RELIGION_FLAG(1) = 0;
      PLAYER_RELIGION_FLAG(3) = 0;
      PLAYER_MINIMAP_VISIBLE(1) = 1;
      strcpy((char *)(PLAYER_DATA(0) + PLAYER_DISPLAY_NAME_OFFSET), "Sir Mordus");
      strcpy((char *)(PLAYER_DATA(1) + PLAYER_DISPLAY_NAME_OFFSET), "Raylin");
      strcpy((char *)(PLAYER_DATA(2) + PLAYER_DISPLAY_NAME_OFFSET), "Galaghan");
      strcpy((char *)(PLAYER_DATA(3) + PLAYER_DISPLAY_NAME_OFFSET), "Longhand");
      strcpy((char *)(PLAYER_DATA(4) + PLAYER_DISPLAY_NAME_OFFSET), "Riludius");
      MiniMap_CreateSurface(a2);
      castle_index = createCastle(a2, 83, 15, 1, 2, "Gorendberg", UNIT_TYPE_BUILDER, -1);
      building_record = BUILDING_RECORD(castle_index);
      *(_DWORD *)(building_record + 438) -= 100;
      createCastle(a2, 73, 68, 1, 2, "Timbran", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 83, 17, 1, UNIT_TYPE_ARCHER, UNIT_TYPE_ARCHER, UNIT_TYPE_CATAPULT, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_FLY, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      createUnit(a2, 84, 17, 1, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createUnit(a2, 73, 70, 1, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, -1);
      castle_index = createCastle(a2, 20, 9, 2, 2, "Ghettan", UNIT_TYPE_BUILDER, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, UNIT_TYPE_SPECIAL_FOOT_PERSONAGE, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) = 600;
      createCastle(a2, 70, 30, 2, 2, "Drakefly", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 20, 11, 2, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 21, 11, 2, UNIT_TYPE_MUSKETEER, UNIT_TYPE_MUSKETEER, UNIT_TYPE_WIZARD, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, -1);
      createUnit(a2, 22, 11, 2, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CYCLOP, UNIT_TYPE_CANNON, UNIT_TYPE_EAGLE, -1);
      createUnit(a2, 70, 32, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_DRAGON, UNIT_TYPE_PEGASUS, UNIT_TYPE_WINGER, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 71, 32, 2, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_SCORPION, UNIT_TYPE_WIZARD, UNIT_TYPE_DRAGON, -1);
      createCastle(a2, 36, 54, 3, 2, "Bhua Rock", UNIT_TYPE_BUILDER, -1);
      createUnit(a2, 35, 56, 3, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_TROLL, UNIT_TYPE_SCORPION, -1);
      createUnit(a2, 36, 56, 3, UNIT_TYPE_EAGLE, UNIT_TYPE_EAGLE, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CANNON, UNIT_TYPE_WINGER, -1);
      createUnit(a2, 37, 56, 3, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, UNIT_TYPE_HEAVY_CAVALRY, -1);
      createUnit(a2, 38, 56, 3, UNIT_TYPE_WINGER, UNIT_TYPE_PEGASUS, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 36, 53, 3, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_TROLL, UNIT_TYPE_ELEPHANT, UNIT_TYPE_SCORPION, -1);
      createCastle(a2, 79, 2, 4, 2, "Katha Gha", UNIT_TYPE_BUILDER, -1);
      castle_index = createCastle(a2, 88, 63, 4, 1, "Stormus", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) += 300;
      createUnit(a2, 79, 4, 4, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, UNIT_TYPE_TROLL, UNIT_TYPE_PEGASUS, -1);
      createUnit(a2, 80, 4, 4, UNIT_TYPE_WORM, UNIT_TYPE_WORM, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_ELEPHANT, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      createUnit(a2, 88, 65, 4, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, -1);
      createUnit(a2, 89, 65, 4, UNIT_TYPE_SCORPION, UNIT_TYPE_FLY, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, -1);
      castle_index = createCastle(a2, 95, 51, 0, 2, "Guluali", UNIT_TYPE_BUILDER, -1);
      *(_DWORD *)(BUILDING_RECORD(castle_index) + 438) += 300;
      createUnit(a2, 95, 53, 0, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createUnit(a2, 96, 53, 0, UNIT_TYPE_SKELETON, UNIT_TYPE_SKELETON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      createUnit(a2, 97, 53, 0, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_LIGHT_CAVALRY, UNIT_TYPE_KNIGHTS, UNIT_TYPE_KNIGHTS, UNIT_TYPE_WORM, UNIT_TYPE_GHOST, UNIT_TYPE_GHOST, -1);
      createUnit(a2, 55, 79, 0, UNIT_TYPE_CATAPULT, UNIT_TYPE_CATAPULT, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_DRAGON_CAVALRY, UNIT_TYPE_PEGASUS, UNIT_TYPE_PEGASUS, -1);
      createUnit(a2, 78, 98, 0, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_DRAGON, UNIT_TYPE_TROLL, UNIT_TYPE_TROLL, -1);
      Rules_LogMissionSetupInfo();
      Game_InitPlayerViewState();
      break;
    default:
      break;
  }
  Diagnostics_TraceWorldMapActionEvent(
    "mission_load_done",
    g_SelectedUnitIndex,
    mission_index,
    ACTIVE_MISSION_INDEX,
    g_CurrentPlayerIndex);
  Diagnostics_TraceWorldMapUnitSnapshot("after_mission_load");
}

//----- (00460370) --------------------------------------------------------
int  Scenario_LoadMissionByIndexAndPlay(char *a1, int a2, DWORD a3, double a4)
{
  int mission_index; // eax
  unsigned __int8 saved_campaign_state[27]; // [esp-1Bh] [ebp-1Bh] BYREF

  mission_index = (int)(size_t)a1;
  qmemcpy(saved_campaign_state, (const void *)(gameData + 147147), 0x1Bu);
  if ( mission_index && mission_index != 10 )
    Video_PlayAviWithModeGuard(0, aZwy01_0);
  Mission_PlayInfoSlideshow(mission_index, a1);
  WorldMap_Initialize((char)mission_index, a3);
  Scenario_LoadMissionByIndex(mission_index, a4);
  if ( mission_index && mission_index != 10 )
    qmemcpy((void *)(gameData + 147147), saved_campaign_state, 0x1Bu);
  return PlayGame(0, (char)mission_index, a3, 0, a4);
}
// 5202E4: using guessed type int gameData;

//----- (004603F0) --------------------------------------------------------
int __thiscall RenderState_ConstructGlobalInstance(void *this)
{
  int v1; // edx
  int v2; // ecx

  Device_GetParamA((int)g_RenderState, (int)this);
  return CRT_RegisterFinalizableObject(v2, v1);
}
// 4603FF: variable 'v2' is possibly undefined
// 4603FF: variable 'v1' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 544CD8: using guessed type _DWORD g_RenderState[9];

/*
 * The original `unk_545158` descriptor lives far beyond the render-state slab
 * rooted at `g_RenderState`. In the compacted C global layout those regions sit
 * adjacent, so mutating the descriptor's width/height fields would overwrite
 * `g_RenderState + 0x3c`, which is the live descriptor pointer used by
 * `RenderState_SelectCursorDescriptor` and `RenderState_RecalculateCursorBoundsForRect`. Keep the bootstrap cursor descriptor in
 * dedicated storage until the broader DGROUP layout is recovered safely.
 */
static _DWORD g_RenderVideoInitCursorDescriptor[9];
static _DWORD *Compat_RenderStateSurface(int render_state, unsigned int field_offset);
static _DWORD *Compat_RenderStateCursorDescriptor(int render_state);

static void Compat_SyncRenderCursorGlobals(const _DWORD *render_state)
{
  g_MouseCursorRawX = render_state[9];
  g_MouseCursorRawY = render_state[10];
  g_CursorCoordShift = (unsigned char)render_state[277];
}

typedef struct CompatRenderStateTail
{
  int field_464_active;
  int field_468_active;
  int field_46C_ticks;
  int field_470_ticks;
  int field_474_handle;
} CompatRenderStateTail;

static CompatRenderStateTail g_RenderStateTail;

static CompatRenderStateTail *Compat_RenderStateTailFields(int render_state)
{
  (void)render_state;
  return &g_RenderStateTail;
}

static int Compat_MenuProbeTraceEnabled(void)
{
  static int trace_state = -1;

  if ( trace_state == -1 )
  {
    const char *value = getenv("CLASH95_TRACE_RENDER_INPUT");
    trace_state = value && *value;
  }
  return trace_state;
}

static void Compat_MenuProbeTraceRenderInput(
        const char *phase,
        int render_state,
        int arg0,
        int arg1,
        int extra0,
        int extra1)
{
  static unsigned int trace_count;
  CompatRenderStateTail *tail;

  if ( !Compat_MenuProbeTraceEnabled() || trace_count >= 1024 )
    return;
  tail = Compat_RenderStateTailFields(render_state);
  fprintf(
    stderr,
    "[menu-input] phase=%s arg0=%d arg1=%d extra0=%d extra1=%d field468=%d flags=%u x=%d y=%d scale=%u deadline=%d\n",
    phase,
    arg0,
    arg1,
    extra0,
    extra1,
    tail->field_468_active,
    *(unsigned __int8 *)(render_state + 44),
    *(_DWORD *)(render_state + 36) >> *(_BYTE *)(render_state + 1108),
    *(_DWORD *)(render_state + 40) >> *(_BYTE *)(render_state + 1108),
    *(unsigned __int8 *)(render_state + 1108),
    g_RenderStateNextRefreshTick);
  fflush(stderr);
  ++trace_count;
}

//----- (00460410) --------------------------------------------------------
_DWORD * RenderState_ConstructDefault(int a1, int a2)
{
  int v2; // eax
  _DWORD *v3; // eax

  (void)a2;
  v2 = a1 + 80;
  *(_DWORD *)(v2 - 64) = 0;
  *(_DWORD *)(v2 - 60) = 0;
  *(_DWORD *)(v2 - 56) = 639;
  *(_DWORD *)(v2 - 52) = 479;
  *(_DWORD *)(v2 - 48) = 64;
  *(_DWORD *)(v2 - 16) = 0;
  v3 = (_DWORD *)(uintptr_t)(unsigned int)_wcpp_4_ctor_array__(v2, 256);
  v3[256] = 50;
  v3[257] = 6;
  v3[258] = 2;
  v3[259] = 5;
  v3[260] = g_RenderState_Vtable;
  return v3 - 20;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 50F1E4: using guessed type int (*off_50F1E4[6])();

//----- (00460490) --------------------------------------------------------
int  RenderState_InitCursorResources(int a1, int a2, char a3, DWORD a4)
{
  _DWORD *sprite_set;
  _DWORD *surface;

  g_CursorOverlayPresented = 0;
  *(_DWORD *)(a1 + 44) = 0;
  sprite_set = (_DWORD *)Mem_Alloc(4112, a2, a3, a4);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, "mouse.s32");
  *(_DWORD *)(a1 + 64) = sprite_set;
  surface = (_DWORD *)Mem_Alloc(188, 0, a3, a4);
  if ( surface )
  {
    a3 = 64;
    surface = Render_CreateSurface((int)surface, 64, 64);
  }
  *(_DWORD *)(a1 + 8) = surface;
  surface = (_DWORD *)Mem_Alloc(188, 0, a3, a4);
  if ( surface )
    surface = Render_CreateSurface((int)surface, 64, 64);
  *(_DWORD *)(a1 + 12) = surface;
  RenderState_SelectCursorDescriptor(a1, (int)(uintptr_t)g_RenderVideoInitCursorDescriptor);
  Compat_RenderStateInvokeMethod(a1, 20);
  *(_DWORD *)(a1 + 48) = (*(int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)(*(_DWORD *)(a1 + 60) + 20);
  *(_DWORD *)(a1 + 52) = (*(int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)(*(_DWORD *)(a1 + 60) + 24);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)a1, 0, 640, 0, 480);
  return LoadPalCOL(a1 + 80, (intptr_t)aMap_pal_1, a4);
}
// 544D10: using guessed type int dword_544D10;

//----- (00460580) --------------------------------------------------------
int  RenderState_ReleaseCursorResources(int a1)
{
  int surface_handle;
  int vtable;
  int (*release_proc)(int, int);

  DLXSpriteSet_ReleaseAndClear((int *)(a1 + 64));
  surface_handle = *(_DWORD *)(a1 + 8);
  if ( surface_handle )
  {
    vtable = *(_DWORD *)(surface_handle + 184);
    release_proc = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(vtable);
    release_proc(surface_handle, 2);
  }
  surface_handle = *(_DWORD *)(a1 + 12);
  if ( !surface_handle )
    return 0;
  vtable = *(_DWORD *)(surface_handle + 184);
  release_proc = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(vtable);
  release_proc(surface_handle, 2);
  return 0;
}

//----- (004605D0) --------------------------------------------------------
unsigned int  DD_Pump(int a1, int a2, ...)
{
  _DWORD *primary_surface;
  _DWORD *back_surface;
  _DWORD *cursor_descriptor;
  unsigned int message_pump_result;
  int v4; // edx
  int v5; // ecx
  unsigned int result; // eax
  int cursor_update_deadline;
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // edi
  int v13; // ebp
  int v14; // ebx
  unsigned int v15; // eax
  _DWORD *v17; // eax
  int v18; // ecx
  int v19; // ebp
  int v20; // eax
  int SpriteForChar; // eax
  void *v22; // [esp+1Ch] [ebp-18h]

  message_pump_result = Platform_PumpMessagesAndBlitFrame(a2);
  result = Time_Now(v5, v4);
  Compat_MenuProbeTraceRenderInput(
    "dd-pump",
    a1,
    message_pump_result,
    result,
    g_RenderStateNextRefreshTick,
    *(_DWORD *)(a1 + 1112));
  if ( result >= g_RenderStateNextRefreshTick || message_pump_result )
  {
    g_RenderStateNextRefreshTick = *(_DWORD *)(a1 + 1112) + Time_Now(v8, v7);
    Compat_RenderStateInvokeMethod(a1, 20);
    if ( g_DDPageFlipWasInProgressFlag && !DD_IsFlipping(a1) )
    {
      *(_DWORD *)(a1 + 68) = Time_Now(v10, v9);
      *(_DWORD *)(a1 + 72) = *(int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108);
      *(_DWORD *)(a1 + 76) = *(int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108);
    }
    g_DDPageFlipWasInProgressFlag = DD_IsFlipping(a1);
    Compat_RenderStateInvokeMethod(a1, 4);
    cursor_descriptor = Compat_RenderStateCursorDescriptor(a1);
    v12 = (int)cursor_descriptor;
    v13 = *(_DWORD *)(v12 + 8);
    v14 = 0;
    if ( v13 )
    {
      cursor_update_deadline = *(_DWORD *)(v12 + 28) + v13;
      v15 = Time_Now(cursor_update_deadline, v11);
      if ( (unsigned int)cursor_update_deadline < v15 )
      {
        *(_DWORD *)((char *)cursor_descriptor + 28) = Time_Now(v15, v11);
        ++*(_DWORD *)((char *)cursor_descriptor + 32);
        v17 = cursor_descriptor;
        if ( v17[1] - *v17 < v17[8] )
          v17[8] = 0;
        v14 = 1;
      }
    }
    *(_DWORD *)(a1 + 48) = (*(int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)((char *)cursor_descriptor + 20);
    v18 = (*(int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)((char *)cursor_descriptor + 24);
    *(_DWORD *)(a1 + 52) = v18;
    result = g_CursorOverlayPresented;
    if ( g_CursorOverlayPresented )
    {
      if ( message_pump_result
        || v14
        || (result = *(_DWORD *)(a1 + 48), result != *(_DWORD *)a1)
        || v18 != *(_DWORD *)(a1 + 4) )
      {
        v22 = g_RenderDevice;
        v19 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
        primary_surface = Compat_RenderStateSurface(a1, 8);
        back_surface = Compat_RenderStateSurface(a1, 12);
        if ( *(_DWORD *)a1 == *(_DWORD *)(a1 + 48) && *(_DWORD *)(a1 + 52) == *(_DWORD *)(a1 + 4) )
        {
          g_RenderDevice = (_UNKNOWN *)back_surface;
          Render_FillRect(
            primary_surface,
            back_surface,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            0,
            0);
          SpriteForChar = DLX_GetSpriteForChar(
                            *(_DWORD *)(a1 + 64),
                            *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
          (void)SpriteForChar;
          Render_FillRect(
            back_surface,
            0,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            *(_WORD *)a1,
            *(_WORD *)(a1 + 4));
        }
        else
        {
          g_RenderDevice = &g_MainRenderDevice;
          Render_FillRect(
            primary_surface,
            0,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            *(_WORD *)a1,
            *(_WORD *)(a1 + 4));
          Render_FillRect(
            0,
            primary_surface,
            *(unsigned __int16 *)(a1 + 52),
            *(unsigned __int16 *)(a1 + 48),
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) + *(_WORD *)(a1 + 48) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) + *(_WORD *)(a1 + 52) - 1,
            0,
            0);
          v20 = DLX_GetSpriteForChar(
                  *(_DWORD *)(a1 + 64),
                  *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
          (void)v20;
          *(_DWORD *)a1 = *(_DWORD *)(a1 + 48);
          *(_DWORD *)(a1 + 4) = *(_DWORD *)(a1 + 52);
        }
        g_RenderDevice = v22;
        return Render_SetResourceHandle((int)&g_MainRenderDevice, v19);
      }
    }
  }
  return result;
}
// 4605DF: variable 'v5' is possibly undefined
// 4605DF: variable 'v4' is possibly undefined
// 4605EE: variable 'v7' is possibly undefined
// 4605F4: variable 'v8' is possibly undefined
// 4607E8: variable 'v10' is possibly undefined
// 4607E8: variable 'v9' is possibly undefined
// 46065C: variable 'v11' is possibly undefined
// 460663: variable 'v16' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5448B0: using guessed type int dword_5448B0;
// 5448B4: using guessed type int dword_5448B4;
// 544D10: using guessed type int dword_544D10;

//----- (004608D0) --------------------------------------------------------
void  RenderState_SetMouseSpeed(int a1, int a2, DWORD a3)
{
  Debug_Log(a1, a2, a3, (int)aMouse_speedD);
  *(_DWORD *)(a1 + 32) = a2;
}

//----- (004608F0) --------------------------------------------------------
BOOL  DD_IsFlipping(int a1)
{
  return (*(_BYTE *)(a1 + 44) & 1) != 0;
}

//----- (00460900) --------------------------------------------------------
BOOL  DD_IsLost(int a1)
{
  return (*(_BYTE *)(a1 + 44) & 2) != 0;
}

//----- (00460910) --------------------------------------------------------
BOOL  Input_PollEventsUntil(int a1, char a2)
{
  int previous_poll_state;

  previous_poll_state = *(_DWORD *)(a1 + 56);
  *(_DWORD *)(a1 + 56) = 0;
  Platform_PumpMessagesAndBlitFrame(a2);
  *(_DWORD *)(a1 + 56) = previous_poll_state;
  InputBackend_PollState(&g_InputBackendState, a1, previous_poll_state);
  return g_InputMousePrimaryButtonState < 0 || g_InputMouseSecondaryButtonState < 0;
}
// 5451C0: using guessed type char byte_5451C0;
// 5451C8: using guessed type char byte_5451C8;

//----- (00460950) --------------------------------------------------------
BOOL  RenderState_IsCursorFlipStillActive(int a1)
{
  int v4; // eax
  int v6; // eax
  int v7; // eax

  if ( !DD_IsFlipping(a1) )
    return 0;
  v4 = Time_Now(0, 0);
  if ( (unsigned int)(v4 - *(_DWORD *)(a1 + 68)) >= *(_DWORD *)(a1 + 1104) )
    return 0;
  v6 = *(_DWORD *)(a1 + 72) - (*(int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108));
  if ( v6 <= 0 )
    v6 = (*(int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)(a1 + 72);
  if ( v6 >= *(_DWORD *)(a1 + 1116) )
    return 0;
  v7 = *(_DWORD *)(a1 + 76) - (*(int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108));
  if ( v7 <= 0 )
    v7 = (*(int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)(a1 + 76);
  return v7 < *(_DWORD *)(a1 + 1116);
}

//----- (004609D0) --------------------------------------------------------
BOOL  Render_Begin(int a1, void (*a2)(void), ...)
{
  BOOL result; // eax

  result = 0;
  while ( 1 )
  {
    if ( !DD_IsFlipping(a1) )
    {
      result = DD_IsLost(a1);
      if ( !result )
        break;
    }
    DD_Pump(a1, (char)a2);
    if ( a2 )
      a2();
  }
  return result;
}

//----- (00460A10) --------------------------------------------------------
BOOL  Render_FlipRect(int a1, char a2)
{
  int previous_poll_state;
  BOOL result; // eax

  result = 0;
  while ( 1 )
  {
    if ( !DD_IsFlipping(a1) )
    {
      result = DD_IsLost(a1);
      if ( !result )
        break;
    }
    previous_poll_state = *(_DWORD *)(a1 + 56);
    *(_DWORD *)(a1 + 56) = 0;
    Platform_PumpMessagesAndBlitFrame(a2);
    *(_DWORD *)(a1 + 56) = previous_poll_state;
    Compat_RenderStateInvokeMethod(a1, 20);
  }
  return result;
}

//----- (00460A50) --------------------------------------------------------
int  RenderState_PollInputAndClampCursor(int a1, int a2)
{
  _DWORD *v2; // edx
  int v3; // eax
  int v4; // edi
  int v5; // ecx
  int v6; // ebx
  int v7; // esi
  int result; // eax
  int v9; // edi

  v2 = (_DWORD *)(uintptr_t)(unsigned int)a1;
  InputBackend_PollState(&g_InputBackendState, a1, a2);
  Compat_MenuProbeTraceRenderInput(
    "live-input",
    a1,
    g_InputBackendState.mouse_delta_x,
    g_InputBackendState.mouse_delta_y,
    g_InputBackendState.mouse_button_primary,
    g_InputBackendState.mouse_button_secondary);
  v2[9] += v2[8] * g_InputBackendState.mouse_delta_x;
  v3 = v2[8] * g_InputBackendState.mouse_delta_y;
  v4 = v2[10];
  v2[11] = 0;
  v2[10] = v3 + v4;
  if ( g_InputMousePrimaryButtonState < 0 )
    ++v2[11];
  if ( g_InputMouseSecondaryButtonState < 0 )
    v2[11] += 2;
  v5 = v2[4];
  if ( v2[9] < v5 )
    v2[9] = v5;
  v6 = v2[5];
  if ( v2[10] < v6 )
    v2[10] = v6;
  v7 = v2[6];
  if ( v2[9] > v7 )
    v2[9] = v7;
  result = v2[10];
  v9 = v2[7];
  if ( result > v9 )
    v2[10] = v9;
  Compat_SyncRenderCursorGlobals(v2);
  return result;
}
// 460A66: variable 'v2' is possibly undefined
// 5451A8: using guessed type int dword_5451A8;
// 5451AC: using guessed type int dword_5451AC;
// 5451C0: using guessed type char byte_5451C0;
// 5451C8: using guessed type char byte_5451C8;

//----- (00460AF0) --------------------------------------------------------
unsigned int  RenderState_WarpCursorAndPump(_DWORD *a1, unsigned __int16 a2, unsigned __int16 a3)
{
  a1[9] = a2 << a1[277];
  a1[10] = a3 << a1[277];
  Compat_SyncRenderCursorGlobals(a1);
  return DD_Pump((int)a1, a3);
}

//----- (00460B20) --------------------------------------------------------
_DWORD * RenderState_RecalculateCursorBoundsForRect(
        _DWORD *result,
        __int16 a2,
        __int16 a3,
        __int16 a4,
        __int16 a5)
{
  _WORD *v6; // edx
  unsigned __int16 v7; // si
  unsigned __int16 v8; // bx
  unsigned __int16 v9; // di
  __int16 v10; // cx

  v6 = (_WORD *)result[15];
  v7 = v6[10] + 1 + a2;
  v8 = v6[12] + 1 + a4;
  v9 = a3 - (v6[6] - v6[10] + 1);
  v10 = v6[8];
  LOWORD(v6) = v6[12];
  result[4] = v7 << result[277];
  result[5] = v8 << result[277];
  result[6] = v9 << result[277];
  result[7] = (unsigned __int16)(a5 - (v10 - (_WORD)v6 + 1)) << result[277];
  return result;
}

//----- (00460BB0) --------------------------------------------------------
_DWORD * RenderState_PumpIfRectInViewBounds(
        _DWORD *result,
        unsigned __int16 a2,
        unsigned __int16 a3,
        unsigned __int16 a4,
        unsigned __int16 a5)
{
  int v6; // ebx

  v6 = result[15];
  if ( *(_DWORD *)(v6 + 12) + result[12] >= a2
    && a3 >= (int)result[12]
    && result[13] + *(_DWORD *)(v6 + 16) >= a4
    && a5 >= (int)result[13] )
  {
    return (_DWORD *)Render_Pump();
  }
  return result;
}

//----- (00460C70) --------------------------------------------------------
_DWORD * RenderState_LoadDefaultCursorSprite(int a1)
{
  _DWORD *result; // eax
  if ( *(_DWORD *)(a1 + 64) )
    DLXSpriteSet_ReleaseAndClear((int *)(a1 + 64));
  result = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, "mouse.s32");
    *(_DWORD *)(a1 + 64) = result;
  }
  else
  {
    *(_DWORD *)(a1 + 64) = 0;
  }
  return result;
}

//----- (00460CB0) --------------------------------------------------------
_DWORD * RenderState_LoadOrRenderCursorLabelSprite(int a1, int a2, int a3, DWORD a4)
{
  unsigned __int8 *source_bytes; // eax
  unsigned __int8 checksum_xor; // bl
  unsigned __int16 checksum_sum; // cx
  int i; // edx
  unsigned __int8 current_byte; // bh
  int cache_query_handle;
  _DWORD *result; // eax
  CHAR cache_path[104]; // [esp+0h] [ebp-78h] BYREF
  CHAR query_path[104]; // [esp+68h] [ebp-10h] BYREF

  if ( *(_DWORD *)(a1 + 64) )
    DLXSpriteSet_ReleaseAndClear((int *)(a1 + 64));
  source_bytes = (unsigned __int8 *)a2;
  checksum_xor = 0;
  checksum_sum = 0;
  for ( i = 0; i < 768; ++i )
  {
    current_byte = *source_bytes++;
    checksum_xor ^= current_byte;
    checksum_sum += current_byte;
  }
  sprintf_(cache_path, "cache\\m%02x%04x.s32", checksum_xor, checksum_sum);
  cache_query_handle = 0;
  if ( Res_ProbeGfxFileExists(cache_path, 0, a4, 0) )
  {
    strcpy(query_path, aGfx);
    strcat(query_path, cache_path);
    cache_query_handle = FileSystem_ResolveReadPath(query_path, 0);
    if ( cache_query_handle )
    {
      Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &cache_query_handle);
      result = (_DWORD *)Mem_Alloc(4112, 0, 0, a4);
      if ( result )
        result = DLXSpriteSet_Load(result, cache_path);
      *(_DWORD *)(a1 + 64) = result;
      return result;
    }
  }
  RenderState_LoadDefaultCursorSprite(a1);
  DLXSpriteSet_DrawText(*(_DWORD *)(a1 + 64), -1, a2, (unsigned __int8 *)(a1 + 80));
  result = *(_DWORD **)(a1 + 64);
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00460D80) --------------------------------------------------------
static uintptr_t Compat_RenderStateMethodPointer(int render_state, unsigned int table_offset)
{
  uintptr_t *vtable;

  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(render_state + 1120);
  if ( !vtable )
    return 0;
  return vtable[table_offset / 4];
}

static void Compat_RenderStateInvokeMethod(int render_state, unsigned int table_offset)
{
  uintptr_t method_ptr;

  method_ptr = Compat_RenderStateMethodPointer(render_state, table_offset);
  if ( method_ptr )
    ((void (*)(int))(uintptr_t)method_ptr)(render_state);
}

static _DWORD *Compat_RenderStateSurface(int render_state, unsigned int field_offset)
{
  return (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(render_state + field_offset);
}

static _DWORD *Compat_RenderStateCursorDescriptor(int render_state)
{
  unsigned int descriptor_handle;

  descriptor_handle = (unsigned int)*(_DWORD *)(render_state + 60);
  if ( !descriptor_handle )
  {
    descriptor_handle = (unsigned int)(uintptr_t)g_RenderVideoInitCursorDescriptor;
    *(_DWORD *)(render_state + 60) = descriptor_handle;
  }
  return (_DWORD *)(uintptr_t)descriptor_handle;
}

static void Compat_PresentPrimaryIndexedSurfaceToPlatform(void)
{
  unsigned int primary_surface_handle;

  primary_surface_handle = (unsigned int)*(_DWORD *)((unsigned char *)&g_MainRenderDevice + 0xD0);
  if ( primary_surface_handle )
  {
    Platform_PresentRecoveredIndexedSurfaceHandle(
      (void *)(uintptr_t)primary_surface_handle,
      (const uint32_t *)(const void *)((unsigned char *)&g_MainRenderDevice + 220));
  }
}

static int Compat_RenderClearPresentedRect(int render_state)
{
  _DWORD *present_surface;
  _DWORD *cursor_descriptor;
  int resource_handle;

  if ( !g_CursorOverlayPresented )
    return g_CursorOverlayPresented;
  g_CursorOverlayPresented = 0;
  resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  present_surface = Compat_RenderStateSurface(render_state, 8);
  cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
  Render_FillRect(
    present_surface,
    0,
    0,
    0,
    *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
    *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
    *(unsigned __int16 *)render_state,
    *(unsigned __int16 *)(render_state + 4));
  return Render_SetResourceHandle((int)&g_MainRenderDevice, resource_handle);
}

__int16  RenderState_SelectCursorDescriptor(int a1, int a2)
{
  int descriptor;
  int result;
  int active_descriptor;
  unsigned int sprite_index;
  unsigned __int16 max_height;
  unsigned __int16 max_width;
  unsigned __int16 sprite_height;
  unsigned __int16 sprite_width;
  unsigned char was_presenting;

  result = a1;
  active_descriptor = a2;
  if ( !active_descriptor )
    active_descriptor = *(_DWORD *)(a1 + 60);
  if ( active_descriptor )
    g_ActiveCursorDescriptorPtr = active_descriptor;
  if ( a2 == *(_DWORD *)(a1 + 60) )
    return result;
  was_presenting = (unsigned char)g_CursorOverlayPresented;
  if ( was_presenting )
    Compat_RenderClearPresentedRect(a1);
  *(_DWORD *)(a1 + 60) = a2;
  descriptor = *(_DWORD *)(a1 + 60);
  max_height = 0;
  max_width = 0;
  for ( sprite_index = *(unsigned __int16 *)descriptor; sprite_index <= (unsigned int)*(int *)(descriptor + 4); ++sprite_index )
  {
    sprite_height = DLX_GetSpriteHeight(*(_DWORD *)(a1 + 64), (int)sprite_index);
    sprite_width = DLX_GetSpriteWidth(*(_DWORD *)(a1 + 64), (int)sprite_index);
    if ( sprite_height > max_height )
      max_height = sprite_height;
    if ( sprite_width > max_width )
      max_width = sprite_width;
  }
  *(_DWORD *)(descriptor + 12) = max_height;
  *(_DWORD *)(descriptor + 16) = max_width;
  *(_DWORD *)(descriptor + 32) = 0;
  *(_DWORD *)(descriptor + 28) = 0;
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)a1, 0, 640, 0, 480);
  Compat_RenderStateInvokeMethod(a1, 20);
  Compat_RenderStateInvokeMethod(a1, 4);
  *(_DWORD *)(a1 + 48) = (*(int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)(descriptor + 20);
  *(_DWORD *)(a1 + 52) = (*(int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108)) - *(_DWORD *)(descriptor + 24);
  if ( was_presenting )
    result = Render_Present(a1);
  return result;
}
// 544D10: using guessed type int dword_544D10;

//----- (00460EA0) --------------------------------------------------------
int  Render_Present(int a1)
{
  _DWORD *cursor_descriptor;
  _DWORD *present_surface;
  int result; // eax
  int v3; // edi
  int SpriteForChar; // eax
  void *v5; // [esp+1Ch] [ebp-Ch]

  present_surface = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 8);
  cursor_descriptor = Compat_RenderStateCursorDescriptor(a1);
  result = g_CursorOverlayPresented;
  if ( !g_CursorOverlayPresented )
  {
    v3 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
    g_CursorOverlayPresented = 1;
    v5 = g_RenderDevice;
    Render_FillRect(
      0,
      present_surface,
      *(unsigned __int16 *)(a1 + 52),
      *(unsigned __int16 *)(a1 + 48),
      *(unsigned __int16 *)((char *)cursor_descriptor + 12) + *(_WORD *)(a1 + 48) - 1,
      *(unsigned __int16 *)((char *)cursor_descriptor + 16) + *(_WORD *)(a1 + 52) - 1,
      0,
      0);
    g_RenderDevice = &g_MainRenderDevice;
    SpriteForChar = DLX_GetSpriteForChar(
                      *(_DWORD *)(a1 + 64),
                      *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
    (void)SpriteForChar;
    *(_DWORD *)a1 = *(_DWORD *)(a1 + 48);
    *(_DWORD *)(a1 + 4) = *(_DWORD *)(a1 + 52);
    g_RenderDevice = v5;
    result = Render_SetResourceHandle((int)&g_MainRenderDevice, v3);
    Compat_PresentPrimaryIndexedSurfaceToPlatform();
    return result;
  }
  Compat_PresentPrimaryIndexedSurfaceToPlatform();
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544D10: using guessed type int dword_544D10;

//----- (00460F90) --------------------------------------------------------
int Render_Pump()
{
  _DWORD *cursor_descriptor;
  _DWORD *present_surface;
  int result; // eax
  int render_state;
  int v1; // esi

  result = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
  {
    g_CursorOverlayPresented = 0;
    v1 = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
    render_state = (int)g_RenderState;
    present_surface = Compat_RenderStateSurface(render_state, 8);
    cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
    Render_FillRect(
      present_surface,
      0,
      0,
      0,
      *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
      *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
      *(_WORD *)render_state,
      *(_WORD *)(render_state + 4));
    return Render_SetResourceHandle((int)&g_MainRenderDevice, v1);
  }
  return result;
}
// 544D10: using guessed type int dword_544D10;

//----- (00461000) --------------------------------------------------------
void Input_Flush()
{
  g_CursorOverlayPresented = 0;
}
// 544D10: using guessed type int dword_544D10;

//----- (004610B0) --------------------------------------------------------
int  RenderState_DrawCursorSpriteToPrimarySurface(int a1)
{
  void *v2; // esi
  int SpriteForChar; // eax
  int result; // eax

  v2 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, &g_CursorSpritePalette);
  SpriteForChar = DLX_GetSpriteForChar(*(_DWORD *)(a1 + 64), g_CursorDesc_Busy[0] + 1);
  result = Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  g_RenderDevice = v2;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519808: using guessed type int dword_519808;

//----- (00461140) --------------------------------------------------------
_DWORD * Device_GetParamA(int a1, int a2)
{
  _DWORD *result; // eax
  CompatRenderStateTail *tail;

  result = RenderState_ConstructDefault(a1, a2);
  result[280] = g_Device_Vtable;
  tail = Compat_RenderStateTailFields(a1);
  tail->field_464_active = 0;
  tail->field_468_active = 0;
  tail->field_46C_ticks = 0;
  tail->field_470_ticks = 0;
  tail->field_474_handle = 0;
  Compat_SyncRenderCursorGlobals(result);
  return result;
}
// 50F204: using guessed type int (*off_50F204[6])();

//----- (00461170) --------------------------------------------------------
int  Device_DoOp(int a1, int a2, DWORD a3)
{
  CompatRenderStateTail *tail;
  int record_handle;

  (void)a2;
  tail = Compat_RenderStateTailFields(a1);
  tail->field_464_active = 1;
  tail->field_46C_ticks = Time_Now(0, 0);
  record_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aWb_7, 0, a3);
  return fclose_(record_handle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004611A0) --------------------------------------------------------
__int16  Device_GetParamB(int a1, DWORD a2, int a3, int a4)
{
  CompatRenderStateTail *tail;
  unsigned int current_x;
  unsigned int current_y;
  int current_flags;
  _DWORD elapsed_ticks;
  int record_handle;

  (void)a3;
  (void)a4;
  tail = Compat_RenderStateTailFields(a1);
  if ( tail->field_464_active )
  {
    current_flags = *(_DWORD *)(a1 + 44);
    current_x = *(unsigned int *)(a1 + 36) >> *(_BYTE *)(a1 + 1108);
    current_y = *(unsigned int *)(a1 + 40) >> *(_BYTE *)(a1 + 1108);
    if ( (unsigned __int8)g_DeviceRecordLastFlipLostState != current_flags
      || current_x != (unsigned __int16)g_DeviceRecordLastX
      || current_y != (unsigned __int16)g_DeviceRecordLastY )
    {
      g_DeviceRecordLastX = *(_WORD *)(a1 + 36);
      g_DeviceRecordLastY = *(_WORD *)(a1 + 40);
      g_DeviceRecordLastFlipLostState = (unsigned char)(2 * (DD_IsFlipping(a1) + DD_IsLost(a1)));
      elapsed_ticks = Time_Now(0, 0) - tail->field_46C_ticks;
      record_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aAb, 1, a2);
      fwrite_(&g_DeviceRecordLastX, 2, record_handle, 1);
      fwrite_(&g_DeviceRecordLastY, 2, record_handle, 1);
      fwrite_(&g_DeviceRecordLastFlipLostState, 1, record_handle, 1);
      fwrite_(&elapsed_ticks, 4, record_handle, 1);
      return fclose_(record_handle);
    }
  }
  return 0;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 544CBA: using guessed type __int16 word_544CBA;
// 544CBC: using guessed type __int16 word_544CBC;
// 544CBE: using guessed type char byte_544CBE;

//----- (004612A0) --------------------------------------------------------
int  Device_SetParamA(int a1, DWORD a2)
{
  CompatRenderStateTail *tail;

  tail = Compat_RenderStateTailFields(a1);
  tail->field_468_active = 1;
  tail->field_470_ticks = Time_Now(0, 0);
  tail->field_474_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aRb_9, 0, a2);
  return tail->field_474_handle;
}

//----- (004612E0) --------------------------------------------------------
int  Device_UpdateRect(_DWORD *a1, int a2, int a3)
{
  CompatRenderStateTail *tail;
  int v4; // eax
  char v5; // bl
  int v6; // ecx
  unsigned int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int result; // eax
  int v12; // edi
  unsigned int v13; // ecx

  tail = Compat_RenderStateTailFields((int)a1);
  Compat_MenuProbeTraceRenderInput(
    "device-update",
    (int)a1,
    a2,
    a3,
    tail->field_470_ticks,
    tail->field_474_handle);
  if ( !tail->field_468_active )
    return RenderState_PollInputAndClampCursor((int)a1, a3);
  v4 = Time_Now(a3, a2);
  v5 = g_DeviceRectTweenTimeBase;
  v6 = tail->field_470_ticks;
  v7 = v4 - v6 - g_DeviceRectTweenTimeBase;
  if ( v7 < g_DeviceReplaySegmentTargetTick - g_DeviceReplaySegmentBaseTick )
  {
    v13 = ((Time_Now(v6, v7) - tail->field_470_ticks - g_DeviceRectTweenTimeBase) << 8)
        / (unsigned int)(g_DeviceReplaySegmentTargetTick - g_DeviceReplaySegmentBaseTick);
    a1[9] = (unsigned __int16)g_DeviceRectLastWidth
          + ((int)(v13 * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)
                 - (__CFSHL__((int)(v13 * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)) >> 31, 8)
                  + ((int)(v13 * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)) >> 31 << 8))) >> 8);
    result = (unsigned __int16)g_RenderCursor_TweenPrevY
           + ((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * v13
                  - (__CFSHL__((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * v13) >> 31, 8)
                   + ((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * v13) >> 31 << 8))) >> 8);
    a1[10] = result;
    Compat_SyncRenderCursorGlobals(a1);
  }
  else
  {
    g_DeviceRectTweenTimeBase = Time_Now(v6, v7) - tail->field_470_ticks;
    g_DeviceReplaySegmentBaseTick = g_DeviceReplaySegmentTargetTick;
    g_DeviceRectLastWidth = g_DeviceRectTargetWidth;
    g_RenderCursor_TweenPrevY = g_DeviceRectTargetHeight;
    a1[9] = (unsigned __int16)g_DeviceRectTargetWidth;
    a1[10] = (unsigned __int16)g_DeviceRectTargetHeight;
    Compat_SyncRenderCursorGlobals(a1);
    v8 = tail->field_474_handle;
    a1[11] = (unsigned __int8)g_DemoPlaybackCursorButtonState;
    if ( (*(_BYTE *)(v8 + 12) & 0x10) == 0 )
    {
      fread_();
      fread_();
      fread_();
      v5 = 1;
      fread_();
    }
    v9 = 0;
    v10 = 0;
    if ( g_DemoScript_TriggerTickTable[0] != -1 )
    {
      while ( g_DemoScriptCurrentTick != g_DemoScript_TriggerTickTable[v10] )
      {
        v12 = g_DemoScript_MessageIdTable[v10++];
        ++v9;
        if ( v12 == -1 )
          goto LABEL_8;
      }
      Demo_ShowNumberedTextScreen(v5, g_DemoScriptCurrentTick);
    }
LABEL_8:
    result = Input_IsKeyPressed(1);
    if ( result )
      App_RequestQuit((int)&g_App_QuitReason_DemoSkipKey);
    ++g_DemoScriptCurrentTick;
  }
  return result;
}
// 519620: using guessed type __int16 word_519620;
// 519622: using guessed type __int16 word_519622;
// 519624: using guessed type __int16 word_519624;
// 519626: using guessed type __int16 word_519626;
// 519628: using guessed type int dword_519628[];
// 51962C: using guessed type int dword_51962C[];
// 544CC0: using guessed type int dword_544CC0;
// 544CC4: using guessed type int dword_544CC4;
// 544CC8: using guessed type int dword_544CC8;
// 544CCC: using guessed type char byte_544CCC;
// 544CD0: using guessed type int dword_544CD0;

