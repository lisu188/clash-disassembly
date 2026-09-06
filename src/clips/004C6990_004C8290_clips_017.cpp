/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004C6990) --------------------------------------------------------
int  Class_BloadRefreshHandlerRecord(int *buf, int obji, double a3)
{
  int theSlot; // ecx
  int v4; // edx
  unsigned int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  unsigned int v12; // edx
  unsigned int v13; // edx
  unsigned int v14; // edx
  unsigned int v15; // edx
  int clsIndex; // edx
  int clsPtr; // eax
  int slotName; // eax
  int defaultIndex; // edi
  int constraintIndex; // ebx
  int result; // eax
  _DWORD *freeNode; // ebp
  signed int defaultValue; // eax
  _DWORD *valuePtr; // ebx
  int defaultExprIndex; // eax
  int defaultExpr; // edx
  int v28 CLASH95_UNUSED; // ecx

  theSlot = 44 * obji + g_DefclassSlotDescriptorArrayPtr;
  v4 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~0x40u;
  *(_DWORD *)(uintptr_t)theSlot |= v4 & 0x40;
  v5 = (unsigned int)(*buf << 24) >> 31;
  *(_BYTE *)(uintptr_t)(theSlot + 1) &= ~1u;
  *(_DWORD *)(uintptr_t)theSlot |= (v5 & 1) << 8;
  v6 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~1u;
  *(_DWORD *)(uintptr_t)theSlot |= v6 & 1;
  v7 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~2u;
  *(_DWORD *)(uintptr_t)theSlot |= v7 & 2;
  v8 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~4u;
  *(_DWORD *)(uintptr_t)theSlot |= v8 & 4;
  v9 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~8u;
  *(_DWORD *)(uintptr_t)theSlot |= v9 & 8;
  v10 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~0x10u;
  *(_DWORD *)(uintptr_t)theSlot |= v10 & 0x10;
  v11 = *buf;
  *(_BYTE *)(uintptr_t)theSlot &= ~0x20u;
  *(_DWORD *)(uintptr_t)theSlot |= v11 & 0x20;
  v12 = (unsigned int)(*buf << 23) >> 31;
  *(_BYTE *)(uintptr_t)(theSlot + 1) &= ~2u;
  *(_DWORD *)(uintptr_t)theSlot |= (v12 & 1) << 9;
  v13 = (unsigned int)(*buf << 22) >> 31;
  *(_BYTE *)(uintptr_t)(theSlot + 1) &= ~4u;
  *(_DWORD *)(uintptr_t)theSlot |= (v13 & 1) << 10;
  v14 = (unsigned int)(*buf << 21) >> 31;
  *(_BYTE *)(uintptr_t)(theSlot + 1) &= ~8u;
  *(_DWORD *)(uintptr_t)theSlot |= (v14 & 1) << 11;
  v15 = (unsigned int)(*buf << 20) >> 31;
  *(_BYTE *)(uintptr_t)(theSlot + 1) &= ~0x10u;
  *(_DWORD *)(uintptr_t)theSlot |= (v15 & 1) << 12;
  clsIndex = buf[1];
  if ( clsIndex == -1 )
    clsPtr = 0;
  else
    clsPtr = g_Clips_DefclassArrayBase + 124 * clsIndex;
  *(_DWORD *)(uintptr_t)(theSlot + 4) = clsPtr;
  *(_DWORD *)(uintptr_t)(theSlot + 8) = 28 * buf[2] + g_DefclassSlotTable;
  slotName = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * buf[5]);
  *(_DWORD *)(uintptr_t)(theSlot + 12) = slotName;
  ++*(_DWORD *)(uintptr_t)(slotName + 4);
  defaultIndex = buf[3];
  if ( defaultIndex == -1 )
  {
    *(_DWORD *)(uintptr_t)(theSlot + 16) = 0;
  }
  else if ( (*(_BYTE *)(uintptr_t)theSlot & 0x40) != 0 )
  {
    *(_DWORD *)(uintptr_t)(theSlot + 16) = g_ClipsPackedExpressionArray + 14 * defaultIndex;
  }
  else
  {
    freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *freeNode;
      defaultValue = g_ClipsMemFreeListTemp;
    }
    else
    {
      defaultValue = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    *(_DWORD *)(uintptr_t)(theSlot + 16) = defaultValue;
    valuePtr = (_DWORD *)(uintptr_t)defaultValue;
    defaultExprIndex = buf[3];
    if ( defaultExprIndex == -1 )
      defaultExpr = 0;
    else
      defaultExpr = 14 * defaultExprIndex + g_ClipsPackedExpressionArray;
    Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)(uintptr_t)theSlot << 30 >> 31, defaultExpr, valuePtr, a3);
    Rules_ValueInstall(*(_DWORD *)(uintptr_t)(theSlot + 16), theSlot);
  }
  constraintIndex = buf[4];
  if ( constraintIndex == -1 )
    result = 0;
  else
    result = g_ClipsConstraintRecordArrayBase + 42 * constraintIndex;
  *(_DWORD *)(uintptr_t)(theSlot + 24) = 0;
  *(_DWORD *)(uintptr_t)(theSlot + 40) = 0;
  *(_DWORD *)(uintptr_t)(theSlot + 20) = result;
  BYTE1(result) = *(_BYTE *)(uintptr_t)theSlot;
  *(_DWORD *)(uintptr_t)(theSlot + 28) = 0;
  if ( (result & 0x100) != 0 )
  {
    *(_DWORD *)(uintptr_t)(theSlot + 40) = 0;
    *(_DWORD *)(uintptr_t)(theSlot + 32) = theSlot;
  }
  return result;
}
// 4C6AEC: conditional instruction was optimized away because edi.4!=FFFFFFFF
// 4C6B01: variable 'v3' is possibly undefined
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3BC: using guessed type int dword_51B3BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E674: using guessed type int dword_54E674;
// 54E688: using guessed type int dword_54E688;
// 54E68C: using guessed type int dword_54E68C;

//----- (004C6C00) --------------------------------------------------------
_DWORD * Class_BloadRefreshSlotRecord(_DWORD *buf, int obji)
{
  _DWORD *result; // eax
  int nameSym; // edx
  int putHandlerSym; // edx
  int hashIndex; // edx

  result = (_DWORD *)(uintptr_t)(g_DefclassSlotTable + 28 * obji);
  result[2] = *buf;
  nameSym = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * buf[2]);
  result[3] = nameSym;
  ++*(_DWORD *)(uintptr_t)(nameSym + 4);
  putHandlerSym = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * buf[3]);
  result[4] = putHandlerSym;
  ++*(_DWORD *)(uintptr_t)(putHandlerSym + 4);
  hashIndex = buf[1];
  *result = hashIndex;
  result[5] = *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * hashIndex);
  *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * *result) = (_DWORD)(uintptr_t)(result);
  return result;
}
// 51AD70: using guessed type int dword_51AD70;
// 51B3BC: using guessed type int dword_51B3BC;
// 54E674: using guessed type int dword_54E674;

