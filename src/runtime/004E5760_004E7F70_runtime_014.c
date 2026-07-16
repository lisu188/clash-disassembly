/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004E5760) --------------------------------------------------------
int  AST_CloneFieldAccessSubtreeJN(int result)
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
    freeListEntry = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 56);
    if ( freeListEntry )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = *freeListEntry;
      newExpr = g_ClipsMemFreeListTemp;
    }
    else
    {
      newExpr = Mem_HeapAllocWithRetry((_DWORD *)0xE);
    }
    *(_WORD *)(uintptr_t)newExpr = *(_WORD *)(uintptr_t)currentNode;
    *(_DWORD *)(uintptr_t)(newExpr + 2) = *(_DWORD *)(uintptr_t)(currentNode + 4);
    nextArgExpr = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(uintptr_t)(currentNode + 64));
    *(_DWORD *)(uintptr_t)(v5 + 10) = nextArgExpr;
    argListExpr = AST_CloneFieldAccessSubtreeJN(*(_DWORD *)(uintptr_t)(v6 + 68));
    *(_DWORD *)(uintptr_t)(v9 + 6) = argListExpr;
    resultExpr = v9;
    if ( *v8 == 15 || *v8 == 16 )
    {
      (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)(v8[5] + 24) + 52))();
    }
    else if ( *(_WORD *)(uintptr_t)v9 == 13 )
    {
      Defglobal_ResolveGlobalVariableReference(v9, v9);
      return resultExpr;
    }
    return resultExpr;
  }
  return result;
}
// 4E579C: variable 'v5' is possibly undefined
// 4E579F: variable 'v6' is possibly undefined
// 4E57A7: variable 'v9' is possibly undefined
// 4E57AA: variable 'v8' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E57F0) --------------------------------------------------------
int  AST_BuildCrossClassFieldAccessTest(int selfNode, int referringNode)
{
  int selfPatternType; // eax
  int referringPatternType; // edx
  int compareSymbol; // edx
  int v7; // ecx
  __int64 v8; // rax
  __int64 v9; // rax

  selfPatternType = *(_DWORD *)(uintptr_t)(selfNode + 24);
  if ( !*(_DWORD *)(uintptr_t)(selfPatternType + 44) )
    return 0;
  referringPatternType = *(_DWORD *)(uintptr_t)(referringNode + 24);
  if ( !*(_DWORD *)(uintptr_t)(referringPatternType + 44) )
    return 0;
  if ( *(_DWORD *)(uintptr_t)(selfPatternType + 44) == *(_DWORD *)(uintptr_t)(referringPatternType + 44) )
    return (*(int (**)(void))(uintptr_t)(selfPatternType + 44))();
  if ( (*(_BYTE *)(uintptr_t)(selfNode + 8) & 1) != 0 )
    compareSymbol = g_ClipsSymbolNeq;
  else
    compareSymbol = g_ClipsSymbolEq;
  AST_NewNode(10, compareSymbol);
  v8 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v7 + 24) + 40))();
  *(_DWORD *)(uintptr_t)(HIDWORD(v8) + 6) = v8;
  v9 = ((__int64 (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(referringNode + 24) + 40))();
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(HIDWORD(v9) + 6) + 10) = v9;
  return HIDWORD(v9);
}
// 4E5829: variable 'v7' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E5870) --------------------------------------------------------
int  AST_InvokeFieldAccessValidator(int theField, int jnTest)
{
  int patternType; // ecx

  patternType = *(_DWORD *)(uintptr_t)(theField + 24);
  if ( *(_DWORD *)(uintptr_t)(patternType + 60) )
    return (*(int (__cdecl **)(int))(uintptr_t)(patternType + 60))(jnTest);
  else
    return 0;
}

