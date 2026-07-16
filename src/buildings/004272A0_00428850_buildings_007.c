/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004272A0) --------------------------------------------------------
int  UnitBattle_PlayAttackAnimation(int a1, int a2, int a3, int a4, unsigned __int16 *a5)
{
  __int16 *attacker_unit; // esi
  char attacker_owner; // bl
  int v7; // ecx
  _DWORD *attacker_sprite_set; // eax
  char defender_owner; // bl
  int v10; // ecx
  _DWORD *defender_sprite_set; // eax
  signed int impact_offset_x; // ebp
  unsigned int direction; // edi
  int dir_index; // ebx
  unsigned __int16 *SpriteForChar CLASH95_UNUSED; // eax
  int v16 CLASH95_UNUSED; // eax
  unsigned __int16 *v17 CLASH95_UNUSED; // ecx
  unsigned __int16 *v18 CLASH95_UNUSED; // eax
  unsigned __int16 *v19 CLASH95_UNUSED; // ecx
  int v20 CLASH95_UNUSED; // eax
  int v21 CLASH95_UNUSED; // edx
  int vertical_offset; // edx
  int v23; // edx
  int v24; // ecx
  int v25 CLASH95_UNUSED; // ecx
  int anim_start_time; // ebx
  int v27; // eax
  int v28; // edx
  int v29; // eax
  int move_tick_interval_ms; // edx
  int v31; // ecx
  int v32; // eax
  unsigned __int8 v33 CLASH95_UNUSED; // dl
  char tick_parity; // al
  int v35; // eax
  int v36; // edx
  int v37; // eax
  int attacker_type_move; // eax
  int step_dir_x; // eax
  unsigned __int16 *v40 CLASH95_UNUSED; // eax
  signed int v41 CLASH95_UNUSED; // ebp
  unsigned __int16 *v42 CLASH95_UNUSED; // ecx
  int v43 CLASH95_UNUSED; // eax
  unsigned __int16 *v44 CLASH95_UNUSED; // eax
  unsigned __int16 *v45 CLASH95_UNUSED; // ecx
  int v46 CLASH95_UNUSED; // eax
  int v47 CLASH95_UNUSED; // edx
  unsigned __int16 *attacker_sprite_alone; // eax
  int v49 CLASH95_UNUSED; // eax
  int v50; // eax
  int sign_x; // edx
  int v52; // eax
  int v53; // eax
  int sign_y; // ecx
  int v55; // eax
  int v56; // eax
  int v57; // edx
  int v58; // eax
  char attacker_owner_attack; // bl
  int v60; // ecx
  _DWORD *attack_sprite_set; // eax
  int v62; // ecx
  int v63; // eax
  int v64; // ecx
  int v65; // ebx
  int v66; // ecx
  int v67; // eax
  unsigned int v68 CLASH95_UNUSED; // edx
  int attacker_unit_type; // eax
  int v70; // edx
  int v71; // edx
  int v73; // eax
  int v74 CLASH95_UNUSED; // edx
  int v75 CLASH95_UNUSED; // ecx
  int v76 CLASH95_UNUSED; // edx
  int v77 CLASH95_UNUSED; // edx
  int v78 CLASH95_UNUSED; // ecx
  int v79; // eax
  int v80 CLASH95_UNUSED; // edx
  char attacker_owner_return; // bl
  int v82; // ecx
  _DWORD *return_sprite_set; // eax
  int v84; // edx
  int v85; // ebx
  int v86; // ecx
  int v87; // eax
  int v88; // ecx
  unsigned int arrival_tick_interval_ms; // edx
  char arrival_parity; // al
  int attacker_type_arrival; // eax
  int v92; // edx
  int arrival_step_dir_x; // eax
  int arrival_step_dir_y; // eax
  int v95; // ecx
  int v96; // edx
  char v97[100]; // [esp+0h] [ebp-88h] BYREF
  int defender_dead; // [esp+64h] [ebp-24h]
  int attacker_dead; // [esp+68h] [ebp-20h]
  unsigned __int16 *defender_unit; // [esp+6Ch] [ebp-1Ch]
  int defender_index; // [esp+70h] [ebp-18h]
  int attacker_index; // [esp+74h] [ebp-14h]
  int impact_offset_y; // [esp+78h] [ebp-10h]

  attacker_index = a1;
  defender_index = a2;
  attacker_dead = a4;
  defender_dead = a3;
  Debug_Log(a3, a4, (DWORD)(intptr_t)a5, (int)(intptr_t)aAttackanimDD);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Busy);
  attacker_unit = (__int16 *)(uintptr_t)(g_MapData + 852 + 31 * attacker_index);
  if ( defender_index == -1 )
    defender_unit = 0;
  else
    defender_unit = (unsigned __int16 *)(uintptr_t)(31 * defender_index + g_MapData + 852);
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3])
    || (a5 = defender_unit) != 0 && !UnitBattle_IsTileInViewport(defender_unit[2], defender_unit[3]) )
  {
    UnitBattle_CenterViewOnUnit(attacker_index);
    UnitBattle_RedrawVisibleGrid();
  }
  if ( defender_unit )
    *((_BYTE *)attacker_unit + 3) = Facing_DirectionFromDelta8(defender_unit[2] - (unsigned __int16)attacker_unit[2], defender_unit[3] - (unsigned __int16)attacker_unit[3]);
  attacker_owner = *((_BYTE *)attacker_unit + 2);
  Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)attacker_unit, attacker_owner);
  attacker_sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v7, attacker_owner, (DWORD)(intptr_t)a5);
  if ( attacker_sprite_set )
    attacker_sprite_set = DLXSpriteSet_Load(attacker_sprite_set, v97);
  g_ActiveUnitAnimSpriteSet = (int)(intptr_t)attacker_sprite_set;
  if ( defender_index != -1 )
  {
    defender_owner = *((_BYTE *)defender_unit + 2);
    Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)defender_unit, defender_owner);
    defender_sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v10, defender_owner, (DWORD)(intptr_t)a5);
    if ( defender_sprite_set )
      defender_sprite_set = DLXSpriteSet_Load(defender_sprite_set, v97);
    g_UnitBattleAnimatingUnitSpriteSet = (int)(intptr_t)defender_sprite_set;
  }
  impact_offset_x = 0;
  direction = *((unsigned __int8 *)attacker_unit + 3);
  impact_offset_y = 0;
  if ( defender_unit )
  {
    unsigned __int16 *defender_sprite;
    unsigned __int16 *attacker_sprite;

    defender_sprite = (unsigned __int16 *)(uintptr_t)UnitSpriteCache_FindEntryOrLoad(*defender_unit, *((_BYTE *)defender_unit + 2), 0, *((_BYTE *)defender_unit + 3));
    dir_index = 8 * *((unsigned __int8 *)attacker_unit + 3);
    if ( direction == 7 || direction == 6 || direction == 5 )
    {
      attacker_sprite = (unsigned __int16 *)(uintptr_t)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      impact_offset_x = -UnitBattle_ScanSpriteFirstOpaqueRunLength(attacker_sprite) - UnitBattle_ScanSpriteMinOpaqueRunLength(defender_sprite);
    }
    else if ( direction == 1 || direction == 2 || direction == 3 )
    {
      attacker_sprite = (unsigned __int16 *)(uintptr_t)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      impact_offset_x = UnitBattle_ScanSpriteMinOpaqueRunLength(attacker_sprite) + UnitBattle_ScanSpriteFirstOpaqueRunLength(defender_sprite);
    }
    if ( direction == 7 || direction < 2 )
    {
      attacker_sprite = (unsigned __int16 *)(uintptr_t)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      vertical_offset = -UnitBattle_CountLeadingBlankSpriteRows(attacker_sprite) - UnitBattle_CountTrailingBlankSpriteRows(defender_sprite);
    }
    else
    {
      if ( direction != 5 && direction != 4 && direction != 3 )
        goto LABEL_20;
      attacker_sprite = (unsigned __int16 *)(uintptr_t)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, dir_index);
      vertical_offset = UnitBattle_CountTrailingBlankSpriteRows(attacker_sprite) + UnitBattle_CountLeadingBlankSpriteRows(defender_sprite);
    }
    impact_offset_y = vertical_offset;
    goto LABEL_20;
  }
  attacker_sprite_alone = (unsigned __int16 *)(uintptr_t)DLX_GetSpriteForChar(g_ActiveUnitAnimSpriteSet, 8 * direction);
  if ( direction == 6 )
  {
    impact_offset_x = -UnitBattle_ScanSpriteFirstOpaqueRunLength(attacker_sprite_alone);
  }
  else
  {
    impact_offset_x = UnitBattle_ScanSpriteMinOpaqueRunLength(attacker_sprite_alone);
  }
