/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0048D570) --------------------------------------------------------
int __fastcall Rules_ReportMultifieldAssertIntoSingleSlotError(int a1 CLASH95_UNUSED, int theDeftemplate)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *slotName; // edx
  char *v7; // eax
  int v8; // ecx
  int v9; // ecx
  char *v10; // eax
  char *deftemplateName; // edx
  int v12; // ecx

  Rules_PrintErrorID((int)(intptr_t)aTmpltfun, 2, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAttemptedToAss, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIntoTheSingleF, v4);
  if ( v5 )
  {
    v7 = g_IO_LogicalNameTable_WError[0];
    slotName = *(char **)(uintptr_t)(*(_DWORD *)(uintptr_t)v5 + 16);
  }
  else
  {
    slotName = aUnknown_2;
    v7 = g_IO_LogicalNameTable_WError[0];
  }
  Output_Write((int)(intptr_t)v7, (int)(intptr_t)slotName, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOfDeftemplate, v8);
  if ( theDeftemplate )
  {
    v10 = g_IO_LogicalNameTable_WError[0];
    deftemplateName = *(char **)(uintptr_t)(*(_DWORD *)(uintptr_t)theDeftemplate + 16);
  }
  else
  {
    deftemplateName = aUnknown_2;
    v10 = g_IO_LogicalNameTable_WError[0];
  }
  Output_Write((int)(intptr_t)v10, (int)(intptr_t)deftemplateName, v9);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__10, v12);
  return Lexer_ErrorRecover(1);
}
// 48D595: variable 'v3' is possibly undefined
// 48D5A4: variable 'v4' is possibly undefined
// 48D5AB: variable 'v5' is possibly undefined
// 48D5C6: variable 'v8' is possibly undefined
// 48D5D9: variable 'v9' is possibly undefined
// 48D5E8: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D620) --------------------------------------------------------
int  Rules_CheckFactAgainstSlotConstraints(int theFact)
{
  int result; // eax
  int theDeftemplate; // ecx
  int slotPtr; // ecx
  int fieldIndex; // ebx
  __int16 *fieldPtr; // edx
  int v7; // ecx
  int violationCode; // esi
  int v9; // ecx
  int v10; // ecx
  int *v11; // ecx
  int dataObject; // [esp+0h] [ebp-44h] BYREF
  int valueType CLASH95_UNUSED; // [esp+4h] [ebp-40h]
  int value CLASH95_UNUSED; // [esp+8h] [ebp-3Ch]
  int rangeBegin CLASH95_UNUSED; // [esp+Ch] [ebp-38h]
  int rangeEnd CLASH95_UNUSED; // [esp+10h] [ebp-34h]
  _BYTE factIdBuffer[44]; // [esp+18h] [ebp-2Ch] BYREF

  result = Rules_DynamicConstraintCheckingEnabled();
  if ( result )
  {
    theDeftemplate = *(_DWORD *)(uintptr_t)(theFact + 16);
    if ( theDeftemplate )
    {
      if ( (*(_BYTE *)(uintptr_t)(theDeftemplate + 24) & 1) == 0 )
      {
        slotPtr = *(_DWORD *)(uintptr_t)(theDeftemplate + 20);
        fieldIndex = 0;
        if ( slotPtr )
        {
          while ( 1 )
          {
            fieldPtr = (__int16 *)(uintptr_t)(theFact + 54 + 6 * fieldIndex);
            if ( (*(_BYTE *)(uintptr_t)(slotPtr + 4) & 1) != 0 )
            {
              valueType = 4;
              value = *(_DWORD *)(fieldPtr + 1);
              rangeBegin = 0;
              ++fieldIndex;
              rangeEnd = *(_DWORD *)(uintptr_t)(*(_DWORD *)(fieldPtr + 1) + 6) - 1;
            }
            else
            {
              valueType = *fieldPtr;
              ++fieldIndex;
              value = *(_DWORD *)(fieldPtr + 1);
            }
            result = Rules_CheckFieldAgainstConstraint(&dataObject, *(_DWORD *)(uintptr_t)(slotPtr + 8));
            violationCode = result;
            if ( result )
              break;
            slotPtr = *(_DWORD *)(uintptr_t)(v7 + 16);
            if ( !slotPtr )
              return result;
          }
          sprintf_(factIdBuffer, "fact f-%-5ld ", *(_DWORD *)(uintptr_t)(theFact + 24));
          Rules_PrintErrorID((int)(intptr_t)aCstrnchk_0, 1, 1);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSlotValue, v9);
          Rules_PrintDataObject((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)&dataObject);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_5046F0, v10);
          Rules_PrintConstraintViolationMessage(0, (int)(intptr_t)factIdBuffer, 0, 0, *v11, 0, violationCode, v11[2], 1);
          return Rules_SetEvaluationErrorFlag(1);
        }
      }
    }
  }
  return result;
}
// 48D68A: variable 'v7' is possibly undefined
// 48D6DD: variable 'v9' is possibly undefined
// 48D6F8: variable 'v10' is possibly undefined
// 48D70E: variable 'v11' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048D730) --------------------------------------------------------
signed int  Rules_CheckLiteralSlotValueConstraint(int *exprList, int thePlace)
{
  int v3; // edx
  signed int violationCode; // eax
  int *v6; // ecx
  int v7; // edx
  char *errorMessage; // eax

  if ( !Rules_StaticConstraintCheckingEnabled() )
    return 1;
  violationCode = Rules_CheckFieldExprListAgainstConstraint(exprList, *(_DWORD *)(uintptr_t)(v3 + 8));
  v7 = violationCode;
  if ( !violationCode )
    return 1;
  if ( violationCode == 5 )
    errorMessage = aLiteralSlotVal;
  else
    errorMessage = aALiteralSlotVa;
  Rules_PrintConstraintViolationMessage((int)(intptr_t)errorMessage, thePlace, 0, 1, *v6, 0, v7, v6[2], 1);
  return 0;
}
// 48D74D: variable 'v3' is possibly undefined
// 48D76E: variable 'v6' is possibly undefined

//----- (0048D790) --------------------------------------------------------
int  Lexer_GetSlotByOrdinal(int theDeftemplate, int position)
{
  int result; // eax
  int slotIndex; // edx

  result = *(_DWORD *)(uintptr_t)(theDeftemplate + 20);
  slotIndex = 0;
  if ( !result )
    return 0;
  while ( slotIndex != position )
  {
    result = *(_DWORD *)(uintptr_t)(result + 16);
    ++slotIndex;
    if ( !result )
      return 0;
  }
  return result;
}

//----- (0048D7B0) --------------------------------------------------------
signed int  Lexer_FindSymbolIndex(int theDeftemplate, int slotName)
{
  _DWORD *slotPtr; // eax
  int position; // edx

  slotPtr = *(_DWORD **)(uintptr_t)(theDeftemplate + 20);
  position = 1;
  if ( !slotPtr )
    return 0;
  while ( slotName != *slotPtr )
  {
    slotPtr = (_DWORD *)(uintptr_t)slotPtr[4];
    ++position;
    if ( !slotPtr )
      return 0;
  }
  return position;
}

