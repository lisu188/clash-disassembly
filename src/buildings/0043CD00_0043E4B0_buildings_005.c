/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
#include "../recovered_internal.h"

CLASH95_TEST_VISIBLE WCCompatListBase *WCCompat_ListFromBase (WCIsvListBase *this);
CLASH95_TEST_VISIBLE WCCompatListBase *WCCompat_ListFromHandle (int list_handle);
CLASH95_TEST_VISIBLE WCCompatLink *WCCompat_LinkFromHandle (int link_handle);

//----- (0043CD00) --------------------------------------------------------
signed int  UnitBattle_RunAiTurnForSide(unsigned __int8 side)
{
  signed int turnResult; // esi
  int v3; // edx
  int poppedUnitId; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  signed int queueIndex; // esi
  int i; // edi
  int queuedUnitId; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int unitRecordAddr; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int unitIndex; // [esp+0h] [ebp-1Ch]

  turnResult = 1;
  unitIndex = 0;
  Diagnostics_TraceWorldMapActionEvent("battle_ai_turn_enter", side, g_CurrentPlayerIndex, g_UnitBattleAiTurnCounter, 0);
  g_BattleAiActionAttemptCount = 0;
  ++g_UnitBattleAiTurnCounter;
  if ( *(_DWORD *)(g_MapData + 828) != -1 )
  {
    Diagnostics_TraceWorldMapActionEvent(
      "battle_ai_before_wall_scan",
      side,
      *(_DWORD *)(g_MapData + 828),
      *(_DWORD *)(g_MapData + 800),
      *(_DWORD *)(g_MapData + 804));
    UnitBattle_ScanAiWallTargetColumns();
    Diagnostics_TraceWorldMapActionEvent("battle_ai_after_wall_scan", side, g_UnitBattleWallScanTileRow, g_BattleWallScanColumn, g_BattleWallScanTileX);
  }
  Diagnostics_TraceWorldMapActionEvent("battle_ai_before_idle", side, g_SelectedUnitIndex, g_UnitBattleAiTurnCounter, 0);
  UnitBattle_UpdateIdleAnimatedUnits();
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_idle", side, g_SelectedUnitIndex, g_UnitBattleAiTurnCounter, 0);
  g_UnitBattleAiCurrentPlanMode = UnitBattle_SelectAiPlanMode(side, side);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_mode", side, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiTurnCounter, 0);
  UnitBattle_UpdateIdleAnimatedUnits();
  UnitBattle_BuildAiUnitQueueForCurrentMode(side);
  Diagnostics_TraceWorldMapActionEvent("battle_ai_after_queue", side, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiCandidateQueueTail, g_BattleAiUnitQueueCount);
  UnitBattle_UpdateIdleAnimatedUnits();
  g_BattleShootingUnitMoveActiveFlag = 0;
  switch ( g_UnitBattleAiCurrentPlanMode )
  {
    case 0:
    case 1:
    case 4:
      goto LABEL_13;
    case 2:
      while ( g_UnitBattleAiCandidateQueueTail )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        poppedUnitId = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
        unitIndex = poppedUnitId;
        UnitBattle_ResetAiReachGridForSide(side);
        UnitBattle_ScoreAiActionGridForUnit(unitIndex, side, 0, 1);
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( UnitBattle_SelectAiActionForUnit(unitIndex, side) )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          UnitBattle_ExecuteAiActionForUnit(unitIndex, side, 0);
        }
        else
        {
          WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, unitIndex);
        }
      }
      goto LABEL_8;
    case 6:
LABEL_8:
      queueIndex = 0;
      for ( i = g_BattleAiUnitQueueCount; queueIndex < i; ++queueIndex )
      {
        UnitBattle_UpdateIdleAnimatedUnits();
        queuedUnitId = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
        unitIndex = queuedUnitId;
        UnitBattle_ResetAiReachGridForSide(side);
        UnitBattle_ScoreAiActionGridForUnit(unitIndex, side, 0, queueIndex);
        UnitBattle_UpdateIdleAnimatedUnits();
        if ( UnitBattle_SelectAiActionForUnit(unitIndex, side) )
        {
          UnitBattle_UpdateIdleAnimatedUnits();
          UnitBattle_ExecuteAiActionForUnit(unitIndex, side, 0);
        }
        WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, unitIndex);
      }
      UnitBattle_UpdateIdleAnimatedUnits();
      g_UnitBattleAiCurrentPlanMode = UnitBattle_SelectAiPlanMode(side, side);
      UnitBattle_UpdateIdleAnimatedUnits();
      turnResult = 0;
      UnitBattle_BuildAiUnitQueueForCurrentMode(side);
      Diagnostics_TraceWorldMapActionEvent("battle_ai_after_requeue", side, g_UnitBattleAiCurrentPlanMode, g_UnitBattleAiCandidateQueueTail, g_BattleAiUnitQueueCount);
      UnitBattle_UpdateIdleAnimatedUnits();
LABEL_13:
      if ( !g_UnitBattleAiCandidateQueueTail )
        goto LABEL_21;
      break;
    default:
      goto LABEL_21;
  }
  while ( 1 )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    unitIndex = WCIsvListBase_PopFrontValue((int)&g_UnitBattleAiCandidateQueue, 0);
    Diagnostics_TraceWorldMapActionEvent("battle_ai_unit_candidate", unitIndex, side, g_UnitBattleAiCandidateQueueTail, turnResult);
    unitRecordAddr = g_MapData + 31 * unitIndex;
    if ( *(__int16 *)(unitRecordAddr + 852) != -1 && side == *(_BYTE *)(unitRecordAddr + 854) )
      break;
