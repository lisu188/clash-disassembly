/* Generated from src/recovered/world/00408030_world_map.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "world_internal.h"
#include "world_state.h"
#include "world_shared_state.h"
#include "../render/render_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0040D6D0) --------------------------------------------------------
int  MiniMap_RedrawTileRect(int x0, signed int y0, int y1, int x1)
{
  signed int clampedY0; // edi
  int clampedY1; // esi
  int mapWidth; // ebx
  int mapHeight; // eax
  int result; // eax
  char *i; // ebx
  signed int j; // ecx
  __int16 boxHeight; // cx
  unsigned __int16 boxLeft; // si
  unsigned __int16 boxRight; // bx
  unsigned __int16 boxBottom; // bp
  unsigned __int16 boxTop; // di
  int clampedX0; // [esp+8h] [ebp-10h]

  clampedX0 = x0;
  clampedY0 = y0;
  clampedY1 = y1;
  if ( x0 < 0 )
    clampedX0 = 0;
  if ( y0 < 0 )
    clampedY0 = 0;
  mapWidth = *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET);
  if ( x1 >= mapWidth )
    x1 = mapWidth - 1;
  mapHeight = *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET);
  if ( y1 >= mapHeight )
    clampedY1 = mapHeight - 1;
  result = PLAYER_DATA_STRIDE * VIEWED_PLAYER_INDEX;
  if ( PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX) )
  {
    for ( i = (char *)(uintptr_t)clampedX0; (int)(intptr_t)i <= x1; ++i )
    {
      for ( j = clampedY0; j <= clampedY1; ++j )
        MiniMap_DrawTileCell(i, j);
    }
    boxHeight = (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)clampedY1 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 - 1;
    boxLeft = g_MiniMapRectLeft_523344 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)clampedX0 + 7;
    boxRight = g_MiniMapRectLeft_523344 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)x1 - 1 + 7;
    boxBottom = g_MiniMapRectTop_523346 + boxHeight + 7;
    boxTop = g_MiniMapRectTop_523346 + (unsigned __int8)g_MiniMapPixelsPerTile_523F54 * (_WORD)clampedY0 + 7;
    g_RenderDevice = &g_MainRenderDevice;
    MiniMap_BlitDirtyRectAndDrawViewportBox(boxLeft, boxTop, boxBottom, boxRight);
    return Render_FillRect(g_RenderDevice, 0, boxTop, boxLeft, boxRight, boxBottom, boxLeft, boxTop);
  }
  return result;
}
// 40D747: variable 'j' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523F54: using guessed type char byte_523F54;

//----- (0040D800) --------------------------------------------------------
BOOL  MiniMap_IsSpanWithinViewportBounds(unsigned __int16 left, unsigned __int16 bottom)
{
  return PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX)
      && left >= (unsigned __int16)g_MiniMapRectLeft_523344
      && bottom <= (unsigned __int16)g_MiniMapRectHeight_52334A + (unsigned __int16)g_MiniMapRectTop_523346;
}
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 52334A: using guessed type __int16 word_52334A;

//----- (0040D850) --------------------------------------------------------
void MiniMap_RedrawAllTiles()
{
  char *tileX; // ebx
  signed int i; // ecx

  tileX = 0;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_MiniMapSurface_52334C;
  while ( (int)(intptr_t)tileX < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
  {
    for ( i = 0; i < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET); ++i )
      MiniMap_DrawTileCell(tileX, i);
    ++tileX;
  }
  return;
}
// 40D86A: control flows out of bounds to 40D410

void Locale_DrawInteger(void)
{
  MiniMap_RedrawAllTiles();
}
// 40D88B: variable 'v2' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E4: using guessed type int gameData;
// 52334C: using guessed type int dword_52334C;

//----- (0040D890) --------------------------------------------------------
void * MiniMap_DrawTileCell(void *result, signed int tileColumn)
{
  int row; // esi
  int column; // ecx
  unsigned __int16 *terrain_tile; // eax
  unsigned int tile_index; // eax
  int stack_record; // eax
  void *previous_render_device; // [esp+8h] [ebp-14h]
  unsigned __int8 color; // [esp+Ch] [ebp-10h]
  unsigned int scale;
  _DWORD *surface;

  row = (int)(intptr_t)result;
  column = tileColumn;
  if ( row < 0 || row >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) || column < 0 || column >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    return result;

  previous_render_device = g_RenderDevice;
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)(unsigned int)g_MiniMapSurface_52334C;
  color = 0xCFu;
  if ( (g_MiniMapDrawMask_511FF0 & 1) != 0 )
  {
    terrain_tile = TILE_TERRAIN_RECORD(row, column);
    if ( terrain_tile[2] == 0xFFFF )
      color = *(_BYTE *)((uintptr_t)(unsigned int)g_MiniMapTerrainColorTable_523F50 + *terrain_tile);
  }
  if ( (g_MiniMapDrawMask_511FF0 & 2) != 0 )
  {
    tile_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(row, column));
    if ( tile_index <= 0x1F4u
      && (unsigned int)*(__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * tile_index + 6) <= 0x28 )
    {
      stack_record = gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * tile_index;
      if ( !*(_BYTE *)(uintptr_t)(stack_record + 720) )
        color = g_MiniMapBuildingOwnerColorTable[*(unsigned __int8 *)(uintptr_t)(stack_record + 4)];
    }
  }
  if ( (g_MiniMapDrawMask_511FF0 & 4) != 0 )
  {
    tile_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(row, column));
    if ( tile_index >= 0x8000 && tile_index != 0xFFFF )
      color = g_MiniMapBuildingOwnerColorTable[*(unsigned __int8 *)(uintptr_t)(gameData + BUILDING_TABLE_OFFSET + BUILDING_RECORD_SIZE * (tile_index - TILE_OCCUPANT_BUILDING_INDEX_BASE) + 2)];
  }
  if ( !Map_IsTileVisibleToPlayer(row, column, *(_DWORD *)(uintptr_t)(gameData + VIEWED_PLAYER_INDEX_OFFSET)) )
    color = 1;

  surface = (_DWORD *)(uintptr_t)(unsigned int)g_MiniMapSurface_52334C;
  scale = (unsigned __int8)g_MiniMapPixelsPerTile_523F54;
  if ( scale == 1 )
  {
    RenderSurface_WriteSoftwarePixel(surface, row + 7, column + 7, color);
  }
  else
  {
    RenderSurface_FillSoftwareRect(
      surface,
      scale * row + 7,
      scale * column + 7,
      scale * (row + 1) + 6,
      scale * (column + 1) + 6,
      color);
  }
  result = previous_render_device;
  g_RenderDevice = previous_render_device;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 52334C: using guessed type int dword_52334C;
// 523F50: using guessed type int dword_523F50;
// 523F54: using guessed type char byte_523F54;

//----- (0040DB80) --------------------------------------------------------
signed int  Map_GetTileSurfaceClassOrUnexplored(int tileX, signed int tileY)
{
  unsigned __int16 *terrainRecord; // eax
  int surfaceClass; // edi

  terrainRecord = (unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * tileX + TILE_TERRAIN_RECORD_STRIDE * tileY);
  if ( terrainRecord[2] == 0xFFFF )
    surfaceClass = (unsigned __int8)g_MiniMapTileColorTableTheme0[*terrainRecord];
  else
    surfaceClass = 207;
  if ( Map_IsTileVisibleToPlayer(tileX, tileY, g_CurrentPlayerIndex) )
    return surfaceClass;
  else
    return 1;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DC10) --------------------------------------------------------
int MiniMap_UpdateViewportFromCursor(void)
{
  int result; // eax
  int tileX; // ebx
  int maxViewLeft; // esi
  int maxViewTop; // edx
  int cursor_x;
  int cursor_y;
  int is_flipping;
  int allow_scripted_update;
  int trace_minimap;
  int trace_minimap_verbose;
  int trace_cursor_on_minimap;

  result = DD_IsFlipping((int)(intptr_t)g_RenderState);
  allow_scripted_update = !result && getenv("CLASH95_ALLOW_MINIMAP_UPDATE_OFF_FLIP");
  if ( result || allow_scripted_update )
  {
    is_flipping = result;
    cursor_x = g_MouseCursorRawX >> g_CursorCoordShift;
    cursor_y = g_MouseCursorRawY >> g_CursorCoordShift;
    trace_minimap = getenv("CLASH95_TRACE_MINIMAP_CLICK") != 0;
    trace_minimap_verbose = getenv("CLASH95_TRACE_MINIMAP_VERBOSE") != 0;
    trace_cursor_on_minimap = cursor_x >= g_MiniMapRectLeft_523344
                           && cursor_x <= g_MiniMapRectLeft_523344 + 220
                           && cursor_y >= g_MiniMapRectTop_523346
                           && cursor_y <= g_MiniMapRectTop_523346 + 220;
    if ( trace_minimap_verbose && trace_cursor_on_minimap )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "minimap_sample",
        g_SelectedUnitIndex,
        g_MiniMapRectLeft_523344,
        g_MiniMapRectTop_523346,
        (unsigned __int8)g_MiniMapPixelsPerTile_523F54);
      Diagnostics_TraceWorldMapActionEvent(
        "minimap_cursor",
        g_SelectedUnitIndex,
        cursor_x,
        cursor_y,
        PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX));
    }
    result = PLAYER_DATA_STRIDE * VIEWED_PLAYER_INDEX;
    if ( PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX) )
    {
      tileX = (cursor_x - (unsigned __int16)g_MiniMapRectLeft_523344 - 7) / (unsigned __int8)g_MiniMapPixelsPerTile_523F54;
      result = (cursor_y - (unsigned __int16)g_MiniMapRectTop_523346 - 7) / (unsigned __int8)g_MiniMapPixelsPerTile_523F54;
      if ( trace_minimap_verbose && trace_cursor_on_minimap )
      {
        Diagnostics_TraceWorldMapActionEvent(
          "minimap_calc",
          g_SelectedUnitIndex,
          tileX,
          result,
          *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET));
      }
      if ( tileX >= 0
        && result >= 0
        && (tileX != *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) || result != *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET))
        && result <= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
      {
        maxViewLeft = *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) - 9;
        if ( tileX <= maxViewLeft )
          *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = tileX;
        else
          *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET) = maxViewLeft;
        *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = result;
        maxViewTop = *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) - 7;
        if ( maxViewTop < *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) )
          *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET) = maxViewTop;
        if ( trace_minimap )
        {
          Diagnostics_TraceWorldMapActionEvent(
            "minimap_update",
            g_SelectedUnitIndex,
            *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET),
            *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET),
            is_flipping);
        }
        return WorldMap_RedrawViewport(1);
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523F54: using guessed type char byte_523F54;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040DD30) --------------------------------------------------------
int MiniMap_ToggleVisibility(void)
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) ^= 1u;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DD60) --------------------------------------------------------
BOOL MiniMap_IsCursorInside(void)
{
  if ( !PLAYER_MINIMAP_VISIBLE(VIEWED_PLAYER_INDEX) )
    return 0;
  return g_MouseCursorRawX >> g_CursorCoordShift > (unsigned __int16)g_MiniMapRectLeft_523344
      && g_MouseCursorRawX >> g_CursorCoordShift < (unsigned __int16)g_MiniMapRectWidth_523348 + (unsigned __int16)g_MiniMapRectLeft_523344
      && g_MouseCursorRawY >> g_CursorCoordShift > (unsigned __int16)g_MiniMapRectTop_523346
      && g_MouseCursorRawY >> g_CursorCoordShift < (unsigned __int16)g_MiniMapRectHeight_52334A + (unsigned __int16)g_MiniMapRectTop_523346;
}
// 5202E4: using guessed type int gameData;
// 523344: using guessed type __int16 word_523344;
// 523346: using guessed type __int16 word_523346;
// 523348: using guessed type __int16 word_523348;
// 52334A: using guessed type __int16 word_52334A;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040DDE0) --------------------------------------------------------
int MiniMap_ShowAllLayers(void)
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 1;
  g_MiniMapDrawMask_511FF0 = 7;
  Locale_DrawInteger();
  return WorldMap_RedrawViewport(1);
}
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DE20) --------------------------------------------------------
int MiniMap_ShowUnitsOnly(void)
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 1;
  g_MiniMapDrawMask_511FF0 = 2;
  Locale_DrawInteger();
  return WorldMap_RedrawViewport(1);
}
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DE60) --------------------------------------------------------
int MiniMap_ShowBuildingsOnly(void)
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 1;
  g_MiniMapDrawMask_511FF0 = 4;
  Locale_DrawInteger();
  return WorldMap_RedrawViewport(1);
}
// 511FF0: using guessed type int dword_511FF0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DEA0) --------------------------------------------------------
int MiniMap_Hide(void)
{
  PLAYER_MINIMAP_VISIBLE(g_CurrentPlayerIndex) = 0;
  return WorldMap_RedrawViewport(1);
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0040DED0) --------------------------------------------------------
signed int  UI_MenuHitTestEntry(_WORD *menu)
{
  int centerOffset; // edi
  _WORD *measureEntryPtr; // esi
  int i; // ebx
  _WORD *hitEntryPtr; // esi
  int hitIndex; // ebx
  int rowOffset; // edi
  int SpriteHeight; // ebp
  int textWidth; // edx
  int centerGap; // ebp
  int rowTop; // ebp
  int rightX; // [esp+4h] [ebp-2Ch]
  unsigned __int16 topBaseY; // [esp+10h] [ebp-20h]
  unsigned __int16 leftX; // [esp+14h] [ebp-1Ch]

  LOWORD(centerOffset) = -1;
  measureEntryPtr = menu;
  for ( i = 0; i < (unsigned __int16)menu[4]; ++i )
  {
    SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    LOWORD(textWidth) = Render_LoadResourceSprite_v3(*(_BYTE **)&measureEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
    centerGap = SpriteHeight - textWidth;
    if ( (unsigned __int16)(centerGap / 2) < (unsigned __int16)centerOffset )
      centerOffset = centerGap / 2;
    measureEntryPtr += 20;
  }
  hitEntryPtr = menu;
  leftX = centerOffset + *menu;
  hitIndex = 0;
  rowOffset = 0;
  topBaseY = menu[1] + 25;
  while ( 1 )
  {
    if ( hitIndex >= (unsigned __int16)menu[4] )
      return -1;
    rowTop = rowOffset + topBaseY;
    rightX = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)&hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]) + leftX;
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= leftX
      && g_MouseCursorRawY >> g_CursorCoordShift >= rowTop
      && g_MouseCursorRawX >> g_CursorCoordShift <= rightX
      && g_MouseCursorRawY >> g_CursorCoordShift <= rowTop + 22 )
    {
      break;
    }
    hitEntryPtr += 20;
    rowOffset += 22;
    ++hitIndex;
  }
  return hitIndex;
}
// 40DF54: variable 'v9' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 523F5C: using guessed type int dword_523F5C;
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040DFF0) --------------------------------------------------------
int  UI_RunMenu(_WORD *menu, DWORD a2)
{
  int menuTopY; // eax
  int sprite3Height; // eax
  int sprite3Width; // eax
  int panelSpriteWidth; // ebx
  int sprite4Width; // eax
  int v7; // ecx
  _DWORD *Surface; // eax
  __int16 menuTop; // dx
  int SpriteForChar; // eax
  DWORD deviceVTable; // ebp
  int v12; // edi
  int v13; // ecx
  int measureIndex; // esi
  _WORD *measureEntryPtr; // edi
  int v16; // ecx
  int drawIndex; // esi
  _WORD *drawEntryPtr; // edi
  unsigned __int16 *v19; // edx
  __int16 SpriteHeight; // ax
  int v21; // esi
  int v22; // ebx
  int mouseY; // edx
  int mouseX; // ecx
  int i; // eax
  int v26 CLASH95_UNUSED; // edi
  int v27 CLASH95_UNUSED; // esi
  signed int submenuHitIndex; // eax
  _WORD *v29; // ebx
  __int16 v30; // ax
  int renderDeviceMethods; // esi
  _WORD *v32; // ebx
  __int16 v33; // ax
  _WORD *resultEntryPtr; // eax
  int measureTextWidth; // edx
  int v37; // ecx
  int measureGap; // ecx
  char colorIndex; // cl
  DWORD prevHoveredIndex; // ebp
  signed int hitIndex; // esi
  int *colorPrevPtr; // edx
  char prevColorIndex; // al
  int v44; // edi
  __int16 prevTextWidth; // ax
  int entryEnabled; // ecx
  char highlightColorIndex; // al
  unsigned __int16 hitTextX; // di
  int hitEntryY; // ebp
  __int16 hitTextWidth; // ax
  _WORD *hitEntryLangBase; // eax
  _WORD *hitEntry; // eax
  unsigned __int16 menuBottomY; // [esp+3Ch] [ebp-78h]
  unsigned __int16 v54; // [esp+3Ch] [ebp-78h]
  unsigned __int16 v55; // [esp+3Ch] [ebp-78h]
  unsigned __int16 v56; // [esp+3Ch] [ebp-78h]
  int v57; // [esp+40h] [ebp-74h]
  unsigned __int16 menuX; // [esp+40h] [ebp-74h]
  unsigned __int16 v59; // [esp+40h] [ebp-74h]
  int v60; // [esp+40h] [ebp-74h]
  unsigned __int16 menuY; // [esp+44h] [ebp-70h]
  unsigned __int16 v62; // [esp+44h] [ebp-70h]
  int v63; // [esp+48h] [ebp-6Ch]
  int colorActive; // [esp+4Ch] [ebp-68h] BYREF
  int colorInactive; // [esp+50h] [ebp-64h] BYREF
  int colorPrevActive; // [esp+54h] [ebp-60h] BYREF
  int colorPrevInactive; // [esp+58h] [ebp-5Ch] BYREF
  _WORD *prevEntryPtr; // [esp+5Ch] [ebp-58h]
  int colorHighlight; // [esp+60h] [ebp-54h] BYREF
  int hoveredIndex; // [esp+64h] [ebp-50h]
  _WORD *menuPtr; // [esp+68h] [ebp-4Ch]
  _WORD *hitEntryPtr; // [esp+6Ch] [ebp-48h]
  _DWORD *menuSurface; // [esp+70h] [ebp-44h]
  int exitFlag; // [esp+74h] [ebp-40h]
  int centerOffset; // [esp+78h] [ebp-3Ch]
  _WORD *menuLeft; // [esp+7Ch] [ebp-38h]
  char *textX; // [esp+80h] [ebp-34h]
  int textBaseY; // [esp+84h] [ebp-30h]
  int textY; // [esp+88h] [ebp-2Ch]
  char *hoverTextX; // [esp+8Ch] [ebp-28h]
  int entryY; // [esp+90h] [ebp-24h]
  int surfaceWidth; // [esp+94h] [ebp-20h]
  int surfaceHeight; // [esp+98h] [ebp-1Ch]
  const WorldMapTopMenuHitRecord *top_menu_record;

  menuPtr = menu;
  LOWORD(menu) = *menu;
  menuLeft = menu;
  HIWORD(menuTopY) = HIWORD(menuPtr);
  v63 = 0;
  LOWORD(menuTopY) = menuPtr[1];
  textBaseY = menuTopY;
  LOWORD(sprite3Height) = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
  surfaceWidth = sprite3Height + 1;
  LOWORD(sprite3Width) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u);
  panelSpriteWidth = sprite3Width;
  LOWORD(sprite4Width) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u);
  surfaceHeight = panelSpriteWidth + sprite4Width + 1;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v7, panelSpriteWidth, a2);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, surfaceWidth, surfaceHeight);
  menuTop = menuPtr[1];
  menuSurface = Surface;
  Render_FillRect(
    (_DWORD *)(uintptr_t)g_WorldMapTargetSurface,
    Surface,
    (unsigned __int16)menuPtr[1],
    (unsigned __int16)*menuPtr,
    surfaceWidth + *menuPtr - 1,
    surfaceHeight + menuTop - 1,
    0,
    0);
  g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_WorldMapTargetSurface;
  SpriteForChar = DLX_GetSpriteForChar(g_MapPanelSpriteSet, 3);
  deviceVTable = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(deviceVTable + 52))(
    (unsigned __int16)textBaseY,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v12 = *((_DWORD *)g_RenderDevice + 46);
  textBaseY += 25;
  v57 = (unsigned __int16)(textBaseY + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u));
  LOWORD(v13) = (_WORD)(intptr_t)menuLeft + DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
  measureIndex = 0;
  (*(void (__fastcall **)(int, _DWORD, int, _DWORD))(uintptr_t)(v12 + 28))(v13, (unsigned __int16)(intptr_t)menuLeft, v57, 0);
  measureEntryPtr = menuPtr;
  Render_ReleaseSurface(19, deviceVTable);
  centerOffset = v16;
  while ( measureIndex < (unsigned __int16)menuPtr[4] )
  {
    DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    LOWORD(measureTextWidth) = Render_LoadResourceSprite_v3(*(_BYTE **)&measureEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
    measureGap = v37 - measureTextWidth;
    if ( (unsigned __int16)(measureGap / 2) < (unsigned __int16)centerOffset )
      centerOffset = measureGap / 2;
    measureEntryPtr += 20;
    ++measureIndex;
  }
  drawIndex = 0;
  textX = (char *)menuLeft + centerOffset;
  drawEntryPtr = menuPtr;
  textY = textBaseY;
  while ( drawIndex < (unsigned __int16)menuPtr[4] )
  {
    if ( *(_DWORD *)(drawEntryPtr + 13) )
    {
      colorActive = 0xFFFFFF;
      colorIndex = Render_ApplyColorTripletBytes((int)(intptr_t)&g_RenderEnvPaletteContext, (unsigned __int8 *)&colorActive);
    }
    else
    {
      colorInactive = 10395294;
      colorIndex = Render_ApplyColorTripletBytes((int)(intptr_t)&g_RenderEnvPaletteContext, (unsigned __int8 *)&colorInactive);
    }
    TextSprite_SetStyleFlag(colorIndex);
    TextSprite_DrawStringWithOrientation(
      (unsigned __int16)(intptr_t)textX,
      (unsigned __int16)textY,
      0,
      *(unsigned __int8 **)&drawEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
    drawEntryPtr += 20;
    ++drawIndex;
    textY += 22;
  }
  DLX_GetSpriteForChar(g_MapPanelSpriteSet, 4);
  (*(void (__stdcall **)(int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v19 = menuPtr;
  Render_Pump();
  menuY = v19[1];
  menuX = *v19;
  v22 = (int)(intptr_t)menuPtr;
  LOWORD(v22) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u) + *(_WORD *)(uintptr_t)(v22 + 2);
  menuBottomY = v22 + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u);
  SpriteHeight = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
  v21 = centerOffset;
  Render_BlitSurfaceRect(
    (_DWORD *)(uintptr_t)g_WorldMapTargetSurface,
    0,
    (unsigned __int16)menuPtr[1],
    (unsigned __int16)*menuPtr,
    *menuPtr + SpriteHeight,
    menuBottomY,
    menuX,
    menuY);
  LOBYTE(v22) = -1;
  Render_Present((int)(intptr_t)g_RenderState);
  exitFlag = 0;
  hoveredIndex = -1;
  hoverTextX = (char *)menuLeft + v21;
  while ( DD_IsFlipping((int)(intptr_t)g_RenderState) && !exitFlag )
  {
    DD_Pump((int)(intptr_t)g_RenderState, v22);
    mouseY = g_MouseCursorRawY >> g_CursorCoordShift;
    mouseX = g_MouseCursorRawX >> g_CursorCoordShift;
    for ( i = 0; i < WORLD_MAP_TOP_MENU_HIT_RECORD_COUNT; ++i )
    {
      top_menu_record = &g_WorldMapTopMenuHitRecords[i];
      if ( menuPtr != top_menu_record->menu )
      {
        if ( mouseX >= (unsigned __int16)top_menu_record->left
          && mouseY >= (unsigned __int16)top_menu_record->top
          && mouseX <= (unsigned __int16)top_menu_record->right
          && mouseY <= (unsigned __int16)top_menu_record->bottom )
        {
          exitFlag = 1;
        }
      }
    }
    if ( *((_DWORD *)menuPtr + 1) )
    {
      submenuHitIndex = UI_MenuHitTestEntry(*((_WORD **)menuPtr + 1));
      if ( submenuHitIndex != -1 && menuPtr != *(_WORD **)(uintptr_t)(*((_DWORD *)menuPtr + 1) + 40 * submenuHitIndex + 30) )
        break;
    }
    prevHoveredIndex = hoveredIndex;
    hitIndex = UI_MenuHitTestEntry(menuPtr);
    if ( hitIndex != prevHoveredIndex )
    {
      Render_Pump();
      if ( prevHoveredIndex != -1 )
      {
        if ( *(_DWORD *)&menuPtr[20 * prevHoveredIndex + 13] )
        {
          colorPrevPtr = &colorPrevActive;
          colorPrevActive = 0xFFFFFF;
        }
        else
        {
          colorPrevPtr = &colorPrevInactive;
          colorPrevInactive = 10395294;
        }
        prevColorIndex = Render_ApplyColorTripletBytes((int)(intptr_t)&g_RenderEnvPaletteContext, (unsigned __int8 *)colorPrevPtr);
        v44 = hoveredIndex;
        TextSprite_SetStyleFlag(prevColorIndex);
        prevEntryPtr = &menuPtr[20 * v44];
        LOWORD(v44) = (_WORD)(intptr_t)hoverTextX;
        v22 = *(_DWORD *)&prevEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5];
        entryY = 22 * hoveredIndex + textBaseY;
        prevHoveredIndex = (unsigned __int16)entryY;
        TextSprite_DrawStringWithOrientation((unsigned __int16)(intptr_t)hoverTextX, (unsigned __int16)entryY, 0, (unsigned __int8 *)(uintptr_t)v22);
        v55 = entryY + 22;
        prevTextWidth = Render_LoadResourceSprite_v3(*(_BYTE **)&prevEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
        LOBYTE(v22) = v44;
        Render_FillRect((_DWORD *)(uintptr_t)g_WorldMapTargetSurface, 0, prevHoveredIndex, (unsigned __int16)v44, v44 + prevTextWidth, v55, v44, prevHoveredIndex);
      }
      if ( hitIndex == -1 )
        goto LABEL_52;
      entryEnabled = *(_DWORD *)&menuPtr[20 * hitIndex + 13];
      hitEntryPtr = &menuPtr[20 * hitIndex];
      if ( !entryEnabled )
        goto LABEL_52;
      colorHighlight = 3342130;
      highlightColorIndex = Render_ApplyColorTripletBytes((int)(intptr_t)&g_RenderEnvPaletteContext, (unsigned __int8 *)&colorHighlight);
      TextSprite_SetStyleFlag(highlightColorIndex);
      v22 = *(_DWORD *)&hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5];
      hitTextX = (unsigned __int16)(intptr_t)hoverTextX;
      entryY = 22 * hitIndex + textBaseY;
      hitEntryY = (unsigned __int16)entryY;
      TextSprite_DrawStringWithOrientation((unsigned __int16)(intptr_t)hoverTextX, (unsigned __int16)entryY, 0, (unsigned __int8 *)(uintptr_t)v22);
      v56 = entryY + 22;
      hitTextWidth = Render_LoadResourceSprite_v3(*(_BYTE **)&hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex + 5]);
      LOBYTE(v22) = hitTextX;
      Render_FillRect((_DWORD *)(uintptr_t)g_WorldMapTargetSurface, 0, hitEntryY, hitTextX, hitTextX + hitTextWidth, v56, hitTextX, hitEntryY);
      hitEntryLangBase = &hitEntryPtr[2 * (unsigned __int8)g_LanguageIndex];
      prevHoveredIndex = *(_DWORD *)(hitEntryLangBase + 19);
      if ( prevHoveredIndex )
        Tooltip_ShowText(3, *(char **)(hitEntryLangBase + 19), v63);
      else
LABEL_52:
        Tooltip_RestoreBackdrop();
      hoveredIndex = hitIndex;
      Render_Present((int)(intptr_t)g_RenderState);
      if ( hitIndex != -1 )
      {
        hitEntry = &menuPtr[20 * hitIndex];
        v22 = *(_DWORD *)(hitEntry + 15);
        if ( v22 )
        {
          if ( *(_DWORD *)(hitEntry + 13) )
          {
            v63 = UI_RunMenu(*(_DWORD *)(hitEntry + 15), prevHoveredIndex);
            if ( v63 )
              hoveredIndex = -1;
          }
        }
      }
    }
  }
  Render_Pump();
  if ( g_WorldMapTargetSurface != g_PrimaryRenderSurface )
  {
    v62 = menuPtr[1];
    v59 = *menuPtr;
    v29 = menuPtr;
    LOWORD(v29) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u) + v29[1];
    v54 = (_WORD)(intptr_t)v29 + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u);
    v30 = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    Render_FillRect(
      (_DWORD *)(uintptr_t)g_PrimaryRenderSurface,
      0,
      (unsigned __int16)menuPtr[1],
      (unsigned __int16)*menuPtr,
      *menuPtr + v30,
      v54,
      v59,
      v62);
  }
  Render_BlitSurfaceRect(menuSurface, 0, 0, 0, surfaceWidth - 1, surfaceHeight - 1, *menuPtr, menuPtr[1]);
  Render_Present((int)(intptr_t)g_RenderState);
  if ( g_WorldMapTargetSurface != g_PrimaryRenderSurface )
  {
    renderDeviceMethods = *((_DWORD *)g_RenderDevice + 46);
    v32 = menuPtr;
    LOWORD(v32) = DLX_GetSpriteWidth(g_MapPanelSpriteSet, 3u) + v32[1];
    v60 = (unsigned __int16)((_WORD)(intptr_t)v32 + DLX_GetSpriteWidth(g_MapPanelSpriteSet, 4u));
    v33 = DLX_GetSpriteHeight(g_MapPanelSpriteSet, 3u);
    (*(void (__fastcall **)(_DWORD, _DWORD, int, _DWORD))(uintptr_t)(renderDeviceMethods + 28))(
      (unsigned __int16)(*menuPtr + v33),
      (unsigned __int16)*menuPtr,
      v60,
      0);
  }
  Render_BlitSurfaceRect(menuSurface, (_DWORD *)(uintptr_t)g_WorldMapTargetSurface, 0, 0, surfaceWidth - 1, surfaceHeight - 1, *menuPtr, menuPtr[1]);
  if ( menuSurface )
    (*(void (**)(void))(uintptr_t)menuSurface[46])();
  if ( hoveredIndex != -1 && (resultEntryPtr = &menuPtr[20 * hoveredIndex], *(_DWORD *)(resultEntryPtr + 13)) )
    return *(_DWORD *)(resultEntryPtr + 17);
  else
    return v63;
}
// 40E02A: variable 'v3' is possibly undefined
// 40E03D: variable 'v4' is possibly undefined
// 40E049: variable 'v6' is possibly undefined
// 40E055: variable 'v7' is possibly undefined
// 40E160: variable 'v13' is possibly undefined
// 40E176: variable 'v16' is possibly undefined
// 40E53B: variable 'v63' is possibly undefined
// 40E586: variable 'v37' is possibly undefined
// 40E586: variable 'v36' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512348: using guessed type __int16 word_512348[];
// 51234A: using guessed type __int16 word_51234A[];
// 51234C: using guessed type __int16 word_51234C[];
// 51234E: using guessed type __int16 word_51234E[];
// 512350: using guessed type void *off_512350;
// 5202E0: using guessed type int dword_5202E0;
// 523F5C: using guessed type int dword_523F5C;
// 523F60: using guessed type int dword_523F60;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0040E8B0) --------------------------------------------------------
BOOL  WorldMap_HandleTopMenuBar(char a1, int a2)
{
  _DWORD *surface; // eax
  int menu_sprite; // edx
  int mission_index; // edx
  int mouse_x; // ebx
  int mouse_y; // eax
  int i; // edx
  int close_button_left; // ebx
  int previous_screen_handle; // [esp+1Ch] [ebp-28h]
  int should_hide_menu; // [esp+20h] [ebp-24h]
  void (*menu_callback)(void); // [esp+24h] [ebp-20h]
  int previous_resource_handle; // [esp+28h] [ebp-1Ch]
  int (*previous_render_hook)(); // [esp+2Ch] [ebp-18h]
  const WorldMapTopMenuHitRecord *top_menu_record;

  if ( g_MouseCursorRawX >> g_CursorCoordShift < 0
    || g_MouseCursorRawY >> g_CursorCoordShift < 0
    || g_MouseCursorRawX >> g_CursorCoordShift > 640
    || g_MouseCursorRawY >> g_CursorCoordShift > 5
    || DD_IsFlipping((int)(intptr_t)g_RenderState) )
  {
    return 1;
  }
  Diagnostics_TraceWorldMapActionEvent("top_menu_enter", g_SelectedUnitIndex, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift, 0);
  Debug_Log(0, a1, a2, (int)(intptr_t)aMenuDraw);
  Render_Pump();
  previous_screen_handle = g_ActiveCursorDescriptorPtr;
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  Render_FillRect(0, (_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 0, SCREEN_MAX_X, 0x18Fu, 0, 0);
  Render_Present((int)(intptr_t)g_RenderState);
  surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 0, 0, a2);
  if ( surface )
    surface = Render_CreateSurface((int)(intptr_t)surface, SCREEN_WIDTH, 400);
  g_WorldMapTargetSurface = (int)(intptr_t)surface;
  g_RenderDevice = surface;
  RenderSurface_InvokeSlot56(surface);
  menu_sprite = DLX_GetSpriteForChar(g_MapPanelSpriteSet, (unsigned __int8)g_LanguageIndex % 3);
  /*
   * Original sub_40E8B0 (clash95.asm 21690-21706): straight after
   * DLX_GetSpriteForChar the localized top-menu-bar panel is blitted through
   * render-device slot +52:
   *   mov esi, ds:g_RenderDevice / mov ebx, 20h / mov edi,[esi+0B8h]
   *   mov edx, eax / mov eax, esi / call dword ptr [edi+34h]
   * with ecx = 0, i.e. x = 0x20, y = 0 and stack args 0,0,1,-1,-1,-1,-1
   * (draw_mode 1, the same idiom as every other converted +52 caller).
   * The raw decompile discarded the sprite handle and never drew the panel.
   */
  Compat_RenderDeviceDrawMenuSprite(0x20, 0, menu_sprite, 1);
  Render_ReleaseSurface(2, 0);
  TextSprite_SetStyleFlag(76);
  mission_index = ACTIVE_MISSION_INDEX;
  if ( mission_index == 3 || mission_index == 13 )
    UI_DrawTextFmt(0, 585, 11, 0, 2, (const char *)aDD, GAME_TURN_COUNTER, 10);
  else if ( mission_index == 4 || mission_index == 14 )
    UI_DrawTextFmt(0, 585, 11, 0, 2, (const char *)aDD, GAME_TURN_COUNTER, 20);
  else
    UI_DrawTextFmt(0, 570, 11, 0, 2, (const char *)aD, GAME_TURN_COUNTER);
  Render_Pump();
  /*
   * Original sub_40E8B0 loc_40EA33 (clash95.asm 21744-21760): between
   * Render_Pump and Render_Present the composed 640x36 menu strip is copied
   * from the offscreen menu surface to the visible surface:
   *   push 0 / push 0 / push 23h / xor ecx,ecx / xor ebx,ebx / push 27Fh
   *   xor edx,edx / mov eax, ds:dword_523F60 / call sub_402850
   * i.e. Render_BlitSurfaceRect(g_WorldMapTargetSurface, 0, 0, 0, 0x27F,
   * 0x23, 0, 0).  The raw decompile omitted the blit entirely.
   */
  Render_BlitSurfaceRect((_DWORD *)(uintptr_t)g_WorldMapTargetSurface, 0, 0, 0, 0x27Fu, 0x23u, 0, 0);
  Render_Present((int)(intptr_t)g_RenderState);
  should_hide_menu = 0;
  menu_callback = 0;
  while ( g_MouseCursorRawX >> g_CursorCoordShift >= 0
       && g_MouseCursorRawY >> g_CursorCoordShift >= 0
       && g_MouseCursorRawX >> g_CursorCoordShift <= 640
       && g_MouseCursorRawY >> g_CursorCoordShift <= 25 )
  {
    WorldMap_RunInputScriptStep();
    DD_Pump((int)(intptr_t)g_RenderState, 0);
    for ( i = 0; i < WORLD_MAP_TOP_MENU_HIT_RECORD_COUNT; ++i )
    {
      top_menu_record = &g_WorldMapTopMenuHitRecords[i];
      mouse_x = g_MouseCursorRawX >> g_CursorCoordShift;
      if ( mouse_x >= (unsigned __int16)top_menu_record->left )
      {
        mouse_y = g_MouseCursorRawY >> g_CursorCoordShift;
        if ( mouse_y >= (unsigned __int16)top_menu_record->top
          && mouse_x <= (unsigned __int16)top_menu_record->right
          && mouse_y <= (unsigned __int16)top_menu_record->bottom
          && DD_IsFlipping((int)(intptr_t)g_RenderState) )
        {
          menu_callback = (void (*)(void))(uintptr_t)UI_RunMenu(
                                         top_menu_record->menu,
                                         (unsigned __int16)top_menu_record->bottom);
        }
      }
    }
    if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
    {
      close_button_left = g_LanguageIndex == 2 ? 430 : 470;
      if ( g_MouseCursorRawX >> g_CursorCoordShift >= close_button_left
        && g_MouseCursorRawY >> g_CursorCoordShift >= 0
        && g_MouseCursorRawX >> g_CursorCoordShift <= 590
        && g_MouseCursorRawY >> g_CursorCoordShift <= 25 )
      {
        Render_Begin((int)(intptr_t)g_RenderState, 0);
        should_hide_menu = 1;
        Diagnostics_TraceWorldMapActionEvent("top_menu_close", g_SelectedUnitIndex, close_button_left, g_MouseCursorRawX >> g_CursorCoordShift, g_MouseCursorRawY >> g_CursorCoordShift);
        break;
      }
    }
  }
  surface = (_DWORD *)(uintptr_t)g_WorldMapTargetSurface;
  if ( surface )
    RenderSurface_InvokeSlot0(surface, 2);
  Render_Pump();
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, 0, 0, SCREEN_MAX_X, 0x18Fu, 0, 0);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, previous_screen_handle);
  Render_Present((int)(intptr_t)g_RenderState);
  previous_resource_handle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  previous_render_hook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)(intptr_t)Render_DefaultRH, 0, a2, (int)(intptr_t)aSetrhS08x_2, aStdrh_3, Render_DefaultRH);
  if ( menu_callback )
    menu_callback();
  Debug_Log((int)(intptr_t)g_RenderHook, 0, a2, (int)(intptr_t)aUnsetrh08x_2, g_RenderHook);
  g_RenderHook = previous_render_hook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, previous_resource_handle);
  Debug_Log(0, 0, a2, (int)(intptr_t)aMenuHide);
  Diagnostics_TraceWorldMapActionEvent("top_menu_return", g_SelectedUnitIndex, should_hide_menu, menu_callback != 0, 0);
  return !should_hide_menu;
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512348: using guessed type __int16 word_512348[];
// 51234A: using guessed type __int16 word_51234A[];
// 51234C: using guessed type __int16 word_51234C[];
// 51234E: using guessed type __int16 word_51234E[];
// 512350: using guessed type void *off_512350;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 523F5C: using guessed type int dword_523F5C;
// 523F60: using guessed type int dword_523F60;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (0040ECF0) --------------------------------------------------------
_DWORD * WorldMapTopMenu_LoadSpriteSet(void)
{
  _DWORD *result; // eax

  result = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, 0);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, "menu.s32");
    g_MapPanelSpriteSet = (int)(intptr_t)result;
  }
  else
  {
    g_MapPanelSpriteSet = 0;
  }
  return result;
}
// 512000: using guessed type char *off_512000;
// 523F5C: using guessed type int dword_523F5C;

