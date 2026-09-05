/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

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
    if ( MessageHandler_AnyHandlerBusy((int)(intptr_t)theClass) )
    {
      Rules_GetConstructNameString((int)(intptr_t)theClass);
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
            Rules_PrintErrorID((int)(intptr_t)aMsgpsr_0, 3, 0);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSystemMessag_0, v13);
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
            flagsPtr = (_BYTE *)(uintptr_t)(i + theClass[22]);
            if ( (*flagsPtr & 1) == 0 )
              *flagsPtr |= 8u;
            ++scanIndex;
            i += 36;
          }
          while ( scanIndex < theClass[24] );
        }
      }
LABEL_19:
      Class_PurgeMarkedMessageHandlers((signed int)(intptr_t)theClass, i);
      return success;
    }
    handler = Class_FindMessageHandler(theClass, handlerName, handlerType);
    if ( handler )
    {
      if ( (*(_BYTE *)handler & 1) == 0 )
      {
        *(_BYTE *)handler |= 8u;
        Class_PurgeMarkedMessageHandlers((signed int)(intptr_t)theClass, v15);
        return 1;
      }
      if ( v15 )
      {
        Rules_PrintErrorID((int)(intptr_t)aMsgpsr_0, 3, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSystemMessag_0, v18);
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
            recordFlags = (_BYTE *)(uintptr_t)(recordOffset + theClass[22]);
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
        Rules_GetConstructNameString((int)(intptr_t)theClass);
        MessageHandler_ReportUnableToDelete();
      }
    }
    Class_PurgeMarkedMessageHandlers((signed int)(intptr_t)theClass, v15);
    return 0;
  }
  if ( !indicateMissing )
    return 1;
  Rules_GetConstructNameString((int)(intptr_t)theClass);
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
  if ( *(_DWORD *)(uintptr_t)(result + 96) )
  {
    recordOffset = 0;
    do
    {
      handlerRecord = recordOffset + *(_DWORD *)(uintptr_t)(theClass + 88);
      if ( (*(_BYTE *)(uintptr_t)handlerRecord & 8) != 0 )
      {
        Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(handlerRecord + 8), a2);
        AST_DeinstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v14 + 28));
        AST_FreePackedNodeChain(*(_DWORD *)(uintptr_t)(v15 + 28));
        ppForm = (const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(v16 + 32);
        ++deletedCount;
        if ( ppForm )
          Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v16 + 32), strlen(ppForm) + 1);
      }
      else
      {
        *(_DWORD *)(uintptr_t)(handlerRecord + 4) = deletedCount;
      }
      result = theClass;
      ++handlerIndex;
      a2 = *(_DWORD *)(uintptr_t)(theClass + 96);
      recordOffset += 36;
    }
    while ( handlerIndex < a2 );
  }
  if ( deletedCount )
  {
    totalCount = *(_DWORD *)(uintptr_t)(theClass + 96);
    if ( deletedCount == totalCount )
    {
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theClass + 88), 36 * totalCount);
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theClass + 92), 4 * *(_DWORD *)(uintptr_t)(theClass + 96));
      result = theClass;
      *(_DWORD *)(uintptr_t)(theClass + 88) = 0;
      *(_DWORD *)(uintptr_t)(theClass + 92) = 0;
      *(_DWORD *)(uintptr_t)(theClass + 96) = 0;
    }
    else
    {
      remainingCount = totalCount - deletedCount;
      oldHandlerArray = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theClass + 88);
      oldIndexArray = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theClass + 92);
      newHandlerArray = (char *)Mem_SmallBlockAlloc(36 * remainingCount);
      newIndexCursor = Mem_SmallBlockAlloc(4 * remainingCount);
      newIndexArray = (signed int)(intptr_t)newIndexCursor;
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
      Mem_SmallBlockFree(oldHandlerArray, 36 * *(_DWORD *)(uintptr_t)(theClass + 96));
      Mem_SmallBlockFree(oldIndexArray, 4 * *(_DWORD *)(uintptr_t)(theClass + 96));
      *(_DWORD *)(uintptr_t)(theClass + 88) = newHandlerArray;
      *(_DWORD *)(uintptr_t)(theClass + 96) = remainingCount;
      result = newIndexArray;
      *(_DWORD *)(uintptr_t)(theClass + 92) = newIndexArray;
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
      Rules_PrintErrorID((int)(intptr_t)aMsgfun, 7, 0);
      Output_Write((int)(intptr_t)aWerror, (int)(intptr_t)aUnrecognizedMe, v5);
      Output_Write((int)(intptr_t)aWerror, typeName, v6);
      Output_Write((int)(intptr_t)aWerror, (int)(intptr_t)a__20, v7);
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
signed int __fastcall MessageHandler_CheckCurrentMessage(int functionName CLASH95_UNUSED, int instanceRequired)
{
  int firstArgument; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( g_CurrentMessageHandler )
  {
    firstArgument = MessageHandler_GetNthArgument(0);
    if ( instanceRequired == 1 && *(_DWORD *)(uintptr_t)(firstArgument + 4) != 7 )
    {
      Rules_PrintErrorID((int)(intptr_t)aMsgfun, 5, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v7, v7);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOperatesOnlyOn, v8);
      Lexer_ErrorRecover(1);
      return 0;
    }
    else if ( *(_DWORD *)(uintptr_t)(firstArgument + 4) == 7 && (*(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(firstArgument + 8) + 24) & 2) != 0 )
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
    Rules_PrintErrorID((int)(intptr_t)aMsgfun, 4, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v5, v5);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMayOnlyBeCalle, v6);
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

  Output_Write(logicalName, *(_DWORD *)(uintptr_t)(theHandler[2] + 16), logicalName);
  Output_Write(v4, (int)(intptr_t)asc_5092EC, v4);
  Output_Write(v5, (int)(intptr_t)g_MessageHandlerTypeNames[*theHandler << 29 >> 30], v5);
  Output_Write(v6, (int)(intptr_t)aInClass_0, v6);
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
      indexCursor = (_DWORD *)(uintptr_t)(theClass[23] + 4 * groupStart);
      do
      {
        result = (_DWORD *)(uintptr_t)(theClass[22] + 36 * *indexCursor);
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
        handlerRecord = (_DWORD *)(uintptr_t)(theClass[22] + 36 * *(_DWORD *)(uintptr_t)indexEntry);
        if ( handlerName != handlerRecord[2] )
          break;
        if ( *handlerRecord << 29 >> 30 == handlerType )
          return *(_DWORD *)(uintptr_t)indexEntry;
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
    midNameBucket = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(36 * *(_DWORD *)(uintptr_t)(indexArray + 4 * mid) + handlerArray + 8) + 12) << 16 >> 18;
    targetBucket = *(_DWORD *)(uintptr_t)(handlerName + 12) << 16 >> 18;
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
    backCursor = (_DWORD *)(uintptr_t)(indexArray + 4 * mid);
    do
    {
      if ( handlerName == *(_DWORD *)(uintptr_t)(handlerArray + 36 * *backCursor + 8) )
        foundIndex = scanIndex;
      if ( *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(handlerArray + 36 * *backCursor + 8) + 12) << 16 >> 18 != *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(36 * *(_DWORD *)(uintptr_t)(indexArray + 4 * mid)
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
  for ( i = (_DWORD *)(uintptr_t)(indexArray + 4 * result); ; ++i )
  {
    cursorName = *(_DWORD *)(uintptr_t)(handlerArray + 36 * *i + 8);
    if ( handlerName == cursorName )
      break;
    if ( *(_DWORD *)(uintptr_t)(cursorName + 12) << 16 >> 18 != *(_DWORD *)(uintptr_t)(handlerName + 12) << 16 >> 18 )
      return -1;
    if ( ++result > searchHigh )
      return -1;
  }
  return result;
}

//----- (004AEEB0) --------------------------------------------------------
signed int MessageHandler_ReportUnableToDelete(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aMsgfun, 8, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToDele_2, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__20, v2);
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
  if ( (*(_BYTE *)(uintptr_t)*handlerLink & 6) != 0 )
  {
    while ( currentLink )
    {
      result = (*(_DWORD *)(uintptr_t)*currentLink & 6) == 2;
      if ( (*(_DWORD *)(uintptr_t)*currentLink & 6) != 2 )
        break;
      MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)(intptr_t)asc_5094A8, indentDepth);
      result = MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)(intptr_t)asc_5094AC, indentDepth);
      currentLink = (int *)(uintptr_t)currentLink[1];
    }
    if ( currentLink )
    {
      result = (*(_DWORD *)(uintptr_t)*currentLink & 6) == 4;
      if ( (*(_DWORD *)(uintptr_t)*currentLink & 6) == 4 )
      {
        result = MessageHandler_PrintAroundHandlerNesting(logicalName, currentLink, indentDepth);
        currentLink = (int *)(uintptr_t)result;
      }
    }
    while ( currentLink )
    {
      result = (*(_DWORD *)(uintptr_t)*currentLink & 6) == 6;
      if ( (*(_DWORD *)(uintptr_t)*currentLink & 6) != 6 )
        break;
      MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)(intptr_t)asc_5094A8, indentDepth);
      result = MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)(intptr_t)asc_5094AC, indentDepth);
      currentLink = (int *)(uintptr_t)currentLink[1];
    }
  }
  else
  {
    MessageHandler_PrintIndentedHandlerMarker(logicalName, handlerLink, (int)(intptr_t)asc_5094A8, indentDepth);
    nextLink = (int *)(uintptr_t)currentLink[1];
    if ( nextLink )
      MessageHandler_PrintHandlerPreview(logicalName, nextLink, indentDepth + 1);
    return MessageHandler_PrintIndentedHandlerMarker(logicalName, currentLink, (int)(intptr_t)asc_5094AC, indentDepth);
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
  while ( classIndex < *(unsigned __int16 *)(uintptr_t)(cls + 46) )
  {
    classOffset += 4;
    ++classIndex;
    MessageHandler_CollectClassHandlersIntoCore(
      (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(classOffset + *(_DWORD *)(uintptr_t)(cls + 48) - 4),
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

  Output_Write(logicalName, (int)(intptr_t)aMsg, logicalName);
  Output_Write(v3, traceString, v3);
  Output_Write(v4, (int)(intptr_t)asc_5092EC, v4);
  Output_Write(v5, *(_DWORD *)(uintptr_t)(g_CurrentMessageHandler + 16), v5);
  Output_Write(v6, (int)(intptr_t)aEd_0, v6);
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

  Output_Write(logicalName, (int)(intptr_t)aHnd, logicalName);
  Output_Write(v4, traceString, v4);
  Output_Write(v5, (int)(intptr_t)asc_5092EC, v5);
  MessageHandler_PrintNameTypeAndClass((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (_DWORD *)(uintptr_t)*handlerLink, 1);
  Output_Write(v6, (int)(intptr_t)aEd, v6);
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

  MessageHandler_PrintIndentedHandlerMarker(logicalName, handlerLink, (int)(intptr_t)asc_5094A8, indentDepth);
  innerLink = (int *)(uintptr_t)handlerLink[1];
  if ( innerLink && (*(_DWORD *)(uintptr_t)*innerLink & 6) == 4 )
    nextLink = MessageHandler_PrintAroundHandlerNesting(logicalName, innerLink, indentDepth + 1);
  else
    nextLink = handlerLink[1];
  savedNext = nextLink;
  MessageHandler_PrintIndentedHandlerMarker(logicalName, handlerLink, (int)(intptr_t)asc_5094AC, indentDepth);
  return savedNext;
}

//----- (004AF180) --------------------------------------------------------
signed int  MessageHandler_PrintIndentedHandlerMarker(int logicalName, int *handlerLink, int markerString, int indentDepth)
{
  int i; // ecx
  int v8; // ecx

  for ( i = 0; i < indentDepth; Output_Write(logicalName, (int)(intptr_t)asc_5094D4, i + 1) )
    ;
  Output_Write(logicalName, markerString, i);
  Output_Write(logicalName, (int)(intptr_t)asc_5092EC, v8);
  return MessageHandler_PrintNameTypeAndClass(logicalName, (_DWORD *)(uintptr_t)*handlerLink, 1);
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
    *(_DWORD *)node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
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
  /* var_20/var_1E/var_1A/var_16 form ONE packed 16-byte synthesized expression
     node (type at +0 as a WORD, then three DWORDs at +2/+6/+10). Declaring them
     as separate C locals let the compiler re-align them, so MessageHandler_Send
     walked garbage when it followed the +10 argument-list link. */
  _BYTE exprNode[16]; // [esp+10h] [ebp-20h] BYREF
  int v10 CLASH95_UNUSED; // [esp+28h] [ebp-8h]

  v10 = a2;
  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = Lexer_ParseValueList(2, argBuffer, 2, a3);
  if ( result )
  {
    *(_WORD *)exprNode = *(_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    *(_DWORD *)(exprNode + 2) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2);
    *(_DWORD *)(exprNode + 6) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 6);
    *(_DWORD *)(exprNode + 10) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 10);
    return MessageHandler_Send(returnValue, (_DWORD *)exprNode, argBuffer[2], a3);
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
BOOL MessageHandler_HasNextHandler(void)
{
  if ( !g_ClipsCurrentHandlerCore )
    return 0;
  if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore & 6) != 0 )
  {
    if ( (*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore & 6) == 4 && g_ClipsMessageHandlerCursor )
      return (*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsMessageHandlerCursor & 6) == 4;
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
  int exprValue CLASH95_UNUSED; // [esp+2h] [ebp-2Ah]
  int exprNext CLASH95_UNUSED; // [esp+6h] [ebp-26h]
  int exprArgList CLASH95_UNUSED; // [esp+Ah] [ebp-22h]
  int argFramePushed; // [esp+10h] [ebp-1Ch]

  returnValue[1] = 2;
  result = (_DWORD *)(uintptr_t)g_ClipsFalseSymbol;
  returnValue[2] = g_ClipsFalseSymbol;
  g_ClipsEvaluationError = 0;
  if ( !g_ClipsHaltExecution )
  {
    if ( !MessageHandler_HasNextHandler() )
    {
      Rules_PrintErrorID((int)(intptr_t)aMsgpass, 1, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aShadowedMessag, v12);
      return (_DWORD *)(uintptr_t)Lexer_ErrorRecover(1);
    }
    Symbol = Rules_MakeSymbol(aOverrideNext_0);
    if ( Symbol == *(int ***)(uintptr_t)(v5 + 2) )
    {
      firstArgType = *(_WORD *)(uintptr_t)(g_ClipsProcParamArray + 4);
      argFramePushed = 1;
      exprType = firstArgType;
      if ( firstArgType == 4 )
        exprValue = g_ClipsProcParamArray;
      else
        exprValue = *(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8);
      exprArgList = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
      exprNext = 0;
      messageName = *(_DWORD *)(uintptr_t)(g_CurrentMessageHandler + 16);
      argCount = AST_CountListNodes((int)(intptr_t)&exprType);
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
    savedCursor = (int *)(uintptr_t)g_ClipsMessageHandlerCursor;
    if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore & 6) == 0 && (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsMessageHandlerCursor & 6) != 0 )
    {
      result = MessageHandler_CallHandlers(returnValue, a2);
    }
    else
    {
      g_ClipsCurrentHandlerCore = g_ClipsMessageHandlerCursor;
      g_ClipsMessageHandlerCursor = *(_DWORD *)(uintptr_t)(g_ClipsMessageHandlerCursor + 4);
      if ( (*(_BYTE *)(uintptr_t)*savedCursor & 0x10) != 0 )
        MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], savedCursor, (int)(intptr_t)asc_509548);
      if ( MessageHandler_CheckArgCount() )
        Rules_ExecuteRuleActions(
          *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) + 8),
          (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 28),
          returnValue,
          *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 24),
          a2,
          (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
      result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore;
      if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore & 0x10) != 0 )
        result = (_DWORD *)(uintptr_t)MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int *)(uintptr_t)g_ClipsCurrentHandlerCore, (int)(intptr_t)asc_50954C);
    }
    g_ClipsMessageHandlerCursor = (int)(intptr_t)savedCursor;
    g_ClipsCurrentHandlerCore = savedHandlerCore;
    if ( argFramePushed )
      result = (_DWORD *)(uintptr_t)ProcParam_PopFrame();
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
    node = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    if ( node )
    {
      g_ClipsMemFreeListTemp = (int)(uintptr_t)node;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *node;
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
      *(_DWORD *)(uintptr_t)(bots[1] + 4) = primaryHead;
      result = tops[1];
    }
    if ( *tops )
    {
      *(_DWORD *)(uintptr_t)(*bots + 4) = result;
      result = *tops;
    }
    *(_DWORD *)(uintptr_t)(bots[2] + 4) = tops[3];
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
  int slot_descriptor CLASH95_UNUSED; // eax

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
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (int *)(uintptr_t)MessageHandler_CheckCurrentMessage(returnValue, 1);
  if ( result )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), slotNameValue, v4, a3);
    if ( slotNameValue[1] == 2 )
    {
      result = (int *)(uintptr_t)Instance_GetSlotValueBySymbol(*(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8), slotNameValue[2]);
      if ( result )
      {
        if ( (*(_BYTE *)(uintptr_t)(*result + 1) & 4) != 0 || *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) == *(_DWORD *)(uintptr_t)(*result + 4) )
        {
          v5[1] = (unsigned int)(result[1] << 24) >> 26;
          v5[2] = result[2];
          if ( (result[1] & 0xFC) == 0x10 )
          {
            v5[3] = 0;
            result = (int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result[2] + 6) - 1);
            v5[4] = result;
          }
        }
        else
        {
          MessageHandler_ReportPrivateSlotAccessDenied(*result);
          return (int *)(uintptr_t)Lexer_ErrorRecover(1);
        }
      }
      else
      {
        return (int *)(uintptr_t)Instance_ReportNoSuchSlotError((int)(intptr_t)v5, (int)(intptr_t)aDynamicGet_0);
      }
    }
    else
    {
      Parser_ReportError(1, (int)(intptr_t)aSymbol_5);
      return (int *)(uintptr_t)Lexer_ErrorRecover(1);
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
  _DWORD tempValue[6]; // [esp+0h] [ebp-30h] BYREF
  /* stack alias of tempValue[1] */
  /* stack alias of tempValue[2]: the DATA_OBJECT value slot */
  /* stack alias of tempValue[3] */
  /* stack alias of tempValue[4] */

  returnValue[1] = 2;
  returnValue[2] = g_ClipsFalseSymbol;
  result = MessageHandler_CheckCurrentMessage(a2, 1);
  if ( result )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), tempValue, v5, a3);
    if ( tempValue[1] == 2 )
    {
      instancePtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8);
      slotLookup = (int *)(uintptr_t)Instance_GetSlotValueBySymbol((int)(intptr_t)instancePtr, tempValue[2]);
      slotPtr = slotLookup;
      if ( slotLookup )
      {
        slotFlags = *(_BYTE *)(uintptr_t)*slotLookup;
        if ( (slotFlags & 0x10) != 0 && ((slotFlags & 0x20) == 0 || !g_Instance_SlotInitInProgress ? (writeDenied = 1) : (writeDenied = 0), writeDenied) )
        {
          MessageHandler_ReportSlotWriteAccessDenied(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*slotPtr + 8) + 12) + 16), 1);
          return Lexer_ErrorRecover(1);
        }
        else
        {
          slotDesc = *slotPtr;
          if ( (*(_BYTE *)(uintptr_t)(*slotPtr + 1) & 4) != 0 || *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) == *(_DWORD *)(uintptr_t)(slotDesc + 4) )
          {
            result = Parser_ParseSlotDefaultOrRestriction(*(_DWORD *)(uintptr_t)*slotPtr << 30 >> 31, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10), tempValue, a3);
            if ( result )
            {
              result = Instance_PutSlotValue(instancePtr, slotPtr, tempValue, a3);
              if ( result )
              {
                returnValue[1] = tempValue[1];
                returnValue[2] = tempValue[2];
                returnValue[3] = tempValue[3];
                result = tempValue[4];
                returnValue[4] = tempValue[4];
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
        return Instance_ReportNoSuchSlotError(v8, (int)(intptr_t)aDynamicPut_0);
      }
    }
    else
    {
      Parser_ReportError(1, (int)(intptr_t)aSymbol_5);
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
  int v9 CLASH95_UNUSED; // edx
  int argCount; // eax
  int v11 CLASH95_UNUSED; // ecx
  int v12 CLASH95_UNUSED; // ecx
  int firstArgType; // edx
  int handlerCore; // eax
  int savedCursor; // ebp
  int v16 CLASH95_UNUSED; // edx
  int currentModule; // eax
  int v18 CLASH95_UNUSED; // ecx
  _DWORD *namedInstance; // eax
  int v20 CLASH95_UNUSED; // ecx
  int v21 CLASH95_UNUSED; // ecx
  int v22 CLASH95_UNUSED; // ecx
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
  messageNameStr = *(_DWORD *)(uintptr_t)(messageSymbol + 16);
  argCount = AST_CountListNodes((uintptr_t)argExprs);
  ProcParam_PushEvaluatedArgumentFrame(argExprs, argCount, (int)(uintptr_t)"message", messageNameStr, a4, (int (*)(void))Rules_ReportUndefinedMessageHandlerName);
  if ( g_ClipsEvaluationError )
  {
    g_CurrentMessageHandler = savedMessageHandler;
    --g_ClipsCurrentEvaluationDepth;
    Rules_RunPeriodicCleanup(0, 1);
    return Rules_SetReentryGuardFlag(savedReentryFlag);
  }
  firstArgType = *(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 4);
  if ( firstArgType == 7 )
  {
    instancePtr = (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8);
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
      Instance_ReportNoSuchInstanceError(*(_DWORD *)(uintptr_t)(instancePtr[7] + 16), (int)(intptr_t)aSend_0);
    }
  }
  else
  {
    if ( firstArgType != 8 )
    {
      classPtr = g_ClipsPrimitiveTypeClassMap[firstArgType];
      if ( !classPtr )
      {
        Rules_ReportSystemError((int)(intptr_t)aMsgpass, 1);
        IO_RunRouterExitCallbacks(2);
      }
      goto LABEL_8;
    }
    namedInstance = Instance_FindByName(*(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8));
    instancePtr = namedInstance;
    if ( !namedInstance )
    {
      Rules_PrintErrorID((int)(intptr_t)aMsgpass, 2, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoSuchInstan_0, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8) + 16), 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunctionSend, 0);
      goto LABEL_7;
    }
    *(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 8) = (int)(uintptr_t)namedInstance;
    *(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + 4) = 7;
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
      if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)handlerCore & 6) != 0 )
      {
        g_ClipsMessageHandlerCursor = handlerCore;
        g_ClipsCurrentHandlerCore = 0;
        if ( g_MessageHandler_WatchMessages )
          MessageHandler_TraceMessageSend((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_509548);
        MessageHandler_CallHandlers(returnValue, a4);
      }
      else
      {
        g_ClipsCurrentHandlerCore = handlerCore;
        g_ClipsMessageHandlerCursor = *(_DWORD *)(uintptr_t)(handlerCore + 4);
        if ( g_MessageHandler_WatchMessages )
          MessageHandler_TraceMessageSend((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_509548);
        if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore & 0x10) != 0 )
          MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int *)(uintptr_t)g_ClipsCurrentHandlerCore, (int)(intptr_t)asc_509548);
        if ( MessageHandler_CheckArgCount() )
          Rules_ExecuteRuleActions(
            *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 12) + 8),
            (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 28),
            returnValue,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore + 24),
            a4,
            (void (*)(void))Rules_ReportUndefinedMessageHandlerName);
        if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore & 0x10) != 0 )
          MessageHandler_TraceHandlerCall((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int *)(uintptr_t)g_ClipsCurrentHandlerCore, (int)(intptr_t)asc_50954C);
      }
      if ( g_MessageHandler_WatchMessages )
        MessageHandler_TraceMessageSend((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_50954C);
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
  while ( classIndex < *(unsigned __int16 *)(uintptr_t)(cls + 46) )
  {
    classOffset += 4;
    ++classIndex;
    MessageHandler_CollectClassHandlersIntoCore(
      (_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(classOffset + *(_DWORD *)(uintptr_t)(cls + 48) - 4),
      (uintptr_t)tops,
      messageName,
      (uintptr_t)&bots[1]);
  }
  return MessageHandler_JoinHandlerLinks(tops, &bots[1]);
}
