/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004C4FB0) --------------------------------------------------------
signed int Deffunction_CountBsaveEntries(void)
{
  signed int result; // eax

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_Clips_DeffunctionCount);
    Rules_ConstructQueuePush(g_Deffunction_Count);
  }
  g_Deffunction_Count = 0;
  result = Rules_DoForAllConstructs((void (*)(void))Deffunction_CountAndMarkExpressions, 0);
  g_Clips_DeffunctionCount = result;
  return result;
}
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004C5000) --------------------------------------------------------
__int16  Deffunction_CountAndMarkExpressions(_DWORD *theDeffunction)
{
  int bsaveId; // edx
  int v2; // ecx
  int v3; // ecx

  bsaveId = g_Deffunction_Count++;
  AST_MarkNodeFieldBound(theDeffunction, bsaveId);
  g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v2 + 30));
  return Rules_MarkReferencedFunctions(*(__int16 **)(uintptr_t)(v3 + 30));
}
// 4C5018: variable 'v2' is possibly undefined
// 4C5026: variable 'v3' is possibly undefined
// 51B3A4: using guessed type int dword_51B3A4;
// 54E680: using guessed type int dword_54E680;

//----- (004C5030) --------------------------------------------------------
signed int Deffunction_BsaveWriteExpressions(void)
{
  return Rules_DoForAllConstructs((void (*)(void))Deffunction_BsaveWriteBodyExpression, 0);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004C5050) --------------------------------------------------------
__int16 * Deffunction_BsaveWriteBodyExpression(int theDeffunction, int fp)
{
  return Rules_BsaveWriteExpression(*(__int16 **)(uintptr_t)(theDeffunction + 30), fp);
}

//----- (004C5060) --------------------------------------------------------
const void * Deffunction_BsaveWriteBinaryHeader(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 8;
  Rules_BsaveWriteBlock(4, fp, space);
  Rules_BsaveWriteBlock(4, v2, &g_Clips_DeffunctionCount);
  return Rules_BsaveWriteBlock(4, v3, &g_Deffunction_Count);
}
// 4C508A: variable 'v2' is possibly undefined
// 4C509B: variable 'v3' is possibly undefined
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;

//----- (004C50B0) --------------------------------------------------------
int  Deffunction_BsaveWriteConstructs(int fp, int a2)
{
  int theItem; // eax
  int v4; // ecx
  _DWORD *theModuleItem; // eax
  int v6; // ecx
  int result; // eax
  _DWORD dummyModule[3]; // [esp-Ch] [ebp-20h] BYREF
  _DWORD space[5]; // [esp+0h] [ebp-14h] BYREF

  space[3] = a2;
  space[0] = 32 * g_Deffunction_Count + 12 * g_Clips_DeffunctionCount;
  Rules_BsaveWriteBlock(4, fp, space);
  g_Deffunction_Count = 0;
  if ( Module_NextEnum(0) )
  {
    do
    {
      theItem = Module_FindItemByName((int)(intptr_t)aDeffunction_2);
      theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(v4, *(_DWORD *)(uintptr_t)(theItem + 4));
      Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
      Rules_BsaveWriteBlock(12, fp, dummyModule);
    }
    while ( Module_NextEnum(v6) );
  }
  Rules_DoForAllConstructs((void (*)(void))Deffunction_BsaveWriteRecord, 0);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_Clips_DeffunctionCount);
    return Rules_ConstructQueuePop(&g_Deffunction_Count);
  }
  return result;
}
// 4C5112: variable 'v4' is possibly undefined
// 4C5130: variable 'v6' is possibly undefined
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004C5190) --------------------------------------------------------
const void * Deffunction_BsaveWriteRecord(int theDeffunction, int fp, int a3)
{
  int v4; // ecx
  _DWORD dummyDeffunction[7]; // [esp-Ch] [ebp-28h] BYREF
  int codeIndex CLASH95_UNUSED; // [esp+10h] [ebp-Ch]
  int v8 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v8 = a3;
  AST_ExtractPatternBindingInfo(dummyDeffunction, theDeffunction);
  dummyDeffunction[3] = *(_DWORD *)(uintptr_t)(v4 + 34);
  dummyDeffunction[4] = *(_DWORD *)(uintptr_t)(v4 + 38);
  dummyDeffunction[5] = *(_DWORD *)(uintptr_t)(v4 + 42);
  if ( *(_DWORD *)(uintptr_t)(v4 + 30) )
  {
    codeIndex = g_ClipsExpressionNodeIndex;
    g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(v4 + 30));
  }
  else
  {
    codeIndex = -1;
  }
  return Rules_BsaveWriteBlock(32, fp, dummyDeffunction);
}
// 4C51A2: variable 'v4' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004C5200) --------------------------------------------------------
int __thiscall Deffunction_BloadAllocateBinaryStorage(void *this)
{
  int result; // eax
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = this;
  result = Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    Rules_BloadReadBlock((uintptr_t)&g_Clips_DeffunctionCount, 4u);
    result = Rules_BloadReadBlock((uintptr_t)&g_Deffunction_Count, 4u);
    if ( g_Clips_DeffunctionCount )
    {
      space[0] = 12 * g_Clips_DeffunctionCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * g_Clips_DeffunctionCount));
      g_Clips_DeffunctionRecordArray = result;
      if ( g_Deffunction_Count )
      {
        space[0] = 46 * g_Deffunction_Count;
        result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(46 * g_Deffunction_Count));
        g_DeffunctionBloadRecordArray = result;
      }
      else
      {
        g_DeffunctionBloadRecordArray = 0;
      }
    }
    else
    {
      g_Clips_DeffunctionRecordArray = 0;
      g_DeffunctionBloadRecordArray = 0;
    }
  }
  return result;
}
// 51B3A0: using guessed type int dword_51B3A0;
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E894: using guessed type int dword_54E894;

//----- (004C52B0) --------------------------------------------------------
signed int Deffunction_BloadRefreshConstructs(void)
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  Rules_BloadAndRefresh(g_Clips_DeffunctionCount, 12, (void (__fastcall *)(signed int, signed int))Deffunction_BloadRefreshRecord);
  return Rules_BloadAndRefresh(g_Deffunction_Count, 32, (void (__fastcall *)(signed int, signed int))Deffunction_BloadRefreshBodyRecord);
}
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;

//----- (004C52F0) --------------------------------------------------------
_DWORD * Deffunction_BloadRefreshRecord(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(uintptr_t)(12 * obji + g_Clips_DeffunctionRecordArray), g_DeffunctionBloadRecordArray, 46);
}
// 51B3A0: using guessed type int dword_51B3A0;
// 54E894: using guessed type int dword_54E894;

