/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004A8570) --------------------------------------------------------
int  Rules_CountJoinNetworkEntryNodes(int theJoin)
{
  int count; // edx

  count = 0;
  if ( !theJoin )
    return count;
  do
  {
    while ( (*(_BYTE *)theJoin & 4) != 0 )
    {
      theJoin = *(_DWORD *)(theJoin + 16);
      if ( !theJoin )
        return count;
    }
    ++count;
    theJoin = *(_DWORD *)(theJoin + 24);
  }
  while ( theJoin );
  return count;
}

//----- (004A85A0) --------------------------------------------------------
signed int Rules_PrintJoinNetworkSharingReport(void)
{
  int v0; // edx
  signed int v1; // ecx

  Rules_ClearJoinNetworkMarkedFlags();
  return Rules_PrintJoinNetworkNodeRuleOwners(v1, v0);
}
// 4A85AC: variable 'v1' is possibly undefined
// 4A85AC: variable 'v0' is possibly undefined

//----- (004A85C0) --------------------------------------------------------
signed int  Rules_PrintJoinNetworkNodeRuleOwners(signed int result, int linePrefix)
{
  uintptr_t node; // ecx
  int rule_name; // esi

  node = (uintptr_t)(unsigned int)result;
  while ( node )
  {
    while ( node && (*(_BYTE *)node & 0x20) != 0 )
      node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 28);
    if ( !node )
      return result;
    if ( *(_DWORD *)(node + 36) )
    {
      *(_BYTE *)node |= 0x20u;
      rule_name = Rules_GetConstructNameString(*(_DWORD *)(node + 36));
      Output_Write((int)g_IO_LogicalNameTable_WError[0], linePrefix, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], rule_name, 0);
      result = Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_5083B4, 0);
      node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 28);
    }
    else
    {
      *(_BYTE *)node |= 0x20u;
      result = Rules_PrintJoinNetworkNodeRuleOwners(*(_DWORD *)(node + 20), linePrefix);
      node = (uintptr_t)(unsigned int)*(_DWORD *)(node + 28);
    }
  }
  return result;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004A8650) --------------------------------------------------------
int Rules_ClearJoinNetworkMarkedFlags(void)
{
  int i; // esi
  int theDefrule; // ebx
  uintptr_t node; // eax
  unsigned int flags; // edx
  int next_rule; // edx

  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    theDefrule = Rules_GetNextDefrule(0);
    while ( theDefrule )
    {
      node = (uintptr_t)(unsigned int)*(_DWORD *)(theDefrule + 44);
      while ( node )
      {
        flags = *(_DWORD *)node & 0xFFFFFFDF;
        *(_DWORD *)node = flags;
        node = (uintptr_t)(unsigned int)*(_DWORD *)(node + ((*(_BYTE *)node & 4) != 0 ? 16 : 24));
      }
      next_rule = *(_DWORD *)(theDefrule + 48);
      if ( next_rule )
        theDefrule = next_rule;
      else
        theDefrule = Rules_GetNextDefrule(theDefrule);
    }
  }
  return Module_EndEnum();
}

//----- (004A86F0) --------------------------------------------------------
int  Rules_JoinNetworkAssignCodeGenIds(_DWORD *moduleCount, int *ruleCount, int *joinCount)
{
  int result; // eax
  int i; // edi
  _DWORD *theDefrule; // ecx
  int currentRuleId; // eax
  int joinPtr; // eax
  int currentJoinId; // edx
  int nextJoin; // edx

  *moduleCount = 0;
  *ruleCount = 0;
  *joinCount = 0;
  Rules_ClearJoinNetworkMarkedFlags();
  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ++*moduleCount;
    Module_SetCurrent(i);
    theDefrule = (_DWORD *)Rules_GetNextDefrule(0);
    while ( theDefrule )
    {
      currentRuleId = *ruleCount;
      theDefrule[3] = *ruleCount;
      *ruleCount = currentRuleId + 1;
      joinPtr = theDefrule[11];
      if ( joinPtr )
      {
        do
        {
          if ( (*(_BYTE *)joinPtr & 0x20) == 0 )
          {
            *(_BYTE *)joinPtr |= 0x20u;
            currentJoinId = *joinCount;
            *(_DWORD *)(joinPtr + 4) = *joinCount;
            *joinCount = currentJoinId + 1;
          }
          if ( (*(_BYTE *)joinPtr & 4) != 0 )
            nextJoin = *(_DWORD *)(joinPtr + 16);
          else
            nextJoin = *(_DWORD *)(joinPtr + 24);
          joinPtr = nextJoin;
        }
        while ( nextJoin );
      }
      if ( theDefrule[12] )
        theDefrule = (_DWORD *)theDefrule[12];
      else
        theDefrule = (_DWORD *)Rules_GetNextDefrule((int)theDefrule);
    }
    result = Module_NextEnum(i);
  }
  return result;
}

//----- (004A87A0) --------------------------------------------------------
int Rules_DefruleCommandDefinitions(void)
{
  Rules_AddResetFunction((int)aDefrule_0, (int)Rules_ResetDefrules, 70);
  Rules_AddSaveFunction((int)aDefrule_0, (int)Rules_SaveDefrules, 0);
  Rules_AddClearReadyFunction((int)aDefrule_0, (int)Rules_ClearDefrulesReady, 0);
  Rules_AddClearFunction((int)aDefrule_0, (int)Rules_ClearDefrules, 0);
  Rules_AddWatchItem((int)aRules, 0, 70, (int)&g_WatchRulesFlag, (int)Rules_DefruleWatchAccess, (int)Rules_DefruleWatchPrint);
  Rules_RegisterHostFunction(aGetDefruleList, 109, (int)aGetdefrulelist, (int)Rules_GetDefruleListFunction, (int)a01w_4);
  Rules_RegisterHostFunction(aUndefrule, 118, (int)aUndefrulecomma, (int)Rules_UndefruleCommand, (int)a11w_7);
  Rules_RegisterHostFunction(aDefruleModule, 119, (int)aDefrulemodulef, (int)Rules_DefruleModuleFunction, (int)a11w_7);
  Rules_RegisterHostFunction(aRules, 118, (int)aListdefrulesco, (int)Rules_ListDefrulesCommand, (int)a01w_4);
  Rules_RegisterHostFunction(aListDefrules, 118, (int)aListdefrulesco, (int)Rules_ListDefrulesCommand, (int)a01w_4);
  Rules_RegisterHostFunction(aPpdefrule, 118, (int)aPpdefrulecomma, (int)Rules_PPDefruleCommand, (int)a11w_7);
  Rules_RegisterDefruleBinaryItem();
  return Rules_SetupDefruleCodeGenerator();
}
// 4A88D0: using guessed type int sub_4A88D0();
// 4A8920: using guessed type int sub_4A8920();
// 51AD08: using guessed type int dword_51AD08;