//----- (0048D7E0) --------------------------------------------------------
signed int  Rules_PrintTemplateFactSlots(int logicalName, int theFact, int a3)
{
  __int16 *fieldPtr; // ebp
  _DWORD *theDeftemplate; // edi
  int v6; // ecx
  int v7; // ecx
  int slotPtr; // edi
  int v9; // ecx
  int v10; // ecx
  int theSegment; // ebx

  fieldPtr = (__int16 *)(uintptr_t)(theFact + 54);
  /* 64-bit host repair (save-facts path): the deftemplate pointer at
     (fact + 16) is a 32-bit low32-arena pointer; an 8-byte load here reads
     into the neighbouring field and faults. */
  theDeftemplate = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theFact + 16);
  Output_Write(logicalName, (int)(intptr_t)asc_504720, a3);
  Output_Write(logicalName, *(_DWORD *)(uintptr_t)(*theDeftemplate + 16), v6);
  if ( theDeftemplate[5] )
    Output_Write(logicalName, (int)(intptr_t)asc_5046F0, v7);
  slotPtr = theDeftemplate[5];
  if ( slotPtr )
  {
    while ( 1 )
    {
      Output_Write(logicalName, (int)(intptr_t)asc_504720, v7);
      Output_Write(logicalName, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)slotPtr + 16), v9);
      if ( (*(_BYTE *)(uintptr_t)(slotPtr + 4) & 1) != 0 )
      {
        theSegment = *(_DWORD *)(fieldPtr + 1);
        if ( *(int *)(uintptr_t)(theSegment + 6) > 0 )
        {
          Output_Write(logicalName, (int)(intptr_t)asc_5046F0, v10);
          Lexer_OutputFieldRange(logicalName, *(_DWORD *)(fieldPtr + 1), *(_DWORD *)(uintptr_t)(theSegment + 6) - 1, 0, 0);
        }
      }
      else
      {
        Output_Write(logicalName, (int)(intptr_t)asc_5046F0, v10);
        /* 64-bit host repair: the field value cell is a 32-bit pointer. */
        Rules_PrintAtomValue(logicalName, *fieldPtr, (int *)(uintptr_t)*(_DWORD *)(fieldPtr + 1));
      }
      Output_Write(logicalName, (int)(intptr_t)asc_504724, v10);
      slotPtr = *(_DWORD *)(uintptr_t)(slotPtr + 16);
      fieldPtr += 3;
      if ( !slotPtr )
        break;
      Output_Write(logicalName, (int)(intptr_t)asc_5046F0, v7);
    }
  }
  return Output_Write(logicalName, (int)(intptr_t)asc_504724, v7);
}
// 48D7FE: variable 'v6' is possibly undefined
// 48D88B: variable 'v7' is possibly undefined
// 48D827: variable 'v9' is possibly undefined
// 48D839: variable 'v10' is possibly undefined

//----- (0048D8C0) --------------------------------------------------------
int Lexer_MarkImpliedTemplates(void)
{
  int result; // eax
  int i; // edi
  _BYTE *j; // esi
  _DWORD v3[7]; // [esp+0h] [ebp-1Ch] BYREF

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    /* 64-bit host repair (save-facts path): the deftemplate list head at
       (module item + 4) and the construct name at (*deftemplate + 16) are
       32-bit low32-arena pointers; the raw decompile read them with 8-byte
       loads, concatenating two neighbouring 32-bit pointers into one bogus
       64-bit address (SIGSEGV in the first save-facts enumeration). */
    for ( j = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(Module_GetItem(i, g_ClipsDeftemplateModuleItemId) + 4); j; j = (_BYTE *)(uintptr_t)Rules_GetNextDeftemplate((int)(intptr_t)j) )
    {
      int visible = Rules_FindImportExportConstruct(aDeftemplate_6, v3, (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)j + 16), 1, 0) != 0;

      if ( getenv("CLASH95_TRACE_SAVE_FACTS") )
        fprintf(
          stderr,
          "[savefacts] mark deftemplate=%s visible=%d\n",
          (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)j + 16),
          visible);
      if ( visible )
        j[24] |= 4u;
      else
        j[24] &= ~4u;
    }
    result = Module_NextEnum(i);
  }
  return result;
}
// 54E654: using guessed type int dword_54E654;

//----- (0048D940) --------------------------------------------------------
_DWORD * Lexer_FindSlotWithIndex(int theDeftemplate, int slotName, _DWORD *whichOne)
{
  _DWORD *result; // eax

  *whichOne = 1;
  result = *(_DWORD **)(uintptr_t)(theDeftemplate + 20);
  if ( result )
  {
    while ( slotName != *result )
    {
      ++*whichOne;
      result = (_DWORD *)(uintptr_t)result[4];
      if ( !result )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    *whichOne = -1;
    return 0;
  }
  return result;
}

//----- (0048D970) --------------------------------------------------------
int  Rules_CreateDeftemplateRecord(int deftemplateName, char implied)
{
  int free_template_record; // ecx
  int template_record; // edx
  int module_data; // eax

  free_template_record = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 144);
  if ( free_template_record )
  {
    g_ClipsMemFreeListTemp = free_template_record;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 144) = *(_DWORD *)(uintptr_t)free_template_record;
    template_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    template_record = Mem_HeapAllocWithRetry((_DWORD *)0x24);
  }
  *(_DWORD *)(uintptr_t)(template_record + 4) = 0;
  *(_DWORD *)(uintptr_t)template_record = deftemplateName;
  *(_BYTE *)(uintptr_t)(template_record + 24) &= 0xFEu;
  *(_DWORD *)(uintptr_t)(template_record + 20) = 0;
  *(_DWORD *)(uintptr_t)(template_record + 24) |= implied & 1;
  *(_DWORD *)(uintptr_t)(template_record + 32) = 0;
  *(_BYTE *)(uintptr_t)(template_record + 24) |= 4u;
  *(_DWORD *)(uintptr_t)(template_record + 28) = 0;
  *(_DWORD *)(uintptr_t)(template_record + 16) = 0;
  *(_WORD *)(uintptr_t)(template_record + 24) &= 5u;
  if ( Rules_GetWatchItemState((int)(intptr_t)aFacts_0) )
    Rules_SetFactWatchFlag(1, template_record);
  module_data = Module_GetItem(0, g_ClipsDeftemplateModuleItemId);
  *(_DWORD *)(uintptr_t)(template_record + 8) = module_data;
  Rules_AppendConstructToModuleList(template_record);
  Rules_DeftemplateInstallSlots((_DWORD *)(uintptr_t)template_record, template_record);
  return template_record;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E654: using guessed type int dword_54E654;

