/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
#include "../recovered_test_seams.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_TEST_VISIBLE DWORD Compat_FileTimeToUnixSeconds (DWORD low_part, DWORD high_part);

//----- (0048773C) --------------------------------------------------------
unsigned __int16 * CRT_ConvertPrintfArgument(unsigned __int8 *outputBuffer, int *argList, int formatCtx)
{
  int ctx; // ecx
  unsigned __int16 *result_text; // edi
  unsigned __int8 format_char; // al
  bool v7; // zf
  int v8; // ebx
  int v9; // ebp
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // ebp
  int v14; // eax
  int v15; // ebx
  int v16; // ebp
  int v17; // eax
  int v18; // ebx
  int v19; // eax
  char v20; // al
  int v21; // eax
  int v22; // eax
  unsigned __int8 conversion_char; // al
  bool v24; // zf
  int v25; // ebx
  int v26; // eax
  int v27; // ecx
  int v28; // ecx
  char v29; // al
  int v30; // ebp
  int v31; // esi
  unsigned __int16 *string_arg; // eax
  int v33; // ebx
  int string_length; // eax
  int v35; // ecx
  int v36; // edx
  int v37; // eax
  int v38; // eax
  int v39; // eax
  int formattedLength; // eax
  int v41; // ecx
  int v42; // edx
  int v43; // eax
  int v44; // eax
  signed int pointer_value; // ebp
  int v46; // eax
  char *v47; // edx
  signed int v48; // eax
  int v49; // ecx
  int converted_length; // eax
  int v51; // ecx
  char format_flags; // bl
  int wideCharArgCursor; // ebx
  int v54; // ecx
  int mbcsCodePageActive; // ebp
  int charArgCursor; // eax
  int arg_ptr; // ebp
  int valueLow; // [esp+0h] [ebp-20h]
  __int64 value64; // [esp+4h] [ebp-1Ch]
  unsigned __int8 mbLeadByte; // [esp+Ch] [ebp-14h]
  unsigned __int8 mbTrailByte; // [esp+Dh] [ebp-13h]

  ctx = formatCtx;
  __ES__ = __DS__;
  *(_DWORD *)(uintptr_t)(formatCtx + 32) = 0;
  *(_DWORD *)(uintptr_t)(formatCtx + 36) = 0;
  *(_DWORD *)(uintptr_t)(formatCtx + 40) = 0;
  *(_DWORD *)(uintptr_t)(formatCtx + 44) = 0;
  *(_DWORD *)(uintptr_t)(formatCtx + 48) = 0;
  result_text = (unsigned __int16 *)outputBuffer;
  format_char = *(_BYTE *)(uintptr_t)(formatCtx + 21);
  *(_DWORD *)(uintptr_t)(formatCtx + 52) = 0;
  if ( format_char < 0x69u )
  {
    if ( format_char < 0x58u )
      goto LABEL_42;
    if ( format_char <= 0x58u )
      goto LABEL_13;
    if ( format_char != 100 )
      goto LABEL_42;
  }
  else if ( format_char > 0x69u )
  {
    if ( format_char < 0x75u )
    {
      v7 = format_char == 111;
LABEL_6:
      if ( !v7 )
        goto LABEL_42;
      goto LABEL_13;
    }
    if ( format_char > 0x75u )
    {
      v7 = format_char == 120;
      goto LABEL_6;
    }
LABEL_13:
    if ( (*(_BYTE *)(uintptr_t)(formatCtx + 31) & 1) == 0 )
    {
      if ( (*(_BYTE *)(uintptr_t)(formatCtx + 30) & 0x20) != 0 )
      {
        v11 = *argList + 4;
        *argList = v11;
        v12 = *(_DWORD *)(uintptr_t)(v11 - 4);
      }
      else
      {
        v13 = *argList + 4;
        *argList = v13;
        HIDWORD(value64) = *(_DWORD *)(uintptr_t)(v13 - 4);
        if ( (*(_BYTE *)(uintptr_t)(formatCtx + 30) & 0x10) == 0 )
          goto LABEL_42;
        v12 = WORD2(value64);
      }
      HIDWORD(value64) = v12;
      goto LABEL_42;
    }
    v8 = *argList + 4;
    *argList = v8;
    valueLow = *(_DWORD *)(uintptr_t)(v8 - 4);
    v9 = *argList + 4;
    *argList = v9;
    v10 = *(_DWORD *)(uintptr_t)(v9 - 4);
    goto LABEL_15;
  }
  if ( (*(_BYTE *)(uintptr_t)(formatCtx + 31) & 1) == 0 )
  {
    if ( (*(_BYTE *)(uintptr_t)(formatCtx + 30) & 0x20) != 0 )
    {
      v16 = *argList + 4;
      *argList = v16;
      v17 = *(_DWORD *)(uintptr_t)(v16 - 4);
    }
    else
    {
      v18 = *argList + 4;
      *argList = v18;
      HIDWORD(value64) = *(_DWORD *)(uintptr_t)(v18 - 4);
      if ( (*(_BYTE *)(uintptr_t)(ctx + 30) & 0x10) == 0 )
        goto LABEL_28;
      v17 = *(int *)((char *)&value64 + 2) >> 16;
    }
    HIDWORD(value64) = v17;
    goto LABEL_28;
  }
  v14 = *argList + 4;
  *argList = v14;
  valueLow = *(_DWORD *)(uintptr_t)(v14 - 4);
  v15 = *argList + 4;
  *argList = v15;
  LODWORD(value64) = *(_DWORD *)(uintptr_t)(v15 - 4);
LABEL_28:
  if ( (*(_BYTE *)(uintptr_t)(ctx + 31) & 1) != 0 )
  {
    if ( (value64 & 0x80000000LL) != 0 )
      goto LABEL_33;
  }
  else if ( value64 < 0 )
  {
LABEL_33:
    v19 = *(_DWORD *)(uintptr_t)(ctx + 32);
    *(_DWORD *)(uintptr_t)(ctx + 32) = v19 + 1;
    outputBuffer[v19] = 45;
    if ( (*(_BYTE *)(uintptr_t)(ctx + 31) & 1) == 0 )
    {
      HIDWORD(value64) = -HIDWORD(value64);
      goto LABEL_42;
    }
    valueLow = -valueLow;
    if ( valueLow )
      v10 = ~(_DWORD)value64;
    else
      v10 = -(int)value64;
LABEL_15:
    LODWORD(value64) = v10;
    goto LABEL_42;
  }
  v20 = *(_BYTE *)(uintptr_t)(ctx + 30);
  if ( (v20 & 4) != 0 )
  {
    v21 = *(_DWORD *)(uintptr_t)(ctx + 32);
    *(_DWORD *)(uintptr_t)(ctx + 32) = v21 + 1;
    outputBuffer[v21] = 43;
  }
  else if ( (v20 & 2) != 0 )
  {
    v22 = *(_DWORD *)(uintptr_t)(ctx + 32);
    *(_DWORD *)(uintptr_t)(ctx + 32) = v22 + 1;
    outputBuffer[v22] = 32;
  }
LABEL_42:
  conversion_char = *(_BYTE *)(uintptr_t)(ctx + 21);
  if ( conversion_char >= 0x64u )
  {
    if ( conversion_char <= 0x64u )
      goto LABEL_104;
    if ( conversion_char >= 0x6Fu )
    {
      if ( conversion_char <= 0x6Fu )
        goto LABEL_101;
      if ( conversion_char >= 0x73u )
      {
        if ( conversion_char > 0x73u )
        {
          if ( conversion_char >= 0x75u )
          {
            if ( conversion_char <= 0x75u )
              goto LABEL_104;
            if ( conversion_char != 120 )
              goto LABEL_139;
LABEL_94:
            if ( (*(_BYTE *)(uintptr_t)(ctx + 30) & 1) != 0 )
            {
              if ( (*(_BYTE *)(uintptr_t)(ctx + 31) & 1) != 0 )
              {
                if ( valueLow || (_DWORD)value64 )
                  goto LABEL_100;
              }
              else if ( HIDWORD(value64) )
              {
LABEL_100:
                v37 = *(_DWORD *)(uintptr_t)(ctx + 32);
                *(_DWORD *)(uintptr_t)(ctx + 32) = v37 + 1;
                outputBuffer[v37] = 48;
                v38 = *(_DWORD *)(uintptr_t)(ctx + 32);
                *(_DWORD *)(uintptr_t)(ctx + 32) = v38 + 1;
                outputBuffer[v38] = *(_BYTE *)(uintptr_t)(ctx + 21);
              }
            }
LABEL_101:
            if ( *(_BYTE *)(uintptr_t)(ctx + 21) == 111 && (*(_BYTE *)(uintptr_t)(ctx + 30) & 1) != 0 )
            {
              v39 = *(_DWORD *)(uintptr_t)(ctx + 32);
              *(_DWORD *)(uintptr_t)(ctx + 32) = v39 + 1;
              outputBuffer[v39] = 48;
            }
            goto LABEL_104;
          }
LABEL_139:
          *(_DWORD *)(uintptr_t)(ctx + 4) = 0;
          *outputBuffer = *(_BYTE *)(uintptr_t)(ctx + 21);
          *(_DWORD *)(uintptr_t)(ctx + 32) = 1;
          return result_text;
        }
LABEL_77:
        *outputBuffer = 0;
        v29 = *(_BYTE *)(uintptr_t)(ctx + 30);
        if ( v29 >= 0 )
        {
          if ( (v29 & 0x40) != 0 )
          {
            v31 = *argList + 4;
            *argList = v31;
            string_arg = *(unsigned __int16 **)(uintptr_t)(v31 - 4);
            if ( !string_arg )
              goto LABEL_86;
          }
          else
          {
            v33 = *argList + 4;
            *argList = v33;
            string_arg = *(unsigned __int16 **)(uintptr_t)(v33 - 4);
            if ( !string_arg )
              goto LABEL_86;
          }
          result_text = string_arg;
          __ES__ = __DS__;
        }
        else
        {
          v30 = *argList + 8;
          *argList = v30;
          if ( *(_DWORD *)(uintptr_t)(v30 - 8) || *(_WORD *)(uintptr_t)(v30 - 4) )
          {
            __ES__ = *(_WORD *)(uintptr_t)(v30 - 4);
            result_text = *(unsigned __int16 **)(uintptr_t)(v30 - 8);
          }
        }
LABEL_86:
        if ( *(_BYTE *)(uintptr_t)(ctx + 21) == 83 )
        {
          if ( (*(_BYTE *)(uintptr_t)(ctx + 30) & 0x10) == 0 )
          {
LABEL_88:
            string_length = CRT_WideCharToMultiByteLenBounded(result_text, __ES__, *(_DWORD *)(uintptr_t)(ctx + 8));
LABEL_91:
            v36 = *(_DWORD *)(uintptr_t)(v35 + 8);
            *(_DWORD *)(uintptr_t)(v35 + 40) = string_length;
            if ( v36 >= 0 && string_length > v36 )
              *(_DWORD *)(uintptr_t)(v35 + 40) = v36;
            return result_text;
          }
        }
        else if ( (*(_BYTE *)(uintptr_t)(ctx + 30) & 0x20) != 0 )
        {
          goto LABEL_88;
        }
        string_length = CRT_FarStrLenBounded((int)(intptr_t)result_text, __ES__, *(_DWORD *)(uintptr_t)(ctx + 8));
        goto LABEL_91;
      }
      v24 = conversion_char == 112;
      goto LABEL_53;
    }
    if ( conversion_char >= 0x66u )
    {
      if ( conversion_char > 0x66u )
      {
        if ( conversion_char > 0x67u )
        {
          if ( conversion_char != 105 )
            goto LABEL_139;
LABEL_104:
          result_text = (unsigned __int16 *)&outputBuffer[*(_DWORD *)(uintptr_t)(ctx + 32)];
          if ( (*(_BYTE *)(uintptr_t)(ctx + 31) & 1) != 0 )
          {
            if ( !*(_DWORD *)(uintptr_t)(ctx + 8) && !valueLow && !(_DWORD)value64 )
            {
LABEL_108:
              outputBuffer[*(_DWORD *)(uintptr_t)(ctx + 32)] = 0;
              formattedLength = 0;
LABEL_116:
              *(_DWORD *)(uintptr_t)(ctx + 40) = formattedLength;
              v42 = formattedLength;
              v43 = *(_DWORD *)(uintptr_t)(ctx + 8);
              if ( v42 < v43 )
                *(_DWORD *)(uintptr_t)(ctx + 36) = v43 - v42;
              if ( *(_DWORD *)(uintptr_t)(ctx + 8) == -1 )
                CRT_ApplyZeroPadWidth(ctx);
              return result_text;
            }
            _clib_ulltoa_(ctx, &outputBuffer[*(_DWORD *)(uintptr_t)(ctx + 32)]);
            if ( *(_BYTE *)(uintptr_t)(v41 + 21) == 88 )
              goto LABEL_114;
          }
          else
          {
            if ( !*(_DWORD *)(uintptr_t)(ctx + 8) && !HIDWORD(value64) )
              goto LABEL_108;
            CRT_SignedLongToDecimalString(ctx, &outputBuffer[*(_DWORD *)(uintptr_t)(ctx + 32)]);
            if ( *(_BYTE *)(uintptr_t)(v41 + 21) == 88 )
LABEL_114:
              CRT_ToUpperInPlace(outputBuffer, v41);
          }
          formattedLength = CRT_FarStrLenBounded((int)(intptr_t)result_text, __DS__, -1);
          goto LABEL_116;
        }
        goto LABEL_76;
      }
LABEL_74:
      if ( (*(_BYTE *)(uintptr_t)(ctx + 30) & 0x10) != 0 )
      {
        v25 = *argList + 4;
        *argList = v25;
        CRT_FormatFixedDecimal((char *)outputBuffer, *(_DWORD *)(uintptr_t)(v25 - 4), ctx);
        v26 = CRT_FarStrLenBounded((int)(intptr_t)outputBuffer, __DS__, '\xFF');
        *(_DWORD *)(uintptr_t)(v27 + 40) = v26;
        return result_text;
      }
    }
LABEL_76:
    CRT_DispatchFloatFormat();
    CRT_ApplyZeroPadWidth(v28);
    return (unsigned __int16 *)(outputBuffer + 1);
  }
  if ( conversion_char < 0x47u )
  {
    if ( conversion_char < 0x45u )
    {
      if ( conversion_char != 67 )
        goto LABEL_139;
      arg_ptr = *argList + 4;
      *argList = arg_ptr;
      converted_length = wctomb_(ctx, *(unsigned __int16 *)(uintptr_t)(arg_ptr - 4));
      if ( converted_length == -1 )
      {
        *(_DWORD *)(uintptr_t)(v51 + 32) = 0;
        return result_text;
      }
      goto LABEL_130;
    }
    if ( conversion_char > 0x45u )
      goto LABEL_74;
    goto LABEL_76;
  }
  if ( conversion_char <= 0x47u )
    goto LABEL_76;
  if ( conversion_char < 0x53u )
  {
    v24 = conversion_char == 80;
LABEL_53:
    if ( !v24 )
      goto LABEL_139;
    if ( !*(_DWORD *)(uintptr_t)(ctx + 4) )
    {
      if ( *(char *)(uintptr_t)(ctx + 30) >= 0 )
        *(_DWORD *)(uintptr_t)(ctx + 4) = 8;
      else
        *(_DWORD *)(uintptr_t)(ctx + 4) = 13;
    }
    *(_BYTE *)(uintptr_t)(ctx + 30) &= 0xF9u;
    v44 = *argList + 4;
    *argList = v44;
    pointer_value = *(_DWORD *)(uintptr_t)(v44 - 4);
    if ( *(char *)(uintptr_t)(ctx + 30) >= 0 )
    {
      v47 = (char *)outputBuffer;
      v48 = *(_DWORD *)(uintptr_t)(v44 - 4);
    }
    else
    {
      v46 = v44 + 4;
      *argList = v46;
      CRT_FormatPaddedHexDigits((unsigned __int16)*(_DWORD *)(uintptr_t)(v46 - 4), (char *)outputBuffer, 4);
      v47 = (char *)(outputBuffer + 5);
      v48 = pointer_value;
      outputBuffer[4] = 58;
    }
    CRT_FormatPaddedHexDigits(v48, v47, 8);
    if ( *(_BYTE *)(uintptr_t)(v49 + 21) == 80 )
      CRT_ToUpperInPlace(outputBuffer, v49);
    converted_length = CRT_FarStrLenBounded((int)(intptr_t)outputBuffer, __DS__, -1);
LABEL_130:
    *(_DWORD *)(uintptr_t)(v51 + 32) = converted_length;
    return result_text;
  }
  if ( conversion_char <= 0x53u )
    goto LABEL_77;
  if ( conversion_char < 0x58u )
    goto LABEL_139;
  if ( conversion_char <= 0x58u )
    goto LABEL_94;
  if ( conversion_char != 99 )
    goto LABEL_139;
  format_flags = *(_BYTE *)(uintptr_t)(ctx + 30);
  *(_DWORD *)(uintptr_t)(ctx + 32) = 1;
  if ( (format_flags & 0x20) != 0 )
  {
    wideCharArgCursor = *argList + 4;
    *argList = wideCharArgCursor;
    if ( wctomb_(ctx, *(unsigned __int16 *)(uintptr_t)(wideCharArgCursor - 4)) != -1 )
    {
      mbcsCodePageActive = g_CRT_MbcsCodePageActive;
      *outputBuffer = mbLeadByte;
      if ( mbcsCodePageActive )
      {
        if ( (g_Clips_DbcsLeadByteTable[mbLeadByte] & 1) != 0 )
        {
          outputBuffer[1] = mbTrailByte;
          ++*(_DWORD *)(uintptr_t)(v54 + 32);
        }
      }
    }
  }
  else
  {
    charArgCursor = *argList + 4;
    *argList = charArgCursor;
    *outputBuffer = *(_BYTE *)(uintptr_t)(charArgCursor - 4);
  }
  return result_text;
}
// 487859: variable 'v60' is possibly undefined
// 4878A6: variable 'v59' is possibly undefined
// 4879CB: variable 'v27' is possibly undefined
// 4879DE: variable 'v28' is possibly undefined
// 487A6A: variable 'v35' is possibly undefined
// 487B25: variable 'v41' is possibly undefined
// 487B6A: variable 'v4' is possibly undefined
// 487BFA: variable 'v49' is possibly undefined
// 487C15: variable 'v51' is possibly undefined
// 487C58: variable 'v61' is possibly undefined
// 487C77: variable 'v62' is possibly undefined
// 487C7A: variable 'v54' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);
// 4B5946: using guessed type int __fastcall _clib_ulltoa_(_DWORD, _DWORD);
// 4B5A33: using guessed type int __fastcall sub_4B5A33(_DWORD, _DWORD);
// 54E718: using guessed type int dword_54E718;

