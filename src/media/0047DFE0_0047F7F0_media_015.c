/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0047DFE0) --------------------------------------------------------
int  Rules_GetNextActivation(int activation)
{
  int result; // eax

  if ( activation )
    return *(_DWORD *)(uintptr_t)(activation + 28);
  result = Module_GetItem(0, g_DefruleConstructClass);
  if ( result )
    return *(_DWORD *)(uintptr_t)(result + 12);
  return result;
}
// 54E64C: using guessed type int dword_54E64C;

//----- (0047E000) --------------------------------------------------------
int  Rules_GetActivationRuleName(int activation)
{
  /* sub_47E000: `mov eax,[eax]; mov eax,[eax]; mov eax,[eax+10h]` - three 32-BIT
     loads. The outer `*(_DWORD **)` read an 8-byte pointer out of emulated memory. */
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)activation + 16);
}

//----- (0047E0D0) --------------------------------------------------------
signed int  Rules_DetachActivation(_DWORD *activation)
{
  _DWORD *v1; // ecx
  int v2; // eax
  _DWORD *agendaHead; // edx
  int prevActivation; // ebx
  int nextActivation; // esi

  v1 = activation;
  if ( !activation )
    Rules_ReportSystemError(0, 1);
  v2 = *(_DWORD *)(uintptr_t)(*v1 + 8);
  agendaHead = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v2 + 12);
  if ( v1 == agendaHead )
    *(_DWORD *)(uintptr_t)(v2 + 12) = agendaHead[7];
  prevActivation = v1[6];
  if ( prevActivation )
    *(_DWORD *)(uintptr_t)(prevActivation + 28) = v1[7];
  nextActivation = v1[7];
  if ( nextActivation )
    *(_DWORD *)(uintptr_t)(nextActivation + 24) = v1[6];
  v1[6] = 0;
  v1[7] = 0;
  g_Rules_AgendaChangedFlag = 1;
  return 1;
}
// 47E0DB: variable 'v1' is possibly undefined
// 51A1E8: using guessed type int dword_51A1E8;

//----- (0047E140) --------------------------------------------------------
signed int __fastcall Rules_PrintActivation(int logicalName, int activation)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  _BYTE buffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v9 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v9 = logicalName;
  sprintf_(buffer, "%-6d ", *(_DWORD *)(uintptr_t)(activation + 8));
  Output_Write(v3, (int)(intptr_t)buffer, v3);
  Output_Write(v4, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)activation + 16), v4);
  Output_Write(v5, (int)(intptr_t)asc_502D44, v5);
  return Rules_PrintArgumentValueList(v6, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(activation + 4));
}
// 47E163: variable 'v3' is possibly undefined
// 47E171: variable 'v4' is possibly undefined
// 47E17D: variable 'v5' is possibly undefined
// 47E187: variable 'v6' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (0047E1A0) --------------------------------------------------------
int  Rules_ActivationsCommand(int logicalName, int module)
{
  return Rules_ListConstructsAcrossModules(
           logicalName,
           module,
           (int)(intptr_t)aActivations,
           (int)(intptr_t)aActivation_1,
           (int (__cdecl *)(int))Rules_GetNextActivation,
           0,
           (void (__fastcall *)(int, int))Rules_PrintActivation,
           0);
}

//----- (0047E1D0) --------------------------------------------------------
int  Rules_RemoveActivation(_DWORD *theActivation, int updateAgenda, int updateLinks)
{
  _DWORD *activation; // ecx
  int ruleModule; // edx
  int prevActivation; // esi
  int newAgendaHead; // eax
  int v8; // ecx
  int v9; // ecx
  _DWORD *binds; // edx
  int result; // eax
  int nextActivation; // edx

  activation = theActivation;
  ruleModule = *(_DWORD *)(uintptr_t)(*theActivation + 8);
  if ( updateAgenda == 1 )
  {
    prevActivation = theActivation[6];
    if ( prevActivation )
    {
      nextActivation = theActivation[7];
      *(_DWORD *)(uintptr_t)(prevActivation + 28) = nextActivation;
      if ( nextActivation )
        *(_DWORD *)(uintptr_t)(nextActivation + 24) = theActivation[6];
    }
    else
    {
      newAgendaHead = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(ruleModule + 12) + 28);
      *(_DWORD *)(uintptr_t)(ruleModule + 12) = newAgendaHead;
      if ( newAgendaHead )
        *(_DWORD *)(uintptr_t)(newAgendaHead + 24) = 0;
    }
    if ( (*(_BYTE *)(uintptr_t)(*activation + 29) & 0x10) != 0 )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aActivation, (int)(intptr_t)activation);
      Rules_PrintActivation(v8, v8);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_502D24, v9);
    }
    g_Rules_AgendaChangedFlag = 1;
  }
  if ( updateLinks == 1 )
  {
    binds = (_DWORD *)(uintptr_t)activation[1];
    if ( binds )
      *(_DWORD *)(uintptr_t)(activation[1] + 4 * (*binds << 17 >> 23) + 8) = 0;
  }
  --g_Rules_ActivationCount;
  if ( activation[4] )
    Rules_FreePartialMatch(activation[4]);
  g_ClipsMemFreeListTemp = (int)(intptr_t)activation;
  *activation = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
  return result;
}
// 47E219: variable 'v8' is possibly undefined
// 47E228: variable 'v9' is possibly undefined
// 47E23C: variable 'v4' is possibly undefined
// 51A1E0: using guessed type int dword_51A1E0;
// 51A1E8: using guessed type int dword_51A1E8;
// 51A618: using guessed type char *off_51A618[4];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047E2B0) --------------------------------------------------------
void Rules_ResetActivationSequence(void)
{
  g_Rules_ActivationSequenceCounter = 0;
}
// 51A1E4: using guessed type int dword_51A1E4;

//----- (0047E2C0) --------------------------------------------------------
_DWORD *Rules_ClearActivationsForModule(void)
{
  _DWORD *result; // eax
  _DWORD *nextActivation; // ecx

  result = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(Rules_GetDefruleModuleItem(0) + 12);
  if ( result )
  {
    do
    {
      Rules_RemoveActivation(result, 1, 1);
      result = nextActivation;
    }
    while ( nextActivation );
  }
  return result;
}
// 47E2E3: variable 'v1' is possibly undefined

//----- (0047E310) --------------------------------------------------------
int  Rules_SetAgendaChanged(int result)
{
  g_Rules_AgendaChangedFlag = result;
  return result;
}
// 51A1E8: using guessed type int dword_51A1E8;

