/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004A3790) --------------------------------------------------------
signed int Rules_RegisterMathBuiltins(void)
{
  Rules_RegisterHostFunction(aCos, 100, (int)(intptr_t)aCosfunction, (int)(intptr_t)Rules_CosBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aSin, 100, (int)(intptr_t)aSinfunction, (int)(intptr_t)Rules_SinBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aTan, 100, (int)(intptr_t)aTanfunction, (int)(intptr_t)Rules_TanBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aSec, 100, (int)(intptr_t)aSecfunction, (int)(intptr_t)Rules_SecBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aCsc, 100, (int)(intptr_t)aCscfunction, (int)(intptr_t)Rules_CscBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aCot, 100, (int)(intptr_t)aCotfunction, (int)(intptr_t)Rules_CotBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAcos, 100, (int)(intptr_t)aAcosfunction, (int)(intptr_t)Rules_AcosBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAsin, 100, (int)(intptr_t)aAsinfunction, (int)(intptr_t)Rules_AsinBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAtan, 100, (int)(intptr_t)aAtanfunction, (int)(intptr_t)Rules_AtanBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAsec, 100, (int)(intptr_t)aAsecfunction, (int)(intptr_t)Rules_AsecBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAcsc, 100, (int)(intptr_t)aAcscfunction, (int)(intptr_t)Rules_AcscBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAcot, 100, (int)(intptr_t)aAcotfunction, (int)(intptr_t)Rules_AcotBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aCosh, 100, (int)(intptr_t)aCoshfunction, (int)(intptr_t)Rules_CoshBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aSinh, 100, (int)(intptr_t)aSinhfunction, (int)(intptr_t)Rules_SinhBuiltin, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aTanh, 100, (int)(intptr_t)aTanhfunction, (int)(intptr_t)Rules_MathTanh, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aSech, 100, (int)(intptr_t)aSechfunction, (int)(intptr_t)Rules_MathSech, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aCsch, 100, (int)(intptr_t)aCschfunction, (int)(intptr_t)Rules_MathCsch, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aCoth, 100, (int)(intptr_t)aCothfunction, (int)(intptr_t)Rules_MathCoth, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAcosh, 100, (int)(intptr_t)aAcoshfunction, (int)(intptr_t)Rules_MathAcosh, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAsinh, 100, (int)(intptr_t)aAsinhfunction, (int)(intptr_t)Rules_MathAsinh, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAtanh, 100, (int)(intptr_t)aAtanhfunction, (int)(intptr_t)Rules_MathAtanh, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAsech, 100, (int)(intptr_t)aAsechfunction, (int)(intptr_t)Rules_MathAsech, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAcsch, 100, (int)(intptr_t)aAcschfunction, (int)(intptr_t)Rules_MathAcsch, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aAcoth, 100, (int)(intptr_t)aAcothfunction, (int)(intptr_t)Rules_MathAcoth, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aMod, 110, (int)(intptr_t)aModfunction, (int)(intptr_t)Rules_MathMod, (int)(intptr_t)a22n);
  Rules_RegisterHostFunction(aExp, 100, (int)(intptr_t)aExpfunction, (int)(intptr_t)Rules_MathExp, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aLog, 100, (int)(intptr_t)aLogfunction, (int)(intptr_t)Rules_MathLog, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aLog10, 100, (int)(intptr_t)aLog10function, (int)(intptr_t)Rules_MathLog10, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aSqrt, 100, (int)(intptr_t)aSqrtfunction, (int)(intptr_t)Rules_MathSqrt, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aPi, 100, (int)(intptr_t)aPifunction, (int)(intptr_t)Rules_MathPi, (int)(intptr_t)a00_8);
  Rules_RegisterHostFunction(aDegRad, 100, (int)(intptr_t)aDegradfunction, (int)(intptr_t)Rules_MathDegToRad, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aRadDeg, 100, (int)(intptr_t)aRaddegfunction, (int)(intptr_t)Rules_MathRadToDeg, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aDegGrad, 100, (int)(intptr_t)aDeggradfunctio, (int)(intptr_t)Rules_MathDegToGrad, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(aGradDeg, 100, (int)(intptr_t)aGraddegfunctio, (int)(intptr_t)Rules_MathGradToDeg, (int)(intptr_t)a11n_0);
  Rules_RegisterHostFunction(asc_507678, 100, (int)(intptr_t)aPowfunction, (int)(intptr_t)Rules_MathPow, (int)(intptr_t)a22n);
  return Rules_RegisterHostFunction(aRound, 108, (int)(intptr_t)aRoundfunction, (int)(intptr_t)Rules_MathRound, (int)(intptr_t)a11n_0);
}

//----- (004A3BD0) --------------------------------------------------------
signed int  Rules_MathParseSingleArg(double *theNumber, int a2, double a3)
{
  signed int result; // eax
  _DWORD item[10]; // [esp-8h] [ebp-28h] BYREF

  item[8] = a2;
  if ( Lexer_TokenExpect(0, 0, 1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, item, 0, a3);
  if ( result )
  {
    result = 1;
    *theNumber = *(double *)(uintptr_t)(item[2] + 16);
  }
  return result;
}

//----- (004A3C20) --------------------------------------------------------
BOOL __stdcall Rules_MathIsNearZero(double theNumber, double range)
{
  return -range <= theNumber && theNumber <= range;
}

//----- (004A3C50) --------------------------------------------------------
int Rules_MathDomainError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aEmathfun, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDomainErrorFor, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction__1, v2);
  Rules_SetEvaluationErrorFlag(1);
  return Lexer_ErrorRecover(1);
}
// 4A3C70: variable 'v0' is possibly undefined
// 4A3C7C: variable 'v1' is possibly undefined
// 4A3C8B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A3CB0) --------------------------------------------------------
int Rules_MathArgumentOverflowError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aEmathfun, 2, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aArgumentOverfl, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction__1, v2);
  Rules_SetEvaluationErrorFlag(1);
  return Lexer_ErrorRecover(1);
}
// 4A3CD0: variable 'v0' is possibly undefined
// 4A3CDC: variable 'v1' is possibly undefined
// 4A3CEB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004A3D10) --------------------------------------------------------
int Rules_MathSingularityError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aEmathfun, 3, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSingularityAtA, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction__1, v2);
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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  double theNumber; // [esp+0h] [ebp-20h] BYREF
  double cosValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

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
  double theNumber; // [esp+0h] [ebp-20h] BYREF
  double cosValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

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
  double theNumber; // [esp+0h] [ebp-20h] BYREF
  double sinValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

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
  double theNumber; // [esp+0h] [ebp-20h] BYREF
  double sinValue; // [esp+8h] [ebp-18h]
  double v8; // [esp+10h] [ebp-10h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

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
  int v9 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v9 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v9 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v9 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  double v6 CLASH95_UNUSED; // [esp+8h] [ebp-14h]
  int v7 CLASH95_UNUSED; // [esp+10h] [ebp-Ch]
  int v8 CLASH95_UNUSED; // [esp+14h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v7 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v8 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v8 CLASH95_UNUSED; // [esp+14h] [ebp-Ch]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

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
  int v8 CLASH95_UNUSED; // [esp+14h] [ebp-Ch]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-8h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

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
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v7 CLASH95_UNUSED; // [esp+10h] [ebp-Ch]
  int v8 CLASH95_UNUSED; // [esp+14h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+18h] [ebp-4h]

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
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v7 CLASH95_UNUSED; // [esp+8h] [ebp-Ch]
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v7 CLASH95_UNUSED; // [esp+8h] [ebp-Ch]
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  double theNumber; // [esp+0h] [ebp-18h] BYREF
  double v7; // [esp+8h] [ebp-10h]
  int v8 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  _DWORD value1[6]; // [esp+0h] [ebp-58h] BYREF
  /* stack alias of value1[2]: the DATA_OBJECT value slot */
  _DWORD value2[6]; // [esp+18h] [ebp-40h] BYREF
  /* stack alias of value2[2]: the DATA_OBJECT value slot */
  double num1; // [esp+30h] [ebp-28h]
  double num2; // [esp+38h] [ebp-20h]
  double intPart; // [esp+40h] [ebp-18h]

  if ( Lexer_TokenExpect((int)(intptr_t)asc_507678, 0, 2) == -1 )
    return 0.0;
  parseOk = Lexer_ParseValueList(1, value1, 0, a1);
  if ( !parseOk )
    return 0.0;
  parseOk = Lexer_ParseValueList(2, value2, 0, a1);
  if ( !parseOk )
    return 0.0;
  num1 = *(double *)(uintptr_t)(value1[2] + 16);
  num2 = *(double *)(uintptr_t)(value2[2] + 16);
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
  signed int parseStatus; // eax
  int *result; // eax
  signed int intRemainder; // eax
  _DWORD item2[6]; // [esp+8h] [ebp-78h] BYREF
  /* stack alias of item2[1] */
  /* stack alias of item2[2]: the DATA_OBJECT value slot */
  _DWORD item1[6]; // [esp+20h] [ebp-60h] BYREF
  /* stack alias of item1[1] */
  /* stack alias of item1[2]: the DATA_OBJECT value slot */
  double fnum2; // [esp+38h] [ebp-48h]
  double quotient; // [esp+40h] [ebp-40h]
  double truncatedQuotient; // [esp+48h] [ebp-38h]
  double fnum1; // [esp+50h] [ebp-30h]
  double floatRemainder; // [esp+58h] [ebp-28h]

  if ( Lexer_TokenExpect((int)(intptr_t)aMod, 0, 2) == -1 )
  {
    parseStatus = 0;
LABEL_20:
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 1;
    result = Rules_AddIntegerValue(parseStatus);
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
    return result;
  }
  parseStatus = Lexer_ParseValueList(1, item1, 110, a2);
  if ( !parseStatus )
    goto LABEL_20;
  parseStatus = Lexer_ParseValueList(2, item2, 110, a2);
  if ( !parseStatus )
    goto LABEL_20;
  if ( item2[1] == 1 && !*(_DWORD *)(uintptr_t)(item2[2] + 16) || item2[1] != 1 && *(double *)(uintptr_t)(item2[2] + 16) == 0.0 )
  {
    Rules_ReportDivideByZeroError();
    Lexer_ErrorRecover(1);
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 1;
    result = Rules_AddIntegerValue(0);
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  }
  else if ( item1[1] && item2[1] )
  {
    intRemainder = *(_DWORD *)(uintptr_t)(item1[2] + 16) % *(_DWORD *)(uintptr_t)(item2[2] + 16);
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 1;
    result = Rules_AddIntegerValue(intRemainder);
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  }
  else
  {
    if ( item1[1] == 1 )
      fnum1 = (double)*(int *)(uintptr_t)(item1[2] + 16);
    else
      fnum1 = *(double *)(uintptr_t)(item1[2] + 16);
    if ( item2[1] == 1 )
      fnum2 = (double)*(int *)(uintptr_t)(item2[2] + 16);
    else
      fnum2 = *(double *)(uintptr_t)(item2[2] + 16);
    quotient = fnum1 / fnum2;
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 0;
    if ( quotient >= 0.0 )
      truncatedQuotient = floor(quotient);
    else
      truncatedQuotient = ceil(quotient);
    floatRemainder = fnum1 - truncatedQuotient * fnum2;
    result = (int *)(uintptr_t)Rules_AddDoubleValue(floatRemainder);
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  }
  return result;
}