//----- (004C6C70) --------------------------------------------------------
int  Class_BloadRefreshSlotNameLink(_DWORD *buf, int obji)
{
  int result; // eax

  if ( *buf == -1 )
  {
    result = 0;
    *(_DWORD *)(uintptr_t)(g_DefclassBloadSlotNameLinkArray + 4 * obji) = 0;
  }
  else
  {
    result = 44 * *buf + g_DefclassSlotDescriptorArrayPtr;
    *(_DWORD *)(uintptr_t)(g_DefclassBloadSlotNameLinkArray + 4 * obji) = result;
  }
  return result;
}
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;

//----- (004C6CA0) --------------------------------------------------------
char * Class_BloadRefreshTemplateSlotRecord(int *buf, int obji)
{
  char *result; // eax
  int v4; // edx
  int v5; // edx
  int clsIndex; // ebp
  int clsPtr; // edx
  int nameSym; // edx
  int actionsIndex; // esi
  int actionsPtr; // edx
  char flagsByte; // dl
  int watchHandlers; // edx

  result = (char *)(uintptr_t)(g_DefclassBloadTemplateSlotArray + 36 * obji);
  v4 = *buf;
  *result &= ~1u;
  *(_DWORD *)result |= v4 & 1;
  v5 = *buf;
  *result &= 0xF9u;
  *(_DWORD *)result |= v5 & 6;
  *((_DWORD *)result + 4) = buf[1];
  *((_DWORD *)result + 5) = buf[2];
  *((_DWORD *)result + 6) = buf[3];
  clsIndex = buf[5];
  if ( clsIndex == -1 )
    clsPtr = 0;
  else
    clsPtr = 124 * clsIndex + g_Clips_DefclassArrayBase;
  *((_DWORD *)result + 3) = clsPtr;
  nameSym = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * buf[4]);
  *((_DWORD *)result + 2) = nameSym;
  ++*(_DWORD *)(uintptr_t)(nameSym + 4);
  actionsIndex = buf[6];
  if ( actionsIndex == -1 )
    actionsPtr = 0;
  else
    actionsPtr = 14 * actionsIndex + g_ClipsPackedExpressionArray;
  *((_DWORD *)result + 8) = 0;
  *((_DWORD *)result + 7) = actionsPtr;
  flagsByte = *result;
  *((_DWORD *)result + 1) = 0;
  *result = flagsByte & 0xF7;
  watchHandlers = g_Rules_WatchMessageHandlers & 1;
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * watchHandlers;
  return result;
}
// 51AD4C: using guessed type int dword_51AD4C;
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3C4: using guessed type int dword_51B3C4;
// 54E674: using guessed type int dword_54E674;
// 54E688: using guessed type int dword_54E688;

