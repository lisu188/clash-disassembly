/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004AB610) --------------------------------------------------------
_DWORD * Instance_ActiveMessageDuplicateInstanceFunction(int *returnValue, double a2)
{
  int v3; // ecx
  _DWORD *overrides; // edi
  _DWORD *result; // eax
  int *messageSymbol; // eax
  int v7; // edx
  int v8; // ecx
  int newNameValue; // [esp+1Ch] [ebp-3Ch] BYREF
  int savedGuardState; // [esp+34h] [ebp-24h]
  int overrideCount; // [esp+38h] [ebp-20h] BYREF
  _DWORD errorFlag[7]; // [esp+3Ch] [ebp-1Ch] BYREF

  overrides = (_DWORD *)Instance_ParseSlotOverrideArgs(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10), &overrideCount, errorFlag, a2);
  if ( errorFlag[0] )
  {
    returnValue[1] = 2;
    result = (_DWORD *)g_ClipsFalseSymbol;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  else if ( Instance_ResolveArgumentToInstance(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), v3, a2) && Lexer_ParseValueList(2, &newNameValue, 8, a2) )
  {
    savedGuardState = g_InstanceDirectMessageGuardActive;
    g_InstanceDirectMessageGuardActive = 1;
    messageSymbol = Rules_FindSymbolEntry(aMessageDupli_1);
    MessageHandler_SendToInstanceAddress((int)messageSymbol, v7, v8, returnValue, a2);
    g_InstanceDirectMessageGuardActive = savedGuardState;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  else
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return Instance_FreeSlotOverrideArgs(overrides, overrideCount);
  }
  return result;
}
// 4AB666: variable 'v3' is possibly undefined
// 4AB712: variable 'v7' is possibly undefined
// 4AB712: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD70: using guessed type int dword_54DD70;

//----- (004AB740) --------------------------------------------------------
int  Instance_ModifyInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveModifyInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB752: variable 'v1' is possibly undefined
// 4AB752: variable 'v2' is possibly undefined
// 4AB759: variable 'v3' is possibly undefined

//----- (004AB770) --------------------------------------------------------
int  Instance_MessageModifyInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveMessageModifyInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB782: variable 'v1' is possibly undefined
// 4AB782: variable 'v2' is possibly undefined
// 4AB789: variable 'v3' is possibly undefined

//----- (004AB7A0) --------------------------------------------------------
int  Instance_DuplicateInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveDuplicateInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB7B2: variable 'v1' is possibly undefined
// 4AB7B2: variable 'v2' is possibly undefined
// 4AB7B9: variable 'v3' is possibly undefined

//----- (004AB7D0) --------------------------------------------------------
int  Instance_MessageDuplicateInstanceFunction(double a1)
{
  int *v1; // ecx
  double v2; // st7
  int v3; // edx

  Rules_SetObjectPatternMatchDelay(1, a1);
  Instance_ActiveMessageDuplicateInstanceFunction(v1, v2);
  return Rules_SetObjectPatternMatchDelay(v3, v2);
}
// 4AB7E2: variable 'v1' is possibly undefined
// 4AB7E2: variable 'v2' is possibly undefined
// 4AB7E9: variable 'v3' is possibly undefined

//----- (004AB800) --------------------------------------------------------
_DWORD * Instance_DirectDuplicateFunction(int *returnValue, double a2)
{
  return Rules_DuplicateInstanceCore(returnValue, 0, a2);
}

//----- (004AB810) --------------------------------------------------------
_DWORD * Instance_MessageDuplicateFunction(int *returnValue, double a2)
{
  return Rules_DuplicateInstanceCore(returnValue, 1, a2);
}

//----- (004AB820) --------------------------------------------------------
_DWORD * Instance_DirectModifyFunction(int returnValue, double a2)
{
  return Rules_ModifyInstanceCore(returnValue, 0, a2);
}

//----- (004AB830) --------------------------------------------------------
_DWORD * Instance_MessageModifyFunction(int returnValue, double a2)
{
  return Rules_ModifyInstanceCore(returnValue, 1, a2);
}

//----- (004AB840) --------------------------------------------------------
int  Instance_ParseSlotOverrideArgs(int overrideExprs, _DWORD *overrideCount, _DWORD *errorFlag, double a4)
{
  int exprCursor; // esi
  int result; // eax
  int overrideIndex; // edi
  _DWORD *v7; // eax
  _DWORD *overrideCursor; // ecx
  _DWORD *v9; // ecx
  _DWORD *v10; // ecx
  _DWORD *nextOverride; // eax
  _DWORD *overrideArray; // [esp+8h] [ebp-18h]
  int slotNameSymbol; // [esp+Ch] [ebp-14h]

  exprCursor = overrideExprs;
  *errorFlag = 0;
  result = AST_CountListNodes(overrideExprs) / 2;
  *overrideCount = result;
  if ( result )
  {
    overrideIndex = 0;
    v7 = Mem_SmallBlockAlloc(24 * result);
    overrideArray = v7;
    if ( exprCursor )
    {
      overrideCursor = v7;
      while ( !Parser_ParseForm((__int16 *)exprCursor, overrideCursor, (int)overrideCursor, a4) )
      {
        if ( v9[1] != 2 )
        {
          Parser_ReportError(overrideIndex + 1, (int)aSlotName);
          Lexer_ErrorRecover(1);
          break;
        }
        slotNameSymbol = v9[2];
        if ( !Parser_ParseSlotDefaultOrRestriction(0, *(_DWORD *)(*(_DWORD *)(exprCursor + 10) + 6), v9, a4) )
          break;
        *v10 = slotNameSymbol;
        exprCursor = *(_DWORD *)(*(_DWORD *)(exprCursor + 10) + 10);
        if ( exprCursor )
          nextOverride = &overrideArray[6 * overrideIndex + 6];
        else
          nextOverride = 0;
        overrideCursor = v10 + 6;
        ++overrideIndex;
        *(overrideCursor - 1) = nextOverride;
        if ( !exprCursor )
          return (int)overrideArray;
      }
      Mem_SmallBlockFree(overrideArray, 24 * *overrideCount);
      *errorFlag = 1;
      return 0;
    }
    else
    {
      return (int)overrideArray;
    }
  }
  return result;
}
// 4AB8AA: variable 'v9' is possibly undefined
// 4AB928: variable 'v10' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (004AB960) --------------------------------------------------------
_DWORD * Instance_FreeSlotOverrideArgs(_DWORD *result, int overrideCount)
{
  if ( result )
    return (_DWORD *)Mem_SmallBlockFree(result, 24 * overrideCount);
  return result;
}

