/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004BEF30) --------------------------------------------------------
int  Rules_ListDefruleMatches(_DWORD *theDefrule, int a2)
{
  _DWORD *lastJoin; // edi
  int patternCount; // ebp
  int alphaSlot; // edx
  signed int alphaArray; // ecx
  _DWORD *joinNode; // eax
  int alphaWritePtr; // esi
  int patternIndex; // esi
  int *alphaPtr; // ebx
  int result; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int match; // ecx
  int joinCount; // ebp
  signed int betaArray; // ecx
  int betaSlot; // eax
  _DWORD *joinWalk; // edx
  int betaWritePtr; // esi
  int joinIndex; // esi
  int *betaPtr; // edi
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int betaMatch; // ecx
  int i; // ebx
  _DWORD *betaMatchNode; // ecx
  int v28; // ecx
  int v29; // ecx
  _DWORD **activation; // edi
  _DWORD *alphaMatchNode; // ecx
  int v32; // ecx
  int v33; // ecx
  _DWORD *theDisjunct; // [esp+4h] [ebp-20h]
  int alphaBlock; // [esp+8h] [ebp-1Ch]
  int betaBlock; // [esp+8h] [ebp-1Ch]

  theDisjunct = theDefrule;
  if ( theDefrule )
  {
    while ( 1 )
    {
      lastJoin = (_DWORD *)(uintptr_t)theDisjunct[11];
      patternCount = Rules_CountJoinNetworkEntryNodes((int)(intptr_t)lastJoin);
      alphaSlot = patternCount - 1;
      alphaArray = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * patternCount));
      alphaBlock = alphaArray;
      joinNode = lastJoin;
      if ( lastJoin )
      {
        alphaWritePtr = alphaArray + 4 * alphaSlot;
        do
        {
          if ( (*(_BYTE *)joinNode & 4) != 0 )
          {
            joinNode = (_DWORD *)(uintptr_t)joinNode[4];
          }
          else
          {
            alphaWritePtr -= 4;
            *(_DWORD *)(uintptr_t)(alphaWritePtr + 4) = *(_DWORD *)(uintptr_t)joinNode[4];
            --alphaSlot;
            joinNode = (_DWORD *)(uintptr_t)joinNode[6];
          }
        }
        while ( joinNode );
      }
      patternIndex = 0;
      if ( patternCount > 0 )
        break;
LABEL_16:
      Mem_ReleasePoolBlock(alphaBlock, 12 * patternCount);
      joinCount = *lastJoin << 16 >> 25;
      betaArray = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(12 * joinCount));
      betaBlock = betaArray;
      betaSlot = joinCount - 1;
      joinWalk = lastJoin;
      if ( joinCount - 1 >= 0 )
      {
        betaWritePtr = betaArray + 4 * betaSlot;
        do
        {
          betaWritePtr -= 4;
          *(_DWORD *)(uintptr_t)(betaWritePtr + 4) = joinWalk[2];
          --betaSlot;
          joinWalk = (_DWORD *)(uintptr_t)joinWalk[6];
        }
        while ( betaSlot >= 0 );
      }
      joinIndex = 1;
      if ( joinCount > 1 )
      {
        betaPtr = (int *)(uintptr_t)(betaArray + 4);
        do
        {
          result = Rules_GetEvaluationErrorFlag();
          if ( result == 1 )
            return result;
          Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aPartialMatches, v22);
          Rules_PrintLongInteger(v23, joinIndex + 1);
          Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50A998, v24);
          betaMatch = *betaPtr;
          for ( i = 0; betaMatch; betaMatch = betaMatchNode[1] )
          {
            result = Rules_GetEvaluationErrorFlag();
            if ( result == 1 )
              return result;
            if ( (*(_BYTE *)betaMatchNode & 0x20) == 0 )
            {
              Rules_PrintArgumentValueList((int)(intptr_t)g_IO_LogicalName_WDisplay, betaMatchNode);
              ++i;
              Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50A998, v28);
            }
          }
          if ( !i )
            Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aNone_3, betaMatch);
          ++joinIndex;
          ++betaPtr;
        }
        while ( joinIndex < joinCount );
      }
      Mem_ReleasePoolBlock(betaBlock, 12 * joinCount);
      theDisjunct = (_DWORD *)(uintptr_t)theDisjunct[12];
      if ( !theDisjunct )
        goto LABEL_31;
    }
    alphaPtr = (int *)(uintptr_t)alphaArray;
    while ( 1 )
    {
      result = Rules_GetEvaluationErrorFlag();
      if ( result == 1 )
        break;
      Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aMatchesForPatt, v11);
      Rules_PrintLongInteger(v12, patternIndex + 1);
      Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50A998, v13);
      match = *alphaPtr;
      if ( !*alphaPtr )
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aNone_3, 0);
      while ( match )
      {
        result = Rules_GetEvaluationErrorFlag();
        if ( result == 1 )
          return result;
        Rules_PrintArgumentValueList((int)(intptr_t)g_IO_LogicalName_WDisplay, alphaMatchNode);
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50A998, v32);
        match = *(_DWORD *)(uintptr_t)(v33 + 4);
      }
      ++patternIndex;
      ++alphaPtr;
      if ( patternIndex >= patternCount )
        goto LABEL_16;
    }
  }
  else
  {
LABEL_31:
    Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aActivations_1, a2);
    activation = (_DWORD **)(uintptr_t)Rules_GetNextActivation(0);
    if ( activation )
    {
      while ( 1 )
      {
        result = Rules_GetEvaluationErrorFlag();
        if ( result == 1 )
          break;
        if ( *theDefrule == **activation )
        {
          Rules_PrintArgumentValueList((int)(intptr_t)g_IO_LogicalName_WDisplay, activation[1]);
          Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_50A998, 0);
        }
        activation = (_DWORD **)(uintptr_t)Rules_GetNextActivation((int)(intptr_t)activation);
        if ( !activation )
          goto LABEL_36;
      }
    }
    else
    {
LABEL_36:
      if ( v29 )
        Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)aNone_3, v29);
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
void  Rules_FreeDefruleDisjunctChain(int theDefrule)
{
  int currentDisjunct; // ebx
  int v2; // ecx
  int nextDisjunct; // eax

  currentDisjunct = theDefrule;
  if ( theDefrule )
  {
    g_ClipsDefrulePreservedWatchBreakFlags = (*(_BYTE *)(uintptr_t)(theDefrule + 29) & 8) != 0;
    if ( (*(_BYTE *)(uintptr_t)(theDefrule + 29) & 0x10) != 0 )
      LOBYTE(g_ClipsDefrulePreservedWatchBreakFlags) = g_ClipsDefrulePreservedWatchBreakFlags | 2;
    if ( (*(_BYTE *)(uintptr_t)(theDefrule + 29) & 0x20) != 0 )
      LOBYTE(g_ClipsDefrulePreservedWatchBreakFlags) = g_ClipsDefrulePreservedWatchBreakFlags | 4;
    Rules_ClearActivationsForRule(theDefrule);
    do
    {
      Rules_RemoveJoinNetworkNodes(currentDisjunct);
      if ( v2 )
      {
        if ( *(_DWORD *)(uintptr_t)(currentDisjunct + 32) )
        {
          AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentDisjunct + 32));
          AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(currentDisjunct + 32));
          *(_DWORD *)(uintptr_t)(currentDisjunct + 32) = 0;
        }
        if ( *(_DWORD *)(uintptr_t)(currentDisjunct + 4) )
        {
          Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentDisjunct + 4), strlen((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentDisjunct + 4)) + 1);
          *(_DWORD *)(uintptr_t)(currentDisjunct + 4) = 0;
        }
        v2 = 0;
      }
      Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)currentDisjunct, v2);
      if ( *(_DWORD *)(uintptr_t)(currentDisjunct + 36) )
      {
        AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentDisjunct + 36));
        AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(currentDisjunct + 36));
      }
      nextDisjunct = *(_DWORD *)(uintptr_t)(currentDisjunct + 48);
      g_ClipsMemFreeListTemp = currentDisjunct;
      *(_DWORD *)(uintptr_t)currentDisjunct = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208) = g_ClipsMemFreeListTemp;
      currentDisjunct = nextDisjunct;
    }
    while ( nextDisjunct );
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
  _DWORD *theJoin; // edx
  int remainingLinks; // ecx
  _DWORD *v3; // ebx
  _DWORD *parentJoin; // esi
  int v5; // edx
  __int16 *networkTest; // eax
  int v7; // ecx
  _DWORD *joinToFree; // edx
  _DWORD *currentLink; // eax
  _DWORD *prevLink; // ecx

  theJoin = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(result + 44);
  *(_DWORD *)(uintptr_t)(result + 44) = 0;
  if ( theJoin )
  {
    remainingLinks = theJoin[5];
    theJoin[9] = 0;
    if ( !remainingLinks )
    {
      while ( 1 )
      {
        v3 = (_DWORD *)(uintptr_t)theJoin[6];
        if ( (*(_BYTE *)theJoin & 4) != 0 )
          parentJoin = (_DWORD *)(uintptr_t)theJoin[4];
        else
          parentJoin = 0;
        if ( theJoin[4] && (*(_BYTE *)theJoin & 4) == 0 )
          Rules_UnlinkJoinNetworkNode(theJoin);
        Rules_ReleaseJoinNetworkNodeChain(theJoin[2]);
        networkTest = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 12);
        *(_DWORD *)(uintptr_t)(v5 + 8) = 0;
        AST_RemoveHashedNodeChain(networkTest, v7);
        g_ClipsMemFreeListTemp = (int)(intptr_t)joinToFree;
        *joinToFree = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160);
        result = g_ClipsMemoryTable;
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 160) = g_ClipsMemFreeListTemp;
        if ( !v3 )
          break;
        currentLink = (_DWORD *)(uintptr_t)v3[5];
        prevLink = 0;
        if ( currentLink )
        {
          while ( currentLink != joinToFree )
          {
            prevLink = currentLink;
            currentLink = (_DWORD *)(uintptr_t)currentLink[7];
            if ( !currentLink )
              goto LABEL_13;
          }
          if ( prevLink )
            prevLink[7] = joinToFree[7];
          else
            v3[5] = joinToFree[7];
        }