//----- (004C6D80) --------------------------------------------------------
signed int Class_ClearBloadedData(void)
{
  signed int result; // eax
  int defclassIdCount; // edx
  int classIndex; // ecx
  int classOffset; // edx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  int slotDescIndex; // ecx
  int slotDescOffset; // edx
  int v10; // edx
  int v11; // ecx
  int slotIndex; // ecx
  int slotOffset; // edx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int templateSlotIndex; // ecx
  int templateSlotOffset; // edx
  int v21; // edx

  result = 12 * g_DefclassNameTableCount;
  if ( 12 * g_DefclassNameTableCount )
  {
    result = Mem_ReleasePoolBlock(g_Class_BloadModuleArray, 12 * g_DefclassNameTableCount);
    HIWORD(defclassIdCount) = 0;
    g_Class_BloadModuleArray = 0;
    g_DefclassNameTableCount = 0;
    if ( g_ClipsBloadDefclassCount )
    {
      LOWORD(defclassIdCount) = g_ClipsDefclassIdCount;
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_ClipsDefclassIdTable, 4 * defclassIdCount);
      g_ClipsDefclassIdTable = 0;
      g_ClipsDefclassIdCount = 0;
      if ( g_ClipsBloadDefclassCount > 0 )
      {
        classOffset = 0;
        do
        {
          Rules_ReleaseSymbolReference((int *)(uintptr_t)(classOffset + g_Clips_DefclassArrayBase), classIndex);
          Rules_DecrementBitmapCount(*(_DWORD *)(uintptr_t)(v4 + g_Clips_DefclassArrayBase + 104), v5);
          Class_RemoveFromHashTable(v6 + g_Clips_DefclassArrayBase);
          classOffset = v7 + 124;
        }
        while ( classIndex < g_ClipsBloadDefclassCount );
      }
      slotDescIndex = 0;
      if ( g_ClipsDefclassBsaveHandlerCount > 0 )
      {
        slotDescOffset = 0;
        do
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(slotDescOffset + g_DefclassSlotDescriptorArrayPtr + 12), slotDescIndex);
          if ( *(_DWORD *)(uintptr_t)(v10 + g_DefclassSlotDescriptorArrayPtr + 16) && (*(_BYTE *)(uintptr_t)(v10 + g_DefclassSlotDescriptorArrayPtr) & 0x40) == 0 )
          {
            Rules_ValueDeinstall(*(_DWORD *)(uintptr_t)(v10 + g_DefclassSlotDescriptorArrayPtr + 16), v11);
            g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(v10 + g_DefclassSlotDescriptorArrayPtr + 16);
            *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
            *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
          }
          slotDescIndex = v11 + 1;
          slotDescOffset = v10 + 44;
        }
        while ( slotDescIndex < g_ClipsDefclassBsaveHandlerCount );
      }
      slotIndex = 0;
      if ( g_Defclass_SlotRecordCount > 0 )
      {
        slotOffset = 0;
        do
        {
          *(_DWORD *)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + 4 * *(_DWORD *)(uintptr_t)(slotOffset + g_DefclassSlotTable)) = 0;
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(slotOffset + g_DefclassSlotTable + 12), slotIndex);
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(v14 + g_DefclassSlotTable + 16), v15 + 1);
          slotOffset = v16 + 28;
        }
        while ( slotIndex < g_Defclass_SlotRecordCount );
      }
      if ( 124 * g_ClipsBloadDefclassCount )
      {
        Mem_ReleasePoolBlock(g_Clips_DefclassArrayBase, 124 * g_ClipsBloadDefclassCount);
        g_Clips_DefclassArrayBase = 0;
        g_ClipsBloadDefclassCount = 0;
      }
      if ( 4 * g_ClipsBloadClassLinkCount )
      {
        Mem_ReleasePoolBlock(g_DefclassLinkTable, 4 * g_ClipsBloadClassLinkCount);
        g_DefclassLinkTable = v17;
        g_ClipsBloadClassLinkCount = v17;
      }
      if ( 44 * g_ClipsDefclassBsaveHandlerCount )
      {
        Mem_ReleasePoolBlock(g_DefclassSlotDescriptorArrayPtr, 44 * g_ClipsDefclassBsaveHandlerCount);
        g_DefclassSlotDescriptorArrayPtr = 0;
        g_ClipsDefclassBsaveHandlerCount = 0;
      }
      result = 28 * g_Defclass_SlotRecordCount;
      if ( 28 * g_Defclass_SlotRecordCount )
      {
        Mem_ReleasePoolBlock(g_DefclassSlotTable, 28 * g_Defclass_SlotRecordCount);
        result = 0;
        g_DefclassSlotTable = 0;
        g_Defclass_SlotRecordCount = 0;
      }
      if ( 4 * g_Defclass_SlotNameLinkCount )
      {
        result = Mem_ReleasePoolBlock(g_DefclassBloadSlotNameLinkArray, 4 * g_Defclass_SlotNameLinkCount);
        g_DefclassBloadSlotNameLinkArray = v18;
        g_Defclass_SlotNameLinkCount = v18;
      }
      if ( 4 * g_ClipsDefclassBsaveIndexArrayCount )
      {
        result = Mem_ReleasePoolBlock(g_Class_BloadClassLinkArray, 4 * g_ClipsDefclassBsaveIndexArrayCount);
        g_Class_BloadClassLinkArray = 0;
        g_ClipsDefclassBsaveIndexArrayCount = 0;
      }
    }
    if ( g_ClipsBloadSlotRecordCount )
    {
      templateSlotIndex = 0;
      if ( g_ClipsBloadSlotRecordCount > 0 )
      {
        templateSlotOffset = 0;
        do
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(templateSlotOffset + g_DefclassBloadTemplateSlotArray + 8), templateSlotIndex + 1);
          templateSlotOffset = v21 + 36;
        }
        while ( templateSlotIndex < g_ClipsBloadSlotRecordCount );
      }
      result = 36 * g_ClipsBloadSlotRecordCount;
      if ( 36 * g_ClipsBloadSlotRecordCount )
      {
        Mem_ReleasePoolBlock(g_DefclassBloadTemplateSlotArray, 36 * g_ClipsBloadSlotRecordCount);
        g_DefclassBloadTemplateSlotArray = 0;
        result = Mem_ReleasePoolBlock(g_Class_BloadSlotNameMapArray, 4 * g_ClipsBloadSlotRecordCount);
        g_Class_BloadSlotNameMapArray = 0;
        g_ClipsBloadSlotRecordCount = 0;
      }
    }
  }
  return result;
}
// 4C6E10: variable 'v2' is possibly undefined
// 4C6E1A: variable 'v4' is possibly undefined
// 4C6E1E: variable 'v5' is possibly undefined
// 4C6E28: variable 'v6' is possibly undefined
// 4C6E36: variable 'v7' is possibly undefined
// 4C6E60: variable 'v10' is possibly undefined
// 4C6E70: variable 'v11' is possibly undefined
// 4C6EDB: variable 'v12' is possibly undefined
// 4C6EE5: variable 'v14' is possibly undefined
// 4C6EE9: variable 'v15' is possibly undefined
// 4C6EF5: variable 'v16' is possibly undefined
// 4C6F4D: variable 'v17' is possibly undefined
// 4C6FCD: variable 'v18' is possibly undefined
// 4C7021: variable 'v19' is possibly undefined
// 4C702D: variable 'v21' is possibly undefined
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;
// 51AD70: using guessed type int dword_51AD70;
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;
// 51B3BC: using guessed type int dword_51B3BC;
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C4: using guessed type int dword_51B3C4;
// 51B3C8: using guessed type int dword_51B3C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C70F0) --------------------------------------------------------
int Deffacts_CommandDefinitions(void)
{
  int v0; // ecx

  Rules_AddResetFunction((int)(intptr_t)aDeffacts_0, (int)(intptr_t)Deffacts_Reset, 0);
  Rules_AddClearFunction((int)(intptr_t)aDeffacts_0, (int)(intptr_t)Deffacts_ClearAction, 0);
  Rules_AddSaveFunction((int)(intptr_t)aDeffacts_0, (int)(intptr_t)Deffacts_Save, 10);
  Rules_RegisterHostFunction(aGetDeffactsLis, 109, v0, (int)(intptr_t)Deffacts_GetListFunction, (int)(intptr_t)a01w_6);
  Rules_RegisterHostFunction(aUndeffacts, 118, (int)(intptr_t)aUndeffactscomm, (int)(intptr_t)Deffacts_UndefCommand, (int)(intptr_t)a11w_10);
  Rules_RegisterHostFunction(aDeffactsModule, 119, (int)(intptr_t)aDeffactsmodule, (int)(intptr_t)Deffacts_ModuleFunction, (int)(intptr_t)a11w_10);
  Rules_RegisterHostFunction(aListDeffacts, 118, (int)(intptr_t)aListdeffactsco, (int)(intptr_t)Deffacts_ListCommand, (int)(intptr_t)a01w_6);
  Rules_RegisterHostFunction(aPpdeffacts, 118, (int)(intptr_t)aPpdeffactscomm, (int)(intptr_t)Deffacts_PPCommand, (int)(intptr_t)a11w_10);
  Deffacts_RegisterBinaryItem();
  return Deffacts_CompilerSetup();
}
// 4C7142: variable 'v0' is possibly undefined

//----- (004C71D0) --------------------------------------------------------
signed int Deffacts_Reset(void)
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))Deffacts_ResetAction, g_ClipsDeffactsModuleItemId, 0, 1);
}
// 54E698: using guessed type int dword_54E698;

//----- (004C71F0) --------------------------------------------------------
int  Deffacts_ResetAction(int result, intptr_t context)
{
  uintptr_t record; // ecx
  uintptr_t expression; // eax
  _DWORD parsed[6]; // [esp+0h] [ebp-18h] BYREF

  (void)context;
  record = (uintptr_t)(unsigned int)result;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(record + 20);
  if ( expression )
  {
    Lexer_ErrorRecover(0);
    return Parser_ParseForm((__int16 *)expression, parsed, (int)record, 0.0);
  }
  return (int)record;
}