//----- (004E5890) --------------------------------------------------------
int  AST_IsFieldAccessHomogeneousAcrossHierarchy(int nodeChain, int whichPattern)
{
  int chainNode; // esi
  int fieldNode; // ecx
  int nodeType; // edx
  int result; // eax

  chainNode = nodeChain;
  if ( !nodeChain )
    return 1;
  while ( 1 )
  {
    fieldNode = chainNode;
    if ( chainNode )
      break;
LABEL_6:
    chainNode = *(_DWORD *)(uintptr_t)(chainNode + 68);
    if ( !chainNode )
      return 1;
  }
  while ( 1 )
  {
    nodeType = *(_DWORD *)(uintptr_t)fieldNode;
    if ( *(_DWORD *)(uintptr_t)fieldNode == 15 || nodeType == 16 )
      break;
    if ( nodeType == 93 || nodeType == 94 )
    {
      result = AST_IsFieldPositionConsistent(*(_DWORD **)(uintptr_t)(fieldNode + 56), whichPattern);
      if ( !result )
        return result;
    }
LABEL_5:
    fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 64);
    if ( !fieldNode )
      goto LABEL_6;
  }
  if ( whichPattern == *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(fieldNode + 20) + 28) )
    goto LABEL_5;
  return 0;
}
// 4E58B0: variable 'v4' is possibly undefined

//----- (004E58F0) --------------------------------------------------------
int  AST_IsFieldPositionConsistent(_DWORD *theNode, int whichPattern)
{
  _DWORD *currentNode; // ecx
  int result; // eax
  int v5; // ecx

  currentNode = theNode;
  if ( !theNode )
    return 1;
  while ( *currentNode != 15 && *currentNode != 16 || whichPattern == *(_DWORD *)(uintptr_t)(currentNode[5] + 28) )
  {
    result = AST_IsFieldPositionConsistent(currentNode[17], whichPattern);
    if ( !result )
      return result;
    currentNode = *(_DWORD **)(uintptr_t)(v5 + 64);
    if ( !currentNode )
      return 1;
  }
  return 0;
}
// 4E5921: variable 'v5' is possibly undefined

//----- (004E5C90) --------------------------------------------------------
unsigned int  CRT_StrToXLong(unsigned __int8 *numStr, int *endPtr, int signedFlag, signed int requestedBase)
{
  signed int radix; // esi
  unsigned __int8 *i; // edx
  unsigned __int8 hexPrefixChar; // cl
  unsigned __int8 v9; // bh
  unsigned int value; // ebx
  int digitPtr; // edx
  unsigned int prevValue; // eax
  char signChar; // ch
  unsigned __int8 *digitsStart; // [esp+4h] [ebp-18h]
  int digit; // [esp+8h] [ebp-14h]
  int signedFlagSaved; // [esp+Ch] [ebp-10h]

  radix = requestedBase;
  signedFlagSaved = signedFlag;
  if ( endPtr )
    *endPtr = (int)(intptr_t)numStr;
  for ( i = numStr; (IsTable[(unsigned __int8)(*i + 1)] & 2) != 0; ++i )
    ;
  BYTE1(signedFlag) = *i;
  if ( *i == 43 || BYTE1(signedFlag) == 45 )
    ++i;
  if ( requestedBase )
  {
    if ( requestedBase < 2 || requestedBase > 36 )
    {
      _set_errno_((int)(intptr_t)numStr);
      return 0;
    }
    if ( requestedBase == 16 )
      goto LABEL_21;
  }
  else
  {
    if ( *i == 48 )
    {
      hexPrefixChar = i[1];
      if ( hexPrefixChar == 120 || hexPrefixChar == 88 )
      {
        radix = 16;
LABEL_21:
        if ( *i == 48 )
        {
          v9 = i[1];
          if ( v9 == 120 || v9 == 88 )
            i += 2;
        }
        goto LABEL_25;
      }
    }
    if ( *i == 48 )
      radix = 8;
    else
      radix = 10;
  }
LABEL_25:
  digitsStart = i;
  LOBYTE(signedFlag) = 0;
  value = 0;
  while ( 1 )
  {
    digit = CRT_DigitCharToValue(*i, (int)(intptr_t)i, signedFlag);
    if ( digit >= radix )
      break;
    if ( value > (unsigned int)(intptr_t)g_StrToLongOverflowLimitTable[radix] )
      LOBYTE(signedFlag) = 1;
    prevValue = value;
    value = digit + radix * value;
    if ( value < prevValue )
      LOBYTE(signedFlag) = 1;
    i = (unsigned __int8 *)(uintptr_t)(digitPtr + 1);
  }
  if ( (unsigned __int8 *)(uintptr_t)digitPtr == digitsStart )
    digitPtr = (int)(intptr_t)numStr;
  if ( endPtr )
    *endPtr = digitPtr;
  if ( (signedFlagSaved != 1 || value < 0x80000000 || value == 0x80000000 && BYTE1(signedFlag) == 45) && !(_BYTE)signedFlag )
  {
    if ( BYTE1(signedFlag) == 45 )
      return -value;
    return value;
  }
  else
  {
    _set_errno_((int)(intptr_t)numStr);
    if ( signedFlagSaved )
    {
      if ( signChar == 45 )
        return 0x80000000;
      else
        return 0x7FFFFFFF;
    }
    else
    {
      return -1;
    }
  }
}
// 4E5D40: variable 'a3' is possibly undefined
// 4E5D66: variable 'v11' is possibly undefined
// 4E5DAF: variable 'v13' is possibly undefined
// 51C790: using guessed type char *off_51C790[2];

