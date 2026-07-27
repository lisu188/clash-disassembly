/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "units_internal.h"
#include "units_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../buildings/buildings_api.h"
#include "../battle/battle_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_LOCAL int Diagnostics_ForceAutoresolveEnabled (void);

//----- (0041A960) --------------------------------------------------------
int  UI_DrawSpecialUnitInfoPane(
        int paneLeft,
        int paneTop,
        int a3,
        unsigned __int8 *unitRecord,
        DWORD allocContext,
        int iconSpriteIndex)
{
  _DWORD *iconSet; // eax
  char ownerIndex; // bl
  int v9; // ecx
  _DWORD *animSet; // eax
  int v11; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  DWORD renderSpriteObj; // ebp
  int typeSprite; // eax
  int renderSpriteObj2; // edi
  char *unitName; // ebx
  int v18; // edx
  int v19; // ecx
  int lastFrameTime; // edi
  int animFrameIndex; // esi
  int v22; // ecx
  unsigned int currentTime; // eax
  unsigned int v24; // edx
  int v25; // ecx
  int animSprite; // eax
  int extraIconSprite; // eax
  _DWORD *finalSurface; // esi
  char unitInfoBuf[100]; // [esp+0h] [ebp-90h] BYREF
  _DWORD *iconSpriteSet; // [esp+64h] [ebp-2Ch] BYREF
  _DWORD *animSpriteSet; // [esp+68h] [ebp-28h] BYREF
  _DWORD *surface; // [esp+6Ch] [ebp-24h]
  int screenTop; // [esp+70h] [ebp-20h]
  int screenLeft; // [esp+74h] [ebp-1Ch]
  int animSpriteTop; // [esp+78h] [ebp-18h]
  int animSpriteLeft; // [esp+7Ch] [ebp-14h]

  screenLeft = paneLeft;
  screenTop = paneTop;
  iconSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, a3, (char)(intptr_t)unitRecord, allocContext);
  if ( iconSet )
    iconSet = DLXSpriteSet_Load(iconSet, (char)(intptr_t)unitRecord);
  iconSpriteSet = iconSet;
  ownerIndex = unitRecord[2];
  UI_BeginUnitInfo(unitInfoBuf, *unitRecord, ownerIndex);
  animSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v9, ownerIndex, allocContext);
  if ( animSet )
    animSet = DLXSpriteSet_Load(animSet, ownerIndex);
  animSpriteSet = animSet;
  Render_Pump();
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, v11, ownerIndex, allocContext);
  if ( Surface )
    Surface = Render_CreateSurface((int)(intptr_t)Surface, 201, 116);
  surface = Surface;
  Render_FillRect(0, Surface, (unsigned __int16)screenTop, (unsigned __int16)screenLeft, screenLeft + 200, screenTop + 115, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(7, allocContext);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)iconSpriteSet, 24);
  renderSpriteObj = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderSpriteObj + 52))(
    screenTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  switch ( *(_WORD *)unitRecord )
  {
    case UNIT_TYPE_GOLD_CARGO:
      iconSpriteIndex = 26;
      break;
    case UNIT_TYPE_PEASANT_CARGO:
      iconSpriteIndex = 25;
      break;
    case UNIT_TYPE_SPECIAL_FOOT_PERSONAGE:
    case UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE:
      iconSpriteIndex = 28;
      break;
    default:
      break;
  }
  typeSprite = DLX_GetSpriteForChar((int)(intptr_t)iconSpriteSet, iconSpriteIndex);
  renderSpriteObj2 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(renderSpriteObj2 + 52))(
    screenTop + 20,
    typeSprite,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(15, renderSpriteObj);
  UI_DrawTextFmt(renderSpriteObj2, screenLeft + 120, screenLeft + 173, screenTop + 30, 2, (int)(intptr_t)aD_19);
  Render_ReleaseSurface(7, renderSpriteObj);
  UI_DrawTextFmt(renderSpriteObj2, screenLeft + 15, screenLeft + 88, screenTop + 32, 2, (int)(intptr_t)aD_20);
  unitName = (**(&g_UnitTypeMetadataRecords + 22 * UNIT_STACK_TILE_ROW(unitRecord)))[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt(renderSpriteObj2, screenLeft + 64, screenLeft + 162, screenTop + 8, 3, (int)(intptr_t)unitName);
  if ( (unitRecord[13] & 8) != 0 )
  {
    extraIconSprite = DLX_GetSpriteForChar((int)(intptr_t)iconSpriteSet, 27);
    LOBYTE(unitName) = screenLeft - 105;
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
      screenTop + 52,
      extraIconSprite,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  lastFrameTime = Time_Now(v19, v18);
  animSpriteLeft = screenLeft + 11;
  animFrameIndex = 0;
  animSpriteTop = screenTop + 5;
  while ( DD_IsLost((int)(intptr_t)g_RenderState) || DD_IsFlipping((int)(intptr_t)g_RenderState) )
  {
    DD_Pump((int)(intptr_t)g_RenderState, (char)(intptr_t)unitName);
    currentTime = Time_Now(v22, lastFrameTime + 10);
    if ( v24 < currentTime )
    {
      lastFrameTime = Time_Now(v25, v24);
      animFrameIndex = (animFrameIndex + 1) % 8;
      animSprite = DLX_GetSpriteForChar((int)(intptr_t)animSpriteSet, animFrameIndex);
      LOBYTE(unitName) = animSpriteLeft;
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
        animSpriteTop,
        animSprite,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
    }
  }
  Render_FillRect(surface, 0, 0, 0, 0xC8u, 0x73u, screenLeft, screenTop);
  finalSurface = surface;
  Render_Present((int)(intptr_t)g_RenderState);
  if ( finalSurface )
    (*(void (**)(void))(uintptr_t)finalSurface[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&iconSpriteSet);
  return DLXSpriteSet_ReleaseAndClear((int *)&animSpriteSet);
}
// 41A99F: variable 'v9' is possibly undefined
// 41A9C2: variable 'v11' is possibly undefined
// 41AB96: variable 'v19' is possibly undefined
// 41AB96: variable 'v18' is possibly undefined
// 41ABD6: variable 'v22' is possibly undefined
// 41ABDD: variable 'v24' is possibly undefined
// 41ABDF: variable 'v25' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];
// 544CD8: using guessed type _DWORD g_RenderState[9];

// Test hook: CLASH95_FORCE_AUTORESOLVE routes combats through the authentic
// autoresolve path (CalculateBattleResult) even under direct-boot, where
// dword_51D01C otherwise forces manual tactical battles. This exercises the same
// recovered battle-resolution the real menu path uses, letting campaign-route
// probes resolve combats without hand-authored battlefield input.
CLASH95_LOCAL int Diagnostics_ForceAutoresolveEnabled(void)
{
  static int checked;
  static int enabled;
  if ( !checked )
  {
    const char *value = getenv("CLASH95_FORCE_AUTORESOLVE");
    enabled = value && *value;
    checked = 1;
  }
  return enabled;
}

//----- (0041AD20) --------------------------------------------------------
void  Unit_Attack(int attackerIndex, int defenderIndex, char a3, DWORD a4, double a5)
{
  int v5 CLASH95_UNUSED; // ecx
  int v6 CLASH95_UNUSED; // edx
  int v7 CLASH95_UNUSED; // edx
  __int16 *attackerStack; // ebp
  int attackerPlayerOffset; // eax
  BOOL bothHuman; // eax
  int v11 CLASH95_UNUSED; // ecx
  int xDistance; // eax
  int yDistance; // eax
  _DWORD *movePath; // eax
  int xDistanceAfterMove; // eax
  int yDistanceAfterMove; // eax
  int v17 CLASH95_UNUSED; // edx
  unsigned __int8 *attackerHasSpecial; // esi
  signed int attackerSquadCount; // eax
  unsigned __int8 *v20; // ebx
  signed int defenderSquadCount; // eax
  int v22 CLASH95_UNUSED; // ecx
  BOOL eitherHuman; // eax
  __int16 *defenderStackForPrompt; // ebx
  signed int attackerSquadCountForPrompt; // eax
  int v26 CLASH95_UNUSED; // ecx
  BOOL leadTroopsManually; // ecx
  BOOL defenderEliminated; // edx
  int v29; // ecx
  const char *transitionScript; // eax
  DWORD battleWinner; // edi
  signed int defenderSquadCountRemaining; // eax
  int useManualBattle; // ecx
  int v34; // ecx
  int v35 CLASH95_UNUSED; // edx
  int v36 CLASH95_UNUSED; // ecx
  unsigned __int8 mapThemeIndex; // al
  _DWORD *backgroundSpriteSet; // eax
  _DWORD *frameSpriteSet; // eax
  int v40 CLASH95_UNUSED; // ecx
  int needFullRedraw; // esi
  int v42; // ecx
  signed int attackerUnitCount; // eax
  _WORD *v44 CLASH95_UNUSED; // ecx
  int v45; // ecx
  int v46; // ecx
  int attackerSpawnStack; // eax
  int v48 CLASH95_UNUSED; // edx
  signed int v49 CLASH95_UNUSED; // ecx
  int v50 CLASH95_UNUSED; // edx
  int defenderSpawnStack; // eax
  int v52 CLASH95_UNUSED; // edx
  signed int v53 CLASH95_UNUSED; // ecx
  signed int defenderUnitCount; // [esp-10h] [ebp-368h]
  int defenderHasSpecialArg; // [esp-Ch] [ebp-364h]
  char attackerSpecialEntries[404]; // [esp+0h] [ebp-358h] BYREF
  unsigned __int8 defenderSpecialEntries[404]; // [esp+194h] [ebp-1C4h] BYREF
  int defenderStackIndex; // [esp+328h] [ebp-30h]
  unsigned __int8 *bothPlayersHuman; // [esp+32Ch] [ebp-2Ch]
  int defenderHasSpecial; // [esp+330h] [ebp-28h]
  int manualBattleFought; // [esp+334h] [ebp-24h]
  __int16 *defenderStack; // [esp+338h] [ebp-20h]
  int capturedCargoFlag; // [esp+33Ch] [ebp-1Ch]
  int attackerStackIndex; // [esp+340h] [ebp-18h]
  int autoresolveRan; // recovered autoresolve-return probe

  attackerStackIndex = attackerIndex;
  defenderStackIndex = defenderIndex;
  autoresolveRan = 0;
  Debug_Log(attackerIndex, a3, a4, (int)(intptr_t)aUnit_attackDD);
  Render_DrawSprite_v3(attackerStackIndex, a4);
  Render_DrawSprite_v3(defenderStackIndex, a4);
  attackerStack = (__int16 *)(uintptr_t)UNIT_STACK(attackerStackIndex);
  attackerPlayerOffset = PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4);
  defenderStack = (__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * defenderStackIndex + gameData + UNIT_STACK_TABLE_OFFSET);
  Diagnostics_TraceWorldMapActionEvent("unit_attack_enter", attackerStackIndex, defenderStackIndex, *defenderStack, defenderStack[1]);
  bothHuman = *(_DWORD *)(uintptr_t)(gameData + attackerPlayerOffset + 140051) && *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)defenderStack + 4) + 140051);
  bothPlayersHuman = (unsigned __int8 *)(uintptr_t)bothHuman;
  capturedCargoFlag = 0;
  if ( UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
  {
    xDistance = *attackerStack - *defenderStack;
    if ( xDistance <= 0 )
      xDistance = *defenderStack - *attackerStack;
    if ( xDistance <= 1 )
    {
      yDistance = attackerStack[1] - defenderStack[1];
      if ( yDistance <= 0 )
        yDistance = defenderStack[1] - attackerStack[1];
      if ( yDistance <= 1 )
        goto LABEL_22;
    }
    movePath = Unit_MoveTrackNearTile(attackerStackIndex, *defenderStack, (int)(intptr_t)attackerStack, defenderStack[1], (DWORD)(intptr_t)attackerStack);
    Diagnostics_TraceWorldMapActionEvent(movePath ? "unit_attack_track" : "unit_attack_no_track", attackerStackIndex, defenderStackIndex, *defenderStack, defenderStack[1]);
    if ( movePath )
    {
      Diagnostics_TraceWorldMapActionEvent(
        "unit_attack_track_state",
        attackerStackIndex,
        defenderStackIndex,
        movePath[0],
        movePath[0] > 0 ? HIWORD(movePath[movePath[0]]) : 0);
      qmemcpy(attackerStack + 158, movePath, UNIT_STACK_PATH_BYTES);
      UnitStack_ExecuteQueuedPath(attackerStackIndex, 1, (_BYTE)(intptr_t)attackerStack + 60, (DWORD)(intptr_t)attackerStack, a5);
      Diagnostics_TraceWorldMapActionEvent("unit_attack_after_track", attackerStackIndex, defenderStackIndex, *attackerStack, attackerStack[1]);
      Diagnostics_TraceWorldMapActionEvent(
        "unit_attack_after_track_state",
        attackerStackIndex,
        defenderStackIndex,
        *((_DWORD *)attackerStack + 79),
        UnitStack_GetMinCurrentActionPoints((intptr_t)attackerStack));
      if ( !*((_DWORD *)attackerStack + 79) && (unsigned int)attackerStack[3] <= 0x28 )
      {
        xDistanceAfterMove = *attackerStack - *defenderStack;
        if ( xDistanceAfterMove <= 0 )
          xDistanceAfterMove = *defenderStack - *attackerStack;
        if ( xDistanceAfterMove <= 1 )
        {
          yDistanceAfterMove = attackerStack[1] - defenderStack[1];
          if ( yDistanceAfterMove <= 0 )
            yDistanceAfterMove = defenderStack[1] - attackerStack[1];
          if ( yDistanceAfterMove <= 1 )
          {
LABEL_22:
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_adjacent",
              attackerStackIndex,
              defenderStackIndex,
              Unit_GetSquadCount((int)(intptr_t)attackerStack),
              Unit_GetSquadCount((int)(intptr_t)defenderStack));
            UnitStack_SetSpentTurnFlag((int)(intptr_t)attackerStack);
            UnitStack_AdjustFatigueByPredicate(attackerStack, 10, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
            UnitStack_AdjustFatigueByPredicate(defenderStack, 10, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
            if ( ACTIVE_MISSION_INDEX == 15 )
              Mission_MarkObjective15CompleteOnAttack(*((unsigned __int8 *)attackerStack + 4), *((unsigned __int8 *)defenderStack + 4));
            if ( ACTIVE_MISSION_INDEX == 5 )
              Mission05_MarkFailureOnFriendlyAttack(*((unsigned __int8 *)attackerStack + 4), *((unsigned __int8 *)defenderStack + 4));
            attackerHasSpecial = (unsigned __int8 *)(uintptr_t)UnitStack_HasSpecialPersonageUnits((intptr_t)attackerStack);
            defenderHasSpecial = UnitStack_HasSpecialPersonageUnits((intptr_t)defenderStack);
            attackerSquadCount = Unit_GetSquadCount((int)(intptr_t)attackerStack);
            UnitSlots_ExtractSpecialEntries((char *)attackerStack + 6, attackerSquadCount, attackerSpecialEntries);
            v20 = defenderSpecialEntries;
            defenderSquadCount = Unit_GetSquadCount((int)(intptr_t)defenderStack);
            UnitSlots_ExtractSpecialEntries((char *)defenderStack + 6, defenderSquadCount, (char *)defenderSpecialEntries);
            eitherHuman = *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + gameData + 140051)
               || *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)defenderStack + 4) + gameData + 140051);
            if ( eitherHuman && Unit_GetSquadCount((int)(intptr_t)attackerStack) && Unit_GetSquadCount((int)(intptr_t)defenderStack) )
            {
              defenderStackForPrompt = defenderStack;
              defenderSquadCount = Unit_GetSquadCount((int)(intptr_t)defenderStack);
              v20 = (unsigned __int8 *)(defenderStackForPrompt + 3);
              attackerSquadCountForPrompt = Unit_GetSquadCount((int)(intptr_t)attackerStack);
              leadTroopsManually = UI_PromptLeadTroopsPersonally((int)(intptr_t)(attackerStack + 3), attackerSquadCountForPrompt, defenderSquadCount, (int)(intptr_t)v20, (DWORD)(intptr_t)attackerStack, (int)(intptr_t)(attackerStack + 3), 0) == 0;
            }
            else
            {
              leadTroopsManually = 0;
            }
            useManualBattle = (g_ManualTacticalBattleEnabled || leadTroopsManually) && !Diagnostics_ForceAutoresolveEnabled();
            if ( useManualBattle )
            {
              if ( *((_BYTE *)attackerStack + 720) )
              {
                defenderEliminated = Unit_GetSquadCount((int)(intptr_t)defenderStack) == 0;
                transitionScript = aAtak_zas;
              }
              else
              {
                defenderEliminated = Unit_GetSquadCount((int)(intptr_t)defenderStack) == 0;
                transitionScript = aBattle;
              }
              Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_transition_enter", attackerStackIndex, defenderStackIndex, defenderEliminated, 0);
              Win_PlayModeChangeFrameTransition(transitionScript, defenderEliminated, v29, (char)(intptr_t)v20, (DWORD)(intptr_t)attackerStack);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_transition_return", attackerStackIndex, defenderStackIndex, defenderEliminated, 0);
            }
            battleWinner = 0;
            defenderSquadCountRemaining = Unit_GetSquadCount((int)(intptr_t)defenderStack);
            manualBattleFought = 0;
            if ( defenderSquadCountRemaining <= 0 )
            {
LABEL_48:
              if ( battleWinner )
              {
                if ( battleWinner == 1 )
                {
                  UnitSlots_AppendEntries((char *)defenderStack + 6, (char *)defenderSpecialEntries);
                  if ( *(__int16 *)attackerSpecialEntries != -1 )
                  {
                    defenderSpawnStack = Unit_CreateNearbyUnitGroup(*defenderStack, defenderStack[1], (unsigned __int8 *)attackerSpecialEntries, a5);
                    if ( (UnitStack_HasPeasantCargo(defenderSpawnStack) || UnitStack_HasGoldCargo(defenderSpawnStack))
                      && *(unsigned __int8 *)(uintptr_t)(defenderSpawnStack + 4) == *(_DWORD *)(uintptr_t)(gameData + VIEWED_PLAYER_INDEX_OFFSET) )
                    {
                      capturedCargoFlag = 1;
                    }
                    UnitStack_CaptureDefeatedStack(defenderStack, defenderSpawnStack, defenderSpawnStack, (int)(intptr_t)attackerSpecialEntries, a5);
                  }
                  UnitStack_AdjustMoraleByPredicate(attackerStack, -5, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(defenderStack, 4, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)(intptr_t)attackerStack, a5);
                  --*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  ++*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)defenderStack + 4) + 141441);
                }
                else if ( battleWinner == 2 )
                {
                  UnitSlots_AppendEntries((char *)attackerStack + 6, attackerSpecialEntries);
                  if ( *(__int16 *)attackerSpecialEntries != -1 )
                  {
                    attackerSpawnStack = Unit_CreateNearbyUnitGroup(*attackerStack, attackerStack[1], defenderSpecialEntries, a5);
                    if ( (UnitStack_HasPeasantCargo(attackerSpawnStack) || UnitStack_HasGoldCargo(attackerSpawnStack))
                      && *(unsigned __int8 *)(uintptr_t)(attackerSpawnStack + 4) == *(_DWORD *)(uintptr_t)(gameData + VIEWED_PLAYER_INDEX_OFFSET) )
                    {
                      capturedCargoFlag = 1;
                    }
                    UnitStack_CaptureDefeatedStack(attackerStack, attackerSpawnStack, attackerSpawnStack, (int)(intptr_t)defenderSpecialEntries, a5);
                  }
                  UnitStack_AdjustMoraleByPredicate(defenderStack, -5, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_SubtractActionPointsFloorZero(attackerStack, 10, (DWORD)(intptr_t)attackerStack, a5);
                  ++*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  --*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)defenderStack + 4) + 141441);
                }
                goto LABEL_52;
              }