//----- (004A88D0) --------------------------------------------------------
int Rules_ResetDefrules(void)
{
  int *mainModule; // eax

  g_Rules_EntityTimeTagCounter = 0;
  Rules_ClearFocusStack();
  mainModule = Module_FindByName(aMain_4);
  return Rules_PushFocus((int)mainModule);
}
// 4A88D0: using guessed type int sub_4A88D0();
// 51A998: using guessed type int dword_51A998;

//----- (004A88F0) --------------------------------------------------------
int Rules_ClearDefrulesReady(void)
{
  int result; // eax
  int v1; // edx

  if ( g_Rules_CurrentlyExecutingRule )
    return 0;
  Rules_ClearFocusStack();
  result = Module_GetCurrent();
  if ( result )
  {
    result = 1;
    g_Rules_EntityTimeTagCounter = v1;
  }
  return result;
}
// 4A8912: variable 'v1' is possibly undefined
// 51A1F0: using guessed type int dword_51A1F0;
// 51A998: using guessed type int dword_51A998;

//----- (004A8920) --------------------------------------------------------
int Rules_ClearDefrules(void)
{
  int *mainModule; // eax

  mainModule = Module_FindByName(aMain_4);
  return Rules_PushFocus((int)mainModule);
}
// 4A8920: using guessed type int sub_4A8920();