//----- (004C5330) --------------------------------------------------------
int  Deffunction_BloadRefreshBodyRecord(_DWORD *buf, int obji)
{
  int theDeffunction; // esi
  int codeIndex; // edx
  int codeExpr; // eax
  int result; // eax

  theDeffunction = g_DeffunctionBloadRecordArray + 46 * obji;
  Rules_BuildIndexedSlotDescriptor((int)(intptr_t)buf, (_DWORD *)(uintptr_t)theDeffunction, g_Clips_DeffunctionRecordArray, 12, 46, g_DeffunctionBloadRecordArray);
  codeIndex = buf[7];
  if ( codeIndex == -1 )
    codeExpr = 0;
  else
    codeExpr = g_ClipsPackedExpressionArray + 14 * codeIndex;
  *(_DWORD *)(uintptr_t)(theDeffunction + 20) = 0;
  *(_DWORD *)(uintptr_t)(theDeffunction + 24) = 0;
  *(_DWORD *)(uintptr_t)(theDeffunction + 30) = codeExpr;
  *(_WORD *)(uintptr_t)(theDeffunction + 28) = g_Rules_WatchDeffunctions;
  *(_DWORD *)(uintptr_t)(theDeffunction + 34) = buf[3];
  *(_DWORD *)(uintptr_t)(theDeffunction + 38) = buf[4];
  result = buf[5];
  *(_DWORD *)(uintptr_t)(theDeffunction + 42) = result;
  return result;
}
// 51AAE8: using guessed type int dword_51AAE8;
// 51B3A0: using guessed type int dword_51B3A0;
// 54E688: using guessed type int dword_54E688;
// 54E894: using guessed type int dword_54E894;

//----- (004C53B0) --------------------------------------------------------
signed int Deffunction_ClearBinaryData(void)
{
  signed int result; // eax
  int recordOffset; // ecx
  int v2; // ecx
  int v3; // edx

  result = 12 * g_Clips_DeffunctionCount;
  if ( 12 * g_Clips_DeffunctionCount )
  {
    result = Mem_ReleasePoolBlock(g_Clips_DeffunctionRecordArray, 12 * g_Clips_DeffunctionCount);
    g_Clips_DeffunctionRecordArray = 0;
    g_Clips_DeffunctionCount = 0;
    if ( g_Deffunction_Count > 0 )
    {
      recordOffset = 0;
      do
      {
        result = Rules_ReleaseSymbolReference((int *)(uintptr_t)(recordOffset + g_DeffunctionBloadRecordArray), recordOffset);
        recordOffset = v2 + 46;
      }
      while ( v3 < g_Deffunction_Count );
    }
    if ( 46 * g_Deffunction_Count )
    {
      result = Mem_ReleasePoolBlock(g_DeffunctionBloadRecordArray, 46 * g_Deffunction_Count);
      g_DeffunctionBloadRecordArray = 0;
      g_Deffunction_Count = 0;
    }
  }
  return result;
}
// 4C5411: variable 'v2' is possibly undefined
// 4C5416: variable 'v3' is possibly undefined
// 51B3A0: using guessed type int dword_51B3A0;
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E894: using guessed type int dword_54E894;

//----- (004C5450) --------------------------------------------------------
signed int Class_RegisterBinaryItem(void)
{
  Rules_AddAbortBloadFunction((int)(intptr_t)aDefclass_0, (int)(intptr_t)Class_CreateSystemClasses, 0);
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDefclass_0,
           0,
           (int)(intptr_t)Class_BsaveWriteExpressions,
           (int)(intptr_t)Class_CountBsaveEntries,
           (int)(intptr_t)Class_BsaveWriteHeader,
           (int)(intptr_t)Class_BsaveWriteData,
           (int)(intptr_t)Class_BloadStorage,
           (int)(intptr_t)Class_BloadBinaryItem,
           (int)(intptr_t)Class_ClearBloadedData);
}

//----- (004C54A0) --------------------------------------------------------
int  Class_RecordAtIndex(int theIndex)
{
  return 12 * theIndex + g_Class_BloadModuleArray;
}
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C54C0) --------------------------------------------------------
_DWORD *Class_CountBsaveEntries(void)
{
  int i; // ecx
  _DWORD *result; // eax
  int slotNameId; // edx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DefclassNameTableCount);
    Rules_ConstructQueuePush(g_ClipsBloadDefclassCount);
    Rules_ConstructQueuePush(g_ClipsBloadClassLinkCount);
    Rules_ConstructQueuePush(g_Defclass_SlotRecordCount);
    Rules_ConstructQueuePush(g_ClipsDefclassBsaveHandlerCount);
    Rules_ConstructQueuePush(g_Defclass_SlotNameLinkCount);
    Rules_ConstructQueuePush(g_ClipsDefclassBsaveIndexArrayCount);
    Rules_ConstructQueuePush(g_ClipsBloadSlotRecordCount);
  }
  g_DefclassNameTableCount = 0;
  g_ClipsBloadDefclassCount = 0;
  g_ClipsDefclassBsaveHandlerCount = 0;
  g_Defclass_SlotRecordCount = 0;
  g_ClipsBloadClassLinkCount = 0;
  g_Defclass_SlotNameLinkCount = 0;
  g_ClipsDefclassBsaveIndexArrayCount = 0;
  g_ClipsBloadSlotRecordCount = 0;
  g_DefclassNameTableCount = Rules_DoForAllConstructs((void (*)(void))Class_CountSlotsAndMarkExpressions, 0);
  for ( i = 0; i != 668; i += 4 )
  {
    for ( result = *(_DWORD **)(uintptr_t)(i + g_Defclass_SlotNameHashTablePtr); result; result = (_DWORD *)(uintptr_t)result[5] )
    {
      if ( result[2] >= 2u )
      {
        slotNameId = g_Defclass_SlotRecordCount++;
        result[6] = slotNameId;
        *(_DWORD *)(uintptr_t)(result[3] + 12) |= 2u;
        *(_DWORD *)(uintptr_t)(result[4] + 12) |= 2u;
      }
    }
  }
  return result;
}
// 4C5541: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 51AD70: using guessed type int dword_51AD70;
// 54E6BC: using guessed type int dword_54E6BC;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C55E0) --------------------------------------------------------
int  Class_CountSlotsAndMarkExpressions(int theDefclass)
{
  int bsaveId; // edx
  _DWORD *classPtr; // ecx
  unsigned int slotIndex; // esi
  int slotOffset; // ebx
  int slotBsaveId; // eax
  int slotNameSym; // eax
  int theSlot; // eax
  int v9; // ecx
  unsigned int handlerIndex; // ebx
  int handlerOffset; // edx
  int handlerNameSym; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // edx
  int result; // eax
  signed int defaultExpr; // eax
  __int16 *v18; // edx
  int v19; // edx

  bsaveId = g_ClipsBloadDefclassCount++;
  AST_MarkNodeFieldBound((_DWORD *)(uintptr_t)theDefclass, bsaveId);
  g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(uintptr_t)(theDefclass + 40) + *(unsigned __int16 *)(uintptr_t)(theDefclass + 34) + *(unsigned __int16 *)(uintptr_t)(theDefclass + 46);
  *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theDefclass + 104) + 12) |= 2u;
  slotIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(theDefclass + 64) )
  {
    slotOffset = 0;
    do
    {
      slotBsaveId = g_ClipsDefclassBsaveHandlerCount++;
      *(_DWORD *)(uintptr_t)(classPtr[13] + slotOffset + 28) = slotBsaveId;
      slotNameSym = *(_DWORD *)(uintptr_t)(slotOffset + classPtr[13] + 12);
      *(_BYTE *)(uintptr_t)(slotNameSym + 12) |= 2u;
      theSlot = slotOffset + classPtr[13];
      if ( *(_DWORD *)(uintptr_t)(theSlot + 16) )
      {
        if ( (*(_BYTE *)(uintptr_t)theSlot & 0x40) != 0 )
        {
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(theSlot + 16));
          Rules_MarkReferencedFunctions(*(__int16 **)(uintptr_t)(slotOffset + *(_DWORD *)(uintptr_t)(v9 + 52) + 16));
        }
        else
        {
          defaultExpr = AST_BuildExpressionFromValue(*(_DWORD **)(uintptr_t)(theSlot + 16));
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(defaultExpr);
          Rules_MarkReferencedFunctions(v18);
          AST_Free(v19);
        }
      }
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < classPtr[16] );
  }
  g_Defclass_SlotNameLinkCount += classPtr[18];
  if ( classPtr[18] )
    g_ClipsDefclassBsaveIndexArrayCount += classPtr[19] + 1;
  handlerIndex = 0;
  if ( classPtr[24] )
  {
    handlerOffset = 0;
    do
    {
      handlerNameSym = *(_DWORD *)(uintptr_t)(handlerOffset + classPtr[22] + 8);
      *(_BYTE *)(uintptr_t)(handlerNameSym + 12) |= 2u;
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(handlerOffset + classPtr[22] + 28));
      ++handlerIndex;
      Rules_MarkReferencedFunctions(*(__int16 **)(uintptr_t)(v14 + *(_DWORD *)(uintptr_t)(v13 + 88) + 28));
      handlerOffset = v15 + 36;
    }
    while ( handlerIndex < classPtr[24] );
  }
  result = classPtr[24];
  g_ClipsBloadSlotRecordCount += result;
  return result;
}
// 4C563A: variable 'v3' is possibly undefined
// 4C566E: variable 'v9' is possibly undefined
// 4C56D9: variable 'v14' is possibly undefined
// 4C56D6: variable 'v13' is possibly undefined
// 4C56E6: variable 'v15' is possibly undefined
// 4C5725: variable 'v18' is possibly undefined
// 4C572C: variable 'v19' is possibly undefined
// 54E680: using guessed type int dword_54E680;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5740) --------------------------------------------------------
void Class_BsaveWriteExpressions(void)
{
  if ( g_ClipsBloadDefclassCount || g_ClipsBloadSlotRecordCount )
  {
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveHandlerExpressions, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveSlotExpressions, 0);
  }
}
// 54E6BC: using guessed type int dword_54E6BC;
// 54E89C: using guessed type int dword_54E89C;
// 54E8B0: using guessed type int dword_54E8B0;

