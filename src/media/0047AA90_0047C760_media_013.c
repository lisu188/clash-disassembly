/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_LOCAL int InputBackend_ScaleHostMouseDeltaToRecoveredUnits (int render_state, int host_delta);

//----- (0047AA90) --------------------------------------------------------
signed int  Rules_ResetFacts(double a1)
{
  signed int result; // eax

  for ( g_Rules_NextFactIndex = 0; g_Rules_FactListHead; result = Rules_RetractFact(g_Rules_FactListHead, a1) )
    ;
  return result;
}
// 51A15C: using guessed type int dword_51A15C;
// 51A160: using guessed type int dword_51A160;

//----- (0047AAD0) --------------------------------------------------------
BOOL  Rules_ClearFacts(double a1)
{
  g_Rules_NextFactIndex = 0;
  while ( g_Rules_FactListHead )
    Rules_RetractFact(g_Rules_FactListHead, a1);
  return Rules_GetNextFact(0) == 0;
}
// 51A15C: using guessed type int dword_51A15C;
// 51A160: using guessed type int dword_51A160;

//----- (0047AB20) --------------------------------------------------------
int Rules_FindFactByIndex(void)
{
  int result; // eax
  int target_index; // ecx

  result = Rules_GetNextFact(0);
  if ( !result )
    return 0;
  while ( target_index != *(_DWORD *)(result + 24) )
  {
    result = Rules_GetNextFact(result);
    if ( !result )
      return 0;
  }
  return result;
}
// 47AB31: variable 'v1' is possibly undefined

//----- (0047AB50) --------------------------------------------------------
signed int Rules_RegisterFactCommands(void)
{
  Rules_RegisterHostFunction(aFacts_1, 118, (int)aFactscommand, (int)Rules_FactsCommand, (int)a4iu);
  Rules_RegisterHostFunctionNoRestrictions(aAssert, 117, (int)aAssertcommand, (int)Rules_AssertCommand);
  Rules_RegisterHostFunction(aRetract_0, 118, (int)aRetractcommand, (int)Rules_RetractCommand, (int)a1Z);
  Rules_RegisterHostFunction(aAssertString, 117, (int)aAssertstringfu, (int)Rules_AssertStringFunction, (int)a11s);
  Rules_RegisterHostFunction(aStrAssert, 117, (int)aAssertstringfu, (int)Rules_AssertStringFunction, (int)a11s);
  Rules_RegisterHostFunction(aGetFactDuplica, 98, (int)aGetfactduplica, (int)Rules_GetFactDuplicationCommand, (int)a00_1);
  Rules_RegisterHostFunction(aSetFactDuplica, 98, (int)aSetfactduplica, (int)Rules_SetFactDuplicationCommand, (int)a11);
  Rules_RegisterHostFunction(aSaveFacts, 98, (int)aSavefactscomma, (int)Rules_ParseSaveFactsCommand, (int)a1Wk);
  Rules_RegisterHostFunction(aLoadFacts, 98, (int)aLoadfactscomma, (int)Rules_ParseLoadFactsCommand, (int)a11k);
  Rules_RegisterHostFunction(aFactIndex, 108, (int)aFactindexfunct, (int)Rules_FactIndexFunction, (int)a11y);
  Rules_AddFunctionParser(aAssert);
  return Rules_SetFunctionSeqOverloadFlags(aAssert, 0);
}

//----- (0047ACA0) --------------------------------------------------------
_DWORD * Rules_AssertCommand(uintptr_t returnValue, uintptr_t a2, double eval_context)
{
  uintptr_t out; // eax
  uintptr_t expression; // ebx
  uintptr_t deftemplate_record; // edi
  int multifield_reorder_needed; // ebp
  uintptr_t slot_constraint; // ecx
  _DWORD *fact; // [esp+1Ch] [ebp-1Ch]
  char *slot_value; // esi
  _DWORD *result; // eax
  _DWORD parsed[6]; // [esp+0h] [ebp-38h] BYREF

  (void)a2;
  out = returnValue;
  *(_DWORD *)(out + 4) = 2;
  *(_DWORD *)(out + 8) = g_ClipsFalseSymbol;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6);
  deftemplate_record = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2);
  multifield_reorder_needed = 0;
  if ( (*(_BYTE *)(deftemplate_record + 24) & 1) != 0 )
  {
    fact = Module_AllocList(1);
    if ( !*(_DWORD *)(expression + 10) )
    {
      *((_WORD *)fact + 27) = 4;
      fact[14] = (int)(uintptr_t)Rules_CreateMultifield(0);
    }
    slot_constraint = 0;
  }
  else
  {
    fact = Module_AllocList(((unsigned int)*(_DWORD *)(deftemplate_record + 24) << 16) >> 19);
    slot_constraint = (uintptr_t)(unsigned int)*(_DWORD *)(deftemplate_record + 20);
  }
  fact[4] = (int)deftemplate_record;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  slot_value = (char *)fact + 54;
  while ( expression )
  {
    Parser_ParseForm((__int16 *)expression, parsed, (int)slot_constraint, eval_context);
    if ( slot_constraint && (*(_BYTE *)(slot_constraint + 4) & 1) == 0 && parsed[1] == 4 )
    {
      multifield_reorder_needed = 1;
      Rules_ReportMultifieldAssertIntoSingleSlotError((int)slot_constraint, (int)deftemplate_record);
      parsed[1] = 2;
      parsed[2] = g_ClipsFalseSymbol;
    }
    *(_WORD *)slot_value = parsed[1];
    *(_DWORD *)(slot_value + 2) = parsed[2];
    if ( slot_constraint )
      slot_constraint = (uintptr_t)(unsigned int)*(_DWORD *)(slot_constraint + 16);
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
    slot_value += 6;
  }
  if ( multifield_reorder_needed )
    return Rules_ReturnFact(fact);
  result = Rules_AssertFactDriver(fact, eval_context);
  if ( result )
  {
    *(_DWORD *)(out + 4) = 6;
    *(_DWORD *)(out + 8) = (int)(uintptr_t)result;
  }
  return result;
}
// 47AD18: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0047ADD0) --------------------------------------------------------
void  Rules_RetractCommand(int a1, int a2, double a3)
{
  __int16 *argExpr; // ecx
  int i; // esi
  int valueString; // ecx
  int fact; // eax
  int factIndex; // edx
  int curArg; // ecx
  int v9; // ecx
  int v10; // ecx
  int resultObj; // [esp-4h] [ebp-3Ch] BYREF
  int arg_type; // [esp+0h] [ebp-38h]
  int arg_value; // [esp+4h] [ebp-34h]
  _BYTE buffer[24]; // [esp+14h] [ebp-24h] BYREF
  int v15; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+30h] [ebp-8h]

  v16 = a2;
  v15 = a1;
  argExpr = *(__int16 **)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    while ( 1 )
    {
      Parser_ParseForm(argExpr, &resultObj, (int)argExpr, a3);
      if ( arg_type != 1 )
        break;
      if ( *(int *)(arg_value + 16) < 0 )
      {
        Parser_ReportError(i, (int)aFactAddressFac);
        return;
      }
      fact = Rules_FindFactByIndex();
      if ( !fact )
      {
        a3 = sprintf_(buffer, "f-%ld", factIndex);
        Rules_ReportCantFindItem(v9, (int)buffer);
        goto LABEL_6;
      }
LABEL_5:
      Rules_RetractFact(fact, a3);
LABEL_6:
      argExpr = *(__int16 **)(curArg + 10);
      ++i;
      if ( !argExpr )
        return;
    }
    if ( arg_type == 6 )
    {
      fact = arg_value;
      goto LABEL_5;
    }
    if ( arg_type == 2 && !strcmp_(valueString, asc_502790) )
    {
      Rules_RemoveAllFacts(a3);
      return;
    }
    Parser_ReportError(i, (int)aFactAddressFac);
    Lexer_ErrorRecover(1);
    argExpr = *(__int16 **)(v10 + 10);
  }
}
// 47AE16: variable 'v8' is possibly undefined
// 47AE44: variable 'v7' is possibly undefined
// 47AE55: variable 'v9' is possibly undefined
// 47AE72: variable 'v5' is possibly undefined
// 47AE9E: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (0047AED0) --------------------------------------------------------
int  Rules_SetFactDuplicationCommand(int a1, double a2)
{
  int old_flag; // esi
  int v4; // ecx
  int new_flag; // eax
  _DWORD v6[10]; // [esp-4h] [ebp-28h] BYREF

  v6[8] = a1;
  old_flag = Rules_GetFactDuplicationFlag();
  if ( Lexer_TokenExpect(1) == -1 )
    return v4;
  Rules_RtnUnknown(1, v6, a2);
  new_flag = 1;
  if ( v6[0] == 2 && v6[1] == g_ClipsFalseSymbol )
    new_flag = 0;
  Rules_SetFactDuplicationEnabled(new_flag);
  return old_flag;
}
// 47AEF6: variable 'v4' is possibly undefined
// 48AC80: using guessed type int __fastcall unknown_libname_8(int);
// 54DD70: using guessed type int dword_54DD70;