LABEL_49:
              UnitSlots_AppendEntries((char *)attackerStack + 6, attackerSpecialEntries);
              UnitSlots_AppendEntries((char *)defenderStack + 6, (char *)defenderSpecialEntries);
              if ( UnitStack_HasNormalCombatUnits((intptr_t)defenderStack) || !UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
              {
                if ( UnitStack_HasNormalCombatUnits((intptr_t)defenderStack) && !UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
                {
                  if ( (unsigned int)attackerStack[3] <= 0x28 )
                  {
                    if ( (UnitStack_HasPeasantCargo((int)(intptr_t)attackerStack) || UnitStack_HasGoldCargo((int)(intptr_t)attackerStack))
                      && *((unsigned __int8 *)defenderStack + 4) == *(_DWORD *)(uintptr_t)(gameData + VIEWED_PLAYER_INDEX_OFFSET) )
                    {
                      capturedCargoFlag = 1;
                    }
                    UnitStack_CaptureDefeatedStack(defenderStack, (signed int)(intptr_t)attackerStack, v46, (int)(intptr_t)v20, a5);
                  }
                  v20 = (unsigned __int8 *)CSyncObject_Unlock;
                  UnitStack_AdjustMoraleByPredicate(defenderStack, 4, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)(intptr_t)attackerStack, a5);
                  UnitStack_CycleAllSlotOrders(defenderStack, (DWORD)(intptr_t)attackerStack, a5);
                  --*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  ++*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)defenderStack + 4) + 141441);
                }
              }
              else
              {
                if ( (unsigned int)defenderStack[3] <= 0x28 )
                {
                  if ( (UnitStack_HasPeasantCargo((int)(intptr_t)defenderStack) || UnitStack_HasGoldCargo((int)(intptr_t)defenderStack))
                    && *((unsigned __int8 *)attackerStack + 4) == *(_DWORD *)(uintptr_t)(gameData + VIEWED_PLAYER_INDEX_OFFSET) )
                  {
                    capturedCargoFlag = 1;
                  }
                  UnitStack_CaptureDefeatedStack(attackerStack, (signed int)(intptr_t)defenderStack, v45, (int)(intptr_t)v20, a5);
                }
                v20 = (unsigned __int8 *)CSyncObject_Unlock;
                UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)(intptr_t)attackerStack, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)attackerStack, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)attackerStack, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)attackerStack, a5);
                ++*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + 141441);
                --*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)defenderStack + 4) + 141441);
              }
