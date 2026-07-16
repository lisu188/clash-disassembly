/* Generated from src/recovered/rules/clips/00491580_objects.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (00492BE0) --------------------------------------------------------
signed int Rules_AllocDeftemplateHashNode(void)
{
  _DWORD *freeListNode; // edx

  freeListNode = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( !freeListNode )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListNode;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492C10) --------------------------------------------------------
int  Rules_FreeDeftemplateHashNode(int theItem)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(theItem, g_DeftemplateConstructType, theItem);
  freed_node = (_DWORD *)theItem;
  g_ClipsMemFreeListTemp = theItem;
  *freed_node = *(_DWORD *)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E650: using guessed type int dword_54E650;

//----- (00492C60) --------------------------------------------------------
int  Rules_FindDeftemplateByName(_BYTE *deftemplateName, int a2)
{
  return Rules_FindConstructByNameGeneric(deftemplateName, g_DeftemplateConstructType);
}
// 54E650: using guessed type int dword_54E650;

//----- (00492C70) --------------------------------------------------------
int  Rules_GetNextDeftemplate(int deftemplatePtr)
{
  return Class_Enum(deftemplatePtr, g_ClipsDeftemplateModuleItemId);
}
// 54E654: using guessed type int dword_54E654;

//----- (00492C80) --------------------------------------------------------
int Rules_DeftemplateIsDeletable(void)
{
  int result; // eax
  int theDeftemplate; // edx

  result = Rules_IsBloaded();
  if ( result )
    return 0;
  if ( *(int *)(theDeftemplate + 28) <= 0 && !*(_DWORD *)(theDeftemplate + 32) )
    return 1;
  return result;
}
// 492C8C: variable 'v1' is possibly undefined

//----- (00492CB0) --------------------------------------------------------
int  Rules_FreeDeftemplateRecord(int result)
{
  int template_def; // ecx
  int slot; // edx
  int next_slot; // ecx

  template_def = result;
  if ( result )
  {
    g_Rules_DeftemplateWatchFlag = (*(_BYTE *)(template_def + 24) & 2) != 0;
    slot = *(_DWORD *)(template_def + 20);
    while ( slot )
    {
      Rules_DecrementSymbolCount(*(_DWORD *)slot, template_def);
      AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 12), template_def);
      AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 8));
      *(_DWORD *)(slot + 12) = 0;
      *(_DWORD *)(slot + 8) = 0;
      next_slot = *(_DWORD *)(slot + 16);
      slot = next_slot;
    }
    Rules_FreeTemplateSlotList(*(_DWORD *)(template_def + 20));
    Rules_FreeConstructHeaderString((int *)(uintptr_t)(unsigned int)template_def, template_def);
    g_ClipsMemFreeListTemp = template_def;
    *(_DWORD *)template_def = *(_DWORD *)(g_ClipsMemoryTable + 144);
    result = g_ClipsMemFreeListTemp;
    *(_DWORD *)(g_ClipsMemoryTable + 144) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 51A948: using guessed type int dword_51A948;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492D60) --------------------------------------------------------
int  Rules_FreeTemplateSlotList(int result)
{
  int node; // edx
  int next; // ecx
  int last_result; // eax

  node = result;
  last_result = 0;
  while ( node )
  {
    next = *(_DWORD *)(node + 16);
    AST_Free(*(_DWORD *)(node + 12));
    AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8));
    g_ClipsMemFreeListTemp = node;
    *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 80);
    last_result = g_ClipsMemoryTable;
    *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    node = next;
  }
  return last_result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492DB0) --------------------------------------------------------
int  Rules_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 28);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (00492DC0) --------------------------------------------------------
int  Rules_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(result + 28);
  return result;
}

//----- (00492DD0) --------------------------------------------------------
int Rules_InitExpressionHashTable(void)
{
  int result; // eax

  Rules_CacheConnectiveSymbols();
  g_ExpressionHashTable = (int)Mem_SmallBlockAlloc(0x7DCu);
  for ( result = 0; result != 2012; result += 4 )
    *(_DWORD *)(g_ExpressionHashTable + result) = 0;
  return result;
}
// 51A9FC: using guessed type int dword_51A9FC;

//----- (00492E10) --------------------------------------------------------
int **Rules_CacheConnectiveSymbols(void)
{
  int **result; // eax
  int v1; // ecx

  g_Clips_SymbolAnd = (int)Rules_MakeSymbol(aAnd);
  g_ClipsSymbolOr = (int)Rules_MakeSymbol(aOr);
  g_ClipsSymbolEq = (int)Rules_MakeSymbol(aEq);
  g_ClipsSymbolNeq = (int)Rules_MakeSymbol(aNeq);
  result = Rules_MakeSymbol(aNot);
  g_ClipsNotSymbol = (int)result;
  if ( !g_Clips_SymbolAnd || !g_ClipsSymbolOr || !g_ClipsSymbolEq || !g_ClipsSymbolNeq || !result )
  {
    Rules_ReportSystemError(v1, 1);
    return (int **)IO_RunRouterExitCallbacks();
  }
  return result;
}
// 492E91: variable 'v1' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E65C: using guessed type int dword_54E65C;
// 54E660: using guessed type int dword_54E660;
// 54E664: using guessed type int dword_54E664;
// 54E668: using guessed type int dword_54E668;

//----- (00492EB0) --------------------------------------------------------
__int16 * AST_InstallNodeChain(__int16 *result)
{
  __int16 *node; // ecx
  int child_node; // eax
  int next_node; // ecx

  for ( node = result; node; node = (__int16 *)(uintptr_t)(unsigned int)next_node )
  {
    Rules_AtomInstall(*node, *(_DWORD *)(node + 1), (int)(uintptr_t)node);
    child_node = *(_DWORD *)((char *)node + 6);
    AST_InstallNodeChain((__int16 *)(uintptr_t)(unsigned int)child_node);
    next_node = *(_DWORD *)((char *)node + 10);
  }
  return result;
}

//----- (00492EE0) --------------------------------------------------------
__int16 * AST_DeinstallNodeChain(__int16 *result)
{
  __int16 *node; // ecx
  int child_node; // eax
  int next_node; // ecx

  for ( node = result; node; node = (__int16 *)(uintptr_t)(unsigned int)next_node )
  {
    Rules_AtomDeinstall(
      *node,
      (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)node + 2),
      (int)(uintptr_t)node);
    child_node = *(_DWORD *)((char *)node + 6);
    AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)child_node);
    next_node = *(_DWORD *)((char *)node + 10);
  }
  return result;
}

//----- (00492F10) --------------------------------------------------------
_DWORD * AST_PackNodeChain(_DWORD *result)
{
  int node_count; // eax
  _DWORD *copy; // esi

  if ( result )
  {
    node_count = AST_CountTreeNodes((int)result);
    copy = Mem_NewArray(14 * node_count);
    AST_CopyNodeChainToArray((int)result, (int)copy, 0);
    return copy;
  }
  return result;
}

//----- (00492F50) --------------------------------------------------------
int  AST_CopyNodeChainToArray(int theList, int theArray, int storeIndex)
{
  int node; // ecx
  int current_index; // edi
  int output_node; // eax
  int child_node; // edx
  int next_node; // edi

  node = theList;
  if ( !theList )
    return storeIndex;
  while ( node )
  {
    current_index = storeIndex;
    output_node = theArray + 14 * storeIndex;
    *(_WORD *)output_node = *(_WORD *)node;
    *(_DWORD *)(output_node + 2) = *(_DWORD *)(node + 2);
    ++storeIndex;
    child_node = *(_DWORD *)(node + 6);
    if ( child_node )
    {
      *(_DWORD *)(output_node + 6) = theArray + 14 * storeIndex;
      storeIndex = AST_CopyNodeChainToArray(child_node, theArray, storeIndex);
    }
    else
    {
      *(_DWORD *)(output_node + 6) = 0;
    }
    next_node = *(_DWORD *)(node + 10);
    if ( next_node )
      *(_DWORD *)(theArray + 14 * current_index + 10) = theArray + 14 * storeIndex;
    else
      *(_DWORD *)(theArray + 14 * current_index + 10) = 0;
    node = next_node;
  }
  return storeIndex;
}

//----- (00492FD0) --------------------------------------------------------
int  AST_FreePackedNodeChain(int result)
{
  int node_count; // eax

  if ( result )
  {
    node_count = AST_CountTreeNodes(result);
    return Mem_SmallBlockRelease((_DWORD *)result, 14 * node_count);
  }
  return result;
}

//----- (00492FF0) --------------------------------------------------------
signed int AST_AllocNode(void)
{
  int node;

  node = *(_DWORD *)(g_ClipsMemoryTable + 288);
  if ( node )
  {
    g_ClipsMemFreeListTemp = node;
    *(_DWORD *)(g_ClipsMemoryTable + 288) = *(_DWORD *)node;
    node = g_ClipsMemFreeListTemp;
  }
  else
  {
    node = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }

  *(_DWORD *)node = 103;
  *(_DWORD *)(node + 4) = 0;
  *(_DWORD *)(node + 16) = 0;
  *(_DWORD *)(node + 20) = 0;
  *(_DWORD *)(node + 24) = 0;
  *(_DWORD *)(node + 28) = -1;
  *(_DWORD *)(node + 32) = -1;
  *(_DWORD *)(node + 36) = 0;
  *(_DWORD *)(node + 40) = -1;
  *(_DWORD *)(node + 44) = 1;
  *(_DWORD *)(node + 48) = 1;
  *(_DWORD *)(node + 52) = 0;
  *(_DWORD *)(node + 56) = 0;
  *(_DWORD *)(node + 60) = 0;
  *(_DWORD *)(node + 64) = 0;
  *(_DWORD *)(node + 68) = 0;
  *(_DWORD *)(node + 8) &= 0xE0003FC0;
  *(_WORD *)(node + 12) &= 0xC000u;
  *(_BYTE *)(node + 8) |= 0x20u;
  return node;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493050) --------------------------------------------------------
int AST_FreeNode(int result)
{
  int node;
  int owner;
  int (__thiscall *cleanup_fn)(void *this, int);

  node = result;
  if ( !node )
    return 0;

  AST_Free(*(_DWORD *)(node + 52));
  AST_FreeNode(*(_DWORD *)(node + 64));
  AST_FreeNode(*(_DWORD *)(node + 68));
  AST_FreeNode(*(_DWORD *)(node + 56));
  if ( *(_BYTE *)(node + 8) & 0x10 )
    AST_DecrementNodeRefCount(*(_DWORD **)(node + 16));

  if ( *(_DWORD *)(node + 60) )
  {
    owner = *(_DWORD *)(node + 24);
    if ( owner )
    {
      cleanup_fn = *(int (__thiscall **)(void *this, int))(owner + 64);
      if ( cleanup_fn )
        cleanup_fn((void *)owner, *(_DWORD *)(node + 60));
    }
  }

  g_ClipsMemFreeListTemp = node;
  *(_DWORD *)node = *(_DWORD *)(g_ClipsMemoryTable + 288);
  *(_DWORD *)(g_ClipsMemoryTable + 288) = g_ClipsMemFreeListTemp;
  return g_ClipsMemoryTable;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493000) --------------------------------------------------------
int  AST_Free(int result)
{
  int i; // edx
  _DWORD *currentNode; // eax

  for ( i = result; i; *(_DWORD *)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp )
  {
    if ( *(_DWORD *)(i + 6) )
      AST_Free(*(_DWORD *)(i + 6));
    currentNode = (_DWORD *)i;
    i = *(_DWORD *)(i + 10);
    g_ClipsMemFreeListTemp = (int)currentNode;
    *currentNode = *(_DWORD *)(g_ClipsMemoryTable + 56);
    result = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 493015: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493050) --------------------------------------------------------
__int16 * AST_FindHashedNodeChain(__int16 *result, _DWORD *hashInfo)
{
  __int16 *theExpression; // esi
  unsigned int hashValue; // eax
  unsigned int *v5; // edx
  int hashEntry; // ecx
  int v7; // ecx

  theExpression = result;
  if ( result )
  {
    hashValue = AST_HashNodeChain(result);
    *v5 = hashValue;
    *hashInfo = 0;
    hashEntry = *(_DWORD *)(g_ExpressionHashTable + 4 * *v5);
    if ( hashEntry )
    {
      while ( !AST_NodeListsEqual(*(__int16 **)(hashEntry + 8), theExpression) )
      {
        *hashInfo = v7;
        hashEntry = *(_DWORD *)(v7 + 12);
        if ( !hashEntry )
          return 0;
      }
      return (__int16 *)v7;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 493060: variable 'v5' is possibly undefined
// 493084: variable 'v7' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;

//----- (004930A0) --------------------------------------------------------
unsigned int  AST_HashNodeChain(__int16 *theExp)
{
  __int16 *currentExpr; // edx
  int argList; // ecx
  unsigned int tally; // eax
  int nodeValue; // ebx
  unsigned int v5; // eax

  currentExpr = theExp;
  argList = *(_DWORD *)(theExp + 3);
  tally = 269;
  if ( argList )
    tally = 257 * AST_HashNodeChain(argList) + 269;
  while ( currentExpr )
  {
    nodeValue = *(_DWORD *)(currentExpr + 1);
    v5 = 263 * *currentExpr + tally;
    currentExpr = *(__int16 **)(currentExpr + 5);
    tally = nodeValue + v5;
  }
  return tally % 0x1F7;
}
// 4930B3: variable 'v1' is possibly undefined

//----- (004930F0) --------------------------------------------------------
__int16 * AST_RemoveHashedNodeChain(__int16 *theExpression, int a2)
{
  __int16 *result; // eax
  int newCount; // ecx
  int v5; // edx
  _DWORD *v6; // edx
  _DWORD hashInfo[5]; // [esp+0h] [ebp-14h] BYREF

  hashInfo[3] = a2;
  result = AST_FindHashedNodeChain(theExpression, hashInfo);
  if ( result )
  {
    newCount = *((_DWORD *)result + 1) - 1;
    *((_DWORD *)result + 1) = newCount;
    if ( !newCount )
    {
      if ( hashInfo[0] )
        *(_DWORD *)(hashInfo[0] + 12) = *((_DWORD *)result + 3);
      else
        *(_DWORD *)(g_ExpressionHashTable + 4 * hashInfo[1]) = *((_DWORD *)result + 3);
      AST_DeinstallNodeChain(*((__int16 **)result + 2));
      AST_FreePackedNodeChain(*(_DWORD *)(v5 + 8));
      g_ClipsMemFreeListTemp = (int)v6;
      *v6 = *(_DWORD *)(g_ClipsMemoryTable + 80);
      result = (__int16 *)g_ClipsMemFreeListTemp;
      *(_DWORD *)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    }
  }
  return result;
}
// 493127: variable 'v5' is possibly undefined
// 493134: variable 'v6' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493170) --------------------------------------------------------
__int16 * AST_AddHashedNodeChain(__int16 *result, int a2, int a3)
{
  __int16 *foundEntry; // eax
  _DWORD *v4; // ecx
  _DWORD *freeListEntry; // edx
  _DWORD *newEntry; // edx
  __int16 *packedChain; // eax
  int v8; // edx
  _DWORD *hashEntry; // edx
  _DWORD searchContext[5]; // [esp-4h] [ebp-14h] BYREF

  searchContext[3] = a3;
  searchContext[2] = a2;
  if ( result )
  {
    foundEntry = AST_FindHashedNodeChain(result, searchContext);
    if ( foundEntry )
    {
      ++*((_DWORD *)foundEntry + 1);
      return (__int16 *)*((_DWORD *)foundEntry + 2);
    }
    else
    {
      freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 80);
      if ( freeListEntry )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 80);
        *(_DWORD *)(g_ClipsMemoryTable + 80) = *freeListEntry;
        newEntry = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        newEntry = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
      }
      *newEntry = searchContext[1];
      newEntry[1] = 1;
      packedChain = (__int16 *)AST_PackNodeChain(v4);
      *(_DWORD *)(v8 + 8) = packedChain;
      AST_InstallNodeChain(packedChain);
      hashEntry[3] = *(_DWORD *)(g_ExpressionHashTable + 4 * *hashEntry);
      *(_DWORD *)(g_ExpressionHashTable + 4 * *hashEntry) = hashEntry;
      hashEntry[4] = 0;
      return (__int16 *)hashEntry[2];
    }
  }
  return result;
}
// 4931B9: variable 'v4' is possibly undefined
// 4931BE: variable 'v8' is possibly undefined
// 4931CC: variable 'v9' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493210) --------------------------------------------------------
signed int  AST_GetHashedNodeIndex(__int16 *theExpression)
{
  __int16 *hashEntry; // eax
  int hashInfo; // [esp+0h] [ebp-8h] BYREF

  if ( !theExpression )
    return -1;
  hashEntry = AST_FindHashedNodeChain(theExpression, &hashInfo);
  if ( hashEntry )
    return *((_DWORD *)hashEntry + 4);
  else
    return -1;
}

//----- (00493250) --------------------------------------------------------
char * Parser_NextToken(int readSource, int theToken)
{
  unsigned int v4; // ecx
  char charType; // dl
  signed int firstChar; // eax
  unsigned int v7; // ecx
  int lexerSource; // eax
  signed int count; // edx
  signed int *tokenSymbol; // eax
  int printForm; // eax
  char *printText; // eax
  char *result; // eax
  unsigned int v14; // ecx
  int nextChar; // ecx
  unsigned int v16; // ecx
  signed int sfNameLength; // ecx
  int sfVarSymbol; // edi
  const char *sfVarName; // edi
  int sfNameSymbol; // edx
  int sfFinalSymbol; // edx
  unsigned int sfBufferLength; // kr0C_4
  int v23; // ecx
  signed int *tildeSymbol; // eax
  unsigned int v25; // ecx
  int v26; // ecx
  unsigned int v27; // ecx
  signed int mfNameLength; // ecx
  int mfVarSymbol; // edi
  const char *mfVarName; // edi
  int mfNameSymbol; // edx
  int mfFinalSymbol; // edx
  unsigned int mfBufferLength; // kr18_4
  int v34; // ecx
  signed int *lparenSymbol; // eax
  signed int *eofSymbol; // eax
  int stringSymbol; // eax
  unsigned int v38; // ecx
  signed int v39; // ecx
  signed int v40; // eax
  int v41; // ecx
  int v42; // ecx
  char *appended; // eax
  signed int *rparenSymbol; // eax
  signed int *orSymbol; // eax
  signed int *ampersandSymbol; // eax
  unsigned int v47; // ecx
  int v48; // ecx
  int scannedType; // [esp+0h] [ebp-1Ch] BYREF
  int i; // [esp+4h] [ebp-18h]

  if ( getenv("CLASH95_TRACE_PARSER_TOKEN") )
  {
    fprintf(
      stderr,
      "[parser] next-token lexer=%08x token=%08x caller=%p\n",
      readSource,
      theToken,
      __builtin_return_address(0));
    fflush(stderr);
  }
  *(_DWORD *)theToken = 103;
  *(_DWORD *)(theToken + 4) = 0;
  *(_DWORD *)(theToken + 8) = aUnknown;
  g_TokenCap = 0;
  g_TokenLen = 0;
  for ( i = Lexer_PeekChar(readSource, 0xDu);
        i == 32 || i == 10 || i == 12 || v4 == i || i == 59 || i == 9;
        i = Lexer_PeekChar(readSource, v4) )
  {
    if ( i == 59 )
    {
      for ( i = Lexer_PeekChar(readSource, v4); i != 10; i = Lexer_PeekChar(readSource, v4) )
      {
        if ( v4 == i )
          break;
        if ( i == -1 )
          break;
      }
    }
  }
  charType = IsTable[(unsigned __int8)(i + 1)];
  if ( (charType & 0xC0) != 0 )
  {
    firstChar = i;
    *(_DWORD *)theToken = 2;
    Lexer_SkipChar(firstChar, readSource, v4);
    lexerSource = readSource;
    count = 0;
LABEL_12:
    tokenSymbol = (signed int *)(uintptr_t)(unsigned int)(uintptr_t)Lexer_ReadToken(lexerSource, count, &scannedType, v7);
    *(_DWORD *)(theToken + 4) = (int)(uintptr_t)tokenSymbol;
LABEL_13:
    printForm = tokenSymbol[4];
LABEL_14:
    *(_DWORD *)(theToken + 8) = printForm;
    goto LABEL_15;
  }
  if ( (charType & 0x20) != 0 )
    goto LABEL_37;
  if ( i >= 41 )
  {
    if ( i <= 41 )
    {
      *(_DWORD *)theToken = 101;
      rparenSymbol = Str_Intern(asc_504D38, v4);
      *(_DWORD *)(theToken + 8) = asc_504D38;
      *(_DWORD *)(theToken + 4) = rparenSymbol;
      goto LABEL_15;
    }
    if ( i >= 60 )
    {
      if ( i <= 60 )
      {
        *(_DWORD *)theToken = 2;
        appended = Str_AppendCharEscaping(
                     60,
                     (char *)g_TokenBuf,
                     (unsigned int *)&g_TokenLen,
                     &g_TokenCap,
                     g_TokenLen + 80);
        count = 1;
        g_TokenBuf = (int)appended;
        lexerSource = readSource;
        goto LABEL_12;
      }
      if ( i >= 124 )
      {
        if ( i <= 124 )
        {
          *(_DWORD *)theToken = 92;
          orSymbol = Str_Intern(asc_504D40, v4);
          *(_DWORD *)(theToken + 8) = asc_504D40;
          *(_DWORD *)(theToken + 4) = orSymbol;
          goto LABEL_15;
        }
        if ( i == 126 )
        {
          *(_DWORD *)theToken = 90;
          tildeSymbol = Str_Intern(asc_504D3C, v4);
          *(_DWORD *)(theToken + 8) = asc_504D3C;
          *(_DWORD *)(theToken + 4) = tildeSymbol;
          goto LABEL_15;
        }
      }
      else if ( i == 63 )
      {
        i = Lexer_PeekChar(readSource, v4);
        nextChar = i;
        if ( (IsTable[(unsigned __int8)(i + 1)] & 0xC0) != 0 || i == 42 )
        {
          Lexer_SkipChar(i, readSource, i);
          *(_DWORD *)(theToken + 4) = Lexer_ReadToken(readSource, 0, &scannedType, v16);
          sfVarSymbol = *(_DWORD *)(theToken + 4);
          *(_DWORD *)theToken = 15;
          sfVarName = *(const char **)(sfVarSymbol + 16);
          if ( *sfVarName != 42
            || (sfNameLength = strlen(sfVarName), sfNameLength <= 1)
            || (sfNameSymbol = *(_DWORD *)(theToken + 4),
                sfNameLength = strlen(*(const char **)(sfNameSymbol + 16)),
                *(_BYTE *)(sfNameLength + *(_DWORD *)(sfNameSymbol + 16) - 1) != 42) )
          {
            printForm = Str_Concat(aQuestion_LexerSingleFieldVarPrefix, *(const char **)(*(_DWORD *)(theToken + 4) + 16), sfNameLength);
            goto LABEL_14;
          }
          sfFinalSymbol = *(_DWORD *)(theToken + 4);
          *(_DWORD *)theToken = 13;
          *(_DWORD *)(theToken + 8) = Str_Concat(aQuestion_LexerSingleFieldVarPrefix, *(const char **)(sfFinalSymbol + 16), sfNameLength);
          sfBufferLength = strlen((const char *)g_TokenBuf) + 1;
          *(_BYTE *)(sfBufferLength - 1 + g_TokenBuf - 1) = 0;
          *(_DWORD *)(theToken + 4) = Str_Intern((char *)(g_TokenBuf + 1), sfBufferLength - 1);
          *(_BYTE *)(g_TokenBuf + v23 - 1) = i;
        }
        else
        {
          *(_DWORD *)theToken = 17;
          *(_DWORD *)(theToken + 4) = Str_Intern(aQuestion_LexerSingleFieldVarPrefix, nextChar);
          Lexer_SkipChar(v39, readSource, v39);
          *(_DWORD *)(theToken + 8) = aQuestion_LexerSingleFieldVarPrefix;
        }
        goto LABEL_15;
      }
      goto LABEL_30;
    }
    if ( i >= 45 )
    {
      if ( i > 46 )
        goto LABEL_30;
    }
    else if ( i != 43 )
    {
      goto LABEL_30;
    }
LABEL_37:
    Lexer_SkipChar(i, readSource, v4);
    Lexer_ScanNumberToken(readSource, (_DWORD *)theToken, v14);
    goto LABEL_15;
  }
  if ( i < 34 )
  {
    if ( i >= 0 )
    {
      if ( i > 0 && i != 3 )
        goto LABEL_30;
LABEL_66:
      *(_DWORD *)theToken = 102;
      eofSymbol = Str_Intern(aStop, v4);
      *(_DWORD *)(theToken + 8) = g_Lexer_EmptyQuotedStringBuffer;
      *(_DWORD *)(theToken + 4) = eofSymbol;
      goto LABEL_15;
    }
    if ( i == -1 )
      goto LABEL_66;
LABEL_30:
    if ( (IsTable[(unsigned __int8)(i + 1)] & 8) != 0 )
    {
      Lexer_SkipChar(i, readSource, v4);
      *(_DWORD *)(theToken + 4) = Lexer_ReadToken(readSource, 0, &scannedType, v47);
      *(_DWORD *)theToken = scannedType;
      tokenSymbol = (signed int *)(uintptr_t)(unsigned int)*(_DWORD *)(theToken + 4);
      goto LABEL_13;
    }
    *(_DWORD *)(theToken + 8) = aUnprintableCha;
    goto LABEL_15;
  }
  if ( i <= 34 )
  {
    *(_DWORD *)(theToken + 4) = Lexer_ReadQuotedString(readSource, v4);
    stringSymbol = *(_DWORD *)(theToken + 4);
    *(_DWORD *)theToken = 3;
    printForm = Str_InternQuotedEscapedString(*(int **)(stringSymbol + 16), v38);
    goto LABEL_14;
  }
  if ( i >= 38 )
  {
    if ( i <= 38 )
    {
      *(_DWORD *)theToken = 91;
      ampersandSymbol = Str_Intern(asc_504D44, v4);
      *(_DWORD *)(theToken + 8) = asc_504D44;
      *(_DWORD *)(theToken + 4) = ampersandSymbol;
      goto LABEL_15;
    }
    if ( i == 40 )
    {
      *(_DWORD *)theToken = 100;
      lparenSymbol = Str_Intern(asc_504D34, v4);
      *(_DWORD *)(theToken + 8) = asc_504D34;
      *(_DWORD *)(theToken + 4) = lparenSymbol;
      goto LABEL_15;
    }
    goto LABEL_30;
  }
  if ( i != 36 )
    goto LABEL_30;
  i = Lexer_PeekChar(readSource, v4);
  if ( i != 63 )
  {
    *(_DWORD *)theToken = 2;
    g_TokenBuf = (int)Str_AppendCharEscaping(
                        36,
                        (char *)g_TokenBuf,
                        (unsigned int *)&g_TokenLen,
                        &g_TokenCap,
                        g_TokenLen + 80);
    Lexer_SkipChar(i, readSource, v42);
    count = 1;
    lexerSource = readSource;
    goto LABEL_12;
  }
  i = Lexer_PeekChar(readSource, v25);
  if ( (IsTable[(unsigned __int8)(i + 1)] & 0xC0) != 0 || i == 42 )
  {
    Lexer_SkipChar(i, readSource, v26);
    *(_DWORD *)(theToken + 4) = Lexer_ReadToken(readSource, 0, &scannedType, v27);
    mfVarSymbol = *(_DWORD *)(theToken + 4);
    *(_DWORD *)theToken = 16;
    mfVarName = *(const char **)(mfVarSymbol + 16);
    if ( *mfVarName != 42
      || (mfNameLength = strlen(mfVarName), mfNameLength <= 1)
      || (mfNameSymbol = *(_DWORD *)(theToken + 4),
          mfNameLength = strlen(*(const char **)(mfNameSymbol + 16)),
          *(_BYTE *)(mfNameLength + *(_DWORD *)(mfNameSymbol + 16) - 1) != 42) )
    {
      printForm = Str_Concat(aQuestion_LexerMultiFieldVarPrefix, *(const char **)(*(_DWORD *)(theToken + 4) + 16), mfNameLength);
      goto LABEL_14;
    }
    mfFinalSymbol = *(_DWORD *)(theToken + 4);
    *(_DWORD *)theToken = 14;
    *(_DWORD *)(theToken + 8) = Str_Concat(aQuestion_LexerMultiFieldVarPrefix, *(const char **)(mfFinalSymbol + 16), mfNameLength);
    mfBufferLength = strlen((const char *)g_TokenBuf) + 1;
    *(_BYTE *)(mfBufferLength - 1 + g_TokenBuf - 1) = 0;
    *(_DWORD *)(theToken + 4) = Str_Intern((char *)(g_TokenBuf + 1), mfBufferLength - 1);
    *(_BYTE *)(v34 + g_TokenBuf - 1) = i;
  }
  else
  {
    *(_DWORD *)theToken = 18;
    *(_DWORD *)(theToken + 4) = Str_Intern(aQuestion_LexerMultiFieldVarPrefix, v26);
    v40 = i;
    *(_DWORD *)(theToken + 8) = aQuestion_LexerMultiFieldVarPrefix;
    Lexer_SkipChar(v40, readSource, v41);
  }
LABEL_15:
  if ( *(_DWORD *)theToken == 8 )
  {
    IO_OutWriteToken(asc_504D70);
    IO_OutWriteToken(*(char **)(theToken + 8));
    printText = asc_504D74;
  }
  else
  {
    printText = *(char **)(theToken + 8);
  }
  result = IO_OutWriteToken(printText);
  if ( g_TokenBuf )
  {
    result = (char *)Mem_SmallBlockFree((_DWORD *)g_TokenBuf, g_TokenLen);
    g_TokenBuf = 0;
    g_TokenLen = 0;
    g_TokenCap = 0;
  }
  return result;
}
// 493549: simplified comparisons for '%var_18.4': <2E || ==2E became <2F
// 4932C2: variable 'v4' is possibly undefined
// 4932FD: variable 'v7' is possibly undefined
// 49341B: variable 'v14' is possibly undefined
// 493478: variable 'v16' is possibly undefined
// 49350D: variable 'v23' is possibly undefined
// 49358B: variable 'v25' is possibly undefined
// 4935BB: variable 'v26' is possibly undefined
// 4935C4: variable 'v27' is possibly undefined
// 49365D: variable 'v34' is possibly undefined
// 4936D2: variable 'v38' is possibly undefined
// 4936E7: variable 'v17' is possibly undefined
// 493708: variable 'v39' is possibly undefined
// 493724: variable 'v28' is possibly undefined
// 49374E: variable 'v41' is possibly undefined
// 49378B: variable 'v42' is possibly undefined
// 493846: variable 'v47' is possibly undefined
// 493875: variable 'v48' is possibly undefined
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (00493890) --------------------------------------------------------
signed int * Lexer_ReadToken(
        int readSource,
        signed int count,
        _DWORD *type,
        unsigned int a4)
{
  int v6; // ecx
  unsigned int v7; // ecx
  int v8; // ecx
  signed int *result; // eax
  int i; // [esp+0h] [ebp-14h]

  for ( i = Lexer_PeekChar(readSource, a4); i != 60; i = Lexer_PeekChar(readSource, v7) )
  {
    if ( i == 34 )
      break;
    if ( i == 40 )
      break;
    if ( i == 41 )
      break;
    if ( i == 38 )
      break;
    if ( i == 124 )
      break;
    if ( i == 126 )
      break;
    if ( i == 32 )
      break;
    if ( i == 59 )
      break;
    if ( (IsTable[(unsigned __int8)(i + 1)] & 8) == 0 )
      break;
    g_TokenBuf = (int)Str_AppendCharEscaping(
                        i,
                        (char *)g_TokenBuf,
                        (unsigned int *)&g_TokenLen,
                        &g_TokenCap,
                        g_TokenLen + 80);
    ++count;
  }
  Lexer_SkipChar(i, readSource, v6);
  if ( count > 2 && *(_BYTE *)g_TokenBuf == 91 && *(_BYTE *)(count + g_TokenBuf - 1) == 93 )
  {
    *type = 8;
    *(_BYTE *)(count + g_TokenBuf - 1) = 0;
    result = Str_Intern((char *)(g_TokenBuf + 1), v8);
    *(_BYTE *)(g_TokenBuf + count - 1) = 93;
  }
  else
  {
    *type = 2;
    return Str_Intern((char *)g_TokenBuf, v8);
  }
  return result;
}
// 493922: variable 'v7' is possibly undefined
// 493938: variable 'v6' is possibly undefined
// 49397A: variable 'v8' is possibly undefined
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (004939B0) --------------------------------------------------------
signed int * Lexer_ReadQuotedString(int logicalName, unsigned int a2)
{
  char *appended; // edi
  int i; // eax
  unsigned int v6; // ecx
  unsigned int v7; // ecx
  int stringSymbol; // ecx
  int stringCapacity; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int stringLength[6]; // [esp+4h] [ebp-18h] BYREF

  stringLength[4] = a2;
  appended = 0;
  stringCapacity = 0;
  stringLength[0] = 0;
  for ( i = Lexer_PeekChar(logicalName, a2); i != 34; i = Lexer_PeekChar(logicalName, v7) )
  {
    if ( i == -1 )
      break;
    if ( i == 92 )
      i = Lexer_PeekChar(logicalName, v6);
    appended = Str_AppendCharEscaping(i, appended, stringLength, &stringCapacity, stringLength[0] + 80);
  }
  if ( i == -1 && !g_Lexer_SuppressEofError )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aEncounteredEnd, v6);
  if ( !appended )
    return Str_Intern(g_Lexer_EmptyQuotedStringBuffer, v6);
  Str_Intern(appended, v6);
  Mem_SmallBlockFree(appended, stringLength[0]);
  return (signed int *)stringSymbol;
}
// 4939DB: variable 'v6' is possibly undefined
// 4939FB: variable 'v7' is possibly undefined
// 493A51: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AA0C: using guessed type int dword_51AA0C;

//----- (00493A60) --------------------------------------------------------
int  Lexer_ScanNumberToken(int logicalName, _DWORD *theToken, unsigned int a3)
{
  int digitFound; // ebp
  char charType; // bl
  unsigned int bufferSize; // eax
  int v6; // ecx
  char *tokenBufPtr; // edx
  int count; // edi
  int phase; // esi
  char *appended; // eax
  unsigned int v11; // ecx
  char *digitBuffer; // eax
  int v13; // ecx
  int theLong; // eax
  signed int longValue; // ecx
  int v16; // ecx
  int *integerValue; // eax
  int v18; // edx
  int result; // eax
  int v20; // edx
  signed int symbolCount; // edi
  char *symbolBuffer; // eax
  unsigned int v23; // ecx
  signed int *scannedSymbol; // eax
  _DWORD *v25; // edx
  char lastChar; // al
  signed int *symbolValue; // eax
  int v28; // edx
  int doubleValue; // eax
  int v30; // edx
  int v31; // edx
  double theFloat; // [esp+0h] [ebp-44h]
  int scannedType; // [esp+8h] [ebp-3Ch] BYREF
  _DWORD *tokenOut; // [esp+Ch] [ebp-38h]
  int v35; // [esp+10h] [ebp-34h]
  int readSource; // [esp+14h] [ebp-30h]
  int processFloat; // [esp+18h] [ebp-2Ch]
  int nextCount; // [esp+1Ch] [ebp-28h]
  int inchar; // [esp+20h] [ebp-24h]
  unsigned __int8 v40; // [esp+24h] [ebp-20h]
  unsigned __int8 charLookupIndex; // [esp+28h] [ebp-1Ch]
  unsigned __int8 v42; // [esp+2Ch] [ebp-18h]

  readSource = logicalName;
  tokenOut = theToken;
  inchar = Lexer_PeekChar(logicalName, a3);
  digitFound = 0;
  processFloat = 0;
  v35 = 1;
  charType = IsTable[(unsigned __int8)(inchar + 1)];
  bufferSize = g_TokenLen + 80;
  if ( (charType & 0x20) != 0 )
  {
    digitFound = 1;
    count = v35;
    tokenBufPtr = (char *)g_TokenBuf;
    goto LABEL_5;
  }
  v6 = inchar;
  if ( inchar == 43 || inchar == 45 )
  {
    tokenBufPtr = (char *)g_TokenBuf;
    bufferSize = g_TokenLen + 80;
    count = 1;
LABEL_5:
    phase = 0;
    appended = Str_AppendCharEscaping(inchar, tokenBufPtr, (unsigned int *)&g_TokenLen, &g_TokenCap, bufferSize);
    goto LABEL_6;
  }
  if ( inchar == 46 )
  {
    phase = 1;
    processFloat = 1;
    count = v35;
    appended = Str_AppendCharEscaping(46, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
    goto LABEL_6;
  }
  if ( inchar != 69 && inchar != 101 )
  {
    if ( inchar != 60
      && inchar != 34
      && inchar != 40
      && inchar != 41
      && inchar != 38
      && inchar != 124
      && inchar != 126
      && inchar != 32
      && inchar != 59
      && (charType & 8) != 0 )
    {
      symbolCount = v35;
      symbolBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
      goto LABEL_33;
    }
    goto LABEL_18;
  }
  processFloat = 1;
  phase = 2;
  count = 1;
  appended = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
LABEL_6:
  for ( g_TokenBuf = (int)appended; ; g_TokenBuf = (int)digitBuffer )
  {
    inchar = Lexer_PeekChar(readSource, v11);
    v40 = inchar + 1;
    v42 = inchar + 1;
    charLookupIndex = inchar + 1;
    switch ( phase )
    {
      case 0:
        if ( (IsTable[v40] & 0x20) == 0 )
        {
          if ( inchar == 46 )
          {
            phase = 1;
            processFloat = 1;
            ++count;
            appended = Str_AppendCharEscaping(
                         46,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( inchar == 69 || inchar == 101 )
          {
            phase = 2;
            processFloat = 1;
            ++count;
            appended = Str_AppendCharEscaping(
                         inchar,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( inchar != 60
            && inchar != 34
            && inchar != 40
            && inchar != 41
            && inchar != 38
            && inchar != 124
            && inchar != 126
            && inchar != 32
            && inchar != 59
            && (IsTable[(unsigned __int8)(inchar + 1)] & 8) != 0 )
          {
            goto LABEL_68;
          }
          goto LABEL_18;
        }
        goto LABEL_9;
      case 1:
        if ( (IsTable[v42] & 0x20) == 0 )
        {
          if ( inchar == 69 || inchar == 101 )
          {
            phase = 2;
            ++count;
            appended = Str_AppendCharEscaping(
                         inchar,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( inchar != 60
            && inchar != 34
            && inchar != 40
            && inchar != 41
            && inchar != 38
            && inchar != 124
            && inchar != 126
            && inchar != 32
            && inchar != 59
            && (IsTable[(unsigned __int8)(inchar + 1)] & 8) != 0 )
          {
            goto LABEL_68;
          }
          goto LABEL_18;
        }
LABEL_9:
        digitFound = 1;
        ++count;
        digitBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
        continue;
      case 2:
        if ( (IsTable[charLookupIndex] & 0x20) == 0 && inchar != 43 && inchar != 45 )
        {
          if ( inchar != 60
            && inchar != 34
            && inchar != 40
            && inchar != 41
            && inchar != 38
            && inchar != 124
            && inchar != 126
            && inchar != 32
            && inchar != 59
            && (IsTable[(unsigned __int8)(inchar + 1)] & 8) != 0 )
          {
LABEL_68:
            symbolCount = count + 1;
            symbolBuffer = Str_AppendCharEscaping(
                    inchar,
                    (char *)g_TokenBuf,
                    (unsigned int *)&g_TokenLen,
                    &g_TokenCap,
                    g_TokenLen + 80);
            goto LABEL_33;
          }
          digitFound = 0;
LABEL_18:
          Lexer_SkipChar(inchar, readSource, v6);
          if ( digitFound )
          {
            if ( processFloat )
            {
              theFloat = strtod((const char *)(uintptr_t)(unsigned int)g_TokenBuf, 0);
              *tokenOut = 0;
              doubleValue = Rules_AddDoubleValue(theFloat);
              *(_DWORD *)((uintptr_t)tokenOut + 4) = doubleValue;
              result = Rules_FloatToSymbol(*(_DWORD *)((uintptr_t)(unsigned int)doubleValue + 16), *(double *)((uintptr_t)(unsigned int)doubleValue + 16));
              *(_DWORD *)((uintptr_t)tokenOut + 8) = result;
            }
            else
            {
              theLong = Str_ParseSignedInt((char *)g_TokenBuf);
              longValue = theLong;
              if ( theLong == 0x7FFFFFFF || theLong == 0x80000000 )
              {
                Rules_PrintWarningID((int)aScanner, 1, 0);
                Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aOverOrUnderflo, v16);
              }
              *tokenOut = 1;
              integerValue = Rules_AddIntegerValue(longValue);
              *(_DWORD *)((uintptr_t)tokenOut + 4) = integerValue;
              result = Rules_LongIntegerToSymbol(*(_DWORD *)((uintptr_t)(unsigned int)integerValue + 16));
              *(_DWORD *)((uintptr_t)tokenOut + 8) = result;
            }
          }
          else
          {
            *tokenOut = 2;
            symbolValue = Str_Intern((char *)(uintptr_t)(unsigned int)g_TokenBuf, 0);
            *(_DWORD *)((uintptr_t)tokenOut + 4) = symbolValue;
            result = *(_DWORD *)((uintptr_t)(unsigned int)symbolValue + 16);
            *(_DWORD *)((uintptr_t)tokenOut + 8) = result;
          }
          return result;
        }
        phase = 3;
        ++count;
        appended = Str_AppendCharEscaping(
                     inchar,
                     (char *)g_TokenBuf,
                     (unsigned int *)&g_TokenLen,
                     &g_TokenCap,
                     g_TokenLen + 80);
        goto LABEL_6;
    }
    nextCount = count + 1;
    if ( (IsTable[charLookupIndex] & 0x20) == 0 )
      break;
    count = nextCount;
    digitBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
  }
  v6 = inchar;
  if ( inchar == 60
    || inchar == 34
    || inchar == 40
    || inchar == 41
    || inchar == 38
    || inchar == 124
    || inchar == 126
    || inchar == 32
    || inchar == 59
    || (IsTable[charLookupIndex] & 8) == 0 )
  {
    lastChar = *(_BYTE *)(g_TokenBuf + count - 1);
    if ( lastChar == 43 || lastChar == 45 )
      digitFound = 0;
    goto LABEL_18;
  }
  symbolCount = nextCount;
  symbolBuffer = Str_AppendCharEscaping(inchar, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
LABEL_33:
  g_TokenBuf = (int)symbolBuffer;
  scannedSymbol = Lexer_ReadToken(readSource, symbolCount, &scannedType, v23);
  v25 = tokenOut;
  tokenOut[1] = scannedSymbol;
  *v25 = scannedType;
  result = *(_DWORD *)(v25[1] + 16);
  v25[2] = result;
  return result;
}
// 493B07: conditional instruction was optimized away because esi.4<4u
// 493B10: conditional instruction was optimized away because esi.4<4u
// 493B19: conditional instruction was optimized away because esi.4<4u
// 493B6B: conditional instruction was optimized away because esi.4 is in (<2u|==3)
// 493B70: conditional instruction was optimized away because esi.4 is in (<2u|==3)
// 493FEC: conditional instruction was optimized away because esi.4==3
// 493AE9: variable 'v11' is possibly undefined
// 493C13: variable 'v6' is possibly undefined
// 493C5D: variable 'v16' is possibly undefined
// 493C72: variable 'v15' is possibly undefined
// 493C77: variable 'v18' is possibly undefined
// 493C82: variable 'v20' is possibly undefined
// 493D0C: variable 'v23' is possibly undefined
// 4940CB: variable 'v13' is possibly undefined
// 4940D0: variable 'v28' is possibly undefined
// 49410E: variable 'v30' is possibly undefined
// 494122: variable 'v31' is possibly undefined
// 4B6AC6: using guessed type double __fastcall strtod_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (00494160) --------------------------------------------------------
signed int  Rules_ExpressionConstraintsCompatible(__int16 *theExpression)
{
  _BYTE *rv; // ebx
  _BYTE *implicit; // eax
  _DWORD *v3; // ecx
  char *v4; // edx
  _DWORD *intersection; // edx

  rv = Rules_BuildLHSNodeFromToken(theExpression);
  implicit = Rules_ApplyPatternKeywordFlags();
  Rules_IntersectConstraints((int)rv, (int)implicit);
  AST_DecrementNodeRefCount(rv);
  AST_DecrementNodeRefCount(v3);
  if ( Rules_ConstraintIsUnmatchable(v4) )
  {
    AST_DecrementNodeRefCount(intersection);
    return 1;
  }
  else
  {
    AST_DecrementNodeRefCount(intersection);
    return 0;
  }
}
// 494186: variable 'v3' is possibly undefined
// 49418D: variable 'v4' is possibly undefined
// 494198: variable 'v5' is possibly undefined

//----- (00494230) --------------------------------------------------------
signed int  Rules_TagIsConstantType(int theType)
{
  signed int result; // eax

  switch ( theType )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

//----- (00494250) --------------------------------------------------------
int  AST_NodeListsEqual(__int16 *firstList, __int16 *secondList)
{
  __int16 *i; // ecx
  int result; // eax
  int v5; // ecx

  for ( i = firstList; i; secondList = *(__int16 **)(secondList + 5) )
  {
    if ( !secondList )
      break;
    if ( *i != *secondList || *(_DWORD *)(i + 1) != *(_DWORD *)(secondList + 1) )
      return 0;
    result = AST_NodeListsEqual(*(_DWORD *)(i + 3), *(_DWORD *)(secondList + 3));
    if ( !result )
      return result;
    i = *(__int16 **)(v5 + 10);
  }
  return i == secondList;
}
// 49427F: variable 'v5' is possibly undefined

//----- (004942A0) --------------------------------------------------------
int  AST_CountListNodes(uintptr_t exprList)
{
  int i; // edx

  for ( i = 0; exprList; ++i )
    exprList = (uintptr_t)(unsigned int)*(_DWORD *)(exprList + 10);
  return i;
}

//----- (004942C0) --------------------------------------------------------
signed int  AST_CloneNodeList(signed int result)
{
  signed int lastCopy; // ebx
  signed int topLevel; // esi
  int v3; // ecx
  int v4; // ecx
  int i; // ecx
  int v6; // ecx
  signed int copiedArgList; // eax
  signed int newCopy; // edx
  int v9; // ecx

  if ( result )
  {
    lastCopy = AST_NewNode(*(_WORD *)result, *(_DWORD *)(result + 2));
    topLevel = lastCopy;
    *(_DWORD *)(lastCopy + 6) = AST_CloneNodeList(*(_DWORD *)(v3 + 6));
    for ( i = *(_DWORD *)(v4 + 10); i; lastCopy = newCopy )
    {
      AST_NewNode(*(_WORD *)i, *(_DWORD *)(i + 2));
      copiedArgList = AST_CloneNodeList(*(_DWORD *)(v6 + 6));
      *(_DWORD *)(newCopy + 6) = copiedArgList;
      *(_DWORD *)(lastCopy + 10) = newCopy;
      i = *(_DWORD *)(v9 + 10);
    }
    return topLevel;
  }
  return result;
}
// 4942DB: variable 'v3' is possibly undefined
// 4942E6: variable 'v4' is possibly undefined
// 4942FA: variable 'v6' is possibly undefined
// 494302: variable 'v8' is possibly undefined
// 494308: variable 'v9' is possibly undefined