//----- (004A8930) --------------------------------------------------------
int  Rules_SaveDefrules(signed int logicalName)
{
  return Rules_SaveConstruct(logicalName, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8940) --------------------------------------------------------
int __thiscall Rules_UndefruleCommand(void *this)
{
  return Rules_UndefconstructCommand((int)this, g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8960) --------------------------------------------------------
int  Rules_DeleteDefruleOrAll(int theDefrule, int a2)
{
  return Rules_DeleteConstructOrAll(theDefrule, g_DefruleConstructTypePtr, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8970) --------------------------------------------------------
_DWORD * Rules_GetDefruleListFunction(int returnValue, double a2)
{
  return Rules_GetConstructListCommand(returnValue, g_DefruleConstructTypePtr, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A89B0) --------------------------------------------------------
int __thiscall Rules_DefruleModuleFunction(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A89D0) --------------------------------------------------------
int __thiscall Rules_PPDefruleCommand(void *this)
{
  return Rules_PPConstructCommand((int)this, (const char **)g_DefruleConstructTypePtr);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8A00) --------------------------------------------------------
int  Rules_ListDefrulesCommand(int a1, double a2)
{
  return Rules_ListConstructsCommand(g_DefruleConstructTypePtr, a1, a2);
}
// 54E648: using guessed type int dword_54E648;

//----- (004A8A40) --------------------------------------------------------
int  Rules_TestInheritedFlagBit4(int theDefrule)
{
  if ( !theDefrule )
    return 0;
  while ( (*(_BYTE *)(theDefrule + 29) & 0x10) == 0 )
  {
    theDefrule = *(_DWORD *)(theDefrule + 48);
    if ( !theDefrule )
      return 0;
  }
  return 1;
}

//----- (004A8A60) --------------------------------------------------------
int  Rules_TestInheritedFlagBit5(int theDefrule)
{
  if ( !theDefrule )
    return 0;
  while ( (*(_BYTE *)(theDefrule + 29) & 0x20) == 0 )
  {
    theDefrule = *(_DWORD *)(theDefrule + 48);
    if ( !theDefrule )
      return 0;
  }
  return 1;
}

//----- (004A8A80) --------------------------------------------------------
int  Rules_SetInheritedFlagBit4(char newState, int theDefrule)
{
  int result; // eax

  for ( result = theDefrule; result; result = *(_DWORD *)(result + 48) )
  {
    *(_BYTE *)(result + 29) &= ~0x10u;
    *(_DWORD *)(result + 28) |= (newState & 1) << 12;
  }
  return result;
}

//----- (004A8AB0) --------------------------------------------------------
int  Rules_SetInheritedFlagBit5(char newState, int theDefrule)
{
  int result; // eax

  for ( result = theDefrule; result; result = *(_DWORD *)(result + 48) )
  {
    *(_BYTE *)(result + 29) &= ~0x20u;
    *(_DWORD *)(result + 28) |= (newState & 1) << 13;
  }
  return result;
}

//----- (004A8AE0) --------------------------------------------------------
signed int  Rules_DefruleWatchAccess(int code, int newState, int argExprs, double a4)
{
  if ( code )
    return Rules_ApplyWatchFlagCommand(g_DefruleConstructTypePtr, newState, (int)Rules_TestInheritedFlagBit4, argExprs, a4, (void (*)(void))Rules_SetInheritedFlagBit4);
  else
    return Rules_ApplyWatchFlagCommand(g_DefruleConstructTypePtr, newState, (int)Rules_TestInheritedFlagBit5, argExprs, a4, (void (*)(void))Rules_SetInheritedFlagBit5);
}
// 4A8A40: using guessed type int sub_4A8A40();
// 4A8A60: using guessed type int sub_4A8A60();
// 54E648: using guessed type int dword_54E648;

//----- (004A8B20) --------------------------------------------------------
signed int  Rules_DefruleWatchPrint(int logicalName, int argExprs, double a3)
{
  return Rules_ListWatchFlagStatus(g_DefruleConstructTypePtr, logicalName, (int)Rules_TestInheritedFlagBit4, argExprs, a3, (void (*)(void))Rules_SetInheritedFlagBit4);
}
// 4A8A40: using guessed type int sub_4A8A40();
// 54E648: using guessed type int dword_54E648;

//----- (004A8B40) --------------------------------------------------------
int  Rules_AppendConstructToModuleList(int result)
{
  int theModuleItem; // edx
  int lastItem; // ecx

  theModuleItem = *(_DWORD *)(result + 8);
  lastItem = *(_DWORD *)(theModuleItem + 8);
  if ( lastItem )
    *(_DWORD *)(lastItem + 16) = result;
  else
    *(_DWORD *)(theModuleItem + 4) = result;
  *(_DWORD *)(*(_DWORD *)(result + 8) + 8) = result;
  *(_DWORD *)(result + 16) = 0;
  return result;
}

//----- (004A8B80) --------------------------------------------------------
int __fastcall Rules_TryDeleteConstruct(int theConstruct, int constructClass)
{
  int v4; // ecx

  if ( Rules_IsBloaded() == 1 )
    return 0;
  if ( (*(int (__cdecl **)(int))(constructClass + 12))(theConstruct) )
    return (*(int (**)(void))(constructClass + 40))();
  if ( strcmp_(v4, v4) )
    return 0;
  (*(void (**)(void))(constructClass + 40))();
  return 1;
}
// 4A8BA5: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A8BD0) --------------------------------------------------------
int  Rules_FindConstructByNameGeneric(_BYTE *constructName, int constructClass)
{
  _BYTE *local_name; // eax
  int *target_symbol; // ebx
  int get_name_func; // [ecx+10h]
  int next_func; // [ecx+1Ch]
  int current_item; // edx

  Module_BeginEnum();
  local_name = (_BYTE *)Rules_ExtractModuleAndConstructName(constructName);
  if ( local_name )
  {
    target_symbol = Rules_FindSymbolEntry(local_name);
    if ( target_symbol )
    {
      get_name_func = *(_DWORD *)(constructClass + 16);
      next_func = *(_DWORD *)(constructClass + 28);
      current_item = ((int (*)(int))(uintptr_t)(unsigned int)next_func)(0);
      while ( current_item )
      {
        if ( target_symbol == (int *)((int (*)(int))(uintptr_t)(unsigned int)get_name_func)(current_item) )
        {
          Module_EndEnum();
          return current_item;
        }
        current_item = ((int (*)(int))(uintptr_t)(unsigned int)next_func)(current_item);
      }
    }
  }
  Module_EndEnum();
  return 0;
}

//----- (004A8C30) --------------------------------------------------------
int __fastcall Rules_UndefconstructCommand(int a1, int constructClass)
{
  double v4; // st7
  int v5; // ecx
  int result; // eax
  int theConstruct; // esi
  int v8; // ecx
  int v9; // ecx
  _BYTE argNameBuffer[84]; // [esp+0h] [ebp-5Ch] BYREF
  int v11; // [esp+54h] [ebp-8h]

  v11 = a1;
  v4 = sprintf_(argNameBuffer, "%s name", (const char *)*(_DWORD *)constructClass);
  result = Rules_GetConstructNameArg((int)argNameBuffer, v5, v4);
  theConstruct = result;
  if ( result )
  {
    if ( (*(int (__thiscall **)(int))(constructClass + 12))(result) || !strcmp_(v8, v8) )
    {
      result = Rules_TryDeleteConstruct(v8, constructClass);
      if ( !result )
        return Rules_ReportCantDeleteItem(v9, theConstruct);
    }
    else
    {
      return Rules_ReportCantFindItem(v8, v8);
    }
  }
  return result;
}
// 4A8C53: variable 'v5' is possibly undefined
// 4A8C75: variable 'v8' is possibly undefined
// 4A8C8F: variable 'v9' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A8CB0) --------------------------------------------------------
int __fastcall Rules_PPConstructCommand(int a1, const char **constructClass)
{
  double v4; // st7
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  _BYTE argNameBuffer[84]; // [esp+0h] [ebp-5Ch] BYREF
  int v9; // [esp+54h] [ebp-8h]

  v9 = a1;
  v4 = sprintf_(argNameBuffer, "%s name", *constructClass);
  result = Rules_GetConstructNameArg((int)argNameBuffer, v5, v4);
  if ( result )
  {
    result = Rules_PrintConstructPPForm((int)g_IO_LogicalName_WDisplay, result, (int)constructClass);
    if ( !result )
      return Rules_ReportCantFindItem(v7, v7);
  }
  return result;
}
// 4A8CD3: variable 'v5' is possibly undefined
// 4A8CFA: variable 'v7' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A624: using guessed type char *off_51A624;

//----- (004A8D10) --------------------------------------------------------
int  Rules_PrintConstructPPForm(int logicalName, int constructName, int constructType)
{
  int result; // eax
  char *ppForm; // eax
  signed int v5; // ecx

  result = (*(int (__thiscall **)(int, int))(constructType + 12))(logicalName, constructName);
  if ( result )
  {
    if ( (*(int (**)(void))(constructType + 20))() )
    {
      ppForm = (char *)(*(int (**)(void))(constructType + 20))();
      Output_WriteLongString(v5, ppForm);
    }
    return 1;
  }
  return result;
}
// 4A8D35: variable 'v5' is possibly undefined

//----- (004A8D50) --------------------------------------------------------
int __fastcall Rules_GetConstructModuleCommand(int a1, const char **constructClass)
{
  double v3; // st7
  int v4; // ecx
  _BYTE *constructName; // eax
  int *theModule; // eax
  int v8; // ecx
  _BYTE argNameBuffer[80]; // [esp+0h] [ebp-58h] BYREF
  int v10; // [esp+50h] [ebp-8h]

  v10 = a1;
  v3 = sprintf_(argNameBuffer, "%s name", *constructClass);
  constructName = (_BYTE *)Rules_GetConstructNameArg((int)argNameBuffer, v4, v3);
  if ( !constructName )
    return g_ClipsFalseSymbol;
  theModule = Rules_GetConstructModuleName(constructName, (int)constructName);
  if ( theModule )
    return *theModule;
  Rules_ReportCantFindItem(v8, v8);
  return g_ClipsFalseSymbol;
}
// 4A8D72: variable 'v4' is possibly undefined
// 4A8D9F: variable 'v8' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 54DD70: using guessed type int dword_54DD70;

//----- (004A8DB0) --------------------------------------------------------
int * Rules_GetConstructModuleName(_BYTE *constructName, int a2)
{
  signed int separatorPosition; // eax
  char **v4; // ecx
  signed int *moduleName; // eax
  int *result; // eax
  _DWORD countBuffer[3]; // [esp+0h] [ebp-Ch] BYREF

  countBuffer[1] = a2;
  separatorPosition = Rules_FindModuleSeparator(constructName);
  if ( separatorPosition )
  {
    moduleName = Rules_ExtractModuleName(separatorPosition);
    if ( moduleName )
      return Module_FindByName((_BYTE *)moduleName[4]);
  }
  result = (int *)Rules_FindImportExportConstruct(*v4, countBuffer, constructName, 1, 0);
  if ( result )
    return *(int **)result[2];
  return result;
}
// 4A8DCF: variable 'v4' is possibly undefined

//----- (004A8E00) --------------------------------------------------------
int  Rules_DeleteConstructOrAll(int theConstruct, int constructClass, int a3)
{
  int v4; // ecx
  int success; // esi
  int nextConstruct; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int result; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx

  if ( theConstruct )
  {
    result = (*(int (__cdecl **)(int))(constructClass + 36))(a3);
    if ( result )
    {
      Rules_UnlinkListNode(theConstruct);
      (*(void (**)(void))(v14 + 44))();
      if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
        Rules_RunPeriodicCleanup(1, 0);
      return 1;
    }
  }
  else
  {
    success = 1;
    if ( (*(int (**)(void))(constructClass + 28))() )
    {
      do
      {
        nextConstruct = ((__int64 (*)(void))*(_DWORD *)(v4 + 28))();
        if ( (*(int (**)(void))(v7 + 36))() )
        {
          Rules_UnlinkListNode(v8);
          (*(void (**)(void))(v10 + 44))();
        }
        else
        {
          v12 = (*(int (**)(void))(v9 + 16))();
          success = 0;
          Rules_ReportCantDeleteItem(v13, *(_DWORD *)(v12 + 16));
        }
      }
      while ( nextConstruct );
    }
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      Rules_RunPeriodicCleanup(1, 0);
    return success;
  }
  return result;
}
// 4A8E1F: variable 'v4' is possibly undefined
// 4A8E26: variable 'v7' is possibly undefined
// 4A8E2F: variable 'v8' is possibly undefined
// 4A8E36: variable 'v10' is possibly undefined
// 4A8E6E: variable 'v9' is possibly undefined
// 4A8E78: variable 'v13' is possibly undefined
// 4A8E8F: variable 'v14' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (004A8EC0) --------------------------------------------------------
int  Rules_SaveConstruct(signed int logicalName, int constructClass)
{
  int i; // edi
  char *ppForm; // eax
  int v6; // ecx

  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    while ( (*(int (**)(void))(constructClass + 28))() )
    {
      ppForm = (char *)(*(int (**)(void))(constructClass + 20))();
      if ( ppForm )
      {
        Output_WriteLongString(logicalName, ppForm);
        Output_Write(logicalName, (int)asc_50849C, v6);
      }
    }
  }
  return Module_EndEnum();
}
// 4A8F08: variable 'v6' is possibly undefined

//----- (004A8F40) --------------------------------------------------------
int  Rules_GetConstructNameString(int theConstruct)
{
  return *(_DWORD *)(*(_DWORD *)theConstruct + 16);
}

//----- (004A8F50) --------------------------------------------------------
int  Rules_GetConstructNameSymbol(int theConstruct)
{
  return *(_DWORD *)theConstruct;
}

//----- (004A8F60) --------------------------------------------------------
_DWORD * Rules_GetConstructListCommand(int returnValue, int constructClass, double a3)
{
  int numArgs; // eax
  int v4; // ecx
  int *theModule; // eax
  _DWORD *v6; // ecx
  int v8; // edx
  _DWORD argValue[2]; // [esp-4h] [ebp-24h] BYREF
  int v10; // [esp+4h] [ebp-1Ch]
  int v11; // [esp+1Ch] [ebp-4h]

  v11 = returnValue;
  numArgs = Lexer_TokenExpect(1);
  if ( numArgs == -1 )
    return Rules_SetMultifieldErrorValue(v4);
  if ( numArgs == 1 )
  {
    Rules_RtnUnknown(1, argValue, a3);
    if ( argValue[1] != 2
      || (theModule = Module_FindByName(*(_BYTE **)(v10 + 16))) == 0 && (theModule = (int *)strcmp_(v6, *(_DWORD *)(v10 + 16))) != 0 )
    {
      Rules_SetMultifieldErrorValue((int)v6);
      return (_DWORD *)Parser_ReportError(v8, (int)aDefmoduleNam_2);
    }
  }
  else
  {
    theModule = (int *)Module_GetCurrent();
  }
  return (_DWORD *)Rules_BuildConstructNameList(v6, constructClass, (int)theModule);
}
// 4A8F90: variable 'v6' is possibly undefined
// 4A8F9E: variable 'v4' is possibly undefined
// 4A8FEB: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A9000) --------------------------------------------------------
int  Rules_BuildConstructNameList(_DWORD *returnValue, int constructClass, int Enum)
{
  signed int constructCount; // ebx
  int i; // edx
  int v7; // edx
  int v8; // ecx
  _DWORD *theMultifield; // eax
  int fieldPosition; // ebx
  int v11; // ecx
  int v12; // edx
  int v13; // edx
  int constructClassRec; // esi
  __int64 constructPtr; // rax
  int v16; // ecx
  int useModulePrefix; // edi
  int theConstruct; // ebp
  char *moduleNameDst; // edi
  char *Name; // esi
  char moduleNameChar; // al
  char moduleNameChar2; // al
  char *separatorSrc; // esi
  char *separatorDst; // edi
  char separatorChar; // al
  char separatorChar2; // al
  char *constructNameSrc; // esi
  unsigned int nameLength; // kr08_4
  char *constructNameDst; // edi
  char constructNameChar; // al
  char constructNameChar2; // al
  signed int *qualifiedSymbol; // eax
  int v33; // edx
  signed int *nameSymbol; // eax
  int v35; // edx
  char qualifiedName[512]; // [esp+0h] [ebp-224h] BYREF
  _DWORD *savedMultifield; // [esp+200h] [ebp-24h]
  int allModules; // [esp+204h] [ebp-20h]
  int moduleCursor; // [esp+208h] [ebp-1Ch]
  int nextConstruct; // [esp+20Ch] [ebp-18h]
  int savedConstructClass; // [esp+210h] [ebp-14h]

  savedConstructClass = constructClass;
  constructCount = 0;
  Module_BeginEnum();
  allModules = 0;
  if ( !Enum )
  {
    Enum = Module_NextEnum(0);
    allModules = v8;
  }
  for ( i = Enum; i; i = Module_NextEnum(v7) )
  {
    Module_SetCurrent(i);
    while ( (*(int (**)(void))(savedConstructClass + 28))() )
      ++constructCount;
    if ( !allModules )
      break;
  }
  returnValue[1] = 4;
  moduleCursor = Enum;
  returnValue[4] = constructCount - 1;
  returnValue[3] = 0;
  theMultifield = Rules_CreateEphemeralMultifield(constructCount);
  fieldPosition = 1;
  savedMultifield = theMultifield;
  for ( returnValue[2] = theMultifield; moduleCursor; moduleCursor = Module_NextEnum(moduleCursor) )
  {
    Module_SetCurrent(moduleCursor);
    nextConstruct = 0;
    v13 = v11 + v12 - 6;
    while ( 1 )
    {
      constructClassRec = savedConstructClass;
      nextConstruct = (*(int (__fastcall **)(int, int))(savedConstructClass + 28))(v11, v13);
      if ( !nextConstruct )
        break;
      constructPtr = ((__int64 (*)(void))*(_DWORD *)(constructClassRec + 16))();
      useModulePrefix = allModules;
      theConstruct = constructPtr;
      *(_WORD *)(HIDWORD(constructPtr) + 14) = 2;
      if ( useModulePrefix )
      {
        moduleNameDst = qualifiedName;
        Name = (char *)Module_GetName(moduleCursor);
        do
        {
          moduleNameChar = *Name;
          *moduleNameDst = *Name;
          if ( !moduleNameChar )
            break;
          moduleNameChar2 = Name[1];
          Name += 2;
          moduleNameDst[1] = moduleNameChar2;
          moduleNameDst += 2;
        }
        while ( moduleNameChar2 );
        separatorSrc = asc_5084B0;
        separatorDst = &qualifiedName[strlen(qualifiedName)];
        do
        {
          separatorChar = *separatorSrc;
          *separatorDst = *separatorSrc;
          if ( !separatorChar )
            break;
          separatorChar2 = separatorSrc[1];
          separatorSrc += 2;
          separatorDst[1] = separatorChar2;
          separatorDst += 2;
        }
        while ( separatorChar2 );
        constructNameSrc = *(char **)(theConstruct + 16);
        nameLength = strlen(qualifiedName) + 1;
        constructNameDst = &qualifiedName[nameLength - 1];
        do
        {
          constructNameChar = *constructNameSrc;
          *constructNameDst = *constructNameSrc;
          if ( !constructNameChar )
            break;
          constructNameChar2 = constructNameSrc[1];
          constructNameSrc += 2;
          constructNameDst[1] = constructNameChar2;
          constructNameDst += 2;
        }
        while ( constructNameChar2 );
        qualifiedSymbol = Str_Intern(qualifiedName, ~nameLength);
        *(_DWORD *)(v33 + 16) = qualifiedSymbol;
        v13 = v33 + 6;
        ++fieldPosition;
      }
      else
      {
        nameSymbol = Str_Intern(*(char **)(constructPtr + 16), v16);
        *(_DWORD *)(v35 + 16) = nameSymbol;
        v13 = v35 + 6;
        ++fieldPosition;
      }
    }
    if ( !allModules )
      break;
  }
  return Module_EndEnum();
}
// 4A9055: variable 'v8' is possibly undefined
// 4A906A: variable 'v7' is possibly undefined
// 4A90D0: variable 'v11' is possibly undefined
// 4A90C6: variable 'v12' is possibly undefined
// 4A918D: variable 'v33' is possibly undefined
// 4A919C: variable 'v16' is possibly undefined
// 4A91A1: variable 'v35' is possibly undefined

//----- (004A91F0) --------------------------------------------------------
int  Rules_ListConstructsCommand(int constructClass, int a2, double a3)
{
  int result; // eax
  int *theModule; // eax
  int v6; // ecx
  _DWORD argValue[2]; // [esp-4h] [ebp-24h] BYREF
  int v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+18h] [ebp-8h]

  v9 = a2;
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    if ( result == 1 )
    {
      Rules_RtnUnknown(1, argValue, a3);
      if ( argValue[1] != 2 )
        return Parser_ReportError(1, (int)aDefmoduleNam_2);
      theModule = Module_FindByName(*(_BYTE **)(v8 + 16));
      if ( !theModule )
      {
        theModule = (int *)strcmp_(v6, *(_DWORD *)(v8 + 16));
        if ( theModule )
          return Parser_ReportError(1, (int)aDefmoduleNam_2);
      }
    }
    else
    {
      theModule = (int *)Module_GetCurrent();
    }
    return Rules_PrintConstructNamesByModule(constructClass, (int)g_IO_LogicalName_WDisplay, (int)theModule);
  }
  return result;
}
// 4A9258: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A624: using guessed type char *off_51A624;

//----- (004A9280) --------------------------------------------------------
int  Rules_PrintConstructNamesByModule(int constructClass, int logicalName, int theModule)
{
  int constructCount; // ebp
  int result; // eax
  int v7; // ecx
  int theConstruct; // ebx
  int v9; // ecx
  int Name; // eax
  int v11; // ecx
  int v12; // ecx
  int Enum; // [esp+0h] [ebp-18h]
  int allModules; // [esp+4h] [ebp-14h]

  Enum = theModule;
  constructCount = 0;
  Module_BeginEnum();
  allModules = 0;
  if ( !theModule )
  {
    Enum = Module_NextEnum(0);
    allModules = 1;
  }
  while ( 1 )
  {
    if ( !Enum )
    {
LABEL_14:
      Rules_PrintTally((int)g_IO_LogicalName_WDisplay, constructCount, *(_DWORD *)(constructClass + 4), *(_DWORD *)constructClass);
      return Module_EndEnum();
    }
    if ( allModules )
    {
      Name = Module_GetName(Enum);
      Output_Write(logicalName, Name, v11);
      Output_Write(logicalName, (int)asc_5084B4, v12);
    }
    Module_SetCurrent(Enum);
    result = (*(int (**)(void))(constructClass + 28))();
    if ( result )
      break;
LABEL_13:
    if ( !allModules )
      goto LABEL_14;
    Enum = Module_NextEnum(Enum);
  }
  while ( g_ClipsHaltExecution != 1 )
  {
    theConstruct = (*(int (**)(void))(constructClass + 16))();
    if ( theConstruct )
    {
      if ( allModules )
        Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5084B8, v7);
      Output_Write(logicalName, *(_DWORD *)(theConstruct + 16), v7);
      Output_Write(logicalName, (int)asc_50849C, v9);
    }
    ++constructCount;
    result = (*(int (**)(void))(constructClass + 28))();
    if ( !result )
      goto LABEL_13;
  }
  return result;
}
// 4A935C: variable 'v11' is possibly undefined
// 4A9368: variable 'v12' is possibly undefined
// 4A92EF: variable 'v7' is possibly undefined
// 4A9305: variable 'v9' is possibly undefined
// 51A624: using guessed type char *off_51A624;
// 51A968: using guessed type int dword_51A968;

