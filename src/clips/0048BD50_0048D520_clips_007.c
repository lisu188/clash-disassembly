/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0048BD50) --------------------------------------------------------
int  Lexer_ParseSlotConstraint(_DWORD *returnValue, int a2, double a3)
{
  int result; // eax
  int v5; // ecx
  int theFact; // edi
  _DWORD slotNameArg[11]; // [esp-8h] [ebp-2Ch] BYREF

  slotNameArg[9] = a2;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Lexer_TokenExpect(0, 0, 2);
  if ( result != -1 )
  {
    result = Rules_ResolveFactArgument(1, v5, 1, a3);
    theFact = result;
    if ( result )
    {
      result = Lexer_ParseValueList(2, slotNameArg, 2, a3);
      if ( result )
        return Lexer_BuildSlotNode(theFact, (char *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotNameArg[2] + 16), returnValue);
    }
  }
  return result;
}
// 48BD94: variable 'v5' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BDD0) --------------------------------------------------------
int  Lexer_BuildSlotNode(int theFact, char *slotName, _DWORD *returnValue)
{
  char *v5; // ecx
  int v7; // ecx
  signed int *slotSymbol; // eax
  int v9; // ecx
  int slotPosition; // [esp+0h] [ebp-18h] BYREF
  int theDeftemplate; // [esp+4h] [ebp-14h]

  if ( (*(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theFact + 16) + 24) & 1) != 0 )
  {
    if ( strcmp_(slotName, aImplied) )
    {
      Lexer_ErrorRecover(1);
      return Rules_ReportInvalidSlotError(v7, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theFact + 16) + 16));
    }
  }
  else
  {
    slotSymbol = Str_Intern(slotName, (int)(intptr_t)slotName);
    theDeftemplate = *(_DWORD *)(uintptr_t)(theFact + 16);
    if ( !Lexer_FindTemplateSlot(theDeftemplate, (int)(intptr_t)slotSymbol, &slotPosition) )
    {
      Lexer_ErrorRecover(1);
      return Rules_ReportInvalidSlotError(v9, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theFact + 16) + 16));
    }
  }
  if ( (*(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theFact + 16) + 24) & 1) != 0 )
    return Lexer_EmitSlotBinding(theFact, 0, (int)(intptr_t)v5, returnValue);
  else
    return Lexer_EmitSlotBinding(theFact, v5, (int)(intptr_t)v5, returnValue);
}
// 48BE07: variable 'v5' is possibly undefined
// 48BE28: variable 'v7' is possibly undefined
// 48BE62: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0048BE80) --------------------------------------------------------
int  Lexer_ParseFieldSpec(int returnValue, double a2)
{
  int result; // eax
  int v3; // ecx
  _DWORD *v4; // ecx

  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  result = Lexer_TokenExpect(0, 0, 1);
  if ( result != -1 )
  {
    result = Rules_ResolveFactArgument(1, v3, 1, a2);
    if ( result )
      return Rules_BuildFactSlotNameList(result, v4);
  }
  return result;
}
// 48BEBA: variable 'v3' is possibly undefined
// 48BEC5: variable 'v4' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0048BED0) --------------------------------------------------------
int  Rules_BuildFactSlotNameList(int theFact, _DWORD *returnValue)
{
  int theDeftemplate; // edx
  int slotChain; // edx
  signed int i; // eax
  _DWORD *theList; // eax
  int v8; // ecx
  _DWORD *theMultifield; // ebx
  _DWORD *currentSlot; // edx
  int result; // eax
  _DWORD *fieldPtr; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx

  theDeftemplate = *(_DWORD *)(uintptr_t)(theFact + 16);
  if ( (*(_BYTE *)(uintptr_t)(theDeftemplate + 24) & 1) != 0 )
  {
    returnValue[1] = 4;
    returnValue[3] = 0;
    returnValue[4] = 0;
    *((_WORD *)Rules_CreateEphemeralMultifield(1) + 7) = 2;
    result = (int)(intptr_t)Str_Intern(aImplied, v13);
    *(_DWORD *)(uintptr_t)(v14 + 16) = result;
    *(_DWORD *)(uintptr_t)(v15 + 8) = v14;
  }
  else
  {
    slotChain = *(_DWORD *)(uintptr_t)(theDeftemplate + 20);
    for ( i = 0; slotChain; ++i )
      slotChain = *(_DWORD *)(uintptr_t)(slotChain + 16);
    returnValue[1] = 4;
    returnValue[3] = 0;
    returnValue[4] = i - 1;
    theList = Rules_CreateEphemeralMultifield(i);
    *(_DWORD *)(uintptr_t)(v8 + 8) = theList;
    theMultifield = theList;
    currentSlot = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theFact + 16) + 20);
    result = 1;
    if ( currentSlot )
    {
      fieldPtr = theMultifield;
      do
      {
        *((_WORD *)fieldPtr + 7) = 2;
        fieldPtr[4] = *currentSlot;
        fieldPtr = (_DWORD *)((char *)fieldPtr + 6);
        currentSlot = (_DWORD *)(uintptr_t)currentSlot[4];
        ++result;
      }
      while ( currentSlot );
    }
  }
  return result;
}
// 48BF19: variable 'v8' is possibly undefined
// 48BF80: variable 'v13' is possibly undefined
// 48BF85: variable 'v14' is possibly undefined
// 48BF88: variable 'v15' is possibly undefined

