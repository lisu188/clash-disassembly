/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004811C0) --------------------------------------------------------
double  Rules_RtnDouble(int argumentPosition, int a2, double a3)
{
  int argExpr; // eax
  int i; // edx
  int v7; // eax
  int v8; // [esp+0h] [ebp-30h] BYREF
  int resultType; // [esp+4h] [ebp-2Ch]
  int resultValue; // [esp+8h] [ebp-28h]
  double returnValue; // [esp+18h] [ebp-18h]

  argExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    if ( i >= argumentPosition )
      break;
    argExpr = *(_DWORD *)(uintptr_t)(argExpr + 10);
  }
  if ( !argExpr )
  {
    Rules_NonexistentArgError(*(_DWORD *)(uintptr_t)(**(_DWORD **)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
    returnValue = 1.0;
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return returnValue;
  }
  Parser_ParseForm((__int16 *)(uintptr_t)argExpr, &v8, a2, a3);
  if ( !resultType )
  {
    v7 = *(_DWORD *)(uintptr_t)(resultValue + 20);
    LODWORD(returnValue) = *(_DWORD *)(uintptr_t)(resultValue + 16);
    HIDWORD(returnValue) = v7;
    return returnValue;
  }
  if ( resultType == 1 )
    return (double)*(int *)(uintptr_t)(resultValue + 16);
  Rules_ExpectedTypeError((int)(intptr_t)aRtndouble, *(_DWORD *)(uintptr_t)(**(_DWORD **)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
  HIDWORD(returnValue) = 1072693248;
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  LODWORD(returnValue) = 0;
  return returnValue;
}
// 51A960: using guessed type int dword_51A960;

//----- (004812C0) --------------------------------------------------------
signed int  Rules_RtnLong(int argumentPosition, int a2, double a3)
{
  uintptr_t expression; // eax
  uintptr_t current; // eax
  int i; // edx
  uintptr_t function_node; // edx
  uintptr_t function_symbol; // edx
  _DWORD parsed[6]; // [esp+0h] [ebp-28h] BYREF

  expression = (uintptr_t)(unsigned int)g_ClipsCurrentExpression;
  current = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 6) : 0;
  for ( i = 1; current; ++i )
  {
    if ( i >= argumentPosition )
      break;
    current = (uintptr_t)(unsigned int)*(_DWORD *)(current + 10);
  }
  if ( !current )
  {
    function_node = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2) : 0;
    function_symbol = function_node ? (uintptr_t)(unsigned int)*(_DWORD *)function_node : 0;
    Rules_NonexistentArgError(function_symbol ? *(_DWORD *)(function_symbol + 16) : 0, argumentPosition);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 1;
  }
  Parser_ParseForm((__int16 *)current, parsed, a2, a3);
  if ( !parsed[1] )
    return (int)Parser_NumberValueAsDouble(parsed[2]);
  if ( parsed[1] == 1 )
    return Parser_NumberValueAsInt(parsed[2]);
  function_node = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2) : 0;
  function_symbol = function_node ? (uintptr_t)(unsigned int)*(_DWORD *)function_node : 0;
  Rules_ExpectedTypeError((int)(intptr_t)aRtnlong, function_symbol ? *(_DWORD *)(function_symbol + 16) : 0, argumentPosition);
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (004813B0) --------------------------------------------------------
int  Rules_RtnUnknown(int argumentPosition, _DWORD *returnValue, double a3)
{
  int argExpr; // eax
  int i; // edx
  int resultType; // ecx

  argExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    if ( i >= argumentPosition )
      break;
    argExpr = *(_DWORD *)(uintptr_t)(argExpr + 10);
  }
  if ( argExpr )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)argExpr, returnValue, (int)(intptr_t)returnValue, a3);
    return resultType;
  }
  else
  {
    Rules_NonexistentArgError(*(_DWORD *)(uintptr_t)(**(_DWORD **)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 48140E: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (00481420) --------------------------------------------------------
int Rules_RtnArgCount(void)
{
  int argExpr; // eax
  int i; // edx

  argExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  for ( i = 0; argExpr; ++i )
    argExpr = *(_DWORD *)(uintptr_t)(argExpr + 10);
  return i;
}
// 51A960: using guessed type int dword_51A960;

//----- (00481450) --------------------------------------------------------
int Lexer_TokenExpect(int expectedNumber)
{
  int result; // eax
  int countRelation; // edx
  int functionName; // ecx

  result = Rules_RtnArgCount();
  if ( !countRelation )
  {
    if ( result == expectedNumber )
      return result;
LABEL_9:
    Rules_ExpectedCountError(functionName, expectedNumber);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -1;
  }
  if ( countRelation == 1 )
  {
    if ( result < expectedNumber )
      goto LABEL_9;
  }
  else if ( countRelation != 2 || result > expectedNumber )
  {
    goto LABEL_9;
  }
  return result;
}
// 48145A: variable 'v2' is possibly undefined
// 481478: variable 'v3' is possibly undefined

//----- (004814A0) --------------------------------------------------------
int  Rules_ArgRangeCheck(int functionName, int maxArgs)
{
  int result; // eax
  int minArgs; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  result = Rules_RtnArgCount();
  if ( result < minArgs || result > maxArgs )
  {
    Rules_PrintErrorID((int)(intptr_t)aArgacces, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction, v5);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, v6);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAtLeas, v7);
    Rules_PrintLongInteger(v8, v8);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAndNoMoreThan, v9);
    Rules_PrintLongInteger(v10, maxArgs);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aArguments_, v11);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -1;
  }
  return result;
}
// 4814B0: variable 'v4' is possibly undefined
// 4814D5: variable 'v5' is possibly undefined
// 4814E1: variable 'v6' is possibly undefined
// 4814F0: variable 'v7' is possibly undefined
// 4814FC: variable 'v8' is possibly undefined
// 48150B: variable 'v9' is possibly undefined
// 481517: variable 'v10' is possibly undefined
// 481526: variable 'v11' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
