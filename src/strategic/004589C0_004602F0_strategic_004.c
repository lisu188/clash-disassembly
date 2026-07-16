/* Generated from src/recovered/rules/strategic/004506B0_strategic.inc.c; original address order retained. */
#include "../recovered_internal.h"

CLASH95_TEST_VISIBLE void Mission_TraceObjectiveBlocked (int mission_index, int detail_a, int detail_b, int detail_c);

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

CLASH95_TEST_VISIBLE void Mission_TraceObjectiveBlocked(int mission_index, int detail_a, int detail_b, int detail_c)
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
int Mission_CheckFailureCondition(void)
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