//----- (0047E320) --------------------------------------------------------
int  Rules_ReorderAgenda(int result)
{
  int module; // esi
  int enumeratingAllModules; // edi
  int Enum; // eax
  int v4; // ecx
  int *agendaListHead; // ebx
  int nextActivation; // ecx

  module = result;
  enumeratingAllModules = 0;
  if ( result || (Enum = Module_NextEnum(0), enumeratingAllModules = 1, (module = Enum) != 0) )
  {
    do
    {
      v4 = Rules_GetDefruleModuleItem(module);
      Enum = *(_DWORD *)(uintptr_t)(v4 + 12);
      *(_DWORD *)(uintptr_t)(v4 + 12) = 0;
      if ( Enum )
      {
        agendaListHead = (int *)(uintptr_t)(v4 + 12);
        do
        {
          *(_DWORD *)(uintptr_t)(Enum + 24) = 0;
          nextActivation = *(_DWORD *)(uintptr_t)(Enum + 28);
          *(_DWORD *)(uintptr_t)(Enum + 28) = 0;
          Rules_InsertActivationSorted(agendaListHead, (_DWORD *)(uintptr_t)(unsigned int)Enum);
          Enum = nextActivation;
        }
        while ( nextActivation );
      }
      if ( !enumeratingAllModules )
        break;
      Enum = Module_NextEnum(module);
      module = Enum;
    }
    while ( Enum );
  }
  return Enum;
}

//----- (0047E3A0) --------------------------------------------------------
int Rules_GetActivationCount(void)
{
  return g_Rules_ActivationCount;
}
// 51A1E0: using guessed type int dword_51A1E0;

//----- (0047E3B0) --------------------------------------------------------
_BYTE * Rules_RefreshCommand(int a1, double a2)
{
  _BYTE *result; // eax
  int v3; // ecx
  int defrule; // eax
  int v5; // edx
  int v6; // ecx

  result = (_BYTE *)(uintptr_t)Rules_GetConstructNameArg((int)(intptr_t)aRuleName, a1, a2);
  if ( result )
  {
    defrule = Rules_FindDefruleByName(result, v3);
    if ( defrule )
      return (_BYTE *)(uintptr_t)Rules_RefreshRule(defrule, a2);
    else
      return (_BYTE *)(uintptr_t)Rules_ReportCantFindItem(v6, v5);
  }
  return result;
}
// 47E3C8: variable 'v3' is possibly undefined
// 47E3D6: variable 'v6' is possibly undefined
// 47E3D6: variable 'v5' is possibly undefined

//----- (0047E3F0) --------------------------------------------------------
signed int  Rules_RefreshRule(int defrule, double a2)
{
  int i; // ebx
  int j; // ecx

  for ( i = defrule; i; i = *(_DWORD *)(uintptr_t)(i + 48) )
  {
    for ( j = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(i + 44) + 8); j; j = *(_DWORD *)(uintptr_t)(j + 4) )
    {
      if ( (*(_BYTE *)(uintptr_t)j & 4) != 0 && (*(_BYTE *)(uintptr_t)j & 0x20) == 0 && !*(_DWORD *)(uintptr_t)(j + 4 * (*(_DWORD *)(uintptr_t)j << 17 >> 23) + 8) )
        Rules_AddActivation(i, j, a2);
    }
  }
  return 1;
}
// 47E429: variable 'j' is possibly undefined

//----- (0047E450) --------------------------------------------------------
signed int Rules_SalienceInformationError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)(intptr_t)aAgenda, 3, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThisErrorOccur, v0);
  if ( !v1 )
    return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_Agenda, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aForRule, v1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v3, v3);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_Agenda, v4);
}
// 47E473: variable 'v0' is possibly undefined
// 47E47A: variable 'v1' is possibly undefined
// 47E4A5: variable 'v3' is possibly undefined
// 47E4B4: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047E4C0) --------------------------------------------------------
signed int Rules_SalienceRangeError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)(intptr_t)aAgenda, 2, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSalienceValueO, v0);
  Rules_PrintLongInteger(v1, -10000);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aTo, v2);
  Rules_PrintLongInteger(v3, 10000);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_Agenda, v4);
}
// 47E4E0: variable 'v0' is possibly undefined
// 47E4EF: variable 'v1' is possibly undefined
// 47E4FE: variable 'v2' is possibly undefined
// 47E50D: variable 'v3' is possibly undefined
// 47E51C: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047E530) --------------------------------------------------------
signed int Rules_SalienceNonIntegerError(void)
{
  int v0; // ecx

  Rules_PrintErrorID((int)(intptr_t)aAgenda, 1, 1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSalienceValueM, v0);
}
// 47E54D: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047E560) --------------------------------------------------------
int * Rules_RefreshAgendaCommand(double a1)
{
  int *result; // eax
  int v2; // ecx
  _DWORD v3[3]; // [esp+0h] [ebp-Ch] BYREF

  result = (int *)(uintptr_t)Lexer_TokenExpect((int)(intptr_t)aRefreshAgenda, 2, 1);
  if ( result != (int *)-1 )
  {
    if ( result == (int *)1 )
    {
      result = Rules_GetModuleNameArg(1, v2, v3, a1);
      if ( !v3[0] )
        return (int *)(uintptr_t)Rules_RefreshAgenda(a1);
    }
    else
    {
      Module_GetCurrent();
      return (int *)(uintptr_t)Rules_RefreshAgenda(a1);
    }
  }
  return result;
}
// 47E59C: variable 'v2' is possibly undefined