//----- (0048DA40) --------------------------------------------------------
int  Rules_MatchFactAgainstPatternNetwork(
        int result,
        int patternPtr,
        _DWORD *markers,
        int offset,
        double a5,
        int endMark)
{
  int currentPattern; // esi
  int fieldIndex; // ebx
  int v9; // ecx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // eax
  int theFact; // [esp+0h] [ebp-1Ch]
  int whichSlot; // [esp+Ch] [ebp-10h]

  theFact = result;
  currentPattern = patternPtr;
  if ( patternPtr )
  {
    whichSlot = *(_DWORD *)(uintptr_t)(patternPtr + 20) << 16 >> 24;
    g_ClipsFactMatchMarkerList = (int)(intptr_t)markers;
    g_CurrentPatternFact = result;
    do
    {
      fieldIndex = (unsigned __int8)*(_DWORD *)(uintptr_t)(currentPattern + 20);
      if ( *(_DWORD *)(uintptr_t)(currentPattern + 20) << 16 >> 24 == whichSlot )
        fieldIndex += offset;
      result = Rules_ShouldProcessPatternNode(currentPattern);
      if ( !result )
      {
        BYTE1(result) = *(_BYTE *)(uintptr_t)(currentPattern + 12);
        if ( (result & 0x100) != 0 )
        {
          if ( (*(_BYTE *)(uintptr_t)(currentPattern + 12) & 0x40) == 0
            || !g_ClipsFactMatchMarkerList
            || (v12 = *(_DWORD *)(uintptr_t)(currentPattern + 20) << 16 >> 24, *(__int16 *)(uintptr_t)(g_ClipsFactMatchMarkerList + 4) != v12)
            || (v13 = 6 * v12 + g_CurrentPatternFact, *(_WORD *)(uintptr_t)(v13 + 54) != 4)
            || (v9 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v13 + 56) + 6), fieldIndex + (*(_DWORD *)(uintptr_t)(currentPattern + 20) << 8 >> 24) == v9) )
          {
            if ( Rules_EvaluatePatternNetworkTest(currentPattern, *(_DWORD *)(uintptr_t)(currentPattern + 24), 0, a5) )
            {
              if ( (*(_BYTE *)(uintptr_t)(currentPattern + 12) & 4) != 0 )
                Rules_AttachFactPatternMatch(theFact, markers, (signed int *)(uintptr_t)currentPattern, a5);
              v11 = currentPattern;
              v10 = 0;
              goto LABEL_7;
            }
          }
        }
        else
        {
          if ( (result & 0x200) == 0 )
            continue;
          if ( *(_DWORD *)(uintptr_t)(currentPattern + 20) << 16 >> 24 == whichSlot )
            Rules_MatchMultifieldWildcardInPattern(currentPattern, (int)(intptr_t)markers, offset, endMark, a5);
          else
            Rules_MatchMultifieldWildcardInPattern(currentPattern, (int)(intptr_t)markers, 0, endMark, a5);
        }
      }
      v10 = 1;
      v11 = currentPattern;
LABEL_7:
      result = Rules_AdvancePatternNetworkNode(v10, v11);
      currentPattern = result;
    }
    while ( currentPattern );
  }
  return result;
}
// 48DAE1: conditional instruction was optimized away because %var_18.4==0
// 48DB2F: variable 'v9' is possibly undefined
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (0048DBA0) --------------------------------------------------------
int  Rules_MatchMultifieldWildcardInPattern(int theNode, int markers, int offset, int endMark, double a5)
{
  int theSegment; // edi
  _DWORD *freeMark; // edx
  signed int newMark; // eax
  int v9; // eax
  int v10; // edi
  int result; // eax
  int repeatCount; // edi
  int newOffset; // ebp
  int theTest; // edx
  _DWORD *theMark; // [esp+Ch] [ebp-10h]

  theSegment = *(_DWORD *)(uintptr_t)(g_CurrentPatternFact + 6 * (*(_DWORD *)(uintptr_t)(theNode + 20) << 16 >> 24) + 56);
  freeMark = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 80);
  if ( freeMark )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80) = *freeMark;
    newMark = g_ClipsMemFreeListTemp;
  }
  else
  {
    newMark = Mem_HeapAllocWithRetry((_DWORD *)0x14);
  }
  *(_DWORD *)(uintptr_t)newMark = (unsigned __int8)*(_DWORD *)(uintptr_t)(theNode + 20) - 1;
  *(_WORD *)(uintptr_t)(newMark + 4) = HIBYTE(*(_WORD *)(uintptr_t)(theNode + 20));
  theMark = (_DWORD *)(uintptr_t)newMark;
  *(_DWORD *)(uintptr_t)(newMark + 8) = (unsigned __int8)*(_DWORD *)(uintptr_t)(theNode + 20) - 1 + offset;
  *(_DWORD *)(uintptr_t)(newMark + 16) = 0;
  if ( endMark )
    *(_DWORD *)(uintptr_t)(endMark + 16) = newMark;
  else
    g_ClipsFactMatchMarkerList = newMark;
  if ( (*(_BYTE *)(uintptr_t)(theNode + 12) & 0x40) != 0 )
  {
    v9 = *(_DWORD *)(uintptr_t)(theSegment + 6) - ((*(_DWORD *)(uintptr_t)(theNode + 20) << 8 >> 24) + 1);
    v10 = theMark[2];
    theMark[3] = v9;
    if ( v9 < v10 )
      theMark[3] = v10 - 1;
    if ( !*(_DWORD *)(uintptr_t)(theNode + 24) || Rules_EvaluatePatternNetworkTest(theNode, *(_DWORD *)(uintptr_t)(theNode + 24), endMark, a5) )
    {
      if ( (*(_BYTE *)(uintptr_t)(theNode + 12) & 4) != 0 )
        Rules_AttachFactPatternMatch(g_CurrentPatternFact, (_DWORD *)(uintptr_t)g_ClipsFactMatchMarkerList, (signed int *)(uintptr_t)theNode, a5);
      Rules_MatchFactAgainstPatternNetwork(g_CurrentPatternFact, *(_DWORD *)(uintptr_t)(theNode + 28), g_ClipsFactMatchMarkerList, 0, a5, (int)(intptr_t)theMark);
    }
    g_ClipsMemFreeListTemp = (int)(intptr_t)theMark;
    *theMark = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
    if ( endMark )
      *(_DWORD *)(uintptr_t)(endMark + 16) = 0;
LABEL_14:
    result = markers;
    g_ClipsFactMatchMarkerList = markers;
    return result;
  }
  repeatCount = *(_DWORD *)(uintptr_t)(theSegment + 6) - (*(_DWORD *)(uintptr_t)(newMark + 8) + (*(_DWORD *)(uintptr_t)(theNode + 20) << 8 >> 24));
  if ( repeatCount >= 0 )
  {
    newOffset = offset + repeatCount - 1;
    do
    {
      theMark[3] = repeatCount - 1 + theMark[2];
      theTest = *(_DWORD *)(uintptr_t)(theNode + 24);
      if ( !theTest || Rules_EvaluatePatternNetworkTest(theNode, theTest, offset, a5) )
        Rules_MatchFactAgainstPatternNetwork(g_CurrentPatternFact, *(_DWORD *)(uintptr_t)(theNode + 28), g_ClipsFactMatchMarkerList, newOffset, a5, (int)(intptr_t)theMark);
      --repeatCount;
      --newOffset;
    }
    while ( repeatCount >= 0 );
  }
  g_ClipsMemFreeListTemp = (int)(intptr_t)theMark;
  *theMark = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 80) = g_ClipsMemFreeListTemp;
  if ( !endMark )
    goto LABEL_14;
  *(_DWORD *)(uintptr_t)(endMark + 16) = 0;
  result = markers;
  g_ClipsFactMatchMarkerList = markers;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E528: using guessed type int dword_54E528;
