/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../clips/clips_api.h"
#include "../state/state_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0047F820) --------------------------------------------------------
int Rules_GetCurrentFocus(void)
{
  if ( g_Rules_FocusStackTop )
    return *(_DWORD *)(uintptr_t)g_Rules_FocusStackTop;
  else
    return 0;
}
// 51A200: using guessed type int dword_51A200;

//----- (0047F840) --------------------------------------------------------
signed int  Rules_FocusCommand(int a1, double a2)
{
  int v2; // eax
  int argCount; // esi
  signed int result; // eax
  int *module; // eax
  int v6; // edx
  int v7; // ecx
  _DWORD v8[10]; // [esp-8h] [ebp-28h] BYREF

  v8[8] = a1;
  v2 = Lexer_TokenExpect((int)(intptr_t)aFocus_1, 1, 1);
  if ( v2 == -1 )
    return 0;
  argCount = v2;
  if ( v2 <= 0 )
    return 1;
  while ( 1 )
  {
    result = Lexer_ParseValueList(argCount, v8, 2, a2);
    if ( !result )
      break;
    module = Module_FindByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v8[2] + 16));
    if ( !module )
    {
      Rules_ReportCantFindItem(v7, v6);
      return 0;
    }
    --argCount;
    Rules_PushFocus((int)(intptr_t)module);
    if ( argCount <= 0 )
      return 1;
  }
  return result;
}
// 47F8B4: variable 'v7' is possibly undefined
// 47F8B4: variable 'v6' is possibly undefined

//----- (0047F8F0) --------------------------------------------------------
signed int Rules_RegisterInstanceFunctions(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_EnsureObjectPatternVTable();
  Instance_InitHashTable();
  Rules_RegisterEvaluationHandler((int)(uintptr_t)g_Rules_ObjectPatternVTable, 7);
  Rules_RegisterHostFunction(aInitializeInst, 117, v0, (int)(intptr_t)Instance_InitializeInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveInitiali, 117, (int)(intptr_t)aInitializeinst, (int)(intptr_t)Instance_ActiveInitializeInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveInitiali);
  Rules_RegisterHostFunction(aMakeInstance, 117, v1, (int)(intptr_t)Instance_MakeInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveMakeInst, 117, (int)(intptr_t)aMakeinstanceco, (int)(intptr_t)Instance_ActiveMakeInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveMakeInst);
  Rules_AddFunctionParser(aInitializeInst);
  Rules_AddFunctionParser(aMakeInstance);
  Rules_RegisterHostFunction(aInitSlots, 117, v2, (int)(intptr_t)Instance_InitSlotsCommand, (int)(intptr_t)a00_3);
  Rules_RegisterHostFunction(aDeleteInstance, 98, (int)(intptr_t)aDeleteinstance, (int)(intptr_t)Rules_DeleteInstanceCommand, (int)(intptr_t)a00_3);
  Rules_RegisterHostFunction(aUnmakeInstance, 98, (int)(intptr_t)aUnmakeinstance, (int)(intptr_t)Rules_UnmakeInstanceCommand, (int)(intptr_t)a1E);
  Rules_RegisterHostFunction(aInstances, 118, (int)(intptr_t)aInstancescomma, (int)(intptr_t)Rules_InstancesCommand, (int)(intptr_t)a3w);
  Rules_RegisterHostFunction(aPpinstance, 118, (int)(intptr_t)aPpinstancecomm, (int)(intptr_t)Rules_PPInstanceCommand, (int)(intptr_t)a00_3);
  Rules_RegisterHostFunction(aSymbolToInstan, 117, (int)(intptr_t)aSymboltoinstan, (int)(intptr_t)Rules_SymbolToInstanceName, (int)(intptr_t)a11w_4);
  Rules_RegisterHostFunction(aInstanceNameTo, 119, (int)(intptr_t)aInstancenameto, (int)(intptr_t)Rules_InstanceNameToSymbol, (int)(intptr_t)a11p);
  Rules_RegisterHostFunction(aInstanceAddres, 117, (int)(intptr_t)aInstanceaddres, (int)(intptr_t)Rules_InstanceAddressCommand, (int)(intptr_t)a12eep);
  Rules_RegisterHostFunction(aInstanceAddr_0, 98, (int)(intptr_t)aInstanceaddr_0, (int)(intptr_t)Rules_InstanceAddressPCommand, (int)(intptr_t)a11_2);
  Rules_RegisterHostFunction(aInstanceNamep, 98, (int)(intptr_t)aInstancenamepc, (int)(intptr_t)Rules_InstanceNamePCommand, (int)(intptr_t)a11_2);
  Rules_RegisterHostFunction(aInstanceName, 117, (int)(intptr_t)aInstancenameco, (int)(intptr_t)Rules_InstanceNameCommand, (int)(intptr_t)a11e);
  Rules_RegisterHostFunction(aInstancep, 98, (int)(intptr_t)aInstancepcomma, (int)(intptr_t)Rules_InstancePCommand, (int)(intptr_t)a11_2);
  Rules_RegisterHostFunction(aInstanceExistp, 98, (int)(intptr_t)aInstanceexistp, (int)(intptr_t)Rules_InstanceExistPCommand, (int)(intptr_t)a11e);
  Rules_RegisterHostFunction(aClass, 117, (int)(intptr_t)aClasscommand_0, (int)(intptr_t)Rules_ClassCommand, (int)(intptr_t)a11_2);
  Instance_RegisterModifyAndDuplicateFunctions();
  Rules_RegisterInstanceIOCommands();
  Rules_RegisterMultifieldSlotCommands();
  Rules_AddPeriodicFunction((int)(intptr_t)aInstances, (int)(intptr_t)Instance_PurgeDeletedInstances, 0);
  return Rules_AddResetFunction((int)(intptr_t)aInstances, (int)(intptr_t)Instance_PrintClassInstanceSummary, 60);
}
// 47F91D: variable 'v0' is possibly undefined
// 47F962: variable 'v1' is possibly undefined
// 47F9C8: variable 'v2' is possibly undefined