//----- (0047E5C0) --------------------------------------------------------
int  Rules_RefreshAgenda(double a1)
{
  int Enum; // ecx
  int enumeratingAllModules; // ebx
  int v3; // edx
  int savedSalienceMode; // esi
  int *i; // edx
  int v6; // ecx
  int v7; // ecx

  Module_BeginEnum();
  enumeratingAllModules = 0;
  if ( !v3 )
  {
    enumeratingAllModules = 1;
    Enum = Module_NextEnum(0);
  }
  savedSalienceMode = g_Rules_SalienceEvaluationMode;
  for ( g_Rules_SalienceEvaluationMode = 1; Enum; Enum = Module_NextEnum(v7) )
  {
    Module_SetCurrent(Enum);
    for ( i = (int *)(uintptr_t)Rules_GetNextActivation(0); i; i = (int *)(uintptr_t)Rules_GetNextActivation((int)(intptr_t)i) )
      i[2] = Rules_EvaluateSalience(*i, a1);
    Rules_ReorderAgenda(v6);
    if ( !enumeratingAllModules )
      break;
  }
  g_Rules_SalienceEvaluationMode = savedSalienceMode;
  return Module_EndEnum();
}
// 47E5D1: variable 'v3' is possibly undefined
// 47E5E6: variable 'Enum' is possibly undefined
// 47E5FE: variable 'a1' is possibly undefined
// 47E615: variable 'v6' is possibly undefined
// 47E620: variable 'v7' is possibly undefined
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E650) --------------------------------------------------------
signed int * Rules_SetSalienceEvaluationCommand(int context, double a2)
{
  char *currentModeName; // esi
  int v4; // ecx
  char *v5; // eax
  int v7; // ecx
  int v8; // ecx
  _DWORD v9[11]; // [esp-8h] [ebp-2Ch] BYREF

  v9[9] = context;
  currentModeName = Rules_SalienceEvaluationModeName(g_Rules_SalienceEvaluationMode);
  if ( Lexer_TokenExpect((int)(intptr_t)aSetSalienceEva, 0, 1) == -1 || !Lexer_ParseValueList(1, v9, 2, a2) )
  {
    v5 = currentModeName;
    return Str_Intern(v5, v4);
  }
  if ( !strcmp_(*(_DWORD *)(uintptr_t)(v9[2] + 16), aWhenDefined) )
  {
    g_Rules_SalienceEvaluationMode = 0;
    v5 = currentModeName;
    return Str_Intern(v5, v4);
  }
  if ( !strcmp_(v4, aWhenActivated) )
  {
    g_Rules_SalienceEvaluationMode = 1;
    return Str_Intern(currentModeName, v7);
  }
  else
  {
    if ( !strcmp_(v7, aEveryCycle) )
      g_Rules_SalienceEvaluationMode = 2;
    else
      Parser_ReportError(1, (int)(intptr_t)aSymbolWithVa_1);
    return Str_Intern(currentModeName, v8);
  }
}
// 47E6B4: variable 'v4' is possibly undefined
// 47E6E2: variable 'v7' is possibly undefined
// 47E70C: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E740) --------------------------------------------------------
signed int *Rules_GetSalienceEvaluationCommand(void)
{
  char *modeName; // eax
  int v1; // ecx

  Lexer_TokenExpect((int)(intptr_t)aGetSalienceEva, 0, 0);
  modeName = Rules_SalienceEvaluationModeName(g_Rules_SalienceEvaluationMode);
  return Str_Intern(modeName, v1);
}
// 47E75A: variable 'v1' is possibly undefined
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E770) --------------------------------------------------------
char * Rules_SalienceEvaluationModeName(unsigned int mode)
{
  if ( !mode )
    return aWhenDefined;
  if ( mode <= 1 )
    return aWhenActivated;
  if ( mode == 2 )
    return aEveryCycle;
  return aUnknown_1;
}

//----- (0047E7A0) --------------------------------------------------------
int Rules_GetSalienceEvaluation(void)
{
  return g_Rules_SalienceEvaluationMode;
}
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E7B0) --------------------------------------------------------
int __fastcall Rules_SetSalienceEvaluationMode(int mode)
{
  int result; // eax

  result = g_Rules_SalienceEvaluationMode;
  g_Rules_SalienceEvaluationMode = mode;
  return result;
}
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E7C0) --------------------------------------------------------
signed int  Rules_EvaluateSalience(int defrule, double a2)
{
  signed int result; // eax
  /* sub_47E7C0: `mov ecx, eax; mov ebx, eax` (both are `defrule`) and
     `mov edx, esp` - the DATA_OBJECT is this frame's own local area, with
     var_20 = buf[1] (type) and var_1C = buf[2] (value). IDA turned all of
     that into the undefined temps v4..v9. */
  _DWORD parsed[6]; // [esp+0h] BYREF

  if ( !g_Rules_SalienceEvaluationMode || !*(_DWORD *)(uintptr_t)(defrule + 32) )
    return *(_DWORD *)(uintptr_t)(defrule + 20);
  Lexer_ErrorRecover(0);
  if ( Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(defrule + 32), parsed, defrule, a2) )
  {
    Rules_SalienceInformationError();
    return *(_DWORD *)(uintptr_t)(defrule + 20);
  }
  else if ( parsed[1] == 1 )
  {
    result = *(_DWORD *)((uintptr_t)(unsigned int)parsed[2] + 16);
    if ( result > 10000 || result < -10000 )
    {
      Rules_SalienceRangeError();
      Lexer_ErrorRecover(1);
      Rules_SalienceInformationError();
      return *(_DWORD *)(uintptr_t)(defrule + 20);
    }
    else
    {
      *(_DWORD *)(uintptr_t)(defrule + 20) = result;
    }
  }
  else
  {
    Rules_SalienceNonIntegerError();
    Rules_SalienceInformationError();
    Lexer_ErrorRecover(1);
    return *(_DWORD *)(uintptr_t)(defrule + 20);
  }
  return result;
}
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E880) --------------------------------------------------------
int * Rules_AgendaCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx
  int currentModule; // eax
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a1;
  result = (int *)(uintptr_t)Lexer_TokenExpect((int)(intptr_t)aAgenda_0, 2, 1);
  if ( result != (int *)-1 )
  {
    if ( result == (int *)1 )
    {
      result = Rules_GetModuleNameArg(1, v3, v5, a2);
      if ( !v5[0] )
        return (int *)(uintptr_t)Rules_ActivationsCommand((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)result);
    }
    else
    {
      currentModule = Module_GetCurrent();
      return (int *)(uintptr_t)Rules_ActivationsCommand((int)(intptr_t)g_IO_LogicalName_WDisplay, currentModule);
    }
  }
  return result;
}
// 47E8C5: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047E8E4) --------------------------------------------------------
int __fastcall IO_PrintfToStdout(int format, int a2 CLASH95_UNUSED, int a3 CLASH95_UNUSED, char firstArg)
{
  int args[3]; // [esp+0h] [ebp-Ch] BYREF

  args[0] = (int)(intptr_t)&firstArg;
  return CRT_VfprintfLockedWrite((int)(intptr_t)&g_CRT_StdoutStream, format, args);
}

/* --- diagnostic seam (CLASH95_TRACE_RULE_FIRE): names the rules the agenda
   actually activates and fires.  Not part of the recovered binary. --- */
static int Diagnostics_IsRuleFireTraceEnabled(void)
{
  static int cached = -1;
  if ( cached < 0 )
  {
    const char *value = getenv("CLASH95_TRACE_RULE_FIRE");
    cached = value && *value && *value != '0';
  }
  return cached;
}