//----- (004C5790) --------------------------------------------------------
__int16 * Class_BsaveHandlerExpressions(__int16 *result, int fp)
{
  __int16 *theDefclass; // ebp
  unsigned int slotIndex; // edi
  int slotOffset; // esi
  __int16 *defaultExpr; // eax
  int v7; // ecx

  theDefclass = result;
  slotIndex = 0;
  if ( *((_DWORD *)result + 16) )
  {
    slotOffset = 0;
    do
    {
      result = (__int16 *)(uintptr_t)(slotOffset + *((_DWORD *)theDefclass + 13));
      if ( *((_DWORD *)result + 4) )
      {
        if ( (*(_BYTE *)result & 0x40) != 0 )
        {
          result = Rules_BsaveWriteExpression(*((__int16 **)result + 4), fp);
        }
        else
        {
          defaultExpr = (__int16 *)(uintptr_t)AST_BuildExpressionFromValue(*((_DWORD **)result + 4));
          Rules_BsaveWriteExpression(defaultExpr, fp);
          result = (__int16 *)(uintptr_t)AST_Free(v7);
        }
      }
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < *((_DWORD *)theDefclass + 16) );
  }
  return result;
}
// 4C57E2: variable 'v7' is possibly undefined

//----- (004C57F0) --------------------------------------------------------
__int16 * Class_BsaveSlotExpressions(__int16 *result, int fp)
{
  int theDefclass; // edi
  unsigned int handlerIndex; // ebx
  int handlerOffset; // ecx
  int v6; // ecx

  theDefclass = (int)(intptr_t)result;
  handlerIndex = 0;
  if ( *((_DWORD *)result + 24) )
  {
    handlerOffset = 0;
    do
    {
      ++handlerIndex;
      result = Rules_BsaveWriteExpression(*(__int16 **)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(theDefclass + 88) + 28), fp);
      handlerOffset = v6 + 36;
    }
    while ( handlerIndex < *(_DWORD *)(uintptr_t)(theDefclass + 96) );
  }
  return result;
}
// 4C5816: variable 'v6' is possibly undefined