//----- (004E5DD9) --------------------------------------------------------
unsigned int  CRT_StrToULongRadix(unsigned __int8 *numStr, int *endPtr, signed int base)
{
  return CRT_StrToXLong(numStr, endPtr, 1, base);
}

//----- (004E5DE1) --------------------------------------------------------
int  CRT_DigitCharToValue(unsigned __int8 digitChar, int a2, int a3)
{
  unsigned __int8 lowerChar; // al

  if ( digitChar >= 0x30u && digitChar <= 0x39u )
    return digitChar - 48;
  lowerChar = tolower_(a3, a2);
  if ( lowerChar >= 0x61u && lowerChar <= 0x69u )
    return lowerChar - 87;
  if ( lowerChar >= 0x6Au && lowerChar <= 0x72u || lowerChar >= 0x73u && lowerChar <= 0x7Au )
    return lowerChar - 87;
  return 37;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004E5F8A) --------------------------------------------------------
void  CRT_PutEnvEntryA(_BYTE *envString, _BYTE *i, int a3)
{
  int entryIndex; // ebp
  _DWORD *newTable; // eax
  int flagArrayPtr; // eax
  int foundIndex; // eax
  int v7; // edx
  int tableSizeBytes; // ecx
  int v9; // eax
  void *newBlock; // eax
  unsigned int copyBytes; // ecx
  int reallocatedTable; // eax
  int v13; // ecx
  int tableBytes; // [esp+4h] [ebp-20h]
  int envTable; // [esp+8h] [ebp-1Ch]

  if ( envString )
  {
    if ( *envString )
    {
      for ( i = envString + 1; *i && *i != 61; ++i )
        ;
    }
    if ( *i )
    {
      entryIndex = i[1] == 0;
      envTable = g_CRT_EnvVarPointerArray;
      if ( g_CRT_EnvVarPointerArray )
      {
        foundIndex = CRT_FindEnvVarIndexA(envString, entryIndex, a3);
        if ( entryIndex )
          goto LABEL_23;
        if ( foundIndex > 0 )
        {
          entryIndex = foundIndex - 1;
          goto LABEL_22;
        }
        entryIndex = -foundIndex;
        tableSizeBytes = -4 * foundIndex;
        tableBytes = -4 * foundIndex + 8;
        v9 = 1 - foundIndex + tableBytes;
        if ( g_RuntimeGrowableByteFlagArrayPtr )
        {
          reallocatedTable = nrealloc_(tableSizeBytes, v9);
          envTable = reallocatedTable;
          if ( !reallocatedTable )
            goto LABEL_23;
          memmove_((void *)(uintptr_t)(reallocatedTable + tableBytes), (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryIndex);
          g_RuntimeGrowableByteFlagArrayPtr = v13;
        }
        else
        {
          newBlock = (void *)nmalloc_(tableSizeBytes, v7);
          envTable = (int)(intptr_t)newBlock;
          if ( !newBlock )
            goto LABEL_23;
          qmemcpy(newBlock, (const void *)(uintptr_t)g_CRT_EnvVarPointerArray, copyBytes);
          g_RuntimeGrowableByteFlagArrayPtr = (int)(intptr_t)newBlock + tableBytes;
          memset_(0, 0);
        }
        g_CRT_EnvVarPointerArray = envTable;
        *(_DWORD *)(uintptr_t)(envTable + 4 * entryIndex + 4) = 0;
        goto LABEL_22;
      }
      if ( i[1] )
      {
        newTable = (_DWORD *)nmalloc_(a3, i);
        envTable = (int)(intptr_t)newTable;
        if ( newTable )
        {
          g_CRT_EnvVarPointerArray = (int)(intptr_t)newTable;
          *newTable = 0;
          flagArrayPtr = (int)(intptr_t)(newTable + 2);
          *(_DWORD *)(uintptr_t)(flagArrayPtr - 4) = 0;
          g_RuntimeGrowableByteFlagArrayPtr = flagArrayPtr;
LABEL_22:
          *(_DWORD *)(uintptr_t)(envTable + 4 * entryIndex) = envString;
          *(_BYTE *)(uintptr_t)(g_RuntimeGrowableByteFlagArrayPtr + entryIndex) = 0;
        }
      }
    }
  }
LABEL_23:
  // 4E60F0: jumps to the shared register-restore epilogue at 4E5F83 (in putenv_);
  // in C this is the function return.
  return;
}
// 4E60F0: control flows out of bounds to 4E5F83
// 4E603E: variable 'v7' is possibly undefined
// 4E6064: variable 'v11' is possibly undefined
// 4E60AF: variable 'v13' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 4D9607: using guessed type int __fastcall nrealloc_(_DWORD, _DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E704: using guessed type int dword_54E704;

//----- (004E60F5) --------------------------------------------------------
int  CRT_FindEnvVarIndexA(_BYTE *envName, int deleteFlag, int a3)
{
  _DWORD *tableEntry; // esi
  _BYTE *i; // ebx
  int v7; // eax
  int v8; // eax
  _BYTE *v9; // edx
  int entryIndex; // edi
  _DWORD *j; // ecx
  int entryCount; // esi
  int v13; // ecx
  unsigned __int8 *flagBytePtr; // eax

  tableEntry = (_DWORD *)(uintptr_t)g_CRT_EnvVarPointerArray;
LABEL_20:
  if ( !*tableEntry )
    return (g_CRT_EnvVarPointerArray - (int)(intptr_t)tableEntry) >> 2;
  for ( i = envName; ; ++i )
  {
    if ( !*i || (v7 = toupper_(a3), v8 = toupper_(v7), a3 != v8) )
    {
      ++tableEntry;
      goto LABEL_20;
    }
    if ( *v9 == 61 )
      break;
  }
  entryIndex = ((int)(intptr_t)tableEntry - g_CRT_EnvVarPointerArray) >> 2;
  if ( !deleteFlag )
    return entryIndex + 1;
  for ( j = tableEntry; *j; ++j )
    *j = j[1];
  if ( g_RuntimeGrowableByteFlagArrayPtr )
  {
    if ( *(_BYTE *)(uintptr_t)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr) )
      nfree_(j);
    entryCount = ((int)(intptr_t)j - g_CRT_EnvVarPointerArray) >> 2;
    memmove_(j, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryCount);
    g_RuntimeGrowableByteFlagArrayPtr = v13;
    if ( entryIndex < entryCount )
    {
      flagBytePtr = (unsigned __int8 *)(uintptr_t)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr);
      do
      {
        *flagBytePtr = flagBytePtr[1];
        ++flagBytePtr;
        ++entryIndex;
      }
      while ( entryIndex < entryCount );
    }
  }
  return 0;
}
// 4E6114: variable 'a3' is possibly undefined
// 4E612C: variable 'v9' is possibly undefined
// 4E617A: variable 'j' is possibly undefined
// 4E618E: variable 'v13' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 476271: using guessed type int __thiscall toupper_(_DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E704: using guessed type int dword_54E704;