//----- (0040ED20) --------------------------------------------------------
int WorldMapTopMenu_FreeSpriteSet(void)
{
  return DLXSpriteSet_ReleaseAndClear(&g_MapPanelSpriteSet);
}
// 523F5C: using guessed type int dword_523F5C;

//----- (0040ED30) --------------------------------------------------------
int  UI_MenuEntry_Enable(int menuBase, int entryIndex)
{
  int result; // eax

  result = entryIndex;
  *(_DWORD *)(uintptr_t)(menuBase + 40 * entryIndex + 26) = 1;
  return result;
}

//----- (0040ED50) --------------------------------------------------------
int  UI_MenuEntry_Disable(int menuBase, int entryIndex)
{
  int result; // eax

  result = entryIndex;
  *(_DWORD *)(uintptr_t)(menuBase + 40 * entryIndex + 26) = 0;
  return result;
}

//----- (0040ED70) --------------------------------------------------------
void  Map_RevealAllTilesForPlayer(int playerIndex)
{
  int rowOffset; // ebp
  int playerBase; // edi
  int i; // ebx
  int byteAddr; // eax
  char maskedByte; // dl

  rowOffset = 0;
  playerBase = PLAYER_DATA_STRIDE * playerIndex;
  do
  {
    for ( i = 0; i < 100; ++i )
    {
      byteAddr = playerBase + gameData + rowOffset + ((i - (__CFSHL__(i >> 31, 3) + 8 * (i >> 31))) >> 3);
      maskedByte = (1 << (i & 7)) | *(_BYTE *)(uintptr_t)(byteAddr + PLAYER_RUNTIME_STATE_OFFSET + PLAYER_REVEALED_TILES_OFFSET);
      *(_BYTE *)(uintptr_t)(byteAddr + PLAYER_RUNTIME_STATE_OFFSET + PLAYER_REVEALED_TILES_OFFSET) = maskedByte;
    }
    rowOffset += 13;
  }
  while ( rowOffset != 1300 );
  Locale_DrawInteger();
}
// 5202E4: using guessed type int gameData;