//----- (00487CD8) --------------------------------------------------------
_BYTE * CRT_ToUpperInPlace(_BYTE *result, int a2)
{
  _BYTE *i; // edx
  _BYTE *v3; // edx

  for ( i = result; *i; i = v3 + 1 )
  {
    result = (_BYTE *)(uintptr_t)toupper_(a2);
    *v3 = (_BYTE)(intptr_t)result;
  }
  return result;
}
// 487CE4: variable 'a2' is possibly undefined
// 487CE9: variable 'v3' is possibly undefined
// 476271: using guessed type int __thiscall toupper_(_DWORD);

//----- (004880E1) --------------------------------------------------------
int Mem_NearMallocHookStub(void)
{
  return 0;
}

//----- (0048817D) --------------------------------------------------------
unsigned int  CRT_OpenFile(DWORD pmode, const CHAR *path, int openFlags)
{
  return CRT_OpenFileShared(pmode, path, openFlags, 0);
}

//----- (004881A1) --------------------------------------------------------
unsigned int  CRT_OpenFileShared(DWORD pmode, const CHAR *fileName, int openMode, int shareFlags)
{
  return CRT_CreateFileHandleFromPath(fileName, openMode, shareFlags, pmode);
}

//----- (004881C8) --------------------------------------------------------
unsigned int  CRT_CreateFileHandleFromPath(const CHAR *fileName, int openMode, int extraOpenFlags, DWORD retryDisposition)
{
  char v5; // dl
  int access_bits; // esi
  DWORD file_attributes; // ebx
  int *v9; // ecx
  unsigned int file_descriptor; // edi
  int v11; // ebp
  DWORD creation_disposition; // eax
  HANDLE FileA; // ecx
  void *v14; // ecx
  struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+0h] [ebp-2Ch] BYREF
  DWORD dwShareMode; // [esp+Ch] [ebp-20h] BYREF
  DWORD dwDesiredAccess; // [esp+10h] [ebp-1Ch] BYREF
  int v18; // [esp+14h] [ebp-18h] BYREF
  int v19; // [esp+18h] [ebp-14h]
  int v20; // [esp+1Ch] [ebp-10h]

  v20 = openMode;
  v19 = extraOpenFlags;
  if ( _NTAtMaxFiles_() )
    goto LABEL_2;
  access_bits = v5 & 7;
  CRT_MapAccessModeToCreateFileFlags(access_bits, &dwDesiredAccess, &v18);
  file_attributes = 128;
  CRT_MapOpenFlagsToCreationDisposition(access_bits | v19, &dwShareMode);
  SecurityAttributes.lpSecurityDescriptor = 0;
  SecurityAttributes.nLength = 12;
  SecurityAttributes.bInheritHandle = (v20 & 0x80u) == 0;
  if ( g_CRT_ConsoleOpenHook && !stricmp_(v9, aCon_0) )
  {
    _NTGetFakeHandle_(
      SecurityAttributes.nLength,
      SecurityAttributes.lpSecurityDescriptor,
      SecurityAttributes.bInheritHandle);
    file_descriptor = g_CRT_AddFileHandleHook();
    g_CRT_ConsoleOpenHook(0, file_descriptor, -1);
    goto LABEL_26;
  }
  if ( (v20 & 0x20) != 0 )
  {
    v11 = *v9 + 4;
    *v9 = v11;
    v18 = *(_DWORD *)(uintptr_t)(v11 - 4);
    *v9 = 0;
    v18 &= ~g_CRT_OpenModeStripMask;
    if ( (v18 & 0x100) != 0 && (v18 & 0x80u) == 0 )
      file_attributes = 1;
    if ( (v20 & 0x400) != 0 )
    {
      retryDisposition = 1;
      creation_disposition = 1;
      goto LABEL_18;
    }
    if ( (v20 & 0x40) != 0 )
    {
      retryDisposition = 2;
LABEL_14:
      creation_disposition = 5;
      goto LABEL_18;
    }
    retryDisposition = 4;
  }
  else if ( (v20 & 0x40) != 0 )
  {
    goto LABEL_14;
  }
  creation_disposition = 3;