//----- (004A9390) --------------------------------------------------------
int  Rules_SetConstructNextInModule(int result, int nextConstruct)
{
  *(_DWORD *)(result + 16) = nextConstruct;
  return result;
}

//----- (004A93A0) --------------------------------------------------------
int  Rules_GetConstructOwnerModule(int theConstruct)
{
  return *(_DWORD *)(theConstruct + 8);
}

//----- (004A93B0) --------------------------------------------------------
int  Rules_GetModuleConstructListHead(int theModuleItem)
{
  return *(_DWORD *)(theModuleItem + 4);
}

//----- (004A93C0) --------------------------------------------------------
int  Class_Enum(int theConstruct, int moduleItemIndex)
{
  int result; // eax

  if ( theConstruct )
    return *(_DWORD *)(theConstruct + 16);
  result = Module_GetItem(0, moduleItemIndex);
  if ( result )
    return Rules_GetModuleConstructListHead(result);
  return result;
}

//----- (004A93E0) --------------------------------------------------------
int  Rules_GetModuleConstructData(int theModule, int moduleItemIndex)
{
  if ( !theModule )
    theModule = Module_GetCurrent();
  return Module_GetItem(theModule, moduleItemIndex);
}
// 4A93ED: variable 'a2' is possibly undefined

//----- (004A9400) --------------------------------------------------------
int  Rules_ClearModuleConstructList(int theModuleItem, int constructClass, int a3)
{
  int result; // eax
  int next; // edx
  int cleanup; // ecx

  (void)a3;
  result = *(_DWORD *)(theModuleItem + 4);
  while ( result )
  {
    next = *(_DWORD *)(result + 16);
    cleanup = *(_DWORD *)(constructClass + 44);
    ((void (*)(int))(uintptr_t)(unsigned int)cleanup)(result);
    result = next;
  }
  return result;
}