//----- (0040EDE0) --------------------------------------------------------
signed int  Map_RevealTileWithPropagation(int tileX, signed int tileY, int playerIndex)
{
  int revealByteAddr; // eax
  int leftTileX; // ecx
  int rightTileX; // ecx
  signed int upTileY; // ecx
  signed int downTileY; // ecx
  int diagLeftTileX; // ecx
  int diagRightTileX; // ecx
  signed int diagDownTileY; // ecx
  int diagRightTileX2; // edi
  signed int diagDownTileY2; // ecx

  if ( tileX < 0
    || tileY < 0
    || tileX >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
    || tileY >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
    || Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
  {
    return 0;
  }
  revealByteAddr = PLAYER_DATA(playerIndex) + PLAYER_REVEALED_TILE_ROW_BYTES * tileX + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3);
  *(_BYTE *)(uintptr_t)(revealByteAddr + PLAYER_REVEALED_TILES_OFFSET) |= 1 << (tileY & 7);
  MiniMap_DrawTileCell((void *)(uintptr_t)tileX, tileY);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex) )
    Map_RevealTileWithPropagation(leftTileX, tileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY, playerIndex) && !Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex) )
    Map_RevealTileWithPropagation(rightTileX, tileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX, upTileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX, tileY + 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX, tileY + 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX, downTileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(diagLeftTileX, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY - 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex) )
    Map_RevealTileWithPropagation(diagRightTileX, tileY - 1, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX - 2, tileY + 2, playerIndex) && !Map_IsTileVisibleToPlayer(tileX - 1, tileY + 1, playerIndex) )
    Map_RevealTileWithPropagation(tileX - 1, diagDownTileY, playerIndex);
  if ( Map_IsTileVisibleToPlayer(tileX + 2, tileY + 2, playerIndex) )
  {
    diagRightTileX2 = tileX + 1;
    if ( !Map_IsTileVisibleToPlayer(diagRightTileX2, tileY + 1, playerIndex) )
      Map_RevealTileWithPropagation(diagRightTileX2, diagDownTileY2, playerIndex);
  }
  return 1;
}
// 40EFE9: variable 'v6' is possibly undefined
// 40EFFB: variable 'v7' is possibly undefined
// 40F00B: variable 'v8' is possibly undefined
// 40F01B: variable 'v9' is possibly undefined
// 40F02B: variable 'v10' is possibly undefined
// 40F03B: variable 'v11' is possibly undefined
// 40F04B: variable 'v12' is possibly undefined
// 40EFCF: variable 'v14' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0040F060) --------------------------------------------------------
BOOL  Map_IsTileVisibleToPlayer(int tileX, signed int tileY, int playerIndex)
{
  return tileX >= 0
      && tileY >= 0
      && tileX < *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET)
      && tileY < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && ((1 << (tileY & 7)) & *(unsigned __int8 *)(uintptr_t)(PLAYER_DATA(playerIndex)
                                               + PLAYER_REVEALED_TILE_ROW_BYTES * tileX
                                               + ((tileY - (__CFSHL__(tileY >> 31, 3) + 8 * (tileY >> 31))) >> 3)
                                               + PLAYER_REVEALED_TILES_OFFSET)) != 0;
}
// 5202E4: using guessed type int gameData;

