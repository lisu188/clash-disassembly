/* CLIPS compiler marking, dependency, and emission passes.
 * Original function-marker range: 0x004ACB00..0x004C8290.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004ACB00) --------------------------------------------------------
int  Compiler_WriteHeaders(int fp)
{
  fwrite_(g_Bload_SignaturePtr, strlen((const char *)g_Bload_SignaturePtr) + 1, fp, 1);
  return fwrite_(g_Bload_VersionString, strlen(g_Bload_VersionString) + 1, fp, 1);
}
// 51AD20: using guessed type void *off_51AD20;
// 51AD24: using guessed type char *off_51AD24;

//----- (004ACB60) --------------------------------------------------------
void __fastcall Compiler_MarkAndEmit(int a1, int theInstance)
{
  unsigned int slotIndex; // ebp
  int slotOffset; // edi
  _DWORD *slotPtr; // esi
  int slotNameSymbol; // eax
  unsigned int fieldIndex; // ebx
  int i; // ecx
  int multifieldPtr; // eax

  g_ClipsBsaveInstanceDataSpace += 8;
  *(_BYTE *)(*(_DWORD *)(theInstance + 28) + 12) |= 2u;
  *(_BYTE *)(**(_DWORD **)(theInstance + 44) + 12) |= 2u;
  slotIndex = 0;
  slotOffset = 0;
  g_ClipsBsaveInstanceDataSpace += 8 * *(_DWORD *)(*(_DWORD *)(theInstance + 44) + 72) + 16;
  while ( slotIndex < *(_DWORD *)(*(_DWORD *)(theInstance + 44) + 72) )
  {
    slotPtr = *(_DWORD **)(slotOffset + *(_DWORD *)(theInstance + 72));
    slotNameSymbol = *(_DWORD *)(*(_DWORD *)(*slotPtr + 8) + 12);
    *(_BYTE *)(slotNameSymbol + 12) |= 2u;
    if ( (*(_BYTE *)*slotPtr & 2) != 0 )
    {
      fieldIndex = 1;
      for ( i = 0; ; Compiler_MarkAtomicValueInUse(*(__int16 *)(i + 6 + multifieldPtr + 8), *(_DWORD *)(i + 6 + multifieldPtr + 10)) )
      {
        multifieldPtr = slotPtr[2];
        if ( fieldIndex > *(_DWORD *)(multifieldPtr + 6) )
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

  result = (signed int *)value;
  g_ClipsBsaveInstanceDataSpace += 8;
  switch ( type )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
      *(_BYTE *)(value + 12) |= 2u;
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
  symbolIndex = *(_DWORD *)(*(_DWORD *)(theInstance + 28) + 12) << 16 >> 18;
  fwrite_(&symbolIndex, 4, fp, 1);
  symbolIndex = *(_DWORD *)(**(_DWORD **)(instance + 44) + 12) << 16 >> 18;
  slotOffset = 0;
  fwrite_(&symbolIndex, 4, fp, 1);
  v5 = fp;
  slotIndex = 0;
  fwrite_((const void *)(*(_DWORD *)(instance + 44) + 72), 4, v5, 1);
  while ( slotIndex < *(_DWORD *)(*(_DWORD *)(instance + 44) + 72) )
  {
    slotPtr = *(_DWORD **)(*(_DWORD *)(instance + 72) + slotOffset);
    slotNameIndex = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*slotPtr + 8) + 12) + 12) << 16 >> 18;
    if ( (*(_BYTE *)*slotPtr & 2) != 0 )
      fieldCount = *(_DWORD *)(slotPtr[2] + 6);
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
    result = *(_DWORD *)(instance + 44);
    if ( slotIndex2 >= *(_DWORD *)(result + 72) )
      break;
    slot = *(_DWORD *)(slotOffset2 + *(_DWORD *)(instance + 72));
    if ( (**(_BYTE **)slot & 2) != 0 )
      numFields = *(_DWORD *)(*(_DWORD *)(slot + 8) + 6);
    else
      numFields = 1;
    LOBYTE(v7) = **(_BYTE **)slot;
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
          Compiler_WriteAtomicValueRef(*(__int16 *)(fieldOffset + *(_DWORD *)(slot + 8) + 14), *(_DWORD *)(fieldOffset + *(_DWORD *)(slot + 8) + 16), fp, fieldOffset);
          fieldOffset = v13 + 6;
        }
        while ( fieldIndex <= slotFieldCount );
      }
    }
    else
    {
      Compiler_WriteAtomicValueRef(*(_DWORD *)(slot + 4) << 24 >> 26, *(_DWORD *)(slot + 8), fp, v7);
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
  int valueIndex; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]

  v8 = a4;
  typeCode = type;
  switch ( type )
  {
    case 0:
    case 1:
      bucketBits = *(_DWORD *)(value + 12);
      goto LABEL_3;
    case 2:
    case 3:
    case 8:
      bucketBits = *(_DWORD *)(value + 12);
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
    Symbol = Rules_MakeSymbol(aMakeInstance_1);
    AST_NewNode(10, (int)Symbol);
    readSource = instanceFile;
    Parser_NextToken(instanceFile, (int)&g_ParserCurrentTokenType);
    savedUseMessageDispatch = g_Instance_UseMessageDispatchForInit;
    g_Instance_UseMessageDispatchForInit = useMessageDispatch;
    if ( g_ParserCurrentTokenType != 102 )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( g_ParserCurrentTokenType != 100 )
        {
          Parser_ReportSyntaxError();
          g_ClipsMemFreeListTemp = (int)v18;
          *v18 = *(_DWORD *)(g_ClipsMemoryTable + 56);
          *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
          fclose_(v18);
          IO_SetFastLoadFile(savedFastLoadFile);
          Lexer_ErrorRecover(1);
          g_Instance_UseMessageDispatchForInit = savedUseMessageDispatch;
          return instanceCount;
        }
        if ( !Rules_ParseMakeInstanceNode((int)v9, readSource) )
        {
          fclose_(v11);
          IO_SetFastLoadFile(savedFastLoadFile);
          g_Instance_UseMessageDispatchForInit = savedUseMessageDispatch;
          Lexer_ErrorRecover(1);
          return instanceCount;
        }
        AST_InstallNodeChain(v11);
        Parser_ParseForm(v13, v12, (int)v13, a5);
        AST_DeinstallNodeChain(v14);
        if ( !g_ClipsEvaluationError )
          ++instanceCount;
        AST_Free(*(_DWORD *)(v15 + 6));
        Parser_NextToken(readSource, v16);
        if ( g_ParserCurrentTokenType == 102 )
          break;
      }
    }
    g_ClipsMemFreeListTemp = (int)v9;
    *v9 = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    fclose_(v9);
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
signed int __fastcall Rules_ReportInstanceFileProcessError(int functionName, int fileName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aInsfile, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction_1, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCouldNotComple, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], fileName, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__18, v7);
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
  if ( !strcmp_(v4, g_Bload_SignaturePtr) )
  {
    Rules_BloadReadBlock((uintptr_t)headerBuffer, strlen(g_Bload_VersionString) + 1);
    if ( !strcmp_(v5, g_Bload_VersionString) )
    {
      return 1;
    }
    else
    {
      Rules_PrintErrorID((int)aInsfile, 3, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], fileName, v9);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFileIsNotAComp, v10);
      return 0;
    }
  }
  else
  {
    Rules_PrintErrorID((int)aInsfile, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], fileName, v7);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFileIsNotABina, v8);
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
signed int  Rules_BloadReadInstanceRecord(int a1, double a2)
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

  Rules_BloadReadBufferedBytes((int)&bloadIndex, 4u, a1);
  instanceName = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * bloadIndex);
  Rules_BloadReadBufferedBytes((int)&bloadIndex, 4u, v2);
  classNameSymbol = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * bloadIndex);
  Rules_BloadReadBufferedBytes((int)&slotCount, 4u, v4);
  theDefclass = Class_LookupInScope(*(_BYTE **)(classNameSymbol + 16));
  totalAtomCount[1] = theDefclass;
  if ( !theDefclass )
  {
    Class_ReportLookupError(v6, *(_DWORD *)(classNameSymbol + 16));
    return 0;
  }
  if ( slotCount != theDefclass[18] || (newInstance = Instance_BuildInstance(instanceName, (int)theDefclass, 0, a2)) == 0 )
  {
    Rules_ReportBloadInstanceError(instanceName);
    return 0;
  }
  if ( !slotCount )
    return 1;
  bsaveSlotValues = Mem_SmallBlockAlloc(8 * slotCount);
  Rules_BloadReadBufferedBytes((int)bsaveSlotValues, 8 * slotCount, v8);
  Rules_BloadReadBufferedBytes((int)totalAtomCount, 4u, v9);
  if ( totalAtomCount[0] )
  {
    slotValueAtoms = Mem_NewArray(8 * totalAtomCount[0]);
    Rules_BloadReadBufferedBytes((int)slotValueAtoms, 8 * totalAtomCount[0], v10);
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
    slotPtr = *(int **)(slotOffset + newInstance[18]);
    if ( *(_DWORD *)(4 * *slotValueCursor + g_ClipsBloadSymbolPointerArray) != *(_DWORD *)(*(_DWORD *)(*slotPtr + 8) + 12) )
      break;
    Rules_BloadBuildSlotValue(slotValue, &slotValueAtoms[2 * atomIndex], (int)aBloadInstances, slotValueCursor[1]);
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
  Instance_DeleteInstance((int)newInstance, a2);
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

  Rules_PrintErrorID((int)aInsfile, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionBloadI, v2);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(instanceName + 16), v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfClass_0, v4);
  return Class_PrintName(v5, 1);
}
// 4AD452: variable 'v2' is possibly undefined
// 4AD45F: variable 'v3' is possibly undefined
// 4AD473: variable 'v4' is possibly undefined
// 4AD47F: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AD490) --------------------------------------------------------
void ** Rules_BloadBuildSlotValue(_DWORD *returnValue, _DWORD *bsaveValues, int a3, signed int valueCount)
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
      result = Rules_BloadLookupAtomByIndex(bsaveValues, a3);
      returnValue[2] = result;
    }
    else
    {
      returnValue[1] = 4;
      multifield = Rules_CreateEphemeralMultifield(valueCount);
      returnValue[3] = 0;
      returnValue[2] = multifield;
      returnValue[4] = valueCount - 1;
      fieldCursor = v7 + 2;
      fieldOffset = 0;
      endPtr = &v7[2 * valueCount - 2];
      do
      {
        *(_WORD *)(returnValue[2] + fieldOffset + 14) = *((_WORD *)fieldCursor - 4);
        result = Rules_BloadLookupAtomByIndex(v7, fieldOffset + 6);
        fieldCursor += 2;
        v7 = (_DWORD *)(v12 + 8);
        *(_DWORD *)(fieldOffset + returnValue[2] + 10) = result;
      }
      while ( v7 <= endPtr );
    }
  }
  else
  {
    returnValue[1] = 4;
    result = (void **)Rules_CreateEphemeralMultifield(0);
    returnValue[4] = -1;
    returnValue[2] = result;
    returnValue[3] = 0;
  }
  return result;
}
// 4AD4CC: conditional instruction was optimized away because ebx.4>=2u
// 4AD4D5: variable 'v7' is possibly undefined
// 4AD4E3: variable 'v9' is possibly undefined
// 4AD4FE: variable 'v12' is possibly undefined

//----- (004AD570) --------------------------------------------------------
void ** Rules_BloadLookupAtomByIndex(_DWORD *bsaveValue, int a2)
{
  void **result; // eax

  switch ( *bsaveValue )
  {
    case 0:
      result = *(void ***)(g_Clips_FloatConstantTable + 4 * bsaveValue[1]);
      break;
    case 1:
      result = *(void ***)(g_Clips_IntegerConstantTable + 4 * bsaveValue[1]);
      break;
    case 2:
    case 3:
    case 8:
      result = *(void ***)(g_ClipsBloadSymbolPointerArray + 4 * bsaveValue[1]);
      break;
    case 5:
      result = 0;
      break;
    case 6:
      result = &g_Rules_DummyFactPtr;
      break;
    default:
      Rules_ReportSystemError(a2, 1);
      IO_RunRouterExitCallbacks();
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
unsigned int  Rules_BloadReadBufferedBytes(int dataBuffer, unsigned int bufferSize, int a3)
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
            copyByte = *(_BYTE *)(g_ClipsBloadReadBuffer + bytesCopied + g_BloadReadBufferOffset);
            ++bytesCopied;
            *(_BYTE *)(destCursor - 1) = copyByte;
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
    for ( result = 0; result < bufferSize; *(_BYTE *)(dataBuffer - 1) = curByte )
    {
      ++dataBuffer;
      curByte = *(_BYTE *)(result + g_BloadReadBufferOffset + g_ClipsBloadReadBuffer);
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
        Rules_ReportSystemError(a3, 2);
        IO_RunRouterExitCallbacks();
      }
    }
    g_ClipsBloadReadBuffer = Mem_HeapAllocWithRetry((_DWORD *)g_Clips_BloadBufferSize);
    Rules_BloadReadBlock(g_ClipsBloadReadBuffer, g_Clips_BloadBufferSize);
    for ( i = 0; i < bufferSize; *(_BYTE *)(dataBuffer - 1) = bufferByte )
    {
      ++dataBuffer;
      bufferByte = *(_BYTE *)(g_ClipsBloadReadBuffer + i++);
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
signed int Rules_BloadReleaseReadBuffer()
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
signed int Rules_RegisterMultifieldSlotCommands()
{
  Rules_RegisterHostFunction(aDirectMvReplac, 98, (int)aDirectmvreplac, (int)Rules_DirectSlotReplaceCommand, (int)a4Wii);
  Rules_RegisterHostFunction(aDirectMvInsert, 98, (int)aDirectmvinsert, (int)Rules_DirectSlotInsertCommand, (int)a3Wi);
  Rules_RegisterHostFunction(aDirectMvDelete, 98, (int)aDirectmvdelete, (int)Rules_DirectSlotDeleteCommand, (int)a33iw);
  Rules_RegisterHostFunction(aMvSlotReplace, 117, (int)aMvslotreplacec, (int)Rules_MvSlotReplaceCommand, (int)a5Uewii);
  Rules_RegisterHostFunction(aMvSlotInsert, 117, (int)aMvslotinsertco, (int)Rules_MvSlotInsertCommand, (int)a4Uewi);
  Rules_RegisterHostFunction(aMvSlotDelete, 117, (int)aMvslotdeleteco, (int)Rules_MvSlotDeleteCommand, (int)a44iew);
  Rules_RegisterHostFunction(aSlotDirectRepl, 98, (int)aDirectmvreplac, (int)Rules_DirectSlotReplaceCommand, (int)a4Wii);
  Rules_RegisterHostFunction(aSlotDirectInse, 98, (int)aDirectmvinsert, (int)Rules_DirectSlotInsertCommand, (int)a3Wi);
  Rules_RegisterHostFunction(aSlotDirectDele, 98, (int)aDirectmvdelete, (int)Rules_DirectSlotDeleteCommand, (int)a33iw);
  Rules_RegisterHostFunction(aSlotReplace, 117, (int)aMvslotreplacec, (int)Rules_MvSlotReplaceCommand, (int)a5Uewii);
  Rules_RegisterHostFunction(aSlotInsert, 117, (int)aMvslotinsertco, (int)Rules_MvSlotInsertCommand, (int)a4Uewi);
  return Rules_RegisterHostFunction(aSlotDelete, 117, (int)aMvslotdeleteco, (int)Rules_MvSlotDeleteCommand, (int)a44iew);
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
  _DWORD *exprValue; // [esp+4Ah] [ebp-2Eh]
  int exprNext; // [esp+4Eh] [ebp-2Ah]
  int exprArgList; // [esp+52h] [ebp-26h]
  int rangeEnd; // [esp+58h] [ebp-20h] BYREF
  int rangeStart[7]; // [esp+5Ch] [ebp-1Ch] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Rules_ResolveSlotEditInstanceArg((int)aSlotReplace, a2, a3);
  instancePtr = result;
  if ( result )
  {
    result = (_DWORD *)Rules_ParseMultifieldSlotEditArgs(
                         1u,
                         (int)aSlotReplace,
                         *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
                         (int)result,
                         a3,
                         rangeStart,
                         &rangeEnd,
                         newValue);
    slotPtr = result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, (int)result);
      result = (_DWORD *)Rules_MultifieldReplaceRange(newSlotValue, slotValueDesc, rangeEnd, rangeStart[0], newValue, (int)aSlotReplace);
      if ( result )
      {
        exprType = 4;
        exprValue = newSlotValue;
        exprArgList = 0;
        exprNext = 0;
        return (_DWORD *)MessageHandler_SendToInstanceAddress(*(_DWORD *)(*slotPtr + 12), (int)instancePtr, (int)&exprType, returnValue, a3);
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
  _DWORD *exprValue; // [esp+4Ah] [ebp-2Ah]
  int exprNext; // [esp+4Eh] [ebp-26h]
  int exprArgList; // [esp+52h] [ebp-22h]
  int insertIndex[7]; // [esp+58h] [ebp-1Ch] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Rules_ResolveSlotEditInstanceArg((int)aSlotInsert, a2, a3);
  instancePtr = result;
  if ( result )
  {
    result = (_DWORD *)Rules_ParseMultifieldSlotEditArgs(
                         0,
                         (int)aSlotInsert,
                         *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
                         (int)result,
                         a3,
                         insertIndex,
                         0,
                         newValue);
    slotPtr = result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, (int)result);
      result = (_DWORD *)Rules_MultifieldInsertRange(newSlotValue, slotValueDesc, v8, insertIndex[0], (int)aSlotInsert);
      if ( result )
      {
        exprType = 4;
        exprValue = newSlotValue;
        exprArgList = 0;
        exprNext = 0;
        return (_DWORD *)MessageHandler_SendToInstanceAddress(*(_DWORD *)(*slotPtr + 12), (int)instancePtr, (int)&exprType, returnValue, a3);
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
  _DWORD *exprValue; // [esp+32h] [ebp-2Eh]
  int exprNext; // [esp+36h] [ebp-2Ah]
  int exprArgList; // [esp+3Ah] [ebp-26h]
  int rangeEnd; // [esp+40h] [ebp-20h] BYREF
  int rangeStart[7]; // [esp+44h] [ebp-1Ch] BYREF

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Rules_ResolveSlotEditInstanceArg((int)aSlotDelete, a2, a3);
  instancePtr = result;
  if ( result )
  {
    result = (_DWORD *)Rules_ParseMultifieldSlotEditArgs(
                         2u,
                         (int)aSlotDelete,
                         *(__int16 **)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
                         (int)result,
                         a3,
                         rangeStart,
                         &rangeEnd,
                         0);
    slotPtr = result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, (int)result);
      result = (_DWORD *)Rules_MultifieldDeleteRange(newSlotValue, slotValueDesc, rangeEnd, rangeStart[0], (int)aSlotDelete);
      if ( result )
      {
        exprType = 4;
        exprValue = newSlotValue;
        exprArgList = 0;
        exprNext = 0;
        return (_DWORD *)MessageHandler_SendToInstanceAddress(*(_DWORD *)(*slotPtr + 12), (int)instancePtr, (int)&exprType, returnValue, a3);
      }
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ADB40) --------------------------------------------------------
int  Rules_DirectSlotReplaceCommand(int a1, double a2)
{
  int result; // eax
  _DWORD *instancePtr; // edi
  int *slotPtr; // esi
  _DWORD newSlotValue[6]; // [esp+0h] [ebp-64h] BYREF
  _DWORD slotValueDesc[6]; // [esp+18h] [ebp-4Ch] BYREF
  _DWORD newValue[6]; // [esp+30h] [ebp-34h] BYREF
  int rangeStart; // [esp+48h] [ebp-1Ch] BYREF
  int rangeEnd[6]; // [esp+4Ch] [ebp-18h] BYREF

  rangeEnd[4] = a1;
  result = MessageHandler_CheckCurrentMessage(a1, 1);
  if ( result )
  {
    instancePtr = *(_DWORD **)(MessageHandler_GetNthArgument(0) + 8);
    result = Rules_ParseMultifieldSlotEditArgs(1u, (int)aDirectSlotRepl, *(__int16 **)(g_ClipsCurrentExpression + 6), (int)instancePtr, a2, &rangeStart, rangeEnd, newValue);
    slotPtr = (int *)result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, result);
      result = Rules_MultifieldReplaceRange(newSlotValue, slotValueDesc, rangeEnd[0], rangeStart, newValue, (int)aDirectSlotRepl);
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
int  Rules_DirectSlotInsertCommand(int a1, double a2)
{
  int result; // eax
  _DWORD *instancePtr; // edi
  int *slotPtr; // esi
  _DWORD *v5; // ecx
  _DWORD slotValueDesc[6]; // [esp+0h] [ebp-60h] BYREF
  _DWORD newValue[6]; // [esp+18h] [ebp-48h] BYREF
  _DWORD newSlotValue[6]; // [esp+30h] [ebp-30h] BYREF
  int insertIndex[6]; // [esp+48h] [ebp-18h] BYREF

  insertIndex[4] = a1;
  result = MessageHandler_CheckCurrentMessage(a1, 1);
  if ( result )
  {
    instancePtr = *(_DWORD **)(MessageHandler_GetNthArgument(0) + 8);
    result = Rules_ParseMultifieldSlotEditArgs(0, (int)aDirectSlotInse, *(__int16 **)(g_ClipsCurrentExpression + 6), (int)instancePtr, a2, insertIndex, 0, newValue);
    slotPtr = (int *)result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, result);
      result = Rules_MultifieldInsertRange(newSlotValue, slotValueDesc, v5, insertIndex[0], (int)aDirectSlotInse);
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
int  Rules_DirectSlotDeleteCommand(int a1, double a2)
{
  int result; // eax
  _DWORD *instancePtr; // edi
  int v4; // edx
  int *slotPtr; // esi
  _DWORD newSlotValue[6]; // [esp+0h] [ebp-4Ch] BYREF
  _DWORD slotValueDesc[6]; // [esp+18h] [ebp-34h] BYREF
  int rangeStart; // [esp+30h] [ebp-1Ch] BYREF
  int rangeEnd[6]; // [esp+34h] [ebp-18h] BYREF

  rangeEnd[4] = a1;
  result = MessageHandler_CheckCurrentMessage(a1, 1);
  if ( result )
  {
    instancePtr = *(_DWORD **)(MessageHandler_GetNthArgument(0) + 8);
    result = Rules_ParseMultifieldSlotEditArgs(2u, v4, *(__int16 **)(g_ClipsCurrentExpression + 6), (int)instancePtr, a2, &rangeStart, rangeEnd, 0);
    slotPtr = (int *)result;
    if ( result )
    {
      Rules_MakeMultifieldRangeDescriptor(slotValueDesc, result);
      result = Rules_MultifieldDeleteRange(newSlotValue, slotValueDesc, rangeEnd[0], rangeStart, (int)aDirectSlotDele);
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
  int v10; // [esp+1Ch] [ebp-8h]

  v10 = a2;
  if ( !Lexer_ParseValueList(1, instanceArg, 112, a3) )
  {
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( instanceArg[1] == 7 )
  {
    instancePtr = (_DWORD *)argValue;
    if ( (*(_BYTE *)(argValue + 24) & 2) != 0 )
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
      return (_DWORD *)v7;
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
  int tempValue; // [esp+0h] [ebp-30h] BYREF
  int parsedType; // [esp+4h] [ebp-2Ch]
  int parsedValue; // [esp+8h] [ebp-28h]
  _BYTE **slotPtr; // [esp+18h] [ebp-18h]
  int v29; // [esp+1Ch] [ebp-14h]
  int argPosBase; // [esp+20h] [ebp-10h]

  v29 = instancePtr;
  argPosBase = (argExprs != *(__int16 **)(g_ClipsCurrentExpression + 6)) + 1;
  argPos = argPosBase;
  g_ClipsEvaluationError = 0;
  Parser_ParseForm(argExprs, &tempValue, (int)argExprs, a5);
  if ( parsedType != 2 )
  {
    Parser_ReportError(argPosBase, (int)aSymbol_4);
    Lexer_ErrorRecover(1);
    return 0;
  }
  slotLookup = (_BYTE **)Instance_GetSlotValueBySymbol(v29, parsedValue);
  v13 = slotLookup;
  slotPtr = slotLookup;
  if ( !slotLookup )
  {
    Instance_ReportNoSuchSlotError(v12, functionName);
    return 0;
  }
  if ( (**slotLookup & 2) == 0 )
  {
    Rules_PrintErrorID((int)aInsmult, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction_2, v18);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v19);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotBeUsedOn, v20);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(*((_DWORD *)*v13 + 2) + 12) + 16), v21);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInInstance_1, v22);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(v29 + 28) + 16), v23);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__19, v24);
    Lexer_ErrorRecover(1);
    return 0;
  }
  Parser_ParseForm(*(__int16 **)(v12 + 10), &tempValue, v12, a5);
  if ( parsedType != 1 )
  {
    Parser_ReportError(argPos + 1, (int)aInteger_3);
    Lexer_ErrorRecover(1);
    return 0;
  }
  nextArgExpr = *(__int16 **)(*(_DWORD *)(v14 + 10) + 10);
  *rangeStart = *(_DWORD *)(parsedValue + 16);
  if ( editCode == 1 || editCode == 2 )
  {
    Parser_ParseForm(nextArgExpr, &tempValue, (int)nextArgExpr, a5);
    if ( parsedType != 1 )
    {
      Parser_ReportError(argPos + 2, (int)aInteger_3);
      Lexer_ErrorRecover(1);
      return 0;
    }
    *rangeEnd = *(_DWORD *)(parsedValue + 16);
    nextArgExpr = *(__int16 **)(v16 + 10);
  }
  if ( editCode > 1 )
    return (BOOL)slotPtr;
  result = Parser_ParseSlotDefaultOrRestriction(1, (int)nextArgExpr, newValue, a5);
  if ( result )
    return (BOOL)slotPtr;
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

  result[1] = *(_DWORD *)(theSlot + 4) << 24 >> 26;
  multifieldValue = *(_DWORD *)(theSlot + 8);
  result[3] = 0;
  result[2] = multifieldValue;
  result[4] = *(_DWORD *)(*(_DWORD *)(theSlot + 8) + 6) - 1;
  return result;
}

//----- (004AE040) --------------------------------------------------------
signed int __thiscall Rules_ReportUndefinedMessageHandlerName(void *this)
{
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMessageHandl_3, (int)this);
  return MessageHandler_PrintNameTypeAndClass((int)g_IO_LogicalNameTable_WError[0], *(_DWORD **)g_ClipsCurrentHandlerCore, 1);
}
// 51A614: using guessed type char *off_51A614[5];
// 51AD58: using guessed type int dword_51AD58;

//----- (004AE070) --------------------------------------------------------
signed int MessageHandler_PrintNoApplicableHandlerError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aMsgfun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoApplicablePr, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__20, v2);
}
// 4AE090: variable 'v0' is possibly undefined
// 4AE09C: variable 'v1' is possibly undefined
// 4AE0AB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AE0C0) --------------------------------------------------------
signed int MessageHandler_CheckArgCount()
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

  theHandler = *(_DWORD *)g_ClipsCurrentHandlerCore;
  if ( *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 20) == -1 )
  {
    if ( g_ClipsProcParamCount >= *(_DWORD *)(theHandler + 16) )
      return 1;
  }
  else if ( g_ClipsProcParamCount == *(_DWORD *)(theHandler + 16) )
  {
    return 1;
  }
  Lexer_ErrorRecover(1);
  Rules_PrintErrorID((int)aMsgfun, v2, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMessageHandl_4, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(v4 + 8) + 16), v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_5092EC, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)g_MessageHandlerTypeNames[*v6 << 29 >> 30], (int)v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInClass_0, v7);
  constructName = Rules_GetConstructNameString(*(_DWORD *)(v8 + 12));
  Output_Write((int)g_IO_LogicalNameTable_WError[0], constructName, v10);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpected, v11);
  if ( *(_DWORD *)(v12 + 20) == -1 )
    quantifierText = aAtLeast;
  else
    quantifierText = aExactly;
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)quantifierText, v12);
  Rules_PrintLongInteger(v14, *(_DWORD *)(v14 + 16) - 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArgumentS_, v15);
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

  Rules_PrintErrorID((int)aMsgfun, 3, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], slotName, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlotIn, v5);
  if ( instanceFlag )
  {
    Instance_PrintNameOfClass((int)g_IO_LogicalNameTable_WError[0], v6, 0);
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClass_1, v6);
    Class_PrintName(v9, 0);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWriteAccessDen, v7);
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

  Rules_PrintErrorID((int)aMsgfun, 6, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPrivateSlot, v2);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theSlot + 8) + 12) + 16), v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfClass_1, v4);
  Class_PrintName(*(_DWORD *)(theSlot + 4), 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotBeAccess, v5);
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

  class_record = (int)Class_LookupInScope(className);
  message_name = Str_Intern(handlerName, class_record);
  message_handler = Class_InsertMessageHandlerRecord((_DWORD *)class_record, (int)message_name, 2);
  ++*(_DWORD *)(message_handler[2] + 4);
  ++extraArgCount;
  message_handler[6] = 0;
  message_handler[5] = extraArgCount;
  handler_flags = *(_BYTE *)message_handler;
  message_handler[4] = extraArgCount;
  *(_BYTE *)message_handler = handler_flags | 1;
  free_expression_node = *(_DWORD *)(g_ClipsMemoryTable + 56);
  if ( free_expression_node )
  {
    g_ClipsMemFreeListTemp = free_expression_node;
    *(_DWORD *)(g_ClipsMemoryTable + 56) = *(_DWORD *)free_expression_node;
    expression_node = g_ClipsMemFreeListTemp;
  }
  else
  {
    expression_node = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  message_handler[7] = expression_node;
  *(_DWORD *)(expression_node + 6) = 0;
  *(_WORD *)message_handler[7] = 10;
  symbol = Rules_MakeSymbol(internalFunctionName);
  *(_DWORD *)(*(_DWORD *)((char *)message_handler + 28) + 2) = symbol;
  result = *(_DWORD *)((char *)message_handler + 28);
  *(_DWORD *)(result + 10) = 0;
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
  oldHandlerArray = (_DWORD *)theClass[22];
  oldIndexArray = (int *)theClass[23];
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
        if ( *(_DWORD *)(handlerName + 12) << 16 >> 18 < *(_DWORD *)(existingName + 12) << 16 >> 18 || existingName == handlerName )
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
  newRecordFlags = &newHandlerArray[9 * theClass[24]];
  *newRecordFlags &= 0xF9u;
  *(_DWORD *)newRecordFlags |= 2 * (handlerType & 3);
  newHandlerArray[9 * theClass[24] + 1] = 0;
  LOBYTE(newHandlerArray[9 * theClass[24]]) &= ~8u;
  recordFlagsPtr = &newHandlerArray[9 * theClass[24]];
  watchFlag = g_Rules_WatchMessageHandlers & 1;
  *recordFlagsPtr &= ~0x10u;
  *(_DWORD *)recordFlagsPtr |= 16 * watchFlag;
  newHandlerArray[9 * theClass[24] + 2] = handlerName;
  newHandlerArray[9 * theClass[24] + 3] = theClass;
  newHandlerArray[9 * theClass[24] + 4] = 0;
  newHandlerArray[9 * theClass[24] + 5] = 0;
  newHandlerArray[9 * theClass[24] + 6] = 0;
  newHandlerArray[9 * theClass[24] + 7] = 0;
  newHandlerArray[9 * theClass[24] + 8] = 0;
  oldCount = theClass[24];
  if ( oldCount )
  {
    Mem_SmallBlockFree(oldHandlerArray, 36 * oldCount);
    Mem_SmallBlockFree(oldIndexArray, 4 * theClass[24]);
  }
  theClass[22] = newHandlerArray;
  handlerCount = theClass[24];
  theClass[23] = newIndexArray;
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
  if ( !*(_DWORD *)(theClass + 96) )
    return 0;
  for ( i = *(_DWORD *)(theClass + 88); !*(_DWORD *)(i + 4); i += 36 )
  {
    if ( (unsigned int)++handlerIndex >= *(_DWORD *)(theClass + 96) )
      return 0;
  }
  return 1;
}

//----- (004AE6D0) --------------------------------------------------------
signed int  MessageHandler_RemoveByNameAndType(_DWORD *theClass, int handlerName, int indicateMissing, int handlerType)
{
  int found; // ebp
  int i; // ecx
  _DWORD *handlerRecord; // eax
  int v10; // ecx
  unsigned int scanIndex; // edx
  _BYTE *flagsPtr; // eax
  int v13; // ecx
  _DWORD *handler; // eax
  unsigned int v15; // ecx
  int recordOffset; // edx
  _BYTE *recordFlags; // eax
  int v18; // ecx
  int success; // [esp+0h] [ebp-10h]

  success = 1;
  if ( theClass[24] )
  {
    if ( MessageHandler_AnyHandlerBusy((int)theClass) )
    {
      Rules_GetConstructNameString((int)theClass);
      MessageHandler_ReportUnableToDelete();
      return 0;
    }
    if ( handlerType == -1 )
    {
      found = 0;
      for ( i = 0; i <= 3; i = v10 + 1 )
      {
        handlerRecord = Class_FindMessageHandler(theClass, handlerName, i);
        if ( handlerRecord )
        {
          found = 1;
          if ( (*(_BYTE *)handlerRecord & 1) != 0 )
          {
            Rules_PrintErrorID((int)aMsgpsr_0, 3, 0);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSystemMessag_0, v13);
            success = 0;
          }
          else
          {
            *(_BYTE *)handlerRecord |= 8u;
          }
        }
      }
      if ( !found && !strcmp_(i, asc_5093F0) )
      {
        i = theClass[24];
        scanIndex = 0;
        if ( i )
        {
          i = 0;
          do
          {
            flagsPtr = (_BYTE *)(i + theClass[22]);
            if ( (*flagsPtr & 1) == 0 )
              *flagsPtr |= 8u;
            ++scanIndex;
            i += 36;
          }
          while ( scanIndex < theClass[24] );
        }
      }
LABEL_19:
      Class_PurgeMarkedMessageHandlers((signed int)theClass, i);
      return success;
    }
    handler = Class_FindMessageHandler(theClass, handlerName, handlerType);
    if ( handler )
    {
      if ( (*(_BYTE *)handler & 1) == 0 )
      {
        *(_BYTE *)handler |= 8u;
        Class_PurgeMarkedMessageHandlers((signed int)theClass, v15);
        return 1;
      }
      if ( v15 )
      {
        Rules_PrintErrorID((int)aMsgpsr_0, 3, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSystemMessag_0, v18);
      }
    }
    else
    {
      if ( !strcmp_(v15, asc_5093F0) )
      {
        i = 0;
        if ( theClass[24] )
        {
          recordOffset = 0;
          do
          {
            recordFlags = (_BYTE *)(recordOffset + theClass[22]);
            if ( *(_DWORD *)recordFlags << 29 >> 30 == handlerType && (*recordFlags & 1) == 0 )
              *recordFlags |= 8u;
            ++i;
            recordOffset += 36;
          }
          while ( (unsigned int)i < theClass[24] );
        }
        goto LABEL_19;
      }
      if ( v15 )
      {
        Rules_GetConstructNameString((int)theClass);
        MessageHandler_ReportUnableToDelete();
      }
    }
    Class_PurgeMarkedMessageHandlers((signed int)theClass, v15);
    return 0;
  }
  if ( !indicateMissing )
    return 1;
  Rules_GetConstructNameString((int)theClass);
  MessageHandler_ReportUnableToDelete();
  return 0;
}
// 4AE746: variable 'v10' is possibly undefined
// 4AE794: variable 'i' is possibly undefined
// 4AE7D3: variable 'v13' is possibly undefined
// 4AE7FD: variable 'v15' is possibly undefined
// 4AE8A5: variable 'v18' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004AE8C0) --------------------------------------------------------
signed int  Class_PurgeMarkedMessageHandlers(signed int result, unsigned int a2)
{
  unsigned int handlerIndex; // esi
  int deletedCount; // ebx
  int recordOffset; // ebp
  int handlerRecord; // edx
  int totalCount; // esi
  unsigned int remainingCount; // ebx
  _DWORD *newIndexCursor; // eax
  unsigned int v9; // ecx
  _DWORD *indexCursor; // edx
  _DWORD *handlerEntry; // esi
  _DWORD *oldRecordCursor; // edx
  char *newRecordCursor; // ebp
  int v14; // edx
  int v15; // edx
  int v16; // edx
  const char *ppForm; // edi
  signed int newIndexArray; // [esp+0h] [ebp-30h]
  char *newHandlerArray; // [esp+4h] [ebp-2Ch]
  _DWORD *oldIndexArray; // [esp+8h] [ebp-28h]
  _DWORD *oldHandlerArray; // [esp+Ch] [ebp-24h]
  signed int theClass; // [esp+10h] [ebp-20h]
  unsigned int copiedCount; // [esp+14h] [ebp-1Ch]

  theClass = result;
  handlerIndex = 0;
  deletedCount = 0;
  if ( *(_DWORD *)(result + 96) )
  {
    recordOffset = 0;
    do
    {
      handlerRecord = recordOffset + *(_DWORD *)(theClass + 88);
      if ( (*(_BYTE *)handlerRecord & 8) != 0 )
      {
        Rules_DecrementSymbolCount(*(_DWORD *)(handlerRecord + 8), a2);
        AST_DeinstallNodeChain(*(__int16 **)(v14 + 28));
        AST_FreePackedNodeChain(*(_DWORD *)(v15 + 28));
        ppForm = *(const char **)(v16 + 32);
        ++deletedCount;
        if ( ppForm )
          Mem_SmallBlockFree(*(_DWORD **)(v16 + 32), strlen(ppForm) + 1);
      }
      else
      {
        *(_DWORD *)(handlerRecord + 4) = deletedCount;
      }
      result = theClass;
      ++handlerIndex;
      a2 = *(_DWORD *)(theClass + 96);
      recordOffset += 36;
    }
    while ( handlerIndex < a2 );
  }
  if ( deletedCount )
  {
    totalCount = *(_DWORD *)(theClass + 96);
    if ( deletedCount == totalCount )
    {
      Mem_SmallBlockFree(*(_DWORD **)(theClass + 88), 36 * totalCount);
      Mem_SmallBlockFree(*(_DWORD **)(theClass + 92), 4 * *(_DWORD *)(theClass + 96));
      result = theClass;
      *(_DWORD *)(theClass + 88) = 0;
      *(_DWORD *)(theClass + 92) = 0;
      *(_DWORD *)(theClass + 96) = 0;
    }
    else
    {
      remainingCount = totalCount - deletedCount;
      oldHandlerArray = *(_DWORD **)(theClass + 88);
      oldIndexArray = *(_DWORD **)(theClass + 92);
      newHandlerArray = (char *)Mem_SmallBlockAlloc(36 * remainingCount);
      newIndexCursor = Mem_SmallBlockAlloc(4 * remainingCount);
      newIndexArray = (signed int)newIndexCursor;
      if ( remainingCount )
      {
        indexCursor = oldIndexArray;
        do
        {
          handlerEntry = &oldHandlerArray[9 * *indexCursor];
          if ( (*(_BYTE *)handlerEntry & 8) == 0 )
          {
            ++newIndexCursor;
            ++v9;
            *(newIndexCursor - 1) = *indexCursor - handlerEntry[1];
          }
          ++indexCursor;
        }
        while ( v9 < remainingCount );
      }
      copiedCount = 0;
      if ( remainingCount )
      {
        oldRecordCursor = oldHandlerArray;
        newRecordCursor = newHandlerArray;
        do
        {
          if ( (*(_BYTE *)oldRecordCursor & 8) == 0 )
          {
            oldRecordCursor[1] = 0;
            qmemcpy(newRecordCursor, oldRecordCursor, 0x24u);
            newRecordCursor += 36;
            ++copiedCount;
          }
          oldRecordCursor += 9;
        }
        while ( remainingCount > copiedCount );
      }
      Mem_SmallBlockFree(oldHandlerArray, 36 * *(_DWORD *)(theClass + 96));
      Mem_SmallBlockFree(oldIndexArray, 4 * *(_DWORD *)(theClass + 96));
      *(_DWORD *)(theClass + 88) = newHandlerArray;
      *(_DWORD *)(theClass + 96) = remainingCount;
      result = newIndexArray;
      *(_DWORD *)(theClass + 92) = newIndexArray;
    }
  }
  return result;
}
// 4AE97D: variable 'v9' is possibly undefined
// 4AEA33: variable 'v14' is possibly undefined
// 4AEA3B: variable 'v15' is possibly undefined
// 4AEA43: variable 'v16' is possibly undefined

//----- (004AEAD0) --------------------------------------------------------
signed int  MessageHandler_TypeIndexFromKeyword(int typeName)
{
  int typeIndex; // esi
  int tableOffset; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  typeIndex = 0;
  tableOffset = 0;
  while ( strcmp_(tableOffset, *(char **)((char *)g_MessageHandlerTypeNames + tableOffset)) )
  {
    tableOffset = v4 + 4;
    ++typeIndex;
    if ( tableOffset > 12 )
    {
      Rules_PrintErrorID((int)aMsgfun, 7, 0);
      Output_Write((int)aWerror, (int)aUnrecognizedMe, v5);
      Output_Write((int)aWerror, typeName, v6);
      Output_Write((int)aWerror, (int)a__20, v7);
      return 4;
    }
  }
  return typeIndex;
}
// 4AEAED: variable 'v4' is possibly undefined
// 4AEB11: variable 'v5' is possibly undefined
// 4AEB1D: variable 'v6' is possibly undefined
// 4AEB2C: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004AEB50) --------------------------------------------------------
signed int __fastcall MessageHandler_CheckCurrentMessage(int functionName, int instanceRequired)
{
  int firstArgument; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( g_CurrentMessageHandler )
  {
    firstArgument = MessageHandler_GetNthArgument(0);
    if ( instanceRequired == 1 && *(_DWORD *)(firstArgument + 4) != 7 )
    {
      Rules_PrintErrorID((int)aMsgfun, 5, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, v7);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOperatesOnlyOn, v8);
      Lexer_ErrorRecover(1);
      return 0;
    }
    else if ( *(_DWORD *)(firstArgument + 4) == 7 && (*(_BYTE *)(*(_DWORD *)(firstArgument + 8) + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      Lexer_ErrorRecover(1);
      return 0;
    }
    else
    {
      return 1;
    }
  }
  else
  {
    Rules_PrintErrorID((int)aMsgfun, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMayOnlyBeCalle, v6);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 4AEBB6: variable 'v5' is possibly undefined
// 4AEBC5: variable 'v6' is possibly undefined
// 4AEBF1: variable 'v7' is possibly undefined
// 4AEC00: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD54: using guessed type int dword_51AD54;

//----- (004AEC30) --------------------------------------------------------
signed int  MessageHandler_PrintNameTypeAndClass(int logicalName, _DWORD *theHandler, int crtn)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  Output_Write(logicalName, *(_DWORD *)(theHandler[2] + 16), logicalName);
  Output_Write(v4, (int)asc_5092EC, v4);
  Output_Write(v5, (int)g_MessageHandlerTypeNames[*theHandler << 29 >> 30], v5);
  Output_Write(v6, (int)aInClass_0, v6);
  return Class_PrintName(theHandler[3], crtn);
}
// 4AEC48: variable 'v4' is possibly undefined
// 4AEC5E: variable 'v5' is possibly undefined
// 4AEC6A: variable 'v6' is possibly undefined
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004AEC80) --------------------------------------------------------
_DWORD * Class_FindMessageHandler(_DWORD *theClass, int handlerName, int handlerType)
{
  unsigned int groupStart; // eax
  unsigned int searchIndex; // ecx
  _DWORD *indexCursor; // edx
  _DWORD *result; // eax

  groupStart = Class_FindMessageHandlerNameGroup(theClass, handlerName);
  if ( groupStart != -1 )
  {
    searchIndex = groupStart;
    if ( groupStart < theClass[24] )
    {
      indexCursor = (_DWORD *)(theClass[23] + 4 * groupStart);
      do
      {
        result = (_DWORD *)(theClass[22] + 36 * *indexCursor);
        if ( handlerName != result[2] )
          break;
        if ( *result << 29 >> 30 == handlerType )
          return result;
        ++searchIndex;
        ++indexCursor;
      }
      while ( searchIndex < theClass[24] );
    }
  }
  return 0;
}

//----- (004AECF0) --------------------------------------------------------
unsigned int  Class_FindMessageHandlerIndex(_DWORD *theClass, int handlerName, int handlerType)
{
  unsigned int result; // eax
  unsigned int searchIndex; // edx
  int indexEntry; // eax
  _DWORD *handlerRecord; // ecx

  result = Class_FindMessageHandlerNameGroup(theClass, handlerName);
  if ( result != -1 )
  {
    searchIndex = result;
    if ( result < theClass[24] )
    {
      indexEntry = theClass[23] + 4 * result;
      do
      {
        handlerRecord = (_DWORD *)(theClass[22] + 36 * *(_DWORD *)indexEntry);
        if ( handlerName != handlerRecord[2] )
          break;
        if ( *handlerRecord << 29 >> 30 == handlerType )
          return *(_DWORD *)indexEntry;
        ++searchIndex;
        indexEntry += 4;
      }
      while ( searchIndex < theClass[24] );
    }
    return -1;
  }
  return result;
}

//----- (004AED60) --------------------------------------------------------
int  Class_FindMessageHandlerNameGroup(_DWORD *theClass, int handlerName)
{
  int searchLow; // esi
  int searchHigh; // ecx
  int mid; // eax
  unsigned int midNameBucket; // edi
  unsigned int targetBucket; // edx
  int result; // eax
  _DWORD *backCursor; // edx
  _DWORD *i; // edx
  int cursorName; // edi
  int indexArray; // [esp+4h] [ebp-24h]
  int foundIndex; // [esp+8h] [ebp-20h]
  int handlerArray; // [esp+Ch] [ebp-1Ch]
  int scanIndex; // [esp+10h] [ebp-18h]

  if ( !theClass[24] )
    return -1;
  searchLow = 0;
  handlerArray = theClass[22];
  searchHigh = theClass[24] - 1;
  foundIndex = -1;
  indexArray = theClass[23];
  while ( 1 )
  {
    mid = (searchLow + searchHigh) / 2;
    midNameBucket = *(_DWORD *)(*(_DWORD *)(36 * *(_DWORD *)(indexArray + 4 * mid) + handlerArray + 8) + 12) << 16 >> 18;
    targetBucket = *(_DWORD *)(handlerName + 12) << 16 >> 18;
    if ( targetBucket == midNameBucket )
      break;
    if ( targetBucket >= midNameBucket )
      searchLow = mid + 1;
    else
      searchHigh = mid - 1;
    if ( searchLow > searchHigh )
      return -1;
  }
  scanIndex = (searchLow + searchHigh) / 2;
  if ( mid >= searchLow )
  {
    backCursor = (_DWORD *)(indexArray + 4 * mid);
    do
    {
      if ( handlerName == *(_DWORD *)(handlerArray + 36 * *backCursor + 8) )
        foundIndex = scanIndex;
      if ( *(_DWORD *)(*(_DWORD *)(handlerArray + 36 * *backCursor + 8) + 12) << 16 >> 18 != *(_DWORD *)(*(_DWORD *)(36 * *(_DWORD *)(indexArray + 4 * mid)
                                                                                                  + handlerArray
                                                                                                  + 8)
                                                                                      + 12) << 16 >> 18 )
        break;
      --backCursor;
      --scanIndex;
    }
    while ( searchLow <= scanIndex );
  }
  if ( foundIndex != -1 )
    return foundIndex;
  result = mid + 1;
  if ( result > searchHigh )
    return -1;
  for ( i = (_DWORD *)(indexArray + 4 * result); ; ++i )
  {
    cursorName = *(_DWORD *)(handlerArray + 36 * *i + 8);
    if ( handlerName == cursorName )
      break;
    if ( *(_DWORD *)(cursorName + 12) << 16 >> 18 != *(_DWORD *)(handlerName + 12) << 16 >> 18 )
      return -1;
    if ( ++result > searchHigh )
      return -1;
  }
  return result;
}

//----- (004AEEB0) --------------------------------------------------------
signed int MessageHandler_ReportUnableToDelete()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aMsgfun, 8, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToDele_2, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__20, v2);
}
// 4AEED0: variable 'v0' is possibly undefined
// 4AEEDC: variable 'v1' is possibly undefined
// 4AEEEB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004AEF00) --------------------------------------------------------
int  MessageHandler_PrintHandlerPreview(int logicalName, int *handlerLink, int indentDepth)
{
  int *currentLink; // esi
  int result; // eax
  int *nextLink; // edx

  currentLink = handlerLink;
  result = *handlerLink;
  if ( (*(_BYTE *)*handlerLink & 6) != 0 )
  {
    while ( currentLink )
    {
      result = (*(_DWORD *)*currentLink & 6) == 2;
      if ( (*(_DWORD *)*currentLink & 6) != 2 )
        break;
      MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)asc_5094A8, indentDepth);
      result = MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)asc_5094AC, indentDepth);
      currentLink = (int *)currentLink[1];
    }
    if ( currentLink )
    {
      result = (*(_DWORD *)*currentLink & 6) == 4;
      if ( (*(_DWORD *)*currentLink & 6) == 4 )
      {
        result = MessageHandler_PrintAroundHandlerNesting(logicalName, currentLink, indentDepth);
        currentLink = (int *)result;
      }
    }
    while ( currentLink )
    {
      result = (*(_DWORD *)*currentLink & 6) == 6;
      if ( (*(_DWORD *)*currentLink & 6) != 6 )
        break;
      MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)asc_5094A8, indentDepth);
      result = MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)asc_5094AC, indentDepth);
      currentLink = (int *)currentLink[1];
    }
  }
  else
  {
    MessageHandler_PrintIndentedHandlerMarker(logicalName, handlerLink, (int)asc_5094A8, indentDepth);
    nextLink = (int *)currentLink[1];
    if ( nextLink )
      MessageHandler_PrintHandlerPreview(logicalName, nextLink, indentDepth + 1);
    return MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)asc_5094AC, indentDepth);
  }
  return result;
}

//----- (004AEFF0) --------------------------------------------------------
int  MessageHandler_BuildPreviewHandlerCore(int theClass, int messageName)
{
  int i; // eax
  int classIndex; // esi
  int classOffset; // edi
  int bots[4]; // [esp+0h] [ebp-3Ch] BYREF
  int tops[4]; // [esp+14h] [ebp-28h] BYREF
  int cls; // [esp+24h] [ebp-18h]

  cls = theClass;
  for ( i = 0; i != 4; tops[i - 1] = 0 )
    bots[++i] = 0;
  classIndex = 0;
  classOffset = 0;
  while ( classIndex < *(unsigned __int16 *)(cls + 46) )
  {
    classOffset += 4;
    ++classIndex;
    MessageHandler_CollectClassHandlersIntoCore(
      (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(classOffset + *(_DWORD *)(cls + 48) - 4),
      (uintptr_t)tops,
      messageName,
      (uintptr_t)&bots[1]);
  }
  return MessageHandler_JoinHandlerLinks(tops, &bots[1]);
}

//----- (004AF060) --------------------------------------------------------
signed int  MessageHandler_TraceMessageSend(int logicalName, int traceString)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  Output_Write(logicalName, (int)aMsg, logicalName);
  Output_Write(v3, traceString, v3);
  Output_Write(v4, (int)asc_5092EC, v4);
  Output_Write(v5, *(_DWORD *)(g_CurrentMessageHandler + 16), v5);
  Output_Write(v6, (int)aEd_0, v6);
  Rules_PrintLongInteger(v7, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments(v8);
}
// 4AF074: variable 'v3' is possibly undefined
// 4AF080: variable 'v4' is possibly undefined
// 4AF090: variable 'v5' is possibly undefined
// 4AF09C: variable 'v6' is possibly undefined
// 4AF0A9: variable 'v7' is possibly undefined
// 4AF0B0: variable 'v8' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 51AD54: using guessed type int dword_51AD54;

//----- (004AF0C0) --------------------------------------------------------
signed int  MessageHandler_TraceHandlerCall(int logicalName, int *handlerLink, int traceString)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  Output_Write(logicalName, (int)aHnd, logicalName);
  Output_Write(v4, traceString, v4);
  Output_Write(v5, (int)asc_5092EC, v5);
  MessageHandler_PrintNameTypeAndClass((int)g_IO_LogicalNameTable_WTrace[0], (_DWORD *)*handlerLink, 1);
  Output_Write(v6, (int)aEd, v6);
  Rules_PrintLongInteger(v7, g_ClipsCurrentEvaluationDepth);
  return ProcParam_PrintArguments(v8);
}
// 4AF0D4: variable 'v4' is possibly undefined
// 4AF0E5: variable 'v5' is possibly undefined
// 4AF0FD: variable 'v6' is possibly undefined
// 4AF10A: variable 'v7' is possibly undefined
// 4AF111: variable 'v8' is possibly undefined
// 51A618: using guessed type char *off_51A618[4];
// 51A96C: using guessed type int dword_51A96C;

//----- (004AF120) --------------------------------------------------------
int  MessageHandler_PrintAroundHandlerNesting(int logicalName, int *handlerLink, int indentDepth)
{
  int *innerLink; // edx
  int nextLink; // eax
  int savedNext; // [esp+0h] [ebp-14h]

  MessageHandler_PrintIndentedHandlerMarker(logicalName, handlerLink, (int)asc_5094A8, indentDepth);
  innerLink = (int *)handlerLink[1];
  if ( innerLink && (*(_DWORD *)*innerLink & 6) == 4 )
    nextLink = MessageHandler_PrintAroundHandlerNesting(logicalName, innerLink, indentDepth + 1);
  else
    nextLink = handlerLink[1];
  savedNext = nextLink;
  MessageHandler_PrintIndentedHandlerMarker(logicalName, handlerLink, (int)asc_5094AC, indentDepth);
  return savedNext;
}

//----- (004AF180) --------------------------------------------------------
signed int  MessageHandler_PrintIndentedHandlerMarker(int logicalName, int *handlerLink, int markerString, int indentDepth)
{
  int i; // ecx
  int v8; // ecx

  for ( i = 0; i < indentDepth; Output_Write(logicalName, (int)asc_5094D4, i + 1) )
    ;
  Output_Write(logicalName, markerString, i);
  Output_Write(logicalName, (int)asc_5092EC, v8);
  return MessageHandler_PrintNameTypeAndClass(logicalName, (_DWORD *)*handlerLink, 1);
}
// 4AF196: variable 'i' is possibly undefined
// 4AF1B5: variable 'v8' is possibly undefined

//----- (004AF1D0) --------------------------------------------------------
int  MessageHandler_SendToInstanceAddress(int messageName, int instancePtr, int remainingArgs, int *resultBuffer, double a5)
{
  _DWORD local_result[6]; // [esp+0h] [ebp-2Ch] BYREF
  unsigned char message_expression[14]; // [esp+18h] [ebp-14h] BYREF
  _DWORD *result_buffer; // eax

  result_buffer = (_DWORD *)resultBuffer;
  if ( !result_buffer )
    result_buffer = local_result;
  *(__int16 *)(message_expression + 0) = 7;
  *(_DWORD *)(message_expression + 2) = instancePtr;
  *(_DWORD *)(message_expression + 6) = 0;
  *(_DWORD *)(message_expression + 10) = remainingArgs;
  return MessageHandler_Send(result_buffer, (_DWORD *)message_expression, messageName, a5);
}

//----- (004AF2D0) --------------------------------------------------------
int  MessageHandler_FreeHandlerCore(int result)
{
  uintptr_t current; // ecx
  uintptr_t node; // edx
  uintptr_t handler; // eax

  current = (uintptr_t)(unsigned int)result;
  while ( current )
  {
    node = current;
    handler = (uintptr_t)(unsigned int)*(_DWORD *)node;
    --*(_DWORD *)(handler + 4);
    current = (uintptr_t)(unsigned int)*(_DWORD *)(node + 4);
    Class_ReleaseBusyReference(*(_DWORD *)(handler + 12));
    g_ClipsMemFreeListTemp = (int)node;
    *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AF330) --------------------------------------------------------
signed int  MessageHandler_ParseAndSend(_DWORD *returnValue, int a2, double a3)
{
  signed int result; // eax
  _DWORD argBuffer[6]; // [esp-8h] [ebp-38h] BYREF
  __int16 exprType; // [esp+10h] [ebp-20h] BYREF
  int exprValue; // [esp+12h] [ebp-1Eh]
  int exprNext; // [esp+16h] [ebp-1Ah]
  int exprArgList; // [esp+1Ah] [ebp-16h]
  int v10; // [esp+28h] [ebp-8h]

  v10 = a2;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Lexer_ParseValueList(2, argBuffer, 2, a3);
  if ( result )
  {
    exprType = **(_WORD **)(g_ClipsCurrentExpression + 6);
    exprValue = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 2);
    exprNext = *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 6);
    exprArgList = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
    return MessageHandler_Send(returnValue, &exprType, argBuffer[2], a3);
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AF3B0) --------------------------------------------------------
int  MessageHandler_GetNthArgument(int argIndex)
{
  return 24 * argIndex + g_ClipsProcParamArray;
}
// 51ABB8: using guessed type int dword_51ABB8;

//----- (004AF3D0) --------------------------------------------------------
BOOL MessageHandler_HasNextHandler()
{
  if ( !g_ClipsCurrentHandlerCore )
    return 0;
  if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 6) != 0 )
  {
    if ( (**(_DWORD **)g_ClipsCurrentHandlerCore & 6) == 4 && g_ClipsMessageHandlerCursor )
      return (**(_DWORD **)g_ClipsMessageHandlerCursor & 6) == 4;
    return 0;
  }
  return g_ClipsMessageHandlerCursor != 0;
}
// 51AD58: using guessed type int dword_51AD58;
// 51AD60: using guessed type int dword_51AD60;

//----- (004AF430) --------------------------------------------------------
_DWORD * MessageHandler_CallNextHandler(_DWORD *returnValue, double a2)
{
  _DWORD *result; // eax
  int **Symbol; // eax
  int v5; // edx
  __int16 firstArgType; // ax
  int messageName; // ebx
  int argCount; // eax
  int v9; // ecx
  int savedHandlerCore; // ebp
  int *savedCursor; // esi
  int v12; // ecx
  __int16 exprType; // [esp+0h] [ebp-2Ch] BYREF
  int exprValue; // [esp+2h] [ebp-2Ah]
  int exprNext; // [esp+6h] [ebp-26h]
  int exprArgList; // [esp+Ah] [ebp-22h]
  int argFramePushed; // [esp+10h] [ebp-1Ch]

  returnValue[1] = 2;
  result = (_DWORD *)g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    if ( !MessageHandler_HasNextHandler() )
    {
      Rules_PrintErrorID((int)aMsgpass, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aShadowedMessag, v12);
      return (_DWORD *)Lexer_ErrorRecover(1);
    }
    Symbol = Rules_MakeSymbol(aOverrideNext_0);
    if ( Symbol == *(int ***)(v5 + 2) )
    {
      firstArgType = *(_WORD *)(g_ClipsProcParamArray + 4);
      argFramePushed = 1;
      exprType = firstArgType;
      if ( firstArgType == 4 )
        exprValue = g_ClipsProcParamArray;
      else
        exprValue = *(_DWORD *)(g_ClipsProcParamArray + 8);
      exprArgList = *(_DWORD *)(g_ClipsCurrentExpression + 6);
      exprNext = 0;
      messageName = *(_DWORD *)(g_CurrentMessageHandler + 16);
      argCount = AST_CountListNodes((int)&exprType);
      result = ProcParam_PushEvaluatedArgumentFrame(&exprType, argCount, v9, messageName, a2, (int (*)(void))Rules_ReportUndefinedMessageHandlerName);
      if ( g_ClipsEvaluationError )
      {
        g_ClipsHaltExecutionFlag = 0;
        return result;
      }
    }
    else
    {
      argFramePushed = 0;
    }
    savedHandlerCore = g_ClipsCurrentHandlerCore;
    savedCursor = (int *)g_ClipsMessageHandlerCursor;
    if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 6) == 0 && (**(_BYTE **)g_ClipsMessageHandlerCursor & 6) != 0 )
    {
      result = MessageHandler_CallHandlers(returnValue, a2);
    }
    else
    {
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)*savedCursor & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], savedCursor, (int)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(*(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(*(_DWORD *)g_ClipsCurrentHandlerCore + 28),
          returnValue,
          *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      result = *(_DWORD **)g_ClipsCurrentHandlerCore;
      if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        result = (_DWORD *)MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], (int *)g_ClipsCurrentHandlerCore, (int)asc_50954C);
    }
    g_ClipsMessageHandlerCursor = (int)savedCursor;
    g_ClipsCurrentHandlerCore = savedHandlerCore;
    if ( argFramePushed )
      result = (_DWORD *)ProcParam_PopFrame();
    g_ClipsHaltExecutionFlag = 0;
  }
  return result;
}
// 4AF483: variable 'v5' is possibly undefined
// 4AF4E8: variable 'v9' is possibly undefined
// 4AF5CD: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 51ABB8: using guessed type int dword_51ABB8;
// 51ACC0: using guessed type int dword_51ACC0;
// 51AD54: using guessed type int dword_51AD54;
// 51AD58: using guessed type int dword_51AD58;
// 51AD60: using guessed type int dword_51AD60;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AF620) --------------------------------------------------------
int  MessageHandler_CollectClassHandlersIntoCore(_DWORD *theClass, uintptr_t topsArray, int handlerName, uintptr_t botsArray)
{
  int result_index; // eax
  int last_index; // [esp+0h] [ebp-24h]
  uintptr_t handler_base; // ebx
  uintptr_t index_cursor; // ecx
  _DWORD *node; // edx
  _DWORD *handler_record; // ebp
  unsigned int handler_kind; // eax
  uintptr_t head_slot; // eax
  uintptr_t tail_slot; // [esp+8h] [ebp-1Ch]

  result_index = Class_FindMessageHandlerNameGroup(theClass, handlerName);
  if ( result_index == -1 )
    return result_index;
  last_index = theClass[24] - 1;
  handler_base = (uintptr_t)(unsigned int)theClass[22];
  if ( result_index > last_index )
    return result_index;
  index_cursor = (uintptr_t)(unsigned int)theClass[23] + 4 * result_index;
  do
  {
    if ( handlerName != *(_DWORD *)(handler_base + 36 * *(_DWORD *)index_cursor + 8) )
      return result_index;
    node = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsMemoryTable + 32);
    if ( node )
    {
      g_ClipsMemFreeListTemp = (int)(uintptr_t)node;
      *(_DWORD *)(g_ClipsMemoryTable + 32) = *node;
      node = (_DWORD *)(uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
    }
    else
    {
      node = (_DWORD *)(uintptr_t)(unsigned int)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    ++*(_DWORD *)(handler_base + 36 * *(_DWORD *)index_cursor + 4);
    Class_AddBusyReference(*(_DWORD *)(handler_base + 36 * *(_DWORD *)index_cursor + 12));
    handler_record = (_DWORD *)(handler_base + 36 * *(_DWORD *)index_cursor);
    *node = (int)(uintptr_t)handler_record;
    handler_kind = ((unsigned int)*handler_record << 29) >> 30;
    head_slot = topsArray + 4 * handler_kind;
    tail_slot = botsArray + 4 * handler_kind;
    if ( *(_DWORD *)head_slot )
    {
      if ( (*handler_record & 6) == 6 )
      {
        node[1] = *(_DWORD *)head_slot;
        *(_DWORD *)head_slot = (int)(uintptr_t)node;
      }
      else
      {
        *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)tail_slot + 4) = (int)(uintptr_t)node;
        *(_DWORD *)tail_slot = (int)(uintptr_t)node;
        node[1] = 0;
      }
    }
    else
    {
      node[1] = 0;
      *(_DWORD *)tail_slot = (int)(uintptr_t)node;
      *(_DWORD *)head_slot = (int)(uintptr_t)node;
    }
    ++result_index;
    index_cursor += 4;
  }
  while ( result_index <= last_index );
  return result_index;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AF760) --------------------------------------------------------
int  MessageHandler_JoinHandlerLinks(int *tops, _DWORD *bots)
{
  int primaryHead; // ebx
  int result; // eax
  int *v6; // ecx
  int *v7; // edx
  int *v8; // ecx

  primaryHead = tops[2];
  if ( primaryHead )
  {
    result = tops[2];
    if ( tops[1] )
    {
      *(_DWORD *)(bots[1] + 4) = primaryHead;
      result = tops[1];
    }
    if ( *tops )
    {
      *(_DWORD *)(*bots + 4) = result;
      result = *tops;
    }
    *(_DWORD *)(bots[2] + 4) = tops[3];
  }
  else
  {
    MessageHandler_PrintNoApplicableHandlerError();
    v7 = v6;
    do
      MessageHandler_FreeHandlerCore(*v7);
    while ( v7 != v8 );
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 4AF799: variable 'v6' is possibly undefined
// 4AF79E: variable 'v7' is possibly undefined
// 4AF7AA: variable 'v8' is possibly undefined

//----- (004AF7D0) --------------------------------------------------------
signed int  MessageHandler_GetSelfSlotDirect(int theValue, _DWORD *theResult)
{
  int payload; // ebx
  int instance; // eax
  int slot_class; // esi
  int instance_class; // edx
  int slot_value; // edx
  unsigned int slot_id; // edi
  int mapped_slot; // edx
  int slot_descriptor; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  instance = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsProcParamArray + 8);
  slot_class = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsDefclassIdTable + 4 * *(unsigned __int16 *)(uintptr_t)(unsigned int)payload);
  instance_class = *(_DWORD *)((uintptr_t)(unsigned int)instance + 44);
  slot_id = *(_DWORD *)((uintptr_t)(unsigned int)payload + 2);
  if ( slot_class == instance_class )
  {
    mapped_slot = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance_class + 60) + 4 * slot_id);
    slot_value = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance + 72) + 4 * mapped_slot - 4);
  }
  else
  {
    if ( slot_id > *(_DWORD *)((uintptr_t)(unsigned int)instance_class + 76)
      || (mapped_slot = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance_class + 60) + 4 * slot_id)) == 0
      || (slot_value = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance + 72) + 4 * (mapped_slot - 1)),
          slot_class != *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)slot_value + 4)) )
    {
      MessageHandler_ReportStaticSlotAccessError(instance, slot_class, slot_id);
      theResult[1] = 2;
      theResult[2] = g_ClipsFalseSymbol;
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  theResult[1] = ((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_value + 4) << 24) >> 26;
  theResult[2] = *(_DWORD *)((uintptr_t)(unsigned int)slot_value + 8);
  if ( (*(_DWORD *)((uintptr_t)(unsigned int)slot_value + 4) & 0xFC) == 0x10 )
  {
    theResult[3] = 0;
    theResult[4] = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_value + 8) + 6) - 1;
  }
  return 1;
}
// 51ABB8: using guessed type int dword_51ABB8;
// 51AD64: using guessed type int dword_51AD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AF890) --------------------------------------------------------
signed int  MessageHandler_PutSelfSlotDirect(int theValue, _DWORD *theResult, double a3)
{
  int payload; // eax
  int instance; // esi
  int instance_class; // ecx
  int slot_class; // edx
  int slot_value; // ebp
  unsigned int slot_id; // ebx
  int mapped_slot; // ebp
  int slot_descriptor; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  instance = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsProcParamArray + 8);
  instance_class = *(_DWORD *)((uintptr_t)(unsigned int)instance + 44);
  slot_class = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsDefclassIdTable + 4 * *(unsigned __int16 *)(uintptr_t)(unsigned int)payload);
  slot_id = *(_DWORD *)((uintptr_t)(unsigned int)payload + 2);
  if ( slot_class == instance_class )
  {
    mapped_slot = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance_class + 60) + 4 * slot_id);
    slot_value = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance + 72) + 4 * mapped_slot - 4);
  }
  else
  {
    if ( slot_id > *(_DWORD *)((uintptr_t)(unsigned int)instance_class + 76)
      || (mapped_slot = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance_class + 60) + 4 * slot_id)) == 0
      || (slot_value = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instance + 72) + 4 * (mapped_slot - 1)),
          slot_class != *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)slot_value + 4)) )
    {
      MessageHandler_ReportStaticSlotAccessError(instance, slot_class, slot_id);
      goto LABEL_6;
    }
  }
  slot_descriptor = *(_DWORD *)(uintptr_t)(unsigned int)slot_value;
  if ( (*(_BYTE *)(uintptr_t)(unsigned int)slot_descriptor & 0x20) != 0 && !g_Instance_SlotInitInProgress )
  {
    MessageHandler_ReportSlotWriteAccessDenied(*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slot_descriptor + 8) + 12) + 16), 1);
LABEL_6:
    theResult[1] = 2;
    theResult[2] = g_ClipsFalseSymbol;
    Lexer_ErrorRecover(1);
    return 0;
  }
  if ( !Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)(uintptr_t)(unsigned int)slot_descriptor << 30 >> 31, *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6), theResult, a3)
    || !Instance_PutSlotValue((_DWORD *)(uintptr_t)(unsigned int)instance, (int *)(uintptr_t)(unsigned int)slot_value, theResult, a3) )
  {
    goto LABEL_6;
  }
  return 1;
}
// 51A27C: using guessed type int dword_51A27C;
// 51A960: using guessed type int dword_51A960;
// 51ABB8: using guessed type int dword_51ABB8;
// 51AD64: using guessed type int dword_51AD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AF990) --------------------------------------------------------
int * MessageHandler_DynamicGetSlot(int returnValue, int a2, double a3)
{
  int *result; // eax
  int v4; // ecx
  _DWORD *v5; // ecx
  _DWORD slotNameValue[11]; // [esp-4h] [ebp-2Ch] BYREF

  slotNameValue[9] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (int *)MessageHandler_CheckCurrentMessage(returnValue, 1);
  if ( result )
  {
    Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), slotNameValue, v4, a3);
    if ( slotNameValue[1] == 2 )
    {
      result = (int *)Instance_GetSlotValueBySymbol(*(_DWORD *)(g_ClipsProcParamArray + 8), slotNameValue[2]);
      if ( result )
      {
        if ( (*(_BYTE *)(*result + 1) & 4) != 0 || *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) == *(_DWORD *)(*result + 4) )
        {
          v5[1] = (unsigned int)(result[1] << 24) >> 26;
          v5[2] = result[2];
          if ( (result[1] & 0xFC) == 0x10 )
          {
            v5[3] = 0;
            result = (int *)(*(_DWORD *)(result[2] + 6) - 1);
            v5[4] = result;
          }
        }
        else
        {
          MessageHandler_ReportPrivateSlotAccessDenied(*result);
          return (int *)Lexer_ErrorRecover(1);
        }
      }
      else
      {
        return (int *)Instance_ReportNoSuchSlotError((int)v5, (int)aDynamicGet_0);
      }
    }
    else
    {
      Parser_ReportError(1, (int)aSymbol_5);
      return (int *)Lexer_ErrorRecover(1);
    }
  }
  return result;
}
// 4AF9CF: variable 'v4' is possibly undefined
// 4AFA1D: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51ABB8: using guessed type int dword_51ABB8;
// 51AD58: using guessed type int dword_51AD58;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AFAB0) --------------------------------------------------------
signed int  MessageHandler_DynamicPutSlot(_DWORD *returnValue, int a2, double a3)
{
  signed int result; // eax
  int v5; // ecx
  _DWORD *instancePtr; // edi
  int *slotLookup; // eax
  int v8; // ecx
  int *slotPtr; // ebp
  char slotFlags; // dl
  int slotDesc; // eax
  int writeDenied; // eax
  int tempValue; // [esp+0h] [ebp-30h] BYREF
  int tempType; // [esp+4h] [ebp-2Ch]
  int tempData; // [esp+8h] [ebp-28h]
  int rangeBegin; // [esp+Ch] [ebp-24h]
  signed int rangeEnd; // [esp+10h] [ebp-20h]

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = MessageHandler_CheckCurrentMessage(a2, 1);
  if ( result )
  {
    Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &tempValue, v5, a3);
    if ( tempType == 2 )
    {
      instancePtr = *(_DWORD **)(g_ClipsProcParamArray + 8);
      slotLookup = (int *)Instance_GetSlotValueBySymbol((int)instancePtr, tempData);
      slotPtr = slotLookup;
      if ( slotLookup )
      {
        slotFlags = *(_BYTE *)*slotLookup;
        if ( (slotFlags & 0x10) != 0 && ((slotFlags & 0x20) == 0 || !g_Instance_SlotInitInProgress ? (writeDenied = 1) : (writeDenied = 0), writeDenied) )
        {
          MessageHandler_ReportSlotWriteAccessDenied(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*slotPtr + 8) + 12) + 16), 1);
          return Lexer_ErrorRecover(1);
        }
        else
        {
          slotDesc = *slotPtr;
          if ( (*(_BYTE *)(*slotPtr + 1) & 4) != 0 || *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) == *(_DWORD *)(slotDesc + 4) )
          {
            result = Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)*slotPtr << 30 >> 31, *(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10), &tempValue, a3);
            if ( result )
            {
              result = Instance_PutSlotValue(instancePtr, slotPtr, &tempValue, a3);
              if ( result )
              {
                returnValue[1] = tempType;
                returnValue[2] = tempData;
                returnValue[3] = rangeBegin;
                result = rangeEnd;
                returnValue[4] = rangeEnd;
              }
            }
          }
          else
          {
            MessageHandler_ReportPrivateSlotAccessDenied(slotDesc);
            return Lexer_ErrorRecover(1);
          }
        }
      }
      else
      {
        return Instance_ReportNoSuchSlotError(v8, (int)aDynamicPut_0);
      }
    }
    else
    {
      Parser_ReportError(1, (int)aSymbol_5);
      return Lexer_ErrorRecover(1);
    }
  }
  return result;
}
// 4AFAF1: variable 'v5' is possibly undefined
// 4AFBDF: variable 'v8' is possibly undefined
// 51A27C: using guessed type int dword_51A27C;
// 51A960: using guessed type int dword_51A960;
// 51ABB8: using guessed type int dword_51ABB8;
// 51AD58: using guessed type int dword_51AD58;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AFC60) --------------------------------------------------------
int  MessageHandler_Send(_DWORD *returnValue, _DWORD *argExprs, int messageSymbol, double a4)
{
  int result; // eax
  int classPtr; // ebp
  _DWORD *instancePtr; // edi
  int messageNameStr; // ebx
  int v9; // edx
  int argCount; // eax
  int v11; // ecx
  int v12; // ecx
  int firstArgType; // edx
  int handlerCore; // eax
  int savedCursor; // ebp
  int v16; // edx
  int currentModule; // eax
  int v18; // ecx
  _DWORD *namedInstance; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int savedHandlerCore; // [esp+0h] [ebp-2Ch]
  int savedDispatchCore; // [esp+4h] [ebp-28h]
  int savedReentryFlag; // [esp+10h] [ebp-1Ch]
  int savedMessageHandler; // [esp+14h] [ebp-18h]

  returnValue[1] = 2;
  result = g_ClipsFalseSymbol;
  classPtr = 0;
  returnValue[2] = g_ClipsFalseSymbol;
  instancePtr = 0;
  g_ClipsEvaluationError = 0;
  if ( g_ClipsHaltExecution )
    return result;
  savedReentryFlag = Rules_GetReentryGuardFlag();
  Rules_SetReentryGuardFlag(1);
  savedMessageHandler = g_CurrentMessageHandler;
  g_CurrentMessageHandler = messageSymbol;
  ++g_ClipsCurrentEvaluationDepth;
  messageNameStr = *(_DWORD *)(messageSymbol + 16);
  argCount = AST_CountListNodes((uintptr_t)argExprs);
  ProcParam_PushEvaluatedArgumentFrame(argExprs, argCount, (int)(uintptr_t)"message", messageNameStr, a4, (int (*)(void))Rules_ReportUndefinedMessageHandlerName);
  if ( g_ClipsEvaluationError )
  {
    g_CurrentMessageHandler = savedMessageHandler;
    --g_ClipsCurrentEvaluationDepth;
    Rules_RunPeriodicCleanup(0, 1);
    return Rules_SetReentryGuardFlag(savedReentryFlag);
  }
  firstArgType = *(_DWORD *)(g_ClipsProcParamArray + 4);
  if ( firstArgType == 7 )
  {
    instancePtr = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsProcParamArray + 8);
    if ( (instancePtr[6] & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
LABEL_7:
      Lexer_ErrorRecover(1);
      goto LABEL_8;
    }
    currentModule = Module_GetCurrent();
    if ( Class_IsInScope(instancePtr[11], currentModule) )
    {
      classPtr = instancePtr[11];
      ++instancePtr[10];
    }
    else
    {
      Instance_ReportNoSuchInstanceError(*(_DWORD *)(instancePtr[7] + 16), (int)aSend_0);
    }
  }
  else
  {
    if ( firstArgType != 8 )
    {
      classPtr = g_ClipsPrimitiveTypeClassMap[firstArgType];
      if ( !classPtr )
      {
        Rules_ReportSystemError((int)aMsgpass, 1);
        IO_RunRouterExitCallbacks(2);
      }
      goto LABEL_8;
    }
    namedInstance = Instance_FindByName(*(_DWORD *)(g_ClipsProcParamArray + 8));
    instancePtr = namedInstance;
    if ( !namedInstance )
    {
      Rules_PrintErrorID((int)aMsgpass, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoSuchInstan_0, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsProcParamArray + 8) + 16), 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunctionSend, 0);
      goto LABEL_7;
    }
    *(_DWORD *)(g_ClipsProcParamArray + 8) = (int)(uintptr_t)namedInstance;
    *(_DWORD *)(g_ClipsProcParamArray + 4) = 7;
    classPtr = namedInstance[11];
    ++namedInstance[10];
  }
LABEL_8:
  if ( g_ClipsEvaluationError )
  {
    ProcParam_PopFrame();
    g_CurrentMessageHandler = savedMessageHandler;
    --g_ClipsCurrentEvaluationDepth;
    Rules_RunPeriodicCleanup(0, 1);
    return Rules_SetReentryGuardFlag(savedReentryFlag);
  }
  else
  {
    savedDispatchCore = g_MessageHandler_CurrentDispatchCore;
    handlerCore = MessageHandler_BuildSendHandlerCore(classPtr, messageSymbol);
    g_MessageHandler_CurrentDispatchCore = handlerCore;
    if ( handlerCore )
    {
      savedHandlerCore = g_ClipsCurrentHandlerCore;
      savedCursor = g_ClipsMessageHandlerCursor;
      if ( (**(_BYTE **)handlerCore & 6) != 0 )
      {
        g_ClipsMessageHandlerCursor = handlerCore;
        g_ClipsCurrentHandlerCore = 0;
        if ( g_MessageHandler_WatchMessages )
          MessageHandler_TraceMessageSend((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_509548);
        MessageHandler_CallHandlers(returnValue, a4);
      }
      else
      {
        g_ClipsCurrentHandlerCore = handlerCore;
        g_ClipsMessageHandlerCursor = *(_DWORD *)(handlerCore + 4);
        if ( g_MessageHandler_WatchMessages )
          MessageHandler_TraceMessageSend((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_509548);
        if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 0x10) != 0 )
          MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], (int *)g_ClipsCurrentHandlerCore, (int)asc_509548);
        if ( MessageHandler_CheckArgCount() )
          Rules_ExecuteRuleActions(
            **(_DWORD **)(*(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) + 8),
            *(__int16 **)(*(_DWORD *)g_ClipsCurrentHandlerCore + 28),
            returnValue,
            *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 24),
            a4,
            (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
        if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 0x10) != 0 )
          MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], (int *)g_ClipsCurrentHandlerCore, (int)asc_50954C);
      }
      if ( g_MessageHandler_WatchMessages )
        MessageHandler_TraceMessageSend((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_50954C);
      MessageHandler_FreeHandlerCore(g_MessageHandler_CurrentDispatchCore);
      g_ClipsMessageHandlerCursor = savedCursor;
      g_ClipsCurrentHandlerCore = savedHandlerCore;
    }
    g_MessageHandler_CurrentDispatchCore = savedDispatchCore;
    g_ClipsHaltExecutionFlag = 0;
    if ( instancePtr )
      --instancePtr[10];
    ProcParam_PopFrame();
    g_CurrentMessageHandler = savedMessageHandler;
    --g_ClipsCurrentEvaluationDepth;
    Rules_PropagateReturnValueDepth((uintptr_t)returnValue);
    Rules_RunPeriodicCleanup(0, 1);
    result = Rules_SetReentryGuardFlag(savedReentryFlag);
    if ( g_ClipsEvaluationError )
    {
      returnValue[1] = 2;
      result = g_ClipsFalseSymbol;
      returnValue[2] = g_ClipsFalseSymbol;
    }
  }
  return result;
}
// 4AFCE2: variable 'v9' is possibly undefined
// 4AFCED: variable 'v11' is possibly undefined
// 4AFE6D: variable 'v16' is possibly undefined
// 4AFF01: variable 'v18' is possibly undefined
// 4AFF29: variable 'v12' is possibly undefined
// 4AFF8B: variable 'v20' is possibly undefined
// 4AFFA1: variable 'v21' is possibly undefined
// 4AFFB0: variable 'v22' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ABB8: using guessed type int dword_51ABB8;
// 51ACC0: using guessed type int dword_51ACC0;
// 51AD50: using guessed type int dword_51AD50;
// 51AD54: using guessed type int dword_51AD54;
// 51AD58: using guessed type int dword_51AD58;
// 51AD5C: using guessed type int dword_51AD5C;
// 51AD60: using guessed type int dword_51AD60;
// 51AD7C: using guessed type int dword_51AD7C[];
// 54DD70: using guessed type int dword_54DD70;

//----- (004B0030) --------------------------------------------------------
int  MessageHandler_BuildSendHandlerCore(int theClass, int messageName)
{
  int i; // eax
  int classIndex; // esi
  int classOffset; // edi
  int bots[4]; // [esp+0h] [ebp-3Ch] BYREF
  int tops[4]; // [esp+14h] [ebp-28h] BYREF
  int cls; // [esp+24h] [ebp-18h]

  cls = theClass;
  for ( i = 0; i != 4; tops[i - 1] = 0 )
    bots[++i] = 0;
  classIndex = 0;
  classOffset = 0;
  while ( classIndex < *(unsigned __int16 *)(cls + 46) )
  {
    classOffset += 4;
    ++classIndex;
    MessageHandler_CollectClassHandlersIntoCore(
      (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(classOffset + *(_DWORD *)(cls + 48) - 4),
      (uintptr_t)tops,
      messageName,
      (uintptr_t)&bots[1]);
  }
  return MessageHandler_JoinHandlerLinks(tops, &bots[1]);
}

//----- (004B00A0) --------------------------------------------------------
_DWORD * MessageHandler_CallHandlers(_DWORD *result, double a2)
{
  _DWORD *returnBuffer; // ebp
  int savedHandlerCore; // esi
  int savedCursor; // edi
  int *handlerLink; // eax
  int handlerType; // edx
  int *afterLink; // edx
  _DWORD tempResult[12]; // [esp+0h] [ebp-30h] BYREF

  returnBuffer = result;
  if ( !g_ClipsHaltExecution )
  {
    savedHandlerCore = g_ClipsCurrentHandlerCore;
    savedCursor = g_ClipsMessageHandlerCursor;
    while ( 1 )
    {
      handlerLink = (int *)g_ClipsMessageHandlerCursor;
      handlerType = **(_DWORD **)g_ClipsMessageHandlerCursor & 6;
      if ( handlerType != 2 )
        break;
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)*handlerLink & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], handlerLink, (int)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(*(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(*(_DWORD *)g_ClipsCurrentHandlerCore + 28),
          tempResult,
          *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], (int *)g_ClipsCurrentHandlerCore, (int)asc_50954C);
      result = 0;
      g_ClipsHaltExecutionFlag = 0;
      if ( !g_ClipsMessageHandlerCursor || g_ClipsHaltExecution )
        goto LABEL_14;
    }
    if ( handlerType == 4 )
    {
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)*handlerLink & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], handlerLink, (int)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(*(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(*(_DWORD *)g_ClipsCurrentHandlerCore + 28),
          returnBuffer,
          *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      result = *(_DWORD **)g_ClipsCurrentHandlerCore;
      if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        result = (_DWORD *)MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], (int *)g_ClipsCurrentHandlerCore, (int)asc_50954C);
      g_ClipsHaltExecutionFlag = 0;
      if ( !g_ClipsMessageHandlerCursor || g_ClipsHaltExecution )
        goto LABEL_14;
      while ( (**(_DWORD **)g_ClipsMessageHandlerCursor & 6) == 4 )
      {
        result = *(_DWORD **)(g_ClipsMessageHandlerCursor + 4);
        g_ClipsMessageHandlerCursor = (int)result;
        if ( !result )
          goto LABEL_14;
      }
    }
    do
    {
      afterLink = (int *)g_ClipsMessageHandlerCursor;
      result = (_DWORD *)(**(_DWORD **)g_ClipsMessageHandlerCursor & 6);
      if ( result != (_DWORD *)6 )
        break;
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)*afterLink & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], afterLink, (int)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          **(_DWORD **)(*(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 12) + 8),
          *(__int16 **)(*(_DWORD *)g_ClipsCurrentHandlerCore + 28),
          tempResult,
          *(_DWORD *)(*(_DWORD *)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      if ( (**(_BYTE **)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)g_IO_LogicalNameTable_WTrace[0], (int *)g_ClipsCurrentHandlerCore, (int)asc_50954C);
      result = (_DWORD *)g_ClipsMessageHandlerCursor;
      g_ClipsHaltExecutionFlag = 0;
      if ( !g_ClipsMessageHandlerCursor )
        break;
    }
    while ( !g_ClipsHaltExecution );
LABEL_14:
    g_ClipsMessageHandlerCursor = savedCursor;
    g_ClipsCurrentHandlerCore = savedHandlerCore;
  }
  return result;
}
// 51A618: using guessed type char *off_51A618[4];
// 51A968: using guessed type int dword_51A968;
// 51ACC0: using guessed type int dword_51ACC0;
// 51AD58: using guessed type int dword_51AD58;
// 51AD60: using guessed type int dword_51AD60;

//----- (004B02F0) --------------------------------------------------------
signed int  MessageHandler_ReportStaticSlotAccessError(int theInstance, int slotClass, int slotIndex)
{
  int slotDesc; // edi
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  slotDesc = *(_DWORD *)(*(_DWORD *)(slotClass + 56) + 4 * *(_DWORD *)(*(_DWORD *)(slotClass + 60) + 4 * slotIndex) - 4);
  Rules_PrintErrorID((int)aMsgpass, 3, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aStaticReferenc, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(slotDesc + 8) + 12) + 16), v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfClass_2, v7);
  Class_PrintName(v8, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotApplyTo, v9);
  return Instance_PrintNameOfClass((int)g_IO_LogicalNameTable_WError[0], theInstance, 1);
}
// 4B031F: variable 'v5' is possibly undefined
// 4B0332: variable 'v6' is possibly undefined
// 4B0343: variable 'v7' is possibly undefined
// 4B034F: variable 'v8' is possibly undefined
// 4B0363: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B0380) --------------------------------------------------------
int Class_LookupCurrentScopedName()
{
  _BYTE *v0; // edx
  _BYTE *className; // eax
  int *nameSymbol; // ebx
  int v3; // edx
  int result; // eax
  int v5; // ecx

  Module_BeginEnum();
  className = (_BYTE *)Rules_ExtractModuleAndConstructName(v0);
  nameSymbol = Rules_FindSymbolEntry(className);
  Module_GetCurrent();
  Module_EndEnum();
  if ( !v3 )
    return 0;
  result = *(_DWORD *)(4 * Class_HashClassName(v3) + g_DefclassHashTable);
  if ( !result )
    return 0;
  while ( nameSymbol != *(int **)result || (*(_BYTE *)(result + 20) & 2) == 0 && v5 != **(_DWORD **)(result + 8) )
  {
    result = *(_DWORD *)(result + 100);
    if ( !result )
      return 0;
  }
  if ( (*(_BYTE *)(result + 20) & 1) == 0 )
    return 0;
  return result;
}
// 4B038C: variable 'v0' is possibly undefined
// 4B03A8: variable 'v3' is possibly undefined
// 4B03E3: variable 'v5' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0400) --------------------------------------------------------
int * Class_LookupByQualifiedName(_BYTE *qualifiedName)
{
  _BYTE *v1; // ecx
  _BYTE *v2; // ecx
  int theModule; // ebx
  _BYTE *v4; // edx
  int *result; // eax
  int v6; // ecx

  if ( !Rules_FindModuleSeparator(qualifiedName) )
    return Class_LookupInScope(v1);
  Module_BeginEnum();
  Rules_ExtractModuleAndConstructName(v2);
  theModule = Module_GetCurrent();
  Module_EndEnum();
  if ( !v4 )
    return 0;
  result = Rules_FindSymbolEntry(v4);
  if ( result )
  {
    result = *(int **)(g_DefclassHashTable + 4 * Class_HashClassName((int)result));
    if ( !result )
      return 0;
    while ( v6 != *result || theModule != *(_DWORD *)result[2] )
    {
      result = (int *)result[25];
      if ( !result )
        return 0;
    }
    if ( (result[5] & 1) == 0 )
      return 0;
  }
  return result;
}
// 4B0415: variable 'v2' is possibly undefined
// 4B042A: variable 'v4' is possibly undefined
// 4B0434: variable 'v1' is possibly undefined
// 4B045E: variable 'v6' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0480) --------------------------------------------------------
int * Class_LookupInScope(_BYTE *className)
{
  int symbol; // ebx
  int class_record; // ecx
  int bucket_index; // eax

  symbol = (int)(uintptr_t)Rules_FindSymbolEntry(className);
  if ( !symbol )
    return 0;
  bucket_index = Class_HashClassName(symbol);
  class_record = *(_DWORD *)(g_DefclassHashTable + 4 * bucket_index);
  while ( class_record )
  {
    if ( symbol == *(_DWORD *)class_record && Class_IsInScope(class_record, 0) )
    {
      if ( (*(_BYTE *)(class_record + 20) & 1) != 0 )
        return (int *)(uintptr_t)(unsigned int)class_record;
      return 0;
    }
    class_record = *(_DWORD *)(class_record + 100);
  }
  return 0;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (004B04D0) --------------------------------------------------------
int *__fastcall Class_LookupByModule(int a1, _BYTE *className)
{
  int *result; // eax
  int *nameSymbol; // ebx
  int v4; // ecx

  result = Rules_FindSymbolEntry(className);
  nameSymbol = result;
  if ( result )
  {
    result = *(int **)(4 * Class_HashClassName((int)result) + g_DefclassHashTable);
    if ( !result )
      return 0;
    while ( nameSymbol != (int *)*result || v4 && v4 != *(_DWORD *)result[2] )
    {
      result = (int *)result[25];
      if ( !result )
        return 0;
    }
    if ( (result[5] & 1) == 0 )
      return 0;
  }
  return result;
}
// 4B0502: variable 'v4' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0520) --------------------------------------------------------
BOOL  Class_IsInScope(int theDefclass, int theModule)
{
  int scopeMap; // ebx

  scopeMap = *(_DWORD *)(*(_DWORD *)(theDefclass + 104) + 16);
  if ( !theModule )
    theModule = Module_GetCurrent();
  return (unsigned __int8)((1 << (*(_DWORD *)(theModule + 24) % 8)) & *(_BYTE *)(scopeMap
                                                                        + ((*(_DWORD *)(theModule + 24)
                                                                          - (__CFSHL__(*(int *)(theModule + 24) >> 31, 3)
                                                                           + 8 * (*(int *)(theModule + 24) >> 31))) >> 3))) != 0;
}

//----- (004B0580) --------------------------------------------------------
int  Class_GetNextRecord(int defclassPtr)
{
  return Class_Enum(defclassPtr, g_CLIPS_DefclassModuleItemIndex);
}
// 54E6BC: using guessed type int dword_54E6BC;

//----- (004B0590) --------------------------------------------------------
BOOL Class_IsDeletable()
{
  int v0; // edx

  return !Rules_IsBloaded() && (*(_BYTE *)(v0 + 20) & 2) == 0 && Class_HierarchyHasInstances(v0) == 0;
}
// 4B059C: variable 'v0' is possibly undefined

//----- (004B05C0) --------------------------------------------------------
int __thiscall Class_UndefineCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_ClipsDefclassConstructType);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B05E0) --------------------------------------------------------
signed int Class_IsDeletableAlt()
{
  int v0; // edx

  if ( Rules_IsBloaded() )
    return 0;
  if ( v0 )
    return Class_DeleteRecursive(v0);
  return Class_RemoveAllDeletableClasses();
}
// 4B05EE: variable 'v0' is possibly undefined

//----- (004B0610) --------------------------------------------------------
int __thiscall Class_PrettyPrintCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_ClipsDefclassConstructType);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0630) --------------------------------------------------------
int  Class_ListConstructsCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefclassConstructType, a1, a2);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0670) --------------------------------------------------------
int  Class_GetWatchInstances(int theClass)
{
  return *(_DWORD *)(theClass + 20) << 27 >> 31;
}

//----- (004B0680) --------------------------------------------------------
int  Class_SetWatchInstances(int result, int theClass)
{
  char classFlags; // bl

  classFlags = *(_BYTE *)(theClass + 20);
  if ( (classFlags & 4) == 0 )
  {
    *(_BYTE *)(theClass + 20) = classFlags & 0xEF;
    result = 16 * (result & 1);
    *(_DWORD *)(theClass + 20) |= result;
  }
  return result;
}

//----- (004B06A0) --------------------------------------------------------
int  Class_GetWatchSlots(int theClass)
{
  return *(_DWORD *)(theClass + 20) << 26 >> 31;
}

//----- (004B06B0) --------------------------------------------------------
int  Class_SetWatchSlots(char newState, int theClass)
{
  int result; // eax

  *(_BYTE *)(theClass + 20) &= ~0x20u;
  result = 32 * (newState & 1);
  *(_DWORD *)(theClass + 20) |= result;
  return result;
}

//----- (004B06D0) --------------------------------------------------------
signed int  Class_SetWatchFlagCommand(int watchCode, int newState, int argExprs, double a4)
{
  if ( watchCode )
    return Rules_ApplyWatchFlagCommand(g_ClipsDefclassConstructType, newState, (int)Class_GetWatchSlots, argExprs, a4, (void (*)(void))Class_SetWatchSlots);
  else
    return Rules_ApplyWatchFlagCommand(g_ClipsDefclassConstructType, newState, (int)Class_GetWatchInstances, argExprs, a4, (void (*)(void))Class_SetWatchInstances);
}
// 4B0670: using guessed type int sub_4B0670();
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0710) --------------------------------------------------------
signed int  Class_SetWatchFlagForModuleCommand(int logicalName, int watchCode, int argExprs, double a4)
{
  if ( watchCode )
    return Rules_ListWatchFlagStatus(g_ClipsDefclassConstructType, logicalName, (int)Class_GetWatchSlots, argExprs, a4, (void (*)(void))Class_SetWatchSlots);
  else
    return Rules_ListWatchFlagStatus(g_ClipsDefclassConstructType, logicalName, (int)Class_GetWatchInstances, argExprs, a4, (void (*)(void))Class_SetWatchInstances);
}
// 4B0670: using guessed type int sub_4B0670();
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0750) --------------------------------------------------------
_DWORD * Class_GetConstructListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDefclassConstructType, a2);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004B0790) --------------------------------------------------------
signed int  Class_HasSuperclass(int theClass, int superclass)
{
  unsigned int classIndex; // edx
  int listOffset; // eax

  classIndex = 1;
  listOffset = 4;
  while ( classIndex < *(unsigned __int16 *)(theClass + 46) )
  {
    if ( superclass == *(_DWORD *)(*(_DWORD *)(theClass + 48) + listOffset) )
      return 1;
    listOffset += 4;
    ++classIndex;
  }
  return 0;
}

//----- (004B07D0) --------------------------------------------------------
signed int  Class_ParseClassReference(int **classOut, int a2, double a3)
{
  signed int result; // eax
  int *classPtr; // eax
  int v6; // ecx
  _DWORD argBuffer[2]; // [esp-8h] [ebp-28h] BYREF
  int argValue; // [esp+0h] [ebp-20h]
  int v9; // [esp+18h] [ebp-8h]

  v9 = a2;
  result = Lexer_ParseValueList(1, argBuffer, 2, a3);
  if ( result )
  {
    classPtr = Class_LookupByQualifiedName(*(_BYTE **)(argValue + 16));
    *classOut = classPtr;
    if ( classPtr )
    {
      result = Lexer_ParseValueList(2, argBuffer, 2, a3);
      if ( result )
        return argValue;
    }
    else
    {
      Class_ReportLookupError(v6, *(_DWORD *)(argValue + 16));
      return 0;
    }
  }
  return result;
}
// 4B082F: variable 'v6' is possibly undefined

//----- (004B0850) --------------------------------------------------------
signed int Class_ListAllConstructs()
{
  return Rules_DoForAllConstructs((void (*)(void))Class_PrintModuleList, 0);
}
// 54E6BC: using guessed type int dword_54E6BC;

//----- (004B0870) --------------------------------------------------------
char * Class_PrintModuleList(int a1)
{
  char *result; // eax
  signed int v3; // ecx
  signed int v4; // edx
  signed int v5; // esi
  int v6; // ecx
  int i; // ecx
  char *ppForm; // eax
  int v9; // ecx
  int v10; // ecx

  result = (char *)Rules_GetModuleConstructListHead(a1);
  v5 = v4;
  if ( result )
  {
    Output_WriteLongString(v3, result);
    Output_Write(v6, (int)asc_509610, v6);
    result = (char *)MessageHandler_EnumNext(a1, 0);
    for ( i = (int)result; result; i = (int)result )
    {
      ppForm = (char *)MessageHandler_GetRecordPPForm(a1, i);
      if ( ppForm )
      {
        Output_WriteLongString(v5, ppForm);
        Output_Write(v5, (int)asc_509610, v10);
      }
      result = (char *)MessageHandler_EnumNext(a1, v9);
    }
  }
  return result;
}
// 4B087C: variable 'v4' is possibly undefined
// 4B088A: variable 'v3' is possibly undefined
// 4B0896: variable 'v6' is possibly undefined
// 4B08C7: variable 'v10' is possibly undefined
// 4B08D0: variable 'v9' is possibly undefined

//----- (004B08E0) --------------------------------------------------------
int  Class_AddBusyReference(int result)
{
  ++*(_DWORD *)(result + 26);
  return result;
}

//----- (004B08F0) --------------------------------------------------------
int  Class_ReleaseBusyReference(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 26);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (004B0900) --------------------------------------------------------
BOOL  Class_PrepareUndefineCheck(double a1)
{
  int v1; // edx

  Instance_PrintClassInstanceSummary(a1);
  if ( !g_ClipsCurrentEvaluationDepth )
    g_ClipsCurrentEvaluationDepth = -1;
  Instance_PurgeDeletedInstances();
  g_ClipsCurrentEvaluationDepth = v1;
  return g_Clips_InstanceListHead == 0;
}
// 4B0926: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (004B0940) --------------------------------------------------------
int Class_InitHashTables()
{
  int i; // eax
  int result; // eax

  g_DefclassHashTable = (int)Mem_SmallBlockAlloc(0x29Cu);
  for ( i = 0; i != 668; i += 4 )
    *(_DWORD *)(g_DefclassHashTable + i) = 0;
  g_Defclass_SlotNameHashTablePtr = (int)Mem_SmallBlockAlloc(0x29Cu);
  for ( result = 0; result != 668; result += 4 )
    *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + result) = 0;
  return result;
}
// 51AD68: using guessed type int dword_51AD68;
// 51AD70: using guessed type int dword_51AD70;

//----- (004B09B0) --------------------------------------------------------
int  Class_FindSlotBySymbol(int theClass, int slotName)
{
  int slotIndex; // edx
  int result; // eax

  slotIndex = 0;
  if ( !*(_DWORD *)(theClass + 64) )
    return 0;
  for ( result = *(_DWORD *)(theClass + 52); slotName != *(_DWORD *)(*(_DWORD *)(result + 8) + 12); result += 44 )
  {
    if ( (unsigned int)++slotIndex >= *(_DWORD *)(theClass + 64) )
      return 0;
  }
  return result;
}

//----- (004B09E0) --------------------------------------------------------
int __fastcall Class_ReportLookupError(int a1, int className)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)aClassfun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToFindCl, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], className, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInFunction_1, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v6, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__21, v7);
  return Lexer_ErrorRecover(1);
}
// 4B0A02: variable 'v3' is possibly undefined
// 4B0A0E: variable 'v4' is possibly undefined
// 4B0A1D: variable 'v5' is possibly undefined
// 4B0A29: variable 'v6' is possibly undefined
// 4B0A38: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B0A50) --------------------------------------------------------
_DWORD * Mem_ReturnListToFreePool(_DWORD *result)
{
  _DWORD *i; // edx

  for ( i = result; result; i = result )
  {
    result = (_DWORD *)result[1];
    g_ClipsMemFreeListTemp = (int)i;
    *i = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B0AA0) --------------------------------------------------------
signed int  Class_PrintName(int theDefclass, int linefeedFlag)
{
  int v3; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  int Name; // eax
  int v7; // ecx
  int v8; // ecx
  signed int result; // eax
  int v10; // ecx

  v3 = Module_GetCurrent();
  if ( v3 != *v5 && (*(_BYTE *)(theDefclass + 20) & 2) == 0 )
  {
    Name = Module_GetName(**(_DWORD **)(theDefclass + 8));
    Output_Write(v7, Name, v7);
    Output_Write(v8, (int)asc_50964C, v8);
  }
  result = Output_Write(v4, *(_DWORD *)(*(_DWORD *)theDefclass + 16), v4);
  if ( linefeedFlag )
    return Output_Write(v10, (int)asc_509650, v10);
  return result;
}
// 4B0AAE: variable 'v5' is possibly undefined
// 4B0AC6: variable 'v7' is possibly undefined
// 4B0AD2: variable 'v8' is possibly undefined
// 4B0ADE: variable 'v4' is possibly undefined
// 4B0AF1: variable 'v10' is possibly undefined

//----- (004B0B00) --------------------------------------------------------
signed int  Class_PrintNameList(int logicalName, int headerString, unsigned __int16 *classList)
{
  int v3; // ecx
  unsigned int classIndex; // edi
  int listOffset; // esi

  Output_Write(logicalName, headerString, logicalName);
  classIndex = 0;
  listOffset = 0;
  while ( classIndex < *classList )
  {
    Output_Write(v3, (int)asc_509654, v3);
    listOffset += 4;
    ++classIndex;
    Class_PrintName(*(_DWORD *)(*(_DWORD *)(classList + 1) + listOffset - 4), 0);
  }
  return Output_Write(v3, (int)asc_509650, v3);
}
// 4B0B22: variable 'v3' is possibly undefined

//----- (004B0B50) --------------------------------------------------------
int  Class_AddToHashTable(int theClass)
{
  unsigned int bucket; // edx

  bucket = 11329 * ((unsigned int)(*(_DWORD *)(Rules_GetConstructNameSymbol(theClass) + 12) << 16) >> 18) % 0xA7u;
  *(_DWORD *)(theClass + 30) = bucket;
  *(_DWORD *)(theClass + 100) = *(_DWORD *)(g_DefclassHashTable + 4 * bucket);
  *(_DWORD *)(g_DefclassHashTable + 4 * bucket) = theClass;
  return bucket;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0BA0) --------------------------------------------------------
int  Class_RemoveFromHashTable(int theClass)
{
  int chainCursor; // eax
  int i; // ecx
  int result; // eax

  chainCursor = *(_DWORD *)(g_DefclassHashTable + 4 * *(_DWORD *)(theClass + 30));
  for ( i = 0; chainCursor != theClass; chainCursor = *(_DWORD *)(chainCursor + 100) )
    i = chainCursor;
  result = *(_DWORD *)(theClass + 100);
  if ( i )
    *(_DWORD *)(i + 100) = result;
  else
    *(_DWORD *)(4 * *(_DWORD *)(theClass + 30) + g_DefclassHashTable) = result;
  return result;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (004B0BF0) --------------------------------------------------------
signed int  Class_InsertLinkEntry(unsigned __int16 *linkArray, int newClass, int insertPosition)
{
  int old_count; // eax
  int old_items; // esi
  int new_items; // [esp+2h] [ebp-1Ah]
  int insert_slot; // edx
  unsigned __int16 new_count; // [esp+0h] [ebp-1Ch]

  old_count = *linkArray;
  new_items = (int)(uintptr_t)Mem_SmallBlockAlloc(4 * old_count + 4);
  old_items = *(_DWORD *)(linkArray + 1);
  if ( insertPosition == -1 )
  {
    qmemcpy(
      (void *)(uintptr_t)(unsigned int)new_items,
      (const void *)(uintptr_t)(unsigned int)old_items,
      4 * old_count);
    insert_slot = new_items + 4 * old_count;
  }
  else
  {
    if ( insertPosition )
      qmemcpy(
        (void *)(uintptr_t)(unsigned int)new_items,
        (const void *)(uintptr_t)(unsigned int)old_items,
        4 * insertPosition);
    insert_slot = new_items + 4 * insertPosition;
    qmemcpy(
      (void *)(uintptr_t)(unsigned int)(insert_slot + 4),
      (const void *)(uintptr_t)(unsigned int)(old_items + 4 * insertPosition),
      4 * (old_count - insertPosition));
  }
  *(_DWORD *)(uintptr_t)(unsigned int)insert_slot = newClass;
  new_count = old_count + 1;
  Class_FreeOrRecycleArray(linkArray, 0);
  *linkArray = new_count;
  *(_DWORD *)(linkArray + 1) = new_items;
  return new_items;
}

//----- (004B0CE0) --------------------------------------------------------
unsigned __int16  Class_RemoveLinkEntry(int superClass, int theClass)
{
  unsigned __int16 *array_header; // ebx
  unsigned int remove_index; // edx
  int byte_offset; // eax
  unsigned __int16 count; // ax
  int old_items; // esi
  int new_items; // [esp+2h] [ebp-16h]
  unsigned __int16 new_count; // [esp+0h] [ebp-18h]

  array_header = (unsigned __int16 *)(superClass + 40);
  old_items = *(_DWORD *)(array_header + 1);
  remove_index = 0;
  byte_offset = 0;
  while ( remove_index < *array_header
       && theClass != *(_DWORD *)(uintptr_t)(unsigned int)(old_items + byte_offset) )
  {
    byte_offset += 4;
    ++remove_index;
  }
  count = *array_header;
  if ( remove_index == count )
    return count;
  if ( count <= 1u )
  {
    new_items = 0;
  }
  else
  {
    new_items = (int)(uintptr_t)Mem_SmallBlockAlloc(4 * count - 4);
    if ( remove_index )
      qmemcpy(
        (void *)(uintptr_t)(unsigned int)new_items,
        (const void *)(uintptr_t)(unsigned int)old_items,
        4 * remove_index);
    qmemcpy(
      (void *)(uintptr_t)(unsigned int)(new_items + 4 * remove_index),
      (const void *)(uintptr_t)(unsigned int)(old_items + 4 * remove_index + 4),
      4 * (count - remove_index) - 4);
  }
  new_count = count - 1;
  Class_FreeOrRecycleArray(array_header, 0);
  *array_header = new_count;
  *(_DWORD *)(array_header + 1) = new_items;
  return (unsigned __int16)new_items;
}

//----- (004B0DC0) --------------------------------------------------------
int  Class_AllocateRecord(int classNameSymbol)
{
  int free_record; // edx
  int class_record; // ecx
  char v4; // ah
  char v5; // dl
  int watchInstancesFlag; // eax
  char v7; // bl
  int v8; // esi

  free_record = *(_DWORD *)(g_ClipsMemoryTable + 496);
  if ( free_record )
  {
    g_ClipsMemFreeListTemp = free_record;
    *(_DWORD *)(g_ClipsMemoryTable + 496) = *(_DWORD *)free_record;
    class_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    class_record = Mem_HeapAllocWithRetry((_DWORD *)0x7C);
  }
  sub_4A94D0_Impl((int)aDefclass_2, class_record, classNameSymbol);
  v4 = *(_BYTE *)(class_record + 20);
  *(_WORD *)(class_record + 24) = 0;
  *(_BYTE *)(class_record + 20) = v4 & 0xF0;
  v5 = *(_BYTE *)(class_record + 20);
  *(_DWORD *)(class_record + 26) = 0;
  v5 |= 8u;
  *(_BYTE *)(class_record + 20) = v5;
  watchInstancesFlag = g_Rules_WatchInstances & 1;
  *(_BYTE *)(class_record + 20) = v5 & 0xEF;
  *(_DWORD *)(class_record + 20) |= 16 * watchInstancesFlag;
  LOBYTE(watchInstancesFlag) = g_Class_WatchSlots[0];
  *(_DWORD *)(class_record + 30) = 0;
  *(_WORD *)(class_record + 34) = 0;
  *(_DWORD *)(class_record + 36) = 0;
  *(_WORD *)(class_record + 40) = 0;
  *(_DWORD *)(class_record + 42) = 0;
  *(_WORD *)(class_record + 46) = 0;
  *(_DWORD *)(class_record + 48) = 0;
  *(_DWORD *)(class_record + 52) = 0;
  *(_DWORD *)(class_record + 56) = 0;
  *(_DWORD *)(class_record + 60) = 0;
  *(_DWORD *)(class_record + 72) = 0;
  *(_DWORD *)(class_record + 68) = 0;
  *(_DWORD *)(class_record + 64) = 0;
  *(_DWORD *)(class_record + 76) = 0;
  *(_DWORD *)(class_record + 88) = 0;
  *(_DWORD *)(class_record + 92) = 0;
  *(_DWORD *)(class_record + 96) = 0;
  *(_DWORD *)(class_record + 80) = 0;
  v7 = *(_BYTE *)(class_record + 20);
  *(_DWORD *)(class_record + 84) = 0;
  *(_DWORD *)(class_record + 100) = 0;
  *(_BYTE *)(class_record + 20) = v7 & 0xDF;
  v8 = *(_DWORD *)(class_record + 20);
  *(_DWORD *)(class_record + 104) = 0;
  *(_DWORD *)(class_record + 20) = (32 * (watchInstancesFlag & 1)) | v8;
  Mem_AllocArray((_BYTE *)(class_record + 108), 16);
  return class_record;
}
// 51AD74: using guessed type int dword_51AD74;
// 51AD78: using guessed type int dword_51AD78[];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B0F00) --------------------------------------------------------
unsigned __int16 * Class_FreeOrRecycleArray(unsigned __int16 *result, int returnToPool)
{
  unsigned __int16 *arrayHeader; // ecx
  int items; // eax

  arrayHeader = result;
  if ( *result )
  {
    items = *(_DWORD *)(result + 1);
    result = (unsigned __int16 *)Mem_SmallBlockFree(
      (_DWORD *)(uintptr_t)(unsigned int)items,
      4 * *result);
    *arrayHeader = 0;
    *(_DWORD *)(arrayHeader + 1) = 0;
    if ( !returnToPool )
      return result;
    goto LABEL_5;
  }
  if ( returnToPool )
  {
LABEL_5:
    g_ClipsMemFreeListTemp = (int)arrayHeader;
    *(_DWORD *)arrayHeader = *(_DWORD *)(g_ClipsMemoryTable + 24);
    result = (unsigned __int16 *)g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4B0F27: variable 'v2' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B0F60) --------------------------------------------------------
__int16  Class_AssignID(int theClass)
{
  __int16 result; // ax
  unsigned int idIndex; // eax
  int tableOffset; // edx

  if ( !((unsigned __int16)g_ClipsDefclassIdCount % 30) )
  {
    g_ClipsDefclassIdTable = (int)Mem_Realloc(
                          (char *)g_ClipsDefclassIdTable,
                          4 * (unsigned __int16)g_ClipsDefclassIdCount,
                          4 * (unsigned __int16)g_ClipsDefclassIdCount + 120);
    idIndex = (unsigned __int16)g_ClipsDefclassIdCount;
    tableOffset = 4 * (unsigned __int16)g_ClipsDefclassIdCount;
    while ( idIndex < (unsigned int)(unsigned __int16)g_ClipsDefclassIdCount + 30 )
    {
      ++idIndex;
      *(_DWORD *)(g_ClipsDefclassIdTable + tableOffset) = 0;
      tableOffset += 4;
    }
  }
  *(_DWORD *)(4 * (unsigned __int16)g_ClipsDefclassIdCount + g_ClipsDefclassIdTable) = theClass;
  result = g_ClipsDefclassIdCount++;
  *(_WORD *)(theClass + 24) = result;
  return result;
}
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;

//----- (004B1010) --------------------------------------------------------
unsigned int * Class_InternSlotName(_DWORD *slotNameSymbol, int newSlotID, int useNewID)
{
  int slotNameID; // edi
  _DWORD *existingEntry; // ebx
  unsigned int i; // ecx
  _DWORD *freeNode; // ebx
  unsigned int *allocatedEntry; // eax
  unsigned int *newEntry; // ebx
  const char *slotNameStr; // edi
  char *prefixCursor; // esi
  _BYTE *destCursor; // edi
  char v15; // al
  char v16; // al
  char *nameCursor; // esi
  unsigned int prefixLen; // kr08_4
  char *appendCursor; // edi
  char v20; // al
  char v21; // al
  signed int *putSymbol; // eax
  unsigned int temp_name_bytes; // edx
  char *putName; // [esp-4h] [ebp-18h]
  _DWORD *putNameAlloc; // [esp+0h] [ebp-14h]

  slotNameID = newSlotID;
  existingEntry = *(_DWORD **)(g_Defclass_SlotNameHashTablePtr + 4 * (11329 * (slotNameSymbol[3] << 16 >> 18) % 0xA7u));
  for ( i = 11329 * (slotNameSymbol[3] << 16 >> 18) % 0xA7u; existingEntry; existingEntry = (_DWORD *)existingEntry[5] )
  {
    if ( slotNameSymbol == (_DWORD *)existingEntry[3] )
      break;
  }
  if ( existingEntry )
  {
    if ( useNewID )
    {
      if ( newSlotID != existingEntry[2] )
      {
        Rules_ReportSystemError(i, 1);
        IO_RunRouterExitCallbacks();
      }
    }
    ++existingEntry[1];
    return existingEntry;
  }
  else
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 112);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(g_ClipsMemoryTable + 112) = *freeNode;
      allocatedEntry = (unsigned int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      allocatedEntry = (unsigned int *)Mem_HeapAllocWithRetry((_DWORD *)0x1C);
    }
    allocatedEntry[1] = 1;
    allocatedEntry[3] = (unsigned int)slotNameSymbol;
    newEntry = allocatedEntry;
    *allocatedEntry = i;
    if ( !useNewID )
      slotNameID = Class_FindUnusedSlotNameID();
    newEntry[2] = slotNameID;
    newEntry[5] = *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * i);
    *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * i) = newEntry;
    slotNameStr = (const char *)slotNameSymbol[4];
    ++slotNameSymbol[1];
    prefixCursor = aPut_0;
    temp_name_bytes = strlen(slotNameStr) + 5;
    destCursor = Mem_SmallBlockAlloc(temp_name_bytes);
    putNameAlloc = destCursor;
    putName = destCursor;
    do
    {
      v15 = *prefixCursor;
      *destCursor = *prefixCursor;
      if ( !v15 )
        break;
      v16 = prefixCursor[1];
      prefixCursor += 2;
      destCursor[1] = v16;
      destCursor += 2;
    }
    while ( v16 );
    nameCursor = (char *)slotNameSymbol[4];
    prefixLen = strlen(putName) + 1;
    appendCursor = &putName[prefixLen - 1];
    do
    {
      v20 = *nameCursor;
      *appendCursor = *nameCursor;
      if ( !v20 )
        break;
      v21 = nameCursor[1];
      nameCursor += 2;
      appendCursor[1] = v21;
      appendCursor += 2;
    }
    while ( v21 );
    putSymbol = Str_Intern(putName, ~prefixLen);
    newEntry[4] = (unsigned int)putSymbol;
    ++putSymbol[1];
    Mem_SmallBlockFree(putNameAlloc, temp_name_bytes);
    newEntry[6] = 0;
    return newEntry;
  }
}
// 4B10B0: variable 'i' is possibly undefined
// 51AD70: using guessed type int dword_51AD70;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1180) --------------------------------------------------------
_DWORD * Class_ReleaseSlotName(_DWORD *result)
{
  int entry; // edx
  int previous; // ecx
  int ref_count; // ebx

  if ( result )
  {
    entry = *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * *result);
    previous = 0;
    while ( entry != (int)(uintptr_t)result )
    {
      previous = entry;
      entry = *(_DWORD *)(entry + 20);
    }
    ref_count = *(_DWORD *)(entry + 4) - 1;
    *(_DWORD *)(entry + 4) = ref_count;
    if ( !ref_count )
    {
      if ( previous )
      {
        *(_DWORD *)(previous + 20) = *(_DWORD *)(entry + 20);
      }
      else
      {
        *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * *(_DWORD *)entry) = *(_DWORD *)(entry + 20);
      }
      Rules_DecrementSymbolCount(*(_DWORD *)(entry + 12), entry);
      Rules_DecrementSymbolCount(*(_DWORD *)(entry + 16), entry);
      g_ClipsMemFreeListTemp = entry;
      *(_DWORD *)entry = *(_DWORD *)(g_ClipsMemoryTable + 112);
      result = (_DWORD *)g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 51AD70: using guessed type int dword_51AD70;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1210) --------------------------------------------------------
int  Class_DestroyRecord(int theClass)
{
  unsigned int i; // ecx
  int offset; // esi
  int slot; // eax
  int expression; // eax
  int count; // edi
  int handler; // edx
  int handler_name; // ecx
  int result; // eax

  i = 0;
  offset = 0;
  while ( i < *(unsigned __int16 *)(theClass + 34) )
  {
    offset += 4;
    Class_RemoveLinkEntry(*(_DWORD *)(*(_DWORD *)(theClass + 36) + offset - 4), theClass);
    ++i;
  }
  Class_RemoveFromHashTable(theClass);
  Class_SetInstallState((__int16 *)theClass, 0);
  Class_FreeOrRecycleArray((unsigned __int16 *)(theClass + 34), 0);
  Class_FreeOrRecycleArray((unsigned __int16 *)(theClass + 46), 0);
  Class_FreeOrRecycleArray((unsigned __int16 *)(theClass + 40), 0);
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(theClass + 64) )
  {
    slot = *(_DWORD *)(theClass + 52) + offset;
    expression = *(_DWORD *)(slot + 16);
    if ( expression )
    {
      if ( (*(_BYTE *)slot & 0x40) != 0 )
      {
        AST_FreePackedNodeChain(expression);
      }
      else
      {
        g_ClipsMemFreeListTemp = expression;
        *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
      }
    }
    Class_ReleaseSlotName((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 8));
    AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 20));
    ++i;
    offset += 44;
  }
  count = *(_DWORD *)(theClass + 72);
  if ( count )
  {
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(theClass + 56), 4 * count);
    Mem_SmallBlockFree(*(_DWORD **)(theClass + 60), 4 * (*(_DWORD *)(theClass + 76) + 1));
  }
  count = *(_DWORD *)(theClass + 64);
  if ( count )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(theClass + 52), 44 * count);
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(theClass + 96) )
  {
    handler = *(_DWORD *)(theClass + 88) + offset;
    expression = *(_DWORD *)(handler + 28);
    if ( expression )
      AST_FreePackedNodeChain(expression);
    handler_name = *(_DWORD *)(handler + 32);
    if ( handler_name )
      Mem_SmallBlockFree(
        (_DWORD *)(uintptr_t)(unsigned int)handler_name,
        strlen((const char *)(uintptr_t)(unsigned int)handler_name) + 1);
    ++i;
    offset += 36;
  }
  count = *(_DWORD *)(theClass + 96);
  if ( count )
  {
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(theClass + 88), 36 * count);
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(theClass + 92), 4 * count);
  }
  Rules_ReplaceConstructPPForm(theClass, 0);
  Class_ReleaseSlotIDMapEntry(*(unsigned __int16 *)(theClass + 24), 0);
  g_ClipsMemFreeListTemp = theClass;
  *(_DWORD *)theClass = *(_DWORD *)(g_ClipsMemoryTable + 496);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 496) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B13E0) --------------------------------------------------------
__int16 * Class_SetInstallState(__int16 *result, int install)
{
  int class_record; // ecx
  unsigned int i; // ebx
  int offset; // esi
  int slot; // edx
  int handler; // edx

  class_record = (int)(uintptr_t)result;
  if ( install )
  {
    if ( *(_BYTE *)(class_record + 20) & 1 )
      return result;
    *(_BYTE *)(class_record + 20) |= 1u;
    ++*(_DWORD *)(*(_DWORD *)class_record + 4);
    return result;
  }
  if ( (*(_BYTE *)(class_record + 20) & 1) == 0 )
    return result;
  *(_BYTE *)(class_record + 20) &= ~1u;
  Rules_DecrementSymbolCount(*(_DWORD *)class_record, class_record);
  Rules_DecrementBitmapCount(*(_DWORD *)(class_record + 104), class_record);
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(class_record + 64) )
  {
    slot = *(_DWORD *)(class_record + 52) + offset;
    Rules_DecrementSymbolCount(*(_DWORD *)(slot + 12), class_record);
    if ( *(_DWORD *)(slot + 16) )
    {
      if ( (*(_BYTE *)slot & 0x40) != 0 )
        AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 16));
      else
        Rules_ValueDeinstall(*(_DWORD *)(slot + 16), class_record);
    }
    ++i;
    offset += 44;
  }
  i = 0;
  offset = 0;
  while ( i < (unsigned int)*(_DWORD *)(class_record + 96) )
  {
    handler = *(_DWORD *)(class_record + 88) + offset;
    Rules_DecrementSymbolCount(*(_DWORD *)(handler + 8), class_record);
    if ( *(_DWORD *)(handler + 28) )
      AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(handler + 28));
    ++i;
    offset += 36;
  }
  return result;
}

//----- (004B14B0) --------------------------------------------------------
signed int  Class_HierarchyHasInstances(int theClass)
{
  int subclassOffset; // ecx
  int v4; // edx
  int v5; // ecx

  if ( *(_DWORD *)(theClass + 26) )
    return 1;
  subclassOffset = 0;
  if ( *(_WORD *)(theClass + 40) )
  {
    while ( !Class_HierarchyHasInstances(*(_DWORD *)(subclassOffset + *(_DWORD *)(theClass + 42))) )
    {
      subclassOffset = v5 + 4;
      if ( v4 + 1 >= (unsigned int)*(unsigned __int16 *)(theClass + 40) )
        return 0;
    }
    return 1;
  }
  return 0;
}
// 4B14E7: variable 'v5' is possibly undefined
// 4B14EA: variable 'v4' is possibly undefined

//----- (004B1500) --------------------------------------------------------
signed int Class_RemoveAllDeletableClasses()
{
  int success; // ebx
  int i; // ecx
  int v3; // edx
  int constructName; // eax
  int v5; // ecx

  success = 1;
  if ( Rules_IsBloaded() )
    return 0;
  for ( i = Class_GetNextRecord(0); i; i = Class_GetNextRecord(i) )
  {
    if ( (*(_BYTE *)(i + 20) & 2) == 0 )
      break;
  }
  while ( i )
  {
    Class_GetNextRecord(i);
    if ( Class_IsDeletable() )
    {
      Rules_UnlinkListNode(v3);
      Class_DestroyRecord(v3);
    }
    else
    {
      constructName = Rules_GetConstructNameString(v3);
      success = 0;
      Rules_ReportCantDeleteItem(v5, constructName);
    }
  }
  return success;
}
// 4B1528: variable 'i' is possibly undefined
// 4B1542: variable 'v3' is possibly undefined
// 4B156F: variable 'v5' is possibly undefined

//----- (004B1580) --------------------------------------------------------
int  Class_DeleteRecursive(int theClass)
{
  int v2; // ecx
  int subclassCount; // eax
  int result; // eax
  int v5; // edx

  if ( *(_WORD *)(theClass + 40) )
  {
    while ( 1 )
    {
      Class_DeleteRecursive(**(_DWORD **)(theClass + 42));
      subclassCount = *(unsigned __int16 *)(theClass + 40);
      if ( (unsigned __int16)subclassCount == v2 )
        return v2 ^ subclassCount;
      if ( !*(_WORD *)(theClass + 40) )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    result = Class_IsDeletable();
    if ( result )
    {
      Rules_UnlinkListNode(v5);
      Class_DestroyRecord(v5);
      return 1;
    }
  }
  return result;
}
// 4B15A6: variable 'v2' is possibly undefined
// 4B15C6: variable 'v5' is possibly undefined

//----- (004B15E0) --------------------------------------------------------
int  Class_MarkBitmapSubclasses(int bitmap, int theClass, int setBit)
{
  unsigned __int16 classID; // cx
  _BYTE *bytePtr; // esi
  int result; // eax
  unsigned int v8; // ecx
  int subclassOffset; // esi

  classID = *(_WORD *)(theClass + 24);
  bytePtr = (_BYTE *)(((int)classID >> 3) + bitmap);
  if ( setBit )
  {
    result = 1 << (classID % 8);
    *bytePtr |= result;
  }
  else
  {
    result = ~(1 << (classID % 8));
    *bytePtr &= result;
  }
  v8 = 0;
  subclassOffset = 0;
  while ( v8 < *(unsigned __int16 *)(theClass + 40) )
  {
    subclassOffset += 4;
    result = Class_MarkBitmapSubclasses(bitmap, *(_DWORD *)(*(_DWORD *)(theClass + 42) + subclassOffset - 4), setBit);
  }
  return result;
}
// 4B1631: variable 'v8' is possibly undefined

//----- (004B1690) --------------------------------------------------------
signed int  Class_FindSlotNameID(int slotNameSymbol)
{
  int current; // eax
  unsigned int bucket_index; // edx

  bucket_index = 11329 * ((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)slotNameSymbol + 12) << 16 >> 18) % 0xA7u;
  current = *(_DWORD *)((uintptr_t)(unsigned int)g_Defclass_SlotNameHashTablePtr + 4 * bucket_index);
  while ( current )
  {
    if ( slotNameSymbol == *(_DWORD *)((uintptr_t)(unsigned int)current + 12) )
      break;
    current = *(_DWORD *)((uintptr_t)(unsigned int)current + 20);
  }
  if ( current )
    return *(_DWORD *)((uintptr_t)(unsigned int)current + 8);
  else
    return -1;
}
// 51AD70: using guessed type int dword_51AD70;

//----- (004B16F0) --------------------------------------------------------
int  Class_GetSlotNameByID(int slotNameID)
{
  int result; // eax

  result = Class_FindSlotNameEntryByID(slotNameID);
  if ( result )
    return *(_DWORD *)(result + 12);
  return result;
}

//----- (004B1700) --------------------------------------------------------
int  Class_FindSlotNameEntryByID(int slotNameID)
{
  int bucketOffset; // ecx
  int result; // eax

  bucketOffset = 0;
  while ( 1 )
  {
    result = *(_DWORD *)(bucketOffset + g_Defclass_SlotNameHashTablePtr);
    if ( result )
      break;
LABEL_5:
    bucketOffset += 4;
    if ( bucketOffset >= 668 )
      return 0;
  }
  while ( slotNameID != *(_DWORD *)(result + 8) )
  {
    result = *(_DWORD *)(result + 20);
    if ( !result )
      goto LABEL_5;
  }
  return result;
}
// 51AD70: using guessed type int dword_51AD70;

//----- (004B1730) --------------------------------------------------------
signed int Class_NewTraversalID()
{
  int i; // edi
  int j; // ebx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  if ( (unsigned __int8)g_Class_TraversalIDCounter >= 0x80u )
  {
    Rules_PrintErrorID((int)aClassfun, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMaximumNumberO, v3);
    Rules_PrintLongInteger(v4, 128);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__21, v5);
    Lexer_ErrorRecover(1);
    return -1;
  }
  else
  {
    for ( i = 0; i != 668; i += 4 )
    {
      for ( j = *(_DWORD *)(i + g_DefclassHashTable); j; j = *(_DWORD *)(j + 100) )
        *(_BYTE *)(j + (unsigned __int8)g_Class_TraversalIDCounter / 8 + 108) &= ~(1 << ((unsigned __int8)g_Class_TraversalIDCounter % 8));
    }
    return (unsigned __int8)g_Class_TraversalIDCounter++;
  }
}
// 4B17D3: variable 'v3' is possibly undefined
// 4B17E2: variable 'v4' is possibly undefined
// 4B17F1: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD68: using guessed type int dword_51AD68;
// 51ADA0: using guessed type char byte_51ADA0;

//----- (004B1810) --------------------------------------------------------
void Class_ReleaseTraversalID()
{
  --g_Class_TraversalIDCounter;
}
// 51ADA0: using guessed type char byte_51ADA0;

//----- (004B1820) --------------------------------------------------------
unsigned int  Class_HashClassName(int classNameSymbol)
{
  return 11329 * (*(_DWORD *)(classNameSymbol + 12) << 16 >> 18) % 0xA7u;
}

//----- (004B1860) --------------------------------------------------------
int Class_FindUnusedSlotNameID()
{
  int candidateID; // ecx
  unsigned int bucketIndex; // ebx
  int bucketOffset; // esi
  int i; // eax

  candidateID = 0;
LABEL_2:
  bucketIndex = 0;
  bucketOffset = 0;
  do
  {
    for ( i = *(_DWORD *)(bucketOffset + g_Defclass_SlotNameHashTablePtr); i; i = *(_DWORD *)(i + 20) )
    {
      if ( candidateID == *(_DWORD *)(i + 8) )
        break;
    }
    if ( i )
    {
      ++candidateID;
      goto LABEL_2;
    }
    ++bucketIndex;
    bucketOffset += 4;
  }
  while ( bucketIndex < 0xA7 );
  return candidateID;
}
// 4B1898: conditional instruction was optimized away because ebx.4<A7u
// 51AD70: using guessed type int dword_51AD70;

//----- (004B18C0) --------------------------------------------------------
int  Class_ReleaseSlotIDMapEntry(int classID, int a2)
{
  int idCursor; // ecx
  unsigned int scanIndex; // ebx
  int result; // eax
  int tableOffset; // esi
  int cursorOffset; // esi
  int shrinkPending; // edi
  int oldTableSize; // [esp+0h] [ebp-20h]

  idCursor = classID;
  scanIndex = classID + 1;
  result = g_ClipsDefclassIdTable;
  tableOffset = 4 * scanIndex;
  *(_DWORD *)(g_ClipsDefclassIdTable + 4 * idCursor) = 0;
  while ( scanIndex < (unsigned __int16)g_ClipsDefclassIdCount )
  {
    if ( *(_DWORD *)(g_ClipsDefclassIdTable + tableOffset) )
      return result;
    tableOffset += 4;
    ++scanIndex;
  }
  cursorOffset = 4 * idCursor;
  shrinkPending = 0;
  while ( !*(_DWORD *)(g_ClipsDefclassIdTable + cursorOffset) )
  {
    result = (unsigned __int16)idCursor / 30;
    g_ClipsDefclassIdCount = idCursor;
    if ( !((unsigned __int16)idCursor % 30) )
    {
      a2 = (unsigned __int16)idCursor;
      if ( !shrinkPending )
      {
        shrinkPending = 1;
        oldTableSize = (unsigned __int16)idCursor + 30;
      }
    }
    if ( !idCursor )
      break;
    cursorOffset -= 4;
    --idCursor;
  }
  if ( shrinkPending )
  {
    result = (int)Mem_Realloc((char *)g_ClipsDefclassIdTable, 4 * oldTableSize, 4 * a2);
    g_ClipsDefclassIdTable = result;
  }
  return result;
}
// 4B1971: variable 'v8' is possibly undefined
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;

//----- (004B1990) --------------------------------------------------------
int  Rules_EvaluatePatternQueryExpression(_DWORD *returnValue, double a2)
{
  int savedDelayFlag; // eax
  double v4; // st7
  int v5; // ecx
  int v6; // ecx

  savedDelayFlag = Rules_SetObjectPatternMatchDelay(1, a2);
  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), returnValue, savedDelayFlag, v4);
  if ( !g_ClipsEvaluationError )
    return Rules_SetObjectPatternMatchDelay(v5, v4);
  Rules_SetEvaluationErrorFlag(0);
  Lexer_ErrorRecover(0);
  Rules_SetObjectPatternMatchDelay(v6, v4);
  return Lexer_ErrorRecover(1);
}
// 4B19A8: variable 'v4' is possibly undefined
// 4B19C6: variable 'v6' is possibly undefined
// 4B19DA: variable 'v5' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;

//----- (004B19F0) --------------------------------------------------------
int  Rules_SetObjectPatternMatchDelay(int delayFlag, double a2)
{
  int oldFlag; // ecx

  oldFlag = g_Rules_ObjectMatchDelayFlag;
  if ( delayFlag )
  {
    g_Rules_ObjectMatchDelayFlag = 1;
  }
  else
  {
    g_Rules_ObjectMatchDelayFlag = 0;
    Rules_ObjectMatchAction(0, 0, -1, a2);
  }
  return oldFlag;
}
// 4B1A05: variable 'v2' is possibly undefined
// 51AEB4: using guessed type int dword_51AEB4;

//----- (004B1A40) --------------------------------------------------------
int Rules_GetObjectPatternNetworkRoot()
{
  return g_Rules_ObjectPatternNetworkRoot;
}
// 51AEAC: using guessed type int dword_51AEAC;

//----- (004B1A50) --------------------------------------------------------
int Rules_GetReactiveRuleList()
{
  return g_ReactiveRuleListHead;
}
// 51AEB0: using guessed type int dword_51AEB0;

//----- (004B1A60) --------------------------------------------------------
int  Rules_SetObjectPatternNetworkRoot(int result)
{
  g_Rules_ObjectPatternNetworkRoot = result;
  return result;
}
// 51AEAC: using guessed type int dword_51AEAC;

//----- (004B1A70) --------------------------------------------------------
int  Rules_SetReactiveRuleList(int result)
{
  g_ReactiveRuleListHead = result;
  return result;
}
// 51AEB0: using guessed type int dword_51AEB0;

//----- (004B1A80) --------------------------------------------------------
void  Rules_ObjectMatchAction(unsigned __int16 *actionType, _DWORD *theInstance, signed int slotNameID, double a4)
{
  unsigned __int16 *slotBitmap; // ebx

  if ( !g_Rules_JoinOperationInProgress )
  {
    g_Rules_ObjectMatchTimeTag = g_Rules_EntityTimeTagCounter;
    g_Rules_JoinOperationInProgress = 1;
    ++g_Rules_EntityTimeTagCounter;
    if ( theInstance )
    {
      if ( g_Rules_ObjectMatchDelayFlag )
      {
        Rules_EnqueueObjectMatchAction(actionType, (uintptr_t)theInstance, slotNameID);
        goto LABEL_6;
      }
      if ( !actionType )
        goto LABEL_5;
      if ( (unsigned int)actionType <= 1 )
      {
        Rules_AssertNewObjectIntoNetwork((int)theInstance, a4);
        goto LABEL_6;
      }
      if ( actionType == (unsigned __int16 *)2 )
      {
        Rules_RetractObjectPatternMatches(theInstance, 0, a4);
      }
      else
      {
LABEL_5:
        slotBitmap = Rules_GrowSlotBitmapSetBit(0, slotNameID);
        Rules_ReassertObjectSlotChange(theInstance, slotBitmap, a4);
        Mem_SmallBlockFree(slotBitmap, ((int)*slotBitmap >> 3) + 3);
      }
    }
LABEL_6:
    Rules_FlushQueuedObjectMatchActions(a4);
    g_Rules_JoinOperationInProgress = 0;
    Rules_FlushPendingDependencyDestructors();
  }
}
// 4B1AD1: variable 'v5' is possibly undefined
// 51A954: using guessed type int dword_51A954;
// 51A998: using guessed type int dword_51A998;
// 51AEB4: using guessed type int dword_51AEB4;
// 51AEBC: using guessed type int dword_51AEBC;

//----- (004B1B30) --------------------------------------------------------
int Rules_ResetRuleMarkCounters()
{
  int result; // eax
  _DWORD *ruleCursor; // edx

  result = g_RuleTraversalMarkCounter + 1;
  if ( g_RuleTraversalMarkCounter + 1 < (unsigned int)g_RuleTraversalMarkCounter )
  {
    result = g_ReactiveRuleListHead;
    g_RuleTraversalMarkCounter = 0;
    ruleCursor = (_DWORD *)g_ReactiveRuleListHead;
    if ( g_ReactiveRuleListHead )
    {
      do
      {
LABEL_3:
        result = ruleCursor[7];
        ruleCursor[4] = 0;
        if ( result )
        {
          while ( *(_DWORD *)(result + 4) )
          {
            *(_DWORD *)(result + 4) = 0;
            result = *(_DWORD *)(result + 20);
            if ( !result )
            {
              ruleCursor = (_DWORD *)ruleCursor[9];
              if ( ruleCursor )
                goto LABEL_3;
              return result;
            }
          }
        }
        ruleCursor = (_DWORD *)ruleCursor[9];
      }
      while ( ruleCursor );
    }
  }
  return result;
}
// 51AEB0: using guessed type int dword_51AEB0;
// 51AEB8: using guessed type int dword_51AEB8;

//----- (004B1B90) --------------------------------------------------------
unsigned __int16 * Rules_EnqueueObjectMatchAction(unsigned __int16 *result, uintptr_t a2, signed int slotNameID)
{
  uintptr_t change_kind; // ebp
  uintptr_t instance; // esi
  uintptr_t node; // ecx
  uintptr_t previous; // ebx
  uintptr_t bitmap; // edx/eax
  uintptr_t new_node; // edi/eax

  change_kind = (uintptr_t)result;
  instance = a2;
  node = (uintptr_t)(unsigned int)g_ClipsObjectMatchQueueHead;
  previous = 0;
  while ( node )
  {
    if ( instance == (uintptr_t)(unsigned int)*(_DWORD *)(node + 4) )
    {
      if ( *(_DWORD *)node == 1 )
      {
        if ( change_kind == 2 )
        {
          if ( previous )
            *(_DWORD *)(previous + 12) = *(_DWORD *)(node + 12);
          else
            g_ClipsObjectMatchQueueHead = *(_DWORD *)(node + 12);
          --*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(node + 4) + 40);
          return (unsigned __int16 *)Rules_FreeQueuedObjectMatchNode((_DWORD *)node);
        }
        return result;
      }
      if ( change_kind == 2 )
      {
        bitmap = (uintptr_t)(unsigned int)*(_DWORD *)(node + 8);
        *(_DWORD *)node = (int)change_kind;
        if ( bitmap )
        {
          Mem_SmallBlockFree((void *)bitmap, (((int)*(unsigned __int16 *)bitmap) >> 3) + 3);
          *(_DWORD *)(node + 8) = 0;
        }
        return result;
      }
      bitmap = (uintptr_t)Rules_GrowSlotBitmapSetBit(
        (unsigned __int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8),
        slotNameID);
      *(_DWORD *)(node + 8) = (int)bitmap;
      return (unsigned __int16 *)bitmap;
    }
    previous = node;
    node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 12);
  }

  if ( *(_DWORD *)(g_ClipsMemoryTable + 64) )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(g_ClipsMemoryTable + 64) = *(_DWORD *)(uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
    new_node = (uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
  }
  else
  {
    new_node = (uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  *(_DWORD *)new_node = (int)change_kind;
  *(_DWORD *)(new_node + 12) = 0;
  if ( change_kind == 3 )
    bitmap = (uintptr_t)Rules_GrowSlotBitmapSetBit(0, slotNameID);
  else
    bitmap = 0;
  *(_DWORD *)(new_node + 8) = (int)bitmap;
  *(_DWORD *)(new_node + 4) = (int)instance;
  ++*(_DWORD *)(instance + 40);
  if ( previous )
    *(_DWORD *)(previous + 12) = (int)new_node;
  else
    g_ClipsObjectMatchQueueHead = (int)new_node;
  return (unsigned __int16 *)bitmap;
}
// 51AEA8: using guessed type int dword_51AEA8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1CA0) --------------------------------------------------------
unsigned __int16 * Rules_GrowSlotBitmapSetBit(unsigned __int16 *oldBitmap, signed int bitIndex)
{
  unsigned __int16 *bitmap; // [esp+0h] [ebp-18h]
  unsigned __int16 bit_capacity; // [esp+4h] [ebp-14h]
  int allocation_size; // edx
  int old_size; // edx
  char *target_byte; // edi

  if ( oldBitmap && bitIndex <= *oldBitmap )
  {
    bitmap = oldBitmap;
  }
  else
  {
    bit_capacity = 2 * bitIndex;
    allocation_size = ((int)bit_capacity >> 3) + 3;
    bitmap = (unsigned __int16 *)Mem_SmallBlockAlloc(allocation_size);
    Mem_AllocArray((_BYTE *)bitmap, allocation_size);
    if ( oldBitmap )
    {
      old_size = ((int)*oldBitmap >> 3) + 3;
      qmemcpy(bitmap, oldBitmap, old_size);
      Mem_SmallBlockFree(oldBitmap, old_size);
    }
    *bitmap = bit_capacity;
  }
  target_byte = (char *)bitmap + ((bitIndex - (__CFSHL__(bitIndex >> 31, 3) + 8 * (bitIndex >> 31))) >> 3);
  target_byte[2] |= 1 << (bitIndex % 8);
  return bitmap;
}

//----- (004B1D80) --------------------------------------------------------
int  Rules_FreeQueuedObjectMatchNode(_DWORD *theNode)
{
  _DWORD *v1; // ecx
  _DWORD *slotBitmap; // edx
  int result; // eax

  v1 = theNode;
  slotBitmap = (_DWORD *)theNode[2];
  if ( slotBitmap )
    Mem_SmallBlockFree(slotBitmap, ((int)*(unsigned __int16 *)slotBitmap >> 3) + 3);
  g_ClipsMemFreeListTemp = (int)v1;
  *v1 = *(_DWORD *)(g_ClipsMemoryTable + 64);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  return result;
}
// 4B1D90: variable 'v1' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B1DD0) --------------------------------------------------------
int  Rules_FlushQueuedObjectMatchActions(double a1)
{
  uintptr_t queued_change; // ecx
  uintptr_t instance; // eax
  uintptr_t slot_bitmap; // edx
  int change_kind; // eax
  int result; // eax

  result = 0;
  if ( g_ClipsObjectMatchQueueHead )
  {
    while ( g_ClipsObjectMatchQueueHead && !g_Rules_ObjectMatchDelayFlag )
    {
      queued_change = (uintptr_t)(unsigned int)g_ClipsObjectMatchQueueHead;
      g_ClipsObjectMatchQueueHead = *(_DWORD *)(queued_change + 12);
      change_kind = *(_DWORD *)queued_change;
      instance = (uintptr_t)(unsigned int)*(_DWORD *)(queued_change + 4);
      slot_bitmap = (uintptr_t)(unsigned int)*(_DWORD *)(queued_change + 8);
      if ( change_kind == 1 )
      {
        Rules_AssertNewObjectIntoNetwork((int)instance, a1);
      }
      else if ( change_kind == 2 )
      {
        Rules_RetractObjectPatternMatches((_DWORD *)instance, (unsigned __int16 *)slot_bitmap, a1);
      }
      else
      {
        Rules_ReassertObjectSlotChange((_DWORD *)instance, (unsigned __int16 *)slot_bitmap, a1);
      }
      --*(_DWORD *)(instance + 40);
      result = Rules_FreeQueuedObjectMatchNode((_DWORD *)queued_change);
    }
  }
  return result;
}
// 51AEA8: using guessed type int dword_51AEA8;
// 51AEB4: using guessed type int dword_51AEB4;

//----- (004B1E40) --------------------------------------------------------
char  Rules_MarkDependentRulesForSlotChange(unsigned __int16 *slotBitmap)
{
  uintptr_t rule; // ebx
  uintptr_t slot_record; // edx
  unsigned int slot_id; // [esp+0h] [ebp-1Ch]
  unsigned int slot_byte; // edi
  unsigned char slot_mask; // cl
  uintptr_t rule_bitmap_owner; // eax
  unsigned int rule_bitmap; // eax
  uintptr_t dependency_owner; // eax
  unsigned int dependency_bitmap; // edx
  uintptr_t dependent; // eax
  int mark_id; // ebp

  Rules_ResetRuleMarkCounters();
  ++g_RuleTraversalMarkCounter;
  rule = (uintptr_t)(unsigned int)g_ReactiveRuleListHead;
  slot_record = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 44);
  slot_id = *(unsigned __int16 *)(slot_record + 24);
  slot_mask = 1 << (slot_id & 7);
  slot_byte = slot_id >> 3;
  while ( rule )
  {
    if ( !g_IncrementalResetInProgress || (*(_BYTE *)(rule + 12) & 8) != 0 )
    {
      rule_bitmap_owner = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 20);
      rule_bitmap = rule_bitmap_owner ? *(_DWORD *)(rule_bitmap_owner + 16) : 0;
      if ( rule_bitmap
        && *(unsigned __int16 *)(uintptr_t)(unsigned int)rule_bitmap >= slot_id
        && (*(_BYTE *)((uintptr_t)(unsigned int)rule_bitmap + slot_byte + 2) & slot_mask) != 0 )
      {
        if ( slotBitmap )
        {
          dependency_owner = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 24);
          dependency_bitmap = dependency_owner ? *(_DWORD *)(dependency_owner + 16) : 0;
          if ( !dependency_bitmap
            || !Rules_BitmapsIntersect(slotBitmap, (unsigned __int16 *)(uintptr_t)(unsigned int)dependency_bitmap) )
            goto next_rule;
        }
        mark_id = g_RuleTraversalMarkCounter;
        *(_DWORD *)(rule + 16) = mark_id;
        for ( dependent = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 28);
              dependent;
              dependent = (uintptr_t)(unsigned int)*(_DWORD *)(dependent + 20) )
        {
          if ( *(_DWORD *)(dependent + 4) == mark_id )
            break;
          *(_DWORD *)(dependent + 4) = mark_id;
        }
      }
    }
next_rule:
    rule = (uintptr_t)(unsigned int)*(_DWORD *)(rule + 36);
  }
  return 0;
}
// 51AEB0: using guessed type int dword_51AEB0;
// 51AEB8: using guessed type int dword_51AEB8;
// 51B354: using guessed type int dword_51B354;
// 51B478: using guessed type int dword_51B478;

//----- (004B1F50) --------------------------------------------------------
signed int  Rules_BitmapsIntersect(unsigned __int16 *bitmap1, unsigned __int16 *bitmap2)
{
  unsigned __int16 minBits; // ax
  unsigned __int16 i; // dx

  minBits = *bitmap1;
  if ( *bitmap1 >= (int)*bitmap2 )
    minBits = *bitmap2;
  for ( i = 0; i <= (int)minBits >> 3; ++i )
  {
    if ( (*((_BYTE *)bitmap2 + i + 2) & *((_BYTE *)bitmap1 + i + 2)) != 0 )
      return 1;
  }
  return 0;
}

//----- (004B1FC0) --------------------------------------------------------
_DWORD * Rules_TraverseObjectPatternNetwork(_DWORD *result, _DWORD *patternNode, int endMark, double a4)
{
  int offset; // esi
  _DWORD *patternCursor; // ecx
  unsigned int slotNameID; // ebx
  int savedFieldCount; // ebp
  int slotValue; // eax
  int savedSlotNode; // [esp+0h] [ebp-14h]

  offset = (int)result;
  patternCursor = patternNode;
  while ( patternCursor )
  {
    while ( 1 )
    {
      if ( g_RuleTraversalMarkCounter == patternCursor[1] )
      {
        slotNameID = patternCursor[2];
        if ( slotNameID > 1 )
        {
          if ( !g_ObjectPatternActiveClassNode || *(_DWORD *)(*(_DWORD *)(*(_DWORD *)g_ObjectPatternActiveClassNode + 8) + 8) != slotNameID )
          {
            slotValue = *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 72)
                           + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 44) + 60) + 4 * patternCursor[2])
                           - 4);
            g_ObjectPatternActiveClassNode = slotValue;
            offset = 0;
            if ( (**(_BYTE **)slotValue & 2) != 0 )
              g_ObjectPatternMatchFieldCount = *(_DWORD *)(*(_DWORD *)(slotValue + 8) + 6);
            else
              g_ObjectPatternMatchFieldCount = 1;
          }
        }
        else
        {
          offset = 0;
          g_ObjectPatternActiveClassNode = 0;
          g_ObjectPatternMatchFieldCount = 1;
        }
        savedSlotNode = g_ObjectPatternActiveClassNode;
        savedFieldCount = g_ObjectPatternMatchFieldCount;
        Rules_MatchObjectPatternNode(offset, (int)patternCursor, endMark, a4);
        g_ObjectPatternMatchFieldCount = savedFieldCount;
        g_ObjectPatternActiveClassNode = savedSlotNode;
      }
      result = (_DWORD *)(*patternCursor & 1);
      if ( result == (_DWORD *)1 )
        break;
      patternCursor = (_DWORD *)patternCursor[7];
      if ( !patternCursor )
        return result;
    }
    *(_BYTE *)patternCursor &= ~1u;
    result = patternCursor;
    patternCursor = (_DWORD *)patternCursor[7];
    if ( patternCursor )
    {
      while ( patternCursor[2] == result[2] && *patternCursor << 21 >> 24 == *result << 21 >> 24 )
      {
        patternCursor = (_DWORD *)patternCursor[7];
        if ( !patternCursor )
          return result;
      }
    }
  }
  return result;
}
// 4B1FE5: simplified comparisons for 'ebx.4': !=0 && !=1 became >=2u
// 4B2021: variable 'v5' is possibly undefined
// 51AEB8: using guessed type int dword_51AEB8;
// 51B478: using guessed type int dword_51B478;
// 51B47C: using guessed type int dword_51B47C;
// 51B480: using guessed type int dword_51B480;

//----- (004B2110) --------------------------------------------------------
int  Rules_MatchObjectPatternNode(int offset, int patternNode, int endMark, double a4)
{
  int whichField; // edx
  int fieldPosition; // ebp
  int *alphaNodeList; // eax
  int result; // eax
  int networkTest; // ebx
  _DWORD *freeNode; // ebx
  _DWORD *newMarker; // eax
  int slotNameRecord; // edx
  _DWORD *theMarker; // edi
  int markerPosition; // edx
  int savedSlotNode; // [esp+4h] [ebp-20h]
  int savedFieldCount; // [esp+8h] [ebp-1Ch]
  int i; // [esp+10h] [ebp-14h]

  whichField = *(_DWORD *)patternNode << 21 >> 24;
  fieldPosition = offset + whichField;
  if ( !g_ObjectPatternActiveClassNode )
  {
    if ( *(_DWORD *)(patternNode + 12) )
    {
      result = Rules_EvaluatePatternConstraint(fieldPosition, 0, (_BYTE *)patternNode, *(_DWORD *)(patternNode + 12), a4);
      if ( !result )
        return result;
    }
    if ( !*(_DWORD *)(patternNode + 32) )
      return Rules_TraverseObjectPatternNetwork(offset, *(_DWORD *)(patternNode + 16), endMark, a4);
    alphaNodeList = *(int **)(patternNode + 32);
LABEL_5:
    Rules_AssertObjectPatternMatch(alphaNodeList, a4);
    return Rules_TraverseObjectPatternNetwork(offset, *(_DWORD *)(patternNode + 16), endMark, a4);
  }
  if ( (*(_BYTE *)patternNode & 2) != 0 )
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 80);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
      *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeNode;
      newMarker = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newMarker = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
    }
    *newMarker = whichField;
    slotNameRecord = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)g_ObjectPatternActiveClassNode + 8) + 12);
    newMarker[4] = 0;
    newMarker[1] = slotNameRecord;
    newMarker[2] = fieldPosition;
    theMarker = newMarker;
    if ( g_ObjectPatternMarkerListHead )
      *(_DWORD *)(endMark + 16) = newMarker;
    else
      g_ObjectPatternMarkerListHead = (int)newMarker;
    if ( (*(_BYTE *)patternNode & 4) != 0 )
    {
      newMarker[3] = g_ObjectPatternMatchFieldCount;
      if ( !*(_DWORD *)(patternNode + 12) || Rules_EvaluatePatternConstraint(fieldPosition, (int)newMarker, (_BYTE *)patternNode, *(_DWORD *)(patternNode + 12), a4) )
      {
        if ( *(_DWORD *)(patternNode + 32) )
          Rules_AssertObjectPatternMatch(*(int **)(patternNode + 32), a4);
        Rules_TraverseObjectPatternNetwork(0, *(_DWORD *)(patternNode + 16), (int)theMarker, a4);
      }
    }
    else
    {
      savedFieldCount = g_ObjectPatternMatchFieldCount;
      savedSlotNode = g_ObjectPatternActiveClassNode;
      markerPosition = newMarker[2];
      newMarker[3] = markerPosition - 1;
      for ( i = savedFieldCount - markerPosition - (*(_DWORD *)patternNode << 13 >> 24) + 2; i > 0; ++theMarker[3] )
      {
        if ( !*(_DWORD *)(patternNode + 12) || Rules_EvaluatePatternConstraint(fieldPosition, (int)theMarker, (_BYTE *)patternNode, *(_DWORD *)(patternNode + 12), a4) )
        {
          if ( *(_DWORD *)(patternNode + 32) )
            Rules_AssertObjectPatternMatch(*(int **)(patternNode + 32), a4);
          Rules_TraverseObjectPatternNetwork(offset + theMarker[3] - fieldPosition, *(_DWORD *)(patternNode + 16), (int)theMarker, a4);
          g_ObjectPatternMatchFieldCount = savedFieldCount;
          g_ObjectPatternActiveClassNode = savedSlotNode;
        }
        --i;
      }
    }
    if ( theMarker == (_DWORD *)g_ObjectPatternMarkerListHead )
      g_ObjectPatternMarkerListHead = 0;
    else
      *(_DWORD *)(endMark + 16) = 0;
    g_ClipsMemFreeListTemp = (int)theMarker;
    *theMarker = *(_DWORD *)(g_ClipsMemoryTable + 80);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
  }
  else
  {
    networkTest = *(_DWORD *)(patternNode + 12);
    if ( !networkTest || (result = Rules_EvaluatePatternConstraint(offset + whichField, 0, (_BYTE *)patternNode, networkTest, a4)) != 0 )
    {
      if ( !*(_DWORD *)(patternNode + 32) )
        return Rules_TraverseObjectPatternNetwork(offset, *(_DWORD *)(patternNode + 16), endMark, a4);
      alphaNodeList = *(int **)(patternNode + 32);
      goto LABEL_5;
    }
  }
  return result;
}
// 51B47C: using guessed type int dword_51B47C;
// 51B480: using guessed type int dword_51B480;
// 51B484: using guessed type int dword_51B484;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B2350) --------------------------------------------------------
int * Rules_AssertObjectPatternMatch(int *result, double a2)
{
  int pattern; // edi
  int partial_match; // esi
  int link_record; // eax
  int free_record; // ebx
  int join; // ecx

  pattern = (int)(uintptr_t)result;
  while ( pattern )
  {
    if ( g_RuleTraversalMarkCounter == *(_DWORD *)((uintptr_t)(unsigned int)pattern + 16) )
    {
      ++*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 40);
      partial_match = Rules_AppendExpressionValueNode(g_ClipsObjectReteCurrentInstance, (_DWORD *)(uintptr_t)(unsigned int)g_ObjectPatternMarkerListHead, (signed int *)(uintptr_t)(unsigned int)pattern);
      free_record = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48);
      if ( free_record )
      {
        g_ClipsMemFreeListTemp = free_record;
        *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 48) = *(_DWORD *)(uintptr_t)(unsigned int)free_record;
        link_record = g_ClipsMemFreeListTemp;
      }
      else
      {
        link_record = Mem_HeapAllocWithRetry((_DWORD *)0xC);
      }
      *(_DWORD *)(uintptr_t)(unsigned int)link_record = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 16);
      *(_DWORD *)((uintptr_t)(unsigned int)link_record + 8) = pattern;
      *(_DWORD *)((uintptr_t)(unsigned int)link_record + 4) = partial_match;
      *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsObjectReteCurrentInstance + 16) = link_record;
      join = *(_DWORD *)((uintptr_t)(unsigned int)pattern + 8);
      while ( join )
      {
        result = Rules_DriveJoinNetwork(
                   (int *)(uintptr_t)(unsigned int)partial_match,
                   (char *)(uintptr_t)(unsigned int)join,
                   1,
                   a2);
        join = *(_DWORD *)((uintptr_t)(unsigned int)join + 32);
      }
    }
    pattern = *(_DWORD *)((uintptr_t)(unsigned int)pattern + 32);
  }
  return result;
}
// 51AEB8: using guessed type int dword_51AEB8;
// 51B478: using guessed type int dword_51B478;
// 51B484: using guessed type int dword_51B484;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B2410) --------------------------------------------------------
int  Rules_EvaluatePatternConstraint(int objectSlotField, int selfSlotMarker, _BYTE *patternNode, int theTest, double a5)
{
  int testHead; // eax
  int orClause; // esi
  int result; // eax
  int savedExpression; // ebp
  _BYTE *v11; // ecx
  int andClause; // esi
  _DWORD evalResult[2]; // [esp+0h] [ebp-28h] BYREF
  int resultValue; // [esp+8h] [ebp-20h]
  int v15; // [esp+18h] [ebp-10h]

  v15 = objectSlotField;
  if ( *(_WORD *)theTest == 50 )
  {
    savedExpression = g_ClipsCurrentExpression;
    g_ClipsCurrentExpression = theTest;
    result = Rules_EvalObjectSlotBoundVariableEqual(*(_DWORD *)(theTest + 2), (int)evalResult, (int)patternNode, a5);
    g_ClipsCurrentExpression = savedExpression;
    if ( result )
    {
      if ( **(char **)(*(_DWORD *)(theTest + 2) + 16) < 0 )
        *v11 |= 1u;
      return 1;
    }
  }
  else
  {
    testHead = *(_DWORD *)(theTest + 2);
    if ( testHead == g_ClipsSymbolOr )
    {
      orClause = *(_DWORD *)(theTest + 6);
      if ( orClause )
      {
        while ( !Rules_EvaluatePatternConstraint(v15, selfSlotMarker, (int)patternNode, orClause, a5) )
        {
          *patternNode &= ~1u;
          orClause = *(_DWORD *)(orClause + 10);
          if ( !orClause )
            return 0;
        }
        result = 1;
        *patternNode &= ~1u;
      }
      else
      {
        return 0;
      }
    }
    else if ( testHead == g_Clips_SymbolAnd )
    {
      andClause = *(_DWORD *)(theTest + 6);
      if ( andClause )
      {
        while ( 1 )
        {
          result = Rules_EvaluatePatternConstraint(v15, selfSlotMarker, (int)patternNode, andClause, a5);
          if ( !result )
            break;
          *patternNode &= ~1u;
          andClause = *(_DWORD *)(andClause + 10);
          if ( !andClause )
            return 1;
        }
        *patternNode &= ~1u;
      }
      else
      {
        return 1;
      }
    }
    else
    {
      g_ClipsHaltExecution = 0;
      if ( Parser_ParseForm((__int16 *)theTest, evalResult, (int)patternNode, a5) )
      {
        Rules_PrintObjectPatternNetworkError();
        g_ClipsEvaluationError = 0;
        g_ClipsHaltExecution = 0;
        return 0;
      }
      else if ( resultValue == g_ClipsFalseSymbol && evalResult[1] == 2 )
      {
        return g_ClipsFalseSymbol ^ resultValue;
      }
      else
      {
        return 1;
      }
    }
  }
  return result;
}
// 4B248F: variable 'v11' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51A968: using guessed type int dword_51A968;
// 54DD70: using guessed type int dword_54DD70;
// 54E65C: using guessed type int dword_54E65C;
// 54E664: using guessed type int dword_54E664;

//----- (004B2550) --------------------------------------------------------
_DWORD * Rules_AssertNewObjectIntoNetwork(int theInstance, double a2)
{
  *(_DWORD *)(theInstance + 12) = g_Rules_ObjectMatchTimeTag;
  g_ClipsObjectReteCurrentInstance = theInstance;
  g_ObjectPatternActiveClassNode = 0;
  Rules_MarkDependentRulesForSlotChange(0);
  return Rules_TraverseObjectPatternNetwork(0, (_DWORD *)g_Rules_ObjectPatternNetworkRoot, 0, a2);
}
// 51AEAC: using guessed type int dword_51AEAC;
// 51AEBC: using guessed type int dword_51AEBC;
// 51B478: using guessed type int dword_51B478;
// 51B47C: using guessed type int dword_51B47C;

//----- (004B2590) --------------------------------------------------------
_DWORD * Rules_ReassertObjectSlotChange(_DWORD *theInstance, unsigned __int16 *slotBitmap, double a3)
{
  theInstance[3] = g_Rules_ObjectMatchTimeTag;
  Rules_RetractObjectPatternMatches(theInstance, slotBitmap, a3);
  g_ClipsObjectReteCurrentInstance = (int)(uintptr_t)theInstance;
  g_ObjectPatternActiveClassNode = 0;
  Rules_MarkDependentRulesForSlotChange(slotBitmap);
  return Rules_TraverseObjectPatternNetwork(0, (_DWORD *)g_Rules_ObjectPatternNetworkRoot, 0, a3);
}
// 51AEAC: using guessed type int dword_51AEAC;
// 51AEBC: using guessed type int dword_51AEBC;
// 51B478: using guessed type int dword_51B478;
// 51B47C: using guessed type int dword_51B47C;

//----- (004B25D0) --------------------------------------------------------
_DWORD * Rules_RetractObjectPatternMatches(_DWORD *result, unsigned __int16 *slotBitmap, double a3)
{
  uintptr_t instance; // ebx
  unsigned int current_link; // ecx
  unsigned int previous_link; // esi
  unsigned int removed_links; // edi
  unsigned int next_link; // eax
  unsigned int pattern; // eax
  unsigned int dependency; // edx
  unsigned int dependency_bitmap; // edx
  unsigned int link; // ecx
  int saved_rule_head; // edx

  instance = (uintptr_t)result;
  if ( !slotBitmap )
  {
    current_link = *(_DWORD *)(instance + 16);
    if ( current_link )
    {
      for ( link = current_link; link; link = *(_DWORD *)(uintptr_t)link )
        --*(_DWORD *)(instance + 40);
      result = (_DWORD *)Rules_RetractFactFromNetwork((_DWORD *)(uintptr_t)current_link, a3);
      *(_DWORD *)(instance + 16) = 0;
    }
    return result;
  }

  current_link = *(_DWORD *)(instance + 16);
  previous_link = 0;
  removed_links = 0;
  while ( current_link )
  {
    uintptr_t link_record = (uintptr_t)current_link;
    pattern = *(_DWORD *)(link_record + 8);
    dependency = pattern ? *(_DWORD *)((uintptr_t)pattern + 24) : 0;
    dependency_bitmap = dependency ? *(_DWORD *)((uintptr_t)dependency + 16) : 0;
    if ( dependency_bitmap
      && Rules_BitmapsIntersect(slotBitmap, (unsigned __int16 *)(uintptr_t)dependency_bitmap) )
    {
      --*(_DWORD *)(instance + 40);
      next_link = *(_DWORD *)link_record;
      if ( previous_link )
        *(_DWORD *)(uintptr_t)previous_link = next_link;
      else
        *(_DWORD *)(instance + 16) = next_link;
      *(_DWORD *)link_record = removed_links;
      removed_links = current_link;
      current_link = next_link;
    }
    else
    {
      previous_link = current_link;
      current_link = *(_DWORD *)link_record;
    }
  }

  if ( removed_links )
  {
    saved_rule_head = *(_DWORD *)(instance + 4);
    *(_DWORD *)(instance + 4) = 0;
    result = (_DWORD *)Rules_RetractFactFromNetwork((_DWORD *)(uintptr_t)removed_links, a3);
    *(_DWORD *)(instance + 4) = saved_rule_head;
  }
  return result;
}

//----- (004B2680) --------------------------------------------------------
signed int Rules_PrintObjectPatternNetworkError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // ecx
  int v10; // ecx
  int *v11; // ecx
  int v12; // ecx

  Rules_PrintErrorID((int)aObjrtmch, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOcc_2, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCurrentlyAct_0, v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(g_ClipsObjectReteCurrentInstance + 28) + 16), v2);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_509714, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aProblemResid_2, v4);
  v6 = Class_GetSlotNameByID(*(_DWORD *)(v5 + 8));
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v6 + 16), v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField, v8);
  Rules_PrintLongInteger((int)v9, *v9 << 21 >> 24);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_509740, v10);
  Rules_PrintObjectPatternErrorDetail(1, v11, (int)v11);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_509740, v12);
}
// 4B26A0: variable 'v0' is possibly undefined
// 4B26AF: variable 'v1' is possibly undefined
// 4B26C4: variable 'v2' is possibly undefined
// 4B26D3: variable 'v3' is possibly undefined
// 4B26E2: variable 'v4' is possibly undefined
// 4B26E7: variable 'v5' is possibly undefined
// 4B26F7: variable 'v7' is possibly undefined
// 4B2706: variable 'v8' is possibly undefined
// 4B2718: variable 'v9' is possibly undefined
// 4B2727: variable 'v10' is possibly undefined
// 4B2733: variable 'v11' is possibly undefined
// 4B2742: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B478: using guessed type int dword_51B478;

//----- (004B2750) --------------------------------------------------------
int  Rules_PrintObjectPatternErrorDetail(int result, int *patternNode, int j)
{
  int stopAfterFirst; // esi
  int *i; // ebx
  int alphaNode; // edx
  _DWORD *v6; // ecx
  int v7; // ecx
  int v8; // ecx

  stopAfterFirst = result;
  for ( i = patternNode; i; i = (int *)i[7] )
  {
    alphaNode = i[8];
    if ( alphaNode )
    {
      for ( j = *(_DWORD *)(alphaNode + 8); j; j = *(_DWORD *)(v8 + 32) )
      {
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfPattern, j);
        Rules_PrintLongInteger((int)v6, *v6 << 16 >> 25);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInRuleS, v7);
        Rules_PrintJoinNetworkSharingReport();
      }
    }
    result = Rules_PrintObjectPatternErrorDetail(0, i[4], j);
    if ( stopAfterFirst )
      break;
  }
  return result;
}
// 4B2792: variable 'v6' is possibly undefined
// 4B27A1: variable 'v7' is possibly undefined
// 4B27AF: variable 'v8' is possibly undefined
// 4B27BB: variable 'j' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B2840) --------------------------------------------------------
BOOL  Method_CharRestrictionAllowsType(int typeChar, char *constraints)
{
  BOOL result; // eax
  char v5; // bh
  char v6; // dh

  if ( !constraints || (*constraints & 1) != 0 )
    return 1;
  switch ( typeChar )
  {
    case 'a':
      return *constraints < 0;
    case 'b':
    case 'c':
    case 'w':
      return (*constraints & 2) != 0;
    case 'd':
    case 'f':
      return (*constraints & 8) != 0;
    case 'i':
    case 'l':
      return (*constraints & 0x10) != 0;
    case 'j':
      v5 = *constraints;
      return (*constraints & 2) != 0 || (v5 & 4) != 0 || (v5 & 0x20) != 0;
    case 'k':
      v6 = *constraints;
      return (*constraints & 2) != 0 || (v6 & 4) != 0;
    case 'm':
      return constraints[1] < 0;
    case 'n':
      return (*constraints & 0x10) != 0 || (*constraints & 8) != 0;
    case 'o':
      if ( (*constraints & 0x20) != 0 )
        return 1;
      goto LABEL_29;
    case 's':
      return (*constraints & 4) != 0;
    case 'v':
LABEL_29:
      result = 0;
      break;
    case 'x':
      if ( (*constraints & 0x40) != 0 )
        return 1;
      result = 0;
      break;
    default:
      return 1;
  }
  return result;
}

//----- (004B2900) --------------------------------------------------------
BOOL  Method_TypeCodeAllowsRestriction(BOOL result, int constraints)
{
  if ( result == 105 )
    return 0;
  if ( !constraints )
    return 1;
  if ( (*(_DWORD *)constraints & 1) == 1 )
    return 1;
  if ( result == 2 && (*(_BYTE *)constraints & 2) == 0 || result == 3 && (*(_BYTE *)constraints & 4) == 0 )
    return 0;
  if ( result || (*(_BYTE *)constraints & 8) != 0 )
    return (result != 1 || (*(_BYTE *)constraints & 0x10) != 0)
        && (result != 8 || (*(_BYTE *)constraints & 0x20) != 0)
        && (result != 7 || (*(_BYTE *)constraints & 0x40) != 0)
        && (result != 5 || *(char *)constraints < 0)
        && (result != 6 || (*(_BYTE *)(constraints + 1) & 1) != 0);
  return result;
}

//----- (004B2990) --------------------------------------------------------
BOOL  Method_ParamCountInRange(int number, int constraints)
{
  int minRestriction; // ecx
  int minExpr; // ebx
  int maxRestriction; // ebp
  int maxExpr; // ecx
  BOOL result; // eax

  result = 1;
  if ( constraints )
  {
    minRestriction = *(_DWORD *)(constraints + 18);
    if ( minRestriction )
    {
      minExpr = *(_DWORD *)(minRestriction + 2);
      if ( minExpr != g_Clips_NegativeInfinitySymbol && number < *(_DWORD *)(minExpr + 16) )
        return 0;
    }
    maxRestriction = *(_DWORD *)(constraints + 22);
    if ( maxRestriction )
    {
      maxExpr = *(_DWORD *)(maxRestriction + 2);
      if ( maxExpr != g_ClipsPositiveInfinitySymbol && number > *(_DWORD *)(maxExpr + 16) )
        return 0;
    }
  }
  return result;
}
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B29E0) --------------------------------------------------------
BOOL  Method_ParamRangeInBounds(int minCount, int maxCount, int constraints)
{
  int maxRestriction; // esi
  int minRestriction; // eax
  int minExpr; // ecx
  BOOL result; // eax

  result = 1;
  if ( constraints )
  {
    maxRestriction = *(_DWORD *)(constraints + 22);
    if ( maxRestriction )
    {
      if ( g_ClipsPositiveInfinitySymbol != *(_DWORD *)(maxRestriction + 2) && minCount > *(_DWORD *)(*(_DWORD *)(maxRestriction + 2) + 16) )
        return 0;
    }
    minRestriction = *(_DWORD *)(constraints + 18);
    if ( minRestriction )
    {
      if ( maxCount != -1 )
      {
        minExpr = *(_DWORD *)(minRestriction + 2);
        if ( minExpr != g_Clips_NegativeInfinitySymbol && maxCount < *(_DWORD *)(minExpr + 16) )
          return 0;
      }
    }
  }
  return result;
}
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B2A60) --------------------------------------------------------
signed int  Method_QueryRestrictionAllowsType(int type, int value, int constraints)
{
  char v5; // ah
  __int16 *restrictionList; // eax
  signed int result; // eax
  char v8; // ah
  char v9; // ah
  char v10; // dh
  char v11; // dh

  if ( !constraints )
    return 1;
  switch ( type )
  {
    case 0:
      v5 = *(_BYTE *)(constraints + 1);
      if ( (v5 & 0x10) == 0 && (v5 & 2) == 0 )
        goto LABEL_22;
      goto LABEL_5;
    case 1:
      v11 = *(_BYTE *)(constraints + 1);
      if ( (v11 & 0x20) == 0 && (v11 & 2) == 0 )
        goto LABEL_22;
      goto LABEL_5;
    case 2:
      v8 = *(_BYTE *)(constraints + 1);
      if ( (v8 & 4) != 0 || (v8 & 2) != 0 )
        goto LABEL_5;
      return 1;
    case 3:
      v10 = *(_BYTE *)(constraints + 1);
      if ( (v10 & 8) != 0 || (v10 & 2) != 0 )
        goto LABEL_5;
      return 1;
    case 8:
      v9 = *(_BYTE *)(constraints + 1);
      if ( (v9 & 0x40) != 0 || (v9 & 2) != 0 )
      {
LABEL_5:
        restrictionList = *(__int16 **)(constraints + 6);
        if ( !restrictionList )
          return 0;
        while ( *restrictionList != type || value != *(_DWORD *)(restrictionList + 1) )
        {
          restrictionList = *(__int16 **)(restrictionList + 5);
          if ( !restrictionList )
            return 0;
        }
LABEL_22:
        result = 1;
      }
      else
      {
        result = 1;
      }
      break;
    default:
      goto LABEL_22;
  }
  return result;
}

//----- (004B2B10) --------------------------------------------------------
signed int  Rules_ValueSatisfiesRangeConstraint(unsigned int type, int value, int constraints)
{
  __int16 *minList; // esi
  __int16 *maxList; // edi

  if ( !constraints || type > 1 )
    return 1;
  minList = *(__int16 **)(constraints + 10);
  maxList = *(__int16 **)(constraints + 14);
  if ( !minList )
    return 0;
  while ( !Rules_CompareBoundedCEValues(type, value, *(_DWORD *)(minList + 1), *minList) || Rules_CompareBoundedCEValues(type, value, *(_DWORD *)(maxList + 1), *maxList) == 1 )
  {
    minList = *(__int16 **)(minList + 5);
    maxList = *(__int16 **)(maxList + 5);
    if ( !minList )
      return 0;
  }
  return 1;
}
// 4B2B23: simplified comparisons for 'eax.4': !=1 && !=0 became >=2u

//----- (004B2B90) --------------------------------------------------------
signed int  Rules_PrintConstraintViolationMessage(
        int theWhat,
        int thePlace,
        int thePattern,
        int commandFlag,
        int theSlot,
        int theField,
        int violationType,
        int theConstraint,
        int printPrelude)
{
  int v12; // ecx
  int v13; // ecx
  char *v14; // edx
  int v15; // ecx
  int v16; // ecx
  char *v17; // edx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx

  v12 = violationType;
  if ( !printPrelude )
    goto LABEL_12;
  if ( violationType == 4 )
  {
    Rules_PrintErrorID((int)aCstrnchk_1, 1, 1);
    v14 = aTheFunctionRet;
  }
  else
  {
    if ( !theWhat )
      goto LABEL_5;
    Rules_PrintErrorID((int)aCstrnchk_1, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], theWhat, v19);
    v14 = asc_50979C;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v14, v13);
LABEL_5:
  if ( thePlace )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundIn_0, v12);
    if ( commandFlag )
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe, v15);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], thePlace, v15);
    if ( commandFlag )
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCommand_0, v12);
  }
  if ( thePattern > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInCe, v12);
    Rules_PrintLongInteger(v16, thePattern);
  }
LABEL_12:
  switch ( v12 )
  {
    case 1:
    case 4:
      v17 = aDoesNotMatchTh;
LABEL_14:
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v17, v12);
      break;
    case 2:
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotFallInT, 2);
      Rules_PrintConstraintRange((int)g_IO_LogicalNameTable_WError[0], theConstraint);
      break;
    case 3:
      v17 = aDoesNotMatch_0;
      goto LABEL_14;
    case 5:
      v17 = aDoesNotSatisfy;
      goto LABEL_14;
  }
  if ( theSlot )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForSlot, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theSlot + 16), v20);
  }
  else if ( theField > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForField, v12);
    Rules_PrintLongInteger(v21, theField);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__29, v12);
}
// 4B2BD2: variable 'v13' is possibly undefined
// 4B2BE8: variable 'v12' is possibly undefined
// 4B2BFB: variable 'v15' is possibly undefined
// 4B2C3C: variable 'v16' is possibly undefined
// 4B2D35: variable 'v21' is possibly undefined
// 4B2CA5: variable 'v19' is possibly undefined
// 4B2D15: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B2D40) --------------------------------------------------------
signed int  Rules_PrintConstraintRange(int logicalName, int theConstraint)
{
  int minList; // edx
  int v4; // ecx
  int v5; // ecx
  int maxList; // edx

  minList = *(_DWORD *)(theConstraint + 10);
  if ( g_Clips_NegativeInfinitySymbol == *(_DWORD *)(minList + 2) )
    Output_Write(logicalName, *(_DWORD *)(g_Clips_NegativeInfinitySymbol + 16), logicalName);
  else
    Rules_PrintFieldExprList(logicalName, (__int16 *)minList);
  Output_Write(v4, (int)aTo_1, v4);
  maxList = *(_DWORD *)(theConstraint + 14);
  if ( g_ClipsPositiveInfinitySymbol == *(_DWORD *)(maxList + 2) )
    return Output_Write(v5, *(_DWORD *)(g_ClipsPositiveInfinitySymbol + 16), v5);
  else
    return Rules_PrintFieldExprList(v5, (__int16 *)maxList);
}
// 4B2D64: variable 'v4' is possibly undefined
// 4B2D7C: variable 'v5' is possibly undefined
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B2DA0) --------------------------------------------------------
signed int  Rules_CheckFieldAgainstConstraint(_DWORD *theData, int theConstraint)
{
  int fieldIndex; // esi
  __int16 *fieldPtr; // ecx
  signed int result; // eax
  int v7; // ecx

  if ( !theConstraint )
    return 0;
  if ( theData[1] != 4 )
  {
    if ( Method_ParamCountInRange(1, theConstraint) )
      return Rules_CheckValueAgainstConstraint(theData[1], theData[2], theConstraint);
    else
      return 5;
  }
  if ( !Method_ParamCountInRange(theData[4] - theData[3] + 1, theConstraint) )
    return 5;
  fieldIndex = theData[3];
  if ( fieldIndex > theData[4] )
    return 0;
  fieldPtr = (__int16 *)(6 * fieldIndex + theData[2] + 14);
  while ( 1 )
  {
    result = Rules_CheckValueAgainstConstraint(*fieldPtr, *(_DWORD *)(fieldPtr + 1), theConstraint);
    if ( result )
      break;
    ++fieldIndex;
    fieldPtr = (__int16 *)(v7 + 6);
    if ( fieldIndex > theData[4] )
      return 0;
  }
  return result;
}
// 4B2DF7: variable 'v7' is possibly undefined

//----- (004B2E40) --------------------------------------------------------
signed int  Rules_CheckValueAgainstConstraint(unsigned int type, int value, int theConstraint)
{
  int v6; // ecx
  char *v7; // ecx

  if ( !Method_TypeCodeAllowsRestriction(type, theConstraint) )
    return 1;
  if ( !Method_QueryRestrictionAllowsType(type, value, theConstraint) )
    return 3;
  if ( !Rules_ValueSatisfiesRangeConstraint(type, value, v6) )
    return 2;
  if ( type != 10 || Method_CharRestrictionAllowsType(*(unsigned __int8 *)(value + 8), v7) )
    return 0;
  return 4;
}
// 4B2E79: variable 'v6' is possibly undefined
// 4B2E9D: variable 'v7' is possibly undefined

//----- (004B2EB0) --------------------------------------------------------
signed int  Rules_CheckFieldExprListAgainstConstraint(int *theExpression, int theConstraint)
{
  int *exprCursor; // edx
  int minFields; // ecx
  int i; // esi
  int v7; // edx
  int *checkCursor; // ecx
  signed int result; // eax
  int v10; // ecx
  char returnTypeChar; // bl

  exprCursor = theExpression;
  minFields = 0;
  for ( i = 0; exprCursor; exprCursor = *(int **)(v7 + 10) )
  {
    if ( Rules_TagIsConstantType(*(__int16 *)exprCursor)
      || *(_WORD *)v7 == 10 && (returnTypeChar = *(_BYTE *)(*(_DWORD *)(v7 + 2) + 8), returnTypeChar != 109) && returnTypeChar != 117 )
    {
      ++minFields;
    }
    else
    {
      i = -1;
    }
  }
  if ( !i )
    i = minFields;
  if ( !Method_ParamRangeInBounds(minFields, i, theConstraint) )
    return 5;
  checkCursor = theExpression;
  if ( !theExpression )
    return 0;
  while ( 1 )
  {
    result = Rules_CheckValueAgainstConstraint(*(__int16 *)checkCursor, *(int *)((char *)checkCursor + 2), theConstraint);
    if ( result )
      break;
    checkCursor = *(int **)(v10 + 10);
    if ( !checkCursor )
      return 0;
  }
  return result;
}
// 4B2ECF: variable 'v5' is possibly undefined
// 4B2ED0: variable 'v7' is possibly undefined
// 4B2F03: variable 'v10' is possibly undefined

//----- (004B2F40) --------------------------------------------------------
signed int  Rules_CheckExprTreeAgainstConstraint(__int16 *theExpression, int theConstraint)
{
  signed int result; // eax
  int v5; // ecx
  int v6; // ecx

  result = 0;
  if ( theConstraint && theExpression )
  {
    do
    {
      result = Rules_CheckValueAgainstConstraint(*theExpression, *(_DWORD *)(theExpression + 1), theConstraint);
      if ( result )
        break;
      result = Rules_CheckExprTreeAgainstConstraint(*(_DWORD *)(v5 + 6), theConstraint);
      if ( result )
        break;
      theExpression = *(__int16 **)(v6 + 10);
    }
    while ( theExpression );
  }
  return result;
}
// 4B2F68: variable 'v5' is possibly undefined
// 4B2F74: variable 'v6' is possibly undefined

//----- (004B2F80) --------------------------------------------------------
char * Rules_ConstraintIsUnmatchable(char *result)
{
  char typeFlags; // dl
  char highFlags; // dh

  if ( result )
  {
    typeFlags = *result;
    result = (char *)((*result & 1) == 0
                   && (typeFlags & 2) == 0
                   && (typeFlags & 4) == 0
                   && (typeFlags & 8) == 0
                   && (typeFlags & 0x10) == 0
                   && (typeFlags & 0x20) == 0
                   && (typeFlags & 0x40) == 0
                   && (highFlags = result[1], highFlags >= 0)
                   && typeFlags >= 0
                   && (highFlags & 1) == 0);
  }
  return result;
}

//----- (004B2FC7) --------------------------------------------------------
int  IO_ScanfGetChar(int (**streamOps)(void))
{
  return (*streamOps)();
}

//----- (004B2FCE) --------------------------------------------------------
int __fastcall IO_ScanfUngetChar(int ch, int streamOps)
{
  return (*(int (__thiscall **)(int))(streamOps + 4))(ch);
}

//----- (004B2FD6) --------------------------------------------------------
signed int  IO_ScanfParseFormat(int streamContext, unsigned __int8 *formatString, int *argList)
{
  int assignedCount; // ebp
  int charsConsumed; // edi
  unsigned __int8 *formatCharPtr; // ebx
  int formatChar; // ebx
  int v8; // ecx
  unsigned __int8 *specEnd; // eax
  unsigned int convChar; // ebx
  bool isHexConv; // zf
  int radix; // ebx
  int v13; // eax
  int fieldResult; // eax
  unsigned __int8 *formatPtr; // [esp+0h] [ebp-18h] BYREF
  int argCursor[5]; // [esp+4h] [ebp-14h] BYREF

  formatPtr = formatString;
  argCursor[0] = *argList;
  assignedCount = 0;
  charsConsumed = 0;
  *(_BYTE *)(streamContext + 16) &= ~2u;
  while ( 1 )
  {
    formatCharPtr = formatPtr++;
    formatChar = *formatCharPtr;
    if ( !formatChar )
      break;
    if ( (IsTable[(unsigned __int8)(formatChar + 1)] & 2) != 0 )
    {
      charsConsumed += IO_ScanfSkipWhitespace(streamContext);
      goto LABEL_64;
    }
    if ( formatChar != 37 )
    {
      if ( IO_ScanfGetChar((int (**)(void))streamContext) != formatChar )
        goto LABEL_7;
LABEL_63:
      ++charsConsumed;
      goto LABEL_64;
    }
    specEnd = IO_ScanfParseFieldSpec(formatPtr, streamContext);
    formatPtr = specEnd;
    convChar = *specEnd;
    if ( *specEnd )
      formatPtr = specEnd + 1;
    if ( convChar < 0x64 )
    {
      if ( convChar < 0x47 )
      {
        if ( convChar < 0x43 )
        {
          if ( convChar != 37 )
            goto LABEL_64;
          if ( IO_ScanfGetChar((int (**)(void))streamContext) != 37 )
          {
LABEL_7:
            if ( (*(_BYTE *)(streamContext + 16) & 2) == 0 )
              IO_ScanfUngetChar(v8, streamContext);
            break;
          }
          goto LABEL_63;
        }
        if ( convChar <= 0x43 )
        {
          *(_BYTE *)(streamContext + 16) |= 0x20u;
LABEL_57:
          fieldResult = IO_ScanfReadCharField(streamContext, argCursor, (_WORD *)streamContext);
LABEL_58:
          if ( fieldResult <= 0 )
            break;
          charsConsumed += fieldResult;
          if ( (*(_BYTE *)(streamContext + 16) & 1) != 0 )
            ++assignedCount;
          goto LABEL_64;
        }
        if ( convChar == 69 )
        {
LABEL_52:
          IO_ScanfReadFloatField(streamContext, argCursor);
          goto LABEL_58;
        }
      }
      else
      {
        if ( convChar <= 0x47 )
          goto LABEL_52;
        if ( convChar < 0x58 )
        {
          if ( convChar == 83 )
          {
            *(_BYTE *)(streamContext + 16) |= 0x20u;
LABEL_54:
            IO_ScanfReadStringField(streamContext, argCursor, (unsigned __int8 *)streamContext);
            goto LABEL_58;
          }
        }
        else
        {
          if ( convChar <= 0x58 )
          {
LABEL_51:
            radix = 16;
LABEL_46:
            v13 = streamContext;
LABEL_47:
            fieldResult = IO_ScanfReadIntegerField(v13, argCursor, radix);
            goto LABEL_58;
          }
          if ( convChar >= 0x5B )
          {
            if ( convChar <= 0x5B )
            {
              fieldResult = IO_ScanfReadScansetField(argCursor, (int *)&formatPtr, (_BYTE *)streamContext);
              goto LABEL_58;
            }
            if ( convChar == 99 )
              goto LABEL_57;
          }
        }
      }
    }
    else
    {
      if ( convChar <= 0x64 )
      {
        radix = 10;
        goto LABEL_46;
      }
      if ( convChar < 0x6F )
      {
        if ( convChar < 0x69 )
        {
          if ( convChar <= 0x67 )
            goto LABEL_52;
        }
        else
        {
          if ( convChar <= 0x69 )
          {
            v13 = streamContext;
            radix = 0;
            goto LABEL_47;
          }
          if ( convChar == 110 )
            IO_ScanfStoreScanCount(streamContext, argCursor, charsConsumed);
        }
      }
      else
      {
        if ( convChar <= 0x6F )
        {
          radix = 8;
          goto LABEL_46;
        }
        if ( convChar < 0x73 )
        {
          isHexConv = convChar == 112;
        }
        else
        {
          if ( convChar <= 0x73 )
            goto LABEL_54;
          if ( convChar < 0x75 )
            goto LABEL_64;
          if ( convChar <= 0x75 )
          {
            radix = 10;
            v13 = streamContext;
            goto LABEL_47;
          }
          isHexConv = convChar == 120;
        }
        if ( isHexConv )
          goto LABEL_51;
      }
    }
LABEL_64:
    if ( (*(_BYTE *)(streamContext + 16) & 2) != 0 )
    {
      if ( *formatPtr == 37 )
      {
        ++formatPtr;
        formatPtr = IO_ScanfParseFieldSpec(formatPtr, streamContext);
        if ( *formatPtr == 110 )
          IO_ScanfStoreScanCount(streamContext, argCursor, charsConsumed);
      }
      break;
    }
  }
  if ( assignedCount || (*(_BYTE *)(streamContext + 16) & 2) == 0 )
    return assignedCount;
  else
    return -1;
}
// 4B304C: variable 'v8' is possibly undefined
// 4B31CD: variable 'v14' is possibly undefined

//----- (004B324A) --------------------------------------------------------
unsigned __int8 * IO_ScanfParseFieldSpec(unsigned __int8 *result, int streamContext)
{
  char flagsByte; // dl
  int fieldWidth; // edx
  unsigned __int8 sizeChar; // dl
  char newFlags; // dh
  int digitChar; // [esp+0h] [ebp-10h]

  flagsByte = *(_BYTE *)(streamContext + 16) | 1;
  *(_BYTE *)(streamContext + 16) = flagsByte;
  *(_DWORD *)(streamContext + 12) = -1;
  *(_BYTE *)(streamContext + 16) = flagsByte & 3;
  if ( *result == 42 )
  {
    ++result;
    *(_BYTE *)(streamContext + 16) &= ~1u;
  }
  digitChar = *result;
  if ( (IsTable[(unsigned __int8)(digitChar + 1)] & 0x20) != 0 )
  {
    fieldWidth = 0;
    do
    {
      ++result;
      fieldWidth = digitChar - 48 + 10 * fieldWidth;
      digitChar = *result;
    }
    while ( (IsTable[(unsigned __int8)(digitChar + 1)] & 0x20) != 0 );
    *(_DWORD *)(streamContext + 12) = fieldWidth;
  }
  if ( *result == 78 )
  {
    *(_BYTE *)(streamContext + 16) |= 8u;
  }
  else
  {
    if ( *result != 70 )
      goto LABEL_12;
    *(_BYTE *)(streamContext + 16) |= 4u;
  }
  ++result;
LABEL_12:
  sizeChar = *result;
  if ( *result >= 0x68u )
  {
    if ( *result > 0x68u )
    {
      if ( sizeChar >= 0x6Cu && (sizeChar <= 0x6Cu || sizeChar == 119) )
      {
        ++result;
        *(_BYTE *)(streamContext + 16) |= 0x20u;
      }
      return result;
    }
    newFlags = *(_BYTE *)(streamContext + 16) | 0x10;
    ++result;
LABEL_28:
    *(_BYTE *)(streamContext + 16) = newFlags;
    return result;
  }
  if ( sizeChar < 0x49u )
    return result;
  if ( sizeChar <= 0x49u )
  {
    if ( result[1] != 54 || result[2] != 52 )
      return result;
    newFlags = *(_BYTE *)(streamContext + 16) | 0x40;
    result += 3;
    goto LABEL_28;
  }
  if ( sizeChar == 76 )
  {
    ++result;
    *(_BYTE *)(streamContext + 16) |= 0x40u;
  }
  return result;
}

//----- (004B3341) --------------------------------------------------------
int  IO_ScanfSkipWhitespace(int streamContext)
{
  int skippedCount; // esi
  int v3; // ecx

  skippedCount = 0;
  while ( (IsTable[(unsigned __int8)(IO_ScanfGetChar((int (**)(void))streamContext) + 1)] & 2) != 0 )
    ++skippedCount;
  if ( (*(_BYTE *)(streamContext + 16) & 2) == 0 )
    IO_ScanfUngetChar(v3, streamContext);
  return skippedCount;
}
// 4B336D: variable 'v3' is possibly undefined

//----- (004B3378) --------------------------------------------------------
int  IO_ScanfReadCharField(int streamContext, int *argList, _WORD *destBuffer)
{
  int v3; // ecx
  char v4; // bl
  int v5; // edi
  int v6; // esi
  int v7; // ebx
  int fieldWidth; // edi
  int charsRead; // ebp
  unsigned __int8 inputChar; // al
  char statusFlags; // dl
  int wideChar; // [esp+0h] [ebp-20h] BYREF
  unsigned __int8 mbBuffer[28]; // [esp+4h] [ebp-1Ch] BYREF

  v3 = streamContext;
  if ( (*(_BYTE *)(streamContext + 16) & 1) != 0 )
  {
    v4 = *(_BYTE *)(streamContext + 16);
    if ( (v4 & 4) != 0 )
    {
      v5 = *argList + 8;
      *argList = v5;
      destBuffer = *(_WORD **)(v5 - 8);
      __ES__ = *(_WORD *)(v5 - 8 + 4);
    }
    else if ( (v4 & 8) != 0 )
    {
      v6 = *argList + 4;
      *argList = v6;
      __ES__ = __DS__;
      destBuffer = *(_WORD **)(v6 - 4);
    }
    else
    {
      v7 = *argList + 4;
      *argList = v7;
      __ES__ = __DS__;
      destBuffer = *(_WORD **)(v7 - 4);
    }
  }
  fieldWidth = *(_DWORD *)(streamContext + 12);
  charsRead = 0;
  if ( fieldWidth == -1 )
    fieldWidth = 1;
  while ( fieldWidth > 0 )
  {
    inputChar = IO_ScanfGetChar((int (**)(void))v3);
    statusFlags = *(_BYTE *)(v3 + 16);
    if ( (statusFlags & 2) != 0 )
      break;
    ++charsRead;
    --fieldWidth;
    if ( (statusFlags & 1) != 0 )
    {
      if ( (statusFlags & 0x20) != 0 )
      {
        mbBuffer[0] = inputChar;
        if ( g_CRT_MbcsCodePageActive )
        {
          if ( (g_Clips_DbcsLeadByteTable[inputChar] & 1) != 0 )
            mbBuffer[1] = IO_ScanfGetChar((int (**)(void))v3);
        }
        if ( Str_DecodeMultibyteChar(&wideChar, mbBuffer, 2u) == -1 )
          return 0;
        *destBuffer++ = wideChar;
      }
      else
      {
        *(_BYTE *)destBuffer = inputChar;
        destBuffer = (_WORD *)((char *)destBuffer + 1);
      }
    }
  }
  return charsRead;
}
// 4B33D9: variable 'v3' is possibly undefined
// 54E718: using guessed type int dword_54E718;

//----- (004B345A) --------------------------------------------------------
void  IO_ScanfReadStringField(int streamContext, int *argList, unsigned __int8 *destBuffer)
{
  int v3; // ecx
  char v4; // bl
  int v5; // edi
  int v6; // esi
  int v7; // ebx
  int i; // edi
  unsigned __int8 inputChar; // bl
  int fieldWidth; // eax
  int nextChar; // eax
  int wideChar; // [esp+0h] [ebp-24h] BYREF
  unsigned __int8 mbBuffer[4]; // [esp+4h] [ebp-20h] BYREF
  unsigned __int8 charSize; // [esp+8h] [ebp-1Ch]

  v3 = streamContext;
  if ( (*(_BYTE *)(streamContext + 16) & 0x20) != 0 )
    charSize = 2;
  else
    charSize = 1;
  v4 = *(_BYTE *)(streamContext + 16);
  if ( (v4 & 1) != 0 )
  {
    if ( (v4 & 4) != 0 )
    {
      v5 = *argList + 8;
      *argList = v5;
      destBuffer = *(unsigned __int8 **)(v5 - 8);
      __ES__ = *(_WORD *)(v5 - 8 + 4);
    }
    else if ( (v4 & 8) != 0 )
    {
      v6 = *argList + 4;
      *argList = v6;
      __ES__ = __DS__;
      destBuffer = *(unsigned __int8 **)(v6 - 4);
    }
    else
    {
      v7 = *argList + 4;
      *argList = v7;
      __ES__ = __DS__;
      destBuffer = *(unsigned __int8 **)(v7 - 4);
    }
  }
  for ( i = 0; ; ++i )
  {
    inputChar = IO_ScanfGetChar((int (**)(void))v3);
    if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 2) == 0 )
      break;
  }
  if ( (*(_BYTE *)(v3 + 16) & 2) != 0 )
  {
    i = 0;
  }
  else
  {
    fieldWidth = *(_DWORD *)(v3 + 12);
    *(_DWORD *)(v3 + 12) = fieldWidth - 1;
    if ( fieldWidth )
    {
      do
      {
        ++i;
        if ( (*(_BYTE *)(v3 + 16) & 1) != 0 )
        {
          if ( charSize == 1 )
          {
            *destBuffer = inputChar;
          }
          else
          {
            mbBuffer[0] = inputChar;
            if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[inputChar] & 1) != 0 )
              mbBuffer[1] = IO_ScanfGetChar((int (**)(void))v3);
            if ( Str_DecodeMultibyteChar(&wideChar, mbBuffer, 2u) == -1 )
              goto LABEL_33;
            *(_WORD *)destBuffer = wideChar;
          }
          destBuffer += charSize;
        }
        nextChar = IO_ScanfNextFieldChar(v3);
        inputChar = nextChar;
        if ( nextChar == -1 )
          goto LABEL_28;
      }
      while ( (IsTable[(unsigned __int8)(nextChar + 1)] & 2) == 0 );
    }
    IO_ScanfUngetChar(v3, v3);
  }
LABEL_28:
  if ( (*(_BYTE *)(v3 + 16) & 1) != 0 && i > 0 )
  {
    if ( charSize == 1 )
      *destBuffer = 0;
    else
      *(_WORD *)destBuffer = 0;
  }
LABEL_33:
  // 4B35A8: jumps to the shared epilogue loc_4B3453 (pop ebp/es/edi/esi/ecx/ebx; retn)
  // shared with sub_4B3378; in C this is the function return.
  return;
}
// 4B35A8: control flows out of bounds to 4B3453
// 4B34BB: variable 'v3' is possibly undefined
// 54E718: using guessed type int dword_54E718;

//----- (004B35AD) --------------------------------------------------------
int  IO_ScanfStoreScanCount(int result, int *argList, int charCount)
{
  char flagsByte; // cl
  int v4; // edi
  _WORD *destPtr; // edx
  int v6; // esi
  int v7; // ecx

  flagsByte = *(_BYTE *)(result + 16);
  if ( (flagsByte & 1) != 0 )
  {
    if ( (flagsByte & 4) != 0 )
    {
      v4 = *argList + 8;
      *argList = v4;
      destPtr = *(_WORD **)(v4 - 8);
      __ES__ = *(_WORD *)(v4 - 8 + 4);
    }
    else if ( (flagsByte & 8) != 0 )
    {
      v6 = *argList + 4;
      *argList = v6;
      __ES__ = __DS__;
      destPtr = *(_WORD **)(v6 - 4);
    }
    else
    {
      v7 = *argList + 4;
      *argList = v7;
      __ES__ = __DS__;
      destPtr = *(_WORD **)(v7 - 4);
    }
    if ( (*(_BYTE *)(result + 16) & 0x10) != 0 )
      *destPtr = charCount;
    else
      *(_DWORD *)destPtr = charCount;
  }
  return result;
}

//----- (004B360B) --------------------------------------------------------
_BYTE * IO_ScanfParseScanset(int a1, int scansetBitmap)
{
  unsigned __int8 *v3; // ecx
  int setChar; // eax
  _BYTE *formatCursor; // ecx

  memset_(a1, 0);
  setChar = *v3;
  formatCursor = v3 + 1;
  if ( setChar )
  {
    do
    {
      *(_BYTE *)((setChar >> 3) + scansetBitmap) |= g_BitPositionMaskTable[setChar & 7];
      setChar = (unsigned __int8)*formatCursor;
      if ( !*formatCursor )
        break;
      ++formatCursor;
    }
    while ( setChar != 93 );
  }
  return formatCursor;
}
// 4B3622: variable 'v3' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004B364E) --------------------------------------------------------
int  IO_ScanfReadScansetField(int *argList, int *formatPtr, _BYTE *destBuffer)
{
  _BYTE *v4; // eax
  bool v5; // zf
  int v6; // ecx
  char v7; // bl
  int v8; // esi
  int v9; // eoff
  int v10; // ebx
  int v11; // edx
  int fieldWidth; // edx
  int i; // edi
  int inputChar; // eax
  int v15; // edx
  char v16; // bl
  char scansetBitmap[32]; // [esp+0h] [ebp-40h] BYREF
  int bitmapByte; // [esp+20h] [ebp-20h]
  BOOL negateSet; // [esp+24h] [ebp-1Ch]
  int savedChar; // [esp+28h] [ebp-18h]

  v4 = (_BYTE *)*formatPtr;
  v5 = *(_BYTE *)*formatPtr != 94;
  negateSet = *(_BYTE *)*formatPtr == 94;
  if ( !v5 )
    *formatPtr = (int)(v4 + 1);
  *formatPtr = (int)IO_ScanfParseScanset(*formatPtr, (int)scansetBitmap);
  v7 = *(_BYTE *)(v6 + 16);
  if ( (v7 & 1) != 0 )
  {
    if ( (v7 & 4) != 0 )
    {
      v8 = *argList + 8;
      *argList = v8;
      v9 = v8 - 8;
      destBuffer = *(_BYTE **)(v8 - 8);
      __ES__ = *(_WORD *)(v9 + 4);
    }
    else if ( (v7 & 8) != 0 )
    {
      v10 = *argList + 4;
      *argList = v10;
      __ES__ = __DS__;
      destBuffer = *(_BYTE **)(v10 - 4);
    }
    else
    {
      v11 = *argList + 4;
      *argList = v11;
      __ES__ = __DS__;
      destBuffer = *(_BYTE **)(v11 - 4);
    }
  }
  fieldWidth = *(_DWORD *)(v6 + 12);
  for ( i = 0; fieldWidth; ++i )
  {
    inputChar = IO_ScanfGetChar((int (**)(void))v6);
    v16 = *(_BYTE *)(v6 + 16);
    savedChar = inputChar;
    if ( (v16 & 2) != 0 )
      break;
    bitmapByte = (unsigned __int8)scansetBitmap[inputChar >> 3];
    if ( ((unsigned __int8)(bitmapByte & g_BitPositionMaskTable[inputChar & 7]) == 0) != negateSet )
    {
      IO_ScanfUngetChar(v6, v6);
      break;
    }
    fieldWidth = v15 - 1;
    if ( (*(_BYTE *)(v6 + 16) & 1) != 0 )
      *destBuffer++ = savedChar;
  }
  if ( (*(_BYTE *)(v6 + 16) & 1) != 0 && i > 0 )
    *destBuffer = 0;
  return i;
}
// 4B367C: variable 'v6' is possibly undefined
// 4B371B: variable 'v15' is possibly undefined

//----- (004B3744) --------------------------------------------------------
void  IO_ScanfReadFloatField(int streamContext, int *argList)
{
  int digitCount; // edi
  char *bufferCursor; // ebx
  int v5; // eax
  int inputChar; // ecx
  int v7; // edx
  int v8; // ebp
  int sawIntegerDigits; // ebp
  int v10; // eax
  int v11; // eax
  char *digitCursor; // ebp
  char v13; // al
  int v14; // eax
  int v15; // eax
  char v16; // ah
  int v17; // ecx
  int *destPtr; // ebx
  int v19; // ebx
  int v20; // edx
  char v21; // dh
  int v22; // eax
  char numberBuffer; // [esp+0h] [ebp-84h] BYREF
  _BYTE v24[3]; // [esp+1h] [ebp-83h] BYREF
  _DWORD doubleValue[2]; // [esp+50h] [ebp-34h] BYREF
  int *argCursor; // [esp+58h] [ebp-2Ch]
  int v27; // [esp+5Ch] [ebp-28h]
  unsigned int j; // [esp+60h] [ebp-24h]
  int integerValue; // [esp+64h] [ebp-20h]
  int i; // [esp+68h] [ebp-1Ch]

  argCursor = argList;
  digitCount = 0;
  bufferCursor = &numberBuffer;
  for ( i = 0; ; ++i )
  {
    v5 = IO_ScanfGetChar((int (**)(void))streamContext);
    inputChar = v5;
    if ( (IsTable[(unsigned __int8)(v5 + 1)] & 2) == 0 )
      break;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 2) != 0 )
    goto LABEL_42;
  v7 = *(_DWORD *)(streamContext + 12);
  *(_DWORD *)(streamContext + 12) = v7 - 1;
  if ( v7 )
  {
    if ( v5 == 43 || v5 == 45 )
    {
      v8 = i;
      numberBuffer = v5;
      bufferCursor = v24;
      inputChar = IO_ScanfNextFieldChar(streamContext);
      i = v8 + 1;
      if ( inputChar == -1 )
        goto LABEL_42;
    }
    if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) != 0 || inputChar == 46 )
    {
      integerValue = 0;
      sawIntegerDigits = 0;
      if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) != 0 )
      {
        sawIntegerDigits = 1;
        while ( 1 )
        {
          *bufferCursor++ = inputChar;
          if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
            HIWORD(integerValue) = 10 * HIWORD(integerValue) + inputChar - 48;
          ++digitCount;
          v10 = IO_ScanfNextFieldChar(streamContext);
          inputChar = v10;
          if ( v10 == -1 )
            break;
          if ( (IsTable[(unsigned __int8)(v10 + 1)] & 0x20) == 0 )
            goto LABEL_17;
        }
LABEL_42:
        if ( digitCount > 0 && (*(_BYTE *)(streamContext + 16) & 1) != 0 )
        {
          *bufferCursor = 0;
          if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
          {
            if ( numberBuffer == 45 )
              integerValue = -integerValue;
          }
          else
          {
            g_StringToDoubleScanFn(inputChar, doubleValue);
          }
          v16 = *(_BYTE *)(streamContext + 16);
          if ( (v16 & 4) != 0 )
          {
            v17 = *argCursor + 8;
            *argCursor = v17;
            destPtr = *(int **)(v17 - 8);
            __ES__ = *(_WORD *)(v17 - 8 + 4);
          }
          else if ( (v16 & 8) != 0 )
          {
            v19 = *argCursor + 4;
            *argCursor = v19;
            __ES__ = __DS__;
            destPtr = *(int **)(v19 - 4);
          }
          else
          {
            v20 = *argCursor + 4;
            *argCursor = v20;
            __ES__ = __DS__;
            destPtr = *(int **)(v20 - 4);
          }
          v21 = *(_BYTE *)(streamContext + 16);
          if ( (v21 & 0x10) != 0 )
          {
            v22 = integerValue;
          }
          else
          {
            if ( (v21 & 0x20) != 0 || (v21 & 0x40) != 0 )
            {
              *destPtr = doubleValue[0];
              destPtr[1] = doubleValue[1];
              goto LABEL_60;
            }
            v22 = _FDFS();
          }
          *destPtr = v22;
        }
LABEL_60:
        // 4B3597: jumps to the shared epilogue loc_4B3453 (pop ebp/es/edi/esi/ecx/ebx; retn)
        // shared with sub_4B3378; in C this is the function return.
        return;
      }
LABEL_17:
      if ( inputChar == 46 )
      {
        *bufferCursor = 46;
        v11 = IO_ScanfNextFieldChar(streamContext);
        ++bufferCursor;
        inputChar = v11;
        if ( v11 == -1 )
          goto LABEL_42;
        if ( !sawIntegerDigits && (IsTable[(unsigned __int8)(v11 + 1)] & 0x20) == 0 )
          goto LABEL_41;
        ++digitCount;
        do
        {
          if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) == 0 )
            break;
          ++digitCount;
          *bufferCursor++ = inputChar;
          inputChar = IO_ScanfNextFieldChar(streamContext);
        }
        while ( inputChar != -1 );
        if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
        {
          digitCursor = bufferCursor;
          for ( j = 0; ; j /= 0xAu )
          {
            v13 = *--digitCursor;
            if ( *digitCursor == 46 )
              break;
            v27 = 10;
            BYTE2(j) = v13 - 48;
          }
          LOWORD(integerValue) = j;
        }
        if ( inputChar == -1 )
          goto LABEL_42;
      }
      if ( (*(_BYTE *)(streamContext + 16) & 0x10) == 0 && (inputChar == 101 || inputChar == 69) )
      {
        ++digitCount;
        *bufferCursor = inputChar;
        v14 = IO_ScanfNextFieldChar(streamContext);
        ++bufferCursor;
        inputChar = v14;
        if ( v14 == -1 )
          goto LABEL_42;
        if ( v14 == 43 || v14 == 45 )
        {
          ++digitCount;
          *bufferCursor++ = v14;
          inputChar = IO_ScanfNextFieldChar(streamContext);
          if ( inputChar == -1 )
            goto LABEL_42;
        }
        if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) != 0 )
        {
          while ( 1 )
          {
            ++digitCount;
            *bufferCursor = inputChar;
            v15 = IO_ScanfNextFieldChar(streamContext);
            ++bufferCursor;
            inputChar = v15;
            if ( v15 == -1 )
              goto LABEL_42;
            if ( (IsTable[(unsigned __int8)(v15 + 1)] & 0x20) == 0 )
              goto LABEL_41;
          }
        }
        digitCount = 0;
      }
    }
  }
LABEL_41:
  IO_ScanfUngetChar(inputChar, streamContext);
  goto LABEL_42;
}
// 4B3A15: control flows out of bounds to 4B3453
// 4B398E: variable 'v6' is possibly undefined
// 4D9506: using guessed type int _FDFS(void);
// 51AF08: using guessed type int (__fastcall *off_51AF08)(_DWORD, _DWORD);

//----- (004B3A1A) --------------------------------------------------------
signed int  IO_ScanfReadIntegerField(int streamContext, int *argList, int radix)
{
  int digitCount; // ebp
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // edx
  signed int v16; // eax
  int v17; // edx
  int v18; // ecx
  int v19; // eax
  int v20; // eax
  signed int v21; // eax
  int v22; // edx
  int v23; // ecx
  int v24; // eax
  int v25; // eax
  char v26; // bh
  int v27; // edx
  __int16 v28; // ax
  int v29; // edi
  int v30; // edi
  int v31; // esi
  char v32; // al
  int v33; // ebx
  _WORD *destPtr; // eax
  int v35; // edx
  int v36; // esi
  __int64 int64Value; // [esp+8h] [ebp-38h]
  int signChar; // [esp+18h] [ebp-28h]
  int i; // [esp+20h] [ebp-20h]
  int intValue; // [esp+24h] [ebp-1Ch]
  signed int inputChar; // [esp+2Ch] [ebp-14h]

  digitCount = 0;
  int64Value = 0LL;
  intValue = 0;
  for ( i = 0; ; ++i )
  {
    v5 = IO_ScanfGetChar((int (**)(void))streamContext);
    inputChar = v5;
    if ( (IsTable[(unsigned __int8)(v5 + 1)] & 2) == 0 )
      break;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 2) != 0 )
    goto LABEL_44;
  v8 = *(_DWORD *)(streamContext + 12);
  *(_DWORD *)(streamContext + 12) = v8 - 1;
  if ( !v8 )
    goto LABEL_43;
  signChar = 43;
  if ( v7 && (v5 == 43 || v5 == 45) )
  {
    signChar = v5;
    ++i;
    inputChar = IO_ScanfNextFieldChar(streamContext);
    if ( inputChar == -1 )
      goto LABEL_44;
  }
  if ( radix )
  {
    if ( radix == 16 && inputChar == 48 )
    {
      digitCount = 1;
      v12 = IO_ScanfNextFieldChar(streamContext);
      inputChar = v12;
      if ( v12 == -1 )
        goto LABEL_44;
      if ( v12 == 120 || v12 == 88 )
      {
        digitCount = 0;
        inputChar = IO_ScanfNextFieldChar(streamContext);
        i += 2;
        if ( inputChar == -1 )
          goto LABEL_44;
      }
    }
  }
  else if ( inputChar == 48 )
  {
    digitCount = 1;
    v9 = IO_ScanfNextFieldChar(streamContext);
    inputChar = v9;
    if ( v9 == -1 )
      goto LABEL_44;
    if ( v9 == 120 || v9 == 88 )
    {
      v10 = IO_ScanfNextFieldChar(streamContext);
      digitCount = 0;
      v6 = v11 + 2;
      inputChar = v10;
      i = v6;
      if ( v10 == -1 )
        goto LABEL_44;
      radix = 16;
    }
    else
    {
      radix = 8;
    }
  }
  else
  {
    radix = 10;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 0x40) != 0 )
  {
    v13 = 0;
    while ( 1 )
    {
      v14 = IO_ScanfDigitValue(inputChar, radix, v13);
      if ( v14 >= v15 )
        break;
      int64Value = (unsigned int)v14 + _I8M(0, HIDWORD(int64Value));
      ++digitCount;
      inputChar = IO_ScanfNextFieldChar(streamContext);
      if ( inputChar == -1 )
        goto LABEL_44;
    }
    if ( inputChar == 58 && *(char *)(streamContext + 16) < 0 )
    {
      while ( 1 )
      {
        ++digitCount;
        v16 = IO_ScanfNextFieldChar(streamContext);
        if ( v16 == -1 )
          goto LABEL_44;
        v19 = IO_ScanfDigitValue(v16, v17, v18);
        if ( v19 >= radix )
          break;
        int64Value = (unsigned int)v19 + _I8M(0, HIDWORD(int64Value));
      }
    }
LABEL_43:
    IO_ScanfUngetChar(v7, streamContext);
    goto LABEL_44;
  }
  while ( 1 )
  {
    v20 = IO_ScanfDigitValue(inputChar, v6, v7);
    if ( v20 >= radix )
      break;
    ++digitCount;
    intValue = v20 + radix * intValue;
    inputChar = IO_ScanfNextFieldChar(streamContext);
    if ( inputChar == -1 )
      goto LABEL_44;
  }
  if ( inputChar != 58 || *(char *)(streamContext + 16) >= 0 )
    goto LABEL_43;
  while ( 1 )
  {
    ++digitCount;
    v21 = IO_ScanfNextFieldChar(streamContext);
    if ( v21 == -1 )
      break;
    v24 = IO_ScanfDigitValue(v21, v22, v23);
    if ( v24 >= v7 )
      goto LABEL_43;
    intValue = v24 + v7 * intValue;
  }
LABEL_44:
  if ( (*(_BYTE *)(streamContext + 16) & 0x40) != 0 )
  {
    if ( signChar == 45 )
    {
      v25 = ~HIDWORD(int64Value);
      LODWORD(int64Value) = -(int)int64Value;
      if ( !(_DWORD)int64Value )
        v25 = -HIDWORD(int64Value);
      HIDWORD(int64Value) = v25;
    }
    if ( digitCount > 0 )
    {
      v26 = *(_BYTE *)(streamContext + 16);
      digitCount += i;
      if ( (v26 & 1) != 0 )
      {
        if ( (v26 & 4) != 0 )
        {
          v27 = *argList + 8;
          *argList = v27;
          v28 = *(_WORD *)(v27 - 4);
          v29 = *(_DWORD *)(v27 - 8);
        }
        else if ( (v26 & 8) != 0 )
        {
          v30 = *argList + 4;
          *argList = v30;
          v28 = __DS__;
          v29 = *(_DWORD *)(v30 - 4);
        }
        else
        {
          v31 = *argList + 4;
          *argList = v31;
          v28 = __DS__;
          v29 = *(_DWORD *)(v31 - 4);
        }
        *(__int64 *)MK_FP(v28, v29) = int64Value;
      }
    }
  }
  else
  {
    if ( signChar == 45 )
      intValue = -intValue;
    if ( digitCount > 0 )
    {
      v32 = *(_BYTE *)(streamContext + 16);
      digitCount += i;
      if ( (v32 & 1) != 0 )
      {
        if ( (v32 & 4) != 0 )
        {
          v33 = *argList + 8;
          *argList = v33;
          destPtr = *(_WORD **)(v33 - 8);
          __ES__ = *(_WORD *)(v33 - 8 + 4);
        }
        else if ( (v32 & 8) != 0 )
        {
          v35 = *argList + 4;
          *argList = v35;
          __ES__ = __DS__;
          destPtr = *(_WORD **)(v35 - 4);
        }
        else
        {
          v36 = *argList + 4;
          *argList = v36;
          __ES__ = __DS__;
          destPtr = *(_WORD **)(v36 - 4);
        }
        if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
          *destPtr = intValue;
        else
          *(_DWORD *)destPtr = intValue;
      }
    }
  }
  return digitCount;
}
// 4B3A8B: variable 'v7' is possibly undefined
// 4B3AFE: variable 'v11' is possibly undefined
// 4B3BA0: variable 'v13' is possibly undefined
// 4B3BA7: variable 'v15' is possibly undefined
// 4B3C34: variable 'v17' is possibly undefined
// 4B3C34: variable 'v18' is possibly undefined
// 4B3C91: variable 'v6' is possibly undefined
// 4B3CDC: variable 'v22' is possibly undefined
// 4B3CDC: variable 'v23' is possibly undefined
// 4B3D0E: variable 'v39' is possibly undefined
// 4D9552: using guessed type __int64 __fastcall _I8M(_DWORD, _DWORD);

//----- (004B3E1F) --------------------------------------------------------
int  IO_ScanfDigitValue(signed int ch, int a2, int a3)
{
  int lowerChar; // eax

  if ( ch >= 48 && ch <= 57 )
    return ch - 48;
  lowerChar = tolower_(a3, a2);
  if ( lowerChar < 97 || lowerChar > 102 )
    return 16;
  else
    return lowerChar - 87;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004B3E46) --------------------------------------------------------
int  IO_ScanfNextFieldChar(int streamContext)
{
  int remainingWidth; // eax
  int result; // eax
  int v4; // edx

  remainingWidth = *(_DWORD *)(streamContext + 12);
  *(_DWORD *)(streamContext + 12) = remainingWidth - 1;
  if ( !remainingWidth )
    return -1;
  result = IO_ScanfGetChar((int (**)(void))streamContext);
  if ( (*(_BYTE *)(v4 + 16) & 2) != 0 )
    return -1;
  return result;
}
// 4B3E5E: variable 'v4' is possibly undefined

//----- (004B4E7A) --------------------------------------------------------
BOOL CRT_HasActiveWindow()
{
  HMODULE LibraryA; // eax
  HWND v1; // ebx
  HWND (__stdcall *GetActiveWindow)(); // eax

  LibraryA = LoadLibraryA(LibFileName);
  v1 = 0;
  if ( LibraryA )
  {
    GetActiveWindow = (HWND (__stdcall *)())GetProcAddress(LibraryA, ProcName);
    if ( GetActiveWindow )
      v1 = GetActiveWindow();
  }
  return v1 != 0;
}

//----- (004B4EB4) --------------------------------------------------------
unsigned int  CRT_FormatExceptionMessage(unsigned int result, char *appendText, unsigned int addressValue)
{
  char *hexInsertPos; // ebx
  char *i; // esi
  char srcChar; // cl
  char hexDigit; // dl

  hexInsertPos = 0;
  while ( *(_BYTE *)result )
    ++result;
  for ( i = (char *)(result + 9); ; ++i )
  {
    srcChar = *appendText;
    *(_BYTE *)result = *appendText;
    if ( !srcChar )
      break;
    if ( srcChar == 48 && appendText[1] == 120 )
      hexInsertPos = i;
    ++result;
    ++appendText;
  }
  if ( hexInsertPos )
  {
    for ( result = addressValue; result; result >>= 4 )
    {
      hexDigit = g_HexDigitCharTable[result & 0xF];
      *hexInsertPos-- = hexDigit;
    }
  }
  return result;
}

//----- (004B4F01) --------------------------------------------------------
signed int __stdcall TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
  PCONTEXT ContextRecord; // ebx
  unsigned int *exceptionRecord; // ecx
  unsigned int exceptionCode; // eax
  unsigned int faultAddress; // ebx
  char *messageText; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  char Buffer[256]; // [esp+0h] [ebp-10Ch] BYREF
  DWORD NumberOfBytesWritten; // [esp+100h] [ebp-Ch] BYREF

  ContextRecord = ExceptionInfo->ContextRecord;
  if ( CRT_HasActiveWindow() || _NTConsoleOutput_() == -1 )
    return 0;
  Buffer[0] = 0;
  exceptionCode = *exceptionRecord;
  if ( *exceptionRecord < 0xC0000090 )
  {
    if ( exceptionCode < 0xC000008D )
    {
      if ( exceptionCode < 0xC0000005 )
        goto LABEL_41;
      if ( exceptionCode <= 0xC0000005 )
      {
        CRT_FormatExceptionMessage((unsigned int)Buffer, aTheInstructi_7, exceptionRecord[3]);
        CRT_FormatExceptionMessage((unsigned int)Buffer, aAt0x00000000_T, *(_DWORD *)(v7 + 24));
        if ( *(_DWORD *)(v8 + 20) )
          messageText = aWritten_;
        else
          messageText = aRead_;
        faultAddress = 0;
        goto LABEL_42;
      }
      if ( exceptionCode != -1073741795 )
        goto LABEL_41;
      messageText = aAnIllegalInstr;
    }
    else if ( exceptionCode <= 0xC000008D )
    {
      messageText = aTheInstructi_1;
    }
    else if ( exceptionCode <= 0xC000008E )
    {
      messageText = aTheInstructi_2;
    }
    else
    {
      messageText = aTheInstructi_3;
    }
  }
  else if ( *exceptionRecord <= 0xC0000090 )
  {
    messageText = aTheInstructi_6;
  }
  else if ( exceptionCode < 0xC0000093 )
  {
    if ( exceptionCode <= 0xC0000091 )
    {
      messageText = aTheInstructi_4;
    }
    else if ( (ContextRecord->FloatSave.StatusWord & 0x200) != 0 )
    {
      messageText = aTheInstruction;
    }
    else
    {
      messageText = aTheInstructi_0;
    }
  }
  else if ( exceptionCode <= 0xC0000093 )
  {
    messageText = aTheInstructi_5;
  }
  else if ( exceptionCode < 0xC0000096 )
  {
    if ( exceptionCode != -1073741676 )
      goto LABEL_41;
    messageText = aAnIntegerDivid;
  }
  else if ( exceptionCode <= 0xC0000096 )
  {
    messageText = aAPrivilegedIns;
  }
  else
  {
    if ( exceptionCode != -1073741571 )
    {
LABEL_41:
      CRT_FormatExceptionMessage((unsigned int)Buffer, aTheProgramEnco, *exceptionRecord);
      messageText = aAddress0x00000;
      faultAddress = *(_DWORD *)(v9 + 12);
      goto LABEL_42;
    }
    messageText = aAStackOverflow;
  }
  faultAddress = exceptionRecord[3];
LABEL_42:
  CRT_FormatExceptionMessage((unsigned int)Buffer, messageText, faultAddress);
  WriteFile(*(HANDLE *)(g_CRT_OsHandleTable + 8), Buffer, strlen(Buffer), &NumberOfBytesWritten, 0);
  return 1;
}
// 4B4F34: variable 'v2' is possibly undefined
// 4B5015: variable 'v7' is possibly undefined
// 4B501D: variable 'v8' is possibly undefined
// 4B506C: variable 'v9' is possibly undefined
// 4B48D9: using guessed type int _NTConsoleOutput_(void);
// 51AED0: using guessed type int dword_51AED0;

//----- (004B50D6) --------------------------------------------------------
signed int __cdecl CRT_FpuExceptionFrameHandler(EXCEPTION_RECORD *exceptionRecord, int establisherFrame, int contextRecord)
{
  int v3; // ecx
  signed int result; // eax
  int retryCount; // ebx
  int handlerResult; // eax
  struct _EXCEPTION_POINTERS exceptionPointers; // [esp+0h] [ebp-14h] BYREF

  if ( (exceptionRecord->ExceptionFlags & 6) != 0 )
    return 1;
  switch ( exceptionRecord->ExceptionCode )
  {
    case 0xC000008D:
    case 0xC000008E:
    case 0xC000008F:
    case 0xC0000090:
    case 0xC0000091:
    case 0xC0000092:
    case 0xC0000093:
      g_CRT_FpuExceptionActiveFlag = 1;
      Fpu_ClearExceptions();
      if ( CRT_DispatchRegisteredFpeHandler() == -1 || !g_CRT_FpuExceptionActiveFlag )
        goto LABEL_15;
      result = 0;
      *(_WORD *)(contextRecord + 32) &= 0x7F00u;
      return result;
    default:
      if ( !g_FpuExceptionResignalFn )
        goto LABEL_15;
      retryCount = 1;
      break;
  }
  while ( 1 )
  {
    handlerResult = g_CRT_ExceptionHandlerCallback(v3, exceptionRecord->ExceptionCode);
    if ( handlerResult )
    {
      if ( handlerResult == 1 || handlerResult == 2 || handlerResult == 3 )
      {
LABEL_15:
        exceptionPointers.ExceptionRecord = exceptionRecord;
        exceptionPointers.ContextRecord = (PCONTEXT)contextRecord;
        if ( UnhandledExceptionFilter(&exceptionPointers) )
          ExitProcess(0xFFFFFFFF);
        return 1;
      }
      g_CRT_FpuExceptionActiveFlag = 1;
      g_FpuExceptionResignalFn();
      if ( g_CRT_FpuExceptionActiveFlag )
        return 0;
    }
    if ( ++retryCount > 12 )
      goto LABEL_15;
  }
}
// 4B517F: conditional instruction was optimized away because dx.2!=F1D9
// 4B51E2: conditional instruction was optimized away because ebx.4 is in (==81|==8D)
// 4B5233: variable 'v3' is possibly undefined
// 4965FF: using guessed type int sub_4965FF(void);
// 51AEDC: using guessed type int (__fastcall *dword_51AEDC)(_DWORD, _DWORD);
// 51AEE0: using guessed type int (*dword_51AEE0)(void);
// 54E710: using guessed type char byte_54E710;

//----- (004B529A) --------------------------------------------------------
LPTOP_LEVEL_EXCEPTION_FILTER  CRT_InstallUnhandledExceptionFilter(int a1, int a2)
{
  __int64 v3; // rax
  int v4; // ecx
  __int64 v5; // rax
  int v6; // ecx
  int v7; // ecx
  __int64 v8; // rax

  v3 = g_CrtThreadDataAccessor(a2, a1);
  *(_DWORD *)(v3 + 84) = HIDWORD(v3);
  v5 = g_CrtThreadDataAccessor(v4, NtCurrentTeb()->NtTib.ExceptionList);
  **(_DWORD **)(v5 + 84) = HIDWORD(v5);
  *(_DWORD *)(*(_DWORD *)(g_CrtThreadDataAccessor(v6, HIDWORD(v5)) + 84) + 4) = CRT_FpuExceptionFrameHandler;
  v8 = g_CrtThreadDataAccessor(v7, 0);
  __writefsdword(HIDWORD(v8), *(_DWORD *)(v8 + 84));
  return SetUnhandledExceptionFilter(TopLevelExceptionFilter);
}
// 4B52AE: variable 'v4' is possibly undefined
// 4B52B9: variable 'v6' is possibly undefined
// 4B52CB: variable 'v7' is possibly undefined
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004B52E6) --------------------------------------------------------
int __fastcall CRT_RemoveUnhandledExceptionFilter(int a1, int a2)
{
  unsigned int *exceptionRegistration; // eax
  int v3; // edx
  int v4; // ecx
  int result; // eax

  exceptionRegistration = *(unsigned int **)(g_CrtThreadDataAccessor(a1, a2) + 84);
  if ( exceptionRegistration )
  {
    v3 = 0;
    __writefsdword(0, *exceptionRegistration);
  }
  result = g_CrtThreadDataAccessor(v4, v3);
  *(_DWORD *)(result + 84) = 0;
  return result;
}
// 4B52FB: variable 'v4' is possibly undefined
// 4B52FB: variable 'v3' is possibly undefined
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004B5310) --------------------------------------------------------
signed int IO_InitializeFileIORouter()
{
  return IO_AddRouter(
           (int)aFileio,
           0,
           (int)IO_FileIOQueryCallback,
           (int)ismbdprint_,
           (int)IO_FileIOGetcCallback,
           (int)IO_FileIOUngetcCallback,
           (int)IO_FileIOExitCallback);
}

//----- (004B5340) --------------------------------------------------------
int __thiscall IO_FindOpenFileByLogicalName(void *this)
{
  int result; // eax
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  _DWORD *fileListCursor; // ecx

  result = strcmp_(this, aStdout_1);
  if ( result )
  {
    result = strcmp_(v2, aStdin_0);
    if ( result )
    {
      result = strcmp_(v3, g_IO_LogicalNameTable_WTrace[0]);
      if ( result )
      {
        result = strcmp_(v4, g_IO_LogicalNameTable_WDialog[0]);
        if ( result )
        {
          result = strcmp_(v5, g_IO_LogicalNameTable_WClips[0]);
          if ( result )
          {
            result = strcmp_(v6, g_IO_LogicalName_WDisplay);
            if ( result )
            {
              result = strcmp_(v7, g_IO_LogicalNameTable_WError[0]);
              if ( result )
              {
                result = strcmp_(v8, g_IO_LogicalNameTable_WWarning[0]);
                if ( result )
                {
                  fileListCursor = (_DWORD *)g_IO_LogicalNameFileListHead;
                  if ( g_IO_LogicalNameFileListHead )
                  {
                    do
                    {
                      if ( !strcmp_(fileListCursor, *fileListCursor) )
                        break;
                      fileListCursor = (_DWORD *)fileListCursor[2];
                    }
                    while ( fileListCursor );
                  }
                  if ( fileListCursor )
                    return fileListCursor[1];
                  else
                    return 0;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}
// 4B535E: variable 'v2' is possibly undefined
// 4B536F: variable 'v3' is possibly undefined
// 4B5380: variable 'v4' is possibly undefined
// 4B5391: variable 'v5' is possibly undefined
// 4B53A2: variable 'v6' is possibly undefined
// 4B53B3: variable 'v7' is possibly undefined
// 4B53C4: variable 'v8' is possibly undefined
// 4B53EC: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A620: using guessed type char *off_51A620[2];
// 51A624: using guessed type char *off_51A624;
// 51AEF8: using guessed type int dword_51AEF8;

//----- (004B5410) --------------------------------------------------------
int ismbdprint_(void *logical_name)
{
  return IO_FindOpenFileByLogicalName(logical_name) != 0;
}

//----- (004B5420) --------------------------------------------------------
signed int __thiscall IO_FileIOExitCallback(void *this)
{
  IO_CloseAllNamedFiles(this);
  return 1;
}

//----- (004B5430) --------------------------------------------------------
int __fastcall IO_FileIOQueryCallback(int a1, void *logicalName)
{
  int filePtr; // eax
  int v3; // ecx
  int v4; // ecx

  filePtr = IO_FindOpenFileByLogicalName(logicalName);
  Output_WriteFormatted(v3, filePtr, filePtr, (int)aS_13, v3);
  fflush_(v4);
  return 1;
}
// 4B5441: variable 'v3' is possibly undefined
// 4B544B: variable 'v4' is possibly undefined
// 48A216: using guessed type int __thiscall fflush_(_DWORD);

//----- (004B5460) --------------------------------------------------------
int __thiscall IO_FileIOGetcCallback(void *this)
{
  int v1; // ecx
  __int64 v2; // rax
  unsigned __int8 *v3; // ecx

  LODWORD(v2) = IO_FindOpenFileByLogicalName(this);
  v1 = *(_DWORD *)(v2 + 4);
  HIDWORD(v2) = v2;
  if ( v1 > 0 && (v1 = **(unsigned __int8 **)v2 - 13, (unsigned int)v1 > 0xFD) )
  {
    v3 = *(unsigned __int8 **)v2;
    --*(_DWORD *)(v2 + 4);
    *(_DWORD *)v2 = v3 + 1;
    LODWORD(v2) = *v3;
  }
  else
  {
    v2 = fgetc_(v1, v2);
  }
  if ( v2 == __PAIR64__(&g_IO_FileGetcSentinelAddr, -1) )
    g_IO_FileGetcStreamFlags &= 0xCFu;
  return v2;
}
// 488F44: using guessed type __int64 __fastcall fgetc_(_DWORD, _DWORD);
// 51A34C: using guessed type char byte_51A34C;

//----- (004B54D0) --------------------------------------------------------
signed int  IO_FileIOUngetcCallback(void *logicalName)
{
  signed int v1; // ecx

  IO_FindOpenFileByLogicalName(logicalName);
  return CRT_FlushBufferAndPutChar(v1, v1);
}
// 4B54DE: variable 'v1' is possibly undefined

//----- (004B54F0) --------------------------------------------------------
int  IO_OpenNamedFile(
        const CHAR *fileName,
        unsigned __int8 *accessMode,
        int a3,
        const char *logicalName,
        DWORD a5)
{
  int result; // eax
  int filePtr; // ebp
  _DWORD *v7; // ecx
  const char *nameCursor; // esi
  _DWORD *fileEntry; // edx
  _BYTE *nameCopy; // edi
  char v11; // al
  char v12; // al

  result = IO_FOpen(fileName, accessMode, a3, a5);
  filePtr = result;
  if ( result )
  {
    v7 = *(_DWORD **)(g_ClipsMemoryTable + 48);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *v7;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    nameCursor = logicalName;
    nameCopy = Mem_SmallBlockAlloc(strlen(logicalName) + 1);
    *fileEntry = nameCopy;
    do
    {
      v11 = *nameCursor;
      *nameCopy = *nameCursor;
      if ( !v11 )
        break;
      v12 = nameCursor[1];
      nameCursor += 2;
      nameCopy[1] = v12;
      nameCopy += 2;
    }
    while ( v12 );
    fileEntry[1] = filePtr;
    fileEntry[2] = g_IO_LogicalNameFileListHead;
    result = 1;
    g_IO_LogicalNameFileListHead = (int)fileEntry;
  }
  return result;
}
// 4B5535: variable 'v9' is possibly undefined
// 51AEF8: using guessed type int dword_51AEF8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B5580) --------------------------------------------------------
signed int  IO_CloseNamedFile(int logicalName)
{
  int v1; // ecx
  int fileEntry; // ebx
  int previousEntry; // esi

  v1 = logicalName;
  fileEntry = g_IO_LogicalNameFileListHead;
  previousEntry = 0;
  if ( !g_IO_LogicalNameFileListHead )
    return 0;
  while ( strcmp_(v1, v1) )
  {
    previousEntry = fileEntry;
    fileEntry = *(_DWORD *)(fileEntry + 8);
    if ( !fileEntry )
      return 0;
  }
  fclose_(v1);
  Mem_SmallBlockFree(*(_DWORD **)fileEntry, strlen(*(const char **)fileEntry) + 1);
  if ( previousEntry )
    *(_DWORD *)(previousEntry + 8) = *(_DWORD *)(fileEntry + 8);
  else
    g_IO_LogicalNameFileListHead = *(_DWORD *)(fileEntry + 8);
  Mem_SmallBlockFree((_DWORD *)fileEntry, 12);
  return 1;
}
// 4B5596: variable 'v1' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51AEF8: using guessed type int dword_51AEF8;

//----- (004B5600) --------------------------------------------------------
signed int __thiscall IO_CloseAllNamedFiles(void *this)
{
  _DWORD **fileEntry; // ebx
  _DWORD *currentEntry; // eax
  signed int result; // eax

  if ( !g_IO_LogicalNameFileListHead )
    return 0;
  fileEntry = (_DWORD **)g_IO_LogicalNameFileListHead;
  do
  {
    fclose_(this);
    Mem_SmallBlockFree(*fileEntry, strlen((const char *)*fileEntry) + 1);
    currentEntry = fileEntry;
    fileEntry = (_DWORD **)fileEntry[2];
    Mem_SmallBlockFree(currentEntry, 12);
  }
  while ( fileEntry );
  result = 1;
  g_IO_LogicalNameFileListHead = 0;
  return result;
}
// 4B5616: variable 'this' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AEF8: using guessed type int dword_51AEF8;

//----- (004B5BA0) --------------------------------------------------------
int  CRT_MapAccessModeToCreateFileFlags(int result, _DWORD *desiredAccess, _DWORD *fileAttributes)
{
  if ( result == 2 )
  {
    *desiredAccess = -1073741824;
LABEL_3:
    *fileAttributes = 128;
    return result;
  }
  if ( result == 1 )
  {
    *desiredAccess = 0x40000000;
    goto LABEL_3;
  }
  *desiredAccess = 0x80000000;
  *fileAttributes = 1;
  return result;
}

//----- (004B5BCC) --------------------------------------------------------
unsigned int  CRT_MapOpenFlagsToCreationDisposition(char openFlags, _DWORD *creationDisposition)
{
  unsigned int result; // eax
  int accessBits; // ebx

  result = openFlags & 0x70;
  accessBits = openFlags & 7;
  if ( result < 0x20 )
  {
    if ( result )
    {
      if ( result == 16 )
        *creationDisposition = 0;
    }
    else
    {
      *creationDisposition = 1;
      if ( !accessBits )
        *(_BYTE *)creationDisposition |= 2u;
    }
  }
  else if ( result <= 0x20 )
  {
    *creationDisposition = 1;
  }
  else if ( result >= 0x30 )
  {
    if ( result <= 0x30 )
    {
      *creationDisposition = 2;
    }
    else if ( result == 64 )
    {
      *creationDisposition = 3;
    }
  }
  return result;
}

//----- (004B5C7A) --------------------------------------------------------
int  CRT_CheckReadOnlyBeforeOpen(const CHAR *fileName, char openFlags, int a3)
{
  DWORD FileAttributesA; // eax

  FileAttributesA = GetFileAttributesA(fileName);
  if ( FileAttributesA == -1 )
    return _set_errno_nt_(a3);
  if ( (openFlags & 2) != 0 && (FileAttributesA & 1) != 0 )
    return _set_errno_dos_(a3);
  return 0;
}
// 485306: using guessed type int __cdecl _set_errno_dos_(_DWORD);
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (004B5CAE) --------------------------------------------------------
int __fastcall CRT_GetThreadErrnoPtr(int a1, int a2)
{
  return g_CrtThreadDataAccessor(a1, a2) + 4;
}
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004B5E0A) --------------------------------------------------------
BOOL  CRT_IsLeapYear(unsigned int year)
{
  return (year & 3) == 0 && (year % 0x64 || !(year % 0x190));
}

//----- (004B5E3D) --------------------------------------------------------
int  CRT_TzRuleDayOfYear(_DWORD *tzRule, int year)
{
  int ruleType; // ecx
  int v4; // edx
  int ruleMonth; // eax
  int nextMonthYday; // esi
  int monthYday; // eax
  int v8; // eax
  int daysInMonth; // esi
  int weekdayOffset; // edx
  int ruleWeek; // eax
  int weekNumber; // eax
  _DWORD timeFields[14]; // [esp+0h] [ebp-38h] BYREF

  ruleType = tzRule[8];
  if ( ruleType )
  {
    if ( ruleType == 1 )
      return tzRule[7] - 1;
    else
      return tzRule[7];
  }
  else
  {
    if ( CRT_IsLeapYear(year + 1900) )
    {
      ruleMonth = tzRule[4];
      nextMonthYday = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth + 2);
      monthYday = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth);
    }
    else
    {
      v8 = tzRule[4];
      nextMonthYday = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * v8 + 2);
      monthYday = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * v8);
    }
    daysInMonth = (nextMonthYday >> 16) - (monthYday >> 16);
    memset(timeFields, 0, 12);
    timeFields[3] = 1;
    timeFields[4] = tzRule[4];
    timeFields[5] = v4;
    timeFields[8] = 0;
    CRT_MkTime((int)timeFields);
    weekdayOffset = (tzRule[6] - timeFields[6] + 7) % 7;
    ruleWeek = tzRule[3];
    if ( ruleWeek == 5 )
    {
      if ( weekdayOffset + 29 <= daysInMonth )
        weekNumber = 4;
      else
        weekNumber = tzRule[3] - 2;
    }
    else
    {
      weekNumber = ruleWeek - 1;
    }
    return weekdayOffset + timeFields[7] + 7 * weekNumber;
  }
}
// 4B5EAA: variable 'v4' is possibly undefined
// 5110EE: using guessed type int dword_5110EE;
// 511108: using guessed type int dword_511108;

//----- (004B5F22) --------------------------------------------------------
signed int  CRT_TzYearStartsInDaylightTime(_DWORD *dstStartRule, int dstEndRule, int year)
{
  int startMonth; // esi
  int endMonth; // edi
  int startYday; // esi
  _DWORD *v7; // ecx

  if ( dstStartRule[8] || *(_DWORD *)(dstEndRule + 32) )
    goto LABEL_6;
  startMonth = dstStartRule[4];
  endMonth = *(_DWORD *)(dstEndRule + 16);
  if ( startMonth > endMonth )
    return 1;
  if ( startMonth >= endMonth )
  {
LABEL_6:
    startYday = CRT_TzRuleDayOfYear(dstStartRule, year);
    if ( startYday > CRT_TzRuleDayOfYear(v7, year) )
      return 1;
  }
  return 0;
}
// 4B5F55: variable 'v7' is possibly undefined

//----- (004B5F64) --------------------------------------------------------
int  CRT_IsDaylightTime(_DWORD *timeFields)
{
  _DWORD *v1; // ecx
  int inDaylight; // edi
  int v3; // ecx
  int *firstRule; // esi
  int *secondRule; // ebx
  int ruleMonth; // ebp
  int v7; // edx
  int v8; // eax
  int v9; // eax
  int v10; // edx
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // esi
  int v17; // eax
  int v18; // ebp
  int v19; // esi
  int v20; // edx
  int v21; // eax
  int v22; // edx
  int v23; // edx
  int v24; // eax
  int result; // eax
  int v26; // [esp+8h] [ebp-2Ch]
  int v27; // [esp+Ch] [ebp-28h]
  int daysInMonth; // [esp+10h] [ebp-24h]
  signed int startsInDst; // [esp+14h] [ebp-20h]

  v1 = timeFields;
  inDaylight = 0;
  if ( !*g_CRT_TzDaylightNamePtr )
    goto LABEL_54;
  startsInDst = CRT_TzYearStartsInDaylightTime(g_CRT_TzDstStartRule, (int)&g_CRT_TzDstEndRule, timeFields[5]);
  if ( startsInDst )
  {
    firstRule = &g_CRT_TzDstEndRule;
    secondRule = g_CRT_TzDstStartRule;
  }
  else
  {
    firstRule = g_CRT_TzDstStartRule;
    secondRule = &g_CRT_TzDstEndRule;
  }
  ruleMonth = *(_DWORD *)(v3 + 16);
  if ( CRT_IsLeapYear(*(_DWORD *)(v3 + 20) + 1900) )
  {
    v7 = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth + 2);
    v8 = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth);
  }
  else
  {
    v7 = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * ruleMonth + 2);
    v8 = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * ruleMonth);
  }
  daysInMonth = (v7 >> 16) - (v8 >> 16);
  v9 = firstRule[8];
  if ( v9 )
  {
    v13 = firstRule[7];
    if ( v9 == 1 )
    {
      if ( CRT_IsLeapYear(v1[5] + 1900) && v14 > g_CRT_NonLeapFebMarDayThreshold >> 16 )
        ++v14;
      v13 = v14 - 1;
    }
    v15 = v1[7];
    if ( v13 <= v15 )
    {
      inDaylight = 1;
      if ( v13 == v15 )
        goto LABEL_27;
    }
  }
  else
  {
    v10 = firstRule[4];
    if ( ruleMonth > v10 )
    {
      inDaylight = 1;
      goto LABEL_28;
    }
    if ( ruleMonth == v10 )
    {
      v26 = v1[3] - (v1[6] + 7 - firstRule[6]) % 7;
      v11 = firstRule[3];
      v27 = v1[3] - 1 - (v1[6] + 6 - firstRule[6]) % 7;
      if ( v11 == 5 )
      {
        if ( daysInMonth - 7 < v26 )
        {
          inDaylight = 1;
          if ( daysInMonth - 7 >= v27 )
LABEL_27:
            inDaylight = CRT_CompareTzTransitionDate(v1, firstRule) == 0;
        }
      }
      else
      {
        v12 = 7 * (v11 - 1) + 1;
        if ( v12 <= v26 )
        {
          inDaylight = 1;
          if ( v12 > v27 )
            goto LABEL_27;
        }
      }
    }
  }
LABEL_28:
  if ( !inDaylight )
  {
    if ( startsInDst )
      inDaylight = startsInDst;
    goto LABEL_54;
  }
  v16 = secondRule[8];
  if ( v16 )
  {
    v22 = secondRule[7];
    if ( v16 == 1 )
    {
      if ( CRT_IsLeapYear(v1[5] + 1900) && v23 > g_CRT_NonLeapFebMarDayThreshold >> 16 )
        ++v23;
      v22 = v23 - 1;
    }
    v24 = v1[7];
    if ( v22 > v24 )
      goto LABEL_52;
    inDaylight = 0;
    if ( v22 != v24 )
      goto LABEL_52;
    goto LABEL_51;
  }
  v17 = secondRule[4];
  if ( ruleMonth > v17 )
  {
    inDaylight = 0;
    goto LABEL_52;
  }
  if ( ruleMonth != v17 )
    goto LABEL_52;
  v18 = v1[3] - (v1[6] + 7 - secondRule[6]) % 7;
  inDaylight = 0;
  v19 = secondRule[3];
  v20 = v1[3] - 1 - (v1[6] + 6 - secondRule[6]) % 7;
  if ( v19 != 5 )
  {
    v21 = 7 * (v19 - 1) + 1;
    if ( v18 < v21 )
      goto LABEL_37;
    if ( v20 >= v21 )
      goto LABEL_52;
LABEL_51:
    inDaylight = CRT_CompareTzTransitionDate(v1, secondRule);
    goto LABEL_52;
  }
  if ( v18 <= daysInMonth - 7 )
  {
LABEL_37:
    inDaylight = 1;
    goto LABEL_52;
  }
  if ( v20 <= daysInMonth - 7 )
    goto LABEL_51;
LABEL_52:
  if ( startsInDst )
    inDaylight = startsInDst - inDaylight;
LABEL_54:
  result = inDaylight;
  v1[8] = inDaylight;
  return result;
}
// 4B60F4: conditional instruction was optimized away because %var_30.4==0
// 4B61EB: conditional instruction was optimized away because %var_34.4==0
// 4B5FB8: variable 'v3' is possibly undefined
// 4B6034: variable 'v1' is possibly undefined
// 4B60DD: variable 'v14' is possibly undefined
// 4B61D5: variable 'v23' is possibly undefined
// 5110EE: using guessed type int dword_5110EE;
// 5110F2: using guessed type int dword_5110F2;
// 511108: using guessed type int dword_511108;
// 51AF68: using guessed type _DWORD dword_51AF68[9];
// 51AF8C: using guessed type int dword_51AF8C;
// 51B0B6: using guessed type char *off_51B0B6;

//----- (004B6213) --------------------------------------------------------
signed int  CRT_CompareTzTransitionDate(_DWORD *timeFields, _DWORD *tzRule)
{
  int hour; // ecx
  int ruleHour; // esi
  int v4; // ebx
  int minute; // ecx
  int ruleMinute; // ebp

  hour = timeFields[2];
  ruleHour = tzRule[2];
  v4 = 0;
  if ( hour < ruleHour )
    return 1;
  if ( hour == ruleHour )
  {
    minute = timeFields[1];
    ruleMinute = tzRule[1];
    if ( minute < ruleMinute || minute == ruleMinute && *timeFields < *tzRule )
      return 1;
  }
  return v4;
}

//----- (004B63CC) --------------------------------------------------------
void __thiscall CRT_TzSetFromSystemInfo(int this)
{
  DWORD TimeZoneInformation; // eax
  int v4; // ecx
  int v5; // ecx
  struct _TIME_ZONE_INFORMATION v6; // [esp+0h] [ebp-BCh] BYREF
  int v7; // [esp+B4h] [ebp-8h]

  v7 = this;
  if ( (g_TzInitFlags & 1) == 0 || (g_TzInitFlags & 2) == 0 )
  {
    LOBYTE(g_TzInitFlags) = g_TzInitFlags | 2;
    TimeZoneInformation = GetTimeZoneInformation(&v6);
    if ( TimeZoneInformation )
    {
      if ( TimeZoneInformation <= 1 )
      {
        v4 = 0;
        g_TzDaylightFlag = 0;
      }
      else
      {
        if ( TimeZoneInformation != 2 )
          return;
        g_TzDaylightFlag = 1;
        g_CRT_DaylightBiasSeconds = -60 * v6.DaylightBias;
      }
      g_CRT_TimezoneSeconds = 60 * (v6.Bias + v6.StandardBias);
      if ( wcstombs_(v4, v6.StandardName) == -1 )
        g_TzStandardNameBuffer = 0;
      else
        g_CRT_TzStandardNameBufEnd = 0;
      if ( wcstombs_(v5, v6.DaylightName) == -1 )
        g_TzDaylightName = 0;
      else
        g_CRT_TzDaylightNameBufEnd = 0;
    }
  }
}
// 4B6471: variable 'v4' is possibly undefined
// 4B649B: variable 'v5' is possibly undefined
// 4D9993: using guessed type int __fastcall wcstombs_(_DWORD, _DWORD);
// 51AFB0: using guessed type char byte_51AFB0;
// 51B030: using guessed type char byte_51B030;
// 51B031: using guessed type char byte_51B031;
// 51B0B1: using guessed type char byte_51B0B1;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0BE: using guessed type int dword_51B0BE;
// 51B0C2: using guessed type int dword_51B0C2;
// 51B0C6: using guessed type int dword_51B0C6;

//----- (004B64C2) --------------------------------------------------------
void CRT_TzSet()
{
  _BYTE *tzEnvString; // eax
  int v1; // edx
  int v2; // ecx
  _BYTE *afterStdName; // ecx
  _BYTE *afterDstName; // eax
  int v5; // ecx
  _BYTE *ruleCursor; // edx
  int dstOffset[7]; // [esp+0h] [ebp-1Ch] BYREF

  tzEnvString = (_BYTE *)getenv_();
  if ( tzEnvString )
  {
    dstOffset[5] = v2;
    dstOffset[4] = v1;
    g_TzDaylightFlag = 0;
    afterStdName = CRT_ParseTzNameAndOffset(tzEnvString, &g_TzStandardNameBuffer, &g_CRT_TimezoneSeconds);
    if ( *afterStdName )
    {
      g_TzDaylightFlag = 1;
      dstOffset[0] = g_CRT_TimezoneSeconds - 3600;
      afterDstName = CRT_ParseTzNameAndOffset(afterStdName, &g_TzDaylightName, dstOffset);
      v5 = dstOffset[0];
      g_CRT_DaylightBiasSeconds = g_CRT_TimezoneSeconds - dstOffset[0];
      ruleCursor = afterDstName;
      if ( *afterDstName == 44 )
        ruleCursor = CRT_ParseTzDstRule(afterDstName + 1, (int)g_CRT_TzDstStartRule, dstOffset[0]);
      if ( *ruleCursor == 44 )
      {
        CRT_ParseTzDstRule(ruleCursor + 1, (int)&g_CRT_TzDstEndRule, v5);
        g_CRT_TzDstEndRuleHour -= g_CRT_DaylightBiasSeconds / 3600;
        g_CRT_TzDstEndRuleMinute -= g_CRT_DaylightBiasSeconds / 60 % 60;
        g_CRT_TzDstEndRule -= g_CRT_DaylightBiasSeconds % 60;
      }
    }
    else
    {
      g_TzDaylightName = 0;
    }
  }
  else
  {
    CRT_TzSetFromSystemInfo(v2);
  }
}
// 4B64D5: variable 'v2' is possibly undefined
// 4B64D6: variable 'v1' is possibly undefined
// 4B678E: variable 'v5' is possibly undefined
// 4B5CC2: using guessed type int getenv_(void);
// 51AF68: using guessed type _DWORD dword_51AF68[9];
// 51AF8C: using guessed type int dword_51AF8C;
// 51AF90: using guessed type int dword_51AF90;
// 51AF94: using guessed type int dword_51AF94;
// 51AFB0: using guessed type char byte_51AFB0;
// 51B031: using guessed type char byte_51B031;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0BE: using guessed type int dword_51B0BE;
// 51B0C2: using guessed type int dword_51B0C2;

//----- (004B650B) --------------------------------------------------------
_BYTE * CRT_ParseTzDecimalDigits(_BYTE *result, int *valueOut)
{
  int value; // edx
  int v4; // edx

  value = 0;
  while ( *result >= 0x30u && *result <= 0x39u )
  {
    v4 = (unsigned __int8)*result++ + 10 * value;
    value = v4 - 48;
  }
  *valueOut = value;
  return result;
}

//----- (004B6531) --------------------------------------------------------
_BYTE * CRT_ParseTzNameAndOffset(_BYTE *tzString, void *nameBuffer, _DWORD *offsetSecondsOut)
{
  _BYTE *cursor; // ebp
  _BYTE *nameStart; // esi
  unsigned __int8 curChar; // dl
  _BYTE *afterHours; // eax
  int v7; // ecx
  _BYTE *afterMinutes; // eax
  int totalSeconds; // edx
  int seconds; // [esp+4h] [ebp-20h] BYREF
  int minutes; // [esp+8h] [ebp-1Ch] BYREF
  int hours; // [esp+Ch] [ebp-18h] BYREF
  unsigned int nameLength; // [esp+10h] [ebp-14h]

  cursor = tzString;
  if ( *tzString == 58 )
    cursor = tzString + 1;
  nameStart = cursor;
  while ( 1 )
  {
    curChar = *cursor;
    if ( !*cursor || curChar == 44 || curChar == 45 || curChar == 43 || curChar >= 0x30u && curChar <= 0x39u )
      break;
    ++cursor;
  }
  nameLength = cursor - nameStart;
  if ( cursor - nameStart > 128 )
    nameLength = 128;
  qmemcpy(nameBuffer, nameStart, nameLength);
  *((_BYTE *)nameBuffer + nameLength) = 0;
  if ( curChar == 45 || curChar == 43 )
    ++cursor;
  if ( *cursor >= 0x30u && *cursor <= 0x39u )
  {
    seconds = 0;
    minutes = 0;
    hours = 0;
    afterHours = CRT_ParseTzDecimalDigits(cursor, &hours);
    cursor = afterHours;
    if ( *afterHours == 58 )
    {
      afterMinutes = CRT_ParseTzDecimalDigits(afterHours + 1, &minutes);
      cursor = afterMinutes;
      if ( *afterMinutes == 58 )
        cursor = CRT_ParseTzDecimalDigits(afterMinutes + 1, &seconds);
    }
    totalSeconds = 60 * (60 * hours + minutes) + seconds;
    *offsetSecondsOut = totalSeconds;
    if ( v7 )
      *offsetSecondsOut = -totalSeconds;
  }
  return cursor;
}
// 4B6636: variable 'v7' is possibly undefined

//----- (004B6646) --------------------------------------------------------
_BYTE * CRT_ParseTzDstRule(_BYTE *a1, int a2, int a3)
{
  _BYTE *v3; // ebx
  int v4; // esi
  _BYTE *v5; // edx
  _DWORD *v6; // ecx
  _BYTE *v7; // ebx
  _BYTE *v8; // edx
  _BYTE *v9; // eax
  _BYTE *v10; // eax
  int v12; // [esp+0h] [ebp-1Ch] BYREF
  int v13; // [esp+4h] [ebp-18h] BYREF
  int v14; // [esp+8h] [ebp-14h] BYREF
  int v15[4]; // [esp+Ch] [ebp-10h] BYREF

  v15[2] = a3;
  v3 = a1;
  v4 = -1;
  if ( *a1 == 74 )
  {
    v4 = 1;
    v3 = a1 + 1;
  }
  if ( *v3 == 77 )
  {
    ++v3;
    v4 = 0;
  }
  *(_DWORD *)(a2 + 32) = v4;
  v5 = CRT_ParseTzDecimalDigits(v3, v15);
  v7 = v5;
  if ( v4 )
  {
    v6[7] = v15[0];
  }
  else
  {
    v6[4] = v15[0] - 1;
    if ( *v5 == 46 )
    {
      v8 = CRT_ParseTzDecimalDigits(v5 + 1, v15);
      v7 = v8;
      v6[3] = v15[0];
      if ( *v8 == 46 )
      {
        v7 = CRT_ParseTzDecimalDigits(v8 + 1, v15);
        v6[6] = v15[0];
      }
    }
    v6[7] = 0;
  }
  v14 = 2;
  v12 = 0;
  v13 = 0;
  if ( *v7 == 47 )
  {
    v9 = CRT_ParseTzDecimalDigits(v7 + 1, &v14);
    v7 = v9;
    if ( *v9 == 58 )
    {
      v10 = CRT_ParseTzDecimalDigits(v9 + 1, &v13);
      v7 = v10;
      if ( *v10 == 58 )
        v7 = CRT_ParseTzDecimalDigits(v10 + 1, &v12);
    }
  }
  *v6 = v12;
  v6[1] = v13;
  v6[2] = v14;
  return v7;
}
// 4B6685: variable 'v6' is possibly undefined

//----- (004B6DD0) --------------------------------------------------------
int Rules_RegisterPatternConstraintEvaluators()
{
  g_EvalDesc_FetchJoinBindingFieldRecord[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldRecord[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldRecord[4] = (int)(uintptr_t)Rules_FetchJoinBindingFieldRecord;
  g_EvalDesc_FetchJoinBindingFieldSimple[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldSimple[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldSimple[4] = (int)(uintptr_t)Rules_FetchJoinBindingFieldSimple;
  g_EvalDesc_FetchJoinBindingNestedField[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingNestedField[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingNestedField[4] = (int)(uintptr_t)Rules_FetchJoinBindingNestedField;
  g_EvalDesc_FetchPatternFieldRecord[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldRecord[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldRecord[4] = (int)(uintptr_t)Rules_FetchPatternFieldRecord;
  g_EvalDesc_FetchPatternFieldSimple[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldSimple[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldSimple[4] = (int)(uintptr_t)Rules_FetchPatternFieldSimple;
  g_EvalDesc_FetchPatternNestedFieldRecord[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternNestedFieldRecord[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternNestedFieldRecord[4] = (int)(uintptr_t)Rules_FetchPatternNestedFieldRecord;
  g_EvalDesc_TestJoinBindingFieldsEqual[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqual[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqual[4] = (int)(uintptr_t)Rules_TestJoinBindingFieldsEqual;
  g_EvalDesc_TestJoinBindingFieldsEqualRanged[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqualRanged[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqualRanged[4] = (int)(uintptr_t)Rules_TestJoinBindingFieldsEqualRanged;
  g_EvalDesc_EvalPatternFieldsEqual[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalPatternFieldsEqual[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalPatternFieldsEqual[4] = (int)(uintptr_t)Rules_EvalPatternFieldsEqual;
  g_EvalNodeDescCopyMultifieldBinding[4] = (int)(uintptr_t)Rules_EvalCopyMultifieldBinding;
  g_EvalDesc_EvalMultifieldIndexInRange[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalMultifieldIndexInRange[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalMultifieldIndexInRange[4] = (int)(uintptr_t)Rules_EvalMultifieldIndexInRange;
  g_EvalDesc_TestPatternFieldSimple[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternFieldSimple[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternFieldSimple[4] = (int)(uintptr_t)Rules_TestPatternFieldSimple;
  g_EvalDesc_TestPatternNestedField[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternNestedField[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternNestedField[4] = (int)(uintptr_t)Rules_TestPatternNestedField;
  Rules_RegisterEvaluationHandler((int)&g_Rules_FactPatternEntityRecord, 6);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchJoinBindingFieldRecord, 29);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchJoinBindingFieldSimple, 30);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchJoinBindingNestedField, 31);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchPatternFieldRecord, 26);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchPatternFieldSimple, 27);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchPatternNestedFieldRecord, 28);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestJoinBindingFieldsEqual, 23);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestJoinBindingFieldsEqualRanged, 24);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_EvalPatternFieldsEqual, 22);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescCopyMultifieldBinding, 34);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_EvalMultifieldIndexInRange, 25);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestPatternFieldSimple, 32);
  return Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestPatternNestedField, 33);
}

//----- (004B6EB0) --------------------------------------------------------
signed int  Rules_BuildFieldIndexConstraintNode(int a1)
{
  int v1; // edx
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  signed int v6; // ebx
  _DWORD *v7; // ecx
  int v9; // ecx
  unsigned __int8 v10; // al
  int v11; // eax
  signed int v12; // ebx
  _DWORD *v13; // ecx
  int v14; // eax
  int v15; // edx
  signed int v16; // ebx
  int *v17; // ecx
  int v18; // edx
  int v19; // edx
  _DWORD *v20; // ecx
  int v21; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD v22[6]; // [esp+4h] [ebp-18h] BYREF

  if ( (*(_BYTE *)(a1 + 9) & 0x40) != 0 )
  {
    v1 = *(_DWORD *)(a1 + 8);
    if ( (v1 & 0x3F8000) != 0 && ((v1 & 0x3F8000) != 0x8000 || (*(_WORD *)(a1 + 10) & 0x1FC0) != 0) )
    {
      if ( (*(_BYTE *)(a1 + 8) & 1) != 0 )
        v15 = g_ClipsSymbolNeq;
      else
        v15 = g_ClipsSymbolEq;
      v16 = AST_NewNode(10, v15);
      v18 = *v17;
      *v17 = 15;
      *(_DWORD *)(v16 + 6) = PP_MakeLowTierConst((int)v17, v18, (int)v17);
      *v20 = v19;
      *(_DWORD *)(*(_DWORD *)(v16 + 6) + 10) = AST_NewNode(*v20, v20[1]);
      return v16;
    }
    else
    {
      Mem_AllocArray(v22, 4);
      if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
        LOBYTE(v22[0]) &= ~1u;
      else
        LOBYTE(v22[0]) |= 1u;
      v22[0] = ((unsigned __int8)(*(_DWORD *)(v2 + 40) - 1) << 10) | v22[0] & 0xFFFC03FF;
      if ( (*(_DWORD *)(v2 + 8) & 0x3F8000) != 0 )
      {
        LOBYTE(v22[0]) &= ~2u;
        v14 = *(_DWORD *)(v2 + 12) << 18 >> 25;
        LOWORD(v22[0]) &= 0xFC03u;
        v4 = 4 * (unsigned __int8)v14;
      }
      else
      {
        LOBYTE(v22[0]) |= 2u;
        v3 = *(_DWORD *)(v2 + 12) & 0x7F;
        LOWORD(v22[0]) &= 0xFC03u;
        v4 = 4 * v3;
      }
      v22[0] |= v4;
      v5 = Rules_AddBitmapValue(v22, 4);
      v6 = AST_NewNode(33, v5);
      *(_DWORD *)(v6 + 6) = AST_NewNode(*v7, v7[1]);
      return v6;
    }
  }
  else
  {
    Mem_AllocArray(&v21, 4);
    if ( (*(_BYTE *)(v9 + 8) & 1) != 0 )
      LOBYTE(v21) = v21 & 0xFE;
    else
      LOBYTE(v21) = v21 | 1;
    v10 = *(_DWORD *)(v9 + 40) - 1;
    LOWORD(v21) = v21 & 0xFE01;
    v21 |= 2 * v10;
    v11 = Rules_AddBitmapValue(&v21, 4);
    v12 = AST_NewNode(32, v11);
    *(_DWORD *)(v12 + 6) = AST_NewNode(*v13, v13[1]);
    return v12;
  }
}
// 4B6EFB: variable 'v2' is possibly undefined
// 4B6F7E: variable 'v7' is possibly undefined
// 4B6FA0: variable 'v9' is possibly undefined
// 4B6FE7: variable 'v13' is possibly undefined
// 4B705E: variable 'v17' is possibly undefined
// 4B706E: variable 'v19' is possibly undefined
// 4B706E: variable 'v20' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004B70A0) --------------------------------------------------------
signed int  PP_MakeLowTierConst(int a1, int a2, int a3)
{
  int v3; // esi
  int Const28; // edx
  __int16 v5; // ax
  int Const26; // eax

  if ( *(int *)(a1 + 40) > 0 && (*(_BYTE *)(a1 + 9) & 0x40) == 0 )
  {
    Const28 = PP_MakeConst27(a3, a2);
    v5 = 27;
    return AST_NewNode(v5, Const28);
  }
  if ( (*(_DWORD *)a1 == 17 || *(_DWORD *)a1 == 15)
    && ((v3 = *(_DWORD *)(a1 + 8), (v3 & 0x3F8000) == 0)
     || (v3 & 0x3F8000) == 0x8000 && (*(_WORD *)(a1 + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)a1 == 18 || *(_DWORD *)a1 == 16)
    && (*(_DWORD *)(a1 + 8) & 0x3F8000) == 0
    && (*(_WORD *)(a1 + 10) & 0x1FC0) == 0 )
  {
    Const28 = PP_MakeConst28();
    v5 = 28;
    return AST_NewNode(v5, Const28);
  }
  Const26 = PP_MakeConst26();
  return AST_NewNode(26, Const26);
}

//----- (004B7140) --------------------------------------------------------
signed int  PP_ParsePrimary(int a1, int a2, int a3)
{
  int v3; // ecx
  int v4; // esi
  int Const31; // edx
  __int16 v6; // ax
  int v8; // eax

  if ( *(int *)(a1 + 40) > 0 && (*(_BYTE *)(a1 + 9) & 0x40) == 0 )
  {
    Const31 = PP_MakeConst31(a3, a2);
    v6 = 30;
    return AST_NewNode(v6, Const31);
  }
  v3 = *(_DWORD *)a1;
  if ( (*(_DWORD *)a1 == 17 || v3 == 15)
    && ((v4 = *(_DWORD *)(a1 + 8), (v4 & 0x3F8000) == 0)
     || (a2 = v4 & 0x3F8000, (v4 & 0x3F8000) == 0x8000) && (*(_WORD *)(a1 + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)a1 == 18 || *(_DWORD *)a1 == 16)
    && (*(_DWORD *)(a1 + 8) & 0x3F8000) == 0
    && (*(_WORD *)(a1 + 10) & 0x1FC0) == 0 )
  {
    Const31 = PP_MakeConst30(v3, a2);
    v6 = 31;
    return AST_NewNode(v6, Const31);
  }
  v8 = PP_BuildDefault();
  return AST_NewNode(29, v8);
}

//----- (004B71E0) --------------------------------------------------------
signed int  PP_ShouldEmit(int a1)
{
  int v1; // ecx
  int v2; // eax
  int v3; // eax
  unsigned int v5; // eax
  _DWORD v6[4]; // [esp+0h] [ebp-10h] BYREF

  if ( (*(_WORD *)(a1 + 12) & 0x3F80) == 0 && *(_DWORD *)a1 != 15 && *(_DWORD *)a1 != 17 )
    return 0;
  Mem_AllocArray(v6, 4);
  v6[0] = ((unsigned __int8)(*(_DWORD *)(v1 + 40) - 1) << 9) | v6[0] & 0xFFFE01FF;
  if ( *(_DWORD *)v1 == 16 || *(_DWORD *)v1 == 18 || (*(_WORD *)(v1 + 10) & 0x1FC0) != 0 )
    BYTE1(v6[0]) &= ~1u;
  else
    BYTE1(v6[0]) |= 1u;
  if ( *(_DWORD *)v1 == 15 || *(_DWORD *)v1 == 17 )
  {
    v2 = *(_DWORD *)(v1 + 12) << 18 >> 25;
    LOBYTE(v6[0]) = 0;
    v6[0] |= (unsigned __int8)(v2 + 1);
  }
  else
  {
    v5 = *(_DWORD *)(v1 + 12) << 18;
    LOBYTE(v6[0]) = 0;
    v6[0] |= v5 >> 25;
  }
  v3 = Rules_AddBitmapValue(v6, 4);
  return AST_NewNode(25, v3);
}
// 4B7210: variable 'v1' is possibly undefined

//----- (004B72D0) --------------------------------------------------------
signed int __fastcall PP_MakeConst25(int a1, int a2)
{
  char v2; // cl
  int v3; // eax
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a1;
  Mem_AllocArray(v5, 4);
  v5[0] = ((unsigned __int8)(v2 - 1) << 9) | v5[0] & 0xFFFE01FF;
  LOBYTE(v5[0]) = 0;
  BYTE1(v5[0]) |= 1u;
  v3 = Rules_AddBitmapValue(v5, 4);
  return AST_NewNode(25, v3);
}
// 4B72E8: variable 'v2' is possibly undefined

//----- (004B7330) --------------------------------------------------------
int  PP_PatchHighTierConst(_WORD *a1, int a2)
{
  int v3; // eax
  int v4; // edi
  int result; // eax
  int v6; // ecx
  int v7; // ecx

  v3 = a2;
  if ( *(int *)(a2 + 40) > 0 && (*(_BYTE *)(a2 + 9) & 0x40) == 0 )
  {
    *a1 = 30;
    result = PP_MakeConst31((int)a1, a2);
    goto LABEL_11;
  }
  if ( (*(_DWORD *)a2 == 17 || *(_DWORD *)a2 == 15)
    && ((v4 = *(_DWORD *)(a2 + 8), (v4 & 0x3F8000) == 0)
     || (a2 = v4 & 0x3F8000, (v4 & 0x3F8000) == 0x8000) && (*(_WORD *)(v3 + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)v3 == 18 || *(_DWORD *)v3 == 16)
    && (*(_DWORD *)(v3 + 8) & 0x3F8000) == 0
    && (*(_WORD *)(v3 + 10) & 0x1FC0) == 0 )
  {
    *a1 = 31;
    result = PP_MakeConst30((int)a1, a2);
LABEL_11:
    *(_DWORD *)(v6 + 2) = result;
    return result;
  }
  *a1 = 29;
  result = PP_BuildDefault();
  *(_DWORD *)(v7 + 2) = result;
  return result;
}
// 4B7390: variable 'v6' is possibly undefined
// 4B73BA: variable 'v7' is possibly undefined

//----- (004B73D0) --------------------------------------------------------
int  PP_PatchLowTierConst(_WORD *a1, int a2)
{
  int v4; // edx
  int v5; // esi
  int result; // eax
  int v7; // ecx
  int v8; // ecx

  if ( (*(_BYTE *)(a2 + 9) & 0x40) == 0 )
  {
    *a1 = 27;
    result = PP_MakeConst27((int)a1, a2);
    goto LABEL_10;
  }
  v4 = *(_DWORD *)a2;
  if ( (*(_DWORD *)a2 == 17 || v4 == 15)
    && ((v5 = *(_DWORD *)(a2 + 8), (v5 & 0x3F8000) == 0)
     || (v5 & 0x3F8000) == 0x8000 && (*(_WORD *)(a2 + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)a2 == 18 || *(_DWORD *)a2 == 16)
    && (*(_DWORD *)(a2 + 8) & 0x3F8000) == 0
    && (*(_WORD *)(a2 + 10) & 0x1FC0) == 0 )
  {
    *a1 = 28;
    result = PP_MakeConst28();
LABEL_10:
    *(_DWORD *)(v7 + 2) = result;
    return result;
  }
  *a1 = 26;
  result = PP_MakeConst26();
  *(_DWORD *)(v8 + 2) = result;
  return result;
}
// 4B7429: variable 'v7' is possibly undefined
// 4B7452: variable 'v8' is possibly undefined

//----- (004B7460) --------------------------------------------------------
int PP_BuildDefault()
{
  _DWORD *v0; // ecx
  int v1; // eax
  unsigned __int8 v2; // al
  int v3; // eax
  _DWORD v5[6]; // [esp+0h] [ebp-18h] BYREF

  Mem_AllocArray(v5, 4);
  if ( (int)v0[10] <= 0 )
  {
    LOBYTE(v5[0]) |= 1u;
    v5[0] &= 0xFC0003FD;
  }
  else
  {
    v1 = v5[0];
    LOBYTE(v1) = v5[0] & 0xFC;
    if ( (int)v0[8] <= 0 )
    {
      LOBYTE(v1) = v1 | 2;
      v5[0] = v1;
      v5[0] = ((unsigned __int8)(v0[10] - 1) << 10) | v1 & 0xFFFC03FF;
      HIWORD(v5[0]) &= 0xFC03u;
    }
    else
    {
      v5[0] = v1;
      v5[0] = ((unsigned __int8)(v0[10] - 1) << 10) | v1 & 0xFFFC03FF;
      v2 = v0[8] - 1;
      HIWORD(v5[0]) &= 0xFC03u;
      v5[0] |= v2 << 18;
    }
  }
  v3 = v0[7];
  LOWORD(v5[0]) &= 0xFC03u;
  v5[0] |= 4 * (unsigned __int8)(v3 - 1);
  return Rules_AddBitmapValue(v5, 4);
}
// 4B7476: variable 'v0' is possibly undefined

//----- (004B7550) --------------------------------------------------------
int __fastcall PP_MakeConst31(int a1, int a2)
{
  int v2; // ecx
  unsigned __int8 v3; // al
  int v4; // eax
  _DWORD v6[3]; // [esp+0h] [ebp-Ch] BYREF

  v6[2] = a1;
  Mem_AllocArray(v6, 4);
  v3 = *(_DWORD *)(v2 + 40) - 1;
  BYTE1(v6[0]) = 0;
  v6[0] |= v3 << 8;
  v4 = *(_DWORD *)(v2 + 28);
  LOBYTE(v6[0]) = 0;
  v6[0] |= (unsigned __int8)(v4 - 1);
  return Rules_AddBitmapValue(v6, 4);
}
// 4B7563: variable 'v2' is possibly undefined

//----- (004B75B0) --------------------------------------------------------
int __fastcall PP_MakeConst30(int a1, int a2)
{
  _DWORD *v2; // ecx
  unsigned __int8 v3; // al
  unsigned __int8 v4; // al
  int v5; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD v10[5]; // [esp+0h] [ebp-14h] BYREF

  v10[3] = a1;
  Mem_AllocArray(v10, 4);
  v3 = v2[10] - 1;
  HIBYTE(v10[0]) = 0;
  v10[0] |= v3 << 24;
  v4 = v2[7] - 1;
  BYTE2(v10[0]) = 0;
  v10[0] |= v4 << 16;
  if ( *v2 == 17 || *v2 == 15 )
  {
    if ( (v2[2] & 0x3F8000) != 0 )
    {
      LOBYTE(v10[0]) |= 2u;
      LOWORD(v10[0]) &= 0xFE02u;
      v9 = v2[3] << 18 >> 25;
      BYTE1(v10[0]) &= 1u;
      v10[0] |= (v9 & 0x7F) << 9;
    }
    else
    {
      LOBYTE(v10[0]) = v10[0] & 0xFC | 1;
      v5 = v2[3];
      LOWORD(v10[0]) &= 0xFE03u;
      v10[0] |= 4 * (v5 & 0x7F);
      BYTE1(v10[0]) &= 1u;
    }
    return Rules_AddBitmapValue(v10, 4);
  }
  else
  {
    LOBYTE(v10[0]) |= 3u;
    v7 = v2[3] & 0x7F;
    LOWORD(v10[0]) &= 0xFE03u;
    v10[0] |= 4 * v7;
    v8 = v2[3] << 18 >> 25;
    BYTE1(v10[0]) &= 1u;
    v10[0] |= (v8 & 0x7F) << 9;
    return Rules_AddBitmapValue(v10, 4);
  }
}
// 4B75C5: variable 'v2' is possibly undefined

//----- (004B76F0) --------------------------------------------------------
int PP_MakeConst26()
{
  int v0; // ecx
  int v1; // eax
  int v2; // edx
  unsigned __int8 v3; // al
  _DWORD v5[5]; // [esp+0h] [ebp-14h] BYREF

  Mem_AllocArray(v5, 4);
  if ( *(int *)(v0 + 40) <= 0 )
  {
    LOBYTE(v5[0]) |= 1u;
    v5[0] &= 0xFFFC0001;
    return Rules_AddBitmapValue(v5, 4);
  }
  v1 = v5[0];
  LOBYTE(v1) = v5[0] & 0xFC;
  if ( *(int *)(v0 + 32) > 0 )
  {
    v5[0] = v1;
    v2 = (unsigned __int8)(*(_DWORD *)(v0 + 40) - 1);
    v5[0] = (v2 << 10) | v1 & 0xFFFC03FF;
    LOWORD(v2) = ((_WORD)v2 << 10) | v1 & 3;
    v3 = *(_DWORD *)(v0 + 32) - 1;
    LOWORD(v5[0]) = v2;
    v5[0] |= 4 * v3;
    return Rules_AddBitmapValue(v5, 4);
  }
  LOBYTE(v1) = v1 | 2;
  v5[0] = v1;
  v5[0] = ((unsigned __int8)(*(_DWORD *)(v0 + 40) - 1) << 10) | v1 & 0xFFFC03FF;
  LOWORD(v5[0]) &= 0xFC03u;
  return Rules_AddBitmapValue(v5, 4);
}
// 4B7705: variable 'v0' is possibly undefined

//----- (004B77D0) --------------------------------------------------------
int __fastcall PP_MakeConst27(int a1, int a2)
{
  int v2; // ecx
  int v3; // eax
  _DWORD v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  Mem_AllocArray(v5, 4);
  v3 = *(_DWORD *)(v2 + 40);
  LOBYTE(v5[0]) = 0;
  v5[0] |= (unsigned __int8)(v3 - 1);
  return Rules_AddBitmapValue(v5, 4);
}
// 4B77E5: variable 'v2' is possibly undefined

//----- (004B7810) --------------------------------------------------------
int PP_MakeConst28()
{
  _DWORD *v0; // ecx
  unsigned __int8 v1; // al
  int v2; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  _DWORD v7[5]; // [esp+0h] [ebp-14h] BYREF

  Mem_AllocArray(v7, 4);
  v1 = v0[10] - 1;
  BYTE2(v7[0]) = 0;
  v7[0] |= v1 << 16;
  if ( *v0 == 17 || *v0 == 15 )
  {
    if ( (v0[2] & 0x3F8000) != 0 )
    {
      LOBYTE(v7[0]) |= 2u;
      LOWORD(v7[0]) &= 0xFE02u;
      v6 = v0[3];
      BYTE1(v7[0]) &= 1u;
      v7[0] |= (unsigned __int8)((unsigned int)(v6 << 18) >> 24) >> 1 << 9;
    }
    else
    {
      LOBYTE(v7[0]) = v7[0] & 0xFC | 1;
      v2 = v0[3];
      LOWORD(v7[0]) &= 0xFE03u;
      v7[0] |= 4 * (v2 & 0x7F);
      BYTE1(v7[0]) &= 1u;
    }
    return Rules_AddBitmapValue(v7, 4);
  }
  else
  {
    LOBYTE(v7[0]) |= 3u;
    v4 = v0[3] & 0x7F;
    LOWORD(v7[0]) &= 0xFE03u;
    v7[0] |= 4 * v4;
    v5 = v0[3] << 18 >> 25;
    BYTE1(v7[0]) &= 1u;
    v7[0] |= (v5 & 0x7F) << 9;
    return Rules_AddBitmapValue(v7, 4);
  }
}
// 4B7825: variable 'v0' is possibly undefined

//----- (004B7940) --------------------------------------------------------
signed int __fastcall Rules_BuildFieldRangeConstraintNode(int a1, int a2)
{
  int v3; // ecx
  char v4; // al
  char v5; // al
  int v6; // eax
  int v8; // edx
  signed int v9; // eax
  int v10; // ecx
  signed int v11; // eax
  int v12; // edx
  int v13; // ecx
  signed int v14; // eax
  int v15; // edx
  _DWORD v16[4]; // [esp+0h] [ebp-10h] BYREF

  Mem_AllocArray(v16, 4);
  if ( (*(_BYTE *)(v3 + 9) & 0x40) != 0
    || *(int *)(v3 + 40) <= 0
    || (*(_BYTE *)(a2 + 9) & 0x40) != 0
    || *(int *)(a2 + 40) <= 0 )
  {
    if ( (*(_BYTE *)(v3 + 8) & 1) != 0 )
      v8 = g_ClipsSymbolNeq;
    else
      v8 = g_ClipsSymbolEq;
    v9 = AST_NewNode(10, v8);
    v11 = PP_MakeLowTierConst(v10, v9, v10);
    *(_DWORD *)(v12 + 6) = v11;
    v14 = PP_MakeLowTierConst(a2, v12, v13);
    *(_DWORD *)(*(_DWORD *)(v15 + 6) + 10) = v14;
    return v15;
  }
  else
  {
    LOBYTE(v16[0]) &= 0xFCu;
    v4 = *(_DWORD *)(v3 + 40) - 1;
    LOWORD(v16[0]) &= 0xFE03u;
    v16[0] |= 4 * (v4 & 0x7F);
    v5 = *(_DWORD *)(a2 + 40) - 1;
    BYTE1(v16[0]) &= 1u;
    v16[0] |= (v5 & 0x7F) << 9;
    if ( (*(_BYTE *)(v3 + 8) & 1) != 0 )
      LOBYTE(v16[0]) |= 2u;
    else
      LOBYTE(v16[0]) |= 1u;
    v6 = Rules_AddBitmapValue(v16, 4);
    return AST_NewNode(22, v6);
  }
}
// 4B7956: variable 'v3' is possibly undefined
// 4B7A1C: variable 'v10' is possibly undefined
// 4B7A21: variable 'v12' is possibly undefined
// 4B7A26: variable 'v13' is possibly undefined
// 4B7A2B: variable 'v15' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004B7A50) --------------------------------------------------------
signed int  Rules_BuildFieldRangeOrValueConstraintNode(int a1, int a2)
{
  int v4; // ecx
  char v5; // al
  unsigned int v6; // eax
  int v7; // eax
  int v9; // eax
  _DWORD *v10; // ecx
  char v11; // al
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edx
  signed int v16; // eax
  int v17; // ecx
  signed int v18; // eax
  int v19; // edx
  int v20; // ecx
  signed int v21; // eax
  int v22; // edx
  unsigned int v23; // [esp+0h] [ebp-20h] BYREF
  int v24; // [esp+4h] [ebp-1Ch]
  _DWORD v25[6]; // [esp+8h] [ebp-18h] BYREF

  if ( (*(_BYTE *)(a1 + 9) & 0x40) != 0
    || *(int *)(a1 + 40) <= 0
    || (*(_BYTE *)(a2 + 9) & 0x40) != 0
    || *(int *)(a2 + 40) <= 0 )
  {
    if ( *(int *)(a1 + 40) <= 0
      || *(_DWORD *)a1 != 15
      || (v9 = *(_DWORD *)(a1 + 8), (v9 & 0x3F8000) != 0)
      && ((v9 & 0x3F8000) != 0x8000 || (*(_WORD *)(a1 + 10) & 0x1FC0) != 0)
      || *(int *)(a2 + 40) <= 0
      || *(_DWORD *)a2 != 15
      || (*(_DWORD *)(a2 + 8) & 0x3F8000) != 0 && (*(_WORD *)(a2 + 10) & 0x1FC0) != 0 )
    {
      if ( (*(_BYTE *)(a1 + 8) & 1) != 0 )
        v15 = g_ClipsSymbolNeq;
      else
        v15 = g_ClipsSymbolEq;
      v16 = AST_NewNode(10, v15);
      v18 = PP_ParsePrimary(v17, v16, v17);
      *(_DWORD *)(v19 + 6) = v18;
      v21 = PP_ParsePrimary(a2, v19, v20);
      *(_DWORD *)(*(_DWORD *)(v22 + 6) + 10) = v21;
      return v22;
    }
    else
    {
      Mem_AllocArray(&v23, 8);
      LOBYTE(v23) = v23 & 0xFC;
      v11 = v10[10] - 1;
      LOWORD(v23) = v23 & 0xFE03;
      v23 |= 4 * (v11 & 0x7F);
      v12 = (unsigned __int8)*(_DWORD *)(a2 + 28);
      HIWORD(v23) &= 0xFE01u;
      v23 |= v12 << 17;
      LOBYTE(v12) = *(_DWORD *)(a2 + 40) - 1;
      HIBYTE(v23) &= 1u;
      v23 |= (unsigned __int8)v12 << 25;
      if ( (v10[2] & 0x3F8000) != 0 )
      {
        BYTE1(v23) &= ~2u;
        v23 = ((unsigned __int8)(v10[3] << 18 >> 24) >> 1 << 10) | v23 & 0xFFFE03FF;
      }
      else
      {
        BYTE1(v23) |= 2u;
        v23 = ((v10[3] & 0x7F) << 10) | v23 & 0xFFFE03FF;
      }
      if ( (*(_DWORD *)(a2 + 8) & 0x3F8000) != 0 )
      {
        LOBYTE(v24) = v24 & 0xFE;
        v13 = *(_DWORD *)(a2 + 12) << 18 >> 25;
      }
      else
      {
        LOBYTE(v24) = v24 | 1;
        v13 = *(_DWORD *)(a2 + 12);
      }
      v24 |= 2 * (v13 & 0x7F);
      if ( (v10[2] & 1) != 0 )
        LOBYTE(v23) = v23 | 2;
      else
        LOBYTE(v23) = v23 | 1;
      v14 = Rules_AddBitmapValue(&v23, 8);
      return AST_NewNode(24, v14);
    }
  }
  else
  {
    Mem_AllocArray(v25, 4);
    LOBYTE(v25[0]) &= 0xFCu;
    v5 = *(_DWORD *)(v4 + 40) - 1;
    LOWORD(v25[0]) &= 0xFE03u;
    v25[0] |= 4 * (v5 & 0x7F);
    v25[0] = ((unsigned __int8)*(_DWORD *)(a2 + 28) << 9) | v25[0] & 0xFFFE01FF;
    v6 = v25[0] & 0xFF01FFFF;
    if ( *(int *)(a2 + 32) >= 0 )
      v6 |= (((unsigned __int8)*(_DWORD *)(a2 + 40) - 1) & 0x7F) << 17;
    v25[0] = v6;
    if ( (*(_BYTE *)(v4 + 8) & 1) != 0 )
      LOBYTE(v25[0]) |= 2u;
    else
      LOBYTE(v25[0]) |= 1u;
    v7 = Rules_AddBitmapValue(v25, 4);
    return AST_NewNode(23, v7);
  }
}
// 4B7C33: masking with 0x1 was optimized away because %var_1C.1 <= 0x1
// 4B7A9B: variable 'v4' is possibly undefined
// 4B7B88: variable 'v10' is possibly undefined
// 4B7CA6: variable 'v17' is possibly undefined
// 4B7CAB: variable 'v19' is possibly undefined
// 4B7CB0: variable 'v20' is possibly undefined
// 4B7CB5: variable 'v22' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004B7D50) --------------------------------------------------------
int  Rules_ParseOrderedFactPattern(int a1, int a2)
{
  signed int v4; // esi
  char v5; // ah
  _DWORD *v6; // eax
  unsigned int *v7; // eax

  v4 = AST_AllocNode();
  *(_DWORD *)v4 = 17;
  v5 = *(_BYTE *)(v4 + 8);
  *(_DWORD *)(v4 + 32) = -1;
  *(_DWORD *)(v4 + 40) = 1;
  *(_BYTE *)(v4 + 8) = v5 & 0xFE;
  v6 = (_DWORD *)AST_AllocNode();
  *(_DWORD *)(v4 + 68) = v6;
  *v6 = 2;
  *(_BYTE *)(*(_DWORD *)(v4 + 68) + 8) &= ~1u;
  *(_DWORD *)(*(_DWORD *)(v4 + 68) + 4) = *(_DWORD *)(a2 + 4);
  IO_OutWriteToken(asc_509EB8);
  Parser_NextToken(a1, a2);
  if ( *(_DWORD *)a2 == 92 || *(_DWORD *)a2 == 91 )
  {
    AST_FreeNode(v4);
    Parser_ReportSyntaxError();
    return 0;
  }
  else
  {
    v7 = Rules_ParsePatternFieldList(a1, (int *)a2, 0, 1, 1u, 0, 1);
    if ( v7 )
    {
      *(_DWORD *)(v4 + 64) = v7;
      if ( *(_DWORD *)a2 == 101 )
      {
        if ( !v7[17] )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken(asc_509EEC);
        }
        return v4;
      }
      else
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_509EB8);
        IO_OutWriteToken(*(char **)(a2 + 8));
        Parser_ReportSyntaxError();
        AST_FreeNode(v4);
        return 0;
      }
    }
    else
    {
      AST_FreeNode(v4);
      return 0;
    }
  }
}

//----- (004B7E60) --------------------------------------------------------
int __fastcall Rules_CreateInitialFactPatternNode(int a1, int a2)
{
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  int v4; // edx
  int v5; // ecx
  signed int *v6; // eax
  int v7; // edx
  int v9; // ecx
  int v10; // eax
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  signed int *v15; // eax
  char v16; // dl
  _DWORD v17[4]; // [esp+0h] [ebp-10h] BYREF

  v17[2] = a1;
  if ( !Rules_FindImportExportConstruct(aDeftemplate_7, v17, aInitialFact, 1, 0) )
  {
    Rules_PrintWarningID((int)aFactlhs, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aCreatingImplie, v9);
    v10 = Module_GetCurrent();
    Name = Module_GetName(v10);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], Name, (int)g_IO_LogicalNameTable_WWarning[0]);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)a__22, v12);
    Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aYouProbablyWan, v13);
    v15 = Str_Intern(aInitialFact, v14);
    Rules_CreateDeftemplateRecord((int)v15, v16);
  }
  v2 = (_DWORD *)AST_AllocNode();
  *v2 = 17;
  v2[8] = 0;
  v2[10] = 1;
  v3 = (_DWORD *)AST_AllocNode();
  *(_DWORD *)(v4 + 68) = v3;
  *v3 = 2;
  v6 = Str_Intern(aInitialFact, v5);
  *(_DWORD *)(*(_DWORD *)(v7 + 68) + 4) = v6;
  return v7;
}
// 4B7EE0: variable 'v9' is possibly undefined
// 4B7F08: variable 'v12' is possibly undefined
// 4B7F17: variable 'v13' is possibly undefined
// 4B7F23: variable 'v14' is possibly undefined
// 4B7F28: variable 'v16' is possibly undefined
// 4B7EA3: variable 'v4' is possibly undefined
// 4B7EB1: variable 'v5' is possibly undefined
// 4B7EB6: variable 'v7' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];

//----- (004B7F50) --------------------------------------------------------
int  Rules_ParseFactPatternRelation(int a1, int a2, int a3)
{
  int v5; // edx
  int v6; // eax
  _BYTE *v8; // ebx
  int v9; // eax
  _DWORD v10[5]; // [esp+0h] [ebp-14h] BYREF

  v10[3] = a3;
  if ( Rules_FindModuleSeparator(*(_BYTE **)(*(_DWORD *)(a2 + 4) + 16)) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  v6 = Rules_FindImportExportConstruct(aDeftemplate_7, v10, *(_BYTE **)(*(_DWORD *)(v5 + 4) + 16), 1, 0);
  if ( v10[0] > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)aDeftemplate_7, *(_DWORD *)(*(_DWORD *)(a2 + 4) + 16));
    return 0;
  }
  if ( !v6 )
  {
    v8 = *(_BYTE **)(*(_DWORD *)(a2 + 4) + 16);
    v9 = Module_GetCurrent();
    if ( Rules_FindImportExportConflict(aDeftemplate_7, v9, v8) )
    {
      Lexer_WarnImpliedTemplate((int)aImpliedDefte_0, *(_DWORD *)(*(_DWORD *)(a2 + 4) + 16), 0);
      return 0;
    }
    v6 = Rules_CreateDeftemplateRecord(*(_DWORD *)(a2 + 4), 1);
  }
  if ( (*(_BYTE *)(v6 + 24) & 1) != 0 )
    return Rules_ParseOrderedFactPattern(a1, a2);
  else
    return Rules_ParseDeftemplateFactPattern(a1, (_DWORD *)v6);
}
// 4B7F6F: variable 'v5' is possibly undefined

//----- (004B8030) --------------------------------------------------------
int * Rules_AddReservedPatternSymbol(int a1, int a2)
{
  int v2; // ecx
  _DWORD *v3; // ebx
  int *result; // eax

  v2 = a1;
  v3 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( v3 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *v3;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = v2;
  result[1] = a2;
  result[2] = g_Rules_ReservedPatternSymbolList;
  g_Rules_ReservedPatternSymbolList = (int)result;
  return result;
}
// 4B8050: variable 'v2' is possibly undefined
// 51B350: using guessed type int dword_51B350;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B8080) --------------------------------------------------------
int __fastcall Rules_IsReservedPatternSymbol(int a1, int a2)
{
  int item; // ecx
  int v5; // edx
  int result; // eax

  item = g_Rules_ReservedPatternSymbolList;
  if ( !item )
    return 0;
  while ( strcmp_(a1, *(_DWORD *)item) )
  {
    item = *(_DWORD *)(item + 8);
    if ( !item )
      return 0;
  }
  v5 = *(_DWORD *)(item + 4);
  if ( !v5 )
    return 1;
  if ( !a2 )
    return 1;
  result = strcmp_(a2, v5);
  if ( result )
    return 1;
  return result;
}
// 4B809E: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B350: using guessed type int dword_51B350;

//----- (004B80D0) --------------------------------------------------------
signed int __fastcall Rules_PrintReservedSymbolErrorMessage(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  Rules_PrintErrorID((int)aPattern, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheSymbol, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aHasSpecialMean, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAndMayNotBeUse, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v7);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__8, v8);
}
// 4B80F2: variable 'v3' is possibly undefined
// 4B80FE: variable 'v4' is possibly undefined
// 4B810D: variable 'v5' is possibly undefined
// 4B811C: variable 'v6' is possibly undefined
// 4B8128: variable 'v7' is possibly undefined
// 4B8137: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B8140) --------------------------------------------------------
int  Rules_FindPatternParser(_DWORD *a1, _DWORD *a2)
{
  int current; // edx
  int callback_table; // edx
  int callback_address; // eax
  int result; // eax

  current = *a1;
  if ( current )
  {
    if ( a2 )
    {
      callback_table = *(_DWORD *)(current + 4);
      callback_address = *(_DWORD *)(callback_table + 20);
      result = ((int (__fastcall *)(int))(uintptr_t)(unsigned int)callback_address)(*a2);
      *a2 = result;
      if ( result )
        return result;
      result = *(_DWORD *)(current + 92);
      *a1 = result;
    }
    else
    {
      Rules_ReportSystemError(a1, 1);
      result = IO_RunRouterExitCallbacks();
    }
  }
  else
  {
    result = g_PatternParserListHead;
    *a1 = g_PatternParserListHead;
    *a2 = 0;
  }
  while ( !*a2 )
  {
    current = *a1;
    if ( !current )
      break;
    callback_table = *(_DWORD *)(current + 4);
    callback_address = *(_DWORD *)(callback_table + 20);
    result = ((int (__fastcall *)(int))(uintptr_t)(unsigned int)callback_address)(*a2);
    *a2 = result;
    if ( result )
      break;
    result = *(_DWORD *)(current + 92);
    *a1 = result;
  }
  return result;
}
// 51B348: using guessed type int dword_51B348;

//----- (004B81C0) --------------------------------------------------------
int  Rules_DeletePatternNetworkForType(int result, int *a2, int a3)
{
  int v3; // ecx

  if ( g_CLIPS_PatternParserTableByTypeId[result] )
  {
    Rules_ReleaseJoinNetworkNodeChain(*a2);
    return (*(int (__cdecl **)(int))(*(int *)((char *)g_CLIPS_PatternParserTableByTypeId + v3) + 28))(a3);
  }
  return result;
}
// 4B81DA: variable 'v3' is possibly undefined
// 54E820: using guessed type int dword_54E820[];

//----- (004B81F0) --------------------------------------------------------
signed int  Rules_AddPatternParser(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        int a21,
        int a22)
{
  int v24; // ecx
  _DWORD *v25; // ebp
  _DWORD *v26; // eax
  int v27; // edx
  int v28; // ebx
  int v29; // edi
  int v30; // eax

  v24 = 0;
  if ( g_PatternParserCount >= 8 )
    return 0;
  v25 = *(_DWORD **)(g_ClipsMemoryTable + 384);
  if ( v25 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 384);
    *(_DWORD *)(g_ClipsMemoryTable + 384) = *v25;
    v26 = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v26 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x60);
  }
  v26[1] = a4;
  v26[3] = a3;
  v26[22] = a2;
  *v26 = a1;
  v26[4] = a5;
  v26[5] = a6;
  v26[6] = a7;
  v26[7] = a8;
  v26[8] = a9;
  v26[9] = a10;
  v26[10] = a11;
  v26[11] = a12;
  v26[12] = a13;
  v26[13] = a14;
  v26[14] = a15;
  v26[15] = a16;
  v26[16] = a17;
  v26[17] = a18;
  v26[18] = a19;
  v26[19] = a20;
  v26[20] = a21;
  v26[21] = a22;
  v27 = g_PatternParserCount;
  v26[2] = g_PatternParserCount;
  ++v27;
  v28 = (int)v26;
  v29 = g_PatternParserListHead;
  g_Rules_PatternParserTable[v27] = (int)v26;
  g_PatternParserCount = v27;
  if ( !v29 )
  {
    v26[23] = 0;
    g_PatternParserListHead = (int)v26;
    return 1;
  }
  v30 = v29;
  do
  {
    if ( a2 >= *(_DWORD *)(v30 + 88) )
      break;
    v24 = v30;
    v30 = *(_DWORD *)(v30 + 92);
  }
  while ( v30 );
  if ( !v24 )
  {
    *(_DWORD *)(v28 + 92) = g_PatternParserListHead;
    g_PatternParserListHead = v28;
    return 1;
  }
  *(_DWORD *)(v28 + 92) = v30;
  *(_DWORD *)(v24 + 92) = v28;
  return 1;
}
// 4B82E8: conditional instruction was optimized away because edi.4!=0
// 4B8303: variable 'v24' is possibly undefined
// 51B348: using guessed type int dword_51B348;
// 51B34C: using guessed type int dword_51B34C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E81C: using guessed type int dword_54E81C[];

//----- (004B8360) --------------------------------------------------------
int  Rules_FindPatternParserByName(int a1)
{
  int v2; // ecx
  int v3; // ecx

  v2 = g_PatternParserListHead;
  if ( !g_PatternParserListHead )
    return 0;
  while ( strcmp_(v2, a1) )
  {
    v2 = *(_DWORD *)(v3 + 92);
    if ( !v2 )
      return 0;
  }
  return v3;
}
// 4B837C: variable 'v3' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B348: using guessed type int dword_51B348;

//----- (004B8390) --------------------------------------------------------
int  Rules_GetPatternParserByTypeID(int a1)
{
  return g_CLIPS_PatternParserTableByTypeId[a1];
}
// 54E820: using guessed type int dword_54E820[];

//----- (004B83A0) --------------------------------------------------------
int  Rules_PrintPatternNetworkNodeTrace(int a1, int a2, int a3)
{
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // ecx
  char v11; // [esp+0h] [ebp-Ch]
  char v12; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)aNullNull, v11);
  if ( *(_DWORD *)(v7 + 8) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      *(_DWORD *)(*(_DWORD *)(a2 + 8) + 4) % a3,
      a1,
      (int)aSD_DD_4,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v6, 0, a1, (int)aNull_15, v12);
  return Output_WriteFormatted(v9, v8, a1, (int)aDDD00DD, *(_BYTE *)(a2 + 12) & 1);
}
// 4B83B1: variable 'v11' is possibly undefined
// 4B83B6: variable 'v7' is possibly undefined
// 4B83C6: variable 'v6' is possibly undefined
// 4B83C6: variable 'v12' is possibly undefined
// 4B8403: variable 'v9' is possibly undefined
// 4B8403: variable 'v8' is possibly undefined
// 54E884: using guessed type int dword_54E884;

//----- (004B8450) --------------------------------------------------------
signed int  Rules_PatternChainHasActiveType80Callback(_DWORD *a1)
{
  _DWORD *v1; // edx
  int v2; // ebx

  v1 = a1;
  if ( !a1 )
    return 0;
  while ( 1 )
  {
    if ( *v1 == 80 )
    {
      v2 = v1[6];
      if ( v2 )
      {
        if ( *(_DWORD *)(v2 + 20) && (*(int (**)(void))(v2 + 20))() )
          break;
      }
    }
    v1 = (_DWORD *)v1[17];
    if ( !v1 )
      return 0;
  }
  return 1;
}
// 4B8478: variable 'v1' is possibly undefined

//----- (004B8490) --------------------------------------------------------
unsigned int * Rules_ParsePatternFieldList(
        int a1,
        int *a2,
        int a3,
        int a4,
        unsigned int a5,
        int *a6,
        int a7)
{
  int v9; // ebx
  signed int v10; // eax
  unsigned int *v11; // ebx
  int v12; // ecx
  int v14; // ebx
  int v15; // eax
  int v16; // ebp
  signed int v17; // eax
  char v18; // dh
  int v19; // esi
  int v20; // ecx
  int *v21; // eax
  signed int v22; // eax
  int v23; // ecx
  int *v24; // eax
  int v25; // [esp+0h] [ebp-28h] BYREF
  int v26; // [esp+4h] [ebp-24h]
  int v27; // [esp+8h] [ebp-20h]
  unsigned int *v28; // [esp+Ch] [ebp-1Ch]
  int v29; // [esp+10h] [ebp-18h]
  int v30; // [esp+14h] [ebp-14h]
  int v31; // [esp+18h] [ebp-10h]

  v29 = a4;
  v27 = a3;
  v28 = 0;
  v31 = 0;
  v25 = 0;
  v30 = 0;
  v9 = *a2;
  v26 = a7;
  if ( v9 == 101 )
  {
LABEL_24:
    if ( !v28 && !v29 )
    {
      Parser_ReportSyntaxError();
      return 0;
    }
    v14 = (int)v28;
    if ( !v28 )
    {
LABEL_33:
      if ( v29 )
      {
        v17 = AST_AllocNode();
        *(_DWORD *)v17 = 18;
        v18 = *(_BYTE *)(v17 + 8);
        *(_DWORD *)(v17 + 16) = a6;
        *(_BYTE *)(v17 + 8) = v18 | 4;
        *(_DWORD *)(v17 + 68) = v28;
        *(_DWORD *)(v17 + 36) = v27;
        *(_DWORD *)(v17 + 40) = a5;
        *(_DWORD *)(v17 + 32) = v26;
        v28 = (unsigned int *)v17;
        Rules_ComputePatternFieldPositions(*(_DWORD **)(v17 + 68));
      }
      return v28;
    }
    while ( !a6 )
    {
      if ( *(_DWORD *)v14 == 15 )
      {
        v15 = Rules_CreateLHSParseNode();
LABEL_30:
        *(_DWORD *)(v14 + 16) = v15;
        AST_Free(*(_DWORD *)(*(_DWORD *)(v14 + 16) + 18));
        AST_Free(*(_DWORD *)(*(_DWORD *)(v14 + 16) + 22));
        *(_DWORD *)(*(_DWORD *)(v14 + 16) + 18) = AST_NewNode(2, g_Clips_NegativeInfinitySymbol);
        *(_DWORD *)(*(_DWORD *)(v14 + 16) + 22) = AST_NewNode(2, g_ClipsPositiveInfinitySymbol);
        v16 = *(_DWORD *)v14;
        *(_BYTE *)(v14 + 8) |= 0x10u;
        if ( v16 == 18 || v16 == 16 )
        {
          v19 = Rules_CreateLHSParseNode();
          Rules_UpdateCETypeFlag(4u, v19);
          *(_BYTE *)(v20 + 2) &= ~1u;
          *(_DWORD *)(v20 + 26) = *(_DWORD *)(v14 + 16);
          *(_DWORD *)(v14 + 16) = v20;
          if ( g_ClipsPositiveInfinitySymbol != *(_DWORD *)(*(int *)((char *)a6 + 22) + 2) )
          {
            AST_Free(*(_DWORD *)(v20 + 22));
            v21 = Rules_AddIntegerValue(*(_DWORD *)(*(_DWORD *)(*(int *)((char *)a6 + 22) + 2) + 16) - v31);
            v22 = AST_NewNode(1, (int)v21);
            *(_DWORD *)(v23 + 22) = v22;
          }
          if ( v30 == 1 && g_Clips_NegativeInfinitySymbol != *(_DWORD *)(*(int *)((char *)a6 + 18) + 2) )
          {
            AST_Free(*(_DWORD *)(v19 + 18));
            v24 = Rules_AddIntegerValue(*(_DWORD *)(*(_DWORD *)(*(int *)((char *)a6 + 18) + 2) + 16) - v31);
            *(_DWORD *)(v19 + 18) = AST_NewNode(1, (int)v24);
          }
        }
      }
      v14 = *(_DWORD *)(v14 + 64);
      if ( !v14 )
        goto LABEL_33;
    }
    v15 = Rules_CloneLHSParseNode(a6);
    goto LABEL_30;
  }
  while ( 1 )
  {
    if ( *a2 == 17 || *a2 == 18 )
    {
      v10 = AST_AllocNode();
      *(_DWORD *)v10 = *a2;
      v11 = (unsigned int *)v10;
      *(_BYTE *)(v10 + 8) &= ~1u;
      Parser_NextToken(a1, (int)a2);
    }
    else
    {
      v11 = Rules_ParseConnectedConstraint(a1, &v25);
      if ( !v11 )
      {
        AST_FreeNode((int)v28);
        return 0;
      }
    }
    if ( *a2 != 101 && v29 == 1 )
    {
      IO_OutNewline();
      IO_OutWriteToken(asc_50A02C);
      IO_OutWriteToken((char *)a2[2]);
    }
    if ( *v11 == 17 || *v11 == 15 )
      ++v31;
    else
      ++v30;
    v11[9] = v27;
    v11[10] = a5;
    v11[8] = a7++;
    if ( !v29 )
      break;
    if ( v12 )
      *(_DWORD *)(v12 + 64) = v11;
    else
      v28 = v11;
    if ( *a2 == 101 )
      goto LABEL_24;
  }
  if ( a6 )
  {
    v11[4] = (unsigned int)a6;
  }
  else if ( *v11 == 15 )
  {
    v11[4] = Rules_CreateLHSParseNode();
  }
  else
  {
    v11[4] = v29;
  }
  return v11;
}
// 4B85A2: variable 'v12' is possibly undefined
// 4B86E3: variable 'v20' is possibly undefined
// 4B8726: variable 'v23' is possibly undefined
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004B8780) --------------------------------------------------------
int  Rules_ComputePatternFieldPositions(_DWORD *a1)
{
  _DWORD *v2; // edx
  int result; // eax
  int v4; // ecx
  char v5; // di
  char i; // si
  int v7; // edx
  int v8; // ebp
  unsigned int v9; // ecx
  char v10; // bh
  int v11; // ebp
  __int16 v12; // cx
  int v13; // ebp
  int v14; // ecx
  int v15; // ebx
  bool j; // zf
  int v17; // ecx
  int v18; // ecx
  unsigned int v19; // ebp
  int v20; // ecx
  int v21; // ecx
  char v22; // [esp+4h] [ebp-28h]
  char v23; // [esp+8h] [ebp-24h]
  int v24; // [esp+Ch] [ebp-20h]
  char v25; // [esp+10h] [ebp-1Ch]

  v2 = a1;
  result = 0;
  v4 = 0;
  v5 = 0;
  for ( i = 0; v2; v2 = (_DWORD *)v2[16] )
  {
    if ( *v2 == 15 || *v2 == 17 )
      ++result;
    else
      ++v4;
  }
  v7 = (int)a1;
  if ( a1 )
  {
    v24 = v4 - 1;
    v25 = v4;
    v23 = result;
    v22 = result - 1;
    do
    {
      *(_BYTE *)(v7 + 12) &= 0x80u;
      v8 = v5 & 0x7F | *(_DWORD *)(v7 + 12);
      v9 = *(_DWORD *)(v7 + 8) & 0xFFC07FFF;
      *(_DWORD *)(v7 + 8) = v9;
      *(_DWORD *)(v7 + 8) = ((i & 0x7F) << 15) | v9;
      v10 = *(_BYTE *)(v7 + 9);
      *(_DWORD *)(v7 + 12) = v8;
      v11 = *(_DWORD *)v7;
      *(_BYTE *)(v7 + 9) = v10 | 0x40;
      if ( v11 == 15 || v11 == 17 )
      {
        v12 = *(_WORD *)(v7 + 10);
        *(_WORD *)(v7 + 12) &= 0xC07Fu;
        v13 = ((v22 & 0x7F) << 7) | *(_DWORD *)(v7 + 12);
        *(_WORD *)(v7 + 10) = v12 & 0xE03F;
        v14 = *(_DWORD *)(v7 + 8);
        result = (v25 & 0x7F) << 22;
        *(_DWORD *)(v7 + 12) = v13;
        *(_DWORD *)(v7 + 8) = result | v14;
      }
      else
      {
        *(_WORD *)(v7 + 12) &= 0xC07Fu;
        *(_DWORD *)(v7 + 12) |= (v23 & 0x7F) << 7;
        *(_WORD *)(v7 + 10) &= 0xE03Fu;
        result = (v24 & 0x7F) << 22;
        *(_DWORD *)(v7 + 8) |= result;
      }
      v15 = *(_DWORD *)(v7 + 68);
      for ( j = v15 == 0; v15; j = v15 == 0 )
      {
        result = v15;
        if ( !j )
        {
          do
          {
            v17 = *(_DWORD *)(v7 + 12);
            *(_BYTE *)(result + 12) &= 0x80u;
            *(_DWORD *)(result + 12) |= v17 & 0x7F;
            v18 = *(_DWORD *)(v7 + 12);
            *(_WORD *)(result + 12) &= 0xC07Fu;
            *(_DWORD *)(result + 12) |= v18 & 0x3F80;
            v19 = *(_DWORD *)(result + 8) & 0xFFC07FFF;
            v20 = *(_DWORD *)(v7 + 8) & 0x3F8000;
            *(_DWORD *)(result + 8) = v19;
            *(_DWORD *)(result + 8) = v20 | v19;
            v21 = *(_DWORD *)(v7 + 8);
            *(_WORD *)(result + 10) &= 0xE03Fu;
            *(_DWORD *)(result + 8) |= v21 & 0x1FC00000;
            *(_BYTE *)(result + 9) |= 0x40u;
            result = *(_DWORD *)(result + 64);
          }
          while ( result );
        }
        v15 = *(_DWORD *)(v15 + 68);
      }
      if ( *(_DWORD *)v7 == 15 || *(_DWORD *)v7 == 17 )
      {
        ++v5;
        --v23;
        --v22;
      }
      else
      {
        ++i;
        result = --v24;
        --v25;
      }
      v7 = *(_DWORD *)(v7 + 64);
    }
    while ( v7 );
  }
  return result;
}

//----- (004B8970) --------------------------------------------------------
unsigned int * Rules_ParseConnectedConstraint(int a1, _DWORD *a2)
{
  int v3; // ecx
  unsigned int *v4; // ebp
  unsigned int *v5; // edi
  int *v7; // ecx
  char v8; // ah
  unsigned int *v9; // eax
  int v10; // ecx
  signed int v11; // eax
  unsigned int v12; // ebx
  char v13; // dl
  int v14; // ecx
  unsigned int *v16; // [esp+4h] [ebp-1Ch]
  int v17; // [esp+8h] [ebp-18h]

  v4 = Rules_ParseSingleFieldConstraintTerm(a1, a2);
  v5 = v4;
  if ( *a2 == 1 )
    return 0;
  Parser_NextToken(a1, v3);
  if ( *v4 != 15 && *v4 != 16 || (v8 = *((_BYTE *)v4 + 8), (v8 & 1) != 0) || *v7 == 92 )
  {
    v11 = AST_AllocNode();
    v12 = *v4;
    v16 = (unsigned int *)v11;
    *(_DWORD *)(v11 + 68) = v4;
    v13 = *(_BYTE *)(v11 + 8) & 0xFE;
    *(_DWORD *)v11 = (v12 == 16) + 17;
    *(_BYTE *)(v11 + 8) = v13;
  }
  else
  {
    v16 = v4;
    v4 = 0;
    *((_BYTE *)v5 + 8) = v8 | 8;
    v5 = 0;
  }
  while ( *v7 == 92 || *v7 == 91 )
  {
    v17 = *v7;
    Parser_NextToken(a1, (int)v7);
    v9 = Rules_ParseSingleFieldConstraintTerm(a1, a2);
    if ( *a2 == 1 )
    {
      AST_FreeNode((int)v16);
      return 0;
    }
    if ( v17 == 92 )
    {
      if ( v4 )
        v4[17] = (unsigned int)v9;
      else
        v16[17] = (unsigned int)v9;
      v4 = v9;
      v5 = v9;
      Parser_NextToken(a1, v10);
    }
    else if ( v17 == 91 )
    {
      if ( v5 )
      {
        v5[16] = (unsigned int)v9;
      }
      else
      {
        v4 = v9;
        v16[17] = (unsigned int)v9;
      }
      v5 = v9;
      Parser_NextToken(a1, v10);
    }
    else
    {
      Rules_ReportSystemError(v10, 1);
      IO_RunRouterExitCallbacks();
      Parser_NextToken(a1, v14);
    }
  }
  if ( !Rules_CheckMixedWildcardConstraint(v16) )
    return v16;
  *a2 = 1;
  AST_FreeNode((int)v16);
  return 0;
}
// 4B899D: variable 'v3' is possibly undefined
// 4B89BA: variable 'v7' is possibly undefined
// 4B8A2A: variable 'v10' is possibly undefined
// 4B8AC4: variable 'v14' is possibly undefined

//----- (004B8B10) --------------------------------------------------------
signed int  Rules_CheckMixedWildcardConstraint(_DWORD *a1)
{
  BOOL v1; // esi
  int v2; // ebx
  int v3; // edi
  int *v4; // edx
  _BYTE *v6; // eax
  int v7; // ecx
  int *i; // [esp+0h] [ebp-24h]
  int v9; // [esp+4h] [ebp-20h]
  int v10; // [esp+8h] [ebp-1Ch]

  v1 = 0;
  v2 = 0;
  v3 = 0;
  v10 = 0;
  v9 = 0;
  if ( *a1 == 15 )
    v2 = 1;
  else
    v1 = *a1 == 16;
  for ( i = (int *)a1[17]; i; i = (int *)i[17] )
  {
    v4 = i;
    do
    {
      if ( *v4 == 15 )
      {
        v2 = 1;
        goto LABEL_7;
      }
      if ( *v4 == 16 )
      {
        v1 = 1;
        goto LABEL_7;
      }
      if ( Rules_TagIsConstantType(*v4) )
      {
        v3 = 1;
        goto LABEL_7;
      }
      if ( *v4 == 94 )
      {
        v6 = Rules_ApplyCEKeywordFlags();
        if ( (*v6 & 1) != 0 )
          goto LABEL_22;
        if ( (char)v6[1] < 0 )
        {
          v9 = 1;
LABEL_22:
          AST_DecrementNodeRefCount(v6);
          goto LABEL_7;
        }
        v10 = 1;
        AST_DecrementNodeRefCount(v6);
      }
LABEL_7:
      v4 = (int *)v4[16];
    }
    while ( v4 );
  }
  if ( !v2 && !v3 && !v10 )
    return 0;
  if ( !v1 && !v9 )
    return 0;
  Rules_PrintErrorID((int)aPattern, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSingleAndMulti, v7);
  return 1;
}
// 4B8B48: conditional instruction was optimized away because %var_24.4!=0
// 4B8B56: variable 'v4' is possibly undefined
// 4B8C3D: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004B8C60) --------------------------------------------------------
unsigned int * Rules_ParseSingleFieldConstraintTerm(int a1, _DWORD *a2)
{
  signed int v4; // eax
  unsigned int *v5; // ecx
  signed int v6; // edi
  _DWORD *v7; // edx
  unsigned int *v8; // ebx
  unsigned int v9; // eax
  int v11; // ecx
  __int16 *v12; // eax
  int v13; // ecx
  __int16 *v14; // eax
  int v15; // ecx

  v4 = AST_AllocNode();
  v6 = v4;
  v8 = (unsigned int *)v4;
  if ( *v7 == 90 )
  {
    Parser_NextToken(a1, (int)v5);
    *(_BYTE *)(v6 + 8) |= 1u;
  }
  else
  {
    *(_BYTE *)(v4 + 8) &= ~1u;
  }
  v9 = *v5;
  *v8 = *v5;
  if ( v9 == 2 )
  {
    if ( !strcmp_(v5, asc_50A08C) )
    {
      v12 = (__int16 *)Parser_ParseRequiredFunctionCall(a1, v11);
      if ( v12 )
      {
        *v8 = 94;
        v8[14] = (unsigned int)Rules_CECloneRestrictionExpr(v12);
        AST_Free(v13);
        return v8;
      }
    }
    else
    {
      if ( strcmp_(v11, asc_50A090) )
      {
LABEL_5:
        v8[1] = v5[1];
        return v8;
      }
      v14 = (__int16 *)Parser_ParseRequiredFunctionCall(a1, (int)v5);
      if ( v14 )
      {
        *v8 = 93;
        v8[14] = (unsigned int)Rules_CECloneRestrictionExpr(v14);
        AST_Free(v15);
        return v8;
      }
    }
    *a2 = 1;
    AST_FreeNode((int)v8);
    return 0;
  }
  if ( v9 == 15 || v9 == 16 || v9 < 2 || v9 == 3 || v9 == 8 )
    goto LABEL_5;
  Parser_ReportSyntaxError();
  *a2 = 1;
  AST_FreeNode((int)v8);
  return 0;
}
// 4B8D4F: simplified comparisons for 'eax.4': ==0 || ==1 became <2u
// 4B8C71: variable 'v7' is possibly undefined
// 4B8C83: variable 'v5' is possibly undefined
// 4B8CC7: variable 'v11' is possibly undefined
// 4B8CE2: variable 'v13' is possibly undefined
// 4B8D38: variable 'v15' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004B8D90) --------------------------------------------------------
int * Rules_BuildConjunctionFromPatternList(int a1)
{
  int *v2; // eax
  _DWORD *v3; // ecx
  int *v4; // edi
  int *v5; // eax
  _DWORD *v6; // ecx
  int *v7; // eax
  int *v8; // edi
  _DWORD *i; // edx
  _DWORD *v10; // eax
  int v11; // ecx
  int v12; // edx
  int *v13; // ebx
  int v14; // eax
  int j; // edx
  int v16; // ebp
  int v17; // eax
  int v18; // edx
  int *v19; // eax
  int v20; // edx

  v2 = (int *)AST_AllocNode();
  v4 = v2;
  *v2 = 81;
  if ( a1 )
  {
    v2[16] = a1;
  }
  else
  {
    v17 = Rules_CEAllocTestNode();
    *(_DWORD *)(v18 + 64) = v17;
  }
  v5 = Rules_NormalizeNestedConnectives(v4, v3, 1);
  v7 = Rules_NormalizeNestedConnectives(v5, v6, 2);
  v8 = v7;
  if ( *v7 == 82 )
  {
    for ( i = (_DWORD *)v7[16]; i; i = (_DWORD *)i[17] )
    {
      if ( *i != 81 )
      {
        v10 = (_DWORD *)AST_AllocNode();
        *v10 = 81;
        v10[16] = v12;
        v10[17] = *(_DWORD *)(v12 + 68);
        *(_DWORD *)(v12 + 68) = 0;
        if ( v11 )
          *(_DWORD *)(v11 + 68) = v10;
        else
          v8[16] = (int)v10;
        i = v10;
      }
    }
  }
  else if ( *v7 != 81 )
  {
    v19 = (int *)AST_AllocNode();
    *v19 = 81;
    v8 = v19;
    v19[16] = v20;
  }
  Rules_FinalizeConjunctionChain(v8);
  if ( *v8 == 82 )
    v13 = (int *)v8[16];
  else
    v13 = v8;
  while ( v13 )
  {
    v14 = v13[16];
    for ( j = 1; v14; v14 = *(_DWORD *)(v14 + 68) )
    {
      if ( (*(_BYTE *)(v14 + 8) & 0x20) != 0 )
      {
        *(_WORD *)(v14 + 8) &= 0xE03Fu;
        v16 = ((j++ & 0x7F) << 6) | *(_DWORD *)(v14 + 8);
        *(_DWORD *)(v14 + 8) = v16;
      }
    }
    Rules_CEAssignJoinDepth((_DWORD *)v13[16], 1);
    v13 = (int *)v13[17];
  }
  return v8;
}
// 4B8DBC: variable 'v3' is possibly undefined
// 4B8DC8: variable 'v6' is possibly undefined
// 4B8DF5: variable 'v12' is possibly undefined
// 4B8E09: variable 'v11' is possibly undefined
// 4B8E82: variable 'v18' is possibly undefined
// 4B8EA1: variable 'v20' is possibly undefined

//----- (004B8EC0) --------------------------------------------------------
int * Rules_NormalizeNestedConnectives(int *a1, _DWORD *a2, int a3)
{
  int v4; // ecx
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  int v8; // edx
  _DWORD *v9; // esi
  int v10; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD *v15; // [esp+4h] [ebp-18h]
  int v16; // [esp+8h] [ebp-14h]

  v15 = a2;
  *a2 = 0;
  do
  {
    v4 = *a1;
    v16 = 0;
    if ( v4 == 81 || v4 == 83 || v4 == 82 )
    {
      if ( a3 == 1 )
        v5 = Rules_CENormalizeAndOr(a1, &v14);
      else
        v5 = (_DWORD *)Rules_CECollapseNotWrapper((int)a1, &v14);
      if ( v14 )
      {
        v16 = 1;
        *v15 = 1;
      }
      a1 = (int *)Rules_CEMergeRedundantNodes((int)v5, &v14);
      if ( v14 )
      {
        v16 = 1;
        *v15 = 1;
      }
    }
    v6 = (_DWORD *)a1[16];
    v7 = 0;
    if ( v6 )
    {
      do
      {
        v8 = *v6;
        v9 = (_DWORD *)v6[17];
        if ( *v6 == 81 || v8 == 83 || v8 == 82 )
        {
          v6[17] = 0;
          if ( v7 )
          {
            v12 = Rules_NormalizeNestedConnectives((int)v6, (int)&v14, a3);
            *(_DWORD *)(v13 + 68) = v12;
            *(_DWORD *)(v12 + 68) = v9;
            v7 = *(_DWORD **)(v13 + 68);
          }
          else
          {
            v10 = Rules_NormalizeNestedConnectives((int)v6, (int)&v14, a3);
            a1[16] = v10;
            *(_DWORD *)(v10 + 68) = v9;
            v7 = (_DWORD *)a1[16];
          }
          if ( v14 )
          {
            *v15 = 1;
            v16 = 1;
          }
        }
        else
        {
          v7 = v6;
        }
        v6 = v9;
      }
      while ( v9 );
    }
  }
  while ( v16 );
  return a1;
}
// 4B8FDC: variable 'v13' is possibly undefined

//----- (004B8FF0) --------------------------------------------------------
_DWORD * Rules_FinalizeConjunctionChain(_DWORD *result)
{
  _DWORD *v1; // ecx
  int i; // edx
  int v3; // edx
  _DWORD *j; // edx
  int v5; // edx
  int v6; // esi
  _BYTE *v7; // edx
  bool v8; // al

  v1 = result;
  if ( *result == 82 )
  {
    for ( i = result[16]; i; i = *(_DWORD *)(v3 + 68) )
      result = (_DWORD *)Rules_FinalizeConjunctionChain(i);
  }
  else
  {
    for ( j = (_DWORD *)result[16]; j; j = (_DWORD *)j[17] )
    {
      if ( *j == 80 )
        break;
    }
    v5 = result[16];
    if ( (*(_BYTE *)(v5 + 8) & 1) != 0 || *(_DWORD *)v5 == 84 || *(int *)(v5 + 44) > 1 )
    {
      v6 = Rules_CEAllocTestNode();
      v7 = (_BYTE *)(v6 + 8);
      v8 = (v1[2] & 2) != 0 || (*(_BYTE *)(v1[16] + 8) & 2) != 0;
      *v7 &= ~2u;
      *(_DWORD *)v7 |= 2 * v8;
      *(_DWORD *)(v6 + 68) = v1[16];
      v1[16] = v6;
    }
    return (_DWORD *)Rules_CEInsertBoundVariableJoinTests(v1[16]);
  }
  return result;
}
// 4B9007: variable 'v3' is possibly undefined
// 4B903C: variable 'v1' is possibly undefined

//----- (004B90A0) --------------------------------------------------------
_DWORD * Rules_CENormalizeAndOr(_DWORD *a1, _DWORD *a2)
{
  _DWORD *v2; // ecx
  int v3; // ebx
  int i; // eax
  int v5; // esi
  int v7; // edi
  int v8; // edx
  int v9; // esi
  signed int v10; // edi
  char v11; // bl
  int v13; // [esp+4h] [ebp-18h]

  v2 = a1;
  *a2 = 0;
  do
  {
LABEL_2:
    v3 = 1;
    i = v2[16];
    v5 = 0;
    v13 = 0;
    if ( i )
    {
      while ( 1 )
      {
        if ( *v2 == 81 && *(_DWORD *)i == 82 )
        {
          v2 = Rules_CEMultiplyAndOverOr(v2, *(_DWORD *)(i + 64), v3);
          *a2 = 1;
          goto LABEL_2;
        }
        if ( *v2 == 83 && *(_DWORD *)i == 82 )
          break;
        if ( *v2 == 82 && *(_DWORD *)i == 82 || *v2 == 81 && *(_DWORD *)i == 81 )
        {
          if ( (*(_BYTE *)(i + 8) & 2) != 0 )
            *((_BYTE *)v2 + 8) |= 2u;
          v13 = 1;
          *a2 = 1;
          *(_DWORD *)(i + 64) = 0;
          v7 = *(_DWORD *)(i + 68);
          *(_DWORD *)(i + 68) = 0;
          AST_FreeNode(i);
          if ( v5 )
            *(_DWORD *)(v5 + 68) = v8;
          else
            v2[16] = v8;
          for ( i = v8; *(_DWORD *)(v8 + 68); v8 = *(_DWORD *)(v8 + 68) )
            ;
          *(_DWORD *)(v8 + 68) = v7;
          if ( !i )
            goto LABEL_6;
        }
        else
        {
          v5 = i;
          ++v3;
          i = *(_DWORD *)(i + 68);
          if ( !i )
            goto LABEL_6;
        }
      }
      v13 = 1;
      *a2 = 1;
      *(_DWORD *)(i + 68) = 0;
      v9 = *(_DWORD *)(i + 64);
      *(_DWORD *)(i + 64) = 0;
      AST_FreeNode(i);
      *v2 = 81;
      for ( v2[16] = v9; v9; v9 = *(_DWORD *)(v9 + 68) )
      {
        v10 = AST_AllocNode();
        Rules_CECopyNodeFields(v10, (_DWORD *)v9, 0);
        *(_DWORD *)(v10 + 64) = *(_DWORD *)(v9 + 64);
        *(_DWORD *)(v10 + 68) = 0;
        *(_DWORD *)v9 = 83;
        *(_DWORD *)(v9 + 4) = 0;
        *(_DWORD *)(v9 + 56) = 0;
        v11 = *(_BYTE *)(v9 + 8);
        *(_DWORD *)(v9 + 64) = v10;
        *(_BYTE *)(v9 + 8) = v11 & 0xFC;
      }
    }
LABEL_6:
    ;
  }
  while ( v13 );
  return v2;
}
// 4B90B8: variable 'v2' is possibly undefined
// 4B9157: variable 'v8' is possibly undefined

//----- (004B9220) --------------------------------------------------------
int  Rules_CECollapseNotWrapper(int a1, _DWORD *a2)
{
  _DWORD *v4; // ecx
  _DWORD *v5; // ecx
  char v7; // dl
  int v8; // eax
  char v9; // dh
  int v10; // eax
  int v11; // edx

  *a2 = 0;
LABEL_2:
  while ( 1 )
  {
    v4 = *(_DWORD **)(a1 + 64);
    if ( !v4 )
      return a1;
    while ( 1 )
    {
      if ( *(_DWORD *)a1 == 83 && *v4 == 80 )
      {
        *a2 = 1;
        Rules_CECopyNodeFields(a1, v4, 0);
        *(_BYTE *)(a1 + 8) |= 1u;
        *(_DWORD *)(a1 + 64) = v5[16];
        v5[13] = 0;
        v5[14] = 0;
        v5[15] = 0;
        v5[16] = 0;
        v5[17] = 0;
        AST_FreeNode((int)v5);
        goto LABEL_2;
      }
      if ( *(_DWORD *)a1 == 83 && (*v4 == 81 || *v4 == 83) )
        break;
      v4 = (_DWORD *)v4[17];
      if ( !v4 )
        return a1;
    }
    *a2 = 1;
    v7 = *(_BYTE *)(a1 + 8);
    *(_DWORD *)a1 = *v4;
    v8 = v4[2];
    *(_BYTE *)(a1 + 8) = v7 & 0xFE;
    *(_DWORD *)(a1 + 8) |= v8 & 1;
    v9 = *(_BYTE *)(a1 + 8);
    *(_DWORD *)(a1 + 4) = v4[1];
    v10 = v4[2];
    *(_BYTE *)(a1 + 8) = v9 & 0xFD;
    *(_DWORD *)(a1 + 8) |= v10 & 2;
    *(_DWORD *)(a1 + 64) = v4[16];
    v4[16] = 0;
    v4[17] = 0;
    AST_FreeNode((int)v4);
    Rules_CECountPatternNodes(*(int **)(a1 + 64), v11);
  }
}
// 4B925B: variable 'v5' is possibly undefined
// 4B9318: variable 'v11' is possibly undefined

//----- (004B9330) --------------------------------------------------------
_DWORD * Rules_CEMultiplyAndOverOr(_DWORD *a1, int a2, int a3)
{
  int v3; // ebp
  int v4; // edi
  int v5; // eax
  int j; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  _DWORD *result; // eax
  int v11; // ecx
  int i; // [esp+8h] [ebp-14h]

  v3 = a2;
  for ( i = 0; v3; v3 = *(_DWORD *)(v3 + 68) )
  {
    v4 = Rules_CECloneNode(a1);
    v5 = 1;
    for ( j = *(_DWORD *)(v4 + 64); v5 != a3; j = *(_DWORD *)(j + 68) )
      ++v5;
    AST_FreeNode(*(_DWORD *)(j + 64));
    Rules_CECopyNodeFields(v7, (_DWORD *)v3, 1);
    v8 = Rules_CECloneNode(*(_DWORD **)(v3 + 64));
    *(_DWORD *)(v9 + 64) = v8;
    if ( i )
      *(_DWORD *)(i + 68) = v4;
    i = v4;
    *(_DWORD *)(v4 + 68) = 0;
  }
  AST_FreeNode((int)a1);
  result = (_DWORD *)AST_AllocNode();
  *result = 82;
  result[16] = v11;
  return result;
}
// 4B937D: variable 'v7' is possibly undefined
// 4B938E: variable 'v9' is possibly undefined
// 4B93BE: variable 'v11' is possibly undefined

//----- (004B93E0) --------------------------------------------------------
int  Rules_CEMergeRedundantNodes(int a1, _DWORD *a2)
{
  int i; // ecx
  int v5; // edi
  int v6; // ebx
  int v7; // edx
  _DWORD *v9; // edx
  int v10; // edx
  _DWORD *v11; // edx
  signed int v12; // edi
  int v13; // ecx
  _DWORD *v14; // edx
  int v15; // ecx
  _DWORD *v16; // ebx
  int v17; // ecx
  _DWORD *v18; // eax
  int v19; // ecx
  __int16 *v20; // edx
  __int16 *v21; // eax
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // eax
  int v26; // ecx
  int v27; // [esp+0h] [ebp-18h]

  *a2 = 0;
LABEL_2:
  while ( 2 )
  {
    i = *(_DWORD *)(a1 + 64);
    v5 = 0;
    v27 = 0;
    while ( i )
    {
      if ( *(_DWORD *)a1 == 82 && *(_DWORD *)i == 82 || *(_DWORD *)a1 == 81 && *(_DWORD *)i == 81 )
      {
        if ( (*(_BYTE *)(i + 8) & 2) != 0 )
          *(_BYTE *)(a1 + 8) |= 2u;
        *a2 = 1;
        v27 = 1;
        *(_DWORD *)(i + 64) = 0;
        v6 = *(_DWORD *)(i + 68);
        *(_DWORD *)(i + 68) = 0;
        AST_FreeNode(i);
        if ( v5 )
          *(_DWORD *)(v5 + 68) = v7;
        else
          *(_DWORD *)(a1 + 64) = v7;
        for ( i = v7; *(_DWORD *)(v7 + 68); v7 = *(_DWORD *)(v7 + 68) )
          ;
        *(_DWORD *)(v7 + 68) = v6;
      }
      else
      {
        if ( *(_DWORD *)a1 == 83 && *(_DWORD *)i == 84 )
        {
          *a2 = 1;
          v12 = AST_NewNode(10, g_ClipsNotSymbol);
          *(_DWORD *)(v12 + 6) = Rules_CECloneBindingList(*(_DWORD *)(v13 + 56));
          Rules_CECopyNodeFields(a1, v14, 1);
          AST_FreeNode(v15);
          AST_FreeNode(*(_DWORD *)(a1 + 56));
          *(_DWORD *)(a1 + 56) = Rules_CECloneRestrictionExpr((__int16 *)v12);
          *(_DWORD *)(a1 + 64) = 0;
          AST_Free(v12);
          goto LABEL_2;
        }
        if ( *(_DWORD *)a1 == 81
          && *(_DWORD *)i == 84
          && (v9 = *(_DWORD **)(i + 68)) != 0
          && *v9 == 84
          && (v10 = *(_DWORD *)(i + 44), v10 == *(_DWORD *)(i + 48))
          && v10 == *(_DWORD *)(*(_DWORD *)(i + 68) + 44) )
        {
          *a2 = 1;
          v27 = 1;
          v16 = (_DWORD *)Rules_CECloneBindingList(*(_DWORD *)(i + 56));
          v18 = (_DWORD *)Rules_CECloneBindingList(*(_DWORD *)(*(_DWORD *)(v17 + 68) + 56));
          AST_MergeFieldAccessNodes(v16, v18);
          AST_FreeNode(*(_DWORD *)(v19 + 56));
          v21 = Rules_CECloneRestrictionExpr(v20);
          *(_DWORD *)(v22 + 56) = v21;
          AST_Free(v23);
          v25 = *(_DWORD *)(v24 + 68);
          *(_DWORD *)(v24 + 68) = *(_DWORD *)(v25 + 68);
          *(_DWORD *)(v25 + 68) = 0;
          AST_FreeNode(v25);
        }
        else
        {
          if ( *(_DWORD *)a1 == 81 && *(_DWORD *)i == 84 )
          {
            v11 = *(_DWORD **)(a1 + 64);
            if ( (_DWORD *)i == v11 && !v11[17] )
            {
              *a2 = 1;
              Rules_CECopyNodeFields(a1, v11, 1);
              *(_DWORD *)(a1 + 64) = 0;
              AST_FreeNode(v26);
              goto LABEL_2;
            }
          }
          v5 = i;
          i = *(_DWORD *)(i + 68);
        }
      }
    }
    if ( v27 )
      continue;
    return a1;
  }
}
// 4B940B: variable 'i' is possibly undefined
// 4B9447: variable 'v7' is possibly undefined
// 4B950C: variable 'v13' is possibly undefined
// 4B951B: variable 'v14' is possibly undefined
// 4B9522: variable 'v15' is possibly undefined
// 4B9561: variable 'v17' is possibly undefined
// 4B9577: variable 'v19' is possibly undefined
// 4B9581: variable 'v20' is possibly undefined
// 4B9586: variable 'v22' is possibly undefined
// 4B958B: variable 'v23' is possibly undefined
// 4B9590: variable 'v24' is possibly undefined
// 4B95C6: variable 'v26' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004B95D0) --------------------------------------------------------
int  Rules_CECloneNode(_DWORD *a1)
{
  _DWORD *v1; // ecx
  _DWORD *v2; // edx
  signed int v3; // esi
  int v4; // ecx
  int v5; // ecx

  v1 = a1;
  if ( !a1 )
    return 0;
  v2 = *(_DWORD **)(g_ClipsMemoryTable + 288);
  if ( v2 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 288);
    *(_DWORD *)(g_ClipsMemoryTable + 288) = *v2;
    v3 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v3 = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }
  Rules_CECopyNodeFields(v3, v1, 1);
  *(_DWORD *)(v3 + 64) = Rules_CECloneNode(*(_DWORD *)(v4 + 64));
  *(_DWORD *)(v3 + 68) = Rules_CECloneNode(*(_DWORD *)(v5 + 68));
  return v3;
}
// 4B9607: variable 'v1' is possibly undefined
// 4B960C: variable 'v4' is possibly undefined
// 4B9617: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B9640) --------------------------------------------------------
int  Rules_CECopyNodeFields(int a1, _DWORD *a2, int a3)
{
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int result; // eax
  signed int v16; // eax
  _DWORD *v17; // edx
  int v18; // ecx
  int v19; // ebp
  int v20; // eax
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // eax
  int v25; // ecx

  *(_DWORD *)a1 = *a2;
  *(_DWORD *)(a1 + 4) = a2[1];
  v4 = a2[2];
  *(_BYTE *)(a1 + 8) &= ~1u;
  *(_DWORD *)(a1 + 8) |= v4 & 1;
  v5 = a2[2];
  *(_BYTE *)(a1 + 8) &= ~8u;
  *(_DWORD *)(a1 + 8) |= v5 & 8;
  v6 = a2[2];
  *(_BYTE *)(a1 + 9) &= ~0x40u;
  *(_DWORD *)(a1 + 8) |= v6 & 0x4000;
  v7 = a2[2];
  *(_BYTE *)(a1 + 8) &= ~4u;
  v8 = v7 & 4 | *(_DWORD *)(a1 + 8);
  *(_DWORD *)(a1 + 8) = v8;
  v9 = a2[2] & 0x3F8000;
  *(_DWORD *)(a1 + 8) = v8 & 0xFFC07FFF;
  *(_DWORD *)(a1 + 8) = v9 | v8 & 0xFFC07FFF;
  v10 = a2[2];
  *(_WORD *)(a1 + 10) &= 0xE03Fu;
  *(_DWORD *)(a1 + 8) |= v10 & 0x1FC00000;
  v11 = a2[3];
  *(_BYTE *)(a1 + 12) &= 0x80u;
  *(_DWORD *)(a1 + 12) |= v11 & 0x7F;
  v12 = a2[3];
  *(_WORD *)(a1 + 12) &= 0xC07Fu;
  *(_DWORD *)(a1 + 12) |= v12 & 0x3F80;
  v13 = a2[2];
  *(_BYTE *)(a1 + 8) &= ~2u;
  *(_DWORD *)(a1 + 8) |= v13 & 2;
  v14 = a2[2];
  *(_BYTE *)(a1 + 8) &= ~0x20u;
  *(_DWORD *)(a1 + 8) |= v14 & 0x20;
  *(_DWORD *)(a1 + 20) = a2[5];
  *(_DWORD *)(a1 + 24) = a2[6];
  *(_DWORD *)(a1 + 28) = a2[7];
  *(_DWORD *)(a1 + 32) = a2[8];
  *(_DWORD *)(a1 + 36) = a2[9];
  *(_DWORD *)(a1 + 40) = a2[10];
  *(_DWORD *)(a1 + 44) = a2[11];
  *(_DWORD *)(a1 + 48) = a2[12];
  if ( a3 )
  {
    v16 = AST_CloneNodeList(a2[13]);
    *(_DWORD *)(v18 + 52) = v16;
    v19 = v17[15];
    if ( v19 && *(_DWORD *)(v17[6] + 68) )
    {
      v24 = (*(int (**)(void))(v17[6] + 68))();
      *(_DWORD *)(v25 + 60) = v24;
    }
    else
    {
      *(_DWORD *)(v18 + 60) = v19;
    }
    v20 = Rules_CECloneNode(v17[14]);
    *(_DWORD *)(v21 + 56) = v20;
    result = Rules_CloneLHSParseNode(*(int **)(v22 + 16));
    *(_DWORD *)(v23 + 16) = result;
    if ( result )
      *(_BYTE *)(v23 + 8) |= 0x10u;
    else
      *(_BYTE *)(v23 + 8) &= ~0x10u;
  }
  else
  {
    *(_DWORD *)(a1 + 52) = a2[13];
    *(_DWORD *)(a1 + 60) = a2[15];
    *(_DWORD *)(a1 + 56) = a2[14];
    *(_BYTE *)(a1 + 8) &= ~0x10u;
    result = a2[4];
    *(_DWORD *)(a1 + 16) = result;
  }
  return result;
}
// 4B975B: variable 'v18' is possibly undefined
// 4B975E: variable 'v17' is possibly undefined
// 4B9770: variable 'v21' is possibly undefined
// 4B9773: variable 'v22' is possibly undefined
// 4B977B: variable 'v23' is possibly undefined
// 4B979B: variable 'v25' is possibly undefined

//----- (004B97B0) --------------------------------------------------------
signed int Rules_CEAllocDefaultNode()
{
  _DWORD *v0; // edx
  signed int result; // eax
  int v2; // ecx
  __int16 v3; // dx

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 288);
  if ( v0 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 288);
    *(_DWORD *)(g_ClipsMemoryTable + 288) = *v0;
    result = g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }
  *(_DWORD *)result = 103;
  *(_DWORD *)(result + 4) = 0;
  *(_DWORD *)(result + 16) = 0;
  *(_DWORD *)(result + 20) = 0;
  *(_DWORD *)(result + 24) = 0;
  *(_DWORD *)(result + 28) = -1;
  *(_DWORD *)(result + 32) = -1;
  *(_DWORD *)(result + 36) = 0;
  *(_DWORD *)(result + 40) = -1;
  *(_DWORD *)(result + 44) = 1;
  *(_DWORD *)(result + 48) = 1;
  *(_DWORD *)(result + 60) = 0;
  *(_DWORD *)(result + 52) = 0;
  *(_DWORD *)(result + 56) = 0;
  v2 = *(_DWORD *)(result + 8);
  v3 = *(_WORD *)(result + 12);
  *(_DWORD *)(result + 64) = 0;
  *(_DWORD *)(result + 8) = v2 & 0xE0003FC0;
  *(_WORD *)(result + 12) = v3 & 0xC000;
  LOBYTE(v3) = *(_BYTE *)(result + 8);
  *(_DWORD *)(result + 68) = 0;
  *(_BYTE *)(result + 8) = v3 | 0x20;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B9880) --------------------------------------------------------
int  Rules_CEFreeNode(int result)
{
  int v1; // edx
  int v2; // edx
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int v6; // eax

  if ( result )
  {
    AST_Free(*(_DWORD *)(result + 52));
    AST_FreeNode(*(_DWORD *)(v1 + 64));
    AST_FreeNode(*(_DWORD *)(v2 + 68));
    AST_FreeNode(*(_DWORD *)(v3 + 56));
    if ( (*(_BYTE *)(v4 + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(v4 + 16));
    if ( *(_DWORD *)(v4 + 60) )
    {
      v6 = *(_DWORD *)(v4 + 24);
      if ( *(_DWORD *)(v6 + 64) )
        (*(void (__cdecl **)(int))(v6 + 64))(v5);
    }
    g_ClipsMemFreeListTemp = v4;
    *(_DWORD *)v4 = *(_DWORD *)(g_ClipsMemoryTable + 288);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 288) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4B9891: variable 'v1' is possibly undefined
// 4B9899: variable 'v2' is possibly undefined
// 4B98A1: variable 'v3' is possibly undefined
// 4B98A9: variable 'v4' is possibly undefined
// 4B98CC: variable 'v5' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B9900) --------------------------------------------------------
__int16 * Rules_CECloneRestrictionExpr(__int16 *result)
{
  __int16 *v1; // ebx
  _DWORD *v2; // edi
  signed int v3; // eax
  int v4; // ecx
  signed int v5; // eax
  int *v6; // ecx
  int v7; // edx
  int v8; // ebx
  int v9; // esi
  signed int i; // ecx
  _BYTE *v11; // eax

  v1 = result;
  if ( result )
  {
    v2 = (_DWORD *)AST_AllocNode();
    *v2 = *v1;
    v2[1] = *(_DWORD *)(v1 + 1);
    v3 = Rules_CECloneRestrictionExpr(*(_DWORD *)(v1 + 5));
    *(_DWORD *)(v4 + 64) = v3;
    v5 = Rules_CECloneRestrictionExpr(*(_DWORD *)(v1 + 3));
    v7 = *v6;
    v6[17] = v5;
    if ( v7 == 10 )
    {
      v8 = 1;
      v9 = v6[1];
      for ( i = v5; i; ++v8 )
      {
        if ( *(_DWORD *)i == 15 )
        {
          Rules_GetArgRestrictionType(v9, v8);
          v11 = Rules_ApplyPatternKeywordFlags();
          *(_DWORD *)(i + 16) = v11;
          *(_BYTE *)(i + 8) |= 0x10u;
        }
        i = *(_DWORD *)(i + 64);
      }
      return (__int16 *)v2;
    }
    else
    {
      return (__int16 *)v6;
    }
  }
  return result;
}
// 4B992B: variable 'v4' is possibly undefined
// 4B9936: variable 'v6' is possibly undefined
// 4B9962: variable 'i' is possibly undefined

//----- (004B9980) --------------------------------------------------------
int  Rules_CECloneBindingList(int a1)
{
  int v1; // ecx
  _DWORD *v2; // ebx
  signed int v3; // edx
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // edx

  v1 = a1;
  if ( !a1 )
    return 0;
  v2 = *(_DWORD **)(g_ClipsMemoryTable + 56);
  if ( v2 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = *v2;
    v3 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v3 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_WORD *)v3 = *(_WORD *)v1;
  *(_DWORD *)(v3 + 2) = *(_DWORD *)(v1 + 4);
  v4 = Rules_CECloneBindingList(*(_DWORD *)(v1 + 64));
  *(_DWORD *)(v5 + 10) = v4;
  v7 = Rules_CECloneBindingList(*(_DWORD *)(v6 + 68));
  *(_DWORD *)(v8 + 6) = v7;
  return v8;
}
// 4B99A7: variable 'v1' is possibly undefined
// 4B99BB: variable 'v5' is possibly undefined
// 4B99BE: variable 'v6' is possibly undefined
// 4B99C6: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B99F0) --------------------------------------------------------
int * Rules_CECountPatternNodes(int *result, int a2)
{
  int *v2; // ecx
  int v4; // edx
  BOOL v5; // edx
  int v6; // ecx
  int v7; // ecx

  v2 = result;
  if ( result )
  {
    while ( 1 )
    {
      v4 = *v2;
      if ( *v2 == 80 || v4 == 84 )
        break;
      if ( v4 == 81 || v4 == 83 )
      {
        if ( a2 )
          v5 = v2[17] == 0;
        else
          v5 = 0;
        result = (int *)Rules_CECountPatternNodes(v2[16], v5);
        v2 = *(int **)(v6 + 68);
        if ( !v2 )
          return result;
      }
      else if ( v4 == 82 )
      {
        result = (int *)Rules_ReportSystemError((int)v2, 1);
        v2 = *(int **)(v7 + 68);
        if ( !v2 )
          return result;
      }
      else
      {
LABEL_6:
        v2 = (int *)v2[17];
        if ( !v2 )
          return result;
      }
    }
    ++v2[11];
    if ( !a2 || v2[17] )
      ++v2[12];
    goto LABEL_6;
  }
  return result;
}
// 4B9A3E: variable 'v6' is possibly undefined
// 4B9A61: variable 'v7' is possibly undefined

//----- (004B9A70) --------------------------------------------------------
int Rules_CEAllocTestNode()
{
  signed int v0; // eax
  int v1; // edx
  char v2; // bl
  int v3; // ecx
  __int64 v5; // rax
  _DWORD *v6; // ecx
  int v7; // ecx

  v0 = AST_AllocNode();
  *(_DWORD *)v0 = 80;
  v2 = *(_BYTE *)(v0 + 8);
  *(_DWORD *)(v0 + 68) = 0;
  v3 = v0;
  *(_BYTE *)(v0 + 8) = v2 & 0xDF;
  if ( !v1 )
    v1 = Rules_FindPatternParserByName((int)aFacts_6);
  if ( !v1 )
  {
    v1 = g_PatternParserListHead;
    if ( !g_PatternParserListHead )
    {
LABEL_7:
      Rules_ReportSystemError(v3, 2);
      return 0;
    }
    while ( !*(_DWORD *)(v1 + 80) )
    {
      v1 = *(_DWORD *)(v1 + 92);
      if ( !v1 )
        goto LABEL_7;
    }
  }
  v5 = ((__int64 (__fastcall *)(int))*(_DWORD *)(v1 + 80))(v3);
  v6[16] = v5;
  AST_PropagateDepthTag(v6, SHIDWORD(v5));
  return v7;
}
// 4B9A94: variable 'v1' is possibly undefined
// 4B9ABB: variable 'v3' is possibly undefined
// 4B9AD7: variable 'v6' is possibly undefined
// 4B9AE1: variable 'v7' is possibly undefined
// 51B348: using guessed type int dword_51B348;

//----- (004B9AF0) --------------------------------------------------------
int  Rules_CEInsertBoundVariableJoinTests(int result)
{
  int i; // ecx
  int j; // esi
  int v3; // ecx
  int v4; // ebx
  int v5; // eax
  int v6; // eax

  for ( i = result; result; result = *(_DWORD *)(result + 68) )
    *(_BYTE *)(result + 9) &= ~0x20u;
  for ( j = 0; i; i = *(_DWORD *)(i + 68) )
  {
    if ( (*(_BYTE *)(i + 8) & 1) != 0 && (*(_DWORD *)(i + 8) & 0x2000) != 0 )
    {
      result = 0;
    }
    else if ( (*(_DWORD *)i == 84 || (*(_BYTE *)(i + 8) & 1) != 0) && (*(_DWORD *)(i + 8) & 0x2000) == 0 )
    {
      v4 = Rules_CEAllocTestNode();
      v5 = *(_DWORD *)(v3 + 8);
      *(_BYTE *)(v4 + 8) &= ~2u;
      *(_DWORD *)(v4 + 8) |= v5 & 2;
      v6 = *(_DWORD *)(v3 + 44);
      *(_DWORD *)(v4 + 44) = v6;
      *(_DWORD *)(v4 + 48) = v6;
      if ( !j )
        Rules_ReportSystemError(v3, 3);
      *(_DWORD *)(j + 68) = v4;
      *(_DWORD *)(v4 + 68) = v3;
      i = v4;
      result = *(_DWORD *)(v4 + 68);
    }
    else
    {
      result = *(_DWORD *)(i + 68);
    }
    while ( result )
    {
      if ( *(_DWORD *)(result + 44) != *(_DWORD *)(i + 44) )
        goto LABEL_9;
      if ( (*(_BYTE *)(result + 8) & 1) != 0 )
      {
        *(_DWORD *)(result + 8) |= 0x2000u;
        result = *(_DWORD *)(result + 68);
      }
      else
      {
        if ( *(_DWORD *)result == 80 )
          break;
        if ( *(_DWORD *)result == 84 )
        {
          *(_DWORD *)(result + 8) |= 0x2000u;
          *(_DWORD *)(result + 24) = *(_DWORD *)(i + 24);
          result = *(_DWORD *)(result + 68);
        }
        else
        {
LABEL_9:
          result = *(_DWORD *)(result + 68);
        }
      }
    }
    j = i;
  }
  return result;
}
// 4B9B65: variable 'v3' is possibly undefined

//----- (004B9C10) --------------------------------------------------------
void  Rules_CEPrintExpression(int a1, int a2)
{
  int v2; // ecx
  int v3; // ebx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  char *v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  char *v13; // edx
  int v14; // ecx

  v2 = a1;
  v3 = a2;
  if ( a2 )
  {
    while ( v3 )
    {
      switch ( *(_DWORD *)v3 )
      {
        case 'P':
          Output_Write(v2, (int)asc_50A0A4, v2);
          if ( (*(_BYTE *)(v3 + 8) & 1) != 0 )
            Output_Write(v4, (int)aN, v4);
          if ( (*(_DWORD *)(v3 + 8) & 2) != 0 )
            Output_Write(v4, (int)asc_50A0AC, v4);
          Rules_PrintLongInteger(v4, *(_DWORD *)(v3 + 44));
          Output_Write(v5, (int)asc_50A0B0, v5);
          Rules_PrintLongInteger(v6, *(_DWORD *)(v3 + 48));
          Output_Write(v7, (int)asc_50A0B4, v7);
          Output_Write(v8, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 64) + 68) + 4) + 16), v8);
          goto LABEL_9;
        case 'Q':
          if ( (*(_DWORD *)(v3 + 8) & 2) != 0 )
            v13 = aLand;
          else
            v13 = aAnd_3;
          goto LABEL_21;
        case 'R':
          if ( (*(_DWORD *)(v3 + 8) & 2) != 0 )
            v13 = aLor;
          else
            v13 = aOr_3;
          goto LABEL_21;
        case 'S':
          if ( (*(_DWORD *)(v3 + 8) & 2) != 0 )
            v13 = aLnot;
          else
            v13 = aNot_3;
LABEL_21:
          Output_Write(v2, (int)v13, v2);
          Rules_CEPrintExpression(v14, *(_DWORD *)(v3 + 64));
          goto LABEL_9;
        case 'T':
          Output_Write(v2, (int)aTest_1, v2);
          Rules_PrintLongInteger(v10, *(_DWORD *)(v3 + 44));
          Output_Write(v11, (int)asc_50A0B0, v11);
          Rules_PrintLongInteger(v12, *(_DWORD *)(v3 + 48));
LABEL_9:
          v9 = asc_50A0B8;
          break;
        default:
          v9 = aPrettyPrintUnknownExpressionToken;
          break;
      }
      Output_Write(v2, (int)v9, v2);
      v3 = *(_DWORD *)(v3 + 68);
      if ( v3 )
        Output_Write(v2, (int)asc_50A0B4, v2);
    }
  }
  // 4B9C1B: jumps to the shared epilogue loc_4B9BCE (pop ebp/edi/esi/ecx/ebx; retn)
  // shared with sub_4B9AF0; in C this is the function return.
  return;
}
// 4B9C1B: control flows out of bounds to 4B9BCE
// 4B9C4C: variable 'v2' is possibly undefined
// 4B9C5E: variable 'v4' is possibly undefined
// 4B9C82: variable 'v5' is possibly undefined
// 4B9C8C: variable 'v6' is possibly undefined
// 4B9C98: variable 'v7' is possibly undefined
// 4B9CAB: variable 'v8' is possibly undefined
// 4B9CE6: variable 'v10' is possibly undefined
// 4B9CEF: variable 'v11' is possibly undefined
// 4B9CF9: variable 'v12' is possibly undefined
// 4B9D61: variable 'v14' is possibly undefined

//----- (004B9D80) --------------------------------------------------------
_DWORD * Rules_CEAssignJoinDepth(_DWORD *a1, int a2)
{
  _DWORD *v2; // ebp
  _DWORD *result; // eax
  int v5; // ecx
  _DWORD *v6; // esi
  int v7; // ecx
  int v8; // ebx
  int v9; // [esp-4h] [ebp-1Ch]
  int v10; // [esp+0h] [ebp-18h]

  v2 = a1;
  v10 = a1[11];
  while ( 1 )
  {
    if ( v10 < v2[11] )
    {
      result = (_DWORD *)Rules_CEAssignJoinDepth((int)v2, a2);
      v2 = result;
      if ( result[12] < v5 )
        return result;
      ++a2;
      goto LABEL_5;
    }
    if ( *v2 != 84 )
      break;
    if ( v10 > v2[12] )
      return v2;
LABEL_5:
    v2 = (_DWORD *)v2[17];
    if ( !v2 )
      return 0;
  }
  if ( *v2 != 80 )
    goto LABEL_5;
  v6 = (_DWORD *)v2[16];
  for ( v2[7] = a2; v6; v6 = (_DWORD *)v6[16] )
  {
    v7 = v6[9];
    v9 = v6[10];
    v8 = v6[8];
    v6[7] = a2;
    Rules_CEPropagateJoinCoordinates((int)v6, a2, v7, v8, v9);
  }
  if ( v10 <= v2[12] )
  {
    ++a2;
    goto LABEL_5;
  }
  return v2;
}
// 4B9DCC: variable 'v5' is possibly undefined

//----- (004B9E10) --------------------------------------------------------
int  Rules_CEPropagateJoinCoordinates(int result, int a2, int a3, int a4, int a5)
{
  int v7; // ebx
  _DWORD *v8; // eax
  int j; // [esp+0h] [ebp-14h]
  _DWORD *i; // [esp+4h] [ebp-10h]

  if ( result )
  {
    if ( (*(_BYTE *)(result + 8) & 4) != 0 )
    {
      *(_DWORD *)(result + 28) = a2;
      if ( a4 > 0 )
        *(_DWORD *)(result + 32) = a4;
      *(_DWORD *)(result + 36) = a3;
      *(_DWORD *)(result + 40) = a5;
      result = *(_DWORD *)(result + 68);
      for ( i = (_DWORD *)result; result; i = (_DWORD *)result )
      {
        i[7] = a2;
        v7 = i[8];
        i[9] = a3;
        Rules_CEPropagateJoinCoordinates((int)i, a2, a3, v7, a5);
        result = i[16];
      }
    }
    else
    {
      result = *(_DWORD *)(result + 68);
      for ( j = result; result; j = result )
      {
        v8 = (_DWORD *)j;
        if ( j )
        {
          do
          {
            v8[7] = a2;
            if ( a4 > 0 )
              v8[8] = a4;
            v8[9] = a3;
            v8[10] = a5;
            v8 = (_DWORD *)v8[16];
          }
          while ( v8 );
        }
        result = *(_DWORD *)(j + 68);
      }
    }
  }
  return result;
}

//----- (004B9EC0) --------------------------------------------------------
signed int Rules_RegisterDeftemplateBinaryItem()
{
  return Rules_RegisterBinaryItem(
           (int)aDeftemplate_2,
           0,
           0,
           (int)Rules_DeftemplateBsaveFind,
           (int)Rules_DeftemplateBsaveWriteCounts,
           (int)Rules_DeftemplateBsaveWriteData,
           (int)Rules_DeftemplateBloadStorage,
           (int)Rules_DeftemplateBload,
           (int)Rules_DeftemplateClearBloaded);
}

//----- (004B9F00) --------------------------------------------------------
int Rules_DeftemplateBsaveFind()
{
  int result; // eax
  int i; // ebx
  _DWORD *j; // ecx
  int v3; // edx
  int v4; // ecx
  _DWORD *k; // eax

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DeftemplateBsaveCount);
    Rules_ConstructQueuePush(g_Deftemplate_SlotCount);
    Rules_ConstructQueuePush(g_DeftemplateModuleItemCount);
  }
  g_DeftemplateBsaveCount = 0;
  g_Deftemplate_SlotCount = 0;
  g_DeftemplateModuleItemCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    ++g_DeftemplateModuleItemCount;
    for ( j = (_DWORD *)Rules_GetNextDeftemplate(0); j; j = (_DWORD *)Rules_GetNextDeftemplate(v4) )
    {
      v3 = g_DeftemplateBsaveCount++;
      AST_MarkNodeFieldBound(j, v3);
      for ( k = *(_DWORD **)(v4 + 20); k; k = (_DWORD *)k[4] )
      {
        ++g_Deftemplate_SlotCount;
        *(_DWORD *)(*k + 12) |= 2u;
      }
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4B9F8F: variable 'v4' is possibly undefined
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004B9FD0) --------------------------------------------------------
const void * Rules_DeftemplateBsaveWriteCounts(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  _DWORD v6[4]; // [esp+0h] [ebp-10h] BYREF

  v6[2] = a2;
  v6[0] = 12;
  Rules_BsaveWriteBlock(4, a1, v6);
  Rules_BsaveWriteBlock(4, v2, &g_DeftemplateBsaveCount);
  Rules_BsaveWriteBlock(4, v3, &g_Deftemplate_SlotCount);
  return Rules_BsaveWriteBlock(4, v4, &g_DeftemplateModuleItemCount);
}
// 4B9FFA: variable 'v2' is possibly undefined
// 4BA00B: variable 'v3' is possibly undefined
// 4BA01C: variable 'v4' is possibly undefined
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA030) --------------------------------------------------------
int  Rules_DeftemplateBsaveWriteData(int a1)
{
  int i; // ecx
  int v3; // eax
  _DWORD *v4; // eax
  int v5; // ecx
  int j; // ebp
  int k; // ecx
  _DWORD *v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int m; // ebp
  int n; // edi
  int v16; // ecx
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  int result; // eax
  int v25; // ebx
  _DWORD v26[3]; // [esp+0h] [ebp-54h] BYREF
  int v27; // [esp+Ch] [ebp-48h]
  int v28; // [esp+10h] [ebp-44h]
  int v29; // [esp+14h] [ebp-40h]
  int v30; // [esp+18h] [ebp-3Ch] BYREF
  int v31; // [esp+1Ch] [ebp-38h]
  int v32; // [esp+20h] [ebp-34h]
  signed int v33; // [esp+24h] [ebp-30h]
  int v34; // [esp+28h] [ebp-2Ch]
  _DWORD v35[3]; // [esp+2Ch] [ebp-28h] BYREF
  int v36[7]; // [esp+38h] [ebp-1Ch] BYREF

  v36[0] = 12 * g_DeftemplateModuleItemCount + 20 * g_Deftemplate_SlotCount + 24 * g_DeftemplateBsaveCount;
  Rules_BsaveWriteBlock(4, a1, v36);
  g_DeftemplateBsaveCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v5) )
  {
    Module_SetCurrent(i);
    v3 = Module_FindItemByName((int)aDeftemplate_2);
    v4 = (_DWORD *)Module_GetItem(0, *(_DWORD *)(v3 + 4));
    Module_AssignBsaveItemHeaderIndices(v35, v4);
    Rules_BsaveWriteBlock(12, a1, v35);
  }
  g_Deftemplate_SlotCount = 0;
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Rules_GetNextDeftemplate(0); k; k = Rules_GetNextDeftemplate(v13) )
    {
      AST_ExtractPatternBindingInfo(v26, k);
      v9 = v8[6];
      LOBYTE(v28) = v28 & 0xFE;
      v28 |= v9 & 1;
      v10 = v8[6] << 16 >> 19;
      LOWORD(v28) = v28 & 1;
      v28 |= 2 * (v10 & 0x7FFF);
      v11 = v8[8];
      if ( v11 )
        v12 = *(_DWORD *)(v11 + 16);
      else
        v12 = -1;
      v29 = v12;
      if ( v8[5] )
        v27 = g_Deftemplate_SlotCount;
      else
        v27 = -1;
      Rules_BsaveWriteBlock(24, a1, v26);
      g_Deftemplate_SlotCount += *(_DWORD *)(v13 + 24) << 16 >> 19;
    }
  }
  for ( m = Module_NextEnum(0); m; m = Module_NextEnum(m) )
  {
    Module_SetCurrent(m);
    for ( n = Rules_GetNextDeftemplate(0); n; n = Rules_GetNextDeftemplate(n) )
    {
      if ( *(_DWORD *)(n + 20) )
      {
        do
        {
          if ( Rules_DynamicConstraintCheckingEnabled() && (v25 = *(_DWORD *)(v16 + 8)) != 0 )
            v17 = *(unsigned __int16 *)(v25 + 4);
          else
            v17 = -1;
          v32 = v17;
          v30 = *(_DWORD *)(*(_DWORD *)v16 + 12) << 16 >> 18;
          v18 = *(_DWORD *)(v16 + 4);
          LOBYTE(v31) = v31 & 0xFE;
          v31 |= v18 & 1;
          v19 = *(_DWORD *)(v16 + 4);
          LOBYTE(v31) = v31 & 0xFD;
          v31 |= v19 & 2;
          v20 = *(_DWORD *)(v16 + 4);
          LOBYTE(v31) = v31 & 0xFB;
          v31 |= v20 & 4;
          v21 = *(_DWORD *)(v16 + 4);
          LOBYTE(v31) = v31 & 0xF7;
          v31 |= v21 & 8;
          v33 = AST_GetHashedNodeIndex(*(__int16 **)(v16 + 12));
          v34 = (*(_DWORD *)(v22 + 16) != 0) - 1;
          Rules_BsaveWriteBlock(20, a1, &v30);
        }
        while ( *(_DWORD *)(v23 + 16) );
      }
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DeftemplateBsaveCount);
    Rules_ConstructQueuePop(&g_Deftemplate_SlotCount);
    return Rules_ConstructQueuePop(&g_DeftemplateModuleItemCount);
  }
  return result;
}
// 4BA0E6: variable 'v5' is possibly undefined
// 4BA143: variable 'v8' is possibly undefined
// 4BA1AD: variable 'v13' is possibly undefined
// 4BA230: variable 'v16' is possibly undefined
// 4BA29F: variable 'v22' is possibly undefined
// 4BA2C0: variable 'v23' is possibly undefined
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA360) --------------------------------------------------------
int __thiscall Rules_DeftemplateBloadStorage(void *this)
{
  int result; // eax
  _DWORD v2[4]; // [esp+0h] [ebp-10h] BYREF

  v2[2] = this;
  Rules_BloadReadBlock((uintptr_t)v2, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DeftemplateBsaveCount, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_Deftemplate_SlotCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_DeftemplateModuleItemCount, 4u);
  if ( g_DeftemplateModuleItemCount )
  {
    v2[0] = 12 * g_DeftemplateModuleItemCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_DeftemplateModuleItemCount));
    g_ClipsDeftemplateModuleItemArray = result;
    if ( g_DeftemplateBsaveCount )
    {
      v2[0] = 36 * g_DeftemplateBsaveCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(36 * g_DeftemplateBsaveCount));
      g_DeftemplateRecordTable = result;
      if ( g_Deftemplate_SlotCount )
      {
        v2[0] = 20 * g_Deftemplate_SlotCount;
        result = Mem_HeapAllocWithRetry((_DWORD *)(20 * g_Deftemplate_SlotCount));
        g_DeftemplateSlotTable = result;
      }
      else
      {
        g_DeftemplateSlotTable = 0;
      }
    }
    else
    {
      g_DeftemplateRecordTable = 0;
      g_DeftemplateSlotTable = 0;
    }
  }
  else
  {
    g_DeftemplateRecordTable = 0;
    g_DeftemplateSlotTable = 0;
    g_ClipsDeftemplateModuleItemArray = 0;
  }
  return result;
}
// 54E840: using guessed type int dword_54E840;
// 54E844: using guessed type int dword_54E844;
// 54E848: using guessed type int dword_54E848;
// 54E84C: using guessed type int dword_54E84C;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA460) --------------------------------------------------------
signed int Rules_DeftemplateBload()
{
  int v3; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&v3, 4u);
  Rules_BloadAndRefresh(g_DeftemplateModuleItemCount, 12, (void (__fastcall *)(signed int, signed int))Rules_DeftemplateBloadRefreshModuleItem);
  Rules_BloadAndRefresh(g_DeftemplateBsaveCount, 24, (void (__fastcall *)(signed int, signed int))Rules_DeftemplateBloadRefreshRecord);
  return Rules_BloadAndRefresh(g_Deftemplate_SlotCount, 20, (void (__fastcall *)(signed int, signed int))Rules_DeftemplateBloadRefreshSlot);
}
// 54E848: using guessed type int dword_54E848;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA4C0) --------------------------------------------------------
_DWORD * Rules_DeftemplateBloadRefreshModuleItem(_DWORD *a1, int a2)
{
  return Module_UpdateItemHeader(a1, (_DWORD *)(12 * a2 + g_ClipsDeftemplateModuleItemArray), g_DeftemplateRecordTable, 36);
}
// 54E840: using guessed type int dword_54E840;
// 54E84C: using guessed type int dword_54E84C;

//----- (004BA500) --------------------------------------------------------
int  Rules_DeftemplateBloadRefreshRecord(_DWORD *a1, int a2)
{
  int v4; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int result; // eax

  v4 = g_DeftemplateRecordTable + 36 * a2;
  Rules_BuildIndexedSlotDescriptor((int)a1, (_DWORD *)v4, g_ClipsDeftemplateModuleItemArray, 12, 36, g_DeftemplateRecordTable);
  v5 = a1[3];
  if ( v5 == -1 )
    *(_DWORD *)(v4 + 20) = 0;
  else
    *(_DWORD *)(v4 + 20) = 20 * v5 + g_DeftemplateSlotTable;
  v6 = a1[5];
  if ( v6 == -1 )
    *(_DWORD *)(v4 + 32) = 0;
  else
    *(_DWORD *)(v4 + 32) = g_ClipsFactPatternNodeBloadArray + 44 * v6;
  v7 = a1[4];
  *(_BYTE *)(v4 + 24) &= ~1u;
  *(_DWORD *)(v4 + 24) |= v7 & 1;
  v8 = g_Rules_WatchFactsFlag & 1;
  *(_BYTE *)(v4 + 24) &= ~2u;
  *(_DWORD *)(v4 + 24) |= 2 * v8;
  *(_BYTE *)(v4 + 24) &= ~4u;
  v9 = (a1[4] << 16 >> 17) & 0x1FFF;
  *(_WORD *)(v4 + 24) &= 7u;
  result = 8 * v9;
  *(_DWORD *)(v4 + 24) |= result;
  return result;
}
// 4BA555: conditional instruction was optimized away because ecx.4!=FFFFFFFF
// 51A150: using guessed type int dword_51A150;
// 54E51C: using guessed type int dword_54E51C;
// 54E840: using guessed type int dword_54E840;
// 54E844: using guessed type int dword_54E844;
// 54E84C: using guessed type int dword_54E84C;

//----- (004BA5F0) --------------------------------------------------------
int  Rules_DeftemplateBloadRefreshSlot(_DWORD *a1, int a2)
{
  int result; // eax
  int v6; // edx
  int v7; // ebp
  int v8; // edx
  int v9; // edx
  int v10; // edx
  char v11; // bl
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int v15; // edx

  result = g_DeftemplateSlotTable + 20 * a2;
  v6 = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * *a1);
  *(_DWORD *)result = v6;
  ++*(_DWORD *)(v6 + 4);
  v7 = a1[3];
  if ( v7 == -1 )
    v8 = 0;
  else
    v8 = 14 * v7 + g_ClipsPackedExpressionArray;
  *(_DWORD *)(result + 12) = v8;
  v9 = a1[2];
  if ( v9 == -1 )
    v10 = 0;
  else
    v10 = g_ClipsConstraintRecordArrayBase + 42 * v9;
  v11 = *(_BYTE *)(result + 4);
  *(_DWORD *)(result + 8) = v10;
  v12 = a1[1];
  *(_BYTE *)(result + 4) = v11 & 0xFE;
  *(_DWORD *)(result + 4) |= v12 & 1;
  v13 = a1[1];
  *(_BYTE *)(result + 4) &= ~2u;
  *(_DWORD *)(result + 4) |= v13 & 2;
  v14 = a1[1];
  *(_BYTE *)(result + 4) &= ~4u;
  *(_DWORD *)(result + 4) |= v14 & 4;
  v15 = a1[1];
  *(_BYTE *)(result + 4) &= ~8u;
  *(_DWORD *)(result + 4) |= v15 & 8;
  if ( a1[4] == -1 )
    *(_DWORD *)(result + 16) = 0;
  else
    *(_DWORD *)(result + 16) = 20 * (a2 + 1) + g_DeftemplateSlotTable;
  return result;
}
// 54E674: using guessed type int dword_54E674;
// 54E688: using guessed type int dword_54E688;
// 54E68C: using guessed type int dword_54E68C;
// 54E844: using guessed type int dword_54E844;

//----- (004BA700) --------------------------------------------------------
int Rules_DeftemplateClearBloaded()
{
  int v0; // ecx
  int v1; // edx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  signed int *v5; // eax
  char v6; // dl

  v0 = 0;
  if ( g_DeftemplateBsaveCount > 0 )
  {
    v1 = 0;
    do
    {
      Rules_ReleaseSymbolReference((int *)(v1 + g_DeftemplateRecordTable), v0 + 1);
      v1 = v2 + 36;
    }
    while ( v0 < g_DeftemplateBsaveCount );
  }
  if ( g_Deftemplate_SlotCount > 0 )
  {
    v0 = 0;
    do
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(v0 + g_DeftemplateSlotTable), v0);
      v0 = v3 + 20;
    }
    while ( v4 < g_Deftemplate_SlotCount );
  }
  if ( 12 * g_DeftemplateModuleItemCount )
    Mem_ReleasePoolBlock(g_ClipsDeftemplateModuleItemArray, 12 * g_DeftemplateModuleItemCount);
  if ( 36 * g_DeftemplateBsaveCount )
    Mem_ReleasePoolBlock(g_DeftemplateRecordTable, 36 * g_DeftemplateBsaveCount);
  if ( 20 * g_Deftemplate_SlotCount )
    Mem_ReleasePoolBlock(g_DeftemplateSlotTable, 20 * g_Deftemplate_SlotCount);
  v5 = Str_Intern(aInitialFact_0, v0);
  return Rules_CreateDeftemplateRecord((int)v5, v6);
}
// 4BA71A: variable 'v0' is possibly undefined
// 4BA726: variable 'v2' is possibly undefined
// 4BA752: variable 'v3' is possibly undefined
// 4BA757: variable 'v4' is possibly undefined
// 4BA7C9: variable 'v6' is possibly undefined
// 54E840: using guessed type int dword_54E840;
// 54E844: using guessed type int dword_54E844;
// 54E848: using guessed type int dword_54E848;
// 54E84C: using guessed type int dword_54E84C;
// 54E850: using guessed type int dword_54E850;
// 54E854: using guessed type int dword_54E854;

//----- (004BA800) --------------------------------------------------------
int  Rules_DeftemplateGetBloadedModuleItem(int a1)
{
  return 12 * a1 + g_ClipsDeftemplateModuleItemArray;
}
// 54E84C: using guessed type int dword_54E84C;

//----- (004BA820) --------------------------------------------------------
int Rules_RegisterDeftemplateCodeGen()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDeftemplate_3, 0, 0, 0, (int)Rules_DeftemplateGenerateCode, 3);
  g_Clips_DeftemplateCodeGenItem = result;
  return result;
}
// 54E858: using guessed type int dword_54E858;

//----- (004BA850) --------------------------------------------------------
int  Rules_DeftemplateGenerateCode(const char *a1, const char *a2, int a3, int a4, int a5)
{
  int v5; // edx
  int v6; // esi
  int Enum; // eax
  int v8; // edx
  int v9; // esi
  int v10; // eax
  int v11; // edi
  int v12; // eax
  int v13; // edi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // esi
  int v20; // eax
  int v21; // ecx
  int v23; // [esp+0h] [ebp-50h] BYREF
  int v24; // [esp+4h] [ebp-4Ch] BYREF
  int v25; // [esp+8h] [ebp-48h] BYREF
  int v26; // [esp+Ch] [ebp-44h] BYREF
  int v27; // [esp+10h] [ebp-40h] BYREF
  int v28; // [esp+14h] [ebp-3Ch] BYREF
  int v29; // [esp+18h] [ebp-38h] BYREF
  int v30; // [esp+1Ch] [ebp-34h]
  int v31; // [esp+20h] [ebp-30h]
  int v32; // [esp+24h] [ebp-2Ch]
  int v33; // [esp+28h] [ebp-28h]
  int v34; // [esp+2Ch] [ebp-24h]
  const char *v35; // [esp+30h] [ebp-20h]
  const char *v36; // [esp+34h] [ebp-1Ch]
  int v37; // [esp+38h] [ebp-18h]
  int v38; // [esp+3Ch] [ebp-14h]
  int v39; // [esp+40h] [ebp-10h]

  v36 = a1;
  v35 = a2;
  v37 = a4;
  v38 = a3;
  v39 = 0;
  v24 = 0;
  v25 = 1;
  v32 = 0;
  v26 = 0;
  v27 = 1;
  v28 = 0;
  v29 = 1;
  v30 = 0;
  v33 = 0;
  Output_WriteFormatted(0, 1, a4, (int)aIncludeTmpltde, 1);
  v6 = v5;
  Enum = Module_NextEnum(0);
  v9 = v8 ^ v6;
  v31 = Enum;
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(v31);
      v10 = Rules_ConstructCodeFileOpen(
              v30,
              v36,
              v38,
              v35,
              &v23,
              v27,
              v37,
              (char)aStructDeftempl,
              **(const char ***)(g_Clips_DeftemplateCodeGenItem + 20),
              0,
              0);
      v11 = v10;
      if ( !v10 )
      {
        Rules_DeftemplateCodeGenCloseFiles(0, v33, a5, v9);
        return 0;
      }
      Rules_DeftemplateWriteModuleHeaderToCode(v10, v31, a5, v32);
      v30 = Rules_ConstructCodeFileClose(v11, &v26, a5, &v27, 0, 0);
      v34 = Rules_GetNextDeftemplate(0);
      if ( v34 )
        break;
LABEL_9:
      v31 = Module_NextEnum(v31);
      v32 = v21 + 1;
      ++v26;
      if ( !v31 )
        goto LABEL_10;
    }
    while ( 1 )
    {
      v12 = Rules_ConstructCodeFileOpen(
              v33,
              v36,
              v38,
              v35,
              &v23,
              v29,
              v37,
              (char)aStructDeftem_0,
              *(const char **)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 4),
              0,
              0);
      v13 = v12;
      if ( !v12 )
      {
        Rules_DeftemplateCodeGenCloseFiles(v30, 0, a5, v9);
        return 0;
      }
      Rules_DeftemplateWriteRecordToCode(v12, v34, a5, v38, v32, v39);
      v14 = v13;
      ++v28;
      v15 = v34;
      v16 = Rules_ConstructCodeFileClose(v14, &v28, a5, &v29, 0, 0);
      v17 = *(_DWORD *)(v15 + 20);
      v33 = v16;
      if ( v17 )
        break;
LABEL_8:
      v34 = Rules_GetNextDeftemplate(v34);
      if ( !v34 )
        goto LABEL_9;
    }
    while ( 1 )
    {
      v18 = Rules_ConstructCodeFileOpen(
              v9,
              v36,
              v38,
              v35,
              &v23,
              v25,
              v37,
              (char)aStructTemplate,
              *(const char **)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 8),
              0,
              0);
      v19 = v18;
      if ( !v18 )
        break;
      Rules_DeftemplateWriteSlotToCode(v18, v17, a5, v38, v39++);
      ++v24;
      v20 = Rules_ConstructCodeFileClose(v19, &v24, a5, &v25, 0, 0);
      v17 = *(_DWORD *)(v17 + 16);
      v9 = v20;
      if ( !v17 )
        goto LABEL_8;
    }
    Rules_DeftemplateCodeGenCloseFiles(v30, v33, a5, 0);
    return 0;
  }
  else
  {
LABEL_10:
    Rules_DeftemplateCodeGenCloseFiles(v30, v33, a5, v9);
    return 1;
  }
}
// 4BA8AD: variable 'v5' is possibly undefined
// 4BA8B4: variable 'v8' is possibly undefined
// 4BAA90: variable 'v21' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BAB10) --------------------------------------------------------
int  Rules_DeftemplateCodeGenCloseFiles(int a1, int a2, int a3, int a4)
{
  int result; // eax
  int v8; // [esp+0h] [ebp-14h] BYREF
  _DWORD v9[4]; // [esp+4h] [ebp-10h] BYREF

  result = a4;
  v8 = a3;
  v9[0] = 0;
  if ( a4 )
    result = Rules_ConstructCodeFileClose(a4, &v8, a3, v9, 0, 0);
  if ( a2 )
  {
    v8 = a3;
    result = Rules_ConstructCodeFileClose(a2, &v8, a3, v9, 0, 0);
  }
  if ( a1 )
  {
    v8 = a3;
    return Rules_ConstructCodeFileClose(a1, &v8, a3, v9, 0, 0);
  }
  return result;
}

//----- (004BAB90) --------------------------------------------------------
int  Rules_DeftemplateWriteModuleHeaderToCode(int a1, int a2, int a3, int a4)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50A17C, v10);
  Rules_WriteConstructModuleItemHeaderToCode(a1, v5, v6, g_ClipsDeftemplateModuleItemId, *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, a1, (int)asc_50A180, v11);
}
// 4BAB9B: variable 'v10' is possibly undefined
// 4BABB8: variable 'v5' is possibly undefined
// 4BABB8: variable 'v6' is possibly undefined
// 4BABC3: variable 'v8' is possibly undefined
// 4BABC3: variable 'v7' is possibly undefined
// 4BABC3: variable 'v11' is possibly undefined
// 54E654: using guessed type int dword_54E654;
// 54E858: using guessed type int dword_54E858;

//----- (004BABE0) --------------------------------------------------------
int  Rules_DeftemplateWriteRecordToCode(int a1, int a2, int a3, char a4, int a5, int a6)
{
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // eax
  int v18; // edx
  int v19; // ecx
  char v21; // [esp+0h] [ebp-10h]
  int v22; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50A17C, a4);
  Rules_WriteConstructHeaderToCode(a1, a2, a3, a5, **(_DWORD **)(g_Clips_DeftemplateCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 4));
  Output_WriteFormatted(v10, v9, a1, (int)asc_50A184, v21);
  if ( *(_DWORD *)(a2 + 20) )
    Output_WriteFormatted(
      *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 8),
      v22,
      a1,
      (int)aSD_DD_5,
      *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v12, v11, a1, (int)aNull_19, v22);
  Output_WriteFormatted(v14, v13, a1, (int)aD00DLd, *(_BYTE *)(a2 + 24) & 1);
  v17 = *(_DWORD *)(a2 + 32);
  if ( v17 )
    Rules_FactPatternNetworkWriteNodeRefToCode(v17, a1, a3);
  else
    Output_WriteFormatted(v16, v15, a1, (int)aNull_3, v22);
  return Output_WriteFormatted(v19, v18, a1, (int)asc_50A180, v22);
}
// 4BAC26: variable 'v10' is possibly undefined
// 4BAC26: variable 'v9' is possibly undefined
// 4BAC26: variable 'v21' is possibly undefined
// 4BAC69: variable 'v22' is possibly undefined
// 4BAC8C: variable 'v14' is possibly undefined
// 4BAC8C: variable 'v13' is possibly undefined
// 4BACA1: variable 'v16' is possibly undefined
// 4BACA1: variable 'v15' is possibly undefined
// 4BACAF: variable 'v19' is possibly undefined
// 4BACAF: variable 'v18' is possibly undefined
// 4BACC6: variable 'v12' is possibly undefined
// 4BACC6: variable 'v11' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BACE0) --------------------------------------------------------
int  Rules_DeftemplateWriteSlotToCode(int a1, int a2, int a3, char a4, int a5)
{
  int *v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  char v19; // [esp+0h] [ebp-10h]
  char v20; // [esp+0h] [ebp-10h]
  int v21; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(a3, a2, a1, (int)asc_50A17C, a4);
  Compiler_WriteSymbolReference(a1, *v8, v9);
  Output_WriteFormatted(v11, v10, a1, (int)aDDDD, *(_BYTE *)(a2 + 4) & 1);
  Compiler_WriteConstraintReference(a1, *(_DWORD *)(a2 + 8), v12, a4);
  Output_WriteFormatted(a3, v13, a1, (int)asc_50A184, v19);
  Rules_WriteExpressionRefToCode(a1, *(__int16 **)(a2 + 12), v14, v20);
  Output_WriteFormatted(v16, v15, a1, (int)asc_50A184, v20);
  if ( *(_DWORD *)(a2 + 16) )
    return Output_WriteFormatted(v21, (a5 + 1) % a3, a1, (int)aSD_DD_6, *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 8));
  else
    return Output_WriteFormatted(v17, 0, a1, (int)aNull_20, v21);
}
// 4BACFF: variable 'v8' is possibly undefined
// 4BAD01: variable 'v9' is possibly undefined
// 4BAD31: variable 'v11' is possibly undefined
// 4BAD31: variable 'v10' is possibly undefined
// 4BAD3E: variable 'v12' is possibly undefined
// 4BAD4B: variable 'v13' is possibly undefined
// 4BAD4B: variable 'v19' is possibly undefined
// 4BAD5B: variable 'v14' is possibly undefined
// 4BAD5B: variable 'v20' is possibly undefined
// 4BAD66: variable 'v16' is possibly undefined
// 4BAD66: variable 'v15' is possibly undefined
// 4BAD7B: variable 'v17' is possibly undefined
// 4BAD7B: variable 'v21' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BADD0) --------------------------------------------------------
int  Rules_DeftemplateWriteModuleHeaderRef(int a1, int a2)
{
  return Output_WriteFormatted(a2, **(_DWORD **)(g_Clips_DeftemplateCodeGenItem + 20), a1, (int)aMihsSD_DD_3, **(_DWORD **)(g_Clips_DeftemplateCodeGenItem + 20));
}
// 54E858: using guessed type int dword_54E858;

//----- (004BAE10) --------------------------------------------------------
int  Rules_DeftemplateWriteRecordRefToCode(int a1, int a2, int a3)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( a2 )
    return Output_WriteFormatted(
             a3,
             *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 4),
             a1,
             (int)aSD_LdLd,
             *(_DWORD *)(*(_DWORD *)(g_Clips_DeftemplateCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(a3, 0, a1, (int)aNull_3, v4);
}
// 4BAE20: variable 'v4' is possibly undefined
// 54E858: using guessed type int dword_54E858;

//----- (004BAE60) --------------------------------------------------------
signed int Rules_RegisterDefruleBinaryItem()
{
  return Rules_RegisterBinaryItem(
           (int)aDefrule_1,
           20,
           (int)Rules_DefruleBsaveWriteExpressions,
           (int)Rules_DefruleBsaveFind,
           (int)Rules_DefruleBsaveWriteCounts,
           (int)Rules_DefruleBsaveWriteData,
           (int)Rules_JoinNetworkBloadStorage,
           (int)Rules_JoinNetworkBload,
           (int)Rules_ClearBloadedJoinNetwork);
}

//----- (004BAEA0) --------------------------------------------------------
int Rules_DefruleBsaveFind()
{
  int i; // ebx
  _DWORD *j; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int k; // edx
  int v6; // edx
  int v7; // edx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DefruleModuleBloadCount);
    Rules_ConstructQueuePush(g_RuleJoinNodeBsaveCount);
    Rules_ConstructQueuePush(g_Clips_JoinTestCount);
  }
  Rules_JoinNetworkAssignCodeGenIds(&g_DefruleModuleBloadCount, &g_RuleJoinNodeBsaveCount, &g_Clips_JoinTestCount);
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = (_DWORD *)Rules_GetNextDefrule(0); j; j = (_DWORD *)Rules_GetNextDefrule(v4) )
    {
      AST_MarkNodeFieldBound(j, j[3]);
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v2 + 32));
      Rules_MarkReferencedFunctions(*(__int16 **)(v3 + 32));
      for ( k = v4; k; k = *(_DWORD *)(v7 + 48) )
      {
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(k + 36));
        Rules_MarkReferencedFunctions(*(__int16 **)(v6 + 36));
      }
    }
  }
  return Rules_ClearJoinNetworkMarkedFlags();
}
// 4BAF10: variable 'v2' is possibly undefined
// 4BAF1E: variable 'v3' is possibly undefined
// 4BAF26: variable 'v4' is possibly undefined
// 4BAF3A: variable 'v6' is possibly undefined
// 4BAF42: variable 'v7' is possibly undefined
// 54E680: using guessed type int dword_54E680;
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BAF80) --------------------------------------------------------
int  Rules_DefruleBsaveWriteExpressions(int a1)
{
  int i; // edi
  int j; // esi
  int k; // ecx
  int v5; // ecx

  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDefrule(0); j; j = Rules_GetNextDefrule(j) )
    {
      Rules_BsaveWriteExpression(*(__int16 **)(j + 32), a1);
      for ( k = j; k; k = *(_DWORD *)(v5 + 48) )
        Rules_BsaveWriteExpression(*(__int16 **)(k + 36), a1);
    }
  }
  return Rules_ClearJoinNetworkMarkedFlags();
}
// 4BAFC5: variable 'v5' is possibly undefined

//----- (004BB000) --------------------------------------------------------
const void * Rules_DefruleBsaveWriteCounts(int a1, int a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  _DWORD v6[4]; // [esp+0h] [ebp-10h] BYREF

  v6[2] = a2;
  v6[0] = 12;
  Rules_BsaveWriteBlock(4, a1, v6);
  Rules_BsaveWriteBlock(4, v2, &g_DefruleModuleBloadCount);
  Rules_BsaveWriteBlock(4, v3, &g_RuleJoinNodeBsaveCount);
  return Rules_BsaveWriteBlock(4, v4, &g_Clips_JoinTestCount);
}
// 4BB02A: variable 'v2' is possibly undefined
// 4BB03B: variable 'v3' is possibly undefined
// 4BB04C: variable 'v4' is possibly undefined
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BB060) --------------------------------------------------------
int  Rules_DefruleBsaveWriteData(const void *a1, int a2)
{
  int i; // ecx
  int v4; // eax
  _DWORD *v5; // eax
  int v6; // ecx
  int j; // ebx
  int k; // ecx
  int v9; // ecx
  int result; // eax
  _DWORD v11[3]; // [esp-Ch] [ebp-20h] BYREF
  _DWORD v12[5]; // [esp+0h] [ebp-14h] BYREF

  v12[3] = a2;
  v12[0] = 12 * g_DefruleModuleBloadCount + 32 * g_Clips_JoinTestCount + 44 * g_RuleJoinNodeBsaveCount;
  Rules_BsaveWriteBlock(4, (int)a1, v12);
  g_RuleJoinNodeBsaveCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v6) )
  {
    Module_SetCurrent(i);
    v4 = Module_FindItemByName((int)aDefrule_1);
    v5 = (_DWORD *)Module_GetItem(0, *(_DWORD *)(v4 + 4));
    Module_AssignBsaveItemHeaderIndices(v11, v5);
    Rules_BsaveWriteBlock(12, (int)a1, v11);
  }
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Rules_GetNextDefrule(0); k; k = Rules_GetNextDefrule(v9) )
      Rules_BsaveDefruleDisjuncts(a1, k);
  }
  Rules_ClearJoinNetworkMarkedFlags();
  Rules_BsaveJoinNetworkForModules((int)a1);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DefruleModuleBloadCount);
    Rules_ConstructQueuePop(&g_RuleJoinNodeBsaveCount);
    return Rules_ConstructQueuePop(&g_Clips_JoinTestCount);
  }
  return result;
}
// 4BB0EF: variable 'v6' is possibly undefined
// 4BB12C: variable 'v9' is possibly undefined
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BB190) --------------------------------------------------------
const void * Rules_BsaveDefruleDisjuncts(const void *result, int a2)
{
  int v2; // esi
  int v3; // ebx
  int v4; // ecx
  int i; // edi
  _DWORD *v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // eax
  int v11; // ebp
  int v12; // eax
  int v13; // ecx
  _DWORD v14[5]; // [esp+0h] [ebp-40h] BYREF
  int v15; // [esp+14h] [ebp-2Ch]
  int v16; // [esp+18h] [ebp-28h]
  int v17; // [esp+1Ch] [ebp-24h]
  int v18; // [esp+20h] [ebp-20h]
  int v19; // [esp+24h] [ebp-1Ch]
  int v20; // [esp+28h] [ebp-18h]

  v2 = (int)result;
  v3 = 1;
  v4 = a2;
  for ( i = 0; v4; v3 = 0 )
  {
    ++g_RuleJoinNodeBsaveCount;
    AST_ExtractPatternBindingInfo(v14, v4);
    v14[3] = v6[5];
    v14[4] = v6[6];
    v7 = v6[7];
    LOWORD(v15) = v15 & 0xF000;
    v15 |= v7 & 0x7FF;
    v8 = v6[7] << 17 >> 31;
    BYTE1(v15) &= ~0x10u;
    v15 |= (v8 & 1) << 12;
    if ( v6[8] )
    {
      if ( v3 )
      {
        v16 = g_ClipsExpressionNodeIndex;
        i = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(v6[8]);
      }
      else
      {
        v16 = i;
      }
    }
    else
    {
      v16 = -1;
    }
    if ( v6[9] )
    {
      v17 = g_ClipsExpressionNodeIndex;
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(v6[9]);
    }
    else
    {
      v17 = -1;
    }
    v9 = v6[10];
    if ( v9 )
      v10 = *(_DWORD *)(v9 + 4);
    else
      v10 = -1;
    v18 = v10;
    v11 = v6[11];
    if ( v11 )
      v12 = *(_DWORD *)(v11 + 4);
    else
      v12 = -1;
    v19 = v12;
    if ( v6[12] )
      v20 = g_RuleJoinNodeBsaveCount;
    else
      v20 = -1;
    result = Rules_BsaveWriteBlock(44, v2, v14);
    v4 = *(_DWORD *)(v13 + 48);
  }
  return result;
}
// 4BB1C1: variable 'v6' is possibly undefined
// 4BB296: variable 'v13' is possibly undefined
// 54E680: using guessed type int dword_54E680;
// 54E864: using guessed type int dword_54E864;

//----- (004BB2E0) --------------------------------------------------------
int  Rules_BsaveJoinNetworkForModules(int a1)
{
  int result; // eax
  int i; // edi
  int v4; // esi
  int *v5; // ecx
  int *v6; // eax

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    v4 = Rules_GetNextDefrule(0);
    while ( v4 )
    {
      v5 = *(int **)(v4 + 44);
      if ( v5 )
      {
        do
        {
          if ( (*(_BYTE *)v5 & 0x20) != 0 )
            Rules_BsaveJoinNode(a1, v5);
          if ( (*(_BYTE *)v5 & 4) != 0 )
            v6 = (int *)v5[4];
          else
            v6 = (int *)v5[6];
          v5 = v6;
        }
        while ( v6 );
      }
      if ( *(_DWORD *)(v4 + 48) )
        v4 = *(_DWORD *)(v4 + 48);
      else
        v4 = Rules_GetNextDefrule(v4);
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4BB320: variable 'v5' is possibly undefined

//----- (004BB360) --------------------------------------------------------
const void * Rules_BsaveJoinNode(int a1, int *a2)
{
  unsigned int v3; // eax
  unsigned int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // ebp
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // esi
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // ebp
  _DWORD v21[2]; // [esp+0h] [ebp-34h] BYREF
  int v22; // [esp+8h] [ebp-2Ch]
  int v23; // [esp+Ch] [ebp-28h]
  int v24; // [esp+10h] [ebp-24h]
  int v25; // [esp+14h] [ebp-20h]
  int v26; // [esp+18h] [ebp-1Ch]
  int v27; // [esp+1Ch] [ebp-18h]

  *(_BYTE *)a2 &= ~0x20u;
  v3 = (unsigned int)(*a2 << 16) >> 25;
  LOWORD(v21[0]) &= 0xC07Fu;
  v21[0] |= (v3 & 0x7F) << 7;
  v4 = (unsigned int)(*a2 << 23) >> 29;
  LOBYTE(v21[0]) &= 0x8Fu;
  v21[0] |= 16 * (v4 & 7);
  v5 = *a2;
  LOBYTE(v21[0]) &= ~1u;
  v21[0] |= v5 & 1;
  v6 = *a2;
  LOBYTE(v21[0]) &= ~2u;
  v21[0] |= v6 & 2;
  v7 = *a2;
  LOBYTE(v21[0]) &= ~4u;
  v21[0] |= v7 & 4;
  v8 = *a2;
  LOBYTE(v21[0]) &= ~8u;
  v21[0] |= v8 & 8;
  if ( (*(_BYTE *)a2 & 4) != 0 )
  {
    v9 = a2[4];
    if ( v9 )
      v10 = *(_DWORD *)(v9 + 4);
    else
      v10 = -1;
    v22 = v10;
  }
  else
  {
    v22 = -1;
  }
  v11 = a2[6];
  if ( v11 )
    v12 = *(_DWORD *)(v11 + 4);
  else
    v12 = -1;
  v24 = v12;
  v13 = a2[5];
  if ( v13 )
    v14 = *(_DWORD *)(v13 + 4);
  else
    v14 = -1;
  v23 = v14;
  v15 = a2[8];
  if ( v15 )
    v16 = *(_DWORD *)(v15 + 4);
  else
    v16 = -1;
  v26 = v16;
  v17 = a2[7];
  if ( v17 )
    v18 = *(_DWORD *)(v17 + 4);
  else
    v18 = -1;
  v25 = v18;
  v21[1] = AST_GetHashedNodeIndex((__int16 *)a2[3]);
  v19 = a2[9];
  if ( v19 )
    v27 = *(_DWORD *)(v19 + 12);
  else
    v27 = -1;
  return Rules_BsaveWriteBlock(32, a1, v21);
}

//----- (004BB4C0) --------------------------------------------------------
int  Rules_BsavePackSharedRecordHeader(int result, int a2)
{
  int v2; // ecx
  int v3; // esi
  int v4; // ecx
  char v5; // bh
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx

  v2 = *(_DWORD *)(a2 + 12);
  *(_BYTE *)(result + 4) &= ~2u;
  *(_DWORD *)(result + 4) |= v2 & 2;
  v3 = *(_DWORD *)(a2 + 8);
  if ( v3 )
    v4 = *(_DWORD *)(v3 + 4);
  else
    v4 = -1;
  v5 = *(_BYTE *)(result + 4);
  *(_DWORD *)result = v4;
  v6 = *(_DWORD *)(a2 + 12);
  *(_BYTE *)(result + 4) = v5 & 0xFE;
  *(_DWORD *)(result + 4) |= v6 & 1;
  v7 = *(_DWORD *)(a2 + 12);
  *(_BYTE *)(result + 4) &= ~4u;
  *(_DWORD *)(result + 4) |= v7 & 4;
  v8 = *(_DWORD *)(a2 + 12) << 26 >> 31;
  *(_BYTE *)(result + 4) &= ~0x40u;
  *(_DWORD *)(result + 4) |= (v8 & 1) << 6;
  v9 = *(_DWORD *)(a2 + 12) << 25 >> 31;
  *(_BYTE *)(result + 4) &= ~0x80u;
  *(_DWORD *)(result + 4) |= (v9 & 1) << 7;
  return result;
}

//----- (004BB550) --------------------------------------------------------
signed int Rules_JoinNetworkBloadStorage()
{
  signed int result; // eax
  int v1[3]; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)v1, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DefruleModuleBloadCount, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_RuleJoinNodeBsaveCount, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_Clips_JoinTestCount, 4u);
  if ( !g_DefruleModuleBloadCount )
  {
    g_ClipsJoinNetworkModuleBloadArray = 0;
    g_ClipsBloadJoinArray = 0;
    g_ClipsJoinNodeArray = 0;
  }
  v1[0] = 16 * g_DefruleModuleBloadCount;
  result = Mem_HeapAllocWithRetry((_DWORD *)(16 * g_DefruleModuleBloadCount));
  g_ClipsJoinNetworkModuleBloadArray = result;
  if ( g_RuleJoinNodeBsaveCount )
  {
    v1[0] = 52 * g_RuleJoinNodeBsaveCount;
    g_ClipsBloadJoinArray = Mem_HeapAllocWithRetry((_DWORD *)(52 * g_RuleJoinNodeBsaveCount));
    v1[0] = 40 * g_Clips_JoinTestCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(40 * g_Clips_JoinTestCount));
    g_ClipsJoinNodeArray = result;
  }
  else
  {
    g_ClipsBloadJoinArray = 0;
    g_ClipsJoinNodeArray = 0;
  }
  return result;
}
// 54E85C: using guessed type int dword_54E85C;
// 54E860: using guessed type int dword_54E860;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;
// 54E86C: using guessed type int dword_54E86C;
// 54E870: using guessed type int dword_54E870;

//----- (004BB620) --------------------------------------------------------
signed int Rules_JoinNetworkBload()
{
  int v3; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&v3, 4u);
  Rules_BloadAndRefresh(g_DefruleModuleBloadCount, 12, (void (__fastcall *)(signed int, signed int))Rules_DefruleModuleBloadFixup);
  Rules_BloadAndRefresh(g_RuleJoinNodeBsaveCount, 44, (void (__fastcall *)(signed int, signed int))Rules_JoinBloadFixup);
  return Rules_BloadAndRefresh(g_Clips_JoinTestCount, 32, (void (__fastcall *)(signed int, signed int))Rules_JoinTestBloadFixup);
}
// 54E85C: using guessed type int dword_54E85C;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;

//----- (004BB680) --------------------------------------------------------
int  Rules_DefruleModuleBloadFixup(_DWORD *a1, int a2)
{
  int v2; // esi
  int result; // eax

  v2 = 16 * a2;
  Module_UpdateItemHeader(a1, (_DWORD *)(16 * a2 + g_ClipsJoinNetworkModuleBloadArray), g_ClipsBloadJoinArray, 52);
  result = g_ClipsJoinNetworkModuleBloadArray;
  *(_DWORD *)(v2 + g_ClipsJoinNetworkModuleBloadArray + 12) = 0;
  return result;
}
// 54E860: using guessed type int dword_54E860;
// 54E870: using guessed type int dword_54E870;

//----- (004BB6C0) --------------------------------------------------------
int  Rules_JoinBloadFixup(_DWORD *a1, int a2)
{
  int v5; // ecx
  int v6; // eax
  int v7; // ebx
  int v8; // eax
  int v9; // ebp
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // edx
  int v14; // edx
  int v15; // eax
  int v16; // edi
  int v17; // edx
  int v18; // edi
  int v19; // edx
  int v20; // esi
  int v21; // edx
  int result; // eax
  int v23; // edx

  Rules_BuildIndexedSlotDescriptor((int)a1, (_DWORD *)(g_ClipsBloadJoinArray + 52 * a2), g_ClipsJoinNetworkModuleBloadArray, 16, 52, g_ClipsBloadJoinArray);
  v5 = a1[6];
  if ( v5 == -1 )
    v6 = 0;
  else
    v6 = g_ClipsPackedExpressionArray + 14 * v5;
  *(_DWORD *)(g_ClipsBloadJoinArray + 52 * a2 + 32) = v6;
  v7 = a1[7];
  if ( v7 == -1 )
    v8 = 0;
  else
    v8 = g_ClipsPackedExpressionArray + 14 * v7;
  *(_DWORD *)(52 * a2 + g_ClipsBloadJoinArray + 36) = v8;
  v9 = a1[8];
  if ( v9 == -1 )
    v10 = 0;
  else
    v10 = g_ClipsJoinNodeArray + 40 * v9;
  *(_DWORD *)(g_ClipsBloadJoinArray + 52 * a2 + 40) = v10;
  v11 = a1[9];
  if ( v11 == -1 )
    v12 = 0;
  else
    v12 = 40 * v11 + g_ClipsJoinNodeArray;
  *(_DWORD *)(g_ClipsBloadJoinArray + 52 * a2 + 44) = v12;
  v13 = a1[10];
  if ( v13 == -1 )
    v14 = 0;
  else
    v14 = g_ClipsBloadJoinArray + 52 * v13;
  v15 = 52 * a2;
  *(_DWORD *)(g_ClipsBloadJoinArray + v15 + 48) = v14;
  *(_DWORD *)(g_ClipsBloadJoinArray + v15 + 20) = a1[3];
  *(_DWORD *)(g_ClipsBloadJoinArray + 52 * a2 + 24) = a1[4];
  v16 = g_ClipsBloadJoinArray;
  v17 = a1[5];
  *(_WORD *)(g_ClipsBloadJoinArray + v15 + 28) &= 0xF800u;
  *(_DWORD *)(v16 + v15 + 28) |= v17 & 0x7FF;
  v18 = g_ClipsBloadJoinArray;
  v19 = a1[5] << 19 >> 31;
  *(_BYTE *)(g_ClipsBloadJoinArray + v15 + 29) &= ~0x40u;
  *(_DWORD *)(v18 + v15 + 28) |= v19 << 14;
  *(_BYTE *)(g_ClipsBloadJoinArray + v15 + 29) &= ~0x80u;
  *(_BYTE *)(g_ClipsBloadJoinArray + v15 + 29) &= ~8u;
  v20 = g_ClipsBloadJoinArray;
  v21 = g_Rules_WatchActivationsFlag & 1;
  *(_BYTE *)(g_ClipsBloadJoinArray + v15 + 29) &= ~0x10u;
  *(_DWORD *)(v20 + v15 + 28) |= v21 << 12;
  result = g_ClipsBloadJoinArray + v15;
  v23 = g_WatchRulesFlag & 1;
  *(_BYTE *)(result + 29) &= ~0x20u;
  *(_DWORD *)(result + 28) |= v23 << 13;
  return result;
}
// 51A1DC: using guessed type int dword_51A1DC;
// 51AD08: using guessed type int dword_51AD08;
// 54E688: using guessed type int dword_54E688;
// 54E860: using guessed type int dword_54E860;
// 54E86C: using guessed type int dword_54E86C;
// 54E870: using guessed type int dword_54E870;

//----- (004BB8C0) --------------------------------------------------------
int  Rules_JoinTestBloadFixup(int *a1, int a2)
{
  int v2; // esi
  int v3; // ebx
  int v4; // edi
  int v5; // esi
  int v6; // edi
  int v7; // esi
  int v8; // edi
  int v9; // esi
  int v10; // edi
  int v11; // esi
  unsigned int v12; // edi
  _WORD *v13; // ebx
  unsigned int v14; // esi
  int v15; // ebp
  int v16; // esi
  int v17; // ecx
  int v18; // ebx
  int v19; // ebx
  int v20; // esi
  int v21; // esi
  int v22; // ebx
  int v23; // edi
  int v24; // ebx
  int v25; // ebp
  int v26; // esi
  int v27; // ecx
  int v28; // ecx
  int result; // eax

  v2 = g_ClipsJoinNodeArray;
  v3 = 40 * a2;
  v4 = *a1;
  *(_BYTE *)(g_ClipsJoinNodeArray + v3) &= ~1u;
  *(_DWORD *)(v2 + v3) |= v4 & 1;
  v5 = g_ClipsJoinNodeArray;
  v6 = *a1;
  *(_BYTE *)(g_ClipsJoinNodeArray + v3) &= ~2u;
  *(_DWORD *)(v5 + v3) |= v6 & 2;
  v7 = g_ClipsJoinNodeArray;
  v8 = *a1;
  *(_BYTE *)(g_ClipsJoinNodeArray + v3) &= ~4u;
  *(_DWORD *)(v7 + v3) |= v8 & 4;
  v9 = g_ClipsJoinNodeArray;
  v10 = *a1;
  *(_BYTE *)(g_ClipsJoinNodeArray + v3) &= ~8u;
  *(_DWORD *)(v9 + v3) |= v10 & 8;
  v11 = g_ClipsJoinNodeArray;
  v12 = (unsigned int)(*a1 << 18) >> 25;
  *(_BYTE *)(g_ClipsJoinNodeArray + v3 + 1) &= 1u;
  *(_DWORD *)(v11 + v3) = ((v12 & 0x7F) << 9) | *(_DWORD *)(v11 + 40 * a2);
  v13 = (_WORD *)(g_ClipsJoinNodeArray + 40 * a2);
  v14 = (unsigned int)(*a1 << 25) >> 29;
  *v13 &= 0xFE3Fu;
  *(_DWORD *)v13 |= (v14 & 7) << 6;
  v15 = a1[1];
  if ( v15 == -1 )
    v16 = 0;
  else
    v16 = 14 * v15 + g_ClipsPackedExpressionArray;
  *(_DWORD *)(g_ClipsJoinNodeArray + 40 * a2 + 12) = v16;
  v17 = a1[3];
  if ( v17 == -1 )
    v18 = 0;
  else
    v18 = 40 * v17 + g_ClipsJoinNodeArray;
  *(_DWORD *)(g_ClipsJoinNodeArray + 40 * a2 + 20) = v18;
  v19 = a1[4];
  if ( v19 == -1 )
    v20 = 0;
  else
    v20 = 40 * v19 + g_ClipsJoinNodeArray;
  *(_DWORD *)(g_ClipsJoinNodeArray + 40 * a2 + 24) = v20;
  if ( (*(_BYTE *)a1 & 4) != 0 )
  {
    v21 = a1[2];
    if ( v21 == -1 )
      v22 = 0;
    else
      v22 = 40 * v21 + g_ClipsJoinNodeArray;
    *(_DWORD *)(g_ClipsJoinNodeArray + 40 * a2 + 16) = v22;
  }
  v23 = a1[6];
  if ( v23 == -1 )
    v24 = 0;
  else
    v24 = 40 * v23 + g_ClipsJoinNodeArray;
  *(_DWORD *)(g_ClipsJoinNodeArray + 40 * a2 + 32) = v24;
  v25 = a1[5];
  if ( v25 == -1 )
    v26 = 0;
  else
    v26 = 40 * v25 + g_ClipsJoinNodeArray;
  *(_DWORD *)(g_ClipsJoinNodeArray + 40 * a2 + 28) = v26;
  v27 = a1[7];
  if ( v27 == -1 )
    v28 = 0;
  else
    v28 = 52 * v27 + g_ClipsBloadJoinArray;
  result = 5 * a2;
  *(_DWORD *)(g_ClipsJoinNodeArray + 8 * result + 36) = v28;
  *(_BYTE *)(g_ClipsJoinNodeArray + 8 * result) &= ~0x10u;
  *(_BYTE *)(g_ClipsJoinNodeArray + 8 * result) &= ~0x20u;
  *(_DWORD *)(g_ClipsJoinNodeArray + 8 * result + 4) = 0;
  *(_DWORD *)(g_ClipsJoinNodeArray + 8 * result + 8) = 0;
  return result;
}
// 54E688: using guessed type int dword_54E688;
// 54E860: using guessed type int dword_54E860;
// 54E86C: using guessed type int dword_54E86C;

//----- (004BBB60) --------------------------------------------------------
int  Rules_BloadUnpackSharedRecordHeader(int a1, int *a2)
{
  char v3; // bl
  int v4; // eax
  int v5; // eax
  int v6; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  int v9; // ebx
  int v10; // esi
  bool v11; // zf
  int v12; // edx
  int result; // eax

  v3 = *(_BYTE *)(a1 + 12) & 0xFE;
  v4 = a2[1];
  *(_BYTE *)(a1 + 12) = v3;
  *(_DWORD *)(a1 + 12) |= v4 & 1;
  v5 = a2[1];
  *(_BYTE *)(a1 + 12) &= ~2u;
  *(_DWORD *)(a1 + 12) |= v5 & 2;
  v6 = a2[1];
  *(_BYTE *)(a1 + 12) &= ~4u;
  *(_DWORD *)(a1 + 12) |= v6 & 4;
  v7 = (unsigned int)(a2[1] << 25) >> 31;
  *(_BYTE *)(a1 + 12) &= ~0x20u;
  *(_DWORD *)(a1 + 12) |= 32 * (v7 & 1);
  v8 = (unsigned int)(a2[1] << 24) >> 31;
  *(_BYTE *)(a1 + 12) &= ~0x40u;
  v9 = *(_DWORD *)(a1 + 12);
  *(_DWORD *)a1 = 0;
  *(_DWORD *)(a1 + 12) = ((v8 & 1) << 6) | v9;
  BYTE1(v9) = *(_BYTE *)(a1 + 12);
  *(_DWORD *)(a1 + 4) = 0;
  *(_BYTE *)(a1 + 12) = BYTE1(v9) & 0xE7;
  v10 = *a2;
  if ( *a2 == -1 )
  {
    v12 = 0;
    v11 = 1;
  }
  else
  {
    v11 = 40 * v10 + g_ClipsJoinNodeArray == 0;
    v12 = 40 * v10 + g_ClipsJoinNodeArray;
  }
  result = v12;
  *(_DWORD *)(a1 + 8) = v12;
  if ( !v11 )
  {
    do
    {
      *(_DWORD *)(result + 16) = a1;
      result = *(_DWORD *)(result + 32);
    }
    while ( result );
  }
  return result;
}
// 54E86C: using guessed type int dword_54E86C;

//----- (004BBC30) --------------------------------------------------------
signed int Rules_ClearBloadedJoinNetwork()
{
  int module_node; // edx
  int offset; // edx
  int index; // ecx
  signed int result; // eax
  int v11; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD v12[6]; // [esp+4h] [ebp-18h] BYREF

  v11 = 0;
  v12[0] = 0;
  Rules_FindPatternParser((_DWORD *)&v11, v12);
  if ( v12[0] )
  {
    do
    {
      (*(void (__fastcall **)(int))(*(_DWORD *)v12[0] + 12))(v12[0]);
      v12[0] = 0;
      Rules_FindPatternParser((_DWORD *)&v11, v12);
    }
    while ( v12[0] );
  }
  Module_BeginEnum();
  for ( module_node = Module_NextEnum(0); module_node; module_node = Module_NextEnum(module_node) )
  {
    Module_SetCurrent(module_node);
    Rules_ClearActivationsForModule();
  }
  Module_EndEnum();
  Rules_ClearFocusStack();
  if ( g_Clips_JoinTestCount > 0 )
  {
    offset = 0;
    for ( index = 0; index < g_Clips_JoinTestCount; ++index )
    {
      Rules_ReleaseJoinNetworkNodeChain(*(_DWORD *)(offset + g_ClipsJoinNodeArray + 8));
      offset += 40;
    }
  }
  if ( g_RuleJoinNodeBsaveCount > 0 )
  {
    offset = 0;
    for ( index = 0; index < g_RuleJoinNodeBsaveCount; ++index )
    {
      Rules_ReleaseSymbolReference((int *)(offset + g_ClipsBloadJoinArray), index + 1);
      offset += 52;
    }
  }
  if ( 16 * g_DefruleModuleBloadCount )
    Mem_ReleasePoolBlock(g_ClipsJoinNetworkModuleBloadArray, 16 * g_DefruleModuleBloadCount);
  if ( 52 * g_RuleJoinNodeBsaveCount )
    Mem_ReleasePoolBlock(g_ClipsBloadJoinArray, 52 * g_RuleJoinNodeBsaveCount);
  result = 40 * g_Clips_JoinTestCount;
  if ( 40 * g_Clips_JoinTestCount )
    return Mem_ReleasePoolBlock(g_ClipsJoinNodeArray, 40 * g_Clips_JoinTestCount);
  return result;
}
// 54E85C: using guessed type int dword_54E85C;
// 54E860: using guessed type int dword_54E860;
// 54E864: using guessed type int dword_54E864;
// 54E868: using guessed type int dword_54E868;
// 54E86C: using guessed type int dword_54E86C;
// 54E870: using guessed type int dword_54E870;

//----- (004BBD90) --------------------------------------------------------
int  Rules_JoinNetworkModuleRecord(int a1)
{
  return g_ClipsJoinNetworkModuleBloadArray + 16 * a1;
}
// 54E870: using guessed type int dword_54E870;

//----- (004BBDA0) --------------------------------------------------------
int  Rules_ParseDeftemplate(char *a1, double a2)
{
  int v3; // edx
  int v4; // ecx
  int v5; // edi
  int v7; // ecx
  _DWORD *v8; // ebx
  _DWORD *v9; // ebp
  signed int v10; // esi
  char v11; // ah
  int v12; // ecx
  __int16 v13; // ax
  int v14; // ecx
  _DWORD *v15; // ecx
  char *v16; // eax
  _DWORD v17[9]; // [esp+0h] [ebp-24h] BYREF

  g_DeftemplateSlotParseErrorFlag = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  IO_OutWriteToken(aDeftemplate_8);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  g_Rules_DeftemplateWatchFlag = v3;
  v5 = Rules_GetConstructNameAndComment(
         (int)a1,
         (int)v17,
         (int (*)(void))Rules_FindDeftemplateByName,
         aDeftemplate_9,
         (int (*)(void))Rules_DeleteDeftemplate,
         asc_50A228,
         1,
         1,
         1);
  if ( !v5 )
    return 1;
  if ( Rules_IsReservedPatternSymbol(v4, (int)aDeftemplate_9) )
  {
    Rules_PrintReservedSymbolErrorMessage(v7, (int)aADeftemplateNa);
    return 1;
  }
  else
  {
    v8 = Rules_ParseTemplateSlotList(a1, v17, a2);
    if ( g_DeftemplateSlotParseErrorFlag == 1 )
    {
      return 1;
    }
    else
    {
      v9 = *(_DWORD **)(g_ClipsMemoryTable + 144);
      if ( v9 )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 144);
        *(_DWORD *)(g_ClipsMemoryTable + 144) = *v9;
        v10 = g_ClipsMemFreeListTemp;
      }
      else
      {
        v10 = Mem_HeapAllocWithRetry((_DWORD *)0x24);
      }
      *(_DWORD *)(v10 + 16) = 0;
      *(_WORD *)(v10 + 24) = 0;
      *(_DWORD *)(v10 + 28) = 0;
      *(_DWORD *)(v10 + 32) = 0;
      *(_DWORD *)v10 = v5;
      v11 = *(_BYTE *)(v10 + 24);
      *(_DWORD *)(v10 + 20) = v8;
      *(_BYTE *)(v10 + 24) = v11 | 4;
      for ( *(_DWORD *)(v10 + 8) = Module_GetItem(0, g_ClipsDeftemplateModuleItemId); v8; v8 = (_DWORD *)v8[4] )
      {
        v13 = (*(_WORD *)(v12 + 24) >> 3) + 1;
        *(_WORD *)(v12 + 24) &= 7u;
        *(_DWORD *)(v12 + 24) |= 8 * (v13 & 0x1FFF);
      }
      if ( Mem_GetAllocFlag() == 1 )
      {
        *(_DWORD *)(v14 + 4) = 0;
      }
      else
      {
        v16 = Rules_CopyPPBuffer();
        *(_DWORD *)(v14 + 4) = v16;
      }
      if ( (g_Rules_DeftemplateWatchFlag & 1) != 0 || Rules_GetWatchItemState((int)aFacts_0) )
        Rules_SetFactWatchFlag(1, v14);
      Rules_AppendConstructToModuleList(v14);
      Rules_DeftemplateInstallSlots(v15, (int)v15);
      return 0;
    }
  }
}
// 4BBDEB: variable 'v3' is possibly undefined
// 4BBE2C: variable 'v4' is possibly undefined
// 4BBEB1: variable 'v12' is possibly undefined
// 4BBEFA: variable 'v14' is possibly undefined
// 4BBF1F: variable 'v15' is possibly undefined
// 4BBF38: variable 'v7' is possibly undefined
// 51A948: using guessed type int dword_51A948;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E654: using guessed type int dword_54E654;
// 54E874: using guessed type int dword_54E874;

//----- (004BBF90) --------------------------------------------------------
_DWORD * Rules_DeftemplateInstallSlots(_DWORD *result, int a2)
{
  __int16 **i; // edx
  int v3; // edx
  int v4; // edx
  _DWORD *v5; // eax
  int v6; // ecx
  int v7; // edx

  ++*(_DWORD *)(*result + 4);
  for ( i = (__int16 **)result[5]; i; i = *(__int16 ***)(v7 + 16) )
  {
    ++*((_DWORD *)*i + 1);
    AST_AddHashedNodeChain(i[3], (int)i, a2);
    AST_Free(*(_DWORD *)(v3 + 12));
    v5 = *(_DWORD **)(v4 + 8);
    *(_DWORD *)(v4 + 12) = v6;
    result = AST_InternNode(v5);
    *(_DWORD *)(v7 + 8) = result;
  }
  return result;
}
// 4BBFA6: variable 'a2' is possibly undefined
// 4BBFAD: variable 'v3' is possibly undefined
// 4BBFB5: variable 'v4' is possibly undefined
// 4BBFB8: variable 'v6' is possibly undefined
// 4BBFC0: variable 'v7' is possibly undefined

//----- (004BBFE0) --------------------------------------------------------
_DWORD * Rules_ParseTemplateSlotList(char *a1, _DWORD *a2, double a3)
{
  _DWORD *v4; // ecx
  _DWORD *v5; // edi
  int v6; // ebp
  _DWORD *v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // edx

  v4 = a2;
  v5 = 0;
  v6 = 0;
  if ( *a2 == 101 )
  {
LABEL_12:
    IO_OutWriteToken(asc_50A250);
    return v5;
  }
  else
  {
    while ( 1 )
    {
      if ( *v4 != 100 )
      {
        Parser_ReportSyntaxError();
        Rules_FreeTemplateSlotList((int)v5);
        Rules_FreeTemplateSlotList(0);
        g_DeftemplateSlotParseErrorFlag = v12;
        return 0;
      }
      Parser_NextToken((int)a1, (int)v4);
      if ( *v7 != 2 )
      {
        Parser_ReportSyntaxError();
        Rules_FreeTemplateSlotList((int)v5);
        Rules_FreeTemplateSlotList(0);
        g_DeftemplateSlotParseErrorFlag = v13;
        return 0;
      }
      v8 = Rules_ParseTemplateSlot(a1, (int)v7, v5, a3);
      if ( g_DeftemplateSlotParseErrorFlag == 1 )
        break;
      if ( v8 )
      {
        if ( v6 )
          *(_DWORD *)(v6 + 16) = v8;
        else
          v5 = (_DWORD *)v8;
        v6 = v8;
      }
      Parser_NextToken((int)a1, v9);
      if ( *v4 != 101 )
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_50A248);
        IO_OutWriteToken(*(char **)(v10 + 8));
      }
      if ( *v4 == 101 )
        goto LABEL_12;
    }
    Rules_FreeTemplateSlotList(v8);
    Rules_FreeTemplateSlotList((int)v5);
    Rules_FreeTemplateSlotList(0);
    return 0;
  }
}
// 4BBFFA: variable 'v4' is possibly undefined
// 4BC00C: variable 'v7' is possibly undefined
// 4BC045: variable 'v9' is possibly undefined
// 4BC05E: variable 'v10' is possibly undefined
// 4BC09E: variable 'v12' is possibly undefined
// 4BC0CD: variable 'v13' is possibly undefined
// 54E874: using guessed type int dword_54E874;

//----- (004BC110) --------------------------------------------------------
int  Rules_ParseTemplateSlot(char *a1, int a2, _DWORD *a3, double a4)
{
  int v5; // ecx
  int v6; // ecx
  BOOL v7; // edi
  int v8; // ecx
  _DWORD *v9; // ecx
  int result; // eax
  __int16 *v11; // ecx
  int v12; // esi
  int v13; // ecx
  int v14; // edx
  char v15; // ah
  int v16; // ecx
  char *v17; // edx

  if ( !strcmp_(a2, aField_0) || !strcmp_(v5, aMultifield_2) || !strcmp_(v5, aSlot_3) || !strcmp_(v5, aMultislot) )
  {
    v7 = !strcmp_(v5, aMultifield_2) || !strcmp_(v6, aMultislot);
    IO_OutWriteToken(asc_50A27C);
    Parser_NextToken((int)a1, v8);
    if ( *v9 == 2 )
    {
      if ( a3 )
      {
        while ( v9[1] != *a3 )
        {
          a3 = (_DWORD *)a3[4];
          if ( !a3 )
            goto LABEL_8;
        }
        Rules_ReportAlreadyParsed((int)v9, *(_DWORD *)(*a3 + 16));
        g_DeftemplateSlotParseErrorFlag = 1;
        return 0;
      }
      else
      {
LABEL_8:
        result = Rules_ParseTemplateSlotAttributes(a1, v9[1], (int)v9, v7, a4);
        v12 = result;
        if ( result )
        {
          if ( Rules_CheckConstraintParseConflicts(*(_DWORD *)(result + 8), v11) )
          {
            v15 = *(_BYTE *)(v14 + 4);
            if ( ((v15 & 4) != 0 || (v15 & 8) != 0)
              && Rules_CheckFieldExprListAgainstConstraint(*(int **)(v12 + 12), *(_DWORD *)(v12 + 8))
              && Rules_StaticConstraintCheckingEnabled() )
            {
              if ( (*(_BYTE *)(v12 + 4) & 8) != 0 )
                v17 = aTheDefaultDyna;
              else
                v17 = aTheDefaultAttr;
              Rules_PrintConstraintViolationMessage((int)aAnExpression, (int)v17, 0, 0, *(_DWORD *)v12, 0, v16, *(_DWORD *)(v12 + 8), 1);
              Rules_FreeTemplateSlotList(v12);
              g_DeftemplateSlotParseErrorFlag = 1;
              return 0;
            }
            else
            {
              return v12;
            }
          }
          else
          {
            Rules_FreeTemplateSlotList(v14);
            result = 0;
            g_DeftemplateSlotParseErrorFlag = 1;
          }
        }
        else
        {
          g_DeftemplateSlotParseErrorFlag = 1;
        }
      }
    }
    else
    {
      Parser_ReportSyntaxError();
      g_DeftemplateSlotParseErrorFlag = v13;
      return 0;
    }
  }
  else
  {
    Parser_ReportSyntaxError();
    g_DeftemplateSlotParseErrorFlag = 1;
    return 0;
  }
  return result;
}
// 4BC13B: variable 'v5' is possibly undefined
// 4BC15B: variable 'v8' is possibly undefined
// 4BC160: variable 'v9' is possibly undefined
// 4BC216: variable 'v6' is possibly undefined
// 4BC239: variable 'v13' is possibly undefined
// 4BC267: variable 'v11' is possibly undefined
// 4BC270: variable 'v14' is possibly undefined
// 4BC2B7: variable 'v16' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E874: using guessed type int dword_54E874;

//----- (004BC300) --------------------------------------------------------
int  Rules_ParseTemplateSlotAttributes(char *a1, int a2, int a3, int a4, double a5)
{
  _DWORD *v7; // ecx
  int *v8; // edx
  int v9; // eax
  int v10; // ebx
  int v11; // esi
  int v12; // eax
  int v13; // edx
  char v14; // al
  int v15; // edx
  int v16; // edx
  int v17; // ecx
  int v19; // ecx
  char v20; // al
  int v21; // eax
  int v22; // ecx
  int v23; // ecx
  char v24; // cl
  char v25; // dl
  int v26; // [esp+0h] [ebp-24h] BYREF
  int v27; // [esp+4h] [ebp-20h] BYREF
  __int16 v28; // [esp+8h] [ebp-1Ch] BYREF
  int v29; // [esp+Ch] [ebp-18h]
  int v30; // [esp+10h] [ebp-14h]
  int v31; // [esp+14h] [ebp-10h]

  v29 = a2;
  v31 = a4;
  v7 = *(_DWORD **)(g_ClipsMemoryTable + 80);
  v30 = 0;
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = (int)v7;
    *(_DWORD *)(g_ClipsMemoryTable + 80) = *v7;
    v8 = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
  }
  v9 = v29;
  v10 = v31;
  v8[3] = 0;
  v11 = (int)v8;
  *v8 = v9;
  v12 = Rules_CreateLHSParseNode();
  *(_DWORD *)(v13 + 8) = v12;
  if ( v10 )
    *(_BYTE *)(v12 + 1) |= 0x80u;
  v14 = v31;
  *(_BYTE *)(v11 + 4) &= ~1u;
  v15 = *(_DWORD *)(v11 + 4);
  *(_DWORD *)(v11 + 16) = 0;
  *(_DWORD *)(v11 + 4) = v14 & 1 | v15;
  *(_BYTE *)(v11 + 4) &= 0xF1u;
  Rules_ResetConstraintParsedFlags(&v28);
  Parser_NextToken((int)a1, v16);
  if ( *(_DWORD *)a3 == 101 )
    return v11;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50A27C);
    IO_OutWriteToken(*(char **)(a3 + 8));
    if ( *(_DWORD *)a3 != 100 || (Parser_NextToken((int)a1, a3), *(_DWORD *)a3 != 2) )
    {
      Parser_ReportSyntaxError();
      Rules_FreeTemplateSlotList(v11);
      g_DeftemplateSlotParseErrorFlag = 1;
      return 0;
    }
    if ( Rules_IsConstraintAttributeKeyword(*(_DWORD *)(*(_DWORD *)(a3 + 4) + 16)) )
    {
      if ( !Rules_ParseStandardConstraintAttribute(a1, *(const char **)(*(_DWORD *)(a3 + 4) + 16), &v28, *(_DWORD *)(v11 + 8), v31) )
      {
        g_DeftemplateSlotParseErrorFlag = 1;
        Rules_FreeTemplateSlotList(v11);
        return 0;
      }
      goto LABEL_10;
    }
    if ( strcmp_(v17, aDefault) && strcmp_(v19, aDefaultDynamic) )
    {
      Parser_ReportSyntaxError();
      Rules_FreeTemplateSlotList(v11);
      g_DeftemplateSlotParseErrorFlag = v22;
      return 0;
    }
    if ( v30 )
    {
      Rules_ReportAlreadyParsed(1, 0);
      g_DeftemplateSlotParseErrorFlag = v23;
      Rules_FreeTemplateSlotList(v11);
      return 0;
    }
    *(_BYTE *)(v11 + 4) &= ~2u;
    if ( !strcmp_(v19, aDefault) )
    {
      v20 = *(_BYTE *)(v11 + 4) | 4;
      *(_BYTE *)(v11 + 4) = v20;
      *(_BYTE *)(v11 + 4) = v20 & 0xF7;
    }
    else
    {
      v24 = *(_BYTE *)(v11 + 4) & 0xF3;
      *(_BYTE *)(v11 + 4) = v24;
      *(_BYTE *)(v11 + 4) = v24 | 8;
    }
    v21 = Rules_ParseDefaultAttribute((int)a1, v31, 1, *(_DWORD *)(v11 + 4) << 28 >> 31, a5, &v26, &v27, &g_DeftemplateSlotParseErrorFlag);
    if ( g_DeftemplateSlotParseErrorFlag == 1 )
      break;
    v30 = 1;
    if ( v27 )
    {
      *(_BYTE *)(v11 + 4) &= ~4u;
    }
    else if ( v26 )
    {
      v25 = *(_BYTE *)(v11 + 4) | 2;
      *(_BYTE *)(v11 + 4) = v25;
      *(_BYTE *)(v11 + 4) = v25 & 0xFB;
      *(_DWORD *)(v11 + 12) = v21;
      goto LABEL_10;
    }
    *(_DWORD *)(v11 + 12) = v21;
LABEL_10:
    Parser_NextToken((int)a1, a3);
    if ( *(_DWORD *)a3 == 101 )
      return v11;
  }
  Rules_FreeTemplateSlotList(v11);
  return 0;
}
// 4BC351: variable 'v13' is possibly undefined
// 4BC391: variable 'v16' is possibly undefined
// 4BC486: variable 'v17' is possibly undefined
// 4BC4AD: variable 'v19' is possibly undefined
// 4BC54E: variable 'v22' is possibly undefined
// 4BC570: variable 'v23' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E874: using guessed type int dword_54E874;

//----- (004BC5D0) --------------------------------------------------------
signed int  Rules_FetchPatternFieldRecord(int a1, _DWORD *a2)
{
  _DWORD *v3; // eax
  int v4; // ebx
  int v5; // edi
  __int16 *v6; // eax
  int v7; // ebp
  signed int result; // eax
  int v9; // ebx
  unsigned int v10; // edx
  int v11; // edi
  int v12; // eax
  __int16 *v13; // edi
  int v14[6]; // [esp+0h] [ebp-18h] BYREF

  v3 = *(_DWORD **)(a1 + 16);
  v4 = g_CurrentPatternFact;
  if ( (*(_BYTE *)v3 & 1) != 0 )
  {
    a2[1] = 6;
    result = 1;
    a2[2] = v4;
  }
  else
  {
    v5 = g_CurrentPatternFact + 54;
    if ( (*(_BYTE *)v3 & 2) != 0 )
    {
      v6 = (__int16 *)(v5 + 6 * (*v3 << 14 >> 24));
      a2[1] = *v6;
      v7 = a2[1];
      a2[2] = *(_DWORD *)(v6 + 1);
      if ( v7 == 4 )
      {
        a2[3] = 0;
        a2[4] = *(_DWORD *)(*(_DWORD *)(v6 + 1) + 6) - 1;
      }
      return 1;
    }
    else
    {
      v9 = *v3 << 14 >> 24;
      v10 = *v3 << 22;
      v14[0] = -1;
      v11 = 6 * v9 + v5;
      v12 = Rules_ComputeMultifieldSegmentOffset(g_ClipsFactMatchMarkerList, HIBYTE(v10), v14, v9);
      if ( v14[0] == -1 )
      {
        v13 = (__int16 *)(*(_DWORD *)(v11 + 2) + 14 + 6 * v12);
        a2[1] = *v13;
        a2[2] = *(_DWORD *)(v13 + 1);
      }
      else
      {
        a2[1] = 4;
        a2[2] = *(_DWORD *)(v11 + 2);
        a2[3] = v12;
        a2[4] = v14[0] + v12 - 1;
      }
      return 1;
    }
  }
  return result;
}
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (004BC6E0) --------------------------------------------------------
signed int  Rules_FetchPatternFieldSimple(int a1, int a2)
{
  uintptr_t payload; // eax
  uintptr_t descriptor; // eax

  if ( !a1 )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( !payload )
    return 1;
  descriptor = (uintptr_t)(unsigned int)g_CurrentPatternFact + 54 + 6 * (unsigned __int8)*(_DWORD *)payload;
  *(_DWORD *)(a2 + 4) = *(__int16 *)descriptor;
  *(_DWORD *)(a2 + 8) = *(_DWORD *)(descriptor + 2);
  return 1;
}
// 54E528: using guessed type int dword_54E528;

//----- (004BC720) --------------------------------------------------------
signed int  Rules_FetchPatternNestedFieldRecord(int a1, _DWORD *a2)
{
  uintptr_t payload; // eax
  unsigned int payload_word; // ebx
  uintptr_t descriptor; // edx
  uintptr_t vector_entry; // eax
  int index; // edx

  if ( !a1 || !a2 )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( !payload )
    return 1;
  payload_word = *(_DWORD *)payload;
  descriptor = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_CurrentPatternFact
                                                   + 6 * ((payload_word << 8) >> 24)
                                                   + 56);
  if ( (*(_BYTE *)payload & 1) != 0 && (*(_BYTE *)payload & 2) != 0 )
  {
    a2[1] = 4;
    a2[2] = descriptor;
    a2[3] = (payload_word << 23) >> 25;
    a2[4] = *(_DWORD *)(descriptor + 6) - (((payload_word << 16) >> 25) + 1);
  }
  else
  {
    if ( (*(_BYTE *)payload & 1) != 0 )
      index = (payload_word << 23) >> 25;
    else
      index = *(_DWORD *)(descriptor + 6) - (((payload_word << 16) >> 25) + 1);
    vector_entry = descriptor + 14 + 6 * index;
    a2[1] = *(__int16 *)vector_entry;
    a2[2] = *(_DWORD *)(vector_entry + 2);
  }
  return 1;
}
// 54E528: using guessed type int dword_54E528;

//----- (004BC7C0) --------------------------------------------------------
int  Rules_TestPatternFieldSimple(int a1)
{
  uintptr_t payload; // edx
  uintptr_t descriptor; // eax
  uintptr_t expression; // ecx

  if ( !a1 )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( !payload )
    return 1;
  descriptor = (uintptr_t)(unsigned int)g_CurrentPatternFact + 54 + 6 * (((unsigned int)*(_DWORD *)payload << 23) >> 24);
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( *(__int16 *)expression == *(__int16 *)descriptor && *(_DWORD *)(expression + 2) == *(_DWORD *)(descriptor + 2) )
    return *(_DWORD *)payload & 1;
  else
    return 1 - (*(_DWORD *)payload & 1);
}
// 51A960: using guessed type int dword_51A960;
// 54E528: using guessed type int dword_54E528;

//----- (004BC820) --------------------------------------------------------
int  Rules_TestPatternNestedField(int a1)
{
  uintptr_t payload; // edx
  uintptr_t descriptor; // eax
  uintptr_t vector; // eax
  unsigned int index; // ecx
  uintptr_t expression; // ecx

  if ( !a1 )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( !payload )
    return 1;
  descriptor = (uintptr_t)(unsigned int)g_CurrentPatternFact + 54 + 6 * (((unsigned int)*(_DWORD *)payload << 14) >> 24);
  if ( *(__int16 *)descriptor == 4 )
  {
    vector = (uintptr_t)(unsigned int)*(_DWORD *)(descriptor + 2);
    if ( (*(_BYTE *)payload & 2) != 0 )
      index = ((unsigned int)*(_DWORD *)payload << 22) >> 24;
    else
      index = *(_DWORD *)(vector + 6) - ((((unsigned int)*(_DWORD *)payload << 22) >> 24) + 1);
    descriptor = vector + 14 + 6 * index;
  }
  expression = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( *(__int16 *)expression == *(__int16 *)descriptor && *(_DWORD *)(expression + 2) == *(_DWORD *)(descriptor + 2) )
    return *(_DWORD *)payload & 1;
  else
    return 1 - (*(_DWORD *)payload & 1);
}
// 51A960: using guessed type int dword_51A960;
// 54E528: using guessed type int dword_54E528;

//----- (004BC8C0) --------------------------------------------------------
signed int  Rules_FetchJoinBindingFieldRecord(int a1, _DWORD *a2)
{
  _DWORD *v3; // eax
  int *v4; // ebp
  int v5; // edi
  int v6; // ebp
  int v7; // edx
  __int16 *v8; // eax
  int v9; // edi
  signed int result; // eax
  int v11; // edx
  int v12; // ebx
  int v13; // ecx
  _WORD *v14; // eax
  __int16 v15; // dx
  int v16; // eax
  _WORD *v17; // edx
  __int16 *v18; // eax
  int v19; // [esp+0h] [ebp-24h] BYREF
  int v20; // [esp+4h] [ebp-20h]
  int v21; // [esp+8h] [ebp-1Ch]
  _WORD *v22; // [esp+Ch] [ebp-18h]

  v3 = *(_DWORD **)(a1 + 16);
  if ( g_Rules_GlobalRHSBinds )
  {
    v11 = *v3 << 22 >> 24;
    if ( (*(_DWORD *)g_CurrentPatternEntityPtr << 16 >> 25) - 1 == v11 )
      v4 = *(int **)(g_Rules_GlobalRHSBinds + 8);
    else
      v4 = *(int **)(g_Clips_CurrentPartialMatch + 4 * v11 + 8);
  }
  else
  {
    v4 = *(int **)(g_Clips_CurrentPartialMatch + 4 * (*v3 << 22 >> 24) + 8);
  }
  v5 = *v4;
  v6 = v4[1];
  if ( (*(_BYTE *)v3 & 1) != 0 )
  {
    a2[1] = 6;
    result = 1;
    a2[2] = v5;
  }
  else
  {
    v7 = v5 + 54;
    if ( (*(_BYTE *)v3 & 2) != 0 )
    {
      v8 = (__int16 *)(v7 + 6 * (*v3 << 14 >> 24));
      a2[1] = *v8;
      v9 = a2[1];
      a2[2] = *(_DWORD *)(v8 + 1);
      if ( v9 == 4 )
      {
        a2[3] = 0;
        a2[4] = *(_DWORD *)(*(_DWORD *)(v8 + 1) + 6) - 1;
      }
      return 1;
    }
    else
    {
      v12 = *v3 << 14 >> 24;
      v13 = *v3 << 6 >> 24;
      v21 = 6 * v12;
      v14 = (_WORD *)(v7 + 6 * v12);
      v20 = v13;
      v15 = *v14;
      v22 = v14;
      if ( v15 == 4 )
      {
        v19 = -1;
        v16 = Rules_ComputeMultifieldSegmentOffset(v6, v20, &v19, v12);
        if ( v19 == -1 )
        {
          v18 = (__int16 *)(*(_DWORD *)(v21 + v5 + 56) + 14 + 6 * v16);
          a2[1] = *v18;
          a2[2] = *(_DWORD *)(v18 + 1);
        }
        else
        {
          v17 = v22;
          a2[1] = 4;
          a2[2] = *(_DWORD *)(v17 + 1);
          a2[3] = v16;
          a2[4] = v19 + v16 - 1;
        }
        return 1;
      }
      else
      {
        a2[1] = v15;
        a2[2] = *(_DWORD *)(v22 + 1);
        return 1;
      }
    }
  }
  return result;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCA70) --------------------------------------------------------
signed int  Rules_FetchJoinBindingFieldSimple(int a1, int a2)
{
  _DWORD *v3; // eax
  int v4; // edx
  _DWORD *v5; // edx
  int v6; // ebx
  int v7; // eax

  v3 = *(_DWORD **)(a1 + 16);
  if ( g_Rules_GlobalRHSBinds )
  {
    v4 = (unsigned __int8)*v3;
    if ( (*(_DWORD *)g_CurrentPatternEntityPtr << 16 >> 25) - 1 == v4 )
      v5 = *(_DWORD **)(g_Rules_GlobalRHSBinds + 8);
    else
      v5 = *(_DWORD **)(g_Clips_CurrentPartialMatch + 4 * v4 + 8);
  }
  else
  {
    v5 = *(_DWORD **)(g_Clips_CurrentPartialMatch + 4 * (unsigned __int8)*v3 + 8);
  }
  v6 = 6 * (*v3 << 16 >> 24);
  v7 = *v5 + 54;
  *(_DWORD *)(a2 + 4) = *(__int16 *)(v6 + v7);
  *(_DWORD *)(a2 + 8) = *(_DWORD *)(v6 + v7 + 2);
  return 1;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCB00) --------------------------------------------------------
signed int  Rules_FetchJoinBindingNestedField(int a1, _DWORD *a2)
{
  uintptr_t payload; // eax
  unsigned int bits; // ebx
  unsigned int fact_index; // ecx
  uintptr_t fact_cell; // esi
  uintptr_t fact_record; // esi
  uintptr_t multifield; // ecx
  unsigned int slot_index; // ecx
  uintptr_t slot_value; // eax

  if ( !a1 || !a2 )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  if ( !payload )
    return 1;
  bits = *(_DWORD *)payload;
  fact_index = (bits << 8) >> 24;
  if ( g_Rules_GlobalRHSBinds
    && (((unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)g_CurrentPatternEntityPtr << 16) >> 25) - 1 == fact_index )
  {
    fact_cell = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Rules_GlobalRHSBinds + 8);
  }
  else
  {
    fact_cell = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Clips_CurrentPartialMatch + 4 * fact_index + 8);
  }
  fact_record = (uintptr_t)(unsigned int)*(_DWORD *)fact_cell;
  multifield = (uintptr_t)(unsigned int)*(_DWORD *)(fact_record + 6 * (bits >> 24) + 56);
  if ( (bits & 1) != 0 && (bits & 2) != 0 )
  {
    a2[1] = 4;
    a2[2] = (int)multifield;
    a2[3] = (bits << 23) >> 25;
    a2[4] = *(_DWORD *)(multifield + 6) - (((bits << 16) >> 25) + 1);
    return 1;
  }
  if ( (bits & 1) != 0 )
    slot_index = (bits << 23) >> 25;
  else
    slot_index = *(_DWORD *)(multifield + 6) - (((bits << 16) >> 25) + 1);
  slot_value = multifield + 14 + 6 * slot_index;
  a2[1] = *(__int16 *)slot_value;
  a2[2] = *(_DWORD *)(slot_value + 2);
  return 1;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCBF0) --------------------------------------------------------
signed int  Rules_EvalMultifieldIndexInRange(int a1, uintptr_t a2)
{
  int v2; // esi
  int v3; // eax
  int i; // ecx
  int v5; // eax
  unsigned int v6; // ecx

  *(_DWORD *)(a2 + 4) = 2;
  *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  if ( !a1 )
  {
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
    return 1;
  }
  v2 = *(_DWORD *)(a1 + 16);
  v3 = g_ClipsFactMatchMarkerList;
  for ( i = 0; v3; v3 = *(_DWORD *)(v3 + 16) )
  {
    if ( *(_WORD *)(v3 + 4) == *(_DWORD *)v2 << 15 >> 24 )
      i += *(_DWORD *)(v3 + 12) - *(_DWORD *)(v3 + 8) + 1;
  }
  v5 = *(_DWORD *)(6 * (*(_DWORD *)v2 << 15 >> 24) + g_CurrentPatternFact + 56);
  v6 = (unsigned __int8)*(_DWORD *)v2 + i;
  if ( v6 > *(_DWORD *)(v5 + 6) || (*(_BYTE *)(v2 + 1) & 1) != 0 && v6 < *(_DWORD *)(v5 + 6) )
    return 0;
  *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  return 1;
}
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (004BCC90) --------------------------------------------------------
int  Rules_TestJoinBindingFieldsEqual(int a1)
{
  _DWORD *v1; // edx
  int v2; // ebx
  int v3; // ebx
  int v4; // esi
  int v5; // ebx

  v1 = *(_DWORD **)(a1 + 16);
  v2 = (*v1 << 15 >> 24) - 1;
  if ( (*(_DWORD *)g_CurrentPatternEntityPtr << 16 >> 25) - 1 == v2 )
    v3 = **(_DWORD **)(g_Rules_GlobalRHSBinds + 8);
  else
    v3 = **(_DWORD **)(g_Clips_CurrentPartialMatch + 4 * v2 + 8);
  v4 = 6 * (*v1 << 23 >> 25) + **(_DWORD **)(g_Rules_GlobalRHSBinds + 8);
  v5 = 6 * (*v1 << 8 >> 25) + v3;
  if ( *(__int16 *)(v4 + 54) == *(__int16 *)(v5 + 54) && *(_DWORD *)(v4 + 56) == *(_DWORD *)(v5 + 56) )
    return *v1 & 1;
  else
    return *v1 << 30 >> 31;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCD30) --------------------------------------------------------
int  Rules_TestJoinBindingFieldsEqualRanged(int a1)
{
  uintptr_t payload; // eax
  unsigned int bits; // eax
  unsigned int bits2; // eax
  int compare_index; // ebx
  int right_index; // ebp
  int left_index; // edi
  uintptr_t active_cell; // ecx
  uintptr_t left_base; // ecx
  uintptr_t right_base; // ebx
  uintptr_t left_descriptor; // ecx
  uintptr_t right_descriptor; // edx
  uintptr_t vector; // edx
  int vector_index; // esi

  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a1 + 16);
  bits = *(_DWORD *)payload;
  compare_index = (int)((bits << 7) >> 24) - 1;
  right_index = bits >> 25;
  left_index = (bits << 23) >> 25;
  active_cell = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Rules_GlobalRHSBinds + 8);
  left_base = (uintptr_t)(unsigned int)*(_DWORD *)active_cell;
  if ( (((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_CurrentPatternEntityPtr) << 16) >> 25) - 1 == compare_index )
  {
    right_base = left_base;
  }
  else
  {
    uintptr_t compare_cell =
      (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_Clips_CurrentPartialMatch + 4 * compare_index + 8);
    right_base = (uintptr_t)(unsigned int)*(_DWORD *)compare_cell;
  }
  left_descriptor = left_base + 6 * left_index + 54;
  if ( *(_WORD *)left_descriptor == 4 )
  {
    vector = (uintptr_t)(unsigned int)*(_DWORD *)(left_descriptor + 2);
    if ( (*(_BYTE *)(payload + 1) & 2) != 0 )
      vector_index = (bits << 15) >> 25;
    else
      vector_index = *(_DWORD *)(vector + 6) - (((bits << 15) >> 25) + 1);
    left_descriptor = vector + 14 + 6 * vector_index;
  }
  right_descriptor = right_base + 6 * right_index + 54;
  if ( *(_WORD *)right_descriptor == 4 )
  {
    vector = (uintptr_t)(unsigned int)*(_DWORD *)(right_descriptor + 2);
    bits2 = *(_DWORD *)(payload + 4);
    if ( (*(_BYTE *)(payload + 4) & 1) != 0 )
      vector_index = (bits2 << 24) >> 25;
    else
      vector_index = *(_DWORD *)(vector + 6) - (((bits2 << 24) >> 25) + 1);
    right_descriptor = vector + 14 + 6 * vector_index;
  }
  if ( *(__int16 *)left_descriptor == *(__int16 *)right_descriptor
    && *(_DWORD *)(left_descriptor + 2) == *(_DWORD *)(right_descriptor + 2) )
  {
    return bits & 1;
  }
  else
  {
    return (bits << 30) >> 31;
  }
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCE80) --------------------------------------------------------
int  Rules_EvalPatternFieldsEqual(int a1, int a2)
{
  _DWORD *v3; // edx
  __int16 *v4; // esi
  __int16 *v5; // eax
  int result; // eax

  v3 = *(_DWORD **)(a1 + 16);
  v4 = (__int16 *)(g_CurrentPatternFact + 54 + 6 * (*v3 << 23 >> 25));
  v5 = (__int16 *)(g_CurrentPatternFact + 54 + 6 * (*v3 << 16 >> 25));
  if ( *v4 == *v5 && *(_DWORD *)(v4 + 1) == *(_DWORD *)(v5 + 1) )
    result = *v3 & 1;
  else
    result = *v3 << 30 >> 31;
  *(_DWORD *)(a2 + 4) = 2;
  if ( result )
    *(_DWORD *)(a2 + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(a2 + 8) = g_ClipsFalseSymbol;
  return result;
}
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;
// 54E528: using guessed type int dword_54E528;

//----- (004BCF10) --------------------------------------------------------
int  Rules_ComputeMultifieldSegmentOffset(int a1, int a2, _DWORD *a3, int a4)
{
  int v5; // ecx

  v5 = a2;
  if ( !a1 )
    return v5;
  while ( 1 )
  {
    while ( *(__int16 *)(a1 + 4) != a4 )
    {
      a1 = *(_DWORD *)(a1 + 16);
      if ( !a1 )
        return v5;
    }
    if ( a2 == *(_DWORD *)a1 )
      break;
    if ( a2 < *(_DWORD *)a1 )
      return v5;
    v5 += *(_DWORD *)(a1 + 12) - *(_DWORD *)(a1 + 8);
    a1 = *(_DWORD *)(a1 + 16);
    if ( !a1 )
      return v5;
  }
  *a3 = *(_DWORD *)(a1 + 12) - *(_DWORD *)(a1 + 8) + 1;
  return v5;
}

//----- (004BCF60) --------------------------------------------------------
signed int  Rules_EvalCopyMultifieldBinding(int a1, _DWORD *a2, double a3)
{
  (void)a1;
  Rules_StoreEvaluatedNodesAsMultifield(a2, *(_DWORD *)(g_ClipsCurrentExpression + 6), 0, a3);
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (004BCF80) --------------------------------------------------------
int  Rules_RunIncrementalReset(int result, double a2)
{
  int v2; // ecx
  int i; // edx
  int v4; // edx
  int j; // edx

  if ( g_Rules_IncrementalResetEnabled )
  {
    Rules_ToggleJoinNetworkResetMark(result, 1);
    g_IncrementalResetInProgress = 1;
    for ( i = v2; i; i = *(_DWORD *)(v4 + 48) )
      Rules_DriveIncrementalResetForModule(i, a2);
    for ( j = g_PatternParserListHead; j; j = *(_DWORD *)(j + 92) )
    {
      if ( *(_DWORD *)(j + 76) )
        (*(void (**)(void))(j + 76))();
    }
    g_IncrementalResetInProgress = 0;
    return Rules_ToggleJoinNetworkResetMark(v2, 0);
  }
  return result;
}
// 4BCFA5: variable 'v2' is possibly undefined
// 4BCFB2: variable 'v4' is possibly undefined
// 4BCFD3: variable 'j' is possibly undefined
// 51B348: using guessed type int dword_51B348;
// 51B354: using guessed type int dword_51B354;
// 51B358: using guessed type int dword_51B358;

//----- (004BCFF0) --------------------------------------------------------
int  Rules_ToggleJoinNetworkResetMark(int result, char a2)
{
  int v2; // ebp
  int v3; // edi
  int v4; // ecx
  int v5; // edx

  v2 = result;
  if ( result )
  {
    v3 = 16 * (a2 & 1);
    do
    {
      v4 = *(_DWORD *)(v2 + 44);
      if ( v4 )
      {
        do
        {
          BYTE1(result) = *(_BYTE *)v4;
          if ( (*(_BYTE *)v4 & 0x10) != 0 && (result & 0x400) == 0 )
          {
            *(_BYTE *)v4 = BYTE1(result) & 0xEF;
            *(_DWORD *)v4 |= v3;
            result = Rules_RunConstructTypeIncrementalReset(*(_DWORD *)v4 << 23 >> 29, v4);
          }
          if ( (*(_BYTE *)v4 & 4) != 0 )
            v5 = *(_DWORD *)(v4 + 16);
          else
            v5 = *(_DWORD *)(v4 + 24);
          v4 = v5;
        }
        while ( v5 );
      }
      v2 = *(_DWORD *)(v2 + 48);
    }
    while ( v2 );
  }
  return result;
}
// 4BD037: variable 'v4' is possibly undefined

//----- (004BD060) --------------------------------------------------------
int  Rules_DriveIncrementalResetForModule(int result, double a2)
{
  int v2; // ebx
  int v3; // esi
  int v4; // eax
  bool v5; // zf
  int i; // ecx
  int v7; // ecx

  v2 = result;
  v3 = *(_DWORD *)(result + 44);
  if ( v3 )
  {
    do
    {
      while ( 1 )
      {
        if ( (*(_BYTE *)v3 & 0x10) != 0 )
        {
          if ( (*(_DWORD *)v3 & 1) == 1 )
          {
            v4 = (*(_BYTE *)v3 & 4) != 0 ? 0 : *(_DWORD *)(v3 + 16);
            v5 = (*(_BYTE *)(v4 + 12) & 8) == 0;
          }
          else
          {
            v5 = (**(_BYTE **)(v3 + 24) & 0x10) == 0;
          }
          if ( v5 )
            Rules_DriveIncrementalResetJoin((int *)v3, a2);
        }
        else if ( v2 == *(_DWORD *)(v3 + 36) )
        {
          for ( i = *(_DWORD *)(v3 + 8); i; i = *(_DWORD *)(v7 + 4) )
            Rules_AddActivation(v2, i, a2);
        }
        if ( (*(_BYTE *)v3 & 4) == 0 )
          break;
        result = *(_DWORD *)(v3 + 16);
        v3 = result;
        if ( !result )
          return result;
      }
      result = *(_DWORD *)(v3 + 24);
      v3 = result;
    }
    while ( result );
  }
  return result;
}
// 4BD0C5: variable 'v7' is possibly undefined

//----- (004BD0E0) --------------------------------------------------------
int * Rules_DriveIncrementalResetJoin(int *result, double a2)
{
  char *v2; // esi
  int *i; // ecx
  int v4; // ecx
  int *j; // ecx
  int v6; // ecx

  v2 = (char *)result;
  if ( (*result & 1) == 1 )
  {
    for ( i = *(int **)result[4]; i; i = *(int **)(v4 + 4) )
      result = Rules_DriveJoinNetwork(i, v2, 1, a2);
  }
  else if ( !result[2] )
  {
    for ( j = *(int **)(result[6] + 8); j; j = *(int **)(v6 + 4) )
      result = Rules_DriveJoinNetwork(j, v2, 0, a2);
  }
  return result;
}
// 4BD107: variable 'v4' is possibly undefined
// 4BD130: variable 'v6' is possibly undefined

//----- (004BD140) --------------------------------------------------------
int  Rules_RunConstructTypeIncrementalReset(int a1, int a2)
{
  int result; // eax

  result = Rules_GetPatternParserByTypeID(a1);
  if ( result )
  {
    if ( *(_DWORD *)(result + 72) )
      return (*(int (__cdecl **)(int))(result + 72))(a2);
  }
  return result;
}

//----- (004BD160) --------------------------------------------------------
int Rules_GetIncrementalReset()
{
  return g_Rules_IncrementalResetEnabled;
}
// 51B358: using guessed type int dword_51B358;

//----- (004BD170) --------------------------------------------------------
signed int Rules_SetIncrementalReset()
{
  int v0; // edx
  int v1; // ecx

  if ( Rules_GetNextDefrule(0) )
    return -1;
  g_Rules_IncrementalResetEnabled = v0;
  return v1;
}
// 4BD18D: variable 'v0' is possibly undefined
// 4BD193: variable 'v1' is possibly undefined
// 51B358: using guessed type int dword_51B358;

//----- (004BD1A0) --------------------------------------------------------
int  Rules_SetIncrementalResetCommand(int a1, double a2)
{
  int v3; // eax
  int v4; // ecx
  int v5; // esi
  int v7; // ecx
  int v8; // ecx
  _DWORD v9[10]; // [esp-4h] [ebp-28h] BYREF

  v9[8] = a1;
  v3 = Lexer_TokenExpect(1);
  v5 = v4;
  if ( v3 == -1 )
    return v4;
  if ( Rules_GetNextDefrule(0) )
  {
    Rules_PrintErrorID((int)aIncrrset, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheIncremental, v7);
    Lexer_ErrorRecover(1);
    return v8;
  }
  else
  {
    Rules_RtnUnknown(1, v9, a2);
    Rules_SetIncrementalReset();
    return v5;
  }
}
// 4BD1BE: variable 'v4' is possibly undefined
// 4BD227: variable 'v7' is possibly undefined
// 4BD236: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B358: using guessed type int dword_51B358;
// 54DD70: using guessed type int dword_54DD70;

//----- (004BD260) --------------------------------------------------------
int Rules_GetIncrementalResetCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  return v0;
}
// 4BD27A: variable 'v0' is possibly undefined
// 51B358: using guessed type int dword_51B358;

//----- (004BD280) --------------------------------------------------------
int  Parser_ParseRequiredFunctionCall(int a1, int a2)
{
  int v3; // ecx
  int token_buffer_ptr;
  _DWORD *token_buffer;
  int result;

  token_buffer_ptr = Compat_AllocLow32Bytes(20);
  if ( !token_buffer_ptr )
    return 0;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  token_buffer[4] = a2;
  Parser_NextToken(a1, token_buffer_ptr);
  if ( token_buffer[0] == 100 )
  {
    result = Parser_ParseExpression(v3, v3);
  }
  else
  {
    Parser_ReportSyntaxError();
    result = 0;
  }
  Compat_FreeLow32Bytes(token_buffer_ptr);
  return result;
}
// 4BD2A8: variable 'v3' is possibly undefined

//----- (004BD2C0) --------------------------------------------------------
int Parser_ParseExpression(a1, a2)
int a1;
int a2;
{
  int v3; // ecx
  int v4; // ecx
  int token_buffer_ptr;
  _DWORD *token_buffer;
  int result;
  int token_symbol;
  _BYTE *token_text;

  token_buffer_ptr = Compat_AllocLow32Bytes(20);
  if ( !token_buffer_ptr )
    return 0;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  token_buffer[4] = a2;
  Parser_NextToken(a1, token_buffer_ptr);
  if ( token_buffer[0] == 2 )
  {
    token_symbol = token_buffer[1];
    token_text = (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)token_symbol + 16);
    result = Parser_ParseFunctionCallExpr(v3, token_text);
  }
  else
  {
    Rules_PrintErrorID((int)aExprnpsr, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAFunctionNameM, v4);
    result = 0;
  }
  Compat_FreeLow32Bytes(token_buffer_ptr);
  return result;
}
// 4BD2F0: variable 'v4' is possibly undefined
// 4BD307: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BD320) --------------------------------------------------------
int  Parser_ParseFunctionCallExpr(int a1, _BYTE *a2)
{
  _BYTE *v4; // edx
  _BYTE *v5; // edx
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  __int16 v10; // ax
  _WORD *v11; // edi
  int v12; // ecx
  int v13; // esi
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int **v18; // eax
  int v19; // edx
  int v20; // ecx
  int **v21; // eax
  int v22; // ecx
  int v23; // eax
  int **Symbol; // [esp+4h] [ebp-18h]

  if ( Rules_FindModuleSeparator(a2) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  Symbol = Rules_MakeSymbol(v4);
  v6 = Defgeneric_LookupLocalOnly(v5);
  v7 = v6;
  if ( v8 || v6 || (v9 = Deffunction_LookupByName(a2)) == 0 )
  {
    if ( v7 )
    {
      v10 = 11;
    }
    else
    {
      v7 = (int)Symbol;
      if ( !Symbol )
      {
        Rules_PrintErrorID((int)aExprnpsr, 3, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMissingFunctio, v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a2, v16);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ParserError, v17);
        return 0;
      }
      v10 = 10;
    }
  }
  else
  {
    v7 = v9;
    v10 = 12;
  }
  v11 = (_WORD *)AST_NewNode(v10, v7);
  Parser_PushFunctionParseState();
  g_ClipsParseReturnContext = v12;
  g_ParserBreakContextFlag = v12;
  if ( *v11 == 10 && *(int **)((char *)Symbol + 13) )
  {
    v13 = (*(int (__fastcall **)(int **, int))((char *)Symbol + 13))(Symbol, a1);
    Parser_PopFunctionParseState();
    if ( !v13 )
      return 0;
    Rules_MakeSymbol(aExpand_0);
    v18 = Rules_MakeSymbol(aExpansionCal_0);
    if ( Parser_ParseExpansion(*(_DWORD *)(v13 + 6), v19, v20, (int)v18) )
      goto LABEL_29;
    return v13;
  }
  v13 = Parser_CollectFunctionArguments((int)v11, a1, v12);
  Parser_PopFunctionParseState();
  if ( !v13 )
    return 0;
  Rules_MakeSymbol(aExpand_0);
  v21 = Rules_MakeSymbol(aExpansionCal_0);
  if ( Parser_ParseExpansion(*(_DWORD *)(v13 + 6), v13, v22, (int)v21) )
    goto LABEL_29;
  if ( Rules_MakeSymbol(aExpansionCal_0) == *(int ***)(v13 + 2) )
    return v13;
  if ( *(_WORD *)v13 != 10 || !Rules_StaticConstraintCheckingEnabled() )
  {
    if ( *(_WORD *)v13 == 12 )
    {
      v23 = AST_CountListNodes(*(_DWORD *)(v13 + 6));
      if ( !Deffunction_CheckArgumentCount(*(_DWORD *)(v13 + 2), v23) )
        goto LABEL_29;
    }
    return v13;
  }
  if ( !Parser_ValidateFunctionCallArgs(v13, *(int *)((char *)Symbol + 17), (int)a2) )
    return v13;
LABEL_29:
  AST_Free(v13);
  return 0;
}
// 4BD33D: variable 'v4' is possibly undefined
// 4BD34A: variable 'v5' is possibly undefined
// 4BD353: variable 'v8' is possibly undefined
// 4BD36F: variable 'v7' is possibly undefined
// 4BD37D: variable 'v12' is possibly undefined
// 4BD401: variable 'v15' is possibly undefined
// 4BD40D: variable 'v16' is possibly undefined
// 4BD41C: variable 'v17' is possibly undefined
// 4BD465: variable 'v19' is possibly undefined
// 4BD465: variable 'v20' is possibly undefined
// 4BD4AE: variable 'v22' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BD540) --------------------------------------------------------
signed int  Parser_ParseExpansion(int a1, int a2, int a3, int a4)
{
  int v4; // esi
  signed int v7; // eax
  int v8; // edx
  _WORD *v9; // eax
  __int16 v10; // cx
  int v11; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx

  v4 = a1;
  if ( !a1 )
    return 0;
  while ( 1 )
  {
    if ( g_SequenceOperatorRecognition || *(_WORD *)v4 != 16 )
    {
      if ( *(_WORD *)v4 == 16 || *(_WORD *)v4 == 14 )
        goto LABEL_6;
    }
    else
    {
      *(_WORD *)v4 = 15;
    }
    if ( a3 != *(_DWORD *)(v4 + 2) )
      goto LABEL_13;
LABEL_6:
    if ( *(_WORD *)a2 == 10 && !*(_WORD *)(*(_DWORD *)(a2 + 2) + 23) )
      break;
    if ( *(_DWORD *)(a2 + 2) != a4 )
    {
      v7 = AST_NewNode(*(_WORD *)a2, *(_DWORD *)(a2 + 2));
      v8 = *(_DWORD *)(a2 + 6);
      *(_DWORD *)(v7 + 10) = 0;
      *(_DWORD *)(v7 + 6) = v8;
      *(_WORD *)a2 = 10;
      *(_DWORD *)(a2 + 2) = a4;
      *(_DWORD *)(a2 + 6) = v7;
    }
    if ( a3 != *(_DWORD *)(v4 + 2) )
    {
      v9 = (_WORD *)AST_NewNode(15, *(_DWORD *)(v4 + 2));
      if ( *(_WORD *)v4 == 14 )
        *v9 = 13;
      *(_WORD *)v4 = 10;
      *(_DWORD *)(v4 + 6) = v9;
      *(_DWORD *)(v4 + 2) = a3;
    }
LABEL_13:
    if ( *(_DWORD *)(v4 + 6) )
    {
      v10 = *(_WORD *)v4;
      if ( *(_WORD *)v4 == 11 || v10 == 12 || v10 == 10 )
        v11 = v4;
      else
        v11 = a2;
      if ( Parser_ParseExpansion(*(_DWORD *)(v4 + 6), v11, a3, a4) )
        return 1;
    }
    v4 = *(_DWORD *)(v4 + 10);
    if ( !v4 )
      return 0;
  }
  Rules_PrintErrorID((int)aExprnpsr, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSequenceOperat, v13);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(a2 + 2) + 16), v14);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ParserError, v15);
  return 1;
}
// 4BD667: variable 'v13' is possibly undefined
// 4BD679: variable 'v14' is possibly undefined
// 4BD688: variable 'v15' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B360: using guessed type int dword_51B360;

//----- (004BD6C0) --------------------------------------------------------
_DWORD *Parser_PushFunctionParseState()
{
  _DWORD *v0; // edx
  _DWORD *result; // eax

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( v0 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *v0;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = g_ClipsParseReturnContext;
  result[1] = g_ParserBreakContextFlag;
  result[2] = g_ClipsParseContextSaveStack;
  g_ClipsParseContextSaveStack = (int)result;
  return result;
}
// 51B35C: using guessed type int dword_51B35C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BD710) --------------------------------------------------------
int Parser_PopFunctionParseState()
{
  _DWORD *v0; // eax
  int result; // eax

  v0 = (_DWORD *)g_ClipsParseContextSaveStack;
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  g_ParserBreakContextFlag = *(_DWORD *)(g_ClipsParseContextSaveStack + 4);
  g_ClipsParseContextSaveStack = *(_DWORD *)(g_ClipsParseContextSaveStack + 8);
  g_ClipsMemFreeListTemp = (int)v0;
  *v0 = *(_DWORD *)(g_ClipsMemoryTable + 48);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 51B35C: using guessed type int dword_51B35C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BD750) --------------------------------------------------------
signed int  Parser_ValidateFunctionCallArgs(int a1, int a2, int a3)
{
  int v4; // ebp
  _BYTE *v6; // edx
  int v7; // ecx
  int v8; // ebx
  int v9; // edi
  int v10; // eax
  int v11; // ebx
  _BYTE *v12; // esi
  char v13; // cl
  char *v14; // eax
  char v16; // [esp+8h] [ebp-1Ch]

  v4 = 1;
  if ( !a2 )
    return 0;
  v7 = AST_CountListNodes(*(_DWORD *)(a1 + 6));
  if ( (IsTable[(unsigned __int8)(*v6 + 1)] & 0x20) != 0 )
  {
    v8 = atoi_(v7);
  }
  else
  {
    if ( *v6 != 42 )
      return 0;
    v8 = -1;
  }
  v16 = v6[1];
  v9 = 2;
  if ( (IsTable[(unsigned __int8)(v16 + 1)] & 0x20) == 0 )
  {
    if ( v16 == 42 )
    {
      v10 = 10000;
      goto LABEL_9;
    }
    return 0;
  }
  v10 = atoi_(v7);
LABEL_9:
  if ( v8 == v10 )
  {
    if ( v7 == v10 )
      goto LABEL_11;
LABEL_22:
    Rules_ExpectedCountError(a3, v8);
    return 1;
  }
  if ( v7 < v8 )
    goto LABEL_22;
  if ( v7 > v10 )
  {
    Rules_ExpectedCountError(a3, v10);
    return 1;
  }
LABEL_11:
  if ( v6[2] )
    v9 = 3;
  v11 = *(_DWORD *)(a1 + 6);
  if ( !v11 )
    return 0;
  v12 = &v6[v9];
  while ( 1 )
  {
    if ( *v12 )
    {
      ++v12;
      ++v9;
    }
    if ( Rules_ExpressionConstraintsCompatible((__int16 *)v11) )
      break;
    v11 = *(_DWORD *)(v11 + 10);
    ++v4;
    if ( !v11 )
      return 0;
  }
  v14 = Rules_GetArgTypeName(v13);
  Parser_ReportError(v4, (int)v14);
  return 1;
}
// 4BD789: variable 'v6' is possibly undefined
// 4BD7ED: variable 'v7' is possibly undefined
// 4BD8ED: variable 'v13' is possibly undefined
// 48523F: using guessed type int __thiscall unknown_libname_2(_DWORD);

//----- (004BD910) --------------------------------------------------------
int  Parser_CollectFunctionArguments(int a1, int a2, int a3)
{
  int v5; // edx
  int v6; // ecx
  signed int v7; // eax
  int v8; // ecx
  _DWORD v10[5]; // [esp+0h] [ebp-14h] BYREF

  v10[3] = a3;
  while ( 1 )
  {
    IO_OutWriteToken(asc_50A444);
    v10[0] = v5;
    v7 = Parser_ParseArgument(a2, v10, v6);
    if ( v10[0] == 1 )
    {
      AST_Free(a1);
      return 0;
    }
    if ( !v7 )
      break;
    if ( v8 )
      *(_DWORD *)(v8 + 10) = v7;
    else
      *(_DWORD *)(a1 + 6) = v7;
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50A448);
  return a1;
}
// 4BD929: variable 'v5' is possibly undefined
// 4BD930: variable 'v6' is possibly undefined
// 4BD945: variable 'v8' is possibly undefined

//----- (004BD980) --------------------------------------------------------
signed int  Parser_ParseArgument(int a1, _DWORD *a2, int a3)
{
  int v4; // ecx
  signed int result; // eax
  int v6; // ecx
  _DWORD v7[5]; // [esp+0h] [ebp-14h] BYREF

  v7[4] = a3;
  Parser_NextToken(a1, (int)v7);
  if ( v7[0] == 101 )
    return 0;
  if ( v7[0] == 15 || v7[0] == 16 || v7[0] == 2 || v7[0] == 3 || v7[0] == 13 || v7[0] == 14 || v7[0] == 8 || v7[0] < 2u )
    return AST_NewNode(v7[0], v7[1]);
  if ( v7[0] == 100 )
  {
    result = Parser_ParseExpression(v4, 100, v4);
    if ( !result )
      *a2 = 1;
  }
  else
  {
    Rules_PrintErrorID((int)aExprnpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAConst, v6);
    *a2 = 1;
    return 0;
  }
  return result;
}
// 4BD9BD: simplified comparisons for '%var_14.4': ==0 || ==1 became <2u
// 4BD9CB: variable 'v4' is possibly undefined
// 4BDA15: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDA30) --------------------------------------------------------
int  Parser_ParseSingleExpression(int a1, __int16 *a2, int a3)
{
  int v3; // ecx
  __int16 *v4; // ebx
  unsigned int v5; // edx
  int v6; // edx
  int result; // eax
  int v8; // ecx
  _DWORD v9[5]; // [esp-10h] [ebp-14h] BYREF

  v9[3] = a3;
  v3 = a1;
  v4 = a2;
  if ( !a2 )
  {
    v4 = (__int16 *)v9;
    Parser_NextToken(a1, (int)v9);
  }
  v5 = *(_DWORD *)v4;
  if ( *(_DWORD *)v4 == 2 || v5 == 3 || v5 < 2 || v5 == 8 || v5 == 13 || v5 == 14 || v5 == 15 || v5 == 16 )
    return AST_NewNode(*(_DWORD *)v4, *((_DWORD *)v4 + 1));
  if ( v5 != 100 )
  {
    Rules_PrintErrorID((int)aExprnpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAConst, v8);
    return 0;
  }
  result = Parser_ParseExpression(v3, v3);
  v6 = result;
  if ( result )
    return v6;
  return result;
}
// 4BDA6B: simplified comparisons for 'edx.4': ==1 || ==0 became <2u
// 4BDA91: variable 'v3' is possibly undefined
// 4BDAC0: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDAD0) --------------------------------------------------------
int  Parser_ParseProgram(int a1, unsigned int *a2, signed int a3)
{
  int **Symbol; // eax
  signed int v7; // ebx
  int v8; // ecx
  unsigned int v9; // eax
  signed int v10; // eax
  int v11; // edx
  int v12; // ecx
  int **v14; // ebx
  int v15; // edx
  int v16; // ecx
  signed int v17; // [esp+0h] [ebp-10h]

  Symbol = Rules_MakeSymbol(aProgn_2);
  v7 = 0;
  v17 = AST_NewNode(10, (int)Symbol);
  while ( 1 )
  {
    if ( a3 )
      Parser_NextToken(a1, (int)a2);
    else
      a3 = 1;
    if ( *a2 == 2 && v8 && !strcmp_(v8, v8) )
      return v17;
    v9 = *a2;
    if ( *a2 == 2 || v9 == 3 || v9 < 2 || v9 == 13 || v9 == 14 || v9 == 8 || v9 == 15 || v9 == 16 )
    {
      v10 = AST_NewNode(*a2, a2[1]);
      goto LABEL_10;
    }
    if ( v9 != 100 )
      break;
    v10 = Parser_ParseExpression(a1, v8);
LABEL_10:
    if ( !v10 )
    {
      *a2 = 103;
      AST_Free(v17);
      return 0;
    }
    if ( v7 )
    {
      *(_DWORD *)(v7 + 10) = v10;
      v7 = v10;
      AST_Append(v12, v11);
    }
    else
    {
      *(_DWORD *)(v17 + 6) = v10;
      v7 = v10;
      AST_Append(v12, v17);
    }
  }
  Rules_MakeSymbol(aExpand_0);
  v14 = Rules_MakeSymbol(aExpansionCal_0);
  if ( !Parser_ParseExpansion(v17, v15, v16, (int)v14) )
    return v17;
  AST_Free(v17);
  return 0;
}
// 4BDB67: simplified comparisons for 'eax.4': ==1 || ==0 became <2u
// 4BDB07: variable 'v8' is possibly undefined
// 4BDB48: variable 'v12' is possibly undefined
// 4BDBB1: variable 'v15' is possibly undefined
// 4BDBB1: variable 'v16' is possibly undefined
// 4BDBE7: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004BDC10) --------------------------------------------------------
int Parser_GetSequenceOperatorRecognition()
{
  return g_SequenceOperatorRecognition;
}
// 51B360: using guessed type int dword_51B360;

//----- (004BDC20) --------------------------------------------------------
const char * Parser_ParseCLIPSFunctionArgString(const char *result, _DWORD *a2)
{
  signed int v3; // esi
  signed int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD v10[8]; // [esp+0h] [ebp-20h] BYREF

  v3 = 0;
  *a2 = 0;
  if ( result )
  {
    if ( IO_OpenStringSource((int)aClipsfnxargs, result, 0) )
    {
      Parser_NextToken((int)aClipsfnxargs, (int)v10);
      if ( v10[0] == 102 )
      {
LABEL_11:
        IO_CloseStringRouter((int)aClipsfnxargs);
        return (const char *)v6;
      }
      else
      {
        while ( v10[0] == 2 || v10[0] == 3 || v10[0] < 2u || v10[0] == 8 )
        {
          v4 = AST_NewNode(v10[0], v10[1]);
          if ( v5 )
            *(_DWORD *)(v3 + 10) = v4;
          v3 = v4;
          Parser_NextToken((int)aClipsfnxargs, (int)v10);
          if ( v10[0] == 102 )
            goto LABEL_11;
        }
        Rules_PrintErrorID((int)aExprnpsr, 7, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOnlyConstantAr, v8);
        AST_Free(v9);
        *a2 = 1;
        IO_CloseStringRouter((int)aClipsfnxargs);
        return 0;
      }
    }
    else
    {
      Rules_PrintErrorID((int)aExprnpsr, 6, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotReadArgu, v7);
      *a2 = 1;
      return 0;
    }
  }
  return result;
}
// 4BDC73: simplified comparisons for '%var_20.4': ==0 || ==1 became <2u
// 4BDC8F: variable 'v5' is possibly undefined
// 4BDCB2: variable 'v6' is possibly undefined
// 4BDCD8: variable 'v7' is possibly undefined
// 4BDD09: variable 'v8' is possibly undefined
// 4BDD10: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDC00) --------------------------------------------------------
int Parser_SetSequenceOperatorRecognition(int value)
{
  int previous_value; // eax

  previous_value = g_SequenceOperatorRecognition;
  g_SequenceOperatorRecognition = value;
  return previous_value;
}
// 51B360: using guessed type int dword_51B360;

//----- (004BDD20) --------------------------------------------------------
signed int Parser_AddFunctionParser(_BYTE *function_name, int handler)
{
  int **symbol; // eax
  int v3; // ecx

  symbol = Rules_MakeSymbol(function_name);
  if ( symbol )
  {
    *(int **)((char *)symbol + 17) = 0;
    *(_WORD *)((char *)symbol + 21) = 0;
    *(int **)((char *)symbol + 13) = (int *)handler;
    return 1;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionParser, v3);
  return 0;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004BDD40) --------------------------------------------------------
int Parser_RegisterProceduralFunctionParsers()
{
  if ( !Parser_AddFunctionParser(aBind, (int)Parser_ParseBind) )
    return 0;
  if ( !Parser_AddFunctionParser(aProgn, (int)Parser_ParseProgn) )
    return 0;
  if ( !Parser_AddFunctionParser(aIf, (int)Parser_ParseIf) )
    return 0;
  if ( !Parser_AddFunctionParser(aWhile, (int)Parser_ParseWhile) )
    return 0;
  if ( !Parser_AddFunctionParser(aLoopForCount, (int)Parser_ParseLoopForCount) )
    return 0;
  if ( !Parser_AddFunctionParser(aReturn, (int)Parser_ParseReturn) )
    return 0;
  if ( !Parser_AddFunctionParser(aBreak, (int)Parser_ParseBreak) )
    return 0;
  return Parser_AddFunctionParser(aSwitch, (int)Parser_ParseSwitch);
}

//----- (004BDDC0) --------------------------------------------------------
int Parser_GetLoopContextStack()
{
  return g_ClipsLoopContextStackTop;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BDDD0) --------------------------------------------------------
int  Parser_SetLoopContextStack(int result)
{
  g_ClipsLoopContextStackTop = result;
  return result;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BDDE0) --------------------------------------------------------
int Parser_FreeLoopContextStack()
{
  int result; // eax
  int v1; // edx

  if ( g_ClipsLoopContextStackTop )
  {
    do
    {
      AST_DecrementNodeRefCount(*(_DWORD **)(g_ClipsLoopContextStackTop + 4));
      g_ClipsMemFreeListTemp = g_ClipsLoopContextStackTop;
      *(_DWORD *)g_ClipsLoopContextStackTop = *(_DWORD *)(g_ClipsMemoryTable + 48);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      g_ClipsLoopContextStackTop = v1;
    }
    while ( v1 );
  }
  return result;
}
// 4BDE23: variable 'v1' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E880: using guessed type int dword_54E880;

//----- (004BDE40) --------------------------------------------------------
BOOL Parser_LoopContextStackIsEmpty()
{
  return g_ClipsLoopContextStackTop == 0;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BDE50) --------------------------------------------------------
int  Parser_ParseWhile(int a1, int a2)
{
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  signed int v9; // ebx
  int v11; // edx
  int v12; // ecx
  unsigned int v13; // [esp+0h] [ebp-20h] BYREF
  char *v14; // [esp+8h] [ebp-18h]

  IO_OutWriteToken(asc_50A54C);
  v5 = Parser_ParseSingleExpression(a2, 0, v4);
  *(_DWORD *)(a1 + 6) = v5;
  if ( !v5 )
    goto LABEL_10;
  Parser_NextToken(a2, (int)&v13);
  if ( v13 == 2 && !strcmp_(v6, aDo) )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50A54C);
    IO_OutWriteToken(v14);
    v9 = 1;
    Rules_IncrementIndentDepth(3);
    AST_Append(v12, v11);
  }
  else
  {
    if ( v13 != 100 )
    {
LABEL_9:
      Parser_ReportSyntaxError();
LABEL_10:
      AST_Free(a1);
      return 0;
    }
    IO_OutNewline();
    Rules_IncrementIndentDepth(3);
    AST_Append(v8, v7);
    v9 = 0;
    IO_OutWriteToken(v14);
  }
  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
    g_ClipsParseReturnContext = 1;
  g_ParserBreakContextFlag = 1;
  *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = Parser_ParseProgram(a2, &v13, v9);
  if ( !*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) )
    goto LABEL_10;
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(v14);
  if ( v13 != 101 )
    goto LABEL_9;
  Rules_DecrementIndentDepth(3);
  return a1;
}
// 4BDE6A: variable 'v4' is possibly undefined
// 4BDEA2: variable 'v8' is possibly undefined
// 4BDEA2: variable 'v7' is possibly undefined
// 4BDF2A: variable 'v6' is possibly undefined
// 4BDF5E: variable 'v12' is possibly undefined
// 4BDF5E: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BDF80) --------------------------------------------------------
int  Parser_ParseLoopForCount(int a1, int a2)
{
  int v4; // edx
  int v5; // esi
  int *v6; // eax
  int v7; // ecx
  int v8; // ecx
  signed int v9; // ebx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int *v14; // eax
  int v16; // ecx
  __int16 *v17; // eax
  int v18; // edx
  int v19; // ecx
  int *v20; // eax
  signed int v21; // eax
  int v22; // edx
  int v23; // ecx
  int v24; // ecx
  unsigned int v25; // [esp+0h] [ebp-28h] BYREF
  int v26; // [esp+4h] [ebp-24h]
  char *v27; // [esp+8h] [ebp-20h]
  int v28; // [esp+Ch] [ebp-1Ch]
  int v29; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_50A54C);
  Parser_NextToken(a2, v4);
  v5 = 0;
  if ( v25 == 100 )
  {
    Parser_NextToken(a2, (int)&v25);
    if ( v25 == 15 )
    {
      v5 = v26;
      IO_OutWriteToken(asc_50A54C);
      v17 = (__int16 *)Parser_ParseSingleExpression(a2, 0, v16);
      *(_DWORD *)(a1 + 6) = v17;
      if ( !v17 )
        goto LABEL_23;
      if ( Rules_ExpressionConstraintsCompatible(v17) )
        goto LABEL_18;
      IO_OutWriteToken(asc_50A54C);
      Parser_NextToken(a2, v18);
      if ( v25 == 101 )
      {
        IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(v27);
        v20 = Rules_AddIntegerValue(1);
        v21 = AST_NewNode(1, (int)v20);
        *(_DWORD *)(v21 + 10) = *(_DWORD *)(a1 + 6);
        *(_DWORD *)(a1 + 6) = v21;
      }
      else
      {
        *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = Parser_ParseSingleExpression(a2, (__int16 *)&v25, v19);
        if ( !*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) )
          goto LABEL_23;
        Parser_NextToken(a2, (int)&v25);
        if ( v25 != 101 )
          goto LABEL_18;
      }
      IO_OutWriteToken(asc_50A54C);
      goto LABEL_3;
    }
    if ( v25 != 2 )
      goto LABEL_18;
    v14 = Rules_AddIntegerValue(1);
    *(_DWORD *)(a1 + 6) = AST_NewNode(1, (int)v14);
    *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = Parser_ParseFunctionCallExpr(a2, *(_BYTE **)(v26 + 16));
    if ( *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) )
      goto LABEL_3;
LABEL_23:
    AST_Free(a1);
    return 0;
  }
  v6 = Rules_AddIntegerValue(1);
  *(_DWORD *)(a1 + 6) = AST_NewNode(1, (int)v6);
  *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = Parser_ParseSingleExpression(a2, (__int16 *)&v25, v7);
  if ( !*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) )
    goto LABEL_23;
LABEL_3:
  if ( Rules_ExpressionConstraintsCompatible(*(__int16 **)(*(_DWORD *)(a1 + 6) + 10)) )
    goto LABEL_18;
  Parser_NextToken(a2, (int)&v25);
  if ( v25 == 2 && !strcmp_(v8, aDo) )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50A54C);
    IO_OutWriteToken(v27);
    v9 = 1;
    Rules_IncrementIndentDepth(3);
    AST_Append(v11, v10);
    goto LABEL_7;
  }
  if ( v25 != 100 )
  {
LABEL_18:
    Parser_ReportSyntaxError();
    goto LABEL_23;
  }
  IO_OutNewline();
  Rules_IncrementIndentDepth(3);
  AST_Append(v23, v22);
  v9 = 0;
  IO_OutWriteToken(v27);
LABEL_7:
  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
    g_ClipsParseReturnContext = 1;
  g_ParserBreakContextFlag = 1;
  v28 = g_ClipsLoopContextStackTop;
  v29 = g_ClipsLoopContextStackTop;
  g_ClipsLoopContextStackTop = 0;
  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) + 10) = Parser_ParseProgram(a2, &v25, v9);
  if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) + 10) )
  {
    g_ClipsLoopContextStackTop = v28;
    AST_Free(a1);
    return 0;
  }
  v12 = 0;
  v13 = g_ClipsLoopContextStackTop;
  if ( !g_ClipsLoopContextStackTop )
  {
LABEL_13:
    if ( v12 )
      *(_DWORD *)(v12 + 8) = v29;
    else
      g_ClipsLoopContextStackTop = v29;
    if ( v5 )
      Parser_ReplaceLoopCountVars(v5, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) + 10), 0);
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(v27);
    if ( v25 == 101 )
    {
      Rules_DecrementIndentDepth(3);
      return a1;
    }
    goto LABEL_18;
  }
  while ( !v5 || strcmp_(v13, *(_DWORD *)(v5 + 16)) )
  {
    v12 = v13;
    v13 = *(_DWORD *)(v13 + 8);
    if ( !v13 )
      goto LABEL_13;
  }
  Parser_FreeLoopContextStack();
  g_ClipsLoopContextStackTop = v29;
  Rules_PrintErrorID((int)aPrcdrpsr, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRebindLo, v24);
  AST_Free(a1);
  return 0;
}
// 4BDF9A: variable 'v4' is possibly undefined
// 4BDFCA: variable 'v7' is possibly undefined
// 4BE019: variable 'v8' is possibly undefined
// 4BE04D: variable 'v11' is possibly undefined
// 4BE04D: variable 'v10' is possibly undefined
// 4BE0BD: variable 'v13' is possibly undefined
// 4BE19A: variable 'v16' is possibly undefined
// 4BE1CA: variable 'v18' is possibly undefined
// 4BE21A: variable 'v19' is possibly undefined
// 4BE25F: variable 'v23' is possibly undefined
// 4BE25F: variable 'v22' is possibly undefined
// 4BE2D5: variable 'v24' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;
// 54E880: using guessed type int dword_54E880;

//----- (004BE310) --------------------------------------------------------
int  Parser_ReplaceLoopCountVars(int result, int a2, signed int a3)
{
  int v3; // esi
  int v4; // ecx
  signed int v6; // ebp
  signed int v7; // ebx
  int **Symbol; // eax
  int v9; // ecx
  int *v10; // eax
  int **v11; // eax

  v3 = result;
  v4 = a2;
  if ( a2 )
  {
    v6 = a3 + 1;
    do
    {
      if ( *(_WORD *)v4 == 15 && (result = strcmp_(v4, *(_DWORD *)(v3 + 16)) == 0) != 0 )
      {
        *(_WORD *)v4 = 10;
        Symbol = Rules_MakeSymbol(aGetLoopCount_0);
        *(_DWORD *)(v9 + 2) = Symbol;
        v10 = Rules_AddIntegerValue(a3);
        result = AST_NewNode(1, (int)v10);
        *(_DWORD *)(v4 + 6) = result;
      }
      else if ( *(_DWORD *)(v4 + 6) )
      {
        if ( *(_WORD *)v4 == 10 && (v11 = Rules_MakeSymbol(aLoopForCount_0), v11 == *(int ***)(v4 + 2)) )
          v7 = v6;
        else
          v7 = a3;
        result = Parser_ReplaceLoopCountVars(v3, *(_DWORD *)(v4 + 6), v7);
      }
      v4 = *(_DWORD *)(v4 + 10);
    }
    while ( v4 );
  }
  return result;
}
// 4BE327: variable 'v4' is possibly undefined
// 4BE374: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004BE3B0) --------------------------------------------------------
int  Parser_ParseIf(int a1, int a2)
{
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  unsigned int v16[8]; // [esp+0h] [ebp-20h] BYREF

  IO_OutWriteToken(asc_50A54C);
  v5 = Parser_ParseSingleExpression(a2, 0, v4);
  *(_DWORD *)(a1 + 6) = v5;
  if ( !v5 )
    goto LABEL_15;
  Rules_IncrementIndentDepth(3);
  AST_Append(v7, v6);
  Parser_NextToken(a2, v8);
  if ( v16[0] != 2 || strcmp_(v9, aThen) )
    goto LABEL_14;
  AST_Append(v11, v10);
  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
    g_ClipsParseReturnContext = 1;
  if ( *(_DWORD *)(g_ClipsParseContextSaveStack + 4) == 1 )
    g_ParserBreakContextFlag = 1;
  *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = Parser_ParseProgram(a2, v16, 1);
  if ( !*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) )
    goto LABEL_15;
  if ( v16[0] == 101 )
  {
    Rules_DecrementIndentDepth(3);
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken((char *)v16[2]);
    return a1;
  }
  else
  {
    if ( v16[0] != 2 || strcmp_(v12, aElse_0) )
      goto LABEL_14;
    AST_Append(v14, v13);
    *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) + 10) = Parser_ParseProgram(a2, v16, 1);
    if ( !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) + 10) )
    {
LABEL_15:
      AST_Free(a1);
      return 0;
    }
    if ( v16[0] != 101 )
    {
LABEL_14:
      Parser_ReportSyntaxError();
      goto LABEL_15;
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50A5F4);
    Rules_DecrementIndentDepth(3);
    return a1;
  }
}
// 4BE3CA: variable 'v4' is possibly undefined
// 4BE3E6: variable 'v7' is possibly undefined
// 4BE3E6: variable 'v6' is possibly undefined
// 4BE3ED: variable 'v8' is possibly undefined
// 4BE408: variable 'v9' is possibly undefined
// 4BE415: variable 'v11' is possibly undefined
// 4BE415: variable 'v10' is possibly undefined
// 4BE47A: variable 'v12' is possibly undefined
// 4BE483: variable 'v14' is possibly undefined
// 4BE483: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BE520) --------------------------------------------------------
int  Parser_ParseProgn(int a1, int a2)
{
  int v3; // edx
  int v4; // ecx
  unsigned int *v5; // edx
  int v6; // edx
  char *v8; // [esp+0h] [ebp-10h]

  AST_Free(a1);
  g_ParserBreakContextFlag = *(_DWORD *)(g_ClipsParseContextSaveStack + 4);
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  Rules_IncrementIndentDepth(3);
  AST_Append(v4, v3);
  Parser_ParseProgram(a2, v5, 1);
  Rules_DecrementIndentDepth(3);
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(v8);
  return v6;
}
// 4BE555: variable 'v4' is possibly undefined
// 4BE555: variable 'v3' is possibly undefined
// 4BE55C: variable 'v5' is possibly undefined
// 4BE57B: variable 'v8' is possibly undefined
// 4BE580: variable 'v6' is possibly undefined
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BE590) --------------------------------------------------------
int  Parser_ParseBind(int a1, int a2)
{
  int v4; // edx
  _BYTE *v5; // ebp
  int v6; // edx
  _DWORD *v7; // ebx
  signed int v8; // ecx
  _DWORD *v9; // ecx
  int v10; // eax
  int v12; // [esp+0h] [ebp-28h]
  int v13; // [esp+4h] [ebp-24h]
  int v14; // [esp+Ch] [ebp-1Ch] BYREF
  int v15; // [esp+10h] [ebp-18h]

  IO_OutWriteToken(asc_50A54C);
  Parser_NextToken(a2, v4);
  v5 = 0;
  if ( v12 != 15 && v12 != 13 && (v12 != 16 || g_SequenceOperatorRecognition) )
  {
    Parser_ReportSyntaxError();
    AST_Free(a1);
    return 0;
  }
  *(_DWORD *)(a1 + 6) = AST_NewNode(2, v13);
  v15 = v13;
  if ( v12 == 13 && (v6 = Rules_FindImportExportConstruct(aDefglobal_4, &v14, *(_BYTE **)(v13 + 16), 1, 0)) != 0 )
  {
    **(_WORD **)(a1 + 6) = 60;
    *(_DWORD *)(*(_DWORD *)(a1 + 6) + 2) = v6;
  }
  else if ( v12 == 13 )
  {
    Defglobal_PrintUndefinedVariableError();
LABEL_19:
    AST_Free(a1);
    return 0;
  }
  v7 = *(_DWORD **)(g_ClipsMemoryTable + 56);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
    *(_DWORD *)(g_ClipsMemoryTable + 56) = *v7;
    v8 = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = Mem_HeapAllocWithRetry((_DWORD *)0xE);
  }
  *(_DWORD *)(v8 + 10) = 0;
  *(_DWORD *)(v8 + 6) = *(_DWORD *)(v8 + 10);
  if ( !Parser_CollectFunctionArguments(v8, a2, v8) )
    goto LABEL_19;
  *(_DWORD *)(*(_DWORD *)(a1 + 6) + 10) = *(_DWORD *)((char *)v9 + 6);
  g_ClipsMemFreeListTemp = (int)v9;
  *v9 = *(_DWORD *)(g_ClipsMemoryTable + 56);
  *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
  v10 = *(_DWORD *)(a1 + 6);
  if ( *(_WORD *)v10 != 60 )
  {
    if ( *(_DWORD *)(v10 + 10) )
      v5 = Rules_BuildLHSNodeFromToken(*(__int16 **)(v10 + 10));
    Rules_PushNamedContextEntry(v15, v5);
  }
  return a1;
}
// 4BE5AA: variable 'v4' is possibly undefined
// 4BE5B7: variable 'v12' is possibly undefined
// 4BE5DD: variable 'v13' is possibly undefined
// 4BE66D: variable 'v9' is possibly undefined
// 51B360: using guessed type int dword_51B360;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004BE720) --------------------------------------------------------
int __fastcall Parser_ParseReturn(int a1, int a2)
{
  _DWORD *v3; // edx
  int v4; // ecx
  signed int v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  int v13; // [esp+0h] [ebp-1Ch]

  if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
  {
    g_ClipsParseReturnContext = 1;
  }
  else if ( !g_ClipsParseReturnContext )
  {
    Rules_PrintErrorID((int)aPrcdrpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheReturnFunct, v9);
    AST_Free(v10);
    return 0;
  }
  g_ClipsParseReturnContext = 0;
  IO_OutWriteToken(asc_50A54C);
  v5 = Parser_ParseArgument(a2, v3, v4);
  *(_DWORD *)(v6 + 6) = v5;
  if ( !v5 || (IO_OutWriteToken(asc_50A54C), Parser_NextToken(a2, v11), v13 == 101) )
  {
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50A5F4);
    return v7;
  }
  else
  {
    Parser_ReportSyntaxError();
    AST_Free(v12);
    return 0;
  }
}
// 4BE769: conditional instruction was optimized away because %var_10.4==0
// 4BE75C: variable 'v3' is possibly undefined
// 4BE75C: variable 'v4' is possibly undefined
// 4BE761: variable 'v6' is possibly undefined
// 4BE783: variable 'v7' is possibly undefined
// 4BE7B2: variable 'v9' is possibly undefined
// 4BE7B9: variable 'v10' is possibly undefined
// 4BE7D0: variable 'v11' is possibly undefined
// 4BE7D9: variable 'v13' is possibly undefined
// 4BE7E7: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BE800) --------------------------------------------------------
int __fastcall Parser_ParseBreak(int a1, int a2)
{
  int v3; // edx
  int v4; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // [esp+0h] [ebp-14h]

  if ( !*(_DWORD *)(g_ClipsParseContextSaveStack + 4) )
  {
    Rules_PrintErrorID((int)aPrcdrpsr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheBreakFuncti, v6);
    goto LABEL_4;
  }
  IO_OutWriteToken(asc_50A54C);
  Parser_NextToken(a2, v3);
  if ( v8 != 101 )
  {
    Parser_ReportSyntaxError();
LABEL_4:
    AST_Free(v4);
    return 0;
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50A5F4);
  return v7;
}
// 4BE822: variable 'v3' is possibly undefined
// 4BE82B: variable 'v8' is possibly undefined
// 4BE839: variable 'v4' is possibly undefined
// 4BE864: variable 'v6' is possibly undefined
// 4BE87F: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;

//----- (004BE890) --------------------------------------------------------
int  Parser_ParseSwitch(int a1, int a2)
{
  int v3; // ebp
  __int16 *v4; // edx
  int v5; // ecx
  int v6; // esi
  int v7; // edx
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  __int16 *v12; // ecx
  __int16 *v13; // eax
  int v14; // ecx
  int v15; // esi
  int v16; // edx
  int v17; // ecx
  unsigned int *v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  int v23; // [esp+0h] [ebp-28h] BYREF
  char *v24; // [esp+8h] [ebp-20h]
  int v25; // [esp+Ch] [ebp-1Ch]
  int v26; // [esp+10h] [ebp-18h]

  v25 = a1;
  Rules_IncrementIndentDepth(3);
  IO_OutWriteToken(asc_50A54C);
  v3 = 0;
  v26 = 0;
  v6 = Parser_ParseSingleExpression(a2, v4, v5);
  *(_DWORD *)(v25 + 6) = v6;
  if ( !v6 )
    goto LABEL_5;
  Parser_NextToken(a2, (int)&v23);
  while ( v23 != 101 )
  {
    IO_OutNewline();
    AST_Append(v8, v7);
    IO_OutWriteToken(v24);
    if ( v23 != 100 )
      goto LABEL_4;
    Parser_NextToken(a2, (int)&v23);
    IO_OutWriteToken(asc_50A54C);
    if ( v23 == 2 && !strcmp_(v10, aCase) )
    {
      if ( v26 )
        goto LABEL_4;
      *(_DWORD *)(v6 + 10) = Parser_ParseSingleExpression(a2, 0, v11);
      IO_OutWriteToken(asc_50A54C);
      if ( !*(_DWORD *)(v6 + 10) )
        goto LABEL_5;
      v12 = *(__int16 **)(*(_DWORD *)(v25 + 6) + 10);
      if ( v12 != *(__int16 **)(v6 + 10) )
      {
        while ( 1 )
        {
          v13 = *(__int16 **)(v6 + 10);
          if ( *v12 == *v13
            && *(_DWORD *)(v12 + 1) == *(_DWORD *)(v13 + 1)
            && AST_NodeListsEqual(*(__int16 **)(v12 + 3), *(__int16 **)(v13 + 3)) )
          {
            break;
          }
          v12 = *(__int16 **)(v12 + 5);
          if ( v12 == *(__int16 **)(v6 + 10) )
            goto LABEL_15;
        }
        Rules_PrintErrorID((int)aPrcdrpsr, 3, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateCaseF, v21);
        goto LABEL_5;
      }
LABEL_15:
      Parser_NextToken(a2, (int)&v23);
      if ( v23 != 2 || strcmp_(v14, aThen) )
        goto LABEL_4;
      ++v3;
    }
    else
    {
      if ( v23 != 2 || strcmp_(2, aDefault_1) || v3 < v22 || v26 )
        goto LABEL_4;
      *(_DWORD *)(v6 + 10) = AST_NewNode(105, 0);
      v26 = 1;
    }
    v15 = *(_DWORD *)(v6 + 10);
    if ( *(_DWORD *)g_ClipsParseContextSaveStack == 1 )
      g_ClipsParseReturnContext = 1;
    if ( *(_DWORD *)(g_ClipsParseContextSaveStack + 4) == 1 )
      g_ParserBreakContextFlag = 1;
    Rules_IncrementIndentDepth(3);
    AST_Append(v17, v16);
    *(_DWORD *)(v15 + 10) = Parser_ParseProgram(a2, v18, 1);
    Rules_DecrementIndentDepth(3);
    g_ClipsParseReturnContext = v19;
    g_ParserBreakContextFlag = v19;
    if ( !*(_DWORD *)(v15 + 10) )
      goto LABEL_5;
    v6 = *(_DWORD *)(v15 + 10);
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(v24);
    Parser_NextToken(a2, v20);
  }
  if ( v3 < 2 )
  {
LABEL_4:
    Parser_ReportSyntaxError();
LABEL_5:
    AST_Free(v25);
    Rules_DecrementIndentDepth(3);
    return 0;
  }
  Rules_DecrementIndentDepth(3);
  return v25;
}
// 4BE8B8: variable 'v4' is possibly undefined
// 4BE8B8: variable 'v5' is possibly undefined
// 4BE8E6: variable 'v8' is possibly undefined
// 4BE8E6: variable 'v7' is possibly undefined
// 4BE94B: variable 'v10' is possibly undefined
// 4BE962: variable 'v11' is possibly undefined
// 4BE9B3: variable 'v12' is possibly undefined
// 4BE9DA: variable 'v14' is possibly undefined
// 4BEA29: variable 'v17' is possibly undefined
// 4BEA29: variable 'v16' is possibly undefined
// 4BEA32: variable 'v18' is possibly undefined
// 4BEA46: variable 'v19' is possibly undefined
// 4BEA76: variable 'v20' is possibly undefined
// 4BEAC3: variable 'v21' is possibly undefined
// 4BEAF4: variable 'v22' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51B35C: using guessed type int dword_51B35C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BEB30) --------------------------------------------------------
signed int  Rules_FindNamedContextDepth(int a1)
{
  _DWORD *v2; // eax
  int v3; // edx

  v2 = (_DWORD *)g_ClipsLoopContextStackTop;
  v3 = 1;
  if ( !g_ClipsLoopContextStackTop )
    return 0;
  while ( a1 != *v2 )
  {
    v2 = (_DWORD *)v2[2];
    ++v3;
    if ( !v2 )
      return 0;
  }
  return v3;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BEB60) --------------------------------------------------------
int  Rules_GetNamedContextValue(int a1)
{
  _DWORD *v2; // eax

  v2 = (_DWORD *)g_ClipsLoopContextStackTop;
  if ( !g_ClipsLoopContextStackTop )
    return 0;
  while ( a1 != *v2 )
  {
    v2 = (_DWORD *)v2[2];
    if ( !v2 )
      return 0;
  }
  return v2[1];
}
// 54E880: using guessed type int dword_54E880;

//----- (004BEB80) --------------------------------------------------------
int Rules_CountNamedContextEntries()
{
  int v0; // eax
  int i; // edx

  v0 = g_ClipsLoopContextStackTop;
  for ( i = 0; v0; ++i )
    v0 = *(_DWORD *)(v0 + 8);
  return i;
}
// 54E880: using guessed type int dword_54E880;

//----- (004BEBB0) --------------------------------------------------------
signed int  Rules_PushNamedContextEntry(int a1, _DWORD *a2)
{
  int v4; // ebx
  _DWORD *v5; // ecx
  _DWORD *v6; // edx
  _DWORD *v7; // esi
  int v8; // eax
  int v9; // ecx
  _DWORD *v11; // ecx
  _DWORD *v12; // eax

  v4 = 1;
  v5 = (_DWORD *)g_ClipsLoopContextStackTop;
  v6 = 0;
  if ( g_ClipsLoopContextStackTop )
  {
    while ( a1 != *v5 )
    {
      v6 = v5;
      v5 = (_DWORD *)v5[2];
      ++v4;
      if ( !v5 )
        goto LABEL_7;
    }
    if ( a2 )
    {
      v7 = (_DWORD *)v5[1];
      v8 = Rules_UnionConstraints((int)a2, (int)v7);
      *(_DWORD *)(v9 + 4) = v8;
      AST_DecrementNodeRefCount(v7);
      AST_DecrementNodeRefCount(a2);
    }
    return v4;
  }
  else
  {
LABEL_7:
    v11 = *(_DWORD **)(g_ClipsMemoryTable + 48);
    if ( v11 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *v11;
      v12 = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      v12 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    v12[2] = 0;
    *v12 = a1;
    v12[1] = a2;
    if ( v6 )
      v6[2] = v12;
    else
      g_ClipsLoopContextStackTop = (int)v12;
    return v4;
  }
}
// 4BEBDD: variable 'v9' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E880: using guessed type int dword_54E880;

//----- (004BEC50) --------------------------------------------------------
int  Rules_RemoveNamedContextEntry(int result)
{
  int v1; // ebx
  int v2; // edx
  int i; // ecx
  _DWORD *v4; // edx

  v1 = result;
  v2 = g_ClipsLoopContextStackTop;
  for ( i = 0; v2; v2 = *(_DWORD *)(v2 + 8) )
  {
    result = v1 != *(_DWORD *)v2;
    if ( v1 == *(_DWORD *)v2 )
      break;
    i = v2;
  }
  if ( v2 )
  {
    if ( i )
      *(_DWORD *)(i + 8) = *(_DWORD *)(v2 + 8);
    else
      g_ClipsLoopContextStackTop = *(_DWORD *)(v2 + 8);
    AST_DecrementNodeRefCount(*(_DWORD **)(v2 + 4));
    g_ClipsMemFreeListTemp = (int)v4;
    *v4 = *(_DWORD *)(g_ClipsMemoryTable + 48);
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4BEC91: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E880: using guessed type int dword_54E880;

//----- (004BECC0) --------------------------------------------------------
signed int Rules_RegisterRuleCommands()
{
  Rules_RegisterHostFunction(aRun, 118, (int)aRuncommand, (int)Rules_RunCommand, (int)a1i);
  Rules_RegisterHostFunction(aHalt, 118, (int)aHaltcommand, (int)Rules_HaltCommand, (int)a00_9);
  Rules_RegisterHostFunction(aFocus_2, 98, (int)aFocuscommand, (int)Rules_FocusCommand, (int)a1W_1);
  Rules_RegisterHostFunction(aClearFocusStac, 118, (int)aClearfocusstac, (int)Rules_ClearFocusStackCommand, (int)a00_9);
  Rules_RegisterHostFunction(aGetFocusStack, 109, (int)aGetfocusstackf, (int)Rules_GetFocusStackFunction, (int)a00_9);
  Rules_RegisterHostFunction(aPopFocus, 119, (int)aPopfocusfuncti, (int)Rules_PopFocusFunction, (int)a00_9);
  Rules_RegisterHostFunction(aGetFocus, 119, (int)aGetfocusfuncti, (int)Rules_GetFocusFunction, (int)a00_9);
  Rules_RegisterHostFunction(aSetBreak, 118, (int)aSetbreakcomman, (int)Rules_SetBreakCommand, (int)a11w_8);
  Rules_RegisterHostFunction(aRemoveBreak, 118, (int)aRemovebreakcom, (int)Rules_RemoveBreakCommand, (int)a1w);
  Rules_RegisterHostFunction(aShowBreaks, 118, (int)aShowbreakscomm, (int)Rules_ShowBreaksCommand, (int)a01w_5);
  Rules_RegisterHostFunction(aMatches, 118, (int)aMatchescommand, (int)Rules_MatchesCommand, (int)a11w_8);
  Rules_RegisterHostFunction(aListFocusStack, 118, (int)aListfocusstack, (int)Rules_ListFocusStackCommand, (int)a00_9);
  Rules_RegisterHostFunction(aDependencies, 118, (int)aDependenciesco, (int)Rules_Dependencies, (int)a11h);
  Rules_RegisterHostFunction(aDependents, 118, (int)aDependentscomm, (int)Rules_Dependents, (int)a11h);
  Rules_RegisterHostFunction(aGetIncremental, 98, (int)aGetincremental, (int)Rules_GetIncrementalResetCommand, (int)a00_9);
  Rules_RegisterHostFunction(aSetIncremental, 98, (int)aSetincremental, (int)Rules_SetIncrementalResetCommand, (int)a11_4);
  Rules_RegisterHostFunction(aGetStrategy, 119, (int)aGetstrategycom, (int)Rules_GetStrategyCommand, (int)a00_9);
  return Rules_RegisterHostFunction(aSetStrategy, 119, (int)aSetstrategycom, (int)Rules_SetStrategyCommand, (int)a11w_8);
}

//----- (004BEEF0) --------------------------------------------------------
_BYTE * Rules_MatchesCommand(int a1, double a2)
{
  _BYTE *result; // eax
  int v3; // ecx
  _DWORD *v4; // eax
  int v5; // edx
  int v6; // ecx

  result = (_BYTE *)Rules_GetConstructNameArg((int)aRuleName_0, a1, a2);
  if ( result )
  {
    v4 = (_DWORD *)Rules_FindDefruleByName(result, v3);
    if ( v4 )
      return (_BYTE *)Rules_ListDefruleMatches(v4, v6);
    else
      return (_BYTE *)Rules_ReportCantFindItem(v6, v5);
  }
  return result;
}
// 4BEF08: variable 'v3' is possibly undefined
// 4BEF16: variable 'v6' is possibly undefined
// 4BEF16: variable 'v5' is possibly undefined

//----- (004BEF30) --------------------------------------------------------
int  Rules_ListDefruleMatches(_DWORD *a1, int a2)
{
  _DWORD *v2; // edi
  int v3; // ebp
  int v4; // edx
  signed int v5; // ecx
  _DWORD *v6; // eax
  int v7; // esi
  int v8; // esi
  int *v9; // ebx
  int result; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ebp
  signed int v16; // ecx
  int v17; // eax
  _DWORD *v18; // edx
  int v19; // esi
  int v20; // esi
  int *v21; // edi
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int i; // ebx
  _DWORD *v27; // ecx
  int v28; // ecx
  int v29; // ecx
  _DWORD **v30; // edi
  _DWORD *v31; // ecx
  int v32; // ecx
  int v33; // ecx
  _DWORD *v35; // [esp+4h] [ebp-20h]
  int v36; // [esp+8h] [ebp-1Ch]
  int v37; // [esp+8h] [ebp-1Ch]

  v35 = a1;
  if ( a1 )
  {
    while ( 1 )
    {
      v2 = (_DWORD *)v35[11];
      v3 = Rules_CountJoinNetworkEntryNodes((int)v2);
      v4 = v3 - 1;
      v5 = Mem_HeapAllocWithRetry((_DWORD *)(12 * v3));
      v36 = v5;
      v6 = v2;
      if ( v2 )
      {
        v7 = v5 + 4 * v4;
        do
        {
          if ( (*(_BYTE *)v6 & 4) != 0 )
          {
            v6 = (_DWORD *)v6[4];
          }
          else
          {
            v7 -= 4;
            *(_DWORD *)(v7 + 4) = *(_DWORD *)v6[4];
            --v4;
            v6 = (_DWORD *)v6[6];
          }
        }
        while ( v6 );
      }
      v8 = 0;
      if ( v3 > 0 )
        break;
LABEL_16:
      Mem_ReleasePoolBlock(v36, 12 * v3);
      v15 = *v2 << 16 >> 25;
      v16 = Mem_HeapAllocWithRetry((_DWORD *)(12 * v15));
      v37 = v16;
      v17 = v15 - 1;
      v18 = v2;
      if ( v15 - 1 >= 0 )
      {
        v19 = v16 + 4 * v17;
        do
        {
          v19 -= 4;
          *(_DWORD *)(v19 + 4) = v18[2];
          --v17;
          v18 = (_DWORD *)v18[6];
        }
        while ( v17 >= 0 );
      }
      v20 = 1;
      if ( v15 > 1 )
      {
        v21 = (int *)(v16 + 4);
        do
        {
          result = Rules_GetEvaluationErrorFlag();
          if ( result == 1 )
            return result;
          Output_Write((int)g_IO_LogicalName_WDisplay, (int)aPartialMatches, v22);
          Rules_PrintLongInteger(v23, v20 + 1);
          Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50A998, v24);
          v25 = *v21;
          for ( i = 0; v25; v25 = v27[1] )
          {
            result = Rules_GetEvaluationErrorFlag();
            if ( result == 1 )
              return result;
            if ( (*(_BYTE *)v27 & 0x20) == 0 )
            {
              Rules_PrintArgumentValueList((int)g_IO_LogicalName_WDisplay, v27);
              ++i;
              Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50A998, v28);
            }
          }
          if ( !i )
            Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone_3, v25);
          ++v20;
          ++v21;
        }
        while ( v20 < v15 );
      }
      Mem_ReleasePoolBlock(v37, 12 * v15);
      v35 = (_DWORD *)v35[12];
      if ( !v35 )
        goto LABEL_31;
    }
    v9 = (int *)v5;
    while ( 1 )
    {
      result = Rules_GetEvaluationErrorFlag();
      if ( result == 1 )
        break;
      Output_Write((int)g_IO_LogicalName_WDisplay, (int)aMatchesForPatt, v11);
      Rules_PrintLongInteger(v12, v8 + 1);
      Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50A998, v13);
      v14 = *v9;
      if ( !*v9 )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone_3, 0);
      while ( v14 )
      {
        result = Rules_GetEvaluationErrorFlag();
        if ( result == 1 )
          return result;
        Rules_PrintArgumentValueList((int)g_IO_LogicalName_WDisplay, v31);
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50A998, v32);
        v14 = *(_DWORD *)(v33 + 4);
      }
      ++v8;
      ++v9;
      if ( v8 >= v3 )
        goto LABEL_16;
    }
  }
  else
  {
LABEL_31:
    Output_Write((int)g_IO_LogicalName_WDisplay, (int)aActivations_1, a2);
    v30 = (_DWORD **)Rules_GetNextActivation(0);
    if ( v30 )
    {
      while ( 1 )
      {
        result = Rules_GetEvaluationErrorFlag();
        if ( result == 1 )
          break;
        if ( *a1 == **v30 )
        {
          Rules_PrintArgumentValueList((int)g_IO_LogicalName_WDisplay, v30[1]);
          Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_50A998, 0);
        }
        v30 = (_DWORD **)Rules_GetNextActivation((int)v30);
        if ( !v30 )
          goto LABEL_36;
      }
    }
    else
    {
LABEL_36:
      if ( v29 )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)aNone_3, v29);
      return 1;
    }
  }
  return result;
}
// 4BEFBD: variable 'v11' is possibly undefined
// 4BEFCA: variable 'v12' is possibly undefined
// 4BEFD9: variable 'v13' is possibly undefined
// 4BEFEA: variable 'v14' is possibly undefined
// 4BF069: variable 'v22' is possibly undefined
// 4BF076: variable 'v23' is possibly undefined
// 4BF085: variable 'v24' is possibly undefined
// 4BF0A0: variable 'v27' is possibly undefined
// 4BF0BC: variable 'v28' is possibly undefined
// 4BF113: variable 'a2' is possibly undefined
// 4BF16E: variable 'v29' is possibly undefined
// 4BF1B7: variable 'v31' is possibly undefined
// 4BF1C6: variable 'v32' is possibly undefined
// 4BF1CB: variable 'v33' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004BF1E0) --------------------------------------------------------
void  Rules_FreeDefruleDisjunctChain(int a1)
{
  int v1; // ebx
  int v2; // ecx
  int v3; // eax

  v1 = a1;
  if ( a1 )
  {
    g_ClipsDefrulePreservedWatchBreakFlags = (*(_BYTE *)(a1 + 29) & 8) != 0;
    if ( (*(_BYTE *)(a1 + 29) & 0x10) != 0 )
      LOBYTE(g_ClipsDefrulePreservedWatchBreakFlags) = g_ClipsDefrulePreservedWatchBreakFlags | 2;
    if ( (*(_BYTE *)(a1 + 29) & 0x20) != 0 )
      LOBYTE(g_ClipsDefrulePreservedWatchBreakFlags) = g_ClipsDefrulePreservedWatchBreakFlags | 4;
    Rules_ClearActivationsForRule(a1);
    do
    {
      Rules_RemoveJoinNetworkNodes(v1);
      if ( v2 )
      {
        if ( *(_DWORD *)(v1 + 32) )
        {
          AST_DeinstallNodeChain(*(__int16 **)(v1 + 32));
          AST_FreePackedNodeChain(*(_DWORD *)(v1 + 32));
          *(_DWORD *)(v1 + 32) = 0;
        }
        if ( *(_DWORD *)(v1 + 4) )
        {
          Mem_SmallBlockFree(*(_DWORD **)(v1 + 4), strlen(*(const char **)(v1 + 4)) + 1);
          *(_DWORD *)(v1 + 4) = 0;
        }
        v2 = 0;
      }
      Rules_DecrementSymbolCount(*(_DWORD *)v1, v2);
      if ( *(_DWORD *)(v1 + 36) )
      {
        AST_DeinstallNodeChain(*(__int16 **)(v1 + 36));
        AST_FreePackedNodeChain(*(_DWORD *)(v1 + 36));
      }
      v3 = *(_DWORD *)(v1 + 48);
      g_ClipsMemFreeListTemp = v1;
      *(_DWORD *)v1 = *(_DWORD *)(g_ClipsMemoryTable + 208);
      *(_DWORD *)(g_ClipsMemoryTable + 208) = g_ClipsMemFreeListTemp;
      v1 = v3;
    }
    while ( v3 );
    if ( !g_Rules_CurrentlyExecutingRule )
      Rules_FlushPendingNetworkGarbage();
  }
}
// 4BF22D: variable 'v2' is possibly undefined
// 51A1F0: using guessed type int dword_51A1F0;
// 51B364: using guessed type int dword_51B364;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004BF300) --------------------------------------------------------
int  Rules_RemoveJoinNetworkNodes(int result)
{
  _DWORD *v1; // edx
  int v2; // ecx
  _DWORD *v3; // ebx
  _DWORD *v4; // esi
  int v5; // edx
  __int16 *v6; // eax
  int v7; // ecx
  _DWORD *v8; // edx
  _DWORD *v9; // eax
  _DWORD *v10; // ecx

  v1 = *(_DWORD **)(result + 44);
  *(_DWORD *)(result + 44) = 0;
  if ( v1 )
  {
    v2 = v1[5];
    v1[9] = 0;
    if ( !v2 )
    {
      while ( 1 )
      {
        v3 = (_DWORD *)v1[6];
        if ( (*(_BYTE *)v1 & 4) != 0 )
          v4 = (_DWORD *)v1[4];
        else
          v4 = 0;
        if ( v1[4] && (*(_BYTE *)v1 & 4) == 0 )
          Rules_UnlinkJoinNetworkNode(v1);
        Rules_ReleaseJoinNetworkNodeChain(v1[2]);
        v6 = *(__int16 **)(v5 + 12);
        *(_DWORD *)(v5 + 8) = 0;
        AST_RemoveHashedNodeChain(v6, v7);
        g_ClipsMemFreeListTemp = (int)v8;
        *v8 = *(_DWORD *)(g_ClipsMemoryTable + 160);
        result = g_ClipsMemoryTable;
        *(_DWORD *)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
        if ( !v3 )
          break;
        v9 = (_DWORD *)v3[5];
        v10 = 0;
        if ( v9 )
        {
          while ( v9 != v8 )
          {
            v10 = v9;
            v9 = (_DWORD *)v9[7];
            if ( !v9 )
              goto LABEL_13;
          }
          if ( v10 )
            v10[7] = v8[7];
          else
            v3[5] = v8[7];
        }
LABEL_13:
        if ( v4 )
        {
          v3 = v4;
          v4[5] = 0;
        }
        result = v3[9];
        if ( result || v3[5] )
          break;
        v1 = v3;
      }
    }
  }
  return result;
}
// 4BF32D: conditional instruction was optimized away because edx.4!=0
// 4BF35D: variable 'v5' is possibly undefined
// 4BF363: variable 'v7' is possibly undefined
// 4BF36D: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004BF3F0) --------------------------------------------------------
_DWORD * Rules_UnlinkJoinNetworkNode(_DWORD *a1)
{
  int *v2; // ebx
  _DWORD *result; // eax
  int v4; // ecx

  v2 = (int *)a1[4];
  result = (_DWORD *)v2[2];
  v4 = 0;
  if ( result )
  {
    do
    {
      if ( result == a1 )
      {
        result = (_DWORD *)a1[8];
        if ( v4 )
          *(_DWORD *)(v4 + 32) = result;
        else
          v2[2] = (int)result;
        goto LABEL_5;
      }
      v4 = (int)result;
      result = (_DWORD *)result[8];
    }
    while ( result );
    if ( v2[2] )
      return result;
    return (_DWORD *)Rules_DeletePatternNetworkForType(*a1 << 23 >> 29, v2, v4);
  }
LABEL_5:
  if ( !v2[2] )
    return (_DWORD *)Rules_DeletePatternNetworkForType(*a1 << 23 >> 29, v2, v4);
  return result;
}

//----- (004BF450) --------------------------------------------------------
signed int  Rules_ParseDefrule(int a1, double a2)
{
  int v3; // eax
  signed int result; // eax
  int *v5; // esi
  signed int v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // edx
  int v10; // edx
  int v11; // eax
  int v12; // edx
  _DWORD *v13; // ecx
  _DWORD *i; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  char *v18; // eax
  int v19; // edx
  _BYTE v20[36]; // [esp+0h] [ebp-24h] BYREF

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  IO_OutWriteToken(aDefrule_4);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  g_ClipsDefrulePreservedWatchBreakFlags = 0;
  v3 = Rules_GetConstructNameAndComment(a1, (int)v20, (int (*)(void))Rules_FindDefruleByName, aDefrule_5, (int (*)(void))Rules_DeleteDefruleOrAll, asc_50A9E8, 0, 1, 1);
  if ( !v3 )
    return 1;
  v5 = Lexer_ParseRuleLHS(a1, v3, *(_DWORD *)(v3 + 16), a2);
  if ( v5 )
  {
    Parser_FreeLoopContextStack();
    g_ClipsParseReturnContext = 1;
    v6 = Rules_ParseDefruleRHS(a1);
    v8 = v6;
    if ( v6 )
    {
      Rules_BuildDefruleDisjunctChain(v5, v6, v7);
      AST_Free(v8);
      Parser_FreeLoopContextStack();
      AST_FreeNode((int)v5);
      if ( v9 )
      {
        g_ClipsParsedFormAst = 0;
        IO_OutWriteToken(asc_50A9EC);
        if ( Mem_GetAllocFlag() == 1 )
        {
          *(_DWORD *)(v10 + 4) = 0;
        }
        else
        {
          v18 = Rules_CopyPPBuffer();
          *(_DWORD *)(v19 + 4) = v18;
        }
        v11 = Module_FindItemByName((int)aDefrule_5);
        v12 = Module_GetItem(0, *(_DWORD *)(v11 + 4));
        for ( i = v13; i; i = (_DWORD *)i[12] )
          i[2] = v12;
        Rules_AddConstructToModuleList(v13);
        if ( (g_ClipsDefrulePreservedWatchBreakFlags & 1) != 0 )
          Rules_SetBreakFlag(v15);
        if ( (g_ClipsDefrulePreservedWatchBreakFlags & 2) != 0 || Rules_GetWatchItemState((int)aActivations) )
          Rules_SetInheritedFlagBit4(1, v15);
        if ( (g_ClipsDefrulePreservedWatchBreakFlags & 4) != 0 || Rules_GetWatchItemState((int)aRules) )
        {
          Rules_SetInheritedFlagBit5(1, v15);
          Rules_RunIncrementalReset(v16, a2);
          return 0;
        }
        else
        {
          Rules_RunIncrementalReset(v15, a2);
          return 0;
        }
      }
      else
      {
        AST_FreePackedNodeChain(g_ClipsParsedFormAst);
        result = 1;
        g_ClipsParsedFormAst = v17;
      }
    }
    else
    {
      AST_FreePackedNodeChain(g_ClipsParsedFormAst);
      g_ClipsParsedFormAst = 0;
      AST_FreeNode((int)v5);
      return 1;
    }
  }
  else
  {
    AST_FreePackedNodeChain(g_ClipsParsedFormAst);
    g_ClipsParsedFormAst = 0;
    return 1;
  }
  return result;
}
// 4BF508: variable 'v7' is possibly undefined
// 4BF526: variable 'v9' is possibly undefined
// 4BF54C: variable 'v10' is possibly undefined
// 4BF565: variable 'v13' is possibly undefined
// 4BF592: variable 'v15' is possibly undefined
// 4BF5CB: variable 'v16' is possibly undefined
// 4BF630: variable 'v17' is possibly undefined
// 4BF645: variable 'v19' is possibly undefined
// 51B364: using guessed type int dword_51B364;
// 51C6F4: using guessed type int dword_51C6F4;
// 54E87C: using guessed type int dword_54E87C;

//----- (004BF690) --------------------------------------------------------
int  Rules_BuildDefruleDisjunctChain(_DWORD *theLHS, signed int actions, int ruleName)
{
  _DWORD *lhsPtr; // ebp
  _DWORD *tempNode; // esi
  __int16 *newActions; // edi
  _DWORD *packPtr; // ebx
  _DWORD *v7; // edx
  _DWORD *lastJoin; // edi
  __int16 complexity; // ax
  _DWORD *currentDisjunct; // eax
  _DWORD *v11; // edx
  int localVarCnt; // [esp+4h] [ebp-24h]
  _DWORD *lastDisjunct; // [esp+8h] [ebp-20h]
  int topDisjunct; // [esp+10h] [ebp-18h]
  signed int logicalJoin; // [esp+14h] [ebp-14h]

  lhsPtr = theLHS;
  tempNode = 0;
  topDisjunct = 0;
  lastDisjunct = 0;
  if ( *theLHS == 82 )
    lhsPtr = (_DWORD *)theLHS[16];
  localVarCnt = Rules_CountNamedContextEntries();
  if ( !lhsPtr )
    return topDisjunct;
  while ( 1 )
  {
    if ( *lhsPtr == 81 )
    {
      tempNode = (_DWORD *)lhsPtr[16];
    }
    else if ( *lhsPtr == 80 )
    {
      tempNode = lhsPtr;
    }
    if ( Rules_CEDetectDuplicatePatternBinding(tempNode) || Rules_PatternChainHasActiveType80Callback(tempNode) || (logicalJoin = Rules_ValidateLogicalCEPlacement((signed int)tempNode), logicalJoin < 0) || Rules_CheckRHSActionsAgainstCEConstraints(actions, (int)tempNode) )
    {
      Rules_FreeDefruleDisjunctChain(topDisjunct);
      return 0;
    }
    newActions = (__int16 *)AST_CloneNodeList(actions);
    if ( Parser_ReplaceProcVars((int)aRhsOfDefrule, (int)newActions, 0, 0, (int (*)(void))Rules_ReplaceRHSModifyDuplicateVar, (int)tempNode) )
      break;
    AST_InstallNodeChain(newActions);
    packPtr = AST_PackNodeChain(newActions);
    AST_Free((int)newActions);
    lastJoin = Rules_BuildJoinTestExpressionChain(logicalJoin, v7, tempNode);
    complexity = Rules_SumCEListComplexity((int)tempNode);
    currentDisjunct = Rules_AllocDefruleDisjunct(ruleName, localVarCnt, complexity, (int)packPtr, logicalJoin, (int)lastJoin);
    v11 = currentDisjunct;
    if ( topDisjunct )
    {
      lastDisjunct[12] = currentDisjunct;
    }
    else
    {
      topDisjunct = (int)currentDisjunct;
      AST_InstallNodeChain((__int16 *)currentDisjunct[8]);
    }
    lhsPtr = (_DWORD *)lhsPtr[17];
    lastDisjunct = v11;
    if ( !lhsPtr )
      return topDisjunct;
  }
  Rules_FreeDefruleDisjunctChain(topDisjunct);
  AST_Free((int)newActions);
  return 0;
}
// 4BF75E: variable 'v7' is possibly undefined
// 4BF79A: variable 'v11' is possibly undefined

//----- (004BF7F0) --------------------------------------------------------
_DWORD * Rules_AllocDefruleDisjunct(int ruleName, int localVarCnt, __int16 complexity, int theActions, int logicalJoin, int lastJoin)
{
  _DWORD *freeNode; // ecx
  signed int newDisjunct; // ecx
  __int16 v11; // di
  int v12; // eax
  int theItem; // eax
  int theModuleItem; // eax
  _DWORD *disjunctPtr; // ecx
  int theJoin; // eax

  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 208);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 208);
    *(_DWORD *)(g_ClipsMemoryTable + 208) = *freeNode;
    newDisjunct = g_ClipsMemFreeListTemp;
  }
  else
  {
    newDisjunct = Mem_HeapAllocWithRetry((_DWORD *)0x34);
  }
  *(_DWORD *)(newDisjunct + 4) = 0;
  *(_DWORD *)(newDisjunct + 16) = 0;
  *(_DWORD *)(newDisjunct + 40) = 0;
  *(_DWORD *)(newDisjunct + 48) = 0;
  *(_DWORD *)newDisjunct = ruleName;
  ++*(_DWORD *)(ruleName + 4);
  *(_DWORD *)(newDisjunct + 36) = theActions;
  v11 = *(_WORD *)(newDisjunct + 28) & 0x4000;
  *(_DWORD *)(newDisjunct + 20) = g_CLIPS_CurrentRuleSalience;
  *(_WORD *)(newDisjunct + 28) = v11;
  *(_DWORD *)(newDisjunct + 28) |= complexity & 0x7FF;
  v12 = g_Rules_DeclaredAutoFocusFlag & 1;
  *(_BYTE *)(newDisjunct + 29) &= ~0x40u;
  *(_DWORD *)(newDisjunct + 28) |= v12 << 14;
  *(_DWORD *)(newDisjunct + 32) = g_ClipsParsedFormAst;
  *(_DWORD *)(newDisjunct + 24) = localVarCnt;
  theItem = Module_FindItemByName((int)aDefrule_5);
  theModuleItem = Module_GetItem(0, *(_DWORD *)(theItem + 4));
  disjunctPtr[2] = theModuleItem;
  theJoin = lastJoin;
  *(_DWORD *)(lastJoin + 36) = disjunctPtr;
  disjunctPtr[11] = lastJoin;
  do
  {
    if ( *(_DWORD *)theJoin << 16 >> 25 == logicalJoin )
    {
      disjunctPtr[10] = theJoin;
      *(_BYTE *)theJoin |= 2u;
    }
    theJoin = *(_DWORD *)(theJoin + 24);
  }
  while ( theJoin );
  return disjunctPtr;
}
// 4BF8AC: variable 'v15' is possibly undefined
// 51C6F4: using guessed type int dword_51C6F4;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E90C: using guessed type int dword_54E90C;
// 54E910: using guessed type int dword_54E910;

//----- (004BF8F0) --------------------------------------------------------
int  Rules_ReplaceRHSModifyDuplicateVar(__int16 *nodePtr, _DWORD *theLHS, int a3)
{
  __int16 nodeType; // bx
  int result; // eax
  int **Symbol; // eax
  int v6; // edx
  int v7; // ecx
  int **duplicateSymbol; // eax
  int v9; // edx
  int v10; // ecx

  nodeType = *nodePtr;
  if ( *nodePtr == 10 )
  {
    Symbol = Rules_MakeSymbol(aModify_0);
    if ( Symbol == *(int ***)(v7 + 2) )
    {
      if ( !Lexer_ValidateMessageHandler(v7, (int)aModify_0, v6) )
        return -1;
    }
    else
    {
      duplicateSymbol = Rules_MakeSymbol(aDuplicate_0);
      if ( duplicateSymbol == *(int ***)(v10 + 2) && !Lexer_ValidateMessageHandler(v10, (int)aDuplicate_0, v9) )
        return -1;
    }
    return 0;
  }
  if ( nodeType != 15 && nodeType != 16 )
    return 0;
  result = (int)Rules_FindCEByIndex(*(_DWORD *)(nodePtr + 1), theLHS);
  if ( result )
  {
    if ( *(_DWORD *)(result + 24) )
    {
      (*(void (__cdecl **)(int))(*(_DWORD *)(result + 24) + 36))(a3);
      return 1;
    }
    return 0;
  }
  return result;
}
// 4BF918: variable 'v7' is possibly undefined
// 4BF926: variable 'v6' is possibly undefined
// 4BF941: variable 'v10' is possibly undefined
// 4BF94F: variable 'v9' is possibly undefined

//----- (004BF990) --------------------------------------------------------
int  Rules_ParseDefruleRHS(int readSource)
{
  unsigned int *v2; // edx
  int result; // eax
  int v4; // edx
  int v5; // edx
  int v6; // [esp+0h] [ebp-1Ch]
  char *v7; // [esp+8h] [ebp-14h]

  IO_OutWriteToken(asc_50AA28);
  Rules_SetIndentDepth(3);
  result = Parser_ParseProgram(readSource, v2, 1);
  if ( result )
  {
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(v7);
    if ( v6 == 101 )
    {
      return v4;
    }
    else
    {
      Parser_ReportSyntaxError();
      AST_Free(v5);
      return 0;
    }
  }
  return result;
}
// 4BF9B8: variable 'v2' is possibly undefined
// 4BF9D9: variable 'v7' is possibly undefined
// 4BF9E2: variable 'v6' is possibly undefined
// 4BF9E4: variable 'v4' is possibly undefined
// 4BF9FA: variable 'v5' is possibly undefined

//----- (004BFA10) --------------------------------------------------------
int  Rules_SumCEListComplexity(int theLHS)
{
  int lhsNode; // esi
  int i; // ecx
  int testComplexity; // eax
  int fieldNode; // ebx
  int v5; // ecx
  int j; // edx
  int subComplexity; // eax
  int v8; // edx
  int v9; // ecx
  int fieldComplexity; // eax
  int v12; // ecx

  lhsNode = theLHS;
  for ( i = 0; lhsNode; lhsNode = *(_DWORD *)(lhsNode + 68) )
  {
    testComplexity = Rules_ComputeExpressionComplexity(*(__int16 **)(lhsNode + 52));
    fieldNode = *(_DWORD *)(lhsNode + 64);
    for ( i = testComplexity + v5; fieldNode; fieldNode = *(_DWORD *)(fieldNode + 64) )
    {
      if ( (*(_BYTE *)(fieldNode + 8) & 4) != 0 )
      {
        for ( j = *(_DWORD *)(fieldNode + 68); j; i = subComplexity + v9 )
        {
          subComplexity = Rules_ComputeExpressionComplexity(*(__int16 **)(j + 52));
          j = *(_DWORD *)(v8 + 64);
        }
      }
      else
      {
        fieldComplexity = Rules_ComputeExpressionComplexity(*(__int16 **)(fieldNode + 52));
        i = fieldComplexity + v12;
      }
    }
  }
  return i;
}
// 4BFA28: variable 'v5' is possibly undefined
// 4BFA43: variable 'v8' is possibly undefined
// 4BFA46: variable 'v9' is possibly undefined
// 4BFA69: variable 'v12' is possibly undefined

//----- (004BFA70) --------------------------------------------------------
int  Rules_ComputeExpressionComplexity(__int16 *exprList)
{
  __int16 *exprPtr; // edx
  int complexity; // ecx
  int fcallValue; // eax
  int argComplexity; // eax
  int v5; // ecx
  _DWORD *entityRecord; // ebx

  exprPtr = exprList;
  complexity = 0;
  if ( !exprList )
    return complexity;
  do
  {
    while ( 1 )
    {
      if ( *exprPtr == 10 )
      {
        fcallValue = *(_DWORD *)(exprPtr + 1);
        if ( fcallValue == g_Clips_SymbolAnd || fcallValue == g_ClipsNotSymbol || fcallValue == g_ClipsSymbolOr )
        {
          argComplexity = Rules_ComputeExpressionComplexity(*(_DWORD *)(exprPtr + 3));
          complexity = argComplexity + v5;
        }
        else
        {
          ++complexity;
        }
        goto LABEL_5;
      }
      entityRecord = (_DWORD *)g_Clips_PrimitiveEntityTable[*exprPtr];
      if ( entityRecord )
      {
        if ( (*entityRecord & 0x8000) != 0 )
          break;
      }
LABEL_5:
      exprPtr = *(__int16 **)(exprPtr + 5);
      if ( !exprPtr )
        return complexity;
    }
    ++complexity;
    exprPtr = *(__int16 **)(exprPtr + 5);
  }
  while ( exprPtr );
  return complexity;
}
// 4BFA9A: variable 'v5' is possibly undefined
// 4BFA9C: variable 'v1' is possibly undefined
// 54E530: using guessed type int dword_54E530[70];
// 54E65C: using guessed type int dword_54E65C;
// 54E660: using guessed type int dword_54E660;
// 54E664: using guessed type int dword_54E664;

//----- (004BFAF0) --------------------------------------------------------
signed int  Rules_ValidateLogicalCEPlacement(signed int result)
{
  int lastLogicalDepth; // ecx
  int logicalJoin; // edx
  int gappedLogical; // ebx
  int firstLogical; // esi
  int v5; // ecx
  int v6; // ecx

  lastLogicalDepth = 0;
  logicalJoin = 0;
  gappedLogical = 0;
  firstLogical = *(_DWORD *)(result + 8) << 30 >> 31;
  do
  {
    if ( *(_DWORD *)result == 80 && *(_DWORD *)(result + 48) == 1 )
    {
      if ( (*(_BYTE *)(result + 8) & 2) != 0 )
      {
        if ( !firstLogical )
        {
          Rules_PrintErrorID((int)aRulepsr_0, 1, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aLogicalCesMust, v5);
          return -1;
        }
        if ( gappedLogical )
        {
          Rules_PrintErrorID((int)aRulepsr_0, 2, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aGapsMayNotExis, v6);
          return -1;
        }
        lastLogicalDepth = *(_DWORD *)(result + 48);
        ++logicalJoin;
      }
      else
      {
        gappedLogical = *(_DWORD *)(result + 48);
      }
    }
    result = *(_DWORD *)(result + 68);
  }
  while ( result );
  if ( lastLogicalDepth )
    return logicalJoin;
  return result;
}
// 4BFB54: variable 'v5' is possibly undefined
// 4BFB7F: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004BFB90) --------------------------------------------------------
_DWORD * Rules_FindCEByIndex(int theVariable, _DWORD *theLHS)
{
  int savedNode; // edx
  _DWORD *foundCE; // ecx
  int fieldNode; // eax

  savedNode = 0;
  foundCE = 0;
  if ( !theLHS )
    return foundCE;
  do
  {
    while ( 1 )
    {
      if ( *theLHS == 80 && (theLHS[2] & 1) != 1 && (int)theLHS[11] <= 1 )
      {
        if ( theVariable == theLHS[1] )
          foundCE = theLHS;
        fieldNode = theLHS[16];
        if ( fieldNode )
          break;
      }
      theLHS = (_DWORD *)theLHS[17];
      if ( !theLHS )
        return foundCE;
    }
    do
    {
      if ( (*(_BYTE *)(fieldNode + 8) & 4) != 0 )
      {
        savedNode = fieldNode;
        fieldNode = *(_DWORD *)(fieldNode + 68);
      }
      if ( fieldNode && (*(_DWORD *)fieldNode == 15 || *(_DWORD *)fieldNode == 16) && theVariable == *(_DWORD *)(fieldNode + 4) )
        foundCE = (_DWORD *)fieldNode;
      if ( fieldNode )
      {
        if ( !*(_DWORD *)(fieldNode + 64) )
        {
          if ( savedNode )
          {
            fieldNode = savedNode;
            savedNode = 0;
          }
        }
      }
      else
      {
        fieldNode = savedNode;
        savedNode = 0;
      }
      fieldNode = *(_DWORD *)(fieldNode + 64);
    }
    while ( fieldNode );
    theLHS = (_DWORD *)theLHS[17];
  }
  while ( theLHS );
  return foundCE;
}

//----- (004BFC30) --------------------------------------------------------
_DWORD * Rules_AddConstructToModuleList(_DWORD *result)
{
  _DWORD *theConstruct; // edx
  int moduleHeader; // ecx

  theConstruct = result;
  moduleHeader = result[2];
  if ( *(_DWORD *)(moduleHeader + 8) )
  {
    result = *(_DWORD **)(moduleHeader + 8);
    do
    {
      result[4] = theConstruct;
      result = (_DWORD *)result[12];
    }
    while ( result );
    *(_DWORD *)(moduleHeader + 8) = theConstruct;
  }
  else
  {
    *(_DWORD *)(moduleHeader + 4) = result;
    *(_DWORD *)(moduleHeader + 8) = result;
  }
  return result;
}
// 4BFC41: conditional instruction was optimized away because ebx.4!=0

//----- (004BFC70) --------------------------------------------------------
int Rules_SetupDefruleCodeGenerator()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDefrules_0, 0, 0, (int)Rules_PrepareDefrulesForCodeGen, (int)Rules_WriteDefrulesToCode, 3);
  g_ClipsDefruleCodeGenItem = result;
  return result;
}
// 54E884: using guessed type int dword_54E884;

//----- (004BFCA0) --------------------------------------------------------
int Rules_PrepareDefrulesForCodeGen()
{
  int v3; // [esp-4h] [ebp-14h] BYREF
  int v4; // [esp+0h] [ebp-10h] BYREF
  int v5[3]; // [esp+4h] [ebp-Ch] BYREF

  return Rules_JoinNetworkAssignCodeGenIds(&v3, &v4, v5);
}

//----- (004BFCC0) --------------------------------------------------------
int  Rules_WriteDefrulesToCode(const char *fileName, const char *a2, int imageID, int headerFP, int maxIndices)
{
  int joinFile; // edi
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  int v10; // eax
  int v11; // esi
  int v12; // eax
  int theJoin; // esi
  int v14; // eax
  int v15; // edi
  int v16; // eax
  int fileCount; // [esp+0h] [ebp-4Ch] BYREF
  int joinArrayCount; // [esp+4h] [ebp-48h] BYREF
  int joinArrayVersion; // [esp+8h] [ebp-44h] BYREF
  int moduleArrayCount; // [esp+Ch] [ebp-40h] BYREF
  int moduleArrayVersion; // [esp+10h] [ebp-3Ch] BYREF
  int defruleArrayCount; // [esp+14h] [ebp-38h] BYREF
  int defruleArrayVersion; // [esp+18h] [ebp-34h] BYREF
  int moduleFile; // [esp+1Ch] [ebp-30h]
  int Enum; // [esp+20h] [ebp-2Ch]
  int moduleCount; // [esp+24h] [ebp-28h]
  int defruleFile; // [esp+28h] [ebp-24h]
  int theDefrule; // [esp+2Ch] [ebp-20h]
  const char *v30; // [esp+30h] [ebp-1Ch]
  const char *v31; // [esp+34h] [ebp-18h]
  int v32; // [esp+38h] [ebp-14h]
  int v33; // [esp+3Ch] [ebp-10h]

  v30 = fileName;
  v31 = a2;
  v32 = headerFP;
  v33 = imageID;
  joinArrayCount = 0;
  joinArrayVersion = 1;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  defruleArrayCount = 0;
  defruleArrayVersion = 1;
  moduleFile = 0;
  defruleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeRuledef, 1);
  joinFile = 0;
  Enum = Module_NextEnum(0);
  if ( !Enum )
  {
LABEL_16:
    Rules_CloseDefruleCodeFiles(moduleFile, defruleFile, maxIndices, joinFile);
    return 1;
  }
  while ( 1 )
  {
    Module_SetCurrent(Enum);
    v6 = Rules_ConstructCodeFileOpen(
           moduleFile,
           v30,
           v33,
           v31,
           &fileCount,
           moduleArrayVersion,
           v32,
           (char)aStructDefrulem,
           **(const char ***)(g_ClipsDefruleCodeGenItem + 20),
           0,
           0);
    v7 = v6;
    if ( !v6 )
    {
      Rules_CloseDefruleCodeFiles(0, defruleFile, maxIndices, joinFile);
      return 0;
    }
    Rules_WriteDefruleModuleHeaderEntry(v6, Enum, maxIndices, moduleCount);
    moduleFile = Rules_ConstructCodeFileClose(v7, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
    theDefrule = Rules_GetNextDefrule(0);
    if ( theDefrule )
      break;
LABEL_15:
    ++moduleCount;
    ++moduleArrayCount;
    Enum = Module_NextEnum(Enum);
    if ( !Enum )
      goto LABEL_16;
  }
  while ( 1 )
  {
    v8 = Rules_ConstructCodeFileOpen(
           defruleFile,
           v30,
           v33,
           v31,
           &fileCount,
           defruleArrayVersion,
           v32,
           (char)aStructDefrule,
           *(const char **)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 4),
           0,
           0);
    v9 = v8;
    if ( !v8 )
    {
      Rules_CloseDefruleCodeFiles(moduleFile, 0, maxIndices, joinFile);
      return 0;
    }
    Rules_WriteDefruleStructEntry(v8, theDefrule, maxIndices, v33, moduleCount);
    v10 = v9;
    ++defruleArrayCount;
    v11 = theDefrule;
    v12 = Rules_ConstructCodeFileClose(v10, &defruleArrayCount, maxIndices, &defruleArrayVersion, 0, 0);
    theJoin = *(_DWORD *)(v11 + 44);
    defruleFile = v12;
    if ( theJoin )
      break;
LABEL_12:
    if ( *(_DWORD *)(theDefrule + 48) )
      theDefrule = *(_DWORD *)(theDefrule + 48);
    else
      theDefrule = Rules_GetNextDefrule(theDefrule);
    if ( !theDefrule )
      goto LABEL_15;
  }
  while ( (*(_BYTE *)theJoin & 0x20) == 0 )
  {
LABEL_9:
    if ( (*(_BYTE *)theJoin & 4) != 0 )
      v16 = *(_DWORD *)(theJoin + 16);
    else
      v16 = *(_DWORD *)(theJoin + 24);
    theJoin = v16;
    if ( !v16 )
      goto LABEL_12;
  }
  v14 = Rules_ConstructCodeFileOpen(
          joinFile,
          v30,
          v33,
          v31,
          &fileCount,
          joinArrayVersion,
          v32,
          (char)aStructJoinnode,
          *(const char **)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
          0,
          0);
  v15 = v14;
  if ( v14 )
  {
    Rules_WriteJoinNodeStructEntry(v14, theJoin, maxIndices, v33);
    ++joinArrayCount;
    joinFile = Rules_ConstructCodeFileClose(v15, &joinArrayCount, maxIndices, &joinArrayVersion, 0, 0);
    goto LABEL_9;
  }
  Rules_CloseDefruleCodeFiles(moduleFile, defruleFile, maxIndices, 0);
  return 0;
}
// 54E884: using guessed type int dword_54E884;

//----- (004BFF90) --------------------------------------------------------
int  Rules_CloseDefruleCodeFiles(int moduleFile, int defruleFile, int maxIndices, int joinFile)
{
  int result; // eax
  int count; // [esp+0h] [ebp-14h] BYREF
  _DWORD arrayVersion[4]; // [esp+4h] [ebp-10h] BYREF

  result = joinFile;
  count = maxIndices;
  arrayVersion[0] = 0;
  if ( joinFile )
    result = Rules_ConstructCodeFileClose(joinFile, &count, maxIndices, arrayVersion, 0, 0);
  if ( defruleFile )
  {
    count = maxIndices;
    result = Rules_ConstructCodeFileClose(defruleFile, &count, maxIndices, arrayVersion, 0, 0);
  }
  if ( moduleFile )
  {
    count = maxIndices;
    return Rules_ConstructCodeFileClose(moduleFile, &count, maxIndices, arrayVersion, 0, 0);
  }
  return result;
}

//----- (004C0010) --------------------------------------------------------
int  Rules_WriteDefruleModuleHeaderEntry(int theFile, int theModule, int maxIndices, int moduleCount)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, theFile, (int)asc_50AAE8, v10);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v5, v6, g_DefruleConstructClass, *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, theFile, (int)aNull_22, v11);
}
// 4C001B: variable 'v10' is possibly undefined
// 4C0038: variable 'v5' is possibly undefined
// 4C0038: variable 'v6' is possibly undefined
// 4C0043: variable 'v8' is possibly undefined
// 4C0043: variable 'v7' is possibly undefined
// 4C0043: variable 'v11' is possibly undefined
// 54E64C: using guessed type int dword_54E64C;
// 54E884: using guessed type int dword_54E884;

//----- (004C0060) --------------------------------------------------------
int  Rules_WriteDefruleStructEntry(int theFile, int theDefrule, int maxIndices, char imageID, int moduleCount)
{
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // ecx
  char v22; // [esp+0h] [ebp-10h]
  char v23; // [esp+0h] [ebp-10h]
  char v24; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(maxIndices, theDefrule, theFile, (int)asc_50AAE8, imageID);
  Rules_WriteConstructHeaderToCode(theFile, theDefrule, maxIndices, moduleCount, **(_DWORD **)(g_ClipsDefruleCodeGenItem + 20), *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 4));
  Output_WriteFormatted(v8, *(_DWORD *)(theDefrule + 20), theFile, (int)aDDDDDDDD, *(_DWORD *)(theDefrule + 20));
  Rules_ExpressionToCode(theFile, *(__int16 **)(theDefrule + 32), v9, maxIndices);
  Output_WriteFormatted(v11, v10, theFile, (int)asc_50AB10, v22);
  Rules_ExpressionToCode(theFile, *(__int16 **)(theDefrule + 36), v12, maxIndices);
  Output_WriteFormatted(v14, v13, theFile, (int)asc_50AB10, v23);
  v16 = *(_DWORD *)(theDefrule + 40);
  if ( v16 )
    Output_WriteFormatted(
      v16,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)aSD_LdLd_6,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v15, theFile, (int)aNull_23, v24);
  v18 = *(_DWORD *)(theDefrule + 44);
  if ( v18 )
    Output_WriteFormatted(
      v18,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)aSD_LdLd_6,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v17, theFile, (int)aNull_23, v24);
  v20 = *(_DWORD *)(theDefrule + 48);
  if ( v20 )
    return Output_WriteFormatted(
             v20,
             *(_DWORD *)(v20 + 12) % maxIndices,
             theFile,
             (int)aSD_LdLd_7,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(0, v19, theFile, (int)aNull_24, v24);
}
// 4C00E9: variable 'v8' is possibly undefined
// 4C00F6: variable 'v9' is possibly undefined
// 4C0101: variable 'v11' is possibly undefined
// 4C0101: variable 'v10' is possibly undefined
// 4C0101: variable 'v22' is possibly undefined
// 4C010E: variable 'v12' is possibly undefined
// 4C0119: variable 'v14' is possibly undefined
// 4C0119: variable 'v13' is possibly undefined
// 4C0119: variable 'v23' is possibly undefined
// 4C0132: variable 'v15' is possibly undefined
// 4C0132: variable 'v24' is possibly undefined
// 4C0206: variable 'v17' is possibly undefined
// 4C0219: variable 'v19' is possibly undefined
// 54E884: using guessed type int dword_54E884;

//----- (004C0230) --------------------------------------------------------
int  Rules_WriteJoinNodeStructEntry(int theFile, int theJoin, int maxIndices, char imageID)
{
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int rightSideEntry; // edx
  int patternParser; // eax
  int v15; // ebp
  int v16; // edx
  int v17; // ecx
  int nextLevel; // ebx
  int v19; // edx
  int v20; // ecx
  int v21; // edx
  int v22; // ecx
  int v23; // edx
  int v24; // ecx
  int v25; // edx
  int v26; // ecx
  int v28; // edx
  int v29; // ecx
  char v30; // [esp+0h] [ebp-14h]
  char v31; // [esp+0h] [ebp-14h]
  char v32; // [esp+0h] [ebp-14h]

  *(_BYTE *)theJoin &= ~0x20u;
  Output_WriteFormatted(maxIndices, theJoin, theFile, (int)aDDDD00DD0, *(_BYTE *)theJoin & 1);
  Output_WriteFormatted(v7, v6, theFile, (int)aNull_23, imageID);
  Rules_WriteExpressionRefToCode(theFile, *(__int16 **)(v8 + 12), v9, imageID);
  Output_WriteFormatted(v11, v10, theFile, (int)asc_50AB10, v30);
  rightSideEntry = *(_DWORD *)(theJoin + 16);
  if ( !rightSideEntry )
    goto LABEL_4;
  if ( (*(_BYTE *)theJoin & 4) != 0 )
  {
    Output_WriteFormatted(
      *(_DWORD *)(theJoin + 16),
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)aSD_LdLd_6,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  }
  else
  {
    patternParser = Rules_GetPatternParserByTypeID(*(_DWORD *)theJoin << 23 >> 29);
    v12 = *(_DWORD *)(patternParser + 84);
    v15 = patternParser;
    if ( !v12 )
    {
LABEL_4:
      Output_WriteFormatted(v12, rightSideEntry, theFile, (int)aNull_23, v31);
      goto LABEL_5;
    }
    Output_WriteFormatted(v12, theFile, theFile, (int)aVs_0, v31);
    (*(void (__thiscall **)(int))(v15 + 84))(maxIndices);
    Output_WriteFormatted(v29, v28, theFile, (int)asc_50AB10, v32);
  }
LABEL_5:
  nextLevel = *(_DWORD *)(theJoin + 20);
  if ( nextLevel )
    Output_WriteFormatted(v17, *(_DWORD *)(nextLevel + 4) % maxIndices, theFile, (int)aSD_LdLd_6, *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v17, v16, theFile, (int)aNull_23, v31);
  if ( *(_DWORD *)(theJoin + 24) )
    Output_WriteFormatted(
      *(_DWORD *)(theJoin + 24),
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)aSD_LdLd_6,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v20, v19, theFile, (int)aNull_23, v31);
  v22 = *(_DWORD *)(theJoin + 28);
  if ( v22 )
    Output_WriteFormatted(
      v22,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)aSD_LdLd_6,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v21, theFile, (int)aNull_23, v31);
  v24 = *(_DWORD *)(theJoin + 32);
  if ( v24 )
    Output_WriteFormatted(
      v24,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)aSD_LdLd_6,
      *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v23, theFile, (int)aNull_23, v31);
  v26 = *(_DWORD *)(theJoin + 36);
  if ( v26 )
    return Output_WriteFormatted(
             v26,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 4),
             theFile,
             (int)aSD_LdLd_7,
             *(_DWORD *)(*(_DWORD *)(g_ClipsDefruleCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(0, v25, theFile, (int)aNull_24, v31);
}
// 4C028B: variable 'v7' is possibly undefined
// 4C028B: variable 'v6' is possibly undefined
// 4C0295: variable 'v8' is possibly undefined
// 4C0298: variable 'v9' is possibly undefined
// 4C02A3: variable 'v11' is possibly undefined
// 4C02A3: variable 'v10' is possibly undefined
// 4C02A3: variable 'v30' is possibly undefined
// 4C02DB: variable 'v12' is possibly undefined
// 4C02DB: variable 'v13' is possibly undefined
// 4C02DB: variable 'v31' is possibly undefined
// 4C02F4: variable 'v17' is possibly undefined
// 4C02F4: variable 'v16' is possibly undefined
// 4C030D: variable 'v20' is possibly undefined
// 4C030D: variable 'v19' is possibly undefined
// 4C0326: variable 'v21' is possibly undefined
// 4C033F: variable 'v23' is possibly undefined
// 4C0358: variable 'v25' is possibly undefined
// 4C0389: variable 'v29' is possibly undefined
// 4C0389: variable 'v28' is possibly undefined
// 4C0389: variable 'v32' is possibly undefined
// 54E884: using guessed type int dword_54E884;

//----- (004C0510) --------------------------------------------------------
int  Rules_WriteJoinHashStructRef(int theFile, int count)
{
  return Output_WriteFormatted(count, **(_DWORD **)(g_ClipsDefruleCodeGenItem + 20), theFile, (int)aMihsSD_DD_4, **(_DWORD **)(g_ClipsDefruleCodeGenItem + 20));
}
// 54E884: using guessed type int dword_54E884;

//----- (004C0550) --------------------------------------------------------
int Rules_CreateLHSParseNode()
{
  _DWORD *freeNode; // edx
  _BYTE *newConstraint; // ecx
  int v2; // ecx
  char v3; // ah
  char v4; // dl
  signed int minValueExpr; // eax
  int v6; // ecx
  signed int maxValueExpr; // eax
  int v8; // ecx
  signed int minFieldsExpr; // eax
  int v10; // ecx
  signed int maxFieldsExpr; // eax
  int v12; // ecx

  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 168);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 168);
    *(_DWORD *)(g_ClipsMemoryTable + 168) = *freeNode;
    newConstraint = (_BYTE *)g_ClipsMemFreeListTemp;
  }
  else
  {
    newConstraint = (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)0x2A);
  }
  Rules_SetLHSParseNodeDefaultFlags(newConstraint, 1);
  v3 = *(_BYTE *)(v2 + 2);
  v4 = *(_BYTE *)(v2 + 1);
  *(_DWORD *)(v2 + 6) = 0;
  *(_BYTE *)(v2 + 2) = v3 | 1;
  *(_BYTE *)(v2 + 1) = v4 & 1;
  minValueExpr = AST_NewNode(2, g_Clips_NegativeInfinitySymbol);
  *(_DWORD *)(v6 + 10) = minValueExpr;
  maxValueExpr = AST_NewNode(2, g_ClipsPositiveInfinitySymbol);
  *(_DWORD *)(v8 + 14) = maxValueExpr;
  minFieldsExpr = AST_NewNode(1, g_CLIPS_IntegerZeroValueNode);
  *(_DWORD *)(v10 + 18) = minFieldsExpr;
  maxFieldsExpr = AST_NewNode(2, g_ClipsPositiveInfinitySymbol);
  *(_DWORD *)(v12 + 34) = -1;
  *(_DWORD *)(v12 + 38) = 0;
  *(_DWORD *)(v12 + 26) = 0;
  *(_DWORD *)(v12 + 30) = 0;
  *(_DWORD *)(v12 + 22) = maxFieldsExpr;
  return v12;
}
// 4C0586: variable 'v2' is possibly undefined
// 4C05AF: variable 'v6' is possibly undefined
// 4C05C2: variable 'v8' is possibly undefined
// 4C05D5: variable 'v10' is possibly undefined
// 4C05E8: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;
// 54DD6C: using guessed type int dword_54DD6C;

//----- (004C0620) --------------------------------------------------------
_BYTE * Rules_SetLHSParseNodeDefaultFlags(_BYTE *result, int justOne)
{
  char v2; // cl
  int v3; // edx

  if ( justOne )
  {
    LOBYTE(justOne) = 1;
    v2 = 0;
  }
  else
  {
    v2 = 1;
  }
  *result &= ~1u;
  *(_DWORD *)result |= justOne & 1;
  v3 = v2 & 1;
  *result &= ~2u;
  *(_DWORD *)result |= 2 * v3;
  *result &= ~4u;
  *(_DWORD *)result |= 4 * v3;
  *result &= ~8u;
  *(_DWORD *)result |= 8 * v3;
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * v3;
  *result &= ~0x20u;
  *(_DWORD *)result |= 32 * v3;
  *result &= ~0x40u;
  *(_DWORD *)result |= v3 << 6;
  *result &= ~0x80u;
  *(_DWORD *)result |= v3 << 7;
  result[1] &= ~1u;
  *(_DWORD *)result |= v3 << 8;
  return result;
}

//----- (004C06C0) --------------------------------------------------------
int  Rules_CloneLHSParseNode(int *theConstraint)
{
  int *v1; // ecx
  _DWORD *freeNode; // ebx
  _BYTE *theCopy; // edx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  signed int restrictionListCopy; // eax
  int v22; // edx
  int v23; // ecx
  signed int minValueCopy; // eax
  int v25; // edx
  int v26; // ecx
  signed int maxValueCopy; // eax
  int v28; // edx
  int v29; // ecx
  signed int minFieldsCopy; // eax
  int v31; // edx
  int v32; // ecx
  signed int maxFieldsCopy; // eax
  int v34; // edx
  int v35; // ecx
  int multifieldCopy; // eax
  int v37; // edx

  v1 = theConstraint;
  if ( !theConstraint )
    return 0;
  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 168);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 168);
    *(_DWORD *)(g_ClipsMemoryTable + 168) = *freeNode;
    theCopy = (_BYTE *)g_ClipsMemFreeListTemp;
  }
  else
  {
    theCopy = (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)0x2A);
  }
  v4 = *v1;
  *theCopy &= ~1u;
  *(_DWORD *)theCopy |= v4 & 1;
  v5 = *v1;
  *theCopy &= ~2u;
  *(_DWORD *)theCopy |= v5 & 2;
  v6 = *v1;
  *theCopy &= ~4u;
  *(_DWORD *)theCopy |= v6 & 4;
  v7 = *v1;
  *theCopy &= ~8u;
  *(_DWORD *)theCopy |= v7 & 8;
  v8 = *v1;
  *theCopy &= ~0x10u;
  *(_DWORD *)theCopy |= v8 & 0x10;
  v9 = *v1;
  *theCopy &= ~0x20u;
  *(_DWORD *)theCopy |= v9 & 0x20;
  v10 = *v1;
  *theCopy &= ~0x40u;
  *(_DWORD *)theCopy |= v10 & 0x40;
  v11 = *v1;
  *theCopy &= ~0x80u;
  *(_DWORD *)theCopy |= v11 & 0x80;
  v12 = *v1;
  theCopy[1] &= ~0x80u;
  *(_DWORD *)theCopy |= v12 & 0x8000;
  v13 = *v1;
  theCopy[2] &= ~1u;
  *(_DWORD *)theCopy |= v13 & 0x10000;
  v14 = *v1;
  theCopy[1] &= ~1u;
  *(_DWORD *)theCopy |= v14 & 0x100;
  v15 = *v1;
  theCopy[1] &= ~2u;
  *(_DWORD *)theCopy |= v15 & 0x200;
  v16 = *v1;
  theCopy[1] &= ~4u;
  *(_DWORD *)theCopy |= v16 & 0x400;
  v17 = *v1;
  theCopy[1] &= ~8u;
  *(_DWORD *)theCopy |= v17 & 0x800;
  v18 = *v1;
  theCopy[1] &= ~0x10u;
  *(_DWORD *)theCopy |= v18 & 0x1000;
  v19 = *v1;
  theCopy[1] &= ~0x20u;
  *(_DWORD *)theCopy |= v19 & 0x2000;
  v20 = *v1;
  theCopy[1] &= ~0x40u;
  *(_DWORD *)theCopy |= v20 & 0x4000;
  restrictionListCopy = AST_CloneNodeList(*(int *)((char *)v1 + 6));
  *(_DWORD *)(v22 + 6) = restrictionListCopy;
  minValueCopy = AST_CloneNodeList(*(_DWORD *)(v23 + 10));
  *(_DWORD *)(v25 + 10) = minValueCopy;
  maxValueCopy = AST_CloneNodeList(*(_DWORD *)(v26 + 14));
  *(_DWORD *)(v28 + 14) = maxValueCopy;
  minFieldsCopy = AST_CloneNodeList(*(_DWORD *)(v29 + 18));
  *(_DWORD *)(v31 + 18) = minFieldsCopy;
  maxFieldsCopy = AST_CloneNodeList(*(_DWORD *)(v32 + 22));
  *(_DWORD *)(v34 + 34) = -1;
  *(_DWORD *)(v34 + 38) = 0;
  *(_DWORD *)(v34 + 22) = maxFieldsCopy;
  multifieldCopy = Rules_CloneLHSParseNode(*(_DWORD *)(v35 + 26));
  *(_DWORD *)(v37 + 30) = 0;
  *(_DWORD *)(v37 + 26) = multifieldCopy;
  return v37;
}
// 4C06FA: variable 'v1' is possibly undefined
// 4C0811: variable 'v22' is possibly undefined
// 4C0814: variable 'v23' is possibly undefined
// 4C081C: variable 'v25' is possibly undefined
// 4C081F: variable 'v26' is possibly undefined
// 4C0827: variable 'v28' is possibly undefined
// 4C082A: variable 'v29' is possibly undefined
// 4C0832: variable 'v31' is possibly undefined
// 4C0835: variable 'v32' is possibly undefined
// 4C083D: variable 'v34' is possibly undefined
// 4C084E: variable 'v35' is possibly undefined
// 4C0856: variable 'v37' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C0880) --------------------------------------------------------
int  Rules_SetLHSParseNodeExtendedFlags(int result, int justOne)
{
  char v2; // cl

  if ( justOne )
  {
    LOBYTE(justOne) = 1;
    v2 = 0;
  }
  else
  {
    v2 = 1;
  }
  *(_BYTE *)(result + 1) &= ~2u;
  *(_DWORD *)result |= (justOne & 1) << 9;
  *(_BYTE *)(result + 1) &= ~4u;
  *(_DWORD *)result |= (v2 & 1) << 10;
  *(_BYTE *)(result + 1) &= ~8u;
  *(_DWORD *)result |= (v2 & 1) << 11;
  *(_BYTE *)(result + 1) &= ~0x10u;
  *(_DWORD *)result |= (v2 & 1) << 12;
  *(_BYTE *)(result + 1) &= ~0x20u;
  *(_DWORD *)result |= (v2 & 1) << 13;
  *(_BYTE *)(result + 1) &= ~0x40u;
  *(_DWORD *)result |= (v2 & 1) << 14;
  return result;
}

//----- (004C0900) --------------------------------------------------------
signed int  Rules_UpdateCETypeFlag(unsigned int theType, int constraints)
{
  int returnValue; // ecx
  int anyAllowedFlag; // ecx

  returnValue = 1;
  if ( theType >= 6 )
  {
    if ( theType > 6 )
    {
      if ( theType >= 0x67 )
      {
        if ( theType <= 0x67 )
        {
          anyAllowedFlag = *(_DWORD *)constraints & 1;
          *(_BYTE *)constraints |= 1u;
          return anyAllowedFlag;
        }
        if ( theType >= 0x6F )
        {
          if ( theType > 0x6F )
          {
            if ( theType == 112 )
            {
              returnValue = (*(_DWORD *)constraints << 26 >> 31) | (*(_DWORD *)constraints << 25 >> 31);
              *(_BYTE *)constraints |= 0x60u;
            }
          }
          else
          {
            returnValue = (*(_DWORD *)constraints << 29 >> 31) | (*(_DWORD *)constraints << 30 >> 31);
            *(_BYTE *)constraints |= 6u;
          }
        }
        else if ( theType == 110 )
        {
          returnValue = (*(_DWORD *)constraints << 28 >> 31) | (*(_DWORD *)constraints << 27 >> 31);
          *(_BYTE *)constraints |= 0x18u;
        }
      }
      else if ( theType > 7 )
      {
        if ( theType == 8 )
        {
          returnValue = *(_DWORD *)constraints << 26 >> 31;
          *(_BYTE *)constraints |= 0x20u;
        }
      }
      else
      {
        returnValue = *(_DWORD *)constraints << 25 >> 31;
        *(_BYTE *)constraints |= 0x40u;
      }
    }
    else
    {
      returnValue = *(_DWORD *)constraints << 23 >> 31;
      *(_BYTE *)(constraints + 1) |= 1u;
    }
  }
  else if ( theType >= 2 )
  {
    if ( theType > 2 )
    {
      if ( theType >= 4 )
      {
        if ( theType > 4 )
        {
          returnValue = *(_DWORD *)constraints << 24 >> 31;
          *(_BYTE *)constraints |= 0x80u;
        }
        else
        {
          returnValue = *(_DWORD *)constraints << 16 >> 31;
          *(_BYTE *)(constraints + 1) |= 0x80u;
        }
      }
      else
      {
        returnValue = *(_DWORD *)constraints << 29 >> 31;
        *(_BYTE *)constraints |= 4u;
      }
    }
    else
    {
      returnValue = *(_DWORD *)constraints << 30 >> 31;
      *(_BYTE *)constraints |= 2u;
    }
  }
  else if ( theType )
  {
    returnValue = *(_DWORD *)constraints << 27 >> 31;
    *(_BYTE *)constraints |= 0x10u;
  }
  else
  {
    returnValue = *(_DWORD *)constraints << 28 >> 31;
    *(_BYTE *)constraints |= 8u;
  }
  *(_BYTE *)constraints &= ~1u;
  return returnValue;
}
// 4C092F: conditional instruction was optimized away because eax.4 is in (==1|9..66|68..6D|>=71u)
// 4C0950: conditional instruction was optimized away because eax.4==6
// 4C097B: conditional instruction was optimized away because eax.4==7
// 4C0997: conditional instruction was optimized away because eax.4==67
// 4C09E9: conditional instruction was optimized away because eax.4==6F
// 4C0A5A: conditional instruction was optimized away because eax.4==2
// 4C0A7C: conditional instruction was optimized away because eax.4==3
// 4C0A99: conditional instruction was optimized away because eax.4==4
// 4C0ACB: conditional instruction was optimized away because eax.4==5

//----- (004C0AE0) --------------------------------------------------------
signed int  Rules_CompareBoundedCEValues(int type1, int value1, int value2, int type2)
{
  int intValue1; // eax
  int intValue2; // edi
  double convertedValue1; // st7
  double floatValue1; // st7
  double convertedValue2; // [esp+0h] [ebp-18h]

  if ( value1 == value2 )
    return 2;
  if ( value1 == g_ClipsPositiveInfinitySymbol )
    return 1;
  if ( value1 == g_Clips_NegativeInfinitySymbol || value2 == g_ClipsPositiveInfinitySymbol )
    return 0;
  if ( value2 == g_Clips_NegativeInfinitySymbol )
    return 1;
  if ( type1 == 1 && type2 == 1 )
  {
    intValue1 = *(_DWORD *)(value1 + 16);
    intValue2 = *(_DWORD *)(value2 + 16);
    if ( intValue1 >= intValue2 )
    {
      if ( intValue1 > intValue2 )
        return 1;
      return 2;
    }
    return 0;
  }
  if ( !type1 && !type2 )
  {
    if ( *(double *)(value1 + 16) >= *(double *)(value2 + 16) )
    {
      if ( *(double *)(value1 + 16) > *(double *)(value2 + 16) )
        return 1;
      return 2;
    }
    return 0;
  }
  if ( type1 != 1 || type2 )
  {
    if ( type1 || type2 != 1 )
    {
      return -1;
    }
    else
    {
      convertedValue2 = (double)*(int *)(value2 + 16);
      floatValue1 = *(double *)(value1 + 16);
      if ( floatValue1 < convertedValue2 )
        return 0;
      if ( floatValue1 > convertedValue2 )
        return 1;
      return 2;
    }
  }
  else
  {
    convertedValue1 = (double)*(int *)(value1 + 16);
    if ( convertedValue1 < *(double *)(value2 + 16) )
      return 0;
    if ( convertedValue1 <= *(double *)(value2 + 16) )
      return 2;
    return 1;
  }
}
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004C0BC0) --------------------------------------------------------
_BYTE * Rules_BuildLHSNodeFromToken(__int16 *theExpression)
{
  __int16 exprType; // bx
  _BYTE *constraints; // eax
  int v3; // edx
  char v4; // bl
  __int16 valueType; // si
  _BYTE *v6; // ecx
  char v7; // al
  signed int restrictionExpr; // eax
  int v9; // ecx
  _BYTE *result; // eax

  if ( theExpression )
  {
    exprType = *theExpression;
    if ( *theExpression == 15 || exprType == 16 || exprType == 11 || exprType == 12 || exprType == 13 || exprType == 14 )
    {
      result = (_BYTE *)Rules_CreateLHSParseNode();
      result[1] |= 0x80u;
    }
    else if ( exprType == 10 )
    {
      return Rules_ApplyCEKeywordFlags();
    }
    else
    {
      constraints = (_BYTE *)Rules_CreateLHSParseNode();
      v4 = *constraints & 0xFE;
      *constraints = v4;
      valueType = *(_WORD *)v3;
      v6 = constraints;
      if ( *(_WORD *)v3 )
      {
        switch ( valueType )
        {
          case 1:
            *(_WORD *)constraints |= 0x2010u;
            break;
          case 2:
            *(_WORD *)constraints |= 0x402u;
            break;
          case 3:
            *(_WORD *)constraints |= 0x804u;
            break;
          case 8:
            *(_WORD *)constraints |= 0x4020u;
            break;
          case 7:
            *constraints = v4 | 0x40;
            break;
        }
      }
      else
      {
        *(_WORD *)constraints |= 0x1008u;
      }
      v7 = *constraints;
      if ( (*v6 & 8) != 0 || (v7 & 0x10) != 0 || (v7 & 2) != 0 || (v7 & 4) != 0 || (v7 & 0x20) != 0 )
      {
        restrictionExpr = AST_NewNode(*(_WORD *)v3, *(_DWORD *)(v3 + 2));
        *(_DWORD *)(v9 + 6) = restrictionExpr;
        return (_BYTE *)v9;
      }
      else
      {
        return v6;
      }
    }
  }
  else
  {
    result = (_BYTE *)Rules_CreateLHSParseNode();
    *result &= ~1u;
  }
  return result;
}
// 4C0C0F: variable 'v3' is possibly undefined
// 4C0C37: variable 'v9' is possibly undefined

//----- (004C0D30) --------------------------------------------------------
_BYTE *Rules_ApplyCEKeywordFlags()
{
  _BYTE *result; // eax
  int theFunction; // ecx

  result = (_BYTE *)Rules_CreateLHSParseNode();
  *result &= ~1u;
  if ( (unsigned __int8)(*(_BYTE *)(theFunction + 8) - 97) <= 0x17u )
  {
    switch ( *(_BYTE *)(theFunction + 8) )
    {
      case 'a':
        *result |= 0x80u;
        break;
      case 'b':
      case 'c':
      case 'w':
        *result |= 2u;
        break;
      case 'd':
      case 'f':
        *result |= 8u;
        break;
      case 'e':
      case 'g':
      case 'h':
      case 'p':
      case 'q':
      case 'r':
      case 't':
      case 'v':
        return result;
      case 'i':
      case 'l':
        *result |= 0x10u;
        break;
      case 'j':
        *result |= 0x26u;
        break;
      case 'k':
        *result |= 6u;
        break;
      case 'm':
        *(_DWORD *)result &= 0xFFFE7FFF;
        result[1] |= 0x80u;
        break;
      case 'n':
        *result |= 0x18u;
        break;
      case 'o':
        *result |= 0x20u;
        break;
      case 's':
        *result |= 4u;
        break;
      case 'u':
        *(_WORD *)result |= 0x8001u;
        break;
      case 'x':
        *result |= 0x40u;
        break;
    }
  }
  return result;
}
// 4C0D3D: variable 'v1' is possibly undefined

//----- (004C0E40) --------------------------------------------------------
_BYTE *Rules_ApplyPatternKeywordFlags()
{
  _BYTE *result; // eax
  char v1; // bl
  int restrictionCode; // ecx

  result = (_BYTE *)Rules_CreateLHSParseNode();
  v1 = *result & 0xFE;
  *result = v1;
  switch ( restrictionCode )
  {
    case 'a':
      *result = v1 | 0x80;
      break;
    case 'd':
    case 'f':
      *result |= 8u;
      break;
    case 'e':
      *result = v1 | 0x62;
      break;
    case 'g':
      *result = v1 | 0x1A;
      break;
    case 'h':
      *(_WORD *)result |= 0x172u;
      break;
    case 'i':
    case 'l':
      *result |= 0x10u;
      break;
    case 'j':
      *result = v1 | 0x26;
      break;
    case 'k':
      *result = v1 | 6;
      break;
    case 'm':
      *(_DWORD *)result &= 0xFFFE7FFF;
      result[1] |= 0x80u;
      break;
    case 'n':
      *result = v1 | 0x18;
      break;
    case 'o':
      *result = v1 | 0x20;
      break;
    case 'p':
      *result = v1 | 0x22;
      break;
    case 'q':
      *(_WORD *)result |= 0x8006u;
      break;
    case 's':
      *result = v1 | 4;
      break;
    case 'u':
      *(_WORD *)result |= 0x8001u;
      break;
    case 'w':
      *result = v1 | 2;
      break;
    case 'x':
      *result = v1 | 0x40;
      break;
    case 'y':
      result[1] |= 1u;
      break;
    case 'z':
      *(_WORD *)result |= 0x112u;
      break;
    default:
      return result;
  }
  return result;
}
// 4C0E5B: variable 'v2' is possibly undefined

//----- (004C0F50) --------------------------------------------------------
int Module_RegisterDefmoduleCommands()
{
  int v0; // ecx

  Rules_AddClearFunction((int)aDefmodule_0, (int)Module_ClearAllModulesResetToMain, 2000);
  Rules_AddSaveFunction((int)aDefmodule_0, (int)Module_SaveAllPPFormsToFile, 1100);
  Rules_RegisterHostFunction(aGetDefmoduleLi, 109, v0, (int)Module_GetDefmoduleNameListCommand, (int)a00_10);
  Rules_RegisterHostFunction(aListDefmodules, 118, (int)aListdefmodules, (int)Module_ListDefmodulesCommand, (int)a00_10);
  Rules_RegisterHostFunction(aPpdefmodule, 118, (int)aPpdefmodulecom, (int)Module_PPDefmoduleCommand, (int)a11w_9);
  Module_RegisterBsaveBloadHandlers();
  return Compiler_RegisterModuleCodeItem();
}
// 4C0F94: variable 'v0' is possibly undefined
// 4C0FF0: using guessed type int sub_4C0FF0();

//----- (004C0FF0) --------------------------------------------------------
int Module_ClearAllModulesResetToMain()
{
  int result; // eax

  result = Rules_IsBloaded();
  if ( result != 1 )
  {
    Module_RemoveAllModules();
    result = Module_CreateMainModule();
    g_Module_MainRedefinable = 1;
  }
  return result;
}
// 4C0FF0: using guessed type int sub_4C0FF0();
// 51A9C4: using guessed type int dword_51A9C4;

//----- (004C1020) --------------------------------------------------------
int  Module_SaveAllPPFormsToFile(signed int logicalName)
{
  int result; // eax
  int i; // ecx
  char *ppForm; // eax
  int v5; // ecx
  int v6; // ecx

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ppForm = (char *)Module_GetPPForm(i);
    if ( ppForm )
    {
      Output_WriteLongString(logicalName, ppForm);
      Output_Write(logicalName, (int)asc_50ABFC, v6);
    }
    result = Module_NextEnum(v5);
  }
  return result;
}
// 4C104D: variable 'v6' is possibly undefined
// 4C1054: variable 'v5' is possibly undefined

//----- (004C1070) --------------------------------------------------------
_DWORD * Module_GetDefmoduleNameListCommand(_DWORD *returnValue)
{
  return Module_BuildNameListMultifield(returnValue, (int (*)(void))Module_NextEnum, (int (*)(void))Module_GetName);
}

//----- (004C1090) --------------------------------------------------------
_BYTE * Module_PPDefmoduleCommand(int a1, double a2)
{
  _BYTE *result; // eax

  result = (_BYTE *)Rules_GetConstructNameArg((int)aDefmoduleNam_3, a1, a2);
  if ( result )
    return (_BYTE *)Module_PrintPPFormByName(result, (signed int)g_IO_LogicalName_WDisplay);
  return result;
}
// 51A624: using guessed type char *off_51A624;

//----- (004C10C0) --------------------------------------------------------
signed int  Module_PrintPPFormByName(_BYTE *defmoduleName, signed int logicalName)
{
  int *theModule; // eax
  int v4; // ecx
  int v5; // edx
  char *ppForm; // eax

  theModule = Module_FindByName(defmoduleName);
  if ( theModule )
  {
    if ( Module_GetPPForm((int)theModule) )
    {
      ppForm = (char *)Module_GetPPForm(v5);
      Output_WriteLongString(logicalName, ppForm);
    }
    return 1;
  }
  else
  {
    Rules_ReportCantFindItem(v4, v4);
    return 0;
  }
}
// 4C10F5: variable 'v5' is possibly undefined
// 4C10E9: variable 'v4' is possibly undefined

//----- (004C1110) --------------------------------------------------------
int Module_ListDefmodulesCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Module_PrintAllNamesWithTally((int)g_IO_LogicalName_WDisplay);
  return result;
}
// 51A624: using guessed type char *off_51A624;

//----- (004C1140) --------------------------------------------------------
int  Module_PrintAllNamesWithTally(int logicalName)
{
  int moduleCount; // edi
  int i; // ecx
  int Name; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  moduleCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v7) )
  {
    Name = Module_GetName(i);
    Output_Write(logicalName, Name, v5);
    Output_Write(logicalName, (int)asc_50ABFC, v6);
    ++moduleCount;
  }
  return Rules_PrintTally(logicalName, moduleCount, (int)aDefmodules_0, (int)aDefmodule_0);
}
// 4C1161: variable 'v5' is possibly undefined
// 4C116D: variable 'v6' is possibly undefined
// 4C1175: variable 'v7' is possibly undefined

//----- (004C11A0) --------------------------------------------------------
int Module_GetModuleCount()
{
  return g_Module_DefModuleCount;
}
// 54E888: using guessed type int dword_54E888;

//----- (004C11B0) --------------------------------------------------------
int  Module_SetModuleCount(int result)
{
  g_Module_DefModuleCount = result;
  return result;
}
// 54E888: using guessed type int dword_54E888;

//----- (004C11C0) --------------------------------------------------------
_DWORD * Module_AddAfterModuleDefinedCallback(int name, int func, int priority)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, priority, g_Module_AfterDefineCallbackList, func);
  g_Module_AfterDefineCallbackList = (int)result;
  return result;
}
// 51B36C: using guessed type int dword_51B36C;

//----- (004C11E0) --------------------------------------------------------
int * Module_RegisterImportExportConstructType(int theName, int theType)
{
  int v2; // ecx
  _DWORD *v3; // ebx
  int *result; // eax

  v2 = theName;
  v3 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( v3 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *v3;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = v2;
  result[1] = theType;
  result[2] = g_Module_PortConstructList;
  g_Module_PortConstructList = (int)result;
  return result;
}
// 4C1200: variable 'v2' is possibly undefined
// 51B368: using guessed type int dword_51B368;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C1230) --------------------------------------------------------
signed int  Module_ParseDefmoduleConstruct(int readSource)
{
  int *redefiningMainModule; // ebp
  int moduleNameString; // ecx
  int moduleName; // ebx
  _DWORD *v5; // edx
  int *newDefmodule; // eax
  int v7; // ecx
  signed int parseError; // edx
  _DWORD *v9; // ecx
  _DWORD *importSpec; // eax
  int nextImportSpec; // ebx
  _DWORD *exportSpec; // edx
  int nextExportSpec; // ebx
  _DWORD *i; // eax
  int importTypeSym; // edi
  int importNameSym; // esi
  _DWORD *j; // eax
  int exportTypeSym; // edx
  int exportNameSym; // esi
  int v21; // ecx
  int moduleIndex; // eax
  int k; // edx
  int v24; // edx
  _DWORD *itemsArray; // eax
  int v26; // ecx
  int itemIndex; // esi
  int itemDescriptor; // edx
  int arrayOffset; // ebx
  int newItemHeader; // eax
  _DWORD *itemHeaderPtr; // eax
  char *ppForm; // eax
  _DWORD inputToken[8]; // [esp+0h] [ebp-20h] BYREF

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  redefiningMainModule = 0;
  IO_OutWriteToken(aDefmodule_6);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  moduleName = Rules_GetConstructNameAndComment(readSource, (int)inputToken, (int (*)(void))Module_FindByName, aDefmodule_7, (int (*)(void))Module_IsRedefinitionOfExistingName, asc_50AC34, 1, 1, 0);
  if ( !moduleName )
    return 1;
  if ( !strcmp_(moduleNameString, aMain_3) )
    redefiningMainModule = Module_FindByName(aMain_3);
  if ( redefiningMainModule )
  {
    v7 = (int)redefiningMainModule;
  }
  else
  {
    v5 = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( v5 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *v5;
      newDefmodule = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDefmodule = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    newDefmodule[7] = 0;
    v7 = (int)newDefmodule;
    *newDefmodule = moduleName;
  }
  *(_DWORD *)(v7 + 12) = 0;
  *(_DWORD *)(v7 + 16) = 0;
  parseError = Module_ParseImportExportClauseList(readSource, inputToken, v7);
  if ( !parseError )
    parseError = Rules_FindMultiImportConflict((int)v9);
  if ( parseError )
  {
    while ( 1 )
    {
      importSpec = (_DWORD *)v9[3];
      if ( !importSpec )
        break;
      nextImportSpec = importSpec[3];
      g_ClipsMemFreeListTemp = v9[3];
      *importSpec = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
      v9[3] = nextImportSpec;
    }
    while ( 1 )
    {
      exportSpec = (_DWORD *)v9[4];
      if ( !exportSpec )
        break;
      nextExportSpec = exportSpec[3];
      g_ClipsMemFreeListTemp = v9[4];
      *exportSpec = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
      v9[4] = nextExportSpec;
    }
    if ( !redefiningMainModule )
    {
      g_ClipsMemFreeListTemp = (int)v9;
      *v9 = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
      return 1;
    }
    return 1;
  }
  if ( redefiningMainModule )
  {
    if ( v9[3] || v9[4] )
      g_Module_MainRedefinable = 0;
  }
  else
  {
    ++*(_DWORD *)(*v9 + 4);
  }
  for ( i = (_DWORD *)v9[3]; i; i = (_DWORD *)i[3] )
  {
    if ( *i )
      ++*(_DWORD *)(*i + 4);
    importTypeSym = i[1];
    if ( importTypeSym )
      ++*(_DWORD *)(importTypeSym + 4);
    importNameSym = i[2];
    if ( importNameSym )
      ++*(_DWORD *)(importNameSym + 4);
  }
  for ( j = (_DWORD *)v9[4]; j; j = (_DWORD *)j[3] )
  {
    if ( *j )
      ++*(_DWORD *)(*j + 4);
    exportTypeSym = j[1];
    if ( exportTypeSym )
      ++*(_DWORD *)(exportTypeSym + 4);
    exportNameSym = j[2];
    if ( exportNameSym )
      ++*(_DWORD *)(exportNameSym + 4);
  }
  if ( !redefiningMainModule )
  {
    if ( g_ClipsModuleItemCount )
    {
      itemsArray = Mem_SmallBlockAlloc(4 * g_ClipsModuleItemCount);
      *(_DWORD *)(v26 + 8) = itemsArray;
      itemIndex = 0;
      itemDescriptor = g_ModuleItemDescriptorListHead;
      if ( g_ClipsModuleItemCount > 0 )
      {
        arrayOffset = 0;
        do
        {
          if ( !itemDescriptor )
            break;
          if ( *(_DWORD *)(itemDescriptor + 8) )
          {
            newItemHeader = (*(int (**)(void))(itemDescriptor + 8))();
            *(_DWORD *)(*(_DWORD *)(v26 + 8) + arrayOffset) = newItemHeader;
            itemHeaderPtr = *(_DWORD **)(arrayOffset + *(_DWORD *)(v26 + 8));
            itemHeaderPtr[1] = 0;
            itemHeaderPtr[2] = 0;
            *itemHeaderPtr = v26;
          }
          else
          {
            *(_DWORD *)(arrayOffset + *(_DWORD *)(v26 + 8)) = 0;
          }
          arrayOffset += 4;
          ++itemIndex;
          itemDescriptor = *(_DWORD *)(itemDescriptor + 28);
        }
        while ( itemIndex < g_ClipsModuleItemCount );
      }
    }
    else
    {
      v9[2] = 0;
    }
  }
  IO_OutWriteToken(asc_50AC40);
  if ( Mem_GetAllocFlag() == 1 )
  {
    *(_DWORD *)(v21 + 4) = 0;
  }
  else
  {
    ppForm = Rules_CopyPPBuffer();
    *(_DWORD *)(v21 + 4) = ppForm;
  }
  if ( !redefiningMainModule )
  {
    if ( g_ClipsDefmoduleListTail )
      *(_DWORD *)(g_ClipsDefmoduleListTail + 28) = v21;
    else
      g_DefmoduleListHead = v21;
    moduleIndex = g_Module_DefModuleCount;
    g_ClipsDefmoduleListTail = v21;
    ++g_Module_DefModuleCount;
    *(_DWORD *)(v21 + 24) = moduleIndex;
  }
  Module_SetCurrent(v21);
  for ( k = g_Module_AfterDefineCallbackList; k; k = *(_DWORD *)(v24 + 12) )
    (*(void (**)(void))(k + 4))();
  return 0;
}
// 4C12A3: variable 'v3' is possibly undefined
// 4C1309: variable 'v9' is possibly undefined
// 4C1466: variable 'v21' is possibly undefined
// 4C14B0: variable 'v24' is possibly undefined
// 4C1507: variable 'v26' is possibly undefined
// 4C1540: variable 'v28' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 51A9C4: using guessed type int dword_51A9C4;
// 51B36C: using guessed type int dword_51B36C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E888: using guessed type int dword_54E888;

//----- (004C1590) --------------------------------------------------------
int  Module_IsRedefinitionOfExistingName(int theDefmodule)
{
  int v1; // edx
  int v2; // ecx

  Module_GetName(theDefmodule);
  if ( !strcmp_(v2, v1) )
    return g_Module_MainRedefinable;
  else
    return 0;
}
// 4C159B: variable 'v2' is possibly undefined
// 4C159B: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C4: using guessed type int dword_51A9C4;

//----- (004C15B0) --------------------------------------------------------
signed int  Module_ParseImportExportClauseList(int readSource, _DWORD *theToken, int newModule)
{
  int v5; // ecx
  int v6; // ecx
  int error; // eax
  int v8; // edx
  int v9; // ecx

  *(_DWORD *)(newModule + 12) = 0;
  *(_DWORD *)(newModule + 16) = 0;
  if ( *theToken == 101 )
    return 0;
  while ( *theToken == 100 )
  {
    Parser_NextToken(readSource, (int)theToken);
    if ( *theToken != 2 )
      break;
    if ( !strcmp_(v5, aImport) )
    {
      error = Module_ParseImportClause(readSource, theToken, newModule);
    }
    else
    {
      if ( strcmp_(v6, aExport) )
        break;
      error = Module_ParsePortItemSpecList(readSource, (int)theToken, 0, newModule);
    }
    if ( error )
      return 1;
    AST_Append(v9, v8);
    Parser_NextToken(readSource, (int)theToken);
    if ( *theToken == 101 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50AC54);
    }
    if ( *theToken == 101 )
      return 0;
  }
  Parser_ReportSyntaxError();
  return 1;
}
// 4C15EB: variable 'v5' is possibly undefined
// 4C1603: variable 'v9' is possibly undefined
// 4C1603: variable 'v8' is possibly undefined
// 4C1655: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004C1670) --------------------------------------------------------
int  Module_ParseImportClause(int readSource, _DWORD *theToken, int newModule)
{
  int v4; // edx
  int *theModule; // eax
  int v6; // ecx
  int *v7; // esi
  int v8; // eax
  _DWORD *theExport; // eax
  int found; // edx
  int exportType; // ecx
  int v12; // edx
  char *errorConstructName; // ebx
  int Name; // eax
  int newImport; // esi
  int importConstructName; // ebp
  int exportConstructName; // ecx
  _DWORD *theImport; // esi
  int *importModule; // edi
  _DWORD *v21; // ecx
  char *failedConstructName; // ebx
  int importModuleName; // eax
  int oldImportSpec; // [esp+4h] [ebp-1Ch]
  int *savedModule; // [esp+Ch] [ebp-14h]

  IO_OutWriteToken(asc_50AC58);
  Parser_NextToken(readSource, v4);
  if ( *theToken != 2 )
  {
    Parser_ReportSyntaxError();
    return 1;
  }
  theModule = Module_FindByName(*(_BYTE **)(theToken[1] + 16));
  v7 = theModule;
  savedModule = theModule;
  if ( !theModule )
  {
    Rules_ReportCantFindItem(v6, *(_DWORD *)(theToken[1] + 16));
    return 1;
  }
  if ( !theModule[4] )
  {
    errorConstructName = 0;
LABEL_16:
    Name = Module_GetName((int)theModule);
    Rules_ReportConstructNotExported(Name, errorConstructName);
    return 1;
  }
  oldImportSpec = *(_DWORD *)(newModule + 12);
  if ( Module_ParsePortItemSpecList(readSource, (int)theToken, theModule, newModule) )
    return 1;
  v8 = *(_DWORD *)(newModule + 12);
  if ( v8 == oldImportSpec )
    return oldImportSpec ^ v8;
  if ( *(_DWORD *)(v8 + 4) )
  {
    theExport = (_DWORD *)v7[4];
    found = 0;
    while ( theExport )
    {
      if ( found )
        break;
      exportType = theExport[1];
      if ( exportType )
      {
        newImport = *(_DWORD *)(newModule + 12);
        if ( exportType != *(_DWORD *)(newImport + 4) )
          continue;
        importConstructName = *(_DWORD *)(newImport + 8);
        if ( importConstructName )
        {
          exportConstructName = theExport[2];
          if ( exportConstructName )
          {
            if ( exportConstructName != importConstructName )
              continue;
          }
        }
      }
      found = 1;
      theExport = (_DWORD *)theExport[3];
    }
    if ( !found )
    {
      v12 = *(_DWORD *)(*(_DWORD *)(newModule + 12) + 8);
      if ( v12 )
        errorConstructName = *(char **)(v12 + 16);
      else
        errorConstructName = 0;
      theModule = savedModule;
      goto LABEL_16;
    }
  }
  Module_BeginEnum();
  Module_SetCurrent(newModule);
  theImport = *(_DWORD **)(newModule + 12);
  if ( theImport )
  {
    while ( 1 )
    {
      if ( theImport[1] )
      {
        if ( theImport[2] )
        {
          importModule = Module_FindByName(*(_BYTE **)(*theImport + 16));
          Module_SetCurrent((int)importModule);
          if ( !Rules_FindImportExportConstruct(*(char **)(theImport[1] + 16), v21, *(_BYTE **)(theImport[2] + 16), 1, 0) )
            break;
        }
      }
      theImport = (_DWORD *)theImport[3];
      if ( !theImport )
        goto LABEL_31;
    }
    failedConstructName = *(char **)(theImport[2] + 16);
    importModuleName = Module_GetName((int)importModule);
    Rules_ReportConstructNotExported(importModuleName, failedConstructName);
    Module_EndEnum();
    return 1;
  }
  else
  {
LABEL_31:
    Module_EndEnum();
    return 0;
  }
}
// 4C168D: variable 'v4' is possibly undefined
// 4C1760: variable 'v6' is possibly undefined
// 4C17FA: variable 'v21' is possibly undefined

//----- (004C1830) --------------------------------------------------------
int  Module_ParsePortItemSpecList(int readSource, int theToken, int *importModule, int newModule)
{
  int moduleName; // ebp
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // edx
  _DWORD *newPort; // eax
  int v11; // ecx
  _DWORD *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v16; // ecx
  _DWORD *v17; // eax
  int v18; // ecx
  _DWORD *typePortItem; // [esp+4h] [ebp-1Ch]
  _DWORD *allPortItem; // [esp+8h] [ebp-18h]
  int thePortConstruct; // [esp+Ch] [ebp-14h]
  int constructTypeSym; // [esp+10h] [ebp-10h]

  if ( importModule )
    moduleName = *importModule;
  else
    moduleName = 0;
  IO_OutWriteToken(asc_50AC58);
  Parser_NextToken(readSource, theToken);
  if ( *(_DWORD *)theToken == 15 )
  {
    if ( !strcmp_(v7, aAll) )
    {
      if ( *(_DWORD *)(g_ClipsMemoryTable + 64) )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = *(_DWORD *)g_ClipsMemFreeListTemp;
        v12 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v12 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      v12[1] = 0;
      v12[2] = 0;
      v12[3] = 0;
      allPortItem = v12;
      *v12 = moduleName;
    }
    else
    {
      if ( strcmp_(v11, aNone_1) )
        goto LABEL_24;
      allPortItem = 0;
    }
    Parser_NextToken(readSource, theToken);
    if ( *(_DWORD *)theToken == 101 )
    {
      if ( allPortItem )
      {
        if ( !v13 )
        {
          allPortItem[3] = *(_DWORD *)(newModule + 16);
          *(_DWORD *)(newModule + 16) = allPortItem;
          return 0;
        }
        allPortItem[3] = *(_DWORD *)(newModule + 12);
        *(_DWORD *)(newModule + 12) = allPortItem;
      }
      return 0;
    }
    if ( allPortItem )
    {
      g_ClipsMemFreeListTemp = (int)allPortItem;
      *allPortItem = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    goto LABEL_23;
  }
  if ( *(_DWORD *)theToken != 2 )
    goto LABEL_24;
  constructTypeSym = *(_DWORD *)(theToken + 4);
  thePortConstruct = Rules_ValidPortConstructItem((char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)constructTypeSym + 16));
  if ( !thePortConstruct )
    goto LABEL_24;
  IO_OutWriteToken(asc_50AC58);
  Parser_NextToken(readSource, theToken);
  if ( *(_DWORD *)theToken == 15 )
  {
    if ( !strcmp_(v8, aAll) )
    {
      if ( *(_DWORD *)(g_ClipsMemoryTable + 64) )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = *(_DWORD *)g_ClipsMemFreeListTemp;
        v17 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v17 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      v17[2] = 0;
      v17[3] = 0;
      *v17 = moduleName;
      typePortItem = v17;
      v17[1] = constructTypeSym;
    }
    else
    {
      if ( strcmp_(v16, aNone_1) )
        goto LABEL_24;
      typePortItem = 0;
    }
    Parser_NextToken(readSource, theToken);
    if ( *(_DWORD *)theToken == 101 )
    {
      if ( typePortItem )
      {
        if ( !v18 )
        {
          typePortItem[3] = *(_DWORD *)(newModule + 16);
          *(_DWORD *)(newModule + 16) = typePortItem;
          return 0;
        }
        typePortItem[3] = *(_DWORD *)(newModule + 12);
        *(_DWORD *)(newModule + 12) = typePortItem;
      }
      return 0;
    }
    if ( typePortItem )
    {
      g_ClipsMemFreeListTemp = (int)typePortItem;
      *typePortItem = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
LABEL_23:
    IO_OutNewline();
    IO_OutWriteToken(asc_50AC58);
    IO_OutWriteToken(*(char **)(theToken + 8));
    goto LABEL_24;
  }
  if ( *(_DWORD *)theToken == 101 )
  {
LABEL_24:
    Parser_ReportSyntaxError();
    return v14;
  }
  while ( *(_DWORD *)theToken != 101 )
  {
    if ( *(_DWORD *)theToken != *(_DWORD *)(thePortConstruct + 4) )
      goto LABEL_24;
    v9 = *(_DWORD **)(g_ClipsMemoryTable + 64);
    if ( v9 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = *v9;
      newPort = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newPort = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    *newPort = moduleName;
    newPort[1] = constructTypeSym;
    newPort[2] = *(_DWORD *)(theToken + 4);
    if ( v8 )
    {
      newPort[3] = *(_DWORD *)(newModule + 12);
      *(_DWORD *)(newModule + 12) = newPort;
    }
    else
    {
      newPort[3] = *(_DWORD *)(newModule + 16);
      *(_DWORD *)(newModule + 16) = newPort;
    }
    IO_OutWriteToken(asc_50AC58);
    Parser_NextToken(readSource, theToken);
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50AC54);
  return 0;
}
// 4C18F8: variable 'v8' is possibly undefined
// 4C1935: variable 'v7' is possibly undefined
// 4C19D3: variable 'v14' is possibly undefined
// 4C19FE: variable 'v11' is possibly undefined
// 4C1A1A: variable 'v13' is possibly undefined
// 4C1AE9: variable 'v16' is possibly undefined
// 4C1B06: variable 'v18' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C1B80) --------------------------------------------------------
int Rules_ValidPortConstructItem(char *theName)
{
  int export_type; // ecx

  export_type = g_Module_PortConstructList;
  while ( export_type )
  {
    if ( !strcmp(theName, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)export_type) )
      return export_type;
    export_type = *(_DWORD *)((uintptr_t)(unsigned int)export_type + 8);
  }
  return 0;
}
// 51B368: using guessed type int dword_51B368;

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
  int v9; // [esp+4h] [ebp-20h]
  int thePCItem; // [esp+8h] [ebp-1Ch]

  v9 = theModule;
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
      if ( (*(int (**)(void))(theConstruct + 28))() )
        break;
LABEL_6:
      thePCItem = *(_DWORD *)(thePCItem + 8);
      if ( !thePCItem )
        goto LABEL_7;
    }
    while ( 1 )
    {
      Module_SetCurrent(v9);
      theCItem = (*(int (**)(void))(theConstruct + 16))();
      Rules_FindImportExportConstruct(*(char **)thePCItem, &count, *(_BYTE **)(theCItem + 16), 0, 0);
      if ( count > 1 )
        break;
      Module_SetCurrent(Enum);
      if ( !(*(int (**)(void))(theConstruct + 28))() )
        goto LABEL_6;
    }
    conflictPortItem = (int *)thePCItem;
    (*(void (**)(void))(theConstruct + 16))();
    conflictConstructName = *conflictPortItem;
    Name = Module_GetName(v9);
    Lexer_WarnImpliedTemplate((int)aDefmodule_7, Name, conflictConstructName);
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

  Rules_PrintErrorID((int)aModulpsr, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aModule, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], moduleName, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotExport, v5);
  if ( v6 )
  {
    if ( constructName )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe_1, v6);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v12, v12);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50AC58, v13);
      v9 = g_IO_LogicalNameTable_WError[0];
      v8 = constructName;
      goto LABEL_5;
    }
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAny, v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, v7);
    v8 = aConstructs;
  }
  else
  {
    v8 = aAnyConstructs;
  }
  v9 = g_IO_LogicalNameTable_WError[0];
LABEL_5:
  Output_Write((int)v9, (int)v8, v6);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__30, v10);
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
  int v6; // ecx
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
      result = Module_FindItemByName((int)constructName);
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
  int v10; // ecx
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
      while ( *(_DWORD *)(tempSlot + 2) != *slotPtr )
      {
        tempSlot = *(_DWORD *)(tempSlot + 10);
        if ( !tempSlot )
          goto LABEL_6;
      }
      Rules_ReportAlreadyParsed(*slotPtr, *(_DWORD *)(*slotPtr + 16));
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
    if ( !Lexer_CheckValueList(*(int **)(newSlotExpr + 6), (int)aAssert_0) )
    {
      *error = 1;
      AST_Free(firstSlot);
      v11 = v13;
      goto LABEL_12;
    }
    if ( i )
      *(_DWORD *)(i + 10) = v10;
    else
      firstSlot = v10;
  }
  if ( *error )
  {
    AST_Free(firstSlot);
    return 0;
  }
  else
  {
    Rules_ReorderAssertSlotValues(*(_DWORD **)(theDeftemplate + 20), firstSlot, error);
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
  if ( *(_DWORD *)theToken == endType )
    return (_DWORD *)(endType ^ *(_DWORD *)theToken);
  IO_OutNewline();
  IO_OutWriteToken(asc_50AD10);
  IO_OutWriteToken(*(char **)(theToken + 8));
  if ( *(_DWORD *)theToken == 100 && (Parser_NextToken(readSource, theToken), *(_DWORD *)theToken == 2) )
  {
    result = Lexer_FindTemplateSlot(theDeftemplate, *(_DWORD *)(theToken + 4), position);
    if ( !result )
    {
      Rules_ReportInvalidSlotError(v8, *(_DWORD *)(*(_DWORD *)theDeftemplate + 16));
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
  int v14; // ecx
  unsigned int v15; // ebx
  int nextField; // eax
  unsigned int v17; // ebx
  int v18; // ecx
  int printError; // [esp+0h] [ebp-1Ch] BYREF
  int valueList; // [esp+4h] [ebp-18h]
  int *v21; // [esp+8h] [ebp-14h]
  int lastField; // [esp+Ch] [ebp-10h]

  v21 = slotPtr;
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
    if ( *(_WORD *)newField == 10 )
      isMultifield = *(_BYTE *)(*(_DWORD *)(newField + 2) + 8) == 109;
    else
      isMultifield = *(_WORD *)newField == 16;
    if ( isMultifield )
    {
      *error = 1;
      Rules_ReportSingleFieldSlotCardError();
      AST_Free(v12);
      return 0;
    }
    Parser_NextToken(readSource, theToken);
LABEL_11:
    if ( *(_DWORD *)theToken == 101 )
    {
      result = AST_NewNode(2, *v21);
      *(_DWORD *)(result + 6) = v18;
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
  v14 = *error;
  valueList = firstField;
  if ( v14 )
    goto LABEL_3;
  v15 = *(_DWORD *)theToken;
  lastField = firstField;
  if ( v15 == 101 )
    goto LABEL_11;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50AD10);
    IO_OutWriteToken(*(char **)(theToken + 8));
    nextField = Rules_ParseAssertArgument(readSource, (unsigned int *)(uintptr_t)(unsigned int)theToken, error, 101, constantsOnly, &printError);
    if ( *error )
      break;
    *(_DWORD *)(lastField + 10) = nextField;
    v17 = *(_DWORD *)theToken;
    lastField = nextField;
    if ( v17 == 101 )
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
  int v7; // ecx
  int firstValue; // [esp+0h] [ebp-14h]

  slotPtr = slotList;
  lastValue = 0;
  firstValue = 0;
  if ( !slotList )
    return firstValue;
  while ( 1 )
  {
    newValue = Rules_GetSlotAssertValues(slotPtr, firstSlot, (int)slotPtr, error);
    if ( *error )
      break;
    if ( newValue )
    {
      if ( lastValue )
        *(_DWORD *)(lastValue + 10) = newValue;
      else
        firstValue = newValue;
      lastValue = newValue;
    }
    slotPtr = *(_DWORD **)(v7 + 16);
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
  int v5; // ecx
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
    newArgument = *(_DWORD *)(slotItem + 6);
    *(_DWORD *)(slotItem + 6) = 0;
  }
  else
  {
    slotFlags = *(_BYTE *)(v5 + 4);
    if ( (slotFlags & 2) != 0 )
    {
      Rules_PrintErrorID((int)aTmpltrhs, 1, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_1, v12);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)v13 + 16), v13);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aRequiresAValue, v14);
      *error = 1;
      return 0;
    }
    if ( (slotFlags & 4) != 0 || (slotFlags & 8) != 0 )
    {
      defaultExpr = AST_CloneNodeList(*(_DWORD *)(v5 + 12));
    }
    else
    {
      Rules_DeriveDefaultFromConstraints(*(char **)(v5 + 8), theValueBuffer, *(_DWORD *)(v5 + 4) & 1);
      defaultExpr = AST_BuildExpressionFromValue(theValueBuffer);
    }
    newArgument = defaultExpr;
  }
  if ( (*(_BYTE *)(v5 + 4) & 1) != 0 )
  {
    multifieldMarker = Rules_AddBitmapValue(g_Rules_SlotAssertBitmapScratch, 1);
    multifieldExpr = AST_NewNode(34, multifieldMarker);
    *(_DWORD *)(multifieldExpr + 6) = newArgument;
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
  while ( *(_DWORD *)(listOfSlots + 2) != *slotPtr )
  {
    listOfSlots = *(_DWORD *)(listOfSlots + 10);
    if ( !listOfSlots )
      return 0;
  }
  return listOfSlots;
}

//----- (004C2340) --------------------------------------------------------
signed int Rules_RegisterModifyDuplicateFunctions()
{
  Rules_RegisterHostFunctionNoRestrictions(aModify, 117, (int)aModifycommand, (int)Rules_ModifyCommand);
  Rules_RegisterHostFunctionNoRestrictions(aDuplicate, 117, (int)aDuplicatecomma, (int)Rules_DuplicateCommand);
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
  int v10; // edx
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
  int v27; // edx
  int computeResult; // [esp+0h] [ebp-4Ch] BYREF
  int v29; // [esp+4h] [ebp-48h]
  _DWORD *v30; // [esp+8h] [ebp-44h]
  _BYTE tempBuffer[20]; // [esp+18h] [ebp-34h] BYREF
  _DWORD *newFact; // [esp+2Ch] [ebp-20h]
  int v33; // [esp+30h] [ebp-1Ch]
  int v34; // [esp+34h] [ebp-18h]

  v33 = retractIt;
  v34 = returnValue;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (_DWORD *)Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &computeResult, *(_DWORD *)(g_ClipsCurrentExpression + 6), a3);
  if ( v29 != 1 )
  {
    if ( v29 == 6 )
    {
      i = v30;
      goto LABEL_6;
    }
    if ( v33 )
      functionName = aModify;
    else
      functionName = aDuplicate;
LABEL_32:
    Rules_ReportSymbolTypeError(functionName, 1);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  if ( (int)v30[4] < 0 )
  {
    if ( v33 )
      functionName = aModify;
    else
      functionName = aDuplicate;
    goto LABEL_32;
  }
  result = (_DWORD *)Rules_GetNextFact(0);
  for ( i = result; i; i = (_DWORD *)i[9] )
  {
    if ( factNum == i[6] )
      break;
  }
  if ( !i )
  {
    sprintf_(tempBuffer, "f-%ld", factNum);
    return (_DWORD *)Rules_ReportCantFindItem(v22, (int)tempBuffer);
  }
LABEL_6:
  theDeftemplate = i[4];
  if ( (*(_BYTE *)(theDeftemplate + 24) & 1) == 0 )
  {
    v7 = Module_AllocList(*(_DWORD *)((char *)i + 46));
    v7[4] = theDeftemplate;
    fieldIndex = 0;
    v10 = *(_DWORD *)((char *)i + 46);
    newFact = v7;
    if ( v10 > 0 )
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
    for ( j = *(_DWORD *)(v8 + 10); j; j = *(_DWORD *)(v17 + 10) )
    {
      if ( *(_WORD *)j == 1 )
      {
        position = *(_DWORD *)(*(_DWORD *)(j + 2) + 16);
      }
      else
      {
        slotPtr = *(_DWORD **)(theDeftemplate + 20);
        position = 0;
        if ( !slotPtr )
        {
LABEL_46:
          Rules_ReportInvalidSlotError(j, *(_DWORD *)(*(_DWORD *)theDeftemplate + 16));
          Lexer_ErrorRecover(1);
          return Rules_ReturnFact(newFact);
        }
        while ( *slotPtr != *(_DWORD *)(j + 2) )
        {
          slotPtr = (_DWORD *)slotPtr[4];
          ++position;
          if ( !slotPtr )
            goto LABEL_46;
        }
      }
      newFactField = (char *)newFact + 6 * position;
      if ( *((_WORD *)newFactField + 27) == 4 )
      {
        Rules_StoreEvaluatedNodesAsMultifield(&computeResult, *(_DWORD *)(j + 6), 0, a3);
        Lexer_ErrorRecover(0);
      }
      else
      {
        valueExpr = *(_DWORD *)(j + 6);
        if ( !valueExpr || *(_DWORD *)(valueExpr + 10) )
        {
          Lexer_GetSlotByOrdinal(theDeftemplate, position);
          Rules_ReportMultifieldAssertIntoSingleSlotError(v24, theDeftemplate);
          return Rules_ReturnFact(newFact);
        }
        Parser_ParseForm(*(__int16 **)(j + 6), &computeResult, j, a3);
        Lexer_ErrorRecover(0);
        if ( v29 == 4 )
        {
          Rules_ReturnFact(newFact);
          Lexer_GetSlotByOrdinal(theDeftemplate, position);
          return (_DWORD *)Rules_ReportMultifieldAssertIntoSingleSlotError(v25, theDeftemplate);
        }
      }
      *((_WORD *)newFactField + 27) = v29;
      *((_DWORD *)newFactField + 14) = v30;
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
    if ( v33 )
      Rules_RetractFact((int)i, a3);
    result = Rules_AssertFactDriver(newFact, a3);
    if ( result )
    {
      *(_DWORD *)(v34 + 12) = 0;
      v26 = v34;
      v27 = *(_DWORD *)((char *)result + 46);
      *(_DWORD *)(v34 + 4) = 6;
      *(_DWORD *)(v26 + 8) = result;
      *(_DWORD *)(v26 + 16) = v27 - 1;
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
  int v12; // ecx
  int argList; // edx
  int v14; // ecx
  int v15; // edx
  signed int slotPosition; // eax
  int *indexValue; // eax
  int v18; // ecx
  _DWORD position[5]; // [esp+0h] [ebp-14h] BYREF

  functionArgs = *(_DWORD *)(top + 6);
  if ( *(_WORD *)functionArgs != 15 )
    return 1;
  templateName = Rules_FindTemplateForFactAddress(*(_DWORD *)(functionArgs + 2), theLHS);
  if ( !templateName )
    return 1;
  v7 = Symbol_LookupInModule((char **)g_DeftemplateConstructType, *(_BYTE **)(templateName + 16), 0);
  theDeftemplate = v7;
  if ( !v7 )
    return 1;
  if ( (*(_BYTE *)(v7 + 24) & 1) != 0 )
    return 1;
  tempArg = *(_DWORD *)(v8 + 10);
  if ( !tempArg )
    return 1;
  while ( 1 )
  {
    slotPtr = Lexer_FindTemplateSlot(theDeftemplate, *(_DWORD *)(tempArg + 2), position);
    if ( !slotPtr )
    {
      Rules_ReportInvalidSlotError(v12, *(_DWORD *)(*(_DWORD *)theDeftemplate + 16));
      return 0;
    }
    if ( (slotPtr[1] & 1) == 0 )
    {
      argList = *(_DWORD *)(v12 + 6);
      if ( !argList
        || *(_DWORD *)(argList + 10)
        || *(_WORD *)argList == 16
        || *(_WORD *)argList == 10 && *(_BYTE *)(*(_DWORD *)(argList + 2) + 8) == 109 )
      {
        break;
      }
    }
    result = Lexer_CheckValueList(*(int **)(v12 + 6), name);
    if ( !result )
      return result;
    v15 = *(_DWORD *)(v14 + 2);
    *(_WORD *)v14 = 1;
    slotPosition = Lexer_FindSymbolIndex(theDeftemplate, v15);
    indexValue = Rules_AddIntegerValue(slotPosition - 1);
    *(_DWORD *)(v18 + 2) = indexValue;
    tempArg = *(_DWORD *)(v18 + 10);
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
    while ( factAddress != *(_DWORD *)(theLHS + 4) )
    {
      theLHS = *(_DWORD *)(theLHS + 68);
      if ( !theLHS )
        goto LABEL_4;
    }
    thePattern = theLHS;
  }
LABEL_4:
  if ( thePattern && (rightNode = *(_DWORD **)(thePattern + 64), *rightNode == 17) && (templateNode = (_DWORD *)rightNode[17]) != 0 && *templateNode == 2 && !templateNode[16] && !templateNode[17] )
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
  int v5; // edx
  __int16 v6; // ax
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
  int v22; // [esp+14h] [ebp-18h]
  signed int nextAdd; // [esp+18h] [ebp-14h]

  v22 = top;
  error = 0;
  IO_OutWriteToken(asc_50ADC8);
  Parser_NextToken(logicalName, (int)&theToken);
  if ( theToken == 15 || theToken == 13 )
  {
    v5 = tokenValue;
    v6 = theToken;
  }
  else
  {
    if ( theToken != 1 )
    {
      Rules_ReportSymbolTypeError(name, 1);
      AST_Free(v22);
      return 0;
    }
    if ( !Rules_IsEvaluatingTopLevelCommand() )
    {
      Rules_PrintErrorID((int)aTmpltfun_0, v4, v4);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFactIndexesCan, v14);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)name, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAsATopLevelCom, v16);
      AST_Free(v22);
      return 0;
    }
    v5 = tokenValue;
    v6 = v4;
  }
  v7 = AST_NewNode(v6, v5);
  nextAdd = v7;
  *(_DWORD *)(v7 + 10) = 0;
  *(_DWORD *)(v7 + 6) = 0;
  *(_DWORD *)(v22 + 6) = nextAdd;
  Parser_NextToken(logicalName, (int)&theToken);
  if ( theToken == 101 )
    return v22;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50ADC8);
    IO_OutWriteToken(tokenPrintForm);
    if ( theToken != 100 )
      goto LABEL_15;
    Parser_NextToken(logicalName, (int)&theToken);
    if ( theToken != 2 )
      goto LABEL_15;
    parsedSlot = *(_DWORD *)(*(_DWORD *)(v22 + 6) + 10);
    if ( parsedSlot )
      break;
LABEL_12:
    newField = AST_NewNode(2, tokenValue);
    firstField = 0;
    *(_DWORD *)(nextAdd + 10) = newField;
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
          *(_DWORD *)(lastField + 10) = theField;
        else
          firstField = theField;
        lastField = theField;
        if ( theToken == 101 )
          goto LABEL_25;
      }
      if ( printError )
LABEL_15:
        Parser_ReportSyntaxError();
      AST_Free(v22);
      return 0;
    }
LABEL_25:
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50AE50);
    *(_DWORD *)(nextAdd + 6) = firstField;
    Parser_NextToken(logicalName, (int)&theToken);
    if ( theToken == 101 )
      return v22;
  }
  while ( tokenValue != *(_DWORD *)(parsedSlot + 2) )
  {
    parsedSlot = *(_DWORD *)(parsedSlot + 10);
    if ( !parsedSlot )
      goto LABEL_12;
  }
  Rules_ReportAlreadyParsed(tokenValue, *(_DWORD *)(tokenValue + 16));
  AST_Free(v22);
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
  int v8; // ecx
  char *multifieldIntersection; // eax
  _BYTE *tmpConstraint; // eax
  bool v11; // al
  bool v12; // al
  bool v13; // al
  bool v14; // al
  bool v15; // al
  bool v16; // al
  bool v17; // al
  bool v18; // al
  bool v19; // al
  bool v20; // al
  bool v21; // al
  bool v22; // al
  bool v23; // al
  bool v24; // al

  c2Changed = 0;
  if ( !constraint1 && !constraint2 )
  {
    result = (_BYTE *)Rules_CreateLHSParseNode();
    result[1] |= 0x80u;
    return result;
  }
  if ( !constraint1 )
    return (_BYTE *)Rules_CloneLHSParseNode((int *)constraint2);
  if ( !constraint2 )
    return (_BYTE *)Rules_CloneLHSParseNode((int *)constraint1);
  result = (_BYTE *)Rules_CreateLHSParseNode();
  theConstraint = (int)result;
  if ( *(_DWORD *)constraint1 << 16 >> 31 != *(_DWORD *)constraint2 << 16 >> 31 && *(_DWORD *)constraint1 << 15 >> 31 != *(_DWORD *)constraint2 << 15 >> 31 )
  {
    *result &= ~1u;
    return result;
  }
  if ( *(char *)(constraint1 + 1) >= 0 || *(char *)(constraint2 + 1) >= 0 )
    result[1] &= ~0x80u;
  else
    result[1] |= 0x80u;
  if ( (*(_BYTE *)(constraint1 + 2) & 1) != 0 && (*(_BYTE *)(constraint2 + 2) & 1) != 0 )
    result[2] |= 1u;
  else
    result[2] &= ~1u;
  if ( (*(_BYTE *)constraint1 & 1) == 0 || (*(_BYTE *)constraint2 & 1) == 0 )
  {
    if ( (*(_BYTE *)constraint1 & 1) != 0 )
    {
      tmpConstraint = (_BYTE *)constraint1;
    }
    else
    {
      if ( (*(_BYTE *)constraint2 & 1) == 0 )
      {
LABEL_31:
        *(_BYTE *)theConstraint &= ~1u;
        v11 = (*(_BYTE *)constraint1 & 2) != 0 && (*(_BYTE *)constraint2 & 2) != 0;
        *(_BYTE *)theConstraint &= ~2u;
        *(_DWORD *)theConstraint |= 2 * v11;
        v12 = (*(_BYTE *)constraint1 & 4) != 0 && (*(_BYTE *)constraint2 & 4) != 0;
        *(_BYTE *)theConstraint &= ~4u;
        *(_DWORD *)theConstraint |= 4 * v12;
        v13 = (*(_BYTE *)constraint1 & 8) != 0 && (*(_BYTE *)constraint2 & 8) != 0;
        *(_BYTE *)theConstraint &= ~8u;
        *(_DWORD *)theConstraint |= 8 * v13;
        v14 = (*(_BYTE *)constraint1 & 0x10) != 0 && (*(_BYTE *)constraint2 & 0x10) != 0;
        *(_BYTE *)theConstraint &= ~0x10u;
        *(_DWORD *)theConstraint |= 16 * v14;
        v15 = (*(_BYTE *)constraint1 & 0x20) != 0 && (*(_BYTE *)constraint2 & 0x20) != 0;
        *(_BYTE *)theConstraint &= ~0x20u;
        *(_DWORD *)theConstraint |= 32 * v15;
        v16 = (*(_BYTE *)constraint1 & 0x40) != 0 && (*(_BYTE *)constraint2 & 0x40) != 0;
        *(_BYTE *)theConstraint &= ~0x40u;
        *(_DWORD *)theConstraint |= v16 << 6;
        v17 = *(char *)constraint1 < 0 && *(char *)constraint2 < 0;
        *(_BYTE *)theConstraint &= ~0x80u;
        *(_DWORD *)theConstraint |= v17 << 7;
        v18 = *(char *)(constraint1 + 1) < 0 && *(char *)(constraint2 + 1) < 0;
        *(_BYTE *)(theConstraint + 1) &= ~0x80u;
        *(_DWORD *)theConstraint |= v18 << 15;
        v19 = (*(_BYTE *)(constraint1 + 1) & 1) != 0 && (*(_BYTE *)(constraint2 + 1) & 1) != 0;
        *(_BYTE *)(theConstraint + 1) &= ~1u;
        *(_DWORD *)theConstraint |= v19 << 8;
        if ( c1Changed )
          Rules_SetLHSParseNodeDefaultFlags((_BYTE *)constraint1, 1);
        if ( c2Changed )
          Rules_SetLHSParseNodeDefaultFlags((_BYTE *)constraint2, 1);
        goto LABEL_16;
      }
      tmpConstraint = (_BYTE *)constraint2;
      c2Changed = 1;
    }
    Rules_SetLHSParseNodeDefaultFlags(tmpConstraint, 0);
    goto LABEL_31;
  }
  *result |= 1u;
LABEL_16:
  if ( (*(_BYTE *)(constraint1 + 1) & 2) != 0 || (*(_BYTE *)(constraint2 + 1) & 2) != 0 )
  {
    *(_BYTE *)(theConstraint + 1) |= 2u;
  }
  else
  {
    *(_BYTE *)(theConstraint + 1) &= ~2u;
    v20 = (*(_BYTE *)(constraint1 + 1) & 4) != 0 || (*(_BYTE *)(constraint2 + 1) & 4) != 0;
    *(_BYTE *)(theConstraint + 1) &= ~4u;
    *(_DWORD *)theConstraint |= v20 << 10;
    v21 = (*(_BYTE *)(constraint1 + 1) & 8) != 0 || (*(_BYTE *)(constraint2 + 1) & 8) != 0;
    *(_BYTE *)(theConstraint + 1) &= ~8u;
    *(_DWORD *)theConstraint |= v21 << 11;
    v22 = (*(_BYTE *)(constraint1 + 1) & 0x10) != 0 || (*(_BYTE *)(constraint2 + 1) & 0x10) != 0;
    *(_BYTE *)(theConstraint + 1) &= ~0x10u;
    *(_DWORD *)theConstraint |= v22 << 12;
    v23 = (*(_BYTE *)(constraint1 + 1) & 0x20) != 0 || (*(_BYTE *)(constraint2 + 1) & 0x20) != 0;
    *(_BYTE *)(theConstraint + 1) &= ~0x20u;
    *(_DWORD *)theConstraint |= v23 << 13;
    v24 = (*(_BYTE *)(constraint1 + 1) & 0x40) != 0 || (*(_BYTE *)(constraint2 + 1) & 0x40) != 0;
    *(_BYTE *)(theConstraint + 1) &= ~0x40u;
    *(_DWORD *)theConstraint |= v24 << 14;
  }
  Rules_IntersectAllowedValueExpressions(constraint1, constraint2, theConstraint);
  Rules_IntersectNumericExpressions(constraint1, constraint2, v8, theConstraint);
  Rules_IntersectNumericExpressions(constraint1, constraint2, 0, theConstraint);
  Rules_UpdateRestrictionFlags(theConstraint);
  if ( *(char *)(theConstraint + 1) < 0 )
  {
    multifieldIntersection = (char *)Rules_IntersectConstraints(*(_DWORD *)(constraint1 + 26), *(_DWORD *)(constraint2 + 26));
    *(_DWORD *)(theConstraint + 26) = multifieldIntersection;
    if ( Rules_ConstraintIsUnmatchable(multifieldIntersection) )
      *(_BYTE *)(theConstraint + 1) &= ~0x80u;
  }
  return (_BYTE *)theConstraint;
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

  theList1 = *(__int16 **)(constraint1 + 6);
  for ( i = 0; theList1; theList1 = *(__int16 **)(theList1 + 5) )
  {
    if ( Method_QueryRestrictionAllowsType(*theList1, *(_DWORD *)(theList1 + 1), constraint1) && Method_QueryRestrictionAllowsType(*theList1, *(_DWORD *)(theList1 + 1), constraint2) )
    {
      tmpExpr = AST_NewNode(*theList1, *(_DWORD *)(theList1 + 1));
      *(_DWORD *)(tmpExpr + 10) = i;
      i = (__int16 *)tmpExpr;
    }
  }
  for ( j = *(__int16 **)(constraint2 + 6); j; j = *(__int16 **)(j + 5) )
  {
    if ( !Rules_FindItemInExpression(*j, *(_DWORD *)(j + 1), i, 1)
      && Method_QueryRestrictionAllowsType(*j, *(_DWORD *)(j + 1), constraint1)
      && Method_QueryRestrictionAllowsType(*j, *(_DWORD *)(j + 1), constraint2) )
    {
      tmpExpr2 = AST_NewNode(*j, *(_DWORD *)(j + 1));
      *(_DWORD *)(tmpExpr2 + 10) = i;
      i = (__int16 *)tmpExpr2;
    }
  }
  result = newConstraint;
  *(_DWORD *)(newConstraint + 6) = i;
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
    tmpmin1 = *(__int16 **)(constraint1 + 10);
    v5 = *(__int16 **)(constraint1 + 14);
  }
  else
  {
    tmpmin1 = *(__int16 **)(constraint1 + 18);
    v5 = *(__int16 **)(constraint1 + 22);
  }
  while ( 1 )
  {
    tmpmax1 = v5;
    if ( !tmpmin1 )
      break;
    if ( range )
    {
      tmpmin2 = *(__int16 **)(constraint2 + 10);
      tmpmax2 = *(__int16 **)(constraint2 + 14);
    }
    else
    {
      tmpmin2 = *(__int16 **)(constraint2 + 18);
      tmpmax2 = *(__int16 **)(constraint2 + 22);
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
          *(_DWORD *)(lastMin + 10) = theMinNode;
          *(_DWORD *)(lastMax + 10) = theMaxNode;
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
      AST_Free(*(_DWORD *)(newConstraint + 10));
      AST_Free(*(_DWORD *)(newConstraint + 14));
      result = theMaxList;
      *(_DWORD *)(v16 + 10) = theMinList;
      *(_DWORD *)(v16 + 14) = theMaxList;
    }
    else
    {
      AST_Free(*(_DWORD *)(newConstraint + 18));
      AST_Free(*(_DWORD *)(newConstraint + 22));
      result = theMaxList;
      *(_DWORD *)(v17 + 18) = theMinList;
      *(_DWORD *)(v17 + 22) = theMaxList;
    }
  }
  else if ( range )
  {
    if ( (*(_BYTE *)newConstraint & 1) != 0 )
      Rules_SetLHSParseNodeDefaultFlags((_BYTE *)newConstraint, 0);
    result = newConstraint;
    *(_BYTE *)newConstraint &= 0xE7u;
  }
  else
  {
    Rules_SetLHSParseNodeDefaultFlags((_BYTE *)newConstraint, 1);
    result = newConstraint;
    *(_DWORD *)newConstraint &= 0xFFFE7FFE;
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
  if ( (*(_BYTE *)(result + 1) & 2) != 0 && !*(_DWORD *)(result + 6) )
  {
    result = (int)Rules_SetLHSParseNodeDefaultFlags((_BYTE *)result, 1);
    *(_BYTE *)theConstraint &= ~1u;
  }
  if ( (*(_BYTE *)(theConstraint + 1) & 4) != 0 && (*(_BYTE *)theConstraint & 2) != 0 )
  {
    symbolFound = Rules_FindItemInExpression(2, 0, *(__int16 **)(theConstraint + 6), 0);
    *(_BYTE *)theConstraint &= ~2u;
    result = 2 * (symbolFound & 1);
    *(_DWORD *)theConstraint |= result;
  }
  if ( (*(_BYTE *)(theConstraint + 1) & 8) != 0 && (*(_BYTE *)theConstraint & 4) != 0 )
  {
    stringFound = Rules_FindItemInExpression(3, 0, *(__int16 **)(theConstraint + 6), 0);
    *(_BYTE *)theConstraint &= ~4u;
    result = 4 * (stringFound & 1);
    *(_DWORD *)theConstraint |= result;
  }
  if ( (*(_BYTE *)(theConstraint + 1) & 0x10) != 0 && (*(_BYTE *)theConstraint & 8) != 0 )
  {
    floatFound = Rules_FindItemInExpression(0, 0, *(__int16 **)(theConstraint + 6), 0);
    *(_BYTE *)theConstraint &= ~8u;
    result = 8 * (floatFound & 1);
    *(_DWORD *)theConstraint |= result;
  }
  if ( (*(_BYTE *)(theConstraint + 1) & 0x20) != 0 && (*(_BYTE *)theConstraint & 0x10) != 0 )
  {
    integerFound = Rules_FindItemInExpression(1, 0, *(__int16 **)(theConstraint + 6), 0);
    *(_BYTE *)theConstraint &= ~0x10u;
    result = 16 * (integerFound & 1);
    *(_DWORD *)theConstraint |= result;
  }
  if ( (*(_BYTE *)(theConstraint + 1) & 0x40) != 0 && (*(_BYTE *)theConstraint & 0x20) != 0 )
  {
    instanceNameFound = Rules_FindItemInExpression(8, 0, *(__int16 **)(theConstraint + 6), 0);
    *(_BYTE *)theConstraint &= ~0x20u;
    result = 32 * (instanceNameFound & 1);
    *(_DWORD *)theConstraint |= result;
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
    restrictionFlags = *(_BYTE *)(theConstraint + 1);
    if ( (restrictionFlags & 2) != 0 || (restrictionFlags & 4) != 0 && theType == 2 )
      return 1;
    if ( (*(_BYTE *)(theConstraint + 1) & 8) != 0 && theType == 3
      || (*(_BYTE *)(theConstraint + 1) & 0x10) != 0 && !theType
      || (*(_BYTE *)(theConstraint + 1) & 0x20) != 0 && theType == 1
      || (*(_BYTE *)(theConstraint + 1) & 0x40) != 0 && theType == 8 )
    {
      return 1;
    }
  }
  return result;
}

//----- (004C3430) --------------------------------------------------------
int  Rules_UnionConstraints(int constraint1, int constraint2)
{
  int c1Changed; // ebx
  _BYTE *newRecord; // eax
  int c2Changed; // ecx
  int theConstraint; // esi
  int v8; // ecx
  bool v10; // al
  bool v11; // al
  bool v12; // al
  bool v13; // al
  bool v14; // al
  bool v15; // al
  bool v16; // al
  bool v17; // al
  int tmpConstraint; // eax
  bool v19; // al
  bool v20; // al
  bool v21; // al
  bool v22; // al
  bool v23; // al

  c1Changed = 0;
  if ( !constraint1 && !constraint2 )
    return Rules_CreateLHSParseNode();
  if ( !constraint1 )
    return Rules_CloneLHSParseNode((int *)constraint2);
  if ( !constraint2 )
    return Rules_CloneLHSParseNode((int *)constraint1);
  newRecord = (_BYTE *)Rules_CreateLHSParseNode();
  theConstraint = (int)newRecord;
  if ( *(char *)(constraint1 + 1) < 0 || *(char *)(constraint2 + 1) < 0 )
    newRecord[1] |= 0x80u;
  if ( (*(_BYTE *)(constraint1 + 2) & 1) != 0 || (*(_BYTE *)(constraint2 + 2) & 1) != 0 )
    newRecord[2] |= 1u;
  if ( (*(_BYTE *)constraint1 & 1) != 0 || (*(_BYTE *)constraint2 & 1) != 0 )
  {
    *newRecord |= 1u;
  }
  else
  {
    *newRecord &= ~1u;
    v10 = (*(_BYTE *)constraint1 & 2) != 0 || (*(_BYTE *)constraint2 & 2) != 0;
    *(_BYTE *)theConstraint &= ~2u;
    *(_DWORD *)theConstraint |= 2 * v10;
    v11 = (*(_BYTE *)constraint1 & 4) != 0 || (*(_BYTE *)constraint2 & 4) != 0;
    *(_BYTE *)theConstraint &= ~4u;
    *(_DWORD *)theConstraint |= 4 * v11;
    v12 = (*(_BYTE *)constraint1 & 8) != 0 || (*(_BYTE *)constraint2 & 8) != 0;
    *(_BYTE *)theConstraint &= ~8u;
    *(_DWORD *)theConstraint |= 8 * v12;
    v13 = (*(_BYTE *)constraint1 & 0x10) != 0 || (*(_BYTE *)constraint2 & 0x10) != 0;
    *(_BYTE *)theConstraint &= ~0x10u;
    *(_DWORD *)theConstraint |= 16 * v13;
    v14 = (*(_BYTE *)constraint1 & 0x20) != 0 || (*(_BYTE *)constraint2 & 0x20) != 0;
    *(_BYTE *)theConstraint &= ~0x20u;
    *(_DWORD *)theConstraint |= 32 * v14;
    v15 = (*(_BYTE *)constraint1 & 0x40) != 0 || (*(_BYTE *)constraint2 & 0x40) != 0;
    *(_BYTE *)theConstraint &= ~0x40u;
    *(_DWORD *)theConstraint |= v15 << 6;
    v16 = *(char *)constraint1 < 0 || *(char *)constraint2 < 0;
    *(_BYTE *)theConstraint &= ~0x80u;
    *(_DWORD *)theConstraint |= v16 << 7;
    v17 = (*(_BYTE *)(constraint1 + 1) & 1) != 0 || (*(_BYTE *)(constraint2 + 1) & 1) != 0;
    *(_BYTE *)(theConstraint + 1) &= ~1u;
    *(_DWORD *)theConstraint |= v17 << 8;
  }
  if ( (*(_BYTE *)(constraint1 + 1) & 2) == 0 || (*(_BYTE *)(constraint2 + 1) & 2) == 0 )
  {
    if ( (*(_BYTE *)(constraint1 + 1) & 2) != 0 )
    {
      tmpConstraint = constraint1;
      c1Changed = 1;
    }
    else
    {
      if ( (*(_BYTE *)(constraint2 + 1) & 2) == 0 )
      {
LABEL_61:
        *(_BYTE *)(theConstraint + 1) &= ~2u;
        v19 = (*(_BYTE *)(constraint1 + 1) & 4) != 0 && (*(_BYTE *)(constraint2 + 1) & 4) != 0;
        *(_BYTE *)(theConstraint + 1) &= ~4u;
        *(_DWORD *)theConstraint |= v19 << 10;
        v20 = (*(_BYTE *)(constraint1 + 1) & 8) != 0 && (*(_BYTE *)(constraint2 + 1) & 8) != 0;
        *(_BYTE *)(theConstraint + 1) &= ~8u;
        *(_DWORD *)theConstraint |= v20 << 11;
        v21 = (*(_BYTE *)(constraint1 + 1) & 0x10) != 0 && (*(_BYTE *)(constraint2 + 1) & 0x10) != 0;
        *(_BYTE *)(theConstraint + 1) &= ~0x10u;
        *(_DWORD *)theConstraint |= v21 << 12;
        v22 = (*(_BYTE *)(constraint1 + 1) & 0x20) != 0 && (*(_BYTE *)(constraint2 + 1) & 0x20) != 0;
        *(_BYTE *)(theConstraint + 1) &= ~0x20u;
        *(_DWORD *)theConstraint |= v22 << 13;
        v23 = (*(_BYTE *)(constraint1 + 1) & 0x40) != 0 && (*(_BYTE *)(constraint2 + 1) & 0x40) != 0;
        *(_BYTE *)(theConstraint + 1) &= ~0x40u;
        *(_DWORD *)theConstraint |= v23 << 14;
        if ( c1Changed )
        {
          Rules_SetLHSParseNodeExtendedFlags(constraint1, 0);
        }
        else if ( c2Changed )
        {
          Rules_SetLHSParseNodeExtendedFlags(constraint2, 0);
        }
        goto LABEL_14;
      }
      tmpConstraint = constraint2;
    }
    Rules_SetLHSParseNodeExtendedFlags(tmpConstraint, 0);
    goto LABEL_61;
  }
  *(_BYTE *)(theConstraint + 1) |= 2u;
LABEL_14:
  Rules_UnionAllowedValueExpressions(constraint1, constraint2, theConstraint);
  Rules_UnionNumericExpressions((__int16 *)constraint1, constraint2, v8, theConstraint);
  Rules_UnionNumericExpressions((__int16 *)constraint1, constraint2, 0, theConstraint);
  if ( *(char *)(theConstraint + 1) < 0 )
    *(_DWORD *)(theConstraint + 26) = Rules_UnionConstraints(*(_DWORD *)(constraint1 + 26), *(_DWORD *)(constraint2 + 26));
  return theConstraint;
}
// 4C34B6: variable 'v8' is possibly undefined
// 4C379C: variable 'v6' is possibly undefined

//----- (004C3800) --------------------------------------------------------
__int16 * Rules_UnionNumericExpressions(__int16 *result, int constraint2, int range, int newConstraint)
{
  int tmpmin; // esi
  int tmpmax; // edi
  int tmpmin2; // esi
  int tmpmax2; // edi
  __int16 *theMinList; // [esp+0h] [ebp-1Ch] BYREF
  __int16 *theMaxList; // [esp+4h] [ebp-18h] BYREF
  int v10; // [esp+8h] [ebp-14h]
  int v11; // [esp+Ch] [ebp-10h]

  v10 = constraint2;
  v11 = range;
  theMinList = 0;
  theMaxList = 0;
  if ( range )
  {
    tmpmin = *(_DWORD *)(result + 5);
    tmpmax = *(_DWORD *)(result + 7);
  }
  else
  {
    tmpmin = *(_DWORD *)(result + 9);
    tmpmax = *(_DWORD *)(result + 11);
  }
  while ( tmpmin )
  {
    result = Rules_UnionRangeMinMaxValueWithList((__int16 *)tmpmin, (__int16 *)tmpmax, &theMaxList, &theMinList);
    tmpmin = *(_DWORD *)(tmpmin + 10);
    tmpmax = *(_DWORD *)(tmpmax + 10);
  }
  if ( v11 )
  {
    tmpmin2 = *(_DWORD *)(v10 + 10);
    tmpmax2 = *(_DWORD *)(v10 + 14);
  }
  else
  {
    tmpmin2 = *(_DWORD *)(v10 + 18);
    tmpmax2 = *(_DWORD *)(v10 + 22);
  }
  while ( tmpmin2 )
  {
    result = Rules_UnionRangeMinMaxValueWithList((__int16 *)tmpmin2, (__int16 *)tmpmax2, &theMaxList, &theMinList);
    tmpmin2 = *(_DWORD *)(tmpmin2 + 10);
    tmpmax2 = *(_DWORD *)(tmpmax2 + 10);
  }
  if ( theMinList )
  {
    if ( v11 )
    {
      AST_Free(*(_DWORD *)(newConstraint + 10));
      AST_Free(*(_DWORD *)(newConstraint + 14));
      *(_DWORD *)(newConstraint + 10) = theMinList;
      result = theMaxList;
      *(_DWORD *)(newConstraint + 14) = theMaxList;
    }
    else
    {
      AST_Free(*(_DWORD *)(newConstraint + 18));
      AST_Free(*(_DWORD *)(newConstraint + 22));
      *(_DWORD *)(newConstraint + 18) = theMinList;
      result = theMaxList;
      *(_DWORD *)(newConstraint + 22) = theMaxList;
    }
  }
  else if ( v11 )
  {
    if ( (*(_BYTE *)newConstraint & 1) != 0 )
      result = (__int16 *)Rules_SetLHSParseNodeDefaultFlags((_BYTE *)newConstraint, 0);
    *(_BYTE *)newConstraint &= 0xE7u;
  }
  else
  {
    result = (__int16 *)Rules_SetLHSParseNodeDefaultFlags((_BYTE *)newConstraint, 1);
    *(_BYTE *)newConstraint |= 1u;
  }
  return result;
}

//----- (004C3910) --------------------------------------------------------
__int16 * Rules_UnionRangeMinMaxValueWithList(__int16 *theMin, __int16 *theMax, __int16 **theMaxList, __int16 **theMinList)
{
  __int16 *tmpmin; // esi
  __int16 *tmpmax; // edi
  __int16 *result; // eax
  __int16 *maxCursor; // esi
  _DWORD *nextMin; // edi
  int nextMax; // ebp
  __int16 **v11; // ecx
  signed int newMinNode; // ecx
  signed int mergeCompare; // eax
  signed int cmaxmax; // [esp+10h] [ebp-20h]
  signed int cminmin; // [esp+14h] [ebp-1Ch]
  signed int cmaxmin; // [esp+18h] [ebp-18h]
  signed int minCursor; // [esp+1Ch] [ebp-14h]

  if ( *theMinList )
  {
    tmpmin = *theMinList;
    tmpmax = *theMaxList;
    while ( 1 )
    {
      cmaxmax = Rules_CompareBoundedCEValues(*theMax, *(_DWORD *)(theMax + 1), *(_DWORD *)(tmpmax + 1), *tmpmax);
      cminmin = Rules_CompareBoundedCEValues(*theMin, *(_DWORD *)(theMin + 1), *(_DWORD *)(tmpmin + 1), *tmpmin);
      cmaxmin = Rules_CompareBoundedCEValues(*theMax, *(_DWORD *)(theMax + 1), *(_DWORD *)(tmpmin + 1), *tmpmin);
      result = (__int16 *)Rules_CompareBoundedCEValues(*theMin, *(_DWORD *)(theMin + 1), *(_DWORD *)(tmpmax + 1), *tmpmax);
      if ( (!cmaxmax || cmaxmax == 2) && (cminmin == 1 || cminmin == 2) )
        break;
      if ( cmaxmax == 1 && (!result || result == (__int16 *)2) )
      {
        *tmpmax = *theMax;
        *(_DWORD *)(tmpmax + 1) = *(_DWORD *)(theMax + 1);
      }
      if ( !cminmin && (cmaxmin == 1 || cmaxmin == 2) )
      {
        *tmpmin = *theMin;
        *(_DWORD *)(tmpmin + 1) = *(_DWORD *)(theMin + 1);
      }
      if ( !cmaxmin )
      {
        AST_NewNode(*theMin, *(_DWORD *)(theMin + 1));
        result = (__int16 *)AST_NewNode(*theMax, *(_DWORD *)(theMax + 1));
        *(_DWORD *)(newMinNode + 10) = *theMinList;
        *(_DWORD *)(result + 5) = *theMaxList;
        *theMinList = (__int16 *)newMinNode;
        *theMaxList = result;
        return result;
      }
      tmpmin = *(__int16 **)(tmpmin + 5);
      tmpmax = *(__int16 **)(tmpmax + 5);
      if ( !tmpmin )
      {
        result = *theMinList;
        maxCursor = *theMaxList;
        minCursor = (signed int)*theMinList;
        if ( *theMinList )
        {
          while ( 1 )
          {
            nextMin = *(_DWORD **)(minCursor + 10);
            nextMax = *(_DWORD *)(maxCursor + 5);
            if ( !nextMin )
              break;
            mergeCompare = Rules_CompareBoundedCEValues(*maxCursor, *(_DWORD *)(maxCursor + 1), *(_DWORD *)((char *)nextMin + 2), *(__int16 *)nextMin);
            if ( mergeCompare == 1 || mergeCompare == 2 )
            {
              *maxCursor = *(_WORD *)nextMax;
              *(_DWORD *)(maxCursor + 1) = *(_DWORD *)(nextMax + 2);
              *(_DWORD *)(maxCursor + 5) = *(_DWORD *)(nextMax + 10);
              *(_DWORD *)(minCursor + 10) = *(_DWORD *)((char *)nextMin + 10);
              g_ClipsMemFreeListTemp = (int)nextMin;
              *nextMin = *(_DWORD *)(g_ClipsMemoryTable + 56);
              *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
              g_ClipsMemFreeListTemp = nextMax;
              *(_DWORD *)nextMax = *(_DWORD *)(g_ClipsMemoryTable + 56);
              result = (__int16 *)g_ClipsMemoryTable;
              *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
              if ( !minCursor )
                return result;
            }
            else
            {
              result = *(__int16 **)(minCursor + 10);
              maxCursor = *(__int16 **)(maxCursor + 5);
              minCursor = (signed int)result;
              if ( !result )
                return result;
            }
          }
        }
        return result;
      }
    }
  }
  else
  {
    *theMinList = (__int16 *)AST_NewNode(*theMin, *(_DWORD *)(theMin + 1));
    result = (__int16 *)AST_NewNode(*theMax, *(_DWORD *)(theMax + 1));
    *v11 = result;
  }
  return result;
}
// 4C3A7C: variable 'v11' is possibly undefined
// 4C3AD6: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C3BA0) --------------------------------------------------------
__int16 * Rules_UnionAllowedValueExpressions(int constraint1, int constraint2, int newConstraint)
{
  __int16 *theHead; // eax
  int v5; // ecx
  __int16 *result; // eax
  int v7; // ecx

  theHead = Rules_AddToUnionList(*(__int16 **)(constraint1 + 6), 0, newConstraint);
  result = Rules_AddToUnionList(*(__int16 **)(constraint2 + 6), theHead, v5);
  *(_DWORD *)(v7 + 6) = result;
  return result;
}
// 4C3BB9: variable 'v5' is possibly undefined
// 4C3BBE: variable 'v7' is possibly undefined

//----- (004C3BD0) --------------------------------------------------------
__int16 * Rules_AddToUnionList(__int16 *theList, __int16 *theHead, int theConstraint)
{
  __int16 *theItem; // ecx
  __int16 *tmpItem; // eax
  __int16 *result; // eax
  int v7; // ecx

  theItem = theList;
  if ( theList )
  {
    while ( 1 )
    {
      tmpItem = theHead;
      if ( theHead )
        break;
LABEL_8:
      if ( Rules_RestrictionOnType(*theItem, theConstraint) )
      {
        result = (__int16 *)AST_NewNode(*theItem, *(_DWORD *)(theItem + 1));
        *(_DWORD *)(result + 5) = theHead;
        theHead = result;
        theItem = *(__int16 **)(v7 + 10);
        if ( !theItem )
          return result;
      }
      else
      {
LABEL_5:
        theItem = *(__int16 **)(theItem + 5);
        if ( !theItem )
          return theHead;
      }
    }
    while ( *theItem != *tmpItem || *(_DWORD *)(theItem + 1) != *(_DWORD *)(tmpItem + 1) )
    {
      tmpItem = *(__int16 **)(tmpItem + 5);
      if ( !tmpItem )
        goto LABEL_8;
    }
    goto LABEL_5;
  }
  return theHead;
}
// 4C3BFB: variable 'v3' is possibly undefined
// 4C3C32: variable 'v7' is possibly undefined

//----- (004C3C40) --------------------------------------------------------
int  Rules_RemoveConstantFromConstraint(int result, int theValue, int theConstraint)
{
  int theType; // edi
  __int16 *lastOne; // ecx
  __int16 *theList; // edx

  theType = result;
  lastOne = 0;
  if ( theConstraint )
  {
    theList = *(__int16 **)(theConstraint + 6);
    *(_DWORD *)(theConstraint + 6) = 0;
    while ( theList )
    {
      if ( *theList == theType && theValue == *(_DWORD *)(theList + 1) )
      {
        *(_DWORD *)(theList + 5) = 0;
        AST_Free((int)theList);
      }
      else
      {
        if ( lastOne )
          *(_DWORD *)(lastOne + 5) = theList;
        else
          *(_DWORD *)(theConstraint + 6) = theList;
        lastOne = theList;
        theList = *(__int16 **)(theList + 5);
        *(_DWORD *)(lastOne + 5) = 0;
      }
    }
    return Rules_UpdateRestrictionFlags(theConstraint);
  }
  return result;
}
// 4C3C57: variable 'v6' is possibly undefined
// 4C3C60: variable 'v5' is possibly undefined

//----- (004C3CA0) --------------------------------------------------------
signed int Rules_RegisterDefglobalBinaryItem()
{
  Rules_AddAfterBloadFunction((int)aDefglobal_1, (int)Defglobal_ResetAllDefglobals, 50);
  return Rules_RegisterBinaryItem(
           (int)aDefglobal_1,
           0,
           0,
           (int)Rules_BsaveFindDefglobals,
           (int)Rules_BsaveDefglobalStorage,
           (int)Rules_BsaveDefglobals,
           (int)Rules_BloadDefglobalStorage,
           (int)Rules_BloadDefglobals,
           (int)Rules_ClearDefglobalBload);
}

//----- (004C3CF0) --------------------------------------------------------
int Rules_BsaveFindDefglobals()
{
  int result; // eax
  int i; // ebx
  _DWORD *j; // ecx
  int bsaveIndex; // edx
  int v4; // ecx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DefglobalModuleItemCount);
    Rules_ConstructQueuePush(g_Defglobal_Count);
  }
  g_Defglobal_Count = 0;
  g_DefglobalModuleItemCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    ++g_DefglobalModuleItemCount;
    for ( j = (_DWORD *)Defglobal_EnumNext(0); j; j = (_DWORD *)Defglobal_EnumNext(v4) )
    {
      bsaveIndex = g_Defglobal_Count++;
      AST_MarkNodeFieldBound(j, bsaveIndex);
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4C3D64: variable 'v4' is possibly undefined
// 51B374: using guessed type int dword_51B374;
// 54E88C: using guessed type int dword_54E88C;

//----- (004C3D90) --------------------------------------------------------
const void * Rules_BsaveDefglobalStorage(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 8;
  Rules_BsaveWriteBlock(4, fp, space);
  Rules_BsaveWriteBlock(4, v2, &g_Defglobal_Count);
  return Rules_BsaveWriteBlock(4, v3, &g_DefglobalModuleItemCount);
}
// 4C3DBA: variable 'v2' is possibly undefined
// 4C3DCB: variable 'v3' is possibly undefined
// 51B374: using guessed type int dword_51B374;
// 54E88C: using guessed type int dword_54E88C;

//----- (004C3DE0) --------------------------------------------------------
int  Rules_BsaveDefglobals(int fp)
{
  int i; // ecx
  int theItem; // eax
  _DWORD *theModuleItem; // eax
  int v5; // ecx
  int j; // edi
  int k; // ecx
  int v8; // ecx
  int v9; // ecx
  int result; // eax
  _DWORD dummyGlobal[4]; // [esp+0h] [ebp-38h] BYREF
  _DWORD dummyModule[3]; // [esp+10h] [ebp-28h] BYREF
  int space[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  space[0] = 12 * g_DefglobalModuleItemCount + 16 * g_Defglobal_Count;
  Rules_BsaveWriteBlock(4, fp, space);
  g_Defglobal_Count = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v5) )
  {
    Module_SetCurrent(i);
    theItem = Module_FindItemByName((int)aDefglobal_1);
    theModuleItem = (_DWORD *)Module_GetItem(0, *(_DWORD *)(theItem + 4));
    Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
    Rules_BsaveWriteBlock(12, fp, dummyModule);
  }
  g_Defglobal_Count = 0;
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Defglobal_EnumNext(0); k; k = Defglobal_EnumNext(v9) )
    {
      AST_ExtractPatternBindingInfo(dummyGlobal, k);
      dummyGlobal[3] = AST_GetHashedNodeIndex(*(__int16 **)(v8 + 52));
      Rules_BsaveWriteBlock(16, fp, dummyGlobal);
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DefglobalModuleItemCount);
    return Rules_ConstructQueuePop(&g_Defglobal_Count);
  }
  return result;
}
// 4C3E71: variable 'v5' is possibly undefined
// 4C3EB7: variable 'v8' is possibly undefined
// 4C3ED0: variable 'v9' is possibly undefined
// 51B374: using guessed type int dword_51B374;
// 54E88C: using guessed type int dword_54E88C;

//----- (004C3F20) --------------------------------------------------------
signed int Rules_BloadDefglobalStorage()
{
  signed int result; // eax
  int space[3]; // [esp+0h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)space, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_Defglobal_Count, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DefglobalModuleItemCount, 4u);
  if ( !g_DefglobalModuleItemCount )
  {
    g_DefglobalBloadRecords = 0;
    g_ClipsDefglobalModuleItemArray = 0;
  }
  space[0] = 12 * g_DefglobalModuleItemCount;
  result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_DefglobalModuleItemCount));
  g_ClipsDefglobalModuleItemArray = result;
  if ( g_Defglobal_Count )
  {
    space[0] = 56 * g_Defglobal_Count;
    result = Mem_HeapAllocWithRetry((_DWORD *)(56 * g_Defglobal_Count));
    g_DefglobalBloadRecords = result;
  }
  else
  {
    g_DefglobalBloadRecords = 0;
  }
  return result;
}
// 51B370: using guessed type int dword_51B370;
// 51B374: using guessed type int dword_51B374;
// 54E88C: using guessed type int dword_54E88C;
// 54E890: using guessed type int dword_54E890;

//----- (004C3FD0) --------------------------------------------------------
signed int Rules_BloadDefglobals()
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  Rules_BloadAndRefresh(g_DefglobalModuleItemCount, 12, (void (__fastcall *)(signed int, signed int))Rules_UpdateDefglobalModule);
  return Rules_BloadAndRefresh(g_Defglobal_Count, 16, (void (__fastcall *)(signed int, signed int))Rules_UpdateDefglobal);
}
// 51B374: using guessed type int dword_51B374;
// 54E88C: using guessed type int dword_54E88C;

//----- (004C4010) --------------------------------------------------------
_DWORD * Rules_UpdateDefglobalModule(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(12 * obji + g_ClipsDefglobalModuleItemArray), g_DefglobalBloadRecords, 56);
}
// 51B370: using guessed type int dword_51B370;
// 54E890: using guessed type int dword_54E890;

//----- (004C4050) --------------------------------------------------------
int  Rules_UpdateDefglobal(int buf, int obji)
{
  int recordOffset; // ebp
  int v5; // eax
  char v6; // dl
  int initialIndex; // ebx
  int initialExpr; // edx
  int result; // eax

  recordOffset = 56 * obji;
  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(56 * obji + g_DefglobalBloadRecords), g_ClipsDefglobalModuleItemArray, 12, 56, g_DefglobalBloadRecords);
  v5 = g_DefglobalBloadRecords;
  v6 = g_Rules_WatchGlobals;
  *(_BYTE *)(g_DefglobalBloadRecords + recordOffset + 20) &= ~1u;
  *(_DWORD *)(v5 + recordOffset + 20) |= v6 & 1;
  initialIndex = *(_DWORD *)(buf + 12);
  if ( initialIndex == -1 )
    initialExpr = 0;
  else
    initialExpr = 14 * initialIndex + g_ClipsPackedExpressionArray;
  result = 56 * obji;
  *(_DWORD *)(g_DefglobalBloadRecords + result + 52) = initialExpr;
  *(_DWORD *)(g_DefglobalBloadRecords + result + 32) = 105;
  return result;
}
// 51B370: using guessed type int dword_51B370;
// 51B3EC: using guessed type int dword_51B3EC;
// 54E688: using guessed type int dword_54E688;
// 54E890: using guessed type int dword_54E890;

//----- (004C4100) --------------------------------------------------------
signed int Rules_ClearDefglobalBload()
{
  int globalIndex; // ecx
  int recordOffset; // edx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  signed int result; // eax

  globalIndex = 0;
  if ( g_Defglobal_Count > 0 )
  {
    recordOffset = 0;
    do
    {
      Rules_ReleaseSymbolReference((int *)(recordOffset + g_DefglobalBloadRecords), globalIndex);
      Rules_ValueDeinstall(v2 + g_DefglobalBloadRecords + 28, v3);
      if ( *(_DWORD *)(v4 + g_DefglobalBloadRecords + 32) == 4 )
        Rules_ReturnMultifieldToPool(*(_DWORD **)(v4 + g_DefglobalBloadRecords + 36));
      globalIndex = v5 + 1;
      recordOffset = v4 + 56;
    }
    while ( globalIndex < g_Defglobal_Count );
  }
  if ( 56 * g_Defglobal_Count )
    Mem_ReleasePoolBlock(g_DefglobalBloadRecords, 56 * g_Defglobal_Count);
  result = 12 * g_DefglobalModuleItemCount;
  if ( 12 * g_DefglobalModuleItemCount )
    return Mem_ReleasePoolBlock(g_ClipsDefglobalModuleItemArray, 12 * g_DefglobalModuleItemCount);
  return result;
}
// 4C4122: variable 'v2' is possibly undefined
// 4C4127: variable 'v3' is possibly undefined
// 4C4131: variable 'v4' is possibly undefined
// 4C413F: variable 'v5' is possibly undefined
// 51B370: using guessed type int dword_51B370;
// 51B374: using guessed type int dword_51B374;
// 54E88C: using guessed type int dword_54E88C;
// 54E890: using guessed type int dword_54E890;

//----- (004C41B0) --------------------------------------------------------
int  Rules_GetDefglobalModulePointer(int theIndex)
{
  return 12 * theIndex + g_ClipsDefglobalModuleItemArray;
}
// 54E890: using guessed type int dword_54E890;

//----- (004C41D0) --------------------------------------------------------
signed int Defgeneric_RegisterBinaryItem()
{
  return Rules_RegisterBinaryItem(
           (int)aGenericFunct_0,
           0,
           (int)Defgeneric_BsaveWriteExpressions,
           (int)Defgeneric_CountBsaveEntries,
           (int)Defgeneric_BsaveWriteBinaryHeader,
           (int)Defgeneric_BsaveWriteConstructs,
           (int)Defgeneric_BloadAllocateBinaryStorage,
           (int)Defgeneric_BloadRefreshConstructs,
           (int)Defgeneric_ClearBinaryData);
}

//----- (004C4210) --------------------------------------------------------
int  Defgeneric_RecordAtIndex(int theIndex)
{
  return 12 * theIndex + g_DefgenericBloadModuleRefArray;
}
// 51B390: using guessed type int dword_51B390;

//----- (004C4230) --------------------------------------------------------
signed int Defgeneric_CountBsaveEntries()
{
  signed int result; // eax

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DefgenericBloadCount);
    Rules_ConstructQueuePush(g_Defgeneric_MethodRecordCount);
    Rules_ConstructQueuePush(g_Defgeneric_RestrictionRecordCount);
    Rules_ConstructQueuePush(g_Defgeneric_RestrictionTypeCount);
    Rules_ConstructQueuePush(g_Defgeneric_PackedExpressionCount);
  }
  g_Defgeneric_MethodRecordCount = 0;
  g_Defgeneric_RestrictionRecordCount = 0;
  g_Defgeneric_RestrictionTypeCount = 0;
  g_Defgeneric_PackedExpressionCount = 0;
  result = Rules_DoForAllConstructs((void (*)(void))Defgeneric_CountMethodsAndMarkExpressions, 0);
  g_DefgenericBloadCount = result;
  return result;
}
// 51B37C: using guessed type int dword_51B37C;
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;
// 54E6A4: using guessed type int dword_54E6A4;

//----- (004C42B0) --------------------------------------------------------
int  Defgeneric_CountMethodsAndMarkExpressions(_DWORD *theDefgeneric)
{
  int bsaveId; // edx
  int v2; // ecx
  int result; // eax
  unsigned int methodIndex; // ebp
  int methodOffset; // edi
  _DWORD *theMethod; // esi
  unsigned int restrictionIndex; // ebx
  int restrictionOffset; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx

  bsaveId = g_Defgeneric_MethodRecordCount++;
  AST_MarkNodeFieldBound(theDefgeneric, bsaveId);
  result = *(_DWORD *)(v2 + 32);
  g_Defgeneric_RestrictionRecordCount += result;
  methodIndex = 0;
  if ( *(_DWORD *)(v2 + 32) )
  {
    methodOffset = 0;
    do
    {
      theMethod = (_DWORD *)(methodOffset + theDefgeneric[7]);
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theMethod[8]);
      Rules_MarkReferencedFunctions((__int16 *)theMethod[8]);
      g_Defgeneric_RestrictionTypeCount += theMethod[2];
      restrictionIndex = 0;
      if ( theMethod[2] )
      {
        restrictionOffset = 0;
        do
        {
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(restrictionOffset + theMethod[7] + 4));
          Rules_MarkReferencedFunctions(*(__int16 **)(v10 + v9 + 4));
          g_Defgeneric_PackedExpressionCount += *(_DWORD *)(v12 + v11 + 8);
          ++restrictionIndex;
          restrictionOffset = v12 + 12;
        }
        while ( restrictionIndex < theMethod[2] );
      }
      result = (int)theDefgeneric;
      ++methodIndex;
      methodOffset += 40;
    }
    while ( methodIndex < theDefgeneric[8] );
  }
  return result;
}
// 4C42D8: variable 'v2' is possibly undefined
// 4C433E: variable 'v10' is possibly undefined
// 4C433E: variable 'v9' is possibly undefined
// 4C4347: variable 'v12' is possibly undefined
// 4C4347: variable 'v11' is possibly undefined
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;
// 54E680: using guessed type int dword_54E680;

//----- (004C4380) --------------------------------------------------------
signed int Defgeneric_BsaveWriteExpressions()
{
  Rules_DoForAllConstructs((void (*)(void))Defgeneric_BsaveWriteMethodActionExpressions, 0);
  return Rules_DoForAllConstructs((void (*)(void))Defgeneric_BsaveWriteRestrictionExpressions, 0);
}
// 54E6A4: using guessed type int dword_54E6A4;

//----- (004C43C0) --------------------------------------------------------
__int16 * Defgeneric_BsaveWriteMethodActionExpressions(__int16 *result, int fp)
{
  int theDefgeneric; // edi
  unsigned int methodIndex; // ebx
  int methodOffset; // ecx
  int v6; // ecx

  theDefgeneric = (int)result;
  methodIndex = 0;
  if ( *((_DWORD *)result + 8) )
  {
    methodOffset = 0;
    do
    {
      ++methodIndex;
      result = Rules_BsaveWriteExpression(*(__int16 **)(methodOffset + *(_DWORD *)(theDefgeneric + 28) + 32), fp);
      methodOffset = v6 + 40;
    }
    while ( methodIndex < *(_DWORD *)(theDefgeneric + 32) );
  }
  return result;
}
// 4C43E6: variable 'v6' is possibly undefined

//----- (004C4400) --------------------------------------------------------
__int16 * Defgeneric_BsaveWriteRestrictionExpressions(__int16 *result, int fp)
{
  int methodOffset; // ebp
  int theMethod; // esi
  unsigned int restrictionIndex; // ebx
  int restrictionOffset; // ecx
  int v7; // ecx
  int theDefgeneric; // [esp+0h] [ebp-1Ch]
  unsigned int methodIndex; // [esp+4h] [ebp-18h]

  theDefgeneric = (int)result;
  methodIndex = 0;
  if ( *((_DWORD *)result + 8) )
  {
    methodOffset = 0;
    do
    {
      theMethod = methodOffset + *(_DWORD *)(theDefgeneric + 28);
      result = *(__int16 **)(theMethod + 8);
      restrictionIndex = 0;
      if ( result )
      {
        restrictionOffset = 0;
        do
        {
          ++restrictionIndex;
          result = Rules_BsaveWriteExpression(*(__int16 **)(restrictionOffset + *(_DWORD *)(theMethod + 28) + 4), fp);
          restrictionOffset = v7 + 12;
        }
        while ( restrictionIndex < *(_DWORD *)(theMethod + 8) );
      }
      methodOffset += 40;
      ++methodIndex;
    }
    while ( methodIndex < *(_DWORD *)(theDefgeneric + 32) );
  }
  return result;
}
// 4C4441: variable 'v7' is possibly undefined

//----- (004C4470) --------------------------------------------------------
const void * Defgeneric_BsaveWriteBinaryHeader(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 20;
  Rules_BsaveWriteBlock(4, fp, space);
  Rules_BsaveWriteBlock(4, v2, &g_DefgenericBloadCount);
  Rules_BsaveWriteBlock(4, v3, &g_Defgeneric_MethodRecordCount);
  Rules_BsaveWriteBlock(4, v4, &g_Defgeneric_RestrictionRecordCount);
  Rules_BsaveWriteBlock(4, v5, &g_Defgeneric_RestrictionTypeCount);
  return Rules_BsaveWriteBlock(4, v6, &g_Defgeneric_PackedExpressionCount);
}
// 4C449A: variable 'v2' is possibly undefined
// 4C44AB: variable 'v3' is possibly undefined
// 4C44BC: variable 'v4' is possibly undefined
// 4C44CD: variable 'v5' is possibly undefined
// 4C44DE: variable 'v6' is possibly undefined
// 51B37C: using guessed type int dword_51B37C;
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;

//----- (004C44F0) --------------------------------------------------------
int  Defgeneric_BsaveWriteConstructs(int fp, int a2)
{
  int theItem; // eax
  int v4; // ecx
  _DWORD *theModuleItem; // eax
  int v6; // ecx
  int result; // eax
  _DWORD dummyModule[3]; // [esp-Ch] [ebp-24h] BYREF
  _DWORD space[6]; // [esp+0h] [ebp-18h] BYREF

  space[4] = a2;
  space[0] = 4 * g_Defgeneric_PackedExpressionCount + 12 * g_DefgenericBloadCount + 20 * g_Defgeneric_MethodRecordCount + 32 * g_Defgeneric_RestrictionRecordCount + 12 * g_Defgeneric_RestrictionTypeCount;
  Rules_BsaveWriteBlock(4, fp, space);
  g_Defgeneric_MethodRecordCount = 0;
  if ( Module_NextEnum(0) )
  {
    do
    {
      theItem = Module_FindItemByName((int)aDefgeneric_2);
      theModuleItem = (_DWORD *)Module_GetItem(v4, *(_DWORD *)(theItem + 4));
      Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
      Rules_BsaveWriteBlock(12, fp, dummyModule);
    }
    while ( Module_NextEnum(v6) );
  }
  g_Defgeneric_RestrictionRecordCount = 0;
  Rules_DoForAllConstructs((void (*)(void))Defgeneric_BsaveWriteGenericRecord, 0);
  g_Defgeneric_RestrictionTypeCount = 0;
  Rules_DoForAllConstructs((void (*)(void))Defgeneric_BsaveWriteMethodRecord, 0);
  g_Defgeneric_PackedExpressionCount = 0;
  Rules_DoForAllConstructs((void (*)(void))Defgeneric_BsaveWriteRestrictionRecord, 0);
  Rules_DoForAllConstructs((void (*)(void))Defgeneric_BsaveWriteRestrictionTypeRecord, 0);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DefgenericBloadCount);
    Rules_ConstructQueuePop(&g_Defgeneric_MethodRecordCount);
    Rules_ConstructQueuePop(&g_Defgeneric_RestrictionRecordCount);
    Rules_ConstructQueuePop(&g_Defgeneric_RestrictionTypeCount);
    return Rules_ConstructQueuePop(&g_Defgeneric_PackedExpressionCount);
  }
  return result;
}
// 4C4592: variable 'v4' is possibly undefined
// 4C45B0: variable 'v6' is possibly undefined
// 51B37C: using guessed type int dword_51B37C;
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;
// 54E6A4: using guessed type int dword_54E6A4;

//----- (004C4680) --------------------------------------------------------
const void * Defgeneric_BsaveWriteGenericRecord(int theDefgeneric, int fp, int a3)
{
  int v4; // ecx
  _DWORD dummyGeneric[3]; // [esp-Ch] [ebp-1Ch] BYREF
  int methodsIndex; // [esp+0h] [ebp-10h]
  int methodCount; // [esp+4h] [ebp-Ch]
  int v9; // [esp+8h] [ebp-8h]

  v9 = a3;
  AST_ExtractPatternBindingInfo(dummyGeneric, theDefgeneric);
  methodCount = *(_DWORD *)(v4 + 32);
  if ( *(_DWORD *)(v4 + 28) )
  {
    methodsIndex = g_Defgeneric_RestrictionRecordCount;
    g_Defgeneric_RestrictionRecordCount += *(_DWORD *)(v4 + 32);
  }
  else
  {
    methodsIndex = -1;
  }
  return Rules_BsaveWriteBlock(20, fp, dummyGeneric);
}
// 4C4692: variable 'v4' is possibly undefined
// 51B384: using guessed type int dword_51B384;

//----- (004C46F0) --------------------------------------------------------
_DWORD * Defgeneric_BsaveWriteMethodRecord(_DWORD *result, int fp)
{
  int theDefgeneric; // ebp
  unsigned int methodIndex; // esi
  int methodOffset; // ecx
  _DWORD *theMethod; // edx
  int v7; // ecx
  _DWORD dummyMethod[6]; // [esp+0h] [ebp-34h] BYREF
  int restrictionsIndex; // [esp+18h] [ebp-1Ch]
  int actionsIndex; // [esp+1Ch] [ebp-18h]

  theDefgeneric = (int)result;
  methodIndex = 0;
  if ( result[8] )
  {
    methodOffset = 0;
    do
    {
      theMethod = (_DWORD *)(methodOffset + *(_DWORD *)(theDefgeneric + 28));
      dummyMethod[0] = *theMethod;
      dummyMethod[1] = theMethod[2];
      dummyMethod[2] = theMethod[3];
      dummyMethod[3] = theMethod[4];
      dummyMethod[4] = theMethod[5];
      dummyMethod[5] = theMethod[6] & 1;
      if ( theMethod[7] )
      {
        restrictionsIndex = g_Defgeneric_RestrictionTypeCount;
        g_Defgeneric_RestrictionTypeCount += theMethod[2];
      }
      else
      {
        restrictionsIndex = -1;
      }
      if ( theMethod[8] )
      {
        actionsIndex = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theMethod[8]);
      }
      else
      {
        actionsIndex = -1;
      }
      result = Rules_BsaveWriteBlock(32, fp, dummyMethod);
      ++methodIndex;
      methodOffset = v7 + 40;
    }
    while ( methodIndex < *(_DWORD *)(theDefgeneric + 32) );
  }
  return result;
}
// 4C4778: variable 'v7' is possibly undefined
// 51B388: using guessed type int dword_51B388;
// 54E680: using guessed type int dword_54E680;

//----- (004C47B0) --------------------------------------------------------
_DWORD * Defgeneric_BsaveWriteRestrictionRecord(_DWORD *result, int fp)
{
  _DWORD *theDefgeneric; // ebp
  int v4; // ecx
  unsigned int restrictionIndex; // ecx
  int restrictionOffset; // esi
  unsigned int v7; // edx
  _DWORD *theRestriction; // edx
  int v9; // ecx
  int typesIndex; // [esp+0h] [ebp-2Ch] BYREF
  int queryIndex; // [esp+4h] [ebp-28h]
  int typeCount; // [esp+8h] [ebp-24h]
  unsigned int methodIndex; // [esp+Ch] [ebp-20h]
  int methodOffset; // [esp+10h] [ebp-1Ch]
  int v15; // [esp+14h] [ebp-18h]

  theDefgeneric = result;
  v4 = result[8];
  methodIndex = 0;
  if ( v4 )
  {
    methodOffset = 0;
    do
    {
      restrictionIndex = 0;
      restrictionOffset = 0;
      v15 = methodOffset;
      while ( 1 )
      {
        result = (_DWORD *)(v15 + theDefgeneric[7]);
        if ( restrictionIndex >= result[2] )
          break;
        theRestriction = (_DWORD *)(restrictionOffset + result[7]);
        typeCount = theRestriction[2];
        if ( *theRestriction )
        {
          typesIndex = g_Defgeneric_PackedExpressionCount;
          g_Defgeneric_PackedExpressionCount += theRestriction[2];
        }
        else
        {
          typesIndex = -1;
        }
        if ( theRestriction[1] )
        {
          queryIndex = g_ClipsExpressionNodeIndex;
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theRestriction[1]);
        }
        else
        {
          queryIndex = -1;
        }
        Rules_BsaveWriteBlock(12, fp, &typesIndex);
        restrictionOffset += 12;
        restrictionIndex = v9 + 1;
      }
      v7 = theDefgeneric[8];
      methodOffset += 40;
      ++methodIndex;
    }
    while ( methodIndex < v7 );
  }
  return result;
}
// 4C4860: variable 'v9' is possibly undefined
// 51B38C: using guessed type int dword_51B38C;
// 54E680: using guessed type int dword_54E680;

//----- (004C4880) --------------------------------------------------------
_DWORD * Defgeneric_BsaveWriteRestrictionTypeRecord(_DWORD *result, int fp)
{
  int v3; // ecx
  _DWORD *theRestriction; // edi
  int typeOffset; // esi
  int typeAddr; // eax
  int classIndex; // eax
  unsigned int v8; // ecx
  unsigned int v9; // edi
  int dummyClassIndex; // [esp+0h] [ebp-30h] BYREF
  int methodOffset; // [esp+4h] [ebp-2Ch]
  unsigned int methodIndex; // [esp+8h] [ebp-28h]
  int v13; // [esp+Ch] [ebp-24h]
  _DWORD *theDefgeneric; // [esp+10h] [ebp-20h]
  int restrictionOffset; // [esp+14h] [ebp-1Ch]
  unsigned int restrictionIndex; // [esp+18h] [ebp-18h]

  theDefgeneric = result;
  v3 = result[8];
  methodIndex = 0;
  if ( v3 )
  {
    methodOffset = 0;
    do
    {
      restrictionIndex = 0;
      v13 = methodOffset;
      restrictionOffset = 0;
      while ( 1 )
      {
        result = (_DWORD *)(v13 + theDefgeneric[7]);
        if ( restrictionIndex >= result[2] )
          break;
        theRestriction = (_DWORD *)(restrictionOffset + result[7]);
        if ( theRestriction[2] )
        {
          typeOffset = 0;
          do
          {
            typeAddr = typeOffset + *theRestriction;
            if ( *(_DWORD *)typeAddr )
              classIndex = *(_DWORD *)(*(_DWORD *)typeAddr + 12);
            else
              classIndex = -1;
            dummyClassIndex = classIndex;
            Rules_BsaveWriteBlock(4, fp, &dummyClassIndex);
            typeOffset += 4;
          }
          while ( v8 < theRestriction[2] );
        }
        restrictionOffset += 12;
        ++restrictionIndex;
      }
      v9 = theDefgeneric[8];
      methodOffset += 40;
      ++methodIndex;
    }
    while ( methodIndex < v9 );
  }
  return result;
}
// 4C4906: variable 'v8' is possibly undefined

//----- (004C4950) --------------------------------------------------------
int Defgeneric_BloadAllocateBinaryStorage()
{
  int result; // eax
  _DWORD counts[4]; // [esp+0h] [ebp-30h] BYREF
  int exprCount; // [esp+10h] [ebp-20h]
  unsigned int space[7]; // [esp+14h] [ebp-1Ch] BYREF

  result = Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    Rules_BloadReadBlock((uintptr_t)counts, space[0]);
    g_DefgenericBloadCount = counts[0];
    g_Defgeneric_MethodRecordCount = counts[1];
    g_Defgeneric_RestrictionRecordCount = counts[2];
    g_Defgeneric_RestrictionTypeCount = counts[3];
    result = exprCount;
    g_Defgeneric_PackedExpressionCount = exprCount;
    if ( counts[0] )
    {
      space[0] = 12 * counts[0];
      result = Mem_HeapAllocWithRetry((_DWORD *)(12 * counts[0]));
      g_DefgenericBloadModuleRefArray = result;
      if ( g_Defgeneric_MethodRecordCount )
      {
        space[0] = 40 * g_Defgeneric_MethodRecordCount;
        result = Mem_HeapAllocWithRetry((_DWORD *)(40 * g_Defgeneric_MethodRecordCount));
        g_DefgenericMethodArray = result;
        if ( g_Defgeneric_RestrictionRecordCount )
        {
          space[0] = 40 * g_Defgeneric_RestrictionRecordCount;
          result = Mem_HeapAllocWithRetry((_DWORD *)(40 * g_Defgeneric_RestrictionRecordCount));
          g_DefgenericRestrictionRecords = result;
          if ( g_Defgeneric_RestrictionTypeCount )
          {
            space[0] = 12 * g_Defgeneric_RestrictionTypeCount;
            result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_Defgeneric_RestrictionTypeCount));
            g_ClipsDefgenericBloadRestrictionTypeArray = result;
            if ( g_Defgeneric_PackedExpressionCount )
            {
              space[0] = 4 * g_Defgeneric_PackedExpressionCount;
              result = Mem_HeapAllocWithRetry((_DWORD *)(4 * g_Defgeneric_PackedExpressionCount));
              g_DefgenericBloadRestrictionTypeArray = result;
            }
          }
        }
      }
    }
  }
  return result;
}
// 51B378: using guessed type int dword_51B378;
// 51B37C: using guessed type int dword_51B37C;
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;
// 51B390: using guessed type int dword_51B390;
// 51B394: using guessed type int dword_51B394;
// 51B398: using guessed type int dword_51B398;
// 51B39C: using guessed type int dword_51B39C;

//----- (004C4A80) --------------------------------------------------------
int __thiscall Defgeneric_BloadRefreshConstructs(void *this)
{
  int result; // eax
  _DWORD space[4]; // [esp-Ch] [ebp-10h] BYREF

  space[2] = this;
  result = Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( g_DefgenericBloadCount )
  {
    result = Rules_BloadAndRefresh(g_DefgenericBloadCount, 12, (void (__fastcall *)(signed int, signed int))Defgeneric_BloadRefreshGenericRecord);
    if ( g_Defgeneric_MethodRecordCount )
    {
      Rules_BloadAndRefresh(g_Defgeneric_MethodRecordCount, 20, (void (__fastcall *)(signed int, signed int))Defgeneric_BloadRefreshMethodRecord);
      Rules_BloadAndRefresh(g_Defgeneric_RestrictionRecordCount, 32, (void (__fastcall *)(signed int, signed int))Defgeneric_BloadRefreshRestrictionRecord);
      Rules_BloadAndRefresh(g_Defgeneric_RestrictionTypeCount, 12, (void (__fastcall *)(signed int, signed int))Defgeneric_BloadRefreshRestrictionTypeRecord);
      return Rules_BloadAndRefresh(g_Defgeneric_PackedExpressionCount, 4, (void (__fastcall *)(signed int, signed int))Defgeneric_BloadRefreshExpressionPointer);
    }
  }
  return result;
}
// 51B37C: using guessed type int dword_51B37C;
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;

//----- (004C4B20) --------------------------------------------------------
_DWORD * Defgeneric_BloadRefreshGenericRecord(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(12 * obji + g_DefgenericBloadModuleRefArray), g_DefgenericMethodArray, 40);
}
// 51B378: using guessed type int dword_51B378;
// 51B390: using guessed type int dword_51B390;

//----- (004C4B60) --------------------------------------------------------
int  Defgeneric_BloadRefreshMethodRecord(int buf, int obji)
{
  int methodOffset; // ebp
  int restrictionsIndex; // edx
  int restrictionsPtr; // esi
  int result; // eax

  methodOffset = 40 * obji;
  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(g_DefgenericMethodArray + 40 * obji), g_DefgenericBloadModuleRefArray, 12, 40, g_DefgenericMethodArray);
  *(_DWORD *)(g_DefgenericMethodArray + methodOffset + 20) = 0;
  *(_DWORD *)(g_DefgenericMethodArray + methodOffset + 24) = g_Rules_WatchGenericFunctions;
  restrictionsIndex = *(_DWORD *)(buf + 12);
  if ( restrictionsIndex == -1 )
    restrictionsPtr = 0;
  else
    restrictionsPtr = 40 * restrictionsIndex + g_DefgenericRestrictionRecords;
  result = 5 * obji;
  *(_DWORD *)(g_DefgenericMethodArray + 8 * result + 28) = restrictionsPtr;
  *(_DWORD *)(g_DefgenericMethodArray + 8 * result + 32) = *(_DWORD *)(buf + 16);
  *(_DWORD *)(g_DefgenericMethodArray + 8 * result + 36) = 0;
  return result;
}
// 51B378: using guessed type int dword_51B378;
// 51B390: using guessed type int dword_51B390;
// 51B394: using guessed type int dword_51B394;
// 51B3E0: using guessed type int dword_51B3E0;

//----- (004C4C20) --------------------------------------------------------
int  Defgeneric_BloadRefreshRestrictionRecord(_DWORD *buf, int obji)
{
  int restrictionOffset; // edx
  int v4; // ecx
  char v5; // di
  int v6; // edx
  int v7; // ecx
  int typesIndex; // ebp
  int typesPtr; // ecx
  int queryIndex; // eax
  int queryPtr; // edx
  int result; // eax

  restrictionOffset = 40 * obji;
  *(_DWORD *)(restrictionOffset + g_DefgenericRestrictionRecords) = *buf;
  *(_DWORD *)(g_DefgenericRestrictionRecords + restrictionOffset + 4) = 0;
  v4 = g_DefgenericRestrictionRecords;
  v5 = g_Rules_WatchMethods;
  *(_BYTE *)(g_DefgenericRestrictionRecords + restrictionOffset + 24) &= ~2u;
  *(_DWORD *)(v4 + restrictionOffset + 24) |= 2 * (v5 & 1);
  *(_DWORD *)(g_DefgenericRestrictionRecords + restrictionOffset + 8) = buf[1];
  *(_DWORD *)(restrictionOffset + g_DefgenericRestrictionRecords + 12) = buf[2];
  *(_DWORD *)(g_DefgenericRestrictionRecords + restrictionOffset + 16) = buf[3];
  *(_DWORD *)(g_DefgenericRestrictionRecords + restrictionOffset + 20) = buf[4];
  v6 = g_DefgenericRestrictionRecords + restrictionOffset;
  v7 = buf[5];
  *(_BYTE *)(v6 + 24) &= ~1u;
  *(_DWORD *)(v6 + 24) |= v7 & 1;
  typesIndex = buf[6];
  if ( typesIndex == -1 )
    typesPtr = 0;
  else
    typesPtr = 12 * typesIndex + g_ClipsDefgenericBloadRestrictionTypeArray;
  *(_DWORD *)(g_DefgenericRestrictionRecords + 40 * obji + 28) = typesPtr;
  queryIndex = buf[7];
  if ( queryIndex == -1 )
    queryPtr = 0;
  else
    queryPtr = 14 * queryIndex + g_ClipsPackedExpressionArray;
  result = 5 * obji;
  *(_DWORD *)(g_DefgenericRestrictionRecords + 8 * result + 32) = queryPtr;
  *(_DWORD *)(g_DefgenericRestrictionRecords + 8 * result + 36) = 0;
  return result;
}
// 51B394: using guessed type int dword_51B394;
// 51B398: using guessed type int dword_51B398;
// 51B3E4: using guessed type int dword_51B3E4;
// 54E688: using guessed type int dword_54E688;

//----- (004C4D40) --------------------------------------------------------
int  Defgeneric_BloadRefreshRestrictionTypeRecord(_DWORD *buf, int obji)
{
  int typesPtr; // ebx
  int exprIndex; // edi
  int exprPtr; // ecx
  int result; // eax

  *(_DWORD *)(12 * obji + g_ClipsDefgenericBloadRestrictionTypeArray + 8) = buf[2];
  if ( *buf == -1 )
    typesPtr = 0;
  else
    typesPtr = g_DefgenericBloadRestrictionTypeArray + 4 * *buf;
  *(_DWORD *)(g_ClipsDefgenericBloadRestrictionTypeArray + 12 * obji) = typesPtr;
  exprIndex = buf[1];
  if ( exprIndex == -1 )
    exprPtr = 0;
  else
    exprPtr = 14 * exprIndex + g_ClipsPackedExpressionArray;
  result = 3 * obji;
  *(_DWORD *)(g_ClipsDefgenericBloadRestrictionTypeArray + 12 * obji + 4) = exprPtr;
  return result;
}
// 51B398: using guessed type int dword_51B398;
// 51B39C: using guessed type int dword_51B39C;
// 54E688: using guessed type int dword_54E688;

//----- (004C4DD0) --------------------------------------------------------
int  Defgeneric_BloadRefreshExpressionPointer(_DWORD *buf, int obji)
{
  int result; // eax

  if ( *buf == -1 )
  {
    result = 0;
    *(_DWORD *)(g_DefgenericBloadRestrictionTypeArray + 4 * obji) = 0;
  }
  else
  {
    result = g_Clips_DefclassArrayBase + 124 * *buf;
    *(_DWORD *)(g_DefgenericBloadRestrictionTypeArray + 4 * obji) = result;
  }
  return result;
}
// 51B39C: using guessed type int dword_51B39C;
// 51B3AC: using guessed type int dword_51B3AC;

//----- (004C4E10) --------------------------------------------------------
signed int Defgeneric_ClearBinaryData()
{
  signed int result; // eax
  int recordOffset; // edx
  int methodIndex; // ecx
  int v3; // edx

  result = 12 * g_DefgenericBloadCount;
  if ( 12 * g_DefgenericBloadCount )
  {
    Mem_ReleasePoolBlock(g_DefgenericBloadModuleRefArray, 12 * g_DefgenericBloadCount);
    recordOffset = 0;
    methodIndex = 0;
    g_DefgenericBloadModuleRefArray = 0;
    for ( g_DefgenericBloadCount = 0; methodIndex < g_Defgeneric_MethodRecordCount; recordOffset = v3 + 40 )
      Rules_ReleaseSymbolReference((int *)(recordOffset + g_DefgenericMethodArray), methodIndex + 1);
    result = g_Defgeneric_MethodRecordCount;
    if ( 40 * g_Defgeneric_MethodRecordCount )
    {
      Mem_ReleasePoolBlock(g_DefgenericMethodArray, 40 * g_Defgeneric_MethodRecordCount);
      result = g_Defgeneric_RestrictionRecordCount;
      g_DefgenericMethodArray = 0;
      g_Defgeneric_MethodRecordCount = 0;
      if ( 40 * g_Defgeneric_RestrictionRecordCount )
      {
        Mem_ReleasePoolBlock(g_DefgenericRestrictionRecords, 40 * g_Defgeneric_RestrictionRecordCount);
        result = g_Defgeneric_RestrictionTypeCount;
        g_DefgenericRestrictionRecords = 0;
        g_Defgeneric_RestrictionRecordCount = 0;
        if ( 12 * g_Defgeneric_RestrictionTypeCount )
        {
          result = Mem_ReleasePoolBlock(g_ClipsDefgenericBloadRestrictionTypeArray, 12 * g_Defgeneric_RestrictionTypeCount);
          g_ClipsDefgenericBloadRestrictionTypeArray = 0;
          g_Defgeneric_RestrictionTypeCount = 0;
          if ( 4 * g_Defgeneric_PackedExpressionCount )
          {
            result = Mem_ReleasePoolBlock(g_DefgenericBloadRestrictionTypeArray, 4 * g_Defgeneric_PackedExpressionCount);
            g_DefgenericBloadRestrictionTypeArray = 0;
            g_Defgeneric_PackedExpressionCount = 0;
          }
        }
      }
    }
  }
  return result;
}
// 4C4E65: variable 'v2' is possibly undefined
// 4C4E71: variable 'v3' is possibly undefined
// 51B378: using guessed type int dword_51B378;
// 51B37C: using guessed type int dword_51B37C;
// 51B380: using guessed type int dword_51B380;
// 51B384: using guessed type int dword_51B384;
// 51B388: using guessed type int dword_51B388;
// 51B38C: using guessed type int dword_51B38C;
// 51B390: using guessed type int dword_51B390;
// 51B394: using guessed type int dword_51B394;
// 51B398: using guessed type int dword_51B398;
// 51B39C: using guessed type int dword_51B39C;

//----- (004C4F50) --------------------------------------------------------
signed int Deffunction_RegisterBinaryItem()
{
  return Rules_RegisterBinaryItem(
           (int)aDeffunctions_0,
           0,
           (int)Deffunction_BsaveWriteExpressions,
           (int)Deffunction_CountBsaveEntries,
           (int)Deffunction_BsaveWriteBinaryHeader,
           (int)Deffunction_BsaveWriteConstructs,
           (int)Deffunction_BloadAllocateBinaryStorage,
           (int)Deffunction_BloadRefreshConstructs,
           (int)Deffunction_ClearBinaryData);
}

//----- (004C4F90) --------------------------------------------------------
int  Deffunction_RecordAtIndex(int theIndex)
{
  return 12 * theIndex + g_Clips_DeffunctionRecordArray;
}
// 54E894: using guessed type int dword_54E894;

//----- (004C4FB0) --------------------------------------------------------
signed int Deffunction_CountBsaveEntries()
{
  signed int result; // eax

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_Clips_DeffunctionCount);
    Rules_ConstructQueuePush(g_Deffunction_Count);
  }
  g_Deffunction_Count = 0;
  result = Rules_DoForAllConstructs((void (*)(void))Deffunction_CountAndMarkExpressions, 0);
  g_Clips_DeffunctionCount = result;
  return result;
}
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004C5000) --------------------------------------------------------
__int16  Deffunction_CountAndMarkExpressions(_DWORD *theDeffunction)
{
  int bsaveId; // edx
  int v2; // ecx
  int v3; // ecx

  bsaveId = g_Deffunction_Count++;
  AST_MarkNodeFieldBound(theDeffunction, bsaveId);
  g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v2 + 30));
  return Rules_MarkReferencedFunctions(*(__int16 **)(v3 + 30));
}
// 4C5018: variable 'v2' is possibly undefined
// 4C5026: variable 'v3' is possibly undefined
// 51B3A4: using guessed type int dword_51B3A4;
// 54E680: using guessed type int dword_54E680;

//----- (004C5030) --------------------------------------------------------
signed int Deffunction_BsaveWriteExpressions()
{
  return Rules_DoForAllConstructs((void (*)(void))Deffunction_BsaveWriteBodyExpression, 0);
}
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004C5050) --------------------------------------------------------
__int16 * Deffunction_BsaveWriteBodyExpression(int theDeffunction, int fp)
{
  return Rules_BsaveWriteExpression(*(__int16 **)(theDeffunction + 30), fp);
}

//----- (004C5060) --------------------------------------------------------
const void * Deffunction_BsaveWriteBinaryHeader(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 8;
  Rules_BsaveWriteBlock(4, fp, space);
  Rules_BsaveWriteBlock(4, v2, &g_Clips_DeffunctionCount);
  return Rules_BsaveWriteBlock(4, v3, &g_Deffunction_Count);
}
// 4C508A: variable 'v2' is possibly undefined
// 4C509B: variable 'v3' is possibly undefined
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;

//----- (004C50B0) --------------------------------------------------------
int  Deffunction_BsaveWriteConstructs(int fp, int a2)
{
  int theItem; // eax
  int v4; // ecx
  _DWORD *theModuleItem; // eax
  int v6; // ecx
  int result; // eax
  _DWORD dummyModule[3]; // [esp-Ch] [ebp-20h] BYREF
  _DWORD space[5]; // [esp+0h] [ebp-14h] BYREF

  space[3] = a2;
  space[0] = 32 * g_Deffunction_Count + 12 * g_Clips_DeffunctionCount;
  Rules_BsaveWriteBlock(4, fp, space);
  g_Deffunction_Count = 0;
  if ( Module_NextEnum(0) )
  {
    do
    {
      theItem = Module_FindItemByName((int)aDeffunction_2);
      theModuleItem = (_DWORD *)Module_GetItem(v4, *(_DWORD *)(theItem + 4));
      Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
      Rules_BsaveWriteBlock(12, fp, dummyModule);
    }
    while ( Module_NextEnum(v6) );
  }
  Rules_DoForAllConstructs((void (*)(void))Deffunction_BsaveWriteRecord, 0);
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_Clips_DeffunctionCount);
    return Rules_ConstructQueuePop(&g_Deffunction_Count);
  }
  return result;
}
// 4C5112: variable 'v4' is possibly undefined
// 4C5130: variable 'v6' is possibly undefined
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E6A8: using guessed type int dword_54E6A8;

//----- (004C5190) --------------------------------------------------------
const void * Deffunction_BsaveWriteRecord(int theDeffunction, int fp, int a3)
{
  int v4; // ecx
  _DWORD dummyDeffunction[7]; // [esp-Ch] [ebp-28h] BYREF
  int codeIndex; // [esp+10h] [ebp-Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a3;
  AST_ExtractPatternBindingInfo(dummyDeffunction, theDeffunction);
  dummyDeffunction[3] = *(_DWORD *)(v4 + 34);
  dummyDeffunction[4] = *(_DWORD *)(v4 + 38);
  dummyDeffunction[5] = *(_DWORD *)(v4 + 42);
  if ( *(_DWORD *)(v4 + 30) )
  {
    codeIndex = g_ClipsExpressionNodeIndex;
    g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v4 + 30));
  }
  else
  {
    codeIndex = -1;
  }
  return Rules_BsaveWriteBlock(32, fp, dummyDeffunction);
}
// 4C51A2: variable 'v4' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004C5200) --------------------------------------------------------
int __thiscall Deffunction_BloadAllocateBinaryStorage(void *this)
{
  int result; // eax
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = this;
  result = Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    Rules_BloadReadBlock((uintptr_t)&g_Clips_DeffunctionCount, 4u);
    result = Rules_BloadReadBlock((uintptr_t)&g_Deffunction_Count, 4u);
    if ( g_Clips_DeffunctionCount )
    {
      space[0] = 12 * g_Clips_DeffunctionCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_Clips_DeffunctionCount));
      g_Clips_DeffunctionRecordArray = result;
      if ( g_Deffunction_Count )
      {
        space[0] = 46 * g_Deffunction_Count;
        result = Mem_HeapAllocWithRetry((_DWORD *)(46 * g_Deffunction_Count));
        g_DeffunctionBloadRecordArray = result;
      }
      else
      {
        g_DeffunctionBloadRecordArray = 0;
      }
    }
    else
    {
      g_Clips_DeffunctionRecordArray = 0;
      g_DeffunctionBloadRecordArray = 0;
    }
  }
  return result;
}
// 51B3A0: using guessed type int dword_51B3A0;
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E894: using guessed type int dword_54E894;

//----- (004C52B0) --------------------------------------------------------
signed int Deffunction_BloadRefreshConstructs()
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  Rules_BloadAndRefresh(g_Clips_DeffunctionCount, 12, (void (__fastcall *)(signed int, signed int))Deffunction_BloadRefreshRecord);
  return Rules_BloadAndRefresh(g_Deffunction_Count, 32, (void (__fastcall *)(signed int, signed int))Deffunction_BloadRefreshBodyRecord);
}
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;

//----- (004C52F0) --------------------------------------------------------
_DWORD * Deffunction_BloadRefreshRecord(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(12 * obji + g_Clips_DeffunctionRecordArray), g_DeffunctionBloadRecordArray, 46);
}
// 51B3A0: using guessed type int dword_51B3A0;
// 54E894: using guessed type int dword_54E894;

//----- (004C5330) --------------------------------------------------------
int  Deffunction_BloadRefreshBodyRecord(_DWORD *buf, int obji)
{
  int theDeffunction; // esi
  int codeIndex; // edx
  int codeExpr; // eax
  int result; // eax

  theDeffunction = g_DeffunctionBloadRecordArray + 46 * obji;
  Rules_BuildIndexedSlotDescriptor((int)buf, (_DWORD *)theDeffunction, g_Clips_DeffunctionRecordArray, 12, 46, g_DeffunctionBloadRecordArray);
  codeIndex = buf[7];
  if ( codeIndex == -1 )
    codeExpr = 0;
  else
    codeExpr = g_ClipsPackedExpressionArray + 14 * codeIndex;
  *(_DWORD *)(theDeffunction + 20) = 0;
  *(_DWORD *)(theDeffunction + 24) = 0;
  *(_DWORD *)(theDeffunction + 30) = codeExpr;
  *(_WORD *)(theDeffunction + 28) = g_Rules_WatchDeffunctions;
  *(_DWORD *)(theDeffunction + 34) = buf[3];
  *(_DWORD *)(theDeffunction + 38) = buf[4];
  result = buf[5];
  *(_DWORD *)(theDeffunction + 42) = result;
  return result;
}
// 51AAE8: using guessed type int dword_51AAE8;
// 51B3A0: using guessed type int dword_51B3A0;
// 54E688: using guessed type int dword_54E688;
// 54E894: using guessed type int dword_54E894;

//----- (004C53B0) --------------------------------------------------------
signed int Deffunction_ClearBinaryData()
{
  signed int result; // eax
  int recordOffset; // ecx
  int v2; // ecx
  int v3; // edx

  result = 12 * g_Clips_DeffunctionCount;
  if ( 12 * g_Clips_DeffunctionCount )
  {
    result = Mem_ReleasePoolBlock(g_Clips_DeffunctionRecordArray, 12 * g_Clips_DeffunctionCount);
    g_Clips_DeffunctionRecordArray = 0;
    g_Clips_DeffunctionCount = 0;
    if ( g_Deffunction_Count > 0 )
    {
      recordOffset = 0;
      do
      {
        result = Rules_ReleaseSymbolReference((int *)(recordOffset + g_DeffunctionBloadRecordArray), recordOffset);
        recordOffset = v2 + 46;
      }
      while ( v3 < g_Deffunction_Count );
    }
    if ( 46 * g_Deffunction_Count )
    {
      result = Mem_ReleasePoolBlock(g_DeffunctionBloadRecordArray, 46 * g_Deffunction_Count);
      g_DeffunctionBloadRecordArray = 0;
      g_Deffunction_Count = 0;
    }
  }
  return result;
}
// 4C5411: variable 'v2' is possibly undefined
// 4C5416: variable 'v3' is possibly undefined
// 51B3A0: using guessed type int dword_51B3A0;
// 51B3A4: using guessed type int dword_51B3A4;
// 51B3A8: using guessed type int dword_51B3A8;
// 54E894: using guessed type int dword_54E894;

//----- (004C5450) --------------------------------------------------------
signed int Class_RegisterBinaryItem()
{
  Rules_AddAbortBloadFunction((int)aDefclass_0, (int)Class_CreateSystemClasses, 0);
  return Rules_RegisterBinaryItem(
           (int)aDefclass_0,
           0,
           (int)Class_BsaveWriteExpressions,
           (int)Class_CountBsaveEntries,
           (int)Class_BsaveWriteHeader,
           (int)Class_BsaveWriteData,
           (int)Class_BloadStorage,
           (int)Class_BloadBinaryItem,
           (int)Class_ClearBloadedData);
}

//----- (004C54A0) --------------------------------------------------------
int  Class_RecordAtIndex(int theIndex)
{
  return 12 * theIndex + g_Class_BloadModuleArray;
}
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C54C0) --------------------------------------------------------
_DWORD *Class_CountBsaveEntries()
{
  int i; // ecx
  _DWORD *result; // eax
  int slotNameId; // edx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DefclassNameTableCount);
    Rules_ConstructQueuePush(g_ClipsBloadDefclassCount);
    Rules_ConstructQueuePush(g_ClipsBloadClassLinkCount);
    Rules_ConstructQueuePush(g_Defclass_SlotRecordCount);
    Rules_ConstructQueuePush(g_ClipsDefclassBsaveHandlerCount);
    Rules_ConstructQueuePush(g_Defclass_SlotNameLinkCount);
    Rules_ConstructQueuePush(g_ClipsDefclassBsaveIndexArrayCount);
    Rules_ConstructQueuePush(g_ClipsBloadSlotRecordCount);
  }
  g_DefclassNameTableCount = 0;
  g_ClipsBloadDefclassCount = 0;
  g_ClipsDefclassBsaveHandlerCount = 0;
  g_Defclass_SlotRecordCount = 0;
  g_ClipsBloadClassLinkCount = 0;
  g_Defclass_SlotNameLinkCount = 0;
  g_ClipsDefclassBsaveIndexArrayCount = 0;
  g_ClipsBloadSlotRecordCount = 0;
  g_DefclassNameTableCount = Rules_DoForAllConstructs((void (*)(void))Class_CountSlotsAndMarkExpressions, 0);
  for ( i = 0; i != 668; i += 4 )
  {
    for ( result = *(_DWORD **)(i + g_Defclass_SlotNameHashTablePtr); result; result = (_DWORD *)result[5] )
    {
      if ( result[2] >= 2u )
      {
        slotNameId = g_Defclass_SlotRecordCount++;
        result[6] = slotNameId;
        *(_DWORD *)(result[3] + 12) |= 2u;
        *(_DWORD *)(result[4] + 12) |= 2u;
      }
    }
  }
  return result;
}
// 4C5541: simplified comparisons for 'ebx.4': ==0 || ==1 became <2u
// 51AD70: using guessed type int dword_51AD70;
// 54E6BC: using guessed type int dword_54E6BC;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C55E0) --------------------------------------------------------
int  Class_CountSlotsAndMarkExpressions(int theDefclass)
{
  int bsaveId; // edx
  _DWORD *classPtr; // ecx
  unsigned int slotIndex; // esi
  int slotOffset; // ebx
  int slotBsaveId; // eax
  int slotNameSym; // eax
  int theSlot; // eax
  int v9; // ecx
  unsigned int handlerIndex; // ebx
  int handlerOffset; // edx
  int handlerNameSym; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // edx
  int result; // eax
  signed int defaultExpr; // eax
  __int16 *v18; // edx
  int v19; // edx

  bsaveId = g_ClipsBloadDefclassCount++;
  AST_MarkNodeFieldBound((_DWORD *)theDefclass, bsaveId);
  g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(theDefclass + 40) + *(unsigned __int16 *)(theDefclass + 34) + *(unsigned __int16 *)(theDefclass + 46);
  *(_BYTE *)(*(_DWORD *)(theDefclass + 104) + 12) |= 2u;
  slotIndex = 0;
  if ( *(_DWORD *)(theDefclass + 64) )
  {
    slotOffset = 0;
    do
    {
      slotBsaveId = g_ClipsDefclassBsaveHandlerCount++;
      *(_DWORD *)(classPtr[13] + slotOffset + 28) = slotBsaveId;
      slotNameSym = *(_DWORD *)(slotOffset + classPtr[13] + 12);
      *(_BYTE *)(slotNameSym + 12) |= 2u;
      theSlot = slotOffset + classPtr[13];
      if ( *(_DWORD *)(theSlot + 16) )
      {
        if ( (*(_BYTE *)theSlot & 0x40) != 0 )
        {
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(theSlot + 16));
          Rules_MarkReferencedFunctions(*(__int16 **)(slotOffset + *(_DWORD *)(v9 + 52) + 16));
        }
        else
        {
          defaultExpr = AST_BuildExpressionFromValue(*(_DWORD **)(theSlot + 16));
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(defaultExpr);
          Rules_MarkReferencedFunctions(v18);
          AST_Free(v19);
        }
      }
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < classPtr[16] );
  }
  g_Defclass_SlotNameLinkCount += classPtr[18];
  if ( classPtr[18] )
    g_ClipsDefclassBsaveIndexArrayCount += classPtr[19] + 1;
  handlerIndex = 0;
  if ( classPtr[24] )
  {
    handlerOffset = 0;
    do
    {
      handlerNameSym = *(_DWORD *)(handlerOffset + classPtr[22] + 8);
      *(_BYTE *)(handlerNameSym + 12) |= 2u;
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(handlerOffset + classPtr[22] + 28));
      ++handlerIndex;
      Rules_MarkReferencedFunctions(*(__int16 **)(v14 + *(_DWORD *)(v13 + 88) + 28));
      handlerOffset = v15 + 36;
    }
    while ( handlerIndex < classPtr[24] );
  }
  result = classPtr[24];
  g_ClipsBloadSlotRecordCount += result;
  return result;
}
// 4C563A: variable 'v3' is possibly undefined
// 4C566E: variable 'v9' is possibly undefined
// 4C56D9: variable 'v14' is possibly undefined
// 4C56D6: variable 'v13' is possibly undefined
// 4C56E6: variable 'v15' is possibly undefined
// 4C5725: variable 'v18' is possibly undefined
// 4C572C: variable 'v19' is possibly undefined
// 54E680: using guessed type int dword_54E680;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5740) --------------------------------------------------------
void Class_BsaveWriteExpressions()
{
  if ( g_ClipsBloadDefclassCount || g_ClipsBloadSlotRecordCount )
  {
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveHandlerExpressions, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveSlotExpressions, 0);
  }
}
// 54E6BC: using guessed type int dword_54E6BC;
// 54E89C: using guessed type int dword_54E89C;
// 54E8B0: using guessed type int dword_54E8B0;

//----- (004C5790) --------------------------------------------------------
__int16 * Class_BsaveHandlerExpressions(__int16 *result, int fp)
{
  __int16 *theDefclass; // ebp
  unsigned int slotIndex; // edi
  int slotOffset; // esi
  __int16 *defaultExpr; // eax
  int v7; // ecx

  theDefclass = result;
  slotIndex = 0;
  if ( *((_DWORD *)result + 16) )
  {
    slotOffset = 0;
    do
    {
      result = (__int16 *)(slotOffset + *((_DWORD *)theDefclass + 13));
      if ( *((_DWORD *)result + 4) )
      {
        if ( (*(_BYTE *)result & 0x40) != 0 )
        {
          result = Rules_BsaveWriteExpression(*((__int16 **)result + 4), fp);
        }
        else
        {
          defaultExpr = (__int16 *)AST_BuildExpressionFromValue(*((_DWORD **)result + 4));
          Rules_BsaveWriteExpression(defaultExpr, fp);
          result = (__int16 *)AST_Free(v7);
        }
      }
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < *((_DWORD *)theDefclass + 16) );
  }
  return result;
}
// 4C57E2: variable 'v7' is possibly undefined

//----- (004C57F0) --------------------------------------------------------
__int16 * Class_BsaveSlotExpressions(__int16 *result, int fp)
{
  int theDefclass; // edi
  unsigned int handlerIndex; // ebx
  int handlerOffset; // ecx
  int v6; // ecx

  theDefclass = (int)result;
  handlerIndex = 0;
  if ( *((_DWORD *)result + 24) )
  {
    handlerOffset = 0;
    do
    {
      ++handlerIndex;
      result = Rules_BsaveWriteExpression(*(__int16 **)(handlerOffset + *(_DWORD *)(theDefclass + 88) + 28), fp);
      handlerOffset = v6 + 36;
    }
    while ( handlerIndex < *(_DWORD *)(theDefclass + 96) );
  }
  return result;
}
// 4C5816: variable 'v6' is possibly undefined

//----- (004C5830) --------------------------------------------------------
const void * Class_BsaveWriteHeader(int fp, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  if ( g_ClipsBloadDefclassCount || g_ClipsBloadSlotRecordCount )
  {
    space[0] = 36;
    Rules_BsaveWriteBlock(4, fp, space);
    Rules_BsaveWriteBlock(4, v3, &g_DefclassNameTableCount);
    Rules_BsaveWriteBlock(4, v4, &g_ClipsBloadDefclassCount);
    Rules_BsaveWriteBlock(4, v5, &g_ClipsBloadClassLinkCount);
    Rules_BsaveWriteBlock(4, v6, &g_Defclass_SlotRecordCount);
    Rules_BsaveWriteBlock(4, v7, &g_ClipsDefclassBsaveHandlerCount);
    Rules_BsaveWriteBlock(4, v8, &g_Defclass_SlotNameLinkCount);
    Rules_BsaveWriteBlock(4, v9, &g_ClipsDefclassBsaveIndexArrayCount);
    Rules_BsaveWriteBlock(4, v10, &g_ClipsBloadSlotRecordCount);
    space[0] = (unsigned __int16)g_ClipsDefclassIdCount;
    return Rules_BsaveWriteBlock(4, v11, space);
  }
  else
  {
    space[0] = g_ClipsBloadDefclassCount;
    return Rules_BsaveWriteBlock(4, fp, space);
  }
}
// 4C5889: variable 'v3' is possibly undefined
// 4C589A: variable 'v4' is possibly undefined
// 4C58AB: variable 'v5' is possibly undefined
// 4C58BC: variable 'v6' is possibly undefined
// 4C58CD: variable 'v7' is possibly undefined
// 4C58DE: variable 'v8' is possibly undefined
// 4C58EF: variable 'v9' is possibly undefined
// 4C5900: variable 'v10' is possibly undefined
// 4C591C: variable 'v11' is possibly undefined
// 51AD6C: using guessed type __int16 word_51AD6C;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5930) --------------------------------------------------------
const void * Class_BsaveWriteData(int fp)
{
  int theItem; // eax
  int v3; // ecx
  _DWORD *theModuleItem; // eax
  int v5; // ecx
  int bucketOffset; // edi
  _DWORD *i; // ecx
  const void *result; // eax
  _DWORD dummySlotName[4]; // [esp+0h] [ebp-38h] BYREF
  _DWORD dummyModule[3]; // [esp+10h] [ebp-28h] BYREF
  _DWORD space[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  if ( g_ClipsBloadDefclassCount || g_ClipsBloadSlotRecordCount )
  {
    space[0] = 4 * g_ClipsBloadSlotRecordCount
           + 16 * g_Defclass_SlotRecordCount
           + 12 * g_DefclassNameTableCount
           + 76 * g_ClipsBloadDefclassCount
           + 4 * g_ClipsBloadClassLinkCount
           + 24 * g_ClipsDefclassBsaveHandlerCount
           + 4 * g_Defclass_SlotNameLinkCount
           + 4 * g_ClipsDefclassBsaveIndexArrayCount
           + 28 * g_ClipsBloadSlotRecordCount;
    Rules_BsaveWriteBlock(4, fp, space);
    g_ClipsBloadDefclassCount = 0;
    g_ClipsBloadClassLinkCount = 0;
    g_ClipsDefclassBsaveHandlerCount = 0;
    g_Defclass_SlotRecordCount = 0;
    g_Defclass_SlotNameLinkCount = 0;
    g_ClipsDefclassBsaveIndexArrayCount = 0;
    g_ClipsBloadSlotRecordCount = 0;
    if ( Module_NextEnum(0) )
    {
      do
      {
        theItem = Module_FindItemByName((int)aDefclass_0);
        theModuleItem = (_DWORD *)Module_GetItem(v3, *(_DWORD *)(theItem + 4));
        Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
        Rules_BsaveWriteBlock(12, fp, dummyModule);
      }
      while ( Module_NextEnum(v5) );
    }
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteClassRecord, 0);
    g_ClipsBloadClassLinkCount = 0;
    bucketOffset = 0;
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteSuperclassLists, 0);
    do
    {
      for ( i = *(_DWORD **)(g_Defclass_SlotNameHashTablePtr + bucketOffset); i; i = (_DWORD *)i[5] )
      {
        if ( i[2] >= 2u )
        {
          dummySlotName[0] = i[2];
          dummySlotName[1] = *i;
          dummySlotName[2] = *(_DWORD *)(i[3] + 12) << 16 >> 18;
          dummySlotName[3] = *(_DWORD *)(i[4] + 12) << 16 >> 18;
          Rules_BsaveWriteBlock(16, fp, dummySlotName);
        }
      }
      bucketOffset += 4;
    }
    while ( bucketOffset != 668 );
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteHandlerRecords, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteSlotNameTable, 0);
    Rules_DoForAllConstructs((void (*)(void))&g_Class_BsaveWriteUnknownSectionFn, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteSlotRecords, 0);
    Rules_DoForAllConstructs((void (*)(void))Class_BsaveWriteHandlerDispatchTable, 0);
    result = (const void *)Rules_IsBloaded();
    if ( result )
    {
      Rules_ConstructQueuePop(&g_DefclassNameTableCount);
      Rules_ConstructQueuePop(&g_ClipsBloadDefclassCount);
      Rules_ConstructQueuePop(&g_ClipsBloadClassLinkCount);
      Rules_ConstructQueuePop(&g_ClipsDefclassBsaveHandlerCount);
      Rules_ConstructQueuePop(&g_Defclass_SlotRecordCount);
      Rules_ConstructQueuePop(&g_Defclass_SlotNameLinkCount);
      Rules_ConstructQueuePop(&g_ClipsDefclassBsaveIndexArrayCount);
      return (const void *)Rules_ConstructQueuePop(&g_ClipsBloadSlotRecordCount);
    }
  }
  else
  {
    space[0] = g_ClipsBloadDefclassCount;
    return Rules_BsaveWriteBlock(4, fp, space);
  }
  return result;
}
// 4C5AD2: simplified comparisons for 'edx.4': ==0 || ==1 became <2u
// 4C5A4D: variable 'v3' is possibly undefined
// 4C5A6C: variable 'v5' is possibly undefined
// 4C5B10: variable 'i' is possibly undefined
// 4C61F0: using guessed type void *off_4C61F0;
// 51AD70: using guessed type int dword_51AD70;
// 54E6BC: using guessed type int dword_54E6BC;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5C10) --------------------------------------------------------
const void * Class_BsaveWriteClassRecord(int theDefclass, int fp)
{
  int classPtr; // ecx
  unsigned int v5; // eax
  int v6; // eax
  int v7; // eax
  _DWORD dummyClass[3]; // [esp+0h] [ebp-60h] BYREF
  int flagsWord; // [esp+Ch] [ebp-54h]
  __int16 classId; // [esp+10h] [ebp-50h]
  __int16 directSuperclassCount; // [esp+12h] [ebp-4Eh]
  int superclassListIndex; // [esp+14h] [ebp-4Ch]
  __int16 directSubclassCount; // [esp+18h] [ebp-48h]
  int subclassListIndex; // [esp+1Ah] [ebp-46h]
  __int16 allSuperclassCount; // [esp+1Eh] [ebp-42h]
  int allSuperclassListIndex; // [esp+20h] [ebp-40h]
  int slotCount; // [esp+24h] [ebp-3Ch]
  int v19; // [esp+28h] [ebp-38h]
  int v20; // [esp+2Ch] [ebp-34h]
  int v21; // [esp+30h] [ebp-30h]
  int handlerCount; // [esp+34h] [ebp-2Ch]
  int slotsIndex; // [esp+38h] [ebp-28h]
  int instanceTemplateIndex; // [esp+3Ch] [ebp-24h]
  int slotNameMapIndex; // [esp+40h] [ebp-20h]
  int handlersIndex; // [esp+44h] [ebp-1Ch]
  int scopeMapIndex; // [esp+48h] [ebp-18h]

  AST_ExtractPatternBindingInfo(dummyClass, theDefclass);
  v5 = *(_DWORD *)(classPtr + 20) << 29;
  LOBYTE(flagsWord) = flagsWord & 0xFE;
  flagsWord |= v5 >> 31;
  v6 = *(_DWORD *)(classPtr + 20) << 28 >> 31;
  LOBYTE(flagsWord) = flagsWord & 0xFD;
  flagsWord |= 2 * (v6 & 1);
  v7 = *(_DWORD *)(classPtr + 20) << 30 >> 31;
  LOBYTE(flagsWord) = flagsWord & 0xFB;
  flagsWord |= 4 * (v7 & 1);
  classId = *(_WORD *)(classPtr + 24);
  slotCount = *(_DWORD *)(classPtr + 64);
  v20 = *(_DWORD *)(classPtr + 72);
  v19 = *(_DWORD *)(classPtr + 68);
  v21 = *(_DWORD *)(classPtr + 76);
  handlerCount = *(_DWORD *)(classPtr + 96);
  directSuperclassCount = *(_WORD *)(classPtr + 34);
  directSubclassCount = *(_WORD *)(classPtr + 40);
  allSuperclassCount = *(_WORD *)(classPtr + 46);
  if ( *(_WORD *)(classPtr + 34) )
  {
    superclassListIndex = g_ClipsBloadClassLinkCount;
    g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(classPtr + 34);
  }
  else
  {
    superclassListIndex = -1;
  }
  if ( *(_WORD *)(theDefclass + 40) )
  {
    subclassListIndex = g_ClipsBloadClassLinkCount;
    g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(theDefclass + 40);
  }
  else
  {
    subclassListIndex = -1;
  }
  if ( *(_WORD *)(theDefclass + 46) )
  {
    allSuperclassListIndex = g_ClipsBloadClassLinkCount;
    g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(theDefclass + 46);
  }
  else
  {
    allSuperclassListIndex = -1;
  }
  if ( *(_DWORD *)(theDefclass + 52) )
  {
    slotsIndex = g_ClipsDefclassBsaveHandlerCount;
    g_ClipsDefclassBsaveHandlerCount += *(_DWORD *)(theDefclass + 64);
  }
  else
  {
    slotsIndex = -1;
  }
  if ( *(_DWORD *)(theDefclass + 56) )
  {
    instanceTemplateIndex = g_Defclass_SlotNameLinkCount;
    g_Defclass_SlotNameLinkCount += *(_DWORD *)(theDefclass + 72);
    slotNameMapIndex = g_ClipsDefclassBsaveIndexArrayCount;
    g_ClipsDefclassBsaveIndexArrayCount += *(_DWORD *)(theDefclass + 76) + 1;
  }
  else
  {
    instanceTemplateIndex = -1;
    slotNameMapIndex = -1;
  }
  if ( *(_DWORD *)(theDefclass + 88) )
  {
    handlersIndex = g_ClipsBloadSlotRecordCount;
    g_ClipsBloadSlotRecordCount += *(_DWORD *)(theDefclass + 96);
  }
  else
  {
    handlersIndex = -1;
  }
  scopeMapIndex = *(_DWORD *)(*(_DWORD *)(theDefclass + 104) + 12) << 16 >> 18;
  return Rules_BsaveWriteBlock(76, fp, dummyClass);
}
// 4C5C2B: variable 'v4' is possibly undefined
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C5E50) --------------------------------------------------------
unsigned __int16  Class_BsaveWriteSuperclassLists(int theDefclass, int fp)
{
  int classPtr; // ecx
  unsigned int superclassIndex; // ebp
  int superclassOffset; // edi
  unsigned int subclassIndex; // edi
  int subclassOffset; // ebp
  unsigned int allSuperclassIndex; // ebp
  int allSuperclassOffset; // edi
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  unsigned __int16 result; // ax
  _DWORD dummyClassIndex[6]; // [esp+0h] [ebp-18h] BYREF

  classPtr = theDefclass;
  superclassIndex = 0;
  superclassOffset = 0;
  while ( superclassIndex < *(unsigned __int16 *)(classPtr + 34) )
  {
    v12 = superclassOffset + *(_DWORD *)(classPtr + 36);
    if ( *(_DWORD *)v12 )
      v13 = *(_DWORD *)(*(_DWORD *)v12 + 12);
    else
      v13 = -1;
    dummyClassIndex[0] = v13;
    superclassOffset += 4;
    ++superclassIndex;
    Rules_BsaveWriteBlock(4, fp, dummyClassIndex);
  }
  subclassIndex = 0;
  subclassOffset = 0;
  g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(classPtr + 34);
  while ( subclassIndex < *(unsigned __int16 *)(classPtr + 40) )
  {
    v14 = subclassOffset + *(_DWORD *)(classPtr + 42);
    if ( *(_DWORD *)v14 )
      v15 = *(_DWORD *)(*(_DWORD *)v14 + 12);
    else
      v15 = -1;
    dummyClassIndex[0] = v15;
    subclassOffset += 4;
    ++subclassIndex;
    Rules_BsaveWriteBlock(4, fp, dummyClassIndex);
  }
  allSuperclassIndex = 0;
  g_ClipsBloadClassLinkCount += *(unsigned __int16 *)(classPtr + 40);
  allSuperclassOffset = 0;
  while ( allSuperclassIndex < *(unsigned __int16 *)(classPtr + 46) )
  {
    v10 = allSuperclassOffset + *(_DWORD *)(classPtr + 48);
    if ( *(_DWORD *)v10 )
      v11 = *(_DWORD *)(*(_DWORD *)v10 + 12);
    else
      v11 = -1;
    dummyClassIndex[0] = v11;
    allSuperclassOffset += 4;
    ++allSuperclassIndex;
    Rules_BsaveWriteBlock(4, fp, dummyClassIndex);
  }
  result = *(_WORD *)(classPtr + 46);
  g_ClipsBloadClassLinkCount += result;
  return result;
}
// 4C5E62: variable 'v3' is possibly undefined
// 54E8A8: using guessed type int dword_54E8A8;

//----- (004C5F70) --------------------------------------------------------
int  Class_BsaveWriteHandlerRecords(int result, int fp)
{
  unsigned int slotIndex; // edi
  int slotOffset; // esi
  int *theSlot; // edx
  int v6; // eax
  unsigned int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  unsigned int v14; // eax
  unsigned int v15; // eax
  unsigned int v16; // eax
  unsigned int v17; // eax
  int slotClass; // ebx
  int v19; // eax
  int v20; // edx
  int v21; // eax
  signed int defaultExpr; // eax
  int v23; // ecx
  int theConstraint; // ebx
  _DWORD dummySlot[3]; // [esp+0h] [ebp-30h] BYREF
  int defaultValueIndex; // [esp+Ch] [ebp-24h]
  int constraintIndex; // [esp+10h] [ebp-20h]
  int slotNameIndex; // [esp+14h] [ebp-1Ch]
  int theDefclass; // [esp+18h] [ebp-18h]

  theDefclass = result;
  slotIndex = 0;
  if ( *(_DWORD *)(result + 64) )
  {
    slotOffset = 0;
    do
    {
      theSlot = (int *)(slotOffset + *(_DWORD *)(theDefclass + 52));
      v6 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~0x40u;
      dummySlot[0] |= v6 & 0x40;
      v7 = (unsigned int)(*theSlot << 23) >> 31;
      LOBYTE(dummySlot[0]) &= ~0x80u;
      dummySlot[0] |= (v7 & 1) << 7;
      v8 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~1u;
      dummySlot[0] |= v8 & 1;
      v9 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~2u;
      dummySlot[0] |= v9 & 2;
      v10 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~4u;
      dummySlot[0] |= v10 & 4;
      v11 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~8u;
      dummySlot[0] |= v11 & 8;
      v12 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~0x10u;
      dummySlot[0] |= v12 & 0x10;
      v13 = *theSlot;
      LOBYTE(dummySlot[0]) &= ~0x20u;
      dummySlot[0] |= v13 & 0x20;
      v14 = (unsigned int)(*theSlot << 22) >> 31;
      BYTE1(dummySlot[0]) &= ~1u;
      dummySlot[0] |= (v14 & 1) << 8;
      v15 = (unsigned int)(*theSlot << 21) >> 31;
      BYTE1(dummySlot[0]) &= ~2u;
      dummySlot[0] |= (v15 & 1) << 9;
      v16 = (unsigned int)(*theSlot << 20) >> 31;
      BYTE1(dummySlot[0]) &= ~4u;
      dummySlot[0] |= (v16 & 1) << 10;
      v17 = (unsigned int)(*theSlot << 19) >> 31;
      BYTE1(dummySlot[0]) &= ~8u;
      dummySlot[0] |= (v17 & 1) << 11;
      slotClass = theSlot[1];
      if ( slotClass )
        v19 = *(_DWORD *)(slotClass + 12);
      else
        v19 = -1;
      dummySlot[1] = v19;
      dummySlot[2] = *(_DWORD *)(theSlot[2] + 24);
      slotNameIndex = *(_DWORD *)(theSlot[3] + 12) << 16 >> 18;
      if ( theSlot[4] )
      {
        defaultValueIndex = g_ClipsExpressionNodeIndex;
        if ( (*(_BYTE *)theSlot & 0x40) != 0 )
        {
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theSlot[4]);
        }
        else
        {
          defaultExpr = AST_BuildExpressionFromValue((_DWORD *)theSlot[4]);
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(defaultExpr);
          AST_Free(v23);
        }
      }
      else
      {
        defaultValueIndex = -1;
      }
      if ( Rules_DynamicConstraintCheckingEnabled() && (theConstraint = *(_DWORD *)(v20 + 20)) != 0 )
        v21 = *(unsigned __int16 *)(theConstraint + 4);
      else
        v21 = -1;
      constraintIndex = v21;
      Rules_BsaveWriteBlock(24, fp, dummySlot);
      result = theDefclass;
      ++slotIndex;
      slotOffset += 44;
    }
    while ( slotIndex < *(_DWORD *)(theDefclass + 64) );
  }
  return result;
}
// 4C6167: variable 'v23' is possibly undefined
// 4C6178: variable 'v20' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004C6190) --------------------------------------------------------
_DWORD * Class_BsaveWriteSlotNameTable(_DWORD *result, int fp)
{
  int theDefclass; // ebp
  unsigned int linkIndex; // esi
  int linkOffset; // ecx
  int v6; // eax
  int slotNameId; // eax
  int v8; // ecx
  int indexBuffer[6]; // [esp+0h] [ebp-18h] BYREF

  theDefclass = (int)result;
  linkIndex = 0;
  if ( result[18] )
  {
    linkOffset = 0;
    do
    {
      v6 = linkOffset + *(_DWORD *)(theDefclass + 56);
      if ( *(_DWORD *)v6 )
        slotNameId = *(_DWORD *)(*(_DWORD *)v6 + 28);
      else
        slotNameId = -1;
      indexBuffer[0] = slotNameId;
      ++linkIndex;
      result = Rules_BsaveWriteBlock(4, fp, indexBuffer);
      linkOffset = v8 + 4;
    }
    while ( linkIndex < *(_DWORD *)(theDefclass + 72) );
  }
  return result;
}
// 4C61CA: variable 'v8' is possibly undefined

//----- (004C6220) --------------------------------------------------------
_DWORD * Class_BsaveWriteSlotRecords(_DWORD *result, int fp)
{
  int theDefclass; // ebp
  unsigned int handlerIndex; // esi
  int handlerOffset; // ecx
  int *theHandler; // edx
  int v7; // eax
  int v8; // eax
  int handlerClass; // eax
  int classIndex; // eax
  int v11; // ecx
  _DWORD dummyHandler[6]; // [esp+0h] [ebp-30h] BYREF
  int actionsIndex; // [esp+18h] [ebp-18h]

  theDefclass = (int)result;
  handlerIndex = 0;
  if ( result[24] )
  {
    handlerOffset = 0;
    do
    {
      theHandler = (int *)(handlerOffset + *(_DWORD *)(theDefclass + 88));
      v7 = *theHandler;
      LOBYTE(dummyHandler[0]) &= ~1u;
      dummyHandler[0] |= v7 & 1;
      v8 = *theHandler;
      LOBYTE(dummyHandler[0]) &= 0xF9u;
      dummyHandler[0] |= v8 & 6;
      dummyHandler[1] = theHandler[4];
      dummyHandler[2] = theHandler[5];
      dummyHandler[3] = theHandler[6];
      handlerClass = theHandler[3];
      if ( handlerClass )
        classIndex = *(_DWORD *)(handlerClass + 12);
      else
        classIndex = -1;
      dummyHandler[5] = classIndex;
      dummyHandler[4] = *(_DWORD *)(theHandler[2] + 12) << 16 >> 18;
      if ( theHandler[7] )
      {
        actionsIndex = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theHandler[7]);
      }
      else
      {
        actionsIndex = -1;
      }
      result = Rules_BsaveWriteBlock(28, fp, dummyHandler);
      ++handlerIndex;
      handlerOffset = v11 + 36;
    }
    while ( handlerIndex < *(_DWORD *)(theDefclass + 96) );
  }
  return result;
}
// 4C62C6: variable 'v11' is possibly undefined
// 54E680: using guessed type int dword_54E680;

//----- (004C62F0) --------------------------------------------------------
const void * Class_BsaveWriteHandlerDispatchTable(int theDefclass, int fp)
{
  return Rules_BsaveWriteBlock(4 * *(_DWORD *)(theDefclass + 96), fp, *(const void **)(theDefclass + 92));
}

//----- (004C6310) --------------------------------------------------------
_DWORD *__thiscall Class_BloadStorage(void *this)
{
  _DWORD *result; // eax
  _DWORD counts[8]; // [esp+0h] [ebp-40h] BYREF
  _DWORD *maxClassId; // [esp+20h] [ebp-20h]
  unsigned int space[7]; // [esp+24h] [ebp-1Ch] BYREF

  if ( g_ClipsDefclassIdTable || g_ClipsDefclassIdCount )
  {
    Rules_ReportSystemError((int)this, 1);
    IO_RunRouterExitCallbacks();
  }
  result = (_DWORD *)Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    Rules_BloadReadBlock((uintptr_t)counts, space[0]);
    g_DefclassNameTableCount = counts[0];
    g_ClipsBloadDefclassCount = counts[1];
    g_ClipsBloadClassLinkCount = counts[2];
    g_Defclass_SlotRecordCount = counts[3];
    g_ClipsDefclassBsaveHandlerCount = counts[4];
    g_Defclass_SlotNameLinkCount = counts[5];
    g_ClipsDefclassBsaveIndexArrayCount = counts[6];
    g_ClipsBloadSlotRecordCount = counts[7];
    result = maxClassId;
    g_ClipsDefclassIdCount = (__int16)maxClassId;
    if ( counts[0] )
    {
      space[0] = 12 * counts[0];
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(12 * counts[0]));
      g_Class_BloadModuleArray = (int)result;
    }
    if ( g_ClipsBloadDefclassCount )
    {
      space[0] = 124 * g_ClipsBloadDefclassCount;
      g_Clips_DefclassArrayBase = Mem_HeapAllocWithRetry((_DWORD *)(124 * g_ClipsBloadDefclassCount));
      result = Mem_SmallBlockAlloc(4 * (unsigned __int16)g_ClipsDefclassIdCount);
      g_ClipsDefclassIdTable = (int)result;
    }
    if ( g_ClipsBloadClassLinkCount )
    {
      space[0] = 4 * g_ClipsBloadClassLinkCount;
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(4 * g_ClipsBloadClassLinkCount));
      g_DefclassLinkTable = (int)result;
    }
    if ( g_ClipsDefclassBsaveHandlerCount )
    {
      space[0] = 44 * g_ClipsDefclassBsaveHandlerCount;
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(44 * g_ClipsDefclassBsaveHandlerCount));
      g_DefclassSlotDescriptorArrayPtr = (int)result;
    }
    if ( g_Defclass_SlotRecordCount )
    {
      space[0] = 28 * g_Defclass_SlotRecordCount;
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(28 * g_Defclass_SlotRecordCount));
      g_DefclassSlotTable = (int)result;
    }
    if ( g_Defclass_SlotNameLinkCount )
    {
      space[0] = 4 * g_Defclass_SlotNameLinkCount;
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(4 * g_Defclass_SlotNameLinkCount));
      g_DefclassBloadSlotNameLinkArray = (int)result;
    }
    if ( g_ClipsDefclassBsaveIndexArrayCount )
    {
      space[0] = 4 * g_ClipsDefclassBsaveIndexArrayCount;
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(4 * g_ClipsDefclassBsaveIndexArrayCount));
      g_Class_BloadClassLinkArray = (int)result;
    }
    if ( g_ClipsBloadSlotRecordCount )
    {
      space[0] = 36 * g_ClipsBloadSlotRecordCount;
      g_DefclassBloadTemplateSlotArray = Mem_HeapAllocWithRetry((_DWORD *)(36 * g_ClipsBloadSlotRecordCount));
      space[0] = 4 * g_ClipsBloadSlotRecordCount;
      result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)(4 * g_ClipsBloadSlotRecordCount));
      g_Class_BloadSlotNameMapArray = (int)result;
    }
  }
  else
  {
    g_ClipsBloadSlotRecordCount = 0;
    g_ClipsBloadDefclassCount = 0;
  }
  return result;
}
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;
// 51B3BC: using guessed type int dword_51B3BC;
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C4: using guessed type int dword_51B3C4;
// 51B3C8: using guessed type int dword_51B3C8;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C6530) --------------------------------------------------------
int Class_BloadBinaryItem()
{
  int result; // eax
  int space[5]; // [esp+0h] [ebp-14h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)space, 4u);
  if ( space[0] )
  {
    if ( g_DefclassNameTableCount )
      result = Rules_BloadAndRefresh(g_DefclassNameTableCount, 12, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshNameTable);
    if ( g_ClipsBloadDefclassCount )
    {
      Rules_BloadAndRefresh(g_ClipsBloadDefclassCount, 76, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshClassRecords);
      Rules_BloadAndRefresh(g_ClipsBloadClassLinkCount, 4, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshSuperclassLink);
      Rules_BloadAndRefresh(g_Defclass_SlotRecordCount, 16, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshSlotRecord);
      Rules_BloadAndRefresh(g_ClipsDefclassBsaveHandlerCount, 24, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshHandlerRecord);
      if ( g_Defclass_SlotNameLinkCount )
        Rules_BloadAndRefresh(g_Defclass_SlotNameLinkCount, 4, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshSlotNameLink);
      if ( g_ClipsDefclassBsaveIndexArrayCount )
      {
        space[0] = 4 * g_ClipsDefclassBsaveIndexArrayCount;
        Rules_BloadReadBlock(g_Class_BloadClassLinkArray, 4 * g_ClipsDefclassBsaveIndexArrayCount);
      }
      if ( g_ClipsBloadSlotRecordCount )
      {
        Rules_BloadAndRefresh(g_ClipsBloadSlotRecordCount, 28, (void (__fastcall *)(signed int, signed int))Class_BloadRefreshTemplateSlotRecord);
        space[0] = 4 * g_ClipsBloadSlotRecordCount;
        Rules_BloadReadBlock(g_Class_BloadSlotNameMapArray, 4 * g_ClipsBloadSlotRecordCount);
      }
      return Class_BloadFixupNameTable();
    }
  }
  return result;
}
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C8: using guessed type int dword_51B3C8;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;

//----- (004C6650) --------------------------------------------------------
int Class_BloadFixupNameTable()
{
  int result; // eax
  int classOffset; // edx
  int classPtr; // ecx

  result = 0;
  classOffset = 0;
  do
  {
    ++result;
    classPtr = classOffset + g_Clips_DefclassArrayBase;
    classOffset += 124;
    g_Class_WatchSlots[result] = classPtr;
  }
  while ( result != 9 );
  return result * 4;
}
// 51AD78: using guessed type int dword_51AD78[];
// 51B3AC: using guessed type int dword_51B3AC;

//----- (004C6680) --------------------------------------------------------
_DWORD * Class_BloadRefreshNameTable(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(12 * obji + g_Class_BloadModuleArray), g_Clips_DefclassArrayBase, 124);
}
// 51B3AC: using guessed type int dword_51B3AC;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C66C0) --------------------------------------------------------
int  Class_BloadRefreshClassRecords(int buf, int obji)
{
  int theDefclass; // esi
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int superclassListIndex; // ebx
  int v10; // edi
  int superclassListPtr; // eax
  int subclassListIndex; // ebp
  int subclassListPtr; // eax
  int allSuperclassListIndex; // eax
  int allSuperclassListPtr; // eax
  int slotsIndex; // edx
  int slotsPtr; // eax
  int instanceTemplateIndex; // ebx
  int instanceTemplatePtr; // eax
  int slotNameMapIndex; // ebp
  int slotNameMapPtr; // eax
  int handlersIndex; // eax
  int handlersPtr; // eax
  int handlerMapIndex; // edx
  int handlerMapPtr; // eax
  char v26; // ch
  int scopeMap; // eax

  theDefclass = g_Clips_DefclassArrayBase + 124 * obji;
  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)theDefclass, g_Class_BloadModuleArray, 12, 124, g_Clips_DefclassArrayBase);
  v4 = *(_DWORD *)(buf + 12) & 1;
  *(_BYTE *)(theDefclass + 20) &= ~4u;
  *(_DWORD *)(theDefclass + 20) |= 4 * v4;
  v5 = *(_DWORD *)(buf + 12) << 30 >> 31;
  *(_BYTE *)(theDefclass + 20) &= ~8u;
  *(_DWORD *)(theDefclass + 20) |= 8 * (v5 & 1);
  v6 = *(_DWORD *)(buf + 12) << 29 >> 31;
  *(_BYTE *)(theDefclass + 20) &= ~2u;
  *(_DWORD *)(theDefclass + 20) |= 2 * (v6 & 1);
  *(_WORD *)(theDefclass + 24) = *(_WORD *)(buf + 16);
  *(_DWORD *)(4 * *(unsigned __int16 *)(theDefclass + 24) + g_ClipsDefclassIdTable) = theDefclass;
  v7 = g_Rules_WatchInstances & 1;
  *(_BYTE *)(theDefclass + 20) &= ~0x10u;
  *(_DWORD *)(theDefclass + 20) |= 16 * v7;
  v8 = g_Class_WatchSlots[0] & 1;
  *(_BYTE *)(theDefclass + 20) &= ~0x20u;
  *(_DWORD *)(theDefclass + 20) |= 32 * v8;
  *(_DWORD *)(theDefclass + 64) = *(_DWORD *)(buf + 36);
  *(_DWORD *)(theDefclass + 72) = *(_DWORD *)(buf + 44);
  *(_DWORD *)(theDefclass + 68) = *(_DWORD *)(buf + 40);
  *(_DWORD *)(theDefclass + 76) = *(_DWORD *)(buf + 48);
  *(_DWORD *)(theDefclass + 96) = *(_DWORD *)(buf + 52);
  *(_WORD *)(theDefclass + 34) = *(_WORD *)(buf + 18);
  superclassListIndex = *(_DWORD *)(buf + 20);
  v10 = buf;
  if ( superclassListIndex == -1 )
    superclassListPtr = 0;
  else
    superclassListPtr = g_DefclassLinkTable + 4 * superclassListIndex;
  *(_DWORD *)(theDefclass + 36) = superclassListPtr;
  *(_WORD *)(theDefclass + 40) = *(_WORD *)(buf + 24);
  subclassListIndex = *(_DWORD *)(buf + 26);
  if ( subclassListIndex == -1 )
    subclassListPtr = 0;
  else
    subclassListPtr = g_DefclassLinkTable + 4 * subclassListIndex;
  *(_DWORD *)(theDefclass + 42) = subclassListPtr;
  *(_WORD *)(theDefclass + 46) = *(_WORD *)(v10 + 30);
  allSuperclassListIndex = *(_DWORD *)(v10 + 32);
  if ( allSuperclassListIndex == -1 )
    allSuperclassListPtr = 0;
  else
    allSuperclassListPtr = g_DefclassLinkTable + 4 * allSuperclassListIndex;
  *(_DWORD *)(theDefclass + 48) = allSuperclassListPtr;
  slotsIndex = *(_DWORD *)(v10 + 56);
  if ( slotsIndex == -1 )
    slotsPtr = 0;
  else
    slotsPtr = g_DefclassSlotDescriptorArrayPtr + 44 * slotsIndex;
  *(_DWORD *)(theDefclass + 52) = slotsPtr;
  instanceTemplateIndex = *(_DWORD *)(v10 + 60);
  if ( instanceTemplateIndex == -1 )
    instanceTemplatePtr = 0;
  else
    instanceTemplatePtr = g_DefclassBloadSlotNameLinkArray + 4 * instanceTemplateIndex;
  *(_DWORD *)(theDefclass + 56) = instanceTemplatePtr;
  slotNameMapIndex = *(_DWORD *)(v10 + 64);
  if ( slotNameMapIndex == -1 )
    slotNameMapPtr = 0;
  else
    slotNameMapPtr = g_Class_BloadClassLinkArray + 4 * slotNameMapIndex;
  *(_DWORD *)(theDefclass + 80) = 0;
  *(_DWORD *)(theDefclass + 60) = slotNameMapPtr;
  handlersIndex = *(_DWORD *)(v10 + 68);
  if ( handlersIndex == -1 )
    handlersPtr = 0;
  else
    handlersPtr = 36 * handlersIndex + g_DefclassBloadTemplateSlotArray;
  *(_DWORD *)(theDefclass + 88) = handlersPtr;
  handlerMapIndex = *(_DWORD *)(v10 + 68);
  if ( handlerMapIndex == -1 )
    handlerMapPtr = 0;
  else
    handlerMapPtr = 4 * handlerMapIndex + g_Class_BloadSlotNameMapArray;
  *(_DWORD *)(theDefclass + 26) = 0;
  *(_DWORD *)(theDefclass + 80) = 0;
  *(_DWORD *)(theDefclass + 84) = 0;
  v26 = *(_BYTE *)(theDefclass + 20);
  *(_DWORD *)(theDefclass + 92) = handlerMapPtr;
  *(_BYTE *)(theDefclass + 20) = v26 | 1;
  scopeMap = *(_DWORD *)(g_ClipsBloadBitmapPointerTable + 4 * *(_DWORD *)(v10 + 72));
  *(_DWORD *)(theDefclass + 104) = scopeMap;
  ++*(_DWORD *)(scopeMap + 4);
  return Class_AddToHashTable(theDefclass);
}
// 51AD64: using guessed type int dword_51AD64;
// 51AD74: using guessed type int dword_51AD74;
// 51AD78: using guessed type int dword_51AD78[];
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C4: using guessed type int dword_51B3C4;
// 51B3C8: using guessed type int dword_51B3C8;
// 54E67C: using guessed type int dword_54E67C;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C6950) --------------------------------------------------------
int  Class_BloadRefreshSuperclassLink(_DWORD *buf, int obji)
{
  int result; // eax

  if ( *buf == -1 )
  {
    result = 0;
    *(_DWORD *)(g_DefclassLinkTable + 4 * obji) = 0;
  }
  else
  {
    result = g_Clips_DefclassArrayBase + 124 * *buf;
    *(_DWORD *)(g_DefclassLinkTable + 4 * obji) = result;
  }
  return result;
}
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;

//----- (004C6990) --------------------------------------------------------
int  Class_BloadRefreshHandlerRecord(int *buf, int obji, double a3)
{
  int theSlot; // ecx
  int v4; // edx
  unsigned int v5; // edx
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  unsigned int v12; // edx
  unsigned int v13; // edx
  unsigned int v14; // edx
  unsigned int v15; // edx
  int clsIndex; // edx
  int clsPtr; // eax
  int slotName; // eax
  int defaultIndex; // edi
  int constraintIndex; // ebx
  int result; // eax
  _DWORD *v23; // ebp
  signed int defaultValue; // eax
  _DWORD *v25; // ebx
  int v26; // eax
  int defaultExpr; // edx
  int v28; // ecx

  theSlot = 44 * obji + g_DefclassSlotDescriptorArrayPtr;
  v4 = *buf;
  *(_BYTE *)theSlot &= ~0x40u;
  *(_DWORD *)theSlot |= v4 & 0x40;
  v5 = (unsigned int)(*buf << 24) >> 31;
  *(_BYTE *)(theSlot + 1) &= ~1u;
  *(_DWORD *)theSlot |= (v5 & 1) << 8;
  v6 = *buf;
  *(_BYTE *)theSlot &= ~1u;
  *(_DWORD *)theSlot |= v6 & 1;
  v7 = *buf;
  *(_BYTE *)theSlot &= ~2u;
  *(_DWORD *)theSlot |= v7 & 2;
  v8 = *buf;
  *(_BYTE *)theSlot &= ~4u;
  *(_DWORD *)theSlot |= v8 & 4;
  v9 = *buf;
  *(_BYTE *)theSlot &= ~8u;
  *(_DWORD *)theSlot |= v9 & 8;
  v10 = *buf;
  *(_BYTE *)theSlot &= ~0x10u;
  *(_DWORD *)theSlot |= v10 & 0x10;
  v11 = *buf;
  *(_BYTE *)theSlot &= ~0x20u;
  *(_DWORD *)theSlot |= v11 & 0x20;
  v12 = (unsigned int)(*buf << 23) >> 31;
  *(_BYTE *)(theSlot + 1) &= ~2u;
  *(_DWORD *)theSlot |= (v12 & 1) << 9;
  v13 = (unsigned int)(*buf << 22) >> 31;
  *(_BYTE *)(theSlot + 1) &= ~4u;
  *(_DWORD *)theSlot |= (v13 & 1) << 10;
  v14 = (unsigned int)(*buf << 21) >> 31;
  *(_BYTE *)(theSlot + 1) &= ~8u;
  *(_DWORD *)theSlot |= (v14 & 1) << 11;
  v15 = (unsigned int)(*buf << 20) >> 31;
  *(_BYTE *)(theSlot + 1) &= ~0x10u;
  *(_DWORD *)theSlot |= (v15 & 1) << 12;
  clsIndex = buf[1];
  if ( clsIndex == -1 )
    clsPtr = 0;
  else
    clsPtr = g_Clips_DefclassArrayBase + 124 * clsIndex;
  *(_DWORD *)(theSlot + 4) = clsPtr;
  *(_DWORD *)(theSlot + 8) = 28 * buf[2] + g_DefclassSlotTable;
  slotName = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * buf[5]);
  *(_DWORD *)(theSlot + 12) = slotName;
  ++*(_DWORD *)(slotName + 4);
  defaultIndex = buf[3];
  if ( defaultIndex == -1 )
  {
    *(_DWORD *)(theSlot + 16) = 0;
  }
  else if ( (*(_BYTE *)theSlot & 0x40) != 0 )
  {
    *(_DWORD *)(theSlot + 16) = g_ClipsPackedExpressionArray + 14 * defaultIndex;
  }
  else
  {
    v23 = *(_DWORD **)(g_ClipsMemoryTable + 96);
    if ( v23 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = *v23;
      defaultValue = g_ClipsMemFreeListTemp;
    }
    else
    {
      defaultValue = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    *(_DWORD *)(theSlot + 16) = defaultValue;
    v25 = (_DWORD *)defaultValue;
    v26 = buf[3];
    if ( v26 == -1 )
      defaultExpr = 0;
    else
      defaultExpr = 14 * v26 + g_ClipsPackedExpressionArray;
    Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)theSlot << 30 >> 31, defaultExpr, v25, a3);
    Rules_ValueInstall(*(_DWORD *)(theSlot + 16), theSlot);
  }
  constraintIndex = buf[4];
  if ( constraintIndex == -1 )
    result = 0;
  else
    result = g_ClipsConstraintRecordArrayBase + 42 * constraintIndex;
  *(_DWORD *)(theSlot + 24) = 0;
  *(_DWORD *)(theSlot + 40) = 0;
  *(_DWORD *)(theSlot + 20) = result;
  BYTE1(result) = *(_BYTE *)theSlot;
  *(_DWORD *)(theSlot + 28) = 0;
  if ( (result & 0x100) != 0 )
  {
    *(_DWORD *)(theSlot + 40) = 0;
    *(_DWORD *)(theSlot + 32) = theSlot;
  }
  return result;
}
// 4C6AEC: conditional instruction was optimized away because edi.4!=FFFFFFFF
// 4C6B01: variable 'v3' is possibly undefined
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3BC: using guessed type int dword_51B3BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E674: using guessed type int dword_54E674;
// 54E688: using guessed type int dword_54E688;
// 54E68C: using guessed type int dword_54E68C;

//----- (004C6C00) --------------------------------------------------------
_DWORD * Class_BloadRefreshSlotRecord(_DWORD *buf, int obji)
{
  _DWORD *result; // eax
  int nameSym; // edx
  int putHandlerSym; // edx
  int hashIndex; // edx

  result = (_DWORD *)(g_DefclassSlotTable + 28 * obji);
  result[2] = *buf;
  nameSym = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * buf[2]);
  result[3] = nameSym;
  ++*(_DWORD *)(nameSym + 4);
  putHandlerSym = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * buf[3]);
  result[4] = putHandlerSym;
  ++*(_DWORD *)(putHandlerSym + 4);
  hashIndex = buf[1];
  *result = hashIndex;
  result[5] = *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * hashIndex);
  *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * *result) = result;
  return result;
}
// 51AD70: using guessed type int dword_51AD70;
// 51B3BC: using guessed type int dword_51B3BC;
// 54E674: using guessed type int dword_54E674;

//----- (004C6C70) --------------------------------------------------------
int  Class_BloadRefreshSlotNameLink(_DWORD *buf, int obji)
{
  int result; // eax

  if ( *buf == -1 )
  {
    result = 0;
    *(_DWORD *)(g_DefclassBloadSlotNameLinkArray + 4 * obji) = 0;
  }
  else
  {
    result = 44 * *buf + g_DefclassSlotDescriptorArrayPtr;
    *(_DWORD *)(g_DefclassBloadSlotNameLinkArray + 4 * obji) = result;
  }
  return result;
}
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;

//----- (004C6CA0) --------------------------------------------------------
char * Class_BloadRefreshTemplateSlotRecord(int *buf, int obji)
{
  char *result; // eax
  int v4; // edx
  int v5; // edx
  int clsIndex; // ebp
  int clsPtr; // edx
  int nameSym; // edx
  int actionsIndex; // esi
  int actionsPtr; // edx
  char v11; // dl
  int v12; // edx

  result = (char *)(g_DefclassBloadTemplateSlotArray + 36 * obji);
  v4 = *buf;
  *result &= ~1u;
  *(_DWORD *)result |= v4 & 1;
  v5 = *buf;
  *result &= 0xF9u;
  *(_DWORD *)result |= v5 & 6;
  *((_DWORD *)result + 4) = buf[1];
  *((_DWORD *)result + 5) = buf[2];
  *((_DWORD *)result + 6) = buf[3];
  clsIndex = buf[5];
  if ( clsIndex == -1 )
    clsPtr = 0;
  else
    clsPtr = 124 * clsIndex + g_Clips_DefclassArrayBase;
  *((_DWORD *)result + 3) = clsPtr;
  nameSym = *(_DWORD *)(g_ClipsBloadSymbolPointerArray + 4 * buf[4]);
  *((_DWORD *)result + 2) = nameSym;
  ++*(_DWORD *)(nameSym + 4);
  actionsIndex = buf[6];
  if ( actionsIndex == -1 )
    actionsPtr = 0;
  else
    actionsPtr = 14 * actionsIndex + g_ClipsPackedExpressionArray;
  *((_DWORD *)result + 8) = 0;
  *((_DWORD *)result + 7) = actionsPtr;
  v11 = *result;
  *((_DWORD *)result + 1) = 0;
  *result = v11 & 0xF7;
  v12 = g_Rules_WatchMessageHandlers & 1;
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * v12;
  return result;
}
// 51AD4C: using guessed type int dword_51AD4C;
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3C4: using guessed type int dword_51B3C4;
// 54E674: using guessed type int dword_54E674;
// 54E688: using guessed type int dword_54E688;

//----- (004C6D80) --------------------------------------------------------
signed int Class_ClearBloadedData()
{
  signed int result; // eax
  int v1; // edx
  int v2; // ecx
  int v3; // edx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // edx
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // edx

  result = 12 * g_DefclassNameTableCount;
  if ( 12 * g_DefclassNameTableCount )
  {
    result = Mem_ReleasePoolBlock(g_Class_BloadModuleArray, 12 * g_DefclassNameTableCount);
    HIWORD(v1) = 0;
    g_Class_BloadModuleArray = 0;
    g_DefclassNameTableCount = 0;
    if ( g_ClipsBloadDefclassCount )
    {
      LOWORD(v1) = g_ClipsDefclassIdCount;
      Mem_SmallBlockFree((_DWORD *)g_ClipsDefclassIdTable, 4 * v1);
      g_ClipsDefclassIdTable = 0;
      g_ClipsDefclassIdCount = 0;
      if ( g_ClipsBloadDefclassCount > 0 )
      {
        v3 = 0;
        do
        {
          Rules_ReleaseSymbolReference((int *)(v3 + g_Clips_DefclassArrayBase), v2);
          Rules_DecrementBitmapCount(*(_DWORD *)(v4 + g_Clips_DefclassArrayBase + 104), v5);
          Class_RemoveFromHashTable(v6 + g_Clips_DefclassArrayBase);
          v3 = v7 + 124;
        }
        while ( v2 < g_ClipsBloadDefclassCount );
      }
      v8 = 0;
      if ( g_ClipsDefclassBsaveHandlerCount > 0 )
      {
        v9 = 0;
        do
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(v9 + g_DefclassSlotDescriptorArrayPtr + 12), v8);
          if ( *(_DWORD *)(v10 + g_DefclassSlotDescriptorArrayPtr + 16) && (*(_BYTE *)(v10 + g_DefclassSlotDescriptorArrayPtr) & 0x40) == 0 )
          {
            Rules_ValueDeinstall(*(_DWORD *)(v10 + g_DefclassSlotDescriptorArrayPtr + 16), v11);
            g_ClipsMemFreeListTemp = *(_DWORD *)(v10 + g_DefclassSlotDescriptorArrayPtr + 16);
            *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
            *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
          }
          v8 = v11 + 1;
          v9 = v10 + 44;
        }
        while ( v8 < g_ClipsDefclassBsaveHandlerCount );
      }
      v12 = 0;
      if ( g_Defclass_SlotRecordCount > 0 )
      {
        v13 = 0;
        do
        {
          *(_DWORD *)(g_Defclass_SlotNameHashTablePtr + 4 * *(_DWORD *)(v13 + g_DefclassSlotTable)) = 0;
          Rules_DecrementSymbolCount(*(_DWORD *)(v13 + g_DefclassSlotTable + 12), v12);
          Rules_DecrementSymbolCount(*(_DWORD *)(v14 + g_DefclassSlotTable + 16), v15 + 1);
          v13 = v16 + 28;
        }
        while ( v12 < g_Defclass_SlotRecordCount );
      }
      if ( 124 * g_ClipsBloadDefclassCount )
      {
        Mem_ReleasePoolBlock(g_Clips_DefclassArrayBase, 124 * g_ClipsBloadDefclassCount);
        g_Clips_DefclassArrayBase = 0;
        g_ClipsBloadDefclassCount = 0;
      }
      if ( 4 * g_ClipsBloadClassLinkCount )
      {
        Mem_ReleasePoolBlock(g_DefclassLinkTable, 4 * g_ClipsBloadClassLinkCount);
        g_DefclassLinkTable = v17;
        g_ClipsBloadClassLinkCount = v17;
      }
      if ( 44 * g_ClipsDefclassBsaveHandlerCount )
      {
        Mem_ReleasePoolBlock(g_DefclassSlotDescriptorArrayPtr, 44 * g_ClipsDefclassBsaveHandlerCount);
        g_DefclassSlotDescriptorArrayPtr = 0;
        g_ClipsDefclassBsaveHandlerCount = 0;
      }
      result = 28 * g_Defclass_SlotRecordCount;
      if ( 28 * g_Defclass_SlotRecordCount )
      {
        Mem_ReleasePoolBlock(g_DefclassSlotTable, 28 * g_Defclass_SlotRecordCount);
        result = 0;
        g_DefclassSlotTable = 0;
        g_Defclass_SlotRecordCount = 0;
      }
      if ( 4 * g_Defclass_SlotNameLinkCount )
      {
        result = Mem_ReleasePoolBlock(g_DefclassBloadSlotNameLinkArray, 4 * g_Defclass_SlotNameLinkCount);
        g_DefclassBloadSlotNameLinkArray = v18;
        g_Defclass_SlotNameLinkCount = v18;
      }
      if ( 4 * g_ClipsDefclassBsaveIndexArrayCount )
      {
        result = Mem_ReleasePoolBlock(g_Class_BloadClassLinkArray, 4 * g_ClipsDefclassBsaveIndexArrayCount);
        g_Class_BloadClassLinkArray = 0;
        g_ClipsDefclassBsaveIndexArrayCount = 0;
      }
    }
    if ( g_ClipsBloadSlotRecordCount )
    {
      v19 = 0;
      if ( g_ClipsBloadSlotRecordCount > 0 )
      {
        v20 = 0;
        do
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(v20 + g_DefclassBloadTemplateSlotArray + 8), v19 + 1);
          v20 = v21 + 36;
        }
        while ( v19 < g_ClipsBloadSlotRecordCount );
      }
      result = 36 * g_ClipsBloadSlotRecordCount;
      if ( 36 * g_ClipsBloadSlotRecordCount )
      {
        Mem_ReleasePoolBlock(g_DefclassBloadTemplateSlotArray, 36 * g_ClipsBloadSlotRecordCount);
        g_DefclassBloadTemplateSlotArray = 0;
        result = Mem_ReleasePoolBlock(g_Class_BloadSlotNameMapArray, 4 * g_ClipsBloadSlotRecordCount);
        g_Class_BloadSlotNameMapArray = 0;
        g_ClipsBloadSlotRecordCount = 0;
      }
    }
  }
  return result;
}
// 4C6E10: variable 'v2' is possibly undefined
// 4C6E1A: variable 'v4' is possibly undefined
// 4C6E1E: variable 'v5' is possibly undefined
// 4C6E28: variable 'v6' is possibly undefined
// 4C6E36: variable 'v7' is possibly undefined
// 4C6E60: variable 'v10' is possibly undefined
// 4C6E70: variable 'v11' is possibly undefined
// 4C6EDB: variable 'v12' is possibly undefined
// 4C6EE5: variable 'v14' is possibly undefined
// 4C6EE9: variable 'v15' is possibly undefined
// 4C6EF5: variable 'v16' is possibly undefined
// 4C6F4D: variable 'v17' is possibly undefined
// 4C6FCD: variable 'v18' is possibly undefined
// 4C7021: variable 'v19' is possibly undefined
// 4C702D: variable 'v21' is possibly undefined
// 51AD64: using guessed type int dword_51AD64;
// 51AD6C: using guessed type __int16 word_51AD6C;
// 51AD70: using guessed type int dword_51AD70;
// 51B3AC: using guessed type int dword_51B3AC;
// 51B3B0: using guessed type int dword_51B3B0;
// 51B3B4: using guessed type int dword_51B3B4;
// 51B3B8: using guessed type int dword_51B3B8;
// 51B3BC: using guessed type int dword_51B3BC;
// 51B3C0: using guessed type int dword_51B3C0;
// 51B3C4: using guessed type int dword_51B3C4;
// 51B3C8: using guessed type int dword_51B3C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E898: using guessed type int dword_54E898;
// 54E89C: using guessed type int dword_54E89C;
// 54E8A0: using guessed type int dword_54E8A0;
// 54E8A4: using guessed type int dword_54E8A4;
// 54E8A8: using guessed type int dword_54E8A8;
// 54E8AC: using guessed type int dword_54E8AC;
// 54E8B0: using guessed type int dword_54E8B0;
// 54E8B4: using guessed type int dword_54E8B4;
// 54E8B8: using guessed type int dword_54E8B8;

//----- (004C70F0) --------------------------------------------------------
int Deffacts_CommandDefinitions()
{
  int v0; // ecx

  Rules_AddResetFunction((int)aDeffacts_0, (int)Deffacts_Reset, 0);
  Rules_AddClearFunction((int)aDeffacts_0, (int)Deffacts_ClearAction, 0);
  Rules_AddSaveFunction((int)aDeffacts_0, (int)Deffacts_Save, 10);
  Rules_RegisterHostFunction(aGetDeffactsLis, 109, v0, (int)Deffacts_GetListFunction, (int)a01w_6);
  Rules_RegisterHostFunction(aUndeffacts, 118, (int)aUndeffactscomm, (int)Deffacts_UndefCommand, (int)a11w_10);
  Rules_RegisterHostFunction(aDeffactsModule, 119, (int)aDeffactsmodule, (int)Deffacts_ModuleFunction, (int)a11w_10);
  Rules_RegisterHostFunction(aListDeffacts, 118, (int)aListdeffactsco, (int)Deffacts_ListCommand, (int)a01w_6);
  Rules_RegisterHostFunction(aPpdeffacts, 118, (int)aPpdeffactscomm, (int)Deffacts_PPCommand, (int)a11w_10);
  Deffacts_RegisterBinaryItem();
  return Deffacts_CompilerSetup();
}
// 4C7142: variable 'v0' is possibly undefined

//----- (004C71D0) --------------------------------------------------------
signed int Deffacts_Reset()
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))Deffacts_ResetAction, g_ClipsDeffactsModuleItemId, 0, 1);
}
// 54E698: using guessed type int dword_54E698;

//----- (004C71F0) --------------------------------------------------------
int  Deffacts_ResetAction(int result, intptr_t context)
{
  uintptr_t record; // ecx
  uintptr_t expression; // eax
  _DWORD parsed[6]; // [esp+0h] [ebp-18h] BYREF

  (void)context;
  record = (uintptr_t)(unsigned int)result;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(record + 20);
  if ( expression )
  {
    Lexer_ErrorRecover(0);
    return Parser_ParseForm((__int16 *)expression, parsed, (int)record, 0.0);
  }
  return (int)record;
}

//----- (004C7220) --------------------------------------------------------
int Deffacts_ClearAction()
{
  int **assert_symbol; // eax
  int assert_node; // ebx
  int initial_template; // eax
  int value_node; // eax
  int deffacts_record; // edx
  signed int *initial_name; // eax
  _DWORD *rhs_copy; // eax

  assert_symbol = Rules_MakeSymbol(aAssert_2);
  assert_node = AST_NewNode(10, (int)assert_symbol);
  initial_template = Rules_FindDeftemplateByName(aInitialFact_1, assert_node);
  value_node = AST_NewNode(35, initial_template);
  *(_DWORD *)(assert_node + 6) = value_node;
  AST_InstallNodeChain((__int16 *)assert_node);
  deffacts_record = *(_DWORD *)(g_ClipsMemoryTable + 96);
  if ( deffacts_record )
  {
    g_ClipsMemFreeListTemp = deffacts_record;
    *(_DWORD *)(g_ClipsMemoryTable + 96) = *(_DWORD *)deffacts_record;
    deffacts_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    deffacts_record = Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  *(_DWORD *)(deffacts_record + 8) = Rules_GetDeffactsModuleItem(0);
  initial_name = Str_Intern(aInitialFact_1, (int)aInitialFact_1);
  *(_DWORD *)deffacts_record = initial_name;
  ++initial_name[1];
  rhs_copy = AST_PackNodeChain((_DWORD *)assert_node);
  *(_DWORD *)(deffacts_record + 16) = 0;
  *(_DWORD *)(deffacts_record + 20) = rhs_copy;
  *(_DWORD *)(deffacts_record + 4) = 0;
  AST_Free(assert_node);
  return Rules_AppendConstructToModuleList(deffacts_record);
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C72D0) --------------------------------------------------------
int  Deffacts_Save(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C72E0) --------------------------------------------------------
int __thiscall Deffacts_UndefCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7300) --------------------------------------------------------
int  Deffacts_DeleteConstruct(int theConstruct, int a2)
{
  return Rules_DeleteConstructOrAll(theConstruct, g_ClipsDeffactsConstructType, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7310) --------------------------------------------------------
_DWORD * Deffacts_GetListFunction(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDeffactsConstructType, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7350) --------------------------------------------------------
int __thiscall Deffacts_ModuleFunction(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C7370) --------------------------------------------------------
int __thiscall Deffacts_PPCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_ClipsDeffactsConstructType);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C73A0) --------------------------------------------------------
int  Deffacts_ListCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDeffactsConstructType, a1, a2);
}
// 54E69C: using guessed type int dword_54E69C;

//----- (004C73E0) --------------------------------------------------------
signed int  Deffacts_ParseAndInstall(int readSource)
{
  int deffactsName; // edi
  int v4; // eax
  _DWORD *temp; // esi
  __int16 *v6; // ecx
  _DWORD *v7; // ebp
  int *newDeffacts; // ecx
  _DWORD *assertList; // eax
  int v10; // ecx
  int theItem; // eax
  int v12; // ecx
  int v13; // ebx
  int theModuleItem; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  char *ppForm; // eax
  int v19; // ecx
  _DWORD inputToken[3]; // [esp+0h] [ebp-28h] BYREF
  int error[7]; // [esp+Ch] [ebp-1Ch] BYREF

  error[0] = 0;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDeffacts_3);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  deffactsName = Rules_GetConstructNameAndComment(readSource, (int)inputToken, (int (*)(void))Rules_ParseDeffactsConstruct, aDeffacts_4, (int (*)(void))Deffacts_DeleteConstruct, asc_50AFAC, 1, 1, 1);
  if ( !deffactsName )
    return 1;
  v4 = Rules_ParseAssertCommand(readSource, inputToken, 0, error, 0, (int)aDeffacts_4);
  temp = (_DWORD *)v4;
  if ( error[0] == 1 )
    return 1;
  if ( AST_TreeContainsSpecialTag(v4, 0) )
  {
    Rules_ReportLocalVariableError();
    AST_Free(v17);
    return 1;
  }
  else
  {
    IO_OutWriteToken(asc_50AFC8);
    AST_InstallNodeChain(v6);
    v7 = *(_DWORD **)(g_ClipsMemoryTable + 96);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = *v7;
      newDeffacts = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDeffacts = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    *newDeffacts = deffactsName;
    ++*(_DWORD *)(deffactsName + 4);
    assertList = AST_PackNodeChain(temp);
    *(_DWORD *)(v10 + 20) = assertList;
    theItem = Module_FindItemByName((int)aDeffacts_4);
    v13 = v12;
    theModuleItem = Module_GetItem(0, *(_DWORD *)(theItem + 4));
    *(_DWORD *)(v15 + 8) = theModuleItem;
    *(_DWORD *)(v15 + 16) = 0;
    AST_Free((int)temp);
    if ( Mem_GetAllocFlag() == 1 )
    {
      *(_DWORD *)(v16 + 4) = 0;
    }
    else
    {
      ppForm = Rules_CopyPPBuffer();
      *(_DWORD *)(v19 + 4) = ppForm;
    }
    Rules_AppendConstructToModuleList(v13);
    return 0;
  }
}
// 4C74B0: variable 'v6' is possibly undefined
// 4C74DD: variable 'v10' is possibly undefined
// 4C74EF: variable 'v12' is possibly undefined
// 4C74F6: variable 'v15' is possibly undefined
// 4C7511: variable 'v16' is possibly undefined
// 4C7537: variable 'v17' is possibly undefined
// 4C7567: variable 'v19' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C7580) --------------------------------------------------------
signed int Deffacts_RegisterBinaryItem()
{
  return Rules_RegisterBinaryItem(
           (int)aDeffacts_1,
           0,
           (int)Deffacts_BsaveExpressions,
           (int)Deffacts_BsaveFind,
           (int)Deffacts_BsaveWriteHeader,
           (int)Deffacts_BsaveWriteData,
           (int)Deffacts_BloadStorage,
           (int)Deffacts_BloadBinaryItem,
           (int)Deffacts_ClearBload);
}

//----- (004C75C0) --------------------------------------------------------
int Deffacts_BsaveFind()
{
  int result; // eax
  int i; // ebx
  _DWORD *j; // ecx
  int bsaveId; // edx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_DeffactsModuleItemCount);
    Rules_ConstructQueuePush(g_DeffactsBsaveCount);
  }
  g_DeffactsBsaveCount = 0;
  g_DeffactsModuleItemCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    ++g_DeffactsModuleItemCount;
    for ( j = (_DWORD *)Rules_DeffactsGetNextItem(0); j; j = (_DWORD *)Rules_DeffactsGetNextItem(v6) )
    {
      bsaveId = g_DeffactsBsaveCount++;
      AST_MarkNodeFieldBound(j, bsaveId);
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v4 + 20));
      Rules_MarkReferencedFunctions(*(__int16 **)(v5 + 20));
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 4C7632: variable 'v4' is possibly undefined
// 4C7640: variable 'v5' is possibly undefined
// 4C764A: variable 'v6' is possibly undefined
// 51B3D0: using guessed type int dword_51B3D0;
// 54E680: using guessed type int dword_54E680;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7670) --------------------------------------------------------
int  Deffacts_BsaveExpressions(int fp)
{
  int result; // eax
  int i; // esi
  int j; // ecx
  int v5; // ecx

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_DeffactsGetNextItem(0); j; j = Rules_DeffactsGetNextItem(v5) )
      Rules_BsaveWriteExpression(*(__int16 **)(j + 20), fp);
    result = Module_NextEnum(i);
  }
  return result;
}
// 4C76A3: variable 'v5' is possibly undefined

//----- (004C76C0) --------------------------------------------------------
const void * Deffacts_BsaveWriteHeader(int fp, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 8;
  Rules_BsaveWriteBlock(4, fp, space);
  Rules_BsaveWriteBlock(4, v2, &g_DeffactsBsaveCount);
  return Rules_BsaveWriteBlock(4, v3, &g_DeffactsModuleItemCount);
}
// 4C76EA: variable 'v2' is possibly undefined
// 4C76FB: variable 'v3' is possibly undefined
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7710) --------------------------------------------------------
int  Deffacts_BsaveWriteData(int fp)
{
  int i; // ecx
  _DWORD *theModuleItem; // eax
  int v4; // ecx
  int j; // edi
  int k; // ecx
  int v7; // ecx
  int v8; // ecx
  int result; // eax
  _DWORD dummyDeffacts[3]; // [esp+0h] [ebp-38h] BYREF
  int assertListIndex; // [esp+Ch] [ebp-2Ch]
  _DWORD dummyModule[3]; // [esp+10h] [ebp-28h] BYREF
  int space[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  space[0] = 12 * g_DeffactsModuleItemCount + 16 * g_DeffactsBsaveCount;
  Rules_BsaveWriteBlock(4, fp, space);
  g_DeffactsBsaveCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v4) )
  {
    Module_SetCurrent(i);
    theModuleItem = (_DWORD *)Module_GetItem(0, g_ClipsDeffactsModuleItemId);
    Module_AssignBsaveItemHeaderIndices(dummyModule, theModuleItem);
    Rules_BsaveWriteBlock(12, fp, dummyModule);
  }
  for ( j = Module_NextEnum(0); j; j = Module_NextEnum(j) )
  {
    Module_SetCurrent(j);
    for ( k = Rules_DeffactsGetNextItem(0); k; k = Rules_DeffactsGetNextItem(v8) )
    {
      AST_ExtractPatternBindingInfo(dummyDeffacts, k);
      if ( *(_DWORD *)(v7 + 20) )
      {
        assertListIndex = g_ClipsExpressionNodeIndex;
        g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(v7 + 20));
      }
      else
      {
        assertListIndex = -1;
      }
      Rules_BsaveWriteBlock(16, fp, dummyDeffacts);
    }
  }
  result = Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_DeffactsModuleItemCount);
    return Rules_ConstructQueuePop(&g_DeffactsBsaveCount);
  }
  return result;
}
// 4C779A: variable 'v4' is possibly undefined
// 4C77DC: variable 'v7' is possibly undefined
// 4C7808: variable 'v8' is possibly undefined
// 51B3D0: using guessed type int dword_51B3D0;
// 54E680: using guessed type int dword_54E680;
// 54E698: using guessed type int dword_54E698;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7860) --------------------------------------------------------
int __fastcall Deffacts_BloadStorage(int a1)
{
  int result; // eax
  _DWORD space[3]; // [esp+0h] [ebp-Ch] BYREF

  space[2] = a1;
  Rules_BloadReadBlock((uintptr_t)space, 4u);
  Rules_BloadReadBlock((uintptr_t)&g_DeffactsBsaveCount, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_DeffactsModuleItemCount, 4u);
  if ( g_DeffactsModuleItemCount )
  {
    space[0] = 12 * g_DeffactsModuleItemCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(12 * g_DeffactsModuleItemCount));
    g_Deffacts_BloadModuleArray = result;
    if ( g_DeffactsBsaveCount )
    {
      space[0] = 24 * g_DeffactsBsaveCount;
      result = Mem_HeapAllocWithRetry((_DWORD *)(24 * g_DeffactsBsaveCount));
      g_ClipsDeffactsBloadArray = result;
    }
    else
    {
      g_ClipsDeffactsBloadArray = 0;
    }
  }
  else
  {
    g_ClipsDeffactsBloadArray = 0;
    g_Deffacts_BloadModuleArray = 0;
  }
  return result;
}
// 51B3CC: using guessed type int dword_51B3CC;
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7910) --------------------------------------------------------
signed int Deffacts_BloadBinaryItem()
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  Rules_BloadAndRefresh(g_DeffactsModuleItemCount, 12, (void (__fastcall *)(signed int, signed int))Deffacts_UpdateDeffactsModule);
  return Rules_BloadAndRefresh(g_DeffactsBsaveCount, 16, (void (__fastcall *)(signed int, signed int))Deffacts_UpdateDeffacts);
}
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;

//----- (004C7950) --------------------------------------------------------
_DWORD * Deffacts_UpdateDeffactsModule(_DWORD *buf, int obji)
{
  return Module_UpdateItemHeader(buf, (_DWORD *)(12 * obji + g_Deffacts_BloadModuleArray), g_ClipsDeffactsBloadArray, 24);
}
// 51B3CC: using guessed type int dword_51B3CC;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7990) --------------------------------------------------------
int  Deffacts_UpdateDeffacts(int buf, int obji)
{
  int assertList; // esi
  int result; // eax

  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(24 * obji + g_ClipsDeffactsBloadArray), g_Deffacts_BloadModuleArray, 12, 24, g_ClipsDeffactsBloadArray);
  if ( *(_DWORD *)(buf + 12) == -1 )
    assertList = 0;
  else
    assertList = 14 * *(_DWORD *)(buf + 12) + g_ClipsPackedExpressionArray;
  result = 3 * obji;
  *(_DWORD *)(g_ClipsDeffactsBloadArray + 24 * obji + 20) = assertList;
  return result;
}
// 51B3CC: using guessed type int dword_51B3CC;
// 54E688: using guessed type int dword_54E688;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7A10) --------------------------------------------------------
signed int Deffacts_ClearBload()
{
  int recordOffset; // ecx
  int v1; // ecx
  int v2; // edx
  signed int result; // eax

  if ( g_DeffactsBsaveCount > 0 )
  {
    recordOffset = 0;
    do
    {
      Rules_ReleaseSymbolReference((int *)(recordOffset + g_ClipsDeffactsBloadArray), recordOffset);
      recordOffset = v1 + 24;
    }
    while ( v2 < g_DeffactsBsaveCount );
  }
  if ( 24 * g_DeffactsBsaveCount )
    Mem_ReleasePoolBlock(g_ClipsDeffactsBloadArray, 24 * g_DeffactsBsaveCount);
  result = 12 * g_DeffactsModuleItemCount;
  if ( 12 * g_DeffactsModuleItemCount )
    return Mem_ReleasePoolBlock(g_Deffacts_BloadModuleArray, 12 * g_DeffactsModuleItemCount);
  return result;
}
// 4C7A34: variable 'v1' is possibly undefined
// 4C7A39: variable 'v2' is possibly undefined
// 51B3CC: using guessed type int dword_51B3CC;
// 51B3D0: using guessed type int dword_51B3D0;
// 54E8BC: using guessed type int dword_54E8BC;
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7AA0) --------------------------------------------------------
int  Deffacts_GetModuleItem(int theIndex)
{
  return 12 * theIndex + g_Deffacts_BloadModuleArray;
}
// 54E8C0: using guessed type int dword_54E8C0;

//----- (004C7AC0) --------------------------------------------------------
int Deffacts_CompilerSetup()
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)aDeffacts_2, 0, 0, (int)Deffacts_BeforeCode, (int)Deffacts_ToCode, 2);
  g_Clips_DeffactsCodeGeneratorItem = result;
  return result;
}
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7AF0) --------------------------------------------------------
signed int Deffacts_BeforeCode()
{
  return Rules_RegisterModuleItemIdAssigner();
}
// 54E698: using guessed type int dword_54E698;

//----- (004C7B00) --------------------------------------------------------
int  Deffacts_ToCode(const char *fileName, const char *a2, int imageID, int headerFP, int maxIndices)
{
  int deffactsFile; // esi
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  int theDeffacts; // edi
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int fileCount; // [esp+0h] [ebp-3Ch] BYREF
  int moduleArrayCount; // [esp+4h] [ebp-38h] BYREF
  int moduleArrayVersion; // [esp+8h] [ebp-34h] BYREF
  int deffactsArrayCount; // [esp+Ch] [ebp-30h] BYREF
  int deffactsArrayVersion; // [esp+10h] [ebp-2Ch] BYREF
  int moduleFile; // [esp+14h] [ebp-28h]
  int Enum; // [esp+18h] [ebp-24h]
  const char *v22; // [esp+1Ch] [ebp-20h]
  const char *v23; // [esp+20h] [ebp-1Ch]
  int v24; // [esp+24h] [ebp-18h]
  int moduleCount; // [esp+28h] [ebp-14h]
  int v26; // [esp+2Ch] [ebp-10h]

  v22 = fileName;
  v23 = a2;
  v24 = headerFP;
  v26 = imageID;
  moduleCount = 0;
  moduleArrayCount = 0;
  moduleArrayVersion = 1;
  deffactsArrayCount = 0;
  deffactsArrayVersion = 1;
  moduleFile = 0;
  Output_WriteFormatted(0, 1, headerFP, (int)aIncludeDffctde, 1);
  deffactsFile = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      v7 = Rules_ConstructCodeFileOpen(
             moduleFile,
             v22,
             v26,
             v23,
             &fileCount,
             moduleArrayVersion,
             v24,
             (char)aStructDeffacts,
             **(const char ***)(g_Clips_DeffactsCodeGeneratorItem + 20),
             0,
             0);
      v9 = v7;
      if ( !v7 )
      {
        Deffacts_CloseCodeFiles(0, deffactsFile, v8, maxIndices);
        return 0;
      }
      Deffacts_ModuleToCode(v7, Enum, maxIndices, moduleCount);
      moduleFile = Rules_ConstructCodeFileClose(v9, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
      theDeffacts = Rules_DeffactsGetNextItem(0);
      if ( theDeffacts )
        break;
LABEL_6:
      ++moduleCount;
      ++moduleArrayCount;
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v11 = Rules_ConstructCodeFileOpen(
              deffactsFile,
              v22,
              v26,
              v23,
              &fileCount,
              deffactsArrayVersion,
              v24,
              (char)aStructDeffac_0,
              *(const char **)(*(_DWORD *)(g_Clips_DeffactsCodeGeneratorItem + 20) + 4),
              0,
              0);
      v13 = v11;
      if ( !v11 )
        break;
      Deffacts_SingleToCode(v11, theDeffacts, maxIndices, moduleCount);
      ++deffactsArrayCount;
      deffactsFile = Rules_ConstructCodeFileClose(v13, &deffactsArrayCount, maxIndices, &deffactsArrayVersion, 0, 0);
      theDeffacts = Rules_DeffactsGetNextItem(theDeffacts);
      if ( !theDeffacts )
        goto LABEL_6;
    }
    Deffacts_CloseCodeFiles(moduleFile, 0, v12, maxIndices);
    return 0;
  }
  else
  {
LABEL_7:
    Deffacts_CloseCodeFiles(moduleFile, deffactsFile, v6, maxIndices);
    return 1;
  }
}
// 4C7CA0: variable 'v6' is possibly undefined
// 4C7CB7: variable 'v8' is possibly undefined
// 4C7CCF: variable 'v12' is possibly undefined
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7CE0) --------------------------------------------------------
int  Deffacts_CloseCodeFiles(int moduleFile, int deffactsFile, int a3, int maxIndices)
{
  int result; // eax
  int count; // [esp+0h] [ebp-14h] BYREF
  _DWORD arrayVersion[4]; // [esp+4h] [ebp-10h] BYREF

  arrayVersion[3] = a3;
  result = deffactsFile;
  count = maxIndices;
  arrayVersion[0] = 0;
  if ( deffactsFile )
  {
    result = Rules_ConstructCodeFileClose(deffactsFile, &count, maxIndices, arrayVersion, 0, 0);
    if ( !moduleFile )
      return result;
    goto LABEL_5;
  }
  if ( moduleFile )
  {
LABEL_5:
    count = maxIndices;
    return Rules_ConstructCodeFileClose(moduleFile, &count, maxIndices, arrayVersion, 0, 0);
  }
  return result;
}

//----- (004C7D40) --------------------------------------------------------
int  Deffacts_ModuleToCode(int theFile, int theModule, int maxIndices, int moduleCount)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, theFile, (int)asc_50B024, v10);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v5, v6, g_ClipsDeffactsModuleItemId, *(_DWORD *)(*(_DWORD *)(g_Clips_DeffactsCodeGeneratorItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, theFile, (int)asc_50B028, v11);
}
// 4C7D4B: variable 'v10' is possibly undefined
// 4C7D68: variable 'v5' is possibly undefined
// 4C7D68: variable 'v6' is possibly undefined
// 4C7D73: variable 'v8' is possibly undefined
// 4C7D73: variable 'v7' is possibly undefined
// 4C7D73: variable 'v11' is possibly undefined
// 54E698: using guessed type int dword_54E698;
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7D90) --------------------------------------------------------
int  Deffacts_SingleToCode(int theFile, int theDeffacts, int maxIndices, int moduleCount)
{
  int *prefixArray; // eax
  DWORD modulePrefix; // ebp
  signed int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char v15; // [esp+0h] [ebp-Ch]
  char v16; // [esp+0h] [ebp-Ch]
  char v17; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theDeffacts, theFile, (int)asc_50B024, v15);
  prefixArray = *(int **)(g_Clips_DeffactsCodeGeneratorItem + 20);
  modulePrefix = *prefixArray;
  Rules_WriteConstructHeaderToCode(theFile, theDeffacts, v8, moduleCount, *prefixArray, prefixArray[1]);
  Output_WriteFormatted(v10, v9, theFile, (int)asc_50B02C, v16);
  Rules_ExpressionToCode(theFile, *(__int16 **)(theDeffacts + 20), v11, modulePrefix);
  return Output_WriteFormatted(v13, v12, theFile, (int)asc_50B028, v17);
}
// 4C7D9D: variable 'v15' is possibly undefined
// 4C7DBD: variable 'v8' is possibly undefined
// 4C7DC8: variable 'v10' is possibly undefined
// 4C7DC8: variable 'v9' is possibly undefined
// 4C7DC8: variable 'v16' is possibly undefined
// 4C7DD5: variable 'v11' is possibly undefined
// 4C7DE0: variable 'v13' is possibly undefined
// 4C7DE0: variable 'v12' is possibly undefined
// 4C7DE0: variable 'v17' is possibly undefined
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7DF0) --------------------------------------------------------
int  Deffacts_PrintModuleReference(int theFile, int count)
{
  return Output_WriteFormatted(count, **(_DWORD **)(g_Clips_DeffactsCodeGeneratorItem + 20), theFile, (int)aMihsSD_DD_5, **(_DWORD **)(g_Clips_DeffactsCodeGeneratorItem + 20));
}
// 54E8C4: using guessed type int dword_54E8C4;

//----- (004C7E30) --------------------------------------------------------
BOOL Defgeneric_NoActiveCall()
{
  return g_ClipsCurrentGeneric == 0;
}
// 51B3D4: using guessed type int dword_51B3D4;

//----- (004C7E40) --------------------------------------------------------
signed int Defgeneric_AllocateModule()
{
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *v0;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C7E70) --------------------------------------------------------
int  Defgeneric_FreeModule(int theItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theItem, g_Clips_DefgenericConstructType, theItem);
  freed_node = (_DWORD *)theItem;
  g_ClipsMemFreeListTemp = theItem;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6A0: using guessed type int dword_54E6A0;

//----- (004C7EB0) --------------------------------------------------------
int Defgeneric_ClearDefgenericsReady()
{
  int v0; // eax
  int v1; // ecx
  int i; // edx
  int v4; // ecx
  int v5; // edx

  v0 = Rules_IsBloaded();
  if ( v0 == v1 )
    return v1 ^ v0;
  for ( i = Defgeneric_GetNextInModule(0); i; i = Defgeneric_GetNextInModule(v5) )
    Defgeneric_RemoveAllExplicitMethods(i);
  return v4;
}
// 4C7EBD: variable 'v1' is possibly undefined
// 4C7EE0: variable 'v5' is possibly undefined
// 4C7EEB: variable 'v4' is possibly undefined

//----- (004C7EF0) --------------------------------------------------------
signed int  Defgeneric_RemoveAllExplicitMethods(int theDefgeneric)
{
  signed int v2; // eax
  int v3; // edx
  unsigned int methodIndex; // ebp
  int methodOffset; // esi
  int theMethod; // edx
  _DWORD *newMethods; // eax
  int destOffset; // edx
  int copyOffset; // ebp
  _BYTE *oldMethod; // esi
  _DWORD *destMethod; // edi
  int oldMethodCount; // eax
  _DWORD *narr; // [esp+0h] [ebp-18h]
  int systemMethodCount; // [esp+4h] [ebp-14h]
  unsigned int copyIndex; // [esp+8h] [ebp-10h]

  v2 = Defgeneric_MethodsExecuting(theDefgeneric);
  systemMethodCount = v3;
  if ( v2 )
    return v3;
  methodIndex = 0;
  if ( *(_DWORD *)(theDefgeneric + 32) )
  {
    methodOffset = 0;
    do
    {
      theMethod = methodOffset + *(_DWORD *)(theDefgeneric + 28);
      if ( (*(_BYTE *)(theMethod + 24) & 1) != 0 )
        ++systemMethodCount;
      else
        Defgeneric_DeleteMethodInfo(theDefgeneric, theMethod);
      ++methodIndex;
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(theDefgeneric + 32) );
  }
  if ( systemMethodCount )
  {
    newMethods = Mem_SmallBlockAlloc(40 * systemMethodCount);
    destOffset = 0;
    narr = newMethods;
    copyIndex = 0;
    if ( *(_DWORD *)(theDefgeneric + 32) )
    {
      copyOffset = 0;
      do
      {
        oldMethod = (_BYTE *)(copyOffset + *(_DWORD *)(theDefgeneric + 28));
        if ( (oldMethod[24] & 1) != 0 )
        {
          destMethod = &newMethods[destOffset];
          destOffset += 10;
          qmemcpy(destMethod, oldMethod, 0x28u);
        }
        copyOffset += 40;
        ++copyIndex;
      }
      while ( copyIndex < *(_DWORD *)(theDefgeneric + 32) );
    }
    Mem_SmallBlockFree(*(_DWORD **)(theDefgeneric + 28), 40 * *(_DWORD *)(theDefgeneric + 32));
    *(_DWORD *)(theDefgeneric + 32) = systemMethodCount;
    *(_DWORD *)(theDefgeneric + 28) = narr;
    return 1;
  }
  oldMethodCount = *(_DWORD *)(theDefgeneric + 32);
  if ( oldMethodCount )
    Mem_SmallBlockFree(*(_DWORD **)(theDefgeneric + 28), 40 * oldMethodCount);
  *(_DWORD *)(theDefgeneric + 32) = 0;
  *(_DWORD *)(theDefgeneric + 28) = 0;
  return 1;
}
// 4C7EFF: variable 'v3' is possibly undefined

//----- (004C8030) --------------------------------------------------------
int  Defgeneric_RemoveDefgeneric(int theDefgeneric)
{
  int v1; // ecx
  unsigned int methodIndex; // ebx
  int methodOffset; // esi
  int methodCount; // ebp
  int nameSymbol; // eax
  int v6; // ecx
  signed int v7; // ecx
  _DWORD *v8; // ecx
  int result; // eax

  v1 = theDefgeneric;
  methodIndex = 0;
  if ( *(_DWORD *)(theDefgeneric + 32) )
  {
    methodOffset = 0;
    do
    {
      ++methodIndex;
      Defgeneric_DeleteMethodInfo(v1, methodOffset + *(_DWORD *)(v1 + 28));
      methodOffset += 40;
    }
    while ( methodIndex < *(_DWORD *)(v1 + 32) );
  }
  methodCount = *(_DWORD *)(v1 + 32);
  if ( methodCount )
    Mem_SmallBlockFree(*(_DWORD **)(v1 + 28), 40 * methodCount);
  nameSymbol = Rules_GetConstructNameSymbol(v1);
  Rules_DecrementSymbolCount(nameSymbol, v6);
  Rules_ReplaceConstructPPForm(v7, 0);
  g_ClipsMemFreeListTemp = (int)v8;
  *v8 = *(_DWORD *)(g_ClipsMemoryTable + 160);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
  return result;
}
// 4C804B: variable 'v1' is possibly undefined
// 4C806E: variable 'v6' is possibly undefined
// 4C8077: variable 'v7' is possibly undefined
// 4C8081: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C80D0) --------------------------------------------------------
signed int Defgeneric_ClearDefgenerics()
{
  int success; // ebx
  int theDefgeneric; // ecx
  int v3; // edx
  int v4; // edx
  int constructName; // eax
  int v6; // ecx

  success = 1;
  if ( Rules_IsBloaded() == 1 )
    return 0;
  theDefgeneric = Defgeneric_GetNextInModule(0);
  if ( !theDefgeneric )
    return success;
  do
  {
    while ( 1 )
    {
      Defgeneric_GetNextInModule(theDefgeneric);
      if ( Defgeneric_RemoveAllExplicitMethods(v3) )
        break;
      constructName = Rules_GetConstructNameString(v4);
      success = 0;
      Rules_ReportCantDeleteItem(v6, constructName);
      if ( !theDefgeneric )
        return success;
    }
    Rules_UnlinkListNode(v4);
    Defgeneric_RemoveDefgeneric(v4);
  }
  while ( theDefgeneric );
  return success;
}
// 4C80F6: variable 'v2' is possibly undefined
// 4C80FF: variable 'v3' is possibly undefined
// 4C810A: variable 'v4' is possibly undefined
// 4C8118: variable 'v6' is possibly undefined

//----- (004C8140) --------------------------------------------------------
signed int Defgeneric_PrintCannotModifyError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // eax
  int v3; // ecx

  Rules_PrintErrorID((int)aGenrcfun, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefgeneric_0, v0);
  v2 = Rules_GetConstructNameString(v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v2, (int)g_IO_LogicalNameTable_WError[0]);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotBeModifi, v3);
}
// 4C8160: variable 'v0' is possibly undefined
// 4C8167: variable 'v1' is possibly undefined
// 4C8185: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004C8190) --------------------------------------------------------
int  Defgeneric_DeleteMethodInfo(int gfunc, int meth)
{
  int v3; // edx
  int v4; // edx
  int restrictionIndex; // edi
  int restrictionOffset; // esi
  int theRestriction; // ebx
  int typeOffset; // ecx
  int v9; // ecx
  unsigned int typeIndex; // edx
  int result; // eax

  g_Defgeneric_SavedBusyCount = *(_DWORD *)(gfunc + 20);
  AST_DeinstallNodeChain(*(__int16 **)(meth + 32));
  AST_FreePackedNodeChain(*(_DWORD *)(v3 + 32));
  if ( *(_DWORD *)(v4 + 36) )
    Mem_SmallBlockFree(*(_DWORD **)(meth + 36), strlen(*(const char **)(meth + 36)) + 1);
  restrictionIndex = 0;
  if ( *(int *)(meth + 8) > 0 )
  {
    restrictionOffset = 0;
    do
    {
      theRestriction = restrictionOffset + *(_DWORD *)(meth + 28);
      if ( *(_DWORD *)(theRestriction + 8) )
      {
        typeOffset = 0;
        do
        {
          Class_ReleaseBusyReference(*(_DWORD *)(typeOffset + *(_DWORD *)theRestriction));
          typeOffset = v9 + 4;
        }
        while ( typeIndex < *(_DWORD *)(theRestriction + 8) );
      }
      if ( *(_DWORD *)theRestriction )
        Mem_SmallBlockFree(*(_DWORD **)theRestriction, 4 * *(_DWORD *)(theRestriction + 8));
      AST_DeinstallNodeChain(*(__int16 **)(theRestriction + 4));
      ++restrictionIndex;
      AST_FreePackedNodeChain(*(_DWORD *)(theRestriction + 4));
      restrictionOffset += 12;
    }
    while ( restrictionIndex < *(_DWORD *)(meth + 8) );
  }
  if ( *(_DWORD *)(meth + 28) )
    Mem_SmallBlockFree(*(_DWORD **)(meth + 28), 12 * *(_DWORD *)(meth + 8));
  result = g_Defgeneric_SavedBusyCount;
  *(_DWORD *)(gfunc + 20) = g_Defgeneric_SavedBusyCount;
  return result;
}
// 4C81AD: variable 'v3' is possibly undefined
// 4C81B5: variable 'v4' is possibly undefined
// 4C81E8: variable 'v9' is possibly undefined
// 4C81ED: variable 'v10' is possibly undefined
// 54E8C8: using guessed type int dword_54E8C8;

//----- (004C8290) --------------------------------------------------------
signed int  Defgeneric_MethodsExecuting(int gfunc)
{
  int methodIndex; // edx
  int i; // eax

  methodIndex = 0;
  if ( !*(_DWORD *)(gfunc + 32) )
    return 0;
  for ( i = *(_DWORD *)(gfunc + 28); !*(_DWORD *)(i + 4); i += 40 )
  {
    if ( (unsigned int)++methodIndex >= *(_DWORD *)(gfunc + 32) )
      return 0;
  }
  return 1;
}