LABEL_18:
  FileA = CreateFileA(fileName, dwDesiredAccess, dwShareMode, &SecurityAttributes, creation_disposition, file_attributes, 0);
  if ( FileA == (HANDLE)-1 )
  {
    if ( (v20 & 0x20) != 0 )
      FileA = CreateFileA(fileName, dwDesiredAccess, dwShareMode, 0, retryDisposition, file_attributes, 0);
    if ( FileA == (HANDLE)-1 )
      return _set_errno_nt_(SecurityAttributes.nLength);
  }
  file_descriptor = g_CRT_AddFileHandleHook();
  if ( file_descriptor >= g_CRT_MaxFileDescriptor )
  {
    CloseHandle(v14);
LABEL_2:
    _set_errno_(SecurityAttributes.nLength);
    return -1;
  }
  isatty_(v14, 0);
LABEL_26:
  _SetIOMode_(SecurityAttributes.nLength, SecurityAttributes.lpSecurityDescriptor, SecurityAttributes.bInheritHandle);
  return file_descriptor;
}
// 488386: simplified comparisons for 'esi.4': ==0 || !=1 became !=1
// 48837D: simplified comparisons for 'esi.4': ==2 || !=1 became !=1
// 4881FB: variable 'v5' is possibly undefined
// 48824F: variable 'v9' is possibly undefined
// 48835B: variable 'v14' is possibly undefined
// 484E2A: using guessed type int __fastcall stricmp_(_DWORD, _DWORD);
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);
// 48537A: using guessed type _DWORD j___NTAddFileHandle_();
// 488DC0: using guessed type int __cdecl _SetIOMode_(_DWORD, _DWORD, _DWORD);
// 4B4B00: using guessed type int _NTAtMaxFiles_(void);
// 4B4CEE: using guessed type int __cdecl _NTGetFakeHandle_(_DWORD, _DWORD, _DWORD);
// 4B5C24: using guessed type int __fastcall isatty_(_DWORD, _DWORD);
// 51A549: using guessed type int dword_51A549;
// 51A574: using guessed type _DWORD (*off_51A574)();
// 51A5BC: using guessed type int (__cdecl *dword_51A5BC)(_DWORD, _DWORD, _DWORD);
// 51A768: using guessed type int dword_51A768;
// 51AF64: using guessed type int dword_51AF64;

