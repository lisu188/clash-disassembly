/* Generated from src/recovered/rules/clips/004C82D0_methods.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004CEC60) --------------------------------------------------------
int * InstanceQuery_FindAllInstances(_DWORD *returnValue, double a2)
{
  _DWORD *v3; // edx
  _DWORD *v4; // eax
  int v5; // ecx
  int instanceIndex; // ecx
  int fieldPos; // esi
  int v8; // ebx
  int v9; // edx
  signed int *instanceName; // eax
  int v11; // edx
  int v12; // ecx
  int *result; // eax
  int varCount; // [esp+0h] [ebp-18h] BYREF
  int *restrictionList; // [esp+4h] [ebp-14h]

  returnValue[1] = 4;
  returnValue[3] = 0;
  returnValue[4] = -1;
  restrictionList = InstanceQuery_ParseRestrictions(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10), (int)(intptr_t)aFindAllInstanc, &varCount, a2);
  if ( restrictionList )
  {
    InstanceQuery_PushQueryFrame();
    v3 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    if ( v3 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *v3;
      v4 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      v4 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)(intptr_t)v4;
    *v4 = Mem_SmallBlockAlloc(4 * varCount);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4) = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8) = 0;
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) = 0;
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 20) = varCount;
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 24) = 0;
    InstanceQuery_ForEachClassRestriction(restrictionList, 0, a2);
    g_InstanceQuery_AbortFlag = v5;
    returnValue[2] = Rules_CreateEphemeralMultifield(varCount * *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 24));
    while ( *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) )
    {
      instanceIndex = 0;
      fieldPos = returnValue[4] + 2;
      if ( varCount > 0 )
      {
        v8 = 0;
        v9 = 6 * fieldPos - 6;
        do
        {
          *(_WORD *)(uintptr_t)(v9 + returnValue[2] + 14) = 8;
          instanceName = Instance_GetQualifiedName(*(_DWORD *)(uintptr_t)(v8 + *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12)), instanceIndex);
          v8 += 4;
          instanceIndex = v12 + 1;
          ++fieldPos;
          *(_DWORD *)(uintptr_t)(v11 + returnValue[2] + 16) = instanceName;
          v9 = v11 + 6;
        }
        while ( instanceIndex < varCount );
      }
      returnValue[4] = fieldPos - 2;
      InstanceQuery_DequeueDelayedBinding();
    }
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsQueryCore, 4 * varCount);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)(uintptr_t)g_ClipsQueryCore = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  else
  {
    result = Rules_CreateEphemeralMultifield(0);
    returnValue[2] = result;
  }
  return result;
}
// 4CED36: variable 'v5' is possibly undefined
// 4CED99: variable 'v12' is possibly undefined
// 4CED97: variable 'v11' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CEE40) --------------------------------------------------------
int * InstanceQuery_DoForInstance(int returnValue, int a2, double a3)
{
  int *result; // eax
  int *restrictionList; // ebx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  _DWORD varCount[4]; // [esp+0h] [ebp-10h] BYREF

  varCount[2] = a2;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)(intptr_t)aDoForInstance, varCount, a3);
  restrictionList = result;
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v5 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *v5;
      v6 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)(intptr_t)v6;
    *v6 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4) = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
    if ( InstanceQuery_TestClassRestriction(restrictionList, 0, a3) == 1 )
      Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8), v7, (int)(intptr_t)v7, a3);
    g_InstanceQuery_AbortFlag = 0;
    HIDWORD(g_ClipsHaltExecutionFlag) = 0;
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)(uintptr_t)g_ClipsQueryCore = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  return result;
}
// 4CEEF9: variable 'v7' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CEF80) --------------------------------------------------------
int * InstanceQuery_DoForAllInstances(int returnValue, int a2, double a3)
{
  int *result; // eax
  int *restrictionList; // ebx
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  _DWORD varCount[4]; // [esp+0h] [ebp-10h] BYREF

  varCount[2] = a2;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)(intptr_t)aDoForAllInstan, varCount, a3);
  restrictionList = result;
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v5 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *v5;
      v6 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)(intptr_t)v6;
    *v6 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4) = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28) = v7;
    Rules_ValueInstall(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28), v7);
    InstanceQuery_ForEachClassRestriction(restrictionList, v8, a3);
    Rules_ValueDeinstall(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28), v9);
    Rules_PropagateReturnValueDepth(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28));
    g_InstanceQuery_AbortFlag = v10;
    HIDWORD(g_ClipsHaltExecutionFlag) = v10;
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)(uintptr_t)g_ClipsQueryCore = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  return result;
}
// 4CF026: variable 'v7' is possibly undefined
// 4CF03A: variable 'v8' is possibly undefined
// 4CF047: variable 'v9' is possibly undefined
// 4CF063: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CF0E0) --------------------------------------------------------
int * InstanceQuery_DelayedDoForAllInstances(_DWORD *returnValue, double a2)
{
  int *result; // eax
  int *restrictionList; // ebp
  _DWORD *v5; // edx
  _DWORD *v6; // eax
  int v7; // ecx
  int copyIndex; // edx
  int copyOffset; // eax
  int v10; // ecx
  int varCount[5]; // [esp+0h] [ebp-14h] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 10), (int)(intptr_t)aDelayedDoForAl, varCount, a2);
  restrictionList = result;
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v5 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *v5;
      v6 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      v6 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)(intptr_t)v6;
    *v6 = Mem_SmallBlockAlloc(4 * varCount[0]);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4) = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8) = 0;
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) = 0;
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 20) = varCount[0];
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 24) = 0;
    InstanceQuery_ForEachClassRestriction(restrictionList, 0, a2);
    g_InstanceQuery_AbortFlag = v7;
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
    while ( *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) )
    {
      copyIndex = 0;
      if ( varCount[0] > 0 )
      {
        copyOffset = 0;
        do
        {
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsQueryCore + copyOffset) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) + copyOffset);
          ++copyIndex;
          copyOffset += 4;
        }
        while ( copyIndex < varCount[0] );
      }
      InstanceQuery_DequeueDelayedBinding();
      ++g_ClipsCurrentEvaluationDepth;
      Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8), returnValue, v10, a2);
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      if ( g_ClipsHaltExecution || g_ClipsHaltExecutionFlag )
      {
        while ( *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) )
          InstanceQuery_DequeueDelayedBinding();
        break;
      }
    }
    HIDWORD(g_ClipsHaltExecutionFlag) = 0;
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)(uintptr_t)g_ClipsQueryCore = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  return result;
}
// 4CF1B3: variable 'v7' is possibly undefined
// 4CF222: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CF2F0) --------------------------------------------------------
_DWORD *InstanceQuery_PushQueryFrame(void)
{
  _DWORD *freeListNode; // edx
  _DWORD *result; // eax

  freeListNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeListNode;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *result = g_ClipsQueryCore;
  result[1] = g_ClipsInstanceQueryCoreStack;
  g_ClipsInstanceQueryCoreStack = (int)(intptr_t)result;
  return result;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF340) --------------------------------------------------------
int InstanceQuery_PopQueryFrame(void)
{
  _DWORD *topFrame; // eax
  int result; // eax

  topFrame = (_DWORD *)(uintptr_t)g_ClipsInstanceQueryCoreStack;
  g_ClipsQueryCore = *(_DWORD *)(uintptr_t)g_ClipsInstanceQueryCoreStack;
  g_ClipsInstanceQueryCoreStack = *(_DWORD *)(uintptr_t)(g_ClipsInstanceQueryCoreStack + 4);
  g_ClipsMemFreeListTemp = (int)(intptr_t)topFrame;
  *topFrame = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  return result;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF380) --------------------------------------------------------
int  InstanceQuery_GetQueryFrameAtDepth(signed int depth)
{
  _DWORD *i; // edx

  if ( !depth )
    return g_ClipsQueryCore;
  for ( i = (_DWORD *)(uintptr_t)g_ClipsInstanceQueryCoreStack; depth > 1; i = (_DWORD *)(uintptr_t)i[1] )
    --depth;
  return *i;
}
// 51B458: using guessed type int dword_51B458;
// 51B45C: using guessed type int dword_51B45C;

//----- (004CF3B0) --------------------------------------------------------
int * InstanceQuery_ParseRestrictions(int queryExpr, int functionName, _DWORD *varCountOut, double a4)
{
  int *classListHead; // ebp
  int *lastClass; // ebx
  int v8; // ecx
  int newGroup; // edi
  int *classNode; // eax
  _DWORD token[7]; // [esp+0h] [ebp-30h] BYREF
  _DWORD *varCountPtr; // [esp+1Ch] [ebp-14h]

  token[6] = functionName;
  varCountPtr = varCountOut;
  classListHead = 0;
  lastClass = 0;
  v8 = 0;
  newGroup = 0;
  *varCountOut = 0;
  if ( !queryExpr )
    return classListHead;
  while ( 1 )
  {
    if ( Parser_ParseForm((__int16 *)(uintptr_t)queryExpr, token, v8, a4) )
    {
      InstanceQuery_FreeRestrictionClassList(classListHead);
      return 0;
    }
    if ( token[1] != 2 || token[2] != g_InternedSym_Qds )
      break;
    newGroup = 1;
    ++*varCountPtr;
LABEL_6:
    queryExpr = *(_DWORD *)(uintptr_t)(queryExpr + 10);
    if ( !queryExpr )
      return classListHead;
  }
  classNode = InstanceQuery_ResolveClassRestriction(v8, token);
  if ( classNode )
  {
    if ( classListHead )
    {
      if ( newGroup == 1 )
      {
        v8 = (int)(intptr_t)classNode;
        newGroup = 0;
        lastClass[3] = (int)(intptr_t)classNode;
        lastClass = classNode;
      }
      else
      {
        *(_DWORD *)(uintptr_t)(v8 + 8) = classNode;
      }
    }
    else
    {
      v8 = (int)(intptr_t)classNode;
      lastClass = classNode;
      classListHead = classNode;
    }
    while ( *(_DWORD *)(uintptr_t)(v8 + 8) )
      v8 = *(_DWORD *)(uintptr_t)(v8 + 8);
    goto LABEL_6;
  }
  Parser_ReportSyntaxError();
  InstanceQuery_FreeRestrictionClassList(classListHead);
  Lexer_ErrorRecover(1);
  return 0;
}
// 4CF3D7: variable 'v8' is possibly undefined
// 51B454: using guessed type int dword_51B454;

//----- (004CF480) --------------------------------------------------------
int *__fastcall InstanceQuery_ResolveClassRestriction(int a1 CLASH95_UNUSED, _DWORD *classToken)
{
  int v2; // edx
  int currentModule; // edi
  int restrictionType; // ecx
  int *restrictionListHead; // ebp
  int firstField; // eax
  int lastField; // ecx
  int fieldOffset; // esi
  int fieldPtr; // eax
  _BYTE *className; // edx
  int *lookedUpClass; // eax
  int v12; // ecx
  _DWORD *arrayFreeNode; // ecx
  int *arrayNode; // ecx
  int *restrictionNode; // ebx
  _DWORD *v16; // ecx
  int *result; // eax
  _DWORD *singleFreeNode; // ecx
  int *singleNode; // ecx
  int singleNodeAddr; // ebx
  int resolvedClass; // eax
  _DWORD *v22; // ecx
  int *namedClass; // eax
  int v24; // ecx
  int lookupClass; // esi
  _DWORD *namedFreeNode; // edx
  int *namedNode; // ecx
  int namedNodeAddr; // ebx
  _DWORD *v29; // ecx
  int lastFieldOffset; // [esp+4h] [ebp-28h]
  int arrayClass; // [esp+Ch] [ebp-20h]
  int *lastNode; // [esp+10h] [ebp-1Ch]
  int fieldIndex; // [esp+14h] [ebp-18h]

  currentModule = Module_GetCurrent();
  if ( *(_DWORD *)(uintptr_t)(v2 + 4) == 57 )
  {
    Class_AddBusyReference(classToken[2]);
    singleFreeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    if ( singleFreeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *singleFreeNode;
      singleNode = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      singleNode = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    singleNodeAddr = (int)(intptr_t)singleNode;
    resolvedClass = classToken[2];
    *singleNode = resolvedClass;
    if ( Class_IsInScope(resolvedClass, currentModule) )
      v22[1] = currentModule;
    else
      v22[1] = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*v22 + 8);
    *(_DWORD *)(uintptr_t)(singleNodeAddr + 8) = 0;
    result = (int *)(uintptr_t)singleNodeAddr;
    *(_DWORD *)(uintptr_t)(singleNodeAddr + 12) = 0;
  }
  else
  {
    restrictionType = classToken[1];
    if ( restrictionType == 2 )
    {
      namedClass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(classToken[2] + 16));
      lookupClass = (int)(intptr_t)namedClass;
      if ( namedClass )
      {
        Class_AddBusyReference((int)(intptr_t)namedClass);
        namedFreeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
        if ( namedFreeNode )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *namedFreeNode;
          namedNode = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
        }
        else
        {
          namedNode = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
        }
        namedNodeAddr = (int)(intptr_t)namedNode;
        *namedNode = lookupClass;
        if ( Class_IsInScope(lookupClass, currentModule) )
          v29[1] = currentModule;
        else
          v29[1] = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*v29 + 8);
        *(_DWORD *)(uintptr_t)(namedNodeAddr + 8) = 0;
        result = (int *)(uintptr_t)namedNodeAddr;
        *(_DWORD *)(uintptr_t)(namedNodeAddr + 12) = 0;
      }
      else
      {
        Class_ReportLookupError(v24, *(_DWORD *)(uintptr_t)(classToken[2] + 16));
        return 0;
      }
    }
    else
    {
      if ( restrictionType == 4 )
      {
        restrictionListHead = 0;
        lastNode = 0;
        firstField = classToken[3] + 1;
        lastField = classToken[4] + 1;
        fieldIndex = firstField;
        if ( lastField < firstField )
          return restrictionListHead;
        fieldOffset = 6 * firstField - 6;
        lastFieldOffset = 6 * lastField - 6;
        while ( 1 )
        {
          fieldPtr = fieldOffset + classToken[2];
          if ( *(_WORD *)(uintptr_t)(fieldPtr + 14) != 2 )
            break;
          className = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(fieldPtr + 16) + 16);
          lookedUpClass = Class_LookupByQualifiedName(className);
          arrayClass = (int)(intptr_t)lookedUpClass;
          if ( !lookedUpClass )
          {
            Class_ReportLookupError(v12, (int)(intptr_t)className);
            break;
          }
          Class_AddBusyReference((int)(intptr_t)lookedUpClass);
          arrayFreeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
          if ( arrayFreeNode )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
            *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *arrayFreeNode;
            arrayNode = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
          }
          else
          {
            arrayNode = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
          }
          restrictionNode = arrayNode;
          *arrayNode = arrayClass;
          if ( Class_IsInScope(arrayClass, currentModule) )
            v16[1] = currentModule;
          else
            v16[1] = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*v16 + 8);
          restrictionNode[2] = 0;
          restrictionNode[3] = 0;
          if ( restrictionListHead )
            lastNode[2] = (int)(intptr_t)restrictionNode;
          else
            restrictionListHead = restrictionNode;
          lastNode = restrictionNode;
          fieldOffset += 6;
          ++fieldIndex;
          if ( fieldOffset > lastFieldOffset )
            return restrictionListHead;
        }
        InstanceQuery_FreeRestrictionClassList(restrictionListHead);
      }
      return 0;
    }
  }
  return result;
}
// 4CF494: variable 'v2' is possibly undefined
// 4CF560: variable 'v16' is possibly undefined
// 4CF5DC: variable 'v22' is possibly undefined
// 4CF656: variable 'v29' is possibly undefined
// 4CF67F: variable 'v24' is possibly undefined
// 4CF6B1: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF700) --------------------------------------------------------
int * InstanceQuery_FreeRestrictionClassList(int *result)
{
  int *i; // ecx
  int *subNode; // edx
  _DWORD *v3; // edx
  _DWORD *v4; // edx

  for ( i = result; i; *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp )
  {
    while ( 1 )
    {
      subNode = (int *)(uintptr_t)i[2];
      if ( !subNode )
        break;
      i[2] = subNode[2];
      Class_ReleaseBusyReference(*subNode);
      g_ClipsMemFreeListTemp = (int)(intptr_t)v3;
      *v3 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    Class_ReleaseBusyReference(*i);
    g_ClipsMemFreeListTemp = (int)(intptr_t)v4;
    *v4 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    result = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4CF708: variable 'i' is possibly undefined
// 4CF721: variable 'v3' is possibly undefined
// 4CF74D: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CF770) --------------------------------------------------------
signed int  InstanceQuery_TestClassRestriction(int *restrictionList, int queryIndex, double a3)
{
  int *currentRestriction; // esi
  signed int traversalID; // eax

  currentRestriction = restrictionList;
  g_InstanceQuery_AbortFlag = 1;
  if ( restrictionList )
  {
    while ( 1 )
    {
      g_InstanceQuery_AbortFlag = 0;
      traversalID = Class_NewTraversalID();
      if ( traversalID == -1 )
        break;
      if ( InstanceQuery_TestInstancesRecursive(currentRestriction[1], traversalID, (int)(intptr_t)restrictionList, *currentRestriction, a3, queryIndex) )
      {
        Class_ReleaseTraversalID();
        return 1;
      }
      Class_ReleaseTraversalID();
      if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
        return 0;
      currentRestriction = (int *)(uintptr_t)currentRestriction[2];
      if ( !currentRestriction )
        return 0;
    }
  }
  return 0;
}
// 51A968: using guessed type int dword_51A968;
// 51B460: using guessed type int dword_51B460;

//----- (004CF800) --------------------------------------------------------
BOOL  InstanceQuery_TestInstancesRecursive(
        int theModule,
        signed int traversalID,
        int restriction,
        int theClass,
        double a5,
        int queryIndex)
{
  int traversalByte; // ebx
  int traversalMask; // eax
  BOOL result; // eax
  int v10; // edx
  int i; // ecx
  unsigned int subclassIndex; // edi
  int subclassOffset; // ebp
  _DWORD v14[6]; // [esp+0h] [ebp-30h] BYREF
  int v15; // [esp+18h] [ebp-18h]
  signed int v16; // [esp+1Ch] [ebp-14h]
  int v17; // [esp+20h] [ebp-10h]

  v15 = theModule;
  v16 = traversalID;
  v17 = theClass;
  traversalByte = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  traversalMask = 1 << (traversalID % 8);
  if ( ((unsigned __int8)traversalMask & *(_BYTE *)(uintptr_t)(traversalByte + 108)) != 0 )
    return 0;
  v10 = v15;
  *(_BYTE *)(uintptr_t)(traversalByte + 108) |= traversalMask;
  result = Class_IsInScope(v17, v10);
  if ( !result )
    return result;
  i = *(_DWORD *)(uintptr_t)(v17 + 80);
  if ( !i )
    goto LABEL_9;
  while ( 1 )
  {
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsQueryCore + 4 * queryIndex) = i;
    if ( !*(_DWORD *)(uintptr_t)(restriction + 12) )
    {
      ++*(_DWORD *)(uintptr_t)(i + 40);
      ++g_ClipsCurrentEvaluationDepth;
      Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4), v14, i, a5);
      --g_ClipsCurrentEvaluationDepth;
      Rules_RunPeriodicCleanup(0, 1);
      --*(_DWORD *)(uintptr_t)(i + 40);
      if ( g_ClipsHaltExecution == 1 || v14[1] != 2 || v14[2] != g_ClipsFalseSymbol )
        goto LABEL_9;
      goto LABEL_15;
    }
    ++*(_DWORD *)(uintptr_t)(i + 40);
    if ( InstanceQuery_TestClassRestriction(*(_DWORD *)(uintptr_t)(restriction + 12), queryIndex + 1, a5) == 1 )
      break;
    --*(_DWORD *)(uintptr_t)(i + 40);
    if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
      goto LABEL_9;
LABEL_15:
    for ( i = *(_DWORD *)(uintptr_t)(i + 52); i; i = *(_DWORD *)(uintptr_t)(i + 52) )
    {
      if ( (*(_BYTE *)(uintptr_t)(i + 24) & 2) == 0 )
        break;
    }
    if ( !i )
      goto LABEL_9;
  }
  --*(_DWORD *)(uintptr_t)(i + 40);
LABEL_9:
  if ( i )
    return g_ClipsHaltExecution != 1 && g_InstanceQuery_AbortFlag != 1;
  subclassIndex = 0;
  subclassOffset = 0;
  while ( subclassIndex < *(unsigned __int16 *)(uintptr_t)(v17 + 40) )
  {
    if ( InstanceQuery_TestInstancesRecursive(v15, v16, restriction, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v17 + 42) + subclassOffset), a5, queryIndex) )
      return 1;
    if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
      return 0;
    subclassOffset += 4;
    ++subclassIndex;
  }
  return 0;
}
// 4CF8AE: variable 'i' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CF9F0) --------------------------------------------------------
void  InstanceQuery_ForEachClassRestriction(int *restrictionList, int queryIndex, double a3)
{
  int *currentRestriction; // esi
  signed int traversalID; // eax

  currentRestriction = restrictionList;
  for ( g_InstanceQuery_AbortFlag = 1; currentRestriction; currentRestriction = (int *)(uintptr_t)currentRestriction[2] )
  {
    g_InstanceQuery_AbortFlag = 0;
    traversalID = Class_NewTraversalID();
    if ( traversalID == -1 )
      break;
    InstanceQuery_ForEachInstanceRecursive(currentRestriction[1], traversalID, (int)(intptr_t)restrictionList, *currentRestriction, a3, queryIndex);
    Class_ReleaseTraversalID();
    if ( g_ClipsHaltExecution == 1 )
      break;
    if ( g_InstanceQuery_AbortFlag == 1 )
      break;
  }
}
// 51A968: using guessed type int dword_51A968;
// 51B460: using guessed type int dword_51B460;

//----- (004CFA70) --------------------------------------------------------
void  InstanceQuery_ForEachInstanceRecursive(int theModule, signed int traversalID, int restriction, int theClass, double a5, int queryIndex)
{
  int traversalByte; // ebx
  int traversalMask; // eax
  int v9; // edx
  int i; // ecx
  unsigned int subclassIndex; // ebp
  int j; // edi
  bool v13; // zf
  int v14; // ecx
  int v15; // ecx
  _DWORD v16[6]; // [esp+0h] [ebp-30h] BYREF
  int v17; // [esp+18h] [ebp-18h]
  signed int v18; // [esp+1Ch] [ebp-14h]
  int v19; // [esp+20h] [ebp-10h]

  v17 = theModule;
  v18 = traversalID;
  v19 = theClass;
  traversalByte = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  traversalMask = 1 << (traversalID % 8);
  if ( ((unsigned __int8)traversalMask & *(_BYTE *)(uintptr_t)(traversalByte + 108)) == 0 )
  {
    v9 = v17;
    *(_BYTE *)(uintptr_t)(traversalByte + 108) |= traversalMask;
    if ( Class_IsInScope(v19, v9) )
    {
      i = *(_DWORD *)(uintptr_t)(v19 + 80);
      if ( i )
      {
        while ( 1 )
        {
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsQueryCore + 4 * queryIndex) = i;
          if ( *(_DWORD *)(uintptr_t)(restriction + 12) )
            break;
          ++*(_DWORD *)(uintptr_t)(i + 40);
          ++g_ClipsCurrentEvaluationDepth;
          Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4), v16, i, a5);
          --g_ClipsCurrentEvaluationDepth;
          Rules_RunPeriodicCleanup(0, 1);
          --*(_DWORD *)(uintptr_t)(i + 40);
          if ( g_ClipsHaltExecution == 1 )
            goto LABEL_7;
          if ( v16[1] == 2 && v16[2] == g_ClipsFalseSymbol )
            goto LABEL_15;
          if ( *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8) )
          {
            ++*(_DWORD *)(uintptr_t)(i + 40);
            ++g_ClipsCurrentEvaluationDepth;
            Rules_ValueDeinstall(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28), i);
            Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 8), (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28), v14, a5);
            Rules_ValueInstall(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 28), v15);
            --g_ClipsCurrentEvaluationDepth;
            Rules_RunPeriodicCleanup(0, 1);
            --*(_DWORD *)(uintptr_t)(i + 40);
            if ( g_ClipsHaltExecutionFlag )
            {
              g_InstanceQuery_AbortFlag = 1;
              goto LABEL_7;
            }
            v13 = g_ClipsHaltExecution == 1;
            goto LABEL_14;
          }
          InstanceQuery_EnqueueDelayedBinding();
LABEL_15:
          for ( i = *(_DWORD *)(uintptr_t)(i + 52); i; i = *(_DWORD *)(uintptr_t)(i + 52) )
          {
            if ( (*(_BYTE *)(uintptr_t)(i + 24) & 2) == 0 )
              break;
          }
          if ( !i )
            goto LABEL_7;
        }
        ++*(_DWORD *)(uintptr_t)(i + 40);
        InstanceQuery_ForEachClassRestriction(*(_DWORD *)(uintptr_t)(restriction + 12), queryIndex + 1, a5);
        --*(_DWORD *)(uintptr_t)(i + 40);
        if ( g_ClipsHaltExecution == 1 )
          goto LABEL_7;
        v13 = g_InstanceQuery_AbortFlag == 1;
LABEL_14:
        if ( v13 )
          goto LABEL_7;
        goto LABEL_15;
      }
LABEL_7:
      if ( !i )
      {
        subclassIndex = 0;
        for ( j = 0; subclassIndex < *(unsigned __int16 *)(uintptr_t)(v19 + 40); j += 4 )
        {
          InstanceQuery_ForEachInstanceRecursive(v17, v18, restriction, *(_DWORD *)(uintptr_t)(j + *(_DWORD *)(uintptr_t)(v19 + 42)), a5, queryIndex);
          if ( g_ClipsHaltExecution == 1 || g_InstanceQuery_AbortFlag == 1 )
            break;
          ++subclassIndex;
        }
      }
    }
  }
}
// 4CFB17: variable 'i' is possibly undefined
// 4CFC30: variable 'v14' is possibly undefined
// 4CFC3D: variable 'v15' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type __int64 qword_51ACC0;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CFCB0) --------------------------------------------------------
int InstanceQuery_EnqueueDelayedBinding(void)
{
  _DWORD *bindingNode; // edi
  _DWORD *valuesArray; // eax
  _DWORD *v2; // edx
  int copyIndex; // edx
  int copyOffset; // eax
  int result; // eax
  _DWORD *destSlot; // esi
  int value; // ecx

  bindingNode = Mem_SmallBlockAlloc(8u);
  valuesArray = Mem_SmallBlockAlloc(4 * *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 20));
  *v2 = valuesArray;
  copyIndex = 0;
  copyOffset = 0;
  while ( copyIndex < *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 20) )
  {
    destSlot = (_DWORD *)(uintptr_t)(*bindingNode + copyOffset);
    ++copyIndex;
    value = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsQueryCore + copyOffset);
    copyOffset += 4;
    *destSlot = value;
  }
  bindingNode[1] = 0;
  if ( *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) )
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 16) + 4) = bindingNode;
  else
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) = bindingNode;
  *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 16) = bindingNode;
  result = g_ClipsQueryCore;
  ++*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 24);
  return result;
}
// 4CFCD7: variable 'v2' is possibly undefined
// 51B458: using guessed type int dword_51B458;

//----- (004CFD30) --------------------------------------------------------
signed int InstanceQuery_DequeueDelayedBinding(void)
{
  *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 16) = *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12);
  *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 12) + 4);
  Mem_SmallBlockFree(**(_DWORD ***)(uintptr_t)(g_ClipsQueryCore + 16), 4 * *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 20));
  return Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 16), 8);
}
// 51B458: using guessed type int dword_51B458;

//----- (004CFD80) --------------------------------------------------------
int ObjectsCompiler_RegisterCodeGenerator(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aObjects, 0, (int)(intptr_t)ObjectsCompiler_WriteRuntimeInitCall, (int)(intptr_t)ObjectsCompiler_AssignConstructIndices, (int)(intptr_t)ObjectsCompiler_GenerateObjectsCode, 13);
  g_ClipsConstructCompilerData = result;
  return result;
}
// 4CFE40: using guessed type int sub_4CFE40();
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFDB0) --------------------------------------------------------
int  ObjectsCompiler_WriteDefclassPointerRef(int imageID, int theDefclass, int fileID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( theDefclass )
    return Output_WriteFormatted(
             fileID,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20) + 4),
             imageID,
             (int)(intptr_t)aSD_DD_1,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20) + 4));
  else
    return Output_WriteFormatted(fileID, 0, imageID, (int)(intptr_t)aNull_7, v4);
}
// 4CFDC0: variable 'v4' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFE00) --------------------------------------------------------
int  ObjectsCompiler_WriteModuleItemHeaderRef(int imageID, int fileID)
{
  return Output_WriteFormatted(fileID, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20), imageID, (int)(intptr_t)aMihsSD_DD_1, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20));
}
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFE40) --------------------------------------------------------
int ObjectsCompiler_AssignConstructIndices(void)
{
  int slotIndex; // edx
  int i; // ecx
  int result; // eax

  Rules_DoForAllConstructs((void (*)(void))ObjectsCompiler_AssignClassCompileIndex, 0);
  slotIndex = 0;
  for ( i = 0; i != 668; i += 4 )
  {
    for ( result = *(_DWORD *)(uintptr_t)(i + g_Defclass_SlotNameHashTablePtr); result; ++slotIndex )
    {
      *(_DWORD *)(uintptr_t)(result + 24) = slotIndex;
      result = *(_DWORD *)(uintptr_t)(result + 20);
    }
  }
  return result;
}
// 4CFE40: using guessed type int sub_4CFE40();
// 51ACF0: using guessed type int dword_51ACF0;
// 51AD70: using guessed type int dword_51AD70;
// 54E6BC: using guessed type int dword_54E6BC;

//----- (004CFEB0) --------------------------------------------------------
_DWORD * ObjectsCompiler_AssignClassCompileIndex(_DWORD *theClass, _DWORD *indexCounter)
{
  int classIndex; // ebx
  _DWORD *result; // eax
  int v6; // edx
  unsigned int slotIndex; // ebx
  int slotOffset; // edx
  int v9; // ebp
  int v10; // edi

  classIndex = (*indexCounter)++;
  result = indexCounter;
  v6 = theClass[16];
  theClass[3] = classIndex;
  slotIndex = 0;
  if ( v6 )
  {
    slotOffset = 0;
    do
    {
      *(_DWORD *)(uintptr_t)(slotOffset + theClass[13] + 28) = ((unsigned __int16)result[2] << 16) | (unsigned __int16)result[1];
      v9 = result[2] + 1;
      result[2] = v9;
      if ( v9 >= result[3] )
      {
        v10 = result[1];
        result[2] = 0;
        result[1] = v10 + 1;
      }
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < theClass[16] );
  }
  return result;
}

//----- (004CFF30) --------------------------------------------------------
int  ObjectsCompiler_WriteSlotNamePointerRef(int imageID, int slotNamePtr, int fileID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( slotNamePtr )
    return Output_WriteFormatted(
             fileID,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20) + 32),
             imageID,
             (int)(intptr_t)aSD_DD_1,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20) + 32));
  else
    return Output_WriteFormatted(fileID, 0, imageID, (int)(intptr_t)aNull_7, v4);
}
// 4CFF40: variable 'v4' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFF80) --------------------------------------------------------
int  ObjectsCompiler_WriteRuntimeInitCall(int fileID, int imageID)
{
  return Output_WriteFormatted(fileID, imageID, fileID, (int)(intptr_t)aObjectsruntime, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20) + 40));
}
// 54E8F8: using guessed type int dword_54E8F8;

//----- (004CFFC0) --------------------------------------------------------
void  ObjectsCompiler_GenerateObjectsCode(const char *fileName, const char *pathName, DWORD fileNameBuffer, int fileID, int maxIndices)
{
  int initIndex; // eax
  int v9; // edx
  int v10; // ebx
  int v11; // edx
  int v12; // ecx
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // edx
  _DWORD v17[3] CLASH95_UNUSED; // [esp+0h] [ebp-10Ch]
  const char *v18[3]; // [esp+Ch] [ebp-100h] BYREF
  const char *v19[3]; // [esp+18h] [ebp-F4h] BYREF
  const char *v20; // [esp+24h] [ebp-E8h] BYREF
  const char *v21; // [esp+30h] [ebp-DCh] BYREF
  const char *v22; // [esp+3Ch] [ebp-D0h] BYREF
  const char *v23; // [esp+48h] [ebp-C4h] BYREF
  const char *v24; // [esp+54h] [ebp-B8h] BYREF
  const char *v25[3]; // [esp+60h] [ebp-ACh] BYREF
  int moduleFileCount; // [esp+6Ch] [ebp-A0h] BYREF
  int classFileCount; // [esp+70h] [ebp-9Ch] BYREF
  int v28; // [esp+74h] [ebp-98h] BYREF
  int v29; // [esp+78h] [ebp-94h] BYREF
  int v30; // [esp+7Ch] [ebp-90h] BYREF
  int v31; // [esp+80h] [ebp-8Ch] BYREF
  int v32; // [esp+84h] [ebp-88h] BYREF
  int v33; // [esp+88h] [ebp-84h] BYREF
  int moduleFile; // [esp+8Ch] [ebp-80h] BYREF
  int classFile; // [esp+90h] [ebp-7Ch]
  int v36; // [esp+94h] [ebp-78h] BYREF
  int v37; // [esp+98h] [ebp-74h] BYREF
  int v38; // [esp+9Ch] [ebp-70h] BYREF
  int v39; // [esp+A0h] [ebp-6Ch] BYREF
  int v40; // [esp+A4h] [ebp-68h] BYREF
  int v41; // [esp+A8h] [ebp-64h] BYREF
  int v42; // [esp+ACh] [ebp-60h] BYREF
  int v43; // [esp+B0h] [ebp-5Ch] BYREF
  int v44; // [esp+B4h] [ebp-58h] BYREF
  int v45; // [esp+B8h] [ebp-54h] BYREF
  int v46; // [esp+BCh] [ebp-50h] BYREF
  int v47; // [esp+C0h] [ebp-4Ch] BYREF
  int v48; // [esp+C4h] [ebp-48h] BYREF
  int v49; // [esp+C8h] [ebp-44h] BYREF
  int v50; // [esp+CCh] [ebp-40h] BYREF
  int v51; // [esp+D0h] [ebp-3Ch] BYREF
  int v52; // [esp+D4h] [ebp-38h] BYREF
  int v53; // [esp+D8h] [ebp-34h] BYREF
  int v54; // [esp+DCh] [ebp-30h] BYREF
  int v55; // [esp+E0h] [ebp-2Ch] BYREF
  int v56; // [esp+E4h] [ebp-28h] BYREF
  int v57; // [esp+E8h] [ebp-24h] BYREF
  int version; // [esp+ECh] [ebp-20h] BYREF
  int fileIDCopy; // [esp+F0h] [ebp-1Ch]
  _DWORD *j; // [esp+F4h] [ebp-18h]
  int i; // [esp+F8h] [ebp-14h]
  int moduleIndex; // [esp+FCh] [ebp-10h]

  fileIDCopy = fileID;
  initIndex = 0;
  version = 1;
  moduleIndex = 0;
  v9 = 0;
  do
  {
    ++initIndex;
    v9 += 3;
    v25[initIndex + 2] = 0;
    *(int *)((char *)&v49 + initIndex * 4) = 1;
    *(int *)((char *)&v33 + initIndex * 4) = 0;
    *(int *)((char *)&v41 + initIndex * 4) = 0;
    v17[v9] = 0;
  }
  while ( initIndex != 8 );
  v10 = fileIDCopy;
  Output_WriteFormatted(1, v9 * 4, fileIDCopy, (int)(intptr_t)aIncludeClassco, (char)(intptr_t)v18[0]);
  Output_WriteFormatted(v12, v11, v10, (int)(intptr_t)aIncludeClassin, (char)(intptr_t)v18[0]);
  if ( ObjectsCompiler_WriteClassPointerArray(fileName, pathName, fileNameBuffer, v10, maxIndices, &version) )
  {
    if ( ObjectsCompiler_WriteClassHashTable(fileName, pathName, fileNameBuffer, fileIDCopy, maxIndices, &version) )
    {
      ObjectsCompiler_WriteSlotNameHashTable(fileName, pathName, fileNameBuffer, fileIDCopy, maxIndices, &version);
      if ( v13 )
      {
        if ( ObjectsCompiler_WriteSlotNameRecords(fileName, pathName, fileNameBuffer, fileIDCopy, maxIndices, &version) )
        {
          for ( i = Module_NextEnum(0); i; ++moduleFileCount )
          {
            Module_SetCurrent(i);
            v14 = Rules_ConstructCodeFileOpen(
                    moduleFile,
                    fileName,
                    fileNameBuffer,
                    pathName,
                    &version,
                    v50,
                    fileIDCopy,
                    (char)(intptr_t)aDefclass_modul,
                    **(const char ***)(uintptr_t)(g_ClipsConstructCompilerData + 20),
                    v42,
                    v18);
            moduleFile = v14;
            if ( !v14 )
              break;
            ObjectsCompiler_WriteModuleRecord(v14, i, maxIndices);
            moduleFile = Rules_ConstructCodeFileClose(moduleFile, &moduleFileCount, maxIndices, &v50, &v42, (int)(intptr_t)v18);
            for ( j = (_DWORD *)(uintptr_t)Class_GetNextRecord(0); j; j = (_DWORD *)(uintptr_t)Class_GetNextRecord((int)(intptr_t)j) )
            {
              v15 = Rules_ConstructCodeFileOpen(
                      classFile,
                      fileName,
                      fileNameBuffer,
                      pathName,
                      &version,
                      v51,
                      fileIDCopy,
                      (char)(intptr_t)aDefclass_6,
                      (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsConstructCompilerData + 20) + 4),
                      v43,
                      v19);
              classFile = v15;
              if ( !v15 )
                goto LABEL_20;
              ObjectsCompiler_WriteClassRecord(v15, fileNameBuffer, (int)(intptr_t)j, maxIndices, moduleIndex, v52, v28, v53, v29, v54, v30, v55, v31, v56, v32, v57, v33);
              ++classFileCount;
              classFile = Rules_ConstructCodeFileClose(classFile, &classFileCount, maxIndices, &v51, &v43, (int)(intptr_t)v19);
              if ( !ObjectsCompiler_WriteClassLinkPointerArray(&v36, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)(intptr_t)j, &v52, &v28, &v44, &v20)
                || !ObjectsCompiler_WriteSlotDescArray(&v37, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)(intptr_t)j, &v53, &v29, &v45, &v21)
                || !ObjectsCompiler_WriteSlotDescPointerArray(&v38, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)(intptr_t)j, &v54, &v30, &v46, &v22)
                || !ObjectsCompiler_WriteSlotIndexMapArray(&v39, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, j, &v55, &v31, &v47, &v23)
                || !ObjectsCompiler_WriteHandlerArray(&v40, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)(intptr_t)j, &v56, &v32, &v48, &v24)
                || !ObjectsCompiler_WriteHandlerIndexMapArray(&v41, fileName, fileNameBuffer, pathName, fileIDCopy, &version, maxIndices, (int)(intptr_t)j, &v57, &v33, &v49, v25) )
              {
                goto LABEL_20;
              }
            }
            i = Module_NextEnum(i);
            moduleIndex = v16 + 1;
          }
LABEL_20:
          ObjectsCompiler_CloseConstructFileGroup(&moduleFile, &v42, maxIndices, (int)(intptr_t)v18);
        }
      }
    }
  }
}
// 4D0036: variable 'v12' is possibly undefined
// 4D0036: variable 'v11' is possibly undefined
// 4D00B3: variable 'v13' is possibly undefined
// 4D04ED: variable 'v16' is possibly undefined
// 54E8F8: using guessed type int dword_54E8F8;
