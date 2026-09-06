/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "buildings_shared_state.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00422B50) --------------------------------------------------------
int  Tooltip_RestoreIfTextMatches(int a1, int a2)
{
  int result; // eax

  result = strcmp_(a2, a1);
  if ( !result )
    return Tooltip_RestoreBackdrop();
  return result;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (00422B70) --------------------------------------------------------
int  Tooltip_SetResourceHandle(int result)
{
  g_TooltipResourceHandle = result;
  return result;
}
// 526F08: using guessed type int g_TooltipResourceHandle;

//----- (00422B80) --------------------------------------------------------
signed int  Unit_CountSelectedGroupMembers(int stackPtr)
{
  __int16 *slotPtr; // edx
  signed int result; // eax

  slotPtr = (__int16 *)(uintptr_t)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET);
  for ( result = 0; result < UNIT_STACK_SLOT_COUNT; ++result )
  {
    if ( *slotPtr == -1 )
      break;
    slotPtr = (__int16 *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
  }
  return result;
}

//----- (00422BA0) --------------------------------------------------------
signed int  UnitStack_HasOnlyFlyingUnits(int stackPtr)
{
  __int16 *slotPtr; // edx
  int slotIndex; // eax
  int unitType; // ecx

  slotPtr = (__int16 *)(uintptr_t)(stackPtr + UNIT_STACK_SLOT_BASE_OFFSET);
  slotIndex = 0;
  while ( 1 )
  {
    unitType = *slotPtr;
    if ( unitType == -1 )
      return 1;
    if ( (g_UnitTypeFlags[UNIT_TYPE_METADATA_DWORD_STRIDE * unitType] & 1) == 0 )
      break;
    ++slotIndex;
    slotPtr = (__int16 *)((char *)slotPtr + UNIT_SLOT_RECORD_BYTES);
    if ( slotIndex >= UNIT_STACK_SLOT_COUNT )
      return 1;
  }
  return 0;
}
// 51257A: using guessed type int g_UnitTypeFlags[];

//----- (00422BE0) --------------------------------------------------------
int  Unit_AddToGroup(unsigned int sourceUnit, int targetUnit, int a3, DWORD a4, double gameTime)
{
  int source_stack;
  int target_stack;
  signed int source_count;
  signed int target_count;
  int row_delta;
  int column_delta;
  int result; // eax

  Debug_Log(sourceUnit, a3, a4, (int)(intptr_t)aUnit_addtogrou);
  Render_DrawSprite_v3(sourceUnit, a4);
  Render_DrawSprite_v3(targetUnit, a4);
  source_stack = UNIT_STACK(sourceUnit);
  target_stack = UNIT_STACK(targetUnit);
  source_count = Unit_GetSquadCount(source_stack);
  target_count = Unit_GetSquadCount(target_stack);
  if ( source_count + target_count <= UNIT_STACK_SLOT_COUNT )
  {
    if ( a3 )
      goto LABEL_11;
    row_delta = UNIT_STACK_TILE_ROW(source_stack) - UNIT_STACK_TILE_ROW(target_stack);
    if ( row_delta < 0 )
      row_delta = -row_delta;
    if ( row_delta <= 1 )
    {
      column_delta = UNIT_STACK_TILE_COLUMN(source_stack) - UNIT_STACK_TILE_COLUMN(target_stack);
      if ( column_delta < 0 )
        column_delta = -column_delta;
      if ( column_delta <= 1 )
        goto LABEL_11;
    }
    result = (int)(intptr_t)Unit_MoveTrackNearTile(sourceUnit, UNIT_STACK_TILE_ROW(target_stack), source_stack, UNIT_STACK_TILE_COLUMN(target_stack), (DWORD)target_stack);
    if ( !result )
      return result;
    qmemcpy((void *)(uintptr_t)UNIT_STACK_PATH_BUFFER(source_stack), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    UnitStack_ExecuteQueuedPath(sourceUnit, 1, UNIT_STACK_TILE_COLUMN(target_stack), (DWORD)target_stack, gameTime);
    if ( !*(_DWORD *)(uintptr_t)UNIT_STACK_PATH_BUFFER(source_stack) )
    {
LABEL_11:
      if ( UnitStack_GetMinCurrentActionPoints(source_stack) >= 4 )
      {
        UnitStack_SpendActionPointsClamped((__int16 *)(uintptr_t)source_stack, 4, (DWORD)target_stack, gameTime);
        source_count = Unit_GetSquadCount(source_stack);
        target_count = Unit_GetSquadCount(target_stack);
        qmemcpy(
          (void *)(uintptr_t)UNIT_STACK_SLOT(target_stack, target_count),
          (const void *)(uintptr_t)UNIT_STACK_SLOT(source_stack, 0),
          UNIT_STACK_SLOT_STRIDE * source_count);
        UnitStack_KillByIndex(sourceUnit, a3, (DWORD)target_stack, gameTime);
        *(_BYTE *)(uintptr_t)(target_stack + 720) = 0;
        g_SelectedUnitIndex = targetUnit;
        Rules_LinkArmyFact((__int16 *)(uintptr_t)target_stack, 0, 0, gameTime, a3, (DWORD)target_stack);
        Rules_SyncArmyFactStrength((__int16 *)(uintptr_t)target_stack, 0, 0, a3, (DWORD)target_stack, gameTime);
        return 1;
      }
    }
  }
  return 0;
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00422DC0) --------------------------------------------------------
BOOL  Unit_CanMoveSelectionFromGroupToTile(int a1, _DWORD *a2, int a3, int a4)
{
  int current_stack;
  int selected_slot_count;
  int slot_list_index;
  unsigned char temp_stack[UNIT_STACK_STRIDE];
  int target_stack_index;
  int target_stack;
  int dest_slot_type;

  if ( a4 < 0 || a4 >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) || a3 < 0 || a3 >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    return 0;
  current_stack = UNIT_STACK(a1);
  selected_slot_count = 0;
  if ( *a2 != -1 )
  {
    do
    {
      if ( selected_slot_count >= UNIT_STACK_SLOT_COUNT )
        break;
      ++selected_slot_count;
    }
    while ( a2[selected_slot_count] != -1 );
  }
  if ( selected_slot_count == 0 || selected_slot_count == Unit_GetSquadCount(current_stack) )
    return 0;
  qmemcpy(temp_stack, (const void *)(uintptr_t)current_stack, UNIT_STACK_STRIDE);
  for ( slot_list_index = 0; slot_list_index < selected_slot_count; ++slot_list_index )
  {
    qmemcpy(
      temp_stack + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * slot_list_index,
      (const void *)(uintptr_t)UNIT_STACK_SLOT(current_stack, a2[slot_list_index]),
      UNIT_STACK_SLOT_STRIDE);
  }
  *(__int16 *)(temp_stack + UNIT_STACK_SLOT_BASE_OFFSET + UNIT_STACK_SLOT_STRIDE * selected_slot_count) = -1;
  target_stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(a4, a3));
  if ( target_stack_index > 0x1F4u )
  {
    return UnitStack_GetMinCurrentActionPoints((intptr_t)temp_stack) >= 4
        && UnitStack_GetTileMoveCostOrZero((__int16 *)temp_stack, a4, 0, a3) != 0;
  }
  target_stack = UNIT_STACK(target_stack_index);
  dest_slot_type = *(__int16 *)(uintptr_t)(target_stack + UNIT_STACK_SLOT_BASE_OFFSET);
  if ( dest_slot_type < 0 || dest_slot_type > 0x28 )
  {
    return UnitStack_GetMinCurrentActionPoints((intptr_t)temp_stack) >= 4
        && UnitStack_GetTileMoveCostOrZero((__int16 *)temp_stack, a4, 0, a3) != 0;
  }
  return UnitStack_GetMinCurrentActionPoints((intptr_t)temp_stack) >= 4
      && UNIT_STACK_OWNER_INDEX(target_stack) == UNIT_STACK_OWNER_INDEX(current_stack);
}

BOOL  Map_IsTilePlacable(int a1, _DWORD *a2, int a3, int a4)
{
  return Unit_CanMoveSelectionFromGroupToTile(a1, a2, a3, a4);
}
// 5202E4: using guessed type int gameData;

//----- (00423050) --------------------------------------------------------
BOOL  Unit_MoveSelectionFromGroupToTile(int unitIndex, _DWORD *selectedSlots, int targetColumn, int targetRow, double gameTime, int forcePlacement)
{
  int current_stack;
  int selected_slot_count;
  int target_stack_index;
  int target_stack;
  int slot_list_index;
  int target_count;
  unsigned char *dest_slot;
  unsigned char *source_slot;
  char facing;

  Debug_Log(selectedSlots[1], *selectedSlots, selectedSlots[4], (int)(intptr_t)aUnit_movefromg);
  Render_DrawSprite_v3(unitIndex, unitIndex);
  current_stack = UNIT_STACK(unitIndex);
  selected_slot_count = 0;
  if ( *selectedSlots != -1 )
  {
    do
    {
      if ( selected_slot_count >= UNIT_STACK_SLOT_COUNT )
        break;
      ++selected_slot_count;
    }
    while ( selectedSlots[selected_slot_count] != -1 );
  }
  if ( selected_slot_count == 0 || selected_slot_count == Unit_GetSquadCount(current_stack) )
    return 0;
  target_stack = 0;
  target_stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(targetRow, targetColumn));
  if ( target_stack_index < 0x8000 )
  {
    target_stack = UNIT_STACK(target_stack_index);
    if ( selected_slot_count + Unit_GetSquadCount(target_stack) > UNIT_STACK_SLOT_COUNT )
      return 0;
    if ( !Map_IsTilePlacable(unitIndex, selectedSlots, targetColumn, targetRow) )
      return 0;
  }
  else if ( !forcePlacement )
  {
    if ( !Map_IsTilePlacable(unitIndex, selectedSlots, targetColumn, targetRow) )
      return 0;
  }
  if ( !target_stack )
  {
    facing = Facing_DirectionFromDelta8(targetRow - UNIT_STACK_TILE_ROW(current_stack), targetColumn - UNIT_STACK_TILE_COLUMN(current_stack));
    Unit_Create((unit_type)(unsigned int)(0xFFFFFFFF), UNIT_STACK_OWNER_INDEX(current_stack), targetRow, facing, targetColumn);
  }
  target_stack_index = *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(targetRow, targetColumn));
  target_stack = UNIT_STACK(target_stack_index);
  target_count = Unit_GetSquadCount(target_stack);
  dest_slot = (unsigned char *)(uintptr_t)UNIT_STACK_SLOT(target_stack, target_count);
  for ( slot_list_index = 0; slot_list_index < selected_slot_count; ++slot_list_index )
  {
    source_slot = (unsigned char *)(uintptr_t)UNIT_STACK_SLOT(current_stack, selectedSlots[slot_list_index]);
    qmemcpy(dest_slot, source_slot, UNIT_STACK_SLOT_STRIDE);
    dest_slot[8] -= 4;
    UNIT_SLOT_TYPE(source_slot) = -1;
    dest_slot += UNIT_STACK_SLOT_STRIDE;
  }
  Unit_CompactSquad((__int16 *)(uintptr_t)current_stack, targetRow, gameTime);
  *(_BYTE *)(uintptr_t)(current_stack + 720) = 0;
  Rules_LinkArmyFact((__int16 *)(uintptr_t)current_stack, 0, 0, gameTime, 0, (DWORD)current_stack);
  Rules_SyncArmyFactStrength((__int16 *)(uintptr_t)current_stack, 0, 0, 0, (DWORD)current_stack, gameTime);
  Rules_LinkArmyFact((__int16 *)(uintptr_t)target_stack, 0, 0, gameTime, 0, (DWORD)target_stack);
  Rules_SyncArmyFactStrength((__int16 *)(uintptr_t)target_stack, 0, 0, 0, (DWORD)target_stack, gameTime);
  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(target_stack_index, gameTime);
  Trap_TriggerAtStackTile(target_stack_index, (DWORD)current_stack, gameTime);
  return 1;
}
// 5202E4: using guessed type int gameData;

