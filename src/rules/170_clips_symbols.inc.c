/* CLIPS symbols, lookup, evaluation, and shared rule-engine services.
 * Original function-marker range: 0x004A0080..0x004ACA00.
 * Included by clash95.c; not a standalone translation unit. */

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
  int v5; // [esp+14h] [ebp-8h]

  v5 = returnValue;
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
  int v5; // [esp+14h] [ebp-8h]

  v5 = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &item, 1, a2);
  if ( result )
    return *(_DWORD *)(itemValue + 16) == 2 * (*(_DWORD *)(itemValue + 16) / 2);
  return result;
}

//----- (004A0240) --------------------------------------------------------
signed int Rules_RegisterArithmeticFunctions()
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
  int v5; // eax
  double newFtotal; // st6
  int v7; // ebx
  int *result; // eax
  double v9; // [esp-8h] [ebp-4Ch]
  _DWORD theArgument[2]; // [esp+0h] [ebp-44h] BYREF
  int argValuePtr; // [esp+8h] [ebp-3Ch]
  double ftotal; // [esp+18h] [ebp-2Ch]
  int returnValueCopy; // [esp+20h] [ebp-24h]
  int i; // [esp+24h] [ebp-20h]
  signed int v15; // [esp+28h] [ebp-1Ch]

  returnValueCopy = returnValue;
  ltotal = 1;
  useFloatTotal = 0;
  ftotal = 1.0;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 1; theExpression; ++i )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, useFloatTotal, theArgument, a2, i);
    if ( v5 )
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
      v15 = ltotal;
      newFtotal = (double)ltotal * *(double *)(argValuePtr + 16);
      useFloatTotal = 1;
    }
    ftotal = newFtotal;
  }
  if ( useFloatTotal )
  {
    v9 = ftotal;
    v7 = returnValueCopy;
    *(_DWORD *)(returnValueCopy + 4) = 0;
    result = (int *)Rules_AddDoubleValue(v9);
  }
  else
  {
    *(_DWORD *)(returnValueCopy + 4) = 1;
    v7 = returnValueCopy;
    result = Rules_AddIntegerValue(ltotal);
  }
  *(_DWORD *)(v7 + 8) = result;
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
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int *result; // eax
  double v10; // [esp-8h] [ebp-4Ch]
  int theArgument; // [esp+0h] [ebp-44h] BYREF
  int argType; // [esp+4h] [ebp-40h]
  int argValuePtr; // [esp+8h] [ebp-3Ch]
  double ftotal; // [esp+18h] [ebp-2Ch]
  int returnValueCopy; // [esp+20h] [ebp-24h]
  int argIndex; // [esp+24h] [ebp-20h]
  signed int v17; // [esp+28h] [ebp-1Ch]

  returnValueCopy = returnValue;
  ltotal = 0;
  useFloatTotal = 0;
  ftotal = 0.0;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  argIndex = 1;
  if ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, 0, &theArgument, a2, 1);
    if ( v6 )
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
      v7 = *(_DWORD *)(argValuePtr + 20);
      LODWORD(ftotal) = *(_DWORD *)(argValuePtr + 16);
      HIDWORD(ftotal) = v7;
    }
    ++argIndex;
  }
  while ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, useFloatTotal, &theArgument, a2, argIndex);
    if ( v5 )
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
        v17 = ltotal;
        useFloatTotal = 1;
        ftotal = (double)ltotal - *(double *)(argValuePtr + 16);
      }
      ++argIndex;
    }
  }
  if ( useFloatTotal )
  {
    v10 = ftotal;
    v8 = returnValueCopy;
    *(_DWORD *)(returnValueCopy + 4) = 0;
    result = (int *)Rules_AddDoubleValue(v10);
  }
  else
  {
    *(_DWORD *)(returnValueCopy + 4) = 1;
    v8 = returnValueCopy;
    result = Rules_AddIntegerValue(ltotal);
  }
  *(_DWORD *)(v8 + 8) = result;
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
  int v5; // ebx
  int *result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  BOOL isDivideByZero; // eax
  int v11; // ebx
  double v12; // [esp-8h] [ebp-4Ch]
  int theArgument; // [esp+0h] [ebp-44h] BYREF
  int argType; // [esp+4h] [ebp-40h]
  int argValuePtr; // [esp+8h] [ebp-3Ch]
  double ftotal; // [esp+18h] [ebp-2Ch]
  int returnValueCopy; // [esp+20h] [ebp-24h]
  int argIndex; // [esp+24h] [ebp-20h]
  signed int v19; // [esp+28h] [ebp-1Ch]

  returnValueCopy = returnValue;
  ltotal = 1;
  useFloatTotal = g_Rules_AutoFloatDividendEnabled;
  ftotal = 1.0;
  theExpression = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  argIndex = 1;
  if ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, g_Rules_AutoFloatDividendEnabled, &theArgument, a2, 1);
    if ( v7 )
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
      v8 = *(_DWORD *)(argValuePtr + 20);
      LODWORD(ftotal) = *(_DWORD *)(argValuePtr + 16);
      HIDWORD(ftotal) = v8;
    }
    ++argIndex;
  }
  while ( theExpression )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)theExpression, useFloatTotal, &theArgument, a2, argIndex);
    if ( v9 )
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
      v11 = returnValueCopy;
      *(_DWORD *)(returnValueCopy + 4) = 0;
      result = (int *)Rules_AddDoubleValue(1.0);
      *(_DWORD *)(v11 + 8) = result;
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
        v19 = ltotal;
        useFloatTotal = 1;
        ftotal = (double)ltotal / *(double *)(argValuePtr + 16);
      }
      ++argIndex;
    }
  }
  if ( useFloatTotal )
  {
    v12 = ftotal;
    v5 = returnValueCopy;
    *(_DWORD *)(returnValueCopy + 4) = 0;
    result = (int *)Rules_AddDoubleValue(v12);
  }
  else
  {
    *(_DWORD *)(returnValueCopy + 4) = 1;
    v5 = returnValueCopy;
    result = Rules_AddIntegerValue(ltotal);
  }
  *(_DWORD *)(v5 + 8) = result;
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
  int v3; // eax
  double v4; // st6
  int v5; // eax
  double v6; // st6
  double v7; // st6
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
    if ( v3 )
      theExpression = *(_DWORD *)(theExpression + 10);
    else
      theExpression = 0;
    if ( argType == 1 )
    {
      total = *(_DWORD *)(argValuePtr + 16);
    }
    else
    {
      v4 = *(double *)(argValuePtr + 16);
      _CHP(theArgument, argType);
      total = (int)v4;
    }
    argIndex = 2;
  }
  while ( theExpression )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)theExpression, 0, &theArgument, result, argIndex);
    if ( v5 )
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
      v6 = *(double *)(argValuePtr + 16);
      _CHP(theArgument, 0);
      theNumber = (int)v6;
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
      v7 = *(double *)(argValuePtr + 16);
      _CHP(theArgument, argType);
      v11 = (int)v7;
      total /= (int)v7;
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
  int v3; // ecx
  int theValue; // [esp-4h] [ebp-24h] BYREF
  __int64 typeValuePair; // [esp+0h] [ebp-20h]
  int v7; // [esp+18h] [ebp-8h]

  v7 = returnValue;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, &theValue, a2);
    g_Rules_AutoFloatDividendEnabled = typeValuePair != __PAIR64__(g_ClipsFalseSymbol, 2);
  }
  return v3;
}
// 4A0A32: variable 'v3' is possibly undefined
// 51ACD4: using guessed type int dword_51ACD4;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A0A80) --------------------------------------------------------
int Rules_GetAutoFloatDividendCommand()
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
signed int Rules_RegisterMultifieldFunctions()
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
  _BYTE *v17; // edx
  char *spacePtr; // eax
  int v20; // edx
  _BYTE *integerString; // eax
  _BYTE *v22; // edx
  int strOffset; // eax
  char *srcString; // ecx
  char *closingQuotePtr; // ebp
  char ch; // bl
  char *v28; // edx
  __int16 lexemeType; // bx
  char *wordString; // eax
  int writeIndex; // ecx
  char *v32; // edx
  int v34; // eax
  char *instanceNameString; // eax
  int instWriteIndex; // ecx
  char *v37; // edx
  int v39; // eax
  char *symbolString; // eax
  int internedSymbol; // ecx
  int value; // [esp+0h] [ebp-3Ch] BYREF
  int v44; // [esp+8h] [ebp-34h]
  int beginIndex; // [esp+Ch] [ebp-30h]
  int endIndex; // [esp+10h] [ebp-2Ch]
  char *afterBracketPtr; // [esp+18h] [ebp-24h]
  int fieldPos; // [esp+1Ch] [ebp-20h]
  int curField; // [esp+20h] [ebp-1Ch]

  totalSize = 0;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, &value, 4, a1) )
    return Str_Intern(g_Rules_ImplodeEmptyResult, v1);
  fieldIndex = beginIndex + 1;
  theMultifield = v44;
  fieldPtr = v44 + 6 * (beginIndex + 1) - 6;
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
            *v22++ = *integerString;
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
          v28 = &retStr[strOffset];
          ++srcString;
          ++strOffset;
          *v28 = ch;
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
            v32 = afterBracketPtr;
            do
            {
              *v32++ = *wordString;
              ++writeIndex;
            }
            while ( *++wordString );
          }
          v34 = writeIndex;
          bufOffset = writeIndex + 1;
          retStr[v34] = 93;
        }
        else if ( lexemeType == 7 )
        {
          instanceNameString = *(char **)(*(_DWORD *)(*(_DWORD *)(curField + 16) + 28) + 16);
          retStr[bufOffset] = 91;
          instWriteIndex = bufOffset + 1;
          if ( *instanceNameString )
          {
            v37 = afterBracketPtr;
            do
            {
              *v37++ = *instanceNameString;
              ++instWriteIndex;
            }
            while ( *++instanceNameString );
          }
          v39 = instWriteIndex;
          bufOffset = instWriteIndex + 1;
          retStr[v39] = 93;
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
          *v17++ = *floatString;
          ++bufOffset;
        }
        while ( *++floatString );
      }
    }
    spacePtr = &retStr[bufOffset];
    v20 = fieldPos;
    ++bufOffset;
    *spacePtr = 32;
    fieldCursor = curField + 6;
    fieldPos = v20 + 1;
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
  int v7; // edx
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
  v7 = offset;
  subValue[2] = theList;
  result = (_DWORD *)(v7 + end - 2);
  subValue[4] = result;
  subValue[3] = v7 + start - 2;
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
  int v5; // ecx
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
    && (v5 = begin, n = *(_DWORD *)(value1[2] + 16), n <= end - begin + 1)
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
    result = Str_Intern(aNil_1, v5);
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
  int v5; // ecx
  _DWORD item2[6]; // [esp-18h] [ebp-40h] BYREF
  int item1; // [esp+0h] [ebp-28h] BYREF
  int item1Value; // [esp+8h] [ebp-20h]
  int item1Begin; // [esp+Ch] [ebp-1Ch]
  int item1End; // [esp+10h] [ebp-18h]
  int v11; // [esp+20h] [ebp-8h]

  v11 = returnValue;
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
        fieldIndex = v5 + 1;
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

//----- (004A1D40) --------------------------------------------------------
int  Rules_ParsePrognMultifieldForm(int top, int infile)
{
  int v4; // edx
  int v5; // ecx
  int fieldVar; // esi
  int parsedArg; // eax
  unsigned int *v8; // edx
  int argList; // edx
  int argListNext; // ecx
  int tmp; // eax
  int newBindList; // ecx
  int prev; // eax
  int fnCallExpr; // eax
  int v16; // ecx
  int parsedExpr; // eax
  int v18; // edx
  int v19; // ecx
  int tkn; // [esp+0h] [ebp-28h] BYREF
  int tknValue; // [esp+4h] [ebp-24h]
  char *tknPrintForm; // [esp+8h] [ebp-20h]
  int oldBindList; // [esp+Ch] [ebp-1Ch]
  int savedBindList; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_5070CC);
  Parser_NextToken(infile, v4);
  fieldVar = 0;
  if ( tkn != 100 )
  {
    parsedArg = Parser_ParseSingleExpression(infile, (__int16 *)&tkn, v5);
    *(_DWORD *)(top + 6) = parsedArg;
    if ( parsedArg )
      goto LABEL_3;
LABEL_17:
    AST_Free(top);
    return 0;
  }
  Parser_NextToken(infile, (int)&tkn);
  if ( tkn != 15 )
  {
    if ( tkn != 2 )
      goto LABEL_25;
    fnCallExpr = Parser_ParseFunctionCallExpr(infile, *(_BYTE **)(tknValue + 16));
    *(_DWORD *)(top + 6) = fnCallExpr;
    if ( fnCallExpr )
      goto LABEL_3;
    goto LABEL_17;
  }
  fieldVar = tknValue;
  IO_OutWriteToken(asc_5070CC);
  parsedExpr = Parser_ParseSingleExpression(infile, 0, v16);
  *(_DWORD *)(top + 6) = parsedExpr;
  if ( !parsedExpr )
    goto LABEL_17;
  Parser_NextToken(infile, (int)&tkn);
  if ( tkn != 101 )
    goto LABEL_25;
  IO_OutNewline();
  IO_OutWriteToken(tknPrintForm);
  IO_OutWriteToken(asc_5070CC);
LABEL_3:
  if ( Rules_ExpressionConstraintsCompatible(*(__int16 **)(top + 6)) )
  {
LABEL_25:
    Parser_ReportSyntaxError();
    AST_Free(top);
    return 0;
  }
  oldBindList = Parser_GetLoopContextStack();
  savedBindList = oldBindList;
  Parser_SetLoopContextStack(0);
  Rules_IncrementIndentDepth(3);
  g_ParserBreakContextFlag = 1;
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  AST_Append(0, (int)&tkn);
  *(_DWORD *)(*(_DWORD *)(top + 6) + 10) = Parser_ParseProgram(infile, v8, 1);
  Rules_DecrementIndentDepth(3);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(tknPrintForm);
  argList = *(_DWORD *)(top + 6);
  argListNext = *(_DWORD *)(argList + 10);
  if ( argListNext )
  {
    tmp = *(_DWORD *)(argList + 10);
    *(_DWORD *)(argList + 10) = *(_DWORD *)(argListNext + 6);
    *(_DWORD *)(tmp + 6) = 0;
    AST_Free(tmp);
    newBindList = Parser_GetLoopContextStack();
    prev = 0;
    if ( newBindList )
    {
      while ( !fieldVar || strcmp_(newBindList, *(_DWORD *)(fieldVar + 16)) )
      {
        prev = newBindList;
        newBindList = *(_DWORD *)(newBindList + 8);
        if ( !newBindList )
          goto LABEL_8;
      }
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(savedBindList);
      Rules_PrintErrorID((int)aMultifun, v18, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRebindFi, v19);
      AST_Free(top);
      return 0;
    }
    else
    {
LABEL_8:
      if ( prev )
        *(_DWORD *)(prev + 8) = savedBindList;
      else
        Parser_SetLoopContextStack(savedBindList);
      if ( fieldVar )
        Rules_RewritePrognFieldRefs(fieldVar, *(_DWORD *)(*(_DWORD *)(top + 6) + 10), 0);
      return top;
    }
  }
  else
  {
    Parser_SetLoopContextStack(oldBindList);
    AST_Free(top);
    return 0;
  }
}
// 4A1D5A: variable 'v4' is possibly undefined
// 4A1D71: variable 'v5' is possibly undefined
// 4A1DDA: variable 'v8' is possibly undefined
// 4A1E3B: variable 'v12' is possibly undefined
// 4A1EDC: variable 'v16' is possibly undefined
// 4A1F6A: variable 'v18' is possibly undefined
// 4A1F79: variable 'v19' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004A1FC0) --------------------------------------------------------
int  Rules_RewritePrognFieldRefs(int fieldVar, int theExp, signed int depth)
{
  int currentExp; // esi
  const char *fieldVarName; // edi
  int result; // eax
  unsigned int flen; // ecx
  signed int nextDepth; // edi
  int fieldVarArg; // eax
  signed int childDepth; // ebx
  int *fieldDepthConstant; // eax
  int *indexDepthConstant; // eax

  currentExp = theExp;
  fieldVarName = *(const char **)(fieldVar + 16);
  result = 0;
  flen = strlen(fieldVarName);
  if ( theExp )
  {
    nextDepth = depth + 1;
    while ( *(_WORD *)currentExp == 15 )
    {
      result = strncmp_(flen, *(_DWORD *)(fieldVar + 16)) == 0;
      if ( !result )
        break;
      if ( *(_BYTE *)(flen + *(_DWORD *)(*(_DWORD *)(currentExp + 2) + 16)) )
      {
        result = strcmp_(flen, aIndex);
        if ( result )
        {
LABEL_9:
          currentExp = *(_DWORD *)(currentExp + 10);
          if ( !currentExp )
            return result;
        }
        else
        {
          *(_WORD *)currentExp = 10;
          *(_DWORD *)(currentExp + 2) = Rules_MakeSymbol(aGetPrognIndex);
          indexDepthConstant = Rules_AddIntegerValue(depth);
          result = AST_NewNode(1, (int)indexDepthConstant);
          *(_DWORD *)(currentExp + 6) = result;
          currentExp = *(_DWORD *)(currentExp + 10);
          if ( !currentExp )
            return result;
        }
      }
      else
      {
        *(_WORD *)currentExp = 10;
        *(_DWORD *)(currentExp + 2) = Rules_MakeSymbol(aGetPrognField);
        fieldDepthConstant = Rules_AddIntegerValue(depth);
        result = AST_NewNode(1, (int)fieldDepthConstant);
        *(_DWORD *)(currentExp + 6) = result;
        currentExp = *(_DWORD *)(currentExp + 10);
        if ( !currentExp )
          return result;
      }
    }
    if ( *(_DWORD *)(currentExp + 6) )
    {
      if ( *(_WORD *)currentExp == 10 && Rules_MakeSymbol(aProgn_0) == *(int ***)(currentExp + 2) )
      {
        fieldVarArg = fieldVar;
        childDepth = nextDepth;
      }
      else
      {
        fieldVarArg = fieldVar;
        childDepth = depth;
      }
      result = Rules_RewritePrognFieldRefs(fieldVarArg, *(_DWORD *)(currentExp + 6), childDepth);
    }
    goto LABEL_9;
  }
  return result;
}
// 4A2035: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004A20F0) --------------------------------------------------------
int  Rules_EvalPrognMultifieldBuiltin(_DWORD *returnValue, double a2)
{
  _DWORD *freeListNode; // edx
  _DWORD *tmpField; // edi
  _DWORD *tmpFieldPtr; // ebp
  int fieldIndex; // ebx
  int fieldOffset; // edi
  __int16 *theExp; // ecx
  int v9; // ecx
  int result; // eax
  int argval; // [esp+0h] [ebp-34h] BYREF
  int argvalValue; // [esp+8h] [ebp-2Ch]
  int argvalBegin; // [esp+Ch] [ebp-28h]
  int argvalEnd; // [esp+10h] [ebp-24h]
  int endIndex; // [esp+18h] [ebp-1Ch]

  freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 64);
  if ( freeListNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *freeListNode;
    tmpField = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    tmpField = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *tmpField = 2;
  tmpField[1] = g_ClipsFalseSymbol;
  tmpField[3] = g_PrognFieldBindingStack;
  g_PrognFieldBindingStack = (int)tmpField;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  tmpFieldPtr = tmpField;
  if ( Lexer_ParseValueList(1, &argval, 4, a2) )
  {
    fieldIndex = argvalBegin + 1;
    endIndex = argvalEnd + 1;
    if ( argvalBegin + 1 > argvalEnd + 1 )
    {
LABEL_18:
      g_ClipsBreakFlag = 0;
    }
    else
    {
      fieldOffset = 6 * fieldIndex - 6;
      while ( 1 )
      {
        *tmpFieldPtr = *(__int16 *)(argvalValue + fieldOffset + 14);
        tmpFieldPtr[1] = *(_DWORD *)(argvalValue + fieldOffset + 16);
        tmpFieldPtr[2] = fieldIndex;
        theExp = *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
        if ( theExp )
          break;
LABEL_17:
        ++fieldIndex;
        fieldOffset += 6;
        if ( fieldIndex > endIndex )
          goto LABEL_18;
      }
      while ( 1 )
      {
        Parser_ParseForm(theExp, returnValue, (int)theExp, a2);
        if ( g_ClipsHaltExecution || g_ClipsBreakFlag || g_ClipsHaltExecutionFlag )
          break;
        theExp = *(__int16 **)(v9 + 10);
        if ( !theExp )
          goto LABEL_17;
      }
      g_ClipsBreakFlag = 0;
      if ( g_ClipsHaltExecution )
      {
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
      }
    }
    g_PrognFieldBindingStack = tmpFieldPtr[3];
    g_ClipsMemFreeListTemp = (int)tmpFieldPtr;
    *tmpFieldPtr = *(_DWORD *)(g_ClipsMemoryTable + 64);
  }
  else
  {
    g_PrognFieldBindingStack = tmpField[3];
    g_ClipsMemFreeListTemp = (int)tmpField;
    *tmpField = *(_DWORD *)(g_ClipsMemoryTable + 64);
  }
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return result;
}
// 4A2266: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A968: using guessed type int dword_51A968;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 51ACD8: using guessed type int dword_51ACD8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A2290) --------------------------------------------------------
int  Rules_EvalGetPrognFieldBuiltin(int returnValue)
{
  int depth; // eax
  _DWORD *i; // edx
  int result; // eax

  depth = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = (_DWORD *)g_PrognFieldBindingStack; depth > 0; i = (_DWORD *)i[3] )
    --depth;
  *(_DWORD *)(returnValue + 4) = *i;
  result = i[1];
  *(_DWORD *)(returnValue + 8) = result;
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51ACD8: using guessed type int dword_51ACD8;

//----- (004A22D0) --------------------------------------------------------
int Rules_EvalGetPrognIndexBuiltin()
{
  int depth; // eax
  int i; // edx

  depth = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = g_PrognFieldBindingStack; depth > 0; i = *(_DWORD *)(i + 12) )
    --depth;
  return *(_DWORD *)(i + 8);
}
// 4A22D0: using guessed type int sub_4A22D0();
// 51A960: using guessed type int dword_51A960;
// 51ACD8: using guessed type int dword_51ACD8;

//----- (004A2310) --------------------------------------------------------
signed int  Rules_MultifieldReplaceRange(
        _DWORD *dst,
        _DWORD *src,
        int rangeEnd,
        int rangeBegin,
        _DWORD *field,
        int functionName)
{
  int srcLength; // eax
  int srcBegin; // ecx
  int absBegin; // ebp
  int replaceCount; // ecx
  int combinedLength; // eax
  int dstByteOffset; // ebx
  int v14; // edx
  int srcIndex; // edx
  int dstIndex; // eax
  int srcByteOffset; // ecx
  int srcMultifield; // eax
  int dstMultifield; // ebp
  __int16 fieldType; // di
  int dstFieldPtr; // ebx
  int fieldIndex; // ecx
  int v24; // ebx
  int v25; // ecx
  int v26; // edx
  int v27; // ebp
  int v28; // ebx
  int dstWritePtr; // [esp+0h] [ebp-34h]
  int srcReadPtr; // [esp+4h] [ebp-30h]
  int dstLength; // [esp+Ch] [ebp-28h]
  int v32; // [esp+14h] [ebp-20h]
  int absEnd; // [esp+18h] [ebp-1Ch]
  int v35; // [esp+1Ch] [ebp-18h]
  int v37; // [esp+24h] [ebp-10h]

  if ( src )
    srcLength = src[4] - src[3] + 1;
  else
    srcLength = 0;
  if ( rangeBegin > rangeEnd || rangeBegin < 1 || rangeEnd < 1 || rangeBegin > srcLength || srcLength < rangeEnd )
  {
    Rules_MultifieldIndexRangeError(rangeBegin, rangeEnd, srcLength);
    return 0;
  }
  else
  {
    srcBegin = src[3];
    absBegin = srcBegin + rangeBegin - 1;
    absEnd = srcBegin + rangeEnd - 1;
    replaceCount = rangeEnd - rangeBegin + 1;
    if ( field[1] == 4 )
      combinedLength = field[4] - field[3] + 1 + srcLength;
    else
      combinedLength = srcLength + 1;
    dstLength = combinedLength - replaceCount;
    dst[1] = 4;
    dst[3] = 0;
    dstByteOffset = 0;
    dst[2] = Rules_CreateEphemeralMultifield(combinedLength - replaceCount);
    dst[4] = dstLength - 1;
    srcIndex = *(_DWORD *)(v14 + 12);
    v32 = 6 * absBegin;
    dstIndex = 0;
    srcByteOffset = 6 * srcIndex;
    while ( 1 )
    {
      v35 = dstIndex + 1;
      if ( srcByteOffset >= v32 )
        break;
      srcMultifield = src[2];
      dstMultifield = dst[2];
      fieldType = *(_WORD *)(srcByteOffset + srcMultifield + 14);
      srcByteOffset += 6;
      *(_WORD *)(dstByteOffset + dstMultifield + 14) = fieldType;
      dstByteOffset += 6;
      ++srcIndex;
      *(_DWORD *)(dstByteOffset + dstMultifield + 10) = *(_DWORD *)(srcByteOffset + srcMultifield + 10);
      dstIndex = v35;
    }
    if ( field[1] == 4 )
    {
      fieldIndex = field[3];
      if ( fieldIndex <= field[4] )
      {
        v24 = 6 * fieldIndex;
        v37 = 6 * dstIndex;
        do
        {
          dstWritePtr = dst[2] + 14 + v37;
          srcReadPtr = v24 + field[2] + 14;
          *(_WORD *)dstWritePtr = *(_WORD *)srcReadPtr;
          *(_DWORD *)(dstWritePtr + 2) = *(_DWORD *)(srcReadPtr + 2);
          v37 += 6;
          ++fieldIndex;
          ++dstIndex;
          v24 += 6;
        }
        while ( fieldIndex <= field[4] );
      }
    }
    else
    {
      dstFieldPtr = dst[2] + 14 + dstByteOffset;
      *(_WORD *)dstFieldPtr = *((_WORD *)field + 2);
      ++dstIndex;
      *(_DWORD *)(dstFieldPtr + 2) = field[2];
    }
    while ( srcIndex < absEnd )
      ++srcIndex;
    if ( dstIndex < dstLength )
    {
      v25 = 6 * (srcIndex + 1);
      v26 = 6 * dstIndex;
      do
      {
        v27 = src[2];
        v28 = dst[2];
        *(_WORD *)(v26 + v28 + 14) = *(_WORD *)(v25 + v27 + 14);
        v26 += 6;
        ++dstIndex;
        *(_DWORD *)(v26 + v28 + 10) = *(_DWORD *)(v25 + v27 + 16);
        v25 += 6;
      }
      while ( v26 < 6 * dstLength );
    }
    return 1;
  }
}
// 4A23D8: variable 'v14' is possibly undefined

//----- (004A2580) --------------------------------------------------------
signed int  Rules_MultifieldInsertRange(_DWORD *dst, _DWORD *src, _DWORD *theField, int theIndex, int functionName)
{
  int srcLength; // eax
  int v8; // edx
  int maxInsertPos; // eax
  int v12; // eax
  signed int dstLength; // edx
  int v14; // edx
  int insertOffset; // ebp
  int srcIndex; // edx
  int dstIndex; // eax
  int v18; // ecx
  int dstFieldPtr; // ebp
  int v20; // ecx
  int v21; // ecx
  int v22; // ebp
  int fieldIndex; // ecx
  int v24; // ebp
  int v25; // [esp+4h] [ebp-2Ch]
  int v26; // [esp+4h] [ebp-2Ch]
  int v27; // [esp+4h] [ebp-2Ch]
  int insertPos; // [esp+8h] [ebp-28h]
  int insertSlot; // [esp+8h] [ebp-28h]
  int v30; // [esp+Ch] [ebp-24h]
  int v32; // [esp+14h] [ebp-1Ch]
  int v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int v35; // [esp+20h] [ebp-10h]

  insertPos = theIndex;
  if ( src )
    srcLength = src[4] - src[3] + 1;
  else
    srcLength = 0;
  v8 = srcLength;
  maxInsertPos = srcLength + 1;
  if ( theIndex < 1 )
  {
    Rules_MultifieldIndexRangeError(theIndex, theIndex, maxInsertPos);
    return 0;
  }
  else
  {
    if ( maxInsertPos < theIndex )
      insertPos = maxInsertPos;
    dst[1] = 4;
    dst[3] = 0;
    if ( src )
    {
      if ( theField[1] == 4 )
        dstLength = theField[4] - theField[3] + 1 + v8;
      else
        dstLength = v8 + 1;
      dst[2] = Rules_CreateEphemeralMultifield(dstLength);
      insertOffset = insertPos - 1;
      dst[4] = v14 - 1;
      insertSlot = insertOffset;
      srcIndex = src[3];
      dstIndex = 0;
      if ( srcIndex < insertOffset )
      {
        v35 = 0;
        v18 = 6 * srcIndex;
        v30 = 6 * insertOffset;
        do
        {
          dstFieldPtr = dst[2] + 14 + v35;
          v25 = v18 + src[2] + 14;
          *(_WORD *)dstFieldPtr = *(_WORD *)v25;
          ++dstIndex;
          ++srcIndex;
          *(_DWORD *)(dstFieldPtr + 2) = *(_DWORD *)(v25 + 2);
          v18 += 6;
          v35 += 6;
        }
        while ( v18 < v30 );
      }
      if ( theField[1] == 4 )
      {
        fieldIndex = theField[3];
        if ( fieldIndex <= theField[4] )
        {
          v32 = 6 * fieldIndex;
          v33 = 6 * dstIndex;
          do
          {
            v27 = theField[2] + 14 + v32;
            v24 = dst[2] + 14 + v33;
            *(_WORD *)v24 = *(_WORD *)v27;
            *(_DWORD *)(v24 + 2) = *(_DWORD *)(v27 + 2);
            v32 += 6;
            ++fieldIndex;
            v33 += 6;
            ++dstIndex;
          }
          while ( fieldIndex <= theField[4] );
        }
      }
      else
      {
        v20 = dst[2] + 14 + 6 * insertSlot;
        *(_WORD *)v20 = *((_WORD *)theField + 2);
        ++dstIndex;
        *(_DWORD *)(v20 + 2) = theField[2];
      }
      v21 = 6 * srcIndex;
      v34 = 6 * dstIndex;
      while ( srcIndex <= src[4] )
      {
        v22 = dst[2] + 14 + v34;
        v26 = v21 + src[2] + 14;
        *(_WORD *)v22 = *(_WORD *)v26;
        ++dstIndex;
        *(_DWORD *)(v22 + 2) = *(_DWORD *)(v26 + 2);
        ++srcIndex;
        v21 += 6;
        v34 += 6;
      }
    }
    else if ( theField[1] == 4 )
    {
      Rules_AssignMultifieldRangeCopy(dst, (int)theField);
      Rules_RegisterEphemeralMultifield(dst[2]);
    }
    else
    {
      dst[2] = Rules_CreateEphemeralMultifield(0);
      dst[4] = 0;
      v12 = dst[2];
      *(_WORD *)(v12 + 14) = *((_WORD *)theField + 2);
      *(_DWORD *)(v12 + 16) = theField[2];
    }
    return 1;
  }
}
// 4A2655: variable 'v14' is possibly undefined

//----- (004A2810) --------------------------------------------------------
signed int  Rules_MultifieldIndexRangeError(int rangeBegin, int rangeEnd, int fieldCount)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int indexToPrint; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ecx
  int v15; // ecx

  Rules_PrintErrorID((int)aMultifun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMultifieldInde, v5);
  if ( rangeBegin == rangeEnd )
  {
    indexToPrint = rangeBegin;
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aRange, v6);
    Rules_PrintLongInteger(v7, rangeBegin);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__, v8);
    indexToPrint = rangeEnd;
  }
  Rules_PrintLongInteger(v6, indexToPrint);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutOfRange1__, v10);
  Rules_PrintLongInteger(v11, fieldCount);
  if ( !v12 )
    return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__16, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_0, v12);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v14, v14);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__16, v15);
}
// 4A2834: variable 'v5' is possibly undefined
// 4A2847: variable 'v6' is possibly undefined
// 4A2853: variable 'v7' is possibly undefined
// 4A2862: variable 'v8' is possibly undefined
// 4A287D: variable 'v10' is possibly undefined
// 4A2889: variable 'v11' is possibly undefined
// 4A2890: variable 'v12' is possibly undefined
// 4A28C4: variable 'v14' is possibly undefined
// 4A28D3: variable 'v15' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A28E0) --------------------------------------------------------
signed int  Rules_MultifieldDeleteRange(_DWORD *dst, _DWORD *src, int rangeEnd, int rangeBegin, int functionName)
{
  int srcLength; // eax
  int absBegin; // edi
  signed int dstLength; // eax
  int v9; // edx
  int srcIndex; // edx
  int dstIndex; // eax
  int dstByteOffset; // ebx
  int srcByteOffset; // ecx
  int v14; // edx
  _DWORD *emptyMultifield; // eax
  int v17; // ecx
  int v18; // edx
  int dstFieldPtr; // ebp
  int srcMultifield; // ebx
  int fieldValue; // ebx
  int v22; // [esp+0h] [ebp-24h]
  int v23; // [esp+4h] [ebp-20h]
  int absEnd; // [esp+10h] [ebp-14h]

  if ( src )
    srcLength = src[4] - src[3] + 1;
  else
    srcLength = 0;
  if ( rangeEnd < rangeBegin || rangeBegin < 1 || rangeEnd < 1 || srcLength < rangeBegin || srcLength < rangeEnd )
  {
    Rules_MultifieldIndexRangeError(rangeBegin, rangeEnd, srcLength);
    return 0;
  }
  dst[1] = 4;
  dst[3] = 0;
  if ( !srcLength )
  {
    emptyMultifield = Rules_CreateEphemeralMultifield(0);
    dst[4] = -1;
    v14 = 1;
    dst[2] = emptyMultifield;
    return v14;
  }
  absBegin = rangeBegin + src[3] - 1;
  absEnd = rangeEnd + src[3] - 1;
  dstLength = srcLength - (rangeEnd + src[3] - absBegin);
  dst[4] = dstLength - 1;
  dst[2] = Rules_CreateEphemeralMultifield(dstLength);
  srcIndex = *(_DWORD *)(v9 + 12);
  dstIndex = 0;
  if ( srcIndex < absBegin )
  {
    dstByteOffset = 0;
    srcByteOffset = 6 * srcIndex;
    do
    {
      v22 = dstByteOffset + dst[2] + 14;
      v23 = srcByteOffset + src[2] + 14;
      ++dstIndex;
      *(_WORD *)v22 = *(_WORD *)v23;
      ++srcIndex;
      srcByteOffset += 6;
      *(_DWORD *)(v22 + 2) = *(_DWORD *)(v23 + 2);
      dstByteOffset += 6;
    }
    while ( srcByteOffset < 6 * absBegin );
  }
  while ( srcIndex < absEnd )
    ++srcIndex;
  if ( dstIndex <= dst[4] )
  {
    v17 = 6 * (srcIndex + 1);
    v18 = 6 * dstIndex;
    do
    {
      dstFieldPtr = dst[2] + 14 + v18;
      srcMultifield = src[2];
      *(_WORD *)dstFieldPtr = *(_WORD *)(v17 + srcMultifield + 14);
      fieldValue = *(_DWORD *)(v17 + srcMultifield + 16);
      v17 += 6;
      *(_DWORD *)(dstFieldPtr + 2) = fieldValue;
      ++dstIndex;
      v18 += 6;
    }
    while ( dstIndex <= dst[4] );
  }
  return 1;
}
// 4A2988: variable 'v9' is possibly undefined

//----- (004A2AB0) --------------------------------------------------------
signed int Rules_RegisterStringBuiltins()
{
  Rules_RegisterHostFunction(aStrCat, 107, (int)aStrcatfunction, (int)Rules_StrCatBuiltin, (int)a1_1);
  Rules_RegisterHostFunction(aSymCat, 107, (int)aSymcatfunction, (int)Rules_SymCatBuiltin, (int)a1_1);
  Rules_RegisterHostFunction(aStrLength, 108, (int)aStrlengthfunct, (int)Rules_StrLengthBuiltin, (int)a11j);
  Rules_RegisterHostFunction(aStrCompare, 108, (int)aStrcomparefunc, (int)Rules_StrCompareBuiltin, (int)a23Jji);
  Rules_RegisterHostFunction(aUpcase, 106, (int)aUpcasefunction, (int)Rules_UpcaseBuiltin, (int)a11j);
  Rules_RegisterHostFunction(aLowcase, 106, (int)aLowcasefunctio, (int)Rules_LowcaseBuiltin, (int)a11j);
  Rules_RegisterHostFunction(aSubString, 115, (int)aSubstringfunct, (int)Rules_SubStringBuiltin, (int)a33Iij);
  Rules_RegisterHostFunction(aStrIndex, 117, (int)aStrindexfuncti, (int)Rules_StrIndexBuiltin, (int)a22j);
  Rules_RegisterHostFunction(aEval, 117, (int)aEvalfunction, (int)Rules_EvalBuiltin, (int)a11k_1);
  return Rules_RegisterHostFunction(aBuild, 98, (int)aBuildfunction, (int)Rules_BuildBuiltin, (int)a11k_1);
}

//----- (004A2BC0) --------------------------------------------------------
signed int  Rules_StrCatBuiltin(int returnValue, int a2, double a3)
{
  return Rules_ConcatBuiltinCore(returnValue, 3, a2, a3);
}

//----- (004A2C00) --------------------------------------------------------
signed int  Rules_SymCatBuiltin(int returnValue, int a2, double a3)
{
  return Rules_ConcatBuiltinCore(returnValue, 2, a2, a3);
}

//----- (004A2C40) --------------------------------------------------------
signed int  Rules_ConcatBuiltinCore(int returnValue, int returnType, int a3, double a4)
{
  signed int *v4; // eax
  int v5; // edx
  _BYTE *v6; // eax
  int argIndex; // esi
  int v8; // edx
  _BYTE *stringArrayCursor; // ebp
  char *symbolString; // eax
  int v11; // ecx
  signed int *internedSymbol; // eax
  unsigned int lengthWithNull; // kr04_4
  int writeOffset; // ebx
  int stringIndex; // ebp
  int segmentLength; // ecx
  char *theString; // esi
  int v18; // edx
  const char **readCursor; // edx
  signed int *v20; // eax
  int v21; // edx
  char *v23; // ecx
  int theArg; // [esp+0h] [ebp-40h] BYREF
  int theArgType; // [esp+4h] [ebp-3Ch]
  int theArgValue; // [esp+8h] [ebp-38h]
  const char **arrayOfStrings; // [esp+18h] [ebp-28h]
  int v28; // [esp+1Ch] [ebp-24h]
  char *functionName; // [esp+20h] [ebp-20h]
  unsigned int totalSize; // [esp+24h] [ebp-1Ch]
  int numArgs; // [esp+28h] [ebp-18h]

  v28 = returnValue;
  *(_DWORD *)(returnValue + 4) = returnType;
  if ( returnType == 3 )
  {
    v4 = Str_Intern(g_Rules_EmptyStringLiteral, (int)aStrCat);
    functionName = v23;
  }
  else
  {
    functionName = aSymCat;
    v4 = Str_Intern(aNil_4, a3);
  }
  *(_DWORD *)(v5 + 8) = v4;
  numArgs = Rules_RtnArgCount();
  v6 = Mem_SmallBlockAllocZeroed(4 * numArgs);
  totalSize = 1;
  argIndex = 1;
  arrayOfStrings = (const char **)v6;
  if ( v8 < 1 )
  {
LABEL_11:
    writeOffset = 0;
    stringIndex = 0;
    theString = (char *)Mem_SmallBlockAlloc(totalSize);
    if ( v18 > 0 )
    {
      readCursor = arrayOfStrings;
      do
      {
        sprintf_(&theString[writeOffset], "%s", *readCursor);
        ++stringIndex;
        segmentLength = strlen(*(readCursor - 1));
        writeOffset += segmentLength;
      }
      while ( stringIndex < numArgs );
    }
    v20 = Str_Intern(theString, segmentLength);
    *(_DWORD *)(v21 + 8) = v20;
    Mem_SmallBlockFree(theString, totalSize);
  }
  else
  {
    stringArrayCursor = v6 + 4;
    while ( 1 )
    {
      Rules_RtnUnknown(argIndex, &theArg, a4);
      switch ( theArgType )
      {
        case 0:
          symbolString = (char *)Rules_FloatToSymbol(theArgType, *(double *)(theArgValue + 16));
          goto LABEL_7;
        case 1:
          symbolString = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(theArgValue + 16));
LABEL_7:
          internedSymbol = Str_Intern(symbolString, v11);
          goto LABEL_8;
        case 2:
        case 3:
        case 8:
          internedSymbol = (signed int *)theArgValue;
LABEL_8:
          *((_DWORD *)stringArrayCursor - 1) = internedSymbol[4];
          break;
        default:
          Parser_ReportError(argIndex, (int)aStringInstance);
          Lexer_ErrorRecover(1);
          break;
      }
      if ( g_ClipsEvaluationError )
        break;
      lengthWithNull = strlen(*((const char **)stringArrayCursor - 1)) + 1;
      stringArrayCursor += 4;
      ++argIndex;
      totalSize += lengthWithNull - 1;
      if ( argIndex > numArgs )
        goto LABEL_11;
    }
  }
  return Mem_SmallBlockFree(arrayOfStrings, 4 * numArgs);
}
// 4A2C6F: variable 'v5' is possibly undefined
// 4A2C9A: variable 'v8' is possibly undefined
// 4A2CCF: variable 'v11' is possibly undefined
// 4A2D1F: variable 'v18' is possibly undefined
// 4A2D27: variable 'v19' is possibly undefined
// 4A2D66: variable 'v16' is possibly undefined
// 4A2D6B: variable 'v21' is possibly undefined
// 4A2DA9: variable 'v23' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A964: using guessed type int dword_51A964;

//----- (004A2DF0) --------------------------------------------------------
int  Rules_StrLengthBuiltin(int returnValue, double a2)
{
  int result; // eax
  _DWORD theValue[9]; // [esp-8h] [ebp-24h] BYREF

  theValue[7] = returnValue;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    if ( Lexer_ParseValueList(1, theValue, 111, a2) )
      return strlen(*(const char **)(theValue[2] + 16));
    else
      return -1;
  }
  return result;
}

//----- (004A2E60) --------------------------------------------------------
signed int * Rules_UpcaseBuiltin(int returnValue, double a2)
{
  int v3; // ecx
  signed int slen; // kr04_4
  signed int charIndex; // ebx
  char *nsptr; // eax
  _BYTE *osptr; // edx
  char *writePtr; // ecx
  int ch; // eax
  int v10; // edx
  signed int *result; // eax
  _DWORD item[7]; // [esp+0h] [ebp-30h] BYREF
  char *newString; // [esp+1Ch] [ebp-14h]

  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, item, 111, a2) )
  {
    *(_DWORD *)(returnValue + 4) = 3;
    result = Str_Intern(g_Rules_EmptyStringLiteral, v3);
    *(_DWORD *)(returnValue + 8) = result;
  }
  else
  {
    slen = strlen(*(const char **)(item[2] + 16)) + 1;
    charIndex = 0;
    nsptr = (char *)Mem_SmallBlockAlloc(slen);
    newString = nsptr;
    if ( slen > 0 )
    {
      writePtr = nsptr;
      do
      {
        if ( IsTable[(unsigned __int8)(*osptr + 1)] >= 0 )
        {
          LOBYTE(ch) = *osptr;
        }
        else
        {
          ch = toupper_(writePtr);
          item[6] = ch;
        }
        *writePtr++ = ch;
        ++charIndex;
        ++osptr;
      }
      while ( charIndex < slen );
    }
    *(_DWORD *)(returnValue + 4) = item[1];
    *(_DWORD *)(returnValue + 8) = Str_Intern(newString, (int)writePtr);
    return (signed int *)Mem_SmallBlockFree(newString, v10);
  }
  return result;
}
// 4A2ECC: variable 'v7' is possibly undefined
// 4A2EED: variable 'v8' is possibly undefined
// 4A2F0F: variable 'v10' is possibly undefined
// 4A2F2A: variable 'v3' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004A2F40) --------------------------------------------------------
signed int * Rules_LowcaseBuiltin(int returnValue, double a2)
{
  int v3; // ecx
  signed int slen; // kr04_4
  signed int charIndex; // ebx
  char *nsptr; // eax
  _BYTE *osptr; // edx
  char *writePtr; // ecx
  int ch; // eax
  int v10; // edx
  signed int *result; // eax
  _DWORD item[7]; // [esp+0h] [ebp-30h] BYREF
  char *newString; // [esp+1Ch] [ebp-14h]

  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, item, 111, a2) )
  {
    *(_DWORD *)(returnValue + 4) = 3;
    result = Str_Intern(g_Rules_EmptyStringLiteral, v3);
    *(_DWORD *)(returnValue + 8) = result;
  }
  else
  {
    slen = strlen(*(const char **)(item[2] + 16)) + 1;
    charIndex = 0;
    nsptr = (char *)Mem_SmallBlockAlloc(slen);
    newString = nsptr;
    if ( slen > 0 )
    {
      writePtr = nsptr;
      do
      {
        if ( (IsTable[(unsigned __int8)(*osptr + 1)] & 0x40) != 0 )
        {
          ch = tolower_(writePtr, osptr);
          item[6] = ch;
        }
        else
        {
          LOBYTE(ch) = *osptr;
        }
        *writePtr++ = ch;
        ++charIndex;
        ++osptr;
      }
      while ( charIndex < slen );
    }
    *(_DWORD *)(returnValue + 4) = item[1];
    *(_DWORD *)(returnValue + 8) = Str_Intern(newString, (int)writePtr);
    return (signed int *)Mem_SmallBlockFree(newString, v10);
  }
  return result;
}
// 4A2FAC: variable 'v7' is possibly undefined
// 4A2FCD: variable 'v8' is possibly undefined
// 4A2FEF: variable 'v10' is possibly undefined
// 4A300A: variable 'v3' is possibly undefined
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004A3020) --------------------------------------------------------
signed int  Rules_StrCompareBuiltin(int returnValue, double a2)
{
  int numArgs; // esi
  signed int result; // eax
  int v4; // ecx
  int v5; // ecx
  double v6; // st7
  int arg3; // [esp-4h] [ebp-5Ch] BYREF
  int arg3Type; // [esp+0h] [ebp-58h]
  int arg3Value; // [esp+4h] [ebp-54h]
  int arg1; // [esp+14h] [ebp-44h] BYREF
  int arg2; // [esp+2Ch] [ebp-2Ch] BYREF
  int arg2Value; // [esp+34h] [ebp-24h]
  int maxChars; // [esp+44h] [ebp-14h]
  int v14; // [esp+50h] [ebp-8h]

  v14 = returnValue;
  numArgs = Rules_ArgRangeCheck((int)aStrCompare, 3);
  if ( numArgs == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &arg1, 111, a2);
  if ( result )
  {
    result = Lexer_ParseValueList(2, &arg2, 111, a2);
    if ( result )
    {
      if ( numArgs == 3 )
      {
        result = Lexer_ParseValueList(3, &arg3, 1, a2);
        if ( !result )
          return result;
        if ( arg3Type == 1 )
        {
          maxChars = *(_DWORD *)(arg3Value + 16);
        }
        else
        {
          v6 = *(double *)(arg3Value + 16);
          _CHP(arg3, arg3Type);
          maxChars = (int)v6;
        }
        result = strncmp_(v5, *(_DWORD *)(arg2Value + 16));
      }
      else
      {
        result = strcmp_(v4, *(_DWORD *)(arg2Value + 16));
      }
      if ( result < 0 )
      {
        return -1;
      }
      else if ( result > 0 )
      {
        return 1;
      }
    }
  }
  return result;
}
// 4A3097: variable 'v4' is possibly undefined
// 4A30EE: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004A3120) --------------------------------------------------------
signed int * Rules_SubStringBuiltin(double a1)
{
  int v1; // ecx
  int start; // ebp
  int end; // esi
  _DWORD *tempPtr; // eax
  int charIndex; // ecx
  char *returnString; // edi
  char *sourcePtr; // edx
  char ch; // bl
  int v9; // edx
  int v10; // ecx
  int theArgument; // [esp+0h] [ebp-38h] BYREF
  int argType; // [esp+4h] [ebp-34h]
  int argValue; // [esp+8h] [ebp-30h]
  int endRaw; // [esp+18h] [ebp-20h]
  int startRaw; // [esp+1Ch] [ebp-1Ch]

  if ( Lexer_TokenExpect(3) == -1 || !Lexer_ParseValueList(1, &theArgument, 1, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  if ( argType == 1 )
  {
    startRaw = *(_DWORD *)(argValue + 16);
  }
  else
  {
    a1 = *(double *)(argValue + 16);
    _CHP(theArgument, argType);
    startRaw = (int)a1;
  }
  start = startRaw - 1;
  if ( !Lexer_ParseValueList(2, &theArgument, 1, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  if ( argType == 1 )
  {
    endRaw = *(_DWORD *)(argValue + 16);
  }
  else
  {
    a1 = *(double *)(argValue + 16);
    _CHP(theArgument, argType);
    endRaw = (int)a1;
  }
  end = endRaw - 1;
  if ( !Lexer_ParseValueList(3, &theArgument, 111, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  if ( start < 0 )
    start = 0;
  v1 = strlen(*(const char **)(argValue + 16));
  if ( end > v1 )
  {
    v1 = strlen(*(const char **)(argValue + 16));
    end = v1;
  }
  if ( start > end )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  tempPtr = Mem_SmallBlockAlloc(end - start + 2);
  charIndex = start;
  returnString = (char *)tempPtr;
  sourcePtr = (char *)(start + *(_DWORD *)(argValue + 16));
  do
  {
    tempPtr = (_DWORD *)((char *)tempPtr + 1);
    ch = *sourcePtr++;
    ++charIndex;
    *((_BYTE *)tempPtr - 1) = ch;
  }
  while ( charIndex <= end );
  *(_BYTE *)tempPtr = 0;
  Str_Intern(returnString, charIndex);
  Mem_SmallBlockFree(returnString, v9 - start + 2);
  return (signed int *)v10;
}
// 4A323C: variable 'v9' is possibly undefined
// 4A324A: variable 'v10' is possibly undefined
// 4A325B: variable 'v1' is possibly undefined

//----- (004A32A0) --------------------------------------------------------
int * Rules_StrIndexBuiltin(int returnValue, double a2)
{
  int *result; // eax
  const char *strg1; // ebp
  _BYTE *strg2; // esi
  signed int position; // edi
  _BYTE *strg2Ptr; // edx
  int matchLength; // ecx
  char ch; // bh
  const char *v10; // edi
  int v11; // edx
  int v12; // edx
  int theArgument1; // [esp+0h] [ebp-4Ch] BYREF
  int arg1Value; // [esp+8h] [ebp-44h]
  int theArgument2; // [esp+18h] [ebp-34h] BYREF
  int arg2Value; // [esp+20h] [ebp-2Ch]
  int v17; // [esp+30h] [ebp-1Ch]

  v17 = returnValue;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(v17 + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_TokenExpect(2);
  if ( result != (int *)-1 )
  {
    result = (int *)Lexer_ParseValueList(1, &theArgument1, 111, a2);
    if ( result )
    {
      result = (int *)Lexer_ParseValueList(2, &theArgument2, 111, a2);
      if ( result )
      {
        strg1 = *(const char **)(arg1Value + 16);
        strg2 = *(_BYTE **)(arg2Value + 16);
        result = 0;
        if ( strlen(strg1) )
        {
          BYTE1(result) = *strg2;
          position = 1;
          if ( *strg2 )
          {
            while ( 1 )
            {
              result = *(int **)(arg1Value + 16);
              strg2Ptr = strg2;
              matchLength = 0;
              if ( *strg1 )
              {
                do
                {
                  if ( *(_BYTE *)result != *strg2Ptr )
                    break;
                  ++strg2Ptr;
                  ch = *((_BYTE *)result + 1);
                  result = (int *)((char *)result + 1);
                  ++matchLength;
                }
                while ( ch );
              }
              if ( !strg1[matchLength] )
                break;
              ++position;
              if ( !*++strg2 )
                return result;
            }
            *(_DWORD *)(v17 + 4) = 1;
            result = Rules_AddIntegerValue(position);
            *(_DWORD *)(v12 + 8) = result;
          }
        }
        else
        {
          v10 = *(const char **)(arg2Value + 16);
          *(_DWORD *)(v17 + 4) = 1;
          result = Rules_AddIntegerValue(strlen(v10) + 1);
          *(_DWORD *)(v11 + 8) = result;
        }
      }
    }
  }
  return result;
}
// 4A3398: variable 'v11' is possibly undefined
// 4A33BB: variable 'v12' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004A33D0) --------------------------------------------------------
int  Rules_EvalBuiltin(_DWORD *returnValue, int a2, double a3)
{
  int result; // eax
  int v6; // ecx
  _DWORD item[10]; // [esp-8h] [ebp-28h] BYREF

  item[8] = a2;
  if ( Lexer_TokenExpect(1) != -1 && Lexer_ParseValueList(1, item, 111, a3) )
    return Rules_EvalStringCore(v6, returnValue);
  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  return result;
}
// 4A3429: variable 'v6' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004A3440) --------------------------------------------------------
BOOL __fastcall Rules_EvalStringCore(_DWORD theString, _DWORD *returnValue)
{
  double v3; // st7
  const char *v4; // ecx
  BOOL result; // eax
  int ppBufferStatus; // ebx
  int oldBindList; // edi
  __int16 *v8; // edx
  int v9; // ecx
  int top; // ebp
  _WORD *v11; // ecx
  __int16 *v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE logicalNameBuffer[40]; // [esp+0h] [ebp-28h] BYREF

  v3 = sprintf_(logicalNameBuffer, "Eval-%d", ++g_EvalStringRouterCounter);
  if ( IO_OpenStringSource((int)logicalNameBuffer, v4, 0) )
  {
    ppBufferStatus = Rules_GetPPBufferStatus();
    Rules_SetPPBufferStatus(0);
    oldBindList = Parser_GetLoopContextStack();
    Parser_SetLoopContextStack(0);
    top = Parser_ParseSingleExpression((int)logicalNameBuffer, v8, v9);
    Rules_SetPPBufferStatus(ppBufferStatus);
    Parser_FreeLoopContextStack();
    Parser_SetLoopContextStack(oldBindList);
    if ( v11 )
    {
      if ( *v11 == 14 || *v11 == 16 )
      {
        Rules_PrintErrorID((int)aMiscfun_0, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpandMustBe_0, v14);
        Lexer_ErrorRecover(1);
        IO_CloseStringRouter((int)logicalNameBuffer);
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
        AST_Free(top);
        result = 0;
        --g_EvalStringRouterCounter;
      }
      else if ( AST_TreeContainsSpecialTag((int)v11, 0) )
      {
        Rules_PrintErrorID((int)aStrngfun, 2, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSomeVariablesC, v15);
        Lexer_ErrorRecover(1);
        IO_CloseStringRouter((int)logicalNameBuffer);
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
        AST_Free(v16);
        result = 0;
        --g_EvalStringRouterCounter;
      }
      else
      {
        Parser_ParseForm(v12, returnValue, (int)v12, v3);
        --g_EvalStringRouterCounter;
        AST_Free(v13);
        IO_CloseStringRouter((int)logicalNameBuffer);
        return Rules_GetHaltExecutionFlag() == 0;
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      IO_CloseStringRouter((int)logicalNameBuffer);
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
      result = 0;
      --g_EvalStringRouterCounter;
    }
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    result = 0;
    --g_EvalStringRouterCounter;
  }
  return result;
}
// 4A3474: variable 'v4' is possibly undefined
// 4A34C4: variable 'v8' is possibly undefined
// 4A34C4: variable 'v9' is possibly undefined
// 4A34E2: variable 'v11' is possibly undefined
// 4A3510: variable 'v12' is possibly undefined
// 4A3524: variable 'v13' is possibly undefined
// 4A359B: variable 'v14' is possibly undefined
// 4A35FA: variable 'v15' is possibly undefined
// 4A3621: variable 'v16' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];
// 51ACDC: using guessed type int dword_51ACDC;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A3650) --------------------------------------------------------
signed int  Rules_BuildBuiltin(int returnValue, double a2)
{
  signed int result; // eax
  _DWORD theArg[9]; // [esp-8h] [ebp-24h] BYREF

  theArg[7] = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, theArg, 111, a2);
  if ( result )
    return Rules_BuildConstructFromString(*(const char **)(theArg[2] + 16));
  return result;
}

//----- (004A36B0) --------------------------------------------------------
signed int  Rules_BuildConstructFromString(const char *theString)
{
  signed int result; // eax
  signed int errorFlag; // ebx
  int v3; // ecx
  int v4; // edx
  char *ppBuffer; // eax
  int v6; // ecx
  int theToken; // [esp+0h] [ebp-14h] BYREF

  if ( g_Rules_JoinOperationInProgress )
    return 0;
  result = IO_OpenStringSource((int)aBuild, theString, 0);
  if ( result )
  {
    Parser_NextToken((int)aBuild, (int)&theToken);
    if ( theToken != 100 || (Parser_NextToken((int)aBuild, (int)&theToken), theToken != 2) )
    {
      IO_CloseStringRouter((int)aBuild);
      return 0;
    }
    errorFlag = Rules_ParseConstruct();
    IO_CloseStringRouter((int)aBuild);
    if ( v4 == 1 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aError_3, v3);
      ppBuffer = (char *)Rules_GetPPBuffer();
      Output_WriteLongString((signed int)g_IO_LogicalNameTable_WError[0], ppBuffer);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_507374, v6);
    }
    Rules_DestroyPPBuffer();
    return !errorFlag;
  }
  return result;
}
// 4A3722: variable 'v4' is possibly undefined
// 4A372F: variable 'v3' is possibly undefined
// 4A3752: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A954: using guessed type int dword_51A954;

//----- (004A3790) --------------------------------------------------------
signed int Rules_RegisterMathBuiltins()
{
  Rules_RegisterHostFunction(aCos, 100, (int)aCosfunction, (int)Rules_CosBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aSin, 100, (int)aSinfunction, (int)Rules_SinBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aTan, 100, (int)aTanfunction, (int)Rules_TanBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aSec, 100, (int)aSecfunction, (int)Rules_SecBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aCsc, 100, (int)aCscfunction, (int)Rules_CscBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aCot, 100, (int)aCotfunction, (int)Rules_CotBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aAcos, 100, (int)aAcosfunction, (int)Rules_AcosBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aAsin, 100, (int)aAsinfunction, (int)Rules_AsinBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aAtan, 100, (int)aAtanfunction, (int)Rules_AtanBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aAsec, 100, (int)aAsecfunction, (int)Rules_AsecBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aAcsc, 100, (int)aAcscfunction, (int)Rules_AcscBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aAcot, 100, (int)aAcotfunction, (int)Rules_AcotBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aCosh, 100, (int)aCoshfunction, (int)Rules_CoshBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aSinh, 100, (int)aSinhfunction, (int)Rules_SinhBuiltin, (int)a11n_0);
  Rules_RegisterHostFunction(aTanh, 100, (int)aTanhfunction, (int)Rules_MathTanh, (int)a11n_0);
  Rules_RegisterHostFunction(aSech, 100, (int)aSechfunction, (int)Rules_MathSech, (int)a11n_0);
  Rules_RegisterHostFunction(aCsch, 100, (int)aCschfunction, (int)Rules_MathCsch, (int)a11n_0);
  Rules_RegisterHostFunction(aCoth, 100, (int)aCothfunction, (int)Rules_MathCoth, (int)a11n_0);
  Rules_RegisterHostFunction(aAcosh, 100, (int)aAcoshfunction, (int)Rules_MathAcosh, (int)a11n_0);
  Rules_RegisterHostFunction(aAsinh, 100, (int)aAsinhfunction, (int)Rules_MathAsinh, (int)a11n_0);
  Rules_RegisterHostFunction(aAtanh, 100, (int)aAtanhfunction, (int)Rules_MathAtanh, (int)a11n_0);
  Rules_RegisterHostFunction(aAsech, 100, (int)aAsechfunction, (int)Rules_MathAsech, (int)a11n_0);
  Rules_RegisterHostFunction(aAcsch, 100, (int)aAcschfunction, (int)Rules_MathAcsch, (int)a11n_0);
  Rules_RegisterHostFunction(aAcoth, 100, (int)aAcothfunction, (int)Rules_MathAcoth, (int)a11n_0);
  Rules_RegisterHostFunction(aMod, 110, (int)aModfunction, (int)Rules_MathMod, (int)a22n);
  Rules_RegisterHostFunction(aExp, 100, (int)aExpfunction, (int)Rules_MathExp, (int)a11n_0);
  Rules_RegisterHostFunction(aLog, 100, (int)aLogfunction, (int)Rules_MathLog, (int)a11n_0);
  Rules_RegisterHostFunction(aLog10, 100, (int)aLog10function, (int)Rules_MathLog10, (int)a11n_0);
  Rules_RegisterHostFunction(aSqrt, 100, (int)aSqrtfunction, (int)Rules_MathSqrt, (int)a11n_0);
  Rules_RegisterHostFunction(aPi, 100, (int)aPifunction, (int)Rules_MathPi, (int)a00_8);
  Rules_RegisterHostFunction(aDegRad, 100, (int)aDegradfunction, (int)Rules_MathDegToRad, (int)a11n_0);
  Rules_RegisterHostFunction(aRadDeg, 100, (int)aRaddegfunction, (int)Rules_MathRadToDeg, (int)a11n_0);
  Rules_RegisterHostFunction(aDegGrad, 100, (int)aDeggradfunctio, (int)Rules_MathDegToGrad, (int)a11n_0);
  Rules_RegisterHostFunction(aGradDeg, 100, (int)aGraddegfunctio, (int)Rules_MathGradToDeg, (int)a11n_0);
  Rules_RegisterHostFunction(asc_507678, 100, (int)aPowfunction, (int)Rules_MathPow, (int)a22n);
  return Rules_RegisterHostFunction(aRound, 108, (int)aRoundfunction, (int)Rules_MathRound, (int)a11n_0);
}

//----- (004A3BD0) --------------------------------------------------------
signed int  Rules_MathParseSingleArg(double *theNumber, int a2, double a3)
{
  signed int result; // eax
  _DWORD item[10]; // [esp-8h] [ebp-28h] BYREF

  item[8] = a2;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, item, 0, a3);
  if ( result )
  {
    result = 1;
    *theNumber = *(double *)(item[2] + 16);
  }
  return result;
}

//----- (004A3C20) --------------------------------------------------------
BOOL __stdcall Rules_MathIsNearZero(double theNumber, double range)
{
  return -range <= theNumber && theNumber <= range;
}

//----- (004A3C50) --------------------------------------------------------
int Rules_MathDomainError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aEmathfun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDomainErrorFor, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction__1, v2);
  Rules_SetEvaluationErrorFlag(1);
  return Lexer_ErrorRecover(1);
}
// 4A3C70: variable 'v0' is possibly undefined
// 4A3C7C: variable 'v1' is possibly undefined
// 4A3C8B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A3CB0) --------------------------------------------------------
int Rules_MathArgumentOverflowError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aEmathfun, 2, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArgumentOverfl, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction__1, v2);
  Rules_SetEvaluationErrorFlag(1);
  return Lexer_ErrorRecover(1);
}
// 4A3CD0: variable 'v0' is possibly undefined
// 4A3CDC: variable 'v1' is possibly undefined
// 4A3CEB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A3D10) --------------------------------------------------------
int Rules_MathSingularityError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aEmathfun, 3, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSingularityAtA, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction__1, v2);
  Rules_SetEvaluationErrorFlag(1);
  return Lexer_ErrorRecover(1);
}
// 4A3D30: variable 'v0' is possibly undefined
// 4A3D3C: variable 'v1' is possibly undefined
// 4A3D4B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A3D70) --------------------------------------------------------
double  Rules_CosBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return cos(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A3DB0) --------------------------------------------------------
double  Rules_SinBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return sin(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A3DF0) --------------------------------------------------------
double  Rules_TanBuiltin(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double theNumber; // [esp+0h] [ebp-20h] BYREF
  long double cosValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  cosValue = cos(theNumber);
  if ( cosValue >= g_Rules_TanEpsilonPositive || cosValue <= g_Rules_TanEpsilonNegative )
    return sin(theNumber) / cosValue;
  Rules_MathSingularityError();
  LODWORD(v8) = v5;
  HIDWORD(v8) = v5;
  return v8;
}
// 4A3E55: variable 'v5' is possibly undefined
// 5076F8: using guessed type double dbl_5076F8;
// 507700: using guessed type double dbl_507700;

//----- (004A3E70) --------------------------------------------------------
double  Rules_SecBuiltin(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double theNumber; // [esp+0h] [ebp-20h] BYREF
  long double cosValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  cosValue = cos(theNumber);
  if ( cosValue >= g_Rules_SecEpsilonPositive || cosValue <= g_Rules_SecDomainEpsilonNeg )
    return 1.0 / cosValue;
  Rules_MathSingularityError();
  LODWORD(v8) = v5;
  HIDWORD(v8) = v5;
  return v8;
}
// 4A3ED2: variable 'v5' is possibly undefined
// 507708: using guessed type double dbl_507708;
// 507710: using guessed type double dbl_507710;

//----- (004A3EF0) --------------------------------------------------------
double  Rules_CscBuiltin(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double theNumber; // [esp+0h] [ebp-20h] BYREF
  long double sinValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  sinValue = sin(theNumber);
  if ( sinValue >= g_Rules_CscDomainEpsilonPos || sinValue <= g_Rules_CscDomainEpsilonNeg )
    return 1.0 / sinValue;
  Rules_MathSingularityError();
  LODWORD(v8) = v5;
  HIDWORD(v8) = v5;
  return v8;
}
// 4A3F52: variable 'v5' is possibly undefined
// 507718: using guessed type double dbl_507718;
// 507720: using guessed type double dbl_507720;

//----- (004A3F70) --------------------------------------------------------
double  Rules_CotBuiltin(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double theNumber; // [esp+0h] [ebp-20h] BYREF
  long double sinValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  sinValue = sin(theNumber);
  if ( sinValue >= g_Rules_CotDomainEpsilonPos || sinValue <= g_Rules_CotDomainEpsilonNeg )
    return cos(theNumber) / sinValue;
  Rules_MathSingularityError();
  LODWORD(v8) = v5;
  HIDWORD(v8) = v5;
  return v8;
}
// 4A3FD5: variable 'v5' is possibly undefined
// 507728: using guessed type double dbl_507728;
// 507730: using guessed type double dbl_507730;

//----- (004A3FF0) --------------------------------------------------------
double  Rules_AcosBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber <= 1.0 && theNumber >= g_Rules_AcosDomainLowerBound )
    return acos(theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507738: using guessed type double dbl_507738;

//----- (004A4060) --------------------------------------------------------
double  Rules_AsinBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber <= 1.0 && theNumber >= g_Rules_AsinDomainLowerBound )
    return asin(theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507740: using guessed type double dbl_507740;

//----- (004A40D0) --------------------------------------------------------
double  Rules_AtanBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return atan2(theNumber[0], 1.0);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A4110) --------------------------------------------------------
double  Rules_AsecBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber >= 1.0 || theNumber <= g_Rules_AsecDomainLowerBound )
    return acos(1.0 / theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507748: using guessed type double dbl_507748;

//----- (004A4180) --------------------------------------------------------
double  Rules_AcscBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber >= 1.0 || theNumber <= g_Rules_AcscDomainLowerBound )
    return asin(1.0 / theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507750: using guessed type double dbl_507750;

//----- (004A41F0) --------------------------------------------------------
double  Rules_AcotBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-1Ch] BYREF
  double v6; // [esp+8h] [ebp-14h]
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( Rules_MathParseSingleArg(&theNumber, a3, a4) )
  {
    if ( Rules_MathIsNearZero(theNumber, 1.0e-25) )
    {
      v6 = 1.570796326794897;
      return 1.570796326794897;
    }
    else
    {
      return atan2(1.0 / theNumber, 1.0);
    }
  }
  else
  {
    v6 = 0.0;
    return 0.0;
  }
}

//----- (004A4280) --------------------------------------------------------
double  Rules_CoshBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return cosh(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A42C0) --------------------------------------------------------
double  Rules_SinhBuiltin(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return sinh(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A4300) --------------------------------------------------------
double  Rules_MathTanh(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return tanh(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A4340) --------------------------------------------------------
double  Rules_MathSech(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v7; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  v8 = a1;
  v7 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return 1.0 / cosh(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A4390) --------------------------------------------------------
double  Rules_MathCsch(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+14h] [ebp-Ch]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a3;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( (HIDWORD(theNumber) & 0x7FFFFFFF) == 0 && !LODWORD(theNumber) )
  {
    Rules_MathSingularityError();
    return 0.0;
  }
  if ( !Rules_MathIsNearZero(theNumber, 1.0e-25) )
    return 1.0 / sinh(theNumber);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A4440) --------------------------------------------------------
double  Rules_MathCoth(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+14h] [ebp-Ch]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a3;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( (HIDWORD(theNumber) & 0x7FFFFFFF) == 0 && !LODWORD(theNumber) )
  {
    Rules_MathSingularityError();
    return 0.0;
  }
  if ( !Rules_MathIsNearZero(theNumber, 1.0e-25) )
    return 1.0 / tanh(theNumber);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A44F0) --------------------------------------------------------
double  Rules_MathAcosh(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber >= 1.0 )
    return acosh(theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507758: using guessed type double dbl_507758;

//----- (004A4560) --------------------------------------------------------
double  Rules_MathAsinh(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return asinh(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A45B0) --------------------------------------------------------
double  Rules_MathAtanh(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber < 1.0 && theNumber > g_Rules_AtanhDomainLowerBound )
    return atanh(theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507760: using guessed type double dbl_507760;
// 507768: using guessed type double dbl_507768;

//----- (004A4630) --------------------------------------------------------
double  Rules_MathAsech(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber <= 1.0 && theNumber > 0.0 )
    return acosh(1.0 / theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507770: using guessed type double dbl_507770;

//----- (004A46B0) --------------------------------------------------------
double  Rules_MathAcsch(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-1Ch] BYREF
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( (HIDWORD(theNumber) & 0x7FFFFFFF) != 0 || LODWORD(theNumber) )
    return asinh(1.0 / theNumber);
  Rules_MathDomainError();
  return 0.0;
}

//----- (004A4730) --------------------------------------------------------
double  Rules_MathAcoth(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber > 1.0 || theNumber < g_Rules_AcothDomainLowerBound )
    return atanh(1.0 / theNumber);
  Rules_MathDomainError();
  return 0.0;
}
// 507778: using guessed type double dbl_507778;
// 507780: using guessed type double dbl_507780;

//----- (004A47B0) --------------------------------------------------------
double  Rules_MathExp(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return exp(theNumber[0]);
  theNumber[1] = 0.0;
  return 0.0;
}

//----- (004A4800) --------------------------------------------------------
double  Rules_MathLog(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v7; // [esp+8h] [ebp-Ch]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber < 0.0 )
  {
    Rules_MathDomainError();
    return 0.0;
  }
  if ( theNumber != 0.0 )
    return log(theNumber);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A4890) --------------------------------------------------------
double  Rules_MathLog10(int a1, int a2, int a3, double a4)
{
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  int v7; // [esp+8h] [ebp-Ch]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber < 0.0 )
  {
    Rules_MathDomainError();
    return 0.0;
  }
  if ( theNumber != 0.0 )
    return log10(theNumber);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A4920) --------------------------------------------------------
double  Rules_MathSqrt(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double theNumber; // [esp+0h] [ebp-18h] BYREF
  double v7; // [esp+8h] [ebp-10h]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&theNumber, a3, a4) )
    return 0.0;
  if ( theNumber >= 0.0 )
    return sqrt(theNumber);
  Rules_MathDomainError();
  LODWORD(v7) = v5;
  HIDWORD(v7) = v5;
  return v7;
}
// 4A4968: variable 'v5' is possibly undefined

//----- (004A4980) --------------------------------------------------------
double  Rules_MathPow(double a1)
{
  signed int parseOk; // eax
  int value1; // [esp+0h] [ebp-58h] BYREF
  int value1Value; // [esp+8h] [ebp-50h]
  int value2; // [esp+18h] [ebp-40h] BYREF
  int value2Value; // [esp+20h] [ebp-38h]
  double num1; // [esp+30h] [ebp-28h]
  double num2; // [esp+38h] [ebp-20h]
  double intPart; // [esp+40h] [ebp-18h]

  if ( Lexer_TokenExpect(2) == -1 )
    return 0.0;
  parseOk = Lexer_ParseValueList(1, &value1, 0, a1);
  if ( !parseOk )
    return 0.0;
  parseOk = Lexer_ParseValueList(2, &value2, 0, a1);
  if ( !parseOk )
    return 0.0;
  num1 = *(double *)(value1Value + 16);
  num2 = *(double *)(value2Value + 16);
  if ( num1 == 0.0 && num2 <= 0.0 )
    goto LABEL_10;
  if ( num1 < 0.0 )
  {
    if ( num2 >= 0.0 )
      intPart = floor(num2);
    else
      intPart = ceil(num2);
    if ( intPart != num2 )
      goto LABEL_10;
  }
  return pow(num1, num2);
LABEL_10:
  Rules_MathDomainError();
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  return 0.0;
}

//----- (004A4AE0) --------------------------------------------------------
int * Rules_MathMod(int returnValue, double a2)
{
  signed int v3; // eax
  int *result; // eax
  signed int intRemainder; // eax
  int item2; // [esp+8h] [ebp-78h] BYREF
  int item2Type; // [esp+Ch] [ebp-74h]
  int item2Value; // [esp+10h] [ebp-70h]
  int item1; // [esp+20h] [ebp-60h] BYREF
  int item1Type; // [esp+24h] [ebp-5Ch]
  int item1Value; // [esp+28h] [ebp-58h]
  double fnum2; // [esp+38h] [ebp-48h]
  double quotient; // [esp+40h] [ebp-40h]
  double truncatedQuotient; // [esp+48h] [ebp-38h]
  double fnum1; // [esp+50h] [ebp-30h]
  double floatRemainder; // [esp+58h] [ebp-28h]

  if ( Lexer_TokenExpect(2) == -1 )
  {
    v3 = 0;
LABEL_20:
    *(_DWORD *)(returnValue + 4) = 1;
    result = Rules_AddIntegerValue(v3);
    *(_DWORD *)(returnValue + 8) = result;
    return result;
  }
  v3 = Lexer_ParseValueList(1, &item1, 110, a2);
  if ( !v3 )
    goto LABEL_20;
  v3 = Lexer_ParseValueList(2, &item2, 110, a2);
  if ( !v3 )
    goto LABEL_20;
  if ( item2Type == 1 && !*(_DWORD *)(item2Value + 16) || item2Type != 1 && *(double *)(item2Value + 16) == 0.0 )
  {
    Rules_ReportDivideByZeroError();
    Lexer_ErrorRecover(1);
    *(_DWORD *)(returnValue + 4) = 1;
    result = Rules_AddIntegerValue(0);
    *(_DWORD *)(returnValue + 8) = result;
  }
  else if ( item1Type && item2Type )
  {
    intRemainder = *(_DWORD *)(item1Value + 16) % *(_DWORD *)(item2Value + 16);
    *(_DWORD *)(returnValue + 4) = 1;
    result = Rules_AddIntegerValue(intRemainder);
    *(_DWORD *)(returnValue + 8) = result;
  }
  else
  {
    if ( item1Type == 1 )
      fnum1 = (double)*(int *)(item1Value + 16);
    else
      fnum1 = *(double *)(item1Value + 16);
    if ( item2Type == 1 )
      fnum2 = (double)*(int *)(item2Value + 16);
    else
      fnum2 = *(double *)(item2Value + 16);
    quotient = fnum1 / fnum2;
    *(_DWORD *)(returnValue + 4) = 0;
    if ( quotient >= 0.0 )
      truncatedQuotient = floor(quotient);
    else
      truncatedQuotient = ceil(quotient);
    floatRemainder = fnum1 - truncatedQuotient * fnum2;
    result = (int *)Rules_AddDoubleValue(floatRemainder);
    *(_DWORD *)(returnValue + 8) = result;
  }
  return result;
}

//----- (004A4D20) --------------------------------------------------------
double Rules_MathPi()
{
  Lexer_TokenExpect(0);
  return acos(g_Rules_MathPiAcosArgument);
}
// 507788: using guessed type double dbl_507788;

//----- (004A4D50) --------------------------------------------------------
double  Rules_MathDegToRad(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return theNumber[0] * g_Rules_DegToRadPiConstant / g_Rules_DegToRadDegreesConstant;
  theNumber[1] = 0.0;
  return 0.0;
}
// 507790: using guessed type double dbl_507790;
// 507798: using guessed type double dbl_507798;

//----- (004A4DA0) --------------------------------------------------------
double  Rules_MathRadToDeg(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return theNumber[0] * g_Rules_RadToDegDegreesConstant / g_Rules_RadToDegPiConstant;
  theNumber[1] = 0.0;
  return 0.0;
}
// 5077A0: using guessed type double dbl_5077A0;
// 5077A8: using guessed type double dbl_5077A8;

//----- (004A4DF0) --------------------------------------------------------
double  Rules_MathDegToGrad(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return theNumber[0] / g_Rules_DegToGradConversionFactor;
  theNumber[1] = 0.0;
  return 0.0;
}
// 5077B0: using guessed type double dbl_5077B0;

//----- (004A4E30) --------------------------------------------------------
double  Rules_MathGradToDeg(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(theNumber, a3, a4) )
    return theNumber[0] * g_Rules_GradToDegConversionFactor;
  theNumber[1] = 0.0;
  return 0.0;
}
// 5077B8: using guessed type double dbl_5077B8;

//----- (004A4E70) --------------------------------------------------------
signed int  Rules_MathRound(int returnValue, double a2)
{
  signed int result; // eax
  int theValue; // [esp+8h] [ebp-28h] BYREF
  int theValueType; // [esp+Ch] [ebp-24h]
  int theValueContents; // [esp+10h] [ebp-20h]
  int v8; // [esp+28h] [ebp-8h]

  v8 = returnValue;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &theValue, 110, a2);
  if ( !result )
    return result;
  if ( theValueType == 1 )
    return *(_DWORD *)(theValueContents + 16);
  return (int)ceil(*(double *)(theValueContents + 16) + g_Rules_MathRoundHalfOffset);
}
// 5077C0: using guessed type double dbl_5077C0;

//----- (004A5000) --------------------------------------------------------
_DWORD * Help_IndexTopicFile(CHAR *fileName, _BYTE *errorBuffer, int a3, int errorBufferSize, DWORD a5)
{
  int *fp; // esi
  _DWORD *result; // eax
  int v8; // ecx
  int lineNumber; // ebp
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // ecx
  _BYTE lineBuffer[256]; // [esp+0h] [ebp-128h] BYREF
  signed int errBufSize; // [esp+100h] [ebp-28h]
  _BYTE *errBuf; // [esp+104h] [ebp-24h]
  int inEntry; // [esp+108h] [ebp-20h]
  char *fileRecord; // [esp+10Ch] [ebp-1Ch]
  int entryCount; // [esp+110h] [ebp-18h]
  int entryClosed; // [esp+114h] [ebp-14h]

  errBuf = errorBuffer;
  errBufSize = errorBufferSize;
  if ( errorBufferSize > 0 )
    *errorBuffer = 0;
  fp = (int *)IO_FOpen(fileName, g_Help_FileOpenModeRead, a3, a5);
  if ( fp )
  {
    fileRecord = Help_GetOrCreateFileRecord(fileName);
    if ( fileRecord )
    {
      lineNumber = 0;
      entryCount = 0;
      inEntry = 0;
      entryClosed = 1;
      while ( fgets_(lineBuffer, 256, (int)fp) )
      {
        ++lineNumber;
        if ( lineBuffer[0] != 36 || lineBuffer[1] != 36 )
        {
          if ( Str_FindSubstringIndex(lineBuffer, aEndEntry) < 0 )
          {
            if ( Str_FindSubstringIndex(lineBuffer, aBeginEntry) >= 0 )
            {
              if ( entryClosed != 1 )
              {
                fclose_((int)fp);
                Help_UnloadTopicFile((int)fileName);
                if ( v12 < 60 )
                  return 0;
                goto LABEL_23;
              }
              inEntry = 1;
              entryClosed = 0;
              result = Help_ParseEntryHeader(fp, (int)fileName, (int)errBuf, errBufSize, lineNumber);
              if ( !result )
                return result;
              result = (_DWORD *)Help_InsertEntryIntoTopicTree((int)fileRecord, result, (int)errBuf, errBufSize, lineNumber);
              if ( !result )
                return result;
            }
          }
          else
          {
            if ( inEntry != 1 )
            {
              fclose_((int)fp);
              Help_UnloadTopicFile((int)fileName);
              if ( v11 < 60 )
                return 0;
              sprintf_(errBuf, "Line %d : Unmatched end marker.", lineNumber);
              return 0;
            }
            entryClosed = 1;
            inEntry = 0;
            ++entryCount;
          }
        }
      }
      fclose_((int)fp);
      if ( entryClosed )
      {
        if ( !entryCount )
          Help_UnloadTopicFile((int)fileName);
        return (_DWORD *)entryCount;
      }
      Help_UnloadTopicFile((int)fileName);
      if ( v13 >= 60 )
      {
LABEL_23:
        sprintf_(errBuf, "Line %d : Previous entry not closed.", lineNumber);
        return 0;
      }
    }
    else
    {
      fclose_((int)fp);
      if ( v10 >= 60 )
      {
        sprintf_(errBuf, "File \"%s\" already loaded.", fileName);
        return 0;
      }
    }
  }
  else if ( errBufSize >= 60 )
  {
    sprintf_(errBuf, "Could not open file \"%s\".", fileName);
  }
  return 0;
}
// 4A509F: variable 'v8' is possibly undefined
// 4A510E: variable 'v10' is possibly undefined
// 4A514F: variable 'v11' is possibly undefined
// 4A51B0: variable 'v12' is possibly undefined
// 4A5266: variable 'v13' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 4841D3: using guessed type int __fastcall fgets_(_DWORD, _DWORD);
// 5077F0: using guessed type unsigned __int8 byte_5077F0[4];

//----- (004A52C0) --------------------------------------------------------
signed int  Help_UnloadTopicFile(int fileName)
{
  int topicFile; // ecx
  int prevFile; // esi
  BOOL noMatch; // eax
  _DWORD *foundFile; // ecx

  topicFile = g_HelpLoadedTopicFileList;
  prevFile = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    noMatch = strcmp_(g_HelpLoadedTopicFileList, fileName) != 0;
  else
    noMatch = 0;
  if ( noMatch > 0 )
  {
    do
    {
      prevFile = topicFile;
      topicFile = *(_DWORD *)(topicFile + 88);
    }
    while ( topicFile && strcmp_(topicFile, fileName) );
  }
  if ( !topicFile )
    return 0;
  Help_FreeTopicTree(*(_DWORD **)(topicFile + 80));
  if ( (_DWORD *)prevFile == foundFile )
    g_HelpLoadedTopicFileList = foundFile[22];
  else
    *(_DWORD *)(prevFile + 88) = foundFile[22];
  Mem_SmallBlockFree(foundFile, 92);
  return 1;
}
// 4A52D8: variable 'v2' is possibly undefined
// 4A5312: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5350) --------------------------------------------------------
int  Help_OpenFileAtNavigatedTopic(const CHAR *fileName, _DWORD *menu, _DWORD *code, _BYTE *topicName)
{
  int v6; // ecx
  signed int offset; // ebp
  int result; // eax
  int fp; // ecx

  offset = Help_FindOrAdvanceTopicEntry((int)fileName, menu, code, topicName);
  if ( offset < 0 )
    return 0;
  result = IO_FOpen(fileName, g_Help_FileOpenModeRead, v6, offset);
  if ( result )
  {
    if ( IO_SeekStreamGuarded(result, offset, 0, (int)code) < 0 )
    {
      fclose_(fp);
      *code = -10;
      return 0;
    }
    else
    {
      return fp;
    }
  }
  else
  {
    *code = -10;
  }
  return result;
}
// 4A536F: variable 'v6' is possibly undefined
// 4A5391: variable 'v9' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5077F0: using guessed type unsigned __int8 byte_5077F0[4];

//----- (004A53B0) --------------------------------------------------------
int  Help_ReopenFileAtActiveEntry(const CHAR *fileName, _DWORD *code, DWORD a3)
{
  int fileRecord; // ecx
  BOOL noMatch; // eax
  int result; // eax
  int v8; // ecx
  int fp; // esi
  int v10; // ecx

  fileRecord = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    noMatch = strcmp_(g_HelpLoadedTopicFileList, fileName) != 0;
  else
    noMatch = 0;
  if ( noMatch > 0 )
  {
    do
      fileRecord = *(_DWORD *)(fileRecord + 88);
    while ( fileRecord && strcmp_(fileRecord, fileName) );
  }
  if ( !fileRecord )
  {
    *code = -10;
    return 0;
  }
  if ( !*(_DWORD *)(fileRecord + 84) )
  {
    *code = -25;
    return 0;
  }
  result = IO_FOpen(fileName, g_Help_FileOpenModeRead, fileRecord, a3);
  fp = result;
  if ( result )
  {
    if ( IO_SeekStreamGuarded(result, *(_DWORD *)(*(_DWORD *)(v8 + 84) + 88), 0, (int)code) < 0 )
    {
      fclose_(v10);
      *code = -10;
      return 0;
    }
    else
    {
      result = fp;
      *code = 0;
    }
  }
  else
  {
    *code = -10;
  }
  return result;
}
// 4A53C8: variable 'v5' is possibly undefined
// 4A542E: variable 'v8' is possibly undefined
// 4A544E: variable 'v10' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 5077F0: using guessed type unsigned __int8 byte_5077F0[4];
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5460) --------------------------------------------------------
_BYTE * Help_ReadEntryLine(int stream_handle, _BYTE *buffer, int buffer_size)
{
  if ( fgets_((char *)buffer, buffer_size, stream_handle) )
  {
    if ( *buffer == 36 && buffer[1] == 36 )
    {
      *buffer = 32;
      buffer[1] = 32;
      return buffer;
    }
    if ( Str_FindSubstringIndex(buffer, aEndEntry) < 0 )
      return buffer;
  }
  fclose_(stream_handle);
  return 0;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004A54C0) --------------------------------------------------------
signed int  Str_FindSubstringIndex(_BYTE *str, _BYTE *substr)
{
  _BYTE *strCursor; // ebp
  int position; // esi
  _BYTE *substrPtr; // eax
  int matchLength; // ecx
  _BYTE *cmpPtr; // edx
  char ch; // bh
  char nextCh; // dh

  strCursor = str;
  position = 0;
  if ( !*str )
    return -1;
  while ( 1 )
  {
    substrPtr = substr;
    matchLength = 0;
    cmpPtr = &str[position];
    if ( *substr )
    {
      do
      {
        if ( *cmpPtr != *substrPtr )
          break;
        ++cmpPtr;
        ch = *++substrPtr;
        ++matchLength;
      }
      while ( ch );
    }
    if ( !substr[matchLength] && matchLength )
      break;
    nextCh = *++strCursor;
    ++position;
    if ( !nextCh )
      return -1;
  }
  return position;
}

//----- (004A5530) --------------------------------------------------------
int  Str_UppercaseToDelimiter(int result, int a2)
{
  _BYTE *strPtr; // edx
  _BYTE *v4; // edx
  char nextCh; // bh

  strPtr = (_BYTE *)result;
  if ( *(_BYTE *)result )
  {
    do
    {
      while ( 1 )
      {
        result = (unsigned __int8)(*strPtr + 1);
        if ( IsTable[result] < 0 )
          break;
        if ( !*++strPtr )
          return result;
      }
      result = toupper_(a2);
      *v4 = result;
      nextCh = v4[1];
      strPtr = v4 + 1;
    }
    while ( nextCh );
  }
  return result;
}
// 4A555B: variable 'a2' is possibly undefined
// 4A5560: variable 'v4' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004A5570) --------------------------------------------------------
char * Help_GetOrCreateFileRecord(char *fileName)
{
  int record; // ecx
  char *result; // eax
  int v4; // ecx
  char *newRecord; // edx
  int v6; // ecx
  char *dstPtr; // edi
  char ch; // al
  char nextCh; // al

  if ( !g_HelpLoadedTopicFileList )
  {
LABEL_6:
    newRecord = (char *)Mem_SmallBlockAlloc(0x5Cu);
    dstPtr = newRecord;
    do
    {
      ch = *fileName;
      *dstPtr = *fileName;
      if ( !ch )
        break;
      nextCh = fileName[1];
      fileName += 2;
      dstPtr[1] = nextCh;
      dstPtr += 2;
    }
    while ( nextCh );
    *((_DWORD *)newRecord + 20) = 0;
    *((_DWORD *)newRecord + 21) = 0;
    *((_DWORD *)newRecord + 22) = 0;
    if ( g_HelpLoadedTopicFileList )
    {
      *(_DWORD *)(v6 + 88) = newRecord;
      return newRecord;
    }
    else
    {
      g_HelpLoadedTopicFileList = (int)newRecord;
      return newRecord;
    }
  }
  record = g_HelpLoadedTopicFileList;
  if ( !*(_DWORD *)(g_HelpLoadedTopicFileList + 88) )
  {
LABEL_5:
    result = (char *)strcmp_(record, fileName);
    if ( !result )
      return result;
    goto LABEL_6;
  }
  while ( 1 )
  {
    result = (char *)strcmp_(record, fileName);
    if ( !result )
      return result;
    record = *(_DWORD *)(v4 + 88);
    if ( !*(_DWORD *)(record + 88) )
      goto LABEL_5;
  }
}
// 4A5598: variable 'v4' is possibly undefined
// 4A5605: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5610) --------------------------------------------------------
_DWORD * Help_ParseEntryHeader(int *fp, int fileName, int errorBuffer, signed int errorBufferSize, int lineNumber)
{
  _DWORD *entry; // ebx
  int v9; // edx
  _DWORD *v10; // ecx
  int v11; // ecx
  int bufferedCount; // edi
  signed int nextChar; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int fileOffset; // eax
  int v18; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  unsigned __int8 *streamBufPtr; // eax
  char delimiterString; // [esp+0h] [ebp-20h] BYREF
  char entryTypeChar; // [esp+10h] [ebp-10h] BYREF

  entry = Mem_SmallBlockAlloc(0x68u);
  if ( sscanf_(v9, "%d%1s%12s%s", entry, &entryTypeChar, &delimiterString, entry + 2) == 4 )
  {
    if ( entryTypeChar == 77 )
    {
      v10[1] = -45;
LABEL_5:
      if ( !strcmp_(v10, aBeginEntry) )
      {
        bufferedCount = fp[1];
        if ( bufferedCount > 0 && (unsigned int)*(unsigned __int8 *)*fp - 13 > 0xFD )
        {
          streamBufPtr = (unsigned __int8 *)*fp;
          v14 = *fp + 1;
          fp[1] = bufferedCount - 1;
          *fp = v14;
          nextChar = *streamBufPtr;
        }
        else
        {
          nextChar = fgetc_(v11, fp);
        }
        CRT_FlushBufferAndPutChar(nextChar, v14);
        fileOffset = ftell_(v16, v15);
        entry[24] = 0;
        entry[23] = 0;
        entry[22] = fileOffset;
        entry[25] = 0;
        Str_UppercaseToDelimiter((int)(entry + 2), v18);
        return entry;
      }
      else
      {
        Mem_SmallBlockFree(entry, 104);
        fclose_(v24);
        Help_UnloadTopicFile(fileName);
        if ( errorBufferSize >= 60 )
          sprintf_(errorBuffer, "Line %d : Invalid delimeter string.", lineNumber);
        return 0;
      }
    }
    if ( entryTypeChar == 73 )
    {
      v10[1] = -50;
      goto LABEL_5;
    }
    Mem_SmallBlockFree(v10, 104);
    fclose_(v22);
    Help_UnloadTopicFile(fileName);
    if ( v23 >= 60 )
      sprintf_(errorBuffer, "Line %d : Invalid entry type.", lineNumber);
    return 0;
  }
  else
  {
    Mem_SmallBlockFree(v10, 104);
    fclose_(v20);
    Help_UnloadTopicFile(fileName);
    if ( v21 >= 60 )
      sprintf_(errorBuffer, "Line %d : Invalid delimeter string.", lineNumber);
    return 0;
  }
}
// 4A5641: variable 'v9' is possibly undefined
// 4A5668: variable 'v10' is possibly undefined
// 4A56A5: variable 'v11' is possibly undefined
// 4A56AA: variable 'v14' is possibly undefined
// 4A56B1: variable 'v16' is possibly undefined
// 4A56B1: variable 'v15' is possibly undefined
// 4A56D1: variable 'v18' is possibly undefined
// 4A56EF: variable 'v20' is possibly undefined
// 4A5702: variable 'v21' is possibly undefined
// 4A573C: variable 'v22' is possibly undefined
// 4A574F: variable 'v23' is possibly undefined
// 4A577D: variable 'v24' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48429C: using guessed type _DWORD sscanf_(_DWORD, _DWORD, ...);
// 4887EC: using guessed type __int64 __fastcall ftell_(_DWORD, _DWORD);
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);

//----- (004A57D0) --------------------------------------------------------
signed int  Help_InsertEntryIntoTopicTree(int fileRecord, _DWORD *entry, int errorBuffer, signed int errorBufferSize, int lineNumber)
{
  int currentTopic; // edx
  int v8; // edx
  int v10; // ecx
  int v11; // ecx
  _DWORD *nextTopic; // edx

  if ( !*(_DWORD *)(fileRecord + 80) )
  {
    *(_DWORD *)(fileRecord + 80) = entry;
    goto LABEL_6;
  }
  currentTopic = g_ClipsHelpCurrentTopicNode;
  if ( *entry > *(_DWORD *)g_ClipsHelpCurrentTopicNode )
  {
    if ( *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 4) != -45 )
    {
      Mem_SmallBlockFree(entry, 104);
      fclose_(v10);
      Help_UnloadTopicFile(v11);
      if ( errorBufferSize >= 60 )
        sprintf_(errorBuffer, "Line %d : Non-menu entries cannot have subtopics.", lineNumber);
      return 0;
    }
    entry[24] = g_ClipsHelpCurrentTopicNode;
    goto LABEL_5;
  }
  if ( *entry == *(_DWORD *)g_ClipsHelpCurrentTopicNode )
    goto LABEL_13;
  if ( g_ClipsHelpCurrentTopicNode )
  {
    do
    {
      nextTopic = *(_DWORD **)(g_ClipsHelpCurrentTopicNode + 96);
      g_ClipsHelpCurrentTopicNode = (int)nextTopic;
    }
    while ( nextTopic && *entry < *nextTopic );
  }
  if ( g_ClipsHelpCurrentTopicNode )
  {
    if ( *(_DWORD *)g_ClipsHelpCurrentTopicNode < *entry )
    {
      entry[24] = g_ClipsHelpCurrentTopicNode;
      entry[25] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 92);
      currentTopic = g_ClipsHelpCurrentTopicNode;
LABEL_5:
      *(_DWORD *)(currentTopic + 92) = entry;
LABEL_6:
      v8 = 1;
      g_ClipsHelpCurrentTopicNode = (int)entry;
      return v8;
    }
LABEL_13:
    entry[24] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 96);
    entry[25] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 100);
    *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 100) = entry;
    g_ClipsHelpCurrentTopicNode = (int)entry;
    return 1;
  }
  entry[24] = 0;
  entry[25] = *(_DWORD *)(fileRecord + 80);
  *(_DWORD *)(fileRecord + 80) = entry;
  g_ClipsHelpCurrentTopicNode = (int)entry;
  return 1;
}
// 4A581A: variable 'v10' is possibly undefined
// 4A5825: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACE4: using guessed type int dword_51ACE4;

//----- (004A5920) --------------------------------------------------------
signed int  Help_FindOrAdvanceTopicEntry(int fileName, _DWORD *menu, _DWORD *status, _BYTE *topicName)
{
  int fileRecord; // ecx
  BOOL noMatch; // eax
  int currentEntry; // ebx
  int parentEntry; // esi
  signed int result; // eax
  int v12; // ecx
  int curEntry; // edx
  int theEntry; // ebx
  BOOL noTopicMatch; // eax
  int fallbackEntry; // eax
  int menuEntry; // ebp

  fileRecord = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    noMatch = strcmp_(g_HelpLoadedTopicFileList, fileName) != 0;
  else
    noMatch = 0;
  if ( noMatch > 0 )
  {
    do
      fileRecord = *(_DWORD *)(fileRecord + 88);
    while ( fileRecord && strcmp_(fileRecord, fileName) );
  }
  if ( fileRecord )
  {
    if ( topicName )
    {
      Str_UppercaseToDelimiter((int)topicName, fileRecord);
      curEntry = *(_DWORD *)(v12 + 84);
      if ( curEntry )
        theEntry = *(_DWORD *)(curEntry + 92);
      else
        theEntry = *(_DWORD *)(v12 + 80);
      if ( theEntry )
        noTopicMatch = Str_FindSubstringIndex((_BYTE *)(theEntry + 8), topicName) != 0;
      else
        noTopicMatch = 0;
      if ( noTopicMatch > 0 )
      {
        do
          theEntry = *(_DWORD *)(theEntry + 100);
        while ( theEntry && Str_FindSubstringIndex((_BYTE *)(theEntry + 8), topicName) );
      }
      if ( theEntry )
      {
        if ( *(_DWORD *)(theEntry + 4) == -45 )
        {
          *status = -40;
          *(_DWORD *)(v12 + 84) = theEntry;
        }
        else
        {
          *status = 0;
        }
        menuEntry = *(_DWORD *)(v12 + 84);
        if ( menuEntry )
          *menu = menuEntry + 8;
        return *(_DWORD *)(theEntry + 88);
      }
      else
      {
        *status = -25;
        fallbackEntry = *(_DWORD *)(v12 + 84);
        if ( !fallbackEntry )
          return -1;
        *menu = fallbackEntry + 8;
        return *(_DWORD *)(*(_DWORD *)(v12 + 84) + 88);
      }
    }
    else
    {
      currentEntry = *(_DWORD *)(fileRecord + 84);
      if ( currentEntry )
      {
        parentEntry = *(_DWORD *)(currentEntry + 96);
        if ( !parentEntry )
        {
          *status = -30;
          *(_DWORD *)(fileRecord + 84) = 0;
          *menu = 0;
          return -1;
        }
        *(_DWORD *)(fileRecord + 84) = parentEntry;
        *status = -35;
        *menu = *(_DWORD *)(fileRecord + 84) + 8;
        return *(_DWORD *)(*(_DWORD *)(fileRecord + 84) + 88);
      }
      else
      {
        result = -1;
        *status = -30;
      }
    }
  }
  else
  {
    result = -1;
    *status = -10;
  }
  return result;
}
// 4A593F: variable 'v7' is possibly undefined
// 4A59DC: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5A80) --------------------------------------------------------
_DWORD * Help_FreeTopicTree(_DWORD *result)
{
  _DWORD *i; // ecx

  for ( i = result; i; result = (_DWORD *)Mem_SmallBlockFree(i, 104) )
  {
    if ( i[23] )
      Help_FreeTopicTree(i[23]);
  }
  return result;
}
// 4A5A88: variable 'i' is possibly undefined

//----- (004A5AB0) --------------------------------------------------------
signed int  Help_RunInteractiveHelpBrowser(int a1, DWORD a2, double a3)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *mainTopicSrc; // esi
  _BYTE *topicNameDst; // edi
  int topicList; // ebp
  char v9; // al
  char v10; // al
  _DWORD *argTopicList; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // eax
  int lineCount; // ecx
  int fp; // esi
  int v17; // ecx
  char *messageText; // edx
  char *routerName; // eax
  signed int result; // eax
  int v21; // ecx
  _DWORD *nodeToFree; // eax
  char *defaultPathSrc; // esi
  _BYTE *helpPathDst; // edi
  char v25; // al
  char v26; // al
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  unsigned int v31; // ecx
  char inputChar; // al
  char commandChar; // dl
  int v34; // ecx
  int v35; // ecx
  _BYTE lineBuffer[256]; // [esp+0h] [ebp-120h] BYREF
  _DWORD *status; // [esp+100h] [ebp-20h] BYREF
  int menu[7]; // [esp+104h] [ebp-1Ch] BYREF

  if ( !g_HelpSystemInitialized )
  {
    if ( !g_ClipsHelpFilePath )
    {
      defaultPathSrc = aClips_hlp;
      helpPathDst = Mem_SmallBlockAlloc(strlen(aClips_hlp) + 1);
      g_ClipsHelpFilePath = (int)helpPathDst;
      do
      {
        v25 = *defaultPathSrc;
        *helpPathDst = *defaultPathSrc;
        if ( !v25 )
          break;
        v26 = defaultPathSrc[1];
        defaultPathSrc += 2;
        helpPathDst[1] = v26;
        helpPathDst += 2;
      }
      while ( v26 );
    }
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aLoadingHelpFil, a1);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], g_ClipsHelpFilePath, v3);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)a_PleaseWait___, v4);
    status = Help_IndexTopicFile((CHAR *)g_ClipsHelpFilePath, lineBuffer, v5, 256, a2);
    if ( !status )
    {
      Rules_PrintErrorID((int)aTextpro, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToAccess, v27);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)lineBuffer, v28);
      return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50797C, v29);
    }
    IO_AddRouter((int)aWhelp, 10, (int)Rules_HelpRouterPrint, (int)Help_RouterQueryMatchesWhelp, (int)Rules_HelpRouterGetc, (int)Rules_HelpRouterUngetc, 0);
    g_HelpSystemInitialized = 1;
  }
  IO_ActivateRouter((int)aWhelp);
  mainTopicSrc = aMain_2;
  topicNameDst = Mem_SmallBlockAlloc(0x58u);
  topicList = (int)topicNameDst;
  do
  {
    v9 = *mainTopicSrc;
    *topicNameDst = *mainTopicSrc;
    if ( !v9 )
      break;
    v10 = mainTopicSrc[1];
    mainTopicSrc += 2;
    topicNameDst[1] = v10;
    topicNameDst += 2;
  }
  while ( v10 );
  argTopicList = Rules_HelpBuildTopicListFromArgs(a3);
  *(_DWORD *)(v12 + 80) = 0;
  *(_DWORD *)(v12 + 84) = argTopicList;
  Output_Write((int)aWhelp, (int)asc_50797C, v13);
  while ( 1 )
  {
    v14 = Rules_HelpLocateTopicEntry((const CHAR *)g_ClipsHelpFilePath, topicList, &status, menu);
    fp = v14;
    if ( status == (_DWORD *)-10 )
      break;
    if ( status == (_DWORD *)-30 )
      goto LABEL_12;
    if ( status == (_DWORD *)-25 )
    {
      if ( !v14 )
      {
        Output_Write((int)aWhelp, (int)aRootEntryMainN, lineCount);
        Output_Write((int)aWhelp, g_ClipsHelpFilePath, v34);
        messageText = a_SeeExternalDo;
        routerName = aWhelp;
        goto LABEL_11;
      }
      Output_Write((int)aWhelp, (int)aSorryNoInforma, lineCount);
    }
    if ( status != (_DWORD *)-35 )
    {
      while ( 2 )
      {
        if ( !Help_ReadEntryLine(fp, lineBuffer, 256) )
          goto LABEL_43;
        if ( lineCount < 23 )
          goto LABEL_37;
        Output_Write((int)aWhelp, (int)aPressReturnFor, lineCount);
        Output_Write((int)aWhelp, (int)aPressAReturnTo, v30);
        g_Lexer_PendingLineCharIndex = 0;
LABEL_29:
        inputChar = Lexer_PeekChar((int)aWhelp, v31);
        commandChar = inputChar;
        switch ( inputChar )
        {
          case 10:
            goto LABEL_34;
          case 97:
            commandChar = 65;
            goto LABEL_32;
          case 8:
            v31 = g_Lexer_PendingLineCharIndex;
            if ( g_Lexer_PendingLineCharIndex )
              --g_Lexer_PendingLineCharIndex;
            break;
          default:
LABEL_32:
            ++g_Lexer_PendingLineCharIndex;
            break;
        }
        Lexer_PeekChar((int)aWhelp, v31);
LABEL_34:
        if ( commandChar == 10 || commandChar == 65 )
        {
          lineCount = 0;
          g_Lexer_PendingLineCharIndex = -1;
          if ( commandChar == 65 )
            goto LABEL_42;
LABEL_37:
          Output_Write((int)aWhelp, (int)lineBuffer, lineCount + 1);
          continue;
        }
        goto LABEL_29;
      }
    }
    if ( fp )
LABEL_42:
      fclose_(lineCount);
LABEL_43:
    topicList = Rules_HelpReadTopicListFromInput(topicList, menu, lineCount);
    if ( g_ClipsHaltExecution )
    {
      while ( status != (_DWORD *)-30 )
      {
        if ( Help_OpenFileAtNavigatedTopic((const CHAR *)g_ClipsHelpFilePath, menu, &status, 0) )
          fclose_(v35);
      }
    }
    if ( status == (_DWORD *)-30 )
      goto LABEL_12;
  }
  Rules_PrintErrorID((int)aTextpro, 1, 0);
  messageText = aUnableToAccess;
  routerName = g_IO_LogicalNameTable_WError[0];
LABEL_11:
  Output_Write((int)routerName, (int)messageText, v17);
LABEL_12:
  result = IO_DeactivateRouter((int)aWhelp);
  if ( topicList )
  {
    v21 = 88;
    do
    {
      nodeToFree = (_DWORD *)topicList;
      topicList = *(_DWORD *)(topicList + 84);
      result = Mem_SmallBlockFree(nodeToFree, v21);
    }
    while ( topicList );
  }
  return result;
}
// 4A5AE0: variable 'a1' is possibly undefined
// 4A5AF0: variable 'v3' is possibly undefined
// 4A5B04: variable 'v4' is possibly undefined
// 4A5B10: variable 'v5' is possibly undefined
// 4A5B91: variable 'v12' is possibly undefined
// 4A5BA5: variable 'v13' is possibly undefined
// 4A5BF6: variable 'v17' is possibly undefined
// 4A5C15: variable 'v21' is possibly undefined
// 4A5C8A: variable 'v27' is possibly undefined
// 4A5C96: variable 'v28' is possibly undefined
// 4A5CA5: variable 'v29' is possibly undefined
// 4A5CD4: variable 'v15' is possibly undefined
// 4A5D17: variable 'v30' is possibly undefined
// 4A5D28: variable 'v31' is possibly undefined
// 4A5D8B: variable 'v34' is possibly undefined
// 4A5E02: variable 'v35' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A628: using guessed type int dword_51A628;
// 51A968: using guessed type int dword_51A968;
// 51ACE8: using guessed type int dword_51ACE8;
// 51ACEC: using guessed type int dword_51ACEC;

//----- (004A5E30) --------------------------------------------------------
signed int  Help_SetHelpFilePathCommand(int a1, double a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  signed int result; // eax
  int v6; // ecx
  char *dialogRouter; // eax
  char *pathToPrint; // edx
  int v9; // ecx
  const char *newPath; // ebx
  const char *srcPtr; // esi
  int v12; // edx
  int v13; // ecx
  _BYTE *dstPtr; // edi
  char v15; // al
  char v16; // al
  int v17; // ecx
  int v18; // ecx
  _DWORD item[11]; // [esp-8h] [ebp-2Ch] BYREF

  item[9] = a1;
  if ( Rules_RtnArgCount() )
  {
    if ( g_ClipsHelpFilePath )
    {
      if ( g_HelpSystemInitialized == 1 )
      {
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aReleasingHelpE, v2);
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], g_ClipsHelpFilePath, v3);
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)a___, v4);
        Help_UnloadTopicFile(g_ClipsHelpFilePath);
        IO_DeleteRouter((int)aWhelp);
        g_HelpSystemInitialized = 0;
      }
      Mem_SmallBlockFree((_DWORD *)g_ClipsHelpFilePath, strlen((const char *)g_ClipsHelpFilePath) + 1);
    }
    result = Lexer_ParseValueList(1, item, 111, a2);
    if ( result )
    {
      newPath = *(const char **)(item[2] + 16);
      srcPtr = newPath;
      dstPtr = Mem_SmallBlockAlloc(strlen(newPath) + 1);
      g_ClipsHelpFilePath = (int)dstPtr;
      do
      {
        v15 = *srcPtr;
        *dstPtr = *srcPtr;
        if ( !v15 )
          break;
        v16 = srcPtr[1];
        srcPtr += 2;
        dstPtr[1] = v16;
        dstPtr += 2;
      }
      while ( v16 );
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], v12, v13);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)newPath, v17);
      return Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50797C, v18);
    }
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aTheCurrentHelp, v2);
    if ( g_ClipsHelpFilePath )
    {
      dialogRouter = g_IO_LogicalNameTable_WDialog[0];
      pathToPrint = (char *)g_ClipsHelpFilePath;
    }
    else
    {
      pathToPrint = aClips_hlp;
      dialogRouter = g_IO_LogicalNameTable_WDialog[0];
    }
    Output_Write((int)dialogRouter, (int)pathToPrint, v6);
    return Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50797C, v9);
  }
  return result;
}
// 4A5E61: variable 'v2' is possibly undefined
// 4A5E71: variable 'v3' is possibly undefined
// 4A5E80: variable 'v4' is possibly undefined
// 4A5F01: variable 'v6' is possibly undefined
// 4A5F10: variable 'v9' is possibly undefined
// 4A5F6B: variable 'v12' is possibly undefined
// 4A5F6B: variable 'v13' is possibly undefined
// 4A5F77: variable 'v17' is possibly undefined
// 4A5F86: variable 'v18' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 51ACE8: using guessed type int dword_51ACE8;
// 51ACEC: using guessed type int dword_51ACEC;

//----- (004A5FA0) --------------------------------------------------------
int * Help_LoadHelpFileCommand(DWORD returnValue, double a2)
{
  int *result; // eax
  int v4; // ecx
  CHAR *dstPtr; // edi
  CHAR *srcPtr; // esi
  CHAR v7; // al
  CHAR v8; // al
  _DWORD *entryCount; // eax
  int v10; // ecx
  int v11; // ecx
  char *errorMsg; // edx
  int v13; // ecx
  CHAR fileName[80]; // [esp+0h] [ebp-D0h] BYREF
  _BYTE errorBuffer[80]; // [esp+50h] [ebp-80h] BYREF
  _DWORD item[12]; // [esp+A0h] [ebp-30h] BYREF

  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_ParseValueList(1, item, 111, a2);
  if ( result )
  {
    dstPtr = fileName;
    srcPtr = *(CHAR **)(item[2] + 16);
    do
    {
      v7 = *srcPtr;
      *dstPtr = *srcPtr;
      if ( !v7 )
        break;
      v8 = srcPtr[1];
      srcPtr += 2;
      dstPtr[1] = v8;
      dstPtr += 2;
    }
    while ( v8 );
    entryCount = Help_IndexTopicFile(fileName, errorBuffer, v4, 80, returnValue);
    if ( entryCount )
    {
      *(_DWORD *)(returnValue + 4) = 1;
      result = Rules_AddIntegerValue((signed int)entryCount);
      *(_DWORD *)(returnValue + 8) = result;
    }
    else
    {
      Rules_PrintErrorID((int)aTextpro, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToLoadFi, v10);
      if ( errorBuffer[0] )
        errorMsg = errorBuffer;
      else
        errorMsg = aNoEntriesFound;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)errorMsg, v11);
      return (int *)Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50797C, v13);
    }
  }
  return result;
}
// 4A601A: variable 'v4' is possibly undefined
// 4A603E: variable 'v10' is possibly undefined
// 4A6053: variable 'v11' is possibly undefined
// 4A6062: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (004A60A0) --------------------------------------------------------
int  Help_PrintRegionCommand(double a1)
{
  _DWORD *topicList; // edi
  _DWORD *topicListHead; // ebp
  int fp; // eax
  int v4; // ecx
  char *lineText; // edx
  int i; // eax
  char *srcPtr; // esi
  char v8; // al
  char v9; // al
  int success; // edi
  int v11; // ecx
  _DWORD *nodeToFree; // eax
  _BYTE lineBuffer[256]; // [esp+4h] [ebp-118h] BYREF
  int menuBuf; // [esp+104h] [ebp-18h] BYREF
  _DWORD statusBuf[5]; // [esp+108h] [ebp-14h] BYREF

  topicList = Rules_HelpBuildTopicListFromArgs(a1);
  topicListHead = topicList;
  fp = Rules_HelpLocateTopicEntry((const CHAR *)topicList[21], *(_DWORD *)(topicList[21] + 84), statusBuf, &menuBuf);
  if ( statusBuf[0] == -10 || statusBuf[0] == -25 || statusBuf[0] == -30 )
  {
    if ( fp )
      fclose_(fp);
    success = 0;
  }
  else
  {
    if ( !strcmp_(fp, aT_1) )
    {
      srcPtr = aStdout_3;
      do
      {
        v8 = *srcPtr;
        *(_BYTE *)topicList = *srcPtr;
        if ( !v8 )
          break;
        v9 = srcPtr[1];
        srcPtr += 2;
        *((_BYTE *)topicList + 1) = v9;
        topicList = (_DWORD *)((char *)topicList + 2);
      }
      while ( v9 );
    }
    lineText = asc_50797C;
    for ( i = (int)topicListHead; ; i = (int)topicListHead )
    {
      Output_Write(i, (int)lineText, v4);
      if ( !Help_ReadEntryLine(fp, lineBuffer, 256) )
        break;
      lineText = lineBuffer;
    }
    success = 1;
  }
  v11 = 88;
  while ( topicListHead )
  {
    nodeToFree = topicListHead;
    topicListHead = (_DWORD *)topicListHead[21];
    Mem_SmallBlockFree(nodeToFree, v11);
  }
  return success;
}
// 4A610D: variable 'v4' is possibly undefined
// 4A6180: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6190) --------------------------------------------------------
signed int  Help_UnloadHelpFileCommand(int returnValue, double a2)
{
  signed int result; // eax
  int v4; // ecx
  int fileName; // ebx
  _DWORD theValue[9]; // [esp-8h] [ebp-24h] BYREF

  theValue[7] = returnValue;
  result = Lexer_ParseValueList(1, theValue, 111, a2);
  if ( result )
  {
    fileName = *(_DWORD *)(theValue[2] + 16);
    if ( g_ClipsHelpFilePath && !strcmp_(v4, g_ClipsHelpFilePath) && g_HelpSystemInitialized == 1 )
    {
      Mem_SmallBlockFree((_DWORD *)g_ClipsHelpFilePath, strlen((const char *)g_ClipsHelpFilePath) + 1);
      g_ClipsHelpFilePath = 0;
      g_HelpSystemInitialized = 0;
      IO_DeleteRouter((int)aWhelp);
    }
    return Help_UnloadTopicFile(fileName);
  }
  return result;
}
// 4A61C3: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE8: using guessed type int dword_51ACE8;
// 51ACEC: using guessed type int dword_51ACEC;

//----- (004A6220) --------------------------------------------------------
BOOL __thiscall Help_RouterQueryMatchesWhelp(void *this)
{
  return strcmp_(this, aWhelp) == 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6240) --------------------------------------------------------
int __fastcall Rules_HelpRouterPrint(int logicalName, int message)
{
  Output_Write((int)aStdout_3, message, logicalName);
  return 1;
}

//----- (004A6250) --------------------------------------------------------
int __thiscall Rules_HelpRouterGetc(void *this)
{
  return Lexer_PeekChar((int)aStdin_3, (unsigned int)this);
}

//----- (004A6260) --------------------------------------------------------
signed int  Rules_HelpRouterUngetc(signed int theChar, int logicalName)
{
  return Lexer_SkipChar(theChar, (int)aStdin_3, logicalName);
}

//----- (004A6270) --------------------------------------------------------
_DWORD * Rules_HelpBuildTopicListFromArgs(double a1)
{
  int theIndex; // edi
  _DWORD *head; // ebp
  _DWORD *theTopic; // esi
  _DWORD *v4; // edx
  int v5; // ecx
  char *topicName; // edx
  _DWORD *i; // eax
  int argType; // [esp+4h] [ebp-30h]
  int argValue; // [esp+8h] [ebp-2Ch]
  int numArgs; // [esp+18h] [ebp-1Ch]

  theIndex = 1;
  numArgs = Rules_RtnArgCount();
  head = 0;
  if ( numArgs >= 1 )
  {
    do
    {
      theTopic = Mem_SmallBlockAlloc(0x58u);
      Rules_RtnUnknown(theIndex, v4, a1);
      if ( argType == 2 || argType == 3 )
      {
        topicName = *(char **)(argValue + 16);
      }
      else if ( argType )
      {
        if ( argType == 1 )
          topicName = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(argValue + 16));
        else
          topicName = aError_4;
      }
      else
      {
        topicName = (char *)Rules_FloatToSymbol(v5, *(double *)(argValue + 16));
      }
      strncpy_(v5, topicName);
      theTopic[21] = 0;
      theTopic[20] = 0;
      if ( head )
      {
        for ( i = head; i[21]; i = (_DWORD *)i[21] )
          ;
        i[21] = theTopic;
      }
      else
      {
        head = theTopic;
      }
      ++theIndex;
    }
    while ( theIndex <= numArgs );
  }
  return head;
}
// 4A629F: variable 'v4' is possibly undefined
// 4A62AB: variable 'v9' is possibly undefined
// 4A62BD: variable 'v10' is possibly undefined
// 4A62C0: variable 'v5' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004A6350) --------------------------------------------------------
int  Rules_HelpReadTopicListFromInput(int topicList, int *menu, int a3)
{
  int v4; // ecx
  int charIndex; // edx
  unsigned int v6; // ecx
  char inputChar; // al
  int wordLength; // ecx
  int scanIndex; // edx
  char ch; // bl
  int v11; // esi
  char v13; // bh
  char *wordSrc; // esi
  char *newTopic; // ebx
  char *topicDst; // edi
  char v17; // al
  char v18; // al
  int tailNode; // esi
  char *v20; // esi
  char *v21; // edi
  char v22; // al
  char v23; // al
  char v24; // [esp-1h] [ebp-16Dh]
  _BYTE lineBuffer[256]; // [esp+0h] [ebp-16Ch]
  char wordBuffer[80]; // [esp+100h] [ebp-6Ch] BYREF
  char *newTopicPtr; // [esp+150h] [ebp-1Ch]
  int listHead; // [esp+154h] [ebp-18h]

  Output_Write((int)aWhelp, *menu, a3);
  Output_Write((int)aWhelp, (int)aTopic_, v4);
  charIndex = 0;
  g_Lexer_PendingLineCharIndex = 0;
  v6 = -2;
  while ( 1 )
  {
    inputChar = Lexer_PeekChar((int)aWhelp, v6);
    lineBuffer[charIndex] = inputChar;
    if ( inputChar == 10 || charIndex >= 254 || g_ClipsHaltExecution )
      break;
    if ( inputChar == 9 )
    {
      lineBuffer[charIndex] = 32;
      goto LABEL_14;
    }
    if ( inputChar == 8 && charIndex )
    {
      g_Lexer_PendingLineCharIndex += v6;
      charIndex = charIndex - 2 + 1;
      ++g_Lexer_PendingLineCharIndex;
    }
    else
    {
LABEL_14:
      ++charIndex;
      ++g_Lexer_PendingLineCharIndex;
    }
  }
  wordLength = g_ClipsHaltExecution;
  g_Lexer_PendingLineCharIndex = -1;
  if ( g_ClipsHaltExecution )
  {
    Output_Write((int)aWhelp, (int)asc_50797C, g_ClipsHaltExecution);
    *(_DWORD *)(topicList + 80) = topicList;
    return topicList;
  }
  else
  {
    lineBuffer[charIndex] = 32;
    lineBuffer[charIndex + 1] = 0;
    listHead = topicList;
    scanIndex = 0;
    while ( lineBuffer[scanIndex] )
    {
      ch = lineBuffer[scanIndex];
      if ( ch == 32 || wordLength >= 80 )
      {
        if ( wordLength <= 0 )
        {
          ++scanIndex;
        }
        else
        {
          while ( 1 )
          {
            v13 = lineBuffer[scanIndex];
            if ( v13 == 32 || !v13 )
              break;
            ++scanIndex;
          }
          wordBuffer[wordLength] = 0;
          wordLength = 0;
          if ( topicList )
          {
            v20 = wordBuffer;
            v21 = (char *)topicList;
            v24 = HIBYTE(topicList);
            do
            {
              v22 = *v20;
              *v21 = *v20;
              if ( !v22 )
                break;
              v23 = v20[1];
              v20 += 2;
              v21[1] = v23;
              v21 += 2;
            }
            while ( v23 );
            topicList = *(_DWORD *)(topicList + 84);
          }
          else
          {
            wordSrc = wordBuffer;
            newTopic = (char *)Mem_SmallBlockAlloc(0x58u);
            topicDst = newTopic;
            newTopicPtr = newTopic;
            v24 = HIBYTE(newTopic);
            do
            {
              v17 = *wordSrc;
              *topicDst = *wordSrc;
              if ( !v17 )
                break;
              v18 = wordSrc[1];
              wordSrc += 2;
              topicDst[1] = v18;
              topicDst += 2;
            }
            while ( v18 );
            *((_DWORD *)newTopic + 21) = wordLength;
            tailNode = listHead;
            *((_DWORD *)newTopic + 20) = wordLength;
            if ( tailNode )
            {
              for ( ; *(_DWORD *)(tailNode + 84); tailNode = *(_DWORD *)(tailNode + 84) )
                ;
              *(_DWORD *)(tailNode + 84) = newTopicPtr;
            }
            else
            {
              listHead = (int)newTopic;
            }
          }
        }
      }
      else
      {
        ++wordLength;
        ++scanIndex;
        lineBuffer[wordLength + 255] = ch;
      }
    }
    v11 = listHead;
    *(_DWORD *)(listHead + 80) = topicList;
    return v11;
  }
}
// 4A6373: variable 'v4' is possibly undefined
// 4A638E: variable 'v6' is possibly undefined
// 4A63DC: variable 'v9' is possibly undefined
// 4A63EB: variable 'v8' is possibly undefined
// 51A628: using guessed type int dword_51A628;
// 51A968: using guessed type int dword_51A968;

//----- (004A6550) --------------------------------------------------------
int  Rules_HelpLocateTopicEntry(const CHAR *fileName, int topicList, _DWORD *statusOut, _DWORD *entryTitleOut)
{
  _DWORD *statusPtr; // edi
  int result; // eax
  int topicNode; // esi
  int v8; // ecx
  _DWORD *v9; // edx
  _DWORD *v10; // ecx
  const CHAR *v11; // eax
  _BYTE *topicName; // ebx
  int listEnd; // [esp+4h] [ebp-10h]

  statusPtr = statusOut;
  result = 0;
  if ( topicList )
    listEnd = *(_DWORD *)(topicList + 80);
  else
    listEnd = 0;
  topicNode = topicList;
  if ( topicList != listEnd )
  {
    while ( 1 )
    {
      if ( result )
        fclose_(statusOut);
      if ( !strcmp_(statusOut, asc_507B10) )
        break;
      if ( strcmp_(v8, aQuestionMark_507B14) || listEnd != *(_DWORD *)(topicNode + 84) )
      {
        v9 = entryTitleOut;
        v10 = statusPtr;
        topicName = (_BYTE *)topicNode;
        v11 = fileName;
        goto LABEL_8;
      }
      result = Help_ReopenFileAtActiveEntry(fileName, statusPtr, (DWORD)fileName);
LABEL_9:
      statusOut = (_DWORD *)*statusPtr;
      if ( *statusPtr != -10 && statusOut != (_DWORD *)-25 )
      {
        topicNode = *(_DWORD *)(topicNode + 84);
        if ( topicNode != listEnd )
          continue;
      }
      return result;
    }
    v9 = entryTitleOut;
    v10 = statusPtr;
    v11 = fileName;
    topicName = 0;
LABEL_8:
    result = Help_OpenFileAtNavigatedTopic(v11, v9, v10, topicName);
    goto LABEL_9;
  }
  return Help_OpenFileAtNavigatedTopic(fileName, entryTitleOut, statusOut, 0);
}
// 4A6580: variable 'a3' is possibly undefined
// 4A65CC: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6610) --------------------------------------------------------
signed int Rules_RegisterHelpFunctions()
{
  Rules_RegisterHostFunction(aHelp, 118, (int)aHelpfunction, (int)Help_RunInteractiveHelpBrowser, 0);
  Rules_RegisterHostFunction(aHelpPath, 118, (int)aHelppathfuncti, (int)Help_SetHelpFilePathCommand, (int)a1k);
  Rules_RegisterHostFunction(aFetch, 117, (int)aFetchcommand, (int)Help_LoadHelpFileCommand, (int)a11k_2);
  Rules_RegisterHostFunction(aToss, 98, (int)aTosscommand, (int)Help_UnloadHelpFileCommand, (int)a11k_2);
  return Rules_RegisterHostFunction(aPrintRegion, 98, (int)aPrintregioncom, (int)Help_PrintRegionCommand, (int)a2Wk);
}

//----- (004A66B0) --------------------------------------------------------
int  Rules_ConstructsToCCommand(double a1)
{
  int result; // eax
  int argCount; // ebp
  const char *fileName; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int imageId; // edi
  int maxIndices; // ebx
  _DWORD item[2]; // [esp+0h] [ebp-30h] BYREF
  int itemValue; // [esp+8h] [ebp-28h]

  result = Rules_ArgRangeCheck((int)aConstructsToC, 3);
  argCount = result;
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, item, 111, a1);
    if ( result )
    {
      fileName = *(const char **)(itemValue + 16);
      if ( (int)strlen(fileName) > 3 )
      {
        Rules_PrintWarningID((int)aConscomp, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aBaseFileNameEx, v4);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aThisMayCauseFi, v5);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aIsLimitedOnYou, v6);
      }
      result = Lexer_ParseValueList(2, item, 1, a1);
      if ( result )
      {
        imageId = *(_DWORD *)(itemValue + 16);
        if ( imageId < 0 )
        {
          return Parser_ReportError(2, (int)aPositiveIntege);
        }
        else
        {
          if ( argCount != 3 )
          {
            maxIndices = 10000;
            return Rules_ConstructsToC(fileName, imageId, maxIndices, (char)fileName);
          }
          result = Lexer_ParseValueList(3, item, 1, a1);
          if ( result )
          {
            maxIndices = *(_DWORD *)(itemValue + 16);
            if ( maxIndices >= 0 )
              return Rules_ConstructsToC(fileName, imageId, maxIndices, (char)fileName);
            return Parser_ReportError(3, (int)aPositiveIntege);
          }
        }
      }
    }
  }
  return result;
}
// 4A672B: variable 'v4' is possibly undefined
// 4A673A: variable 'v5' is possibly undefined
// 4A6749: variable 'v6' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];

//----- (004A6800) --------------------------------------------------------
signed int  Rules_ConstructsToC(const char *fileName, int imageId, int maxIndices, char a4)
{
  int v5; // ecx
  int codeGenItem; // edx
  int v7; // ecx
  int v8; // ecx
  int headerFile; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // ecx
  char v33; // bl
  int v34; // edx
  int codeItem; // esi
  int i; // edi
  int v37; // edx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  char v42; // [esp-8h] [ebp-60h]
  char v43; // [esp-8h] [ebp-60h]
  char v44; // [esp-8h] [ebp-60h]
  char v45; // [esp-8h] [ebp-60h]
  char v46; // [esp-8h] [ebp-60h]
  char v47; // [esp-8h] [ebp-60h]
  char v48; // [esp-8h] [ebp-60h]
  char v49; // [esp-8h] [ebp-60h]
  char v50; // [esp-8h] [ebp-60h]
  char v51; // [esp-8h] [ebp-60h]
  char v52; // [esp-8h] [ebp-60h]
  char v53; // [esp-8h] [ebp-60h]
  char v54; // [esp-8h] [ebp-60h]
  CHAR headerFileName[88]; // [esp+0h] [ebp-58h] BYREF

  v5 = imageId;
  codeGenItem = g_CodeGeneratorItemList;
  for ( g_ClipsCodeMaxIndicesPerArray = maxIndices; codeGenItem; codeGenItem = *(_DWORD *)(codeGenItem + 24) )
  {
    if ( *(_DWORD *)(codeGenItem + 4) )
      (*(void (__fastcall **)(int))(codeGenItem + 4))(v5);
  }
  Rules_RunPeriodicCleanup(0, 0);
  g_Rules_ConstructsToCodeBaseName = (int)fileName;
  g_ConstructsToCImageId = v7;
  g_ClipsCodeDataFile = 0;
  g_ClipsConstructCodeEntryIndexInFile = 0;
  g_ClipsExpressionCodeFileVersion = 1;
  g_Rules_ExprCodeNeedNewFileFlag = 1;
  sprintf_(headerFileName, "%s.h", fileName);
  headerFile = IO_FOpen(headerFileName, (unsigned __int8 *)aW_2, v8, (DWORD)fileName);
  g_ClipsCodeHeaderFile = headerFile;
  if ( headerFile )
  {
    Output_WriteFormatted(v11, v10, headerFile, (int)aIfndef_constru, a4);
    Output_WriteFormatted(v13, v12, g_ClipsCodeHeaderFile, (int)aDefine_constru, v42);
    Output_WriteFormatted(v15, v14, g_ClipsCodeHeaderFile, (int)aIncludeStdio_h, v43);
    Output_WriteFormatted(v16, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aIncludeSetup_h, v44);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v17, g_ClipsCodeHeaderFile, (int)aIncludeExpress, v45);
    Output_WriteFormatted(v19, v18, g_ClipsCodeHeaderFile, (int)aIncludeExtnfun, v46);
    Output_WriteFormatted(v21, v20, g_ClipsCodeHeaderFile, (int)aIncludeClips_h, v47);
    Output_WriteFormatted(v23, v22, g_ClipsCodeHeaderFile, (int)aDefineVsVoid, v48);
    Output_WriteFormatted(v25, v24, g_ClipsCodeHeaderFile, (int)asc_507D2C, v49);
    Rules_PrintExternalFunctionDeclarations(g_ClipsCodeHeaderFile, v26);
    Output_WriteFormatted(v27, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aEndif, v50);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v28, g_ClipsCodeHeaderFile, (int)asc_507D3C, v51);
    Output_WriteFormatted(v30, v29, g_ClipsCodeHeaderFile, (int)aExternArrayDef, v52);
    Output_WriteFormatted(v32, v31, g_ClipsCodeHeaderFile, (int)asc_507D7C, v53);
    Compiler_GenerateConstructTables((DWORD)fileName);
    Rules_WriteFunctionDefinitionRecordsToCode(fileName);
    Rules_WriteHashedExpressionsToCode((DWORD)fileName);
    v33 = g_ClipsCodeHeaderFile;
    Compiler_WriteConstraintTableFile(fileName, v34, g_ConstructsToCImageId, g_ClipsCodeHeaderFile, g_ClipsCodeMaxIndicesPerArray);
    codeItem = g_CodeGeneratorItemList;
    for ( i = 5; codeItem; codeItem = *(_DWORD *)(codeItem + 24) )
    {
      if ( *(_DWORD *)(codeItem + 12) )
      {
        v33 = g_ClipsCodeHeaderFile;
        v37 = i++;
        (*(void (__fastcall **)(int, int, int))(codeItem + 12))(g_ConstructsToCImageId, v37, g_ClipsCodeMaxIndicesPerArray);
      }
    }
    Rules_RestoreAtomicValueBuckets();
    if ( g_ClipsCodeDataFile )
    {
      Output_WriteFormatted(v38, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_507DA0, v54);
      fclose_(v39);
    }
    Rules_WriteConstructsToCDriverFile(fileName, v33, (DWORD)fileName);
    fclose_(v40);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v11, (int)headerFileName);
    return 0;
  }
}
// 4A681F: variable 'v5' is possibly undefined
// 4A6822: variable 'v6' is possibly undefined
// 4A683A: variable 'v7' is possibly undefined
// 4A6875: variable 'v8' is possibly undefined
// 4A688F: variable 'v11' is possibly undefined
// 4A688F: variable 'v10' is possibly undefined
// 4A68A3: variable 'v13' is possibly undefined
// 4A68A3: variable 'v12' is possibly undefined
// 4A68A3: variable 'v42' is possibly undefined
// 4A68B6: variable 'v15' is possibly undefined
// 4A68B6: variable 'v14' is possibly undefined
// 4A68B6: variable 'v43' is possibly undefined
// 4A68CA: variable 'v16' is possibly undefined
// 4A68CA: variable 'v44' is possibly undefined
// 4A68DE: variable 'v17' is possibly undefined
// 4A68DE: variable 'v45' is possibly undefined
// 4A68F2: variable 'v19' is possibly undefined
// 4A68F2: variable 'v18' is possibly undefined
// 4A68F2: variable 'v46' is possibly undefined
// 4A6906: variable 'v21' is possibly undefined
// 4A6906: variable 'v20' is possibly undefined
// 4A6906: variable 'v47' is possibly undefined
// 4A691A: variable 'v23' is possibly undefined
// 4A691A: variable 'v22' is possibly undefined
// 4A691A: variable 'v48' is possibly undefined
// 4A692D: variable 'v25' is possibly undefined
// 4A692D: variable 'v24' is possibly undefined
// 4A692D: variable 'v49' is possibly undefined
// 4A693A: variable 'v26' is possibly undefined
// 4A694B: variable 'v27' is possibly undefined
// 4A694B: variable 'v50' is possibly undefined
// 4A695F: variable 'v28' is possibly undefined
// 4A695F: variable 'v51' is possibly undefined
// 4A6973: variable 'v30' is possibly undefined
// 4A6973: variable 'v29' is possibly undefined
// 4A6973: variable 'v52' is possibly undefined
// 4A6987: variable 'v32' is possibly undefined
// 4A6987: variable 'v31' is possibly undefined
// 4A6987: variable 'v53' is possibly undefined
// 4A69BC: variable 'v34' is possibly undefined
// 4A6A0C: variable 'v38' is possibly undefined
// 4A6A0C: variable 'v54' is possibly undefined
// 4A6A19: variable 'v39' is possibly undefined
// 4A6A2A: variable 'v40' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACF0: using guessed type int dword_51ACF0;
// 51ACF4: using guessed type int dword_51ACF4;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6D4: using guessed type int dword_54E6D4;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;
// 54E6E0: using guessed type int dword_54E6E0;
// 54E6E4: using guessed type int dword_54E6E4;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A6B10) --------------------------------------------------------
int  Rules_PrintExternalFunctionDeclarations(int codeFile, int a2)
{
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int result; // eax
  int v9; // edx
  int v10; // ecx
  int i; // ebx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  char v17; // [esp-8h] [ebp-Ch]
  char v18; // [esp-8h] [ebp-Ch]
  char v19; // [esp-8h] [ebp-Ch]
  char v20; // [esp-8h] [ebp-Ch]
  char v21; // [esp-8h] [ebp-Ch]

  Output_WriteFormatted(codeFile, a2, codeFile, (int)asc_507D2C, a2);
  Output_WriteFormatted(v3, v2, v3, (int)asc_507DA4, v17);
  Output_WriteFormatted(v5, v4, v5, (int)aExternalFuncti, v18);
  Output_WriteFormatted(v7, v6, v7, (int)asc_507DF4, v19);
  result = Rules_GetFunctionDefinitionListHead();
  for ( i = result; i; i = *(_DWORD *)(i + 27) )
  {
    Output_WriteFormatted(v10, v9, v10, (int)aExtern, v20);
    switch ( *(_BYTE *)(i + 8) )
    {
      case 'a':
      case 'x':
        Output_WriteFormatted(v13, v12, v13, (int)aVoid, v21);
        break;
      case 'b':
      case 'i':
        Output_WriteFormatted(v13, v12, v13, (int)aInt, v21);
        break;
      case 'c':
        Output_WriteFormatted(v13, v12, v13, (int)aChar, v21);
        break;
      case 'd':
        Output_WriteFormatted(v13, v12, v13, (int)aDouble, v21);
        break;
      case 'f':
        Output_WriteFormatted(v13, v12, v13, (int)aFloat_3, v21);
        break;
      case 'j':
      case 'k':
      case 'm':
      case 'n':
      case 'u':
      case 'v':
        Output_WriteFormatted(v13, v12, v13, (int)aVoid_0, v21);
        break;
      case 'l':
        Output_WriteFormatted(v13, v12, v13, (int)aLong, v21);
        break;
      case 'o':
      case 's':
      case 'w':
        Output_WriteFormatted(v13, v12, v13, (int)aSymbol_hn, v21);
        break;
      default:
        Rules_ReportSystemError(v13, 1);
        break;
    }
    Output_WriteFormatted(v14, *(_DWORD *)(i + 4), v14, (int)aS_10, *(_DWORD *)(i + 4));
    switch ( *(_BYTE *)(i + 8) )
    {
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'f':
      case 'i':
      case 'l':
      case 'o':
      case 's':
      case 'v':
      case 'w':
      case 'x':
        Output_WriteFormatted(v16, v15, v16, (int)aVoid_arg, v21);
        break;
      case 'j':
      case 'k':
      case 'm':
      case 'n':
      case 'u':
        Output_WriteFormatted(v16, v15, v16, (int)aData_object_pt, v21);
        break;
      default:
        break;
    }
    result = Output_WriteFormatted(v16, v15, v16, (int)asc_507E90, v21);
  }
  return result;
}
// 4A6B29: variable 'v3' is possibly undefined
// 4A6B29: variable 'v2' is possibly undefined
// 4A6B29: variable 'v17' is possibly undefined
// 4A6B37: variable 'v5' is possibly undefined
// 4A6B37: variable 'v4' is possibly undefined
// 4A6B37: variable 'v18' is possibly undefined
// 4A6B45: variable 'v7' is possibly undefined
// 4A6B45: variable 'v6' is possibly undefined
// 4A6B45: variable 'v19' is possibly undefined
// 4A6B62: variable 'v10' is possibly undefined
// 4A6B62: variable 'v9' is possibly undefined
// 4A6B62: variable 'v20' is possibly undefined
// 4A6B89: variable 'v13' is possibly undefined
// 4A6B89: variable 'v12' is possibly undefined
// 4A6B89: variable 'v21' is possibly undefined
// 4A6B9B: variable 'v14' is possibly undefined
// 4A6BBE: variable 'v16' is possibly undefined
// 4A6BBE: variable 'v15' is possibly undefined

//----- (004A6C40) --------------------------------------------------------
signed int  Rules_WriteFunctionDefinitionRecordsToCode(const char *fileName)
{
  int version; // edi
  int functionList; // ecx
  int bsaveIndex; // esi
  DWORD i; // ebp
  signed int result; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // edx
  int v14; // ecx
  int fctnPtr; // esi
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int v32; // ecx
  char v34; // [esp+0h] [ebp-20h]
  char v35; // [esp+0h] [ebp-20h]
  char v36; // [esp+0h] [ebp-20h]
  const char *v37; // [esp+0h] [ebp-20h]
  char v38; // [esp+0h] [ebp-20h]
  char v39; // [esp+0h] [ebp-20h]
  char v40; // [esp+0h] [ebp-20h]
  int entryCount; // [esp+4h] [ebp-1Ch]

  version = 1;
  functionList = Rules_GetFunctionDefinitionListHead();
  bsaveIndex = 0;
  for ( i = 1; functionList; ++bsaveIndex )
  {
    *(_WORD *)(functionList + 25) = bsaveIndex;
    functionList = *(_DWORD *)(functionList + 27);
  }
  result = Rules_OpenConstructCodeFile(fileName, 2, 1, 1u);
  if ( result )
  {
    Output_WriteFormatted(result, result, result, (int)asc_507E94, (char)fileName);
    Output_WriteFormatted(v7, v6, v6, (int)asc_507DA4, v34);
    Output_WriteFormatted(v9, v8, v8, (int)aFunctionListDe, v35);
    Output_WriteFormatted(v11, v10, v10, (int)asc_507DF4, v36);
    v12 = Rules_GetFunctionDefinitionListHead();
    entryCount = v13;
    fctnPtr = v12;
    while ( fctnPtr )
    {
      if ( i )
      {
        Output_WriteFormatted(v14, g_ConstructsToCImageId, v14, (int)aStructFunction, g_ConstructsToCImageId);
        Output_WriteFormatted(v17, v16, g_ClipsCodeHeaderFile, (int)aExternStructFu, g_ConstructsToCImageId);
        i = 0;
      }
      Output_WriteFormatted(v14, v13, v14, (int)asc_507F14, (char)v37);
      Compiler_WriteSymbolReference(v18, *(_DWORD *)fctnPtr, v18);
      Output_WriteFormatted(v20, v19, v20, (int)aS_4, *(_DWORD *)(fctnPtr + 4));
      Output_WriteFormatted(v22, v21, v22, (int)aC, *(_BYTE *)(fctnPtr + 8));
      Output_WriteFormatted(v23, *(_DWORD *)(fctnPtr + 4), v23, (int)aPtifS, *(_DWORD *)(fctnPtr + 4));
      Output_WriteFormatted(v25, v24, v25, (int)aNull_0, v38);
      if ( *(_DWORD *)(fctnPtr + 17) )
        Output_WriteFormatted(v27, v26, v27, (int)aS_5, *(_DWORD *)(fctnPtr + 17));
      else
        Output_WriteFormatted(v27, v26, v27, (int)aNull_0, v39);
      Output_WriteFormatted(v29, v28, v29, (int)a000, v39);
      Rules_WriteFunctionRecordRefToCode(v30, *(_DWORD *)(fctnPtr + 27), v30);
      fctnPtr = *(_DWORD *)(fctnPtr + 27);
      if ( (__int16)++entryCount <= g_ClipsCodeMaxIndicesPerArray && fctnPtr )
      {
        Output_WriteFormatted(v31, g_ClipsCodeMaxIndicesPerArray, v31, (int)asc_507F54, v40);
      }
      else
      {
        Output_WriteFormatted(v31, g_ClipsCodeMaxIndicesPerArray, v31, (int)asc_507F4C, v40);
        fclose_(v32);
        ++version;
        entryCount = 1;
        if ( fctnPtr )
        {
          result = Rules_OpenConstructCodeFile(v37, 2, version, i);
          v14 = result;
          if ( !result )
            return result;
          i = 1;
        }
      }
    }
    return 1;
  }
  return result;
}
// 4A6CA7: variable 'v7' is possibly undefined
// 4A6CA7: variable 'v6' is possibly undefined
// 4A6CA7: variable 'v34' is possibly undefined
// 4A6CB5: variable 'v9' is possibly undefined
// 4A6CB5: variable 'v8' is possibly undefined
// 4A6CB5: variable 'v35' is possibly undefined
// 4A6CC3: variable 'v11' is possibly undefined
// 4A6CC3: variable 'v10' is possibly undefined
// 4A6CC3: variable 'v36' is possibly undefined
// 4A6CD5: variable 'v13' is possibly undefined
// 4A6CF5: variable 'v14' is possibly undefined
// 4A6D11: variable 'v17' is possibly undefined
// 4A6D11: variable 'v16' is possibly undefined
// 4A6D21: variable 'v37' is possibly undefined
// 4A6D2D: variable 'v18' is possibly undefined
// 4A6D3C: variable 'v20' is possibly undefined
// 4A6D3C: variable 'v19' is possibly undefined
// 4A6D50: variable 'v22' is possibly undefined
// 4A6D50: variable 'v21' is possibly undefined
// 4A6D62: variable 'v23' is possibly undefined
// 4A6D70: variable 'v25' is possibly undefined
// 4A6D70: variable 'v24' is possibly undefined
// 4A6D70: variable 'v38' is possibly undefined
// 4A6D8A: variable 'v27' is possibly undefined
// 4A6D8A: variable 'v26' is possibly undefined
// 4A6D98: variable 'v29' is possibly undefined
// 4A6D98: variable 'v28' is possibly undefined
// 4A6D98: variable 'v39' is possibly undefined
// 4A6DA5: variable 'v30' is possibly undefined
// 4A6DC9: variable 'v31' is possibly undefined
// 4A6DC9: variable 'v40' is possibly undefined
// 4A6DD3: variable 'v32' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A6E50) --------------------------------------------------------
int  Rules_WriteFunctionRecordRefToCode(int theFile, int fctnPtr, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( fctnPtr )
    return Output_WriteFormatted(*(__int16 *)(fctnPtr + 25), *(__int16 *)(fctnPtr + 25) % g_ClipsCodeMaxIndicesPerArray, theFile, (int)aPD_DD, g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, theFile, (int)aNull_1, v4);
}
// 4A6E5E: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004A6EB0) --------------------------------------------------------
signed int  Rules_WriteConstructsToCDriverFile(const char *fileName, char a2, DWORD a3)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int fp; // esi
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // edx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // edx
  int v28; // ecx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // ecx
  int v33; // edx
  int v34; // ecx
  int v35; // edx
  int v36; // ecx
  int v37; // edx
  int v38; // ecx
  int v39; // edx
  int v40; // ecx
  int v41; // edx
  int v42; // ecx
  int v43; // edx
  int v44; // ecx
  int v45; // edx
  int v46; // ecx
  int v47; // edx
  int v48; // ecx
  int v49; // edx
  int v50; // edx
  int v51; // ecx
  int v52; // edx
  int v53; // ecx
  int v54; // edx
  int v55; // ecx
  int v56; // edx
  int v57; // ecx
  int v58; // edx
  int i; // ecx
  int v60; // edx
  int v61; // ecx
  int v62; // ecx
  char v64; // [esp-8h] [ebp-68h]
  char v65; // [esp-8h] [ebp-68h]
  char v66; // [esp-8h] [ebp-68h]
  char v67; // [esp-8h] [ebp-68h]
  char v68; // [esp-8h] [ebp-68h]
  char v69; // [esp-8h] [ebp-68h]
  char v70; // [esp-8h] [ebp-68h]
  char v71; // [esp-8h] [ebp-68h]
  char v72; // [esp-8h] [ebp-68h]
  char v73; // [esp-8h] [ebp-68h]
  char v74; // [esp-8h] [ebp-68h]
  char v75; // [esp-8h] [ebp-68h]
  char v76; // [esp-8h] [ebp-68h]
  char v77; // [esp-8h] [ebp-68h]
  char v78; // [esp-8h] [ebp-68h]
  char v79; // [esp-8h] [ebp-68h]
  char v80; // [esp-8h] [ebp-68h]
  char v81; // [esp-8h] [ebp-68h]
  char v82; // [esp-8h] [ebp-68h]
  CHAR fileNameBuffer[96]; // [esp+0h] [ebp-60h] BYREF

  sprintf_(fileNameBuffer, "%s.c", fileName);
  v4 = IO_FOpen(fileNameBuffer, (unsigned __int8 *)aW_2, v3, a3);
  fp = v4;
  if ( v4 )
  {
    Output_WriteFormatted(v5, v4, v4, (int)aIncludeS_h, v5);
    Output_WriteFormatted(v8, v7, v7, (int)asc_507D2C, a2);
    Output_WriteFormatted(v10, v9, v9, (int)aIncludeUtility, v64);
    Output_WriteFormatted(v12, v11, v11, (int)aIncludeGenerat, v65);
    Output_WriteFormatted(v14, v13, v13, (int)aIncludeExpress, v66);
    Output_WriteFormatted(v16, v15, v15, (int)aIncludeExtnfun, v67);
    Output_WriteFormatted(v18, v17, v17, (int)aIncludeObjrtmc, v68);
    Output_WriteFormatted(v20, v19, v19, (int)aIncludeRulebld, v69);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v21, g_ClipsCodeHeaderFile, (int)aIfAnsi_compile, v70);
    Output_WriteFormatted(v23, v22, g_ClipsCodeHeaderFile, (int)aVoidInitcimage, g_ConstructsToCImageId);
    Output_WriteFormatted(v25, v24, g_ClipsCodeHeaderFile, (int)aElse, v71);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v26, g_ClipsCodeHeaderFile, (int)aVoidInitcima_0, g_ConstructsToCImageId);
    Output_WriteFormatted(v28, v27, g_ClipsCodeHeaderFile, (int)aEndif_0, v72);
    Output_WriteFormatted(v30, v29, v29, (int)asc_507D2C, v73);
    Output_WriteFormatted(v32, v31, v31, (int)asc_508048, v74);
    Output_WriteFormatted(v34, v33, v33, (int)aConstructImage, v75);
    Output_WriteFormatted(v36, v35, v35, (int)asc_508048, v76);
    Output_WriteFormatted(v38, v37, v37, (int)aVoidInitcima_1, g_ConstructsToCImageId);
    Output_WriteFormatted(v40, v39, v39, (int)asc_5080C0, v77);
    Output_WriteFormatted(v42, v41, v41, (int)aClear_0, v78);
    Output_WriteFormatted(v44, v43, v43, (int)aPeriodiccleanu, v79);
    Output_WriteFormatted(v46, v45, v45, (int)aSetsymboltable, g_ConstructsToCImageId);
    Output_WriteFormatted(v48, v47, v47, (int)aSetfloattableF, g_ConstructsToCImageId);
    Output_WriteFormatted(g_ConstructsToCImageId, v49, v49, (int)aSetintegertabl, g_ConstructsToCImageId);
    Output_WriteFormatted(v51, v50, v50, (int)aSetbitmaptable, g_ConstructsToCImageId);
    Output_WriteFormatted(v53, v52, v52, (int)aRefreshspecial, v80);
    Output_WriteFormatted(v55, v54, v54, (int)aInstallfunctio, g_ConstructsToCImageId);
    Output_WriteFormatted(v57, v56, v56, (int)aInitexpression, v81);
    for ( i = g_CodeGeneratorItemList; i; i = *(_DWORD *)(i + 24) )
    {
      if ( *(_DWORD *)(i + 8) )
      {
        (*(void (__fastcall **)(int, int))(i + 8))(i, g_ConstructsToCImageId);
        Output_WriteFormatted(v61, v60, fp, (int)asc_507D2C, v82);
      }
    }
    Output_WriteFormatted(i, v58, fp, (int)asc_5081DC, v82);
    fclose_(v62);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v5, (int)fileNameBuffer);
    return 0;
  }
}
// 4A6EB0: could not find valid save-restore pair for ebx
// 4A6ED3: variable 'v3' is possibly undefined
// 4A6EED: variable 'v5' is possibly undefined
// 4A6EFB: variable 'v8' is possibly undefined
// 4A6EFB: variable 'v7' is possibly undefined
// 4A6F09: variable 'v10' is possibly undefined
// 4A6F09: variable 'v9' is possibly undefined
// 4A6F09: variable 'v64' is possibly undefined
// 4A6F17: variable 'v12' is possibly undefined
// 4A6F17: variable 'v11' is possibly undefined
// 4A6F17: variable 'v65' is possibly undefined
// 4A6F25: variable 'v14' is possibly undefined
// 4A6F25: variable 'v13' is possibly undefined
// 4A6F25: variable 'v66' is possibly undefined
// 4A6F33: variable 'v16' is possibly undefined
// 4A6F33: variable 'v15' is possibly undefined
// 4A6F33: variable 'v67' is possibly undefined
// 4A6F41: variable 'v18' is possibly undefined
// 4A6F41: variable 'v17' is possibly undefined
// 4A6F41: variable 'v68' is possibly undefined
// 4A6F4F: variable 'v20' is possibly undefined
// 4A6F4F: variable 'v19' is possibly undefined
// 4A6F4F: variable 'v69' is possibly undefined
// 4A6F63: variable 'v21' is possibly undefined
// 4A6F63: variable 'v70' is possibly undefined
// 4A6F7E: variable 'v23' is possibly undefined
// 4A6F7E: variable 'v22' is possibly undefined
// 4A6F92: variable 'v25' is possibly undefined
// 4A6F92: variable 'v24' is possibly undefined
// 4A6F92: variable 'v71' is possibly undefined
// 4A6FAC: variable 'v26' is possibly undefined
// 4A6FC0: variable 'v28' is possibly undefined
// 4A6FC0: variable 'v27' is possibly undefined
// 4A6FC0: variable 'v72' is possibly undefined
// 4A6FCE: variable 'v30' is possibly undefined
// 4A6FCE: variable 'v29' is possibly undefined
// 4A6FCE: variable 'v73' is possibly undefined
// 4A6FDC: variable 'v32' is possibly undefined
// 4A6FDC: variable 'v31' is possibly undefined
// 4A6FDC: variable 'v74' is possibly undefined
// 4A6FEA: variable 'v34' is possibly undefined
// 4A6FEA: variable 'v33' is possibly undefined
// 4A6FEA: variable 'v75' is possibly undefined
// 4A6FF8: variable 'v36' is possibly undefined
// 4A6FF8: variable 'v35' is possibly undefined
// 4A6FF8: variable 'v76' is possibly undefined
// 4A700D: variable 'v38' is possibly undefined
// 4A700D: variable 'v37' is possibly undefined
// 4A701B: variable 'v40' is possibly undefined
// 4A701B: variable 'v39' is possibly undefined
// 4A701B: variable 'v77' is possibly undefined
// 4A7029: variable 'v42' is possibly undefined
// 4A7029: variable 'v41' is possibly undefined
// 4A7029: variable 'v78' is possibly undefined
// 4A7037: variable 'v44' is possibly undefined
// 4A7037: variable 'v43' is possibly undefined
// 4A7037: variable 'v79' is possibly undefined
// 4A704C: variable 'v46' is possibly undefined
// 4A704C: variable 'v45' is possibly undefined
// 4A7060: variable 'v48' is possibly undefined
// 4A7060: variable 'v47' is possibly undefined
// 4A7075: variable 'v49' is possibly undefined
// 4A708A: variable 'v51' is possibly undefined
// 4A708A: variable 'v50' is possibly undefined
// 4A7098: variable 'v53' is possibly undefined
// 4A7098: variable 'v52' is possibly undefined
// 4A7098: variable 'v80' is possibly undefined
// 4A70AD: variable 'v55' is possibly undefined
// 4A70AD: variable 'v54' is possibly undefined
// 4A70BB: variable 'v57' is possibly undefined
// 4A70BB: variable 'v56' is possibly undefined
// 4A70BB: variable 'v81' is possibly undefined
// 4A70EA: variable 'v61' is possibly undefined
// 4A70EA: variable 'v60' is possibly undefined
// 4A70EA: variable 'v82' is possibly undefined
// 4A70F2: variable 'i' is possibly undefined
// 4A70FF: variable 'v58' is possibly undefined
// 4A7109: variable 'v62' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACF0: using guessed type int dword_51ACF0;
// 51ACF4: using guessed type int dword_51ACF4;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A7140) --------------------------------------------------------
int  Rules_OpenConstructCodeFile(const char *fileName, int fileID, int version, DWORD reopenOldFile)
{
  char v4; // si
  int v5; // ecx
  char *fileMode; // edx
  int v7; // eax
  int v8; // ecx
  int fp; // ebx
  int v10; // edx
  int v11; // ecx
  CHAR fileNameBuffer[84]; // [esp+0h] [ebp-54h] BYREF

  v4 = (char)fileName;
  sprintf_(fileNameBuffer, "%s%d_%d.c", fileName, fileID, version);
  if ( v5 )
    fileMode = aA_0;
  else
    fileMode = aW_2;
  v7 = IO_FOpen(fileNameBuffer, (unsigned __int8 *)fileMode, v5, reopenOldFile);
  fp = v7;
  if ( v7 )
  {
    if ( !v8 )
    {
      Output_WriteFormatted(0, v7, v7, (int)aIncludeS_h, v4);
      Output_WriteFormatted(v11, v10, v10, (int)asc_507D2C, fileNameBuffer[0]);
    }
    return fp;
  }
  else
  {
    Rules_OpenFileErrorMessage(v8, (int)fileNameBuffer);
    return 0;
  }
}
// 4A715D: variable 'v5' is possibly undefined
// 4A7175: variable 'v8' is possibly undefined
// 4A718C: variable 'v11' is possibly undefined
// 4A718C: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004A71C0) --------------------------------------------------------
signed int  Rules_WriteHashedExpressionsToCode(DWORD reopenOldFile)
{
  int i; // ebx
  signed int result; // eax
  int j; // ecx
  __int16 *exprPtr; // edx
  int v5; // ecx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = g_ExpressionHashTable;
    for ( j = *(_DWORD *)(i + g_ExpressionHashTable); j; j = *(_DWORD *)(v5 + 12) )
    {
      exprPtr = *(__int16 **)(j + 8);
      *(_DWORD *)(j + 16) = g_ClipsCodeMaxIndicesPerArray * g_ClipsExpressionCodeFileVersion + g_ClipsConstructCodeEntryIndexInFile;
      result = Rules_ExpressionToCode(0, exprPtr, j, reopenOldFile);
    }
  }
  return result;
}
// 4A71FE: variable 'v5' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;

//----- (004A7220) --------------------------------------------------------
int  Rules_WriteExpressionRefToCode(int theFile, __int16 *theExpression, int maxIndices, char imageID)
{
  signed int exprID; // eax
  char v9; // [esp+0h] [ebp-8h]

  if ( !theExpression )
    return Output_WriteFormatted(maxIndices, 0, theFile, (int)aNull_1, v9);
  exprID = AST_GetHashedNodeIndex(theExpression);
  return Output_WriteFormatted(exprID, exprID % maxIndices, theFile, (int)aED_LdLd, imageID);
}
// 4A7234: variable 'v9' is possibly undefined

//----- (004A7270) --------------------------------------------------------
signed int  Rules_ExpressionToCode(int theFile, __int16 *theExpression, int a3, DWORD reopenOldFile)
{
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int dataFile; // eax
  int v11; // edx
  int v12; // ecx
  char v13; // [esp+0h] [ebp-10h]

  if ( theExpression )
  {
    if ( theFile )
      Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, g_ClipsConstructCodeEntryIndexInFile, theFile, (int)aED_DLd, g_ConstructsToCImageId);
    if ( g_Rules_ExprCodeNeedNewFileFlag == 1 )
    {
      dataFile = Rules_OpenConstructCodeFile((const char *)g_Rules_ConstructsToCodeBaseName, 3, g_ClipsExpressionCodeFileVersion, reopenOldFile);
      g_ClipsCodeDataFile = dataFile;
      if ( !dataFile )
        return -1;
      Output_WriteFormatted(g_ConstructsToCImageId, g_ClipsExpressionCodeFileVersion, dataFile, (int)aStructExprED_D, g_ConstructsToCImageId);
      Output_WriteFormatted(v12, v11, g_ClipsCodeHeaderFile, (int)aExternStructEx, g_ConstructsToCImageId);
      g_Rules_ExprCodeNeedNewFileFlag = 0;
    }
    else
    {
      Output_WriteFormatted(a3, (int)theExpression, g_ClipsCodeDataFile, (int)asc_508250, v13);
    }
    Rules_WriteExpressionNodeToCode(theExpression, v6);
    if ( g_ClipsConstructCodeEntryIndexInFile >= g_ClipsCodeMaxIndicesPerArray )
    {
      g_ClipsConstructCodeEntryIndexInFile = 0;
      ++g_ClipsExpressionCodeFileVersion;
      Output_WriteFormatted(0, v7, g_ClipsCodeDataFile, (int)asc_507DA0, v13);
      fclose_(v8);
      g_ClipsCodeDataFile = v9;
      g_Rules_ExprCodeNeedNewFileFlag = 1;
    }
    return 1;
  }
  else
  {
    if ( theFile )
      Output_WriteFormatted(a3, 0, theFile, (int)aNull_1, v13);
    return 0;
  }
}
// 4A7284: variable 'v13' is possibly undefined
// 4A72CF: variable 'a3' is possibly undefined
// 4A72CF: variable 'a2' is possibly undefined
// 4A72D9: variable 'v6' is possibly undefined
// 4A730C: variable 'v7' is possibly undefined
// 4A731E: variable 'v8' is possibly undefined
// 4A7323: variable 'v9' is possibly undefined
// 4A739A: variable 'v12' is possibly undefined
// 4A739A: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6D4: using guessed type int dword_54E6D4;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;
// 54E6E0: using guessed type int dword_54E6E0;
// 54E6E4: using guessed type int dword_54E6E4;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A73B0) --------------------------------------------------------
__int16 * Rules_WriteExpressionNodeToCode(__int16 *result, int a2)
{
  __int16 *exprNode; // esi
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  unsigned __int16 nodeType; // ax
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // edx
  char v20; // [esp+0h] [ebp-18h]
  char v21; // [esp+0h] [ebp-18h]
  char v22; // [esp+0h] [ebp-18h]
  char v23; // [esp+0h] [ebp-18h]

  exprNode = result;
  if ( result )
  {
    while ( 1 )
    {
      Output_WriteFormatted(a2, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_507F14, v20);
      Output_WriteFormatted(g_ClipsCodeDataFile, v3, g_ClipsCodeDataFile, (int)aD_37, *exprNode);
      Output_WriteFormatted(v5, v4, g_ClipsCodeDataFile, (int)aVs, v21);
      nodeType = *exprNode;
      if ( (unsigned __int16)*exprNode >= 0xAu )
      {
        if ( (unsigned __int16)*exprNode <= 0xAu )
        {
          Rules_WriteFunctionRecordRefToCode(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), v7);
        }
        else if ( nodeType >= 0x23u )
        {
          if ( nodeType <= 0x23u )
          {
            Rules_DeftemplateWriteRecordRefToCode(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
          }
          else if ( nodeType >= 0x3Cu )
          {
            if ( nodeType <= 0x3Cu )
            {
              Defglobal_WriteDefglobalArrayReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
            }
            else
            {
              if ( nodeType != 105 )
                goto LABEL_20;
              Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)aNull_1, v22);
            }
          }
          else
          {
            if ( nodeType != 57 )
              goto LABEL_20;
            ObjectsCompiler_WriteDefclassPointerRef(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
          }
        }
        else if ( nodeType < 0xCu )
        {
          Defgeneric_PrintModuleIndexOrNull(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
        }
        else
        {
          if ( nodeType > 0xCu )
          {
            if ( nodeType != 13 )
              goto LABEL_20;
LABEL_36:
            Compiler_WriteSymbolReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), v7);
            goto LABEL_6;
          }
          Deffunction_WriteConstructReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), g_ClipsCodeMaxIndicesPerArray);
        }
      }
      else if ( nodeType >= 3u )
      {
        if ( nodeType <= 3u )
          goto LABEL_36;
        if ( nodeType >= 7u )
        {
          if ( nodeType > 7u )
          {
            if ( nodeType != 8 )
            {
LABEL_20:
              v18 = g_Clips_PrimitiveEntityTable[*exprNode];
              if ( v18 )
              {
                if ( (*(_BYTE *)(v18 + 1) & 0x40) != 0 )
                  Compiler_WriteBitMapReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1), v7);
                else
                  Output_WriteFormatted(g_ClipsCodeDataFile, v18, g_ClipsCodeDataFile, (int)aNull_1, v22);
              }
              else
              {
                Output_WriteFormatted(v7, 0, g_ClipsCodeDataFile, (int)aNull_1, v22);
              }
              goto LABEL_6;
            }
            goto LABEL_36;
          }
          Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)aDummyinstance, v22);
        }
        else
        {
          if ( nodeType != 6 )
            goto LABEL_20;
          Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)aDummyfact, v22);
        }
      }
      else
      {
        if ( !nodeType )
        {
          Compiler_WriteFloatReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1));
          goto LABEL_6;
        }
        if ( nodeType > 1u )
          goto LABEL_36;
        Compiler_WriteIntegerReference(g_ClipsCodeDataFile, *(_DWORD *)(exprNode + 1));
      }
LABEL_6:
      Output_WriteFormatted(v10, v9, g_ClipsCodeDataFile, (int)asc_508278, v22);
      ++g_ClipsConstructCodeEntryIndexInFile;
      if ( *(_DWORD *)(exprNode + 3) )
        Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, v11, g_ClipsCodeDataFile, (int)aED_DLd_0, g_ConstructsToCImageId);
      else
        Output_WriteFormatted(v12, v11, g_ClipsCodeDataFile, (int)aNull_0, v23);
      if ( *(_DWORD *)(exprNode + 5) )
      {
        AST_CountTreeNodes(*(_DWORD *)(exprNode + 3));
        result = (__int16 *)Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, v19, g_ClipsCodeDataFile, (int)aED_DLd_1, g_ConstructsToCImageId);
      }
      else
      {
        result = (__int16 *)Output_WriteFormatted(v14, v13, g_ClipsCodeDataFile, (int)aNull_2, v23);
      }
      if ( *(_DWORD *)(exprNode + 3) )
      {
        Output_WriteFormatted(v16, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_508250, v23);
        result = (__int16 *)Rules_WriteExpressionNodeToCode(*(_DWORD *)(exprNode + 3), v17);
      }
      exprNode = *(__int16 **)(exprNode + 5);
      if ( !exprNode )
        return result;
      Output_WriteFormatted(g_ClipsCodeDataFile, v15, g_ClipsCodeDataFile, (int)asc_508250, v23);
    }
  }
  return result;
}
// 4A73CC: variable 'a2' is possibly undefined
// 4A73CC: variable 'v20' is possibly undefined
// 4A73E4: variable 'v3' is possibly undefined
// 4A73F8: variable 'v5' is possibly undefined
// 4A73F8: variable 'v4' is possibly undefined
// 4A73F8: variable 'v21' is possibly undefined
// 4A7443: variable 'v10' is possibly undefined
// 4A7443: variable 'v9' is possibly undefined
// 4A7443: variable 'v22' is possibly undefined
// 4A746F: variable 'v12' is possibly undefined
// 4A746F: variable 'v11' is possibly undefined
// 4A746F: variable 'v23' is possibly undefined
// 4A748D: variable 'v14' is possibly undefined
// 4A748D: variable 'v13' is possibly undefined
// 4A74A7: variable 'v16' is possibly undefined
// 4A74B2: variable 'v17' is possibly undefined
// 4A74CA: variable 'v15' is possibly undefined
// 4A7531: variable 'v7' is possibly undefined
// 4A7583: variable 'v6' is possibly undefined
// 4A7716: variable 'v19' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E530: using guessed type int dword_54E530[70];
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6D4: using guessed type int dword_54E6D4;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;

//----- (004A7730) --------------------------------------------------------
signed int Rules_RegisterConstructsToCFunction()
{
  return Rules_RegisterHostFunction(aConstructsToC, 118, (int)aConstructstocc, (int)Rules_ConstructsToCCommand, (int)a23Kii);
}

//----- (004A7760) --------------------------------------------------------
int  Rules_AddCodeGeneratorItem(int itemName, int priority, int initFunction, int beforeFunction, int generateFunction, int arrayCount)
{
  int construct_code_count; // ecx
  _DWORD *freeNode; // ebx
  int prevItem; // ebp
  _DWORD *newItem; // eax
  int newItemPtr; // ebx
  int arrayBytes; // edi
  _DWORD *nameCopy; // eax
  int slot_offset; // edx
  char *copySrc; // esi
  char *copyDst; // edi
  int nextOffset; // edx
  char v20; // al
  char v21; // al
  int listCursor; // eax
  int result; // eax
  int totalArrayBytes; // [esp+4h] [ebp-18h]
  char prefixBuffer[16]; // [esp+Ch] [ebp-10h] BYREF

  construct_code_count = arrayCount;
  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 112);
  prevItem = 0;
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(g_ClipsMemoryTable + 112) = *freeNode;
    newItem = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    newItem = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  *newItem = itemName;
  newItem[2] = initFunction;
  newItem[1] = beforeFunction;
  newItem[3] = generateFunction;
  newItemPtr = (int)newItem;
  newItem[4] = priority;
  if ( construct_code_count )
  {
    if ( construct_code_count + g_Rules_CodeGeneratorItemIndex > 44 )
    {
      Rules_ReportSystemError((int)aConscomp, 2);
      IO_RunRouterExitCallbacks();
    }
    arrayBytes = 4 * construct_code_count;
    *(_DWORD *)(newItemPtr + 20) = Mem_SmallBlockAlloc(4 * construct_code_count);
    if ( construct_code_count > 0 )
    {
      totalArrayBytes = arrayBytes;
      slot_offset = 0;
      do
      {
        if ( g_Rules_CodeGeneratorItemIndex >= 18 )
          sprintf_(prefixBuffer, "%c_", (unsigned __int8)g_Rules_CodeGeneratorItemPrefixTable[g_Rules_CodeGeneratorItemIndex]);
        else
          sprintf_(prefixBuffer, "%c", (unsigned __int8)g_Rules_CodeGeneratorItemLetterTable[g_Rules_CodeGeneratorItemIndex]);
        ++g_Rules_CodeGeneratorItemIndex;
        nameCopy = Mem_SmallBlockAlloc(strlen(prefixBuffer) + 1);
        *(_DWORD *)(*(_DWORD *)(newItemPtr + 20) + slot_offset) = nameCopy;
        copySrc = prefixBuffer;
        copyDst = (char *)nameCopy;
        nextOffset = slot_offset + 4;
        do
        {
          v20 = *copySrc;
          *copyDst = *copySrc;
          if ( !v20 )
            break;
          v21 = copySrc[1];
          copySrc += 2;
          copyDst[1] = v21;
          copyDst += 2;
        }
        while ( v21 );
        slot_offset = nextOffset;
      }
      while ( nextOffset < totalArrayBytes );
    }
  }
  else
  {
    newItem[5] = 0;
  }
  if ( g_CodeGeneratorItemList )
  {
    listCursor = g_CodeGeneratorItemList;
    do
    {
      if ( priority >= *(_DWORD *)(listCursor + 16) )
        break;
      prevItem = listCursor;
      listCursor = *(_DWORD *)(listCursor + 24);
    }
    while ( listCursor );
    if ( prevItem )
    {
      *(_DWORD *)(newItemPtr + 24) = listCursor;
      *(_DWORD *)(prevItem + 24) = newItemPtr;
    }
    else
    {
      *(_DWORD *)(newItemPtr + 24) = g_CodeGeneratorItemList;
      g_CodeGeneratorItemList = newItemPtr;
    }
    return newItemPtr;
  }
  else
  {
    *(_DWORD *)(newItemPtr + 24) = 0;
    result = newItemPtr;
    g_CodeGeneratorItemList = newItemPtr;
  }
  return result;
}
// 4A77B4: variable 'v8' is possibly undefined
// 4A77F2: variable 'v14' is possibly undefined
// 4A7850: variable 'v16' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACF4: using guessed type int dword_51ACF4;
// 51ACF8: using guessed type int dword_51ACF8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A7920) --------------------------------------------------------
int  Rules_ConstructCodeFileClose(int result, int *theCount, int maxIndices, _DWORD *arrayVersion, _DWORD *canBeReopened, int codeFile)
{
  int curFile; // esi
  int v8; // edx
  int codeFileInfo; // ecx
  int v10; // ecx
  char v11; // [esp+0h] [ebp-Ch]

  curFile = result;
  v8 = maxIndices;
  codeFileInfo = codeFile;
  if ( v8 > *theCount )
  {
    if ( !canBeReopened )
      return result;
    *canBeReopened = 1;
    fclose_(codeFile);
    return 0;
  }
  if ( canBeReopened )
    *canBeReopened = 0;
  if ( !result )
  {
    if ( !canBeReopened || !codeFile )
    {
      Rules_ReportSystemError(codeFile, 3);
      IO_RunRouterExitCallbacks();
    }
    if ( !*(_DWORD *)codeFileInfo )
      return 0;
    curFile = Rules_OpenConstructCodeFile(*(const char **)codeFileInfo, *(_DWORD *)(codeFileInfo + 4), *(_DWORD *)(codeFileInfo + 8), (DWORD)arrayVersion);
    if ( !curFile )
    {
      Rules_ReportSystemError(codeFileInfo, 4);
      IO_RunRouterExitCallbacks();
    }
  }
  Output_WriteFormatted(codeFileInfo, v8, curFile, (int)asc_507DA0, v11);
  fclose_(v10);
  *theCount = 0;
  result = 0;
  ++*arrayVersion;
  return result;
}
// 4A7983: variable 'v9' is possibly undefined
// 4A79C0: variable 'v8' is possibly undefined
// 4A79C0: variable 'v11' is possibly undefined
// 4A79CA: variable 'v10' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004A79F0) --------------------------------------------------------
int  Rules_ConstructCodeFileOpen(
        int theFile,
        const char *fileName,
        int imageID,
        const char *fileID,
        int *fileCount,
        int arrayVersion,
        int headerFP,
        char structureName,
        const char *structPrefix,
        int reopenOldFile,
        const char **codeFile)
{
  const char **v13; // ecx
  const char *curFileName; // edi
  int curFileID; // edx
  int curVersion; // eax
  int result; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // edx
  int v24; // [esp-8h] [ebp-68h]
  char arrayNameBuffer[80]; // [esp+0h] [ebp-60h] BYREF
  int v26; // [esp+50h] [ebp-10h]

  v26 = imageID;
  v13 = codeFile;
  if ( reopenOldFile )
  {
    if ( !codeFile )
    {
      Rules_ReportSystemError(0, 5);
      IO_RunRouterExitCallbacks();
    }
    curFileName = *v13;
    curFileID = (int)v13[1];
    curVersion = (int)v13[2];
  }
  else
  {
    curFileName = fileName;
    curFileID = (int)fileID;
    curVersion = *fileCount;
    if ( codeFile )
    {
      codeFile[2] = (const char *)curVersion;
      *codeFile = fileName;
      codeFile[1] = fileID;
    }
  }
  if ( theFile )
  {
    Output_WriteFormatted((int)v13, curFileID, theFile, (int)asc_508250, arrayNameBuffer[0]);
    return theFile;
  }
  else
  {
    result = Rules_OpenConstructCodeFile(curFileName, curFileID, curVersion, (DWORD)fileName);
    if ( result )
    {
      if ( reopenOldFile )
      {
        Output_WriteFormatted(result, result, result, (int)asc_508250, arrayNameBuffer[0]);
        return v23;
      }
      else
      {
        v24 = v26;
        ++*fileCount;
        sprintf_(arrayNameBuffer, "%s%d_%d", structPrefix, v24, arrayVersion);
        Output_WriteFormatted(v19, v18, v19, (int)aSS_0, structureName);
        Output_WriteFormatted(v21, v20, headerFP, (int)aExternSS, structureName);
        return v22;
      }
    }
  }
  return result;
}
// 4A7A2A: variable 'v13' is possibly undefined
// 4A7A8F: variable 'v19' is possibly undefined
// 4A7A8F: variable 'v18' is possibly undefined
// 4A7AA5: variable 'v21' is possibly undefined
// 4A7AA5: variable 'v20' is possibly undefined
// 4A7AAD: variable 'v22' is possibly undefined
// 4A7AFE: variable 'v23' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004A7B10) --------------------------------------------------------
signed int Rules_RegisterModuleItemIdAssigner()
{
  return Rules_DoForAllConstructs((void (*)(void))Rules_AssignNextModuleItemId, 0);
}

//----- (004A7B40) --------------------------------------------------------
int  Rules_AssignNextModuleItemId(int theConstruct, _DWORD *countBuffer)
{
  int result; // eax

  result = (*countBuffer)++;
  *(_DWORD *)(theConstruct + 12) = result;
  return result;
}

//----- (004A7B60) --------------------------------------------------------
int  Rules_WriteConstructHeaderToCode(int theFile, int theConstruct, signed int maxIndices, int a4, int imageID, char constructPrefix)
{
  int *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int nextConstruct; // ecx
  char v18; // [esp+0h] [ebp-Ch]
  char v19; // [esp+0h] [ebp-Ch]
  char v20; // [esp+0h] [ebp-Ch]
  char v21; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a4, theConstruct, theFile, (int)asc_507F14, v18);
  Compiler_WriteSymbolReference(theFile, *v9, v10);
  Output_WriteFormatted(v11, v11, theFile, (int)aNull_17, v19);
  Output_WriteFormatted(v12, imageID, theFile, (int)aMihsSD_DD_2, imageID);
  Output_WriteFormatted(v14, v13, theFile, (int)a0_1, v20);
  nextConstruct = *(_DWORD *)(theConstruct + 16);
  if ( nextConstruct )
    return Output_WriteFormatted(nextConstruct, *(_DWORD *)(nextConstruct + 12) % maxIndices, theFile, (int)aChsSD_LdLd, constructPrefix);
  else
    return Output_WriteFormatted(0, v15, theFile, (int)aNull_2, v21);
}
// 4A7B75: variable 'v18' is possibly undefined
// 4A7B7F: variable 'v9' is possibly undefined
// 4A7B81: variable 'v10' is possibly undefined
// 4A7B8E: variable 'v11' is possibly undefined
// 4A7B8E: variable 'v19' is possibly undefined
// 4A7BB5: variable 'v12' is possibly undefined
// 4A7BC3: variable 'v14' is possibly undefined
// 4A7BC3: variable 'v13' is possibly undefined
// 4A7BC3: variable 'v20' is possibly undefined
// 4A7BD8: variable 'v15' is possibly undefined
// 4A7BD8: variable 'v21' is possibly undefined

//----- (004A7C20) --------------------------------------------------------
int  Rules_WriteConstructModuleItemHeaderToCode(int theFile, int theModule, int a3, int a4, char constructPrefix)
{
  int v7; // edx
  int theModuleItem; // ebx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int firstItem; // edx
  int v13; // edx
  int v14; // ecx
  int lastItem; // edi
  int v16; // edx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  int v20; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a4, theFile, (int)asc_507F14, v19);
  theModuleItem = Module_GetItem(theModule, v7);
  Compiler_WriteModuleReference(theFile, theModule);
  Output_WriteFormatted(v10, v9, theFile, (int)asc_508278, theModuleItem);
  firstItem = *(_DWORD *)(theModuleItem + 4);
  if ( firstItem )
    Output_WriteFormatted(v11, *(_DWORD *)(firstItem + 12) % v11, theFile, (int)aChsSD_LdLd_0, constructPrefix);
  else
    Output_WriteFormatted(v11, 0, theFile, (int)aNull_0, v20);
  lastItem = *(_DWORD *)(v20 + 8);
  if ( lastItem )
    Output_WriteFormatted(v14, *(_DWORD *)(lastItem + 12) % v14, theFile, (int)aChsSD_LdLd_1, constructPrefix);
  else
    Output_WriteFormatted(v14, v13, theFile, (int)aNull_1, v20);
  return Output_WriteFormatted(v17, v16, theFile, (int)asc_508384, v20);
}
// 4A7C36: variable 'v19' is possibly undefined
// 4A7C40: variable 'v7' is possibly undefined
// 4A7C59: variable 'v10' is possibly undefined
// 4A7C59: variable 'v9' is possibly undefined
// 4A7C8D: variable 'v11' is possibly undefined
// 4A7C98: variable 'v20' is possibly undefined
// 4A7CA5: variable 'v14' is possibly undefined
// 4A7CA5: variable 'v13' is possibly undefined
// 4A7CB3: variable 'v17' is possibly undefined
// 4A7CB3: variable 'v16' is possibly undefined

//----- (004A7DA3) --------------------------------------------------------
int  IO_RenameFile(const CHAR *oldFileName, const CHAR *newFileName, int a3)
{
  if ( MoveFileA(oldFileName, newFileName) )
    return 0;
  else
    return _set_errno_nt_(a3);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (004A7DC0) --------------------------------------------------------
signed int  Rules_PrintArgumentValueList(int logicalName, _DWORD *theSegment)
{
  int v2; // ecx
  __int16 fieldIndex; // bx
  signed int result; // eax
  int fieldValue; // edi

  v2 = logicalName;
  fieldIndex = 0;
  while ( 1 )
  {
    result = *theSegment << 17 >> 23;
    if ( fieldIndex >= result )
      break;
    fieldValue = *(_DWORD *)theSegment[fieldIndex + 2];
    if ( fieldValue )
      (*(void (**)(void))(*(_DWORD *)fieldValue + 4))();
    if ( ++fieldIndex < *theSegment << 17 >> 23 )
      Output_Write(v2, (int)asc_5083B0, v2);
  }
  return result;
}
// 4A7E05: variable 'v2' is possibly undefined

//----- (004A7E20) --------------------------------------------------------
_DWORD * Rules_MultifieldCopyWithMarkers(int *srcSegment, int a2, int a3)
{
  int totalFields; // eax
  signed int newSegmentPtr; // eax
  char v6; // dl
  __int16 v7; // cx
  int v8; // edx
  _DWORD *newSegment; // ebx
  __int16 i; // ax
  int v11; // ecx
  _DWORD *fieldPtr; // esi

  totalFields = a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23);
  if ( (unsigned int)(4 * totalFields + 8) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 16 * totalFields + 32) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(16 * (a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23)) + g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 16 * (a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23)) + 32) = *(_DWORD *)g_ClipsMemFreeListTemp;
    newSegmentPtr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSegmentPtr = Mem_HeapAllocWithRetry((_DWORD *)(4 * (a3 + a2 + ((unsigned int)(*srcSegment << 17) >> 23)) + 8));
  }
  v6 = *(_BYTE *)newSegmentPtr | 1;
  *(_BYTE *)newSegmentPtr = v6;
  *(_BYTE *)newSegmentPtr = v6 & 0xF9;
  *(_DWORD *)newSegmentPtr |= 4 * (a2 & 1);
  *(_BYTE *)newSegmentPtr &= ~8u;
  *(_DWORD *)newSegmentPtr |= 8 * (a3 & 1);
  *(_BYTE *)newSegmentPtr &= 0xCFu;
  v7 = *(_WORD *)newSegmentPtr;
  *(_DWORD *)(newSegmentPtr + 4) = 0;
  v8 = *srcSegment;
  *(_WORD *)newSegmentPtr = v7 & 0x803F;
  newSegment = (_DWORD *)newSegmentPtr;
  *(_DWORD *)newSegmentPtr |= v8 & 0x7FC0;
  for ( i = 0; ; ++i )
  {
    v11 = i;
    fieldPtr = &newSegment[v11];
    if ( i >= *newSegment << 17 >> 23 )
      break;
    fieldPtr[2] = srcSegment[v11 + 2];
  }
  if ( a2 )
  {
    ++i;
    fieldPtr[2] = 0;
  }
  if ( a3 )
    newSegment[i + 2] = 0;
  return newSegment;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A7F90) --------------------------------------------------------
_WORD * Rules_MergeMultifieldValues(_DWORD *firstSegment, _DWORD *secondSegment, int a3, int a4)
{
  int totalFields; // eax
  signed int newSegmentPtr; // eax
  char v8; // bl
  char v9; // bh
  int v10; // ecx
  _WORD *newSegment; // edx
  __int16 i; // ax
  int srcOffset; // ebx
  int writeIndex; // eax
  int j; // ebx
  _WORD *writePtr; // esi
  int fieldValue; // ecx

  totalFields = a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23);
  if ( (unsigned int)(4 * totalFields + 8) < 0x1F4 && *(_DWORD *)(16 * totalFields + g_ClipsMemoryTable + 32) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(16 * (a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23)) + g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 16 * (a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23)) + 32) = *(_DWORD *)g_ClipsMemFreeListTemp;
    newSegmentPtr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSegmentPtr = Mem_HeapAllocWithRetry((_DWORD *)(4 * (a3 + a4 + (*firstSegment << 17 >> 23) + (*secondSegment << 17 >> 23)) + 8));
  }
  v8 = *(_BYTE *)newSegmentPtr | 1;
  *(_BYTE *)newSegmentPtr = v8;
  *(_BYTE *)newSegmentPtr = v8 & 0xF9;
  *(_DWORD *)newSegmentPtr |= 4 * (a4 & 1);
  *(_BYTE *)newSegmentPtr &= ~8u;
  *(_DWORD *)newSegmentPtr |= 8 * (a3 & 1);
  v9 = *(_BYTE *)newSegmentPtr;
  *(_DWORD *)(newSegmentPtr + 4) = 0;
  *(_BYTE *)newSegmentPtr = v9 & 0xCF;
  v10 = (((unsigned __int16)(2 * *(_WORD *)firstSegment) >> 7) + ((unsigned __int16)(2 * *(_WORD *)secondSegment) >> 7)) & 0x1FF;
  *(_WORD *)newSegmentPtr &= 0x803Fu;
  newSegment = (_WORD *)newSegmentPtr;
  *(_DWORD *)newSegmentPtr |= v10 << 6;
  for ( i = 0; i < *firstSegment << 17 >> 23; ++i )
  {
    srcOffset = 4 * i;
    *(_DWORD *)&newSegment[srcOffset / 2u + 4] = firstSegment[srcOffset / 4u + 2];
  }
  writeIndex = *firstSegment << 17 >> 23;
  for ( j = 0; ; ++j )
  {
    writePtr = &newSegment[2 * (__int16)writeIndex];
    if ( (__int16)writeIndex >= (unsigned __int16)(2 * *newSegment) >> 7 )
      break;
    LOWORD(writeIndex) = writeIndex + 1;
    fieldValue = secondSegment[(__int16)j + 2];
    *((_DWORD *)writePtr + 2) = fieldValue;
  }
  if ( a4 )
  {
    LOWORD(writeIndex) = writeIndex + 1;
    *((_DWORD *)writePtr + 2) = 0;
  }
  if ( a3 )
    *(_DWORD *)&newSegment[2 * (__int16)writeIndex + 4] = 0;
  return newSegment;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8170) --------------------------------------------------------
int  Rules_ResetDataObjectValue(int theDataObject)
{
  char incrementalResetFlag; // al
  int v2; // edx
  int result; // eax

  *(_DWORD *)(theDataObject + 8) = 0;
  *(_DWORD *)theDataObject = 0;
  *(_DWORD *)(theDataObject + 4) = 0;
  *(_BYTE *)(theDataObject + 12) &= 0xF8u;
  incrementalResetFlag = Rules_GetIncrementalReset();
  *(_BYTE *)(v2 + 12) &= ~8u;
  result = 8 * (incrementalResetFlag & 1);
  *(_DWORD *)(v2 + 12) |= result;
  *(_BYTE *)(v2 + 12) &= 0x8Fu;
  return result;
}
// 4A8196: variable 'v2' is possibly undefined

//----- (004A81C0) --------------------------------------------------------
signed int  Rules_AppendExpressionValueNode(int theValue, _DWORD *theExpression, signed int *theList)
{
  _DWORD *freeNode; // edx
  signed int v6; // eax
  char v7; // cl
  signed int newNode; // edx
  _DWORD *freeEntry; // ecx
  _DWORD *v10; // ecx
  _DWORD *valueEntry; // ebp
  _DWORD *exprCopy; // eax
  int v13; // ecx
  signed int listTail; // esi

  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeNode;
    v6 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v6 = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *(_WORD *)v6 &= 0x8000u;
  v7 = *(_BYTE *)v6;
  *(_DWORD *)(v6 + 4) = 0;
  *(_BYTE *)v6 = v7 | 0x40;
  newNode = v6;
  freeEntry = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( freeEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeEntry;
    v10 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v10 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  v10[2] = 0;
  valueEntry = v10;
  *v10 = theValue;
  if ( theExpression )
  {
    exprCopy = Rules_CopyExpressionChain(theExpression);
    *(_DWORD *)(v13 + 4) = exprCopy;
  }
  else
  {
    v10[1] = 0;
  }
  *(_DWORD *)(newNode + 8) = valueEntry;
  listTail = theList[1];
  if ( listTail )
    *(_DWORD *)(listTail + 4) = newNode;
  else
    *theList = newNode;
  theList[1] = newNode;
  return newNode;
}
// 4A8231: variable 'v13' is possibly undefined
// 4A8234: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8280) --------------------------------------------------------
signed int  Rules_MultifieldAppendValue(_DWORD *theSegment, int newValue, int a3, int a4)
{
  int totalFields; // eax
  signed int newSegmentPtr; // eax
  char v7; // dl
  char v8; // bh
  __int16 newLength; // dx
  signed int newSegment; // ebp
  __int16 i; // ax
  int v12; // ecx
  int fieldPtr; // ebx
  __int16 writeIndex; // ax
  int v15; // edx

  totalFields = a3 + a4 + (*theSegment << 17 >> 23);
  if ( (unsigned int)(4 * totalFields + 12) < 0x1F4 && *(_DWORD *)(16 * totalFields + g_ClipsMemoryTable + 48) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(16 * (a3 + a4 + (*theSegment << 17 >> 23)) + g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 16 * (a3 + a4 + (*theSegment << 17 >> 23)) + 48) = *(_DWORD *)g_ClipsMemFreeListTemp;
    newSegmentPtr = g_ClipsMemFreeListTemp;
  }
  else
  {
    newSegmentPtr = Mem_HeapAllocWithRetry((_DWORD *)(4 * (a3 + a4 + (*theSegment << 17 >> 23)) + 12));
  }
  v7 = *(_BYTE *)newSegmentPtr | 1;
  *(_BYTE *)newSegmentPtr = v7;
  *(_BYTE *)newSegmentPtr = v7 & 0xF9;
  *(_DWORD *)newSegmentPtr |= 4 * (a4 & 1);
  *(_BYTE *)newSegmentPtr &= ~8u;
  *(_DWORD *)newSegmentPtr |= 8 * (a3 & 1);
  v8 = *(_BYTE *)newSegmentPtr;
  *(_DWORD *)(newSegmentPtr + 4) = 0;
  *(_BYTE *)newSegmentPtr = v8 & 0xCF;
  newLength = ((unsigned __int16)(2 * *(_WORD *)theSegment) >> 7) + 1;
  *(_WORD *)newSegmentPtr &= 0x803Fu;
  newSegment = newSegmentPtr;
  *(_DWORD *)newSegmentPtr |= (newLength & 0x1FF) << 6;
  for ( i = 0; ; ++i )
  {
    v12 = i;
    fieldPtr = v12 * 4 + newSegment;
    if ( i >= *theSegment << 17 >> 23 )
      break;
    *(_DWORD *)(fieldPtr + 8) = theSegment[v12 + 2];
  }
  *(_DWORD *)(fieldPtr + 8) = newValue;
  writeIndex = i + 1;
  if ( a4 )
  {
    v15 = writeIndex++;
    *(_DWORD *)(newSegment + 4 * v15 + 8) = 0;
  }
  if ( a3 )
    *(_DWORD *)(newSegment + 4 * writeIndex + 8) = 0;
  return newSegment;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8410) --------------------------------------------------------
_DWORD * Rules_CopyExpressionChain(_DWORD *theExpression)
{
  _DWORD *srcNode; // edx
  _DWORD *copyHead; // edi
  _DWORD *i; // ecx
  _DWORD *freeNode; // ebx
  _DWORD *newNode; // eax

  srcNode = theExpression;
  copyHead = 0;
  for ( i = 0; srcNode; i = newNode )
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 80);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
      *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeNode;
      newNode = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newNode = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    newNode[4] = 0;
    *newNode = *srcNode;
    newNode[1] = srcNode[1];
    newNode[2] = srcNode[2];
    newNode[3] = srcNode[3];
    if ( i )
      i[4] = newNode;
    else
      copyHead = newNode;
    srcNode = (_DWORD *)srcNode[4];
  }
  return copyHead;
}
// 4A845C: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8520) --------------------------------------------------------
int  Rules_ReleaseJoinNetworkNodeChain(int result)
{
  int nextMatch; // edx
  int v2; // edx

  if ( result )
  {
    do
    {
      while ( 1 )
      {
        nextMatch = *(_DWORD *)(result + 4);
        if ( ((*(_BYTE *)result & 0x10) == 0 || (*(_BYTE *)result & 0x20) != 0) && (*(_BYTE *)result & 1) != 0 )
          break;
        *(_DWORD *)(result + 4) = g_PartialMatchFreeListHead;
        g_PartialMatchFreeListHead = result;
        result = nextMatch;
        if ( !nextMatch )
          return result;
      }
      Rules_FreePartialMatch(result);
      result = v2;
    }
    while ( v2 );
  }
  return result;
}
// 4A8558: variable 'v2' is possibly undefined
// 51A974: using guessed type int dword_51A974;

//----- (004A8570) --------------------------------------------------------
int  Rules_CountJoinNetworkEntryNodes(int theJoin)
{
  int count; // edx

  count = 0;
  if ( !theJoin )
    return count;
  do
  {
    while ( (*(_BYTE *)theJoin & 4) != 0 )
    {
      theJoin = *(_DWORD *)(theJoin + 16);
      if ( !theJoin )
        return count;
    }
    ++count;
    theJoin = *(_DWORD *)(theJoin + 24);
  }
  while ( theJoin );
  return count;
}

//----- (004A85A0) --------------------------------------------------------
signed int Rules_PrintJoinNetworkSharingReport()
{
  int v0; // edx
  signed int v1; // ecx

  Rules_ClearJoinNetworkMarkedFlags();
  return Rules_PrintJoinNetworkNodeRuleOwners(v1, v0);
}
// 4A85AC: variable 'v1' is possibly undefined
// 4A85AC: variable 'v0' is possibly undefined

//----- (004A85C0) --------------------------------------------------------
signed int  Rules_PrintJoinNetworkNodeRuleOwners(signed int result, int a2)
{
  uintptr_t node; // ecx
  int rule_name; // esi

  node = (uintptr_t)(unsigned int)result;
  while ( node )
  {
    while ( node && (*(_BYTE *)node & 0x20) != 0 )
      node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 28);
    if ( !node )
      return result;
    if ( *(_DWORD *)(node + 36) )
    {
      *(_BYTE *)node |= 0x20u;
      rule_name = Rules_GetConstructNameString(*(_DWORD *)(node + 36));
      Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], rule_name, 0);
      result = Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_5083B4, 0);
      node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 28);
    }
    else
    {
      *(_BYTE *)node |= 0x20u;
      result = Rules_PrintJoinNetworkNodeRuleOwners(*(_DWORD *)(node + 20), a2);
      node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 28);
    }
  }
  return result;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004A8650) --------------------------------------------------------
int Rules_ClearJoinNetworkMarkedFlags()
{
  int i; // esi
  int theDefrule; // ebx
  uintptr_t node; // eax
  unsigned int flags; // edx
  int next_rule; // edx

  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    theDefrule = Rules_GetNextDefrule(0);
    while ( theDefrule )
    {
      node = (uintptr_t)(unsigned int)*(_DWORD *)(theDefrule + 44);
      while ( node )
      {
        flags = *(_DWORD *)node & 0xFFFFFFDF;
        *(_DWORD *)node = flags;
        node = (uintptr_t)(unsigned int)*(_DWORD *)(node + ((*(_BYTE *)node & 4) != 0 ? 16 : 24));
      }
      next_rule = *(_DWORD *)(theDefrule + 48);
      if ( next_rule )
        theDefrule = next_rule;
      else
        theDefrule = Rules_GetNextDefrule(theDefrule);
    }
  }
  return Module_EndEnum();
}

//----- (004A86F0) --------------------------------------------------------
int  Rules_JoinNetworkAssignCodeGenIds(_DWORD *moduleCount, int *ruleCount, int *joinCount)
{
  int result; // eax
  int i; // edi
  _DWORD *theDefrule; // ecx
  int v8; // eax
  int joinPtr; // eax
  int v10; // edx
  int nextJoin; // edx

  *moduleCount = 0;
  *ruleCount = 0;
  *joinCount = 0;
  Rules_ClearJoinNetworkMarkedFlags();
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ++*moduleCount;
    Module_SetCurrent(i);
    theDefrule = (_DWORD *)Rules_GetNextDefrule(0);
    while ( theDefrule )
    {
      v8 = *ruleCount;
      theDefrule[3] = *ruleCount;
      *ruleCount = v8 + 1;
      joinPtr = theDefrule[11];
      if ( joinPtr )
      {
        do
        {
          if ( (*(_BYTE *)joinPtr & 0x20) == 0 )
          {
            *(_BYTE *)joinPtr |= 0x20u;
            v10 = *joinCount;
            *(_DWORD *)(joinPtr + 4) = *joinCount;
            *joinCount = v10 + 1;
          }
          if ( (*(_BYTE *)joinPtr & 4) != 0 )
            nextJoin = *(_DWORD *)(joinPtr + 16);
          else
            nextJoin = *(_DWORD *)(joinPtr + 24);
          joinPtr = nextJoin;
        }
        while ( nextJoin );
      }
      if ( theDefrule[12] )
        theDefrule = (_DWORD *)theDefrule[12];
      else
        theDefrule = (_DWORD *)Rules_GetNextDefrule((int)theDefrule);
    }
    result = Module_NextEnum(i);
  }
  return result;
}

//----- (004A87A0) --------------------------------------------------------
int Rules_DefruleCommandDefinitions()
{
  Rules_AddResetFunction((int)aDefrule_0, (int)Rules_ResetDefrules, 70);
  Rules_AddSaveFunction((int)aDefrule_0, (int)Rules_SaveDefrules, 0);
  Rules_AddClearReadyFunction((int)aDefrule_0, (int)Rules_ClearDefrulesReady, 0);
  Rules_AddClearFunction((int)aDefrule_0, (int)Rules_ClearDefrules, 0);
  Rules_AddWatchItem((int)aRules, 0, 70, (int)&g_WatchRulesFlag, (int)Rules_DefruleWatchAccess, (int)Rules_DefruleWatchPrint);
  Rules_RegisterHostFunction(aGetDefruleList, 109, (int)aGetdefrulelist, (int)Rules_GetDefruleListFunction, (int)a01w_4);
  Rules_RegisterHostFunction(aUndefrule, 118, (int)aUndefrulecomma, (int)Rules_UndefruleCommand, (int)a11w_7);
  Rules_RegisterHostFunction(aDefruleModule, 119, (int)aDefrulemodulef, (int)Rules_DefruleModuleFunction, (int)a11w_7);
  Rules_RegisterHostFunction(aRules, 118, (int)aListdefrulesco, (int)Rules_ListDefrulesCommand, (int)a01w_4);
  Rules_RegisterHostFunction(aListDefrules, 118, (int)aListdefrulesco, (int)Rules_ListDefrulesCommand, (int)a01w_4);
  Rules_RegisterHostFunction(aPpdefrule, 118, (int)aPpdefrulecomma, (int)Rules_PPDefruleCommand, (int)a11w_7);
  Rules_RegisterDefruleBinaryItem();
  return Rules_SetupDefruleCodeGenerator();
}
// 4A88D0: using guessed type int sub_4A88D0();
// 4A8920: using guessed type int sub_4A8920();
// 51AD08: using guessed type int dword_51AD08;

//----- (004A88D0) --------------------------------------------------------
int Rules_ResetDefrules()
{
  int *mainModule; // eax

  g_Rules_EntityTimeTagCounter = 0;
  Rules_ClearFocusStack();
  mainModule = Module_FindByName(aMain_4);
  return Rules_PushFocus((int)mainModule);
}
// 4A88D0: using guessed type int sub_4A88D0();
// 51A998: using guessed type int dword_51A998;

//----- (004A88F0) --------------------------------------------------------
int Rules_ClearDefrulesReady()
{
  int result; // eax
  int v1; // edx

  if ( g_Rules_CurrentlyExecutingRule )
    return 0;
  Rules_ClearFocusStack();
  result = Module_GetCurrent();
  if ( result )
  {
    result = 1;
    g_Rules_EntityTimeTagCounter = v1;
  }
  return result;
}
// 4A8912: variable 'v1' is possibly undefined
// 51A1F0: using guessed type int dword_51A1F0;
// 51A998: using guessed type int dword_51A998;

//----- (004A8920) --------------------------------------------------------
int Rules_ClearDefrules()
{
  int *mainModule; // eax

  mainModule = Module_FindByName(aMain_4);
  return Rules_PushFocus((int)mainModule);
}
// 4A8920: using guessed type int sub_4A8920();

//----- (004A8930) --------------------------------------------------------
int  Rules_SaveDefrules(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8940) --------------------------------------------------------
int __thiscall Rules_UndefruleCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8960) --------------------------------------------------------
int  Rules_DeleteDefruleOrAll(int theDefrule, int a2)
{
  return Rules_DeleteConstructOrAll(theDefrule, g_DefruleConstructTypePtr, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8970) --------------------------------------------------------
_DWORD * Rules_GetDefruleListFunction(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_DefruleConstructTypePtr, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A89B0) --------------------------------------------------------
int __thiscall Rules_DefruleModuleFunction(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A89D0) --------------------------------------------------------
int __thiscall Rules_PPDefruleCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8A00) --------------------------------------------------------
int  Rules_ListDefrulesCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_DefruleConstructTypePtr, a1, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8A40) --------------------------------------------------------
int  Rules_TestInheritedFlagBit4(int theDefrule)
{
  if ( !theDefrule )
    return 0;
  while ( (*(_BYTE *)(theDefrule + 29) & 0x10) == 0 )
  {
    theDefrule = *(_DWORD *)(theDefrule + 48);
    if ( !theDefrule )
      return 0;
  }
  return 1;
}

//----- (004A8A60) --------------------------------------------------------
int  Rules_TestInheritedFlagBit5(int theDefrule)
{
  if ( !theDefrule )
    return 0;
  while ( (*(_BYTE *)(theDefrule + 29) & 0x20) == 0 )
  {
    theDefrule = *(_DWORD *)(theDefrule + 48);
    if ( !theDefrule )
      return 0;
  }
  return 1;
}

//----- (004A8A80) --------------------------------------------------------
int  Rules_SetInheritedFlagBit4(char newState, int theDefrule)
{
  int result; // eax

  for ( result = theDefrule; result; result = *(_DWORD *)(result + 48) )
  {
    *(_BYTE *)(result + 29) &= ~0x10u;
    *(_DWORD *)(result + 28) |= (newState & 1) << 12;
  }
  return result;
}

//----- (004A8AB0) --------------------------------------------------------
int  Rules_SetInheritedFlagBit5(char newState, int theDefrule)
{
  int result; // eax

  for ( result = theDefrule; result; result = *(_DWORD *)(result + 48) )
  {
    *(_BYTE *)(result + 29) &= ~0x20u;
    *(_DWORD *)(result + 28) |= (newState & 1) << 13;
  }
  return result;
}

//----- (004A8AE0) --------------------------------------------------------
signed int  Rules_DefruleWatchAccess(int code, int newState, int argExprs, double a4)
{
  if ( code )
    return Rules_ApplyWatchFlagCommand(g_DefruleConstructTypePtr, newState, (int)Rules_TestInheritedFlagBit4, argExprs, a4, (void (*)(void))Rules_SetInheritedFlagBit4);
  else
    return Rules_ApplyWatchFlagCommand(g_DefruleConstructTypePtr, newState, (int)Rules_TestInheritedFlagBit5, argExprs, a4, (void (*)(void))Rules_SetInheritedFlagBit5);
}
// 4A8A40: using guessed type int sub_4A8A40();
// 4A8A60: using guessed type int sub_4A8A60();
// 54E648: using guessed type int dword_54E648;

//----- (004A8B20) --------------------------------------------------------
signed int  Rules_DefruleWatchPrint(int logicalName, int argExprs, double a3)
{
  return Rules_ListWatchFlagStatus(g_DefruleConstructTypePtr, logicalName, (int)Rules_TestInheritedFlagBit4, argExprs, a3, (void (*)(void))Rules_SetInheritedFlagBit4);
}
// 4A8A40: using guessed type int sub_4A8A40();
// 54E648: using guessed type int dword_54E648;

//----- (004A8B40) --------------------------------------------------------
int  Rules_AppendConstructToModuleList(int result)
{
  int theModuleItem; // edx
  int lastItem; // ecx

  theModuleItem = *(_DWORD *)(result + 8);
  lastItem = *(_DWORD *)(theModuleItem + 8);
  if ( lastItem )
    *(_DWORD *)(lastItem + 16) = result;
  else
    *(_DWORD *)(theModuleItem + 4) = result;
  *(_DWORD *)(*(_DWORD *)(result + 8) + 8) = result;
  *(_DWORD *)(result + 16) = 0;
  return result;
}

//----- (004A8B80) --------------------------------------------------------
int __fastcall Rules_TryDeleteConstruct(int theConstruct, int constructClass)
{
  int v4; // ecx

  if ( Rules_IsBloaded() == 1 )
    return 0;
  if ( (*(int (__cdecl **)(int))(constructClass + 12))(theConstruct) )
    return (*(int (**)(void))(constructClass + 40))();
  if ( strcmp_(v4, v4) )
    return 0;
  (*(void (**)(void))(constructClass + 40))();
  return 1;
}
// 4A8BA5: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A8BD0) --------------------------------------------------------
int  Rules_FindConstructByNameGeneric(_BYTE *constructName, int constructClass)
{
  _BYTE *local_name; // eax
  int *target_symbol; // ebx
  int get_name_func; // [ecx+10h]
  int next_func; // [ecx+1Ch]
  int current_item; // edx

  Module_BeginEnum();
  local_name = (_BYTE *)Rules_ExtractModuleAndConstructName(constructName);
  if ( local_name )
  {
    target_symbol = Rules_FindSymbolEntry(local_name);
    if ( target_symbol )
    {
      get_name_func = *(_DWORD *)(constructClass + 16);
      next_func = *(_DWORD *)(constructClass + 28);
      current_item = ((int (*)(int))(uintptr_t)(unsigned int)next_func)(0);
      while ( current_item )
      {
        if ( target_symbol == (int *)((int (*)(int))(uintptr_t)(unsigned int)get_name_func)(current_item) )
        {
          Module_EndEnum();
          return current_item;
        }
        current_item = ((int (*)(int))(uintptr_t)(unsigned int)next_func)(current_item);
      }
    }
  }
  Module_EndEnum();
  return 0;
}

//----- (004A8C30) --------------------------------------------------------
int __fastcall Rules_UndefconstructCommand(int a1, int constructClass)
{
  double v4; // st7
  int v5; // ecx
  int result; // eax
  int theConstruct; // esi
  int v8; // ecx
  int v9; // ecx
  _BYTE argNameBuffer[84]; // [esp+0h] [ebp-5Ch] BYREF
  int v11; // [esp+54h] [ebp-8h]

  v11 = a1;
  v4 = sprintf_(argNameBuffer, "%s name", (const char *)*(_DWORD *)constructClass);
  result = Rules_GetConstructNameArg((int)argNameBuffer, v5, v4);
  theConstruct = result;
  if ( result )
  {
    if ( (*(int (__thiscall **)(int))(constructClass + 12))(result) || !strcmp_(v8, v8) )
    {
      result = Rules_TryDeleteConstruct(v8, constructClass);
      if ( !result )
        return Rules_ReportCantDeleteItem(v9, theConstruct);
    }
    else
    {
      return Rules_ReportCantFindItem(v8, v8);
    }
  }
  return result;
}
// 4A8C53: variable 'v5' is possibly undefined
// 4A8C75: variable 'v8' is possibly undefined
// 4A8C8F: variable 'v9' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A8CB0) --------------------------------------------------------
int __fastcall Rules_PPConstructCommand(int a1, const char **constructClass)
{
  double v4; // st7
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  _BYTE argNameBuffer[84]; // [esp+0h] [ebp-5Ch] BYREF
  int v9; // [esp+54h] [ebp-8h]

  v9 = a1;
  v4 = sprintf_(argNameBuffer, "%s name", *constructClass);
  result = Rules_GetConstructNameArg((int)argNameBuffer, v5, v4);
  if ( result )
  {
    result = Rules_PrintConstructPPForm((int)g_IO_LogicalName_WDisplay, result, (int)constructClass);
    if ( !result )
      return Rules_ReportCantFindItem(v7, v7);
  }
  return result;
}
// 4A8CD3: variable 'v5' is possibly undefined
// 4A8CFA: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A624: using guessed type char *off_51A624;

//----- (004A8D10) --------------------------------------------------------
int  Rules_PrintConstructPPForm(int logicalName, int constructName, int constructType)
{
  int result; // eax
  char *ppForm; // eax
  signed int v5; // ecx

  result = (*(int (__thiscall **)(int, int))(constructType + 12))(logicalName, constructName);
  if ( result )
  {
    if ( (*(int (**)(void))(constructType + 20))() )
    {
      ppForm = (char *)(*(int (**)(void))(constructType + 20))();
      Output_WriteLongString(v5, ppForm);
    }
    return 1;
  }
  return result;
}
// 4A8D35: variable 'v5' is possibly undefined

//----- (004A8D50) --------------------------------------------------------
int __fastcall Rules_GetConstructModuleCommand(int a1, const char **constructClass)
{
  double v3; // st7
  int v4; // ecx
  _BYTE *constructName; // eax
  int *theModule; // eax
  int v8; // ecx
  _BYTE argNameBuffer[80]; // [esp+0h] [ebp-58h] BYREF
  int v10; // [esp+50h] [ebp-8h]

  v10 = a1;
  v3 = sprintf_(argNameBuffer, "%s name", *constructClass);
  constructName = (_BYTE *)Rules_GetConstructNameArg((int)argNameBuffer, v4, v3);
  if ( !constructName )
    return g_ClipsFalseSymbol;
  theModule = Rules_GetConstructModuleName(constructName, (int)constructName);
  if ( theModule )
    return *theModule;
  Rules_ReportCantFindItem(v8, v8);
  return g_ClipsFalseSymbol;
}
// 4A8D72: variable 'v4' is possibly undefined
// 4A8D9F: variable 'v8' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 54DD70: using guessed type int dword_54DD70;

//----- (004A8DB0) --------------------------------------------------------
int * Rules_GetConstructModuleName(_BYTE *constructName, int a2)
{
  signed int separatorPosition; // eax
  char **v4; // ecx
  signed int *moduleName; // eax
  int *result; // eax
  _DWORD countBuffer[3]; // [esp+0h] [ebp-Ch] BYREF

  countBuffer[1] = a2;
  separatorPosition = Rules_FindModuleSeparator(constructName);
  if ( separatorPosition )
  {
    moduleName = Rules_ExtractModuleName(separatorPosition);
    if ( moduleName )
      return Module_FindByName((_BYTE *)moduleName[4]);
  }
  result = (int *)Rules_FindImportExportConstruct(*v4, countBuffer, constructName, 1, 0);
  if ( result )
    return *(int **)result[2];
  return result;
}
// 4A8DCF: variable 'v4' is possibly undefined

//----- (004A8E00) --------------------------------------------------------
int  Rules_DeleteConstructOrAll(int theConstruct, int constructClass, int a3)
{
  int v4; // ecx
  int success; // esi
  int nextConstruct; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int result; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx

  if ( theConstruct )
  {
    result = (*(int (__cdecl **)(int))(constructClass + 36))(a3);
    if ( result )
    {
      Rules_UnlinkListNode(theConstruct);
      (*(void (**)(void))(v14 + 44))();
      if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
        Rules_RunPeriodicCleanup(1, 0);
      return 1;
    }
  }
  else
  {
    success = 1;
    if ( (*(int (**)(void))(constructClass + 28))() )
    {
      do
      {
        nextConstruct = ((__int64 (*)(void))*(_DWORD *)(v4 + 28))();
        if ( (*(int (**)(void))(v7 + 36))() )
        {
          Rules_UnlinkListNode(v8);
          (*(void (**)(void))(v10 + 44))();
        }
        else
        {
          v12 = (*(int (**)(void))(v9 + 16))();
          success = 0;
          Rules_ReportCantDeleteItem(v13, *(_DWORD *)(v12 + 16));
        }
      }
      while ( nextConstruct );
    }
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      Rules_RunPeriodicCleanup(1, 0);
    return success;
  }
  return result;
}
// 4A8E1F: variable 'v4' is possibly undefined
// 4A8E26: variable 'v7' is possibly undefined
// 4A8E2F: variable 'v8' is possibly undefined
// 4A8E36: variable 'v10' is possibly undefined
// 4A8E6E: variable 'v9' is possibly undefined
// 4A8E78: variable 'v13' is possibly undefined
// 4A8E8F: variable 'v14' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (004A8EC0) --------------------------------------------------------
int  Rules_SaveConstruct(signed int logicalName, int constructClass)
{
  int i; // edi
  char *ppForm; // eax
  int v6; // ecx

  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    while ( (*(int (**)(void))(constructClass + 28))() )
    {
      ppForm = (char *)(*(int (**)(void))(constructClass + 20))();
      if ( ppForm )
      {
        Output_WriteLongString(logicalName, ppForm);
        Output_Write(logicalName, (int)asc_50849C, v6);
      }
    }
  }
  return Module_EndEnum();
}
// 4A8F08: variable 'v6' is possibly undefined

//----- (004A8F40) --------------------------------------------------------
int  Rules_GetConstructNameString(int theConstruct)
{
  return *(_DWORD *)(*(_DWORD *)theConstruct + 16);
}

//----- (004A8F50) --------------------------------------------------------
int  Rules_GetConstructNameSymbol(int theConstruct)
{
  return *(_DWORD *)theConstruct;
}

//----- (004A8F60) --------------------------------------------------------
_DWORD * Rules_GetConstructListCommand(int returnValue, int constructClass, double a3)
{
  int numArgs; // eax
  int v4; // ecx
  int *theModule; // eax
  _DWORD *v6; // ecx
  int v8; // edx
  _DWORD argValue[2]; // [esp-4h] [ebp-24h] BYREF
  int v10; // [esp+4h] [ebp-1Ch]
  int v11; // [esp+1Ch] [ebp-4h]

  v11 = returnValue;
  numArgs = Lexer_TokenExpect(1);
  if ( numArgs == -1 )
    return Rules_SetMultifieldErrorValue(v4);
  if ( numArgs == 1 )
  {
    Rules_RtnUnknown(1, argValue, a3);
    if ( argValue[1] != 2
      || (theModule = Module_FindByName(*(_BYTE **)(v10 + 16))) == 0 && (theModule = (int *)strcmp_(v6, *(_DWORD *)(v10 + 16))) != 0 )
    {
      Rules_SetMultifieldErrorValue((int)v6);
      return (_DWORD *)Parser_ReportError(v8, (int)aDefmoduleNam_2);
    }
  }
  else
  {
    theModule = (int *)Module_GetCurrent();
  }
  return (_DWORD *)Rules_BuildConstructNameList(v6, constructClass, (int)theModule);
}
// 4A8F90: variable 'v6' is possibly undefined
// 4A8F9E: variable 'v4' is possibly undefined
// 4A8FEB: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A9000) --------------------------------------------------------
int  Rules_BuildConstructNameList(_DWORD *returnValue, int constructClass, int Enum)
{
  signed int constructCount; // ebx
  int i; // edx
  int v7; // edx
  int v8; // ecx
  _DWORD *theMultifield; // eax
  int fieldPosition; // ebx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int v14; // esi
  __int64 v15; // rax
  int v16; // ecx
  int v17; // edi
  int theConstruct; // ebp
  char *v19; // edi
  char *Name; // esi
  char v21; // al
  char v22; // al
  char *v23; // esi
  char *v24; // edi
  char v25; // al
  char v26; // al
  char *v27; // esi
  unsigned int nameLength; // kr08_4
  char *v29; // edi
  char v30; // al
  char v31; // al
  signed int *qualifiedSymbol; // eax
  int v33; // edx
  signed int *nameSymbol; // eax
  int v35; // edx
  char qualifiedName[512]; // [esp+0h] [ebp-224h] BYREF
  _DWORD *v38; // [esp+200h] [ebp-24h]
  int allModules; // [esp+204h] [ebp-20h]
  int moduleCursor; // [esp+208h] [ebp-1Ch]
  int v41; // [esp+20Ch] [ebp-18h]
  int v42; // [esp+210h] [ebp-14h]

  v42 = constructClass;
  constructCount = 0;
  Module_BeginEnum();
  allModules = 0;
  if ( !Enum )
  {
    Enum = Module_NextEnum(0);
    allModules = v8;
  }
  for ( i = Enum; i; i = Module_NextEnum(v7) )
  {
    Module_SetCurrent(i);
    while ( (*(int (**)(void))(v42 + 28))() )
      ++constructCount;
    if ( !allModules )
      break;
  }
  returnValue[1] = 4;
  moduleCursor = Enum;
  returnValue[4] = constructCount - 1;
  returnValue[3] = 0;
  theMultifield = Rules_CreateEphemeralMultifield(constructCount);
  fieldPosition = 1;
  v38 = theMultifield;
  for ( returnValue[2] = theMultifield; moduleCursor; moduleCursor = Module_NextEnum(moduleCursor) )
  {
    Module_SetCurrent(moduleCursor);
    v41 = 0;
    v13 = v11 + v12 - 6;
    while ( 1 )
    {
      v14 = v42;
      v41 = (*(int (__fastcall **)(int, int))(v42 + 28))(v11, v13);
      if ( !v41 )
        break;
      v15 = ((__int64 (*)(void))*(_DWORD *)(v14 + 16))();
      v17 = allModules;
      theConstruct = v15;
      *(_WORD *)(HIDWORD(v15) + 14) = 2;
      if ( v17 )
      {
        v19 = qualifiedName;
        Name = (char *)Module_GetName(moduleCursor);
        do
        {
          v21 = *Name;
          *v19 = *Name;
          if ( !v21 )
            break;
          v22 = Name[1];
          Name += 2;
          v19[1] = v22;
          v19 += 2;
        }
        while ( v22 );
        v23 = asc_5084B0;
        v24 = &qualifiedName[strlen(qualifiedName)];
        do
        {
          v25 = *v23;
          *v24 = *v23;
          if ( !v25 )
            break;
          v26 = v23[1];
          v23 += 2;
          v24[1] = v26;
          v24 += 2;
        }
        while ( v26 );
        v27 = *(char **)(theConstruct + 16);
        nameLength = strlen(qualifiedName) + 1;
        v29 = &qualifiedName[nameLength - 1];
        do
        {
          v30 = *v27;
          *v29 = *v27;
          if ( !v30 )
            break;
          v31 = v27[1];
          v27 += 2;
          v29[1] = v31;
          v29 += 2;
        }
        while ( v31 );
        qualifiedSymbol = Str_Intern(qualifiedName, ~nameLength);
        *(_DWORD *)(v33 + 16) = qualifiedSymbol;
        v13 = v33 + 6;
        ++fieldPosition;
      }
      else
      {
        nameSymbol = Str_Intern(*(char **)(v15 + 16), v16);
        *(_DWORD *)(v35 + 16) = nameSymbol;
        v13 = v35 + 6;
        ++fieldPosition;
      }
    }
    if ( !allModules )
      break;
  }
  return Module_EndEnum();
}
// 4A9055: variable 'v8' is possibly undefined
// 4A906A: variable 'v7' is possibly undefined
// 4A90D0: variable 'v11' is possibly undefined
// 4A90C6: variable 'v12' is possibly undefined
// 4A918D: variable 'v33' is possibly undefined
// 4A919C: variable 'v16' is possibly undefined
// 4A91A1: variable 'v35' is possibly undefined

//----- (004A91F0) --------------------------------------------------------
int  Rules_ListConstructsCommand(int constructClass, int a2, double a3)
{
  int result; // eax
  int *theModule; // eax
  int v6; // ecx
  _DWORD argValue[2]; // [esp-4h] [ebp-24h] BYREF
  int v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-8h]

  v9 = a2;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    if ( result == 1 )
    {
      Rules_RtnUnknown(1, argValue, a3);
      if ( argValue[1] != 2 )
        return Parser_ReportError(1, (int)aDefmoduleNam_2);
      theModule = Module_FindByName(*(_BYTE **)(v8 + 16));
      if ( !theModule )
      {
        theModule = (int *)strcmp_(v6, *(_DWORD *)(v8 + 16));
        if ( theModule )
          return Parser_ReportError(1, (int)aDefmoduleNam_2);
      }
    }
    else
    {
      theModule = (int *)Module_GetCurrent();
    }
    return Rules_PrintConstructNamesByModule(constructClass, (int)g_IO_LogicalName_WDisplay, (int)theModule);
  }
  return result;
}
// 4A9258: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A624: using guessed type char *off_51A624;

//----- (004A9280) --------------------------------------------------------
int  Rules_PrintConstructNamesByModule(int constructClass, int logicalName, int theModule)
{
  int constructCount; // ebp
  int result; // eax
  int v7; // ecx
  int theConstruct; // ebx
  int v9; // ecx
  int Name; // eax
  int v11; // ecx
  int v12; // ecx
  int Enum; // [esp+0h] [ebp-18h]
  int allModules; // [esp+4h] [ebp-14h]

  Enum = theModule;
  constructCount = 0;
  Module_BeginEnum();
  allModules = 0;
  if ( !theModule )
  {
    Enum = Module_NextEnum(0);
    allModules = 1;
  }
  while ( 1 )
  {
    if ( !Enum )
    {
LABEL_14:
      Rules_PrintTally((int)g_IO_LogicalName_WDisplay, constructCount, *(_DWORD *)(constructClass + 4), *(_DWORD *)constructClass);
      return Module_EndEnum();
    }
    if ( allModules )
    {
      Name = Module_GetName(Enum);
      Output_Write(logicalName, Name, v11);
      Output_Write(logicalName, (int)asc_5084B4, v12);
    }
    Module_SetCurrent(Enum);
    result = (*(int (**)(void))(constructClass + 28))();
    if ( result )
      break;
LABEL_13:
    if ( !allModules )
      goto LABEL_14;
    Enum = Module_NextEnum(Enum);
  }
  while ( g_ClipsHaltExecution != 1 )
  {
    theConstruct = (*(int (**)(void))(constructClass + 16))();
    if ( theConstruct )
    {
      if ( allModules )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5084B8, v7);
      Output_Write(logicalName, *(_DWORD *)(theConstruct + 16), v7);
      Output_Write(logicalName, (int)asc_50849C, v9);
    }
    ++constructCount;
    result = (*(int (**)(void))(constructClass + 28))();
    if ( !result )
      goto LABEL_13;
  }
  return result;
}
// 4A935C: variable 'v11' is possibly undefined
// 4A9368: variable 'v12' is possibly undefined
// 4A92EF: variable 'v7' is possibly undefined
// 4A9305: variable 'v9' is possibly undefined
// 51A624: using guessed type char *off_51A624;
// 51A968: using guessed type int dword_51A968;

//----- (004A9390) --------------------------------------------------------
int  Rules_SetConstructNextInModule(int result, int nextConstruct)
{
  *(_DWORD *)(result + 16) = nextConstruct;
  return result;
}

//----- (004A93A0) --------------------------------------------------------
int  Rules_GetConstructOwnerModule(int theConstruct)
{
  return *(_DWORD *)(theConstruct + 8);
}

//----- (004A93B0) --------------------------------------------------------
int  Rules_GetModuleConstructListHead(int theModuleItem)
{
  return *(_DWORD *)(theModuleItem + 4);
}

//----- (004A93C0) --------------------------------------------------------
int  Class_Enum(int theConstruct, int moduleItemIndex)
{
  int result; // eax

  if ( theConstruct )
    return *(_DWORD *)(theConstruct + 16);
  result = Module_GetItem(0, moduleItemIndex);
  if ( result )
    return Rules_GetModuleConstructListHead(result);
  return result;
}

//----- (004A93E0) --------------------------------------------------------
int  Rules_GetModuleConstructData(int theModule, int moduleItemIndex)
{
  if ( !theModule )
    theModule = Module_GetCurrent();
  return Module_GetItem(theModule, moduleItemIndex);
}
// 4A93ED: variable 'a2' is possibly undefined

//----- (004A9400) --------------------------------------------------------
int  Rules_ClearModuleConstructList(int theModuleItem, int constructClass, int a3)
{
  int result; // eax
  int next; // edx
  int cleanup; // ecx

  (void)a3;
  result = *(_DWORD *)(theModuleItem + 4);
  while ( result )
  {
    next = *(_DWORD *)(result + 16);
    cleanup = *(_DWORD *)(constructClass + 44);
    ((void (*)(int))(uintptr_t)(unsigned int)cleanup)(result);
    result = next;
  }
  return result;
}

static signed int sub_4A9430_Impl(int (*callback)(int, intptr_t), int construct_index, intptr_t callback_context, int stop_on_watch);

//----- (004A9430) --------------------------------------------------------
signed int  Rules_DoForAllConstructs(void (*actionFunction)(void), int interruptable)
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))actionFunction, 0, 0, interruptable);
}

static signed int sub_4A9430_Impl(int (*callback)(int, intptr_t), int construct_index, intptr_t callback_context, int stop_on_watch)
{
  int module; // ebp
  int module_index; // [esp+4h] [ebp-10h]
  int construct_data; // eax
  int item; // ecx

  Module_BeginEnum();
  module = Module_NextEnum(0);
  module_index = 0;
  if ( module )
  {
    while ( 1 )
    {
      Module_SetCurrent(module);
      construct_data = Module_GetItem(module, construct_index);
      item = *(_DWORD *)(construct_data + 4);
      if ( item )
        break;
LABEL_6:
      module = Module_NextEnum(module);
      ++module_index;
      if ( !module )
        goto LABEL_7;
    }
    while ( !stop_on_watch || Rules_GetEvaluationErrorFlag() != 1 )
    {
      callback(item, callback_context);
      item = *(_DWORD *)(item + 16);
      if ( !item )
        goto LABEL_6;
    }
    Module_EndEnum();
    return -1;
  }
  else
  {
LABEL_7:
    Module_EndEnum();
    return module_index;
  }
}

//----- (004A94D0) --------------------------------------------------------
static int sub_4A94D0_Impl(int construct_name, int construct_data, int owner_symbol)
{
  int construct_record; // eax
  int module_data; // eax

  construct_record = Module_FindItemByName(construct_name);
  module_data = Module_GetItem(0, *(_DWORD *)(construct_record + 4));
  *(_DWORD *)(construct_data + 4) = 0;
  *(_DWORD *)(construct_data + 12) = 0;
  *(_DWORD *)(construct_data + 16) = 0;
  *(_DWORD *)(construct_data + 8) = module_data;
  *(_DWORD *)construct_data = owner_symbol;
  return module_data;
}

int  Rules_InitConstructModuleRecord(int constructType, int theConstruct)
{
  return sub_4A94D0_Impl(constructType, theConstruct, theConstruct);
}

//----- (004A9500) --------------------------------------------------------
signed int  Rules_ReplaceConstructPPForm(signed int result, int ppForm)
{
  signed int theConstruct; // ebx
  const char *oldPPForm; // edx

  theConstruct = result;
  oldPPForm = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(result + 4);
  if ( oldPPForm )
  {
    result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(result + 4), strlen(oldPPForm) + 1);
    *(_DWORD *)(theConstruct + 4) = ppForm;
  }
  else
  {
    *(_DWORD *)(result + 4) = ppForm;
  }
  return result;
}

//----- (004A9540) --------------------------------------------------------
signed int  Rules_ListWatchFlagStatus(
        int constructClass,
        int logicalName,
        int accessFunc,
        int argExprs,
        double a5,
        void (*setFunction)(void))
{
  return Rules_ProcessWatchFlagRequest(constructClass, (int)aListWatchIte_0, argExprs, logicalName, a5, 0, 0, accessFunc, setFunction);
}

//----- (004A9560) --------------------------------------------------------
signed int  Rules_ApplyWatchFlagCommand(
        int constructClass,
        int newState,
        int accessFunc,
        int argExprs,
        double a5,
        void (*setFunction)(void))
{
  return Rules_ProcessWatchFlagRequest(constructClass, (int)aWatch_0, argExprs, (int)g_IO_LogicalNameTable_WError[0], a5, 1, newState, accessFunc, setFunction);
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004A9590) --------------------------------------------------------
signed int  Rules_ProcessWatchFlagRequest(
        int constructType,
        int functionName,
        int argExprs,
        int logicalName,
        double a5,
        int setMode,
        int newState,
        int getWatchFunc,
        void (*setWatchFunc)(void))
{
  int argPtr; // esi
  int v12; // edx
  int Name; // eax
  int v14; // ecx
  int v15; // ecx
  _DWORD argValue[7]; // [esp+0h] [ebp-30h] BYREF
  int argIndex; // [esp+1Ch] [ebp-14h]
  int i; // [esp+20h] [ebp-10h]

  argValue[6] = functionName;
  argPtr = argExprs;
  argIndex = 2;
  if ( argExprs )
  {
    while ( 1 )
    {
      if ( !argPtr )
        return 1;
      if ( Parser_ParseForm((__int16 *)argPtr, argValue, argExprs, a5) )
        return 0;
      if ( argValue[1] != 2 || !Symbol_LookupInModule((char **)constructType, *(_BYTE **)(argValue[2] + 16), 1) )
        break;
      if ( setMode )
        setWatchFunc();
      else
        Rules_PrintWatchFlagState(logicalName, constructType);
      argPtr = *(_DWORD *)(argPtr + 10);
      ++argIndex;
    }
    Parser_ReportError(argIndex, *(_DWORD *)constructType);
    return 0;
  }
  else
  {
    Module_BeginEnum();
    for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
    {
      Module_SetCurrent(i);
      if ( !v12 )
      {
        Name = Module_GetName(i);
        Output_Write(logicalName, Name, v14);
        Output_Write(logicalName, (int)asc_5084B4, v15);
      }
      while ( (*(int (**)(void))(constructType + 28))() )
      {
        if ( setMode )
        {
          setWatchFunc();
        }
        else
        {
          Output_Write(logicalName, (int)asc_5084B8, getWatchFunc);
          Rules_PrintWatchFlagState(logicalName, constructType);
        }
      }
    }
    Module_EndEnum();
    return 1;
  }
}
// 4A95E5: variable 'v12' is possibly undefined
// 4A95F4: variable 'v14' is possibly undefined
// 4A9600: variable 'v15' is possibly undefined
// 4A9671: variable 'a3' is possibly undefined

//----- (004A9710) --------------------------------------------------------
signed int  Rules_PrintWatchFlagState(int logicalName, int constructType)
{
  int theConstruct; // eax
  int v4; // ecx
  int (*getWatchFunc)(void); // ecx
  int v6; // ecx

  theConstruct = (*(int (**)(void))(constructType + 16))();
  Output_Write(logicalName, *(_DWORD *)(theConstruct + 16), v4);
  if ( getWatchFunc() )
    return Output_Write(logicalName, (int)aOn_2, v6);
  else
    return Output_Write(logicalName, (int)aOff_2, v6);
}
// 4A971D: variable 'v4' is possibly undefined
// 4A9724: variable 'v5' is possibly undefined
// 4A9731: variable 'v6' is possibly undefined

//----- (004A9750) --------------------------------------------------------
int  Symbol_LookupInModule(char **constructType, _BYTE *constructName, int moduleNameAllowed)
{
  char *typeName; // edi
  int result; // eax
  int theConstruct; // edx
  int count; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+4h] [ebp-14h]

  v9 = moduleNameAllowed;
  typeName = *constructType;
  result = Rules_FindImportExportConstruct(*constructType, &count, constructName, 1, 0);
  theConstruct = result;
  if ( result )
  {
    if ( count > 1 )
    {
      Rules_ReportAmbiguousReferenceError((int)typeName, (int)constructName);
      return 0;
    }
  }
  else
  {
    if ( v9 && Rules_FindModuleSeparator(constructName) )
      return ((int (*)(void))constructType[3])();
    return theConstruct;
  }
  return result;
}
// 4A97AE: variable 'v7' is possibly undefined

//----- (004A97C0) --------------------------------------------------------
_DWORD * Instance_ActiveInitializeInstanceFunction(uintptr_t returnValue, double a2)
{
  _DWORD *result; // eax
  _DWORD *theInstance; // ebx
  uintptr_t out; // ecx

  out = returnValue;
  *(_DWORD *)(out + 4) = 2;
  *(_DWORD *)(out + 8) = g_ClipsFalseSymbol;
  result = Instance_ResolveArgumentToInstance((int)aInitializeIn_0, (int)out, a2);
  theInstance = result;
  if ( result )
  {
    result = (_DWORD *)Instance_InitializeSlots(
                         (int)result,
                         *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
                         a2);
    if ( result == (_DWORD *)1 )
    {
      *(_DWORD *)(out + 4) = 8;
      result = (_DWORD *)theInstance[7];
      *(_DWORD *)(out + 8) = result;
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9810) --------------------------------------------------------
_DWORD * Instance_ActiveMakeInstanceFunction(uintptr_t returnValue, uintptr_t a2, double a3)
{
  uintptr_t expression; // eax
  int instance_name; // ecx
  int class_record; // edx
  _DWORD *result; // eax
  int parsed_ptr; // ecx
  _DWORD *parsed; // [esp+0h] [ebp-24h] BYREF

  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6);
  Parser_ParseForm((__int16 *)expression, parsed, (int)a2, a3);
  if ( parsed[1] != 2 && parsed[1] != 8 )
  {
    Rules_PrintErrorID((int)aInsmngr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_2, 0);
    result = (_DWORD *)(uintptr_t)(unsigned int)Lexer_ErrorRecover(1);
    goto done;
  }
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  instance_name = parsed[2];
  if ( *(_WORD *)expression == 57 )
  {
    class_record = *(_DWORD *)(expression + 2);
  }
  else
  {
    Parser_ParseForm((__int16 *)expression, parsed, instance_name, a3);
    if ( parsed[1] != 2 )
    {
      Rules_PrintErrorID((int)aInsmngr, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_3, 0);
      result = (_DWORD *)(uintptr_t)(unsigned int)Lexer_ErrorRecover(1);
      goto done;
    }
    class_record = (int)Class_LookupInScope(*(_BYTE **)((uintptr_t)(unsigned int)parsed[2] + 16));
    if ( !class_record )
    {
      Class_ReportLookupError(
        *(_DWORD *)(*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 2)) + 16),
        *(_DWORD *)((uintptr_t)(unsigned int)parsed[2] + 16));
      result = (_DWORD *)(uintptr_t)(unsigned int)Lexer_ErrorRecover(1);
      goto done;
    }
  }
  result = Instance_BuildInstance(instance_name, class_record, 1, a3);
  if ( result )
  {
    if ( Instance_InitializeSlots((int)result, *(_DWORD *)(expression + 10), a3) )
    {
      *(_DWORD *)(returnValue + 4) = 8;
      result = Instance_GetQualifiedName((int)result, (int)result);
      *(_DWORD *)(returnValue + 8) = result;
    }
    else
    {
      result = (_DWORD *)(uintptr_t)(unsigned int)Instance_DeleteInstance((int)result, a3);
      *(_DWORD *)(returnValue + 4) = 2;
      *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
      goto done;
    }
  }
done:
  if ( *(_DWORD *)(returnValue + 4) == 2 && *(_DWORD *)(returnValue + 8) != g_ClipsFalseSymbol )
  {
    if ( getenv("CLASH95_TRACE_RULES_ASSERT_FACT") )
    {
      fprintf(
        stderr,
        "[rules] make-instance-reset-invalid-symbol value=%08x nil=%08x caller=%p\n",
        *(_DWORD *)(returnValue + 8),
        g_ClipsFalseSymbol,
        __builtin_return_address(0));
      fflush(stderr);
    }
    *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  }
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9970) --------------------------------------------------------
signed int * Instance_GetQualifiedName(int theInstance, int a2)
{
  uintptr_t instance; // edx
  uintptr_t class_record; // eax
  uintptr_t module_record; // ecx
  uintptr_t instance_name_symbol; // eax
  const char *module_name; // ebx
  const char *instance_name; // edi
  unsigned int buffer_size; // esi
  char *qualified_name; // ecx
  signed int *symbol; // ebx

  instance = (uintptr_t)(unsigned int)theInstance;
  if ( instance == (uintptr_t)&g_Instance_DummyInstanceRecord )
    return Str_Intern(aDummyInstance, a2);
  instance_name_symbol = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 28);
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 )
    return (signed int *)instance_name_symbol;
  class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
  module_record = (uintptr_t)(unsigned int)*(_DWORD *)(class_record + 8);
  if ( Module_GetCurrent() == *(_DWORD *)module_record )
    return (signed int *)instance_name_symbol;
  module_name = (const char *)Module_GetName(*(_DWORD *)module_record);
  instance_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(instance_name_symbol + 16);
  buffer_size = (unsigned int)(strlen(instance_name) + strlen(module_name) + 3);
  qualified_name = (char *)(uintptr_t)(unsigned int)Mem_SmallBlockAlloc(buffer_size);
  sprintf_(qualified_name, "%s::%s", module_name, instance_name);
  symbol = Str_Intern(qualified_name, buffer_size);
  Mem_SmallBlockFree(qualified_name, buffer_size);
  return symbol;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A214: using guessed type void *off_51A214;

//----- (004A9A20) --------------------------------------------------------
_DWORD * Instance_BuildInstance(int instanceName, int theDefclass, int initMessage, double a4)
{
  signed int *nameSymbol; // esi
  signed int separatorPosition; // eax
  signed int *moduleName; // eax
  int v8; // ecx
  _DWORD *existingInstance; // eax
  int v10; // ecx
  _DWORD *oldInstance; // ebp
  int v12; // eax
  int bucketHead; // ebx
  int v14; // ecx
  int v15; // eax
  _DWORD *theInstance; // ecx
  _DWORD *result; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  int v31; // eax
  int prevInstance; // [esp+0h] [ebp-20h] BYREF
  int hashBucket; // [esp+4h] [ebp-1Ch]
  int v34; // [esp+8h] [ebp-18h]
  int v35; // [esp+Ch] [ebp-14h]

  nameSymbol = (signed int *)instanceName;
  v35 = initMessage;
  if ( g_Rules_JoinOperationInProgress && (*(_BYTE *)(theDefclass + 20) & 8) != 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 10, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotCreate_0, v18);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternMatch_0, v19);
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( (*(_BYTE *)(theDefclass + 20) & 4) != 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotCreate_1, v20);
    v21 = Rules_GetConstructNameString(theDefclass);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v21, (int)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, v22);
    Lexer_ErrorRecover(1);
    return 0;
  }
  separatorPosition = Rules_FindModuleSeparator((_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)(instanceName + 16));
  if ( separatorPosition )
  {
    moduleName = Rules_ExtractModuleName(separatorPosition);
    if ( !moduleName || moduleName != ***(signed int ****)(theDefclass + 8) )
    {
      Rules_PrintErrorID((int)aInsmngr, 11, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInvalidModuleS, v23);
      Lexer_ErrorRecover(1);
      return 0;
    }
    nameSymbol = Rules_ExtractConstructName(v8, (char *)nameSymbol[4], v8);
  }
  existingInstance = Instance_FindHashEntryForBuild(theDefclass, (int)nameSymbol, &prevInstance, &hashBucket);
  oldInstance = existingInstance;
  if ( !existingInstance )
    goto LABEL_14;
  if ( (existingInstance[6] & 1) == 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheInstance, v24);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], nameSymbol[4], v25);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aHasASlotValueW, v26);
    Lexer_ErrorRecover(1);
    return 0;
  }
  ++existingInstance[10];
  ++nameSymbol[1];
  if ( (existingInstance[6] & 2) == 0 )
  {
    if ( g_Instance_UseMessageDispatchForInit )
    {
      v34 = g_ClipsDeleteMessageSymbol;
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, (int)existingInstance, 0, 0, a4);
    }
    else
    {
      Instance_DeleteInstance((int)existingInstance, a4);
    }
  }
  --oldInstance[10];
  Rules_DecrementSymbolCount((int)nameSymbol, v10);
  if ( (oldInstance[6] & 2) == 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 5, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDele_0, v27);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], nameSymbol[4], v28);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, v29);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
LABEL_14:
    g_ClipsInstanceUnderConstruction = Instance_AllocateInstanceRecord();
    if ( Rules_AddLogicalDependencyLink(g_ClipsInstanceUnderConstruction, 0) )
    {
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 28) = nameSymbol;
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 44) = theDefclass;
      Instance_AllocateSlotValueTable(v35);
      v12 = hashBucket;
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 36) = hashBucket;
      if ( prevInstance )
      {
        *(_DWORD *)(g_ClipsInstanceUnderConstruction + 60) = *(_DWORD *)(prevInstance + 60);
        v30 = *(_DWORD *)(prevInstance + 60);
        if ( v30 )
          *(_DWORD *)(v30 + 56) = g_ClipsInstanceUnderConstruction;
        v31 = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(prevInstance + 60) = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(v31 + 56) = prevInstance;
      }
      else
      {
        *(_DWORD *)(g_ClipsInstanceUnderConstruction + 60) = *(_DWORD *)(g_Instance_HashTableBase + 4 * v12);
        bucketHead = *(_DWORD *)(g_Instance_HashTableBase + 4 * hashBucket);
        if ( bucketHead )
          *(_DWORD *)(bucketHead + 56) = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(4 * hashBucket + g_Instance_HashTableBase) = g_ClipsInstanceUnderConstruction;
      }
      v14 = *(_DWORD *)(g_ClipsInstanceUnderConstruction + 44);
      if ( *(_DWORD *)(v14 + 80) )
        *(_DWORD *)(*(_DWORD *)(v14 + 84) + 52) = g_ClipsInstanceUnderConstruction;
      else
        *(_DWORD *)(v14 + 80) = g_ClipsInstanceUnderConstruction;
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 48) = *(_DWORD *)(*(_DWORD *)(g_ClipsInstanceUnderConstruction + 44) + 84);
      v15 = g_ClipsInstanceUnderConstruction;
      *(_DWORD *)(*(_DWORD *)(g_ClipsInstanceUnderConstruction + 44) + 84) = g_ClipsInstanceUnderConstruction;
      if ( g_Clips_InstanceListHead )
        *(_DWORD *)(g_Instance_GlobalListTail + 68) = v15;
      else
        g_Clips_InstanceListHead = v15;
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 64) = g_Instance_GlobalListTail;
      g_Instance_InstancesChangedFlag = 1;
      g_Instance_GlobalListTail = g_ClipsInstanceUnderConstruction;
      Instance_SetActiveFlag(g_ClipsInstanceUnderConstruction, 1);
      theInstance = (_DWORD *)g_ClipsInstanceUnderConstruction;
      g_ClipsInstanceUnderConstruction = 0;
      if ( (*(_BYTE *)(theInstance[11] + 20) & 8) != 0 )
        Rules_ObjectMatchAction((unsigned __int16 *)1, theInstance, -1, a4);
      return theInstance;
    }
    else
    {
      g_ClipsMemFreeListTemp = g_ClipsInstanceUnderConstruction;
      *(_DWORD *)g_ClipsInstanceUnderConstruction = *(_DWORD *)(g_ClipsMemoryTable + 320);
      *(_DWORD *)(g_ClipsMemoryTable + 320) = g_ClipsMemFreeListTemp;
      result = 0;
      g_ClipsInstanceUnderConstruction = 0;
    }
  }
  return result;
}
// 4A9A7C: variable 'v8' is possibly undefined
// 4A9AD9: variable 'v10' is possibly undefined
// 4A9C15: variable 'v16' is possibly undefined
// 4A9C3A: variable 'v18' is possibly undefined
// 4A9C49: variable 'v19' is possibly undefined
// 4A9C7D: variable 'v20' is possibly undefined
// 4A9CA2: variable 'v22' is possibly undefined
// 4A9CD9: variable 'v23' is possibly undefined
// 4A9D0D: variable 'v24' is possibly undefined
// 4A9D1A: variable 'v25' is possibly undefined
// 4A9D29: variable 'v26' is possibly undefined
// 4A9D67: variable 'v27' is possibly undefined
// 4A9D74: variable 'v28' is possibly undefined
// 4A9D83: variable 'v29' is possibly undefined
// 51A278: using guessed type int dword_51A278;
// 51A284: using guessed type int dword_51A284;
// 51A288: using guessed type int dword_51A288;
// 51A614: using guessed type char *off_51A614[5];
// 51A954: using guessed type int dword_51A954;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD14: using guessed type int dword_51AD14;
// 51AD18: using guessed type int dword_51AD18;
// 51AD38: using guessed type int dword_51AD38;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A9E30) --------------------------------------------------------
char  Instance_InitSlotsCommand(uintptr_t returnValue, uintptr_t a2, double a3)
{
  signed int v2; // eax
  int selfArgument; // eax

  (void)a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  v2 = MessageHandler_CheckCurrentMessage((int)aInitSlots, 1);
  if ( v2 )
  {
    selfArgument = MessageHandler_GetNthArgument(0);
    LOBYTE(v2) = Instance_InitSlots(*(_DWORD *)(selfArgument + 8), (__int16)returnValue, a3);
    if ( !g_ClipsEvaluationError )
    {
      *(_DWORD *)(returnValue + 4) = 7;
      v2 = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
      *(_DWORD *)(returnValue + 8) = v2;
    }
  }
  return v2;
}
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9E90) --------------------------------------------------------
signed int  Instance_DeleteInstance(int theInstance, double a2)
{
  uintptr_t instance; // ecx
  uintptr_t class_record; // eax
  unsigned char flags; // dh
  unsigned int previous_hash_link; // ebx
  unsigned int next_hash_link; // esi
  unsigned int previous_class_link; // edi
  unsigned int next_class_link; // ebp
  unsigned int previous_global_link; // eax
  unsigned int next_global_link; // edx
  int was_active; // ebx
  unsigned int deferred_node; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx

  instance = (uintptr_t)(unsigned int)theInstance;
  class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
  if ( g_Rules_JoinOperationInProgress && (*(_BYTE *)(class_record + 20) & 8) != 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 12, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotDeleteIn, v14);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternMatch_0, v15);
    Lexer_ErrorRecover(1);
    return 0;
  }
  flags = *(_BYTE *)(instance + 24);
  if ( (flags & 2) != 0 )
    return 0;
  if ( (flags & 1) != 0 )
  {
    if ( (*(_BYTE *)(class_record + 20) & 0x10) != 0 )
      Instance_PrintWatchTrace((int)asc_508714, (int)instance);
    Rules_ReleaseLogicalSupportList((int)instance);
    if ( (*(_BYTE *)(class_record + 20) & 8) != 0 )
      Rules_ObjectMatchAction((unsigned __int16 *)2, (_DWORD *)instance, -1, a2);
    previous_hash_link = *(_DWORD *)(instance + 56);
    if ( previous_hash_link )
      *(_DWORD *)((uintptr_t)previous_hash_link + 60) = *(_DWORD *)(instance + 60);
    else
      *(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * *(_DWORD *)(instance + 36)) = *(_DWORD *)(instance + 60);
    next_hash_link = *(_DWORD *)(instance + 60);
    if ( next_hash_link )
      *(_DWORD *)((uintptr_t)next_hash_link + 56) = *(_DWORD *)(instance + 56);
    previous_class_link = *(_DWORD *)(instance + 48);
    if ( previous_class_link )
      *(_DWORD *)((uintptr_t)previous_class_link + 52) = *(_DWORD *)(instance + 52);
    else
      *(_DWORD *)(class_record + 80) = *(_DWORD *)(instance + 52);
    next_class_link = *(_DWORD *)(instance + 52);
    if ( next_class_link )
      *(_DWORD *)((uintptr_t)next_class_link + 48) = *(_DWORD *)(instance + 48);
    else
      *(_DWORD *)(class_record + 84) = *(_DWORD *)(instance + 48);
    previous_global_link = *(_DWORD *)(instance + 64);
    if ( previous_global_link )
      *(_DWORD *)((uintptr_t)previous_global_link + 68) = *(_DWORD *)(instance + 68);
    else
      g_Clips_InstanceListHead = *(_DWORD *)(instance + 68);
    next_global_link = *(_DWORD *)(instance + 68);
    if ( next_global_link )
      *(_DWORD *)((uintptr_t)next_global_link + 64) = *(_DWORD *)(instance + 64);
    else
      g_Instance_GlobalListTail = *(_DWORD *)(instance + 64);
    was_active = *(_DWORD *)(instance + 24) & 1;
    Instance_SetActiveFlag((int)instance, 0);
    if ( was_active == 1 && !*(_DWORD *)(instance + 8) )
      Instance_ReleaseSlotValues((int)instance);
    if ( *(_DWORD *)(instance + 40)
      || g_ClipsCurrentEvaluationDepth >= *(_DWORD *)(instance + 32)
      || g_Instance_PurgeInProgress
      || *(_DWORD *)(instance + 8) )
    {
      deferred_node = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32);
      if ( deferred_node )
      {
        g_ClipsMemFreeListTemp = deferred_node;
        *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 32) = *(_DWORD *)(uintptr_t)deferred_node;
        deferred_node = g_ClipsMemFreeListTemp;
      }
      else
      {
        deferred_node = Mem_HeapAllocWithRetry((_DWORD *)8);
      }
      *(_BYTE *)(instance + 24) |= 2u;
      *(_DWORD *)(uintptr_t)deferred_node = (int)instance;
      *(_DWORD *)((uintptr_t)deferred_node + 4) = g_Instance_DeletedListHead;
      g_Instance_DeletedListHead = deferred_node;
      g_ClipsEphemeralItemCount += 2;
      g_ClipsEphemeralItemBytes += 88;
      g_Instance_InstancesChangedFlag = 1;
      return 1;
    }
    else
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(instance + 28), (int)instance);
      g_ClipsMemFreeListTemp = (int)instance;
      *(_DWORD *)instance = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 320);
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 320) = g_ClipsMemFreeListTemp;
      g_Instance_InstancesChangedFlag = 1;
      return 1;
    }
  }
  else
  {
    Rules_PrintErrorID((int)aInsmngr, 6, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotDelete_0, v16);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(instance + 28) + 16), v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuringInitiali, v18);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 4AA009: variable 'v14' is possibly undefined
// 4AA018: variable 'v15' is possibly undefined
// 4AA049: variable 'v16' is possibly undefined
// 4AA04E: variable 'v17' is possibly undefined
// 4AA068: variable 'v18' is possibly undefined
// 51A278: using guessed type int dword_51A278;
// 51A280: using guessed type int dword_51A280;
// 51A288: using guessed type int dword_51A288;
// 51A28C: using guessed type int dword_51A28C;
// 51A614: using guessed type char *off_51A614[5];
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A954: using guessed type int dword_51A954;
// 51A96C: using guessed type int dword_51A96C;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD18: using guessed type int dword_51AD18;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AA140) --------------------------------------------------------
int  Instance_InitializeInstanceFunction(uintptr_t returnValue, uintptr_t a2, double a3)
{
  int previous_watch_state; // edx

  (void)a2;
  previous_watch_state = Rules_SetObjectPatternMatchDelay(1, a3);
  Instance_ActiveInitializeInstanceFunction(returnValue, a3);
  return Rules_SetObjectPatternMatchDelay(previous_watch_state, a3);
}

//----- (004AA170) --------------------------------------------------------
int  Instance_MakeInstanceFunction(uintptr_t returnValue, uintptr_t a2, double a3)
{
  int previous_watch_state; // edx

  (void)a2;
  previous_watch_state = Rules_SetObjectPatternMatchDelay(1, a3);
  Instance_ActiveMakeInstanceFunction(returnValue, returnValue, a3);
  return Rules_SetObjectPatternMatchDelay(previous_watch_state, a3);
}

//----- (004AA1A0) --------------------------------------------------------
signed int Instance_AllocateInstanceRecord()
{
  _DWORD *freeNode; // edx
  signed int result; // eax
  char v2; // dl
  int evalDepth; // edx

  Rules_EnsureObjectPatternVTable();
  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 320);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 320);
    *(_DWORD *)(g_ClipsMemoryTable + 320) = *freeNode;
    result = g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0x50);
  }
  *(_DWORD *)result = (int)(uintptr_t)g_Rules_ObjectPatternVTable;
  *(_DWORD *)(result + 4) = 0;
  *(_DWORD *)(result + 8) = 0;
  *(_DWORD *)(result + 12) = 0;
  *(_DWORD *)(result + 16) = 0;
  *(_DWORD *)(result + 20) = 0;
  v2 = *(_BYTE *)(result + 24);
  *(_DWORD *)(result + 40) = 0;
  *(_BYTE *)(result + 24) = v2 & 0xF8;
  evalDepth = g_ClipsCurrentEvaluationDepth;
  *(_DWORD *)(result + 28) = 0;
  *(_DWORD *)(result + 36) = 0;
  *(_DWORD *)(result + 44) = 0;
  *(_DWORD *)(result + 76) = 0;
  *(_DWORD *)(result + 72) = 0;
  *(_DWORD *)(result + 48) = 0;
  *(_DWORD *)(result + 52) = 0;
  *(_DWORD *)(result + 56) = 0;
  *(_DWORD *)(result + 60) = 0;
  *(_DWORD *)(result + 64) = 0;
  *(_DWORD *)(result + 68) = 0;
  *(_DWORD *)(result + 32) = evalDepth;
  return result;
}
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AA270) --------------------------------------------------------
_DWORD * Instance_FindHashEntryForBuild(int theDefclass, int instanceName, _DWORD *prevInstance, _DWORD *hashTableIndex)
{
  unsigned int bucket; // eax
  _DWORD *result; // eax

  bucket = Instance_HashNameToBucket(instanceName);
  *hashTableIndex = bucket;
  result = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * bucket);
  for ( *prevInstance = 0; result; result = (_DWORD *)(uintptr_t)(unsigned int)result[15] )
  {
    if ( instanceName == (int)result[7] )
      break;
    *prevInstance = (int)(uintptr_t)result;
  }
  while ( result && instanceName == (int)result[7] )
  {
    if ( *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(theDefclass + 8) ==
         *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)result[11] + 8) )
      return result;
    *prevInstance = (int)(uintptr_t)result;
    result = (_DWORD *)(uintptr_t)(unsigned int)result[15];
  }
  return 0;
}
// 51A278: using guessed type int dword_51A278;

//----- (004AA2E0) --------------------------------------------------------
int  Instance_SetActiveFlag(int result, int set)
{
  int theInstance; // ecx

  theInstance = result;
  if ( set == 1 )
  {
    if ( (*(_BYTE *)(result + 24) & 1) == 0 )
    {
      if ( (*(_BYTE *)(*(_DWORD *)(result + 44) + 20) & 0x10) != 0 )
        Instance_PrintWatchTrace((int)asc_508718, result);
      *(_BYTE *)(theInstance + 24) |= 1u;
      *(_DWORD *)(theInstance + 32) = g_ClipsCurrentEvaluationDepth;
      ++*(_DWORD *)(*(_DWORD *)(theInstance + 28) + 4);
      result = Class_AddBusyReference(*(_DWORD *)(theInstance + 44));
      ++g_Rules_ActiveInstanceCount;
    }
  }
  else if ( (*(_BYTE *)(result + 24) & 1) != 0 )
  {
    *(_BYTE *)(result + 24) &= ~1u;
    --g_Rules_ActiveInstanceCount;
  }
  return result;
}
// 4AA303: variable 'v2' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 51AD10: using guessed type int dword_51AD10;

//----- (004AA340) --------------------------------------------------------
int  Instance_AllocateSlotValueTable(int initMessage)
{
  int class_record; // edx
  int slot_count; // eax
  int local_slot_count; // edx
  int slot_value_table; // ecx
  int local_slot_values; // ebx
  int local_slot_cursor; // ebx
  int slot_descriptors; // esi
  int slot_value_cursor; // ecx
  int slot_descriptor; // eax
  int slot_value; // eax
  int create_mode; // [esp+4h] [ebp-20h]
  int index; // edi

  class_record = *(_DWORD *)(g_ClipsInstanceUnderConstruction + 44);
  slot_count = *(_DWORD *)(class_record + 72);
  local_slot_count = *(_DWORD *)(class_record + 68);
  if ( slot_count <= 0 )
    return slot_count;
  slot_value_table = (int)(uintptr_t)Mem_SmallBlockAlloc(4 * slot_count);
  *(_DWORD *)(g_ClipsInstanceUnderConstruction + 72) = slot_value_table;
  local_slot_values = 0;
  if ( local_slot_count )
  {
    local_slot_values = (int)(uintptr_t)Mem_SmallBlockAlloc(12 * local_slot_count);
    *(_DWORD *)(g_ClipsInstanceUnderConstruction + 76) = local_slot_values;
  }
  slot_descriptors = *(_DWORD *)(class_record + 56);
  create_mode = initMessage & 1;
  local_slot_cursor = local_slot_values;
  slot_value_cursor = slot_value_table;
  for ( index = 0; index < slot_count; ++index )
  {
    slot_descriptor = *(_DWORD *)(slot_descriptors + 4 * index);
    if ( (*(_BYTE *)slot_descriptor & 1) != 0 )
    {
      ++*(_DWORD *)(slot_descriptor + 24);
      slot_value = slot_descriptor + 32;
      *(_DWORD *)slot_value_cursor = slot_value;
    }
    else
    {
      slot_value = local_slot_cursor;
      *(_DWORD *)(slot_value + 8) = 0;
      *(_DWORD *)slot_value = slot_descriptor;
      local_slot_cursor += 12;
      *(_DWORD *)slot_value_cursor = slot_value;
    }
    if ( *(_DWORD *)(slot_value + 8) )
    {
      *(_BYTE *)(slot_value + 4) &= ~1u;
    }
    else
    {
      *(_BYTE *)(slot_value + 4) &= ~1u;
      *(_BYTE *)(slot_value + 4) |= create_mode;
      if ( (*(_BYTE *)*(_DWORD *)slot_value & 2) != 0 )
      {
        *(_BYTE *)(slot_value + 4) = (*(_BYTE *)(slot_value + 4) & 3) | 0x10;
        *(_DWORD *)(slot_value + 8) = (int)(uintptr_t)Rules_CreateMultifield(0);
        Rules_InstallMultifield((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot_value + 8));
      }
      else
      {
        *(_BYTE *)(slot_value + 4) = (*(_BYTE *)(slot_value + 4) & 3) | 8;
        *(_DWORD *)(slot_value + 8) = (int)(uintptr_t)Str_Intern(aNil_3, 0);
        Rules_AtomInstall(((unsigned int)*(_DWORD *)(slot_value + 4) << 24) >> 26, *(_DWORD *)(slot_value + 8), slot_value);
      }
    }
    *(_BYTE *)(slot_value + 4) &= ~2u;
    slot_value_cursor += 4;
  }
  return slot_value;
}
// 51AD14: using guessed type int dword_51AD14;

//----- (004AA4A0) --------------------------------------------------------
BOOL  Instance_InitializeSlots(int theInstance, int overrideExprs, double a3)
{
  int v4; // ecx
  char v5; // bl
  __int16 v6; // cx
  int savedSlotInit; // edi
  char v8; // cl
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int messageResult[11]; // [esp+0h] [ebp-2Ch] BYREF

  if ( (*(_BYTE *)(theInstance + 24) & 1) != 0 )
  {
    v4 = *(_DWORD *)(theInstance + 40) + 1;
    v5 = *(_BYTE *)(theInstance + 24) & 0xFE;
    *(_DWORD *)(theInstance + 40) = v4;
    *(_BYTE *)(theInstance + 24) = v5;
    if ( Instance_ApplySlotOverrideList((_DWORD *)theInstance, overrideExprs, v4, a3) )
    {
      *(_BYTE *)(theInstance + 24) |= 4u;
      savedSlotInit = g_Instance_SlotInitInProgress;
      g_Instance_SlotInitInProgress = 1;
      if ( g_Instance_UseMessageDispatchForInit )
        MessageHandler_SendToInstanceAddress(g_MessageHandler_InitSymbol, theInstance, 0, messageResult, a3);
      else
        Instance_InitSlots(theInstance, v6, a3);
      g_Instance_SlotInitInProgress = savedSlotInit;
      v8 = *(_BYTE *)(theInstance + 24) | 1;
      --*(_DWORD *)(theInstance + 40);
      *(_BYTE *)(theInstance + 24) = v8;
      if ( g_ClipsEvaluationError )
      {
        Rules_PrintErrorID((int)aInsmngr, 8, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAnErrorOccurre, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(theInstance + 28) + 16), v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, v16);
        return 0;
      }
      else
      {
        return (v8 & 4) == 0;
      }
    }
    else
    {
      v13 = *(_DWORD *)(theInstance + 40) - 1;
      *(_BYTE *)(theInstance + 24) |= 1u;
      *(_DWORD *)(theInstance + 40) = v13;
      return 0;
    }
  }
  else
  {
    Rules_PrintErrorID((int)aInsmngr, 7, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstance_4, v10);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(theInstance + 28) + 16), v11);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsAlreadyBeing, v12);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 4AA558: variable 'v10' is possibly undefined
// 4AA568: variable 'v11' is possibly undefined
// 4AA577: variable 'v12' is possibly undefined
// 4AA5AD: variable 'v6' is possibly undefined
// 4AA5D2: variable 'v14' is possibly undefined
// 4AA5E2: variable 'v15' is possibly undefined
// 4AA5F1: variable 'v16' is possibly undefined
// 51A27C: using guessed type int dword_51A27C;
// 51A284: using guessed type int dword_51A284;
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51AD34: using guessed type int dword_51AD34;

//----- (004AA610) --------------------------------------------------------
signed int  Instance_ApplySlotOverrideList(_DWORD *theInstance, int slotOverrides, int a3, double a4)
{
  int slot_override; // edi
  int *slot_value; // esi
  signed int result; // eax
  int parsed_ptr; // ecx
  int saved_context; // [esp+18h] [ebp-1Ch]
  int *saved_slot_value; // [esp+1Ch] [ebp-18h]
  _DWORD *parsed; // [esp+0h] [ebp-34h] BYREF

  slot_override = slotOverrides;
  g_ClipsEvaluationError = 0;
  saved_context = g_Instance_SlotInitInProgress;
  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  if ( !slotOverrides )
  {
    result = 1;
    goto done;
  }
  while ( 1 )
  {
    int slot_name_symbol;
    int pair_node;
    int value_expression;

    if ( Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)slot_override, parsed, a3, a4) == 1 || parsed[1] != 2 )
    {
      Rules_PrintErrorID((int)aInsmngr, 9, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_4, 0);
      Lexer_ErrorRecover(1);
      result = 0;
      goto done;
    }
    slot_name_symbol = parsed[2];
    slot_value = (int *)Instance_GetSlotValueBySymbol((int)(uintptr_t)theInstance, slot_name_symbol);
    saved_slot_value = slot_value;
    if ( !slot_value )
      break;
    g_Instance_SlotInitInProgress = 1;
    pair_node = *(_DWORD *)((uintptr_t)(unsigned int)slot_override + 10);
    value_expression = *(_DWORD *)((uintptr_t)(unsigned int)pair_node + 6);
    if ( g_Instance_UseMessageDispatchForInit )
    {
      MessageHandler_SendToInstanceAddress(*(_DWORD *)((uintptr_t)(unsigned int)*slot_value + 12), (int)(uintptr_t)theInstance, value_expression, 0, a4);
    }
    else if ( Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)(uintptr_t)(unsigned int)*slot_value << 30 >> 31, value_expression, parsed, a4) )
    {
      Instance_PutSlotValue(theInstance, slot_value, parsed, a4);
    }
    g_Instance_SlotInitInProgress = saved_context;
    if ( g_ClipsEvaluationError )
    {
      result = 0;
      goto done;
    }
    *((_BYTE *)saved_slot_value + 4) |= 2u;
    slot_override = *(_DWORD *)((uintptr_t)(unsigned int)pair_node + 10);
    if ( !slot_override )
    {
      result = 1;
      goto done;
    }
  }
  Rules_PrintErrorID((int)aInsmngr, 13, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_2, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)parsed[2] + 16), 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotExistIn, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)theInstance[7] + 16), 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, 0);
  Lexer_ErrorRecover(1);
  result = 0;
done:
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A27C: using guessed type int dword_51A27C;
// 51A284: using guessed type int dword_51A284;
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;

//----- (004AA7C0) --------------------------------------------------------
char  Instance_InitSlots(int theInstance, __int16 a2, double a3)
{
  int slot_value_offset; // ebp
  int slot_value; // esi
  int slot_descriptor; // eax
  int slot_value_table; // eax
  unsigned __int8 slot_flags; // dh
  unsigned __int8 descriptor_flags; // bl
  char result; // al
  int parsed_ptr; // ecx
  _DWORD *parsed; // [esp+0h] [ebp-34h] BYREF
  unsigned int i; // [esp+18h] [ebp-1Ch]

  result = 1;
  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  if ( (*(_BYTE *)((uintptr_t)(unsigned int)theInstance + 24) & 4) != 0 )
  {
    slot_value_offset = 0;
    for ( i = 0; ; ++i )
    {
      int class_record = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 44);
      if ( i >= *(_DWORD *)((uintptr_t)(unsigned int)class_record + 72) )
        break;
      slot_value_table = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 72);
      slot_value = *(_DWORD *)((uintptr_t)(unsigned int)slot_value_table + slot_value_offset);
      slot_flags = *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4);
      if ( (slot_flags & 2) != 0 )
      {
        *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) = slot_flags & 0xFD;
      }
      else
      {
        slot_descriptor = *(_DWORD *)(uintptr_t)(unsigned int)slot_value;
        descriptor_flags = *(_BYTE *)(uintptr_t)(unsigned int)slot_descriptor;
        if ( (descriptor_flags & 0x40) != 0 )
        {
          if ( Parser_ParseSlotDefaultOrRestriction(
                 ((unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)slot_descriptor << 30) >> 31,
                 *(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 16),
                 parsed,
                 a3) )
            result = Instance_PutSlotValue(
                       (_DWORD *)(uintptr_t)(unsigned int)theInstance,
                       (int *)(uintptr_t)(unsigned int)slot_value,
                       parsed,
                       a3);
        }
        else if ( ((descriptor_flags & 1) != 0
                && *(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 24) != 1)
               || (*(_BYTE *)((uintptr_t)(unsigned int)slot_descriptor + 1) & 1) != 0 )
        {
          if ( (*(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) & 1) != 0 )
          {
            Rules_PrintErrorID((int)aInsmngr, 14, 0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOverrideRequir, 0);
            Output_Write(
              (int)g_IO_LogicalNameTable_WError[0],
              *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 8) + 12) + 16),
              0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInInstance_0, 0);
            Output_Write(
              (int)g_IO_LogicalNameTable_WError[0],
              *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)theInstance + 28) + 16),
              0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, 0);
            result = Lexer_ErrorRecover(1);
          }
        }
        else
        {
          result = Instance_StoreSlotValueAndMatch(
                     (_DWORD *)(uintptr_t)(unsigned int)theInstance,
                     (int *)(uintptr_t)(unsigned int)slot_value,
                     a2,
                     (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 16),
                     a3);
        }
      }
      *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) &= ~1u;
      if ( (*(_BYTE *)((uintptr_t)(unsigned int)theInstance + 24) & 2) != 0 )
      {
        Output_Write(
          (int)g_IO_LogicalNameTable_WError[0],
          *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)theInstance + 28) + 16),
          0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstanceDelete, 0);
        result = Lexer_ErrorRecover(1);
      }
      if ( g_ClipsEvaluationError )
        goto done;
      slot_value_offset += 4;
    }
    *(_BYTE *)((uintptr_t)(unsigned int)theInstance + 24) &= ~4u;
  }
  else
  {
    Rules_PrintErrorID((int)aInsmngr, 15, 0);
    Lexer_ErrorRecover(1);
    result = Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInitSlotsNotVa, 0);
  }
done:
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;

//----- (004AA980) --------------------------------------------------------
signed int  Instance_PrintWatchTrace(int traceString, int theInstance)
{
  int v2; // ecx
  int v3; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], traceString, theInstance);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aInstance, v2);
  return Instance_PrintNameOfClass((int)g_IO_LogicalNameTable_WTrace[0], v3, 1);
}
// 4AA9A2: variable 'v2' is possibly undefined
// 4AA9AE: variable 'v3' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];

//----- (004AA9C0) --------------------------------------------------------
int __fastcall Rules_ParseObjectInstanceFunctionCall(int top, int readSource)
{
  int **Symbol; // eax
  int v4; // ecx
  int callType; // esi
  _WORD *v6; // ecx
  signed int v7; // eax
  int v8; // ecx
  int v9; // ecx
  int **v11; // eax
  int v12; // ecx
  int **v13; // eax
  int v14; // ecx
  int **v15; // eax
  int v16; // ecx
  int **v17; // eax
  int v18; // ecx
  int **v19; // eax
  int v20; // ecx
  int **v21; // eax
  int v22; // ecx
  int **v23; // eax
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  signed int v29; // eax
  int v30; // ecx
  int v31; // ecx
  signed int v32; // eax
  _WORD *v33; // edi
  int **v34; // eax
  int v35; // edx
  int v36; // ecx
  int v37; // ecx
  int v38; // eax
  int v39; // ecx
  int v40; // edx
  int v41; // ecx
  int **v42; // eax
  signed int v43; // eax
  _DWORD *v44; // edx
  int v45; // ecx
  signed int v46; // eax
  int v47; // ecx
  int v48; // ecx
  _DWORD errorFlag[5]; // [esp+0h] [ebp-14h] BYREF

  errorFlag[3] = top;
  Symbol = Rules_MakeSymbol(aMakeInstance_0);
  if ( Symbol == *(int ***)(v4 + 2) || (v11 = Rules_MakeSymbol(aActiveMakeIn_0), v11 == *(int ***)(v12 + 2)) )
  {
    callType = 0;
  }
  else
  {
    v13 = Rules_MakeSymbol(aInitializeIn_1);
    if ( v13 == *(int ***)(v14 + 2) || (v15 = Rules_MakeSymbol(aActiveInitia_0), v15 == *(int ***)(v16 + 2)) )
    {
      callType = 1;
    }
    else
    {
      v17 = Rules_MakeSymbol(aModifyInstan_0);
      if ( v17 == *(int ***)(v18 + 2)
        || (v19 = Rules_MakeSymbol(aActiveModify_0), v19 == *(int ***)(v20 + 2))
        || (v21 = Rules_MakeSymbol(aMessageModif_0), v21 == *(int ***)(v22 + 2))
        || (v23 = Rules_MakeSymbol(aActiveMessag_0), v23 == *(int ***)(v24 + 2)) )
      {
        callType = 2;
      }
      else
      {
        callType = 3;
      }
    }
  }
  Rules_IncrementIndentDepth(3);
  errorFlag[0] = 0;
  if ( *v6 == 103 )
    *v6 = 10;
  else
    IO_OutWriteToken(asc_508954);
  v7 = Parser_ParseArgument(readSource, errorFlag, (int)v6);
  *(_DWORD *)(v8 + 6) = v7;
  if ( errorFlag[0] )
    goto LABEL_8;
  if ( !v7 )
    goto LABEL_7;
  IO_OutWriteToken(asc_508954);
  if ( !callType )
  {
    if ( **(_WORD **)(v26 + 6) == 2 && !strcmp_(v26, aOf_0) )
    {
      v32 = Parser_ParseArgument(readSource, errorFlag, v31);
      *(_DWORD *)(*(_DWORD *)(v28 + 6) + 10) = v32;
      if ( errorFlag[0] == 1 )
        goto LABEL_8;
      v33 = *(_WORD **)(*(_DWORD *)(v28 + 6) + 10);
      if ( !v33 )
        goto LABEL_7;
      if ( *v33 != 2 || strcmp_(v28, aOf_0) )
      {
        **(_WORD **)(v28 + 6) = 10;
        v34 = Rules_MakeSymbol(aGensym_1);
        *(_DWORD *)(*(_DWORD *)(v30 + 6) + 2) = v34;
LABEL_33:
        if ( !Rules_ResolveClassNameNode(*(_DWORD *)(*(_DWORD *)(v30 + 6) + 10)) )
          goto LABEL_8;
        goto LABEL_34;
      }
    }
    else
    {
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 2 || strcmp_(v27, *(_DWORD *)(g_ClipsParserTokenValue + 16)) )
        goto LABEL_7;
      IO_OutWriteToken(asc_508954);
    }
    v29 = Parser_ParseArgument(readSource, errorFlag, v28);
    *(_DWORD *)(*(_DWORD *)(v30 + 6) + 10) = v29;
    if ( errorFlag[0] )
      goto LABEL_8;
    if ( !*(_DWORD *)(*(_DWORD *)(v30 + 6) + 10) )
    {
LABEL_7:
      Parser_ReportSyntaxError();
LABEL_8:
      Lexer_ErrorRecover(1);
      AST_Free(v9);
      Rules_DecrementIndentDepth(3);
      return 0;
    }
    goto LABEL_33;
  }
  AST_Append(v26, v25);
  Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
  if ( callType == 3 )
  {
    if ( g_ParserCurrentTokenType != 2 || strcmp_(v41, aTo_2) )
    {
      v42 = Rules_MakeSymbol(aGensym_1);
      v43 = AST_NewNode(10, (int)v42);
      *(_DWORD *)(*(_DWORD *)(v37 + 6) + 10) = v43;
      goto LABEL_35;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
    IO_OutWriteToken(asc_508954);
    v46 = Parser_ParseArgument(readSource, v44, v45);
    v35 = *(_DWORD *)(v36 + 6);
    *(_DWORD *)(v35 + 10) = v46;
    if ( errorFlag[0] )
      goto LABEL_8;
    if ( !*(_DWORD *)(*(_DWORD *)(v36 + 6) + 10) )
      goto LABEL_7;
LABEL_34:
    AST_Append(v36, v35);
    Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
LABEL_35:
    v38 = Rules_ParseObjectFunctionArgList(readSource, errorFlag, v37);
    v40 = *(_DWORD *)(*(_DWORD *)(v39 + 6) + 10);
    goto LABEL_36;
  }
  v38 = Rules_ParseObjectFunctionArgList(readSource, errorFlag, v41);
  v40 = *(_DWORD *)(v47 + 6);
LABEL_36:
  *(_DWORD *)(v40 + 10) = v38;
  if ( errorFlag[0] )
    goto LABEL_8;
  if ( g_ParserCurrentTokenType != 101 )
    goto LABEL_7;
  Rules_DecrementIndentDepth(3);
  return v48;
}
// 4AA9D5: variable 'v4' is possibly undefined
// 4AA9EB: variable 'v6' is possibly undefined
// 4AAA03: variable 'v8' is possibly undefined
// 4AAA2A: variable 'v9' is possibly undefined
// 4AAA4D: variable 'v12' is possibly undefined
// 4AAA5C: variable 'v14' is possibly undefined
// 4AAA75: variable 'v16' is possibly undefined
// 4AAA84: variable 'v18' is possibly undefined
// 4AAA9D: variable 'v20' is possibly undefined
// 4AAAAC: variable 'v22' is possibly undefined
// 4AAABB: variable 'v24' is possibly undefined
// 4AAAEB: variable 'v26' is possibly undefined
// 4AAB1B: variable 'v27' is possibly undefined
// 4AAB3E: variable 'v28' is possibly undefined
// 4AAB43: variable 'v30' is possibly undefined
// 4AAB8A: variable 'v31' is possibly undefined
// 4AABDC: variable 'v36' is possibly undefined
// 4AABDC: variable 'v35' is possibly undefined
// 4AABF1: variable 'v37' is possibly undefined
// 4AABF6: variable 'v39' is possibly undefined
// 4AAC4F: variable 'v25' is possibly undefined
// 4AACA0: variable 'v41' is possibly undefined
// 4AACD3: variable 'v44' is possibly undefined
// 4AACD3: variable 'v45' is possibly undefined
// 4AAD08: variable 'v47' is possibly undefined
// 4AAD1A: variable 'v48' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;
// 54E904: using guessed type int dword_54E904;

//----- (004AAD30) --------------------------------------------------------
int  Rules_ParseObjectFunctionArgList(int readSource, _DWORD *errorFlag, int a3)
{
  int top; // edi
  int tail; // ebp
  signed int v7; // eax
  signed int valueListNode; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  signed int slotNameExpr; // [esp+0h] [ebp-18h]

  top = 0;
  tail = 0;
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      *errorFlag = 0;
      v7 = Parser_ParseArgument(readSource, errorFlag, a3);
      slotNameExpr = v7;
      if ( *errorFlag == 1 )
      {
        AST_Free(top);
        return 0;
      }
      if ( !v7 )
      {
        Parser_ReportSyntaxError();
        *errorFlag = 1;
        AST_Free(top);
        Lexer_ErrorRecover(1);
        return 0;
      }
      valueListNode = AST_NewNode(2, g_ClipsTrueSymbol);
      *(_DWORD *)(v9 + 10) = valueListNode;
      if ( !Parser_CollectFunctionArguments(valueListNode, readSource, v9) )
        break;
      if ( top )
        *(_DWORD *)(tail + 10) = v10;
      else
        top = v10;
      tail = *(_DWORD *)(slotNameExpr + 10);
      AST_Append(v10, (int)&g_ParserCurrentTokenType);
      Parser_NextToken(readSource, v11);
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_8;
    }
    *errorFlag = 1;
    AST_Free(top);
    return 0;
  }
  else
  {
LABEL_8:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
    return top;
  }
}
// 4AAD55: variable 'a3' is possibly undefined
// 4AAD7A: variable 'v9' is possibly undefined
// 4AAD92: variable 'v10' is possibly undefined
// 4AADA6: variable 'v11' is possibly undefined
// 54DD64: using guessed type int dword_54DD64;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E904: using guessed type int dword_54E904;

//----- (004AAE30) --------------------------------------------------------
int  Rules_ParseMakeInstanceNode(int topNode, int readSource)
{
  int override_head; // ebx
  int slot_override_parent; // edi
  int token_type; // edi
  int override_tail; // esi
  int value_node; // eax
  int create_symbol; // eax
  int trace_load_save; // eax

  trace_load_save = 0;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-enter\n");
  Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-token1=%d\n", g_ParserCurrentTokenType);
  override_head = 0;
  if ( g_ParserCurrentTokenType != 8 && g_ParserCurrentTokenType != 2 )
    goto MAKE_INSTANCE_ERROR;
  *(_DWORD *)(topNode + 6) = AST_NewNode(8, g_ClipsParserTokenValue);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-head-node\n");
  Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
  token_type = g_ParserCurrentTokenType;
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] parse-make-instance-token2=%d symbol=%s\n",
      token_type,
      g_ClipsParserTokenValue ? (const char *)*(_DWORD *)(g_ClipsParserTokenValue + 16) : "<null>");
  if ( token_type != 2 )
    goto MAKE_INSTANCE_ERROR;
  if ( strcmp_((int)aOf_0, *(_DWORD *)(g_ClipsParserTokenValue + 16)) )
    goto MAKE_INSTANCE_ERROR;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-of\n");
  Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] parse-make-instance-token3=%d symbol=%s\n",
      g_ParserCurrentTokenType,
      g_ClipsParserTokenValue ? (const char *)*(_DWORD *)(g_ClipsParserTokenValue + 16) : "<null>");
  if ( g_ParserCurrentTokenType != token_type )
    goto MAKE_INSTANCE_ERROR;
  *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10) = AST_NewNode(g_ParserCurrentTokenType, g_ClipsParserTokenValue);
  slot_override_parent = *(_DWORD *)(*(_DWORD *)(topNode + 6) + 10);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-before-class-lookup\n");
  if ( !Rules_ResolveClassNameNode(slot_override_parent) )
    goto MAKE_INSTANCE_ERROR;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-class-lookup\n");
  Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-token4=%d\n", g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType != 100 )
    goto CHECK_END_TOKEN;
  while ( 1 )
  {
    Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
    if ( g_ParserCurrentTokenType != 2 )
      goto SLOT_OVERRIDE_ERROR;
    *(_DWORD *)(slot_override_parent + 10) = AST_NewNode(2, g_ClipsParserTokenValue);
    *(_DWORD *)(*(_DWORD *)(slot_override_parent + 10) + 10) = AST_NewNode(2, g_ClipsTrueSymbol);
    slot_override_parent = *(_DWORD *)(*(_DWORD *)(slot_override_parent + 10) + 10);
    Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
    override_tail = 0;
    while ( g_ParserCurrentTokenType != 101 )
    {
      if ( g_ParserCurrentTokenType == 100 )
      {
        Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType != 2 )
          goto SLOT_OVERRIDE_ERROR;
        if ( strcmp_(*(_DWORD *)(g_ClipsParserTokenValue + 16), (int)aCreate_0) )
          goto SLOT_OVERRIDE_ERROR;
        Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType != 101 )
          goto SLOT_OVERRIDE_ERROR;
        create_symbol = (int)Rules_MakeSymbol(aCreate_0);
        value_node = AST_NewNode(10, create_symbol);
      }
      else
      {
        if ( g_ParserCurrentTokenType != 2
          && g_ParserCurrentTokenType != 3
          && g_ParserCurrentTokenType != 0
          && g_ParserCurrentTokenType != 1
          && g_ParserCurrentTokenType != 8 )
        {
          goto SLOT_OVERRIDE_ERROR;
        }
        value_node = AST_NewNode(g_ParserCurrentTokenType, g_ClipsParserTokenValue);
      }
      if ( override_head )
        *(_DWORD *)(override_tail + 10) = value_node;
      else
        override_head = value_node;
      override_tail = value_node;
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
    }
    *(_DWORD *)(slot_override_parent + 6) = override_head;
    Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
    override_head = 0;
    if ( g_ParserCurrentTokenType != 100 )
      break;
  }
CHECK_END_TOKEN:
  if ( g_ParserCurrentTokenType == 101 )
    return topNode;
SLOT_OVERRIDE_ERROR:
  Parser_ReportSyntaxError();
  Lexer_ErrorRecover(1);
  AST_Free(topNode);
  AST_Free(override_head);
  return 0;
MAKE_INSTANCE_ERROR:
  Parser_ReportSyntaxError();
  Lexer_ErrorRecover(1);
  AST_Free(topNode);
  return 0;
}
// 4AB03F: simplified comparisons for '$dword_54E8FC.4': ==0 || ==1 became <2u
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DD64: using guessed type int dword_54DD64;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004AB0B0) --------------------------------------------------------
signed int  Rules_ResolveClassNameNode(int theExpression)
{
  int class_name; // edx
  int *class_record; // ebx
  int trace_load_save; // eax

  if ( *(_WORD *)theExpression != 2 )
    return 1;
  class_name = *(_DWORD *)(*(_DWORD *)(theExpression + 2) + 16);
  trace_load_save = 0;
  class_record = Class_LookupInScope((_BYTE *)class_name);
  if ( class_record )
  {
    if ( Class_IsAbstract((int)class_record) )
    {
      if ( trace_load_save )
        fprintf(
          stderr,
          "[menu-probe] class-lookup-cannot-create name=%s class=%p\n",
          class_name ? (const char *)(uintptr_t)(unsigned int)class_name : "<null>",
          (void *)(uintptr_t)(unsigned int)class_record);
      Rules_PrintErrorID((int)aInsmngr_0, 3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotCreateIn, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], class_name, class_name);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__7, 0);
      return 0;
    }
    *(_WORD *)theExpression = 57;
    *(_DWORD *)(theExpression + 2) = class_record;
    return 1;
  }
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] class-lookup-failed name=%s\n",
      class_name ? (const char *)(uintptr_t)(unsigned int)class_name : "<null>");
  Rules_ReportCantFindItem((int)aClass, class_name);
  return 0;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004AB150) --------------------------------------------------------
signed int Instance_RegisterModifyAndDuplicateFunctions()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx

  Rules_RegisterHostFunction(aModifyInstance, 117, (int)aInactivemodify, (int)Instance_ModifyInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveModifyIn, 117, (int)aModifyinstance, (int)Instance_ActiveModifyInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveModifyIn);
  Rules_RegisterHostFunction(aMessageModifyI, 117, v0, (int)Instance_MessageModifyInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveMessageM, 117, (int)aMsgmodifyinsta, (int)Instance_ActiveMessageModifyInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveMessageM);
  Rules_RegisterHostFunction(aDuplicateInsta, 117, v1, (int)Instance_DuplicateInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveDuplicat, 117, (int)aDuplicateinsta, (int)Instance_ActiveDuplicateInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveDuplicat);
  Rules_RegisterHostFunction(aMessageDuplica, 117, v2, (int)Instance_MessageDuplicateInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveMessageD, 117, (int)aMsgduplicatein, (int)Instance_ActiveMessageDuplicateInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveMessageD);
  Rules_RegisterHostFunction(aDirectModify, 117, v3, (int)Instance_DirectModifyFunction, 0);
  Rules_RegisterHostFunction(aMessageModify, 117, (int)aMsgmodifymsgha, (int)Instance_MessageModifyFunction, 0);
  Rules_RegisterHostFunction(aDirectDuplicat, 117, (int)aDirectduplicat, (int)Instance_DirectDuplicateFunction, 0);
  Rules_RegisterHostFunction(aMessageDupli_0, 117, (int)aMsgduplicatems, (int)Instance_MessageDuplicateFunction, 0);
  Rules_AddFunctionParser(aModifyInstance);
  Rules_AddFunctionParser(aMessageModifyI);
  Rules_AddFunctionParser(aDuplicateInsta);
  return Rules_AddFunctionParser(aMessageDuplica);
}
// 4AB1AE: variable 'v0' is possibly undefined
// 4AB1F3: variable 'v1' is possibly undefined
// 4AB238: variable 'v2' is possibly undefined
// 4AB27D: variable 'v3' is possibly undefined

//----- (004AB320) --------------------------------------------------------
_DWORD * Instance_ActiveModifyInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int savedGuardState; // ebp
  int *messageSymbol; // eax
  int v8; // edx
  int v9; // ecx
  int overrideCount; // [esp+10h] [ebp-1Ch] BYREF
  _DWORD errorFlag[6]; // [esp+14h] [ebp-18h] BYREF

  overrides = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) )
    {
      savedGuardState = g_InstanceDirectMessageGuardActive;
      g_InstanceDirectMessageGuardActive = 1;
      messageSymbol = Rules_FindSymbolEntry(aDirectModify_0);
      MessageHandler_SendToInstanceAddress((int)messageSymbol, v8, v9, returnValue, a2);
      g_InstanceDirectMessageGuardActive = savedGuardState;
    }
    else
    {
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
    }
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB371: variable 'v3' is possibly undefined
// 4AB3D8: variable 'v8' is possibly undefined
// 4AB3D8: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB400) --------------------------------------------------------
_DWORD * Instance_ActiveMessageModifyInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int savedGuardState; // ebp
  int *messageSymbol; // eax
  int v8; // edx
  int v9; // ecx
  int overrideCount; // [esp+10h] [ebp-1Ch] BYREF
  _DWORD errorFlag[6]; // [esp+14h] [ebp-18h] BYREF

  overrides = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) )
    {
      savedGuardState = g_InstanceDirectMessageGuardActive;
      g_InstanceDirectMessageGuardActive = 1;
      messageSymbol = Rules_FindSymbolEntry(aMessageModif_1);
      MessageHandler_SendToInstanceAddress((int)messageSymbol, v8, v9, returnValue, a2);
      g_InstanceDirectMessageGuardActive = savedGuardState;
    }
    else
    {
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
    }
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB451: variable 'v3' is possibly undefined
// 4AB4B8: variable 'v8' is possibly undefined
// 4AB4B8: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB4E0) --------------------------------------------------------
_DWORD * Instance_ActiveDuplicateInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int *messageSymbol; // eax
  int v7; // edx
  int v8; // ecx
  int newNameValue; // [esp+1Ch] [ebp-3Ch] BYREF
  int savedGuardState; // [esp+34h] [ebp-24h]
  int overrideCount; // [esp+38h] [ebp-20h] BYREF
  _DWORD errorFlag[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  overrides = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) && Lexer_ParseValueList(2, &newNameValue, 8, a2) )
  {
    savedGuardState = g_InstanceDirectMessageGuardActive;
    g_InstanceDirectMessageGuardActive = 1;
    messageSymbol = Rules_FindSymbolEntry(aDirectDuplic_0);
    MessageHandler_SendToInstanceAddress((int)messageSymbol, v7, v8, returnValue, a2);
    g_InstanceDirectMessageGuardActive = savedGuardState;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB536: variable 'v3' is possibly undefined
// 4AB5E2: variable 'v7' is possibly undefined
// 4AB5E2: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB610) --------------------------------------------------------
_DWORD * Instance_ActiveMessageDuplicateInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int *messageSymbol; // eax
  int v7; // edx
  int v8; // ecx
  int newNameValue; // [esp+1Ch] [ebp-3Ch] BYREF
  int savedGuardState; // [esp+34h] [ebp-24h]
  int overrideCount; // [esp+38h] [ebp-20h] BYREF
  _DWORD errorFlag[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  overrides = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) && Lexer_ParseValueList(2, &newNameValue, 8, a2) )
  {
    savedGuardState = g_InstanceDirectMessageGuardActive;
    g_InstanceDirectMessageGuardActive = 1;
    messageSymbol = Rules_FindSymbolEntry(aMessageDupli_1);
    MessageHandler_SendToInstanceAddress((int)messageSymbol, v7, v8, returnValue, a2);
    g_InstanceDirectMessageGuardActive = savedGuardState;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB666: variable 'v3' is possibly undefined
// 4AB712: variable 'v7' is possibly undefined
// 4AB712: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB740) --------------------------------------------------------
int  Instance_ModifyInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveModifyInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB752: variable 'v1' is possibly undefined
// 4AB752: variable 'v2' is possibly undefined
// 4AB759: variable 'v3' is possibly undefined

//----- (004AB770) --------------------------------------------------------
int  Instance_MessageModifyInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveMessageModifyInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB782: variable 'v1' is possibly undefined
// 4AB782: variable 'v2' is possibly undefined
// 4AB789: variable 'v3' is possibly undefined

//----- (004AB7A0) --------------------------------------------------------
int  Instance_DuplicateInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveDuplicateInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB7B2: variable 'v1' is possibly undefined
// 4AB7B2: variable 'v2' is possibly undefined
// 4AB7B9: variable 'v3' is possibly undefined

//----- (004AB7D0) --------------------------------------------------------
int  Instance_MessageDuplicateInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveMessageDuplicateInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB7E2: variable 'v1' is possibly undefined
// 4AB7E2: variable 'v2' is possibly undefined
// 4AB7E9: variable 'v3' is possibly undefined

//----- (004AB800) --------------------------------------------------------
_DWORD * Instance_DirectDuplicateFunction(int *returnValue, double a2)
{
  return Rules_DuplicateInstanceCore(returnValue, 0, a2);
}

//----- (004AB810) --------------------------------------------------------
_DWORD * Instance_MessageDuplicateFunction(int *returnValue, double a2)
{
  return Rules_DuplicateInstanceCore(returnValue, 1, a2);
}

//----- (004AB820) --------------------------------------------------------
_DWORD * Instance_DirectModifyFunction(int returnValue, double a2)
{
  return Rules_ModifyInstanceCore(returnValue, 0, a2);
}

//----- (004AB830) --------------------------------------------------------
_DWORD * Instance_MessageModifyFunction(int returnValue, double a2)
{
  return Rules_ModifyInstanceCore(returnValue, 1, a2);
}

//----- (004AB840) --------------------------------------------------------
int  Instance_ParseSlotOverrideArgs(int overrideExprs, _DWORD *overrideCount, _DWORD *errorFlag, double a4)
{
  int exprCursor; // esi
  int result; // eax
  int overrideIndex; // edi
  _DWORD *v7; // eax
  _DWORD *overrideCursor; // ecx
  _DWORD *v9; // ecx
  _DWORD *v10; // ecx
  _DWORD *v11; // eax
  _DWORD *overrideArray; // [esp+8h] [ebp-18h]
  int slotNameSymbol; // [esp+Ch] [ebp-14h]

  exprCursor = overrideExprs;
  *errorFlag = 0;
  result = AST_CountListNodes(overrideExprs) / 2;
  *overrideCount = result;
  if ( result )
  {
    overrideIndex = 0;
    v7 = Mem_SmallBlockAlloc(24 * result);
    overrideArray = v7;
    if ( exprCursor )
    {
      overrideCursor = v7;
      while ( !Parser_ParseForm((__int16 *)exprCursor, overrideCursor, (int)overrideCursor, a4) )
      {
        if ( v9[1] != 2 )
        {
          Parser_ReportError(overrideIndex + 1, (int)aSlotName);
          Lexer_ErrorRecover(1);
          break;
        }
        slotNameSymbol = v9[2];
        if ( !Parser_ParseSlotDefaultOrRestriction(0, *(_DWORD *)(*(_DWORD *)(exprCursor + 10) + 6), v9, a4) )
          break;
        *v10 = slotNameSymbol;
        exprCursor = *(_DWORD *)(*(_DWORD *)(exprCursor + 10) + 10);
        if ( exprCursor )
          v11 = &overrideArray[6 * overrideIndex + 6];
        else
          v11 = 0;
        overrideCursor = v10 + 6;
        ++overrideIndex;
        *(overrideCursor - 1) = v11;
        if ( !exprCursor )
          return (int)overrideArray;
      }
      Mem_SmallBlockFree(overrideArray, 24 * *overrideCount);
      *errorFlag = 1;
      return 0;
    }
    else
    {
      return (int)overrideArray;
    }
  }
  return result;
}
// 4AB8AA: variable 'v9' is possibly undefined
// 4AB928: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004AB960) --------------------------------------------------------
_DWORD * Instance_FreeSlotOverrideArgs(_DWORD *result, int overrideCount)
{
  if ( result )
    return (_DWORD *)Mem_SmallBlockFree(result, 24 * overrideCount);
  return result;
}

//----- (004AB990) --------------------------------------------------------
_DWORD * Rules_ModifyInstanceCore(int returnValue, int msgpass, double a3)
{
  int theInstance; // edi
  int slotOverride; // esi
  int v6; // eax
  int v7; // ecx
  int *theSlot; // edx
  _DWORD *result; // eax
  bool putFailed; // zf
  int v11; // ecx
  int *putValue; // eax
  int sendResult; // [esp+0h] [ebp-40h] BYREF
  int sendResultType; // [esp+4h] [ebp-3Ch]
  _DWORD *sendResultValue; // [esp+8h] [ebp-38h]
  int v16; // [esp+Ch] [ebp-34h]
  int v17; // [esp+10h] [ebp-30h]
  __int16 tmpExprType; // [esp+18h] [ebp-28h] BYREF
  int tmpExprValue; // [esp+1Ah] [ebp-26h]
  int tmpExprArgList; // [esp+1Eh] [ebp-22h]
  int tmpExprNext; // [esp+22h] [ebp-1Eh]
  int v22; // [esp+28h] [ebp-18h]

  v22 = returnValue;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(v22 + 8) = g_ClipsFalseSymbol;
  if ( !g_InstanceDirectMessageGuardActive )
  {
    Rules_PrintErrorID((int)aInsmoddp, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDirectMessageM, v11);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  g_InstanceDirectMessageGuardActive = 0;
  theInstance = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
  if ( (*(_BYTE *)(theInstance + 24) & 2) != 0 )
  {
    Instance_ReportInvalidInstanceAddressError();
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  slotOverride = *(_DWORD *)(MessageHandler_GetNthArgument(1) + 8);
  *(_DWORD *)(v22 + 4) = 2;
  *(_DWORD *)(v22 + 8) = g_ClipsFalseSymbol;
  if ( slotOverride )
  {
    while ( 1 )
    {
      v6 = Instance_GetSlotValueBySymbol(theInstance, *(_DWORD *)slotOverride);
      theSlot = (int *)v6;
      if ( !v6 )
      {
        Instance_ReportNoSuchSlotError(v7, (int)aModifyInstance);
        return (_DWORD *)Lexer_ErrorRecover(1);
      }
      if ( !msgpass )
        break;
      tmpExprType = *(_WORD *)(slotOverride + 4);
      if ( tmpExprType == 4 )
        tmpExprValue = slotOverride;
      else
        tmpExprValue = *(_DWORD *)(slotOverride + 8);
      tmpExprArgList = 0;
      tmpExprNext = 0;
      result = (_DWORD *)MessageHandler_SendToInstanceAddress(*(_DWORD *)(*(_DWORD *)v6 + 12), theInstance, (int)&tmpExprType, &sendResult, a3);
      if ( g_ClipsEvaluationError )
        return result;
      if ( sendResultType == 2 )
      {
        result = sendResultValue;
        putFailed = sendResultValue == (_DWORD *)g_ClipsFalseSymbol;
        goto LABEL_11;
      }
LABEL_12:
      slotOverride = *(_DWORD *)(slotOverride + 20);
      if ( !slotOverride )
        goto LABEL_13;
    }
    if ( (**(_BYTE **)v6 & 2) == 0 || *(_DWORD *)(slotOverride + 4) == 4 )
    {
      putValue = (int *)slotOverride;
    }
    else
    {
      sendResultType = 4;
      sendResultValue = Rules_CreateEphemeralMultifield(1);
      v16 = 0;
      v17 = 0;
      *((_WORD *)sendResultValue + 7) = *(_WORD *)(slotOverride + 4);
      sendResultValue[4] = *(_DWORD *)(slotOverride + 8);
      putValue = &sendResult;
    }
    result = (_DWORD *)Instance_PutSlotValue((_DWORD *)theInstance, theSlot, putValue, a3);
    putFailed = result == 0;
LABEL_11:
    if ( putFailed )
      return result;
    goto LABEL_12;
  }
LABEL_13:
  result = (_DWORD *)g_ClipsTrueSymbol;
  *(_DWORD *)(v22 + 8) = g_ClipsTrueSymbol;
  return result;
}
// 4ABAAA: variable 'v11' is possibly undefined
// 4ABAE9: variable 'v7' is possibly undefined
// 4ABB52: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ABB70) --------------------------------------------------------
_DWORD * Rules_DuplicateInstanceCore(int *returnValue, int msgpass, double a3)
{
  int srcInstance; // ebp
  int newNameSymbol; // ecx
  int slotOverride; // edi
  _DWORD *result; // eax
  int dupInstance; // esi
  int *v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  bool putFailed; // zf
  int v13; // ecx
  int localSlotOffset; // edi
  int *putValue; // eax
  _DWORD *srcSlotValue; // eax
  unsigned int slotIndex; // edx
  int slotTableOffset; // eax
  int v19; // ecx
  char v20; // bh
  int v21; // edx
  int sendResult; // [esp+0h] [ebp-54h] BYREF
  int sendResultType; // [esp+4h] [ebp-50h]
  _DWORD *sendResultValue; // [esp+8h] [ebp-4Ch]
  int v25; // [esp+Ch] [ebp-48h]
  int v26; // [esp+10h] [ebp-44h]
  __int16 v27; // [esp+18h] [ebp-3Ch] BYREF
  int v28; // [esp+1Ah] [ebp-3Ah]
  int v29; // [esp+1Eh] [ebp-36h]
  int v30; // [esp+22h] [ebp-32h]
  int v31; // [esp+28h] [ebp-2Ch]
  int savedFlag; // [esp+2Ch] [ebp-28h]
  int initExpr; // [esp+30h] [ebp-24h]
  int *v34; // [esp+34h] [ebp-20h]
  unsigned int localSlotIndex; // [esp+38h] [ebp-1Ch]
  int *theSlot; // [esp+3Ch] [ebp-18h]

  v34 = returnValue;
  v31 = msgpass;
  returnValue[1] = 2;
  v34[2] = g_ClipsFalseSymbol;
  if ( !g_InstanceDirectMessageGuardActive )
  {
    Rules_PrintErrorID((int)aInsmoddp, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDirectMessageD, v10);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  g_InstanceDirectMessageGuardActive = 0;
  srcInstance = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
  MessageHandler_GetNthArgument(1);
  slotOverride = *(_DWORD *)(MessageHandler_GetNthArgument(2) + 8);
  if ( (*(_BYTE *)(srcInstance + 24) & 2) != 0 )
  {
    Instance_ReportInvalidInstanceAddressError();
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  if ( newNameSymbol == *(_DWORD *)(srcInstance + 28) )
  {
    Rules_PrintErrorID((int)aInsmoddp, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstanceCopyMu, v11);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  savedFlag = g_Instance_UseMessageDispatchForInit;
  g_Instance_UseMessageDispatchForInit = v31;
  result = Instance_BuildInstance(newNameSymbol, *(_DWORD *)(srcInstance + 44), 1, a3);
  dupInstance = (int)result;
  g_Instance_UseMessageDispatchForInit = savedFlag;
  if ( result )
  {
    ++result[10];
    if ( slotOverride )
    {
      while ( 1 )
      {
        v8 = (int *)Instance_GetSlotValueBySymbol(dupInstance, *(_DWORD *)slotOverride);
        theSlot = v8;
        if ( !v8 )
        {
          Instance_ReportNoSuchSlotError(v9, (int)aDuplicateInsta);
LABEL_8:
          --*(_DWORD *)(dupInstance + 40);
          Instance_DeleteInstance(dupInstance, a3);
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        if ( !v31 )
          break;
        v27 = *(_WORD *)(slotOverride + 4);
        if ( v27 == 4 )
          v28 = slotOverride;
        else
          v28 = *(_DWORD *)(slotOverride + 8);
        v29 = 0;
        v30 = 0;
        MessageHandler_SendToInstanceAddress(*(_DWORD *)(*theSlot + 12), dupInstance, (int)&v27, &sendResult, a3);
        if ( g_ClipsEvaluationError )
          goto LABEL_8;
        if ( sendResultType == 2 )
        {
          putFailed = sendResultValue == (_DWORD *)g_ClipsFalseSymbol;
          goto LABEL_19;
        }
LABEL_20:
        *((_BYTE *)theSlot + 4) |= 2u;
        slotOverride = *(_DWORD *)(slotOverride + 20);
        if ( !slotOverride )
          goto LABEL_21;
      }
      if ( (*(_BYTE *)*v8 & 2) == 0 || *(_DWORD *)(slotOverride + 4) == 4 )
      {
        putValue = (int *)slotOverride;
      }
      else
      {
        sendResultType = 4;
        sendResultValue = Rules_CreateEphemeralMultifield(1);
        v25 = 0;
        v26 = 0;
        *((_WORD *)sendResultValue + 7) = *(_WORD *)(slotOverride + 4);
        sendResultValue[4] = *(_DWORD *)(slotOverride + 8);
        putValue = &sendResult;
      }
      putFailed = Instance_PutSlotValue((_DWORD *)dupInstance, theSlot, putValue, a3) == 0;
LABEL_19:
      if ( putFailed )
        goto LABEL_8;
      goto LABEL_20;
    }
LABEL_21:
    v13 = 0;
    localSlotOffset = 0;
    localSlotIndex = 0;
    while ( 1 )
    {
      if ( localSlotIndex >= *(_DWORD *)(*(_DWORD *)(dupInstance + 44) + 68) )
      {
        if ( v31 )
        {
          slotIndex = 0;
          slotTableOffset = 0;
          while ( slotIndex < *(_DWORD *)(*(_DWORD *)(dupInstance + 44) + 72) )
          {
            v19 = *(_DWORD *)(*(_DWORD *)(dupInstance + 72) + slotTableOffset);
            slotTableOffset += 4;
            ++slotIndex;
            *(_BYTE *)(v19 + 4) |= 2u;
          }
          *(_BYTE *)(dupInstance + 24) |= 4u;
          savedFlag = g_Instance_SlotInitInProgress;
          g_Instance_SlotInitInProgress = 1;
          MessageHandler_SendToInstanceAddress(g_MessageHandler_InitSymbol, dupInstance, 0, v34, a3);
          g_Instance_SlotInitInProgress = savedFlag;
        }
        v20 = *(_BYTE *)(dupInstance + 24);
        --*(_DWORD *)(dupInstance + 40);
        if ( (v20 & 2) != 0 )
        {
          v34[1] = 2;
          v34[2] = g_ClipsFalseSymbol;
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        else
        {
          v34[1] = 8;
          result = Instance_GetQualifiedName(dupInstance, v13);
          *(_DWORD *)(v21 + 8) = result;
        }
        return result;
      }
      if ( (*(_BYTE *)(localSlotOffset + *(_DWORD *)(dupInstance + 76) + 4) & 2) != 0 )
      {
LABEL_24:
        localSlotOffset += 12;
        ++localSlotIndex;
      }
      else if ( v31 )
      {
        sendResultType = *(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 4) << 24 >> 26;
        srcSlotValue = *(_DWORD **)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 8);
        sendResultValue = srcSlotValue;
        if ( sendResultType == 4 )
        {
          v25 = 0;
          v26 = *(_DWORD *)((char *)srcSlotValue + 6) - 1;
        }
        initExpr = AST_BuildExpressionFromValue(&sendResult);
        MessageHandler_SendToInstanceAddress(*(_DWORD *)(*(_DWORD *)(localSlotOffset + *(_DWORD *)(dupInstance + 76)) + 12), dupInstance, initExpr, &sendResult, a3);
        AST_Free(initExpr);
        if ( g_ClipsEvaluationError )
          goto LABEL_8;
        if ( sendResultType != 2 )
          goto LABEL_24;
        if ( sendResultValue == (_DWORD *)g_ClipsFalseSymbol )
          goto LABEL_8;
        localSlotOffset += 12;
        ++localSlotIndex;
      }
      else
      {
        sendResultType = *(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 4) << 24 >> 26;
        sendResultValue = *(_DWORD **)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 8);
        if ( (*(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 4) & 0xFC) == 0x10 )
        {
          v25 = 0;
          v26 = *(_DWORD *)(*(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 8) + 6) - 1;
        }
        if ( !Instance_PutSlotValue((_DWORD *)dupInstance, (int *)(localSlotOffset + *(_DWORD *)(dupInstance + 76)), &sendResult, a3) )
          goto LABEL_8;
        localSlotOffset += 12;
        ++localSlotIndex;
      }
    }
  }
  return result;
}
// 4ABBD9: variable 'v4' is possibly undefined
// 4ABC3A: variable 'v9' is possibly undefined
// 4ABC7B: variable 'v10' is possibly undefined
// 4ABCCB: variable 'v11' is possibly undefined
// 4ABFB3: variable 'v13' is possibly undefined
// 4ABFB8: variable 'v21' is possibly undefined
// 51A27C: using guessed type int dword_51A27C;
// 51A284: using guessed type int dword_51A284;
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51AD1C: using guessed type int dword_51AD1C;
// 51AD34: using guessed type int dword_51AD34;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ABFD0) --------------------------------------------------------
signed int Rules_RegisterInstanceIOCommands()
{
  Rules_RegisterHostFunction(aSaveInstances, 108, (int)aSaveinstancesc, (int)Rules_SaveInstancesCommand, (int)a1Wk_0);
  Rules_RegisterHostFunction(aLoadInstances, 108, (int)aLoadinstancesc, (int)Rules_LoadInstancesCommand, (int)a11k_3);
  Rules_RegisterHostFunction(aRestoreInstanc, 108, (int)aRestoreinstanc, (int)Rules_RestoreInstancesCommand, (int)a11k_3);
  Rules_RegisterHostFunction(aBsaveInstances, 108, (int)aBinarysaveinst, (int)Rules_BsaveInstancesCommand, (int)a1Wk_0);
  return Rules_RegisterHostFunction(aBloadInstances, 108, (int)aBinaryloadinst, (int)Rules_BloadInstancesCommand, (int)a11k_3);
}

//----- (004AC070) --------------------------------------------------------
signed int  Rules_SaveInstancesCommand(double a1)
{
  return Rules_ParseSaveInstancesArgsAndDispatch((int (*)(void))Rules_SaveInstancesTextFile, a1);
}

//----- (004AC090) --------------------------------------------------------
signed int  Rules_LoadInstancesCommand(int a1, DWORD a2, double a3)
{
  signed int result; // eax
  int v4; // ecx
  signed int instancesLoaded; // ebx
  int fileArgValue; // [esp-8h] [ebp-24h] BYREF
  int fileNameSymbol; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, &fileArgValue, 111, a3);
  if ( result )
  {
    instancesLoaded = Rules_ReadInstancesTextFile(*(const CHAR **)(fileNameSymbol + 16), 1, *(_DWORD *)(fileNameSymbol + 16), a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v4, v4);
    return instancesLoaded;
  }
  return result;
}
// 4AC0DD: variable 'v4' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC100) --------------------------------------------------------
signed int  Rules_RestoreInstancesCommand(int a1, DWORD a2, double a3)
{
  signed int result; // eax
  int v4; // ecx
  signed int instancesLoaded; // ebx
  int fileArgValue; // [esp-8h] [ebp-24h] BYREF
  int fileNameSymbol; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, &fileArgValue, 111, a3);
  if ( result )
  {
    instancesLoaded = Rules_ReadInstancesTextFile(*(const CHAR **)(fileNameSymbol + 16), 0, *(_DWORD *)(fileNameSymbol + 16), a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v4, v4);
    return instancesLoaded;
  }
  return result;
}
// 4AC14A: variable 'v4' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC170) --------------------------------------------------------
signed int  Rules_BloadInstancesCommand(int a1, DWORD a2, double a3)
{
  signed int result; // eax
  int v4; // ecx
  int v5; // edx
  signed int instancesLoaded; // ecx
  _DWORD argBuffer[9]; // [esp-8h] [ebp-24h] BYREF

  argBuffer[7] = a1;
  result = Lexer_ParseValueList(1, argBuffer, 111, a3);
  if ( result )
  {
    instancesLoaded = Rules_BloadInstancesFile(*(const CHAR **)(argBuffer[2] + 16), v4, a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(instancesLoaded, v5);
    return instancesLoaded;
  }
  return result;
}
// 4AC1A0: variable 'v4' is possibly undefined
// 4AC1B6: variable 'v5' is possibly undefined
// 4AC1BB: variable 'v6' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC1D0) --------------------------------------------------------
signed int  Rules_BloadInstancesFile(const CHAR *fileName, int a2, DWORD a3, double a4)
{
  int v5; // ecx
  void *v6; // ecx
  int instanceCount; // ecx
  int v8; // edx
  void *v9; // ecx
  void *v11; // ecx
  int v12; // edx
  _DWORD instanceCountBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  instanceCountBuffer[2] = a2;
  if ( Rules_BloadOpenFile(fileName, a3) )
  {
    if ( Rules_ValidateBloadInstancesHeader(v5, v5) )
    {
      Rules_BloadAtomTables();
      g_Rules_BloadBytesConsumed = 0;
      Rules_BloadReadBlock((uintptr_t)&g_ClipsBsaveInstanceDataSpace, 4u);
      Rules_BloadReadBlock((uintptr_t)instanceCountBuffer, 4u);
      instanceCount = instanceCountBuffer[0];
      if ( instanceCountBuffer[0] <= 0 )
      {
LABEL_6:
        Rules_BloadReleaseReadBuffer();
        Rules_FreeBloadAtomTables();
        Rules_BloadCloseFile(v9);
        return instanceCountBuffer[0];
      }
      else
      {
        while ( Rules_BloadReadInstanceRecord(instanceCount, a4) )
        {
          if ( v8 + 1 >= instanceCountBuffer[0] )
            goto LABEL_6;
        }
        Rules_BloadReleaseReadBuffer();
        Rules_FreeBloadAtomTables();
        Rules_BloadCloseFile(v11);
        Lexer_ErrorRecover(1);
        return v12;
      }
    }
    else
    {
      Rules_BloadCloseFile(v6);
      Lexer_ErrorRecover(1);
      return -1;
    }
  }
  else
  {
    Lexer_ErrorRecover(1);
    return -1;
  }
}
// 4AC1EA: variable 'v5' is possibly undefined
// 4AC224: variable 'v7' is possibly undefined
// 4AC230: variable 'v8' is possibly undefined
// 4AC23F: variable 'v9' is possibly undefined
// 4AC25F: variable 'v6' is possibly undefined
// 4AC27F: variable 'v11' is possibly undefined
// 4AC28E: variable 'v12' is possibly undefined
// 54E6EC: using guessed type int dword_54E6EC;
// 54E6F0: using guessed type int dword_54E6F0;

//----- (004AC2A0) --------------------------------------------------------
_DWORD * Rules_SaveInstancesTextFile(const CHAR *fileName, int saveCode, DWORD inheritFlag, int classExpressionList, double a5)
{
  _DWORD *result; // eax
  _DWORD *classList; // edi
  int v8; // ecx
  int filePtr; // eax
  int v10; // ecx
  int v11; // ecx
  int instanceCount; // ebp
  int v13; // ecx
  int savedPreserveEscapes; // [esp+0h] [ebp-24h]
  int savedAddressesToStrings; // [esp+4h] [ebp-20h]
  int savedInstancesToNames; // [esp+8h] [ebp-1Ch]

  result = Rules_BuildClassListForSave((int)aSaveInstances, classExpressionList, inheritFlag, saveCode, a5);
  classList = result;
  if ( result || !classExpressionList )
  {
    Rules_ForEachInstanceForSave(saveCode, inheritFlag, (int)result, 1, 0);
    filePtr = IO_FOpen(fileName, (unsigned __int8 *)aW_5, v8, inheritFlag);
    if ( filePtr )
    {
      savedPreserveEscapes = g_Print_PreserveEscapedCharactersFlag;
      g_Print_PreserveEscapedCharactersFlag = 1;
      savedAddressesToStrings = g_Print_AddressesToStringsFlag;
      g_Print_AddressesToStringsFlag = 1;
      savedInstancesToNames = g_Print_InstanceAddressesToNamesFlag;
      g_Print_InstanceAddressesToNamesFlag = 1;
      IO_SetFastSaveFile(filePtr);
      instanceCount = Rules_ForEachInstanceForSave(saveCode, inheritFlag, (int)classList, v11, (void (__fastcall *)(int, int))Rules_WriteInstanceTextRecord);
      fclose_(v13);
      IO_SetFastSaveFile(0);
      g_Print_PreserveEscapedCharactersFlag = savedPreserveEscapes;
      g_Print_AddressesToStringsFlag = savedAddressesToStrings;
      g_Print_InstanceAddressesToNamesFlag = savedInstancesToNames;
      Rules_FreeClassList(classList);
      return (_DWORD *)instanceCount;
    }
    else
    {
      Rules_OpenFileErrorMessage(v10, (int)fileName);
      Rules_FreeClassList(classList);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}
// 4AC2F7: variable 'v8' is possibly undefined
// 4AC30B: variable 'v10' is possibly undefined
// 4AC372: variable 'v11' is possibly undefined
// 4AC37B: variable 'v13' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A5F8: using guessed type int dword_51A5F8;
// 51A5FC: using guessed type int dword_51A5FC;
// 51A600: using guessed type int dword_51A600;

//----- (004AC3C0) --------------------------------------------------------
signed int  Rules_BsaveInstancesCommand(double a1)
{
  return Rules_ParseSaveInstancesArgsAndDispatch((int (*)(void))Rules_SaveInstancesBinaryFile, a1);
}

//----- (004AC3E0) --------------------------------------------------------
_DWORD * Rules_SaveInstancesBinaryFile(const CHAR *fileName, int saveCode, DWORD a3, int classExpressionList, double a5)
{
  _DWORD *result; // eax
  _DWORD *classList; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int fp; // esi
  int v13; // edx
  int v14; // ecx
  int instancesSaved; // [esp+0h] [ebp-18h] BYREF
  const CHAR *v16; // [esp+4h] [ebp-14h]
  int v17; // [esp+8h] [ebp-10h]

  v16 = fileName;
  v17 = saveCode;
  result = Rules_BuildClassListForSave((int)aBsaveInstances, classExpressionList, a3, saveCode, a5);
  classList = result;
  if ( result || !classExpressionList )
  {
    g_ClipsBsaveInstanceDataSpace = 0;
    Rules_ClearAtomInUseMarks();
    instancesSaved = Rules_ForEachInstanceForSave(v17, a3, (int)classList, v8, Compiler_MarkAndEmit);
    v10 = IO_FOpen(v16, (unsigned __int8 *)aWb_5, v9, a3);
    fp = v10;
    if ( v10 )
    {
      Compiler_WriteHeaders(v10);
      Rules_BsaveAtomTables(fp);
      fwrite_(&g_ClipsBsaveInstanceDataSpace, v13, fp, 1);
      fwrite_(&instancesSaved, 4, fp, 1);
      Rules_SetAtomicValueIndices(0);
      Rules_ForEachInstanceForSave(v17, a3, (int)classList, 0, (void (__fastcall *)(int, int))Compiler_WriteInstanceRecord);
      Rules_RestoreAtomicValueBuckets();
      fclose_(v14);
      Rules_FreeClassList(classList);
      return (_DWORD *)instancesSaved;
    }
    else
    {
      Rules_OpenFileErrorMessage(v11, (int)v16);
      Rules_FreeClassList(classList);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}
// 4AC42E: variable 'v8' is possibly undefined
// 4AC43F: variable 'v9' is possibly undefined
// 4AC453: variable 'v11' is possibly undefined
// 4AC48F: variable 'v13' is possibly undefined
// 4AC4CB: variable 'v14' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E6EC: using guessed type int dword_54E6EC;

//----- (004AC4F0) --------------------------------------------------------
signed int  Rules_ParseSaveInstancesArgsAndDispatch(int (*saveFunction)(void), double a2)
{
  int saveCode; // ebp
  signed int result; // eax
  int v4; // ecx
  int v5; // ecx
  int classExpr; // edi
  _DWORD argBuffer[7]; // [esp+0h] [ebp-38h] BYREF
  int (*v8)(void); // [esp+1Ch] [ebp-1Ch]
  int inheritFlag; // [esp+20h] [ebp-18h]

  v8 = saveFunction;
  saveCode = 1;
  inheritFlag = 0;
  result = Lexer_ParseValueList(1, argBuffer, 111, a2);
  if ( result )
  {
    argBuffer[6] = *(_DWORD *)(argBuffer[2] + 16);
    if ( Rules_RtnArgCount() <= 1 )
      return ((int (__fastcall *)(int, int))v8)(inheritFlag, saveCode);
    if ( Lexer_ParseValueList(2, argBuffer, 2, a2) )
    {
      if ( !strcmp_(v4, aLocal_1) )
      {
LABEL_5:
        classExpr = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
        if ( classExpr && *(_DWORD *)(classExpr + 10) && *(_WORD *)classExpr == 2 && !strcmp_(v5, aInherit_3) )
          inheritFlag = 1;
        return ((int (__fastcall *)(int, int))v8)(inheritFlag, saveCode);
      }
      if ( !strcmp_(v5, aVisible_0) )
      {
        saveCode = 2;
        goto LABEL_5;
      }
    }
    Parser_ReportError(2, (int)aSymbolLocalOrV);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 4AC560: variable 'v4' is possibly undefined
// 4AC59E: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (004AC620) --------------------------------------------------------
_DWORD * Rules_BuildClassListForSave(int functionName, int classExprs, int inheritFlag, int saveCode, double a5)
{
  _DWORD *classListHead; // ebp
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  char *expectedClassKind; // ebx
  int *v13; // eax
  int theDefclass; // ebx
  _DWORD *listCursor; // ecx
  _DWORD *i; // edx
  int v17; // eax
  int *v18; // ecx
  _DWORD *newNode; // eax
  int v20; // ecx
  int v21; // eax
  _DWORD argValue[2]; // [esp+0h] [ebp-38h] BYREF
  int argSymbol; // [esp+8h] [ebp-30h]
  int v24; // [esp+18h] [ebp-20h]
  int currentModule; // [esp+1Ch] [ebp-1Ch]
  int v26; // [esp+20h] [ebp-18h]
  int argIndex; // [esp+24h] [ebp-14h]
  int v28; // [esp+28h] [ebp-10h]

  v24 = functionName;
  v26 = saveCode;
  classListHead = 0;
  argIndex = (inheritFlag != 0) + 3;
  currentModule = Module_GetCurrent();
  if ( !v9 )
    return classListHead;
  while ( !Parser_ParseForm((__int16 *)classExprs, argValue, v8, a5) && argValue[1] == 2 )
  {
    v13 = v26 == 1 ? Class_LookupByModule(v10, *(_BYTE **)(argSymbol + 16)) : Class_LookupInScope(*(_BYTE **)(argSymbol + 16));
    theDefclass = (int)v13;
    if ( !v13 || (v13[5] & 4) != 0 && !inheritFlag )
      break;
    listCursor = classListHead;
    for ( i = classListHead; listCursor; listCursor = (_DWORD *)listCursor[5] )
    {
      v17 = listCursor[2];
      if ( theDefclass == v17 || inheritFlag && (Class_HasSuperclass(v17, theDefclass) || Class_HasSuperclass(theDefclass, *(_DWORD *)(v20 + 8))) )
        goto LABEL_3;
      i = listCursor;
    }
    v18 = *(int **)(g_ClipsMemoryTable + 96);
    v28 = g_ClipsMemoryTable;
    if ( v18 )
    {
      g_ClipsMemFreeListTemp = (int)v18;
      v21 = *v18;
      v8 = v28;
      *(_DWORD *)(v28 + 96) = v21;
      newNode = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newNode = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    newNode[1] = 57;
    newNode[5] = 0;
    newNode[2] = theDefclass;
    if ( i )
      i[5] = newNode;
    else
      classListHead = newNode;
    classExprs = *(_DWORD *)(classExprs + 10);
    ++argIndex;
    if ( !classExprs )
      return classListHead;
  }
LABEL_3:
  if ( inheritFlag )
    expectedClassKind = aValidClassName;
  else
    expectedClassKind = aValidConcreteC;
  Parser_ReportError(argIndex, (int)expectedClassKind);
  Rules_FreeClassList(classListHead);
  Lexer_ErrorRecover(1);
  return 0;
}
// 4AC650: variable 'v9' is possibly undefined
// 4AC65A: variable 'v8' is possibly undefined
// 4AC6B6: variable 'v10' is possibly undefined
// 4AC6DE: variable 'v15' is possibly undefined
// 4AC759: variable 'v20' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AC7A0) --------------------------------------------------------
_DWORD * Rules_FreeClassList(_DWORD *result)
{
  _DWORD *classNode; // edx

  for ( ; result; *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp )
  {
    classNode = result;
    result = (_DWORD *)result[5];
    g_ClipsMemFreeListTemp = (int)classNode;
    *classNode = *(_DWORD *)(g_ClipsMemoryTable + 96);
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AC7E0) --------------------------------------------------------
int  Rules_ForEachInstanceForSave(int saveCode, int inheritFlag, int classList, int interruptOK, void (__fastcall *saveFunction)(int, int))
{
  int instanceCount; // esi
  int classCursor; // ebp
  int subtreeCount; // eax
  int theInstance; // ecx
  signed int traversalID; // [esp+0h] [ebp-1Ch]
  int currentModule; // [esp+Ch] [ebp-10h]

  currentModule = Module_GetCurrent();
  instanceCount = 0;
  if ( classList )
  {
    traversalID = Class_NewTraversalID();
    if ( traversalID != -1 )
    {
      classCursor = classList;
      do
      {
        if ( g_ClipsHaltExecution && interruptOK )
          break;
        subtreeCount = Rules_ForEachInstanceInClassSubtree(currentModule, *(_DWORD *)(classCursor + 8), saveCode, inheritFlag, traversalID, saveFunction);
        classCursor = *(_DWORD *)(classCursor + 20);
        instanceCount += subtreeCount;
      }
      while ( classCursor );
      Class_ReleaseTraversalID();
    }
  }
  else
  {
    theInstance = Rules_GetNextInstanceInScope(0);
    if ( theInstance )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( saveCode == 2 || **(_DWORD **)(*(_DWORD *)(theInstance + 44) + 8) == currentModule )
        {
          if ( saveFunction )
            saveFunction(theInstance, theInstance);
          ++instanceCount;
        }
        theInstance = Rules_GetNextInstanceInScope(theInstance);
        if ( !theInstance )
          return instanceCount;
      }
    }
  }
  return instanceCount;
}
// 4AC810: conditional instruction was optimized away because ebx.4!=0
// 4AC891: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (004AC8C0) --------------------------------------------------------
int  Rules_ForEachInstanceInClassSubtree(
        int currentModule,
        int theDefclass,
        int saveCode,
        int inheritFlag,
        signed int traversalID,
        void (__fastcall *saveFunction)(int, int))
{
  int traversalMarkAddr; // ebx
  int traversalMask; // eax
  int instanceCount; // edi
  int i; // ecx
  unsigned int subclassIndex; // [esp+Ch] [ebp-14h]
  int subclassOffset; // [esp+10h] [ebp-10h]

  traversalMarkAddr = theDefclass + ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3);
  traversalMask = 1 << (traversalID % 8);
  instanceCount = 0;
  if ( (*(_BYTE *)(traversalMarkAddr + 108) & (unsigned __int8)traversalMask) != 0 )
    return 0;
  *(_BYTE *)(traversalMarkAddr + 108) |= traversalMask;
  if ( saveCode == 1 && currentModule == **(_DWORD **)(theDefclass + 8) || saveCode == 2 && Class_IsInScope(theDefclass, currentModule) )
  {
    for ( i = Rules_GetNextInstanceInClass(theDefclass, 0); i; i = Rules_GetNextInstanceInClass(theDefclass, i) )
    {
      if ( saveFunction )
        saveFunction(i, i);
      ++instanceCount;
    }
  }
  if ( inheritFlag )
  {
    subclassIndex = 0;
    subclassOffset = 0;
    while ( *(unsigned __int16 *)(theDefclass + 40) > subclassIndex )
    {
      instanceCount += Rules_ForEachInstanceInClassSubtree(currentModule, *(_DWORD *)(subclassOffset + *(_DWORD *)(theDefclass + 42)), saveCode, 1, traversalID, saveFunction);
      subclassOffset += 4;
      ++subclassIndex;
    }
  }
  return instanceCount;
}
// 4AC959: variable 'i' is possibly undefined

//----- (004ACA00) --------------------------------------------------------
signed int  Rules_WriteInstanceTextRecord(int logicalName, int theInstance)
{
  int v3; // ecx
  int v4; // ecx
  unsigned int slotIndex; // edi
  int slotOffset; // ebp
  int v7; // ecx
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  Output_Write(logicalName, (int)asc_508EB0, logicalName);
  Output_Write(v3, *(_DWORD *)(*(_DWORD *)(theInstance + 28) + 16), v3);
  Output_Write(v4, (int)aOf_1, v4);
  slotIndex = 0;
  slotOffset = 0;
  Output_Write(v7, *(_DWORD *)(**(_DWORD **)(theInstance + 44) + 16), v7);
  while ( slotIndex < *(_DWORD *)(*(_DWORD *)(theInstance + 44) + 72) )
  {
    Output_Write(logicalName, (int)asc_508EBC, *(_DWORD *)(*(_DWORD *)(theInstance + 72) + slotOffset));
    Output_Write(logicalName, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v10 + 8) + 12) + 16), v10);
    if ( (*(_DWORD *)(v11 + 4) & 0xFC) == 0x10 )
    {
      if ( *(_DWORD *)(*(_DWORD *)(v11 + 8) + 6) )
      {
        Output_Write(logicalName, (int)asc_508EC4, v11);
        Lexer_OutputFieldRange(logicalName, *(_DWORD *)(v13 + 8), *(_DWORD *)(*(_DWORD *)(v13 + 8) + 6) - 1, 0, 0);
      }
    }
    else
    {
      Output_Write(logicalName, (int)asc_508EC4, v11);
      Rules_PrintAtomValue(logicalName, *(_DWORD *)(v12 + 4) << 24 >> 26, *(int **)(v12 + 8));
    }
    Output_Write(logicalName, (int)asc_508EC8, v11);
    slotOffset += 4;
    ++slotIndex;
  }
  return Output_Write(logicalName, (int)asc_508ECC, v8);
}
// 4ACA24: variable 'v3' is possibly undefined
// 4ACA30: variable 'v4' is possibly undefined
// 4ACA46: variable 'v7' is possibly undefined
// 4ACA5D: variable 'v8' is possibly undefined
// 4ACA80: variable 'v10' is possibly undefined
// 4ACA92: variable 'v11' is possibly undefined
// 4ACAAC: variable 'v12' is possibly undefined
// 4ACAE9: variable 'v13' is possibly undefined