// 54E52C: using guessed type int dword_54E52C;

//----- (0048DDF0) --------------------------------------------------------
int  Rules_AdvancePatternNetworkNode(int finishedMatching, int thePattern)
{
  g_ClipsEvaluationError = 0;
  if ( finishedMatching || !*(_DWORD *)(uintptr_t)(thePattern + 28) )
  {
    while ( !*(_DWORD *)(uintptr_t)(thePattern + 40) )
    {
      thePattern = *(_DWORD *)(uintptr_t)(thePattern + 32);
      if ( !thePattern )
        return thePattern;
      if ( (*(_BYTE *)(uintptr_t)(thePattern + 12) & 2) != 0 )
        return 0;
    }
    return *(_DWORD *)(uintptr_t)(thePattern + 40);
  }
  else
  {
    return *(_DWORD *)(uintptr_t)(thePattern + 28);
  }
}
// 51A964: using guessed type int dword_51A964;

//----- (0048DE30) --------------------------------------------------------
int * Rules_AttachFactPatternMatch(int theFact, _DWORD *markers, signed int *thePattern, double a4)
{
  int *partial_match; // esi
  int link; // eax
  int old_fact_links; // ebx
  int join; // ecx
  int *result; // eax

  partial_match = (int *)(uintptr_t)(unsigned int)Rules_AppendExpressionValueNode(theFact, markers, thePattern);
  old_fact_links = *(_DWORD *)(uintptr_t)(theFact + 20);
  link = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( link )
  {
    g_ClipsMemFreeListTemp = link;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *(_DWORD *)(uintptr_t)link;
    link = g_ClipsMemFreeListTemp;
  }
  else
  {
    link = Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *(_DWORD *)(uintptr_t)(theFact + 20) = link;
  *(_DWORD *)(uintptr_t)link = old_fact_links;
  *(_DWORD *)(uintptr_t)(link + 8) = (int)(intptr_t)thePattern;
  *(_DWORD *)(uintptr_t)(link + 4) = (int)(intptr_t)partial_match;
  result = (int *)(uintptr_t)(unsigned int)link;
  join = thePattern[2];
  while ( join )
  {
    result = Rules_DriveJoinNetwork(partial_match, (char *)(uintptr_t)(unsigned int)join, 1, a4);
    join = *(_DWORD *)(uintptr_t)(join + 32);
  }
  return result;
}
// 48DE46: variable 'v5' is possibly undefined
// 48DE85: variable 'v12' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048DEA0) --------------------------------------------------------
int  Rules_EvaluatePatternNetworkTest(signed int patternPtr, int theTest, int a3, double a4)
{
  __int16 exprType; // ax
  int operatorValue; // eax
  int orChild; // ecx
  int result; // eax
  int v9 CLASH95_UNUSED; // ecx
  int savedExprNested; // esi
  int savedExprSimple; // esi
  int savedExprRange; // esi
  int andChild; // ecx
  int v14 CLASH95_UNUSED; // ecx
  _DWORD parsed[6]; // [esp-4h] [ebp-24h] BYREF
  int v17 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

  v17 = a3;
  if ( !theTest )
    return 1;
  exprType = *(_WORD *)(uintptr_t)theTest;
  if ( *(_WORD *)(uintptr_t)theTest >= 0x20u )
  {
    if ( *(_WORD *)(uintptr_t)theTest <= 0x20u )
    {
      savedExprSimple = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = theTest;
      result = Rules_TestPatternFieldSimple(*(_DWORD *)(uintptr_t)(theTest + 2));
      g_ClipsCurrentExpression = savedExprSimple;
      return result;
    }
    if ( exprType == 33 )
    {
      savedExprNested = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = theTest;
      result = Rules_TestPatternNestedField(*(_DWORD *)(uintptr_t)(theTest + 2));
      g_ClipsCurrentExpression = savedExprNested;
      return result;
    }
  }
  else if ( exprType == 25 )
  {
    savedExprRange = g_ClipsCurrentExpression;
    g_ClipsCurrentExpression = theTest;
    result = Rules_EvalMultifieldIndexInRange(*(_DWORD *)(uintptr_t)(theTest + 2), (uintptr_t)parsed);
    g_ClipsCurrentExpression = savedExprRange;
    return result;
  }
  operatorValue = *(_DWORD *)(uintptr_t)(theTest + 2);
  if ( operatorValue == g_ClipsSymbolOr )
  {
    orChild = *(_DWORD *)(uintptr_t)(theTest + 6);
    if ( orChild )
    {
      while ( 1 )
      {
        result = Rules_EvaluatePatternNetworkTest(patternPtr, orChild, orChild, a4);
        if ( result == 1 )
          break;
        if ( g_ClipsEvaluationError )
          return 0;
        orChild = *(_DWORD *)(uintptr_t)(orChild + 10);
        if ( !orChild )
          return 0;
      }
      if ( !g_ClipsEvaluationError )
        return result;
    }
    return 0;
  }
  if ( operatorValue != g_Clips_SymbolAnd )
  {
    if ( Parser_ParseForm((__int16 *)(uintptr_t)theTest, parsed, theTest, a4) )
    {
      Rules_ReportPatternNetworkError(patternPtr);
      return 0;
    }
    if ( parsed[2] == g_ClipsFalseSymbol && parsed[1] == 2 )
      return g_ClipsFalseSymbol ^ parsed[2];
    return 1;
  }
  andChild = *(_DWORD *)(uintptr_t)(theTest + 6);
  if ( !andChild )
    return 1;
  while ( 1 )
  {
    result = Rules_EvaluatePatternNetworkTest(patternPtr, andChild, andChild, a4);
    if ( !result )
      break;
    if ( g_ClipsEvaluationError )
      return 0;
    andChild = *(_DWORD *)(uintptr_t)(andChild + 10);
    if ( !andChild )
      return 1;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 54DD70: using guessed type int dword_54DD70;
// 54E65C: using guessed type int dword_54E65C;
// 54E664: using guessed type int dword_54E664;

//----- (0048E020) --------------------------------------------------------
signed int  Rules_ReportPatternNetworkError(signed int patternPtr)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int theDeftemplate; // edx
  _DWORD *slotPtr; // edx
  int i; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // [esp-4h] [ebp-4Ch]
  _BYTE messageBuffer[72]; // [esp+0h] [ebp-48h] BYREF

  Rules_PrintErrorID((int)(intptr_t)aFactmch, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThisErrorOcc_0, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCurrentlyActiv, v4);
  Rules_PrintFact((int)(intptr_t)g_IO_LogicalNameTable_WError[0], g_CurrentPatternFact);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504794, v5);
  theDeftemplate = *(_DWORD *)(uintptr_t)(g_CurrentPatternFact + 16);
  if ( (*(_BYTE *)(uintptr_t)(theDeftemplate + 24) & 1) != 0 )
  {
    sprintf_(messageBuffer, "   Problem resides in field #%d\n", (unsigned __int8)*(_DWORD *)(uintptr_t)(patternPtr + 20));
  }
  else
  {
    v14 = v6;
    slotPtr = *(_DWORD **)(uintptr_t)(theDeftemplate + 20);
    for ( i = 0; i < *(_DWORD *)(uintptr_t)(patternPtr + 20) << 16 >> 24; ++i )
      slotPtr = (_DWORD *)(uintptr_t)slotPtr[4];
    sprintf_(messageBuffer, "   Problem resides in slot %s\n", *(const char **)(uintptr_t)(*slotPtr + 16));
    v10 = v14;
  }
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)messageBuffer, v10);
  Rules_ReportPatternNetworkRules(patternPtr, 0, v11);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504794, v12);
}
// 48E043: variable 'v3' is possibly undefined
// 48E052: variable 'v4' is possibly undefined
// 48E071: variable 'v5' is possibly undefined
// 48E085: variable 'v6' is possibly undefined
// 48E0C0: variable 'v10' is possibly undefined
// 48E0C9: variable 'v11' is possibly undefined
// 48E0D8: variable 'v12' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];
// 54E528: using guessed type int dword_54E528;

