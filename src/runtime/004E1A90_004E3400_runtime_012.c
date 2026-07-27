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

//----- (004E1A90) --------------------------------------------------------
signed int  Rules_BuildDualSlotConstraintBitmapTestNode(int joinTest, int selfNode, int referringNode)
{
  int v5; // ecx
  int compareSymbol; // edx
  signed int compareCallNode; // ebp
  int v8; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // ecx
  unsigned int v21; // ebp
  int v22; // eax
  unsigned int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // eax
  unsigned int v27; // edx
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // edx
  int v33; // edx
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // eax
  int v40; // eax
  int v41; // eax
  int v42; // eax
  int v43; // ebx
  int v44; // eax
  int v45; // eax
  int v46; // eax
  int v47; // eax
  int v48; // eax
  int v49; // eax
  int v50; // eax
  int jnVars1; // [esp+0h] [ebp-3Ch] BYREF
  int jnVars1Hi; // [esp+4h] [ebp-38h]
  int pnVars2; // [esp+8h] [ebp-34h] BYREF
  int pnVars2Hi; // [esp+Ch] [ebp-30h]
  int pnVars3; // [esp+10h] [ebp-2Ch] BYREF
  int pnVars3Hi; // [esp+14h] [ebp-28h]
  int jnVars2; // [esp+18h] [ebp-24h] BYREF
  int jnVars2Hi; // [esp+1Ch] [ebp-20h]
  int jnVars3; // [esp+20h] [ebp-1Ch] BYREF
  int jnVars3Hi; // [esp+24h] [ebp-18h]
  _DWORD pnVars1[5]; // [esp+28h] [ebp-14h] BYREF

  if ( Rules_IsMultiplyConstrainedSlot(selfNode) && Rules_IsMultiplyConstrainedSlot(referringNode) )
  {
    if ( (*(_BYTE *)(uintptr_t)(v10 + 9) & 0x40) == 0 && (*(_BYTE *)(uintptr_t)(referringNode + 9) & 0x40) == 0 )
    {
      Mem_AllocArray(pnVars1, 4);
      Mem_AllocArray(&jnVars1, 8);
      if ( (*(_BYTE *)(uintptr_t)(v11 + 8) & 1) != 0 )
      {
        HIBYTE(jnVars1) |= 0x80u;
        HIBYTE(pnVars1[0]) = HIBYTE(pnVars1[0]) & 0x7F | 0x80;
      }
      else
      {
        BYTE1(jnVars1) |= 0x80u;
        BYTE1(pnVars1[0]) = BYTE1(pnVars1[0]) & 0x7F | 0x80;
      }
      v12 = *(_DWORD *)(uintptr_t)(v11 + 40);
      LOWORD(jnVars1) = jnVars1 & 0x8000;
      jnVars1 |= v12 & 0x7FFF;
      v13 = *(_DWORD *)(uintptr_t)(v11 + 40);
      LOWORD(pnVars1[0]) &= 0x8000u;
      pnVars1[0] |= v13 & 0x7FFF;
      v14 = *(_DWORD *)(uintptr_t)(referringNode + 40);
      HIWORD(jnVars1) &= 0x8000u;
      jnVars1 |= (v14 & 0x7FFF) << 16;
      v15 = *(_DWORD *)(uintptr_t)(referringNode + 40);
      HIWORD(pnVars1[0]) &= 0x8000u;
      pnVars1[0] |= (v15 & 0x7FFF) << 16;
      if ( joinTest )
      {
        v16 = *(_DWORD *)(uintptr_t)(v11 + 28);
        LOBYTE(jnVars1Hi) = 0;
        jnVars1Hi |= (unsigned __int8)v16;
        v17 = *(_DWORD *)(uintptr_t)(referringNode + 28);
        BYTE1(jnVars1Hi) = 0;
        jnVars1Hi |= (unsigned __int8)v17 << 8;
        v18 = Rules_AddBitmapValue(&jnVars1, 8);
        return AST_NewNode(52, v18);
      }
      else
      {
        v19 = Rules_AddBitmapValue(pnVars1, 4);
        return AST_NewNode(51, v19);
      }
    }
    if ( (*(_BYTE *)(uintptr_t)(v5 + 9) & 0x40) == 0 || (*(_BYTE *)(uintptr_t)(referringNode + 9) & 0x40) == 0 )
    {
      Mem_AllocArray(&pnVars2, 8);
      Mem_AllocArray(&jnVars2, 8);
      if ( (*(_BYTE *)(uintptr_t)(v20 + 8) & 1) != 0 )
      {
        BYTE2(jnVars2Hi) |= 0x80u;
        HIBYTE(pnVars2) = HIBYTE(pnVars2) & 0x7F | 0x80;
      }
      else
      {
        BYTE1(jnVars2) |= 0x80u;
        BYTE1(pnVars2) = BYTE1(pnVars2) & 0x7F | 0x80;
      }
      v22 = jnVars2Hi;
      v21 = jnVars2 & 0xFFFF8000;
      v23 = pnVars2 & 0xFFFF8000;
      LOBYTE(v22) = 0;
      if ( (*(_BYTE *)(uintptr_t)(v20 + 9) & 0x40) != 0 )
      {
        jnVars2 = v21 | *(_DWORD *)(uintptr_t)(v20 + 40) & 0x7FFF;
        pnVars2 = *(_DWORD *)(uintptr_t)(v20 + 40) & 0x7FFF | v23;
        v24 = *(_DWORD *)(uintptr_t)(referringNode + 40);
        HIWORD(jnVars2) &= 0x8000u;
        jnVars2 |= (v24 & 0x7FFF) << 16;
        v25 = *(_DWORD *)(uintptr_t)(referringNode + 40);
        HIWORD(pnVars2) &= 0x8000u;
        pnVars2 |= (v25 & 0x7FFF) << 16;
        if ( joinTest )
        {
          jnVars2Hi = (unsigned __int8)*(_DWORD *)(uintptr_t)(v20 + 28) | v22;
          v26 = *(_DWORD *)(uintptr_t)(referringNode + 28);
          BYTE1(jnVars2Hi) = 0;
          jnVars2Hi |= (unsigned __int8)v26 << 8;
        }
        v27 = jnVars2Hi & 0xFF80FFFF;
        if ( (*(_DWORD *)(uintptr_t)(v20 + 8) & 0x3F8000) != 0 )
        {
          v30 = (unsigned __int8)(*(_DWORD *)(uintptr_t)(v20 + 12) << 18 >> 24) >> 1;
          LOBYTE(pnVars2Hi) = pnVars2Hi & 0x80;
          jnVars2Hi = (v30 << 16) | v27;
          goto LABEL_24;
        }
        HIBYTE(jnVars2) |= 0x80u;
        LOBYTE(pnVars2Hi) = pnVars2Hi & 0x7F | 0x80;
        v28 = *(_DWORD *)(uintptr_t)(v20 + 12);
      }
      else
      {
        jnVars2 = v21 | *(_DWORD *)(uintptr_t)(referringNode + 40) & 0x7FFF;
        pnVars2 = *(_DWORD *)(uintptr_t)(referringNode + 40) & 0x7FFF | v23;
        v32 = *(_DWORD *)(uintptr_t)(v20 + 40);
        HIWORD(jnVars2) &= 0x8000u;
        jnVars2 |= (v32 & 0x7FFF) << 16;
        v33 = *(_DWORD *)(uintptr_t)(v20 + 40) & 0x7FFF;
        HIWORD(pnVars2) &= 0x8000u;
        pnVars2 |= v33 << 16;
        if ( joinTest )
        {
          jnVars2Hi = (unsigned __int8)*(_DWORD *)(uintptr_t)(referringNode + 28) | v22;
          v34 = *(_DWORD *)(uintptr_t)(v20 + 28);
          BYTE1(jnVars2Hi) = 0;
          jnVars2Hi |= (unsigned __int8)v34 << 8;
        }
        v27 = jnVars2Hi & 0xFF80FFFF;
        if ( (*(_DWORD *)(uintptr_t)(referringNode + 8) & 0x3F8000) != 0 )
        {
          v35 = (unsigned __int8)(*(_DWORD *)(uintptr_t)(referringNode + 12) << 18 >> 24) >> 1;
          LOBYTE(pnVars2Hi) = pnVars2Hi & 0x80;
          jnVars2Hi = (v35 << 16) | v27;
          pnVars2Hi |= v35;
LABEL_25:
          if ( joinTest )
          {
            v31 = Rules_AddBitmapValue(&jnVars2, 8);
            return AST_NewNode(54, v31);
          }
          else
          {
            v36 = Rules_AddBitmapValue(&pnVars2, 8);
            return AST_NewNode(53, v36);
          }
        }
        HIBYTE(jnVars2) |= 0x80u;
        LOBYTE(pnVars2Hi) = pnVars2Hi & 0x7F | 0x80;
        v28 = *(_DWORD *)(uintptr_t)(referringNode + 12);
      }
      v29 = v28 & 0x7F;
      jnVars2Hi = (v29 << 16) | v27;
      LOBYTE(pnVars2Hi) = pnVars2Hi & 0x80;
      v30 = v29 & 0x7F;
LABEL_24:
      pnVars2Hi |= v30;
      goto LABEL_25;
    }
    Mem_AllocArray(&pnVars3, 8);
    Mem_AllocArray(&jnVars3, 8);
    if ( (*(_BYTE *)(uintptr_t)(v37 + 8) & 1) != 0 )
    {
      HIBYTE(jnVars3) |= 0x80u;
      HIBYTE(pnVars3) = HIBYTE(pnVars3) & 0x7F | 0x80;
    }
    else
    {
      BYTE1(jnVars3) |= 0x80u;
      BYTE1(pnVars3) = BYTE1(pnVars3) & 0x7F | 0x80;
    }
    v38 = *(_DWORD *)(uintptr_t)(v37 + 40);
    LOWORD(jnVars3) = jnVars3 & 0x8000;
    jnVars3 |= v38 & 0x7FFF;
    v39 = *(_DWORD *)(uintptr_t)(v37 + 40);
    LOWORD(pnVars3) = pnVars3 & 0x8000;
    pnVars3 |= v39 & 0x7FFF;
    v40 = *(_DWORD *)(uintptr_t)(referringNode + 40);
    HIWORD(jnVars3) &= 0x8000u;
    jnVars3 |= (v40 & 0x7FFF) << 16;
    v41 = *(_DWORD *)(uintptr_t)(referringNode + 40);
    HIWORD(pnVars3) &= 0x8000u;
    pnVars3 |= (v41 & 0x7FFF) << 16;
    if ( (*(_DWORD *)(uintptr_t)(v37 + 8) & 0x3F8000) != 0 )
    {
      v44 = (unsigned __int8)(*(_DWORD *)(uintptr_t)(v37 + 12) << 18 >> 24) >> 1;
      BYTE2(jnVars3Hi) &= 0x80u;
      LOBYTE(pnVars3Hi) = pnVars3Hi & 0x80;
      jnVars3Hi |= v44 << 16;
    }
    else
    {
      BYTE2(jnVars3Hi) |= 0x80u;
      LOBYTE(pnVars3Hi) = pnVars3Hi & 0x7F | 0x80;
      v42 = *(_DWORD *)(uintptr_t)(v37 + 12) & 0x7F;
      BYTE2(jnVars3Hi) &= 0x80u;
      v43 = (v42 << 16) | jnVars3Hi;
      LOBYTE(pnVars3Hi) = pnVars3Hi & 0x80;
      v44 = v42 & 0x7F;
      jnVars3Hi = v43;
    }
    pnVars3Hi |= v44;
    if ( (*(_DWORD *)(uintptr_t)(referringNode + 8) & 0x3F8000) != 0 )
    {
      v46 = (unsigned __int8)(*(_DWORD *)(uintptr_t)(referringNode + 12) << 18 >> 24) >> 1;
      HIBYTE(jnVars3Hi) &= 0x80u;
      jnVars3Hi |= v46 << 24;
    }
    else
    {
      HIBYTE(jnVars3Hi) |= 0x80u;
      BYTE1(pnVars3Hi) = BYTE1(pnVars3Hi) & 0x7F | 0x80;
      v45 = *(_DWORD *)(uintptr_t)(referringNode + 12) & 0x7F;
      HIBYTE(jnVars3Hi) &= 0x80u;
      jnVars3Hi |= v45 << 24;
      v46 = v45 & 0x7F;
    }
    BYTE1(pnVars3Hi) &= 0x80u;
    pnVars3Hi |= v46 << 8;
    if ( joinTest )
    {
      v47 = *(_DWORD *)(uintptr_t)(v37 + 28);
      LOBYTE(jnVars3Hi) = 0;
      jnVars3Hi |= (unsigned __int8)v47;
      v48 = *(_DWORD *)(uintptr_t)(referringNode + 28);
      BYTE1(jnVars3Hi) = 0;
      jnVars3Hi |= (unsigned __int8)v48 << 8;
      v49 = Rules_AddBitmapValue(&jnVars3, 8);
      return AST_NewNode(56, v49);
    }
    else
    {
      v50 = Rules_AddBitmapValue(&pnVars3, 8);
      return AST_NewNode(55, v50);
    }
  }
  else
  {
    if ( (*(_BYTE *)(uintptr_t)(v5 + 8) & 1) != 0 )
      compareSymbol = g_ClipsSymbolNeq;
    else
      compareSymbol = g_ClipsSymbolEq;
    compareCallNode = AST_NewNode(10, compareSymbol);
    *(_DWORD *)(uintptr_t)(compareCallNode + 6) = AST_NewNode(0, 0);
    Rules_BuildSlotConstraintBitmapTestNode(joinTest, v8);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(compareCallNode + 6) + 10) = AST_NewNode(0, 0);
    Rules_BuildSlotConstraintBitmapTestNode(joinTest, referringNode);
    return compareCallNode;
  }
}
// 4E1AA8: variable 'v5' is possibly undefined
// 4E1AD8: variable 'v8' is possibly undefined
// 4E1B14: variable 'v10' is possibly undefined
// 4E1B42: variable 'v11' is possibly undefined
// 4E1CA8: variable 'v20' is possibly undefined
// 4E1F83: variable 'v37' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004E2200) --------------------------------------------------------
signed int Rules_RegisterObjectPatternNetworkBinaryItem(void)
{
  return Rules_RegisterBinaryItem(
           (int)(intptr_t)aObjectPatter_0,
           0,
           0,
           (int)(intptr_t)Rules_AssignObjectPatternNetworkBsaveIndices,
           (int)(intptr_t)Rules_BsaveObjectPatternNetworkCounts,
           (int)(intptr_t)Rules_BsaveObjectPatternNetworkRecords,
           (int)(intptr_t)Rules_BloadObjectPatternNetworkCounts,
           (int)(intptr_t)Rules_BloadObjectPatternNetworkRecords,
           (int)(intptr_t)Class_ClearClassIDTable);
}