//----- (0047AF50) --------------------------------------------------------
int Rules_GetFactDuplicationCommand(void)
{
  int v0; // ecx

  Rules_GetFactDuplicationFlag();
  Lexer_TokenExpect(0);
  return v0;
}
// 47AF6B: variable 'v0' is possibly undefined

//----- (0047AF80) --------------------------------------------------------
int  Rules_FactIndexFunction(double a1)
{
  int result; // eax
  _DWORD v2[2]; // [esp-4h] [ebp-20h] BYREF
  int fact; // [esp+4h] [ebp-18h]

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    Rules_RtnUnknown(1, v2, a1);
    if ( v2[1] == 6 )
    {
      if ( *(char *)(fact + 29) >= 0 )
        return Rules_GetFactIndex(fact);
      else
        return -1;
    }
    else
    {
      Parser_ReportError(1, (int)aFactAddress_0);
      return -1;
    }
  }
  return result;
}

//----- (0047B000) --------------------------------------------------------
signed int  Rules_FactsCommand(double frame)
{
  signed int result; // eax
  signed int v2; // esi
  int argumentCount; // ebx
  int v4; // ecx
  int start; // esi
  int arg_offset; // ebp
  int end; // ecx
  int moduleName; // ecx
  int v9; // ecx
  int theValue; // [esp+0h] [ebp-30h] BYREF
  int arg_type; // [esp+4h] [ebp-2Ch]
  int argValue; // [esp+8h] [ebp-28h]

  result = Lexer_TokenExpect(4);
  v2 = result;
  argumentCount = result;
  if ( result == -1 )
    return result;
  Module_GetCurrent();
  if ( !v2 )
    return Rules_PrintFactRange((int)g_IO_LogicalName_WDisplay, -1, -1, -1);
  Rules_RtnUnknown(1, &theValue, frame);
  if ( arg_type != 2 )
  {
    if ( arg_type != 1 || (start = *(_DWORD *)(argValue + 16), start < 0) )
    {
      Parser_ReportError(1, (int)aSymbolOrPositi);
      Rules_SetEvaluationErrorFlag(1);
      return Lexer_ErrorRecover(1);
    }
    arg_offset = 0;
    goto LABEL_8;
  }
  if ( !Module_FindByName(*(_BYTE **)(argValue + 16)) && strcmp_(moduleName, asc_502790) )
  {
    Lexer_ErrorRecover(1);
    return Rules_ReportCantFindItem(v9, *(_DWORD *)(argValue + 16));
  }
  result = Rules_ParsePositiveIntArg(2, argumentCount, moduleName, frame);
  start = result;
  if ( result != -2 )
  {
    arg_offset = 1;
LABEL_8:
    result = Rules_ParsePositiveIntArg(arg_offset + 2, argumentCount, v4, frame);
    if ( result != -2 )
    {
      result = Rules_ParsePositiveIntArg(arg_offset + 3, argumentCount, result, frame);
      if ( result != -2 )
        return Rules_PrintFactRange((int)g_IO_LogicalName_WDisplay, end, start, result);
    }
  }
  return result;
}
// 47B06F: variable 'v4' is possibly undefined
// 47B094: variable 'v7' is possibly undefined
// 47B0E3: variable 'v8' is possibly undefined
// 47B123: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A624: using guessed type char *off_51A624;

