/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0048ED60) --------------------------------------------------------
int  Rules_ReleaseLogicalSupportList(int result)
{
  uintptr_t fact; // edi
  uintptr_t support; // ebx
  int last; // eax

  fact = (uintptr_t)(unsigned int)result;
  support = fact ? (uintptr_t)(unsigned int)*(_DWORD *)(fact + 4) : 0;
  last = result;
  while ( support )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(support + 4);
    uintptr_t match = (uintptr_t)(unsigned int)*(_DWORD *)support;
    if ( match )
    {
      unsigned int slot_index = ((*(_DWORD *)match << 17) >> 23) + ((*(_DWORD *)match << 29) >> 31);
      _DWORD *head = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(match + 4 * slot_index + 8);
      _DWORD *new_head = Rules_RemoveDependencyLink(head, (int)fact);
      *(_DWORD *)(match + 4 * slot_index + 8) = (int)(uintptr_t)new_head;
    }
    g_ClipsMemFreeListTemp = (int)support;
    *(_DWORD *)support = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
    last = g_ClipsMemFreeListTemp;
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    support = next;
  }
  if ( fact )
    *(_DWORD *)(fact + 4) = 0;
  return last;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EDE0) --------------------------------------------------------
_DWORD * Rules_RemoveDependencyLink(_DWORD *theList, int theEntity)
{
  uintptr_t head; // esi
  uintptr_t current; // eax
  uintptr_t previous; // ecx

  head = (uintptr_t)(unsigned int)(uintptr_t)theList;
  current = head;
  previous = 0;
  while ( current )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
    if ( theEntity == *(_DWORD *)current )
    {
      if ( previous )
        *(_DWORD *)(previous + 4) = (int)next;
      else
        head = next;
      g_ClipsMemFreeListTemp = (int)current;
      *(_DWORD *)current = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      current = next;
    }
    else
    {
      previous = current;
      current = next;
    }
  }
  return (_DWORD *)(uintptr_t)(unsigned int)head;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EE40) --------------------------------------------------------
int  Rules_RemoveEntityDependencies(_DWORD *theBinds)
{
  _DWORD *dependencyPtr; // ecx
  int theBind; // ebx
  _DWORD *nextDependency; // esi
  _DWORD *v5; // ecx
  int result; // eax

  dependencyPtr = (_DWORD *)(uintptr_t)theBinds[(*theBinds << 29 >> 31) + 2 + (*theBinds << 17 >> 23)];
  if ( dependencyPtr )
  {
    do
    {
      theBind = *dependencyPtr;
      nextDependency = (_DWORD *)(uintptr_t)dependencyPtr[1];
      *(_DWORD *)(uintptr_t)(theBind + 4) = Rules_RemoveDependencyLink((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*dependencyPtr + 4), (int)(intptr_t)theBinds);
      g_ClipsMemFreeListTemp = (int)(intptr_t)v5;
      *v5 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      dependencyPtr = nextDependency;
    }
    while ( nextDependency );
  }
  result = (*theBinds << 17 >> 23) + (*theBinds << 29 >> 31);
  theBinds[result + 2] = 0;
  return result;
}
// 48EE78: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EEC0) --------------------------------------------------------
int  Rules_RemovePMDependencies(int result)
{
  _DWORD *theBinds; // edi
  _DWORD *dependencyPtr; // ecx
  int theBind; // ebx
  _DWORD *nextDependency; // esi
  _DWORD *updatedList; // eax
  _DWORD *v6; // ecx

  theBinds = (_DWORD *)(uintptr_t)result;
  if ( (*(_BYTE *)(uintptr_t)result & 8) != 0 )
  {
    dependencyPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(result + 4 * ((*(_DWORD *)(uintptr_t)result << 17 >> 23) + (*(_DWORD *)(uintptr_t)result << 29 >> 31)) + 8);
    if ( dependencyPtr )
    {
      do
      {
        theBind = *dependencyPtr;
        nextDependency = (_DWORD *)(uintptr_t)dependencyPtr[1];
        updatedList = Rules_RemoveDependencyLink((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*dependencyPtr + 4), (int)(intptr_t)theBinds);
        *(_DWORD *)(uintptr_t)(theBind + 4) = updatedList;
        if ( updatedList )
        {
          g_ClipsMemFreeListTemp = (int)(intptr_t)v6;
          *v6 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        }
        else
        {
          v6[1] = g_ClipsPendingDependencyDestructorList;
          g_ClipsPendingDependencyDestructorList = (int)(intptr_t)v6;
        }
        dependencyPtr = nextDependency;
      }
      while ( nextDependency );
    }
    result = (*theBinds << 17 >> 23) + (*theBinds << 29 >> 31);
    theBinds[result + 2] = 0;
  }
  return result;
}
// 48EF05: variable 'v6' is possibly undefined
// 51A958: using guessed type int dword_51A958;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EF60) --------------------------------------------------------
void Rules_FlushPendingDependencyDestructors(void)
{
  _DWORD *dependencyPtr; // eax
  int theEntity; // edx

  if ( !g_Rules_FlushingDependencyDestructors )
  {
    g_Rules_FlushingDependencyDestructors = 1;
    while ( g_ClipsPendingDependencyDestructorList )
    {
      dependencyPtr = (_DWORD *)(uintptr_t)g_ClipsPendingDependencyDestructorList;
      theEntity = *(_DWORD *)(uintptr_t)g_ClipsPendingDependencyDestructorList;
      g_ClipsPendingDependencyDestructorList = *(_DWORD *)(uintptr_t)(g_ClipsPendingDependencyDestructorList + 4);
      g_ClipsMemFreeListTemp = (int)(intptr_t)dependencyPtr;
      *dependencyPtr = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)theEntity + 12))();
    }
    g_Rules_FlushingDependencyDestructors = 0;
  }
}
// 51A958: using guessed type int dword_51A958;
// 51A95C: using guessed type int dword_51A95C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EFD0) --------------------------------------------------------
signed int  Rules_PrintDependencyList(signed int result, int a2)
{
  _DWORD **dependencyPtr; // ecx
  int v3; // ecx
  signed int v4; // eax
  int v5; // ecx

  if ( !*(_DWORD *)(uintptr_t)(result + 4) )
    return Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aNone, a2);
  dependencyPtr = *(_DWORD ***)(uintptr_t)(result + 4);
  do
  {
    Rules_PrintArgumentValueList((int)(intptr_t)g_IO_LogicalName_WDisplay, *dependencyPtr);
    v4 = Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_504880, v3);
    dependencyPtr = *(_DWORD ***)(uintptr_t)(v5 + 4);
  }
  while ( dependencyPtr );
  return v4;
}
// 48EFDB: conditional instruction was optimized away because edx.4!=0
// 48EFF3: variable 'v3' is possibly undefined
// 48EFF8: variable 'v5' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0048F020) --------------------------------------------------------
signed int  Rules_PrintDependentList(int theEntity, int a2)
{
  int v4; // ecx
  int found; // esi
  _DWORD **dependencyPtr; // ecx
  int v7; // ecx
  _DWORD *entityPtr; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD traversalBuffer[6]; // [esp+4h] [ebp-18h] BYREF

  traversalBuffer[4] = a2;
  entityPtr = 0;
  traversalBuffer[0] = 0;
  Rules_FindPatternParser(traversalBuffer, &entityPtr);
  found = 0;
  while ( entityPtr )
  {
    dependencyPtr = (_DWORD **)(uintptr_t)entityPtr[1];
    if ( dependencyPtr )
    {
      while ( Rules_ArrayContainsValue(theEntity, *dependencyPtr) != 1 )
      {
        dependencyPtr = *(_DWORD ***)(uintptr_t)(v7 + 4);
        if ( !dependencyPtr )
          goto LABEL_7;
      }
      if ( found )
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_504884, v7);
      found = 1;
      (*(void (**)(void))(uintptr_t)(*entityPtr + 4))();
    }
LABEL_7:
    Rules_FindPatternParser(traversalBuffer, &entityPtr);
  }
  if ( found )
    return Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_504880, v4);
  else
    return Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aNone, v4);
}
// 48F06D: variable 'v7' is possibly undefined
// 48F0A6: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0048F0E0) --------------------------------------------------------
signed int  Rules_ArrayContainsValue(int theEntity, _DWORD *theMatch)
{
  __int16 i; // ax

  for ( i = 0; i < *theMatch << 17 >> 23; ++i )
  {
    if ( theEntity == *(_DWORD *)(uintptr_t)theMatch[i + 2] )
      return 1;
  }
  return 0;
}