//----- (004E2240) --------------------------------------------------------
_DWORD *Rules_AssignObjectPatternNetworkBsaveIndices(void)
{
  _DWORD *i; // eax
  int slotBitmap; // ebx
  int alphaIndex; // edx
  _DWORD *result; // eax
  int patternIndex; // edx
  _DWORD *nextLevelNode; // esi

  if ( Rules_IsBloaded() )
  {
    Rules_ConstructQueuePush(g_ReactiveRuleBloadCount);
    Rules_ConstructQueuePush(g_ObjectPatternNetworkBloadCount);
  }
  g_ReactiveRuleBloadCount = 0;
  for ( i = (_DWORD *)(uintptr_t)Rules_GetReactiveRuleList(); i; i = (_DWORD *)(uintptr_t)i[9] )
  {
    *(_BYTE *)(uintptr_t)(i[5] + 12) |= 2u;
    slotBitmap = i[6];
    if ( slotBitmap )
      *(_BYTE *)(uintptr_t)(i[6] + 12) = *(_BYTE *)(uintptr_t)(slotBitmap + 12) | 2;
    alphaIndex = g_ReactiveRuleBloadCount++;
    i[10] = alphaIndex;
  }
  g_ObjectPatternNetworkBloadCount = 0;
  result = (_DWORD *)(uintptr_t)Rules_GetObjectPatternNetworkRoot();
  if ( result )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        patternIndex = g_ObjectPatternNetworkBloadCount++;
        nextLevelNode = (_DWORD *)(uintptr_t)result[4];
        result[9] = patternIndex;
        if ( !nextLevelNode )
          break;
        result = nextLevelNode;
      }
      while ( !result[7] )
      {
        result = (_DWORD *)(uintptr_t)result[5];
        if ( !result )
          return result;
      }
      result = (_DWORD *)(uintptr_t)result[7];
    }
  }
  return result;
}
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E2300) --------------------------------------------------------
const void * Rules_BsaveObjectPatternNetworkCounts(int filePtr, int a2)
{
  int v2; // ecx
  int v3; // ecx
  _DWORD spaceBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  spaceBuffer[2] = a2;
  spaceBuffer[0] = 8;
  Rules_BsaveWriteBlock(4, filePtr, spaceBuffer);
  Rules_BsaveWriteBlock(4, v2, &g_ReactiveRuleBloadCount);
  return Rules_BsaveWriteBlock(4, v3, &g_ObjectPatternNetworkBloadCount);
}
// 4E232A: variable 'v2' is possibly undefined
// 4E233B: variable 'v3' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E2350) --------------------------------------------------------
const void * Rules_BsaveObjectPatternNetworkRecords(int outFile)
{
  int i; // ecx
  _DWORD *alphaNode; // ecx
  int slotBitmapRef; // edx
  int patternNodeRef; // edi
  int patternIndex; // eax
  int nextAlphaPtr; // ebp
  int nextAlphaIdx; // eax
  int nextTerminalPtr; // eax
  int nextTerminalIdx; // eax
  int v11; // ecx
  int currentPattern; // ecx
  unsigned int multifieldNodeFlag; // eax
  int whichField; // eax
  int endSlotFlag; // eax
  _DWORD *patternNode; // ecx
  int nextLevelPtr; // ebx
  int nextLevelIndex; // eax
  int lastLevelPtr; // edi
  int lastLevelIndex; // eax
  int leftNodePtr; // ebp
  int leftNodeIndex; // eax
  int rightNodePtr; // eax
  int rightNodeIndex; // eax
  int alphaPtr; // edx
  int alphaNodeIndex; // eax
  const void *result; // eax
  _DWORD *traverseNode; // ecx
  _DWORD bsavePatternRecord[8]; // [esp+0h] [ebp-58h] BYREF
  _BYTE bsaveAlphaRecord[8]; // [esp+20h] [ebp-38h] BYREF
  int classBitmapIndex CLASH95_UNUSED; // [esp+28h] [ebp-30h]
  int slotBitmapIndex CLASH95_UNUSED; // [esp+2Ch] [ebp-2Ch]
  int patternNodeIndex CLASH95_UNUSED; // [esp+30h] [ebp-28h]
  int nextAlphaIndex CLASH95_UNUSED; // [esp+34h] [ebp-24h]
  int nextTerminalIndex CLASH95_UNUSED; // [esp+38h] [ebp-20h]
  int bsaveSpace[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  bsaveSpace[0] = 32 * g_ObjectPatternNetworkBloadCount + 28 * g_ReactiveRuleBloadCount;
  Rules_BsaveWriteBlock(4, outFile, bsaveSpace);
  for ( i = Rules_GetReactiveRuleList(); i; i = *(_DWORD *)(uintptr_t)(i + 36) )
  {
    Rules_BsavePackSharedRecordHeader((int)(intptr_t)bsaveAlphaRecord, i);
    classBitmapIndex = *(_DWORD *)(uintptr_t)(alphaNode[5] + 12) << 16 >> 18;
    slotBitmapRef = alphaNode[6];
    if ( slotBitmapRef )
      slotBitmapIndex = *(_DWORD *)(uintptr_t)(slotBitmapRef + 12) << 16 >> 18;
    else
      slotBitmapIndex = -1;
    patternNodeRef = alphaNode[7];
    if ( patternNodeRef )
      patternIndex = *(_DWORD *)(uintptr_t)(patternNodeRef + 36);
    else
      patternIndex = -1;
    patternNodeIndex = patternIndex;
    nextAlphaPtr = alphaNode[8];
    if ( nextAlphaPtr )
      nextAlphaIdx = *(_DWORD *)(uintptr_t)(nextAlphaPtr + 40);
    else
      nextAlphaIdx = -1;
    nextAlphaIndex = nextAlphaIdx;
    nextTerminalPtr = alphaNode[9];
    if ( nextTerminalPtr )
      nextTerminalIdx = *(_DWORD *)(uintptr_t)(nextTerminalPtr + 40);
    else
      nextTerminalIdx = -1;
    nextTerminalIndex = nextTerminalIdx;
    Rules_BsaveWriteBlock(28, outFile, bsaveAlphaRecord);
  }
  currentPattern = Rules_GetObjectPatternNetworkRoot();
  while ( currentPattern )
  {
    multifieldNodeFlag = *(_DWORD *)(uintptr_t)currentPattern << 30;
    LOBYTE(bsavePatternRecord[0]) &= ~1u;
    bsavePatternRecord[0] |= multifieldNodeFlag >> 31;
    whichField = *(_DWORD *)(uintptr_t)currentPattern << 21 >> 24;
    LOWORD(bsavePatternRecord[0]) &= 0xFC03u;
    bsavePatternRecord[0] |= 4 * (unsigned __int8)whichField;
    bsavePatternRecord[0] = ((unsigned __int8)(*(_DWORD *)(uintptr_t)currentPattern << 13 >> 24) << 10) | bsavePatternRecord[0] & 0xFFFC03FF;
    endSlotFlag = *(_DWORD *)(uintptr_t)currentPattern << 29 >> 31;
    LOBYTE(bsavePatternRecord[0]) &= ~2u;
    bsavePatternRecord[0] |= 2 * (endSlotFlag & 1);
    bsavePatternRecord[1] = *(_DWORD *)(uintptr_t)(currentPattern + 8);
    bsavePatternRecord[2] = AST_GetHashedNodeIndex((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentPattern + 12));
    nextLevelPtr = patternNode[4];
    if ( nextLevelPtr )
      nextLevelIndex = *(_DWORD *)(uintptr_t)(nextLevelPtr + 36);
    else
      nextLevelIndex = -1;
    bsavePatternRecord[3] = nextLevelIndex;
    lastLevelPtr = patternNode[5];
    if ( lastLevelPtr )
      lastLevelIndex = *(_DWORD *)(uintptr_t)(lastLevelPtr + 36);
    else
      lastLevelIndex = -1;
    bsavePatternRecord[4] = lastLevelIndex;
    leftNodePtr = patternNode[6];
    if ( leftNodePtr )
      leftNodeIndex = *(_DWORD *)(uintptr_t)(leftNodePtr + 36);
    else
      leftNodeIndex = -1;
    bsavePatternRecord[5] = leftNodeIndex;
    rightNodePtr = patternNode[7];
    if ( rightNodePtr )
      rightNodeIndex = *(_DWORD *)(uintptr_t)(rightNodePtr + 36);
    else
      rightNodeIndex = -1;
    bsavePatternRecord[6] = rightNodeIndex;
    alphaPtr = patternNode[8];
    if ( alphaPtr )
      alphaNodeIndex = *(_DWORD *)(uintptr_t)(alphaPtr + 40);
    else
      alphaNodeIndex = -1;
    bsavePatternRecord[7] = alphaNodeIndex;
    result = Rules_BsaveWriteBlock(32, outFile, bsavePatternRecord);
    if ( traverseNode[4] )
    {
      currentPattern = traverseNode[4];
    }
    else
    {
      while ( !traverseNode[7] )
      {
        traverseNode = (_DWORD *)(uintptr_t)traverseNode[5];
        if ( !traverseNode )
          return result;
      }
      currentPattern = traverseNode[7];
    }
  }
  result = (const void *)(uintptr_t)Rules_IsBloaded();
  if ( result )
  {
    Rules_ConstructQueuePop(&g_ReactiveRuleBloadCount);
    return (const void *)(uintptr_t)Rules_ConstructQueuePop(&g_ObjectPatternNetworkBloadCount);
  }
  return result;
}
// 4E23AB: variable 'v3' is possibly undefined
// 4E2419: variable 'v11' is possibly undefined
// 4E24C7: variable 'v16' is possibly undefined
// 4E252F: variable 'v28' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;

//----- (004E25F0) --------------------------------------------------------
signed int Rules_BloadObjectPatternNetworkCounts(void)
{
  signed int result; // eax
  unsigned int count_bytes; // [esp+8h] [ebp-Ch] BYREF
  int counts[2]; // [esp+0h] [ebp-14h] BYREF

  Rules_BloadReadBlock((uintptr_t)&count_bytes, 4u);
  Rules_BloadReadBlock((uintptr_t)counts, count_bytes);
  g_ReactiveRuleBloadCount = counts[0];
  result = counts[1];
  g_ObjectPatternNetworkBloadCount = counts[1];
  if ( counts[0] )
  {
    count_bytes = 44 * counts[0];
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(44 * counts[0]));
    g_ReactiveRuleArrayPtr = result;
  }
  else
  {
    g_ReactiveRuleArrayPtr = 0;
  }
  if ( g_ObjectPatternNetworkBloadCount )
  {
    count_bytes = 40 * g_ObjectPatternNetworkBloadCount;
    result = Mem_HeapAllocWithRetry((_DWORD *)(uintptr_t)(40 * g_ObjectPatternNetworkBloadCount));
    g_ObjectPatternNetworkArrayPtr = result;
  }
  else
  {
    g_ObjectPatternNetworkArrayPtr = 0;
  }
  return result;
}
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;

