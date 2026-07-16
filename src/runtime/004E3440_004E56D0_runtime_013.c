/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004E3440) --------------------------------------------------------
int * Class_ParseSlot(
        char *readSource,
        _DWORD *slotList,
        int multiSlot,
        unsigned __int16 *precedenceList,
        double a5,
        int fieldSlot)
{
  int slot; // esi
  int *result; // eax
  _BYTE *slotFlagsPtr; // ecx
  int insertedList; // ebp
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ebx
  char *v19; // eax
  int parseStatus; // eax
  __int16 *v21; // ecx
  char slotFlagsByte; // cl
  int v23; // ecx
  signed int accessFacet; // eax
  int v25; // ecx
  signed int storageFacet; // eax
  int v27; // ecx
  signed int propagationFacet; // eax
  int v29; // ecx
  signed int sourceFacet; // eax
  int v31; // ecx
  signed int matchFacet; // eax
  int v33; // ecx
  signed int visibilityFacet; // eax
  int v35; // ecx
  signed int createAccessorFacet; // eax
  signed int overrideFacet; // eax
  int v38; // ecx
  int overrideMsgSymNode; // eax
  __int16 parsedConstraint; // [esp+0h] [ebp-1Ch] BYREF
  int overrideMessageSymbol; // [esp+4h] [ebp-18h] BYREF
  unsigned __int16 *savedPrecList; // [esp+8h] [ebp-14h]
  char specbits[16]; // [esp+Ch] [ebp-10h] BYREF

  savedPrecList = precedenceList;
  IO_OutWriteToken(asc_50E844);
  specbits[1] = 0;
  specbits[0] = 0;
  Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
  if ( g_ParserCurrentTokenType != 2 || g_ClipsParserTokenValue == g_Symbol_IsA || g_ClipsParserTokenValue == g_Clips_NameSymbol )
  {
    Class_DeleteSlotList((int)slotList);
    Parser_ReportSyntaxError();
    return 0;
  }
  slot = Class_NewSlot((_DWORD *)g_ClipsParserTokenValue);
  result = Class_InsertSlot(slotList, slot);
  insertedList = (int)result;
  if ( !result )
    return result;
  if ( multiSlot )
    *slotFlagsPtr |= 2u;
  if ( fieldSlot )
    specbits[0] |= 2u;
  Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
  Rules_IncrementIndentDepth(3);
  Rules_ResetConstraintParsedFlags(&parsedConstraint);
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      IO_OutNewline();
      AST_Append(v14, v13);
      IO_OutWriteToken(asc_50E858);
      Parser_NextToken((int)readSource, v15);
      if ( g_ParserCurrentTokenType != 2 )
        goto LABEL_11;
      if ( !strcmp_(v16, aDefault_2) )
        break;
      if ( !strcmp_(v17, aDefaultDynam_1) )
      {
        v18 = slot;
        BYTE1(v17) = specbits[0] | 0x80;
        v19 = readSource;
        specbits[0] |= 0x80u;
        goto LABEL_18;
      }
      if ( !strcmp_(v17, aAccess) )
      {
        accessFacet = Class_ParseSimpleFacet(
                (int)readSource,
                (int)specbits,
                2,
                (int)aAccess,
                (int)aReadWrite,
                (int)aReadOnly,
                (int)aInitializeOnly,
                0,
                0);
        switch ( accessFacet )
        {
          case -1:
            goto LABEL_12;
          case 1:
            *(_BYTE *)slot |= 0x10u;
            break;
          case 2:
            *(_BYTE *)slot |= 0x20u;
            break;
        }
      }
      else if ( !strcmp_(v23, aStorage) )
      {
        storageFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 0, (int)aStorage, (int)aLocal_0, (int)aShared, 0, 0, 0);
        if ( storageFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)slot &= ~1u;
        *(_DWORD *)slot |= storageFacet & 1;
      }
      else if ( !strcmp_(v25, aPropagation) )
      {
        propagationFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 3, (int)aPropagation, (int)aInherit_2, (int)aNoInherit, 0, 0, 0);
        if ( propagationFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)slot &= ~8u;
        *(_DWORD *)slot |= 8 * (propagationFacet & 1);
      }
      else if ( !strcmp_(v27, aSource) )
      {
        sourceFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 4, (int)aSource, (int)aExclusive, (int)aComposite, 0, 0, 0);
        if ( sourceFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)slot &= ~4u;
        *(_DWORD *)slot |= 4 * (sourceFacet & 1);
      }
      else if ( !strcmp_(v29, aPatternMatch_1) )
      {
        matchFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 5, (int)aPatternMatch_1, (int)aNonReactive_0, (int)aReactive_0, 0, 0, 0);
        if ( matchFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)(slot + 1) &= ~2u;
        *(_DWORD *)slot |= (matchFacet & 1) << 9;
      }
      else if ( !strcmp_(v31, aVisibility) )
      {
        visibilityFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 8, (int)aVisibility, (int)aPrivate, (int)aPublic, 0, 0, 0);
        if ( visibilityFacet == -1 )
          goto LABEL_12;
        *(_BYTE *)(slot + 1) &= ~4u;
        *(_DWORD *)slot |= (visibilityFacet & 1) << 10;
      }
      else if ( !strcmp_(v33, aCreateAccessor) )
      {
        createAccessorFacet = Class_ParseSimpleFacet(
                (int)readSource,
                (int)specbits,
                9,
                (int)aCreateAccessor,
                (int)aRead_0,
                (int)aWrite,
                (int)aReadWrite,
                (int)aNone_2,
                0);
        if ( createAccessorFacet == -1 )
          goto LABEL_12;
        if ( !createAccessorFacet || createAccessorFacet == 2 )
          *(_BYTE *)(slot + 1) |= 8u;
        if ( createAccessorFacet == 1 || createAccessorFacet == 2 )
          *(_BYTE *)(slot + 1) |= 0x10u;
      }
      else
      {
        if ( strcmp_(v35, aOverrideMessag) )
        {
          if ( !Rules_IsConstraintAttributeKeyword(*(_DWORD *)(g_ClipsParserTokenValue + 16)) )
            goto LABEL_11;
          parseStatus = Rules_ParseStandardConstraintAttribute(readSource, *(const char **)(g_ClipsParserTokenValue + 16), &parsedConstraint, *(_DWORD *)(slot + 20), 1);
          goto LABEL_19;
        }
        overrideFacet = Class_ParseSimpleFacet((int)readSource, (int)specbits, 10, (int)aOverrideMessag, 0, 0, 0, (int)aDefault_3, &overrideMessageSymbol);
        if ( overrideFacet == -1 )
          goto LABEL_12;
        if ( overrideFacet == 4 )
        {
          Rules_DecrementSymbolCount(*(_DWORD *)(slot + 12), v38);
          overrideMsgSymNode = overrideMessageSymbol;
          *(_DWORD *)(slot + 12) = overrideMessageSymbol;
          ++*(_DWORD *)(overrideMsgSymNode + 4);
        }
        *(_BYTE *)(slot + 1) |= 0x20u;
      }