//----- (004E70ED) --------------------------------------------------------
signed int  CRT_PutEnvEntryW(_WORD *envString, _WORD *i)
{
  bool valueIsEmpty; // al
  BOOL removeFlag; // ebx
  _DWORD *allocatedTable; // eax
  int envTablePtr; // ecx
  int flagArrayBase; // eax
  int entryIndex; // esi
  int foundIndex; // eax
  int mallocSize; // edx
  int reallocSize; // eax
  int newTable; // ebp
  int v14; // ecx
  int reallocedTable; // eax
  int flagArrayPtr; // ebp
  int tableBytes; // [esp+0h] [ebp-20h]

  if ( !envString )
    return -1;
  if ( *envString )
  {
    for ( i = envString + 1; *i && *i != 61; ++i )
      ;
  }
  if ( !*i )
    return -1;
  valueIsEmpty = i[1] == 0;
  removeFlag = valueIsEmpty;
  if ( g_CrtWideEnvironTable )
  {
    foundIndex = CRT_FindEnvVarIndexW(envString, valueIsEmpty, g_CrtWideEnvironTable);
    if ( !removeFlag )
    {
      if ( foundIndex > 0 )
      {
        entryIndex = foundIndex - 1;
        goto LABEL_22;
      }
      entryIndex = -foundIndex;
      mallocSize = 1 - foundIndex;
      tableBytes = -4 * foundIndex + 8;
      reallocSize = 1 - foundIndex + tableBytes;
      if ( g_RuntimeGrowableByteFlagArrayPtr )
      {
        reallocedTable = nrealloc_(envTablePtr, reallocSize);
        if ( !reallocedTable )
          return -1;
        flagArrayPtr = reallocedTable + tableBytes;
        memmove_((void *)(uintptr_t)reallocedTable, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryIndex);
        g_RuntimeGrowableByteFlagArrayPtr = flagArrayPtr;
      }
      else
      {
        newTable = nmalloc_(envTablePtr, mallocSize);
        if ( !newTable )
          return -1;
        memcpy_(newTable, g_CrtWideEnvironTable);
        g_RuntimeGrowableByteFlagArrayPtr = newTable + tableBytes;
        memset_(v14, 0);
      }
      g_CrtWideEnvironTable = envTablePtr;
      *(_DWORD *)(uintptr_t)(envTablePtr + 4 * entryIndex + 4) = 0;
      goto LABEL_22;
    }
  }
  else if ( i[1] )
  {
    allocatedTable = (_DWORD *)nmalloc_(0, i);
    envTablePtr = (int)(intptr_t)allocatedTable;
    if ( allocatedTable )
    {
      g_CrtWideEnvironTable = (int)(intptr_t)allocatedTable;
      *allocatedTable = 0;
      flagArrayBase = (int)(intptr_t)(allocatedTable + 2);
      entryIndex = 0;
      *(_DWORD *)(uintptr_t)(flagArrayBase - 4) = 0;
      g_RuntimeGrowableByteFlagArrayPtr = flagArrayBase;
LABEL_22:
      *(_DWORD *)(uintptr_t)(envTablePtr + 4 * entryIndex) = envString;
      *(_BYTE *)(uintptr_t)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr) = 0;
      return 0;
    }
    return -1;
  }
  return 0;
}
// 4E71AC: variable 'v7' is possibly undefined
// 4E71D8: variable 'v14' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 4D9607: using guessed type int __fastcall nrealloc_(_DWORD, _DWORD);
// 4D9756: using guessed type int __fastcall memcpy_(_DWORD, _DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E708: using guessed type int dword_54E708;