//----- (00423370) --------------------------------------------------------
_DWORD * UI_LoadCurrentPlayerInfoSpriteSet(int playerIndex, int a2, char a3, DWORD a4)
{
  int playerIndexCopy; // edx
  int v5; // ecx
  _DWORD *result; // eax
  _BYTE fileName[24]; // [esp+0h] [ebp-1Ch] BYREF
  int v8 CLASH95_UNUSED; // [esp+18h] [ebp-4h]

  v8 = a2;
  playerIndexCopy = playerIndex;
  if ( g_CurrentPlayerInfoSpriteSet )
  {
    nfree_(g_CurrentPlayerInfoSpriteSet);
    g_CurrentPlayerInfoSpriteSet = 0;
  }
  sprintf_((char*)(fileName), "info%d.s32", playerIndexCopy + 1);
  result = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v5, a3, a4);
  if ( result )
  {
    result = DLXSpriteSet_Load(result, fileName);
    g_CurrentPlayerInfoSpriteSet = (int)(intptr_t)result;
  }
  else
  {
    g_CurrentPlayerInfoSpriteSet = 0;
  }
  return result;
}
// 423393: variable 'v4' is possibly undefined
// 4233AB: variable 'v5' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 527C24: using guessed type int dword_527C24;

//----- (004233E0) --------------------------------------------------------
int UI_FreeCurrentPlayerInfoSpriteSet(void)
{
  int result; // eax

  if ( g_CurrentPlayerInfoSpriteSet )
    result = nfree_(g_CurrentPlayerInfoSpriteSet);
  g_CurrentPlayerInfoSpriteSet = 0;
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 527C24: using guessed type int dword_527C24;

//----- (00423420) --------------------------------------------------------
int  UnitStackSelection_RedrawPanel(int result, DWORD a2)
{
  int chosenUnitIndex; // edx
  int chosenUnitIndexScaled; // eax
  int *slotListPtr; // ebx
  void *v5 CLASH95_UNUSED; // ecx
  int v6; // ecx
  int ownerIndex; // eax
  int SpriteForChar; // eax
  int v9; // ecx
  int unitSpriteId; // eax
  int statusMarkSpriteId; // eax
  int selectionMarkSpriteId; // eax
  int neighbor_row; // eax
  int neighbor_column; // ebp
  int selectedSlotList[11]; // [esp+44h] [ebp-4Ch] BYREF
  int j; // [esp+70h] [ebp-20h]
  int i; // [esp+74h] [ebp-1Ch]

  if ( g_UnitStackSelectionActiveUnitIndex != -1 )
  {
    if ( result == -1 )
    {
      chosenUnitIndex = g_SelectedUnitIndex;
      chosenUnitIndexScaled = 8 * g_SelectedUnitIndex;
    }
    else
    {
      chosenUnitIndex = result;
      chosenUnitIndexScaled = 8 * result;
    }
    g_SelectedUnitStackRecordPtr = 5 * (chosenUnitIndex + 16 * (chosenUnitIndex + chosenUnitIndexScaled)) + gameData + UNIT_STACK_TABLE_OFFSET;
    memset(selectedSlotList, 0, sizeof(selectedSlotList));
    slotListPtr = selectedSlotList;
    UnitStackSelection_BuildSelectedSlotIndexList((int)(intptr_t)g_UnitStackSlotSelectedFlags, UNIT_STACK_SLOT_COUNT, selectedSlotList);
    UI_ClearTileHighlight(0);
    if ( (unsigned int)*(__int16 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + UNIT_STACK_SLOT_BASE_OFFSET) <= 0x28 && UnitStackSelection_HasSelectedSlots() )
    {
      for ( i = 0; i < 12; ++i )
      {
        neighbor_column = Map_NeighborDY[2 * i] + *(__int16 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + 2);
        neighbor_row = Map_NeighborDX[2 * i] + *(__int16 *)(uintptr_t)g_SelectedUnitStackRecordPtr;
        if ( Map_IsTilePlacable(g_SelectedUnitIndex, (_DWORD*)(selectedSlotList), neighbor_column, neighbor_row) )
          UI_HighlightTile(neighbor_row, neighbor_column);
      }
    }
    g_RenderDevice = (_UNKNOWN *)(uintptr_t)g_PrimaryRenderSurface;
    ownerIndex = *(unsigned __int8 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + 4);
    if ( ownerIndex != g_CurrentPlayerIndex )
      UI_LoadCurrentPlayerInfoSpriteSet(ownerIndex, v6, (char)(intptr_t)slotListPtr, a2);
    SpriteForChar = DLX_GetSpriteForChar(g_MarksSpriteSet, 35);
    Compat_RenderDeviceDrawMenuSprite(400, 29, SpriteForChar, 1);
    for ( j = 0; j < UNIT_STACK_SLOT_COUNT; ++j )
    {
      if ( *(__int16 *)(uintptr_t)(UNIT_SLOT_RECORD_BYTES * j + g_SelectedUnitStackRecordPtr + UNIT_STACK_SLOT_BASE_OFFSET) == -1 )
        break;
      unitSpriteId = DLX_GetSpriteForChar(g_CurrentPlayerInfoSpriteSet, *(__int16 *)(uintptr_t)(UNIT_SLOT_RECORD_BYTES * j + g_SelectedUnitStackRecordPtr + UNIT_STACK_SLOT_BASE_OFFSET));
      Compat_RenderDeviceDrawMenuSprite(401, 38 * j + 35, unitSpriteId, 1);
      if ( (*(_BYTE *)(uintptr_t)(g_SelectedUnitStackRecordPtr + UNIT_SLOT_RECORD_BYTES * j + 19) & 4) != 0 )
      {
        statusMarkSpriteId = DLX_GetSpriteForChar(g_MarksSpriteSet, 33);
        Compat_RenderDeviceDrawMenuSprite(405, 38 * j + 40, statusMarkSpriteId, 1);
      }
      Render_ReleaseSurface(7, a2);
      v9 = g_CurrentPlayerIndex;
      if ( *(unsigned __int8 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + 4) == g_CurrentPlayerIndex )
        UI_DrawTextFmt(j, 38 * j + 32, 38 * j + 70, 450, 3, (const char*)(intptr_t)((int)(intptr_t)aD_5));
      if ( g_UnitStackSlotSelectedFlags[j] )
      {
        selectionMarkSpriteId = DLX_GetSpriteForChar(g_MarksSpriteSet, (*(unsigned __int8 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + UNIT_SLOT_RECORD_BYTES * j + 14) >= 4u) + 4);
        Compat_RenderDeviceDrawMenuSprite(402, 38 * j + 58, selectionMarkSpriteId, 1);
      }
    }
    result = *(unsigned __int8 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + 4);
    if ( result != g_CurrentPlayerIndex )
      return (int)(intptr_t)UI_LoadCurrentPlayerInfoSpriteSet(g_CurrentPlayerIndex, v9, g_CurrentPlayerIndex, a2);
  }
  return result;
}
// 42349D: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 42348D: variable 'v5' is possibly undefined
// 423555: variable 'v6' is possibly undefined
// 42374A: variable 'v9' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 514194: using guessed type int dword_514194;
// 5202C8: using guessed type int dword_5202C8;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 526F78: using guessed type _DWORD dword_526F78[10];
// 526FA0: using guessed type int dword_526FA0;
// 527C24: using guessed type int dword_527C24;

//----- (00423760) --------------------------------------------------------
int  UnitStack_ShowSelectionDialog(int unitIndex, int a2)
{
  _BYTE savedSlotFlags[40]; // [esp+0h] [ebp-48h] BYREF
  int savedStackRecordPtr; // [esp+28h] [ebp-20h]
  int savedSelectionModeActive; // [esp+2Ch] [ebp-1Ch]
  int savedActiveUnitIndex; // [esp+30h] [ebp-18h]

  savedActiveUnitIndex = g_UnitStackSelectionActiveUnitIndex;
  savedSelectionModeActive = g_UnitStackSelectionModeActive;
  savedStackRecordPtr = g_SelectedUnitStackRecordPtr;
  qmemcpy(savedSlotFlags, g_UnitStackSlotSelectedFlags, sizeof(savedSlotFlags));
  g_UnitStackSelectionModeActive = 1;
  g_UnitStackSelectionActiveUnitIndex = unitIndex;
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(unitIndex, unitIndex);
  WorldMap_RedrawViewport(1);
  while ( DD_IsLost((int)(intptr_t)g_RenderState) )
  {
    DD_Pump((int)(intptr_t)g_RenderState, a2);
    WorldMap_HandleScrollKeysAndIdle(unitIndex);
    WorldMap_RedrawFrame(a2);
  }
  g_UnitStackSelectionModeActive = savedSelectionModeActive;
  g_UnitStackSelectionActiveUnitIndex = savedActiveUnitIndex;
  g_SelectedUnitStackRecordPtr = savedStackRecordPtr;
  qmemcpy(g_UnitStackSlotSelectedFlags, savedSlotFlags, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(-1, unitIndex);
  return WorldMap_RedrawViewport(1);
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 514194: using guessed type int dword_514194;
// 526994: using guessed type int dword_526994;
// 526F78: using guessed type _DWORD dword_526F78[10];
// 526FA0: using guessed type int dword_526FA0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00423860) --------------------------------------------------------
signed int  UnitStackSelection_HandleInput(DWORD a1, double a2)
{
  int slot_index; // esi
  signed int handled_panel_input; // edi
  signed int special_unit_info; // eax
  int target_tile_x; // esi
  int target_tile_y; // ecx
  int distance_x; // eax
  int distance_y; // eax
  int selected_slot_indices[12]; // [esp+0h] [ebp-30h] BYREF

  if ( g_UnitStackSelectionActiveUnitIndex == -1 )
    return 0;
  slot_index = ((g_MouseCursorRawX >> g_CursorCoordShift) - 35) / 38;
  handled_panel_input = 0;
  if ( g_MouseCursorRawY >> g_CursorCoordShift >= 400
    && g_MouseCursorRawY >> g_CursorCoordShift < 464
    && slot_index >= 0
    && slot_index <= 9 )
  {
    RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
    if ( DD_IsLost((int)(intptr_t)g_RenderState) && *(__int16 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + UNIT_SLOT_RECORD_BYTES * slot_index + UNIT_STACK_SLOT_BASE_OFFSET) != -1 )
    {
      special_unit_info = UnitStack_HasSpecialPersonageUnits(g_SelectedUnitStackRecordPtr);
      Unit_Info(100, 100, special_unit_info, (unsigned __int8 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + UNIT_SLOT_RECORD_BYTES * slot_index + UNIT_STACK_SLOT_BASE_OFFSET), a1, 0);
      WorldMap_RedrawViewport(1);
    }
    if ( DD_IsFlipping((int)(intptr_t)g_RenderState) && *(__int16 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + UNIT_SLOT_RECORD_BYTES * slot_index + UNIT_STACK_SLOT_BASE_OFFSET) != -1 )
    {
      LOBYTE(g_UnitStackSlotSelectedFlags[slot_index]) ^= 1u;
      Diagnostics_TraceWorldMapActionEvent(
        "selection_slot_toggle",
        g_SelectedUnitIndex,
        slot_index,
        g_UnitStackSlotSelectedFlags[slot_index],
        g_UnitStackSelectionActiveUnitIndex);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_toggle_set",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
      UnitStackSelection_RedrawPanel(-1, a1);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_redraw",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
      WorldMap_RedrawViewport(1);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_refresh",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
      Render_Begin((int)(intptr_t)g_RenderState, 0);
      Diagnostics_TraceWorldMapActionEvent(
        "selection_after_render_begin",
        g_SelectedUnitIndex,
        g_UnitStackSelectionActiveUnitIndex,
        g_UnitStackSlotSelectedFlags[0],
        g_UnitStackSlotSelectedFlags[slot_index]);
    }
    handled_panel_input = 1;
  }
  if ( DD_IsFlipping((int)(intptr_t)g_RenderState) )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "selection_split_probe",
      g_SelectedUnitIndex,
      g_UnitStackSelectionActiveUnitIndex,
      g_UnitStackSlotSelectedFlags[0],
      UnitStackSelection_HasSelectedSlots());
  }
  if ( DD_IsFlipping((int)(intptr_t)g_RenderState) && UnitStackSelection_HasSelectedSlots() )
  {
    target_tile_x = ((g_MouseCursorRawX >> g_CursorCoordShift) - 32) / 64 + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET);
    target_tile_y = ((g_MouseCursorRawY >> g_CursorCoordShift) - 16) / 64 + *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET);
    distance_x = *(__int16 *)(uintptr_t)g_SelectedUnitStackRecordPtr - target_tile_x;
    if ( distance_x < 0 )
      distance_x = -distance_x;
    if ( distance_x <= 1 )
    {
      distance_y = *(__int16 *)(uintptr_t)(g_SelectedUnitStackRecordPtr + 2) - target_tile_y;
      if ( distance_y < 0 )
        distance_y = -distance_y;
      if ( distance_y <= 1 )
      {
        Render_Begin((int)(intptr_t)g_RenderState, 0);
        memset(selected_slot_indices, 0, sizeof(selected_slot_indices));
        UnitStackSelection_BuildSelectedSlotIndexList((int)(intptr_t)g_UnitStackSlotSelectedFlags, UNIT_STACK_SLOT_COUNT, selected_slot_indices);
        Diagnostics_TraceWorldMapActionEvent(
          "selection_split_attempt",
          g_SelectedUnitIndex,
          target_tile_x,
          target_tile_y,
          selected_slot_indices[0]);
        if ( Unit_MoveSelectionFromGroupToTile(
               g_SelectedUnitIndex,
               (_DWORD *)selected_slot_indices,
               target_tile_y,
               target_tile_x,
               a2,
               0) )
        {
          Diagnostics_TraceWorldMapActionEvent(
            "selection_split_done",
            g_SelectedUnitIndex,
            target_tile_x,
            target_tile_y,
            selected_slot_indices[0]);
          memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
        }
        Render_LoadResourceSprite_v2();
        UnitStackSelection_RedrawPanel(-1, a1);
        WorldMap_RedrawViewport(1);
      }
    }
  }
  return handled_panel_input;
}
// 4238BB: simplified comparisons for 'esi.4': <0 || >=A became >=Au
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;
// 5202E4: using guessed type int gameData;
// 526F78: using guessed type _DWORD dword_526F78[10];
// 526FA0: using guessed type int dword_526FA0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (00423AC0) --------------------------------------------------------
signed int UnitStackSelection_HasSelectedSlots(void)
{
  int byte_offset; // eax

  if ( g_UnitStackSelectionActiveUnitIndex != -1 )
  {
    byte_offset = 0;
    if ( *(_DWORD *)g_UnitStackSlotSelectedFlags )
      return 1;
    while ( 1 )
    {
      byte_offset += 4;
      if ( byte_offset >= 40 )
        break;
      if ( *(_DWORD *)((char *)g_UnitStackSlotSelectedFlags + byte_offset) )
        return 1;
    }
  }
  return 0;
}
// 514194: using guessed type int dword_514194;