//----- (004E2680) --------------------------------------------------------
int Rules_BloadObjectPatternNetworkRecords(void)
{
  int result; // eax
  int space; // [esp+0h] [ebp-8h] BYREF

  result = Rules_BloadReadBlock((uintptr_t)&space, 4u);
  if ( space )
  {
    Rules_BloadAndRefresh(g_ReactiveRuleBloadCount, 28, (void (__fastcall *)(signed int, signed int))Rules_RefreshBloadedReactiveRuleRecord);
    Rules_BloadAndRefresh(g_ObjectPatternNetworkBloadCount, 32, (void (__fastcall *)(signed int, signed int))Class_ResolveSystemSlotTemplate);
    Rules_SetReactiveRuleList(g_ReactiveRuleArrayPtr);
    return Rules_SetObjectPatternNetworkRoot(g_ObjectPatternNetworkArrayPtr);
  }
  return result;
}
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;

//----- (004E26E0) --------------------------------------------------------
int  Rules_RefreshBloadedReactiveRuleRecord(int *bsaveAlpha, int itemIndex)
{
  int record; // ecx
  int reactive_slots_index; // ebp
  int reactive_slots; // eax
  int direct_super_index; // eax
  int result; // eax
  int superclass_index; // ebx
  int role_symbol; // eax
  int superclass; // ebx

  record = 44 * itemIndex + g_ReactiveRuleArrayPtr;
  Rules_BloadUnpackSharedRecordHeader(record, bsaveAlpha);
  *(_DWORD *)(uintptr_t)(record + 16) = 0;
  *(_DWORD *)(uintptr_t)(record + 20) = *(_DWORD *)(uintptr_t)(g_ClipsBloadBitmapPointerTable + 4 * bsaveAlpha[2]);
  if ( bsaveAlpha[3] == -1 )
  {
    *(_DWORD *)(uintptr_t)(record + 24) = 0;
  }
  else
  {
    role_symbol = *(_DWORD *)(uintptr_t)(g_ClipsBloadBitmapPointerTable + 4 * bsaveAlpha[3]);
    *(_DWORD *)(uintptr_t)(record + 24) = role_symbol;
    ++*(_DWORD *)(uintptr_t)(role_symbol + 4);
  }
  ++*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(record + 20) + 4);
  reactive_slots_index = bsaveAlpha[4];
  if ( reactive_slots_index == -1 )
    reactive_slots = 0;
  else
    reactive_slots = 40 * reactive_slots_index + g_ObjectPatternNetworkArrayPtr;
  *(_DWORD *)(uintptr_t)(record + 28) = reactive_slots;
  direct_super_index = bsaveAlpha[5];
  if ( direct_super_index == -1 )
    result = 0;
  else
    result = g_ReactiveRuleArrayPtr + 44 * direct_super_index;
  *(_DWORD *)(uintptr_t)(record + 32) = result;
  superclass_index = bsaveAlpha[6];
  if ( superclass_index == -1 )
  {
    *(_DWORD *)(uintptr_t)(record + 40) = 0;
    *(_DWORD *)(uintptr_t)(record + 36) = 0;
  }
  else
  {
    result = 44 * superclass_index;
    superclass = 44 * superclass_index + g_ReactiveRuleArrayPtr;
    *(_DWORD *)(uintptr_t)(record + 40) = 0;
    *(_DWORD *)(uintptr_t)(record + 36) = superclass;
  }
  return result;
}
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;
// 54E67C: using guessed type int dword_54E67C;