//----- (0047B1A0) --------------------------------------------------------
int  Rules_PrintFactRange(int logicalName, int end_index, int start_index, int max_count)
{
  int printed_count; // edi
  int v8; // edx
  int v9; // eax
  int fact; // eax
  int fact_cursor; // ecx
  int v12; // ecx
  int saved_module; // [esp+0h] [ebp-18h]
  int scan_all_modules; // [esp+8h] [ebp-10h]

  printed_count = 0;
  saved_module = Module_GetCurrent();
  scan_all_modules = 0;
  if ( v8 )
  {
    Module_SetCurrent(v8);
    v9 = 0;
LABEL_3:
    fact = Rules_GetNextFactInModule(v9);
    goto LABEL_4;
  }
  scan_all_modules = 1;
  fact = Rules_GetNextFact(0);
LABEL_4:
  while ( fact )
  {
    if ( Rules_GetEvaluationErrorFlag() == 1 )
      return Module_SetCurrent(saved_module);
    if ( end_index < *(_DWORD *)(fact_cursor + 24) && end_index != -1 || !max_count )
      break;
    if ( start_index <= *(_DWORD *)(fact_cursor + 24) )
    {
      Rules_PrintFactWithIndex(fact_cursor, fact_cursor);
      ++printed_count;
      Output_Write(logicalName, (int)asc_5027CC, v12);
      if ( max_count > 0 )
        --max_count;
    }
    if ( !scan_all_modules )
    {
      v9 = fact_cursor;
      goto LABEL_3;
    }
    fact = Rules_GetNextFact(fact_cursor);
  }
  Rules_PrintTally(logicalName, printed_count, (int)aFacts_1, (int)aFact);
  return Module_SetCurrent(saved_module);
}
// 47B1C2: variable 'v8' is possibly undefined
// 47B1EA: variable 'v11' is possibly undefined
// 47B215: variable 'v12' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047B270) --------------------------------------------------------
signed int  Rules_ParsePositiveIntArg(int arg_index, int max_args, int a3, double a4)
{
  signed int result; // eax
  _DWORD v6[9]; // [esp-8h] [ebp-24h] BYREF

  v6[7] = a3;
  if ( arg_index > max_args )
    return -1;
  if ( !Lexer_ParseValueList(arg_index, v6, 1, a4) )
    return -2;
  result = *(_DWORD *)(v6[2] + 16);
  if ( result < 0 )
  {
    Parser_ReportError(arg_index, (int)aPositiveNumber);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -2;
  }
  return result;
}

//----- (0047B2F0) --------------------------------------------------------
_DWORD * Rules_AssertStringFunction(int returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  int v5; // ecx
  _DWORD v6[10]; // [esp-8h] [ebp-28h] BYREF

  v6[8] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v6, 3, a3);
    if ( result )
    {
      result = Rules_Log(*(const char **)(v6[2] + 16), v5, a3);
      if ( result )
      {
        *(_DWORD *)(returnValue + 4) = 6;
        *(_DWORD *)(returnValue + 8) = result;
      }
    }
  }
  return result;
}
// 47B347: variable 'v5' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0047B370) --------------------------------------------------------
int  Rules_ParseSaveFactsCommand(double a1)
{
  int save_scope; // esi
  _DWORD *template_list; // edi
  int v3; // ecx
  int result; // eax
  int v5; // ecx
  const CHAR *filename; // ebp
  int v7; // ecx
  _DWORD v8[6]; // [esp+0h] [ebp-34h] BYREF
  int arg_count; // [esp+18h] [ebp-1Ch]

  save_scope = 1;
  template_list = 0;
  v3 = Lexer_TokenExpect(1);
  arg_count = v3;
  if ( v3 == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v3, a1);
  filename = (const CHAR *)result;
  if ( result )
  {
    if ( v5 > 1 )
    {
      result = Lexer_ParseValueList(2, v8, 2, a1);
      if ( !result )
        return result;
      if ( strcmp_(*(_DWORD *)(v8[2] + 16), aLocal) )
      {
        if ( strcmp_(v7, aVisible) )
        {
          Parser_ReportError(2, (int)aSymbolWithValu);
          return 0;
        }
        save_scope = 2;
      }
    }
    if ( arg_count > 2 )
      template_list = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
    result = Rules_SaveFactsToFile(filename, save_scope, template_list, a1);
    if ( result )
      return 1;
  }
  return result;
}
// 47B3B9: variable 'v5' is possibly undefined
// 47B422: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (0047B470) --------------------------------------------------------
signed int  Rules_ParseLoadFactsCommand(DWORD a1, double a2)
{
  int v2; // ecx
  signed int result; // eax
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, a2);
  if ( result )
  {
    result = Rules_LoadFactsFromFile((const CHAR *)result, v4, a1, a2);
    if ( result )
      return 1;
  }
  return result;
}
// 47B497: variable 'v2' is possibly undefined
// 47B4A0: variable 'v4' is possibly undefined

//----- (0047B4C0) --------------------------------------------------------
signed int  Rules_SaveFactsToFile(const CHAR *fileName, int saveScope, _DWORD *importList, double frame)
{
  int v5; // eax
  int v6; // ecx
  int file; // esi
  int v8; // ecx
  int v9; // ecx
  int i; // ebx
  int v12; // ecx
  int matchIndex; // eax
  _DWORD *matchScan; // edx
  int arrayCount; // [esp+0h] [ebp-30h] BYREF
  int errorFlag; // [esp+4h] [ebp-2Ch] BYREF
  int savedPreserveEscapedFlag; // [esp+8h] [ebp-28h]
  int savedAddressesToStringsFlag; // [esp+Ch] [ebp-24h]
  int savedInstanceAddressesFlag; // [esp+10h] [ebp-20h]
  int currentModule; // [esp+14h] [ebp-1Ch]
  int v21; // [esp+18h] [ebp-18h]
  _DWORD *deftemplateArray; // [esp+1Ch] [ebp-14h]

  v21 = saveScope;
  v5 = IO_FOpen(fileName, (unsigned __int8 *)aW_0, (int)fileName, (DWORD)importList);
  file = v5;
  if ( v5 )
  {
    IO_SetFastSaveFile(v5);
    savedPreserveEscapedFlag = g_Print_PreserveEscapedCharactersFlag;
    g_Print_PreserveEscapedCharactersFlag = 1;
    savedAddressesToStringsFlag = g_Print_AddressesToStringsFlag;
    g_Print_AddressesToStringsFlag = 1;
    savedInstanceAddressesFlag = g_Print_InstanceAddressesToNamesFlag;
    g_Print_InstanceAddressesToNamesFlag = 1;
    deftemplateArray = Rules_CollectFactsToArray(importList, v21, &errorFlag, &arrayCount, frame);
    if ( errorFlag )
    {
      g_Print_PreserveEscapedCharactersFlag = savedPreserveEscapedFlag;
      g_Print_AddressesToStringsFlag = savedAddressesToStringsFlag;
      g_Print_InstanceAddressesToNamesFlag = savedInstanceAddressesFlag;
      fclose_(v8);
      IO_SetFastSaveFile(0);
      return 0;
    }
    else
    {
      currentModule = Module_GetCurrent();
      for ( i = Rules_GetNextFactInModule(0); i; i = Rules_GetNextFactInModule(i) )
      {
        if ( v21 == 1 && currentModule != **(_DWORD **)(*(_DWORD *)(i + 16) + 8) )
          continue;
        if ( importList )
        {
          matchIndex = 0;
          if ( arrayCount <= 0 )
            continue;
          matchScan = deftemplateArray;
          while ( matchScan[2] != *(_DWORD *)(i + 16) )
          {
            ++matchIndex;
            matchScan += 6;
            if ( matchIndex >= arrayCount )
              goto LABEL_6;
          }
        }
        Rules_PrintFact(file, i);
        Output_Write(file, (int)asc_5027CC, v12);
LABEL_6:
        ;
      }
      g_Print_PreserveEscapedCharactersFlag = savedPreserveEscapedFlag;
      g_Print_AddressesToStringsFlag = savedAddressesToStringsFlag;
      g_Print_InstanceAddressesToNamesFlag = savedInstanceAddressesFlag;
      fclose_(v9);
      IO_SetFastSaveFile(0);
      if ( importList )
        Mem_SmallBlockRelease(deftemplateArray, 24 * arrayCount);
      return 1;
    }
  }
  else
  {
    Rules_OpenFileErrorMessage(v6, v6);
    return 0;
  }
}
// 47B599: variable 'v9' is possibly undefined
// 47B5D9: variable 'v6' is possibly undefined
// 47B605: variable 'v8' is possibly undefined
// 47B62F: variable 'v12' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A5F8: using guessed type int dword_51A5F8;
// 51A5FC: using guessed type int dword_51A5FC;
// 51A600: using guessed type int dword_51A600;

