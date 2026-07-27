/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004C1BB0) --------------------------------------------------------
signed int  Rules_FindMultiImportConflict(int theModule)
{
  int Enum; // edi
  int theConstruct; // ebp
  int theCItem; // eax
  int *conflictPortItem; // ebx
  int conflictConstructName; // ebx
  int Name; // eax
  int count; // [esp+0h] [ebp-24h] BYREF
  int targetModule; // [esp+4h] [ebp-20h]
  int thePCItem; // [esp+8h] [ebp-1Ch]

  targetModule = theModule;
  Module_BeginEnum();
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      thePCItem = g_Module_PortConstructList;
      if ( g_Module_PortConstructList )
        break;
LABEL_7:
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_8;
    }
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      theConstruct = Rules_FindConstructByName();
      if ( (*(int (**)(void))(uintptr_t)(theConstruct + 28))() )
        break;
LABEL_6:
      thePCItem = *(_DWORD *)(uintptr_t)(thePCItem + 8);
      if ( !thePCItem )
        goto LABEL_7;
    }
    while ( 1 )
    {
      Module_SetCurrent(targetModule);
      theCItem = (*(int (**)(void))(uintptr_t)(theConstruct + 16))();
      Rules_FindImportExportConstruct((char *)(uintptr_t)*(_DWORD *)(uintptr_t)thePCItem, &count, (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(theCItem + 16), 0, 0);
      if ( count > 1 )
        break;
      Module_SetCurrent(Enum);
      if ( !(*(int (**)(void))(uintptr_t)(theConstruct + 28))() )
        goto LABEL_6;
    }
    conflictPortItem = (int *)(uintptr_t)thePCItem;
    (*(void (**)(void))(uintptr_t)(theConstruct + 16))();
    conflictConstructName = *conflictPortItem;
    Name = Module_GetName(targetModule);
    Lexer_WarnImpliedTemplate((int)(intptr_t)aDefmodule_7, Name, conflictConstructName);
    Module_EndEnum();
    return 1;
  }
  else
  {
LABEL_8:
    Module_EndEnum();
    return 0;
  }
}
// 51B368: using guessed type int dword_51B368;

//----- (004C1CB0) --------------------------------------------------------
signed int  Rules_ReportConstructNotExported(int moduleName, char *constructName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  char *v8; // edx
  char *v9; // eax
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx

  Rules_PrintErrorID((int)(intptr_t)aModulpsr, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aModule, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], moduleName, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDoesNotExport, v5);
  if ( v6 )
  {
    if ( constructName )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThe_1, v6);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v12, v12);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_50AC58, v13);
      v9 = g_IO_LogicalNameTable_WError[0];
      v8 = constructName;
      goto LABEL_5;
    }
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAny, v6);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v7, v7);
    v8 = aConstructs;
  }
  else
  {
    v8 = aAnyConstructs;
  }
  v9 = g_IO_LogicalNameTable_WError[0];
LABEL_5:
  Output_Write((int)(intptr_t)v9, (int)(intptr_t)v8, v6);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__30, v10);
}
// 4C1CD4: variable 'v3' is possibly undefined
// 4C1CE0: variable 'v4' is possibly undefined
// 4C1CEF: variable 'v5' is possibly undefined
// 4C1CF6: variable 'v6' is possibly undefined
// 4C1D12: variable 'v7' is possibly undefined
// 4C1D30: variable 'v10' is possibly undefined
// 4C1D56: variable 'v12' is possibly undefined
// 4C1D65: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C1D80) --------------------------------------------------------
int  Rules_FindImportExportConflict(char *constructName, int matchModule, _BYTE *findName)
{
  int result; // eax
  int Enum; // esi
  int v6 CLASH95_UNUSED; // ecx
  _DWORD count[6]; // [esp+0h] [ebp-18h] BYREF

  count[1] = matchModule;
  result = Rules_ValidPortConstructItem(constructName);
  if ( result )
  {
    if ( Rules_FindModuleSeparator(findName) )
    {
      return 0;
    }
    else
    {
      result = Module_FindItemByName((int)(intptr_t)constructName);
      if ( result )
      {
        if ( *(_DWORD *)((uintptr_t)(unsigned int)result + 24) )
        {
          Module_BeginEnum();
          Enum = Module_NextEnum(0);
          if ( Enum )
          {
            while ( 1 )
            {
              Module_SetCurrent(Enum);
              Rules_FindImportExportConstruct(constructName, count, findName, 1, matchModule);
              if ( count[0] > 1 )
                break;
              Enum = Module_NextEnum(Enum);
              if ( !Enum )
                goto LABEL_11;
            }
            Module_EndEnum();
            return 1;
          }
          else
          {
LABEL_11:
            Module_EndEnum();
            return 0;
          }
        }
        else
        {
          return 0;
        }
      }
    }
  }
  return result;
}
// 4C1DFA: variable 'v6' is possibly undefined