static void Diagnostics_DumpAgenda(const char *tag)
{
  int activation;
  int count = 0;

  if ( !Diagnostics_IsRuleFireTraceEnabled() )
    return;
  for ( activation = Rules_GetNextActivation(0); activation; activation = Rules_GetNextActivation(activation) )
  {
    const char *name = (const char *)(uintptr_t)Rules_GetActivationRuleName(activation);
    fprintf(stderr, "[rule_agenda] %s #%d salience=%d %s\n", tag, count,
            *(int *)(uintptr_t)(activation + 8), name ? name : "(null)");
    ++count;
    if ( count > 400 )
      break;
  }
  fprintf(stderr, "[rule_agenda] %s total=%d\n", tag, count);
}

//----- (0047E910) --------------------------------------------------------
int  Rules_RunAgendaLoop(int runLimit, int a2, double a3)
{
  int v3; // ecx
  int *activation; // edi
  int v5 CLASH95_UNUSED; // edx
  int ruleName; // ebp
  _DWORD *binds; // esi
  unsigned int bindIndex; // ebx
  _DWORD *bindWalker; // edx
  int matchEntity; // eax
  int result; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16 CLASH95_UNUSED; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  _DWORD *bindPtr; // ebx
  unsigned int cleanupIndex; // edx
  unsigned int lastBindIndex; // eax
  int cleanupEntity; // eax
  int finalEntity; // eax
  int factCount; // eax
  int prevMaxInstances; // edi
  int newFactSum; // esi
  int instanceCount; // eax
  int newInstanceSum; // ebp
  int activationCount; // eax
  int v31; // ecx
  int i; // edx
  int callbackNode CLASH95_UNUSED; // edx
  int nextActivation; // eax
  int v35; // ecx
  int nextRuleName; // eax
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v42 CLASH95_UNUSED; // edx
  int v43 CLASH95_UNUSED; // ecx
  char *messageString; // edx
  int v45; // ecx
  int v46; // ecx
  int v47; // ecx
  double rulesPerSecond; // [esp+0h] [ebp-ECh]
  int v49 CLASH95_UNUSED; // [esp+4h] [ebp-E8h]
  int v50 CLASH95_UNUSED; // [esp+8h] [ebp-E4h]
  int v51 CLASH95_UNUSED; // [esp+8h] [ebp-E4h]
  int v52 CLASH95_UNUSED; // [esp+8h] [ebp-E4h]
  _DWORD fireTraceBuffer[15]; // [esp+Ch] [ebp-E0h] BYREF
  _BYTE statsBuffer[60]; // [esp+48h] [ebp-A4h] BYREF
  int returnValue[6]; // [esp+84h] [ebp-68h] BYREF
  double runtimeSeconds CLASH95_UNUSED; // [esp+9Ch] [ebp-50h]
  double startTime; // [esp+A4h] [ebp-48h]
  int maxInstances; // [esp+B4h] [ebp-38h]
  int maxFacts; // [esp+B8h] [ebp-34h]
  int activationSum; // [esp+BCh] [ebp-30h]
  int instanceSum; // [esp+C0h] [ebp-2Ch]
  int factSum; // [esp+C4h] [ebp-28h]
  int maxActivations; // [esp+C8h] [ebp-24h]
  int fireCount; // [esp+CCh] [ebp-20h]
  int remainingFires; // [esp+D0h] [ebp-1Ch]
  int meanValue; // [esp+D4h] [ebp-18h]

  remainingFires = runLimit;
  fireCount = 0;
  maxActivations = 0;
  activationSum = 0;
  maxFacts = 0;
  factSum = 0;
  maxInstances = 0;
  instanceSum = 0;
  startTime = 0.0;
  if ( g_Rules_AgendaLoopRunningFlag )
    return 0;
  g_Rules_AgendaLoopRunningFlag = 1;
  if ( g_Rules_WatchStatisticsFlag )
  {
    maxFacts = Rules_GetInstalledFactCount();
    factSum = maxFacts;
    maxInstances = Rules_GetActiveInstanceCount();
    instanceSum = maxInstances;
    maxActivations = Rules_GetActivationCount();
    activationSum = maxActivations;
    startTime = Rules_TimeCommand();
  }
  if ( !g_ClipsCurrentEvaluationDepth )
    Rules_SetEvaluationErrorFlag(0);
  v50 = a2;
  g_Rules_HaltRulesFlag = 0;
  Diagnostics_DumpAgenda("enter");
  activation = (int *)(uintptr_t)Rules_NextActivationToFire();
  while ( activation )
  {
    if ( !remainingFires || g_ClipsHaltExecution || g_Rules_HaltRulesFlag )
      break;
    Rules_DetachActivation(activation);
    ruleName = Rules_GetActivationRuleName((int)(intptr_t)activation);
    if ( Diagnostics_IsRuleFireTraceEnabled() )
      fprintf(stderr, "[rule_fire] %d %s\n", fireCount + 1,
              (const char *)(uintptr_t)ruleName);
    binds = (_DWORD *)(uintptr_t)activation[1];
    g_Rules_CurrentlyExecutingRule = *activation;
    ++fireCount;
    /* 47E9FD: `test edx,edx; jle; lea ecx,[edx-1]` - edx is remainingFires. */
    if ( remainingFires > 0 )
      remainingFires = remainingFires - 1;
    if ( (*(_BYTE *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 29) & 0x20) != 0 )
    {
      a3 = sprintf_(fireTraceBuffer, "FIRE %4ld ", fireCount);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)fireTraceBuffer, v12);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], ruleName, v13);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_502E90, v14);
      Rules_PrintArgumentValueList((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], binds);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_502E94, v15);
    }
    binds[(*binds << 17 >> 23) + 2] = 0;
    bindIndex = 0;
    *(_BYTE *)binds |= 2u;
    g_Clips_CurrentPartialMatch = (int)(intptr_t)binds;
    g_Rules_GlobalRHSBinds = 0;
    bindWalker = binds;
    while ( bindIndex < *binds << 17 >> 23 )
    {
      matchEntity = *(_DWORD *)(uintptr_t)bindWalker[2];
      if ( matchEntity )
        /* loc_47EB1E: `mov ecx,[eax]; call dword ptr [ecx+34h]` - the vtable slot is
           a 32-BIT function address, so it must be loaded as a _DWORD. */
        /* loc_47EB1E: `mov ecx,[eax]; call dword ptr [ecx+34h]` - eax (the pattern
           entity) is still live and is the callee's register argument. */
        (*(void (*)(int))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)matchEntity + 52))(matchEntity);
      ++bindWalker;
      ++bindIndex;
    }
    g_Rules_CurrentLogicalJoin = *(_DWORD *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 40);
    ++g_ClipsCurrentEvaluationDepth;
    Lexer_ErrorRecover(0);
    *(_BYTE *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 29) |= 0x80u;
    /* 47EB4A: `mov eax,[eax+8]; mov eax,[eax]` and `mov edx,[eax+24h]` - 32-BIT loads. */
    Rules_ExecuteRuleActions(
      *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 8),
      (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 36),
      returnValue,
      *(_DWORD *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 24),
      a3,
      0);
    *(_BYTE *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 29) &= ~0x80u;
    Lexer_ErrorRecover(0);
    g_Rules_CurrentLogicalJoin = 0;   /* 47EB92: `xor ecx,ecx ... mov ds:dword_51A1F8, ecx` */
    --g_ClipsCurrentEvaluationDepth;
    if ( g_ClipsHaltExecution || g_Rules_HaltRulesFlag && (*(_BYTE *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 29) & 0x20) != 0 )
    {
      Rules_PrintErrorID((int)(intptr_t)aPrccode, 4, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExecutionHalte, v17);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], ruleName, v18);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_RuleRuntime, v19);
    }
    bindPtr = binds;
    cleanupIndex = 0;
    *(_BYTE *)binds &= ~2u;
    while ( 1 )
    {
      lastBindIndex = (*binds << 17 >> 23) - 1;
      if ( cleanupIndex >= lastBindIndex )
        break;
      cleanupEntity = *(_DWORD *)(uintptr_t)bindPtr[2];
      if ( cleanupEntity )
        /* loc_47EC1A: `mov ecx,[eax]; call dword ptr [ecx+30h]` */
        (*(void (*)(int))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)cleanupEntity + 48))(cleanupEntity);
      ++bindPtr;
      ++cleanupIndex;
    }
    if ( (*(_BYTE *)binds & 0x20) == 0 )
    {
      finalEntity = *(_DWORD *)(uintptr_t)binds[lastBindIndex + 2];
      if ( finalEntity )
        /* 47EC33: `call dword ptr [edx+30h]` - no argument is set up. */
        /* 47EC31: `mov edx,[eax]; call dword ptr [edx+30h]` */
        (*(void (*)(int))(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)finalEntity + 48))(finalEntity);
    }
    Rules_RemoveActivation(activation, 0, 0);
    Rules_FlushPendingNetworkGarbage();
    Rules_RunPeriodicCleanup(0, 1);
    if ( g_Rules_WatchStatisticsFlag )
    {
      factCount = Rules_GetInstalledFactCount();
      if ( factCount > maxFacts )
        maxFacts = factCount;
      prevMaxInstances = maxInstances;
      newFactSum = factCount + factSum;
      instanceCount = Rules_GetActiveInstanceCount();
      factSum = newFactSum;
      if ( instanceCount > prevMaxInstances )
        maxInstances = instanceCount;
      newInstanceSum = instanceCount + instanceSum;
      activationCount = Rules_GetActivationCount();
      instanceSum = newInstanceSum;
      if ( activationCount > v31 )
        maxActivations = activationCount;
      activationSum += activationCount;
    }
    if ( Rules_GetSalienceEvaluation() == 2 )
      Rules_RefreshAgenda(a3);
    /* list-walk cursor advances from the node itself, as in Rules_RunPeriodicCleanup */
    for ( i = g_Rules_PostRuleFireCallbackListHead; i; i = *(_DWORD *)(uintptr_t)(i + 12) )
      (*(void (*)(void))(uintptr_t)*(_DWORD *)(uintptr_t)(i + 4))();
    if ( g_ClipsHaltExecutionFlag == 1 )
      Rules_RemoveModuleFocus(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_Rules_CurrentlyExecutingRule + 8));
    g_ClipsHaltExecutionFlag = 0;
    nextActivation = Rules_NextActivationToFire();
    v3 = nextActivation;
    activation = (int *)(uintptr_t)nextActivation;
    if ( nextActivation && (*(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)nextActivation + 29) & 8) != 0 )
    {
      g_Rules_HaltRulesFlag = 1;
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aBreakingOnRule, nextActivation);
      nextRuleName = Rules_GetActivationRuleName(v35);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], nextRuleName, (int)(intptr_t)g_IO_LogicalNameTable_WDialog[0]);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aDotNewline_RuleRuntime, v37);
    }
  }
  if ( remainingFires == fireCount )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aRuleFiringLimi, v3);
  g_Rules_CurrentlyExecutingRule = 0;
  g_Rules_HaltRulesFlag = 0;
  if ( g_Rules_WatchStatisticsFlag )
  {
    double runtime_end;
    double runtime_elapsed;
    double sample_count;

    runtime_end = Rules_TimeCommand();
    runtimeSeconds = runtime_end;
    Rules_PrintLongInteger(v38, fireCount);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aRulesFired, v39);
    if ( startTime >= runtime_end )
    {
      messageString = asc_502E94;
    }
    else
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)aRunTimeIs, v40);
      runtime_elapsed = runtime_end - startTime;
      runtimeSeconds = runtime_elapsed;
      Rules_PrintFloat((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], runtime_elapsed);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)" seconds.\n", 0);
      rulesPerSecond = (double)fireCount / runtime_elapsed;
      Rules_PrintFloat((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], rulesPerSecond);
      messageString = " rules per second.\n";
    }
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)messageString, v40);
    sample_count = (double)(fireCount + 1);
    meanValue = (int)((double)factSum / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(statsBuffer, "%ld mean number of facts (%ld maximum).\n", meanValue, maxFacts);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)statsBuffer, v45);
    meanValue = (int)((double)instanceSum / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(statsBuffer, "%ld mean number of instances (%ld maximum).\n", meanValue, maxInstances);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)statsBuffer, v46);
    meanValue = (int)((double)activationSum / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(statsBuffer, "%ld mean number of activations (%ld maximum).\n", meanValue, maxActivations);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WDialog[0], (int)(intptr_t)statsBuffer, v47);
  }
  if ( g_Rules_FocusStackTop && Module_GetCurrent() != *(_DWORD *)(uintptr_t)g_Rules_FocusStackTop )
    Module_SetCurrent(*(_DWORD *)(uintptr_t)g_Rules_FocusStackTop);
  result = fireCount;
  g_Rules_AgendaLoopRunningFlag = 0;
  return result;
}
// 47EAAA: inconsistent fpu stack
// 47E99A: variable 'a2' is possibly undefined
// 47E9FD: variable 'v5' is possibly undefined
// 47EADE: variable 'v12' is possibly undefined
// 47EAEA: variable 'v13' is possibly undefined
// 47EAF9: variable 'v14' is possibly undefined
// 47EB14: variable 'v15' is possibly undefined
// 47EA5D: variable 'v9' is possibly undefined
// 47EB92: variable 'v16' is possibly undefined
// 47EBBD: variable 'v17' is possibly undefined
// 47EBC9: variable 'v18' is possibly undefined
// 47EBD8: variable 'v19' is possibly undefined
// 47EC01: variable 'v21' is possibly undefined
// 47EC32: variable 'v50' is possibly undefined
// 47ECC0: variable 'v31' is possibly undefined
// 47ECEE: variable 'v33' is possibly undefined
// 47ED46: variable 'v35' is possibly undefined
// 47ED64: variable 'v37' is possibly undefined
// 47ED8B: variable 'v3' is possibly undefined
// 47EDC3: variable 'v38' is possibly undefined
// 47EDD2: variable 'v39' is possibly undefined
// 47EDF8: variable 'v40' is possibly undefined
// 47EE36: variable 'v42' is possibly undefined
// 47EE36: variable 'v43' is possibly undefined
// 47EE71: variable 'v44' is possibly undefined
// 47EEEC: variable 'v45' is possibly undefined
// 47EF13: variable 'v51' is possibly undefined
// 47EF4A: variable 'v46' is possibly undefined
// 47EF79: variable 'v52' is possibly undefined
// 47EF97: variable 'v49' is possibly undefined
// 47EFA8: variable 'v47' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 502FDC: using guessed type double dbl_502FDC;
// 51A1F0: using guessed type int dword_51A1F0;
// 51A1F4: using guessed type int dword_51A1F4;
// 51A1F8: using guessed type int dword_51A1F8;
// 51A1FC: using guessed type int dword_51A1FC;
// 51A200: using guessed type int dword_51A200;
// 51A208: using guessed type int dword_51A208;
// 51A210: using guessed type int dword_51A210;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A968: using guessed type int dword_51A968;
// 51A96C: using guessed type int dword_51A96C;
// 51ACC0: using guessed type int dword_51ACC0;
// 51ACFC: using guessed type int dword_51ACFC;
// 51AD00: using guessed type int dword_51AD00;