//----- (0047B670) --------------------------------------------------------
_DWORD * Rules_CollectFactsToArray(
        _DWORD *result,
        int saveScope,
        _DWORD *errorFlagPtr,
        int *countPtr,
        double frame)
{
  int listNode; // edi
  _DWORD *v7; // eax
  int v8; // ecx
  int entryCount; // ebx
  _DWORD *arrayEntry; // esi
  int v11; // eax
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // edx
  int tmpCnt; // [esp+0h] [ebp-28h] BYREF
  _DWORD *deftemplateArray; // [esp+4h] [ebp-24h]
  _DWORD *v19; // [esp+8h] [ebp-20h]
  int v20; // [esp+Ch] [ebp-1Ch]
  int exprIndex; // [esp+10h] [ebp-18h]
  int deftemplate; // [esp+14h] [ebp-14h]
  int writtenCount; // [esp+18h] [ebp-10h]

  listNode = (int)result;
  v20 = saveScope;
  v19 = errorFlagPtr;
  *errorFlagPtr = 0;
  if ( !result )
  {
    *countPtr = 0;
    return result;
  }
  *countPtr = 0;
  do
  {
    result = *(_DWORD **)((char *)result + 10);
    ++*countPtr;
  }
  while ( result );
  v7 = Mem_NewArray(24 * *countPtr);
  v8 = 0;
  deftemplateArray = v7;
  entryCount = *countPtr;
  writtenCount = 0;
  if ( entryCount <= 0 )
    return deftemplateArray;
  arrayEntry = v7;
  exprIndex = 3;
  while ( 1 )
  {
    Parser_ParseForm((__int16 *)listNode, arrayEntry, v8, frame);
    if ( g_ClipsEvaluationError )
    {
      *v19 = 1;
      Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
      return 0;
    }
    if ( arrayEntry[1] != 2 )
    {
      v13 = exprIndex;
      *v19 = 1;
      Parser_ReportError(v13, (int)aSymbol_1);
      Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
      return 0;
    }
    if ( v20 != 1 )
      break;
    deftemplate = Rules_FindDeftemplateByName(*(_BYTE **)(arrayEntry[2] + 16), 1);
    if ( !deftemplate )
    {
      v15 = exprIndex;
      *v19 = v14;
      Parser_ReportError(v15, (int)aLocalDeftempla);
      Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
      return 0;
    }
LABEL_11:
    arrayEntry += 6;
    v11 = deftemplate;
    v12 = writtenCount;
    *(arrayEntry - 5) = 35;
    *(arrayEntry - 4) = v11;
    writtenCount = v12 + 1;
    listNode = *(_DWORD *)(listNode + 10);
    v8 = *countPtr;
    ++exprIndex;
    if ( v12 + 1 >= v8 )
      return deftemplateArray;
  }
  if ( v20 != 2 )
    goto LABEL_11;
  deftemplate = Rules_FindImportExportConstruct(aDeftemplate_4, &tmpCnt, *(_BYTE **)(arrayEntry[2] + 16), 1, g_ClipsEvaluationError);
  if ( deftemplate )
    goto LABEL_11;
  v16 = exprIndex;
  *v19 = 1;
  Parser_ReportError(v16, (int)aVisibleDeftemp);
  Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
  return 0;
}
// 47B696: conditional instruction was optimized away because eax.4!=0
// 47B818: variable 'v14' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (0047B890) --------------------------------------------------------
BOOL  Rules_LoadFactsFromFile(const CHAR *fileName, int a2, DWORD a3, double a4)
{
  int v5; // eax
  int v6; // ecx
  int file; // ebx
  __int16 *parsedForm; // eax
  int v9; // ecx
  int v10; // ecx
  int v12; // [esp-18h] [ebp-34h] BYREF
  _DWORD v13[7]; // [esp+0h] [ebp-1Ch] BYREF

  v13[5] = a2;
  v5 = IO_FOpen(fileName, (unsigned __int8 *)aR_0, (int)fileName, a3);
  file = v5;
  if ( !v5 )
  {
    Rules_OpenFileErrorMessage(v6, v6);
    return 0;
  }
  IO_SetFastLoadFile(v5);
  v13[0] = 100;
  do
  {
    parsedForm = (__int16 *)Rules_ParseAssertFormFromFile(file, v13);
    v9 = (int)parsedForm;
    if ( parsedForm )
      Parser_ParseForm(parsedForm, &v12, (int)parsedForm, a4);
    else
      v13[0] = 102;
    AST_Free(v9);
  }
  while ( v13[0] != 102 );
  IO_SetFastLoadFile(0);
  fclose_(v10);
  return !g_ClipsEvaluationError;
}
// 47B8D3: variable 'v9' is possibly undefined
// 47B8E8: variable 'v10' is possibly undefined
// 47B907: variable 'v6' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A964: using guessed type int dword_51A964;