//----- (004C1E40) --------------------------------------------------------
int  Rules_ParseAssertTemplate(int readSource, int theToken, int endType, int *error, int constantsOnly, int theDeftemplate)
{
  int *slotPtr; // esi
  int tempSlot; // eax
  signed int newSlotExpr; // eax
  int newSlot; // ecx
  int v11; // eax
  int v13; // ecx
  int v14; // edx
  signed int v16; // [esp+4h] [ebp-1Ch]
  signed int i; // [esp+Ch] [ebp-14h]
  int firstSlot; // [esp+10h] [ebp-10h]

  firstSlot = 0;
  for ( i = 0; ; i = v16 )
  {
    slotPtr = Rules_ParseSlotLabel(readSource, theToken, error, theDeftemplate, endType);
    if ( !slotPtr )
      break;
    tempSlot = firstSlot;
    if ( firstSlot )
    {
      while ( *(_DWORD *)(uintptr_t)(tempSlot + 2) != *slotPtr )
      {
        tempSlot = *(_DWORD *)(uintptr_t)(tempSlot + 10);
        if ( !tempSlot )
          goto LABEL_6;
      }
      Rules_ReportAlreadyParsed(*slotPtr, *(_DWORD *)(uintptr_t)(*slotPtr + 16));
      v11 = firstSlot;
      *error = 1;
      goto LABEL_12;
    }
LABEL_6:
    newSlotExpr = Rules_ParseAssertSlotValues(readSource, theToken, error, slotPtr, constantsOnly);
    v16 = newSlotExpr;
    if ( *error )
    {
      v11 = firstSlot;
LABEL_12:
      AST_Free(v11);
      return 0;
    }
    if ( !Lexer_CheckValueList((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(newSlotExpr + 6), (int)(intptr_t)aAssert_0) )
    {
      *error = 1;
      AST_Free(firstSlot);
      v11 = v13;
      goto LABEL_12;
    }
    if ( i )
      *(_DWORD *)(uintptr_t)(i + 10) = newSlot;
    else
      firstSlot = newSlot;
  }
  if ( *error )
  {
    AST_Free(firstSlot);
    return 0;
  }
  else
  {
    Rules_ReorderAssertSlotValues((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDeftemplate + 20), firstSlot, error);
    AST_Free(firstSlot);
    return v14;
  }
}
// 4C1ECD: variable 'v10' is possibly undefined
// 4C1F17: variable 'v13' is possibly undefined
// 4C1F61: variable 'v14' is possibly undefined

//----- (004C1F70) --------------------------------------------------------
_DWORD * Rules_ParseSlotLabel(int readSource, int theToken, _DWORD *error, int theDeftemplate, int endType)
{
  _DWORD *result; // eax
  int v8; // ecx
  _DWORD *v9; // ecx
  _DWORD *v10; // ecx
  _DWORD position[4]; // [esp+0h] [ebp-10h] BYREF

  *error = 0;
  Parser_NextToken(readSource, theToken);
  if ( *(_DWORD *)(uintptr_t)theToken == endType )
    return (_DWORD *)(uintptr_t)(endType ^ *(_DWORD *)(uintptr_t)theToken);
  IO_OutNewline();
  IO_OutWriteToken(asc_50AD10);
  IO_OutWriteToken((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theToken + 8));
  if ( *(_DWORD *)(uintptr_t)theToken == 100 && (Parser_NextToken(readSource, theToken), *(_DWORD *)(uintptr_t)theToken == 2) )
  {
    result = Lexer_FindTemplateSlot(theDeftemplate, *(_DWORD *)(uintptr_t)(theToken + 4), position);
    if ( !result )
    {
      Rules_ReportInvalidSlotError(v8, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theDeftemplate + 16));
      *v10 = 1;
      return 0;
    }
  }
  else
  {
    Parser_ReportSyntaxError();
    *v9 = 1;
    return 0;
  }
  return result;
}
// 4C1FE9: variable 'v9' is possibly undefined
// 4C2006: variable 'v8' is possibly undefined
// 4C200B: variable 'v10' is possibly undefined

//----- (004C2020) --------------------------------------------------------
signed int  Rules_ParseAssertSlotValues(int readSource, int theToken, int *error, int *slotPtr, int constantsOnly)
{
  int newField; // eax
  signed int result; // eax
  bool isMultifield; // zf
  int v11; // ecx
  int v12; // ecx
  int firstField; // eax
  int errorFlag; // ecx
  unsigned int tokenType; // ebx
  int nextField; // eax
  unsigned int nextTokenType; // ebx
  int v18; // ecx
  int printError; // [esp+0h] [ebp-1Ch] BYREF
  int valueList; // [esp+4h] [ebp-18h]
  int *theSlot; // [esp+8h] [ebp-14h]
  int lastField; // [esp+Ch] [ebp-10h]

  theSlot = slotPtr;
  if ( (slotPtr[1] & 1) == 0 )
  {
    IO_OutWriteToken(asc_50AD10);
    newField = Rules_ParseAssertArgument(readSource, (unsigned int *)(uintptr_t)(unsigned int)theToken, error, 101, constantsOnly, &printError);
    if ( *error )
    {
LABEL_3:
      if ( printError )
        Parser_ReportSyntaxError();
      return 0;
    }
    if ( !newField )
    {
      *error = 1;
      Rules_ReportSingleFieldSlotCardError();
      return 0;
    }
    if ( *(_WORD *)(uintptr_t)newField == 10 )
      isMultifield = *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(newField + 2) + 8) == 109;
    else
      isMultifield = *(_WORD *)(uintptr_t)newField == 16;
    if ( isMultifield )
    {
      *error = 1;
      Rules_ReportSingleFieldSlotCardError();
      AST_Free(v12);
      return 0;
    }
    Parser_NextToken(readSource, theToken);
LABEL_11:
    if ( *(_DWORD *)(uintptr_t)theToken == 101 )
    {
      result = AST_NewNode(2, *theSlot);
      *(_DWORD *)(uintptr_t)(result + 6) = v18;
    }
    else
    {
      Rules_ReportSingleFieldSlotCardError();
      *error = 1;
      AST_Free(v11);
      return 0;
    }
    return result;
  }
  firstField = Rules_ParseAssertArgument(readSource, (unsigned int *)(uintptr_t)(unsigned int)theToken, error, 101, constantsOnly, &printError);
  errorFlag = *error;
  valueList = firstField;
  if ( errorFlag )
    goto LABEL_3;
  tokenType = *(_DWORD *)(uintptr_t)theToken;
  lastField = firstField;
  if ( tokenType == 101 )
    goto LABEL_11;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50AD10);
    IO_OutWriteToken((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theToken + 8));
    nextField = Rules_ParseAssertArgument(readSource, (unsigned int *)(uintptr_t)(unsigned int)theToken, error, 101, constantsOnly, &printError);
    if ( *error )
      break;
    *(_DWORD *)(uintptr_t)(lastField + 10) = nextField;
    nextTokenType = *(_DWORD *)(uintptr_t)theToken;
    lastField = nextField;
    if ( nextTokenType == 101 )
      goto LABEL_11;
  }
  if ( printError )
    Parser_ReportSyntaxError();
  AST_Free(valueList);
  return 0;
}
// 4C20C5: variable 'v11' is possibly undefined
// 4C2110: variable 'v12' is possibly undefined
// 4C21D4: variable 'v18' is possibly undefined

//----- (004C21E0) --------------------------------------------------------
int  Rules_ReorderAssertSlotValues(_DWORD *slotList, int firstSlot, _DWORD *error)
{
  _DWORD *slotPtr; // ecx
  signed int lastValue; // edi
  signed int newValue; // eax
  int currentSlot; // ecx
  int firstValue; // [esp+0h] [ebp-14h]

  slotPtr = slotList;
  lastValue = 0;
  firstValue = 0;
  if ( !slotList )
    return firstValue;
  while ( 1 )
  {
    newValue = Rules_GetSlotAssertValues(slotPtr, firstSlot, (int)(intptr_t)slotPtr, error);
    if ( *error )
      break;
    if ( newValue )
    {
      if ( lastValue )
        *(_DWORD *)(uintptr_t)(lastValue + 10) = newValue;
      else
        firstValue = newValue;
      lastValue = newValue;
    }
    slotPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentSlot + 16);
    if ( !slotPtr )
      return firstValue;
  }
  AST_Free(firstValue);
  return 0;
}
// 4C2218: variable 'v7' is possibly undefined

