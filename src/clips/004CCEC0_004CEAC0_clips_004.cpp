/* Generated from src/recovered/rules/clips/004C82D0_methods.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "004CCEC0_004CEAC0_clips_004_local.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE int Runtime_ExprDescriptorNoop (int value);

//----- (004CCEC0) --------------------------------------------------------
CLASH95_TEST_VISIBLE int Runtime_ExprDescriptorNoop(int value)
{
  return value;
}

int MessageHandler_RegisterCommands(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  g_EvalDesc_GetSelfSlotDirect[1] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_GetSelfSlotDirect[2] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_GetSelfSlotDirect[4] = (int)(uintptr_t)MessageHandler_GetSelfSlotDirect;
  g_EvalDesc_PutSelfSlotDirect[1] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_PutSelfSlotDirect[2] = (int)(uintptr_t)Runtime_ExprDescriptorNoop;
  g_EvalDesc_PutSelfSlotDirect[4] = (int)(uintptr_t)MessageHandler_PutSelfSlotDirect;
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDesc_GetSelfSlotDirect, 58);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDesc_PutSelfSlotDirect, 59);
  g_MessageHandler_InitSymbol = (int)(intptr_t)Str_Intern(aInit, v0);
  ++*(_DWORD *)(uintptr_t)(g_MessageHandler_InitSymbol + 4);
  g_ClipsDeleteMessageSymbol = (int)(intptr_t)Str_Intern(aDelete_0, v1);
  ++*(_DWORD *)(uintptr_t)(g_ClipsDeleteMessageSymbol + 4);
  Rules_AddClearFunction((int)(intptr_t)aDefclass_1, (int)(intptr_t)MessageHandler_RegisterSystemHandlers, -100);
  g_MessageHandler_SelfSymbol = (int)(intptr_t)Str_Intern(aSelf, v2);
  ++*(_DWORD *)(uintptr_t)(g_MessageHandler_SelfSymbol + 4);
  Rules_RegisterConstructType((int)(intptr_t)aDefmessageHa_0, (int)(intptr_t)aDefmessageHand, 0, (int)(intptr_t)MessageHandler_ParseDefinition, 0, 0, 0, 0, 0, 0, 0, 0);
  Rules_RegisterHostFunction(aUndefmessageHa, 118, (int)(intptr_t)aUndefmessageha, (int)(intptr_t)MessageHandler_UndefineCommand, (int)(intptr_t)a23w_0);
  Rules_RegisterHostFunction(aSend, 117, (int)(intptr_t)aSendcommand, (int)(intptr_t)MessageHandler_ParseAndSend, (int)(intptr_t)a2Uuw);
  Rules_RegisterHostFunction(aPreviewSend, 118, (int)(intptr_t)aPreviewsendcom, (int)(intptr_t)MessageHandler_PreviewSendCommand, (int)(intptr_t)a22w_0);
  Rules_RegisterHostFunction(aPpdefmessageHa, 118, (int)(intptr_t)aPpdefmessageha, (int)(intptr_t)MessageHandler_PrettyPrintCommand, (int)(intptr_t)a23w_0);
  Rules_RegisterHostFunction(aListDefmessage, 118, (int)(intptr_t)aListdefmessage, (int)(intptr_t)MessageHandler_ListCommand, (int)(intptr_t)a02w_0);
  Rules_RegisterHostFunction(aNextHandlerp, 98, (int)(intptr_t)aNexthandlerava, (int)(intptr_t)MessageHandler_HasNextHandler, (int)(intptr_t)a00_12);
  Rules_SetFunctionSeqOverloadFlags((_BYTE*)(aNextHandlerp), 0);
  Rules_RegisterHostFunction(aCallNextHandle, 117, v3, (int)(intptr_t)MessageHandler_CallNextHandler, (int)(intptr_t)a00_12);
  Rules_SetFunctionSeqOverloadFlags((_BYTE*)(aCallNextHandle), 0);
  Rules_RegisterHostFunction(aOverrideNextHa, 117, v4, (int)(intptr_t)MessageHandler_CallNextHandler, 0);
  Rules_SetFunctionSeqOverloadFlags((_BYTE*)(aOverrideNextHa), 0);
  Rules_RegisterHostFunction(aDynamicGet, 117, v5, (int)(intptr_t)MessageHandler_DynamicGetSlot, (int)(intptr_t)a11w_12);
  Rules_RegisterHostFunction(aDynamicPut, 117, (int)(intptr_t)aDynamichandl_0, (int)(intptr_t)MessageHandler_DynamicPutSlot, (int)(intptr_t)a1W_2);
  Rules_RegisterHostFunction(aGet, 117, (int)(intptr_t)aDynamichandler, (int)(intptr_t)MessageHandler_DynamicGetSlot, (int)(intptr_t)a11w_12);
  Rules_RegisterHostFunction(aPut, 117, (int)(intptr_t)aDynamichandl_0, (int)(intptr_t)MessageHandler_DynamicPutSlot, (int)(intptr_t)a1W_2);
  Rules_AddWatchItem((int)(intptr_t)aMessages, 0, 36, (int)(intptr_t)&g_MessageHandler_WatchMessages, 0, 0);
  return Rules_AddWatchItem((int)(intptr_t)aMessageHandl_0, 0, 35, (int)(intptr_t)&g_Rules_WatchMessageHandlers, (int)(intptr_t)MessageHandler_WatchCommand, (int)(intptr_t)MessageHandler_ListWatchItemsCommand);
}
// 4CCEE6: variable 'v0' is possibly undefined
// 4CCEF8: variable 'v1' is possibly undefined
// 4CCF22: variable 'v2' is possibly undefined
// 4CD037: variable 'v3' is possibly undefined
// 4CD063: variable 'v4' is possibly undefined
// 4CD092: variable 'v5' is possibly undefined
// 51AD34: using guessed type int dword_51AD34;
// 51AD38: using guessed type int dword_51AD38;
// 51AD4C: using guessed type int dword_51AD4C;
// 51AD50: using guessed type int dword_51AD50;
// 51C708: using guessed type int dword_51C708;

//----- (004CD180) --------------------------------------------------------
int  MessageHandler_EnumNext(int classPtr, int handlerIndex)
{
  if ( !handlerIndex )
    return *(_DWORD *)(uintptr_t)(classPtr + 88) != 0;
  if ( handlerIndex == *(_DWORD *)(uintptr_t)(classPtr + 96) )
    return 0;
  return handlerIndex + 1;
}

//----- (004CD1C0) --------------------------------------------------------
_BYTE * MessageHandler_SetWatchFlagField(char newState, int classPtr, int handlerIndex)
{
  _BYTE *result; // eax

  result = (_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)(classPtr + 88) + 36 * (handlerIndex - 1));
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * (newState & 1);
  return result;
}

//----- (004CD270) --------------------------------------------------------
int  MessageHandler_UndefineCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int *classPtr; // edi
  int v6; // ecx
  signed int *v7; // esi
  int v8; // ecx
  char *typeName; // ebx
  int v10; // ecx
  _DWORD v11[2]; // [esp-8h] [ebp-2Ch] BYREF
  signed int *parseBuffer; // [esp+0h] [ebp-24h]
  int v13 CLASH95_UNUSED; // [esp+1Ch] [ebp-8h]

  v13 = a1;
  if ( Rules_IsBloaded() )
  {
    Rules_PrintErrorID((int)(intptr_t)aMsgcom, 3, 0);
    return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToDele_1, v3);
  }
  result = Lexer_ParseValueList(1, v11, 2, a2);
  if ( result )
  {
    classPtr = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)parseBuffer[4]);
    if ( !classPtr && strcmp_(v4, (_DWORD)(uintptr_t)(asc_50BFD4)) )
      return Class_ReportLookupError(v6, parseBuffer[4]);
    result = Lexer_ParseValueList(2, v11, 2, a2);
    if ( result )
    {
      v7 = parseBuffer;
      if ( Rules_RtnArgCount() != 3 )
      {
        typeName = g_MessageHandler_PrimaryAfterTypeNames[0];
        return MessageHandler_UndefineForClassOrAll((_DWORD*)(classPtr), v7, v8, (int)(intptr_t)typeName);
      }
      result = Lexer_ParseValueList(3, v11, 2, a2);
      if ( result )
      {
        typeName = (char *)(uintptr_t)parseBuffer[4];
        if ( strcmp_(v10, (_DWORD)(uintptr_t)(asc_50BFD4)) )
          return MessageHandler_UndefineForClassOrAll((_DWORD*)(classPtr), v7, v8, (int)(intptr_t)typeName);
        return MessageHandler_UndefineForClassOrAll((_DWORD*)(classPtr), v7, v8, 0);
      }
    }
  }
  return result;
}
// 4CD2BF: variable 'v3' is possibly undefined
// 4CD2E4: variable 'v4' is possibly undefined
// 4CD324: variable 'v8' is possibly undefined
// 4CD33E: variable 'v6' is possibly undefined
// 4CD375: variable 'v10' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51AD44: using guessed type char *off_51AD44[2];

//----- (004CD450) --------------------------------------------------------
signed int  MessageHandler_PrettyPrintCommand(double a1)
{
  signed int result; // eax
  int *classPtr; // edi
  int *classNameSymbol; // ebp
  _DWORD *v4; // ecx
  int *handlerNameSymbol; // esi
  signed int handlerType; // ebx
  _DWORD *handler; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  _DWORD parseBuffer[2]; // [esp+0h] [ebp-30h] BYREF
  int v16; // [esp+8h] [ebp-28h]

  result = Lexer_ParseValueList(1, parseBuffer, 2, a1);
  classPtr = 0;
  if ( result )
  {
    classNameSymbol = Rules_FindSymbolEntry((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v16 + 16));
    result = Lexer_ParseValueList(2, v4, 2, a1);
    if ( result )
    {
      handlerNameSymbol = Rules_FindSymbolEntry((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v16 + 16));
      if ( Rules_RtnArgCount() != 3 || (result = Lexer_ParseValueList(3, parseBuffer, 2, a1)) != 0 )
      {
        handlerType = MessageHandler_TypeIndexFromKeyword((int)(intptr_t)aPpdefmessageHa);
        if ( handlerType == 4 )
        {
          return Lexer_ErrorRecover(1);
        }
        else
        {
          if ( classNameSymbol )
            classPtr = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)classNameSymbol[4]);
          if ( classPtr && handlerNameSymbol && (handler = Class_FindMessageHandler((_DWORD*)(classPtr), (int)(intptr_t)handlerNameSymbol, handlerType), result = handler == 0, handler) )
          {
            if ( handler[8] )
              return Output_WriteLongString((signed int)(intptr_t)g_IO_LogicalName_WDisplay, (char *)(uintptr_t)handler[8]);
          }
          else
          {
            Rules_PrintErrorID((int)(intptr_t)aMsgcom, 2, 0);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToFind_0, v8);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], handlerNameSymbol[4], v9);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_50C030, v10);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v11, v11);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aForClass, v12);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], classNameSymbol[4], v13);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunctionPpde, v14);
            return Lexer_ErrorRecover(1);
          }
        }
      }
    }
  }
  return result;
}
// 4CD49B: variable 'v4' is possibly undefined
// 4CD581: variable 'v8' is possibly undefined
// 4CD58E: variable 'v9' is possibly undefined
// 4CD59D: variable 'v10' is possibly undefined
// 4CD5A9: variable 'v11' is possibly undefined
// 4CD5B8: variable 'v12' is possibly undefined
// 4CD5C5: variable 'v13' is possibly undefined
// 4CD5D4: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A624: using guessed type char *off_51A624;
// 51AD44: using guessed type char *off_51AD44[2];

//----- (004CD5F0) --------------------------------------------------------
int * MessageHandler_ListCommand(double a1)
{
  int v1; // ecx
  int *result; // eax
  int classArg[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !Rules_RtnArgCount() )
    return (int *)(uintptr_t)MessageHandler_PrintHandlerListTally((int)(intptr_t)g_IO_LogicalName_WDisplay, 0, v1, 0);
  result = Class_ParseClassNameAndInheritFlag((int)(intptr_t)aListDefmessage, (_DWORD*)(classArg), a1);
  if ( result )
    return (int *)(uintptr_t)MessageHandler_PrintHandlerListTally((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)result, (int)(intptr_t)g_IO_LogicalName_WDisplay, classArg[0]);
  return result;
}
// 4CD61D: variable 'v1' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CD640) --------------------------------------------------------
int * MessageHandler_PreviewSendCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx
  _DWORD parseBuffer[2]; // [esp-8h] [ebp-28h] BYREF
  int argSlot; // [esp+0h] [ebp-20h]
  int v6 CLASH95_UNUSED; // [esp+18h] [ebp-8h]

  v6 = a1;
  result = (int *)(uintptr_t)Lexer_ParseValueList(1, parseBuffer, 2, a2);
  if ( result )
  {
    if ( Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argSlot + 16)) )
    {
      result = (int *)(uintptr_t)Lexer_ParseValueList(2, parseBuffer, 2, a2);
      if ( result )
        return MessageHandler_PreviewSendForSymbol((int)(intptr_t)g_IO_LogicalName_WDisplay, (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argSlot + 16));
    }
    else
    {
      return (int *)(uintptr_t)Class_ReportLookupError(v3, *(_DWORD *)(uintptr_t)(argSlot + 16));
    }
  }
  return result;
}
// 4CD6B9: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004CD6D0) --------------------------------------------------------
int  MessageHandler_GetRecordPPForm(int classPtr, int handlerIndex)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(classPtr + 88) + 36 * (handlerIndex - 1) + 32);
}

//----- (004CD6F0) --------------------------------------------------------
int  MessageHandler_PrintHandlerListTally(int logicalName, int classPtr, int a3, int inheritFlag)
{
  unsigned __int16 *v5; // edx
  int handlerCount; // edi
  int v8; // ecx
  unsigned __int16 v9; // [esp+0h] [ebp-18h] BYREF
  int *v10 CLASH95_UNUSED; // [esp+2h] [ebp-16h]
  int classFrame[4]; // [esp+8h] [ebp-10h] BYREF

  classFrame[3] = a3;
  if ( classPtr )
  {
    classFrame[0] = classPtr;
    if ( inheritFlag )
    {
      v5 = (unsigned __int16 *)(uintptr_t)(classPtr + 46);
    }
    else
    {
      v5 = &v9;
      v9 = 1;
      v10 = classFrame;
    }
    handlerCount = MessageHandler_CountAndPrintHandlers(logicalName, v5, a3, 0);
  }
  else
  {
    handlerCount = 0;
    v9 = 1;
    for ( classFrame[0] = Class_GetNextRecord(0); classFrame[0]; classFrame[0] = Class_GetNextRecord(classFrame[0]) )
    {
      v10 = classFrame;
      handlerCount += MessageHandler_CountAndPrintHandlers(logicalName, &v9, v8, 0);
    }
  }
  return Rules_PrintTally(logicalName, handlerCount, (int)(intptr_t)aMessageHandl_0, (int)(intptr_t)aMessageHandl_5);
}
// 4CD775: variable 'v8' is possibly undefined

//----- (004CD790) --------------------------------------------------------
int * MessageHandler_PreviewSendForSymbol(int logicalName, _BYTE *handlerName)
{
  int *result; // eax
  int v4; // ecx
  int v5; // ecx

  result = Rules_FindSymbolEntry(handlerName);
  if ( result )
  {
    result = (int *)(uintptr_t)MessageHandler_BuildPreviewHandlerCore(v4, (int)(intptr_t)result);
    if ( result )
    {
      MessageHandler_PrintHandlerPreview(logicalName, result, 0);
      return (int *)(uintptr_t)MessageHandler_FreeHandlerCore(v5);
    }
  }
  return result;
}
// 4CD7A8: variable 'v4' is possibly undefined
// 4CD7C0: variable 'v5' is possibly undefined

//----- (004CD7D0) --------------------------------------------------------
int  MessageHandler_CountAndPrintHandlers(int logicalName, unsigned __int16 *classArray, int a3, unsigned int classIndex)
{
  unsigned int handlerIndex; // ecx
  int i; // esi
  int classPtr; // eax
  int totalCount; // [esp+0h] [ebp-18h]

  totalCount = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(classArray + 1) + 4 * classIndex) + 96);
  if ( classIndex < (unsigned int)*classArray - 1 )
    totalCount += MessageHandler_CountAndPrintHandlers(logicalName, (short unsigned int*)(intptr_t)((int)(intptr_t)classArray), a3, classIndex + 1);
  handlerIndex = 0;
  for ( i = 0; ; i += 36 )
  {
    classPtr = *(_DWORD *)(uintptr_t)(4 * classIndex + *(_DWORD *)(classArray + 1));
    if ( handlerIndex >= *(_DWORD *)(uintptr_t)(classPtr + 96) )
      break;
    MessageHandler_PrintNameTypeAndClass(logicalName, (_DWORD *)(uintptr_t)(i + *(_DWORD *)(uintptr_t)(classPtr + 88)), 1);
  }
  return totalCount;
}
// 4CD811: variable 'v6' is possibly undefined

//----- (004CD850) --------------------------------------------------------
int MessageHandler_RegisterSystemHandlers(void)
{
  MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aInit, 0, (_BYTE*)(aInitSlots_0));
  MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aDelete_0, 0, (_BYTE*)(aDeleteInstan_0));
  MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aPrint, 0, (_BYTE*)(aPpinstance_0));
  MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aDirectModify_2, 1, (_BYTE*)(aDirectModify_1));
  MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aMessageModif_3, 1, (_BYTE*)(aMessageModif_2));
  MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aDirectDuplic_2, 2, (_BYTE*)(aDirectDuplic_1));
  return MessageHandler_AddSystemHandler((_BYTE*)(aUser_0), aMessageDupli_3, 2, (_BYTE*)(aMessageDupli_2));
}

//----- (004CD900) --------------------------------------------------------
signed int  MessageHandler_UndefineForClassOrAll(_DWORD *theClass, signed int *handlerName, int a3, int typeSpecified)
{
  int v6; // edx
  signed int typeIndex; // ebp
  int v8; // eax
  int v9; // edx
  _DWORD *classRecord; // esi
  int success; // [esp+0h] [ebp-14h]

  v6 = typeSpecified;
  if ( !handlerName )
    handlerName = Str_Intern(asc_50BFD4, a3);
  if ( v6 )
  {
    typeIndex = MessageHandler_TypeIndexFromKeyword((int)(intptr_t)aUndefmessageHa);
    if ( typeIndex == 4 )
      return 0;
  }
  else
  {
    typeIndex = -1;
  }
  if ( theClass )
    return MessageHandler_RemoveByNameAndType(theClass, (int)(intptr_t)handlerName, 1, typeIndex);
  v8 = Class_GetNextRecord(0);
  success = v9;
  classRecord = (_DWORD *)(uintptr_t)v8;
  if ( v8 )
  {
    do
    {
      if ( !MessageHandler_RemoveByNameAndType(classRecord, (int)(intptr_t)handlerName, 0, typeIndex) )
        success = 0;
      classRecord = (_DWORD *)(uintptr_t)Class_GetNextRecord((int)(intptr_t)classRecord);
    }
    while ( classRecord );
  }
  return success;
}
// 4CD913: variable 'v6' is possibly undefined
// 4CD92A: variable 'v9' is possibly undefined

//----- (004CD9A0) --------------------------------------------------------
BOOL  MessageHandler_WatchCommand(int watchFlag, int arguments, double a3)
{
  if ( watchFlag )
    return MessageHandler_DispatchWatchCommand((int)(intptr_t)aWatch_2, 0, 0, watchFlag, a3, (void (*)(void))MessageHandler_SetWatchFlagField, arguments);
  else
    return MessageHandler_DispatchWatchCommand((int)(intptr_t)aUnwatch_1, 0, 0, 0, a3, (void (*)(void))MessageHandler_SetWatchFlagField, arguments);
}
// 4CD1C0: using guessed type int sub_4CD1C0();

//----- (004CD9D0) --------------------------------------------------------
BOOL  MessageHandler_ListWatchItemsCommand(int logicalName, int arguments, double a3)
{
  return MessageHandler_DispatchWatchCommand((int)(intptr_t)aListWatchIte_2, logicalName, (void (*)(void))MessageHandler_PrintWatchStatusLine, -1, a3, 0, arguments);
}

//----- (004CD9F0) --------------------------------------------------------
BOOL  MessageHandler_DispatchWatchCommand(
        int commandName,
        int logicalName,
        void (*printFunction)(void),
        int a4,
        double a5,
        void (*actionFunction)(void),
        int arguments)
{
  int currentArg; // esi
  BOOL result; // eax
  int classRecord; // esi
  int Name; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int nextArg; // ebx
  signed int typeIndex; // eax
  __int16 *v17; // eax
  int v18; // ebx
  int v19; // ecx
  _DWORD v20[6]; // [esp+0h] [ebp-40h] BYREF
  /* stack alias of v20[1] */
  /* stack alias of v20[2]: the DATA_OBJECT value slot */
  int v23; // [esp+18h] [ebp-28h]
  int *theClass; // [esp+1Ch] [ebp-24h]
  int handlerName; // [esp+20h] [ebp-20h]
  int Enum; // [esp+24h] [ebp-1Ch]
  int argIndex; // [esp+28h] [ebp-18h]
  void (*v28)(void); // [esp+2Ch] [ebp-14h]
  int v29; // [esp+30h] [ebp-10h]

  currentArg = arguments;
  v23 = commandName;
  v29 = a4;
  v28 = printFunction;
  argIndex = 2;
  if ( arguments )
  {
    while ( 1 )
    {
      if ( !currentArg )
        return 1;
      if ( Parser_ParseForm((__int16 *)(uintptr_t)currentArg, v20, (int)(intptr_t)printFunction, a5) )
        return 0;
      if ( v20[1] != 2 || (theClass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v20[2] + 16))) == 0 )
      {
        Parser_ReportError(argIndex, (int)(intptr_t)aClassName);
        return 0;
      }
      nextArg = *(_DWORD *)(uintptr_t)(currentArg + 10);
      if ( nextArg )
      {
        v17 = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentArg + 10);
        ++argIndex;
        currentArg = nextArg;
        if ( Parser_ParseForm(v17, v20, v14, a5) )
          return 0;
        if ( v20[1] != 2 )
        {
          Parser_ReportError(argIndex, (int)(intptr_t)aHandlerName);
          return 0;
        }
        v18 = *(_DWORD *)(uintptr_t)(nextArg + 10);
        handlerName = *(_DWORD *)(uintptr_t)(v20[2] + 16);
        if ( v18 )
        {
          currentArg = *(_DWORD *)(uintptr_t)(currentArg + 10);
          ++argIndex;
          if ( Parser_ParseForm((__int16 *)(uintptr_t)currentArg, v20, 2, a5) )
            return 0;
          if ( v19 != (int)v20[1] )
          {
            Parser_ReportError(argIndex, (int)(intptr_t)aHandlerType);
            return 0;
          }
          typeIndex = MessageHandler_TypeIndexFromKeyword(v23);
          if ( typeIndex == 4 )
            return 0;
        }
        else
        {
          typeIndex = -1;
        }
      }
      else
      {
        typeIndex = -1;
        handlerName = 0;
      }
      if ( !MessageHandler_ForEachMatchingHandler((int)(intptr_t)theClass, handlerName, logicalName, typeIndex, v29, 0, v28, actionFunction) )
        break;
      currentArg = *(_DWORD *)(uintptr_t)(currentArg + 10);
      ++argIndex;
    }
    Parser_ReportError(argIndex, (int)(intptr_t)aHandler_0);
    return 0;
  }
  else
  {
    Module_BeginEnum();
    Enum = Module_NextEnum(0);
    if ( Enum )
    {
      while ( 1 )
      {
        Module_SetCurrent(Enum);
        if ( !actionFunction )
        {
          Name = Module_GetName(Enum);
          Output_Write(logicalName, Name, v12);
          Output_Write(logicalName, (int)(intptr_t)asc_50C164, v13);
        }
        classRecord = Class_GetNextRecord(0);
        if ( classRecord )
          break;
LABEL_11:
        Enum = Module_NextEnum(Enum);
        if ( !Enum )
          goto LABEL_12;
      }
      while ( 1 )
      {
        result = MessageHandler_ForEachMatchingHandler(classRecord, 0, logicalName, -1, v29, 1, v28, actionFunction);
        if ( !result )
          break;
        classRecord = Class_GetNextRecord(classRecord);
        if ( !classRecord )
          goto LABEL_11;
      }
    }
    else
    {
LABEL_12:
      Module_EndEnum();
      return 1;
    }
  }
  return result;
}
// 4CDABB: variable 'v12' is possibly undefined
// 4CDAC7: variable 'v13' is possibly undefined
// 4CDAD2: variable 'a3' is possibly undefined
// 4CDB74: variable 'v14' is possibly undefined
// 4CDBDC: variable 'v19' is possibly undefined

