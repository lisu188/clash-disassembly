/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (00428880) --------------------------------------------------------
__int16  UnitBattle_PlayShotAnimation(
        int shooter_index,
        int target_unit_index,
        int target_col,
        int a4,
        int a5,
        int a6,
        __int128 a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        __int64 a16)
{
  char shooter_owner; // bl
  int v17; // ecx
  _DWORD *shooterSpriteSet; // eax
  char target_owner; // bl
  int v20; // ecx
  _DWORD *targetSpriteSet; // eax
  int v22; // ecx
  int v23; // ecx
  _DWORD *projPaletteSpriteSet; // eax
  char v25; // bl
  int v26; // edx
  int v27; // ecx
  int v28; // ecx
  unsigned __int16 shooterUnitType; // ax
  char *v30; // esi
  int v31; // ecx
  int shooter_record_offset; // edi
  int v33; // ecx
  int now; // eax
  int v35; // ecx
  unsigned int v36; // edx
  int soundUnitType; // eax
  int soundFrameIndex; // edx
  int projHalfHeight; // ebx
  unsigned __int16 v40; // cx
  unsigned __int16 SpriteWidth; // ax
  int spriteVerticalOffset; // edx
  int proj_px_y; // esi
  int v44; // ebx
  int v45; // ecx
  int v46; // ecx
  int v47; // edx
  int frameCount; // ecx
  unsigned int frameIndex; // edx
  int frameNow; // eax
  int v51; // eax
  int v52; // ecx
  int v53; // edx
  unsigned int arcPhase; // eax
  unsigned int arcOffset; // edx
  int v56; // edi
  unsigned __int16 v57; // dx
  __int16 SpriteHeight; // dx
  __int16 v59; // ax
  int v60; // eax
  __int16 v61; // ax
  int v62; // ecx
  int v63; // edx
  int v64; // ecx
  int v65; // eax
  int v66; // eax
  int v67; // edx
  int v68; // ecx
  int v69; // eax
  int v70; // edx
  int v71; // eax
  int v72; // eax
  BOOL isProjectileUnit; // eax
  int v74; // ecx
  int v75; // eax
  _DWORD *battleProjectileSpriteSet; // eax
  int v77; // eax
  _DWORD *v78; // eax
  char targetFacing; // bl
  char newTargetFacing; // al
  unsigned __int8 facingHighBits; // bl
  int v82; // edx
  int v83; // ecx
  int hitAnimTime; // ebx
  int v85; // edx
  int v86; // ecx
  int v87; // ecx
  int projAnimStartTime; // esi
  int v89; // ecx
  unsigned int hitNow; // eax
  unsigned int v91; // edx
  int v92; // ecx
  int hitAnimFrame; // edx
  int v94; // ecx
  int v95; // ecx
  int mapRowCount; // edi
  int mapColCount; // ecx
  char *v98; // esi
  char *v99; // esi
  char *v100; // esi
  int v101; // eax
  int v102; // edx
  int v103; // eax
  int SpriteForChar; // eax
  int v105; // ecx
  __int16 result; // ax
  unsigned __int16 v107; // [esp-Ch] [ebp-2BCh]
  unsigned __int16 v108; // [esp-4h] [ebp-2B4h]
  char v109[384]; // [esp+82h] [ebp-22Eh] BYREF
  char v110[44]; // [esp+202h] [ebp-AEh] BYREF
  _BYTE v111[56]; // [esp+22Eh] [ebp-82h] BYREF
  char v112[74]; // [esp+266h] [ebp-4Ah] BYREF
  unsigned __int8 *target_unit; // [esp+2D6h] [ebp+26h]
  int target_px_y; // [esp+2E2h] [ebp+32h]
  int travelDeltaX; // [esp+2E6h] [ebp+36h]
  int travelDeltaY; // [esp+2EAh] [ebp+3Ah]
  int source_px_x; // [esp+2EEh] [ebp+3Eh]
  int source_px_y; // [esp+2F2h] [ebp+42h]
  int target_row; // [esp+302h] [ebp+52h]
  int target_px_x; // [esp+306h] [ebp+56h]
  int last_tick; // [esp+30Ah] [ebp+5Ah]
  __int16 *shooter_unit; // [esp+30Eh] [ebp+5Eh]
  unsigned int projectile_frame; // [esp+312h] [ebp+62h]
  int travel_steps; // [esp+316h] [ebp+66h]
  int unitRecordOffset; // [esp+31Ah] [ebp+6Ah]
  int prevProjX; // [esp+31Eh] [ebp+6Eh]
  int shot_start_time; // [esp+322h] [ebp+72h]
  int projectile_sprite_set; // [esp+326h] [ebp+76h]
  int sprite_frame_base; // [esp+32Ah] [ebp+7Ah]
  int proj_px_x; // [esp+32Eh] [ebp+7Eh]

  target_row = a4;
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Busy);
  shooter_unit = (__int16 *)(g_MapData + 852 + 31 * shooter_index);
  if ( target_unit_index == -1 )
  {
    LOBYTE(a4) = 0;
    target_unit = 0;
  }
  else
  {
    target_unit = (unsigned __int8 *)(31 * target_unit_index + g_MapData + 852);
  }
  Debug_Log(target_unit_index, a4, (DWORD)v111, (int)a_shotanimDDDDD);
  if ( !UnitBattle_IsTileInViewport((unsigned __int16)shooter_unit[2], (unsigned __int16)shooter_unit[3]) || !UnitBattle_IsTileInViewport(target_row, target_col) )
  {
    *(_DWORD *)(g_MapData + 808) = (target_row + (unsigned __int16)shooter_unit[2]) / 2 - 3;
    *(_DWORD *)(g_MapData + 812) = (target_col + (unsigned __int16)shooter_unit[3]) / 2 - 3;
    if ( *(int *)(g_MapData + 808) < 0 )
      *(_DWORD *)(g_MapData + 808) = 0;
    mapRowCount = *(_DWORD *)(g_MapData + 804);
    if ( *(_DWORD *)(g_MapData + 808) + 7 > mapRowCount )
      *(_DWORD *)(g_MapData + 808) = mapRowCount - 7;
    if ( *(int *)(g_MapData + 812) < 0 )
      *(_DWORD *)(g_MapData + 812) = 0;
    mapColCount = *(_DWORD *)(g_MapData + 800);
    if ( *(_DWORD *)(g_MapData + 812) + 7 > mapColCount )
      *(_DWORD *)(g_MapData + 812) = mapColCount - 7;
    UnitBattle_RedrawVisibleGrid();
  }
  *((_BYTE *)shooter_unit + 3) = Facing_DirectionFromDelta8(target_row - (unsigned __int16)shooter_unit[2], target_col - (unsigned __int16)shooter_unit[3]);
  shooter_owner = *((_BYTE *)shooter_unit + 2);
  Unit_BuildShotAnimSpritePath(v110, *(_BYTE *)shooter_unit, shooter_owner);
  shooterSpriteSet = (_DWORD *)Mem_Alloc(4112, v17, shooter_owner, (DWORD)v111);
  if ( shooterSpriteSet )
    shooterSpriteSet = DLXSpriteSet_Load(shooterSpriteSet, shooter_owner);
  g_ActiveUnitAnimSpriteSet = (int)shooterSpriteSet;
  target_owner = 0;
  g_UnitMoveAnimOffsetX = 0;
  g_ActiveUnitMoveTileIndex = shooter_index;
  g_UnitMoveAnimOffsetY = 0;
  g_UnitAnimFrameIndex = 0;
  g_UnitBattleAnimFrameCount = (unsigned __int8)g_UnitTypeShotAnimationFrameCount[88 * *shooter_unit];
  if ( target_unit_index != -1 )
  {
    target_owner = target_unit[2];
    Unit_BuildGoSpriteFilePath(v110, *target_unit, target_owner);
    targetSpriteSet = (_DWORD *)Mem_Alloc(4112, v20, target_owner, (DWORD)v111);
    if ( targetSpriteSet )
      targetSpriteSet = DLXSpriteSet_Load(targetSpriteSet, target_owner);
    g_UnitBattleAnimatingUnitSpriteSet = (int)targetSpriteSet;
  }
  qmemcpy(v109, &g_UnitBattleShotAnimTemplate, sizeof(v109));
  Unit_BuildShotAnimPaletteSpritePath(v112, *(_BYTE *)shooter_unit);
  projectile_sprite_set = 0;
  if ( DLX_OpenArchive(v112, v22) )
  {
    projPaletteSpriteSet = (_DWORD *)Mem_Alloc(4112, v23, target_owner, (DWORD)v111);
    if ( projPaletteSpriteSet )
      projPaletteSpriteSet = DLXSpriteSet_Load(projPaletteSpriteSet, target_owner);
    projectile_sprite_set = (int)projPaletteSpriteSet;
  }
  v25 = projectile_sprite_set;
  Debug_Log(-1, projectile_sprite_set, (DWORD)v111, (int)aLoaded);
  sprite_frame_base = v27;
  v28 = g_UnitBattleAnimFrameCount - 1;
  if ( projectile_sprite_set )
  {
    *(_DWORD *)((char *)&a7 + 2) = 32 - (unsigned __int16)DLX_GetSpriteHeight(projectile_sprite_set, 0) / 2;
    v26 = 32 - (unsigned __int16)DLX_GetSpriteWidth(projectile_sprite_set, 0) / 2;
    *(_DWORD *)((char *)&a7 + 6) = v26;
  }
  shooterUnitType = *shooter_unit;
  if ( (unsigned __int16)*shooter_unit >= 0xFu )
  {
    if ( (unsigned __int16)*shooter_unit <= 0xFu )
    {
      v28 = 26;
      v26 = *((unsigned __int8 *)shooter_unit + 3);
      *(_DWORD *)((char *)&a16 + 2) = 5;
      v99 = &v109[8 * v26 + 256];
      sprite_frame_base = 5 * v26;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v99;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v99 + 1);
      *(_DWORD *)((char *)&a7 + 10) = 6;
    }
    else if ( shooterUnitType >= 0x1Cu )
    {
      if ( shooterUnitType <= 0x1Cu )
      {
        v28 = 3;
        sprite_frame_base = 8 * *((unsigned __int8 *)shooter_unit + 3);
        v26 = 6;
        *(_DWORD *)((char *)&a7 + 10) = 6;
        *(_DWORD *)((char *)&a16 + 2) = 8;
        *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)&v109[sprite_frame_base + 192];
        *(_DWORD *)((char *)&a7 + 6) = *(_DWORD *)&v109[sprite_frame_base + 196];
      }
      else if ( shooterUnitType == 30 )
      {
        v26 = (int)shooter_unit;
        *(_DWORD *)((char *)&a16 + 2) = 8;
        v28 = 8;
        *(_DWORD *)((char *)&a7 + 10) = 6;
        sprite_frame_base = 8 * *((unsigned __int8 *)shooter_unit + 3);
        *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)&v109[sprite_frame_base];
        *(_DWORD *)((char *)&a7 + 6) = *(_DWORD *)&v109[sprite_frame_base + 4];
      }
    }
    else if ( shooterUnitType == 20 )
    {
      v25 = 1;
      *(_DWORD *)((char *)&a7 + 10) = 8;
      sprite_frame_base = 0;
      v100 = &v109[8 * *((unsigned __int8 *)shooter_unit + 3) + 320];
      *(_DWORD *)((char *)&a16 + 2) = 1;
      v28 = 6;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v100;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v100 + 1);
    }
  }
  else if ( shooterUnitType >= 0xAu )
  {
    if ( shooterUnitType <= 0xAu )
    {
      *(_DWORD *)((char *)&a16 + 2) = 5;
      *(_DWORD *)((char *)&a7 + 10) = 8;
      v26 = *((unsigned __int8 *)shooter_unit + 3);
      v98 = &v109[8 * v26 + 128];
      v28 = 4;
      *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v98;
      *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v98 + 1);
      sprite_frame_base = 5 * v26;
    }
    else if ( shooterUnitType == 12 )
    {
      v26 = 0;
      v25 = 2;
      sprite_frame_base = 0;
      *(_DWORD *)((char *)&a16 + 2) = 5;
      *(_DWORD *)((char *)&a7 + 10) = 2;
      v28 = 1;
    }
  }
  else if ( shooterUnitType == 9 )
  {
    v28 = 6;
    v26 = *((unsigned __int8 *)shooter_unit + 3);
    *(_DWORD *)((char *)&a7 + 10) = 6;
    v30 = &v109[8 * v26 + 64];
    sprite_frame_base = 5 * v26;
    *(_DWORD *)((char *)&a7 + 2) = *(_DWORD *)v30;
    *(_DWORD *)((char *)&a7 + 6) = *((_DWORD *)v30 + 1);
    *(_DWORD *)((char *)&a16 + 2) = 5;
  }
  last_tick = Time_Now(v28, v26);
  if ( v31 >= g_UnitAnimFrameIndex )
  {
    shooter_record_offset = 31 * shooter_index;
    do
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, v25);
      v25 = last_tick;
      now = Time_Now(v33, (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * *(__int16 *)(shooter_record_offset + g_MapData + 852)]);
      if ( now - last_tick >= v36 )
      {
        soundUnitType = *(__int16 *)(shooter_record_offset + g_MapData + 852);
        soundFrameIndex = (unsigned __int8)g_UnitTypeShotSoundFrameIndex[88 * soundUnitType];
        if ( soundFrameIndex == g_UnitAnimFrameIndex )
          Audio_PlayUnitRangedAttackSound(soundUnitType);
        last_tick = Time_Now(v35, soundFrameIndex);
        UnitBattle_RedrawTile(*(unsigned __int16 *)(shooter_record_offset + g_MapData + 856), *(unsigned __int16 *)(shooter_record_offset + g_MapData + 858));
        ++g_UnitAnimFrameIndex;
      }
    }
    while ( v35 >= g_UnitAnimFrameIndex );
  }
  if ( sprite_frame_base != -1 )
  {
    projHalfHeight = (unsigned __int16)DLX_GetSpriteHeight(projectile_sprite_set, sprite_frame_base) / 2;
    SpriteWidth = DLX_GetSpriteWidth(projectile_sprite_set, v40);
    spriteVerticalOffset = (unsigned __int8)g_UnitTypeSpriteVerticalOffsetPx[88 * *shooter_unit];
    source_px_x = (((unsigned __int16)shooter_unit[2] - *(_DWORD *)(g_MapData + 808)) << 6)
         + 32
         + *(_DWORD *)((char *)&a7 + 2)
         - spriteVerticalOffset;
    proj_px_y = *(_DWORD *)((char *)&a7 + 6) + (((unsigned __int16)shooter_unit[3] - *(_DWORD *)(g_MapData + 812)) << 6) + 16 - spriteVerticalOffset;
    source_px_y = proj_px_y;
    target_px_x = ((target_row - *(_DWORD *)(g_MapData + 808)) << 6) + 64 - projHalfHeight;
    target_px_y = ((target_col - *(_DWORD *)(g_MapData + 812)) << 6) + 48 - SpriteWidth / 2;
    proj_px_x = source_px_x;
    v44 = target_px_y - proj_px_y;
    travel_steps = Math_CeilSqrt(v44 * v44 + (target_px_x - source_px_x) * (target_px_x - source_px_x)) / *(_DWORD *)((char *)&a7 + 10);
    shot_start_time = Time_Now(v45, shooter_index);
    travelDeltaX = v46;
    travelDeltaY = target_px_y - proj_px_y;
    unitRecordOffset = 31 * v47;
    while ( 1 )
    {
      UnitBattle_UpdateIdleAnimatedUnits();
      DD_Pump((int)g_RenderState, v44);
      frameCount = g_UnitBattleAnimFrameCount;
      frameIndex = g_UnitAnimFrameIndex % g_UnitBattleAnimFrameCount;
      g_UnitAnimFrameIndex = frameIndex;
      if ( frameIndex )
      {
        frameNow = Time_Now(unitRecordOffset, (unsigned __int8)g_UnitTypeAnimationFrameIntervalMs[88 * *(__int16 *)(unitRecordOffset + g_MapData + 852)]);
        if ( frameNow - last_tick >= frameIndex )
        {
          v51 = *(__int16 *)(frameCount + g_MapData + 852);
          v52 = g_UnitAnimFrameIndex;
          v53 = (unsigned __int8)g_UnitTypeShotSoundFrameIndex[88 * v51];
          if ( v53 == g_UnitAnimFrameIndex )
            Audio_PlayUnitRangedAttackSound(v51);
          last_tick = Time_Now(v52, v53);
          UnitBattle_RedrawTile(*(unsigned __int16 *)(unitRecordOffset + g_MapData + 856), *(unsigned __int16 *)(unitRecordOffset + g_MapData + 858));
          frameCount = g_UnitBattleAnimFrameCount;
          frameIndex = (g_UnitAnimFrameIndex + 1) % g_UnitBattleAnimFrameCount;
          g_UnitAnimFrameIndex = frameIndex;
        }
      }
      g_RenderDevice = &g_MainRenderDevice;
      if ( *shooter_unit == UNIT_TYPE_CATAPULT )
      {
        arcPhase = 8 * (Time_Now(frameCount, frameIndex) - shot_start_time) / (unsigned int)travel_steps;
        arcOffset = arcPhase - 4;
        if ( (int)(arcPhase - 4) <= 0 )
          arcOffset = 4 - arcPhase;
        projectile_frame = 4 - arcOffset;
      }
      else
      {
        projectile_frame = (Time_Now(frameCount, frameIndex) - shot_start_time) / 0xAu % *(_DWORD *)((char *)&a16 + 2);
      }
      prevProjX = proj_px_x;
      Render_SaveBackbuffer((int)&g_MainRenderDevice);
      v56 = proj_px_y;
      v108 = proj_px_y + DLX_GetSpriteWidth(projectile_sprite_set, v57);
      SpriteHeight = DLX_GetSpriteHeight(projectile_sprite_set, sprite_frame_base);
      v59 = proj_px_x;
      if ( proj_px_y >= proj_px_x )
        v59 = proj_px_y;
      RenderState_PumpIfRectInViewBounds(g_RenderState, proj_px_x, v59 + SpriteHeight, proj_px_y, v108);
      v60 = proj_px_y + (unsigned __int16)DLX_GetSpriteWidth(projectile_sprite_set, sprite_frame_base) + 1;
      if ( v60 > 464 )
        LOWORD(v60) = 464;
      if ( proj_px_y < 16 )
        LOWORD(proj_px_y) = 16;
      v107 = v60;
      v61 = DLX_GetSpriteHeight(projectile_sprite_set, sprite_frame_base);
      Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, v62, (unsigned __int16)proj_px_x, proj_px_x + v61 + 1, v107, proj_px_x, proj_px_y);
      v65 = Time_Now(v64, v63);
      v66 = Time_Now(shot_start_time, (v65 - shot_start_time) * travelDeltaX / travel_steps + source_px_x);
      proj_px_x = v67;
      v25 = v67;
      proj_px_y = (v66 - v68) * travelDeltaY / travel_steps + source_px_y;
      v69 = target_px_x - v67;
      if ( target_px_x - v67 <= 0 )
      {
        if ( target_px_x != v67 )
          v69 = -1;
      }
      else
      {
        v69 = 1;
      }
      v70 = v69;
      v71 = target_px_x - prevProjX;
      if ( target_px_x - prevProjX <= 0 )
      {
        if ( target_px_x != prevProjX )
          v71 = -1;
      }
      else
      {
        v71 = 1;
      }
      if ( v70 != v71 )
        break;
      v101 = target_px_y - proj_px_y;
      if ( target_px_y - proj_px_y <= 0 )
      {
        if ( target_px_y != proj_px_y )
          v101 = -1;
      }
      else
      {
        v101 = 1;
      }
      v102 = v101;
      v103 = target_px_y - v56;
      if ( target_px_y - v56 <= 0 )
      {
        if ( target_px_y != v56 )
          v103 = -1;
      }
      else
      {
        v103 = 1;
      }
      if ( v102 != v103 )
        break;
      SpriteForChar = DLX_GetSpriteForChar(projectile_sprite_set, projectile_frame + sprite_frame_base);
      LOBYTE(v44) = proj_px_x;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        proj_px_y,
        SpriteForChar,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      Render_Present((int)g_RenderState);
    }
  }
  g_UnitAnimFrameIndex %= g_UnitBattleAnimFrameCount;
  UnitBattle_RedrawTile(*(unsigned __int16 *)(g_MapData + 31 * shooter_index + 856), *(unsigned __int16 *)(g_MapData + 31 * shooter_index + 858));
  v72 = *shooter_unit;
  isProjectileUnit = v72 == UNIT_TYPE_CATAPULT
     || v72 == UNIT_TYPE_CANNON
     || v72 == UNIT_TYPE_DRAGON
     || v72 == UNIT_TYPE_WINGER
     || v72 == UNIT_TYPE_WIZARD;
  v74 = isProjectileUnit;
  if ( isProjectileUnit )
  {
    v75 = *shooter_unit;
    if ( v75 == UNIT_TYPE_CATAPULT || v75 == UNIT_TYPE_CANNON )
    {
      battleProjectileSpriteSet = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
      if ( battleProjectileSpriteSet )
LABEL_55:
        battleProjectileSpriteSet = DLXSpriteSet_Load(battleProjectileSpriteSet, v25);
    }
    else
    {
      if ( v75 != 24 )
      {
LABEL_57:
        v77 = *shooter_unit;
        if ( v77 == UNIT_TYPE_DRAGON || v77 == UNIT_TYPE_WINGER )
        {
          v78 = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
          if ( v78 )
            v78 = DLXSpriteSet_Load(v78, v25);
          g_UnitBattleProjectileSpriteSet = (int)v78;
        }
        g_UnitBattleShotProjectileTileX = target_row;
        g_UnitBattleShotProjectileTileY = target_col;
        g_BattleShotAnimFrameIndex = 0;
        Audio_PlayUnitShotSound(*(__int16 *)(g_MapData + 31 * shooter_index + 852));
        goto LABEL_62;
      }
      battleProjectileSpriteSet = (_DWORD *)Mem_Alloc(4112, v74, v25, (DWORD)v111);
      if ( battleProjectileSpriteSet )
        goto LABEL_55;
    }
    g_UnitBattleProjectileSpriteSet = (int)battleProjectileSpriteSet;
    goto LABEL_57;
  }