//----- (004E27B0) --------------------------------------------------------
int * Class_ResolveSystemSlotTemplate(_DWORD *bsaveData, int itemIndex)
{
  int *result; // eax
  int packedFlags; // ebx
  int whichField; // ebx
  int flagWord; // edi
  int leaveFieldBits; // ebx
  int endSlotFlag; // ebx
  int flagWordSnapshot; // edi
  int networkTestIndex; // ebp
  _DWORD *bsaveFields; // edx
  int networkTest; // ecx
  int nextLevelIndex; // ecx
  int nextLevel; // ecx
  int lastLevelIndex; // ebx
  int lastLevel; // ecx
  int leftNodeIndex; // esi
  int leftNode; // ecx
  int rightNodeIndex; // edi
  int rightNode; // ecx
  int alphaNodeIndex; // ebp
  int alphaNode; // edx

  result = (int *)(uintptr_t)(40 * itemIndex + g_ObjectPatternNetworkArrayPtr);
  *(_BYTE *)result &= ~1u;
  packedFlags = *bsaveData;
  *(_BYTE *)result &= ~2u;
  *result |= 2 * (packedFlags & 1);
  whichField = *bsaveData << 22 >> 24;
  *(_WORD *)result &= 0xF807u;
  flagWord = (8 * (unsigned __int8)whichField) | *result;
  *result = flagWord;
  leaveFieldBits = (unsigned __int8)(*bsaveData << 14 >> 24) << 11;
  *result = flagWord & 0xFFF807FF;
  *result = leaveFieldBits | flagWord & 0xFFF807FF;
  endSlotFlag = *bsaveData << 30 >> 31;
  *(_BYTE *)result &= ~4u;
  flagWordSnapshot = *result;
  result[1] = 0;
  *result = (4 * (endSlotFlag & 1)) | flagWordSnapshot;
  result[2] = bsaveData[1];
  networkTestIndex = bsaveData[2];
  bsaveFields = bsaveData;
  if ( networkTestIndex == -1 )
    networkTest = 0;
  else
    networkTest = g_ClipsPackedExpressionArray + 14 * networkTestIndex;
  result[3] = networkTest;
  nextLevelIndex = bsaveFields[3];
  if ( nextLevelIndex == -1 )
    nextLevel = 0;
  else
    nextLevel = g_ObjectPatternNetworkArrayPtr + 40 * nextLevelIndex;
  result[4] = nextLevel;
  lastLevelIndex = bsaveFields[4];
  if ( lastLevelIndex == -1 )
    lastLevel = 0;
  else
    lastLevel = g_ObjectPatternNetworkArrayPtr + 40 * lastLevelIndex;
  result[5] = lastLevel;
  leftNodeIndex = bsaveFields[5];
  if ( leftNodeIndex == -1 )
    leftNode = 0;
  else
    leftNode = g_ObjectPatternNetworkArrayPtr + 40 * leftNodeIndex;
  result[6] = leftNode;
  rightNodeIndex = bsaveFields[6];
  if ( rightNodeIndex == -1 )
    rightNode = 0;
  else
    rightNode = g_ObjectPatternNetworkArrayPtr + 40 * rightNodeIndex;
  result[7] = rightNode;
  alphaNodeIndex = bsaveFields[7];
  if ( alphaNodeIndex == -1 )
  {
    result[9] = 0;
    result[8] = 0;
  }
  else
  {
    alphaNode = g_ReactiveRuleArrayPtr + 44 * alphaNodeIndex;
    result[9] = 0;
    result[8] = alphaNode;
  }
  return result;
}
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;
// 54E688: using guessed type int dword_54E688;