//----- (0047F000) --------------------------------------------------------
int Rules_NextActivationToFire(void)
{
  int activation; // edx
  int *mainModule; // eax

  if ( !g_Rules_FocusStackTop )
  {
    mainModule = Module_FindByName(aMain_0);
    Rules_PushFocus((int)(intptr_t)mainModule);
  }
  activation = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Rules_FocusStackTop + 4) + 12);
  while ( !activation )
  {
    if ( !g_Rules_FocusStackTop )
      break;
    Rules_PopFocus();
    if ( g_Rules_FocusStackTop )
      activation = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(g_Rules_FocusStackTop + 4) + 12);
  }
  return activation;
}
// 47F039: variable 'v0' is possibly undefined
// 51A200: using guessed type int dword_51A200;

//----- (0047F060) --------------------------------------------------------
int  Rules_RemoveModuleFocus(int module)
{
  int found; // ebx
  int removedTop; // ebp
  _DWORD *focusEntry; // eax
  int prevEntry; // ecx
  int nextEntry; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int result; // eax

  found = 0;
  removedTop = 0;
  if ( !g_Rules_FocusStackTop )
    return 0;
  focusEntry = (_DWORD *)(uintptr_t)g_Rules_FocusStackTop;
  prevEntry = 0;
  do
  {
    if ( found )
      break;
    if ( module == *focusEntry )
    {
      nextEntry = focusEntry[2];
      g_ClipsMemFreeListTemp = (int)(intptr_t)focusEntry;
      *focusEntry = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
      found = 1;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      focusEntry = (_DWORD *)(uintptr_t)nextEntry;
      if ( prevEntry )
      {
        *(_DWORD *)(uintptr_t)(prevEntry + 8) = nextEntry;
      }
      else
      {
        removedTop = 1;
        g_Rules_FocusStackTop = nextEntry;
      }
    }
    else
    {
      prevEntry = (int)(intptr_t)focusEntry;
      focusEntry = (_DWORD *)(uintptr_t)focusEntry[2];
    }
  }
  while ( focusEntry );
  if ( !found )
    return *(_DWORD *)(uintptr_t)g_Rules_FocusStackTop;
  if ( g_Rules_WatchFocusFlag )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aFocus, prevEntry);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)module + 16), v7);
    if ( g_Rules_FocusStackTop && removedTop )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aTo_0, v8);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_Rules_FocusStackTop + 16), v9);
    }
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_502E94, v8);
  }
  if ( g_Rules_FocusStackTop )
  {
    if ( removedTop )
      Module_SetCurrent(*(_DWORD *)(uintptr_t)g_Rules_FocusStackTop);
  }
  result = module;
  g_Rules_FocusStackChangedFlag = 1;
  return result;
}
// 47F0F4: variable 'v7' is possibly undefined
// 47F110: variable 'v8' is possibly undefined
// 47F126: variable 'v9' is possibly undefined
// 51A200: using guessed type int dword_51A200;
// 51A204: using guessed type int dword_51A204;
// 51A20C: using guessed type int dword_51A20C;
// 51A618: using guessed type char *off_51A618[4];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047F190) --------------------------------------------------------
int Rules_PopFocus(void)
{
  if ( g_Rules_FocusStackTop )
    return Rules_RemoveModuleFocus(*(_DWORD *)(uintptr_t)g_Rules_FocusStackTop);
  else
    return 0;
}
// 51A200: using guessed type int dword_51A200;