LABEL_62:
  if ( target_unit )
  {
    if ( (g_UnitTypeFlags[22 * *(__int16 *)target_unit] & 1) != 0 )
    {
      targetFacing = target_unit[17] & 7;
      newTargetFacing = (targetFacing + Rng_RandRange(2, 5)) & 7;
      facingHighBits = target_unit[17] & 0xF8;
      target_unit[17] = facingHighBits;
      target_unit[17] = newTargetFacing & 7 | facingHighBits;
    }
    else
    {
      g_UnitBattleAnimatingUnitIndex = target_unit_index;
    }
  }
  g_UnitBattleHitAnimFrame = Rng_RandRange(3, 7);
  if ( target_unit )
    Audio_PlayUnitHitSound(*(__int16 *)target_unit);
  hitAnimTime = Time_Now(v83, v82);
  projAnimStartTime = Time_Now(v86, v85);
  while ( v87 && (unsigned __int16)DLXSpriteSet_GetLastCharIndex(g_UnitBattleProjectileSpriteSet) >= g_BattleShotAnimFrameIndex || target_unit && g_UnitBattleHitAnimFrame )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    hitNow = Time_Now(v89, hitAnimTime + 5);
    if ( hitNow >= v91 && target_unit )
    {
      hitAnimFrame = g_UnitBattleHitAnimFrame;
      if ( g_UnitBattleHitAnimFrame )
        g_UnitBattleHitAnimFrame = ((_BYTE)g_UnitBattleHitAnimFrame + 1) & 7;
      UnitBattle_RedrawUnitNeighborhood(target_unit_index);
      hitAnimTime = Time_Now(v94, hitAnimFrame);
    }
    g_BattleShotAnimFrameIndex = (unsigned int)(Time_Now(v92, v91) - projAnimStartTime) >> 1;
    if ( v95 )
    {
      if ( (unsigned __int16)DLXSpriteSet_GetLastCharIndex(g_UnitBattleProjectileSpriteSet) <= g_BattleShotAnimFrameIndex )
        break;
    }
    UnitBattle_RedrawTile(target_row, target_col);
  }
  g_UnitBattleShotProjectileTileY = -1;
  g_UnitBattleShotProjectileTileX = -1;
  UnitBattle_RedrawTile(target_row, target_col);
  if ( g_UnitBattleProjectileSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_UnitBattleProjectileSpriteSet);
  g_UnitBattleAnimatingUnitIndex = -1;
  if ( g_UnitBattleAnimatingUnitSpriteSet )
    DLXSpriteSet_ReleaseAndClear(&g_UnitBattleAnimatingUnitSpriteSet);
  g_UnitBattleAnimatingUnitSpriteSet = 0;
  DLXSpriteSet_ReleaseAndClear(&g_ActiveUnitAnimSpriteSet);
  if ( v105 )
    nfree_(v105);
  result = RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_ActionBusy);
  g_ActiveUnitMoveTileIndex = -1;
  g_UnitBattleAnimFrameCount = 8;
  return result;
}
// 42897D: variable 'v17' is possibly undefined
// 4289EB: variable 'v20' is possibly undefined
// 428A2A: variable 'v22' is possibly undefined
// 428A3B: variable 'v23' is possibly undefined
// 428A61: variable 'v27' is possibly undefined
// 428B04: variable 'v28' is possibly undefined
// 428B04: variable 'v26' is possibly undefined
// 428B14: variable 'v31' is possibly undefined
// 428B50: variable 'v33' is possibly undefined
// 428B59: variable 'v36' is possibly undefined
// 428B86: variable 'v35' is possibly undefined
// 428B86: variable 'v38' is possibly undefined
// 428BF0: variable 'v40' is possibly undefined
// 428CBF: variable 'v45' is possibly undefined
// 428CCC: variable 'v46' is possibly undefined
// 428CD4: variable 'v47' is possibly undefined
// 428D30: variable 'v49' is possibly undefined
// 428D3B: variable 'v48' is possibly undefined
// 428D62: variable 'v52' is possibly undefined
// 428D62: variable 'v53' is possibly undefined
// 428E11: variable 'v57' is possibly undefined
// 428ECD: variable 'v62' is possibly undefined
// 428ED2: variable 'v64' is possibly undefined
// 428ED2: variable 'v63' is possibly undefined
// 428EF6: variable 'v67' is possibly undefined
// 428EF9: variable 'v68' is possibly undefined
// 428FE3: variable 'v74' is possibly undefined
// 429098: variable 'v83' is possibly undefined
// 429098: variable 'v82' is possibly undefined
// 42909F: variable 'v86' is possibly undefined
// 42909F: variable 'v85' is possibly undefined
// 4290AA: variable 'v87' is possibly undefined
// 4290D5: variable 'v89' is possibly undefined
// 4290DC: variable 'v91' is possibly undefined
// 429108: variable 'v94' is possibly undefined
// 42910F: variable 'v92' is possibly undefined
// 42911F: variable 'v95' is possibly undefined
// 429561: variable 'v105' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512360: using guessed type int dword_512360;
// 512364: using guessed type int dword_512364;
// 51257A: using guessed type int g_UnitTypeFlags[];
// 514E44: using guessed type int dword_514E44;
// 514E54: using guessed type int dword_514E54;
// 514E58: using guessed type int dword_514E58;
// 519808: using guessed type int dword_519808;
// 5202E0: using guessed type int dword_5202E0;
// 523F70: using guessed type int dword_523F70;
// 523F74: using guessed type int dword_523F74;
// 523F78: using guessed type int dword_523F78;
// 523F7C: using guessed type int dword_523F7C;
// 532048: using guessed type int g_MapData;
// 5320EC: using guessed type int dword_5320EC;
// 5320F0: using guessed type int dword_5320F0;
// 5320FC: using guessed type int dword_5320FC;
// 532100: using guessed type int dword_532100;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004295D0) --------------------------------------------------------
int  UnitBattle_CalcShotTargetHealthAfterHit(int shooter_index, int target_index)
{
  int shooter_record; // ebx
  __int16 *target_unit; // esi
  signed int crowd_scale; // eax
  int base_damage; // ecx
  int v7; // edx
  int defense_scaled; // eax
  int damage_tier; // eax
  int damage; // ecx
  int result; // eax

  shooter_record = g_MapData + 852 + 31 * shooter_index;
  target_unit = (__int16 *)(31 * target_index + g_MapData + 852);
  Unit_CalcEffectivenessC((__int16 *)shooter_record);
  Math_CeilSqrt(
    (*(unsigned __int16 *)(shooter_record + 4) - (unsigned __int16)target_unit[2])
  * (*(unsigned __int16 *)(shooter_record + 4) - (unsigned __int16)target_unit[2])
  + (*(unsigned __int16 *)(shooter_record + 6) - (unsigned __int16)target_unit[3])
  * (*(unsigned __int16 *)(shooter_record + 6) - (unsigned __int16)target_unit[3]));
  crowd_scale = UnitBattle_GetTargetCrowdingScale((int)target_unit);
  defense_scaled = v7 / crowd_scale * (unsigned __int8)g_UnitTypeBaseDefensePower[UNIT_TYPE_METADATA_STRIDE * *target_unit];
  damage_tier = (defense_scaled - (__CFSHL__(defense_scaled >> 31, 8) + (defense_scaled >> 31 << 8))) >> 8;
  if ( damage_tier < 1 )
    goto LABEL_2;
  if ( damage_tier >= 2 )
  {
    base_damage *= 3;
LABEL_2:
    damage = 2 * base_damage;
    goto LABEL_3;
  }
  damage = 4 * base_damage;
LABEL_3:
  result = *(char *)(g_MapData + 31 * target_index + 861) - damage;
  if ( result < 0 )
    return 0;
  return result;
}
// 4296BD: variable 'v7' is possibly undefined
// 4296E6: variable 'v6' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (00429740) --------------------------------------------------------
int  UnitBattle_Shot(int shooter_index, int target_index)
{
  char *shooter_unit; // edi
  char *target_unit; // esi
  int volleys_used; // eax
  int v6; // ecx
  unsigned __int16 target_row; // dx
  unsigned __int16 target_col; // ax

  Debug_Log(shooter_index, target_index, 0, (int)aUnitbattle_sho, shooter_index, target_index);
  shooter_unit = (char *)(g_MapData + 852 + 31 * shooter_index);
  target_unit = (char *)(g_MapData + 852 + 31 * target_index);
  if ( !UnitBattle_IsUnitWithinRange(shooter_index, target_index) )
    return 0;
  volleys_used = UNIT_SLOT_VOLLEYS_USED(shooter_unit);
  if ( volleys_used >= UNIT_SLOT_STATUS_LEVEL(shooter_unit) + 1 )
    return 0;
  if ( (unsigned __int8)shooter_unit[8] < 5u )
    return 0;
  shooter_unit[8] -= 5;
  UNIT_SLOT_SET_VOLLEYS_USED(shooter_unit, volleys_used + 1);
  g_SelectedUnitIndex = shooter_index;
  UnitBattle_DrawSelectedUnitPanel(0, 1, target_index, 0);
  UnitBattle_RedrawVisibleGrid();
  target_unit[9] = UnitBattle_CalcShotTargetHealthAfterHit(shooter_index, target_index);
  UnitBattle_PlayShotAnimation(
    shooter_index,
    target_index,
    *(unsigned __int16 *)(target_unit + 6),
    *(unsigned __int16 *)(target_unit + 4),
    (signed __int8)target_unit[9] <= 0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0);
  if ( (signed __int8)target_unit[9] <= 0 )
  {
    target_row = *(unsigned __int16 *)(target_unit + 4);
    target_col = *(unsigned __int16 *)(target_unit + 6);
    *(_BYTE *)(40 * target_row + g_MapData + 2 * target_col + 2334) = UnitBattle_GetCorpseSpriteIndex((__int16 *)target_unit);
    UnitBattle_PlayDeathAnimation(target_index, 0, 0, 0);
    *(_WORD *)target_unit = -1;
    *(_WORD *)(40 * target_row + g_MapData + 2 * target_col + 1534) = -1;
  }
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(shooter_unit + 2) + gameData + 140073) = 1;
  UnitBattle_RedrawVisibleGrid();
  return UnitBattle_DrawSelectedUnitPanel(0, 1, target_index, 0), 1;
}

