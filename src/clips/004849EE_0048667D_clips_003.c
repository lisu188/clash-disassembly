/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004849EE) --------------------------------------------------------
// Deferred to compat/decomp_runtime_stubs.c until the ExcString throw helper is reconstructed.

//----- (00484AED) --------------------------------------------------------
int CRT_ConstructBadExceptionFromCurrentSEH(void)
{
  int result; // eax

  result = ExcString_CtorFromPtr((void *)NtCurrentTeb()->NtTib.ExceptionList);
  *(_DWORD *)(uintptr_t)(result + 100) = &g_BadException_VTable;
  return result;
}
// 510F44: using guessed type _DWORD (__cdecl *off_510F44)(bad_exception *this);

//----- (00484DBD) --------------------------------------------------------
int __thiscall CRT_WriteMessageAndCountNewline(void *this)
{
  int result; // eax
  int v2; // ecx
  int charsWritten; // ebx

  result = fputs_(this, &g_CRT_StdoutStream);
  charsWritten = result;
  if ( result != -1 )
  {
    result = CRT_PutcToStream(v2, &g_CRT_StdoutStream);
    if ( result == 10 )
      return charsWritten + 1;
  }
  return result;
}
// 484DDA: variable 'v2' is possibly undefined
// 4850C6: using guessed type int __fastcall fputs_(_DWORD, _DWORD);
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (00484EBB) --------------------------------------------------------
int  CRT_WatcomEHTraverseUnwindState(int a1, int a2)
{
  int v2; // eax
  int v3; // edx
  int v4; // ecx

  v2 = _wcpp_4_stab_trav_move__(a2, a1);
  v4 = v2;
  if ( v2 && !*(_DWORD *)(uintptr_t)v2 && *(_DWORD *)(uintptr_t)(v3 + 4) != *(_DWORD *)(uintptr_t)(v3 + 8) )
  {
    switch ( **(_BYTE **)(uintptr_t)(v2 + 4) )
    {
      case 2:
      case 3:
      case 4:
        goto LABEL_6;
      case 6:
      case 7:
      case 8:
      case 9:
      case 0xA:
      case 0xB:
      case 0xC:
      case 0xD:
        return v4;
      default:
        _wcpp_4_corrupted_stack__(v2);
LABEL_6:
        _wcpp_4_corrupted_stack__(v4);
        break;
    }
  }
  return v4;
}
// 484ED0: variable 'v3' is possibly undefined
// 484EF2: variable 'v4' is possibly undefined
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B47CD: using guessed type int __fastcall _wcpp_4_stab_trav_move__(_DWORD, _DWORD);

//----- (00484EFD) --------------------------------------------------------
int  CRT_WatcomEHInvokeStateDestructor(int a1, unsigned __int8 a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)(uintptr_t)(a1 + 4) + *(_DWORD *)(uintptr_t)(a3 + 4);
  if ( (a2 & *(_BYTE *)(uintptr_t)(result + 4)) == 0 )
    return (*(int (**)(void))(uintptr_t)(a1 + 12))();
  return result;
}

//----- (00484F53) --------------------------------------------------------
unsigned int  CRT_WatcomEHUnwindToState(unsigned int targetState, int unwindBlock, int regRecord)
{
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int objectPtr; // edx
  unsigned __int8 dtorFlag; // cl
  int destructorBlock; // ebx
  int destructorRecord; // eax
  unsigned int result; // eax
  int stateEntry; // esi
  int v14; // ecx
  int cleanupInfo; // esi
  _BYTE traverseCursor[4]; // [esp+4h] [ebp-24h] BYREF
  unsigned int currentState; // [esp+8h] [ebp-20h]
  unsigned int traverseTargetState CLASH95_UNUSED; // [esp+Ch] [ebp-1Ch]
  char traverseFlags; // [esp+11h] [ebp-17h]
  int entry; // [esp+14h] [ebp-14h]

  *(_DWORD *)(uintptr_t)(unwindBlock + 4) = regRecord;
  *(_DWORD *)(uintptr_t)(unwindBlock + 8) = *(_DWORD *)(uintptr_t)(regRecord + 8);
  _wcpp_4_stab_trav_init__();
  traverseTargetState = targetState;
  traverseFlags |= 1u;
  entry = CRT_WatcomEHTraverseUnwindState((int)(intptr_t)traverseCursor, v5);
  while ( 1 )
  {
    result = currentState;
    if ( currentState == targetState )
      break;
    if ( currentState < targetState )
      _wcpp_4_corrupted_stack__(v6);
    _wcpp_4_stab_trav_next__();
    stateEntry = entry;
    entry = CRT_WatcomEHTraverseUnwindState((int)(intptr_t)traverseCursor, v14);
    *(_DWORD *)(uintptr_t)(regRecord + 12) = currentState;
    if ( *(_DWORD *)(uintptr_t)stateEntry )
    {
      (*(void (**)(void))(uintptr_t)stateEntry)();
    }
    else
    {
      cleanupInfo = *(_DWORD *)(uintptr_t)(stateEntry + 4);
      switch ( *(_BYTE *)(uintptr_t)cleanupInfo )
      {
        case 0:
          goto LABEL_3;
        case 2:
        case 3:
        case 4:
          _wcpp_4_corrupted_stack__(v7);
          continue;
        case 6:
          dtorFlag = 17;
          goto LABEL_7;
        case 7:
          dtorFlag = 16;
LABEL_7:
          destructorBlock = unwindBlock;
          destructorRecord = cleanupInfo;
          goto LABEL_8;
        case 8:
          dtorFlag = 16;
          destructorBlock = unwindBlock;
          destructorRecord = cleanupInfo;
LABEL_8:
          CRT_WatcomEHInvokeStateDestructor(destructorRecord, dtorFlag, destructorBlock);
          continue;
        case 9:
          objectPtr = *(_DWORD *)(uintptr_t)(regRecord + *(_DWORD *)(uintptr_t)(cleanupInfo + 4) + 8);
          goto LABEL_4;
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
          (*(void (**)(void))(uintptr_t)(cleanupInfo + 8))();
          continue;
        default:
          _wcpp_4_corrupted_stack__(v7);
LABEL_3:
          objectPtr = *(_DWORD *)(uintptr_t)(cleanupInfo + 8);
LABEL_4:
          _wcpp_4_dtor_array__(v7, objectPtr);
          break;
      }
    }
  }
  *(_DWORD *)(uintptr_t)(regRecord + 12) = currentState;
  return result;
}
// 484F81: variable 'v5' is possibly undefined
// 484F8C: variable 'v7' is possibly undefined
// 484FF9: variable 'v6' is possibly undefined
// 48500F: variable 'v14' is possibly undefined
// 473197: using guessed type int __fastcall _wcpp_4_dtor_array__(_DWORD, _DWORD);
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B475C: using guessed type int _wcpp_4_stab_trav_init__(void);
// 4B477E: using guessed type int _wcpp_4_stab_trav_next__(void);