//----- (004C2240) --------------------------------------------------------
signed int  Rules_GetSlotAssertValues(_DWORD *slotPtr, int firstSlot, int a3, _DWORD *error)
{
  int slotItem; // eax
  int slotDesc; // ecx
  char slotFlags; // ah
  signed int defaultExpr; // eax
  signed int newArgument; // ebx
  int multifieldMarker; // eax
  signed int multifieldExpr; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  _DWORD theValueBuffer[8]; // [esp-20h] [ebp-20h] BYREF

  theValueBuffer[7] = a3;
  slotItem = Rules_FindAssertSlotItem(slotPtr, firstSlot);
  if ( slotItem )
  {
    newArgument = *(_DWORD *)(uintptr_t)(slotItem + 6);
    *(_DWORD *)(uintptr_t)(slotItem + 6) = 0;
  }
  else
  {
    slotFlags = *(_BYTE *)(uintptr_t)(slotDesc + 4);
    if ( (slotFlags & 2) != 0 )
    {
      Rules_PrintErrorID((int)(intptr_t)aTmpltrhs, 1, 1);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSlot_1, v12);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v13 + 16), v13);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aRequiresAValue, v14);
      *error = 1;
      return 0;
    }
    if ( (slotFlags & 4) != 0 || (slotFlags & 8) != 0 )
    {
      defaultExpr = AST_CloneNodeList(*(_DWORD *)(uintptr_t)(slotDesc + 12));
    }
    else
    {
      Rules_DeriveDefaultFromConstraints((char *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotDesc + 8), theValueBuffer, *(_DWORD *)(uintptr_t)(slotDesc + 4) & 1);
      defaultExpr = AST_BuildExpressionFromValue(theValueBuffer);
    }
    newArgument = defaultExpr;
  }
  if ( (*(_BYTE *)(uintptr_t)(slotDesc + 4) & 1) != 0 )
  {
    multifieldMarker = Rules_AddBitmapValue(g_Rules_SlotAssertBitmapScratch, 1);
    multifieldExpr = AST_NewNode(34, multifieldMarker);
    *(_DWORD *)(uintptr_t)(multifieldExpr + 6) = newArgument;
    return multifieldExpr;
  }
  return newArgument;
}
// 4C2252: variable 'v5' is possibly undefined
// 4C22DA: variable 'v12' is possibly undefined
// 4C22DF: variable 'v13' is possibly undefined
// 4C22F8: variable 'v14' is possibly undefined
// 50AD7C: using guessed type _BYTE byte_50AD7C[4];
// 51A614: using guessed type char *off_51A614[5];

//----- (004C2320) --------------------------------------------------------
int  Rules_FindAssertSlotItem(_DWORD *slotPtr, int listOfSlots)
{
  if ( !listOfSlots )
    return 0;
  while ( *(_DWORD *)(uintptr_t)(listOfSlots + 2) != *slotPtr )
  {
    listOfSlots = *(_DWORD *)(uintptr_t)(listOfSlots + 10);
    if ( !listOfSlots )
      return 0;
  }
  return listOfSlots;
}

//----- (004C2340) --------------------------------------------------------
signed int Rules_RegisterModifyDuplicateFunctions(void)
{
  Rules_RegisterHostFunctionNoRestrictions(aModify, 117, (int)(intptr_t)aModifycommand, (int)(intptr_t)Rules_ModifyCommand);
  Rules_RegisterHostFunctionNoRestrictions(aDuplicate, 117, (int)(intptr_t)aDuplicatecomma, (int)(intptr_t)Rules_DuplicateCommand);
  Rules_AddFunctionParser(aModify);
  Rules_AddFunctionParser(aDuplicate);
  Rules_SetFunctionSeqOverloadFlags(aModify, 0);
  return Rules_SetFunctionSeqOverloadFlags(aDuplicate, 0);
}

//----- (004C23C0) --------------------------------------------------------
_DWORD * Rules_ModifyCommand(int returnValue, double a2)
{
  return Rules_ModifyOrDuplicateFact(1, returnValue, a2);
}

//----- (004C23D0) --------------------------------------------------------
_DWORD * Rules_DuplicateCommand(int returnValue, double a2)
{
  return Rules_ModifyOrDuplicateFact(0, returnValue, a2);
}

//----- (004C23E0) --------------------------------------------------------
_DWORD * Rules_ModifyOrDuplicateFact(int retractIt, int returnValue, double a3)
{
  _DWORD *result; // eax
  int factNum; // edx
  _DWORD *i; // esi
  int theDeftemplate; // ebp
  _DWORD *v7; // eax
  int v8; // ecx
  int fieldIndex; // ebx
  int fieldCount; // edx
  _DWORD *oldField; // edx
  __int16 fieldType; // di
  int j; // ecx
  int position; // ebx
  char *newFactField; // edi
  int valueExpr; // edx
  int v17; // ecx
  int copyIndex; // ebx
  _DWORD *newField; // edx
  _DWORD *copiedMultifield; // eax
  char *functionName; // eax
  int v22; // ecx
  _DWORD *slotPtr; // eax
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int resultFieldCount; // edx
  int computeResult; // [esp+0h] [ebp-4Ch] BYREF
  int resultType; // [esp+4h] [ebp-48h]
  _DWORD *evalValue; // [esp+8h] [ebp-44h]
  _BYTE tempBuffer[20]; // [esp+18h] [ebp-34h] BYREF
  _DWORD *newFact; // [esp+2Ch] [ebp-20h]
  int doRetract; // [esp+30h] [ebp-1Ch]
  int resultValue; // [esp+34h] [ebp-18h]

  doRetract = retractIt;
  resultValue = returnValue;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (_DWORD *)(uintptr_t)Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), &computeResult, *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), a3);
  if ( resultType != 1 )
  {
    if ( resultType == 6 )
    {
      i = evalValue;
      goto LABEL_6;
    }
    if ( doRetract )
      functionName = aModify;
    else
      functionName = aDuplicate;
LABEL_32:
    Rules_ReportSymbolTypeError(functionName, 1);
    return (_DWORD *)(uintptr_t)Lexer_ErrorRecover(1);
  }
  if ( (int)evalValue[4] < 0 )
  {
    if ( doRetract )
      functionName = aModify;
    else
      functionName = aDuplicate;
    goto LABEL_32;
  }
  result = (_DWORD *)(uintptr_t)Rules_GetNextFact(0);
  for ( i = result; i; i = (_DWORD *)(uintptr_t)i[9] )
  {
    if ( factNum == i[6] )
      break;
  }
  if ( !i )
  {
    sprintf_(tempBuffer, "f-%ld", factNum);
    return (_DWORD *)(uintptr_t)Rules_ReportCantFindItem(v22, (int)(intptr_t)tempBuffer);
  }