//----- (00488514) --------------------------------------------------------
DWORD Process_GetCurrentId(void)
{
  return GetCurrentProcessId();
}

//----- (00488BDC) --------------------------------------------------------
signed int  CRT_MkTime(_DWORD *brokenDownTime)
{
  int rawYear; // esi
  int month; // edi
  int year; // esi
  char *monthDayTable; // ecx
  int dayCount; // edi
  int i; // esi
  int utcSeconds; // esi
  int adjustedSeconds; // esi

  rawYear = brokenDownTime[5];
  month = brokenDownTime[4] % 12;
  if ( rawYear < -184844639 )
    return -1;
  year = brokenDownTime[4] / 12 + rawYear;
  while ( month < 0 )
  {
    --year;
    month += 12;
  }
  if ( year < 0 )
    return -1;
  if ( CRT_IsLeapYear(year + 1900) )
    monthDayTable = (char *)&g_CRT_LeapMonthDayTable + 2;
  dayCount = brokenDownTime[3]
     + (year + 299) / 400
     + ((year + 3 - (__CFSHL__((year + 3) >> 31, 2) + 4 * ((year + 3) >> 31))) >> 2)
     + 365 * year
     - (year + 99) / 100
     + *(__int16 *)&monthDayTable[2 * month]
     - 1;
  for ( i = 60 * (60 * brokenDownTime[2] + brokenDownTime[1]) + *brokenDownTime; i < 0; i += 86400 )
    --dayCount;
  _brktime_(brokenDownTime, i);
  CRT_TzSet();
  utcSeconds = g_CRT_TimezoneSeconds + i;
  if ( (int)brokenDownTime[8] < 0 )
    CRT_IsDaylightTime(brokenDownTime);
  if ( (int)brokenDownTime[8] > 0 )
    utcSeconds -= g_CRT_DaylightBiasSeconds;
  while ( utcSeconds < 0 )
  {
    --dayCount;
    utcSeconds += 86400;
  }
  if ( dayCount < 25566 )
    return -1;
  if ( dayCount != 25566 )
    return 86400 * (dayCount - 25567) + utcSeconds;
  adjustedSeconds = utcSeconds - 86400;
  if ( g_CRT_TimezoneSeconds <= 0 || adjustedSeconds < 0 )
    return -1;
  return adjustedSeconds;
}
// 488C9B: variable 'v6' is possibly undefined
// 4B6243: using guessed type int __fastcall _brktime_(_DWORD, _DWORD);
// 5110EE: using guessed type int dword_5110EE;
// 511108: using guessed type int dword_511108;
// 51B0BA: using guessed type int dword_51B0BA;
// 51B0C2: using guessed type int dword_51B0C2;