LABEL_20:
  if ( !impact_offset_x || !impact_offset_y )
    goto LABEL_21;
  if ( impact_offset_x <= 0 )
    v50 = -1;
  else
    v50 = 1;
  sign_x = v50;
  if ( impact_offset_y <= 0 )
    v52 = -impact_offset_y;
  else
    v52 = impact_offset_y;
  if ( impact_offset_x <= 0 )
    impact_offset_x = -impact_offset_x;
  if ( impact_offset_x <= v52 )
    impact_offset_x = v52;
  impact_offset_x *= sign_x;
  if ( impact_offset_y <= 0 )
    v53 = -1;
  else
    v53 = 1;
  sign_y = v53;
  if ( impact_offset_y <= 0 )
    v55 = -impact_offset_y;
  else
    v55 = impact_offset_y;
  if ( impact_offset_x <= 0 )
  {
    if ( -impact_offset_x > v55 )
    {
      impact_offset_y = -impact_offset_x * sign_y;
      goto LABEL_21;
    }
LABEL_82:
    impact_offset_y = v55 * sign_y;
    goto LABEL_21;
  }
  if ( impact_offset_x <= v55 )
    goto LABEL_82;
  impact_offset_y = impact_offset_x * sign_y;
LABEL_21:
  v23 = 8;
  v24 = 0;
  g_ActiveUnitMoveTileIndex = attacker_index;
  g_UnitMoveAnimOffsetX = 0;
  g_UnitMoveAnimOffsetY = 0;
  g_UnitAnimFrameIndex = 0;
  g_UnitBattleAnimFrameCount = 8;