//----- (00423B00) --------------------------------------------------------
int  UnitStackSelection_BeginForSelectedStack(DWORD a1)
{
  g_UnitStackSelectionModeActive = 1;
  g_UnitStackSelectionActiveUnitIndex = g_SelectedUnitIndex;
  Diagnostics_TraceWorldMapActionEvent(
    "selection_begin_clear",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    0);
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  UnitStackSelection_RedrawPanel(-1, a1);
  return WorldMap_RedrawViewport(1);
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;
// 526994: using guessed type int dword_526994;

//----- (00423B40) --------------------------------------------------------
int __thiscall UnitStackSelection_End(void *this_)
{
  UI_ClearTileHighlight(this_);
  g_UnitStackSelectionModeActive = 0;
  g_UnitStackSelectionActiveUnitIndex = -1;
  return WorldMap_RedrawViewport(1);
}
// 514194: using guessed type int dword_514194;
// 526994: using guessed type int dword_526994;

//----- (00423B70) --------------------------------------------------------
int __thiscall UnitStackSelection_ClearMask(void *this_)
{
  (void)this_;
  Diagnostics_TraceWorldMapActionEvent(
    "selection_mask_clear",
    g_SelectedUnitIndex,
    g_UnitStackSelectionActiveUnitIndex,
    g_UnitStackSlotSelectedFlags[0],
    0);
  memset(g_UnitStackSlotSelectedFlags, 0, sizeof(g_UnitStackSlotSelectedFlags));
  return (int)(uintptr_t)g_UnitStackSlotSelectedFlags;
}

//----- (00423B90) --------------------------------------------------------
int  UnitStackSelection_RefreshForSelectedStack(DWORD a1)
{
  g_UnitStackSelectionActiveUnitIndex = g_SelectedUnitIndex;
  UnitStackSelection_RedrawPanel(-1, a1);
  return WorldMap_RedrawViewport(1);
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514194: using guessed type int dword_514194;

//----- (00423BB0) --------------------------------------------------------
BOOL  MapTile_HasNorthRoadConnection(int row, int column)
{
  const MapTileRecord *neighborTile = (const MapTileRecord *)(uintptr_t)(
      gameData + TILE_TERRAIN_ROW_STRIDE * (row - 1) + TILE_TERRAIN_RECORD_STRIDE * column);
  const int roadTileId = Map_NormalizeRoadOverlayTileId(neighborTile->road_or_bridge_tile_id);
  return roadTileId == 867 || roadTileId == 869 || roadTileId == 871 || roadTileId == 872
      || roadTileId == 874 || roadTileId == 875 || roadTileId == 868 || roadTileId == 952;
}
// 5202E4: using guessed type int gameData;

//----- (00423C50) --------------------------------------------------------
BOOL  MapTile_HasSouthRoadConnection(int row, int column)
{
  const MapTileRecord *neighborTile = (const MapTileRecord *)(uintptr_t)(
      gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column);
  const int roadTileId = Map_NormalizeRoadOverlayTileId(neighborTile->road_or_bridge_tile_id);
  return roadTileId == 867 || roadTileId == 869 || roadTileId == 870 || roadTileId == 872
      || roadTileId == 873 || roadTileId == 875 || roadTileId == 876 || roadTileId == 951;
}
// 5202E4: using guessed type int gameData;

//----- (00423CF0) --------------------------------------------------------
BOOL  MapTile_HasWestRoadConnection(int row, int column)
{
  const int buildingMarker = *(const unsigned __int16 *)(uintptr_t)TILE_INDEX(row, column - 2);
  if ( buildingMarker >= TILE_OCCUPANT_BUILDING_INDEX_BASE && buildingMarker <= 65534 )
  {
    const unsigned char *building = (const unsigned char *)(uintptr_t)BUILDING_RECORD(
        buildingMarker - TILE_OCCUPANT_BUILDING_INDEX_BASE);
    const int buildingType = (signed char)building[4];
    // Original 0x423D53 accepts this building before reading the Road tile.
    if ( (buildingType == 2 || buildingType == 1)
      && building[0] == row && building[1] == column - 2 )
    {
      return 1;
    }
  }

  const MapTileRecord *neighborTile = (const MapTileRecord *)(uintptr_t)(
      gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * (column - 1));
  const int roadTileId = Map_NormalizeRoadOverlayTileId(neighborTile->road_or_bridge_tile_id);
  return roadTileId == 866 || roadTileId == 868 || roadTileId == 869 || roadTileId == 870
      || roadTileId == 871 || roadTileId == 872 || roadTileId == 873 || roadTileId == 949;
}
// 5202E4: using guessed type int gameData;

//----- (00423E10) --------------------------------------------------------
BOOL  MapTile_HasEastRoadConnection(int row, int column)
{
  const MapTileRecord *neighborTile = (const MapTileRecord *)(uintptr_t)(
      gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * (column + 1));
  const int roadTileId = Map_NormalizeRoadOverlayTileId(neighborTile->road_or_bridge_tile_id);
  return roadTileId == 866 || (roadTileId >= 871 && roadTileId <= 876) || roadTileId == 950;
}
// 5202E4: using guessed type int gameData;

//----- (00423E90) --------------------------------------------------------
int  Map_RebuildRoadOverlayAtTile(int row, int column)
{
  // Original 0x423E90 probes west, south, east, then north using the same tile.
  int connectionMask = 8 * MapTile_HasWestRoadConnection(row, column);
  connectionMask |= 4 * MapTile_HasSouthRoadConnection(row, column);
  connectionMask |= 2 * MapTile_HasEastRoadConnection(row, column);
  connectionMask |= MapTile_HasNorthRoadConnection(row, column);
  const int overlaySprite = g_RoadOverlaySpriteByConnectionMask[connectionMask];

  // Preserve the original row-base return, distinct from the updated tile.
  const int rowBaseAddress = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  MapTileRecord *tile = (MapTileRecord *)(uintptr_t)(
      rowBaseAddress + TILE_TERRAIN_RECORD_STRIDE * column);
  tile->road_or_bridge_tile_id = overlaySprite ? overlaySprite : 0xFFFF;
  return rowBaseAddress;
}
// 5141A0: using guessed type int dword_5141A0[27];
// 5202E4: using guessed type int gameData;

//----- (00423FC0) --------------------------------------------------------
int  Map_NormalizeRoadOverlayTileId(int overlayTileId)
{
  if ( overlayTileId >= 819 && overlayTileId <= 861 )
  {
    WorldMap_EnsureBuilderWidgetTables();
    // Original 0x42400E reads WORDs at 0x51423C..0x514290 in shared Road data.
    constexpr int normalizationTableOffset = 0x30;
    const int tableIndex = overlayTileId - 819;
    uint16_t normalizedTileId;
    memcpy(&normalizedTileId,
           g_RoadBuildData + normalizationTableOffset + sizeof(normalizedTileId) * tableIndex,
           sizeof(normalizedTileId));
    return normalizedTileId;
  }
  if ( overlayTileId >= 877 && overlayTileId <= 949 )
    return ((overlayTileId - 877) % 6 / 3 == 0) + 866;
  return overlayTileId;
}

//----- (00424020) --------------------------------------------------------
signed int  MapTile_HasAlignedBridgeApproachRoadOverlay(int refRow, int refColumn, int column, int row)
{
  WorldMap_EnsureBuilderWidgetTables();
  const MapTileRecord *tile = (const MapTileRecord *)(uintptr_t)(
      gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
  const int overlayTileId = tile->overlay_tile_id;
  int matchedApproachIndex = -1;

  // Original 0x42407F scans 48 live DWORDs, including aliased marker data.
  // Preserve the first match: its index selects the required alignment axis.
  for (int approachIndex = 0; approachIndex < 48; ++approachIndex)
  {
    if ( overlayTileId == g_BridgeApproachRoadOverlayTileIds[approachIndex] )
    {
      matchedApproachIndex = approachIndex;
      break;
    }
  }

  if ( matchedApproachIndex == -1 )
    return 0;
  if ( matchedApproachIndex >= 6 )
  {
    if ( column != refColumn )
      return 0;
  }
  else if ( row != refRow )
  {
    return 0;
  }

  const int terrainTileId = tile->terrain_tile_id;
  return terrainTileId >= 603 && terrainTileId <= 610;
}
// 51420C: using guessed type int g_BridgeApproachRoadOverlayTileIds[];
// 5202E4: using guessed type int gameData;

//----- (00424120) --------------------------------------------------------
BOOL  MapTile_IsBareBridgeCrossingRoadOverlayCandidate(int row, int column)
{
  int southOverlay; // ebp
  int v3; // eax
  int westOverlay; // ecx
  unsigned int northOverlay; // edi
  int eastOverlay; // ebx
  unsigned __int16 *tilePtr; // eax
  int baseTileId; // eax
  BOOL result; // eax

  if ( !row || *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) - 1 == row || !column || column == *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) - 1 )
    return 0;
  southOverlay = *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4);
  v3 = gameData + TILE_TERRAIN_ROW_STRIDE * row;
  westOverlay = *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (column - 1) + v3 + 4);
  northOverlay = *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (row - 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4);
  eastOverlay = *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (column + 1) + v3 + 4);
  if ( northOverlay >= 0x36D && *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (row - 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4) <= 0x3B4u )
    northOverlay = (int)(northOverlay - 877) % 6;
  if ( *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4) >= 0x36Du
    && *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (row + 1) + TILE_TERRAIN_RECORD_STRIDE * column + 4) <= 0x3B4u )
  {
    southOverlay = (southOverlay - 877) % 6;
  }
  if ( *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (column - 1) + v3 + 4) >= 0x36Du
    && *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (column - 1) + v3 + 4) <= 0x3B4u )
  {
    westOverlay = (westOverlay - 877) % 6;
  }
  if ( *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (column + 1) + v3 + 4) >= 0x36Du
    && *(unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (column + 1) + v3 + 4) <= 0x3B4u )
  {
    eastOverlay = (eastOverlay - 877) % 6;
  }
  tilePtr = (unsigned __int16 *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * column + TILE_TERRAIN_ROW_STRIDE * row + gameData);
  result = 0;
  if ( tilePtr[1] == 0xFFFF )
  {
    baseTileId = *tilePtr;
    if ( baseTileId >= 603 && baseTileId <= 610 && (northOverlay <= 1 || southOverlay == 1 || southOverlay == 2 || westOverlay == 3 || westOverlay == 4 || eastOverlay == 4 || eastOverlay == 5) )
      return 1;
  }
  return result;
}
// 424328: simplified comparisons for 'edi.4': !=0 && !=1 became >=2u
// 5202E4: using guessed type int gameData;