//----- (0048507C) --------------------------------------------------------
unsigned int  CRT_WatcomEHUnwindThreadToState(int a1, int a2)
{
  __int64 v2; // rax
  unsigned int v3; // ecx
  _DWORD v5[5]; // [esp+0h] [ebp-14h] BYREF

  v5[3] = a2;
  v2 = _wcpp_4_pgm_thread__(a1);
  v5[0] = v2;
  return CRT_WatcomEHUnwindToState(v3, (int)(intptr_t)v5, SHIDWORD(v2));
}
// 485091: variable 'v3' is possibly undefined
// 4B42EA: using guessed type __int64 __thiscall _wcpp_4_pgm_thread__(_DWORD);

//----- (0048509C) --------------------------------------------------------
unsigned int __fastcall CRT_WatcomEHUnwindToExceptionList(int a1, int a2 CLASH95_UNUSED)
{
  unsigned int v2; // ecx
  _DWORD v4[6]; // [esp+0h] [ebp-18h] BYREF

  v4[4] = a1;
  v4[0] = _wcpp_4_pgm_thread__(0);
  return CRT_WatcomEHUnwindToState(v2, (int)(intptr_t)v4, (int)(intptr_t)NtCurrentTeb()->NtTib.ExceptionList);
}
// 4850BA: variable 'v2' is possibly undefined
// 4B42EA: using guessed type int __thiscall _wcpp_4_pgm_thread__(_DWORD);

//----- (00485296) --------------------------------------------------------
int  Str_ParseSignedInt(char *str)
{
  char signChar; // cl
  int value; // ebx
  int accum; // ebx

  while ( (IsTable[(unsigned __int8)(*str + 1)] & 2) != 0 )
    ++str;
  signChar = *str;
  if ( *str == 43 || signChar == 45 )
    ++str;
  value = 0;
  while ( (IsTable[(unsigned __int8)(*str + 1)] & 0x20) != 0 )
  {
    accum = (unsigned __int8)*str++ + 10 * value;
    value = accum - 48;
  }
  if ( signChar == 45 )
    return -value;
  return value;
}

//----- (00485384) --------------------------------------------------------
int  CRT_InitializeProcessStartupInfo(int threadDataMgmtDisabled, int a2, int a3, HMODULE moduleHandle)
{
  int result; // eax
  CHAR *cmdLineA; // eax
  _BYTE *cmdLineW; // eax
  LPWSTR rawCmdLineW;
  _BYTE v13[520]; // [esp+0h] [ebp-41Ch] BYREF
  CHAR Filename[260]; // [esp+208h] [ebp-214h] BYREF
  CHAR moduleFilename[268]; // [esp+30Ch] [ebp-110h] BYREF
  int v16 CLASH95_UNUSED; // [esp+418h] [ebp-4h]
  static const _WORD emptyWideCommandLine[] = { 0 };

  v16 = a3;
  g_CrtThreadDataMgmtDisabledFlag = threadDataMgmtDisabled;
  result = CRT_AllocateThreadDataBlock(a2, a3);
  lpTlsValue = (LPVOID)(uintptr_t)result;
  if ( result )
  {
    _NTInitFileHandles_();
    g_CRT_EnvironmentStringsPtr = (int)(intptr_t)GetEnvironmentStrings();
    g_CRT_EnvVarPointerArray = 0;
    g_WindowsVersionDword = GetVersion();
    g_CRT_OsBuildNumber = HIWORD(g_WindowsVersionDword);
    g_CRT_WinMajorVersion = (unsigned __int8)g_WindowsVersionDword;
    g_CRT_WinMinorVersion = BYTE1(g_WindowsVersionDword);
    g_CRT_WinVersion = BYTE1(g_WindowsVersionDword) | ((unsigned __int8)g_WindowsVersionDword << 8);
    GetModuleFileNameA(0, Filename, 0x104u);
    g_CRT_ExecutablePathA = CRT_FinalizeAnsiApiStringResult(Filename);
    _lib_GetModuleFileNameW_(0, (_WORD *)v13, 0x208u);
    g_CRT_ExecutablePathW = CRT_FinalizeWideApiStringResult((_WORD *)v13);
    cmdLineA = GetCommandLineA();
    cmdLineA = (CHAR *)(uintptr_t)CRT_FinalizeAnsiApiStringResult(cmdLineA);
    if ( *cmdLineA != 34 )
    {
      while ( (IsTable[(unsigned __int8)(*cmdLineA + 1)] & 2) == 0 && *cmdLineA )
        ++cmdLineA;
      goto LABEL_12;
    }
    do
      ++cmdLineA;
    while ( *cmdLineA != 34 && *cmdLineA );
    if ( !*cmdLineA )
      goto LABEL_12;
    do
    {
      ++cmdLineA;
LABEL_12:
      ;
    }
    while ( (IsTable[(unsigned __int8)(*cmdLineA + 1)] & 2) != 0 );
    lpCmdLine = cmdLineA;
    rawCmdLineW = GetCommandLineW();
    if ( rawCmdLineW )
    {
      cmdLineW = (_BYTE *)(uintptr_t)CRT_FinalizeWideApiStringResult((const _WORD *)rawCmdLineW);
      if ( *(_WORD *)cmdLineW != 34 )
      {
        while ( (IsTable[(unsigned __int8)(*cmdLineW + 1)] & 2) == 0 && *(_WORD *)cmdLineW )
          cmdLineW += 2;
        goto LABEL_22;
      }
      do
        cmdLineW += 2;
      while ( *(_WORD *)cmdLineW != 34 && *(_WORD *)cmdLineW );
      if ( !*(_WORD *)cmdLineW )
        goto LABEL_22;
      do
      {
        cmdLineW += 2;
LABEL_22:
        ;
      }
      while ( (IsTable[(unsigned __int8)(*cmdLineW + 1)] & 2) != 0 );
    }
    else
    {
      cmdLineW = (_BYTE *)(uintptr_t)CRT_FinalizeWideApiStringResult(emptyWideCommandLine);
    }
    g_CRT_WideCommandLine = (int)(intptr_t)cmdLineW;
    if ( threadDataMgmtDisabled )
    {
      GetModuleFileNameA(moduleHandle, moduleFilename, 0x104u);
      g_CRT_ModulePathA = CRT_FinalizeAnsiApiStringResult(moduleFilename);
      _lib_GetModuleFileNameW_((_DWORD)(uintptr_t)moduleHandle, (_WORD *)v13, 0x208u);
      g_CRT_ModulePathW = CRT_FinalizeWideApiStringResult((_WORD *)v13);
    }
    return 1;
  }
  else if ( !threadDataMgmtDisabled )
  {
    ExitProcess(1u);
  }
  return result;
}
// 4B4C8F: using guessed type int _NTInitFileHandles_(void);
// 4B4D17: source pointer is passed in EAX; allocated copy is returned in EAX.
// 4B4D5C: module, output buffer, and byte count arrive in EAX, EDX, and EBX.
// 4B4DEC: wide source pointer is passed in EAX; allocated copy is returned in EAX.
// 51A868: using guessed type int dword_51A868;
// 51A86C: using guessed type int dword_51A86C;
// 51A870: using guessed type int dword_51A870;
// 51A874: using guessed type int dword_51A874;
// 51A878: using guessed type int dword_51A878;
// 51A8A1: using guessed type int dword_51A8A1;
// 51A8A7: using guessed type int dword_51A8A7;
// 51A8AB: using guessed type int dword_51A8AB;
// 51A8AF: using guessed type int dword_51A8AF;
// 51A8B3: using guessed type int dword_51A8B3;
// 51A8B7: using guessed type int dword_51A8B7;
// 54E704: using guessed type int dword_54E704;

