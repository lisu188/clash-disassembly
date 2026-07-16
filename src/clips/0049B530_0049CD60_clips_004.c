/* Generated from src/recovered/rules/clips/00496000_events.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0049B530) --------------------------------------------------------
signed int  Dribble_PrintRouter(int logicalName, unsigned __int8 *str, int a3)
{
  unsigned __int8 *v4; // ecx
  unsigned __int8 *charPtr; // edx
  _BYTE *v6; // edx
  char v7; // al
  int v8; // ecx
  int timestampIndex; // edx
  int v11; // edx
  char v12; // al
  _BYTE timestampBuffer[16]; // [esp+0h] [ebp-18h] BYREF
  int v14 CLASH95_UNUSED; // [esp+10h] [ebp-8h]

  v14 = a3;
  v4 = str;
  if ( g_Dribble_LineStartNeedsTimestamp )
  {
    sprintf_(
      timestampBuffer,
      "%03d:%02d:%02d ",
      *(_DWORD *)(uintptr_t)g_CLIPS_DribbleClockCentisecsPtr / 0x1770u % 0x3C,
      *(_DWORD *)(uintptr_t)g_CLIPS_DribbleClockCentisecsPtr / 0x64u % 0x3C,
      *(_DWORD *)(uintptr_t)g_CLIPS_DribbleClockCentisecsPtr % 0x64u);
    timestampIndex = 0;
    if ( timestampBuffer[0] )
    {
      do
      {
        Dribble_AppendChar((char *)(uintptr_t)(unsigned __int8)timestampBuffer[timestampIndex], timestampIndex, (int)(intptr_t)v4);
        v12 = timestampBuffer[v11 + 1];
        timestampIndex = v11 + 1;
      }
      while ( v12 );
    }
    g_Dribble_LineStartNeedsTimestamp = 0;
  }
  charPtr = v4;
  if ( *v4 )
  {
    do
    {
      Dribble_AppendChar((char *)(uintptr_t)*charPtr, (int)(intptr_t)charPtr, (int)(intptr_t)v4);
      if ( *v6 == 10 )
        g_Dribble_LineStartNeedsTimestamp = 1;
      v7 = v6[1];
      charPtr = v6 + 1;
    }
    while ( v7 );
  }
  IO_DeactivateRouter((int)(intptr_t)aDribble);
  Output_Write(logicalName, v8, v8);
  IO_ActivateRouter((int)(intptr_t)aDribble);
  return 1;
}
// 49B545: variable 'v4' is possibly undefined
// 49B559: variable 'v6' is possibly undefined
// 49B57A: variable 'v8' is possibly undefined
// 49B5F4: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACBC: using guessed type int dword_51ACBC;
// 54E6C0: using guessed type int dword_54E6C0;

//----- (0049B610) --------------------------------------------------------
int Dribble_GetcRouter(void)
{
  int v0; // edx
  unsigned int v1; // ecx
  char *v2; // edx
  int v3; // ecx
  int v4; // edx

  IO_DeactivateRouter((int)(intptr_t)aDribble);
  Lexer_PeekChar(v0, v1);
  IO_ActivateRouter((int)(intptr_t)aDribble);
  Dribble_AppendChar(v2, (int)(intptr_t)v2, v3);
  return v4;
}
// 49B61F: variable 'v0' is possibly undefined
// 49B61F: variable 'v1' is possibly undefined
// 49B632: variable 'v2' is possibly undefined
// 49B632: variable 'v3' is possibly undefined
// 49B637: variable 'v4' is possibly undefined
// 49B610: using guessed type int sub_49B610();

//----- (0049B640) --------------------------------------------------------
char * Dribble_AppendChar(char *result, int a2, int a3)
{
  if ( result == (char *)-1 )
  {
    if ( g_DribbleBufferLength > 0 )
    {
      Output_WriteFormatted(g_DribbleFileHandle, g_Clips_DribbleBuffer, g_DribbleFileHandle, (int)(intptr_t)aS_3, g_Clips_DribbleBuffer);
      result = (char *)(uintptr_t)g_Clips_DribbleBuffer;
      g_DribbleBufferLength = 0;
      *(_BYTE *)(uintptr_t)g_Clips_DribbleBuffer = 0;
    }
  }
  else if ( g_Lexer_PendingLineCharIndex >= 0 )
  {
    result = Str_AppendCharEscaping(
               (int)(intptr_t)result,
               (char *)(uintptr_t)g_Clips_DribbleBuffer,
               (unsigned int *)&g_Dribble_BufferCapacity,
               &g_DribbleBufferLength,
               g_Dribble_BufferCapacity + 120);
    g_Clips_DribbleBuffer = (int)(intptr_t)result;
  }
  else
  {
    if ( g_DribbleBufferLength > 0 )
    {
      Output_WriteFormatted(a3, a2, g_DribbleFileHandle, (int)(intptr_t)aS_3, g_Clips_DribbleBuffer);
      g_DribbleBufferLength = 0;
      *(_BYTE *)(uintptr_t)g_Clips_DribbleBuffer = 0;
    }
    return (char *)(uintptr_t)CRT_PutcToStream(a3, g_DribbleFileHandle);
  }
  return result;
}
// 49B6CF: variable 'a3' is possibly undefined
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);
// 51A628: using guessed type int dword_51A628;
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 51ACA0: using guessed type int dword_51ACA0;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B710) --------------------------------------------------------
int Dribble_UngetcRouter(void)
{
  int v0; // edx
  signed int v1; // ecx
  int v2; // edx

  if ( g_DribbleBufferLength > 0 )
    --g_DribbleBufferLength;
  *(_BYTE *)(uintptr_t)(g_DribbleBufferLength + g_Clips_DribbleBuffer) = 0;
  IO_DeactivateRouter((int)(intptr_t)aDribble);
  Lexer_SkipChar(v1, v0, v1);
  IO_ActivateRouter((int)(intptr_t)aDribble);
  return v2;
}
// 49B743: variable 'v1' is possibly undefined
// 49B743: variable 'v0' is possibly undefined
// 49B754: variable 'v2' is possibly undefined
// 51AC9C: using guessed type int dword_51AC9C;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B760) --------------------------------------------------------
int __fastcall Dribble_ExitRouter(int a1, int a2)
{
  int v3; // [esp-4h] [ebp-8h]

  if ( g_DribbleBufferLength > 0 )
  {
    v3 = a1;
    Output_WriteFormatted(g_Clips_DribbleBuffer, a2, g_DribbleFileHandle, (int)(intptr_t)aS_3, g_Clips_DribbleBuffer);
    a1 = v3;
  }
  if ( g_DribbleFileHandle )
    fclose_(a1);
  return 1;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B7B0) --------------------------------------------------------
const CHAR * Rules_DribbleOnCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)(uintptr_t)Rules_GetFileNameArg(1, v2, context);
  if ( result )
    return (const CHAR *)(uintptr_t)Dribble_TurnOn(result, a1);
  return result;
}
// 49B7D7: variable 'v2' is possibly undefined

//----- (0049B7F0) --------------------------------------------------------
signed int  Dribble_TurnOn(const CHAR *fileName, DWORD a2)
{
  const CHAR *v2; // ecx
  int v3; // ecx

  v2 = fileName;
  if ( g_DribbleFileHandle )
    Dribble_TurnOff();
  g_DribbleFileHandle = IO_FOpen(v2, (unsigned __int8 *)aW_3, (int)(intptr_t)v2, a2);
  if ( g_DribbleFileHandle )
  {
    IO_AddRouter((int)(intptr_t)aDribble, 40, (int)(intptr_t)Dribble_PrintRouter, (int)(intptr_t)Dribble_QueryRouter, (int)(intptr_t)Dribble_GetcRouter, (int)(intptr_t)Dribble_UngetcRouter, (int)(intptr_t)Dribble_ExitRouter);
    g_DribbleBufferLength = 0;
    if ( g_Dribble_StatusChangeCallback )
      g_Dribble_StatusChangeCallback(0);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v3, v3);
    return 0;
  }
}
// 49B809: variable 'v2' is possibly undefined
// 49B86D: variable 'v3' is possibly undefined
// 49B610: using guessed type int sub_49B610();
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 51ACA4: using guessed type int (__thiscall *dword_51ACA4)(_DWORD);

//----- (0049B890) --------------------------------------------------------
signed int Rules_DribbleOffCommand(void)
{
  if ( Lexer_TokenExpect(0) == -1 )
    return 0;
  else
    return Dribble_TurnOff();
}

//----- (0049B8C0) --------------------------------------------------------
signed int Dribble_TurnOff(void)
{
  int (__thiscall *statusCallback)(_DWORD); // edx
  int v1; // ecx
  int v2; // ecx
  signed int v3; // ecx
  signed int result; // eax

  statusCallback = g_Dribble_StatusChangeCallback;
  v1 = 0;
  if ( g_Dribble_StatusChangeCallback )
    g_Dribble_StatusChangeCallback(0);
  if ( !g_DribbleFileHandle )
    goto LABEL_7;
  if ( g_DribbleBufferLength > 0 )
    Output_WriteFormatted(v1, (int)(intptr_t)statusCallback, g_DribbleFileHandle, (int)(intptr_t)aS_3, g_Clips_DribbleBuffer);
  IO_DeleteRouter((int)(intptr_t)aDribble);
  if ( !fclose_(v2) )
LABEL_7:
    v3 = 1;
  g_DribbleFileHandle = 0;
  if ( g_Clips_DribbleBuffer )
  {
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_Clips_DribbleBuffer, g_Dribble_BufferCapacity);
    g_Clips_DribbleBuffer = 0;
  }
  result = v3;
  g_DribbleBufferLength = 0;
  g_Dribble_BufferCapacity = 0;
  return result;
}
// 49B8F1: variable 'v1' is possibly undefined
// 49B8F1: variable 'v0' is possibly undefined
// 49B909: variable 'v2' is possibly undefined
// 49B92A: variable 'v3' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AC98: using guessed type int dword_51AC98;
// 51AC9C: using guessed type int dword_51AC9C;
// 51ACA0: using guessed type int dword_51ACA0;
// 51ACA4: using guessed type int (__thiscall *dword_51ACA4)(_DWORD);
// 54E6C4: using guessed type int dword_54E6C4;

//----- (0049B980) --------------------------------------------------------
BOOL __thiscall Rules_BatchQueryStdin(void *this)
{
  return strcmp_(this, aStdin_2) == 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (0049B9A0) --------------------------------------------------------
int  Rules_BatchGetChar(int logicalName)
{
  return Rules_BatchReadChar(logicalName, 0);
}

//----- (0049B9B0) --------------------------------------------------------
int  Rules_BatchReadChar(int logicalName, unsigned int returnOnEOF)
{
  unsigned int returnOnEofFlag; // esi
  signed int closeStatus; // ecx
  int remainingChars; // edi
  int ch; // eax
  unsigned int v7; // ecx
  unsigned __int8 *charPtr; // eax
  char *appended; // eax
  int v11; // ecx
  int rv; // [esp+0h] [ebp-18h]

  returnOnEofFlag = returnOnEOF;
  closeStatus = 1;
  do
  {
    if ( g_ClipsBatchSourceIsStringFlag )
    {
      ch = Lexer_PeekChar(g_CurrentStringInputSource, closeStatus);
    }
    else
    {
      remainingChars = *(_DWORD *)(uintptr_t)(g_CurrentStringInputSource + 4);
      if ( remainingChars > 0 && (returnOnEOF = **(unsigned __int8 **)(uintptr_t)g_CurrentStringInputSource - 13, returnOnEOF > 0xFD) )
      {
        *(_DWORD *)(uintptr_t)(g_CurrentStringInputSource + 4) = remainingChars - 1;
        returnOnEOF = g_CurrentStringInputSource;
        charPtr = (unsigned __int8 *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_CurrentStringInputSource)++;
        ch = *charPtr;
      }
      else
      {
        ch = fgetc_(closeStatus, returnOnEOF);
      }
    }
    rv = ch;
    if ( ch == -1 )
    {
      if ( g_BatchEchoBufferLength > 0 )
        Output_Write((int)(intptr_t)aStdout_2, g_ClipsBatchEchoLineBuffer, closeStatus);
      closeStatus = Rules_CloseBatch();
    }
  }
  while ( rv == -1 && closeStatus == 1 );
  if ( rv == -1 )
  {
    if ( g_BatchEchoBufferLength > 0 )
      Output_Write((int)(intptr_t)aStdout_2, g_ClipsBatchEchoLineBuffer, closeStatus);
    IO_DeleteRouter((int)(intptr_t)aBatch);
    Rules_CloseBatch();
    if ( returnOnEofFlag == 1 )
      return -1;
    else
      return Lexer_PeekChar(logicalName, v7);
  }
  else
  {
    appended = Str_AppendCharEscaping(
                 (unsigned __int8)rv,
                 (char *)(uintptr_t)g_ClipsBatchEchoLineBuffer,
                 (unsigned int *)&g_ClipsBatchLineBufferCapacity,
                 &g_BatchEchoBufferLength,
                 g_ClipsBatchLineBufferCapacity + 120);
    g_ClipsBatchEchoLineBuffer = (int)(intptr_t)appended;
    if ( (_BYTE)rv == 10 )
    {
      Output_Write((int)(intptr_t)aStdout_2, (int)(intptr_t)appended, v11);
      g_BatchEchoBufferLength = 0;
      if ( g_ClipsBatchEchoLineBuffer )
      {
        if ( g_ClipsBatchLineBufferCapacity > 120 )
        {
          Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_ClipsBatchEchoLineBuffer, g_ClipsBatchLineBufferCapacity);
          g_ClipsBatchLineBufferCapacity = 0;
          g_ClipsBatchEchoLineBuffer = 0;
        }
      }
    }
    return rv;
  }
}
// 49B9F8: variable 'v4' is possibly undefined
// 49B9F8: variable 'a2' is possibly undefined
// 49BAA2: variable 'v7' is possibly undefined
// 49BAE1: variable 'v11' is possibly undefined
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB0: using guessed type int dword_51ACB0;
// 54E6C8: using guessed type int dword_54E6C8;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BB30) --------------------------------------------------------
signed int  Rules_BatchUngetChar(signed int ch, int logicalName)
{
  if ( g_BatchEchoBufferLength > 0 )
    logicalName = --g_BatchEchoBufferLength;
  if ( g_ClipsBatchEchoLineBuffer )
    *(_BYTE *)(uintptr_t)(g_ClipsBatchEchoLineBuffer + g_BatchEchoBufferLength) = 0;
  if ( g_ClipsBatchSourceIsStringFlag )
    return Lexer_SkipChar(ch, g_CurrentStringInputSource, logicalName);
  else
    return CRT_FlushBufferAndPutChar(ch, logicalName);
}
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 54E6C8: using guessed type int dword_54E6C8;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BB90) --------------------------------------------------------
signed int __thiscall Rules_BatchExitFunction(void *this)
{
  Rules_CloseAllBatchSources(this);
  return 1;
}

//----- (0049BBA0) --------------------------------------------------------
const CHAR * Rules_BatchCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)(uintptr_t)Rules_GetFileNameArg(1, v2, context);
  if ( result )
    return (const CHAR *)(uintptr_t)Rules_OpenBatch(result, 0, v4, a1);
  return result;
}
// 49BBC7: variable 'v2' is possibly undefined
// 49BBD2: variable 'v4' is possibly undefined

//----- (0049BBF0) --------------------------------------------------------
signed int  Rules_OpenBatch(const CHAR *fileName, int placeAtEnd, int a3, DWORD a4)
{
  int v6; // ecx
  int theFile; // edi

  theFile = IO_FOpen(fileName, (unsigned __int8 *)aR_1, a3, a4);
  if ( theFile )
  {
    if ( !g_Rules_BatchStackTop )
      IO_AddRouter((int)(intptr_t)aBatch, 20, 0, (int)(intptr_t)Rules_BatchQueryStdin, (int)(intptr_t)Rules_BatchGetChar, (int)(intptr_t)Rules_BatchUngetChar, (int)(intptr_t)Rules_BatchExitFunction);
    Rules_AddBatchEntry(placeAtEnd, theFile, 0, 0);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v6, (int)(intptr_t)fileName);
    return 0;
  }
}
// 49BC54: variable 'v6' is possibly undefined
// 51ACB4: using guessed type int dword_51ACB4;

//----- (0049BCC0) --------------------------------------------------------
_DWORD * Rules_AddBatchEntry(int placeAtEnd, int theSource, int theString, int sourceType)
{
  _DWORD *freeListHead; // edi
  _DWORD *result; // eax

  freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 64);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = *freeListHead;
    result = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x10);
  }
  result[3] = 0;
  *result = sourceType;
  result[1] = theSource;
  result[2] = theString;
  if ( g_Rules_BatchStackTop )
  {
    if ( placeAtEnd )
    {
      *(_DWORD *)(uintptr_t)(g_Batch_ListTail + 12) = result;
      g_Batch_ListTail = (int)(intptr_t)result;
    }
    else
    {
      result[3] = g_Rules_BatchStackTop;
      g_Rules_BatchStackTop = (int)(intptr_t)result;
      g_ClipsBatchSourceIsStringFlag = sourceType;
      g_CurrentStringInputSource = theSource;
      g_BatchEchoBufferLength = 0;
    }
  }
  else
  {
    g_Rules_BatchStackTop = (int)(intptr_t)result;
    g_Batch_ListTail = (int)(intptr_t)result;
    g_ClipsBatchSourceIsStringFlag = sourceType;
    g_CurrentStringInputSource = theSource;
    g_BatchEchoBufferLength = 0;
  }
  return result;
}
// 49BCED: variable 'a3' is possibly undefined
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB4: using guessed type int dword_51ACB4;
// 51ACB8: using guessed type int dword_51ACB8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BD60) --------------------------------------------------------
signed int Rules_CloseBatch(void)
{
  _DWORD *poppedEntry; // eax
  signed int result; // eax

  if ( !g_Rules_BatchStackTop )
    return 0;
  if ( *(_DWORD *)(uintptr_t)g_Rules_BatchStackTop )
  {
    IO_CloseStringRouter(*(_DWORD *)(uintptr_t)(g_Rules_BatchStackTop + 4));
    Mem_SmallBlockFree(*(_DWORD **)(uintptr_t)(g_Rules_BatchStackTop + 8), strlen(*(const char **)(uintptr_t)(g_Rules_BatchStackTop + 8)) + 1);
  }
  else
  {
    fclose_(0);
  }
  poppedEntry = (_DWORD *)(uintptr_t)g_Rules_BatchStackTop;
  g_Rules_BatchStackTop = *(_DWORD *)(uintptr_t)(g_Rules_BatchStackTop + 12);
  g_ClipsMemFreeListTemp = (int)(intptr_t)poppedEntry;
  *poppedEntry = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
  if ( g_Rules_BatchStackTop )
  {
    g_ClipsBatchSourceIsStringFlag = *(_DWORD *)(uintptr_t)g_Rules_BatchStackTop;
    g_CurrentStringInputSource = *(_DWORD *)(uintptr_t)(g_Rules_BatchStackTop + 4);
    g_BatchEchoBufferLength = 0;
    return 1;
  }
  else
  {
    g_Batch_ListTail = 0;
    g_CurrentStringInputSource = 0;
    if ( g_ClipsBatchEchoLineBuffer )
    {
      Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_ClipsBatchEchoLineBuffer, g_ClipsBatchLineBufferCapacity);
      g_ClipsBatchEchoLineBuffer = 0;
    }
    result = 0;
    g_BatchEchoBufferLength = 0;
    g_ClipsBatchLineBufferCapacity = 0;
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51ACA8: using guessed type int dword_51ACA8;
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB0: using guessed type int dword_51ACB0;
// 51ACB4: using guessed type int dword_51ACB4;
// 51ACB8: using guessed type int dword_51ACB8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6C8: using guessed type int dword_54E6C8;
// 54E6CC: using guessed type int dword_54E6CC;

//----- (0049BE60) --------------------------------------------------------
BOOL Rules_BatchIsActive(void)
{
  return g_Rules_BatchStackTop != 0;
}
// 51ACB4: using guessed type int dword_51ACB4;

//----- (0049BE70) --------------------------------------------------------
signed int __thiscall Rules_CloseAllBatchSources(void *this)
{
  signed int result; // eax

  if ( g_ClipsBatchEchoLineBuffer )
  {
    if ( g_BatchEchoBufferLength > 0 )
      Output_Write((int)(intptr_t)aStdout_2, g_ClipsBatchEchoLineBuffer, (int)(intptr_t)this);
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_ClipsBatchEchoLineBuffer, g_ClipsBatchLineBufferCapacity);
    g_ClipsBatchEchoLineBuffer = 0;
    g_BatchEchoBufferLength = 0;
    g_ClipsBatchLineBufferCapacity = 0;
  }
  IO_DeleteRouter((int)(intptr_t)aBatch);
  do
    result = Rules_CloseBatch();
  while ( result );
  return result;
}
// 51ACAC: using guessed type int dword_51ACAC;
// 51ACB0: using guessed type int dword_51ACB0;
// 54E6C8: using guessed type int dword_54E6C8;

//----- (0049BED0) --------------------------------------------------------
const CHAR * Rules_BatchStarCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)(uintptr_t)Rules_GetFileNameArg(1, v2, context);
  if ( result )
    return (const CHAR *)(uintptr_t)Rules_BatchStar(result, a1, context);
  return result;
}
// 49BEF7: variable 'v2' is possibly undefined

//----- (0049BF10) --------------------------------------------------------
signed int  Rules_BatchStar(const CHAR *fileName, DWORD a2, double context)
{
  char *appended; // edi
  int v4; // ecx
  int *theFile; // esi
  int v6; // edx
  int v7; // ecx
  int ch; // eax
  int nextCharPtr; // ecx
  int v10; // ecx
  int v11; // ecx
  unsigned __int8 *charPtr; // eax
  int lineLength; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int bufferSize[6]; // [esp+4h] [ebp-18h] BYREF

  appended = 0;
  lineLength = 0;
  bufferSize[0] = 0;
  theFile = (int *)(uintptr_t)IO_FOpen(fileName, (unsigned __int8 *)aR_1, (int)(intptr_t)fileName, a2);
  if ( theFile )
  {
    Rules_SetEvaluationErrorFlag(0);
    Lexer_ErrorRecover(0);
    while ( 1 )
    {
      if ( theFile[1] <= 0 || (unsigned int)*(unsigned __int8 *)(uintptr_t)*theFile - 13 <= 0xFD )
      {
        ch = fgetc_(v7, v6);
      }
      else
      {
        charPtr = (unsigned __int8 *)(uintptr_t)*theFile;
        nextCharPtr = *theFile + 1;
        --theFile[1];
        *theFile = nextCharPtr;
        ch = *charPtr;
      }
      if ( ch == -1 )
        break;
      appended = Str_AppendCharEscaping(ch, appended, bufferSize, &lineLength, bufferSize[0] + 80);
      if ( Lexer_IsCommandTextComplete((signed int)(intptr_t)appended) )
      {
        Rules_FlushPPBuffer();
        Rules_SetPPBufferStatus(0);
        Rules_RouteCommand(v10, 0, v10, context);
        Rules_FlushPPBuffer();
        Rules_SetEvaluationErrorFlag(0);
        Lexer_ErrorRecover(0);
        Rules_FreeBoundVariableEntry();
        appended = 0;
        Mem_ReleasePoolBlock(v11, bufferSize[0]);
        bufferSize[0] = 0;
        lineLength = 0;
      }
    }
    fclose_(nextCharPtr);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v4, v4);
    return 0;
  }
}
// 49BF53: variable 'v7' is possibly undefined
// 49BF53: variable 'v6' is possibly undefined
// 49BF95: variable 'v10' is possibly undefined
// 49BFBA: variable 'v11' is possibly undefined
// 49BFD3: variable 'v4' is possibly undefined
// 49C016: variable 'v9' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);

//----- (0049C030) --------------------------------------------------------
int  Rules_LoadCommand(DWORD a1, double context)
{
  int v2; // ecx
  int result; // eax
  const CHAR *v4; // edx
  int v5; // ecx
  int loadResult; // ecx
  int v7; // edx
  int v8; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, context);
  if ( result )
  {
    Rules_SetLoadInProgress(1);
    if ( Rules_Load(v4, v5, a1) )
    {
      Rules_SetLoadInProgress(0);
      return loadResult != -1;
    }
    else
    {
      Rules_SetLoadInProgress(0);
      Rules_OpenFileErrorMessage(v8, v7);
      return 0;
    }
  }
  return result;
}
// 49C059: variable 'v2' is possibly undefined
// 49C070: variable 'v4' is possibly undefined
// 49C070: variable 'v5' is possibly undefined
// 49C085: variable 'v6' is possibly undefined
// 49C097: variable 'v8' is possibly undefined
// 49C097: variable 'v7' is possibly undefined

//----- (0049C0B0) --------------------------------------------------------
const CHAR * Rules_LoadStarCommand(DWORD a1, double context)
{
  int v2; // ecx
  const CHAR *result; // eax
  int v4; // ecx
  int fileName; // edx
  signed int loadResult; // eax
  int v7; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = (const CHAR *)Rules_GetFileNameArg(1, v2, context);
  fileName = (int)result;
  if ( result )
  {
    loadResult = Rules_Load(result, v4, a1);
    if ( loadResult )
    {
      return (const CHAR *)(loadResult != -1);
    }
    else
    {
      Rules_OpenFileErrorMessage(v7, fileName);
      return 0;
    }
  }
  return result;
}
// 49C0D7: variable 'v2' is possibly undefined
// 49C0E2: variable 'v4' is possibly undefined
// 49C0FA: variable 'v7' is possibly undefined

//----- (0049C110) --------------------------------------------------------
int  Rules_SaveCommand(DWORD a1, double context)
{
  int v2; // ecx
  int result; // eax
  int v4; // ecx
  int fileName; // edx
  int v6; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, context);
  fileName = result;
  if ( result )
  {
    if ( Rules_Save((const CHAR *)(uintptr_t)result, v4, a1) )
    {
      return 1;
    }
    else
    {
      Rules_OpenFileErrorMessage(v6, fileName);
      return 0;
    }
  }
  return result;
}
// 49C137: variable 'v2' is possibly undefined
// 49C142: variable 'v4' is possibly undefined
// 49C158: variable 'v6' is possibly undefined

//----- (0049C170) --------------------------------------------------------
signed int  Rules_Load(const CHAR *fileName, int a2, DWORD a3)
{
  signed int result; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  result = IO_FOpen(fileName, (unsigned __int8 *)aR_2, a2, a3);
  if ( result )
  {
    IO_SetFastLoadFile(result);
    Rules_LoadConstructsFromLogicalName(v4, v5);
    IO_SetFastLoadFile(0);
    fclose_(v6);
    if ( v7 )
      return 1;
    else
      return -1;
  }
  return result;
}
// 49C18C: variable 'v4' is possibly undefined
// 49C18C: variable 'v5' is possibly undefined
// 49C19C: variable 'v6' is possibly undefined
// 49C1A3: variable 'v7' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (0049C1C0) --------------------------------------------------------
int  Rules_LoadConstructsFromLogicalName(int readSource, int a2)
{
  int v4; // edx
  _DWORD *v5; // ecx
  int v6; // ecx
  char *ppBuffer; // eax
  _DWORD *v8; // ecx
  signed int errorCorrection; // ebx
  int v11; // ecx
  int theToken; // [esp-4h] [ebp-20h] BYREF
  _DWORD noErrorsFlag[5]; // [esp+8h] [ebp-14h] BYREF

  noErrorsFlag[3] = a2;
  noErrorsFlag[0] = 1;
  if ( !g_ClipsCurrentEvaluationDepth )
    Rules_SetEvaluationErrorFlag(0);
  Lexer_ErrorRecover(0);
  Parser_NextToken(readSource, v4);
  if ( Rules_SkipToConstructBeginning(readSource, &theToken, v5, 0) == 1 )
  {
    do
    {
      if ( Rules_GetEvaluationErrorFlag() )
        break;
      Rules_FlushPPBuffer();
      if ( Rules_ParseConstruct() == 1 )
      {
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aError_2, v6);
        ppBuffer = (char *)(uintptr_t)Rules_GetPPBuffer();
        Output_WriteLongString((signed int)(intptr_t)g_IO_LogicalNameTable_WError[0], ppBuffer);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_505E94, (int)(intptr_t)noErrorsFlag);
        noErrorsFlag[0] = 0;
        Parser_NextToken(readSource, (int)(intptr_t)&theToken);
        errorCorrection = 1;
      }
      else
      {
        Parser_NextToken(readSource, (int)(intptr_t)&theToken);
        errorCorrection = 0;
      }
    }
    while ( Rules_SkipToConstructBeginning(readSource, &theToken, v8, errorCorrection) == 1 );
  }
  if ( Rules_GetWatchItemState((int)(intptr_t)aCompilations) == 1 || !Rules_GetLoadInProgress() )
  {
    Rules_DestroyPPBuffer();
    return noErrorsFlag[0];
  }
  else
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)asc_505E94, v11);
    Rules_DestroyPPBuffer();
    return noErrorsFlag[0];
  }
}
// 49C1F1: variable 'v4' is possibly undefined
// 49C1FA: variable 'v5' is possibly undefined
// 49C237: variable 'v6' is possibly undefined
// 49C27B: variable 'v8' is possibly undefined
// 49C2D5: variable 'v11' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A96C: using guessed type int dword_51A96C;

//----- (0049C2F0) --------------------------------------------------------
signed int  Rules_SkipToConstructBeginning(int readSource, _DWORD *theToken, _DWORD *noErrorsOut, signed int errorCorrection)
{
  int firstAttempt; // ecx
  int leftParenFound; // ebx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx

  firstAttempt = 1;
  leftParenFound = 0;
  if ( *theToken == 102 )
    return 0;
  while ( *theToken == 100 )
  {
    leftParenFound = 1;
LABEL_4:
    Parser_NextToken(readSource, (int)(intptr_t)theToken);
    if ( *theToken == 102 )
      return 0;
  }
  if ( *theToken != 2 || leftParenFound != 1 )
  {
    if ( firstAttempt )
    {
      if ( !errorCorrection )
      {
        errorCorrection = 1;
        *noErrorsOut = 0;
        Rules_PrintErrorID((int)(intptr_t)aCstrcpsr, 1, 1);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedTheBeg, v10);
      }
    }
    leftParenFound = 0;
    goto LABEL_4;
  }
  if ( !Rules_FindConstructByName() )
  {
    if ( v11 && !errorCorrection )
    {
      *noErrorsOut = 0;
      errorCorrection = 1;
      Rules_PrintErrorID((int)(intptr_t)aCstrcpsr, 1, 1);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedTheBeg, v12);
    }
    leftParenFound = 0;
    goto LABEL_4;
  }
  return 1;
}
// 49C33D: variable 'v7' is possibly undefined
// 49C367: variable 'v10' is possibly undefined
// 49C383: variable 'v11' is possibly undefined
// 49C3A4: variable 'v12' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049C3C0) --------------------------------------------------------
signed int Rules_ParseConstruct(void)
{
  int constructRecord; // ebx
  int v2; // edx
  int v3; // ecx

  constructRecord = Rules_FindConstructByName();
  if ( !constructRecord )
    return -1;
  Rules_GetEvaluationErrorFlag();
  Lexer_ErrorRecover(0);
  Rules_SetEvaluationErrorFlag(0);
  Parser_FreeLoopContextStack();
  Parser_PushFunctionParseState();
  g_ClipsParseReturnContext = 0;
  g_ParserBreakContextFlag = 0;
  ++g_ClipsCurrentEvaluationDepth;
  (*(void (**)(void))(uintptr_t)(constructRecord + 8))();
  --g_ClipsCurrentEvaluationDepth;
  Parser_PopFunctionParseState();
  Parser_FreeLoopContextStack();
  Rules_SetPPBufferStatus(0);
  Rules_SetEvaluationErrorFlag(v2);
  return v3;
}
// 49C434: variable 'v2' is possibly undefined
// 49C439: variable 'v3' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54E878: using guessed type int dword_54E878;
// 54E87C: using guessed type int dword_54E87C;

//----- (0049C440) --------------------------------------------------------
int  Rules_GetConstructNameAndComment(
        int readSource,
        int inputToken,
        int (*findFunction)(void),
        char *constructName,
        int (*deleteFunction)(void),
        char *constructSymbol,
        int fullMessageCR,
        int getComment,
        int moduleNameAllowed)
{
  signed int moduleSeparator; // eax
  int separatorPosition; // ebx
  signed int *moduleNameSymbol; // eax
  int *theModule; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // ecx
  signed int *constructNameSymbol; // ecx
  int v20; // ecx
  int v21; // ecx
  char *definingVerb; // edx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  char *trailingText; // edx
  int v28; // ecx
  int v29; // edx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  int v34; // edx
  char *Name; // eax
  int v36; // ecx
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int savedModule; // [esp+0h] [ebp-18h]
  int redefining; // [esp+8h] [ebp-10h]

  redefining = 0;
  Parser_NextToken(readSource, inputToken);
  if ( *(_DWORD *)(uintptr_t)inputToken != 2 )
  {
    Rules_PrintErrorID((int)(intptr_t)aCstrcpsr, 2, 1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aMissingNameFor, v31);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)constructName, v32);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aConstruct, v33);
    return 0;
  }
  moduleSeparator = Rules_FindModuleSeparator(*(_BYTE **)(uintptr_t)(*(_DWORD *)(uintptr_t)(inputToken + 4) + 16));
  separatorPosition = moduleSeparator;
  if ( moduleSeparator )
  {
    if ( !moduleNameAllowed )
      goto LABEL_23;
    moduleNameSymbol = Rules_ExtractModuleName(moduleSeparator);
    if ( !moduleNameSymbol )
      goto LABEL_23;
    theModule = Module_FindByName((_BYTE *)(uintptr_t)moduleNameSymbol[4]);
    savedModule = (int)(intptr_t)theModule;
    if ( !theModule )
    {
      Rules_ReportCantFindItem(v17, *(_DWORD *)(uintptr_t)(v16 + 16));
      return 0;
    }
    Module_SetCurrent((int)(intptr_t)theModule);
    constructNameSymbol = Rules_ExtractConstructName(separatorPosition, *(char **)(uintptr_t)(v18 + 16), v18);
    if ( !constructNameSymbol )
    {
LABEL_23:
      Parser_ReportSyntaxError();
      return 0;
    }
  }
  else
  {
    savedModule = Module_GetCurrent();
    if ( moduleNameAllowed )
    {
      IO_OutNewline();
      Name = (char *)(uintptr_t)Module_GetName(v34);
      IO_OutWriteToken(Name);
      IO_OutWriteToken(asc_505F2C);
      IO_OutWriteToken(*(char **)(uintptr_t)(v36 + 16));
    }
  }
  if ( Rules_FindImportExportConflict(constructName, savedModule, (_BYTE *)(uintptr_t)constructNameSymbol[4]) )
  {
    Lexer_WarnImpliedTemplate((int)(intptr_t)constructName, *(_DWORD *)(uintptr_t)(v20 + 16), 0);
    return 0;
  }
  if ( findFunction )
  {
    if ( findFunction() )
    {
      redefining = 1;
      if ( deleteFunction )
      {
        if ( !deleteFunction() )
        {
          Rules_PrintErrorID((int)(intptr_t)aCstrcpsr, 4, 1);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotRedefine, v37);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)constructName, v38);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_505F44, v39);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(v40 + 16), v40);
          Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aWhileItIsInUse, v41);
          return 0;
        }
      }
    }
  }
  if ( Rules_GetWatchItemState((int)(intptr_t)aCompilations) == 1 && Rules_GetLoadInProgress() )
  {
    if ( redefining )
      definingVerb = aRedefining;
    else
      definingVerb = aDefining;
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)definingVerb, v21);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)constructName, v23);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)asc_505F78, v24);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], *(_DWORD *)(uintptr_t)(v25 + 16), v25);
    if ( fullMessageCR )
      trailingText = asc_505E94;
    else
      trailingText = asc_505F44;
    goto LABEL_15;
  }
  if ( Rules_GetLoadInProgress() )
  {
    trailingText = constructSymbol;
LABEL_15:
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)trailingText, v26);
  }
  Parser_NextToken(readSource, inputToken);
  if ( *(_DWORD *)(uintptr_t)inputToken == 3 && getComment )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_505F44);
    IO_OutWriteToken(*(char **)(uintptr_t)(inputToken + 8));
    Parser_NextToken(readSource, v29);
  }
  if ( *(_DWORD *)(uintptr_t)inputToken != 101 )
  {
    IO_OutNewline();
    IO_OutWriteToken(asc_505F7C);
    IO_OutWriteToken(*(char **)(uintptr_t)(inputToken + 8));
  }
  return v28;
}
// 49C4B4: variable 'v18' is possibly undefined
// 49C4CB: variable 'v19' is possibly undefined
// 49C51B: variable 'v21' is possibly undefined
// 49C527: variable 'v23' is possibly undefined
// 49C536: variable 'v24' is possibly undefined
// 49C540: variable 'v25' is possibly undefined
// 49C55E: variable 'v26' is possibly undefined
// 49C593: variable 'v29' is possibly undefined
// 49C5B4: variable 'v28' is possibly undefined
// 49C5DD: variable 'v31' is possibly undefined
// 49C5E9: variable 'v32' is possibly undefined
// 49C5F8: variable 'v33' is possibly undefined
// 49C63A: variable 'v17' is possibly undefined
// 49C637: variable 'v16' is possibly undefined
// 49C667: variable 'v34' is possibly undefined
// 49C67B: variable 'v36' is possibly undefined
// 49C68A: variable 'v20' is possibly undefined
// 49C6EA: variable 'v37' is possibly undefined
// 49C6F6: variable 'v38' is possibly undefined
// 49C705: variable 'v39' is possibly undefined
// 49C70F: variable 'v40' is possibly undefined
// 49C721: variable 'v41' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];

//----- (0049C760) --------------------------------------------------------
int  Rules_UnlinkListNode(int theConstruct)
{
  int constructAddr; // ecx
  int currentItem; // eax
  int i; // ebx
  int result; // eax

  constructAddr = theConstruct;
  currentItem = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theConstruct + 8) + 4);
  for ( i = 0; currentItem != constructAddr; currentItem = *(_DWORD *)(uintptr_t)(currentItem + 16) )
    i = currentItem;
  if ( !currentItem )
  {
    Rules_ReportSystemError(constructAddr, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( i )
  {
    *(_DWORD *)(uintptr_t)(i + 16) = *(_DWORD *)(uintptr_t)(constructAddr + 16);
    result = *(_DWORD *)(uintptr_t)(constructAddr + 8);
    if ( constructAddr != *(_DWORD *)(uintptr_t)(result + 8) )
      return result;
    goto LABEL_9;
  }
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(constructAddr + 8) + 4) = *(_DWORD *)(uintptr_t)(constructAddr + 16);
  result = *(_DWORD *)(uintptr_t)(constructAddr + 8);
  if ( constructAddr == *(_DWORD *)(uintptr_t)(result + 8) )
LABEL_9:
    *(_DWORD *)(uintptr_t)(result + 8) = i;
  return result;
}
// 49C7A4: variable 'v1' is possibly undefined

//----- (0049C7D0) --------------------------------------------------------
signed int  Rules_ImportExportConflictMessage(int constructName, int itemName, int causedByConstruct)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx

  Rules_PrintErrorID((int)(intptr_t)aCstrcpsr, 3, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotDefine, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], constructName, v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_505F44, v7);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], itemName, v8);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aBecauseOfAnImp, v9);
  if ( causedByConstruct )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCausedByThe, v10);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], causedByConstruct, v12);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_505F44, v13);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v14, v14);
  }
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_ConstructError, v10);
}
// 49C7F7: variable 'v5' is possibly undefined
// 49C803: variable 'v6' is possibly undefined
// 49C812: variable 'v7' is possibly undefined
// 49C81E: variable 'v8' is possibly undefined
// 49C82D: variable 'v9' is possibly undefined
// 49C853: variable 'v10' is possibly undefined
// 49C85F: variable 'v12' is possibly undefined
// 49C86E: variable 'v13' is possibly undefined
// 49C87A: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049C8A0) --------------------------------------------------------
signed int Rules_RegisterControlFlowFunctions(void)
{
  Rules_RegisterHostFunction(aIf, 117, (int)(intptr_t)aIffunction, (int)(intptr_t)Rules_IfFunction, 0);
  Rules_RegisterHostFunction(aWhile, 117, (int)(intptr_t)aWhilefunction, (int)(intptr_t)Rules_WhileFunction, 0);
  Rules_RegisterHostFunction(aLoopForCount, 117, (int)(intptr_t)aLoopforcountfu, (int)(intptr_t)Rules_LoopForCountFunction, 0);
  Rules_RegisterHostFunction(aGetLoopCount, 108, (int)(intptr_t)aGetloopcount, (int)(intptr_t)Rules_GetLoopCountFunction, 0);
  Rules_RegisterHostFunction(aBind, 117, (int)(intptr_t)aBindfunction, (int)(intptr_t)Rules_BindFunction, 0);
  Rules_RegisterHostFunction(aProgn, 117, (int)(intptr_t)aPrognfunction, (int)(intptr_t)Rules_PrognFunction, 0);
  Rules_RegisterHostFunction(aReturn, 117, (int)(intptr_t)aReturnfunction, (int)(intptr_t)Rules_ReturnFunction, 0);
  Rules_RegisterHostFunction(aBreak, 118, (int)(intptr_t)aBreakfunction, (int)(intptr_t)Rules_BreakFunction, 0);
  Rules_RegisterHostFunction(aSwitch, 117, (int)(intptr_t)aSwitchfunction, (int)(intptr_t)Rules_SwitchFunction, 0);
  Parser_RegisterProceduralFunctionParsers();
  Rules_SetFunctionSeqOverloadFlags(aProgn, 0);
  Rules_SetFunctionSeqOverloadFlags(aIf, 0);
  Rules_SetFunctionSeqOverloadFlags(aWhile, 0);
  Rules_SetFunctionSeqOverloadFlags(aLoopForCount, 0);
  Rules_SetFunctionSeqOverloadFlags(aReturn, 0);
  return Rules_SetFunctionSeqOverloadFlags(aSwitch, 0);
}
// 49CD20: using guessed type int sub_49CD20();
// 4BDD40: using guessed type int sub_4BDD40(void);

//----- (0049CA00) --------------------------------------------------------
int  Rules_WhileFunction(double context)
{
  _DWORD *returnValue; // ecx
  int result; // eax
  int theResult; // [esp+0h] [ebp-30h] BYREF
  int resultType; // [esp+4h] [ebp-2Ch]
  int resultValue; // [esp+8h] [ebp-28h]
  int resultBegin; // [esp+Ch] [ebp-24h]
  int resultEnd; // [esp+10h] [ebp-20h]

  ++g_ClipsCurrentEvaluationDepth;
  Rules_RtnUnknown(1, &theResult, context);
  while ( resultValue != g_ClipsFalseSymbol || resultType != 2 )
  {
    if ( g_ClipsHaltExecution == 1 )
      break;
    if ( g_ClipsBreakFlag == 1 )
      break;
    if ( g_ClipsHaltExecutionFlag == 1 )
      break;
    Rules_RtnUnknown(2, &theResult, context);
    --g_ClipsCurrentEvaluationDepth;
    Rules_RunPeriodicCleanup(0, 1);
    ++g_ClipsCurrentEvaluationDepth;
    if ( g_ClipsBreakFlag == 1 || g_ClipsHaltExecutionFlag == 1 )
      break;
    Rules_RtnUnknown(1, &theResult, context);
  }
  g_ClipsBreakFlag = 0;
  --g_ClipsCurrentEvaluationDepth;
  if ( g_ClipsHaltExecutionFlag == 1 )
  {
    returnValue[1] = resultType;
    returnValue[2] = resultValue;
    returnValue[3] = resultBegin;
    result = resultEnd;
    returnValue[4] = resultEnd;
  }
  else
  {
    returnValue[1] = 2;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  return result;
}
// 49CA6D: variable 'v1' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CB10) --------------------------------------------------------
int  Rules_LoopForCountFunction(_DWORD *returnValue, double context)
{
  _DWORD *freeListHead; // edx
  int *loopVarNode; // edi
  int *savedLoopVarNode; // esi
  int result; // eax
  int endCount; // ecx
  int nextCount; // edi
  _DWORD argData[2]; // [esp+0h] [ebp-30h] BYREF
  int argValue; // [esp+8h] [ebp-28h]
  int resultBegin; // [esp+Ch] [ebp-24h]
  int resultEnd; // [esp+10h] [ebp-20h]

  freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 32);
  if ( freeListHead )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeListHead;
    loopVarNode = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    loopVarNode = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *loopVarNode = 0;
  savedLoopVarNode = loopVarNode;
  loopVarNode[1] = g_LoopForCountBindingStack;
  g_LoopForCountBindingStack = (int)(intptr_t)loopVarNode;
  if ( Lexer_ParseValueList(1, argData, 1, context) )
  {
    *loopVarNode = *(_DWORD *)(uintptr_t)(argValue + 16);
    if ( Lexer_ParseValueList(2, argData, 1, context) )
    {
      if ( *(_DWORD *)(uintptr_t)(argValue + 16) >= *loopVarNode )
      {
        do
        {
          if ( g_ClipsHaltExecution == 1 )
            break;
          if ( g_ClipsBreakFlag == 1 )
            break;
          if ( g_ClipsHaltExecutionFlag == 1 )
            break;
          ++g_ClipsCurrentEvaluationDepth;
          Rules_RtnUnknown(3, argData, context);
          --g_ClipsCurrentEvaluationDepth;
          Rules_RunPeriodicCleanup(0, 1);
          if ( g_ClipsBreakFlag == 1 )
            break;
          if ( g_ClipsHaltExecutionFlag == 1 )
            break;
          nextCount = *savedLoopVarNode + 1;
          *savedLoopVarNode = nextCount;
        }
        while ( endCount >= nextCount );
      }
      g_ClipsBreakFlag = 0;
      if ( g_ClipsHaltExecutionFlag == 1 )
      {
        returnValue[1] = argData[1];
        returnValue[2] = argValue;
        returnValue[3] = resultBegin;
        returnValue[4] = resultEnd;
      }
      else
      {
        returnValue[1] = 2;
        returnValue[2] = g_ClipsFalseSymbol;
      }
      g_LoopForCountBindingStack = savedLoopVarNode[1];
      g_ClipsMemFreeListTemp = (int)(intptr_t)savedLoopVarNode;
      *savedLoopVarNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    }
    else
    {
      returnValue[1] = 2;
      returnValue[2] = g_ClipsFalseSymbol;
      g_LoopForCountBindingStack = loopVarNode[1];
      g_ClipsMemFreeListTemp = (int)(intptr_t)loopVarNode;
      *loopVarNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      result = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
    }
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    g_LoopForCountBindingStack = loopVarNode[1];
    g_ClipsMemFreeListTemp = (int)(intptr_t)loopVarNode;
    *loopVarNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    result = g_ClipsMemoryTable;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
  }
  return result;
}
// 49CCFF: variable 'v7' is possibly undefined
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 51ACC8: using guessed type int dword_51ACC8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049CD20) --------------------------------------------------------
int Rules_GetLoopCountFunction(void)
{
  int depth; // eax
  _DWORD *i; // edx

  depth = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2) + 16);
  for ( i = (_DWORD *)(uintptr_t)g_LoopForCountBindingStack; depth > 0; i = (_DWORD *)(uintptr_t)i[1] )
    --depth;
  return *i;
}
// 49CD20: using guessed type int sub_49CD20();
// 51A960: using guessed type int dword_51A960;
// 51ACC8: using guessed type int dword_51ACC8;

//----- (0049CD60) --------------------------------------------------------
int  Rules_IfFunction(double context)
{
  int result; // eax
  _DWORD *returnValue; // ecx
  int argCount; // ebx
  _DWORD *resultValue; // ecx

  result = Rules_ArgRangeCheck((int)(intptr_t)aIf, 3);
  argCount = result;
  if ( result == -1 )
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    result = Rules_RtnUnknown(1, returnValue, context);
    if ( g_ClipsBreakFlag != 1 && g_ClipsHaltExecutionFlag != 1 )
    {
      if ( g_ClipsFalseSymbol == resultValue[2] && resultValue[1] == 2 && argCount == 3 )
      {
        return Rules_RtnUnknown(3, resultValue, context);
      }
      else if ( g_ClipsFalseSymbol == resultValue[2] && resultValue[1] == 2 )
      {
        resultValue[2] = g_ClipsFalseSymbol;
      }
      else
      {
        return Rules_RtnUnknown(2, resultValue, context);
      }
    }
  }
  return result;
}
// 49CD81: variable 'v2' is possibly undefined
// 49CDBA: variable 'v4' is possibly undefined
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACC4: using guessed type int dword_51ACC4;
// 54DD70: using guessed type int dword_54DD70;