LABEL_52:
              if ( attackerStack[3] == -1 )
                Rules_UnlinkArmyFact(attackerStack, a5);
              if ( defenderStack[3] == -1 )
                Rules_UnlinkArmyFact(defenderStack, a5);
              WorldMap_SyncSelectionForHumanPlayer((DWORD)(intptr_t)attackerStack);
              needFullRedraw = manualBattleFought;
              UnitStackSelection_RefreshForSelectedStack((DWORD)(intptr_t)attackerStack);
              if ( needFullRedraw )
                WorldMap_RenderHook((DWORD)(intptr_t)attackerStack);
              else
                WorldMap_RedrawViewport(1);
              if ( capturedCargoFlag )
                Win_PlayModeChangeFrameTransition(aChlop, 1, v42, (char)(intptr_t)v20, (DWORD)(intptr_t)attackerStack);
              if ( autoresolveRan )
                Diagnostics_TraceWorldMapActionEvent("unit_attack_autoresolve_return", attackerStackIndex, defenderStackIndex, *attackerStack, attackerStack[1]);
              Render_DrawSprite_v3(attackerStackIndex, (DWORD)(intptr_t)attackerStack);
              Render_DrawSprite_v3(defenderStackIndex, (DWORD)(intptr_t)attackerStack);
              return;
            }
            if ( !useManualBattle )
            {
              defenderHasSpecialArg = defenderHasSpecial;
              v20 = attackerHasSpecial;
              defenderUnitCount = Unit_GetSquadCount((int)(intptr_t)defenderStack);
              attackerUnitCount = Unit_GetSquadCount((int)(intptr_t)attackerStack);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_autoresolve", attackerStackIndex, defenderStackIndex, attackerUnitCount, defenderUnitCount);
              autoresolveRan = 1;
              CalculateBattleResult(attackerStack + 3, attackerUnitCount, defenderStack + 3, (int)(intptr_t)attackerHasSpecial, (DWORD)(intptr_t)attackerStack, defenderUnitCount, defenderHasSpecialArg, 0, 0);
              Diagnostics_TraceWorldMapActionEvent(
                "unit_attack_autoresolve_done",
                attackerStackIndex,
                defenderStackIndex,
                Unit_GetSquadCount((int)(intptr_t)attackerStack),
                Unit_GetSquadCount((int)(intptr_t)defenderStack));
              goto LABEL_49;
            }
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_prepare", attackerStackIndex, defenderStackIndex, useManualBattle, 0);
            Render_Pump();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_render_pump", attackerStackIndex, defenderStackIndex, 0, 0);
            Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_unlock", attackerStackIndex, defenderStackIndex, 0, 0);
            DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_frame_free", attackerStackIndex, defenderStackIndex, 0, 0);
            BuildingSpriteCache_Clear();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_building_cache_clear", attackerStackIndex, defenderStackIndex, 0, 0);
            UnitSpriteCache_FreeAllEntries(v34, (DWORD)(intptr_t)attackerStack);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_unit_cache_clear", attackerStackIndex, defenderStackIndex, 0, 0);
            CSS_EmptySampleCache();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_sample_clear", attackerStackIndex, defenderStackIndex, 0, 0);
            TextSprite_ReleaseAllResourceSlots();
            Diagnostics_TraceWorldMapActionEvent("unit_attack_manual_after_text_enddraw", attackerStackIndex, defenderStackIndex, 0, 0);
            defenderUnitCount = Unit_GetSquadCount((int)(intptr_t)defenderStack);
            attackerUnitCount = Unit_GetSquadCount((int)(intptr_t)attackerStack);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_battle_enter", attackerStackIndex, defenderStackIndex, attackerUnitCount, defenderUnitCount);
            Battle_ResetInputScriptReader();
            battleWinner = Battle_RunTacticalCombat(
                    (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * attackerStackIndex),
                    (__int16 *)(uintptr_t)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * defenderStackIndex),
                    (int)(intptr_t)attackerHasSpecial,
                    0,
                    (DWORD)(intptr_t)attackerStack,
                    defenderHasSpecial);
            Diagnostics_TraceWorldMapActionEvent("unit_attack_battle_return", attackerStackIndex, defenderStackIndex, battleWinner, 0);
            mapThemeIndex = *(_BYTE *)(uintptr_t)(gameData + MAP_THEME_INDEX_OFFSET);
            if ( g_WorldMapBackgroundSpriteSet )
              DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
            if ( mapThemeIndex == 0 )
            {
              backgroundSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)attackerStack);
              if ( backgroundSpriteSet )
                backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, "backgr1.s32");
              g_WorldMapBackgroundSpriteSet = (int)(intptr_t)backgroundSpriteSet;
            }
            else if ( mapThemeIndex == 1 )
            {
              backgroundSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)attackerStack);
              if ( backgroundSpriteSet )
                backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, "backgr2.s32");
              g_WorldMapBackgroundSpriteSet = (int)(intptr_t)backgroundSpriteSet;
            }
            else if ( mapThemeIndex == 2 )
            {
              backgroundSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)attackerStack);
              if ( backgroundSpriteSet )
                backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, "backgr3.s32");
              g_WorldMapBackgroundSpriteSet = (int)(intptr_t)backgroundSpriteSet;
            }
            frameSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)attackerStack);
            if ( frameSpriteSet )
              frameSpriteSet = DLXSpriteSet_Load(frameSpriteSet, "frame.s32");
            g_ActiveUiSpriteSet = (int)(intptr_t)frameSpriteSet;
            Tooltip_CaptureBackdrop(160, 473, 3, 467, 76);
            Palette_LoadOrBuildBlendLookupTable(aMainmap_0, g_MapPalettePtr, 1, (DWORD)(intptr_t)attackerStack);
            manualBattleFought = 1;
            /*
             * Original Unit_Attack (clash95.asm 42155-42163):
             *   mov ebx,[esp+358h+var_2C]   ; both players human
             *   call sub_435ED0             ; Palette_LoadOrBuildBlendLookupTable
             *   mov [esp+358h+var_24], ecx  ; manualBattleFought = 1
             *   test ebx, ebx
             *   jz short loc_41B1F7
             *   call UI_LoadTurnBannerGfx   ; __usercall(char@<bl>, DWORD@<ebp>)
             * i.e. after a hot-seat manual battle the turn-intro banner screen
             * is repainted.  The raw decompile dropped the call and left
             * bothPlayersHuman unused; the sibling Unit_AttackBuilding
             * (asm 42968-42974) kept it.
             */
            if ( bothPlayersHuman )
              UI_LoadTurnBannerGfx(1, (DWORD)(intptr_t)attackerStack);
            goto LABEL_48;
          }
        }
      }
    }
  }
}
// 41AEB1: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41B401: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41B4CA: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 41AD4C: variable 'v5' is possibly undefined
// 41AD5A: variable 'v6' is possibly undefined
// 41AD82: variable 'v7' is possibly undefined
// 41AE60: variable 'v11' is possibly undefined
// 41AF0E: variable 'v17' is possibly undefined
// 41AFC1: variable 'v22' is possibly undefined
// 41B03E: variable 'v26' is possibly undefined
// 41B085: variable 'v29' is possibly undefined
// 41B0A9: variable 'v33' is possibly undefined
// 41B0D7: variable 'v34' is possibly undefined
// 41B110: variable 'v35' is possibly undefined
// 41B17B: variable 'v36' is possibly undefined
// 41B1E7: variable 'v40' is possibly undefined
// 41B2B0: variable 'v42' is possibly undefined
// 41B3DB: variable 'v44' is possibly undefined
// 41B442: variable 'v45' is possibly undefined
// 41B50E: variable 'v46' is possibly undefined
// 41B5F0: variable 'v49' is possibly undefined
// 41B652: variable 'v50' is possibly undefined
// 41B6E9: variable 'v53' is possibly undefined
// 41B798: variable 'v52' is possibly undefined
// 41B7AC: variable 'v48' is possibly undefined
// 51D01C: using guessed type int dword_51D01C;
// 5202BC: using guessed type int dword_5202BC;
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;
// 5202F4: using guessed type int dword_5202F4;