//----- (0048E100) --------------------------------------------------------
signed int  Rules_ReportPatternNetworkRules(signed int result, int processSiblings, int j)
{
  signed int i; // ebx
  int patternCount; // eax
  int v6; // ecx
  int v7; // ecx
  _BYTE messageBuffer[68]; // [esp+0h] [ebp-4Ch] BYREF
  int v9 CLASH95_UNUSED; // [esp+44h] [ebp-8h]

  v9 = j;
  for ( i = result; i; i = *(_DWORD *)(uintptr_t)(i + 40) )
  {
    if ( (*(_BYTE *)(uintptr_t)(i + 12) & 4) != 0 )
    {
      for ( j = *(_DWORD *)(uintptr_t)(i + 8); j; j = *(_DWORD *)(uintptr_t)(v7 + 32) )
      {
        patternCount = Rules_CountJoinNetworkEntryNodes(j);
        sprintf_(messageBuffer, "      Of pattern #%d in rule(s):\n", patternCount);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)messageBuffer, v6);
        result = Rules_PrintJoinNetworkSharingReport();
      }
    }
    else
    {
      result = Rules_ReportPatternNetworkRules(*(_DWORD *)(uintptr_t)(i + 28), 1, j);
    }
    if ( !processSiblings )
      break;
  }
  return result;
}
// 48E142: variable 'v6' is possibly undefined
// 48E150: variable 'v7' is possibly undefined
// 48E172: variable 'j' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048E180) --------------------------------------------------------
BOOL  Rules_ShouldProcessPatternNode(int thePattern)
{
  return g_IncrementalResetInProgress && (*(_BYTE *)(uintptr_t)(thePattern + 12) & 8) == 0;
}
// 51B354: using guessed type int dword_51B354;

//----- (0048E1A0) --------------------------------------------------------
void  Rules_PropagatePatternNodeResetFlag(int thePattern, char value)
{
  int flagBits; // edx

  if ( (*(_BYTE *)(uintptr_t)(thePattern + 12) & 8) != 0 )
  {
    flagBits = 8 * (value & 1);
    while ( thePattern )
    {
      *(_BYTE *)(uintptr_t)(thePattern + 12) &= ~8u;
      *(_DWORD *)(uintptr_t)(thePattern + 12) |= flagBits;
      thePattern = *(_DWORD *)(uintptr_t)(thePattern + 32);
    }
  }
  return;
}

//----- (0048E1D0) --------------------------------------------------------
int  Rules_RematchAllFactsAgainstPatternNetwork(double a1)
{
  int result; // eax
  int i; // esi

  result = Rules_GetNextFact(0);
  for ( i = result; result; i = result )
  {
    Rules_MatchFactAgainstPatternNetwork(i, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(i + 16) + 32), 0, 0, a1, 0);
    result = Rules_GetNextFact(i);
  }
  return result;
}

//----- (0048E220) --------------------------------------------------------
int * Rules_DriveJoinNetwork(int *result, char *join, int operation, double a4)
{
  int resetInProgress; // ecx
  int *lhsBinds; // ebp
  int *oppositeBinds; // esi
  char joinFlags; // dl
  char v9; // bh
  int *compareBinds; // ecx
  int i; // edx
  int *binds; // [esp+0h] [ebp-20h]
  signed int exprResult; // [esp+4h] [ebp-1Ch]
  int *rhsBinds; // [esp+8h] [ebp-18h]

  binds = result;
  resetInProgress = g_IncrementalResetInProgress;
  lhsBinds = 0;
  oppositeBinds = 0;
  rhsBinds = 0;
  if ( g_IncrementalResetInProgress && (*join & 0x10) == 0 )
    return result;
  if ( !operation )
  {
    joinFlags = *join;
    if ( (*join & 8) != 0 || (joinFlags & 4) != 0 )
    {
      result = (int *)(uintptr_t)Rules_MultifieldAppendValue(result, 0, *(_DWORD *)join << 30 >> 31, *((_DWORD *)join + 9) != 0);
      *(_BYTE *)result |= 0x30u;
      result[1] = *((_DWORD *)join + 2);
      binds = result;
      *((_DWORD *)join + 2) = result;
    }
  }
  v9 = *join;
  if ( (*join & 1) != 0 )
    return Rules_AddJoinLeftMemoryEntry((int)(intptr_t)join, binds, resetInProgress, a4);
  if ( operation )
  {
    if ( operation == 1 )
    {
      if ( (v9 & 8) != 0 || (v9 & 4) != 0 )
        oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
      else
        oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(join + 24) + 8);
      result = binds;
      rhsBinds = binds;
    }
    else
    {
      Rules_ReportSystemError(operation, 1);
      result = (int *)(uintptr_t)IO_RunRouterExitCallbacks();
    }
  }
  else
  {
    if ( (v9 & 4) != 0 )
      oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(join + 16) + 8);
    else
      oppositeBinds = (int *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(join + 16);
    lhsBinds = binds;
  }
  while ( oppositeBinds )
  {
    if ( operation == 1 )
    {
      lhsBinds = oppositeBinds;
      if ( (*(_BYTE *)oppositeBinds & 0x20) == 0 || (*join & 8) != 0 || (*join & 4) != 0 )
      {
        if ( ((*join & 8) != 0 || (*join & 4) != 0) && (*(_BYTE *)oppositeBinds & 0x20) != 0 )
          goto LABEL_31;
        goto LABEL_33;
      }
      oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
    }
    else
    {
      rhsBinds = oppositeBinds;
LABEL_33:
      if ( *((_DWORD *)join + 3) )
      {
        result = (int *)(uintptr_t)Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(join + 12), lhsBinds, (_BYTE *)join, (int)(intptr_t)rhsBinds, a4);
        exprResult = (signed int)(intptr_t)result;
        if ( g_ClipsEvaluationError )
        {
          if ( (*join & 8) != 0 )
            exprResult = 1;
          result = (int *)(uintptr_t)Lexer_ErrorRecover(0);
        }
      }
      else
      {
        exprResult = 1;
        if ( (*join & 4) != 0 )
        {
          compareBinds = rhsBinds;
          result = lhsBinds;
          for ( i = 0; i < (int)(((unsigned int)(*lhsBinds << 17) >> 23) - 1); ++i )
          {
            if ( result[2] != compareBinds[2] )
              goto LABEL_31;
            ++compareBinds;
            ++result;
          }
        }
      }
      if ( exprResult )
      {
        if ( (*join & 8) != 0 || (*join & 4) != 0 )
        {
          if ( operation == 1 )
          {
            result = (int *)(uintptr_t)Rules_ProcessJoinMemoryMatches((int)(intptr_t)join, oppositeBinds, (int)(intptr_t)rhsBinds, a4);
            oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
          }
          else
          {
            if ( operation )
              goto LABEL_31;
            result = &binds[(unsigned int)(*binds << 17) >> 23];
            oppositeBinds = 0;
            result[1] = (int)(intptr_t)rhsBinds;
          }
        }
        else
        {
          result = Rules_CreateJoinPartialMatch(lhsBinds, rhsBinds, join, a4);
          oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
        }
      }
      else
      {
LABEL_31:
        oppositeBinds = (int *)(uintptr_t)(unsigned int)oppositeBinds[1];
      }
    }
  }
  BYTE1(result) = *join;
  if ( ((*join & 8) != 0 || (BYTE1(result) & 4) != 0) && !operation )
  {
    result = &binds[(unsigned int)(*binds << 17) >> 23];
    if ( !result[1] )
      return Rules_AddJoinRightMemoryEntry((int)(intptr_t)join, binds, a4);
  }
  return result;
}
// 48E2F0: variable 'v5' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51B354: using guessed type int dword_51B354;