CLASH95_INTERNAL signed int sub_4A9430_Impl(int (*callback)(int, intptr_t), int construct_index, intptr_t callback_context, int stop_on_watch);

//----- (004A9430) --------------------------------------------------------
signed int  Rules_DoForAllConstructs(void (*actionFunction)(void), int interruptable)
{
  return sub_4A9430_Impl((int (*)(int, intptr_t))actionFunction, 0, 0, interruptable);
}

CLASH95_INTERNAL signed int sub_4A9430_Impl(int (*callback)(int, intptr_t), int construct_index, intptr_t callback_context, int stop_on_watch)
{
  int module; // ebp
  int module_index; // [esp+4h] [ebp-10h]
  int construct_data; // eax
  int item; // ecx

  Module_BeginEnum();
  module = Module_NextEnum(0);
  module_index = 0;
  if ( module )
  {
    while ( 1 )
    {
      Module_SetCurrent(module);
      construct_data = Module_GetItem(module, construct_index);
      item = *(_DWORD *)(construct_data + 4);
      if ( item )
        break;
LABEL_6:
      module = Module_NextEnum(module);
      ++module_index;
      if ( !module )
        goto LABEL_7;
    }
    while ( !stop_on_watch || Rules_GetEvaluationErrorFlag() != 1 )
    {
      callback(item, callback_context);
      item = *(_DWORD *)(item + 16);
      if ( !item )
        goto LABEL_6;
    }
    Module_EndEnum();
    return -1;
  }
  else
  {
LABEL_7:
    Module_EndEnum();
    return module_index;
  }
}