//----- (004C5830) --------------------------------------------------------
const void * Class_BsaveWriteHeader(int fp, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  if ( g_ClipsBloadDefclassCount || g_ClipsBloadSlotRecordCount )
  {
    space[0] = 36;
    Rules_BsaveWriteBlock(4, fp, space);
    Rules_BsaveWriteBlock(4, v3, &g_DefclassNameTableCount);
    Rules_BsaveWriteBlock(4, v4, &g_ClipsBloadDefclassCount);
    Rules_BsaveWriteBlock(4, v5, &g_ClipsBloadClassLinkCount);
    Rules_BsaveWriteBlock(4, v6, &g_Defclass_SlotRecordCount);
    Rules_BsaveWriteBlock(4, v7, &g_ClipsDefclassBsaveHandlerCount);
    Rules_BsaveWriteBlock(4, v8, &g_Defclass_SlotNameLinkCount);
    Rules_BsaveWriteBlock(4, v9, &g_ClipsDefclassBsaveIndexArrayCount);
    Rules_BsaveWriteBlock(4, v10, &g_ClipsBloadSlotRecordCount);
    space[0] = (unsigned __int16)g_ClipsDefclassIdCount;
    return Rules_BsaveWriteBlock(4, v11, space);
  }
  else
  {
    space[0] = g_ClipsBloadDefclassCount;
    return Rules_BsaveWriteBlock(4, fp, space);
  }
}
// 4C5889: variable 'v3' is possibly undefined
// 4C589A: variable 'v4' is possibly undefined
// 4C58AB: variable 'v5' is possibly undefined
// 4C58BC: variable 'v6' is possibly undefined
// 4C58CD: variable 'v7' is possibly undefined
// 4C58DE: variable 'v8' is possibly undefined
// 4C58EF: variable 'v9' is possibly undefined
// 4C5900: variable 'v10' is possibly undefined
// 4C591C: variable 'v11' is possibly undefined
// 51AD6C: using guessed type __int16 word_51AD6C;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5930) --------------------------------------------------------
const void * Class_BsaveWriteData(int fp)
{
  int theItem; // eax
  int v3; // ecx
  _DWORD *theModuleItem; // eax
  int v5; // ecx
  int bucketOffset; // edi
  _DWORD *i; // ecx
  const void *result; // eax
  _DWORD dummySlotName[4]; // [esp+0h] [ebp-38h] BYREF
  _DWORD dummyModule[3]; // [esp+10h] [ebp-28h] BYREF
  _DWORD space[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  if ( g_ClipsBloadDefclassCount || g_ClipsBloadSlotRecordCount )
  {
    space[0] = 4 * g_ClipsBloadSlotRecordCount
           + 16 * g_Defclass_SlotRecordCount
           + 12 * g_DefclassNameTableCount
           + 76 * g_ClipsBloadDefclassCount
           + 4 * g_ClipsBloadClassLinkCount
           + 24 * g_ClipsDefclassBsaveHandlerCount
           + 4 * g_Defclass_SlotNameLinkCount
           + 4 * g_ClipsDefclassBsaveIndexArrayCount
           + 28 * g_ClipsBloadSlotRecordCount;
    Rules_BsaveWriteBlock(4, fp, space);
    g_ClipsBloadDefclassCount = 0;
    g_ClipsBloadClassLinkCount = 0;
    g_ClipsDefclassBsaveHandlerCount = 0;
    g_Defclass_SlotRecordCount = 0;
    g_Defclass_SlotNameLinkCount = 0;
    g_ClipsDefclassBsaveIndexArrayCount = 0;
    g_ClipsBloadSlotRecordCount = 0;
    if ( Module_NextEnum(0) )
    {
      do
      {
        theItem = Module_FindItemByName((int)(intptr_t)aDefclass_0);
        theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(v3, *(_DWORD *)(uintptr_t)(theItem + 4));
        Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
        Rules_BsaveWriteBlock(12, fp, dummyModule);
      }
      while ( Module_NextEnum(v5) );
    }
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteClassRecord, 0);
    g_ClipsBloadClassLinkCount = 0;
    bucketOffset = 0;
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteSuperclassLists, 0);
    do
    {
      for ( i = *(_DWORD **)(uintptr_t)(g_Defclass_SlotNameHashTablePtr + bucketOffset); i; i = (_DWORD *)(uintptr_t)i[5] )
      {
        if ( i[2] >= 2u )
        {
          dummySlotName[0] = i[2];
          dummySlotName[1] = *i;
          dummySlotName[2] = *(_DWORD *)(uintptr_t)(i[3] + 12) << 16 >> 18;
          dummySlotName[3] = *(_DWORD *)(uintptr_t)(i[4] + 12) << 16 >> 18;
          Rules_BsaveWriteBlock(16, fp, dummySlotName);
        }
      }
      bucketOffset += 4;
    }
    while ( bucketOffset != 668 );
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteHandlerRecords, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteSlotNameTable, 0);
    Rules_DoForAllConstructs((void (*)(void))&g_Class_BsaveWriteUnknownSectionFn, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteSlotRecords, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteHandlerDispatchTable, 0);
    result = (const void *)(uintptr_t)Rules_IsBloaded();
    if ( result )
    {
      Rules_ConstructQueuePop(&g_DefclassNameTableCount);
      Rules_ConstructQueuePop(&g_ClipsBloadDefclassCount);
      Rules_ConstructQueuePop(&g_ClipsBloadClassLinkCount);
      Rules_ConstructQueuePop(&g_ClipsDefclassBsaveHandlerCount);
      Rules_ConstructQueuePop(&g_Defclass_SlotRecordCount);
      Rules_ConstructQueuePop(&g_Defclass_SlotNameLinkCount);
      Rules_ConstructQueuePop(&g_ClipsDefclassBsaveIndexArrayCount);
      return (const void *)(uintptr_t)Rules_ConstructQueuePop(&g_ClipsBloadSlotRecordCount);
    }
  }
  else
  {
    space[0] = g_ClipsBloadDefclassCount;
    return Rules_BsaveWriteBlock(4, fp, space);
  }
  return result;
}
// 4C5AD2: simplified comparisons for 'edx.4': ==0 || ==1 became <2u
// 4C5A4D: variable 'v3' is possibly undefined
// 4C5A6C: variable 'v5' is possibly undefined
// 4C5B10: variable 'i' is possibly undefined
// 4C61F0: using guessed type void *off_4C61F0;
// 51AD70: using guessed type int dword_51AD70;
// 54E6BC: using guessed type int dword_54E6BC;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5C10) --------------------------------------------------------
const void * Class_BsaveWriteClassRecord(int theDefclass, int fp)
{
  int classPtr; // ecx
  unsigned int v5; // eax
  int v6; // eax
  int v7; // eax
  _DWORD dummyClass[3]; // [esp+0h] [ebp-60h] BYREF
  int flagsWord; // [esp+Ch] [ebp-54h]
  __int16 classId CLASH95_UNUSED; // [esp+10h] [ebp-50h]
  __int16 directSuperclassCount CLASH95_UNUSED; // [esp+12h] [ebp-4Eh]
  int superclassListIndex CLASH95_UNUSED; // [esp+14h] [ebp-4Ch]
  __int16 directSubclassCount CLASH95_UNUSED; // [esp+18h] [ebp-48h]
  int subclassListIndex CLASH95_UNUSED; // [esp+1Ah] [ebp-46h]
  __int16 allSuperclassCount CLASH95_UNUSED; // [esp+1Eh] [ebp-42h]
  int allSuperclassListIndex CLASH95_UNUSED; // [esp+20h] [ebp-40h]
  int slotCount CLASH95_UNUSED; // [esp+24h] [ebp-3Ch]
  int v19 CLASH95_UNUSED; // [esp+28h] [ebp-38h]
  int v20 CLASH95_UNUSED; // [esp+2Ch] [ebp-34h]
  int maxSlotNameID CLASH95_UNUSED; // [esp+30h] [ebp-30h]
  int handlerCount CLASH95_UNUSED; // [esp+34h] [ebp-2Ch]
  int slotsIndex CLASH95_UNUSED; // [esp+38h] [ebp-28h]
  int instanceTemplateIndex CLASH95_UNUSED; // [esp+3Ch] [ebp-24h]
  int slotNameMapIndex CLASH95_UNUSED; // [esp+40h] [ebp-20h]
  int handlersIndex CLASH95_UNUSED; // [esp+44h] [ebp-1Ch]
  int scopeMapIndex CLASH95_UNUSED; // [esp+48h] [ebp-18h]

  AST_ExtractPatternBindingInfo(dummyClass, theDefclass);
  v5 = *(_DWORD *)(uintptr_t)(classPtr + 20) << 29;
  LOBYTE(flagsWord) = flagsWord & 0xFE;
  flagsWord |= v5 >> 31;
  v6 = *(_DWORD *)(uintptr_t)(classPtr + 20) << 28 >> 31;
  LOBYTE(flagsWord) = flagsWord & 0xFD;
  flagsWord |= 2 * (v6 & 1);
  v7 = *(_DWORD *)(uintptr_t)(classPtr + 20) << 30 >> 31;
  LOBYTE(flagsWord) = flagsWord & 0xFB;
  flagsWord |= 4 * (v7 & 1);
  classId = *(_WORD *)(uintptr_t)(classPtr + 24);
  slotCount = *(_DWORD *)(uintptr_t)(classPtr + 64);
  v20 = *(_DWORD *)(uintptr_t)(classPtr + 72);
  v19 = *(_DWORD *)(uintptr_t)(classPtr + 68);
  maxSlotNameID = *(_DWORD *)(uintptr_t)(classPtr + 76);
  handlerCount = *(_DWORD *)(uintptr_t)(classPtr + 96);
  directSuperclassCount = *(_WORD *)(uintptr_t)(classPtr + 34);
  directSubclassCount = *(_WORD *)(uintptr_t)(classPtr + 40);
  allSuperclassCount = *(_WORD *)(uintptr_t)(classPtr + 46);
  if ( *(_WORD *)(uintptr_t)(classPtr + 34) )
  {
    superclassListIndex = g_ClipsBloadClassLinkCount;
    g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(uintptr_t)(classPtr + 34);
  }
  else
  {
    superclassListIndex = -1;
  }
  if ( *(_WORD *)(uintptr_t)(theDefclass + 40) )
  {
    subclassListIndex = g_ClipsBloadClassLinkCount;
    g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(uintptr_t)(theDefclass + 40);
  }
  else
  {
    subclassListIndex = -1;
  }
  if ( *(_WORD *)(uintptr_t)(theDefclass + 46) )
  {
    allSuperclassListIndex = g_ClipsBloadClassLinkCount;
    g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(uintptr_t)(theDefclass + 46);
  }
  else
  {
    allSuperclassListIndex = -1;
  }
  if ( *(_DWORD *)(uintptr_t)(theDefclass + 52) )
  {
    slotsIndex = g_ClipsDefclassBsaveHandlerCount;
    g_ClipsDefclassBsaveHandlerCount += *(_DWORD *)(uintptr_t)(theDefclass + 64);
  }
  else
  {
    slotsIndex = -1;
  }
  if ( *(_DWORD *)(uintptr_t)(theDefclass + 56) )
  {
    instanceTemplateIndex = g_Defclass_SlotNameLinkCount;
    g_Defclass_SlotNameLinkCount += *(_DWORD *)(uintptr_t)(theDefclass + 72);
    slotNameMapIndex = g_ClipsDefclassBsaveIndexArrayCount;
    g_ClipsDefclassBsaveIndexArrayCount += *(_DWORD *)(uintptr_t)(theDefclass + 76) + 1;
  }
  else
  {
    instanceTemplateIndex = -1;
    slotNameMapIndex = -1;
  }
  if ( *(_DWORD *)(uintptr_t)(theDefclass + 88) )
  {
    handlersIndex = g_ClipsBloadSlotRecordCount;
    g_ClipsBloadSlotRecordCount += *(_DWORD *)(uintptr_t)(theDefclass + 96);
  }
  else
  {
    handlersIndex = -1;
  }
  scopeMapIndex = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theDefclass + 104) + 12) << 16 >> 18;
  return Rules_BsaveWriteBlock(76, fp, dummyClass);
}
// 4C5C2B: variable 'v4' is possibly undefined
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5E50) --------------------------------------------------------
unsigned __int16  Class_BsaveWriteSuperclassLists(int theDefclass, int fp)
{
  int classPtr; // ecx
  unsigned int superclassIndex; // ebp
  int superclassOffset; // edi
  unsigned int subclassIndex; // edi
  int subclassOffset; // ebp
  unsigned int allSuperclassIndex; // ebp
  int allSuperclassOffset; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  unsigned __int16 result; // ax
  _DWORD dummyClassIndex[6]; // [esp+0h] [ebp-18h] BYREF

  classPtr = theDefclass;
  superclassIndex = 0;
  superclassOffset = 0;
  while ( superclassIndex < *(unsigned __int16 *)(uintptr_t)(classPtr + 34) )
  {
    v12 = superclassOffset + *(_DWORD *)(uintptr_t)(classPtr + 36);
    if ( *(_DWORD *)(uintptr_t)v12 )
      v13 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v12 + 12);
    else
      v13 = -1;
    dummyClassIndex[0] = v13;
    superclassOffset += 4;
    ++superclassIndex;
    Rules_BsaveWriteBlock(4, fp, dummyClassIndex);
  }
  subclassIndex = 0;
  subclassOffset = 0;
  g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(uintptr_t)(classPtr + 34);
  while ( subclassIndex < *(unsigned __int16 *)(uintptr_t)(classPtr + 40) )
  {
    v14 = subclassOffset + *(_DWORD *)(uintptr_t)(classPtr + 42);
    if ( *(_DWORD *)(uintptr_t)v14 )
      v15 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v14 + 12);
    else
      v15 = -1;
    dummyClassIndex[0] = v15;
    subclassOffset += 4;
    ++subclassIndex;
    Rules_BsaveWriteBlock(4, fp, dummyClassIndex);
  }
  allSuperclassIndex = 0;
  g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(uintptr_t)(classPtr + 40);
  allSuperclassOffset = 0;
  while ( allSuperclassIndex < *(unsigned __int16 *)(uintptr_t)(classPtr + 46) )
  {
    v10 = allSuperclassOffset + *(_DWORD *)(uintptr_t)(classPtr + 48);
    if ( *(_DWORD *)(uintptr_t)v10 )
      v11 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v10 + 12);
    else
      v11 = -1;
    dummyClassIndex[0] = v11;
    allSuperclassOffset += 4;
    ++allSuperclassIndex;
    Rules_BsaveWriteBlock(4, fp, dummyClassIndex);
  }
  result = *(_WORD *)(uintptr_t)(classPtr + 46);
  g_ClipsBloadClassLinkCount += result;
  return result;
}
// 4C5E62: variable 'v3' is possibly undefined
// 54E8A8: using guessed type int dword_54E8A8;