LABEL_20:
    if ( !g_UnitBattleAiCandidateQueueTail )
    {
LABEL_21:
      WCIsvListBase_base_destroy((WCIsvListBase *)&g_UnitBattleAiCandidateQueue);
      Diagnostics_TraceWorldMapActionEvent("battle_ai_turn_exit", side, turnResult, g_UnitBattleAiCandidateQueueTail, 0);
      return turnResult;
    }
  }
  while ( 1 )
  {
    UnitBattle_UpdateIdleAnimatedUnits();
    UnitBattle_ResetAiReachGridForSide(side);
    if ( UnitBattle_ScoreAiActionGridForUnit(unitIndex, side, 0, turnResult) )
      return 1;
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( !UnitBattle_SelectAiActionForUnit(unitIndex, side) )
    {
      WCIsvListBase_AppendValue((int)&g_UnitBattleAiCandidateQueue, unitIndex);
LABEL_19:
      turnResult = 0;
      goto LABEL_20;
    }
    UnitBattle_UpdateIdleAnimatedUnits();
    if ( !UnitBattle_ExecuteAiActionForUnit(unitIndex, side, 0) )
      goto LABEL_19;
  }
}
// 43CD57: variable 'v3' is possibly undefined
// 43CD9F: variable 'v5' is possibly undefined
// 43CDA9: variable 'v6' is possibly undefined
// 43CDB8: variable 'v7' is possibly undefined
// 43CDCF: variable 'v9' is possibly undefined
// 43CE04: variable 'v13' is possibly undefined
// 43CE0E: variable 'v14' is possibly undefined
// 43CE1D: variable 'v15' is possibly undefined
// 43CE30: variable 'v17' is possibly undefined
// 43CE3C: variable 'v16' is possibly undefined
// 43CE64: variable 'v18' is possibly undefined
// 43CEBC: variable 'v20' is possibly undefined
// 43CEC6: variable 'v21' is possibly undefined
// 43CED9: variable 'v22' is possibly undefined
// 43CEEC: variable 'v24' is possibly undefined
// 43CF10: variable 'v26' is possibly undefined
// 43CF28: variable 'v8' is possibly undefined
// 43CF40: variable 'v23' is possibly undefined
// 515A10: using guessed type int dword_515A10;
// 532048: using guessed type int g_MapData;
// 532078: using guessed type int dword_532078;
// 5437A8: using guessed type int dword_5437A8;
// 5437AC: using guessed type int dword_5437AC;
// 5437C0: using guessed type int dword_5437C0;
// 5437C8: using guessed type int dword_5437C8;
// 5437CC: using guessed type int dword_5437CC;

//----- (0043CF50) --------------------------------------------------------
_DWORD * WCIsvListBase_ctorRoot(_DWORD *result)
{
  *result = 0;
  result[1] = &g_WCIsvListBaseRoot_Vtable;
  return result;
}
// 50F0E4: using guessed type int (*off_50F0E4)();