//----- (0047B930) --------------------------------------------------------
int  Rules_ParseAssertFormFromFile(int readSource, _DWORD *parseState)
{
  int **Symbol; // eax
  signed int assertNode; // esi
  int v7; // ecx
  int errorFlag[6]; // [esp+0h] [ebp-18h] BYREF

  errorFlag[0] = 0;
  Parser_NextToken(readSource, (int)parseState);
  if ( *parseState != 100 )
    return 0;
  Symbol = Rules_MakeSymbol(aAssert);
  assertNode = AST_NewNode(10, (int)Symbol);
  *(_DWORD *)(assertNode + 6) = Rules_ParseAssertRHSPattern(readSource, (int)parseState, 1, errorFlag, 0, 1, 101);
  if ( errorFlag[0] == 1 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionLoadFa, v7);
    Lexer_ErrorRecover(1);
  }
  else if ( !AST_TreeContainsSpecialTag(assertNode, 1) )
  {
    return assertNode;
  }
  AST_Free(assertNode);
  return 0;
}
// 47B9B8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047B9E0) --------------------------------------------------------
int  Rules_AssertParsedFact(int parseTree, int readSource, int a3)
{
  int v4; // edx
  _DWORD v6[3]; // [esp+0h] [ebp-1Ch] BYREF
  int v7[4]; // [esp+Ch] [ebp-10h] BYREF

  v7[2] = a3;
  AST_Free(parseTree);
  IO_OutWriteToken(asc_502890);
  Rules_IncrementIndentDepth(8);
  Rules_ParseAssertCommand(readSource, v6, 1, v7, 1, (int)aAssertCommand);
  Rules_DecrementIndentDepth(8);
  return v4;
}
// 47BA28: variable 'v4' is possibly undefined

//----- (0047BA31) --------------------------------------------------------
signed int  IO_AdvanceBufferCursor(int offset, int bufferState)
{
  int remaining; // edi
  int newPosition; // esi
  int newRemaining; // edi
  signed int result; // eax

  if ( offset > *(_DWORD *)(bufferState + 4) || offset < *(_DWORD *)(*(_DWORD *)(bufferState + 8) + 8) - *(_DWORD *)bufferState )
    return 1;
  remaining = *(_DWORD *)(bufferState + 4);
  newPosition = offset + *(_DWORD *)bufferState;
  *(_BYTE *)(bufferState + 12) &= ~0x10u;
  newRemaining = remaining - offset;
  *(_DWORD *)bufferState = newPosition;
  result = 0;
  *(_DWORD *)(bufferState + 4) = newRemaining;
  return result;
}

//----- (0047BA70) --------------------------------------------------------
int  IO_ResetBufferCursor(int result)
{
  int basePtr; // edx

  *(_BYTE *)(result + 12) &= ~0x10u;
  basePtr = *(_DWORD *)(*(_DWORD *)(result + 8) + 8);
  *(_DWORD *)(result + 4) = 0;
  *(_DWORD *)result = basePtr;
  return result;
}

//----- (0047BA86) --------------------------------------------------------
signed int  IO_SeekStreamGuarded(int stream, int offset, unsigned int whence, int a4)
{
  int fd_index;
  int seek_result;

  (void)a4;
  fd_index = *(_DWORD *)(stream + 16);
  g_CRT_FileHandleLockAcquireHook(fd_index);
  seek_result = Compat_StreamSeek(stream, offset, (int)whence);
  g_CRT_FileHandleLockReleaseHook(fd_index, seek_result);
  if ( seek_result == -1 )
    return -1;
  return 0;
}
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

//----- (0047BC10) --------------------------------------------------------
BOOL __stdcall InputBackend_StoreEnumeratedDevice(int deviceInstance, int directInput)
{
  return (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)directInput + 12))(directInput, deviceInstance + 4, &g_InputBackendTempJoystickDevice, 0) != 0;
}
// 54DD20: using guessed type int g_InputBackendTempJoystickDevice;

//----- (0047BC40) --------------------------------------------------------
InputBackendState * InputBackend_ResetState(InputBackendState *result)
{
  memset(result->keyboard_state, 0, sizeof(result->keyboard_state));
  result->direct_input = 0;
  result->keyboard_device = 0;
  result->mouse_device = 0;
  result->joystick_device = 0;
  result->mouse_delta_x = 0;
  result->mouse_delta_y = 0;
  result->joystick_axis_x = 0;
  result->joystick_axis_y = 0;
  result->mouse_device_ready = 0;
  result->keyboard_device_ready = 0;
  result->joystick_device_ready = 0;
  Platform_ResetInputFallbackState();
  return result;
}

//----- (0047BCA0) --------------------------------------------------------
InputBackendState * InputBackend_ReleaseDevices(InputBackendState *state)
{
  _DWORD *raw; // esi
  int keyboardDevice; // edx
  int mouseDevice; // ecx
  int joystickDevice; // esi

  raw = (_DWORD *)state;
  keyboardDevice = raw[1];
  if ( keyboardDevice )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)keyboardDevice + 8))(keyboardDevice);
    raw[1] = 0;
  }
  mouseDevice = raw[2];
  if ( mouseDevice )
  {
    (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)mouseDevice + 8))(mouseDevice, raw[2]);
    raw[2] = 0;
  }
  joystickDevice = raw[3];
  if ( joystickDevice )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)joystickDevice + 8))(raw[3]);
    raw[3] = 0;
  }
  if ( raw[0] )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)raw[0] + 8))(raw[0]);
    raw[0] = 0;
  }
  return state;
}