//----- (004A94D0) --------------------------------------------------------
CLASH95_INTERNAL int sub_4A94D0_Impl(int construct_name, int construct_data, int owner_symbol)
{
  int construct_record; // eax
  int module_data; // eax

  construct_record = Module_FindItemByName(construct_name);
  module_data = Module_GetItem(0, *(_DWORD *)(construct_record + 4));
  *(_DWORD *)(construct_data + 4) = 0;
  *(_DWORD *)(construct_data + 12) = 0;
  *(_DWORD *)(construct_data + 16) = 0;
  *(_DWORD *)(construct_data + 8) = module_data;
  *(_DWORD *)construct_data = owner_symbol;
  return module_data;
}

int  Rules_InitConstructModuleRecord(int constructType, int theConstruct)
{
  return sub_4A94D0_Impl(constructType, theConstruct, theConstruct);
}

//----- (004A9500) --------------------------------------------------------
signed int  Rules_ReplaceConstructPPForm(signed int result, int ppForm)
{
  signed int theConstruct; // ebx
  const char *oldPPForm; // edx

  theConstruct = result;
  oldPPForm = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(result + 4);
  if ( oldPPForm )
  {
    result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(result + 4), strlen(oldPPForm) + 1);
    *(_DWORD *)(theConstruct + 4) = ppForm;
  }
  else
  {
    *(_DWORD *)(result + 4) = ppForm;
  }
  return result;
}

