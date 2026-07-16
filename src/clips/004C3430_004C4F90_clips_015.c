/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004C3430) --------------------------------------------------------
int  Rules_UnionConstraints(int constraint1, int constraint2)
{
  int c1Changed; // ebx
  _BYTE *newRecord; // eax
  int c2Changed; // ecx
  int theConstraint; // esi
  int rangeFlag; // ecx
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
    return Rules_CloneLHSParseNode((int *)(uintptr_t)constraint2);
  if ( !constraint2 )
    return Rules_CloneLHSParseNode((int *)(uintptr_t)constraint1);
  newRecord = (_BYTE *)(uintptr_t)Rules_CreateLHSParseNode();
  theConstraint = (int)(intptr_t)newRecord;
  if ( *(char *)(uintptr_t)(constraint1 + 1) < 0 || *(char *)(uintptr_t)(constraint2 + 1) < 0 )
    newRecord[1] |= 0x80u;
  if ( (*(_BYTE *)(uintptr_t)(constraint1 + 2) & 1) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 2) & 1) != 0 )
    newRecord[2] |= 1u;
  if ( (*(_BYTE *)(uintptr_t)constraint1 & 1) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 1) != 0 )
  {
    *newRecord |= 1u;
  }
  else
  {
    *newRecord &= ~1u;
    v10 = (*(_BYTE *)(uintptr_t)constraint1 & 2) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 2) != 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~2u;
    *(_DWORD *)(uintptr_t)theConstraint |= 2 * v10;
    v11 = (*(_BYTE *)(uintptr_t)constraint1 & 4) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 4) != 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~4u;
    *(_DWORD *)(uintptr_t)theConstraint |= 4 * v11;
    v12 = (*(_BYTE *)(uintptr_t)constraint1 & 8) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 8) != 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~8u;
    *(_DWORD *)(uintptr_t)theConstraint |= 8 * v12;
    v13 = (*(_BYTE *)(uintptr_t)constraint1 & 0x10) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 0x10) != 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~0x10u;
    *(_DWORD *)(uintptr_t)theConstraint |= 16 * v13;
    v14 = (*(_BYTE *)(uintptr_t)constraint1 & 0x20) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 0x20) != 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~0x20u;
    *(_DWORD *)(uintptr_t)theConstraint |= 32 * v14;
    v15 = (*(_BYTE *)(uintptr_t)constraint1 & 0x40) != 0 || (*(_BYTE *)(uintptr_t)constraint2 & 0x40) != 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~0x40u;
    *(_DWORD *)(uintptr_t)theConstraint |= v15 << 6;
    v16 = *(char *)(uintptr_t)constraint1 < 0 || *(char *)(uintptr_t)constraint2 < 0;
    *(_BYTE *)(uintptr_t)theConstraint &= ~0x80u;
    *(_DWORD *)(uintptr_t)theConstraint |= v16 << 7;
    v17 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 1) != 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 1) != 0;
    *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~1u;
    *(_DWORD *)(uintptr_t)theConstraint |= v17 << 8;
  }
  if ( (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 2) == 0 || (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 2) == 0 )
  {
    if ( (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 2) != 0 )
    {
      tmpConstraint = constraint1;
      c1Changed = 1;
    }
    else
    {
      if ( (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 2) == 0 )
      {
LABEL_61:
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~2u;
        v19 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 4) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 4) != 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~4u;
        *(_DWORD *)(uintptr_t)theConstraint |= v19 << 10;
        v20 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 8) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 8) != 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~8u;
        *(_DWORD *)(uintptr_t)theConstraint |= v20 << 11;
        v21 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 0x10) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 0x10) != 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x10u;
        *(_DWORD *)(uintptr_t)theConstraint |= v21 << 12;
        v22 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 0x20) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 0x20) != 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x20u;
        *(_DWORD *)(uintptr_t)theConstraint |= v22 << 13;
        v23 = (*(_BYTE *)(uintptr_t)(constraint1 + 1) & 0x40) != 0 && (*(_BYTE *)(uintptr_t)(constraint2 + 1) & 0x40) != 0;
        *(_BYTE *)(uintptr_t)(theConstraint + 1) &= ~0x40u;
        *(_DWORD *)(uintptr_t)theConstraint |= v23 << 14;
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
  *(_BYTE *)(uintptr_t)(theConstraint + 1) |= 2u;