//----- (00424370) --------------------------------------------------------
signed int  Map_GetBridgeCrossingCostOrZero(int row, int column)
{
  const MapTileRecord *tile = (const MapTileRecord *)(uintptr_t)(
      gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column);
  const int terrainTileId = tile->terrain_tile_id;
  return terrainTileId >= 603 && terrainTileId <= 610 ? 5 : 0;
}
// 5202E4: using guessed type int gameData;

//----- (00424400) --------------------------------------------------------
signed int  Road_Build(int unitIndex, int direction, char a3, DWORD a4, double a5)
{
  int v5; // ecx
  int unitStackRecordBase; // eax
  BOOL hasNorthRoad; // ebx
  BOOL hasSouthRoad; // edi
  BOOL hasEastRoad; // eax
  int hasWestRoad; // ecx
  int targetRow; // esi
  int targetColumn; // ebp
  __int16 roadOverlayTileId; // di
  unsigned __int16 *originTilePtr; // edx
  int originBaseTileId; // eax
  unsigned __int16 neighborBaseTileId; // ax
  int targetTileRecordBase; // eax
  int crossingTileRecordBase; // eax
  signed int result; // eax
  signed int minActionPoints; // eax
  signed int v21; // edx
  unsigned __int16 neighborPrevOverlay; // di
  int v23; // ecx
  int targetOverlayRecordBase; // ebx
  DWORD unitStackByteOffset; // ebp
  int unitCurrentColumn; // ebx
  int v27; // edx
  int moveTargetColumn; // [esp-4h] [ebp-44h]
  int originRow; // [esp+8h] [ebp-38h]
  int bridgeCrossOverlayId; // [esp+Ch] [ebp-34h]
  signed int moveCost; // [esp+10h] [ebp-30h]
  int savedTargetOverlay; // [esp+14h] [ebp-2Ch]
  int appliedTargetOverlay; // [esp+1Ch] [ebp-24h]
  int bridgeApproachOverlayId; // [esp+24h] [ebp-1Ch]
  int originColumn; // [esp+28h] [ebp-18h]

  Debug_Log(unitIndex, a3, a4, (int)(intptr_t)aRoad_buildDD);
  /* asm 00424400: `mov ecx, eax` before the log call (which preserves ecx),
   * then `mov eax, ecx` scaled 145*u then 725*u: gameData + 725*unitIndex. */
  v5 = unitIndex;
  unitStackRecordBase = gameData + UNIT_STACK_STRIDE * v5;
  originRow = *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TABLE_OFFSET);
  originColumn = *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET);
  hasNorthRoad = MapTile_HasNorthRoadConnection(originRow, originColumn);
  hasSouthRoad = MapTile_HasSouthRoadConnection(originRow, originColumn);
  /* asm 00424474: `call sub_423CF0 / mov ecx, eax` -- the west result IS kept
   * and drives the per-direction overlay choice; the decompiler dropped it. */
  hasWestRoad = MapTile_HasWestRoadConnection(originRow, originColumn);
  hasEastRoad = MapTile_HasEastRoadConnection(originRow, originColumn);
  switch ( direction )
  {
    case DIRECTION8_WEST:
      targetRow = originRow;
      targetColumn = originColumn - 1;
      if ( !hasEastRoad && hasNorthRoad && !hasSouthRoad )
      {
        roadOverlayTileId = 876;
        goto LABEL_14;
      }
      if ( !hasEastRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 874;
        goto LABEL_14;
      }
      if ( !hasEastRoad && hasNorthRoad && hasSouthRoad )
        goto LABEL_40;
      if ( hasEastRoad && hasNorthRoad && !hasSouthRoad )
        goto LABEL_41;
      if ( hasEastRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 871;
        goto LABEL_14;
      }
      if ( !hasEastRoad || !hasNorthRoad || !hasSouthRoad )
        goto LABEL_44;
      goto LABEL_13;
    case DIRECTION8_SOUTH:
      targetColumn = originColumn;
      targetRow = originRow + 1;
      if ( !hasNorthRoad && hasWestRoad && !hasEastRoad )
      {
        roadOverlayTileId = 874;
        goto LABEL_14;
      }
      if ( !hasNorthRoad && !hasWestRoad && hasEastRoad )
      {
        roadOverlayTileId = 868;
        goto LABEL_14;
      }
      if ( !hasNorthRoad && hasWestRoad && hasEastRoad )
      {
        roadOverlayTileId = 871;
        goto LABEL_14;
      }
      if ( hasNorthRoad && hasWestRoad && !hasEastRoad )
        goto LABEL_40;
      if ( hasNorthRoad && !hasWestRoad && hasEastRoad )
      {
        roadOverlayTileId = 869;
        goto LABEL_14;
      }
      if ( hasNorthRoad && hasWestRoad && hasEastRoad )
        goto LABEL_13;
      goto LABEL_68;
    case DIRECTION8_EAST:
      targetRow = originRow;
      targetColumn = originColumn + 1;
      if ( !hasWestRoad && hasNorthRoad && !hasSouthRoad )
      {
        roadOverlayTileId = 870;
        goto LABEL_14;
      }
      if ( !hasWestRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 868;
        goto LABEL_14;
      }
      if ( !hasWestRoad && hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 869;
        goto LABEL_14;
      }
      if ( hasWestRoad && hasNorthRoad && !hasSouthRoad )
      {
LABEL_41:
        roadOverlayTileId = 873;
        goto LABEL_14;
      }
      if ( hasWestRoad && !hasNorthRoad && hasSouthRoad )
      {
        roadOverlayTileId = 871;
        goto LABEL_14;
      }
      if ( !hasWestRoad || !hasNorthRoad || !hasSouthRoad )
      {
LABEL_44:
        roadOverlayTileId = 866;
        goto LABEL_14;
      }
      goto LABEL_13;
    case DIRECTION8_NORTH:
      targetColumn = originColumn;
      targetRow = originRow - 1;
      if ( hasSouthRoad || !hasWestRoad || hasEastRoad )
      {
        if ( hasSouthRoad || hasWestRoad || !hasEastRoad )
        {
          if ( !hasSouthRoad && hasWestRoad && hasEastRoad )
          {
            roadOverlayTileId = 873;
          }
          else if ( hasSouthRoad && hasWestRoad && !hasEastRoad )
          {
LABEL_40:
            roadOverlayTileId = 875;
          }
          else if ( hasSouthRoad && !hasWestRoad && hasEastRoad )
          {
            roadOverlayTileId = 869;
          }
          else if ( hasSouthRoad && hasWestRoad && hasEastRoad )
          {
LABEL_13:
            roadOverlayTileId = 872;
          }
          else
          {
LABEL_68:
            roadOverlayTileId = 867;
          }
        }
        else
        {
          roadOverlayTileId = 870;
        }
      }
      else
      {
        roadOverlayTileId = 876;
      }
LABEL_14:
      originTilePtr = (unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * originRow + TILE_TERRAIN_RECORD_STRIDE * originColumn);
      HIWORD(originBaseTileId) = 0;
      if ( *originTilePtr >= 0x25Bu )
      {
        LOWORD(originBaseTileId) = *originTilePtr;
        if ( originBaseTileId <= 642 )
          roadOverlayTileId = originTilePtr[2];
      }
      appliedTargetOverlay = 0;
      savedTargetOverlay = 0;
      if ( MapTile_HasAlignedBridgeApproachRoadOverlay(originRow, originColumn, targetColumn, targetRow) )
      {
        neighborBaseTileId = *(_WORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 2);
        if ( neighborBaseTileId >= 0x236u )
        {
          if ( neighborBaseTileId <= 0x236u )
          {
            bridgeApproachOverlayId = 877;
          }
          else if ( neighborBaseTileId >= 0x240u )
          {
            if ( neighborBaseTileId <= 0x240u )
            {
              bridgeApproachOverlayId = 904;
            }
            else if ( neighborBaseTileId >= 0x243u )
            {
              if ( neighborBaseTileId <= 0x243u )
              {
                bridgeApproachOverlayId = 903;
              }
              else if ( neighborBaseTileId == 581 )
              {
                bridgeApproachOverlayId = 906;
              }
            }
            else if ( neighborBaseTileId == 578 )
            {
              bridgeApproachOverlayId = 901;
            }
          }
          else if ( neighborBaseTileId <= 0x237u )
          {
            bridgeApproachOverlayId = 879;
          }
          else if ( neighborBaseTileId == 569 )
          {
            bridgeApproachOverlayId = 882;
          }
        }
        else if ( neighborBaseTileId >= 0x223u )
        {
          if ( neighborBaseTileId <= 0x223u )
          {
            bridgeApproachOverlayId = 927;
          }
          else if ( neighborBaseTileId >= 0x225u )
          {
            if ( neighborBaseTileId <= 0x225u )
            {
              bridgeApproachOverlayId = 930;
            }
            else if ( neighborBaseTileId == 564 )
            {
              bridgeApproachOverlayId = 880;
            }
          }
        }
        else if ( neighborBaseTileId >= 0x220u )
        {
          if ( neighborBaseTileId <= 0x220u )
          {
            bridgeApproachOverlayId = 928;
          }
          else if ( neighborBaseTileId == 546 )
          {
            bridgeApproachOverlayId = 925;
          }
        }
        targetTileRecordBase = gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn;
        savedTargetOverlay = *(unsigned __int16 *)(uintptr_t)(targetTileRecordBase + 4);
        appliedTargetOverlay = bridgeApproachOverlayId;
        *(_WORD *)(uintptr_t)(targetTileRecordBase + 4) = bridgeApproachOverlayId;
        *(_DWORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 10) = *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET);
      }
      if ( MapTile_IsBareBridgeCrossingRoadOverlayCandidate(targetRow, targetColumn) )
      {
        if ( !direction || direction == DIRECTION8_EAST )
        {
          bridgeCrossOverlayId = 881;
        }
        else if ( direction == DIRECTION8_NORTH || direction == DIRECTION8_SOUTH )
        {
          bridgeCrossOverlayId = 878;
        }
        crossingTileRecordBase = gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn;
        savedTargetOverlay = *(unsigned __int16 *)(uintptr_t)(crossingTileRecordBase + 4);
        appliedTargetOverlay = bridgeCrossOverlayId;
        *(_WORD *)(uintptr_t)(crossingTileRecordBase + 4) = bridgeCrossOverlayId;
        *(_DWORD *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * targetColumn + TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + 10) = *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET);
        roadOverlayTileId = *(_WORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * originRow + gameData + TILE_TERRAIN_RECORD_STRIDE * originColumn + 4);
      }
      moveCost = UnitStack_GetTileMoveCostOrZero((__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * unitIndex), targetRow, 145 * unitIndex, targetColumn);
      if ( MapTile_IsCastleFoundationTile(targetRow, targetColumn, 2) )
        moveCost = 0;
      if ( savedTargetOverlay )
        *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 4) = savedTargetOverlay;
      result = moveCost;
      if ( moveCost )
      {
        /* asm loc_424B38: edx = moveCost + 1 across sub_410010 (preserves edx). */
        v21 = moveCost + ROAD_BUILD_CONSTRUCTION_ACTION_POINTS;
        minActionPoints = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * unitIndex + gameData + UNIT_STACK_TABLE_OFFSET);
        if ( minActionPoints >= v21 )
        {
          if ( Map_GetTileSurfaceClassOrUnexplored(originRow, originColumn) == 185
            || Map_GetTileSurfaceClassOrUnexplored(targetRow, targetColumn) == 185 )
          {
            return 0;
          }
          else
          {
            *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * originRow + TILE_TERRAIN_RECORD_STRIDE * originColumn + 4) = roadOverlayTileId;
            neighborPrevOverlay = *(_WORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * targetRow + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 4);
            Map_RebuildRoadOverlayAtTile(targetRow, targetColumn);
            if ( neighborPrevOverlay != 0xFFFF )
            {
              /* asm loc_424B9B: ecx = 1400*targetRow, live across sub_423E90. */
              v23 = TILE_TERRAIN_ROW_STRIDE * targetRow;
              targetOverlayRecordBase = v23 + gameData + TILE_TERRAIN_RECORD_STRIDE * targetColumn;
              if ( *(unsigned __int16 *)(uintptr_t)(targetOverlayRecordBase + 4) == 0xFFFF )
                *(_WORD *)(uintptr_t)(targetOverlayRecordBase + 4) = neighborPrevOverlay;
            }
            if ( appliedTargetOverlay )
            {
              *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * targetRow + TILE_TERRAIN_RECORD_STRIDE * targetColumn + 4) = appliedTargetOverlay;
            }
            else
            {
              MapTile_HasNorthRoadConnection(targetRow, targetColumn);
              MapTile_HasSouthRoadConnection(targetRow, targetColumn);
              MapTile_HasWestRoadConnection(targetRow, targetColumn);
              MapTile_HasEastRoadConnection(targetRow, targetColumn);
            }
            g_SelectedUnitIndex = unitIndex;
            moveTargetColumn = targetColumn;
            unitStackByteOffset = UNIT_STACK_STRIDE * unitIndex;
            unitCurrentColumn = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * unitIndex + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET);
            result = (signed int)(intptr_t)Unit_MoveTrack(unitIndex, *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * unitIndex + UNIT_STACK_TABLE_OFFSET), targetRow, unitCurrentColumn, UNIT_STACK_STRIDE * unitIndex, moveTargetColumn);
            if ( result )
            {
              qmemcpy((void *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + unitStackByteOffset + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
              j__nfree_();
              /* asm loc_424E62: `mov edx, 1` is live into sub_410330. */
              v27 = 1;
              UnitStack_ExecuteQueuedPath(unitIndex, v27, unitCurrentColumn, unitStackByteOffset, a5);
              UnitStack_SpendActionPointsClamped((__int16 *)(uintptr_t)(unitStackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET), ROAD_BUILD_CONSTRUCTION_ACTION_POINTS, unitStackByteOffset, a5);
              WorldMap_RefreshUnitStatusPanel(unitStackByteOffset);
              return 1;
            }
          }
        }
        else
        {
          return 0;
        }
      }
      return result;
    default:
      return 0;
  }
}
// 42443D: variable 'v5' is possibly undefined
// 42462D: variable 'v36' is possibly undefined
// 4246C2: variable 'v30' is possibly undefined
// 42486C: variable 'v10' is possibly undefined
// 424B6F: variable 'v21' is possibly undefined
// 424C4C: variable 'v23' is possibly undefined
// 424E8E: variable 'v27' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 5202E4: using guessed type int gameData;