//----- (004CDC40) --------------------------------------------------------
BOOL  MessageHandler_ForEachMatchingHandler(
        int theClass,
        int handlerName,
        int logicalName,
        int typeIndex,
        int a5 CLASH95_UNUSED,
        int printHeader,
        void (*printFunction)(void),
        void (*actionFunction)(void))
{
  int found; // ebx
  int i; // ecx

  found = 0;
  for ( i = MessageHandler_EnumNext(theClass, 0); i; i = MessageHandler_EnumNext(theClass, i) )
  {
    if ( (typeIndex == -1 || *(_DWORD *)(uintptr_t)(36 * (i - 1) + *(_DWORD *)(uintptr_t)(theClass + 88)) << 29 >> 30 == typeIndex)
      && (!handlerName || !strcmp_(i, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(36 * (i - 1) + *(_DWORD *)(uintptr_t)(theClass + 88) + 8) + 16))) )
    {
      if ( actionFunction )
      {
        actionFunction();
      }
      else
      {
        if ( printHeader )
          Output_Write(logicalName, (int)(intptr_t)asc_50C19C, i);
        printFunction();
      }
      found = 1;
    }
  }
  return !handlerName || typeIndex == -1 || found;
}
// 4CDC8C: variable 'i' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004CDD40) --------------------------------------------------------
signed int  MessageHandler_PrintWatchStatusLine(int theClass, int handlerIndex)
{
  int className; // eax
  int v4; // ecx
  int v5; // ecx
  int handlerOffset; // ebx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx

  className = Rules_GetConstructNameString(theClass);
  Output_Write(v4, className, v4);
  Output_Write(v5, (int)(intptr_t)asc_50C030, v5);
  handlerOffset = 36 * (handlerIndex - 1);
  Output_Write(v7, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(theClass + 88) + 8) + 16), v7);
  Output_Write(v8, (int)(intptr_t)asc_50C030, v8);
  Output_Write(v9, (int)(intptr_t)g_MessageHandlerTypeNames[*(_DWORD *)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(theClass + 88)) << 29 >> 30], v9);
  if ( (*(_DWORD *)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(theClass + 88)) & 0x10) != 0 )
    return Output_Write(v10, (int)(intptr_t)aOn_4, v10);
  else
    return Output_Write(v10, (int)(intptr_t)aOff_4, v10);
}
// 4CDD51: variable 'v4' is possibly undefined
// 4CDD5D: variable 'v5' is possibly undefined
// 4CDD81: variable 'v7' is possibly undefined
// 4CDD8D: variable 'v8' is possibly undefined
// 4CDDA7: variable 'v9' is possibly undefined
// 4CDDC3: variable 'v10' is possibly undefined
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004CDDE0) --------------------------------------------------------
int Definstances_SetupConstruct(void)
{
  int v0; // ecx
  int v1; // ecx

  g_Clips_DefinstancesModuleItemIndex = Module_RegisterItem(
                   (int)(intptr_t)aDefinstances,
                   (int)(intptr_t)Definstances_AllocModuleData,
                   (int)(intptr_t)Rules_DefinstancesBloadModuleReference,
                   (int)(intptr_t)Definstances_FreeModuleData,
                   (int)(intptr_t)Rules_WriteDefinstancesModuleReference,
                   (int)(intptr_t)Definstances_FindByName);
  g_ClipsDefinstancesConstructType = (int)(intptr_t)Rules_RegisterConstructType(
                        (int)(intptr_t)aDefinstances,
                        (int)(intptr_t)aDefinstances,
                        (int)(intptr_t)Definstances_FindByName,
                        (int)(intptr_t)Definstances_ParseAndCreate,
                        (int)(intptr_t)Rules_GetConstructNameSymbol,
                        (int)(intptr_t)Rules_GetModuleConstructListHead,
                        (int)(intptr_t)Rules_GetConstructOwnerModule,
                        (int)(intptr_t)Definstances_GetNextRecord,
                        (int)(intptr_t)Rules_SetConstructNextInModule,
                        (int)(intptr_t)Definstances_IsDeletable,
                        (int)(intptr_t)Definstances_DeleteRecord,
                        (int)(intptr_t)Definstances_FreeRecord);
  Rules_AddClearReadyFunction((int)(intptr_t)aDefinstances, (int)(intptr_t)Definstances_IsClearReady, 0);
  Rules_RegisterHostFunction(aUndefinstanc_0, 118, v0, (int)(intptr_t)Definstances_UndefineCommand, (int)(intptr_t)a11w_13);
  Rules_AddSaveFunction((int)(intptr_t)aDefinstances, (int)(intptr_t)Definstances_SaveConstruct, 0);
  Rules_AddClearFunction((int)(intptr_t)aDefinstances, (int)(intptr_t)Definstances_CreateDefaultRecord, -1000);
  Rules_RegisterHostFunction(aPpdefinstanc_0, 118, v1, (int)(intptr_t)Definstances_PrettyPrintCommand, (int)(intptr_t)a11w_13);
  Rules_RegisterHostFunction(aListDefinstanc, 118, (int)(intptr_t)aListdefinstanc, (int)(intptr_t)Definstances_ListCommand, (int)(intptr_t)a01_2);
  Rules_RegisterHostFunction(aGetDefinstance, 109, (int)(intptr_t)aGetdefinstance, (int)(intptr_t)Definstances_GetListCommand, (int)(intptr_t)a01_2);
  Rules_RegisterHostFunction(aDefinstancesMo, 119, (int)(intptr_t)aGetdefinstan_0, (int)(intptr_t)Definstances_GetModuleCommand, (int)(intptr_t)a11w_13);
  Rules_AddResetFunction((int)(intptr_t)aDefinstances, (int)(intptr_t)Definstances_ResetAll, 0);
  Rules_SetupDefinstancesBsaveBload();
  return Rules_RegisterDefinstancesCodeGenerator();
}
// 4CDE78: variable 'v0' is possibly undefined
// 4CDEBB: variable 'v1' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDF40) --------------------------------------------------------
int  Definstances_GetNextRecord(int previousRecord)
{
  return Class_Enum(previousRecord, g_Clips_DefinstancesModuleItemIndex);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CDF50) --------------------------------------------------------