LABEL_6:
  theDeftemplate = i[4];
  if ( (*(_BYTE *)(uintptr_t)(theDeftemplate + 24) & 1) == 0 )
  {
    v7 = Module_AllocList(*(_DWORD *)((char *)i + 46));
    v7[4] = theDeftemplate;
    fieldIndex = 0;
    fieldCount = *(_DWORD *)((char *)i + 46);
    newFact = v7;
    if ( fieldCount > 0 )
    {
      oldField = i;
      do
      {
        fieldType = *((_WORD *)oldField + 27);
        *((_WORD *)v7 + 27) = fieldType;
        if ( fieldType == 4 )
          v7[14] = 0;
        else
          v7[14] = oldField[14];
        v7 = (_DWORD *)((char *)v7 + 6);
        ++fieldIndex;
        oldField = (_DWORD *)((char *)oldField + 6);
      }
      while ( fieldIndex < *(_DWORD *)((char *)i + 46) );
    }
    for ( j = *(_DWORD *)(uintptr_t)(v8 + 10); j; j = *(_DWORD *)(uintptr_t)(j + 10) )
    {
      if ( *(_WORD *)(uintptr_t)j == 1 )
      {
        position = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(j + 2) + 16);
      }
      else
      {
        slotPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDeftemplate + 20);
        position = 0;
        if ( !slotPtr )
        {
LABEL_46:
          Rules_ReportInvalidSlotError(j, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theDeftemplate + 16));
          Lexer_ErrorRecover(1);
          return Rules_ReturnFact(newFact);
        }
        while ( *slotPtr != *(_DWORD *)(uintptr_t)(j + 2) )
        {
          slotPtr = (_DWORD *)(uintptr_t)slotPtr[4];
          ++position;
          if ( !slotPtr )
            goto LABEL_46;
        }
      }
      newFactField = (char *)newFact + 6 * position;
      if ( *((_WORD *)newFactField + 27) == 4 )
      {
        Rules_StoreEvaluatedNodesAsMultifield(&computeResult, *(_DWORD *)(uintptr_t)(j + 6), 0, a3);
        Lexer_ErrorRecover(0);
      }
      else
      {
        valueExpr = *(_DWORD *)(uintptr_t)(j + 6);
        if ( !valueExpr || *(_DWORD *)(uintptr_t)(valueExpr + 10) )
        {
          Lexer_GetSlotByOrdinal(theDeftemplate, position);
          Rules_ReportMultifieldAssertIntoSingleSlotError(v24, theDeftemplate);
          return Rules_ReturnFact(newFact);
        }
        Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 6), &computeResult, j, a3);
        Lexer_ErrorRecover(0);
        if ( resultType == 4 )
        {
          Rules_ReturnFact(newFact);
          Lexer_GetSlotByOrdinal(theDeftemplate, position);
          return (_DWORD *)(uintptr_t)Rules_ReportMultifieldAssertIntoSingleSlotError(v25, theDeftemplate);
        }
      }
      *((_WORD *)newFactField + 27) = resultType;
      *((_DWORD *)newFactField + 14) = evalValue;
    }
    copyIndex = 0;
    if ( *(int *)((char *)i + 46) > 0 )
    {
      newField = newFact;
      do
      {
        if ( *((_WORD *)newField + 27) == 4 && !newField[14] )
        {
          copiedMultifield = Rules_CloneMultifield(*(_DWORD *)((char *)i + 6 * copyIndex + 56));
          newField[14] = copiedMultifield;
        }
        ++copyIndex;
        newField = (_DWORD *)((char *)newField + 6);
      }
      while ( copyIndex < *(_DWORD *)((char *)i + 46) );
    }
    if ( doRetract )
      Rules_RetractFact((int)(intptr_t)i, a3);
    result = Rules_AssertFactDriver(newFact, a3);
    if ( result )
    {
      *(_DWORD *)(uintptr_t)(resultValue + 12) = 0;
      v26 = resultValue;
      resultFieldCount = *(_DWORD *)((char *)result + 46);
      *(_DWORD *)(uintptr_t)(resultValue + 4) = 6;
      *(_DWORD *)(uintptr_t)(v26 + 8) = result;
      *(_DWORD *)(uintptr_t)(v26 + 16) = resultFieldCount - 1;
    }
  }
  return result;
}
// 4C243D: variable 'v4' is possibly undefined
// 4C2498: variable 'v8' is possibly undefined
// 4C2509: variable 'v17' is possibly undefined
// 4C2536: variable 'v19' is possibly undefined
// 4C25CD: variable 'v22' is possibly undefined
// 4C2688: variable 'v24' is possibly undefined
// 4C26B3: variable 'v25' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004C2710) --------------------------------------------------------
signed int  Lexer_ValidateMessageHandler(int top, int name, int theLHS)
{
  int functionArgs; // ecx
  signed int result; // eax
  int templateName; // eax
  int v7; // eax
  int v8; // ecx
  int theDeftemplate; // esi
  int tempArg; // ecx
  _DWORD *slotPtr; // eax
  int currentArg; // ecx
  int argList; // edx
  int v14; // ecx
  int v15; // edx
  signed int slotPosition; // eax
  int *indexValue; // eax
  int v18; // ecx
  _DWORD position[5]; // [esp+0h] [ebp-14h] BYREF

  functionArgs = *(_DWORD *)(uintptr_t)(top + 6);
  if ( *(_WORD *)(uintptr_t)functionArgs != 15 )
    return 1;
  templateName = Rules_FindTemplateForFactAddress(*(_DWORD *)(uintptr_t)(functionArgs + 2), theLHS);
  if ( !templateName )
    return 1;
  v7 = Symbol_LookupInModule((char **)(uintptr_t)g_DeftemplateConstructType, (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(templateName + 16), 0);
  theDeftemplate = v7;
  if ( !v7 )
    return 1;
  if ( (*(_BYTE *)(uintptr_t)(v7 + 24) & 1) != 0 )
    return 1;
  tempArg = *(_DWORD *)(uintptr_t)(v8 + 10);
  if ( !tempArg )
    return 1;
  while ( 1 )
  {
    slotPtr = Lexer_FindTemplateSlot(theDeftemplate, *(_DWORD *)(uintptr_t)(tempArg + 2), position);
    if ( !slotPtr )
    {
      Rules_ReportInvalidSlotError(currentArg, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)theDeftemplate + 16));
      return 0;
    }
    if ( (slotPtr[1] & 1) == 0 )
    {
      argList = *(_DWORD *)(uintptr_t)(currentArg + 6);
      if ( !argList
        || *(_DWORD *)(uintptr_t)(argList + 10)
        || *(_WORD *)(uintptr_t)argList == 16
        || *(_WORD *)(uintptr_t)argList == 10 && *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(argList + 2) + 8) == 109 )
      {
        break;
      }
    }
    result = Lexer_CheckValueList((int *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentArg + 6), name);
    if ( !result )
      return result;
    v15 = *(_DWORD *)(uintptr_t)(v14 + 2);
    *(_WORD *)(uintptr_t)v14 = 1;
    slotPosition = Lexer_FindSymbolIndex(theDeftemplate, v15);
    indexValue = Rules_AddIntegerValue(slotPosition - 1);
    *(_DWORD *)(uintptr_t)(v18 + 2) = indexValue;
    tempArg = *(_DWORD *)(uintptr_t)(v18 + 10);
    if ( !tempArg )
      return 1;
  }
  Rules_ReportSingleFieldSlotCardError();
  return 0;
}
// 4C2758: variable 'v8' is possibly undefined
// 4C277B: variable 'v12' is possibly undefined
// 4C27CA: variable 'v14' is possibly undefined
// 4C27DD: variable 'v18' is possibly undefined
// 54E650: using guessed type int dword_54E650;

