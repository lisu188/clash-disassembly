/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004B529A) --------------------------------------------------------
LPTOP_LEVEL_EXCEPTION_FILTER  CRT_InstallUnhandledExceptionFilter(int a1, int a2)
{
  __int64 v3; // rax
  int v4; // ecx
  __int64 v5; // rax
  int v6; // ecx
  int v7; // ecx
  __int64 v8; // rax

  v3 = g_CrtThreadDataAccessor(a2, a1);
  *(_DWORD *)(v3 + 84) = HIDWORD(v3);
  v5 = g_CrtThreadDataAccessor(v4, NtCurrentTeb()->NtTib.ExceptionList);
  **(_DWORD **)(v5 + 84) = HIDWORD(v5);
  *(_DWORD *)(*(_DWORD *)(g_CrtThreadDataAccessor(v6, HIDWORD(v5)) + 84) + 4) = CRT_FpuExceptionFrameHandler;
  v8 = g_CrtThreadDataAccessor(v7, 0);
  __writefsdword(HIDWORD(v8), *(_DWORD *)(v8 + 84));
  return SetUnhandledExceptionFilter(TopLevelExceptionFilter);
}
// 4B52AE: variable 'v4' is possibly undefined
// 4B52B9: variable 'v6' is possibly undefined
// 4B52CB: variable 'v7' is possibly undefined
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004B52E6) --------------------------------------------------------
int __fastcall CRT_RemoveUnhandledExceptionFilter(int a1, int a2)
{
  unsigned int *exceptionRegistration; // eax
  int v3; // edx
  int v4; // ecx
  int result; // eax

  exceptionRegistration = *(unsigned int **)(g_CrtThreadDataAccessor(a1, a2) + 84);
  if ( exceptionRegistration )
  {
    v3 = 0;
    __writefsdword(0, *exceptionRegistration);
  }
  result = g_CrtThreadDataAccessor(v4, v3);
  *(_DWORD *)(result + 84) = 0;
  return result;
}
// 4B52FB: variable 'v4' is possibly undefined
// 4B52FB: variable 'v3' is possibly undefined
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004B5310) --------------------------------------------------------
signed int IO_InitializeFileIORouter(void)
{
  return IO_AddRouter(
           (int)aFileio,
           0,
           (int)IO_FileIOQueryCallback,
           (int)ismbdprint_,
           (int)IO_FileIOGetcCallback,
           (int)IO_FileIOUngetcCallback,
           (int)IO_FileIOExitCallback);
}