int  Definstances_FindByName(_BYTE *constructName, int a2 CLASH95_UNUSED)
{
  return Rules_FindConstructByNameGeneric(constructName, g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDF60) --------------------------------------------------------
BOOL Definstances_IsDeletable(void)
{
  int theDefinstances; // edx

  return !Rules_IsBloaded() && *(_DWORD *)(uintptr_t)(theDefinstances + 20) == 0;
}
// 4CDF70: variable 'v0' is possibly undefined

//----- (004CDF80) --------------------------------------------------------
int __thiscall Definstances_UndefineCommand(void *this_)
{
  return Rules_UndefconstructCommand((int)(intptr_t)this_, g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDFA0) --------------------------------------------------------
int __thiscall Definstances_GetModuleCommand(void *this_)
{
  return Rules_GetConstructModuleCommand((int)(intptr_t)this_, (const char **)(uintptr_t)g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CDFC0) --------------------------------------------------------
signed int Definstances_DeleteRecord(void)
{
  int v0; // edx
  signed int result; // eax
  int theRecord; // edx

  if ( Rules_IsBloaded() )
    return 0;
  if ( !v0 )
    return Definstances_RemoveAll();
  result = Definstances_IsDeletable();
  if ( result )
  {
    Rules_UnlinkListNode(theRecord);
    Definstances_FreeRecord(theRecord);
    return 1;
  }
  return result;
}
// 4CDFCE: variable 'v0' is possibly undefined
// 4CDFEA: variable 'v2' is possibly undefined

//----- (004CE000) --------------------------------------------------------
int __thiscall Definstances_PrettyPrintCommand(void *this_)
{
  return Rules_PPConstructCommand((int)(intptr_t)this_, (const char **)(uintptr_t)g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE020) --------------------------------------------------------
int  Definstances_ListCommand(int logicalName, double a2)
{
  return Rules_ListConstructsCommand(g_ClipsDefinstancesConstructType, logicalName, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE060) --------------------------------------------------------
_DWORD * Definstances_GetListCommand(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_ClipsDefinstancesConstructType, a2);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE0A0) --------------------------------------------------------
signed int  Definstances_ParseAndCreate(int readSource)
{
  int lastNode; // edi
  int constructName; // ebx
  _DWORD *v4; // edx
  _DWORD *v5; // ecx
  char *makeInstanceName; // eax
  int **Symbol; // ebx
  int v8; // ecx
  int v9; // eax
  int instanceNode; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  char *ppForm; // eax
  _DWORD *packedActions; // eax
  int v16; // edx
  int v17; // ecx
  int v18; // edx
  int nameSymbol; // eax
  int v20; // edx
  int v21; // edx
  int v23; // ecx
  int activeFlag; // [esp+0h] [ebp-20h] BYREF
  _DWORD *newRecord; // [esp+4h] [ebp-1Ch]

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  lastNode = 0;
  IO_OutWriteToken(aDefinstances_2);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  constructName = Definstances_ParseHeaderAndActiveFlag(readSource, (_DWORD*)(&activeFlag));
  if ( !constructName )
    return 1;
  v4 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
  if ( v4 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = *v4;
  }
  else
  {
    Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  Rules_InitConstructModuleRecord((int)(intptr_t)aDefinstances, constructName);
  v5[5] = 0;
  v5[6] = 0;
  newRecord = v5;
  if ( activeFlag )
    makeInstanceName = aActiveMakeIn_1;
  else
    makeInstanceName = aMakeInstance_2;
  Symbol = Rules_MakeSymbol((_BYTE*)(makeInstanceName));
  if ( g_ParserCurrentTokenType == 100 )
  {
    while ( 1 )
    {
      AST_NewNode(103, (int)(intptr_t)Symbol);
      v9 = Rules_ParseObjectInstanceFunctionCall(v8, readSource);
      instanceNode = v9;
      if ( !v9 )
      {
        AST_Free(newRecord[6]);
        g_ClipsMemFreeListTemp = (int)(intptr_t)newRecord;
        *newRecord = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
        *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
        return 1;
      }
      if ( AST_TreeContainsSpecialTag(v9, 0) == 1 )
        break;
      if ( lastNode )
        *(_DWORD *)(uintptr_t)(lastNode + 10) = v11;
      else
        newRecord[6] = v11;
      Parser_NextToken(readSource, (int)(intptr_t)&g_ParserCurrentTokenType);
      IO_OutNewline();
      AST_Append(v13, v12);
      IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
      lastNode = instanceNode;
      if ( g_ParserCurrentTokenType != 100 )
        goto LABEL_13;
    }
    Rules_ReportLocalVariableError();
    AST_Free(v23);
    AST_Free(newRecord[6]);
    g_ClipsMemFreeListTemp = (int)(intptr_t)newRecord;
    *newRecord = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
    return 1;
  }
  else
  {
LABEL_13:
    if ( g_ParserCurrentTokenType == 101 )
    {
      if ( !Mem_GetAllocFlag() )
      {
        if ( newRecord[6] )
          IO_OutNewline();
        IO_OutNewline();
        IO_OutWriteToken(asc_50C2E4);
        ppForm = Rules_CopyPPBuffer();
        Rules_ReplaceConstructPPForm((signed int)(intptr_t)newRecord, (int)(intptr_t)ppForm);
      }
      packedActions = AST_PackNodeChain((_DWORD *)(uintptr_t)newRecord[6]);
      *(_DWORD *)(uintptr_t)(v16 + 24) = (_DWORD)(uintptr_t)(packedActions);
      AST_Free(v17);
      nameSymbol = Rules_GetConstructNameSymbol(v18);
      ++*(_DWORD *)(uintptr_t)(nameSymbol + 4);
      AST_InstallNodeChain((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v20 + 24));
      Rules_AppendConstructToModuleList(v21);
      return 0;
    }
    else
    {
      AST_Free(newRecord[6]);
      g_ClipsMemFreeListTemp = (int)(intptr_t)newRecord;
      *newRecord = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
      Parser_ReportSyntaxError();
      return 1;
    }
  }
}
// 4CE118: variable 'v5' is possibly undefined
// 4CE159: variable 'v8' is possibly undefined
// 4CE186: variable 'v11' is possibly undefined
// 4CE19A: variable 'v13' is possibly undefined
// 4CE19A: variable 'v12' is possibly undefined
// 4CE20B: variable 'v16' is possibly undefined
// 4CE210: variable 'v17' is possibly undefined
// 4CE217: variable 'v18' is possibly undefined
// 4CE21F: variable 'v20' is possibly undefined
// 4CE229: variable 'v21' is possibly undefined
// 4CE2BF: variable 'v23' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E904: using guessed type int dword_54E904;

//----- (004CE360) --------------------------------------------------------
int  Definstances_ParseHeaderAndActiveFlag(int readSource, _DWORD *activeFlag)
{
  int result; // eax
  int constructName; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  int v11; // edx

  *activeFlag = 0;
  result = Rules_GetConstructNameAndComment(
             readSource,
             (int)(intptr_t)&g_ParserCurrentTokenType,
             (int (*)(void))Definstances_FindByName,
             aDefinstances,
             (int (*)(void))Definstances_DeleteRecord,
             aDefinstancesConstructMarker,
             1,
             0,
             1);
  constructName = result;
  if ( result )
  {
    if ( g_ParserCurrentTokenType == 2 && !strcmp_(result, (_DWORD)(uintptr_t)(aActive)) )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50C2F4);
      IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
      AST_Append(v10, v9);
      Parser_NextToken(readSource, v11);
      *activeFlag = 1;
    }
    if ( g_ParserCurrentTokenType == 3 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50C2F4);
      IO_OutWriteToken((char *)(uintptr_t)g_ClipsScanTokenPrintForm);
      AST_Append(v7, v6);
      Parser_NextToken(readSource, v8);
    }
    return constructName;
  }
  return result;
}
// 4CE3CD: variable 'v7' is possibly undefined
// 4CE3CD: variable 'v6' is possibly undefined
// 4CE3D4: variable 'v8' is possibly undefined
// 4CE3D9: variable 'v5' is possibly undefined
// 4CE421: variable 'v10' is possibly undefined
// 4CE421: variable 'v9' is possibly undefined
// 4CE428: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;
// 54E904: using guessed type int dword_54E904;

//----- (004CE440) --------------------------------------------------------
int  Definstances_FreeRecord(int theDefinstances)
{
  int nameSymbol; // eax
  int rhs; // eax
  int result; // eax

  nameSymbol = Rules_GetConstructNameSymbol(theDefinstances);
  Rules_DecrementSymbolCount(nameSymbol, theDefinstances);
  rhs = *(_DWORD *)(uintptr_t)(theDefinstances + 24);
  AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)rhs);
  AST_FreePackedNodeChain(rhs);
  Rules_ReplaceConstructPPForm(theDefinstances, 0);
  g_ClipsMemFreeListTemp = theDefinstances;
  *(_DWORD *)(uintptr_t)theDefinstances = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CE490) --------------------------------------------------------