//----- (0047FB90) --------------------------------------------------------
signed int  Rules_RetractFactById(int instance, double a2)
{
  int allDeleted; // ecx
  int currentInstance; // edx

  allDeleted = 1;
  if ( instance )
    return Instance_DeleteInstance(instance, a2);
  currentInstance = g_Clips_InstanceListHead;
  while ( currentInstance )
  {
    if ( !Instance_DeleteInstance(currentInstance, a2) )
      allDeleted = 0;
  }
  if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
    Rules_RunPeriodicCleanup(1, 0);
  return allDeleted;
}
// 47FBAA: variable 'v3' is possibly undefined
// 47FBDF: variable 'v2' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (0047FBF0) --------------------------------------------------------
BOOL  Rules_UnmakeInstance(int instance, double a2)
{
  BOOL allDeleted; // edi
  int savedPurgeFlag; // ebp
  int i; // esi

  allDeleted = 1;
  savedPurgeFlag = g_Instance_PurgeInProgress;
  g_Instance_PurgeInProgress = 1;
  if ( instance )
  {
    MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, instance, 0, 0, a2);
    allDeleted = (*(_BYTE *)(uintptr_t)(instance + 24) & 2) != 0;
  }
  else
  {
    i = g_Clips_InstanceListHead;
    while ( i )
    {
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, i, 0, 0, a2);
      if ( (*(_BYTE *)(uintptr_t)(i + 24) & 2) == 0 )
        allDeleted = 0;
      for ( i = *(_DWORD *)(uintptr_t)(i + 68); i; i = *(_DWORD *)(uintptr_t)(i + 68) )
      {
        if ( (*(_DWORD *)(uintptr_t)(i + 24) & 2) == 0 )
          break;
      }
    }
  }
  g_Instance_PurgeInProgress = savedPurgeFlag;
  Instance_PurgeDeletedInstances();
  if ( g_ClipsCurrentEvaluationDepth || g_ClipsCommandEvalInProgress || g_ClipsCurrentExpression )
    return allDeleted;
  Rules_RunPeriodicCleanup(1, 0);
  return allDeleted;
}
// 51A280: using guessed type int dword_51A280;
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD38: using guessed type int dword_51AD38;

//----- (0047FCB0) --------------------------------------------------------
void  Rules_InstancesCommand(double context)
{
  int includeInherited; // ebp
  _BYTE *className; // esi
  int moduleName; // ecx
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int keywordArg; // ecx
  int v9; // edx
  _DWORD temp[2]; // [esp+0h] [ebp-34h] BYREF
  int v11; // [esp+8h] [ebp-2Ch]
  int argCount; // [esp+18h] [ebp-1Ch]

  Module_GetCurrent();
  includeInherited = 0;
  className = 0;
  argCount = Rules_RtnArgCount();
  if ( argCount <= 0 )
    goto LABEL_16;
  if ( !Lexer_ParseValueList(1, temp, 2, context) )
    return;
  if ( !Module_FindByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v11 + 16)) && strcmp_(moduleName, asc_5033CC) )
  {
    Lexer_ErrorRecover(1);
    Parser_ReportError(v5, (int)(intptr_t)aDefmoduleName);
    return;
  }
  if ( argCount <= 1 )
    goto LABEL_16;
  if ( !Lexer_ParseValueList(2, temp, 2, context) )
    return;
  className = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v11 + 16);
  if ( !Class_LookupByModule(v4, className) )
  {
    if ( strcmp_(v6, asc_5033CC) )
    {
      Class_ReportLookupError(v7, (int)(intptr_t)className);
      return;
    }
    className = 0;
  }
  if ( argCount <= 2 )
  {
LABEL_16:
    Rules_PrintInstancesByModule((int)(intptr_t)g_IO_LogicalName_WDisplay, includeInherited, (int)(intptr_t)className);
    return;
  }
  if ( Lexer_ParseValueList(3, temp, 2, context) )
  {
    if ( strcmp_(keywordArg, aInherit) )
    {
      Lexer_ErrorRecover(1);
      Parser_ReportError(v9, (int)(intptr_t)aKeywordInherit);
      return;
    }
    includeInherited = 1;
    goto LABEL_16;
  }
}
// 47FD39: variable 'v3' is possibly undefined
// 47FD63: variable 'v5' is possibly undefined
// 47FD75: variable 'v4' is possibly undefined
// 47FD85: variable 'v6' is possibly undefined
// 47FDC1: variable 'v8' is possibly undefined
// 47FDF0: variable 'v7' is possibly undefined
// 47FE18: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A624: using guessed type char *off_51A624;

