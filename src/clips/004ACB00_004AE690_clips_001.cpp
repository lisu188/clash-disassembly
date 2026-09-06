/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004ACB00) --------------------------------------------------------
int  Compiler_WriteHeaders(int fp)
{
  fwrite_(g_Bload_SignaturePtr, strlen((const char *)g_Bload_SignaturePtr) + 1, fp, 1);
  return fwrite_(g_Bload_VersionString, strlen(g_Bload_VersionString) + 1, fp, 1);
}
// 51AD20: using guessed type void *off_51AD20;
// 51AD24: using guessed type char *off_51AD24;

//----- (004ACB60) --------------------------------------------------------
void __fastcall Compiler_MarkAndEmit(int a1 CLASH95_UNUSED, int theInstance)
{
  unsigned int slotIndex; // ebp
  int slotOffset; // edi
  _DWORD *slotPtr; // esi
  int slotNameSymbol; // eax
  unsigned int fieldIndex; // ebx
  int i; // ecx
  int multifieldPtr; // eax

  g_ClipsBsaveInstanceDataSpace += 8;
  *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 28) + 12) |= 2u;
  *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theInstance + 44) + 12) |= 2u;
  slotIndex = 0;
  slotOffset = 0;
  g_ClipsBsaveInstanceDataSpace += 8 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 44) + 72) + 16;
  while ( slotIndex < *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 44) + 72) )
  {
    slotPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotOffset + *(_DWORD *)(uintptr_t)(theInstance + 72));
    slotNameSymbol = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*slotPtr + 8) + 12);
    *(_BYTE *)(uintptr_t)(slotNameSymbol + 12) |= 2u;
    if ( (*(_BYTE *)(uintptr_t)*slotPtr & 2) != 0 )
    {
      fieldIndex = 1;
      for ( i = 0; ; Compiler_MarkAtomicValueInUse(*(__int16 *)(uintptr_t)(i + 6 + multifieldPtr + 8), *(_DWORD *)(uintptr_t)(i + 6 + multifieldPtr + 10)) )
      {
        multifieldPtr = slotPtr[2];
        if ( fieldIndex > *(_DWORD *)(uintptr_t)(multifieldPtr + 6) )
          break;
        ++fieldIndex;
      }
    }
    else
    {
      Compiler_MarkAtomicValueInUse(slotPtr[1] << 24 >> 26, slotPtr[2]);
    }
    slotOffset += 4;
    ++slotIndex;
  }
  return;
}
// 4ACBBE: control flows out of bounds to 4ACA62
// 4ACBEF: variable 'i' is possibly undefined
// 54E6EC: using guessed type int dword_54E6EC;

//----- (004ACC40) --------------------------------------------------------
signed int * Compiler_MarkAtomicValueInUse(int type, int value)
{
  signed int *result; // eax

  result = (signed int *)(uintptr_t)value;
  g_ClipsBsaveInstanceDataSpace += 8;
  switch ( type )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
      *(_BYTE *)(uintptr_t)(value + 12) |= 2u;
      break;
    case 7:
      result = Instance_GetQualifiedName(value, type);
      *((_BYTE *)result + 12) |= 2u;
      break;
    default:
      return result;
  }
  return result;
}
// 54E6EC: using guessed type int dword_54E6EC;

//----- (004ACC70) --------------------------------------------------------
int  Compiler_WriteInstanceRecord(int fp, int theInstance)
{
  int slotOffset; // ebp
  int v5; // ecx
  unsigned int slotIndex; // esi
  int v7; // ecx
  int result; // eax
  int slot; // ebp
  int numFields; // eax
  unsigned int fieldIndex; // esi
  int fieldOffset; // ecx
  int v13; // ecx
  _DWORD *slotPtr; // eax
  int fieldCount; // eax
  int slotNameIndex; // [esp+0h] [ebp-34h] BYREF
  int slotValueCount; // [esp+4h] [ebp-30h]
  int symbolIndex; // [esp+8h] [ebp-2Ch] BYREF
  int totalValueCount; // [esp+Ch] [ebp-28h] BYREF
  int slotOffset2; // [esp+10h] [ebp-24h]
  unsigned int slotIndex2; // [esp+14h] [ebp-20h]
  int instance; // [esp+18h] [ebp-1Ch]
  unsigned int slotFieldCount; // [esp+1Ch] [ebp-18h]

  instance = theInstance;
  totalValueCount = 0;
  symbolIndex = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 28) + 12) << 16 >> 18;
  fwrite_(&symbolIndex, 4, fp, 1);
  symbolIndex = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(instance + 44) + 12) << 16 >> 18;
  slotOffset = 0;
  fwrite_(&symbolIndex, 4, fp, 1);
  v5 = fp;
  slotIndex = 0;
  fwrite_((const void *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 44) + 72), 4, v5, 1);
  while ( slotIndex < *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 44) + 72) )
  {
    slotPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 72) + slotOffset);
    slotNameIndex = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*slotPtr + 8) + 12) + 12) << 16 >> 18;
    if ( (*(_BYTE *)(uintptr_t)*slotPtr & 2) != 0 )
      fieldCount = *(_DWORD *)(uintptr_t)(slotPtr[2] + 6);
    else
      fieldCount = 1;
    slotValueCount = fieldCount;
    fwrite_(&slotNameIndex, 8, fp, 1);
    slotOffset += 4;
    ++slotIndex;
    totalValueCount += slotValueCount;
  }
  if ( totalValueCount )
    fwrite_(&totalValueCount, 4, fp, 1);
  slotIndex2 = 0;
  slotOffset2 = 0;
  while ( 1 )
  {
    result = *(_DWORD *)(uintptr_t)(instance + 44);
    if ( slotIndex2 >= *(_DWORD *)(uintptr_t)(result + 72) )
      break;
    slot = *(_DWORD *)(uintptr_t)(slotOffset2 + *(_DWORD *)(uintptr_t)(instance + 72));
    if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)slot & 2) != 0 )
      numFields = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slot + 8) + 6);
    else
      numFields = 1;
    LOBYTE(v7) = *(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)slot;
    slotFieldCount = numFields;
    if ( (v7 & 2) != 0 )
    {
      fieldIndex = 1;
      if ( numFields )
      {
        fieldOffset = 0;
        do
        {
          ++fieldIndex;
          Compiler_WriteAtomicValueRef(*(__int16 *)(uintptr_t)(fieldOffset + *(_DWORD *)(uintptr_t)(slot + 8) + 14), *(_DWORD *)(uintptr_t)(fieldOffset + *(_DWORD *)(uintptr_t)(slot + 8) + 16), fp, fieldOffset);
          fieldOffset = v13 + 6;
        }
        while ( fieldIndex <= slotFieldCount );
      }
    }
    else
    {
      Compiler_WriteAtomicValueRef(*(_DWORD *)(uintptr_t)(slot + 4) << 24 >> 26, *(_DWORD *)(uintptr_t)(slot + 8), fp, v7);
    }
    v7 = slotIndex2 + 1;
    slotOffset2 += 4;
    ++slotIndex2;
  }
  return result;
}
// 4ACD88: variable 'v13' is possibly undefined
// 4ACE3A: variable 'v7' is possibly undefined