//----- (004E7239) --------------------------------------------------------
int  CRT_FindEnvVarIndexW(_WORD *envName, int deleteFlag, int a3)
{
  _DWORD *tableEntry; // esi
  _WORD *i; // ebx
  int v7; // eax
  __int16 v8; // ax
  _WORD *v9; // edx
  int entryIndex; // edi
  _DWORD *j; // ecx
  int entryCount; // esi
  int v13; // ecx
  _BYTE *flagBytePtr; // eax

  tableEntry = (_DWORD *)(uintptr_t)g_CrtWideEnvironTable;
LABEL_20:
  if ( !*tableEntry )
    return (g_CrtWideEnvironTable - (int)(intptr_t)tableEntry) >> 2;
  for ( i = envName; ; ++i )
  {
    if ( !*i || (v7 = towupper_(a3), v8 = towupper_(v7), (_WORD)a3 != v8) )
    {
      ++tableEntry;
      goto LABEL_20;
    }
    if ( *v9 == 61 )
      break;
  }
  entryIndex = ((int)(intptr_t)tableEntry - g_CrtWideEnvironTable) >> 2;
  if ( !deleteFlag )
    return entryIndex + 1;
  for ( j = tableEntry; *j; ++j )
    *j = j[1];
  if ( g_RuntimeGrowableByteFlagArrayPtr )
  {
    if ( *(_BYTE *)(uintptr_t)(entryIndex + g_RuntimeGrowableByteFlagArrayPtr) )
      nfree_(j);
    entryCount = ((int)(intptr_t)j - g_CrtWideEnvironTable) >> 2;
    memmove_(j, (const void *)(uintptr_t)g_RuntimeGrowableByteFlagArrayPtr, (size_t)entryCount);
    g_RuntimeGrowableByteFlagArrayPtr = v13;
    flagBytePtr = (_BYTE *)(uintptr_t)(entryIndex + v13);
    while ( entryIndex < entryCount )
    {
      ++entryIndex;
      *flagBytePtr = flagBytePtr[1];
      ++flagBytePtr;
    }
  }
  return 0;
}
// 4E7259: variable 'a3' is possibly undefined
// 4E7273: variable 'v9' is possibly undefined
// 4E72C2: variable 'j' is possibly undefined
// 4E72D6: variable 'v13' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 4E7DBB: using guessed type int __thiscall towupper_(_DWORD);
// 54E700: using guessed type int dword_54E700;
// 54E708: using guessed type int dword_54E708;