//----- (0047F1C0) --------------------------------------------------------
int  Rules_PushFocus(int a1)
{
  int module; // ecx
  int focus_entry; // edx

  module = a1;
  Module_SetCurrent(a1);
  if ( !g_Rules_FocusStackTop || module != *(_DWORD *)(uintptr_t)g_Rules_FocusStackTop )
  {
    if ( g_Rules_WatchFocusFlag )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aFocus_0, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)module + 16), module);
      if ( g_Rules_FocusStackTop )
      {
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aFrom, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_Rules_FocusStackTop + 16), g_Rules_FocusStackTop);
      }
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_502E94, 0);
    }
    focus_entry = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
    if ( focus_entry )
    {
      g_ClipsMemFreeListTemp = focus_entry;
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *(_DWORD *)(uintptr_t)focus_entry;
      focus_entry = g_ClipsMemFreeListTemp;
    }
    else
    {
      focus_entry = Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    *(_DWORD *)(uintptr_t)focus_entry = module;
    *(_DWORD *)(uintptr_t)(focus_entry + 4) = Rules_GetDefruleModuleItem(module);
    *(_DWORD *)(uintptr_t)(focus_entry + 8) = g_Rules_FocusStackTop;
    g_Rules_FocusStackTop = focus_entry;
    g_Rules_FocusStackChangedFlag = 1;
  }
  return g_Rules_FocusStackTop;
}
// 51A200: using guessed type int dword_51A200;
// 51A204: using guessed type int dword_51A204;
// 51A20C: using guessed type int dword_51A20C;
// 51A618: using guessed type char *off_51A618[4];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047F2A0) --------------------------------------------------------
int Rules_ClearFocusStackCommand(void)
{
  int result; // eax

  result = Lexer_TokenExpect(0, 0, 0);
  if ( result != -1 )
    return Rules_ClearFocusStack();
  return result;
}

