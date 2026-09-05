/* Generated from src/recovered/world/00408030_world_map.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "world_internal.h"
#include "world_state.h"
#include "world_shared_state.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00408030) --------------------------------------------------------
BOOL UI_TrySelectFriendlyStackUnderCursor(void)
{
  BOOL result; // eax
  int tileX; // esi
  int tileY; // ecx
  unsigned int stackIndex; // edx

  result = DD_IsFlipping((int)(intptr_t)g_RenderState);
  if ( result )
  {
    tileY = (((g_MouseCursorRawY >> g_CursorCoordShift)
         - 16
         - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
          + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
       + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET);
    if ( tileY == *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) + 6
      && ((g_MouseCursorRawX >> g_CursorCoordShift)
        - 32
        - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
         + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6 >= 6 )
    {
      return 0;
    }
    tileX = (((g_MouseCursorRawX >> g_CursorCoordShift)
         - 32
         - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
          + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
       + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
    stackIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY));
    if ( stackIndex > 0x7FFF || stackIndex == g_SelectedUnitIndex || *(unsigned __int8 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147178) != g_CurrentPlayerIndex )
    {
      return 0;
    }
    else
    {
      result = 1;
      g_SelectedUnitIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY));
      Diagnostics_TraceWorldMapActionEvent("selected_stack_changed", g_SelectedUnitIndex, tileX, tileY, 0);
    }
  }
  return result;
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00408140) --------------------------------------------------------
BOOL  MapTile_HasOwnUnitStack(int tileX, int tileY)
{
  unsigned __int16 stackIndex; // bx
  int stackIndexDword; // edx

  HIWORD(stackIndexDword) = 0;
  stackIndex = *(_WORD *)(uintptr_t)(TILE_INDEX(tileX, tileY));
  LOWORD(stackIndexDword) = stackIndex;
  return stackIndex <= 0x1F4u
      && (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndexDword + 147180) <= 0x28
      && *(unsigned __int8 *)(uintptr_t)(UNIT_STACK_STRIDE * stackIndex + gameData + 147178) == g_CurrentPlayerIndex;
}
// 4081A7: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00408200) --------------------------------------------------------
BOOL  MapTile_HasVisibleEnemyUnitStack(int tileX, int tileY)
{
  int stackIndex; // edx
  int stackRecord; // eax
  BOOL result; // eax

  stackIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY));
  result = 0;
  if ( (unsigned __int16)stackIndex <= 0x1F4u && (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * stackIndex + 147180) <= 0x28 )
  {
    stackRecord = gameData + UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY));
    if ( *(unsigned __int8 *)(uintptr_t)(stackRecord + 147178) != g_CurrentPlayerIndex && !*(_BYTE *)(uintptr_t)(stackRecord + 147894) )
      return 1;
  }
  return result;
}
// 408268: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004082C0) --------------------------------------------------------
BOOL  MapTile_HasOwnOrVisibleEnemyUnitStack(int tileX, int tileY)
{
  BOOL result; // eax

  if ( MapTile_HasOwnUnitStack(tileX, tileY) )
    return 1;
  result = MapTile_HasVisibleEnemyUnitStack(tileX, tileY);
  if ( result )
    return 1;
  return result;
}

//----- (004082F0) --------------------------------------------------------
BOOL  MapTile_HasOwnBuilding(int tileX, int tileY)
{
  unsigned int buildingIndex; // eax
  int buildingTableRecord; // edx
  int buildingRecord; // eax
  BOOL result; // eax

  buildingIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
  result = 0;
  if ( buildingIndex <= 0x64 )
  {
    buildingTableRecord = UNIT_RECORD(buildingIndex);
    if ( (unsigned int)*(char *)(uintptr_t)(buildingTableRecord + 4) < 4 && *(__int16 *)(uintptr_t)(buildingTableRecord + 16) != -1 )
    {
      buildingRecord = gameData + BUILDING_RECORD_SIZE * buildingIndex;
      if ( *(unsigned __int8 *)(uintptr_t)(buildingRecord + 509676) == g_CurrentPlayerIndex && *(__int16 *)(uintptr_t)(buildingRecord + 509690) != -1 )
        return 1;
    }
  }
  return result;
}
// 40832B: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 408346: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00408390) --------------------------------------------------------
BOOL  MapTile_HasEnemyBuilding(int tileX, int tileY)
{
  unsigned int buildingIndex; // eax
  int buildingTableRecord; // edx
  int buildingRecord; // eax
  BOOL result; // eax

  buildingIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
  result = 0;
  if ( buildingIndex <= 0x64 )
  {
    buildingTableRecord = UNIT_RECORD(buildingIndex);
    if ( (unsigned int)*(char *)(uintptr_t)(buildingTableRecord + 4) < 4 && *(__int16 *)(uintptr_t)(buildingTableRecord + 16) != -1 )
    {
      buildingRecord = gameData + BUILDING_RECORD_SIZE * buildingIndex;
      if ( *(unsigned __int8 *)(uintptr_t)(buildingRecord + 509676) != g_CurrentPlayerIndex && *(__int16 *)(uintptr_t)(buildingRecord + 509690) != -1 )
        return 1;
    }
  }
  return result;
}
// 4083CB: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 4083E6: simplified comparisons for 'ecx.4': <0 || >=4 became >=4u
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00408430) --------------------------------------------------------
BOOL  MapTile_HasBuilding(int tileX, int tileY)
{
  BOOL result; // eax

  if ( MapTile_HasOwnBuilding(tileX, tileY) )
    return 1;
  result = MapTile_HasEnemyBuilding(tileX, tileY);
  if ( result )
    return 1;
  return result;
}

//----- (00408460) --------------------------------------------------------
BOOL  Port_IsInsideFootprint(int tileX, int tileY)
{
  int portRow; // ebx
  int portColumn; // edi
  BOOL result; // eax

  portRow = PORT_ROW;
  result = 0;
  if ( portRow != -1 && tileX >= portRow && tileX <= portRow + 1 )
  {
    portColumn = PORT_COLUMN;
    if ( tileY >= portColumn && tileY <= portColumn + 1 )
      return 1;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004084A0) --------------------------------------------------------
void  WorldMap_HandleTileHoverAndClick(double a1)
{
  int tileX; // ebp
  int v2; // edx
  int v3; // ecx
  unsigned __int16 *tileColumnBase; // ecx
  int v5; // ebx
  int v6; // ecx
  void *cursorDescriptor; // edx
  int tileYByteOffset; // edi
  int tileXByteOffset; // esi
  int v10; // ecx
  unsigned int terrainClass; // ecx
  char *terrainNamePl; // eax
  char *terrainNameEn; // edx
  char *terrainNameDe; // ecx
  void *attackCursorDesc; // edx
  void *v16; // ecx
  int buildingTileYOffset; // esi
  int buildingRecordByteOffset; // ecx
  int buildingRecord; // edx
  DWORD buildingTableRecord; // eax
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  char v27; // bl
  char v28; // di
  const void *portApproachTrack; // ebp
  int v30; // ebx
  int v31; // ecx
  const void *approachTrack; // ebp
  void *pathBufferDest; // edi
  void (*v34)(void); // edx
  _DWORD *portTrack; // ebp
  int v36; // edx
  char v37; // bl
  __int16 *Supply; // eax
  __int16 *shipment; // eax
  int v40 CLASH95_UNUSED; // esi
  int v41 CLASH95_UNUSED; // ecx
  int buildingIndex; // eax
  int buildingRecordOffset; // ebx
  __int16 constructionState; // si
  int hasOwnBuilding; // edi
  int buildingTileXOffset; // esi
  int ownBuildingTileYOffset; // ecx
  int targetBuildingIndex; // edx
  int v49 CLASH95_UNUSED; // ecx
  int v50 CLASH95_UNUSED; // ecx
  char v51; // bl
  int v52; // ecx
  int tileStackPtr; // eax
  char v54; // di
  void *v55; // ecx
  DWORD prevSelectedIndex; // ebp
  void *v57; // ecx
  int v58 CLASH95_UNUSED; // ecx
  void *v59; // ecx
  void *v60; // ecx
  DWORD v61; // ebp
  int v62; // edx
  int unitTileY; // ebx
  const void *moveTrack; // eax
  DWORD selectedStackByteOffset; // ebp
  DWORD selectedStackRecord; // edx
  int v67 CLASH95_UNUSED; // ecx
  int stackPosPacked; // eax
  char *tooltipTextPl; // [esp+0h] [ebp-70h]
  char *tooltipTextEn; // [esp+4h] [ebp-6Ch]
  char *tooltipTextDe; // [esp+8h] [ebp-68h]
  int shrineTextPtrs[3]; // [esp+Ch] [ebp-64h]
  int cultPlaceTextPtrs[3]; // [esp+18h] [ebp-58h]
  int emptyShrineTextPtrs[3]; // [esp+24h] [ebp-4Ch]
  int emptyCultPlaceTextPtrs[3]; // [esp+30h] [ebp-40h]
  int hiddenTreasureTextPtrs[3]; // [esp+3Ch] [ebp-34h]
  int castleFoundationTextPtrs[3]; // [esp+48h] [ebp-28h]
  int tileY; // [esp+54h] [ebp-1Ch]
  int bridge_crossings_enabled;

  if ( MiniMap_IsCursorInside() )
    goto LABEL_35;
  if ( g_MouseCursorRawX >> g_CursorCoordShift < 32 )
    return;
  if ( g_MouseCursorRawY >> g_CursorCoordShift < 16 )
    return;
  tileX = (((g_MouseCursorRawX >> g_CursorCoordShift)
       - 32
       - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
        + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6)
     + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
  tileY = (((g_MouseCursorRawY >> g_CursorCoordShift)
        - 16
        - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
         + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
      + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET);
  if ( tileX < 0
    || tileX >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
    || tileY < 0
    || tileY >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
    || *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) + 6 == tileY && tileX - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) >= 6 )
  {
    if ( DD_IsLost((int)(intptr_t)&g_RenderState) || DD_IsFlipping((int)(intptr_t)&g_RenderState) )
      Diagnostics_TraceWorldMapClickEvent(
        "reject_out_of_bounds",
        tileX,
        tileY,
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    return;
  }
  Diagnostics_TraceWorldMapCursorSample(
    tileX,
    tileY,
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
    *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
    g_SelectedUnitIndex);
  if ( DD_IsLost((int)(intptr_t)&g_RenderState) || DD_IsFlipping((int)(intptr_t)&g_RenderState) )
    Diagnostics_TraceWorldMapClickEvent(
      "tile_input",
      tileX,
      tileY,
      *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
      *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
      g_SelectedUnitIndex);
  if ( DD_IsFlipping((int)(intptr_t)&g_RenderState) || DD_IsLost((int)(intptr_t)&g_RenderState) )
    goto LABEL_12;
  LOBYTE(v3) = g_CursorCoordShift;
  if ( g_MouseCursorRawX >> g_CursorCoordShift == g_WorldMap_LastCursorTileX && g_MouseCursorRawY >> g_CursorCoordShift == g_WorldMap_LastCursorTileY )
  {
    if ( g_WorldMap_HoverTooltipActiveFlag )
      goto LABEL_12;
  }
  else
  {
    LOBYTE(v3) = g_CursorCoordShift;
    g_WorldMap_LastCursorTileX = g_MouseCursorRawX >> g_CursorCoordShift;
    g_WorldMap_LastCursorTileY = g_MouseCursorRawY >> g_CursorCoordShift;
    g_WorldMap_CursorTileEnterTime = Time_Now(v3, v2);
    if ( g_WorldMap_HoverTooltipActiveFlag )
      WorldMap_RefreshUnitStatusPanel(tileX);
    v2 = 0;
    g_WorldMap_HoverTooltipActiveFlag = 0;
  }
  if ( (unsigned int)(Time_Now(v3, v2) - g_WorldMap_CursorTileEnterTime) > 0xC8
    && *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) == 0xFFFF )
  {
    Map_GetTileSurfaceClassOrUnexplored(tileX, tileY);
    if ( !Map_IsTileVisibleToPlayer(tileX, tileY, g_CurrentPlayerIndex) )
    {
      tooltipTextPl = aTerenNieodkryt;
      tooltipTextEn = aUnexploredTerr;
      tooltipTextDe = aUnerforschtesT;
      goto LABEL_48;
    }
    if ( terrainClass >= 0xB7 )
    {
      if ( terrainClass <= 0xB7 )
      {
        terrainNamePl = aRvwnina4pa;
        terrainNameEn = aPlain4ap;
        terrainNameDe = aEbene;
        goto LABEL_47;
      }
      if ( terrainClass >= 0xCA )
      {
        if ( terrainClass <= 0xCA )
        {
          terrainNamePl = aGvryWysokie;
          terrainNameEn = aMountains;
          terrainNameDe = aBerge;
          goto LABEL_47;
        }
        if ( terrainClass >= 0xCC )
        {
          if ( terrainClass <= 0xCC )
          {
            tooltipTextPl = aGvryNiskie8pa;
            tooltipTextEn = aHills8ap;
            tooltipTextDe = aHbgel;
            goto LABEL_48;
          }
          if ( terrainClass == 207 )
          {
            terrainNamePl = aDroga3pa;
            terrainNameEn = aRoad3ap;
            terrainNameDe = aStrase;
            goto LABEL_47;
          }
        }
      }
      else if ( terrainClass == 185 )
      {
        tooltipTextPl = aLas6pa;
        tooltipTextEn = aForest6ap;
        tooltipTextDe = aBaum;
        goto LABEL_48;
      }
    }
    else if ( terrainClass >= 0x93 )
    {
      if ( terrainClass <= 0x93 )
      {
        terrainNamePl = aWoda;
        terrainNameEn = aWater;
        terrainNameDe = aWasser;
        goto LABEL_47;
      }
      if ( terrainClass == 151 )
      {
        tooltipTextPl = aPustynia5pa;
        tooltipTextEn = aDesert5ap;
        tooltipTextDe = aWbste;
        goto LABEL_48;
      }
    }
    else if ( terrainClass == 39 )
    {
      terrainNamePl = aBagno7pa;
      terrainNameEn = aSwamp7ap;
      terrainNameDe = aSumpf;
LABEL_47:
      tooltipTextPl = terrainNamePl;
      tooltipTextEn = terrainNameEn;
      tooltipTextDe = terrainNameDe;
LABEL_48:
      if ( (unsigned __int8)g_LanguageIndex == 0 )
        Tooltip_ShowText(3, tooltipTextPl);
      else if ( (unsigned __int8)g_LanguageIndex == 2 )
        Tooltip_ShowText(3, tooltipTextDe);
      else
        Tooltip_ShowText(3, tooltipTextEn);
      g_WorldMap_HoverTooltipActiveFlag = 1;
      goto LABEL_12;
    }
    tooltipTextPl = aBlad;
    tooltipTextEn = aError;
    tooltipTextDe = aError_0;
    goto LABEL_48;
  }
LABEL_12:
  if ( !Map_ClassifyFogOfWarOverlayForPlayer(tileX, tileY, g_CurrentPlayerIndex) )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      Diagnostics_TraceWorldMapClickEvent(
        "reject_fog",
        tileX,
        tileY,
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
LABEL_35:
    RenderState_SelectCursorDescriptor((int)(intptr_t)&g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
    return;
  }
  v5 = 0;
  if ( g_SelectedUnitIndex != -1 && MapTile_HasOwnOrVisibleEnemyUnitStack(tileX, tileY) )
  {
    if ( MapTile_HasOwnUnitStack(tileX, tileY) )
    {
      if ( *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) == g_SelectedUnitIndex
        && *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) )
      {
        v5 = 1;
        RenderState_SelectCursorDescriptor((int)(intptr_t)&g_RenderState, (int)(intptr_t)&g_CursorDesc_SelectedUnitHover);
        g_WorldMapActionHoverActive = 1;
        goto LABEL_21;
      }
      tileColumnBase = (unsigned __int16 *)(uintptr_t)(200 * tileX + gameData);
      if ( tileColumnBase[tileY + 278187] != g_SelectedUnitIndex && g_WorldMapJoinUnitsModeActive )
      {
        RenderState_SelectCursorDescriptor((int)(intptr_t)&g_RenderState, (int)(intptr_t)&g_CursorDesc_CannotSelect);
        g_WorldMapActionHoverActive = v6;
        goto LABEL_21;
      }
    }
    else if ( MapTile_HasVisibleEnemyUnitStack(tileX, tileY) )
    {
      if ( UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
        attackCursorDesc = &g_CursorDesc_Attack;
      else
        attackCursorDesc = &g_CursorDesc_CannotAttack;
      RenderState_SelectCursorDescriptor((int)(intptr_t)&g_RenderState, (int)(intptr_t)attackCursorDesc);
      g_WorldMapActionHoverActive = 1;
      goto LABEL_21;
    }
  }
  if ( g_WorldMapActionHoverActive )
  {
    WorldMap_RefreshActionButtonBarState(tileColumnBase);
    g_WorldMapActionHoverActive = 0;
  }
LABEL_21:
  if ( g_SelectedUnitIndex != -1 && MapTile_GetReligiousSiteCategory(tileX, tileY) )
  {
    if ( UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
    {
LABEL_24:
      cursorDescriptor = &g_CursorDesc_EnterSite;
LABEL_25:
      RenderState_SelectCursorDescriptor((int)(intptr_t)&g_RenderState, (int)(intptr_t)cursorDescriptor);
      goto LABEL_26;
    }
LABEL_80:
    cursorDescriptor = &g_CursorDesc_CannotEnter;
    goto LABEL_25;
  }
  if ( Port_IsInsideFootprint(tileX, tileY) )
  {
    if ( g_SelectedUnitIndex == -1 )
    {
      cursorDescriptor = &g_CursorDesc_GoTo;
      goto LABEL_25;
    }
    if ( UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
      goto LABEL_24;
    goto LABEL_80;
  }
  if ( MapTile_HasBuilding(tileX, tileY) )
  {
    if ( g_SelectedUnitIndex == -1 )
    {
      cursorDescriptor = &g_CursorDesc_GoTo;
      goto LABEL_25;
    }
    buildingTileYOffset = 2 * tileY;
    v5 = 200 * tileX;
    if ( !MapTile_HasOwnBuilding(tileX, tileY) )
    {
      if ( !UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex)
        || (v5 += gameData,
            *(_BYTE *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(uintptr_t)(buildingTileYOffset + v5 + 556374) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + 509678) == 1)
        && UnitStack_HasPeasantCargo(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex) )
      {
        cursorDescriptor = &g_CursorDesc_DeliverCargo;
      }
      else
      {
        cursorDescriptor = &g_CursorDesc_VisitBuilding;
      }
      goto LABEL_25;
    }
    v5 += gameData;
    if ( !Building_CanAcceptUnitStack(g_SelectedUnitIndex, *(unsigned __int16 *)(uintptr_t)(buildingTileYOffset + v5 + 556374) - TILE_OCCUPANT_BUILDING_INDEX_BASE) )
    {
      cursorDescriptor = &g_CursorDesc_CannotEnter;
      goto LABEL_25;
    }
    goto LABEL_24;
  }
  if ( (_UNKNOWN *)(uintptr_t)g_ActiveCursorDescriptorPtr == &g_CursorDesc_GoTo
    || (_UNKNOWN *)(uintptr_t)g_ActiveCursorDescriptorPtr == &g_CursorDesc_EnterSite
    || (_UNKNOWN *)(uintptr_t)g_ActiveCursorDescriptorPtr == &g_CursorDesc_VisitBuilding
    || (_UNKNOWN *)(uintptr_t)g_ActiveCursorDescriptorPtr == &g_CursorDesc_DeliverCargo
    || (_UNKNOWN *)(uintptr_t)g_ActiveCursorDescriptorPtr == &g_CursorDesc_CannotEnter )
  {
    WorldMap_RefreshActionButtonBarState(v16);
  }
LABEL_26:
  if ( DD_IsLost((int)(intptr_t)&g_RenderState) && Port_IsInsideFootprint(tileX, tileY) )
    UI_DrawPortStatusPanel(v5, tileX);
  if ( DD_IsLost((int)(intptr_t)&g_RenderState) )
  {
    tileYByteOffset = 2 * tileY;
    tileXByteOffset = 200 * tileX;
    if ( MapTile_HasOwnOrVisibleEnemyUnitStack(tileX, tileY) )
    {
      if ( Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(tileYByteOffset + gameData + tileXByteOffset + TILE_MAP_OFFSET)) <= 1 )
      {
        Unit_Info(100, 100, 0, UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(tileYByteOffset + gameData + tileXByteOffset + TILE_MAP_OFFSET) + gameData + UNIT_STACK_TABLE_OFFSET + 6, tileX, 0);
      }
      else
      {
        UnitStack_ShowSelectionDialog(*(unsigned __int16 *)(uintptr_t)(tileYByteOffset + tileXByteOffset + gameData + TILE_MAP_OFFSET), v5);
        UIWidget_RefreshActionButtonState((int)(intptr_t)&g_WorldMapJoinUnitsWidgetRecord, v10);
      }
    }
    else if ( MapTile_HasBuilding(tileX, tileY) )
    {
      buildingRecordByteOffset = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(uintptr_t)(tileYByteOffset + gameData + tileXByteOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
      buildingRecord = gameData + buildingRecordByteOffset;
      buildingTableRecord = buildingRecordByteOffset + gameData + BUILDING_TABLE_OFFSET;
      if ( *(_WORD *)(uintptr_t)(gameData + buildingRecordByteOffset + 509690) )
      {
        if ( *(unsigned __int8 *)(uintptr_t)(buildingRecord + 509676) == g_CurrentPlayerIndex && *(__int16 *)(uintptr_t)(buildingRecord + 509690) != -1 )
          Building_ShowConstructionProgressDialog(buildingTableRecord, g_CurrentPlayerIndex, tileX, a1);
      }
      else
      {
        Building_ShowHoverInfoPopup(buildingTableRecord, 0, tileYByteOffset);
      }
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_SHRINE )
    {
      shrineTextPtrs[0] = (int)(intptr_t)g_ShrineTexts[0];
      shrineTextPtrs[1] = (int)(intptr_t)g_ShrineTexts[1];
      shrineTextPtrs[2] = (int)(intptr_t)g_ShrineTexts[2];
      UI_ShowSimpleTextInfoWindow(shrineTextPtrs[(unsigned __int8)g_LanguageIndex], v21, v5, tileX);
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_EMPTY_SHRINE )
    {
      emptyShrineTextPtrs[0] = (int)(intptr_t)g_EmptyShrineTexts[0];
      emptyShrineTextPtrs[1] = (int)(intptr_t)g_EmptyShrineTexts[1];
      emptyShrineTextPtrs[2] = (int)(intptr_t)g_EmptyShrineTexts[2];
      UI_ShowSimpleTextInfoWindow(emptyShrineTextPtrs[(unsigned __int8)g_LanguageIndex], v22, v5, tileX);
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_CULT_PLACE )
    {
      cultPlaceTextPtrs[0] = (int)(intptr_t)g_CultPlaceTexts[0];
      cultPlaceTextPtrs[1] = (int)(intptr_t)g_CultPlaceTexts[1];
      cultPlaceTextPtrs[2] = (int)(intptr_t)g_CultPlaceTexts[2];
      UI_ShowSimpleTextInfoWindow(cultPlaceTextPtrs[(unsigned __int8)g_LanguageIndex], v23, v5, tileX);
    }
    else if ( MapTile_GetReligiousSiteCategory(tileX, tileY) == RELIGIOUS_SITE_CATEGORY_EMPTY_CULT_PLACE )
    {
      emptyCultPlaceTextPtrs[0] = (int)(intptr_t)g_EmptyCultPlaceTexts[0];
      emptyCultPlaceTextPtrs[1] = (int)(intptr_t)g_EmptyCultPlaceTexts[1];
      emptyCultPlaceTextPtrs[2] = (int)(intptr_t)g_EmptyCultPlaceTexts[2];
      UI_ShowSimpleTextInfoWindow(emptyCultPlaceTextPtrs[(unsigned __int8)g_LanguageIndex], v24, v5, tileX);
    }
    else if ( MapTile_IsCastleFoundationTile(tileX, tileY, 2) )
    {
      castleFoundationTextPtrs[0] = (int)(intptr_t)g_CastleFoundationTexts[0];
      castleFoundationTextPtrs[1] = (int)(intptr_t)g_CastleFoundationTexts[1];
      castleFoundationTextPtrs[2] = (int)(intptr_t)g_CastleFoundationTexts[2];
      UI_ShowSimpleTextInfoWindow(castleFoundationTextPtrs[(unsigned __int8)g_LanguageIndex], v25, 2, tileX);
    }
    else if ( MapTile_HasHiddenTreasure(tileX, tileY) )
    {
      hiddenTreasureTextPtrs[0] = (int)(intptr_t)g_HiddenTreasureTexts[0];
      hiddenTreasureTextPtrs[1] = (int)(intptr_t)g_HiddenTreasureTexts[1];
      hiddenTreasureTextPtrs[2] = (int)(intptr_t)g_HiddenTreasureTexts[2];
      UI_ShowSimpleTextInfoWindow(hiddenTreasureTextPtrs[(unsigned __int8)g_LanguageIndex], v26, 2, tileX);
    }
  }
  if ( !DD_IsFlipping((int)(intptr_t)&g_RenderState) )
    return;
  v27 = g_CurrentPlayerIndex;
  if ( Trap_GetTileOwnerMask(tileX, tileY, g_CurrentPlayerIndex) )
    Trap_ShowPitfallDiscoveryDialog(tileX, tileY, v27, tileX);
    if ( g_SelectedUnitIndex != -1
      && UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex)
      && MapTile_GetReligiousSiteCategory(tileX, tileY) )
  {
    LOBYTE(v30) = tileY;
    if ( !QueuedPath_StartsAtTile(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_PATH_OFFSET, tileX, tileY) )
    {
      LOBYTE(v30) = tileY;
      bridge_crossings_enabled = UnitStack_HasBuilder(g_SelectedUnitIndex);
      if ( bridge_crossings_enabled )
      {
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_enable_temple", g_SelectedUnitIndex, tileX, tileY, 0);
        Pathing_EnableBridgeCrossings(g_SelectedUnitIndex, (char)tileY, 0);
      }
      approachTrack = (const void *)Temple_GenerateApproachTrack(g_SelectedUnitIndex, tileX, v31, tileY);
      if ( bridge_crossings_enabled )
      {
        Pathing_DisableBridgeCrossings(g_SelectedUnitIndex, (char)(uintptr_t)approachTrack, 0);
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_disable_temple", g_SelectedUnitIndex, tileX, tileY, approachTrack != 0);
      }
      if ( approachTrack )
      {
        pathBufferDest = (void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_PATH_OFFSET);
        qmemcpy(pathBufferDest, approachTrack, UNIT_STACK_PATH_BYTES);
        j__nfree_();
        Diagnostics_TraceWorldMapActionEvent("temple_path_queued", g_SelectedUnitIndex, tileX, tileY, 1);
        WorldMap_RedrawViewport(1);
        Render_Begin((int)(intptr_t)&g_RenderState, 0);
      }
      if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) != 1 )
        return;
      goto LABEL_138;
    }
    if ( !UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
      return;
    goto LABEL_205;
  }
  v28 = g_SelectedUnitIndex;
    if ( g_SelectedUnitIndex != -1
      && UnitStack_HasNormalCombatUnits(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex)
      && Port_IsInsideFootprint(tileX, tileY) )
  {
    if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) )
    {
      portTrack = (_DWORD *)Port_GenerateApproachTrack(g_SelectedUnitIndex);
      v27 = gameData - 26;
      if ( *portTrack )
        v36 = portTrack[1];
      else
        v36 = *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 320);
      if ( (unsigned __int16)*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 320) == (_WORD)v36 )
      {
        v37 = gameData;
        qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), portTrack, UNIT_STACK_PATH_BYTES);
        if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) || !*portTrack )
        {
          if ( *portTrack )
          {
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
            UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, v37, (DWORD)(intptr_t)portTrack, a1);
            WorldMap_RefreshUnitStatusPanel((DWORD)(intptr_t)portTrack);
          }
          if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) )
          {
            Supply = (__int16 *)(uintptr_t)Port_CollectReinforcementShipment(145 * g_SelectedUnitIndex, v37, (DWORD)(intptr_t)portTrack, a1);
            if ( Supply )
              UI_CenterWorldMapViewportOnRectIfFit(
                *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
                *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
                Supply[1],
                *Supply);
          }
        }
        j__nfree_();
        return;
      }
      j__nfree_();
    }
    portApproachTrack = (const void *)Port_GenerateApproachTrack(g_SelectedUnitIndex);
    if ( portApproachTrack )
    {
      qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_PATH_OFFSET), portApproachTrack, UNIT_STACK_PATH_BYTES);
      j__nfree_();
      WorldMap_RedrawViewport(1);
      if ( !*(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET) )
      {
        shipment = (__int16 *)(uintptr_t)Port_CollectReinforcementShipment(UNIT_STACK_STRIDE * g_SelectedUnitIndex, v27, (DWORD)(intptr_t)portApproachTrack, a1);
        if ( shipment )
          UI_CenterWorldMapViewportOnRectIfFit(
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
            shipment[1],
            *shipment);
      }
    }
    return;
  }
  if ( Port_IsInsideFootprint(tileX, tileY) )
  {
    UI_DrawPortStatusPanel(v27, tileX);
    return;
  }
  v40 = 2 * tileY;
  if ( MapTile_HasBuilding(tileX, tileY) )
  {
    if ( g_SelectedUnitIndex == -1 && MapTile_HasOwnBuilding(tileX, tileY) )
    {
      buildingIndex = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
      buildingRecordOffset = BUILDING_RECORD_SIZE * buildingIndex;
      constructionState = *(_WORD *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * buildingIndex + 509690);
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        fprintf(
          stderr,
          "[world_click] own_building_enter_branch tile=%d,%d building_idx=%d construction=%d current_player=%d flipping=%d lost=%d\n",
          tileX,
          tileY,
          buildingIndex,
          constructionState,
          g_CurrentPlayerIndex,
          DD_IsFlipping((int)(intptr_t)&g_RenderState),
          DD_IsLost((int)(intptr_t)&g_RenderState));
      if ( constructionState )
      {
        if ( constructionState != -1 )
          Building_ShowConstructionProgressDialog(buildingRecordOffset + gameData + BUILDING_TABLE_OFFSET, buildingRecordOffset, tileX, a1);
      }
      else
      {
        Building_GetInto(buildingIndex, buildingRecordOffset, tileX);
      }
      return;
    }
    hasOwnBuilding = MapTile_HasOwnBuilding(tileX, tileY);
    buildingTileXOffset = 200 * tileX;
    v30 = UNIT_STACK_STRIDE * g_SelectedUnitIndex;
    ownBuildingTileYOffset = 2 * tileY;
    if ( !hasOwnBuilding )
    {
      if ( g_SelectedUnitIndex != -1
        && (*(_BYTE *)(uintptr_t)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(uintptr_t)(ownBuildingTileYOffset + gameData + buildingTileXOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509678) != 1
         || !UnitStack_HasPeasantCargo(v30 + gameData + UNIT_STACK_TABLE_OFFSET)) )
      {
        Unit_AttackBuilding(
          g_SelectedUnitIndex,
          *(unsigned __int16 *)(uintptr_t)(2 * tileY + gameData + TILE_ROW_STRIDE * tileX + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE,
          v30,
          200 * tileX,
          a1);
      }
      return;
    }
    targetBuildingIndex = *(unsigned __int16 *)(uintptr_t)(ownBuildingTileYOffset + gameData + buildingTileXOffset + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE;
    if ( *(_WORD *)(uintptr_t)(BUILDING_RECORD_SIZE * targetBuildingIndex + gameData + 509690) )
      return;
    if ( !QueuedPath_StartsInBuildingFootprint(v30 + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET, targetBuildingIndex) )
    {
      approachTrack = (const void *)Building_GenerateApproachTrack(
                            g_SelectedUnitIndex,
                            targetBuildingIndex,
                            ownBuildingTileYOffset,
                            v30,
                            tileX);
      if ( approachTrack )
      {
        qmemcpy((void *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), approachTrack, UNIT_STACK_PATH_BYTES);
        j__nfree_();
        WorldMap_RedrawViewport(1);
      }
      if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) != 1 )
        return;
LABEL_138:
      UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, v30, (DWORD)(intptr_t)approachTrack, a1);
      WorldMap_RefreshUnitStatusPanel((DWORD)(intptr_t)approachTrack);
      return;
    }
    if ( !UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
      return;
LABEL_205:
    Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
    UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, v30, tileX, a1);
    WorldMap_RefreshUnitStatusPanel(tileX);
    return;
  }
  if ( MapTile_HasOwnUnitStack(tileX, tileY) )
  {
    if ( DD_IsLost((int)(intptr_t)&g_RenderState) )
      Diagnostics_TraceWorldMapClickEvent(
        "own_stack",
        tileX,
        tileY,
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    if ( g_WorldMapJoinUnitsModeActive && *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) != g_SelectedUnitIndex )
    {
      Render_Begin((int)(intptr_t)&g_RenderState, 0, v28);
      Unit_AddToGroup(g_SelectedUnitIndex, *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)), 0, tileX, a1);
      g_WorldMapJoinUnitsModeActive = 0;
      WorldMap_RefreshActionButtonBarState(v59);
      WorldMap_RefreshUnitStatusPanel(tileX);
      UnitStackSelection_SyncForCurrentSelection(v60, tileX);
      WorldMap_RedrawViewport(1);
    }
    else
    {
      v51 = gameData;
      v52 = g_SelectedUnitIndex;
      if ( *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)) == g_SelectedUnitIndex
        && (v52 = 145 * g_SelectedUnitIndex, *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490)) )
      {
        Render_Begin((int)(intptr_t)&g_RenderState, 0, v28);
        if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
        {
          v61 = UNIT_STACK_STRIDE * g_SelectedUnitIndex;
          Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
          UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, v62, v51, v61, a1);
          WorldMap_RefreshUnitStatusPanel(v61);
        }
      }
      else
      {
        tileStackPtr = TILE_INDEX(tileX, tileY);
        v54 = g_SelectedUnitIndex;
        if ( *(unsigned __int16 *)(uintptr_t)tileStackPtr != g_SelectedUnitIndex )
        {
          g_LastSelectedUnitIndex = g_SelectedUnitIndex;
          g_SelectedUnitIndex = *(unsigned __int16 *)(uintptr_t)tileStackPtr;
          Diagnostics_TraceWorldMapActionEvent(
            "selected_stack_changed",
            g_SelectedUnitIndex,
            tileX,
            tileY,
            g_LastSelectedUnitIndex);
          UnitStackSelection_ClearMask((void *)(uintptr_t)v52);
          WorldMap_RefreshActionButtonBarState(v55);
          WorldMap_RedrawViewport(1);
          prevSelectedIndex = g_LastSelectedUnitIndex;
          if ( g_LastSelectedUnitIndex != -1 )
            WorldMap_RedrawTileIfVisible(
              *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_LastSelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
              *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_LastSelectedUnitIndex + 147176));
          WorldMap_RefreshUnitStatusPanel(prevSelectedIndex);
          UnitStackSelection_SyncForCurrentSelection(v57, prevSelectedIndex);
          Audio_PlayUnitActivateSound(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
          Render_Begin((int)(intptr_t)&g_RenderState, 0, v54);
        }
      }
    }
    return;
  }
  if ( g_SelectedUnitIndex != -1 && MapTile_HasVisibleEnemyUnitStack(tileX, tileY) )
  {
    if ( DD_IsLost((int)(intptr_t)&g_RenderState) )
      Diagnostics_TraceWorldMapClickEvent(
        "enemy_stack",
        tileX,
        tileY,
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    Render_Begin((int)(intptr_t)&g_RenderState, 0, v28);
    Diagnostics_TraceWorldMapActionEvent(
      "enemy_attack_call",
      g_SelectedUnitIndex,
      *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)),
      tileX,
      tileY);
    Unit_Attack(g_SelectedUnitIndex, *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)), v27, tileX, a1);
    Diagnostics_TraceWorldMapActionEvent(
      "enemy_attack_return",
      g_SelectedUnitIndex,
      *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(tileX, tileY)),
      tileX,
      tileY);
    Diagnostics_TraceWorldMapUnitSnapshot("after_enemy_attack");
    return;
  }
  if ( !MapTile_HasOwnOrVisibleEnemyUnitStack(tileX, tileY) && g_SelectedUnitIndex != -1 )
  {
    if ( Diagnostics_IsWorldMapClickTraceEnabled() )
      Diagnostics_TraceWorldMapClickEvent(
        "empty_tile_with_selection",
        tileX,
        tileY,
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
        g_SelectedUnitIndex);
    if ( !*(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490)
      || (stackPosPacked = *(_DWORD *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET + 320), (unsigned __int8)stackPosPacked != tileX)
      || (LOBYTE(v30) = tileY, BYTE1(stackPosPacked) != tileY) )
    {
      unitTileY = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176);
      bridge_crossings_enabled = UnitStack_HasBuilder(g_SelectedUnitIndex);
      if ( bridge_crossings_enabled )
      {
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_enable_move", g_SelectedUnitIndex, tileX, tileY, 0);
        Pathing_EnableBridgeCrossings(g_SelectedUnitIndex, (char)tileY, 0);
      }
      moveTrack = (const void *)Unit_MoveTrack(
                            g_SelectedUnitIndex,
                            *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
                            tileX,
                            unitTileY,
                            tileX,
                            tileY);
      if ( bridge_crossings_enabled )
      {
        Pathing_DisableBridgeCrossings(g_SelectedUnitIndex, (char)(uintptr_t)moveTrack, 0);
        Diagnostics_TraceWorldMapActionEvent("bridge_pathing_disable_move", g_SelectedUnitIndex, tileX, tileY, moveTrack != 0);
      }
      selectedStackByteOffset = UNIT_STACK_STRIDE * g_SelectedUnitIndex;
      if ( Diagnostics_IsWorldMapClickTraceEnabled() )
        Diagnostics_TraceWorldMapActionEvent(
          "move_order_track_result",
          g_SelectedUnitIndex,
          tileX,
          tileY,
          moveTrack ? *(_DWORD *)moveTrack : -1);
      if ( moveTrack )
      {
        selectedStackRecord = selectedStackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET;
        qmemcpy((void *)(uintptr_t)(selectedStackRecord + 316), moveTrack, UNIT_STACK_PATH_BYTES);
        v28 = selectedStackRecord - 48;
        j__nfree_();
      }
      else
      {
        *(_DWORD *)(uintptr_t)(gameData + selectedStackByteOffset + 147490) = 0;
      }
      if ( *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) == 1 )
      {
        if ( UnitStackSelection_HasSelectedSlots() )
        {
          *(_DWORD *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147490) = 0;
          WorldMap_RedrawViewport(1);
        }
        else
        {
          if ( UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
          UnitStack_ExecuteQueuedPath(g_SelectedUnitIndex, 1, unitTileY, selectedStackByteOffset, a1);
          WorldMap_RefreshUnitStatusPanel(selectedStackByteOffset);
          WorldMap_RedrawViewport(1);
        }
      }
      else
      {
        Render_Begin((int)(intptr_t)&g_RenderState, 0, v28);
        WorldMap_RedrawViewport(1);
      }
      return;
    }
    if ( !UnitStack_CanExecuteQueuedPathNow(g_SelectedUnitIndex) )
      return;
    goto LABEL_205;
  }
}
// 408698: variable 'v6' is possibly undefined
// 4087D2: variable 'v10' is possibly undefined
// 408845: variable 'v3' is possibly undefined
// 408845: variable 'v2' is possibly undefined
// 4088E4: variable 'v11' is possibly undefined
// 408B2B: variable 'v4' is possibly undefined
// 408CF5: variable 'v16' is possibly undefined
// 408E41: variable 'v25' is possibly undefined
// 408E62: variable 'v21' is possibly undefined
// 408E83: variable 'v22' is possibly undefined
// 408EA4: variable 'v23' is possibly undefined
// 408EC5: variable 'v24' is possibly undefined
// 408EF9: variable 'v26' is possibly undefined
// 4090F6: variable 'v31' is possibly undefined
// 409156: variable 'v34' is possibly undefined
// 409493: variable 'v41' is possibly undefined
// 40959E: variable 'v49' is possibly undefined
// 409779: variable 'v50' is possibly undefined
// 409859: variable 'v55' is possibly undefined
// 4098AC: variable 'v57' is possibly undefined
// 40990B: variable 'v58' is possibly undefined
// 40992A: variable 'v59' is possibly undefined
// 409934: variable 'v60' is possibly undefined
// 4099A8: variable 'v62' is possibly undefined
// 409B51: variable 'v67' is possibly undefined
// 511130: using guessed type char byte_511130;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 511B68: using guessed type char *off_511B68[21];
// 511B74: using guessed type char *off_511B74[18];
// 511B80: using guessed type char *off_511B80[15];
// 511B8C: using guessed type char *off_511B8C[12];
// 511B98: using guessed type char *g_CastleFoundationTexts[9];
// 511BA4: using guessed type char *off_511BA4[6];
// 5202A4: using guessed type int dword_5202A4;
// 5202A8: using guessed type int dword_5202A8;
// 5202AC: using guessed type int dword_5202AC;
// 5202B0: using guessed type int dword_5202B0;
// 5202B4: using guessed type int dword_5202B4;
// 5202E4: using guessed type int gameData;
// 5202E8: using guessed type int dword_5202E8;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (00409CC0) --------------------------------------------------------
int  WorldMap_ShowQuitConfirmDialog(int a1, char a2, DWORD a3)
{
  int result; // eax

  result = YesNoWindow((int)(intptr_t)g_Text_QuitConfirm[(unsigned __int8)g_LanguageIndex], 0, a1, a2, a3);
  g_WorldMapTurnLoopExitFlag = result;
  return result;
}
// 511130: using guessed type char g_LanguageIndex;
// 511B48: using guessed type char *g_Text_QuitConfirm[3];
// 5202F8: using guessed type int dword_5202F8;

//----- (00409CE0) --------------------------------------------------------
int  WorldMap_HandleSaveGameAction(char a1, DWORD a2, double a3)
{
  SaveSlotDialog_Run(1, a1, a2, a3);
  UnitStackSelection_RefreshForSelectedStack(a2);
  return WorldMap_RedrawViewport(1);
}

//----- (00409D00) --------------------------------------------------------
int  WorldMap_HandleLoadGameAction(DWORD a1, char a2, double a3)
{
  int result; // eax

  result = SaveSlotDialog_Run(0, a2, a1, a3);
  g_PendingLoadGameSlotIndex = result;
  if ( result == -1 )
  {
    WorldMap_RedrawViewport(1);
    return UnitStackSelection_RefreshForSelectedStack(a1);
  }
  else
  {
    g_WorldMapTurnLoopExitFlag = 1;
  }
  return result;
}
// 511B64: using guessed type int dword_511B64;
// 5202F8: using guessed type int dword_5202F8;

//----- (00409D30) --------------------------------------------------------
int  WorldMap_HandleSurrenderAction(int a1, char a2, DWORD a3, double a4)
{
  int result; // eax
  int v5; // ecx
  int v6; // edx
  int surrenderConfirmTexts[6]; // [esp+0h] [ebp-18h]

  surrenderConfirmTexts[0] = (int)(intptr_t)g_Text_SurrenderConfirm[0];
  surrenderConfirmTexts[1] = (int)(intptr_t)g_Text_SurrenderConfirm[1];
  surrenderConfirmTexts[2] = (int)(intptr_t)g_Text_SurrenderConfirm[2];
  result = YesNoWindow(surrenderConfirmTexts[(unsigned __int8)g_LanguageIndex], 0, a1, a2, a3);
  if ( result )
  {
    result = Player_Surrender(g_CurrentPlayerIndex, v5, a3, a4);
    g_AdvanceToNextPlayerFlag = v6;
  }
  return result;
}
// 409D66: variable 'v5' is possibly undefined
// 409D6B: variable 'v6' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511BB0: using guessed type char *g_Text_SurrenderConfirm[3];
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5202FC: using guessed type int dword_5202FC;

//----- (00409D80) --------------------------------------------------------
int  WorldMap_HandleDeselectUnitAction(uintptr_t widget, DWORD a2)
{
  if ( g_SelectedUnitIndex == -1 )
  {
    Audio_PlayButtonSound(aWrong_2);
    return Render_Begin((int)(intptr_t)g_RenderState, 0);
  }
  else
  {
    Audio_PlayButtonSound((char *)Compat_WidgetPackedString(widget, 49));
    g_LastSelectedUnitIndex = g_SelectedUnitIndex;
    g_SelectedUnitIndex = -1;
    UnitStackSelection_SyncForCurrentSelection(NULL, a2);
    WorldMap_RefreshActionButtonBarState(NULL);
    g_SavedCursorDescriptor = (int)(intptr_t)&g_CursorDesc_Default;
    return WorldMap_RedrawViewport(1);
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 526A34: using guessed type int dword_526A34;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00409DF0) --------------------------------------------------------
void  WorldMap_SelectNextActiveUnitStack(uintptr_t widget, int a2, DWORD statusPanelContext)
{
  int scan_index; // edx
  int found; // ebx
  int checked_count; // ecx
  int unit_record; // eax

  Diagnostics_TraceWorldMapActionEvent("next_unit_enter", g_SelectedUnitIndex, g_LastSelectedUnitIndex, g_CurrentPlayerIndex, 0);
  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  if ( g_SelectedUnitIndex == -1 )
  {
    if ( g_LastSelectedUnitIndex == -1 )
      scan_index = 0;
    else
      scan_index = g_LastSelectedUnitIndex;
  }
  else
  {
    scan_index = g_SelectedUnitIndex + 1;
  }
  scan_index %= 500;
  found = 0;
  checked_count = 0;
  do
  {
    unit_record = UNIT_STACK_STRIDE * scan_index + gameData;
    if ( *(__int16 *)(uintptr_t)(unit_record + 147180) != -1
      && *(unsigned __int8 *)(uintptr_t)(unit_record + 147178) == g_CurrentPlayerIndex
      && Unit_AttemptNeighborMove(scan_index) )
    {
      found = 1;
    }
    else
    {
      scan_index = (scan_index + 1) % 500;
    }
    ++checked_count;
  }
  while ( checked_count < 500 && !found );
  Diagnostics_TraceWorldMapActionEvent("next_unit_scan_done", g_SelectedUnitIndex, scan_index, found, checked_count);
  if ( found )
  {
    g_LastSelectedUnitIndex = g_SelectedUnitIndex;
    g_SelectedUnitIndex = scan_index;
    UnitStackSelection_ClearMask(NULL);
    WorldMap_RefreshActionButtonBarState(NULL);
    Camera_CenterOnUnit(scan_index);
    Audio_PlayUnitActivateSound(*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147180));
    WorldMap_RedrawViewport(1);
    WorldMap_RefreshUnitStatusPanel(statusPanelContext);
    UnitStackSelection_SyncForCurrentSelection(NULL, statusPanelContext);
    Diagnostics_TraceWorldMapActionEvent(
      "next_unit_selected",
      g_SelectedUnitIndex,
      *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
      *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + 147176),
      Unit_GetSquadCount(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * g_SelectedUnitIndex));
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 511B5C: using guessed type int g_LastSelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00409F00) --------------------------------------------------------
int  WorldMap_CenterViewOnNextOwnedBuildingWithUnit(int widget, int a2)
{
  int i; // ecx
  int buildingRecord; // eax
  void *v5; // ecx

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  g_UnitSearchCursor = (g_UnitSearchCursor + 1) % 100;
  for ( i = 0; i < 100; ++i )
  {
    if ( (unsigned int)g_UnitSearchCursor <= 0x64 )
    {
      buildingRecord = UNIT_RECORD(g_UnitSearchCursor);
      if ( (unsigned int)*(char *)(uintptr_t)(buildingRecord + 4) < 4
        && *(__int16 *)(uintptr_t)(buildingRecord + 16) != -1
        && *(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_RECORD_SIZE * g_UnitSearchCursor + 509676) == g_CurrentPlayerIndex )
      {
        break;
      }
    }
    g_UnitSearchCursor = (g_UnitSearchCursor + 1) % 100;
  }
  UI_CenterWorldMapViewportOnTile(
    *(unsigned __int8 *)(uintptr_t)(UNIT_RECORD(g_UnitSearchCursor)),
    *(unsigned __int8 *)(uintptr_t)(BUILDING_RECORD_SIZE * g_UnitSearchCursor + gameData + 509675));
  g_SelectedUnitIndex = -1;
  WorldMap_RefreshActionButtonBarState(v5);
  return WorldMap_RedrawViewport(1);
}
// 409F38: simplified comparisons for '$g_UnitSearchCursor.4': <0 || >=65 became >=65u
// 409F59: simplified comparisons for 'edx.4': <0 || >=4 became >=4u
// 409FE2: variable 'v5' is possibly undefined
// 511B54: using guessed type int g_UnitSearchCursor;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040A000) --------------------------------------------------------
int  WorldMap_HandleHideUnitAction(int widget, int a2, unsigned __int16 a3, DWORD a4, double a5)
{
  if ( g_SelectedUnitIndex == -1 )
  {
    Audio_PlayButtonSound(aWrong_3);
    return Render_Begin((int)(intptr_t)g_RenderState, 0);
  }
  else
  {
    UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
    return UnitStack_TryHide(g_SelectedUnitIndex, a3, a4, a5);
  }
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040A040) --------------------------------------------------------
char *WorldMap_ToggleSelectedUnitModeFlag(void)
{
  int v1; // ecx
  char *result; // eax
  int v3; // ecx

  Render_Begin((int)(intptr_t)g_RenderState, 0);
  if ( g_SelectedUnitIndex == -1 )
    return Audio_PlayButtonSound(aWrong_4);
  result = Audio_PlayButtonSound(*(char **)(uintptr_t)(v1 + 49));
  if ( g_WorldMapJoinUnitsModeActive )
  {
    g_WorldMapJoinUnitsModeActive = 0;
    *(_DWORD *)(uintptr_t)(v3 + 8) = 1;
  }
  else
  {
    g_WorldMapJoinUnitsModeActive = 1;
    *(_DWORD *)(uintptr_t)(v3 + 8) = 2;
  }
  return result;
}
// 40A059: variable 'v1' is possibly undefined
// 40A073: variable 'v3' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E8: using guessed type int dword_5202E8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0040A0A0) --------------------------------------------------------
int  WorldMap_ComputeBuildMenuActionFromCursor(int widget, int a2)
{
  int v3; // edx
  int result; // eax

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  result = (*(_DWORD *)(uintptr_t)(v3 + 16) - 15) / 2;
  g_WorldMapBuilderMenuAction = result;
  return result;
}
// 40A0A8: variable 'v3' is possibly undefined
// 520308: using guessed type int dword_520308;

CLASH95_INTERNAL void WorldMap_EnsureActionButtonWidgetTable(void);