//----- (004298E0) --------------------------------------------------------
int  UnitBattle_AttackWall(int unitSlot, DWORD wallRow, int a3, int wallCol)
{
  int result; // eax
  int unitRecord; // esi
  int rowDist; // eax
  int colDist; // eax
  unsigned __int16 unitCol; // dx
  unsigned __int16 unitRow; // ax
  int v12; // ebx
  int v13; // eax
  int v14; // ecx
  int wallTilePtr; // eax
  int v16; // ecx
  int moveTrackPtr; // ecx
  int rowDistAfterMove; // eax
  DWORD wallTileBase; // [esp+4h] [ebp-1Ch]
  int gateSpriteBefore; // [esp+8h] [ebp-18h]
  int wall_hp_before;
  int wall_hp_after;
  int unit_ap_before;
  int wall_kind;
  int wall_factor;
  int effective_wall_attack;
  int wall_damage;

  Debug_Log(a3, wallCol, wallRow, (int)aUnitbattle_a_0);
  if ( !g_UnitTypeBaseMeleeAttack_51257E[88 * *(__int16 *)(g_MapData + 31 * unitSlot + 852)] || !*(_BYTE *)(wallCol + g_MapData + 20 * wallRow + 3134) )
    return 0;
  g_SelectedUnitIndex = unitSlot;
  unitRecord = g_MapData + 852 + 31 * unitSlot;
  UnitBattle_RefreshSelectedUnitUI();
  rowDist = *(unsigned __int16 *)(unitRecord + 4) - wallRow;
  if ( rowDist <= 0 )
    rowDist = wallRow - *(unsigned __int16 *)(unitRecord + 4);
  if ( rowDist > 1 )
    goto LABEL_18;
  colDist = *(unsigned __int16 *)(unitRecord + 6) - wallCol;
  if ( colDist <= 0 )
    colDist = wallCol - *(unsigned __int16 *)(unitRecord + 6);
  if ( colDist )
  {
LABEL_18:
    result = (int)UnitBattle_MoveTrackNearWall(unitSlot, wallRow, wallCol, wallRow);
    if ( !result )
      return result;
    *(_DWORD *)(unitRecord + 23) = result;
    UnitBattle_Move(unitSlot, 0, 0, 0);
    moveTrackPtr = *(_DWORD *)(unitRecord + 23);
    if ( moveTrackPtr )
    {
      nfree_(moveTrackPtr);
      *(_DWORD *)(unitRecord + 23) = 0;
      return 0;
    }
    rowDistAfterMove = *(unsigned __int16 *)(unitRecord + 4) - wallRow;
    if ( rowDistAfterMove <= 0 )
      rowDistAfterMove = wallRow - *(unsigned __int16 *)(unitRecord + 4);
    if ( rowDistAfterMove > 1 )
      return 0;
    if ( *(unsigned __int16 *)(unitRecord + 6) - wallCol > 0 )
      return 0;
    if ( wallCol != *(unsigned __int16 *)(unitRecord + 6) )
      return 0;
  }
  unit_ap_before = *(unsigned __int8 *)(unitRecord + 8);
  if ( unit_ap_before < 5u )
    return 0;
  *(_BYTE *)(unitRecord + 8) -= 5;
  unitCol = *(_WORD *)(unitRecord + 6);
  unitRow = *(_WORD *)(unitRecord + 4);
  *(_BYTE *)(unitRecord + 22) &= ~1u;
  if ( !UnitBattle_IsTileInViewport(unitRow, unitCol) || !UnitBattle_IsTileInViewport(wallRow, wallCol) )
  {
    UnitBattle_CenterViewOnUnit(unitSlot);
    UnitBattle_RedrawVisibleGrid();
  }
  HIWORD(v12) = 0;
  *(_BYTE *)(unitRecord + 3) = Facing_DirectionFromDelta8(wallRow - *(unsigned __int16 *)(unitRecord + 4), wallCol - *(unsigned __int16 *)(unitRecord + 6));
  UnitBattle_PlayAttackAnimation(unitSlot, -1, 0, 0, (unsigned __int16 *)wallRow);
  UnitBattle_RedrawTile(wallRow, wallCol);
  gateSpriteBefore = g_BattleWallGateLastSpriteChar;
  wallTileBase = wallCol + g_MapData + 20 * wallRow;
  wall_hp_before = *(unsigned __int8 *)(wallTileBase + 3134);
  wall_kind = *(_DWORD *)(g_MapData + 820);
  wall_factor = (unsigned __int16)g_WallKindDefenseFactor[2 * wall_kind];
  effective_wall_attack = Unit_CalcEffectivenessD((char *)unitRecord, 0);
  wall_damage = wall_factor * effective_wall_attack / 256;
  *(_BYTE *)(wallTileBase + 3134) -= wall_damage;
  wall_hp_after = *(unsigned __int8 *)(wallTileBase + 3134);
  wallTilePtr = wallTileBase;
  if ( *(char *)(wallTilePtr + 3134) <= 0 )
  {
    *(_BYTE *)(wallTilePtr + 3134) = 0;
    if ( wallCol == *(_DWORD *)(g_MapData + 828) )
      *(_DWORD *)(g_MapData + 832) = 0;
    wall_hp_after = *(unsigned __int8 *)(wallTilePtr + 3134);
  }
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(
      stderr,
      "[battle] wall_attack unit=%d type=%d tile=%lu,%d ap_before=%d ap_after=%d wall_before=%d wall_after=%d wall_kind=%d wall_factor=%d effective_wall_attack=%d wall_damage=%d gate_column=%d gate_state=%d battle_result=%d\n",
      unitSlot,
      *(__int16 *)unitRecord,
      (unsigned long)wallRow,
      wallCol,
      unit_ap_before,
      *(unsigned __int8 *)(unitRecord + 8),
      wall_hp_before,
      wall_hp_after,
      wall_kind,
      wall_factor,
      effective_wall_attack,
      wall_damage,
      *(_DWORD *)(g_MapData + 828),
      *(_DWORD *)(g_MapData + 832),
      g_BattleWallGateLastSpriteChar);
  UnitBattle_RedrawTile(wallRow, wallCol);
  if ( gateSpriteBefore != g_BattleWallGateLastSpriteChar )
    Audio_PlaySoundEffectByName(aBattleMurek, 64);
  UnitBattle_RedrawTile(wallRow + 1, wallCol);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(unitRecord + 2) + gameData + 140073) = 1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, v12, wallCol);
  return 1;
}
// 429B53: conditional instruction was optimized away because eax.4>=1
// 429A85: variable 'v14' is possibly undefined
// 429B24: variable 'v16' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513A78: using guessed type __int16 word_513A78[];
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;
// 532104: using guessed type int dword_532104;