//----- (004A9540) --------------------------------------------------------
signed int  Rules_ListWatchFlagStatus(
        int constructClass,
        int logicalName,
        int accessFunc,
        int argExprs,
        double a5,
        void (*setFunction)(void))
{
  return Rules_ProcessWatchFlagRequest(constructClass, (int)aListWatchIte_0, argExprs, logicalName, a5, 0, 0, accessFunc, setFunction);
}

//----- (004A9560) --------------------------------------------------------
signed int  Rules_ApplyWatchFlagCommand(
        int constructClass,
        int newState,
        int accessFunc,
        int argExprs,
        double a5,
        void (*setFunction)(void))
{
  return Rules_ProcessWatchFlagRequest(constructClass, (int)aWatch_0, argExprs, (int)g_IO_LogicalNameTable_WError[0], a5, 1, newState, accessFunc, setFunction);
}
// 51A614: using guessed type char *off_51A614[5];

//----- (004A9590) --------------------------------------------------------
signed int  Rules_ProcessWatchFlagRequest(
        int constructType,
        int functionName,
        int argExprs,
        int logicalName,
        double a5,
        int setMode,
        int newState,
        int getWatchFunc,
        void (*setWatchFunc)(void))
{
  int argPtr; // esi
  int v12; // edx
  int Name; // eax
  int v14; // ecx
  int v15; // ecx
  _DWORD argValue[7]; // [esp+0h] [ebp-30h] BYREF
  int argIndex; // [esp+1Ch] [ebp-14h]
  int i; // [esp+20h] [ebp-10h]

  argValue[6] = functionName;
  argPtr = argExprs;
  argIndex = 2;
  if ( argExprs )
  {
    while ( 1 )
    {
      if ( !argPtr )
        return 1;
      if ( Parser_ParseForm((__int16 *)argPtr, argValue, argExprs, a5) )
        return 0;
      if ( argValue[1] != 2 || !Symbol_LookupInModule((char **)constructType, *(_BYTE **)(argValue[2] + 16), 1) )
        break;
      if ( setMode )
        setWatchFunc();
      else
        Rules_PrintWatchFlagState(logicalName, constructType);
      argPtr = *(_DWORD *)(argPtr + 10);
      ++argIndex;
    }
    Parser_ReportError(argIndex, *(_DWORD *)constructType);
    return 0;
  }
  else
  {
    Module_BeginEnum();
    for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
    {
      Module_SetCurrent(i);
      if ( !v12 )
      {
        Name = Module_GetName(i);
        Output_Write(logicalName, Name, v14);
        Output_Write(logicalName, (int)asc_5084B4, v15);
      }
      while ( (*(int (**)(void))(constructType + 28))() )
      {
        if ( setMode )
        {
          setWatchFunc();
        }
        else
        {
          Output_Write(logicalName, (int)asc_5084B8, getWatchFunc);
          Rules_PrintWatchFlagState(logicalName, constructType);
        }
      }
    }
    Module_EndEnum();
    return 1;
  }
}
// 4A95E5: variable 'v12' is possibly undefined
// 4A95F4: variable 'v14' is possibly undefined
// 4A9600: variable 'v15' is possibly undefined
// 4A9671: variable 'a3' is possibly undefined

//----- (004A9710) --------------------------------------------------------
signed int  Rules_PrintWatchFlagState(int logicalName, int constructType)
{
  int theConstruct; // eax
  int v4; // ecx
  int (*getWatchFunc)(void); // ecx
  int v6; // ecx

  theConstruct = (*(int (**)(void))(constructType + 16))();
  Output_Write(logicalName, *(_DWORD *)(theConstruct + 16), v4);
  if ( getWatchFunc() )
    return Output_Write(logicalName, (int)aOn_2, v6);
  else
    return Output_Write(logicalName, (int)aOff_2, v6);
}
// 4A971D: variable 'v4' is possibly undefined
// 4A9724: variable 'v5' is possibly undefined
// 4A9731: variable 'v6' is possibly undefined

//----- (004A9750) --------------------------------------------------------
int  Symbol_LookupInModule(char **constructType, _BYTE *constructName, int moduleNameAllowed)
{
  char *typeName; // edi
  int result; // eax
  int theConstruct; // edx
  int count; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+4h] [ebp-14h]

  v9 = moduleNameAllowed;
  typeName = *constructType;
  result = Rules_FindImportExportConstruct(*constructType, &count, constructName, 1, 0);
  theConstruct = result;
  if ( result )
  {
    if ( count > 1 )
    {
      Rules_ReportAmbiguousReferenceError((int)typeName, (int)constructName);
      return 0;
    }
  }
  else
  {
    if ( v9 && Rules_FindModuleSeparator(constructName) )
      return ((int (*)(void))constructType[3])();
    return theConstruct;
  }
  return result;
}
// 4A97AE: variable 'v7' is possibly undefined