//----- (004C2840) --------------------------------------------------------
int  Rules_FindTemplateForFactAddress(int factAddress, int theLHS)
{
  int thePattern; // ecx
  _DWORD *rightNode; // ecx
  _DWORD *templateNode; // edi

  thePattern = 0;
  if ( theLHS )
  {
    while ( factAddress != *(_DWORD *)(uintptr_t)(theLHS + 4) )
    {
      theLHS = *(_DWORD *)(uintptr_t)(theLHS + 68);
      if ( !theLHS )
        goto LABEL_4;
    }
    thePattern = theLHS;
  }
LABEL_4:
  if ( thePattern && (rightNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(thePattern + 64), *rightNode == 17) && (templateNode = (_DWORD *)(uintptr_t)rightNode[17]) != 0 && *templateNode == 2 && !templateNode[16] && !templateNode[17] )
    return templateNode[1];
  else
    return 0;
}

//----- (004C2890) --------------------------------------------------------
int  Rules_ParseModify(int top, int logicalName)
{
  return Lexer_ParseModifyOrDuplicate(top, logicalName, aModify);
}

//----- (004C28A0) --------------------------------------------------------
int  Rules_ParseDuplicate(int top, int logicalName)
{
  return Lexer_ParseModifyOrDuplicate(top, logicalName, aDuplicate);
}

//----- (004C28B0) --------------------------------------------------------
int  Lexer_ParseModifyOrDuplicate(int top, int logicalName, _BYTE *name)
{
  int v4; // ecx
  int nodeValue; // edx
  __int16 nodeType; // ax
  signed int v7; // eax
  int parsedSlot; // edx
  signed int newField; // eax
  int firstField; // ebp
  int lastField; // esi
  int theField; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  unsigned int theToken; // [esp+0h] [ebp-2Ch] BYREF
  int tokenValue; // [esp+4h] [ebp-28h]
  char *tokenPrintForm; // [esp+8h] [ebp-24h]
  int error; // [esp+Ch] [ebp-20h] BYREF
  int printError; // [esp+10h] [ebp-1Ch] BYREF
  int topNode; // [esp+14h] [ebp-18h]
  signed int nextAdd; // [esp+18h] [ebp-14h]

  topNode = top;
  error = 0;
  IO_OutWriteToken(asc_50ADC8);
  Parser_NextToken(logicalName, (int)(intptr_t)&theToken);
  if ( theToken == 15 || theToken == 13 )
  {
    nodeValue = tokenValue;
    nodeType = theToken;
  }
  else
  {
    if ( theToken != 1 )
    {
      Rules_ReportSymbolTypeError(name, 1);
      AST_Free(topNode);
      return 0;
    }
    if ( !Rules_IsEvaluatingTopLevelCommand() )
    {
      Rules_PrintErrorID((int)(intptr_t)aTmpltfun_0, v4, v4);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFactIndexesCan, v14);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)name, v15);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAsATopLevelCom, v16);
      AST_Free(topNode);
      return 0;
    }
    nodeValue = tokenValue;
    nodeType = v4;
  }
  v7 = AST_NewNode(nodeType, nodeValue);
  nextAdd = v7;
  *(_DWORD *)(uintptr_t)(v7 + 10) = 0;
  *(_DWORD *)(uintptr_t)(v7 + 6) = 0;
  *(_DWORD *)(uintptr_t)(topNode + 6) = nextAdd;
  Parser_NextToken(logicalName, (int)(intptr_t)&theToken);
  if ( theToken == 101 )
    return topNode;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50ADC8);
    IO_OutWriteToken(tokenPrintForm);
    if ( theToken != 100 )
      goto LABEL_15;
    Parser_NextToken(logicalName, (int)(intptr_t)&theToken);
    if ( theToken != 2 )
      goto LABEL_15;
    parsedSlot = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(topNode + 6) + 10);
    if ( parsedSlot )
      break;
LABEL_12:
    newField = AST_NewNode(2, tokenValue);
    firstField = 0;
    *(_DWORD *)(uintptr_t)(nextAdd + 10) = newField;
    nextAdd = newField;
    lastField = 0;
    if ( theToken != 101 )
    {
      while ( 1 )
      {
        IO_OutWriteToken(asc_50ADC8);
        theField = Rules_ParseAssertArgument(logicalName, &theToken, &error, 101, 0, &printError);
        if ( error )
          break;
        if ( lastField )
          *(_DWORD *)(uintptr_t)(lastField + 10) = theField;
        else
          firstField = theField;
        lastField = theField;
        if ( theToken == 101 )
          goto LABEL_25;
      }
      if ( printError )
LABEL_15:
        Parser_ReportSyntaxError();
      AST_Free(topNode);
      return 0;
    }
