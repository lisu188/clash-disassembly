/* Generated from src/recovered/buildings/0041D030_buildings.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (0042C560) --------------------------------------------------------
int  Battle_ApplyPeriodicDamageToSideUnits(int sideOwner)
{
  int slotIndex; // ebx
  __int16 *unitRecord; // ecx
  int result; // eax
  int apResilience; // esi
  int damage; // eax
  char newHealth; // ah

  slotIndex = 0;
  unitRecord = (__int16 *)(g_MapData + 852);
  do
  {
    while ( 1 )
    {
      result = *unitRecord;
      if ( result != -1 && *((unsigned __int8 *)unitRecord + 2) == sideOwner )
      {
        apResilience = (unsigned __int8)g_UnitTypeBaseActionPoints_512580[88 * result] - 15;
        damage = Rng_RandRange(25, 35) - apResilience;
        if ( damage < 0 )
          damage = 0;
        if ( damage > *((char *)unitRecord + 9) )
          LOBYTE(damage) = *((_BYTE *)unitRecord + 9);
        newHealth = *((_BYTE *)unitRecord + 9) - damage;
        *((_BYTE *)unitRecord + 9) = newHealth;
        result = newHealth;
        if ( result <= 0 )
          break;
      }
      ++slotIndex;
      unitRecord = (__int16 *)((char *)unitRecord + 31);
      if ( slotIndex >= 22 )
        return result;
    }
    *unitRecord = -1;
    ++slotIndex;
    unitRecord = (__int16 *)((char *)unitRecord + 31);
  }
  while ( slotIndex < 22 );
  return result;
}
// 42C5B3: variable 'v3' is possibly undefined
// 532048: using guessed type int g_MapData;

//----- (0042C600) --------------------------------------------------------
_BOOL2 UnitBattle_HandleManualRotateAndMoveInput()
{
  int IsKeyPressed; // eax
  int mapDataCw; // ecx
  int unitOffsetCw; // eax
  char facingCW; // dl
  int mapDataCcw; // ecx
  int unitOffsetCcw; // eax
  char facingCCW; // bl
  int unitRecord; // ecx
  int facing; // eax
  DWORD deltaY; // ebp
  int pathNode; // ecx
  int *movePath; // ebx
  unsigned __int16 requiredAp; // bx
  int v14; // ecx
  int v15; // ecx

  if ( Input_IsKeyPressed(34) )
  {
    if ( *(_DWORD *)(gameData + 147151) )
      goto LABEL_5;
    *(_DWORD *)(gameData + 147151) = 1;
    goto LABEL_4;
  }
  if ( *(_DWORD *)(gameData + 147151) )
  {
    *(_DWORD *)(gameData + 147151) = 0;
LABEL_4:
    UnitBattle_RedrawVisibleGrid();
  }
LABEL_5:
  IsKeyPressed = Input_IsKeyPressed(56);
  if ( IsKeyPressed )
  {
    if ( Input_IsKeyPressed(205) && g_SelectedUnitIndex != -1 )
    {
      mapDataCw = g_MapData;
      unitOffsetCw = 31 * g_SelectedUnitIndex;
      facingCW = *(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 855) + 1;
      *(_BYTE *)(g_MapData + unitOffsetCw + 855) = facingCW;
      *(_BYTE *)(mapDataCw + unitOffsetCw + 855) = facingCW & 7;
      UnitBattle_RedrawUnitNeighborhood(g_SelectedUnitIndex);
      while ( Input_IsKeyPressed(205) )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)g_RenderState, (char)g_RenderState);
      }
    }
    if ( Input_IsKeyPressed(203) && g_SelectedUnitIndex != -1 )
    {
      mapDataCcw = g_MapData;
      unitOffsetCcw = 31 * g_SelectedUnitIndex;
      facingCCW = *(_BYTE *)(g_MapData + 31 * g_SelectedUnitIndex + 855) - 1;
      *(_BYTE *)(g_MapData + unitOffsetCcw + 855) = facingCCW;
      *(_BYTE *)(mapDataCcw + unitOffsetCcw + 855) = facingCCW & 7;
      UnitBattle_RedrawUnitNeighborhood(g_SelectedUnitIndex);
      while ( Input_IsKeyPressed(203) )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        DD_Pump((int)g_RenderState, (char)g_RenderState);
      }
    }
    IsKeyPressed = Input_IsKeyPressed(200);
    if ( IsKeyPressed )
    {
      if ( g_SelectedUnitIndex != -1 )
      {
        unitRecord = 31 * g_SelectedUnitIndex + g_MapData + 852;
        facing = *(unsigned __int8 *)(unitRecord + 3);
        deltaY = Map_NeighborDY[2 * facing];
        movePath = UnitBattle_MoveTrack(
                g_SelectedUnitIndex,
                Map_NeighborDX[2 * facing] + *(unsigned __int16 *)(unitRecord + 4),
                unitRecord,
                deltaY + *(unsigned __int16 *)(unitRecord + 6),
                deltaY);
        LOWORD(IsKeyPressed) = 31 * g_SelectedUnitIndex;
        *(_DWORD *)(g_MapData + 31 * g_SelectedUnitIndex + 875) = movePath;
        if ( movePath )
        {
          requiredAp = HIWORD(*(_DWORD *)(*(_DWORD *)(pathNode + 23) + 4));
          if ( *(unsigned __int8 *)(pathNode + 8) < (int)requiredAp )
          {
            LOWORD(IsKeyPressed) = j__nfree_();
            *(_DWORD *)(v15 + 23) = 0;
          }
          else
          {
            Audio_PlayUnitMoveOrderSound(*(__int16 *)(g_MapData + 31 * g_SelectedUnitIndex + 852));
            LOWORD(IsKeyPressed) = UnitBattle_Move(g_SelectedUnitIndex, v14, requiredAp, deltaY);
          }
        }
      }
    }
  }
  return IsKeyPressed;
}
// 42C7D4: variable 'v11' is possibly undefined
// 42C815: variable 'v14' is possibly undefined
// 42C829: variable 'v15' is possibly undefined
// 511B58: using guessed type int g_SelectedUnitIndex;
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0042C840) --------------------------------------------------------
int __thiscall UnitBattle_UpdateViewportFromInputAndGetHoveredSlot(int this)
{
  unsigned int now; // eax
  unsigned int scroll_deadline; // edx
  int result; // eax
  int scrollCol; // edx
  int scrollRow; // edi
  int dragAnchorX; // esi
  int dragAnchorY; // ebx
  int deltaX; // eax
  int mapWidthTiles; // esi
  int mapHeightTiles; // ecx
  int deltaY; // eax

  (void)this;
  scroll_deadline = 16 - *(unsigned __int8 *)(gameData + 147171) + g_BattleViewportScrollRepeatDelayBias;
  now = Time_Now(0, 0);
  if ( now > scroll_deadline && !Input_IsKeyPressed(56) )
  {
    if ( Input_IsKeyPressed(203) )
    {
      scrollCol = *(_DWORD *)(g_MapData + 808);
      if ( scrollCol )
      {
        *(_DWORD *)(g_MapData + 808) = scrollCol - 1;
        UnitBattle_RedrawVisibleGrid();
      }
    }
    if ( Input_IsKeyPressed(205) && *(_DWORD *)(g_MapData + 808) + 7 < *(_DWORD *)(g_MapData + 804) )
    {
      ++*(_DWORD *)(g_MapData + 808);
      UnitBattle_RedrawVisibleGrid();
    }
    if ( Input_IsKeyPressed(200) )
    {
      scrollRow = *(_DWORD *)(g_MapData + 812);
      if ( scrollRow )
      {
        *(_DWORD *)(g_MapData + 812) = scrollRow - 1;
        UnitBattle_RedrawVisibleGrid();
      }
    }
    if ( Input_IsKeyPressed(208) && *(_DWORD *)(g_MapData + 812) + 7 < *(_DWORD *)(g_MapData + 800) )
    {
      ++*(_DWORD *)(g_MapData + 812);
      UnitBattle_RedrawVisibleGrid();
    }
  }
  result = *(__int16 *)(40
                      * (*(_DWORD *)(g_MapData + 808)
                       + (((g_MouseCursorRawX >> g_CursorCoordShift)
                         - 32
                         - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31, 6)
                          + (((g_MouseCursorRawX >> g_CursorCoordShift) - 32) >> 31 << 6))) >> 6))
                      + g_MapData
                      + 2
                      * ((((g_MouseCursorRawY >> g_CursorCoordShift)
                         - 16
                         - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31, 6)
                          + (((g_MouseCursorRawY >> g_CursorCoordShift) - 16) >> 31 << 6))) >> 6)
                       + *(_DWORD *)(g_MapData + 812))
                      + 1534);
  if ( result == -1 )
  {
    result = DD_IsLost((int)g_RenderState);
    if ( result )
    {
      Render_Pump();
      dragAnchorX = g_MouseCursorRawX >> g_CursorCoordShift;
      dragAnchorY = g_MouseCursorRawY >> g_CursorCoordShift;
      while ( DD_IsLost((int)g_RenderState) )
      {
        DD_Pump((int)g_RenderState, dragAnchorY);
        deltaX = (g_MouseCursorRawX >> g_CursorCoordShift) - dragAnchorX;
        if ( deltaX <= 0 )
          deltaX = dragAnchorX - (g_MouseCursorRawX >> g_CursorCoordShift);
        if ( deltaX < 8 )
        {
          deltaY = (g_MouseCursorRawY >> g_CursorCoordShift) - dragAnchorY;
          if ( deltaY <= 0 )
            deltaY = dragAnchorY - (g_MouseCursorRawY >> g_CursorCoordShift);
          if ( deltaY < 8 )
            continue;
        }
        *(_DWORD *)(g_MapData + 808) += ((g_MouseCursorRawX >> g_CursorCoordShift)
                                          - dragAnchorX
                                          - (__CFSHL__(((g_MouseCursorRawX >> g_CursorCoordShift) - dragAnchorX) >> 31, 3)
                                           + 8 * (((g_MouseCursorRawX >> g_CursorCoordShift) - dragAnchorX) >> 31))) >> 3;
        *(_DWORD *)(g_MapData + 812) += ((g_MouseCursorRawY >> g_CursorCoordShift)
                                          - dragAnchorY
                                          - (__CFSHL__(((g_MouseCursorRawY >> g_CursorCoordShift) - dragAnchorY) >> 31, 3)
                                           + 8 * (((g_MouseCursorRawY >> g_CursorCoordShift) - dragAnchorY) >> 31))) >> 3;
        if ( *(int *)(g_MapData + 808) < 0 )
          *(_DWORD *)(g_MapData + 808) = 0;
        mapWidthTiles = *(_DWORD *)(g_MapData + 804);
        if ( *(_DWORD *)(g_MapData + 808) + 7 > mapWidthTiles )
          *(_DWORD *)(g_MapData + 808) = mapWidthTiles - 7;
        if ( *(int *)(g_MapData + 812) < 0 )
          *(_DWORD *)(g_MapData + 812) = 0;
        mapHeightTiles = *(_DWORD *)(g_MapData + 800);
        if ( *(_DWORD *)(g_MapData + 812) + 7 > mapHeightTiles )
          *(_DWORD *)(g_MapData + 812) = mapHeightTiles - 7;
        UnitBattle_RedrawVisibleGrid();
        dragAnchorX = g_MouseCursorRawX >> g_CursorCoordShift;
        dragAnchorY = g_MouseCursorRawY >> g_CursorCoordShift;
      }
      UnitBattle_RedrawVisibleGrid();
      return Render_Present((int)g_RenderState);
    }
  }
  return result;
}
// 42C86E: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;
// 532040: using guessed type int dword_532040;
// 532048: using guessed type int g_MapData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