//----- (0047FE30) --------------------------------------------------------
signed int __thiscall Rules_PPInstanceCommand(void *this)
{
  signed int result; // eax
  int instance; // edx
  int v3; // ecx

  result = MessageHandler_CheckCurrentMessage((int)(intptr_t)this, 1);
  if ( result )
  {
    result = MessageHandler_GetNthArgument(0);
    instance = *(_DWORD *)(uintptr_t)(result + 8);
    if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) == 0 )
    {
      Rules_PrintInstanceSlots((int)(intptr_t)g_IO_LogicalName_WDisplay, instance, (int)(intptr_t)asc_5033FC);
      return Output_Write((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)asc_5033FC, v3);
    }
  }
  return result;
}
// 47FE70: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047FE80) --------------------------------------------------------
void  Rules_PrintInstancesByModule(int logicalName, int a2, int className)
{
  signed int traversalID; // esi
  int targetModule; // edx
  int i; // esi
  int Name; // eax
  int v8; // ecx
  int v9; // ecx
  signed int v10; // [esp+0h] [ebp-18h]
  int instanceCount; // [esp+8h] [ebp-10h]

  traversalID = Class_NewTraversalID();
  v10 = traversalID;
  instanceCount = 0;
  if ( traversalID != -1 )
  {
    Module_BeginEnum();
    if ( targetModule )
    {
      Module_SetCurrent(targetModule);
      instanceCount = Rules_ListInstancesForClassOrModule(traversalID, logicalName, className, v9);
    }
    else
    {
      for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
      {
        Name = Module_GetName(i);
        Output_Write(logicalName, Name, v8);
        Output_Write(logicalName, (int)(intptr_t)asc_503400, a2);
        Module_SetCurrent(i);
        instanceCount += Rules_ListInstancesForClassOrModule(v10, logicalName, className, 1);
      }
    }
    Module_EndEnum();
    Class_ReleaseTraversalID();
    if ( !g_ClipsHaltExecution )
      Rules_PrintTally(logicalName, instanceCount, (int)(intptr_t)aInstances, (int)(intptr_t)aInstance_1);
  }
}
// 47FEB1: variable 'v5' is possibly undefined
// 47FECF: variable 'v8' is possibly undefined
// 47FF63: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (0047FF70) --------------------------------------------------------
_DWORD * Rules_AssertFact(const char *factString, int a2, double a3)
{
  _DWORD *result; // eax
  int **Symbol; // eax
  signed int astNode; // ebx
  int parse_buffer_ptr; // ecx
  _DWORD *parse_buffer; // esi
  int token_buffer_ptr; // ecx
  _DWORD *token_buffer; // esi
  int trace_load_save; // eax
  int trace_rules_assert; // eax

  (void)a2;
  trace_load_save = 0;
  trace_rules_assert = getenv("CLASH95_TRACE_RULES_ASSERT_FACT") != 0;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] rules-assert-enter %s\n", factString);
  if ( trace_rules_assert )
  {
    fprintf(stderr, "[rules] assert-enter fact=\"%s\" caller=%p\n", factString ? factString : "<null>", __builtin_return_address(0));
    fflush(stderr);
  }
  parse_buffer_ptr = Compat_AllocLow32Bytes(28);
  token_buffer_ptr = Compat_AllocLow32Bytes(28);
  if ( !parse_buffer_ptr || !token_buffer_ptr )
  {
    if ( parse_buffer_ptr )
      Compat_FreeLow32Bytes(parse_buffer_ptr);
    if ( token_buffer_ptr )
      Compat_FreeLow32Bytes(token_buffer_ptr);
    return 0;
  }
  parse_buffer = (_DWORD *)(uintptr_t)(unsigned int)parse_buffer_ptr;
  token_buffer = (_DWORD *)(uintptr_t)(unsigned int)token_buffer_ptr;
  parse_buffer[1] = 2;
  parse_buffer[2] = g_ClipsFalseSymbol;
  result = (_DWORD *)(uintptr_t)IO_OpenStringSource((int)(intptr_t)aMkins, factString, 0);
  if ( result )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-assert-after-router-add\n");
    Parser_NextToken((int)(intptr_t)aMkins, token_buffer_ptr);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-assert-after-first-token token=%d\n", token_buffer[0]);
    if ( trace_rules_assert )
    {
      fprintf(
        stderr,
        "[rules] assert-token1 token=%d symbol=%08x fact=\"%s\"\n",
        token_buffer[0],
        token_buffer[1],
        factString ? factString : "<null>");
      fflush(stderr);
    }
    if ( token_buffer[0] == 100 )
    {
      if ( !g_ClipsFunctionNameHashTable )
      {
        if ( trace_load_save )
          fprintf(stderr, "[menu-probe] rules-assert-seed-make-instance-symbol\n");
        Rules_RegisterHostFunction(aMakeInstance, 117, (int)(intptr_t)aMakeinstanceco, (int)(intptr_t)Instance_MakeInstanceFunction, 0);
      }
      Symbol = Rules_MakeSymbol(aMakeInstance);
      if ( trace_load_save )
        fprintf(stderr, "[menu-probe] rules-assert-after-make-symbol symbol=%p\n", Symbol);
      astNode = AST_NewNode(10, (int)(intptr_t)Symbol);
      if ( trace_load_save )
        fprintf(stderr, "[menu-probe] rules-assert-after-ast-new-node node=%d\n", astNode);
      if ( Rules_ParseMakeInstanceNode(astNode, (int)(intptr_t)aMkins) )
      {
        if ( trace_load_save )
          fprintf(stderr, "[menu-probe] rules-assert-after-instance-head\n");
        Parser_NextToken((int)(intptr_t)aMkins, token_buffer_ptr);
        if ( trace_load_save )
          fprintf(stderr, "[menu-probe] rules-assert-after-second-token token=%d\n", token_buffer[0]);
        if ( trace_rules_assert )
        {
          fprintf(
            stderr,
            "[rules] assert-token2 token=%d symbol=%08x fact=\"%s\"\n",
            token_buffer[0],
            token_buffer[1],
            factString ? factString : "<null>");
          fflush(stderr);
        }
        if ( token_buffer[0] == 102 )
          Parser_ParseForm((__int16 *)(uintptr_t)astNode, parse_buffer, (int)(intptr_t)aMkins, a3);
        else
          Parser_ReportSyntaxError();
        if ( trace_load_save )
          fprintf(stderr, "[menu-probe] rules-assert-after-parse-form\n");
        if ( trace_rules_assert )
        {
          fprintf(
            stderr,
            "[rules] assert-parsed form=%08x type=%08x value=%08x extra=%08x:%08x:%08x fact=\"%s\"\n",
            parse_buffer[0],
            parse_buffer[1],
            parse_buffer[2],
            parse_buffer[3],
            parse_buffer[4],
            parse_buffer[5],
            factString ? factString : "<null>");
          fflush(stderr);
        }
        AST_Free(astNode);
      }
    }
    else
    {
      Parser_ReportSyntaxError();
    }
    IO_CloseStringRouter((int)(intptr_t)aMkins);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-assert-after-router-remove\n");
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      Rules_RunPeriodicCleanup(1, 0);
    if ( trace_rules_assert )
    {
      fprintf(
        stderr,
        "[rules] assert-result-candidate type=%08x value=%08x nil=%08x fact=\"%s\"\n",
        parse_buffer[1],
        parse_buffer[2],
        g_ClipsFalseSymbol,
        factString ? factString : "<null>");
      fflush(stderr);
    }
    if ( parse_buffer[1] == 2 && parse_buffer[2] == g_ClipsFalseSymbol )
      result = (_DWORD *)(uintptr_t)(g_ClipsFalseSymbol ^ parse_buffer[2]);
    else
      result = Instance_FindByName(parse_buffer[2]);
  }
  else if ( trace_load_save )
  {
    fprintf(stderr, "[menu-probe] rules-assert-router-add-failed\n");
  }
  Compat_FreeLow32Bytes(token_buffer_ptr);
  Compat_FreeLow32Bytes(parse_buffer_ptr);
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004800F0) --------------------------------------------------------
int  Rules_GetInstanceSlotValue(int instance, _BYTE *slotName, int a3, _DWORD *returnValue)
{
  int *slot; // eax
  int result; // eax

  (void)a3;
  if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) != 0 || (slot = Rules_FindInstanceSlot(instance, slotName)) == 0 )
  {
    Lexer_ErrorRecover(1);
    returnValue[1] = 2;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else
  {
    returnValue[1] = (unsigned int)(slot[1] << 24) >> 26;
    returnValue[2] = slot[2];
    if ( (slot[1] & 0xFC) == 0x10 )
    {
      returnValue[3] = 0;
      returnValue[4] = *(_DWORD *)(uintptr_t)(slot[2] + 6) - 1;
    }
    return Rules_PropagateReturnValueDepth((uintptr_t)returnValue);
  }
  return result;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (00480160) --------------------------------------------------------
signed int  Rules_PutInstanceSlotValue(int instance, _BYTE *slotName, int a3, _DWORD *value, double a5)
{
  int *slot; // eax
  signed int result; // eax

  (void)a3;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
  {
    fprintf(
      stderr,
      "[world_action] fact_external_put_enter selected=%d a=%d b=%d c=%d key=%s arg1=%d arg2=%d cursor=%d,%d flipping=%d lost=%d\n",
      g_SelectedUnitIndex,
      instance,
      (int)(intptr_t)slotName,
      (int)(intptr_t)value,
      slotName ? (const char *)slotName : "(null)",
      value ? value[1] : -1,
      value ? value[2] : -1,
      g_MouseCursorRawX >> g_CursorCoordShift,
      g_MouseCursorRawY >> g_CursorCoordShift,
      DD_IsFlipping((int)(intptr_t)&g_RenderState),
      DD_IsLost((int)(intptr_t)&g_RenderState));
    fflush(stderr);
  }
  if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) == 0 && value && (slot = Rules_FindInstanceSlot(instance, slotName)) != 0 )
  {
    result = Instance_PutSlotValue((_DWORD *)(uintptr_t)instance, slot, value, a5);
    if ( result )
    {
      if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
        Rules_RunPeriodicCleanup(1, 0);
      return 1;
    }
  }
  else
  {
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (004801D0) --------------------------------------------------------
int  Rules_GetInstanceClassName(int instance)
{
  if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) != 0 )
    return 0;
  else
    return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 28) + 16);
}