//----- (0041B7D0) --------------------------------------------------------
void  Unit_AttackBuilding(int attackerIndex, int buildingIndexArg, char a3, DWORD a4, double a5)
{
  unsigned __int8 *buildingRecord; // ebp
  BOOL bothHumanControlled; // eax
  int xDelta; // eax
  int buildingY; // edx
  int yDelta; // eax
  const void *approachTrack; // eax
  int attackerHasSpecial; // edi
  BOOL eitherHuman; // eax
  signed int attackerSquadCount; // eax
  signed int useManualBattle; // esi
  signed int compactedSquadCount; // eax
  int garrisonCount; // eax
  int garrisonSlot; // ecx
  int buildingRecordOffset; // ebx
  int v33; // ecx
  unsigned __int8 *buildingRecordPtr; // ebx
  int v35 CLASH95_UNUSED; // ecx
  DWORD battleWinner; // esi
  unsigned __int8 mapThemeIndex; // al
  _DWORD *backgroundSpriteSet; // eax
  _DWORD *frameSpriteSet; // eax
  char v40; // bl
  int v41 CLASH95_UNUSED; // ecx
  DWORD savedRefreshIndex; // ebp
  __int16 *attackerSlots; // esi
  signed int autoresolveSquadCount; // eax
  _WORD *v45; // ecx
  int v48; // edx
  int defenderGarrisonCount; // [esp-10h] [ebp-364h]
  int defenderSpecialFlag; // [esp-Ch] [ebp-360h]
  int defenderBuildingRecord; // [esp-8h] [ebp-35Ch]
  char attackerSpecialEntries[404]; // [esp+0h] [ebp-354h] BYREF
  char garrisonSpecialEntries[404]; // [esp+194h] [ebp-1C0h] BYREF
  BOOL bothPlayersHuman; // [esp+328h] [ebp-2Ch]
  int buildingHasSpecial; // [esp+32Ch] [ebp-28h]
  DWORD selectionRefreshIndex; // [esp+330h] [ebp-24h]
  int buildingIndex; // [esp+334h] [ebp-20h]
  int attackerStackIndex; // [esp+338h] [ebp-1Ch]
  __int16 *attackerStack; // [esp+33Ch] [ebp-18h]

  attackerStackIndex = attackerIndex;
  buildingIndex = buildingIndexArg;
  Debug_Log(attackerIndex, a3, a4, (int)(intptr_t)aUnit_attackbui);
  Render_DrawSprite_v3(attackerStackIndex, BUILDING_RECORD_SIZE * buildingIndex);
  attackerStack = (__int16 *)(uintptr_t)UNIT_STACK(attackerStackIndex);
  buildingRecord = (unsigned __int8 *)(uintptr_t)(UNIT_RECORD(buildingIndex));
  bothHumanControlled = PLAYER_HAS_HUMAN_CONTROLLER(UNIT_STACK_OWNER_INDEX((int)(intptr_t)attackerStack)) && PLAYER_HAS_HUMAN_CONTROLLER(buildingRecord[2]);
  bothPlayersHuman = bothHumanControlled;
  if ( UnitStack_HasNormalCombatUnits((intptr_t)attackerStack) )
  {
    xDelta = *attackerStack - *buildingRecord;
    if ( xDelta <= 0 )
      xDelta = *buildingRecord - *attackerStack;
    if ( xDelta <= 1 )
    {
      buildingY = buildingRecord[1];
      yDelta = attackerStack[1] - buildingY;
      if ( yDelta <= 0 )
        yDelta = buildingY - attackerStack[1];
      if ( yDelta <= 1 )
        goto LABEL_15;
    }
    approachTrack = (const void *)Building_GenerateApproachTrack(attackerStackIndex, buildingIndex, 0, 0, 0);
    if ( approachTrack )
    {
      qmemcpy(attackerStack + 158, approachTrack, UNIT_STACK_PATH_BYTES);
      UnitStack_ExecuteQueuedPath(attackerStackIndex, 1, (_BYTE)(intptr_t)attackerStack + 60, (DWORD)(intptr_t)buildingRecord, a5);
      if ( !*((_DWORD *)attackerStack + 79) )
      {
LABEL_15:
        if ( UnitStack_GetMinCurrentActionPoints((intptr_t)attackerStack) >= 5 )
        {
          UnitStack_SpendActionPointsByIndexClamped(attackerStackIndex, 5, (DWORD)(intptr_t)buildingRecord, a5);
          UnitStack_SetSpentTurnFlag((int)(intptr_t)attackerStack);
          UnitStack_AdjustFatigueByPredicate(attackerStack, 10, UnitSlot_PredicateAlways, (DWORD)(intptr_t)buildingRecord, a5);
          if ( ACTIVE_MISSION_INDEX == 15 )
            Mission_MarkObjective15CompleteOnAttack(*((unsigned __int8 *)attackerStack + 4), buildingRecord[2]);
          if ( ACTIVE_MISSION_INDEX == 5 )
            Mission05_MarkFailureOnFriendlyAttack(*((unsigned __int8 *)attackerStack + 4), buildingRecord[2]);
          attackerHasSpecial = UnitStack_HasSpecialPersonageUnits((intptr_t)attackerStack);
          buildingHasSpecial = Building_HasSpecialPersonageGarrisonEntries((int)(intptr_t)buildingRecord);
          eitherHuman = PLAYER_HAS_HUMAN_CONTROLLER(UNIT_STACK_OWNER_INDEX((int)(intptr_t)attackerStack)) || PLAYER_HAS_HUMAN_CONTROLLER(buildingRecord[2]);
          if ( !eitherHuman || Building_CountGarrison((int)(intptr_t)buildingRecord) == Building_CountNonCombatGarrisonEntries((int)(intptr_t)buildingRecord) )
          {
            useManualBattle = 0;
          }
          else
          {
            attackerSquadCount = Unit_GetSquadCount((int)(intptr_t)attackerStack);
            useManualBattle = UI_PromptLeadTroopsPersonally((int)(intptr_t)(attackerStack + 3), attackerSquadCount, 12, (int)(intptr_t)(buildingRecord + 18), (DWORD)(intptr_t)buildingRecord, attackerHasSpecial, 1) == 0;
          }
          Diagnostics_TraceWorldMapActionEvent("unit_attack_building_prompt_result", attackerStackIndex, buildingIndex, useManualBattle, g_ManualTacticalBattleEnabled);
          if ( g_ManualTacticalBattleEnabled && !Diagnostics_ForceAutoresolveEnabled() )
          {
            useManualBattle = 1;
          }
          else if ( !useManualBattle )
          {
LABEL_28:
            selectionRefreshIndex = 0;
            if ( !Building_CountGarrison(UNIT_RECORD(buildingIndex)) )
            {
              UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)(intptr_t)buildingRecord, a5);
              UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)buildingRecord, a5);
              UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)buildingRecord, a5);
              UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)buildingRecord, a5);
              Unit_CaptureBuilding(attackerStackIndex, buildingIndex, 0, useManualBattle, a5);
              ++*(_WORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + gameData + 141441);
              --*(_WORD *)(uintptr_t)(PLAYER_DATA_STRIDE * buildingRecord[2] + gameData + 141441);