int  Definstances_SaveConstruct(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_ClipsDefinstancesConstructType);
}
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE4A0) --------------------------------------------------------
signed int Definstances_RemoveAll(void)
{
  int allDeleted; // esi
  int currentRecord; // ebx
  int theRecord; // ecx
  int v4; // ecx
  int constructName; // eax
  int v6; // ecx

  allDeleted = 1;
  if ( Rules_IsBloaded() )
    return 0;
  currentRecord = Class_Enum(0, g_Clips_DefinstancesModuleItemIndex);
  if ( !currentRecord )
    return allDeleted;
  do
  {
    while ( 1 )
    {
      currentRecord = Class_Enum(currentRecord, g_Clips_DefinstancesModuleItemIndex);
      if ( !Definstances_IsDeletable() )
        break;
      Rules_UnlinkListNode(theRecord);
      Definstances_FreeRecord(v4);
      if ( !currentRecord )
        return allDeleted;
    }
    constructName = Rules_GetConstructNameString(theRecord);
    Definstances_ReportCannotDelete(constructName, v6);
    allDeleted = 0;
  }
  while ( currentRecord );
  return 0;
}
// 4CE4E5: variable 'v3' is possibly undefined
// 4CE4EC: variable 'v4' is possibly undefined
// 4CE503: variable 'v6' is possibly undefined
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE520) --------------------------------------------------------
signed int  Definstances_ReportCannotDelete(int constructName, int a2)
{
  return Rules_ReportCantDeleteItem(a2, constructName);
}