//----- (004801F0) --------------------------------------------------------
int Rules_GetActiveInstanceCount(void)
{
  return g_Rules_ActiveInstanceCount;
}
// 51AD10: using guessed type int dword_51AD10;

//----- (00480200) --------------------------------------------------------
int  Rules_GetNextInstance(int instance)
{
  if ( !instance )
    return g_Clips_InstanceListHead;
  if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) != 0 )
    return 0;
  return *(_DWORD *)(uintptr_t)(instance + 68);
}
// 51AD0C: using guessed type int dword_51AD0C;

//----- (00480220) --------------------------------------------------------
int  Rules_GetNextInstanceInScope(int instance)
{
  int candidateInstance; // ecx
  int v3; // ecx

  if ( !instance )
  {
    candidateInstance = g_Clips_InstanceListHead;
    if ( g_Clips_InstanceListHead )
      goto LABEL_7;
    return 0;
  }
  if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) != 0 )
    return 0;
  candidateInstance = *(_DWORD *)(uintptr_t)(instance + 68);
  if ( !candidateInstance )
    return 0;
LABEL_7:
  while ( !Class_IsInScope(*(_DWORD *)(uintptr_t)(candidateInstance + 44), 0) )
  {
    candidateInstance = *(_DWORD *)(uintptr_t)(v3 + 68);
    if ( !candidateInstance )
      return 0;
  }
  return v3;
}
// 48025C: variable 'v3' is possibly undefined
// 51AD0C: using guessed type int dword_51AD0C;

//----- (00480270) --------------------------------------------------------
int  Rules_GetNextInstanceInClass(int classPtr, int instance)
{
  if ( !instance )
    return *(_DWORD *)(uintptr_t)(classPtr + 80);
  if ( (*(_BYTE *)(uintptr_t)(instance + 24) & 2) != 0 )
    return 0;
  return *(_DWORD *)(uintptr_t)(instance + 52);
}

//----- (004802F0) --------------------------------------------------------
int  Rules_ClassCommand(int returnValue, int a2, double a3)
{
  int argName; // esi
  _DWORD *instance; // eax
  int result; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  _DWORD temp[6]; // [esp-4h] [ebp-24h] BYREF
  /* stack alias of temp[1] */
  /* stack alias of temp[2]: the DATA_OBJECT value slot */
  int v15 CLASH95_UNUSED; // [esp+1Ch] [ebp-4h]

  v15 = a2;
  argName = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16);
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), temp, returnValue, a3);
  if ( temp[1] == 7 )
  {
    instance = (_DWORD *)(uintptr_t)temp[2];
    if ( (*(_BYTE *)(uintptr_t)(temp[2] + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      return Lexer_ErrorRecover(1);
    }
LABEL_5:
    result = Rules_GetConstructNameSymbol(instance[11]);
    *(_DWORD *)(uintptr_t)(v6 + 8) = result;
    return result;
  }
  if ( temp[1] == 8 )
  {
    instance = Instance_FindByName(temp[2]);
    if ( !instance )
      return Instance_ReportNoSuchInstanceError(v8, argName);
    goto LABEL_5;
  }
  switch ( temp[1] )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      result = Rules_GetConstructNameSymbol(g_ClipsPrimitiveTypeClassMap[temp[1]]);
      *(_DWORD *)(uintptr_t)(v7 + 8) = result;
      break;
    default:
      Rules_PrintErrorID((int)(intptr_t)aInscom, 1, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUndefinedTypeI, v9);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], argName, v10);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__32, v11);
      result = Lexer_ErrorRecover(1);
      break;
  }
  return result;
}
// 480356: variable 'v6' is possibly undefined
// 48037E: variable 'v7' is possibly undefined
// 48039E: variable 'v8' is possibly undefined
// 4803C6: variable 'v9' is possibly undefined
// 4803D2: variable 'v10' is possibly undefined
// 4803E1: variable 'v11' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51AD7C: using guessed type int dword_51AD7C[];
// 54DD70: using guessed type int dword_54DD70;

//----- (00480400) --------------------------------------------------------
signed int  Rules_DeleteInstanceCommand(int a1, double a2)
{
  signed int result; // eax
  int argument; // eax

  result = MessageHandler_CheckCurrentMessage(a1, 1);
  if ( result )
  {
    argument = MessageHandler_GetNthArgument(0);
    return Instance_DeleteInstance(*(_DWORD *)(uintptr_t)(argument + 8), a2);
  }
  return result;
}