//----- (004C7220) --------------------------------------------------------
int Deffacts_ClearAction(void)
{
  int **assert_symbol; // eax
  int assert_node; // ebx
  int initial_template; // eax
  int value_node; // eax
  int deffacts_record; // edx
  signed int *initial_name; // eax
  _DWORD *rhs_copy; // eax

  assert_symbol = Rules_MakeSymbol((_BYTE*)(aAssert_2));
  assert_node = AST_NewNode(10, (int)(intptr_t)assert_symbol);
  initial_template = Rules_FindDeftemplateByName((_BYTE*)(aInitialFact_1), assert_node);
  value_node = AST_NewNode(35, initial_template);
  *(_DWORD *)(uintptr_t)(assert_node + 6) = value_node;
  AST_InstallNodeChain((__int16 *)(uintptr_t)assert_node);
  deffacts_record = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
  if ( deffacts_record )
  {
    g_ClipsMemFreeListTemp = deffacts_record;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *(_DWORD *)(uintptr_t)deffacts_record;
    deffacts_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    deffacts_record = Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  *(_DWORD *)(uintptr_t)(deffacts_record + 8) = Rules_GetDeffactsModuleItem(0);
  initial_name = Str_Intern(aInitialFact_1, (int)(intptr_t)aInitialFact_1);
  *(_DWORD *)(uintptr_t)deffacts_record = (_DWORD)(uintptr_t)(initial_name);
  ++initial_name[1];
  rhs_copy = AST_PackNodeChain((_DWORD *)(uintptr_t)assert_node);
  *(_DWORD *)(uintptr_t)(deffacts_record + 16) = 0;
  *(_DWORD *)(uintptr_t)(deffacts_record + 20) = (_DWORD)(uintptr_t)(rhs_copy);
  *(_DWORD *)(uintptr_t)(deffacts_record + 4) = 0;
  AST_Free(assert_node);
  return Rules_AppendConstructToModuleList(deffacts_record);
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C72D0) --------------------------------------------------------
int  Deffacts_Save(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C72E0) --------------------------------------------------------
int __thiscall Deffacts_UndefCommand(void *this_)
{
  return Rules_UndefconstructCommand((int)(intptr_t)this_, g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7300) --------------------------------------------------------
int  Deffacts_DeleteConstruct(int theConstruct, int a2)
{
  return Rules_DeleteConstructOrAll(theConstruct, g_ClipsDeffactsConstructType, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7310) --------------------------------------------------------
_DWORD * Deffacts_GetListFunction(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDeffactsConstructType, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7350) --------------------------------------------------------
int __thiscall Deffacts_ModuleFunction(void *this_)
{
  return Rules_GetConstructModuleCommand((int)(intptr_t)this_, (const char **)(uintptr_t)g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7370) --------------------------------------------------------
int __thiscall Deffacts_PPCommand(void *this_)
{
  return Rules_PPConstructCommand((int)(intptr_t)this_, (const char **)(uintptr_t)g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C73A0) --------------------------------------------------------
int  Deffacts_ListCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDeffactsConstructType, a1, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C73E0) --------------------------------------------------------
signed int  Deffacts_ParseAndInstall(int readSource)
{
  int deffactsName; // edi
  int v4; // eax
  _DWORD *temp; // esi
  __int16 *v6; // ecx
  _DWORD *freeNode; // ebp
  int *newDeffacts; // ecx
  _DWORD *assertList; // eax
  int v10; // ecx
  int theItem; // eax
  int v12; // ecx
  int v13; // ebx
  int theModuleItem; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  char *ppForm; // eax
  int v19; // ecx
  _DWORD inputToken[3]; // [esp+0h] [ebp-28h] BYREF
  int error[7]; // [esp+Ch] [ebp-1Ch] BYREF

  error[0] = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDeffacts_3);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  deffactsName = Rules_GetConstructNameAndComment(readSource, (int)(intptr_t)inputToken, (int (*)(void))Rules_ParseDeffactsConstruct, aDeffacts_4, (int (*)(void))Deffacts_DeleteConstruct, asc_50AFAC, 1, 1, 1);
  if ( !deffactsName )
    return 1;
  v4 = Rules_ParseAssertCommand(readSource, inputToken, 0, error, 0, (int)(intptr_t)aDeffacts_4);
  temp = (_DWORD *)(uintptr_t)v4;
  if ( error[0] == 1 )
    return 1;
  if ( AST_TreeContainsSpecialTag(v4, 0) )
  {
    Rules_ReportLocalVariableError();
    AST_Free(v17);
    return 1;
  }
  else
  {
    IO_OutWriteToken(asc_50AFC8);
    AST_InstallNodeChain(v6);
    freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *freeNode;
      newDeffacts = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDeffacts = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    *newDeffacts = deffactsName;
    ++*(_DWORD *)(uintptr_t)(deffactsName + 4);
    assertList = AST_PackNodeChain(temp);
    *(_DWORD *)(uintptr_t)(v10 + 20) = (_DWORD)(uintptr_t)(assertList);
    theItem = Module_FindItemByName((int)(intptr_t)aDeffacts_4);
    v13 = v12;
    theModuleItem = Module_GetItem(0, *(_DWORD *)(uintptr_t)(theItem + 4));
    *(_DWORD *)(uintptr_t)(v15 + 8) = theModuleItem;
    *(_DWORD *)(uintptr_t)(v15 + 16) = 0;
    AST_Free((int)(intptr_t)temp);
    if ( Mem_GetAllocFlag() == 1 )
    {
      *(_DWORD *)(uintptr_t)(v16 + 4) = 0;
    }
    else
    {
      ppForm = Rules_CopyPPBuffer();
      *(_DWORD *)(uintptr_t)(v19 + 4) = (_DWORD)(uintptr_t)(ppForm);
    }
    Rules_AppendConstructToModuleList(v13);
    return 0;
  }
}
// 4C74B0: variable 'v6' is possibly undefined
// 4C74DD: variable 'v10' is possibly undefined
// 4C74EF: variable 'v12' is possibly undefined
// 4C74F6: variable 'v15' is possibly undefined
// 4C7511: variable 'v16' is possibly undefined
// 4C7537: variable 'v17' is possibly undefined
// 4C7567: variable 'v19' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C7580) --------------------------------------------------------
signed int Deffacts_RegisterBinaryItem(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDeffacts_1,
           0,
           (int)(intptr_t)Deffacts_BsaveExpressions,
           (int)(intptr_t)Deffacts_BsaveFind,
           (int)(intptr_t)Deffacts_BsaveWriteHeader,
           (int)(intptr_t)Deffacts_BsaveWriteData,
           (int)(intptr_t)Deffacts_BloadStorage,
           (int)(intptr_t)Deffacts_BloadBinaryItem,
           (int)(intptr_t)Deffacts_ClearBload);
}

//----- (004C75C0) --------------------------------------------------------
int Deffacts_BsaveFind(void)
{
  int result; // eax
  int i; // ebx
  _DWORD *j; // ecx
  int bsaveId; // edx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DeffactsModuleItemCount);
    Rules_ConstructQueuePush(g_DeffactsBsaveCount);
  }
  g_DeffactsBsaveCount = 0;
  g_DeffactsModuleItemCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    ++g_DeffactsModuleItemCount;
    for ( j = (_DWORD *)(uintptr_t)Rules_DeffactsGetNextItem(0); j; j = (_DWORD *)(uintptr_t)Rules_DeffactsGetNextItem(v6) )
    {
      bsaveId = g_DeffactsBsaveCount++;
      AST_MarkNodeFieldBound(j, bsaveId);
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v4 + 20));
      Rules_MarkReferencedFunctions((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 20));
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4C7632: variable 'v4' is possibly undefined
// 4C7640: variable 'v5' is possibly undefined
// 4C764A: variable 'v6' is possibly undefined
// 51B3D0: using guessed type int dword_51B3D0;
// 54E680: using guessed type int dword_54E680;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7670) --------------------------------------------------------
int  Deffacts_BsaveExpressions(int fp)
{
  int result; // eax
  int i; // esi
  int j; // ecx
  int v5; // ecx

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_DeffactsGetNextItem(0); j; j = Rules_DeffactsGetNextItem(v5) )
      Rules_BsaveWriteExpression((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 20), fp);
    result = Module_NextEnum(i);
  }
  return result;
}
// 4C76A3: variable 'v5' is possibly undefined