//----- (00488DE1) --------------------------------------------------------
int  CRT_PutcCallbackForWrite(_DWORD *writeContext, int ch)
{
  int result; // eax

  result = CRT_PutcToStream(ch, *writeContext);
  ++writeContext[4];
  return result;
}
// 488A97: using guessed type int __fastcall sub_488A97(_DWORD, _DWORD);

//----- (00488DF2) --------------------------------------------------------
int  CRT_VfprintfLockedWrite(int stream, int format, int *argList)
{
  int lock_key;
  int stream_state;
  int busy_state;
  int saved_mode_bits;
  int flush_after_write;
  int write_result;
  unsigned char stream_flags;

  lock_key = *(_DWORD *)(uintptr_t)(stream + 16);
  g_CRT_FileHandleLockAcquireHook(lock_key);
  stream_state = *(_DWORD *)(uintptr_t)(stream + 8);
  busy_state = *(_DWORD *)(uintptr_t)(stream_state + 12);
  if ( busy_state != 1 )
  {
    if ( busy_state )
    {
      g_CRT_FileHandleLockReleaseHook(lock_key, 0);
      return 0;
    }
    *(_DWORD *)(uintptr_t)(stream_state + 12) = 1;
  }
  saved_mode_bits = *(_DWORD *)(uintptr_t)(stream + 12) & 0x30;
  *(_BYTE *)(uintptr_t)(stream + 12) &= 0xCFu;
  if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(stream + 8) + 8) )
    _ioalloc_();
  flush_after_write = 0;
  if ( (*(_BYTE *)(uintptr_t)(stream + 13) & 4) != 0 )
  {
    stream_flags = *(_BYTE *)(uintptr_t)(stream + 13) & 0xFA;
    *(_BYTE *)(uintptr_t)(stream + 13) = stream_flags;
    *(_BYTE *)(uintptr_t)(stream + 13) = stream_flags | 1;
    flush_after_write = 1;
  }
  write_result = CRT_PrintfFormatEngine(stream, (_BYTE *)(uintptr_t)(unsigned int)format, (void (*)(void))CRT_PutcCallbackForWrite, argList);
  if ( flush_after_write )
  {
    stream_flags = *(_BYTE *)(uintptr_t)(stream + 13) & 0xFA;
    *(_BYTE *)(uintptr_t)(stream + 13) = stream_flags;
    *(_BYTE *)(uintptr_t)(stream + 13) = stream_flags | 4;
    _flush_(stream, write_result);
  }
  if ( (*(_BYTE *)(uintptr_t)(stream + 12) & 0x20) != 0 )
    write_result = -1;
  *(_DWORD *)(uintptr_t)(stream + 12) |= saved_mode_bits;
  g_CRT_FileHandleLockReleaseHook(lock_key, write_result);
  return write_result;
}
// 4886DD: using guessed type int __fastcall _flush_(_DWORD, _DWORD);
// 488946: using guessed type int _ioalloc_(void);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

//----- (00488EB2) --------------------------------------------------------
DWORD  CRT_ReadFileHandle(int fileDescriptor, int buffer, DWORD length)
{
  void *v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // edx
  int v10; // ecx
  DWORD NumberOfBytesRead; // [esp+0h] [ebp-Ch] BYREF
  int v12 CLASH95_UNUSED; // [esp+8h] [ebp-4h]

  v12 = buffer;
  if ( fileDescriptor >= 0 && fileDescriptor <= (unsigned int)g_CRT_MaxFileDescriptor )
  {
    g_CRT_FileHandleLockAcquireHook(buffer);
    if ( g_CRT_CustomReadHook && g_CRT_CustomReadAvailablePredicateHook() )
    {
      v6 = g_CRT_CustomReadHook();
      g_CRT_FileHandleLockReleaseHook(v7, v6);
      return v8;
    }
    else if ( ReadFile(*(HANDLE *)(uintptr_t)(g_CRT_OsHandleTable + 4 * fileDescriptor), v5, length, &NumberOfBytesRead, 0) )
    {
      g_CRT_FileHandleLockReleaseHook(v10, v9);
      return NumberOfBytesRead;
    }
    else
    {
      g_CRT_FileHandleLockReleaseHook(v10, v9);
      return _set_errno_nt_(NumberOfBytesRead);
    }
  }
  else
  {
    _set_errno_(NumberOfBytesRead);
    return -1;
  }
}
// 488EFB: variable 'v7' is possibly undefined
// 488F01: variable 'v8' is possibly undefined
// 488F19: variable 'v5' is possibly undefined
// 488F26: variable 'v10' is possibly undefined
// 488F26: variable 'v9' is possibly undefined
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);
// 51A5B4: using guessed type int (*dword_51A5B4)(void);
// 51A5DC: using guessed type int (*dword_51A5DC)(void);
// 51A768: using guessed type int dword_51A768;
// 51AED0: using guessed type int dword_51AED0;

//----- (004890EC) --------------------------------------------------------
void CRT_InstallFloatPrintfSupport(void)
{
  g_FloatEfgFormatFn = EFG_Format_;
  g_StringToDoubleScanFn = (int (__fastcall *)(_DWORD, _DWORD))_cnvs2d_;
}
// 489119: using guessed type int _cnvs2d_();
// 4B681E: using guessed type int EFG_Format_();
// 51AF04: using guessed type int (*off_51AF04)();
// 51AF08: using guessed type int (__fastcall *off_51AF08)(_DWORD, _DWORD);