//----- (00424EC0) --------------------------------------------------------
signed int  UnitStack_MoveOneTileInDirection(int unitIndex, int direction, double a3)
{
  int unitStackByteOffset; // esi
  int unitStackRecordBase; // edx
  int originColumn; // ebx
  signed int result; // eax
  int v9; // edx

  g_SelectedUnitIndex = unitIndex;
  unitStackByteOffset = UNIT_STACK_STRIDE * unitIndex;
  unitStackRecordBase = gameData + UNIT_STACK_STRIDE * unitIndex;
  originColumn = *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET);
  result = (signed int)(intptr_t)Unit_MoveTrack(
                         unitIndex,
                         *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TABLE_OFFSET),
                         *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TABLE_OFFSET) + Map_NeighborDX[2 * direction],
                         originColumn,
                         unitIndex,
                         originColumn + Map_NeighborDY[2 * direction]);
  if ( result )
  {
    qmemcpy((void *)(uintptr_t)(unitStackByteOffset + gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_PATH_OFFSET), (const void *)(uintptr_t)result, UNIT_STACK_PATH_BYTES);
    j__nfree_();
    UnitStack_ExecuteQueuedPath(unitIndex, v9, originColumn, unitIndex, a3);
    WorldMap_RefreshUnitStatusPanel(unitIndex);
    return 1;
  }
  return result;
}
// 424F4D: variable 'v9' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (00424F70) --------------------------------------------------------
BOOL  Map_TileHasOwner(int row, int column)
{
  return *(unsigned __int16 *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * row + TILE_TERRAIN_RECORD_STRIDE * column + 4) != 0xFFFF;
}
// 5202E4: using guessed type int gameData;