//----- (004AB990) --------------------------------------------------------
_DWORD * Rules_ModifyInstanceCore(int returnValue, int msgpass, double a3)
{
  int theInstance; // edi
  int slotOverride; // esi
  int v6; // eax
  int v7; // ecx
  int *theSlot; // edx
  _DWORD *result; // eax
  bool putFailed; // zf
  int v11; // ecx
  int *putValue; // eax
  int sendResult; // [esp+0h] [ebp-40h] BYREF
  int sendResultType; // [esp+4h] [ebp-3Ch]
  _DWORD *sendResultValue; // [esp+8h] [ebp-38h]
  int multifieldBegin; // [esp+Ch] [ebp-34h]
  int multifieldEnd; // [esp+10h] [ebp-30h]
  __int16 tmpExprType; // [esp+18h] [ebp-28h] BYREF
  int tmpExprValue; // [esp+1Ah] [ebp-26h]
  int tmpExprArgList; // [esp+1Eh] [ebp-22h]
  int tmpExprNext; // [esp+22h] [ebp-1Eh]
  int v22; // [esp+28h] [ebp-18h]

  v22 = returnValue;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(v22 + 8) = g_ClipsFalseSymbol;
  if ( !g_InstanceDirectMessageGuardActive )
  {
    Rules_PrintErrorID((int)aInsmoddp, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDirectMessageM, v11);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  g_InstanceDirectMessageGuardActive = 0;
  theInstance = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
  if ( (*(_BYTE *)(theInstance + 24) & 2) != 0 )
  {
    Instance_ReportInvalidInstanceAddressError();
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  slotOverride = *(_DWORD *)(MessageHandler_GetNthArgument(1) + 8);
  *(_DWORD *)(v22 + 4) = 2;
  *(_DWORD *)(v22 + 8) = g_ClipsFalseSymbol;
  if ( slotOverride )
  {
    while ( 1 )
    {
      v6 = Instance_GetSlotValueBySymbol(theInstance, *(_DWORD *)slotOverride);
      theSlot = (int *)v6;
      if ( !v6 )
      {
        Instance_ReportNoSuchSlotError(v7, (int)aModifyInstance);
        return (_DWORD *)Lexer_ErrorRecover(1);
      }
      if ( !msgpass )
        break;
      tmpExprType = *(_WORD *)(slotOverride + 4);
      if ( tmpExprType == 4 )
        tmpExprValue = slotOverride;
      else
        tmpExprValue = *(_DWORD *)(slotOverride + 8);
      tmpExprArgList = 0;
      tmpExprNext = 0;
      result = (_DWORD *)MessageHandler_SendToInstanceAddress(*(_DWORD *)(*(_DWORD *)v6 + 12), theInstance, (int)&tmpExprType, &sendResult, a3);
      if ( g_ClipsEvaluationError )
        return result;
      if ( sendResultType == 2 )
      {
        result = sendResultValue;
        putFailed = sendResultValue == (_DWORD *)g_ClipsFalseSymbol;
        goto LABEL_11;
      }
LABEL_12:
      slotOverride = *(_DWORD *)(slotOverride + 20);
      if ( !slotOverride )
        goto LABEL_13;
    }
    if ( (**(_BYTE **)v6 & 2) == 0 || *(_DWORD *)(slotOverride + 4) == 4 )
    {
      putValue = (int *)slotOverride;
    }
    else
    {
      sendResultType = 4;
      sendResultValue = Rules_CreateEphemeralMultifield(1);
      multifieldBegin = 0;
      multifieldEnd = 0;
      *((_WORD *)sendResultValue + 7) = *(_WORD *)(slotOverride + 4);
      sendResultValue[4] = *(_DWORD *)(slotOverride + 8);
      putValue = &sendResult;
    }
    result = (_DWORD *)Instance_PutSlotValue((_DWORD *)theInstance, theSlot, putValue, a3);
    putFailed = result == 0;
LABEL_11:
    if ( putFailed )
      return result;
    goto LABEL_12;
  }
LABEL_13:
  result = (_DWORD *)g_ClipsTrueSymbol;
  *(_DWORD *)(v22 + 8) = g_ClipsTrueSymbol;
  return result;
}
// 4ABAAA: variable 'v11' is possibly undefined
// 4ABAE9: variable 'v7' is possibly undefined
// 4ABB52: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51AD1C: using guessed type int dword_51AD1C;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ABB70) --------------------------------------------------------
_DWORD * Rules_DuplicateInstanceCore(int *returnValue, int msgpass, double a3)
{
  int srcInstance; // ebp
  int newNameSymbol; // ecx
  int slotOverride; // edi
  _DWORD *result; // eax
  int dupInstance; // esi
  int *v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  bool putFailed; // zf
  int v13; // ecx
  int localSlotOffset; // edi
  int *putValue; // eax
  _DWORD *srcSlotValue; // eax
  unsigned int slotIndex; // edx
  int slotTableOffset; // eax
  int slotValue; // ecx
  char instanceFlags; // bh
  int v21; // edx
  int sendResult; // [esp+0h] [ebp-54h] BYREF
  int sendResultType; // [esp+4h] [ebp-50h]
  _DWORD *sendResultValue; // [esp+8h] [ebp-4Ch]
  int multifieldBegin; // [esp+Ch] [ebp-48h]
  int multifieldEnd; // [esp+10h] [ebp-44h]
  __int16 exprType; // [esp+18h] [ebp-3Ch] BYREF
  int exprValue; // [esp+1Ah] [ebp-3Ah]
  int exprArgList; // [esp+1Eh] [ebp-36h]
  int exprNext; // [esp+22h] [ebp-32h]
  int msgpassFlag; // [esp+28h] [ebp-2Ch]
  int savedFlag; // [esp+2Ch] [ebp-28h]
  int initExpr; // [esp+30h] [ebp-24h]
  int *v34; // [esp+34h] [ebp-20h]
  unsigned int localSlotIndex; // [esp+38h] [ebp-1Ch]
  int *theSlot; // [esp+3Ch] [ebp-18h]

  v34 = returnValue;
  msgpassFlag = msgpass;
  returnValue[1] = 2;
  v34[2] = g_ClipsFalseSymbol;
  if ( !g_InstanceDirectMessageGuardActive )
  {
    Rules_PrintErrorID((int)aInsmoddp, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDirectMessageD, v10);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  g_InstanceDirectMessageGuardActive = 0;
  srcInstance = *(_DWORD *)(MessageHandler_GetNthArgument(0) + 8);
  MessageHandler_GetNthArgument(1);
  slotOverride = *(_DWORD *)(MessageHandler_GetNthArgument(2) + 8);
  if ( (*(_BYTE *)(srcInstance + 24) & 2) != 0 )
  {
    Instance_ReportInvalidInstanceAddressError();
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  if ( newNameSymbol == *(_DWORD *)(srcInstance + 28) )
  {
    Rules_PrintErrorID((int)aInsmoddp, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInstanceCopyMu, v11);
    return (_DWORD *)Lexer_ErrorRecover(1);
  }
  savedFlag = g_Instance_UseMessageDispatchForInit;
  g_Instance_UseMessageDispatchForInit = msgpassFlag;
  result = Instance_BuildInstance(newNameSymbol, *(_DWORD *)(srcInstance + 44), 1, a3);
  dupInstance = (int)result;
  g_Instance_UseMessageDispatchForInit = savedFlag;
  if ( result )
  {
    ++result[10];
    if ( slotOverride )
    {
      while ( 1 )
      {
        v8 = (int *)Instance_GetSlotValueBySymbol(dupInstance, *(_DWORD *)slotOverride);
        theSlot = v8;
        if ( !v8 )
        {
          Instance_ReportNoSuchSlotError(v9, (int)aDuplicateInsta);
LABEL_8:
          --*(_DWORD *)(dupInstance + 40);
          Instance_DeleteInstance(dupInstance, a3);
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        if ( !msgpassFlag )
          break;
        exprType = *(_WORD *)(slotOverride + 4);
        if ( exprType == 4 )
          exprValue = slotOverride;
        else
          exprValue = *(_DWORD *)(slotOverride + 8);
        exprArgList = 0;
        exprNext = 0;
        MessageHandler_SendToInstanceAddress(*(_DWORD *)(*theSlot + 12), dupInstance, (int)&exprType, &sendResult, a3);
        if ( g_ClipsEvaluationError )
          goto LABEL_8;
        if ( sendResultType == 2 )
        {
          putFailed = sendResultValue == (_DWORD *)g_ClipsFalseSymbol;
          goto LABEL_19;
        }
LABEL_20:
        *((_BYTE *)theSlot + 4) |= 2u;
        slotOverride = *(_DWORD *)(slotOverride + 20);
        if ( !slotOverride )
          goto LABEL_21;
      }
      if ( (*(_BYTE *)*v8 & 2) == 0 || *(_DWORD *)(slotOverride + 4) == 4 )
      {
        putValue = (int *)slotOverride;
      }
      else
      {
        sendResultType = 4;
        sendResultValue = Rules_CreateEphemeralMultifield(1);
        multifieldBegin = 0;
        multifieldEnd = 0;
        *((_WORD *)sendResultValue + 7) = *(_WORD *)(slotOverride + 4);
        sendResultValue[4] = *(_DWORD *)(slotOverride + 8);
        putValue = &sendResult;
      }
      putFailed = Instance_PutSlotValue((_DWORD *)dupInstance, theSlot, putValue, a3) == 0;
LABEL_19:
      if ( putFailed )
        goto LABEL_8;
      goto LABEL_20;
    }
LABEL_21:
    v13 = 0;
    localSlotOffset = 0;
    localSlotIndex = 0;
    while ( 1 )
    {
      if ( localSlotIndex >= *(_DWORD *)(*(_DWORD *)(dupInstance + 44) + 68) )
      {
        if ( msgpassFlag )
        {
          slotIndex = 0;
          slotTableOffset = 0;
          while ( slotIndex < *(_DWORD *)(*(_DWORD *)(dupInstance + 44) + 72) )
          {
            slotValue = *(_DWORD *)(*(_DWORD *)(dupInstance + 72) + slotTableOffset);
            slotTableOffset += 4;
            ++slotIndex;
            *(_BYTE *)(slotValue + 4) |= 2u;
          }
          *(_BYTE *)(dupInstance + 24) |= 4u;
          savedFlag = g_Instance_SlotInitInProgress;
          g_Instance_SlotInitInProgress = 1;
          MessageHandler_SendToInstanceAddress(g_MessageHandler_InitSymbol, dupInstance, 0, v34, a3);
          g_Instance_SlotInitInProgress = savedFlag;
        }
        instanceFlags = *(_BYTE *)(dupInstance + 24);
        --*(_DWORD *)(dupInstance + 40);
        if ( (instanceFlags & 2) != 0 )
        {
          v34[1] = 2;
          v34[2] = g_ClipsFalseSymbol;
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        else
        {
          v34[1] = 8;
          result = Instance_GetQualifiedName(dupInstance, v13);
          *(_DWORD *)(v21 + 8) = result;
        }
        return result;
      }
      if ( (*(_BYTE *)(localSlotOffset + *(_DWORD *)(dupInstance + 76) + 4) & 2) != 0 )
      {
LABEL_24:
        localSlotOffset += 12;
        ++localSlotIndex;
      }
      else if ( msgpassFlag )
      {
        sendResultType = *(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 4) << 24 >> 26;
        srcSlotValue = *(_DWORD **)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 8);
        sendResultValue = srcSlotValue;
        if ( sendResultType == 4 )
        {
          multifieldBegin = 0;
          multifieldEnd = *(_DWORD *)((char *)srcSlotValue + 6) - 1;
        }
        initExpr = AST_BuildExpressionFromValue(&sendResult);
        MessageHandler_SendToInstanceAddress(*(_DWORD *)(*(_DWORD *)(localSlotOffset + *(_DWORD *)(dupInstance + 76)) + 12), dupInstance, initExpr, &sendResult, a3);
        AST_Free(initExpr);
        if ( g_ClipsEvaluationError )
          goto LABEL_8;
        if ( sendResultType != 2 )
          goto LABEL_24;
        if ( sendResultValue == (_DWORD *)g_ClipsFalseSymbol )
          goto LABEL_8;
        localSlotOffset += 12;
        ++localSlotIndex;
      }
      else
      {
        sendResultType = *(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 4) << 24 >> 26;
        sendResultValue = *(_DWORD **)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 8);
        if ( (*(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 4) & 0xFC) == 0x10 )
        {
          multifieldBegin = 0;
          multifieldEnd = *(_DWORD *)(*(_DWORD *)(localSlotOffset + *(_DWORD *)(srcInstance + 76) + 8) + 6) - 1;
        }
        if ( !Instance_PutSlotValue((_DWORD *)dupInstance, (int *)(localSlotOffset + *(_DWORD *)(dupInstance + 76)), &sendResult, a3) )
          goto LABEL_8;
        localSlotOffset += 12;
        ++localSlotIndex;
      }
    }
  }
  return result;
}
// 4ABBD9: variable 'v4' is possibly undefined
// 4ABC3A: variable 'v9' is possibly undefined
// 4ABC7B: variable 'v10' is possibly undefined
// 4ABCCB: variable 'v11' is possibly undefined
// 4ABFB3: variable 'v13' is possibly undefined
// 4ABFB8: variable 'v21' is possibly undefined
// 51A27C: using guessed type int dword_51A27C;
// 51A284: using guessed type int dword_51A284;
// 51A614: using guessed type char *off_51A614[5];
// 51A964: using guessed type int dword_51A964;
// 51AD1C: using guessed type int dword_51AD1C;
// 51AD34: using guessed type int dword_51AD34;
// 54DD70: using guessed type int dword_54DD70;

//----- (004ABFD0) --------------------------------------------------------
signed int Rules_RegisterInstanceIOCommands(void)
{
  Rules_RegisterHostFunction(aSaveInstances, 108, (int)aSaveinstancesc, (int)Rules_SaveInstancesCommand, (int)a1Wk_0);
  Rules_RegisterHostFunction(aLoadInstances, 108, (int)aLoadinstancesc, (int)Rules_LoadInstancesCommand, (int)a11k_3);
  Rules_RegisterHostFunction(aRestoreInstanc, 108, (int)aRestoreinstanc, (int)Rules_RestoreInstancesCommand, (int)a11k_3);
  Rules_RegisterHostFunction(aBsaveInstances, 108, (int)aBinarysaveinst, (int)Rules_BsaveInstancesCommand, (int)a1Wk_0);
  return Rules_RegisterHostFunction(aBloadInstances, 108, (int)aBinaryloadinst, (int)Rules_BloadInstancesCommand, (int)a11k_3);
}

//----- (004AC070) --------------------------------------------------------
signed int  Rules_SaveInstancesCommand(double a1)
{
  return Rules_ParseSaveInstancesArgsAndDispatch((int (*)(void))Rules_SaveInstancesTextFile, a1);
}

//----- (004AC090) --------------------------------------------------------
signed int  Rules_LoadInstancesCommand(int a1, DWORD a2, double a3)
{
  signed int result; // eax
  int v4; // ecx
  signed int instancesLoaded; // ebx
  int fileArgValue; // [esp-8h] [ebp-24h] BYREF
  int fileNameSymbol; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, &fileArgValue, 111, a3);
  if ( result )
  {
    instancesLoaded = Rules_ReadInstancesTextFile(*(const CHAR **)(fileNameSymbol + 16), 1, *(_DWORD *)(fileNameSymbol + 16), a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v4, v4);
    return instancesLoaded;
  }
  return result;
}
// 4AC0DD: variable 'v4' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC100) --------------------------------------------------------
signed int  Rules_RestoreInstancesCommand(int a1, DWORD a2, double a3)
{
  signed int result; // eax
  int v4; // ecx
  signed int instancesLoaded; // ebx
  int fileArgValue; // [esp-8h] [ebp-24h] BYREF
  int fileNameSymbol; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+14h] [ebp-8h]

  v8 = a1;
  result = Lexer_ParseValueList(1, &fileArgValue, 111, a3);
  if ( result )
  {
    instancesLoaded = Rules_ReadInstancesTextFile(*(const CHAR **)(fileNameSymbol + 16), 0, *(_DWORD *)(fileNameSymbol + 16), a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(v4, v4);
    return instancesLoaded;
  }
  return result;
}
// 4AC14A: variable 'v4' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC170) --------------------------------------------------------
signed int  Rules_BloadInstancesCommand(int a1, DWORD a2, double a3)
{
  signed int result; // eax
  int v4; // ecx
  int v5; // edx
  signed int instancesLoaded; // ecx
  _DWORD argBuffer[9]; // [esp-8h] [ebp-24h] BYREF

  argBuffer[7] = a1;
  result = Lexer_ParseValueList(1, argBuffer, 111, a3);
  if ( result )
  {
    instancesLoaded = Rules_BloadInstancesFile(*(const CHAR **)(argBuffer[2] + 16), v4, a2, a3);
    if ( g_ClipsEvaluationError )
      Rules_ReportInstanceFileProcessError(instancesLoaded, v5);
    return instancesLoaded;
  }
  return result;
}
// 4AC1A0: variable 'v4' is possibly undefined
// 4AC1B6: variable 'v5' is possibly undefined
// 4AC1BB: variable 'v6' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (004AC1D0) --------------------------------------------------------
signed int  Rules_BloadInstancesFile(const CHAR *fileName, int a2, DWORD a3, double a4)
{
  int v5; // ecx
  void *v6; // ecx
  int instanceCount; // ecx
  int v8; // edx
  void *v9; // ecx
  void *v11; // ecx
  int v12; // edx
  _DWORD instanceCountBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  instanceCountBuffer[2] = a2;
  if ( Rules_BloadOpenFile(fileName, a3) )
  {
    if ( Rules_ValidateBloadInstancesHeader(v5, v5) )
    {
      Rules_BloadAtomTables();
      g_Rules_BloadBytesConsumed = 0;
      Rules_BloadReadBlock((uintptr_t)&g_ClipsBsaveInstanceDataSpace, 4u);
      Rules_BloadReadBlock((uintptr_t)instanceCountBuffer, 4u);
      instanceCount = instanceCountBuffer[0];
      if ( instanceCountBuffer[0] <= 0 )
      {
LABEL_6:
        Rules_BloadReleaseReadBuffer();
        Rules_FreeBloadAtomTables();
        Rules_BloadCloseFile(v9);
        return instanceCountBuffer[0];
      }
      else
      {
        while ( Rules_BloadReadInstanceRecord(instanceCount, a4) )
        {
          if ( v8 + 1 >= instanceCountBuffer[0] )
            goto LABEL_6;
        }
        Rules_BloadReleaseReadBuffer();
        Rules_FreeBloadAtomTables();
        Rules_BloadCloseFile(v11);
        Lexer_ErrorRecover(1);
        return v12;
      }
    }
    else
    {
      Rules_BloadCloseFile(v6);
      Lexer_ErrorRecover(1);
      return -1;
    }
  }
  else
  {
    Lexer_ErrorRecover(1);
    return -1;
  }
}
// 4AC1EA: variable 'v5' is possibly undefined
// 4AC224: variable 'v7' is possibly undefined
// 4AC230: variable 'v8' is possibly undefined
// 4AC23F: variable 'v9' is possibly undefined
// 4AC25F: variable 'v6' is possibly undefined
// 4AC27F: variable 'v11' is possibly undefined
// 4AC28E: variable 'v12' is possibly undefined
// 54E6EC: using guessed type int dword_54E6EC;
// 54E6F0: using guessed type int dword_54E6F0;

//----- (004AC2A0) --------------------------------------------------------
_DWORD * Rules_SaveInstancesTextFile(const CHAR *fileName, int saveCode, DWORD inheritFlag, int classExpressionList, double a5)
{
  _DWORD *result; // eax
  _DWORD *classList; // edi
  int v8; // ecx
  int filePtr; // eax
  int v10; // ecx
  int v11; // ecx
  int instanceCount; // ebp
  int v13; // ecx
  int savedPreserveEscapes; // [esp+0h] [ebp-24h]
  int savedAddressesToStrings; // [esp+4h] [ebp-20h]
  int savedInstancesToNames; // [esp+8h] [ebp-1Ch]

  result = Rules_BuildClassListForSave((int)aSaveInstances, classExpressionList, inheritFlag, saveCode, a5);
  classList = result;
  if ( result || !classExpressionList )
  {
    Rules_ForEachInstanceForSave(saveCode, inheritFlag, (int)result, 1, 0);
    filePtr = IO_FOpen(fileName, (unsigned __int8 *)aW_5, v8, inheritFlag);
    if ( filePtr )
    {
      savedPreserveEscapes = g_Print_PreserveEscapedCharactersFlag;
      g_Print_PreserveEscapedCharactersFlag = 1;
      savedAddressesToStrings = g_Print_AddressesToStringsFlag;
      g_Print_AddressesToStringsFlag = 1;
      savedInstancesToNames = g_Print_InstanceAddressesToNamesFlag;
      g_Print_InstanceAddressesToNamesFlag = 1;
      IO_SetFastSaveFile(filePtr);
      instanceCount = Rules_ForEachInstanceForSave(saveCode, inheritFlag, (int)classList, v11, (void (__fastcall *)(int, int))Rules_WriteInstanceTextRecord);
      fclose_(v13);
      IO_SetFastSaveFile(0);
      g_Print_PreserveEscapedCharactersFlag = savedPreserveEscapes;
      g_Print_AddressesToStringsFlag = savedAddressesToStrings;
      g_Print_InstanceAddressesToNamesFlag = savedInstancesToNames;
      Rules_FreeClassList(classList);
      return (_DWORD *)instanceCount;
    }
    else
    {
      Rules_OpenFileErrorMessage(v10, (int)fileName);
      Rules_FreeClassList(classList);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}
// 4AC2F7: variable 'v8' is possibly undefined
// 4AC30B: variable 'v10' is possibly undefined
// 4AC372: variable 'v11' is possibly undefined
// 4AC37B: variable 'v13' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A5F8: using guessed type int dword_51A5F8;
// 51A5FC: using guessed type int dword_51A5FC;
// 51A600: using guessed type int dword_51A600;

//----- (004AC3C0) --------------------------------------------------------
signed int  Rules_BsaveInstancesCommand(double a1)
{
  return Rules_ParseSaveInstancesArgsAndDispatch((int (*)(void))Rules_SaveInstancesBinaryFile, a1);
}

//----- (004AC3E0) --------------------------------------------------------
_DWORD * Rules_SaveInstancesBinaryFile(const CHAR *fileName, int saveCode, DWORD inheritFlag, int classExpressionList, double a5)
{
  _DWORD *result; // eax
  _DWORD *classList; // edi
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int fp; // esi
  int v13; // edx
  int v14; // ecx
  int instancesSaved; // [esp+0h] [ebp-18h] BYREF
  const CHAR *v16; // [esp+4h] [ebp-14h]
  int v17; // [esp+8h] [ebp-10h]

  v16 = fileName;
  v17 = saveCode;
  result = Rules_BuildClassListForSave((int)aBsaveInstances, classExpressionList, inheritFlag, saveCode, a5);
  classList = result;
  if ( result || !classExpressionList )
  {
    g_ClipsBsaveInstanceDataSpace = 0;
    Rules_ClearAtomInUseMarks();
    instancesSaved = Rules_ForEachInstanceForSave(v17, inheritFlag, (int)classList, v8, Compiler_MarkAndEmit);
    v10 = IO_FOpen(v16, (unsigned __int8 *)aWb_5, v9, inheritFlag);
    fp = v10;
    if ( v10 )
    {
      Compiler_WriteHeaders(v10);
      Rules_BsaveAtomTables(fp);
      fwrite_(&g_ClipsBsaveInstanceDataSpace, v13, fp, 1);
      fwrite_(&instancesSaved, 4, fp, 1);
      Rules_SetAtomicValueIndices(0);
      Rules_ForEachInstanceForSave(v17, inheritFlag, (int)classList, 0, (void (__fastcall *)(int, int))Compiler_WriteInstanceRecord);
      Rules_RestoreAtomicValueBuckets();
      fclose_(v14);
      Rules_FreeClassList(classList);
      return (_DWORD *)instancesSaved;
    }
    else
    {
      Rules_OpenFileErrorMessage(v11, (int)v16);
      Rules_FreeClassList(classList);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  return result;
}
// 4AC42E: variable 'v8' is possibly undefined
// 4AC43F: variable 'v9' is possibly undefined
// 4AC453: variable 'v11' is possibly undefined
// 4AC48F: variable 'v13' is possibly undefined
// 4AC4CB: variable 'v14' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54E6EC: using guessed type int dword_54E6EC;

//----- (004AC4F0) --------------------------------------------------------
signed int  Rules_ParseSaveInstancesArgsAndDispatch(int (*saveFunction)(void), double a2)
{
  int saveCode; // ebp
  signed int result; // eax
  int v4; // ecx
  int v5; // ecx
  int classExpr; // edi
  _DWORD argBuffer[7]; // [esp+0h] [ebp-38h] BYREF
  int (*v8)(void); // [esp+1Ch] [ebp-1Ch]
  int inheritFlag; // [esp+20h] [ebp-18h]

  v8 = saveFunction;
  saveCode = 1;
  inheritFlag = 0;
  result = Lexer_ParseValueList(1, argBuffer, 111, a2);
  if ( result )
  {
    argBuffer[6] = *(_DWORD *)(argBuffer[2] + 16);
    if ( Rules_RtnArgCount() <= 1 )
      return ((int (__fastcall *)(int, int))v8)(inheritFlag, saveCode);
    if ( Lexer_ParseValueList(2, argBuffer, 2, a2) )
    {
      if ( !strcmp_(v4, aLocal_1) )
      {
LABEL_5:
        classExpr = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
        if ( classExpr && *(_DWORD *)(classExpr + 10) && *(_WORD *)classExpr == 2 && !strcmp_(v5, aInherit_3) )
          inheritFlag = 1;
        return ((int (__fastcall *)(int, int))v8)(inheritFlag, saveCode);
      }
      if ( !strcmp_(v5, aVisible_0) )
      {
        saveCode = 2;
        goto LABEL_5;
      }
    }
    Parser_ReportError(2, (int)aSymbolLocalOrV);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 4AC560: variable 'v4' is possibly undefined
// 4AC59E: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (004AC620) --------------------------------------------------------
_DWORD * Rules_BuildClassListForSave(int functionName, int classExprs, int inheritFlag, int saveCode, double a5)
{
  _DWORD *classListHead; // ebp
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  char *expectedClassKind; // ebx
  int *v13; // eax
  int theDefclass; // ebx
  _DWORD *listCursor; // ecx
  _DWORD *i; // edx
  int existingClass; // eax
  int *freeNode; // ecx
  _DWORD *newNode; // eax
  int v20; // ecx
  int nextFree; // eax
  _DWORD argValue[2]; // [esp+0h] [ebp-38h] BYREF
  int argSymbol; // [esp+8h] [ebp-30h]
  int v24; // [esp+18h] [ebp-20h]
  int currentModule; // [esp+1Ch] [ebp-1Ch]
  int v26; // [esp+20h] [ebp-18h]
  int argIndex; // [esp+24h] [ebp-14h]
  int memoryTable; // [esp+28h] [ebp-10h]

  v24 = functionName;
  v26 = saveCode;
  classListHead = 0;
  argIndex = (inheritFlag != 0) + 3;
  currentModule = Module_GetCurrent();
  if ( !v9 )
    return classListHead;
  while ( !Parser_ParseForm((__int16 *)classExprs, argValue, v8, a5) && argValue[1] == 2 )
  {
    v13 = v26 == 1 ? Class_LookupByModule(v10, *(_BYTE **)(argSymbol + 16)) : Class_LookupInScope(*(_BYTE **)(argSymbol + 16));
    theDefclass = (int)v13;
    if ( !v13 || (v13[5] & 4) != 0 && !inheritFlag )
      break;
    listCursor = classListHead;
    for ( i = classListHead; listCursor; listCursor = (_DWORD *)listCursor[5] )
    {
      existingClass = listCursor[2];
      if ( theDefclass == existingClass || inheritFlag && (Class_HasSuperclass(existingClass, theDefclass) || Class_HasSuperclass(theDefclass, *(_DWORD *)(v20 + 8))) )
        goto LABEL_3;
      i = listCursor;
    }
    freeNode = *(int **)(g_ClipsMemoryTable + 96);
    memoryTable = g_ClipsMemoryTable;
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = (int)freeNode;
      nextFree = *freeNode;
      v8 = memoryTable;
      *(_DWORD *)(memoryTable + 96) = nextFree;
      newNode = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newNode = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    newNode[1] = 57;
    newNode[5] = 0;
    newNode[2] = theDefclass;
    if ( i )
      i[5] = newNode;
    else
      classListHead = newNode;
    classExprs = *(_DWORD *)(classExprs + 10);
    ++argIndex;
    if ( !classExprs )
      return classListHead;
  }
LABEL_3:
  if ( inheritFlag )
    expectedClassKind = aValidClassName;
  else
    expectedClassKind = aValidConcreteC;
  Parser_ReportError(argIndex, (int)expectedClassKind);
  Rules_FreeClassList(classListHead);
  Lexer_ErrorRecover(1);
  return 0;
}
// 4AC650: variable 'v9' is possibly undefined
// 4AC65A: variable 'v8' is possibly undefined
// 4AC6B6: variable 'v10' is possibly undefined
// 4AC6DE: variable 'v15' is possibly undefined
// 4AC759: variable 'v20' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AC7A0) --------------------------------------------------------
_DWORD * Rules_FreeClassList(_DWORD *result)
{
  _DWORD *classNode; // edx

  for ( ; result; *(_DWORD *)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp )
  {
    classNode = result;
    result = (_DWORD *)result[5];
    g_ClipsMemFreeListTemp = (int)classNode;
    *classNode = *(_DWORD *)(g_ClipsMemoryTable + 96);
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004AC7E0) --------------------------------------------------------
int  Rules_ForEachInstanceForSave(int saveCode, int inheritFlag, int classList, int interruptOK, void (__fastcall *saveFunction)(int, int))
{
  int instanceCount; // esi
  int classCursor; // ebp
  int subtreeCount; // eax
  int theInstance; // ecx
  signed int traversalID; // [esp+0h] [ebp-1Ch]
  int currentModule; // [esp+Ch] [ebp-10h]

  currentModule = Module_GetCurrent();
  instanceCount = 0;
  if ( classList )
  {
    traversalID = Class_NewTraversalID();
    if ( traversalID != -1 )
    {
      classCursor = classList;
      do
      {
        if ( g_ClipsHaltExecution && interruptOK )
          break;
        subtreeCount = Rules_ForEachInstanceInClassSubtree(currentModule, *(_DWORD *)(classCursor + 8), saveCode, inheritFlag, traversalID, saveFunction);
        classCursor = *(_DWORD *)(classCursor + 20);
        instanceCount += subtreeCount;
      }
      while ( classCursor );
      Class_ReleaseTraversalID();
    }
  }
  else
  {
    theInstance = Rules_GetNextInstanceInScope(0);
    if ( theInstance )
    {
      while ( g_ClipsHaltExecution != 1 )
      {
        if ( saveCode == 2 || **(_DWORD **)(*(_DWORD *)(theInstance + 44) + 8) == currentModule )
        {
          if ( saveFunction )
            saveFunction(theInstance, theInstance);
          ++instanceCount;
        }
        theInstance = Rules_GetNextInstanceInScope(theInstance);
        if ( !theInstance )
          return instanceCount;
      }
    }
  }
  return instanceCount;
}
// 4AC810: conditional instruction was optimized away because ebx.4!=0
// 4AC891: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (004AC8C0) --------------------------------------------------------
int  Rules_ForEachInstanceInClassSubtree(
        int currentModule,
        int theDefclass,
        int saveCode,
        int inheritFlag,
        signed int traversalID,
        void (__fastcall *saveFunction)(int, int))
{
  int traversalMarkAddr; // ebx
  int traversalMask; // eax
  int instanceCount; // edi
  int i; // ecx
  unsigned int subclassIndex; // [esp+Ch] [ebp-14h]
  int subclassOffset; // [esp+10h] [ebp-10h]

  traversalMarkAddr = theDefclass + ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3);
  traversalMask = 1 << (traversalID % 8);
  instanceCount = 0;
  if ( (*(_BYTE *)(traversalMarkAddr + 108) & (unsigned __int8)traversalMask) != 0 )
    return 0;
  *(_BYTE *)(traversalMarkAddr + 108) |= traversalMask;
  if ( saveCode == 1 && currentModule == **(_DWORD **)(theDefclass + 8) || saveCode == 2 && Class_IsInScope(theDefclass, currentModule) )
  {
    for ( i = Rules_GetNextInstanceInClass(theDefclass, 0); i; i = Rules_GetNextInstanceInClass(theDefclass, i) )
    {
      if ( saveFunction )
        saveFunction(i, i);
      ++instanceCount;
    }
  }
  if ( inheritFlag )
  {
    subclassIndex = 0;
    subclassOffset = 0;
    while ( *(unsigned __int16 *)(theDefclass + 40) > subclassIndex )
    {
      instanceCount += Rules_ForEachInstanceInClassSubtree(currentModule, *(_DWORD *)(subclassOffset + *(_DWORD *)(theDefclass + 42)), saveCode, 1, traversalID, saveFunction);
      subclassOffset += 4;
      ++subclassIndex;
    }
  }
  return instanceCount;
}
// 4AC959: variable 'i' is possibly undefined

//----- (004ACA00) --------------------------------------------------------
signed int  Rules_WriteInstanceTextRecord(int logicalName, int theInstance)
{
  int v3; // ecx
  int v4; // ecx
  unsigned int slotIndex; // edi
  int slotOffset; // ebp
  int v7; // ecx
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  Output_Write(logicalName, (int)asc_508EB0, logicalName);
  Output_Write(v3, *(_DWORD *)(*(_DWORD *)(theInstance + 28) + 16), v3);
  Output_Write(v4, (int)aOf_1, v4);
  slotIndex = 0;
  slotOffset = 0;
  Output_Write(v7, *(_DWORD *)(**(_DWORD **)(theInstance + 44) + 16), v7);
  while ( slotIndex < *(_DWORD *)(*(_DWORD *)(theInstance + 44) + 72) )
  {
    Output_Write(logicalName, (int)asc_508EBC, *(_DWORD *)(*(_DWORD *)(theInstance + 72) + slotOffset));
    Output_Write(logicalName, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v10 + 8) + 12) + 16), v10);
    if ( (*(_DWORD *)(v11 + 4) & 0xFC) == 0x10 )
    {
      if ( *(_DWORD *)(*(_DWORD *)(v11 + 8) + 6) )
      {
        Output_Write(logicalName, (int)asc_508EC4, v11);
        Lexer_OutputFieldRange(logicalName, *(_DWORD *)(v13 + 8), *(_DWORD *)(*(_DWORD *)(v13 + 8) + 6) - 1, 0, 0);
      }
    }
    else
    {
      Output_Write(logicalName, (int)asc_508EC4, v11);
      Rules_PrintAtomValue(logicalName, *(_DWORD *)(v12 + 4) << 24 >> 26, *(int **)(v12 + 8));
    }
    Output_Write(logicalName, (int)asc_508EC8, v11);
    slotOffset += 4;
    ++slotIndex;
  }
  return Output_Write(logicalName, (int)asc_508ECC, v8);
}
// 4ACA24: variable 'v3' is possibly undefined
// 4ACA30: variable 'v4' is possibly undefined
// 4ACA46: variable 'v7' is possibly undefined
// 4ACA5D: variable 'v8' is possibly undefined
// 4ACA80: variable 'v10' is possibly undefined
// 4ACA92: variable 'v11' is possibly undefined
// 4ACAAC: variable 'v12' is possibly undefined
// 4ACAE9: variable 'v13' is possibly undefined