//----- (004A4D20) --------------------------------------------------------
double Rules_MathPi(void)
{
  Lexer_TokenExpect((int)(intptr_t)aPi, 0, 0);
  return acos(g_Rules_MathPiAcosArgument);
}
// 507788: using guessed type double dbl_507788;

//----- (004A4D50) --------------------------------------------------------
double  Rules_MathDegToRad(int a1, int a2, int a3, double a4)
{
  double theNumber[2]; // [esp+0h] [ebp-18h] BYREF
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  int v6 CLASH95_UNUSED; // [esp+10h] [ebp-8h]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-4h]

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
  _DWORD theValue[6]; // [esp+8h] [ebp-28h] BYREF
  /* stack alias of theValue[1] */
  /* stack alias of theValue[2]: the DATA_OBJECT value slot */
  int v8 CLASH95_UNUSED; // [esp+28h] [ebp-8h]

  v8 = returnValue;
  if ( Lexer_TokenExpect((int)(intptr_t)aRound, 0, 1) == -1 )
    return 0;
  result = Lexer_ParseValueList(1, theValue, 110, a2);
  if ( !result )
    return result;
  if ( theValue[1] == 1 )
    return *(_DWORD *)(uintptr_t)(theValue[2] + 16);
  return (int)ceil(*(double *)(uintptr_t)(theValue[2] + 16) + g_Rules_MathRoundHalfOffset);
}
// 5077C0: using guessed type double dbl_5077C0;