//----- (0048BF90) --------------------------------------------------------
_DWORD * Rules_GetFactListFunction(int returnValue, double a2)
{
  int numArgs; // eax
  int v4; // ecx
  int v6; // ecx
  int v7; // ecx
  _DWORD v8[6]; // [esp-4h] [ebp-24h] BYREF
  /* stack alias of v8[2]: the DATA_OBJECT value slot */
  int v11 CLASH95_UNUSED; // [esp+18h] [ebp-8h]

  v11 = returnValue;
  numArgs = Lexer_TokenExpect((int)(intptr_t)aGetFactList, 2, 1);
  if ( numArgs == -1 )
    return Rules_SetMultifieldErrorValue(v4);
  if ( numArgs == 1 )
  {
    Rules_RtnUnknown(1, v8, a2);
    if ( v8[1] != 2 || !Module_FindByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)((uintptr_t)(unsigned int)v8[2] + 16)) && strcmp_(v7, *(_DWORD *)(uintptr_t)((uintptr_t)(unsigned int)v8[2] + 16)) )
    {
      Rules_SetMultifieldErrorValue(v6);
      return (_DWORD *)(uintptr_t)Parser_ReportError(1, (int)(intptr_t)aDefmoduleNam_1);
    }
  }
  else
  {
    Module_GetCurrent();
  }
  return (_DWORD *)(uintptr_t)Rules_BuildFactAddressList();
}
// 48BFCD: variable 'v4' is possibly undefined
// 48BFFE: variable 'v7' is possibly undefined
// 48C013: variable 'v6' is possibly undefined
// 48C01D: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0048C030) --------------------------------------------------------
int Rules_BuildFactAddressList(void)
{
  int v0; // edx
  int theModule; // esi
  int theFact; // eax
  _DWORD *v3; // ecx
  signed int i; // edx
  int v5; // edx
  _DWORD *theList; // eax
  int v7; // ecx
  int m; // eax
  int v9; // edx
  int v10; // edx
  int j; // eax
  int v12; // edx
  int k; // eax
  int v14; // edx
  int v15; // edx

  Module_BeginEnum();
  theModule = v0;
  if ( v0 )
  {
    Module_SetCurrent(v0);
    Lexer_MarkImpliedTemplates();
    theFact = Rules_GetNextFactInModule(0);
    for ( i = 0; theFact; i = v5 + 1 )
      theFact = Rules_GetNextFactInModule(theFact);
  }
  else
  {
    for ( j = Rules_GetNextFact(0); j; i = v12 + 1 )
      j = Rules_GetNextFact(j);
  }
  v3[1] = 4;
  v3[4] = i - 1;
  v3[3] = 0;
  theList = Rules_CreateEphemeralMultifield(i);
  *(_DWORD *)(uintptr_t)(v7 + 8) = theList;
  if ( theModule )
  {
    for ( k = Rules_GetNextFactInModule(0); k; v14 = v15 + 6 )
    {
      *(_WORD *)(uintptr_t)(v14 + 14) = 6;
      *(_DWORD *)(uintptr_t)(v14 + 16) = k;
      k = Rules_GetNextFactInModule(k);
    }
  }
  else
  {
    for ( m = Rules_GetNextFact(0); m; v9 = v10 + 6 )
    {
      *(_WORD *)(uintptr_t)(v9 + 14) = 6;
      *(_DWORD *)(uintptr_t)(v9 + 16) = m;
      m = Rules_GetNextFact(m);
    }
  }
  Module_EndEnum();
  return Lexer_MarkImpliedTemplates();
}
// 48C039: variable 'v0' is possibly undefined
// 48C061: variable 'v5' is possibly undefined
// 48C073: variable 'v3' is possibly undefined
// 48C070: variable 'i' is possibly undefined
// 48C08D: variable 'v7' is possibly undefined
// 48C09F: variable 'v9' is possibly undefined
// 48C0AD: variable 'v10' is possibly undefined
// 48C0DD: variable 'v12' is possibly undefined
// 48C0EF: variable 'v14' is possibly undefined
// 48C0FD: variable 'v15' is possibly undefined

//----- (0048C120) --------------------------------------------------------
int  Rules_ResolveFactArgument(int argumentPosition, int theFunction, int noFactError, double a4)
{
  int v4; // ecx
  int result; // eax
  int factIndex; // edx
  int v7; // ecx
  _DWORD v8[6]; // [esp-4h] [ebp-34h] BYREF
  /* stack alias of v8[1] */
  /* stack alias of v8[2]: the DATA_OBJECT value slot */
  _BYTE tempBuffer[24]; // [esp+14h] [ebp-1Ch] BYREF
  int v12 CLASH95_UNUSED; // [esp+2Ch] [ebp-4h]

  v12 = theFunction;
  Rules_RtnUnknown(argumentPosition, v8, a4);
  if ( v8[1] == 6 )
  {
    result = v8[2];
    if ( *(char *)(uintptr_t)(v8[2] + 29) < 0 )
      return 0;
  }
  else if ( v8[1] == 1 && *(int *)(uintptr_t)(v8[2] + 16) >= 0 )
  {
    factIndex = *(int *)(uintptr_t)(v8[2] + 16);
    result = Rules_FindFactByIndex(factIndex);
    if ( !result && noFactError )
    {
      sprintf_(tempBuffer, "f-%ld", factIndex);
      Rules_ReportCantFindItem(v7, (int)(intptr_t)tempBuffer);
      return 0;
    }
  }
  else
  {
    Parser_ReportError(v4, (int)(intptr_t)aFactAddressOrF);
    return 0;
  }
  return result;
}
// 48C17F: variable 'v4' is possibly undefined
// 48C197: variable 'v6' is possibly undefined
// 48C1A8: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (0048C1C0) --------------------------------------------------------
signed int Rules_RegisterFactPatternNetworkPersistence(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aFacts_3,
           0,
           0,
           (int)(intptr_t)Rules_FactPatternNetworkBsaveFind,
           (int)(intptr_t)Rules_FactPatternNetworkWriteHeader,
           (int)(intptr_t)Rules_FactPatternNetworkBsaveStorage,
           (int)(intptr_t)Rules_FactPatternNetworkBloadStorage,
           (int)(intptr_t)Rules_FactPatternNetworkBload,
           (int)(intptr_t)Rules_FactPatternNetworkClearBloaded);
}