//----- (004E7AAE) --------------------------------------------------------
DWORD __cdecl CRT_SpawnveLaunchProcess(int spawnMode, int a2 CLASH95_UNUSED, LPSTR lpCommandLine, LPVOID lpEnvironment, int a5)
{
  int v5; // ecx
  DWORD dwProcessId; // eax
  HANDLE v8; // eax
  HANDLE hProcess; // [esp-18h] [ebp-88h]
  HANDLE CurrentProcess; // [esp-14h] [ebp-84h]
  struct _STARTUPINFOA StartupInfo; // [esp+0h] [ebp-70h] BYREF
  struct _PROCESS_INFORMATION ProcessInformation; // [esp+44h] [ebp-2Ch] BYREF
  DWORD ExitCode; // [esp+54h] [ebp-1Ch] BYREF
  HANDLE TargetHandle; // [esp+58h] [ebp-18h] BYREF

  _ccmdline_(0, a5);
  memset_(v5, 0);
  StartupInfo.wShowWindow = 1;
  if ( !CreateProcessA(0, lpCommandLine, 0, 0, 1, 0, lpEnvironment, 0, &StartupInfo, &ProcessInformation) )
  {
    GetLastError();
    return _set_errno_dos_(StartupInfo.cb);
  }
  if ( spawnMode )
  {
    if ( spawnMode == 3 )
    {
      CloseHandle(ProcessInformation.hProcess);
      dwProcessId = ProcessInformation.dwProcessId;
    }
    else
    {
      CurrentProcess = GetCurrentProcess();
      hProcess = ProcessInformation.hProcess;
      v8 = GetCurrentProcess();
      if ( !DuplicateHandle(v8, hProcess, CurrentProcess, &TargetHandle, 0, 0, 2u) )
        TargetHandle = ProcessInformation.hProcess;
      dwProcessId = (DWORD)(intptr_t)TargetHandle;
    }
    ExitCode = dwProcessId;
LABEL_20:
    CloseHandle(ProcessInformation.hThread);
    return ExitCode;
  }
  if ( HIWORD(g_WindowsVersionDword) < 0x8000u || (unsigned __int8)g_WindowsVersionDword >= 4u )
  {
    if ( WaitForSingleObject(ProcessInformation.hProcess, 0xFFFFFFFF) )
      ExitCode = _set_errno_nt_(StartupInfo.cb);
    else
      GetExitCodeProcess(ProcessInformation.hProcess, &ExitCode);
LABEL_13:
    CloseHandle(ProcessInformation.hProcess);
    goto LABEL_20;
  }
  Sleep(0x3E8u);
  ExitCode = 259;
  while ( 1 )
  {
    Sleep(0x64u);
    if ( !GetExitCodeProcess(ProcessInformation.hProcess, &ExitCode) )
      return _set_errno_nt_(StartupInfo.cb);
    if ( ExitCode != 259 )
      goto LABEL_13;
  }
}
// 4E7AD5: variable 'v5' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 485306: using guessed type int __cdecl _set_errno_dos_(_DWORD);
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);
// 4E77CE: using guessed type int __fastcall _ccmdline_(_DWORD, _DWORD);
// 51A8A7: using guessed type int dword_51A8A7;