//----- (0048F120) --------------------------------------------------------
_DWORD * Rules_Dependencies(double a1)
{
  _DWORD *result; // eax
  int v2; // ecx
  int v3; // ecx
  int itemBuffer; // [esp-1Ch] [ebp-20h] BYREF

  result = (_DWORD *)(uintptr_t)Lexer_TokenExpect((int)(intptr_t)aDependencies_0, 0, 1);
  if ( result != (_DWORD *)-1 )
  {
    result = Rules_ResolveFactOrInstanceArg(&itemBuffer, aDependencies_0, v2, a1);
    if ( result )
      return (_DWORD *)(uintptr_t)Rules_PrintDependencyList((signed int)(intptr_t)result, v3);
  }
  return result;
}
// 48F148: variable 'v2' is possibly undefined
// 48F151: variable 'v3' is possibly undefined

//----- (0048F160) --------------------------------------------------------
_DWORD * Rules_Dependents(double a1)
{
  _DWORD *result; // eax
  int v2; // ecx
  int v3; // ecx
  int itemBuffer; // [esp-1Ch] [ebp-20h] BYREF

  result = (_DWORD *)(uintptr_t)Lexer_TokenExpect((int)(intptr_t)aDependents_0, 0, 1);
  if ( result != (_DWORD *)-1 )
  {
    result = Rules_ResolveFactOrInstanceArg(&itemBuffer, aDependents_0, v2, a1);
    if ( result )
      return (_DWORD *)(uintptr_t)Rules_PrintDependentList((int)(intptr_t)result, v3);
  }
  return result;
}
// 48F188: variable 'v2' is possibly undefined
// 48F191: variable 'v3' is possibly undefined

//----- (0048F1A0) --------------------------------------------------------
_DWORD * Rules_ResolveFactOrInstanceArg(_DWORD *item, _BYTE *functionName, int a3, double a4)
{
  int v5; // ecx
  int theType; // edx
  int v7; // ecx
  _DWORD *foundEntity; // ebx
  _BYTE *itemName; // edx
  int v11; // ecx
  _BYTE numberBuffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v13 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v13 = a3;
  Rules_RtnUnknown(1, item, a4);
  theType = *(_DWORD *)(uintptr_t)(v5 + 4);
  if ( theType == 6 || theType == 7 )
    return (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 8);
  if ( theType == 1 )
  {
    foundEntity = (_DWORD *)(uintptr_t)Rules_FindFactByIndex(*(int *)((uintptr_t)(unsigned int)item[2] + 16));
    if ( foundEntity )
      return foundEntity;
    sprintf_(numberBuffer, "f-%ld", *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v11 + 8) + 16));
    itemName = numberBuffer;
    goto LABEL_8;
  }
  if ( theType != 8 && theType != 2 )
  {
    Rules_ReportSymbolTypeError(functionName, 1);
    return 0;
  }
  foundEntity = Instance_FindByName(*(_DWORD *)(uintptr_t)(v5 + 8));
  if ( !foundEntity )
  {
    itemName = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v7 + 8) + 16);