//----- (0048C200) --------------------------------------------------------
int Rules_FactPatternNetworkBsaveFind(void)
{
  int result; // eax
  int i; // esi
  int j; // ecx
  int v3; // ecx

  if ( Rules_IsBloaded() )
    Rules_ConstructQueuePush(g_FactPatternNodeCount);
  g_FactPatternNodeCount = 0;
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(v3) )
      Rules_FactPatternNetworkAssignNodeIds(0, 0, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 32));
    result = Module_NextEnum(i);
  }
  return result;
}
// 48C251: variable 'v3' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C270) --------------------------------------------------------
const void * Rules_FactPatternNetworkAssignNodeIds(const void *result, int theFile, _DWORD *thePattern)
{
  const void *v3; // ecx

  v3 = result;
  if ( thePattern )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        if ( v3 )
        {
          if ( v3 == (const void *)1 )
            result = Rules_FactPatternNetworkWriteNodeRecord((int)(intptr_t)thePattern, theFile);
        }
        else
        {
          result = (const void *)(uintptr_t)g_FactPatternNodeCount++;
          thePattern[4] = result;
        }
        if ( !thePattern[7] )
          break;
        thePattern = (_DWORD *)(uintptr_t)thePattern[7];
      }
      while ( !thePattern[10] )
      {
        thePattern = (_DWORD *)(uintptr_t)thePattern[8];
        if ( !thePattern )
          return result;
      }
      thePattern = (_DWORD *)(uintptr_t)thePattern[10];
    }
  }
  return result;
}
// 48C27D: variable 'v3' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C2D0) --------------------------------------------------------
const void * Rules_FactPatternNetworkWriteHeader(int theFile, int a2)
{
  int v2; // ecx
  _DWORD space[4]; // [esp+0h] [ebp-10h] BYREF

  space[2] = a2;
  space[0] = 4;
  Rules_BsaveWriteBlock(4, theFile, space);
  return Rules_BsaveWriteBlock(4, v2, &g_FactPatternNodeCount);
}
// 48C2F5: variable 'v2' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C310) --------------------------------------------------------
int  Rules_FactPatternNetworkBsaveStorage(int theFile)
{
  int i; // edi
  int j; // ecx
  int v4; // ecx
  int result; // eax
  int space[7]; // [esp+0h] [ebp-1Ch] BYREF

  space[0] = 32 * g_FactPatternNodeCount;
  Rules_BsaveWriteBlock(4, theFile, space);
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(v4) )
      Rules_FactPatternNetworkAssignNodeIds((const void *)1, theFile, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 32));
  }
  result = Rules_IsBloaded();
  if ( result )
    return Rules_ConstructQueuePop(&g_FactPatternNodeCount);
  return result;
}
// 48C368: variable 'v4' is possibly undefined
// 54E520: using guessed type int dword_54E520;

//----- (0048C3B0) --------------------------------------------------------
const void * Rules_FactPatternNetworkWriteNodeRecord(int thePattern, int theFile)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  _DWORD *v7; // ecx
  int nextLevelPtr; // ebp
  int v9; // eax
  int lastLevelPtr; // eax
  int v11; // eax
  int leftNodePtr; // edx
  int v13; // eax
  int rightNodePtr; // esi
  int v15; // eax
  _BYTE tempNode[8]; // [esp+0h] [ebp-34h] BYREF
  int packedFields; // [esp+8h] [ebp-2Ch]
  signed int networkTestIndex CLASH95_UNUSED; // [esp+Ch] [ebp-28h]
  int nextLevelIndex CLASH95_UNUSED; // [esp+10h] [ebp-24h]
  int lastLevelIndex CLASH95_UNUSED; // [esp+14h] [ebp-20h]
  int leftNodeIndex CLASH95_UNUSED; // [esp+18h] [ebp-1Ch]
  int rightNodeIndex CLASH95_UNUSED; // [esp+1Ch] [ebp-18h]

  Rules_BsavePackSharedRecordHeader((int)(intptr_t)tempNode, thePattern);
  v4 = *(_DWORD *)(uintptr_t)(v3 + 20);
  BYTE1(packedFields) = 0;
  packedFields |= (unsigned __int8)v4 << 8;
  v5 = *(_DWORD *)(uintptr_t)(v3 + 20);
  BYTE2(packedFields) = 0;
  packedFields |= v5 & 0xFF0000;
  v6 = *(_DWORD *)(uintptr_t)(v3 + 20) << 16;
  LOBYTE(packedFields) = 0;
  packedFields |= HIBYTE(v6);
  networkTestIndex = AST_GetHashedNodeIndex((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v3 + 24));
  nextLevelPtr = v7[7];
  if ( nextLevelPtr )
    v9 = *(_DWORD *)(uintptr_t)(nextLevelPtr + 16);
  else
    v9 = -1;
  nextLevelIndex = v9;
  lastLevelPtr = v7[8];
  if ( lastLevelPtr )
    v11 = *(_DWORD *)(uintptr_t)(lastLevelPtr + 16);
  else
    v11 = -1;
  lastLevelIndex = v11;
  leftNodePtr = v7[9];
  if ( leftNodePtr )
    v13 = *(_DWORD *)(uintptr_t)(leftNodePtr + 16);
  else
    v13 = -1;
  leftNodeIndex = v13;
  rightNodePtr = v7[10];
  if ( rightNodePtr )
    v15 = *(_DWORD *)(uintptr_t)(rightNodePtr + 16);
  else
    v15 = -1;
  rightNodeIndex = v15;
  return Rules_BsaveWriteBlock(32, theFile, tempNode);
}
// 48C3C7: variable 'v3' is possibly undefined
// 48C41A: variable 'v7' is possibly undefined

//----- (0048C490) --------------------------------------------------------
int Rules_FactPatternNetworkBloadStorage(void)
{
  int result; // eax
  int space; // [esp+0h] [ebp-8h] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  result = Rules_BloadReadBlock((uintptr_t)&g_FactPatternNodeCount, 4u);
  if ( g_FactPatternNodeCount )
  {
    space = 44 * g_FactPatternNodeCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(44 * g_FactPatternNodeCount));
    g_ClipsFactPatternNodeBloadArray = result;
  }
  else
  {
    g_ClipsFactPatternNodeBloadArray = 0;
  }
  return result;
}
// 54E51C: using guessed type int dword_54E51C;
// 54E520: using guessed type int dword_54E520;

//----- (0048C4E0) --------------------------------------------------------
signed int Rules_FactPatternNetworkBload(void)
{
  int space; // [esp-8h] [ebp-Ch] BYREF

  Rules_BloadReadBlock((uintptr_t)&space, 4u);
  return Rules_BloadAndRefresh(g_FactPatternNodeCount, 32, (void (__fastcall *)(signed int, signed int))Rules_FactPatternNetworkFixupNodeRecord);
}
// 54E520: using guessed type int dword_54E520;

