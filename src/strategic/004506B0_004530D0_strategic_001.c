/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004506B0) --------------------------------------------------------
int  Queen_FindEligibleBirthHostBuilding(int player_index)
{
  int building_index; // eax
  int building_record; // ebx
  int building_type; // ecx

  building_index = 0;
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(uintptr_t)(building_record + 4) < 4 && *(__int16 *)(uintptr_t)(building_record + 16) != -1 )
  {
    building_type = *(char *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + 509678);
    if ( (building_type == 2 || building_type == 1) && *(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + 509676) == player_index )
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
  __int16 v12 CLASH95_UNUSED; // ax
  int v13 CLASH95_UNUSED; // ecx
  __int16 v14 CLASH95_UNUSED; // bx
  int proposal_accepted; // eax
  int player_offset; // edx
  int v17 CLASH95_UNUSED; // ecx
  __int16 v18 CLASH95_UNUSED; // ax
  int v19 CLASH95_UNUSED; // ecx
  __int16 v20 CLASH95_UNUSED; // dx
  int host_building; // eax
  int v22 CLASH95_UNUSED; // ecx
  int v23; // ecx
  int v24 CLASH95_UNUSED; // edx
  int v25 CLASH95_UNUSED; // ecx
  signed int theft_castle_index; // eax
  int theft_castle_offset; // eax
  int v28 CLASH95_UNUSED; // edx
  int v29 CLASH95_UNUSED; // ecx
  signed int poison_castle_index; // eax
  int poison_castle_offset; // edx
  int poison_castle_record; // eax
  char plague_state_byte; // bh
  int v34 CLASH95_UNUSED; // edx
  int v35 CLASH95_UNUSED; // ecx
  signed int arson_castle_index; // eax
  int v37 CLASH95_UNUSED; // edx
  unsigned int whim_index; // eax
  int available_funds; // eax
  int v40 CLASH95_UNUSED; // ecx
  int v41 CLASH95_UNUSED; // ecx
  int player_record_accepted; // eax
  int player_record_declined; // eax
  int castle_name_ptr; // [esp-4h] [ebp-1Ch]
  int son_birth_texts[3]; // [esp+0h] [ebp-18h]
  int daughter_birth_texts[3]; // [esp+Ch] [ebp-Ch]
  _DWORD savedregs[6]; // [esp+18h] [ebp+0h] BYREF

  result = gameData;
  if ( ACTIVE_MISSION_INDEX != 6 )
  {
    Debug_Log(a1, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newturn, son_birth_texts[0]);
    result = PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex);
    if ( result != -1 )
    {
      if ( PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) )
      {
        if ( result == QUEEN_RELATIONSHIP_STATE_CHILDBIRTH_PENDING )
        {
          Debug_Log(g_CurrentPlayerIndex, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newturnN, son_birth_texts[0]);
          a2 = (char)((Rng_RandRange(0, 100) <= 0x32) + 33);
          host_building = Queen_FindEligibleBirthHostBuilding(g_CurrentPlayerIndex);
          if ( host_building )
          {
            Building_CreateSpecialPersonageGarrisonUnit(host_building, a2, host_building, a2, a4);
            PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) = 5;
            if ( PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
            {
              son_birth_texts[0] = (int)(intptr_t)g_QueenSonBirthTexts[0];
              son_birth_texts[1] = (int)(intptr_t)g_QueenSonBirthTexts[1];
              son_birth_texts[2] = (int)(intptr_t)g_QueenSonBirthTexts[2];
              castle_name_ptr = host_building + 5;
              daughter_birth_texts[0] = (int)(intptr_t)g_QueenDaughterBirthTexts[0];
              daughter_birth_texts[1] = (int)(intptr_t)g_QueenDaughterBirthTexts[1];
              daughter_birth_texts[2] = (int)(intptr_t)g_QueenDaughterBirthTexts[2];
              if ( a2 == 33 )
                sprintf_(&g_QueenBirthMessageBuffer, (const char *)(uintptr_t)son_birth_texts[(unsigned __int8)g_LanguageIndex], castle_name_ptr);
              else
                sprintf_(&g_QueenBirthMessageBuffer, (const char *)(uintptr_t)daughter_birth_texts[(unsigned __int8)g_LanguageIndex], castle_name_ptr);
              UI_ShowInfoWindow((const char *)&g_QueenBirthMessageBuffer, 0, v23, (DWORD)(intptr_t)savedregs, (int)(intptr_t)savedregs, (int)(intptr_t)&g_QueenDaughterBirthTexts[3]);
            }
          }
        }
        else if ( result == 1 )
        {
          Debug_Log(g_CurrentPlayerIndex, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newturnK, son_birth_texts[0]);
          PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex) = -1;
          switch ( Rng_RandRange(0, 3) )
          {
            case 0u:
              Debug_Log(v6, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newtur_0, 0);
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
              Debug_Log(v6, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newtur_1, 1);
              theft_castle_index = Unit_FindById(g_CurrentPlayerIndex);
              if ( theft_castle_index != -1 )
              {
                theft_castle_offset = BUILDING_RECORD_SIZE * theft_castle_index;
                *(_DWORD *)(uintptr_t)(gameData + theft_castle_offset + 510112) = 0;
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleTreasuryTheftTexts[(unsigned __int8)g_LanguageIndex],
                  gameData + BUILDING_TABLE_OFFSET + theft_castle_offset + 5);
              }
              break;
            case 2u:
              Debug_Log(v6, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newtur_2, 2);
              poison_castle_index = Unit_FindById(g_CurrentPlayerIndex);
              if ( poison_castle_index != -1 )
              {
                poison_castle_offset = BUILDING_RECORD_SIZE * poison_castle_index;
                poison_castle_record = gameData + BUILDING_RECORD_SIZE * poison_castle_index;
                plague_state_byte = *(_BYTE *)(uintptr_t)(poison_castle_record + 510109) & 0xF8;
                *(_BYTE *)(uintptr_t)(poison_castle_record + 510109) = plague_state_byte;
                *(_BYTE *)(uintptr_t)(poison_castle_record + 510109) = plague_state_byte | 5;
                sprintf_(
                  g_QueenDepartureEventMessageBuffer,
                  g_QueenCastleWellPoisoningTexts[(unsigned __int8)g_LanguageIndex],
                  poison_castle_offset + gameData + BUILDING_TABLE_OFFSET + 5);
              }
              break;
            case 3u:
              Debug_Log(v6, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newtur_3, 3);
              arson_castle_index = Unit_FindById(g_CurrentPlayerIndex);
              if ( arson_castle_index != -1 )
              {
                Building_Destroy(UNIT_RECORD(arson_castle_index), a2, (DWORD)(intptr_t)savedregs, a4);
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
            Queen_ShowMessageDialog((int)(intptr_t)g_QueenDepartureEventMessageBuffer, message_len - 1, a2, (DWORD)(intptr_t)savedregs);
        }
        result = PLAYER_DATA(g_CurrentPlayerIndex);
        if ( GAME_TURN_COUNTER >= *(_WORD *)(uintptr_t)(result + 141445) )
        {
          if ( *(_DWORD *)(uintptr_t)(result + 140051) )
          {
            whim_index = Rng_RandRange(0, 24);
            Debug_Log(whim_index, a2, (DWORD)(intptr_t)savedregs, (int)(intptr_t)aQueen_newturnZ, whim_index);
            available_funds = Player_CalcAvailableStrongholdFunds(g_CurrentPlayerIndex);
            if ( Queen_ShowWhimDecisionDialog(
                   g_QueenWhimRecords[whim_index].texts[(unsigned __int8)g_LanguageIndex],
                   g_QueenWhimRecords[whim_index].required_stronghold_funds,
                   7 * whim_index,
                   available_funds,
                   (DWORD)(intptr_t)savedregs) )
            {
              Player_SpendStrongholdFundsEvenly(g_CurrentPlayerIndex, g_QueenWhimRecords[whim_index].required_stronghold_funds);
              player_record_accepted = PLAYER_DATA(g_CurrentPlayerIndex);
              if ( *(char *)(uintptr_t)(player_record_accepted + 141443) < 9 )
                ++*(_BYTE *)(uintptr_t)(player_record_accepted + 141443);
            }
            else
            {
              player_record_declined = PLAYER_DATA(g_CurrentPlayerIndex);
              if ( *(char *)(uintptr_t)(player_record_declined + 141443) > 1 )
                --*(_BYTE *)(uintptr_t)(player_record_declined + 141443);
            }
            goto LABEL_18;
          }
          if ( ACTIVE_MISSION_INDEX != 14 )
          {
            if ( *(char *)(uintptr_t)(result + 141443) < 9 )
              ++*(_BYTE *)(uintptr_t)(result + 141443);
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
            Win_PlayModeChangeFrameTransition((int)(intptr_t)aP_posla, 1, gameData, a2, (DWORD)(intptr_t)savedregs, a3);
            Diagnostics_TraceWorldMapActionEvent(
              "queen_proposal_dialog_enter",
              g_SelectedUnitIndex,
              result,
              ACTIVE_MISSION_INDEX,
              GAME_TURN_COUNTER);
            proposal_accepted = Queen_ShowMarriageProposalDialog(0, a2, (DWORD)(intptr_t)savedregs);
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
            *(_BYTE *)(uintptr_t)(player_offset + gameData + 141443) = 5;
            result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
            PLAYER_QUEEN_NEXT_RELATIONSHIP_CHECK_TURN(g_CurrentPlayerIndex) = GAME_TURN_COUNTER + Rng_RandRange(5, 8);
          }
          else
          {
            result = gameData;
            *(_BYTE *)(uintptr_t)(player_offset + gameData + 141443) = -1;
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

  Debug_Log(a2, player_index, a3, (int)(intptr_t)aPlayer_surrend);
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(uintptr_t)(building_record + 4) < 4
    && *(__int16 *)(uintptr_t)(building_record + 16) != -1
    && *(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + 509676) == player_index )
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
  if ( (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28
    && *(unsigned __int8 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + 147178) == player_index )
  {
    UnitStack_KillByIndex(stack_index, player_index, a3, a4);
  }
  while ( ++stack_index < 500 )
  {
    if ( stack_index >= 0 )
      goto LABEL_10;
  }
  result = gameData;
  *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * player_index + gameData + PLAYER_RUNTIME_STATE_OFFSET) = 0;
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
  if ( (unsigned int)*(char *)(uintptr_t)(building_record + 4) >= 4
    || *(__int16 *)(uintptr_t)(building_record + 16) == -1
    || (building_offset = gameData + BUILDING_RECORD_SIZE * result, !*(_BYTE *)(uintptr_t)(building_offset + 509678))
    || *(unsigned __int8 *)(uintptr_t)(building_offset + 509676) != nation )
  {
    while ( ++result < 100 )
    {
      if ( result >= 0 )
        goto LABEL_2;
    }
    stack_index = 0;
LABEL_10:
    if ( (unsigned int)*(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 6) > 0x28
      || *(unsigned __int8 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147178) != nation
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
        if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * i + PLAYER_RUNTIME_STATE_OFFSET) )
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
          if ( *(_DWORD *)(uintptr_t)(player_record + 140051) && *(_DWORD *)(uintptr_t)(player_record + 140024) )
            human_ally_alive = 1;
        }
        if ( human_ally_alive )
        {
          notice_texts[0] = (int)(intptr_t)g_AllyEliminatedNoticeTexts[0];
          notice_texts[1] = (int)(intptr_t)g_AllyEliminatedNoticeTexts[1];
          notice_texts[2] = (int)(intptr_t)g_AllyEliminatedNoticeTexts[2];
          notice_format = (const char *)(uintptr_t)notice_texts[(unsigned __int8)g_LanguageIndex];
          sprintf_(message_buffer, notice_format, PLAYER_DATA_STRIDE * v13 + gameData + PLAYER_RUNTIME_STATE_OFFSET + 4);
          return UI_ShowInfoWindow((const char *)message_buffer, 0, v17, a3, (int)(intptr_t)notice_format, (int)(intptr_t)&g_AllyEliminatedNoticeTexts[3]);
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
  if ( (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28 )
  {
    owner_index = *(unsigned __int8 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147178);
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
  if ( (unsigned int)*(char *)(uintptr_t)(building_record + 4) < 4
    && *(__int16 *)(uintptr_t)(building_record + 16) != -1
    && (*(_BYTE *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + 509678) || Building_CountGarrison(UNIT_RECORD(building_index))) )
  {
    owner_index = *(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + 509676);
    if ( owner_index == player_index )
      return player_index ^ owner_index;
  }
  while ( ++building_index < 100 )
  {
    if ( building_index >= 0 )
      goto LABEL_9;
  }
  *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * player_index + gameData + PLAYER_RUNTIME_STATE_OFFSET) = 0;
  Render_Pump();
  Audio_StopMainMusic();
  Video_PlayAviWithModeGuard((int)(intptr_t)aArama1, aKon_por1);
  survivor_index = 0;
  while ( 1 )
  {
    survivor_record = gameData + PLAYER_DATA_STRIDE * survivor_index;
    if ( *(_DWORD *)(uintptr_t)(survivor_record + 140024) )
    {
      if ( *(_DWORD *)(uintptr_t)(survivor_record + 140051) )
        break;
    }
    if ( ++survivor_index >= 5 )
      return 1;
  }
  Music_PlayMainMapTrack(*(unsigned __int8 *)(uintptr_t)(gameData + MAP_THEME_INDEX_OFFSET), survivor_record, gameData, a2);
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
  while ( !*(_DWORD *)(uintptr_t)(gameData + player_offset + PLAYER_RUNTIME_STATE_OFFSET) || player_offset == own_player_offset )
  {
    player_offset += PLAYER_DATA_STRIDE;
    if ( player_offset >= 7115 )
    {
      Render_Pump();
      Audio_StopMainMusic();
      Palette_FadeOutToBlack((int *)&g_MainRenderDevice, v4);
      g_RenderDevice = &g_MainRenderDevice;
      (*(void (**)(void))(uintptr_t)(g_RenderDeviceDisplayContextPtr + 56))();
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
  *(_BYTE *)(uintptr_t)(gameData + 147173) = ((unsigned __int16)(((_WORD)g_OptionsInGameMusicVolumeRaw << 7)
                                                    - (__CFSHL__(g_OptionsInGameMusicVolumeRaw << 7 >> 31, 8)
                                                     + ((unsigned __int16)(g_OptionsInGameMusicVolumeRaw << 7 >> 31) << 8))) >> 8)
                                - 64;
  *(_BYTE *)(uintptr_t)(gameData + 147172) = (unsigned __int16)(16 * g_OptionsInGameSoundVolumeRaw
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
  if ( (*(_BYTE *)(uintptr_t)(widget_base - 98) & 2) == 0 )
  {
    *(_DWORD *)(uintptr_t)(widget_base - 98) = 2;
    UIWidget_RefreshActionButtonState(widget_base - 106, widget_base);
  }
  if ( (*(_BYTE *)(uintptr_t)(widget_base - 151) & 2) == 0 )
  {
    *(_DWORD *)(uintptr_t)(widget_base - 151) = 2;
    UIWidget_RefreshActionButtonState(widget_base - 159, widget_base);
  }
  if ( (*(_BYTE *)(uintptr_t)(widget_base - 204) & 2) == 0 )
  {
    *(_DWORD *)(uintptr_t)(widget_base - 204) = 2;
    UIWidget_RefreshActionButtonState(widget_base - 212, widget_base);
  }
  if ( (*(_BYTE *)(uintptr_t)(widget_base - 257) & 1) == 0 )
  {
    *(_DWORD *)(uintptr_t)(widget_base - 257) = 1;
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

  checkbox_state = *(_BYTE *)(uintptr_t)(widget + 8) ^ 1;
  *(_BYTE *)(uintptr_t)(widget + 8) = checkbox_state;
  *(_BYTE *)(uintptr_t)(widget + 8) = checkbox_state ^ 2;
  Audio_PlayButtonSound(*(char **)(uintptr_t)(widget + 49));
  return Render_Begin((int)(intptr_t)g_RenderState, 0);
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

  sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a1, a2, a3);
  if ( sprite_set )
    sprite_set = DLXSpriteSet_Load(sprite_set, a2);
  g_InGameOptionsSpriteSet = (int)(intptr_t)sprite_set;
  prev_resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  render_hook_fn = Render_DefaultRH;
  *(_DWORD *)&v17[25] = aStdrh_19;
  prev_render_hook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(92, a2, prev_resource_handle, (int)(intptr_t)aSetrhS08x_24);
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
  if ( *(_DWORD *)(uintptr_t)(gameData + 147159) )
    v20 = 2;
  if ( *(_DWORD *)(uintptr_t)(gameData + 147147) )
    v22 = 2;
  if ( *(_DWORD *)(uintptr_t)(gameData + 147163) )
    v23 = 2;
  if ( *(_DWORD *)(uintptr_t)(gameData + 147167) )
    v24 = 2;
  music_volume_raw = (*(char *)(uintptr_t)(gameData + 147173) << 8) + 0x4000;
  g_OptionsInGameMusicVolumeRaw = (music_volume_raw - (__CFSHL__(music_volume_raw >> 31, 7) + (music_volume_raw >> 31 << 7))) >> 7;
  g_OptionsInGameScrollSpeedRaw = ((*(unsigned __int8 *)(uintptr_t)(gameData + 147171) << 8)
                - (__CFSHL__(*(unsigned __int8 *)(uintptr_t)(gameData + 147171) << 8 >> 31, 4)
                 + 16 * (*(unsigned __int8 *)(uintptr_t)(gameData + 147171) << 8 >> 31))) >> 4;
  g_OptionsInGameSoundVolumeRaw = ((*(unsigned __int8 *)(uintptr_t)(gameData + 147172) << 8)
                - (__CFSHL__(*(unsigned __int8 *)(uintptr_t)(gameData + 147172) << 8 >> 31, 4)
                 + 16 * (*(unsigned __int8 *)(uintptr_t)(gameData + 147172) << 8 >> 31))) >> 4;
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar(g_InGameOptionsSpriteSet, (unsigned __int8)g_LanguageIndex);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
    DD_Pump((int)(intptr_t)g_RenderState, 132);
    UIWidgetTable_PollHoverAndActions(widget_table, prev_resource_handle);
    Options_AnimateAllSliderThumbs(g_InGameSliderThumbPositions);
  }
  while ( v14 == g_InGameOptionsDialogExitSignal );
  *(_DWORD *)(uintptr_t)(gameData + 147159) = v20 == 2;
  *(_DWORD *)(uintptr_t)(gameData + 147147) = v22 == 2;
  *(_DWORD *)(uintptr_t)(gameData + 147163) = v23 == 2;
  *(_DWORD *)(uintptr_t)(gameData + 147167) = v24 == 2;
  *(_BYTE *)(uintptr_t)(gameData + 147173) = ((unsigned __int16)(((_WORD)g_OptionsInGameMusicVolumeRaw << 7)
                                                    - (__CFSHL__(g_OptionsInGameMusicVolumeRaw << 7 >> 31, 8)
                                                     + ((unsigned __int16)(g_OptionsInGameMusicVolumeRaw << 7 >> 31) << 8))) >> 8)
                                - 64;
  *(_BYTE *)(uintptr_t)(gameData + 147171) = (unsigned __int16)(16 * g_OptionsInGameScrollSpeedRaw
                                                   - (__CFSHL__((16 * g_OptionsInGameScrollSpeedRaw) >> 31, 8)
                                                    + ((unsigned __int16)((16 * g_OptionsInGameScrollSpeedRaw) >> 31) << 8))) >> 8;
  *(_BYTE *)(uintptr_t)(gameData + 147172) = (unsigned __int16)(16 * g_OptionsInGameSoundVolumeRaw
                                                   - (__CFSHL__((16 * g_OptionsInGameSoundVolumeRaw) >> 31, 8)
                                                    + ((unsigned __int16)((16 * g_OptionsInGameSoundVolumeRaw) >> 31) << 8))) >> 8;
  Options_ApplyRecordSettings(gameData + 147147, v14, prev_resource_handle);
  Options_DestroySliderThumbList(g_InGameSliderThumbPositions);
  render_hook_fn = (int ( *)(int, char, DWORD))g_RenderHook;
  Debug_Log(v15, (char)(intptr_t)g_RenderHook, prev_resource_handle, (int)(intptr_t)aUnsetrh08x_24);
  g_RenderHook = prev_render_hook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, prev_resource_handle);
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
int Cheat_RevealMapForCurrentPlayer(void)
{
  Map_RevealAllTilesForPlayer(g_CurrentPlayerIndex);
  return WorldMap_RedrawViewport(1);
}
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004516B0) --------------------------------------------------------
void Cheat_FillSelectedSquadWithCannons(void)
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
        *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147178));
    }
    WorldMap_RedrawViewport(1);
  }
}
// 4516DE: variable 'v3' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00451730) --------------------------------------------------------
signed int Cheat_ClearSelectedSquadDamageFlags(void)
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
      *(_BYTE *)(uintptr_t)(slot_offset + UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147192) |= 3u;
      *(_BYTE *)(uintptr_t)(slot_offset + 31 + UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + 147161) = *(_BYTE *)(uintptr_t)(slot_offset
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
void Cheat_ForceWinCurrentMission(void)
{
  g_CheatForceWinMissionFlag = 1;
}
// 5448A0: using guessed type int dword_5448A0;

//----- (004517C0) --------------------------------------------------------
void Cheat_HealSelectedSquadAndClearDamage(void)
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
      *(_BYTE *)(uintptr_t)(slot_offset + 31 + gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147158) = 100;
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
          + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET));
  tile_occupant_id = *(unsigned __int16 *)(uintptr_t)(result
                           + 2
                           * ((((g_MouseCursorRawY >> g_CursorCoordShift)
                              - 16
                              - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                               + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
                            + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET))
                           + TILE_MAP_OFFSET);
  if ( (unsigned __int16)tile_occupant_id != 0xFFFF )
  {
    if ( tile_occupant_id > 0x1F4 || (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * tile_occupant_id + 147180) > 0x28 )
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
int Cheat_TeleportSelectedUnitToCursor(void)
{
  int tile_x; // esi
  int result; // eax
  int tile_y; // edi

  tile_x = (((g_MouseCursorRawX >> g_CursorCoordShift)
       - 32
       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
        + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
     + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
  result = ((g_MouseCursorRawY >> g_CursorCoordShift)
          - 16
          - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
           + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6;
  tile_y = result + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET);
  if ( g_SelectedUnitIndex != -1 )
  {
    *(_WORD *)(uintptr_t)(TILE_ROW_STRIDE * *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET)
             + gameData
             + 2 * *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176)
             + TILE_MAP_OFFSET) = -1;
    *(_WORD *)(uintptr_t)(TILE_INDEX(tile_x, tile_y)) = g_SelectedUnitIndex;
    *(_WORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET) = tile_x;
    *(_WORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176) = tile_y;
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
signed int Cheat_FillSelectedSquadWithPegasi(void)
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
        *(_BYTE *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147178));
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
  Render_FillRect(0, (_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  palette_mem = Mem_Alloc(1024, v2, 0, a1);
  if ( palette_mem )
  {
    palette_ctor_descriptor = &g_Runtime_PaletteArrayCtorDescriptor;
    palette_mem = _wcpp_4_ctor_array__(v4, 256);
  }
  palette = (unsigned __int8 *)(uintptr_t)palette_mem;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v4, (char)(intptr_t)palette_ctor_descriptor, a1);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  team_surface = Surface;
  saved_surface = Surface;
  RenderSurface_InvokeSlot48LoadPCX(Surface, aTeam1_gfx, 0, (uintptr_t)palette);
  RenderSurface_InvokeSlot36(team_surface);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, palette, 20);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) )
    DD_Pump((int)(intptr_t)g_RenderState, 20);
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 0, 0, SCREEN_MAX_X, SCREEN_MAX_Y, 0, 0);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)(uintptr_t)g_MapPalettePtr, 20);
  if ( saved_surface )
    RenderSurface_InvokeSlot0(saved_surface, 2);
  return j__nfree_();
}
// 451B1C: variable 'v2' is possibly undefined
// 451BB0: variable 'v4' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 5202E0: using guessed type int dword_5202E0;
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00451C50) --------------------------------------------------------
void __noreturn Cheat_QuitWithJokeMessage(void)
{
  App_RequestQuit((int)(intptr_t)aHeheNoBonus);
}