//----- (00424FD0) --------------------------------------------------------
int Map_AutoUpgradeVillages(void)
{
  int result; // eax
  int columnIndex; // esi
  int columnTerrainOffset; // edx
  int columnTileMapOffset; // ebx
  int tileRecordPtr; // ecx
  int rowIndex; // [esp+4h] [ebp-2Ch]
  int i; // [esp+8h] [ebp-28h]
  int rowTerrainOffset; // [esp+Ch] [ebp-24h]

  rowIndex = 0;
  rowTerrainOffset = 0;
  for ( i = 0; ; i += TILE_ROW_STRIDE )
  {
    result = gameData;
    if ( rowIndex >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    columnIndex = 0;
    columnTerrainOffset = 0;
    columnTileMapOffset = 0;
    while ( columnIndex < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
    {
      if ( *(unsigned __int16 *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 4) >= 0x36Du
        && *(unsigned __int16 *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 4) <= 0x37Eu
        || *(unsigned __int16 *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 4) >= 0x385u
        && *(unsigned __int16 *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 4) <= 0x396u
        || *(unsigned __int16 *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 4) >= 0x39Du
        && *(unsigned __int16 *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 4) <= 0x3AEu )
      {
        tileRecordPtr = columnTerrainOffset + gameData + rowTerrainOffset;
        if ( *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET) >= (unsigned int)(*(_DWORD *)(uintptr_t)(tileRecordPtr + 10) + 30)
          && *(unsigned __int16 *)(uintptr_t)(columnTileMapOffset + i + gameData + TILE_MAP_OFFSET) == 0xFFFF )
        {
          *(_WORD *)(uintptr_t)(tileRecordPtr + 4) += 6;
          *(_DWORD *)(uintptr_t)(columnTerrainOffset + rowTerrainOffset + gameData + 10) = *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET);
        }
      }
      columnTerrainOffset += TILE_TERRAIN_RECORD_STRIDE;
      columnTileMapOffset += 2;
      ++columnIndex;
    }
    rowTerrainOffset += TILE_TERRAIN_ROW_STRIDE;
    ++rowIndex;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (004250F0) --------------------------------------------------------
int  RoadBuildMode_RequestExitAfterWidgetPress(int a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_RoadBuildModeExitRequested = 1;
  return result;
}
// 527C30: using guessed type int g_RoadBuildModeExitRequested;

//----- (00425110) --------------------------------------------------------
void RoadBuildMode_RequestExit(void)
{
  g_RoadBuildModeExitRequested = 1;
}
// 527C30: using guessed type int g_RoadBuildModeExitRequested;

//----- (00425120) --------------------------------------------------------
int  RoadBuildMode_HighlightBuildableAdjacentTile(int tileRow, int tileColumn)
{
  int unitStackRecordBase; // eax
  int northMarkerScreenY; // eax
  int directionIndex; // ebp
  int result; // eax
  int selectedUnitRecord; // eax
  int eastMarkerScreenX; // edx
  int unitStackEntry; // eax
  int southMarkerScreenY; // eax
  int westMarkerScreenY; // ecx
  int moveCost; // ecx

  WorldMap_EnsureBuilderWidgetTables();
  unitStackRecordBase = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
  if ( tileRow == *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TABLE_OFFSET) && tileColumn - *(__int16 *)(uintptr_t)(unitStackRecordBase + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET) == -1 )
  {
    northMarkerScreenY = (tileColumn - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
    g_RoadBuildModeNorthMarkerX = ((tileRow - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 57;
    directionIndex = 0;
    g_RoadBuildModeNorthMarkerY = northMarkerScreenY + 59 - g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex];
  }
  else
  {
    selectedUnitRecord = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
    if ( tileRow - *(__int16 *)(uintptr_t)(selectedUnitRecord + UNIT_STACK_TABLE_OFFSET) == 1 && tileColumn == *(__int16 *)(uintptr_t)(selectedUnitRecord + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET) )
    {
      directionIndex = 1;
      eastMarkerScreenX = ((tileRow - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
          + 42
          - g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex];
      g_RoadBuildModeEastMarkerY = ((tileColumn - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET)) << 6) + 41;
      g_RoadBuildModeEastMarkerX = eastMarkerScreenX;
    }
    else
    {
      unitStackEntry = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
      if ( tileRow == *(__int16 *)(uintptr_t)(unitStackEntry + UNIT_STACK_TABLE_OFFSET) && tileColumn - *(__int16 *)(uintptr_t)(unitStackEntry + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET) == 1 )
      {
        southMarkerScreenY = (tileColumn - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
        g_RoadBuildModeSouthMarkerX = ((tileRow - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6) + 57;
        directionIndex = 2;
        g_RoadBuildModeSouthMarkerY = g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex] + southMarkerScreenY + 26;
      }
      else
      {
        result = gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex;
        if ( tileRow - *(__int16 *)(uintptr_t)(result + UNIT_STACK_TABLE_OFFSET) != -1 )
          return result;
        result = *(__int16 *)(uintptr_t)(result + 147176);
        if ( tileColumn != result )
          return result;
        directionIndex = 3;
        westMarkerScreenY = (tileColumn - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_TOP_OFFSET)) << 6;
        g_RoadBuildModeWestMarkerX = g_RoadBuildModeMarkerBounceOffsets[g_RoadBuildModeAnimationFrameIndex]
                     + ((tileRow - *(_DWORD *)(uintptr_t)(gameData + MAP_VIEW_LEFT_OFFSET)) << 6)
                     + 75;
        g_RoadBuildModeWestMarkerY = westMarkerScreenY + 41;
      }
    }
  }
  if ( (MapTile_HasAlignedBridgeApproachRoadOverlay(
          *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TABLE_OFFSET),
          *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * g_SelectedUnitIndex + UNIT_STACK_TILE_COLUMN_TABLE_OFFSET),
          tileColumn,
          tileRow)
     || MapTile_IsBareBridgeCrossingRoadOverlayCandidate(tileRow, tileColumn))
    && UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET) >= ROAD_BUILD_BRIDGE_HIGHLIGHT_MIN_ACTION_POINTS
    || (moveCost = result = UnitStack_GetTileMoveCostOrZero((__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET), tileRow, gameData, tileColumn)) != 0
    && (result = MapTile_IsCastleFoundationTile(tileRow, tileColumn, 2)) == 0
    && (result = UnitStack_GetMinCurrentActionPoints(UNIT_STACK_STRIDE * g_SelectedUnitIndex + gameData + UNIT_STACK_TABLE_OFFSET), result >= moveCost + ROAD_BUILD_CONSTRUCTION_ACTION_POINTS)
    && (result = Map_GetTileSurfaceClassOrUnexplored(tileRow, tileColumn), result != 185) )
  {
    g_RoadBuildModeHasBuildTarget = 1;
    return UIWidget_RefreshActionButtonState((int)(intptr_t)&g_RoadBuildModeNorthMarkerX + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * directionIndex, 0);
  }
  return result;
}
// 511B58: using guessed type int g_SelectedUnitIndex;
// 514294: using guessed type int g_RoadBuildModeMarkerBounceOffsets[9];
// 5142B8: using guessed type int dword_5142B8;
// 5142BC: using guessed type int dword_5142BC;
// 5142ED: using guessed type int dword_5142ED;
// 5142F1: using guessed type int dword_5142F1;
// 514322: using guessed type int dword_514322;
// 514326: using guessed type int dword_514326;
// 514357: using guessed type int dword_514357;
// 51435B: using guessed type int dword_51435B;
// 5202E4: using guessed type int gameData;
// 527C34: using guessed type int dword_527C34;
// 527C38: using guessed type int g_RoadBuildModeAnimationFrameIndex;

