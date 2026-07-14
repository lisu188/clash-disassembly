/* Clash strategic rules integration, host functions, campaign, and AI.
 * Original function-marker range: 0x004506B0..0x004612E0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004506B0) --------------------------------------------------------
int  Queen_FindEligibleBirthHostBuilding(int player_index)
{
  int building_index; // eax
  int building_record; // ebx
  int building_type; // ecx

  building_index = 0;
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(building_record + 4) < 4 && *(__int16 *)(building_record + 16) != -1 )
  {
    building_type = *(char *)(gameData + BUILDING_RECORD_SIZE * building_index + 509678);
    if ( (building_type == 2 || building_type == 1) && *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building_index + 509676) == player_index )
      return UNIT_RECORD(building_index);
  }
  while ( ++building_index < 100 )
  {
    if ( building_index >= 0 )
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
  char *dest; // edi
  char *src; // esi
  char ch; // al
  char next_ch; // al
  unsigned int message_len; // kr04_4
  __int16 v12; // ax
  int v13; // ecx
  __int16 v14; // bx
  int proposal_accepted; // eax
  int player_offset; // edx
  int v17; // ecx
  __int16 v18; // ax
  int v19; // ecx
  __int16 v20; // dx
  int host_building; // eax
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  signed int theft_castle_index; // eax
  int theft_castle_offset; // eax
  int v28; // edx
  int v29; // ecx
  signed int poison_castle_index; // eax
  int poison_castle_offset; // edx
  int poison_castle_record; // eax
  char plague_state_byte; // bh
  int v34; // edx
  int v35; // ecx
  signed int arson_castle_index; // eax
  int v37; // edx
  unsigned int whim_index; // eax
  int available_funds; // eax
  int v40; // ecx
  int v41; // ecx
  int player_record_accepted; // eax
  int player_record_declined; // eax
  int castle_name_ptr; // [esp-4h] [ebp-1Ch]
  int son_birth_texts[3]; // [esp+0h] [ebp-18h]
  int daughter_birth_texts[3]; // [esp+Ch] [ebp-Ch]
  _DWORD savedregs[6]; // [esp+18h] [ebp+0h] BYREF

  result = gameData;
  if ( ACTIVE_MISSION_INDEX != 6 )
  {
    Debug_Log(a1, a2, (DWORD)savedregs, (int)aQueen_newturn, son_birth_texts[0]);
    result = PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex);
    if ( result != -1 )
    {
      if ( PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) )
      {
        if ( result == QUEEN_RELATIONSHIP_STATE_CHILDBIRTH_PENDING )
        {
          Debug_Log(g_CurrentPlayerIndex, a2, (DWORD)savedregs, (int)aQueen_newturnN, son_birth_texts[0]);
          a2 = (char)((Rng_RandRange(0, 100) <= 0x32) + 33);
          host_building = Queen_FindEligibleBirthHostBuilding(g_CurrentPlayerIndex);
          if ( host_building )
          {
            Building_CreateSpecialPersonageGarrisonUnit(host_building, a2, host_building, a2, a4);
            PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) = 5;
            if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
            {
              son_birth_texts[0] = (int)g_QueenSonBirthTexts[0];
              son_birth_texts[1] = (int)g_QueenSonBirthTexts[1];
              son_birth_texts[2] = (int)g_QueenSonBirthTexts[2];
              castle_name_ptr = host_building + 5;
              daughter_birth_texts[0] = (int)g_QueenDaughterBirthTexts[0];
              daughter_birth_texts[1] = (int)g_QueenDaughterBirthTexts[1];
              daughter_birth_texts[2] = (int)g_QueenDaughterBirthTexts[2];
              if ( a2 == 33 )
                sprintf_(&g_QueenBirthMessageBuffer, (const char *)son_birth_texts[(unsigned __int8)g_LanguageIndex], castle_name_ptr);
              else
                sprintf_(&g_QueenBirthMessageBuffer, (const char *)daughter_birth_texts[(unsigned __int8)g_LanguageIndex], castle_name_ptr);
              UI_ShowInfoWindow((const char *)&g_QueenBirthMessageBuffer, 0, v23, (DWORD)savedregs, (int)savedregs, (int)&g_QueenDaughterBirthTexts[3]);
            }
          }
        }
        else if ( result == 1 )
        {
          Debug_Log(g_CurrentPlayerIndex, a2, (DWORD)savedregs, (int)aQueen_newturnK, son_birth_texts[0]);
          PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) = -1;
          switch ( Rng_RandRange(0, 3) )
          {
            case 0u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_0, 0);
              dest = g_QueenDepartureEventMessageBuffer;
              src = g_QueenDepartureTexts[(unsigned __int8)g_LanguageIndex];
              do
              {
                ch = *src;
                *dest = *src;
                if ( !ch )
                  break;
                next_ch = src[1];
                src += 2;
                dest[1] = next_ch;
                dest += 2;
              }
              while ( next_ch );
              break;
            case 1u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_1, 1);
              theft_castle_index = Unit_FindById(g_CurrentPlayerIndex);
              if ( theft_castle_index != -1 )
              {
                theft_castle_offset = BUILDING_RECORD_SIZE * theft_castle_index;
                *(_DWORD *)(gameData + theft_castle_offset + 510112) = 0;
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleTreasuryTheftTexts[(unsigned __int8)g_LanguageIndex],
                  gameData + BUILDING_TABLE_OFFSET + theft_castle_offset + 5);
              }
              break;
            case 2u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_2, 2);
              poison_castle_index = Unit_FindById(g_CurrentPlayerIndex);
              if ( poison_castle_index != -1 )
              {
                poison_castle_offset = BUILDING_RECORD_SIZE * poison_castle_index;
                poison_castle_record = gameData + BUILDING_RECORD_SIZE * poison_castle_index;
                plague_state_byte = *(_BYTE *)(poison_castle_record + 510109) & 0xF8;
                *(_BYTE *)(poison_castle_record + 510109) = plague_state_byte;
                *(_BYTE *)(poison_castle_record + 510109) = plague_state_byte | 5;
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleWellPoisoningTexts[(unsigned __int8)g_LanguageIndex],
                  poison_castle_offset + gameData + BUILDING_TABLE_OFFSET + 5);
              }
              break;
            case 3u:
              Debug_Log(v6, a2, (DWORD)savedregs, (int)aQueen_newtur_3, 3);
              arson_castle_index = Unit_FindById(g_CurrentPlayerIndex);
              if ( arson_castle_index != -1 )
              {
                Building_Destroy(UNIT_RECORD(arson_castle_index), a2, (DWORD)savedregs, a4);
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleArsonTexts[(unsigned __int8)g_LanguageIndex],
                  UNIT_RECORD(arson_castle_index) + 5);
              }
              break;
            default:
              break;
          }
          message_len = strlen(g_QueenDepartureEventMessageBuffer) + 1;
          if ( message_len != 1 )
            Queen_ShowMessageDialog((int)g_QueenDepartureEventMessageBuffer, message_len - 1, a2, (DWORD)savedregs);
        }
        result = PLAYER_DATA(g_CurrentPlayerIndex);
        if ( GAME_TURN_COUNTER >= *(_WORD *)(result + 141445) )
        {
          if ( *(_DWORD *)(result + 140051) )
          {
            whim_index = Rng_RandRange(0, 24);
            Debug_Log(whim_index, a2, (DWORD)savedregs, (int)aQueen_newturnZ, whim_index);
            available_funds = Player_CalcAvailableStrongholdFunds(g_CurrentPlayerIndex);
            if ( Queen_ShowWhimDecisionDialog(
                   g_QueenWhimRecords[whim_index].texts[(unsigned __int8)g_LanguageIndex],
                   g_QueenWhimRecords[whim_index].required_stronghold_funds,
                   7 * whim_index,
                   available_funds,
                   (DWORD)savedregs) )
            {
              Player_SpendStrongholdFundsEvenly(g_CurrentPlayerIndex, g_QueenWhimRecords[whim_index].required_stronghold_funds);
              player_record_accepted = PLAYER_DATA(g_CurrentPlayerIndex);
              if ( *(char *)(player_record_accepted + 141443) < 9 )
                ++*(_BYTE *)(player_record_accepted + 141443);
            }
            else
            {
              player_record_declined = PLAYER_DATA(g_CurrentPlayerIndex);
              if ( *(char *)(player_record_declined + 141443) > 1 )
                --*(_BYTE *)(player_record_declined + 141443);
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
          proposal_accepted = 1;
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
            proposal_accepted = Queen_ShowMarriageProposalDialog(0, a2, (DWORD)savedregs);
            Diagnostics_TraceWorldMapActionEvent(
              "queen_proposal_dialog_return",
              g_SelectedUnitIndex,
              proposal_accepted,
              ACTIVE_MISSION_INDEX,
              GAME_TURN_COUNTER);
          }
          player_offset = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
          if ( proposal_accepted )
          {
            *(_BYTE *)(player_offset + gameData + 141443) = 5;
            result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
            PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN(g_CurrentPlayerIndex) = GAME_TURN_COUNTER + Rng_RandRange(5, 8);
          }
          else
          {
            result = gameData;
            *(_BYTE *)(player_offset + gameData + 141443) = -1;
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
int  Player_Surrender(int player_index, int a2, DWORD a3, double a4)
{
  int building_index; // edx
  int building_record; // eax
  int stack_index; // edx
  int result; // eax

  Debug_Log(a2, player_index, a3, (int)aPlayer_surrend);
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(building_record + 4) < 4
    && *(__int16 *)(building_record + 16) != -1
    && *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building_index + 509676) == player_index )
  {
    Building_Destroy(UNIT_RECORD(building_index), player_index, a3, a4);
  }
  while ( ++building_index < 100 )
  {
    if ( building_index >= 0 )
      goto LABEL_2;
  }
  stack_index = 0;
LABEL_10:
  if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28
    && *(unsigned __int8 *)(UNIT_STACK_STRIDE * stack_index + gameData + 147178) == player_index )
  {
    UnitStack_KillByIndex(stack_index, player_index, a3, a4);
  }
  while ( ++stack_index < 500 )
  {
    if ( stack_index >= 0 )
      goto LABEL_10;
  }
  result = gameData;
  *(_DWORD *)(PLAYER_DATA_STRIDE * player_index + gameData + PLAYER_RUNTIME_STATE_OFFSET) = 0;
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
        signed int player_index,
        int a2,
        DWORD a3,
        double a4)
{
  signed int nation; // ecx
  int result; // eax
  int building_record; // edx
  int building_offset; // edx
  int stack_index; // edx
  int max_strength; // ebx
  signed int i; // edx
  int strength; // eax
  int v12; // ecx
  int v13; // ecx
  int human_ally_alive; // edx
  int player_record; // ebx
  const char *notice_format; // edi
  int v17; // ecx
  _BYTE message_buffer[200]; // [esp+0h] [ebp-E4h] BYREF
  int notice_texts[7]; // [esp+C8h] [ebp-1Ch]

  notice_texts[5] = a2;
  nation = player_index;
  result = 0;
LABEL_2:
  building_record = UNIT_RECORD(result);
  if ( (unsigned int)*(char *)(building_record + 4) >= 4
    || *(__int16 *)(building_record + 16) == -1
    || (building_offset = gameData + BUILDING_RECORD_SIZE * result, !*(_BYTE *)(building_offset + 509678))
    || *(unsigned __int8 *)(building_offset + 509676) != nation )
  {
    while ( ++result < 100 )
    {
      if ( result >= 0 )
        goto LABEL_2;
    }
    stack_index = 0;
LABEL_10:
    if ( (unsigned int)*(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 6) > 0x28
      || *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147178) != nation
      || (result = UnitStack_HasBuilder(stack_index)) == 0 )
    {
      while ( ++stack_index < 500 )
      {
        if ( stack_index >= 0 )
          goto LABEL_10;
      }
      max_strength = 0;
      for ( i = 0; i < 5; ++i )
      {
        if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * i + PLAYER_RUNTIME_STATE_OFFSET) )
        {
          strength = Player_CalcMilitaryStrength(i);
          if ( strength > max_strength )
            max_strength = strength;
        }
      }
      result = 100 * Player_CalcMilitaryStrength(nation) / max_strength;
      if ( result < 10 )
      {
        Player_Surrender(v12, v12, a3, a4);
        human_ally_alive = 0;
        for ( result = 0; result < 5; ++result )
        {
          player_record = gameData + PLAYER_DATA_STRIDE * result;
          if ( *(_DWORD *)(player_record + 140051) && *(_DWORD *)(player_record + 140024) )
            human_ally_alive = 1;
        }
        if ( human_ally_alive )
        {
          notice_texts[0] = (int)g_AllyEliminatedNoticeTexts[0];
          notice_texts[1] = (int)g_AllyEliminatedNoticeTexts[1];
          notice_texts[2] = (int)g_AllyEliminatedNoticeTexts[2];
          notice_format = (const char *)notice_texts[(unsigned __int8)g_LanguageIndex];
          sprintf_(message_buffer, notice_format, PLAYER_DATA_STRIDE * v13 + gameData + PLAYER_RUNTIME_STATE_OFFSET + 4);
          return UI_ShowInfoWindow((const char *)message_buffer, 0, v17, a3, (int)notice_format, (int)&g_AllyEliminatedNoticeTexts[3]);
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
int  Player_CheckForDefeatAndHandleElimination(int player_index, DWORD a2)
{
  int stack_index; // edx
  int owner_index; // eax
  int building_index; // edx
  int building_record; // eax
  int survivor_index; // eax
  int survivor_record; // edx

  stack_index = 0;
LABEL_2:
  if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28 )
  {
    owner_index = *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147178);
    if ( owner_index == player_index )
      return player_index ^ owner_index;
  }
  while ( ++stack_index < 500 )
  {
    if ( stack_index >= 0 )
      goto LABEL_2;
  }
  building_index = 0;
LABEL_9:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(building_record + 4) < 4
    && *(__int16 *)(building_record + 16) != -1
    && (*(_BYTE *)(gameData + BUILDING_RECORD_SIZE * building_index + 509678) || Building_CountGarrison(UNIT_RECORD(building_index))) )
  {
    owner_index = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building_index + 509676);
    if ( owner_index == player_index )
      return player_index ^ owner_index;
  }
  while ( ++building_index < 100 )
  {
    if ( building_index >= 0 )
      goto LABEL_9;
  }
  *(_DWORD *)(PLAYER_DATA_STRIDE * player_index + gameData + PLAYER_RUNTIME_STATE_OFFSET) = 0;
  Render_Pump();
  Audio_StopMainMusic();
  Video_PlayAviWithModeGuard((int)aArama1, aKon_por1);
  survivor_index = 0;
  while ( 1 )
  {
    survivor_record = gameData + PLAYER_DATA_STRIDE * survivor_index;
    if ( *(_DWORD *)(survivor_record + 140024) )
    {
      if ( *(_DWORD *)(survivor_record + 140051) )
        break;
    }
    if ( ++survivor_index >= 5 )
      return 1;
  }
  Music_PlayMainMapTrack(*(unsigned __int8 *)(gameData + MAP_THEME_INDEX_OFFSET), survivor_record, gameData, a2);
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
signed int  Player_CheckSoleSurvivorAndShowVictoryBanner(int player_index)
{
  int player_offset; // eax
  int own_player_offset; // ecx
  signed int v4; // edx
  int v5; // ecx

  player_offset = 0;
  own_player_offset = PLAYER_DATA_STRIDE * player_index;
  while ( !*(_DWORD *)(gameData + player_offset + PLAYER_RUNTIME_STATE_OFFSET) || player_offset == own_player_offset )
  {
    player_offset += PLAYER_DATA_STRIDE;
    if ( player_offset >= 7115 )
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

signed int UI_CheckEndTurnHotkey(int player_index)
{
  return Player_CheckSoleSurvivorAndShowVictoryBanner(player_index);
}
// 45119B: variable 'v4' is possibly undefined
// 4511BB: variable 'v5' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 51D578: using guessed type int dword_51D578;
// 5202E4: using guessed type int gameData;

//----- (004511D0) --------------------------------------------------------
void  Options_ApplyInGameSliders(int a1, DWORD resource_handle)
{
  *(_BYTE *)(gameData + 147173) = ((unsigned __int16)(((_WORD)g_OptionsInGameMusicVolumeRaw << 7)
                                                    - (__CFSHL__(g_OptionsInGameMusicVolumeRaw << 7 >> 31, 8)
                                                     + ((unsigned __int16)(g_OptionsInGameMusicVolumeRaw << 7 >> 31) << 8))) >> 8)
                                - 64;
  *(_BYTE *)(gameData + 147172) = (unsigned __int16)(16 * g_OptionsInGameSoundVolumeRaw
                                                   - (__CFSHL__((16 * g_OptionsInGameSoundVolumeRaw) >> 31, 8)
                                                    + ((unsigned __int16)((16 * g_OptionsInGameSoundVolumeRaw) >> 31) << 8))) >> 8;
  Options_ApplyRecordSettings(gameData + 147147, a1, resource_handle);
}
// 51938C: using guessed type int dword_51938C;
// 5193D4: using guessed type int dword_5193D4;
// 5202E4: using guessed type int gameData;

//----- (00451230) --------------------------------------------------------
int  Options_HandleCloseButtonInGame(int widget)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(widget);
  g_InGameOptionsDialogExitSignal = v3;
  return result;
}
// 45123B: variable 'v3' is possibly undefined
// 54453C: using guessed type int dword_54453C;

//----- (00451250) --------------------------------------------------------
unsigned __int16 * Options_InitInGameSlidersAndWidgets(int widget, int a2, DWORD resource_handle)
{
  int widget_base; // ecx

  UIWidget_PlayPressedReleaseAnimation(widget);
  if ( (*(_BYTE *)(widget_base - 98) & 2) == 0 )
  {
    *(_DWORD *)(widget_base - 98) = 2;
    UIWidget_RefreshActionButtonState(widget_base - 106, widget_base);
  }
  if ( (*(_BYTE *)(widget_base - 151) & 2) == 0 )
  {
    *(_DWORD *)(widget_base - 151) = 2;
    UIWidget_RefreshActionButtonState(widget_base - 159, widget_base);
  }
  if ( (*(_BYTE *)(widget_base - 204) & 2) == 0 )
  {
    *(_DWORD *)(widget_base - 204) = 2;
    UIWidget_RefreshActionButtonState(widget_base - 212, widget_base);
  }
  if ( (*(_BYTE *)(widget_base - 257) & 1) == 0 )
  {
    *(_DWORD *)(widget_base - 257) = 1;
    UIWidget_RefreshActionButtonState(widget_base - 265, widget_base);
  }
  g_OptionsInGameMusicVolumeRaw = 128;
  g_OptionsInGameScrollSpeedRaw = 128;
  g_OptionsInGameSoundVolumeRaw = 128;
  return Options_DrawAllSliderThumbs(g_InGameSliderThumbPositions, a2, resource_handle);
}
// 451259: variable 'v4' is possibly undefined
// 519380: using guessed type unsigned __int16 word_519380[6];
// 51938C: using guessed type int dword_51938C;
// 5193B0: using guessed type int dword_5193B0;
// 5193D4: using guessed type int dword_5193D4;

//----- (00451310) --------------------------------------------------------
BOOL  Options_ToggleCheckboxInGame(int widget)
{
  char checkbox_state; // dl

  checkbox_state = *(_BYTE *)(widget + 8) ^ 1;
  *(_BYTE *)(widget + 8) = checkbox_state;
  *(_BYTE *)(widget + 8) = checkbox_state ^ 2;
  Audio_PlayButtonSound(*(char **)(widget + 49));
  return Render_Begin((int)g_RenderState, 0);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00451340) --------------------------------------------------------
int  Options_RunInGameSettingsDialog(int a1, char a2, DWORD a3)
{
  _DWORD *sprite_set; // eax
  int prev_resource_handle; // ebp
  int field_offset; // eax
  int v7; // ecx
  char *copy_dest; // edi
  char *copy_src; // esi
  int button_text; // ebx
  int music_volume_raw; // eax
  int SpriteForChar; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  _BYTE v17[29]; // [esp+1h] [ebp-1B1h]
  int ( *render_hook_fn)(int, char, DWORD); // [esp+1Eh] [ebp-194h]
  char widget_table[8]; // [esp+22h] [ebp-190h] BYREF
  int v20; // [esp+2Ah] [ebp-188h]
  _DWORD widget_text_ptrs[11]; // [esp+32h] [ebp-180h]
  int v22; // [esp+5Fh] [ebp-153h]
  int v23; // [esp+94h] [ebp-11Eh]
  int v24; // [esp+C9h] [ebp-E9h]
  int (*prev_render_hook)(); // [esp+196h] [ebp-1Ch]

  sprite_set = (_DWORD *)Mem_Alloc(4112, a1, a2, a3);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, a2);
  g_InGameOptionsSpriteSet = (int)sprite_set;
  prev_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  render_hook_fn = Render_DefaultRH;
  *(_DWORD *)&v17[25] = aStdrh_19;
  prev_render_hook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(92, a2, prev_resource_handle, (int)aSetrhS08x_24);
  field_offset = 0;
  qmemcpy(widget_table, &g_InGameSettingsButtonWidgetsTemplate, 4 * v7);
  copy_src = (char *)&g_InGameSettingsButtonWidgetsTemplate + 4 * v7;
  copy_dest = &widget_table[4 * v7];
  *(_WORD *)copy_dest = *(_WORD *)copy_src;
  copy_dest[2] = copy_src[2];
  do
  {
    *(_DWORD *)((char *)widget_text_ptrs + field_offset) += (unsigned __int8)g_LanguageIndex;
    button_text = *(_DWORD *)((char *)&widget_text_ptrs[1] + field_offset);
    field_offset += 53;
    *(_DWORD *)&v17[field_offset] = (unsigned __int8)g_LanguageIndex + button_text;
  }
  while ( field_offset != 212 );
  if ( *(_DWORD *)(gameData + 147159) )
    v20 = 2;
  if ( *(_DWORD *)(gameData + 147147) )
    v22 = 2;
  if ( *(_DWORD *)(gameData + 147163) )
    v23 = 2;
  if ( *(_DWORD *)(gameData + 147167) )
    v24 = 2;
  music_volume_raw = (*(char *)(gameData + 147173) << 8) + 0x4000;
  g_OptionsInGameMusicVolumeRaw = (music_volume_raw - (__CFSHL__(music_volume_raw >> 31, 7) + (music_volume_raw >> 31 << 7))) >> 7;
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
  UIWidgetTable_InitDrawStates(widget_table);
  Options_DrawAllSliderThumbs(g_InGameSliderThumbPositions, 132, prev_resource_handle);
  g_InGameOptionsDialogExitSignal = v13;
  do
  {
    DD_Pump((int)g_RenderState, 132);
    UIWidgetTable_PollHoverAndActions(widget_table, prev_resource_handle);
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
  Options_ApplyRecordSettings(gameData + 147147, v14, prev_resource_handle);
  Options_DestroySliderThumbList(g_InGameSliderThumbPositions);
  render_hook_fn = (int ( *)(int, char, DWORD))g_RenderHook;
  Debug_Log(v15, (char)g_RenderHook, prev_resource_handle, (int)aUnsetrh08x_24);
  g_RenderHook = prev_render_hook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, prev_resource_handle);
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
  signed int squad_count; // eax
  signed int slot_index; // ecx

  if ( g_SelectedUnitIndex != -1 )
  {
    for ( i = 0; ; i += 31 )
    {
      squad_count = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( slot_index >= squad_count )
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
  int slot_offset; // edx
  signed int slot_index; // ecx

  if ( g_SelectedUnitIndex != -1 )
  {
    while ( 1 )
    {
      result = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( slot_index >= result )
        break;
      *(_BYTE *)(slot_offset + UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147192) |= 3u;
      *(_BYTE *)(slot_offset + 31 + UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147161) = *(_BYTE *)(slot_offset
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
  signed int squad_count; // eax
  int slot_offset; // ecx
  signed int slot_index; // edx

  if ( g_SelectedUnitIndex != -1 )
  {
    while ( 1 )
    {
      squad_count = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( slot_index >= squad_count )
        break;
      *(_BYTE *)(slot_offset + 31 + gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147158) = 100;
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
  unsigned int tile_occupant_id; // edx

  result = gameData
         + 200
         * ((((g_MouseCursorRawX >> g_CursorCoordShift)
            - 32
            - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
             + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
          + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET));
  tile_occupant_id = *(unsigned __int16 *)(result
                           + 2
                           * ((((g_MouseCursorRawY >> g_CursorCoordShift)
                              - 16
                              - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                               + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
                            + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET))
                           + TILE_MAP_OFFSET);
  if ( (unsigned __int16)tile_occupant_id != 0xFFFF )
  {
    if ( tile_occupant_id > 0x1F4 || (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * tile_occupant_id + 147180) > 0x28 )
    {
      Building_Destroy(BUILDING_RECORD_SIZE * (tile_occupant_id - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET, gameData, a1, a2);
      return WorldMap_RedrawViewport(1);
    }
    else
    {
      UnitStack_KillByIndex(tile_occupant_id, gameData, a1, a2);
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
  int tile_x; // esi
  int result; // eax
  int tile_y; // edi

  tile_x = (((g_MouseCursorRawX >> g_CursorCoordShift)
       - 32
       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
        + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
     + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
  result = ((g_MouseCursorRawY >> g_CursorCoordShift)
          - 16
          - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
           + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6;
  tile_y = result + *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET);
  if ( g_SelectedUnitIndex != -1 )
  {
    *(_WORD *)(TILE_ROW_STRIDE * *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET)
             + gameData
             + 2 * *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176)
             + TILE_MAP_OFFSET) = -1;
    *(_WORD *)(TILE_INDEX(tile_x, tile_y)) = g_SelectedUnitIndex;
    *(_WORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET) = tile_x;
    *(_WORD *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176) = tile_y;
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
  signed int slot_index; // ecx

  if ( g_SelectedUnitIndex != -1 )
  {
    for ( i = 0; ; i += 31 )
    {
      result = Unit_GetSquadCount(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
      if ( slot_index >= result )
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
  void *palette_ctor_descriptor; // ebx
  int v2; // ecx
  int palette_mem; // eax
  int v4; // ecx
  unsigned __int8 *palette; // edi
  _DWORD *Surface; // eax
  _DWORD *team_surface; // esi
  _DWORD *saved_surface; // [esp+0h] [ebp-1Ch]

  LOBYTE(palette_ctor_descriptor) = 0;
  Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  palette_mem = Mem_Alloc(1024, v2, 0, a1);
  if ( palette_mem )
  {
    palette_ctor_descriptor = &g_Runtime_PaletteArrayCtorDescriptor;
    palette_mem = _wcpp_4_ctor_array__(v4, 256);
  }
  palette = (unsigned __int8 *)palette_mem;
  Surface = (_DWORD *)Mem_Alloc(188, v4, (char)palette_ctor_descriptor, a1);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  team_surface = Surface;
  saved_surface = Surface;
  (*(void (__fastcall **)(_DWORD, char *))(Surface[46] + 48))(0, aTeam1_gfx);
  (*(void (**)(void))(team_surface[46] + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, palette, 20);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping((int)g_RenderState) )
    DD_Pump((int)g_RenderState, 20);
  Render_Begin((int)g_RenderState, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_MapPalettePtr, 20);
  if ( saved_surface )
    (*(void (**)(void))saved_surface[46])();
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
  int building_index; // eax
  int building_record; // edx
  int building_offset; // edx
  char color_flags; // bl

  *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) = 3;
  building_index = 0;
  while ( 1 )
  {
    building_record = UNIT_RECORD(building_index);
    if ( (unsigned int)*(char *)(building_record + 4) < 4 && *(__int16 *)(building_record + 16) != -1 )
    {
      building_offset = gameData + BUILDING_RECORD_SIZE * building_index;
      if ( *(unsigned __int8 *)(building_offset + 509676) == g_CurrentPlayerIndex )
      {
        color_flags = *(_BYTE *)(building_offset + 510118) & 0xF8;
        *(_BYTE *)(building_offset + 510118) = color_flags;
        *(_BYTE *)(building_offset + 510118) = color_flags | 3;
      }
    }
    do
    {
      if ( ++building_index >= 100 )
        // 451CE5: loop exit jumps to the shared epilogue loc_451C1C
        // (pop edx/ecx/ebx; retn) shared with sub_451AE0; in C this is the return.
        return;
    }
    while ( building_index < 0 );
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
  int trigger_key; // esi
  int result; // eax
  _BYTE *i; // esi
  signed int key_code; // eax
  unsigned int popped_key; // ebx
  int pressed_key; // ecx
  _BYTE *decode_cursor; // esi
  int table_offset; // ecx
  int v10; // ecx
  int next_cheat_string; // ebx
  _BYTE cheat_buffer[124]; // [esp+0h] [ebp-7Ch] BYREF

  if ( g_LanguageIndex == 2 )
    trigger_key = 25;
  else
    trigger_key = 46;
  result = Input_IsKeyPressed(trigger_key);
  if ( result )
  {
    while ( Input_IsKeyPressed(trigger_key) )
      DD_Pump((int)g_RenderState, a1);
    for ( i = cheat_buffer; ; *(i - 1) = Input_KeyToChar(popped_key) )
    {
      while ( 1 )
      {
        key_code = Input_PopKey();
        popped_key = key_code;
        if ( key_code != -1 )
          break;
        DD_Pump((int)g_RenderState, -1);
      }
      pressed_key = key_code;
      while ( 1 )
      {
        result = Input_IsKeyPressed(pressed_key);
        if ( !result )
          break;
        DD_Pump((int)g_RenderState, popped_key);
      }
      if ( popped_key == 28 )
        break;
      ++i;
    }
    *i = 0;
    BYTE1(result) = cheat_buffer[0];
    decode_cursor = cheat_buffer;
    if ( cheat_buffer[0] )
    {
      do
        *decode_cursor ^= 0x32u;
      while ( *++decode_cursor );
    }
    table_offset = 0;
    if ( g_CheatTable )
    {
      do
      {
        result = strcmp_(table_offset, cheat_buffer);
        if ( !result )
          result = (*(int (**)())((char *)&g_CheatCodeHandlerTable + v10))();
        next_cheat_string = *(int *)((char *)&g_CheatCodeStringTable + v10);
        table_offset = v10 + 8;
      }
      while ( next_cheat_string );
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
  double formatted_turn; // st7
  double formatted_player; // st7
  int castle_count; // edx
  int building_index; // eax
  int building_record; // ecx
  int building_offset; // ecx
  double formatted_castles; // st7
  int fortress_count; // edx
  int fortress_scan_index; // eax
  int fortress_record; // ebx
  int fortress_offset; // ecx
  double formatted_fortresses; // st7
  char fact_text[224]; // [esp+0h] [ebp-E0h] BYREF

  Diagnostics_TraceWorldMapActionEvent("ai_turn_enter", g_SelectedUnitIndex, g_CurrentPlayerIndex, GAME_TURN_COUNTER, 0);
  Map_RebuildCastleSiteAnchorCache();
  formatted_turn = sprintf_(fact_text, "(tura %d)", *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET));
  g_AITurnLogFactHandle_Turn = (int)Rules_Log(fact_text, 0, formatted_turn);
  formatted_player = sprintf_(fact_text, "(gracz %d inteligencja %d)", g_CurrentPlayerIndex, PLAYER_AI_INTELLIGENCE(g_CurrentPlayerIndex));
  g_AITurnPlayerIntelligenceFactHandle = (int)Rules_Log(fact_text, 0, formatted_player);
  memset(fact_text, 0, 0xC8);
  castle_count = 0;
  building_index = 0;
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(building_record + 4) < 4 && *(__int16 *)(building_record + 16) != -1 )
  {
    building_offset = gameData + BUILDING_RECORD_SIZE * building_index;
    if ( *(unsigned __int8 *)(building_offset + 509676) == g_CurrentPlayerIndex && *(_BYTE *)(building_offset + 509678) == 2 )
      ++castle_count;
  }
  while ( ++building_index < 100 )
  {
    if ( building_index >= 0 )
      goto LABEL_2;
  }
  formatted_castles = sprintf_(fact_text, "(ilosc-zamkow %d %d)", g_CurrentPlayerIndex, castle_count);
  g_AITurnCastleCountFactHandle = (int)Rules_Log(fact_text, 0, formatted_castles);
  fortress_count = 0;
  fortress_scan_index = 0;
LABEL_11:
  fortress_record = UNIT_RECORD(fortress_scan_index);
  if ( (unsigned int)*(char *)(fortress_record + 4) < 4 && *(__int16 *)(fortress_record + 16) != -1 )
  {
    fortress_offset = gameData + BUILDING_RECORD_SIZE * fortress_scan_index;
    if ( *(unsigned __int8 *)(fortress_offset + 509676) == g_CurrentPlayerIndex && *(_BYTE *)(fortress_offset + 509678) == 1 )
      ++fortress_count;
  }
  while ( ++fortress_scan_index < 100 )
  {
    if ( fortress_scan_index >= 0 )
      goto LABEL_11;
  }
  formatted_fortresses = sprintf_(fact_text, "(ilosc-twierdz %d %d)", g_CurrentPlayerIndex, fortress_count);
  g_AiTurnFortressCountFactHandle = (int)Rules_Log(fact_text, 0, formatted_fortresses);
  Diagnostics_TraceWorldMapActionEvent("ai_turn_before_agenda", g_SelectedUnitIndex, g_CurrentPlayerIndex, castle_count, fortress_count);
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
unsigned int  Rules_CreateArmyFact(stack_record, army_id, a3, a4, a5)
__int16 *stack_record;
int army_id;
int a3;
char a4;
DWORD a5;
{
  unsigned int result; // eax
  _DWORD *fact; // eax
  int trace_load_save; // eax
  char fact_text[1000]; // [esp+0h] [ebp-3ECh] BYREF

  trace_load_save = 0;
  result = stack_record[3];
  if ( result <= 0x28 )
  {
    ++g_RulesArmyFactCreatedCount;
    sprintf_(
      fact_text,
      "( ODDZIAL%d of oddzial (id %d)(gracz %d)(PA %d)(moc %d)(x %d)(y %d))",
      army_id,
      army_id,
      *((unsigned __int8 *)stack_record + 4),
      100,
      100,
      *stack_record,
      stack_record[1]);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-create-army-fact %s\n", fact_text);
    Debug_Log(0, a4, a5, (int)aMkinstArmyS);
    fact = Rules_AssertFact(fact_text, 0, 0.0);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-create-army-after-assert fact=%p\n", fact);
    *(_DWORD *)((char *)stack_record + 721) = fact;
    if ( !fact )
      return 0;
    return Rules_LinkArmyFact(stack_record, army_id, a3, 0.0, a4, a5);
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
  char fact_text[1000]; // [esp+0h] [ebp-3F0h] BYREF
  int v9; // [esp+3E8h] [ebp-8h]
  int v10; // [esp+3ECh] [ebp-4h]

  stack = (__int16 *)result;
  v10 = a3;
  v9 = a2;
  if ( *(_DWORD *)((char *)result + 721) )
  {
    Rules_RetractFactById(*(_DWORD *)((char *)result + 721), a4);
    sprintf_(fact_text, "(usunieto armie %d )", *(unsigned __int16 *)(TILE_INDEX(*stack, stack[1])));
    result = Rules_Log(fact_text, 0, a4);
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
  Rules_RegisterHostFunction(aOdleglosc_od_0, 105, (int)aOdleglosc_od_o, (int)&Rules_HostDistanceFromObject, (int)a33i);
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
signed int  Rules_UnitStackHasNormalCombatUnits(int stack_index)
{
  return UnitStack_HasNormalCombatUnits(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00453110) --------------------------------------------------------
signed int  Rules_QueuePathToTile(int stack_index, int target_x, int target_y, DWORD a4)
{
  int v5; // ecx
  int *track; // ebx
  int v7; // ecx
  int v8; // edx
  int queued_target_xy; // [esp+0h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( !abs32(target_x - (unsigned __int8)queued_target_xy) && !abs32(target_y - BYTE1(queued_target_xy)) )
      return 1;
  }
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(v5, target_y, a4);
  track = Unit_MoveTrack(
         stack_index,
         *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
         v5,
         *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
         a4,
         target_y);
  Pathing_DisableBridgeCrossings(v7, (char)track, a4);
  if ( !v8 )
    return 0;
  if ( *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + 147490) )
    *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) = 0;
  qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
  j__nfree_();
  return 1;
}
// 453152: variable 'v5' is possibly undefined
// 453191: variable 'v7' is possibly undefined
// 453198: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004532A0) --------------------------------------------------------
signed int  Rules_QueuePathNearTile(int stack_index, int target_x, int target_y, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  _DWORD *track; // ebx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  Debug_Log(stack_index, target_y, a4, (int)aJest_droga_w_3);
  if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v6 + UNIT_STACK_PATH_OFFSET) )
  {
    queued_target_xy = *(_DWORD *)(UNIT_STACK_STRIDE * v5 + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( (int)abs32(target_x - (unsigned __int8)queued_target_xy) < 2 )
    {
      a4 = BYTE1(queued_target_xy);
      if ( (int)abs32(target_y - BYTE1(queued_target_xy)) > 2 )
      {
        if ( target_x != (unsigned __int8)queued_target_xy )
          return 1;
        if ( target_y != BYTE1(queued_target_xy) )
          return 1;
      }
    }
  }
  if ( UnitStack_HasBuilder(v5) )
    Pathing_EnableBridgeCrossings(v7, target_y, a4);
  track = Unit_MoveTrackNearTile(v7, target_x, v7, target_y, a4);
  Pathing_DisableBridgeCrossings(v9, (char)track, a4);
  if ( v11 )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v10 + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v10 + 147490) = 0;
    qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v10 + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
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
signed int  Rules_QueuePathNearCastle(int stack_index, int castle_x, int castle_y, DWORD a4)
{
  int v5; // ecx
  const void *track; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    a4 = (unsigned __int8)queued_target_xy;
    if ( (int)abs32(castle_x - (unsigned __int8)queued_target_xy) < 3 && (int)abs32(castle_y - BYTE1(queued_target_xy)) < 3 )
    {
      if ( castle_x != (unsigned __int8)queued_target_xy )
        return 1;
      if ( castle_y != BYTE1(queued_target_xy) )
        return 1;
    }
  }
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(v5, castle_y, a4);
  track = (const void *)Building_GenerateNearApproachTrack(v5, *(unsigned __int16 *)(TILE_INDEX(castle_x, castle_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v5, castle_y, a4);
  Pathing_DisableBridgeCrossings(v7, (char)track, a4);
  if ( v9 )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
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
signed int  Rules_QueuePathToPort(int army_index, int target_x, int queued_dest, DWORD a4)
{
  int target_y; // esi
  int v5; // ecx
  int *move_track; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx

  target_y = queued_dest;
  LOBYTE(queued_dest) = gameData;
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * army_index + 147490) )
  {
    queued_dest = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * army_index + 320);
    if ( !abs32(target_x - (unsigned __int8)queued_dest) && !abs32(target_y - BYTE1(queued_dest)) )
      return 1;
  }
  if ( UnitStack_HasBuilder(army_index) )
    Pathing_EnableBridgeCrossings(v5, queued_dest, a4);
  move_track = Port_GenerateApproachTrack(v5);
  Pathing_DisableBridgeCrossings(v7, (char)move_track, a4);
  if ( !v9 )
    return 0;
  if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v8 + UNIT_STACK_PATH_OFFSET) )
    *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) = 0;
  qmemcpy((void *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), move_track, UNIT_STACK_PATH_BYTES);
  j__nfree_();
  return 1;
}
// 453641: variable 'v5' is possibly undefined
// 453651: variable 'v7' is possibly undefined
// 453658: variable 'v9' is possibly undefined
// 45367B: variable 'v8' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453770) --------------------------------------------------------
signed int  Rules_QueuePathToCastle(int stack_index, int castle_x, int castle_y, DWORD a4)
{
  int v5; // ecx
  const void *track; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    a4 = (unsigned __int8)queued_target_xy;
    if ( (int)abs32(castle_x - (unsigned __int8)queued_target_xy) < 2 && (int)abs32(castle_y - BYTE1(queued_target_xy)) < 2 )
    {
      if ( castle_x != (unsigned __int8)queued_target_xy )
        return 1;
      if ( castle_y != BYTE1(queued_target_xy) )
        return 1;
    }
  }
  if ( UnitStack_HasBuilder(stack_index) )
    Pathing_EnableBridgeCrossings(v5, castle_y, a4);
  track = (const void *)Building_GenerateApproachTrack(
                       v5,
                       *(unsigned __int16 *)(TILE_INDEX(castle_x, castle_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
                       v5,
                       castle_y,
                       a4);
  Pathing_DisableBridgeCrossings(v7, (char)track, a4);
  if ( v9 )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v8 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
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
signed int  Move_IsAtTargetOrCanStay(int stack_index, int target_x, int target_y)
{
  signed int result; // eax
  int v4; // ecx
  int queued_target_xy; // [esp+0h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    queued_target_xy = *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( !abs32(target_x - (unsigned __int8)queued_target_xy) && !abs32(target_y - BYTE1(queued_target_xy)) )
      return 1;
  }
  result = (signed int)Temple_GenerateApproachTrack(stack_index, target_x, stack_index, target_y);
  if ( result )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v4 + UNIT_STACK_PATH_OFFSET) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v4 + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * v4 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    return 1;
  }
  return result;
}
// 453993: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453A90) --------------------------------------------------------
signed int  Move_TryApproachTarget(int stack_index, DWORD target_x, int target_y)
{
  signed int result; // eax
  int v4; // ecx
  const void *track; // ebp
  signed int min_action_points; // eax
  signed int queued_move_cost; // edx
  int stack_offset; // ebx
  unsigned __int16 required_move_cost; // di
  int v10; // ecx
  int queued_target_xy; // [esp+4h] [ebp-14h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490)
    && (queued_target_xy = *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320), (int)abs32(target_x - (unsigned __int8)queued_target_xy) <= 2)
    && (int)abs32(target_y - BYTE1(queued_target_xy)) <= 2 )
  {
    min_action_points = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
    return min_action_points >= queued_move_cost;
  }
  else
  {
    result = Building_GenerateApproachTrack(stack_index, *(unsigned __int16 *)(TILE_INDEX(target_x, target_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE, stack_index, target_y, target_x);
    track = (const void *)result;
    if ( result )
    {
      stack_offset = UNIT_STACK_STRIDE * v4;
      required_move_cost = HIWORD(*(_DWORD *)(result + 4));
      if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * v4 + gameData + UNIT_STACK_TABLE_OFFSET) < required_move_cost )
      {
        j__nfree_();
        return 0;
      }
      else
      {
        if ( *(_DWORD *)(stack_offset + gameData + 147490) )
          *(_DWORD *)(UNIT_STACK_STRIDE * v10 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) = 0;
        qmemcpy((void *)(UNIT_STACK_STRIDE * v10 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
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
signed int  Rules_QueuePathIntoArmyRange(int stack_index, int target_x, int target_y, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  signed int result; // eax
  int v8; // ecx
  const void *track; // ebp
  signed int min_action_points; // eax
  signed int queued_move_cost; // edx
  int stack_offset; // ebx
  unsigned __int16 required_move_cost; // di
  int v14; // ecx
  int queued_target_xy; // [esp+4h] [ebp-14h]

  Debug_Log(stack_index, target_y, a4, (int)aOddzial_w_za_2);
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v6 + 147490)
    && (a4 = UNIT_STACK_STRIDE * v5, queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v5 + 320), (int)abs32(target_x - (unsigned __int8)queued_target_xy) <= 1)
    && (int)abs32(target_y - BYTE1(queued_target_xy)) <= 1 )
  {
    min_action_points = UnitStack_GetMinCurrentActionPoints(a4 + gameData + UNIT_STACK_TABLE_OFFSET);
    return min_action_points >= queued_move_cost;
  }
  else
  {
    result = (signed int)Unit_MoveTrackNearTile(v5, target_x, v5, target_y, a4);
    track = (const void *)result;
    if ( result )
    {
      stack_offset = UNIT_STACK_STRIDE * v8;
      required_move_cost = HIWORD(*(_DWORD *)(result + 4));
      if ( UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * v8 + gameData + UNIT_STACK_TABLE_OFFSET) < required_move_cost )
      {
        j__nfree_();
        return 0;
      }
      else
      {
        if ( *(_DWORD *)(stack_offset + gameData + 147490) )
          *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v14 + 147490) = 0;
        qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * v14 + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
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
signed int  Rules_GetPathDistanceToObject(int stack_index, int target_x, int target_y, DWORD a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int *Track; // eax
  int path_distance; // edx
  int queued_target_xy; // [esp+0h] [ebp-14h]

  Debug_Log(target_x, target_y, a4, (int)aOdleglosc_od_1);
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v6 + 147490) )
  {
    a4 = gameData;
    queued_target_xy = *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 320);
    if ( (int)abs32(v5 - (unsigned __int8)queued_target_xy) <= 1 && (int)abs32(target_y - BYTE1(queued_target_xy)) <= 1 )
      return *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + 147490);
  }
  if ( MapTile_GetReligiousSiteCategory(v5, target_y) )
  {
    Track = Temple_GenerateApproachTrack(stack_index, v7, v7, target_y);
  }
  else if ( MapTile_HasHiddenTreasure(v7, target_y) )
  {
    Track = Unit_MoveTrack(
              stack_index,
              *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
              v8,
              *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
              a4,
              target_y);
  }
  else if ( v8 == PORT_ROW && target_y == PORT_COLUMN )
  {
    Track = Port_GenerateApproachTrack(stack_index);
  }
  else
  {
    Track = Unit_MoveTrackNearTile(stack_index, v8, v8, target_y, a4);
  }
  if ( !Track )
    return 1000;
  j__nfree_();
  return path_distance;
}
// 453E97: variable 'v6' is possibly undefined
// 453EAB: variable 'v5' is possibly undefined
// 453EBC: variable 'v7' is possibly undefined
// 453EFC: variable 'v8' is possibly undefined
// 453FD0: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00453FE0) --------------------------------------------------------
BOOL  Rules_IsTempleWithinArmyRange(int stack_index, int temple_x, int temple_y)
{
  int *Track; // edx
  BOOL result; // eax
  signed int min_action_points; // eax
  signed int required_move_cost; // edx
  int queued_target_xy; // [esp+4h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( (int)abs32(temple_x - (unsigned __int8)queued_target_xy) > 1 || (int)abs32(temple_y - BYTE1(queued_target_xy)) > 1 )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) = 0;
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    Track = Temple_GenerateApproachTrack(stack_index, temple_x, temple_x, temple_y);
    if ( Track )
    {
      qmemcpy((void *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), Track, UNIT_STACK_PATH_BYTES);
      j__nfree_();
    }
  }
  result = 0;
  if ( *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) )
  {
    min_action_points = UnitStack_GetMinCurrentActionPoints(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index);
    if ( min_action_points >= required_move_cost )
      return 1;
  }
  return result;
}
// 454198: variable 'v7' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004541B0) --------------------------------------------------------
BOOL  Player_CanEnterReligiousSiteTile(int player_index, int tile_x, int tile_y)
{
  int v4; // ecx

  return MapTile_GetReligiousSiteCategory(tile_x, tile_y) == RELIGIOUS_SITE_CATEGORY_SHRINE && PLAYER_RELIGION_FLAG(player_index)
      || MapTile_GetReligiousSiteCategory(v4, tile_y) == RELIGIOUS_SITE_CATEGORY_CULT_PLACE && !PLAYER_RELIGION_FLAG(player_index);
}
// 4541E6: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454210) --------------------------------------------------------
signed int  Move_CommitIfWithinCost(
        unsigned int stack_index,
        int a2,
        DWORD a3,
        double a4)
{
  int stack_offset; // ebx
  int stack_record; // eax
  int prev_x; // esi
  int prev_y; // edi
  unsigned int v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  _DWORD pa_value[9]; // [esp-4h] [ebp-24h] BYREF

  pa_value[8] = a2;
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
    return 0;
  stack_offset = UNIT_STACK_STRIDE * stack_index;
  stack_record = gameData + UNIT_STACK_STRIDE * stack_index;
  prev_x = *(__int16 *)(stack_record + 147174);
  prev_y = *(__int16 *)(stack_record + 147176);
  UnitStack_ExecuteQueuedPath(stack_index, 1, -43 * stack_index, a3, a4);
  if ( v10 > 0x1F4 || (unsigned int)*(__int16 *)(stack_offset + gameData + 147180) > 0x28 )
    return 1;
  if ( Rules_IsQueuedPathTargetBridgeCrossing(v10) )
    Rules_BuildRoadOrStepTowardQueuedPath(v11, a3, a4);
  v12 = gameData + UNIT_STACK_STRIDE * v11;
  if ( prev_x == *(__int16 *)(v12 + 147174) && prev_y == *(__int16 *)(v12 + 147176) )
  {
    pa_value[1] = 1;
    pa_value[2] = Rules_AddIntegerValue(0);
    Rules_PutInstanceSlotValue(*(_DWORD *)(v13 + gameData + 147895), aPa, v14, pa_value, a4);
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
signed int  Rules_MarchToTemple(unsigned int stack_index, int temple_x, int temple_y, double a4)
{
  int *Track; // edx
  int stack_record; // eax
  int prev_x; // edi
  int prev_y; // ebx
  int v10; // ecx
  int stack_offset; // ebp
  int stack_record_after; // eax
  int v13; // ecx
  _DWORD pa_value[6]; // [esp+0h] [ebp-28h] BYREF
  int queued_target_xy; // [esp+18h] [ebp-10h]

  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( (int)abs32(temple_x - (unsigned __int8)queued_target_xy) > 1 || (int)abs32(temple_y - BYTE1(queued_target_xy)) > 1 )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) = 0;
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    Track = Temple_GenerateApproachTrack(stack_index, temple_x, temple_x, temple_y);
    if ( Track )
    {
      qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), Track, UNIT_STACK_PATH_BYTES);
      j__nfree_();
    }
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
    return 0;
  stack_record = gameData + UNIT_STACK_STRIDE * stack_index;
  prev_x = *(__int16 *)(stack_record + 147174);
  prev_y = *(__int16 *)(stack_record + 147176);
  UnitStack_ExecuteQueuedPath(stack_index, 1, prev_y, stack_index, a4);
  if ( stack_index <= 0x1F4 && (unsigned int)*(__int16 *)(v10 + gameData + 147180) <= 0x28 )
  {
    stack_offset = UNIT_STACK_STRIDE * stack_index;
    stack_record_after = gameData + stack_offset;
    if ( *(__int16 *)(gameData + stack_offset + 147180) == -1 )
      return 0;
    if ( prev_x == *(__int16 *)(stack_record_after + 147174) && prev_y == *(__int16 *)(stack_record_after + 147176) )
    {
      pa_value[1] = 1;
      pa_value[2] = Rules_AddIntegerValue(0);
      Rules_PutInstanceSlotValue(*(_DWORD *)(gameData + stack_offset + 147895), aPa_0, v13, pa_value, a4);
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
signed int  Rules_MarchNearTile(DWORD stack_index, int target_x, int target_y, double a4)
{
  int v5; // ecx
  int v6; // edx
  _DWORD *track; // edx
  DWORD stack_record; // eax
  int prev_x; // edi
  int prev_y; // ebx
  int v12; // ecx
  DWORD stack_offset; // ebp
  int v14; // ecx
  _DWORD pa_value[6]; // [esp+4h] [ebp-28h] BYREF
  int queued_target_xy; // [esp+1Ch] [ebp-10h]

  Debug_Log(target_x, target_y, stack_index, (int)aMaszeruj_bli_1);
  if ( *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v6 + 147490) )
  {
    queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320);
    if ( (int)abs32(v5 - (unsigned __int8)queued_target_xy) > 1 || (int)abs32(target_y - BYTE1(queued_target_xy)) > 1 )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) = 0;
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
  {
    track = Unit_MoveTrackNearTile(stack_index, v5, v5, target_y, stack_index);
    if ( track )
    {
      qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
      j__nfree_();
    }
  }
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
    return 0;
  stack_record = gameData + UNIT_STACK_STRIDE * stack_index;
  prev_x = *(__int16 *)(stack_record + 147174);
  prev_y = *(__int16 *)(stack_record + 147176);
  UnitStack_ExecuteQueuedPath(stack_index, 1, prev_y, stack_index, a4);
  if ( stack_index <= 0x1F4 && (unsigned int)*(__int16 *)(v12 + gameData + 147180) <= 0x28 )
  {
    stack_offset = UNIT_STACK_STRIDE * stack_index;
    if ( prev_x == *(__int16 *)(gameData + stack_offset + UNIT_STACK_TABLE_OFFSET) && prev_y == *(__int16 *)(gameData + stack_offset + 147176) )
    {
      pa_value[1] = 1;
      pa_value[2] = Rules_AddIntegerValue(0);
      Rules_PutInstanceSlotValue(*(_DWORD *)(gameData + stack_offset + 147895), aPa_1, v14, pa_value, a4);
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
signed int  Rules_HostUnitAttack(int army_index, int target_army_index, char a3, DWORD a4, double a5)
{
  Unit_Attack(army_index, target_army_index, a3, a4, a5);
  return 1;
}

//----- (00454800) --------------------------------------------------------
signed int  Rules_HostUnitCaptureDefeatedStack(int capturing_stack_index, int defeated_stack_index, double a3)
{
  UnitStack_CaptureDefeatedStack(
    (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * capturing_stack_index),
    gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * defeated_stack_index,
    gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * defeated_stack_index,
    capturing_stack_index,
    a3);
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00454860) --------------------------------------------------------
signed int  Rules_HostUnitMoveAndHide(unsigned int target_x, unsigned int target_y, DWORD stack_index, double a4)
{
  DWORD stack_offset; // esi
  signed int result; // eax
  char move_succeeded; // bl
  int v8; // edx
  unsigned __int64 target_xy_pair; // [esp+4h] [ebp-18h]

  target_xy_pair = __PAIR64__(target_x, target_y);
  stack_offset = UNIT_STACK_STRIDE * stack_index;
  result = (signed int)Unit_MoveTrack(
                         stack_index,
                         *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
                         target_x,
                         *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
                         stack_index,
                         target_y);
  move_succeeded = result;
  if ( result )
  {
    if ( *(_DWORD *)(stack_offset + gameData + 147490) )
      *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(stack_index, v8, move_succeeded, stack_index, a4);
    if ( __PAIR64__(*(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + 147176)) == target_xy_pair )
    {
      UnitStack_TryHide(stack_index, target_xy_pair, stack_index, a4);
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
signed int  Rules_HostUnitAttackBuilding(int army_index, int building_index, char a3, DWORD a4, double a5)
{
  Unit_AttackBuilding(army_index, building_index, a3, a4, a5);
  return 1;
}

//----- (004549A0) --------------------------------------------------------
BOOL  UnitStack_HasNormalCombatUnitsByIndex(int stack_index)
{
  return UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index) != 0;
}
// 5202E4: using guessed type int gameData;

//----- (004549E0) --------------------------------------------------------
signed int  UnitStack_GetSquadCountByIndex(int stack_index)
{
  return Unit_GetSquadCount(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00454A20) --------------------------------------------------------
signed int  Rules_IsQueuedPathTargetBridgeCrossing(int stack_index)
{
  signed int result; // eax
  int stack_table_base; // ebx

  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490) )
    return 0;
  stack_table_base = gameData + UNIT_STACK_TABLE_OFFSET;
  result = Map_GetBridgeCrossingCostOrZero(
             (unsigned __int8)*(_DWORD *)(stack_table_base + UNIT_STACK_STRIDE * stack_index + 4 * (*(_DWORD *)(stack_table_base + UNIT_STACK_STRIDE * stack_index + 316) - 1) + 320),
             (unsigned __int8)BYTE1(*(_DWORD *)(stack_table_base + UNIT_STACK_STRIDE * stack_index + 4 * (*(_DWORD *)(stack_table_base + UNIT_STACK_STRIDE * stack_index + 316) - 1) + 320)));
  if ( result )
    return 1;
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00454AE0) --------------------------------------------------------
signed int  Rules_BuildRoadOrStepTowardQueuedPath(int stack_index, DWORD a2, double a3)
{
  int stack_offset; // esi
  int stack_record; // eax
  int path_length; // ebx
  int path_base; // eax
  int next_waypoint_xy; // ebx
  signed int direction; // edi
  int v10; // ecx
  int v11; // eax
  int step_direction; // edx
  signed int move_result; // eax
  int fallback_direction; // edx

  stack_offset = UNIT_STACK_STRIDE * stack_index;
  stack_record = UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET;
  path_length = *(_DWORD *)(stack_record + 316);
  path_base = stack_record + 316;
  if ( !path_length )
    return 1;
  next_waypoint_xy = *(_DWORD *)(path_base + 4 * (path_length - 1) + 4);
  direction = Facing_DirectionFromDelta8(
         (unsigned __int8)next_waypoint_xy - *(__int16 *)(gameData + stack_offset + UNIT_STACK_TABLE_OFFSET),
         BYTE1(next_waypoint_xy) - *(__int16 *)(gameData + stack_offset + 147176));
  if ( Map_TileHasOwner(*(__int16 *)(stack_offset + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(stack_offset + gameData + 147176))
    && !Rules_IsQueuedPathTargetBridgeCrossing(v10) )
  {
    switch ( direction )
    {
      case 1:
        move_result = UnitStack_MoveOneTileInDirection(v10, 0, a3);
        goto LABEL_10;
      case 3:
        move_result = UnitStack_MoveOneTileInDirection(v10, 4, a3);
LABEL_10:
        if ( move_result )
          goto LABEL_13;
        fallback_direction = 2;
        break;
      case 5:
        if ( UnitStack_MoveOneTileInDirection(v10, 4, a3) )
          goto LABEL_13;
        fallback_direction = 6;
        break;
      case 7:
        if ( UnitStack_MoveOneTileInDirection(v10, 0, a3) )
          goto LABEL_13;
        fallback_direction = 6;
        break;
      default:
        fallback_direction = direction;
        break;
    }
LABEL_12:
    UnitStack_MoveOneTileInDirection(v10, fallback_direction, a3);
  }
  else
  {
    switch ( direction )
    {
      case 1:
        if ( !Road_Build(v10, 0, direction, a2, a3) )
        {
          v11 = v10;
          step_direction = 0;
          goto LABEL_8;
        }
        break;
      case 3:
        if ( !Road_Build(v10, 4, direction, a2, a3) )
        {
          step_direction = 4;
          v11 = v10;
LABEL_8:
          if ( !UnitStack_MoveOneTileInDirection(v11, step_direction, a3) )
          {
            move_result = Road_Build(v10, 2, direction, a2, a3);
            goto LABEL_10;
          }
        }
        break;
      case 5:
        if ( !Road_Build(v10, 4, direction, a2, a3)
          && !UnitStack_MoveOneTileInDirection(v10, 4, a3)
          && !Road_Build(v10, 6, direction, a2, a3) )
        {
          fallback_direction = 6;
          goto LABEL_12;
        }
        break;
      case 7:
        if ( !Road_Build(v10, 0, direction, a2, a3)
          && !UnitStack_MoveOneTileInDirection(v10, 0, a3)
          && !Road_Build(v10, 6, direction, a2, a3) )
        {
          fallback_direction = 6;
          goto LABEL_12;
        }
        break;
      default:
        if ( !Road_Build(v10, direction, direction, a2, a3) )
        {
          fallback_direction = direction;
          goto LABEL_12;
        }
        break;
    }
  }
LABEL_13:
  *(_DWORD *)(UNIT_STACK_STRIDE * v10 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) = 0;
  return 0;
}
// 454B74: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00454D20) --------------------------------------------------------
int  Rules_BuildTrapNearTile(DWORD target_x, int target_y, DWORD stack_index, double a4)
{
  int v5; // edx
  int v6; // ecx
  int result; // eax
  char move_succeeded; // bl
  int v9; // edx
  __int64 dx; // rax
  __int64 dy; // rax

  Debug_Log(target_x, stack_index, stack_index, (int)aBuduj_pulapke2);
  result = (int)Unit_MoveTrackNearTile(stack_index, v6, v6, v5, stack_index);
  move_succeeded = result;
  if ( result )
  {
    if ( *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET) )
      *(_DWORD *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) = 0;
    qmemcpy((void *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(stack_index, v9, move_succeeded, stack_index, a4);
    dx = (int)(*(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET) - target_x);
    if ( (int)((HIDWORD(dx) ^ dx) - HIDWORD(dx)) >= 2 )
      return 0;
    dy = *(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + 147176) - target_y;
    if ( (int)((HIDWORD(dy) ^ dy) - HIDWORD(dy)) >= 2 )
    {
      return 0;
    }
    else
    {
      Trap_New(target_x, target_y, target_x, stack_index, a4);
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
int  UnitStack_CalcArmyFactStrength(int stack_record)
{
  int total_strength;
  signed int i;
  char *unit_slot;
  int melee_strength;
  int shot_strength;

  total_strength = 0;
  unit_slot = (char *)(uintptr_t)(unsigned int)(stack_record + 6);
  for ( i = 0; i < Unit_GetSquadCount(stack_record); ++i )
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
signed int  Rules_EnsureArmyFactForStack(__int16 *army_stack, int army_id, double a3, char a4, DWORD a5)
{
  if ( (unsigned int)army_stack[3] > 0x28 && *(_DWORD *)((char *)army_stack + 721) )
  {
    Rules_RetractArmyFact(army_stack, army_id, (int)army_stack, a3);
    return 1;
  }
  else if ( *(_DWORD *)((char *)army_stack + 721) )
  {
    return 0;
  }
  else
  {
    Rules_CreateArmyFact((__int16 *)army_stack, *(unsigned __int16 *)(2 * army_stack[1] + gameData + TILE_ROW_STRIDE * *army_stack + TILE_MAP_OFFSET), (int)army_stack, a4, a5);
    return 1;
  }
}
// 454ED9: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;

//----- (00454F50) --------------------------------------------------------
signed int  Rules_LinkArmyFact(
        __int16 *stack,
        int army_id,
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
  stack_record = (int)(uintptr_t)stack;
  result = Rules_EnsureArmyFactForStack(stack, army_id, a4, a5, a6);
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
      result = *stack;
      if ( *(_DWORD *)((uintptr_t)(unsigned int)x_value[2] + 16) != result )
      {
        x_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(result);
        Rules_PutInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 2), stack_record, x_value, a4);
      }
      y_value[1] = 1;
      Rules_GetInstanceSlotValue(fact, (_BYTE *)((char *)aXxyy + 4), stack_record, y_value);
      result = stack[1];
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
        __int16 *army_stack,
        int army_id,
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
  stack_record = (int)(uintptr_t)army_stack;
  result = Rules_EnsureArmyFactForStack(army_stack, army_id, a6, a4, a5);
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
        __int16 *stack_record,
        char a2,
        DWORD a3,
        double a4)
{
  signed int result; // eax
  int v5; // edx
  int v6; // edx
  int v7; // ecx
  _DWORD owner_value[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Rules_EnsureArmyFactForStack(stack_record, (int)stack_record, a4, a2, a3);
  if ( !result )
  {
    result = *(__int16 *)(v5 + 6);
    if ( result != -1 )
    {
      owner_value[1] = 1;
      owner_value[2] = Rules_AddIntegerValue(*(unsigned __int8 *)(v5 + 4));
      return Rules_PutInstanceSlotValue(*(_DWORD *)(v6 + 721), aGracz, v7, owner_value, a4);
    }
  }
  return result;
}
// 4550FF: variable 'v5' is possibly undefined
// 45512A: variable 'v6' is possibly undefined
// 455135: variable 'v7' is possibly undefined

//----- (00455150) --------------------------------------------------------
signed int  Rules_SyncCastleFactOwner(int castle_record, int a2, double a3)
{
  int v5 = 0; // ecx
  int castle_fact; // eax
  int castle_owner; // eax
  int building_table_delta; // edx
  int building_index; // edx
  _DWORD owner_value[9]; // [esp-4h] [ebp-24h] BYREF

  (void)a2;
  owner_value[7] = a2;
  owner_value[1] = 1;
  castle_owner = *(unsigned __int8 *)(castle_record + 2);
  owner_value[2] = (int)(uintptr_t)Rules_AddIntegerValue(castle_owner);
  castle_fact = *(_DWORD *)(castle_record + 463);
  if ( !castle_fact )
  {
    building_index = -1;
    building_table_delta = castle_record - (gameData + BUILDING_TABLE_OFFSET);
    if ( building_table_delta >= 0 && building_table_delta % BUILDING_RECORD_SIZE == 0 )
    {
      building_index = building_table_delta / BUILDING_RECORD_SIZE;
      if ( (unsigned int)building_index >= 100u )
        building_index = -1;
    }
    Diagnostics_TraceWorldMapActionEvent(
      "rules_sync_castle_fact_missing",
      g_SelectedUnitIndex,
      castle_record,
      building_index,
      castle_owner);
    if ( building_index >= 0 )
    {
      Rules_AssertCastleFact((unsigned __int8 *)castle_record, building_index);
      castle_fact = *(_DWORD *)(castle_record + 463);
    }
  }
  Diagnostics_TraceWorldMapActionEvent(
    "rules_sync_castle_fact_owner",
    g_SelectedUnitIndex,
    castle_record,
    castle_fact,
    castle_owner);
  if ( !castle_fact )
  {
    Lexer_ErrorRecover(1);
    return 0;
  }
  return Rules_PutInstanceSlotValue(castle_fact, aGracz_0, v5, owner_value, a3);
}

//----- (004551A0) --------------------------------------------------------
_DWORD * Rules_LogTrapFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(pulapka %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 4551BC: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004551D0) --------------------------------------------------------
_DWORD * Rules_RetractTrapFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(kasuj pulapke %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 4551EC: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455200) --------------------------------------------------------
_DWORD * Rules_LogTempleFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(swiatynia %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 45521C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455230) --------------------------------------------------------
_DWORD * Rules_LogTreasureFact(int tile_x, int tile_y)
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(skarb %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 45524C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455260) --------------------------------------------------------
_DWORD * Rules_RetractTreasureFact(tile_x, tile_y)
int tile_x;
int tile_y;
{
  double formatted; // st7
  int v4; // ecx
  char fact_text[200]; // [esp+0h] [ebp-C8h] BYREF

  formatted = sprintf_(fact_text, "(kasuj skarb %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, v4, formatted);
}
// 45527C: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00455290) --------------------------------------------------------
_DWORD * Rules_RetractTempleFact(int tile_x, int tile_y, char a3, DWORD a4)
{
  int v5; // edx
  int v6; // ecx
  double formatted; // st7
  int v8; // ecx
  char fact_text[200]; // [esp+0h] [ebp-CCh] BYREF
  int v11; // [esp+C8h] [ebp-4h]

  v11 = tile_y;
  Debug_Log(tile_x, a3, a4, (int)aKasuj_swiatyni);
  formatted = sprintf_(fact_text, "(kasuj swiatynie %d %d)", v6, v5);
  return Rules_Log(fact_text, v8, formatted);
}
// 4552B4: variable 'v6' is possibly undefined
// 4552B4: variable 'v5' is possibly undefined
// 4552BE: variable 'v8' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004552D0) --------------------------------------------------------
int  Rules_AssertCastleFact(unsigned __int8 *castle_record, int building_index)
{
  char *barracks_text; // eax
  char *smithy_text; // eax
  char *workshop_text; // eax
  char *school_text; // eax
  const char *hospital_text; // eax
  double formatted; // st7
  int v10 = 0; // ecx
  _DWORD *fact; // eax
  const char *school_arg; // [esp-18h] [ebp-400h]
  const char *workshop_arg; // [esp-14h] [ebp-3FCh]
  const char *smithy_arg; // [esp-10h] [ebp-3F8h]
  const char *barracks_arg; // [esp-Ch] [ebp-3F4h]
  int castle_x; // [esp-8h] [ebp-3F0h]
  int castle_y; // [esp-4h] [ebp-3ECh]
  char fact_text[1000]; // [esp+0h] [ebp-3E8h] BYREF

  castle_y = castle_record[1];
  castle_x = *castle_record;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_BARRACKS) != 0 )
    barracks_text = aTak;
  else
    barracks_text = aNie;
  barracks_arg = barracks_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_SMITHS) != 0 )
    smithy_text = aTak_0;
  else
    smithy_text = aNie_0;
  smithy_arg = smithy_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_WORKSHOP) != 0 )
    workshop_text = aTak_1;
  else
    workshop_text = aNie_1;
  workshop_arg = workshop_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_SCHOOL) != 0 )
    school_text = aTak_2;
  else
    school_text = aNie_2;
  school_arg = school_text;
  if ( (castle_record[416] & BUILDING_ADDON_FLAG_HOSPITAL) != 0 )
    hospital_text = aTak_3;
  else
    hospital_text = aNie_3;
  formatted = sprintf_(
         fact_text,
         "( ZAMEK%d of zamek (id %d)(gracz %d)(szpital %s)(szkola %s)(warsztat %s)(kuznia %s)(koszary %s)(x %d)(y %d)(moc 0))",
         building_index,
         building_index,
         castle_record[2],
         hospital_text,
         school_arg,
         workshop_arg,
         smithy_arg,
         barracks_arg,
         castle_x,
         castle_y);
  fact = Rules_AssertFact(fact_text, v10, formatted);
  *(_DWORD *)(castle_record + 463) = (int)(uintptr_t)fact;
  return Building_OnGarrisonChange(building_index, (int)(uintptr_t)castle_record, 0.0);
}
// 455361: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004553A0) --------------------------------------------------------
_DWORD * Rules_RetractCastleFact(unsigned __int8 *castle_record, double a2)
{
  unsigned __int8 *castle_ptr; // edx
  int castle_x; // ecx

  castle_ptr = castle_record;
  if ( *(_DWORD *)(castle_record + 463) )
    Rules_RetractFactById(*(_DWORD *)(castle_record + 463), a2);
  castle_x = *castle_ptr;
  *(_DWORD *)(castle_ptr + 463) = 0;
  return Rules_LogCastleDestroyedFact(castle_ptr[2], *(unsigned __int16 *)(TILE_INDEX(castle_x, castle_ptr[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
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
_DWORD * Rules_OnCastleUpdate(int building_index, char a2, DWORD a3, double a4)
{
  return Building_Destroy(UNIT_RECORD(building_index), a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00455450) --------------------------------------------------------
BOOL  Building_TryStartUpgradeByIndex(int building_index)
{
  return Building_TryStartUpgrade((unsigned __int8 *)(UNIT_RECORD(building_index)));
}
// 5202E4: using guessed type int gameData;

//----- (00455470) --------------------------------------------------------
int  Building_GetTaxRateByIndex(int building_index)
{
  return *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * building_index + 510110) & 0x3F;
}
// 5202E4: using guessed type int gameData;

//----- (00455490) --------------------------------------------------------
signed int  Building_BuildSchoolByIndex(int building_index, char a2, DWORD a3)
{
  return Building_BuildSchool((char *)(UNIT_RECORD(building_index)), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004554B0) --------------------------------------------------------
signed int  Building_BuildSmithsByIndex(char a1, DWORD a2)
{
  return Building_BuildSmiths(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (004554D0) --------------------------------------------------------
int  Building_GetWallStrengthByIndex(int building_index)
{
  return *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building_index + 510095);
}
// 5202E4: using guessed type int gameData;

//----- (004554F0) --------------------------------------------------------
int  Building_GetMoneyByIndex(int building_index)
{
  return *(_DWORD *)(gameData + BUILDING_RECORD_SIZE * building_index + 510112);
}
// 5202E4: using guessed type int gameData;

//----- (00455510) --------------------------------------------------------
int  Building_GetCastleStrengthByIndex(int building_index)
{
  return Building_GetTotalValue(UNIT_RECORD(building_index));
}
// 5202E4: using guessed type int gameData;

//----- (00455530) --------------------------------------------------------
signed int  Building_BuildBarracksByIndex(int building_index, char a2, DWORD a3)
{
  return Building_BuildBarracks(building_index, a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455550) --------------------------------------------------------
signed int  Building_BuildHospitalByIndex(char a1, DWORD a2)
{
  return Building_BuildHospital(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (00455580) --------------------------------------------------------
int  Building_GetTechLevelByIndex(int building_index)
{
  return *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * building_index + 510118) & 7;
}
// 5202E4: using guessed type int gameData;

//----- (004555A0) --------------------------------------------------------
int  Building_GetTypeByIndex(int building_index)
{
  return *(char *)(gameData + BUILDING_RECORD_SIZE * building_index + 509678);
}
// 5202E4: using guessed type int gameData;

//----- (004555C0) --------------------------------------------------------
signed int  Building_BuildWorkshopByIndex(char a1, DWORD a2)
{
  return Building_BuildWorkshop(a1, a2);
}
// 5202E4: using guessed type int gameData;

//----- (004555E0) --------------------------------------------------------
int  Building_GetSatisfactionByIndex(int building_index)
{
  return *(char *)(gameData + BUILDING_RECORD_SIZE * building_index + 510108);
}
// 5202E4: using guessed type int gameData;

//----- (00455600) --------------------------------------------------------
int  Building_GetPeasantCountByIndex(int building_index)
{
  int result; // eax

  LOWORD(result) = *(_WORD *)(gameData + BUILDING_RECORD_SIZE * building_index + 510104);
  BYTE1(result) &= 0xFu;
  return (unsigned __int16)result;
}
// 5202E4: using guessed type int gameData;

//----- (00455620) --------------------------------------------------------
BOOL  Building_HasProductionByIndex(int building_index)
{
  return *(char *)(gameData + BUILDING_RECORD_SIZE * building_index + 510088) != -1;
}
// 5202E4: using guessed type int gameData;

//----- (00455650) --------------------------------------------------------
BOOL  Building_CanStartUpgradeByIndex(int building_index)
{
  return Building_CanStartUpgrade((unsigned __int8 *)(UNIT_RECORD(building_index)));
}
// 5202E4: using guessed type int gameData;

//----- (00455670) --------------------------------------------------------
int  Building_GetGarrisonCountByIndex(int building_index)
{
  return Building_CountGarrison(UNIT_RECORD(building_index));
}
// 5202E4: using guessed type int gameData;

//----- (00455690) --------------------------------------------------------
BOOL  Building_IsGarrisonFullByIndex(int building_index)
{
  return Building_CountGarrison(UNIT_RECORD(building_index)) == 12;
}
// 5202E4: using guessed type int gameData;

//----- (004556C0) --------------------------------------------------------
__int16  Building_RepairUnitByIndex(int building_index, int slot_index, DWORD a3)
{
  return Building_RepairUnit(UNIT_RECORD(building_index), slot_index, a3);
}
// 5202E4: using guessed type int gameData;

//----- (004556E0) --------------------------------------------------------
_BYTE * Building_TrainUnitByIndex(int building_index, char a2, DWORD a3)
{
  return Building_TrainUnit(UNIT_RECORD(building_index), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455700) --------------------------------------------------------
int  Building_SetUnitProductionByIndex(int building_index, char a2, DWORD a3)
{
  return Building_SetUnitProduction(UNIT_RECORD(building_index), a2, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455720) --------------------------------------------------------
int  Building_RemoveUnitLicenceByIndex(int building_index, unit_type licence_type, DWORD a3)
{
  return Building_RemoveUnitLicence(UNIT_RECORD(building_index), licence_type, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455740) --------------------------------------------------------
void  Building_AdjustTaxRateByIndex(int building_index, int ebx0, float tax_delta)
{
  double new_rate; // st7
  double applied_rate; // st7
  int v5; // edx
  char tax_byte_upper; // ah
  float new_rate_float; // [esp+0h] [ebp-10h]

  new_rate = (double)(*(_BYTE *)(BUILDING_RECORD_SIZE * building_index + gameData + 510110) & 0x3F) + tax_delta;
  new_rate_float = new_rate;
  if ( new_rate <= g_Building_MaxTaxRate )
  {
    applied_rate = new_rate_float;
    _CHP(ebx0, LODWORD(new_rate_float));
    tax_byte_upper = *(_BYTE *)(v5 + 510110) & 0xC0;
    *(_BYTE *)(v5 + 510110) = tax_byte_upper;
    *(_BYTE *)(v5 + 510110) = (int)applied_rate & 0x3F | tax_byte_upper;
  }
}
// 455791: variable 'v5' is possibly undefined
// 5000C6: using guessed type float flt_5000C6;
// 5202E4: using guessed type int gameData;

//----- (004557C0) --------------------------------------------------------
signed int  Building_HasUnitLicenceByIndex(int building_index, unit_type licence_type)
{
  return Building_HasUnitLicence(UNIT_RECORD(building_index), licence_type);
}
// 5202E4: using guessed type int gameData;

//----- (004557E0) --------------------------------------------------------
BOOL  Building_BuyUnitLicenceByIndex(int building_index, unit_type licence_type, DWORD a3)
{
  return Building_BuyUnitLicence(UNIT_RECORD(building_index), licence_type, gameData + BUILDING_TABLE_OFFSET, a3);
}
// 5202E4: using guessed type int gameData;

//----- (00455800) --------------------------------------------------------
BOOL  Building_CanBuyUnitLicenceByIndex(int building_index, unit_type licence_type)
{
  return Building_IsUnitLicenceEligible((char *)(UNIT_RECORD(building_index)), licence_type);
}
// 5202E4: using guessed type int gameData;

//----- (00455830) --------------------------------------------------------
BOOL  Rules_BuildCastle(int building_type, DWORD a2, double a3, char *castle_name)
{
  return Building_New(building_type, a2, a3, castle_name, 0);
}

//----- (00455850) --------------------------------------------------------
signed int  Building_FindUnitLicenceSlotIndexOrZero(int building_index, unit_type licence_type)
{
  signed int result; // eax
  int building_offset; // ebx

  result = 0;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  while ( *(char *)(building_offset + gameData + result + 510076) != licence_type )
  {
    if ( ++result >= 12 )
      return 0;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00455890) --------------------------------------------------------
signed int  Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero(int building_index)
{
  signed int result; // eax
  int building_offset; // ecx
  int licence_unit_type; // edx

  result = 0;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  while ( 1 )
  {
    licence_unit_type = *(char *)(building_offset + gameData + result + 510076);
    if ( licence_unit_type != -1 && licence_unit_type != UNIT_TYPE_PEASANT && licence_unit_type != UNIT_TYPE_BUILDER )
      break;
    if ( ++result >= 12 )
      return 0;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004558D0) --------------------------------------------------------
signed int  Building_UnitsLeaveReadyGarrisonSlots(int building_index, int a2, double a3)
{
  int i; // eax
  int slot_index; // eax
  int slot_offset; // ecx
  int ready_count; // edx
  int building_record; // ebx
  int garrison_slot; // esi
  int v11; // ecx
  int leave_slot_indices[10]; // [esp+4h] [ebp-44h] BYREF
  int v14; // [esp+2Ch] [ebp-1Ch]
  int building_offset; // [esp+30h] [ebp-18h]
  int v16; // [esp+40h] [ebp-8h]

  v16 = a2;
  v14 = building_index;
  for ( i = 0; i != 10; leave_slot_indices[i - 1] = -1 )
    ++i;
  slot_index = 0;
  building_offset = BUILDING_RECORD_SIZE * v14;
  slot_offset = 0;
  ready_count = 0;
  do
  {
    building_record = building_offset + gameData;
    garrison_slot = building_offset + gameData + slot_offset;
    if ( *(__int16 *)(garrison_slot + 509692) != -1
      && *(_BYTE *)(garrison_slot + 509701) == 100
      && !((unsigned __int8)(4 * *(_BYTE *)(building_record + slot_index + 510064)) >> 5)
      && (*(_BYTE *)(building_record + slot_index + 510064) & 7) == 0 )
    {
      leave_slot_indices[ready_count++] = slot_index;
    }
    ++slot_index;
    slot_offset += 31;
  }
  while ( slot_index < 10 && ready_count < 5 );
  if ( leave_slot_indices[0] == -1 )
    return 0;
  if ( Building_HasFreeAdjacentExitTile((unsigned __int8 *)(UNIT_RECORD(v14))) )
    return Building_UnitsLeave((unsigned __int8 *)(v11 + gameData + BUILDING_TABLE_OFFSET), leave_slot_indices, a3);
  return -1;
}
// 4559BC: variable 'v11' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004559D0) --------------------------------------------------------
signed int  Building_HasTrainableIdleGarrisonUnit(int building_index)
{
  int slot_offset; // edx
  int slot_index; // eax
  int building_offset; // edi
  int garrison_slot; // esi

  slot_offset = 0;
  slot_index = 0;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  while ( 1 )
  {
    garrison_slot = building_offset + gameData + slot_offset;
    if ( *(__int16 *)(garrison_slot + 509692) != -1
      && (*(_BYTE *)(garrison_slot + 509704) & 3u) < 2
      && (*(_BYTE *)(building_offset + gameData + slot_index + 510064) & 7) == 0 )
    {
      break;
    }
    ++slot_index;
    slot_offset += 31;
    if ( slot_index >= 12 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00455A50) --------------------------------------------------------
signed int  Building_HasRepairableIdleGarrisonUnit(int building_index)
{
  int slot_offset; // edx
  int slot_index; // eax
  int building_offset; // edi
  int garrison_slot; // ebx

  slot_offset = 0;
  slot_index = 0;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  while ( 1 )
  {
    garrison_slot = building_offset + gameData + slot_offset;
    if ( *(__int16 *)(garrison_slot + 509692) != -1
      && *(char *)(garrison_slot + 509701) < 50
      && !((unsigned __int8)(4 * *(_BYTE *)(building_offset + gameData + slot_index + 510064)) >> 5) )
    {
      break;
    }
    ++slot_index;
    slot_offset += 31;
    if ( slot_index >= 12 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00455AD0) --------------------------------------------------------
int  Building_StartTrainingIdleGarrisonUnits(int building_index)
{
  int slot_index; // ecx
  int slot_offset; // ebx
  DWORD building_offset; // ebp
  DWORD building_record; // edi
  int result; // eax

  slot_index = 0;
  slot_offset = 0;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  do
  {
    building_record = gameData + building_offset;
    result = slot_offset + gameData + building_offset;
    if ( *(__int16 *)(result + 509692) != -1 )
    {
      result = *(_BYTE *)(result + 509704) & 3;
      if ( result < 2 )
      {
        result = slot_index + building_record;
        if ( (*(_BYTE *)(slot_index + building_record + 510064) & 7) == 0 )
        {
          result = (unsigned __int8)(4 * *(_BYTE *)(result + 510064)) >> 5;
          if ( !result )
            result = (int)Building_TrainUnit(building_offset + gameData + BUILDING_TABLE_OFFSET, slot_offset, building_offset);
        }
      }
    }
    ++slot_index;
    slot_offset += 31;
  }
  while ( slot_index < 12 );
  return result;
}
// 455B40: variable 'v1' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00455B50) --------------------------------------------------------
__int16  Building_StartRepairIdleGarrisonUnits(int building_index)
{
  int slot_index; // ecx
  int slot_offset; // ebx
  int building_offset; // edi
  __int16 result; // ax
  int garrison_slot; // edx
  DWORD slot_unit_type; // ebp
  int slot_state_ptr; // esi

  slot_index = 0;
  slot_offset = 0;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  do
  {
    result = gameData;
    garrison_slot = slot_offset + building_offset + gameData;
    slot_unit_type = *(__int16 *)(garrison_slot + 509692);
    if ( slot_unit_type != -1 && *(char *)(garrison_slot + 509701) <= 90 )
    {
      slot_state_ptr = slot_index + building_offset + gameData;
      if ( (*(_BYTE *)(slot_state_ptr + 510064) & 7) == 0 && !((unsigned __int8)(4 * *(_BYTE *)(slot_state_ptr + 510064)) >> 5) )
        result = Building_RepairUnit(building_offset + gameData + BUILDING_TABLE_OFFSET, slot_index, slot_unit_type);
    }
    ++slot_index;
    slot_offset += 31;
  }
  while ( slot_index < 12 );
  return result;
}
// 455BB8: variable 'v1' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00455BD0) --------------------------------------------------------
signed int  Building_UnitsLeaveByUnitType(int building_index, unit_type leave_type, int a3, double a4)
{
  int i; // eax
  int slot_index; // edx
  int slot_offset; // eax
  int building_offset; // edi
  int leave_slot_indices[14]; // [esp+4h] [ebp-38h] BYREF

  leave_slot_indices[12] = a3;
  for ( i = 0; i != 10; leave_slot_indices[i - 1] = -1 )
    ++i;
  slot_index = 0;
  slot_offset = 0;
  while ( *(__int16 *)(BUILDING_RECORD_SIZE * building_index + gameData + slot_offset + 509692) != leave_type )
  {
    slot_offset += 31;
    ++slot_index;
    if ( slot_offset >= 310 )
    {
      if ( leave_slot_indices[0] == -1 )
        return 0;
      goto LABEL_10;
    }
  }
  leave_slot_indices[0] = slot_index;
  if ( slot_index == -1 )
    return 0;
LABEL_10:
  building_offset = BUILDING_RECORD_SIZE * building_index;
  if ( Building_HasFreeAdjacentExitTile((unsigned __int8 *)(building_offset + gameData + BUILDING_TABLE_OFFSET)) )
    return Building_UnitsLeave((unsigned __int8 *)(building_offset + gameData + BUILDING_TABLE_OFFSET), leave_slot_indices, a4);
  else
    return -1;
}
// 5202E4: using guessed type int gameData;

//----- (00455C90) --------------------------------------------------------
_DWORD * Rules_LogCastleSiteFact(int tile_x, int tile_y)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(zamek_place %d %d)", tile_x, tile_y);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455CC0) --------------------------------------------------------
_DWORD * Rules_LogBuildingTransferFact(int a1, int a2, int a3)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(budowanie transfer 0 0 %d %d %d)", a1, a2, a3);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455CF0) --------------------------------------------------------
_DWORD * Rules_LogNewCastleFact(int a1, int a2)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(powstal-nowy-zamek %d %d)", a1, a2);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455D20) --------------------------------------------------------
_DWORD * Rules_LogCastleDestroyedFact(int owner_index, int castle_id)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(zginal-zamek %d %d)", owner_index, castle_id);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455D50) --------------------------------------------------------
_DWORD * Rules_LogCastleSchemeFact(int a1, int castle_id)
{
  unsigned int scheme_index; // eax
  char fact_buffer[52]; // [esp+0h] [ebp-3Ch] BYREF

  scheme_index = Rng_RandRange(1, 3);
  sprintf_(fact_buffer, "(schemat %d %d %d)", a1, castle_id, scheme_index);
  return Rules_Log(fact_buffer, 0, 0.0);
}

//----- (00455D90) --------------------------------------------------------
_DWORD * Rules_LogBuildingCapturedFact(int a1, int a2, int a3)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(zdobyty %d %d %d)", a1, a2, a3);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455DC0) --------------------------------------------------------
_DWORD * Rules_LogCastleUnderConstructionFact(int castle_id)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(zamek w budowie %d)", castle_id);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455DF0) --------------------------------------------------------
_DWORD *__fastcall Rules_LogCastleBuiltFactAndScheme(int a1, int castle_id)
{
  char fact_text[52]; // [esp+0h] [ebp-38h] BYREF

  sprintf_(fact_text, "(zbudowano zamek %d)", castle_id);
  Rules_Log(fact_text, 0, 0.0);
  return Rules_LogCastleSchemeFact(a1, castle_id);
}

//----- (00455E20) --------------------------------------------------------
_DWORD * Rules_LogAssignedCastleFact(int castle_id, int a2)
{
  char fact_buffer[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_buffer, "(wyznaczony zamek %d %d)", castle_id, a2);
  return Rules_Log(fact_buffer, 0, 0.0);
}

//----- (00455E50) --------------------------------------------------------
_DWORD * Rules_LogAssignedPlayerFact(int a1, int a2)
{
  char fact_text[52]; // [esp+0h] [ebp-34h] BYREF

  sprintf_(fact_text, "(wyznaczony gracz %d %d)", a1, a2);
  return Rules_Log(fact_text, 0, 0.0);
}

//----- (00455E80) --------------------------------------------------------
BOOL  Building_SelectedUnitLicenceMatchesTypeByIndex(int building_index, unit_type licence_type)
{
  int building_record; // ecx
  int licence_slot_index; // eax

  building_record = BUILDING_RECORD_SIZE * building_index + gameData;
  licence_slot_index = BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX(building_record + 509674);
  return licence_slot_index != -1 && *(char *)(building_record + licence_slot_index + 510076) == licence_type;
}
// 5202E4: using guessed type int gameData;

//----- (00455EC0) --------------------------------------------------------
int  Player_GetInternedNameByIndex(int player_index, int a2, int a3)
{
  char *name_cursor; // edx
  char *name_buffer; // esi
  int char_index; // eax
  int player_offset; // ebx
  int name_char; // ecx
  int v9; // ecx
  int v10; // edx

  name_cursor = (char *)nmalloc_(a3, a2);
  name_buffer = name_cursor;
  char_index = 0;
  player_offset = PLAYER_DATA_STRIDE * player_index;
  do
  {
    name_char = player_offset + gameData;
    ++name_cursor;
    LOBYTE(name_char) = *(_BYTE *)(player_offset + gameData + char_index++ + 140028);
    *(name_cursor - 1) = name_char;
  }
  while ( char_index <= 11 );
  name_buffer[11] = 0;
  Str_Intern(name_buffer, name_char);
  nfree_(v9);
  return v10;
}
// 455F08: variable 'v9' is possibly undefined
// 455F0D: variable 'v10' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00455F20) --------------------------------------------------------
signed int  Building_HasGarrisonUnitTypeByIndex(int building_index, unit_type sought_type)
{
  int building_offset; // ebx
  int slot_offset; // eax

  building_offset = BUILDING_RECORD_SIZE * building_index;
  slot_offset = 0;
  while ( *(__int16 *)(building_offset + gameData + slot_offset + 509692) != sought_type )
  {
    slot_offset += 31;
    if ( slot_offset >= 310 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00455F60) --------------------------------------------------------
signed int  Map_IsCastleSiteDistanceMinimal(int candidate_row, int candidate_column, int site_column, int site_row)
{
  int slot; // edx
  float candidate_distance; // [esp+0h] [ebp-Ch]
  signed int minimum_distance; // [esp+4h] [ebp-8h]

  minimum_distance = Math_CeilSqrt((candidate_row - site_row) * (candidate_row - site_row) + (candidate_column - site_column) * (candidate_column - site_column));
  if ( g_CastleSiteAnchorRows[1] == -1 )
    return 1;
  for ( slot = 1; slot < CASTLE_SITE_ANCHOR_CACHE_COUNT && g_CastleSiteAnchorRows[slot] != -1; ++slot )
  {
    candidate_distance = (float)minimum_distance;
    if ( (double)Math_CeilSqrt(
                   (g_CastleSiteAnchorColumns[slot] - site_column) * (g_CastleSiteAnchorColumns[slot] - site_column)
                 + (g_CastleSiteAnchorRows[slot] - site_row) * (g_CastleSiteAnchorRows[slot] - site_row)) < candidate_distance )
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
int  Building_CalcGarrisonFactStrength(int building_index)
{
  int buildingOffset; // ebx
  int totalStrength; // edi
  int slotOffset; // ecx
  int slotPtr; // esi
  int meleeStrength; // eax
  int damageStrength; // eax

  buildingOffset = BUILDING_RECORD_SIZE * building_index;
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
int  Building_OnGarrisonChange(int building_index, int instance_record, double a3)
{
  int building_offset; // esi
  int result; // eax
  int previous_strength; // ebx
  _DWORD moc_value[2]; // [esp-4h] [ebp-28h] BYREF
  int *strength_value_ptr; // [esp+4h] [ebp-20h]
  int v11; // [esp+1Ch] [ebp-8h]

  v11 = instance_record;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  result = BUILDING_RECORD_SIZE * building_index + gameData;
  if ( *(_DWORD *)(result + 510137) )
  {
    moc_value[1] = 1;
    Rules_GetInstanceSlotValue(*(_DWORD *)(result + 510137), aMoc_1, building_index, moc_value);
    previous_strength = strength_value_ptr[4];
    result = Building_CalcGarrisonFactStrength(building_index);
    if ( previous_strength != result )
    {
      strength_value_ptr = Rules_AddIntegerValue(result);
      return Rules_PutInstanceSlotValue(*(_DWORD *)(building_offset + gameData + 510137), aMoc_2, instance_record, moc_value, a3);
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
signed int  UnitStack_HasUnitsNeedingHealing(int stack_index)
{
  int needs_healing; // esi
  __int16 *unit_slot; // eax
  int i; // edx
  int slot_unit_type; // ecx

  needs_healing = 0;
  unit_slot = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6);
  for ( i = 0; i < 10; ++i )
  {
    slot_unit_type = *unit_slot;
    if ( slot_unit_type == -1 )
      break;
    if ( *((char *)unit_slot + 9) <= 50 && (unsigned __int8)g_UnitTypeRole[88 * slot_unit_type] >= 3u )
      needs_healing = 1;
    unit_slot = (__int16 *)((char *)unit_slot + 31);
  }
  return needs_healing;
}
// 5202E4: using guessed type int gameData;

//----- (00457860) --------------------------------------------------------
BOOL  UnitStack_FindPathToNearestHospitalCastle(DWORD stack_index)
{
  int best_building_index; // edi
  int building_index; // ebx
  int building_record; // eax
  unsigned int building_status; // ecx
  _DWORD *track; // eax
  const void *track_ptr; // esi
  int track_cost; // eax
  int v9; // ecx
  int building_cursor; // [esp+0h] [ebp-28h]
  int best_cost; // [esp+8h] [ebp-20h]
  int track_info; // [esp+Ch] [ebp-1Ch]

  best_building_index = -1;
  building_index = 0;
  building_cursor = gameData + BUILDING_TABLE_OFFSET;
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  building_status = *(char *)(building_record + 4);
  if ( building_status < 4 && *(__int16 *)(building_record + 16) != -1 && (*(_DWORD *)(building_cursor + 416) & BUILDING_ADDON_FLAG_HOSPITAL) == 1 )
  {
    track = (_DWORD *)Building_GenerateApproachTrack(stack_index, building_index, building_status, building_index, stack_index);
    track_ptr = track;
    if ( track )
    {
      track_info = track[1];
      if ( best_building_index == -1 )
      {
        qmemcpy((void *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
        track_cost = HIWORD(track_info);
      }
      else
      {
        if ( HIWORD(track_info) >= best_cost )
          goto LABEL_9;
        j__nfree_();
        qmemcpy((void *)(v9 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track_ptr, UNIT_STACK_PATH_BYTES);
        track_cost = HIWORD(track_info);
      }
      best_building_index = building_index;
      best_cost = track_cost;
LABEL_9:
      j__nfree_();
    }
  }
  while ( 1 )
  {
    ++building_index;
    building_cursor += 467;
    if ( building_index >= 100 )
      return best_building_index != -1;
    if ( building_index >= 0 )
      goto LABEL_2;
  }
}
// 457945: conditional instruction was optimized away because ebx.4<64u
// 457899: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 45795C: variable 'v12' is possibly undefined
// 45797E: variable 'v9' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004579B0) --------------------------------------------------------
BOOL  UnitStack_ExecuteHealingPathAndCheckArrival(unsigned int stack_index, char a2, DWORD a3, double a4)
{
  int v4; // ecx

  UnitStack_ExecuteQueuedPath(stack_index, 1, a2, a3, a4);
  return *(__int16 *)(gameData + UNIT_STACK_STRIDE * v4 + 147180) == -1;
}
// 4579DE: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457A10) --------------------------------------------------------
const void * UnitStack_MoveToBuildingAndCheckArrival(unsigned int stack_index, int building_index, double a3)
{
  unsigned int building_x; // edi
  DWORD building_y; // ebp
  const void *result; // eax
  int queued_target_xy; // [esp+8h] [ebp-18h]

  building_x = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building_index + BUILDING_TABLE_OFFSET);
  building_y = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building_index + 509675);
  if ( !*(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 147490)
    || (queued_target_xy = *(_DWORD *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 320), (int)abs32(building_x - (unsigned __int8)queued_target_xy) >= 3)
    || (int)abs32(building_y - BYTE1(queued_target_xy)) >= 3
    || __PAIR64__(building_y, building_x) == __PAIR64__(BYTE1(queued_target_xy), (unsigned __int8)queued_target_xy) )
  {
    result = (const void *)Building_GenerateApproachTrack(stack_index, building_index, building_index, stack_index, building_y);
    if ( !result )
      return result;
    qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_PATH_OFFSET), result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
  }
  UnitStack_ExecuteQueuedPath(stack_index, 1, stack_index, building_y, a3);
  return (const void *)(*(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) == -1);
}
// 457A65: conditional instruction was optimized away because %var_20.4==0
// 5202E4: using guessed type int gameData;

//----- (00457BA0) --------------------------------------------------------
int  UnitStack_QueuePathNearBuilding(int stack_index, int building_index, char a3, DWORD a4)
{
  int result; // eax
  int v5; // ecx

  result = Building_GenerateNearApproachTrack(stack_index, building_index, stack_index, a3, a4);
  if ( result )
  {
    qmemcpy((void *)(UNIT_STACK_STRIDE * v5 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    return 1;
  }
  return result;
}
// 457BD7: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457C00) --------------------------------------------------------
int  Building_GetMaxEnemyStrengthUnderWalls(int building_index)
{
  int building_offset; // eax
  int building_x; // edx
  int building_y; // ecx
  int scan_x; // edi
  int scan_y; // edx
  int j; // ecx
  int stack_offset; // ebx
  int scan_x_end; // [esp+4h] [ebp-38h]
  int scan_y_start; // [esp+8h] [ebp-34h]
  int i; // [esp+Ch] [ebp-30h]
  int building_record_offset; // [esp+10h] [ebp-2Ch]
  int scan_y_end; // [esp+1Ch] [ebp-20h]
  int max_strength; // [esp+20h] [ebp-1Ch]

  building_offset = BUILDING_RECORD_SIZE * building_index;
  max_strength = 0;
  building_x = *(unsigned __int8 *)(gameData + building_offset + BUILDING_TABLE_OFFSET);
  building_y = *(unsigned __int8 *)(gameData + building_offset + 509675);
  building_record_offset = building_offset;
  scan_x = building_x - 1;
  scan_y_end = building_y + 2;
  scan_x_end = building_x + 2;
  scan_y_start = building_y - 1;
  for ( i = 200 * (building_x - 1); scan_x <= scan_x_end; i += 200 )
  {
    scan_y = scan_y_start;
    for ( j = 2 * scan_y_start; scan_y <= scan_y_end; j += 2 )
    {
      if ( scan_x >= 0
        && scan_x < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
        && scan_y >= 0
        && scan_y < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
        && *(unsigned __int16 *)(j + gameData + i + TILE_MAP_OFFSET) <= 0x1F4u
        && (unsigned int)*(__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(j + gameData + i + TILE_MAP_OFFSET) + 6) <= 0x28 )
      {
        stack_offset = UNIT_STACK_STRIDE * *(unsigned __int16 *)(j + gameData + i + TILE_MAP_OFFSET);
        if ( *(_BYTE *)(gameData + stack_offset + 147178) != *(_BYTE *)(gameData + building_record_offset + 509676)
          && UnitStack_CalcArmyFactStrength(gameData + UNIT_STACK_TABLE_OFFSET + stack_offset) > max_strength )
        {
          max_strength = UnitStack_CalcArmyFactStrength(stack_offset + gameData + UNIT_STACK_TABLE_OFFSET);
        }
      }
      ++scan_y;
    }
    ++scan_x;
  }
  return max_strength;
}
// 457CF5: simplified comparisons for 'ebx.4': <0 || >=29 became >=29u
// 457D5E: variable 'v5' is possibly undefined
// 457D5F: variable 'j' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457DA0) --------------------------------------------------------
int  Building_GetPlagueState(int building_index)
{
  return *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * building_index + 510109) & 7;
}
// 5202E4: using guessed type int gameData;

//----- (00457DC0) --------------------------------------------------------
signed int  UnitStack_HasPlagueByIndex(int stack_index)
{
  return UnitStack_HasPlague(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET);
}
// 5202E4: using guessed type int gameData;

//----- (00457E00) --------------------------------------------------------
BOOL  Unit_ExecuteQueuedPathAndCheckFinished(unsigned int stack_index, char a2, DWORD a3, double a4)
{
  int v4; // ecx

  UnitStack_ExecuteQueuedPath(stack_index, 1, a2, a3, a4);
  return *(_DWORD *)(gameData + UNIT_STACK_STRIDE * v4 + 147490) == 0;
}
// 457E2E: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00457E50) --------------------------------------------------------
int  Script_UnitAddToGroup(unsigned int unit_index, int group_index, DWORD a3, double a4)
{
  return Unit_AddToGroup(unit_index, group_index, 0, a3, a4);
}

//----- (00457E60) --------------------------------------------------------
BOOL  UnitStack_DetachWeakUnitsToAdjacentTile(int army_index, int dest_tile_y, int dest_tile_x, double a4)
{
  int weak_count; // ecx
  __int16 *unit_slot; // eax
  int selected_count; // esi
  int i; // edx
  int j; // eax
  int offset_y; // esi
  _DWORD selected_slot_list[10]; // [esp+4h] [ebp-50h] BYREF
  int v13; // [esp+2Ch] [ebp-28h]
  int found_exit_tile; // [esp+30h] [ebp-24h]
  int offset_x; // [esp+34h] [ebp-20h]
  __int16 *stack_record; // [esp+38h] [ebp-1Ch]

  v13 = army_index;
  weak_count = 0;
  stack_record = (__int16 *)(UNIT_STACK_STRIDE * army_index + gameData + UNIT_STACK_TABLE_OFFSET);
  unit_slot = stack_record + 3;
  selected_count = 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( *unit_slot == -1 )
      break;
    if ( *((char *)unit_slot + 9) <= 10 )
    {
      ++weak_count;
      ++selected_count;
      selected_slot_list[weak_count - 1] = i;
    }
    unit_slot = (__int16 *)((char *)unit_slot + 31);
  }
  if ( !selected_count || selected_count == Unit_GetSquadCount((int)stack_record) )
    return 0;
  for ( j = selected_count; j < 10; selected_slot_list[j - 1] = -1 )
  {
    ++j;
    ++selected_count;
  }
  found_exit_tile = 0;
  offset_x = -1;
  do
  {
    offset_y = -1;
    do
    {
      if ( offset_x || offset_y )
      {
        dest_tile_x = offset_x + *stack_record;
        dest_tile_y = offset_y + stack_record[1];
        if ( dest_tile_x >= 0
          && dest_tile_x < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
          && dest_tile_y >= 0
          && dest_tile_y < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Map_GetUnitTileMoveCostOrZero(*((unsigned __int8 *)stack_record + 4), 0, offset_y + stack_record[1], offset_x + *stack_record) )
        {
          found_exit_tile = 1;
        }
      }
      ++offset_y;
    }
    while ( offset_y <= 1 && !found_exit_tile );
    ++offset_x;
  }
  while ( offset_x <= 1 && !found_exit_tile );
  return found_exit_tile && Unit_MoveSelectionFromGroupToTile(v13, selected_slot_list, dest_tile_y, dest_tile_x, a4, 0);
}
// 457F19: conditional instruction was optimized away because %var_24.4==0
// 5202E4: using guessed type int gameData;

//----- (00457FE0) --------------------------------------------------------
BOOL  UnitStack_DetachUnitTypeToAdjacentTile(int army_index, unit_type type, int dest_tile_x, int dest_tile_y, double a5)
{
  int selected_count; // esi
  __int16 *unit_slot; // edx
  int match_count; // ecx
  int i; // eax
  int slot_type; // ebx
  int j; // eax
  int offset_y; // esi
  _DWORD selected_slot_list[10]; // [esp+4h] [ebp-50h] BYREF
  int v15; // [esp+2Ch] [ebp-28h]
  int v16; // [esp+30h] [ebp-24h]
  int found_exit_tile; // [esp+34h] [ebp-20h]
  int offset_x; // [esp+38h] [ebp-1Ch]
  __int16 *stack_record; // [esp+3Ch] [ebp-18h]

  v15 = army_index;
  v16 = type;
  selected_count = 0;
  stack_record = (__int16 *)(UNIT_STACK_STRIDE * army_index + gameData + UNIT_STACK_TABLE_OFFSET);
  unit_slot = stack_record + 3;
  match_count = 0;
  for ( i = 0; i < 10; ++i )
  {
    slot_type = *unit_slot;
    if ( slot_type == -1 )
      break;
    if ( slot_type == v16 )
    {
      ++match_count;
      ++selected_count;
      selected_slot_list[match_count - 1] = i;
    }
    unit_slot = (__int16 *)((char *)unit_slot + 31);
  }
  if ( !selected_count || selected_count == Unit_GetSquadCount((int)stack_record) )
    return 0;
  for ( j = selected_count; j < 10; selected_slot_list[j - 1] = -1 )
  {
    ++j;
    ++selected_count;
  }
  found_exit_tile = 0;
  offset_x = -1;
  do
  {
    offset_y = -1;
    do
    {
      if ( offset_x || offset_y )
      {
        dest_tile_x = offset_x + *stack_record;
        dest_tile_y = offset_y + stack_record[1];
        if ( dest_tile_x >= 0
          && dest_tile_x < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
          && dest_tile_y >= 0
          && dest_tile_y < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
          && Map_GetUnitTileMoveCostOrZero(*((unsigned __int8 *)stack_record + 4), 0, offset_y + stack_record[1], offset_x + *stack_record) )
        {
          found_exit_tile = 1;
        }
      }
      ++offset_y;
    }
    while ( offset_y <= 1 && !found_exit_tile );
    ++offset_x;
  }
  while ( offset_x <= 1 && !found_exit_tile );
  return found_exit_tile && Unit_MoveSelectionFromGroupToTile(v15, selected_slot_list, dest_tile_y, dest_tile_x, a5, 0);
}
// 458094: conditional instruction was optimized away because %var_20.4==0
// 5202E4: using guessed type int gameData;

//----- (00458160) --------------------------------------------------------
signed int  UnitStack_HasUnitType(int stack_index, unit_type sought_type)
{
  int slot_index; // edx
  __int16 *i; // eax
  int slot_unit_type; // ecx

  slot_index = 0;
  for ( i = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6); ; i = (__int16 *)((char *)i + 31) )
  {
    slot_unit_type = *i;
    if ( slot_unit_type == -1 )
      return 0;
    if ( slot_unit_type == sought_type )
      break;
    if ( ++slot_index >= 10 )
      return 0;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (004581C0) --------------------------------------------------------
signed int  UnitStack_HasOnlyUnitType(int stack_index, unit_type sought_type)
{
  int slot_index; // edx
  __int16 *i; // eax
  int slot_unit_type; // ecx

  slot_index = 0;
  for ( i = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6); ; i = (__int16 *)((char *)i + 31) )
  {
    slot_unit_type = *i;
    if ( slot_unit_type == -1 )
      return 1;
    if ( slot_unit_type != sought_type )
      break;
    if ( ++slot_index >= 10 )
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
signed int  UnitStack_GetHealthPercentAggregate(int stack_index, int aggregate_mode)
{
  int slot_base; // eax
  int unit_count; // ecx
  int aggregate_health; // edx
  __int16 *unit_slot; // eax
  int slot_health; // ebx

  slot_base = gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6;
  unit_count = 1;
  aggregate_health = *(char *)(slot_base + 9);
  unit_slot = (__int16 *)(slot_base + 31);
  while ( *unit_slot != -1 )
  {
    if ( aggregate_mode < 0 )
    {
      slot_health = *((char *)unit_slot + 9);
      if ( aggregate_health >= slot_health )
        goto LABEL_11;
    }
    else
    {
      if ( aggregate_mode <= 0 )
      {
        aggregate_health += *((char *)unit_slot + 9);
        goto LABEL_6;
      }
      slot_health = *((char *)unit_slot + 9);
      if ( aggregate_health <= slot_health )
LABEL_11:
        aggregate_health = slot_health;
    }
LABEL_6:
    ++unit_count;
    unit_slot = (__int16 *)((char *)unit_slot + 31);
    if ( unit_count >= 10 )
      break;
  }
  if ( !aggregate_mode )
    aggregate_health /= unit_count;
  return aggregate_health;
}
// 5202E4: using guessed type int gameData;

//----- (004582B0) --------------------------------------------------------
int  UnitStack_RegroupWithOtherStackByHealth(int a1, int a2, char a3, DWORD a4, double a5)
{
  int stack_index_reg; // edx
  int v6; // ecx
  int dx; // ebp
  __int64 dy; // rax
  int result; // eax
  int dx_second; // ebp
  int first_stack_offset; // ebx
  __int64 dx_recheck; // rax
  __int64 dy_second; // rax
  __int64 dy_recheck; // rax
  int copy_count_first; // ebp
  int first_stack_record; // edx
  _BYTE *copy_dest; // ebx
  __int16 *first_src_slot; // edx
  __int16 *second_src_slot; // edx
  int copy_count_second; // ebp
  _BYTE *copy_dest_second; // ebx
  int healthy_scan_offset; // ebx
  _BYTE *writeback_src; // ebp
  int writeback_index; // ebx
  _WORD *first_dest_slot; // edx
  signed int writeback_index_second; // ebp
  _WORD *second_dest_slot; // edx
  _BYTE *writeback_src_second; // ebx
  int compare_index; // ebp
  _BYTE *slot_a_ptr; // ebx
  _BYTE *slot_b_ptr; // edx
  _BYTE merged_units[620]; // [esp+0h] [ebp-2CCh] BYREF
  _BYTE swap_buf[28]; // [esp+26Ch] [ebp-60h] BYREF
  _BYTE swap_tail[3]; // [esp+288h] [ebp-44h] BYREF
  int stack_index; // [esp+28Ch] [ebp-40h]
  int other_stack_index; // [esp+290h] [ebp-3Ch]
  signed int units_kept_second; // [esp+294h] [ebp-38h]
  int sort_pass_limit; // [esp+298h] [ebp-34h]
  int sort_pass_offset; // [esp+29Ch] [ebp-30h]
  int units_kept_first; // [esp+2A0h] [ebp-2Ch]
  int sort_pass; // [esp+2A4h] [ebp-28h]
  int compare_base_index; // [esp+2A8h] [ebp-24h]
  int sort_done; // [esp+2ACh] [ebp-20h]
  int total_units; // [esp+2B0h] [ebp-1Ch]
  int compare_base_offset; // [esp+2B4h] [ebp-18h]

  stack_index = a1;
  other_stack_index = a2;
  Debug_Log(a1, a3, a4, (int)aPrzegrupujar_0);
  dx = *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index_reg + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET);
  if ( (int)abs32(dx) > 1
    || (dy = *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index_reg + 147176) - *(__int16 *)(UNIT_STACK_STRIDE * other_stack_index + gameData + 147176),
        (int)((HIDWORD(dy) ^ dy) - HIDWORD(dy)) > 1) )
  {
    result = (int)Unit_MoveTrackNearTile(
                    stack_index,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET),
                    v6,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * other_stack_index + 147176),
                    dx);
    if ( !result )
      return result;
    qmemcpy((void *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(stack_index, 1, -43 * stack_index, dx, a5);
  }
  dx_second = *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET);
  if ( (int)abs32(dx_second) > 1
    || (dy_second = *(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + 147176) - *(__int16 *)(UNIT_STACK_STRIDE * other_stack_index + gameData + 147176),
        (int)((HIDWORD(dy_second) ^ dy_second) - HIDWORD(dy_second)) > 1) )
  {
    result = (int)Unit_MoveTrackNearTile(
                    other_stack_index,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
                    v6,
                    *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
                    dx_second);
    if ( !result )
      return result;
    qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_PATH_OFFSET), (const void *)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(other_stack_index, 1, -111 * other_stack_index, dx_second, a5);
  }
  first_stack_offset = UNIT_STACK_STRIDE * stack_index;
  dx_recheck = *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(dx_recheck) ^ dx_recheck) - HIDWORD(dx_recheck)) > 1 )
    return 0;
  dy_recheck = *(__int16 *)(gameData + first_stack_offset + 147176) - *(__int16 *)(UNIT_STACK_STRIDE * other_stack_index + gameData + 147176);
  if ( (int)((HIDWORD(dy_recheck) ^ dy_recheck) - HIDWORD(dy_recheck)) > 1 )
    return 0;
  copy_count_first = 0;
  total_units = 0;
  first_stack_record = gameData + UNIT_STACK_TABLE_OFFSET + first_stack_offset;
  copy_dest = merged_units;
  first_src_slot = (__int16 *)(first_stack_record + 6);
  do
  {
    if ( *first_src_slot == -1 )
      break;
    qmemcpy(copy_dest, first_src_slot, 0x1Cu);
    qmemcpy(copy_dest + 28, first_src_slot + 14, 3u);
    ++copy_count_first;
    first_src_slot = (__int16 *)((char *)first_src_slot + 31);
    copy_dest += 31;
    ++total_units;
  }
  while ( copy_count_first < 10 );
  second_src_slot = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * other_stack_index + 6);
  copy_count_second = 0;
  copy_dest_second = &merged_units[31 * total_units];
  do
  {
    if ( *second_src_slot == -1 )
      break;
    qmemcpy(copy_dest_second, second_src_slot, 0x1Cu);
    qmemcpy(copy_dest_second + 28, second_src_slot + 14, 3u);
    ++copy_count_second;
    second_src_slot = (__int16 *)((char *)second_src_slot + 31);
    copy_dest_second += 31;
    ++total_units;
  }
  while ( copy_count_second < 10 );
  sort_done = 0;
  if ( total_units > 1 )
  {
    sort_pass = 0;
    sort_pass_offset = 31;
    sort_pass_limit = total_units - 1;
    do
    {
      if ( sort_done )
        break;
      sort_done = 1;
      compare_index = 1;
      if ( total_units > 1 )
      {
        compare_base_index = sort_pass;
        compare_base_offset = sort_pass_offset;
        do
        {
          if ( merged_units[31 * compare_base_index + 9] > merged_units[compare_base_offset + 9] )
          {
            sort_done = 0;
            slot_a_ptr = &merged_units[31 * compare_base_index];
            qmemcpy(swap_buf, slot_a_ptr, sizeof(swap_buf));
            qmemcpy(swap_tail, slot_a_ptr + 28, sizeof(swap_tail));
            slot_b_ptr = &merged_units[compare_base_offset];
            qmemcpy(slot_a_ptr, &merged_units[compare_base_offset], 0x1Cu);
            qmemcpy(slot_a_ptr + 28, slot_b_ptr + 28, 3u);
            qmemcpy(slot_b_ptr, swap_buf, 0x1Cu);
            qmemcpy(slot_b_ptr + 28, swap_tail, 3u);
          }
          ++compare_index;
        }
        while ( compare_index < total_units );
      }
      sort_pass_offset += 31;
      ++sort_pass;
    }
    while ( sort_pass < sort_pass_limit );
  }
  units_kept_first = 0;
  if ( total_units > 0 )
  {
    healthy_scan_offset = 0;
    do
    {
      if ( (char)merged_units[healthy_scan_offset + 9] >= 8 )
        ++units_kept_first;
      healthy_scan_offset += 31;
    }
    while ( healthy_scan_offset < 31 * total_units );
  }
  if ( units_kept_first > 10 )
    units_kept_first = 10;
  if ( total_units - 10 > units_kept_first )
    units_kept_first = total_units - 10;
  writeback_src = merged_units;
  writeback_index = 0;
  first_dest_slot = (_WORD *)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  do
  {
    if ( writeback_index >= units_kept_first )
    {
      *first_dest_slot = -1;
    }
    else
    {
      qmemcpy(first_dest_slot, writeback_src, 0x1Cu);
      qmemcpy(first_dest_slot + 14, writeback_src + 28, 3u);
    }
    writeback_src += 31;
    ++writeback_index;
    first_dest_slot = (_WORD *)((char *)first_dest_slot + 31);
  }
  while ( writeback_index < 10 );
  units_kept_second = total_units - units_kept_first;
  writeback_index_second = 0;
  second_dest_slot = (_WORD *)(UNIT_STACK_STRIDE * other_stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  writeback_src_second = &merged_units[31 * units_kept_first];
  do
  {
    if ( writeback_index_second >= units_kept_second )
    {
      *second_dest_slot = -1;
    }
    else
    {
      qmemcpy(second_dest_slot, writeback_src_second, 0x1Cu);
      qmemcpy(second_dest_slot + 14, writeback_src_second + 28, 3u);
    }
    writeback_src_second += 31;
    ++writeback_index_second;
    second_dest_slot = (_WORD *)((char *)second_dest_slot + 31);
  }
  while ( writeback_index_second < 10 );
  if ( !units_kept_first )
    UnitStack_KillByIndex(stack_index, (char)writeback_src_second, writeback_index_second, a5);
  if ( units_kept_first == total_units )
    UnitStack_KillByIndex(other_stack_index, (char)writeback_src_second, writeback_index_second, a5);
  return 1;
}
// 4582F8: variable 'v5' is possibly undefined
// 45839D: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (004589C0) --------------------------------------------------------
signed int  UnitStack_RegroupWithBuildingGarrisonByHealth(int army_index, int building_index, char a3, DWORD a4, double a5)
{
  int building_offset; // edi
  int v6; // ecx
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rax
  int v11; // ebx
  int dx; // ebp
  const void *approach_track; // eax
  int v14; // edx
  __int64 v15; // rax
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  int first_copy_count; // ebp
  _BYTE *merge_cursor; // ebx
  __int16 *first_source_slot; // edx
  int garrison_copy_count; // ebp
  __int16 *garrison_source_slot; // edx
  _BYTE *garrison_merge_cursor; // ebx
  int healthy_scan_offset; // edx
  _BYTE *writeback_cursor; // ebp
  int first_write_index; // ebx
  _WORD *first_dest_slot; // edx
  int garrison_write_index; // ebx
  _WORD *garrison_dest_slot; // edx
  _BYTE *garrison_writeback_cursor; // ebp
  __int64 v34; // rax
  __int64 v35; // rax
  __int64 v36; // rax
  __int64 v37; // rax
  __int64 v38; // rax
  __int64 v39; // rax
  int inner_index; // ebp
  _BYTE *swap_a; // edx
  _BYTE *swap_b; // ebx
  _BYTE merged_units[684]; // [esp+0h] [ebp-30Ch] BYREF
  _BYTE swap_buffer[28]; // [esp+2ACh] [ebp-60h] BYREF
  _BYTE swap_tail[3]; // [esp+2C8h] [ebp-44h] BYREF
  int building; // [esp+2CCh] [ebp-40h]
  int army; // [esp+2D0h] [ebp-3Ch]
  int remainder_count; // [esp+2D4h] [ebp-38h]
  int sort_limit; // [esp+2D8h] [ebp-34h]
  int sorted_flag; // [esp+2DCh] [ebp-30h]
  int outer_offset; // [esp+2E0h] [ebp-2Ch]
  int keep_count; // [esp+2E4h] [ebp-28h]
  int outer_index; // [esp+2E8h] [ebp-24h]
  int compare_index; // [esp+2ECh] [ebp-20h]
  int total_units; // [esp+2F0h] [ebp-1Ch]
  int compare_offset; // [esp+2F4h] [ebp-18h]

  army = army_index;
  building = building_index;
  building_offset = BUILDING_RECORD_SIZE * building_index;
  Debug_Log(army_index, a3, a4, (int)aPrzegrupujza_0);
  v7 = *(unsigned __int8 *)(gameData + building_offset + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * v6 + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(v7) ^ v7) - HIDWORD(v7)) > 1
    || (v8 = *(unsigned __int8 *)(building_offset + gameData + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * v6 + gameData + 147176),
        (int)((HIDWORD(v8) ^ v8) - HIDWORD(v8)) > 1) )
  {
    v9 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( (int)((HIDWORD(v9) ^ v9) - HIDWORD(v9)) > 1
      || (v34 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + 147176),
          (int)((HIDWORD(v34) ^ v34) - HIDWORD(v34)) > 1) )
    {
      v10 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(gameData + UNIT_STACK_STRIDE * army + UNIT_STACK_TABLE_OFFSET);
      if ( (int)((HIDWORD(v10) ^ v10) - HIDWORD(v10)) > 1
        || (v35 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * building + gameData + 509675) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + 147176),
            (int)((HIDWORD(v35) ^ v35) - HIDWORD(v35)) > 1) )
      {
        v11 = UNIT_STACK_STRIDE * army;
        dx = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * army + UNIT_STACK_TABLE_OFFSET);
        if ( (int)abs32(dx) > 1
          || (v11 = *(__int16 *)(v11 + gameData + 147176),
              v36 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * building + gameData + 509675) + 1 - v11,
              (int)((HIDWORD(v36) ^ v36) - HIDWORD(v36)) > 1) )
        {
          approach_track = (const void *)Building_GenerateNearApproachTrack(army, building, v6, v11, dx);
          if ( !approach_track )
            return 0;
          qmemcpy((void *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * army + UNIT_STACK_PATH_OFFSET), approach_track, UNIT_STACK_PATH_BYTES);
          j__nfree_();
          UnitStack_ExecuteQueuedPath(army, v14, -111 * army, dx, a5);
        }
      }
    }
  }
  v15 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * army + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(v15) ^ v15) - HIDWORD(v15)) > 1
    || (v37 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * building + gameData + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + 147176),
        (int)((HIDWORD(v37) ^ v37) - HIDWORD(v37)) > 1) )
  {
    v16 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + UNIT_STACK_TABLE_OFFSET);
    if ( (int)((HIDWORD(v16) ^ v16) - HIDWORD(v16)) > 1
      || (v38 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * building + gameData + 509675) - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + 147176),
          (int)((HIDWORD(v38) ^ v38) - HIDWORD(v38)) > 1) )
    {
      v17 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) + 1 - *(__int16 *)(gameData + UNIT_STACK_STRIDE * army + UNIT_STACK_TABLE_OFFSET);
      if ( (int)((HIDWORD(v17) ^ v17) - HIDWORD(v17)) > 1
        || (v39 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + 509675) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + 147176),
            (int)((HIDWORD(v39) ^ v39) - HIDWORD(v39)) > 1) )
      {
        v18 = *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * building + BUILDING_TABLE_OFFSET) - *(__int16 *)(gameData + UNIT_STACK_STRIDE * army + UNIT_STACK_TABLE_OFFSET);
        if ( (int)((HIDWORD(v18) ^ v18) - HIDWORD(v18)) > 1 )
          return 0;
        v19 = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * building + gameData + 509675) + 1 - *(__int16 *)(UNIT_STACK_STRIDE * army + gameData + 147176);
        if ( (int)((HIDWORD(v19) ^ v19) - HIDWORD(v19)) > 1 )
          return 0;
      }
    }
  }
  total_units = 0;
  first_copy_count = 0;
  merge_cursor = merged_units;
  first_source_slot = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * army + 6);
  do
  {
    if ( *first_source_slot == -1 )
      break;
    qmemcpy(merge_cursor, first_source_slot, 0x1Cu);
    qmemcpy(merge_cursor + 28, first_source_slot + 14, 3u);
    ++first_copy_count;
    first_source_slot = (__int16 *)((char *)first_source_slot + 31);
    merge_cursor += 31;
    ++total_units;
  }
  while ( first_copy_count < 10 );
  garrison_copy_count = 0;
  garrison_source_slot = (__int16 *)(UNIT_RECORD(building) + 18);
  garrison_merge_cursor = &merged_units[31 * total_units];
  do
  {
    if ( *garrison_source_slot == -1 )
      break;
    qmemcpy(garrison_merge_cursor, garrison_source_slot, 0x1Cu);
    qmemcpy(garrison_merge_cursor + 28, garrison_source_slot + 14, 3u);
    ++garrison_copy_count;
    garrison_source_slot = (__int16 *)((char *)garrison_source_slot + 31);
    garrison_merge_cursor += 31;
    ++total_units;
  }
  while ( garrison_copy_count < 12 );
  sorted_flag = 0;
  if ( total_units > 1 )
  {
    outer_index = 0;
    outer_offset = 31;
    sort_limit = total_units - 1;
    do
    {
      if ( sorted_flag )
        break;
      inner_index = 1;
      sorted_flag = 1;
      if ( total_units > 1 )
      {
        compare_index = outer_index;
        compare_offset = outer_offset;
        do
        {
          if ( merged_units[31 * compare_index + 9] > merged_units[compare_offset + 9] )
          {
            sorted_flag = 0;
            swap_a = &merged_units[31 * compare_index];
            qmemcpy(swap_buffer, swap_a, sizeof(swap_buffer));
            qmemcpy(swap_tail, swap_a + 28, sizeof(swap_tail));
            swap_b = &merged_units[compare_offset];
            qmemcpy(swap_a, &merged_units[compare_offset], 0x1Cu);
            qmemcpy(swap_a + 28, swap_b + 28, 3u);
            qmemcpy(swap_b, swap_buffer, 0x1Cu);
            qmemcpy(swap_b + 28, swap_tail, 3u);
          }
          ++inner_index;
        }
        while ( inner_index < total_units );
      }
      outer_offset += 31;
      ++outer_index;
    }
    while ( outer_index < sort_limit );
  }
  healthy_scan_offset = 0;
  keep_count = 0;
  if ( total_units > 0 )
  {
    do
    {
      if ( (char)merged_units[healthy_scan_offset + 9] >= 8 )
        ++keep_count;
      healthy_scan_offset += 31;
    }
    while ( healthy_scan_offset < 31 * total_units );
  }
  if ( keep_count > 10 )
    keep_count = 10;
  if ( total_units - 12 > keep_count )
    keep_count = total_units - 12;
  writeback_cursor = merged_units;
  first_write_index = 0;
  first_dest_slot = (_WORD *)(UNIT_STACK_STRIDE * army + gameData + UNIT_STACK_TABLE_OFFSET + 6);
  do
  {
    if ( first_write_index >= keep_count )
    {
      *first_dest_slot = -1;
    }
    else
    {
      qmemcpy(first_dest_slot, writeback_cursor, 0x1Cu);
      qmemcpy(first_dest_slot + 14, writeback_cursor + 28, 3u);
    }
    writeback_cursor += 31;
    ++first_write_index;
    first_dest_slot = (_WORD *)((char *)first_dest_slot + 31);
  }
  while ( first_write_index < 10 );
  garrison_write_index = 0;
  remainder_count = total_units - keep_count;
  garrison_dest_slot = (_WORD *)(UNIT_RECORD(building) + 18);
  garrison_writeback_cursor = &merged_units[31 * keep_count];
  do
  {
    if ( garrison_write_index >= remainder_count )
    {
      *garrison_dest_slot = -1;
    }
    else
    {
      qmemcpy(garrison_dest_slot, garrison_writeback_cursor, 0x1Cu);
      qmemcpy(garrison_dest_slot + 14, garrison_writeback_cursor + 28, 3u);
    }
    garrison_writeback_cursor += 31;
    ++garrison_write_index;
    garrison_dest_slot = (_WORD *)((char *)garrison_dest_slot + 31);
  }
  while ( garrison_write_index < 12 );
  if ( !keep_count )
    UnitStack_KillByIndex(army, garrison_write_index, (DWORD)garrison_writeback_cursor, a5);
  return 1;
}
// 458A0D: variable 'v6' is possibly undefined
// 458BBF: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00459230) --------------------------------------------------------
double  AI_CalcStrategicPriorityScore(int target_type, DWORD tile_x, int origin_x, int tile_y, int origin_y)
{
  int file; // ecx
  int v8; // ecx
  _BYTE line_buffer[80]; // [esp+0h] [ebp-70h] BYREF
  int entry_type; // [esp+50h] [ebp-20h] BYREF
  float entry_weight; // [esp+54h] [ebp-1Ch] BYREF
  int origin_x_saved; // [esp+58h] [ebp-18h]
  float weight; // [esp+5Ch] [ebp-14h]
  signed int distance; // [esp+60h] [ebp-10h]

  origin_x_saved = origin_x;
  weight = -1.0;
  file = IO_FOpen(aStrategprior, (unsigned __int8 *)aR, origin_x, tile_x);
  if ( file )
  {
    while ( fgets_(line_buffer, 80, file) )
    {
      sscanf_(line_buffer, "%d %f", &entry_type, &entry_weight);
      if ( target_type == entry_type )
        weight = entry_weight;
    }
  }
  fclose_(file);
  distance = Math_CeilSqrt((origin_x_saved - tile_x) * (origin_x_saved - tile_x) + (origin_y - tile_y) * (origin_y - tile_y));
  return weight / (double)distance;
}
// 459267: variable 'v7' is possibly undefined
// 4592B5: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4841D3: using guessed type int __fastcall fgets_(_DWORD, _DWORD);
// 48429C: using guessed type _DWORD sscanf_(_DWORD, _DWORD, ...);

//----- (004592E0) --------------------------------------------------------
void  AI_EvaluateStrategicTargetAtTile(
        int filter_type,
        int filter_owner,
        int tile_y,
        int tile_x,
        int origin_x,
        int origin_y,
        int *best_type_out,
        int *best_target_out,
        float *best_score_out)
{
  int target_id; // ebp
  int target_type; // edi
  unsigned int building_id; // eax
  int building_record; // edx
  double score; // st7
  int v16; // [esp+0h] [ebp-20h]
  float score_float; // [esp+8h] [ebp-18h]

  target_id = -1;
  if ( tile_x >= 0 && tile_x < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) && tile_y >= 0 && tile_y < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
  {
    if ( *(unsigned __int16 *)(TILE_INDEX(tile_x, tile_y)) > 0x1F4u
      || (unsigned int)*(__int16 *)(gameData
                                  + UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(tile_x, tile_y))
                                  + 147180) > 0x28 )
    {
      building_id = *(unsigned __int16 *)(TILE_INDEX(tile_x, tile_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
      if ( building_id > 0x64
        || (building_record = UNIT_RECORD(building_id), (unsigned int)*(char *)(building_record + 4) >= 4)
        || *(__int16 *)(building_record + 16) == -1 )
      {
        if ( MapTile_HasHiddenTreasure(tile_x, tile_y) )
        {
          target_type = 3;
        }
        else
        {
          if ( !MapTile_GetReligiousSiteCategory(tile_x, tile_y) )
            return;
          target_type = 4;
        }
      }
      else
      {
        target_type = 1;
        target_id = *(unsigned __int16 *)(TILE_INDEX(tile_x, tile_y)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
      }
    }
    else
    {
      target_type = 2;
      target_id = *(unsigned __int16 *)(TILE_INDEX(tile_x, tile_y));
    }
    if ( (filter_type == -1 || target_type == filter_type)
      && (filter_owner == -1
       || (target_type != 1 || *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * target_id + 509676) == filter_owner)
       && (target_type != 2 || *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * target_id + 147178) == filter_owner)) )
    {
      AI_CalcStrategicPriorityScore(target_type, tile_x, origin_x, tile_y, origin_y);
      score = (double)(int)_CHP(v16, filter_type);
      if ( score > *best_score_out )
      {
        *best_type_out = target_type;
        *best_target_out = target_id;
        score_float = score;
        *best_score_out = score_float;
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
int  AI_FindBestStrategicTargetNearTile(int type_filter, int owner_filter, int origin_x, int origin_y, signed int search_radius)
{
  int tile_y; // esi
  int tile_x; // edi
  int scan_y; // ebx
  int scan_x; // ecx
  int best_type; // [esp+0h] [ebp-48h] BYREF
  int best_target; // [esp+4h] [ebp-44h] BYREF
  int best_score_bits; // [esp+8h] [ebp-40h] BYREF
  int y_min; // [esp+Ch] [ebp-3Ch]
  int x_max; // [esp+10h] [ebp-38h]
  int x_min; // [esp+14h] [ebp-34h]
  int y_max; // [esp+18h] [ebp-30h]
  signed int ring_radius; // [esp+1Ch] [ebp-2Ch]
  int i; // [esp+20h] [ebp-28h]
  int v20; // [esp+24h] [ebp-24h]
  int v21; // [esp+28h] [ebp-20h]
  int v22; // [esp+2Ch] [ebp-1Ch]
  int owner_filter_saved; // [esp+30h] [ebp-18h]
  int center_x; // [esp+34h] [ebp-14h]
  int center_y; // [esp+38h] [ebp-10h]

  owner_filter_saved = owner_filter;
  center_y = origin_y;
  center_x = origin_x;
  best_type = -1;
  best_target = -1;
  best_score_bits = -1082130432;
  ring_radius = 1;
  if ( search_radius >= 1 )
  {
    y_max = center_y + 1;
    x_min = origin_x - 1;
    y_min = center_y - 1;
    x_max = origin_x + 1;
    do
    {
      tile_y = center_y - ring_radius;
      tile_x = ring_radius + center_x;
      for ( i = y_max; tile_y < i; ++tile_y )
        AI_EvaluateStrategicTargetAtTile(type_filter, owner_filter_saved, tile_x, tile_y, center_y, center_x, &best_type, &best_target, (float *)&best_score_bits);
      v21 = x_min;
      while ( tile_x > v21 )
        AI_EvaluateStrategicTargetAtTile(type_filter, owner_filter_saved, tile_x--, tile_y, center_y, center_x, &best_type, &best_target, (float *)&best_score_bits);
      v20 = y_min;
      while ( tile_y > v20 )
      {
        scan_y = tile_y--;
        AI_EvaluateStrategicTargetAtTile(type_filter, owner_filter_saved, tile_x, scan_y, center_y, center_x, &best_type, &best_target, (float *)&best_score_bits);
      }
      v22 = x_max;
      while ( tile_x < v22 )
      {
        scan_x = tile_x++;
        AI_EvaluateStrategicTargetAtTile(type_filter, owner_filter_saved, scan_x, tile_y, center_y, center_x, &best_type, &best_target, (float *)&best_score_bits);
      }
      ++y_max;
      --x_min;
      --y_min;
      ++x_max;
      ++ring_radius;
    }
    while ( ring_radius <= search_radius );
  }
  if ( best_type == -1 )
    return -1;
  if ( best_type == 3 || best_type == 4 )
    return 100 * best_type;
  return best_target + 100 * best_type;
}

//----- (00459760) --------------------------------------------------------
signed int  createUnit(double a1, int tile_x, int tile_y, int player_index, unit_type first_unit_type, unit_type second_unit_type, ...)
{
  va_list args;
  char owner; // bl
  int stack_id; // ecx
  unit_type next_unit_type; // eax
  DWORD tile_x_offset; // ebp
  int slot_offset; // ecx
  int tile_offset; // [esp+0h] [ebp-1Ch]

  va_start(args, second_unit_type);
  Unit_Create(first_unit_type, player_index, tile_x, 0, a1, tile_y);
  owner = player_index;
  slot_offset = 31;
  next_unit_type = second_unit_type;
  tile_x_offset = 200 * tile_x;
  tile_offset = 2 * tile_y;
  while ( next_unit_type != -1 )
  {
    stack_id = *(unsigned __int16 *)(tile_offset + gameData + tile_x_offset + TILE_MAP_OFFSET);
    UnitSlot_InitFromType(slot_offset + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_id + 6, next_unit_type, player_index);
    next_unit_type = va_arg(args, int);
    slot_offset += 31;
  }
  va_end(args);
  return Rules_SyncArmyFactStrength(
           gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(tile_offset + gameData + tile_x_offset + TILE_MAP_OFFSET),
           145 * *(unsigned __int16 *)(tile_offset + gameData + tile_x_offset + TILE_MAP_OFFSET),
           gameData + UNIT_STACK_TABLE_OFFSET,
           owner,
           tile_x_offset,
           a1);
}
// 5202E4: using guessed type int gameData;

//----- (00459860) --------------------------------------------------------
int  createCastle(
        double st7_0,
        int tile_x,
        int tile_y,
        int player_index,
        int building_type,
        char *castle_name,
        unit_type first_unit_type,
        unit_type second_unit_type,
        ...)
{
  va_list args;
  int stack_id; // eax
  int slot_offset; // ecx
  unit_type next_unit_type; // eax
  int unit_index; // eax
  int tile_offset; // [esp+0h] [ebp-20h]
  DWORD tile_x_offset; // [esp+4h] [ebp-1Ch]

  va_start(args, second_unit_type);
  Diagnostics_TraceBootstrapEvent("createCastle-unit-create");
  Unit_Create(first_unit_type, player_index, tile_x, 0, tile_y);
  Diagnostics_TraceBootstrapEvent("createCastle-fill-slots");
  tile_x_offset = 200 * tile_x;
  next_unit_type = second_unit_type;
  slot_offset = 31;
  tile_offset = 2 * tile_y;
  while ( next_unit_type != -1 )
  {
    stack_id = *(unsigned __int16 *)(tile_offset + gameData + tile_x_offset + TILE_MAP_OFFSET);
    UnitSlot_InitFromType(slot_offset + UNIT_STACK_STRIDE * stack_id + gameData + UNIT_STACK_TABLE_OFFSET + 6, next_unit_type, player_index);
    next_unit_type = va_arg(args, int);
    slot_offset += 31;
  }
  va_end(args);
  Rules_SyncArmyFactStrength(
    (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(tile_offset + gameData + tile_x_offset + TILE_MAP_OFFSET)),
    145 * *(unsigned __int16 *)(tile_offset + gameData + tile_x_offset + TILE_MAP_OFFSET),
    gameData + UNIT_STACK_TABLE_OFFSET,
    tile_offset,
    tile_x_offset,
    st7_0);
  Diagnostics_TraceBootstrapEvent("createCastle-building-new");
  Building_New(building_type, *(unsigned __int16 *)(tile_offset + tile_x_offset + gameData + TILE_MAP_OFFSET), st7_0, castle_name, 1);
  Diagnostics_TraceBootstrapEvent("createCastle-post-building-new");
  unit_index = *(unsigned __int16 *)(tile_offset + tile_x_offset + gameData + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
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
int  WorldMap_DrawMission01ShrineMarker(int result, int tile_y, int screen_y, int screen_x)
{
  int now; // eax
  int SpriteForChar; // eax
  int pulse_brightness; // [esp-14h] [ebp-18h]

  if ( result == 16 && tile_y == 11 )
  {
    now = Time_Now(screen_y, 11);
    pulse_brightness = ((50 * Math_SinDegreesQ16(2 * now - 90)) >> 16) + 50;
    SpriteForChar = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 730);
    return Sprite_DrawSimpleIgnoringRect(SpriteForChar, screen_x, screen_y, screen_y, screen_x + 63, screen_y + 63, pulse_brightness, 0, 0, 0, 1u);
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
int  WorldMap_DrawMission07TreasureMarker(int result, int tile_y)
{
  int tile_x; // esi

  tile_x = result;
  if ( result == 55 && tile_y == 45 && (result = MapTile_HasHiddenTreasure(55, 45)) != 0
    || tile_x == 50 && tile_y == 27 && (result = MapTile_HasHiddenTreasure(50, 27)) != 0
    || tile_x == 35 && tile_y == 63 && (result = MapTile_HasHiddenTreasure(35, 63)) != 0 )
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
  else if ( tile_x == 14 && tile_y == 68 )
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
int  WorldMap_DrawMission11ShrineMarker(int result, int tile_y, int screen_y, int screen_x)
{
  int now; // eax
  int SpriteForChar; // eax
  int pulse_brightness; // [esp-Ch] [ebp-10h]

  if ( result == 2 && tile_y == 44 )
  {
    now = Time_Now(screen_y, 44);
    pulse_brightness = ((50 * Math_SinDegreesQ16(2 * now - 90)) >> 16) + 50;
    SpriteForChar = DLX_GetSpriteForChar(g_WorldMapBackgroundSpriteSet, 738);
    return Sprite_DrawSimpleIgnoringRect(SpriteForChar, screen_x, screen_y, screen_y, screen_x + 63, screen_y + 63, 0, 0, pulse_brightness, 0, 1u);
  }
  return result;
}
// 5202C0: using guessed type int dword_5202C0;

//----- (0045E630) --------------------------------------------------------
int  Mission_MarkObjective15CompleteOnAttack(int result, int target_owner_index)
{
  if ( result == 1 && (target_owner_index == 2 || target_owner_index == 3) )
  {
    result = gameData;
    MISSION_FAILURE_FLAG = 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0045F190) --------------------------------------------------------
int  WorldMap_DrawMission17TreasureMarker(int result, int tile_y)
{
  int tile_x; // esi

  tile_x = result;
  if ( result == 50 && tile_y == 34 && (result = MapTile_HasHiddenTreasure(50, 34)) != 0
    || tile_x == 51 && tile_y == 73 && (result = MapTile_HasHiddenTreasure(51, 73)) != 0
    || tile_x == 77 && tile_y == 34 && (result = MapTile_HasHiddenTreasure(77, 34)) != 0
    || tile_x == 24 && tile_y == 49 && (result = MapTile_HasHiddenTreasure(24, 49)) != 0 )
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
  int mission0_stack_index; // edx
  int building_scan_index; // eax
  int building_record; // ecx
  int building_owner; // edx
  int stack_scan_index; // edx
  int stack_owner; // eax
  int enemy_building_index; // eax
  int enemy_building_record; // edx
  int enemy_stack_index; // edx
  BOOL all_treasures_taken; // eax
  BOOL objective_met; // edi
  int kill_stack_index; // ecx
  int kill_stack_offset; // esi
  int kill_stack_record; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int garrison_slot_offset; // eax
  int player_offset; // eax
  int owner2_stack_index; // edx
  int owner4_building_index; // eax
  int owner4_building_record; // ecx
  int owner4_stack_index; // edx
  BOOL treasures_taken_m17; // eax
  int kill_stack_index_m17; // ecx
  int kill_stack_offset_m17; // esi
  int kill_stack_record_m17; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // ecx
  int personage_count; // ecx
  int i; // eax
  int garrison_unit_type; // edx
  int ally_offset; // eax
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
      mission0_stack_index = 0;
LABEL_6:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * mission0_stack_index + 147180) <= 0x28
        && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * mission0_stack_index + 147178) == 1 )
      {
        if ( mission0_last_blocker_index != mission0_stack_index || mission0_last_blocker_turn != GAME_TURN_COUNTER )
        {
          mission0_last_blocker_index = mission0_stack_index;
          mission0_last_blocker_turn = GAME_TURN_COUNTER;
          Diagnostics_TraceWorldMapActionEvent(
            "mission_objective_blocked",
            mission0_stack_index,
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * mission0_stack_index + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * mission0_stack_index + 147176),
            Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * mission0_stack_index));
        }
        return 0;
      }
      while ( ++mission0_stack_index < 500 )
      {
        if ( mission0_stack_index >= 0 )
          goto LABEL_6;
      }
      return 1;
    case 1:
      if ( MapTile_GetReligiousSiteCategory(16, 11) == RELIGIOUS_SITE_CATEGORY_EMPTY_SHRINE )
        return 1;
      Mission_TraceObjectiveBlocked(1, 16, 11, MapTile_GetReligiousSiteCategory(16, 11));
      return 0;
    case 2:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 564710) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) == 0 )
        return 1;
      Mission_TraceObjectiveBlocked(
        2,
        41,
        68,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 564710) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676));
      return 0;
    case 3:
    case 0xD:
      if ( *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) > 0xAu )
        return 1;
      Mission_TraceObjectiveBlocked(ACTIVE_MISSION_INDEX, *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET), 10, 0);
      return 0;
    case 4:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 567712) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) == 0 )
        return 1;
      Mission_TraceObjectiveBlocked(
        4,
        56,
        69,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 567712) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676));
      return 0;
    case 5:
      building_scan_index = (unsigned __int8)g_LanguageIndex;
      if ( g_LanguageIndex )
      {
        enemy_building_index = 0;
LABEL_35:
        enemy_building_record = UNIT_RECORD(enemy_building_index);
        if ( (unsigned int)*(char *)(enemy_building_record + 4) >= 4
          || *(__int16 *)(enemy_building_record + 16) == -1
          || *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * enemy_building_index + 509676) != 3 )
        {
          while ( ++enemy_building_index < 100 )
          {
            if ( enemy_building_index >= 0 )
              goto LABEL_35;
          }
          enemy_stack_index = 0;
LABEL_42:
          if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * enemy_stack_index + 147180) > 0x28
            || *(_BYTE *)(gameData + UNIT_STACK_STRIDE * enemy_stack_index + 147178) != 3 )
          {
            while ( ++enemy_stack_index < 500 )
            {
              if ( enemy_stack_index >= 0 )
                goto LABEL_42;
            }
            return 1;
          }
          Mission_TraceObjectiveBlocked(5, enemy_stack_index, *(_BYTE *)(gameData + UNIT_STACK_STRIDE * enemy_stack_index + 147178), Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * enemy_stack_index));
          return 0;
        }
        Mission_TraceObjectiveBlocked(5, enemy_building_index, *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * enemy_building_index + 509676), *(__int16 *)(enemy_building_record + 16));
        return 0;
      }
LABEL_18:
      building_record = UNIT_RECORD(building_scan_index);
      if ( (unsigned int)*(char *)(building_record + 4) < 4 && *(__int16 *)(building_record + 16) != -1 )
      {
        building_owner = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * building_scan_index + gameData + 509676);
        if ( building_owner == 1 || building_owner == 2 )
        {
          Mission_TraceObjectiveBlocked(5, building_scan_index, building_owner, *(__int16 *)(building_record + 16));
          return 0;
        }
      }
      while ( ++building_scan_index < 100 )
      {
        if ( building_scan_index >= 0 )
          goto LABEL_18;
      }
      stack_scan_index = 0;
LABEL_27:
      if ( (unsigned int)*(__int16 *)(UNIT_STACK_STRIDE * stack_scan_index + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28 )
      {
        stack_owner = *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * stack_scan_index + 147178);
        if ( stack_owner == 1 || stack_owner == 2 )
        {
          Mission_TraceObjectiveBlocked(5, stack_scan_index, stack_owner, Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_scan_index));
          return 0;
        }
      }
      while ( ++stack_scan_index < 500 )
      {
        if ( stack_scan_index >= 0 )
          goto LABEL_27;
      }
      return 1;
    case 6:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574456) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) == 0 )
        return 1;
      Mission_TraceObjectiveBlocked(
        6,
        90,
        41,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574456) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676));
      return 0;
    case 7:
      all_treasures_taken = !MapTile_HasHiddenTreasure(55, 45) && !MapTile_HasHiddenTreasure(50, 27) && !MapTile_HasHiddenTreasure(35, 63) && !MapTile_HasHiddenTreasure(14, 68);
      objective_met = all_treasures_taken;
      if ( !all_treasures_taken )
      {
        Mission_TraceObjectiveBlocked(
          7,
          55,
          45,
          (MapTile_HasHiddenTreasure(55, 45) ? 1 : 0)
            | (MapTile_HasHiddenTreasure(50, 27) ? 2 : 0)
            | (MapTile_HasHiddenTreasure(35, 63) ? 4 : 0)
            | (MapTile_HasHiddenTreasure(14, 68) ? 8 : 0));
        return objective_met;
      }
      kill_stack_index = 0;
      while ( 1 )
      {
        if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * kill_stack_index + 147180) <= 0x28 )
        {
          kill_stack_offset = UNIT_STACK_STRIDE * kill_stack_index;
          kill_stack_record = gameData + UNIT_STACK_STRIDE * kill_stack_index;
          if ( *(_BYTE *)(kill_stack_record + 147178) )
          {
            if ( Map_IsTileVisibleToPlayer(*(__int16 *)(kill_stack_record + 147174), *(__int16 *)(kill_stack_record + 147176), 0) )
            {
              Camera_CenterOnUnit(kill_stack_index);
              Audio_PlayArtifactSound(0);
              UI_StartTileBlinkFlash(*(__int16 *)(kill_stack_offset + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(kill_stack_offset + gameData + 147176), v16);
              Unit_Kill(kill_stack_offset + gameData + UNIT_STACK_TABLE_OFFSET, 0, a1, a2);
              Timer_BusyWaitWithCallback(100, v17, v18);
            }
          }
        }
        do
        {
          if ( ++kill_stack_index >= 500 )
            return objective_met;
        }
        while ( kill_stack_index < 0 );
      }
    case 8:
      garrison_slot_offset = 0;
      while ( *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 562420) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + garrison_slot_offset + 509692) == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE )
      {
        garrison_slot_offset += 31;
        if ( garrison_slot_offset >= 372 )
          return 1;
      }
      Mission_TraceObjectiveBlocked(8, 30, 23, garrison_slot_offset / 31);
      return 0;
    case 9:
      player_offset = 1423;
      while ( !*(_DWORD *)(gameData + player_offset + PLAYER_RUNTIME_STATE_OFFSET) )
      {
        player_offset += PLAYER_DATA_STRIDE;
        if ( player_offset >= 7115 )
          return 1;
      }
      Mission_TraceObjectiveBlocked(9, player_offset / PLAYER_DATA_STRIDE, *(_DWORD *)(gameData + player_offset + PLAYER_RUNTIME_STATE_OFFSET), 0);
      return 0;
    case 0xA:
      owner2_stack_index = 0;
LABEL_75:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * owner2_stack_index + 147180) <= 0x28
        && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * owner2_stack_index + 147178) == 2 )
      {
        Mission_TraceObjectiveBlocked(
          10,
          owner2_stack_index,
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * owner2_stack_index + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * owner2_stack_index + 147176));
        return 0;
      }
      while ( ++owner2_stack_index < 500 )
      {
        if ( owner2_stack_index >= 0 )
          goto LABEL_75;
      }
      return 1;
    case 0xB:
      if ( MapTile_GetReligiousSiteCategory(2, 44) == RELIGIOUS_SITE_CATEGORY_EMPTY_CULT_PLACE )
        return 1;
      Mission_TraceObjectiveBlocked(11, 2, 44, MapTile_GetReligiousSiteCategory(2, 44));
      return 0;
    case 0xC:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 568202) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) == 1 )
        return 1;
      Mission_TraceObjectiveBlocked(
        12,
        59,
        14,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 568202) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676));
      return 0;
    case 0xE:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 566822) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) == 1 )
        return 1;
      Mission_TraceObjectiveBlocked(
        14,
        52,
        24,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 566822) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676));
      return 0;
    case 0xF:
      owner4_building_index = 0;
LABEL_86:
      owner4_building_record = UNIT_RECORD(owner4_building_index);
      if ( (unsigned int)*(char *)(owner4_building_record + 4) < 4
        && *(__int16 *)(owner4_building_record + 16) != -1
        && *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * owner4_building_index + 509676) == 4 )
      {
        Mission_TraceObjectiveBlocked(15, owner4_building_index, *(_BYTE *)(gameData + BUILDING_RECORD_SIZE * owner4_building_index + 509676), *(__int16 *)(owner4_building_record + 16));
        return 0;
      }
      while ( ++owner4_building_index < 100 )
      {
        if ( owner4_building_index >= 0 )
          goto LABEL_86;
      }
      owner4_stack_index = 0;
LABEL_94:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * owner4_stack_index + 147180) <= 0x28
        && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * owner4_stack_index + 147178) == 4 )
      {
        Mission_TraceObjectiveBlocked(
          15,
          owner4_stack_index,
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * owner4_stack_index + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(gameData + UNIT_STACK_STRIDE * owner4_stack_index + 147176));
        return 0;
      }
      while ( ++owner4_stack_index < 500 )
      {
        if ( owner4_stack_index >= 0 )
          goto LABEL_94;
      }
      return 1;
    case 0x10:
      if ( *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574660) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) == 1 )
        return 1;
      Mission_TraceObjectiveBlocked(
        16,
        91,
        43,
        *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 574660) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676));
      return 0;
    case 0x11:
      treasures_taken_m17 = !MapTile_HasHiddenTreasure(50, 34) && !MapTile_HasHiddenTreasure(51, 73) && !MapTile_HasHiddenTreasure(77, 34) && !MapTile_HasHiddenTreasure(24, 49);
      objective_met = treasures_taken_m17;
      if ( !treasures_taken_m17 )
      {
        Mission_TraceObjectiveBlocked(
          17,
          50,
          34,
          (MapTile_HasHiddenTreasure(50, 34) ? 1 : 0)
            | (MapTile_HasHiddenTreasure(51, 73) ? 2 : 0)
            | (MapTile_HasHiddenTreasure(77, 34) ? 4 : 0)
            | (MapTile_HasHiddenTreasure(24, 49) ? 8 : 0));
        return objective_met;
      }
      kill_stack_index_m17 = 0;
LABEL_105:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * kill_stack_index_m17 + 147180) <= 0x28 )
      {
        kill_stack_offset_m17 = UNIT_STACK_STRIDE * kill_stack_index_m17;
        kill_stack_record_m17 = gameData + UNIT_STACK_STRIDE * kill_stack_index_m17;
        if ( *(_BYTE *)(kill_stack_record_m17 + 147178) != 1 )
        {
          if ( Map_IsTileVisibleToPlayer(*(__int16 *)(kill_stack_record_m17 + 147174), *(__int16 *)(kill_stack_record_m17 + 147176), 1) )
          {
            Camera_CenterOnUnit(kill_stack_index_m17);
            Audio_PlayArtifactSound(0);
            UI_StartTileBlinkFlash(*(__int16 *)(kill_stack_offset_m17 + gameData + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(kill_stack_offset_m17 + gameData + 147176), v29);
            Unit_Kill(kill_stack_offset_m17 + gameData + UNIT_STACK_TABLE_OFFSET, 1, a1, a2);
            Timer_BusyWaitWithCallback(100, v30, v31);
          }
        }
      }
      while ( ++kill_stack_index_m17 < 500 )
      {
        if ( kill_stack_index_m17 >= 0 )
          goto LABEL_105;
      }
      return objective_met;
    case 0x12:
      personage_count = 0;
      for ( i = 0; i != 372; i += 31 )
      {
        garrison_unit_type = *(__int16 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 573450) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + i + 509692);
        if ( garrison_unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || garrison_unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
          ++personage_count;
      }
      if ( personage_count >= 6 )
        return 1;
      Mission_TraceObjectiveBlocked(18, 85, 38, personage_count);
      return 0;
    case 0x13:
      if ( *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) )
      {
        Mission_TraceObjectiveBlocked(19, 0, *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET), 0);
        return 0;
      }
      ally_offset = 2846;
      while ( !*(_DWORD *)(gameData + ally_offset + PLAYER_RUNTIME_STATE_OFFSET) )
      {
        ally_offset += PLAYER_DATA_STRIDE;
        if ( ally_offset >= 7115 )
          return 1;
      }
      Mission_TraceObjectiveBlocked(19, ally_offset / PLAYER_DATA_STRIDE, *(_DWORD *)(gameData + ally_offset + PLAYER_RUNTIME_STATE_OFFSET), 0);
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
  int personage_count; // ebx
  int stack_index; // edx
  int i; // esi
  int slot_unit_type; // eax
  int building_index; // eax
  int building_record; // ecx
  int j; // ecx
  int garrison_unit_type; // edx
  int personage_count_p1; // ebx
  int stack_index_p1; // edx
  int k; // esi
  int slot_unit_type_p1; // eax
  int building_index_p1; // eax
  int building_record_p1; // ecx
  int m; // ecx
  int garrison_unit_type_p1; // edx

  switch ( ACTIVE_MISSION_INDEX )
  {
    case 3:
      return *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 560616) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) != 0;
    case 4:
    case 0xE:
      return *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) > 0x14u;
    case 5:
      result = (unsigned __int8)g_LanguageIndex;
      if ( g_LanguageIndex )
        return MISSION_FAILURE_FLAG;
      return result;
    case 8:
      personage_count = 0;
      stack_index = 0;
LABEL_7:
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28 && !*(_BYTE *)(gameData + UNIT_STACK_STRIDE * stack_index + 147178) )
      {
        for ( i = 0; i < 10; ++i )
        {
          slot_unit_type = *(__int16 *)(UNIT_STACK_STRIDE * stack_index + gameData + 31 * i + 147180);
          if ( slot_unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slot_unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
            ++personage_count;
        }
      }
      while ( ++stack_index < 500 )
      {
        if ( stack_index >= 0 )
          goto LABEL_7;
      }
      building_index = 0;
LABEL_19:
      building_record = UNIT_RECORD(building_index);
      if ( (unsigned int)*(char *)(building_record + 4) < 4
        && *(__int16 *)(building_record + 16) != -1
        && !*(_BYTE *)(BUILDING_RECORD_SIZE * building_index + gameData + 509676) )
      {
        for ( j = 0; j < 12; ++j )
        {
          garrison_unit_type = *(__int16 *)(31 * j + gameData + BUILDING_RECORD_SIZE * building_index + 509692);
          if ( garrison_unit_type == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || garrison_unit_type == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
            ++personage_count;
        }
      }
      while ( ++building_index < 100 )
      {
        if ( building_index >= 0 )
          goto LABEL_19;
      }
      return personage_count < 12;
    case 0xD:
      return *(unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 561026) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509676) != 1;
    case 0xF:
      return MISSION_FAILURE_FLAG;
    case 0x12:
      personage_count_p1 = 0;
      stack_index_p1 = 0;
      break;
    default:
      return 0;
  }
LABEL_34:
  if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index_p1 + 147180) <= 0x28
    && *(_BYTE *)(gameData + UNIT_STACK_STRIDE * stack_index_p1 + 147178) == 1 )
  {
    for ( k = 0; k < 10; ++k )
    {
      slot_unit_type_p1 = *(__int16 *)(UNIT_STACK_STRIDE * stack_index_p1 + gameData + 31 * k + 147180);
      if ( slot_unit_type_p1 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || slot_unit_type_p1 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        ++personage_count_p1;
    }
  }
  while ( ++stack_index_p1 < 500 )
  {
    if ( stack_index_p1 >= 0 )
      goto LABEL_34;
  }
  building_index_p1 = 0;
LABEL_46:
  building_record_p1 = UNIT_RECORD(building_index_p1);
  if ( (unsigned int)*(char *)(building_record_p1 + 4) < 4
    && *(__int16 *)(building_record_p1 + 16) != -1
    && *(_BYTE *)(BUILDING_RECORD_SIZE * building_index_p1 + gameData + 509676) == 1 )
  {
    for ( m = 0; m < 12; ++m )
    {
      garrison_unit_type_p1 = *(__int16 *)(31 * m + gameData + BUILDING_RECORD_SIZE * building_index_p1 + 509692);
      if ( garrison_unit_type_p1 == UNIT_TYPE_SPECIAL_FOOT_PERSONAGE || garrison_unit_type_p1 == UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE )
        ++personage_count_p1;
    }
  }
  while ( ++building_index_p1 < 100 )
  {
    if ( building_index_p1 >= 0 )
      goto LABEL_46;
  }
  return personage_count_p1 < 6;
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
      Rules_LogAssignedCastleFact(*(unsigned __int16 *)(gameData + 567712) - TILE_OCCUPANT_BUILDING_INDEX_BASE, 4);
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
      Rules_LogAssignedCastleFact(*(unsigned __int16 *)(TILE_INDEX(52, 24)) - TILE_OCCUPANT_BUILDING_INDEX_BASE, 14);
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
int  Scenario_LoadMissionByIndexAndPlay(char *mission_index_arg, int a2, DWORD a3, double a4)
{
  int mission_index; // eax
  unsigned __int8 saved_campaign_state[27]; // [esp-1Bh] [ebp-1Bh] BYREF

  mission_index = (int)(size_t)mission_index_arg;
  qmemcpy(saved_campaign_state, (const void *)(gameData + 147147), 0x1Bu);
  if ( mission_index && mission_index != 10 )
    Video_PlayAviWithModeGuard(0, aZwy01_0);
  Mission_PlayInfoSlideshow(mission_index, mission_index_arg);
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
_DWORD * RenderState_ConstructDefault(int render_state, int a2)
{
  int palette_base; // eax
  _DWORD *palette_array; // eax

  (void)a2;
  palette_base = render_state + 80;
  *(_DWORD *)(palette_base - 64) = 0;
  *(_DWORD *)(palette_base - 60) = 0;
  *(_DWORD *)(palette_base - 56) = 639;
  *(_DWORD *)(palette_base - 52) = 479;
  *(_DWORD *)(palette_base - 48) = 64;
  *(_DWORD *)(palette_base - 16) = 0;
  palette_array = (_DWORD *)(uintptr_t)(unsigned int)_wcpp_4_ctor_array__(palette_base, 256);
  palette_array[256] = 50;
  palette_array[257] = 6;
  palette_array[258] = 2;
  palette_array[259] = 5;
  palette_array[260] = g_RenderState_Vtable;
  return palette_array - 20;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 50F1E4: using guessed type int (*off_50F1E4[6])();

//----- (00460490) --------------------------------------------------------
int  RenderState_InitCursorResources(int render_state, int a2, char a3, DWORD a4)
{
  _DWORD *sprite_set;
  _DWORD *surface;

  g_CursorOverlayPresented = 0;
  *(_DWORD *)(render_state + 44) = 0;
  sprite_set = (_DWORD *)Mem_Alloc(4112, a2, a3, a4);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, "mouse.s32");
  *(_DWORD *)(render_state + 64) = sprite_set;
  surface = (_DWORD *)Mem_Alloc(188, 0, a3, a4);
  if ( surface )
  {
    a3 = 64;
    surface = Render_CreateSurface((int)surface, 64, 64);
  }
  *(_DWORD *)(render_state + 8) = surface;
  surface = (_DWORD *)Mem_Alloc(188, 0, a3, a4);
  if ( surface )
    surface = Render_CreateSurface((int)surface, 64, 64);
  *(_DWORD *)(render_state + 12) = surface;
  RenderState_SelectCursorDescriptor(render_state, (int)(uintptr_t)g_RenderVideoInitCursorDescriptor);
  Compat_RenderStateInvokeMethod(render_state, 20);
  *(_DWORD *)(render_state + 48) = (*(int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)(*(_DWORD *)(render_state + 60) + 20);
  *(_DWORD *)(render_state + 52) = (*(int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)(*(_DWORD *)(render_state + 60) + 24);
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)render_state, 0, 640, 0, 480);
  return LoadPalCOL(render_state + 80, (intptr_t)aMap_pal_1, a4);
}
// 544D10: using guessed type int dword_544D10;

//----- (00460580) --------------------------------------------------------
int  RenderState_ReleaseCursorResources(int render_state)
{
  int surface_handle;
  int vtable;
  int (*release_proc)(int, int);

  DLXSpriteSet_ReleaseAndClear((int *)(render_state + 64));
  surface_handle = *(_DWORD *)(render_state + 8);
  if ( surface_handle )
  {
    vtable = *(_DWORD *)(surface_handle + 184);
    release_proc = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(vtable);
    release_proc(surface_handle, 2);
  }
  surface_handle = *(_DWORD *)(render_state + 12);
  if ( !surface_handle )
    return 0;
  vtable = *(_DWORD *)(surface_handle + 184);
  release_proc = (int (*)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(vtable);
  release_proc(surface_handle, 2);
  return 0;
}

//----- (004605D0) --------------------------------------------------------
unsigned int  DD_Pump(int render_state, int a2, ...)
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
  int descriptor_addr; // edi
  int frame_interval; // ebp
  int cursor_frame_advanced; // ebx
  unsigned int now; // eax
  _DWORD *descriptor_frames; // eax
  int cursor_screen_y; // ecx
  int resource_handle; // ebp
  int v20; // eax
  int SpriteForChar; // eax
  void *saved_render_device; // [esp+1Ch] [ebp-18h]

  message_pump_result = Platform_PumpMessagesAndBlitFrame(a2);
  result = Time_Now(v5, v4);
  Compat_MenuProbeTraceRenderInput(
    "dd-pump",
    render_state,
    message_pump_result,
    result,
    g_RenderStateNextRefreshTick,
    *(_DWORD *)(render_state + 1112));
  if ( result >= g_RenderStateNextRefreshTick || message_pump_result )
  {
    g_RenderStateNextRefreshTick = *(_DWORD *)(render_state + 1112) + Time_Now(v8, v7);
    Compat_RenderStateInvokeMethod(render_state, 20);
    if ( g_DDPageFlipWasInProgressFlag && !DD_IsFlipping(render_state) )
    {
      *(_DWORD *)(render_state + 68) = Time_Now(v10, v9);
      *(_DWORD *)(render_state + 72) = *(int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108);
      *(_DWORD *)(render_state + 76) = *(int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108);
    }
    g_DDPageFlipWasInProgressFlag = DD_IsFlipping(render_state);
    Compat_RenderStateInvokeMethod(render_state, 4);
    cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
    descriptor_addr = (int)cursor_descriptor;
    frame_interval = *(_DWORD *)(descriptor_addr + 8);
    cursor_frame_advanced = 0;
    if ( frame_interval )
    {
      cursor_update_deadline = *(_DWORD *)(descriptor_addr + 28) + frame_interval;
      now = Time_Now(cursor_update_deadline, v11);
      if ( (unsigned int)cursor_update_deadline < now )
      {
        *(_DWORD *)((char *)cursor_descriptor + 28) = Time_Now(now, v11);
        ++*(_DWORD *)((char *)cursor_descriptor + 32);
        descriptor_frames = cursor_descriptor;
        if ( descriptor_frames[1] - *descriptor_frames < descriptor_frames[8] )
          descriptor_frames[8] = 0;
        cursor_frame_advanced = 1;
      }
    }
    *(_DWORD *)(render_state + 48) = (*(int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)((char *)cursor_descriptor + 20);
    cursor_screen_y = (*(int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)((char *)cursor_descriptor + 24);
    *(_DWORD *)(render_state + 52) = cursor_screen_y;
    result = g_CursorOverlayPresented;
    if ( g_CursorOverlayPresented )
    {
      if ( message_pump_result
        || cursor_frame_advanced
        || (result = *(_DWORD *)(render_state + 48), result != *(_DWORD *)render_state)
        || cursor_screen_y != *(_DWORD *)(render_state + 4) )
      {
        saved_render_device = g_RenderDevice;
        resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
        primary_surface = Compat_RenderStateSurface(render_state, 8);
        back_surface = Compat_RenderStateSurface(render_state, 12);
        if ( *(_DWORD *)render_state == *(_DWORD *)(render_state + 48) && *(_DWORD *)(render_state + 52) == *(_DWORD *)(render_state + 4) )
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
                            *(_DWORD *)(render_state + 64),
                            *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
          (void)SpriteForChar;
          Render_FillRect(
            back_surface,
            0,
            0,
            0,
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) - 1,
            *(_WORD *)render_state,
            *(_WORD *)(render_state + 4));
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
            *(_WORD *)render_state,
            *(_WORD *)(render_state + 4));
          Render_FillRect(
            0,
            primary_surface,
            *(unsigned __int16 *)(render_state + 52),
            *(unsigned __int16 *)(render_state + 48),
            *(unsigned __int16 *)((char *)cursor_descriptor + 12) + *(_WORD *)(render_state + 48) - 1,
            *(unsigned __int16 *)((char *)cursor_descriptor + 16) + *(_WORD *)(render_state + 52) - 1,
            0,
            0);
          v20 = DLX_GetSpriteForChar(
                  *(_DWORD *)(render_state + 64),
                  *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
          (void)v20;
          *(_DWORD *)render_state = *(_DWORD *)(render_state + 48);
          *(_DWORD *)(render_state + 4) = *(_DWORD *)(render_state + 52);
        }
        g_RenderDevice = saved_render_device;
        return Render_SetResourceHandle((int)&g_MainRenderDevice, resource_handle);
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
void  RenderState_SetMouseSpeed(int render_state, int mouse_speed, DWORD a3)
{
  Debug_Log(render_state, mouse_speed, a3, (int)aMouse_speedD);
  *(_DWORD *)(render_state + 32) = mouse_speed;
}

//----- (004608F0) --------------------------------------------------------
BOOL  DD_IsFlipping(int render_state)
{
  return (*(_BYTE *)(render_state + 44) & 1) != 0;
}

//----- (00460900) --------------------------------------------------------
BOOL  DD_IsLost(int render_state)
{
  return (*(_BYTE *)(render_state + 44) & 2) != 0;
}

//----- (00460910) --------------------------------------------------------
BOOL  Input_PollEventsUntil(int render_state, char a2)
{
  int previous_poll_state;

  previous_poll_state = *(_DWORD *)(render_state + 56);
  *(_DWORD *)(render_state + 56) = 0;
  Platform_PumpMessagesAndBlitFrame(a2);
  *(_DWORD *)(render_state + 56) = previous_poll_state;
  InputBackend_PollState(&g_InputBackendState, render_state, previous_poll_state);
  return g_InputMousePrimaryButtonState < 0 || g_InputMouseSecondaryButtonState < 0;
}
// 5451C0: using guessed type char byte_5451C0;
// 5451C8: using guessed type char byte_5451C8;

//----- (00460950) --------------------------------------------------------
BOOL  RenderState_IsCursorFlipStillActive(int render_state)
{
  int now; // eax
  int delta_x; // eax
  int delta_y; // eax

  if ( !DD_IsFlipping(render_state) )
    return 0;
  now = Time_Now(0, 0);
  if ( (unsigned int)(now - *(_DWORD *)(render_state + 68)) >= *(_DWORD *)(render_state + 1104) )
    return 0;
  delta_x = *(_DWORD *)(render_state + 72) - (*(int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108));
  if ( delta_x <= 0 )
    delta_x = (*(int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)(render_state + 72);
  if ( delta_x >= *(_DWORD *)(render_state + 1116) )
    return 0;
  delta_y = *(_DWORD *)(render_state + 76) - (*(int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108));
  if ( delta_y <= 0 )
    delta_y = (*(int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)(render_state + 76);
  return delta_y < *(_DWORD *)(render_state + 1116);
}

//----- (004609D0) --------------------------------------------------------
BOOL  Render_Begin(int render_state, void (*idle_callback)(void), ...)
{
  BOOL result; // eax

  result = 0;
  while ( 1 )
  {
    if ( !DD_IsFlipping(render_state) )
    {
      result = DD_IsLost(render_state);
      if ( !result )
        break;
    }
    DD_Pump(render_state, (char)idle_callback);
    if ( idle_callback )
      idle_callback();
  }
  return result;
}

//----- (00460A10) --------------------------------------------------------
BOOL  Render_FlipRect(int render_state, char a2)
{
  int previous_poll_state;
  BOOL result; // eax

  result = 0;
  while ( 1 )
  {
    if ( !DD_IsFlipping(render_state) )
    {
      result = DD_IsLost(render_state);
      if ( !result )
        break;
    }
    previous_poll_state = *(_DWORD *)(render_state + 56);
    *(_DWORD *)(render_state + 56) = 0;
    Platform_PumpMessagesAndBlitFrame(a2);
    *(_DWORD *)(render_state + 56) = previous_poll_state;
    Compat_RenderStateInvokeMethod(render_state, 20);
  }
  return result;
}

//----- (00460A50) --------------------------------------------------------
int  RenderState_PollInputAndClampCursor(int render_state, int a2)
{
  _DWORD *state; // edx
  int scaled_delta_y; // eax
  int prev_cursor_y; // edi
  int min_x; // ecx
  int min_y; // ebx
  int max_x; // esi
  int result; // eax
  int max_y; // edi

  state = (_DWORD *)(uintptr_t)(unsigned int)render_state;
  InputBackend_PollState(&g_InputBackendState, render_state, a2);
  Compat_MenuProbeTraceRenderInput(
    "live-input",
    render_state,
    g_InputBackendState.mouse_delta_x,
    g_InputBackendState.mouse_delta_y,
    g_InputBackendState.mouse_button_primary,
    g_InputBackendState.mouse_button_secondary);
  state[9] += state[8] * g_InputBackendState.mouse_delta_x;
  scaled_delta_y = state[8] * g_InputBackendState.mouse_delta_y;
  prev_cursor_y = state[10];
  state[11] = 0;
  state[10] = scaled_delta_y + prev_cursor_y;
  if ( g_InputMousePrimaryButtonState < 0 )
    ++state[11];
  if ( g_InputMouseSecondaryButtonState < 0 )
    state[11] += 2;
  min_x = state[4];
  if ( state[9] < min_x )
    state[9] = min_x;
  min_y = state[5];
  if ( state[10] < min_y )
    state[10] = min_y;
  max_x = state[6];
  if ( state[9] > max_x )
    state[9] = max_x;
  result = state[10];
  max_y = state[7];
  if ( result > max_y )
    state[10] = max_y;
  Compat_SyncRenderCursorGlobals(state);
  return result;
}
// 460A66: variable 'v2' is possibly undefined
// 5451A8: using guessed type int dword_5451A8;
// 5451AC: using guessed type int dword_5451AC;
// 5451C0: using guessed type char byte_5451C0;
// 5451C8: using guessed type char byte_5451C8;

//----- (00460AF0) --------------------------------------------------------
unsigned int  RenderState_WarpCursorAndPump(_DWORD *render_state, unsigned __int16 cursor_x, unsigned __int16 cursor_y)
{
  render_state[9] = cursor_x << render_state[277];
  render_state[10] = cursor_y << render_state[277];
  Compat_SyncRenderCursorGlobals(render_state);
  return DD_Pump((int)render_state, cursor_y);
}

//----- (00460B20) --------------------------------------------------------
_DWORD * RenderState_RecalculateCursorBoundsForRect(
        _DWORD *result,
        __int16 rect_left,
        __int16 rect_right,
        __int16 rect_top,
        __int16 rect_bottom)
{
  _WORD *descriptor_words; // edx
  unsigned __int16 min_x; // si
  unsigned __int16 min_y; // bx
  unsigned __int16 max_x; // di
  __int16 v10; // cx

  descriptor_words = (_WORD *)result[15];
  min_x = descriptor_words[10] + 1 + rect_left;
  min_y = descriptor_words[12] + 1 + rect_top;
  max_x = rect_right - (descriptor_words[6] - descriptor_words[10] + 1);
  v10 = descriptor_words[8];
  LOWORD(descriptor_words) = descriptor_words[12];
  result[4] = min_x << result[277];
  result[5] = min_y << result[277];
  result[6] = max_x << result[277];
  result[7] = (unsigned __int16)(rect_bottom - (v10 - (_WORD)descriptor_words + 1)) << result[277];
  return result;
}

//----- (00460BB0) --------------------------------------------------------
_DWORD * RenderState_PumpIfRectInViewBounds(
        _DWORD *result,
        unsigned __int16 rect_left,
        unsigned __int16 rect_right,
        unsigned __int16 rect_top,
        unsigned __int16 rect_bottom)
{
  int cursor_descriptor; // ebx

  cursor_descriptor = result[15];
  if ( *(_DWORD *)(cursor_descriptor + 12) + result[12] >= rect_left
    && rect_right >= (int)result[12]
    && result[13] + *(_DWORD *)(cursor_descriptor + 16) >= rect_top
    && rect_bottom >= (int)result[13] )
  {
    return (_DWORD *)Render_Pump();
  }
  return result;
}

//----- (00460C70) --------------------------------------------------------
_DWORD * RenderState_LoadDefaultCursorSprite(int render_state)
{
  _DWORD *result; // eax
  if ( *(_DWORD *)(render_state + 64) )
    DLXSpriteSet_ReleaseAndClear((int *)(render_state + 64));
  result = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, "mouse.s32");
    *(_DWORD *)(render_state + 64) = result;
  }
  else
  {
    *(_DWORD *)(render_state + 64) = 0;
  }
  return result;
}

//----- (00460CB0) --------------------------------------------------------
_DWORD * RenderState_LoadOrRenderCursorLabelSprite(int render_state, int label_text, int a3, DWORD a4)
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

  if ( *(_DWORD *)(render_state + 64) )
    DLXSpriteSet_ReleaseAndClear((int *)(render_state + 64));
  source_bytes = (unsigned __int8 *)label_text;
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
      *(_DWORD *)(render_state + 64) = result;
      return result;
    }
  }
  RenderState_LoadDefaultCursorSprite(render_state);
  DLXSpriteSet_DrawText(*(_DWORD *)(render_state + 64), -1, label_text, (unsigned __int8 *)(render_state + 80));
  result = *(_DWORD **)(render_state + 64);
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

__int16  RenderState_SelectCursorDescriptor(int render_state, int new_descriptor)
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

  result = render_state;
  active_descriptor = new_descriptor;
  if ( !active_descriptor )
    active_descriptor = *(_DWORD *)(render_state + 60);
  if ( active_descriptor )
    g_ActiveCursorDescriptorPtr = active_descriptor;
  if ( new_descriptor == *(_DWORD *)(render_state + 60) )
    return result;
  was_presenting = (unsigned char)g_CursorOverlayPresented;
  if ( was_presenting )
    Compat_RenderClearPresentedRect(render_state);
  *(_DWORD *)(render_state + 60) = new_descriptor;
  descriptor = *(_DWORD *)(render_state + 60);
  max_height = 0;
  max_width = 0;
  for ( sprite_index = *(unsigned __int16 *)descriptor; sprite_index <= (unsigned int)*(int *)(descriptor + 4); ++sprite_index )
  {
    sprite_height = DLX_GetSpriteHeight(*(_DWORD *)(render_state + 64), (int)sprite_index);
    sprite_width = DLX_GetSpriteWidth(*(_DWORD *)(render_state + 64), (int)sprite_index);
    if ( sprite_height > max_height )
      max_height = sprite_height;
    if ( sprite_width > max_width )
      max_width = sprite_width;
  }
  *(_DWORD *)(descriptor + 12) = max_height;
  *(_DWORD *)(descriptor + 16) = max_width;
  *(_DWORD *)(descriptor + 32) = 0;
  *(_DWORD *)(descriptor + 28) = 0;
  RenderState_RecalculateCursorBoundsForRect((_DWORD *)render_state, 0, 640, 0, 480);
  Compat_RenderStateInvokeMethod(render_state, 20);
  Compat_RenderStateInvokeMethod(render_state, 4);
  *(_DWORD *)(render_state + 48) = (*(int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)(descriptor + 20);
  *(_DWORD *)(render_state + 52) = (*(int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108)) - *(_DWORD *)(descriptor + 24);
  if ( was_presenting )
    result = Render_Present(render_state);
  return result;
}
// 544D10: using guessed type int dword_544D10;

//----- (00460EA0) --------------------------------------------------------
int  Render_Present(int render_state)
{
  _DWORD *cursor_descriptor;
  _DWORD *present_surface;
  int result; // eax
  int resource_handle; // edi
  int SpriteForChar; // eax
  void *saved_render_device; // [esp+1Ch] [ebp-Ch]

  present_surface = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(render_state + 8);
  cursor_descriptor = Compat_RenderStateCursorDescriptor(render_state);
  result = g_CursorOverlayPresented;
  if ( !g_CursorOverlayPresented )
  {
    resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
    g_CursorOverlayPresented = 1;
    saved_render_device = g_RenderDevice;
    Render_FillRect(
      0,
      present_surface,
      *(unsigned __int16 *)(render_state + 52),
      *(unsigned __int16 *)(render_state + 48),
      *(unsigned __int16 *)((char *)cursor_descriptor + 12) + *(_WORD *)(render_state + 48) - 1,
      *(unsigned __int16 *)((char *)cursor_descriptor + 16) + *(_WORD *)(render_state + 52) - 1,
      0,
      0);
    g_RenderDevice = &g_MainRenderDevice;
    SpriteForChar = DLX_GetSpriteForChar(
                      *(_DWORD *)(render_state + 64),
                      *(_DWORD *)((char *)cursor_descriptor + 32) + *cursor_descriptor);
    (void)SpriteForChar;
    *(_DWORD *)render_state = *(_DWORD *)(render_state + 48);
    *(_DWORD *)(render_state + 4) = *(_DWORD *)(render_state + 52);
    g_RenderDevice = saved_render_device;
    result = Render_SetResourceHandle((int)&g_MainRenderDevice, resource_handle);
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
  int resource_handle; // esi

  result = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
  {
    g_CursorOverlayPresented = 0;
    resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
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
    return Render_SetResourceHandle((int)&g_MainRenderDevice, resource_handle);
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
int  RenderState_DrawCursorSpriteToPrimarySurface(int render_state)
{
  void *saved_render_device; // esi
  int SpriteForChar; // eax
  int result; // eax

  saved_render_device = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, &g_CursorSpritePalette);
  SpriteForChar = DLX_GetSpriteForChar(*(_DWORD *)(render_state + 64), g_CursorDesc_Busy[0] + 1);
  result = Compat_RenderDeviceDrawMenuSprite(0, 0, SpriteForChar, 1);
  g_RenderDevice = saved_render_device;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519808: using guessed type int dword_519808;

//----- (00461140) --------------------------------------------------------
_DWORD * Device_GetParamA(int render_state, int a2)
{
  _DWORD *result; // eax
  CompatRenderStateTail *tail;

  result = RenderState_ConstructDefault(render_state, a2);
  result[280] = g_Device_Vtable;
  tail = Compat_RenderStateTailFields(render_state);
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
int  Device_DoOp(int render_state, int a2, DWORD a3)
{
  CompatRenderStateTail *tail;
  int record_handle;

  (void)a2;
  tail = Compat_RenderStateTailFields(render_state);
  tail->field_464_active = 1;
  tail->field_46C_ticks = Time_Now(0, 0);
  record_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aWb_7, 0, a3);
  return fclose_(record_handle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004611A0) --------------------------------------------------------
__int16  Device_GetParamB(int render_state, DWORD a2, int a3, int a4)
{
  CompatRenderStateTail *tail;
  unsigned int current_x;
  unsigned int current_y;
  int current_flags;
  _DWORD elapsed_ticks;
  int record_handle;

  (void)a3;
  (void)a4;
  tail = Compat_RenderStateTailFields(render_state);
  if ( tail->field_464_active )
  {
    current_flags = *(_DWORD *)(render_state + 44);
    current_x = *(unsigned int *)(render_state + 36) >> *(_BYTE *)(render_state + 1108);
    current_y = *(unsigned int *)(render_state + 40) >> *(_BYTE *)(render_state + 1108);
    if ( (unsigned __int8)g_DeviceRecordLastFlipLostState != current_flags
      || current_x != (unsigned __int16)g_DeviceRecordLastX
      || current_y != (unsigned __int16)g_DeviceRecordLastY )
    {
      g_DeviceRecordLastX = *(_WORD *)(render_state + 36);
      g_DeviceRecordLastY = *(_WORD *)(render_state + 40);
      g_DeviceRecordLastFlipLostState = (unsigned char)(2 * (DD_IsFlipping(render_state) + DD_IsLost(render_state)));
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
int  Device_SetParamA(int render_state, DWORD a2)
{
  CompatRenderStateTail *tail;

  tail = Compat_RenderStateTailFields(render_state);
  tail->field_468_active = 1;
  tail->field_470_ticks = Time_Now(0, 0);
  tail->field_474_handle = IO_FOpen(aDefault_rec, (unsigned __int8 *)aRb_9, 0, a2);
  return tail->field_474_handle;
}

//----- (004612E0) --------------------------------------------------------
int  Device_UpdateRect(_DWORD *render_state, int a2, int a3)
{
  CompatRenderStateTail *tail;
  int now; // eax
  char v5; // bl
  int segment_start_ticks; // ecx
  unsigned int elapsed_ticks; // edx
  int replay_handle; // ecx
  int trigger_count; // edx
  int trigger_index; // eax
  int result; // eax
  int message_id; // edi
  unsigned int tween_fraction; // ecx

  tail = Compat_RenderStateTailFields((int)render_state);
  Compat_MenuProbeTraceRenderInput(
    "device-update",
    (int)render_state,
    a2,
    a3,
    tail->field_470_ticks,
    tail->field_474_handle);
  if ( !tail->field_468_active )
    return RenderState_PollInputAndClampCursor((int)render_state, a3);
  now = Time_Now(a3, a2);
  v5 = g_DeviceRectTweenTimeBase;
  segment_start_ticks = tail->field_470_ticks;
  elapsed_ticks = now - segment_start_ticks - g_DeviceRectTweenTimeBase;
  if ( elapsed_ticks < g_DeviceReplaySegmentTargetTick - g_DeviceReplaySegmentBaseTick )
  {
    tween_fraction = ((Time_Now(segment_start_ticks, elapsed_ticks) - tail->field_470_ticks - g_DeviceRectTweenTimeBase) << 8)
        / (unsigned int)(g_DeviceReplaySegmentTargetTick - g_DeviceReplaySegmentBaseTick);
    render_state[9] = (unsigned __int16)g_DeviceRectLastWidth
          + ((int)(tween_fraction * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)
                 - (__CFSHL__((int)(tween_fraction * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)) >> 31, 8)
                  + ((int)(tween_fraction * ((unsigned __int16)g_DeviceRectTargetWidth - (unsigned __int16)g_DeviceRectLastWidth)) >> 31 << 8))) >> 8);
    result = (unsigned __int16)g_RenderCursor_TweenPrevY
           + ((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * tween_fraction
                  - (__CFSHL__((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * tween_fraction) >> 31, 8)
                   + ((int)(((unsigned __int16)g_DeviceRectTargetHeight - (unsigned __int16)g_RenderCursor_TweenPrevY) * tween_fraction) >> 31 << 8))) >> 8);
    render_state[10] = result;
    Compat_SyncRenderCursorGlobals(render_state);
  }
  else
  {
    g_DeviceRectTweenTimeBase = Time_Now(segment_start_ticks, elapsed_ticks) - tail->field_470_ticks;
    g_DeviceReplaySegmentBaseTick = g_DeviceReplaySegmentTargetTick;
    g_DeviceRectLastWidth = g_DeviceRectTargetWidth;
    g_RenderCursor_TweenPrevY = g_DeviceRectTargetHeight;
    render_state[9] = (unsigned __int16)g_DeviceRectTargetWidth;
    render_state[10] = (unsigned __int16)g_DeviceRectTargetHeight;
    Compat_SyncRenderCursorGlobals(render_state);
    replay_handle = tail->field_474_handle;
    render_state[11] = (unsigned __int8)g_DemoPlaybackCursorButtonState;
    if ( (*(_BYTE *)(replay_handle + 12) & 0x10) == 0 )
    {
      fread_();
      fread_();
      fread_();
      v5 = 1;
      fread_();
    }
    trigger_count = 0;
    trigger_index = 0;
    if ( g_DemoScript_TriggerTickTable[0] != -1 )
    {
      while ( g_DemoScriptCurrentTick != g_DemoScript_TriggerTickTable[trigger_index] )
      {
        message_id = g_DemoScript_MessageIdTable[trigger_index++];
        ++trigger_count;
        if ( message_id == -1 )
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