LABEL_47:
              if ( attackerStack[3] == -1 )
                Rules_UnlinkArmyFact(attackerStack, a5);
              WorldMap_SyncSelectionForHumanPlayer((DWORD)(intptr_t)buildingRecord);
              savedRefreshIndex = selectionRefreshIndex;
              UnitStackSelection_RefreshForSelectedStack(selectionRefreshIndex);
              if ( savedRefreshIndex )
                WorldMap_RenderHook(savedRefreshIndex);
              Render_DrawSprite_v3(attackerStackIndex, savedRefreshIndex);
              return;
            }
            Building_CompactGarrison(buildingRecord, (unsigned __int8 *)attackerStack, a5);
            compactedSquadCount = Unit_GetSquadCount((int)(intptr_t)attackerStack);
            UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)attackerStack + 6, compactedSquadCount, attackerSpecialEntries);
            garrisonCount = Building_CountGarrison((int)(intptr_t)buildingRecord);
            UnitSlots_ExtractSpecialEntriesForBuildingAttack((char *)buildingRecord + 18, garrisonCount, garrisonSpecialEntries);
            Building_CompactGarrison(buildingRecord, buildingRecord + 18, a5);
            for ( garrisonSlot = 0; garrisonSlot < 12; ++garrisonSlot )
            {
              Building_ClearGarrisonTrainingTimer((int)(intptr_t)buildingRecord, garrisonSlot);
              Building_ClearGarrisonRepairTimer((int)(intptr_t)buildingRecord, garrisonSlot);
            }
            buildingRecordOffset = BUILDING_RECORD_SIZE * buildingIndex;
            if ( !useManualBattle )
            {
              defenderBuildingRecord = buildingRecordOffset + gameData + BUILDING_TABLE_OFFSET;
              defenderSpecialFlag = buildingHasSpecial;
              defenderGarrisonCount = Building_CountGarrison(defenderBuildingRecord);
              attackerSlots = attackerStack + 3;
              v40 = (char)attackerHasSpecial;
              autoresolveSquadCount = Unit_GetSquadCount((int)(intptr_t)attackerStack);
              Diagnostics_TraceWorldMapActionEvent("unit_attack_building_autoresolve", attackerStackIndex, buildingIndex, autoresolveSquadCount, defenderGarrisonCount);
              CalculateBattleResult(attackerSlots, autoresolveSquadCount, v45, attackerHasSpecial, (DWORD)(intptr_t)buildingRecord, defenderGarrisonCount, defenderSpecialFlag, defenderBuildingRecord, 0);
              Diagnostics_TraceWorldMapActionEvent(
                "unit_attack_building_autoresolve_done",
                attackerStackIndex,
                buildingIndex,
                Unit_GetSquadCount((int)(intptr_t)attackerStack),
                Building_CountGarrison(defenderBuildingRecord));
              battleWinner = 0;
LABEL_42:
              UnitSlots_AppendEntriesForBuildingAttack((char *)attackerStack + 6, attackerSpecialEntries);
              if ( battleWinner )
              {
                if ( battleWinner == 1 )
                {
                  UnitStack_AdjustMoraleByPredicate(attackerStack, -5, UnitSlot_PredicateAlways, (DWORD)(intptr_t)buildingRecord, a5);
                  --*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + 141441);
                  ++*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * buildingRecord[2] + 141441);
                  Building_AdjustAllGarrisonMoraleByDelta((int)(intptr_t)buildingRecord, 4);
                  Building_CycleAllGarrisonOrdersOnce((int)(intptr_t)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)(intptr_t)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)(intptr_t)buildingRecord);
                }
              }
              else if ( Building_CountGarrison(UNIT_RECORD(buildingIndex))
                     || !UnitStack_HasNormalCombatUnits(UNIT_STACK_STRIDE * attackerStackIndex + gameData + UNIT_STACK_TABLE_OFFSET) )
              {
                if ( Building_CountGarrison(UNIT_RECORD(buildingIndex))
                  && !UnitStack_HasNormalCombatUnits(UNIT_STACK_STRIDE * attackerStackIndex + gameData + UNIT_STACK_TABLE_OFFSET) )
                {
                  UnitSlots_AppendEntriesForBuildingAttack((char *)buildingRecord + 18, garrisonSpecialEntries);
                  UnitStack_KillByIndex(attackerStackIndex, v40, (DWORD)(intptr_t)buildingRecord, a5);
                  --*(_WORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(v48 + 4) + 141441);
                  ++*(_WORD *)(uintptr_t)(PLAYER_DATA_STRIDE * buildingRecord[2] + gameData + 141441);
                  Building_AdjustAllGarrisonMoraleByDelta((int)(intptr_t)buildingRecord, 4);
                  Building_CycleAllGarrisonOrdersOnce((int)(intptr_t)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)(intptr_t)buildingRecord);
                  Building_CycleAllGarrisonOrdersOnce((int)(intptr_t)buildingRecord);
                }
                else if ( !Building_CountGarrison(UNIT_RECORD(buildingIndex))
                       && !UnitStack_HasNormalCombatUnits(UNIT_STACK_STRIDE * attackerStackIndex + gameData + UNIT_STACK_TABLE_OFFSET) )
                {
                  UnitStack_KillByIndex(attackerStackIndex, v40, (DWORD)(intptr_t)buildingRecord, a5);
                }
              }
              else
              {
                UnitStack_AdjustMoraleByPredicate(attackerStack, 4, UnitSlot_PredicateAlways, (DWORD)(intptr_t)buildingRecord, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)buildingRecord, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)buildingRecord, a5);
                UnitStack_CycleAllSlotOrders(attackerStack, (DWORD)(intptr_t)buildingRecord, a5);
                Unit_CaptureBuilding(attackerStackIndex, buildingIndex, 0, 0, a5);
                ++*(_WORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)attackerStack + 4) + gameData + 141441);
                --*(_WORD *)(uintptr_t)(PLAYER_DATA_STRIDE * buildingRecord[2] + gameData + 141441);
              }
              goto LABEL_47;
            }
            Render_Pump();
            Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
            DLXSpriteSet_ReleaseAndClear(&g_ActiveUiSpriteSet);
            BuildingSpriteCache_Clear();
            UnitSpriteCache_FreeAllEntries(v33, (DWORD)(intptr_t)buildingRecord);
            CSS_EmptySampleCache();
            TextSprite_ReleaseAllResourceSlots();
            buildingRecordPtr = (unsigned __int8 *)(uintptr_t)(gameData + BUILDING_TABLE_OFFSET + buildingRecordOffset);
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_building_battle_enter",
              attackerStackIndex,
              buildingIndex,
              Unit_GetSquadCount((int)(intptr_t)attackerStack),
              Building_CountGarrison((int)(intptr_t)buildingRecord));
            battleWinner = Battle_RunTacticalCombat((__int16 *)(uintptr_t)(UNIT_STACK_STRIDE * attackerStackIndex + gameData + UNIT_STACK_TABLE_OFFSET), 0, (int)attackerHasSpecial, buildingRecordPtr, (DWORD)(intptr_t)buildingRecord, buildingHasSpecial);
            Diagnostics_TraceWorldMapActionEvent(
              "unit_attack_building_battle_return",
              attackerStackIndex,
              buildingIndex,
              battleWinner,
              Building_CountGarrison((int)(intptr_t)buildingRecord));
            mapThemeIndex = *(_BYTE *)(uintptr_t)(gameData + MAP_THEME_INDEX_OFFSET);
            if ( mapThemeIndex == 0 )
            {
              if ( g_WorldMapBackgroundSpriteSet )
                DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
              backgroundSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)buildingRecord);
              if ( backgroundSpriteSet )
                backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, "backgr1.s32");
              g_WorldMapBackgroundSpriteSet = (int)(intptr_t)backgroundSpriteSet;
            }
            else if ( mapThemeIndex == 1 )
            {
              if ( g_WorldMapBackgroundSpriteSet )
                DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
              backgroundSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)buildingRecord);
              if ( backgroundSpriteSet )
                backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, "backgr2.s32");
              g_WorldMapBackgroundSpriteSet = (int)(intptr_t)backgroundSpriteSet;
            }
            else if ( mapThemeIndex == 2 )
            {
              if ( g_WorldMapBackgroundSpriteSet )
                DLXSpriteSet_ReleaseAndClear(&g_WorldMapBackgroundSpriteSet);
              backgroundSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)buildingRecord);
              if ( backgroundSpriteSet )
                backgroundSpriteSet = DLXSpriteSet_Load(backgroundSpriteSet, "backgr3.s32");
              g_WorldMapBackgroundSpriteSet = (int)(intptr_t)backgroundSpriteSet;
            }
            frameSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, 0, (DWORD)(intptr_t)buildingRecord);
            if ( frameSpriteSet )
              frameSpriteSet = DLXSpriteSet_Load(frameSpriteSet, "frame.s32");
            v40 = -45;
            g_ActiveUiSpriteSet = (int)(intptr_t)frameSpriteSet;
            Tooltip_CaptureBackdrop(160, 473, 3, 467, 76);
            Palette_LoadOrBuildBlendLookupTable(aMainmap_1, g_MapPalettePtr, 1, (DWORD)(intptr_t)buildingRecord);
            selectionRefreshIndex = 1;
            if ( bothPlayersHuman )
              UI_LoadTurnBannerGfx(211, (DWORD)(intptr_t)buildingRecord);
            goto LABEL_42;
          }
          Win_PlayModeChangeFrameTransition(aAtak_zam, 0, 0, 0, 0);
          goto LABEL_28;
        }
      }
    }
  }
}
// 41BB63: variable 'v33' is possibly undefined
// 41BBEA: variable 'v35' is possibly undefined
// 41BC45: variable 'v41' is possibly undefined
// 41BE69: variable 'v45' is possibly undefined
// 41BF5D: variable 'v48' is possibly undefined
// 51D01C: using guessed type int dword_51D01C;
// 5202BC: using guessed type int dword_5202BC;
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;
// 5202F4: using guessed type int dword_5202F4;