//----- (0043CF60) --------------------------------------------------------
int  WCIsvListBase_dtorRoot(int result, char dtorFlags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_WCIsvListBaseRoot_DtorArrayTag);
    j_j__nfree_();
    return v3;
  }
  else if ( (dtorFlags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 43CF89: variable 'v4' is possibly undefined
// 43CF80: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0043CF90) --------------------------------------------------------
int __cdecl WCIsvListBase_vtblFree(void)
{
  return j__nfree_();
}

//----- (0043CFA0) --------------------------------------------------------
BOOL  WCIsvListBase_ValuesEqual(_DWORD *leftNode, _DWORD *rightNode)
{
  return *leftNode == *rightNode;
}

//----- (0043CFB0) --------------------------------------------------------
_DWORD * WCIsvListBase_ctorVariant124(_DWORD *result)
{
  *result = 0;
  result[1] = &g_WCIsvListBaseRoot_Vtable;
  result[2] = 0;
  result[3] = 0;
  result[4] = 0;
  result[5] = 0;
  result[1] = &g_WCIsvListBaseDtor_Vtable;
  result[1] = &g_WCIsvListBaseDestroyElements_Vtable;
  result[1] = &g_WCIsvListBaseVariant124_Vtable;
  return result;
}
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F114: using guessed type int (__thiscall *off_50F114)(WCIsvListBase *this);
// 50F124: using guessed type void *off_50F124;

//----- (0043CFF0) --------------------------------------------------------
int  WCIsvListBase_dtorVariant124(WCIsvListBase *a1, char dtorFlags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_WCIsvListBaseVariant124_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = WCIsvListBase_DestroyElementsAndDtor(a1, (int)a1);
    if ( (dtorFlags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 43D020: variable 'v4' is possibly undefined
// 43D02A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0043D030) --------------------------------------------------------
int  WCIsvListBase_ctorVariant124AndCopy(_DWORD *dest, _DWORD *source)
{
  int v2; // ecx

  *dest = 0;
  dest[1] = &g_WCIsvListBaseRoot_Vtable;
  dest[2] = 0;
  dest[3] = 0;
  dest[4] = 0;
  dest[5] = 0;
  dest[1] = &g_WCIsvListBaseDtor_Vtable;
  dest[1] = &g_WCIsvListBaseDestroyElements_Vtable;
  dest[1] = &g_WCIsvListBaseVariant124_Vtable;
  WCIsvListBase_CopyAppendAll(dest, source, (int)dest);
  return v2;
}
// 43D076: variable 'v2' is possibly undefined
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F114: using guessed type int (__thiscall *off_50F114)(WCIsvListBase *this);
// 50F124: using guessed type void *off_50F124;

//----- (0043D080) --------------------------------------------------------
_DWORD * WCIsvListBase_ctorVariant134(_DWORD *result)
{
  *result = 0;
  result[1] = &g_WCIsvListBaseRoot_Vtable;
  result[2] = 0;
  result[3] = 0;
  result[4] = 0;
  result[5] = 0;
  result[1] = &g_WCIsvListBaseDtor_Vtable;
  result[1] = &g_WCIsvListBaseVariant124_Vtable;
  result[1] = &g_WCIsvListBaseVariant134_Vtable;
  return result;
}
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F124: using guessed type void *off_50F124;
// 50F134: using guessed type void *off_50F134;

//----- (0043D0C0) --------------------------------------------------------
int  WCIsvListBase_dtorVariant134(WCIsvListBase *a1, char dtorFlags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_WCIsvListBaseVariant134_DtorArrayTag);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = WCIsvListBase_DestroyElementsAndDtor(a1, (int)a1);
    if ( (dtorFlags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 43D0F0: variable 'v4' is possibly undefined
// 43D0FA: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

/* Type declaration moved to recovered_internal.h. */




/* Type declaration moved to recovered_internal.h. */








CLASH95_TEST_VISIBLE WCCompatListBase *WCCompat_ListFromBase(WCIsvListBase *this)
{
  return (WCCompatListBase *)this;
}

CLASH95_TEST_VISIBLE WCCompatListBase *WCCompat_ListFromHandle(int list_handle)
{
  return (WCCompatListBase *)(uintptr_t)(unsigned int)list_handle;
}

CLASH95_TEST_VISIBLE WCCompatLink *WCCompat_LinkFromHandle(int link_handle)
{
  return (WCCompatLink *)(uintptr_t)(unsigned int)link_handle;
}

//----- (0043D100) --------------------------------------------------------
_DWORD *WCIsvListBase_vtblDtor(WCIsvListBase *this)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromBase(this);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseFreeOnly_Vtable;
  WCIsvListBase_dtor(this);
  return (_DWORD *)this;
}

//----- (0043D100) --------------------------------------------------------
_DWORD * WCIsvListBase_dtorVariant104(WCIsvListBase *this)
{
  return WCIsvListBase_vtblDtor(this);
}

int __fastcall WCIsvListBase_base_next(int list_handle, int cursor_handle)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  list = WCCompat_ListFromHandle(list_handle);
  if ( !list || !list->head_link )
    return 0;
  for ( link = WCCompat_LinkFromHandle(list->head_link); link; link = WCCompat_LinkFromHandle(link->next_link) )
  {
    if ( (int)(uintptr_t)link == cursor_handle )
      return link->next_link;
  }
  return list->head_link;
}

int __fastcall WCIsvListBase_base_insert(int list_handle, int link_handle)
{
  WCCompatListBase *list;
  WCCompatLink *link;
  WCCompatLink *tail;

  list = WCCompat_ListFromHandle(list_handle);
  link = WCCompat_LinkFromHandle(link_handle);
  if ( !list || !link )
    return 0;
  link->next_link = 0;
  if ( list->tail_link )
  {
    tail = WCCompat_LinkFromHandle(list->tail_link);
    if ( tail )
      tail->next_link = link_handle;
    else
      list->head_link = link_handle;
  }
  else
  {
    list->head_link = link_handle;
  }
  list->count += 1;
  return link_handle;
}

int __fastcall WCIsvListBase_base_sget(int list_handle)
{
  WCCompatListBase *list;
  WCCompatLink *head;
  int link_handle;

  list = WCCompat_ListFromHandle(list_handle);
  if ( !list || !list->head_link )
    return 0;
  link_handle = list->head_link;
  head = WCCompat_LinkFromHandle(link_handle);
  if ( !head )
  {
    list->head_link = 0;
    list->tail_link = 0;
    list->count = 0;
    return 0;
  }
  list->head_link = head->next_link;
  if ( !list->head_link )
    list->tail_link = 0;
  if ( list->count > 0 )
    list->count -= 1;
  return link_handle;
}

void WCIsvListBase_base_destroy(WCIsvListBase *this)
{
  int link_handle;

  for ( link_handle = WCIsvListBase_base_sget((int)(uintptr_t)this); link_handle; link_handle = WCIsvListBase_base_sget((int)(uintptr_t)this) )
    WCIsvListBase_ReleaseLinkNode((int)(uintptr_t)this, link_handle, 8);
}

_DWORD WCIsvListBase_dtor(WCIsvListBase *this)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromBase(this);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseDtor_Vtable;
  if ( list->tail_link )
    Noop_WCIsvListErrorHook((int)(uintptr_t)this);
  return (unsigned int)(uintptr_t)this;
}

//----- (0043D120) --------------------------------------------------------
_DWORD * WCIsvListBase_AllocLinkNode(int listHandle, int a2)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  list = WCCompat_ListFromHandle(listHandle);
  if ( !list )
    return 0;
  if ( !list->alloc_fn )
    link = (WCCompatLink *)(uintptr_t)(unsigned int)j_Mem_Alloc(8);
  else
    link = (WCCompatLink *)(uintptr_t)(unsigned int)(*(int (__cdecl **)(int))(uintptr_t)(unsigned int)list->alloc_fn)(8);
  if ( !link )
    return 0;
  link->next_link = 0;
  link->value = a2;
  return (_DWORD *)link;
}

//----- (0043D160) --------------------------------------------------------
int  WCIsvListBase_ReleaseLinkNode(int listHandle, int linkHandle, int freeSize)
{
  if ( !linkHandle )
    return 0;
  if ( *(_DWORD *)(listHandle + 20) )
    return (*(int (__cdecl **)(int))(uintptr_t)(unsigned int)*(_DWORD *)(listHandle + 20))(freeSize);
  return nfree_(linkHandle);
}

//----- (0043D180) --------------------------------------------------------
int  WCIsvListBase_CopyAppendAll(_DWORD *destList, _DWORD *sourceList, int startCursor)
{
  int link_handle;
  WCCompatLink *link;

  *destList = *sourceList;
  destList[4] = sourceList[4];
  destList[5] = sourceList[5];
  link_handle = WCIsvListBase_base_next((int)(uintptr_t)sourceList, startCursor);
  while ( link_handle )
  {
    link = WCCompat_LinkFromHandle(link_handle);
    if ( !link )
      break;
    WCIsvListBase_AppendValue((int)(uintptr_t)destList, link->value);
    link_handle = WCIsvListBase_base_next((int)(uintptr_t)sourceList, link_handle);
  }
  return link_handle;
}

//----- (0043D1E0) --------------------------------------------------------
int  WCIsvListBase_DestroyElementsAndDtor(WCIsvListBase *this, int listHandle)
{
  WCCompatListBase *list;

  list = WCCompat_ListFromHandle(listHandle);
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseDestroyElements_Vtable;
  if ( list->tail_link )
  {
    Noop_WCIsvListErrorHook(listHandle);
    WCIsvListBase_base_destroy(this);
  }
  list->vtable = (int)(uintptr_t)g_WCIsvListBaseFreeOnly_Vtable;
  return WCIsvListBase_dtor(this);
}

//----- (0043D220) --------------------------------------------------------
signed int  WCIsvListBase_AppendValue(int listHandle, int value)
{
  WCCompatListBase *list;
  WCCompatLink *link;

  link = (WCCompatLink *)WCIsvListBase_AllocLinkNode(listHandle, value);
  if ( link )
  {
    list = WCCompat_ListFromHandle(listHandle);
    WCIsvListBase_base_insert(listHandle, (int)(uintptr_t)link);
    list->tail_link = (int)(uintptr_t)link;
    return 1;
  }
  Noop_WCIsvListErrorHook(listHandle);
  return 0;
}

//----- (0043D250) --------------------------------------------------------
int  WCIsvListBase_PopFrontValue(int listHandle, int defaultValue)
{
  int link_handle;
  WCCompatLink *link;

  link_handle = WCIsvListBase_base_sget(listHandle);
  if ( !link_handle )
    return defaultValue;
  link = WCCompat_LinkFromHandle(link_handle);
  if ( !link )
    return defaultValue;
  defaultValue = link->value;
  WCIsvListBase_ReleaseLinkNode(listHandle, link_handle, 8);
  return defaultValue;
}

//----- (0043D280) --------------------------------------------------------
int  WCIsvListBase_CopyCtor(_DWORD *dest, _DWORD *source)
{
  int v2; // ecx
  int result; // eax

  *dest = 0;
  dest[1] = &g_WCIsvListBaseRoot_Vtable;
  dest[2] = 0;
  dest[3] = 0;
  dest[4] = 0;
  dest[5] = 0;
  dest[1] = &g_WCIsvListBaseDtor_Vtable;
  dest[1] = &g_WCIsvListBaseVariant124_Vtable;
  WCIsvListBase_CopyAppendAll(dest, source, (int)dest);
  result = v2;
  *(_DWORD *)(v2 + 4) = &g_WCIsvListBaseVariant134_Vtable;
  return result;
}
// 43D2BF: variable 'v2' is possibly undefined
// 50F0E4: using guessed type int (*off_50F0E4)();
// 50F0F4: using guessed type _DWORD (*off_50F0F4)(WCIsvListBase * this);
// 50F124: using guessed type void *off_50F124;
// 50F134: using guessed type void *off_50F134;

//----- (0043D2D0) --------------------------------------------------------
int  Battle_DeploySideUnitsByRoleBuckets(char *ownUnits, int ownCount, char *enemyUnits, int placementSide, int enemyCount)
{
  int ownDefenseTotal; // esi
  int ownAttackTotal; // edi
  int enemyAttackTotal; // ebp
  int ownIndex; // ebx
  char *ownCursor; // ecx
  int enemyIndex; // ebx
  char *enemyCursor; // ecx
  int enemyUnitDefense; // eax
  unsigned __int8 deployMode; // al
  float defenseRatioFloat; // [esp+10h] [ebp-24h]
  float attackRatioFloat; // [esp+14h] [ebp-20h]
  int enemyDefenseTotal; // [esp+20h] [ebp-14h]
  int attackRatio; // [esp+24h] [ebp-10h]
  int defenseRatio; // [esp+24h] [ebp-10h]
  int deploy_result;

  Diagnostics_TraceWorldMapActionEvent("battle_deploy_enter", ownCount, placementSide, enemyCount, *(__int16 *)ownUnits);
  ownDefenseTotal = 0;
  ownAttackTotal = 0;
  enemyAttackTotal = 0;
  ownIndex = 0;
  enemyDefenseTotal = 0;
  if ( ownCount > 0 )
  {
    ownCursor = ownUnits;
    do
    {
      ownAttackTotal += Unit_CalcEffectivenessA(ownCursor, 0);
      Unit_CalcEffectivenessB(ownCursor, 0);
      ++ownIndex;
      ownDefenseTotal += Unit_CalcEffectivenessC((__int16 *)ownCursor);
      ownCursor += UNIT_STACK_SLOT_STRIDE;
    }
    while ( ownIndex < ownCount );
  }
  enemyIndex = 0;
  if ( enemyCount > 0 )
  {
    enemyCursor = enemyUnits;
    do
    {
      enemyAttackTotal += Unit_CalcEffectivenessA(enemyCursor, 0);
      Unit_CalcEffectivenessB(enemyCursor, 0);
      ++enemyIndex;
      enemyUnitDefense = Unit_CalcEffectivenessC((__int16 *)enemyCursor);
      enemyCursor += UNIT_STACK_SLOT_STRIDE;
      enemyDefenseTotal += enemyUnitDefense;
    }
    while ( enemyIndex < enemyCount );
  }
  if ( enemyAttackTotal <= 0 )
    attackRatio = ownAttackTotal;
  else
    attackRatio = ownAttackTotal / enemyAttackTotal;
  attackRatioFloat = (float)attackRatio;
  if ( enemyDefenseTotal <= 0 )
    defenseRatio = ownDefenseTotal;
  else
    defenseRatio = ownDefenseTotal / enemyDefenseTotal;
  defenseRatioFloat = (float)defenseRatio;
  deployMode = defenseRatioFloat < g_Battle_RoleDeployRatioHighThreshold && (defenseRatioFloat <= g_Battle_RoleDeployRatioLowThreshold || SLODWORD(attackRatioFloat) > 1065353216);
  Battle_BuildRoleDeploymentBuckets((int)ownUnits, ownCount, deployMode);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_deploy_after_build",
    ownCount,
    deployMode,
    Diagnostics_CountBattleDeploymentBucketEntries(),
    *(__int16 *)ownUnits);
  deploy_result = Battle_PlaceRoleDeploymentBuckets(deployMode, placementSide);
  Diagnostics_TraceWorldMapActionEvent(
    "battle_deploy_after_place",
    deploy_result,
    Diagnostics_CountBattleUnitsTotal(),
    Diagnostics_CountBattleUnitsForOwner(ownUnits[2]),
    g_SelectedUnitIndex);
  return deploy_result;
}
// 43D2D0: could not find valid save-restore pair for ebx
// 4F18A7: using guessed type double dbl_4F18A7;
// 4F18AF: using guessed type double dbl_4F18AF;

//----- (0043D430) --------------------------------------------------------
int  Battle_BuildRoleDeploymentBuckets(int unitsPtr, int unitCount, unsigned __int8 deployMode)
{
  int result; // eax
  __int16 *unitRecord; // ecx
  int unitIndex; // edi
  int bucket1Count; // ebp
  int bucket2Count; // esi
  int bucket3Count; // [esp+4h] [ebp-20h]
  unsigned __int8 bucketCode; // [esp+Ch] [ebp-18h]

  memset(g_BattleDeploymentBucketStorage_5437DC, 0, 0xC0);
  result = 0;
  unitRecord = (__int16 *)(uintptr_t)(unsigned int)unitsPtr;
  unitIndex = 0;
  if ( unitCount > 0 )
  {
    bucket3Count = 0;
    bucket1Count = 0;
    bucket2Count = 0;
    do
    {
      bucketCode = g_BattleRoleDeploymentBucketTable[7 * deployMode + (unsigned __int8)g_UnitTypeRole[88 * *unitRecord]];
      if ( (bucketCode - bucketCode % 10) / 10 == 1 )
        g_BattleDeploymentBucketRole1[++bucket1Count] = (int)unitRecord;
      if ( (bucketCode - bucketCode % 10) / 10 == 2 )
        g_BattleDeploymentBucketRole2[++bucket2Count] = (int)unitRecord;
      result = (bucketCode - bucketCode % 10) / 10;
      if ( result == 3 )
      {
        result = bucket3Count * 4;
        g_BattleDeploymentBucketRole3[bucket3Count++] = (int)unitRecord;
      }
      ++unitIndex;
      unitRecord = (__int16 *)((char *)unitRecord + 31);
    }
    while ( unitIndex < unitCount );
  }
  return result;
}
// 43D466: variable 'v4' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 543808: using guessed type int dword_543808[];
// 543838: using guessed type int dword_543838[];
// 54386C: using guessed type int dword_54386C[];

//----- (0043D560) --------------------------------------------------------
signed int  Battle_PlaceUnitAtNextOpenDeploymentTile(unsigned __int8 *unitRecord, _DWORD *columnCursor, int isAttackerSide, int *rowCursor)
{
  int tileY; // ebp
  int nextRowRight; // edx
  int tileYLeft; // ecx
  int tileX2; // ebp
  char facingCode; // al
  signed int result; // eax
  int nextRowLeft; // edx
  char facingCode2; // al
  int tileYLeftKept; // [esp+8h] [ebp-18h]
  int tileX; // [esp+Ch] [ebp-14h]

  while ( 1 )
  {
    while ( 1 )
    {
      tileY = isAttackerSide ? 2 - *rowCursor : *rowCursor + *(_DWORD *)(g_MapData + 804) - 3;
      tileX = *(_DWORD *)(g_MapData + 800) / 2 + *columnCursor;
      if ( tileX < *(_DWORD *)(g_MapData + 800) )
        break;
      *columnCursor = 0;
      nextRowRight = ++*rowCursor % 3;
      *rowCursor = nextRowRight;
    }
    if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)unitRecord, tileY, tileX) )
    {
      facingCode = isAttackerSide ? 2 : 6;
      result = Battle_PlaceUnit(unitRecord, tileY, facingCode, tileX);
      if ( result )
        break;
    }
    while ( 1 )
    {
      tileYLeft = isAttackerSide ? 2 - *rowCursor : *rowCursor + *(_DWORD *)(g_MapData + 804) - 3;
      tileX2 = *(_DWORD *)(g_MapData + 800) / 2 - *columnCursor;
      tileYLeftKept = tileYLeft;
      if ( tileX2 >= 0 )
        break;
      *columnCursor = 0;
      nextRowLeft = ++*rowCursor % 3;
      *rowCursor = nextRowLeft;
    }
    if ( UnitBattle_GetTileMoveCostOrZero(*(__int16 *)unitRecord, tileYLeft, tileX2) )
    {
      facingCode2 = isAttackerSide ? 2 : 6;
      result = Battle_PlaceUnit(unitRecord, tileYLeftKept, facingCode2, tileX2);
      if ( result )
      {
        ++*columnCursor;
        return result;
      }
    }
    ++*columnCursor;
  }
  return result;
}
// 532048: using guessed type int g_MapData;