//----- (004855AF) --------------------------------------------------------
int  CRT_InitializeRuntimeBeforeWinMain(int a1, int a2)
{
  HMODULE ModuleHandleA; // ebx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  ModuleHandleA = GetModuleHandleA(0);
  CRT_InitializeProcessStartupInfo(0, a2, v5, ModuleHandleA);
  g_CrtThreadDataAccessor(v6, &g_CRT_StartupThreadDataBlock);
  _init_stack_limits_();
  CRT_InstallUnhandledExceptionFilter(a1, v7);
  _InitRtns();
  g_CRT_ThreadStartupHook();
  return _InitRtns();
}
// 4855C6: variable 'v5' is possibly undefined
// 4855D0: variable 'v6' is possibly undefined
// 4855DD: variable 'v7' is possibly undefined
// 485379: using guessed type _DWORD nullsub_8();
// 48564F: using guessed type int _InitRtns(void);
// 4B4E13: using guessed type int _init_stack_limits_(void);
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A5A8: using guessed type _DWORD (*off_51A5A8)();

//----- (004856F0) --------------------------------------------------------
signed int  Output_WriteLongString(signed int result, char *str)
{
  int logicalName; // esi
  char *strPtr; // ebx
  int length; // ecx
  int segmentStart; // edx
  char saved_char; // cl

  logicalName = result;
  strPtr = str;
  if ( str )
  {
    while ( 1 )
    {
      length = strlen(strPtr);
      if ( length <= 500 )
        break;
      segmentStart = (int)(intptr_t)strPtr;
      strPtr += 500;
      LOBYTE(length) = *strPtr;
      saved_char = *strPtr;
      *strPtr = 0;
      Output_Write(logicalName, segmentStart, length);
      *strPtr = saved_char;
    }
    return Output_Write(logicalName, (int)(intptr_t)strPtr, length);
  }
  return result;
}

//----- (00485740) --------------------------------------------------------
signed int  Rules_PrintFloat(int logicalName, double number)
{
  int floatText; // eax

  floatText = Rules_FloatToSymbol(logicalName, number);
  return Output_Write(logicalName, floatText, logicalName);
}

//----- (00485770) --------------------------------------------------------
signed int __fastcall Rules_PrintLongInteger(int logicalName, int number)
{
  _BYTE printBuffer[32]; // [esp+0h] [ebp-24h] BYREF
  int v5; // [esp+20h] [ebp-4h]

  v5 = logicalName;
  sprintf_(printBuffer, "%ld", number);
  return Output_Write(v5, (int)(intptr_t)printBuffer, v5);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004857A0) --------------------------------------------------------
