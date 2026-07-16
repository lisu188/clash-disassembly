/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004A0080) --------------------------------------------------------
int  Rules_NumericNotEqualFunction(int a1, double result, int a3)
{
  uintptr_t expression; // esi
  int argument_index; // edi
  _DWORD previous[6]; // [esp+0h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-2Ch] BYREF

  (void)a1;
  (void)a3;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, previous, result, 1) )
    return 0;

  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  for ( argument_index = 2; expression; ++argument_index )
  {
    if ( !Parser_ParseNumericFormCompat((__int16 *)expression, 0, current, result, argument_index) )
      return 0;
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) == Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (004A0180) --------------------------------------------------------
signed int  Rules_OddpFunction(int returnValue, double a2)
{
  signed int result; // eax
  int item; // [esp-8h] [ebp-24h] BYREF
  int itemValue; // [esp+0h] [ebp-1Ch]
  int returnValueCopy; // [esp+14h] [ebp-8h]

  returnValueCopy = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &item, 1, a2);
  if ( result )
    return *(_DWORD *)(itemValue + 16) != 2 * (*(_DWORD *)(itemValue + 16) / 2);
  return result;
}

//----- (004A01E0) --------------------------------------------------------
signed int  Rules_EvenpFunction(int returnValue, double a2)
{
  signed int result; // eax
  int item; // [esp-8h] [ebp-24h] BYREF
  int itemValue; // [esp+0h] [ebp-1Ch]
  int returnValueCopy; // [esp+14h] [ebp-8h]

  returnValueCopy = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &item, 1, a2);
  if ( result )
    return *(_DWORD *)(itemValue + 16) == 2 * (*(_DWORD *)(itemValue + 16) / 2);
  return result;
}

//----- (004A0240) --------------------------------------------------------
signed int Rules_RegisterArithmeticFunctions(void)
{
  Rules_RegisterHostFunction(asc_506D2C, 110, (int)aAdditionfuncti, (int)Rules_AdditionFunction, (int)a2N_0);
  Rules_RegisterHostFunction(asc_506D48, 110, (int)aMultiplication, (int)Rules_MultiplicationFunction, (int)a2N_0);
  Rules_RegisterHostFunction(asc_506D60, 110, (int)aSubtractionfun, (int)Rules_SubtractionFunction, (int)a2N_0);
  Rules_RegisterHostFunction(asc_506D78, 110, (int)aDivisionfuncti, (int)Rules_DivisionFunction, (int)a2N_0);
  Rules_RegisterHostFunction(aDiv, 108, (int)aDivfunction, (int)Rules_DivFunction, (int)a2N_0);
  Rules_RegisterHostFunction(aSetAutoFloatDi, 98, (int)aSetautofloatdi, (int)Rules_SetAutoFloatDividendCommand, (int)a11_3);
  Rules_RegisterHostFunction(aGetAutoFloatDi, 98, (int)aGetautofloatdi, (int)Rules_GetAutoFloatDividendCommand, (int)a00_6);
  Rules_RegisterHostFunction(aInteger, 108, (int)aIntegerfunctio, (int)Rules_IntegerFunction, (int)a11n);
  Rules_RegisterHostFunction(aFloat, 100, (int)aFloatfunction, (int)Rules_FloatFunction, (int)a11n);
  Rules_RegisterHostFunction(aAbs, 110, (int)aAbsfunction, (int)Rules_AbsFunction, (int)a11n);
  Rules_RegisterHostFunction(aMin, 110, (int)aMinfunction, (int)Rules_MinFunction, (int)a2N_0);
  return Rules_RegisterHostFunction(aMax, 110, (int)aMaxfunction, (int)Rules_MaxFunction, (int)a2N_0);
}

//----- (004A03B0) --------------------------------------------------------
int * Rules_AdditionFunction(uintptr_t returnValue, double a2)
{
  uintptr_t expression; // esi
  uintptr_t current; // esi
  uintptr_t next; // esi
  int integer_sum; // ebp
  int saw_float; // edi
  double float_sum; // [esp+18h] [ebp-2Ch]
  _DWORD parsed[6]; // [esp+0h] [ebp-44h] BYREF
  int argument_index; // [esp+24h] [ebp-20h]
  int value; // eax

  integer_sum = 0;
  saw_float = 0;
  float_sum = 0.0;
  expression = (uintptr_t)(unsigned int)g_ClipsCurrentExpression;
  current = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 6) : 0;
  for ( argument_index = 1; current; ++argument_index )
  {
    if ( Parser_ParseNumericFormCompat((__int16 *)current, saw_float, parsed, a2, argument_index) )
      next = (uintptr_t)(unsigned int)*(_DWORD *)(current + 10);
    else
      next = 0;
    value = parsed[2];
    if ( saw_float )
    {
      float_sum += Parser_NumberValueAsDouble(value);
    }
    else if ( parsed[1] == 1 )
    {
      integer_sum += Parser_NumberValueAsInt(value);
    }
    else
    {
      float_sum = (double)integer_sum + Parser_NumberValueAsDouble(value);
      saw_float = 1;
    }
    current = next;
  }
  if ( saw_float )
  {
    *(_DWORD *)(returnValue + 4) = 0;
    *(_DWORD *)(returnValue + 8) = (int)(uintptr_t)Rules_AddDoubleValue(float_sum);
  }
  else
  {
    *(_DWORD *)(returnValue + 4) = 1;
    *(_DWORD *)(returnValue + 8) = (int)(uintptr_t)Rules_AddIntegerValue(integer_sum);
  }
  return (int *)(uintptr_t)(unsigned int)*(_DWORD *)(returnValue + 8);
}
// 51A960: using guessed type int dword_51A960;