//----- (004B5340) --------------------------------------------------------
int __thiscall IO_FindOpenFileByLogicalName(void *this)
{
  int result; // eax
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  _DWORD *fileListCursor; // ecx

  result = strcmp_(this, aStdout_1);
  if ( result )
  {
    result = strcmp_(v2, aStdin_0);
    if ( result )
    {
      result = strcmp_(v3, g_IO_LogicalNameTable_WTrace[0]);
      if ( result )
      {
        result = strcmp_(v4, g_IO_LogicalNameTable_WDialog[0]);
        if ( result )
        {
          result = strcmp_(v5, g_IO_LogicalNameTable_WClips[0]);
          if ( result )
          {
            result = strcmp_(v6, g_IO_LogicalName_WDisplay);
            if ( result )
            {
              result = strcmp_(v7, g_IO_LogicalNameTable_WError[0]);
              if ( result )
              {
                result = strcmp_(v8, g_IO_LogicalNameTable_WWarning[0]);
                if ( result )
                {
                  fileListCursor = (_DWORD *)g_IO_LogicalNameFileListHead;
                  if ( g_IO_LogicalNameFileListHead )
                  {
                    do
                    {
                      if ( !strcmp_(fileListCursor, *fileListCursor) )
                        break;
                      fileListCursor = (_DWORD *)fileListCursor[2];
                    }
                    while ( fileListCursor );
                  }
                  if ( fileListCursor )
                    return fileListCursor[1];
                  else
                    return 0;
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}
// 4B535E: variable 'v2' is possibly undefined
// 4B536F: variable 'v3' is possibly undefined
// 4B5380: variable 'v4' is possibly undefined
// 4B5391: variable 'v5' is possibly undefined
// 4B53A2: variable 'v6' is possibly undefined
// 4B53B3: variable 'v7' is possibly undefined
// 4B53C4: variable 'v8' is possibly undefined
// 4B53EC: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A620: using guessed type char *off_51A620[2];
// 51A624: using guessed type char *off_51A624;
// 51AEF8: using guessed type int dword_51AEF8;

//----- (004B5410) --------------------------------------------------------
int ismbdprint_(void *logical_name)
{
  return IO_FindOpenFileByLogicalName(logical_name) != 0;
}

//----- (004B5420) --------------------------------------------------------
signed int __thiscall IO_FileIOExitCallback(void *this)
{
  IO_CloseAllNamedFiles(this);
  return 1;
}

//----- (004B5430) --------------------------------------------------------
int __fastcall IO_FileIOQueryCallback(int a1, void *logicalName)
{
  int filePtr; // eax
  int v3; // ecx
  int v4; // ecx

  filePtr = IO_FindOpenFileByLogicalName(logicalName);
  Output_WriteFormatted(v3, filePtr, filePtr, (int)aS_13, v3);
  fflush_(v4);
  return 1;
}
// 4B5441: variable 'v3' is possibly undefined
// 4B544B: variable 'v4' is possibly undefined
// 48A216: using guessed type int __thiscall fflush_(_DWORD);

//----- (004B5460) --------------------------------------------------------
int __thiscall IO_FileIOGetcCallback(void *this)
{
  int v1; // ecx
  __int64 v2; // rax
  unsigned __int8 *bufferPtr; // ecx

  LODWORD(v2) = IO_FindOpenFileByLogicalName(this);
  v1 = *(_DWORD *)(v2 + 4);
  HIDWORD(v2) = v2;
  if ( v1 > 0 && (v1 = **(unsigned __int8 **)v2 - 13, (unsigned int)v1 > 0xFD) )
  {
    bufferPtr = *(unsigned __int8 **)v2;
    --*(_DWORD *)(v2 + 4);
    *(_DWORD *)v2 = bufferPtr + 1;
    LODWORD(v2) = *bufferPtr;
  }
  else
  {
    v2 = fgetc_(v1, v2);
  }
  if ( v2 == __PAIR64__(&g_IO_FileGetcSentinelAddr, -1) )
    g_IO_FileGetcStreamFlags &= 0xCFu;
  return v2;
}
// 488F44: using guessed type __int64 __fastcall fgetc_(_DWORD, _DWORD);
// 51A34C: using guessed type char byte_51A34C;

//----- (004B54D0) --------------------------------------------------------
signed int  IO_FileIOUngetcCallback(void *logicalName)
{
  signed int v1; // ecx

  IO_FindOpenFileByLogicalName(logicalName);
  return CRT_FlushBufferAndPutChar(v1, v1);
}
// 4B54DE: variable 'v1' is possibly undefined

//----- (004B54F0) --------------------------------------------------------
int  IO_OpenNamedFile(
        const CHAR *fileName,
        unsigned __int8 *accessMode,
        int a3,
        const char *logicalName,
        DWORD a5)
{
  int result; // eax
  int filePtr; // ebp
  _DWORD *freeListHead; // ecx
  const char *nameCursor; // esi
  _DWORD *fileEntry; // edx
  _BYTE *nameCopy; // edi
  char curByte; // al
  char nextByte; // al

  result = IO_FOpen(fileName, accessMode, a3, a5);
  filePtr = result;
  if ( result )
  {
    freeListHead = *(_DWORD **)(g_ClipsMemoryTable + 48);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeListHead;
    }
    else
    {
      Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    nameCursor = logicalName;
    nameCopy = Mem_SmallBlockAlloc(strlen(logicalName) + 1);
    *fileEntry = nameCopy;
    do
    {
      curByte = *nameCursor;
      *nameCopy = *nameCursor;
      if ( !curByte )
        break;
      nextByte = nameCursor[1];
      nameCursor += 2;
      nameCopy[1] = nextByte;
      nameCopy += 2;
    }
    while ( nextByte );
    fileEntry[1] = filePtr;
    fileEntry[2] = g_IO_LogicalNameFileListHead;
    result = 1;
    g_IO_LogicalNameFileListHead = (int)fileEntry;
  }
  return result;
}
// 4B5535: variable 'v9' is possibly undefined
// 51AEF8: using guessed type int dword_51AEF8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004B5580) --------------------------------------------------------
signed int  IO_CloseNamedFile(int logicalName)
{
  int v1; // ecx
  int fileEntry; // ebx
  int previousEntry; // esi

  v1 = logicalName;
  fileEntry = g_IO_LogicalNameFileListHead;
  previousEntry = 0;
  if ( !g_IO_LogicalNameFileListHead )
    return 0;
  while ( strcmp_(v1, v1) )
  {
    previousEntry = fileEntry;
    fileEntry = *(_DWORD *)(fileEntry + 8);
    if ( !fileEntry )
      return 0;
  }
  fclose_(v1);
  Mem_SmallBlockFree(*(_DWORD **)fileEntry, strlen(*(const char **)fileEntry) + 1);
  if ( previousEntry )
    *(_DWORD *)(previousEntry + 8) = *(_DWORD *)(fileEntry + 8);
  else
    g_IO_LogicalNameFileListHead = *(_DWORD *)(fileEntry + 8);
  Mem_SmallBlockFree((_DWORD *)fileEntry, 12);
  return 1;
}
// 4B5596: variable 'v1' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51AEF8: using guessed type int dword_51AEF8;

//----- (004B5600) --------------------------------------------------------
signed int __thiscall IO_CloseAllNamedFiles(void *this)
{
  _DWORD **fileEntry; // ebx
  _DWORD *currentEntry; // eax
  signed int result; // eax

  if ( !g_IO_LogicalNameFileListHead )
    return 0;
  fileEntry = (_DWORD **)g_IO_LogicalNameFileListHead;
  do
  {
    fclose_(this);
    Mem_SmallBlockFree(*fileEntry, strlen((const char *)*fileEntry) + 1);
    currentEntry = fileEntry;
    fileEntry = (_DWORD **)fileEntry[2];
    Mem_SmallBlockFree(currentEntry, 12);
  }
  while ( fileEntry );
  result = 1;
  g_IO_LogicalNameFileListHead = 0;
  return result;
}
// 4B5616: variable 'this' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51AEF8: using guessed type int dword_51AEF8;

//----- (004B5BA0) --------------------------------------------------------
int  CRT_MapAccessModeToCreateFileFlags(int result, _DWORD *desiredAccess, _DWORD *fileAttributes)
{
  if ( result == 2 )
  {
    *desiredAccess = -1073741824;
LABEL_3:
    *fileAttributes = 128;
    return result;
  }
  if ( result == 1 )
  {
    *desiredAccess = 0x40000000;
    goto LABEL_3;
  }
  *desiredAccess = 0x80000000;
  *fileAttributes = 1;
  return result;
}

//----- (004B5BCC) --------------------------------------------------------
unsigned int  CRT_MapOpenFlagsToCreationDisposition(char openFlags, _DWORD *creationDisposition)
{
  unsigned int result; // eax
  int accessBits; // ebx

  result = openFlags & 0x70;
  accessBits = openFlags & 7;
  if ( result < 0x20 )
  {
    if ( result )
    {
      if ( result == 16 )
        *creationDisposition = 0;
    }
    else
    {
      *creationDisposition = 1;
      if ( !accessBits )
        *(_BYTE *)creationDisposition |= 2u;
    }
  }
  else if ( result <= 0x20 )
  {
    *creationDisposition = 1;
  }
  else if ( result >= 0x30 )
  {
    if ( result <= 0x30 )
    {
      *creationDisposition = 2;
    }
    else if ( result == 64 )
    {
      *creationDisposition = 3;
    }
  }
  return result;
}

//----- (004B5C7A) --------------------------------------------------------
int  CRT_CheckReadOnlyBeforeOpen(const CHAR *fileName, char openFlags, int a3)
{
  DWORD FileAttributesA; // eax

  FileAttributesA = GetFileAttributesA(fileName);
  if ( FileAttributesA == -1 )
    return _set_errno_nt_(a3);
  if ( (openFlags & 2) != 0 && (FileAttributesA & 1) != 0 )
    return _set_errno_dos_(a3);
  return 0;
}
// 485306: using guessed type int __cdecl _set_errno_dos_(_DWORD);
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (004B5CAE) --------------------------------------------------------
int __fastcall CRT_GetThreadErrnoPtr(int a1, int a2)
{
  return g_CrtThreadDataAccessor(a1, a2) + 4;
}
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);

//----- (004B5E0A) --------------------------------------------------------
BOOL  CRT_IsLeapYear(unsigned int year)
{
  return (year & 3) == 0 && (year % 0x64 || !(year % 0x190));
}

//----- (004B5E3D) --------------------------------------------------------
int  CRT_TzRuleDayOfYear(_DWORD *tzRule, int year)
{
  int ruleType; // ecx
  int v4; // edx
  int ruleMonth; // eax
  int nextMonthYday; // esi
  int monthYday; // eax
  int v8; // eax
  int daysInMonth; // esi
  int weekdayOffset; // edx
  int ruleWeek; // eax
  int weekNumber; // eax
  _DWORD timeFields[14]; // [esp+0h] [ebp-38h] BYREF

  ruleType = tzRule[8];
  if ( ruleType )
  {
    if ( ruleType == 1 )
      return tzRule[7] - 1;
    else
      return tzRule[7];
  }
  else
  {
    if ( CRT_IsLeapYear(year + 1900) )
    {
      ruleMonth = tzRule[4];
      nextMonthYday = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth + 2);
      monthYday = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth);
    }
    else
    {
      v8 = tzRule[4];
      nextMonthYday = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * v8 + 2);
      monthYday = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * v8);
    }
    daysInMonth = (nextMonthYday >> 16) - (monthYday >> 16);
    memset(timeFields, 0, 12);
    timeFields[3] = 1;
    timeFields[4] = tzRule[4];
    timeFields[5] = v4;
    timeFields[8] = 0;
    CRT_MkTime((int)timeFields);
    weekdayOffset = (tzRule[6] - timeFields[6] + 7) % 7;
    ruleWeek = tzRule[3];
    if ( ruleWeek == 5 )
    {
      if ( weekdayOffset + 29 <= daysInMonth )
        weekNumber = 4;
      else
        weekNumber = tzRule[3] - 2;
    }
    else
    {
      weekNumber = ruleWeek - 1;
    }
    return weekdayOffset + timeFields[7] + 7 * weekNumber;
  }
}
// 4B5EAA: variable 'v4' is possibly undefined
// 5110EE: using guessed type int dword_5110EE;
// 511108: using guessed type int dword_511108;

//----- (004B5F22) --------------------------------------------------------
signed int  CRT_TzYearStartsInDaylightTime(_DWORD *dstStartRule, int dstEndRule, int year)
{
  int startMonth; // esi
  int endMonth; // edi
  int startYday; // esi
  _DWORD *endRulePtr; // ecx

  if ( dstStartRule[8] || *(_DWORD *)(dstEndRule + 32) )
    goto LABEL_6;
  startMonth = dstStartRule[4];
  endMonth = *(_DWORD *)(dstEndRule + 16);
  if ( startMonth > endMonth )
    return 1;
  if ( startMonth >= endMonth )
  {
LABEL_6:
    startYday = CRT_TzRuleDayOfYear(dstStartRule, year);
    if ( startYday > CRT_TzRuleDayOfYear(endRulePtr, year) )
      return 1;
  }
  return 0;
}
// 4B5F55: variable 'v7' is possibly undefined

//----- (004B5F64) --------------------------------------------------------
int  CRT_IsDaylightTime(_DWORD *timeFields)
{
  _DWORD *tmFields; // ecx
  int inDaylight; // edi
  int v3; // ecx
  int *firstRule; // esi
  int *secondRule; // ebx
  int ruleMonth; // ebp
  int monthEndOffset; // edx
  int monthStartOffset; // eax
  int firstRuleMode; // eax
  int firstRuleMonth; // edx
  int firstRuleWeek; // edx
  int firstRuleWeekStartDom; // eax
  int firstRuleDay; // edx
  int firstRuleDayLeap; // edx
  int tmYday; // eax
  int secondRuleMode; // esi
  int secondRuleMonth; // eax
  int secondRuleCandidateDay; // ebp
  int secondRuleWeek; // esi
  int secondRuleCandidateDayPrev; // edx
  int secondRuleWeekStartDom; // eax
  int secondRuleDay; // edx
  int secondRuleDayLeap; // edx
  int currentTmYday; // eax
  int result; // eax
  int v26; // [esp+8h] [ebp-2Ch]
  int v27; // [esp+Ch] [ebp-28h]
  int daysInMonth; // [esp+10h] [ebp-24h]
  signed int startsInDst; // [esp+14h] [ebp-20h]

  tmFields = timeFields;
  inDaylight = 0;
  if ( !*g_CRT_TzDaylightNamePtr )
    goto LABEL_54;
  startsInDst = CRT_TzYearStartsInDaylightTime(g_CRT_TzDstStartRule, (int)&g_CRT_TzDstEndRule, timeFields[5]);
  if ( startsInDst )
  {
    firstRule = &g_CRT_TzDstEndRule;
    secondRule = g_CRT_TzDstStartRule;
  }
  else
  {
    firstRule = g_CRT_TzDstStartRule;
    secondRule = &g_CRT_TzDstEndRule;
  }
  ruleMonth = *(_DWORD *)(v3 + 16);
  if ( CRT_IsLeapYear(*(_DWORD *)(v3 + 20) + 1900) )
  {
    monthEndOffset = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth + 2);
    monthStartOffset = *(int *)((char *)&g_CRT_LeapMonthDayTable + 2 * ruleMonth);
  }
  else
  {
    monthEndOffset = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * ruleMonth + 2);
    monthStartOffset = *(int *)((char *)&g_CRT_NonLeapMonthDayTable + 2 * ruleMonth);
  }
  daysInMonth = (monthEndOffset >> 16) - (monthStartOffset >> 16);
  firstRuleMode = firstRule[8];
  if ( firstRuleMode )
  {
    firstRuleDay = firstRule[7];
    if ( firstRuleMode == 1 )
    {
      if ( CRT_IsLeapYear(tmFields[5] + 1900) && firstRuleDayLeap > g_CRT_NonLeapFebMarDayThreshold >> 16 )
        ++firstRuleDayLeap;
      firstRuleDay = firstRuleDayLeap - 1;
    }
    tmYday = tmFields[7];
    if ( firstRuleDay <= tmYday )
    {
      inDaylight = 1;
      if ( firstRuleDay == tmYday )
        goto LABEL_27;
    }
  }
  else
  {
    firstRuleMonth = firstRule[4];
    if ( ruleMonth > firstRuleMonth )
    {
      inDaylight = 1;
      goto LABEL_28;
    }
    if ( ruleMonth == firstRuleMonth )
    {
      v26 = tmFields[3] - (tmFields[6] + 7 - firstRule[6]) % 7;
      firstRuleWeek = firstRule[3];
      v27 = tmFields[3] - 1 - (tmFields[6] + 6 - firstRule[6]) % 7;
      if ( firstRuleWeek == 5 )
      {
        if ( daysInMonth - 7 < v26 )
        {
          inDaylight = 1;
          if ( daysInMonth - 7 >= v27 )
LABEL_27:
            inDaylight = CRT_CompareTzTransitionDate(tmFields, firstRule) == 0;
        }
      }
      else
      {
        firstRuleWeekStartDom = 7 * (firstRuleWeek - 1) + 1;
        if ( firstRuleWeekStartDom <= v26 )
        {
          inDaylight = 1;
          if ( firstRuleWeekStartDom > v27 )
            goto LABEL_27;
        }
      }
    }
  }
LABEL_28:
  if ( !inDaylight )
  {
    if ( startsInDst )
      inDaylight = startsInDst;
    goto LABEL_54;
  }
  secondRuleMode = secondRule[8];
  if ( secondRuleMode )
  {
    secondRuleDay = secondRule[7];
    if ( secondRuleMode == 1 )
    {
      if ( CRT_IsLeapYear(tmFields[5] + 1900) && secondRuleDayLeap > g_CRT_NonLeapFebMarDayThreshold >> 16 )
        ++secondRuleDayLeap;
      secondRuleDay = secondRuleDayLeap - 1;
    }
    currentTmYday = tmFields[7];
    if ( secondRuleDay > currentTmYday )
      goto LABEL_52;
    inDaylight = 0;
    if ( secondRuleDay != currentTmYday )
      goto LABEL_52;
    goto LABEL_51;
  }
  secondRuleMonth = secondRule[4];
  if ( ruleMonth > secondRuleMonth )
  {
    inDaylight = 0;
    goto LABEL_52;
  }
  if ( ruleMonth != secondRuleMonth )
    goto LABEL_52;
  secondRuleCandidateDay = tmFields[3] - (tmFields[6] + 7 - secondRule[6]) % 7;
  inDaylight = 0;
  secondRuleWeek = secondRule[3];
  secondRuleCandidateDayPrev = tmFields[3] - 1 - (tmFields[6] + 6 - secondRule[6]) % 7;
  if ( secondRuleWeek != 5 )
  {
    secondRuleWeekStartDom = 7 * (secondRuleWeek - 1) + 1;
    if ( secondRuleCandidateDay < secondRuleWeekStartDom )
      goto LABEL_37;
    if ( secondRuleCandidateDayPrev >= secondRuleWeekStartDom )
      goto LABEL_52;
LABEL_51:
    inDaylight = CRT_CompareTzTransitionDate(tmFields, secondRule);
    goto LABEL_52;
  }
  if ( secondRuleCandidateDay <= daysInMonth - 7 )
  {
LABEL_37:
    inDaylight = 1;
    goto LABEL_52;
  }
  if ( secondRuleCandidateDayPrev <= daysInMonth - 7 )
    goto LABEL_51;
LABEL_52:
  if ( startsInDst )
    inDaylight = startsInDst - inDaylight;
LABEL_54:
  result = inDaylight;
  tmFields[8] = inDaylight;
  return result;
}
// 4B60F4: conditional instruction was optimized away because %var_30.4==0
// 4B61EB: conditional instruction was optimized away because %var_34.4==0
// 4B5FB8: variable 'v3' is possibly undefined
// 4B6034: variable 'v1' is possibly undefined
// 4B60DD: variable 'v14' is possibly undefined
// 4B61D5: variable 'v23' is possibly undefined
// 5110EE: using guessed type int dword_5110EE;
// 5110F2: using guessed type int dword_5110F2;
// 511108: using guessed type int dword_511108;
// 51AF68: using guessed type _DWORD dword_51AF68[9];
// 51AF8C: using guessed type int dword_51AF8C;
// 51B0B6: using guessed type char *off_51B0B6;

//----- (004B6213) --------------------------------------------------------
signed int  CRT_CompareTzTransitionDate(_DWORD *timeFields, _DWORD *tzRule)
{
  int hour; // ecx
  int ruleHour; // esi
  int v4; // ebx
  int minute; // ecx
  int ruleMinute; // ebp

  hour = timeFields[2];
  ruleHour = tzRule[2];
  v4 = 0;
  if ( hour < ruleHour )
    return 1;
  if ( hour == ruleHour )
  {
    minute = timeFields[1];
    ruleMinute = tzRule[1];
    if ( minute < ruleMinute || minute == ruleMinute && *timeFields < *tzRule )
      return 1;
  }
  return v4;
}

//----- (004B63CC) --------------------------------------------------------
void __thiscall CRT_TzSetFromSystemInfo(int this)
{
  DWORD TimeZoneInformation; // eax
  int v4; // ecx
  int v5; // ecx
  struct _TIME_ZONE_INFORMATION v6; // [esp+0h] [ebp-BCh] BYREF
  int v7; // [esp+B4h] [ebp-8h]

  v7 = this;
  if ( (g_TzInitFlags & 1) == 0 || (g_TzInitFlags & 2) == 0 )
  {
    LOBYTE(g_TzInitFlags) = g_TzInitFlags | 2;
    TimeZoneInformation = GetTimeZoneInformation(&v6);
    if ( TimeZoneInformation )
    {
      if ( TimeZoneInformation <= 1 )
      {
        v4 = 0;
        g_TzDaylightFlag = 0;
      }
      else
      {
        if ( TimeZoneInformation != 2 )
          return;
        g_TzDaylightFlag = 1;
        g_CRT_DaylightBiasSeconds = -60 * v6.DaylightBias;
      }
      g_CRT_TimezoneSeconds = 60 * (v6.Bias + v6.StandardBias);
      if ( wcstombs_(v4, v6.StandardName) == -1 )
        g_TzStandardNameBuffer = 0;
      else
        g_CRT_TzStandardNameBufEnd = 0;
      if ( wcstombs_(v5, v6.DaylightName) == -1 )
        g_TzDaylightName = 0;
      else
        g_CRT_TzDaylightNameBufEnd = 0;
    }
  }
}
// 4B6471: variable 'v4' is possibly undefined
// 4B649B: variable 'v5' is possibly undefined
// 4D9993: using guessed type int __fastcall wcstombs_(_DWORD, _DWORD);
// 51AFB0: using guessed type char byte_51AFB0;
// 51B030: using guessed type char byte_51B030;
// 51B031: using guessed type char byte_51B031;
// 51B0B1: using guessed type char byte_51B0B1;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0BE: using guessed type int dword_51B0BE;
// 51B0C2: using guessed type int dword_51B0C2;
// 51B0C6: using guessed type int dword_51B0C6;

//----- (004B64C2) --------------------------------------------------------
void CRT_TzSet(void)
{
  _BYTE *tzEnvString; // eax
  int v1; // edx
  int v2; // ecx
  _BYTE *afterStdName; // ecx
  _BYTE *afterDstName; // eax
  int v5; // ecx
  _BYTE *ruleCursor; // edx
  int dstOffset[7]; // [esp+0h] [ebp-1Ch] BYREF

  tzEnvString = (_BYTE *)getenv_();
  if ( tzEnvString )
  {
    dstOffset[5] = v2;
    dstOffset[4] = v1;
    g_TzDaylightFlag = 0;
    afterStdName = CRT_ParseTzNameAndOffset(tzEnvString, &g_TzStandardNameBuffer, &g_CRT_TimezoneSeconds);
    if ( *afterStdName )
    {
      g_TzDaylightFlag = 1;
      dstOffset[0] = g_CRT_TimezoneSeconds - 3600;
      afterDstName = CRT_ParseTzNameAndOffset(afterStdName, &g_TzDaylightName, dstOffset);
      v5 = dstOffset[0];
      g_CRT_DaylightBiasSeconds = g_CRT_TimezoneSeconds - dstOffset[0];
      ruleCursor = afterDstName;
      if ( *afterDstName == 44 )
        ruleCursor = CRT_ParseTzDstRule(afterDstName + 1, (int)g_CRT_TzDstStartRule, dstOffset[0]);
      if ( *ruleCursor == 44 )
      {
        CRT_ParseTzDstRule(ruleCursor + 1, (int)&g_CRT_TzDstEndRule, v5);
        g_CRT_TzDstEndRuleHour -= g_CRT_DaylightBiasSeconds / 3600;
        g_CRT_TzDstEndRuleMinute -= g_CRT_DaylightBiasSeconds / 60 % 60;
        g_CRT_TzDstEndRule -= g_CRT_DaylightBiasSeconds % 60;
      }
    }
    else
    {
      g_TzDaylightName = 0;
    }
  }
  else
  {
    CRT_TzSetFromSystemInfo(v2);
  }
}
// 4B64D5: variable 'v2' is possibly undefined
// 4B64D6: variable 'v1' is possibly undefined
// 4B678E: variable 'v5' is possibly undefined
// 4B5CC2: using guessed type int getenv_(void);
// 51AF68: using guessed type _DWORD dword_51AF68[9];
// 51AF8C: using guessed type int dword_51AF8C;
// 51AF90: using guessed type int dword_51AF90;
// 51AF94: using guessed type int dword_51AF94;
// 51AFB0: using guessed type char byte_51AFB0;
// 51B031: using guessed type char byte_51B031;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0BE: using guessed type int dword_51B0BE;
// 51B0C2: using guessed type int dword_51B0C2;

//----- (004B650B) --------------------------------------------------------
_BYTE * CRT_ParseTzDecimalDigits(_BYTE *result, int *valueOut)
{
  int value; // edx
  int v4; // edx

  value = 0;
  while ( *result >= 0x30u && *result <= 0x39u )
  {
    v4 = (unsigned __int8)*result++ + 10 * value;
    value = v4 - 48;
  }
  *valueOut = value;
  return result;
}

//----- (004B6531) --------------------------------------------------------
_BYTE * CRT_ParseTzNameAndOffset(_BYTE *tzString, void *nameBuffer, _DWORD *offsetSecondsOut)
{
  _BYTE *cursor; // ebp
  _BYTE *nameStart; // esi
  unsigned __int8 curChar; // dl
  _BYTE *afterHours; // eax
  int isNegative; // ecx
  _BYTE *afterMinutes; // eax
  int totalSeconds; // edx
  int seconds; // [esp+4h] [ebp-20h] BYREF
  int minutes; // [esp+8h] [ebp-1Ch] BYREF
  int hours; // [esp+Ch] [ebp-18h] BYREF
  unsigned int nameLength; // [esp+10h] [ebp-14h]

  cursor = tzString;
  if ( *tzString == 58 )
    cursor = tzString + 1;
  nameStart = cursor;
  while ( 1 )
  {
    curChar = *cursor;
    if ( !*cursor || curChar == 44 || curChar == 45 || curChar == 43 || curChar >= 0x30u && curChar <= 0x39u )
      break;
    ++cursor;
  }
  nameLength = cursor - nameStart;
  if ( cursor - nameStart > 128 )
    nameLength = 128;
  qmemcpy(nameBuffer, nameStart, nameLength);
  *((_BYTE *)nameBuffer + nameLength) = 0;
  if ( curChar == 45 || curChar == 43 )
    ++cursor;
  if ( *cursor >= 0x30u && *cursor <= 0x39u )
  {
    seconds = 0;
    minutes = 0;
    hours = 0;
    afterHours = CRT_ParseTzDecimalDigits(cursor, &hours);
    cursor = afterHours;
    if ( *afterHours == 58 )
    {
      afterMinutes = CRT_ParseTzDecimalDigits(afterHours + 1, &minutes);
      cursor = afterMinutes;
      if ( *afterMinutes == 58 )
        cursor = CRT_ParseTzDecimalDigits(afterMinutes + 1, &seconds);
    }
    totalSeconds = 60 * (60 * hours + minutes) + seconds;
    *offsetSecondsOut = totalSeconds;
    if ( isNegative )
      *offsetSecondsOut = -totalSeconds;
  }
  return cursor;
}
// 4B6636: variable 'v7' is possibly undefined

//----- (004B6646) --------------------------------------------------------
_BYTE * CRT_ParseTzDstRule(_BYTE *ruleString, int ruleStruct, int offsetSeconds)
{
  _BYTE *cursor; // ebx
  int ruleType; // esi
  _BYTE *v5; // edx
  _DWORD *ruleFields; // ecx
  _BYTE *v7; // ebx
  _BYTE *v8; // edx
  _BYTE *v9; // eax
  _BYTE *v10; // eax
  int second; // [esp+0h] [ebp-1Ch] BYREF
  int minute; // [esp+4h] [ebp-18h] BYREF
  int hour; // [esp+8h] [ebp-14h] BYREF
  int parsed[4]; // [esp+Ch] [ebp-10h] BYREF

  parsed[2] = offsetSeconds;
  cursor = ruleString;
  ruleType = -1;
  if ( *ruleString == 74 )
  {
    ruleType = 1;
    cursor = ruleString + 1;
  }
  if ( *cursor == 77 )
  {
    ++cursor;
    ruleType = 0;
  }
  *(_DWORD *)(ruleStruct + 32) = ruleType;
  v5 = CRT_ParseTzDecimalDigits(cursor, parsed);
  v7 = v5;
  if ( ruleType )
  {
    ruleFields[7] = parsed[0];
  }
  else
  {
    ruleFields[4] = parsed[0] - 1;
    if ( *v5 == 46 )
    {
      v8 = CRT_ParseTzDecimalDigits(v5 + 1, parsed);
      v7 = v8;
      ruleFields[3] = parsed[0];
      if ( *v8 == 46 )
      {
        v7 = CRT_ParseTzDecimalDigits(v8 + 1, parsed);
        ruleFields[6] = parsed[0];
      }
    }
    ruleFields[7] = 0;
  }
  hour = 2;
  second = 0;
  minute = 0;
  if ( *v7 == 47 )
  {
    v9 = CRT_ParseTzDecimalDigits(v7 + 1, &hour);
    v7 = v9;
    if ( *v9 == 58 )
    {
      v10 = CRT_ParseTzDecimalDigits(v9 + 1, &minute);
      v7 = v10;
      if ( *v10 == 58 )
        v7 = CRT_ParseTzDecimalDigits(v10 + 1, &second);
    }
  }
  *ruleFields = second;
  ruleFields[1] = minute;
  ruleFields[2] = hour;
  return v7;
}
// 4B6685: variable 'v6' is possibly undefined

//----- (004B6DD0) --------------------------------------------------------
int Rules_RegisterPatternConstraintEvaluators()
{
  g_EvalDesc_FetchJoinBindingFieldRecord[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldRecord[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldRecord[4] = (int)(uintptr_t)Rules_FetchJoinBindingFieldRecord;
  g_EvalDesc_FetchJoinBindingFieldSimple[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldSimple[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingFieldSimple[4] = (int)(uintptr_t)Rules_FetchJoinBindingFieldSimple;
  g_EvalDesc_FetchJoinBindingNestedField[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingNestedField[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchJoinBindingNestedField[4] = (int)(uintptr_t)Rules_FetchJoinBindingNestedField;
  g_EvalDesc_FetchPatternFieldRecord[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldRecord[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldRecord[4] = (int)(uintptr_t)Rules_FetchPatternFieldRecord;
  g_EvalDesc_FetchPatternFieldSimple[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldSimple[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternFieldSimple[4] = (int)(uintptr_t)Rules_FetchPatternFieldSimple;
  g_EvalDesc_FetchPatternNestedFieldRecord[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternNestedFieldRecord[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_FetchPatternNestedFieldRecord[4] = (int)(uintptr_t)Rules_FetchPatternNestedFieldRecord;
  g_EvalDesc_TestJoinBindingFieldsEqual[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqual[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqual[4] = (int)(uintptr_t)Rules_TestJoinBindingFieldsEqual;
  g_EvalDesc_TestJoinBindingFieldsEqualRanged[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqualRanged[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestJoinBindingFieldsEqualRanged[4] = (int)(uintptr_t)Rules_TestJoinBindingFieldsEqualRanged;
  g_EvalDesc_EvalPatternFieldsEqual[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalPatternFieldsEqual[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalPatternFieldsEqual[4] = (int)(uintptr_t)Rules_EvalPatternFieldsEqual;
  g_EvalNodeDescCopyMultifieldBinding[4] = (int)(uintptr_t)Rules_EvalCopyMultifieldBinding;
  g_EvalDesc_EvalMultifieldIndexInRange[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalMultifieldIndexInRange[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_EvalMultifieldIndexInRange[4] = (int)(uintptr_t)Rules_EvalMultifieldIndexInRange;
  g_EvalDesc_TestPatternFieldSimple[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternFieldSimple[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternFieldSimple[4] = (int)(uintptr_t)Rules_TestPatternFieldSimple;
  g_EvalDesc_TestPatternNestedField[1] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternNestedField[2] = (int)(uintptr_t)Runtime_DescriptorNoop;
  g_EvalDesc_TestPatternNestedField[4] = (int)(uintptr_t)Rules_TestPatternNestedField;
  Rules_RegisterEvaluationHandler((int)&g_Rules_FactPatternEntityRecord, 6);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchJoinBindingFieldRecord, 29);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchJoinBindingFieldSimple, 30);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchJoinBindingNestedField, 31);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchPatternFieldRecord, 26);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchPatternFieldSimple, 27);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_FetchPatternNestedFieldRecord, 28);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestJoinBindingFieldsEqual, 23);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestJoinBindingFieldsEqualRanged, 24);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_EvalPatternFieldsEqual, 22);
  Rules_RegisterEvaluationHandler((int)&g_EvalNodeDescCopyMultifieldBinding, 34);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_EvalMultifieldIndexInRange, 25);
  Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestPatternFieldSimple, 32);
  return Rules_RegisterEvaluationHandler((int)&g_EvalDesc_TestPatternNestedField, 33);
}

//----- (004B6EB0) --------------------------------------------------------
signed int  Rules_BuildFieldIndexConstraintNode(int fieldDescriptor)
{
  int fieldFlags; // edx
  int v2; // ecx
  int v3; // eax
  int v4; // eax
  int bitmapValue; // eax
  signed int constraintNode; // ebx
  _DWORD *v7; // ecx
  int v9; // ecx
  unsigned __int8 v10; // al
  int indexBitmapValue; // eax
  signed int indexConstraintNode; // ebx
  _DWORD *v13; // ecx
  int v14; // eax
  int comparisonSymbol; // edx
  signed int testNode; // ebx
  int *v17; // ecx
  int savedFieldType; // edx
  int v19; // edx
  _DWORD *v20; // ecx
  int bitmapWord; // [esp+0h] [ebp-1Ch] BYREF
  _DWORD bitmapData[6]; // [esp+4h] [ebp-18h] BYREF

  if ( (*(_BYTE *)(fieldDescriptor + 9) & 0x40) != 0 )
  {
    fieldFlags = *(_DWORD *)(fieldDescriptor + 8);
    if ( (fieldFlags & 0x3F8000) != 0 && ((fieldFlags & 0x3F8000) != 0x8000 || (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) != 0) )
    {
      if ( (*(_BYTE *)(fieldDescriptor + 8) & 1) != 0 )
        comparisonSymbol = g_ClipsSymbolNeq;
      else
        comparisonSymbol = g_ClipsSymbolEq;
      testNode = AST_NewNode(10, comparisonSymbol);
      savedFieldType = *v17;
      *v17 = 15;
      *(_DWORD *)(testNode + 6) = PP_MakeLowTierConst((int)v17, savedFieldType, (int)v17);
      *v20 = v19;
      *(_DWORD *)(*(_DWORD *)(testNode + 6) + 10) = AST_NewNode(*v20, v20[1]);
      return testNode;
    }
    else
    {
      Mem_AllocArray(bitmapData, 4);
      if ( (*(_BYTE *)(v2 + 8) & 1) != 0 )
        LOBYTE(bitmapData[0]) &= ~1u;
      else
        LOBYTE(bitmapData[0]) |= 1u;
      bitmapData[0] = ((unsigned __int8)(*(_DWORD *)(v2 + 40) - 1) << 10) | bitmapData[0] & 0xFFFC03FF;
      if ( (*(_DWORD *)(v2 + 8) & 0x3F8000) != 0 )
      {
        LOBYTE(bitmapData[0]) &= ~2u;
        v14 = *(_DWORD *)(v2 + 12) << 18 >> 25;
        LOWORD(bitmapData[0]) &= 0xFC03u;
        v4 = 4 * (unsigned __int8)v14;
      }
      else
      {
        LOBYTE(bitmapData[0]) |= 2u;
        v3 = *(_DWORD *)(v2 + 12) & 0x7F;
        LOWORD(bitmapData[0]) &= 0xFC03u;
        v4 = 4 * v3;
      }
      bitmapData[0] |= v4;
      bitmapValue = Rules_AddBitmapValue(bitmapData, 4);
      constraintNode = AST_NewNode(33, bitmapValue);
      *(_DWORD *)(constraintNode + 6) = AST_NewNode(*v7, v7[1]);
      return constraintNode;
    }
  }
  else
  {
    Mem_AllocArray(&bitmapWord, 4);
    if ( (*(_BYTE *)(v9 + 8) & 1) != 0 )
      LOBYTE(bitmapWord) = bitmapWord & 0xFE;
    else
      LOBYTE(bitmapWord) = bitmapWord | 1;
    v10 = *(_DWORD *)(v9 + 40) - 1;
    LOWORD(bitmapWord) = bitmapWord & 0xFE01;
    bitmapWord |= 2 * v10;
    indexBitmapValue = Rules_AddBitmapValue(&bitmapWord, 4);
    indexConstraintNode = AST_NewNode(32, indexBitmapValue);
    *(_DWORD *)(indexConstraintNode + 6) = AST_NewNode(*v13, v13[1]);
    return indexConstraintNode;
  }
}
// 4B6EFB: variable 'v2' is possibly undefined
// 4B6F7E: variable 'v7' is possibly undefined
// 4B6FA0: variable 'v9' is possibly undefined
// 4B6FE7: variable 'v13' is possibly undefined
// 4B705E: variable 'v17' is possibly undefined
// 4B706E: variable 'v19' is possibly undefined
// 4B706E: variable 'v20' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E668: using guessed type int dword_54E668;

//----- (004B70A0) --------------------------------------------------------
signed int  PP_MakeLowTierConst(int fieldDescriptor, int a2, int a3)
{
  int v3; // esi
  int Const28; // edx
  __int16 v5; // ax
  int Const26; // eax

  if ( *(int *)(fieldDescriptor + 40) > 0 && (*(_BYTE *)(fieldDescriptor + 9) & 0x40) == 0 )
  {
    Const28 = PP_MakeConst27(a3, a2);
    v5 = 27;
    return AST_NewNode(v5, Const28);
  }
  if ( (*(_DWORD *)fieldDescriptor == 17 || *(_DWORD *)fieldDescriptor == 15)
    && ((v3 = *(_DWORD *)(fieldDescriptor + 8), (v3 & 0x3F8000) == 0)
     || (v3 & 0x3F8000) == 0x8000 && (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)fieldDescriptor == 18 || *(_DWORD *)fieldDescriptor == 16)
    && (*(_DWORD *)(fieldDescriptor + 8) & 0x3F8000) == 0
    && (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) == 0 )
  {
    Const28 = PP_MakeConst28();
    v5 = 28;
    return AST_NewNode(v5, Const28);
  }
  Const26 = PP_MakeConst26();
  return AST_NewNode(26, Const26);
}

//----- (004B7140) --------------------------------------------------------
signed int  PP_ParsePrimary(int fieldDescriptor, int a2, int a3)
{
  int v3; // ecx
  int v4; // esi
  int Const31; // edx
  __int16 v6; // ax
  int v8; // eax

  if ( *(int *)(fieldDescriptor + 40) > 0 && (*(_BYTE *)(fieldDescriptor + 9) & 0x40) == 0 )
  {
    Const31 = PP_MakeConst31(a3, a2);
    v6 = 30;
    return AST_NewNode(v6, Const31);
  }
  v3 = *(_DWORD *)fieldDescriptor;
  if ( (*(_DWORD *)fieldDescriptor == 17 || v3 == 15)
    && ((v4 = *(_DWORD *)(fieldDescriptor + 8), (v4 & 0x3F8000) == 0)
     || (a2 = v4 & 0x3F8000, (v4 & 0x3F8000) == 0x8000) && (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)fieldDescriptor == 18 || *(_DWORD *)fieldDescriptor == 16)
    && (*(_DWORD *)(fieldDescriptor + 8) & 0x3F8000) == 0
    && (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) == 0 )
  {
    Const31 = PP_MakeConst30(v3, a2);
    v6 = 31;
    return AST_NewNode(v6, Const31);
  }
  v8 = PP_BuildDefault();
  return AST_NewNode(29, v8);
}

//----- (004B71E0) --------------------------------------------------------
signed int  PP_ShouldEmit(int fieldDescriptor)
{
  int v1; // ecx
  int v2; // eax
  int v3; // eax
  unsigned int v5; // eax
  _DWORD bitmapData[4]; // [esp+0h] [ebp-10h] BYREF

  if ( (*(_WORD *)(fieldDescriptor + 12) & 0x3F80) == 0 && *(_DWORD *)fieldDescriptor != 15 && *(_DWORD *)fieldDescriptor != 17 )
    return 0;
  Mem_AllocArray(bitmapData, 4);
  bitmapData[0] = ((unsigned __int8)(*(_DWORD *)(v1 + 40) - 1) << 9) | bitmapData[0] & 0xFFFE01FF;
  if ( *(_DWORD *)v1 == 16 || *(_DWORD *)v1 == 18 || (*(_WORD *)(v1 + 10) & 0x1FC0) != 0 )
    BYTE1(bitmapData[0]) &= ~1u;
  else
    BYTE1(bitmapData[0]) |= 1u;
  if ( *(_DWORD *)v1 == 15 || *(_DWORD *)v1 == 17 )
  {
    v2 = *(_DWORD *)(v1 + 12) << 18 >> 25;
    LOBYTE(bitmapData[0]) = 0;
    bitmapData[0] |= (unsigned __int8)(v2 + 1);
  }
  else
  {
    v5 = *(_DWORD *)(v1 + 12) << 18;
    LOBYTE(bitmapData[0]) = 0;
    bitmapData[0] |= v5 >> 25;
  }
  v3 = Rules_AddBitmapValue(bitmapData, 4);
  return AST_NewNode(25, v3);
}
// 4B7210: variable 'v1' is possibly undefined

//----- (004B72D0) --------------------------------------------------------
signed int __fastcall PP_MakeConst25(int a1, int a2)
{
  char v2; // cl
  int v3; // eax
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a1;
  Mem_AllocArray(v5, 4);
  v5[0] = ((unsigned __int8)(v2 - 1) << 9) | v5[0] & 0xFFFE01FF;
  LOBYTE(v5[0]) = 0;
  BYTE1(v5[0]) |= 1u;
  v3 = Rules_AddBitmapValue(v5, 4);
  return AST_NewNode(25, v3);
}
// 4B72E8: variable 'v2' is possibly undefined

//----- (004B7330) --------------------------------------------------------
int  PP_PatchHighTierConst(_WORD *astNode, int fieldDescriptor)
{
  int v3; // eax
  int v4; // edi
  int result; // eax
  int v6; // ecx
  int v7; // ecx

  v3 = fieldDescriptor;
  if ( *(int *)(fieldDescriptor + 40) > 0 && (*(_BYTE *)(fieldDescriptor + 9) & 0x40) == 0 )
  {
    *astNode = 30;
    result = PP_MakeConst31((int)astNode, fieldDescriptor);
    goto LABEL_11;
  }
  if ( (*(_DWORD *)fieldDescriptor == 17 || *(_DWORD *)fieldDescriptor == 15)
    && ((v4 = *(_DWORD *)(fieldDescriptor + 8), (v4 & 0x3F8000) == 0)
     || (fieldDescriptor = v4 & 0x3F8000, (v4 & 0x3F8000) == 0x8000) && (*(_WORD *)(v3 + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)v3 == 18 || *(_DWORD *)v3 == 16)
    && (*(_DWORD *)(v3 + 8) & 0x3F8000) == 0
    && (*(_WORD *)(v3 + 10) & 0x1FC0) == 0 )
  {
    *astNode = 31;
    result = PP_MakeConst30((int)astNode, fieldDescriptor);
LABEL_11:
    *(_DWORD *)(v6 + 2) = result;
    return result;
  }
  *astNode = 29;
  result = PP_BuildDefault();
  *(_DWORD *)(v7 + 2) = result;
  return result;
}
// 4B7390: variable 'v6' is possibly undefined
// 4B73BA: variable 'v7' is possibly undefined

//----- (004B73D0) --------------------------------------------------------
int  PP_PatchLowTierConst(_WORD *astNode, int fieldDescriptor)
{
  int v4; // edx
  int v5; // esi
  int result; // eax
  int v7; // ecx
  int v8; // ecx

  if ( (*(_BYTE *)(fieldDescriptor + 9) & 0x40) == 0 )
  {
    *astNode = 27;
    result = PP_MakeConst27((int)astNode, fieldDescriptor);
    goto LABEL_10;
  }
  v4 = *(_DWORD *)fieldDescriptor;
  if ( (*(_DWORD *)fieldDescriptor == 17 || v4 == 15)
    && ((v5 = *(_DWORD *)(fieldDescriptor + 8), (v5 & 0x3F8000) == 0)
     || (v5 & 0x3F8000) == 0x8000 && (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) == 0)
    || (*(_DWORD *)fieldDescriptor == 18 || *(_DWORD *)fieldDescriptor == 16)
    && (*(_DWORD *)(fieldDescriptor + 8) & 0x3F8000) == 0
    && (*(_WORD *)(fieldDescriptor + 10) & 0x1FC0) == 0 )
  {
    *astNode = 28;
    result = PP_MakeConst28();
LABEL_10:
    *(_DWORD *)(v7 + 2) = result;
    return result;
  }
  *astNode = 26;
  result = PP_MakeConst26();
  *(_DWORD *)(v8 + 2) = result;
  return result;
}
// 4B7429: variable 'v7' is possibly undefined
// 4B7452: variable 'v8' is possibly undefined

//----- (004B7460) --------------------------------------------------------
int PP_BuildDefault(void)
{
  _DWORD *v0; // ecx
  int v1; // eax
  unsigned __int8 v2; // al
  int v3; // eax
  _DWORD v5[6]; // [esp+0h] [ebp-18h] BYREF

  Mem_AllocArray(v5, 4);
  if ( (int)v0[10] <= 0 )
  {
    LOBYTE(v5[0]) |= 1u;
    v5[0] &= 0xFC0003FD;
  }
  else
  {
    v1 = v5[0];
    LOBYTE(v1) = v5[0] & 0xFC;
    if ( (int)v0[8] <= 0 )
    {
      LOBYTE(v1) = v1 | 2;
      v5[0] = v1;
      v5[0] = ((unsigned __int8)(v0[10] - 1) << 10) | v1 & 0xFFFC03FF;
      HIWORD(v5[0]) &= 0xFC03u;
    }
    else
    {
      v5[0] = v1;
      v5[0] = ((unsigned __int8)(v0[10] - 1) << 10) | v1 & 0xFFFC03FF;
      v2 = v0[8] - 1;
      HIWORD(v5[0]) &= 0xFC03u;
      v5[0] |= v2 << 18;
    }
  }
  v3 = v0[7];
  LOWORD(v5[0]) &= 0xFC03u;
  v5[0] |= 4 * (unsigned __int8)(v3 - 1);
  return Rules_AddBitmapValue(v5, 4);
}
// 4B7476: variable 'v0' is possibly undefined

//----- (004B7550) --------------------------------------------------------
int __fastcall PP_MakeConst31(int a1, int a2)
{
  int v2; // ecx
  unsigned __int8 v3; // al
  int v4; // eax
  _DWORD v6[3]; // [esp+0h] [ebp-Ch] BYREF

  v6[2] = a1;
  Mem_AllocArray(v6, 4);
  v3 = *(_DWORD *)(v2 + 40) - 1;
  BYTE1(v6[0]) = 0;
  v6[0] |= v3 << 8;
  v4 = *(_DWORD *)(v2 + 28);
  LOBYTE(v6[0]) = 0;
  v6[0] |= (unsigned __int8)(v4 - 1);
  return Rules_AddBitmapValue(v6, 4);
}
// 4B7563: variable 'v2' is possibly undefined

//----- (004B75B0) --------------------------------------------------------
int __fastcall PP_MakeConst30(int a1, int a2)
{
  _DWORD *node; // ecx
  unsigned __int8 v3; // al
  unsigned __int8 v4; // al
  int v5; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  _DWORD bitmapData[5]; // [esp+0h] [ebp-14h] BYREF

  bitmapData[3] = a1;
  Mem_AllocArray(bitmapData, 4);
  v3 = node[10] - 1;
  HIBYTE(bitmapData[0]) = 0;
  bitmapData[0] |= v3 << 24;
  v4 = node[7] - 1;
  BYTE2(bitmapData[0]) = 0;
  bitmapData[0] |= v4 << 16;
  if ( *node == 17 || *node == 15 )
  {
    if ( (node[2] & 0x3F8000) != 0 )
    {
      LOBYTE(bitmapData[0]) |= 2u;
      LOWORD(bitmapData[0]) &= 0xFE02u;
      v9 = node[3] << 18 >> 25;
      BYTE1(bitmapData[0]) &= 1u;
      bitmapData[0] |= (v9 & 0x7F) << 9;
    }
    else
    {
      LOBYTE(bitmapData[0]) = bitmapData[0] & 0xFC | 1;
      v5 = node[3];
      LOWORD(bitmapData[0]) &= 0xFE03u;
      bitmapData[0] |= 4 * (v5 & 0x7F);
      BYTE1(bitmapData[0]) &= 1u;
    }
    return Rules_AddBitmapValue(bitmapData, 4);
  }
  else
  {
    LOBYTE(bitmapData[0]) |= 3u;
    v7 = node[3] & 0x7F;
    LOWORD(bitmapData[0]) &= 0xFE03u;
    bitmapData[0] |= 4 * v7;
    v8 = node[3] << 18 >> 25;
    BYTE1(bitmapData[0]) &= 1u;
    bitmapData[0] |= (v8 & 0x7F) << 9;
    return Rules_AddBitmapValue(bitmapData, 4);
  }
}
// 4B75C5: variable 'v2' is possibly undefined