//----- (004A97C0) --------------------------------------------------------
_DWORD * Instance_ActiveInitializeInstanceFunction(uintptr_t returnValue, double a2)
{
  _DWORD *result; // eax
  _DWORD *theInstance; // ebx
  uintptr_t out; // ecx

  out = returnValue;
  *(_DWORD *)(out + 4) = 2;
  *(_DWORD *)(out + 8) = g_ClipsFalseSymbol;
  result = Instance_ResolveArgumentToInstance((int)aInitializeIn_0, (int)out, a2);
  theInstance = result;
  if ( result )
  {
    result = (_DWORD *)Instance_InitializeSlots(
                         (int)result,
                         *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10),
                         a2);
    if ( result == (_DWORD *)1 )
    {
      *(_DWORD *)(out + 4) = 8;
      result = (_DWORD *)theInstance[7];
      *(_DWORD *)(out + 8) = result;
    }
  }
  return result;
}
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9810) --------------------------------------------------------
_DWORD * Instance_ActiveMakeInstanceFunction(uintptr_t returnValue, uintptr_t a2, double a3)
{
  uintptr_t expression; // eax
  int instance_name; // ecx
  int class_record; // edx
  _DWORD *result; // eax
  int parsed_ptr; // ecx
  _DWORD *parsed; // [esp+0h] [ebp-24h] BYREF

  parsed_ptr = Compat_AllocLow32Bytes(24);
  if ( !parsed_ptr )
    return 0;
  parsed = (_DWORD *)(uintptr_t)(unsigned int)parsed_ptr;
  memset(parsed, 0, 24);
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6);
  Parser_ParseForm((__int16 *)expression, parsed, (int)a2, a3);
  if ( parsed[1] != 2 && parsed[1] != 8 )
  {
    Rules_PrintErrorID((int)aInsmngr, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_2, 0);
    result = (_DWORD *)(uintptr_t)(unsigned int)Lexer_ErrorRecover(1);
    goto done;
  }
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  instance_name = parsed[2];
  if ( *(_WORD *)expression == 57 )
  {
    class_record = *(_DWORD *)(expression + 2);
  }
  else
  {
    Parser_ParseForm((__int16 *)expression, parsed, instance_name, a3);
    if ( parsed[1] != 2 )
    {
      Rules_PrintErrorID((int)aInsmngr, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAVal_3, 0);
      result = (_DWORD *)(uintptr_t)(unsigned int)Lexer_ErrorRecover(1);
      goto done;
    }
    class_record = (int)Class_LookupInScope(*(_BYTE **)((uintptr_t)(unsigned int)parsed[2] + 16));
    if ( !class_record )
    {
      Class_ReportLookupError(
        *(_DWORD *)(*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 2)) + 16),
        *(_DWORD *)((uintptr_t)(unsigned int)parsed[2] + 16));
      result = (_DWORD *)(uintptr_t)(unsigned int)Lexer_ErrorRecover(1);
      goto done;
    }
  }
  result = Instance_BuildInstance(instance_name, class_record, 1, a3);
  if ( result )
  {
    if ( Instance_InitializeSlots((int)result, *(_DWORD *)(expression + 10), a3) )
    {
      *(_DWORD *)(returnValue + 4) = 8;
      result = Instance_GetQualifiedName((int)result, (int)result);
      *(_DWORD *)(returnValue + 8) = result;
    }
    else
    {
      result = (_DWORD *)(uintptr_t)(unsigned int)Instance_DeleteInstance((int)result, a3);
      *(_DWORD *)(returnValue + 4) = 2;
      *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
      goto done;
    }
  }
done:
  if ( *(_DWORD *)(returnValue + 4) == 2 && *(_DWORD *)(returnValue + 8) != g_ClipsFalseSymbol )
  {
    if ( getenv("CLASH95_TRACE_RULES_ASSERT_FACT") )
    {
      fprintf(
        stderr,
        "[rules] make-instance-reset-invalid-symbol value=%08x nil=%08x caller=%p\n",
        *(_DWORD *)(returnValue + 8),
        g_ClipsFalseSymbol,
        __builtin_return_address(0));
      fflush(stderr);
    }
    *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  }
  Compat_FreeLow32Bytes(parsed_ptr);
  return result;
}
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (004A9970) --------------------------------------------------------
signed int * Instance_GetQualifiedName(int theInstance, int a2)
{
  uintptr_t instance; // edx
  uintptr_t class_record; // eax
  uintptr_t module_record; // ecx
  uintptr_t instance_name_symbol; // eax
  const char *module_name; // ebx
  const char *instance_name; // edi
  unsigned int buffer_size; // esi
  char *qualified_name; // ecx
  signed int *symbol; // ebx

  instance = (uintptr_t)(unsigned int)theInstance;
  if ( instance == (uintptr_t)&g_Instance_DummyInstanceRecord )
    return Str_Intern(aDummyInstance, a2);
  instance_name_symbol = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 28);
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 )
    return (signed int *)instance_name_symbol;
  class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
  module_record = (uintptr_t)(unsigned int)*(_DWORD *)(class_record + 8);
  if ( Module_GetCurrent() == *(_DWORD *)module_record )
    return (signed int *)instance_name_symbol;
  module_name = (const char *)Module_GetName(*(_DWORD *)module_record);
  instance_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(instance_name_symbol + 16);
  buffer_size = (unsigned int)(strlen(instance_name) + strlen(module_name) + 3);
  qualified_name = (char *)(uintptr_t)(unsigned int)Mem_SmallBlockAlloc(buffer_size);
  sprintf_(qualified_name, "%s::%s", module_name, instance_name);
  symbol = Str_Intern(qualified_name, buffer_size);
  Mem_SmallBlockFree(qualified_name, buffer_size);
  return symbol;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51A214: using guessed type void *off_51A214;