//----- (004ACE80) --------------------------------------------------------
int  Compiler_WriteAtomicValueRef(int type, int value, int fp, int a4)
{
  signed int bucketBits; // eax
  int typeCode; // [esp+0h] [ebp-Ch] BYREF
  int valueIndex CLASH95_UNUSED; // [esp+4h] [ebp-8h]
  int v8 CLASH95_UNUSED; // [esp+8h] [ebp-4h]

  v8 = a4;
  typeCode = type;
  switch ( type )
  {
    case 0:
    case 1:
      bucketBits = *(_DWORD *)(uintptr_t)(value + 12);
      goto LABEL_3;
    case 2:
    case 3:
    case 8:
      bucketBits = *(_DWORD *)(uintptr_t)(value + 12);
      goto LABEL_3;
    case 7:
      typeCode = 8;
      bucketBits = Instance_GetQualifiedName(value, type)[3];
LABEL_3:
      valueIndex = (unsigned __int16)bucketBits >> 2;
      break;
    default:
      valueIndex = -1;
      break;
  }
  return fwrite_(&typeCode, 8, fp, 1);
}

//----- (004ACEE0) --------------------------------------------------------
signed int  Rules_ReadInstancesTextFile(
        const CHAR *fileName,
        int useMessageDispatch,
        int a3,
        DWORD a4,
        double a5)
{
  int instanceCount; // esi
  int instanceFile; // edi
  int **Symbol; // eax
  int readSource; // ebx
  _DWORD *v9; // ecx
  int savedUseMessageDispatch; // edi
  __int16 *v11; // ecx
  _DWORD *v12; // edx
  __int16 *v13; // ecx
  __int16 *v14; // ecx
  int v15; // ecx
  int v16; // edx
  _DWORD *v18; // ecx
  int savedFastLoadFile; // [esp+1Ch] [ebp-18h]

  instanceCount = 0;
  instanceFile = IO_FOpen(fileName, (unsigned __int8 *)aR_8, a3, a4);
  if ( instanceFile )
  {
    savedFastLoadFile = IO_GetFastLoadFile();
    IO_SetFastLoadFile(instanceFile);
    Symbol = Rules_MakeSymbol((_BYTE*)(aMakeInstance_1));
    AST_NewNode(10, (int)(intptr_t)Symbol);
    readSource = instanceFile;
    Parser_NextToken(instanceFile, (int)(intptr_t)&g_ParserCurrentTokenType);
    savedUseMessageDispatch = g_Instance_UseMessageDispatchForInit;
    g_Instance_UseMessageDispatchForInit = useMessageDispatch;
    if ( g_ParserCurrentTokenType != 102 )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( g_ParserCurrentTokenType != 100 )
        {
          Parser_ReportSyntaxError();
          g_ClipsMemFreeListTemp = (int)(intptr_t)v18;
          *v18 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
          fclose_((_DWORD)(uintptr_t)(v18));
          IO_SetFastLoadFile(savedFastLoadFile);
          Lexer_ErrorRecover(1);
          g_Instance_UseMessageDispatchForInit = savedUseMessageDispatch;
          return instanceCount;
        }
        if ( !Rules_ParseMakeInstanceNode((int)(intptr_t)v9, readSource) )
        {
          fclose_((_DWORD)(uintptr_t)(v11));
          IO_SetFastLoadFile(savedFastLoadFile);
          g_Instance_UseMessageDispatchForInit = savedUseMessageDispatch;
          Lexer_ErrorRecover(1);
          return instanceCount;
        }
        AST_InstallNodeChain(v11);
        Parser_ParseForm(v13, v12, (int)(intptr_t)v13, a5);
        AST_DeinstallNodeChain(v14);
        if ( !g_ClipsEvaluationError )
          ++instanceCount;
        AST_Free(*(_DWORD *)(uintptr_t)(v15 + 6));
        Parser_NextToken(readSource, v16);
        if ( g_ParserCurrentTokenType == 102 )
          break;
      }
    }
    g_ClipsMemFreeListTemp = (int)(intptr_t)v9;
    *v9 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    fclose_((_DWORD)(uintptr_t)(v9));
    IO_SetFastLoadFile(savedFastLoadFile);
    g_Instance_UseMessageDispatchForInit = savedUseMessageDispatch;
    return instanceCount;
  }
  else
  {
    Lexer_ErrorRecover(1);
    return -1;
  }
}
// 4ACF6E: variable 'v9' is possibly undefined
// 4ACF7F: variable 'v11' is possibly undefined
// 4ACF86: variable 'v13' is possibly undefined
// 4ACF86: variable 'v12' is possibly undefined
// 4ACF8D: variable 'v14' is possibly undefined
// 4ACF9C: variable 'v15' is possibly undefined
// 4ACFAB: variable 'v16' is possibly undefined
// 4AD01F: variable 'v18' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A284: using guessed type int dword_51A284;
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8FC: using guessed type int dword_54E8FC;

//----- (004AD090) --------------------------------------------------------
signed int __fastcall Rules_ReportInstanceFileProcessError(int functionName CLASH95_UNUSED, int fileName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aInsfile, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_1, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCouldNotComple, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], fileName, v6);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__18, v7);
}
// 4AD0B2: variable 'v3' is possibly undefined
// 4AD0BE: variable 'v4' is possibly undefined
// 4AD0CD: variable 'v5' is possibly undefined
// 4AD0D9: variable 'v6' is possibly undefined
// 4AD0E8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AD100) --------------------------------------------------------
signed int  Rules_ValidateBloadInstancesHeader(int fileName, int a2)
{
  int v4; // ecx
  int v5; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  _DWORD headerBuffer[10]; // [esp-24h] [ebp-28h] BYREF

  headerBuffer[8] = a2;
  Rules_BloadReadBlock((uintptr_t)headerBuffer, strlen((const char *)g_Bload_SignaturePtr) + 1);
  if ( !strcmp_(v4, (_DWORD)(uintptr_t)(g_Bload_SignaturePtr)) )
  {
    Rules_BloadReadBlock((uintptr_t)headerBuffer, strlen(g_Bload_VersionString) + 1);
    if ( !strcmp_(v5, (_DWORD)(uintptr_t)(g_Bload_VersionString)) )
    {
      return 1;
    }
    else
    {
      Rules_PrintErrorID((int)(intptr_t)aInsfile, 3, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], fileName, v9);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFileIsNotAComp, v10);
      return 0;
    }
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aInsfile, 2, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], fileName, v7);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFileIsNotABina, v8);
    return 0;
  }
}
// 4AD12C: variable 'v4' is possibly undefined
// 4AD157: variable 'v5' is possibly undefined
// 4AD186: variable 'v7' is possibly undefined
// 4AD195: variable 'v8' is possibly undefined
// 4AD1B6: variable 'v9' is possibly undefined
// 4AD1C5: variable 'v10' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51AD20: using guessed type void *off_51AD20;
// 51AD24: using guessed type char *off_51AD24;