//----- (004CE530) --------------------------------------------------------
int Definstances_CreateDefaultRecord(void)
{
  int free_record; // edx
  int definstances_record; // ecx
  int **make_instance_symbol; // eax
  int make_instance_node; // ebx
  int initial_object_node; // eax
  int *initial_object_class; // eax
  _DWORD *rhs_copy; // eax
  int owner_symbol; // eax

  free_record = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112);
  if ( free_record )
  {
    g_ClipsMemFreeListTemp = free_record;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 112) = *(_DWORD *)(uintptr_t)free_record;
    definstances_record = g_ClipsMemFreeListTemp;
  }
  else
  {
    definstances_record = Mem_HeapAllocWithRetry((_DWORD *)0x1C);
  }
  sub_4A94D0_Impl((int)(intptr_t)aDefinstances, definstances_record, g_Rules_InitialObjectSymbol);
  *(_DWORD *)(uintptr_t)(definstances_record + 20) = 0;
  make_instance_symbol = Rules_MakeSymbol((_BYTE*)(aMakeInstance_2));
  make_instance_node = AST_NewNode(10, (int)(intptr_t)make_instance_symbol);
  initial_object_node = AST_NewNode(8, g_Rules_InitialObjectSymbol);
  *(_DWORD *)(uintptr_t)(make_instance_node + 6) = initial_object_node;
  initial_object_class = Class_LookupInScope((_BYTE*)(aInitialObjec_1));
  *(_DWORD *)(uintptr_t)(initial_object_node + 10) = AST_NewNode(57, (int)(intptr_t)initial_object_class);
  rhs_copy = AST_PackNodeChain((_DWORD *)(uintptr_t)make_instance_node);
  *(_DWORD *)(uintptr_t)(definstances_record + 24) = (_DWORD)(uintptr_t)(rhs_copy);
  AST_Free(make_instance_node);
  owner_symbol = Rules_GetConstructNameSymbol(definstances_record);
  ++*(_DWORD *)(uintptr_t)(owner_symbol + 4);
  AST_InstallNodeChain((__int16 *)rhs_copy);
  return Rules_AppendConstructToModuleList(definstances_record);
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6F4: using guessed type int dword_54E6F4;