LABEL_8:
    Rules_ReportCantFindItem(v7, (int)(intptr_t)itemName);
  }
  return foundEntity;
}
// 48F1B5: variable 'v5' is possibly undefined
// 48F1DF: variable 'v7' is possibly undefined
// 48F20D: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (0048F300) --------------------------------------------------------
int  Parser_ParseForm(__int16 *problem, _DWORD *returnValue, int a3, double a4)
{
  _DWORD *valuePtr; // ecx
  int theType; // eax
  int result; // eax
  int oldArgument; // ebx
  int theFunction; // edx
  void *theValue; // eax
  int v11 CLASH95_UNUSED; // ecx
  int *longResult; // eax
  int v13 CLASH95_UNUSED; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17 CLASH95_UNUSED; // ecx
  int entityRecord; // edx
  int savedExpression; // edi
  int v20 CLASH95_UNUSED; // ecx
  uintptr_t function_ptr;
  uintptr_t evaluator;
  double doubleResult; // [esp+0h] [ebp-18h]
  char charBuffer[8]; // [esp+Ch] [ebp-Ch] BYREF
  int v23 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

  v23 = a3;
  valuePtr = returnValue;
  if ( problem )
  {
    switch ( *problem )
    {
      case 0:
      case 1:
      case 2:
      case 3:
      case 5:
      case 7:
      case 8:
        theType = *problem;
        goto LABEL_4;
      case 4:
        returnValue[1] = 4;
        returnValue[2] = *(_DWORD *)(uintptr_t)(*(_DWORD *)(problem + 1) + 8);
        returnValue[3] = *(_DWORD *)(uintptr_t)(*(_DWORD *)(problem + 1) + 12);
        returnValue[4] = *(_DWORD *)(uintptr_t)(*(_DWORD *)(problem + 1) + 16);
        Rules_PropagateReturnValueDepth((uintptr_t)returnValue);
        return g_ClipsEvaluationError;
      case 10:
        oldArgument = g_ClipsCurrentExpression;
        g_ClipsCurrentExpression = (int)(intptr_t)problem;
        theFunction = *(_DWORD *)(problem + 1);
        function_ptr = (uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theFunction + 9);
        switch ( *(_BYTE *)(uintptr_t)(theFunction + 8) )
        {
          case 'a':
            valuePtr[1] = 5;
            goto LABEL_9;
          case 'b':
            valuePtr[1] = 2;
            if ( !((int (*)(void))function_ptr)() )
              goto LABEL_13;
            theValue = (void *)(uintptr_t)g_ClipsTrueSymbol;
            goto LABEL_10;
          case 'c':
            charBuffer[0] = ((int (*)(_DWORD *))function_ptr)(valuePtr);
            charBuffer[1] = 0;
            valuePtr[1] = 2;
            theValue = Str_Intern(charBuffer, 0);
            goto LABEL_10;
          case 'd':
          case 'f':
            valuePtr[1] = 0;
            doubleResult = ((double (*)(void))function_ptr)();
            theValue = (void *)(uintptr_t)Rules_AddDoubleValue(doubleResult);
            goto LABEL_10;
          case 'i':
          case 'l':
            valuePtr[1] = 1;
            longResult = (int *)((uintptr_t)(unsigned int)((int (*)(void))function_ptr)());
            theValue = Rules_AddIntegerValue(longResult);
            goto LABEL_10;
          case 'j':
          case 'k':
          case 'm':
          case 'n':
          case 'u':
            ((void (*)(uintptr_t, uintptr_t, double))function_ptr)((uintptr_t)valuePtr, (uintptr_t)valuePtr, a4);
            break;
          case 'o':
            valuePtr[1] = 8;
            goto LABEL_9;
          case 's':
            valuePtr[1] = 3;
            goto LABEL_9;
          case 'v':
            ((void (*)(void))function_ptr)();
            valuePtr[1] = 105;
LABEL_13:
            theValue = (void *)(uintptr_t)g_ClipsFalseSymbol;
            goto LABEL_10;
          case 'w':
            valuePtr[1] = 2;
            goto LABEL_9;
          case 'x':
            valuePtr[1] = 7;
LABEL_9:
            theValue = (void *)(uintptr_t)(unsigned int)((int (*)(void))function_ptr)();
LABEL_10:
            valuePtr[2] = (int)(uintptr_t)theValue;
            break;
          default:
            Rules_ReportSystemError((int)(intptr_t)valuePtr, 2);
            IO_RunRouterExitCallbacks(5);
            break;
        }
        g_ClipsCurrentExpression = oldArgument;
        Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
        return g_ClipsEvaluationError;
      case 15:
      case 16:
        if ( Rules_FindBoundVariable(returnValue, *(_DWORD *)(problem + 1)) )
          goto LABEL_5;
        Rules_PrintErrorID((int)(intptr_t)aEvaluatn, 1, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aVariable, v14);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(problem + 1) + 16), v15);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIsUnbound, v16);
        valuePtr[1] = 2;
        valuePtr[2] = g_ClipsFalseSymbol;
        g_ClipsEvaluationError = 1;
        g_ClipsHaltExecution = 1;
        Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
        result = g_ClipsEvaluationError;
        break;
      default:
        if ( !g_Clips_PrimitiveEntityTable[*problem] )
        {
          Rules_ReportSystemError((int)(intptr_t)returnValue, 3);
          IO_RunRouterExitCallbacks(5);
        }
        theType = *problem;
        entityRecord = g_Clips_PrimitiveEntityTable[theType];
        if ( (*(_BYTE *)(uintptr_t)(entityRecord + 1) & 0x20) != 0 )
        {
LABEL_4:
          valuePtr[1] = theType;
          valuePtr[2] = *(_DWORD *)(problem + 1);
LABEL_5:
          Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
          result = g_ClipsEvaluationError;
        }
        else
        {
          if ( !*(_DWORD *)(uintptr_t)(entityRecord + 16) )
          {
            Rules_ReportSystemError((int)(intptr_t)valuePtr, 4);
            IO_RunRouterExitCallbacks(5);
          }
          savedExpression = g_ClipsCurrentExpression;
          g_ClipsCurrentExpression = (int)(intptr_t)problem;
          evaluator = (uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(g_Clips_PrimitiveEntityTable[*problem] + 16);
          ((void (*)(int, _DWORD *, double))evaluator)(*(_DWORD *)(problem + 1), valuePtr, a4);
          g_ClipsCurrentExpression = savedExpression;
          Rules_PropagateReturnValueDepth((uintptr_t)valuePtr);
          result = g_ClipsEvaluationError;
        }
        break;
    }
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return g_ClipsEvaluationError;
  }
  return result;
}
// 48F3F2: inconsistent fpu stack
// 48F32A: variable 'v5' is possibly undefined
// 48F392: variable 'v11' is possibly undefined
// 48F437: variable 'v13' is possibly undefined
// 48F4D2: variable 'v14' is possibly undefined
// 48F4E2: variable 'v15' is possibly undefined
// 48F4F1: variable 'v16' is possibly undefined
// 48F4F6: variable 'v17' is possibly undefined
// 48F5AA: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F5C0) --------------------------------------------------------
int  Rules_RegisterEvaluationHandler(int result, int whichPosition)
{
  int thePrimitive; // ebx
  int v3; // ecx

  thePrimitive = result;
  if ( g_Clips_PrimitiveEntityTable[whichPosition] )
  {
    Rules_ReportSystemError(whichPosition, 5);
    result = IO_RunRouterExitCallbacks();
    g_Clips_PrimitiveEntityTable[v3] = thePrimitive;
  }
  else
  {
    g_Clips_PrimitiveEntityTable[whichPosition] = result;
  }
  return result;
}
// 48F5F3: variable 'v3' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F600) --------------------------------------------------------
int  Lexer_ErrorRecover(int result)
{
  g_ClipsEvaluationError = result;
  if ( result == 1 )
    return Rules_SetEvaluationErrorFlag(1);
  return result;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048F610) --------------------------------------------------------