//----- (004A04A0) --------------------------------------------------------
int * Rules_MultiplicationFunction(int returnValue, double a2)
{
  signed int ltotal; // ebp
  int useFloatTotal; // edi
  int theExpression; // esi
  int parseOk; // eax
  double newFtotal; // st6
  int resultTarget; // ebx
  int *result; // eax
  double floatResultValue; // [esp-8h] [ebp-4Ch]
  _DWORD theArgument[2]; // [esp+0h] [ebp-44h] BYREF
  int argValuePtr; // [esp+8h] [ebp-3Ch]
  double ftotal; // [esp+18h] [ebp-2Ch]
  int returnValueCopy; // [esp+20h] [ebp-24h]
  int i; // [esp+24h] [ebp-20h]
  signed int savedLtotal; // [esp+28h] [ebp-1Ch]

  returnValueCopy = returnValue;
  ltotal = 1;
  useFloatTotal = 0;
  ftotal = 1.0;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 1; theExpression; ++i )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, useFloatTotal, theArgument, a2, i);
    if ( parseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( useFloatTotal )
    {
      newFtotal = ftotal * *(double *)(argValuePtr + 16);
    }
    else
    {
      if ( theArgument[1] == 1 )
      {
        ltotal *= *(_DWORD *)(argValuePtr + 16);
        continue;
      }
      savedLtotal = ltotal;
      newFtotal = (double)ltotal * *(double *)(argValuePtr + 16);
      useFloatTotal = 1;
    }
    ftotal = newFtotal;
  }
  if ( useFloatTotal )
  {
    floatResultValue = ftotal;
    resultTarget = returnValueCopy;
    *(_DWORD *)(returnValueCopy + 4) = 0;
    result = (int *)Rules_AddDoubleValue(floatResultValue);
  }
  else
  {
    *(_DWORD *)(returnValueCopy + 4) = 1;
    resultTarget = returnValueCopy;
    result = Rules_AddIntegerValue(ltotal);
  }
  *(_DWORD *)(resultTarget + 8) = result;
  return result;
}
// 4A04ED: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A0590) --------------------------------------------------------
int * Rules_SubtractionFunction(int returnValue, double a2)
{
  signed int ltotal; // ebp
  int useFloatTotal; // edi
  int theExpression; // esi
  int parseOk; // eax
  int firstParseOk; // eax
  int floatHighBits; // eax
  int resultTarget; // ebx
  int *result; // eax
  double floatResultValue; // [esp-8h] [ebp-4Ch]
  int theArgument; // [esp+0h] [ebp-44h] BYREF
  int argType; // [esp+4h] [ebp-40h]
  int argValuePtr; // [esp+8h] [ebp-3Ch]
  double ftotal; // [esp+18h] [ebp-2Ch]
  int returnValueCopy; // [esp+20h] [ebp-24h]
  int argIndex; // [esp+24h] [ebp-20h]
  signed int savedLtotal; // [esp+28h] [ebp-1Ch]

  returnValueCopy = returnValue;
  ltotal = 0;
  useFloatTotal = 0;
  ftotal = 0.0;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  argIndex = 1;
  if ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, 0, &theArgument, a2, 1);
    if ( firstParseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( argType == 1 )
    {
      ltotal = *(_DWORD *)(argValuePtr + 16);
    }
    else
    {
      useFloatTotal = 1;
      floatHighBits = *(_DWORD *)(argValuePtr + 20);
      LODWORD(ftotal) = *(_DWORD *)(argValuePtr + 16);
      HIDWORD(ftotal) = floatHighBits;
    }
    ++argIndex;
  }
  while ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, useFloatTotal, &theArgument, a2, argIndex);
    if ( parseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( useFloatTotal )
    {
      ftotal = ftotal - *(double *)(argValuePtr + 16);
      ++argIndex;
    }
    else
    {
      if ( argType == 1 )
      {
        ltotal -= *(_DWORD *)(argValuePtr + 16);
      }
      else
      {
        savedLtotal = ltotal;
        useFloatTotal = 1;
        ftotal = (double)ltotal - *(double *)(argValuePtr + 16);
      }
      ++argIndex;
    }
  }
  if ( useFloatTotal )
  {
    floatResultValue = ftotal;
    resultTarget = returnValueCopy;
    *(_DWORD *)(returnValueCopy + 4) = 0;
    result = (int *)Rules_AddDoubleValue(floatResultValue);
  }
  else
  {
    *(_DWORD *)(returnValueCopy + 4) = 1;
    resultTarget = returnValueCopy;
    result = Rules_AddIntegerValue(ltotal);
  }
  *(_DWORD *)(resultTarget + 8) = result;
  return result;
}
// 4A05E0: variable 'v5' is possibly undefined
// 4A0616: variable 'v6' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A06E0) --------------------------------------------------------
int * Rules_DivisionFunction(int returnValue, double a2)
{
  signed int ltotal; // esi
  int useFloatTotal; // ebp
  int theExpression; // edi
  int resultTarget; // ebx
  int *result; // eax
  int firstParseOk; // eax
  int floatHighBits; // eax
  int parseOk; // eax
  BOOL isDivideByZero; // eax
  int divZeroResultTarget; // ebx
  double floatResultValue; // [esp-8h] [ebp-4Ch]
  int theArgument; // [esp+0h] [ebp-44h] BYREF
  int argType; // [esp+4h] [ebp-40h]
  int argValuePtr; // [esp+8h] [ebp-3Ch]
  double ftotal; // [esp+18h] [ebp-2Ch]
  int returnValueCopy; // [esp+20h] [ebp-24h]
  int argIndex; // [esp+24h] [ebp-20h]
  signed int savedLtotal; // [esp+28h] [ebp-1Ch]

  returnValueCopy = returnValue;
  ltotal = 1;
  useFloatTotal = g_Rules_AutoFloatDividendEnabled;
  ftotal = 1.0;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  argIndex = 1;
  if ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, g_Rules_AutoFloatDividendEnabled, &theArgument, a2, 1);
    if ( firstParseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( argType == 1 )
    {
      ltotal = *(_DWORD *)(argValuePtr + 16);
    }
    else
    {
      useFloatTotal = 1;
      floatHighBits = *(_DWORD *)(argValuePtr + 20);
      LODWORD(ftotal) = *(_DWORD *)(argValuePtr + 16);
      HIDWORD(ftotal) = floatHighBits;
    }
    ++argIndex;
  }
  while ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, useFloatTotal, &theArgument, a2, argIndex);
    if ( parseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( argType == 1 )
      isDivideByZero = *(_DWORD *)(argValuePtr + 16) == 0;
    else
      isDivideByZero = !argType && (*(_DWORD *)(argValuePtr + 20) & 0x7FFFFFFF) == 0 && !*(_DWORD *)(argValuePtr + 16);
    if ( isDivideByZero )
    {
      Rules_ReportDivideByZeroError();
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      divZeroResultTarget = returnValueCopy;
      *(_DWORD *)(returnValueCopy + 4) = 0;
      result = (int *)Rules_AddDoubleValue(1.0);
      *(_DWORD *)(divZeroResultTarget + 8) = result;
      return result;
    }
    if ( useFloatTotal )
    {
      ftotal = ftotal / *(double *)(argValuePtr + 16);
      ++argIndex;
    }
    else
    {
      if ( argType == 1 )
      {
        ltotal /= *(int *)(argValuePtr + 16);
      }
      else
      {
        savedLtotal = ltotal;
        useFloatTotal = 1;
        ftotal = (double)ltotal / *(double *)(argValuePtr + 16);
      }
      ++argIndex;
    }
  }
  if ( useFloatTotal )
  {
    floatResultValue = ftotal;
    resultTarget = returnValueCopy;
    *(_DWORD *)(returnValueCopy + 4) = 0;
    result = (int *)Rules_AddDoubleValue(floatResultValue);
  }
  else
  {
    *(_DWORD *)(returnValueCopy + 4) = 1;
    resultTarget = returnValueCopy;
    result = Rules_AddIntegerValue(ltotal);
  }
  *(_DWORD *)(resultTarget + 8) = result;
  return result;
}
// 4A0762: variable 'v7' is possibly undefined
// 4A07B6: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ACD4: using guessed type int dword_51ACD4;