//----- (004C5F70) --------------------------------------------------------
int  Class_BsaveWriteHandlerRecords(int result, int fp)
{
  unsigned int slotIndex; // edi
  int slotOffset; // esi
  int *theSlot; // edx
  int slotFlags; // eax
  unsigned int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // eax
  unsigned int v16; // eax
  unsigned int v17; // eax
  int slotClass; // ebx
  int slotClassBsaveId; // eax
  int v20; // edx
  int constraintBsaveIndex; // eax
  signed int defaultExpr; // eax
  int v23; // ecx
  int theConstraint; // ebx
  _DWORD dummySlot[3]; // [esp+0h] [ebp-30h] BYREF
  int defaultValueIndex CLASH95_UNUSED; // [esp+Ch] [ebp-24h]
  int constraintIndex CLASH95_UNUSED; // [esp+10h] [ebp-20h]
  int slotNameIndex CLASH95_UNUSED; // [esp+14h] [ebp-1Ch]
  int theDefclass; // [esp+18h] [ebp-18h]

  theDefclass = result;
  slotIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(result + 64) )
  {
    slotOffset = 0;
    do
    {
      theSlot = (int *)(uintptr_t)(slotOffset + *(_DWORD *)(uintptr_t)(theDefclass + 52));
      slotFlags = *theSlot;
      LOBYTE(dummySlot[0]) &= ~0x40u;
      dummySlot[0] |= slotFlags & 0x40;
      v7 = (unsigned int)(*theSlot << 23) >> 31;
      LOBYTE(dummySlot[0]) &= ~0x80u;
      dummySlot[0] |= (v7 & 1) << 7;
      v8 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~1u;
      dummySlot[0] |= v8 & 1;
      v9 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~2u;
      dummySlot[0] |= v9 & 2;
      v10 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~4u;
      dummySlot[0] |= v10 & 4;
      v11 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~8u;
      dummySlot[0] |= v11 & 8;
      v12 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~0x10u;
      dummySlot[0] |= v12 & 0x10;
      v13 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~0x20u;
      dummySlot[0] |= v13 & 0x20;
      v14 = (unsigned int)(*theSlot << 22) >> 31;
      BYTE1(dummySlot[0]) &= ~1u;
      dummySlot[0] |= (v14 & 1) << 8;
      v15 = (unsigned int)(*theSlot << 21) >> 31;
      BYTE1(dummySlot[0]) &= ~2u;
      dummySlot[0] |= (v15 & 1) << 9;
      v16 = (unsigned int)(*theSlot << 20) >> 31;
      BYTE1(dummySlot[0]) &= ~4u;
      dummySlot[0] |= (v16 & 1) << 10;
      v17 = (unsigned int)(*theSlot << 19) >> 31;
      BYTE1(dummySlot[0]) &= ~8u;
      dummySlot[0] |= (v17 & 1) << 11;
      slotClass = theSlot[1];
      if ( slotClass )
        slotClassBsaveId = *(_DWORD *)(uintptr_t)(slotClass + 12);
      else
        slotClassBsaveId = -1;
      dummySlot[1] = slotClassBsaveId;
      dummySlot[2] = *(_DWORD *)(uintptr_t)(theSlot[2] + 24);
      slotNameIndex = *(_DWORD *)(uintptr_t)(theSlot[3] + 12) << 16 >> 18;
      if ( theSlot[4] )
      {
        defaultValueIndex = g_ClipsExpressionNodeIndex;
        if ( (*(_BYTE *)theSlot & 0x40) != 0 )
        {
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theSlot[4]);
        }
        else
        {
          defaultExpr = AST_BuildExpressionFromValue((_DWORD *)(uintptr_t)theSlot[4]);
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(defaultExpr);
          AST_Free(v23);
        }
      }
      else
      {
        defaultValueIndex = -1;
      }
      if ( Rules_DynamicConstraintCheckingEnabled() && (theConstraint = *(_DWORD *)(uintptr_t)(v20 + 20)) != 0 )
        constraintBsaveIndex = *(unsigned __int16 *)(uintptr_t)(theConstraint + 4);
      else
        constraintBsaveIndex = -1;
      constraintIndex = constraintBsaveIndex;
      Rules_BsaveWriteBlock(24, fp, dummySlot);
      result = theDefclass;
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < *(_DWORD *)(uintptr_t)(theDefclass + 64) );
  }
  return result;
}
// 4C6167: variable 'v23' is possibly undefined
// 4C6178: variable 'v20' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004C6190) --------------------------------------------------------
_DWORD * Class_BsaveWriteSlotNameTable(_DWORD *result, int fp)
{
  int theDefclass; // ebp
  unsigned int linkIndex; // esi
  int linkOffset; // ecx
  int v6; // eax
  int slotNameId; // eax
  int v8; // ecx
  int indexBuffer[6]; // [esp+0h] [ebp-18h] BYREF

  theDefclass = (int)(intptr_t)result;
  linkIndex = 0;
  if ( result[18] )
  {
    linkOffset = 0;
    do
    {
      v6 = linkOffset + *(_DWORD *)(uintptr_t)(theDefclass + 56);
      if ( *(_DWORD *)(uintptr_t)v6 )
        slotNameId = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v6 + 28);
      else
        slotNameId = -1;
      indexBuffer[0] = slotNameId;
      ++linkIndex;
      result = Rules_BsaveWriteBlock(4, fp, indexBuffer);
      linkOffset = v8 + 4;
    }
    while ( linkIndex < *(_DWORD *)(uintptr_t)(theDefclass + 72) );
  }
  return result;
}
// 4C61CA: variable 'v8' is possibly undefined