//----- (0048C510) --------------------------------------------------------
int  Rules_FactPatternNetworkFixupNodeRecord(int *bsaveNode, int nodeIndex)
{
  int record_offset;
  int record;
  unsigned int flags;
  int relation_index;
  int previous_index;
  int next_index;
  int parent_index;
  int child_index;
  int result;

  record_offset = 44 * nodeIndex;
  record = g_ClipsFactPatternNodeBloadArray + record_offset;
  Rules_BloadUnpackSharedRecordHeader(record, bsaveNode);
  *(_DWORD *)(uintptr_t)(record + 16) = 0;

  flags = (unsigned int)bsaveNode[2];
  *(_BYTE *)(uintptr_t)(record + 20) = 0;
  *(_DWORD *)(uintptr_t)(record + 20) |= (flags >> 8) & 0xFF;
  *(_BYTE *)(uintptr_t)(record + 22) = 0;
  *(_DWORD *)(uintptr_t)(record + 20) |= flags & 0xFF0000;
  *(_BYTE *)(uintptr_t)(record + 21) = 0;
  *(_DWORD *)(uintptr_t)(record + 20) |= (flags & 0xFF) << 8;

  relation_index = bsaveNode[3];
  *(_DWORD *)(uintptr_t)(record + 24) = relation_index == -1 ? 0 : g_ClipsPackedExpressionArray + 14 * relation_index;

  previous_index = bsaveNode[7];
  *(_DWORD *)(uintptr_t)(record + 40) = previous_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * previous_index;

  next_index = bsaveNode[4];
  *(_DWORD *)(uintptr_t)(record + 28) = next_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * next_index;

  parent_index = bsaveNode[5];
  *(_DWORD *)(uintptr_t)(record + 32) = parent_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * parent_index;

  child_index = bsaveNode[6];
  result = child_index == -1 ? 0 : g_ClipsFactPatternNodeBloadArray + 44 * child_index;
  *(_DWORD *)(uintptr_t)(record + 36) = result;
  return result;
}
// 54E51C: using guessed type int dword_54E51C;
// 54E688: using guessed type int dword_54E688;

//----- (0048C670) --------------------------------------------------------
signed int Rules_FactPatternNetworkClearBloaded(void)
{
  signed int result; // eax

  if ( 44 * g_FactPatternNodeCount )
    return Mem_ReleasePoolBlock(g_ClipsFactPatternNodeBloadArray, 44 * g_FactPatternNodeCount);
  return result;
}
// 54E51C: using guessed type int dword_54E51C;
// 54E520: using guessed type int dword_54E520;

//----- (0048C690) --------------------------------------------------------
int Rules_RegisterFactPatternNetworkCodeGen(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aFacts_4, 0, 0, (int)(intptr_t)Rules_FactPatternNetworkAssignCodeGenIds, (int)(intptr_t)Rules_FactPatternNetworkToCode, 1);
  g_ClipsFactPatternNetworkCodeGenItem = result;
  return result;
}
// 54E524: using guessed type int dword_54E524;

//----- (0048C6C0) --------------------------------------------------------
int Rules_FactPatternNetworkAssignCodeGenIds(void)
{
  int result; // eax
  int deftemplateIndex; // esi
  int i; // edi
  int nodeIndex; // ecx
  int j; // ebx
  _DWORD *thePattern; // eax
  int v6; // ecx

  result = Module_NextEnum(0);
  deftemplateIndex = 0;
  for ( i = result; result; i = result )
  {
    Module_SetCurrent(i);
    for ( j = Rules_GetNextDeftemplate(0); j; j = Rules_GetNextDeftemplate(j) )
    {
      thePattern = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 32);
      for ( *(_DWORD *)(uintptr_t)(j + 12) = deftemplateIndex++; thePattern; nodeIndex = v6 + 1 )
      {
        thePattern[4] = nodeIndex;
        thePattern = Rules_FactPatternNetworkNextNode(thePattern);
      }
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 48C6F7: variable 'v3' is possibly undefined
// 48C6FF: variable 'v6' is possibly undefined

//----- (0048C730) --------------------------------------------------------
_DWORD * Rules_FactPatternNetworkNextNode(_DWORD *result)
{
  if ( result[7] )
    return (_DWORD *)(uintptr_t)result[7];
  while ( !result[10] )
  {
    result = (_DWORD *)(uintptr_t)result[8];
    if ( !result )
      return result;
  }
  return (_DWORD *)(uintptr_t)result[10];
}

//----- (0048C760) --------------------------------------------------------
int  Rules_FactPatternNetworkToCode(const char *fileName, const char *fileID, int imageID, int headerFP, int maxIndices)
{
  int fileVersion; // esi
  int v6; // ecx
  _DWORD *thePattern; // edi
  int v8; // eax
  int v9; // ecx
  int theFile; // esi
  int v12; // [esp+0h] [ebp-30h] BYREF
  int itemCount; // [esp+4h] [ebp-2Ch] BYREF
  int v14; // [esp+8h] [ebp-28h] BYREF
  int Enum; // [esp+Ch] [ebp-24h]
  int theDeftemplate; // [esp+10h] [ebp-20h]
  const char *v17; // [esp+14h] [ebp-1Ch]
  const char *v18; // [esp+18h] [ebp-18h]
  int v19; // [esp+1Ch] [ebp-14h]
  int v20; // [esp+20h] [ebp-10h]

  v18 = fileName;
  v17 = fileID;
  v19 = headerFP;
  v20 = imageID;
  itemCount = 0;
  v14 = 1;
  Output_WriteFormatted(0, 1, headerFP, (int)(intptr_t)aIncludeFactbld, 1);
  fileVersion = 0;
  Enum = Module_NextEnum(0);
  if ( Enum )
  {
    while ( 1 )
    {
      Module_SetCurrent(Enum);
      theDeftemplate = Rules_GetNextDeftemplate(0);
      if ( theDeftemplate )
        break;
LABEL_7:
      Enum = Module_NextEnum(Enum);
      if ( !Enum )
        goto LABEL_8;
    }
    while ( 1 )
    {
      thePattern = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDeftemplate + 32);
      if ( thePattern )
        break;
LABEL_6:
      theDeftemplate = Rules_GetNextDeftemplate(theDeftemplate);
      if ( !theDeftemplate )
        goto LABEL_7;
    }
    while ( 1 )
    {
      v8 = Rules_ConstructCodeFileOpen(
             fileVersion,
             v18,
             v20,
             v17,
             &v12,
             v14,
             v19,
             (char)(intptr_t)aStructFactpatt,
             **(const char ***)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20),
             0,
             0);
      theFile = v8;
      if ( !v8 )
        break;
      Rules_FactPatternNetworkNodeToCode(v8, (int)(intptr_t)thePattern, maxIndices, v20);
      ++itemCount;
      fileVersion = Rules_ConstructCodeFileClose(theFile, &itemCount, maxIndices, &v14, 0, 0);
      thePattern = Rules_FactPatternNetworkNextNode(thePattern);
      if ( !thePattern )
        goto LABEL_6;
    }
    Rules_FactPatternNetworkToCodeClose(0, maxIndices, v9);
    return 0;
  }
  else
  {
LABEL_8:
    Rules_FactPatternNetworkToCodeClose(fileVersion, maxIndices, v6);
    return 1;
  }
}
// 48C885: variable 'v6' is possibly undefined
// 48C89A: variable 'v9' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048C8B0) --------------------------------------------------------
int  Rules_FactPatternNetworkToCodeClose(int result, int maxIndices, int imageID)
{
  int v3; // [esp+0h] [ebp-Ch] BYREF
  _DWORD v4[2]; // [esp+4h] [ebp-8h] BYREF

  v4[1] = imageID;
  v3 = maxIndices;
  v4[0] = 0;
  if ( result )
    return Rules_ConstructCodeFileClose(result, &v3, maxIndices, v4, 0, 0);
  return result;
}