LABEL_13:
        if ( parentJoin )
        {
          v3 = parentJoin;
          parentJoin[5] = 0;
        }
        result = v3[9];
        if ( result || v3[5] )
          break;
        theJoin = v3;
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
_DWORD * Rules_UnlinkJoinNetworkNode(_DWORD *theJoin)
{
  int *parentJoin; // ebx
  _DWORD *result; // eax
  int prevLink; // ecx

  parentJoin = (int *)(uintptr_t)theJoin[4];
  result = (_DWORD *)(uintptr_t)parentJoin[2];
  prevLink = 0;
  if ( result )
  {
    do
    {
      if ( result == theJoin )
      {
        result = (_DWORD *)(uintptr_t)theJoin[8];
        if ( prevLink )
          *(_DWORD *)(uintptr_t)(prevLink + 32) = result;
        else
          parentJoin[2] = (int)(intptr_t)result;
        goto LABEL_5;
      }
      prevLink = (int)(intptr_t)result;
      result = (_DWORD *)(uintptr_t)result[8];
    }
    while ( result );
    if ( parentJoin[2] )
      return result;
    return (_DWORD *)(uintptr_t)Rules_DeletePatternNetworkForType(*theJoin << 23 >> 29, parentJoin, prevLink);
  }
LABEL_5:
  if ( !parentJoin[2] )
    return (_DWORD *)(uintptr_t)Rules_DeletePatternNetworkForType(*theJoin << 23 >> 29, parentJoin, prevLink);
  return result;
}