//----- (004CE600) --------------------------------------------------------
signed int Definstances_AllocModuleData(void)
{
  _DWORD *freeListHead; // edx

  freeListHead = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CE630) --------------------------------------------------------
int  Definstances_FreeModuleData(int moduleData)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(moduleData, g_ClipsDefinstancesConstructType, moduleData);
  freed_node = (_DWORD *)(uintptr_t)moduleData;
  g_ClipsMemFreeListTemp = moduleData;
  *freed_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8F4: using guessed type int dword_54E8F4;

//----- (004CE670) --------------------------------------------------------
__int64 __fastcall Definstances_IsClearReady(int a1 CLASH95_UNUSED, int a2)
{
  __int64 clearReadyResult; // [esp+0h] [ebp-10h]

  HIDWORD(clearReadyResult) = a2;
  LODWORD(clearReadyResult) = 1;
  sub_4A9430_Impl((int (*)(int, intptr_t))Definstances_CheckRecordBusy, g_Clips_DefinstancesModuleItemIndex, (intptr_t)&clearReadyResult, 0);
  return clearReadyResult;
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE6A0) --------------------------------------------------------
int  Definstances_CheckRecordBusy(int result, _DWORD *clearReadyFlag)
{
  if ( *(_DWORD *)(uintptr_t)(result + 20) )
    *clearReadyFlag = 0;
  return result;
}

