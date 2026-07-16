/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "strategic_internal.h"
#include "strategic_state.h"
#include "../state/state_shared.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00455740) --------------------------------------------------------
void  Building_AdjustTaxRateByIndex(int building_index, int ebx0, float tax_delta)
{
  double new_rate; // st7
  double applied_rate; // st7
  int v5; // edx
  char tax_byte_upper; // ah
  float new_rate_float; // [esp+0h] [ebp-10h]

  new_rate = (double)(*(_BYTE *)(uintptr_t)(BUILDING_RECORD_SIZE * building_index + gameData + 510110) & 0x3F) + tax_delta;
  new_rate_float = new_rate;
  if ( new_rate <= g_Building_MaxTaxRate )
  {
    applied_rate = new_rate_float;
    _CHP(ebx0, LODWORD(new_rate_float));
    tax_byte_upper = *(_BYTE *)(uintptr_t)(v5 + 510110) & 0xC0;
    *(_BYTE *)(uintptr_t)(v5 + 510110) = tax_byte_upper;
    *(_BYTE *)(uintptr_t)(v5 + 510110) = (int)applied_rate & 0x3F | tax_byte_upper;
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
  return Building_IsUnitLicenceEligible((char *)(uintptr_t)(UNIT_RECORD(building_index)), licence_type);
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
  while ( *(char *)(uintptr_t)(building_offset + gameData + result + 510076) != licence_type )
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
    licence_unit_type = *(char *)(uintptr_t)(building_offset + gameData + result + 510076);
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
    if ( *(__int16 *)(uintptr_t)(garrison_slot + 509692) != -1
      && *(_BYTE *)(uintptr_t)(garrison_slot + 509701) == 100
      && !((unsigned __int8)(4 * *(_BYTE *)(uintptr_t)(building_record + slot_index + 510064)) >> 5)
      && (*(_BYTE *)(uintptr_t)(building_record + slot_index + 510064) & 7) == 0 )
    {
      leave_slot_indices[ready_count++] = slot_index;
    }
    ++slot_index;
    slot_offset += 31;
  }
  while ( slot_index < 10 && ready_count < 5 );
  if ( leave_slot_indices[0] == -1 )
    return 0;
  if ( Building_HasFreeAdjacentExitTile((unsigned __int8 *)(uintptr_t)(UNIT_RECORD(v14))) )
    return Building_UnitsLeave((unsigned __int8 *)(uintptr_t)(v11 + gameData + BUILDING_TABLE_OFFSET), leave_slot_indices, a3);
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
    if ( *(__int16 *)(uintptr_t)(garrison_slot + 509692) != -1
      && (*(_BYTE *)(uintptr_t)(garrison_slot + 509704) & 3u) < 2
      && (*(_BYTE *)(uintptr_t)(building_offset + gameData + slot_index + 510064) & 7) == 0 )
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
    if ( *(__int16 *)(uintptr_t)(garrison_slot + 509692) != -1
      && *(char *)(uintptr_t)(garrison_slot + 509701) < 50
      && !((unsigned __int8)(4 * *(_BYTE *)(uintptr_t)(building_offset + gameData + slot_index + 510064)) >> 5) )
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
    if ( *(__int16 *)(uintptr_t)(result + 509692) != -1 )
    {
      result = *(_BYTE *)(uintptr_t)(result + 509704) & 3;
      if ( result < 2 )
      {
        result = slot_index + building_record;
        if ( (*(_BYTE *)(uintptr_t)(slot_index + building_record + 510064) & 7) == 0 )
        {
          result = (unsigned __int8)(4 * *(_BYTE *)(uintptr_t)(result + 510064)) >> 5;
          if ( !result )
            result = (int)(intptr_t)Building_TrainUnit(building_offset + gameData + BUILDING_TABLE_OFFSET, slot_offset, building_offset);
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
    slot_unit_type = *(__int16 *)(uintptr_t)(garrison_slot + 509692);
    if ( slot_unit_type != -1 && *(char *)(uintptr_t)(garrison_slot + 509701) <= 90 )
    {
      slot_state_ptr = slot_index + building_offset + gameData;
      if ( (*(_BYTE *)(uintptr_t)(slot_state_ptr + 510064) & 7) == 0 && !((unsigned __int8)(4 * *(_BYTE *)(uintptr_t)(slot_state_ptr + 510064)) >> 5) )
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
  while ( *(__int16 *)(uintptr_t)(BUILDING_RECORD_SIZE * building_index + gameData + slot_offset + 509692) != leave_type )
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
  if ( Building_HasFreeAdjacentExitTile((unsigned __int8 *)(uintptr_t)(building_offset + gameData + BUILDING_TABLE_OFFSET)) )
    return Building_UnitsLeave((unsigned __int8 *)(uintptr_t)(building_offset + gameData + BUILDING_TABLE_OFFSET), leave_slot_indices, a4);
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
  return licence_slot_index != -1 && *(char *)(uintptr_t)(building_record + licence_slot_index + 510076) == licence_type;
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
    LOBYTE(name_char) = *(_BYTE *)(uintptr_t)(player_offset + gameData + char_index++ + 140028);
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
  while ( *(__int16 *)(uintptr_t)(building_offset + gameData + slot_offset + 509692) != sought_type )
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
void Map_RebuildCastleSiteAnchorCache(void)
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
  for ( row = 0; row < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET); ++row )
  {
    for ( column = 0; column < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET); ++column )
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
    if ( *(__int16 *)(uintptr_t)slotPtr != -1 )
    {
      meleeStrength = Unit_CalcEffectivenessA((char *)(uintptr_t)slotPtr, 0);
      damageStrength = Unit_CalcEffectivenessC((__int16 *)(uintptr_t)slotPtr);
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
  if ( *(_DWORD *)(uintptr_t)(result + 510137) )
  {
    moc_value[1] = 1;
    Rules_GetInstanceSlotValue(*(_DWORD *)(uintptr_t)(result + 510137), aMoc_1, building_index, moc_value);
    previous_strength = strength_value_ptr[4];
    result = Building_CalcGarrisonFactStrength(building_index);
    if ( previous_strength != result )
    {
      strength_value_ptr = Rules_AddIntegerValue(result);
      return Rules_PutInstanceSlotValue(*(_DWORD *)(uintptr_t)(building_offset + gameData + 510137), aMoc_2, instance_record, moc_value, a3);
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004561B0) --------------------------------------------------------
signed int Rules_RegisterBuildingHostFunctions(void)
{
  CRT_ProbeStackFrame(36);
  Rules_RegisterHostFunction(aLeczenie, 118, (int)(intptr_t)aLeczenie, (int)(intptr_t)&Rules_HostHealing, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aSzkolenie, 118, (int)(intptr_t)aSzkolenie, (int)(intptr_t)&Rules_HostTraining, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aPalBudowle, 118, (int)(intptr_t)aPalbudowle, (int)(intptr_t)&Rules_HostBurnBuildings, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aUpgradeWall, 118, (int)(intptr_t)aUpgradewall, (int)(intptr_t)&Rules_HostUpgradeWall, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aZmienPodatek, 118, (int)(intptr_t)aZmienpodatek, (int)(intptr_t)&Rules_HostChangeTax, (int)(intptr_t)a22iif);
  Rules_RegisterHostFunction(aRemoveLicence, 118, (int)(intptr_t)aRemovelicence, (int)(intptr_t)&Rules_HostRemoveLicence, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aZacznijLeczeni, 118, (int)(intptr_t)aZacznijleczeni, (int)(intptr_t)&Rules_HostStartHealing, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aZacznijSzkolen, 118, (int)(intptr_t)aZacznijszkolen, (int)(intptr_t)&Rules_HostStartTraining, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aZacznijProdukc, 118, (int)(intptr_t)aZacznijprodukc, (int)(intptr_t)&Rules_HostStartProduction, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aKupSzkola, 98, (int)(intptr_t)aKupszkola, (int)(intptr_t)&Rules_HostBuySchool, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aKupKuznia, 98, (int)(intptr_t)aKupkuznia, (int)(intptr_t)&Rules_HostBuyForge, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aIsLicence, 98, (int)(intptr_t)aIslicence, (int)(intptr_t)&Rules_HostIsLicence, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aBuyLicence, 98, (int)(intptr_t)aBuylicence, (int)(intptr_t)&Rules_HostBuyLicence, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aKupSzpital, 98, (int)(intptr_t)aKupszpital, (int)(intptr_t)&Rules_HostBuyHospital, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aBudujZamek, 98, (int)(intptr_t)aBudujzamek, (int)(intptr_t)&Rules_HostBuildCastle, (int)(intptr_t)a55iiiiis);
  Rules_RegisterHostFunction(aKupKoszary, 98, (int)(intptr_t)aKupkoszary, (int)(intptr_t)&Rules_HostBuyBarracks, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aKupWarsztat, 98, (int)(intptr_t)aKupwarsztat, (int)(intptr_t)&Rules_HostBuyWorkshop, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aIsProduction, 98, (int)(intptr_t)aIsproduction, (int)(intptr_t)&Rules_HostIsProduction, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aCzyMinimalny, 98, (int)(intptr_t)aCzyminimalny, (int)(intptr_t)&Rules_HostIsMinimal, (int)(intptr_t)a44i);
  Rules_RegisterHostFunction(aCanBuyLicence, 98, (int)(intptr_t)aCanbuylicence, (int)(intptr_t)&Rules_HostCanBuyLicence, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aIsProductionAn, 98, (int)(intptr_t)aIsproductionan, (int)(intptr_t)&Rules_HostIsProductionAny, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aMaxIloscOddzia, 98, (int)(intptr_t)aMaxiloscoddzia, (int)(intptr_t)&Rules_HostMaxTroopCount, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aJednostkiDoSzk, 98, (int)(intptr_t)aJednostkidoszk, (int)(intptr_t)&Rules_HostUnitsToSchool, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aJednostkiDoSzp, 98, (int)(intptr_t)aJednostkidoszp, (int)(intptr_t)&Rules_HostUnitsToHospital, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aJestJednostkaW, 98, (int)(intptr_t)aJestjednostkaw, (int)(intptr_t)&Rules_HostUnitInCastleExists, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aPodatek, 105, (int)(intptr_t)aPodatek, (int)(intptr_t)&Rules_HostTax, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aPieniadze, 105, (int)(intptr_t)aPieniadze, (int)(intptr_t)&Rules_HostMoney, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aSilaMurow, 105, (int)(intptr_t)aSilamurow, (int)(intptr_t)&Rules_HostWallStrength, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aSilaZamku, 105, (int)(intptr_t)aSilazamku, (int)(intptr_t)&Rules_HostCastleStrength, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aNumerTury, 105, (int)(intptr_t)aNumertury, (int)(intptr_t)&Rules_HostTurnNumber, (int)(intptr_t)a00i_0);
  Rules_RegisterHostFunction(aPoziomTech, 105, (int)(intptr_t)aPoziomtech, (int)(intptr_t)&Rules_HostTechLevel, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aZadowolenie, 105, (int)(intptr_t)aZadowolenie, (int)(intptr_t)&Rules_HostHappiness, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aTypBudowli, 105, (int)(intptr_t)aTypbudowli, (int)(intptr_t)&Rules_HostBuildingType, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aSilaGracza, 105, (int)(intptr_t)aSilagracza, (int)(intptr_t)&Rules_HostPlayerStrength, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aIloscChlopow, 105, (int)(intptr_t)aIloscchlopow, (int)(intptr_t)&Rules_HostPeasantCount, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aLicencjaIndex, 105, (int)(intptr_t)aLicencjaindex, (int)(intptr_t)&Rules_HostLicenceIndex, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aLicencjaInd, 105, (int)(intptr_t)aLicencjaind, (int)(intptr_t)&Rules_HostLicenceInd, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aIloscOddzialow, 105, (int)(intptr_t)aIloscoddzialow, (int)(intptr_t)&Rules_HostTroopCount, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aCanUpgradeWall, 105, (int)(intptr_t)aCanupgradewall, (int)(intptr_t)&Rules_HostCanUpgradeWall, (int)(intptr_t)a11i_3);
  Rules_RegisterHostFunction(aWyprowadzChlop, 105, (int)(intptr_t)aWyprowadzchlop, (int)(intptr_t)&Rules_HostLeadOutPeasants, (int)(intptr_t)a44i);
  Rules_RegisterHostFunction(aWyprowadzenieO, 105, (int)(intptr_t)aWyprowadzenieo, (int)(intptr_t)&Rules_HostLeadOutTroop, (int)(intptr_t)a22i);
  Rules_RegisterHostFunction(aWyprowadzeni_1, 105, (int)(intptr_t)aWyprowadzeni_0, (int)(intptr_t)&Rules_HostLeadOutTroops, (int)(intptr_t)a11i_3);
  return Rules_RegisterHostFunction(aNazwaZamku, 115, (int)(intptr_t)aNazwazamku, (int)(intptr_t)&Rules_HostCastleName, (int)(intptr_t)a11i_3);
}
// 47C181: using guessed type _DWORD __stdcall sub_47C181(_DWORD);

//----- (004570E3) --------------------------------------------------------
signed int Rules_RegisterArmyHostFunctions(void)
{
  CRT_ProbeStackFrame(36);
  Rules_RegisterHostFunction(aWejdzDoZamku, 98, (int)(intptr_t)aWejdzdozamku, (int)(intptr_t)&Rules_HostEnterCastle, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aDolaczDoOddzia, 98, (int)(intptr_t)aDolaczdoarmii, (int)(intptr_t)&Rules_HostJoinTroop, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aPrzegrupujOddz, 98, (int)(intptr_t)aPrzegrupujarmi, (int)(intptr_t)&Rules_HostRegroupTroops, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aPrzegrupujZame, 98, (int)(intptr_t)aPrzegrupujzame, (int)(intptr_t)&Rules_HostRegroupCastle, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aLiczbaWolnychM, 105, (int)(intptr_t)aLiczbawolnychm, (int)(intptr_t)&Rules_HostCastleFreeSlotCount, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aZnajdzDrogeWPo, 98, (int)(intptr_t)aZnajdzdrogewpo, (int)(intptr_t)&Rules_HostFindRoadNearCastle, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aMocPrzeciwnika, 105, (int)(intptr_t)aMocprzeciwnika, (int)(intptr_t)&Rules_HostEnemyPowerAtWalls, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aStanOsobArmii, 105, (int)(intptr_t)aStanosobarmii, (int)(intptr_t)&Rules_HostArmyHeadcount, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aArmiaMaJednost, 98, (int)(intptr_t)aArmiamajednost, (int)(intptr_t)&Rules_HostArmyHasUnitsOfType, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aArmiaTylkoJedn, 98, (int)(intptr_t)aArmiatylkojedn, (int)(intptr_t)&Rules_HostArmyHasOnlyUnitType, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aMaJednostkiDoL, 98, (int)(intptr_t)aMajednostkidol, (int)(intptr_t)&Rules_HostHasUnitsToHeal, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aZnajdzZamekDoL, 98, (int)(intptr_t)aZnajdzzamekdol, (int)(intptr_t)&Rules_HostFindCastleForHealing, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aIdzDoLeczenia, 98, (int)(intptr_t)aIdzdoleczenia, (int)(intptr_t)&Rules_HostGoToHealing, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aJestZarazaWZam, 98, (int)(intptr_t)aJestzarazawzam, (int)(intptr_t)&Rules_HostPlagueInCastleExists, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aJestZarazaWOdd, 98, (int)(intptr_t)aJestzarazawodd, (int)(intptr_t)&Rules_HostPlagueInTroopExists, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aOdlaczJednostk, 98, (int)(intptr_t)aOdlaczjednostk, (int)(intptr_t)&Rules_HostDetachWeakUnits, (int)(intptr_t)a11i_0);
  Rules_RegisterHostFunction(aOdlaczJednos_0, 98, (int)(intptr_t)aOdlaczjednos_0, (int)(intptr_t)&Rules_HostDetachUnitsOfType, (int)(intptr_t)a22i_0);
  Rules_RegisterHostFunction(aMaszerujWzdluz, 98, (int)(intptr_t)aMaszerujwzdluz, (int)(intptr_t)&Rules_HostMarchAlongRoad, (int)(intptr_t)a11i_0);
  return Rules_RegisterHostFunction(aZnajdzNajlepsz, 105, (int)(intptr_t)aZnajdz_najleps, (int)(intptr_t)&Rules_HostFindBest, (int)(intptr_t)a55i);
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
  unit_slot = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6);
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
  building_status = *(char *)(uintptr_t)(building_record + 4);
  if ( building_status < 4 && *(__int16 *)(uintptr_t)(building_record + 16) != -1 && (*(_DWORD *)(uintptr_t)(building_cursor + 416) & BUILDING_ADDON_FLAG_HOSPITAL) == 1 )
  {
    track = (_DWORD *)Building_GenerateApproachTrack(stack_index, building_index, building_status, building_index, stack_index);
    track_ptr = track;
    if ( track )
    {
      track_info = track[1];
      if ( best_building_index == -1 )
      {
        qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track, UNIT_STACK_PATH_BYTES);
        track_cost = HIWORD(track_info);
      }
      else
      {
        if ( HIWORD(track_info) >= best_cost )
          goto LABEL_9;
        j__nfree_();
        qmemcpy((void *)(uintptr_t)(v9 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), track_ptr, UNIT_STACK_PATH_BYTES);
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
  return *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * v4 + 147180) == -1;
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
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * v5 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
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
  building_x = *(unsigned __int8 *)(uintptr_t)(gameData + building_offset + BUILDING_TABLE_OFFSET);
  building_y = *(unsigned __int8 *)(uintptr_t)(gameData + building_offset + 509675);
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
        && scan_x < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
        && scan_y >= 0
        && scan_y < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
        && *(unsigned __int16 *)(uintptr_t)(j + gameData + i + TILE_MAP_OFFSET) <= 0x1F4u
        && (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(j + gameData + i + TILE_MAP_OFFSET) + 6) <= 0x28 )
      {
        stack_offset = UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(j + gameData + i + TILE_MAP_OFFSET);
        if ( *(_BYTE *)(uintptr_t)(gameData + stack_offset + 147178) != *(_BYTE *)(uintptr_t)(gameData + building_record_offset + 509676)
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
  return *(_BYTE *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * building_index + 510109) & 7;
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
  return *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * v4 + 147490) == 0;
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
  stack_record = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * army_index + gameData + UNIT_STACK_TABLE_OFFSET);
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
  if ( !selected_count || selected_count == Unit_GetSquadCount((int)(intptr_t)stack_record) )
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
          && dest_tile_x < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
          && dest_tile_y >= 0
          && dest_tile_y < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
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
  stack_record = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * army_index + gameData + UNIT_STACK_TABLE_OFFSET);
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
  if ( !selected_count || selected_count == Unit_GetSquadCount((int)(intptr_t)stack_record) )
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
          && dest_tile_x < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
          && dest_tile_y >= 0
          && dest_tile_y < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
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
  for ( i = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6); ; i = (__int16 *)((char *)i + 31) )
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
  for ( i = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index + 6); ; i = (__int16 *)((char *)i + 31) )
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
  aggregate_health = *(char *)(uintptr_t)(slot_base + 9);
  unit_slot = (__int16 *)(uintptr_t)(slot_base + 31);
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
  Debug_Log(a1, a3, a4, (int)(intptr_t)aPrzegrupujar_0);
  dx = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index_reg + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET);
  if ( (int)abs32(dx) > 1
    || (dy = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index_reg + 147176) - *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * other_stack_index + gameData + 147176),
        (int)((HIDWORD(dy) ^ dy) - HIDWORD(dy)) > 1) )
  {
    result = (int)(intptr_t)Unit_MoveTrackNearTile(
                    stack_index,
                    *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET),
                    v6,
                    *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * other_stack_index + 147176),
                    dx);
    if ( !result )
      return result;
    qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(stack_index, 1, -43 * stack_index, dx, a5);
  }
  dx_second = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET);
  if ( (int)abs32(dx_second) > 1
    || (dy_second = *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + 147176) - *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * other_stack_index + gameData + 147176),
        (int)((HIDWORD(dy_second) ^ dy_second) - HIDWORD(dy_second)) > 1) )
  {
    result = (int)(intptr_t)Unit_MoveTrackNearTile(
                    other_stack_index,
                    *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
                    v6,
                    *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
                    dx_second);
    if ( !result )
      return result;
    qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(other_stack_index, 1, -111 * other_stack_index, dx_second, a5);
  }
  first_stack_offset = UNIT_STACK_STRIDE * stack_index;
  dx_recheck = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET) - *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * other_stack_index + UNIT_STACK_TABLE_OFFSET);
  if ( (int)((HIDWORD(dx_recheck) ^ dx_recheck) - HIDWORD(dx_recheck)) > 1 )
    return 0;
  dy_recheck = *(__int16 *)(uintptr_t)(gameData + first_stack_offset + 147176) - *(__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * other_stack_index + gameData + 147176);
  if ( (int)((HIDWORD(dy_recheck) ^ dy_recheck) - HIDWORD(dy_recheck)) > 1 )
    return 0;
  copy_count_first = 0;
  total_units = 0;
  first_stack_record = gameData + UNIT_STACK_TABLE_OFFSET + first_stack_offset;
  copy_dest = merged_units;
  first_src_slot = (__int16 *)(uintptr_t)(first_stack_record + 6);
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
  second_src_slot = (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * other_stack_index + 6);
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
  first_dest_slot = (_WORD *)(uintptr_t)(UNIT_STACK_STRIDE * stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 6);
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
  second_dest_slot = (_WORD *)(uintptr_t)(UNIT_STACK_STRIDE * other_stack_index + gameData + UNIT_STACK_TABLE_OFFSET + 6);
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
    UnitStack_KillByIndex(stack_index, (char)(intptr_t)writeback_src_second, writeback_index_second, a5);
  if ( units_kept_first == total_units )
    UnitStack_KillByIndex(other_stack_index, (char)(intptr_t)writeback_src_second, writeback_index_second, a5);
  return 1;
}
// 4582F8: variable 'v5' is possibly undefined
// 45839D: variable 'v6' is possibly undefined
// 5202E4: using guessed type int gameData;