//----- (004BF450) --------------------------------------------------------
signed int  Rules_ParseDefrule(int readSource, double a2)
{
  int theDefrule; // eax
  signed int result; // eax
  int *theLHS; // esi
  signed int theActions; // eax
  int v7; // ecx
  int rhsActions; // edi
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
  _BYTE inputToken[36]; // [esp+0h] [ebp-24h] BYREF

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  IO_OutWriteToken(aDefrule_4);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  g_ClipsDefrulePreservedWatchBreakFlags = 0;
  theDefrule = Rules_GetConstructNameAndComment(readSource, (int)(intptr_t)inputToken, (int (*)(void))Rules_FindDefruleByName, aDefrule_5, (int (*)(void))Rules_DeleteDefruleOrAll, asc_50A9E8, 0, 1, 1);
  if ( !theDefrule )
    return 1;
  theLHS = Lexer_ParseRuleLHS(readSource, theDefrule, *(_DWORD *)(uintptr_t)(theDefrule + 16), a2);
  if ( theLHS )
  {
    Parser_FreeLoopContextStack();
    g_ClipsParseReturnContext = 1;
    theActions = Rules_ParseDefruleRHS(readSource);
    rhsActions = theActions;
    if ( theActions )
    {
      Rules_BuildDefruleDisjunctChain(theLHS, theActions, v7);
      AST_Free(rhsActions);
      Parser_FreeLoopContextStack();
      AST_FreeNode((int)(intptr_t)theLHS);
      if ( v9 )
      {
        g_ClipsParsedFormAst = 0;
        IO_OutWriteToken(asc_50A9EC);
        if ( Mem_GetAllocFlag() == 1 )
        {
          *(_DWORD *)(uintptr_t)(v10 + 4) = 0;
        }
        else
        {
          v18 = Rules_CopyPPBuffer();
          *(_DWORD *)(uintptr_t)(v19 + 4) = v18;
        }
        v11 = Module_FindItemByName((int)(intptr_t)aDefrule_5);
        v12 = Module_GetItem(0, *(_DWORD *)(uintptr_t)(v11 + 4));
        for ( i = v13; i; i = (_DWORD *)(uintptr_t)i[12] )
          i[2] = v12;
        Rules_AddConstructToModuleList(v13);
        if ( (g_ClipsDefrulePreservedWatchBreakFlags & 1) != 0 )
          Rules_SetBreakFlag(v15);
        if ( (g_ClipsDefrulePreservedWatchBreakFlags & 2) != 0 || Rules_GetWatchItemState((int)(intptr_t)aActivations) )
          Rules_SetInheritedFlagBit4(1, v15);
        if ( (g_ClipsDefrulePreservedWatchBreakFlags & 4) != 0 || Rules_GetWatchItemState((int)(intptr_t)aRules) )
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
      AST_FreeNode((int)(intptr_t)theLHS);
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
    lhsPtr = (_DWORD *)(uintptr_t)theLHS[16];
  localVarCnt = Rules_CountNamedContextEntries();
  if ( !lhsPtr )
    return topDisjunct;
  while ( 1 )
  {
    if ( *lhsPtr == 81 )
    {
      tempNode = (_DWORD *)(uintptr_t)lhsPtr[16];
    }
    else if ( *lhsPtr == 80 )
    {
      tempNode = lhsPtr;
    }
    if ( Rules_CEDetectDuplicatePatternBinding(tempNode) || Rules_PatternChainHasActiveType80Callback(tempNode) || (logicalJoin = Rules_ValidateLogicalCEPlacement((signed int)(intptr_t)tempNode), logicalJoin < 0) || Rules_CheckRHSActionsAgainstCEConstraints(actions, (int)(intptr_t)tempNode) )
    {
      Rules_FreeDefruleDisjunctChain(topDisjunct);
      return 0;
    }
    newActions = (__int16 *)(uintptr_t)AST_CloneNodeList(actions);
    if ( Parser_ReplaceProcVars((int)(intptr_t)aRhsOfDefrule, (int)(intptr_t)newActions, 0, 0, (int (*)(void))Rules_ReplaceRHSModifyDuplicateVar, (int)(intptr_t)tempNode) )
      break;
    AST_InstallNodeChain(newActions);
    packPtr = AST_PackNodeChain(newActions);
    AST_Free((int)(intptr_t)newActions);
    lastJoin = Rules_BuildJoinTestExpressionChain(logicalJoin, v7, tempNode);
    complexity = Rules_SumCEListComplexity((int)(intptr_t)tempNode);
    currentDisjunct = Rules_AllocDefruleDisjunct(ruleName, localVarCnt, complexity, (int)(intptr_t)packPtr, logicalJoin, (int)(intptr_t)lastJoin);
    v11 = currentDisjunct;
    if ( topDisjunct )
    {
      lastDisjunct[12] = currentDisjunct;
    }
    else
    {
      topDisjunct = (int)(intptr_t)currentDisjunct;
      AST_InstallNodeChain((__int16 *)(uintptr_t)currentDisjunct[8]);
    }
    lhsPtr = (_DWORD *)(uintptr_t)lhsPtr[17];
    lastDisjunct = v11;
    if ( !lhsPtr )
      return topDisjunct;
  }
  Rules_FreeDefruleDisjunctChain(topDisjunct);
  AST_Free((int)(intptr_t)newActions);
  return 0;
}
// 4BF75E: variable 'v7' is possibly undefined
// 4BF79A: variable 'v11' is possibly undefined

//----- (004BF7F0) --------------------------------------------------------
_DWORD * Rules_AllocDefruleDisjunct(int ruleName, int localVarCnt, __int16 complexity, int theActions, int logicalJoin, int lastJoin)
{
  _DWORD *freeNode; // ecx
  signed int newDisjunct; // ecx
  __int16 savedFlagBit; // di
  int autoFocusFlag; // eax
  int theItem; // eax
  int theModuleItem; // eax
  _DWORD *disjunctPtr; // ecx
  int theJoin; // eax

  freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 208) = *freeNode;
    newDisjunct = g_ClipsMemFreeListTemp;
  }
  else
  {
    newDisjunct = Mem_HeapAllocWithRetry((_DWORD *)0x34);
  }
  *(_DWORD *)(uintptr_t)(newDisjunct + 4) = 0;
  *(_DWORD *)(uintptr_t)(newDisjunct + 16) = 0;
  *(_DWORD *)(uintptr_t)(newDisjunct + 40) = 0;
  *(_DWORD *)(uintptr_t)(newDisjunct + 48) = 0;
  *(_DWORD *)(uintptr_t)newDisjunct = ruleName;
  ++*(_DWORD *)(uintptr_t)(ruleName + 4);
  *(_DWORD *)(uintptr_t)(newDisjunct + 36) = theActions;
  savedFlagBit = *(_WORD *)(uintptr_t)(newDisjunct + 28) & 0x4000;
  *(_DWORD *)(uintptr_t)(newDisjunct + 20) = g_CLIPS_CurrentRuleSalience;
  *(_WORD *)(uintptr_t)(newDisjunct + 28) = savedFlagBit;
  *(_DWORD *)(uintptr_t)(newDisjunct + 28) |= complexity & 0x7FF;
  autoFocusFlag = g_Rules_DeclaredAutoFocusFlag & 1;
  *(_BYTE *)(uintptr_t)(newDisjunct + 29) &= ~0x40u;
  *(_DWORD *)(uintptr_t)(newDisjunct + 28) |= autoFocusFlag << 14;
  *(_DWORD *)(uintptr_t)(newDisjunct + 32) = g_ClipsParsedFormAst;
  *(_DWORD *)(uintptr_t)(newDisjunct + 24) = localVarCnt;
  theItem = Module_FindItemByName((int)(intptr_t)aDefrule_5);
  theModuleItem = Module_GetItem(0, *(_DWORD *)(uintptr_t)(theItem + 4));
  disjunctPtr[2] = theModuleItem;
  theJoin = lastJoin;
  *(_DWORD *)(uintptr_t)(lastJoin + 36) = disjunctPtr;
  disjunctPtr[11] = lastJoin;
  do
  {
    if ( *(_DWORD *)(uintptr_t)theJoin << 16 >> 25 == logicalJoin )
    {
      disjunctPtr[10] = theJoin;
      *(_BYTE *)(uintptr_t)theJoin |= 2u;
    }
    theJoin = *(_DWORD *)(uintptr_t)(theJoin + 24);
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
    if ( Symbol == *(int ***)(uintptr_t)(v7 + 2) )
    {
      if ( !Lexer_ValidateMessageHandler(v7, (int)(intptr_t)aModify_0, v6) )
        return -1;
    }
    else
    {
      duplicateSymbol = Rules_MakeSymbol(aDuplicate_0);
      if ( duplicateSymbol == *(int ***)(uintptr_t)(v10 + 2) && !Lexer_ValidateMessageHandler(v10, (int)(intptr_t)aDuplicate_0, v9) )
        return -1;
    }
    return 0;
  }
  if ( nodeType != 15 && nodeType != 16 )
    return 0;
  result = (int)(intptr_t)Rules_FindCEByIndex(*(_DWORD *)(nodePtr + 1), theLHS);
  if ( result )
  {
    if ( *(_DWORD *)(uintptr_t)(result + 24) )
    {
      (*(void (__cdecl **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 24) + 36))(a3);
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
  int tokenType; // [esp+0h] [ebp-1Ch]
  char *v7; // [esp+8h] [ebp-14h]

  IO_OutWriteToken(asc_50AA28);
  Rules_SetIndentDepth(3);
  result = Parser_ParseProgram(readSource, v2, 1);
  if ( result )
  {
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(v7);
    if ( tokenType == 101 )
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
  for ( i = 0; lhsNode; lhsNode = *(_DWORD *)(uintptr_t)(lhsNode + 68) )
  {
    testComplexity = Rules_ComputeExpressionComplexity((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(lhsNode + 52));
    fieldNode = *(_DWORD *)(uintptr_t)(lhsNode + 64);
    for ( i = testComplexity + v5; fieldNode; fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 64) )
    {
      if ( (*(_BYTE *)(uintptr_t)(fieldNode + 8) & 4) != 0 )
      {
        for ( j = *(_DWORD *)(uintptr_t)(fieldNode + 68); j; i = subComplexity + v9 )
        {
          subComplexity = Rules_ComputeExpressionComplexity((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(j + 52));
          j = *(_DWORD *)(uintptr_t)(v8 + 64);
        }
      }
      else
      {
        fieldComplexity = Rules_ComputeExpressionComplexity((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(fieldNode + 52));
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
      entityRecord = (_DWORD *)(uintptr_t)g_Clips_PrimitiveEntityTable[*exprPtr];
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
  firstLogical = *(_DWORD *)(uintptr_t)(result + 8) << 30 >> 31;
  do
  {
    if ( *(_DWORD *)(uintptr_t)result == 80 && *(_DWORD *)(uintptr_t)(result + 48) == 1 )
    {
      if ( (*(_BYTE *)(uintptr_t)(result + 8) & 2) != 0 )
      {
        if ( !firstLogical )
        {
          Rules_PrintErrorID((int)(intptr_t)aRulepsr_0, 1, 1);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aLogicalCesMust, v5);
          return -1;
        }
        if ( gappedLogical )
        {
          Rules_PrintErrorID((int)(intptr_t)aRulepsr_0, 2, 1);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aGapsMayNotExis, v6);
          return -1;
        }
        lastLogicalDepth = *(_DWORD *)(uintptr_t)(result + 48);
        ++logicalJoin;
      }
      else
      {
        gappedLogical = *(_DWORD *)(uintptr_t)(result + 48);
      }
    }
    result = *(_DWORD *)(uintptr_t)(result + 68);
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
      theLHS = (_DWORD *)(uintptr_t)theLHS[17];
      if ( !theLHS )
        return foundCE;
    }
    do
    {
      if ( (*(_BYTE *)(uintptr_t)(fieldNode + 8) & 4) != 0 )
      {
        savedNode = fieldNode;
        fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 68);
      }
      if ( fieldNode && (*(_DWORD *)(uintptr_t)fieldNode == 15 || *(_DWORD *)(uintptr_t)fieldNode == 16) && theVariable == *(_DWORD *)(uintptr_t)(fieldNode + 4) )
        foundCE = (_DWORD *)(uintptr_t)fieldNode;
      if ( fieldNode )
      {
        if ( !*(_DWORD *)(uintptr_t)(fieldNode + 64) )
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
      fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 64);
    }
    while ( fieldNode );
    theLHS = (_DWORD *)(uintptr_t)theLHS[17];
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
  if ( *(_DWORD *)(uintptr_t)(moduleHeader + 8) )
  {
    result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(moduleHeader + 8);
    do
    {
      result[4] = theConstruct;
      result = (_DWORD *)(uintptr_t)result[12];
    }
    while ( result );
    *(_DWORD *)(uintptr_t)(moduleHeader + 8) = theConstruct;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(moduleHeader + 4) = result;
    *(_DWORD *)(uintptr_t)(moduleHeader + 8) = result;
  }
  return result;
}
// 4BFC41: conditional instruction was optimized away because ebx.4!=0

//----- (004BFC70) --------------------------------------------------------
int Rules_SetupDefruleCodeGenerator(void)
{
  int result; // eax

  result = Rules_AddCodeGeneratorItem((int)(intptr_t)aDefrules_0, 0, 0, (int)(intptr_t)Rules_PrepareDefrulesForCodeGen, (int)(intptr_t)Rules_WriteDefrulesToCode, 3);
  g_ClipsDefruleCodeGenItem = result;
  return result;
}
// 54E884: using guessed type int dword_54E884;

//----- (004BFCA0) --------------------------------------------------------
int Rules_PrepareDefrulesForCodeGen(void)
{
  int v3; // [esp-4h] [ebp-14h] BYREF
  int v4; // [esp+0h] [ebp-10h] BYREF
  int v5[3]; // [esp+4h] [ebp-Ch] BYREF

  return Rules_JoinNetworkAssignCodeGenIds(&v3, &v4, v5);
}

//----- (004BFCC0) --------------------------------------------------------
int  Rules_WriteDefrulesToCode(const char *fileName, const char *fileID, int imageID, int headerFP, int maxIndices)
{
  int joinFile; // edi
  int moduleFileOpenResult; // eax
  int moduleFileHandle; // esi
  int defruleFileOpenResult; // eax
  int defruleFileHandle; // esi
  int v10; // eax
  int currentDefrule; // esi
  int closedDefruleFile; // eax
  int theJoin; // esi
  int joinFileOpenResult; // eax
  int joinFileHandle; // edi
  int nextJoin; // eax
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
  v31 = fileID;
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
  Output_WriteFormatted(0, 1, headerFP, (int)(intptr_t)aIncludeRuledef, 1);
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
    moduleFileOpenResult = Rules_ConstructCodeFileOpen(
           moduleFile,
           v30,
           v33,
           v31,
           &fileCount,
           moduleArrayVersion,
           v32,
           (char)(intptr_t)aStructDefrulem,
           **(const char ***)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20),
           0,
           0);
    moduleFileHandle = moduleFileOpenResult;
    if ( !moduleFileOpenResult )
    {
      Rules_CloseDefruleCodeFiles(0, defruleFile, maxIndices, joinFile);
      return 0;
    }
    Rules_WriteDefruleModuleHeaderEntry(moduleFileOpenResult, Enum, maxIndices, moduleCount);
    moduleFile = Rules_ConstructCodeFileClose(moduleFileHandle, &moduleArrayCount, maxIndices, &moduleArrayVersion, 0, 0);
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
    defruleFileOpenResult = Rules_ConstructCodeFileOpen(
           defruleFile,
           v30,
           v33,
           v31,
           &fileCount,
           defruleArrayVersion,
           v32,
           (char)(intptr_t)aStructDefrule,
           (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 4),
           0,
           0);
    defruleFileHandle = defruleFileOpenResult;
    if ( !defruleFileOpenResult )
    {
      Rules_CloseDefruleCodeFiles(moduleFile, 0, maxIndices, joinFile);
      return 0;
    }
    Rules_WriteDefruleStructEntry(defruleFileOpenResult, theDefrule, maxIndices, v33, moduleCount);
    v10 = defruleFileHandle;
    ++defruleArrayCount;
    currentDefrule = theDefrule;
    closedDefruleFile = Rules_ConstructCodeFileClose(v10, &defruleArrayCount, maxIndices, &defruleArrayVersion, 0, 0);
    theJoin = *(_DWORD *)(uintptr_t)(currentDefrule + 44);
    defruleFile = closedDefruleFile;
    if ( theJoin )
      break;
LABEL_12:
    if ( *(_DWORD *)(uintptr_t)(theDefrule + 48) )
      theDefrule = *(_DWORD *)(uintptr_t)(theDefrule + 48);
    else
      theDefrule = Rules_GetNextDefrule(theDefrule);
    if ( !theDefrule )
      goto LABEL_15;
  }
  while ( (*(_BYTE *)(uintptr_t)theJoin & 0x20) == 0 )
  {
LABEL_9:
    if ( (*(_BYTE *)(uintptr_t)theJoin & 4) != 0 )
      nextJoin = *(_DWORD *)(uintptr_t)(theJoin + 16);
    else
      nextJoin = *(_DWORD *)(uintptr_t)(theJoin + 24);
    theJoin = nextJoin;
    if ( !nextJoin )
      goto LABEL_12;
  }
  joinFileOpenResult = Rules_ConstructCodeFileOpen(
          joinFile,
          v30,
          v33,
          v31,
          &fileCount,
          joinArrayVersion,
          v32,
          (char)(intptr_t)aStructJoinnode,
          (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
          0,
          0);
  joinFileHandle = joinFileOpenResult;
  if ( joinFileOpenResult )
  {
    Rules_WriteJoinNodeStructEntry(joinFileOpenResult, theJoin, maxIndices, v33);
    ++joinArrayCount;
    joinFile = Rules_ConstructCodeFileClose(joinFileHandle, &joinArrayCount, maxIndices, &joinArrayVersion, 0, 0);
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
int  Rules_WriteDefruleModuleHeaderEntry(int theFile, int theModule, int maxIndices, int moduleCount CLASH95_UNUSED)
{
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  char v10; // [esp+0h] [ebp-Ch]
  char v11; // [esp+0h] [ebp-Ch]

  Output_WriteFormatted(maxIndices, theModule, theFile, (int)(intptr_t)asc_50AAE8, v10);
  Rules_WriteConstructModuleItemHeaderToCode(theFile, v5, v6, g_DefruleConstructClass, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 4));
  return Output_WriteFormatted(v8, v7, theFile, (int)(intptr_t)aNull_22, v11);
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

  Output_WriteFormatted(maxIndices, theDefrule, theFile, (int)(intptr_t)asc_50AAE8, imageID);
  Rules_WriteConstructHeaderToCode(theFile, theDefrule, maxIndices, moduleCount, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20), *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 4));
  Output_WriteFormatted(v8, *(_DWORD *)(uintptr_t)(theDefrule + 20), theFile, (int)(intptr_t)aDDDDDDDD, *(_DWORD *)(uintptr_t)(theDefrule + 20));
  Rules_ExpressionToCode(theFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDefrule + 32), v9, maxIndices);
  Output_WriteFormatted(v11, v10, theFile, (int)(intptr_t)asc_50AB10, v22);
  Rules_ExpressionToCode(theFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(theDefrule + 36), v12, maxIndices);
  Output_WriteFormatted(v14, v13, theFile, (int)(intptr_t)asc_50AB10, v23);
  v16 = *(_DWORD *)(uintptr_t)(theDefrule + 40);
  if ( v16 )
    Output_WriteFormatted(
      v16,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)(intptr_t)aSD_LdLd_6,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v15, theFile, (int)(intptr_t)aNull_23, v24);
  v18 = *(_DWORD *)(uintptr_t)(theDefrule + 44);
  if ( v18 )
    Output_WriteFormatted(
      v18,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)(intptr_t)aSD_LdLd_6,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v17, theFile, (int)(intptr_t)aNull_23, v24);
  v20 = *(_DWORD *)(uintptr_t)(theDefrule + 48);
  if ( v20 )
    return Output_WriteFormatted(
             v20,
             *(_DWORD *)(uintptr_t)(v20 + 12) % maxIndices,
             theFile,
             (int)(intptr_t)aSD_LdLd_7,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(0, v19, theFile, (int)(intptr_t)aNull_24, v24);
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
  int patternParserSaved; // ebp
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

  *(_BYTE *)(uintptr_t)theJoin &= ~0x20u;
  Output_WriteFormatted(maxIndices, theJoin, theFile, (int)(intptr_t)aDDDD00DD0, *(_BYTE *)(uintptr_t)theJoin & 1);
  Output_WriteFormatted(v7, v6, theFile, (int)(intptr_t)aNull_23, imageID);
  Rules_WriteExpressionRefToCode(theFile, (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v8 + 12), v9, imageID);
  Output_WriteFormatted(v11, v10, theFile, (int)(intptr_t)asc_50AB10, v30);
  rightSideEntry = *(_DWORD *)(uintptr_t)(theJoin + 16);
  if ( !rightSideEntry )
    goto LABEL_4;
  if ( (*(_BYTE *)(uintptr_t)theJoin & 4) != 0 )
  {
    Output_WriteFormatted(
      *(_DWORD *)(uintptr_t)(theJoin + 16),
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)(intptr_t)aSD_LdLd_6,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  }
  else
  {
    patternParser = Rules_GetPatternParserByTypeID(*(_DWORD *)(uintptr_t)theJoin << 23 >> 29);
    v12 = *(_DWORD *)(uintptr_t)(patternParser + 84);
    patternParserSaved = patternParser;
    if ( !v12 )
    {
LABEL_4:
      Output_WriteFormatted(v12, rightSideEntry, theFile, (int)(intptr_t)aNull_23, v31);
      goto LABEL_5;
    }
    Output_WriteFormatted(v12, theFile, theFile, (int)(intptr_t)aVs_0, v31);
    (*(void (__thiscall **)(int))(uintptr_t)(patternParserSaved + 84))(maxIndices);
    Output_WriteFormatted(v29, v28, theFile, (int)(intptr_t)asc_50AB10, v32);
  }
LABEL_5:
  nextLevel = *(_DWORD *)(uintptr_t)(theJoin + 20);
  if ( nextLevel )
    Output_WriteFormatted(v17, *(_DWORD *)(uintptr_t)(nextLevel + 4) % maxIndices, theFile, (int)(intptr_t)aSD_LdLd_6, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v17, v16, theFile, (int)(intptr_t)aNull_23, v31);
  if ( *(_DWORD *)(uintptr_t)(theJoin + 24) )
    Output_WriteFormatted(
      *(_DWORD *)(uintptr_t)(theJoin + 24),
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)(intptr_t)aSD_LdLd_6,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(v20, v19, theFile, (int)(intptr_t)aNull_23, v31);
  v22 = *(_DWORD *)(uintptr_t)(theJoin + 28);
  if ( v22 )
    Output_WriteFormatted(
      v22,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)(intptr_t)aSD_LdLd_6,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v21, theFile, (int)(intptr_t)aNull_23, v31);
  v24 = *(_DWORD *)(uintptr_t)(theJoin + 32);
  if ( v24 )
    Output_WriteFormatted(
      v24,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8),
      theFile,
      (int)(intptr_t)aSD_LdLd_6,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 8));
  else
    Output_WriteFormatted(0, v23, theFile, (int)(intptr_t)aNull_23, v31);
  v26 = *(_DWORD *)(uintptr_t)(theJoin + 36);
  if ( v26 )
    return Output_WriteFormatted(
             v26,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 4),
             theFile,
             (int)(intptr_t)aSD_LdLd_7,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20) + 4));
  else
    return Output_WriteFormatted(0, v25, theFile, (int)(intptr_t)aNull_24, v31);
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
  return Output_WriteFormatted(count, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20), theFile, (int)(intptr_t)aMihsSD_DD_4, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsDefruleCodeGenItem + 20));
}
// 54E884: using guessed type int dword_54E884;