//----- (004AD1E0) --------------------------------------------------------
signed int  Rules_BloadReadInstanceRecord(int instanceCount, double a2)
{
  int v2; // ecx
  int classNameSymbol; // ebp
  int v4; // ecx
  int *theDefclass; // eax
  int v6; // ecx
  _DWORD *newInstance; // ebp
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  _DWORD *slotValueCursor; // esi
  int *slotPtr; // edi
  int valueCount; // eax
  _DWORD slotValue[6]; // [esp+0h] [ebp-58h] BYREF
  unsigned int slotCount; // [esp+18h] [ebp-40h] BYREF
  int bloadIndex; // [esp+1Ch] [ebp-3Ch] BYREF
  _DWORD totalAtomCount[2]; // [esp+20h] [ebp-38h] BYREF
  _DWORD *bsaveSlotValues; // [esp+28h] [ebp-30h]
  int instanceName; // [esp+2Ch] [ebp-2Ch]
  _DWORD *slotValueAtoms; // [esp+30h] [ebp-28h]
  int slotOffset; // [esp+34h] [ebp-24h]
  int atomIndex; // [esp+38h] [ebp-20h]
  int slotIndex; // [esp+3Ch] [ebp-1Ch]

  Rules_BloadReadBufferedBytes((int)(intptr_t)&bloadIndex, 4u, instanceCount);
  instanceName = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * bloadIndex);
  Rules_BloadReadBufferedBytes((int)(intptr_t)&bloadIndex, 4u, v2);
  classNameSymbol = *(_DWORD *)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * bloadIndex);
  Rules_BloadReadBufferedBytes((int)(intptr_t)&slotCount, 4u, v4);
  theDefclass = Class_LookupInScope((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(classNameSymbol + 16));
  totalAtomCount[1] = (_DWORD)(uintptr_t)(theDefclass);
  if ( !theDefclass )
  {
    Class_ReportLookupError(v6, *(_DWORD *)(uintptr_t)(classNameSymbol + 16));
    return 0;
  }
  if ( slotCount != theDefclass[18] || (newInstance = Instance_BuildInstance(instanceName, (int)(intptr_t)theDefclass, 0, a2)) == 0 )
  {
    Rules_ReportBloadInstanceError(instanceName);
    return 0;
  }
  if ( !slotCount )
    return 1;
  bsaveSlotValues = Mem_SmallBlockAlloc(8 * slotCount);
  Rules_BloadReadBufferedBytes((int)(intptr_t)bsaveSlotValues, 8 * slotCount, v8);
  Rules_BloadReadBufferedBytes((int)(intptr_t)totalAtomCount, 4u, v9);
  if ( totalAtomCount[0] )
  {
    slotValueAtoms = Mem_NewArray(8 * totalAtomCount[0]);
    Rules_BloadReadBufferedBytes((int)(intptr_t)slotValueAtoms, 8 * totalAtomCount[0], v10);
  }
  slotIndex = 0;
  atomIndex = 0;
  if ( !slotCount )
  {
LABEL_12:
    Mem_SmallBlockFree(bsaveSlotValues, 8 * slotCount);
    if ( totalAtomCount[0] )
      Mem_SmallBlockRelease(slotValueAtoms, 8 * totalAtomCount[0]);
    return 1;
  }
  slotValueCursor = bsaveSlotValues;
  slotOffset = 0;
  while ( 1 )
  {
    slotPtr = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotOffset + newInstance[18]);
    if ( *(_DWORD *)(uintptr_t)(4 * *slotValueCursor + g_ClipsBloadSymbolPointerArray) != *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*slotPtr + 8) + 12) )
      break;
    Rules_BloadBuildSlotValue(slotValue, &slotValueAtoms[2 * atomIndex], (int)(intptr_t)aBloadInstances, slotValueCursor[1]);
    if ( !Instance_PutSlotValue(newInstance, slotPtr, slotValue, a2) )
      break;
    valueCount = slotValueCursor[1];
    slotValueCursor += 2;
    atomIndex += valueCount;
    slotOffset += 4;
    if ( ++slotIndex >= slotCount )
      goto LABEL_12;
  }
  Rules_ReportBloadInstanceError(instanceName);
  Instance_DeleteInstance((int)(intptr_t)newInstance, a2);
  Mem_SmallBlockFree(bsaveSlotValues, 8 * slotCount);
  Mem_SmallBlockRelease(slotValueAtoms, 8 * totalAtomCount[0]);
  return 0;
}
// 4AD211: variable 'v2' is possibly undefined
// 4AD22B: variable 'v4' is possibly undefined
// 4AD291: variable 'v8' is possibly undefined
// 4AD29F: variable 'v9' is possibly undefined
// 4AD2C7: variable 'v10' is possibly undefined
// 4AD3BE: variable 'v6' is possibly undefined
// 54E674: using guessed type int dword_54E674;

//----- (004AD430) --------------------------------------------------------
signed int  Rules_ReportBloadInstanceError(int instanceName)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  Rules_PrintErrorID((int)(intptr_t)aInsfile, 4, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunctionBloadI, v2);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(instanceName + 16), v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOfClass_0, v4);
  return Class_PrintName(v5, 1);
}
// 4AD452: variable 'v2' is possibly undefined
// 4AD45F: variable 'v3' is possibly undefined
// 4AD473: variable 'v4' is possibly undefined
// 4AD47F: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AD490) --------------------------------------------------------
void ** Rules_BloadBuildSlotValue(_DWORD *returnValue, _DWORD *bsaveValues, int functionName, signed int valueCount)
{
  _DWORD *multifield; // eax
  _DWORD *v7; // edx
  _DWORD *fieldCursor; // ebx
  int fieldOffset; // ecx
  _DWORD *endPtr; // ebp
  void **result; // eax
  int v12; // edx

  if ( valueCount )
  {
    if ( valueCount == 1 )
    {
      returnValue[1] = *bsaveValues;
      result = Rules_BloadLookupAtomByIndex(bsaveValues, functionName);
      returnValue[2] = (_DWORD)(uintptr_t)(result);
    }
    else
    {
      returnValue[1] = 4;
      multifield = Rules_CreateEphemeralMultifield(valueCount);
      returnValue[3] = 0;
      returnValue[2] = (_DWORD)(uintptr_t)(multifield);
      returnValue[4] = valueCount - 1;
      fieldCursor = v7 + 2;
      fieldOffset = 0;
      endPtr = &v7[2 * valueCount - 2];
      do
      {
        *(_WORD *)(uintptr_t)(returnValue[2] + fieldOffset + 14) = *((_WORD *)fieldCursor - 4);
        result = Rules_BloadLookupAtomByIndex(v7, fieldOffset + 6);
        fieldCursor += 2;
        v7 = (_DWORD *)(uintptr_t)(v12 + 8);
        *(_DWORD *)(uintptr_t)(fieldOffset + returnValue[2] + 10) = (_DWORD)(uintptr_t)(result);
      }
      while ( v7 <= endPtr );
    }
  }
  else
  {
    returnValue[1] = 4;
    result = (void **)Rules_CreateEphemeralMultifield(0);
    returnValue[4] = -1;
    returnValue[2] = (_DWORD)(uintptr_t)(result);
    returnValue[3] = 0;
  }
  return result;
}
// 4AD4CC: conditional instruction was optimized away because ebx.4>=2u
// 4AD4D5: variable 'v7' is possibly undefined
// 4AD4E3: variable 'v9' is possibly undefined
// 4AD4FE: variable 'v12' is possibly undefined