//----- (0048E4A0) --------------------------------------------------------
signed int  Rules_EvaluateJoinExpression(
        __int16 *joinExpr,
        _WORD *lbinds,
        _BYTE *theJoin,
        int rbinds,
        double a5)
{
  __int16 *exprPtr; // esi
  int testResult; // edi
  int savedPatternEntity; // eax
  char joinFlags; // dl
  int exprFunction; // eax
  int entityRecord; // edi
  int exprSymbol; // eax
  __int16 v13; // ax
  __int16 v15; // ax
  uintptr_t evaluator; // eax
  int oldExpression; // ecx
  __int16 v18; // ax
  __int16 v19; // ax
  __int16 v20; // ax
  __int16 v21; // ax
  int v22 CLASH95_UNUSED; // edx
  int v23 CLASH95_UNUSED; // ecx
  __int16 v24; // ax
  __int16 v25; // ax
  __int16 v26; // ax
  _DWORD theResult[6]; // [esp+0h] [ebp-3Ch] BYREF
  int oldJoin; // [esp+18h] [ebp-24h]
  int oldRHSBinds; // [esp+1Ch] [ebp-20h]
  int oldLHSBinds; // [esp+20h] [ebp-1Ch]
  int rhsBindsCopy; // [esp+24h] [ebp-18h]
  int andLogic; // [esp+28h] [ebp-14h]
  _BYTE *joinNode; // [esp+2Ch] [ebp-10h]

  exprPtr = joinExpr;
  rhsBindsCopy = rbinds;
  joinNode = theJoin;
  testResult = 1;
  if ( !joinExpr )
    return 1;
  oldLHSBinds = g_Clips_CurrentPartialMatch;
  g_Clips_CurrentPartialMatch = (int)(intptr_t)lbinds;
  oldRHSBinds = g_Rules_GlobalRHSBinds;
  g_Rules_GlobalRHSBinds = rbinds;
  savedPatternEntity = g_CurrentPatternEntityPtr;
  g_CurrentPatternEntityPtr = (int)(intptr_t)theJoin;
  joinFlags = *theJoin;
  oldJoin = savedPatternEntity;
  if ( (joinFlags & 8) != 0 )
  {
    v15 = ((unsigned __int16)(2 * *lbinds) >> 7) - 1;
    *lbinds &= 0x803Fu;
    *(_DWORD *)lbinds |= (v15 & 0x1FF) << 6;
  }
  exprFunction = *(_DWORD *)(exprPtr + 1);
  if ( exprFunction == g_Clips_SymbolAnd )
  {
    exprPtr = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)exprPtr + 6);
    andLogic = 1;
  }
  else if ( exprFunction == g_ClipsSymbolOr )
  {
    exprPtr = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)exprPtr + 6);
    andLogic = 0;
  }
  else
  {
    andLogic = 1;
  }
  while ( exprPtr )
  {
    entityRecord = g_Clips_PrimitiveEntityTable[*exprPtr];
    evaluator = entityRecord ? (uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(entityRecord + 16) : 0;
    if ( evaluator )
    {
      oldExpression = g_ClipsCurrentExpression;
      g_ClipsCurrentExpression = (int)(uintptr_t)exprPtr;
      testResult = ((int (*)(int, _DWORD *, double))evaluator)(*(_DWORD *)((char *)exprPtr + 2), theResult, a5);
      g_ClipsCurrentExpression = oldExpression;
    }
    else
    {
      exprSymbol = *(_DWORD *)(exprPtr + 1);
      if ( exprSymbol == g_ClipsSymbolOr )
      {
        testResult = 0;
        if ( Rules_EvaluateJoinExpression(exprPtr, lbinds, joinNode, rhsBindsCopy, a5) == 1 )
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*joinNode & 8) != 0 )
            {
              v19 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
              *lbinds &= 0x803Fu;
              *(_DWORD *)lbinds |= (v19 & 0x1FF) << 6;
            }
            goto LABEL_14;
          }
          testResult = 1;
        }
        else if ( g_ClipsEvaluationError )
        {
          if ( (*joinNode & 8) != 0 )
          {
            v20 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
            *lbinds &= 0x803Fu;
            *(_DWORD *)lbinds |= (v20 & 0x1FF) << 6;
          }
          goto LABEL_14;
        }
      }
      else if ( exprSymbol == g_Clips_SymbolAnd )
      {
        testResult = 1;
        if ( Rules_EvaluateJoinExpression(exprPtr, lbinds, joinNode, rhsBindsCopy, a5) )
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*joinNode & 8) != 0 )
            {
              v21 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
              *lbinds &= 0x803Fu;
              *(_DWORD *)lbinds |= (v21 & 0x1FF) << 6;
            }
            goto LABEL_14;
          }
        }
        else
        {
          if ( g_ClipsEvaluationError )
          {
            if ( (*joinNode & 8) != 0 )
            {
              v13 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
              *lbinds &= 0x803Fu;
              *(_DWORD *)lbinds |= (v13 & 0x1FF) << 6;
            }
LABEL_14:
            g_Clips_CurrentPartialMatch = oldLHSBinds;
            g_Rules_GlobalRHSBinds = oldRHSBinds;
            g_CurrentPatternEntityPtr = oldJoin;
            return 0;
          }
          testResult = 0;
        }
      }
      else
      {
        Parser_ParseForm(exprPtr, theResult, g_ClipsSymbolOr, a5);
        testResult = g_ClipsEvaluationError;
        if ( g_ClipsEvaluationError )
        {
          Rules_ReportJoinNetworkError((int)(uintptr_t)joinNode, 0);
          if ( (*joinNode & 8) != 0 )
          {
            v24 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
            *lbinds &= 0x803Fu;
            *(_DWORD *)lbinds |= (v24 & 0x1FF) << 6;
          }
          goto LABEL_14;
        }
        if ( theResult[2] != g_ClipsFalseSymbol || theResult[1] != 2 )
          testResult = 1;
      }
    }
    if ( andLogic == 1 && !testResult )
    {
      if ( (*joinNode & 8) != 0 )
      {
        v18 = andLogic + ((unsigned __int16)(2 * *lbinds) >> 7);
        *lbinds &= 0x803Fu;
        *(_DWORD *)lbinds |= (v18 & 0x1FF) << 6;
      }
      goto LABEL_14;
    }
    if ( !andLogic && testResult == 1 )
    {
      if ( (*joinNode & 8) != 0 )
      {
        v25 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
        *lbinds &= 0x803Fu;
        *(_DWORD *)lbinds |= (v25 & 0x1FF) << 6;
      }
      g_Clips_CurrentPartialMatch = oldLHSBinds;
      g_Rules_GlobalRHSBinds = oldRHSBinds;
      g_CurrentPatternEntityPtr = oldJoin;
      return 1;
    }
    exprPtr = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)exprPtr + 10);
  }
  g_Clips_CurrentPartialMatch = oldLHSBinds;
  g_Rules_GlobalRHSBinds = oldRHSBinds;
  g_CurrentPatternEntityPtr = oldJoin;
  if ( (*joinNode & 8) != 0 )
  {
    v26 = ((unsigned __int16)(2 * *lbinds) >> 7) + 1;
    *lbinds &= 0x803Fu;
    *(_DWORD *)lbinds |= (v26 & 0x1FF) << 6;
  }
  return testResult;
}
// 48E659: variable 'v17' is possibly undefined
// 48E7BE: variable 'v23' is possibly undefined
// 48E7BE: variable 'v22' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A964: using guessed type int dword_51A964;
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;
// 51AD04: using guessed type int dword_51AD04;
// 54DD70: using guessed type int dword_54DD70;
// 54E530: using guessed type int dword_54E530[70];
// 54E65C: using guessed type int dword_54E65C;
// 54E664: using guessed type int dword_54E664;