//----- (0041C100) --------------------------------------------------------
int  UnitSlots_CalcCombatStrengthScore(char *slotArray, int slotCount, int statContext, int wallDefenseBonus)
{
  unsigned int unitType; // eax
  int unitScore; // edi
  char *(**unitMetadata)[102]; // ecx
  int effectivenessD; // eax
  int orderTier; // ebp
  int effectivenessA; // eax
  int adjustedRankCount; // edi
  int v16; // edx
  __int64 v17; // rax
  int tierCount; // eax
  int adjustedTier; // edi
  int v20; // edx
  int totalScore; // [esp+8h] [ebp-14h]
  int remainingRanks;

  totalScore = 0;
  while ( --slotCount != -1 )
  {
    while ( 1 )
    {
      unitType = UNIT_SLOT_TYPE(slotArray);
      if ( unitType <= 0x28 )
        break;
      slotArray += 31;
    }
    unitScore = 0;
    unitMetadata = &g_UnitTypeMetadataRecords + 22 * unitType;
    if ( unitType == 13 )
    {
      if ( wallDefenseBonus )
      {
        effectivenessD = Unit_CalcEffectivenessD(slotArray, statContext);
        unitScore = effectivenessD * (*((unsigned __int8 *)unitMetadata + 24) / 5) / 2;
      }
      else
      {
        unitScore = 1;
      }
      goto LABEL_8;
    }
    if ( *((_BYTE *)unitMetadata + 22) && !*((_BYTE *)unitMetadata + 25) )
    {
      adjustedRankCount = *((unsigned __int8 *)unitMetadata + 24) / 5 - 1;
      if ( (*((_BYTE *)unitMetadata + 18) & 1) == 0 )
        adjustedRankCount -= 2 * wallDefenseBonus / 100;
      v16 = Unit_CalcEffectivenessA(slotArray, statContext) * adjustedRankCount + totalScore;
      slotArray += 31;
      totalScore = v16;
    }
    else if ( *((_BYTE *)unitMetadata + 22) || !*((_BYTE *)unitMetadata + 25) )
    {
      if ( !*((_BYTE *)unitMetadata + 22) || !*((_BYTE *)unitMetadata + 25) )
        goto LABEL_8;
      orderTier = (slotArray[12] & 3) + 1;
      if ( orderTier >= *((unsigned __int8 *)unitMetadata + 24) / 5 )
        orderTier = *((unsigned __int8 *)unitMetadata + 24) / 5;
      unitScore = Unit_CalcEffectivenessC((__int16 *)slotArray) * orderTier;
      remainingRanks = *((unsigned __int8 *)unitMetadata + 24) / 5 - orderTier - 1;
      if ( remainingRanks > 0 )
      {
        effectivenessA = Unit_CalcEffectivenessA(slotArray, statContext);
        slotArray += 31;
        totalScore += remainingRanks * effectivenessA + unitScore;
      }
      else
      {
LABEL_8:
        slotArray += 31;
        totalScore += unitScore;
      }
    }
    else
    {
      v17 = 6 - *((unsigned __int8 *)unitMetadata + 26);
      tierCount = *((unsigned __int8 *)unitMetadata + 24) / 5 - (((int)v17 - HIDWORD(v17)) >> 1);
      if ( (slotArray[12] & 3) + 1 < tierCount )
        tierCount = (slotArray[12] & 3) + 1;
      adjustedTier = tierCount;
      if ( tierCount >= 3 )
        adjustedTier = tierCount + 2;
      v20 = Unit_CalcEffectivenessC((__int16 *)slotArray) * adjustedTier + totalScore;
      slotArray += 31;
      totalScore = v20;
    }
  }
  return totalScore;
}
// 41C143: simplified comparisons for 'eax.4': >=0 && <29 became <29u
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (0041C300) --------------------------------------------------------
int  UnitSlots_CalcDefenseScore(char *slotArray, int slotCount, int statContext)
{
  int i; // ebx
  int slotDefense; // eax

  for ( i = 0; --slotCount != -1; i += slotDefense )
  {
    while ( (unsigned int)*(__int16 *)slotArray > 0x28 )
      slotArray += 31;
    slotDefense = Unit_CalcEffectivenessB(slotArray, statContext);
    slotArray += 31;
  }
  return (300 * i - (__CFSHL__((300 * i) >> 31, 8) + ((300 * i) >> 31 << 8))) >> 8;
}
// 41C316: simplified comparisons for 'eax.4': >=0 && <29 became <29u

//----- (0041C360) --------------------------------------------------------
int  Building_ApplySiegeDamageToWallSections(int buildingRecord, signed int siegeDamage)
{
  signed int remainingDamage; // ebx
  int result; // eax
  int sectionsToClear; // ecx
  int sectionHitPoints; // edx
  int v7; // ecx
  unsigned int sectionIndex; // ebx
  char damageAmount; // dl
  int v10; // ecx
  int existingSectionHP; // ecx

  remainingDamage = siegeDamage;
  result = siegeDamage / 100;
  sectionsToClear = siegeDamage / 100;
  if ( siegeDamage / 100 > 2 )
    sectionsToClear = 2;
  while ( sectionsToClear )
  {
    result = Rng_RandRange(0, 6);
    sectionHitPoints = *(unsigned __int8 *)(uintptr_t)(buildingRecord + result + 422);
    *(_BYTE *)(uintptr_t)(buildingRecord + result + 422) = 0;
    remainingDamage -= sectionHitPoints;
  }
  if ( remainingDamage )
  {
    do
      sectionIndex = Rng_RandRange(0, 6);
    while ( !*(_BYTE *)(uintptr_t)(buildingRecord + sectionIndex + 422) && v7 + 1 < 6 );
    result = Rng_RandRange(10, 25);
    damageAmount = result;
    existingSectionHP = *(unsigned __int8 *)(uintptr_t)(v10 + 422);
    if ( result > existingSectionHP )
      damageAmount = existingSectionHP;
    *(_BYTE *)(uintptr_t)(buildingRecord + sectionIndex + 422) -= damageAmount;
  }
  return result;
}
// 41C37E: variable 'v5' is possibly undefined
// 41C3CA: variable 'v7' is possibly undefined
// 41C3E4: variable 'v10' is possibly undefined

//----- (0041C410) --------------------------------------------------------
int  Building_CalcWallDefenseBonus(int buildingRecord, signed int weakestSection)
{
  int minSectionHP; // eax
  int firstPassPtr; // ecx
  int i; // edx
  int secondPassPtr; // ecx
  int firstMinHP; // edi
  int j; // edx
  int wallDefenseRaw; // eax

  minSectionHP = 100;
  firstPassPtr = buildingRecord;
  for ( i = 0; i < 7; ++i )
  {
    if ( *(unsigned __int8 *)(uintptr_t)(firstPassPtr + 422) < minSectionHP )
    {
      minSectionHP = *(unsigned __int8 *)(uintptr_t)(firstPassPtr + 422);
      weakestSection = i;
    }
    ++firstPassPtr;
  }
  secondPassPtr = buildingRecord;
  firstMinHP = minSectionHP;
  for ( j = 0; j < 7; ++j )
  {
    if ( *(unsigned __int8 *)(uintptr_t)(secondPassPtr + 422) < minSectionHP && j != weakestSection )
      minSectionHP = *(unsigned __int8 *)(uintptr_t)(secondPassPtr + 422);
    ++secondPassPtr;
  }
  wallDefenseRaw = (minSectionHP + firstMinHP) / 2 * (unsigned __int16)g_WallKindDefenseFactor[2 * *(unsigned __int8 *)(uintptr_t)(buildingRecord + 421)];
  return (wallDefenseRaw - (__CFSHL__(wallDefenseRaw >> 31, 8) + (wallDefenseRaw >> 31 << 8))) >> 8;
}
// 513A78: using guessed type __int16 word_513A78[];