//----- (0048C8E0) --------------------------------------------------------
int  Rules_FactPatternNetworkNodeToCode(int theFile, int thePattern, int maxIndices, char imageID)
{
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  int v18; // ecx
  int v20; // [esp+0h] [ebp-10h]

  Output_WriteFormatted(maxIndices, thePattern, theFile, (int)(intptr_t)asc_504530, imageID);
  Rules_PrintPatternNetworkNodeTrace(theFile, v7, v8);
  Output_WriteFormatted(maxIndices, v9, theFile, (int)(intptr_t)a0DDD, *(_DWORD *)(uintptr_t)(thePattern + 20));
  Rules_WriteExpressionRefToCode(theFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(thePattern + 24), v10, v20);
  v12 = *(_DWORD *)(uintptr_t)(thePattern + 28);
  if ( v12 )
    Output_WriteFormatted(v20, *(_DWORD *)(uintptr_t)(v12 + 16) % maxIndices, theFile, (int)(intptr_t)aSD_LdLd_1, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v11, 0, theFile, (int)(intptr_t)aNull_14, v20);
  if ( *(_DWORD *)(uintptr_t)(thePattern + 32) )
    Output_WriteFormatted(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20), v20, theFile, (int)(intptr_t)aSD_LdLd_2, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v14, v13, theFile, (int)(intptr_t)aNull_12, v20);
  if ( *(_DWORD *)(uintptr_t)(thePattern + 36) )
    Output_WriteFormatted(v16, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20), theFile, (int)(intptr_t)aSD_LdLd_2, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    Output_WriteFormatted(v16, v15, theFile, (int)(intptr_t)aNull_12, v20);
  v18 = *(_DWORD *)(uintptr_t)(thePattern + 40);
  if ( v18 )
    return Output_WriteFormatted(v18, *(_DWORD *)(uintptr_t)(v18 + 16) % maxIndices, theFile, (int)(intptr_t)aSD_LdLd_3, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(0, v17, theFile, (int)(intptr_t)aNull_13, v20);
}
// 48C8FF: variable 'v7' is possibly undefined
// 48C8FF: variable 'v8' is possibly undefined
// 48C929: variable 'v9' is possibly undefined
// 48C939: variable 'v10' is possibly undefined
// 48C939: variable 'v20' is possibly undefined
// 48C98D: variable 'v14' is possibly undefined
// 48C98D: variable 'v13' is possibly undefined
// 48C9A6: variable 'v16' is possibly undefined
// 48C9A6: variable 'v15' is possibly undefined
// 48C9BF: variable 'v17' is possibly undefined
// 48C9D4: variable 'v11' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048CAA0) --------------------------------------------------------
int  Rules_FactPatternNetworkWriteNodeRefToCode(int thePattern, int theFile, int imageID)
{
  char v4; // [esp+0h] [ebp-8h]

  if ( thePattern )
    return Output_WriteFormatted(imageID, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20), theFile, (int)(intptr_t)aSD_LdLd_4, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsFactPatternNetworkCodeGenItem + 20));
  else
    return Output_WriteFormatted(imageID, theFile, theFile, (int)(intptr_t)aNull_16, v4);
}
// 48CAB0: variable 'v4' is possibly undefined
// 54E524: using guessed type int dword_54E524;