unsigned int  Rules_PrintAtomValue(int logicalName, unsigned int type, int *value)
{
  int logName; // ecx
  unsigned int result; // eax
  int entityRecord; // edi
  int escapedText; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int floatText; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _BYTE addressBuffer[32]; // [esp+8h] [ebp-20h] BYREF

  logName = logicalName;
  result = type;
  if ( type < 3 )
  {
    if ( type )
    {
      if ( type > 1 )
        return Output_Write(logName, value[4], logName);
      else
        return Rules_PrintLongInteger(logName, value[4]);
    }
    else
    {
      floatText = Rules_FloatToSymbol(logName, *((double *)value + 2));
      return Output_Write(v12, floatText, v12);
    }
  }
  if ( type <= 3 )
  {
    if ( g_Print_PreserveEscapedCharactersFlag )
    {
      escapedText = Str_InternQuotedEscapedString((int *)(uintptr_t)value[4], logName);
      return Output_Write(v7, escapedText, v7);
    }
    else
    {
      Output_Write(logName, (int)(intptr_t)asc_503EA4, logName);
      Output_Write(v13, value[4], v13);
      return Output_Write(v14, (int)(intptr_t)asc_503EA4, v14);
    }
  }
  if ( type < 8 )
  {
    if ( type == 5 )
    {
      if ( g_Print_AddressesToStringsFlag )
        Output_Write(logName, (int)(intptr_t)asc_503EA4, logName);
      Output_Write(logName, (int)(intptr_t)aPointer, logName);
      sprintf_(addressBuffer, "%p", value);
      Output_Write(v8, (int)(intptr_t)addressBuffer, v8);
      result = Output_Write(v9, (int)(intptr_t)asc_503EB8, v9);
      if ( g_Print_AddressesToStringsFlag )
        return Output_Write(v10, (int)(intptr_t)asc_503EA4, v10);
      return result;
    }
    goto LABEL_4;
  }
  if ( type <= 8 )
  {
    Output_Write(logName, (int)(intptr_t)asc_503EBC, logName);
    Output_Write(v15, value[4], v15);
    return Output_Write(v16, (int)(intptr_t)asc_503EC0, v16);
  }
  if ( type != 105 )
  {
LABEL_4:
    result = 4 * type;
    entityRecord = g_Clips_PrimitiveEntityTable[type];
    if ( entityRecord )
    {
      if ( *(_DWORD *)(uintptr_t)(entityRecord + 8) )
        return (*(int (**)(void))(uintptr_t)(entityRecord + 8))();
      else
        return Output_Write(logName, (int)(intptr_t)aUnknownAtomTyp, logName);
    }
  }
  return result;
}
// 4858CB: variable 'v12' is possibly undefined
// 48580C: variable 'v7' is possibly undefined
// 48583E: variable 'v3' is possibly undefined
// 48585A: variable 'v8' is possibly undefined
// 485866: variable 'v9' is possibly undefined
// 48587F: variable 'v10' is possibly undefined
// 4858F9: variable 'v13' is possibly undefined
// 485905: variable 'v14' is possibly undefined
// 485922: variable 'v15' is possibly undefined
// 48592E: variable 'v16' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);
// 51A5F8: using guessed type int dword_51A5F8;
// 51A5FC: using guessed type int dword_51A5FC;
// 54E530: using guessed type int dword_54E530[70];

//----- (00485950) --------------------------------------------------------
int  Rules_PrintTally(int result, int count, int a3, int singularWord)
{
  int logName; // esi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v10; // ecx

  logName = result;
  if ( count )
  {
    Output_Write(result, (int)(intptr_t)aForATotalOf, a3);
    Rules_PrintLongInteger(v6, count);
    Output_Write(logName, (int)(intptr_t)asc_503EE8, v7);
    if ( count != 1 )
      singularWord = v8;
    Output_Write(logName, singularWord, v8);
    return Output_Write(logName, (int)(intptr_t)a__14, v10);
  }
  return result;
}
// 48596B: variable 'v6' is possibly undefined
// 485977: variable 'v7' is possibly undefined
// 485985: variable 'v8' is possibly undefined
// 485991: variable 'v10' is possibly undefined

//----- (004859A0) --------------------------------------------------------
signed int  Rules_PrintErrorID(int module, int errorID, int printCR)
{
  if ( printCR )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_503EF0, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_503EBC, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], module, 0);
  Rules_PrintLongInteger((int)(intptr_t)g_IO_LogicalNameTable_WError[0], errorID);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_503EF4, 0);
}
// 51A614: using guessed type char *off_51A614[5];

//----- (00485A00) --------------------------------------------------------
signed int  Rules_PrintWarningID(int module, int warningID, int printCR)
{
  if ( printCR )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)asc_503EF0, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)asc_503EBC, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], module, 0);
  Rules_PrintLongInteger((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], warningID);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WWarning[0], (int)(intptr_t)aWarning, 0);
}
// 51A610: using guessed type char *off_51A610[6];