//----- (004C76C0) --------------------------------------------------------
const void * Deffacts_BsaveWriteHeader(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 8;
  Rules_BsaveWriteBlock(4, fp, space);
  Rules_BsaveWriteBlock(4, v2, &g_DeffactsBsaveCount);
  return Rules_BsaveWriteBlock(4, v3, &g_DeffactsModuleItemCount);
}
// 4C76EA: variable 'v2' is possibly undefined
// 4C76FB: variable 'v3' is possibly undefined
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7710) --------------------------------------------------------
int  Deffacts_BsaveWriteData(int fp)
{
  int i; // ecx
  _DWORD *theModuleItem; // eax
  int v4; // ecx
  int j; // edi
  int k; // ecx
  int v7; // ecx
  int v8; // ecx
  int result; // eax
  _DWORD dummyDeffacts[3]; // [esp+0h] [ebp-38h] BYREF
  int assertListIndex CLASH95_UNUSED; // [esp+Ch] [ebp-2Ch]
  _DWORD dummyModule[3]; // [esp+10h] [ebp-28h] BYREF
  int space[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  space[0] = 12 * g_DeffactsModuleItemCount + 16 * g_DeffactsBsaveCount;
  Rules_BsaveWriteBlock(4, fp, space);
  g_DeffactsBsaveCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v4) )
  {
    Module_SetCurrent(i);
    theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(0, g_ClipsDeffactsModuleItemId);
    Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
    Rules_BsaveWriteBlock(12, fp, dummyModule);
  }
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Rules_DeffactsGetNextItem(0); k; k = Rules_DeffactsGetNextItem(v8) )
    {
      AST_ExtractPatternBindingInfo(dummyDeffacts, k);
      if ( *(_DWORD *)(uintptr_t)(v7 + 20) )
      {
        assertListIndex = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v7 + 20));
      }
      else
      {
        assertListIndex = -1;
      }
      Rules_BsaveWriteBlock(16, fp, dummyDeffacts);
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop((_DWORD*)(&g_DeffactsModuleItemCount));
    return Rules_ConstructQueuePop((_DWORD*)(&g_DeffactsBsaveCount));
  }
  return result;
}
// 4C779A: variable 'v4' is possibly undefined
// 4C77DC: variable 'v7' is possibly undefined
// 4C7808: variable 'v8' is possibly undefined
// 51B3D0: using guessed type int dword_51B3D0;
// 54E680: using guessed type int dword_54E680;
// 54E698: using guessed type int dword_54E698;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7860) --------------------------------------------------------
int __fastcall Deffacts_BloadStorage(int a1)
{
  int result; // eax
  _DWORD space[3]; // [esp+0h] [ebp-Ch] BYREF

  space[2] = a1;
  Rules_BloadReadBlock((uintptr_t)space, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DeffactsBsaveCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_DeffactsModuleItemCount, 4u);
  if ( g_DeffactsModuleItemCount )
  {
    space[0] = 12 * g_DeffactsModuleItemCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * g_DeffactsModuleItemCount));
    g_Deffacts_BloadModuleArray = result;
    if ( g_DeffactsBsaveCount )
    {
      space[0] = 24 * g_DeffactsBsaveCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(24 * g_DeffactsBsaveCount));
      g_ClipsDeffactsBloadArray = result;
    }
    else
    {
      g_ClipsDeffactsBloadArray = 0;
    }
  }
  else
  {
    g_ClipsDeffactsBloadArray = 0;
    g_Deffacts_BloadModuleArray = 0;
  }
  return result;
}
// 51B3CC: using guessed type int dword_51B3CC;
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7910) --------------------------------------------------------
signed int Deffacts_BloadBinaryItem(void)
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  Rules_BloadAndRefresh(g_DeffactsModuleItemCount, 12, (void (__fastcall *)(signed int, signed int))Deffacts_UpdateDeffactsModule);
  return Rules_BloadAndRefresh(g_DeffactsBsaveCount, 16, (void (__fastcall *)(signed int, signed int))Deffacts_UpdateDeffacts);
}
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7950) --------------------------------------------------------
_DWORD * Deffacts_UpdateDeffactsModule(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(uintptr_t)(12 * obji + g_Deffacts_BloadModuleArray), g_ClipsDeffactsBloadArray, 24);
}
// 51B3CC: using guessed type int dword_51B3CC;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7990) --------------------------------------------------------
int  Deffacts_UpdateDeffacts(int buf, int obji)
{
  int assertList; // esi
  int result; // eax

  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(uintptr_t)(24 * obji + g_ClipsDeffactsBloadArray), g_Deffacts_BloadModuleArray, 12, 24, g_ClipsDeffactsBloadArray);
  if ( *(_DWORD *)(uintptr_t)(buf + 12) == -1 )
    assertList = 0;
  else
    assertList = 14 * *(_DWORD *)(uintptr_t)(buf + 12) + g_ClipsPackedExpressionArray;
  result = 3 * obji;
  *(_DWORD *)(uintptr_t)(g_ClipsDeffactsBloadArray + 24 * obji + 20) = assertList;
  return result;
}
// 51B3CC: using guessed type int dword_51B3CC;
// 54E688: using guessed type int dword_54E688;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7A10) --------------------------------------------------------
signed int Deffacts_ClearBload(void)
{
  int recordOffset; // ecx
  int v1; // ecx
  int recordIndex; // edx
  signed int result; // eax

  if ( g_DeffactsBsaveCount > 0 )
  {
    recordOffset = 0;
    do
    {
      Rules_ReleaseSymbolReference((int *)(uintptr_t)(recordOffset + g_ClipsDeffactsBloadArray), recordOffset);
      recordOffset = v1 + 24;
    }
    while ( recordIndex < g_DeffactsBsaveCount );
  }
  if ( 24 * g_DeffactsBsaveCount )
    Mem_ReleasePoolBlock(g_ClipsDeffactsBloadArray, 24 * g_DeffactsBsaveCount);
  result = 12 * g_DeffactsModuleItemCount;
  if ( 12 * g_DeffactsModuleItemCount )
    return Mem_ReleasePoolBlock(g_Deffacts_BloadModuleArray, 12 * g_DeffactsModuleItemCount);
  return result;
}
// 4C7A34: variable 'v1' is possibly undefined
// 4C7A39: variable 'v2' is possibly undefined
// 51B3CC: using guessed type int dword_51B3CC;
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7AA0) --------------------------------------------------------
int  Deffacts_GetModuleItem(int theIndex)
{
  return 12 * theIndex + g_Deffacts_BloadModuleArray;
}
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7AC0) --------------------------------------------------------
int Deffacts_CompilerSetup(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aDeffacts_2, 0, 0, (int)(intptr_t)Deffacts_BeforeCode, (int)(intptr_t)Deffacts_ToCode, 2);
  g_Clips_DeffactsCodeGeneratorItem = result;
  return result;
}
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7AF0) --------------------------------------------------------
signed int Deffacts_BeforeCode(void)
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E698: using guessed type int dword_54E698;