//----- (0048CAF0) --------------------------------------------------------
_DWORD * Rules_CreateMultifield(signed int size)
{
  signed int originalSize; // ecx
  signed int adjustedSize; // edx
  int bucketAddress; // eax
  _DWORD *result; // eax
  __int16 evaluationDepth; // dx

  originalSize = size;
  adjustedSize = size;
  if ( size <= 0 )
    adjustedSize = 1;
  if ( (unsigned int)(6 * (adjustedSize - 1) + 20) < 0x1F4 && *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24 * (adjustedSize - 1) + 80) )
  {
    bucketAddress = g_ClipsMemoryTable + 24 * (adjustedSize - 1);
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(bucketAddress + 80);
    *(_DWORD *)(uintptr_t)(bucketAddress + 80) = *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (adjustedSize - 1) + 20);
  }
  *(_DWORD *)((char *)result + 6) = originalSize;
  evaluationDepth = g_ClipsCurrentEvaluationDepth;
  *result = 0;
  *(_DWORD *)((char *)result + 10) = 0;
  *((_WORD *)result + 2) = evaluationDepth;
  return result;
}
// 48CB51: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048CB90) --------------------------------------------------------
_DWORD * Rules_ReturnMultifieldToPool(_DWORD *result)
{
  int fieldCount; // edx
  unsigned int byteSize; // edx

  if ( result )
  {
    fieldCount = *(_DWORD *)((char *)result + 6);
    if ( !fieldCount )
      fieldCount = 1;
    byteSize = 6 * (fieldCount - 1) + 20;
    g_ClipsMemPoolReturnBucketIndex = byteSize;
    if ( byteSize >= 0x1F4 )
    {
      return (_DWORD *)(uintptr_t)Mem_SmallBlockRelease(result, byteSize);
    }
    else
    {
      g_ClipsMemFreeListTemp = (int)(intptr_t)result;
      *result = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 4 * byteSize);
      result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(4 * g_ClipsMemPoolReturnBucketIndex + g_ClipsMemoryTable) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0048CC00) --------------------------------------------------------
__int16 * Rules_InstallMultifield(__int16 *result)
{
  unsigned char *multifield;
  unsigned char *field;
  int count;
  int index;

  if ( result )
  {
    multifield = (unsigned char *)(uintptr_t)(unsigned int)(uintptr_t)result;
    count = *(_DWORD *)(multifield + 6);
    ++*(_DWORD *)multifield;
    if ( count > 0 )
    {
      field = multifield + 14;
      for ( index = 0; index < count; ++index )
      {
        Rules_AtomInstall(*(__int16 *)field, *(_DWORD *)(field + 2), (int)(uintptr_t)field);
        field += 6;
      }
    }
  }
  return result;
}

//----- (0048CC40) --------------------------------------------------------
__int16 * Rules_DeinstallMultifield(__int16 *result)
{
  unsigned char *multifield;
  unsigned char *field;
  int count;
  int index;

  if ( result )
  {
    multifield = (unsigned char *)(uintptr_t)(unsigned int)(uintptr_t)result;
    count = *(_DWORD *)(multifield + 6);
    --*(_DWORD *)multifield;
    if ( count > 0 )
    {
      field = multifield + 14;
      for ( index = 0; index < count; ++index )
      {
        Rules_AtomDeinstall(*(__int16 *)field, (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(field + 2), (int)(uintptr_t)field);
        field += 6;
      }
    }
  }
  return result;
}

//----- (0048CC80) --------------------------------------------------------
_DWORD * Rules_CreateMultifieldFromString(const char *theString)
{
  int topNode; // esi
  int v2; // ecx
  signed int lastNode; // edi
  signed int *theValue; // edx
  __int16 valueType; // ax
  signed int newNode; // eax
  _DWORD *theMultifield; // ebx
  char *fieldPtr; // edx
  int fieldIndex; // ecx
  int i; // eax
  int token_buffer_ptr;
  _DWORD *token_buffer;
  int node_count;

  token_buffer_ptr = Compat_AllocLow32Bytes(12);
  if ( !token_buffer_ptr )
    return 0;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  IO_OpenStringSource((int)(intptr_t)aMultifieldStr, theString, 0);
  topNode = 0;
  Parser_NextToken((int)(intptr_t)aMultifieldStr, token_buffer_ptr);
  lastNode = 0;
  node_count = 0;
  while ( token_buffer[0] != 102 )
  {
    if ( token_buffer[0] == 2 || token_buffer[0] == 3 || token_buffer[0] < 2u || token_buffer[0] == 8 )
    {
      theValue = (signed int *)(uintptr_t)(unsigned int)token_buffer[1];
      valueType = token_buffer[0];
    }
    else
    {
      theValue = Str_Intern((char *)(uintptr_t)(unsigned int)token_buffer[2], v2);
      valueType = 3;
    }
    newNode = AST_NewNode(valueType, (int)(intptr_t)theValue);
    ++node_count;
    if ( topNode )
      *(_DWORD *)(uintptr_t)(lastNode + 10) = newNode;
    else
      topNode = newNode;
    lastNode = newNode;
    Parser_NextToken((int)(intptr_t)aMultifieldStr, token_buffer_ptr);
  }
  IO_CloseStringRouter((int)(intptr_t)aMultifieldStr);
  theMultifield = Rules_CreateEphemeralMultifield(node_count);
  fieldPtr = (char *)theMultifield + 14;
  fieldIndex = 0;
  for ( i = topNode; i; ++fieldIndex )
  {
    *(_WORD *)fieldPtr = *(_WORD *)(uintptr_t)i;
    *(_DWORD *)(fieldPtr + 2) = *(_DWORD *)(uintptr_t)(i + 2);
    fieldPtr += 6;
    i = *(_DWORD *)(uintptr_t)(i + 10);
  }
  AST_Free(topNode);
  Compat_FreeLow32Bytes(token_buffer_ptr);
  return theMultifield;
}
// 48CD3A: simplified comparisons for '%var_24.4': ==0 || ==1 became <2u
// 48CD52: variable 'v2' is possibly undefined

//----- (0048CD70) --------------------------------------------------------
_DWORD * Rules_CreateEphemeralMultifield(signed int size)
{
  signed int originalSize; // ecx
  signed int adjustedSize; // edx
  int bucketAddress; // eax
  _DWORD *result; // eax
  __int16 evaluationDepth; // bx

  originalSize = size;
  if ( size <= 0 )
    adjustedSize = 1;
  else
    adjustedSize = size;
  if ( (unsigned int)(6 * (adjustedSize - 1) + 20) < 0x1F4 && *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24 * (adjustedSize - 1) + 80) )
  {
    bucketAddress = 24 * (adjustedSize - 1) + g_ClipsMemoryTable;
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(bucketAddress + 80);
    *(_DWORD *)(uintptr_t)(bucketAddress + 80) = *(_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (adjustedSize - 1) + 20);
  }
  *(_DWORD *)((char *)result + 6) = originalSize;
  evaluationDepth = g_ClipsCurrentEvaluationDepth;
  *result = 0;
  *(_DWORD *)((char *)result + 10) = 0;
  *((_WORD *)result + 2) = evaluationDepth;
  *(_DWORD *)((char *)result + 10) = g_ClipsEphemeralMultifieldListHead;
  g_ClipsEphemeralMultifieldListHead = (int)(intptr_t)result;
  ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += 6 * adjustedSize + 20;
  return result;
}
// 48CDE6: variable 'v1' is possibly undefined
// 48CE21: variable 'v2' is possibly undefined
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A950: using guessed type int dword_51A950;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048CE70) --------------------------------------------------------
_DWORD * Rules_MaterializeMultifieldRange(_DWORD *theValue)
{
  _DWORD *theCopy; // ebx
  int v3; // edx

  if ( theValue[1] != 4 )
    return 0;
  theCopy = Rules_CreateMultifield(theValue[4] - theValue[3] + 1);
  qmemcpy(
    (char *)theCopy + 14,
    (const void *)(uintptr_t)(6 * *(_DWORD *)(uintptr_t)(v3 + 12) + *(_DWORD *)(uintptr_t)(v3 + 8) + 14),
    6 * *(_DWORD *)((char *)theCopy + 6));
  return theCopy;
}
// 48CE95: variable 'v3' is possibly undefined

//----- (0048CED0) --------------------------------------------------------
int  Rules_RegisterEphemeralMultifield(int theSegment)
{
  int result; // eax

  *(_WORD *)(uintptr_t)(theSegment + 4) = g_ClipsCurrentEvaluationDepth;
  *(_DWORD *)(uintptr_t)(theSegment + 10) = g_ClipsEphemeralMultifieldListHead;
  g_ClipsEphemeralMultifieldListHead = theSegment;
  ++g_ClipsEphemeralItemCount;
  result = 6 * *(_DWORD *)(uintptr_t)(theSegment + 6) + 20;
  g_ClipsEphemeralItemBytes += result;
  return result;
}
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A950: using guessed type int dword_51A950;
// 51A96C: using guessed type int dword_51A96C;