//----- (0047BD10) --------------------------------------------------------
signed int  InputBackend_Initialize(InputBackendState *state, int hInstance, int hwnd)
{
  _DWORD *raw; // esi
  _DWORD rangeProp[2]; // [esp+94h] [ebp-3Ch] BYREF
  int rangeObj; // [esp+9Ch] [ebp-34h]
  int rangeHow; // [esp+A0h] [ebp-30h]
  int rangeMin; // [esp+A4h] [ebp-2Ch]
  int rangeMax; // [esp+A8h] [ebp-28h]
  _DWORD deadzoneProp[2]; // [esp+ACh] [ebp-24h] BYREF
  int deadzoneObj; // [esp+B4h] [ebp-1Ch]
  int deadzoneHow; // [esp+B8h] [ebp-18h]
  int deadzoneValue; // [esp+BCh] [ebp-14h]

  raw = (_DWORD *)state;
  if ( DirectInputCreateA(hInstance, 768, raw, 0) )
    return 0;
  if ( !(*(int (__stdcall **)(_DWORD, void *, _DWORD *, _DWORD))(*(_DWORD *)raw[0] + 12))(raw[0], &g_InputBackendMouseDeviceGuid, raw + 2, 0) )
  {
    (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[2] + 44))(raw[2], g_InputBackendMouseDataFormat);
    (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[2] + 52))(raw[2], hwnd, 5);
    if ( (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[2] + 28))(raw[2]) )
      return 0;
    raw[77] = 1;
  }
  if ( (*(int (__stdcall **)(_DWORD, void *, _DWORD *, _DWORD))(*(_DWORD *)raw[0] + 12))(raw[0], &g_InputBackendKeyboardDeviceGuid, raw + 1, 0) )
    goto LABEL_9;
  (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[1] + 44))(raw[1], g_InputBackendKeyboardDataFormat);
  (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[1] + 52))(raw[1], hwnd, 6);
  if ( (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[1] + 28))(raw[1]) )
    return 0;
  raw[78] = 1;
LABEL_9:
  (*(void (__stdcall **)(_DWORD, int, BOOL (__stdcall *)(int, int), _DWORD, int))(*(_DWORD *)raw[0] + 16))(
    raw[0],
    4,
    InputBackend_StoreEnumeratedDevice,
    raw[0],
    1);
  if ( !g_InputBackendTempJoystickDevice )
    return 1;
  if ( (**(int (__stdcall ***)(int, void *, int))g_InputBackendTempJoystickDevice)(
         g_InputBackendTempJoystickDevice,
         &g_InputBackendJoystickInterfaceIid,
         (int)(raw + 3)) )
    return 0;
  if ( g_InputBackendTempJoystickDevice )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)g_InputBackendTempJoystickDevice + 8))(g_InputBackendTempJoystickDevice);
    g_InputBackendTempJoystickDevice = 0;
  }
  (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[3] + 44))(raw[3], g_InputBackendJoystickDataFormat);
  (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[3] + 52))(raw[3], hwnd, 6);
  rangeProp[0] = 24;
  rangeMin = -1000;
  rangeMax = 1000;
  rangeProp[1] = 16;
  rangeObj = 0;
  rangeHow = 1;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 4, rangeProp) )
    return 0;
  rangeObj = 4;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 4, rangeProp) )
    return 0;
  deadzoneValue = 1000;
  deadzoneProp[0] = 20;
  deadzoneProp[1] = 16;
  deadzoneObj = 0;
  deadzoneHow = 1;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 5, deadzoneProp) )
    return 0;
  deadzoneObj = 4;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 5, deadzoneProp)
    || (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[3] + 28))(raw[3]) )
  {
    return 0;
  }
  raw[79] = 1;
  return 1;
}
// 4E80F0: using guessed type int g_InputBackendMouseDataFormat[5];
// 4E9110: using guessed type int g_InputBackendKeyboardDataFormat[5];
// 4E93F0: using guessed type int g_InputBackendJoystickDataFormat[5];
// 4E9792: using guessed type int __stdcall DirectInputCreateA(_DWORD, _DWORD, _DWORD, _DWORD);
// 54DD20: using guessed type int g_InputBackendTempJoystickDevice;

//----- (0047BF30) --------------------------------------------------------
int  InputBackend_Acquire(InputBackendState *state)
{
  _DWORD *raw; // ebx

  raw = (_DWORD *)state;
  if ( raw[77] && raw[2] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[2] + 28))(raw[2]);
  if ( raw[78] && raw[1] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[1] + 28))(raw[1]);
  if ( raw[79] && raw[3] )
    return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 28))(raw[3]);
  return 0;
}

//----- (0047BF80) --------------------------------------------------------
int  InputBackend_Unacquire(InputBackendState *state)
{
  _DWORD *raw; // ebx

  raw = (_DWORD *)state;
  if ( raw[77] && raw[2] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[2] + 32))(raw[2]);
  if ( raw[78] && raw[1] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[1] + 32))(raw[1]);
  if ( raw[79] && raw[3] )
    return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 32))(raw[3]);
  return 0;
}

CLASH95_LOCAL int InputBackend_ScaleHostMouseDeltaToRecoveredUnits(int render_state, int host_delta)
{
  int sensitivity;
  int fixed_shift;
  int sign;
  unsigned int abs_delta;
  unsigned long long scaled_delta;

  if ( !render_state || !host_delta )
    return host_delta;
  sensitivity = *(_DWORD *)(render_state + 32);
  fixed_shift = *(unsigned __int8 *)(render_state + 1108);
  if ( sensitivity <= 0 || fixed_shift < 0 || fixed_shift >= 24 )
    return host_delta;
  sign = host_delta < 0 ? -1 : 1;
  abs_delta = (unsigned int)(host_delta < 0 ? -host_delta : host_delta);
  scaled_delta = ((unsigned long long)abs_delta << fixed_shift) + (unsigned int)(sensitivity / 2);
  return sign * (int)(scaled_delta / (unsigned int)sensitivity);
}