LABEL_20:
      Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_21;
    }
    v18 = slot;
    v19 = readSource;
LABEL_18:
    parseStatus = Class_ParseDefaultFacet((int)v19, specbits, v17, v18, a5);
LABEL_19:
    if ( !parseStatus )
      goto LABEL_12;
    goto LABEL_20;
  }
LABEL_21:
  if ( g_ParserCurrentTokenType != 101 )
  {
LABEL_11:
    Parser_ReportSyntaxError();
LABEL_12:
    Rules_DecrementIndentDepth(3);
    Class_DeleteSlotList(insertedList);
    return 0;
  }
  if ( (*(_BYTE *)slot & 4) != 0 )
    Class_BuildCompositeFacets(slot, savedPrecList, (int)&parsedConstraint, specbits);
  if ( !Class_CheckForFacetConflicts(slot, (int)&parsedConstraint) || !Rules_CheckConstraintParseConflicts(*(_DWORD *)(slot + 20), v21) || !Class_EvaluateSlotDefaultValue((int *)slot, specbits, a5) )
    goto LABEL_12;
  slotFlagsByte = *(_BYTE *)slot;
  if ( (*(_BYTE *)slot & 0x40) == 0 && (slotFlagsByte & 0x10) != 0 && (slotFlagsByte & 0x20) == 0 )
    *(_BYTE *)slot = slotFlagsByte | 1;
  *(_DWORD *)(slot + 20) = AST_InternNode(*(_DWORD **)(slot + 20));
  Rules_DecrementIndentDepth(3);
  return (int *)insertedList;
}
// 4E34BA: variable 'v11' is possibly undefined
// 4E34F8: variable 'v14' is possibly undefined
// 4E34F8: variable 'v13' is possibly undefined
// 4E350E: variable 'v15' is possibly undefined
// 4E3562: variable 'v16' is possibly undefined
// 4E3577: variable 'v17' is possibly undefined
// 4E35D0: variable 'v21' is possibly undefined
// 4E36C8: variable 'v23' is possibly undefined
// 4E3713: variable 'v25' is possibly undefined
// 4E376C: variable 'v27' is possibly undefined
// 4E37C5: variable 'v29' is possibly undefined
// 4E381C: variable 'v31' is possibly undefined
// 4E3873: variable 'v33' is possibly undefined
// 4E38E5: variable 'v35' is possibly undefined
// 4E3924: variable 'v38' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004E3970) --------------------------------------------------------
int  Class_DeleteSlotList(int result)
{
  int i; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // edx
  int theSlot; // eax
  int v7; // edx

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp )
  {
    Class_ReleaseSlotName(*(_DWORD **)(*(_DWORD *)i + 8));
    Rules_DecrementSymbolCount(*(_DWORD *)(*(_DWORD *)v2 + 12), v3);
    AST_DecrementNodeRefCount(*(_DWORD **)(*(_DWORD *)v4 + 20));
    theSlot = *(_DWORD *)v5;
    if ( (**(_BYTE **)v5 & 0x40) != 0 )
    {
      AST_DeinstallNodeChain(*(__int16 **)(theSlot + 16));
      AST_FreePackedNodeChain(*(_DWORD *)(*(_DWORD *)v7 + 16));
    }
    else if ( *(_DWORD *)(theSlot + 16) )
    {
      Rules_ValueDeinstall(*(_DWORD *)(theSlot + 16), i);
      g_ClipsMemFreeListTemp = *(_DWORD *)(*(_DWORD *)v5 + 16);
      *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    }
    g_ClipsMemFreeListTemp = *(_DWORD *)v5;
    *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
    g_ClipsMemFreeListTemp = v5;
    *(_DWORD *)v5 = *(_DWORD *)(g_ClipsMemoryTable + 32);
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 4E397F: variable 'i' is possibly undefined
// 4E398C: variable 'v2' is possibly undefined
// 4E3991: variable 'v3' is possibly undefined
// 4E3996: variable 'v4' is possibly undefined
// 4E39A0: variable 'v5' is possibly undefined
// 4E3A3E: variable 'v7' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3A50) --------------------------------------------------------
int  Class_NewSlot(_DWORD *slotNameSymbol)
{
  _DWORD *freeListEntry; // edx
  signed int slot; // ecx
  __int16 v4; // dx
  int parseNode; // eax
  int v6; // ecx
  int v7; // edx
  unsigned int *slotNameRecord; // eax
  int v9; // ecx
  unsigned int overrideMessage; // eax

  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 176);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
    *(_DWORD *)(g_ClipsMemoryTable + 176) = *freeListEntry;
    slot = g_ClipsMemFreeListTemp;
  }
  else
  {
    slot = Mem_HeapAllocWithRetry((_DWORD *)0x2C);
  }
  *(_DWORD *)(slot + 24) = 0;
  v4 = *(_WORD *)slot;
  *(_DWORD *)(slot + 4) = 0;
  *(_DWORD *)(slot + 16) = 0;
  *(_WORD *)slot = v4 | 0x240;
  *(_WORD *)slot = v4 & 0xC000 | 0x240;
  parseNode = Rules_CreateLHSParseNode();
  *(_DWORD *)(v6 + 20) = parseNode;
  slotNameRecord = Class_InternSlotName(slotNameSymbol, v7, 0);
  *(_DWORD *)(v9 + 8) = slotNameRecord;
  overrideMessage = slotNameRecord[4];
  *(_DWORD *)(v9 + 12) = overrideMessage;
  ++*(_DWORD *)(overrideMessage + 4);
  return v9;
}
// 4E3AAF: variable 'v6' is possibly undefined
// 4E3AB4: variable 'v7' is possibly undefined
// 4E3AB9: variable 'v9' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3AE0) --------------------------------------------------------
int * Class_InsertSlot(_DWORD *slotList, int theSlot)
{
  int v3; // ecx
  _DWORD *freeListEntry; // edx
  int *result; // eax
  int newLink; // esi
  _DWORD *scanLink; // eax
  _DWORD *prevLink; // edx
  int v9; // edx
  int v10; // ecx

  v3 = theSlot;
  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *freeListEntry;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  result[1] = 0;
  newLink = (int)result;
  *result = v3;
  if ( slotList )
  {
    scanLink = slotList;
    while ( *(_DWORD *)(v3 + 8) != *(_DWORD *)(*scanLink + 8) )
    {
      prevLink = scanLink;
      scanLink = (_DWORD *)scanLink[1];
      if ( !scanLink )
      {
        prevLink[1] = newLink;
        return slotList;
      }
    }
    *(_DWORD *)(newLink + 4) = slotList;
    Class_DeleteSlotList(newLink);
    Rules_PrintErrorID((int)aClsltpsr, v9, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicateSlots, v10);
    return 0;
  }
  return result;
}
// 4E3B0D: variable 'v3' is possibly undefined
// 4E3B63: variable 'v9' is possibly undefined
// 4E3B72: variable 'v10' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3B80) --------------------------------------------------------
signed int  Class_ParseSimpleFacet(
        int readSource,
        int specbits,
        signed int facetBit,
        int facetName,
        int value1,
        int value2,
        int value3,
        int varName,
        _DWORD *facetSymbolicValue)
{
  _BYTE *specbitBytePtr; // ebx
  int bitMask; // eax
  int v13; // edx
  int v14; // ecx
  int rtnCode; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx

  specbitBytePtr = (_BYTE *)(((facetBit - (__CFSHL__(facetBit >> 31, 3) + 8 * (facetBit >> 31))) >> 3) + specbits);
  bitMask = 1 << (facetBit % 8);
  if ( (*specbitBytePtr & (unsigned __int8)bitMask) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], facetName, v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFacetAlreadySp, v18);
    return -1;
  }
  *specbitBytePtr |= bitMask;
  IO_OutWriteToken(asc_50E844);
  Parser_NextToken(readSource, v13);
  if ( g_ParserCurrentTokenType == 15 )
  {
    if ( varName && !strcmp_(v14, varName) )
      goto LABEL_5;
  }
  else if ( g_ParserCurrentTokenType == 2 )
  {
    if ( facetSymbolicValue )
    {
      *facetSymbolicValue = g_ClipsParserTokenValue;
      goto LABEL_5;
    }
    if ( !strcmp_(v14, value1) || !strcmp_(v19, value2) || value3 && !strcmp_(v20, value3) )
    {
LABEL_5:
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType == 101 )
        return rtnCode;
    }
  }
  Parser_ReportSyntaxError();
  return -1;
}
// 4E3BDA: variable 'v13' is possibly undefined
// 4E3C02: variable 'v14' is possibly undefined
// 4E3C35: variable 'v15' is possibly undefined
// 4E3C58: variable 'v17' is possibly undefined
// 4E3C67: variable 'v18' is possibly undefined
// 4E3CC2: variable 'v19' is possibly undefined
// 4E3CE8: variable 'v20' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004E3D20) --------------------------------------------------------
signed int  Class_ParseDefaultFacet(int readSource, _BYTE *specbits, int a3, int theSlot, double a5)
{
  _DWORD *defaultList; // eax
  int v8; // ecx
  int v9; // edx
  int parseError; // [esp+0h] [ebp-18h] BYREF
  int noneExists; // [esp+4h] [ebp-14h] BYREF
  _DWORD deriveExists[4]; // [esp+8h] [ebp-10h] BYREF

  deriveExists[3] = a3;
  if ( (*specbits & 0x40) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDefaultFacetAl, v8);
    return 0;
  }
  *specbits |= 0x40u;
  parseError = 0;
  defaultList = (_DWORD *)Rules_ParseDefaultAttribute(readSource, 1, 0, *specbits & 0x80, a5, &noneExists, deriveExists, &parseError);
  if ( parseError == 1 )
    return 0;
  if ( noneExists || deriveExists[0] )
  {
    if ( !noneExists )
    {
      *specbits &= ~0x40u;
      return 1;
    }
    *(_WORD *)theSlot |= 0x180u;
  }
  else
  {
    *(_DWORD *)(theSlot + 16) = AST_PackNodeChain(defaultList);
    AST_Free(v9);
    AST_InstallNodeChain(*(__int16 **)(theSlot + 16));
    *(_BYTE *)theSlot |= 0x80u;
  }
  return 1;
}
// 4E3D9D: variable 'v8' is possibly undefined
// 4E3DB7: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E3DE0) --------------------------------------------------------
__int16  Class_BuildCompositeFacets(int slot, unsigned __int16 *precedenceList, int parsedConstraint, _BYTE *specbits)
{
  unsigned int superIndex; // ecx
  int arrayOffset; // ebx
  int result; // eax
  int v9; // eax
  int v10; // eax
  __int16 *packedDefault; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int inheritedSlotValue; // eax
  _BYTE *candidateSlot; // eax
  _DWORD *freeListEntry; // edi
  void *defaultCopy; // eax
  _BYTE *compositeSlot; // [esp+8h] [ebp-Ch]

  superIndex = 1;
  arrayOffset = 4;
  while ( 1 )
  {
    LOWORD(result) = *precedenceList;
    if ( superIndex >= *precedenceList )
      break;
    candidateSlot = (_BYTE *)Class_FindSlotBySymbol(*(_DWORD *)(arrayOffset + *(_DWORD *)(precedenceList + 1)), *(_DWORD *)(*(_DWORD *)(slot + 8) + 12));
    compositeSlot = candidateSlot;
    if ( candidateSlot )
    {
      result = (*candidateSlot & 8) == 0;
      if ( result )
        break;
      arrayOffset += 4;
      ++superIndex;
    }
    else
    {
      arrayOffset += 4;
      ++superIndex;
    }
  }
  if ( compositeSlot )
  {
    if ( *(char *)slot >= 0 && (char)*compositeSlot < 0 )
    {
      v9 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~0x40u;
      *(_DWORD *)slot |= v9 & 0x40;
      LOBYTE(superIndex) = *(_BYTE *)(slot + 1) & 0xFE;
      v10 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) = superIndex;
      *(_DWORD *)slot |= v10 & 0x100;
      BYTE1(superIndex) = *(_BYTE *)slot | 0x80;
      *(_BYTE *)slot = BYTE1(superIndex);
      if ( *((_DWORD *)compositeSlot + 4) )
      {
        if ( (superIndex & 0x4000) != 0 )
        {
          packedDefault = (__int16 *)AST_PackNodeChain(*((_DWORD **)compositeSlot + 4));
          *(_DWORD *)(slot + 16) = packedDefault;
          AST_InstallNodeChain(packedDefault);
        }
        else
        {
          freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 96);
          if ( freeListEntry )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
            *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListEntry;
            defaultCopy = (void *)g_ClipsMemFreeListTemp;
          }
          else
          {
            defaultCopy = (void *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
          }
          *(_DWORD *)(slot + 16) = defaultCopy;
          qmemcpy(defaultCopy, *((const void **)compositeSlot + 4), 0x18u);
          Rules_ValueInstall(*(_DWORD *)(slot + 16), 0);
        }
      }
    }
    if ( (*specbits & 2) == 0 )
    {
      v12 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~2u;
      *(_DWORD *)slot |= v12 & 2;
    }
    if ( (*specbits & 1) == 0 )
    {
      v13 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~1u;
      *(_DWORD *)slot |= v13 & 1;
    }
    if ( (*specbits & 4) == 0 )
    {
      BYTE1(superIndex) = *(_BYTE *)slot & 0xEF;
      v14 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot = BYTE1(superIndex);
      *(_DWORD *)slot |= v14 & 0x10;
      v15 = *(_DWORD *)compositeSlot;
      *(_BYTE *)slot &= ~0x20u;
      *(_DWORD *)slot |= v15 & 0x20;
    }
    if ( (*specbits & 0x20) == 0 )
    {
      v16 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) &= ~2u;
      *(_DWORD *)slot |= v16 & 0x200;
    }
    if ( (specbits[1] & 1) == 0 )
    {
      LOBYTE(superIndex) = *(_BYTE *)(slot + 1) & 0xFB;
      v17 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) = superIndex;
      *(_DWORD *)slot |= v17 & 0x400;
    }
    if ( (specbits[1] & 2) == 0 )
    {
      v18 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) &= ~8u;
      *(_DWORD *)slot |= v18 & 0x800;
      v19 = *(_DWORD *)compositeSlot;
      *(_BYTE *)(slot + 1) &= ~0x10u;
      *(_DWORD *)slot |= v19 & 0x1000;
    }
    if ( (specbits[1] & 4) == 0 && (compositeSlot[1] & 0x20) != 0 )
    {
      Rules_DecrementSymbolCount(*(_DWORD *)(slot + 12), superIndex);
      inheritedSlotValue = *((_DWORD *)compositeSlot + 3);
      *(_DWORD *)(slot + 12) = inheritedSlotValue;
      ++*(_DWORD *)(inheritedSlotValue + 4);
      *(_BYTE *)(slot + 1) |= 0x20u;
    }
    LOWORD(result) = Rules_OverlayConstraint(parsedConstraint, *(_DWORD *)(slot + 20), *((int **)compositeSlot + 5));
  }
  return result;
}
// 4E3E0C: variable 'v27' is possibly undefined
// 4E3F75: variable 'v6' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E4040) --------------------------------------------------------
signed int  Class_CheckForFacetConflicts(int slotDesc, int parsedConstraints)
{
  int v2; // ecx
  int v3; // ecx
  int *minIntValue; // eax
  signed int minExprNode; // eax
  int v6; // ecx
  int *maxIntValue; // eax
  signed int maxExprNode; // eax
  char accessBits; // dl
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx

  v2 = slotDesc;
  if ( (*(_BYTE *)slotDesc & 2) == 0 )
  {
    if ( (*(_BYTE *)(parsedConstraints + 1) & 4) != 0 )
    {
      Rules_PrintErrorID((int)aClsltpsr, 3, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCardinalityFac, v11);
      return 0;
    }
    AST_Free(*(_DWORD *)(*(_DWORD *)(slotDesc + 20) + 18));
    AST_Free(*(_DWORD *)(*(_DWORD *)(v3 + 20) + 22));
    minIntValue = Rules_AddIntegerValue(1);
    minExprNode = AST_NewNode(1, (int)minIntValue);
    *(_DWORD *)(*(_DWORD *)(v6 + 20) + 18) = minExprNode;
    maxIntValue = Rules_AddIntegerValue(1);
    maxExprNode = AST_NewNode(1, (int)maxIntValue);
    *(_DWORD *)(*(_DWORD *)(v2 + 20) + 22) = maxExprNode;
  }
  if ( (*(_BYTE *)(v2 + 1) & 1) != 0 && (*(_BYTE *)v2 & 0x10) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 4, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReadOnlySlotsM, v12);
    return 0;
  }
  else if ( (*(_BYTE *)v2 & 0x10) != 0 && ((accessBits = *(_BYTE *)(v2 + 1), (accessBits & 0x10) != 0) || (accessBits & 0x20) != 0) )
  {
    Rules_PrintErrorID((int)aClsltpsr, 5, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReadOnlySlotsC, v13);
    return 0;
  }
  else if ( (*(_BYTE *)v2 & 8) != 0 && (*(_BYTE *)(v2 + 1) & 4) != 0 )
  {
    Rules_PrintErrorID((int)aClsltpsr, 6, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aNoInheritSlots, v14);
    return 0;
  }
  else
  {
    return 1;
  }
}
// 4E405E: variable 'v3' is possibly undefined
// 4E407F: variable 'v6' is possibly undefined
// 4E409B: variable 'v2' is possibly undefined
// 4E40F3: variable 'v11' is possibly undefined
// 4E411B: variable 'v12' is possibly undefined
// 4E4143: variable 'v13' is possibly undefined
// 4E416B: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004E4180) --------------------------------------------------------
signed int  Class_EvaluateSlotDefaultValue(int *slotDesc, char *specBits, double a3)
{
  _DWORD *freeListNode; // ecx
  _DWORD *defaultBuffer; // eax
  int slotFlags; // ebx
  int v7; // ecx
  int savedGuardFlag; // edi
  int v10; // edx
  int v11; // ecx
  int evalStatus; // edx
  int v13; // ecx
  int v14; // edx
  _DWORD *freeNode; // ebx
  void *valueCopy; // eax
  signed int violationCode; // esi
  int v18; // ecx
  _DWORD defaultValue[11]; // [esp+0h] [ebp-2Ch] BYREF

  if ( *specBits >= 0 )
    *(_BYTE *)slotDesc &= ~0x40u;
  if ( (*((_BYTE *)slotDesc + 1) & 1) != 0 )
    return 1;
  if ( (*(_BYTE *)slotDesc & 0x40) != 0 )
  {
    if ( !Rules_StaticConstraintCheckingEnabled() )
      return 1;
    violationCode = Rules_CheckFieldExprListAgainstConstraint((int *)slotDesc[4], slotDesc[5]);
    if ( !violationCode )
      return 1;
    Rules_PrintErrorID((int)aCstrnchk_3, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpressionFo_0, (int)aDynamicDefault);
    Instance_PrintSlotErrorContext((int)g_IO_LogicalNameTable_WError[0], (int)slotDesc, v18, 0);
    Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, violationCode, slotDesc[5], 0);
    return 0;
  }
  else
  {
    if ( (*specBits & 0x40) == 0 )
    {
      if ( *(char *)slotDesc < 0 )
        return 1;
      freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 96);
      if ( freeListNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeListNode;
        defaultBuffer = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        defaultBuffer = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
      }
      slotFlags = *slotDesc;
      slotDesc[4] = (int)defaultBuffer;
      Rules_DeriveDefaultFromConstraints((char *)slotDesc[5], defaultBuffer, (unsigned int)(slotFlags << 30) >> 31);
LABEL_10:
      Rules_ValueInstall(slotDesc[4], v7);
      return 1;
    }
    savedGuardFlag = Rules_GetReentryGuardFlag();
    Rules_SetReentryGuardFlag(1);
    Rules_StaticConstraintCheckingEnabled();
    Rules_SetDynamicConstraintChecking(v11, v10);
    evalStatus = Parser_ParseSlotDefaultOrRestriction((unsigned int)(*slotDesc << 30) >> 31, slotDesc[4], defaultValue, a3);
    if ( evalStatus )
      evalStatus = Instance_ValidateSlotValueConstraints(defaultValue, (int)slotDesc, 0);
    Rules_SetDynamicConstraintChecking(v13, evalStatus);
    Rules_SetReentryGuardFlag(savedGuardFlag);
    if ( v14 )
    {
      AST_DeinstallNodeChain((__int16 *)slotDesc[4]);
      AST_FreePackedNodeChain(slotDesc[4]);
      freeNode = *(_DWORD **)(g_ClipsMemoryTable + 96);
      if ( freeNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 96);
        *(_DWORD *)(g_ClipsMemoryTable + 96) = *freeNode;
        valueCopy = (void *)g_ClipsMemFreeListTemp;
      }
      else
      {
        valueCopy = (void *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
      }
      slotDesc[4] = (int)valueCopy;
      qmemcpy(valueCopy, defaultValue, 0x18u);
      v7 = 0;
      goto LABEL_10;
    }
    *(_BYTE *)slotDesc |= 0x40u;
    return 0;
  }
}
// 4E41E0: variable 'v7' is possibly undefined
// 4E420F: variable 'v11' is possibly undefined
// 4E420F: variable 'v10' is possibly undefined
// 4E4243: variable 'v13' is possibly undefined
// 4E4251: variable 'v14' is possibly undefined
// 4E4320: variable 'v18' is possibly undefined
// 4971A0: using guessed type int __fastcall unknown_libname_10(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E4C6D) --------------------------------------------------------
_DWORD * CRT_ResizeHeapBlockLocked(_DWORD *heapBlock, unsigned int newSize, unsigned int a3)
{
  unsigned int v6[4]; // [esp-Ch] [ebp-10h] BYREF

  v6[2] = a3;
  g_CRT_StaticLock2AcquireHook();
  if ( CRT_ResizeHeapBlockInPlace(__DS__, heapBlock, v6, newSize, heapBlock) )
  {
    g_CRT_StaticLock2ReleaseHook();
    return 0;
  }
  else
  {
    g_CRT_StaticLock2ReleaseHook();
    return heapBlock;
  }
}
// 485379: using guessed type _DWORD nullsub_8();
// 51A584: using guessed type _DWORD (*off_51A584)();
// 51A58C: using guessed type _DWORD (*off_51A58C)();