//----- (0043D6E0) --------------------------------------------------------
int  Battle_PlaceRoleDeploymentBuckets(unsigned __int8 deployMode, int placementSide)
{
  int candidateReadByteOffset; // edi
  int bestRow; // ebx
  int bestCol; // esi
  int bucketColIndex; // ecx
  int result; // eax
  int bestEntryOffset; // esi
  int candidateTableIndex; // edx
  char *bestUnitPtr; // ebp
  int bestUnitTypeOffset; // eax
  unsigned int bestBucketTableValue; // edx
  int bestEffectiveness; // ebp
  int rowCursor; // [esp+0h] [ebp-44h] BYREF
  int columnCursor; // [esp+4h] [ebp-40h] BYREF
  int candidateRankMod10; // [esp+8h] [ebp-3Ch]
  int bucketRowByteOffset; // [esp+Ch] [ebp-38h]
  int placementSideCopy; // [esp+10h] [ebp-34h]
  int rowReadByteOffsetBase; // [esp+14h] [ebp-30h]
  int rowStorageByteOffsetBase; // [esp+18h] [ebp-2Ch]
  int placementIteration; // [esp+1Ch] [ebp-28h]
  int bucketHasEntry; // [esp+20h] [ebp-24h]
  int bucketRow; // [esp+24h] [ebp-20h]
  int storageByteOffset; // [esp+28h] [ebp-1Ch]
  int deployModeTableBase; // [esp+2Ch] [ebp-18h]
  unsigned __int8 deployModeCopy; // [esp+30h] [ebp-14h]
  unsigned __int8 *candidate;
  unsigned __int8 *best_candidate;

  deployModeCopy = deployMode;
  placementSideCopy = placementSide;
  rowCursor = 0;
  bucketRow = 1;
  bucketRowByteOffset = 48;
  do
  {
    columnCursor = 0;
    bucketHasEntry = 0;
    placementIteration = 0;
    rowCursor = (rowCursor + 1) % 3;
    rowReadByteOffsetBase = bucketRowByteOffset;
    rowStorageByteOffsetBase = bucketRowByteOffset;
    do
    {
      candidateReadByteOffset = rowReadByteOffsetBase;
      bestRow = 0;
      bestCol = 0;
      bucketColIndex = 0;
      storageByteOffset = rowStorageByteOffsetBase;
      do
      {
        result = storageByteOffset;
        if ( *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + storageByteOffset) )
        {
          bucketHasEntry = 1;
          if ( !bestRow )
          {
            bestRow = bucketRow;
            bestCol = bucketColIndex;
          }
          candidate = BattleDeploymentBucketReadPointer(candidateReadByteOffset);
          candidateTableIndex = 7 * deployModeCopy + (unsigned __int8)g_UnitTypeRole[88 * *(__int16 *)candidate];
          deployModeTableBase = 7 * deployModeCopy;
          best_candidate = BattleDeploymentBucketReadPointer(48 * bestRow + 4 * bestCol);
          bestUnitPtr = (char *)best_candidate;
          bestUnitTypeOffset = 88 * *(__int16 *)bestUnitPtr;
          candidateRankMod10 = (unsigned __int8)g_BattleRoleDeploymentBucketTable[candidateTableIndex] % 10;
          bestBucketTableValue = (unsigned __int8)g_BattleRoleDeploymentBucketTable[(unsigned __int8)g_UnitTypeRole[bestUnitTypeOffset] + deployModeTableBase];
          deployModeTableBase = 10;
          result = bestBucketTableValue / 10LL;
          if ( bestBucketTableValue % 10LL <= candidateRankMod10 )
          {
            bestEffectiveness = Unit_CalcEffectivenessA(bestUnitPtr, 0);
            result = Unit_CalcEffectivenessA((char *)candidate, 0);
            if ( bestEffectiveness <= result )
            {
              bestRow = bucketRow;
              bestCol = bucketColIndex;
            }
          }
          else
          {
            bestRow = bucketRow;
            bestCol = bucketColIndex;
          }
        }
        candidateReadByteOffset += 4;
        ++bucketColIndex;
        storageByteOffset += 4;
      }
      while ( bucketColIndex < 12 );
      if ( bucketHasEntry )
      {
        bestEntryOffset = 48 * bestRow + 4 * bestCol;
        if ( *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + bestEntryOffset) )
        {
          result = Battle_PlaceUnitAtNextOpenDeploymentTile(BattleDeploymentBucketReadPointer(bestEntryOffset), &columnCursor, placementSideCopy, &rowCursor);
          *(int *)((char *)g_BattleDeploymentBucketStorage_5437DC + bestEntryOffset) = 0;
        }
      }
      ++placementIteration;
    }
    while ( placementIteration < 12 );
    bucketRowByteOffset += 48;
    ++bucketRow;
  }
  while ( bucketRow < 4 );
  return result;
}
// 43D77B: variable 'v5' is possibly undefined
// 5437DC: using guessed type int dword_5437DC[];