//----- (0047BFD0) --------------------------------------------------------
int  InputBackend_PollState(InputBackendState *state, int renderState, int a3)
{
  int result; // eax
  _DWORD *raw; // ebx
  _DWORD joystickState[12]; // [esp+24h] [ebp-6Ch] BYREF
  unsigned __int8 joystickButtonPrimary; // [esp+54h] [ebp-3Ch]
  unsigned __int8 joystickButtonSecondary; // [esp+55h] [ebp-3Bh]
  _DWORD mouseState[3]; // [esp+74h] [ebp-1Ch] BYREF
  unsigned __int8 mouseButtonPrimary; // [esp+80h] [ebp-10h]
  unsigned __int8 mouseButtonSecondary; // [esp+81h] [ebp-Fh]
  unsigned __int8 mouseButtonMiddle; // [esp+82h] [ebp-Eh]
  int renderStateLocal; // [esp+84h] [ebp-Ch]
  int v12; // [esp+88h] [ebp-8h]
  int fallback_mouse_delta_x;
  int fallback_mouse_delta_y;
  signed char fallback_mouse_primary;
  signed char fallback_mouse_secondary;
  signed char fallback_keyboard_state[256];
  int fallback_mouse_delta_is_host_pixels;

  v12 = a3;
  renderStateLocal = renderState;
  result = 0;
  raw = (_DWORD *)state;
  fallback_mouse_delta_x = 0;
  fallback_mouse_delta_y = 0;
  fallback_mouse_primary = 0;
  fallback_mouse_secondary = 0;
  fallback_mouse_delta_is_host_pixels = 0;
  memset(fallback_keyboard_state, 0, sizeof(fallback_keyboard_state));
  if ( !(raw[77] && raw[2]) || !(raw[78] && raw[1]) )
  {
    Platform_ReadInputFallbackState(
      &fallback_mouse_delta_x,
      &fallback_mouse_delta_y,
      &fallback_mouse_primary,
      &fallback_mouse_secondary,
      fallback_keyboard_state,
      sizeof(fallback_keyboard_state),
      &fallback_mouse_delta_is_host_pixels);
    if ( fallback_mouse_delta_is_host_pixels )
    {
      fallback_mouse_delta_x = InputBackend_ScaleHostMouseDeltaToRecoveredUnits(renderStateLocal, fallback_mouse_delta_x);
      fallback_mouse_delta_y = InputBackend_ScaleHostMouseDeltaToRecoveredUnits(renderStateLocal, fallback_mouse_delta_y);
    }
  }
  if ( raw[77] && raw[2] )
  {
    if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(**(_DWORD **)&raw[2] + 36))(raw[2], 16, mouseState) == -2147024866 )
      (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[2] + 28))(raw[2]);
    state->mouse_delta_x = mouseState[0];
    state->mouse_delta_y = mouseState[1];
    state->mouse_button_primary = mouseButtonPrimary;
    state->mouse_button_secondary = mouseButtonSecondary;
    state->mouse_button_middle = mouseButtonMiddle;
  }
  else
  {
    state->mouse_delta_x = fallback_mouse_delta_x;
    state->mouse_delta_y = fallback_mouse_delta_y;
    state->mouse_button_primary = fallback_mouse_primary;
    state->mouse_button_secondary = fallback_mouse_secondary;
    state->mouse_button_middle = 0;
  }
  if ( raw[78] && raw[1] )
  {
    result = (*(int (__stdcall **)(_DWORD, int, int))(**(_DWORD **)&raw[1] + 36))(raw[1], 256, (int)&state->keyboard_state[0]);
    if ( result == -2147024866 )
      result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)&raw[1] + 28))(raw[1]);
  }
  else
  {
    qmemcpy(&state->keyboard_state[0], fallback_keyboard_state, sizeof(fallback_keyboard_state));
  }
  if ( raw[79] && raw[3] )
  {
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 100))(raw[3]);
    if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(**(_DWORD **)&raw[3] + 36))(raw[3], 80, joystickState) == -2147024866 )
      (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 28))(raw[3]);
    state->joystick_axis_x = joystickState[0];
    state->joystick_axis_y = joystickState[1];
    state->joystick_button_primary = joystickButtonPrimary;
    result = joystickButtonSecondary;
    state->joystick_button_secondary = joystickButtonSecondary;
  }
  return result;
}

//----- (0047C200) --------------------------------------------------------
int Rules_FindConstructByName(void)
{
  _DWORD *current; // ecx
  int v1; // ecx

  current = (_DWORD *)g_Rules_ConstructTypeListHead;
  if ( !g_Rules_ConstructTypeListHead )
    return 0;
  while ( strcmp_(current, *current) )
  {
    current = *(_DWORD **)(v1 + 48);
    if ( !current )
      return 0;
  }
  return v1;
}
// 47C21C: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A194: using guessed type int dword_51A194;

//----- (0047C2B0) --------------------------------------------------------
signed int  Rules_Save(const CHAR *fileName, int a2, DWORD a3)
{
  signed int result; // eax
  int v4; // ecx
  int i; // edx
  int v6; // edx

  result = IO_FOpen(fileName, (unsigned __int8 *)aW_1, a2, a3);
  if ( result )
  {
    IO_SetFastSaveFile(result);
    for ( i = g_Rules_SaveFunctionListHead; i; i = *(_DWORD *)(v6 + 12) )
      (*(void (**)(void))(i + 4))();
    fclose_(v4);
    IO_SetFastSaveFile(0);
    return 1;
  }
  return result;
}
// 47C2D9: variable 'v6' is possibly undefined
// 47C2E2: variable 'v4' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A188: using guessed type int dword_51A188;

//----- (0047C340) --------------------------------------------------------
int Rules_GetWatchCompilations(void)
{
  return g_Rules_WatchCompilationsFlag;
}
// 51A190: using guessed type int dword_51A190;

//----- (0047C350) --------------------------------------------------------
int  Rules_SetLoadInProgress(int result)
{
  g_Rules_LoadInProgressFlag = result;
  return result;
}
// 51A18C: using guessed type int dword_51A18C;

//----- (0047C360) --------------------------------------------------------
int Rules_GetLoadInProgress(void)
{
  return g_Rules_LoadInProgressFlag;
}
// 51A18C: using guessed type int dword_51A18C;

//----- (0047C370) --------------------------------------------------------
int Rules_RegisterClearResetCommands(void)
{
  Rules_RegisterHostFunction(aClear, 118, (int)aClearcommand, (int)Rules_ClearCommand, (int)a00_13);
  Rules_RegisterHostFunction(aReset, 118, (int)aResetcommand, (int)Rules_ResetCommand, (int)a00_13);
  return Rules_AddWatchItem((int)aCompilations, 0, 30, (int)&g_Rules_WatchCompilationsFlag, 0, 0);
}
// 51A190: using guessed type int dword_51A190;

//----- (0047C3D0) --------------------------------------------------------
int Rules_ClearCommand(void)
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Rules_Clear();
  return result;
}

//----- (0047C3F0) --------------------------------------------------------
void Rules_ResetCommand(void)
{
  if ( Lexer_TokenExpect(0) != -1 )
    Rules_Reset();
}