//----- (00485A60) --------------------------------------------------------
signed int __fastcall Rules_ReportCantFindItem(int itemType CLASH95_UNUSED, int itemName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToFind, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_503EE8, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], itemName, v6);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__14, v7);
}
// 485A82: variable 'v3' is possibly undefined
// 485A8E: variable 'v4' is possibly undefined
// 485A9D: variable 'v5' is possibly undefined
// 485AA9: variable 'v6' is possibly undefined
// 485AB8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485AD0) --------------------------------------------------------
signed int __fastcall Rules_ReportCantDeleteItem(int itemType CLASH95_UNUSED, int itemName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 4, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToDele_3, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_503EE8, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], itemName, v6);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__14, v7);
}
// 485AF2: variable 'v3' is possibly undefined
// 485AFE: variable 'v4' is possibly undefined
// 485B0D: variable 'v5' is possibly undefined
// 485B19: variable 'v6' is possibly undefined
// 485B28: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485B40) --------------------------------------------------------
signed int __fastcall Rules_ReportAlreadyParsed(int coupler CLASH95_UNUSED, int whichItem)
{
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 5, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThe_0, v3);
  if ( v4 )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  if ( whichItem )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], whichItem, v4);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aHasAlreadyBeen, v4);
}
// 485B65: variable 'v3' is possibly undefined
// 485B6C: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485BC0) --------------------------------------------------------
int Parser_ReportSyntaxError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v3; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 2, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aSyntaxError, v0);
  if ( v1 )
  {
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCheckAppropria, v1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v3, v3);
  }
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__14, v1);
  return Lexer_ErrorRecover(1);
}
// 485BE3: variable 'v0' is possibly undefined
// 485BEA: variable 'v1' is possibly undefined
// 485C1F: variable 'v3' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485C30) --------------------------------------------------------
signed int Rules_ReportLocalVariableError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 6, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aLocalVariables, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)a__14, v2);
}
// 485C53: variable 'v0' is possibly undefined
// 485C5F: variable 'v1' is possibly undefined
// 485C6E: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485C80) --------------------------------------------------------
signed int __fastcall Rules_ReportSystemError(int module CLASH95_UNUSED, int errorID)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 3, 1);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aClipsSystemErr, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aId, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v5, v5);
  Rules_PrintLongInteger(v6, errorID);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_503EF0, v7);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aClipsDataStruc, v8);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThisErrorMayHa, v9);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504060, v10);
}
// 485CA5: variable 'v3' is possibly undefined
// 485CB4: variable 'v4' is possibly undefined
// 485CC0: variable 'v5' is possibly undefined
// 485CCC: variable 'v6' is possibly undefined
// 485CDB: variable 'v7' is possibly undefined
// 485CEA: variable 'v8' is possibly undefined
// 485CF9: variable 'v9' is possibly undefined
// 485D08: variable 'v10' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485D20) --------------------------------------------------------
signed int Rules_ReportDivideByZeroError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aPrntutil, 7, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aAttemptToDivid, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction__0, v2);
}
// 485D40: variable 'v0' is possibly undefined
// 485D4C: variable 'v1' is possibly undefined
// 485D5B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00485D70) --------------------------------------------------------
int __fastcall Rules_FloatToSymbol(int a1, double number)
{
  int char_index; // esi
  int v4; // ecx
  char curr_char; // al
  char *suffix_ptr; // esi
  unsigned int buffer_length; // kr04_4
  char *append_ptr; // edi
  char v10; // al
  char v11; // al
  char print_buffer[52]; // [esp+0h] [ebp-34h] BYREF

  *(_DWORD *)&print_buffer[48] = a1;
  char_index = 0;
  sprintf_(print_buffer, "%.16g", number);
  while ( 1 )
  {
    curr_char = print_buffer[char_index];
    if ( !curr_char )
      break;
    if ( curr_char == 46 || curr_char == 101 )
      return Str_Intern(print_buffer, v4)[4];
    ++char_index;
  }
  suffix_ptr = a_0;
  buffer_length = strlen(print_buffer) + 1;
  append_ptr = &print_buffer[buffer_length - 1];
  do
  {
    v10 = *suffix_ptr;
    *append_ptr = *suffix_ptr;
    if ( !v10 )
      break;
    v11 = suffix_ptr[1];
    suffix_ptr += 2;
    append_ptr[1] = v11;
    append_ptr += 2;
  }
  while ( v11 );
  return Str_Intern(print_buffer, ~buffer_length)[4];
}
// 485DA8: variable 'v4' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00485E00) --------------------------------------------------------
int  Rules_LongIntegerToSymbol(int number)
{
  int v1; // ecx
  char printBuffer[32]; // [esp+0h] [ebp-20h] BYREF

  sprintf_(printBuffer, "%ld", number);
  return Str_Intern(printBuffer, v1)[4];
}
// 485E18: variable 'v1' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00485E30) --------------------------------------------------------
signed int Rules_RegisterExitFunction(void)
{
  Rules_RegisterHostFunction(aExit, 118, (int)(intptr_t)aExitcommand, (int)(intptr_t)Rules_ExitCommand, (int)(intptr_t)a00_16);
  IO_InitializeFileIORouter();
  return IO_RegisterStringRouter();
}