//----- (00480430) --------------------------------------------------------
signed int  Rules_UnmakeInstanceCommand(int a1, double a2)
{
  int argumentIndex; // esi
  int argExpr; // ebx
  int returnCode; // edi
  _DWORD *instance; // ecx
  _DWORD v8[6]; // [esp-4h] [ebp-2Ch] BYREF
  /* stack alias of v8[1] */
  /* stack alias of v8[2]: the DATA_OBJECT value slot */
  int v11 CLASH95_UNUSED; // [esp+20h] [ebp-8h]

  v11 = a1;
  argumentIndex = 1;
  argExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  returnCode = 1;
  if ( argExpr )
  {
    while ( 1 )
    {
      Parser_ParseForm((__int16 *)(uintptr_t)argExpr, v8, a1, a2);
      if ( v8[1] == 8 || v8[1] == 2 )
      {
        instance = Instance_FindByName(v8[2]);
        if ( !instance && strcmp_(0, asc_5033CC) )
        {
          Instance_ReportNoSuchInstanceError((int)(intptr_t)instance, (int)(intptr_t)aUnmakeInstance);
          return 0;
        }
      }
      else
      {
        if ( v8[1] != 7 )
        {
          Parser_ReportError(argumentIndex, (int)(intptr_t)aInstanceAddr_4);
          Lexer_ErrorRecover(1);
          return 0;
        }
        instance = (_DWORD *)(uintptr_t)v8[2];
        if ( (*(_BYTE *)(uintptr_t)(v8[2] + 24) & 2) != 0 )
        {
          Instance_ReportInvalidInstanceAddressError();
          Lexer_ErrorRecover(1);
          return 0;
        }
      }
      if ( !Rules_UnmakeInstance((int)(intptr_t)instance, a2) )
        returnCode = 0;
      if ( a1 )
      {
        argExpr = *(_DWORD *)(uintptr_t)(argExpr + 10);
        ++argumentIndex;
        if ( argExpr )
          continue;
      }
      return returnCode;
    }
  }
  return returnCode;
}
// 480450: variable 'a1' is possibly undefined
// 480478: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (00480520) --------------------------------------------------------
signed int  Rules_SymbolToInstanceName(_DWORD *returnValue, double a2)
{
  signed int result; // eax

  result = Lexer_ParseValueList(1, returnValue, 2, a2);
  if ( result )
  {
    returnValue[1] = 8;
  }
  else
  {
    returnValue[1] = 2;
    result = g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  return result;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (00480560) --------------------------------------------------------
int  Rules_InstanceNameToSymbol(int a1, double a2)
{
  _DWORD result[9]; // [esp-8h] [ebp-24h] BYREF

  result[7] = a1;
  if ( Lexer_ParseValueList(1, result, 8, a2) )
    return result[2];
  else
    return g_ClipsFalseSymbol;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (004805A0) --------------------------------------------------------
_DWORD * Rules_InstanceAddressCommand(int returnValue, double a2)
{
  _DWORD *result; // eax
  int v4; // ecx
  int *theModule; // edi
  int searchImports; // ebp
  int v7; // eax
  int v8; // ecx
  _DWORD v9[2]; // [esp+0h] [ebp-30h] BYREF
  int v8_alias; // [esp+8h] [ebp-28h]

  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  if ( Rules_RtnArgCount() <= 1 )
  {
    result = (_DWORD *)(uintptr_t)Lexer_ParseValueList(1, v9, 112, a2);
    if ( result )
    {
      if ( v9[1] == 7 )
      {
        if ( (*(_BYTE *)(uintptr_t)(v8_alias + 24) & 2) != 0 )
        {
          Instance_ReportInvalidInstanceAddressError();
          return (_DWORD *)(uintptr_t)Lexer_ErrorRecover(1);
        }
        else
        {
          *(_DWORD *)(uintptr_t)(returnValue + 4) = 7;
          result = (_DWORD *)(uintptr_t)v8_alias;
          *(_DWORD *)(uintptr_t)(returnValue + 8) = v8_alias;
        }
      }
      else
      {
        result = Instance_FindByName(v8_alias);
        if ( !result )
          return (_DWORD *)(uintptr_t)Instance_ReportNoSuchInstanceError(v8, (int)(intptr_t)aInstanceAddres);
        *(_DWORD *)(uintptr_t)(returnValue + 4) = 7;
        *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
      }
    }
  }
  else
  {
    result = (_DWORD *)(uintptr_t)Lexer_ParseValueList(1, v9, 2, a2);
    if ( result )
    {
      theModule = Module_FindByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v8_alias + 16));
      if ( !theModule && strcmp_(v4, asc_5033CC) )
      {
        Parser_ReportError(1, (int)(intptr_t)aModuleName);
        return (_DWORD *)(uintptr_t)Lexer_ErrorRecover(1);
      }
      if ( theModule )
      {
        searchImports = 0;
      }
      else
      {
        searchImports = 1;
        theModule = (int *)(uintptr_t)Module_GetCurrent();
      }
      result = (_DWORD *)(uintptr_t)Lexer_ParseValueList(2, v9, 8, a2);
      if ( result )
      {
        v7 = Module_GetCurrent();
        result = Instance_LookupInHashBucket(v8_alias, (int)(intptr_t)theModule, (_DWORD *)(uintptr_t)searchImports, v7);
        if ( result )
        {
          *(_DWORD *)(uintptr_t)(returnValue + 4) = 7;
          *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
          return result;
        }
        return (_DWORD *)(uintptr_t)Instance_ReportNoSuchInstanceError(v8, (int)(intptr_t)aInstanceAddres);
      }
    }
  }
  return result;
}
// 48060A: variable 'v4' is possibly undefined
// 4806AD: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DD70: using guessed type int dword_54DD70;

//----- (00480750) --------------------------------------------------------
int  Rules_InstanceNameCommand(int returnValue, int a2, double a3)
{
  int result; // eax
  _DWORD *instance; // edx
  int v6; // ecx
  _DWORD v7[2]; // [esp-4h] [ebp-28h] BYREF
  int v8_alias; // [esp+4h] [ebp-20h]
  int v9 CLASH95_UNUSED; // [esp+1Ch] [ebp-8h]

  v9 = a2;
  *(_DWORD *)(uintptr_t)(returnValue + 4) = 2;
  *(_DWORD *)(uintptr_t)(returnValue + 8) = g_ClipsFalseSymbol;
  result = Lexer_ParseValueList(1, v7, 112, a3);
  if ( result )
  {
    if ( v7[1] == 7 )
    {
      instance = (_DWORD *)(uintptr_t)v8_alias;
      if ( (*(_BYTE *)(uintptr_t)(v8_alias + 24) & 2) != 0 )
      {
        Instance_ReportInvalidInstanceAddressError();
        return Lexer_ErrorRecover(1);
      }
    }
    else
    {
      instance = Instance_FindByName(v8_alias);
      if ( !instance )
        return Instance_ReportNoSuchInstanceError(v6, (int)(intptr_t)aInstanceName);
    }
    *(_DWORD *)(uintptr_t)(returnValue + 4) = 8;
    result = instance[7];
    *(_DWORD *)(uintptr_t)(returnValue + 8) = result;
  }
  return result;
}
// 4807D9: variable 'v6' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004807F0) --------------------------------------------------------
BOOL  Rules_InstanceAddressPCommand(int a1, double a2)
{
  _DWORD theResult[7]; // [esp-4h] [ebp-1Ch] BYREF

  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), theResult, a1, a2);
  return theResult[1] == 7;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480820) --------------------------------------------------------