//----- (004C7B00) --------------------------------------------------------
int  Deffacts_ToCode(const char *fileName, const char *pathName, int imageID, int headerFP, int maxIndices)
{
  int deffactsFile; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int moduleFP; // edi
  int theDeffacts; // edi
  int v11; // eax
  int v12; // ecx
  int deffactsFP; // esi
  int fileCount; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int deffactsArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int deffactsArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *savedFileName; // [esp+1Ch] [ebp-20h]
  const char *savedPathName; // [esp+20h] [ebp-1Ch]
  int savedHeaderFP; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int savedImageID; // [esp+2Ch] [ebp-10h]

  savedFileName = fileName;
  savedPathName = pathName;
  savedHeaderFP = headerFP;
  savedImageID = imageID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  deffactsArrayCount = 0;
  deffactsArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)(intptr_t)aIncludeDffctde, 1);
  deffactsFile = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v7 = Rules_ConstructCodeFileOpen(
             moduleFile,
             savedFileName,
             savedImageID,
             savedPathName,
             &fileCount,
             moduleArrayVersion,
             savedHeaderFP,
             (char)(intptr_t)aStructDeffacts,
             **(const char ***)(uintptr_t)(g_Clips_DeffactsCodeGeneratorItem + 20),
             0,
             0);
      moduleFP = v7;
      if ( !v7 )
      {
        Deffacts_CloseCodeFiles(0, deffactsFile, v8, maxIndices);
        return 0;
      }
      Deffacts_ModuleToCode(v7, Enum, maxIndices, moduleCount);
      moduleFile = Rules_ConstructCodeFileClose(moduleFP, &moduleArrayCount, maxIndices, (_DWORD*)(&moduleArrayVersion), 0, 0);
      theDeffacts = Rules_DeffactsGetNextItem(0);
      if ( theDeffacts )
        break;
LABEL_6:
      ++moduleCount;
      ++moduleArrayCount;
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v11 = Rules_ConstructCodeFileOpen(
              deffactsFile,
              savedFileName,
              savedImageID,
              savedPathName,
              &fileCount,
              deffactsArrayVersion,
              savedHeaderFP,
              (char)(intptr_t)aStructDeffac_0,
              (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeffactsCodeGeneratorItem + 20) + 4),
              0,
              0);
      deffactsFP = v11;
      if ( !v11 )
        break;
      Deffacts_SingleToCode(v11, theDeffacts, maxIndices, moduleCount);
      ++deffactsArrayCount;
      deffactsFile = Rules_ConstructCodeFileClose(deffactsFP, &deffactsArrayCount, maxIndices, (_DWORD*)(&deffactsArrayVersion), 0, 0);
      theDeffacts = Rules_DeffactsGetNextItem(theDeffacts);
      if ( !theDeffacts )
        goto LABEL_6;
    }
    Deffacts_CloseCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Deffacts_CloseCodeFiles(moduleFile, deffactsFile, v6, maxIndices);
    return 1;
  }
}
// 4C7CA0: variable 'v6' is possibly undefined
// 4C7CB7: variable 'v8' is possibly undefined
// 4C7CCF: variable 'v12' is possibly undefined
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7CE0) --------------------------------------------------------
int  Deffacts_CloseCodeFiles(int moduleFile, int deffactsFile, int a3, int maxIndices)
{
  int result; // eax
  int count; // [esp+0h] [ebp-14h] BYREF
  _DWORD arrayVersion[4]; // [esp+4h] [ebp-10h] BYREF

  arrayVersion[3] = a3;
  result = deffactsFile;
  count = maxIndices;
  arrayVersion[0] = 0;
  if ( deffactsFile )
  {
    result = Rules_ConstructCodeFileClose(deffactsFile, &count, maxIndices, arrayVersion, 0, 0);
    if ( !moduleFile )
      return result;
    goto LABEL_5;
  }
  if ( moduleFile )
  {
LABEL_5:
    count = maxIndices;
    return Rules_ConstructCodeFileClose(moduleFile, &count, maxIndices, arrayVersion, 0, 0);
  }
  return result;
}