//----- (004C6220) --------------------------------------------------------
_DWORD * Class_BsaveWriteSlotRecords(_DWORD *result, int fp)
{
  int theDefclass; // ebp
  unsigned int handlerIndex; // esi
  int handlerOffset; // ecx
  int *theHandler; // edx
  int v7; // eax
  int v8; // eax
  int handlerClass; // eax
  int classIndex; // eax
  int v11; // ecx
  _DWORD dummyHandler[6]; // [esp+0h] [ebp-30h] BYREF
  int actionsIndex CLASH95_UNUSED; // [esp+18h] [ebp-18h]

  theDefclass = (int)(intptr_t)result;
  handlerIndex = 0;
  if ( result[24] )
  {
    handlerOffset = 0;
    do
    {
      theHandler = (int *)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(theDefclass + 88));
      v7 = *theHandler;
      LOBYTE(dummyHandler[0]) &= ~1u;
      dummyHandler[0] |= v7 & 1;
      v8 = *theHandler;
      LOBYTE(dummyHandler[0]) &= 0xF9u;
      dummyHandler[0] |= v8 & 6;
      dummyHandler[1] = theHandler[4];
      dummyHandler[2] = theHandler[5];
      dummyHandler[3] = theHandler[6];
      handlerClass = theHandler[3];
      if ( handlerClass )
        classIndex = *(_DWORD *)(uintptr_t)(handlerClass + 12);
      else
        classIndex = -1;
      dummyHandler[5] = classIndex;
      dummyHandler[4] = *(_DWORD *)(uintptr_t)(theHandler[2] + 12) << 16 >> 18;
      if ( theHandler[7] )
      {
        actionsIndex = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theHandler[7]);
      }
      else
      {
        actionsIndex = -1;
      }
      result = Rules_BsaveWriteBlock(28, fp, dummyHandler);
      ++handlerIndex;
      handlerOffset = v11 + 36;
    }
    while ( handlerIndex < *(_DWORD *)(uintptr_t)(theDefclass + 96) );
  }
  return result;
}
// 4C62C6: variable 'v11' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004C62F0) --------------------------------------------------------
const void * Class_BsaveWriteHandlerDispatchTable(int theDefclass, int fp)
{
  return Rules_BsaveWriteBlock(4 * *(_DWORD *)(uintptr_t)(theDefclass + 96), fp, *(const void **)(uintptr_t)(theDefclass + 92));
}