//----- (0041C4A0) --------------------------------------------------------
int  CalculateBattleResult(
        _WORD *attackerSlots,
        int attackerCount,
        _WORD *defenderSlots,
        int attackerStatContext,
        DWORD a5,
        int defenderCount,
        int defenderStatContext,
        int buildingRecord,
        int applyAttackerBonus)
{
  char slotProcessed[12]; // [esp+0h] [ebp-40h]
  _WORD *attackerSlotsPtr; // [esp+Ch] [ebp-34h]
  int attackerCombatScore; // [esp+10h] [ebp-30h]
  signed int higherNetScore; // [esp+14h] [ebp-2Ch]
  signed int lowerNetScore; // [esp+18h] [ebp-28h]
  int attackerStatCtx; // [esp+1Ch] [ebp-24h]
  signed int attackerNetScore; // [esp+20h] [ebp-20h]
  int loserCount; // [esp+24h] [ebp-1Ch]
  _WORD *loserSlots; // [esp+28h] [ebp-18h]
  __int16 *winnerSlots; // [esp+2Ch] [ebp-14h]
  int casualtyBudget; // [esp+30h] [ebp-10h]
  int defender_combat;
  int defender_score;
  int wall_defense_bonus;
  int i;
  int selected_slot;
  int selected_priority;
  int slot_priority;
  int old_quantity;
  int new_quantity;
  int loss_delta;
  int slot_index;
  int applied_loss;

  attackerSlotsPtr = attackerSlots;
  attackerStatCtx = attackerStatContext;
  Battle_StoreLastOutcomeValue(1);
  Debug_Log(0, 0, a5, (int)(intptr_t)aNewBattle);
  Debug_Log((int)(intptr_t)attackerSlotsPtr, (char)attackerCount, a5, (int)(intptr_t)aCalculatebattl, (int)(intptr_t)attackerSlotsPtr, attackerCount, attackerStatCtx, (int)(intptr_t)defenderSlots, defenderCount, defenderStatContext, buildingRecord, applyAttackerBonus);
  Debug_Log(0, 0, a5, (int)(intptr_t)aJednostka1);
  Debug_Log(0, 0, a5, (int)(intptr_t)aJednostka2);
  if ( buildingRecord )
    wall_defense_bonus = Building_CalcWallDefenseBonus(buildingRecord, (signed int)(intptr_t)defenderSlots);
  else
    wall_defense_bonus = 0;
  attackerCombatScore = UnitSlots_CalcCombatStrengthScore((char *)attackerSlotsPtr, attackerCount, attackerStatCtx, wall_defense_bonus);
  defender_combat = UnitSlots_CalcCombatStrengthScore((char *)defenderSlots, defenderCount, defenderStatContext, 0);
  attackerNetScore = attackerCombatScore - UnitSlots_CalcDefenseScore((char *)defenderSlots, defenderCount, defenderStatContext);
  defender_score = defender_combat - UnitSlots_CalcDefenseScore((char *)attackerSlotsPtr, attackerCount, attackerStatCtx);
  Debug_Log(attackerNetScore, 0, a5, (int)(intptr_t)aAs1D, attackerNetScore);
  Debug_Log(defender_score, 0, a5, (int)(intptr_t)aAs2D, defender_score);
  if ( attackerNetScore < 0 )
    attackerNetScore = 0;
  if ( defender_score < 0 )
    defender_score = 0;
  if ( !attackerNetScore )
    attackerNetScore = 1;
  if ( !defender_score )
    defender_score = 1;
  if ( defender_score == attackerNetScore )
    ++attackerNetScore;
  if ( applyAttackerBonus )
    attackerNetScore = 135 * attackerNetScore / 100;
  if ( defender_score > attackerNetScore )
    higherNetScore = defender_score;
  else
    higherNetScore = attackerNetScore;
  if ( defender_score > attackerNetScore )
    lowerNetScore = attackerNetScore;
  else
    lowerNetScore = defender_score;
  if ( defender_score > attackerNetScore )
    winnerSlots = (__int16 *)defenderSlots;
  else
    winnerSlots = (__int16 *)attackerSlotsPtr;
  if ( defender_score > attackerNetScore )
    loserSlots = attackerSlotsPtr;
  else
    loserSlots = defenderSlots;
  if ( defender_score > attackerNetScore )
    loserCount = attackerCount;
  else
    loserCount = defenderCount;
  if ( defender_score > attackerNetScore )
    attackerCount = defenderCount;
  casualtyBudget = 0;
  for ( i = 0; i < attackerCount; ++i )
    casualtyBudget += *((signed char *)winnerSlots + 31 * i + 9);
  casualtyBudget = casualtyBudget * lowerNetScore / higherNetScore;
  Debug_Log(casualtyBudget, (char)higherNetScore, a5, (int)(intptr_t)aSum_quantDAtt_, casualtyBudget);
  while ( casualtyBudget > 0 )
  {
    applied_loss = 0;
    memset(slotProcessed, 0, sizeof(slotProcessed));
    while ( casualtyBudget > 0 )
    {
      for ( slot_index = 0; slot_index < attackerCount && slot_index < (int)sizeof(slotProcessed) && slotProcessed[slot_index]; ++slot_index )
        ;
      if ( slot_index >= attackerCount || slot_index >= (int)sizeof(slotProcessed) )
        break;
      selected_slot = -1;
      selected_priority = 0;
      for ( i = 0; i < attackerCount && i < (int)sizeof(slotProcessed); ++i )
      {
        slot_priority = (unsigned __int8)unit_stats[88 * UNIT_SLOT_TYPE((char *)winnerSlots + 31 * i)];
        if ( slot_priority > selected_priority && !slotProcessed[i] )
        {
          selected_priority = slot_priority;
          selected_slot = i;
        }
      }
      if ( selected_slot < 0 )
      {
        casualtyBudget = 0;
        break;
      }
      old_quantity = *((signed char *)winnerSlots + 31 * selected_slot + 9);
      new_quantity = old_quantity - selected_priority;
      if ( new_quantity < 0 )
        new_quantity = 0;
      new_quantity -= Rng_RandRange(0, 10);
      loss_delta = old_quantity - new_quantity;
      casualtyBudget -= loss_delta;
      if ( casualtyBudget < 0 )
        new_quantity -= casualtyBudget;
      if ( new_quantity < 0 )
        new_quantity = 0;
      if ( loss_delta > 0 )
        applied_loss = 1;
      *((_BYTE *)winnerSlots + 31 * selected_slot + 9) = new_quantity;
      slotProcessed[selected_slot] = 1;
    }
    if ( !applied_loss )
      break;
  }
  Debug_Log(0, 0, a5, (int)(intptr_t)aJednostkaZwyci);
  for ( i = 0; i < attackerCount; ++i )
  {
    if ( !*((_BYTE *)winnerSlots + 31 * i + 9) )
      *(__int16 *)((char *)winnerSlots + 31 * i) = -1;
  }
  UnitSlots_RemoveGaps((_WORD *)winnerSlots, attackerCount);
  if ( buildingRecord )
    Building_ApplySiegeDamageToWallSections(buildingRecord, attackerNetScore);
  for ( i = 0; i < loserCount; ++i )
  {
    *loserSlots = -1;
    loserSlots = (_WORD *)((char *)loserSlots + 31);
  }
  return Battle_StoreLastOutcomeValue(0);
}
// 41C719: conditional instruction was optimized away because esi.4>=1
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (0041C8B0) --------------------------------------------------------
signed int  UI_PromptLeadTroopsPersonally(
        int attackerSlots,
        int attackerCount,
        int defenderCount,
        int defenderSlots,
        DWORD a5,
        int a6,
        int showThirdOption)
{
  int v7 CLASH95_UNUSED; // ecx
  int v8 CLASH95_UNUSED; // ecx
  _DWORD *promptSpriteSetTmp; // eax
  void *v10 CLASH95_UNUSED; // ecx
  int SpriteForChar; // eax
  int thirdOptionSprite; // eax
  int v13 CLASH95_UNUSED; // edx
  int v14 CLASH95_UNUSED; // edx
  int attackerSlotIndex; // esi
  unsigned __int8 *attackerSlotPtr; // edi
  char attackerOwner; // bl
  int v18; // ecx
  _DWORD *attackerUnitSpriteSet; // eax
  int attackerUnitSprite; // eax
  int defenderSlotIndex; // esi
  unsigned __int8 *defenderSlotPtr; // edi
  char defenderOwner; // bl
  int v24; // ecx
  _DWORD *defenderUnitSpriteSet; // eax
  int defenderUnitSprite; // eax
  int baseLeft; // ebx
  int baseTop; // edi
  int buttonColumnX; // ebx
  int secondaryButtonTop; // edi
  signed int buttonRight; // ebp
  unsigned __int16 SpriteHeight; // ax
  int secondaryButtonBottom; // edx
  int userChoice; // esi
  unsigned __int16 v35 CLASH95_UNUSED; // cx
  unsigned __int16 v36 CLASH95_UNUSED; // bx
  __int16 SpriteWidth; // ax
  __int16 v38 CLASH95_UNUSED; // cx
  __int16 panelHeight; // ax
  int v40 CLASH95_UNUSED; // ecx
  unsigned __int16 v42 CLASH95_UNUSED; // [esp-Ch] [ebp-140h]
  unsigned __int16 v43 CLASH95_UNUSED; // [esp-8h] [ebp-13Ch]
  unsigned __int16 v44 CLASH95_UNUSED; // [esp-4h] [ebp-138h]
  char v45[100]; // [esp+0h] [ebp-134h] BYREF
  char v46[100]; // [esp+64h] [ebp-D0h] BYREF
  int promptTextByLang[3]; // [esp+C8h] [ebp-6Ch]
  _DWORD *promptSpriteSet; // [esp+D4h] [ebp-60h] BYREF
  _DWORD *attackerUnitSpriteHandle; // [esp+D8h] [ebp-5Ch] BYREF
  _DWORD *defenderUnitSpriteHandle; // [esp+DCh] [ebp-58h] BYREF
  int v51 CLASH95_UNUSED; // [esp+E0h] [ebp-54h]
  int (*savedRenderHook)(); // [esp+E4h] [ebp-50h]
  int savedResourceHandle; // [esp+E8h] [ebp-4Ch]
  int panelLeft; // [esp+ECh] [ebp-48h]
  int panelTop; // [esp+F0h] [ebp-44h]
  int defenderGridTop; // [esp+F4h] [ebp-40h]
  int attackerGridLeft; // [esp+F8h] [ebp-3Ch]
  int attackerGridTop; // [esp+FCh] [ebp-38h]
  int defenderGridLeft; // [esp+100h] [ebp-34h]
  int defenderCountCopy; // [esp+104h] [ebp-30h]
  int attackerCountCopy; // [esp+108h] [ebp-2Ch]
  int primaryButtonTop; // [esp+10Ch] [ebp-28h]
  int defenderSlotsBase; // [esp+110h] [ebp-24h]
  int attackerSlotsBase; // [esp+114h] [ebp-20h]
  int attackerCellX; // [esp+118h] [ebp-1Ch]
  int defenderCellX; // [esp+11Ch] [ebp-18h]
  int attackerCellY; // [esp+120h] [ebp-14h]
  int defenderCellY; // [esp+124h] [ebp-10h]

  attackerSlotsBase = attackerSlots;
  attackerCountCopy = attackerCount;
  defenderSlotsBase = defenderSlots;
  defenderCountCopy = defenderCount;
  savedResourceHandle = Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, 1);
  savedRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(0, defenderSlots, a5, (int)(intptr_t)aSetrhS08x_3);
  promptSpriteSetTmp = (_DWORD *)(uintptr_t)Mem_Alloc(4112, 0, defenderSlots, a5);
  if ( promptSpriteSetTmp )
    promptSpriteSetTmp = DLXSpriteSet_Load(promptSpriteSetTmp, "auto.s32");
  promptSpriteSet = promptSpriteSetTmp;
  Render_Pump();
  g_RenderDevice = &g_MainRenderDevice;
  panelTop = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)promptSpriteSet, 0)) / 2;
  panelLeft = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)promptSpriteSet, 0)) / 2;
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)promptSpriteSet, 0);
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  if ( showThirdOption )
  {
    thirdOptionSprite = DLX_GetSpriteForChar((int)(intptr_t)promptSpriteSet, 3);
    Compat_RenderDeviceDrawMenuSprite(panelLeft + 59, panelTop + 441, thirdOptionSprite, 1);
  }
  Render_ReleaseSurface(7, a5);
  UI_DrawTextFmt(a6, panelTop + 42, panelTop + 166, panelLeft + 85, 3, PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(attackerSlotsBase + 2) + gameData + PLAYER_RUNTIME_STATE_OFFSET + 4);
  UI_DrawTextFmt(a6, panelTop + 395, panelTop + 518, panelLeft + 85, 3, PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(defenderSlotsBase + 2) + gameData + PLAYER_RUNTIME_STATE_OFFSET + 4);
  attackerSlotIndex = 0;
  if ( attackerCountCopy > 0 )
  {
    attackerGridLeft = panelLeft + 110;
    attackerSlotPtr = (unsigned __int8 *)(uintptr_t)attackerSlotsBase;
    attackerGridTop = panelTop + 18;
    do
    {
      if ( UNIT_SLOT_TYPE(attackerSlotPtr) != -1 )
      {
        attackerOwner = UNIT_SLOT_OWNER(attackerSlotsBase);
        UI_BeginUnitInfo(v45, *attackerSlotPtr, attackerOwner);
        attackerUnitSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v18, attackerOwner, a5);
        if ( attackerUnitSpriteSet )
          attackerUnitSpriteSet = DLXSpriteSet_Load(attackerUnitSpriteSet, v45);
        attackerCellX = 76 * ((attackerSlotIndex - (__CFSHL__(attackerSlotIndex >> 31, 2) + 4 * (attackerSlotIndex >> 31))) >> 2) + attackerGridLeft;
        attackerCellY = 48 * (attackerSlotIndex % 4) + attackerGridTop;
        attackerUnitSpriteHandle = attackerUnitSpriteSet;
        attackerUnitSprite = DLX_GetSpriteForChar((int)(intptr_t)attackerUnitSpriteSet, 0);
        Compat_RenderDeviceDrawMenuSprite(attackerCellX, attackerCellY, attackerUnitSprite, 1);
        if ( *(_DWORD *)(uintptr_t)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(attackerSlotsBase + 2) + 140051) )
          UI_DrawTextFmt((int)(intptr_t)attackerSlotPtr, attackerCellY, attackerCellY + 32, attackerCellX + 50, 3, (int)(intptr_t)aD_3);
        DLXSpriteSet_ReleaseAndClear((int *)&attackerUnitSpriteHandle);
      }
      a5 = attackerCountCopy;
      ++attackerSlotIndex;
      attackerSlotPtr += 31;
    }
    while ( attackerSlotIndex < attackerCountCopy );
  }
  defenderSlotIndex = 0;
  if ( defenderCountCopy > 0 )
  {
    defenderGridLeft = panelLeft + 110;
    defenderSlotPtr = (unsigned __int8 *)(uintptr_t)defenderSlotsBase;
    defenderGridTop = panelTop + 371;
    do
    {
      if ( UNIT_SLOT_TYPE(defenderSlotPtr) != -1 )
      {
        defenderOwner = UNIT_SLOT_OWNER(defenderSlotsBase);
        UI_BeginUnitInfo(v46, *defenderSlotPtr, defenderOwner);
        defenderUnitSpriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v24, defenderOwner, a5);
        if ( defenderUnitSpriteSet )
          defenderUnitSpriteSet = DLXSpriteSet_Load(defenderUnitSpriteSet, v46);
        defenderCellX = 76 * ((defenderSlotIndex - (__CFSHL__(defenderSlotIndex >> 31, 2) + 4 * (defenderSlotIndex >> 31))) >> 2) + defenderGridLeft;
        defenderCellY = 48 * (defenderSlotIndex % 4) + defenderGridTop;
        defenderUnitSpriteHandle = defenderUnitSpriteSet;
        defenderUnitSprite = DLX_GetSpriteForChar((int)(intptr_t)defenderUnitSpriteSet, 0);
        Compat_RenderDeviceDrawMenuSprite(defenderCellX, defenderCellY, defenderUnitSprite, 1);
        if ( *(_DWORD *)(uintptr_t)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(uintptr_t)(defenderSlotsBase + 2) + gameData + 140051) )
          UI_DrawTextFmt((int)(intptr_t)defenderSlotPtr, defenderCellY, defenderCellY + 32, defenderCellX + 50, 3, (int)(intptr_t)aD_4);
        DLXSpriteSet_ReleaseAndClear((int *)&defenderUnitSpriteHandle);
      }
      a5 = defenderCountCopy;
      ++defenderSlotIndex;
      defenderSlotPtr += 31;
    }
    while ( defenderSlotIndex < defenderCountCopy );
  }
  promptTextByLang[0] = (int)(intptr_t)g_LeadTroopsPersonallyPromptTexts[0];
  promptTextByLang[1] = (int)(intptr_t)g_LeadTroopsPersonallyPromptTexts[1];
  promptTextByLang[2] = (int)(intptr_t)g_LeadTroopsPersonallyPromptTexts[2];
  Render_ReleaseSurface(17, a5);
  UI_DrawTextFmt((int)(intptr_t)&promptSpriteSet, panelTop + 160, panelTop + 390, panelLeft + 10, 6, promptTextByLang[(unsigned __int8)g_LanguageIndex]);
  RenderState_SelectCursorDescriptor((int)(intptr_t)g_RenderState, (int)(intptr_t)&g_CursorDesc_Default);
  baseLeft = panelLeft;
  baseTop = panelTop;
  Render_Present((int)(intptr_t)g_RenderState);
  buttonColumnX = baseLeft + 61;
  secondaryButtonTop = baseTop + 279;
  primaryButtonTop = panelTop + 201;
  Diagnostics_TraceWorldMapActionEvent(
    "battle_prompt_layout_primary",
    primaryButtonTop,
    buttonColumnX,
    primaryButtonTop + (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)promptSpriteSet, 1u),
    buttonColumnX + (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)promptSpriteSet, 1u));
  Diagnostics_TraceWorldMapActionEvent(
    "battle_prompt_layout_secondary",
    secondaryButtonTop,
    buttonColumnX,
    secondaryButtonTop + (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)promptSpriteSet, 2u),
    buttonColumnX + (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)promptSpriteSet, 2u));
  while ( 1 )
  {
    do
    {
      WorldMap_RunInputScriptStep();
      DD_Pump((int)(intptr_t)g_RenderState, buttonColumnX);
    }
    while ( !DD_IsFlipping((int)(intptr_t)g_RenderState) );
    buttonRight = buttonColumnX + (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)promptSpriteSet, 1u);
    SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)promptSpriteSet, 1u);
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= primaryButtonTop
      && g_MouseCursorRawY >> g_CursorCoordShift >= buttonColumnX
      && g_MouseCursorRawX >> g_CursorCoordShift <= SpriteHeight + primaryButtonTop
      && g_MouseCursorRawY >> g_CursorCoordShift <= buttonRight )
    {
      break;
    }
    buttonRight = buttonColumnX + (unsigned __int16)DLX_GetSpriteWidth((int)(intptr_t)promptSpriteSet, 2u);
    secondaryButtonBottom = secondaryButtonTop + (unsigned __int16)DLX_GetSpriteHeight((int)(intptr_t)promptSpriteSet, 2u);
    if ( g_MouseCursorRawX >> g_CursorCoordShift >= secondaryButtonTop
      && g_MouseCursorRawY >> g_CursorCoordShift >= buttonColumnX
      && g_MouseCursorRawX >> g_CursorCoordShift <= secondaryButtonBottom
      && g_MouseCursorRawY >> g_CursorCoordShift <= buttonRight )
    {
      userChoice = 1;
      Audio_PlayButtonSound(aMale);
      goto LABEL_34;
    }
  }
  Audio_PlayButtonSound(aMale_0);
  userChoice = 0;