//----- (00485E60) --------------------------------------------------------
signed int  Output_Write(int logicalName, int str, int a3 CLASH95_UNUSED)
{
  int router; // ecx
  void (__fastcall *router_write)(int, int); // ecx

  if ( g_IO_FastSaveFilePtr && logicalName == g_IO_FastSaveFilePtr )
  {
    Output_WriteFormatted(0, 0, g_IO_FastSaveFilePtr, (int)(intptr_t)aS_1, str);
    return 2;
  }
  else
  {
    router = g_IO_RouterListHead;
    if ( g_IO_RouterListHead )
    {
      while ( !*(_DWORD *)(uintptr_t)(router + 16) || !IO_RouterMatchesName(logicalName, router) )
      {
        router = *(_DWORD *)(uintptr_t)(router + 32);
        if ( !router )
          goto LABEL_5;
      }
      router_write = (void (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(router + 16);
      router_write(logicalName, str);
      return 1;
    }
    else
    {
LABEL_5:
      if ( strcmp_((int)(intptr_t)g_IO_LogicalNameTable_WError[0], logicalName) )
        IO_ReportUnrecognizedRouter(logicalName);
      return 0;
    }
  }
}
// 485E81: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;
// 51A60C: using guessed type int dword_51A60C;
// 51A614: using guessed type char *off_51A614[5];

//----- (00485EE0) --------------------------------------------------------
int  Lexer_PeekChar(int logicalName, unsigned int a2)
{
  int result; // eax
  unsigned __int8 *buffer_ptr; // ecx
  int router; // ecx
  int (__fastcall *router_read)(int); // eax

  if ( logicalName == g_IO_FastLoadFilePtr )
  {
    if ( *(int *)(uintptr_t)(g_IO_FastLoadFilePtr + 4) > 0 && (a2 = **(unsigned __int8 **)(uintptr_t)g_IO_FastLoadFilePtr - 13, a2 > 0xFD) )
    {
      --*(_DWORD *)(uintptr_t)(g_IO_FastLoadFilePtr + 4);
      buffer_ptr = (unsigned __int8 *)(uintptr_t)(*(_DWORD *)(uintptr_t)g_IO_FastLoadFilePtr)++;
      result = *buffer_ptr;
    }
    else
    {
      result = fgetc_(a2, g_IO_FastLoadFilePtr);
    }
    if ( result != 13 )
      return result;
    return 10;
  }
  router = g_IO_RouterListHead;
  if ( !g_IO_RouterListHead )
  {
LABEL_12:
    IO_ReportUnrecognizedRouter(logicalName);
    return -1;
  }
  while ( !*(_DWORD *)(uintptr_t)(router + 24) || !IO_RouterMatchesName(logicalName, router) )
  {
    router = *(_DWORD *)(uintptr_t)(router + 32);
    if ( !router )
      goto LABEL_12;
  }
  router_read = (int (__fastcall *)(int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(router + 24);
  result = router_read(logicalName);
  if ( result == 13 )
    return 10;
  return result;
}
// 485F4E: variable 'v4' is possibly undefined
// 488F44: using guessed type int __fastcall fgetc_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;
// 51A608: using guessed type int dword_51A608;

//----- (00485F90) --------------------------------------------------------
signed int  Lexer_SkipChar(signed int ch, int logicalName, int a3)
{
  int router; // ecx
  int (__fastcall *router_skip)(int, int); // eax

  if ( logicalName == g_IO_FastLoadFilePtr )
    return CRT_FlushBufferAndPutChar(ch, a3);
  router = g_IO_RouterListHead;
  if ( g_IO_RouterListHead )
  {
    while ( !*(_DWORD *)(uintptr_t)(router + 28) || !IO_RouterMatchesName(logicalName, router) )
    {
      router = *(_DWORD *)(uintptr_t)(router + 32);
      if ( !router )
        goto LABEL_5;
    }
    router_skip = (int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(router + 28);
    return router_skip(ch, logicalName);
  }
  else
  {
LABEL_5:
    IO_ReportUnrecognizedRouter(logicalName);
    return -1;
  }
}
// 485FB1: variable 'v4' is possibly undefined
// 51A604: using guessed type int dword_51A604;
// 51A608: using guessed type int dword_51A608;

//----- (00485FF0) --------------------------------------------------------
int Rules_ExitCommand(void)
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return IO_RunRouterExitCallbacks();
  return result;
}

//----- (00486020) --------------------------------------------------------
int IO_RunRouterExitCallbacks(num)
int num;
{
  int router; // edx
  int next_router; // ecx
  int (*router_exit)(int); // eax
  int result; // eax

  g_IO_RouterExitHandledFlag = 0;
  router = g_IO_RouterListHead;
  while ( router )
  {
    next_router = *(_DWORD *)(uintptr_t)(router + 32);
    if ( *(_DWORD *)(uintptr_t)(router + 4) == 1 && *(_DWORD *)(uintptr_t)(router + 20) )
    {
      router_exit = (int (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(router + 20);
      result = router_exit(num);
    }
    router = next_router;
  }
  if ( !g_IO_RouterExitHandledFlag )
    return plib_malloc__1();
  return result;
}
// 47D510: using guessed type int plib_malloc__1(void);
// 51A604: using guessed type int dword_51A604;
// 54DD98: using guessed type int dword_54DD98;

//----- (00486080) --------------------------------------------------------
signed int  IO_AddRouter(int routerName, int priority, int printFunction, int queryFunction, int getcFunction, int ungetcFunction, int exitFunction)
{
  _DWORD *free_entry; // ebx
  _DWORD *new_router; // eax
  int router_ptr; // ebx
  int current_router; // eax
  int previous_router; // ecx

  free_entry = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 144);
  if ( free_entry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 144);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 144) = *free_entry;
    new_router = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    new_router = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry(36);
  }
  new_router[1] = 1;
  new_router[8] = 0;
  *new_router = routerName;
  new_router[2] = priority;
  new_router[3] = queryFunction;
  new_router[4] = printFunction;
  new_router[5] = exitFunction;
  new_router[6] = getcFunction;
  new_router[7] = ungetcFunction;
  router_ptr = (int)(intptr_t)new_router;
  if ( !g_IO_RouterListHead )
  {
    g_IO_RouterListHead = (int)(intptr_t)new_router;
    return 1;
  }
  current_router = g_IO_RouterListHead;
  previous_router = 0;
  do
  {
    if ( priority >= *(_DWORD *)(uintptr_t)(current_router + 8) )
      break;
    previous_router = current_router;
    current_router = *(_DWORD *)(uintptr_t)(current_router + 32);
  }
  while ( current_router );
  if ( !previous_router )
  {
    *(_DWORD *)(uintptr_t)(router_ptr + 32) = g_IO_RouterListHead;
    g_IO_RouterListHead = router_ptr;
    return 1;
  }
  *(_DWORD *)(uintptr_t)(router_ptr + 32) = current_router;
  *(_DWORD *)(uintptr_t)(previous_router + 32) = router_ptr;
  return 1;
}
// 4860C4: variable 'a3' is possibly undefined
// 51A604: using guessed type int dword_51A604;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00486150) --------------------------------------------------------
signed int  IO_DeleteRouter(int routerName)
{
  int router; // ecx
  _DWORD *previous_router; // esi

  router = g_IO_RouterListHead;
  previous_router = 0;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)(uintptr_t)router, routerName) )
  {
    previous_router = (_DWORD *)(uintptr_t)router;
    router = *(_DWORD *)(uintptr_t)(router + 32);
    if ( !router )
      return 0;
  }
  if ( previous_router )
    previous_router[8] = *(_DWORD *)(uintptr_t)(router + 32);
  else
    g_IO_RouterListHead = *(_DWORD *)(uintptr_t)(router + 32);
  Mem_SmallBlockFree((_DWORD *)(uintptr_t)router, 36);
  return 1;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;

//----- (004861B0) --------------------------------------------------------
int  IO_QueryRouters(int logicalName)
{
  int logical_name; // ebx
  int router; // ecx

  logical_name = logicalName;
  router = g_IO_RouterListHead;
  if ( !g_IO_RouterListHead )
    return 0;
  while ( IO_RouterMatchesName(logical_name, router) != 1 )
  {
    router = *(_DWORD *)(uintptr_t)(router + 32);
    if ( !router )
      return 0;
  }
  return 1;
}
// 51A604: using guessed type int dword_51A604;

//----- (004861E0) --------------------------------------------------------
int __fastcall IO_RouterMatchesName(int logicalName, int router)
{
  int result; // eax
  int (__fastcall *router_query)(int); // eax

  if ( !*(_DWORD *)(uintptr_t)(router + 4) )
    return 0;
  if ( !*(_DWORD *)(uintptr_t)(router + 12) )
    return 0;
  router_query = (int (__fastcall *)(int))(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(router + 12);
  result = router_query(logicalName);
  if ( result != 1 )
    return 0;
  return result;
}

//----- (00486200) --------------------------------------------------------
signed int  IO_DeactivateRouter(int routerName)
{
  int router; // ecx

  router = g_IO_RouterListHead;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)(uintptr_t)router, routerName) )
  {
    router = *(_DWORD *)(uintptr_t)(router + 32);
    if ( !router )
      return 0;
  }
  *(_DWORD *)(uintptr_t)(router + 4) = 0;
  return 1;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;