//----- (00429BD0) --------------------------------------------------------
int  UnitBattle_ShotWall(int unitSlot, int targetRow)
{
  char *unitRecord; // esi
  int targetCol; // ebx
  int volleysUsed; // eax
  int effectiveDamage; // eax
  int rowDist; // edx
  int colDist; // eax
  int distance; // eax
  int gateSpriteBefore; // ecx
  int wallRowBase; // eax
  int v12; // edx
  int wallHpAfter; // eax
  int v14; // eax

  targetCol = g_BattleTargetTileCol;
  Debug_Log(unitSlot, targetRow, targetCol, (int)aUnitbattle_s_0, unitSlot, targetRow, targetCol);
  unitRecord = (char *)(g_MapData + 852 + 31 * unitSlot);
  if ( !UnitBattle_IsTileWithinRange(unitSlot, targetRow, targetCol) )
    return 0;
  volleysUsed = UNIT_SLOT_VOLLEYS_USED(unitRecord);
  if ( volleysUsed >= UNIT_SLOT_STATUS_LEVEL(unitRecord) + 1 )
    return 0;
  if ( (unsigned __int8)unitRecord[8] < 5u )
    return 0;
  unitRecord[8] -= 5;
  UNIT_SLOT_SET_VOLLEYS_USED(unitRecord, volleysUsed + 1);
  g_SelectedUnitIndex = unitSlot;
  UnitBattle_PlayShotAnimation(unitSlot, -1, targetCol, targetRow, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  UnitBattle_RedrawTile(targetRow, targetCol);
  gateSpriteBefore = g_BattleWallGateLastSpriteChar;
  effectiveDamage = Unit_CalcEffectivenessC((__int16 *)unitRecord);
  rowDist = (unsigned __int16)*(unsigned __int16 *)(unitRecord + 4) - targetRow;
  if ( rowDist < 0 )
    rowDist = targetRow - *(unsigned __int16 *)(unitRecord + 4);
  colDist = *(unsigned __int16 *)(unitRecord + 6) - targetCol;
  if ( colDist < 0 )
    colDist = targetCol - *(unsigned __int16 *)(unitRecord + 6);
  distance = Math_CeilSqrt(rowDist * rowDist + colDist * colDist);
  if ( *(__int16 *)unitRecord == UNIT_TYPE_CANNON && distance > 4 )
    effectiveDamage = 9 * effectiveDamage / 10;
  if ( *(__int16 *)unitRecord == UNIT_TYPE_CATAPULT && distance > 3 )
    effectiveDamage = 9 * effectiveDamage / 10;
  wallRowBase = g_MapData + 40 * targetRow;
  LOWORD(v12) = g_WallKindDefenseFactor[2 * *(_DWORD *)(g_MapData + 820)];
  wallHpAfter = *(signed __int8 *)(wallRowBase + targetCol + 3134) - ((effectiveDamage * (unsigned __int16)v12) >> 8);
  *(_BYTE *)(wallRowBase + targetCol + 3134) = wallHpAfter;
  if ( wallHpAfter <= 0 )
  {
    *(_BYTE *)(wallRowBase + targetCol + 3134) = 0;
    if ( targetCol == *(_DWORD *)(g_MapData + 828) )
      *(_DWORD *)(g_MapData + 832) = 0;
  }
  UnitBattle_RedrawTile(targetRow, targetCol);
  if ( gateSpriteBefore != g_BattleWallGateLastSpriteChar )
    Audio_PlaySoundEffectByName((int)aBattleMurek_0, 64);
  UnitBattle_RedrawTile(targetRow + 1, targetCol);
  *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(unitRecord + 2) + gameData + 140073) = 1;
  UnitBattle_DrawSelectedUnitPanel(0, 1, targetRow, targetCol);
  UnitBattle_RedrawUnitFootprint(unitSlot);
  return 1;
}