//----- (004AD570) --------------------------------------------------------
void ** Rules_BloadLookupAtomByIndex(_DWORD *bsaveValue, int routineName)
{
  void **result; // eax

  switch ( *bsaveValue )
  {
    case 0:
      result = *(void ***)(uintptr_t)(g_Clips_FloatConstantTable + 4 * bsaveValue[1]);
      break;
    case 1:
      result = *(void ***)(uintptr_t)(g_Clips_IntegerConstantTable + 4 * bsaveValue[1]);
      break;
    case 2:
    case 3:
    case 8:
      result = *(void ***)(uintptr_t)(g_ClipsBloadSymbolPointerArray + 4 * bsaveValue[1]);
      break;
    case 5:
      result = 0;
      break;
    case 6:
      result = &g_Rules_DummyFactPtr;
      break;
    default:
      Rules_ReportSystemError(routineName, 1);
      IO_RunRouterExitCallbacks(2);
      result = 0;
      break;
  }
  return result;
}
// 51A114: using guessed type void *off_51A114;
// 54E670: using guessed type int dword_54E670;
// 54E674: using guessed type int dword_54E674;
// 54E678: using guessed type int dword_54E678;

//----- (004AD5D0) --------------------------------------------------------
unsigned int  Rules_BloadReadBufferedBytes(int dataBuffer, unsigned int bufferSize, int module)
{
  unsigned int bytesAvailable; // esi
  unsigned int result; // eax
  char curByte; // dl
  unsigned int bytesCopied; // eax
  int destCursor; // edx
  char copyByte; // bl
  unsigned int bytesRemaining; // eax
  unsigned int i; // eax
  char bufferByte; // dl

  if ( g_ClipsBloadReadBuffer )
  {
    while ( 1 )
    {
      bytesAvailable = g_Clips_BloadBufferSize - g_BloadReadBufferOffset;
      if ( bufferSize <= g_Clips_BloadBufferSize - g_BloadReadBufferOffset )
        break;
      if ( g_BloadReadBufferOffset < (unsigned int)g_Clips_BloadBufferSize )
      {
        bytesCopied = 0;
        if ( bytesAvailable )
        {
          destCursor = dataBuffer;
          do
          {
            ++destCursor;
            copyByte = *(_BYTE *)(uintptr_t)(g_ClipsBloadReadBuffer + bytesCopied + g_BloadReadBufferOffset);
            ++bytesCopied;
            *(_BYTE *)(uintptr_t)(destCursor - 1) = copyByte;
          }
          while ( bytesCopied < bytesAvailable );
        }
        bufferSize -= bytesAvailable;
        dataBuffer += bytesAvailable;
      }
      Rules_BloadReleaseReadBuffer();
      if ( !g_ClipsBloadReadBuffer )
        goto LABEL_13;
    }
    for ( result = 0; result < bufferSize; *(_BYTE *)(uintptr_t)(dataBuffer - 1) = curByte )
    {
      ++dataBuffer;
      curByte = *(_BYTE *)(uintptr_t)(result + g_BloadReadBufferOffset + g_ClipsBloadReadBuffer);
      ++result;
    }
    g_BloadReadBufferOffset += bufferSize;
    if ( g_BloadReadBufferOffset == g_Clips_BloadBufferSize )
      return Rules_BloadReleaseReadBuffer();
  }
  else
  {
LABEL_13:
    bytesRemaining = g_ClipsBsaveInstanceDataSpace - g_Rules_BloadBytesConsumed;
    if ( bufferSize <= 0x2800 )
    {
      if ( bytesRemaining >= 0x2800 )
        g_Clips_BloadBufferSize = 10240;
      else
        g_Clips_BloadBufferSize = g_ClipsBsaveInstanceDataSpace - g_Rules_BloadBytesConsumed;
    }
    else
    {
      g_Clips_BloadBufferSize = bufferSize;
      if ( bufferSize > bytesRemaining )
      {
        Rules_ReportSystemError(module, 2);
        IO_RunRouterExitCallbacks(2);
      }
    }
    g_ClipsBloadReadBuffer = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)g_Clips_BloadBufferSize);
    Rules_BloadReadBlock(g_ClipsBloadReadBuffer, g_Clips_BloadBufferSize);
    for ( i = 0; i < bufferSize; *(_BYTE *)(uintptr_t)(dataBuffer - 1) = bufferByte )
    {
      ++dataBuffer;
      bufferByte = *(_BYTE *)(uintptr_t)(g_ClipsBloadReadBuffer + i++);
    }
    result = g_Clips_BloadBufferSize;
    g_BloadReadBufferOffset = bufferSize;
    g_Rules_BloadBytesConsumed += g_Clips_BloadBufferSize;
  }
  return result;
}
// 4AD6B0: variable 'a3' is possibly undefined
// 51AD28: using guessed type int dword_51AD28;
// 51AD2C: using guessed type int dword_51AD2C;
// 51AD30: using guessed type int dword_51AD30;
// 54E6EC: using guessed type int dword_54E6EC;
// 54E6F0: using guessed type int dword_54E6F0;

//----- (004AD740) --------------------------------------------------------
signed int Rules_BloadReleaseReadBuffer(void)
{
  signed int result; // eax
  int v1; // ecx

  if ( g_Clips_BloadBufferSize )
  {
    result = Mem_ReleasePoolBlock(g_ClipsBloadReadBuffer, g_Clips_BloadBufferSize);
    g_ClipsBloadReadBuffer = v1;
    g_Clips_BloadBufferSize = v1;
  }
  return result;
}
// 4AD75A: variable 'v1' is possibly undefined
// 51AD28: using guessed type int dword_51AD28;
// 51AD2C: using guessed type int dword_51AD2C;

//----- (004AD770) --------------------------------------------------------
signed int Rules_RegisterMultifieldSlotCommands(void)
{
  Rules_RegisterHostFunction(aDirectMvReplac, 98, (int)(intptr_t)aDirectmvreplac, (int)(intptr_t)Rules_DirectSlotReplaceCommand, (int)(intptr_t)a4Wii);
  Rules_RegisterHostFunction(aDirectMvInsert, 98, (int)(intptr_t)aDirectmvinsert, (int)(intptr_t)Rules_DirectSlotInsertCommand, (int)(intptr_t)a3Wi);
  Rules_RegisterHostFunction(aDirectMvDelete, 98, (int)(intptr_t)aDirectmvdelete, (int)(intptr_t)Rules_DirectSlotDeleteCommand, (int)(intptr_t)a33iw);
  Rules_RegisterHostFunction(aMvSlotReplace, 117, (int)(intptr_t)aMvslotreplacec, (int)(intptr_t)Rules_MvSlotReplaceCommand, (int)(intptr_t)a5Uewii);
  Rules_RegisterHostFunction(aMvSlotInsert, 117, (int)(intptr_t)aMvslotinsertco, (int)(intptr_t)Rules_MvSlotInsertCommand, (int)(intptr_t)a4Uewi);
  Rules_RegisterHostFunction(aMvSlotDelete, 117, (int)(intptr_t)aMvslotdeleteco, (int)(intptr_t)Rules_MvSlotDeleteCommand, (int)(intptr_t)a44iew);
  Rules_RegisterHostFunction(aSlotDirectRepl, 98, (int)(intptr_t)aDirectmvreplac, (int)(intptr_t)Rules_DirectSlotReplaceCommand, (int)(intptr_t)a4Wii);
  Rules_RegisterHostFunction(aSlotDirectInse, 98, (int)(intptr_t)aDirectmvinsert, (int)(intptr_t)Rules_DirectSlotInsertCommand, (int)(intptr_t)a3Wi);
  Rules_RegisterHostFunction(aSlotDirectDele, 98, (int)(intptr_t)aDirectmvdelete, (int)(intptr_t)Rules_DirectSlotDeleteCommand, (int)(intptr_t)a33iw);
  Rules_RegisterHostFunction(aSlotReplace, 117, (int)(intptr_t)aMvslotreplacec, (int)(intptr_t)Rules_MvSlotReplaceCommand, (int)(intptr_t)a5Uewii);
  Rules_RegisterHostFunction(aSlotInsert, 117, (int)(intptr_t)aMvslotinsertco, (int)(intptr_t)Rules_MvSlotInsertCommand, (int)(intptr_t)a4Uewi);
  return Rules_RegisterHostFunction(aSlotDelete, 117, (int)(intptr_t)aMvslotdeleteco, (int)(intptr_t)Rules_MvSlotDeleteCommand, (int)(intptr_t)a44iew);
}