BOOL  Rules_InstanceNamePCommand(int a1, double a2)
{
  _DWORD theResult[7]; // [esp-4h] [ebp-1Ch] BYREF

  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), theResult, a1, a2);
  return theResult[1] == 8;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480850) --------------------------------------------------------
BOOL  Rules_InstancePCommand(int a1, double a2)
{
  int theResult; // [esp-4h] [ebp-1Ch] BYREF
  int resultType; // [esp+0h] [ebp-18h]

  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), theResult, a1, a2);
  return resultType == 8 || resultType == 7;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480890) --------------------------------------------------------
int  Rules_InstanceExistPCommand(int a1, double a2)
{
  int result; // eax
  _DWORD theResult[6]; // [esp-4h] [ebp-1Ch] BYREF
  /* stack alias of theResult[1] */
  /* stack alias of theResult[2]: the DATA_OBJECT value slot */

  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), theResult, a1, a2);
  if ( theResult[1] == 7 )
  {
    LOBYTE(result) = (*(_BYTE *)(uintptr_t)(theResult[2] + 24) & 2) == 0;
    return (unsigned __int8)result;
  }
  if ( theResult[1] == 8 || theResult[1] == 2 )
  {
    LOBYTE(result) = Instance_FindByName(theResult[2]) != 0;
    return (unsigned __int8)result;
  }
  Parser_ReportError(1, (int)(intptr_t)aInstanceNameIn);
  Lexer_ErrorRecover(1);
  return 0;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480910) --------------------------------------------------------
int  Rules_ListInstancesForClassOrModule(signed int a1, int logicalName, int className, int showModulePrefix)
{
  int instanceCount; // edi
  int i; // esi
  int instance; // esi
  int v9; // ecx
  _BYTE *v10; // edx
  int v11; // ecx
  int *theClass; // eax
  int v13; // ecx

  instanceCount = 0;
  if ( className )
  {
    Module_GetCurrent();
    theClass = Class_LookupByModule(v11, v10);
    if ( theClass )
      return Rules_ListInstancesOfClassRecursive(a1, logicalName, v13, (int)(intptr_t)theClass, showModulePrefix);
    if ( !showModulePrefix )
    {
      Class_ReportLookupError(v13, className);
      return 0;
    }
    return instanceCount;
  }
  if ( showModulePrefix )
  {
    for ( i = Class_GetNextRecord(0); i; i = Class_GetNextRecord(i) )
      instanceCount += Rules_ListInstancesOfClassRecursive(a1, logicalName, 0, i, showModulePrefix);
    return instanceCount;
  }
  instance = Rules_GetNextInstanceInScope(0);
  if ( !instance )
    return instanceCount;
  v9 = 1;
  do
  {
    Instance_PrintNameOfClass(logicalName, instance, v9);
    ++instanceCount;
    instance = Rules_GetNextInstanceInScope(instance);
  }
  while ( instance );
  return instanceCount;
}
// 480983: variable 'v9' is possibly undefined
// 4809A8: variable 'v11' is possibly undefined
// 4809A8: variable 'v10' is possibly undefined
// 4809BF: variable 'v13' is possibly undefined

//----- (004809F0) --------------------------------------------------------
int  Rules_ListInstancesOfClassRecursive(signed int traversalID, int logicalName, int inheritFlag, int theClass, int showModulePrefix)
{
  int markByte; // ebx
  int markMask; // eax
  int count; // edi
  int instance; // ecx
  int v10; // ecx
  int subclassOffset; // ebp
  unsigned int i; // [esp+Ch] [ebp-10h]

  markByte = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  markMask = 1 << (traversalID % 8);
  count = 0;
  if ( ((unsigned __int8)markMask & *(_BYTE *)(uintptr_t)(markByte + 108)) != 0 )
    return 0;
  *(_BYTE *)(uintptr_t)(markByte + 108) |= markMask;
  instance = *(_DWORD *)(uintptr_t)(theClass + 80);
  if ( instance )
  {
    while ( !g_ClipsHaltExecution )
    {
      if ( showModulePrefix )
        Output_Write(logicalName, (int)(intptr_t)asc_5034F8, instance);
      Instance_PrintNameOfClass(logicalName, instance, 1);
      instance = *(_DWORD *)(uintptr_t)(v10 + 52);
      ++count;
      if ( !instance )
        goto LABEL_7;
    }
  }
  else
  {
LABEL_7:
    if ( inheritFlag )
    {
      subclassOffset = 0;
      for ( i = 0; *(unsigned __int16 *)(uintptr_t)(theClass + 40) > i && !g_ClipsHaltExecution; ++i )
      {
        count += Rules_ListInstancesOfClassRecursive(traversalID, logicalName, inheritFlag, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 42) + subclassOffset), showModulePrefix);
        subclassOffset += 4;
      }
    }
  }
  return count;
}
// 480A76: variable 'v9' is possibly undefined
// 480A7B: variable 'v10' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (00480AF0) --------------------------------------------------------
signed int  Rules_PrintInstanceSlots(int logicalName, int instance, int separatorString)
{
  signed int result; // eax
  unsigned int slotIndex; // edi
  int slotOffset; // ebp
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  result = Instance_PrintNameOfClass(logicalName, instance, 0);
  slotIndex = 0;
  slotOffset = 0;
  while ( slotIndex < *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 44) + 72) )
  {
    Output_Write(logicalName, separatorString, instance);
    Output_Write(logicalName, (int)(intptr_t)asc_5034FC, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v7 + 72) + slotOffset));
    Output_Write(logicalName, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)v8 + 8) + 12) + 16), v8);
    if ( (*(_DWORD *)(uintptr_t)(v9 + 4) & 0xFC) == 0x10 )
    {
      if ( *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v9 + 8) + 6) )
      {
        Output_Write(logicalName, (int)(intptr_t)asc_503458, v9);
        Lexer_OutputFieldRange(logicalName, *(_DWORD *)(uintptr_t)(v11 + 8), *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v11 + 8) + 6) - 1, 0, 0);
      }
    }
    else
    {
      Output_Write(logicalName, (int)(intptr_t)asc_503458, v9);
      Rules_PrintAtomValue(logicalName, *(_DWORD *)(uintptr_t)(v10 + 4) << 24 >> 26, (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v10 + 8));
    }
    result = Output_Write(logicalName, (int)(intptr_t)asc_503500, v9);
    slotOffset += 4;
    ++slotIndex;
  }
  return result;
}
// 480B2D: variable 'v7' is possibly undefined
// 480B3F: variable 'v8' is possibly undefined
// 480B51: variable 'v9' is possibly undefined
// 480B6B: variable 'v10' is possibly undefined
// 480BA8: variable 'v11' is possibly undefined