//----- (004C6310) --------------------------------------------------------
_DWORD *__thiscall Class_BloadStorage(void *this)
{
  _DWORD *result; // eax
  _DWORD counts[8]; // [esp+0h] [ebp-40h] BYREF
  _DWORD *maxClassId; // [esp+20h] [ebp-20h]
  unsigned int space[7]; // [esp+24h] [ebp-1Ch] BYREF

  if ( g_ClipsDefclassIdTable || g_ClipsDefclassIdCount )
  {
    Rules_ReportSystemError((int)(intptr_t)this, 1);
    IO_RunRouterExitCallbacks();
  }
  result = (_DWORD *)(uintptr_t)Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    Rules_BloadReadBlock((uintptr_t)counts, space[0]);
    g_DefclassNameTableCount = counts[0];
    g_ClipsBloadDefclassCount = counts[1];
    g_ClipsBloadClassLinkCount = counts[2];
    g_Defclass_SlotRecordCount = counts[3];
    g_ClipsDefclassBsaveHandlerCount = counts[4];
    g_Defclass_SlotNameLinkCount = counts[5];
    g_ClipsDefclassBsaveIndexArrayCount = counts[6];
    g_ClipsBloadSlotRecordCount = counts[7];
    result = maxClassId;
    g_ClipsDefclassIdCount = (__int16)(intptr_t)maxClassId;
    if ( counts[0] )
    {
      space[0] = 12 * counts[0];
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * counts[0]));
      g_Class_BloadModuleArray = (int)(intptr_t)result;
    }
    if ( g_ClipsBloadDefclassCount )
    {
      space[0] = 124 * g_ClipsBloadDefclassCount;
      g_Clips_DefclassArrayBase = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(124 * g_ClipsBloadDefclassCount));
      result = Mem_SmallBlockAlloc(4 * (unsigned __int16)g_ClipsDefclassIdCount);
      g_ClipsDefclassIdTable = (int)(intptr_t)result;
    }
    if ( g_ClipsBloadClassLinkCount )
    {
      space[0] = 4 * g_ClipsBloadClassLinkCount;
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * g_ClipsBloadClassLinkCount));
      g_DefclassLinkTable = (int)(intptr_t)result;
    }
    if ( g_ClipsDefclassBsaveHandlerCount )
    {
      space[0] = 44 * g_ClipsDefclassBsaveHandlerCount;
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(44 * g_ClipsDefclassBsaveHandlerCount));
      g_DefclassSlotDescriptorArrayPtr = (int)(intptr_t)result;
    }
    if ( g_Defclass_SlotRecordCount )
    {
      space[0] = 28 * g_Defclass_SlotRecordCount;
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(28 * g_Defclass_SlotRecordCount));
      g_DefclassSlotTable = (int)(intptr_t)result;
    }
    if ( g_Defclass_SlotNameLinkCount )
    {
      space[0] = 4 * g_Defclass_SlotNameLinkCount;
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * g_Defclass_SlotNameLinkCount));
      g_DefclassBloadSlotNameLinkArray = (int)(intptr_t)result;
    }
    if ( g_ClipsDefclassBsaveIndexArrayCount )
    {
      space[0] = 4 * g_ClipsDefclassBsaveIndexArrayCount;
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * g_ClipsDefclassBsaveIndexArrayCount));
      g_Class_BloadClassLinkArray = (int)(intptr_t)result;
    }
    if ( g_ClipsBloadSlotRecordCount )
    {
      space[0] = 36 * g_ClipsBloadSlotRecordCount;
      g_DefclassBloadTemplateSlotArray = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(36 * g_ClipsBloadSlotRecordCount));
      space[0] = 4 * g_ClipsBloadSlotRecordCount;
      result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * g_ClipsBloadSlotRecordCount));
      g_Class_BloadSlotNameMapArray = (int)(intptr_t)result;
    }
  }
  else
  {
    g_ClipsBloadSlotRecordCount = 0;
    g_ClipsBloadDefclassCount = 0;
  }
  return result;
}
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;
// 51B3BC: using guessed type int dword_51B3BC;
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C4: using guessed type int dword_51B3C4;
// 51B3C8: using guessed type int dword_51B3C8;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C6530) --------------------------------------------------------
int Class_BloadBinaryItem(void)
{
  int result; // eax
  int space[5]; // [esp+0h] [ebp-14h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    if ( g_DefclassNameTableCount )
      result = Rules_BloadAndRefresh(g_DefclassNameTableCount, 12, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshNameTable);
    if ( g_ClipsBloadDefclassCount )
    {
      Rules_BloadAndRefresh(g_ClipsBloadDefclassCount, 76, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshClassRecords);
      Rules_BloadAndRefresh(g_ClipsBloadClassLinkCount, 4, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshSuperclassLink);
      Rules_BloadAndRefresh(g_Defclass_SlotRecordCount, 16, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshSlotRecord);
      Rules_BloadAndRefresh(g_ClipsDefclassBsaveHandlerCount, 24, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshHandlerRecord);
      if ( g_Defclass_SlotNameLinkCount )
        Rules_BloadAndRefresh(g_Defclass_SlotNameLinkCount, 4, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshSlotNameLink);
      if ( g_ClipsDefclassBsaveIndexArrayCount )
      {
        space[0] = 4 * g_ClipsDefclassBsaveIndexArrayCount;
        Rules_BloadReadBlock(g_Class_BloadClassLinkArray, 4 * g_ClipsDefclassBsaveIndexArrayCount);
      }
      if ( g_ClipsBloadSlotRecordCount )
      {
        Rules_BloadAndRefresh(g_ClipsBloadSlotRecordCount, 28, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshTemplateSlotRecord);
        space[0] = 4 * g_ClipsBloadSlotRecordCount;
        Rules_BloadReadBlock(g_Class_BloadSlotNameMapArray, 4 * g_ClipsBloadSlotRecordCount);
      }
      return Class_BloadFixupNameTable();
    }
  }
  return result;
}
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C8: using guessed type int dword_51B3C8;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C6650) --------------------------------------------------------
int Class_BloadFixupNameTable(void)
{
  int result; // eax
  int classOffset; // edx
  int classPtr; // ecx

  result = 0;
  classOffset = 0;
  do
  {
    ++result;
    classPtr = classOffset + g_Clips_DefclassArrayBase;
    classOffset += 124;
    g_Class_WatchSlots[result] = classPtr;
  }
  while ( result != 9 );
  return result * 4;
}
// 51AD78: using guessed type int dword_51AD78[];
// 51B3AC: using guessed type int dword_51B3AC;