//----- (004A08D0) --------------------------------------------------------
double  Rules_DivFunction(double result)
{
  int theExpression; // esi
  int argIndex; // edi
  int firstParseOk; // eax
  double firstFloatValue; // st6
  int parseOk; // eax
  double divisorFloatCheck; // st6
  double divisorFloat; // st6
  int theArgument; // [esp+0h] [ebp-3Ch] BYREF
  int argType; // [esp+4h] [ebp-38h]
  int argValuePtr; // [esp+8h] [ebp-34h]
  int v11; // [esp+18h] [ebp-24h]
  int theNumber; // [esp+1Ch] [ebp-20h]
  int total; // [esp+20h] [ebp-1Ch]

  total = 1;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  argIndex = 1;
  if ( theExpression )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)theExpression, 0, &theArgument, result, 1);
    if ( firstParseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( argType == 1 )
    {
      total = *(_DWORD *)(argValuePtr + 16);
    }
    else
    {
      firstFloatValue = *(double *)(argValuePtr + 16);
      _CHP(theArgument, argType);
      total = (int)firstFloatValue;
    }
    argIndex = 2;
  }
  while ( theExpression )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)theExpression, 0, &theArgument, result, argIndex);
    if ( parseOk )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( argType == 1 )
    {
      theNumber = *(_DWORD *)(argValuePtr + 16);
    }
    else
    {
      if ( argType )
        goto LABEL_16;
      divisorFloatCheck = *(double *)(argValuePtr + 16);
      _CHP(theArgument, 0);
      theNumber = (int)divisorFloatCheck;
    }
    if ( !theNumber )
    {
      Rules_ReportDivideByZeroError();
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return result;
    }
LABEL_16:
    if ( argType == 1 )
    {
      total /= *(int *)(argValuePtr + 16);
    }
    else
    {
      divisorFloat = *(double *)(argValuePtr + 16);
      _CHP(theArgument, argType);
      v11 = (int)divisorFloat;
      total /= (int)divisorFloat;
    }
    ++argIndex;
  }
  return result;
}
// 4A0918: variable 'v3' is possibly undefined
// 4A095B: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A0A10) --------------------------------------------------------
int  Rules_SetAutoFloatDividendCommand(int returnValue, double a2)
{
  int result; // ecx
  int theValue; // [esp-4h] [ebp-24h] BYREF
  __int64 typeValuePair; // [esp+0h] [ebp-20h]
  int returnValueCopy; // [esp+18h] [ebp-8h]

  returnValueCopy = returnValue;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, &theValue, a2);
    g_Rules_AutoFloatDividendEnabled = typeValuePair != __PAIR64__(g_ClipsFalseSymbol, 2);
  }
  return result;
}
// 4A0A32: variable 'v3' is possibly undefined
// 51ACD4: using guessed type int dword_51ACD4;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A0A80) --------------------------------------------------------
int Rules_GetAutoFloatDividendCommand(void)
{
  Lexer_TokenExpect(0);
  return g_Rules_AutoFloatDividendEnabled;
}
// 51ACD4: using guessed type int dword_51ACD4;

//----- (004A0AC0) --------------------------------------------------------
signed int  Rules_IntegerFunction(int returnValue, double a2)
{
  signed int result; // eax
  _DWORD item[9]; // [esp-8h] [ebp-24h] BYREF

  item[7] = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, item, 1, a2);
  if ( result )
    return *(_DWORD *)(item[2] + 16);
  return result;
}

//----- (004A0B10) --------------------------------------------------------
double  Rules_FloatFunction(int a1, int a2, int a3, double a4)
{
  int valueHigh; // eax
  int item; // [esp-8h] [ebp-30h] BYREF
  int itemValue; // [esp+0h] [ebp-28h]
  double floatValue; // [esp+10h] [ebp-18h]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+1Ch] [ebp-Ch]
  int v11; // [esp+24h] [ebp-4h]

  v11 = a1;
  v10 = a3;
  v9 = a2;
  if ( Lexer_TokenExpect(1) == -1 )
  {
    floatValue = 0.0;
    return 0.0;
  }
  else if ( Lexer_ParseValueList(1, &item, 0, a4) )
  {
    valueHigh = *(_DWORD *)(itemValue + 20);
    LODWORD(floatValue) = *(_DWORD *)(itemValue + 16);
    HIDWORD(floatValue) = valueHigh;
    return floatValue;
  }
  else
  {
    floatValue = 0.0;
    return 0.0;
  }
}

//----- (004A0B90) --------------------------------------------------------
void  Rules_AbsFunction(_DWORD *returnValue, double a2)
{
  signed int parseOk; // eax
  int longValue; // ecx
  int valuePtr; // edx

  if ( Lexer_TokenExpect(1) == -1 )
  {
    parseOk = 0;
    goto LABEL_7;
  }
  parseOk = Lexer_ParseValueList(1, returnValue, 110, a2);
  if ( !parseOk )
  {
LABEL_7:
    returnValue[1] = 1;
    returnValue[2] = Rules_AddIntegerValue(parseOk);
    return;
  }
  if ( returnValue[1] == 1 )
  {
    longValue = *(_DWORD *)(returnValue[2] + 16);
    if ( longValue < 0 )
      returnValue[2] = Rules_AddIntegerValue(-longValue);
  }
  else
  {
    valuePtr = returnValue[2];
    if ( *(double *)(valuePtr + 16) < 0.0 )
      returnValue[2] = Rules_AddDoubleValue(-*(double *)(valuePtr + 16));
  }
}

