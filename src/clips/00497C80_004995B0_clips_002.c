/* Generated from src/recovered/rules/clips/00496000_events.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00497C80) --------------------------------------------------------
int  Defgeneric_ListDefmethodsCommand(int returnValue, double context)
{
  int v2; // ecx
  int result; // eax
  _DWORD argData[9]; // [esp-8h] [ebp-24h] BYREF

  argData[7] = returnValue;
  if ( !Rules_RtnArgCount() )
    return Defgeneric_ListMethodsAndTally((int)(intptr_t)g_IO_LogicalName_WDisplay, 0, v2);
  result = Lexer_ParseValueList(1, argData, 2, context);
  if ( result )
  {
    result = Defgeneric_CheckGenericExists((int)(intptr_t)aListDefmethods, *(_BYTE **)(uintptr_t)(argData[2] + 16));
    if ( result )
      return Defgeneric_ListMethodsAndTally((int)(intptr_t)g_IO_LogicalName_WDisplay, result, (int)(intptr_t)g_IO_LogicalName_WDisplay);
  }
  return result;
}
// 497CB7: variable 'v2' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (00497D10) --------------------------------------------------------
int  Defgeneric_ListDefgenericsCommand(int logicalName, double context)
{
  return Rules_ListConstructsCommand(g_Clips_DefgenericConstructType, logicalName, context);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497D50) --------------------------------------------------------
int  Defgeneric_ListMethodsAndTally(int logicalName, int theGeneric, int a3)
{
  int methodCount; // edi
  int i; // ecx
  int v6; // ecx
  int v7; // ecx

  if ( theGeneric )
  {
    methodCount = Defgeneric_PrintMethodsList(a3, theGeneric);
  }
  else
  {
    methodCount = 0;
    for ( i = Class_Enum(0, g_DefgenericModuleItemIndex); i; i = Class_Enum(v7, g_DefgenericModuleItemIndex) )
    {
      methodCount += Defgeneric_PrintMethodsList(i, i);
      if ( Class_Enum(v6, g_DefgenericModuleItemIndex) )
        Output_Write(logicalName, (int)(intptr_t)asc_50537C, v7);
    }
  }
  return Rules_PrintTally(logicalName, methodCount, (int)(intptr_t)aMethods, (int)(intptr_t)aMethod_1);
}
// 497D82: variable 'v6' is possibly undefined
// 497D92: variable 'v7' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497DD0) --------------------------------------------------------
_DWORD * Defgeneric_GetDefgenericListCommand(int returnValue, double context)
{
  return Rules_GetConstructListCommand(returnValue, g_Clips_DefgenericConstructType, context);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00497E10) --------------------------------------------------------
_DWORD * Defgeneric_GetDefmethodListCommand(_DWORD *returnValue, int a2, double context)
{
  int theGeneric; // eax
  _DWORD argData[10]; // [esp-8h] [ebp-28h] BYREF

  argData[8] = a2;
  theGeneric = Rules_RtnArgCount();
  if ( !theGeneric )
    return Defgeneric_BuildMethodListValue(theGeneric, returnValue);
  if ( Lexer_ParseValueList(1, argData, 2, context) && (theGeneric = Defgeneric_CheckGenericExists((int)(intptr_t)aGetDefmethodLi, *(_BYTE **)(uintptr_t)(argData[2] + 16))) != 0 )
    return Defgeneric_BuildMethodListValue(theGeneric, returnValue);
  else
    return Rules_SetMultifieldErrorValue((int)(intptr_t)returnValue);
}

//----- (00497E70) --------------------------------------------------------
_DWORD * Defgeneric_BuildMethodListValue(int theGeneric, _DWORD *returnValue)
{
  int v4; // eax
  int genericCursor; // ecx
  int i; // ebx
  signed int multifieldSize; // ebx
  _DWORD *result; // eax
  int v9; // ecx
  int currentGeneric; // ebx
  _DWORD *theMultifield; // edi
  int methodOffset; // esi
  int v13; // ebp
  int v14; // ecx
  int v15; // ecx
  unsigned int v16; // edx
  int savedNext; // [esp+0h] [ebp-20h]
  int v18; // [esp+4h] [ebp-1Ch]
  int firstGeneric; // [esp+8h] [ebp-18h]

  if ( theGeneric )
  {
    savedNext = Class_Enum(theGeneric, g_DefgenericModuleItemIndex);
    Rules_SetConstructNextInModule(theGeneric, 0);
  }
  else
  {
    v4 = Class_Enum(0, g_DefgenericModuleItemIndex);
    genericCursor = v4;
    if ( v4 )
      v4 = Class_Enum(v4, g_DefgenericModuleItemIndex);
    savedNext = v4;
  }
  firstGeneric = genericCursor;
  for ( i = 0; genericCursor; genericCursor = Class_Enum(genericCursor, g_DefgenericModuleItemIndex) )
    i += *(_DWORD *)(uintptr_t)(genericCursor + 32);
  multifieldSize = 2 * i;
  returnValue[1] = 4;
  returnValue[4] = multifieldSize - 1;
  returnValue[3] = 0;
  result = Rules_CreateEphemeralMultifield(multifieldSize);
  currentGeneric = firstGeneric;
  theMultifield = result;
  returnValue[2] = result;
  if ( firstGeneric )
  {
    do
    {
      if ( *(_DWORD *)(uintptr_t)(currentGeneric + 32) )
      {
        methodOffset = 0;
        do
        {
          v13 = 6 * (v9 - 1);
          v18 = v9;
          *(_WORD *)((char *)theMultifield + v13 + 14) = 2;
          *(_DWORD *)((char *)theMultifield + v13 + 16) = Rules_GetConstructNameSymbol(currentGeneric);
          *((_WORD *)theMultifield + 3 * v18 + 7) = 1;
          methodOffset += 40;
          *(_DWORD *)((char *)theMultifield + 6 * v14 + 16) = Rules_AddIntegerValue(*(_DWORD *)(uintptr_t)(methodOffset + *(_DWORD *)(uintptr_t)(currentGeneric + 28) - 40));
          v9 = v15 + 1;
        }
        while ( v16 < *(_DWORD *)(uintptr_t)(currentGeneric + 32) );
      }
      result = (_DWORD *)(uintptr_t)Class_Enum(currentGeneric, g_DefgenericModuleItemIndex);
      currentGeneric = (int)(intptr_t)result;
    }
    while ( result );
  }
  if ( firstGeneric )
    return (_DWORD *)(uintptr_t)Rules_SetConstructNextInModule(firstGeneric, savedNext);
  return result;
}
// 497EA3: variable 'v5' is possibly undefined
// 497F0A: variable 'v9' is possibly undefined
// 497F3C: variable 'v14' is possibly undefined
// 497F57: variable 'v15' is possibly undefined
// 497F5A: variable 'v16' is possibly undefined
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00497FC0) --------------------------------------------------------
int * Defgeneric_GetMethodRestrictionsCommand(_DWORD *returnValue, int a2, double context)
{
  int theGeneric; // edi
  _DWORD argData[2]; // [esp-8h] [ebp-2Ch] BYREF
  int argValue; // [esp+0h] [ebp-24h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a2;
  if ( Lexer_ParseValueList(1, argData, 2, context)
    && (theGeneric = Defgeneric_CheckGenericExists((int)(intptr_t)aGetMethodRestr, *(_BYTE **)(uintptr_t)(argValue + 16))) != 0
    && Lexer_ParseValueList(2, argData, 1, context)
    && Defgeneric_CheckMethodExists((int)(intptr_t)aGetMethodRestr, theGeneric, *(_DWORD *)(uintptr_t)(argValue + 16)) != -1 )
  {
    return Defgeneric_BuildMethodRestrictionsValue(theGeneric, *(_DWORD *)(uintptr_t)(argValue + 16), returnValue);
  }
  else
  {
    return Rules_SetMultifieldErrorValue((int)(intptr_t)returnValue);
  }
}

//----- (00498060) --------------------------------------------------------
int * Defgeneric_BuildMethodRestrictionsValue(int theGeneric, int methodIndex, _DWORD *returnValue)
{
  signed int methodPosition; // eax
  int v5; // ecx
  int methodAddr; // edx
  signed int fieldCount; // ecx
  signed int restrictionScanIndex; // eax
  int restrictionScanPtr; // edx
  _DWORD *theMultifield; // eax
  int v11; // ecx
  _DWORD *multifield; // ebx
  int *result; // eax
  int v14; // edx
  signed int fieldIndex; // edx
  _DWORD *restriction; // edi
  int *fieldIndexValue; // eax
  int v18; // edx
  int v19; // ecx
  int querySymbol; // eax
  int v21; // ecx
  int v22; // edx
  unsigned int typeIndex; // esi
  int typeOffset; // ecx
  char *typeCellPtr; // ebx
  char *typeValueCell; // ebp
  char *className; // eax
  int v28; // ecx
  int v29; // edx
  char *restrictionCellPtr; // [esp+4h] [ebp-28h]
  int v31; // [esp+8h] [ebp-24h]
  int restrictionOffset; // [esp+Ch] [ebp-20h]
  signed int restrictionIndex; // [esp+10h] [ebp-1Ch]
  signed int *theMethod; // [esp+14h] [ebp-18h]
  _DWORD *multifieldPtr; // [esp+18h] [ebp-14h]

  methodPosition = Method_FindByIndex(theGeneric, methodIndex);
  methodAddr = 40 * methodPosition + *(_DWORD *)(uintptr_t)(v5 + 28);
  fieldCount = 3;
  theMethod = (signed int *)(uintptr_t)methodAddr;
  restrictionScanIndex = 0;
  if ( *(int *)(uintptr_t)(methodAddr + 8) > 0 )
  {
    restrictionScanPtr = *(_DWORD *)(uintptr_t)(methodAddr + 28);
    do
    {
      fieldCount += *(_DWORD *)(uintptr_t)(restrictionScanPtr + 8) + 3;
      ++restrictionScanIndex;
      restrictionScanPtr += 12;
    }
    while ( restrictionScanIndex < theMethod[2] );
  }
  theMultifield = Rules_CreateEphemeralMultifield(fieldCount);
  returnValue[1] = 4;
  returnValue[3] = 0;
  returnValue[2] = theMultifield;
  multifield = theMultifield;
  returnValue[4] = v11 - 1;
  multifieldPtr = theMultifield;
  *((_WORD *)theMultifield + 7) = 1;
  theMultifield[4] = Rules_AddIntegerValue(theMethod[3]);
  *((_WORD *)multifield + 10) = 1;
  *(_DWORD *)((char *)multifield + 22) = Rules_AddIntegerValue(theMethod[4]);
  *((_WORD *)multifield + 13) = 1;
  multifield[7] = Rules_AddIntegerValue(theMethod[2]);
  restrictionIndex = 0;
  result = theMethod;
  v31 = 4;
  fieldIndex = *(_DWORD *)(uintptr_t)(v14 + 8) + 4;
  if ( theMethod[2] > 0 )
  {
    restrictionCellPtr = (char *)multifield + 18;
    restrictionOffset = 0;
    do
    {
      restriction = (_DWORD *)(uintptr_t)(restrictionOffset + theMethod[7]);
      *((_WORD *)restrictionCellPtr + 7) = 1;
      fieldIndexValue = Rules_AddIntegerValue(fieldIndex);
      *(_DWORD *)(uintptr_t)(v19 + 16) = fieldIndexValue;
      *((_WORD *)multifieldPtr + 3 * v18 + 4) = 2;
      restrictionCellPtr += 6;
      ++v31;
      if ( restriction[1] )
        querySymbol = g_ClipsTrueSymbol;
      else
        querySymbol = g_ClipsFalseSymbol;
      *(_DWORD *)((char *)multifieldPtr + 6 * v18 + 10) = querySymbol;
      *((_WORD *)multifieldPtr + 3 * v18 + 7) = 1;
      result = Rules_AddIntegerValue(restriction[2]);
      *(_DWORD *)(uintptr_t)(v21 + 16) = result;
      fieldIndex = v22 + 1;
      typeIndex = 0;
      if ( restriction[2] )
      {
        typeOffset = 0;
        typeCellPtr = (char *)multifieldPtr + 6 * fieldIndex - 6;
        do
        {
          *((_WORD *)typeCellPtr + 7) = 2;
          typeCellPtr += 6;
          ++typeIndex;
          typeValueCell = (char *)multifieldPtr + 6 * fieldIndex - 6;
          className = (char *)(uintptr_t)Rules_GetConstructNameString(*(_DWORD *)(uintptr_t)(typeOffset + *restriction));
          *((_DWORD *)typeValueCell + 4) = Str_Intern(className, v28);
          fieldIndex = v29 + 1;
          result = (int *)(uintptr_t)restriction[2];
        }
        while ( typeIndex < (unsigned int)(intptr_t)result );
      }
      restrictionOffset += 12;
      ++restrictionIndex;
    }
    while ( restrictionIndex < theMethod[2] );
  }
  return result;
}
// 498082: variable 'v5' is possibly undefined
// 4980D5: variable 'v11' is possibly undefined
// 498138: variable 'v14' is possibly undefined
// 498185: variable 'v19' is possibly undefined
// 498188: variable 'v18' is possibly undefined
// 4981E2: variable 'v21' is possibly undefined
// 4981E5: variable 'v22' is possibly undefined
// 49821D: variable 'v24' is possibly undefined
// 498229: variable 'v28' is possibly undefined
// 498231: variable 'v29' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (00498280) --------------------------------------------------------
int  Defgeneric_EvaluateGenericFunctionCall(int theGeneric, _DWORD *returnValue, double context)
{
  int v4; // eax

  Method_DispatchGenericCall(theGeneric, 0, *(_DWORD **)(uintptr_t)(g_ClipsCurrentExpression + 6), 0, context, returnValue);
  if ( returnValue[1] == 2 && (v4 = returnValue[2], v4 == g_ClipsFalseSymbol) )
    return g_ClipsFalseSymbol ^ v4;
  else
    return 1;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004982C0) --------------------------------------------------------
int  Defgeneric_DecrementGenericBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(uintptr_t)(result + 20);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (004982D0) --------------------------------------------------------
int  Defgeneric_IncrementGenericBusyCount(int result)
{
  ++*(_DWORD *)(uintptr_t)(result + 20);
  return result;
}

//----- (004982E0) --------------------------------------------------------
int  Defgeneric_SaveConstructs(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_Clips_DefgenericConstructType);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (004982F0) --------------------------------------------------------
signed int Defmethod_SaveConstructs(void)
{
  return Rules_DoForAllConstructs((void (*)(void))Defgeneric_WriteMethodPPForms, 0);
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00498310) --------------------------------------------------------
signed int  Defgeneric_WriteMethodPPForms(signed int result, signed int logicalName)
{
  signed int theGeneric; // edi
  signed int logName; // ecx
  unsigned int methodIndex; // ebx
  int methodOffset; // esi
  char *ppForm; // edx
  int v7; // ecx

  theGeneric = result;
  logName = logicalName;
  methodIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(result + 32) )
  {
    methodOffset = 0;
    do
    {
      result = methodOffset + *(_DWORD *)(uintptr_t)(theGeneric + 28);
      ppForm = *(char **)(uintptr_t)(result + 36);
      if ( ppForm )
      {
        Output_WriteLongString(logName, ppForm);
        result = Output_Write(v7, (int)(intptr_t)asc_50537C, v7);
      }
      ++methodIndex;
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(uintptr_t)(theGeneric + 32) );
  }
  return result;
}
// 498343: variable 'v3' is possibly undefined
// 49834F: variable 'v7' is possibly undefined

//----- (00498360) --------------------------------------------------------
signed int  Defgeneric_DeleteMethod(int theGeneric, int methodIndex)
{
  int methodAddr; // edx
  int methodCount; // edx
  unsigned int copyIndex; // ebx
  char *newMethodArray; // eax
  int sourceIndex; // edx
  char *destPtr; // ebp
  signed int result; // eax
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  signed int newArrayAddr; // [esp+0h] [ebp-14h]

  methodAddr = 40 * methodIndex + *(_DWORD *)(uintptr_t)(theGeneric + 28);
  if ( (*(_BYTE *)(uintptr_t)(methodAddr + 24) & 1) != 0 )
  {
    Lexer_ErrorRecover(1);
    Rules_PrintErrorID((int)(intptr_t)aGenrccom, v9, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotRemoveIm, v10);
    v11 = Rules_GetConstructNameString(theGeneric);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v11, v12);
    return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__15, v13);
  }
  else
  {
    Defgeneric_DeleteMethodInfo(theGeneric, methodAddr);
    methodCount = *(_DWORD *)(uintptr_t)(theGeneric + 32);
    if ( methodCount == 1 )
    {
      Mem_SmallBlockFree(*(_DWORD **)(uintptr_t)(theGeneric + 28), 40);
      result = theGeneric;
      *(_DWORD *)(uintptr_t)(theGeneric + 32) = 0;
      *(_DWORD *)(uintptr_t)(theGeneric + 28) = 0;
    }
    else
    {
      *(_DWORD *)(uintptr_t)(theGeneric + 32) = methodCount - 1;
      copyIndex = 0;
      newMethodArray = (char *)Mem_SmallBlockAlloc(40 * (methodCount - 1));
      newArrayAddr = (signed int)(intptr_t)newMethodArray;
      if ( *(_DWORD *)(uintptr_t)(theGeneric + 32) )
      {
        destPtr = newMethodArray;
        do
        {
          if ( copyIndex == methodIndex )
            ++sourceIndex;
          qmemcpy(destPtr, (const void *)(uintptr_t)(40 * sourceIndex + *(_DWORD *)(uintptr_t)(theGeneric + 28)), 0x28u);
          ++copyIndex;
          destPtr += 40;
          ++sourceIndex;
        }
        while ( copyIndex < *(_DWORD *)(uintptr_t)(theGeneric + 32) );
      }
      Mem_SmallBlockFree(*(_DWORD **)(uintptr_t)(theGeneric + 28), 40 * (*(_DWORD *)(uintptr_t)(theGeneric + 32) + 1));
      result = newArrayAddr;
      *(_DWORD *)(uintptr_t)(theGeneric + 28) = newArrayAddr;
    }
  }
  return result;
}
// 4983E4: variable 'v6' is possibly undefined
// 498466: variable 'v9' is possibly undefined
// 498475: variable 'v10' is possibly undefined
// 49848D: variable 'v12' is possibly undefined
// 49849C: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004984D0) --------------------------------------------------------
int __fastcall Defgeneric_PrintMethodsList(int logicalName, int theGeneric)
{
  unsigned int methodIndex; // ebp
  int methodOffset; // edi
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  char signatureBuffer[276]; // [esp+0h] [ebp-114h] BYREF

  methodIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(theGeneric + 32) )
  {
    methodOffset = 0;
    do
    {
      v5 = Rules_GetConstructNameString(theGeneric);
      Output_Write(v6, v5, v6);
      Output_Write(v7, (int)(intptr_t)asc_505344, v7);
      Defgeneric_AppendMethodSignatureText(signatureBuffer, 255, v8, methodOffset + *(_DWORD *)(uintptr_t)(theGeneric + 28));
      Output_Write(v9, (int)(intptr_t)signatureBuffer, v9);
      ++methodIndex;
      Output_Write(v10, (int)(intptr_t)asc_50537C, v10);
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(uintptr_t)(theGeneric + 32) );
  }
  return *(_DWORD *)(uintptr_t)(theGeneric + 32);
}
// 4984F5: variable 'v6' is possibly undefined
// 498501: variable 'v7' is possibly undefined
// 498512: variable 'v8' is possibly undefined
// 49851B: variable 'v9' is possibly undefined
// 498528: variable 'v10' is possibly undefined

//----- (00498550) --------------------------------------------------------
signed int  Defgeneric_WatchAccessFunction(int newState, int argExprs, double context)
{
  return Rules_ApplyWatchFlagCommand(g_Clips_DefgenericConstructType, newState, (int)(intptr_t)Defgeneric_GetTraceFlag, argExprs, context, (void (*)(void))Defgeneric_SetTraceFlag);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00498570) --------------------------------------------------------
signed int  Defgeneric_WatchPrintFunction(int logicalName, int argExprs, double context)
{
  return Rules_ListWatchFlagStatus(g_Clips_DefgenericConstructType, logicalName, (int)(intptr_t)Defgeneric_GetTraceFlag, argExprs, context, (void (*)(void))Defgeneric_SetTraceFlag);
}
// 54E6A0: using guessed type int dword_54E6A0;

//----- (00498590) --------------------------------------------------------
signed int  Defgeneric_MethodsWatchAccessFunction(int newState, int argExprs, double context)
{
  if ( newState )
    return Defgeneric_WatchMethodsDispatch((int)(intptr_t)aWatch_1, 0, 0, newState, 0, context, (void (*)(void))Defgeneric_SetMethodTraceFlag, argExprs);
  else
    return Defgeneric_WatchMethodsDispatch((int)(intptr_t)aUnwatch_0, 0, 0, 0, 0, context, (void (*)(void))Defgeneric_SetMethodTraceFlag, argExprs);
}

//----- (004985C0) --------------------------------------------------------
signed int  Defgeneric_MethodsWatchPrintFunction(int logicalName, int argExprs, int a3, double context)
{
  return Defgeneric_WatchMethodsDispatch((int)(intptr_t)aListWatchIte_1, logicalName, (void (*)(void))Method_PrintWatchStatusLine, -1, a3, context, 0, argExprs);
}

//----- (004985E0) --------------------------------------------------------
signed int  Defgeneric_WatchMethodsDispatch(
        int funcName,
        int logicalName,
        void (*printFunc)(void),
        int newState,
        int i,
        double context,
        void (*traceFunc)(void),
        int argExprs)
{
  int v9; // ecx
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int k; // esi
  int m; // ecx
  int v16; // ecx
  int theGeneric; // ecx
  int nextExpr; // ebx
  int v19; // ecx
  int v20; // ecx
  _DWORD indexArgData[2]; // [esp+0h] [ebp-50h] BYREF
  int indexArgValue; // [esp+8h] [ebp-48h]
  _DWORD argData[8]; // [esp+18h] [ebp-38h] BYREF
  int j; // [esp+38h] [ebp-18h]
  int argIndex; // [esp+3Ch] [ebp-14h]
  void (*savedPrintFunc)(void); // [esp+40h] [ebp-10h]

  argData[7] = funcName;
  argData[6] = newState;
  savedPrintFunc = printFunc;
  v9 = argExprs;
  argIndex = 2;
  if ( argExprs )
  {
    while ( 1 )
    {
      if ( !argExprs )
        return 1;
      if ( Parser_ParseForm((__int16 *)(uintptr_t)argExprs, argData, v9, context) )
        return 0;
      if ( argData[1] != 2 || (theGeneric = Symbol_LookupInModule((char **)(uintptr_t)g_Clips_DefgenericConstructType, *(_BYTE **)(uintptr_t)(argData[2] + 16), 1)) == 0 )
      {
        Parser_ReportError(argIndex, (int)(intptr_t)aGenericFunct_4);
        return 0;
      }
      nextExpr = *(_DWORD *)(uintptr_t)(argExprs + 10);
      if ( !nextExpr )
        goto LABEL_20;
      ++argIndex;
      argExprs = nextExpr;
      if ( Parser_ParseForm((__int16 *)(uintptr_t)nextExpr, indexArgData, theGeneric, context) )
        return 0;
      if ( indexArgData[1] != 1 || *(int *)(uintptr_t)(indexArgValue + 16) <= 0 || Method_FindByIndex(v20, i) == -1 )
      {
        Parser_ReportError(argIndex, (int)(intptr_t)aMethodIndex);
        return 0;
      }
      i = *(_DWORD *)(uintptr_t)(indexArgValue + 16);
      if ( i )
      {
        if ( traceFunc )
          ((void (__fastcall *)(int, int))traceFunc)(theGeneric, theGeneric);
        else
          ((void (__fastcall *)(int, int))savedPrintFunc)(theGeneric, theGeneric);
        argExprs = *(_DWORD *)(uintptr_t)(nextExpr + 10);
        ++argIndex;
      }
      else
      {
LABEL_20:
        for ( i = Class_NextMethod(theGeneric, 0); i; i = Class_NextMethod(v19, i) )
        {
          if ( traceFunc )
            ((void (__fastcall *)(int, int))traceFunc)(v9, v9);
          else
            ((void (__fastcall *)(int, int))savedPrintFunc)(v9, v9);
        }
        argExprs = *(_DWORD *)(uintptr_t)(argExprs + 10);
        ++argIndex;
      }
    }
  }
  Module_BeginEnum();
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    if ( !traceFunc )
    {
      Name = Module_GetName(j);
      Output_Write(logicalName, Name, v12);
      Output_Write(logicalName, (int)(intptr_t)asc_5053F0, v13);
    }
    for ( k = Class_Enum(0, g_DefgenericModuleItemIndex); k; k = Class_Enum(k, g_DefgenericModuleItemIndex) )
    {
      for ( m = Class_NextMethod(k, 0); m; m = Class_NextMethod(k, v16) )
      {
        if ( traceFunc )
        {
          traceFunc();
        }
        else
        {
          Output_Write(logicalName, (int)(intptr_t)asc_5053F4, m);
          savedPrintFunc();
        }
      }
    }
  }
  Module_EndEnum();
  return 1;
}
// 498655: variable 'v12' is possibly undefined
// 498661: variable 'v13' is possibly undefined
// 49869A: variable 'v16' is possibly undefined
// 4986FE: variable 'v9' is possibly undefined
// 498749: variable 'v17' is possibly undefined
// 49876A: variable 'v19' is possibly undefined
// 4987E0: variable 'v20' is possibly undefined
// 54E6A0: using guessed type int dword_54E6A0;
// 54E6A4: using guessed type int dword_54E6A4;

//----- (00498870) --------------------------------------------------------
signed int  Method_PrintWatchStatusLine(int logicalName, int theGeneric, int methodIndex)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  char signatureBuffer[76]; // [esp+0h] [ebp-4Ch] BYREF

  v5 = Rules_GetConstructNameString(theGeneric);
  Output_Write(logicalName, v5, methodIndex);
  Output_Write(logicalName, (int)(intptr_t)asc_505420, v6);
  Defgeneric_FormatMethodRestrictionsString(signatureBuffer, 59, v7, theGeneric);
  Output_Write(logicalName, (int)(intptr_t)signatureBuffer, v8);
  if ( Defgeneric_GetMethodTraceFlag(theGeneric, methodIndex) )
    return Output_Write(logicalName, (int)(intptr_t)aOn_3, v9);
  else
    return Output_Write(logicalName, (int)(intptr_t)aOff_3, v9);
}
// 498898: variable 'v6' is possibly undefined
// 4988A4: variable 'v7' is possibly undefined
// 4988AD: variable 'v8' is possibly undefined
// 4988C6: variable 'v9' is possibly undefined

//----- (004988F0) --------------------------------------------------------
int Deffunction_InitConstructType(void)
{
  int v0; // ecx

  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_Deffunction, 12);
  g_Clips_DeffunctionModuleItemIndex = Module_RegisterItem(
                   (int)(intptr_t)aDeffunction,
                   (int)(intptr_t)Deffunction_AllocateModule,
                   (int)(intptr_t)Deffunction_RecordAtIndex,
                   (int)(intptr_t)Deffunction_FreeModule,
                   (int)(intptr_t)Deffunction_WriteModuleItemReference,
                   (int)(intptr_t)Deffunction_FindByName);
  g_ClipsDeffunctionConstructType = (int)(intptr_t)Rules_RegisterConstructType(
                        (int)(intptr_t)aDeffunction,
                        (int)(intptr_t)aDeffunctions,
                        (int)(intptr_t)Deffunction_FindByName,
                        (int)(intptr_t)Deffunction_ParseConstruct,
                        (int)(intptr_t)Rules_GetConstructNameSymbol,
                        (int)(intptr_t)Rules_GetModuleConstructListHead,
                        (int)(intptr_t)Rules_GetConstructOwnerModule,
                        (int)(intptr_t)Deffunction_EnumNext,
                        (int)(intptr_t)Rules_SetConstructNextInModule,
                        (int)(intptr_t)Deffunction_IsDeletable,
                        (int)(intptr_t)Deffunction_Delete,
                        (int)(intptr_t)Deffunction_Free);
  Rules_AddClearReadyFunction((int)(intptr_t)aDeffunction, (int)(intptr_t)Deffunction_IsClearReady, 0);
  Module_RegisterImportExportConstructType((int)(intptr_t)aDeffunction, 2);
  Rules_AddSaveFunction((int)(intptr_t)aDeffunctionHea, (int)(intptr_t)Deffunction_SaveHeaders, 1000);
  Rules_AddSaveFunction((int)(intptr_t)aDeffunctions, (int)(intptr_t)Deffunction_SaveBodies, 0);
  Rules_RegisterHostFunction(aUndeffunction, 118, v0, (int)(intptr_t)Deffunction_UndeffunctionCommand, (int)(intptr_t)a11w_3);
  Rules_RegisterHostFunction(aListDeffunctio, 118, (int)(intptr_t)aListdeffunctio, (int)(intptr_t)Deffunction_ListCommand, (int)(intptr_t)a01_0);
  Rules_RegisterHostFunction(aPpdeffunction, 118, (int)(intptr_t)aPpdeffunctionc, (int)(intptr_t)Deffunction_PPCommand, (int)(intptr_t)a11w_3);
  Rules_RegisterHostFunction(aGetDeffunction, 109, (int)(intptr_t)aGetdeffunction, (int)(intptr_t)Deffunction_GetListCommand, (int)(intptr_t)a01_0);
  Rules_RegisterHostFunction(aDeffunctionMod, 119, (int)(intptr_t)aGetdeffuncti_0, (int)(intptr_t)Deffunction_ModuleCommand, (int)(intptr_t)a11w_3);
  Deffunction_RegisterBinaryItem();
  Deffunction_RegisterCodeGenerator();
  return Rules_AddWatchItem((int)(intptr_t)aDeffunctions, 0, 32, (int)(intptr_t)&g_Rules_WatchDeffunctions, (int)(intptr_t)Deffunction_SetWatchAll, (int)(intptr_t)Deffunction_GetWatchAll);
}
// 4989CE: variable 'v0' is possibly undefined
// 51AAE8: using guessed type int dword_51AAE8;
// 54E6A8: using guessed type int dword_54E6A8;
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498A80) --------------------------------------------------------
int  Deffunction_FindByName(_BYTE *deffunctionName, int a2)
{
  return Rules_FindConstructByNameGeneric(deffunctionName, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498AB0) --------------------------------------------------------
int  Deffunction_LookupByName(_BYTE *deffunctionName)
{
  return Symbol_LookupInModule((char **)(uintptr_t)g_ClipsDeffunctionConstructType, deffunctionName, 0);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498AD0) --------------------------------------------------------
signed int Deffunction_Delete(void)
{
  int v0; // edx
  signed int result; // eax
  int v2; // edx

  if ( Rules_IsBloaded() == 1 )
    return 0;
  if ( !v0 )
    return Deffunction_ClearAll();
  result = Deffunction_IsDeletable();
  if ( result )
  {
    Rules_UnlinkListNode(v2);
    Deffunction_Free(v2);
    return 1;
  }
  return result;
}
// 498ADF: variable 'v0' is possibly undefined
// 498AFB: variable 'v2' is possibly undefined

//----- (00498B10) --------------------------------------------------------
int  Deffunction_EnumNext(int deffunctionPtr)
{
  return Class_Enum(deffunctionPtr, g_Clips_DeffunctionModuleItemIndex);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498B20) --------------------------------------------------------
BOOL Deffunction_IsDeletable(void)
{
  int v0; // edx

  return !Rules_IsBloaded() && !*(_DWORD *)(uintptr_t)(v0 + 20) && !*(_DWORD *)(uintptr_t)(v0 + 24);
}
// 498B2C: variable 'v0' is possibly undefined

//----- (00498B50) --------------------------------------------------------
int  Deffunction_Free(int result)
{
  int v1; // eax
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  signed int v6; // ecx
  _DWORD *v7; // ecx

  if ( result )
  {
    v1 = Rules_GetConstructNameSymbol(result);
    Rules_DecrementSymbolCount(v1, v2);
    AST_DeinstallNodeChain(*(__int16 **)(uintptr_t)(v3 + 30));
    AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(v4 + 30));
    Rules_ReplaceConstructPPForm(v6, v5);
    g_ClipsMemFreeListTemp = (int)(intptr_t)v7;
    *v7 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 184);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 184) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 498B5F: variable 'v2' is possibly undefined
// 498B64: variable 'v3' is possibly undefined
// 498B6C: variable 'v4' is possibly undefined
// 498B78: variable 'v6' is possibly undefined
// 498B78: variable 'v5' is possibly undefined
// 498B82: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00498BB0) --------------------------------------------------------
int __thiscall Deffunction_UndeffunctionCommand(void *this)
{
  return Rules_UndefconstructCommand((int)(intptr_t)this, g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498BD0) --------------------------------------------------------
int __thiscall Deffunction_ModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498BF0) --------------------------------------------------------
int __thiscall Deffunction_PPCommand(void *this)
{
  return Rules_PPConstructCommand((int)(intptr_t)this, (const char **)(uintptr_t)g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C10) --------------------------------------------------------
int  Deffunction_ListCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDeffunctionConstructType, a1, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C50) --------------------------------------------------------
_DWORD * Deffunction_GetListCommand(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, g_ClipsDeffunctionConstructType, a2);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498C90) --------------------------------------------------------
int  Deffunction_CheckArgumentCount(int result, int argCount)
{
  int minArgs; // ecx
  int expectedArgs; // ebx
  int deffunctionName; // eax

  if ( result )
  {
    minArgs = *(_DWORD *)(uintptr_t)(result + 34);
    if ( argCount >= minArgs )
    {
      if ( argCount <= minArgs || *(_DWORD *)(uintptr_t)(result + 38) == -1 )
        return 1;
    }
    else if ( *(_DWORD *)(uintptr_t)(result + 38) == -1 )
    {
      expectedArgs = *(_DWORD *)(uintptr_t)(result + 34);
LABEL_5:
      deffunctionName = Rules_GetConstructNameString(result);
      Rules_ExpectedCountError(deffunctionName, expectedArgs);
      return 0;
    }
    expectedArgs = *(_DWORD *)(uintptr_t)(result + 34);
    goto LABEL_5;
  }
  return result;
}

//----- (00498CE0) --------------------------------------------------------
int  Deffunction_CallForBooleanResult(int theDeffunction, _DWORD *returnValue, double context)
{
  int v3; // ecx
  int resultValue; // eax

  Deffunction_CallDeffunction(theDeffunction, *(_DWORD **)(uintptr_t)(g_ClipsCurrentExpression + 6), returnValue, context);
  if ( *(_DWORD *)(uintptr_t)(v3 + 4) == 2 && (resultValue = *(_DWORD *)(uintptr_t)(v3 + 8), resultValue == g_ClipsFalseSymbol) )
    return g_ClipsFalseSymbol ^ resultValue;
  else
    return 1;
}
// 498CF4: variable 'v3' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (00498D20) --------------------------------------------------------
int  Deffunction_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(uintptr_t)(result + 20);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (00498D30) --------------------------------------------------------
int  Deffunction_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(uintptr_t)(result + 20);
  return result;
}

//----- (00498D40) --------------------------------------------------------
signed int Deffunction_AllocateModule(void)
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00498D70) --------------------------------------------------------
int  Deffunction_FreeModule(int theModuleItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theModuleItem, g_ClipsDeffunctionConstructType, theModuleItem);
  freed_node = (_DWORD *)(uintptr_t)theModuleItem;
  g_ClipsMemFreeListTemp = theModuleItem;
  *freed_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498DB0) --------------------------------------------------------
BOOL Deffunction_IsClearReady(void)
{
  return g_CurrentDeffunction == 0;
}
// 51B3E8: using guessed type int dword_51B3E8;

//----- (00498DC0) --------------------------------------------------------
signed int Deffunction_ClearAll(void)
{
  int clearSuccess; // ebx
  int i; // ecx
  int nameString; // eax
  int v4; // ecx
  int v5; // ecx
  int theDeffunction; // esi
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  signed int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // edx
  int v17; // ecx

  clearSuccess = 1;
  if ( Rules_IsBloaded() == 1 )
    return 0;
  for ( i = Class_Enum(0, g_Clips_DeffunctionModuleItemIndex); i; i = Class_Enum(v5, g_Clips_DeffunctionModuleItemIndex) )
  {
    if ( *(_DWORD *)(uintptr_t)(i + 24) )
    {
      nameString = Rules_GetConstructNameString(i);
      Deffunction_ReportCantDelete(nameString, v4);
      clearSuccess = 0;
    }
    else
    {
      AST_DeinstallNodeChain(*(__int16 **)(uintptr_t)(i + 30));
      v15 = *(_DWORD *)(uintptr_t)(v14 + 30);
      *(_DWORD *)(uintptr_t)(v14 + 20) = v16;
      AST_FreePackedNodeChain(v15);
      *(_DWORD *)(uintptr_t)(v5 + 30) = 0;
    }
  }
  theDeffunction = Class_Enum(0, g_Clips_DeffunctionModuleItemIndex);
  if ( !theDeffunction )
    return clearSuccess;
  do
  {
    while ( 1 )
    {
      theDeffunction = Class_Enum(theDeffunction, g_Clips_DeffunctionModuleItemIndex);
      if ( !*(_DWORD *)(uintptr_t)(v7 + 24) )
        break;
LABEL_11:
      if ( !theDeffunction )
        return clearSuccess;
    }
    if ( *(_DWORD *)(uintptr_t)(v7 + 20) )
    {
      Rules_PrintWarningID((int)(intptr_t)aDffnxfun, 1, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aDeffunction_6, v8);
      v10 = Rules_GetConstructNameString(v9);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], v10, v11);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aOnlyPartiallyD, v12);
      clearSuccess = 0;
      Rules_ReplaceConstructPPForm(v13, 0);
      goto LABEL_11;
    }
    Rules_UnlinkListNode(v7);
    Deffunction_Free(v17);
  }
  while ( theDeffunction );
  return clearSuccess;
}
// 498DFB: variable 'v4' is possibly undefined
// 498E0A: variable 'v5' is possibly undefined
// 498E3B: variable 'v7' is possibly undefined
// 498E69: variable 'v8' is possibly undefined
// 498E70: variable 'v9' is possibly undefined
// 498E7F: variable 'v11' is possibly undefined
// 498E8E: variable 'v12' is possibly undefined
// 498E99: variable 'v13' is possibly undefined
// 498EB5: variable 'v14' is possibly undefined
// 498EB8: variable 'v16' is possibly undefined
// 498ED5: variable 'v17' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498EF0) --------------------------------------------------------
signed int  Deffunction_ReportCantDelete(int deffunctionName, int a2)
{
  return Rules_ReportCantDeleteItem(a2, deffunctionName);
}

//----- (00498F00) --------------------------------------------------------
signed int Deffunction_SaveHeaders(void)
{
  return Rules_DoForAllConstructs((void (*)(void))Deffunction_WriteHeaderForm, 0);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (00498F20) --------------------------------------------------------
int  Deffunction_WriteHeaderForm(int theDeffunction, int logicalName)
{
  int result; // eax
  int v6; // ecx
  int nameString; // eax
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int i; // ebx
  int v12; // ecx

  result = Rules_GetModuleConstructListHead(theDeffunction);
  if ( result )
  {
    Output_Write(logicalName, (int)(intptr_t)aDeffunction_1, v6);
    nameString = Rules_GetConstructNameString(theDeffunction);
    Output_Write(logicalName, nameString, v8);
    Output_Write(logicalName, (int)(intptr_t)asc_5055B4, v9);
    for ( i = 0; i < *(_DWORD *)(uintptr_t)(theDeffunction + 34); ++i )
    {
      Output_Write(v10, (int)(intptr_t)aQuestionP_DeffunctionArgumentPrefix, v10);
      Rules_PrintLongInteger(v12, i);
      if ( i != *(_DWORD *)(uintptr_t)(theDeffunction + 34) - 1 )
        Output_Write(v10, (int)(intptr_t)asc_5055BC, v10);
    }
    if ( *(_DWORD *)(uintptr_t)(theDeffunction + 38) == -1 )
    {
      if ( *(_DWORD *)(uintptr_t)(theDeffunction + 34) )
        Output_Write(v10, (int)(intptr_t)asc_5055BC, v10);
      return Output_Write(v10, (int)(intptr_t)a_wildargs, v10);
    }
    else
    {
      return Output_Write(v10, (int)(intptr_t)asc_5055D0, v10);
    }
  }
  return result;
}
// 498F41: variable 'v6' is possibly undefined
// 498F51: variable 'v8' is possibly undefined
// 498F5D: variable 'v9' is possibly undefined
// 498F72: variable 'v10' is possibly undefined
// 498F7B: variable 'v12' is possibly undefined

//----- (00498FE0) --------------------------------------------------------
int  Deffunction_SaveBodies(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDeffunctionConstructType);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00498FF0) --------------------------------------------------------
signed int  Deffunction_SetWatchAll(int newState, int argExprs, double context)
{
  return Rules_ApplyWatchFlagCommand(g_ClipsDeffunctionConstructType, newState, (int)(intptr_t)Deffunction_GetWatchFlagField, argExprs, context, (void (*)(void))Deffunction_SetWatchFlagField);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00499010) --------------------------------------------------------
signed int  Deffunction_GetWatchAll(int logicalName, int argExprs, double context)
{
  return Rules_ListWatchFlagStatus(g_ClipsDeffunctionConstructType, logicalName, (int)(intptr_t)Deffunction_GetWatchFlagField, argExprs, context, (void (*)(void))Deffunction_SetWatchFlagField);
}
// 54E6AC: using guessed type int dword_54E6AC;

//----- (00499030) --------------------------------------------------------
__int16  Deffunction_SetWatchFlagField(__int16 result, int theDeffunction)
{
  *(_WORD *)(uintptr_t)(theDeffunction + 28) = result;
  return result;
}

//----- (00499040) --------------------------------------------------------
int  Deffunction_GetWatchFlagField(int theDeffunction)
{
  return *(unsigned __int16 *)(uintptr_t)(theDeffunction + 28);
}

//----- (00499050) --------------------------------------------------------
_DWORD *Defglobal_InitConstructType(void)
{
  _DWORD *result; // eax

  g_CLIPS_DefglobalEvalNodeDescriptor[4] = (int)(uintptr_t)Defglobal_EvaluateReference;
  g_Defglobal_PtrEntityRecord[4] = (int)(uintptr_t)Mem_CopyDataObjectRecord;
  g_Defglobal_PtrEntityRecord[6] = (int)(uintptr_t)Class_DecrementBusyCount;
  g_Defglobal_PtrEntityRecord[7] = (int)(uintptr_t)Class_IncrementBusyCount;
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_CLIPS_DefglobalEvalNodeDescriptor, 13);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_Defglobal_PtrEntityRecord, 60);
  Defglobal_RegisterModuleItem();
  Defglobal_RegisterConstructCommands();
  Defglobal_RegisterResetGlobalsCommands();
  result = Rules_RegisterConstructType(
             (int)(intptr_t)aDefglobal,
             (int)(intptr_t)aDefglobals,
             (int)(intptr_t)Defglobal_FindByName,
             (int)(intptr_t)Defglobal_ParseDefglobalConstruct,
             (int)(intptr_t)Rules_GetConstructNameSymbol,
             (int)(intptr_t)Rules_GetModuleConstructListHead,
             (int)(intptr_t)Rules_GetConstructOwnerModule,
             (int)(intptr_t)Defglobal_EnumNext,
             (int)(intptr_t)Rules_SetConstructNextInModule,
             (int)(intptr_t)Defglobal_IsDeletable,
             (int)(intptr_t)Defglobal_DeleteConstructOrAll,
             (int)(intptr_t)Defglobal_Free);
  g_ClipsDefglobalConstructType = (int)(intptr_t)result;
  return result;
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004990D0) --------------------------------------------------------
int *Defglobal_RegisterModuleItem(void)
{
  g_ClipsDefglobalModuleItemId = Module_RegisterItem(
                   (int)(intptr_t)aDefglobal,
                   (int)(intptr_t)Defglobal_AllocateModule,
                   (int)(intptr_t)Rules_GetDefglobalModulePointer,
                   (int)(intptr_t)Defglobal_FreeModule,
                   (int)(intptr_t)Defglobal_WriteModuleItemHeaderReference,
                   (int)(intptr_t)Defglobal_FindByName);
  return Module_RegisterImportExportConstructType((int)(intptr_t)aDefglobal, 2);
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (00499110) --------------------------------------------------------
signed int Defglobal_AllocateModule(void)
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499140) --------------------------------------------------------
int  Defglobal_FreeModule(int theModuleItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theModuleItem, g_ClipsDefglobalConstructType, theModuleItem);
  freed_node = (_DWORD *)(uintptr_t)theModuleItem;
  g_ClipsMemFreeListTemp = theModuleItem;
  *freed_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6B4: using guessed type int dword_54E6B4;

//----- (00499190) --------------------------------------------------------
int  Defglobal_FindByName(_BYTE *defglobalName, int a2)
{
  return Rules_FindConstructByNameGeneric(defglobalName, a2);
}
// 54E6B4: using guessed type int dword_54E6B4;

//----- (004991A0) --------------------------------------------------------
int  Defglobal_EnumNext(int defglobalPtr)
{
  return Class_Enum(defglobalPtr, g_ClipsDefglobalModuleItemId);
}
// 54E6B0: using guessed type int dword_54E6B0;

//----- (004991B0) --------------------------------------------------------
BOOL Defglobal_IsDeletable(void)
{
  int v0; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(uintptr_t)(v0 + 24) == 0;
}
// 4991BC: variable 'v0' is possibly undefined

//----- (004991D0) --------------------------------------------------------
int  Defglobal_Free(int result)
{
  int v1; // edx
  int v2; // ecx
  int *v3; // ecx
  _DWORD *v4; // ecx

  if ( result )
  {
    Rules_ValueDeinstall(result + 28, result);
    if ( *(_DWORD *)(uintptr_t)(v1 + 32) == 4 )
      Rules_ReturnMultifieldToPool(*(_DWORD **)(uintptr_t)(v1 + 36));
    AST_RemoveHashedNodeChain(*(__int16 **)(uintptr_t)(v2 + 52), v2);
    Rules_FreeConstructHeaderString(v3, (int)(intptr_t)v3);
    g_ClipsMemFreeListTemp = (int)(intptr_t)v4;
    *v4 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 224);
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 224) = g_ClipsMemFreeListTemp;
    g_Defglobal_ChangedFlag = 1;
  }
  return result;
}
// 4991E5: variable 'v1' is possibly undefined
// 4991F4: variable 'v2' is possibly undefined
// 4991FE: variable 'v3' is possibly undefined
// 499208: variable 'v4' is possibly undefined
// 51AB1C: using guessed type int dword_51AB1C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499240) --------------------------------------------------------
int  Defglobal_SetValue(int theGlobal, _DWORD *vPtr, int resetVar, double context)
{
  int record; // ecx
  int new_type; // eax
  int result; // eax

  record = theGlobal;
  if ( resetVar )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theGlobal + 52), vPtr, theGlobal, context);
    if ( g_ClipsEvaluationError )
    {
      vPtr[1] = 2;
      vPtr[2] = g_ClipsFalseSymbol;
    }
  }
  if ( (*(_BYTE *)(uintptr_t)(record + 20) & 1) != 0 )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aDefglobalWatchPrefix, record);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)record + 16), record);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_5055F8, record);
    Rules_PrintDataObject((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)vPtr);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_505600, record);
    Rules_PrintDataObject((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], record + 28);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_505608, record);
  }
  Rules_ValueDeinstall(record + 28, record);
  if ( *(_DWORD *)(uintptr_t)(record + 32) == 4 )
    Rules_ReturnMultifieldToPool((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(record + 36));
  new_type = vPtr[1];
  *(_DWORD *)(uintptr_t)(record + 32) = new_type;
  if ( new_type == 4 )
    Rules_AssignMultifieldRangeCopy((_DWORD *)(uintptr_t)(record + 28), (int)(intptr_t)vPtr);
  else
    *(_DWORD *)(uintptr_t)(record + 36) = vPtr[2];
  Rules_ValueInstall(record + 28, record);
  result = g_ClipsCurrentEvaluationDepth;
  g_Defglobal_ChangedFlag = 1;
  if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
    return Rules_RunPeriodicCleanup(1, 0);
  return result;
}
// 51A618: using guessed type char *off_51A618[4];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51AB1C: using guessed type int dword_51AB1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (00499360) --------------------------------------------------------
_DWORD *Defglobal_FindNextChanged(void)
{
  _DWORD *result; // eax
  int v1; // ecx

  result = (_DWORD *)(uintptr_t)Class_Enum(0, g_ClipsDefglobalModuleItemId);
  if ( !result )
    return 0;
  while ( v1 != *result )
  {
    result = (_DWORD *)(uintptr_t)Class_Enum((int)(intptr_t)result, g_ClipsDefglobalModuleItemId);
    if ( !result )
      return 0;
  }
  return result;
}
// 499377: variable 'v1' is possibly undefined
// 54E6B0: using guessed type int dword_54E6B0;

//----- (00499410) --------------------------------------------------------
signed int  Defglobal_EvaluateReference(int theValue, _DWORD *returnValue, int a3)
{
  _DWORD *theGlobal; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD countBuf[5]; // [esp+0h] [ebp-14h] BYREF

  countBuf[3] = a3;
  theGlobal = (_DWORD *)(uintptr_t)Rules_FindImportExportConstruct(aDefglobal, countBuf, *(_BYTE **)(uintptr_t)(theValue + 16), 1, 0);
  if ( !theGlobal )
  {
    Rules_PrintErrorID((int)(intptr_t)aGlobldef, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aGlobalVariab_0, v7);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(theValue + 16), v8);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsUnbound_, v9);
    goto LABEL_4;
  }
  if ( countBuf[0] > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)(intptr_t)aDefglobal, *(_DWORD *)(uintptr_t)(theValue + 16));
LABEL_4:
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    Lexer_ErrorRecover(1);
    return 0;
  }
  Mem_CopyDataObjectRecord(theGlobal, returnValue);
  return 1;
}
// 499487: variable 'v7' is possibly undefined
// 499494: variable 'v8' is possibly undefined
// 4994A3: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (004994C0) --------------------------------------------------------
signed int  Mem_CopyDataObjectRecord(_DWORD *src, _DWORD *dst)
{
  int fieldCount; // eax
  int valueType; // ebx
  _DWORD *newMultifield; // eax
  int v6; // edx
  int copyLength; // ebx
  int v8; // ecx

  dst[1] = src[8];
  dst[2] = src[9];
  dst[3] = src[10];
  fieldCount = src[11];
  valueType = dst[1];
  dst[4] = fieldCount;
  if ( valueType == 4 )
  {
    newMultifield = Rules_CreateEphemeralMultifield(fieldCount + 1);
    copyLength = *(_DWORD *)(uintptr_t)(v6 + 16) + 1;
    *(_DWORD *)(uintptr_t)(v6 + 8) = newMultifield;
    qmemcpy(
      (void *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v6 + 8) + 14),
      (const void *)(uintptr_t)(6 * *(_DWORD *)(uintptr_t)(v8 + 40) + *(_DWORD *)(uintptr_t)(v8 + 36) + 14),
      6 * copyLength);
  }
  return 1;
}
// 4994F4: variable 'v6' is possibly undefined
// 499507: variable 'v8' is possibly undefined

//----- (00499590) --------------------------------------------------------
int  Class_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(uintptr_t)(result + 24);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (004995A0) --------------------------------------------------------
int  Class_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(uintptr_t)(result + 24);
  return result;
}

//----- (004995B0) --------------------------------------------------------
int Class_RefreshWatchFlags(void)
{
  int result; // eax
  int i; // edi
  _BYTE *j; // esi
  _DWORD countBuf[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    for ( j = *(_BYTE **)(uintptr_t)(Module_GetItem(i, g_ClipsDefglobalModuleItemId) + 4); j; j = (_BYTE *)(uintptr_t)Class_Enum((int)(intptr_t)j, g_ClipsDefglobalModuleItemId) )
    {
      if ( Rules_FindImportExportConstruct(aDefglobal, countBuf, *(_BYTE **)(uintptr_t)(*(_DWORD *)j + 16), 1, 0) )
        j[20] |= 2u;
      else
        j[20] &= ~2u;
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 54E6B0: using guessed type int dword_54E6B0;