//----- (004E2970) --------------------------------------------------------
int Class_ClearClassIDTable(void)
{
  int alphaIndex; // ecx
  int recordOffset; // edx
  int v2; // edx
  int v3; // ecx

  alphaIndex = 0;
  if ( g_ReactiveRuleBloadCount > 0 )
  {
    recordOffset = 0;
    do
    {
      Rules_DecrementBitmapCount(*(_DWORD *)(uintptr_t)(recordOffset + g_ReactiveRuleArrayPtr + 20), alphaIndex);
      if ( *(_DWORD *)(uintptr_t)(v2 + g_ReactiveRuleArrayPtr + 24) )
        Rules_DecrementBitmapCount(*(_DWORD *)(uintptr_t)(v2 + g_ReactiveRuleArrayPtr + 24), v3);
      alphaIndex = v3 + 1;
      recordOffset = v2 + 44;
    }
    while ( alphaIndex < g_ReactiveRuleBloadCount );
  }
  if ( g_ReactiveRuleBloadCount )
  {
    Mem_ReleasePoolBlock(g_ReactiveRuleArrayPtr, 44 * g_ReactiveRuleBloadCount);
    g_ReactiveRuleArrayPtr = 0;
    Mem_ReleasePoolBlock(g_ObjectPatternNetworkArrayPtr, 40 * g_ObjectPatternNetworkBloadCount);
    g_ObjectPatternNetworkArrayPtr = 0;
  }
  Rules_SetReactiveRuleList(0);
  return Rules_SetObjectPatternNetworkRoot(0);
}
// 4E2996: variable 'v2' is possibly undefined
// 4E29CD: variable 'v3' is possibly undefined
// 51C718: using guessed type int dword_51C718;
// 51C71C: using guessed type int dword_51C71C;
// 51C720: using guessed type int dword_51C720;
// 51C724: using guessed type int dword_51C724;