//----- (0047C410) --------------------------------------------------------
void Rules_Reset(void)
{
  int resetNode; // edx
  int *mainModule; // eax

  if ( !g_Rules_ResetInProgressFlag )
  {
    g_Rules_ResetInProgressFlag = 1;
    if ( !g_ClipsCurrentEvaluationDepth )
      Rules_SetEvaluationErrorFlag(0);
    if ( !g_Rules_BeforeResetCallback || g_Rules_BeforeResetCallback() )
    {
      if ( g_Rules_ResetFunctionListHead )
      {
        resetNode = g_Rules_ResetFunctionListHead;
        do
        {
          if ( Rules_GetEvaluationErrorFlag() )
            break;
          ((void (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(resetNode + 4))();
          resetNode = *(_DWORD *)(resetNode + 12);
        }
        while ( resetNode );
      }
      mainModule = Module_FindByName(aMain);
      Module_SetCurrent((int)mainModule);
      if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
        Rules_RunPeriodicCleanup(1, 0);
      g_Rules_ResetInProgressFlag = 0;
    }
    else
    {
      g_Rules_ResetInProgressFlag = 0;
    }
  }
}
// 47C45A: variable 'v0' is possibly undefined
// 47C45D: variable 'v1' is possibly undefined
// 51A184: using guessed type int dword_51A184;
// 51A198: using guessed type int dword_51A198;
// 51A1A8: using guessed type int (*dword_51A1A8)(void);
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (0047C4E0) --------------------------------------------------------
signed int  Rules_AddResetFunction(int name, int priority, int callback)
{
  g_Rules_ResetFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_ResetFunctionListHead, priority);
  return 1;
}
// 51A198: using guessed type int dword_51A198;

//----- (0047C530) --------------------------------------------------------
signed int Rules_Clear(void)
{
  int i; // edx
  int (*clear_callback)(void); // eax
  signed int result; // eax

  IO_ActivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
  if ( Rules_ClearReady() )
  {
    g_Rules_ClearInProgressFlag = 1;
    for ( i = g_Rules_ClearFunctionListHead; i; i = *(_DWORD *)(i + 12) )
    {
      clear_callback = (int (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(i + 4);
      clear_callback();
    }
    result = IO_DeactivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      result = Rules_RunPeriodicCleanup(1, 0);
    g_Rules_ClearInProgressFlag = 0;
  }
  else
  {
    Rules_PrintErrorID((int)aConstrct, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSomeConstructs, 0);
    return IO_DeactivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
  }
  return result;
}
// 51A180: using guessed type int dword_51A180;
// 51A19C: using guessed type int dword_51A19C;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (0047C5E0) --------------------------------------------------------
int Rules_ClearReady(void)
{
  int item; // edx
  int result; // eax
  int (*query_callback)(void); // eax

  item = g_Rules_ClearReadyFunctionListHead;
  if ( !item )
    return 1;
  while ( 1 )
  {
    query_callback = (int (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(item + 4);
    result = query_callback();
    if ( !result )
      break;
    item = *(_DWORD *)(item + 12);
    if ( !item )
      return 1;
  }
  return result;
}
// 51A1A0: using guessed type int dword_51A1A0;

//----- (0047C610) --------------------------------------------------------
signed int  Rules_AddClearReadyFunction(int name, int priority, int callback)
{
  g_Rules_ClearReadyFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_ClearReadyFunctionListHead, priority);
  return 1;
}
// 51A1A0: using guessed type int dword_51A1A0;

//----- (0047C660) --------------------------------------------------------
signed int  Rules_AddClearFunction(int name, int priority, int callback)
{
  g_Rules_ClearFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_ClearFunctionListHead, priority);
  return 1;
}
// 51A19C: using guessed type int dword_51A19C;

//----- (0047C680) --------------------------------------------------------
BOOL Rules_RemoveClearFunction(int name)
{
  _DWORD v3[3]; // [esp+0h] [ebp-Ch] BYREF

  g_Rules_ClearFunctionListHead = Rules_RemoveNamedCallbackReturningHead(name, g_Rules_ClearFunctionListHead, v3);
  return v3[0] != 0;
}
// 51A19C: using guessed type int dword_51A19C;

//----- (0047C6B0) --------------------------------------------------------
int Rules_GetReentryGuardFlag(void)
{
  return g_Rules_ReentryGuardFlag;
}
// 51A1A4: using guessed type int dword_51A1A4;

//----- (0047C6C0) --------------------------------------------------------
int  Rules_SetReentryGuardFlag(int result)
{
  g_Rules_ReentryGuardFlag = result;
  return result;
}
// 51A1A4: using guessed type int dword_51A1A4;

//----- (0047C6D0) --------------------------------------------------------
_DWORD * Module_BuildNameListMultifield(_DWORD *multifield, int (*getNextFn)(void), int (*getNameFn)(void))
{
  signed int count; // ecx
  int v7; // eax
  int v8; // ecx
  _DWORD *fieldPtr; // ebx
  _DWORD *result; // eax
  char *name; // eax
  int v12; // ecx
  int v13; // ecx

  if ( ((int (__thiscall *)(_DWORD))getNextFn)(0) )
  {
    do
    {
      v7 = getNextFn();
      count = v8 + 1;
    }
    while ( v7 );
  }
  multifield[1] = 4;
  multifield[4] = count - 1;
  multifield[3] = 0;
  fieldPtr = Rules_CreateEphemeralMultifield(count);
  multifield[2] = fieldPtr;
  result = (_DWORD *)((int (__thiscall *)(int))getNextFn)(1);
  if ( result )
  {
    while ( g_ClipsHaltExecution != 1 )
    {
      *((_WORD *)fieldPtr + 7) = 2;
      fieldPtr = (_DWORD *)((char *)fieldPtr + 6);
      name = (char *)getNameFn();
      *(_DWORD *)((char *)fieldPtr + 10) = Str_Intern(name, v12);
      result = (_DWORD *)((int (__thiscall *)(int))getNextFn)(v13 + 1);
      if ( !result )
        return result;
    }
    return Rules_SetMultifieldErrorValue((int)multifield);
  }
  return result;
}
// 47C6E6: variable 'v8' is possibly undefined
// 47C6F0: variable 'v6' is possibly undefined
// 47C737: variable 'v12' is possibly undefined
// 47C741: variable 'v13' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (0047C760) --------------------------------------------------------
int  Rules_FreeConstructHeaderString(int *header, int a2)
{
  int result; // eax
  const char *ppForm; // edx

  result = Rules_DecrementSymbolCount(*header, a2);
  ppForm = (const char *)header[1];
  if ( ppForm )
  {
    result = Mem_SmallBlockFree((_DWORD *)header[1], strlen(ppForm) + 1);
    header[1] = 0;
  }
  return result;
}