int  Rules_SetEvaluationErrorFlag(int result)
{
  g_ClipsHaltExecution = result;
  return result;
}
// 51A968: using guessed type int dword_51A968;

//----- (0048F620) --------------------------------------------------------
int Rules_GetHaltExecutionFlag(void)
{
  return g_ClipsEvaluationError;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048F630) --------------------------------------------------------
int Rules_GetEvaluationErrorFlag(void)
{
  return g_ClipsHaltExecution;
}
// 51A968: using guessed type int dword_51A968;

//----- (0048F640) --------------------------------------------------------
int  Rules_DeinstallValueChain(int result)
{
  int currentValue; // edx
  _DWORD *v2; // edx
  int v3; // ecx

  currentValue = result;
  if ( result )
  {
    do
    {
      Rules_ValueDeinstall(currentValue, *(_DWORD *)(uintptr_t)(currentValue + 20));
      g_ClipsMemFreeListTemp = (int)(intptr_t)v2;
      *v2 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
      currentValue = v3;
    }
    while ( v3 );
  }
  return result;
}
// 48F657: variable 'v2' is possibly undefined
// 48F670: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048F690) --------------------------------------------------------
signed int  Rules_PrintDataObject(int logicalName, int argPtr)
{
  unsigned int theType; // eax
  signed int result; // eax
  int v5; // ecx
  int v6; // ecx

  theType = *(_DWORD *)(uintptr_t)(argPtr + 4);
  if ( theType < 4 )
    return Rules_PrintAtomValue(logicalName, *(_DWORD *)(uintptr_t)(argPtr + 4), (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(argPtr + 8));
  if ( theType <= 4 )
    return Lexer_OutputFieldRange(logicalName, *(_DWORD *)(uintptr_t)(argPtr + 8), *(_DWORD *)(uintptr_t)(argPtr + 16), *(_DWORD *)(uintptr_t)(argPtr + 12), 1);
  if ( theType <= 8 || theType == 105 )
    return Rules_PrintAtomValue(logicalName, *(_DWORD *)(uintptr_t)(argPtr + 4), (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(argPtr + 8));
  Output_Write(logicalName, (int)(intptr_t)aUnknownprintty, argPtr);
  Rules_PrintLongInteger(v5, *(_DWORD *)(uintptr_t)(v5 + 4));
  result = Output_Write(logicalName, (int)(intptr_t)asc_5048FC, v6);
  g_ClipsEvaluationError = 1;
  g_ClipsHaltExecution = 1;
  return result;
}
// 48F6BE: simplified comparisons for 'eax.4': <7u || <8u became <8u
// 48F6BE: simplified comparisons for 'eax.4': <8u || <9u became <9u
// 48F6DD: variable 'v5' is possibly undefined
// 48F6E9: variable 'v6' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;

//----- (0048F720) --------------------------------------------------------
_DWORD * Rules_SetMultifieldErrorValue(int returnValue)
{
  _DWORD *result; // eax
  _DWORD *v2; // edx

  *(_DWORD *)(uintptr_t)(returnValue + 4) = 4;
  result = Rules_CreateEphemeralMultifield(0);
  v2[3] = 1;
  v2[4] = 0;
  v2[2] = result;
  return result;
}
// 48F731: variable 'v2' is possibly undefined

//----- (0048F750) --------------------------------------------------------
__int16 * Rules_ValueInstall(int vPtr, int a2)
{
  if ( *(_DWORD *)(uintptr_t)(vPtr + 4) == 4 )
    return Rules_InstallMultifield((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(vPtr + 8));
  else
    return (__int16 *)(uintptr_t)Rules_AtomInstall(*(_DWORD *)(uintptr_t)(vPtr + 4), *(_DWORD *)(uintptr_t)(vPtr + 8), a2);
}

//----- (0048F770) --------------------------------------------------------
__int16 * Rules_ValueDeinstall(int vPtr, int a2)
{
  if ( *(_DWORD *)(uintptr_t)(vPtr + 4) == 4 )
    return Rules_DeinstallMultifield((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(vPtr + 8));
  else
    return (__int16 *)(uintptr_t)Rules_AtomDeinstall(*(_DWORD *)(uintptr_t)(vPtr + 4), (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(vPtr + 8), a2);
}

//----- (0048F790) --------------------------------------------------------
unsigned int  Rules_AtomInstall(unsigned int result, int vPtr, int a3)
{
  int entityRecord; // esi

  if ( result < 4 )
    goto LABEL_15;
  if ( result >= 8 )
  {
    if ( result <= 8 )
      goto LABEL_15;
    if ( result >= 0xD )
    {
      if ( result <= 0xD )
        goto LABEL_15;
      if ( result == 105 )
        return result;
    }
  }
  else if ( result == 4 )
  {
    return (unsigned int)(intptr_t)Rules_InstallMultifield((__int16 *)(uintptr_t)vPtr);
  }
  result *= 4;
  entityRecord = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( !entityRecord )
    return result;
  result = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( (*(_BYTE *)(uintptr_t)(entityRecord + 1) & 0x40) != 0 )
  {
LABEL_15:
    ++*(_DWORD *)(uintptr_t)(vPtr + 4);
    return result;
  }
  if ( *(_DWORD *)(uintptr_t)(entityRecord + 28) )
    return (*(int (__cdecl **)(int))(uintptr_t)(entityRecord + 28))(a3);
  return result;
}
// 48F795: simplified comparisons for 'eax.4': >=3u && >=4u became >=4u
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F800) --------------------------------------------------------
unsigned int  Rules_AtomDeinstall(unsigned int result, __int16 *vPtr, int a3)
{
  int entityRecord; // ecx

  if ( result < 3 )
  {
    if ( !result )
      return Rules_DecrementFloatCount((int)(intptr_t)vPtr, a3);
    if ( result <= 1 )
      return Rules_DecrementIntegerCount((int)(intptr_t)vPtr, a3);
    return Rules_DecrementSymbolCount((int)(intptr_t)vPtr, a3);
  }
  if ( result <= 3 )
    return Rules_DecrementSymbolCount((int)(intptr_t)vPtr, a3);
  if ( result < 8 )
  {
    if ( result == 4 )
      return (unsigned int)(intptr_t)Rules_DeinstallMultifield(vPtr);
    goto LABEL_4;
  }
  if ( result <= 8 )
    return Rules_DecrementSymbolCount((int)(intptr_t)vPtr, a3);
  if ( result >= 0xD )
  {
    if ( result > 0xD )
    {
      if ( result == 105 )
        return result;
      goto LABEL_4;
    }
    return Rules_DecrementSymbolCount((int)(intptr_t)vPtr, a3);
  }
LABEL_4:
  result *= 4;
  entityRecord = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
  if ( entityRecord )
  {
    result = *(int *)((char *)g_Clips_PrimitiveEntityTable + result);
    if ( (*(_BYTE *)(uintptr_t)(entityRecord + 1) & 0x40) != 0 )
    {
      return Rules_DecrementBitmapCount((int)(intptr_t)vPtr, entityRecord);
    }
    else if ( *(_DWORD *)(uintptr_t)(entityRecord + 24) )
    {
      return (*(int (__cdecl **)(int))(uintptr_t)(entityRecord + 24))(a3);
    }
  }
  return result;
}
// 54E530: using guessed type int dword_54E530[70];

//----- (0048F8A0) --------------------------------------------------------
int  Rules_PropagateReturnValueDepth(uintptr_t vPtr)
{
  int result; // eax
  int fieldIndex; // ebx
  int end; // edi
  __int16 *fieldPtr; // ecx

  if ( *(_DWORD *)(vPtr + 4) != 4 )
    return Rules_ClampEvaluationDepth(*(_DWORD *)(vPtr + 4), (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(vPtr + 8));
  result = *(_DWORD *)(vPtr + 8);
  if ( *(__int16 *)((uintptr_t)(unsigned int)result + 4) > g_ClipsCurrentEvaluationDepth )
    *(_WORD *)((uintptr_t)(unsigned int)result + 4) = g_ClipsCurrentEvaluationDepth;
  fieldIndex = *(_DWORD *)(vPtr + 12);
  end = *(int *)(vPtr + 16);
  if ( fieldIndex <= end )
  {
    fieldPtr = (__int16 *)((uintptr_t)(unsigned int)result + 6 * fieldIndex + 14);
    do
    {
      result = Rules_ClampEvaluationDepth(*fieldPtr, (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(fieldPtr + 1));
      ++fieldIndex;
      fieldPtr += 3;
    }
    while ( fieldIndex <= end );
  }
  return result;
}
// 48F8E8: variable 'v5' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;

//----- (0048F940) --------------------------------------------------------
int  Rules_ClampEvaluationDepth(int result, _DWORD *theValue)
{
  __int16 currentDepth; // bx

  switch ( result )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
      if ( g_ClipsCurrentEvaluationDepth < theValue[2] )
        theValue[2] = g_ClipsCurrentEvaluationDepth;
      break;
    case 6:
      currentDepth = g_ClipsCurrentEvaluationDepth;
      result = theValue[7] & 0x7FFF;
      if ( result > g_ClipsCurrentEvaluationDepth )
      {
        *((_WORD *)theValue + 14) &= 0x8000u;
        result = currentDepth & 0x7FFF;
        theValue[7] |= result;
      }
      break;
    case 7:
      if ( g_ClipsCurrentEvaluationDepth < theValue[8] )
        theValue[8] = g_ClipsCurrentEvaluationDepth;
      break;
    default:
      return result;
  }
  return result;
}
// 51A96C: using guessed type int dword_51A96C;

//----- (0048FB10) --------------------------------------------------------
signed int  AST_BuildExpressionFromValue(_DWORD *theValue)
{
  int theType; // ecx
  signed int lastNode; // ebx
  int fieldIndex; // ecx
  int fieldOffset; // esi
  signed int newNode; // eax
  int v8; // ecx
  int **Symbol; // eax
  signed int topNode; // [esp+0h] [ebp-18h]

  theType = theValue[1];
  lastNode = 0;
  topNode = 0;
  if ( theType != 4 )
    return AST_NewNode(theType, theValue[2]);
  fieldIndex = theValue[3] + 1;
  fieldOffset = 6 * fieldIndex - 6;
  while ( fieldIndex <= theValue[4] + 1 )
  {
    newNode = AST_NewNode(*(_WORD *)(uintptr_t)(fieldOffset + theValue[2] + 14), *(_DWORD *)(uintptr_t)(fieldOffset + theValue[2] + 16));
    if ( lastNode )
      *(_DWORD *)(uintptr_t)(lastNode + 10) = newNode;
    else
      topNode = newNode;
    lastNode = newNode;
    fieldOffset += 6;
    fieldIndex = v8 + 1;
  }
  if ( topNode )
    return topNode;
  Symbol = Rules_MakeSymbol(aCreate_1);
  return AST_NewNode(10, (int)(intptr_t)Symbol);
}
// 48FB80: variable 'v8' is possibly undefined

//----- (0048FBD0) --------------------------------------------------------
int  Rules_ComputeFieldHashValue(int theType, int value, int position)
{
  int result; // eax

  result = value;
  switch ( theType )
  {
    case CLIPS_TYPE_FLOAT:
      result = *(_DWORD *)(uintptr_t)(value + 16);
      goto LABEL_3;
    case CLIPS_TYPE_INTEGER:
      result = *(_DWORD *)(uintptr_t)(value + 16);
      goto LABEL_3;
    case CLIPS_TYPE_SYMBOL:
    case CLIPS_TYPE_STRING:
    case CLIPS_TYPE_INSTANCE_NAME:
      result = *(_DWORD *)(uintptr_t)(value + 12) << 16 >> 18;
      goto LABEL_3;
    case CLIPS_TYPE_EXTERNAL_ADDRESS:
    case CLIPS_TYPE_FACT_ADDRESS:
    case CLIPS_TYPE_INSTANCE_ADDRESS:
LABEL_3:
      if ( position >= 0 )
        result *= position + 29;
      break;
    default:
      result = theType;
      if ( position >= 0 )
        result = (position + 29) * theType;
      break;
  }
  return result;
}

//----- (0048FC30) --------------------------------------------------------
int  Rules_RetractFactFromNetwork(_DWORD *matchList, double a2)
{
  unsigned int link_record; // edi
  unsigned int pattern; // esi
  unsigned int node; // esi/ecx
  unsigned int partial_match; // ebx
  unsigned int next_link; // eax
  int removed_nodes; // [esp+0h] [ebp-20h] BYREF
  int retained_tail; // [esp+4h] [ebp-1Ch] BYREF

  for ( link_record = (unsigned int)(uintptr_t)matchList; link_record; link_record = *(_DWORD *)(uintptr_t)link_record )
  {
    pattern = *(_DWORD *)((uintptr_t)link_record + 8);
    partial_match = *(_DWORD *)((uintptr_t)link_record + 4);
    for ( node = *(_DWORD *)((uintptr_t)pattern + 8); node; node = *(_DWORD *)((uintptr_t)node + 32) )
    {
      if ( (*(_BYTE *)(uintptr_t)node & 8) == 0 )
        Rules_PropagateRetractToJoinNode(
          (int)node,
          *(_DWORD *)((uintptr_t)partial_match + 8),
          ((*(_DWORD *)(uintptr_t)node << 16) >> 25) - 1,
          partial_match,
          a2,
          1);
    }
  }

  link_record = (unsigned int)(uintptr_t)matchList;
  while ( link_record )
  {
    pattern = *(_DWORD *)((uintptr_t)link_record + 8);
    partial_match = *(_DWORD *)((uintptr_t)link_record + 4);
    for ( node = *(_DWORD *)((uintptr_t)pattern + 8); node; node = *(_DWORD *)((uintptr_t)node + 32) )
    {
      if ( (*(_BYTE *)(uintptr_t)node & 8) != 0 )
      {
        if ( (*(_DWORD *)(uintptr_t)node & 1) == 1 )
        {
          Rules_ReportSystemError((int)node, 3);
          IO_RunRouterExitCallbacks();
        }
        else
        {
          Rules_UpdateBetaMemoryOnRetract((_DWORD *)(uintptr_t)node, partial_match, 1, a2);
        }
      }
    }
    removed_nodes = 0;
    retained_tail = 0;
    *(_DWORD *)(uintptr_t)pattern = Rules_FilterPartialMatchList(
                                      *(_DWORD *)((uintptr_t)partial_match + 8),
                                      (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)pattern,
                                      0,
                                      &removed_nodes,
                                      &retained_tail);
    *(_DWORD *)((uintptr_t)pattern + 4) = retained_tail;
    Rules_FreePartialMatchList(removed_nodes, 0);
    next_link = *(_DWORD *)(uintptr_t)link_record;
    g_ClipsMemFreeListTemp = link_record;
    *(_DWORD *)(uintptr_t)link_record = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
    link_record = next_link;
  }
  return Rules_FlushDeferredRetractQueue(a2);
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048FD50) --------------------------------------------------------
int  Rules_PropagateRetractToJoinNode(int result, int theEntity, int position, int a4, double a5, int deferJoinDrive)
{
  uintptr_t node; // [esp+8h] [ebp-14h]
  int removed_nodes; // [esp+0h] [ebp-1Ch] BYREF
  int retained_tail; // [esp+4h] [ebp-18h] BYREF
  int last; // eax

  node = (uintptr_t)(unsigned int)result;
  last = result;
  while ( node )
  {
    if ( !*(_DWORD *)(node + 8) )
      return last;
    last = Rules_FilterPartialMatchList(
             theEntity,
             (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8),
             position,
             &removed_nodes,
             &retained_tail);
    *(_DWORD *)(node + 8) = last;
    if ( !removed_nodes )
      return last;
    {
      uintptr_t child = (uintptr_t)(unsigned int)*(_DWORD *)(node + 20);
      if ( !child )
        return Rules_FreePartialMatchList(removed_nodes, 1);
      if ( (int)node == *(_DWORD *)(child + 16) )
      {
        uintptr_t removed = (uintptr_t)(unsigned int)removed_nodes;
        while ( removed )
        {
          Rules_UpdateBetaMemoryOnRetract((_DWORD *)child, (int)removed, deferJoinDrive, a5);
          removed = (uintptr_t)(unsigned int)*(_DWORD *)(removed + 4);
        }
        return Rules_FreePartialMatchList(removed_nodes, 1);
      }
      last = Rules_FreePartialMatchList(removed_nodes, 1);
      while ( *(_DWORD *)(child + 28) )
      {
        last = Rules_PropagateRetractToJoinNode((int)child, theEntity, position, a4, a5, deferJoinDrive);
        child = (uintptr_t)(unsigned int)*(_DWORD *)(child + 28);
      }
      node = child;
    }
  }
  return last;
}

//----- (0048FE40) --------------------------------------------------------
_DWORD * Rules_UpdateBetaMemoryOnRetract(_DWORD *result, int theBind, int deferJoinDrive, double a4)
{
  int theJoin; // edi
  int currentMatch; // esi
  int v7; // edx
  _DWORD *v8; // ecx
  int childJoin; // ecx
  int v10; // ecx
  _DWORD *v11; // ecx

  theJoin = (int)(intptr_t)result;
  currentMatch = result[2];
  if ( currentMatch )
  {
    while ( 1 )
    {
      if ( (*(_BYTE *)(uintptr_t)currentMatch & 0x20) == 0 )
        goto LABEL_3;
      result = (_DWORD *)(uintptr_t)(currentMatch + 4 * (*(_DWORD *)(uintptr_t)currentMatch << 17 >> 23));
      v7 = result[1];
      if ( theBind != v7 )
        goto LABEL_3;
      result[1] = 0;
      result = (_DWORD *)(uintptr_t)Rules_EvaluateJoinTest((_WORD *)(uintptr_t)currentMatch, *(_DWORD *)(uintptr_t)(v7 + 4), theJoin, a4);
      if ( result )
        goto LABEL_3;
      *(_BYTE *)(uintptr_t)currentMatch &= ~0x20u;
      v8 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
      if ( v8 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *v8;
        result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
      }
      else
      {
        result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      result[2] = 0;
      *result = 0;
      result[1] = 0;
      *(_DWORD *)(uintptr_t)(currentMatch + 4 * (*(_DWORD *)(uintptr_t)currentMatch << 17 >> 23) + 4) = result;
      if ( *(_DWORD *)(uintptr_t)(theJoin + 36) )
        result = Rules_AddActivation(*(_DWORD *)(uintptr_t)(theJoin + 36), currentMatch, a4);
      childJoin = *(_DWORD *)(uintptr_t)(theJoin + 20);
      if ( !childJoin )
        goto LABEL_3;
      if ( theJoin == *(_DWORD *)(uintptr_t)(childJoin + 16) )
      {
        result = (_DWORD *)Rules_DriveJoinNetwork(currentMatch, *(_DWORD *)(uintptr_t)(theJoin + 20), 1, a4);
        currentMatch = *(_DWORD *)(uintptr_t)(currentMatch + 4);
        if ( !currentMatch )
          return result;
      }
      else if ( deferJoinDrive )
      {
        v11 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
        if ( v11 )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *v11;
          result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
        }
        else
        {
          result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
        }
        *result = currentMatch;
        result[1] = *(_DWORD *)(uintptr_t)(theJoin + 20);
        result[2] = g_ClipsDeferredJoinDriveListHead;
        g_ClipsDeferredJoinDriveListHead = (int)(intptr_t)result;
        currentMatch = *(_DWORD *)(uintptr_t)(currentMatch + 4);
        if ( !currentMatch )
          return result;
      }
      else
      {
        while ( childJoin )
        {
          result = (_DWORD *)Rules_DriveJoinNetwork(currentMatch, childJoin, 0, a4);
          childJoin = *(_DWORD *)(uintptr_t)(v10 + 28);
        }
LABEL_3:
        currentMatch = *(_DWORD *)(uintptr_t)(currentMatch + 4);
        if ( !currentMatch )
          return result;
      }
    }
  }
  return result;
}
// 48FF0A: variable 'v10' is possibly undefined
// 51A970: using guessed type int dword_51A970;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048FFA0) --------------------------------------------------------
signed int  Rules_EvaluateJoinTest(_WORD *theBind, int listOfMatches, int theJoin, double a4)
{
  _WORD *bindFieldPtr; // edx
  int matchFieldPtr; // ecx
  int i; // eax
  signed int testResult; // [esp+0h] [ebp-14h]

  if ( (*(_BYTE *)(uintptr_t)theJoin & 4) != 0 )
    listOfMatches = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theJoin + 16) + 8);
  while ( listOfMatches )
  {
    testResult = 0;
    if ( (*(_BYTE *)(uintptr_t)listOfMatches & 0x20) == 0 )
    {
      if ( *(_DWORD *)(uintptr_t)(theJoin + 12) )
      {
        testResult = Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theJoin + 12), theBind, (_BYTE *)(uintptr_t)(unsigned int)theJoin, listOfMatches, a4);
        if ( g_ClipsEvaluationError )
        {
          g_ClipsEvaluationError = 0;
LABEL_15:
          *(_DWORD *)&theBind[2 * (*(_DWORD *)theBind << 17 >> 23) + 2] = listOfMatches;
          return 1;
        }
      }
      else
      {
        testResult = 1;
        if ( (*(_BYTE *)(uintptr_t)theJoin & 4) != 0 )
        {
          bindFieldPtr = theBind;
          matchFieldPtr = listOfMatches;
          for ( i = 0; i < (*(_DWORD *)theBind << 17 >> 23) - 1; ++i )
          {
            if ( *(_DWORD *)(uintptr_t)(matchFieldPtr + 8) != *((_DWORD *)bindFieldPtr + 2) )
              goto LABEL_6;
            bindFieldPtr += 2;
            matchFieldPtr += 4;
          }
        }
      }
    }
    if ( testResult )
      goto LABEL_15;
LABEL_6:
    listOfMatches = *(_DWORD *)(uintptr_t)(listOfMatches + 4);
  }
  return 0;
}
// 51A964: using guessed type int dword_51A964;

//----- (00490060) --------------------------------------------------------
int  Rules_FilterPartialMatchList(int theEntity, _DWORD *listOfPMs, int position, int *deletedMatches, int *lastMatch)
{
  uintptr_t current; // esi
  uintptr_t removed_tail; // ebp
  uintptr_t previous; // ecx
  uintptr_t head; // [esp+Ch] [ebp-10h]
  int slot_offset; // [esp+0h] [ebp-1Ch]

  current = (uintptr_t)(unsigned int)(uintptr_t)listOfPMs;
  head = current;
  previous = current;
  removed_tail = 0;
  slot_offset = 4 * position;
  *deletedMatches = 0;
  while ( current )
  {
    unsigned int field_count = ((unsigned int)*(_DWORD *)current << 17) >> 23;
    int keep = ((*(_BYTE *)current & 0x20) != 0 && (int)field_count - 1 == position);
    if ( !keep )
      keep = theEntity != *(_DWORD *)(current + slot_offset + 8);
    if ( keep )
    {
      previous = current;
      current = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
    }
    else
    {
      uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(current + 4);
      if ( (*(_BYTE *)current & 4) != 0 )
      {
        unsigned int nested = *(_DWORD *)(current + 4 * field_count + 8);
        if ( nested )
          Rules_RemoveActivation((_DWORD *)(uintptr_t)nested, 1, 1);
      }
      if ( current == head )
      {
        if ( *deletedMatches )
          *(_DWORD *)(removed_tail + 4) = (int)current;
        else
          *deletedMatches = (int)current;
        removed_tail = current;
        head = next;
        *(_DWORD *)(current + 4) = 0;
        current = next;
        previous = head;
      }
      else
      {
        *(_DWORD *)(previous + 4) = (int)next;
        if ( *deletedMatches )
          *(_DWORD *)(removed_tail + 4) = (int)current;
        else
          *deletedMatches = (int)current;
        *(_DWORD *)(current + 4) = 0;
        removed_tail = current;
        current = next;
      }
    }
  }
  *lastMatch = (int)previous;
  return (int)head;
}

//----- (00490160) --------------------------------------------------------
signed int  Rules_FreePartialMatchList(signed int result, int betaDelete)
{
  uintptr_t node; // ecx
  signed int last; // eax

  node = (uintptr_t)(unsigned int)result;
  last = result;
  while ( node )
  {
    uintptr_t next = (uintptr_t)(unsigned int)*(_DWORD *)(node + 4);
    if ( (*(_BYTE *)node & 8) != 0 )
      Rules_RemovePMDependencies((int)node);
    if ( !betaDelete || ((*(_BYTE *)node & 0x10) != 0 && (*(_BYTE *)node & 0x20) == 0) )
    {
      last = g_PartialMatchFreeListHead;
      *(_DWORD *)(node + 4) = g_PartialMatchFreeListHead;
      g_PartialMatchFreeListHead = (int)node;
    }
    else
    {
      last = Rules_FreePartialMatch((int)node);
    }
    node = next;
  }
  return last;
}
// 51A974: using guessed type int dword_51A974;

//----- (004901C0) --------------------------------------------------------
signed int  Rules_FreePartialMatch(int theMatch)
{
  uintptr_t node; // ecx
  uintptr_t value_record; // eax
  unsigned int free_bucket; // eax
  signed int result; // eax

  node = (uintptr_t)(unsigned int)theMatch;
  if ( (*(_BYTE *)node & 2) != 0 )
  {
    result = g_PartialMatchFreeListHead;
    *(_DWORD *)(node + 4) = g_PartialMatchFreeListHead;
    g_PartialMatchFreeListHead = (int)node;
  }
  else
  {
    if ( (*(_BYTE *)node & 1) == 0 )
    {
      value_record = (uintptr_t)(unsigned int)*(_DWORD *)(node + 8);
      if ( *(_DWORD *)(value_record + 4) )
        Rules_FreeValueRecordChain((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(value_record + 4));
      Mem_SmallBlockFree((_DWORD *)value_record, 12);
    }
    if ( (*(_BYTE *)node & 8) != 0 )
      Rules_RemoveEntityDependencies((_DWORD *)node);
    free_bucket = 4
                * ((((unsigned int)*(_DWORD *)node << 29) >> 31)
                 + (((unsigned int)*(_DWORD *)node << 17) >> 23)
                 + (((unsigned int)*(_DWORD *)node << 28) >> 31))
                + 8;
    g_Rules_MemPoolFreeBucketIndex = free_bucket;
    if ( free_bucket >= 0x1F4 )
    {
      return Mem_ReleasePoolBlock((int)node, free_bucket);
    }
    else
    {
      g_ClipsMemFreeListTemp = (int)node;
      *(_DWORD *)node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 4 * free_bucket);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 4 * g_Rules_MemPoolFreeBucketIndex) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 4901E8: variable 'v1' is possibly undefined
// 51A974: using guessed type int dword_51A974;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB0: using guessed type int dword_54DBB0;

//----- (00490280) --------------------------------------------------------
_DWORD * Rules_FreeValueRecordChain(_DWORD *result)
{
  uintptr_t node; // eax
  unsigned int next_node; // edx

  node = (uintptr_t)(unsigned int)(uintptr_t)result;
  if ( node )
  {
    do
    {
      next_node = *(_DWORD *)(node + 16);
      g_ClipsMemFreeListTemp = (int)node;
      *(_DWORD *)node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
      node = (uintptr_t)next_node;
    }
    while ( node );
  }
  return (_DWORD *)node;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004902C0) --------------------------------------------------------
int  Rules_FlushDeferredRetractQueue(double a1)
{
  char *i; // ecx
  int v2 CLASH95_UNUSED; // ecx
  int nextEntry; // ecx
  int result; // eax

  if ( g_ClipsDeferredJoinDriveListHead )
  {
    do
    {
      /* loc_4902DC: `mov ecx,[ecx+1Ch]` - the cursor advances from itself. */
      for ( i = (char *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDeferredJoinDriveListHead + 4); i; i = (char *)(uintptr_t)*(_DWORD *)(uintptr_t)((uintptr_t)i + 28) )
        Rules_DriveJoinNetwork((int *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsDeferredJoinDriveListHead, i, 0, a1);
      nextEntry = *(_DWORD *)(uintptr_t)(g_ClipsDeferredJoinDriveListHead + 8);
      g_ClipsMemFreeListTemp = g_ClipsDeferredJoinDriveListHead;
      *(_DWORD *)(uintptr_t)g_ClipsDeferredJoinDriveListHead = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      g_ClipsDeferredJoinDriveListHead = nextEntry;
    }
    while ( nextEntry );
  }
  return result;
}
// 4902EC: variable 'v2' is possibly undefined
// 51A970: using guessed type int dword_51A970;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00490330) --------------------------------------------------------
void Rules_FlushPendingNetworkGarbage(void)
{
  unsigned int next_parser;
  unsigned int next_fact;
  uintptr_t parser_node;
  uintptr_t parser_bucket;
  unsigned int nested_node;

  while ( g_ReteGarbageAlphaMatchList )
  {
    parser_node = (uintptr_t)(unsigned int)g_ReteGarbageAlphaMatchList;
    next_parser = *(_DWORD *)(parser_node + 8);
    g_ClipsMemFreeListTemp = g_ReteGarbageAlphaMatchList;
    *(_DWORD *)parser_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
    g_ReteGarbageAlphaMatchList = next_parser;
  }
  while ( g_PartialMatchFreeListHead )
  {
    parser_node = (uintptr_t)(unsigned int)g_PartialMatchFreeListHead;
    next_fact = *(_DWORD *)(parser_node + 4);
    if ( (*(_BYTE *)parser_node & 0x10) != 0 && (*(_BYTE *)parser_node & 0x20) == 0 )
    {
      parser_bucket = parser_node + 4 * (((unsigned int)*(_DWORD *)parser_node << 17) >> 23);
      nested_node = *(_DWORD *)(parser_bucket + 4);
      if ( nested_node )
      {
        g_ClipsMemFreeListTemp = nested_node;
        *(_DWORD *)(uintptr_t)nested_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
        *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      }
    }
    *(_BYTE *)parser_node &= ~2u;
    Rules_FreePartialMatch((int)parser_node);
    g_PartialMatchFreeListHead = next_fact;
  }
}
// 51A974: using guessed type int dword_51A974;
// 51A978: using guessed type int dword_51A978;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004903E0) --------------------------------------------------------
BOOL  Lexer_AppendCharToPendingToken(int inchar)
{
  int oldLength; // esi

  oldLength = g_Lexer_PendingLineCharIndex;
  g_Lexer_PendingTokenBuffer = (int)(intptr_t)Str_AppendCharEscaping(
                        inchar,
                        (char *)(uintptr_t)g_Lexer_PendingTokenBuffer,
                        (unsigned int *)&g_Lexer_TokenBufferCapacity,
                        &g_Lexer_PendingLineCharIndex,
                        g_Lexer_TokenBufferCapacity + 80);
  return oldLength != g_Lexer_PendingLineCharIndex;
}
// 51A628: using guessed type int dword_51A628;
// 51A980: using guessed type int dword_51A980;
// 51A984: using guessed type int dword_51A984;

//----- (00490430) --------------------------------------------------------
signed int Lexer_ResetPendingTokenBuffer(void)
{
  signed int result; // eax

  if ( g_Lexer_PendingTokenBuffer )
    result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_Lexer_PendingTokenBuffer, g_Lexer_TokenBufferCapacity);
  g_Lexer_PendingTokenBuffer = 0;
  g_Lexer_TokenBufferCapacity = 0;
  g_Lexer_PendingLineCharIndex = 0;
  return result;
}
// 51A628: using guessed type int dword_51A628;
// 51A980: using guessed type int dword_51A980;
// 51A984: using guessed type int dword_51A984;