//----- (004AD8E0) --------------------------------------------------------
_DWORD * Rules_MvSlotReplaceCommand(int *returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD *instancePtr; // esi
  _DWORD *slotPtr; // ebp
  _DWORD newValue[6]; // [esp+0h] [ebp-78h] BYREF
  _DWORD newSlotValue[6]; // [esp+18h] [ebp-60h] BYREF
  _DWORD slotValueDesc[6]; // [esp+30h] [ebp-48h] BYREF
  __int16 exprType; // [esp+48h] [ebp-30h] BYREF
  _DWORD *exprValue CLASH95_UNUSED; // [esp+4Ah] [ebp-2Eh]
  int exprNext CLASH95_UNUSED; // [esp+4Eh] [ebp-2Ah]
  int exprArgList CLASH95_UNUSED; // [esp+52h] [ebp-26h]
  int rangeEnd; // [esp+58h] [ebp-20h] BYREF
  int rangeStart[7]; // [esp+5Ch] [ebp-1Ch] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Rules_ResolveSlotEditInstanceArg((int)(intptr_t)aSlotReplace, a2, a3);
  instancePtr = result;
  if ( result )
  {
    result = (_DWORD *)(uintptr_t)Rules_ParseMultifieldSlotEditArgs(
                         1u,
                         (int)(intptr_t)aSlotReplace,
                         (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10),
                         (int)(intptr_t)result,
                         a3,
                         (_DWORD*)(rangeStart),
                         (_DWORD*)(&rangeEnd),
                         newValue);
    slotPtr = result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, (int)(intptr_t)result);
      result = (_DWORD *)(uintptr_t)Rules_MultifieldReplaceRange(newSlotValue, slotValueDesc, rangeEnd, rangeStart[0], newValue, (int)(intptr_t)aSlotReplace);
      if ( result )
      {
        exprType = 4;
        exprValue = newSlotValue;
        exprArgList = 0;
        exprNext = 0;
        return (_DWORD *)(uintptr_t)MessageHandler_SendToInstanceAddress(*(_DWORD *)(uintptr_t)(*slotPtr + 12), (int)(intptr_t)instancePtr, (int)(intptr_t)&exprType, returnValue, a3);
      }
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AD9B0) --------------------------------------------------------
_DWORD * Rules_MvSlotInsertCommand(int *returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD *instancePtr; // esi
  _DWORD *slotPtr; // ebp
  _DWORD *v8; // ecx
  _DWORD newValue[6]; // [esp+0h] [ebp-74h] BYREF
  _DWORD newSlotValue[6]; // [esp+18h] [ebp-5Ch] BYREF
  _DWORD slotValueDesc[6]; // [esp+30h] [ebp-44h] BYREF
  __int16 exprType; // [esp+48h] [ebp-2Ch] BYREF
  _DWORD *exprValue CLASH95_UNUSED; // [esp+4Ah] [ebp-2Ah]
  int exprNext CLASH95_UNUSED; // [esp+4Eh] [ebp-26h]
  int exprArgList CLASH95_UNUSED; // [esp+52h] [ebp-22h]
  int insertIndex[7]; // [esp+58h] [ebp-1Ch] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Rules_ResolveSlotEditInstanceArg((int)(intptr_t)aSlotInsert, a2, a3);
  instancePtr = result;
  if ( result )
  {
    result = (_DWORD *)(uintptr_t)Rules_ParseMultifieldSlotEditArgs(
                         0,
                         (int)(intptr_t)aSlotInsert,
                         (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10),
                         (int)(intptr_t)result,
                         a3,
                         (_DWORD*)(insertIndex),
                         0,
                         newValue);
    slotPtr = result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, (int)(intptr_t)result);
      result = (_DWORD *)(uintptr_t)Rules_MultifieldInsertRange(newSlotValue, slotValueDesc, v8, insertIndex[0], (int)(intptr_t)aSlotInsert);
      if ( result )
      {
        exprType = 4;
        exprValue = newSlotValue;
        exprArgList = 0;
        exprNext = 0;
        return (_DWORD *)(uintptr_t)MessageHandler_SendToInstanceAddress(*(_DWORD *)(uintptr_t)(*slotPtr + 12), (int)(intptr_t)instancePtr, (int)(intptr_t)&exprType, returnValue, a3);
      }
    }
  }
  return result;
}
// 4ADA2C: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ADA70) --------------------------------------------------------
_DWORD * Rules_MvSlotDeleteCommand(int *returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  _DWORD *instancePtr; // esi
  _DWORD *slotPtr; // ebp
  _DWORD newSlotValue[6]; // [esp+0h] [ebp-60h] BYREF
  _DWORD slotValueDesc[6]; // [esp+18h] [ebp-48h] BYREF
  __int16 exprType; // [esp+30h] [ebp-30h] BYREF
  _DWORD *exprValue CLASH95_UNUSED; // [esp+32h] [ebp-2Eh]
  int exprNext CLASH95_UNUSED; // [esp+36h] [ebp-2Ah]
  int exprArgList CLASH95_UNUSED; // [esp+3Ah] [ebp-26h]
  int rangeEnd; // [esp+40h] [ebp-20h] BYREF
  int rangeStart[7]; // [esp+44h] [ebp-1Ch] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Rules_ResolveSlotEditInstanceArg((int)(intptr_t)aSlotDelete, a2, a3);
  instancePtr = result;
  if ( result )
  {
    result = (_DWORD *)(uintptr_t)Rules_ParseMultifieldSlotEditArgs(
                         2u,
                         (int)(intptr_t)aSlotDelete,
                         (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10),
                         (int)(intptr_t)result,
                         a3,
                         (_DWORD*)(rangeStart),
                         (_DWORD*)(&rangeEnd),
                         0);
    slotPtr = result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, (int)(intptr_t)result);
      result = (_DWORD *)(uintptr_t)Rules_MultifieldDeleteRange(newSlotValue, slotValueDesc, rangeEnd, rangeStart[0], (int)(intptr_t)aSlotDelete);
      if ( result )
      {
        exprType = 4;
        exprValue = newSlotValue;
        exprArgList = 0;
        exprNext = 0;
        return (_DWORD *)(uintptr_t)MessageHandler_SendToInstanceAddress(*(_DWORD *)(uintptr_t)(*slotPtr + 12), (int)(intptr_t)instancePtr, (int)(intptr_t)&exprType, returnValue, a3);
      }
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ADB40) --------------------------------------------------------
int  Rules_DirectSlotReplaceCommand(int functionName, double a2)
{
  int result; // eax
  _DWORD *instancePtr; // edi
  int *slotPtr; // esi
  _DWORD newSlotValue[6]; // [esp+0h] [ebp-64h] BYREF
  _DWORD slotValueDesc[6]; // [esp+18h] [ebp-4Ch] BYREF
  _DWORD newValue[6]; // [esp+30h] [ebp-34h] BYREF
  int rangeStart; // [esp+48h] [ebp-1Ch] BYREF
  int rangeEnd[6]; // [esp+4Ch] [ebp-18h] BYREF

  rangeEnd[4] = functionName;
  result = MessageHandler_CheckCurrentMessage(functionName, 1);
  if ( result )
  {
    instancePtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(MessageHandler_GetNthArgument(0) + 8);
    result = Rules_ParseMultifieldSlotEditArgs(1u, (int)(intptr_t)aDirectSlotRepl, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), (int)(intptr_t)instancePtr, a2, (_DWORD*)(&rangeStart), (_DWORD*)(rangeEnd), newValue);
    slotPtr = (int *)(uintptr_t)result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, result);
      result = Rules_MultifieldReplaceRange(newSlotValue, slotValueDesc, rangeEnd[0], rangeStart, newValue, (int)(intptr_t)aDirectSlotRepl);
      if ( result )
      {
        result = Instance_PutSlotValue(instancePtr, slotPtr, newSlotValue, a2);
        if ( result )
          return 1;
      }
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;