//----- (004CE6B0) --------------------------------------------------------
signed int Definstances_ResetAll(void)
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))Definstances_ExecuteRecordActions, g_Clips_DefinstancesModuleItemIndex, 0, 1);
}
// 54E8F0: using guessed type int dword_54E8F0;

//----- (004CE6D0) --------------------------------------------------------
int  Definstances_ExecuteRecordActions(int theDefinstances, int a2, double a3)
{
  int record; // ecx
  __int16 *expression; // ecx
  int result; // eax
  _DWORD v9[6]; // [esp+0h] [ebp-18h] BYREF

  (void)a2;
  record = theDefinstances;
  Module_BeginEnum();
  Module_SetCurrent(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(record + 8)));
  ++*(_DWORD *)(uintptr_t)(record + 20);
  expression = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(record + 24);
  if ( expression )
  {
    while ( 1 )
    {
      Parser_ParseForm(expression, v9, (int)(uintptr_t)expression, a3);
      if ( g_ClipsHaltExecution || v9[1] == 2 && v9[2] == g_ClipsFalseSymbol )
        break;
      expression = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)(uintptr_t)expression + 10);
      if ( !expression )
        goto LABEL_6;
    }
    result = Module_EndEnum();
    --*(_DWORD *)(uintptr_t)(record + 20);
  }
  else
  {
LABEL_6:
    --*(_DWORD *)(uintptr_t)(record + 20);
    return Module_EndEnum();
  }
  return result;
}
// 51A968: using guessed type int dword_51A968;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CE740) --------------------------------------------------------
signed int __thiscall InstanceQuery_SetupFunctions(void *this_)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx

  g_InternedSym_Qds = (int)(intptr_t)Str_Intern(aQds, (int)(intptr_t)this_);
  ++*(_DWORD *)(uintptr_t)(g_InternedSym_Qds + 4);
  Rules_RegisterHostFunction(aQueryInstance, 111, (int)(intptr_t)aGetqueryinstan, (int)(intptr_t)InstanceQuery_GetQueryInstance, 0);
  Rules_RegisterHostFunction(aQueryInstanceS, 117, (int)(intptr_t)aGetqueryinst_0, (int)(intptr_t)InstanceQuery_ResolveBoundSlotValue, 0);
  Rules_RegisterHostFunction(aAnyInstancep, 98, (int)(intptr_t)aAnyinstances, (int)(intptr_t)InstanceQuery_AnyInstancep, 0);
  Rules_AddFunctionParser((_BYTE*)(aAnyInstancep));
  Rules_RegisterHostFunction(aFindInstance, 109, v1, (int)(intptr_t)InstanceQuery_FindInstance, 0);
  Rules_AddFunctionParser((_BYTE*)(aFindInstance));
  Rules_RegisterHostFunction(aFindAllInstanc, 109, v2, (int)(intptr_t)InstanceQuery_FindAllInstances, 0);
  Rules_AddFunctionParser((_BYTE*)(aFindAllInstanc));
  Rules_RegisterHostFunction(aDoForInstance, 117, v3, (int)(intptr_t)InstanceQuery_DoForInstance, 0);
  Rules_AddFunctionParser((_BYTE*)(aDoForInstance));
  Rules_RegisterHostFunction(aDoForAllInstan, 117, v4, (int)(intptr_t)InstanceQuery_DoForAllInstances, 0);
  Rules_AddFunctionParser((_BYTE*)(aDoForAllInstan));
  Rules_RegisterHostFunction(aDelayedDoForAl, 117, v5, (int)(intptr_t)InstanceQuery_DelayedDoForAllInstances, 0);
  return Rules_AddFunctionParser((_BYTE*)(aDelayedDoForAl));
}
// 4CE7CF: variable 'v1' is possibly undefined
// 4CE7F9: variable 'v2' is possibly undefined
// 4CE823: variable 'v3' is possibly undefined
// 4CE84D: variable 'v4' is possibly undefined
// 4CE877: variable 'v5' is possibly undefined
// 51B454: using guessed type int dword_51B454;