//----- (004A0C30) --------------------------------------------------------
void  Rules_MinFunction(_DWORD *returnValue, double a2)
{
  int numberOfArguments; // ebp
  signed int parseOk; // eax
  int argIndex; // edi
  int argValue; // [esp+0h] [ebp-30h] BYREF
  int argType; // [esp+4h] [ebp-2Ch]
  int argValuePtr; // [esp+8h] [ebp-28h]

  numberOfArguments = Lexer_TokenExpect(1);
  if ( numberOfArguments == -1 )
  {
    parseOk = 0;
    goto LABEL_13;
  }
  parseOk = Lexer_ParseValueList(1, returnValue, 110, a2);
  if ( !parseOk )
  {
LABEL_13:
    returnValue[1] = 1;
    returnValue[2] = Rules_AddIntegerValue(parseOk);
    return;
  }
  argIndex = 2;
  if ( numberOfArguments >= 2 )
  {
    while ( 1 )
    {
      if ( !Lexer_ParseValueList(argIndex, &argValue, 110, a2) )
        return;
      if ( returnValue[1] != 1 )
        break;
      if ( argType != 1 )
      {
        a2 = (double)*(int *)(returnValue[2] + 16);
        if ( a2 <= *(double *)(argValuePtr + 16) )
          goto LABEL_10;
        returnValue[1] = argType;
        goto LABEL_9;
      }
      if ( *(_DWORD *)(returnValue[2] + 16) > *(_DWORD *)(argValuePtr + 16) )
        goto LABEL_8;
LABEL_10:
      if ( ++argIndex > numberOfArguments )
        return;
    }
    if ( argType == 1 )
    {
      a2 = (double)*(int *)(argValuePtr + 16);
      if ( a2 >= *(double *)(returnValue[2] + 16) )
        goto LABEL_10;
    }
    else
    {
      a2 = *(double *)(returnValue[2] + 16);
      if ( a2 <= *(double *)(argValuePtr + 16) )
        goto LABEL_10;
    }
LABEL_8:
    returnValue[1] = argType;
LABEL_9:
    returnValue[2] = argValuePtr;
    goto LABEL_10;
  }
}

//----- (004A0D30) --------------------------------------------------------
void  Rules_MaxFunction(_DWORD *returnValue, double a2)
{
  int numberOfArguments; // ebp
  signed int parseOk; // eax
  int argIndex; // edi
  int argValue; // [esp+0h] [ebp-30h] BYREF
  int argType; // [esp+4h] [ebp-2Ch]
  int argValuePtr; // [esp+8h] [ebp-28h]

  numberOfArguments = Lexer_TokenExpect(1);
  if ( numberOfArguments == -1 )
  {
    parseOk = 0;
    goto LABEL_13;
  }
  parseOk = Lexer_ParseValueList(1, returnValue, 110, a2);
  if ( !parseOk )
  {
LABEL_13:
    returnValue[1] = 1;
    returnValue[2] = Rules_AddIntegerValue(parseOk);
    return;
  }
  argIndex = 2;
  if ( numberOfArguments >= 2 )
  {
    while ( 1 )
    {
      if ( !Lexer_ParseValueList(argIndex, &argValue, 110, a2) )
        return;
      if ( returnValue[1] != 1 )
        break;
      if ( argType != 1 )
      {
        a2 = (double)*(int *)(returnValue[2] + 16);
        if ( a2 >= *(double *)(argValuePtr + 16) )
          goto LABEL_10;
        returnValue[1] = argType;
        goto LABEL_9;
      }
      if ( *(_DWORD *)(returnValue[2] + 16) < *(_DWORD *)(argValuePtr + 16) )
        goto LABEL_8;
LABEL_10:
      if ( ++argIndex > numberOfArguments )
        return;
    }
    if ( argType == 1 )
    {
      a2 = (double)*(int *)(argValuePtr + 16);
      if ( a2 <= *(double *)(returnValue[2] + 16) )
        goto LABEL_10;
    }
    else
    {
      a2 = *(double *)(returnValue[2] + 16);
      if ( a2 >= *(double *)(argValuePtr + 16) )
        goto LABEL_10;
    }
LABEL_8:
    returnValue[1] = argType;
LABEL_9:
    returnValue[2] = argValuePtr;
    goto LABEL_10;
  }
}

//----- (004A0E30) --------------------------------------------------------
signed int Rules_RegisterMultifieldFunctions(void)
{
  int v0; // ecx

  Rules_RegisterHostFunction(aFirst, 109, (int)aFirstfunction, (int)Rules_FirstFunction, (int)a11m_0);
  Rules_RegisterHostFunction(aRest, 109, (int)aRestfunction, (int)Rules_RestFunction, (int)a11m_0);
  Rules_RegisterHostFunction(aSubseq, 109, (int)aSubseqfunction, (int)Rules_SubseqFunction, (int)a33im);
  Rules_RegisterHostFunction(aDelete, 109, (int)aDeletefunction, (int)Rules_DeleteFunction, (int)a33im);
  Rules_RegisterHostFunction(aReplace, 109, (int)aReplacefunctio, (int)Rules_ReplaceFunction, (int)a4Mii);
  Rules_RegisterHostFunction(aInsert, 109, (int)aInsertfunction, (int)Rules_InsertFunction, (int)a3Mi);
  Rules_RegisterHostFunction(aExplode, 109, (int)aExplodefunctio, (int)Rules_ExplodeFunction, (int)a11s_0);
  Rules_RegisterHostFunction(aImplode, 115, (int)aImplodefunctio, (int)Rules_ImplodeFunction, (int)a11m_0);
  Rules_RegisterHostFunction(aNth, 117, (int)aNthfunction, (int)Rules_NthFunction, (int)a22Im);
  Rules_RegisterHostFunction(aMember, 117, (int)aMemberfunction, (int)Rules_MemberFunction, (int)a22Um);
  Rules_RegisterHostFunction(aSubsetp, 98, (int)aSubsetpfunctio, (int)Rules_SubsetpFunction, (int)a22Mm);
  Rules_RegisterHostFunction(aProgn_0, 117, (int)aMultifieldprog, (int)Rules_EvalPrognMultifieldBuiltin, 0);
  Rules_RegisterHostFunction(aStrImplode, 115, (int)aImplodefunctio, (int)Rules_ImplodeFunction, (int)a11m_0);
  Rules_RegisterHostFunction(aStrExplode, 109, (int)aExplodefunctio, (int)Rules_ExplodeFunction, (int)a11s_0);
  Rules_RegisterHostFunction(aSubset, 98, (int)aSubsetpfunctio, (int)Rules_SubsetpFunction, (int)a22Mm);
  Rules_RegisterHostFunction(aNth_0, 117, (int)aNthfunction, (int)Rules_NthFunction, (int)a22Im);
  Rules_RegisterHostFunction(aMvReplace, 109, (int)aMvreplacefunct, (int)Rules_MVReplaceFunction, (int)a33Im);
  Rules_RegisterHostFunction(aMember_0, 117, (int)aMemberfunction, (int)Rules_MemberFunction, (int)a22Um);
  Rules_RegisterHostFunction(aMvSubseq, 109, (int)aMvsubseqfuncti, (int)Rules_MVSubseqFunction, (int)a33Iim);
  Rules_RegisterHostFunction(aMvDelete, 109, (int)aMvdeletefuncti, (int)Rules_MVDeleteFunction, (int)a22Im);
  Rules_AddFunctionParser(aProgn_0);
  Rules_SetFunctionSeqOverloadFlags(aProgn_0, 0);
  Rules_RegisterHostFunction(aGetPrognField, 117, v0, (int)Rules_EvalGetPrognFieldBuiltin, (int)a00_7);
  return Rules_RegisterHostFunction(aGetPrognIndex, 108, (int)aGetmvprogninde, (int)Rules_EvalGetPrognIndexBuiltin, (int)a00_7);
}
// 4A10BE: variable 'v0' is possibly undefined
// 4A22D0: using guessed type int sub_4A22D0();