LABEL_34:
  Render_Pump();
  Debug_Log(0, buttonColumnX, buttonRight, (int)(intptr_t)aUnsetrh08x_3);
  g_RenderHook = savedRenderHook;
  Render_SetResourceHandle((int)(intptr_t)&g_MainRenderDevice, savedResourceHandle);
  SpriteWidth = DLX_GetSpriteWidth((int)(intptr_t)promptSpriteSet, 0);
  panelHeight = DLX_GetSpriteHeight((int)(intptr_t)promptSpriteSet, 0);
  Render_FillRect((_DWORD *)(uintptr_t)g_PrimaryRenderSurface, 0, panelLeft, panelTop, panelTop + panelHeight, panelLeft + SpriteWidth, panelTop, panelLeft);
  Render_Present((int)(intptr_t)g_RenderState);
  DLXSpriteSet_ReleaseAndClear((int *)&promptSpriteSet);
  return userChoice;
}
// 41C91A: variable 'v7' is possibly undefined
// 41C927: variable 'v8' is possibly undefined
// 41C959: variable 'v10' is possibly undefined
// 41CA4A: variable 'v13' is possibly undefined
// 41CACF: variable 'v14' is possibly undefined
// 41CB39: variable 'v18' is possibly undefined
// 41CCB4: variable 'v24' is possibly undefined
// 41CF9E: variable 'v35' is possibly undefined
// 41CFBD: variable 'v38' is possibly undefined
// 41CFDB: variable 'v40' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 513A00: using guessed type char *off_513A00[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

CLASH95_INTERNAL int g_BuildingNewOverrideActive;
CLASH95_INTERNAL int g_BuildingNewOverrideRow;
CLASH95_INTERNAL int g_BuildingNewOverrideColumn;