//----- (0043D8C0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v1(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V1 = v4;
  return result;
}
// 43D8CB: variable 'v4' is possibly undefined
// 5438A4: using guessed type int dword_5438A4;

//----- (0043D8E0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v1(int buildingPtr, int stringBuffer, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(stringBuffer, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrDw_3;
  else
    backgroundPath = aCastle_pogDw_3;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV1SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrDw_5;
  else
    palettePath = aCastle_pogDw_5;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_6);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V1);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V1 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V1, renderContext);
  }
  while ( !g_GateDoorDialogExitFlag_V1 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV1SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43D934: variable 'v5' is possibly undefined
// 43D93C: variable 'v8' is possibly undefined
// 43D971: variable 'v10' is possibly undefined
// 43D97F: variable 'v13' is possibly undefined
// 43D98D: variable 'v14' is possibly undefined
// 43D9EE: variable 'v15' is possibly undefined
// 43D9EE: variable 'v16' is possibly undefined
// 43DA31: variable 'v17' is possibly undefined
// 43DA53: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515A90: using guessed type _DWORD dword_515A90[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438A0: using guessed type int dword_5438A0;
// 5438A4: using guessed type int dword_5438A4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043DAC0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v2(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V2 = v4;
  return result;
}
// 43DACB: variable 'v4' is possibly undefined
// 5438B0: using guessed type int dword_5438B0;