LABEL_14:
  Rules_UnionAllowedValueExpressions(constraint1, constraint2, theConstraint);
  Rules_UnionNumericExpressions((__int16 *)(uintptr_t)constraint1, constraint2, rangeFlag, theConstraint);
  Rules_UnionNumericExpressions((__int16 *)(uintptr_t)constraint1, constraint2, 0, theConstraint);
  if ( *(char *)(uintptr_t)(theConstraint + 1) < 0 )
    *(_DWORD *)(uintptr_t)(theConstraint + 26) = Rules_UnionConstraints(*(_DWORD *)(uintptr_t)(constraint1 + 26), *(_DWORD *)(uintptr_t)(constraint2 + 26));
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
  int otherConstraint; // [esp+8h] [ebp-14h]
  int rangeFlag; // [esp+Ch] [ebp-10h]

  otherConstraint = constraint2;
  rangeFlag = range;
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
    result = Rules_UnionRangeMinMaxValueWithList((__int16 *)(uintptr_t)tmpmin, (__int16 *)(uintptr_t)tmpmax, &theMaxList, &theMinList);
    tmpmin = *(_DWORD *)(uintptr_t)(tmpmin + 10);
    tmpmax = *(_DWORD *)(uintptr_t)(tmpmax + 10);
  }
  if ( rangeFlag )
  {
    tmpmin2 = *(_DWORD *)(uintptr_t)(otherConstraint + 10);
    tmpmax2 = *(_DWORD *)(uintptr_t)(otherConstraint + 14);
  }
  else
  {
    tmpmin2 = *(_DWORD *)(uintptr_t)(otherConstraint + 18);
    tmpmax2 = *(_DWORD *)(uintptr_t)(otherConstraint + 22);
  }
  while ( tmpmin2 )
  {
    result = Rules_UnionRangeMinMaxValueWithList((__int16 *)(uintptr_t)tmpmin2, (__int16 *)(uintptr_t)tmpmax2, &theMaxList, &theMinList);
    tmpmin2 = *(_DWORD *)(uintptr_t)(tmpmin2 + 10);
    tmpmax2 = *(_DWORD *)(uintptr_t)(tmpmax2 + 10);
  }
  if ( theMinList )
  {
    if ( rangeFlag )
    {
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 10));
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 14));
      *(_DWORD *)(uintptr_t)(newConstraint + 10) = theMinList;
      result = theMaxList;
      *(_DWORD *)(uintptr_t)(newConstraint + 14) = theMaxList;
    }
    else
    {
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 18));
      AST_Free(*(_DWORD *)(uintptr_t)(newConstraint + 22));
      *(_DWORD *)(uintptr_t)(newConstraint + 18) = theMinList;
      result = theMaxList;
      *(_DWORD *)(uintptr_t)(newConstraint + 22) = theMaxList;
    }
  }
  else if ( rangeFlag )
  {
    if ( (*(_BYTE *)(uintptr_t)newConstraint & 1) != 0 )
      result = (__int16 *)Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)newConstraint, 0);
    *(_BYTE *)(uintptr_t)newConstraint &= 0xE7u;
  }
  else
  {
    result = (__int16 *)Rules_SetLHSParseNodeDefaultFlags((_BYTE *)(uintptr_t)newConstraint, 1);
    *(_BYTE *)(uintptr_t)newConstraint |= 1u;
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
      result = (__int16 *)(uintptr_t)Rules_CompareBoundedCEValues(*theMin, *(_DWORD *)(theMin + 1), *(_DWORD *)(tmpmax + 1), *tmpmax);
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
        result = (__int16 *)(uintptr_t)AST_NewNode(*theMax, *(_DWORD *)(theMax + 1));
        *(_DWORD *)(uintptr_t)(newMinNode + 10) = *theMinList;
        *(_DWORD *)(result + 5) = *theMaxList;
        *theMinList = (__int16 *)(uintptr_t)newMinNode;
        *theMaxList = result;
        return result;
      }
      tmpmin = *(__int16 **)(tmpmin + 5);
      tmpmax = *(__int16 **)(tmpmax + 5);
      if ( !tmpmin )
      {
        result = *theMinList;
        maxCursor = *theMaxList;
        minCursor = (signed int)(intptr_t)*theMinList;
        if ( *theMinList )
        {
          while ( 1 )
          {
            nextMin = *(_DWORD **)(uintptr_t)(minCursor + 10);
            nextMax = *(_DWORD *)(maxCursor + 5);
            if ( !nextMin )
              break;
            mergeCompare = Rules_CompareBoundedCEValues(*maxCursor, *(_DWORD *)(maxCursor + 1), *(_DWORD *)((char *)nextMin + 2), *(__int16 *)nextMin);
            if ( mergeCompare == 1 || mergeCompare == 2 )
            {
              *maxCursor = *(_WORD *)(uintptr_t)nextMax;
              *(_DWORD *)(maxCursor + 1) = *(_DWORD *)(uintptr_t)(nextMax + 2);
              *(_DWORD *)(maxCursor + 5) = *(_DWORD *)(uintptr_t)(nextMax + 10);
              *(_DWORD *)(uintptr_t)(minCursor + 10) = *(_DWORD *)((char *)nextMin + 10);
              g_ClipsMemFreeListTemp = (int)(intptr_t)nextMin;
              *nextMin = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
              *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
              g_ClipsMemFreeListTemp = nextMax;
              *(_DWORD *)(uintptr_t)nextMax = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
              result = (__int16 *)(uintptr_t)g_ClipsMemoryTable;
              *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
              if ( !minCursor )
                return result;
            }
            else
            {
              result = *(__int16 **)(uintptr_t)(minCursor + 10);
              maxCursor = *(__int16 **)(maxCursor + 5);
              minCursor = (signed int)(intptr_t)result;
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
    *theMinList = (__int16 *)(uintptr_t)AST_NewNode(*theMin, *(_DWORD *)(theMin + 1));
    result = (__int16 *)(uintptr_t)AST_NewNode(*theMax, *(_DWORD *)(theMax + 1));
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

  theHead = Rules_AddToUnionList(*(__int16 **)(uintptr_t)(constraint1 + 6), 0, newConstraint);
  result = Rules_AddToUnionList(*(__int16 **)(uintptr_t)(constraint2 + 6), theHead, v5);
  *(_DWORD *)(uintptr_t)(v7 + 6) = result;
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
        result = (__int16 *)(uintptr_t)AST_NewNode(*theItem, *(_DWORD *)(theItem + 1));
        *(_DWORD *)(result + 5) = theHead;
        theHead = result;
        theItem = *(__int16 **)(uintptr_t)(v7 + 10);
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
    theList = *(__int16 **)(uintptr_t)(theConstraint + 6);
    *(_DWORD *)(uintptr_t)(theConstraint + 6) = 0;
    while ( theList )
    {
      if ( *theList == theType && theValue == *(_DWORD *)(theList + 1) )
      {
        *(_DWORD *)(theList + 5) = 0;
        AST_Free((int)(intptr_t)theList);
      }
      else
      {
        if ( lastOne )
          *(_DWORD *)(lastOne + 5) = theList;
        else
          *(_DWORD *)(uintptr_t)(theConstraint + 6) = theList;
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
signed int Rules_RegisterDefglobalBinaryItem(void)
{
  Rules_AddAfterBloadFunction((int)(intptr_t)aDefglobal_1, (int)(intptr_t)Defglobal_ResetAllDefglobals, 50);
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDefglobal_1,
           0,
           0,
           (int)(intptr_t)Rules_BsaveFindDefglobals,
           (int)(intptr_t)Rules_BsaveDefglobalStorage,
           (int)(intptr_t)Rules_BsaveDefglobals,
           (int)(intptr_t)Rules_BloadDefglobalStorage,
           (int)(intptr_t)Rules_BloadDefglobals,
           (int)(intptr_t)Rules_ClearDefglobalBload);
}

//----- (004C3CF0) --------------------------------------------------------
int Rules_BsaveFindDefglobals(void)
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
    for ( j = (_DWORD *)(uintptr_t)Defglobal_EnumNext(0); j; j = (_DWORD *)(uintptr_t)Defglobal_EnumNext(v4) )
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
    theItem = Module_FindItemByName((int)(intptr_t)aDefglobal_1);
    theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(0, *(_DWORD *)(uintptr_t)(theItem + 4));
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
      dummyGlobal[3] = AST_GetHashedNodeIndex(*(__int16 **)(uintptr_t)(v8 + 52));
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
signed int Rules_BloadDefglobalStorage(void)
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
  result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * g_DefglobalModuleItemCount));
  g_ClipsDefglobalModuleItemArray = result;
  if ( g_Defglobal_Count )
  {
    space[0] = 56 * g_Defglobal_Count;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(56 * g_Defglobal_Count));
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
signed int Rules_BloadDefglobals(void)
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
  return Module_UpdateItemHeader(buf, (_DWORD *)(uintptr_t)(12 * obji + g_ClipsDefglobalModuleItemArray), g_DefglobalBloadRecords, 56);
}
// 51B370: using guessed type int dword_51B370;
// 54E890: using guessed type int dword_54E890;

//----- (004C4050) --------------------------------------------------------
int  Rules_UpdateDefglobal(int buf, int obji)
{
  int recordOffset; // ebp
  int recordsBase; // eax
  char watchFlag; // dl
  int initialIndex; // ebx
  int initialExpr; // edx
  int result; // eax

  recordOffset = 56 * obji;
  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(uintptr_t)(56 * obji + g_DefglobalBloadRecords), g_ClipsDefglobalModuleItemArray, 12, 56, g_DefglobalBloadRecords);
  recordsBase = g_DefglobalBloadRecords;
  watchFlag = g_Rules_WatchGlobals;
  *(_BYTE *)(uintptr_t)(g_DefglobalBloadRecords + recordOffset + 20) &= ~1u;
  *(_DWORD *)(uintptr_t)(recordsBase + recordOffset + 20) |= watchFlag & 1;
  initialIndex = *(_DWORD *)(uintptr_t)(buf + 12);
  if ( initialIndex == -1 )
    initialExpr = 0;
  else
    initialExpr = 14 * initialIndex + g_ClipsPackedExpressionArray;
  result = 56 * obji;
  *(_DWORD *)(uintptr_t)(g_DefglobalBloadRecords + result + 52) = initialExpr;
  *(_DWORD *)(uintptr_t)(g_DefglobalBloadRecords + result + 32) = 105;
  return result;
}
// 51B370: using guessed type int dword_51B370;
// 51B3EC: using guessed type int dword_51B3EC;
// 54E688: using guessed type int dword_54E688;
// 54E890: using guessed type int dword_54E890;

//----- (004C4100) --------------------------------------------------------
signed int Rules_ClearDefglobalBload(void)
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
      Rules_ReleaseSymbolReference((int *)(uintptr_t)(recordOffset + g_DefglobalBloadRecords), globalIndex);
      Rules_ValueDeinstall(v2 + g_DefglobalBloadRecords + 28, v3);
      if ( *(_DWORD *)(uintptr_t)(v4 + g_DefglobalBloadRecords + 32) == 4 )
        Rules_ReturnMultifieldToPool(*(_DWORD **)(uintptr_t)(v4 + g_DefglobalBloadRecords + 36));
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
signed int Defgeneric_RegisterBinaryItem(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aGenericFunct_0,
           0,
           (int)(intptr_t)Defgeneric_BsaveWriteExpressions,
           (int)(intptr_t)Defgeneric_CountBsaveEntries,
           (int)(intptr_t)Defgeneric_BsaveWriteBinaryHeader,
           (int)(intptr_t)Defgeneric_BsaveWriteConstructs,
           (int)(intptr_t)Defgeneric_BloadAllocateBinaryStorage,
           (int)(intptr_t)Defgeneric_BloadRefreshConstructs,
           (int)(intptr_t)Defgeneric_ClearBinaryData);
}