//----- (00489D18) --------------------------------------------------------
int  CRT_DeleteFile(const CHAR *path, int a2)
{
  if ( DeleteFileA(path) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (00489DAA) --------------------------------------------------------
signed int  CRT_FlushBufferAndPutChar(signed int result, int lockKey)
{
  signed int char_value; // ebx
  unsigned __int8 **stream; // edx
  unsigned __int8 *stream_state; // eax
  unsigned __int8 *v6; // ecx
  unsigned __int8 *v7; // ebp
  unsigned __int8 *v8; // edi
  unsigned __int8 *v9; // ebp

  char_value = result;
  if ( result != -1 )
  {
    g_CRT_FileHandleLockAcquireHook(lockKey);
    stream_state = stream[2];
    v6 = (unsigned __int8 *)(uintptr_t)*((_DWORD *)stream_state + 3);
    if ( v6 != (unsigned __int8 *)1 )
    {
      if ( v6 )
      {
LABEL_4:
        g_CRT_FileHandleLockReleaseHook(v6, stream);
        return -1;
      }
      *((_DWORD *)stream_state + 3) = 1;
    }
    if ( (*((_BYTE *)stream + 13) & 0x10) != 0 || ((_BYTE)(intptr_t)stream[3] & 1) == 0 )
      goto LABEL_4;
    if ( !*((_DWORD *)stream[2] + 2) )
      _ioalloc_();
    v7 = stream[1];
    if ( v7 )
    {
      v6 = *stream;
      if ( *stream == *((unsigned __int8 **)stream[2] + 2) )
        goto LABEL_4;
      v8 = v7 + 1;
      v9 = *stream;
      stream[1] = v8;
      *stream = --v9;
      if ( *v9 == char_value )
        goto LABEL_15;
    }
    else
    {
      stream[1] = (unsigned __int8 *)1;
      v6 = stream[5];
      *stream = &v6[*((_DWORD *)stream[2] + 2) - 1];
    }
    *((_BYTE *)stream + 12) |= 4u;
LABEL_15:
    **stream = char_value;
    *((_BYTE *)stream + 12) &= ~0x10u;
    g_CRT_FileHandleLockReleaseHook(v6, stream);
    return (unsigned __int8)char_value;
  }
  return result;
}
// 489DC2: variable 'v4' is possibly undefined
// 488946: using guessed type int _ioalloc_(void);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

CLASH95_TEST_VISIBLE DWORD Compat_FileTimeToUnixSeconds(DWORD low_part, DWORD high_part)
{
  unsigned long long filetime_ticks;

  filetime_ticks = ((unsigned long long)high_part << 32) | low_part;
  if ( filetime_ticks < 116444736000000000ULL )
    return 0;
  return (DWORD)((filetime_ticks - 116444736000000000ULL) / 10000000ULL);
}

//----- (00489E64) --------------------------------------------------------
signed int  CRT_FindFirstFile(const CHAR *pathPattern, _DWORD *findBuffer, int attributes)
{
  HANDLE find_handle; // eax
  WIN32_FIND_DATAA find_data; // [esp+0h] [ebp-140h] BYREF

  (void)attributes;
  find_handle = FindFirstFileA(pathPattern, &find_data);
  if ( find_handle == (HANDLE)-1 )
    return _set_errno_nt_(0);
  CRT_FillFindDataRecord((int)(intptr_t)&find_data, findBuffer);
  return (signed int)(intptr_t)find_handle;
}

//----- (00489EC6) --------------------------------------------------------
char  CRT_FillFindDataRecord(int winFindData, _DWORD *findBuffer)
{
  WIN32_FIND_DATAA *find_data; // esi

  find_data = (WIN32_FIND_DATAA *)(uintptr_t)(unsigned int)winFindData;
  if ( !find_data || !findBuffer )
    return 0;
  *findBuffer = 0;
  if ( (find_data->dwFileAttributes & 0x20) != 0 )
    *(_BYTE *)findBuffer |= 0x20u;
  if ( (find_data->dwFileAttributes & 0x10) != 0 )
    *(_BYTE *)findBuffer |= 0x10u;
  if ( (find_data->dwFileAttributes & 2) != 0 )
    *(_BYTE *)findBuffer |= 2u;
  if ( (find_data->dwFileAttributes & 1) != 0 )
    *(_BYTE *)findBuffer |= 1u;
  if ( (find_data->dwFileAttributes & 4) != 0 )
    *(_BYTE *)findBuffer |= 4u;
  findBuffer[1] = Compat_FileTimeToUnixSeconds(find_data->ftCreationTimeLow, find_data->ftCreationTimeHigh);
  findBuffer[2] = Compat_FileTimeToUnixSeconds(find_data->ftLastAccessTimeLow, find_data->ftLastAccessTimeHigh);
  findBuffer[3] = Compat_FileTimeToUnixSeconds(find_data->ftLastWriteTimeLow, find_data->ftLastWriteTimeHigh);
  findBuffer[4] = find_data->nFileSizeLow;
  qmemcpy((char *)(findBuffer + 5), find_data->cFileName, sizeof(find_data->cFileName));
  return 0;
}

//----- (00489FBA) --------------------------------------------------------
int  CRT_MakeDirectory(const CHAR *path, int a2)
{
  if ( CreateDirectoryA(path, 0) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (00489FD7) --------------------------------------------------------
int  CRT_RemoveDirectory(const CHAR *path, int a2)
{
  if ( RemoveDirectoryA(path) )
    return 0;
  else
    return _set_errno_nt_(a2);
}
// 485357: using guessed type int __cdecl _set_errno_nt_(_DWORD);

//----- (0048A080) --------------------------------------------------------
_DWORD * IO_StreambufAlloc(int a1, char a2, DWORD a3)
{
  _DWORD *result; // eax

  result = (_DWORD *)(uintptr_t)Mem_Alloc(4, a1, a2, a3);
  if ( result )
    *result = g_IOStreambuf_VTable;
  return result;
}
// 511054: using guessed type int (*off_511054[4])();

//----- (0048A0A0) --------------------------------------------------------
int Rules_Builtin_0(void)
{
  return 0;
}

//----- (0048A0C0) --------------------------------------------------------
void *Rules_Builtin_1(void)
{
  return &g_Rules_BuiltinSentinelAddress;
}

//----- (0048A0D0) --------------------------------------------------------
int Rules_Builtin_2(void)
{
  return 0;
}

//----- (0048A0E0) --------------------------------------------------------
int Rules_Builtin_3(void)
{
  return 0;
}

//----- (0048A0F0) --------------------------------------------------------
int IO_StreambufStubZero(void)
{
  return 0;
}

//----- (0048A100) --------------------------------------------------------
_DWORD * IO_StreambufAllocDerived(int a1, char a2, DWORD a3)
{
  _DWORD *result; // eax

  result = (_DWORD *)(uintptr_t)Mem_Alloc(4, a1, a2, a3);
  if ( result )
    *result = g_FuncTable_511094;
  return result;
}
// 511094: using guessed type int (*g_FuncTable_511094[6])();

//----- (0048A120) --------------------------------------------------------
_DWORD * IO_StreambufInitVTable(_DWORD *result)
{
  *result = g_IOStreambuf_VTable;
  return result;
}
// 511054: using guessed type int (*off_511054[4])();

//----- (0048A170) --------------------------------------------------------
int Rules_Builtin_4(void)
{
  return 0;
}

//----- (0048A180) --------------------------------------------------------
int  Rules_ConstructHandleVectorDtor(int result, char dtorFlags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_RulesHandleVector_DtorArrayDescriptor);
    j_j__nfree_();
    return v3;
  }
  else if ( (dtorFlags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 48A1A9: variable 'v4' is possibly undefined
// 48A1A0: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0048A1B0) --------------------------------------------------------
_DWORD * Rules_ConstructRecordInitVTable(_DWORD *result)
{
  *result = g_FuncTable_511094;
  return result;
}
// 511094: using guessed type int (*g_FuncTable_511094[6])();

//----- (0048A1C0) --------------------------------------------------------
int  Rules_ConstructRecordVectorDtor(int result, char dtorFlags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_RulesRecordArrayDtorSlot);
    j_j__nfree_();
    return v3;
  }
  else if ( (dtorFlags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 48A1E9: variable 'v4' is possibly undefined
// 48A1E0: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0048A230) --------------------------------------------------------
signed int Rules_RegisterFactsConstruct(void)
{
  Rules_RegisterPatternConstraintEvaluators();
  return Rules_AddPatternParser(
           (int)(intptr_t)aFacts_2,
           0,
           (int)(intptr_t)CSyncObject_Unlock,
           (int)(intptr_t)g_Rules_FactPatternEntityRecord,
           (int)(intptr_t)Rules_ParseFactPatternRelation,
           0,
           (int)(intptr_t)Rules_ParseDeftemplateSlotList,
           (int)(intptr_t)Rules_FreeDeftemplateSlotList,
           0,
           (int)(intptr_t)PP_PatchHighTierConst,
           (int)(intptr_t)PP_ParsePrimary,
           (int)(intptr_t)Rules_BuildFieldRangeOrValueConstraintNode,
           (int)(intptr_t)Rules_BuildFieldIndexConstraintNode,
           (int)(intptr_t)PP_PatchLowTierConst,
           (int)(intptr_t)PP_MakeLowTierConst,
           (int)(intptr_t)Rules_BuildFieldRangeConstraintNode,
           0,
           0,
           (int)(intptr_t)Rules_PropagatePatternNodeResetFlag,
           (int)(intptr_t)Rules_RematchAllFactsAgainstPatternNetwork,
           (int)(intptr_t)Rules_CreateInitialFactPatternNode,
           (int)(intptr_t)Rules_FactPatternNetworkWriteNodeRefToCode);
}
// 4B6DD0: using guessed type int .fn_init(void);

//----- (0048A2A0) --------------------------------------------------------
_DWORD * Rules_ParseDeftemplateSlotList(int thePattern, _DWORD *theSlot)
{
  int parseTree; // eax
  _BYTE *deftemplateName; // ebx
  int prunedTree; // eax
  int nextNode; // ecx
  int fieldNode; // esi
  int i; // eax
  BOOL withinMultifield; // ebp
  int v11; // edx
  int precedingSlot; // [esp+0h] [ebp-28h] BYREF
  int count; // [esp+4h] [ebp-24h] BYREF
  _DWORD *lastSlot; // [esp+8h] [ebp-20h]
  int savedNode; // [esp+Ch] [ebp-1Ch]

  parseTree = *(_DWORD *)(uintptr_t)(thePattern + 64);
  deftemplateName = (_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(parseTree + 68) + 4) + 16);
  prunedTree = Rules_PruneDeftemplateParseTree(parseTree);
  *(_DWORD *)(uintptr_t)(thePattern + 64) = prunedTree;
  nextNode = *(_DWORD *)(uintptr_t)(prunedTree + 64);
  savedNode = 0;
  if ( nextNode )
  {
    *(_DWORD *)(uintptr_t)(thePattern + 64) = nextNode;
    savedNode = prunedTree;
    *(_DWORD *)(uintptr_t)(prunedTree + 64) = 0;
    AST_FreeNode(prunedTree);
  }
  else
  {
    AST_Free(*(_DWORD *)(uintptr_t)(prunedTree + 52));
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(thePattern + 64) + 52) = v11;
  }
  g_ClipsDeftemplateBeingParsedPtr = Rules_FindImportExportConstruct(aDeftemplate_5, &count, deftemplateName, 1, 0);
  lastSlot = 0;
  fieldNode = *(_DWORD *)(uintptr_t)(thePattern + 64);
  for ( i = *(_DWORD *)(uintptr_t)(g_ClipsDeftemplateBeingParsedPtr + 32); fieldNode; i = theSlot[7] )
  {
    if ( (*(_BYTE *)(uintptr_t)(fieldNode + 8) & 4) != 0 )
    {
      savedNode = fieldNode;
      fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 68);
    }
    withinMultifield = !*(_DWORD *)(uintptr_t)(fieldNode + 64) && savedNode;
    theSlot = (_DWORD *)(uintptr_t)Rules_FindDuplicateDeftemplateSlot(i, (int *)(uintptr_t)fieldNode, withinMultifield, &precedingSlot);
    if ( !theSlot )
      theSlot = Rules_CreateDeftemplateSlot((int *)(uintptr_t)fieldNode, precedingSlot, withinMultifield, (int)(intptr_t)lastSlot);
    if ( !*(_DWORD *)(uintptr_t)(fieldNode + 64) && savedNode )
    {
      fieldNode = savedNode;
      savedNode = 0;
    }
    fieldNode = *(_DWORD *)(uintptr_t)(fieldNode + 64);
    if ( !fieldNode )
      *((_BYTE *)theSlot + 12) |= 4u;
    lastSlot = theSlot;
  }
  return theSlot;
}
// 48A395: variable 'v11' is possibly undefined
// 54E514: using guessed type int dword_54E514;

//----- (0048A3B0) --------------------------------------------------------
int  Rules_FindDuplicateDeftemplateSlot(int slotList, int *fieldNode, int withinMultifield, int *precedingSlot)
{
  int curSlot; // esi
  int nodeType; // edx

  curSlot = slotList;
  *precedingSlot = 0;
  if ( !slotList )
    return 0;
  do
  {
    while ( 1 )
    {
      nodeType = *fieldNode;
      if ( *fieldNode == 17 || nodeType == 15 )
      {
        if ( (*(_BYTE *)(uintptr_t)(curSlot + 12) & 1) != 0
          && *(_DWORD *)(uintptr_t)(curSlot + 12) << 25 >> 31 == withinMultifield
          && (unsigned __int8)*(_DWORD *)(uintptr_t)(curSlot + 20) == fieldNode[8]
          && *(_DWORD *)(uintptr_t)(curSlot + 20) << 16 >> 24 == fieldNode[10] - 1
          && AST_NodeListsEqual((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(curSlot + 24), (__int16 *)(uintptr_t)fieldNode[13]) )
        {
          return curSlot;
        }
        goto LABEL_8;
      }
      if ( nodeType != 18 && nodeType != 16 )
        break;
      if ( (*(_BYTE *)(uintptr_t)(curSlot + 12) & 2) != 0
        && *(_DWORD *)(uintptr_t)(curSlot + 12) << 25 >> 31 == withinMultifield
        && *(_DWORD *)(uintptr_t)(curSlot + 20) << 8 >> 24 == (unsigned int)(fieldNode[3] << 18) >> 25
        && (unsigned __int8)*(_DWORD *)(uintptr_t)(curSlot + 20) == fieldNode[8]
        && *(_DWORD *)(uintptr_t)(curSlot + 20) << 16 >> 24 == fieldNode[10] - 1
        && AST_NodeListsEqual((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(curSlot + 24), (__int16 *)(uintptr_t)fieldNode[13]) )
      {
        return curSlot;
      }
LABEL_8:
      *precedingSlot = curSlot;
      curSlot = *(_DWORD *)(uintptr_t)(curSlot + 40);
      if ( !curSlot )
        return 0;
    }
    *precedingSlot = curSlot;
    curSlot = *(_DWORD *)(uintptr_t)(curSlot + 40);
  }
  while ( curSlot );
  return 0;
}
// 48A3D9: variable 'a3' is possibly undefined

//----- (0048A4A0) --------------------------------------------------------
int  Rules_PruneDeftemplateParseTree(int nodeList)
{
  int curNode; // ecx
  int listHead; // esi
  int prevNode; // ebx
  int nodeType; // edx
  signed int constExpr; // eax
  int v7; // ecx
  _DWORD *ShouldEmit; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // ecx
  int prunedChild; // eax

  curNode = nodeList;
  listHead = nodeList;
  prevNode = 0;
  if ( !nodeList )
    return listHead;
  do
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          while ( 1 )
          {
            while ( 1 )
            {
              while ( 1 )
              {
                nodeType = *(_DWORD *)(uintptr_t)curNode;
                if ( *(_DWORD *)(uintptr_t)curNode != 17 && nodeType != 15 )
                  break;
                if ( *(_DWORD *)(uintptr_t)(curNode + 52) )
                  break;
                if ( prevNode )
                  *(_DWORD *)(uintptr_t)(prevNode + 64) = *(_DWORD *)(uintptr_t)(curNode + 64);
                else
                  listHead = *(_DWORD *)(uintptr_t)(curNode + 64);
                *(_DWORD *)(uintptr_t)(curNode + 64) = 0;
                AST_FreeNode(curNode);
                if ( !prevNode )
                  goto LABEL_21;
                curNode = *(_DWORD *)(uintptr_t)(prevNode + 64);
                if ( !curNode )
                  return listHead;
              }
              if ( *(_DWORD *)(uintptr_t)curNode != 18 && *(_DWORD *)(uintptr_t)curNode != 16
                || (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) != 0
                || *(_DWORD *)(uintptr_t)(curNode + 52)
                || (*(_DWORD *)(uintptr_t)(curNode + 8) & 0x3F8000) != 0
                || (*(_WORD *)(uintptr_t)(curNode + 10) & 0x1FC0) != 0 )
              {
                break;
              }
              if ( prevNode )
                *(_DWORD *)(uintptr_t)(prevNode + 64) = *(_DWORD *)(uintptr_t)(curNode + 64);
              else
                listHead = *(_DWORD *)(uintptr_t)(curNode + 64);
              *(_DWORD *)(uintptr_t)(curNode + 64) = 0;
              AST_FreeNode(curNode);
              if ( !prevNode )
                goto LABEL_21;
              curNode = *(_DWORD *)(uintptr_t)(prevNode + 64);
              if ( !curNode )
                return listHead;
            }
            if ( *(_DWORD *)(uintptr_t)curNode != 18 && *(_DWORD *)(uintptr_t)curNode != 16
              || (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) != 0
              || !*(_DWORD *)(uintptr_t)(curNode + 52)
              || (*(_DWORD *)(uintptr_t)(curNode + 8) & 0x3F8000) != 0
              || (*(_WORD *)(uintptr_t)(curNode + 10) & 0x1FC0) != 0 )
            {
              break;
            }
            *(_DWORD *)(uintptr_t)curNode = 17;
            prevNode = curNode;
            curNode = *(_DWORD *)(uintptr_t)(curNode + 64);
            if ( !curNode )
              return listHead;
          }
          if ( *(_DWORD *)(uintptr_t)curNode != 18 || (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) == 0 || *(_DWORD *)(uintptr_t)(curNode + 68) )
            break;
          *(_DWORD *)(uintptr_t)curNode = 17;
          constExpr = PP_MakeConst25(curNode, nodeType);
          *(_DWORD *)(uintptr_t)(v7 + 52) = constExpr;
          *(_BYTE *)(uintptr_t)(v7 + 8) &= ~4u;
LABEL_41:
          prevNode = v7;
          curNode = *(_DWORD *)(uintptr_t)(v7 + 64);
          if ( !curNode )
            return listHead;
        }
        if ( *(_DWORD *)(uintptr_t)curNode == 18 && (*(_BYTE *)(uintptr_t)(curNode + 8) & 4) != 0 )
          break;
        prevNode = curNode;
        curNode = *(_DWORD *)(uintptr_t)(curNode + 64);
        if ( !curNode )
          return listHead;
      }
      ShouldEmit = (_DWORD *)(uintptr_t)PP_ShouldEmit(*(_DWORD *)(uintptr_t)(curNode + 68));
      v10 = AST_MergeFieldAccessNodes(ShouldEmit, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v9 + 68) + 52));
      *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v11 + 68) + 52) = v10;
      prunedChild = Rules_PruneDeftemplateParseTree(*(_DWORD *)(uintptr_t)(v11 + 68));
      *(_DWORD *)(uintptr_t)(v7 + 68) = prunedChild;
      if ( prunedChild )
        goto LABEL_41;
      if ( prevNode )
        *(_DWORD *)(uintptr_t)(prevNode + 64) = *(_DWORD *)(uintptr_t)(v7 + 64);
      else
        listHead = *(_DWORD *)(uintptr_t)(v7 + 64);
      *(_DWORD *)(uintptr_t)(v7 + 64) = 0;
      AST_FreeNode(v7);
      if ( prevNode )
        break;
LABEL_21:
      curNode = listHead;
      if ( !listHead )
        return 0;
    }
    curNode = *(_DWORD *)(uintptr_t)(prevNode + 64);
  }
  while ( curNode );
  return listHead;
}
// 48A5EF: variable 'v7' is possibly undefined
// 48A612: variable 'v9' is possibly undefined
// 48A61D: variable 'v11' is possibly undefined