//----- (004E7CA5) --------------------------------------------------------
const CHAR * CRT_SetEnvironmentVariableCompat(const WCHAR *wideName, const WCHAR *wideValue, int a3)
{
  const CHAR *result; // eax
  int valueLen; // eax
  int v6; // edx
  int v7; // ecx
  const CHAR *ansiName; // ebp
  const CHAR *ansiValue; // esi
  int nameLen; // eax
  int v11; // edx
  int v12; // ecx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx

  if ( HIWORD(g_WindowsVersionDword) < 0x8000u )
    return (const CHAR *)(uintptr_t)SetEnvironmentVariableW(wideName, wideValue);
  valueLen = wcslen_(a3, wideValue);
  result = (const CHAR *)nmalloc_(2 * valueLen + 1, v6);
  ansiName = result;
  if ( result )
  {
    if ( wideValue )
    {
      nameLen = wcslen_(v7, result);
      ansiValue = (const CHAR *)nmalloc_(2 * nameLen + 1, v11);
      if ( !ansiValue )
        goto LABEL_9;
    }
    else
    {
      ansiValue = 0;
    }
    if ( wcstombs_(v7, wideName) == -1 )
    {
      nfree_(v12);
      if ( !ansiValue )
        return 0;
LABEL_9:
      nfree_(v7);
      return 0;
    }
    if ( ansiValue && wcstombs_(v12, wideValue) == -1 )
      goto LABEL_9;
    SetEnvironmentVariableA(ansiName, ansiValue);
    nfree_(v13);
    if ( ansiValue )
      nfree_(v15);
    return (const CHAR *)(uintptr_t)v14;
  }
  return result;
}
// 4E7CD2: variable 'v6' is possibly undefined
// 4E7CED: variable 'v7' is possibly undefined
// 4E7CF9: variable 'v11' is possibly undefined
// 4E7D1B: variable 'v12' is possibly undefined
// 4E7D50: variable 'v13' is possibly undefined
// 4E7D5B: variable 'v15' is possibly undefined
// 4E7D60: variable 'v14' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4D9743: using guessed type int __fastcall wcslen_(_DWORD, _DWORD);
// 4D9993: using guessed type int __fastcall wcstombs_(_DWORD, _DWORD);
// 51A8A7: using guessed type int dword_51A8A7;