//----- (004C4210) --------------------------------------------------------
int  Defgeneric_RecordAtIndex(int theIndex)
{
  return 12 * theIndex + g_DefgenericBloadModuleRefArray;
}
// 51B390: using guessed type int dword_51B390;

//----- (004C4230) --------------------------------------------------------
signed int Defgeneric_CountBsaveEntries(void)
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
  result = *(_DWORD *)(uintptr_t)(v2 + 32);
  g_Defgeneric_RestrictionRecordCount += result;
  methodIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(v2 + 32) )
  {
    methodOffset = 0;
    do
    {
      theMethod = (_DWORD *)(uintptr_t)(methodOffset + theDefgeneric[7]);
      g_ClipsExpressionNodeIndex += AST_CountTreeNodes(theMethod[8]);
      Rules_MarkReferencedFunctions((__int16 *)(uintptr_t)theMethod[8]);
      g_Defgeneric_RestrictionTypeCount += theMethod[2];
      restrictionIndex = 0;
      if ( theMethod[2] )
      {
        restrictionOffset = 0;
        do
        {
          g_ClipsExpressionNodeIndex += AST_CountTreeNodes(*(_DWORD *)(uintptr_t)(restrictionOffset + theMethod[7] + 4));
          Rules_MarkReferencedFunctions(*(__int16 **)(uintptr_t)(v10 + v9 + 4));
          g_Defgeneric_PackedExpressionCount += *(_DWORD *)(uintptr_t)(v12 + v11 + 8);
          ++restrictionIndex;
          restrictionOffset = v12 + 12;
        }
        while ( restrictionIndex < theMethod[2] );
      }
      result = (int)(intptr_t)theDefgeneric;
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
signed int Defgeneric_BsaveWriteExpressions(void)
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

  theDefgeneric = (int)(intptr_t)result;
  methodIndex = 0;
  if ( *((_DWORD *)result + 8) )
  {
    methodOffset = 0;
    do
    {
      ++methodIndex;
      result = Rules_BsaveWriteExpression(*(__int16 **)(uintptr_t)(methodOffset + *(_DWORD *)(uintptr_t)(theDefgeneric + 28) + 32), fp);
      methodOffset = v6 + 40;
    }
    while ( methodIndex < *(_DWORD *)(uintptr_t)(theDefgeneric + 32) );
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

  theDefgeneric = (int)(intptr_t)result;
  methodIndex = 0;
  if ( *((_DWORD *)result + 8) )
  {
    methodOffset = 0;
    do
    {
      theMethod = methodOffset + *(_DWORD *)(uintptr_t)(theDefgeneric + 28);
      result = *(__int16 **)(uintptr_t)(theMethod + 8);
      restrictionIndex = 0;
      if ( result )
      {
        restrictionOffset = 0;
        do
        {
          ++restrictionIndex;
          result = Rules_BsaveWriteExpression(*(__int16 **)(uintptr_t)(restrictionOffset + *(_DWORD *)(uintptr_t)(theMethod + 28) + 4), fp);
          restrictionOffset = v7 + 12;
        }
        while ( restrictionIndex < *(_DWORD *)(uintptr_t)(theMethod + 8) );
      }
      methodOffset += 40;
      ++methodIndex;
    }
    while ( methodIndex < *(_DWORD *)(uintptr_t)(theDefgeneric + 32) );
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
      theItem = Module_FindItemByName((int)(intptr_t)aDefgeneric_2);
      theModuleItem = (_DWORD *)(uintptr_t)Module_GetItem(v4, *(_DWORD *)(uintptr_t)(theItem + 4));
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
  int methodsIndex CLASH95_UNUSED; // [esp+0h] [ebp-10h]
  int methodCount CLASH95_UNUSED; // [esp+4h] [ebp-Ch]
  int v9 CLASH95_UNUSED; // [esp+8h] [ebp-8h]

  v9 = a3;
  AST_ExtractPatternBindingInfo(dummyGeneric, theDefgeneric);
  methodCount = *(_DWORD *)(uintptr_t)(v4 + 32);
  if ( *(_DWORD *)(uintptr_t)(v4 + 28) )
  {
    methodsIndex = g_Defgeneric_RestrictionRecordCount;
    g_Defgeneric_RestrictionRecordCount += *(_DWORD *)(uintptr_t)(v4 + 32);
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
  int restrictionsIndex CLASH95_UNUSED; // [esp+18h] [ebp-1Ch]
  int actionsIndex CLASH95_UNUSED; // [esp+1Ch] [ebp-18h]

  theDefgeneric = (int)(intptr_t)result;
  methodIndex = 0;
  if ( result[8] )
  {
    methodOffset = 0;
    do
    {
      theMethod = (_DWORD *)(uintptr_t)(methodOffset + *(_DWORD *)(uintptr_t)(theDefgeneric + 28));
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
    while ( methodIndex < *(_DWORD *)(uintptr_t)(theDefgeneric + 32) );
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
  int queryIndex CLASH95_UNUSED; // [esp+4h] [ebp-28h]
  int typeCount CLASH95_UNUSED; // [esp+8h] [ebp-24h]
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
        result = (_DWORD *)(uintptr_t)(v15 + theDefgeneric[7]);
        if ( restrictionIndex >= result[2] )
          break;
        theRestriction = (_DWORD *)(uintptr_t)(restrictionOffset + result[7]);
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
        result = (_DWORD *)(uintptr_t)(v13 + theDefgeneric[7]);
        if ( restrictionIndex >= result[2] )
          break;
        theRestriction = (_DWORD *)(uintptr_t)(restrictionOffset + result[7]);
        if ( theRestriction[2] )
        {
          typeOffset = 0;
          do
          {
            typeAddr = typeOffset + *theRestriction;
            if ( *(_DWORD *)(uintptr_t)typeAddr )
              classIndex = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)typeAddr + 12);
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
int Defgeneric_BloadAllocateBinaryStorage(void)
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
      result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * counts[0]));
      g_DefgenericBloadModuleRefArray = result;
      if ( g_Defgeneric_MethodRecordCount )
      {
        space[0] = 40 * g_Defgeneric_MethodRecordCount;
        result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(40 * g_Defgeneric_MethodRecordCount));
        g_DefgenericMethodArray = result;
        if ( g_Defgeneric_RestrictionRecordCount )
        {
          space[0] = 40 * g_Defgeneric_RestrictionRecordCount;
          result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(40 * g_Defgeneric_RestrictionRecordCount));
          g_DefgenericRestrictionRecords = result;
          if ( g_Defgeneric_RestrictionTypeCount )
          {
            space[0] = 12 * g_Defgeneric_RestrictionTypeCount;
            result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * g_Defgeneric_RestrictionTypeCount));
            g_ClipsDefgenericBloadRestrictionTypeArray = result;
            if ( g_Defgeneric_PackedExpressionCount )
            {
              space[0] = 4 * g_Defgeneric_PackedExpressionCount;
              result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(4 * g_Defgeneric_PackedExpressionCount));
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
  return Module_UpdateItemHeader(buf, (_DWORD *)(uintptr_t)(12 * obji + g_DefgenericBloadModuleRefArray), g_DefgenericMethodArray, 40);
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
  Rules_BuildIndexedSlotDescriptor(buf, (_DWORD *)(uintptr_t)(g_DefgenericMethodArray + 40 * obji), g_DefgenericBloadModuleRefArray, 12, 40, g_DefgenericMethodArray);
  *(_DWORD *)(uintptr_t)(g_DefgenericMethodArray + methodOffset + 20) = 0;
  *(_DWORD *)(uintptr_t)(g_DefgenericMethodArray + methodOffset + 24) = g_Rules_WatchGenericFunctions;
  restrictionsIndex = *(_DWORD *)(uintptr_t)(buf + 12);
  if ( restrictionsIndex == -1 )
    restrictionsPtr = 0;
  else
    restrictionsPtr = 40 * restrictionsIndex + g_DefgenericRestrictionRecords;
  result = 5 * obji;
  *(_DWORD *)(uintptr_t)(g_DefgenericMethodArray + 8 * result + 28) = restrictionsPtr;
  *(_DWORD *)(uintptr_t)(g_DefgenericMethodArray + 8 * result + 32) = *(_DWORD *)(uintptr_t)(buf + 16);
  *(_DWORD *)(uintptr_t)(g_DefgenericMethodArray + 8 * result + 36) = 0;
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
  int recordsBase; // ecx
  char watchFlag; // di
  int recordPtr; // edx
  int v7; // ecx
  int typesIndex; // ebp
  int typesPtr; // ecx
  int queryIndex; // eax
  int queryPtr; // edx
  int result; // eax

  restrictionOffset = 40 * obji;
  *(_DWORD *)(uintptr_t)(restrictionOffset + g_DefgenericRestrictionRecords) = *buf;
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + restrictionOffset + 4) = 0;
  recordsBase = g_DefgenericRestrictionRecords;
  watchFlag = g_Rules_WatchMethods;
  *(_BYTE *)(uintptr_t)(g_DefgenericRestrictionRecords + restrictionOffset + 24) &= ~2u;
  *(_DWORD *)(uintptr_t)(recordsBase + restrictionOffset + 24) |= 2 * (watchFlag & 1);
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + restrictionOffset + 8) = buf[1];
  *(_DWORD *)(uintptr_t)(restrictionOffset + g_DefgenericRestrictionRecords + 12) = buf[2];
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + restrictionOffset + 16) = buf[3];
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + restrictionOffset + 20) = buf[4];
  recordPtr = g_DefgenericRestrictionRecords + restrictionOffset;
  v7 = buf[5];
  *(_BYTE *)(uintptr_t)(recordPtr + 24) &= ~1u;
  *(_DWORD *)(uintptr_t)(recordPtr + 24) |= v7 & 1;
  typesIndex = buf[6];
  if ( typesIndex == -1 )
    typesPtr = 0;
  else
    typesPtr = 12 * typesIndex + g_ClipsDefgenericBloadRestrictionTypeArray;
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + 40 * obji + 28) = typesPtr;
  queryIndex = buf[7];
  if ( queryIndex == -1 )
    queryPtr = 0;
  else
    queryPtr = 14 * queryIndex + g_ClipsPackedExpressionArray;
  result = 5 * obji;
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + 8 * result + 32) = queryPtr;
  *(_DWORD *)(uintptr_t)(g_DefgenericRestrictionRecords + 8 * result + 36) = 0;
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

  *(_DWORD *)(uintptr_t)(12 * obji + g_ClipsDefgenericBloadRestrictionTypeArray + 8) = buf[2];
  if ( *buf == -1 )
    typesPtr = 0;
  else
    typesPtr = g_DefgenericBloadRestrictionTypeArray + 4 * *buf;
  *(_DWORD *)(uintptr_t)(g_ClipsDefgenericBloadRestrictionTypeArray + 12 * obji) = typesPtr;
  exprIndex = buf[1];
  if ( exprIndex == -1 )
    exprPtr = 0;
  else
    exprPtr = 14 * exprIndex + g_ClipsPackedExpressionArray;
  result = 3 * obji;
  *(_DWORD *)(uintptr_t)(g_ClipsDefgenericBloadRestrictionTypeArray + 12 * obji + 4) = exprPtr;
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
    *(_DWORD *)(uintptr_t)(g_DefgenericBloadRestrictionTypeArray + 4 * obji) = 0;
  }
  else
  {
    result = g_Clips_DefclassArrayBase + 124 * *buf;
    *(_DWORD *)(uintptr_t)(g_DefgenericBloadRestrictionTypeArray + 4 * obji) = result;
  }
  return result;
}
// 51B39C: using guessed type int dword_51B39C;
// 51B3AC: using guessed type int dword_51B3AC;

//----- (004C4E10) --------------------------------------------------------
signed int Defgeneric_ClearBinaryData(void)
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
      Rules_ReleaseSymbolReference((int *)(uintptr_t)(recordOffset + g_DefgenericMethodArray), methodIndex + 1);
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
signed int Deffunction_RegisterBinaryItem(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aDeffunctions_0,
           0,
           (int)(intptr_t)Deffunction_BsaveWriteExpressions,
           (int)(intptr_t)Deffunction_CountBsaveEntries,
           (int)(intptr_t)Deffunction_BsaveWriteBinaryHeader,
           (int)(intptr_t)Deffunction_BsaveWriteConstructs,
           (int)(intptr_t)Deffunction_BloadAllocateBinaryStorage,
           (int)(intptr_t)Deffunction_BloadRefreshConstructs,
           (int)(intptr_t)Deffunction_ClearBinaryData);
}

//----- (004C4F90) --------------------------------------------------------
int  Deffunction_RecordAtIndex(int theIndex)
{
  return 12 * theIndex + g_Clips_DeffunctionRecordArray;
}
// 54E894: using guessed type int dword_54E894;