//----- (0040F0C0) --------------------------------------------------------
signed int  Map_ClassifyFogOfWarOverlayForPlayer(int tileX, signed int tileY, int playerIndex)
{
  signed int tileYBelow; // ebp
  bool belowRightVisible; // al
  char neighborAccum; // cl
  char neighborMask; // si
  char neighborMaskFull; // cl

  if ( Map_IsTileVisibleToPlayer(tileX, tileY, playerIndex) )
    return -1;
  Map_IsTileVisibleToPlayer(tileX - 1, tileY - 1, playerIndex);
  Map_IsTileVisibleToPlayer(tileX, tileY - 1, playerIndex);
  Map_IsTileVisibleToPlayer(tileX + 1, tileY - 1, playerIndex);
  Map_IsTileVisibleToPlayer(tileX - 1, tileY, playerIndex);
  Map_IsTileVisibleToPlayer(tileX + 1, tileY, playerIndex);
  tileYBelow = tileY + 1;
  Map_IsTileVisibleToPlayer(tileX - 1, tileYBelow, playerIndex);
  Map_IsTileVisibleToPlayer(tileX, tileYBelow, playerIndex);
  belowRightVisible = Map_IsTileVisibleToPlayer(tileX + 1, tileYBelow, playerIndex);
  neighborMask = belowRightVisible | neighborAccum & 0xFE;
  if ( !neighborMask )
    return 0;
  TextSprite_SetStyleFlag(1);
  if ( (~neighborMask & 0x5A) == 0x5A && (neighborMaskFull & 1) == 1 )
    return 12;
  if ( (~neighborMaskFull & 0x5A) == 0x5A && neighborMaskFull < 0 )
    return 9;
  if ( (~neighborMaskFull & 0x5A) == 0x5A && (neighborMaskFull & 4) != 0 )
    return 11;
  if ( (~neighborMaskFull & 0x5A) == 0x5A && (neighborMaskFull & 0x20) != 0 )
    return 10;
  if ( (~neighborMaskFull & 0x58) == 0x58 && (neighborMaskFull & 2) != 0 )
    return 7;
  if ( (~neighborMaskFull & 0x4A) == 0x4A && (neighborMaskFull & 0x10) != 0 )
    return 4;
  if ( (~neighborMaskFull & 0x52) == 0x52 && (neighborMaskFull & 8) != 0 )
    return 5;
  if ( (~neighborMaskFull & 0x1A) == 0x1A && (neighborMaskFull & 0x40) != 0 )
    return 2;
  if ( (~neighborMaskFull & 0xA) == 0xA && (neighborMaskFull & 0x50) == 0x50 )
    return 1;
  if ( (~neighborMaskFull & 0x12) == 0x12 && (neighborMaskFull & 0x48) == 0x48 )
    return 3;
  if ( (~neighborMaskFull & 0x48) == 0x48 && (neighborMaskFull & 0x12) == 0x12 )
    return 6;
  if ( (~neighborMaskFull & 0x50) == 0x50 && (neighborMaskFull & 0xA) == 0xA )
    return 8;
  if ( (neighborMaskFull & 0x18) == 0x18 || (neighborMaskFull & 0x42) == 0x42 )
    return -1;
  if ( (unsigned __int8)neighborMaskFull == 255 )
    return 13;
  else
    return 14;
}
// 40F19C: variable 'v8' is possibly undefined
// 40F1CA: variable 'v10' is possibly undefined