//----- (004A10F0) --------------------------------------------------------
_DWORD * Rules_DeleteFunction(_DWORD *returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD value1[6]; // [esp+0h] [ebp-58h] BYREF
  _DWORD value3[6]; // [esp+18h] [ebp-40h] BYREF
  _DWORD value2[10]; // [esp+30h] [ebp-28h] BYREF

  value2[8] = a2;
  if ( !Lexer_ParseValueList(1, value1, 4, a3)
    || !Lexer_ParseValueList(2, value2, 1, a3)
    || !Lexer_ParseValueList(3, value3, 1, a3)
    || (result = (_DWORD *)Rules_MultifieldDeleteRange(returnValue, value1, *(_DWORD *)(value3[2] + 16), *(_DWORD *)(value2[2] + 16), (int)aDelete)) == 0 )
  {
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
  return result;
}

//----- (004A1190) --------------------------------------------------------
_DWORD * Rules_MVDeleteFunction(_DWORD *returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD multifieldValue[6]; // [esp+0h] [ebp-40h] BYREF
  int indexValue; // [esp+18h] [ebp-28h] BYREF
  int indexValuePtr; // [esp+20h] [ebp-20h]
  int v8; // [esp+38h] [ebp-8h]

  v8 = a2;
  if ( !Lexer_ParseValueList(1, &indexValue, 1, a3)
    || !Lexer_ParseValueList(2, multifieldValue, 4, a3)
    || (result = (_DWORD *)Rules_MultifieldDeleteRange(returnValue, multifieldValue, *(_DWORD *)(indexValuePtr + 16), *(_DWORD *)(indexValuePtr + 16), (int)aMvDelete)) == 0 )
  {
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
  return result;
}

//----- (004A1210) --------------------------------------------------------
_DWORD * Rules_ReplaceFunction(_DWORD *returnValue, int a2, double a3)
{
  int v5; // ecx
  int fieldArg; // eax
  _DWORD *result; // eax
  _DWORD value1[6]; // [esp+0h] [ebp-70h] BYREF
  _DWORD value3[6]; // [esp+18h] [ebp-58h] BYREF
  _DWORD value2[6]; // [esp+30h] [ebp-40h] BYREF
  _DWORD value4[10]; // [esp+48h] [ebp-28h] BYREF

  value4[8] = a2;
  if ( !Lexer_ParseValueList(1, value1, 4, a3)
    || !Lexer_ParseValueList(2, value2, 1, a3)
    || !Lexer_ParseValueList(3, value3, 1, a3) )
  {
    goto LABEL_7;
  }
  fieldArg = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10) + 10);
  if ( *(_DWORD *)(fieldArg + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(value4, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10) + 10), 1, a3);
  else
    Parser_ParseForm((__int16 *)fieldArg, value4, v5, a3);
  result = (_DWORD *)Rules_MultifieldReplaceRange(returnValue, value1, *(_DWORD *)(value3[2] + 16), *(_DWORD *)(value2[2] + 16), value4, (int)aReplace);
  if ( !result )
  {
LABEL_7:
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
  return result;
}
// 4A12E0: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A12F0) --------------------------------------------------------
_DWORD * Rules_MVReplaceFunction(_DWORD *returnValue, int a2, double a3)
{
  int v4; // ecx
  _DWORD *result; // eax
  _DWORD multifieldValue[6]; // [esp+0h] [ebp-58h] BYREF
  int indexValue; // [esp+18h] [ebp-40h] BYREF
  int indexValuePtr; // [esp+20h] [ebp-38h]
  _DWORD fieldValue[10]; // [esp+30h] [ebp-28h] BYREF

  fieldValue[8] = a2;
  if ( !Lexer_ParseValueList(1, &indexValue, 1, a3)
    || !Lexer_ParseValueList(2, multifieldValue, 4, a3)
    || (Parser_ParseForm(*(__int16 **)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), fieldValue, v4, a3),
        (result = (_DWORD *)Rules_MultifieldReplaceRange(returnValue, multifieldValue, *(_DWORD *)(indexValuePtr + 16), *(_DWORD *)(indexValuePtr + 16), fieldValue, (int)aMvReplace)) == 0) )
  {
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
  return result;
}
// 4A133E: variable 'v4' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A1390) --------------------------------------------------------
_DWORD * Rules_InsertFunction(_DWORD *returnValue, int a2, double a3)
{
  int v5; // ecx
  int fieldArg; // eax
  _DWORD *result; // eax
  _DWORD value1[6]; // [esp+0h] [ebp-58h] BYREF
  _DWORD value3[6]; // [esp+18h] [ebp-40h] BYREF
  _DWORD value2[10]; // [esp+30h] [ebp-28h] BYREF

  value2[8] = a2;
  if ( !Lexer_ParseValueList(1, value1, 4, a3) || !Lexer_ParseValueList(2, value2, 1, a3) )
    goto LABEL_6;
  fieldArg = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
  if ( *(_DWORD *)(fieldArg + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(value3, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), 1, a3);
  else
    Parser_ParseForm((__int16 *)fieldArg, value3, v5, a3);
  result = (_DWORD *)Rules_MultifieldInsertRange(returnValue, value1, value3, *(_DWORD *)(value2[2] + 16), (int)aInsert);
  if ( !result )
  {
LABEL_6:
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
  return result;
}
// 4A1431: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A1440) --------------------------------------------------------
_DWORD * Rules_ExplodeFunction(_DWORD *returnValue, int a2, double a3)
{
  _DWORD *explodedMultifield; // eax
  _DWORD *theMultifield; // ecx
  int multifieldLength; // eax
  _DWORD *result; // eax
  _DWORD value[10]; // [esp-8h] [ebp-28h] BYREF

  value[8] = a2;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, value, 3, a3) )
  {
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)returnValue);
  }
  else
  {
    explodedMultifield = Rules_CreateMultifieldFromString(*(const char **)(value[2] + 16));
    theMultifield = explodedMultifield;
    if ( explodedMultifield )
    {
      multifieldLength = *(_DWORD *)((char *)explodedMultifield + 6);
    }
    else
    {
      theMultifield = Rules_CreateEphemeralMultifield(0);
      multifieldLength = 0;
    }
    returnValue[1] = 4;
    returnValue[3] = 0;
    result = (_DWORD *)(multifieldLength - 1);
    returnValue[2] = theMultifield;
    returnValue[4] = result;
  }
  return result;
}