//----- (004254E0) --------------------------------------------------------
int  RoadBuildMode_BuildInSelectedDirection(int widget, DWORD a2, double a3)
{
  /* asm 004254E0 picks `direction` (edx) from a jump table covering widget ids
   * 0x1B..0x1E only; its default arm falls through with whatever edx held on
   * entry, and edx is not a parameter of this __usercall -- indeterminate in
   * the original. Only the four road buttons reach this handler, so that arm is
   * unreachable; seed a value Road_Build's switch rejects (it returns 0 outside
   * {0,2,4,6}) instead of reading an uninitialised local. AMBIGUOUS-BY-ORIGINAL. */
  int direction = -1; // edx
  int widgetRecord; // ecx

  /* asm 004254E0: `mov ecx, eax` (= widget); after the animation call (which
   * pushes/pops ecx) `mov ecx, [ecx+10h]` reads widget->id as the selector. */
  widgetRecord = widget;
  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, widget);
  switch ( *(_DWORD *)(uintptr_t)(widgetRecord + 16) )
  {
    case 0x1B:
      direction = DIRECTION8_WEST;
      break;
    case 0x1C:
      direction = DIRECTION8_SOUTH;
      break;
    case 0x1D:
      direction = DIRECTION8_EAST;
      break;
    case 0x1E:
      direction = DIRECTION8_NORTH;
      break;
    default:
      break;
  }
  g_WorldMapTileOverlayDrawHook = 0;
  Road_Build(g_SelectedUnitIndex, direction, (char)(intptr_t)RoadBuildMode_HighlightBuildableAdjacentTile, a2, a3);
  g_WorldMapTileOverlayDrawHook = (int (__fastcall *)(_DWORD, _DWORD))RoadBuildMode_HighlightBuildableAdjacentTile;
  return WorldMap_RedrawViewport(1);
}
// 4254EA: variable 'v5' is possibly undefined
// 425510: variable 'v4' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 52698C: using guessed type int (__fastcall *dword_52698C)(_DWORD, _DWORD);