//----- (004C6680) --------------------------------------------------------
_DWORD * Class_BloadRefreshNameTable(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(uintptr_t)(12 * obji + g_Class_BloadModuleArray), g_Clips_DefclassArrayBase, 124);
}
// 51B3AC: using guessed type int dword_51B3AC;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C66C0) --------------------------------------------------------
int  Class_BloadRefreshClassRecords(int buf, int obji)
{
  int theDefclass; // esi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int watchInstances; // eax
  int watchSlots; // eax
  int superclassListIndex; // ebx
  int bufPtr; // edi
  int superclassListPtr; // eax
  int subclassListIndex; // ebp
  int subclassListPtr; // eax
  int allSuperclassListIndex; // eax
  int allSuperclassListPtr; // eax
  int slotsIndex; // edx
  int slotsPtr; // eax
  int instanceTemplateIndex; // ebx
  int instanceTemplatePtr; // eax
  int slotNameMapIndex; // ebp
  int slotNameMapPtr; // eax
  int handlersIndex; // eax
  int handlersPtr; // eax
  int handlerMapIndex; // edx
  int handlerMapPtr; // eax
  char flagsByte; // ch
  int scopeMap; // eax

  theDefclass = g_Clips_DefclassArrayBase + 124 * obji;
  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(uintptr_t)theDefclass, g_Class_BloadModuleArray, 12, 124, g_Clips_DefclassArrayBase);
  v4 = *(_DWORD *)(uintptr_t)(buf + 12) & 1;
  *(_BYTE *)(uintptr_t)(theDefclass + 20) &= ~4u;
  *(_DWORD *)(uintptr_t)(theDefclass + 20) |= 4 * v4;
  v5 = *(_DWORD *)(uintptr_t)(buf + 12) << 30 >> 31;
  *(_BYTE *)(uintptr_t)(theDefclass + 20) &= ~8u;
  *(_DWORD *)(uintptr_t)(theDefclass + 20) |= 8 * (v5 & 1);
  v6 = *(_DWORD *)(uintptr_t)(buf + 12) << 29 >> 31;
  *(_BYTE *)(uintptr_t)(theDefclass + 20) &= ~2u;
  *(_DWORD *)(uintptr_t)(theDefclass + 20) |= 2 * (v6 & 1);
  *(_WORD *)(uintptr_t)(theDefclass + 24) = *(_WORD *)(uintptr_t)(buf + 16);
  *(_DWORD *)(uintptr_t)(4 * *(unsigned __int16 *)(uintptr_t)(theDefclass + 24) + g_ClipsDefclassIdTable) = theDefclass;
  watchInstances = g_Rules_WatchInstances & 1;
  *(_BYTE *)(uintptr_t)(theDefclass + 20) &= ~0x10u;
  *(_DWORD *)(uintptr_t)(theDefclass + 20) |= 16 * watchInstances;
  watchSlots = g_Class_WatchSlots[0] & 1;
  *(_BYTE *)(uintptr_t)(theDefclass + 20) &= ~0x20u;
  *(_DWORD *)(uintptr_t)(theDefclass + 20) |= 32 * watchSlots;
  *(_DWORD *)(uintptr_t)(theDefclass + 64) = *(_DWORD *)(uintptr_t)(buf + 36);
  *(_DWORD *)(uintptr_t)(theDefclass + 72) = *(_DWORD *)(uintptr_t)(buf + 44);
  *(_DWORD *)(uintptr_t)(theDefclass + 68) = *(_DWORD *)(uintptr_t)(buf + 40);
  *(_DWORD *)(uintptr_t)(theDefclass + 76) = *(_DWORD *)(uintptr_t)(buf + 48);
  *(_DWORD *)(uintptr_t)(theDefclass + 96) = *(_DWORD *)(uintptr_t)(buf + 52);
  *(_WORD *)(uintptr_t)(theDefclass + 34) = *(_WORD *)(uintptr_t)(buf + 18);
  superclassListIndex = *(_DWORD *)(uintptr_t)(buf + 20);
  bufPtr = buf;
  if ( superclassListIndex == -1 )
    superclassListPtr = 0;
  else
    superclassListPtr = g_DefclassLinkTable + 4 * superclassListIndex;
  *(_DWORD *)(uintptr_t)(theDefclass + 36) = superclassListPtr;
  *(_WORD *)(uintptr_t)(theDefclass + 40) = *(_WORD *)(uintptr_t)(buf + 24);
  subclassListIndex = *(_DWORD *)(uintptr_t)(buf + 26);
  if ( subclassListIndex == -1 )
    subclassListPtr = 0;
  else
    subclassListPtr = g_DefclassLinkTable + 4 * subclassListIndex;
  *(_DWORD *)(uintptr_t)(theDefclass + 42) = subclassListPtr;
  *(_WORD *)(uintptr_t)(theDefclass + 46) = *(_WORD *)(uintptr_t)(bufPtr + 30);
  allSuperclassListIndex = *(_DWORD *)(uintptr_t)(bufPtr + 32);
  if ( allSuperclassListIndex == -1 )
    allSuperclassListPtr = 0;
  else
    allSuperclassListPtr = g_DefclassLinkTable + 4 * allSuperclassListIndex;
  *(_DWORD *)(uintptr_t)(theDefclass + 48) = allSuperclassListPtr;
  slotsIndex = *(_DWORD *)(uintptr_t)(bufPtr + 56);
  if ( slotsIndex == -1 )
    slotsPtr = 0;
  else
    slotsPtr = g_DefclassSlotDescriptorArrayPtr + 44 * slotsIndex;
  *(_DWORD *)(uintptr_t)(theDefclass + 52) = slotsPtr;
  instanceTemplateIndex = *(_DWORD *)(uintptr_t)(bufPtr + 60);
  if ( instanceTemplateIndex == -1 )
    instanceTemplatePtr = 0;
  else
    instanceTemplatePtr = g_DefclassBloadSlotNameLinkArray + 4 * instanceTemplateIndex;
  *(_DWORD *)(uintptr_t)(theDefclass + 56) = instanceTemplatePtr;
  slotNameMapIndex = *(_DWORD *)(uintptr_t)(bufPtr + 64);
  if ( slotNameMapIndex == -1 )
    slotNameMapPtr = 0;
  else
    slotNameMapPtr = g_Class_BloadClassLinkArray + 4 * slotNameMapIndex;
  *(_DWORD *)(uintptr_t)(theDefclass + 80) = 0;
  *(_DWORD *)(uintptr_t)(theDefclass + 60) = slotNameMapPtr;
  handlersIndex = *(_DWORD *)(uintptr_t)(bufPtr + 68);
  if ( handlersIndex == -1 )
    handlersPtr = 0;
  else
    handlersPtr = 36 * handlersIndex + g_DefclassBloadTemplateSlotArray;
  *(_DWORD *)(uintptr_t)(theDefclass + 88) = handlersPtr;
  handlerMapIndex = *(_DWORD *)(uintptr_t)(bufPtr + 68);
  if ( handlerMapIndex == -1 )
    handlerMapPtr = 0;
  else
    handlerMapPtr = 4 * handlerMapIndex + g_Class_BloadSlotNameMapArray;
  *(_DWORD *)(uintptr_t)(theDefclass + 26) = 0;
  *(_DWORD *)(uintptr_t)(theDefclass + 80) = 0;
  *(_DWORD *)(uintptr_t)(theDefclass + 84) = 0;
  flagsByte = *(_BYTE *)(uintptr_t)(theDefclass + 20);
  *(_DWORD *)(uintptr_t)(theDefclass + 92) = handlerMapPtr;
  *(_BYTE *)(uintptr_t)(theDefclass + 20) = flagsByte | 1;
  scopeMap = *(_DWORD *)(uintptr_t)(g_ClipsBloadBitmapPointerTable + 4 * *(_DWORD *)(uintptr_t)(bufPtr + 72));
  *(_DWORD *)(uintptr_t)(theDefclass + 104) = scopeMap;
  ++*(_DWORD *)(uintptr_t)(scopeMap + 4);
  return Class_AddToHashTable(theDefclass);
}
// 51AD64: using guessed type int dword_51AD64;
// 51AD74: using guessed type int dword_51AD74;
// 51AD78: using guessed type int dword_51AD78[];
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C4: using guessed type int dword_51B3C4;
// 51B3C8: using guessed type int dword_51B3C8;
// 54E67C: using guessed type int dword_54E67C;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C6950) --------------------------------------------------------
int  Class_BloadRefreshSuperclassLink(_DWORD *buf, int obji)
{
  int result; // eax

  if ( *buf == -1 )
  {
    result = 0;
    *(_DWORD *)(uintptr_t)(g_DefclassLinkTable + 4 * obji) = 0;
  }
  else
  {
    result = g_Clips_DefclassArrayBase + 124 * *buf;
    *(_DWORD *)(uintptr_t)(g_DefclassLinkTable + 4 * obji) = result;
  }
  return result;
}
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
