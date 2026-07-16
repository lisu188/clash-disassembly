/* Generated from src/recovered/rules/clips/00496000_events.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0049E930) --------------------------------------------------------
signed int * Rules_HostFormat(double context)
{
  signed int *emptyResult; // ebp
  char *outputString; // esi
  int v3; // ecx
  int argCount; // ebx
  int logicalName; // ecx
  int v7; // ecx
  signed int formatString; // ebp
  char formatChar; // ah
  int segmentStart; // ecx
  int segmentLength; // edi
  _BYTE *i; // eax
  int percentPos; // edi
  int v14; // ecx
  char v15; // cl
  unsigned __int8 conversionChar; // ch
  int v17; // edx
  int specLength; // eax
  const char *convertedString; // eax
  signed int *v20; // eax
  int v21; // edx
  int v22; // ecx
  int v23; // ecx
  char flagBuffer[512]; // [esp+0h] [ebp-284h] BYREF
  char specBuffer[80]; // [esp+200h] [ebp-84h] BYREF
  int formatIndex; // [esp+250h] [ebp-34h] BYREF
  int outputCapacity; // [esp+254h] [ebp-30h] BYREF
  int outputLength; // [esp+258h] [ebp-2Ch] BYREF
  int longFlag; // [esp+25Ch] [ebp-28h] BYREF
  int argIndex; // [esp+260h] [ebp-24h]
  int savedLogicalName; // [esp+264h] [ebp-20h]
  signed int *fallbackResult; // [esp+268h] [ebp-1Ch]

  argIndex = 3;
  formatIndex = 0;
  outputCapacity = 0;
  outputLength = 0;
  emptyResult = Str_Intern(g_Rules_HostFormatEmptyResult, 0);
  fallbackResult = emptyResult;
  outputString = 0;
  argCount = Lexer_TokenExpect(2);
  if ( argCount == -1 )
    return emptyResult;
  logicalName = Rules_GetLogicalNameArg(1, (int)(intptr_t)aStdout_0, v3, context);
  savedLogicalName = logicalName;
  if ( logicalName )
  {
    if ( !strcmp_(logicalName, aNil_0) || IO_QueryRouters(logicalName) )
    {
      formatString = Rules_FormatCountConversionSpecs(argCount, context);
      if ( formatString )
      {
        while ( 1 )
        {
          formatChar = *(_BYTE *)(uintptr_t)(formatString + formatIndex);
          if ( !formatChar )
            break;
          if ( formatChar == 37 )
          {
            percentPos = formatIndex++;
            LOBYTE(v14) = Rules_FormatParseFlag(formatString, &formatIndex, &longFlag, flagBuffer);
            BYTE1(v14) = v14;
            if ( (_BYTE)v14 == 32 )
            {
              outputString = Str_Append(flagBuffer, outputString, (unsigned int *)&outputCapacity, &outputLength);
              if ( !outputString )
                return fallbackResult;
            }
            else
            {
              strncpy_(v14, percentPos + formatString);
              v17 = longFlag;
              specBuffer[formatIndex - percentPos] = 0;
              if ( !v17 && (v15 == 100 || v15 == 111 || v15 == 117 || v15 == 120) )
              {
                specLength = formatIndex - percentPos;
                flagBuffer[specLength + 511] = 108;
                specBuffer[specLength] = conversionChar;
                longFlag = 1;
                specBuffer[specLength + 1] = 0;
              }
              convertedString = (const char *)(uintptr_t)Rules_FormatConvertArg(specBuffer, argIndex, longFlag, conversionChar, context);
              if ( !convertedString )
              {
                if ( outputString )
                  Mem_SmallBlockFree(outputString, outputCapacity);
                return fallbackResult;
              }
              outputString = Str_Append(convertedString, outputString, (unsigned int *)&outputCapacity, &outputLength);
              if ( !outputString )
                return fallbackResult;
              ++argIndex;
            }
          }
          else
          {
            segmentStart = formatIndex;
            segmentLength = 0;
            for ( i = (_BYTE *)(uintptr_t)(formatString + formatIndex); *i != 37; ++segmentLength )
            {
              if ( !*i )
                break;
              if ( segmentLength >= 80 )
                break;
              ++i;
              ++formatIndex;
            }
            outputString = Str_AppendBounded(segmentStart + formatString, outputString, &outputLength, formatIndex - segmentStart, (unsigned int *)&outputCapacity);
          }
        }
        if ( outputString )
        {
          v20 = Str_Intern(outputString, v7);
          if ( strcmp_(v20, v21) )
            Output_Write(savedLogicalName, (int)(intptr_t)outputString, v22);
          Mem_SmallBlockFree(outputString, outputCapacity);
          return (signed int *)(uintptr_t)v23;
        }
        else
        {
          return Str_Intern(g_Rules_HostFormatEmptyResult, v7);
        }
      }
      else
      {
        return fallbackResult;
      }
    }
    else
    {
      IO_ReportUnrecognizedRouter(savedLogicalName);
      return emptyResult;
    }
  }
  else
  {
    Rules_ReportIllegalLogicalName();
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return emptyResult;
  }
}
// 49E9A8: variable 'v3' is possibly undefined
// 49EB1A: variable 'v14' is possibly undefined
// 49EB3F: variable 'v15' is possibly undefined
// 49EB5E: variable 'v16' is possibly undefined
// 49EC37: variable 'v7' is possibly undefined
// 49EC45: variable 'v21' is possibly undefined
// 49EC57: variable 'v22' is possibly undefined
// 49EC6A: variable 'v23' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (0049ECA0) --------------------------------------------------------
signed int  Rules_FormatCountConversionSpecs(int argCount, double context)
{
  signed int result; // eax
  int specCount; // edi
  int formatString; // esi
  char ch; // dl
  _DWORD argData[6]; // [esp+0h] [ebp-44h] BYREF
  _BYTE flagBuffer[12]; // [esp+18h] [ebp-2Ch] BYREF
  int longFlag; // [esp+24h] [ebp-20h] BYREF
  int formatIndex[7]; // [esp+28h] [ebp-1Ch] BYREF

  result = Lexer_ParseValueList(2, argData, 3, context);
  if ( result )
  {
    specCount = 0;
    formatString = *(_DWORD *)(uintptr_t)(argData[2] + 16);
    formatIndex[0] = 0;
    while ( 1 )
    {
      ch = *(_BYTE *)(uintptr_t)(formatString + formatIndex[0]);
      if ( !ch )
        break;
      if ( ch == 37 )
      {
        ++formatIndex[0];
        if ( Rules_FormatParseFlag(formatString, formatIndex, &longFlag, flagBuffer) != 32 )
          ++specCount;
      }
      else
      {
        ++formatIndex[0];
      }
    }
    if ( specCount == argCount - 2 )
    {
      return formatString;
    }
    else
    {
      Rules_ExpectedCountError((int)(intptr_t)aFormat, specCount + 2);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}

//----- (0049ED50) --------------------------------------------------------
char  Rules_FormatParseFlag(int formatString, int *formatIndex, _DWORD *longFlagOut, _BYTE *flagBuffer)
{
  int copyIndex; // esi
  char formatChar; // bl
  _BYTE *bufferCursor; // ecx
  char *charPtr; // eax
  char result; // al
  _DWORD *v11; // edx
  _DWORD *v12; // edx
  _DWORD *v13; // edx
  _DWORD *v14; // edx
  _DWORD *v15; // edx
  int startIndex; // [esp+0h] [ebp-18h]

  copyIndex = 0;
  *longFlagOut = 0;
  formatChar = *(_BYTE *)(uintptr_t)(*formatIndex + formatString);
  switch ( formatChar )
  {
    case 'n':
      sprintf_(flagBuffer, asc_5069B8);
      result = 32;
      ++*v11;
      break;
    case 'r':
      sprintf_(flagBuffer, asc_506A6C);
      result = 32;
      ++*v12;
      break;
    case 't':
      sprintf_(flagBuffer, asc_5069C0);
      result = 32;
      ++*v13;
      break;
    case 'v':
      sprintf_(flagBuffer, asc_5069CC);
      result = 32;
      ++*v14;
      break;
    case '%':
      sprintf_(flagBuffer, asc_506A70);
      result = 32;
      ++*v15;
      break;
    default:
      startIndex = *formatIndex;
      *flagBuffer = 0;
      bufferCursor = flagBuffer;
      while ( 1 )
      {
        charPtr = (char *)(uintptr_t)(*formatIndex + formatString);
        if ( *charPtr == 37 || !*charPtr || *formatIndex - startIndex >= 80 )
          return 32;
        result = *charPtr;
        ++bufferCursor;
        flagBuffer[copyIndex++] = result;
        *bufferCursor = 0;
        if ( result == 100
          || result == 111
          || result == 120
          || result == 117
          || result == 99
          || result == 115
          || result == 101
          || result == 102
          || result == 103 )
        {
          break;
        }
        ++*formatIndex;
      }
      if ( *(_BYTE *)(uintptr_t)(formatString + *formatIndex - 1) == 108 )
        *longFlagOut = 1;
      ++*formatIndex;
      break;
  }
  return result;
}
// 49EE0B: variable 'v11' is possibly undefined
// 49EE27: variable 'v12' is possibly undefined
// 49EE43: variable 'v13' is possibly undefined
// 49EE5F: variable 'v14' is possibly undefined
// 49EE7B: variable 'v15' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (0049EEE0) --------------------------------------------------------
signed int  Rules_FormatConvertArg(
        const char *formatSpec,
        int argIndex,
        int longFlag,
        unsigned int conversionChar,
        double context)
{
  signed int result; // eax
  _DWORD *charBuffer; // eax
  char *v9; // ecx
  signed int internedValue; // esi
  int v11; // edx
  _DWORD *v12; // ecx
  int v13; // ecx
  _DWORD *stringBuffer; // eax
  _DWORD *numberBuffer; // eax
  int v17; // eax
  _DWORD *floatBuffer; // eax
  double floatValue; // [esp+0h] [ebp-30h]
  int argData; // [esp+8h] [ebp-28h] BYREF
  int argType; // [esp+Ch] [ebp-24h]
  int argValue; // [esp+10h] [ebp-20h]
  int intValue; // [esp+20h] [ebp-10h]

  if ( conversionChar >= 0x67 )
  {
    if ( conversionChar <= 0x67 )
      goto LABEL_19;
    if ( conversionChar >= 0x73 )
    {
      if ( conversionChar <= 0x73 )
      {
        result = Lexer_ParseValueList(argIndex, &argData, 111, context);
        if ( !result )
          return result;
        stringBuffer = Mem_SmallBlockAlloc(strlen(*(const char **)(uintptr_t)(argValue + 16)) + strlen(formatSpec) + 200);
        sprintf_(stringBuffer, formatSpec, *(_DWORD *)(uintptr_t)(argValue + 16));
        goto LABEL_6;
      }
      if ( conversionChar < 0x75 || conversionChar > 0x75 && conversionChar != 120 )
        goto LABEL_17;
    }
    else if ( conversionChar != 111 )
    {
      goto LABEL_17;
    }
LABEL_11:
    result = Lexer_ParseValueList(argIndex, &argData, 110, context);
    if ( !result )
      return result;
    numberBuffer = Mem_SmallBlockAlloc(strlen(formatSpec) + 200);
    if ( argType )
    {
      sprintf_(numberBuffer, formatSpec, *(_DWORD *)(uintptr_t)(argValue + 16));
    }
    else
    {
      intValue = (int)*(double *)(uintptr_t)(argValue + 16);
      sprintf_(v17, formatSpec, intValue);
    }
LABEL_6:
    internedValue = Str_Intern(v9, (int)(intptr_t)v9)[4];
    Mem_SmallBlockFree(v12, v11);
    return internedValue;
  }
  if ( conversionChar < 0x64 )
  {
    if ( conversionChar == 99 )
    {
      result = Lexer_ParseValueList(argIndex, &argData, 111, context);
      if ( !result )
        return result;
      charBuffer = Mem_SmallBlockAlloc(strlen(formatSpec) + 200);
      sprintf_(charBuffer, formatSpec, **(unsigned __int8 **)(uintptr_t)(argValue + 16));
      goto LABEL_6;
    }
LABEL_17:
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aErrorInFormatT, longFlag);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aForFormattedOu, v13);
    return 0;
  }
  if ( conversionChar <= 0x64 )
    goto LABEL_11;
LABEL_19:
  result = Lexer_ParseValueList(argIndex, &argData, 110, context);
  if ( result )
  {
    floatBuffer = Mem_SmallBlockAlloc(strlen(formatSpec) + 200);
    if ( argType )
    {
      floatValue = (double)*(int *)(uintptr_t)(argValue + 16);
      sprintf_(floatBuffer, formatSpec, floatValue);
    }
    else
    {
      sprintf_(floatBuffer, formatSpec, *(double *)(uintptr_t)(argValue + 16));
    }
    goto LABEL_6;
  }
  return result;
}
// 49F064: inconsistent fpu stack
// 49EF4A: variable 'v9' is possibly undefined
// 49EF54: variable 'v12' is possibly undefined
// 49EF54: variable 'v11' is possibly undefined
// 49EFB5: variable 'v13' is possibly undefined
// 49F077: variable 'v17' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0049F120) --------------------------------------------------------
signed int * Rules_HostReadline(int returnValue, unsigned int a2, double context)
{
  int argCount; // eax
  int v4; // ecx
  char *logicalName; // esi
  unsigned int v6; // ecx
  char *lineBuffer; // ebx
  int v8; // ecx
  signed int *result; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  signed int *v16; // eax
  int v17; // ecx
  unsigned int bufferSize[5]; // [esp+0h] [ebp-14h] BYREF

  bufferSize[3] = a2;
  bufferSize[0] = 0;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 3;
  argCount = Lexer_TokenExpect(1);
  if ( argCount == -1 )
  {
    result = Str_Intern(aReadError, v4);
LABEL_8:
    *(_DWORD *)(uintptr_t)(v10 + 8) = result;
    return result;
  }
  if ( argCount )
  {
    logicalName = (char *)(uintptr_t)Rules_GetLogicalNameArg(1, (int)(intptr_t)aStdin, v4, context);
    if ( !logicalName )
    {
      Rules_ReportIllegalLogicalName();
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      result = Str_Intern(aReadError, v11);
      *(_DWORD *)(uintptr_t)(v12 + 8) = result;
      return result;
    }
  }
  else
  {
    logicalName = aStdin;
  }
  if ( !IO_QueryRouters((int)(intptr_t)logicalName) )
  {
    IO_ReportUnrecognizedRouter((int)(intptr_t)logicalName);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    result = Str_Intern(aReadError, v13);
    *(_DWORD *)(uintptr_t)(v14 + 8) = result;
    return result;
  }
  g_Lexer_PendingLineCharIndex = 0;
  lineBuffer = Rules_ReadLineWithEscaping((int)(intptr_t)logicalName, &g_Lexer_PendingLineCharIndex, bufferSize, v6);
  g_Lexer_PendingLineCharIndex = -1;
  if ( !Rules_GetEvaluationErrorFlag() )
  {
    if ( lineBuffer )
    {
      v16 = Str_Intern(lineBuffer, v8);
      *(_DWORD *)(uintptr_t)(v17 + 8) = v16;
      return (signed int *)(uintptr_t)Mem_SmallBlockFree(lineBuffer, bufferSize[0]);
    }
    result = Str_Intern(aEof, v8);
    *(_DWORD *)(uintptr_t)(v10 + 4) = 2;
    goto LABEL_8;
  }
  result = Str_Intern(aReadError, v8);
  *(_DWORD *)(uintptr_t)(v15 + 8) = result;
  if ( lineBuffer )
    return (signed int *)(uintptr_t)Mem_SmallBlockFree(lineBuffer, bufferSize[0]);
  return result;
}
// 49F17C: variable 'v6' is possibly undefined
// 49F1A3: variable 'v8' is possibly undefined
// 49F1A8: variable 'v10' is possibly undefined
// 49F1BF: variable 'v4' is possibly undefined
// 49F202: variable 'v11' is possibly undefined
// 49F207: variable 'v12' is possibly undefined
// 49F232: variable 'v13' is possibly undefined
// 49F237: variable 'v14' is possibly undefined
// 49F24C: variable 'v15' is possibly undefined
// 49F270: variable 'v17' is possibly undefined
// 51A628: using guessed type int dword_51A628;

//----- (0049F290) --------------------------------------------------------
char * Rules_ReadLineWithEscaping(int logicalName, int *currentPosition, unsigned int *maximumSize, unsigned int a4)
{
  int ch; // esi
  char *appended; // edx
  unsigned int v7; // ecx

  ch = Lexer_PeekChar(logicalName, a4);
  appended = 0;
  if ( ch == -1 )
    return 0;
  while ( ch != 10 && ch != 13 && ch != -1 && !Rules_GetEvaluationErrorFlag() )
  {
    appended = Str_AppendCharEscaping(ch, appended, maximumSize, currentPosition, *maximumSize + 80);
    ch = Lexer_PeekChar(logicalName, v7);
  }
  return Str_AppendCharEscaping(0, appended, maximumSize, currentPosition, *maximumSize + 80);
}
// 49F2D2: variable 'appended' is possibly undefined
// 49F2DB: variable 'v7' is possibly undefined

//----- (0049F310) --------------------------------------------------------
signed int Rules_ReportIllegalLogicalName(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aIofun, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalLogical, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_, v2);
}
// 49F330: variable 'v0' is possibly undefined
// 49F33C: variable 'v1' is possibly undefined
// 49F34B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049F360) --------------------------------------------------------
signed int Rules_RegisterPredicateHostFunctions(void)
{
  Rules_RegisterHostFunction(aNot_0, 98, (int)(intptr_t)aNotfunction, (int)(intptr_t)Rules_NotFunction, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aAnd_0, 98, (int)(intptr_t)aAndfunction, (int)(intptr_t)Rules_AndFunction, (int)(intptr_t)a2);
  Rules_RegisterHostFunction(aOr_0, 98, (int)(intptr_t)aOrfunction, (int)(intptr_t)Rules_OrFunction, (int)(intptr_t)a2);
  Rules_RegisterHostFunction(aEq_0, 98, (int)(intptr_t)aEqfunction, (int)(intptr_t)Rules_HostEq, (int)(intptr_t)a2);
  Rules_RegisterHostFunction(aNeq_0, 98, (int)(intptr_t)aNeqfunction, (int)(intptr_t)Rules_HostNeq, (int)(intptr_t)a2);
  Rules_RegisterHostFunction(asc_506B64, 98, (int)(intptr_t)aLessthanorequa, (int)(intptr_t)Rules_LessThanOrEqualFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(asc_506B84, 98, (int)(intptr_t)aGreaterthanore, (int)(intptr_t)Rules_GreaterThanOrEqualFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(asc_506B9C, 98, (int)(intptr_t)aLessthanfuncti, (int)(intptr_t)Rules_LessThanFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(asc_506BB4, 98, (int)(intptr_t)aGreaterthanfun, (int)(intptr_t)Rules_GreaterThanFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(asc_506BD0, 98, (int)(intptr_t)aNumericequalfu, (int)(intptr_t)Rules_NumericEqualFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(asc_506BEC, 98, (int)(intptr_t)aNumericnotequa, (int)(intptr_t)Rules_NumericNotEqualFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(asc_506BF0, 98, (int)(intptr_t)aNumericnotequa, (int)(intptr_t)Rules_NumericNotEqualFunction, (int)(intptr_t)a2N);
  Rules_RegisterHostFunction(aSymbolp, 98, (int)(intptr_t)aSymbolpfunctio, (int)(intptr_t)Rules_HostSymbolp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aWordp, 98, (int)(intptr_t)aSymbolpfunctio, (int)(intptr_t)Rules_HostSymbolp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aStringp, 98, (int)(intptr_t)aStringpfunctio, (int)(intptr_t)Rules_HostStringp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aLexemep, 98, (int)(intptr_t)aLexemepfunctio, (int)(intptr_t)Rules_HostLexemep, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aNumberp, 98, (int)(intptr_t)aNumberpfunctio, (int)(intptr_t)Rules_HostNumberp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aIntegerp, 98, (int)(intptr_t)aIntegerpfuncti, (int)(intptr_t)Rules_HostIntegerp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aFloatp, 98, (int)(intptr_t)aFloatpfunction, (int)(intptr_t)Rules_HostFloatp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aOddp, 98, (int)(intptr_t)aOddpfunction, (int)(intptr_t)Rules_OddpFunction, (int)(intptr_t)a11i_2);
  Rules_RegisterHostFunction(aEvenp, 98, (int)(intptr_t)aEvenpfunction, (int)(intptr_t)Rules_EvenpFunction, (int)(intptr_t)a11i_2);
  Rules_RegisterHostFunction(aMultifieldp, 98, (int)(intptr_t)aMultifieldpfun, (int)(intptr_t)Rules_HostMultifieldp, (int)(intptr_t)a11_6);
  Rules_RegisterHostFunction(aSequencep, 98, (int)(intptr_t)aMultifieldpfun, (int)(intptr_t)Rules_HostMultifieldp, (int)(intptr_t)a11_6);
  return Rules_RegisterHostFunction(aPointerp, 98, (int)(intptr_t)aPointerpfuncti, (int)(intptr_t)Rules_PointerpFunction, (int)(intptr_t)a11_6);
}

//----- (0049F640) --------------------------------------------------------
int  Rules_HostEq(int returnValue, double context)
{
  int result; // eax
  int argument_count; // esi
  int argument_index; // ebx
  uintptr_t expression; // ecx
  _DWORD first[6]; // [esp-4h] [ebp-44h] BYREF
  _DWORD current[6]; // [esp+14h] [ebp-2Ch] BYREF

  (void)returnValue;
  result = Rules_RtnArgCount();
  argument_count = result;
  if ( result )
  {
    argument_index = 2;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
    if ( !expression )
      return 1;
    Parser_ParseForm((__int16 *)expression, first, (int)expression, context);
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
    if ( argument_count < 2 )
      return 1;
    while ( expression )
    {
      Parser_ParseForm((__int16 *)expression, current, (int)expression, context);
      if ( current[1] != first[1] )
        return 0;
      if ( current[1] == 4 )
      {
        result = Rules_MultifieldRangesEqual(current, first);
        if ( !result )
          return result;
      }
      else if ( current[2] != first[2] )
      {
        return 0;
      }
      ++argument_index;
      expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
      if ( argument_index > argument_count )
        return 1;
    }
    return 1;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049F6E0) --------------------------------------------------------
int  Rules_HostNeq(double context)
{
  int result; // eax
  int argument_index; // ebx
  uintptr_t expression; // ecx
  _DWORD first[6]; // [esp+0h] [ebp-48h] BYREF
  _DWORD current[6]; // [esp+18h] [ebp-30h] BYREF

  result = Rules_RtnArgCount();
  if ( result )
  {
    argument_index = 2;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
    if ( !expression )
      return 1;
    Parser_ParseForm((__int16 *)expression, first, (int)expression, context);
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
    if ( result < 2 )
      return 1;
    while ( expression )
    {
      Parser_ParseForm((__int16 *)expression, current, (int)expression, context);
      if ( current[1] == first[1] )
      {
        if ( current[1] == 4 )
        {
          if ( Rules_MultifieldRangesEqual(current, first) == 1 )
            return 0;
        }
        else if ( current[2] == first[2] )
        {
          return 0;
        }
      }
      ++argument_index;
      expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
      if ( argument_index > result )
        return 1;
    }
    return 1;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049F790) --------------------------------------------------------
BOOL  Rules_HostStringp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 3 )
      return 1;
  }
  return result;
}

//----- (0049F7E0) --------------------------------------------------------
BOOL  Rules_HostSymbolp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 2 )
      return 1;
  }
  return result;
}

//----- (0049F830) --------------------------------------------------------
BOOL  Rules_HostLexemep(double context)
{
  BOOL result; // eax
  int argData; // [esp-4h] [ebp-20h] BYREF
  int argType; // [esp+0h] [ebp-1Ch]

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, &argData, context);
    if ( argType == 2 || argType == 3 )
      return 1;
  }
  return result;
}

//----- (0049F880) --------------------------------------------------------
BOOL  Rules_HostNumberp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] <= 1u )
      return 1;
  }
  return result;
}
// 49F8B5: simplified comparisons for '%var_1C.4': !=0 && !=1 became >=2u

//----- (0049F8D0) --------------------------------------------------------
BOOL  Rules_HostFloatp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( !argData[1] )
      return 1;
  }
  return result;
}

//----- (0049F920) --------------------------------------------------------
BOOL  Rules_HostIntegerp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 1 )
      return 1;
  }
  return result;
}

//----- (0049F960) --------------------------------------------------------
BOOL  Rules_HostMultifieldp(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 4 )
      return 1;
  }
  return result;
}

//----- (0049F9B0) --------------------------------------------------------
BOOL  Rules_PointerpFunction(double context)
{
  BOOL result; // eax
  _DWORD argData[8]; // [esp-4h] [ebp-20h] BYREF

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    Rules_RtnUnknown(1, argData, context);
    if ( argData[1] == 5 )
      return 1;
  }
  return result;
}

//----- (0049FA00) --------------------------------------------------------
int  Rules_NotFunction(int a1, double context)
{
  uintptr_t expression; // eax
  _DWORD parsed[6]; // [esp-4h] [ebp-1Ch] BYREF

  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 0;
  if ( Parser_ParseForm((__int16 *)expression, parsed, a1, context) )
    return 0;
  return parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FA50) --------------------------------------------------------
int  Rules_AndFunction(int returnValue, double context)
{
  uintptr_t expression; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-20h] BYREF

  (void)returnValue;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
    return 1;
  while ( expression )
  {
    if ( Parser_ParseForm((__int16 *)expression, parsed, (int)expression, context) )
      return 0;
    if ( parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2 )
      return 0;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FAB0) --------------------------------------------------------
int  Rules_OrFunction(int returnValue, double context)
{
  uintptr_t expression; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-20h] BYREF

  (void)returnValue;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  while ( expression )
  {
    if ( Parser_ParseForm((__int16 *)expression, parsed, (int)expression, context) )
      return 0;
    if ( parsed[2] != g_ClipsFalseSymbol || parsed[1] != 2 )
      return 1;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 0;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049FB00) --------------------------------------------------------
double  Rules_LessThanOrEqualFunction(int a1, double result, int a3)
{
  int firstExpr; // esi
  int firstArgValid; // eax
  int currentExpr; // esi
  int i; // edi
  int argValid; // eax
  int previousData; // [esp+0h] [ebp-44h] BYREF
  int previousType; // [esp+4h] [ebp-40h]
  int previousValue; // [esp+8h] [ebp-3Ch]
  int currentData; // [esp+18h] [ebp-2Ch] BYREF
  int currentType; // [esp+1Ch] [ebp-28h]
  int currentValue; // [esp+20h] [ebp-24h]
  int v14; // [esp+38h] [ebp-Ch]
  int v15; // [esp+3Ch] [ebp-8h]

  v15 = a1;
  v14 = a3;
  firstExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  if ( firstExpr )
  {
    result = Rules_CoerceFormToNumericArg((__int16 *)(uintptr_t)firstExpr, 0, &previousData, result, 1);
    if ( firstArgValid )
    {
      currentExpr = *(_DWORD *)(uintptr_t)(firstExpr + 10);
      for ( i = 2; currentExpr; ++i )
      {
        result = Rules_CoerceFormToNumericArg((__int16 *)(uintptr_t)currentExpr, 0, &currentData, result, i);
        if ( !argValid )
          break;
        if ( previousType == 1 )
        {
          if ( currentType == 1 )
          {
            if ( *(_DWORD *)(uintptr_t)(previousValue + 16) > *(_DWORD *)(uintptr_t)(currentValue + 16) )
              return result;
          }
          else if ( (double)*(int *)(uintptr_t)(previousValue + 16) > *(double *)(uintptr_t)(currentValue + 16) )
          {
            return result;
          }
        }
        else if ( currentType == 1 )
        {
          if ( (double)*(int *)(uintptr_t)(currentValue + 16) < *(double *)(uintptr_t)(previousValue + 16) )
            return result;
        }
        else if ( *(double *)(uintptr_t)(previousValue + 16) > *(double *)(uintptr_t)(currentValue + 16) )
        {
          return result;
        }
        previousType = currentType;
        previousValue = currentValue;
        currentExpr = *(_DWORD *)(uintptr_t)(currentExpr + 10);
      }
    }
  }
  return result;
}
// 49FB39: variable 'v4' is possibly undefined
// 49FB5C: variable 'v7' is possibly undefined
// 51A960: using guessed type int dword_51A960;

CLASH95_INTERNAL int Parser_ParseNumericFormCompat(__int16 *expression, int coerce_integer_to_float, _DWORD *parsed, double context, int argument_index)
{
  unsigned int value_type;
  int value;

  if ( !expression || !parsed )
    return 0;
  if ( (unsigned __int16)*expression > 1u )
  {
    Parser_ParseForm(expression, parsed, coerce_integer_to_float, context);
    value_type = parsed[1];
    value = parsed[2];
  }
  else
  {
    value_type = *expression;
    value = *(_DWORD *)(expression + 1);
  }
  if ( value_type > 1 )
  {
    Parser_ReportError(argument_index, (int)(intptr_t)aIntegerOrFlo_0);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    parsed[1] = 1;
    parsed[2] = Rules_AddIntegerValue(0);
    return 0;
  }
  if ( coerce_integer_to_float && value_type == 1 )
    value = Rules_AddDoubleValue((double)*(int *)((uintptr_t)(unsigned int)value + 16));
  parsed[1] = value_type;
  parsed[2] = value;
  return 1;
}

CLASH95_INTERNAL int Parser_NumberValueAsInt(int value)
{
  if ( !value )
    return 0;
  return *(_DWORD *)((uintptr_t)(unsigned int)value + 16);
}

CLASH95_INTERNAL double Parser_NumberValueAsDouble(int value)
{
  if ( !value )
    return 0.0;
  return *(double *)((uintptr_t)(unsigned int)value + 16);
}

CLASH95_INTERNAL double Parser_NumberValueAsComparableDouble(int type, int value)
{
  return type == 1 ? (double)Parser_NumberValueAsInt(value) : Parser_NumberValueAsDouble(value);
}

//----- (0049FC20) --------------------------------------------------------
int  Rules_GreaterThanOrEqualFunction(int a1, double result, int a3)
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
    if ( previous[1] == 1 )
    {
      if ( current[1] == 1 )
      {
        if ( Parser_NumberValueAsInt(previous[2]) < Parser_NumberValueAsInt(current[2]) )
          return 0;
      }
      else if ( (double)Parser_NumberValueAsInt(previous[2]) < Parser_NumberValueAsDouble(current[2]) )
      {
        return 0;
      }
    }
    else if ( current[1] == 1 )
    {
      if ( (double)Parser_NumberValueAsInt(current[2]) > Parser_NumberValueAsDouble(previous[2]) )
        return 0;
    }
    else if ( Parser_NumberValueAsDouble(previous[2]) < Parser_NumberValueAsDouble(current[2]) )
    {
      return 0;
    }
    previous[1] = current[1];
    previous[2] = current[2];
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049FD40) --------------------------------------------------------
int  Rules_LessThanFunction(int a1, double result, int a3)
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
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) >= Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    previous[1] = current[1];
    previous[2] = current[2];
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049FE60) --------------------------------------------------------
int  Rules_GreaterThanFunction(int a1, double result, int a3)
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
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) <= Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    previous[1] = current[1];
    previous[2] = current[2];
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (0049FF80) --------------------------------------------------------
int  Rules_NumericEqualFunction(int a1, double result, int a3)
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
    if ( Parser_NumberValueAsComparableDouble(previous[1], previous[2]) != Parser_NumberValueAsComparableDouble(current[1], current[2]) )
      return 0;
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  }
  return 1;
}
// 51A960: using guessed type int dword_51A960;