//----- (00486240) --------------------------------------------------------
signed int  IO_ActivateRouter(int routerName)
{
  int router; // ecx
  signed int result; // eax

  router = g_IO_RouterListHead;
  if ( !router )
    return 0;
  while ( strcmp_(*(_DWORD *)(uintptr_t)router, routerName) )
  {
    router = *(_DWORD *)(uintptr_t)(router + 32);
    if ( !router )
      return 0;
  }
  result = 1;
  *(_DWORD *)(uintptr_t)(router + 4) = 1;
  return result;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A604: using guessed type int dword_51A604;

//----- (00486280) --------------------------------------------------------
int  IO_SetFastLoadFile(int result)
{
  g_IO_FastLoadFilePtr = result;
  return result;
}
// 51A608: using guessed type int dword_51A608;

//----- (00486290) --------------------------------------------------------
int  IO_SetFastSaveFile(int result)
{
  g_IO_FastSaveFilePtr = result;
  return result;
}
// 51A60C: using guessed type int dword_51A60C;

//----- (004862A0) --------------------------------------------------------
int IO_GetFastLoadFile(void)
{
  return g_IO_FastLoadFilePtr;
}
// 51A608: using guessed type int dword_51A608;

//----- (004862C0) --------------------------------------------------------
int  IO_ReportUnrecognizedRouter(int logicalName)
{
  static int reporting_router_error;
  int result; // eax

  if ( reporting_router_error )
    return 0;
  reporting_router_error = 1;
  Rules_PrintErrorID((int)(intptr_t)aRouter, 1, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aLogicalName, 0);
  if ( logicalName )
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], logicalName, 0);
  result = Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aWasNotRecogniz, 0);
  reporting_router_error = 0;
  return result;
}
// 51A614: using guessed type char *off_51A614[5];

//----- (00486414) --------------------------------------------------------
char *__thiscall CRT_AllocateLockSlot(void *this)
{
  int slotIndex; // edx
  int allocatedSlot; // ebx
  int v3; // ecx

  slotIndex = g_CRT_UsedLockSlotCount;
  if ( g_CRT_UsedLockSlotCount >= 64 )
  {
    allocatedSlot = calloc_(this, 24);
    if ( !allocatedSlot )
      _fatal_runtime_error_(v3, 1);
  }
  else
  {
    ++g_CRT_UsedLockSlotCount;
    return (char *)&g_CRT_LockSlotPool + 24 * slotIndex;
  }
  return (char *)(uintptr_t)allocatedSlot;
}
// 48645D: variable 'v3' is possibly undefined
// 49499A: using guessed type int __fastcall _fatal_runtime_error_(_DWORD, _DWORD);
// 4B56B6: using guessed type int __fastcall calloc_(_DWORD, _DWORD);
// 54DEFC: using guessed type int dword_54DEFC;

//----- (00486468) --------------------------------------------------------
void  CRT_ResetLockSlot(int result)
{
  if ( *(_DWORD *)(uintptr_t)(result + 4) )
    DeleteCriticalSection(*(LPCRITICAL_SECTION *)(uintptr_t)result);
  *(_DWORD *)(uintptr_t)(result + 4) = 0;
  *(_DWORD *)(uintptr_t)(result + 8) = 0;
  *(_DWORD *)(uintptr_t)(result + 12) = 0;
}

//----- (00486496) --------------------------------------------------------
void CRT_AcquireStaticLock1(void)
{
  CRT_LockEnter((int)(intptr_t)&g_CRT_StaticLock1);
}

//----- (004864A0) --------------------------------------------------------
void CRT_ReleaseStaticLock1(void)
{
  CRT_LockLeave((int)(intptr_t)&g_CRT_StaticLock1);
}

//----- (004864AA) --------------------------------------------------------
void  CRT_AcquireFileHandleLock(char fileHandle)
{
  CRT_LockEnter((int)(intptr_t)&g_CRT_FileHandleLockSlots + 16 * (fileHandle & 0xF));
}

//----- (004864B7) --------------------------------------------------------
void  CRT_ReleaseFileHandleLock(char fileHandle)
{
  CRT_LockLeave((int)(intptr_t)&g_CRT_FileHandleLockSlots + 16 * (fileHandle & 0xF));
}

//----- (004864CC) --------------------------------------------------------
int  CRT_ReleaseAndUnregisterFileHandle(char fileHandle)
{
  CRT_ResetLockSlot((int)(intptr_t)&g_CRT_FileHandleLockSlots + 16 * (fileHandle & 0xF));
  return _NTRemoveFileHandle_();
}
// 4B4C63: using guessed type int _NTRemoveFileHandle_(void);

//----- (004864E8) --------------------------------------------------------
void CRT_AcquireStaticLock2(void)
{
  CRT_LockEnter((int)(intptr_t)&g_CRT_StaticLock2);
}

//----- (004864EF) --------------------------------------------------------
void CRT_ReleaseStaticLock2(void)
{
  CRT_LockLeave((int)(intptr_t)&g_CRT_StaticLock2);
}

//----- (004864F9) --------------------------------------------------------
void CRT_AcquireStaticLock3(void)
{
  CRT_LockEnter((int)(intptr_t)&g_CRT_StaticLock3);
}