//----- (004C0550) --------------------------------------------------------
int Rules_CreateLHSParseNode(void)
{
  _DWORD *freeNode; // edx
  _BYTE *newConstraint; // ecx
  int parseNode; // ecx
  char flagsByte2; // ah
  char flagsByte1; // dl
  signed int minValueExpr; // eax
  int v6; // ecx
  signed int maxValueExpr; // eax
  int v8; // ecx
  signed int minFieldsExpr; // eax
  int v10; // ecx
  signed int maxFieldsExpr; // eax
  int newNode; // ecx

  freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 168);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 168);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 168) = *freeNode;
    newConstraint = (_BYTE *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    newConstraint = (_BYTE *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x2A);
  }
  Rules_SetLHSParseNodeDefaultFlags(newConstraint, 1);
  flagsByte2 = *(_BYTE *)(uintptr_t)(parseNode + 2);
  flagsByte1 = *(_BYTE *)(uintptr_t)(parseNode + 1);
  *(_DWORD *)(uintptr_t)(parseNode + 6) = 0;
  *(_BYTE *)(uintptr_t)(parseNode + 2) = flagsByte2 | 1;
  *(_BYTE *)(uintptr_t)(parseNode + 1) = flagsByte1 & 1;
  minValueExpr = AST_NewNode(2, g_Clips_NegativeInfinitySymbol);
  *(_DWORD *)(uintptr_t)(v6 + 10) = minValueExpr;
  maxValueExpr = AST_NewNode(2, g_ClipsPositiveInfinitySymbol);
  *(_DWORD *)(uintptr_t)(v8 + 14) = maxValueExpr;
  minFieldsExpr = AST_NewNode(1, g_CLIPS_IntegerZeroValueNode);
  *(_DWORD *)(uintptr_t)(v10 + 18) = minFieldsExpr;
  maxFieldsExpr = AST_NewNode(2, g_ClipsPositiveInfinitySymbol);
  *(_DWORD *)(uintptr_t)(newNode + 34) = -1;
  *(_DWORD *)(uintptr_t)(newNode + 38) = 0;
  *(_DWORD *)(uintptr_t)(newNode + 26) = 0;
  *(_DWORD *)(uintptr_t)(newNode + 30) = 0;
  *(_DWORD *)(uintptr_t)(newNode + 22) = maxFieldsExpr;
  return newNode;
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