//----- (0048CF20) --------------------------------------------------------
int Rules_FreeUnusedEphemeralMultifields(void)
{
  int result; // eax
  int lastSegment; // ebx
  int nextSegment; // ecx
  int fieldCount; // edx
  unsigned int byteSize; // edx

  result = g_ClipsEphemeralMultifieldListHead;
  lastSegment = 0;
  if ( g_ClipsEphemeralMultifieldListHead )
  {
    do
    {
      while ( 1 )
      {
        nextSegment = *(_DWORD *)(uintptr_t)(result + 10);
        if ( *(__int16 *)(uintptr_t)(result + 4) <= g_ClipsCurrentEvaluationDepth || *(_DWORD *)(uintptr_t)result )
          break;
        --g_ClipsEphemeralItemCount;
        g_ClipsEphemeralItemBytes -= 6 * *(_DWORD *)(uintptr_t)(result + 6) + 20;
        if ( *(_DWORD *)(uintptr_t)(result + 6) )
          fieldCount = *(_DWORD *)(uintptr_t)(result + 6);
        else
          fieldCount = 1;
        byteSize = 6 * (fieldCount - 1) + 20;
        g_ClipsMemPoolReturnBucketIndex = byteSize;
        if ( byteSize >= 0x1F4 )
        {
          Mem_SmallBlockRelease((_DWORD *)(uintptr_t)result, byteSize);
        }
        else
        {
          g_ClipsMemFreeListTemp = result;
          *(_DWORD *)(uintptr_t)result = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 4 * byteSize);
          *(_DWORD *)(uintptr_t)(4 * g_ClipsMemPoolReturnBucketIndex + g_ClipsMemoryTable) = g_ClipsMemFreeListTemp;
        }
        if ( lastSegment )
        {
          *(_DWORD *)(uintptr_t)(lastSegment + 10) = nextSegment;
          result = nextSegment;
          if ( !nextSegment )
            return result;
        }
        else
        {
          g_ClipsEphemeralMultifieldListHead = nextSegment;
          result = nextSegment;
          if ( !nextSegment )
            return result;
        }
      }
      lastSegment = result;
      result = *(_DWORD *)(uintptr_t)(result + 10);
    }
    while ( nextSegment );
  }
  return result;
}
// 48CFBE: variable 'v2' is possibly undefined
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A950: using guessed type int dword_51A950;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0048D010) --------------------------------------------------------
int  Rules_AssignMultifieldRangeCopy(_DWORD *dst, int src)
{
  int rangeSize; // eax
  _DWORD *theCopy; // eax
  int v5; // ecx
  int fieldCount; // ebx
  int v7; // edx
  int result; // eax

  dst[1] = 4;
  dst[3] = 0;
  rangeSize = *(_DWORD *)(uintptr_t)(src + 16) - *(_DWORD *)(uintptr_t)(src + 12);
  dst[4] = rangeSize;
  theCopy = Rules_CreateMultifield(rangeSize + 1);
  fieldCount = *(_DWORD *)(uintptr_t)(v5 + 16) + 1;
  *(_DWORD *)(uintptr_t)(v5 + 8) = theCopy;
  result = 6 * fieldCount;
  qmemcpy(
    (void *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 8) + 14),
    (const void *)(uintptr_t)(6 * *(_DWORD *)(uintptr_t)(v7 + 12) + *(_DWORD *)(uintptr_t)(v7 + 8) + 14),
    6 * fieldCount);
  return result;
}
// 48D035: variable 'v5' is possibly undefined
// 48D048: variable 'v7' is possibly undefined

//----- (0048D080) --------------------------------------------------------
_DWORD * Rules_CloneMultifield(int theMultifield)
{
  _DWORD *theCopy; // ebx
  int v2; // edx

  theCopy = Rules_CreateMultifield(*(_DWORD *)(uintptr_t)(theMultifield + 6));
  qmemcpy((char *)theCopy + 14, (const void *)(uintptr_t)(v2 + 14), 6 * *(_DWORD *)(uintptr_t)(v2 + 6));
  return theCopy;
}
// 48D09B: variable 'v2' is possibly undefined

//----- (0048D0C0) --------------------------------------------------------
int  Rules_PrintMultifieldRange(int result, int theSegment, int end, int begin, int printParens)
{
  int logicalName; // esi
  int fieldsBase; // edi
  int fieldIndex; // ecx
  __int16 *fieldPtr; // edi

  logicalName = result;
  fieldsBase = theSegment + 14;
  if ( printParens )
    result = Output_Write(result, (int)(intptr_t)asc_5045B8, end);
  fieldIndex = begin;
  if ( begin <= end )
  {
    fieldPtr = (__int16 *)(uintptr_t)(6 * begin + fieldsBase);
    do
    {
      /* 64-bit host repair (save-facts path): the field value cell is a
         32-bit low32-arena pointer (8-byte load faulted), and the loop
         counter lived in ecx across the call ('v10' == fieldIndex in the
         original 0x48D0C0), so advance fieldIndex directly. */
      result = Rules_PrintAtomValue(logicalName, *fieldPtr, (int *)(uintptr_t)*(_DWORD *)(fieldPtr + 1));
      ++fieldIndex;
      fieldPtr += 3;
      if ( fieldIndex <= end )
        result = Output_Write(logicalName, (int)(intptr_t)asc_5045BC, fieldIndex);
    }
    while ( fieldIndex <= end );
  }
  if ( printParens )
    return Output_Write(logicalName, (int)(intptr_t)asc_5045C0, fieldIndex);
  return result;
}
// 48D0F1: variable 'v10' is possibly undefined
// 48D107: variable 'v8' is possibly undefined