//----- (004CE890) --------------------------------------------------------
signed int *__thiscall InstanceQuery_GetQueryInstance(void *this_)
{
  _DWORD *queryFrame; // eax

  queryFrame = (_DWORD *)(uintptr_t)InstanceQuery_GetQueryFrameAtDepth(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2) + 16));
  return Instance_GetQualifiedName(
           *(_DWORD *)(uintptr_t)(*queryFrame + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10) + 2) + 16)),
           (int)(intptr_t)this_);
}
// 51A960: using guessed type int dword_51A960;

//----- (004CE8D0) --------------------------------------------------------
int  InstanceQuery_ResolveBoundSlotValue(int returnValue, int a2, double a3)
{
  _DWORD *queryFrame; // eax
  int v5; // edx
  int theInstance; // ebx
  int result; // eax
  _DWORD *v8; // ecx
  _DWORD slotNameValue[9]; // [esp-4h] [ebp-24h] BYREF

  slotNameValue[7] = a2;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  queryFrame = (_DWORD *)(uintptr_t)InstanceQuery_GetQueryFrameAtDepth(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 2) + 16));
  v5 = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10);
  theInstance = *(_DWORD *)(uintptr_t)(*queryFrame + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v5 + 2) + 16));
  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(v5 + 10), slotNameValue, returnValue, a3);
  if ( slotNameValue[1] == 2 )
  {
    result = Instance_GetSlotValueBySymbol(theInstance, slotNameValue[2]);
    if ( result )
    {
      v8[1] = *(_DWORD *)(uintptr_t)(result + 4) << 24 >> 26;
      v8[2] = *(_DWORD *)(uintptr_t)(result + 8);
      if ( (*(_DWORD *)(uintptr_t)(result + 4) & 0xFC) == 0x10 )
      {
        v8[3] = 0;
        result = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(result + 8) + 6) - 1;
        v8[4] = result;
      }
    }
    else
    {
      return Instance_ReportNoSuchSlotError((int)(intptr_t)v8, (int)(intptr_t)aInstanceSetQ_0);
    }
  }
  else
  {
    Parser_ReportError(1, (int)(intptr_t)aSymbol_6);
    return Lexer_ErrorRecover(1);
  }
  return result;
}
// 4CE93A: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004CE9B0) --------------------------------------------------------
int * InstanceQuery_AnyInstancep(int returnValue, double a2)
{
  int *result; // eax
  _DWORD *v3; // edx
  _DWORD *v4; // eax
  int *v5; // ecx
  signed int testResult; // ebx
  int *v7; // ecx
  _DWORD varCount[4]; // [esp+0h] [ebp-10h] BYREF

  varCount[2] = returnValue;
  result = InstanceQuery_ParseRestrictions(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10), (int)(intptr_t)aAnyInstancep, varCount, a2);
  if ( result )
  {
    InstanceQuery_PushQueryFrame();
    v3 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    if ( v3 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *v3;
      v4 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      v4 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)(intptr_t)v4;
    *v4 = (_DWORD)(uintptr_t)(Mem_SmallBlockAlloc(4 * varCount[0]));
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4) = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    testResult = InstanceQuery_TestClassRestriction(v5, 0, a2);
    g_InstanceQuery_AbortFlag = 0;
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)(uintptr_t)g_ClipsQueryCore = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    InstanceQuery_FreeRestrictionClassList(v7);
    return (int *)(uintptr_t)testResult;
  }
  return result;
}
// 4CEA31: variable 'v5' is possibly undefined
// 4CEA8A: variable 'v7' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004CEAC0) --------------------------------------------------------
int * InstanceQuery_FindInstance(_DWORD *returnValue, double a2)
{
  int *restrictionList; // ebp
  _DWORD *v4; // edx
  _DWORD *v5; // eax
  int instanceIndex; // ecx
  int coreOffset; // ebx
  int v8; // edx
  signed int *instanceName; // eax
  int v10; // edx
  int v11; // ecx
  int *result; // eax
  signed int varCount[5]; // [esp+0h] [ebp-14h] BYREF

  returnValue[1] = 4;
  returnValue[3] = 0;
  returnValue[4] = -1;
  restrictionList = InstanceQuery_ParseRestrictions(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6) + 10), (int)(intptr_t)aFindInstance, (_DWORD*)(varCount), a2);
  if ( restrictionList )
  {
    InstanceQuery_PushQueryFrame();
    v4 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    if ( v4 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = *v4;
      v5 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      v5 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    g_ClipsQueryCore = (int)(intptr_t)v5;
    *v5 = (_DWORD)(uintptr_t)(Mem_SmallBlockAlloc(4 * varCount[0]));
    *(_DWORD *)(uintptr_t)(g_ClipsQueryCore + 4) = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
    if ( InstanceQuery_TestClassRestriction(restrictionList, 0, a2) == 1 )
    {
      returnValue[2] = (_DWORD)(uintptr_t)(Rules_CreateEphemeralMultifield(varCount[0]));
      returnValue[4] = varCount[0] - 1;
      instanceIndex = 1;
      if ( varCount[0] >= 1 )
      {
        coreOffset = 4;
        v8 = 0;
        do
        {
          *(_WORD *)(uintptr_t)(v8 + returnValue[2] + 14) = 8;
          instanceName = Instance_GetQualifiedName(*(_DWORD *)(uintptr_t)(coreOffset + *(_DWORD *)(uintptr_t)g_ClipsQueryCore - 4), instanceIndex);
          coreOffset += 4;
          *(_DWORD *)(uintptr_t)(v10 + returnValue[2] + 16) = (_DWORD)(uintptr_t)(instanceName);
          instanceIndex = v11 + 1;
          v8 = v10 + 6;
        }
        while ( instanceIndex <= varCount[0] );
      }
    }
    else
    {
      returnValue[2] = (_DWORD)(uintptr_t)(Rules_CreateEphemeralMultifield(0));
    }
    g_InstanceQuery_AbortFlag = 0;
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsQueryCore, 4 * varCount[0]);
    g_ClipsMemFreeListTemp = g_ClipsQueryCore;
    *(_DWORD *)(uintptr_t)g_ClipsQueryCore = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
    InstanceQuery_PopQueryFrame();
    return InstanceQuery_FreeRestrictionClassList(restrictionList);
  }
  else
  {
    result = (int*)(Rules_CreateEphemeralMultifield(0));
    returnValue[2] = (_DWORD)(uintptr_t)(result);
  }
  return result;
}
// 4CEBA9: variable 'v10' is possibly undefined
// 4CEBAD: variable 'v11' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51B458: using guessed type int dword_51B458;
// 51B460: using guessed type int dword_51B460;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