//----- (004C7D40) --------------------------------------------------------
int  Deffacts_ModuleToCode(int theFile, int theModule, int maxIndices, int moduleCount CLASH95_UNUSED)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, theFile, (int)(intptr_t)asc_50B024, v10);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v5, v6, g_ClipsDeffactsModuleItemId, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Clips_DeffactsCodeGeneratorItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, theFile, (int)(intptr_t)asc_50B028, v11);
}
// 4C7D4B: variable 'v10' is possibly undefined
// 4C7D68: variable 'v5' is possibly undefined
// 4C7D68: variable 'v6' is possibly undefined
// 4C7D73: variable 'v8' is possibly undefined
// 4C7D73: variable 'v7' is possibly undefined
// 4C7D73: variable 'v11' is possibly undefined
// 54E698: using guessed type int dword_54E698;
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7D90) --------------------------------------------------------
int  Deffacts_SingleToCode(int theFile, int theDeffacts, int maxIndices, int moduleCount)
{
  int *prefixArray; // eax
  DWORD modulePrefix; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theDeffacts, theFile, (int)(intptr_t)asc_50B024, v15);
  prefixArray = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_Clips_DeffactsCodeGeneratorItem + 20);
  modulePrefix = *prefixArray;
  Rules_WriteConstructHeaderToCode(theFile, theDeffacts, v8, moduleCount, *prefixArray, prefixArray[1]);
  Output_WriteFormatted(v10, v9, theFile, (int)(intptr_t)asc_50B02C, v16);
  Rules_ExpressionToCode(theFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDeffacts + 20), v11, modulePrefix);
  return Output_WriteFormatted(v13, v12, theFile, (int)(intptr_t)asc_50B028, v17);
}
// 4C7D9D: variable 'v15' is possibly undefined
// 4C7DBD: variable 'v8' is possibly undefined
// 4C7DC8: variable 'v10' is possibly undefined
// 4C7DC8: variable 'v9' is possibly undefined
// 4C7DC8: variable 'v16' is possibly undefined
// 4C7DD5: variable 'v11' is possibly undefined
// 4C7DE0: variable 'v13' is possibly undefined
// 4C7DE0: variable 'v12' is possibly undefined
// 4C7DE0: variable 'v17' is possibly undefined
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7DF0) --------------------------------------------------------
int  Deffacts_PrintModuleReference(int theFile, int count)
{
  return Output_WriteFormatted(count, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_Clips_DeffactsCodeGeneratorItem + 20), theFile, (int)(intptr_t)aMihsSD_DD_5, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_Clips_DeffactsCodeGeneratorItem + 20));
}
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7E30) --------------------------------------------------------
BOOL Defgeneric_NoActiveCall(void)
{
  return g_ClipsCurrentGeneric == 0;
}
// 51B3D4: using guessed type int dword_51B3D4;

//----- (004C7E40) --------------------------------------------------------
signed int Defgeneric_AllocateModule(void)
{
  _DWORD *freeNode; // edx

  freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( !freeNode )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeNode;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C7E70) --------------------------------------------------------
int  Defgeneric_FreeModule(int theItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theItem, g_Clips_DefgenericConstructType, theItem);
  freed_node = (_DWORD *)(uintptr_t)theItem;
  g_ClipsMemFreeListTemp = theItem;
  *freed_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6A0: using guessed type int dword_54E6A0;

//----- (004C7EB0) --------------------------------------------------------
int Defgeneric_ClearDefgenericsReady(void)
{
  int v0; // eax
  int v1; // ecx
  int i; // edx
  int v4; // ecx
  int v5; // edx

  v0 = Rules_IsBloaded();
  if ( v0 == v1 )
    return v1 ^ v0;
  for ( i = Defgeneric_GetNextInModule(0); i; i = Defgeneric_GetNextInModule(v5) )
    Defgeneric_RemoveAllExplicitMethods(i);
  return v4;
}
// 4C7EBD: variable 'v1' is possibly undefined
// 4C7EE0: variable 'v5' is possibly undefined
// 4C7EEB: variable 'v4' is possibly undefined

//----- (004C7EF0) --------------------------------------------------------
signed int  Defgeneric_RemoveAllExplicitMethods(int theDefgeneric)
{
  signed int methodsExecuting; // eax
  int v3; // edx
  unsigned int methodIndex; // ebp
  int methodOffset; // esi
  int theMethod; // edx
  _DWORD *newMethods; // eax
  int destOffset; // edx
  int copyOffset; // ebp
  _BYTE *oldMethod; // esi
  _DWORD *destMethod; // edi
  int oldMethodCount; // eax
  _DWORD *narr; // [esp+0h] [ebp-18h]
  int systemMethodCount; // [esp+4h] [ebp-14h]
  unsigned int copyIndex; // [esp+8h] [ebp-10h]

  methodsExecuting = Defgeneric_MethodsExecuting(theDefgeneric);
  systemMethodCount = v3;
  if ( methodsExecuting )
    return v3;
  methodIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(theDefgeneric + 32) )
  {
    methodOffset = 0;
    do
    {
      theMethod = methodOffset + *(_DWORD *)(uintptr_t)(theDefgeneric + 28);
      if ( (*(_BYTE *)(uintptr_t)(theMethod + 24) & 1) != 0 )
        ++systemMethodCount;
      else
        Defgeneric_DeleteMethodInfo(theDefgeneric, theMethod);
      ++methodIndex;
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(uintptr_t)(theDefgeneric + 32) );
  }
  if ( systemMethodCount )
  {
    newMethods = Mem_SmallBlockAlloc(40 * systemMethodCount);
    destOffset = 0;
    narr = newMethods;
    copyIndex = 0;
    if ( *(_DWORD *)(uintptr_t)(theDefgeneric + 32) )
    {
      copyOffset = 0;
      do
      {
        oldMethod = (_BYTE *)(uintptr_t)(copyOffset + *(_DWORD *)(uintptr_t)(theDefgeneric + 28));
        if ( (oldMethod[24] & 1) != 0 )
        {
          destMethod = &newMethods[destOffset];
          destOffset += 10;
          qmemcpy(destMethod, oldMethod, 0x28u);
        }
        copyOffset += 40;
        ++copyIndex;
      }
      while ( copyIndex < *(_DWORD *)(uintptr_t)(theDefgeneric + 32) );
    }
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDefgeneric + 28), 40 * *(_DWORD *)(uintptr_t)(theDefgeneric + 32));
    *(_DWORD *)(uintptr_t)(theDefgeneric + 32) = systemMethodCount;
    *(_DWORD *)(uintptr_t)(theDefgeneric + 28) = (_DWORD)(uintptr_t)(narr);
    return 1;
  }
  oldMethodCount = *(_DWORD *)(uintptr_t)(theDefgeneric + 32);
  if ( oldMethodCount )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDefgeneric + 28), 40 * oldMethodCount);
  *(_DWORD *)(uintptr_t)(theDefgeneric + 32) = 0;
  *(_DWORD *)(uintptr_t)(theDefgeneric + 28) = 0;
  return 1;
}
// 4C7EFF: variable 'v3' is possibly undefined

