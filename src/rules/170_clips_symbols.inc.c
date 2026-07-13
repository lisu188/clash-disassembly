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
signed int  Rules_OddpFunction(int a1, double a2)
{
  signed int result; // eax
  int v3; // [esp-8h] [ebp-24h] BYREF
  int v4; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+14h] [ebp-8h]

  v5 = a1;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &v3, 1, a2);
  if ( result )
    return *(_DWORD *)(v4 + 16) != 2 * (*(_DWORD *)(v4 + 16) / 2);
  return result;
}

//----- (004A01E0) --------------------------------------------------------
signed int  Rules_EvenpFunction(int a1, double a2)
{
  signed int result; // eax
  int v3; // [esp-8h] [ebp-24h] BYREF
  int v4; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+14h] [ebp-8h]

  v5 = a1;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &v3, 1, a2);
  if ( result )
    return *(_DWORD *)(v4 + 16) == 2 * (*(_DWORD *)(v4 + 16) / 2);
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
int * Rules_AdditionFunction(uintptr_t a1, double a2)
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
    *(_DWORD *)(a1 + 4) = 0;
    *(_DWORD *)(a1 + 8) = (int)(uintptr_t)Rules_AddDoubleValue(float_sum);
  }
  else
  {
    *(_DWORD *)(a1 + 4) = 1;
    *(_DWORD *)(a1 + 8) = (int)(uintptr_t)Rules_AddIntegerValue(integer_sum);
  }
  return (int *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 8);
}
// 51A960: using guessed type int dword_51A960;

//----- (004A04A0) --------------------------------------------------------
int * Rules_MultiplicationFunction(int a1, double a2)
{
  signed int v2; // ebp
  int v3; // edi
  int v4; // esi
  int v5; // eax
  double v6; // st6
  int v7; // ebx
  int *result; // eax
  double v9; // [esp-8h] [ebp-4Ch]
  _DWORD v10[2]; // [esp+0h] [ebp-44h] BYREF
  int v11; // [esp+8h] [ebp-3Ch]
  double v12; // [esp+18h] [ebp-2Ch]
  int v13; // [esp+20h] [ebp-24h]
  int i; // [esp+24h] [ebp-20h]
  signed int v15; // [esp+28h] [ebp-1Ch]

  v13 = a1;
  v2 = 1;
  v3 = 0;
  v12 = 1.0;
  v4 = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 1; v4; ++i )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)v4, v3, v10, a2, i);
    if ( v5 )
      v4 = *(_DWORD *)(v4 + 10);
    else
      v4 = 0;
    if ( v3 )
    {
      v6 = v12 * *(double *)(v11 + 16);
    }
    else
    {
      if ( v10[1] == 1 )
      {
        v2 *= *(_DWORD *)(v11 + 16);
        continue;
      }
      v15 = v2;
      v6 = (double)v2 * *(double *)(v11 + 16);
      v3 = 1;
    }
    v12 = v6;
  }
  if ( v3 )
  {
    v9 = v12;
    v7 = v13;
    *(_DWORD *)(v13 + 4) = 0;
    result = (int *)Rules_AddDoubleValue(v9);
  }
  else
  {
    *(_DWORD *)(v13 + 4) = 1;
    v7 = v13;
    result = Rules_AddIntegerValue(v2);
  }
  *(_DWORD *)(v7 + 8) = result;
  return result;
}
// 4A04ED: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A0590) --------------------------------------------------------
int * Rules_SubtractionFunction(int a1, double a2)
{
  signed int v2; // ebp
  int v3; // edi
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // ebx
  int *result; // eax
  double v10; // [esp-8h] [ebp-4Ch]
  int v11; // [esp+0h] [ebp-44h] BYREF
  int v12; // [esp+4h] [ebp-40h]
  int v13; // [esp+8h] [ebp-3Ch]
  double v14; // [esp+18h] [ebp-2Ch]
  int v15; // [esp+20h] [ebp-24h]
  int v16; // [esp+24h] [ebp-20h]
  signed int v17; // [esp+28h] [ebp-1Ch]

  v15 = a1;
  v2 = 0;
  v3 = 0;
  v14 = 0.0;
  v4 = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  v16 = 1;
  if ( v4 )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)v4, 0, &v11, a2, 1);
    if ( v6 )
      v4 = *(_DWORD *)(v4 + 10);
    else
      v4 = 0;
    if ( v12 == 1 )
    {
      v2 = *(_DWORD *)(v13 + 16);
    }
    else
    {
      v3 = 1;
      v7 = *(_DWORD *)(v13 + 20);
      LODWORD(v14) = *(_DWORD *)(v13 + 16);
      HIDWORD(v14) = v7;
    }
    ++v16;
  }
  while ( v4 )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)v4, v3, &v11, a2, v16);
    if ( v5 )
      v4 = *(_DWORD *)(v4 + 10);
    else
      v4 = 0;
    if ( v3 )
    {
      v14 = v14 - *(double *)(v13 + 16);
      ++v16;
    }
    else
    {
      if ( v12 == 1 )
      {
        v2 -= *(_DWORD *)(v13 + 16);
      }
      else
      {
        v17 = v2;
        v3 = 1;
        v14 = (double)v2 - *(double *)(v13 + 16);
      }
      ++v16;
    }
  }
  if ( v3 )
  {
    v10 = v14;
    v8 = v15;
    *(_DWORD *)(v15 + 4) = 0;
    result = (int *)Rules_AddDoubleValue(v10);
  }
  else
  {
    *(_DWORD *)(v15 + 4) = 1;
    v8 = v15;
    result = Rules_AddIntegerValue(v2);
  }
  *(_DWORD *)(v8 + 8) = result;
  return result;
}
// 4A05E0: variable 'v5' is possibly undefined
// 4A0616: variable 'v6' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A06E0) --------------------------------------------------------
int * Rules_DivisionFunction(int a1, double a2)
{
  signed int v2; // esi
  int v3; // ebp
  int v4; // edi
  int v5; // ebx
  int *result; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  BOOL v10; // eax
  int v11; // ebx
  double v12; // [esp-8h] [ebp-4Ch]
  int v13; // [esp+0h] [ebp-44h] BYREF
  int v14; // [esp+4h] [ebp-40h]
  int v15; // [esp+8h] [ebp-3Ch]
  double v16; // [esp+18h] [ebp-2Ch]
  int v17; // [esp+20h] [ebp-24h]
  int v18; // [esp+24h] [ebp-20h]
  signed int v19; // [esp+28h] [ebp-1Ch]

  v17 = a1;
  v2 = 1;
  v3 = g_Rules_AutoFloatDividendEnabled;
  v16 = 1.0;
  v4 = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  v18 = 1;
  if ( v4 )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)v4, g_Rules_AutoFloatDividendEnabled, &v13, a2, 1);
    if ( v7 )
      v4 = *(_DWORD *)(v4 + 10);
    else
      v4 = 0;
    if ( v14 == 1 )
    {
      v2 = *(_DWORD *)(v15 + 16);
    }
    else
    {
      v3 = 1;
      v8 = *(_DWORD *)(v15 + 20);
      LODWORD(v16) = *(_DWORD *)(v15 + 16);
      HIDWORD(v16) = v8;
    }
    ++v18;
  }
  while ( v4 )
  {
    a2 = Rules_CoerceFormToNumericArg((__int16 *)v4, v3, &v13, a2, v18);
    if ( v9 )
      v4 = *(_DWORD *)(v4 + 10);
    else
      v4 = 0;
    if ( v14 == 1 )
      v10 = *(_DWORD *)(v15 + 16) == 0;
    else
      v10 = !v14 && (*(_DWORD *)(v15 + 20) & 0x7FFFFFFF) == 0 && !*(_DWORD *)(v15 + 16);
    if ( v10 )
    {
      Rules_ReportDivideByZeroError();
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      v11 = v17;
      *(_DWORD *)(v17 + 4) = 0;
      result = (int *)Rules_AddDoubleValue(1.0);
      *(_DWORD *)(v11 + 8) = result;
      return result;
    }
    if ( v3 )
    {
      v16 = v16 / *(double *)(v15 + 16);
      ++v18;
    }
    else
    {
      if ( v14 == 1 )
      {
        v2 /= *(int *)(v15 + 16);
      }
      else
      {
        v19 = v2;
        v3 = 1;
        v16 = (double)v2 / *(double *)(v15 + 16);
      }
      ++v18;
    }
  }
  if ( v3 )
  {
    v12 = v16;
    v5 = v17;
    *(_DWORD *)(v17 + 4) = 0;
    result = (int *)Rules_AddDoubleValue(v12);
  }
  else
  {
    *(_DWORD *)(v17 + 4) = 1;
    v5 = v17;
    result = Rules_AddIntegerValue(v2);
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
  int v1; // esi
  int v2; // edi
  int v3; // eax
  double v4; // st6
  int v5; // eax
  double v6; // st6
  double v7; // st6
  int v8; // [esp+0h] [ebp-3Ch] BYREF
  int v9; // [esp+4h] [ebp-38h]
  int v10; // [esp+8h] [ebp-34h]
  int v11; // [esp+18h] [ebp-24h]
  int v12; // [esp+1Ch] [ebp-20h]
  int v13; // [esp+20h] [ebp-1Ch]

  v13 = 1;
  v1 = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  v2 = 1;
  if ( v1 )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)v1, 0, &v8, result, 1);
    if ( v3 )
      v1 = *(_DWORD *)(v1 + 10);
    else
      v1 = 0;
    if ( v9 == 1 )
    {
      v13 = *(_DWORD *)(v10 + 16);
    }
    else
    {
      v4 = *(double *)(v10 + 16);
      _CHP(v8, v9);
      v13 = (int)v4;
    }
    v2 = 2;
  }
  while ( v1 )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)v1, 0, &v8, result, v2);
    if ( v5 )
      v1 = *(_DWORD *)(v1 + 10);
    else
      v1 = 0;
    if ( v9 == 1 )
    {
      v12 = *(_DWORD *)(v10 + 16);
    }
    else
    {
      if ( v9 )
        goto LABEL_16;
      v6 = *(double *)(v10 + 16);
      _CHP(v8, 0);
      v12 = (int)v6;
    }
    if ( !v12 )
    {
      Rules_ReportDivideByZeroError();
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return result;
    }
LABEL_16:
    if ( v9 == 1 )
    {
      v13 /= *(int *)(v10 + 16);
    }
    else
    {
      v7 = *(double *)(v10 + 16);
      _CHP(v8, v9);
      v11 = (int)v7;
      v13 /= (int)v7;
    }
    ++v2;
  }
  return result;
}
// 4A0918: variable 'v3' is possibly undefined
// 4A095B: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A0A10) --------------------------------------------------------
int  Rules_SetAutoFloatDividendCommand(int a1, double a2)
{
  int v3; // ecx
  int v5; // [esp-4h] [ebp-24h] BYREF
  __int64 v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+18h] [ebp-8h]

  v7 = a1;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, &v5, a2);
    g_Rules_AutoFloatDividendEnabled = v6 != __PAIR64__(g_ClipsFalseSymbol, 2);
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
signed int  Rules_IntegerFunction(int a1, double a2)
{
  signed int result; // eax
  _DWORD v3[9]; // [esp-8h] [ebp-24h] BYREF

  v3[7] = a1;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, v3, 1, a2);
  if ( result )
    return *(_DWORD *)(v3[2] + 16);
  return result;
}

//----- (004A0B10) --------------------------------------------------------
double  Rules_FloatFunction(int a1, int a2, int a3, double a4)
{
  int v5; // eax
  int v6; // [esp-8h] [ebp-30h] BYREF
  int v7; // [esp+0h] [ebp-28h]
  double v8; // [esp+10h] [ebp-18h]
  int v9; // [esp+18h] [ebp-10h]
  int v10; // [esp+1Ch] [ebp-Ch]
  int v11; // [esp+24h] [ebp-4h]

  v11 = a1;
  v10 = a3;
  v9 = a2;
  if ( Lexer_TokenExpect(1) == -1 )
  {
    v8 = 0.0;
    return 0.0;
  }
  else if ( Lexer_ParseValueList(1, &v6, 0, a4) )
  {
    v5 = *(_DWORD *)(v7 + 20);
    LODWORD(v8) = *(_DWORD *)(v7 + 16);
    HIDWORD(v8) = v5;
    return v8;
  }
  else
  {
    v8 = 0.0;
    return 0.0;
  }
}

//----- (004A0B90) --------------------------------------------------------
void  Rules_AbsFunction(_DWORD *a1, double a2)
{
  signed int v3; // eax
  int v4; // ecx
  int v5; // edx

  if ( Lexer_TokenExpect(1) == -1 )
  {
    v3 = 0;
    goto LABEL_7;
  }
  v3 = Lexer_ParseValueList(1, a1, 110, a2);
  if ( !v3 )
  {
LABEL_7:
    a1[1] = 1;
    a1[2] = Rules_AddIntegerValue(v3);
    return;
  }
  if ( a1[1] == 1 )
  {
    v4 = *(_DWORD *)(a1[2] + 16);
    if ( v4 < 0 )
      a1[2] = Rules_AddIntegerValue(-v4);
  }
  else
  {
    v5 = a1[2];
    if ( *(double *)(v5 + 16) < 0.0 )
      a1[2] = Rules_AddDoubleValue(-*(double *)(v5 + 16));
  }
}

//----- (004A0C30) --------------------------------------------------------
void  Rules_MinFunction(_DWORD *a1, double a2)
{
  int v3; // ebp
  signed int v4; // eax
  int v5; // edi
  int v6; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+4h] [ebp-2Ch]
  int v8; // [esp+8h] [ebp-28h]

  v3 = Lexer_TokenExpect(1);
  if ( v3 == -1 )
  {
    v4 = 0;
    goto LABEL_13;
  }
  v4 = Lexer_ParseValueList(1, a1, 110, a2);
  if ( !v4 )
  {
LABEL_13:
    a1[1] = 1;
    a1[2] = Rules_AddIntegerValue(v4);
    return;
  }
  v5 = 2;
  if ( v3 >= 2 )
  {
    while ( 1 )
    {
      if ( !Lexer_ParseValueList(v5, &v6, 110, a2) )
        return;
      if ( a1[1] != 1 )
        break;
      if ( v7 != 1 )
      {
        a2 = (double)*(int *)(a1[2] + 16);
        if ( a2 <= *(double *)(v8 + 16) )
          goto LABEL_10;
        a1[1] = v7;
        goto LABEL_9;
      }
      if ( *(_DWORD *)(a1[2] + 16) > *(_DWORD *)(v8 + 16) )
        goto LABEL_8;
LABEL_10:
      if ( ++v5 > v3 )
        return;
    }
    if ( v7 == 1 )
    {
      a2 = (double)*(int *)(v8 + 16);
      if ( a2 >= *(double *)(a1[2] + 16) )
        goto LABEL_10;
    }
    else
    {
      a2 = *(double *)(a1[2] + 16);
      if ( a2 <= *(double *)(v8 + 16) )
        goto LABEL_10;
    }
LABEL_8:
    a1[1] = v7;
LABEL_9:
    a1[2] = v8;
    goto LABEL_10;
  }
}