//----- (0040F3C0) --------------------------------------------------------
signed int  UnitStack_IsIndexOnMap(int stackIndex)
{
  int rowBase; // edi
  int tileY; // edx
  int i; // eax
  int tileX; // [esp+0h] [ebp-18h]

  rowBase = 0;
  tileX = 0;
LABEL_2:
  if ( tileX >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
    return 0;
  tileY = 0;
  for ( i = 0; ; i += 2 )
  {
    if ( tileY >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      rowBase += 200;
      ++tileX;
      goto LABEL_2;
    }
    if ( *(unsigned __int16 *)(uintptr_t)(rowBase + gameData + i + TILE_MAP_OFFSET) == stackIndex )
      break;
    ++tileY;
  }
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (0040F440) --------------------------------------------------------
int  UnitSlot_InitFromType(int result, unit_type unitType, char ownerIndex)
{
  char moraleValue; // dl
  char stanceBits; // bh
  char auxFlagsByte; // cl
  char stateBitsByte; // dl
  char flagsByte; // ch

  *(_WORD *)(uintptr_t)(result + 4) = 0;
  *(_WORD *)(uintptr_t)(result + 6) = 0;
  *(_BYTE *)(uintptr_t)(result + 3) = 0;
  *(_DWORD *)(uintptr_t)(result + 23) = 0;
  UNIT_SLOT_TYPE(result) = unitType;
  UNIT_SLOT_OWNER(result) = ownerIndex;
  if ( unitType != -1 )
    UNIT_SLOT_ACTION_POINTS(result) = g_UnitTypeBaseActionPoints[UNIT_TYPE_METADATA_STRIDE * unitType];
  UNIT_SLOT_HEALTH_PERCENT(result) = 100;
  if ( unitType != -1 )
  {
    if ( (g_UnitTypeFlags[22 * unitType] & 2) != 0 )
      moraleValue = 6;
    else
      moraleValue = 10;
    UNIT_SLOT_MORALE(result) = moraleValue;
  }
  UNIT_SLOT_FATIGUE(result) = 0;
  stanceBits = UNIT_SLOT_STANCE_BITS(result);
  UNIT_SLOT_AUX_STATE(result) = 0;
  auxFlagsByte = *(_BYTE *)(uintptr_t)(result + 17);
  UNIT_SLOT_STANCE_BITS(result) = stanceBits & 0x80;
  stateBitsByte = UNIT_SLOT_STATE_BITS(result);
  *(_BYTE *)(uintptr_t)(result + 17) = auxFlagsByte & 0xF8;
  flagsByte = UNIT_SLOT_FLAGS(result);
  UNIT_SLOT_STATE_BITS(result) = stateBitsByte & 0xFE;
  UNIT_SLOT_FLAGS(result) = flagsByte & 0xF0;
  return result;
}
// 51257A: using guessed type int g_UnitTypeFlags[];

//----- (0040F4D0) --------------------------------------------------------
char  UnitStack_ResetRecord(int stackPtr, unit_type unitType, char ownerIndex)
{
  int slotIndex; // edx

  UnitSlot_InitFromType(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET, unitType, ownerIndex);
  for ( slotIndex = 1; slotIndex < UNIT_STACK_SLOT_COUNT; ++slotIndex )
    *(_WORD *)(uintptr_t)UNIT_STACK_SLOT(stackPtr, slotIndex) = -1;
  *(_DWORD *)(uintptr_t)UNIT_STACK_PATH_BUFFER(stackPtr) = 0;
  UNIT_STACK_OWNER_INDEX(stackPtr) = ownerIndex;
  return ownerIndex;
}