//----- (004ADC00) --------------------------------------------------------
int  Rules_DirectSlotInsertCommand(int functionName, double a2)
{
  int result; // eax
  _DWORD *instancePtr; // edi
  int *slotPtr; // esi
  _DWORD *v5; // ecx
  _DWORD slotValueDesc[6]; // [esp+0h] [ebp-60h] BYREF
  _DWORD newValue[6]; // [esp+18h] [ebp-48h] BYREF
  _DWORD newSlotValue[6]; // [esp+30h] [ebp-30h] BYREF
  int insertIndex[6]; // [esp+48h] [ebp-18h] BYREF

  insertIndex[4] = functionName;
  result = MessageHandler_CheckCurrentMessage(functionName, 1);
  if ( result )
  {
    instancePtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(MessageHandler_GetNthArgument(0) + 8);
    result = Rules_ParseMultifieldSlotEditArgs(0, (int)(intptr_t)aDirectSlotInse, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), (int)(intptr_t)instancePtr, a2, (_DWORD*)(insertIndex), 0, newValue);
    slotPtr = (int *)(uintptr_t)result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, result);
      result = Rules_MultifieldInsertRange(newSlotValue, slotValueDesc, v5, insertIndex[0], (int)(intptr_t)aDirectSlotInse);
      if ( result )
      {
        result = Instance_PutSlotValue(instancePtr, slotPtr, newSlotValue, a2);
        if ( result )
          return 1;
      }
    }
  }
  return result;
}
// 4ADC75: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004ADCB0) --------------------------------------------------------
int  Rules_DirectSlotDeleteCommand(int functionName, double a2)
{
  int result; // eax
  _DWORD *instancePtr; // edi
  int v4; // edx
  int *slotPtr; // esi
  _DWORD newSlotValue[6]; // [esp+0h] [ebp-4Ch] BYREF
  _DWORD slotValueDesc[6]; // [esp+18h] [ebp-34h] BYREF
  int rangeStart; // [esp+30h] [ebp-1Ch] BYREF
  int rangeEnd[6]; // [esp+34h] [ebp-18h] BYREF

  rangeEnd[4] = functionName;
  result = MessageHandler_CheckCurrentMessage(functionName, 1);
  if ( result )
  {
    instancePtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(MessageHandler_GetNthArgument(0) + 8);
    result = Rules_ParseMultifieldSlotEditArgs(2u, v4, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), (int)(intptr_t)instancePtr, a2, (_DWORD*)(&rangeStart), (_DWORD*)(rangeEnd), 0);
    slotPtr = (int *)(uintptr_t)result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, result);
      result = Rules_MultifieldDeleteRange(newSlotValue, slotValueDesc, rangeEnd[0], rangeStart, (int)(intptr_t)aDirectSlotDele);
      if ( result )
      {
        result = Instance_PutSlotValue(instancePtr, slotPtr, newSlotValue, a2);
        if ( result )
          return 1;
      }
    }
  }
  return result;
}
// 4ADCFF: variable 'v4' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004ADD60) --------------------------------------------------------
_DWORD * Rules_ResolveSlotEditInstanceArg(int functionName, int a2, double a3)
{
  _DWORD *instancePtr; // ecx
  int v7; // ecx
  _DWORD instanceArg[2]; // [esp-4h] [ebp-28h] BYREF
  int argValue; // [esp+4h] [ebp-20h]
  int v10 CLASH95_UNUSED; // [esp+1Ch] [ebp-8h]

  v10 = a2;
  if ( !Lexer_ParseValueList(1, instanceArg, 112, a3) )
  {
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( instanceArg[1] == 7 )
  {
    instancePtr = (_DWORD *)(uintptr_t)argValue;
    if ( (*(_BYTE *)(uintptr_t)(argValue + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    instancePtr = Instance_FindByName(argValue);
    if ( !instancePtr )
    {
      Instance_ReportNoSuchInstanceError(0, functionName);
      return (_DWORD *)(uintptr_t)v7;
    }
  }
  return instancePtr;
}
// 4ADDD9: variable 'v7' is possibly undefined

//----- (004ADDF0) --------------------------------------------------------
BOOL  Rules_ParseMultifieldSlotEditArgs(
        unsigned int editCode,
        int functionName,
        __int16 *argExprs,
        int instancePtr,
        double a5,
        _DWORD *rangeStart,
        _DWORD *rangeEnd,
        _DWORD *newValue)
{
  int argPos; // ebx
  _BYTE **slotLookup; // eax
  int v12; // ecx
  _BYTE **v13; // edi
  int v14; // ecx
  __int16 *nextArgExpr; // ecx
  int v16; // ecx
  BOOL result; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  _DWORD tempValue[6]; // [esp+0h] [ebp-30h] BYREF
  /* stack alias of tempValue[1] */
  /* stack alias of tempValue[2]: the DATA_OBJECT value slot */
  _BYTE **slotPtr; // [esp+18h] [ebp-18h]
  int v29; // [esp+1Ch] [ebp-14h]
  int argPosBase; // [esp+20h] [ebp-10h]

  v29 = instancePtr;
  argPosBase = (argExprs != (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6)) + 1;
  argPos = argPosBase;
  g_ClipsEvaluationError = 0;
  Parser_ParseForm(argExprs, tempValue, (int)(intptr_t)argExprs, a5);
  if ( tempValue[1] != 2 )
  {
    Parser_ReportError(argPosBase, (int)(intptr_t)aSymbol_4);
    Lexer_ErrorRecover(1);
    return 0;
  }
  slotLookup = (_BYTE **)(uintptr_t)Instance_GetSlotValueBySymbol(v29, tempValue[2]);
  v13 = slotLookup;
  slotPtr = slotLookup;
  if ( !slotLookup )
  {
    Instance_ReportNoSuchSlotError(v12, functionName);
    return 0;
  }
  if ( (**slotLookup & 2) == 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsmult, 1, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_2, v18);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, v19);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotBeUsedOn, v20);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*((_DWORD *)*v13 + 2) + 12) + 16), v21);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInInstance_1, v22);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v29 + 28) + 16), v23);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__19, v24);
    Lexer_ErrorRecover(1);
    return 0;
  }
  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v12 + 10), tempValue, v12, a5);
  if ( tempValue[1] != 1 )
  {
    Parser_ReportError(argPos + 1, (int)(intptr_t)aInteger_3);
    Lexer_ErrorRecover(1);
    return 0;
  }
  nextArgExpr = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v14 + 10) + 10);
  *rangeStart = *(_DWORD *)(uintptr_t)(tempValue[2] + 16);
  if ( editCode == 1 || editCode == 2 )
  {
    Parser_ParseForm(nextArgExpr, tempValue, (int)(intptr_t)nextArgExpr, a5);
    if ( tempValue[1] != 1 )
    {
      Parser_ReportError(argPos + 2, (int)(intptr_t)aInteger_3);
      Lexer_ErrorRecover(1);
      return 0;
    }
    *rangeEnd = *(_DWORD *)(uintptr_t)(tempValue[2] + 16);
    nextArgExpr = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v16 + 10);
  }
  if ( editCode > 1 )
    return (BOOL)(intptr_t)slotPtr;
  result = Parser_ParseSlotDefaultOrRestriction(1, (int)(intptr_t)nextArgExpr, newValue, a5);
  if ( result )
    return (BOOL)(intptr_t)slotPtr;
  return result;
}
// 4ADEAF: simplified comparisons for 'ebp.4': !=0 && !=1 became >=2u
// 4ADE59: variable 'v12' is possibly undefined
// 4ADE70: variable 'v14' is possibly undefined
// 4ADEAA: variable 'v16' is possibly undefined
// 4ADF34: variable 'v18' is possibly undefined
// 4ADF40: variable 'v19' is possibly undefined
// 4ADF4F: variable 'v20' is possibly undefined
// 4ADF64: variable 'v21' is possibly undefined
// 4ADF73: variable 'v22' is possibly undefined
// 4ADF87: variable 'v23' is possibly undefined
// 4ADF96: variable 'v24' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;