LABEL_22:
  anim_start_time = Time_Now(v24, v23);
  while ( 1 )
  {
    v27 = g_UnitMoveAnimOffsetX;
    if ( g_UnitMoveAnimOffsetX <= 0 )
      v27 = -g_UnitMoveAnimOffsetX;
    v28 = v27;
    v29 = impact_offset_x <= 0 ? -impact_offset_x : impact_offset_x;
    if ( v28 >= v29 )
    {
      v56 = g_UnitMoveAnimOffsetY;
      if ( g_UnitMoveAnimOffsetY <= 0 )
        v56 = -g_UnitMoveAnimOffsetY;
      v57 = v56;
      v58 = impact_offset_y;
      if ( impact_offset_y <= 0 )
        v58 = -impact_offset_y;
      if ( v57 >= v58 )
        break;
    }
    UnitBattle_UpdateIdleAnimatedUnits();
    DD_Pump((int)(intptr_t)g_RenderState, anim_start_time);
    move_tick_interval_ms = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *attacker_unit];
    v32 = Time_Now(v31, move_tick_interval_ms);
    if ( v32 - anim_start_time >= (unsigned int)move_tick_interval_ms )
    {
      tick_parity = g_UnitMoveAnimTickParityCounter++;
      if ( (tick_parity & 1) != 0 )
        g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
      v35 = g_UnitMoveAnimOffsetX;
      if ( g_UnitMoveAnimOffsetX <= 0 )
        v35 = -g_UnitMoveAnimOffsetX;
      v36 = v35;
      if ( impact_offset_x <= 0 )
        v37 = -impact_offset_x;
      else
        v37 = impact_offset_x;
      if ( v36 >= v37 )
      {
        v73 = g_UnitMoveAnimOffsetY;
        if ( g_UnitMoveAnimOffsetY <= 0 )
          v73 = -g_UnitMoveAnimOffsetY;
        if ( impact_offset_y <= 0 )
        {
          if ( v73 >= -impact_offset_y )
            break;
        }
        else if ( v73 >= impact_offset_y )
        {
          break;
        }
      }
      attacker_type_move = *attacker_unit;
      if ( attacker_type_move == 27 || attacker_type_move == 30 )
      {
        UnitBattle_RedrawUnitNeighborhood(attacker_index);
      }
      else
      {
        UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3]);
        if ( direction == 4 || direction == 5 || direction == 3 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] + 1);
        if ( !direction || direction == 7 || direction == 1 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] - 1);
        if ( direction == 2 || direction == 3 || direction == 1 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3]);
        if ( direction == 6 || direction == 5 || direction == 7 )
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3]);
        switch ( direction )
        {
          case 3u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] + 1);
            break;
          case 1u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] - 1);
            break;
          case 5u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] + 1);
            break;
          case 7u:
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] - 1);
            break;
        }
      }
      if ( impact_offset_x - g_UnitMoveAnimOffsetX <= 0 )
      {
        if ( impact_offset_x == g_UnitMoveAnimOffsetX )
          step_dir_x = v24;
        else
          step_dir_x = -1;
      }
      else
      {
        step_dir_x = 1;
      }
      g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit] * step_dir_x;
      v23 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit];
      if ( impact_offset_y - g_UnitMoveAnimOffsetY <= 0 )
      {
        if ( impact_offset_y == g_UnitMoveAnimOffsetY )
          g_UnitMoveAnimOffsetY += v23 * v24;
        else
          g_UnitMoveAnimOffsetY -= v23;
      }
      else
      {
        g_UnitMoveAnimOffsetY += v23;
      }
      goto LABEL_22;
    }
  }
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  attacker_owner_attack = *((_BYTE *)attacker_unit + 2);
  Unit_BuildAttackAnimSpritePath(v97, *(_BYTE *)attacker_unit, attacker_owner_attack);
  attack_sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v60, attacker_owner_attack, impact_offset_x);
  if ( attack_sprite_set )
    attack_sprite_set = DLXSpriteSet_Load(attack_sprite_set, v97);
  g_ActiveUnitAnimSpriteSet = (int)(intptr_t)attack_sprite_set;
  g_UnitMoveAnimOffsetX = impact_offset_x;
  g_UnitAnimFrameIndex = 0;
  g_UnitMoveAnimOffsetY = impact_offset_y;
  g_UnitBattleAnimFrameCount = (unsigned __int8)g_UnitTypeAttackAnimationFrameCount[88 * *attacker_unit];
  v63 = Time_Now(v62, 0);
  v64 = 31 * attacker_index;
  v65 = v63;
  while ( g_UnitAnimFrameIndex < g_UnitBattleAnimFrameCount )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    DD_Pump((int)(intptr_t)g_RenderState, v65);
    attacker_unit_type = *(__int16 *)(uintptr_t)(v64 + g_MapData + 852);
    v70 = (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * attacker_unit_type];
    v67 = Time_Now(v66, v70);
    if ( v67 - v65 >= (unsigned int)v70 )
    {
      attacker_unit_type = *(__int16 *)(uintptr_t)(v64 + g_MapData + 852);
      v70 = (unsigned __int8)g_UnitTypeAttackSoundFrameIndex[88 * attacker_unit_type];
      if ( v70 == g_UnitAnimFrameIndex )
        Audio_PlayUnitMeleeAttackSound(attacker_unit_type);
      v65 = Time_Now(v64, v70);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] - 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3]);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3]);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3]);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] + 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] + 1);
      UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] + 1);
      ++g_UnitAnimFrameIndex;
    }
  }
  g_UnitAnimFrameIndex = 0;
  if ( defender_index != -1 )
  {
    if ( defender_dead )
    {
      UnitBattle_PlayDeathAnimation(defender_index, v64, v65, impact_offset_x);
    }
    else
    {
      Audio_PlayUnitHitSound((__int16)*defender_unit);
      g_UnitBattleAnimatingUnitIndex = defender_index;
      g_UnitBattleHitAnimFrame = Rng_RandRange(0, 7);
      v64 = Time_Now(0, 3);
      impact_offset_x = Rng_RandRange(1, 3);
      while ( impact_offset_x >= 0 )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)(intptr_t)g_RenderState, 0);
        v79 = Time_Now(0, 0);
        if ( (unsigned int)(v79 - v64) >= 3 )
        {
          v64 = Time_Now(0, 0);
          UnitBattle_RedrawUnitNeighborhood(defender_index);
          LOBYTE(v65) = (g_UnitBattleHitAnimFrame + 1) & 7;
          --impact_offset_x;
          g_UnitBattleHitAnimFrame = (unsigned __int8)v65;
        }
      }
      g_UnitBattleAnimatingUnitIndex = -1;
    }
  }
  if ( attacker_dead )
  {
    if ( g_UnitBattleChargeModeActive_532060 )
      UnitBattle_RefreshSelectedUnitUI();
    UnitBattle_PlayDeathAnimation(attacker_index, v64, v65, impact_offset_x);
  }
  v71 = attacker_dead;
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  if ( !v71 )
  {
    attacker_owner_return = *((_BYTE *)attacker_unit + 2);
    Unit_BuildGoSpriteFilePath(v97, *(_BYTE *)attacker_unit, attacker_owner_return);
    return_sprite_set = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v82, attacker_owner_return, impact_offset_x);
    if ( return_sprite_set )
      return_sprite_set = DLXSpriteSet_Load(return_sprite_set, v97);
    LOBYTE(v85) = 8;
    g_ActiveUnitAnimSpriteSet = (int)(intptr_t)return_sprite_set;
    g_UnitAnimFrameIndex = 0;
    g_UnitBattleAnimFrameCount = 8;
    v88 = Time_Now(0, v84);
    while ( g_UnitMoveAnimOffsetX || g_UnitMoveAnimOffsetY )
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)(intptr_t)g_RenderState, 0);
      arrival_tick_interval_ms = (unsigned __int8)g_UnitTypeMoveAnimationTickIntervalMs[88 * *attacker_unit];
      v87 = Time_Now(v86, arrival_tick_interval_ms);
      if ( v87 - v88 >= arrival_tick_interval_ms )
      {
        arrival_parity = g_UnitArrivalAnimTickParityCounter++;
        if ( (arrival_parity & 1) != 0 )
          g_UnitAnimFrameIndex = ((_BYTE)g_UnitAnimFrameIndex + 1) & 7;
        if ( !g_UnitMoveAnimOffsetX && !g_UnitMoveAnimOffsetY )
          break;
        attacker_type_arrival = *attacker_unit;
        if ( attacker_type_arrival == 27 || attacker_type_arrival == 30 )
        {
          UnitBattle_RedrawUnitNeighborhood(attacker_index);
        }
        else
        {
          UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3]);
          if ( direction == 4 || direction == 5 || direction == 3 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] + 1);
          if ( !direction || direction == 7 || direction == 1 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3] - 1);
          if ( direction == 2 || direction == 3 || direction == 1 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3]);
          if ( direction == 6 || direction == 5 || direction == 7 )
            UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3]);
          switch ( direction )
          {
            case 3u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] + 1);
              break;
            case 1u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] + 1, (unsigned __int16)attacker_unit[3] - 1);
              break;
            case 5u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] + 1);
              break;
            case 7u:
              UnitBattle_RedrawTile((unsigned __int16)attacker_unit[2] - 1, (unsigned __int16)attacker_unit[3] - 1);
              break;
          }
        }
        v92 = g_UnitMoveAnimOffsetX;
        v85 = g_UnitMoveAnimOffsetY;
        if ( -g_UnitMoveAnimOffsetX < 0 || g_UnitMoveAnimOffsetX == 0 )
        {
          if ( g_UnitMoveAnimOffsetX )
            arrival_step_dir_x = -1;
          else
            arrival_step_dir_x = 0;
        }
        else
        {
          arrival_step_dir_x = 1;
        }
        g_UnitMoveAnimOffsetX += (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit] * arrival_step_dir_x;
        if ( -g_UnitMoveAnimOffsetY < 0 || g_UnitMoveAnimOffsetY == 0 )
        {
          if ( g_UnitMoveAnimOffsetY )
            arrival_step_dir_y = -1;
          else
            arrival_step_dir_y = 0;
        }
        else
        {
          arrival_step_dir_y = 1;
        }
        v95 = (unsigned __int8)g_UnitTypeBattleMoveStepPx[88 * *attacker_unit] * arrival_step_dir_y + g_UnitMoveAnimOffsetY;
        v96 = g_UnitMoveAnimOffsetX * v92;
        g_UnitMoveAnimOffsetY = v95;
        if ( v96 < 0 )
          g_UnitMoveAnimOffsetX = 0;
        if ( v85 * g_UnitMoveAnimOffsetY < 0 )
          g_UnitMoveAnimOffsetY = 0;
        v88 = Time_Now(v95, v96);
      }
    }
    DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  }
  if ( g_UnitBattleAnimatingUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_UnitBattleAnimatingUnitSpriteSet);
  g_UnitBattleAnimatingUnitSpriteSet = 0;
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_ActionBusy);
  g_ActiveUnitMoveTileIndex = -1;
  return UnitBattle_RedrawVisibleGrid();
}
// 427704: conditional instruction was optimized away because ebp.4<0
// 42771F: conditional instruction was optimized away because %var_10.4<0
// 427620: simplified comparisons for 'edi.4': ==0 || ==1 became <2u
// 427389: variable 'v7' is possibly undefined
// 4273C0: variable 'v10' is possibly undefined
// 427435: variable 'v16' is possibly undefined
// 427437: variable 'v17' is possibly undefined
// 42745E: variable 'v19' is possibly undefined
// 427463: variable 'v21' is possibly undefined
// 427499: variable 'v24' is possibly undefined
// 4274DE: variable 'v31' is possibly undefined
// 4274E3: variable 'v33' is possibly undefined
// 427603: variable 'v42' is possibly undefined
// 427608: variable 'v43' is possibly undefined
// 427649: variable 'v45' is possibly undefined
// 42764E: variable 'v46' is possibly undefined
// 42764E: variable 'v47' is possibly undefined
// 427686: variable 'v49' is possibly undefined
// 427779: variable 'v25' is possibly undefined
// 4277A6: variable 'v60' is possibly undefined
// 4277E8: variable 'v62' is possibly undefined
// 427835: variable 'v66' is possibly undefined
// 42783E: variable 'v68' is possibly undefined
// 427849: variable 'v64' is possibly undefined
// 42786F: variable 'v70' is possibly undefined
// 427BBF: variable 'v74' is possibly undefined
// 427BDB: variable 'v75' is possibly undefined
// 427BE7: variable 'v76' is possibly undefined
// 427C03: variable 'v78' is possibly undefined
// 427C03: variable 'v77' is possibly undefined
// 427C0F: variable 'v80' is possibly undefined
// 427C5E: variable 'v82' is possibly undefined
// 427C86: variable 'v84' is possibly undefined
// 427CBB: variable 'v86' is possibly undefined
// 427CC0: variable 'v88' is possibly undefined
// 427CC4: variable 'v89' is possibly undefined
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 514E44: using guessed type int dword_514E44;
// 519808: using guessed type int dword_519808;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 531CC0: using guessed type int dword_531CC0;
// 531CC4: using guessed type int dword_531CC4;
// 532048: using guessed type int g_MapData;
// 532060: using guessed type int dword_532060;
// 5320EC: using guessed type int dword_5320EC;
// 5320F0: using guessed type int dword_5320F0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00427FA0) --------------------------------------------------------
int  UnitBattle_PlayDeathAnimation(int unit_index, int a2, char a3, DWORD a4)
{
  int unit_index_copy; // edx
  int unit_record_offset; // esi
  __int16 *unit_ptr; // ebp
  int v8; // ecx
  int death_start_tick; // eax
  int direction; // ecx
  int corpse_tile_row; // edx
  int corpse_tile_offset; // eax
  unsigned int frame_deadline; // edx
  unsigned int current_tick; // eax
  int v15; // ecx
  int fade_direction; // ecx
  int fade_unit_row; // ebx
  int fade_unit_col; // esi
  int final_record_offset; // edi
  int result; // eax
  int unit_row; // ebx
  int unit_col; // esi
  int corpse_row_base; // edx
  int fade_record_offset; // [esp+0h] [ebp-24h]
  int corpse_record_offset; // [esp+4h] [ebp-20h]
  int last_tick; // [esp+8h] [ebp-1Ch]

  Debug_Log(a2, a3, a4, (int)(intptr_t)aDeathanimD);
  unit_index_copy = unit_index;
  unit_record_offset = 31 * unit_index_copy;
  unit_ptr = (__int16 *)(uintptr_t)(g_MapData + 852 + 31 * unit_index_copy);
  Audio_PlayUnitDeathSound(*unit_ptr);
  if ( (g_UnitTypeFlags[22 * *unit_ptr] & 1) != 0 )
  {
    *(_BYTE *)(uintptr_t)(40 * (unsigned __int16)unit_ptr[2] + g_MapData + 2 * (unsigned __int16)unit_ptr[3] + 2334) = 48;
    UnitBattle_InitUnitFadeAnimation(unit_index, 255, -4, 255);
    death_start_tick = Time_Now(v8, 0);
    LOWORD(corpse_tile_row) = unit_ptr[2];
    last_tick = death_start_tick;
    corpse_record_offset = unit_record_offset;
    *(_BYTE *)(uintptr_t)(g_MapData + 40 * corpse_tile_row + 2 * (unsigned __int16)unit_ptr[3] + 2335) = -1;
    while ( 1 )
    {
      corpse_tile_offset = 40 * (unsigned __int16)unit_ptr[2] + g_MapData + 2 * (unsigned __int16)unit_ptr[3];
      if ( *(char *)(uintptr_t)(corpse_tile_offset + 2334) >= 56 )
        break;
      frame_deadline = last_tick + 10;
      while ( 1 )
      {
        current_tick = Time_Now(direction, frame_deadline);
        if ( current_tick >= frame_deadline )
          break;
        UnitBattle_UpdateIdleAnimatedUnits();
      }
      last_tick = Time_Now(v15, frame_deadline);
      UnitBattle_RedrawUnitNeighborhood(unit_index);
      UnitBattle_RedrawUnitNeighborhood(unit_index);
      direction = *(unsigned __int8 *)(uintptr_t)(corpse_record_offset + g_MapData + 855);
      unit_row = *(unsigned __int16 *)(uintptr_t)(corpse_record_offset + g_MapData + 856);
      unit_col = *(unsigned __int16 *)(uintptr_t)(corpse_record_offset + g_MapData + 858);
      if ( !*(_BYTE *)(uintptr_t)(corpse_record_offset + g_MapData + 855) || direction == 7 || direction == 1 )
        UnitBattle_RedrawTile(unit_row, unit_col - 1);
      if ( direction == 1 )
        UnitBattle_RedrawTile(unit_row + 1, unit_col - 1);
      if ( direction == 2 || direction == 1 || direction == 3 )
        UnitBattle_RedrawTile(unit_row + 1, unit_col);
      if ( direction == 3 )
        UnitBattle_RedrawTile(unit_row + 1, unit_col + 1);
      if ( direction == 4 || direction == 3 || direction == 5 )
        UnitBattle_RedrawTile(unit_row, unit_col + 1);
      if ( direction == 5 )
        UnitBattle_RedrawTile(unit_row - 1, unit_col + 1);
      if ( direction == 6 || direction == 7 || direction == 5 )
        UnitBattle_RedrawTile(unit_row - 1, unit_col);
      if ( direction == 7 )
        UnitBattle_RedrawTile(unit_row - 1, unit_col - 1);
      corpse_row_base = 40 * (unsigned __int16)unit_ptr[2] + g_MapData;
      ++*(_BYTE *)(uintptr_t)(corpse_row_base + 2 * (unsigned __int16)unit_ptr[3] + 2334);
    }
    *(_BYTE *)(uintptr_t)(corpse_tile_offset + 2334) = -1;
  }
  else
  {
    UnitBattle_InitUnitFadeAnimation(unit_index, 255, -8, 255);
    if ( g_UnitFadeAnimCurrentOffset )
    {
      fade_record_offset = unit_record_offset;
      do
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        UnitBattle_RedrawUnitNeighborhood(unit_index);
        fade_direction = *(unsigned __int8 *)(uintptr_t)(fade_record_offset + g_MapData + 855);
        fade_unit_row = *(unsigned __int16 *)(uintptr_t)(fade_record_offset + g_MapData + 856);
        fade_unit_col = *(unsigned __int16 *)(uintptr_t)(fade_record_offset + g_MapData + 858);
        if ( !*(_BYTE *)(uintptr_t)(fade_record_offset + g_MapData + 855) || fade_direction == 7 || fade_direction == 1 )
          UnitBattle_RedrawTile(fade_unit_row, fade_unit_col - 1);
        if ( fade_direction == 1 )
          UnitBattle_RedrawTile(fade_unit_row + 1, fade_unit_col - 1);
        if ( fade_direction == 2 || fade_direction == 1 || fade_direction == 3 )
          UnitBattle_RedrawTile(fade_unit_row + 1, fade_unit_col);
        if ( fade_direction == 3 )
          UnitBattle_RedrawTile(fade_unit_row + 1, fade_unit_col + 1);
        if ( fade_direction == 4 || fade_direction == 3 || fade_direction == 5 )
          UnitBattle_RedrawTile(fade_unit_row, fade_unit_col + 1);
        if ( fade_direction == 5 )
          UnitBattle_RedrawTile(fade_unit_row - 1, fade_unit_col + 1);
        if ( fade_direction == 6 || fade_direction == 7 || fade_direction == 5 )
          UnitBattle_RedrawTile(fade_unit_row - 1, fade_unit_col);
        if ( fade_direction == 7 )
          UnitBattle_RedrawTile(fade_unit_row - 1, fade_unit_col - 1);
        *(_BYTE *)(uintptr_t)(40 * (unsigned __int16)unit_ptr[2] + g_MapData + 2 * (unsigned __int16)unit_ptr[3] + 2335) = -1 - g_UnitFadeAnimCurrentOffset;
      }
      while ( g_UnitFadeAnimCurrentOffset );
    }
  }
  final_record_offset = 31 * unit_index;
  *(_WORD *)(uintptr_t)(g_MapData + final_record_offset + 852) = -1;
  result = *(unsigned __int16 *)(uintptr_t)(g_MapData + final_record_offset + 858);
  *(_WORD *)(uintptr_t)(40 * *(unsigned __int16 *)(uintptr_t)(g_MapData + final_record_offset + 856) + g_MapData + 2 * result + 1534) = -1;
  return result;
}
// 427FC9: variable 'v5' is possibly undefined
// 42802E: variable 'v8' is possibly undefined
// 42804A: variable 'v11' is possibly undefined
// 428097: variable 'v10' is possibly undefined
// 428097: variable 'v13' is possibly undefined
// 42811D: variable 'v16' is possibly undefined
// 428273: variable 'v15' is possibly undefined
// 51257A: using guessed type int g_UnitTypeFlags[];
// 532048: using guessed type int g_MapData;
// 5320F4: using guessed type int dword_5320F4;