//----- (004E7DDE) --------------------------------------------------------
// attributes: thunk
int CRT_InvokeIoInitHook(void)
{
  return g_CRT_InitHookPtr();
}
// 51A8BB: using guessed type int (*off_51A8BB)();

//----- (004E7DE5) --------------------------------------------------------
int CRT_DefaultZeroStub(void)
{
  return 0;
}

//----- (004E7DE8) --------------------------------------------------------
signed int  CRT_GetOsHandleFromFd(int fd, int a2)
{
  if ( fd >= 0 && fd <= (unsigned int)g_CRT_MaxFileDescriptor )
    return *(_DWORD *)(uintptr_t)(4 * fd + g_CRT_OsHandleTable);
  _set_errno_(a2);
  return -1;
}
// 51A768: using guessed type int dword_51A768;
// 51AED0: using guessed type int dword_51AED0;

//----- (004E7EB8) --------------------------------------------------------
unsigned int  CRT_MbcsBackUpOverLeadByte(unsigned int stringStart, unsigned int currentPos)
{
  unsigned __int8 *scanPtr; // eax

  if ( stringStart >= currentPos )
    return 0;
  scanPtr = (unsigned __int8 *)(uintptr_t)(currentPos - 1);
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*scanPtr] & 1) != 0 )
    return currentPos - 2;
  do
    --scanPtr;
  while ( stringStart <= (unsigned int)(intptr_t)scanPtr && g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[*scanPtr] & 1) != 0 );
  return currentPos - 1 - (int)(currentPos - (_DWORD)(intptr_t)scanPtr) % 2;
}
// 54E718: using guessed type int dword_54E718;

//----- (004E7F2D) --------------------------------------------------------
int  CRT_IsExtendedMbcsLeadByte(int a1, int a2)
{
  unsigned int mbChar; // edx

  if ( !ismbclegal_(a2, a1) )
    return IsTable[(unsigned __int8)(mbChar + 1)] & 0x80;
  return mbChar >= 0x8281 && mbChar <= 0x829A;
}
// 4E7F3F: variable 'v2' is possibly undefined
// 4E800B: using guessed type int __fastcall ismbclegal_(_DWORD, _DWORD);

//----- (004E7F70) --------------------------------------------------------
char * CRT_StrNCpyMbcsSafe(char *dest, const char *src, unsigned int count)
{
  const char *srcPtr; // esi
  unsigned int srcSize; // kr04_4
  unsigned int srcLen; // ecx
  char *destPtr; // edi
  char curChar; // al
  char nextChar; // al

  srcPtr = src;
  srcSize = strlen(src) + 1;
  srcLen = srcSize - 1;
  if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[(unsigned __int8)src[count]] & 1) != 0 && count < srcLen )
    --count;
  if ( srcSize > count )
  {
    qmemcpy(dest, src, count);
  }
  else
  {
    destPtr = dest;
    do
    {
      curChar = *srcPtr;
      *destPtr = *srcPtr;
      if ( !curChar )
        break;
      nextChar = srcPtr[1];
      srcPtr += 2;
      destPtr[1] = nextChar;
      destPtr += 2;
    }
    while ( nextChar );
    if ( srcLen != count )
      memset_(srcLen, 0);
  }
  return dest;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 54E718: using guessed type int dword_54E718;

// nfuncs=4362 queued=3899 decompiled=3899 lumina nreq=0 worse=0 better=0
// Remaining decompiler scars are tracked in docs/archive/COMPILATION_PROGRESS.md and are no longer fatal to parsing.