//----- (004A14E0) --------------------------------------------------------
signed int * Rules_ImplodeFunction(double a1)
{
  int v1; // ecx
  unsigned int totalSize; // esi
  int fieldIndex; // ebp
  int theMultifield; // ebx
  int fieldPtr; // edx
  __int16 fieldType; // cx
  int numberString; // eax
  const char *fieldString; // edi
  _BYTE *quoteScanPtr; // eax
  char *retStr; // edi
  int fieldCursor; // eax
  int bufOffset; // ecx
  char *writePtr; // edx
  __int16 curFieldType; // bx
  _BYTE *floatString; // eax
  _BYTE *floatWritePtr; // edx
  char *spacePtr; // eax
  int fieldPosSnapshot; // edx
  _BYTE *integerString; // eax
  _BYTE *intWritePtr; // edx
  int strOffset; // eax
  char *srcString; // ecx
  char *closingQuotePtr; // ebp
  char ch; // bl
  char *charWritePtr; // edx
  __int16 lexemeType; // bx
  char *wordString; // eax
  int writeIndex; // ecx
  char *wordWritePtr; // edx
  int wordCloseIndex; // eax
  char *instanceNameString; // eax
  int instWriteIndex; // ecx
  char *instanceWritePtr; // edx
  int instCloseIndex; // eax
  char *symbolString; // eax
  int internedSymbol; // ecx
  int value; // [esp+0h] [ebp-3Ch] BYREF
  int multifieldBase; // [esp+8h] [ebp-34h]
  int beginIndex; // [esp+Ch] [ebp-30h]
  int endIndex; // [esp+10h] [ebp-2Ch]
  char *afterBracketPtr; // [esp+18h] [ebp-24h]
  int fieldPos; // [esp+1Ch] [ebp-20h]
  int curField; // [esp+20h] [ebp-1Ch]

  totalSize = 0;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, &value, 4, a1) )
    return Str_Intern(g_Rules_ImplodeEmptyResult, v1);
  fieldIndex = beginIndex + 1;
  theMultifield = multifieldBase;
  fieldPtr = multifieldBase + 6 * (beginIndex + 1) - 6;
  while ( fieldIndex <= endIndex + 1 )
  {
    fieldType = *(_WORD *)(fieldPtr + 14);
    switch ( fieldType )
    {
      case 0:
        numberString = Rules_FloatToSymbol(*(_DWORD *)(*(_DWORD *)(fieldPtr + 16) + 20), *(double *)(*(_DWORD *)(fieldPtr + 16) + 16));
LABEL_7:
        fieldString = (const char *)numberString;
LABEL_8:
        v1 = strlen(fieldString) + 1;
        totalSize += v1;
        goto LABEL_9;
      case 1:
        numberString = Rules_LongIntegerToSymbol(*(_DWORD *)(*(_DWORD *)(fieldPtr + 16) + 16));
        goto LABEL_7;
      case 3:
        v1 = strlen(*(const char **)(*(_DWORD *)(fieldPtr + 16) + 16)) + 3;
        quoteScanPtr = *(_BYTE **)(*(_DWORD *)(fieldPtr + 16) + 16);
        totalSize += v1;
        if ( *quoteScanPtr )
        {
          do
          {
            if ( *quoteScanPtr == 34 )
              ++totalSize;
            BYTE1(v1) = *++quoteScanPtr;
          }
          while ( BYTE1(v1) );
          fieldPtr += 6;
          ++fieldIndex;
        }
        else
        {
LABEL_9:
          fieldPtr += 6;
          ++fieldIndex;
        }
        break;
      case 8:
        v1 = strlen(*(const char **)(*(_DWORD *)(fieldPtr + 16) + 16)) + 3;
        totalSize += v1;
        fieldPtr += 6;
        ++fieldIndex;
        break;
      case 7:
        v1 = strlen(*(const char **)(*(_DWORD *)(*(_DWORD *)(fieldPtr + 16) + 28) + 16)) + 3;
        totalSize += v1;
        fieldPtr += 6;
        ++fieldIndex;
        break;
      default:
        fieldString = *(const char **)(*(_DWORD *)(fieldPtr + 16) + 16);
        goto LABEL_8;
    }
  }
  if ( !totalSize )
    return Str_Intern(g_Rules_ImplodeEmptyResult, v1);
  retStr = (char *)Mem_SmallBlockAlloc(totalSize);
  fieldPos = beginIndex + 1;
  fieldCursor = theMultifield + 6 * (beginIndex + 1) - 6;
  bufOffset = 0;
  while ( 1 )
  {
    curField = fieldCursor;
    writePtr = &retStr[bufOffset];
    if ( endIndex + 1 < fieldPos )
      break;
    curFieldType = *(_WORD *)(curField + 14);
    if ( curFieldType )
    {
      if ( curFieldType == 1 )
      {
        integerString = (_BYTE *)Rules_LongIntegerToSymbol(*(_DWORD *)(*(_DWORD *)(curField + 16) + 16));
        if ( *integerString )
        {
          do
          {
            *intWritePtr++ = *integerString;
            ++bufOffset;
          }
          while ( *++integerString );
        }
      }
      else if ( curFieldType == 3 )
      {
        strOffset = bufOffset + 1;
        srcString = *(char **)(*(_DWORD *)(curField + 16) + 16);
        *writePtr = 34;
        while ( 1 )
        {
          closingQuotePtr = &retStr[strOffset];
          if ( !*srcString )
            break;
          if ( *srcString == 34 )
          {
            ++strOffset;
            *closingQuotePtr = 92;
          }
          ch = *srcString;
          charWritePtr = &retStr[strOffset];
          ++srcString;
          ++strOffset;
          *charWritePtr = ch;
        }
        bufOffset = strOffset + 1;
        *closingQuotePtr = 34;
      }
      else
      {
        afterBracketPtr = &retStr[bufOffset + 1];
        lexemeType = *(_WORD *)(curField + 14);
        if ( lexemeType == 8 )
        {
          wordString = *(char **)(*(_DWORD *)(curField + 16) + 16);
          retStr[bufOffset] = 91;
          writeIndex = bufOffset + 1;
          if ( *wordString )
          {
            wordWritePtr = afterBracketPtr;
            do
            {
              *wordWritePtr++ = *wordString;
              ++writeIndex;
            }
            while ( *++wordString );
          }
          wordCloseIndex = writeIndex;
          bufOffset = writeIndex + 1;
          retStr[wordCloseIndex] = 93;
        }
        else if ( lexemeType == 7 )
        {
          instanceNameString = *(char **)(*(_DWORD *)(*(_DWORD *)(curField + 16) + 28) + 16);
          retStr[bufOffset] = 91;
          instWriteIndex = bufOffset + 1;
          if ( *instanceNameString )
          {
            instanceWritePtr = afterBracketPtr;
            do
            {
              *instanceWritePtr++ = *instanceNameString;
              ++instWriteIndex;
            }
            while ( *++instanceNameString );
          }
          instCloseIndex = instWriteIndex;
          bufOffset = instWriteIndex + 1;
          retStr[instCloseIndex] = 93;
        }
        else
        {
          symbolString = *(char **)(*(_DWORD *)(curField + 16) + 16);
          if ( *symbolString )
          {
            do
            {
              *writePtr++ = *symbolString;
              ++bufOffset;
            }
            while ( *++symbolString );
          }
        }
      }
    }
    else
    {
      floatString = (_BYTE *)Rules_FloatToSymbol(bufOffset, *(double *)(*(_DWORD *)(curField + 16) + 16));
      if ( *floatString )
      {
        do
        {
          *floatWritePtr++ = *floatString;
          ++bufOffset;
        }
        while ( *++floatString );
      }
    }
    spacePtr = &retStr[bufOffset];
    fieldPosSnapshot = fieldPos;
    ++bufOffset;
    *spacePtr = 32;
    fieldCursor = curField + 6;
    fieldPos = fieldPosSnapshot + 1;
  }
  *(writePtr - 1) = 0;
  Str_Intern(retStr, bufOffset);
  Mem_SmallBlockFree(retStr, totalSize);
  return (signed int *)internedSymbol;
}
// 4A156A: variable 'v5' is possibly undefined
// 4A1575: variable 'v1' is possibly undefined
// 4A1696: variable 'v17' is possibly undefined
// 4A169C: variable 'v13' is possibly undefined
// 4A16D4: variable 'v22' is possibly undefined
// 4A17E2: variable 'v42' is possibly undefined