LABEL_25:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50AE50);
    *(_DWORD *)(uintptr_t)(nextAdd + 6) = firstField;
    Parser_NextToken(logicalName, (int)(intptr_t)&theToken);
    if ( theToken == 101 )
      return topNode;
  }
  while ( tokenValue != *(_DWORD *)(uintptr_t)(parsedSlot + 2) )
  {
    parsedSlot = *(_DWORD *)(uintptr_t)(parsedSlot + 10);
    if ( !parsedSlot )
      goto LABEL_12;
  }
  Rules_ReportAlreadyParsed(tokenValue, *(_DWORD *)(uintptr_t)(tokenValue + 16));
  AST_Free(topNode);
  return 0;
}
// 4C2AD1: conditional instruction was optimized away because %var_2C.4==65
// 4C2907: variable 'v4' is possibly undefined
// 4C2A3D: variable 'v14' is possibly undefined
// 4C2A49: variable 'v15' is possibly undefined
// 4C2A58: variable 'v16' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C2B40) --------------------------------------------------------
_BYTE * Rules_IntersectConstraints(int constraint1, int constraint2)
{
  int c2Changed; // ebx
  _BYTE *result; // eax
  int c1Changed; // ecx
  int theConstraint; // esi
  int rangeFlag; // ecx
  char *multifieldIntersection; // eax
  _BYTE *tmpConstraint; // eax
  bool symbolsAllowed; // al
  bool stringsAllowed; // al
  bool floatsAllowed; // al
  bool integersAllowed; // al
  bool instanceNamesAllowed; // al
  bool instanceAddressesAllowed; // al
  bool externalAddressesAllowed; // al
  bool multifieldsAllowed; // al
  bool v19; // al
  bool v20; // al
  bool v21; // al
  bool v22; // al
  bool v23; // al
  bool v24; // al

  c2Changed = 0;
  if ( !constraint1 && !constraint2 )
  {
    result = (_BYTE *)(uintptr_t)Rules_CreateLHSParseNode();
    result[1] |= 0x80u;
    return result;
  }
  if ( !constraint1 )
    return (_BYTE *)(uintptr_t)Rules_CloneLHSParseNode((int *)(uintptr_t)constraint2);
  if ( !constraint2 )
    return (_BYTE *)(uintptr_t)Rules_CloneLHSParseNode((int *)(uintptr_t)constraint1);
  result = (_BYTE *)(uintptr_t)Rules_CreateLHSParseNode();
  theConstraint = (int)(intptr_t)result;
  if ( *(_DWORD *)(uintptr_t)constraint1 << 16 >> 31 != *(_DWORD *)(uintptr_t)constraint2 << 16 >> 31 && *(_DWORD *)(uintptr_t)constraint1 << 15 >> 31 != *(_DWORD *)(uintptr_t)constraint2 << 15 >> 31 )
  {
    *result &= ~1u;
    return result;
  }
  if ( *(char *)(uintptr_t)(constraint1 + 1) >= 0 || *(char *)(uintptr_t)(constraint2 + 1) >= 0 )
    result[1] &= ~0x80u;
  else
    result[1] |= 0x80u;
  if ( (*(_BYTE *)(uintptr_t)(constraint1 + 2) & 1) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 2) & 1) != 0 )
    result[2] |= 1u;
  else
    result[2] &= ~1u;
  if ( (*(_BYTE *)(uintptr_t)constraint1 & 1) == 0 || (*(_BYTE *)(uintptr_t)constraint2 & 1) == 0 )
  {
    if ( (*(_BYTE *)(uintptr_t)constraint1 & 1) != 0 )
    {
      tmpConstraint = (_BYTE *)(uintptr_t)constraint1;
    }
    else
    {
      if ( (*(_BYTE *)(uintptr_t)constraint2 & 1) == 0 )
      {
LABEL_31:
        *(_BYTE *)(uintptr_t)theConstraint &= ~1u;
        symbolsAllowed = (*(_BYTE *)(uintptr_t)constraint1 & 2) != 0 && (*(_BYTE *)(uintptr_t)constraint2 & 2) != 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~2u;
        *(_DWORD *)(uintptr_t)theConstraint |= 2 * symbolsAllowed;
        stringsAllowed = (*(_BYTE *)(uintptr_t)constraint1 & 4) != 0 && (*(_BYTE *)(uintptr_t)constraint2 & 4) != 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~4u;
        *(_DWORD *)(uintptr_t)theConstraint |= 4 * stringsAllowed;
        floatsAllowed = (*(_BYTE *)(uintptr_t)constraint1 & 8) != 0 && (*(_BYTE *)(uintptr_t)constraint2 & 8) != 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~8u;
        *(_DWORD *)(uintptr_t)theConstraint |= 8 * floatsAllowed;
        integersAllowed = (*(_BYTE *)(uintptr_t)constraint1 & 0x10) != 0 && (*(_BYTE *)(uintptr_t)constraint2 & 0x10) != 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~0x10u;
        *(_DWORD *)(uintptr_t)theConstraint |= 16 * integersAllowed;
        instanceNamesAllowed = (*(_BYTE *)(uintptr_t)constraint1 & 0x20) != 0 && (*(_BYTE *)(uintptr_t)constraint2 & 0x20) != 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~0x20u;
        *(_DWORD *)(uintptr_t)theConstraint |= 32 * instanceNamesAllowed;
        instanceAddressesAllowed = (*(_BYTE *)(uintptr_t)constraint1 & 0x40) != 0 && (*(_BYTE *)(uintptr_t)constraint2 & 0x40) != 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~0x40u;
        *(_DWORD *)(uintptr_t)theConstraint |= instanceAddressesAllowed << 6;
        externalAddressesAllowed = *(char *)(uintptr_t)constraint1 < 0 && *(char *)(uintptr_t)constraint2 < 0;
        *(_BYTE *)(uintptr_t)theConstraint &= ~0x80u;
        *(_DWORD *)(uintptr_t)theConstraint |= externalAddressesAllowed << 7;
        multifieldsAllowed = *(char *)(uintptr_t)(constraint1 + 1) < 0 && *(char *)(uintptr_t)(constraint2 + 1) < 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x80u;
        *(_DWORD *)(uintptr_t)theConstraint |= multifieldsAllowed << 15;
        v19 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 1) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 1) != 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~1u;
        *(_DWORD *)(uintptr_t)theConstraint |= v19 << 8;
        if ( c1Changed )
          Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)constraint1, 1);
        if ( c2Changed )
          Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)constraint2, 1);
        goto LABEL_16;
      }
      tmpConstraint = (_BYTE *)(uintptr_t)constraint2;
      c2Changed = 1;
    }
    Rules_SetLHSParseNodeDefaultFlags(tmpConstraint, 0);
    goto LABEL_31;
  }
  *result |= 1u;