//----- (00429E30) --------------------------------------------------------
signed int  UnitBattle_Defence(int unitSlot, char a2, DWORD a3)
{
  int recordOffset; // edx

  Debug_Log(unitSlot, a2, a3, (int)aUnitbattle_def);
  recordOffset = 31 * unitSlot;
  if ( *(unsigned __int8 *)(g_MapData + recordOffset + 860) < 5u )
    return 0;
  *(_BYTE *)(g_MapData + recordOffset + 860) = 0;
  *(_BYTE *)(recordOffset + g_MapData + 874) |= 1u;
  return 1;
}
// 532048: using guessed type int g_MapData;

//----- (00429E90) --------------------------------------------------------
int  BuildCursor_HandleCancelButtonPress(int widget, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  g_BuildPlacementLoopDone = 1;
  return result;
}
// 531CD0: using guessed type int dword_531CD0;

//----- (00429EB0) --------------------------------------------------------
void BuildCursor_RequestExit(void)
{
  g_BuildPlacementLoopDone = 1;
}
// 531CD0: using guessed type int dword_531CD0;

//----- (00429EC0) --------------------------------------------------------
int  BuildCursor_DrawPlacementOverlay(__int64 result)
{
  __int64 tilePos64; // kr00_8
  int screenX; // edi
  int screenY; // esi
  int v4; // ebp
  int v5; // ebp
  int SpriteForChar; // eax
  unsigned __int16 overlayColor; // [esp+4h] [ebp-2Ch]

  tilePos64 = result;
  screenX = (((_DWORD)result - *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 32;
  screenY = ((HIDWORD(result) - *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 16;
  if ( *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) == 1 )
    overlayColor = 215;
  else
    overlayColor = 76;
  if ( !g_BuildCursorBuildingType || g_BuildCursorBuildingType == 3 )
  {
    if ( (_DWORD)result == (_DWORD)g_BuildPlacementTileXY )
    {
      LODWORD(result) = HIDWORD(g_BuildPlacementTileXY);
      if ( HIDWORD(result) == HIDWORD(g_BuildPlacementTileXY) )
      {
        if ( BuildCursor_IsPlacementValid(tilePos64, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex)
          && tilePos64 != __PAIR64__(
                     *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
                     *(__int16 *)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET)) )
        {
          LODWORD(result) = (*(int (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 24))(
                              (unsigned __int16)(screenX + 63),
                              (unsigned __int16)screenX,
                              (unsigned __int16)(screenY + 63),
                              (unsigned __int8)overlayColor);
          return result;
        }
        goto LABEL_26;
      }
    }
  }
  else
  {
    if ( result == g_BuildPlacementTileXY )
    {
      if ( BuildCursor_IsPlacementValid(result, SHIDWORD(result), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        screenX = (unsigned __int16)screenX;
        (*(void (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          (unsigned __int16)(screenX + 63),
          (unsigned __int16)screenX,
          (unsigned __int16)screenY,
          overlayColor);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            screenX,
                            screenX,
                            (unsigned __int16)(screenY + 63),
                            overlayColor);
        return result;
      }
      goto LABEL_26;
    }
    if ( result == __PAIR64__(HIDWORD(g_BuildPlacementTileXY), (int)g_BuildPlacementTileXY + 1) )
    {
      if ( BuildCursor_IsPlacementValid(result - 1, SHIDWORD(result), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        v4 = (unsigned __int16)(screenX + 63);
        (*(void (__fastcall **)(int, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          v4,
          (unsigned __int16)screenX,
          (unsigned __int16)screenY,
          overlayColor);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v4,
                            v4,
                            (unsigned __int16)(screenY + 63),
                            overlayColor);
        return result;
      }
      goto LABEL_26;
    }
    if ( result == __PAIR64__(HIDWORD(g_BuildPlacementTileXY) + 1, (int)g_BuildPlacementTileXY + 1) )
    {
      if ( BuildCursor_IsPlacementValid(result - 1, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
      {
        v5 = (unsigned __int16)(screenX + 63);
        (*(void (__fastcall **)(int, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
          v5,
          (unsigned __int16)screenX,
          (unsigned __int16)(screenY + 63),
          overlayColor);
        LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                            v5,
                            v5,
                            (unsigned __int16)(screenY + 63),
                            overlayColor);
        return result;
      }
      goto LABEL_26;
    }
    if ( (_DWORD)result == (_DWORD)g_BuildPlacementTileXY )
    {
      LODWORD(result) = HIDWORD(g_BuildPlacementTileXY) + 1;
      if ( HIDWORD(result) == HIDWORD(g_BuildPlacementTileXY) + 1 )
      {
        if ( BuildCursor_IsPlacementValid(tilePos64, SHIDWORD(g_BuildPlacementTileXY), g_BuildCursorBuildingType, g_SelectedUnitIndex) )
        {
          screenX = (unsigned __int16)screenX;
          (*(void (__fastcall **)(_DWORD, _DWORD, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
            (unsigned __int16)(screenX + 63),
            (unsigned __int16)screenX,
            (unsigned __int16)(screenY + 63),
            overlayColor);
          LODWORD(result) = (*(int (__fastcall **)(int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 20))(
                              screenX,
                              screenX,
                              (unsigned __int16)(screenY + 63),
                              overlayColor);
          return result;
        }
LABEL_26:
        SpriteForChar = DLX_GetSpriteForChar(g_ActiveUiSpriteSet, 8);
        LODWORD(result) = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
                            screenY,
                            SpriteForChar,
                            -1,
                            -1,
                            -1,
                            -1,
                            1,
                            0,
                            0);
      }
    }
  }
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202BC: using guessed type int dword_5202BC;
// 5202E4: using guessed type int gameData;
// 531CD4: using guessed type int dword_531CD4;
// 531CD8: using guessed type __int64 qword_531CD8;

//----- (0042A340) --------------------------------------------------------
int  BuildBuilding(int buildingType, int a2, char a3, double a4)
{
  DWORD widgetSlotOffset; // eax
  char coordShift; // cl
  int cursorPixelX; // edx
  int v8; // ebx
  unsigned int v9; // edx
  int cursorTileCol; // esi
  int prevTileCol; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  DWORD widgetSlotOffsetEnd; // eax
  int v18; // ecx
  int v20; // ecx
  int v21; // ecx
  int completionStrings[9]; // [esp+0h] [ebp-24h] BYREF

  Debug_Log(a2, a3, buildingType, (int)aBuildbuildingD, buildingType);
  g_BuildCursorBuildingType = buildingType;
  widgetSlotOffset = 53 * (buildingType + 2);
  g_BuildPlacementLoopDone = 0;
  coordShift = g_CursorCoordShift;
  cursorPixelX = g_MouseCursorRawX >> g_CursorCoordShift;
  *(int *)((char *)&g_BuildBuildingActionWidgetStateBase + widgetSlotOffset) = 2;
  *(int (**)())((char *)&g_BuildBuildingActionWidgetHandlerBase + widgetSlotOffset) = BuildCursor_HandleCancelButtonPress;
  v8 = gameData;
  g_WorldMapTileOverlayDrawHook = (int (__fastcall *)(_DWORD, _DWORD))BuildCursor_DrawPlacementOverlay;
  LODWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET)
                        + ((cursorPixelX - 32 - (__CFSHL__((cursorPixelX - 32) >> 31, 6) + ((cursorPixelX - 32) >> 31 << 6))) >> 6);
  HIDWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
                        + (((g_MouseCursorRawY >> coordShift)
                          - 16
                          - (__CFSHL__(((g_MouseCursorRawY >> coordShift) - 16) >> 31, 6)
                           + (((g_MouseCursorRawY >> coordShift) - 16) >> 31 << 6))) >> 6);
  WorldMap_RedrawViewport(1);
  while ( !g_BuildPlacementLoopDone )
  {
    DD_Pump((int)&g_RenderState, v8, (char)BuildCursor_DrawPlacementOverlay);
    WorldMap_RedrawFrame(v8);
    if ( !UIWidgetTable_PollHoverAndActions((int)&g_BuildBuildingActionWidgetTable, buildingType) && UI_TrySelectFriendlyStackUnderCursor() )
    {
      Render_Begin((int)&g_RenderState, 0, (char)BuildCursor_DrawPlacementOverlay);
      break;
    }
    WorldMap_HandleScrollKeysAndIdle(v9);
    cursorTileCol = (((g_MouseCursorRawX >> g_CursorCoordShift)
          - 32
          - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
           + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
        + *(_DWORD *)(gameData + MAP_VIEW_LEFT_OFFSET);
    v8 = g_BuildPlacementTileXY;
    if ( __PAIR64__(
           *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
         + (((g_MouseCursorRawY >> g_CursorCoordShift)
           - 16
           - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
            + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6),
           cursorTileCol) != g_BuildPlacementTileXY )
    {
      v8 = HIDWORD(g_BuildPlacementTileXY);
      HIDWORD(g_BuildPlacementTileXY) = *(_DWORD *)(gameData + MAP_VIEW_TOP_OFFSET)
                            + (((g_MouseCursorRawY >> g_CursorCoordShift)
                              - 16
                              - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                               + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6);
      prevTileCol = g_BuildPlacementTileXY;
      LODWORD(g_BuildPlacementTileXY) = cursorTileCol;
      WorldMap_RedrawTileIfVisible(prevTileCol, v8);
      if ( buildingType == 2 || buildingType == 1 )
      {
        v13 = v12 + 1;
        v14 = v8++;
        WorldMap_RedrawTileIfVisible(v12 + 1, v14);
        WorldMap_RedrawTileIfVisible(v15, v8);
        WorldMap_RedrawTileIfVisible(v13, v8);
      }
      WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY, SHIDWORD(g_BuildPlacementTileXY));
      if ( buildingType == 2 || buildingType == 1 )
      {
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY + 1, SHIDWORD(g_BuildPlacementTileXY));
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY, HIDWORD(g_BuildPlacementTileXY) + 1);
        WorldMap_RedrawTileIfVisible(g_BuildPlacementTileXY + 1, HIDWORD(g_BuildPlacementTileXY) + 1);
      }
    }
    if ( DD_IsFlipping((int)&g_RenderState) )
    {
      if ( buildingType == 3 )
      {
        v8 = g_SelectedUnitIndex;
        if ( Trap_New(g_BuildPlacementTileXY, SHIDWORD(g_BuildPlacementTileXY), v16, g_SelectedUnitIndex, a4) == 1 )
        {
          Win_PlayModeChangeFrameTransition(aZakl_pul, 1, v20, v8, 3u);
          completionStrings[0] = (int)g_BuildBuildingCompletionMessageStrings[0];
          completionStrings[1] = (int)g_BuildBuildingCompletionMessageStrings[1];
          completionStrings[2] = (int)g_BuildBuildingCompletionMessageStrings[2];
          UI_ShowInfoWindow(completionStrings[(unsigned __int8)g_LanguageIndex], 0, v21, 3u, (int)&completionStrings[3], (int)&g_BuildBuildingCompletionMessageStrings[3]);
          Render_Begin((int)&g_RenderState, 0, (char)&completionStrings[3]);
          g_BuildPlacementLoopDone = 1;
          break;
        }
      }
      else
      {
        v8 = g_SelectedUnitIndex;
        if ( ((BOOL (__cdecl *)(__int64, int, int, double, char *, int))Building_New)(
               g_BuildPlacementTileXY,
               buildingType,
               g_SelectedUnitIndex,
               a4,
               aZam,
               0) == 1 )
        {
          Audio_PlaySoundEffectByName((int)aStruktur_2, 64);
          Render_Begin((int)&g_RenderState, 0, (char)BuildCursor_DrawPlacementOverlay);
          g_BuildPlacementLoopDone = 1;
          break;
        }
      }
    }
  }
  widgetSlotOffsetEnd = 53 * (buildingType + 2);
  *(int *)((char *)&g_BuildBuildingActionWidgetStateBase + widgetSlotOffsetEnd) = 1;
  *(int (**)())((char *)&g_BuildBuildingActionWidgetHandlerBase + widgetSlotOffsetEnd) = (int (*)())BuildCursor_RequestExit;
  UIWidget_RefreshActionButtonState((int)&g_BuildBuildingActionWidgetTable + widgetSlotOffsetEnd, 1);
  g_WorldMapTileOverlayDrawHook = 0;
  return WorldMap_RedrawViewport(v18);
}
// 42A425: variable 'v9' is possibly undefined
// 42A4AD: variable 'v12' is possibly undefined
// 42A4BE: variable 'v15' is possibly undefined
// 42A597: variable 'v18' is possibly undefined
// 42A629: variable 'v16' is possibly undefined
// 42A645: variable 'v20' is possibly undefined
// 42A659: variable 'v21' is possibly undefined
// 429E90: using guessed type int sub_429E90();
// 511130: using guessed type char byte_511130;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5146C8: using guessed type int dword_5146C8;
// 5146E0: using guessed type int (*off_5146E0)();
// 514834: using guessed type char *off_514834[3];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);
// 531CD0: using guessed type int dword_531CD0;
// 531CD4: using guessed type int dword_531CD4;
// 531CD8: using guessed type __int64 qword_531CD8;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0042A760) --------------------------------------------------------
int  UI_DrawNoticeBoxSmall(DWORD renderState, int a2)
{
  int spriteIndex; // edx
  int SpriteForChar; // eax
  int tax_rate; // ecx

  g_RenderDevice = &g_MainRenderDevice;
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 198, 208, 0x104u, 0xDAu, 0xD0u, 0xC6u);
  Render_ReleaseSurface(5, renderState);
  tax_rate = *(_BYTE *)(g_BuildingEconomyDialogBuilding + 436) & 0x3F;
  UI_DrawTextFmt(208, 208, 260, 198, 3, aD_D, tax_rate / 10, tax_rate % 10);
  if ( (__int16)(16 * *(_WORD *)(g_BuildingEconomyDialogBuilding + 432)) >> 4 <= 0
    || (*(_BYTE *)(g_BuildingEconomyDialogBuilding + 435) & 7) != 0 )
  {
    if ( (__int16)(16 * *(_WORD *)(g_BuildingEconomyDialogBuilding + 432)) >> 4
      || (*(_BYTE *)(g_BuildingEconomyDialogBuilding + 435) & 7) != 0 )
      spriteIndex = 4;
    else
      spriteIndex = 3;
  }
  else
  {
    spriteIndex = 5;
  }
  SpriteForChar = DLX_GetSpriteForChar(g_BuildingEconomyDialogSpriteSet, spriteIndex);
  return Compat_RenderDeviceDrawMenuSprite(383, 19, SpriteForChar, 0);
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CE4: using guessed type int g_BuildingEconomyDialogSpriteSet;
// 531CF4: using guessed type int g_BuildingEconomyDialogBuilding;

//----- (0042A890) --------------------------------------------------------
int  UI_DrawConfirmTop(DWORD renderState, int a2)
{
  void *savedRenderDevice; // esi
  int result; // eax

  savedRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(5, renderState);
  Render_SaveBackbuffer((int)&g_MainRenderDevice);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 360, 548, 0x259u, 0x17Cu, 0x224u, 0x168u);
  result = UI_DrawTextFmt(548, 548, 601, 360, 3, aD_8, g_BuildingEconomyDialogPendingPeasantTransfer);
  g_RenderDevice = savedRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 531CEC: using guessed type int g_BuildingEconomyDialogPendingPeasantTransfer;