//----- (004A5000) --------------------------------------------------------
_DWORD * Help_IndexTopicFile(CHAR *fileName, _BYTE *errorBuffer, int a3, int errorBufferSize, DWORD a5)
{
  int *fp; // esi
  _DWORD *result; // eax
  int v8 CLASH95_UNUSED; // ecx
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
  fp = (int *)(uintptr_t)IO_FOpen(fileName, g_Help_FileOpenModeRead, a3, a5);
  if ( fp )
  {
    fileRecord = Help_GetOrCreateFileRecord(fileName);
    if ( fileRecord )
    {
      lineNumber = 0;
      entryCount = 0;
      inEntry = 0;
      entryClosed = 1;
      while ( fgets_(lineBuffer, 256, (int)(intptr_t)fp) )
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
                fclose_((int)(intptr_t)fp);
                Help_UnloadTopicFile((int)(intptr_t)fileName);
                if ( v12 < 60 )
                  return 0;
                goto LABEL_23;
              }
              inEntry = 1;
              entryClosed = 0;
              result = Help_ParseEntryHeader(fp, (int)(intptr_t)fileName, (int)(intptr_t)errBuf, errBufSize, lineNumber);
              if ( !result )
                return result;
              result = (_DWORD *)(uintptr_t)Help_InsertEntryIntoTopicTree((int)(intptr_t)fileRecord, result, (int)(intptr_t)errBuf, errBufSize, lineNumber);
              if ( !result )
                return result;
            }
          }
          else
          {
            if ( inEntry != 1 )
            {
              fclose_((int)(intptr_t)fp);
              Help_UnloadTopicFile((int)(intptr_t)fileName);
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
      fclose_((int)(intptr_t)fp);
      if ( entryClosed )
      {
        if ( !entryCount )
          Help_UnloadTopicFile((int)(intptr_t)fileName);
        return (_DWORD *)(uintptr_t)entryCount;
      }
      Help_UnloadTopicFile((int)(intptr_t)fileName);
      if ( v13 >= 60 )
      {
LABEL_23:
        sprintf_(errBuf, "Line %d : Previous entry not closed.", lineNumber);
        return 0;
      }
    }
    else
    {
      fclose_((int)(intptr_t)fp);
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
      topicFile = *(_DWORD *)(uintptr_t)(topicFile + 88);
    }
    while ( topicFile && strcmp_(topicFile, fileName) );
  }
  if ( !topicFile )
    return 0;
  Help_FreeTopicTree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(topicFile + 80));
  if ( (_DWORD *)(uintptr_t)prevFile == foundFile )
    g_HelpLoadedTopicFileList = foundFile[22];
  else
    *(_DWORD *)(uintptr_t)(prevFile + 88) = foundFile[22];
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

  offset = Help_FindOrAdvanceTopicEntry((int)(intptr_t)fileName, menu, code, topicName);
  if ( offset < 0 )
    return 0;
  result = IO_FOpen(fileName, g_Help_FileOpenModeRead, v6, offset);
  if ( result )
  {
    if ( IO_SeekStreamGuarded(result, offset, 0, (int)(intptr_t)code) < 0 )
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
      fileRecord = *(_DWORD *)(uintptr_t)(fileRecord + 88);
    while ( fileRecord && strcmp_(fileRecord, fileName) );
  }
  if ( !fileRecord )
  {
    *code = -10;
    return 0;
  }
  if ( !*(_DWORD *)(uintptr_t)(fileRecord + 84) )
  {
    *code = -25;
    return 0;
  }
  result = IO_FOpen(fileName, g_Help_FileOpenModeRead, fileRecord, a3);
  fp = result;
  if ( result )
  {
    if ( IO_SeekStreamGuarded(result, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v8 + 84) + 88), 0, (int)(intptr_t)code) < 0 )
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

  strPtr = (_BYTE *)(uintptr_t)result;
  if ( *(_BYTE *)(uintptr_t)result )
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
      *(_DWORD *)(uintptr_t)(v6 + 88) = newRecord;
      return newRecord;
    }
    else
    {
      g_HelpLoadedTopicFileList = (int)(intptr_t)newRecord;
      return newRecord;
    }
  }
  record = g_HelpLoadedTopicFileList;
  if ( !*(_DWORD *)(uintptr_t)(g_HelpLoadedTopicFileList + 88) )
  {
LABEL_5:
    result = (char *)(uintptr_t)strcmp_(record, fileName);
    if ( !result )
      return result;
    goto LABEL_6;
  }
  while ( 1 )
  {
    result = (char *)(uintptr_t)strcmp_(record, fileName);
    if ( !result )
      return result;
    record = *(_DWORD *)(uintptr_t)(v4 + 88);
    if ( !*(_DWORD *)(uintptr_t)(record + 88) )
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
        if ( bufferedCount > 0 && (unsigned int)*(unsigned __int8 *)(uintptr_t)*fp - 13 > 0xFD )
        {
          streamBufPtr = (unsigned __int8 *)(uintptr_t)*fp;
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
        Str_UppercaseToDelimiter((int)(intptr_t)(entry + 2), v18);
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