LABEL_16:
  if ( (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 2) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 2) != 0 )
  {
    *(_BYTE *)(uintptr_t)(theConstraint + 1) |= 2u;
  }
  else
  {
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~2u;
    v20 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 4) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 4) != 0;
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~4u;
    *(_DWORD *)(uintptr_t)theConstraint |= v20 << 10;
    v21 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 8) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 8) != 0;
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~8u;
    *(_DWORD *)(uintptr_t)theConstraint |= v21 << 11;
    v22 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 0x10) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 0x10) != 0;
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x10u;
    *(_DWORD *)(uintptr_t)theConstraint |= v22 << 12;
    v23 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 0x20) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 0x20) != 0;
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x20u;
    *(_DWORD *)(uintptr_t)theConstraint |= v23 << 13;
    v24 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 0x40) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 0x40) != 0;
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x40u;
    *(_DWORD *)(uintptr_t)theConstraint |= v24 << 14;
  }
  Rules_IntersectAllowedValueExpressions(constraint1, constraint2, theConstraint);
  Rules_IntersectNumericExpressions(constraint1, constraint2, rangeFlag, theConstraint);
  Rules_IntersectNumericExpressions(constraint1, constraint2, 0, theConstraint);
  Rules_UpdateRestrictionFlags(theConstraint);
  if ( *(char *)(uintptr_t)(theConstraint + 1) < 0 )
  {
    multifieldIntersection = (char *)Rules_IntersectConstraints(*(_DWORD *)(uintptr_t)(constraint1 + 26), *(_DWORD *)(uintptr_t)(constraint2 + 26));
    *(_DWORD *)(uintptr_t)(theConstraint + 26) = multifieldIntersection;
    if ( Rules_ConstraintIsUnmatchable(multifieldIntersection) )
      *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x80u;
  }
  return (_BYTE *)(uintptr_t)theConstraint;
}
// 4C2C23: variable 'v8' is possibly undefined
// 4C2E41: variable 'v6' is possibly undefined

//----- (004C2FB0) --------------------------------------------------------
int  Rules_IntersectAllowedValueExpressions(int constraint1, int constraint2, int newConstraint)
{
  __int16 *theList1; // esi
  __int16 *i; // edi
  signed int tmpExpr; // eax
  __int16 *j; // esi
  int result; // eax
  signed int tmpExpr2; // eax

  theList1 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint1 + 6);
  for ( i = 0; theList1; theList1 = *(__int16 **)(theList1 + 5) )
  {
    if ( Method_QueryRestrictionAllowsType(*theList1, *(_DWORD *)(theList1 + 1), constraint1) && Method_QueryRestrictionAllowsType(*theList1, *(_DWORD *)(theList1 + 1), constraint2) )
    {
      tmpExpr = AST_NewNode(*theList1, *(_DWORD *)(theList1 + 1));
      *(_DWORD *)(uintptr_t)(tmpExpr + 10) = i;
      i = (__int16 *)(uintptr_t)tmpExpr;
    }
  }
  for ( j = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint2 + 6); j; j = *(__int16 **)(j + 5) )
  {
    if ( !Rules_FindItemInExpression(*j, *(_DWORD *)(j + 1), i, 1)
      && Method_QueryRestrictionAllowsType(*j, *(_DWORD *)(j + 1), constraint1)
      && Method_QueryRestrictionAllowsType(*j, *(_DWORD *)(j + 1), constraint2) )
    {
      tmpExpr2 = AST_NewNode(*j, *(_DWORD *)(j + 1));
      *(_DWORD *)(uintptr_t)(tmpExpr2 + 10) = i;
      i = (__int16 *)(uintptr_t)tmpExpr2;
    }
  }
  result = newConstraint;
  *(_DWORD *)(uintptr_t)(newConstraint + 6) = i;
  return result;
}

//----- (004C3070) --------------------------------------------------------
int  Rules_IntersectNumericExpressions(int constraint1, int constraint2, int range, int newConstraint)
{
  __int16 *tmpmin1; // ebp
  __int16 *v5; // eax
  __int16 *tmpmin2; // esi
  __int16 *tmpmax2; // edi
  signed int min1VsMax2; // eax
  int minValue; // edx
  __int16 minType; // ax
  int maxValue; // edx
  __int16 maxType; // ax
  signed int theMaxNode; // eax
  int theMinNode; // ecx
  int result; // eax
  int v16; // edx
  int v17; // edx
  signed int max1VsMin2; // [esp+0h] [ebp-38h]
  int theMaxList; // [esp+10h] [ebp-28h]
  int theMinList; // [esp+14h] [ebp-24h]
  signed int minCompare; // [esp+18h] [ebp-20h]
  signed int maxCompare; // [esp+1Ch] [ebp-1Ch]
  signed int lastMax; // [esp+20h] [ebp-18h]
  int lastMin; // [esp+24h] [ebp-14h]
  __int16 *tmpmax1; // [esp+28h] [ebp-10h]

  lastMin = 0;
  lastMax = 0;
  theMinList = 0;
  theMaxList = 0;
  if ( range )
  {
    tmpmin1 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint1 + 10);
    v5 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint1 + 14);
  }
  else
  {
    tmpmin1 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint1 + 18);
    v5 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint1 + 22);
  }
  while ( 1 )
  {
    tmpmax1 = v5;
    if ( !tmpmin1 )
      break;
    if ( range )
    {
      tmpmin2 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint2 + 10);
      tmpmax2 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint2 + 14);
    }
    else
    {
      tmpmin2 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint2 + 18);
      tmpmax2 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(constraint2 + 22);
    }
    while ( tmpmin2 )
    {
      maxCompare = Rules_CompareBoundedCEValues(*tmpmax1, *(_DWORD *)(tmpmax1 + 1), *(_DWORD *)(tmpmax2 + 1), *tmpmax2);
      minCompare = Rules_CompareBoundedCEValues(*tmpmin1, *(_DWORD *)(tmpmin1 + 1), *(_DWORD *)(tmpmin2 + 1), *tmpmin2);
      max1VsMin2 = Rules_CompareBoundedCEValues(*tmpmax1, *(_DWORD *)(tmpmax1 + 1), *(_DWORD *)(tmpmin2 + 1), *tmpmin2);
      min1VsMax2 = Rules_CompareBoundedCEValues(*tmpmin1, *(_DWORD *)(tmpmin1 + 1), *(_DWORD *)(tmpmax2 + 1), *tmpmax2);
      if ( !max1VsMin2 || min1VsMax2 == 1 )
      {
        tmpmin2 = *(__int16 **)(tmpmin2 + 5);
        tmpmax2 = *(__int16 **)(tmpmax2 + 5);
      }
      else
      {
        if ( minCompare == 1 )
        {
          minValue = *(_DWORD *)(tmpmin1 + 1);
          minType = *tmpmin1;
        }
        else
        {
          minValue = *(_DWORD *)(tmpmin2 + 1);
          minType = *tmpmin2;
        }
        AST_NewNode(minType, minValue);
        if ( maxCompare )
        {
          maxValue = *(_DWORD *)(tmpmax2 + 1);
          maxType = *tmpmax2;
        }
        else
        {
          maxValue = *(_DWORD *)(tmpmax1 + 1);
          maxType = *tmpmax1;
        }
        theMaxNode = AST_NewNode(maxType, maxValue);
        if ( lastMin )
        {
          *(_DWORD *)(uintptr_t)(lastMin + 10) = theMinNode;
          *(_DWORD *)(uintptr_t)(lastMax + 10) = theMaxNode;
        }
        else
        {
          theMinList = theMinNode;
          theMaxList = theMaxNode;
        }
        lastMin = theMinNode;
        lastMax = theMaxNode;
        tmpmin2 = *(__int16 **)(tmpmin2 + 5);
        tmpmax2 = *(__int16 **)(tmpmax2 + 5);
      }
    }
    v5 = *(__int16 **)(tmpmax1 + 5);
    tmpmin1 = *(__int16 **)(tmpmin1 + 5);
  }
  if ( theMinList )
  {
    if ( range )
    {
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 10));
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 14));
      result = theMaxList;
      *(_DWORD *)(uintptr_t)(v16 + 10) = theMinList;
      *(_DWORD *)(uintptr_t)(v16 + 14) = theMaxList;
    }
    else
    {
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 18));
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 22));
      result = theMaxList;
      *(_DWORD *)(uintptr_t)(v17 + 18) = theMinList;
      *(_DWORD *)(uintptr_t)(v17 + 22) = theMaxList;
    }
  }
  else if ( range )
  {
    if ( (*(_BYTE *)(uintptr_t)newConstraint & 1) != 0 )
      Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)newConstraint, 0);
    result = newConstraint;
    *(_BYTE *)(uintptr_t)newConstraint &= 0xE7u;
  }
  else
  {
    Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)newConstraint, 1);
    result = newConstraint;
    *(_DWORD *)(uintptr_t)newConstraint &= 0xFFFE7FFE;
  }
  return result;
}
// 4C31A1: variable 'v14' is possibly undefined
// 4C3218: variable 'v16' is possibly undefined
// 4C3245: variable 'v17' is possibly undefined