//----- (004E2A30) --------------------------------------------------------
int  Class_ParseSuperclasses(int readSource, int className)
{
  int **linkHead; // esi
  int **linkTail; // ebp
  int v6; // edx
  int **linkScan; // eax
  int *superclass; // eax
  int *theClass; // ecx
  _DWORD *freeLink; // edx
  int **newLink; // eax
  _DWORD *freeNode; // edx
  signed int packedLinks; // eax
  int plinks; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int constructNameStr; // eax
  int v22; // ecx
  int v23; // ecx

  linkHead = 0;
  linkTail = 0;
  if ( g_ParserCurrentTokenType == 100
    && (Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType), g_ParserCurrentTokenType == 2)
    && g_ClipsParserTokenValue == g_Symbol_IsA )
  {
    IO_OutWriteToken(asc_50E6E8);
    Parser_NextToken(readSource, v6);
    if ( g_ParserCurrentTokenType == 101 )
    {
LABEL_23:
      if ( linkHead )
      {
        IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50E7F8);
        freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24);
        if ( freeNode )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24) = *freeNode;
          Class_PackClassLinkList(g_ClipsMemFreeListTemp, linkHead);
        }
        else
        {
          packedLinks = Mem_HeapAllocWithRetry((_DWORD *)6);
          Class_PackClassLinkList(packedLinks, linkHead);
        }
        return plinks;
      }
      else
      {
        Rules_PrintErrorID((int)(intptr_t)aInherpsr, 4, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMustHaveAtLeas, v23);
        return 0;
      }
    }
    else
    {
      while ( 1 )
      {
        if ( g_ParserCurrentTokenType != 2 )
        {
          Parser_ReportSyntaxError();
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        if ( Rules_FindModuleSeparator((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(className + 16)) )
        {
          Module_ReportIllegalSpecifierError();
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        if ( className == g_ClipsParserTokenValue )
        {
          Rules_PrintErrorID((int)(intptr_t)aInherpsr, 1, 0);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAClassMayNotHa, v16);
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        linkScan = linkHead;
        if ( linkHead )
          break;
LABEL_14:
        superclass = Class_LookupInScope((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsParserTokenValue + 16));
        theClass = superclass;
        if ( !superclass )
        {
          Rules_PrintErrorID((int)(intptr_t)aInherpsr, 3, 0);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAClassMustBe_0, v18);
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        if ( superclass == (int *)(uintptr_t)g_Class_InstanceName || superclass == (int *)(uintptr_t)g_Class_InstanceAddress || superclass == **(int ***)(uintptr_t)(g_Class_InstanceName + 36) )
        {
          Rules_PrintErrorID((int)(intptr_t)aInherpsr, 6, 0);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAUserDefinedCl, v19);
          constructNameStr = Rules_GetConstructNameString(v20);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], constructNameStr, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__28, v22);
          Mem_ReturnListToFreePool(linkHead);
          return 0;
        }
        freeLink = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
        if ( freeLink )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeLink;
          newLink = (int **)(uintptr_t)g_ClipsMemFreeListTemp;
        }
        else
        {
          newLink = (int **)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        *newLink = theClass;
        if ( linkHead )
          linkTail[1] = (int *)newLink;
        else
          linkHead = newLink;
        linkTail = newLink;
        newLink[1] = 0;
        IO_OutWriteToken(asc_50E6E8);
        Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
        if ( g_ParserCurrentTokenType == 101 )
          goto LABEL_23;
      }
      while ( g_ClipsParserTokenValue != **linkScan )
      {
        linkScan = (int **)linkScan[1];
        if ( !linkScan )
          goto LABEL_14;
      }
      Rules_PrintErrorID((int)(intptr_t)aInherpsr, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAClassMayInher, v17);
      Mem_ReturnListToFreePool(linkHead);
      return 0;
    }
  }
  else
  {
    Parser_ReportSyntaxError();
    return 0;
  }
}
// 4E2A81: variable 'v6' is possibly undefined
// 4E2B56: variable 'v10' is possibly undefined
// 4E2BCF: variable 'v15' is possibly undefined
// 4E2C06: variable 'v16' is possibly undefined
// 4E2C35: variable 'v17' is possibly undefined
// 4E2C64: variable 'v18' is possibly undefined
// 4E2C93: variable 'v19' is possibly undefined
// 4E2C9A: variable 'v20' is possibly undefined
// 4E2CB8: variable 'v22' is possibly undefined
// 4E2D04: variable 'v23' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AD98: using guessed type int dword_51AD98;
// 51AD9C: using guessed type int dword_51AD9C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6FC: using guessed type int dword_54E6FC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004E2D40) --------------------------------------------------------
int  Class_BuildPrecedenceList(int theClass, unsigned __int16 *superclassLinks)
{
  _DWORD *allSuperclasses; // eax
  _DWORD *partialOrderList; // esi
  _DWORD *freeOrderNode; // ecx
  _DWORD *classOrderNode; // eax
  int superOffset; // ebp
  unsigned int i; // edx
  int scanClass; // eax
  unsigned int nextIndex; // edi
  unsigned int linkIndex; // ecx
  int superClass; // edx
  unsigned int directIndex; // edx
  int directOffset; // ebp
  unsigned int nextDirectIndex; // edi
  unsigned int directLinkIndex; // ecx
  int directSuperClass; // edx
  _DWORD *currentNode; // edx
  _DWORD *progressMarker; // ebx
  _DWORD *prevNode; // ecx
  _DWORD *dependencyLink; // ebp
  int *removedNode; // ebp
  _DWORD *freePrecedenceLink; // edi
  int *precedenceLink; // eax
  int classPtr; // edi
  _DWORD *freeLinkNode; // edx
  signed int sentinelNode; // eax
  int *oldListHead; // edx
  _DWORD *freePackedLinks; // ecx
  signed int packedLinksMem; // ecx
  int v30; // ecx
  _DWORD *cycleDepLink; // ebp
  _DWORD *cycleNode; // eax
  int *precedenceTail; // [esp+8h] [ebp-24h]
  int *precedenceList; // [esp+Ch] [ebp-20h]
  int *scanNode; // [esp+14h] [ebp-18h]

  allSuperclasses = Class_CollectAllSuperclasses(0, superclassLinks);
  partialOrderList = allSuperclasses;
  if ( theClass )
  {
    freeOrderNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    if ( freeOrderNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeOrderNode;
      classOrderNode = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      classOrderNode = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    classOrderNode[1] = 0;
    classOrderNode[2] = 0;
    classOrderNode[3] = partialOrderList;
    *classOrderNode = theClass;
    scanNode = (int *)(uintptr_t)classOrderNode[3];
    partialOrderList = classOrderNode;
    Class_AddPrecedenceDependency(classOrderNode, theClass, 0, superclassLinks);
  }
  else
  {
    scanNode = allSuperclasses;
  }
  while ( scanNode )
  {
    superOffset = 0;
    Class_AddPrecedenceDependency(partialOrderList, *scanNode, 0, (unsigned __int16 *)(uintptr_t)(*scanNode + 34));
    for ( i = 0; ; i = nextIndex )
    {
      scanClass = *scanNode;
      if ( i >= *(unsigned __int16 *)(uintptr_t)(*scanNode + 34) )
        break;
      nextIndex = i + 1;
      linkIndex = i + 1;
      superClass = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(scanClass + 36) + superOffset);
      superOffset += 4;
      Class_AddPrecedenceDependency(partialOrderList, superClass, linkIndex, (unsigned __int16 *)(uintptr_t)(scanClass + 34));
    }
    scanNode = (int *)(uintptr_t)scanNode[3];
  }
  directIndex = 0;
  directOffset = 0;
  while ( directIndex < *superclassLinks )
  {
    nextDirectIndex = directIndex + 1;
    directLinkIndex = directIndex + 1;
    directSuperClass = *(_DWORD *)(uintptr_t)(*(_DWORD *)(superclassLinks + 1) + directOffset);
    directOffset += 4;
    Class_AddPrecedenceDependency(partialOrderList, directSuperClass, directLinkIndex, superclassLinks);
    directIndex = nextDirectIndex;
  }
  currentNode = partialOrderList;
  progressMarker = 0;
  prevNode = 0;
  precedenceTail = 0;
  precedenceList = 0;
  if ( partialOrderList )
  {
    do
    {
      if ( !currentNode )
      {
        currentNode = partialOrderList;
        progressMarker = (_DWORD *)(uintptr_t)progressMarker[3];
        prevNode = 0;
      }
      if ( currentNode[1] )
      {
        prevNode = currentNode;
        currentNode = (_DWORD *)(uintptr_t)currentNode[3];
      }
      else
      {
        while ( 1 )
        {
          dependencyLink = (_DWORD *)(uintptr_t)currentNode[2];
          if ( !dependencyLink )
            break;
          currentNode[2] = dependencyLink[1];
          --*(_DWORD *)(uintptr_t)(*dependencyLink + 4);
          g_ClipsMemFreeListTemp = (int)(intptr_t)dependencyLink;
          *dependencyLink = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
        }
        removedNode = currentNode;
        if ( prevNode )
          prevNode[3] = currentNode[3];
        else
          partialOrderList = (_DWORD *)(uintptr_t)currentNode[3];
        progressMarker = prevNode;
        freePrecedenceLink = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
        currentNode = (_DWORD *)(uintptr_t)currentNode[3];
        if ( freePrecedenceLink )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freePrecedenceLink;
          precedenceLink = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
        }
        else
        {
          precedenceLink = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        classPtr = *removedNode;
        precedenceLink[1] = 0;
        *precedenceLink = classPtr;
        g_ClipsMemFreeListTemp = (int)(intptr_t)removedNode;
        *removedNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
        if ( precedenceList )
          precedenceTail[1] = (int)(intptr_t)precedenceLink;
        else
          precedenceList = precedenceLink;
        precedenceTail = precedenceLink;
      }
    }
    while ( currentNode != progressMarker );
  }
  if ( partialOrderList )
  {
    Rules_PrintErrorID((int)(intptr_t)aInherpsr, 5, 0);
    Class_PrintClassNameList((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aPartialPrecede, precedenceList);
    Class_ReportPrecedenceLoop(partialOrderList);
    do
    {
      while ( 1 )
      {
        cycleDepLink = (_DWORD *)(uintptr_t)partialOrderList[2];
        if ( !cycleDepLink )
          break;
        partialOrderList[2] = cycleDepLink[1];
        g_ClipsMemFreeListTemp = (int)(intptr_t)cycleDepLink;
        *cycleDepLink = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      }
      cycleNode = partialOrderList;
      partialOrderList = (_DWORD *)(uintptr_t)partialOrderList[3];
      g_ClipsMemFreeListTemp = (int)(intptr_t)cycleNode;
      *cycleNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    while ( partialOrderList );
    Mem_ReturnListToFreePool(precedenceList);
    return 0;
  }
  else
  {
    if ( !theClass )
    {
      freeLinkNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      if ( freeLinkNode )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeLinkNode;
        sentinelNode = g_ClipsMemFreeListTemp;
      }
      else
      {
        sentinelNode = Mem_HeapAllocWithRetry((_DWORD *)8);
      }
      oldListHead = precedenceList;
      precedenceList = (int *)(uintptr_t)sentinelNode;
      *(_DWORD *)(uintptr_t)(sentinelNode + 4) = oldListHead;
    }
    *precedenceList = 0;
    freePackedLinks = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24);
    if ( freePackedLinks )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 24) = *freePackedLinks;
      packedLinksMem = g_ClipsMemFreeListTemp;
    }
    else
    {
      packedLinksMem = Mem_HeapAllocWithRetry((_DWORD *)6);
    }
    Class_PackClassLinkList(packedLinksMem, precedenceList);
    return v30;
  }
}
// 4E2FF5: conditional instruction was optimized away because esi.4!=0
// 4E2EAA: variable 'v19' is possibly undefined
// 4E2F87: variable 'v30' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3090) --------------------------------------------------------
_DWORD * Class_PackClassLinkList(int packedLinks, _DWORD *linkList)
{
  _DWORD *countScan; // eax
  int i; // edx
  _DWORD *copyScan; // eax
  int v7; // edx
  int arrayOffset; // ecx
  _DWORD *result; // eax
  __int16 v10; // dx

  countScan = linkList;
  for ( i = 0; countScan; ++i )
    countScan = (_DWORD *)(uintptr_t)countScan[1];
  if ( i )
    *(_DWORD *)(uintptr_t)(packedLinks + 2) = Mem_SmallBlockAlloc(4 * i);
  else
    *(_DWORD *)(uintptr_t)(packedLinks + 2) = 0;
  copyScan = linkList;
  v7 = 0;
  if ( linkList )
  {
    arrayOffset = 0;
    do
    {
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(packedLinks + 2) + arrayOffset) = *copyScan;
      ++v7;
      copyScan = (_DWORD *)(uintptr_t)copyScan[1];
      arrayOffset += 4;
    }
    while ( copyScan );
  }
  result = Mem_ReturnListToFreePool(linkList);
  *(_WORD *)(uintptr_t)packedLinks = v10;
  return result;
}
// 4E30F7: variable 'v10' is possibly undefined