//----- (0048E8E0) --------------------------------------------------------
_DWORD * Rules_CreateJoinPartialMatch(_DWORD *lhsBinds, _DWORD *rhsBinds, _DWORD *theJoin, double unused_fp)
{
  _DWORD *result; // eax
  int partial_match; // esi
  int action; // ebp
  uintptr_t join; // ecx

  result = Rules_MergeMultifieldValues(lhsBinds, rhsBinds, *theJoin << 30 >> 31, theJoin[9] != 0);
  result[1] = theJoin[2];
  partial_match = (int)(uintptr_t)result;
  action = theJoin[9];
  theJoin[2] = result;
  if ( action )
    result = Rules_AddActivation(action, (int)(uintptr_t)result, unused_fp);
  join = (uintptr_t)(unsigned int)theJoin[5];
  if ( join )
  {
    if ( (uintptr_t)(unsigned int)*(_DWORD *)(join + 16) == (uintptr_t)(unsigned int)(uintptr_t)theJoin )
    {
      return (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)partial_match, (char *)join, 1, unused_fp);
    }
    else
    {
      do
      {
        result = (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)partial_match, (char *)join, 0, unused_fp);
        join = (uintptr_t)(unsigned int)*(_DWORD *)(join + 28);
      }
      while ( join );
    }
  }
  return result;
}
// 48E923: conditional instruction was optimized away because ecx.4!=0

//----- (0048E960) --------------------------------------------------------
int  Rules_ProcessJoinMemoryMatches(int result, _BYTE *theBind, int newAlphaMatch, double a4)
{
  _DWORD *theJoin; // ebp
  _BYTE *v6; // edx
  int childJoin; // esi

  theJoin = (_DWORD *)(uintptr_t)result;
  BYTE1(result) = *theBind;
  if ( (*theBind & 0x20) == 0 )
  {
    *theBind = BYTE1(result) | 0x20;
    if ( (result & 0x400) != 0 )
    {
      v6 = &theBind[4 * (*(_DWORD *)theBind << 17 >> 23)];
      if ( *((_DWORD *)v6 + 2) )
        Rules_RemoveActivation(*((_DWORD **)v6 + 2), 1, 1);
    }
    childJoin = theJoin[5];
    if ( childJoin )
    {
      if ( theJoin == *(_DWORD **)(uintptr_t)(childJoin + 16) )
      {
        Rules_UpdateBetaMemoryOnRetract((_DWORD *)(uintptr_t)theJoin[5], (int)(intptr_t)theBind, 0, a4);
      }
      else
      {
        while ( childJoin )
        {
          Rules_PropagateRetractToJoinNode(childJoin, *(_DWORD *)&theBind[4 * (*(_DWORD *)theBind << 17 >> 23) + 4], (*theJoin << 16 >> 25) - 1, (int)(intptr_t)theBind, a4, 0);
          childJoin = *(_DWORD *)(uintptr_t)(childJoin + 28);
        }
      }
    }
    if ( (*theBind & 8) != 0 )
      Rules_RemovePMDependencies((int)(intptr_t)theBind);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)&theBind[4 * (*(_DWORD *)theBind << 17 >> 23) + 4] + 8) = g_ReteGarbageAlphaMatchList;
    g_ReteGarbageAlphaMatchList = *(_DWORD *)&theBind[4 * (*(_DWORD *)theBind << 17 >> 23) + 4];
    result = *(_DWORD *)theBind << 17 >> 23;
    *(_DWORD *)&theBind[4 * result + 4] = newAlphaMatch;
  }
  return result;
}
// 51A978: using guessed type int dword_51A978;