//----- (004AE010) --------------------------------------------------------
_DWORD * Rules_MakeMultifieldRangeDescriptor(_DWORD *result, int theSlot)
{
  int multifieldValue; // ecx

  result[1] = *(_DWORD *)(uintptr_t)(theSlot + 4) << 24 >> 26;
  multifieldValue = *(_DWORD *)(uintptr_t)(theSlot + 8);
  result[3] = 0;
  result[2] = multifieldValue;
  result[4] = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theSlot + 8) + 6) - 1;
  return result;
}

//----- (004AE040) --------------------------------------------------------
signed int __thiscall Rules_ReportUndefinedMessageHandlerName(void *this_)
{
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMessageHandl_3, (int)(intptr_t)this_);
  return MessageHandler_PrintNameTypeAndClass((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore, 1);
}
// 51A614: using guessed type char *off_51A614[5];
// 51AD58: using guessed type int dword_51AD58;

//----- (004AE070) --------------------------------------------------------
signed int MessageHandler_PrintNoApplicableHandlerError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aMsgfun, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoApplicablePr, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__20, v2);
}
// 4AE090: variable 'v0' is possibly undefined
// 4AE09C: variable 'v1' is possibly undefined
// 4AE0AB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AE0C0) --------------------------------------------------------
signed int MessageHandler_CheckArgCount(void)
{
  int theHandler; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  _DWORD *v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int constructName; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  char *quantifierText; // edx
  int v14; // ecx
  int v15; // ecx

  theHandler = *(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore;
  if ( *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 20) == -1 )
  {
    if ( g_ClipsProcParamCount >= *(_DWORD *)(uintptr_t)(theHandler + 16) )
      return 1;
  }
  else if ( g_ClipsProcParamCount == *(_DWORD *)(uintptr_t)(theHandler + 16) )
  {
    return 1;
  }
  Lexer_ErrorRecover(1);
  Rules_PrintErrorID((int)(intptr_t)aMsgfun, v2, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMessageHandl_4, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v4 + 8) + 16), v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_5092EC, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)g_MessageHandlerTypeNames[*v6 << 29 >> 30], (int)(intptr_t)v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInClass_0, v7);
  constructName = Rules_GetConstructNameString(*(_DWORD *)(uintptr_t)(v8 + 12));
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], constructName, v10);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpected, v11);
  if ( *(_DWORD *)(uintptr_t)(v12 + 20) == -1 )
    quantifierText = aAtLeast;
  else
    quantifierText = aExactly;
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)quantifierText, v12);
  Rules_PrintLongInteger(v14, *(_DWORD *)(uintptr_t)(v14 + 16) - 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aArgumentS_, v15);
  return 0;
}
// 4AE119: variable 'v2' is possibly undefined
// 4AE128: variable 'v3' is possibly undefined
// 4AE12D: variable 'v4' is possibly undefined
// 4AE147: variable 'v5' is possibly undefined
// 4AE14C: variable 'v6' is possibly undefined
// 4AE16F: variable 'v7' is possibly undefined
// 4AE174: variable 'v8' is possibly undefined
// 4AE186: variable 'v10' is possibly undefined
// 4AE195: variable 'v11' is possibly undefined
// 4AE19A: variable 'v12' is possibly undefined
// 4AE1B8: variable 'v14' is possibly undefined
// 4AE1C7: variable 'v15' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51ABBC: using guessed type int dword_51ABBC;
// 51AD3C: using guessed type char *off_51AD3C[4];
// 51AD58: using guessed type int dword_51AD58;