//----- (004E4CA7) --------------------------------------------------------
signed int  CRT_ResizeHeapBlockInPlace(
        __int16 dataSegment,
        _DWORD *blockPtr,
        unsigned int *bytesNeededPtr,
        unsigned int requestedSize,
        _DWORD *i)
{
  unsigned int alignedSize; // eax
  unsigned int blockSize; // edx
  unsigned int growAmount; // eax
  unsigned int *j; // ebx
  unsigned int neighborSize; // ebp
  int v11; // ebp
  unsigned int *heapRover; // edx
  unsigned int leftoverSize; // eax
  unsigned int *splitBlock; // ebx
  unsigned int shrinkAmount; // edx
  unsigned int newHeaderSize; // ebx
  unsigned int *blockHeader; // [esp+4h] [ebp-18h]
  unsigned int prevFreeLink; // [esp+8h] [ebp-14h]
  unsigned int nextFreeLink; // [esp+Ch] [ebp-10h]

  alignedSize = requestedSize + 11;
  LOBYTE(alignedSize) = (requestedSize + 11) & 0xF8;
  if ( alignedSize >= requestedSize )
  {
    if ( alignedSize < 0x10 )
      alignedSize = 16;
  }
  else
  {
    alignedSize = -1;
  }
  blockHeader = blockPtr - 1;
  blockSize = *(blockPtr - 1);
  LOBYTE(blockSize) = blockSize & 0xFE;
  if ( alignedSize <= blockSize )
  {
    shrinkAmount = blockSize - alignedSize;
    if ( shrinkAmount >= 0x10 )
    {
      newHeaderSize = alignedSize;
      LOBYTE(newHeaderSize) = alignedSize | 1;
      LOBYTE(shrinkAmount) = shrinkAmount | 1;
      *blockHeader = newHeaderSize;
      *(unsigned int *)((char *)blockHeader + alignedSize) = shrinkAmount;
      if ( __DS__ == dataSegment )
      {
        for ( i = (_DWORD *)g_CRT_HeapSegmentListHead; i[2] && (i > blockPtr || (_DWORD *)((char *)i + *i) <= blockPtr); i = (_DWORD *)i[2] )
          ;
      }
      ++i[6];
      nfree_(blockHeader);
    }
    return 0;
  }
  else
  {
    growAmount = alignedSize - blockSize;
    for ( j = (unsigned int *)((char *)blockHeader + blockSize); ; j = (unsigned int *)((char *)j + neighborSize) )
    {
      *bytesNeededPtr = growAmount;
      neighborSize = *j;
      if ( *j == -1 )
        return 2;
      if ( (neighborSize & 1) != 0 )
        break;
      nextFreeLink = j[2];
      prevFreeLink = j[1];
      if ( __DS__ == dataSegment )
      {
        for ( i = (_DWORD *)g_CRT_HeapSegmentListHead; i[2] && (i > blockPtr || (_DWORD *)((char *)i + *i) <= blockPtr); i = (_DWORD *)i[2] )
          ;
      }
      heapRover = (unsigned int *)i[3];
      if ( j == heapRover )
        i[3] = heapRover[1];
      if ( neighborSize >= *bytesNeededPtr )
      {
        leftoverSize = neighborSize - *bytesNeededPtr;
        if ( leftoverSize >= 0x10 )
        {
          splitBlock = (unsigned int *)((char *)j + *bytesNeededPtr);
          *splitBlock = leftoverSize;
          splitBlock[1] = prevFreeLink;
          splitBlock[2] = nextFreeLink;
          *(_DWORD *)(prevFreeLink + 8) = splitBlock;
          *(_DWORD *)(nextFreeLink + 4) = splitBlock;
          v11 = 0;
          *blockHeader += *bytesNeededPtr;
          g_CRT_HeapCoalesceStateByte = 0;
          return v11;
        }
      }
      *(_DWORD *)(prevFreeLink + 8) = nextFreeLink;
      *(_DWORD *)(nextFreeLink + 4) = prevFreeLink;
      *blockHeader += neighborSize;
      --i[7];
      g_CRT_HeapCoalesceStateByte = 0;
      if ( neighborSize >= *bytesNeededPtr )
        return 0;
      growAmount = *bytesNeededPtr - neighborSize;
    }
    return 1;
  }
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 519F14: using guessed type int dword_519F14;
// 54E511: using guessed type char byte_54E511;

//----- (004E4F71) --------------------------------------------------------
BOOL __cdecl CRT_ThreadStartTrampoline(LPVOID lpThreadParameter)
{
  int v1; // ecx
  int threadDataMgmtDisabled; // edx
  int alignedDataSize; // eax
  void *v4; // esp
  int threadDataBlock; // ecx
  HANDLE ownThreadHandle; // ebx
  int v8; // ecx
  _BYTE sehFrame[8]; // [esp+0h] [ebp-10h] BYREF
  void (*startAddress)(void); // [esp+8h] [ebp-8h]
  HANDLE hObject; // [esp+Ch] [ebp-4h]

  startAddress = *(void (**)(void))lpThreadParameter;
  threadDataMgmtDisabled = g_CrtThreadDataMgmtDisabledFlag;
  hObject = (HANDLE)**((_DWORD **)lpThreadParameter + 4);
  if ( g_CrtThreadDataMgmtDisabledFlag
    || (alignedDataSize = g_CRT_ThreadDataBlockSize + 3,
        LOBYTE(alignedDataSize) = (g_CRT_ThreadDataBlockSize + 3) & 0xFC,
        v4 = alloca(alignedDataSize),
        memset_(sehFrame, 0),
        *(_DWORD *)(threadDataBlock + 240) = g_CRT_ThreadDataBlockSize,
        CRT_CreateAndAttachThreadData(threadDataBlock, threadDataBlock)) )
  {
    ownThreadHandle = hObject;
    *(_DWORD *)(g_CrtThreadDataAccessor(v1, threadDataMgmtDisabled) + 222) = ownThreadHandle;
    SetEvent(*((HANDLE *)lpThreadParameter + 3));
    CRT_InstallUnhandledExceptionFilter((int)sehFrame, v8);
    g_CRT_ThreadStartupHook();
    startAddress();
    endthread_();
  }
  return CloseHandle(hObject);
}
// 4E4FBC: variable 'v5' is possibly undefined
// 4E4FDD: variable 'v1' is possibly undefined
// 4E4FDD: variable 'v2' is possibly undefined
// 4E4FF7: variable 'v8' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 485379: using guessed type _DWORD nullsub_8();
// 4D9788: using guessed type void __noreturn endthread_(void);
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A5A8: using guessed type _DWORD (*off_51A5A8)();
// 51AF00: using guessed type int dword_51AF00;

//----- (004E5018) --------------------------------------------------------
HANDLE  CRT_BeginThread(int startAddress, int stackSize, int argList)
{
  int v3; // ecx
  HANDLE result; // eax
  DWORD CurrentThreadId; // eax
  CHAR eventName[32]; // [esp+0h] [ebp-50h] BYREF
  _DWORD Parameter[3]; // [esp+20h] [ebp-30h] BYREF
  HANDLE hHandle; // [esp+2Ch] [ebp-24h]
  HANDLE *v10; // [esp+30h] [ebp-20h]
  HANDLE Thread; // [esp+34h] [ebp-1Ch] BYREF
  DWORD ThreadId[6]; // [esp+38h] [ebp-18h] BYREF

  v3 = startAddress;
  if ( dwTlsIndex == -1 )
  {
    result = (HANDLE)CRT_AllocateTlsIndex();
    if ( !result )
      return result;
    CRT_InitializeThreadAndFileHandleHooks();
  }
  Parameter[0] = v3;
  Parameter[1] = argList;
  Parameter[2] = GetCurrentThread();
  strcpy(eventName, "__bgnthd");
  CurrentThreadId = GetCurrentThreadId();
  Str_FormatSignedRadixDigits(CurrentThreadId, &eventName[8], 0x10u);
  hHandle = CreateEventA(0, 0, 0, eventName);
  v10 = &Thread;
  Thread = CreateThread(0, (stackSize + 4095) & 0xFFFFF000, (LPTHREAD_START_ROUTINE)CRT_ThreadStartTrampoline, Parameter, 0, ThreadId);
  if ( Thread )
    WaitForSingleObject(hHandle, 0xFFFFFFFF);
  else
    ThreadId[0] = -1;
  CloseHandle(hHandle);
  return Thread;
}
// 4E503F: variable 'v3' is possibly undefined

//----- (004E50F1) --------------------------------------------------------
void __fastcall __noreturn CRT_EndThread(int a1, int a2)
{
  int v2; // edx
  int v3; // ecx

  g_CRT_ThreadEndHook(a2, a1);
  CRT_RemoveUnhandledExceptionFilter(v3, v2);
  if ( !g_CrtThreadDataMgmtDisabledFlag )
    CRT_DetachThreadDataAndMaybeCloseHandle((char *)1);
  ExitThread(0);
}
// 4E50F9: variable 'v3' is possibly undefined
// 4E50F9: variable 'v2' is possibly undefined
// 51A5AC: using guessed type int (__cdecl *off_51A5AC)(_DWORD, _DWORD);

//----- (004E51E0) --------------------------------------------------------
_DWORD * AST_BuildClassHierarchyFieldAccessTest(_DWORD *fieldNode, int patternNode)
{
  int bottomChain; // edi
  _DWORD *pnTestTail; // ebp
  _DWORD *jnTestTail; // edi
  _DWORD *chainNode; // esi
  int prevPnTestHead; // ecx
  _DWORD *prevJnTestHead; // esi
  int referringNode; // ecx
  int referringNodeCopy; // edx
  _DWORD *crossPatternTest; // eax
  _DWORD *result; // eax
  _DWORD *intraPatternTest; // eax
  _DWORD *pnTests; // [esp+0h] [ebp-30h] BYREF
  _DWORD *jnTests; // [esp+4h] [ebp-2Ch] BYREF
  int patternNodeCopy; // [esp+8h] [ebp-28h]
  _DWORD *fieldNodeCopy; // [esp+Ch] [ebp-24h]
  int homogeneousFlag; // [esp+10h] [ebp-20h]
  _DWORD *pnTestHead; // [esp+14h] [ebp-1Ch]
  _DWORD *i; // [esp+18h] [ebp-18h]

  fieldNodeCopy = fieldNode;
  patternNodeCopy = patternNode;
  homogeneousFlag = 1;
  pnTests = 0;
  jnTests = 0;
  if ( !fieldNode )
  {
    Rules_ReportSystemError(0, 3);
    IO_RunRouterExitCallbacks();
  }
  bottomChain = fieldNodeCopy[17];
  if ( bottomChain && *(_DWORD *)(bottomChain + 68) )
    homogeneousFlag = AST_IsFieldAccessHomogeneousAcrossHierarchy(fieldNodeCopy[17], fieldNodeCopy[7]);
  pnTestTail = 0;
  jnTestTail = 0;
  pnTestHead = 0;
  chainNode = (_DWORD *)fieldNodeCopy[17];
  for ( i = 0; chainNode; chainNode = (_DWORD *)chainNode[17] )
  {
    AST_AccumulateFieldAccessTestChain(chainNode, homogeneousFlag, (signed int *)&jnTests, (signed int *)&pnTests);
    if ( pnTests )
    {
      if ( pnTestTail )
        *(_DWORD *)((char *)pnTestTail + 10) = pnTests;
      else
        pnTestHead = pnTests;
      pnTestTail = pnTests;
    }
    if ( jnTests )
    {
      if ( jnTestTail )
        *(_DWORD *)((char *)jnTestTail + 10) = jnTests;
      else
        i = jnTests;
      jnTestTail = jnTests;
    }
  }
  if ( pnTestHead && *(_DWORD *)((char *)pnTestHead + 10) )
  {
    pnTestHead = (_DWORD *)AST_NewNode(10, g_ClipsSymbolOr);
    *(_DWORD *)((char *)pnTestHead + 6) = prevPnTestHead;
  }
  prevJnTestHead = i;
  if ( i && *(_DWORD *)((char *)i + 10) )
  {
    i = (_DWORD *)AST_NewNode(10, g_ClipsSymbolOr);
    *(_DWORD *)((char *)i + 6) = prevJnTestHead;
  }
  if ( *fieldNodeCopy == 16 || *fieldNodeCopy == 15 )
  {
    referringNode = fieldNodeCopy[5];
    if ( referringNode )
    {
      referringNodeCopy = fieldNodeCopy[5];
      if ( *(_DWORD *)(referringNode + 28) == fieldNodeCopy[7] )
      {
        intraPatternTest = (_DWORD *)AST_InvokeFieldAccessValidator((int)fieldNodeCopy, (int)fieldNodeCopy);
        pnTestHead = AST_MergeFieldAccessNodes(intraPatternTest, pnTestHead);
      }
      else if ( *(int *)(referringNodeCopy + 28) > 0 )
      {
        crossPatternTest = (_DWORD *)AST_BuildCrossClassFieldAccessTest((int)fieldNodeCopy, referringNodeCopy);
        i = AST_MergeFieldAccessNodes(crossPatternTest, i);
      }
    }
  }
  fieldNodeCopy[13] = pnTestHead;
  result = AST_MergeFieldAccessNodes(*(_DWORD **)(patternNodeCopy + 52), i);
  *(_DWORD *)(patternNodeCopy + 52) = result;
  return result;
}
// 4E52B5: variable 'v6' is possibly undefined
// 54E664: using guessed type int dword_54E664;

//----- (004E53B0) --------------------------------------------------------
_DWORD * AST_AccumulateFieldAccessTestChain(_DWORD *result, int homogeneousFlag, signed int *jnTests, signed int *pnTests)
{
  int currentNode; // esi
  _DWORD *pnResult; // [esp+0h] [ebp-18h] BYREF
  _DWORD *jnResult; // [esp+4h] [ebp-14h] BYREF
  int homogeneousCopy; // [esp+8h] [ebp-10h]

  currentNode = (int)result;
  homogeneousCopy = homogeneousFlag;
  *pnTests = 0;
  *jnTests = 0;
  if ( result )
  {
    do
    {
      AST_DispatchFieldAccessNodeBuild(currentNode, homogeneousCopy, &jnResult, &pnResult);
      *pnTests = (signed int)AST_MergeFieldAccessNodes((_DWORD *)*pnTests, pnResult);
      result = AST_MergeFieldAccessNodes((_DWORD *)*jnTests, jnResult);
      *jnTests = (signed int)result;
      currentNode = *(_DWORD *)(currentNode + 64);
    }
    while ( currentNode );
  }
  return result;
}

//----- (004E5420) --------------------------------------------------------
int  AST_DispatchFieldAccessNodeBuild(int theNode, int homogeneousFlag, _DWORD *jnTestOut, _DWORD *pnTestOut)
{
  int result; // eax
  unsigned int nodeType; // edx
  _DWORD *v7; // ecx
  _DWORD *v8; // ecx
  _DWORD *v9; // ecx
  int referringNode; // eax
  _DWORD *v11; // ecx

  result = homogeneousFlag;
  *pnTestOut = 0;
  *jnTestOut = 0;
  nodeType = *(_DWORD *)theNode;
  if ( *(_DWORD *)theNode == 3 || nodeType == 2 || nodeType == 8 || nodeType < 2 )
  {
    if ( result == 1 )
    {
      result = AST_BuildFieldAccessNodePN(theNode);
      *pnTestOut = result;
    }
    else
    {
      result = AST_BuildFieldAccessNodeJN(theNode);
      *v7 = result;
    }
  }
  else
  {
    switch ( nodeType )
    {
      case 0x5Du:
        if ( result == 1 && AST_IsFieldPositionConsistent(*(_DWORD **)(theNode + 56), *(_DWORD *)(theNode + 28)) == 1 )
        {
          result = AST_BuildNegatedFieldAccessNodeJN(theNode);
          *pnTestOut = result;
        }
        else
        {
          result = AST_BuildNegatedFieldAccessNodePN(theNode);
          *v8 = result;
        }
        break;
      case 0x5Eu:
        if ( result == 1 && AST_IsFieldPositionConsistent(*(_DWORD **)(theNode + 56), *(_DWORD *)(theNode + 28)) == 1 )
        {
          result = AST_BuildFieldAccessComparisonNodeJN(theNode);
          *pnTestOut = result;
        }
        else
        {
          result = AST_BuildFieldAccessComparisonNodePN(theNode);
          *v9 = result;
        }
        break;
      case 0xFu:
      case 0x10u:
        if ( result == 1 && (referringNode = *(_DWORD *)(theNode + 20)) != 0 && *(_DWORD *)(referringNode + 28) == *(_DWORD *)(theNode + 28) )
        {
          result = AST_InvokeFieldAccessValidator(theNode, (int)jnTestOut);
          *pnTestOut = result;
        }
        else
        {
          result = AST_BuildCrossClassFieldAccessTest(theNode, *(_DWORD *)(theNode + 20));
          *v11 = result;
        }
        break;
    }
  }
  return result;
}
// 4E5454: simplified comparisons for 'edx.4': ==0 || ==1 became <2u
// 4E5487: variable 'v7' is possibly undefined
// 4E5492: variable 'v8' is possibly undefined
// 4E54C2: variable 'v9' is possibly undefined
// 4E5506: variable 'v11' is possibly undefined

//----- (004E5510) --------------------------------------------------------
int  AST_BuildFieldAccessNodePN(int theNode)
{
  int patternType; // eax
  int eqSymbol; // edx
  signed int callNode; // ebx
  int v5; // ecx
  _DWORD *valueNode; // ecx

  patternType = *(_DWORD *)(theNode + 24);
  if ( *(_DWORD *)(patternType + 48) )
    return (*(int (**)(void))(patternType + 48))();
  if ( (*(_BYTE *)(theNode + 8) & 1) != 0 )
    eqSymbol = g_ClipsSymbolNeq;
  else
    eqSymbol = g_ClipsSymbolEq;
  callNode = AST_NewNode(10, eqSymbol);
  *(_DWORD *)(callNode + 6) = (*(int (**)(void))(*(_DWORD *)(v5 + 24) + 56))();
  *(_DWORD *)(*(_DWORD *)(callNode + 6) + 10) = AST_NewNode(*valueNode, valueNode[1]);
  return callNode;
}
// 4E5536: variable 'v5' is possibly undefined
// 4E5544: variable 'v6' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5570) --------------------------------------------------------
int  AST_BuildFieldAccessNodeJN(int theNode)
{
  int patternType; // eax
  int eqSymbol; // edx
  signed int callNode; // ebx
  int v5; // ecx
  _DWORD *valueNode; // ecx

  patternType = *(_DWORD *)(theNode + 24);
  if ( *(_DWORD *)(patternType + 32) )
    return (*(int (**)(void))(patternType + 32))();
  if ( (*(_BYTE *)(theNode + 8) & 1) != 0 )
    eqSymbol = g_ClipsSymbolNeq;
  else
    eqSymbol = g_ClipsSymbolEq;
  callNode = AST_NewNode(10, eqSymbol);
  *(_DWORD *)(callNode + 6) = (*(int (**)(void))(*(_DWORD *)(v5 + 24) + 40))();
  *(_DWORD *)(*(_DWORD *)(callNode + 6) + 10) = AST_NewNode(*valueNode, valueNode[1]);
  return callNode;
}
// 4E5596: variable 'v5' is possibly undefined
// 4E55A4: variable 'v6' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E55D0) --------------------------------------------------------
int  AST_BuildNegatedFieldAccessNodePN(int theNode)
{
  int result; // eax
  int v2; // edx
  int innerTest; // ecx

  result = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(theNode + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
  {
    result = AST_NewNode(10, g_ClipsNotSymbol);
    *(_DWORD *)(result + 6) = innerTest;
  }
  return result;
}
// 4E55DE: variable 'v2' is possibly undefined
// 4E55F9: variable 'v3' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004E5600) --------------------------------------------------------
int  AST_BuildNegatedFieldAccessNodeJN(int theNode)
{
  int result; // eax
  int v2; // edx
  int innerTest; // ecx

  result = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(theNode + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
  {
    result = AST_NewNode(10, g_ClipsNotSymbol);
    *(_DWORD *)(result + 6) = innerTest;
  }
  return result;
}
// 4E560E: variable 'v2' is possibly undefined
// 4E5629: variable 'v3' is possibly undefined
// 54E660: using guessed type int dword_54E660;

//----- (004E5630) --------------------------------------------------------
int  AST_BuildFieldAccessComparisonNodePN(int theField)
{
  int convertedExpr; // esi
  int v2; // ecx
  int compareSymbol; // edx
  int v4; // ecx
  __int64 v5; // rax

  convertedExpr = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(theField + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
    compareSymbol = g_ClipsSymbolNeq;
  else
    compareSymbol = g_ClipsSymbolEq;
  AST_NewNode(10, compareSymbol);
  v5 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v4 + 24) + 40))();
  *(_DWORD *)(HIDWORD(v5) + 6) = v5;
  *(_DWORD *)(v5 + 10) = convertedExpr;
  return HIDWORD(v5);
}
// 4E5640: variable 'v2' is possibly undefined
// 4E5658: variable 'v4' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5680) --------------------------------------------------------
int  AST_BuildFieldAccessComparisonNodeJN(int theField)
{
  int convertedExpr; // esi
  int v2; // ecx
  int compareSymbol; // edx
  int v4; // ecx
  __int64 v5; // rax

  convertedExpr = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(theField + 56));
  if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
    compareSymbol = g_ClipsSymbolNeq;
  else
    compareSymbol = g_ClipsSymbolEq;
  AST_NewNode(10, compareSymbol);
  v5 = ((__int64 (*)(void))*(_DWORD *)(*(_DWORD *)(v4 + 24) + 56))();
  *(_DWORD *)(HIDWORD(v5) + 6) = v5;
  *(_DWORD *)(v5 + 10) = convertedExpr;
  return HIDWORD(v5);
}
// 4E5690: variable 'v2' is possibly undefined
// 4E56A8: variable 'v4' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E56D0) --------------------------------------------------------
int  AST_CloneFieldAccessSubtreePN(int result)
{
  int currentNode; // edx
  _DWORD *freeListEntry; // ebx
  signed int newExpr; // ecx
  int nextArgExpr; // eax
  int v5; // ecx
  int v6; // edx
  int argListExpr; // eax
  _DWORD *v8; // edx
  int v9; // ecx
  int resultExpr; // ebx

  currentNode = result;
  if ( result )
  {
    freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 56);
    if ( freeListEntry )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(g_ClipsMemoryTable + 56) = *freeListEntry;
      newExpr = g_ClipsMemFreeListTemp;
    }
    else
    {
      newExpr = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    *(_WORD *)newExpr = *(_WORD *)currentNode;
    *(_DWORD *)(newExpr + 2) = *(_DWORD *)(currentNode + 4);
    nextArgExpr = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(currentNode + 64));
    *(_DWORD *)(v5 + 10) = nextArgExpr;
    argListExpr = AST_CloneFieldAccessSubtreePN(*(_DWORD *)(v6 + 68));
    *(_DWORD *)(v9 + 6) = argListExpr;
    resultExpr = v9;
    if ( *v8 == 15 || *v8 == 16 )
    {
      (*(void (**)(void))(*(_DWORD *)(v8[5] + 24) + 36))();
    }
    else if ( *(_WORD *)v9 == 13 )
    {
      Defglobal_ResolveGlobalVariableReference(v9, v9);
      return resultExpr;
    }
    return resultExpr;
  }
  return result;
}
// 4E570C: variable 'v5' is possibly undefined
// 4E570F: variable 'v6' is possibly undefined
// 4E5717: variable 'v9' is possibly undefined
// 4E571A: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