//----- (0048EA40) --------------------------------------------------------
_DWORD * Rules_AddJoinRightMemoryEntry(int theJoin, _BYTE *binds, double a3)
{
  _DWORD *result; // eax
  uintptr_t runtime_state; // eax
  unsigned int free_node; // edx
  uintptr_t join; // ecx

  runtime_state = (uintptr_t)(unsigned int)g_ClipsMemoryTable;
  free_node = *(_DWORD *)(runtime_state + 48);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = free_node;
    result = (_DWORD *)(uintptr_t)free_node;
    *(_DWORD *)(runtime_state + 48) = *result;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  result[2] = 0;
  *result = 0;
  result[1] = 0;
  *binds &= ~0x20u;
  *(_DWORD *)&binds[4 * (*(_DWORD *)binds << 17 >> 23) + 4] = (int)(uintptr_t)result;
  if ( *(_DWORD *)(uintptr_t)(theJoin + 36) )
    result = Rules_AddActivation(*(_DWORD *)(uintptr_t)(theJoin + 36), (int)(uintptr_t)binds, a3);
  join = (uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theJoin + 20);
  if ( join )
  {
    if ( (uintptr_t)(unsigned int)theJoin == (uintptr_t)(unsigned int)*(_DWORD *)(join + 16) )
    {
      return (_DWORD *)Rules_DriveJoinNetwork((int *)binds, (char *)join, 1, a3);
    }
    else
    {
      do
      {
        result = (_DWORD *)Rules_DriveJoinNetwork((int *)binds, (char *)join, 0, a3);
        join = (uintptr_t)(unsigned int)*(_DWORD *)(join + 28);
      }
      while ( join );
    }
  }
  return result;
}
// 48EAA4: conditional instruction was optimized away because ecx.4!=0
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048EAE0) --------------------------------------------------------
_DWORD * Rules_AddJoinLeftMemoryEntry(int theJoin, int *rhsBinds, int a3, double a4)
{
  _DWORD *result; // eax
  signed int linker; // esi
  int ruleToActivate; // edx
  int join; // ecx

  if ( !*(_DWORD *)(uintptr_t)(theJoin + 12)
    || (result = (_DWORD *)(uintptr_t)Rules_EvaluateJoinExpression((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(theJoin + 12), 0, (_BYTE *)(uintptr_t)(unsigned int)theJoin, (int)(intptr_t)rhsBinds, a4),
        a3 = 0,
        g_ClipsEvaluationError = 0,
        result) )
  {
    if ( (*(_BYTE *)(uintptr_t)theJoin & 8) != 0 )
    {
      Rules_ReportSystemError(a3, 2);
      IO_RunRouterExitCallbacks();
    }
    result = Rules_MultifieldCopyWithMarkers(rhsBinds, *(_DWORD *)(uintptr_t)(theJoin + 36) != 0, *(_DWORD *)(uintptr_t)theJoin << 30 >> 31);
    result[1] = *(_DWORD *)(uintptr_t)(theJoin + 8);
    linker = (signed int)(intptr_t)result;
    ruleToActivate = *(_DWORD *)(uintptr_t)(theJoin + 36);
    *(_DWORD *)(uintptr_t)(theJoin + 8) = result;
    if ( ruleToActivate )
      result = Rules_AddActivation(ruleToActivate, (int)(intptr_t)result, a4);
    join = *(_DWORD *)(uintptr_t)(theJoin + 20);
    while ( join )
    {
      result = (_DWORD *)Rules_DriveJoinNetwork((int *)(uintptr_t)(unsigned int)linker, (char *)(uintptr_t)(unsigned int)join, 0, a4);
      join = *(_DWORD *)(uintptr_t)(join + 28);
    }
  }
  return result;
}
// 51A964: using guessed type int dword_51A964;

//----- (0048EBA0) --------------------------------------------------------
signed int __fastcall Rules_ReportJoinNetworkError(int joinPtr, int a2)
{
  uintptr_t join; // ecx
  char messageBuffer[64]; // [esp+0h] [ebp-48h] BYREF

  (void)a2;
  join = (uintptr_t)(unsigned int)joinPtr;
  Rules_PrintErrorID((int)(intptr_t)aDrive, 1, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThisErrorOcc_1, 0);
  sprintf_(messageBuffer, "   Problem resides in join #%d in rule(s):\n", join ? (*(_DWORD *)join << 16) >> 25 : 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(uintptr_t)messageBuffer, 0);
  Rules_ClearJoinNetworkMarkedFlags();
  Rules_PrintJoinNetworkNodeRuleOwners((int)join, (int)(uintptr_t)"      ");
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504874, 0);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A614: using guessed type char *off_51A614[5];

//----- (0048EC20) --------------------------------------------------------
int  Rules_AddLogicalDependencyLink(int theEntity, int existingEntity)
{
  int result; // eax
  int v3; // ecx
  _DWORD *theBind; // edx
  _DWORD *freeNode; // esi
  _DWORD *newDependency; // eax
  _DWORD *v7; // edi
  _DWORD *newDependent; // eax

  if ( !g_Rules_CurrentLogicalJoin )
  {
    if ( existingEntity )
      Rules_ReleaseLogicalSupportList(theEntity);
    return 1;
  }
  if ( existingEntity && !*(_DWORD *)(uintptr_t)(theEntity + 4) )
    return 1;
  result = (int)(intptr_t)Rules_FindLogicalDependencyEntry(g_Rules_CurrentLogicalJoin, g_Clips_CurrentPartialMatch);
  theBind = (_DWORD *)(uintptr_t)result;
  if ( result )
  {
    freeNode = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 32);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeNode;
      newDependency = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDependency = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    *newDependency = v3;
    newDependency[1] = theBind[(*theBind << 17 >> 23) + 2 + (*theBind << 29 >> 31)];
    theBind[(*theBind << 29 >> 31) + 2 + (*theBind << 17 >> 23)] = newDependency;
    v7 = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 32);
    if ( v7 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *v7;
      newDependent = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDependent = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    *newDependent = theBind;
    newDependent[1] = *(_DWORD *)(uintptr_t)(v3 + 4);
    *(_DWORD *)(uintptr_t)(v3 + 4) = newDependent;
    return 1;
  }
  return result;
}
// 48EC79: variable 'v3' is possibly undefined
// 51A1F8: using guessed type int dword_51A1F8;
// 51ACFC: using guessed type int dword_51ACFC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0048ED00) --------------------------------------------------------
_DWORD * Rules_FindLogicalDependencyEntry(int theJoin, int theBinds)
{
  _DWORD *compPtr; // esi
  int bindsPtr; // ecx
  _DWORD *compFieldPtr; // eax
  unsigned int i; // edx

  compPtr = *(_DWORD **)(uintptr_t)(theJoin + 8);
  if ( compPtr )
  {
    while ( 2 )
    {
      bindsPtr = theBinds;
      compFieldPtr = compPtr;
      for ( i = 0; ; ++i )
      {
        if ( i >= *compPtr << 17 >> 23 )
          return compPtr;
        if ( compFieldPtr[2] != *(_DWORD *)(uintptr_t)(bindsPtr + 8) )
          break;
        bindsPtr += 4;
        ++compFieldPtr;
      }
      compPtr = (_DWORD *)(uintptr_t)compPtr[1];
      if ( compPtr )
        continue;
      break;
    }
  }
  return 0;
}