//----- (004AE1E0) --------------------------------------------------------
signed int  MessageHandler_ReportSlotWriteAccessDenied(int slotName, int instanceFlag)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v9; // ecx

  Rules_PrintErrorID((int)(intptr_t)aMsgfun, 3, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], slotName, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSlotIn, v5);
  if ( instanceFlag )
  {
    Instance_PrintNameOfClass((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v6, 0);
  }
  else
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aClass_1, v6);
    Class_PrintName(v9, 0);
  }
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aWriteAccessDen, v7);
}
// 4AE201: variable 'v4' is possibly undefined
// 4AE210: variable 'v5' is possibly undefined
// 4AE222: variable 'v6' is possibly undefined
// 4AE231: variable 'v7' is possibly undefined
// 4AE252: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AE270) --------------------------------------------------------
signed int  MessageHandler_ReportPrivateSlotAccessDenied(int theSlot)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  Rules_PrintErrorID((int)(intptr_t)aMsgfun, 6, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aPrivateSlot, v2);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theSlot + 8) + 12) + 16), v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOfClass_1, v4);
  Class_PrintName(*(_DWORD *)(uintptr_t)(theSlot + 4), 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotBeAccess, v5);
  return Class_PrintName(v6, 1);
}
// 4AE292: variable 'v2' is possibly undefined
// 4AE2A5: variable 'v3' is possibly undefined
// 4AE2B6: variable 'v4' is possibly undefined
// 4AE2D7: variable 'v5' is possibly undefined
// 4AE2E3: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AE2F0) --------------------------------------------------------
int  MessageHandler_AddSystemHandler(_BYTE *className, char *handlerName, int extraArgCount, _BYTE *internalFunctionName)
{
  int class_record; // ecx
  signed int *message_name; // eax
  _DWORD *message_handler; // eax
  char handler_flags; // bl
  int expression_node; // eax
  int free_expression_node; // edi
  int **symbol; // eax
  int result; // eax

  class_record = (int)(intptr_t)Class_LookupInScope(className);
  message_name = Str_Intern(handlerName, class_record);
  message_handler = Class_InsertMessageHandlerRecord((_DWORD *)(uintptr_t)class_record, (int)(intptr_t)message_name, 2);
  ++*(_DWORD *)(uintptr_t)(message_handler[2] + 4);
  ++extraArgCount;
  message_handler[6] = 0;
  message_handler[5] = extraArgCount;
  handler_flags = *(_BYTE *)message_handler;
  message_handler[4] = extraArgCount;
  *(_BYTE *)message_handler = handler_flags | 1;
  free_expression_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
  if ( free_expression_node )
  {
    g_ClipsMemFreeListTemp = free_expression_node;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *(_DWORD *)(uintptr_t)free_expression_node;
    expression_node = g_ClipsMemFreeListTemp;
  }
  else
  {
    expression_node = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  message_handler[7] = expression_node;
  *(_DWORD *)(uintptr_t)(expression_node + 6) = 0;
  *(_WORD *)(uintptr_t)message_handler[7] = 10;
  symbol = Rules_MakeSymbol(internalFunctionName);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)message_handler + 28) + 2) = (_DWORD)(uintptr_t)(symbol);
  result = *(_DWORD *)((char *)message_handler + 28);
  *(_DWORD *)(uintptr_t)(result + 10) = 0;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AE390) --------------------------------------------------------
_DWORD * Class_InsertMessageHandlerRecord(_DWORD *theClass, int handlerName, char handlerType)
{
  unsigned int handlerIndex; // ecx
  int destIndex; // eax
  int *indexCursor; // edx
  int indexValue; // ebx
  int newHandlerIndex; // edx
  _BYTE *newRecordFlags; // eax
  _BYTE *recordFlagsPtr; // eax
  int watchFlag; // edx
  int oldCount; // edi
  int handlerCount; // edx
  int existingName; // ebx
  int *oldIndexArray; // [esp+8h] [ebp-28h]
  _DWORD *newHandlerArray; // [esp+Ch] [ebp-24h]
  _DWORD *oldHandlerArray; // [esp+10h] [ebp-20h]
  _DWORD *newIndexArray; // [esp+14h] [ebp-1Ch]
  int insertPosition; // [esp+1Ch] [ebp-14h]

  insertPosition = -1;
  oldHandlerArray = (_DWORD *)(uintptr_t)theClass[22];
  oldIndexArray = (int *)(uintptr_t)theClass[23];
  newHandlerArray = Mem_SmallBlockAlloc(36 * (theClass[24] + 1));
  newIndexArray = Mem_SmallBlockAlloc(4 * (theClass[24] + 1));
  qmemcpy(newHandlerArray, oldHandlerArray, 36 * theClass[24]);
  handlerIndex = 0;
  destIndex = 0;
  if ( theClass[24] )
  {
    indexCursor = oldIndexArray;
    do
    {
      if ( insertPosition == -1 )
      {
        existingName = oldHandlerArray[9 * *indexCursor + 2];
        if ( *(_DWORD *)(uintptr_t)(handlerName + 12) << 16 >> 18 < *(_DWORD *)(uintptr_t)(existingName + 12) << 16 >> 18 || existingName == handlerName )
        {
          insertPosition = handlerIndex;
          ++destIndex;
        }
      }
      indexValue = *indexCursor++;
      newIndexArray[destIndex] = indexValue;
      ++handlerIndex;
      ++destIndex;
    }
    while ( handlerIndex < theClass[24] );
  }
  if ( insertPosition == -1 )
    insertPosition = theClass[24];
  newHandlerIndex = theClass[24];
  newIndexArray[insertPosition] = newHandlerIndex;
  LOBYTE(newHandlerArray[9 * newHandlerIndex]) &= ~1u;
  newRecordFlags = (_BYTE*)(&newHandlerArray[9 * theClass[24]]);
  *newRecordFlags &= 0xF9u;
  *(_DWORD *)newRecordFlags |= 2 * (handlerType & 3);
  newHandlerArray[9 * theClass[24] + 1] = 0;
  LOBYTE(newHandlerArray[9 * theClass[24]]) &= ~8u;
  recordFlagsPtr = (_BYTE*)(&newHandlerArray[9 * theClass[24]]);
  watchFlag = g_Rules_WatchMessageHandlers & 1;
  *recordFlagsPtr &= ~0x10u;
  *(_DWORD *)recordFlagsPtr |= 16 * watchFlag;
  newHandlerArray[9 * theClass[24] + 2] = handlerName;
  newHandlerArray[9 * theClass[24] + 3] = (_DWORD)(uintptr_t)(theClass);
  newHandlerArray[9 * theClass[24] + 4] = 0;
  newHandlerArray[9 * theClass[24] + 5] = 0;
  newHandlerArray[9 * theClass[24] + 6] = 0;
  newHandlerArray[9 * theClass[24] + 7] = 0;
  newHandlerArray[9 * theClass[24] + 8] = 0;
  oldCount = theClass[24];
  if ( oldCount )
  {
    Mem_SmallBlockFree(oldHandlerArray, 36 * oldCount);
    Mem_SmallBlockFree((_DWORD*)(oldIndexArray), 4 * theClass[24]);
  }
  theClass[22] = (_DWORD)(uintptr_t)(newHandlerArray);
  handlerCount = theClass[24];
  theClass[23] = (_DWORD)(uintptr_t)(newIndexArray);
  theClass[24] = handlerCount + 1;
  return &newHandlerArray[9 * handlerCount];
}
// 51AD4C: using guessed type int dword_51AD4C;

//----- (004AE690) --------------------------------------------------------
signed int  MessageHandler_AnyHandlerBusy(int theClass)
{
  int handlerIndex; // edx
  int i; // eax

  handlerIndex = 0;
  if ( !*(_DWORD *)(uintptr_t)(theClass + 96) )
    return 0;
  for ( i = *(_DWORD *)(uintptr_t)(theClass + 88); !*(_DWORD *)(uintptr_t)(i + 4); i += 36 )
  {
    if ( (unsigned int)++handlerIndex >= *(_DWORD *)(uintptr_t)(theClass + 96) )
      return 0;
  }
  return 1;
}