//----- (00480BC0) --------------------------------------------------------
int *__fastcall Rules_FindInstanceSlot(int instance, _BYTE *slotName)
{
  int *result; // eax

  result = Rules_FindSymbolEntry(slotName);
  if ( result )
    return (int *)(uintptr_t)Instance_GetSlotValueBySymbol(instance, (int)(uintptr_t)result);
  return result;
}

//----- (00480BE0) --------------------------------------------------------
signed int  Rules_RegisterHostFunctionNoRestrictions(char *functionName, int returnType, int functionPointer, int actualName)
{
  return Rules_RegisterHostFunction(functionName, returnType, functionPointer, actualName, 0);
}

//----- (00480BF0) --------------------------------------------------------
signed int  Rules_RegisterHostFunction(
        char *functionName,
        int returnType,
        int functionPointer,
        int actualName,
        int restrictions)
{
  int host_function_ptr; // ebx
  _DWORD *free_node; // eax
  signed int *symbol; // eax
  int symbol_ptr; // eax
  int argument_spec_len; // eax

  if ( returnType != 97
    && returnType != 98
    && returnType != 99
    && returnType != 100
    && returnType != 102
    && returnType != 105
    && returnType != 106
    && returnType != 107
    && returnType != 108
    && returnType != 109
    && returnType != 110
    && returnType != 111
    && returnType != 115
    && returnType != 117
    && returnType != 118
    && returnType != 120
    && returnType != 119 )
  {
    return 0;
  }
  free_node = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 124);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 124);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 124) = *free_node;
    host_function_ptr = g_ClipsMemFreeListTemp;
  }
  else
  {
    host_function_ptr = Mem_HeapAllocWithRetry((_DWORD *)0x1F);
  }
  symbol = Str_Intern(functionName, host_function_ptr);
  *(_DWORD *)(uintptr_t)(host_function_ptr + 0) = symbol;
  *(_BYTE *)(uintptr_t)(host_function_ptr + 8) = returnType;
  *(_DWORD *)(uintptr_t)(host_function_ptr + 9) = actualName;
  *(_DWORD *)(uintptr_t)(host_function_ptr + 27) = g_Rules_HostFunctionListHead;
  *(_DWORD *)(uintptr_t)(host_function_ptr + 4) = functionPointer;
  if ( restrictions
    && ((argument_spec_len = strlen((const char *)(uintptr_t)restrictions), argument_spec_len < 2)
     || (IsTable[(unsigned __int8)(*(_BYTE *)(uintptr_t)restrictions + 1)] & 0x20) == 0 && *(_BYTE *)(uintptr_t)restrictions != 42
     || (IsTable[(unsigned __int8)(*(_BYTE *)(uintptr_t)(restrictions + 1) + 1)] & 0x20) == 0 && *(_BYTE *)(uintptr_t)(restrictions + 1) != 42) )
  {
    restrictions = 0;
  }
  *(_DWORD *)(uintptr_t)(host_function_ptr + 13) = 0;
  *(_WORD *)(uintptr_t)(host_function_ptr + 21) = 1;
  *(_WORD *)(uintptr_t)(host_function_ptr + 23) = 1;
  symbol_ptr = *(_DWORD *)(uintptr_t)(host_function_ptr + 0);
  *(_DWORD *)(uintptr_t)(host_function_ptr + 17) = restrictions;
  ++*(_DWORD *)(uintptr_t)(symbol_ptr + 4);
  g_Rules_HostFunctionListHead = host_function_ptr;
  Rules_InsertFunctionHashEntry(host_function_ptr);
  return 1;
}
// 51A264: using guessed type int dword_51A264;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00480D60) --------------------------------------------------------
signed int  Rules_AddFunctionParser(_BYTE *functionName)
{
  int **Symbol; // eax
  int *v2; // edx
  int v3; // ecx

  Symbol = Rules_MakeSymbol(functionName);
  if ( Symbol )
  {
    *(int **)((char *)Symbol + 17) = 0;
    *(_WORD *)((char *)Symbol + 21) = 0;
    *(int **)((char *)Symbol + 13) = v2;
    return 1;
  }
  else
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunctionParser, v3);
    return 0;
  }
}
// 480D76: variable 'v2' is possibly undefined
// 480D89: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00480DD0) --------------------------------------------------------
signed int  Rules_SetFunctionSeqOverloadFlags(_BYTE *functionName, int sequenceFlag)
{
  int **Symbol; // eax
  int overloadFlag; // edx

  Symbol = Rules_MakeSymbol(functionName);
  if ( Symbol )
  {
    *(_WORD *)((char *)Symbol + 23) = overloadFlag != 0;
    *(_WORD *)((char *)Symbol + 21) = sequenceFlag != 0;
    return 1;
  }
  else
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aOnlyExistingFu, 0);
    return 0;
  }
}
// 480DE1: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00480E80) --------------------------------------------------------
char * Rules_GetArgTypeName(char restriction)
{
  char *result; // eax

  switch ( restriction )
  {
    case 'a':
      result = aExternalAddres;
      break;
    case 'd':
    case 'f':
      result = aFloat_0;
      break;
    case 'e':
      result = aInstanceAddr_1;
      break;
    case 'g':
      result = aIntegerFloatOr;
      break;
    case 'h':
      result = aInstanceAddr_2;
      break;
    case 'i':
    case 'l':
      result = aInteger_0;
      break;
    case 'j':
      result = aSymbolString_0;
      break;
    case 'k':
      result = aSymbolOrString;
      break;
    case 'm':
      result = aMultifield;
      break;
    case 'n':
      result = aIntegerOrFloat;
      break;
    case 'o':
      result = aInstanceName_0;
      break;
    case 'p':
      result = aInstanceNameOr;
      break;
    case 'q':
      result = aMultifieldSymb;
      break;
    case 's':
      result = aString_0;
      break;
    case 'u':
      result = aNonVoidReturnV;
      break;
    case 'w':
      result = aSymbol_0;
      break;
    case 'x':
      result = aInstanceAddr_3;
      break;
    case 'y':
      result = aFactAddress;
      break;
    case 'z':
      result = aFactAddressInt;
      break;
    default:
      result = aUnknownArgumen;
      break;
  }
  return result;
}