//----- (0047F2C0) --------------------------------------------------------
int Rules_ClearFocusStack(void)
{
  int result; // eax

  for ( ; g_Rules_FocusStackTop; result = Rules_PopFocus() )
    ;
  g_Rules_FocusStackChangedFlag = 1;
  return result;
}
// 51A200: using guessed type int dword_51A200;
// 51A204: using guessed type int dword_51A204;

//----- (0047F340) --------------------------------------------------------
int Rules_RegisterAgendaWatchFlags(void)
{
  Rules_AddWatchItem((int)(intptr_t)aStatistics, 0, 20, (int)(intptr_t)&g_Rules_WatchStatisticsFlag, 0, 0);
  return Rules_AddWatchItem((int)(intptr_t)aFocus_1, 0, 0, (int)(intptr_t)&g_Rules_WatchFocusFlag, 0, 0);
}
// 51A208: using guessed type int dword_51A208;
// 51A20C: using guessed type int dword_51A20C;

//----- (0047F380) --------------------------------------------------------
int  Rules_RunCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  _DWORD v4[6]; // [esp-8h] [ebp-24h] BYREF
  /* stack alias of v4[2]: the DATA_OBJECT value slot */
  int savedContext CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  savedContext = a1;
  result = Lexer_TokenExpect(0, 2, 1);
  if ( result != v3 )
  {
    if ( result == 1 )
    {
      result = Lexer_ParseValueList(1, v4, 1, a2);
      if ( result )
        return Rules_RunAgendaLoop(*(_DWORD *)(uintptr_t)(v4[2] + 16), *(_DWORD *)(uintptr_t)(v4[2] + 16), a2);
    }
    else
    {
      return Rules_RunAgendaLoop(v3, v3, a2);
    }
  }
  return result;
}
// 47F3A5: simplified comparisons for 'eax.4': !=0 && ==1 became ==1
// 47F3A1: variable 'v3' is possibly undefined

//----- (0047F3F0) --------------------------------------------------------
int Rules_HaltCommand(void)
{
  int result; // eax

  result = Lexer_TokenExpect(0, 0, 0);
  g_Rules_HaltRulesFlag = 1;
  return result;
}
// 51A1F4: using guessed type int dword_51A1F4;

//----- (0047F410) --------------------------------------------------------
int  Rules_SetBreakFlag(int result)
{
  for ( ; result; result = *(_DWORD *)(uintptr_t)(result + 48) )
    *(_BYTE *)(uintptr_t)(result + 29) |= 8u;
  return result;
}

//----- (0047F440) --------------------------------------------------------
signed int  Rules_ClearBreakFlag(int disjunct)
{
  int cleared; // edx
  char flags; // bl

  cleared = 0;
  if ( !disjunct )
    return cleared;
  do
  {
    while ( 1 )
    {
      flags = *(_BYTE *)(uintptr_t)(disjunct + 29);
      if ( (flags & 8) != 0 )
        break;
      disjunct = *(_DWORD *)(uintptr_t)(disjunct + 48);
      if ( !disjunct )
        return cleared;
    }
    cleared = 1;
    *(_BYTE *)(uintptr_t)(disjunct + 29) = flags & 0xF7;
    disjunct = *(_DWORD *)(uintptr_t)(disjunct + 48);
  }
  while ( disjunct );
  return 1;
}

//----- (0047F480) --------------------------------------------------------
void Rules_RemoveAllBreakFlags(void)
{
  int module; // ecx
  int defrule; // edx

  module = 0;
  while ( 1 )
  {
    module = Module_NextEnum(module);
    if ( !module )
      return;
    defrule = 0;
    while ( (defrule = Rules_GetNextDefrule(defrule)) != 0 )
      Rules_ClearBreakFlag(defrule);
  }
}

//----- (0047F4B0) --------------------------------------------------------
int  Rules_ListRuleBreakpoints(int logicalName, int module)
{
  return Rules_ListConstructsAcrossModules(
           logicalName,
           module,
           0,
           0,
           (int (__cdecl *)(int))Rules_GetNextDefrule,
           (int (*)(void))Rules_GetConstructNameString,
           0,
           (int (*)(void))Rules_RuleHasBreakFlag);
}

//----- (0047F4D0) --------------------------------------------------------
int  Rules_RuleHasBreakFlag(int defrule)
{
  return *(_DWORD *)(uintptr_t)(defrule + 28) << 20 >> 31;
}

//----- (0047F4E0) --------------------------------------------------------
int  Rules_SetBreakCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int defrule; // eax
  int v5; // edx
  int v6; // ecx
  _DWORD v7[9]; // [esp-8h] [ebp-24h] BYREF

  v7[7] = a1;
  result = Lexer_TokenExpect(0, 0, 1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, v7, 2, a2);
    if ( result )
    {
      defrule = Rules_FindDefruleByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v7[2] + 16), v3);
      if ( defrule )
        return Rules_SetBreakFlag(defrule);
      else
        return Rules_ReportCantFindItem(v6, v5);
    }
  }
  return result;
}
// 47F526: variable 'v3' is possibly undefined
// 47F534: variable 'v6' is possibly undefined
// 47F534: variable 'v5' is possibly undefined