//----- (004E3110) --------------------------------------------------------
_DWORD * Class_CollectAllSuperclasses(_DWORD *orderList, unsigned __int16 *superclasses)
{
  int linkOffset; // edi
  _DWORD *existingOrder; // eax
  _DWORD *i; // ecx
  _DWORD *freeListEntry; // ebx
  _DWORD *newOrder; // eax
  int superclass; // edx
  unsigned int superIndex; // [esp+0h] [ebp-18h]

  linkOffset = 0;
  superIndex = 0;
  while ( *superclasses > superIndex )
  {
    existingOrder = orderList;
    for ( i = 0; existingOrder; existingOrder = (_DWORD *)(uintptr_t)existingOrder[3] )
    {
      if ( *existingOrder == *(_DWORD *)(uintptr_t)(linkOffset + *(_DWORD *)(superclasses + 1)) )
        break;
      i = existingOrder;
    }
    if ( existingOrder )
    {
      linkOffset += 4;
      ++superIndex;
    }
    else
    {
      freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
      if ( freeListEntry )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeListEntry;
        newOrder = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
      }
      else
      {
        newOrder = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      superclass = *(_DWORD *)(uintptr_t)(*(_DWORD *)(superclasses + 1) + linkOffset);
      newOrder[3] = 0;
      newOrder[2] = 0;
      newOrder[1] = 0;
      *newOrder = superclass;
      if ( i )
        i[3] = newOrder;
      else
        orderList = newOrder;
      orderList = (_DWORD *)Class_CollectAllSuperclasses((int)(intptr_t)orderList, *(_DWORD *)(uintptr_t)(linkOffset + *(_DWORD *)(superclasses + 1)) + 34);
      linkOffset += 4;
      ++superIndex;
    }
  }
  return orderList;
}
// 4E3197: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E31E0) --------------------------------------------------------
__int16  Class_AddPrecedenceDependency(_DWORD *classList, int theClass, unsigned int startIndex, unsigned __int16 *superclassLinks)
{
  int v7; // ecx
  int i; // esi
  __int16 result; // ax
  _DWORD *freeNode; // edx
  _DWORD *superNode; // eax
  _DWORD *newDependency; // ecx
  _DWORD *classNode; // [esp+0h] [ebp-10h]

  classNode = Class_FindClassLinkNode(classList, theClass);
  for ( i = 4 * v7; ; i += 4 )
  {
    result = *superclassLinks;
    if ( startIndex >= *superclassLinks )
      break;
    freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeNode;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    superNode = Class_FindClassLinkNode(classList, *(_DWORD *)(uintptr_t)(*(_DWORD *)(superclassLinks + 1) + i));
    *newDependency = superNode;
    newDependency[1] = classNode[2];
    classNode[2] = newDependency;
    ++startIndex;
    ++*(_DWORD *)(uintptr_t)(*newDependency + 4);
  }
  return result;
}
// 4E31F4: variable 'v7' is possibly undefined
// 4E3230: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3270) --------------------------------------------------------
_DWORD * Class_FindClassLinkNode(_DWORD *result, int theClass)
{
  for ( ; result; result = (_DWORD *)(uintptr_t)result[3] )
  {
    if ( theClass == *result )
      break;
  }
  return result;
}