//----- (0048D140) --------------------------------------------------------
_DWORD * Rules_StoreEvaluatedNodesAsMultifield(_DWORD *returnValue, int expressionList, int garbageSegment, double a4)
{
  EvalResultBuffer *out;
  EvalResultBuffer parsed;
  EvalMultifieldEntry *entries;
  EvalMultifieldEntry *entry;
  _DWORD *entries_raw;
  _DWORD *multifield_raw;
  unsigned char *multifield;
  unsigned char *source_multifield;
  int node_count;
  int node;
  int output_count;
  int entry_index;
  int source_index;
  int destination_index;
  int source_offset;
  int destination_offset;
  int allocation_size;

  out = (EvalResultBuffer *)returnValue;
  node_count = AST_CountListNodes(expressionList);
  if ( !node_count )
  {
    out->type = 4;
    out->begin = 0;
    out->end = -1;
    multifield_raw = garbageSegment ? Rules_CreateEphemeralMultifield(0) : Rules_CreateMultifield(0);
    out->value = (int)(uintptr_t)multifield_raw;
    return multifield_raw;
  }

  allocation_size = sizeof(*entries) * node_count;
  entries_raw = Mem_NewArray(allocation_size);
  entries = (EvalMultifieldEntry *)(uintptr_t)(unsigned int)(uintptr_t)entries_raw;
  output_count = 0;
  node = expressionList;
  for ( entry_index = 0; entry_index < node_count; ++entry_index )
  {
    memset(&parsed, 0, sizeof(parsed));
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)node, (_DWORD *)&parsed, node, a4);
    if ( g_ClipsEvaluationError )
    {
      out->type = 4;
      out->begin = 0;
      out->end = -1;
      multifield_raw = garbageSegment ? Rules_CreateEphemeralMultifield(0) : Rules_CreateMultifield(0);
      out->value = (int)(uintptr_t)multifield_raw;
      Mem_SmallBlockRelease(entries_raw, allocation_size);
      return multifield_raw;
    }

    entry = &entries[entry_index];
    entry->type = parsed.type;
    entry->value = parsed.value;
    if ( parsed.type == 4 )
    {
      entry->begin = parsed.begin;
      entry->end = parsed.end;
      output_count += parsed.end - parsed.begin + 1;
    }
    else if ( parsed.type == 105 )
    {
      entry->begin = 0;
      entry->end = -1;
    }
    else
    {
      entry->begin = -2;
      entry->end = -2;
      ++output_count;
    }
    node = *(_DWORD *)((uintptr_t)(unsigned int)node + 10);
  }

  multifield_raw = garbageSegment ? Rules_CreateEphemeralMultifield(output_count) : Rules_CreateMultifield(output_count);
  multifield = (unsigned char *)(uintptr_t)(unsigned int)(uintptr_t)multifield_raw;
  destination_index = 0;
  for ( entry_index = 0; entry_index < node_count; ++entry_index )
  {
    entry = &entries[entry_index];
    if ( entry->type == 4 )
    {
      source_multifield = (unsigned char *)(uintptr_t)(unsigned int)entry->value;
      for ( source_index = entry->begin; source_index <= entry->end; ++source_index )
      {
        source_offset = 14 + 6 * source_index;
        destination_offset = 14 + 6 * destination_index;
        *(_WORD *)(multifield + destination_offset) = *(_WORD *)(source_multifield + source_offset);
        *(_DWORD *)(multifield + destination_offset + 2) = *(_DWORD *)(source_multifield + source_offset + 2);
        ++destination_index;
      }
    }
    else
    {
      destination_offset = 14 + 6 * destination_index;
      *(_WORD *)(multifield + destination_offset) = (__int16)entry->type;
      *(_DWORD *)(multifield + destination_offset + 2) = entry->value;
      ++destination_index;
    }
  }

  out->type = 4;
  out->begin = 0;
  out->end = output_count - 1;
  out->value = (int)(uintptr_t)multifield_raw;
  Mem_SmallBlockRelease(entries_raw, allocation_size);
  return multifield_raw;
}
// 48D39A: conditional instruction was optimized away because esi.4!=4
// 48D1C0: variable 'v11' is possibly undefined
// 48D1CD: variable 'v10' is possibly undefined
// 48D26F: variable 'v13' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (0048D3C0) --------------------------------------------------------
signed int  Rules_MultifieldRangesEqual(_DWORD *dobj1, _DWORD *dobj2)
{
  int extent; // eax
  __int16 *fieldPtr1; // ecx
  __int16 *fieldPtr2; // edx

  extent = dobj1[4] - dobj1[3] + 1;
  if ( extent == dobj2[4] - dobj2[3] + 1 )
  {
    fieldPtr1 = (__int16 *)(uintptr_t)(dobj1[2] + 14 + 6 * dobj1[3]);
    fieldPtr2 = (__int16 *)(uintptr_t)(6 * dobj2[3] + dobj2[2] + 14);
    if ( !extent )
      return 1;
    while ( *fieldPtr1 == *fieldPtr2 && *(_DWORD *)(fieldPtr1 + 1) == *(_DWORD *)(fieldPtr2 + 1) )
    {
      if ( --extent > 0 )
      {
        fieldPtr1 += 3;
        fieldPtr2 += 3;
      }
      if ( !extent )
        return 1;
    }
  }
  return 0;
}

//----- (0048D440) --------------------------------------------------------
int  Rules_MultifieldsEqual(int segment1, int segment2)
{
  int length1; // edi
  int length2; // ecx
  int fieldIndex; // esi
  __int16 *fields1; // eax
  __int16 *fieldPtr2; // ebx
  __int16 *i; // ecx
  int result; // eax

  length1 = *(_DWORD *)(uintptr_t)(segment1 + 6);
  length2 = *(_DWORD *)(uintptr_t)(segment2 + 6);
  fieldIndex = 0;
  if ( length1 == length2 )
  {
    fields1 = (__int16 *)(uintptr_t)(segment1 + 14);
    fieldPtr2 = (__int16 *)(uintptr_t)(segment2 + 14);
    if ( length2 <= 0 )
      return 1;
    for ( i = fields1; *i == *fieldPtr2; i += 3 )
    {
      if ( *i == 4 )
      {
        result = Rules_MultifieldsEqual(*(_DWORD *)(i + 1), *(_DWORD *)(fieldPtr2 + 1));
        if ( !result )
          return result;
      }
      else if ( *(_DWORD *)(i + 1) != *(_DWORD *)(fieldPtr2 + 1) )
      {
        return 0;
      }
      fieldPtr2 += 3;
      if ( ++fieldIndex >= length1 )
        return 1;
    }
  }
  return 0;
}
// 48D478: variable 'i' is possibly undefined

//----- (0048D4B0) --------------------------------------------------------
signed int __fastcall Rules_ReportInvalidSlotError(int a1 CLASH95_UNUSED, int deftemplateName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aTmpltdef, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInvalidSlot, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNotDefinedInCo, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], deftemplateName, v6);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__10, v7);
}
// 48D4D2: variable 'v3' is possibly undefined
// 48D4DE: variable 'v4' is possibly undefined
// 48D4ED: variable 'v5' is possibly undefined
// 48D4F9: variable 'v6' is possibly undefined
// 48D508: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D520) --------------------------------------------------------
signed int Rules_ReportSingleFieldSlotCardError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aTmpltdef, 2, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTheSingleField, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCanOnlyContain, v2);
}
// 48D543: variable 'v0' is possibly undefined
// 48D54F: variable 'v1' is possibly undefined
// 48D55E: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