//----- (004C8030) --------------------------------------------------------
int  Defgeneric_RemoveDefgeneric(int theDefgeneric)
{
  int genericPtr; // ecx
  unsigned int methodIndex; // ebx
  int methodOffset; // esi
  int methodCount; // ebp
  int nameSymbol; // eax
  int v6; // ecx
  signed int v7; // ecx
  _DWORD *v8; // ecx
  int result; // eax

  genericPtr = theDefgeneric;
  methodIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(theDefgeneric + 32) )
  {
    methodOffset = 0;
    do
    {
      ++methodIndex;
      Defgeneric_DeleteMethodInfo(genericPtr, methodOffset + *(_DWORD *)(uintptr_t)(genericPtr + 28));
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(uintptr_t)(genericPtr + 32) );
  }
  methodCount = *(_DWORD *)(uintptr_t)(genericPtr + 32);
  if ( methodCount )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(genericPtr + 28), 40 * methodCount);
  nameSymbol = Rules_GetConstructNameSymbol(genericPtr);
  Rules_DecrementSymbolCount(nameSymbol, v6);
  Rules_ReplaceConstructPPForm(v7, 0);
  g_ClipsMemFreeListTemp = (int)(intptr_t)v8;
  *v8 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
  return result;
}
// 4C804B: variable 'v1' is possibly undefined
// 4C806E: variable 'v6' is possibly undefined
// 4C8077: variable 'v7' is possibly undefined
// 4C8081: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C80D0) --------------------------------------------------------
signed int Defgeneric_ClearDefgenerics(void)
{
  int success; // ebx
  int theDefgeneric; // ecx
  int v3; // edx
  int currentGeneric; // edx
  int constructName; // eax
  int v6; // ecx

  success = 1;
  if ( Rules_IsBloaded() == 1 )
    return 0;
  theDefgeneric = Defgeneric_GetNextInModule(0);
  if ( !theDefgeneric )
    return success;
  do
  {
    while ( 1 )
    {
      Defgeneric_GetNextInModule(theDefgeneric);
      if ( Defgeneric_RemoveAllExplicitMethods(v3) )
        break;
      constructName = Rules_GetConstructNameString(currentGeneric);
      success = 0;
      Rules_ReportCantDeleteItem(v6, constructName);
      if ( !theDefgeneric )
        return success;
    }
    Rules_UnlinkListNode(currentGeneric);
    Defgeneric_RemoveDefgeneric(currentGeneric);
  }
  while ( theDefgeneric );
  return success;
}
// 4C80F6: variable 'v2' is possibly undefined
// 4C80FF: variable 'v3' is possibly undefined
// 4C810A: variable 'v4' is possibly undefined
// 4C8118: variable 'v6' is possibly undefined

//----- (004C8140) --------------------------------------------------------
signed int Defgeneric_PrintCannotModifyError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // eax
  int v3; // ecx

  Rules_PrintErrorID((int)(intptr_t)aGenrcfun, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDefgeneric_0, v0);
  v2 = Rules_GetConstructNameString(v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v2, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotBeModifi, v3);
}
// 4C8160: variable 'v0' is possibly undefined
// 4C8167: variable 'v1' is possibly undefined
// 4C8185: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C8190) --------------------------------------------------------
int  Defgeneric_DeleteMethodInfo(int gfunc, int meth)
{
  int v3; // edx
  int v4; // edx
  int restrictionIndex; // edi
  int restrictionOffset; // esi
  int theRestriction; // ebx
  int typeOffset; // ecx
  int v9; // ecx
  unsigned int typeIndex; // edx
  int result; // eax

  g_Defgeneric_SavedBusyCount = *(_DWORD *)(uintptr_t)(gfunc + 20);
  AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(meth + 32));
  AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(v3 + 32));
  if ( *(_DWORD *)(uintptr_t)(v4 + 36) )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(meth + 36), strlen((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(meth + 36)) + 1);
  restrictionIndex = 0;
  if ( *(int *)(uintptr_t)(meth + 8) > 0 )
  {
    restrictionOffset = 0;
    do
    {
      theRestriction = restrictionOffset + *(_DWORD *)(uintptr_t)(meth + 28);
      if ( *(_DWORD *)(uintptr_t)(theRestriction + 8) )
      {
        typeOffset = 0;
        do
        {
          Class_ReleaseBusyReference(*(_DWORD *)(uintptr_t)(typeOffset + *(_DWORD *)(uintptr_t)theRestriction));
          typeOffset = v9 + 4;
        }
        while ( typeIndex < *(_DWORD *)(uintptr_t)(theRestriction + 8) );
      }
      if ( *(_DWORD *)(uintptr_t)theRestriction )
        Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)theRestriction, 4 * *(_DWORD *)(uintptr_t)(theRestriction + 8));
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theRestriction + 4));
      ++restrictionIndex;
      AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(theRestriction + 4));
      restrictionOffset += 12;
    }
    while ( restrictionIndex < *(_DWORD *)(uintptr_t)(meth + 8) );
  }
  if ( *(_DWORD *)(uintptr_t)(meth + 28) )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(meth + 28), 12 * *(_DWORD *)(uintptr_t)(meth + 8));
  result = g_Defgeneric_SavedBusyCount;
  *(_DWORD *)(uintptr_t)(gfunc + 20) = g_Defgeneric_SavedBusyCount;
  return result;
}
// 4C81AD: variable 'v3' is possibly undefined
// 4C81B5: variable 'v4' is possibly undefined
// 4C81E8: variable 'v9' is possibly undefined
// 4C81ED: variable 'v10' is possibly undefined
// 54E8C8: using guessed type int dword_54E8C8;

//----- (004C8290) --------------------------------------------------------
signed int  Defgeneric_MethodsExecuting(int gfunc)
{
  int methodIndex; // edx
  int i; // eax

  methodIndex = 0;
  if ( !*(_DWORD *)(uintptr_t)(gfunc + 32) )
    return 0;
  for ( i = *(_DWORD *)(uintptr_t)(gfunc + 28); !*(_DWORD *)(uintptr_t)(i + 4); i += 40 )
  {
    if ( (unsigned int)++methodIndex >= *(_DWORD *)(uintptr_t)(gfunc + 32) )
      return 0;
  }
  return 1;
}