//----- (00451C60) --------------------------------------------------------
void Cheat_SetFactionColorAndCastleFlags(void)
{
  int building_index; // eax
  int building_record; // edx
  int building_offset; // edx
  char color_flags; // bl

  *(_BYTE *)(uintptr_t)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) = 3;
  building_index = 0;
  while ( 1 )
  {
    building_record = UNIT_RECORD(building_index);
    if ( (unsigned int)*(char *)(uintptr_t)(building_record + 4) < 4 && *(__int16 *)(uintptr_t)(building_record + 16) != -1 )
    {
      building_offset = gameData + BUILDING_RECORD_SIZE * building_index;
      if ( *(unsigned __int8 *)(uintptr_t)(building_offset + 509676) == g_CurrentPlayerIndex )
      {
        color_flags = *(_BYTE *)(uintptr_t)(building_offset + 510118) & 0xF8;
        *(_BYTE *)(uintptr_t)(building_offset + 510118) = color_flags;
        *(_BYTE *)(uintptr_t)(building_offset + 510118) = color_flags | 3;
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
      DD_Pump((int)(intptr_t)g_RenderState, a1);
    for ( i = cheat_buffer; ; *(i - 1) = Input_KeyToChar(popped_key) )
    {
      while ( 1 )
      {
        key_code = Input_PopKey();
        popped_key = key_code;
        if ( key_code != -1 )
          break;
        DD_Pump((int)(intptr_t)g_RenderState, -1);
      }
      pressed_key = key_code;
      while ( 1 )
      {
        result = Input_IsKeyPressed(pressed_key);
        if ( !result )
          break;
        DD_Pump((int)(intptr_t)g_RenderState, popped_key);
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
signed int Rules_ShowBanner_StrategicClash(void)
{
  int v0; // ecx
  int v1; // edx
  _DWORD v3[6]; // [esp-18h] [ebp-18h] BYREF

  CRT_ProbeStackFrame(32);
  v3[4] = v0;
  v3[3] = v1;
  Rules_Clear();
  return Rules_Bload((int)(intptr_t)aStrategClash_d, (DWORD)(intptr_t)v3);
}
// 451DFB: variable 'v0' is possibly undefined
// 451DFC: variable 'v1' is possibly undefined
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (00451E20) --------------------------------------------------------
int Rules_ResetEngineOnLoad(void)
{
  int result; // eax

  CRT_ProbeStackFrame(32);
  Rules_Reset();
  return result;
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (00451E46) --------------------------------------------------------
signed int Rules_CompileStrategicRulesFile(void)
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
  return Rules_Bload((int)(intptr_t)aStrategClash_d, (DWORD)(intptr_t)v3);
}
// 451E51: variable 'v0' is possibly undefined
// 451E52: variable 'v1' is possibly undefined
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);
// 47E7B0: using guessed type int __fastcall unknown_libname_7(int);

//----- (00451E87) --------------------------------------------------------
signed int Rules_RegisterAllHostFunctions(void)
{
  CRT_ProbeStackFrame(32);
  Rules_RegisterStrategicActionHostFunctions();
  Rules_RegisterBuildingHostFunctions();
  return Rules_RegisterArmyHostFunctions();
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (00451EC0) --------------------------------------------------------
int Rules_LogMissionSetupInfo(void)
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
    if ( *(_DWORD *)(uintptr_t)(player_record + 140024) )
    {
      formatted = sprintf_(
                    log_line,
                    "(gameinfo gracz %d komputer %d inteligencja %d chrzesc %d)",
                    player_index,
                    1 - *(_DWORD *)(uintptr_t)(player_record + 140051),
                    *(_DWORD *)(uintptr_t)(player_record + 140055),
                    *(_DWORD *)(uintptr_t)(player_record + 140063));
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
signed int Rules_ExecuteAITurn(void)
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
  formatted_turn = sprintf_(fact_text, "(tura %d)", *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET));
  g_AITurnLogFactHandle_Turn = (int)(intptr_t)Rules_Log(fact_text, 0, formatted_turn);
  formatted_player = sprintf_(fact_text, "(gracz %d inteligencja %d)", g_CurrentPlayerIndex, PLAYER_AI_INTELLIGENCE(g_CurrentPlayerIndex));
  g_AITurnPlayerIntelligenceFactHandle = (int)(intptr_t)Rules_Log(fact_text, 0, formatted_player);
  memset(fact_text, 0, 0xC8);
  castle_count = 0;
  building_index = 0;
LABEL_2:
  building_record = UNIT_RECORD(building_index);
  if ( (unsigned int)*(char *)(uintptr_t)(building_record + 4) < 4 && *(__int16 *)(uintptr_t)(building_record + 16) != -1 )
  {
    building_offset = gameData + BUILDING_RECORD_SIZE * building_index;
    if ( *(unsigned __int8 *)(uintptr_t)(building_offset + 509676) == g_CurrentPlayerIndex && *(_BYTE *)(uintptr_t)(building_offset + 509678) == 2 )
      ++castle_count;
  }
  while ( ++building_index < 100 )
  {
    if ( building_index >= 0 )
      goto LABEL_2;
  }
  formatted_castles = sprintf_(fact_text, "(ilosc-zamkow %d %d)", g_CurrentPlayerIndex, castle_count);
  g_AITurnCastleCountFactHandle = (int)(intptr_t)Rules_Log(fact_text, 0, formatted_castles);
  fortress_count = 0;
  fortress_scan_index = 0;
LABEL_11:
  fortress_record = UNIT_RECORD(fortress_scan_index);
  if ( (unsigned int)*(char *)(uintptr_t)(fortress_record + 4) < 4 && *(__int16 *)(uintptr_t)(fortress_record + 16) != -1 )
  {
    fortress_offset = gameData + BUILDING_RECORD_SIZE * fortress_scan_index;
    if ( *(unsigned __int8 *)(uintptr_t)(fortress_offset + 509676) == g_CurrentPlayerIndex && *(_BYTE *)(uintptr_t)(fortress_offset + 509678) == 1 )
      ++fortress_count;
  }
  while ( ++fortress_scan_index < 100 )
  {
    if ( fortress_scan_index >= 0 )
      goto LABEL_11;
  }
  formatted_fortresses = sprintf_(fact_text, "(ilosc-twierdz %d %d)", g_CurrentPlayerIndex, fortress_count);
  g_AiTurnFortressCountFactHandle = (int)(intptr_t)Rules_Log(fact_text, 0, formatted_fortresses);
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
    Debug_Log(0, a4, a5, (int)(intptr_t)aMkinstArmyS);
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
  int v9 CLASH95_UNUSED; // [esp+3E8h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+3ECh] [ebp-4h]

  stack = (__int16 *)result;
  v10 = a3;
  v9 = a2;
  if ( *(_DWORD *)((char *)result + 721) )
  {
    Rules_RetractFactById(*(_DWORD *)((char *)result + 721), a4);
    sprintf_(fact_text, "(usunieto armie %d )", *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(*stack, stack[1])));
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
signed int Rules_RegisterStrategicActionHostFunctions(void)
{
  CRT_ProbeStackFrame(36);
  Rules_RegisterHostFunction(aSwiatynia, 105, (int)(intptr_t)aSwiatynia00, (int)(intptr_t)&Rules_HostTemple, (int)(intptr_t)a22i_1);
  Rules_RegisterHostFunction(aKop_skarb, 105, (int)(intptr_t)aKop_skarb00, (int)(intptr_t)&Rules_HostDigTreasure, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aPobierz_oddz_0, 105, (int)(intptr_t)aPobierz_oddzia, (int)(intptr_t)&Rules_HostCollectPortSupply, (int)(intptr_t)a00i);
  Rules_RegisterHostFunction(aPelny_port, 98, (int)(intptr_t)aPelny_port00, (int)(intptr_t)&Rules_HostPortHasSupplyReady, (int)(intptr_t)a00i);
  Rules_RegisterHostFunction(aJest_pracown_0, 98, (int)(intptr_t)aJest_pracownik, (int)(intptr_t)&Rules_HostArmyHasBuilder, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aJednostka_bi_0, 98, (int)(intptr_t)aJednostka_bite, (int)(intptr_t)&Rules_HostArmyHasNormalCombatUnits, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aJest_droga, 98, (int)(intptr_t)aJest_droga00, (int)(intptr_t)&Rules_HostRoadExists, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aJest_droga_w_0, 98, (int)(intptr_t)aJest_droga_w_p, (int)(intptr_t)&Rules_HostRoadExistsNearby, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aJest_droga_w_2, 98, (int)(intptr_t)aJest_droga_w_1, (int)(intptr_t)&Rules_HostRoadExistsNearCastle, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aJest_droga_d_0, 98, (int)(intptr_t)aJest_droga_do_, (int)(intptr_t)&Rules_HostRoadExistsToPort, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aJest_droga_d_2, 98, (int)(intptr_t)aJest_droga_d_1, (int)(intptr_t)&Rules_HostRoadExistsToCastle, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aJest_droga_d_4, 98, (int)(intptr_t)aJest_droga_d_3, (int)(intptr_t)&Rules_HostRoadExistsToTemple, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aOddzial_w_za_1, 98, (int)(intptr_t)aOddzial_w_za_0, (int)(intptr_t)&Rules_HostTroopInArmyRange, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aBudowla_w_za_0, 98, (int)(intptr_t)aBudowla_w_zasi, (int)(intptr_t)&Rules_HostBuildingInArmyRange, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aOdleglosc_od_0, 105, (int)(intptr_t)aOdleglosc_od_o, (int)(intptr_t)&Rules_HostDistanceFromObject, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aSwiatynia_w__0, 98, (int)(intptr_t)aSwiatynia_w_za, (int)(intptr_t)&Rules_HostTempleInArmyRange, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aSwiatynia_ok, 98, (int)(intptr_t)aSwiatynia_ok00, (int)(intptr_t)&Rules_HostTempleOk, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aMaszeruj, 105, (int)(intptr_t)aMaszeruj00, (int)(intptr_t)&Rules_HostMarch, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aMaszeruj_do__0, 105, (int)(intptr_t)aMaszeruj_do_sw, (int)(intptr_t)&Rules_HostMarchToTemple, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aMaszeruj_bli_0, 105, (int)(intptr_t)aMaszeruj_blisk, (int)(intptr_t)&Rules_HostMarchNear, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aAtakuj_oddzi_0, 105, (int)(intptr_t)aAtakuj_oddzial, (int)(intptr_t)&Rules_HostAttackTroop, (int)(intptr_t)a22i_1);
  Rules_RegisterHostFunction(aPrzejmuj_odd_0, 105, (int)(intptr_t)aPrzejmuj_oddzi, (int)(intptr_t)&Rules_HostCaptureTroop, (int)(intptr_t)a22i_1);
  Rules_RegisterHostFunction(aUkryj_oddzial, 105, (int)(intptr_t)aUkryj_oddzial0, (int)(intptr_t)&Rules_HostHideTroop, (int)(intptr_t)a33i);
  Rules_RegisterHostFunction(aJest_armia, 98, (int)(intptr_t)aJest_armia00, (int)(intptr_t)&Rules_HostArmyExists, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aLiczba_jedno_0, 105, (int)(intptr_t)aLiczba_jednost, (int)(intptr_t)&Rules_HostUnitCountInTroop, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aAtakuj_budow_0, 105, (int)(intptr_t)aAtakuj_budowle, (int)(intptr_t)&Rules_HostAttackBuilding, (int)(intptr_t)a22i_1);
  Rules_RegisterHostFunction(aJest_brod, 98, (int)(intptr_t)aJest_brod00, (int)(intptr_t)&Rules_HostFordExists, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aBuduj_droge, 98, (int)(intptr_t)aBuduj_droge00, (int)(intptr_t)&Rules_HostBuildRoad, (int)(intptr_t)a11i);
  Rules_RegisterHostFunction(aBuduj_pulapke, 105, (int)(intptr_t)aBuduj_pulapke0, (int)(intptr_t)&Rules_HostBuildTrap, (int)(intptr_t)a33i);
  return Rules_RegisterHostFunction(aUnit_canmove, 105, (int)(intptr_t)aUnit_canmove00, (int)(intptr_t)&Rules_HostUnitCanMove, (int)(intptr_t)a11i);
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