//----- (004A0D30) --------------------------------------------------------
void  Rules_MaxFunction(_DWORD *a1, double a2)
{
  int v3; // ebp
  signed int v4; // eax
  int v5; // edi
  int v6; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+4h] [ebp-2Ch]
  int v8; // [esp+8h] [ebp-28h]

  v3 = Lexer_TokenExpect(1);
  if ( v3 == -1 )
  {
    v4 = 0;
    goto LABEL_13;
  }
  v4 = Lexer_ParseValueList(1, a1, 110, a2);
  if ( !v4 )
  {
LABEL_13:
    a1[1] = 1;
    a1[2] = Rules_AddIntegerValue(v4);
    return;
  }
  v5 = 2;
  if ( v3 >= 2 )
  {
    while ( 1 )
    {
      if ( !Lexer_ParseValueList(v5, &v6, 110, a2) )
        return;
      if ( a1[1] != 1 )
        break;
      if ( v7 != 1 )
      {
        a2 = (double)*(int *)(a1[2] + 16);
        if ( a2 >= *(double *)(v8 + 16) )
          goto LABEL_10;
        a1[1] = v7;
        goto LABEL_9;
      }
      if ( *(_DWORD *)(a1[2] + 16) < *(_DWORD *)(v8 + 16) )
        goto LABEL_8;
LABEL_10:
      if ( ++v5 > v3 )
        return;
    }
    if ( v7 == 1 )
    {
      a2 = (double)*(int *)(v8 + 16);
      if ( a2 <= *(double *)(a1[2] + 16) )
        goto LABEL_10;
    }
    else
    {
      a2 = *(double *)(a1[2] + 16);
      if ( a2 >= *(double *)(v8 + 16) )
        goto LABEL_10;
    }
LABEL_8:
    a1[1] = v7;
LABEL_9:
    a1[2] = v8;
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
_DWORD * Rules_DeleteFunction(_DWORD *a1, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD v5[6]; // [esp+0h] [ebp-58h] BYREF
  _DWORD v6[6]; // [esp+18h] [ebp-40h] BYREF
  _DWORD v7[10]; // [esp+30h] [ebp-28h] BYREF

  v7[8] = a2;
  if ( !Lexer_ParseValueList(1, v5, 4, a3)
    || !Lexer_ParseValueList(2, v7, 1, a3)
    || !Lexer_ParseValueList(3, v6, 1, a3)
    || (result = (_DWORD *)Rules_MultifieldDeleteRange(a1, v5, *(_DWORD *)(v6[2] + 16), *(_DWORD *)(v7[2] + 16), (int)aDelete)) == 0 )
  {
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  return result;
}

//----- (004A1190) --------------------------------------------------------
_DWORD * Rules_MVDeleteFunction(_DWORD *a1, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD v5[6]; // [esp+0h] [ebp-40h] BYREF
  int v6; // [esp+18h] [ebp-28h] BYREF
  int v7; // [esp+20h] [ebp-20h]
  int v8; // [esp+38h] [ebp-8h]

  v8 = a2;
  if ( !Lexer_ParseValueList(1, &v6, 1, a3)
    || !Lexer_ParseValueList(2, v5, 4, a3)
    || (result = (_DWORD *)Rules_MultifieldDeleteRange(a1, v5, *(_DWORD *)(v7 + 16), *(_DWORD *)(v7 + 16), (int)aMvDelete)) == 0 )
  {
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  return result;
}

//----- (004A1210) --------------------------------------------------------
_DWORD * Rules_ReplaceFunction(_DWORD *a1, int a2, double a3)
{
  int v5; // ecx
  int v6; // eax
  _DWORD *result; // eax
  _DWORD v8[6]; // [esp+0h] [ebp-70h] BYREF
  _DWORD v9[6]; // [esp+18h] [ebp-58h] BYREF
  _DWORD v10[6]; // [esp+30h] [ebp-40h] BYREF
  _DWORD v11[10]; // [esp+48h] [ebp-28h] BYREF

  v11[8] = a2;
  if ( !Lexer_ParseValueList(1, v8, 4, a3)
    || !Lexer_ParseValueList(2, v10, 1, a3)
    || !Lexer_ParseValueList(3, v9, 1, a3) )
  {
    goto LABEL_7;
  }
  v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10) + 10);
  if ( *(_DWORD *)(v6 + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(v11, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10) + 10), 1, a3);
  else
    Parser_ParseForm((__int16 *)v6, v11, v5, a3);
  result = (_DWORD *)Rules_MultifieldReplaceRange(a1, v8, *(_DWORD *)(v9[2] + 16), *(_DWORD *)(v10[2] + 16), v11, (int)aReplace);
  if ( !result )
  {
LABEL_7:
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  return result;
}
// 4A12E0: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A12F0) --------------------------------------------------------
_DWORD * Rules_MVReplaceFunction(_DWORD *a1, int a2, double a3)
{
  int v4; // ecx
  _DWORD *result; // eax
  _DWORD v6[6]; // [esp+0h] [ebp-58h] BYREF
  int v7; // [esp+18h] [ebp-40h] BYREF
  int v8; // [esp+20h] [ebp-38h]
  _DWORD v9[10]; // [esp+30h] [ebp-28h] BYREF

  v9[8] = a2;
  if ( !Lexer_ParseValueList(1, &v7, 1, a3)
    || !Lexer_ParseValueList(2, v6, 4, a3)
    || (Parser_ParseForm(*(__int16 **)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), v9, v4, a3),
        (result = (_DWORD *)Rules_MultifieldReplaceRange(a1, v6, *(_DWORD *)(v8 + 16), *(_DWORD *)(v8 + 16), v9, (int)aMvReplace)) == 0) )
  {
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  return result;
}
// 4A133E: variable 'v4' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A1390) --------------------------------------------------------
_DWORD * Rules_InsertFunction(_DWORD *a1, int a2, double a3)
{
  int v5; // ecx
  int v6; // eax
  _DWORD *result; // eax
  _DWORD v8[6]; // [esp+0h] [ebp-58h] BYREF
  _DWORD v9[6]; // [esp+18h] [ebp-40h] BYREF
  _DWORD v10[10]; // [esp+30h] [ebp-28h] BYREF

  v10[8] = a2;
  if ( !Lexer_ParseValueList(1, v8, 4, a3) || !Lexer_ParseValueList(2, v10, 1, a3) )
    goto LABEL_6;
  v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
  if ( *(_DWORD *)(v6 + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(v9, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), 1, a3);
  else
    Parser_ParseForm((__int16 *)v6, v9, v5, a3);
  result = (_DWORD *)Rules_MultifieldInsertRange(a1, v8, v9, *(_DWORD *)(v10[2] + 16), (int)aInsert);
  if ( !result )
  {
LABEL_6:
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  return result;
}
// 4A1431: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004A1440) --------------------------------------------------------
_DWORD * Rules_ExplodeFunction(_DWORD *a1, int a2, double a3)
{
  _DWORD *v5; // eax
  _DWORD *v6; // ecx
  int v7; // eax
  _DWORD *result; // eax
  _DWORD v9[10]; // [esp-8h] [ebp-28h] BYREF

  v9[8] = a2;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, v9, 3, a3) )
  {
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  else
  {
    v5 = Rules_CreateMultifieldFromString(*(const char **)(v9[2] + 16));
    v6 = v5;
    if ( v5 )
    {
      v7 = *(_DWORD *)((char *)v5 + 6);
    }
    else
    {
      v6 = Rules_CreateEphemeralMultifield(0);
      v7 = 0;
    }
    a1[1] = 4;
    a1[3] = 0;
    result = (_DWORD *)(v7 - 1);
    a1[2] = v6;
    a1[4] = result;
  }
  return result;
}

//----- (004A14E0) --------------------------------------------------------
signed int * Rules_ImplodeFunction(double a1)
{
  int v1; // ecx
  unsigned int v2; // esi
  int v3; // ebp
  int v4; // ebx
  int v5; // edx
  __int16 v6; // cx
  int v7; // eax
  const char *v8; // edi
  _BYTE *v10; // eax
  char *v11; // edi
  int v12; // eax
  int v13; // ecx
  char *v14; // edx
  __int16 v15; // bx
  _BYTE *v16; // eax
  _BYTE *v17; // edx
  char *v19; // eax
  int v20; // edx
  _BYTE *v21; // eax
  _BYTE *v22; // edx
  int v24; // eax
  char *v25; // ecx
  char *v26; // ebp
  char v27; // bl
  char *v28; // edx
  __int16 v29; // bx
  char *v30; // eax
  int v31; // ecx
  char *v32; // edx
  int v34; // eax
  char *v35; // eax
  int v36; // ecx
  char *v37; // edx
  int v39; // eax
  char *v40; // eax
  int v42; // ecx
  int v43; // [esp+0h] [ebp-3Ch] BYREF
  int v44; // [esp+8h] [ebp-34h]
  int v45; // [esp+Ch] [ebp-30h]
  int v46; // [esp+10h] [ebp-2Ch]
  char *v47; // [esp+18h] [ebp-24h]
  int v48; // [esp+1Ch] [ebp-20h]
  int v49; // [esp+20h] [ebp-1Ch]

  v2 = 0;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, &v43, 4, a1) )
    return Str_Intern(g_Rules_ImplodeEmptyResult, v1);
  v3 = v45 + 1;
  v4 = v44;
  v5 = v44 + 6 * (v45 + 1) - 6;
  while ( v3 <= v46 + 1 )
  {
    v6 = *(_WORD *)(v5 + 14);
    switch ( v6 )
    {
      case 0:
        v7 = Rules_FloatToSymbol(*(_DWORD *)(*(_DWORD *)(v5 + 16) + 20), *(double *)(*(_DWORD *)(v5 + 16) + 16));
LABEL_7:
        v8 = (const char *)v7;
LABEL_8:
        v1 = strlen(v8) + 1;
        v2 += v1;
        goto LABEL_9;
      case 1:
        v7 = Rules_LongIntegerToSymbol(*(_DWORD *)(*(_DWORD *)(v5 + 16) + 16));
        goto LABEL_7;
      case 3:
        v1 = strlen(*(const char **)(*(_DWORD *)(v5 + 16) + 16)) + 3;
        v10 = *(_BYTE **)(*(_DWORD *)(v5 + 16) + 16);
        v2 += v1;
        if ( *v10 )
        {
          do
          {
            if ( *v10 == 34 )
              ++v2;
            BYTE1(v1) = *++v10;
          }
          while ( BYTE1(v1) );
          v5 += 6;
          ++v3;
        }
        else
        {
LABEL_9:
          v5 += 6;
          ++v3;
        }
        break;
      case 8:
        v1 = strlen(*(const char **)(*(_DWORD *)(v5 + 16) + 16)) + 3;
        v2 += v1;
        v5 += 6;
        ++v3;
        break;
      case 7:
        v1 = strlen(*(const char **)(*(_DWORD *)(*(_DWORD *)(v5 + 16) + 28) + 16)) + 3;
        v2 += v1;
        v5 += 6;
        ++v3;
        break;
      default:
        v8 = *(const char **)(*(_DWORD *)(v5 + 16) + 16);
        goto LABEL_8;
    }
  }
  if ( !v2 )
    return Str_Intern(g_Rules_ImplodeEmptyResult, v1);
  v11 = (char *)Mem_SmallBlockAlloc(v2);
  v48 = v45 + 1;
  v12 = v4 + 6 * (v45 + 1) - 6;
  v13 = 0;
  while ( 1 )
  {
    v49 = v12;
    v14 = &v11[v13];
    if ( v46 + 1 < v48 )
      break;
    v15 = *(_WORD *)(v49 + 14);
    if ( v15 )
    {
      if ( v15 == 1 )
      {
        v21 = (_BYTE *)Rules_LongIntegerToSymbol(*(_DWORD *)(*(_DWORD *)(v49 + 16) + 16));
        if ( *v21 )
        {
          do
          {
            *v22++ = *v21;
            ++v13;
          }
          while ( *++v21 );
        }
      }
      else if ( v15 == 3 )
      {
        v24 = v13 + 1;
        v25 = *(char **)(*(_DWORD *)(v49 + 16) + 16);
        *v14 = 34;
        while ( 1 )
        {
          v26 = &v11[v24];
          if ( !*v25 )
            break;
          if ( *v25 == 34 )
          {
            ++v24;
            *v26 = 92;
          }
          v27 = *v25;
          v28 = &v11[v24];
          ++v25;
          ++v24;
          *v28 = v27;
        }
        v13 = v24 + 1;
        *v26 = 34;
      }
      else
      {
        v47 = &v11[v13 + 1];
        v29 = *(_WORD *)(v49 + 14);
        if ( v29 == 8 )
        {
          v30 = *(char **)(*(_DWORD *)(v49 + 16) + 16);
          v11[v13] = 91;
          v31 = v13 + 1;
          if ( *v30 )
          {
            v32 = v47;
            do
            {
              *v32++ = *v30;
              ++v31;
            }
            while ( *++v30 );
          }
          v34 = v31;
          v13 = v31 + 1;
          v11[v34] = 93;
        }
        else if ( v29 == 7 )
        {
          v35 = *(char **)(*(_DWORD *)(*(_DWORD *)(v49 + 16) + 28) + 16);
          v11[v13] = 91;
          v36 = v13 + 1;
          if ( *v35 )
          {
            v37 = v47;
            do
            {
              *v37++ = *v35;
              ++v36;
            }
            while ( *++v35 );
          }
          v39 = v36;
          v13 = v36 + 1;
          v11[v39] = 93;
        }
        else
        {
          v40 = *(char **)(*(_DWORD *)(v49 + 16) + 16);
          if ( *v40 )
          {
            do
            {
              *v14++ = *v40;
              ++v13;
            }
            while ( *++v40 );
          }
        }
      }
    }
    else
    {
      v16 = (_BYTE *)Rules_FloatToSymbol(v13, *(double *)(*(_DWORD *)(v49 + 16) + 16));
      if ( *v16 )
      {
        do
        {
          *v17++ = *v16;
          ++v13;
        }
        while ( *++v16 );
      }
    }
    v19 = &v11[v13];
    v20 = v48;
    ++v13;
    *v19 = 32;
    v12 = v49 + 6;
    v48 = v20 + 1;
  }
  *(v14 - 1) = 0;
  Str_Intern(v11, v13);
  Mem_SmallBlockFree(v11, v2);
  return (signed int *)v42;
}
// 4A156A: variable 'v5' is possibly undefined
// 4A1575: variable 'v1' is possibly undefined
// 4A1696: variable 'v17' is possibly undefined
// 4A169C: variable 'v13' is possibly undefined
// 4A16D4: variable 'v22' is possibly undefined
// 4A17E2: variable 'v42' is possibly undefined

//----- (004A17F0) --------------------------------------------------------
_DWORD * Rules_SubseqFunction(_DWORD *a1, double a2)
{
  int v3; // ebp
  int v4; // edi
  int v5; // eax
  int v6; // edx
  int v7; // edx
  _DWORD *result; // eax
  _DWORD v9[2]; // [esp+0h] [ebp-34h] BYREF
  int v10; // [esp+8h] [ebp-2Ch]
  int v11; // [esp+Ch] [ebp-28h]
  int v12; // [esp+18h] [ebp-1Ch]

  if ( !Lexer_ParseValueList(1, v9, 4, a2) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v12 = v11 + 1;
  v3 = v10;
  if ( !Lexer_ParseValueList(2, v9, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v4 = *(_DWORD *)(v10 + 16);
  if ( !Lexer_ParseValueList(3, v9, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v5 = *(_DWORD *)(v10 + 16);
  if ( v5 < 1 )
    return Rules_SetMultifieldErrorValue((int)a1);
  if ( v5 < v4 )
    return Rules_SetMultifieldErrorValue((int)a1);
  v6 = *(_DWORD *)(v3 + 6);
  if ( v4 > v6 )
    return Rules_SetMultifieldErrorValue((int)a1);
  if ( v5 > v6 )
    v5 = *(_DWORD *)(v3 + 6);
  if ( v4 < 1 )
    v4 = 1;
  a1[1] = 4;
  v7 = v12;
  a1[2] = v3;
  result = (_DWORD *)(v7 + v5 - 2);
  a1[4] = result;
  a1[3] = v7 + v4 - 2;
  return result;
}

//----- (004A18D0) --------------------------------------------------------
_DWORD * Rules_MVSubseqFunction(_DWORD *a1, double a2)
{
  int v3; // edi
  int v4; // ebp
  int v5; // ecx
  _DWORD *result; // eax
  int v7; // edx
  _DWORD v8[2]; // [esp+0h] [ebp-30h] BYREF
  int v9; // [esp+8h] [ebp-28h]
  int v10; // [esp+Ch] [ebp-24h]

  if ( !Lexer_ParseValueList(1, v8, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v3 = *(_DWORD *)(v9 + 16);
  if ( !Lexer_ParseValueList(2, v8, 1, a2) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v4 = *(_DWORD *)(v9 + 16);
  if ( v4 < 1 )
    return Rules_SetMultifieldErrorValue((int)a1);
  if ( v4 < v3 )
    return Rules_SetMultifieldErrorValue((int)a1);
  if ( !Lexer_ParseValueList(3, v8, 4, a2) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v5 = v9;
  result = *(_DWORD **)(v9 + 6);
  v7 = v10 + 1;
  if ( v3 > (int)result )
    return Rules_SetMultifieldErrorValue((int)a1);
  if ( v4 > (int)result )
    v4 = *(_DWORD *)(v9 + 6);
  if ( v3 < 1 )
    v3 = 1;
  a1[1] = 4;
  a1[2] = v5;
  a1[4] = v7 + v4 - 2;
  a1[3] = v3 + v7 - 2;
  return result;
}

//----- (004A19A0) --------------------------------------------------------
_DWORD * Rules_FirstFunction(_DWORD *a1, int a2, double a3)
{
  int v5; // eax
  _DWORD *result; // eax
  _DWORD v7[3]; // [esp-8h] [ebp-28h] BYREF
  signed int v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+8h] [ebp-18h]
  int v10; // [esp+18h] [ebp-8h]

  v10 = a2;
  if ( !Lexer_ParseValueList(1, v7, 4, a3) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v5 = v7[2];
  a1[1] = 4;
  a1[2] = v5;
  if ( v9 + 1 >= v8 + 1 )
  {
    a1[4] = v8;
    result = (_DWORD *)v8;
    a1[3] = v8;
  }
  else
  {
    a1[4] = v9;
    result = (_DWORD *)v8;
    a1[3] = v8;
  }
  return result;
}

//----- (004A1A20) --------------------------------------------------------
_DWORD * Rules_RestFunction(_DWORD *a1, int a2, double a3)
{
  int v5; // eax
  _DWORD *result; // eax
  _DWORD v7[3]; // [esp-8h] [ebp-28h] BYREF
  int v8; // [esp+4h] [ebp-1Ch]
  signed int v9; // [esp+8h] [ebp-18h]
  int v10; // [esp+18h] [ebp-8h]

  v10 = a2;
  if ( !Lexer_ParseValueList(1, v7, 4, a3) )
    return Rules_SetMultifieldErrorValue((int)a1);
  v5 = v7[2];
  a1[1] = 4;
  a1[2] = v5;
  if ( v8 + 1 > v9 + 1 )
  {
    a1[3] = v8;
    result = (_DWORD *)v9;
    a1[4] = v9;
  }
  else
  {
    a1[3] = v8 + 1;
    result = (_DWORD *)v9;
    a1[4] = v9;
  }
  return result;
}

//----- (004A1A90) --------------------------------------------------------
signed int * Rules_NthFunction(int a1, int a2, double a3)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ebx
  signed int *result; // eax
  _DWORD v9[6]; // [esp-8h] [ebp-40h] BYREF
  int v10; // [esp+10h] [ebp-28h] BYREF
  int v11; // [esp+18h] [ebp-20h]
  int v12; // [esp+1Ch] [ebp-1Ch]
  int v13; // [esp+20h] [ebp-18h]
  int v14; // [esp+30h] [ebp-8h]

  v14 = a2;
  if ( Lexer_TokenExpect(2) != -1
    && Lexer_ParseValueList(1, v9, 1, a3)
    && Lexer_ParseValueList(2, &v10, 4, a3)
    && (v5 = v12, v6 = *(_DWORD *)(v9[2] + 16), v6 <= v13 - v12 + 1)
    && v6 >= 1 )
  {
    v7 = v11;
    *(_DWORD *)(a1 + 4) = *(__int16 *)(v11 + 6 * (v12 + v6 - 1) + 14);
    result = *(signed int **)(v7 + 6 * (v12 + v6 - 1) + 16);
    *(_DWORD *)(a1 + 8) = result;
  }
  else
  {
    *(_DWORD *)(a1 + 4) = 2;
    result = Str_Intern(aNil_1, v5);
    *(_DWORD *)(a1 + 8) = result;
  }
  return result;
}
// 4A1B4C: variable 'v5' is possibly undefined

//----- (004A1B60) --------------------------------------------------------
signed int  Rules_SubsetpFunction(int a1, double a2)
{
  signed int result; // eax
  int v3; // ecx
  int v4; // esi
  int v5; // ecx
  _DWORD v6[6]; // [esp-18h] [ebp-40h] BYREF
  int v7; // [esp+0h] [ebp-28h] BYREF
  int v8; // [esp+8h] [ebp-20h]
  int v9; // [esp+Ch] [ebp-1Ch]
  int v10; // [esp+10h] [ebp-18h]
  int v11; // [esp+20h] [ebp-8h]

  v11 = a1;
  if ( Lexer_TokenExpect(2) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &v7, 4, a2);
  if ( result )
  {
    result = Lexer_ParseValueList(2, v6, 4, a2);
    if ( result )
    {
      v3 = v9 + 1;
      v4 = 6 * (v9 + 1) - 6;
      while ( v3 <= v10 + 1 )
      {
        result = Rules_MultifieldFindElementPosition(*(__int16 *)(v4 + v8 + 14), *(_DWORD *)(v4 + v8 + 16), v6);
        if ( !result )
          return result;
        v4 += 6;
        v3 = v5 + 1;
      }
      return 1;
    }
  }
  return result;
}
// 4A1C01: variable 'v5' is possibly undefined

//----- (004A1C10) --------------------------------------------------------
int * Rules_MemberFunction(int a1, int a2, double a3)
{
  int *result; // eax
  int v5; // [esp-4h] [ebp-40h] BYREF
  int v6; // [esp+0h] [ebp-3Ch]
  int v7; // [esp+4h] [ebp-38h]
  _DWORD v8[10]; // [esp+14h] [ebp-28h] BYREF

  v8[8] = a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_TokenExpect(2);
  if ( result != (int *)-1 )
  {
    Rules_RtnUnknown(1, &v5, a3);
    if ( v6 == 2 || v6 == 3 || v6 == 1 || v6 == 5 || v6 == 8 || v6 == 7 || !v6 )
    {
      result = (int *)Lexer_ParseValueList(2, v8, 4, a3);
      if ( result )
      {
        result = (int *)Rules_MultifieldFindElementPosition(v6, v7, v8);
        if ( result )
        {
          *(_DWORD *)(a1 + 4) = 1;
          result = Rules_AddIntegerValue((signed int)result);
          *(_DWORD *)(a1 + 8) = result;
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
int  Rules_MultifieldFindElementPosition(int a1, int a2, _DWORD *a3)
{
  int v6; // ebx
  int v7; // edx
  int i; // eax

  v6 = a3[4] - a3[3] + 1;
  v7 = 0;
  if ( v6 <= 0 )
    return 0;
  for ( i = a3[2] + 6 * a3[3]; a2 != *(_DWORD *)(i + 16) || a1 != *(__int16 *)(i + 14); i += 6 )
  {
    if ( ++v7 >= v6 )
      return 0;
  }
  return v7 + 1;
}

//----- (004A1D40) --------------------------------------------------------
int  Rules_ParsePrognMultifieldForm(int a1, int a2)
{
  int v4; // edx
  int v5; // ecx
  int v6; // esi
  int v7; // eax
  unsigned int *v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v15; // eax
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // [esp+0h] [ebp-28h] BYREF
  int v21; // [esp+4h] [ebp-24h]
  char *v22; // [esp+8h] [ebp-20h]
  int v23; // [esp+Ch] [ebp-1Ch]
  int v24; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_5070CC);
  Parser_NextToken(a2, v4);
  v6 = 0;
  if ( v20 != 100 )
  {
    v7 = Parser_ParseSingleExpression(a2, (__int16 *)&v20, v5);
    *(_DWORD *)(a1 + 6) = v7;
    if ( v7 )
      goto LABEL_3;
LABEL_17:
    AST_Free(a1);
    return 0;
  }
  Parser_NextToken(a2, (int)&v20);
  if ( v20 != 15 )
  {
    if ( v20 != 2 )
      goto LABEL_25;
    v15 = Parser_ParseFunctionCallExpr(a2, *(_BYTE **)(v21 + 16));
    *(_DWORD *)(a1 + 6) = v15;
    if ( v15 )
      goto LABEL_3;
    goto LABEL_17;
  }
  v6 = v21;
  IO_OutWriteToken(asc_5070CC);
  v17 = Parser_ParseSingleExpression(a2, 0, v16);
  *(_DWORD *)(a1 + 6) = v17;
  if ( !v17 )
    goto LABEL_17;
  Parser_NextToken(a2, (int)&v20);
  if ( v20 != 101 )
    goto LABEL_25;
  IO_OutNewline();
  IO_OutWriteToken(v22);
  IO_OutWriteToken(asc_5070CC);
LABEL_3:
  if ( Rules_ExpressionConstraintsCompatible(*(__int16 **)(a1 + 6)) )
  {
LABEL_25:
    Parser_ReportSyntaxError();
    AST_Free(a1);
    return 0;
  }
  v23 = Parser_GetLoopContextStack();
  v24 = v23;
  Parser_SetLoopContextStack(0);
  Rules_IncrementIndentDepth(3);
  g_ParserBreakContextFlag = 1;
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  AST_Append(0, (int)&v20);
  *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = Parser_ParseProgram(a2, v8, 1);
  Rules_DecrementIndentDepth(3);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(v22);
  v9 = *(_DWORD *)(a1 + 6);
  v10 = *(_DWORD *)(v9 + 10);
  if ( v10 )
  {
    v11 = *(_DWORD *)(v9 + 10);
    *(_DWORD *)(v9 + 10) = *(_DWORD *)(v10 + 6);
    *(_DWORD *)(v11 + 6) = 0;
    AST_Free(v11);
    v12 = Parser_GetLoopContextStack();
    v13 = 0;
    if ( v12 )
    {
      while ( !v6 || strcmp_(v12, *(_DWORD *)(v6 + 16)) )
      {
        v13 = v12;
        v12 = *(_DWORD *)(v12 + 8);
        if ( !v12 )
          goto LABEL_8;
      }
      Parser_FreeLoopContextStack();
      Parser_SetLoopContextStack(v24);
      Rules_PrintErrorID((int)aMultifun, v18, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRebindFi, v19);
      AST_Free(a1);
      return 0;
    }
    else
    {
LABEL_8:
      if ( v13 )
        *(_DWORD *)(v13 + 8) = v24;
      else
        Parser_SetLoopContextStack(v24);
      if ( v6 )
        Rules_RewritePrognFieldRefs(v6, *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10), 0);
      return a1;
    }
  }
  else
  {
    Parser_SetLoopContextStack(v23);
    AST_Free(a1);
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
int  Rules_RewritePrognFieldRefs(int a1, int a2, signed int a3)
{
  int v3; // esi
  const char *v5; // edi
  int result; // eax
  unsigned int v7; // ecx
  signed int v8; // edi
  int v9; // eax
  signed int v10; // ebx
  int *v11; // eax
  int *v12; // eax

  v3 = a2;
  v5 = *(const char **)(a1 + 16);
  result = 0;
  v7 = strlen(v5);
  if ( a2 )
  {
    v8 = a3 + 1;
    while ( *(_WORD *)v3 == 15 )
    {
      result = strncmp_(v7, *(_DWORD *)(a1 + 16)) == 0;
      if ( !result )
        break;
      if ( *(_BYTE *)(v7 + *(_DWORD *)(*(_DWORD *)(v3 + 2) + 16)) )
      {
        result = strcmp_(v7, aIndex);
        if ( result )
        {
LABEL_9:
          v3 = *(_DWORD *)(v3 + 10);
          if ( !v3 )
            return result;
        }
        else
        {
          *(_WORD *)v3 = 10;
          *(_DWORD *)(v3 + 2) = Rules_MakeSymbol(aGetPrognIndex);
          v12 = Rules_AddIntegerValue(a3);
          result = AST_NewNode(1, (int)v12);
          *(_DWORD *)(v3 + 6) = result;
          v3 = *(_DWORD *)(v3 + 10);
          if ( !v3 )
            return result;
        }
      }
      else
      {
        *(_WORD *)v3 = 10;
        *(_DWORD *)(v3 + 2) = Rules_MakeSymbol(aGetPrognField);
        v11 = Rules_AddIntegerValue(a3);
        result = AST_NewNode(1, (int)v11);
        *(_DWORD *)(v3 + 6) = result;
        v3 = *(_DWORD *)(v3 + 10);
        if ( !v3 )
          return result;
      }
    }
    if ( *(_DWORD *)(v3 + 6) )
    {
      if ( *(_WORD *)v3 == 10 && Rules_MakeSymbol(aProgn_0) == *(int ***)(v3 + 2) )
      {
        v9 = a1;
        v10 = v8;
      }
      else
      {
        v9 = a1;
        v10 = a3;
      }
      result = Rules_RewritePrognFieldRefs(v9, *(_DWORD *)(v3 + 6), v10);
    }
    goto LABEL_9;
  }
  return result;
}
// 4A2035: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004A20F0) --------------------------------------------------------
int  Rules_EvalPrognMultifieldBuiltin(_DWORD *a1, double a2)
{
  _DWORD *v3; // edx
  _DWORD *v4; // edi
  _DWORD *v5; // ebp
  int v6; // ebx
  int v7; // edi
  __int16 *v8; // ecx
  int v9; // ecx
  int result; // eax
  int v11; // [esp+0h] [ebp-34h] BYREF
  int v12; // [esp+8h] [ebp-2Ch]
  int v13; // [esp+Ch] [ebp-28h]
  int v14; // [esp+10h] [ebp-24h]
  int v15; // [esp+18h] [ebp-1Ch]

  v3 = *(_DWORD **)(g_ClipsMemoryTable + 64);
  if ( v3 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *v3;
    v4 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v4 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *v4 = 2;
  v4[1] = g_ClipsFalseSymbol;
  v4[3] = g_PrognFieldBindingStack;
  g_PrognFieldBindingStack = (int)v4;
  a1[1] = 2;
  a1[2] = g_ClipsFalseSymbol;
  v5 = v4;
  if ( Lexer_ParseValueList(1, &v11, 4, a2) )
  {
    v6 = v13 + 1;
    v15 = v14 + 1;
    if ( v13 + 1 > v14 + 1 )
    {
LABEL_18:
      g_ClipsBreakFlag = 0;
    }
    else
    {
      v7 = 6 * v6 - 6;
      while ( 1 )
      {
        *v5 = *(__int16 *)(v12 + v7 + 14);
        v5[1] = *(_DWORD *)(v12 + v7 + 16);
        v5[2] = v6;
        v8 = *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10);
        if ( v8 )
          break;
LABEL_17:
        ++v6;
        v7 += 6;
        if ( v6 > v15 )
          goto LABEL_18;
      }
      while ( 1 )
      {
        Parser_ParseForm(v8, a1, (int)v8, a2);
        if ( g_ClipsHaltExecution || g_ClipsBreakFlag || g_ClipsHaltExecutionFlag )
          break;
        v8 = *(__int16 **)(v9 + 10);
        if ( !v8 )
          goto LABEL_17;
      }
      g_ClipsBreakFlag = 0;
      if ( g_ClipsHaltExecution )
      {
        a1[1] = 2;
        a1[2] = g_ClipsFalseSymbol;
      }
    }
    g_PrognFieldBindingStack = v5[3];
    g_ClipsMemFreeListTemp = (int)v5;
    *v5 = *(_DWORD *)(g_ClipsMemoryTable + 64);
  }
  else
  {
    g_PrognFieldBindingStack = v4[3];
    g_ClipsMemFreeListTemp = (int)v4;
    *v4 = *(_DWORD *)(g_ClipsMemoryTable + 64);
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
int  Rules_EvalGetPrognFieldBuiltin(int a1)
{
  int v2; // eax
  _DWORD *i; // edx
  int result; // eax

  v2 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = (_DWORD *)g_PrognFieldBindingStack; v2 > 0; i = (_DWORD *)i[3] )
    --v2;
  *(_DWORD *)(a1 + 4) = *i;
  result = i[1];
  *(_DWORD *)(a1 + 8) = result;
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51ACD8: using guessed type int dword_51ACD8;

//----- (004A22D0) --------------------------------------------------------
int Rules_EvalGetPrognIndexBuiltin()
{
  int v0; // eax
  int i; // edx

  v0 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = g_PrognFieldBindingStack; v0 > 0; i = *(_DWORD *)(i + 12) )
    --v0;
  return *(_DWORD *)(i + 8);
}
// 4A22D0: using guessed type int sub_4A22D0();
// 51A960: using guessed type int dword_51A960;
// 51ACD8: using guessed type int dword_51ACD8;

//----- (004A2310) --------------------------------------------------------
signed int  Rules_MultifieldReplaceRange(
        _DWORD *a1,
        _DWORD *a2,
        int a3,
        int a4,
        _DWORD *a5,
        int a6)
{
  int v7; // eax
  int v9; // ecx
  int v10; // ebp
  int v11; // ecx
  int v12; // eax
  int v13; // ebx
  int v14; // edx
  int v15; // edx
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ebp
  __int16 v20; // di
  int v22; // ebx
  int v23; // ecx
  int v24; // ebx
  int v25; // ecx
  int v26; // edx
  int v27; // ebp
  int v28; // ebx
  int v29; // [esp+0h] [ebp-34h]
  int v30; // [esp+4h] [ebp-30h]
  int v31; // [esp+Ch] [ebp-28h]
  int v32; // [esp+14h] [ebp-20h]
  int v34; // [esp+18h] [ebp-1Ch]
  int v35; // [esp+1Ch] [ebp-18h]
  int v37; // [esp+24h] [ebp-10h]

  if ( a2 )
    v7 = a2[4] - a2[3] + 1;
  else
    v7 = 0;
  if ( a4 > a3 || a4 < 1 || a3 < 1 || a4 > v7 || v7 < a3 )
  {
    Rules_MultifieldIndexRangeError(a4, a3, v7);
    return 0;
  }
  else
  {
    v9 = a2[3];
    v10 = v9 + a4 - 1;
    v34 = v9 + a3 - 1;
    v11 = a3 - a4 + 1;
    if ( a5[1] == 4 )
      v12 = a5[4] - a5[3] + 1 + v7;
    else
      v12 = v7 + 1;
    v31 = v12 - v11;
    a1[1] = 4;
    a1[3] = 0;
    v13 = 0;
    a1[2] = Rules_CreateEphemeralMultifield(v12 - v11);
    a1[4] = v31 - 1;
    v15 = *(_DWORD *)(v14 + 12);
    v32 = 6 * v10;
    v16 = 0;
    v17 = 6 * v15;
    while ( 1 )
    {
      v35 = v16 + 1;
      if ( v17 >= v32 )
        break;
      v18 = a2[2];
      v19 = a1[2];
      v20 = *(_WORD *)(v17 + v18 + 14);
      v17 += 6;
      *(_WORD *)(v13 + v19 + 14) = v20;
      v13 += 6;
      ++v15;
      *(_DWORD *)(v13 + v19 + 10) = *(_DWORD *)(v17 + v18 + 10);
      v16 = v35;
    }
    if ( a5[1] == 4 )
    {
      v23 = a5[3];
      if ( v23 <= a5[4] )
      {
        v24 = 6 * v23;
        v37 = 6 * v16;
        do
        {
          v29 = a1[2] + 14 + v37;
          v30 = v24 + a5[2] + 14;
          *(_WORD *)v29 = *(_WORD *)v30;
          *(_DWORD *)(v29 + 2) = *(_DWORD *)(v30 + 2);
          v37 += 6;
          ++v23;
          ++v16;
          v24 += 6;
        }
        while ( v23 <= a5[4] );
      }
    }
    else
    {
      v22 = a1[2] + 14 + v13;
      *(_WORD *)v22 = *((_WORD *)a5 + 2);
      ++v16;
      *(_DWORD *)(v22 + 2) = a5[2];
    }
    while ( v15 < v34 )
      ++v15;
    if ( v16 < v31 )
    {
      v25 = 6 * (v15 + 1);
      v26 = 6 * v16;
      do
      {
        v27 = a2[2];
        v28 = a1[2];
        *(_WORD *)(v26 + v28 + 14) = *(_WORD *)(v25 + v27 + 14);
        v26 += 6;
        ++v16;
        *(_DWORD *)(v26 + v28 + 10) = *(_DWORD *)(v25 + v27 + 16);
        v25 += 6;
      }
      while ( v26 < 6 * v31 );
    }
    return 1;
  }
}
// 4A23D8: variable 'v14' is possibly undefined

//----- (004A2580) --------------------------------------------------------
signed int  Rules_MultifieldInsertRange(_DWORD *a1, _DWORD *a2, _DWORD *a3, int a4, int a5)
{
  int v7; // eax
  int v8; // edx
  int v9; // eax
  int v12; // eax
  signed int v13; // edx
  int v14; // edx
  int v15; // ebp
  int v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // ebp
  int v20; // ecx
  int v21; // ecx
  int v22; // ebp
  int v23; // ecx
  int v24; // ebp
  int v25; // [esp+4h] [ebp-2Ch]
  int v26; // [esp+4h] [ebp-2Ch]
  int v27; // [esp+4h] [ebp-2Ch]
  int v28; // [esp+8h] [ebp-28h]
  int v29; // [esp+8h] [ebp-28h]
  int v30; // [esp+Ch] [ebp-24h]
  int v32; // [esp+14h] [ebp-1Ch]
  int v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int v35; // [esp+20h] [ebp-10h]

  v28 = a4;
  if ( a2 )
    v7 = a2[4] - a2[3] + 1;
  else
    v7 = 0;
  v8 = v7;
  v9 = v7 + 1;
  if ( a4 < 1 )
  {
    Rules_MultifieldIndexRangeError(a4, a4, v9);
    return 0;
  }
  else
  {
    if ( v9 < a4 )
      v28 = v9;
    a1[1] = 4;
    a1[3] = 0;
    if ( a2 )
    {
      if ( a3[1] == 4 )
        v13 = a3[4] - a3[3] + 1 + v8;
      else
        v13 = v8 + 1;
      a1[2] = Rules_CreateEphemeralMultifield(v13);
      v15 = v28 - 1;
      a1[4] = v14 - 1;
      v29 = v15;
      v16 = a2[3];
      v17 = 0;
      if ( v16 < v15 )
      {
        v35 = 0;
        v18 = 6 * v16;
        v30 = 6 * v15;
        do
        {
          v19 = a1[2] + 14 + v35;
          v25 = v18 + a2[2] + 14;
          *(_WORD *)v19 = *(_WORD *)v25;
          ++v17;
          ++v16;
          *(_DWORD *)(v19 + 2) = *(_DWORD *)(v25 + 2);
          v18 += 6;
          v35 += 6;
        }
        while ( v18 < v30 );
      }
      if ( a3[1] == 4 )
      {
        v23 = a3[3];
        if ( v23 <= a3[4] )
        {
          v32 = 6 * v23;
          v33 = 6 * v17;
          do
          {
            v27 = a3[2] + 14 + v32;
            v24 = a1[2] + 14 + v33;
            *(_WORD *)v24 = *(_WORD *)v27;
            *(_DWORD *)(v24 + 2) = *(_DWORD *)(v27 + 2);
            v32 += 6;
            ++v23;
            v33 += 6;
            ++v17;
          }
          while ( v23 <= a3[4] );
        }
      }
      else
      {
        v20 = a1[2] + 14 + 6 * v29;
        *(_WORD *)v20 = *((_WORD *)a3 + 2);
        ++v17;
        *(_DWORD *)(v20 + 2) = a3[2];
      }
      v21 = 6 * v16;
      v34 = 6 * v17;
      while ( v16 <= a2[4] )
      {
        v22 = a1[2] + 14 + v34;
        v26 = v21 + a2[2] + 14;
        *(_WORD *)v22 = *(_WORD *)v26;
        ++v17;
        *(_DWORD *)(v22 + 2) = *(_DWORD *)(v26 + 2);
        ++v16;
        v21 += 6;
        v34 += 6;
      }
    }
    else if ( a3[1] == 4 )
    {
      Rules_AssignMultifieldRangeCopy(a1, (int)a3);
      Rules_RegisterEphemeralMultifield(a1[2]);
    }
    else
    {
      a1[2] = Rules_CreateEphemeralMultifield(0);
      a1[4] = 0;
      v12 = a1[2];
      *(_WORD *)(v12 + 14) = *((_WORD *)a3 + 2);
      *(_DWORD *)(v12 + 16) = a3[2];
    }
    return 1;
  }
}
// 4A2655: variable 'v14' is possibly undefined

//----- (004A2810) --------------------------------------------------------
signed int  Rules_MultifieldIndexRangeError(int a1, int a2, int a3)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ecx
  int v15; // ecx

  Rules_PrintErrorID((int)aMultifun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMultifieldInde, v5);
  if ( a1 == a2 )
  {
    v9 = a1;
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aRange, v6);
    Rules_PrintLongInteger(v7, a1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__, v8);
    v9 = a2;
  }
  Rules_PrintLongInteger(v6, v9);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutOfRange1__, v10);
  Rules_PrintLongInteger(v11, a3);
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
signed int  Rules_MultifieldDeleteRange(_DWORD *a1, _DWORD *a2, int a3, int a4, int a5)
{
  int v6; // eax
  int v7; // edi
  signed int v8; // eax
  int v9; // edx
  int v10; // edx
  int v11; // eax
  int v12; // ebx
  int v13; // ecx
  int v14; // edx
  _DWORD *v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // ebp
  int v20; // ebx
  int v21; // ebx
  int v22; // [esp+0h] [ebp-24h]
  int v23; // [esp+4h] [ebp-20h]
  int v24; // [esp+10h] [ebp-14h]

  if ( a2 )
    v6 = a2[4] - a2[3] + 1;
  else
    v6 = 0;
  if ( a3 < a4 || a4 < 1 || a3 < 1 || v6 < a4 || v6 < a3 )
  {
    Rules_MultifieldIndexRangeError(a4, a3, v6);
    return 0;
  }
  a1[1] = 4;
  a1[3] = 0;
  if ( !v6 )
  {
    v16 = Rules_CreateEphemeralMultifield(0);
    a1[4] = -1;
    v14 = 1;
    a1[2] = v16;
    return v14;
  }
  v7 = a4 + a2[3] - 1;
  v24 = a3 + a2[3] - 1;
  v8 = v6 - (a3 + a2[3] - v7);
  a1[4] = v8 - 1;
  a1[2] = Rules_CreateEphemeralMultifield(v8);
  v10 = *(_DWORD *)(v9 + 12);
  v11 = 0;
  if ( v10 < v7 )
  {
    v12 = 0;
    v13 = 6 * v10;
    do
    {
      v22 = v12 + a1[2] + 14;
      v23 = v13 + a2[2] + 14;
      ++v11;
      *(_WORD *)v22 = *(_WORD *)v23;
      ++v10;
      v13 += 6;
      *(_DWORD *)(v22 + 2) = *(_DWORD *)(v23 + 2);
      v12 += 6;
    }
    while ( v13 < 6 * v7 );
  }
  while ( v10 < v24 )
    ++v10;
  if ( v11 <= a1[4] )
  {
    v17 = 6 * (v10 + 1);
    v18 = 6 * v11;
    do
    {
      v19 = a1[2] + 14 + v18;
      v20 = a2[2];
      *(_WORD *)v19 = *(_WORD *)(v17 + v20 + 14);
      v21 = *(_DWORD *)(v17 + v20 + 16);
      v17 += 6;
      *(_DWORD *)(v19 + 2) = v21;
      ++v11;
      v18 += 6;
    }
    while ( v11 <= a1[4] );
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
signed int  Rules_StrCatBuiltin(int a1, int a2, double a3)
{
  return Rules_ConcatBuiltinCore(a1, 3, a2, a3);
}

//----- (004A2C00) --------------------------------------------------------
signed int  Rules_SymCatBuiltin(int a1, int a2, double a3)
{
  return Rules_ConcatBuiltinCore(a1, 2, a2, a3);
}

//----- (004A2C40) --------------------------------------------------------
signed int  Rules_ConcatBuiltinCore(int a1, int a2, int a3, double a4)
{
  signed int *v4; // eax
  int v5; // edx
  _BYTE *v6; // eax
  int v7; // esi
  int v8; // edx
  _BYTE *v9; // ebp
  char *v10; // eax
  int v11; // ecx
  signed int *v12; // eax
  unsigned int v13; // kr04_4
  int v14; // ebx
  int v15; // ebp
  int v16; // ecx
  char *v17; // esi
  int v18; // edx
  const char **v19; // edx
  signed int *v20; // eax
  int v21; // edx
  char *v23; // ecx
  int v24; // [esp+0h] [ebp-40h] BYREF
  int v25; // [esp+4h] [ebp-3Ch]
  int v26; // [esp+8h] [ebp-38h]
  const char **v27; // [esp+18h] [ebp-28h]
  int v28; // [esp+1Ch] [ebp-24h]
  char *v29; // [esp+20h] [ebp-20h]
  unsigned int v30; // [esp+24h] [ebp-1Ch]
  int v31; // [esp+28h] [ebp-18h]

  v28 = a1;
  *(_DWORD *)(a1 + 4) = a2;
  if ( a2 == 3 )
  {
    v4 = Str_Intern(g_Rules_EmptyStringLiteral, (int)aStrCat);
    v29 = v23;
  }
  else
  {
    v29 = aSymCat;
    v4 = Str_Intern(aNil_4, a3);
  }
  *(_DWORD *)(v5 + 8) = v4;
  v31 = Rules_RtnArgCount();
  v6 = Mem_SmallBlockAllocZeroed(4 * v31);
  v30 = 1;
  v7 = 1;
  v27 = (const char **)v6;
  if ( v8 < 1 )
  {
LABEL_11:
    v14 = 0;
    v15 = 0;
    v17 = (char *)Mem_SmallBlockAlloc(v30);
    if ( v18 > 0 )
    {
      v19 = v27;
      do
      {
        sprintf_(&v17[v14], "%s", *v19);
        ++v15;
        v16 = strlen(*(v19 - 1));
        v14 += v16;
      }
      while ( v15 < v31 );
    }
    v20 = Str_Intern(v17, v16);
    *(_DWORD *)(v21 + 8) = v20;
    Mem_SmallBlockFree(v17, v30);
  }
  else
  {
    v9 = v6 + 4;
    while ( 1 )
    {
      Rules_RtnUnknown(v7, &v24, a4);
      switch ( v25 )
      {
        case 0:
          v10 = (char *)Rules_FloatToSymbol(v25, *(double *)(v26 + 16));
          goto LABEL_7;
        case 1:
          v10 = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(v26 + 16));
LABEL_7:
          v12 = Str_Intern(v10, v11);
          goto LABEL_8;
        case 2:
        case 3:
        case 8:
          v12 = (signed int *)v26;
LABEL_8:
          *((_DWORD *)v9 - 1) = v12[4];
          break;
        default:
          Parser_ReportError(v7, (int)aStringInstance);
          Lexer_ErrorRecover(1);
          break;
      }
      if ( g_ClipsEvaluationError )
        break;
      v13 = strlen(*((const char **)v9 - 1)) + 1;
      v9 += 4;
      ++v7;
      v30 += v13 - 1;
      if ( v7 > v31 )
        goto LABEL_11;
    }
  }
  return Mem_SmallBlockFree(v27, 4 * v31);
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
int  Rules_StrLengthBuiltin(int a1, double a2)
{
  int result; // eax
  _DWORD v3[9]; // [esp-8h] [ebp-24h] BYREF

  v3[7] = a1;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    if ( Lexer_ParseValueList(1, v3, 111, a2) )
      return strlen(*(const char **)(v3[2] + 16));
    else
      return -1;
  }
  return result;
}

//----- (004A2E60) --------------------------------------------------------
signed int * Rules_UpcaseBuiltin(int a1, double a2)
{
  int v3; // ecx
  signed int v4; // kr04_4
  signed int v5; // ebx
  char *v6; // eax
  _BYTE *v7; // edx
  char *v8; // ecx
  int v9; // eax
  int v10; // edx
  signed int *result; // eax
  _DWORD v12[7]; // [esp+0h] [ebp-30h] BYREF
  char *v13; // [esp+1Ch] [ebp-14h]

  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, v12, 111, a2) )
  {
    *(_DWORD *)(a1 + 4) = 3;
    result = Str_Intern(g_Rules_EmptyStringLiteral, v3);
    *(_DWORD *)(a1 + 8) = result;
  }
  else
  {
    v4 = strlen(*(const char **)(v12[2] + 16)) + 1;
    v5 = 0;
    v6 = (char *)Mem_SmallBlockAlloc(v4);
    v13 = v6;
    if ( v4 > 0 )
    {
      v8 = v6;
      do
      {
        if ( IsTable[(unsigned __int8)(*v7 + 1)] >= 0 )
        {
          LOBYTE(v9) = *v7;
        }
        else
        {
          v9 = toupper_(v8);
          v12[6] = v9;
        }
        *v8++ = v9;
        ++v5;
        ++v7;
      }
      while ( v5 < v4 );
    }
    *(_DWORD *)(a1 + 4) = v12[1];
    *(_DWORD *)(a1 + 8) = Str_Intern(v13, (int)v8);
    return (signed int *)Mem_SmallBlockFree(v13, v10);
  }
  return result;
}
// 4A2ECC: variable 'v7' is possibly undefined
// 4A2EED: variable 'v8' is possibly undefined
// 4A2F0F: variable 'v10' is possibly undefined
// 4A2F2A: variable 'v3' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004A2F40) --------------------------------------------------------
signed int * Rules_LowcaseBuiltin(int a1, double a2)
{
  int v3; // ecx
  signed int v4; // kr04_4
  signed int v5; // ebx
  char *v6; // eax
  _BYTE *v7; // edx
  char *v8; // ecx
  int v9; // eax
  int v10; // edx
  signed int *result; // eax
  _DWORD v12[7]; // [esp+0h] [ebp-30h] BYREF
  char *v13; // [esp+1Ch] [ebp-14h]

  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, v12, 111, a2) )
  {
    *(_DWORD *)(a1 + 4) = 3;
    result = Str_Intern(g_Rules_EmptyStringLiteral, v3);
    *(_DWORD *)(a1 + 8) = result;
  }
  else
  {
    v4 = strlen(*(const char **)(v12[2] + 16)) + 1;
    v5 = 0;
    v6 = (char *)Mem_SmallBlockAlloc(v4);
    v13 = v6;
    if ( v4 > 0 )
    {
      v8 = v6;
      do
      {
        if ( (IsTable[(unsigned __int8)(*v7 + 1)] & 0x40) != 0 )
        {
          v9 = tolower_(v8, v7);
          v12[6] = v9;
        }
        else
        {
          LOBYTE(v9) = *v7;
        }
        *v8++ = v9;
        ++v5;
        ++v7;
      }
      while ( v5 < v4 );
    }
    *(_DWORD *)(a1 + 4) = v12[1];
    *(_DWORD *)(a1 + 8) = Str_Intern(v13, (int)v8);
    return (signed int *)Mem_SmallBlockFree(v13, v10);
  }
  return result;
}
// 4A2FAC: variable 'v7' is possibly undefined
// 4A2FCD: variable 'v8' is possibly undefined
// 4A2FEF: variable 'v10' is possibly undefined
// 4A300A: variable 'v3' is possibly undefined
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004A3020) --------------------------------------------------------
signed int  Rules_StrCompareBuiltin(int a1, double a2)
{
  int v2; // esi
  signed int result; // eax
  int v4; // ecx
  int v5; // ecx
  double v6; // st7
  int v7; // [esp-4h] [ebp-5Ch] BYREF
  int v8; // [esp+0h] [ebp-58h]
  int v9; // [esp+4h] [ebp-54h]
  int v10; // [esp+14h] [ebp-44h] BYREF
  int v11; // [esp+2Ch] [ebp-2Ch] BYREF
  int v12; // [esp+34h] [ebp-24h]
  int v13; // [esp+44h] [ebp-14h]
  int v14; // [esp+50h] [ebp-8h]

  v14 = a1;
  v2 = Rules_ArgRangeCheck((int)aStrCompare, 3);
  if ( v2 == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &v10, 111, a2);
  if ( result )
  {
    result = Lexer_ParseValueList(2, &v11, 111, a2);
    if ( result )
    {
      if ( v2 == 3 )
      {
        result = Lexer_ParseValueList(3, &v7, 1, a2);
        if ( !result )
          return result;
        if ( v8 == 1 )
        {
          v13 = *(_DWORD *)(v9 + 16);
        }
        else
        {
          v6 = *(double *)(v9 + 16);
          _CHP(v7, v8);
          v13 = (int)v6;
        }
        result = strncmp_(v5, *(_DWORD *)(v12 + 16));
      }
      else
      {
        result = strcmp_(v4, *(_DWORD *)(v12 + 16));
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
  int v2; // ebp
  int v3; // esi
  _DWORD *v4; // eax
  int v5; // ecx
  char *v6; // edi
  char *v7; // edx
  char v8; // bl
  int v9; // edx
  int v10; // ecx
  int v12; // [esp+0h] [ebp-38h] BYREF
  int v13; // [esp+4h] [ebp-34h]
  int v14; // [esp+8h] [ebp-30h]
  int v15; // [esp+18h] [ebp-20h]
  int v16; // [esp+1Ch] [ebp-1Ch]

  if ( Lexer_TokenExpect(3) == -1 || !Lexer_ParseValueList(1, &v12, 1, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  if ( v13 == 1 )
  {
    v16 = *(_DWORD *)(v14 + 16);
  }
  else
  {
    a1 = *(double *)(v14 + 16);
    _CHP(v12, v13);
    v16 = (int)a1;
  }
  v2 = v16 - 1;
  if ( !Lexer_ParseValueList(2, &v12, 1, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  if ( v13 == 1 )
  {
    v15 = *(_DWORD *)(v14 + 16);
  }
  else
  {
    a1 = *(double *)(v14 + 16);
    _CHP(v12, v13);
    v15 = (int)a1;
  }
  v3 = v15 - 1;
  if ( !Lexer_ParseValueList(3, &v12, 111, a1) )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  if ( v2 < 0 )
    v2 = 0;
  v1 = strlen(*(const char **)(v14 + 16));
  if ( v3 > v1 )
  {
    v1 = strlen(*(const char **)(v14 + 16));
    v3 = v1;
  }
  if ( v2 > v3 )
    return Str_Intern(g_Rules_EmptyStringLiteral, v1);
  v4 = Mem_SmallBlockAlloc(v3 - v2 + 2);
  v5 = v2;
  v6 = (char *)v4;
  v7 = (char *)(v2 + *(_DWORD *)(v14 + 16));
  do
  {
    v4 = (_DWORD *)((char *)v4 + 1);
    v8 = *v7++;
    ++v5;
    *((_BYTE *)v4 - 1) = v8;
  }
  while ( v5 <= v3 );
  *(_BYTE *)v4 = 0;
  Str_Intern(v6, v5);
  Mem_SmallBlockFree(v6, v9 - v2 + 2);
  return (signed int *)v10;
}
// 4A323C: variable 'v9' is possibly undefined
// 4A324A: variable 'v10' is possibly undefined
// 4A325B: variable 'v1' is possibly undefined

//----- (004A32A0) --------------------------------------------------------
int * Rules_StrIndexBuiltin(int a1, double a2)
{
  int *result; // eax
  const char *v3; // ebp
  _BYTE *v4; // esi
  signed int v5; // edi
  _BYTE *v6; // edx
  int v7; // ecx
  char v8; // bh
  const char *v10; // edi
  int v11; // edx
  int v12; // edx
  int v13; // [esp+0h] [ebp-4Ch] BYREF
  int v14; // [esp+8h] [ebp-44h]
  int v15; // [esp+18h] [ebp-34h] BYREF
  int v16; // [esp+20h] [ebp-2Ch]
  int v17; // [esp+30h] [ebp-1Ch]

  v17 = a1;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(v17 + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_TokenExpect(2);
  if ( result != (int *)-1 )
  {
    result = (int *)Lexer_ParseValueList(1, &v13, 111, a2);
    if ( result )
    {
      result = (int *)Lexer_ParseValueList(2, &v15, 111, a2);
      if ( result )
      {
        v3 = *(const char **)(v14 + 16);
        v4 = *(_BYTE **)(v16 + 16);
        result = 0;
        if ( strlen(v3) )
        {
          BYTE1(result) = *v4;
          v5 = 1;
          if ( *v4 )
          {
            while ( 1 )
            {
              result = *(int **)(v14 + 16);
              v6 = v4;
              v7 = 0;
              if ( *v3 )
              {
                do
                {
                  if ( *(_BYTE *)result != *v6 )
                    break;
                  ++v6;
                  v8 = *((_BYTE *)result + 1);
                  result = (int *)((char *)result + 1);
                  ++v7;
                }
                while ( v8 );
              }
              if ( !v3[v7] )
                break;
              ++v5;
              if ( !*++v4 )
                return result;
            }
            *(_DWORD *)(v17 + 4) = 1;
            result = Rules_AddIntegerValue(v5);
            *(_DWORD *)(v12 + 8) = result;
          }
        }
        else
        {
          v10 = *(const char **)(v16 + 16);
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
int  Rules_EvalBuiltin(_DWORD *a1, int a2, double a3)
{
  int result; // eax
  int v6; // ecx
  _DWORD v7[10]; // [esp-8h] [ebp-28h] BYREF

  v7[8] = a2;
  if ( Lexer_TokenExpect(1) != -1 && Lexer_ParseValueList(1, v7, 111, a3) )
    return Rules_EvalStringCore(v6, a1);
  a1[1] = 2;
  result = g_ClipsFalseSymbol;
  a1[2] = g_ClipsFalseSymbol;
  return result;
}
// 4A3429: variable 'v6' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004A3440) --------------------------------------------------------
BOOL __fastcall Rules_EvalStringCore(_DWORD a1, _DWORD *a2)
{
  double v3; // st7
  const char *v4; // ecx
  BOOL result; // eax
  int v6; // ebx
  int v7; // edi
  __int16 *v8; // edx
  int v9; // ecx
  int v10; // ebp
  _WORD *v11; // ecx
  __int16 *v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE v17[40]; // [esp+0h] [ebp-28h] BYREF

  v3 = sprintf_(v17, "Eval-%d", ++g_EvalStringRouterCounter);
  if ( IO_OpenStringSource((int)v17, v4, 0) )
  {
    v6 = Rules_GetPPBufferStatus();
    Rules_SetPPBufferStatus(0);
    v7 = Parser_GetLoopContextStack();
    Parser_SetLoopContextStack(0);
    v10 = Parser_ParseSingleExpression((int)v17, v8, v9);
    Rules_SetPPBufferStatus(v6);
    Parser_FreeLoopContextStack();
    Parser_SetLoopContextStack(v7);
    if ( v11 )
    {
      if ( *v11 == 14 || *v11 == 16 )
      {
        Rules_PrintErrorID((int)aMiscfun_0, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpandMustBe_0, v14);
        Lexer_ErrorRecover(1);
        IO_CloseStringRouter((int)v17);
        a2[1] = 2;
        a2[2] = g_ClipsFalseSymbol;
        AST_Free(v10);
        result = 0;
        --g_EvalStringRouterCounter;
      }
      else if ( AST_TreeContainsSpecialTag((int)v11, 0) )
      {
        Rules_PrintErrorID((int)aStrngfun, 2, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSomeVariablesC, v15);
        Lexer_ErrorRecover(1);
        IO_CloseStringRouter((int)v17);
        a2[1] = 2;
        a2[2] = g_ClipsFalseSymbol;
        AST_Free(v16);
        result = 0;
        --g_EvalStringRouterCounter;
      }
      else
      {
        Parser_ParseForm(v12, a2, (int)v12, v3);
        --g_EvalStringRouterCounter;
        AST_Free(v13);
        IO_CloseStringRouter((int)v17);
        return Rules_GetHaltExecutionFlag() == 0;
      }
    }
    else
    {
      Lexer_ErrorRecover(1);
      IO_CloseStringRouter((int)v17);
      a2[1] = 2;
      a2[2] = g_ClipsFalseSymbol;
      result = 0;
      --g_EvalStringRouterCounter;
    }
  }
  else
  {
    a2[1] = 2;
    a2[2] = g_ClipsFalseSymbol;
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
signed int  Rules_BuildBuiltin(int a1, double a2)
{
  signed int result; // eax
  _DWORD v3[9]; // [esp-8h] [ebp-24h] BYREF

  v3[7] = a1;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, v3, 111, a2);
  if ( result )
    return Rules_BuildConstructFromString(*(const char **)(v3[2] + 16));
  return result;
}

//----- (004A36B0) --------------------------------------------------------
signed int  Rules_BuildConstructFromString(const char *a1)
{
  signed int result; // eax
  signed int v2; // ebx
  int v3; // ecx
  int v4; // edx
  char *v5; // eax
  int v6; // ecx
  int v7; // [esp+0h] [ebp-14h] BYREF

  if ( g_Rules_JoinOperationInProgress )
    return 0;
  result = IO_OpenStringSource((int)aBuild, a1, 0);
  if ( result )
  {
    Parser_NextToken((int)aBuild, (int)&v7);
    if ( v7 != 100 || (Parser_NextToken((int)aBuild, (int)&v7), v7 != 2) )
    {
      IO_CloseStringRouter((int)aBuild);
      return 0;
    }
    v2 = Rules_ParseConstruct();
    IO_CloseStringRouter((int)aBuild);
    if ( v4 == 1 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aError_3, v3);
      v5 = (char *)Rules_GetPPBuffer();
      Output_WriteLongString((signed int)g_IO_LogicalNameTable_WError[0], v5);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_507374, v6);
    }
    Rules_DestroyPPBuffer();
    return !v2;
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
signed int  Rules_MathParseSingleArg(double *a1, int a2, double a3)
{
  signed int result; // eax
  _DWORD v5[10]; // [esp-8h] [ebp-28h] BYREF

  v5[8] = a2;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, v5, 0, a3);
  if ( result )
  {
    result = 1;
    *a1 = *(double *)(v5[2] + 16);
  }
  return result;
}

//----- (004A3C20) --------------------------------------------------------
BOOL __stdcall Rules_MathIsNearZero(double a1, double a2)
{
  return -a2 <= a1 && a1 <= a2;
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
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return cos(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A3DB0) --------------------------------------------------------
double  Rules_SinBuiltin(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return sin(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A3DF0) --------------------------------------------------------
double  Rules_TanBuiltin(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double v6; // [esp+0h] [ebp-20h] BYREF
  long double v7; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  v7 = cos(v6);
  if ( v7 >= g_Rules_TanEpsilonPositive || v7 <= g_Rules_TanEpsilonNegative )
    return sin(v6) / v7;
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
  long double v6; // [esp+0h] [ebp-20h] BYREF
  long double v7; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  v7 = cos(v6);
  if ( v7 >= g_Rules_SecEpsilonPositive || v7 <= g_Rules_SecDomainEpsilonNeg )
    return 1.0 / v7;
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
  long double v6; // [esp+0h] [ebp-20h] BYREF
  long double v7; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  v7 = sin(v6);
  if ( v7 >= g_Rules_CscDomainEpsilonPos || v7 <= g_Rules_CscDomainEpsilonNeg )
    return 1.0 / v7;
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
  long double v6; // [esp+0h] [ebp-20h] BYREF
  long double v7; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  v7 = sin(v6);
  if ( v7 >= g_Rules_CotDomainEpsilonPos || v7 <= g_Rules_CotDomainEpsilonNeg )
    return cos(v6) / v7;
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
  double v7; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v7, a3, a4) )
    return 0.0;
  if ( v7 <= 1.0 && v7 >= g_Rules_AcosDomainLowerBound )
    return acos(v7);
  Rules_MathDomainError();
  return 0.0;
}
// 507738: using guessed type double dbl_507738;

//----- (004A4060) --------------------------------------------------------
double  Rules_AsinBuiltin(int a1, int a2, int a3, double a4)
{
  double v7; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v7, a3, a4) )
    return 0.0;
  if ( v7 <= 1.0 && v7 >= g_Rules_AsinDomainLowerBound )
    return asin(v7);
  Rules_MathDomainError();
  return 0.0;
}
// 507740: using guessed type double dbl_507740;

//----- (004A40D0) --------------------------------------------------------
double  Rules_AtanBuiltin(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return atan2(v5[0], 1.0);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A4110) --------------------------------------------------------
double  Rules_AsecBuiltin(int a1, int a2, int a3, double a4)
{
  double v7; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v7, a3, a4) )
    return 0.0;
  if ( v7 >= 1.0 || v7 <= g_Rules_AsecDomainLowerBound )
    return acos(1.0 / v7);
  Rules_MathDomainError();
  return 0.0;
}
// 507748: using guessed type double dbl_507748;

//----- (004A4180) --------------------------------------------------------
double  Rules_AcscBuiltin(int a1, int a2, int a3, double a4)
{
  double v7; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+10h] [ebp-8h]
  int v10; // [esp+14h] [ebp-4h]

  v10 = a1;
  v9 = a2;
  if ( !Rules_MathParseSingleArg(&v7, a3, a4) )
    return 0.0;
  if ( v7 >= 1.0 || v7 <= g_Rules_AcscDomainLowerBound )
    return asin(1.0 / v7);
  Rules_MathDomainError();
  return 0.0;
}
// 507750: using guessed type double dbl_507750;

//----- (004A41F0) --------------------------------------------------------
double  Rules_AcotBuiltin(int a1, int a2, int a3, double a4)
{
  double v5; // [esp+0h] [ebp-1Ch] BYREF
  double v6; // [esp+8h] [ebp-14h]
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( Rules_MathParseSingleArg(&v5, a3, a4) )
  {
    if ( Rules_MathIsNearZero(v5, 1.0e-25) )
    {
      v6 = 1.570796326794897;
      return 1.570796326794897;
    }
    else
    {
      return atan2(1.0 / v5, 1.0);
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
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return cosh(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A42C0) --------------------------------------------------------
double  Rules_SinhBuiltin(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return sinh(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A4300) --------------------------------------------------------
double  Rules_MathTanh(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return tanh(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A4340) --------------------------------------------------------
double  Rules_MathSech(int a1, int a2, int a3, double a4)
{
  double v6[2]; // [esp+0h] [ebp-18h] BYREF
  int v7; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  v8 = a1;
  v7 = a2;
  if ( Rules_MathParseSingleArg(v6, a3, a4) )
    return 1.0 / cosh(v6[0]);
  v6[1] = 0.0;
  return 0.0;
}

//----- (004A4390) --------------------------------------------------------
double  Rules_MathCsch(int a1, int a2, int a3, double a4)
{
  double v6; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+14h] [ebp-Ch]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a3;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( (HIDWORD(v6) & 0x7FFFFFFF) == 0 && !LODWORD(v6) )
  {
    Rules_MathSingularityError();
    return 0.0;
  }
  if ( !Rules_MathIsNearZero(v6, 1.0e-25) )
    return 1.0 / sinh(v6);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A4440) --------------------------------------------------------
double  Rules_MathCoth(int a1, int a2, int a3, double a4)
{
  double v6; // [esp+0h] [ebp-20h] BYREF
  int v8; // [esp+14h] [ebp-Ch]
  int v9; // [esp+18h] [ebp-8h]
  int v10; // [esp+1Ch] [ebp-4h]

  v10 = a1;
  v9 = a3;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( (HIDWORD(v6) & 0x7FFFFFFF) == 0 && !LODWORD(v6) )
  {
    Rules_MathSingularityError();
    return 0.0;
  }
  if ( !Rules_MathIsNearZero(v6, 1.0e-25) )
    return 1.0 / tanh(v6);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A44F0) --------------------------------------------------------
double  Rules_MathAcosh(int a1, int a2, int a3, double a4)
{
  double v6; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( v6 >= 1.0 )
    return acosh(v6);
  Rules_MathDomainError();
  return 0.0;
}
// 507758: using guessed type double dbl_507758;

//----- (004A4560) --------------------------------------------------------
double  Rules_MathAsinh(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return asinh(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A45B0) --------------------------------------------------------
double  Rules_MathAtanh(int a1, int a2, int a3, double a4)
{
  double v6; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( v6 < 1.0 && v6 > g_Rules_AtanhDomainLowerBound )
    return atanh(v6);
  Rules_MathDomainError();
  return 0.0;
}
// 507760: using guessed type double dbl_507760;
// 507768: using guessed type double dbl_507768;

//----- (004A4630) --------------------------------------------------------
double  Rules_MathAsech(int a1, int a2, int a3, double a4)
{
  double v6; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( v6 <= 1.0 && v6 > 0.0 )
    return acosh(1.0 / v6);
  Rules_MathDomainError();
  return 0.0;
}
// 507770: using guessed type double dbl_507770;

//----- (004A46B0) --------------------------------------------------------
double  Rules_MathAcsch(int a1, int a2, int a3, double a4)
{
  double v5; // [esp+0h] [ebp-1Ch] BYREF
  int v7; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( !Rules_MathParseSingleArg(&v5, a3, a4) )
    return 0.0;
  if ( (HIDWORD(v5) & 0x7FFFFFFF) != 0 || LODWORD(v5) )
    return asinh(1.0 / v5);
  Rules_MathDomainError();
  return 0.0;
}

//----- (004A4730) --------------------------------------------------------
double  Rules_MathAcoth(int a1, int a2, int a3, double a4)
{
  double v6; // [esp+0h] [ebp-18h] BYREF
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( v6 > 1.0 || v6 < g_Rules_AcothDomainLowerBound )
    return atanh(1.0 / v6);
  Rules_MathDomainError();
  return 0.0;
}
// 507778: using guessed type double dbl_507778;
// 507780: using guessed type double dbl_507780;

//----- (004A47B0) --------------------------------------------------------
double  Rules_MathExp(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return exp(v5[0]);
  v5[1] = 0.0;
  return 0.0;
}

//----- (004A4800) --------------------------------------------------------
double  Rules_MathLog(int a1, int a2, int a3, double a4)
{
  double v5; // [esp+0h] [ebp-18h] BYREF
  int v7; // [esp+8h] [ebp-Ch]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( !Rules_MathParseSingleArg(&v5, a3, a4) )
    return 0.0;
  if ( v5 < 0.0 )
  {
    Rules_MathDomainError();
    return 0.0;
  }
  if ( v5 != 0.0 )
    return log(v5);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A4890) --------------------------------------------------------
double  Rules_MathLog10(int a1, int a2, int a3, double a4)
{
  double v5; // [esp+0h] [ebp-18h] BYREF
  int v7; // [esp+8h] [ebp-Ch]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a3;
  v7 = a2;
  if ( !Rules_MathParseSingleArg(&v5, a3, a4) )
    return 0.0;
  if ( v5 < 0.0 )
  {
    Rules_MathDomainError();
    return 0.0;
  }
  if ( v5 != 0.0 )
    return log10(v5);
  Rules_MathArgumentOverflowError();
  return 0.0;
}

//----- (004A4920) --------------------------------------------------------
double  Rules_MathSqrt(int a1, int a2, int a3, double a4)
{
  int v5; // edx
  long double v6; // [esp+0h] [ebp-18h] BYREF
  double v7; // [esp+8h] [ebp-10h]
  int v8; // [esp+10h] [ebp-8h]
  int v9; // [esp+14h] [ebp-4h]

  v9 = a1;
  v8 = a2;
  if ( !Rules_MathParseSingleArg(&v6, a3, a4) )
    return 0.0;
  if ( v6 >= 0.0 )
    return sqrt(v6);
  Rules_MathDomainError();
  LODWORD(v7) = v5;
  HIDWORD(v7) = v5;
  return v7;
}
// 4A4968: variable 'v5' is possibly undefined

//----- (004A4980) --------------------------------------------------------
double  Rules_MathPow(double a1)
{
  signed int v2; // eax
  int v4; // [esp+0h] [ebp-58h] BYREF
  int v5; // [esp+8h] [ebp-50h]
  int v6; // [esp+18h] [ebp-40h] BYREF
  int v7; // [esp+20h] [ebp-38h]
  double v8; // [esp+30h] [ebp-28h]
  double v9; // [esp+38h] [ebp-20h]
  double v10; // [esp+40h] [ebp-18h]

  if ( Lexer_TokenExpect(2) == -1 )
    return 0.0;
  v2 = Lexer_ParseValueList(1, &v4, 0, a1);
  if ( !v2 )
    return 0.0;
  v2 = Lexer_ParseValueList(2, &v6, 0, a1);
  if ( !v2 )
    return 0.0;
  v8 = *(double *)(v5 + 16);
  v9 = *(double *)(v7 + 16);
  if ( v8 == 0.0 && v9 <= 0.0 )
    goto LABEL_10;
  if ( v8 < 0.0 )
  {
    if ( v9 >= 0.0 )
      v10 = floor(v9);
    else
      v10 = ceil(v9);
    if ( v10 != v9 )
      goto LABEL_10;
  }
  return pow(v8, v9);
LABEL_10:
  Rules_MathDomainError();
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  return 0.0;
}

//----- (004A4AE0) --------------------------------------------------------
int * Rules_MathMod(int a1, double a2)
{
  signed int v3; // eax
  int *result; // eax
  signed int v7; // eax
  int v10; // [esp+8h] [ebp-78h] BYREF
  int v11; // [esp+Ch] [ebp-74h]
  int v12; // [esp+10h] [ebp-70h]
  int v13; // [esp+20h] [ebp-60h] BYREF
  int v14; // [esp+24h] [ebp-5Ch]
  int v15; // [esp+28h] [ebp-58h]
  double v16; // [esp+38h] [ebp-48h]
  double v17; // [esp+40h] [ebp-40h]
  double v18; // [esp+48h] [ebp-38h]
  double v19; // [esp+50h] [ebp-30h]
  double v20; // [esp+58h] [ebp-28h]

  if ( Lexer_TokenExpect(2) == -1 )
  {
    v3 = 0;
LABEL_20:
    *(_DWORD *)(a1 + 4) = 1;
    result = Rules_AddIntegerValue(v3);
    *(_DWORD *)(a1 + 8) = result;
    return result;
  }
  v3 = Lexer_ParseValueList(1, &v13, 110, a2);
  if ( !v3 )
    goto LABEL_20;
  v3 = Lexer_ParseValueList(2, &v10, 110, a2);
  if ( !v3 )
    goto LABEL_20;
  if ( v11 == 1 && !*(_DWORD *)(v12 + 16) || v11 != 1 && *(double *)(v12 + 16) == 0.0 )
  {
    Rules_ReportDivideByZeroError();
    Lexer_ErrorRecover(1);
    *(_DWORD *)(a1 + 4) = 1;
    result = Rules_AddIntegerValue(0);
    *(_DWORD *)(a1 + 8) = result;
  }
  else if ( v14 && v11 )
  {
    v7 = *(_DWORD *)(v15 + 16) % *(_DWORD *)(v12 + 16);
    *(_DWORD *)(a1 + 4) = 1;
    result = Rules_AddIntegerValue(v7);
    *(_DWORD *)(a1 + 8) = result;
  }
  else
  {
    if ( v14 == 1 )
      v19 = (double)*(int *)(v15 + 16);
    else
      v19 = *(double *)(v15 + 16);
    if ( v11 == 1 )
      v16 = (double)*(int *)(v12 + 16);
    else
      v16 = *(double *)(v12 + 16);
    v17 = v19 / v16;
    *(_DWORD *)(a1 + 4) = 0;
    if ( v17 >= 0.0 )
      v18 = floor(v17);
    else
      v18 = ceil(v17);
    v20 = v19 - v18 * v16;
    result = (int *)Rules_AddDoubleValue(v20);
    *(_DWORD *)(a1 + 8) = result;
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
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return v5[0] * g_Rules_DegToRadPiConstant / g_Rules_DegToRadDegreesConstant;
  v5[1] = 0.0;
  return 0.0;
}
// 507790: using guessed type double dbl_507790;
// 507798: using guessed type double dbl_507798;

//----- (004A4DA0) --------------------------------------------------------
double  Rules_MathRadToDeg(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return v5[0] * g_Rules_RadToDegDegreesConstant / g_Rules_RadToDegPiConstant;
  v5[1] = 0.0;
  return 0.0;
}
// 5077A0: using guessed type double dbl_5077A0;
// 5077A8: using guessed type double dbl_5077A8;

//----- (004A4DF0) --------------------------------------------------------
double  Rules_MathDegToGrad(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return v5[0] / g_Rules_DegToGradConversionFactor;
  v5[1] = 0.0;
  return 0.0;
}
// 5077B0: using guessed type double dbl_5077B0;

//----- (004A4E30) --------------------------------------------------------
double  Rules_MathGradToDeg(int a1, int a2, int a3, double a4)
{
  double v5[2]; // [esp+0h] [ebp-18h] BYREF
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  v7 = a1;
  v6 = a2;
  if ( Rules_MathParseSingleArg(v5, a3, a4) )
    return v5[0] * g_Rules_GradToDegConversionFactor;
  v5[1] = 0.0;
  return 0.0;
}
// 5077B8: using guessed type double dbl_5077B8;

//----- (004A4E70) --------------------------------------------------------
signed int  Rules_MathRound(int a1, double a2)
{
  signed int result; // eax
  int v4; // [esp+8h] [ebp-28h] BYREF
  int v5; // [esp+Ch] [ebp-24h]
  int v6; // [esp+10h] [ebp-20h]
  int v8; // [esp+28h] [ebp-8h]

  v8 = a1;
  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, &v4, 110, a2);
  if ( !result )
    return result;
  if ( v5 == 1 )
    return *(_DWORD *)(v6 + 16);
  return (int)ceil(*(double *)(v6 + 16) + g_Rules_MathRoundHalfOffset);
}
// 5077C0: using guessed type double dbl_5077C0;

//----- (004A5000) --------------------------------------------------------
_DWORD * Help_IndexTopicFile(CHAR *a1, _BYTE *a2, int a3, int a4, DWORD a5)
{
  int *v6; // esi
  _DWORD *result; // eax
  int v8; // ecx
  int v9; // ebp
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // ecx
  _BYTE v14[256]; // [esp+0h] [ebp-128h] BYREF
  signed int v15; // [esp+100h] [ebp-28h]
  _BYTE *v16; // [esp+104h] [ebp-24h]
  int v17; // [esp+108h] [ebp-20h]
  char *v18; // [esp+10Ch] [ebp-1Ch]
  int v19; // [esp+110h] [ebp-18h]
  int v20; // [esp+114h] [ebp-14h]

  v16 = a2;
  v15 = a4;
  if ( a4 > 0 )
    *a2 = 0;
  v6 = (int *)IO_FOpen(a1, g_Help_FileOpenModeRead, a3, a5);
  if ( v6 )
  {
    v18 = Help_GetOrCreateFileRecord(a1);
    if ( v18 )
    {
      v9 = 0;
      v19 = 0;
      v17 = 0;
      v20 = 1;
      while ( fgets_(v14, 256, (int)v6) )
      {
        ++v9;
        if ( v14[0] != 36 || v14[1] != 36 )
        {
          if ( Str_FindSubstringIndex(v14, aEndEntry) < 0 )
          {
            if ( Str_FindSubstringIndex(v14, aBeginEntry) >= 0 )
            {
              if ( v20 != 1 )
              {
                fclose_((int)v6);
                Help_UnloadTopicFile((int)a1);
                if ( v12 < 60 )
                  return 0;
                goto LABEL_23;
              }
              v17 = 1;
              v20 = 0;
              result = Help_ParseEntryHeader(v6, (int)a1, (int)v16, v15, v9);
              if ( !result )
                return result;
              result = (_DWORD *)Help_InsertEntryIntoTopicTree((int)v18, result, (int)v16, v15, v9);
              if ( !result )
                return result;
            }
          }
          else
          {
            if ( v17 != 1 )
            {
              fclose_((int)v6);
              Help_UnloadTopicFile((int)a1);
              if ( v11 < 60 )
                return 0;
              sprintf_(v16, "Line %d : Unmatched end marker.", v9);
              return 0;
            }
            v20 = 1;
            v17 = 0;
            ++v19;
          }
        }
      }
      fclose_((int)v6);
      if ( v20 )
      {
        if ( !v19 )
          Help_UnloadTopicFile((int)a1);
        return (_DWORD *)v19;
      }
      Help_UnloadTopicFile((int)a1);
      if ( v13 >= 60 )
      {
LABEL_23:
        sprintf_(v16, "Line %d : Previous entry not closed.", v9);
        return 0;
      }
    }
    else
    {
      fclose_((int)v6);
      if ( v10 >= 60 )
      {
        sprintf_(v16, "File \"%s\" already loaded.", a1);
        return 0;
      }
    }
  }
  else if ( v15 >= 60 )
  {
    sprintf_(v16, "Could not open file \"%s\".", a1);
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
signed int  Help_UnloadTopicFile(int a1)
{
  int v2; // ecx
  int v3; // esi
  BOOL v4; // eax
  _DWORD *v5; // ecx

  v2 = g_HelpLoadedTopicFileList;
  v3 = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    v4 = strcmp_(g_HelpLoadedTopicFileList, a1) != 0;
  else
    v4 = 0;
  if ( v4 > 0 )
  {
    do
    {
      v3 = v2;
      v2 = *(_DWORD *)(v2 + 88);
    }
    while ( v2 && strcmp_(v2, a1) );
  }
  if ( !v2 )
    return 0;
  Help_FreeTopicTree(*(_DWORD **)(v2 + 80));
  if ( (_DWORD *)v3 == v5 )
    g_HelpLoadedTopicFileList = v5[22];
  else
    *(_DWORD *)(v3 + 88) = v5[22];
  Mem_SmallBlockFree(v5, 92);
  return 1;
}
// 4A52D8: variable 'v2' is possibly undefined
// 4A5312: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5350) --------------------------------------------------------
int  Help_OpenFileAtNavigatedTopic(const CHAR *a1, _DWORD *a2, _DWORD *a3, _BYTE *a4)
{
  int v6; // ecx
  signed int v7; // ebp
  int result; // eax
  int v9; // ecx

  v7 = Help_FindOrAdvanceTopicEntry((int)a1, a2, a3, a4);
  if ( v7 < 0 )
    return 0;
  result = IO_FOpen(a1, g_Help_FileOpenModeRead, v6, v7);
  if ( result )
  {
    if ( IO_SeekStreamGuarded(result, v7, 0, (int)a3) < 0 )
    {
      fclose_(v9);
      *a3 = -10;
      return 0;
    }
    else
    {
      return v9;
    }
  }
  else
  {
    *a3 = -10;
  }
  return result;
}
// 4A536F: variable 'v6' is possibly undefined
// 4A5391: variable 'v9' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5077F0: using guessed type unsigned __int8 byte_5077F0[4];

//----- (004A53B0) --------------------------------------------------------
int  Help_ReopenFileAtActiveEntry(const CHAR *a1, _DWORD *a2, DWORD a3)
{
  int v5; // ecx
  BOOL v6; // eax
  int result; // eax
  int v8; // ecx
  int v9; // esi
  int v10; // ecx

  v5 = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    v6 = strcmp_(g_HelpLoadedTopicFileList, a1) != 0;
  else
    v6 = 0;
  if ( v6 > 0 )
  {
    do
      v5 = *(_DWORD *)(v5 + 88);
    while ( v5 && strcmp_(v5, a1) );
  }
  if ( !v5 )
  {
    *a2 = -10;
    return 0;
  }
  if ( !*(_DWORD *)(v5 + 84) )
  {
    *a2 = -25;
    return 0;
  }
  result = IO_FOpen(a1, g_Help_FileOpenModeRead, v5, a3);
  v9 = result;
  if ( result )
  {
    if ( IO_SeekStreamGuarded(result, *(_DWORD *)(*(_DWORD *)(v8 + 84) + 88), 0, (int)a2) < 0 )
    {
      fclose_(v10);
      *a2 = -10;
      return 0;
    }
    else
    {
      result = v9;
      *a2 = 0;
    }
  }
  else
  {
    *a2 = -10;
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
signed int  Str_FindSubstringIndex(_BYTE *a1, _BYTE *a2)
{
  _BYTE *v3; // ebp
  int v4; // esi
  _BYTE *v5; // eax
  int v6; // ecx
  _BYTE *v7; // edx
  char v8; // bh
  char v9; // dh

  v3 = a1;
  v4 = 0;
  if ( !*a1 )
    return -1;
  while ( 1 )
  {
    v5 = a2;
    v6 = 0;
    v7 = &a1[v4];
    if ( *a2 )
    {
      do
      {
        if ( *v7 != *v5 )
          break;
        ++v7;
        v8 = *++v5;
        ++v6;
      }
      while ( v8 );
    }
    if ( !a2[v6] && v6 )
      break;
    v9 = *++v3;
    ++v4;
    if ( !v9 )
      return -1;
  }
  return v4;
}

//----- (004A5530) --------------------------------------------------------
int  Str_UppercaseToDelimiter(int result, int a2)
{
  _BYTE *v2; // edx
  _BYTE *v4; // edx
  char v5; // bh

  v2 = (_BYTE *)result;
  if ( *(_BYTE *)result )
  {
    do
    {
      while ( 1 )
      {
        result = (unsigned __int8)(*v2 + 1);
        if ( IsTable[result] < 0 )
          break;
        if ( !*++v2 )
          return result;
      }
      result = toupper_(a2);
      *v4 = result;
      v5 = v4[1];
      v2 = v4 + 1;
    }
    while ( v5 );
  }
  return result;
}
// 4A555B: variable 'a2' is possibly undefined
// 4A5560: variable 'v4' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004A5570) --------------------------------------------------------
char * Help_GetOrCreateFileRecord(char *a1)
{
  int v2; // ecx
  char *result; // eax
  int v4; // ecx
  char *v5; // edx
  int v6; // ecx
  char *v7; // edi
  char v8; // al
  char v9; // al

  if ( !g_HelpLoadedTopicFileList )
  {
LABEL_6:
    v5 = (char *)Mem_SmallBlockAlloc(0x5Cu);
    v7 = v5;
    do
    {
      v8 = *a1;
      *v7 = *a1;
      if ( !v8 )
        break;
      v9 = a1[1];
      a1 += 2;
      v7[1] = v9;
      v7 += 2;
    }
    while ( v9 );
    *((_DWORD *)v5 + 20) = 0;
    *((_DWORD *)v5 + 21) = 0;
    *((_DWORD *)v5 + 22) = 0;
    if ( g_HelpLoadedTopicFileList )
    {
      *(_DWORD *)(v6 + 88) = v5;
      return v5;
    }
    else
    {
      g_HelpLoadedTopicFileList = (int)v5;
      return v5;
    }
  }
  v2 = g_HelpLoadedTopicFileList;
  if ( !*(_DWORD *)(g_HelpLoadedTopicFileList + 88) )
  {
LABEL_5:
    result = (char *)strcmp_(v2, a1);
    if ( !result )
      return result;
    goto LABEL_6;
  }
  while ( 1 )
  {
    result = (char *)strcmp_(v2, a1);
    if ( !result )
      return result;
    v2 = *(_DWORD *)(v4 + 88);
    if ( !*(_DWORD *)(v2 + 88) )
      goto LABEL_5;
  }
}
// 4A5598: variable 'v4' is possibly undefined
// 4A5605: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5610) --------------------------------------------------------
_DWORD * Help_ParseEntryHeader(int *a1, int a2, int a3, signed int a4, int a5)
{
  _DWORD *v8; // ebx
  int v9; // edx
  _DWORD *v10; // ecx
  int v11; // ecx
  int v12; // edi
  signed int v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  unsigned __int8 *v25; // eax
  char v26; // [esp+0h] [ebp-20h] BYREF
  char v27; // [esp+10h] [ebp-10h] BYREF

  v8 = Mem_SmallBlockAlloc(0x68u);
  if ( sscanf_(v9, "%d%1s%12s%s", v8, &v27, &v26, v8 + 2) == 4 )
  {
    if ( v27 == 77 )
    {
      v10[1] = -45;
LABEL_5:
      if ( !strcmp_(v10, aBeginEntry) )
      {
        v12 = a1[1];
        if ( v12 > 0 && (unsigned int)*(unsigned __int8 *)*a1 - 13 > 0xFD )
        {
          v25 = (unsigned __int8 *)*a1;
          v14 = *a1 + 1;
          a1[1] = v12 - 1;
          *a1 = v14;
          v13 = *v25;
        }
        else
        {
          v13 = fgetc_(v11, a1);
        }
        CRT_FlushBufferAndPutChar(v13, v14);
        v17 = ftell_(v16, v15);
        v8[24] = 0;
        v8[23] = 0;
        v8[22] = v17;
        v8[25] = 0;
        Str_UppercaseToDelimiter((int)(v8 + 2), v18);
        return v8;
      }
      else
      {
        Mem_SmallBlockFree(v8, 104);
        fclose_(v24);
        Help_UnloadTopicFile(a2);
        if ( a4 >= 60 )
          sprintf_(a3, "Line %d : Invalid delimeter string.", a5);
        return 0;
      }
    }
    if ( v27 == 73 )
    {
      v10[1] = -50;
      goto LABEL_5;
    }
    Mem_SmallBlockFree(v10, 104);
    fclose_(v22);
    Help_UnloadTopicFile(a2);
    if ( v23 >= 60 )
      sprintf_(a3, "Line %d : Invalid entry type.", a5);
    return 0;
  }
  else
  {
    Mem_SmallBlockFree(v10, 104);
    fclose_(v20);
    Help_UnloadTopicFile(a2);
    if ( v21 >= 60 )
      sprintf_(a3, "Line %d : Invalid delimeter string.", a5);
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
signed int  Help_InsertEntryIntoTopicTree(int a1, _DWORD *a2, int a3, signed int a4, int a5)
{
  int v7; // edx
  int v8; // edx
  int v10; // ecx
  int v11; // ecx
  _DWORD *v12; // edx

  if ( !*(_DWORD *)(a1 + 80) )
  {
    *(_DWORD *)(a1 + 80) = a2;
    goto LABEL_6;
  }
  v7 = g_ClipsHelpCurrentTopicNode;
  if ( *a2 > *(_DWORD *)g_ClipsHelpCurrentTopicNode )
  {
    if ( *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 4) != -45 )
    {
      Mem_SmallBlockFree(a2, 104);
      fclose_(v10);
      Help_UnloadTopicFile(v11);
      if ( a4 >= 60 )
        sprintf_(a3, "Line %d : Non-menu entries cannot have subtopics.", a5);
      return 0;
    }
    a2[24] = g_ClipsHelpCurrentTopicNode;
    goto LABEL_5;
  }
  if ( *a2 == *(_DWORD *)g_ClipsHelpCurrentTopicNode )
    goto LABEL_13;
  if ( g_ClipsHelpCurrentTopicNode )
  {
    do
    {
      v12 = *(_DWORD **)(g_ClipsHelpCurrentTopicNode + 96);
      g_ClipsHelpCurrentTopicNode = (int)v12;
    }
    while ( v12 && *a2 < *v12 );
  }
  if ( g_ClipsHelpCurrentTopicNode )
  {
    if ( *(_DWORD *)g_ClipsHelpCurrentTopicNode < *a2 )
    {
      a2[24] = g_ClipsHelpCurrentTopicNode;
      a2[25] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 92);
      v7 = g_ClipsHelpCurrentTopicNode;
LABEL_5:
      *(_DWORD *)(v7 + 92) = a2;
LABEL_6:
      v8 = 1;
      g_ClipsHelpCurrentTopicNode = (int)a2;
      return v8;
    }
LABEL_13:
    a2[24] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 96);
    a2[25] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 100);
    *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 100) = a2;
    g_ClipsHelpCurrentTopicNode = (int)a2;
    return 1;
  }
  a2[24] = 0;
  a2[25] = *(_DWORD *)(a1 + 80);
  *(_DWORD *)(a1 + 80) = a2;
  g_ClipsHelpCurrentTopicNode = (int)a2;
  return 1;
}
// 4A581A: variable 'v10' is possibly undefined
// 4A5825: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACE4: using guessed type int dword_51ACE4;

//----- (004A5920) --------------------------------------------------------
signed int  Help_FindOrAdvanceTopicEntry(int a1, _DWORD *a2, _DWORD *a3, _BYTE *a4)
{
  int v7; // ecx
  BOOL v8; // eax
  int v9; // ebx
  int v10; // esi
  signed int result; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // ebx
  BOOL v15; // eax
  int v16; // eax
  int v17; // ebp

  v7 = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    v8 = strcmp_(g_HelpLoadedTopicFileList, a1) != 0;
  else
    v8 = 0;
  if ( v8 > 0 )
  {
    do
      v7 = *(_DWORD *)(v7 + 88);
    while ( v7 && strcmp_(v7, a1) );
  }
  if ( v7 )
  {
    if ( a4 )
    {
      Str_UppercaseToDelimiter((int)a4, v7);
      v13 = *(_DWORD *)(v12 + 84);
      if ( v13 )
        v14 = *(_DWORD *)(v13 + 92);
      else
        v14 = *(_DWORD *)(v12 + 80);
      if ( v14 )
        v15 = Str_FindSubstringIndex((_BYTE *)(v14 + 8), a4) != 0;
      else
        v15 = 0;
      if ( v15 > 0 )
      {
        do
          v14 = *(_DWORD *)(v14 + 100);
        while ( v14 && Str_FindSubstringIndex((_BYTE *)(v14 + 8), a4) );
      }
      if ( v14 )
      {
        if ( *(_DWORD *)(v14 + 4) == -45 )
        {
          *a3 = -40;
          *(_DWORD *)(v12 + 84) = v14;
        }
        else
        {
          *a3 = 0;
        }
        v17 = *(_DWORD *)(v12 + 84);
        if ( v17 )
          *a2 = v17 + 8;
        return *(_DWORD *)(v14 + 88);
      }
      else
      {
        *a3 = -25;
        v16 = *(_DWORD *)(v12 + 84);
        if ( !v16 )
          return -1;
        *a2 = v16 + 8;
        return *(_DWORD *)(*(_DWORD *)(v12 + 84) + 88);
      }
    }
    else
    {
      v9 = *(_DWORD *)(v7 + 84);
      if ( v9 )
      {
        v10 = *(_DWORD *)(v9 + 96);
        if ( !v10 )
        {
          *a3 = -30;
          *(_DWORD *)(v7 + 84) = 0;
          *a2 = 0;
          return -1;
        }
        *(_DWORD *)(v7 + 84) = v10;
        *a3 = -35;
        *a2 = *(_DWORD *)(v7 + 84) + 8;
        return *(_DWORD *)(*(_DWORD *)(v7 + 84) + 88);
      }
      else
      {
        result = -1;
        *a3 = -30;
      }
    }
  }
  else
  {
    result = -1;
    *a3 = -10;
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
  char *v6; // esi
  _BYTE *v7; // edi
  int v8; // ebp
  char v9; // al
  char v10; // al
  _DWORD *v11; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // esi
  int v17; // ecx
  char *v18; // edx
  char *v19; // eax
  signed int result; // eax
  int v21; // ecx
  _DWORD *v22; // eax
  char *v23; // esi
  _BYTE *v24; // edi
  char v25; // al
  char v26; // al
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  unsigned int v31; // ecx
  char v32; // al
  char v33; // dl
  int v34; // ecx
  int v35; // ecx
  _BYTE v36[256]; // [esp+0h] [ebp-120h] BYREF
  _DWORD *v37; // [esp+100h] [ebp-20h] BYREF
  int v38[7]; // [esp+104h] [ebp-1Ch] BYREF

  if ( !g_HelpSystemInitialized )
  {
    if ( !g_ClipsHelpFilePath )
    {
      v23 = aClips_hlp;
      v24 = Mem_SmallBlockAlloc(strlen(aClips_hlp) + 1);
      g_ClipsHelpFilePath = (int)v24;
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
    }
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aLoadingHelpFil, a1);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], g_ClipsHelpFilePath, v3);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)a_PleaseWait___, v4);
    v37 = Help_IndexTopicFile((CHAR *)g_ClipsHelpFilePath, v36, v5, 256, a2);
    if ( !v37 )
    {
      Rules_PrintErrorID((int)aTextpro, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToAccess, v27);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v36, v28);
      return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50797C, v29);
    }
    IO_AddRouter((int)aWhelp, 10, (int)Rules_HelpRouterPrint, (int)Help_RouterQueryMatchesWhelp, (int)Rules_HelpRouterGetc, (int)Rules_HelpRouterUngetc, 0);
    g_HelpSystemInitialized = 1;
  }
  IO_ActivateRouter((int)aWhelp);
  v6 = aMain_2;
  v7 = Mem_SmallBlockAlloc(0x58u);
  v8 = (int)v7;
  do
  {
    v9 = *v6;
    *v7 = *v6;
    if ( !v9 )
      break;
    v10 = v6[1];
    v6 += 2;
    v7[1] = v10;
    v7 += 2;
  }
  while ( v10 );
  v11 = Rules_HelpBuildTopicListFromArgs(a3);
  *(_DWORD *)(v12 + 80) = 0;
  *(_DWORD *)(v12 + 84) = v11;
  Output_Write((int)aWhelp, (int)asc_50797C, v13);
  while ( 1 )
  {
    v14 = Rules_HelpLocateTopicEntry((const CHAR *)g_ClipsHelpFilePath, v8, &v37, v38);
    v16 = v14;
    if ( v37 == (_DWORD *)-10 )
      break;
    if ( v37 == (_DWORD *)-30 )
      goto LABEL_12;
    if ( v37 == (_DWORD *)-25 )
    {
      if ( !v14 )
      {
        Output_Write((int)aWhelp, (int)aRootEntryMainN, v15);
        Output_Write((int)aWhelp, g_ClipsHelpFilePath, v34);
        v18 = a_SeeExternalDo;
        v19 = aWhelp;
        goto LABEL_11;
      }
      Output_Write((int)aWhelp, (int)aSorryNoInforma, v15);
    }
    if ( v37 != (_DWORD *)-35 )
    {
      while ( 2 )
      {
        if ( !Help_ReadEntryLine(v16, v36, 256) )
          goto LABEL_43;
        if ( v15 < 23 )
          goto LABEL_37;
        Output_Write((int)aWhelp, (int)aPressReturnFor, v15);
        Output_Write((int)aWhelp, (int)aPressAReturnTo, v30);
        g_Lexer_PendingLineCharIndex = 0;
LABEL_29:
        v32 = Lexer_PeekChar((int)aWhelp, v31);
        v33 = v32;
        switch ( v32 )
        {
          case 10:
            goto LABEL_34;
          case 97:
            v33 = 65;
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
        if ( v33 == 10 || v33 == 65 )
        {
          v15 = 0;
          g_Lexer_PendingLineCharIndex = -1;
          if ( v33 == 65 )
            goto LABEL_42;
LABEL_37:
          Output_Write((int)aWhelp, (int)v36, v15 + 1);
          continue;
        }
        goto LABEL_29;
      }
    }
    if ( v16 )
LABEL_42:
      fclose_(v15);
LABEL_43:
    v8 = Rules_HelpReadTopicListFromInput(v8, v38, v15);
    if ( g_ClipsHaltExecution )
    {
      while ( v37 != (_DWORD *)-30 )
      {
        if ( Help_OpenFileAtNavigatedTopic((const CHAR *)g_ClipsHelpFilePath, v38, &v37, 0) )
          fclose_(v35);
      }
    }
    if ( v37 == (_DWORD *)-30 )
      goto LABEL_12;
  }
  Rules_PrintErrorID((int)aTextpro, 1, 0);
  v18 = aUnableToAccess;
  v19 = g_IO_LogicalNameTable_WError[0];
LABEL_11:
  Output_Write((int)v19, (int)v18, v17);
LABEL_12:
  result = IO_DeactivateRouter((int)aWhelp);
  if ( v8 )
  {
    v21 = 88;
    do
    {
      v22 = (_DWORD *)v8;
      v8 = *(_DWORD *)(v8 + 84);
      result = Mem_SmallBlockFree(v22, v21);
    }
    while ( v8 );
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
  char *v7; // eax
  char *v8; // edx
  int v9; // ecx
  const char *v10; // ebx
  const char *v11; // esi
  int v12; // edx
  int v13; // ecx
  _BYTE *v14; // edi
  char v15; // al
  char v16; // al
  int v17; // ecx
  int v18; // ecx
  _DWORD v19[11]; // [esp-8h] [ebp-2Ch] BYREF

  v19[9] = a1;
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
    result = Lexer_ParseValueList(1, v19, 111, a2);
    if ( result )
    {
      v10 = *(const char **)(v19[2] + 16);
      v11 = v10;
      v14 = Mem_SmallBlockAlloc(strlen(v10) + 1);
      g_ClipsHelpFilePath = (int)v14;
      do
      {
        v15 = *v11;
        *v14 = *v11;
        if ( !v15 )
          break;
        v16 = v11[1];
        v11 += 2;
        v14[1] = v16;
        v14 += 2;
      }
      while ( v16 );
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], v12, v13);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v10, v17);
      return Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50797C, v18);
    }
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aTheCurrentHelp, v2);
    if ( g_ClipsHelpFilePath )
    {
      v7 = g_IO_LogicalNameTable_WDialog[0];
      v8 = (char *)g_ClipsHelpFilePath;
    }
    else
    {
      v8 = aClips_hlp;
      v7 = g_IO_LogicalNameTable_WDialog[0];
    }
    Output_Write((int)v7, (int)v8, v6);
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
int * Help_LoadHelpFileCommand(DWORD a1, double a2)
{
  int *result; // eax
  int v4; // ecx
  CHAR *v5; // edi
  CHAR *v6; // esi
  CHAR v7; // al
  CHAR v8; // al
  _DWORD *v9; // eax
  int v10; // ecx
  int v11; // ecx
  char *v12; // edx
  int v13; // ecx
  CHAR v14[80]; // [esp+0h] [ebp-D0h] BYREF
  _BYTE v15[80]; // [esp+50h] [ebp-80h] BYREF
  _DWORD v16[12]; // [esp+A0h] [ebp-30h] BYREF

  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_ParseValueList(1, v16, 111, a2);
  if ( result )
  {
    v5 = v14;
    v6 = *(CHAR **)(v16[2] + 16);
    do
    {
      v7 = *v6;
      *v5 = *v6;
      if ( !v7 )
        break;
      v8 = v6[1];
      v6 += 2;
      v5[1] = v8;
      v5 += 2;
    }
    while ( v8 );
    v9 = Help_IndexTopicFile(v14, v15, v4, 80, a1);
    if ( v9 )
    {
      *(_DWORD *)(a1 + 4) = 1;
      result = Rules_AddIntegerValue((signed int)v9);
      *(_DWORD *)(a1 + 8) = result;
    }
    else
    {
      Rules_PrintErrorID((int)aTextpro, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToLoadFi, v10);
      if ( v15[0] )
        v12 = v15;
      else
        v12 = aNoEntriesFound;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v12, v11);
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
  _DWORD *v1; // edi
  _DWORD *v2; // ebp
  int v3; // eax
  int v4; // ecx
  char *v5; // edx
  int i; // eax
  char *v7; // esi
  char v8; // al
  char v9; // al
  int v10; // edi
  int v11; // ecx
  _DWORD *v13; // eax
  _BYTE v14[256]; // [esp+4h] [ebp-118h] BYREF
  int v15; // [esp+104h] [ebp-18h] BYREF
  _DWORD v16[5]; // [esp+108h] [ebp-14h] BYREF

  v1 = Rules_HelpBuildTopicListFromArgs(a1);
  v2 = v1;
  v3 = Rules_HelpLocateTopicEntry((const CHAR *)v1[21], *(_DWORD *)(v1[21] + 84), v16, &v15);
  if ( v16[0] == -10 || v16[0] == -25 || v16[0] == -30 )
  {
    if ( v3 )
      fclose_(v3);
    v10 = 0;
  }
  else
  {
    if ( !strcmp_(v3, aT_1) )
    {
      v7 = aStdout_3;
      do
      {
        v8 = *v7;
        *(_BYTE *)v1 = *v7;
        if ( !v8 )
          break;
        v9 = v7[1];
        v7 += 2;
        *((_BYTE *)v1 + 1) = v9;
        v1 = (_DWORD *)((char *)v1 + 2);
      }
      while ( v9 );
    }
    v5 = asc_50797C;
    for ( i = (int)v2; ; i = (int)v2 )
    {
      Output_Write(i, (int)v5, v4);
      if ( !Help_ReadEntryLine(v3, v14, 256) )
        break;
      v5 = v14;
    }
    v10 = 1;
  }
  v11 = 88;
  while ( v2 )
  {
    v13 = v2;
    v2 = (_DWORD *)v2[21];
    Mem_SmallBlockFree(v13, v11);
  }
  return v10;
}
// 4A610D: variable 'v4' is possibly undefined
// 4A6180: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6190) --------------------------------------------------------
signed int  Help_UnloadHelpFileCommand(int a1, double a2)
{
  signed int result; // eax
  int v4; // ecx
  int v5; // ebx
  _DWORD v6[9]; // [esp-8h] [ebp-24h] BYREF

  v6[7] = a1;
  result = Lexer_ParseValueList(1, v6, 111, a2);
  if ( result )
  {
    v5 = *(_DWORD *)(v6[2] + 16);
    if ( g_ClipsHelpFilePath && !strcmp_(v4, g_ClipsHelpFilePath) && g_HelpSystemInitialized == 1 )
    {
      Mem_SmallBlockFree((_DWORD *)g_ClipsHelpFilePath, strlen((const char *)g_ClipsHelpFilePath) + 1);
      g_ClipsHelpFilePath = 0;
      g_HelpSystemInitialized = 0;
      IO_DeleteRouter((int)aWhelp);
    }
    return Help_UnloadTopicFile(v5);
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
int __fastcall Rules_HelpRouterPrint(int a1, int a2)
{
  Output_Write((int)aStdout_3, a2, a1);
  return 1;
}

//----- (004A6250) --------------------------------------------------------
int __thiscall Rules_HelpRouterGetc(void *this)
{
  return Lexer_PeekChar((int)aStdin_3, (unsigned int)this);
}

//----- (004A6260) --------------------------------------------------------
signed int  Rules_HelpRouterUngetc(signed int a1, int a2)
{
  return Lexer_SkipChar(a1, (int)aStdin_3, a2);
}

//----- (004A6270) --------------------------------------------------------
_DWORD * Rules_HelpBuildTopicListFromArgs(double a1)
{
  int v1; // edi
  _DWORD *v2; // ebp
  _DWORD *v3; // esi
  _DWORD *v4; // edx
  int v5; // ecx
  char *v6; // edx
  _DWORD *i; // eax
  int v9; // [esp+4h] [ebp-30h]
  int v10; // [esp+8h] [ebp-2Ch]
  int v11; // [esp+18h] [ebp-1Ch]

  v1 = 1;
  v11 = Rules_RtnArgCount();
  v2 = 0;
  if ( v11 >= 1 )
  {
    do
    {
      v3 = Mem_SmallBlockAlloc(0x58u);
      Rules_RtnUnknown(v1, v4, a1);
      if ( v9 == 2 || v9 == 3 )
      {
        v6 = *(char **)(v10 + 16);
      }
      else if ( v9 )
      {
        if ( v9 == 1 )
          v6 = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(v10 + 16));
        else
          v6 = aError_4;
      }
      else
      {
        v6 = (char *)Rules_FloatToSymbol(v5, *(double *)(v10 + 16));
      }
      strncpy_(v5, v6);
      v3[21] = 0;
      v3[20] = 0;
      if ( v2 )
      {
        for ( i = v2; i[21]; i = (_DWORD *)i[21] )
          ;
        i[21] = v3;
      }
      else
      {
        v2 = v3;
      }
      ++v1;
    }
    while ( v1 <= v11 );
  }
  return v2;
}
// 4A629F: variable 'v4' is possibly undefined
// 4A62AB: variable 'v9' is possibly undefined
// 4A62BD: variable 'v10' is possibly undefined
// 4A62C0: variable 'v5' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004A6350) --------------------------------------------------------
int  Rules_HelpReadTopicListFromInput(int a1, int *a2, int a3)
{
  int v4; // ecx
  int v5; // edx
  unsigned int v6; // ecx
  char v7; // al
  int v8; // ecx
  int v9; // edx
  char v10; // bl
  int v11; // esi
  char v13; // bh
  char *v14; // esi
  char *v15; // ebx
  char *v16; // edi
  char v17; // al
  char v18; // al
  int v19; // esi
  char *v20; // esi
  char *v21; // edi
  char v22; // al
  char v23; // al
  char v24; // [esp-1h] [ebp-16Dh]
  _BYTE v25[256]; // [esp+0h] [ebp-16Ch]
  char v26[80]; // [esp+100h] [ebp-6Ch] BYREF
  char *v27; // [esp+150h] [ebp-1Ch]
  int v28; // [esp+154h] [ebp-18h]

  Output_Write((int)aWhelp, *a2, a3);
  Output_Write((int)aWhelp, (int)aTopic_, v4);
  v5 = 0;
  g_Lexer_PendingLineCharIndex = 0;
  v6 = -2;
  while ( 1 )
  {
    v7 = Lexer_PeekChar((int)aWhelp, v6);
    v25[v5] = v7;
    if ( v7 == 10 || v5 >= 254 || g_ClipsHaltExecution )
      break;
    if ( v7 == 9 )
    {
      v25[v5] = 32;
      goto LABEL_14;
    }
    if ( v7 == 8 && v5 )
    {
      g_Lexer_PendingLineCharIndex += v6;
      v5 = v5 - 2 + 1;
      ++g_Lexer_PendingLineCharIndex;
    }
    else
    {
LABEL_14:
      ++v5;
      ++g_Lexer_PendingLineCharIndex;
    }
  }
  v8 = g_ClipsHaltExecution;
  g_Lexer_PendingLineCharIndex = -1;
  if ( g_ClipsHaltExecution )
  {
    Output_Write((int)aWhelp, (int)asc_50797C, g_ClipsHaltExecution);
    *(_DWORD *)(a1 + 80) = a1;
    return a1;
  }
  else
  {
    v25[v5] = 32;
    v25[v5 + 1] = 0;
    v28 = a1;
    v9 = 0;
    while ( v25[v9] )
    {
      v10 = v25[v9];
      if ( v10 == 32 || v8 >= 80 )
      {
        if ( v8 <= 0 )
        {
          ++v9;
        }
        else
        {
          while ( 1 )
          {
            v13 = v25[v9];
            if ( v13 == 32 || !v13 )
              break;
            ++v9;
          }
          v26[v8] = 0;
          v8 = 0;
          if ( a1 )
          {
            v20 = v26;
            v21 = (char *)a1;
            v24 = HIBYTE(a1);
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
            a1 = *(_DWORD *)(a1 + 84);
          }
          else
          {
            v14 = v26;
            v15 = (char *)Mem_SmallBlockAlloc(0x58u);
            v16 = v15;
            v27 = v15;
            v24 = HIBYTE(v15);
            do
            {
              v17 = *v14;
              *v16 = *v14;
              if ( !v17 )
                break;
              v18 = v14[1];
              v14 += 2;
              v16[1] = v18;
              v16 += 2;
            }
            while ( v18 );
            *((_DWORD *)v15 + 21) = v8;
            v19 = v28;
            *((_DWORD *)v15 + 20) = v8;
            if ( v19 )
            {
              for ( ; *(_DWORD *)(v19 + 84); v19 = *(_DWORD *)(v19 + 84) )
                ;
              *(_DWORD *)(v19 + 84) = v27;
            }
            else
            {
              v28 = (int)v15;
            }
          }
        }
      }
      else
      {
        ++v8;
        ++v9;
        v25[v8 + 255] = v10;
      }
    }
    v11 = v28;
    *(_DWORD *)(v28 + 80) = a1;
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
int  Rules_HelpLocateTopicEntry(const CHAR *a1, int a2, _DWORD *a3, _DWORD *a4)
{
  _DWORD *v5; // edi
  int result; // eax
  int v7; // esi
  int v8; // ecx
  _DWORD *v9; // edx
  _DWORD *v10; // ecx
  const CHAR *v11; // eax
  _BYTE *v12; // ebx
  int v14; // [esp+4h] [ebp-10h]

  v5 = a3;
  result = 0;
  if ( a2 )
    v14 = *(_DWORD *)(a2 + 80);
  else
    v14 = 0;
  v7 = a2;
  if ( a2 != v14 )
  {
    while ( 1 )
    {
      if ( result )
        fclose_(a3);
      if ( !strcmp_(a3, asc_507B10) )
        break;
      if ( strcmp_(v8, aQuestionMark_507B14) || v14 != *(_DWORD *)(v7 + 84) )
      {
        v9 = a4;
        v10 = v5;
        v12 = (_BYTE *)v7;
        v11 = a1;
        goto LABEL_8;
      }
      result = Help_ReopenFileAtActiveEntry(a1, v5, (DWORD)a1);
LABEL_9:
      a3 = (_DWORD *)*v5;
      if ( *v5 != -10 && a3 != (_DWORD *)-25 )
      {
        v7 = *(_DWORD *)(v7 + 84);
        if ( v7 != v14 )
          continue;
      }
      return result;
    }
    v9 = a4;
    v10 = v5;
    v11 = a1;
    v12 = 0;
LABEL_8:
    result = Help_OpenFileAtNavigatedTopic(v11, v9, v10, v12);
    goto LABEL_9;
  }
  return Help_OpenFileAtNavigatedTopic(a1, a4, a3, 0);
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
  int v2; // ebp
  const char *v3; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // edi
  int v8; // ebx
  _DWORD v9[2]; // [esp+0h] [ebp-30h] BYREF
  int v10; // [esp+8h] [ebp-28h]

  result = Rules_ArgRangeCheck((int)aConstructsToC, 3);
  v2 = result;
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, v9, 111, a1);
    if ( result )
    {
      v3 = *(const char **)(v10 + 16);
      if ( (int)strlen(v3) > 3 )
      {
        Rules_PrintWarningID((int)aConscomp, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aBaseFileNameEx, v4);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aThisMayCauseFi, v5);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aIsLimitedOnYou, v6);
      }
      result = Lexer_ParseValueList(2, v9, 1, a1);
      if ( result )
      {
        v7 = *(_DWORD *)(v10 + 16);
        if ( v7 < 0 )
        {
          return Parser_ReportError(2, (int)aPositiveIntege);
        }
        else
        {
          if ( v2 != 3 )
          {
            v8 = 10000;
            return Rules_ConstructsToC(v3, v7, v8, (char)v3);
          }
          result = Lexer_ParseValueList(3, v9, 1, a1);
          if ( result )
          {
            v8 = *(_DWORD *)(v10 + 16);
            if ( v8 >= 0 )
              return Rules_ConstructsToC(v3, v7, v8, (char)v3);
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
signed int  Rules_ConstructsToC(const char *a1, int a2, int a3, char a4)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // eax
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
  int v35; // esi
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
  CHAR v55[88]; // [esp+0h] [ebp-58h] BYREF

  v5 = a2;
  v6 = g_CodeGeneratorItemList;
  for ( g_ClipsCodeMaxIndicesPerArray = a3; v6; v6 = *(_DWORD *)(v6 + 24) )
  {
    if ( *(_DWORD *)(v6 + 4) )
      (*(void (__fastcall **)(int))(v6 + 4))(v5);
  }
  Rules_RunPeriodicCleanup(0, 0);
  g_Rules_ConstructsToCodeBaseName = (int)a1;
  g_ConstructsToCImageId = v7;
  g_ClipsCodeDataFile = 0;
  g_ClipsConstructCodeEntryIndexInFile = 0;
  g_ClipsExpressionCodeFileVersion = 1;
  g_Rules_ExprCodeNeedNewFileFlag = 1;
  sprintf_(v55, "%s.h", a1);
  v9 = IO_FOpen(v55, (unsigned __int8 *)aW_2, v8, (DWORD)a1);
  g_ClipsCodeHeaderFile = v9;
  if ( v9 )
  {
    Output_WriteFormatted(v11, v10, v9, (int)aIfndef_constru, a4);
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
    Compiler_GenerateConstructTables((DWORD)a1);
    Rules_WriteFunctionDefinitionRecordsToCode(a1);
    Rules_WriteHashedExpressionsToCode((DWORD)a1);
    v33 = g_ClipsCodeHeaderFile;
    Compiler_WriteConstraintTableFile(a1, v34, g_ConstructsToCImageId, g_ClipsCodeHeaderFile, g_ClipsCodeMaxIndicesPerArray);
    v35 = g_CodeGeneratorItemList;
    for ( i = 5; v35; v35 = *(_DWORD *)(v35 + 24) )
    {
      if ( *(_DWORD *)(v35 + 12) )
      {
        v33 = g_ClipsCodeHeaderFile;
        v37 = i++;
        (*(void (__fastcall **)(int, int, int))(v35 + 12))(g_ConstructsToCImageId, v37, g_ClipsCodeMaxIndicesPerArray);
      }
    }
    Rules_RestoreAtomicValueBuckets();
    if ( g_ClipsCodeDataFile )
    {
      Output_WriteFormatted(v38, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_507DA0, v54);
      fclose_(v39);
    }
    Rules_WriteConstructsToCDriverFile(a1, v33, (DWORD)a1);
    fclose_(v40);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v11, (int)v55);
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
int  Rules_PrintExternalFunctionDeclarations(int a1, int a2)
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

  Output_WriteFormatted(a1, a2, a1, (int)asc_507D2C, a2);
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
signed int  Rules_WriteFunctionDefinitionRecordsToCode(const char *a1)
{
  int v1; // edi
  int v2; // ecx
  int v3; // esi
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
  int v15; // esi
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
  int v41; // [esp+4h] [ebp-1Ch]

  v1 = 1;
  v2 = Rules_GetFunctionDefinitionListHead();
  v3 = 0;
  for ( i = 1; v2; ++v3 )
  {
    *(_WORD *)(v2 + 25) = v3;
    v2 = *(_DWORD *)(v2 + 27);
  }
  result = Rules_OpenConstructCodeFile(a1, 2, 1, 1u);
  if ( result )
  {
    Output_WriteFormatted(result, result, result, (int)asc_507E94, (char)a1);
    Output_WriteFormatted(v7, v6, v6, (int)asc_507DA4, v34);
    Output_WriteFormatted(v9, v8, v8, (int)aFunctionListDe, v35);
    Output_WriteFormatted(v11, v10, v10, (int)asc_507DF4, v36);
    v12 = Rules_GetFunctionDefinitionListHead();
    v41 = v13;
    v15 = v12;
    while ( v15 )
    {
      if ( i )
      {
        Output_WriteFormatted(v14, g_ConstructsToCImageId, v14, (int)aStructFunction, g_ConstructsToCImageId);
        Output_WriteFormatted(v17, v16, g_ClipsCodeHeaderFile, (int)aExternStructFu, g_ConstructsToCImageId);
        i = 0;
      }
      Output_WriteFormatted(v14, v13, v14, (int)asc_507F14, (char)v37);
      Compiler_WriteSymbolReference(v18, *(_DWORD *)v15, v18);
      Output_WriteFormatted(v20, v19, v20, (int)aS_4, *(_DWORD *)(v15 + 4));
      Output_WriteFormatted(v22, v21, v22, (int)aC, *(_BYTE *)(v15 + 8));
      Output_WriteFormatted(v23, *(_DWORD *)(v15 + 4), v23, (int)aPtifS, *(_DWORD *)(v15 + 4));
      Output_WriteFormatted(v25, v24, v25, (int)aNull_0, v38);
      if ( *(_DWORD *)(v15 + 17) )
        Output_WriteFormatted(v27, v26, v27, (int)aS_5, *(_DWORD *)(v15 + 17));
      else
        Output_WriteFormatted(v27, v26, v27, (int)aNull_0, v39);
      Output_WriteFormatted(v29, v28, v29, (int)a000, v39);
      Rules_WriteFunctionRecordRefToCode(v30, *(_DWORD *)(v15 + 27), v30);
      v15 = *(_DWORD *)(v15 + 27);
      if ( (__int16)++v41 <= g_ClipsCodeMaxIndicesPerArray && v15 )
      {
        Output_WriteFormatted(v31, g_ClipsCodeMaxIndicesPerArray, v31, (int)asc_507F54, v40);
      }
      else
      {
        Output_WriteFormatted(v31, g_ClipsCodeMaxIndicesPerArray, v31, (int)asc_507F4C, v40);
        fclose_(v32);
        ++v1;
        v41 = 1;
        if ( v15 )
        {
          result = Rules_OpenConstructCodeFile(v37, 2, v1, i);
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
int  Rules_WriteFunctionRecordRefToCode(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(*(__int16 *)(a2 + 25), *(__int16 *)(a2 + 25) % g_ClipsCodeMaxIndicesPerArray, a1, (int)aPD_DD, g_ConstructsToCImageId);
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_1, v4);
}
// 4A6E5E: variable 'v4' is possibly undefined
// 51ACF0: using guessed type int dword_51ACF0;
// 54E6D0: using guessed type int dword_54E6D0;

//----- (004A6EB0) --------------------------------------------------------
signed int  Rules_WriteConstructsToCDriverFile(const char *a1, char a2, DWORD a3)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // esi
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
  CHAR v83[96]; // [esp+0h] [ebp-60h] BYREF

  sprintf_(v83, "%s.c", a1);
  v4 = IO_FOpen(v83, (unsigned __int8 *)aW_2, v3, a3);
  v6 = v4;
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
        Output_WriteFormatted(v61, v60, v6, (int)asc_507D2C, v82);
      }
    }
    Output_WriteFormatted(i, v58, v6, (int)asc_5081DC, v82);
    fclose_(v62);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v5, (int)v83);
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
int  Rules_OpenConstructCodeFile(const char *a1, int a2, int a3, DWORD a4)
{
  char v4; // si
  int v5; // ecx
  char *v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // ebx
  int v10; // edx
  int v11; // ecx
  CHAR v13[84]; // [esp+0h] [ebp-54h] BYREF

  v4 = (char)a1;
  sprintf_(v13, "%s%d_%d.c", a1, a2, a3);
  if ( v5 )
    v6 = aA_0;
  else
    v6 = aW_2;
  v7 = IO_FOpen(v13, (unsigned __int8 *)v6, v5, a4);
  v9 = v7;
  if ( v7 )
  {
    if ( !v8 )
    {
      Output_WriteFormatted(0, v7, v7, (int)aIncludeS_h, v4);
      Output_WriteFormatted(v11, v10, v10, (int)asc_507D2C, v13[0]);
    }
    return v9;
  }
  else
  {
    Rules_OpenFileErrorMessage(v8, (int)v13);
    return 0;
  }
}
// 4A715D: variable 'v5' is possibly undefined
// 4A7175: variable 'v8' is possibly undefined
// 4A718C: variable 'v11' is possibly undefined
// 4A718C: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004A71C0) --------------------------------------------------------
signed int  Rules_WriteHashedExpressionsToCode(DWORD a1)
{
  int i; // ebx
  signed int result; // eax
  int j; // ecx
  __int16 *v4; // edx
  int v5; // ecx

  for ( i = 0; i != 2012; i += 4 )
  {
    result = g_ExpressionHashTable;
    for ( j = *(_DWORD *)(i + g_ExpressionHashTable); j; j = *(_DWORD *)(v5 + 12) )
    {
      v4 = *(__int16 **)(j + 8);
      *(_DWORD *)(j + 16) = g_ClipsCodeMaxIndicesPerArray * g_ClipsExpressionCodeFileVersion + g_ClipsConstructCodeEntryIndexInFile;
      result = Rules_ExpressionToCode(0, v4, j, a1);
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
int  Rules_WriteExpressionRefToCode(int a1, __int16 *a2, int a3, char a4)
{
  signed int v8; // eax
  char v9; // [esp+0h] [ebp-8h]

  if ( !a2 )
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_1, v9);
  v8 = AST_GetHashedNodeIndex(a2);
  return Output_WriteFormatted(v8, v8 % a3, a1, (int)aED_LdLd, a4);
}
// 4A7234: variable 'v9' is possibly undefined

//----- (004A7270) --------------------------------------------------------
signed int  Rules_ExpressionToCode(int a1, __int16 *a2, int a3, DWORD a4)
{
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // ecx
  char v13; // [esp+0h] [ebp-10h]

  if ( a2 )
  {
    if ( a1 )
      Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, g_ClipsConstructCodeEntryIndexInFile, a1, (int)aED_DLd, g_ConstructsToCImageId);
    if ( g_Rules_ExprCodeNeedNewFileFlag == 1 )
    {
      v10 = Rules_OpenConstructCodeFile((const char *)g_Rules_ConstructsToCodeBaseName, 3, g_ClipsExpressionCodeFileVersion, a4);
      g_ClipsCodeDataFile = v10;
      if ( !v10 )
        return -1;
      Output_WriteFormatted(g_ConstructsToCImageId, g_ClipsExpressionCodeFileVersion, v10, (int)aStructExprED_D, g_ConstructsToCImageId);
      Output_WriteFormatted(v12, v11, g_ClipsCodeHeaderFile, (int)aExternStructEx, g_ConstructsToCImageId);
      g_Rules_ExprCodeNeedNewFileFlag = 0;
    }
    else
    {
      Output_WriteFormatted(a3, (int)a2, g_ClipsCodeDataFile, (int)asc_508250, v13);
    }
    Rules_WriteExpressionNodeToCode(a2, v6);
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
    if ( a1 )
      Output_WriteFormatted(a3, 0, a1, (int)aNull_1, v13);
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
  __int16 *v2; // esi
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  unsigned __int16 v8; // ax
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

  v2 = result;
  if ( result )
  {
    while ( 1 )
    {
      Output_WriteFormatted(a2, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_507F14, v20);
      Output_WriteFormatted(g_ClipsCodeDataFile, v3, g_ClipsCodeDataFile, (int)aD_37, *v2);
      Output_WriteFormatted(v5, v4, g_ClipsCodeDataFile, (int)aVs, v21);
      v8 = *v2;
      if ( (unsigned __int16)*v2 >= 0xAu )
      {
        if ( (unsigned __int16)*v2 <= 0xAu )
        {
          Rules_WriteFunctionRecordRefToCode(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), v7);
        }
        else if ( v8 >= 0x23u )
        {
          if ( v8 <= 0x23u )
          {
            Rules_DeftemplateWriteRecordRefToCode(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), g_ClipsCodeMaxIndicesPerArray);
          }
          else if ( v8 >= 0x3Cu )
          {
            if ( v8 <= 0x3Cu )
            {
              Defglobal_WriteDefglobalArrayReference(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), g_ClipsCodeMaxIndicesPerArray);
            }
            else
            {
              if ( v8 != 105 )
                goto LABEL_20;
              Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)aNull_1, v22);
            }
          }
          else
          {
            if ( v8 != 57 )
              goto LABEL_20;
            ObjectsCompiler_WriteDefclassPointerRef(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), g_ClipsCodeMaxIndicesPerArray);
          }
        }
        else if ( v8 < 0xCu )
        {
          Defgeneric_PrintModuleIndexOrNull(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), g_ClipsCodeMaxIndicesPerArray);
        }
        else
        {
          if ( v8 > 0xCu )
          {
            if ( v8 != 13 )
              goto LABEL_20;
LABEL_36:
            Compiler_WriteSymbolReference(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), v7);
            goto LABEL_6;
          }
          Deffunction_WriteConstructReference(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), g_ClipsCodeMaxIndicesPerArray);
        }
      }
      else if ( v8 >= 3u )
      {
        if ( v8 <= 3u )
          goto LABEL_36;
        if ( v8 >= 7u )
        {
          if ( v8 > 7u )
          {
            if ( v8 != 8 )
            {
LABEL_20:
              v18 = g_Clips_PrimitiveEntityTable[*v2];
              if ( v18 )
              {
                if ( (*(_BYTE *)(v18 + 1) & 0x40) != 0 )
                  Compiler_WriteBitMapReference(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1), v7);
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
          if ( v8 != 6 )
            goto LABEL_20;
          Output_WriteFormatted(v7, v6, g_ClipsCodeDataFile, (int)aDummyfact, v22);
        }
      }
      else
      {
        if ( !v8 )
        {
          Compiler_WriteFloatReference(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1));
          goto LABEL_6;
        }
        if ( v8 > 1u )
          goto LABEL_36;
        Compiler_WriteIntegerReference(g_ClipsCodeDataFile, *(_DWORD *)(v2 + 1));
      }
LABEL_6:
      Output_WriteFormatted(v10, v9, g_ClipsCodeDataFile, (int)asc_508278, v22);
      ++g_ClipsConstructCodeEntryIndexInFile;
      if ( *(_DWORD *)(v2 + 3) )
        Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, v11, g_ClipsCodeDataFile, (int)aED_DLd_0, g_ConstructsToCImageId);
      else
        Output_WriteFormatted(v12, v11, g_ClipsCodeDataFile, (int)aNull_0, v23);
      if ( *(_DWORD *)(v2 + 5) )
      {
        AST_CountTreeNodes(*(_DWORD *)(v2 + 3));
        result = (__int16 *)Output_WriteFormatted(g_ClipsExpressionCodeFileVersion, v19, g_ClipsCodeDataFile, (int)aED_DLd_1, g_ConstructsToCImageId);
      }
      else
      {
        result = (__int16 *)Output_WriteFormatted(v14, v13, g_ClipsCodeDataFile, (int)aNull_2, v23);
      }
      if ( *(_DWORD *)(v2 + 3) )
      {
        Output_WriteFormatted(v16, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_508250, v23);
        result = (__int16 *)Rules_WriteExpressionNodeToCode(*(_DWORD *)(v2 + 3), v17);
      }
      v2 = *(__int16 **)(v2 + 5);
      if ( !v2 )
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
int  Rules_AddCodeGeneratorItem(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int construct_code_count; // ecx
  _DWORD *v9; // ebx
  int v10; // ebp
  _DWORD *v11; // eax
  int v12; // ebx
  int v13; // edi
  _DWORD *v15; // eax
  int slot_offset; // edx
  char *v17; // esi
  char *v18; // edi
  int v19; // edx
  char v20; // al
  char v21; // al
  int v22; // eax
  int result; // eax
  int v25; // [esp+4h] [ebp-18h]
  char v27[16]; // [esp+Ch] [ebp-10h] BYREF

  construct_code_count = a6;
  v9 = *(_DWORD **)(g_ClipsMemoryTable + 112);
  v10 = 0;
  if ( v9 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(g_ClipsMemoryTable + 112) = *v9;
    v11 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v11 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  *v11 = a1;
  v11[2] = a3;
  v11[1] = a4;
  v11[3] = a5;
  v12 = (int)v11;
  v11[4] = a2;
  if ( construct_code_count )
  {
    if ( construct_code_count + g_Rules_CodeGeneratorItemIndex > 44 )
    {
      Rules_ReportSystemError((int)aConscomp, 2);
      IO_RunRouterExitCallbacks();
    }
    v13 = 4 * construct_code_count;
    *(_DWORD *)(v12 + 20) = Mem_SmallBlockAlloc(4 * construct_code_count);
    if ( construct_code_count > 0 )
    {
      v25 = v13;
      slot_offset = 0;
      do
      {
        if ( g_Rules_CodeGeneratorItemIndex >= 18 )
          sprintf_(v27, "%c_", (unsigned __int8)g_Rules_CodeGeneratorItemPrefixTable[g_Rules_CodeGeneratorItemIndex]);
        else
          sprintf_(v27, "%c", (unsigned __int8)g_Rules_CodeGeneratorItemLetterTable[g_Rules_CodeGeneratorItemIndex]);
        ++g_Rules_CodeGeneratorItemIndex;
        v15 = Mem_SmallBlockAlloc(strlen(v27) + 1);
        *(_DWORD *)(*(_DWORD *)(v12 + 20) + slot_offset) = v15;
        v17 = v27;
        v18 = (char *)v15;
        v19 = slot_offset + 4;
        do
        {
          v20 = *v17;
          *v18 = *v17;
          if ( !v20 )
            break;
          v21 = v17[1];
          v17 += 2;
          v18[1] = v21;
          v18 += 2;
        }
        while ( v21 );
        slot_offset = v19;
      }
      while ( v19 < v25 );
    }
  }
  else
  {
    v11[5] = 0;
  }
  if ( g_CodeGeneratorItemList )
  {
    v22 = g_CodeGeneratorItemList;
    do
    {
      if ( a2 >= *(_DWORD *)(v22 + 16) )
        break;
      v10 = v22;
      v22 = *(_DWORD *)(v22 + 24);
    }
    while ( v22 );
    if ( v10 )
    {
      *(_DWORD *)(v12 + 24) = v22;
      *(_DWORD *)(v10 + 24) = v12;
    }
    else
    {
      *(_DWORD *)(v12 + 24) = g_CodeGeneratorItemList;
      g_CodeGeneratorItemList = v12;
    }
    return v12;
  }
  else
  {
    *(_DWORD *)(v12 + 24) = 0;
    result = v12;
    g_CodeGeneratorItemList = v12;
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
int  Rules_ConstructCodeFileClose(int result, int *a2, int a3, _DWORD *a4, _DWORD *a5, int a6)
{
  int v6; // esi
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  char v11; // [esp+0h] [ebp-Ch]

  v6 = result;
  v8 = a3;
  v9 = a6;
  if ( v8 > *a2 )
  {
    if ( !a5 )
      return result;
    *a5 = 1;
    fclose_(a6);
    return 0;
  }
  if ( a5 )
    *a5 = 0;
  if ( !result )
  {
    if ( !a5 || !a6 )
    {
      Rules_ReportSystemError(a6, 3);
      IO_RunRouterExitCallbacks();
    }
    if ( !*(_DWORD *)v9 )
      return 0;
    v6 = Rules_OpenConstructCodeFile(*(const char **)v9, *(_DWORD *)(v9 + 4), *(_DWORD *)(v9 + 8), (DWORD)a4);
    if ( !v6 )
    {
      Rules_ReportSystemError(v9, 4);
      IO_RunRouterExitCallbacks();
    }
  }
  Output_WriteFormatted(v9, v8, v6, (int)asc_507DA0, v11);
  fclose_(v10);
  *a2 = 0;
  result = 0;
  ++*a4;
  return result;
}
// 4A7983: variable 'v9' is possibly undefined
// 4A79C0: variable 'v8' is possibly undefined
// 4A79C0: variable 'v11' is possibly undefined
// 4A79CA: variable 'v10' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (004A79F0) --------------------------------------------------------
int  Rules_ConstructCodeFileOpen(
        int a1,
        const char *a2,
        int a3,
        const char *a4,
        int *a5,
        int a6,
        int a7,
        char a8,
        const char *a9,
        int a10,
        const char **a11)
{
  const char **v13; // ecx
  const char *v14; // edi
  int v15; // edx
  int v16; // eax
  int result; // eax
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // edx
  int v24; // [esp-8h] [ebp-68h]
  char v25[80]; // [esp+0h] [ebp-60h] BYREF
  int v26; // [esp+50h] [ebp-10h]

  v26 = a3;
  v13 = a11;
  if ( a10 )
  {
    if ( !a11 )
    {
      Rules_ReportSystemError(0, 5);
      IO_RunRouterExitCallbacks();
    }
    v14 = *v13;
    v15 = (int)v13[1];
    v16 = (int)v13[2];
  }
  else
  {
    v14 = a2;
    v15 = (int)a4;
    v16 = *a5;
    if ( a11 )
    {
      a11[2] = (const char *)v16;
      *a11 = a2;
      a11[1] = a4;
    }
  }
  if ( a1 )
  {
    Output_WriteFormatted((int)v13, v15, a1, (int)asc_508250, v25[0]);
    return a1;
  }
  else
  {
    result = Rules_OpenConstructCodeFile(v14, v15, v16, (DWORD)a2);
    if ( result )
    {
      if ( a10 )
      {
        Output_WriteFormatted(result, result, result, (int)asc_508250, v25[0]);
        return v23;
      }
      else
      {
        v24 = v26;
        ++*a5;
        sprintf_(v25, "%s%d_%d", a9, v24, a6);
        Output_WriteFormatted(v19, v18, v19, (int)aSS_0, a8);
        Output_WriteFormatted(v21, v20, a7, (int)aExternSS, a8);
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
int  Rules_AssignNextModuleItemId(int a1, _DWORD *a2)
{
  int result; // eax

  result = (*a2)++;
  *(_DWORD *)(a1 + 12) = result;
  return result;
}

//----- (004A7B60) --------------------------------------------------------
int  Rules_WriteConstructHeaderToCode(int a1, int a2, signed int a3, int a4, int a5, char a6)
{
  int *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  char v18; // [esp+0h] [ebp-Ch]
  char v19; // [esp+0h] [ebp-Ch]
  char v20; // [esp+0h] [ebp-Ch]
  char v21; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a4, a2, a1, (int)asc_507F14, v18);
  Compiler_WriteSymbolReference(a1, *v9, v10);
  Output_WriteFormatted(v11, v11, a1, (int)aNull_17, v19);
  Output_WriteFormatted(v12, a5, a1, (int)aMihsSD_DD_2, a5);
  Output_WriteFormatted(v14, v13, a1, (int)a0_1, v20);
  v16 = *(_DWORD *)(a2 + 16);
  if ( v16 )
    return Output_WriteFormatted(v16, *(_DWORD *)(v16 + 12) % a3, a1, (int)aChsSD_LdLd, a6);
  else
    return Output_WriteFormatted(0, v15, a1, (int)aNull_2, v21);
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
int  Rules_WriteConstructModuleItemHeaderToCode(int a1, int a2, int a3, int a4, char a5)
{
  int v7; // edx
  int v8; // ebx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // edi
  int v16; // edx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  int v20; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a4, a1, (int)asc_507F14, v19);
  v8 = Module_GetItem(a2, v7);
  Compiler_WriteModuleReference(a1, a2);
  Output_WriteFormatted(v10, v9, a1, (int)asc_508278, v8);
  v12 = *(_DWORD *)(v8 + 4);
  if ( v12 )
    Output_WriteFormatted(v11, *(_DWORD *)(v12 + 12) % v11, a1, (int)aChsSD_LdLd_0, a5);
  else
    Output_WriteFormatted(v11, 0, a1, (int)aNull_0, v20);
  v15 = *(_DWORD *)(v20 + 8);
  if ( v15 )
    Output_WriteFormatted(v14, *(_DWORD *)(v15 + 12) % v14, a1, (int)aChsSD_LdLd_1, a5);
  else
    Output_WriteFormatted(v14, v13, a1, (int)aNull_1, v20);
  return Output_WriteFormatted(v17, v16, a1, (int)asc_508384, v20);
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
int  IO_RenameFile(const CHAR *a1, const CHAR *a2, int a3)
{
  if ( MoveFileA(a1, a2) )
    return 0;
  else
    return _set_errno_nt_(a3);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (004A7DC0) --------------------------------------------------------
signed int  Rules_PrintArgumentValueList(int a1, _DWORD *a2)
{
  int v2; // ecx
  __int16 v4; // bx
  signed int result; // eax
  int v6; // edi

  v2 = a1;
  v4 = 0;
  while ( 1 )
  {
    result = *a2 << 17 >> 23;
    if ( v4 >= result )
      break;
    v6 = *(_DWORD *)a2[v4 + 2];
    if ( v6 )
      (*(void (**)(void))(*(_DWORD *)v6 + 4))();
    if ( ++v4 < *a2 << 17 >> 23 )
      Output_Write(v2, (int)asc_5083B0, v2);
  }
  return result;
}
// 4A7E05: variable 'v2' is possibly undefined

//----- (004A7E20) --------------------------------------------------------
_DWORD * Rules_MultifieldCopyWithMarkers(int *a1, int a2, int a3)
{
  int v4; // eax
  signed int v5; // eax
  char v6; // dl
  __int16 v7; // cx
  int v8; // edx
  _DWORD *v9; // ebx
  __int16 i; // ax
  int v11; // ecx
  _DWORD *v12; // esi

  v4 = a3 + a2 + ((unsigned int)(*a1 << 17) >> 23);
  if ( (unsigned int)(4 * v4 + 8) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 16 * v4 + 32) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(16 * (a3 + a2 + ((unsigned int)(*a1 << 17) >> 23)) + g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 16 * (a3 + a2 + ((unsigned int)(*a1 << 17) >> 23)) + 32) = *(_DWORD *)g_ClipsMemFreeListTemp;
    v5 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v5 = Mem_HeapAllocWithRetry((_DWORD *)(4 * (a3 + a2 + ((unsigned int)(*a1 << 17) >> 23)) + 8));
  }
  v6 = *(_BYTE *)v5 | 1;
  *(_BYTE *)v5 = v6;
  *(_BYTE *)v5 = v6 & 0xF9;
  *(_DWORD *)v5 |= 4 * (a2 & 1);
  *(_BYTE *)v5 &= ~8u;
  *(_DWORD *)v5 |= 8 * (a3 & 1);
  *(_BYTE *)v5 &= 0xCFu;
  v7 = *(_WORD *)v5;
  *(_DWORD *)(v5 + 4) = 0;
  v8 = *a1;
  *(_WORD *)v5 = v7 & 0x803F;
  v9 = (_DWORD *)v5;
  *(_DWORD *)v5 |= v8 & 0x7FC0;
  for ( i = 0; ; ++i )
  {
    v11 = i;
    v12 = &v9[v11];
    if ( i >= *v9 << 17 >> 23 )
      break;
    v12[2] = a1[v11 + 2];
  }
  if ( a2 )
  {
    ++i;
    v12[2] = 0;
  }
  if ( a3 )
    v9[i + 2] = 0;
  return v9;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A7F90) --------------------------------------------------------
_WORD * Rules_MergeMultifieldValues(_DWORD *a1, _DWORD *a2, int a3, int a4)
{
  int v6; // eax
  signed int v7; // eax
  char v8; // bl
  char v9; // bh
  int v10; // ecx
  _WORD *v11; // edx
  __int16 i; // ax
  int v13; // ebx
  int v14; // eax
  int j; // ebx
  _WORD *v16; // esi
  int v17; // ecx

  v6 = a3 + a4 + (*a1 << 17 >> 23) + (*a2 << 17 >> 23);
  if ( (unsigned int)(4 * v6 + 8) < 0x1F4 && *(_DWORD *)(16 * v6 + g_ClipsMemoryTable + 32) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(16 * (a3 + a4 + (*a1 << 17 >> 23) + (*a2 << 17 >> 23)) + g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 16 * (a3 + a4 + (*a1 << 17 >> 23) + (*a2 << 17 >> 23)) + 32) = *(_DWORD *)g_ClipsMemFreeListTemp;
    v7 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v7 = Mem_HeapAllocWithRetry((_DWORD *)(4 * (a3 + a4 + (*a1 << 17 >> 23) + (*a2 << 17 >> 23)) + 8));
  }
  v8 = *(_BYTE *)v7 | 1;
  *(_BYTE *)v7 = v8;
  *(_BYTE *)v7 = v8 & 0xF9;
  *(_DWORD *)v7 |= 4 * (a4 & 1);
  *(_BYTE *)v7 &= ~8u;
  *(_DWORD *)v7 |= 8 * (a3 & 1);
  v9 = *(_BYTE *)v7;
  *(_DWORD *)(v7 + 4) = 0;
  *(_BYTE *)v7 = v9 & 0xCF;
  v10 = (((unsigned __int16)(2 * *(_WORD *)a1) >> 7) + ((unsigned __int16)(2 * *(_WORD *)a2) >> 7)) & 0x1FF;
  *(_WORD *)v7 &= 0x803Fu;
  v11 = (_WORD *)v7;
  *(_DWORD *)v7 |= v10 << 6;
  for ( i = 0; i < *a1 << 17 >> 23; ++i )
  {
    v13 = 4 * i;
    *(_DWORD *)&v11[v13 / 2u + 4] = a1[v13 / 4u + 2];
  }
  v14 = *a1 << 17 >> 23;
  for ( j = 0; ; ++j )
  {
    v16 = &v11[2 * (__int16)v14];
    if ( (__int16)v14 >= (unsigned __int16)(2 * *v11) >> 7 )
      break;
    LOWORD(v14) = v14 + 1;
    v17 = a2[(__int16)j + 2];
    *((_DWORD *)v16 + 2) = v17;
  }
  if ( a4 )
  {
    LOWORD(v14) = v14 + 1;
    *((_DWORD *)v16 + 2) = 0;
  }
  if ( a3 )
    *(_DWORD *)&v11[2 * (__int16)v14 + 4] = 0;
  return v11;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8170) --------------------------------------------------------
int  Rules_ResetDataObjectValue(int a1)
{
  char v1; // al
  int v2; // edx
  int result; // eax

  *(_DWORD *)(a1 + 8) = 0;
  *(_DWORD *)a1 = 0;
  *(_DWORD *)(a1 + 4) = 0;
  *(_BYTE *)(a1 + 12) &= 0xF8u;
  v1 = Rules_GetIncrementalReset();
  *(_BYTE *)(v2 + 12) &= ~8u;
  result = 8 * (v1 & 1);
  *(_DWORD *)(v2 + 12) |= result;
  *(_BYTE *)(v2 + 12) &= 0x8Fu;
  return result;
}
// 4A8196: variable 'v2' is possibly undefined

//----- (004A81C0) --------------------------------------------------------
signed int  Rules_AppendExpressionValueNode(int a1, _DWORD *a2, signed int *a3)
{
  _DWORD *v5; // edx
  signed int v6; // eax
  char v7; // cl
  signed int v8; // edx
  _DWORD *v9; // ecx
  _DWORD *v10; // ecx
  _DWORD *v11; // ebp
  _DWORD *v12; // eax
  int v13; // ecx
  signed int v14; // esi

  v5 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( v5 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *v5;
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
  v8 = v6;
  v9 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( v9 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *v9;
    v10 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v10 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  v10[2] = 0;
  v11 = v10;
  *v10 = a1;
  if ( a2 )
  {
    v12 = Rules_CopyExpressionChain(a2);
    *(_DWORD *)(v13 + 4) = v12;
  }
  else
  {
    v10[1] = 0;
  }
  *(_DWORD *)(v8 + 8) = v11;
  v14 = a3[1];
  if ( v14 )
    *(_DWORD *)(v14 + 4) = v8;
  else
    *a3 = v8;
  a3[1] = v8;
  return v8;
}
// 4A8231: variable 'v13' is possibly undefined
// 4A8234: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8280) --------------------------------------------------------
signed int  Rules_MultifieldAppendValue(_DWORD *a1, int a2, int a3, int a4)
{
  int v5; // eax
  signed int v6; // eax
  char v7; // dl
  char v8; // bh
  __int16 v9; // dx
  signed int v10; // ebp
  __int16 i; // ax
  int v12; // ecx
  int v13; // ebx
  __int16 v14; // ax
  int v15; // edx

  v5 = a3 + a4 + (*a1 << 17 >> 23);
  if ( (unsigned int)(4 * v5 + 12) < 0x1F4 && *(_DWORD *)(16 * v5 + g_ClipsMemoryTable + 48) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(16 * (a3 + a4 + (*a1 << 17 >> 23)) + g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 16 * (a3 + a4 + (*a1 << 17 >> 23)) + 48) = *(_DWORD *)g_ClipsMemFreeListTemp;
    v6 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v6 = Mem_HeapAllocWithRetry((_DWORD *)(4 * (a3 + a4 + (*a1 << 17 >> 23)) + 12));
  }
  v7 = *(_BYTE *)v6 | 1;
  *(_BYTE *)v6 = v7;
  *(_BYTE *)v6 = v7 & 0xF9;
  *(_DWORD *)v6 |= 4 * (a4 & 1);
  *(_BYTE *)v6 &= ~8u;
  *(_DWORD *)v6 |= 8 * (a3 & 1);
  v8 = *(_BYTE *)v6;
  *(_DWORD *)(v6 + 4) = 0;
  *(_BYTE *)v6 = v8 & 0xCF;
  v9 = ((unsigned __int16)(2 * *(_WORD *)a1) >> 7) + 1;
  *(_WORD *)v6 &= 0x803Fu;
  v10 = v6;
  *(_DWORD *)v6 |= (v9 & 0x1FF) << 6;
  for ( i = 0; ; ++i )
  {
    v12 = i;
    v13 = v12 * 4 + v10;
    if ( i >= *a1 << 17 >> 23 )
      break;
    *(_DWORD *)(v13 + 8) = a1[v12 + 2];
  }
  *(_DWORD *)(v13 + 8) = a2;
  v14 = i + 1;
  if ( a4 )
  {
    v15 = v14++;
    *(_DWORD *)(v10 + 4 * v15 + 8) = 0;
  }
  if ( a3 )
    *(_DWORD *)(v10 + 4 * v14 + 8) = 0;
  return v10;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8410) --------------------------------------------------------
_DWORD * Rules_CopyExpressionChain(_DWORD *a1)
{
  _DWORD *v1; // edx
  _DWORD *v2; // edi
  _DWORD *i; // ecx
  _DWORD *v4; // ebx
  _DWORD *v5; // eax

  v1 = a1;
  v2 = 0;
  for ( i = 0; v1; i = v5 )
  {
    v4 = *(_DWORD **)(g_ClipsMemoryTable + 80);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
      *(_DWORD *)(g_ClipsMemoryTable + 80) = *v4;
      v5 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v5 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    v5[4] = 0;
    *v5 = *v1;
    v5[1] = v1[1];
    v5[2] = v1[2];
    v5[3] = v1[3];
    if ( i )
      i[4] = v5;
    else
      v2 = v5;
    v1 = (_DWORD *)v1[4];
  }
  return v2;
}
// 4A845C: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004A8520) --------------------------------------------------------
int  Rules_ReleaseJoinNetworkNodeChain(int result)
{
  int v1; // edx
  int v2; // edx

  if ( result )
  {
    do
    {
      while ( 1 )
      {
        v1 = *(_DWORD *)(result + 4);
        if ( ((*(_BYTE *)result & 0x10) == 0 || (*(_BYTE *)result & 0x20) != 0) && (*(_BYTE *)result & 1) != 0 )
          break;
        *(_DWORD *)(result + 4) = g_PartialMatchFreeListHead;
        g_PartialMatchFreeListHead = result;
        result = v1;
        if ( !v1 )
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
int  Rules_CountJoinNetworkEntryNodes(int a1)
{
  int v1; // edx

  v1 = 0;
  if ( !a1 )
    return v1;
  do
  {
    while ( (*(_BYTE *)a1 & 4) != 0 )
    {
      a1 = *(_DWORD *)(a1 + 16);
      if ( !a1 )
        return v1;
    }
    ++v1;
    a1 = *(_DWORD *)(a1 + 24);
  }
  while ( a1 );
  return v1;
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
  int v2; // ebx
  uintptr_t node; // eax
  unsigned int flags; // edx
  int next_rule; // edx

  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    v2 = Rules_GetNextDefrule(0);
    while ( v2 )
    {
      node = (uintptr_t)(unsigned int)*(_DWORD *)(v2 + 44);
      while ( node )
      {
        flags = *(_DWORD *)node & 0xFFFFFFDF;
        *(_DWORD *)node = flags;
        node = (uintptr_t)(unsigned int)*(_DWORD *)(node + ((*(_BYTE *)node & 4) != 0 ? 16 : 24));
      }
      next_rule = *(_DWORD *)(v2 + 48);
      if ( next_rule )
        v2 = next_rule;
      else
        v2 = Rules_GetNextDefrule(v2);
    }
  }
  return Module_EndEnum();
}

//----- (004A86F0) --------------------------------------------------------
int  Rules_JoinNetworkAssignCodeGenIds(_DWORD *a1, int *a2, int *a3)
{
  int result; // eax
  int i; // edi
  _DWORD *v7; // ecx
  int v8; // eax
  int v9; // eax
  int v10; // edx
  int v11; // edx

  *a1 = 0;
  *a2 = 0;
  *a3 = 0;
  Rules_ClearJoinNetworkMarkedFlags();
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ++*a1;
    Module_SetCurrent(i);
    v7 = (_DWORD *)Rules_GetNextDefrule(0);
    while ( v7 )
    {
      v8 = *a2;
      v7[3] = *a2;
      *a2 = v8 + 1;
      v9 = v7[11];
      if ( v9 )
      {
        do
        {
          if ( (*(_BYTE *)v9 & 0x20) == 0 )
          {
            *(_BYTE *)v9 |= 0x20u;
            v10 = *a3;
            *(_DWORD *)(v9 + 4) = *a3;
            *a3 = v10 + 1;
          }
          if ( (*(_BYTE *)v9 & 4) != 0 )
            v11 = *(_DWORD *)(v9 + 16);
          else
            v11 = *(_DWORD *)(v9 + 24);
          v9 = v11;
        }
        while ( v11 );
      }
      if ( v7[12] )
        v7 = (_DWORD *)v7[12];
      else
        v7 = (_DWORD *)Rules_GetNextDefrule((int)v7);
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
  int *v0; // eax

  g_Rules_EntityTimeTagCounter = 0;
  Rules_ClearFocusStack();
  v0 = Module_FindByName(aMain_4);
  return Rules_PushFocus((int)v0);
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
  int *v0; // eax

  v0 = Module_FindByName(aMain_4);
  return Rules_PushFocus((int)v0);
}
// 4A8920: using guessed type int sub_4A8920();

//----- (004A8930) --------------------------------------------------------
int  Rules_SaveDefrules(signed int a1)
{
  return Rules_SaveConstruct(a1, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8940) --------------------------------------------------------
int __thiscall Rules_UndefruleCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8960) --------------------------------------------------------
int  Rules_DeleteDefruleOrAll(int a1, int a2)
{
  return Rules_DeleteConstructOrAll(a1, g_DefruleConstructTypePtr, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8970) --------------------------------------------------------
_DWORD * Rules_GetDefruleListFunction(int a1, double a2)
{
  return Rules_GetConstructListCommand(a1, g_DefruleConstructTypePtr, a2);
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
int  Rules_TestInheritedFlagBit4(int a1)
{
  if ( !a1 )
    return 0;
  while ( (*(_BYTE *)(a1 + 29) & 0x10) == 0 )
  {
    a1 = *(_DWORD *)(a1 + 48);
    if ( !a1 )
      return 0;
  }
  return 1;
}

//----- (004A8A60) --------------------------------------------------------
int  Rules_TestInheritedFlagBit5(int a1)
{
  if ( !a1 )
    return 0;
  while ( (*(_BYTE *)(a1 + 29) & 0x20) == 0 )
  {
    a1 = *(_DWORD *)(a1 + 48);
    if ( !a1 )
      return 0;
  }
  return 1;
}

//----- (004A8A80) --------------------------------------------------------
int  Rules_SetInheritedFlagBit4(char a1, int a2)
{
  int result; // eax

  for ( result = a2; result; result = *(_DWORD *)(result + 48) )
  {
    *(_BYTE *)(result + 29) &= ~0x10u;
    *(_DWORD *)(result + 28) |= (a1 & 1) << 12;
  }
  return result;
}

//----- (004A8AB0) --------------------------------------------------------
int  Rules_SetInheritedFlagBit5(char a1, int a2)
{
  int result; // eax

  for ( result = a2; result; result = *(_DWORD *)(result + 48) )
  {
    *(_BYTE *)(result + 29) &= ~0x20u;
    *(_DWORD *)(result + 28) |= (a1 & 1) << 13;
  }
  return result;
}

//----- (004A8AE0) --------------------------------------------------------
signed int  Rules_DefruleWatchAccess(int a1, int a2, int a3, double a4)
{
  if ( a1 )
    return Rules_ApplyWatchFlagCommand(g_DefruleConstructTypePtr, a2, (int)Rules_TestInheritedFlagBit4, a3, a4, (void (*)(void))Rules_SetInheritedFlagBit4);
  else
    return Rules_ApplyWatchFlagCommand(g_DefruleConstructTypePtr, a2, (int)Rules_TestInheritedFlagBit5, a3, a4, (void (*)(void))Rules_SetInheritedFlagBit5);
}
// 4A8A40: using guessed type int sub_4A8A40();
// 4A8A60: using guessed type int sub_4A8A60();
// 54E648: using guessed type int dword_54E648;

//----- (004A8B20) --------------------------------------------------------
signed int  Rules_DefruleWatchPrint(int a1, int a2, double a3)
{
  return Rules_ListWatchFlagStatus(g_DefruleConstructTypePtr, a1, (int)Rules_TestInheritedFlagBit4, a2, a3, (void (*)(void))Rules_SetInheritedFlagBit4);
}
// 4A8A40: using guessed type int sub_4A8A40();
// 54E648: using guessed type int dword_54E648;

//----- (004A8B40) --------------------------------------------------------
int  Rules_AppendConstructToModuleList(int result)
{
  int v1; // edx
  int v2; // ecx

  v1 = *(_DWORD *)(result + 8);
  v2 = *(_DWORD *)(v1 + 8);
  if ( v2 )
    *(_DWORD *)(v2 + 16) = result;
  else
    *(_DWORD *)(v1 + 4) = result;
  *(_DWORD *)(*(_DWORD *)(result + 8) + 8) = result;
  *(_DWORD *)(result + 16) = 0;
  return result;
}

//----- (004A8B80) --------------------------------------------------------
int __fastcall Rules_TryDeleteConstruct(int a1, int a2)
{
  int v4; // ecx

  if ( Rules_IsBloaded() == 1 )
    return 0;
  if ( (*(int (__cdecl **)(int))(a2 + 12))(a1) )
    return (*(int (**)(void))(a2 + 40))();
  if ( strcmp_(v4, v4) )
    return 0;
  (*(void (**)(void))(a2 + 40))();
  return 1;
}
// 4A8BA5: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A8BD0) --------------------------------------------------------
int  Rules_FindConstructByNameGeneric(_BYTE *a1, int a2)
{
  _BYTE *local_name; // eax
  int *target_symbol; // ebx
  int get_name_func; // [ecx+10h]
  int next_func; // [ecx+1Ch]
  int current_item; // edx

  Module_BeginEnum();
  local_name = (_BYTE *)Rules_ExtractModuleAndConstructName(a1);
  if ( local_name )
  {
    target_symbol = Rules_FindSymbolEntry(local_name);
    if ( target_symbol )
    {
      get_name_func = *(_DWORD *)(a2 + 16);
      next_func = *(_DWORD *)(a2 + 28);
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
int __fastcall Rules_UndefconstructCommand(int a1, int a2)
{
  double v4; // st7
  int v5; // ecx
  int result; // eax
  int v7; // esi
  int v8; // ecx
  int v9; // ecx
  _BYTE v10[84]; // [esp+0h] [ebp-5Ch] BYREF
  int v11; // [esp+54h] [ebp-8h]

  v11 = a1;
  v4 = sprintf_(v10, "%s name", (const char *)*(_DWORD *)a2);
  result = Rules_GetConstructNameArg((int)v10, v5, v4);
  v7 = result;
  if ( result )
  {
    if ( (*(int (__thiscall **)(int))(a2 + 12))(result) || !strcmp_(v8, v8) )
    {
      result = Rules_TryDeleteConstruct(v8, a2);
      if ( !result )
        return Rules_ReportCantDeleteItem(v9, v7);
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
int __fastcall Rules_PPConstructCommand(int a1, const char **a2)
{
  double v4; // st7
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  _BYTE v8[84]; // [esp+0h] [ebp-5Ch] BYREF
  int v9; // [esp+54h] [ebp-8h]

  v9 = a1;
  v4 = sprintf_(v8, "%s name", *a2);
  result = Rules_GetConstructNameArg((int)v8, v5, v4);
  if ( result )
  {
    result = Rules_PrintConstructPPForm((int)g_IO_LogicalName_WDisplay, result, (int)a2);
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
int  Rules_PrintConstructPPForm(int a1, int a2, int a3)
{
  int result; // eax
  char *v4; // eax
  signed int v5; // ecx

  result = (*(int (__thiscall **)(int, int))(a3 + 12))(a1, a2);
  if ( result )
  {
    if ( (*(int (**)(void))(a3 + 20))() )
    {
      v4 = (char *)(*(int (**)(void))(a3 + 20))();
      Output_WriteLongString(v5, v4);
    }
    return 1;
  }
  return result;
}
// 4A8D35: variable 'v5' is possibly undefined

//----- (004A8D50) --------------------------------------------------------
int __fastcall Rules_GetConstructModuleCommand(int a1, const char **a2)
{
  double v3; // st7
  int v4; // ecx
  _BYTE *v5; // eax
  int *v7; // eax
  int v8; // ecx
  _BYTE v9[80]; // [esp+0h] [ebp-58h] BYREF
  int v10; // [esp+50h] [ebp-8h]

  v10 = a1;
  v3 = sprintf_(v9, "%s name", *a2);
  v5 = (_BYTE *)Rules_GetConstructNameArg((int)v9, v4, v3);
  if ( !v5 )
    return g_ClipsFalseSymbol;
  v7 = Rules_GetConstructModuleName(v5, (int)v5);
  if ( v7 )
    return *v7;
  Rules_ReportCantFindItem(v8, v8);
  return g_ClipsFalseSymbol;
}
// 4A8D72: variable 'v4' is possibly undefined
// 4A8D9F: variable 'v8' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 54DD70: using guessed type int dword_54DD70;

//----- (004A8DB0) --------------------------------------------------------
int * Rules_GetConstructModuleName(_BYTE *a1, int a2)
{
  signed int v3; // eax
  char **v4; // ecx
  signed int *v5; // eax
  int *result; // eax
  _DWORD v7[3]; // [esp+0h] [ebp-Ch] BYREF

  v7[1] = a2;
  v3 = Rules_FindModuleSeparator(a1);
  if ( v3 )
  {
    v5 = Rules_ExtractModuleName(v3);
    if ( v5 )
      return Module_FindByName((_BYTE *)v5[4]);
  }
  result = (int *)Rules_FindImportExportConstruct(*v4, v7, a1, 1, 0);
  if ( result )
    return *(int **)result[2];
  return result;
}
// 4A8DCF: variable 'v4' is possibly undefined

//----- (004A8E00) --------------------------------------------------------
int  Rules_DeleteConstructOrAll(int a1, int a2, int a3)
{
  int v4; // ecx
  int v5; // esi
  int v6; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int result; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx

  if ( a1 )
  {
    result = (*(int (__cdecl **)(int))(a2 + 36))(a3);
    if ( result )
    {
      Rules_UnlinkListNode(a1);
      (*(void (**)(void))(v14 + 44))();
      if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
        Rules_RunPeriodicCleanup(1, 0);
      return 1;
    }
  }
  else
  {
    v5 = 1;
    if ( (*(int (**)(void))(a2 + 28))() )
    {
      do
      {
        v6 = ((__int64 (*)(void))*(_DWORD *)(v4 + 28))();
        if ( (*(int (**)(void))(v7 + 36))() )
        {
          Rules_UnlinkListNode(v8);
          (*(void (**)(void))(v10 + 44))();
        }
        else
        {
          v12 = (*(int (**)(void))(v9 + 16))();
          v5 = 0;
          Rules_ReportCantDeleteItem(v13, *(_DWORD *)(v12 + 16));
        }
      }
      while ( v6 );
    }
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      Rules_RunPeriodicCleanup(1, 0);
    return v5;
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
int  Rules_SaveConstruct(signed int a1, int a2)
{
  int i; // edi
  char *v5; // eax
  int v6; // ecx

  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    while ( (*(int (**)(void))(a2 + 28))() )
    {
      v5 = (char *)(*(int (**)(void))(a2 + 20))();
      if ( v5 )
      {
        Output_WriteLongString(a1, v5);
        Output_Write(a1, (int)asc_50849C, v6);
      }
    }
  }
  return Module_EndEnum();
}
// 4A8F08: variable 'v6' is possibly undefined

//----- (004A8F40) --------------------------------------------------------
int  Rules_GetConstructNameString(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 16);
}

//----- (004A8F50) --------------------------------------------------------
int  Rules_GetConstructNameSymbol(int a1)
{
  return *(_DWORD *)a1;
}

//----- (004A8F60) --------------------------------------------------------
_DWORD * Rules_GetConstructListCommand(int a1, int a2, double a3)
{
  int v3; // eax
  int v4; // ecx
  int *v5; // eax
  _DWORD *v6; // ecx
  int v8; // edx
  _DWORD v9[2]; // [esp-4h] [ebp-24h] BYREF
  int v10; // [esp+4h] [ebp-1Ch]
  int v11; // [esp+1Ch] [ebp-4h]

  v11 = a1;
  v3 = Lexer_TokenExpect(1);
  if ( v3 == -1 )
    return Rules_SetMultifieldErrorValue(v4);
  if ( v3 == 1 )
  {
    Rules_RtnUnknown(1, v9, a3);
    if ( v9[1] != 2
      || (v5 = Module_FindByName(*(_BYTE **)(v10 + 16))) == 0 && (v5 = (int *)strcmp_(v6, *(_DWORD *)(v10 + 16))) != 0 )
    {
      Rules_SetMultifieldErrorValue((int)v6);
      return (_DWORD *)Parser_ReportError(v8, (int)aDefmoduleNam_2);
    }
  }
  else
  {
    v5 = (int *)Module_GetCurrent();
  }
  return (_DWORD *)Rules_BuildConstructNameList(v6, a2, (int)v5);
}
// 4A8F90: variable 'v6' is possibly undefined
// 4A8F9E: variable 'v4' is possibly undefined
// 4A8FEB: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A9000) --------------------------------------------------------
int  Rules_BuildConstructNameList(_DWORD *a1, int a2, int Enum)
{
  signed int v5; // ebx
  int i; // edx
  int v7; // edx
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // ebx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int v14; // esi
  __int64 v15; // rax
  int v16; // ecx
  int v17; // edi
  int v18; // ebp
  char *v19; // edi
  char *Name; // esi
  char v21; // al
  char v22; // al
  char *v23; // esi
  char *v24; // edi
  char v25; // al
  char v26; // al
  char *v27; // esi
  unsigned int v28; // kr08_4
  char *v29; // edi
  char v30; // al
  char v31; // al
  signed int *v32; // eax
  int v33; // edx
  signed int *v34; // eax
  int v35; // edx
  char v37[512]; // [esp+0h] [ebp-224h] BYREF
  _DWORD *v38; // [esp+200h] [ebp-24h]
  int v39; // [esp+204h] [ebp-20h]
  int v40; // [esp+208h] [ebp-1Ch]
  int v41; // [esp+20Ch] [ebp-18h]
  int v42; // [esp+210h] [ebp-14h]

  v42 = a2;
  v5 = 0;
  Module_BeginEnum();
  v39 = 0;
  if ( !Enum )
  {
    Enum = Module_NextEnum(0);
    v39 = v8;
  }
  for ( i = Enum; i; i = Module_NextEnum(v7) )
  {
    Module_SetCurrent(i);
    while ( (*(int (**)(void))(v42 + 28))() )
      ++v5;
    if ( !v39 )
      break;
  }
  a1[1] = 4;
  v40 = Enum;
  a1[4] = v5 - 1;
  a1[3] = 0;
  v9 = Rules_CreateEphemeralMultifield(v5);
  v10 = 1;
  v38 = v9;
  for ( a1[2] = v9; v40; v40 = Module_NextEnum(v40) )
  {
    Module_SetCurrent(v40);
    v41 = 0;
    v13 = v11 + v12 - 6;
    while ( 1 )
    {
      v14 = v42;
      v41 = (*(int (__fastcall **)(int, int))(v42 + 28))(v11, v13);
      if ( !v41 )
        break;
      v15 = ((__int64 (*)(void))*(_DWORD *)(v14 + 16))();
      v17 = v39;
      v18 = v15;
      *(_WORD *)(HIDWORD(v15) + 14) = 2;
      if ( v17 )
      {
        v19 = v37;
        Name = (char *)Module_GetName(v40);
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
        v24 = &v37[strlen(v37)];
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
        v27 = *(char **)(v18 + 16);
        v28 = strlen(v37) + 1;
        v29 = &v37[v28 - 1];
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
        v32 = Str_Intern(v37, ~v28);
        *(_DWORD *)(v33 + 16) = v32;
        v13 = v33 + 6;
        ++v10;
      }
      else
      {
        v34 = Str_Intern(*(char **)(v15 + 16), v16);
        *(_DWORD *)(v35 + 16) = v34;
        v13 = v35 + 6;
        ++v10;
      }
    }
    if ( !v39 )
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
int  Rules_ListConstructsCommand(int a1, int a2, double a3)
{
  int result; // eax
  int *v5; // eax
  int v6; // ecx
  _DWORD v7[2]; // [esp-4h] [ebp-24h] BYREF
  int v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-8h]

  v9 = a2;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    if ( result == 1 )
    {
      Rules_RtnUnknown(1, v7, a3);
      if ( v7[1] != 2 )
        return Parser_ReportError(1, (int)aDefmoduleNam_2);
      v5 = Module_FindByName(*(_BYTE **)(v8 + 16));
      if ( !v5 )
      {
        v5 = (int *)strcmp_(v6, *(_DWORD *)(v8 + 16));
        if ( v5 )
          return Parser_ReportError(1, (int)aDefmoduleNam_2);
      }
    }
    else
    {
      v5 = (int *)Module_GetCurrent();
    }
    return Rules_PrintConstructNamesByModule(a1, (int)g_IO_LogicalName_WDisplay, (int)v5);
  }
  return result;
}
// 4A9258: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A624: using guessed type char *off_51A624;

//----- (004A9280) --------------------------------------------------------
int  Rules_PrintConstructNamesByModule(int a1, int a2, int a3)
{
  int v5; // ebp
  int result; // eax
  int v7; // ecx
  int v8; // ebx
  int v9; // ecx
  int Name; // eax
  int v11; // ecx
  int v12; // ecx
  int Enum; // [esp+0h] [ebp-18h]
  int v14; // [esp+4h] [ebp-14h]

  Enum = a3;
  v5 = 0;
  Module_BeginEnum();
  v14 = 0;
  if ( !a3 )
  {
    Enum = Module_NextEnum(0);
    v14 = 1;
  }
  while ( 1 )
  {
    if ( !Enum )
    {
LABEL_14:
      Rules_PrintTally((int)g_IO_LogicalName_WDisplay, v5, *(_DWORD *)(a1 + 4), *(_DWORD *)a1);
      return Module_EndEnum();
    }
    if ( v14 )
    {
      Name = Module_GetName(Enum);
      Output_Write(a2, Name, v11);
      Output_Write(a2, (int)asc_5084B4, v12);
    }
    Module_SetCurrent(Enum);
    result = (*(int (**)(void))(a1 + 28))();
    if ( result )
      break;
LABEL_13:
    if ( !v14 )
      goto LABEL_14;
    Enum = Module_NextEnum(Enum);
  }
  while ( g_ClipsHaltExecution != 1 )
  {
    v8 = (*(int (**)(void))(a1 + 16))();
    if ( v8 )
    {
      if ( v14 )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5084B8, v7);
      Output_Write(a2, *(_DWORD *)(v8 + 16), v7);
      Output_Write(a2, (int)asc_50849C, v9);
    }
    ++v5;
    result = (*(int (**)(void))(a1 + 28))();
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
int  Rules_SetConstructNextInModule(int result, int a2)
{
  *(_DWORD *)(result + 16) = a2;
  return result;
}

//----- (004A93A0) --------------------------------------------------------
int  Rules_GetConstructOwnerModule(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

//----- (004A93B0) --------------------------------------------------------
int  Rules_GetModuleConstructListHead(int a1)
{
  return *(_DWORD *)(a1 + 4);
}

//----- (004A93C0) --------------------------------------------------------
int  Class_Enum(int a1, int a2)
{
  int result; // eax

  if ( a1 )
    return *(_DWORD *)(a1 + 16);
  result = Module_GetItem(0, a2);
  if ( result )
    return Rules_GetModuleConstructListHead(result);
  return result;
}

//----- (004A93E0) --------------------------------------------------------
int  Rules_GetModuleConstructData(int a1, int a2)
{
  if ( !a1 )
    a1 = Module_GetCurrent();
  return Module_GetItem(a1, a2);
}
// 4A93ED: variable 'a2' is possibly undefined

//----- (004A9400) --------------------------------------------------------
int  Rules_ClearModuleConstructList(int a1, int a2, int a3)
{
  int result; // eax
  int next; // edx
  int cleanup; // ecx

  (void)a3;
  result = *(_DWORD *)(a1 + 4);
  while ( result )
  {
    next = *(_DWORD *)(result + 16);
    cleanup = *(_DWORD *)(a2 + 44);
    ((void (*)(int))(uintptr_t)(unsigned int)cleanup)(result);
    result = next;
  }
  return result;
}

static signed int sub_4A9430_Impl(int (*callback)(int, intptr_t), int construct_index, intptr_t callback_context, int stop_on_watch);

//----- (004A9430) --------------------------------------------------------
signed int  Rules_DoForAllConstructs(void (*a1)(void), int a2)
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))a1, 0, 0, a2);
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

int  Rules_InitConstructModuleRecord(int a1, int a2)
{
  return sub_4A94D0_Impl(a1, a2, a2);
}

//----- (004A9500) --------------------------------------------------------
signed int  Rules_ReplaceConstructPPForm(signed int result, int a2)
{
  signed int v2; // ebx
  const char *v4; // edx

  v2 = result;
  v4 = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(result + 4);
  if ( v4 )
  {
    result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(result + 4), strlen(v4) + 1);
    *(_DWORD *)(v2 + 4) = a2;
  }
  else
  {
    *(_DWORD *)(result + 4) = a2;
  }
  return result;
}

//----- (004A9540) --------------------------------------------------------
signed int  Rules_ListWatchFlagStatus(
        int a1,
        int a2,
        int a3,
        int a4,
        double a5,
        void (*a6)(void))
{
  return Rules_ProcessWatchFlagRequest(a1, (int)aListWatchIte_0, a4, a2, a5, 0, 0, a3, a6);
}

//----- (004A9560) --------------------------------------------------------
signed int  Rules_ApplyWatchFlagCommand(
        int a1,
        int a2,
        int a3,
        int a4,
        double a5,
        void (*a6)(void))
{
  return Rules_ProcessWatchFlagRequest(a1, (int)aWatch_0, a4, (int)g_IO_LogicalNameTable_WError[0], a5, 1, a2, a3, a6);
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004A9590) --------------------------------------------------------
signed int  Rules_ProcessWatchFlagRequest(
        int a1,
        int a2,
        int a3,
        int a4,
        double a5,
        int a6,
        int a7,
        int a8,
        void (*a9)(void))
{
  int v10; // esi
  int v12; // edx
  int Name; // eax
  int v14; // ecx
  int v15; // ecx
  _DWORD v16[7]; // [esp+0h] [ebp-30h] BYREF
  int v17; // [esp+1Ch] [ebp-14h]
  int i; // [esp+20h] [ebp-10h]

  v16[6] = a2;
  v10 = a3;
  v17 = 2;
  if ( a3 )
  {
    while ( 1 )
    {
      if ( !v10 )
        return 1;
      if ( Parser_ParseForm((__int16 *)v10, v16, a3, a5) )
        return 0;
      if ( v16[1] != 2 || !Symbol_LookupInModule((char **)a1, *(_BYTE **)(v16[2] + 16), 1) )
        break;
      if ( a6 )
        a9();
      else
        Rules_PrintWatchFlagState(a4, a1);
      v10 = *(_DWORD *)(v10 + 10);
      ++v17;
    }
    Parser_ReportError(v17, *(_DWORD *)a1);
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
        Output_Write(a4, Name, v14);
        Output_Write(a4, (int)asc_5084B4, v15);
      }
      while ( (*(int (**)(void))(a1 + 28))() )
      {
        if ( a6 )
        {
          a9();
        }
        else
        {
          Output_Write(a4, (int)asc_5084B8, a8);
          Rules_PrintWatchFlagState(a4, a1);
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
signed int  Rules_PrintWatchFlagState(int a1, int a2)
{
  int v3; // eax
  int v4; // ecx
  int (*v5)(void); // ecx
  int v6; // ecx

  v3 = (*(int (**)(void))(a2 + 16))();
  Output_Write(a1, *(_DWORD *)(v3 + 16), v4);
  if ( v5() )
    return Output_Write(a1, (int)aOn_2, v6);
  else
    return Output_Write(a1, (int)aOff_2, v6);
}
// 4A971D: variable 'v4' is possibly undefined
// 4A9724: variable 'v5' is possibly undefined
// 4A9731: variable 'v6' is possibly undefined

//----- (004A9750) --------------------------------------------------------
int  Symbol_LookupInModule(char **a1, _BYTE *a2, int a3)
{
  char *v5; // edi
  int result; // eax
  int v7; // edx
  int v8; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+4h] [ebp-14h]

  v9 = a3;
  v5 = *a1;
  result = Rules_FindImportExportConstruct(*a1, &v8, a2, 1, 0);
  v7 = result;
  if ( result )
  {
    if ( v8 > 1 )
    {
      Rules_ReportAmbiguousReferenceError((int)v5, (int)a2);
      return 0;
    }
  }
  else
  {
    if ( v9 && Rules_FindModuleSeparator(a2) )
      return ((int (*)(void))a1[3])();
    return v7;
  }
  return result;
}
// 4A97AE: variable 'v7' is possibly undefined

//----- (004A97C0) --------------------------------------------------------
_DWORD * Instance_ActiveInitializeInstanceFunction(uintptr_t a1, double a2)
{
  _DWORD *result; // eax
  _DWORD *v4; // ebx
  uintptr_t out; // ecx

  out = a1;
  *(_DWORD *)(out + 4) = 2;
  *(_DWORD *)(out + 8) = g_ClipsFalseSymbol;
  result = Instance_ResolveArgumentToInstance((int)aInitializeIn_0, (int)out, a2);
  v4 = result;
  if ( result )
  {
    result = (_DWORD *)Instance_InitializeSlots(
                         (int)result,
                         *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
                         a2);
    if ( result == (_DWORD *)1 )
    {
      *(_DWORD *)(out + 4) = 8;
      result = (_DWORD *)v4[7];
      *(_DWORD *)(out + 8) = result;
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9810) --------------------------------------------------------
_DWORD * Instance_ActiveMakeInstanceFunction(uintptr_t a1, uintptr_t a2, double a3)
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
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
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
      *(_DWORD *)(a1 + 4) = 8;
      result = Instance_GetQualifiedName((int)result, (int)result);
      *(_DWORD *)(a1 + 8) = result;
    }
    else
    {
      result = (_DWORD *)(uintptr_t)(unsigned int)Instance_DeleteInstance((int)result, a3);
      *(_DWORD *)(a1 + 4) = 2;
      *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
      goto done;
    }
  }
done:
  if ( *(_DWORD *)(a1 + 4) == 2 && *(_DWORD *)(a1 + 8) != g_ClipsFalseSymbol )
  {
    if ( getenv("CLASH95_TRACE_RULES_ASSERT_FACT") )
    {
      fprintf(
        stderr,
        "[rules] make-instance-reset-invalid-symbol value=%08x nil=%08x caller=%p\n",
        *(_DWORD *)(a1 + 8),
        g_ClipsFalseSymbol,
        __builtin_return_address(0));
      fflush(stderr);
    }
    *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  }
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9970) --------------------------------------------------------
signed int * Instance_GetQualifiedName(int a1, int a2)
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

  instance = (uintptr_t)(unsigned int)a1;
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
_DWORD * Instance_BuildInstance(int a1, int a2, int a3, double a4)
{
  signed int *v4; // esi
  signed int v6; // eax
  signed int *v7; // eax
  int v8; // ecx
  _DWORD *v9; // eax
  int v10; // ecx
  _DWORD *v11; // ebp
  int v12; // eax
  int v13; // ebx
  int v14; // ecx
  int v15; // eax
  _DWORD *v16; // ecx
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
  int v32; // [esp+0h] [ebp-20h] BYREF
  int v33; // [esp+4h] [ebp-1Ch]
  int v34; // [esp+8h] [ebp-18h]
  int v35; // [esp+Ch] [ebp-14h]

  v4 = (signed int *)a1;
  v35 = a3;
  if ( g_Rules_JoinOperationInProgress && (*(_BYTE *)(a2 + 20) & 8) != 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 10, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotCreate_0, v18);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternMatch_0, v19);
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( (*(_BYTE *)(a2 + 20) & 4) != 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotCreate_1, v20);
    v21 = Rules_GetConstructNameString(a2);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v21, (int)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, v22);
    Lexer_ErrorRecover(1);
    return 0;
  }
  v6 = Rules_FindModuleSeparator((_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 16));
  if ( v6 )
  {
    v7 = Rules_ExtractModuleName(v6);
    if ( !v7 || v7 != ***(signed int ****)(a2 + 8) )
    {
      Rules_PrintErrorID((int)aInsmngr, 11, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInvalidModuleS, v23);
      Lexer_ErrorRecover(1);
      return 0;
    }
    v4 = Rules_ExtractConstructName(v8, (char *)v4[4], v8);
  }
  v9 = Instance_FindHashEntryForBuild(a2, (int)v4, &v32, &v33);
  v11 = v9;
  if ( !v9 )
    goto LABEL_14;
  if ( (v9[6] & 1) == 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheInstance, v24);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v4[4], v25);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aHasASlotValueW, v26);
    Lexer_ErrorRecover(1);
    return 0;
  }
  ++v9[10];
  ++v4[1];
  if ( (v9[6] & 2) == 0 )
  {
    if ( g_Instance_UseMessageDispatchForInit )
    {
      v34 = g_ClipsDeleteMessageSymbol;
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, (int)v9, 0, 0, a4);
    }
    else
    {
      Instance_DeleteInstance((int)v9, a4);
    }
  }
  --v11[10];
  Rules_DecrementSymbolCount((int)v4, v10);
  if ( (v11[6] & 2) == 0 )
  {
    Rules_PrintErrorID((int)aInsmngr, 5, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDele_0, v27);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v4[4], v28);
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
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 28) = v4;
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 44) = a2;
      Instance_AllocateSlotValueTable(v35);
      v12 = v33;
      *(_DWORD *)(g_ClipsInstanceUnderConstruction + 36) = v33;
      if ( v32 )
      {
        *(_DWORD *)(g_ClipsInstanceUnderConstruction + 60) = *(_DWORD *)(v32 + 60);
        v30 = *(_DWORD *)(v32 + 60);
        if ( v30 )
          *(_DWORD *)(v30 + 56) = g_ClipsInstanceUnderConstruction;
        v31 = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(v32 + 60) = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(v31 + 56) = v32;
      }
      else
      {
        *(_DWORD *)(g_ClipsInstanceUnderConstruction + 60) = *(_DWORD *)(g_Instance_HashTableBase + 4 * v12);
        v13 = *(_DWORD *)(g_Instance_HashTableBase + 4 * v33);
        if ( v13 )
          *(_DWORD *)(v13 + 56) = g_ClipsInstanceUnderConstruction;
        *(_DWORD *)(4 * v33 + g_Instance_HashTableBase) = g_ClipsInstanceUnderConstruction;
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
      v16 = (_DWORD *)g_ClipsInstanceUnderConstruction;
      g_ClipsInstanceUnderConstruction = 0;
      if ( (*(_BYTE *)(v16[11] + 20) & 8) != 0 )
        Rules_ObjectMatchAction((unsigned __int16 *)1, v16, -1, a4);
      return v16;
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
char  Instance_InitSlotsCommand(uintptr_t a1, uintptr_t a2, double a3)
{
  signed int v2; // eax
  int v3; // eax

  (void)a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  v2 = MessageHandler_CheckCurrentMessage((int)aInitSlots, 1);
  if ( v2 )
  {
    v3 = MessageHandler_GetNthArgument(0);
    LOBYTE(v2) = Instance_InitSlots(*(_DWORD *)(v3 + 8), (__int16)a1, a3);
    if ( !g_ClipsEvaluationError )
    {
      *(_DWORD *)(a1 + 4) = 7;
      v2 = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
      *(_DWORD *)(a1 + 8) = v2;
    }
  }
  return v2;
}
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9E90) --------------------------------------------------------
signed int  Instance_DeleteInstance(int a1, double a2)
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

  instance = (uintptr_t)(unsigned int)a1;
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
int  Instance_InitializeInstanceFunction(uintptr_t a1, uintptr_t a2, double a3)
{
  int previous_watch_state; // edx

  (void)a2;
  previous_watch_state = Rules_SetObjectPatternMatchDelay(1, a3);
  Instance_ActiveInitializeInstanceFunction(a1, a3);
  return Rules_SetObjectPatternMatchDelay(previous_watch_state, a3);
}

//----- (004AA170) --------------------------------------------------------
int  Instance_MakeInstanceFunction(uintptr_t a1, uintptr_t a2, double a3)
{
  int previous_watch_state; // edx

  (void)a2;
  previous_watch_state = Rules_SetObjectPatternMatchDelay(1, a3);
  Instance_ActiveMakeInstanceFunction(a1, a1, a3);
  return Rules_SetObjectPatternMatchDelay(previous_watch_state, a3);
}

//----- (004AA1A0) --------------------------------------------------------
signed int Instance_AllocateInstanceRecord()
{
  _DWORD *v0; // edx
  signed int result; // eax
  char v2; // dl
  int v3; // edx

  Rules_EnsureObjectPatternVTable();
  v0 = *(_DWORD **)(g_ClipsMemoryTable + 320);
  if ( v0 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 320);
    *(_DWORD *)(g_ClipsMemoryTable + 320) = *v0;
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
  v3 = g_ClipsCurrentEvaluationDepth;
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
  *(_DWORD *)(result + 32) = v3;
  return result;
}
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AA270) --------------------------------------------------------
_DWORD * Instance_FindHashEntryForBuild(int a1, int a2, _DWORD *a3, _DWORD *a4)
{
  unsigned int bucket; // eax
  _DWORD *result; // eax

  bucket = Instance_HashNameToBucket(a2);
  *a4 = bucket;
  result = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * bucket);
  for ( *a3 = 0; result; result = (_DWORD *)(uintptr_t)(unsigned int)result[15] )
  {
    if ( a2 == (int)result[7] )
      break;
    *a3 = (int)(uintptr_t)result;
  }
  while ( result && a2 == (int)result[7] )
  {
    if ( *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 8) ==
         *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)result[11] + 8) )
      return result;
    *a3 = (int)(uintptr_t)result;
    result = (_DWORD *)(uintptr_t)(unsigned int)result[15];
  }
  return 0;
}
// 51A278: using guessed type int dword_51A278;

//----- (004AA2E0) --------------------------------------------------------
int  Instance_SetActiveFlag(int result, int a2)
{
  int v2; // ecx

  v2 = result;
  if ( a2 == 1 )
  {
    if ( (*(_BYTE *)(result + 24) & 1) == 0 )
    {
      if ( (*(_BYTE *)(*(_DWORD *)(result + 44) + 20) & 0x10) != 0 )
        Instance_PrintWatchTrace((int)asc_508718, result);
      *(_BYTE *)(v2 + 24) |= 1u;
      *(_DWORD *)(v2 + 32) = g_ClipsCurrentEvaluationDepth;
      ++*(_DWORD *)(*(_DWORD *)(v2 + 28) + 4);
      result = Class_AddBusyReference(*(_DWORD *)(v2 + 44));
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
int  Instance_AllocateSlotValueTable(int a1)
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
  create_mode = a1 & 1;
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
BOOL  Instance_InitializeSlots(int a1, int a2, double a3)
{
  int v4; // ecx
  char v5; // bl
  __int16 v6; // cx
  int v7; // edi
  char v8; // cl
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17[11]; // [esp+0h] [ebp-2Ch] BYREF

  if ( (*(_BYTE *)(a1 + 24) & 1) != 0 )
  {
    v4 = *(_DWORD *)(a1 + 40) + 1;
    v5 = *(_BYTE *)(a1 + 24) & 0xFE;
    *(_DWORD *)(a1 + 40) = v4;
    *(_BYTE *)(a1 + 24) = v5;
    if ( Instance_ApplySlotOverrideList((_DWORD *)a1, a2, v4, a3) )
    {
      *(_BYTE *)(a1 + 24) |= 4u;
      v7 = g_Instance_SlotInitInProgress;
      g_Instance_SlotInitInProgress = 1;
      if ( g_Instance_UseMessageDispatchForInit )
        MessageHandler_SendToInstanceAddress(g_MessageHandler_InitSymbol, a1, 0, v17, a3);
      else
        Instance_InitSlots(a1, v6, a3);
      g_Instance_SlotInitInProgress = v7;
      v8 = *(_BYTE *)(a1 + 24) | 1;
      --*(_DWORD *)(a1 + 40);
      *(_BYTE *)(a1 + 24) = v8;
      if ( g_ClipsEvaluationError )
      {
        Rules_PrintErrorID((int)aInsmngr, 8, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAnErrorOccurre, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(a1 + 28) + 16), v15);
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
      v13 = *(_DWORD *)(a1 + 40) - 1;
      *(_BYTE *)(a1 + 24) |= 1u;
      *(_DWORD *)(a1 + 40) = v13;
      return 0;
    }
  }
  else
  {
    Rules_PrintErrorID((int)aInsmngr, 7, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstance_4, v10);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(a1 + 28) + 16), v11);
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
signed int  Instance_ApplySlotOverrideList(_DWORD *a1, int a2, int a3, double a4)
{
  int slot_override; // edi
  int *slot_value; // esi
  signed int result; // eax
  int parsed_ptr; // ecx
  int saved_context; // [esp+18h] [ebp-1Ch]
  int *saved_slot_value; // [esp+1Ch] [ebp-18h]
  _DWORD *parsed; // [esp+0h] [ebp-34h] BYREF

  slot_override = a2;
  g_ClipsEvaluationError = 0;
  saved_context = g_Instance_SlotInitInProgress;
  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  if ( !a2 )
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
    slot_value = (int *)Instance_GetSlotValueBySymbol((int)(uintptr_t)a1, slot_name_symbol);
    saved_slot_value = slot_value;
    if ( !slot_value )
      break;
    g_Instance_SlotInitInProgress = 1;
    pair_node = *(_DWORD *)((uintptr_t)(unsigned int)slot_override + 10);
    value_expression = *(_DWORD *)((uintptr_t)(unsigned int)pair_node + 6);
    if ( g_Instance_UseMessageDispatchForInit )
    {
      MessageHandler_SendToInstanceAddress(*(_DWORD *)((uintptr_t)(unsigned int)*slot_value + 12), (int)(uintptr_t)a1, value_expression, 0, a4);
    }
    else if ( Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)(uintptr_t)(unsigned int)*slot_value << 30 >> 31, value_expression, parsed, a4) )
    {
      Instance_PutSlotValue(a1, slot_value, parsed, a4);
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
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)a1[7] + 16), 0);
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
char  Instance_InitSlots(int a1, __int16 a2, double a3)
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
  if ( (*(_BYTE *)((uintptr_t)(unsigned int)a1 + 24) & 4) != 0 )
  {
    slot_value_offset = 0;
    for ( i = 0; ; ++i )
    {
      int class_record = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 44);
      if ( i >= *(_DWORD *)((uintptr_t)(unsigned int)class_record + 72) )
        break;
      slot_value_table = *(_DWORD *)((uintptr_t)(unsigned int)a1 + 72);
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
                       (_DWORD *)(uintptr_t)(unsigned int)a1,
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
              *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 28) + 16),
              0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__17, 0);
            result = Lexer_ErrorRecover(1);
          }
        }
        else
        {
          result = Instance_StoreSlotValueAndMatch(
                     (_DWORD *)(uintptr_t)(unsigned int)a1,
                     (int *)(uintptr_t)(unsigned int)slot_value,
                     a2,
                     (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 16),
                     a3);
        }
      }
      *(_BYTE *)((uintptr_t)(unsigned int)slot_value + 4) &= ~1u;
      if ( (*(_BYTE *)((uintptr_t)(unsigned int)a1 + 24) & 2) != 0 )
      {
        Output_Write(
          (int)g_IO_LogicalNameTable_WError[0],
          *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 28) + 16),
          0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstanceDelete, 0);
        result = Lexer_ErrorRecover(1);
      }
      if ( g_ClipsEvaluationError )
        goto done;
      slot_value_offset += 4;
    }
    *(_BYTE *)((uintptr_t)(unsigned int)a1 + 24) &= ~4u;
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
signed int  Instance_PrintWatchTrace(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], a1, a2);
  Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aInstance, v2);
  return Instance_PrintNameOfClass((int)g_IO_LogicalNameTable_WTrace[0], v3, 1);
}
// 4AA9A2: variable 'v2' is possibly undefined
// 4AA9AE: variable 'v3' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];

//----- (004AA9C0) --------------------------------------------------------
int __fastcall Rules_ParseObjectInstanceFunctionCall(int a1, int a2)
{
  int **Symbol; // eax
  int v4; // ecx
  int v5; // esi
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
  _DWORD v49[5]; // [esp+0h] [ebp-14h] BYREF

  v49[3] = a1;
  Symbol = Rules_MakeSymbol(aMakeInstance_0);
  if ( Symbol == *(int ***)(v4 + 2) || (v11 = Rules_MakeSymbol(aActiveMakeIn_0), v11 == *(int ***)(v12 + 2)) )
  {
    v5 = 0;
  }
  else
  {
    v13 = Rules_MakeSymbol(aInitializeIn_1);
    if ( v13 == *(int ***)(v14 + 2) || (v15 = Rules_MakeSymbol(aActiveInitia_0), v15 == *(int ***)(v16 + 2)) )
    {
      v5 = 1;
    }
    else
    {
      v17 = Rules_MakeSymbol(aModifyInstan_0);
      if ( v17 == *(int ***)(v18 + 2)
        || (v19 = Rules_MakeSymbol(aActiveModify_0), v19 == *(int ***)(v20 + 2))
        || (v21 = Rules_MakeSymbol(aMessageModif_0), v21 == *(int ***)(v22 + 2))
        || (v23 = Rules_MakeSymbol(aActiveMessag_0), v23 == *(int ***)(v24 + 2)) )
      {
        v5 = 2;
      }
      else
      {
        v5 = 3;
      }
    }
  }
  Rules_IncrementIndentDepth(3);
  v49[0] = 0;
  if ( *v6 == 103 )
    *v6 = 10;
  else
    IO_OutWriteToken(asc_508954);
  v7 = Parser_ParseArgument(a2, v49, (int)v6);
  *(_DWORD *)(v8 + 6) = v7;
  if ( v49[0] )
    goto LABEL_8;
  if ( !v7 )
    goto LABEL_7;
  IO_OutWriteToken(asc_508954);
  if ( !v5 )
  {
    if ( **(_WORD **)(v26 + 6) == 2 && !strcmp_(v26, aOf_0) )
    {
      v32 = Parser_ParseArgument(a2, v49, v31);
      *(_DWORD *)(*(_DWORD *)(v28 + 6) + 10) = v32;
      if ( v49[0] == 1 )
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
      Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 2 || strcmp_(v27, *(_DWORD *)(g_ClipsParserTokenValue + 16)) )
        goto LABEL_7;
      IO_OutWriteToken(asc_508954);
    }
    v29 = Parser_ParseArgument(a2, v49, v28);
    *(_DWORD *)(*(_DWORD *)(v30 + 6) + 10) = v29;
    if ( v49[0] )
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
  Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
  if ( v5 == 3 )
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
    v46 = Parser_ParseArgument(a2, v44, v45);
    v35 = *(_DWORD *)(v36 + 6);
    *(_DWORD *)(v35 + 10) = v46;
    if ( v49[0] )
      goto LABEL_8;
    if ( !*(_DWORD *)(*(_DWORD *)(v36 + 6) + 10) )
      goto LABEL_7;
LABEL_34:
    AST_Append(v36, v35);
    Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
LABEL_35:
    v38 = Rules_ParseObjectFunctionArgList(a2, v49, v37);
    v40 = *(_DWORD *)(*(_DWORD *)(v39 + 6) + 10);
    goto LABEL_36;
  }
  v38 = Rules_ParseObjectFunctionArgList(a2, v49, v41);
  v40 = *(_DWORD *)(v47 + 6);
LABEL_36:
  *(_DWORD *)(v40 + 10) = v38;
  if ( v49[0] )
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
int  Rules_ParseObjectFunctionArgList(int a1, _DWORD *a2, int a3)
{
  int v5; // edi
  int v6; // ebp
  signed int v7; // eax
  signed int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  signed int v13; // [esp+0h] [ebp-18h]

  v5 = 0;
  v6 = 0;
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      *a2 = 0;
      v7 = Parser_ParseArgument(a1, a2, a3);
      v13 = v7;
      if ( *a2 == 1 )
      {
        AST_Free(v5);
        return 0;
      }
      if ( !v7 )
      {
        Parser_ReportSyntaxError();
        *a2 = 1;
        AST_Free(v5);
        Lexer_ErrorRecover(1);
        return 0;
      }
      v8 = AST_NewNode(2, g_ClipsTrueSymbol);
      *(_DWORD *)(v9 + 10) = v8;
      if ( !Parser_CollectFunctionArguments(v8, a1, v9) )
        break;
      if ( v5 )
        *(_DWORD *)(v6 + 10) = v10;
      else
        v5 = v10;
      v6 = *(_DWORD *)(v13 + 10);
      AST_Append(v10, (int)&g_ParserCurrentTokenType);
      Parser_NextToken(a1, v11);
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_8;
    }
    *a2 = 1;
    AST_Free(v5);
    return 0;
  }
  else
  {
LABEL_8:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)g_ClipsScanTokenPrintForm);
    return v5;
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
int  Rules_ParseMakeInstanceNode(int a1, int a2)
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
  Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-token1=%d\n", g_ParserCurrentTokenType);
  override_head = 0;
  if ( g_ParserCurrentTokenType != 8 && g_ParserCurrentTokenType != 2 )
    goto MAKE_INSTANCE_ERROR;
  *(_DWORD *)(a1 + 6) = AST_NewNode(8, g_ClipsParserTokenValue);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-head-node\n");
  Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
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
  Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(
      stderr,
      "[menu-probe] parse-make-instance-token3=%d symbol=%s\n",
      g_ParserCurrentTokenType,
      g_ClipsParserTokenValue ? (const char *)*(_DWORD *)(g_ClipsParserTokenValue + 16) : "<null>");
  if ( g_ParserCurrentTokenType != token_type )
    goto MAKE_INSTANCE_ERROR;
  *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = AST_NewNode(g_ParserCurrentTokenType, g_ClipsParserTokenValue);
  slot_override_parent = *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-before-class-lookup\n");
  if ( !Rules_ResolveClassNameNode(slot_override_parent) )
    goto MAKE_INSTANCE_ERROR;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-after-class-lookup\n");
  Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] parse-make-instance-token4=%d\n", g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType != 100 )
    goto CHECK_END_TOKEN;
  while ( 1 )
  {
    Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
    if ( g_ParserCurrentTokenType != 2 )
      goto SLOT_OVERRIDE_ERROR;
    *(_DWORD *)(slot_override_parent + 10) = AST_NewNode(2, g_ClipsParserTokenValue);
    *(_DWORD *)(*(_DWORD *)(slot_override_parent + 10) + 10) = AST_NewNode(2, g_ClipsTrueSymbol);
    slot_override_parent = *(_DWORD *)(*(_DWORD *)(slot_override_parent + 10) + 10);
    Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
    override_tail = 0;
    while ( g_ParserCurrentTokenType != 101 )
    {
      if ( g_ParserCurrentTokenType == 100 )
      {
        Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType != 2 )
          goto SLOT_OVERRIDE_ERROR;
        if ( strcmp_(*(_DWORD *)(g_ClipsParserTokenValue + 16), (int)aCreate_0) )
          goto SLOT_OVERRIDE_ERROR;
        Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
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
      Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
    }
    *(_DWORD *)(slot_override_parent + 6) = override_head;
    Parser_NextToken(a2, (int)&g_ParserCurrentTokenType);
    override_head = 0;
    if ( g_ParserCurrentTokenType != 100 )
      break;
  }
CHECK_END_TOKEN:
  if ( g_ParserCurrentTokenType == 101 )
    return a1;
SLOT_OVERRIDE_ERROR:
  Parser_ReportSyntaxError();
  Lexer_ErrorRecover(1);
  AST_Free(a1);
  AST_Free(override_head);
  return 0;
MAKE_INSTANCE_ERROR:
  Parser_ReportSyntaxError();
  Lexer_ErrorRecover(1);
  AST_Free(a1);
  return 0;
}
// 4AB03F: simplified comparisons for '$dword_54E8FC.4': ==0 || ==1 became <2u
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DD64: using guessed type int dword_54DD64;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004AB0B0) --------------------------------------------------------
signed int  Rules_ResolveClassNameNode(int a1)
{
  int class_name; // edx
  int *class_record; // ebx
  int trace_load_save; // eax

  if ( *(_WORD *)a1 != 2 )
    return 1;
  class_name = *(_DWORD *)(*(_DWORD *)(a1 + 2) + 16);
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
    *(_WORD *)a1 = 57;
    *(_DWORD *)(a1 + 2) = class_record;
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
_DWORD * Instance_ActiveModifyInstanceFunction(int *a1, double a2)
{
  int v3; // ecx
  _DWORD *v4; // edi
  _DWORD *result; // eax
  int v6; // ebp
  int *v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // [esp+10h] [ebp-1Ch] BYREF
  _DWORD v11[6]; // [esp+14h] [ebp-18h] BYREF

  v4 = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), &v10, v11, a2);
  if ( v11[0] )
  {
    a1[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    a1[2] = g_ClipsFalseSymbol;
  }
  else
  {
    if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) )
    {
      v6 = g_InstanceDirectMessageGuardActive;
      g_InstanceDirectMessageGuardActive = 1;
      v7 = Rules_FindSymbolEntry(aDirectModify_0);
      MessageHandler_SendToInstanceAddress((int)v7, v8, v9, a1, a2);
      g_InstanceDirectMessageGuardActive = v6;
    }
    else
    {
      a1[1] = 2;
      a1[2] = g_ClipsFalseSymbol;
    }
    return Instance_FreeSlotOverrideArgs(v4, v10);
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
_DWORD * Instance_ActiveMessageModifyInstanceFunction(int *a1, double a2)
{
  int v3; // ecx
  _DWORD *v4; // edi
  _DWORD *result; // eax
  int v6; // ebp
  int *v7; // eax
  int v8; // edx
  int v9; // ecx
  int v10; // [esp+10h] [ebp-1Ch] BYREF
  _DWORD v11[6]; // [esp+14h] [ebp-18h] BYREF

  v4 = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), &v10, v11, a2);
  if ( v11[0] )
  {
    a1[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    a1[2] = g_ClipsFalseSymbol;
  }
  else
  {
    if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) )
    {
      v6 = g_InstanceDirectMessageGuardActive;
      g_InstanceDirectMessageGuardActive = 1;
      v7 = Rules_FindSymbolEntry(aMessageModif_1);
      MessageHandler_SendToInstanceAddress((int)v7, v8, v9, a1, a2);
      g_InstanceDirectMessageGuardActive = v6;
    }
    else
    {
      a1[1] = 2;
      a1[2] = g_ClipsFalseSymbol;
    }
    return Instance_FreeSlotOverrideArgs(v4, v10);
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
_DWORD * Instance_ActiveDuplicateInstanceFunction(int *a1, double a2)
{
  int v3; // ecx
  _DWORD *v4; // edi
  _DWORD *result; // eax
  int *v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // [esp+1Ch] [ebp-3Ch] BYREF
  int v10; // [esp+34h] [ebp-24h]
  int v11; // [esp+38h] [ebp-20h] BYREF
  _DWORD v12[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  v4 = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), &v11, v12, a2);
  if ( v12[0] )
  {
    a1[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    a1[2] = g_ClipsFalseSymbol;
  }
  else if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) && Lexer_ParseValueList(2, &v9, 8, a2) )
  {
    v10 = g_InstanceDirectMessageGuardActive;
    g_InstanceDirectMessageGuardActive = 1;
    v6 = Rules_FindSymbolEntry(aDirectDuplic_0);
    MessageHandler_SendToInstanceAddress((int)v6, v7, v8, a1, a2);
    g_InstanceDirectMessageGuardActive = v10;
    return Instance_FreeSlotOverrideArgs(v4, v11);
  }
  else
  {
    a1[1] = 2;
    a1[2] = g_ClipsFalseSymbol;
    return Instance_FreeSlotOverrideArgs(v4, v11);
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
_DWORD * Instance_ActiveMessageDuplicateInstanceFunction(int *a1, double a2)
{
  int v3; // ecx
  _DWORD *v4; // edi
  _DWORD *result; // eax
  int *v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // [esp+1Ch] [ebp-3Ch] BYREF
  int v10; // [esp+34h] [ebp-24h]
  int v11; // [esp+38h] [ebp-20h] BYREF
  _DWORD v12[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  v4 = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), &v11, v12, a2);
  if ( v12[0] )
  {
    a1[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    a1[2] = g_ClipsFalseSymbol;
  }
  else if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) && Lexer_ParseValueList(2, &v9, 8, a2) )
  {
    v10 = g_InstanceDirectMessageGuardActive;
    g_InstanceDirectMessageGuardActive = 1;
    v6 = Rules_FindSymbolEntry(aMessageDupli_1);
    MessageHandler_SendToInstanceAddress((int)v6, v7, v8, a1, a2);
    g_InstanceDirectMessageGuardActive = v10;
    return Instance_FreeSlotOverrideArgs(v4, v11);
  }
  else
  {
    a1[1] = 2;
    a1[2] = g_ClipsFalseSymbol;
    return Instance_FreeSlotOverrideArgs(v4, v11);
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
_DWORD * Instance_DirectDuplicateFunction(int *a1, double a2)
{
  return Rules_DuplicateInstanceCore(a1, 0, a2);
}

//----- (004AB810) --------------------------------------------------------
_DWORD * Instance_MessageDuplicateFunction(int *a1, double a2)
{
  return Rules_DuplicateInstanceCore(a1, 1, a2);
}

//----- (004AB820) --------------------------------------------------------
_DWORD * Instance_DirectModifyFunction(int a1, double a2)
{
  return Rules_ModifyInstanceCore(a1, 0, a2);
}

//----- (004AB830) --------------------------------------------------------
_DWORD * Instance_MessageModifyFunction(int a1, double a2)
{
  return Rules_ModifyInstanceCore(a1, 1, a2);
}

//----- (004AB840) --------------------------------------------------------
int  Instance_ParseSlotOverrideArgs(int a1, _DWORD *a2, _DWORD *a3, double a4)
{
  int v4; // esi
  int result; // eax
  int v6; // edi
  _DWORD *v7; // eax
  _DWORD *v8; // ecx
  _DWORD *v9; // ecx
  _DWORD *v10; // ecx
  _DWORD *v11; // eax
  _DWORD *v13; // [esp+8h] [ebp-18h]
  int v14; // [esp+Ch] [ebp-14h]

  v4 = a1;
  *a3 = 0;
  result = AST_CountListNodes(a1) / 2;
  *a2 = result;
  if ( result )
  {
    v6 = 0;
    v7 = Mem_SmallBlockAlloc(24 * result);
    v13 = v7;
    if ( v4 )
    {
      v8 = v7;
      while ( !Parser_ParseForm((__int16 *)v4, v8, (int)v8, a4) )
      {
        if ( v9[1] != 2 )
        {
          Parser_ReportError(v6 + 1, (int)aSlotName);
          Lexer_ErrorRecover(1);
          break;
        }
        v14 = v9[2];
        if ( !Parser_ParseSlotDefaultOrRestriction(0, *(_DWORD *)(*(_DWORD *)(v4 + 10) + 6), v9, a4) )
          break;
        *v10 = v14;
        v4 = *(_DWORD *)(*(_DWORD *)(v4 + 10) + 10);
        if ( v4 )
          v11 = &v13[6 * v6 + 6];
        else
          v11 = 0;
        v8 = v10 + 6;
        ++v6;
        *(v8 - 1) = v11;
        if ( !v4 )
          return (int)v13;
      }
      Mem_SmallBlockFree(v13, 24 * *a2);
      *a3 = 1;
      return 0;
    }
    else
    {
      return (int)v13;
    }
  }
  return result;
}
// 4AB8AA: variable 'v9' is possibly undefined
// 4AB928: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004AB960) --------------------------------------------------------
_DWORD * Instance_FreeSlotOverrideArgs(_DWORD *result, int a2)
{
  if ( result )
    return (_DWORD *)Mem_SmallBlockFree(result, 24 * a2);
  return result;
}

//----- (004AB990) --------------------------------------------------------
_DWORD * Rules_ModifyInstanceCore(int a1, int a2, double a3)
{
  int v4; // edi
  int v5; // esi
  int v6; // eax
  int v7; // ecx
  int *v8; // edx
  _DWORD *result; // eax
  bool v10; // zf
  int v11; // ecx
  int *v12; // eax
  int v13; // [esp+0h] [ebp-40h] BYREF
  int v14; // [esp+4h] [ebp-3Ch]
  _DWORD *v15; // [esp+8h] [ebp-38h]
  int v16; // [esp+Ch] [ebp-34h]
  int v17; // [esp+10h] [ebp-30h]
  __int16 v18; // [esp+18h] [ebp-28h] BYREF
  int v19; // [esp+1Ah] [ebp-26h]
  int v20; // [esp+1Eh] [ebp-22h]
  int v21; // [esp+22h] [ebp-1Eh]
  int v22; // [esp+28h] [ebp-18h]

  v22 = a1;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(v22 + 8) = g_ClipsFalseSymbol;
  if ( !g_InstanceDirectMessageGuardActive )
  {
    Rules_PrintErrorID((int)aInsmoddp, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDirectMessageM, v11);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  g_InstanceDirectMessageGuardActive = 0;
  v4 = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
  if ( (*(_BYTE *)(v4 + 24) & 2) != 0 )
  {
    Instance_ReportInvalidInstanceAddressError();
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  v5 = *(_DWORD *)(MessageHandler_GetNthArgument(1) + 8);
  *(_DWORD *)(v22 + 4) = 2;
  *(_DWORD *)(v22 + 8) = g_ClipsFalseSymbol;
  if ( v5 )
  {
    while ( 1 )
    {
      v6 = Instance_GetSlotValueBySymbol(v4, *(_DWORD *)v5);
      v8 = (int *)v6;
      if ( !v6 )
      {
        Instance_ReportNoSuchSlotError(v7, (int)aModifyInstance);
        return (_DWORD *)Lexer_ErrorRecover(1);
      }
      if ( !a2 )
        break;
      v18 = *(_WORD *)(v5 + 4);
      if ( v18 == 4 )
        v19 = v5;
      else
        v19 = *(_DWORD *)(v5 + 8);
      v20 = 0;
      v21 = 0;
      result = (_DWORD *)MessageHandler_SendToInstanceAddress(*(_DWORD *)(*(_DWORD *)v6 + 12), v4, (int)&v18, &v13, a3);
      if ( g_ClipsEvaluationError )
        return result;
      if ( v14 == 2 )
      {
        result = v15;
        v10 = v15 == (_DWORD *)g_ClipsFalseSymbol;
        goto LABEL_11;
      }
LABEL_12:
      v5 = *(_DWORD *)(v5 + 20);
      if ( !v5 )
        goto LABEL_13;
    }
    if ( (**(_BYTE **)v6 & 2) == 0 || *(_DWORD *)(v5 + 4) == 4 )
    {
      v12 = (int *)v5;
    }
    else
    {
      v14 = 4;
      v15 = Rules_CreateEphemeralMultifield(1);
      v16 = 0;
      v17 = 0;
      *((_WORD *)v15 + 7) = *(_WORD *)(v5 + 4);
      v15[4] = *(_DWORD *)(v5 + 8);
      v12 = &v13;
    }
    result = (_DWORD *)Instance_PutSlotValue((_DWORD *)v4, v8, v12, a3);
    v10 = result == 0;
LABEL_11:
    if ( v10 )
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
_DWORD * Rules_DuplicateInstanceCore(int *a1, int a2, double a3)
{
  int v3; // ebp
  int v4; // ecx
  int v5; // edi
  _DWORD *result; // eax
  int v7; // esi
  int *v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  bool v12; // zf
  int v13; // ecx
  int v14; // edi
  int *v15; // eax
  _DWORD *v16; // eax
  unsigned int v17; // edx
  int v18; // eax
  int v19; // ecx
  char v20; // bh
  int v21; // edx
  int v22; // [esp+0h] [ebp-54h] BYREF
  int v23; // [esp+4h] [ebp-50h]
  _DWORD *v24; // [esp+8h] [ebp-4Ch]
  int v25; // [esp+Ch] [ebp-48h]
  int v26; // [esp+10h] [ebp-44h]
  __int16 v27; // [esp+18h] [ebp-3Ch] BYREF
  int v28; // [esp+1Ah] [ebp-3Ah]
  int v29; // [esp+1Eh] [ebp-36h]
  int v30; // [esp+22h] [ebp-32h]
  int v31; // [esp+28h] [ebp-2Ch]
  int v32; // [esp+2Ch] [ebp-28h]
  int v33; // [esp+30h] [ebp-24h]
  int *v34; // [esp+34h] [ebp-20h]
  unsigned int v35; // [esp+38h] [ebp-1Ch]
  int *v36; // [esp+3Ch] [ebp-18h]

  v34 = a1;
  v31 = a2;
  a1[1] = 2;
  v34[2] = g_ClipsFalseSymbol;
  if ( !g_InstanceDirectMessageGuardActive )
  {
    Rules_PrintErrorID((int)aInsmoddp, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDirectMessageD, v10);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  g_InstanceDirectMessageGuardActive = 0;
  v3 = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
  MessageHandler_GetNthArgument(1);
  v5 = *(_DWORD *)(MessageHandler_GetNthArgument(2) + 8);
  if ( (*(_BYTE *)(v3 + 24) & 2) != 0 )
  {
    Instance_ReportInvalidInstanceAddressError();
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  if ( v4 == *(_DWORD *)(v3 + 28) )
  {
    Rules_PrintErrorID((int)aInsmoddp, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstanceCopyMu, v11);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  v32 = g_Instance_UseMessageDispatchForInit;
  g_Instance_UseMessageDispatchForInit = v31;
  result = Instance_BuildInstance(v4, *(_DWORD *)(v3 + 44), 1, a3);
  v7 = (int)result;
  g_Instance_UseMessageDispatchForInit = v32;
  if ( result )
  {
    ++result[10];
    if ( v5 )
    {
      while ( 1 )
      {
        v8 = (int *)Instance_GetSlotValueBySymbol(v7, *(_DWORD *)v5);
        v36 = v8;
        if ( !v8 )
        {
          Instance_ReportNoSuchSlotError(v9, (int)aDuplicateInsta);
LABEL_8:
          --*(_DWORD *)(v7 + 40);
          Instance_DeleteInstance(v7, a3);
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        if ( !v31 )
          break;
        v27 = *(_WORD *)(v5 + 4);
        if ( v27 == 4 )
          v28 = v5;
        else
          v28 = *(_DWORD *)(v5 + 8);
        v29 = 0;
        v30 = 0;
        MessageHandler_SendToInstanceAddress(*(_DWORD *)(*v36 + 12), v7, (int)&v27, &v22, a3);
        if ( g_ClipsEvaluationError )
          goto LABEL_8;
        if ( v23 == 2 )
        {
          v12 = v24 == (_DWORD *)g_ClipsFalseSymbol;
          goto LABEL_19;
        }
LABEL_20:
        *((_BYTE *)v36 + 4) |= 2u;
        v5 = *(_DWORD *)(v5 + 20);
        if ( !v5 )
          goto LABEL_21;
      }
      if ( (*(_BYTE *)*v8 & 2) == 0 || *(_DWORD *)(v5 + 4) == 4 )
      {
        v15 = (int *)v5;
      }
      else
      {
        v23 = 4;
        v24 = Rules_CreateEphemeralMultifield(1);
        v25 = 0;
        v26 = 0;
        *((_WORD *)v24 + 7) = *(_WORD *)(v5 + 4);
        v24[4] = *(_DWORD *)(v5 + 8);
        v15 = &v22;
      }
      v12 = Instance_PutSlotValue((_DWORD *)v7, v36, v15, a3) == 0;
LABEL_19:
      if ( v12 )
        goto LABEL_8;
      goto LABEL_20;
    }
LABEL_21:
    v13 = 0;
    v14 = 0;
    v35 = 0;
    while ( 1 )
    {
      if ( v35 >= *(_DWORD *)(*(_DWORD *)(v7 + 44) + 68) )
      {
        if ( v31 )
        {
          v17 = 0;
          v18 = 0;
          while ( v17 < *(_DWORD *)(*(_DWORD *)(v7 + 44) + 72) )
          {
            v19 = *(_DWORD *)(*(_DWORD *)(v7 + 72) + v18);
            v18 += 4;
            ++v17;
            *(_BYTE *)(v19 + 4) |= 2u;
          }
          *(_BYTE *)(v7 + 24) |= 4u;
          v32 = g_Instance_SlotInitInProgress;
          g_Instance_SlotInitInProgress = 1;
          MessageHandler_SendToInstanceAddress(g_MessageHandler_InitSymbol, v7, 0, v34, a3);
          g_Instance_SlotInitInProgress = v32;
        }
        v20 = *(_BYTE *)(v7 + 24);
        --*(_DWORD *)(v7 + 40);
        if ( (v20 & 2) != 0 )
        {
          v34[1] = 2;
          v34[2] = g_ClipsFalseSymbol;
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        else
        {
          v34[1] = 8;
          result = Instance_GetQualifiedName(v7, v13);
          *(_DWORD *)(v21 + 8) = result;
        }
        return result;
      }
      if ( (*(_BYTE *)(v14 + *(_DWORD *)(v7 + 76) + 4) & 2) != 0 )
      {
LABEL_24:
        v14 += 12;
        ++v35;
      }
      else if ( v31 )
      {
        v23 = *(_DWORD *)(v14 + *(_DWORD *)(v3 + 76) + 4) << 24 >> 26;
        v16 = *(_DWORD **)(v14 + *(_DWORD *)(v3 + 76) + 8);
        v24 = v16;
        if ( v23 == 4 )
        {
          v25 = 0;
          v26 = *(_DWORD *)((char *)v16 + 6) - 1;
        }
        v33 = AST_BuildExpressionFromValue(&v22);
        MessageHandler_SendToInstanceAddress(*(_DWORD *)(*(_DWORD *)(v14 + *(_DWORD *)(v7 + 76)) + 12), v7, v33, &v22, a3);
        AST_Free(v33);
        if ( g_ClipsEvaluationError )
          goto LABEL_8;
        if ( v23 != 2 )
          goto LABEL_24;
        if ( v24 == (_DWORD *)g_ClipsFalseSymbol )
          goto LABEL_8;
        v14 += 12;
        ++v35;
      }
      else
      {
        v23 = *(_DWORD *)(v14 + *(_DWORD *)(v3 + 76) + 4) << 24 >> 26;
        v24 = *(_DWORD **)(v14 + *(_DWORD *)(v3 + 76) + 8);
        if ( (*(_DWORD *)(v14 + *(_DWORD *)(v3 + 76) + 4) & 0xFC) == 0x10 )
        {
          v25 = 0;
          v26 = *(_DWORD *)(*(_DWORD *)(v14 + *(_DWORD *)(v3 + 76) + 8) + 6) - 1;
        }
        if ( !Instance_PutSlotValue((_DWORD *)v7, (int *)(v14 + *(_DWORD *)(v7 + 76)), &v22, a3) )
          goto LABEL_8;
        v14 += 12;
        ++v35;
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
  signed int v5; // ebx
  int v6; // [esp-8h] [ebp-24h] BYREF
  int v7; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, &v6, 111, a3);
  if ( result )
  {
    v5 = Rules_ReadInstancesTextFile(*(const CHAR **)(v7 + 16), 1, *(_DWORD *)(v7 + 16), a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v4, v4);
    return v5;
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
  signed int v5; // ebx
  int v6; // [esp-8h] [ebp-24h] BYREF
  int v7; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, &v6, 111, a3);
  if ( result )
  {
    v5 = Rules_ReadInstancesTextFile(*(const CHAR **)(v7 + 16), 0, *(_DWORD *)(v7 + 16), a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v4, v4);
    return v5;
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
  signed int v6; // ecx
  _DWORD v7[9]; // [esp-8h] [ebp-24h] BYREF

  v7[7] = a1;
  result = Lexer_ParseValueList(1, v7, 111, a3);
  if ( result )
  {
    v6 = Rules_BloadInstancesFile(*(const CHAR **)(v7[2] + 16), v4, a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v6, v5);
    return v6;
  }
  return result;
}
// 4AC1A0: variable 'v4' is possibly undefined
// 4AC1B6: variable 'v5' is possibly undefined
// 4AC1BB: variable 'v6' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC1D0) --------------------------------------------------------
signed int  Rules_BloadInstancesFile(const CHAR *a1, int a2, DWORD a3, double a4)
{
  int v5; // ecx
  void *v6; // ecx
  int v7; // ecx
  int v8; // edx
  void *v9; // ecx
  void *v11; // ecx
  int v12; // edx
  _DWORD v13[4]; // [esp+0h] [ebp-10h] BYREF

  v13[2] = a2;
  if ( Rules_BloadOpenFile(a1, a3) )
  {
    if ( Rules_ValidateBloadInstancesHeader(v5, v5) )
    {
      Rules_BloadAtomTables();
      g_Rules_BloadBytesConsumed = 0;
      Rules_BloadReadBlock((uintptr_t)&g_ClipsBsaveInstanceDataSpace, 4u);
      Rules_BloadReadBlock((uintptr_t)v13, 4u);
      v7 = v13[0];
      if ( v13[0] <= 0 )
      {
LABEL_6:
        Rules_BloadReleaseReadBuffer();
        Rules_FreeBloadAtomTables();
        Rules_BloadCloseFile(v9);
        return v13[0];
      }
      else
      {
        while ( Rules_BloadReadInstanceRecord(v7, a4) )
        {
          if ( v8 + 1 >= v13[0] )
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
_DWORD * Rules_SaveInstancesTextFile(const CHAR *a1, int a2, DWORD a3, int a4, double a5)
{
  _DWORD *result; // eax
  _DWORD *v7; // edi
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ebp
  int v13; // ecx
  int v14; // [esp+0h] [ebp-24h]
  int v15; // [esp+4h] [ebp-20h]
  int v16; // [esp+8h] [ebp-1Ch]

  result = Rules_BuildClassListForSave((int)aSaveInstances, a4, a3, a2, a5);
  v7 = result;
  if ( result || !a4 )
  {
    Rules_ForEachInstanceForSave(a2, a3, (int)result, 1, 0);
    v9 = IO_FOpen(a1, (unsigned __int8 *)aW_5, v8, a3);
    if ( v9 )
    {
      v14 = g_Print_PreserveEscapedCharactersFlag;
      g_Print_PreserveEscapedCharactersFlag = 1;
      v15 = g_Print_AddressesToStringsFlag;
      g_Print_AddressesToStringsFlag = 1;
      v16 = g_Print_InstanceAddressesToNamesFlag;
      g_Print_InstanceAddressesToNamesFlag = 1;
      IO_SetFastSaveFile(v9);
      v12 = Rules_ForEachInstanceForSave(a2, a3, (int)v7, v11, (void (__fastcall *)(int, int))Rules_WriteInstanceTextRecord);
      fclose_(v13);
      IO_SetFastSaveFile(0);
      g_Print_PreserveEscapedCharactersFlag = v14;
      g_Print_AddressesToStringsFlag = v15;
      g_Print_InstanceAddressesToNamesFlag = v16;
      Rules_FreeClassList(v7);
      return (_DWORD *)v12;
    }
    else
    {
      Rules_OpenFileErrorMessage(v10, (int)a1);
      Rules_FreeClassList(v7);
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
_DWORD * Rules_SaveInstancesBinaryFile(const CHAR *a1, int a2, DWORD a3, int a4, double a5)
{
  _DWORD *result; // eax
  _DWORD *v7; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // esi
  int v13; // edx
  int v14; // ecx
  int v15; // [esp+0h] [ebp-18h] BYREF
  const CHAR *v16; // [esp+4h] [ebp-14h]
  int v17; // [esp+8h] [ebp-10h]

  v16 = a1;
  v17 = a2;
  result = Rules_BuildClassListForSave((int)aBsaveInstances, a4, a3, a2, a5);
  v7 = result;
  if ( result || !a4 )
  {
    g_ClipsBsaveInstanceDataSpace = 0;
    Rules_ClearAtomInUseMarks();
    v15 = Rules_ForEachInstanceForSave(v17, a3, (int)v7, v8, Compiler_MarkAndEmit);
    v10 = IO_FOpen(v16, (unsigned __int8 *)aWb_5, v9, a3);
    v12 = v10;
    if ( v10 )
    {
      Compiler_WriteHeaders(v10);
      Rules_BsaveAtomTables(v12);
      fwrite_(&g_ClipsBsaveInstanceDataSpace, v13, v12, 1);
      fwrite_(&v15, 4, v12, 1);
      Rules_SetAtomicValueIndices(0);
      Rules_ForEachInstanceForSave(v17, a3, (int)v7, 0, (void (__fastcall *)(int, int))Compiler_WriteInstanceRecord);
      Rules_RestoreAtomicValueBuckets();
      fclose_(v14);
      Rules_FreeClassList(v7);
      return (_DWORD *)v15;
    }
    else
    {
      Rules_OpenFileErrorMessage(v11, (int)v16);
      Rules_FreeClassList(v7);
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
signed int  Rules_ParseSaveInstancesArgsAndDispatch(int (*a1)(void), double a2)
{
  int v2; // ebp
  signed int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // edi
  _DWORD v7[7]; // [esp+0h] [ebp-38h] BYREF
  int (*v8)(void); // [esp+1Ch] [ebp-1Ch]
  int v9; // [esp+20h] [ebp-18h]

  v8 = a1;
  v2 = 1;
  v9 = 0;
  result = Lexer_ParseValueList(1, v7, 111, a2);
  if ( result )
  {
    v7[6] = *(_DWORD *)(v7[2] + 16);
    if ( Rules_RtnArgCount() <= 1 )
      return ((int (__fastcall *)(int, int))v8)(v9, v2);
    if ( Lexer_ParseValueList(2, v7, 2, a2) )
    {
      if ( !strcmp_(v4, aLocal_1) )
      {
LABEL_5:
        v6 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
        if ( v6 && *(_DWORD *)(v6 + 10) && *(_WORD *)v6 == 2 && !strcmp_(v5, aInherit_3) )
          v9 = 1;
        return ((int (__fastcall *)(int, int))v8)(v9, v2);
      }
      if ( !strcmp_(v5, aVisible_0) )
      {
        v2 = 2;
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
_DWORD * Rules_BuildClassListForSave(int a1, int a2, int a3, int a4, double a5)
{
  _DWORD *v7; // ebp
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  char *v11; // ebx
  int *v13; // eax
  int v14; // ebx
  _DWORD *v15; // ecx
  _DWORD *i; // edx
  int v17; // eax
  int *v18; // ecx
  _DWORD *v19; // eax
  int v20; // ecx
  int v21; // eax
  _DWORD v22[2]; // [esp+0h] [ebp-38h] BYREF
  int v23; // [esp+8h] [ebp-30h]
  int v24; // [esp+18h] [ebp-20h]
  int v25; // [esp+1Ch] [ebp-1Ch]
  int v26; // [esp+20h] [ebp-18h]
  int v27; // [esp+24h] [ebp-14h]
  int v28; // [esp+28h] [ebp-10h]

  v24 = a1;
  v26 = a4;
  v7 = 0;
  v27 = (a3 != 0) + 3;
  v25 = Module_GetCurrent();
  if ( !v9 )
    return v7;
  while ( !Parser_ParseForm((__int16 *)a2, v22, v8, a5) && v22[1] == 2 )
  {
    v13 = v26 == 1 ? Class_LookupByModule(v10, *(_BYTE **)(v23 + 16)) : Class_LookupInScope(*(_BYTE **)(v23 + 16));
    v14 = (int)v13;
    if ( !v13 || (v13[5] & 4) != 0 && !a3 )
      break;
    v15 = v7;
    for ( i = v7; v15; v15 = (_DWORD *)v15[5] )
    {
      v17 = v15[2];
      if ( v14 == v17 || a3 && (Class_HasSuperclass(v17, v14) || Class_HasSuperclass(v14, *(_DWORD *)(v20 + 8))) )
        goto LABEL_3;
      i = v15;
    }
    v18 = *(int **)(g_ClipsMemoryTable + 96);
    v28 = g_ClipsMemoryTable;
    if ( v18 )
    {
      g_ClipsMemFreeListTemp = (int)v18;
      v21 = *v18;
      v8 = v28;
      *(_DWORD *)(v28 + 96) = v21;
      v19 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v19 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    v19[1] = 57;
    v19[5] = 0;
    v19[2] = v14;
    if ( i )
      i[5] = v19;
    else
      v7 = v19;
    a2 = *(_DWORD *)(a2 + 10);
    ++v27;
    if ( !a2 )
      return v7;
  }
LABEL_3:
  if ( a3 )
    v11 = aValidClassName;
  else
    v11 = aValidConcreteC;
  Parser_ReportError(v27, (int)v11);
  Rules_FreeClassList(v7);
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
  _DWORD *v1; // edx

  for ( ; result; *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp )
  {
    v1 = result;
    result = (_DWORD *)result[5];
    g_ClipsMemFreeListTemp = (int)v1;
    *v1 = *(_DWORD *)(g_ClipsMemoryTable + 96);
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AC7E0) --------------------------------------------------------
int  Rules_ForEachInstanceForSave(int a1, int a2, int a3, int a4, void (__fastcall *a5)(int, int))
{
  int v5; // esi
  int v6; // ebp
  int v7; // eax
  int v9; // ecx
  signed int v10; // [esp+0h] [ebp-1Ch]
  int v13; // [esp+Ch] [ebp-10h]

  v13 = Module_GetCurrent();
  v5 = 0;
  if ( a3 )
  {
    v10 = Class_NewTraversalID();
    if ( v10 != -1 )
    {
      v6 = a3;
      do
      {
        if ( g_ClipsHaltExecution && a4 )
          break;
        v7 = Rules_ForEachInstanceInClassSubtree(v13, *(_DWORD *)(v6 + 8), a1, a2, v10, a5);
        v6 = *(_DWORD *)(v6 + 20);
        v5 += v7;
      }
      while ( v6 );
      Class_ReleaseTraversalID();
    }
  }
  else
  {
    v9 = Rules_GetNextInstanceInScope(0);
    if ( v9 )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( a1 == 2 || **(_DWORD **)(*(_DWORD *)(v9 + 44) + 8) == v13 )
        {
          if ( a5 )
            a5(v9, v9);
          ++v5;
        }
        v9 = Rules_GetNextInstanceInScope(v9);
        if ( !v9 )
          return v5;
      }
    }
  }
  return v5;
}
// 4AC810: conditional instruction was optimized away because ebx.4!=0
// 4AC891: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (004AC8C0) --------------------------------------------------------
int  Rules_ForEachInstanceInClassSubtree(
        int a1,
        int a2,
        int a3,
        int a4,
        signed int a5,
        void (__fastcall *a6)(int, int))
{
  int v7; // ebx
  int v8; // eax
  int v9; // edi
  int i; // ecx
  unsigned int v14; // [esp+Ch] [ebp-14h]
  int v15; // [esp+10h] [ebp-10h]

  v7 = a2 + ((a5 - (__CFSHL__(a5 >> 31, 3) + 8 * (a5 >> 31))) >> 3);
  v8 = 1 << (a5 % 8);
  v9 = 0;
  if ( (*(_BYTE *)(v7 + 108) & (unsigned __int8)v8) != 0 )
    return 0;
  *(_BYTE *)(v7 + 108) |= v8;
  if ( a3 == 1 && a1 == **(_DWORD **)(a2 + 8) || a3 == 2 && Class_IsInScope(a2, a1) )
  {
    for ( i = Rules_GetNextInstanceInClass(a2, 0); i; i = Rules_GetNextInstanceInClass(a2, i) )
    {
      if ( a6 )
        a6(i, i);
      ++v9;
    }
  }
  if ( a4 )
  {
    v14 = 0;
    v15 = 0;
    while ( *(unsigned __int16 *)(a2 + 40) > v14 )
    {
      v9 += Rules_ForEachInstanceInClassSubtree(a1, *(_DWORD *)(v15 + *(_DWORD *)(a2 + 42)), a3, 1, a5, a6);
      v15 += 4;
      ++v14;
    }
  }
  return v9;
}
// 4AC959: variable 'i' is possibly undefined

//----- (004ACA00) --------------------------------------------------------
signed int  Rules_WriteInstanceTextRecord(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  unsigned int v5; // edi
  int v6; // ebp
  int v7; // ecx
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  Output_Write(a1, (int)asc_508EB0, a1);
  Output_Write(v3, *(_DWORD *)(*(_DWORD *)(a2 + 28) + 16), v3);
  Output_Write(v4, (int)aOf_1, v4);
  v5 = 0;
  v6 = 0;
  Output_Write(v7, *(_DWORD *)(**(_DWORD **)(a2 + 44) + 16), v7);
  while ( v5 < *(_DWORD *)(*(_DWORD *)(a2 + 44) + 72) )
  {
    Output_Write(a1, (int)asc_508EBC, *(_DWORD *)(*(_DWORD *)(a2 + 72) + v6));
    Output_Write(a1, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v10 + 8) + 12) + 16), v10);
    if ( (*(_DWORD *)(v11 + 4) & 0xFC) == 0x10 )
    {
      if ( *(_DWORD *)(*(_DWORD *)(v11 + 8) + 6) )
      {
        Output_Write(a1, (int)asc_508EC4, v11);
        Lexer_OutputFieldRange(a1, *(_DWORD *)(v13 + 8), *(_DWORD *)(*(_DWORD *)(v13 + 8) + 6) - 1, 0, 0);
      }
    }
    else
    {
      Output_Write(a1, (int)asc_508EC4, v11);
      Rules_PrintAtomValue(a1, *(_DWORD *)(v12 + 4) << 24 >> 26, *(int **)(v12 + 8));
    }
    Output_Write(a1, (int)asc_508EC8, v11);
    v6 += 4;
    ++v5;
  }
  return Output_Write(a1, (int)asc_508ECC, v8);
}
// 4ACA24: variable 'v3' is possibly undefined
// 4ACA30: variable 'v4' is possibly undefined
// 4ACA46: variable 'v7' is possibly undefined
// 4ACA5D: variable 'v8' is possibly undefined
// 4ACA80: variable 'v10' is possibly undefined
// 4ACA92: variable 'v11' is possibly undefined
// 4ACAAC: variable 'v12' is possibly undefined
// 4ACAE9: variable 'v13' is possibly undefined