//----- (0047F550) --------------------------------------------------------
void  Rules_RemoveBreakCommand(int a1, double a2, int a3)
{
  int tokenType; // eax
  int defrule; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  _DWORD v9[6]; // [esp-8h] [ebp-24h] BYREF
  /* stack alias of v9[2]: the DATA_OBJECT value slot */
  int v11 CLASH95_UNUSED; // [esp+10h] [ebp-Ch]
  int v12 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v12 = a1;
  v11 = a3;
  tokenType = Lexer_TokenExpect(0, 2, 1);
  if ( tokenType != -1 )
  {
    if ( tokenType )
    {
      if ( Lexer_ParseValueList(1, v9, 2, a2) )
      {
        defrule = Rules_FindDefruleByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(v9[2] + 16), *(_DWORD *)(uintptr_t)(v9[2] + 16));
        if ( defrule )
        {
          if ( !Rules_ClearBreakFlag(defrule) )
          {
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aRule, v6);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v7, v7);
            Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDoesNotHaveABr, v8);
          }
        }
        else
        {
          Rules_ReportCantFindItem(v5, v5);
        }
      }
    }
    else
    {
      Rules_RemoveAllBreakFlags();
    }
  }
}
// 47F5C0: variable 'v6' is possibly undefined
// 47F5CC: variable 'v7' is possibly undefined
// 47F5DB: variable 'v8' is possibly undefined
// 47F5EE: variable 'v5' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047F600) --------------------------------------------------------
int * Rules_ShowBreaksCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx
  int currentModule; // eax
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a1;
  result = (int *)(uintptr_t)Lexer_TokenExpect(0, 2, 1);
  if ( result != (int *)-1 )
  {
    if ( result == (int *)1 )
    {
      result = Rules_GetModuleNameArg(1, v3, v5, a2);
      if ( !v5[0] )
        return (int *)(uintptr_t)Rules_ListRuleBreakpoints((int)(intptr_t)g_IO_LogicalName_WDisplay, (int)(intptr_t)result);
    }
    else
    {
      currentModule = Module_GetCurrent();
      return (int *)(uintptr_t)Rules_ListRuleBreakpoints((int)(intptr_t)g_IO_LogicalName_WDisplay, currentModule);
    }
  }
  return result;
}
// 47F645: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047F670) --------------------------------------------------------
int Rules_ListFocusStackCommand(void)
{
  int result; // eax

  result = Lexer_TokenExpect(0, 0, 0);
  if ( result != -1 )
    return Rules_PrintFocusStack((signed int)(intptr_t)g_IO_LogicalName_WDisplay);
  return result;
}
// 51A624: using guessed type char *off_51A624;

//----- (0047F6A0) --------------------------------------------------------
signed int  Rules_PrintFocusStack(signed int result)
{
  int logicalName_copy; // ebx
  int *focusEntry; // ecx
  int Name; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  logicalName_copy = result;
  focusEntry = (int *)(uintptr_t)g_Rules_FocusStackTop;
  if ( g_Rules_FocusStackTop )
  {
    do
    {
      Name = Module_GetName(*focusEntry);
      Output_Write(logicalName_copy, Name, v4);
      result = Output_Write(logicalName_copy, (int)(intptr_t)asc_502E94, v5);
      focusEntry = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(v6 + 8);
    }
    while ( focusEntry );
  }
  return result;
}
// 47F6BA: variable 'v4' is possibly undefined
// 47F6C6: variable 'v5' is possibly undefined
// 47F6CB: variable 'v6' is possibly undefined
// 51A200: using guessed type int dword_51A200;

//----- (0047F6F0) --------------------------------------------------------
int Rules_GetFocusStackFunction(void)
{
  int result; // eax
  _DWORD *returnValue; // ecx

  result = Lexer_TokenExpect(0, 0, 0);
  if ( result != -1 )
    return Rules_BuildFocusStackList(returnValue);
  return result;
}
// 47F70E: variable 'v1' is possibly undefined

//----- (0047F720) --------------------------------------------------------
signed int  Rules_BuildFocusStackList(_DWORD *returnValue)
{
  int focusEntry; // edx
  signed int count; // eax
  _DWORD *multifield; // eax
  int v5; // ecx
  _DWORD *multifield_ptr; // ebx
  int focusEntry_walk; // edx
  signed int result; // eax
  _DWORD *element; // ecx
  int v9_alias; // ecx

  focusEntry = g_Rules_FocusStackTop;
  count = 0;
  if ( g_Rules_FocusStackTop )
  {
    do
    {
      focusEntry = *(_DWORD *)(uintptr_t)(focusEntry + 8);
      ++count;
    }
    while ( focusEntry );
    returnValue[1] = 4;
    returnValue[3] = 0;
    returnValue[4] = count - 1;
    multifield = Rules_CreateEphemeralMultifield(count);
    *(_DWORD *)(uintptr_t)(v5 + 8) = multifield;
    multifield_ptr = multifield;
    focusEntry_walk = g_Rules_FocusStackTop;
    result = 1;
    if ( g_Rules_FocusStackTop )
    {
      element = multifield_ptr;
      do
      {
        *((_WORD *)element + 7) = 2;
        element[4] = *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)focusEntry_walk;
        element = (_DWORD *)((char *)element + 6);
        focusEntry_walk = *(_DWORD *)(uintptr_t)(focusEntry_walk + 8);
        ++result;
      }
      while ( focusEntry_walk );
    }
  }
  else
  {
    returnValue[1] = 4;
    returnValue[4] = -1;
    returnValue[3] = 0;
    result = (signed int)(intptr_t)Rules_CreateEphemeralMultifield(0);
    *(_DWORD *)(uintptr_t)(v9_alias + 8) = result;
  }
  return result;
}
// 47F759: variable 'v5' is possibly undefined
// 47F7AA: variable 'v9_alias' is possibly undefined
// 51A200: using guessed type int dword_51A200;

//----- (0047F7C0) --------------------------------------------------------
int Rules_PopFocusFunction(void)
{
  int focusModule; // eax

  Lexer_TokenExpect(0, 0, 0);
  focusModule = Rules_PopFocus();
  if ( focusModule )
    return *(_DWORD *)(uintptr_t)focusModule;
  else
    return g_ClipsFalseSymbol;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (0047F7F0) --------------------------------------------------------
int Rules_GetFocusFunction(void)
{
  int focusModule; // eax

  Lexer_TokenExpect(0, 0, 0);
  focusModule = Rules_GetCurrentFocus();
  if ( focusModule )
    return *(_DWORD *)(uintptr_t)focusModule;
  else
    return g_ClipsFalseSymbol;
}
// 54DD70: using guessed type int dword_54DD70;