//----- (0043DAE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v2(int buildingPtr, int a2, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(a2, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrDw_6;
  else
    backgroundPath = aCastle_pogDw_6;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV2SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrDw_8;
  else
    palettePath = aCastle_pogDw_8;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_7);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V2);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V2 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V2, renderContext);
  }
  while ( !g_GateDoorDialogExitFlag_V2 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV2SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43DB34: variable 'v5' is possibly undefined
// 43DB3C: variable 'v8' is possibly undefined
// 43DB71: variable 'v10' is possibly undefined
// 43DB7F: variable 'v13' is possibly undefined
// 43DB8D: variable 'v14' is possibly undefined
// 43DBEE: variable 'v15' is possibly undefined
// 43DBEE: variable 'v16' is possibly undefined
// 43DC31: variable 'v17' is possibly undefined
// 43DC53: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515B10: using guessed type _DWORD dword_515B10[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438AC: using guessed type int dword_5438AC;
// 5438B0: using guessed type int dword_5438B0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043DCC0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v3(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V3 = v4;
  return result;
}
// 43DCCB: variable 'v4' is possibly undefined
// 5438BC: using guessed type int dword_5438BC;

//----- (0043DCE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v3(int buildingPtr, int objectArray, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(objectArray, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrDw_9;
  else
    backgroundPath = aCastle_pogDw_9;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV3SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrD_11;
  else
    palettePath = aCastle_pogD_11;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_8);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V3);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V3 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V3, renderContext);
  }
  while ( !g_GateDoorDialogExitFlag_V3 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV3SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43DD34: variable 'v5' is possibly undefined
// 43DD3C: variable 'v8' is possibly undefined
// 43DD71: variable 'v10' is possibly undefined
// 43DD7F: variable 'v13' is possibly undefined
// 43DD8D: variable 'v14' is possibly undefined
// 43DDEE: variable 'v15' is possibly undefined
// 43DDEE: variable 'v16' is possibly undefined
// 43DE31: variable 'v17' is possibly undefined
// 43DE53: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515B90: using guessed type _DWORD dword_515B90[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438B8: using guessed type int dword_5438B8;
// 5438BC: using guessed type int dword_5438BC;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043DEC0) --------------------------------------------------------
int  Building_HandleGateDoorDialogClose_v4(int widget, int delayTicks)
{
  int result; // eax
  int v4; // edx

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(widget, delayTicks);
  g_GateDoorDialogExitFlag_V4 = v4;
  return result;
}
// 43DECB: variable 'v4' is possibly undefined
// 5438C8: using guessed type int dword_5438C8;

//----- (0043DEE0) --------------------------------------------------------
int  Building_ShowGateDoorDialog_v4(int buildingPtr, int ctorArrayBuffer, DWORD renderContext)
{
  int useChrTheme; // esi
  int v5; // ecx
  char *backgroundPath; // edx
  int renderSurface; // edi
  int v8; // ecx
  _DWORD *spriteSet; // eax
  int v10; // ecx
  char spriteSetByte; // bl
  CHAR *palettePath; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  unsigned __int8 paletteBuffer[1040]; // [esp+0h] [ebp-410h] BYREF

  useChrTheme = *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingPtr + 2) + gameData + 140063);
  _wcpp_4_ctor_array__(ctorArrayBuffer, 256);
  if ( useChrTheme )
    backgroundPath = aCastle_chrD_12;
  else
    backgroundPath = aCastle_pogD_12;
  renderSurface = *(_DWORD *)(g_PrimaryRenderSurface + 184);
  (*(void (__fastcall **)(_DWORD, char *, int))(renderSurface + 48))(0, backgroundPath, v5);
  spriteSet = (_DWORD *)Mem_Alloc(4112, v8, (char)paletteBuffer, renderContext);
  spriteSetByte = (char)spriteSet;
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, (char)spriteSet);
  g_GateDoorDialogV4SpriteSet = (int)spriteSet;
  if ( useChrTheme )
    palettePath = aCastle_chrD_14;
  else
    palettePath = aCastle_pogD_14;
  Palette_LoadOrBuildBlendLookupTable(palettePath, (int)paletteBuffer, v10, renderContext);
  Render_LoadResourceSprite_v4(10, paletteBuffer, v13, spriteSetByte, renderContext);
  Render_LoadResourceSprite_v4(8, paletteBuffer, v14, spriteSetByte, renderContext);
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  Render_ReleaseSurface(8, renderContext);
  UI_DrawTextFmt(renderSurface, 193, 439, 80, 3, (int)aS_9);
  Render_ReleaseSurface(10, renderContext);
  UI_DrawFormattedTokenLine(95, v15, v16, 140);
  UIWidgetTable_InitDrawStates(g_GateDoorDialogWidgetTable_V4);
  (*(void (**)(void))(*((_DWORD *)g_RenderDevice + 46) + 36))();
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, paletteBuffer, 20);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)paletteBuffer, v17, renderContext);
  RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
  Render_Present((int)g_RenderState);
  g_GateDoorDialogExitFlag_V4 = v18;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(g_GateDoorDialogWidgetTable_V4, renderContext);
  }
  while ( !g_GateDoorDialogExitFlag_V4 );
  DLXSpriteSet_ReleaseAndClear(&g_GateDoorDialogV4SpriteSet);
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 43DF34: variable 'v5' is possibly undefined
// 43DF3C: variable 'v8' is possibly undefined
// 43DF71: variable 'v10' is possibly undefined
// 43DF7F: variable 'v13' is possibly undefined
// 43DF8D: variable 'v14' is possibly undefined
// 43DFEE: variable 'v15' is possibly undefined
// 43DFEE: variable 'v16' is possibly undefined
// 43E031: variable 'v17' is possibly undefined
// 43E053: variable 'v18' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 515C10: using guessed type _DWORD dword_515C10[3];
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5438C4: using guessed type int dword_5438C4;
// 5438C8: using guessed type int dword_5438C8;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0043E0C0) --------------------------------------------------------
BOOL  Building_HasFreeAdjacentExitTile(unsigned __int8 *building)
{
  int *neighborOffsets; // esi
  int i; // ebp
  int neighborX; // ebx
  int neighborY; // ecx

  if ( building[4] )
    neighborOffsets = (int *)&g_LargeBuildingNeighborOffsets;
  else
    neighborOffsets = Map_NeighborDX;
  for ( i = 0; i < 12; ++i )
  {
    neighborX = *neighborOffsets + *building;
    neighborY = neighborOffsets[1] + building[1];
    if ( neighborX >= 0
      && neighborX < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
      && neighborY >= 0
      && neighborY < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && *(unsigned __int16 *)(TILE_INDEX(neighborX, neighborY)) == 0xFFFF
      && Map_GetUnitTileMoveCostOrZero(building[2], 0, neighborY, neighborX) )
    {
      break;
    }
    neighborOffsets += 2;
  }
  return i != 12;
}
// 513334: using guessed type int dword_513334[];
// 5202E4: using guessed type int gameData;