//----- (004C32A0) --------------------------------------------------------
int  Rules_UpdateRestrictionFlags(int result)
{
  int theConstraint; // esi
  char symbolFound; // al
  char stringFound; // al
  char floatFound; // al
  char integerFound; // al
  char instanceNameFound; // al

  theConstraint = result;
  if ( (*(_BYTE *)(uintptr_t)(result + 1) & 2) != 0 && !*(_DWORD *)(uintptr_t)(result + 6) )
  {
    result = (int)(intptr_t)Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)result, 1);
    *(_BYTE *)(uintptr_t)theConstraint &= ~1u;
  }
  if ( (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 4) != 0 && (*(_BYTE *)(uintptr_t)theConstraint & 2) != 0 )
  {
    symbolFound = Rules_FindItemInExpression(2, 0, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraint + 6), 0);
    *(_BYTE *)(uintptr_t)theConstraint &= ~2u;
    result = 2 * (symbolFound & 1);
    *(_DWORD *)(uintptr_t)theConstraint |= result;
  }
  if ( (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 8) != 0 && (*(_BYTE *)(uintptr_t)theConstraint & 4) != 0 )
  {
    stringFound = Rules_FindItemInExpression(3, 0, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraint + 6), 0);
    *(_BYTE *)(uintptr_t)theConstraint &= ~4u;
    result = 4 * (stringFound & 1);
    *(_DWORD *)(uintptr_t)theConstraint |= result;
  }
  if ( (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 0x10) != 0 && (*(_BYTE *)(uintptr_t)theConstraint & 8) != 0 )
  {
    floatFound = Rules_FindItemInExpression(0, 0, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraint + 6), 0);
    *(_BYTE *)(uintptr_t)theConstraint &= ~8u;
    result = 8 * (floatFound & 1);
    *(_DWORD *)(uintptr_t)theConstraint |= result;
  }
  if ( (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 0x20) != 0 && (*(_BYTE *)(uintptr_t)theConstraint & 0x10) != 0 )
  {
    integerFound = Rules_FindItemInExpression(1, 0, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraint + 6), 0);
    *(_BYTE *)(uintptr_t)theConstraint &= ~0x10u;
    result = 16 * (integerFound & 1);
    *(_DWORD *)(uintptr_t)theConstraint |= result;
  }
  if ( (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 0x40) != 0 && (*(_BYTE *)(uintptr_t)theConstraint & 0x20) != 0 )
  {
    instanceNameFound = Rules_FindItemInExpression(8, 0, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theConstraint + 6), 0);
    *(_BYTE *)(uintptr_t)theConstraint &= ~0x20u;
    result = 32 * (instanceNameFound & 1);
    *(_DWORD *)(uintptr_t)theConstraint |= result;
  }
  return result;
}

//----- (004C33B0) --------------------------------------------------------
signed int  Rules_FindItemInExpression(int theType, int theValue, __int16 *theList, int useValue)
{
  if ( !theList )
    return 0;
  while ( *theList != theType || useValue && theValue != *(_DWORD *)(theList + 1) )
  {
    theList = *(__int16 **)(theList + 5);
    if ( !theList )
      return 0;
  }
  return 1;
}

//----- (004C33E0) --------------------------------------------------------
BOOL  Rules_RestrictionOnType(int theType, int theConstraint)
{
  char restrictionFlags; // bl
  BOOL result; // eax

  result = 0;
  if ( theConstraint )
  {
    restrictionFlags = *(_BYTE *)(uintptr_t)(theConstraint + 1);
    if ( (restrictionFlags & 2) != 0 || (restrictionFlags & 4) != 0 && theType == 2 )
      return 1;
    if ( (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 8) != 0 && theType == 3
      || (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 0x10) != 0 && !theType
      || (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 0x20) != 0 && theType == 1
      || (*(_BYTE *)(uintptr_t)(theConstraint + 1) & 0x40) != 0 && theType == 8 )
    {
      return 1;
    }
  }
  return result;
}