//----- (004283D0) --------------------------------------------------------
int  UnitBattle_GetCorpseSpriteIndex(__int16 *unit_ptr)
{
  return (unsigned __int8)g_UnitTypeCorpseSpriteBaseIndex[88 * *unit_ptr] + (*((unsigned __int8 *)unit_ptr + 3) + 4) % 8;
}

//----- (00428400) --------------------------------------------------------
signed int  UnitBattle_Attack(int attacker_index, int defender_index, int charge_mode)
{
  __int16 *attacker_unit;
  __int16 *defender_unit;
  int attacker_type;
  int delta_x;
  int delta_y;
  int *move_track;
  int track_cost;
  int defender_remaining;
  int attacker_remaining;
  int defender_dead;
  int attacker_dead;
  int corpse_sprite;
  int owner_index;

  Debug_Log(charge_mode, charge_mode, attacker_index, (int)(intptr_t)aUnitbattle_att);
  Diagnostics_TraceWorldMapActionEvent("battle_attack_enter", attacker_index, defender_index, charge_mode, 0);
  if ( !g_MapData || attacker_index < 0 || attacker_index >= 22 || defender_index < 0 || defender_index >= 22 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_attack_invalid_index", attacker_index, defender_index, charge_mode, 0);
    return 0;
  }
  attacker_unit = (__int16 *)(uintptr_t)(g_MapData + 852 + 31 * attacker_index);
  defender_unit = (__int16 *)(uintptr_t)(g_MapData + 852 + 31 * defender_index);
  attacker_type = *attacker_unit;
  if ( attacker_type == -1
    || !g_UnitTypeBaseMeleeAttack[UNIT_TYPE_METADATA_STRIDE * attacker_type]
    || attacker_type == UNIT_TYPE_RAM
    || *defender_unit == -1 )
  {
    Diagnostics_TraceWorldMapActionEvent("battle_attack_invalid_unit", attacker_index, defender_index, attacker_type, *defender_unit);
    return 0;
  }
  if ( charge_mode )
    UnitBattle_EnableSelectedChargeMode();
  UnitBattle_DrawSelectedUnitPanel(0, 1, charge_mode, (int)(intptr_t)defender_unit);
  UnitBattle_RedrawVisibleGrid();
  delta_x = (unsigned __int16)attacker_unit[2] - (unsigned __int16)defender_unit[2];
  if ( delta_x < 0 )
    delta_x = -delta_x;
  delta_y = (unsigned __int16)attacker_unit[3] - (unsigned __int16)defender_unit[3];
  if ( delta_y < 0 )
    delta_y = -delta_y;
  if ( delta_x > 1 || delta_y > 1 )
  {
    move_track = UnitBattle_MoveTrackNear(
                   attacker_index,
                   (unsigned __int16)defender_unit[2],
                   (unsigned __int16)defender_unit[3],
                   attacker_index);
    if ( !move_track )
      goto attack_failed;
    track_cost = move_track[1];
    if ( HIWORD(track_cost) + 5 > (int)*(unsigned __int8 *)((char *)attacker_unit + 8) )
    {
      nfree_((int)(uintptr_t)move_track);
      goto attack_failed;
    }
    *(_DWORD *)((char *)attacker_unit + 23) = move_track;
    UnitBattle_Move(attacker_index, 0, 0, 0);
    if ( *(_DWORD *)((char *)attacker_unit + 23) )
    {
      nfree_(*(_DWORD *)((char *)attacker_unit + 23));
      *(_DWORD *)((char *)attacker_unit + 23) = 0;
      goto attack_failed;
    }
  }
  if ( *(unsigned __int8 *)((char *)attacker_unit + 8) < 5u )
    goto attack_failed;
  *(unsigned char *)((char *)attacker_unit + 8) -= 5;
  *(unsigned char *)((char *)attacker_unit + 22) &= 0xFEu;
  g_SelectedUnitIndex = attacker_index;
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)attacker_unit[2], (unsigned __int16)attacker_unit[3])
    || !UnitBattle_IsTileInViewport((unsigned __int16)defender_unit[2], (unsigned __int16)defender_unit[3]) )
  {
    UnitBattle_CenterViewOnUnit(attacker_index);
    UnitBattle_RedrawVisibleGrid();
  }
  UnitBattle_CalcMeleeExchange(attacker_index, defender_index, &defender_remaining, &attacker_remaining, charge_mode);
  *(unsigned char *)((char *)attacker_unit + 9) = (unsigned char)attacker_remaining;
  *(unsigned char *)((char *)defender_unit + 9) = (unsigned char)defender_remaining;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_attack_after_exchange",
    attacker_index,
    defender_index,
    attacker_remaining,
    defender_remaining);
  *(unsigned char *)((char *)attacker_unit + 3) = Facing_DirectionFromDelta8(
                                                     (unsigned __int16)defender_unit[2]
                                                   - (unsigned __int16)attacker_unit[2],
                                                     (unsigned __int16)defender_unit[3]
                                                   - (unsigned __int16)attacker_unit[3]);
  if ( !*(unsigned char *)((char *)defender_unit + 9) )
  {
    corpse_sprite = UnitBattle_GetCorpseSpriteIndex(defender_unit);
    *(_BYTE *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)defender_unit[2] + 2 * (unsigned __int16)defender_unit[3] + 2334) = corpse_sprite;
    *(_BYTE *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)defender_unit[2] + 2 * (unsigned __int16)defender_unit[3] + 2335) = 0;
  }
  if ( !*(unsigned char *)((char *)attacker_unit + 9) )
  {
    corpse_sprite = UnitBattle_GetCorpseSpriteIndex(attacker_unit);
    *(_BYTE *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)attacker_unit[2] + 2 * (unsigned __int16)attacker_unit[3] + 2334) = corpse_sprite;
    *(_BYTE *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)attacker_unit[2] + 2 * (unsigned __int16)attacker_unit[3] + 2335) = 0;
  }
  defender_dead = *(unsigned char *)((char *)defender_unit + 9) == 0;
  attacker_dead = *(unsigned char *)((char *)attacker_unit + 9) == 0;
  UnitBattle_PlayAttackAnimation(attacker_index, defender_index, defender_dead, attacker_dead, (unsigned __int16 *)(uintptr_t)attacker_index);
  if ( defender_dead )
  {
    *defender_unit = -1;
    *(_WORD *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)defender_unit[2] + 2 * (unsigned __int16)defender_unit[3] + 1534) = -1;
  }
  owner_index = *(unsigned __int8 *)((char *)attacker_unit + 2);
  if ( attacker_dead )
  {
    UnitBattle_RefreshSelectedUnitUI();
    *attacker_unit = -1;
    *(_WORD *)(uintptr_t)(g_MapData + 40 * (unsigned __int16)attacker_unit[2] + 2 * (unsigned __int16)attacker_unit[3] + 1534) = -1;
    if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * owner_index + 140051) )
      UnitBattle_SelectNextControllableUnit(0, 0, (char)(intptr_t)defender_unit);
  }
  *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * owner_index + 140073) = 1;
  UnitBattle_RedrawVisibleGrid();
  UnitBattle_DrawSelectedUnitPanel(0, 1, attacker_dead, (int)(intptr_t)defender_unit);
  UnitBattle_RefreshSelectedUnitUI();
  Diagnostics_TraceWorldMapActionEvent("battle_attack_return", attacker_index, defender_index, attacker_dead, defender_dead);
  return 1;