//----- (004A17F0) --------------------------------------------------------
_DWORD * Rules_SubseqFunction(_DWORD *subValue, double a2)
{
  int theList; // ebp
  int start; // edi
  int end; // eax
  int length; // edx
  int offsetBase; // edx
  _DWORD *result; // eax
  _DWORD value[2]; // [esp+0h] [ebp-34h] BYREF
  int valuePtr; // [esp+8h] [ebp-2Ch]
  int valueBegin; // [esp+Ch] [ebp-28h]
  int offset; // [esp+18h] [ebp-1Ch]

  if ( !Lexer_ParseValueList(1, value, 4, a2) )
    return Rules_SetMultifieldErrorValue((int)subValue);
  offset = valueBegin + 1;
  theList = valuePtr;
  if ( !Lexer_ParseValueList(2, value, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)subValue);
  start = *(_DWORD *)(valuePtr + 16);
  if ( !Lexer_ParseValueList(3, value, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)subValue);
  end = *(_DWORD *)(valuePtr + 16);
  if ( end < 1 )
    return Rules_SetMultifieldErrorValue((int)subValue);
  if ( end < start )
    return Rules_SetMultifieldErrorValue((int)subValue);
  length = *(_DWORD *)(theList + 6);
  if ( start > length )
    return Rules_SetMultifieldErrorValue((int)subValue);
  if ( end > length )
    end = *(_DWORD *)(theList + 6);
  if ( start < 1 )
    start = 1;
  subValue[1] = 4;
  offsetBase = offset;
  subValue[2] = theList;
  result = (_DWORD *)(offsetBase + end - 2);
  subValue[4] = result;
  subValue[3] = offsetBase + start - 2;
  return result;
}

//----- (004A18D0) --------------------------------------------------------
_DWORD * Rules_MVSubseqFunction(_DWORD *subValue, double a2)
{
  int start; // edi
  int end; // ebp
  int theList; // ecx
  _DWORD *result; // eax
  int offset; // edx
  _DWORD theValue[2]; // [esp+0h] [ebp-30h] BYREF
  int valueField; // [esp+8h] [ebp-28h]
  int valueBegin; // [esp+Ch] [ebp-24h]

  if ( !Lexer_ParseValueList(1, theValue, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)subValue);
  start = *(_DWORD *)(valueField + 16);
  if ( !Lexer_ParseValueList(2, theValue, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)subValue);
  end = *(_DWORD *)(valueField + 16);
  if ( end < 1 )
    return Rules_SetMultifieldErrorValue((int)subValue);
  if ( end < start )
    return Rules_SetMultifieldErrorValue((int)subValue);
  if ( !Lexer_ParseValueList(3, theValue, 4, a2) )
    return Rules_SetMultifieldErrorValue((int)subValue);
  theList = valueField;
  result = *(_DWORD **)(valueField + 6);
  offset = valueBegin + 1;
  if ( start > (int)result )
    return Rules_SetMultifieldErrorValue((int)subValue);
  if ( end > (int)result )
    end = *(_DWORD *)(valueField + 6);
  if ( start < 1 )
    start = 1;
  subValue[1] = 4;
  subValue[2] = theList;
  subValue[4] = offset + end - 2;
  subValue[3] = start + offset - 2;
  return result;
}