//----- (00480F10) --------------------------------------------------------
signed int  Rules_GetArgRestrictionType(int theFunction, int position)
{
  signed int result; // eax
  unsigned int v4; // kr04_4

  if ( !theFunction )
    return 117;
  if ( !*(_DWORD *)(uintptr_t)(theFunction + 17) )
    return 117;
  v4 = strlen((const char *)(uintptr_t)*(_DWORD *)(uintptr_t)(theFunction + 17)) + 1;
  if ( (int)(v4 - 1) < 3 )
    return 117;
  result = *(unsigned __int8 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theFunction + 17) + 2);
  if ( result == 42 )
    result = 117;
  if ( (int)(v4 - 1) >= position + 3 )
    return *(unsigned __int8 *)(uintptr_t)(position + *(_DWORD *)(uintptr_t)(theFunction + 17) + 2);
  return result;
}

//----- (00480F70) --------------------------------------------------------
int Rules_GetFunctionDefinitionListHead(void)
{
  return g_Rules_HostFunctionListHead;
}
// 51A264: using guessed type int dword_51A264;

//----- (00481010) --------------------------------------------------------
int ** Rules_MakeSymbol(_BYTE *functionName)
{
  int hash_bucket; // edx
  int interned_name; // ecx
  int bucket_entry; // eax
  int symbol; // edx

  hash_bucket = Rules_HashSymbolName(functionName, 0x33u);
  interned_name = (int)(intptr_t)Rules_FindSymbolEntry((int)(intptr_t)functionName);
  bucket_entry = *(_DWORD *)(uintptr_t)(g_ClipsFunctionNameHashTable + 4 * hash_bucket);
  while ( bucket_entry )
  {
    symbol = *(_DWORD *)(uintptr_t)bucket_entry;
    if ( interned_name == *(_DWORD *)(uintptr_t)symbol )
      return (int **)(uintptr_t)symbol;
    bucket_entry = *(_DWORD *)(uintptr_t)(bucket_entry + 4);
  }
  return 0;
}
// 54DD40: using guessed type int dword_54DD40;

//----- (00481050) --------------------------------------------------------
int Rules_InitFunctionNameHashTable(void)
{
  int result; // eax

  g_ClipsFunctionNameHashTable = (int)(intptr_t)Mem_SmallBlockAlloc(0xCCu);
  for ( result = 0; result != 204; result += 4 )
    *(_DWORD *)(uintptr_t)(g_ClipsFunctionNameHashTable + result) = 0;
  return result;
}
// 54DD40: using guessed type int dword_54DD40;

//----- (00481090) --------------------------------------------------------
int * Rules_InsertFunctionHashEntry(int functionDef)
{
  _DWORD *free_node; // ebx
  int *bucket_head_ptr; // eax
  int existing_head; // edx
  int host_function_ptr; // ecx
  int symbol_record; // eax
  int symbol_name; // eax

  if ( !g_ClipsFunctionNameHashTable )
    Rules_InitFunctionNameHashTable();
  free_node = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = (int)(intptr_t)free_node;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *free_node;
    host_function_ptr = g_ClipsMemFreeListTemp;
  }
  else
  {
    host_function_ptr = Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *(_DWORD *)(uintptr_t)(host_function_ptr + 0) = functionDef;
  symbol_record = *(_DWORD *)(uintptr_t)(unsigned int)functionDef;
  symbol_name = *(_DWORD *)((uintptr_t)(unsigned int)symbol_record + 16);
  bucket_head_ptr = (int *)(uintptr_t)(g_ClipsFunctionNameHashTable
                          + 4 * Rules_HashSymbolName((_BYTE *)(uintptr_t)(unsigned int)symbol_name, 0x33u));
  existing_head = *bucket_head_ptr;
  *bucket_head_ptr = host_function_ptr;
  *(_DWORD *)(uintptr_t)(host_function_ptr + 4) = existing_head;
  return bucket_head_ptr;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD40: using guessed type int dword_54DD40;

//----- (00481100) --------------------------------------------------------
int  Rules_RtnLexeme(int argumentPosition, int a2, double a3)
{
  int argExpr; // eax
  int i; // edx
  _DWORD v8[6]; // [esp-4h] [ebp-20h] BYREF
  /* stack alias of v8[1] */
  /* stack alias of v8[2]: the DATA_OBJECT value slot */

  argExpr = *(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    if ( i >= argumentPosition )
      break;
    argExpr = *(_DWORD *)(uintptr_t)(argExpr + 10);
  }
  if ( argExpr )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)argExpr, v8, a2, a3);
    if ( v8[1] == 2 || v8[1] == 8 || v8[1] == 3 )
    {
      return *(_DWORD *)(uintptr_t)(v8[2] + 16);
    }
    else
    {
      Rules_ExpectedTypeError((int)(intptr_t)aRtnlexeme, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    Rules_NonexistentArgError(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 51A960: using guessed type int dword_51A960;