attack_failed:
  UnitBattle_RefreshSelectedUnitUI();
  Diagnostics_TraceWorldMapActionEvent("battle_attack_failed", attacker_index, defender_index, charge_mode, 0);
  return 0;
}
// 428432: variable 'v5' is possibly undefined
// 42846E: variable 'v4' is possibly undefined
// 42852A: variable 'v13' is possibly undefined
// 42858A: variable 'v15' is possibly undefined
// 4285F0: variable 'v17' is possibly undefined
// 4286B9: variable 'v21' is possibly undefined
// 4286EF: variable 'v20' is possibly undefined
// 428763: variable 'v9' is possibly undefined
// 42878E: variable 'v24' is possibly undefined
// 42879E: variable 'v26' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;

//----- (004287E0) --------------------------------------------------------
BOOL  UnitBattle_IsTileWithinRange(int unit_index, int target_row, int target_col)
{
  int unit_record;
  int unit_type_offset;
  signed int distance; // eax

  if ( !g_MapData || unit_index < 0 || unit_index >= 22 )
    return 0;
  unit_record = g_MapData + 31 * unit_index + 852;
  if ( *(__int16 *)(uintptr_t)unit_record == -1 )
    return 0;
  distance = Math_CeilSqrt(
         (*(unsigned __int16 *)(uintptr_t)(31 * unit_index + g_MapData + 852 + 4) - target_row)
       * (*(unsigned __int16 *)(uintptr_t)(31 * unit_index + g_MapData + 852 + 4) - target_row)
       + (*(unsigned __int16 *)(uintptr_t)(31 * unit_index + g_MapData + 852 + 6) - target_col)
       * (*(unsigned __int16 *)(uintptr_t)(31 * unit_index + g_MapData + 852 + 6) - target_col));
  unit_type_offset = 88 * *(__int16 *)(uintptr_t)unit_record;
  return distance <= (unsigned __int8)g_UnitTypeMaxRange[unit_type_offset]
      && distance > (unsigned __int8)g_UnitTypeMinRange[unit_type_offset];
}
// 532048: using guessed type int g_MapData;

//----- (00428850) --------------------------------------------------------
BOOL  UnitBattle_IsUnitWithinRange(int unit_index, int target_unit_index)
{
  return UnitBattle_IsTileWithinRange(
           unit_index,
           *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * target_unit_index + 856),
           *(unsigned __int16 *)(uintptr_t)(g_MapData + 31 * target_unit_index + 858));
}
// 532048: using guessed type int g_MapData;