//----- (004A19A0) --------------------------------------------------------
_DWORD * Rules_FirstFunction(_DWORD *returnValue, int a2, double a3)
{
  int theMultifield; // eax
  _DWORD *result; // eax
  _DWORD theValue[3]; // [esp-8h] [ebp-28h] BYREF
  signed int begin; // [esp+4h] [ebp-1Ch]
  int end; // [esp+8h] [ebp-18h]
  int v10; // [esp+18h] [ebp-8h]

  v10 = a2;
  if ( !Lexer_ParseValueList(1, theValue, 4, a3) )
    return Rules_SetMultifieldErrorValue((int)returnValue);
  theMultifield = theValue[2];
  returnValue[1] = 4;
  returnValue[2] = theMultifield;
  if ( end + 1 >= begin + 1 )
  {
    returnValue[4] = begin;
    result = (_DWORD *)begin;
    returnValue[3] = begin;
  }
  else
  {
    returnValue[4] = end;
    result = (_DWORD *)begin;
    returnValue[3] = begin;
  }
  return result;
}

//----- (004A1A20) --------------------------------------------------------
_DWORD * Rules_RestFunction(_DWORD *returnValue, int a2, double a3)
{
  int theMultifield; // eax
  _DWORD *result; // eax
  _DWORD theValue[3]; // [esp-8h] [ebp-28h] BYREF
  int begin; // [esp+4h] [ebp-1Ch]
  signed int end; // [esp+8h] [ebp-18h]
  int v10; // [esp+18h] [ebp-8h]

  v10 = a2;
  if ( !Lexer_ParseValueList(1, theValue, 4, a3) )
    return Rules_SetMultifieldErrorValue((int)returnValue);
  theMultifield = theValue[2];
  returnValue[1] = 4;
  returnValue[2] = theMultifield;
  if ( begin + 1 > end + 1 )
  {
    returnValue[3] = begin;
    result = (_DWORD *)end;
    returnValue[4] = end;
  }
  else
  {
    returnValue[3] = begin + 1;
    result = (_DWORD *)end;
    returnValue[4] = end;
  }
  return result;
}

//----- (004A1A90) --------------------------------------------------------
signed int * Rules_NthFunction(int returnValue, int a2, double a3)
{
  int beginCopy; // ecx
  int n; // edx
  int theMultifield; // ebx
  signed int *result; // eax
  _DWORD value1[6]; // [esp-8h] [ebp-40h] BYREF
  int value2; // [esp+10h] [ebp-28h] BYREF
  int multifieldPtr; // [esp+18h] [ebp-20h]
  int begin; // [esp+1Ch] [ebp-1Ch]
  int end; // [esp+20h] [ebp-18h]
  int v14; // [esp+30h] [ebp-8h]

  v14 = a2;
  if ( Lexer_TokenExpect(2) != -1
    && Lexer_ParseValueList(1, value1, 1, a3)
    && Lexer_ParseValueList(2, &value2, 4, a3)
    && (beginCopy = begin, n = *(_DWORD *)(value1[2] + 16), n <= end - begin + 1)
    && n >= 1 )
  {
    theMultifield = multifieldPtr;
    *(_DWORD *)(returnValue + 4) = *(__int16 *)(multifieldPtr + 6 * (begin + n - 1) + 14);
    result = *(signed int **)(theMultifield + 6 * (begin + n - 1) + 16);
    *(_DWORD *)(returnValue + 8) = result;
  }
  else
  {
    *(_DWORD *)(returnValue + 4) = 2;
    result = Str_Intern(aNil_1, beginCopy);
    *(_DWORD *)(returnValue + 8) = result;
  }
  return result;
}
// 4A1B4C: variable 'v5' is possibly undefined

//----- (004A1B60) --------------------------------------------------------
signed int  Rules_SubsetpFunction(int returnValue, double a2)
{
  signed int result; // eax
  int fieldIndex; // ecx
  int fieldOffset; // esi
  int curFieldIndex; // ecx
  _DWORD item2[6]; // [esp-18h] [ebp-40h] BYREF
  int item1; // [esp+0h] [ebp-28h] BYREF
  int item1Value; // [esp+8h] [ebp-20h]
  int item1Begin; // [esp+Ch] [ebp-1Ch]
  int item1End; // [esp+10h] [ebp-18h]
  int returnValueCopy; // [esp+20h] [ebp-8h]

  returnValueCopy = returnValue;
  if ( Lexer_TokenExpect(2) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &item1, 4, a2);
  if ( result )
  {
    result = Lexer_ParseValueList(2, item2, 4, a2);
    if ( result )
    {
      fieldIndex = item1Begin + 1;
      fieldOffset = 6 * (item1Begin + 1) - 6;
      while ( fieldIndex <= item1End + 1 )
      {
        result = Rules_MultifieldFindElementPosition(*(__int16 *)(fieldOffset + item1Value + 14), *(_DWORD *)(fieldOffset + item1Value + 16), item2);
        if ( !result )
          return result;
        fieldOffset += 6;
        fieldIndex = curFieldIndex + 1;
      }
      return 1;
    }
  }
  return result;
}
// 4A1C01: variable 'v5' is possibly undefined

//----- (004A1C10) --------------------------------------------------------
int * Rules_MemberFunction(int returnValue, int a2, double a3)
{
  int *result; // eax
  int item1; // [esp-4h] [ebp-40h] BYREF
  int item1Type; // [esp+0h] [ebp-3Ch]
  int item1Value; // [esp+4h] [ebp-38h]
  _DWORD item2[10]; // [esp+14h] [ebp-28h] BYREF

  item2[8] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_TokenExpect(2);
  if ( result != (int *)-1 )
  {
    Rules_RtnUnknown(1, &item1, a3);
    if ( item1Type == 2 || item1Type == 3 || item1Type == 1 || item1Type == 5 || item1Type == 8 || item1Type == 7 || !item1Type )
    {
      result = (int *)Lexer_ParseValueList(2, item2, 4, a3);
      if ( result )
      {
        result = (int *)Rules_MultifieldFindElementPosition(item1Type, item1Value, item2);
        if ( result )
        {
          *(_DWORD *)(returnValue + 4) = 1;
          result = Rules_AddIntegerValue((signed int)result);
          *(_DWORD *)(returnValue + 8) = result;
        }
      }
    }
    else
    {
      Parser_ReportError(1, (int)aPrimitiveDataT);
      return (int *)Lexer_ErrorRecover(1);
    }
  }
  return result;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (004A1CF0) --------------------------------------------------------
int  Rules_MultifieldFindElementPosition(int searchType, int searchValue, _DWORD *theMultifield)
{
  int length; // ebx
  int position; // edx
  int i; // eax

  length = theMultifield[4] - theMultifield[3] + 1;
  position = 0;
  if ( length <= 0 )
    return 0;
  for ( i = theMultifield[2] + 6 * theMultifield[3]; searchValue != *(_DWORD *)(i + 16) || searchType != *(__int16 *)(i + 14); i += 6 )
  {
    if ( ++position >= length )
      return 0;
  }
  return position + 1;
}