//----- (004E3280) --------------------------------------------------------
signed int  Class_ReportPrecedenceLoop(_DWORD *orderList)
{
  _DWORD *i; // ecx
  _DWORD *j; // edi
  int supportList; // ebx
  _DWORD *supportedOrder; // edx
  _DWORD *freedLink; // eax
  int v6; // eax
  _DWORD *freeListEntry; // esi
  _DWORD *newLink; // eax
  _DWORD *k; // ebx
  int *m; // esi
  int v11; // ecx
  int v12; // ecx

  for ( i = orderList; orderList; orderList = (_DWORD *)(uintptr_t)orderList[3] )
    orderList[1] = 0;
  for ( j = i; j; j = (_DWORD *)(uintptr_t)j[3] )
  {
    if ( j[1] )
    {
      v6 = j[2];
      supportList = *(_DWORD *)(uintptr_t)(v6 + 4);
      *(_DWORD *)(uintptr_t)(v6 + 4) = 0;
    }
    else
    {
      supportList = j[2];
      j[2] = 0;
    }
    while ( supportList )
    {
      supportedOrder = Class_FindClassLinkNode(i, *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)supportList);
      if ( !supportedOrder[1] )
      {
        freeListEntry = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
        if ( freeListEntry )
        {
          g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
          *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeListEntry;
          newLink = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
        }
        else
        {
          newLink = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
        }
        *newLink = j;
        newLink[1] = supportedOrder[2];
        supportedOrder[1] = 1;
        supportedOrder[2] = newLink;
      }
      freedLink = (_DWORD *)(uintptr_t)supportList;
      supportList = *(_DWORD *)(uintptr_t)(supportList + 4);
      g_ClipsMemFreeListTemp = (int)(intptr_t)freedLink;
      *freedLink = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    }
  }
  for ( k = i; k; k = (_DWORD *)(uintptr_t)k[3] )
    k[1] = 0;
  for ( m = i; !m[1]; m = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)m[2] )
    m[1] = 1;
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aPrecedenceLoop, (int)(intptr_t)i);
  if ( m[1] == 1 )
  {
    v11 = 0;
    do
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_50E6E8, v11);
      Class_PrintName(*m, v12);
      m[1] = v11;
      m = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)m[2];
    }
    while ( m[1] == 1 );
  }
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_50E6E8, v11);
  return Class_PrintName(*m, 1);
}
// 4E32C7: variable 'i' is possibly undefined
// 4E33A3: variable 'v11' is possibly undefined
// 4E33B1: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004E3400) --------------------------------------------------------
signed int  Class_PrintClassNameList(int logicalName, int headerMessage, int *classLinks)
{
  int v3; // ecx

  v3 = logicalName;
  if ( headerMessage )
    Output_Write(logicalName, headerMessage, logicalName);
  while ( classLinks )
  {
    Output_Write(v3, (int)(intptr_t)asc_50E6E8, v3);
    Class_PrintName(*classLinks, 0);
    classLinks = (int *)(uintptr_t)classLinks[1];
  }
  return Output_Write(v3, (int)(intptr_t)asc_50E840, v3);
}
// 4E3415: variable 'v3' is possibly undefined