//----- (00486500) --------------------------------------------------------
void CRT_ReleaseStaticLock3(void)
{
  CRT_LockLeave((int)(intptr_t)&g_CRT_StaticLock3);
}

//----- (0048650A) --------------------------------------------------------
void CRT_AcquireStaticLock4(void)
{
  CRT_LockEnter((int)(intptr_t)&g_CRT_StaticLock4);
}

//----- (00486511) --------------------------------------------------------
void CRT_ReleaseStaticLock4(void)
{
  CRT_LockLeave((int)(intptr_t)&g_CRT_StaticLock4);
}

//----- (0048651D) --------------------------------------------------------
void  CRT_LockEnter(int lock)
{
  DWORD CurrentThreadId; // esi
  void *v3; // ecx
  char *criticalSection; // eax

  CurrentThreadId = GetCurrentThreadId();
  if ( CurrentThreadId != *(_DWORD *)(uintptr_t)(lock + 8) )
  {
    if ( !*(_DWORD *)(uintptr_t)(lock + 4) )
    {
      CRT_LockEnter((int)(intptr_t)&g_CRT_LockInitCriticalSection);
      if ( !*(_DWORD *)(uintptr_t)(lock + 4) )
      {
        criticalSection = CRT_AllocateLockSlot(v3);
        *(_DWORD *)(uintptr_t)lock = criticalSection;
        InitializeCriticalSection((LPCRITICAL_SECTION)criticalSection);
        *(_DWORD *)(uintptr_t)(lock + 4) = 1;
      }
      CRT_LockLeave((int)(intptr_t)&g_CRT_LockInitCriticalSection);
    }
    EnterCriticalSection(*(LPCRITICAL_SECTION *)(uintptr_t)lock);
    *(_DWORD *)(uintptr_t)(lock + 8) = CurrentThreadId;
  }
  ++*(_DWORD *)(uintptr_t)(lock + 12);
}
// 486549: variable 'v3' is possibly undefined
// 54DECC: using guessed type int dword_54DECC;

//----- (00486583) --------------------------------------------------------
void  CRT_LockLeave(int result)
{
  int lockCount; // edx
  struct _RTL_CRITICAL_SECTION *criticalSection; // [esp-10h] [ebp-14h]

  lockCount = *(_DWORD *)(uintptr_t)(result + 12);
  if ( lockCount )
  {
    *(_DWORD *)(uintptr_t)(result + 12) = lockCount - 1;
    if ( lockCount == 1 )
    {
      criticalSection = *(struct _RTL_CRITICAL_SECTION **)(uintptr_t)result;
      *(_DWORD *)(uintptr_t)(result + 8) = 0;
      LeaveCriticalSection(criticalSection);
    }
  }
}

//----- (004865AA) --------------------------------------------------------
_BYTE *CRT_GetOrCreateThreadDataPreserveLastError(void)
{
  DWORD LastError; // esi
  _BYTE *Value; // eax
  _BYTE *v2; // ebx
  int ThreadData; // eax

  LastError = GetLastError();
  Value = TlsGetValue(dwTlsIndex);
  v2 = Value;
  if ( !Value )
  {
    ThreadData = _GetThreadData_();
LABEL_5:
    v2 = (_BYTE *)(uintptr_t)ThreadData;
    goto LABEL_6;
  }
  if ( Value[83] )
  {
    ThreadData = _ReallocThreadData_();
    goto LABEL_5;
  }
LABEL_6:
  SetLastError(LastError);
  return v2;
}
// 4B56CE: using guessed type int _GetThreadData_(void);
// 4B5707: using guessed type int _ReallocThreadData_(void);

//----- (004865EE) --------------------------------------------------------
int  CRT_AllocateThreadDataBlock(int a1, int a2)
{
  int thread_data; // eax
  int block_size; // ebx
  int v4; // edx

  if ( !a1 )
  {
    thread_data = calloc_(a2, g_CRT_ThreadDataBlockSize);
    if ( thread_data )
    {
      block_size = g_CRT_ThreadDataBlockSize;
      *(_BYTE *)(uintptr_t)(thread_data + 82) = 1;
      *(_DWORD *)(uintptr_t)(thread_data + 240) = block_size;
    }
  }
  _InitThreadData_(a2);
  return v4;
}
// 48661E: variable 'a2' is possibly undefined
// 486623: variable 'v4' is possibly undefined
// 4B56B6: using guessed type int __fastcall calloc_(_DWORD, _DWORD);
// 4B58D2: using guessed type int __fastcall _InitThreadData_(_DWORD);
// 51AF00: using guessed type int dword_51AF00;

//----- (00486628) --------------------------------------------------------
BOOL CRT_AllocateTlsIndex(void)
{
  dwTlsIndex = TlsAlloc();
  if ( HIWORD(g_WindowsVersionDword) >= 0x8000u && (unsigned __int8)g_WindowsVersionDword < 4u )
  {
    while ( dwTlsIndex <= 2 )
      dwTlsIndex = TlsAlloc();
  }
  return dwTlsIndex != -1;
}
// 486656: simplified comparisons for '$dwTlsIndex.4': ==FFFFFFFF || >=3u became >=3u
// 51A8A7: using guessed type int dword_51A8A7;

//----- (0048667D) --------------------------------------------------------
int  CRT_CreateAndAttachThreadData(int a1, int a2)
{
  int result; // eax
  int v3; // ecx
  void *thread_data; // ebx
  int v5; // ecx

  if ( dwTlsIndex == -1 )
    return 0;
  result = CRT_AllocateThreadDataBlock(a1, a2);
  thread_data = (void *)(uintptr_t)result;
  if ( result )
  {
    if ( !_AddThreadData_(v3, result) )
    {
      nfree_(v5);
      return 0;
    }
    TlsSetValue(dwTlsIndex, thread_data);
    return 1;
  }
  return result;
}
// 4866A2: variable 'v3' is possibly undefined
// 4866AD: variable 'v5' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 4B57DB: using guessed type int __fastcall _AddThreadData_(_DWORD, _DWORD);
