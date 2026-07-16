/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004BBFE0) --------------------------------------------------------
_DWORD * Rules_ParseTemplateSlotList(char *readSource, _DWORD *inputToken, double a3)
{
  _DWORD *v4; // ecx
  _DWORD *slotList; // edi
  int lastSlot; // ebp
  _DWORD *v7; // ecx
  int newSlot; // eax
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // edx

  v4 = inputToken;
  slotList = 0;
  lastSlot = 0;
  if ( *inputToken == 101 )
  {
LABEL_12:
    IO_OutWriteToken(asc_50A250);
    return slotList;
  }
  else
  {
    while ( 1 )
    {
      if ( *v4 != 100 )
      {
        Parser_ReportSyntaxError();
        Rules_FreeTemplateSlotList((int)slotList);
        Rules_FreeTemplateSlotList(0);
        g_DeftemplateSlotParseErrorFlag = v12;
        return 0;
      }
      Parser_NextToken((int)readSource, (int)v4);
      if ( *v7 != 2 )
      {
        Parser_ReportSyntaxError();
        Rules_FreeTemplateSlotList((int)slotList);
        Rules_FreeTemplateSlotList(0);
        g_DeftemplateSlotParseErrorFlag = v13;
        return 0;
      }
      newSlot = Rules_ParseTemplateSlot(readSource, (int)v7, slotList, a3);
      if ( g_DeftemplateSlotParseErrorFlag == 1 )
        break;
      if ( newSlot )
      {
        if ( lastSlot )
          *(_DWORD *)(lastSlot + 16) = newSlot;
        else
          slotList = (_DWORD *)newSlot;
        lastSlot = newSlot;
      }
      Parser_NextToken((int)readSource, v9);
      if ( *v4 != 101 )
      {
        IO_OutNewline();
        IO_OutWriteToken(asc_50A248);
        IO_OutWriteToken(*(char **)(v10 + 8));
      }
      if ( *v4 == 101 )
        goto LABEL_12;
    }
    Rules_FreeTemplateSlotList(newSlot);
    Rules_FreeTemplateSlotList((int)slotList);
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
int  Rules_ParseTemplateSlot(char *readSource, int slotKeyword, _DWORD *slotList, double a4)
{
  int v5; // ecx
  int v6; // ecx
  BOOL multifieldSlot; // edi
  int v8; // ecx
  _DWORD *inputToken; // ecx
  int result; // eax
  __int16 *v11; // ecx
  int theSlot; // esi
  int v13; // ecx
  int v14; // edx
  char v15; // ah
  int v16; // ecx
  char *v17; // edx

  if ( !strcmp_(slotKeyword, aField_0) || !strcmp_(v5, aMultifield_2) || !strcmp_(v5, aSlot_3) || !strcmp_(v5, aMultislot) )
  {
    multifieldSlot = !strcmp_(v5, aMultifield_2) || !strcmp_(v6, aMultislot);
    IO_OutWriteToken(asc_50A27C);
    Parser_NextToken((int)readSource, v8);
    if ( *inputToken == 2 )
    {
      if ( slotList )
      {
        while ( inputToken[1] != *slotList )
        {
          slotList = (_DWORD *)slotList[4];
          if ( !slotList )
            goto LABEL_8;
        }
        Rules_ReportAlreadyParsed((int)inputToken, *(_DWORD *)(*slotList + 16));
        g_DeftemplateSlotParseErrorFlag = 1;
        return 0;
      }
      else
      {
LABEL_8:
        result = Rules_ParseTemplateSlotAttributes(readSource, inputToken[1], (int)inputToken, multifieldSlot, a4);
        theSlot = result;
        if ( result )
        {
          if ( Rules_CheckConstraintParseConflicts(*(_DWORD *)(result + 8), v11) )
          {
            v15 = *(_BYTE *)(v14 + 4);
            if ( ((v15 & 4) != 0 || (v15 & 8) != 0)
              && Rules_CheckFieldExprListAgainstConstraint(*(int **)(theSlot + 12), *(_DWORD *)(theSlot + 8))
              && Rules_StaticConstraintCheckingEnabled() )
            {
              if ( (*(_BYTE *)(theSlot + 4) & 8) != 0 )
                v17 = aTheDefaultDyna;
              else
                v17 = aTheDefaultAttr;
              Rules_PrintConstraintViolationMessage((int)aAnExpression, (int)v17, 0, 0, *(_DWORD *)theSlot, 0, v16, *(_DWORD *)(theSlot + 8), 1);
              Rules_FreeTemplateSlotList(theSlot);
              g_DeftemplateSlotParseErrorFlag = 1;
              return 0;
            }
            else
            {
              return theSlot;
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
int  Rules_ParseTemplateSlotAttributes(char *readSource, int slotName, int inputToken, int multifieldSlot, double a5)
{
  _DWORD *freeSlotNode; // ecx
  int *newSlot; // edx
  int slotNameValue; // eax
  int isMultifield; // ebx
  int theSlot; // esi
  int parseNode; // eax
  int v13; // edx
  char multifieldByte; // al
  int slotFlags; // edx
  int v16; // edx
  int v17; // ecx
  int v19; // ecx
  char defaultFlagBits; // al
  int defaultExpr; // eax
  int v22; // ecx
  int v23; // ecx
  char dynamicFlagBits; // cl
  char parsedFlagBits; // dl
  int noneSpecified; // [esp+0h] [ebp-24h] BYREF
  int deriveSpecified; // [esp+4h] [ebp-20h] BYREF
  __int16 parsedConstraints; // [esp+8h] [ebp-1Ch] BYREF
  int savedSlotName; // [esp+Ch] [ebp-18h]
  int defaultParsed; // [esp+10h] [ebp-14h]
  int savedMultifieldSlot; // [esp+14h] [ebp-10h]

  savedSlotName = slotName;
  savedMultifieldSlot = multifieldSlot;
  freeSlotNode = *(_DWORD **)(g_ClipsMemoryTable + 80);
  defaultParsed = 0;
  if ( freeSlotNode )
  {
    g_ClipsMemFreeListTemp = (int)freeSlotNode;
    *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeSlotNode;
    newSlot = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    newSlot = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
  }
  slotNameValue = savedSlotName;
  isMultifield = savedMultifieldSlot;
  newSlot[3] = 0;
  theSlot = (int)newSlot;
  *newSlot = slotNameValue;
  parseNode = Rules_CreateLHSParseNode();
  *(_DWORD *)(v13 + 8) = parseNode;
  if ( isMultifield )
    *(_BYTE *)(parseNode + 1) |= 0x80u;
  multifieldByte = savedMultifieldSlot;
  *(_BYTE *)(theSlot + 4) &= ~1u;
  slotFlags = *(_DWORD *)(theSlot + 4);
  *(_DWORD *)(theSlot + 16) = 0;
  *(_DWORD *)(theSlot + 4) = multifieldByte & 1 | slotFlags;
  *(_BYTE *)(theSlot + 4) &= 0xF1u;
  Rules_ResetConstraintParsedFlags(&parsedConstraints);
  Parser_NextToken((int)readSource, v16);
  if ( *(_DWORD *)inputToken == 101 )
    return theSlot;
  while ( 1 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_50A27C);
    IO_OutWriteToken(*(char **)(inputToken + 8));
    if ( *(_DWORD *)inputToken != 100 || (Parser_NextToken((int)readSource, inputToken), *(_DWORD *)inputToken != 2) )
    {
      Parser_ReportSyntaxError();
      Rules_FreeTemplateSlotList(theSlot);
      g_DeftemplateSlotParseErrorFlag = 1;
      return 0;
    }
    if ( Rules_IsConstraintAttributeKeyword(*(_DWORD *)(*(_DWORD *)(inputToken + 4) + 16)) )
    {
      if ( !Rules_ParseStandardConstraintAttribute(readSource, *(const char **)(*(_DWORD *)(inputToken + 4) + 16), &parsedConstraints, *(_DWORD *)(theSlot + 8), savedMultifieldSlot) )
      {
        g_DeftemplateSlotParseErrorFlag = 1;
        Rules_FreeTemplateSlotList(theSlot);
        return 0;
      }
      goto LABEL_10;
    }
    if ( strcmp_(v17, aDefault) && strcmp_(v19, aDefaultDynamic) )
    {
      Parser_ReportSyntaxError();
      Rules_FreeTemplateSlotList(theSlot);
      g_DeftemplateSlotParseErrorFlag = v22;
      return 0;
    }
    if ( defaultParsed )
    {
      Rules_ReportAlreadyParsed(1, 0);
      g_DeftemplateSlotParseErrorFlag = v23;
      Rules_FreeTemplateSlotList(theSlot);
      return 0;
    }
    *(_BYTE *)(theSlot + 4) &= ~2u;
    if ( !strcmp_(v19, aDefault) )
    {
      defaultFlagBits = *(_BYTE *)(theSlot + 4) | 4;
      *(_BYTE *)(theSlot + 4) = defaultFlagBits;
      *(_BYTE *)(theSlot + 4) = defaultFlagBits & 0xF7;
    }
    else
    {
      dynamicFlagBits = *(_BYTE *)(theSlot + 4) & 0xF3;
      *(_BYTE *)(theSlot + 4) = dynamicFlagBits;
      *(_BYTE *)(theSlot + 4) = dynamicFlagBits | 8;
    }
    defaultExpr = Rules_ParseDefaultAttribute((int)readSource, savedMultifieldSlot, 1, *(_DWORD *)(theSlot + 4) << 28 >> 31, a5, &noneSpecified, &deriveSpecified, &g_DeftemplateSlotParseErrorFlag);
    if ( g_DeftemplateSlotParseErrorFlag == 1 )
      break;
    defaultParsed = 1;
    if ( deriveSpecified )
    {
      *(_BYTE *)(theSlot + 4) &= ~4u;
    }
    else if ( noneSpecified )
    {
      parsedFlagBits = *(_BYTE *)(theSlot + 4) | 2;
      *(_BYTE *)(theSlot + 4) = parsedFlagBits;
      *(_BYTE *)(theSlot + 4) = parsedFlagBits & 0xFB;
      *(_DWORD *)(theSlot + 12) = defaultExpr;
      goto LABEL_10;
    }
    *(_DWORD *)(theSlot + 12) = defaultExpr;
LABEL_10:
    Parser_NextToken((int)readSource, inputToken);
    if ( *(_DWORD *)inputToken == 101 )
      return theSlot;
  }
  Rules_FreeTemplateSlotList(theSlot);
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
signed int  Rules_FetchPatternFieldRecord(int fieldNode, _DWORD *returnValue)
{
  _DWORD *fieldDescriptor; // eax
  int factAddress; // ebx
  int slotBase; // edi
  __int16 *singleFieldSlot; // eax
  int valueType; // ebp
  signed int result; // eax
  int slotIndex; // ebx
  unsigned int markerBits; // edx
  int multifieldSlot; // edi
  int segmentOffset; // eax
  __int16 *elementPtr; // edi
  int v14[6]; // [esp+0h] [ebp-18h] BYREF

  fieldDescriptor = *(_DWORD **)(fieldNode + 16);
  factAddress = g_CurrentPatternFact;
  if ( (*(_BYTE *)fieldDescriptor & 1) != 0 )
  {
    returnValue[1] = 6;
    result = 1;
    returnValue[2] = factAddress;
  }
  else
  {
    slotBase = g_CurrentPatternFact + 54;
    if ( (*(_BYTE *)fieldDescriptor & 2) != 0 )
    {
      singleFieldSlot = (__int16 *)(slotBase + 6 * (*fieldDescriptor << 14 >> 24));
      returnValue[1] = *singleFieldSlot;
      valueType = returnValue[1];
      returnValue[2] = *(_DWORD *)(singleFieldSlot + 1);
      if ( valueType == 4 )
      {
        returnValue[3] = 0;
        returnValue[4] = *(_DWORD *)(*(_DWORD *)(singleFieldSlot + 1) + 6) - 1;
      }
      return 1;
    }
    else
    {
      slotIndex = *fieldDescriptor << 14 >> 24;
      markerBits = *fieldDescriptor << 22;
      v14[0] = -1;
      multifieldSlot = 6 * slotIndex + slotBase;
      segmentOffset = Rules_ComputeMultifieldSegmentOffset(g_ClipsFactMatchMarkerList, HIBYTE(markerBits), v14, slotIndex);
      if ( v14[0] == -1 )
      {
        elementPtr = (__int16 *)(*(_DWORD *)(multifieldSlot + 2) + 14 + 6 * segmentOffset);
        returnValue[1] = *elementPtr;
        returnValue[2] = *(_DWORD *)(elementPtr + 1);
      }
      else
      {
        returnValue[1] = 4;
        returnValue[2] = *(_DWORD *)(multifieldSlot + 2);
        returnValue[3] = segmentOffset;
        returnValue[4] = v14[0] + segmentOffset - 1;
      }
      return 1;
    }
  }
  return result;
}
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (004BC6E0) --------------------------------------------------------
signed int  Rules_FetchPatternFieldSimple(int fieldNode, int returnValue)
{
  uintptr_t payload; // eax
  uintptr_t descriptor; // eax

  if ( !fieldNode )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)fieldNode + 16);
  if ( !payload )
    return 1;
  descriptor = (uintptr_t)(unsigned int)g_CurrentPatternFact + 54 + 6 * (unsigned __int8)*(_DWORD *)payload;
  *(_DWORD *)(returnValue + 4) = *(__int16 *)descriptor;
  *(_DWORD *)(returnValue + 8) = *(_DWORD *)(descriptor + 2);
  return 1;
}
// 54E528: using guessed type int dword_54E528;

//----- (004BC720) --------------------------------------------------------
signed int  Rules_FetchPatternNestedFieldRecord(int fieldNode, _DWORD *returnValue)
{
  uintptr_t payload; // eax
  unsigned int payload_word; // ebx
  uintptr_t descriptor; // edx
  uintptr_t vector_entry; // eax
  int index; // edx

  if ( !fieldNode || !returnValue )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)fieldNode + 16);
  if ( !payload )
    return 1;
  payload_word = *(_DWORD *)payload;
  descriptor = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_CurrentPatternFact
                                                   + 6 * ((payload_word << 8) >> 24)
                                                   + 56);
  if ( (*(_BYTE *)payload & 1) != 0 && (*(_BYTE *)payload & 2) != 0 )
  {
    returnValue[1] = 4;
    returnValue[2] = descriptor;
    returnValue[3] = (payload_word << 23) >> 25;
    returnValue[4] = *(_DWORD *)(descriptor + 6) - (((payload_word << 16) >> 25) + 1);
  }
  else
  {
    if ( (*(_BYTE *)payload & 1) != 0 )
      index = (payload_word << 23) >> 25;
    else
      index = *(_DWORD *)(descriptor + 6) - (((payload_word << 16) >> 25) + 1);
    vector_entry = descriptor + 14 + 6 * index;
    returnValue[1] = *(__int16 *)vector_entry;
    returnValue[2] = *(_DWORD *)(vector_entry + 2);
  }
  return 1;
}
// 54E528: using guessed type int dword_54E528;

//----- (004BC7C0) --------------------------------------------------------
int  Rules_TestPatternFieldSimple(int fieldNode)
{
  uintptr_t payload; // edx
  uintptr_t descriptor; // eax
  uintptr_t expression; // ecx

  if ( !fieldNode )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)fieldNode + 16);
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
int  Rules_TestPatternNestedField(int fieldNode)
{
  uintptr_t payload; // edx
  uintptr_t descriptor; // eax
  uintptr_t vector; // eax
  unsigned int index; // ecx
  uintptr_t expression; // ecx

  if ( !fieldNode )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)fieldNode + 16);
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
signed int  Rules_FetchJoinBindingFieldRecord(int fieldNode, _DWORD *returnValue)
{
  _DWORD *fieldDescriptor; // eax
  int *bindingEntry; // ebp
  int factAddress; // edi
  int matchMarkers; // ebp
  int factSlotBase; // edx
  __int16 *fieldPtr; // eax
  int fieldType; // edi
  signed int result; // eax
  int bindingIndex; // edx
  int slotIndex; // ebx
  int targetIndex; // ecx
  _WORD *slotFieldPtr; // eax
  __int16 slotType; // dx
  int segmentBegin; // eax
  _WORD *v17; // edx
  __int16 *multifieldElemPtr; // eax
  int segmentLength; // [esp+0h] [ebp-24h] BYREF
  int v20; // [esp+4h] [ebp-20h]
  int slotByteOffset; // [esp+8h] [ebp-1Ch]
  _WORD *v22; // [esp+Ch] [ebp-18h]

  fieldDescriptor = *(_DWORD **)(fieldNode + 16);
  if ( g_Rules_GlobalRHSBinds )
  {
    bindingIndex = *fieldDescriptor << 22 >> 24;
    if ( (*(_DWORD *)g_CurrentPatternEntityPtr << 16 >> 25) - 1 == bindingIndex )
      bindingEntry = *(int **)(g_Rules_GlobalRHSBinds + 8);
    else
      bindingEntry = *(int **)(g_Clips_CurrentPartialMatch + 4 * bindingIndex + 8);
  }
  else
  {
    bindingEntry = *(int **)(g_Clips_CurrentPartialMatch + 4 * (*fieldDescriptor << 22 >> 24) + 8);
  }
  factAddress = *bindingEntry;
  matchMarkers = bindingEntry[1];
  if ( (*(_BYTE *)fieldDescriptor & 1) != 0 )
  {
    returnValue[1] = 6;
    result = 1;
    returnValue[2] = factAddress;
  }
  else
  {
    factSlotBase = factAddress + 54;
    if ( (*(_BYTE *)fieldDescriptor & 2) != 0 )
    {
      fieldPtr = (__int16 *)(factSlotBase + 6 * (*fieldDescriptor << 14 >> 24));
      returnValue[1] = *fieldPtr;
      fieldType = returnValue[1];
      returnValue[2] = *(_DWORD *)(fieldPtr + 1);
      if ( fieldType == 4 )
      {
        returnValue[3] = 0;
        returnValue[4] = *(_DWORD *)(*(_DWORD *)(fieldPtr + 1) + 6) - 1;
      }
      return 1;
    }
    else
    {
      slotIndex = *fieldDescriptor << 14 >> 24;
      targetIndex = *fieldDescriptor << 6 >> 24;
      slotByteOffset = 6 * slotIndex;
      slotFieldPtr = (_WORD *)(factSlotBase + 6 * slotIndex);
      v20 = targetIndex;
      slotType = *slotFieldPtr;
      v22 = slotFieldPtr;
      if ( slotType == 4 )
      {
        segmentLength = -1;
        segmentBegin = Rules_ComputeMultifieldSegmentOffset(matchMarkers, v20, &segmentLength, slotIndex);
        if ( segmentLength == -1 )
        {
          multifieldElemPtr = (__int16 *)(*(_DWORD *)(slotByteOffset + factAddress + 56) + 14 + 6 * segmentBegin);
          returnValue[1] = *multifieldElemPtr;
          returnValue[2] = *(_DWORD *)(multifieldElemPtr + 1);
        }
        else
        {
          v17 = v22;
          returnValue[1] = 4;
          returnValue[2] = *(_DWORD *)(v17 + 1);
          returnValue[3] = segmentBegin;
          returnValue[4] = segmentLength + segmentBegin - 1;
        }
        return 1;
      }
      else
      {
        returnValue[1] = slotType;
        returnValue[2] = *(_DWORD *)(v22 + 1);
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
signed int  Rules_FetchJoinBindingFieldSimple(int fieldNode, int returnValue)
{
  _DWORD *fieldDescriptor; // eax
  int bindingIndex; // edx
  _DWORD *bindingEntry; // edx
  int slotOffset; // ebx
  int slotBase; // eax

  fieldDescriptor = *(_DWORD **)(fieldNode + 16);
  if ( g_Rules_GlobalRHSBinds )
  {
    bindingIndex = (unsigned __int8)*fieldDescriptor;
    if ( (*(_DWORD *)g_CurrentPatternEntityPtr << 16 >> 25) - 1 == bindingIndex )
      bindingEntry = *(_DWORD **)(g_Rules_GlobalRHSBinds + 8);
    else
      bindingEntry = *(_DWORD **)(g_Clips_CurrentPartialMatch + 4 * bindingIndex + 8);
  }
  else
  {
    bindingEntry = *(_DWORD **)(g_Clips_CurrentPartialMatch + 4 * (unsigned __int8)*fieldDescriptor + 8);
  }
  slotOffset = 6 * (*fieldDescriptor << 16 >> 24);
  slotBase = *bindingEntry + 54;
  *(_DWORD *)(returnValue + 4) = *(__int16 *)(slotOffset + slotBase);
  *(_DWORD *)(returnValue + 8) = *(_DWORD *)(slotOffset + slotBase + 2);
  return 1;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCB00) --------------------------------------------------------
signed int  Rules_FetchJoinBindingNestedField(int fieldNode, _DWORD *returnValue)
{
  uintptr_t payload; // eax
  unsigned int bits; // ebx
  unsigned int fact_index; // ecx
  uintptr_t fact_cell; // esi
  uintptr_t fact_record; // esi
  uintptr_t multifield; // ecx
  unsigned int slot_index; // ecx
  uintptr_t slot_value; // eax

  if ( !fieldNode || !returnValue )
    return 1;
  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)fieldNode + 16);
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
    returnValue[1] = 4;
    returnValue[2] = (int)multifield;
    returnValue[3] = (bits << 23) >> 25;
    returnValue[4] = *(_DWORD *)(multifield + 6) - (((bits << 16) >> 25) + 1);
    return 1;
  }
  if ( (bits & 1) != 0 )
    slot_index = (bits << 23) >> 25;
  else
    slot_index = *(_DWORD *)(multifield + 6) - (((bits << 16) >> 25) + 1);
  slot_value = multifield + 14 + 6 * slot_index;
  returnValue[1] = *(__int16 *)slot_value;
  returnValue[2] = *(_DWORD *)(slot_value + 2);
  return 1;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCBF0) --------------------------------------------------------
signed int  Rules_EvalMultifieldIndexInRange(int testNode, uintptr_t returnValue)
{
  int fieldConstraint; // esi
  int marker; // eax
  int i; // ecx
  int theMultifield; // eax
  unsigned int fieldIndex; // ecx

  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  if ( !testNode )
  {
    *(_DWORD *)(returnValue + 8) = g_ClipsTrueSymbol;
    return 1;
  }
  fieldConstraint = *(_DWORD *)(testNode + 16);
  marker = g_ClipsFactMatchMarkerList;
  for ( i = 0; marker; marker = *(_DWORD *)(marker + 16) )
  {
    if ( *(_WORD *)(marker + 4) == *(_DWORD *)fieldConstraint << 15 >> 24 )
      i += *(_DWORD *)(marker + 12) - *(_DWORD *)(marker + 8) + 1;
  }
  theMultifield = *(_DWORD *)(6 * (*(_DWORD *)fieldConstraint << 15 >> 24) + g_CurrentPatternFact + 56);
  fieldIndex = (unsigned __int8)*(_DWORD *)fieldConstraint + i;
  if ( fieldIndex > *(_DWORD *)(theMultifield + 6) || (*(_BYTE *)(fieldConstraint + 1) & 1) != 0 && fieldIndex < *(_DWORD *)(theMultifield + 6) )
    return 0;
  *(_DWORD *)(returnValue + 8) = g_ClipsTrueSymbol;
  return 1;
}
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (004BCC90) --------------------------------------------------------
int  Rules_TestJoinBindingFieldsEqual(int testNode)
{
  _DWORD *payload; // edx
  int compareIndex; // ebx
  int matchBase; // ebx
  int leftField; // esi
  int rightField; // ebx

  payload = *(_DWORD **)(testNode + 16);
  compareIndex = (*payload << 15 >> 24) - 1;
  if ( (*(_DWORD *)g_CurrentPatternEntityPtr << 16 >> 25) - 1 == compareIndex )
    matchBase = **(_DWORD **)(g_Rules_GlobalRHSBinds + 8);
  else
    matchBase = **(_DWORD **)(g_Clips_CurrentPartialMatch + 4 * compareIndex + 8);
  leftField = 6 * (*payload << 23 >> 25) + **(_DWORD **)(g_Rules_GlobalRHSBinds + 8);
  rightField = 6 * (*payload << 8 >> 25) + matchBase;
  if ( *(__int16 *)(leftField + 54) == *(__int16 *)(rightField + 54) && *(_DWORD *)(leftField + 56) == *(_DWORD *)(rightField + 56) )
    return *payload & 1;
  else
    return *payload << 30 >> 31;
}
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;

//----- (004BCD30) --------------------------------------------------------
int  Rules_TestJoinBindingFieldsEqualRanged(int testNode)
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

  payload = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)testNode + 16);
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
int  Rules_EvalPatternFieldsEqual(int testNode, int returnValue)
{
  _DWORD *payload; // edx
  __int16 *leftField; // esi
  __int16 *rightField; // eax
  int result; // eax

  payload = *(_DWORD **)(testNode + 16);
  leftField = (__int16 *)(g_CurrentPatternFact + 54 + 6 * (*payload << 23 >> 25));
  rightField = (__int16 *)(g_CurrentPatternFact + 54 + 6 * (*payload << 16 >> 25));
  if ( *leftField == *rightField && *(_DWORD *)(leftField + 1) == *(_DWORD *)(rightField + 1) )
    result = *payload & 1;
  else
    result = *payload << 30 >> 31;
  *(_DWORD *)(returnValue + 4) = 2;
  if ( result )
    *(_DWORD *)(returnValue + 8) = g_ClipsTrueSymbol;
  else
    *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  return result;
}
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;
// 54E528: using guessed type int dword_54E528;

//----- (004BCF10) --------------------------------------------------------
int  Rules_ComputeMultifieldSegmentOffset(int markerList, int targetIndex, _DWORD *outLength, int whichField)
{
  int offset; // ecx

  offset = targetIndex;
  if ( !markerList )
    return offset;
  while ( 1 )
  {
    while ( *(__int16 *)(markerList + 4) != whichField )
    {
      markerList = *(_DWORD *)(markerList + 16);
      if ( !markerList )
        return offset;
    }
    if ( targetIndex == *(_DWORD *)markerList )
      break;
    if ( targetIndex < *(_DWORD *)markerList )
      return offset;
    offset += *(_DWORD *)(markerList + 12) - *(_DWORD *)(markerList + 8);
    markerList = *(_DWORD *)(markerList + 16);
    if ( !markerList )
      return offset;
  }
  *outLength = *(_DWORD *)(markerList + 12) - *(_DWORD *)(markerList + 8) + 1;
  return offset;
}

//----- (004BCF60) --------------------------------------------------------
signed int  Rules_EvalCopyMultifieldBinding(int a1, _DWORD *returnValue, double context)
{
  (void)a1;
  Rules_StoreEvaluatedNodesAsMultifield(returnValue, *(_DWORD *)(g_ClipsCurrentExpression + 6), 0, context);
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (004BCF80) --------------------------------------------------------
int  Rules_RunIncrementalReset(int result, double context)
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
      Rules_DriveIncrementalResetForModule(i, context);
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
int  Rules_ToggleJoinNetworkResetMark(int result, char setMark)
{
  int module; // ebp
  int markBits; // edi
  int joinNode; // ecx
  int nextJoin; // edx

  module = result;
  if ( result )
  {
    markBits = 16 * (setMark & 1);
    do
    {
      joinNode = *(_DWORD *)(module + 44);
      if ( joinNode )
      {
        do
        {
          BYTE1(result) = *(_BYTE *)joinNode;
          if ( (*(_BYTE *)joinNode & 0x10) != 0 && (result & 0x400) == 0 )
          {
            *(_BYTE *)joinNode = BYTE1(result) & 0xEF;
            *(_DWORD *)joinNode |= markBits;
            result = Rules_RunConstructTypeIncrementalReset(*(_DWORD *)joinNode << 23 >> 29, joinNode);
          }
          if ( (*(_BYTE *)joinNode & 4) != 0 )
            nextJoin = *(_DWORD *)(joinNode + 16);
          else
            nextJoin = *(_DWORD *)(joinNode + 24);
          joinNode = nextJoin;
        }
        while ( nextJoin );
      }
      module = *(_DWORD *)(module + 48);
    }
    while ( module );
  }
  return result;
}
// 4BD037: variable 'v4' is possibly undefined

//----- (004BD060) --------------------------------------------------------
int  Rules_DriveIncrementalResetForModule(int result, double context)
{
  int module; // ebx
  int joinNode; // esi
  int v4; // eax
  bool v5; // zf
  int i; // ecx
  int v7; // ecx

  module = result;
  joinNode = *(_DWORD *)(result + 44);
  if ( joinNode )
  {
    do
    {
      while ( 1 )
      {
        if ( (*(_BYTE *)joinNode & 0x10) != 0 )
        {
          if ( (*(_DWORD *)joinNode & 1) == 1 )
          {
            v4 = (*(_BYTE *)joinNode & 4) != 0 ? 0 : *(_DWORD *)(joinNode + 16);
            v5 = (*(_BYTE *)(v4 + 12) & 8) == 0;
          }
          else
          {
            v5 = (**(_BYTE **)(joinNode + 24) & 0x10) == 0;
          }
          if ( v5 )
            Rules_DriveIncrementalResetJoin((int *)joinNode, context);
        }
        else if ( module == *(_DWORD *)(joinNode + 36) )
        {
          for ( i = *(_DWORD *)(joinNode + 8); i; i = *(_DWORD *)(v7 + 4) )
            Rules_AddActivation(module, i, context);
        }
        if ( (*(_BYTE *)joinNode & 4) == 0 )
          break;
        result = *(_DWORD *)(joinNode + 16);
        joinNode = result;
        if ( !result )
          return result;
      }
      result = *(_DWORD *)(joinNode + 24);
      joinNode = result;
    }
    while ( result );
  }
  return result;
}
// 4BD0C5: variable 'v7' is possibly undefined

//----- (004BD0E0) --------------------------------------------------------
int * Rules_DriveIncrementalResetJoin(int *result, double context)
{
  char *joinPtr; // esi
  int *i; // ecx
  int v4; // ecx
  int *j; // ecx
  int v6; // ecx

  joinPtr = (char *)result;
  if ( (*result & 1) == 1 )
  {
    for ( i = *(int **)result[4]; i; i = *(int **)(v4 + 4) )
      result = Rules_DriveJoinNetwork(i, joinPtr, 1, context);
  }
  else if ( !result[2] )
  {
    for ( j = *(int **)(result[6] + 8); j; j = *(int **)(v6 + 4) )
      result = Rules_DriveJoinNetwork(j, joinPtr, 0, context);
  }
  return result;
}
// 4BD107: variable 'v4' is possibly undefined
// 4BD130: variable 'v6' is possibly undefined

//----- (004BD140) --------------------------------------------------------
int  Rules_RunConstructTypeIncrementalReset(int constructType, int node)
{
  int result; // eax

  result = Rules_GetPatternParserByTypeID(constructType);
  if ( result )
  {
    if ( *(_DWORD *)(result + 72) )
      return (*(int (__cdecl **)(int))(result + 72))(node);
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
int  Rules_SetIncrementalResetCommand(int returnValue, double context)
{
  int v3; // eax
  int v4; // ecx
  int v5; // esi
  int v7; // ecx
  int v8; // ecx
  _DWORD argValue[10]; // [esp-4h] [ebp-28h] BYREF

  argValue[8] = returnValue;
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
    Rules_RtnUnknown(1, argValue, context);
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
int  Parser_ParseRequiredFunctionCall(int readSource, int context)
{
  int v3; // ecx
  int token_buffer_ptr;
  _DWORD *token_buffer;
  int result;

  token_buffer_ptr = Compat_AllocLow32Bytes(20);
  if ( !token_buffer_ptr )
    return 0;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  token_buffer[4] = context;
  Parser_NextToken(readSource, token_buffer_ptr);
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
int Parser_ParseExpression(readSource, context)
int readSource;
int context;
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
  token_buffer[4] = context;
  Parser_NextToken(readSource, token_buffer_ptr);
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
int  Parser_ParseFunctionCallExpr(int readSource, _BYTE *functionName)
{
  _BYTE *v4; // edx
  _BYTE *v5; // edx
  int v6; // eax
  int functionHandle; // edx
  int v8; // ecx
  int v9; // eax
  __int16 nodeType; // ax
  _WORD *topNode; // edi
  int v12; // ecx
  int parsedNode; // esi
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

  if ( Rules_FindModuleSeparator(functionName) )
  {
    Module_ReportIllegalSpecifierError();
    return 0;
  }
  Symbol = Rules_MakeSymbol(v4);
  v6 = Defgeneric_LookupLocalOnly(v5);
  functionHandle = v6;
  if ( v8 || v6 || (v9 = Deffunction_LookupByName(functionName)) == 0 )
  {
    if ( functionHandle )
    {
      nodeType = 11;
    }
    else
    {
      functionHandle = (int)Symbol;
      if ( !Symbol )
      {
        Rules_PrintErrorID((int)aExprnpsr, 3, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMissingFunctio, v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)functionName, v16);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_ParserError, v17);
        return 0;
      }
      nodeType = 10;
    }
  }
  else
  {
    functionHandle = v9;
    nodeType = 12;
  }
  topNode = (_WORD *)AST_NewNode(nodeType, functionHandle);
  Parser_PushFunctionParseState();
  g_ClipsParseReturnContext = v12;
  g_ParserBreakContextFlag = v12;
  if ( *topNode == 10 && *(int **)((char *)Symbol + 13) )
  {
    parsedNode = (*(int (__fastcall **)(int **, int))((char *)Symbol + 13))(Symbol, readSource);
    Parser_PopFunctionParseState();
    if ( !parsedNode )
      return 0;
    Rules_MakeSymbol(aExpand_0);
    v18 = Rules_MakeSymbol(aExpansionCal_0);
    if ( Parser_ParseExpansion(*(_DWORD *)(parsedNode + 6), v19, v20, (int)v18) )
      goto LABEL_29;
    return parsedNode;
  }
  parsedNode = Parser_CollectFunctionArguments((int)topNode, readSource, v12);
  Parser_PopFunctionParseState();
  if ( !parsedNode )
    return 0;
  Rules_MakeSymbol(aExpand_0);
  v21 = Rules_MakeSymbol(aExpansionCal_0);
  if ( Parser_ParseExpansion(*(_DWORD *)(parsedNode + 6), parsedNode, v22, (int)v21) )
    goto LABEL_29;
  if ( Rules_MakeSymbol(aExpansionCal_0) == *(int ***)(parsedNode + 2) )
    return parsedNode;
  if ( *(_WORD *)parsedNode != 10 || !Rules_StaticConstraintCheckingEnabled() )
  {
    if ( *(_WORD *)parsedNode == 12 )
    {
      v23 = AST_CountListNodes(*(_DWORD *)(parsedNode + 6));
      if ( !Deffunction_CheckArgumentCount(*(_DWORD *)(parsedNode + 2), v23) )
        goto LABEL_29;
    }
    return parsedNode;
  }
  if ( !Parser_ValidateFunctionCallArgs(parsedNode, *(int *)((char *)Symbol + 17), (int)functionName) )
    return parsedNode;
LABEL_29:
  AST_Free(parsedNode);
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
signed int  Parser_ParseExpansion(int theExpression, int topNode, int expandSymbol, int expansionCallSymbol)
{
  int currentNode; // esi
  signed int newNode; // eax
  int v8; // edx
  _WORD *operandNode; // eax
  __int16 nodeType; // cx
  int parentNode; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx

  currentNode = theExpression;
  if ( !theExpression )
    return 0;
  while ( 1 )
  {
    if ( g_SequenceOperatorRecognition || *(_WORD *)currentNode != 16 )
    {
      if ( *(_WORD *)currentNode == 16 || *(_WORD *)currentNode == 14 )
        goto LABEL_6;
    }
    else
    {
      *(_WORD *)currentNode = 15;
    }
    if ( expandSymbol != *(_DWORD *)(currentNode + 2) )
      goto LABEL_13;
LABEL_6:
    if ( *(_WORD *)topNode == 10 && !*(_WORD *)(*(_DWORD *)(topNode + 2) + 23) )
      break;
    if ( *(_DWORD *)(topNode + 2) != expansionCallSymbol )
    {
      newNode = AST_NewNode(*(_WORD *)topNode, *(_DWORD *)(topNode + 2));
      v8 = *(_DWORD *)(topNode + 6);
      *(_DWORD *)(newNode + 10) = 0;
      *(_DWORD *)(newNode + 6) = v8;
      *(_WORD *)topNode = 10;
      *(_DWORD *)(topNode + 2) = expansionCallSymbol;
      *(_DWORD *)(topNode + 6) = newNode;
    }
    if ( expandSymbol != *(_DWORD *)(currentNode + 2) )
    {
      operandNode = (_WORD *)AST_NewNode(15, *(_DWORD *)(currentNode + 2));
      if ( *(_WORD *)currentNode == 14 )
        *operandNode = 13;
      *(_WORD *)currentNode = 10;
      *(_DWORD *)(currentNode + 6) = operandNode;
      *(_DWORD *)(currentNode + 2) = expandSymbol;
    }
LABEL_13:
    if ( *(_DWORD *)(currentNode + 6) )
    {
      nodeType = *(_WORD *)currentNode;
      if ( *(_WORD *)currentNode == 11 || nodeType == 12 || nodeType == 10 )
        parentNode = currentNode;
      else
        parentNode = topNode;
      if ( Parser_ParseExpansion(*(_DWORD *)(currentNode + 6), parentNode, expandSymbol, expansionCallSymbol) )
        return 1;
    }
    currentNode = *(_DWORD *)(currentNode + 10);
    if ( !currentNode )
      return 0;
  }
  Rules_PrintErrorID((int)aExprnpsr, 4, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSequenceOperat, v13);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(**(_DWORD **)(topNode + 2) + 16), v14);
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
  _DWORD *freeBlock; // edx
  _DWORD *result; // eax

  freeBlock = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( freeBlock )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeBlock;
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
  _DWORD *frame; // eax
  int result; // eax

  frame = (_DWORD *)g_ClipsParseContextSaveStack;
  g_ClipsParseReturnContext = *(_DWORD *)g_ClipsParseContextSaveStack;
  g_ParserBreakContextFlag = *(_DWORD *)(g_ClipsParseContextSaveStack + 4);
  g_ClipsParseContextSaveStack = *(_DWORD *)(g_ClipsParseContextSaveStack + 8);
  g_ClipsMemFreeListTemp = (int)frame;
  *frame = *(_DWORD *)(g_ClipsMemoryTable + 48);
  result = g_ClipsMemFreeListTemp;
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 51B35C: using guessed type int dword_51B35C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;