//----- (0043E160) --------------------------------------------------------
signed int  Building_UnitsLeave(unsigned __int8 *building, int *exitSlots, double gameTime)
{
  int *neighborOffset; // esi
  int i; // edi
  int neighborX; // ebx
  int neighborY; // ecx
  int *chosenOffset; // edx
  int spawnY; // edi
  int spawnX; // esi
  char facing; // al
  int *slotIndexPtr; // eax
  int movedCount; // edx
  __int16 *destSlot; // ebx
  unsigned __int8 *srcSlot; // esi
  int movedSlotIndex; // esi
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  double v21; // st7
  double v22; // st7
  int v23; // ecx
  int *neighborOffsets; // [esp+0h] [ebp-20h]
  __int16 *newStackRecord; // [esp+8h] [ebp-18h]

  Debug_Log(exitSlots[3], exitSlots[2], (DWORD)building, (int)aBuildingUnitsLeave);
  if ( building[4] )
    neighborOffsets = (int *)&g_LargeBuildingNeighborOffsets;
  else
    neighborOffsets = Map_NeighborDX;
  neighborOffset = neighborOffsets;
  for ( i = 0; i < 12; ++i )
  {
    neighborX = *neighborOffset + *building;
    neighborY = neighborOffset[1] + building[1];
    if ( neighborX >= 0
      && neighborX < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET)
      && neighborY >= 0
      && neighborY < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET)
      && *(unsigned __int16 *)(TILE_INDEX(neighborX, neighborY)) == 0xFFFF
      && Map_GetUnitTileMoveCostOrZero(building[2], 0, neighborY, neighborX) )
    {
      break;
    }
    neighborOffset += 2;
  }
  if ( i == 12 )
    return -1;
  chosenOffset = &neighborOffsets[2 * i];
  spawnY = building[1] + chosenOffset[1];
  spawnX = *building + *chosenOffset;
  facing = Facing_DirectionFromDelta8(*chosenOffset, chosenOffset[1]);
  Diagnostics_TraceWorldMapActionEvent("building_units_leave_request", -1, *building, building[1], exitSlots[0]);
  Unit_Create(0xFFFFFFFF, building[2], spawnX, facing, spawnY);
  slotIndexPtr = exitSlots;
  movedCount = 0;
  newStackRecord = (__int16 *)(UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(spawnX, spawnY)) + gameData + UNIT_STACK_TABLE_OFFSET);
  Diagnostics_TraceWorldMapActionEvent(
    "building_units_leave_spawn",
    *(unsigned __int16 *)(TILE_INDEX(spawnX, spawnY)),
    spawnX,
    spawnY,
    exitSlots[0]);
  destSlot = newStackRecord + 3;
  if ( *exitSlots != -1 )
  {
    do
    {
      srcSlot = &building[31 * *slotIndexPtr + 18];
      qmemcpy(destSlot, srcSlot, 0x1Cu);
      srcSlot += 28;
      destSlot[14] = *(_WORD *)srcSlot;
      *((_BYTE *)destSlot + 30) = srcSlot[2];
      *(_WORD *)&building[31 * *slotIndexPtr + 18] = -1;
      BUILDING_GARRISON_SERVICE_STATE(building, *slotIndexPtr) &= ~BUILDING_GARRISON_TRAINING_TURNS_MASK;
      movedSlotIndex = *slotIndexPtr++;
      ++movedCount;
      destSlot = (__int16 *)((char *)destSlot + 31);
      BUILDING_GARRISON_SERVICE_STATE(building, movedSlotIndex) &= ~BUILDING_GARRISON_REPAIR_TURNS_MASK;
    }
    while ( movedCount < 10 && *slotIndexPtr != -1 );
  }
  UnitStack_ClearRemainingActionPoints(newStackRecord, (DWORD)building, gameTime);
  Rules_LinkArmyFact(newStackRecord, v17, v18, gameTime, (char)destSlot, (DWORD)building);
  Rules_SyncArmyFactStrength(newStackRecord, 0, v19, (char)destSlot, (DWORD)building, gameTime);
  Building_OnGarrisonChange(*(unsigned __int16 *)(TILE_INDEX(*building, building[1])) - TILE_OCCUPANT_BUILDING_INDEX_BASE, v20, v21);
  UnitStack_UpdateVision(*(unsigned __int16 *)(TILE_INDEX(*newStackRecord, newStackRecord[1])));
  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(*(unsigned __int16 *)(TILE_INDEX(*newStackRecord, newStackRecord[1])), v22);
  Debug_Log(v23, (char)destSlot, (DWORD)building, (int)aBuildings_unit);
  Unit_DebugDumpFormationSizes((int)newStackRecord, (DWORD)building);
  return *(unsigned __int16 *)(TILE_INDEX(*newStackRecord, newStackRecord[1]));
}
// 43E33C: variable 'v17' is possibly undefined
// 43E33C: variable 'v18' is possibly undefined
// 43E347: variable 'v19' is possibly undefined
// 43E38B: variable 'v20' is possibly undefined
// 43E38B: variable 'v21' is possibly undefined
// 43E40B: variable 'v22' is possibly undefined
// 43E42B: variable 'v23' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 5202E4: using guessed type int gameData;

//----- (0043E4B0) --------------------------------------------------------
int  Building_CountFreeGarrisonSlots(int buildingId)
{
  int buildingRecord; // esi
  int freeCount; // ebx
  int slotPtr; // eax
  int i; // edx
  int slotLimit; // ecx

  buildingRecord = UNIT_RECORD(buildingId);
  freeCount = 0;
  slotPtr = buildingRecord;
  for ( i = 0; ; ++i )
  {
    slotLimit = *(_BYTE *)(buildingRecord + 4) ? 12 : 10;
    if ( i >= slotLimit )
      break;
    if ( *(__int16 *)(slotPtr + 18) == -1 )
      ++freeCount;
    slotPtr += 31;
  }
  return freeCount;
}
// 5202E4: using guessed type int gameData;
