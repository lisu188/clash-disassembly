/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00469680) --------------------------------------------------------
int  AviPlayer_AllocDecodedBitmapInfo(int self, int headerBytes)
{
  int bitCount; // edx
  int compressionSel; // edx
  int compression; // ebp
  __int64 allocResult; // rax
  int decodedBmi; // edx
  int result; // eax
  int headerSize; // [esp+0h] [ebp-20h]
  int bytesPerPixel; // [esp+4h] [ebp-1Ch]

  bitCount = *(_DWORD *)(uintptr_t)(self + 2123);
  bytesPerPixel = (bitCount + 7) >> 3;
  if ( bitCount == 24 || bitCount == 8 )
    compressionSel = 0;
  else
    compressionSel = 3;
  compression = compressionSel;
  if ( compressionSel )
    headerBytes = **(_DWORD **)(uintptr_t)(self + 151);
  allocResult = j_Mem_Alloc(headerBytes);
  *(_DWORD *)(uintptr_t)(self + 2058) = allocResult;
  headerSize = HIDWORD(allocResult);
  if ( SHIDWORD(allocResult) > **(_DWORD **)(uintptr_t)(self + 151) )
    HIDWORD(allocResult) = **(_DWORD **)(uintptr_t)(self + 151);
  qmemcpy(*(void **)(uintptr_t)(self + 2058), *(const void **)(uintptr_t)(self + 151), HIDWORD(allocResult));
  **(_DWORD **)(uintptr_t)(self + 2058) = headerSize;
  *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 14) = *(_WORD *)(uintptr_t)(self + 2123);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 16) = compression;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 20) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 4)
                                           * abs32(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 8))
                                           * bytesPerPixel;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 32) = 0;
  decodedBmi = *(_DWORD *)(uintptr_t)(self + 2058);
  result = *(_DWORD *)(uintptr_t)(decodedBmi + 8);
  if ( result > 0 )
  {
    result = -result;
    *(_DWORD *)(uintptr_t)(decodedBmi + 8) = result;
  }
  if ( compression == 3 )
  {
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 40) = *(_DWORD *)(uintptr_t)(self + 2127);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 44) = *(_DWORD *)(uintptr_t)(self + 2131);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 2058) + 48) = *(_DWORD *)(uintptr_t)(self + 2135);
    result = *(_DWORD *)(uintptr_t)(self + 2058);
    *(_DWORD *)(uintptr_t)(result + 52) = *(_DWORD *)(uintptr_t)(self + 2139);
  }
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (004697E0) --------------------------------------------------------
// Deferred to compat/decomp_runtime_stubs.c until the late AVI init loop is reconstructed.

//----- (00469C90) --------------------------------------------------------
_DWORD * AviPlayer_CreatePaletteFromBitmap(int self, int ddInterface)
{
  _DWORD *result; // eax
  int i; // eax
  int v5; // ecx
  _BYTE v6[2] CLASH95_UNUSED; // [esp+0h] [ebp-5BEh]
  char paletteEntries[1024]; // [esp+2h] [ebp-5BCh] BYREF
  int (**v8)(); // [esp+466h] [ebp-158h]
  int (**v9)(); // [esp+4CEh] [ebp-F0h]
  _DWORD ehFrame[3]; // [esp+59Ah] [ebp-24h] BYREF
  int ehState CLASH95_UNUSED; // [esp+5A6h] [ebp-18h]

  result = ehFrame;
  ehFrame[0] = NtCurrentTeb()->NtTib.ExceptionList;
  ehFrame[1] = &j____wcpp_4_fs_handler_rtn_;
  ehFrame[2] = &g_AviPlayerCreatePalette_EHScopeTable;
  ehState = 0;
  if ( (*(_BYTE *)(uintptr_t)(self + 2120) & 2) != 0 )
  {
    for ( i = 0; i != 1024; v6[i + 1] = 0 )
    {
      paletteEntries[i] = *(_BYTE *)(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 151) + *(_DWORD *)(uintptr_t)(self + 151) + i + 2);
      paletteEntries[i + 1] = *(_BYTE *)(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 151) + *(_DWORD *)(uintptr_t)(self + 151) + i + 1);
      i += 4;
      v6[i] = *(_BYTE *)(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 151) + *(_DWORD *)(uintptr_t)(self + 151) + i - 4);
    }
    if ( (*(int (__stdcall **)(int, int, char *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)ddInterface + 20))(ddInterface, 4, paletteEntries, self + 1948, 0) )
    {
      ExcString_Ctor();
      ehState = v5;
      ExcString_Ctor();
      v9 = g_AviException_VTable;
      ehState = 0;
      return (_DWORD *)(uintptr_t)CRT_ThrowExcStringException();
    }
    else
    {
      result = (_DWORD *)(uintptr_t)(*(int (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 124))(
                           *(_DWORD *)(uintptr_t)(self + 1956),
                           *(_DWORD *)(uintptr_t)(self + 1948));
      if ( result )
      {
        if ( result != (_DWORD *)-2005532222
          || (result = (_DWORD *)(uintptr_t)(*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956))) == 0
          && (result = (_DWORD *)(uintptr_t)(*(int (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 124))(
                                   *(_DWORD *)(uintptr_t)(self + 1956),
                                   *(_DWORD *)(uintptr_t)(self + 1948))) != 0 )
        {
          ExcString_Ctor();
          ehState = 3;
          ExcString_Ctor();
          v8 = g_AviException_VTable;
          ehState = 0;
          return (_DWORD *)(uintptr_t)CRT_ThrowExcStringException();
        }
      }
    }
  }
  return result;
}
// 469DD3: variable 'v5' is possibly undefined
// 510374: using guessed type int (*off_510374[2])();

//----- (00469E60) --------------------------------------------------------
int __stdcall AviPlayer_SendICDrawBegin(
        int hic,
        int dwFlags,
        int a3,
        int a4,
        int xSrc,
        int ySrc,
        int dxSrc,
        int dySrc,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14)
{
  _DWORD drawBeginParams[13]; // [esp+0h] [ebp-34h] BYREF

  drawBeginParams[0] = dwFlags;
  drawBeginParams[1] = a3;
  drawBeginParams[2] = a4;
  drawBeginParams[9] = xSrc;
  drawBeginParams[10] = ySrc;
  drawBeginParams[11] = dxSrc;
  drawBeginParams[12] = dySrc;
  drawBeginParams[3] = a9;
  drawBeginParams[4] = a10;
  drawBeginParams[5] = a11;
  drawBeginParams[6] = a12;
  drawBeginParams[7] = a13;
  drawBeginParams[8] = a14;
  return ICSendMessage(hic, 16446, (DWORD)(intptr_t)drawBeginParams, 52, 0);
}
// 4E980A: using guessed type int __stdcall ICSendMessage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (00469EF0) --------------------------------------------------------
int AviException_CtorFromExceptionList(void)
{
  int result; // eax

  result = ExcString_CtorFromPtr((void *)NtCurrentTeb()->NtTib.ExceptionList);
  *(_DWORD *)(uintptr_t)(result + 100) = g_AviException_VTable;
  return result;
}
// 510374: using guessed type int (*off_510374[2])();

//----- (00469F50) --------------------------------------------------------
int AviException_CtorForSurfaceCreateFailure(void)
{
  int result; // eax

  result = ExcString_Ctor();
  *(_DWORD *)(uintptr_t)(result + 100) = g_AviException_VTable;
  return result;
}
// 510374: using guessed type int (*off_510374[2])();

//----- (00469FB0) --------------------------------------------------------
int AviException_CtorForDrawFailure(void)
{
  int result; // eax

  result = ExcString_Ctor();
  *(_DWORD *)(uintptr_t)(result + 100) = g_AviException_VTable;
  return result;
}
// 510374: using guessed type int (*off_510374[2])();

//----- (0046A010) --------------------------------------------------------
int  AviException_ScalarDeletingDtor(int self, char dtorFlags)
{
  int v3; // ecx
  int v5; // ecx

  v3 = self;
  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(self, &g_AviException_DtorArrayDescriptor);
    j_j__nfree_();
    return v5;
  }
  else
  {
    if ( (dtorFlags & 2) != 0 )
      j__nfree_();
    return v3;
  }
}
// 46A068: variable 'v3' is possibly undefined
// 46A091: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (0046A0A0) --------------------------------------------------------
int AviException_GetMessage(void)
{
  return ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))ExcString_AsCharPtr)(
           NtCurrentTeb()->NtTib.ExceptionList,
           &j____wcpp_4_fs_handler_rtn_,
           &g_AviExceptionMessage_EHFrame,
           1);
}
// 4842DE: using guessed type _DWORD ExcString_AsCharPtr();

//----- (0046A100) --------------------------------------------------------
BOOL  AviPlayer_PulseEventHandle(HANDLE *eventHandlePtr)
{
  return PulseEvent(*eventHandlePtr);
}

//----- (0046A110) --------------------------------------------------------
int  AviPlayer_LeaveBusySectionAndRelease(int guardPtr)
{
  _DWORD *counter; // ebx

  counter = *(_DWORD **)(uintptr_t)guardPtr;
  LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(*(_DWORD *)(uintptr_t)guardPtr + 4));
  --*counter;
  return guardPtr;
}

//----- (0046A130) --------------------------------------------------------
int  Mem_BitsToBytesCeil(int bitCount)
{
  return (bitCount + 7) >> 3;
}

//----- (0046A140) --------------------------------------------------------
int  AviPlayer_QueueBacklogCount(int queue)
{
  return *(_DWORD *)(uintptr_t)(queue + 8) - *(_DWORD *)(uintptr_t)(queue + 4);
}

//----- (0046A150) --------------------------------------------------------
int  AviPlayer_IncrementFramesRenderedCount(int result)
{
  ++*(_DWORD *)(uintptr_t)(result + 4);
  return result;
}

//----- (0046A160) --------------------------------------------------------
int  AviPlayer_AudioBytesQueued(int self)
{
  return *(_DWORD *)(uintptr_t)(self + 259);
}

//----- (0046A170) --------------------------------------------------------
int  AviPlayer_AudioSampleQueueCount(int queue)
{
  return *(_DWORD *)(uintptr_t)(queue + 8);
}

//----- (0046A180) --------------------------------------------------------
int  AviPlayer_AudioSampleQueueBase(int self)
{
  return self + 219;
}

//----- (0046A190) --------------------------------------------------------
int  AviPlayer_AudioFormatPtr(int self)
{
  return *(_DWORD *)(uintptr_t)(self + 363);
}

//----- (0046A1A0) --------------------------------------------------------
int  AviPlayer_BitmapWidth(int self)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4);
}

//----- (0046A1B0) --------------------------------------------------------
int  AviPlayer_BitmapHeightAbs(int self)
{
  __int64 biHeight; // rax

  biHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 8);
  return (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
}

//----- (0046A1D0) --------------------------------------------------------
int  AviPlayer_AudioBlockAlign(int self)
{
  return *(unsigned __int16 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 363) + 12);
}

//----- (0046A1E0) --------------------------------------------------------
int  AviPlayer_UpdateStreamRectAndSendICDrawBegin(int *codecPtr, int lockedBits, int destHeight, int destWidth, int pitchPixels, int frameData, int frameFlags)
{
  int inputFormat; // edx
  int biHeight; // esi
  int result; // eax
  int v11; // [esp+0h] [ebp-124h]
  _DWORD drawParams[16]; // [esp+CCh] [ebp-58h] BYREF
  int v13 CLASH95_UNUSED; // [esp+10Ch] [ebp-18h]
  int hic; // [esp+110h] [ebp-14h]
  int biWidth; // [esp+114h] [ebp-10h]

  drawParams[13] = NtCurrentTeb()->NtTib.ExceptionList;
  drawParams[14] = &j____wcpp_4_fs_handler_rtn_;
  v13 = 0;
  drawParams[15] = &g_AviStreamRectDrawBegin_EHFrame;
  codecPtr[3] = pitchPixels;
  codecPtr[7] = pitchPixels * destHeight * ((*((unsigned __int16 *)codecPtr + 11) + 7) >> 3);
  inputFormat = codecPtr[1];
  hic = *codecPtr;
  biWidth = *(_DWORD *)(uintptr_t)(inputFormat + 4);
  biHeight = *(_DWORD *)(uintptr_t)(inputFormat + 8);
  drawParams[0] = frameFlags;
  drawParams[1] = inputFormat;
  drawParams[12] = biHeight;
  drawParams[3] = codecPtr + 2;
  drawParams[4] = lockedBits;
  drawParams[8] = destHeight;
  drawParams[2] = frameData;
  drawParams[5] = 0;
  drawParams[6] = 0;
  drawParams[9] = 0;
  drawParams[10] = 0;
  drawParams[7] = destWidth;
  drawParams[11] = biWidth;
  result = ICSendMessage(hic, 16446, drawParams, 52, v11);
  if ( result < 0 )
  {
    ExcString_Ctor();
    v13 = 1;
    ExcString_Ctor();
    v13 = 0;
    return CRT_ThrowExcStringException();
  }
  return result;
}
// 46A2EB: variable 'v11' is possibly undefined
// 4E980A: using guessed type int __stdcall ICSendMessage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (0046A350) --------------------------------------------------------
int  AviPlayer_StreamBitmapInfoPtr(int codecState)
{
  return codecState + 8;
}

//----- (0046A360) --------------------------------------------------------
int __fastcall AviPlayer_SpanDelta(int a1 CLASH95_UNUSED, _DWORD *rect)
{
  return rect[2] - *rect;
}

//----- (0046A370) --------------------------------------------------------
bool  AviPlayer_IsUncompressedFormat(int self)
{
  return *(_BYTE *)(uintptr_t)(self + 1923) != 0;
}

//----- (0046A380) --------------------------------------------------------
bool  AviPlayer_IsIcmDecoderIdle(int self)
{
  int pendingCount; // edx
  int blitState; // eax
  bool result; // al

  result = 0;
  if ( *(_BYTE *)(uintptr_t)(self + 2052) )
  {
    pendingCount = *(_DWORD *)(uintptr_t)(self + 1944);
    blitState = self + 1924;
    if ( !pendingCount && !*(_DWORD *)(uintptr_t)(blitState + 16) )
      return 1;
  }
  return result;
}

//----- (0046A3B0) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit2(int self)
{
  return (*(_BYTE *)(uintptr_t)(self + 2120) & 4) != 0;
}

//----- (0046A3C0) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit3(int self)
{
  return (*(_BYTE *)(uintptr_t)(self + 2120) & 8) != 0;
}

//----- (0046A3D0) --------------------------------------------------------
bool  AviPlayer_TestActiveModeFlag(int self)
{
  return *(_BYTE *)(uintptr_t)(self + 2052) && !*(_DWORD *)(uintptr_t)(self + 1944) && !*(_DWORD *)(uintptr_t)(self + 1940) && (*(_BYTE *)(uintptr_t)(self + 2120) & 8) != 0
      || (!*(_BYTE *)(uintptr_t)(self + 2052) || *(_DWORD *)(uintptr_t)(self + 1944) || *(_DWORD *)(uintptr_t)(self + 1940))
      && (*(_BYTE *)(uintptr_t)(self + 2120) & 4) != 0;
}

//----- (0046A430) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit2AndSubframe(int self)
{
  return (*(_BYTE *)(uintptr_t)(self + 2120) & 4) != 0 && *(_BYTE *)(uintptr_t)(self + 1923);
}

//----- (0046A450) --------------------------------------------------------
bool  AviPlayer_SupportsRequiredPlaybackCaps(int self)
{
  int requiredCaps; // edx

  requiredCaps = *(_DWORD *)(uintptr_t)(self + 2171);
  LOBYTE(requiredCaps) = requiredCaps | 2;
  return ((*(_DWORD *)(uintptr_t)(self + 2175) | requiredCaps) & *(_DWORD *)(uintptr_t)(self + 2119)) == (*(_DWORD *)(uintptr_t)(self + 2175) | requiredCaps);
}

//----- (0046A480) --------------------------------------------------------
bool  AviPlayer_HasValidRateParams(int self)
{
  return *(_BYTE *)(uintptr_t)(self + 1968) && *(_DWORD *)(uintptr_t)(self + 1964);
}

//----- (0046A4A0) --------------------------------------------------------
bool  AviPlayer_IsPlaybackRateInRange(int self)
{
  int stretchRatio; // eax

  stretchRatio = 1000 * (*(_DWORD *)(uintptr_t)(self + 2071) - *(_DWORD *)(uintptr_t)(self + 2063)) / (*(_DWORD *)(uintptr_t)(self + 2087) - *(_DWORD *)(uintptr_t)(self + 2079));
  return stretchRatio >= *(_DWORD *)(uintptr_t)(self + 2143) && stretchRatio <= *(_DWORD *)(uintptr_t)(self + 2147);
}

//----- (0046A510) --------------------------------------------------------
unsigned int  Audio_MapDSoundHResultToErrorCode(unsigned int result)
{
  if ( result >= 0x8878001E )
  {
    if ( result <= 0x8878001E )
      return 1;
    if ( result >= 0x88780078 )
    {
      if ( result <= 0x88780078 )
        return 40;
      if ( result < 0x88780096 )
      {
        if ( result == -2005401470 )
          return 41;
        return 1;
      }
      if ( result <= 0x88780096 )
        return 21;
      if ( result >= 0x887800A0 )
      {
        if ( result > 0x887800A0 )
        {
          if ( result == -2005401430 )
            return 1;
          return 1;
        }
        return 41;
      }
    }
    else
    {
      if ( result >= 0x88780046 )
      {
        if ( result == -2005401500 )
          return 42;
        return 1;
      }
      if ( result == -2005401550 )
        return 39;
    }
    return 1;
  }
  if ( result >= 0x80040110 )
  {
    if ( result > 0x80040110 )
    {
      if ( result < 0x80070057 )
      {
        if ( result == -2147024882 )
          return 2;
        return 1;
      }
      if ( result <= 0x80070057 )
        return 22;
      if ( result == -2005401590 )
        return 41;
    }
    return 1;
  }
  if ( result >= 0x80004001 )
  {
    if ( result > 0x80004001 )
      return 1;
    return 39;
  }
  if ( result )
    return 1;
  return result;
}
// 46A595: simplified comparisons for 'eax.4': <88780047u || !=88780064 became !=88780064

//----- (0046A5F0) --------------------------------------------------------
int __cdecl Audio_ComputeMixChunkSampleCount(unsigned int scaledUpdateRate)
{
  unsigned int chunkSamples; // eax

  chunkSamples = 100 * g_AudioSampleRateHz / scaledUpdateRate + 1;
  LOBYTE(chunkSamples) = chunkSamples & 0xFE;
  g_Audio_MixChunkSampleCount = chunkSamples;
  g_CSS_MixChunkSamplesRemaining = chunkSamples;
  return 0;
}
// 54D390: using guessed type int dword_54D390;
// 54D394: using guessed type int dword_54D394;
// 54D39C: using guessed type int dword_54D39C;

//----- (0046A610) --------------------------------------------------------
signed int __cdecl Audio_DetectDSoundHardwareAccel(_DWORD *accelFlagOut)
{
  signed int result; // eax
  int v2; // ecx
  int dsCaps; // [esp+4h] [ebp-68h] BYREF
  char dsCapsFlags; // [esp+8h] [ebp-64h]

  if ( g_CSS_DSoundAccelDetectEnabled )
  {
    if ( g_AudioWindowHandle )
    {
      g_DSoundCoopWindowHandle = g_AudioWindowHandle;
      if ( DirectSoundCreate(0, &g_DirectSoundDevice, 0) )
      {
        *accelFlagOut = 0;
        return 0;
      }
      else
      {
        memset_(&dsCaps, 0);
        dsCaps = 96;
        if ( (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 16))(g_DirectSoundDevice, v2) || (dsCapsFlags & 0x20) != 0 )
        {
          *accelFlagOut = 0;
          (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 8))(g_DirectSoundDevice);
          return 0;
        }
        else
        {
          *accelFlagOut = 1;
          (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 8))(g_DirectSoundDevice);
          return 0;
        }
      }
    }
    else
    {
      result = 1;
      *accelFlagOut = 0;
    }
  }
  else
  {
    result = 0;
    *accelFlagOut = 0;
  }
  return result;
}
// 46A688: variable 'v2' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 4E979E: using guessed type int __stdcall DirectSoundCreate(_DWORD, _DWORD, _DWORD);
// 519CF8: using guessed type int dword_519CF8;
// 54D368: using guessed type int dword_54D368;
// 54D378: using guessed type int dword_54D378;
// 54D470: using guessed type int dword_54D470;

//----- (0046A6D0) --------------------------------------------------------
int __thiscall Audio_ComputeBytesPerFrame(void *this)
{
  int result; // eax
  int dsCaps; // [esp+4h] [ebp-6Ch] BYREF
  char dsCapsFlags; // [esp+8h] [ebp-68h]
  void *v4 CLASH95_UNUSED; // [esp+68h] [ebp-8h]

  v4 = this;
  memset_(this, 0);
  dsCaps = 96;
  (*(void (__stdcall **)(int, int *))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 16))(g_DirectSoundDevice, &dsCaps);
  if ( (dsCapsFlags & 8) == 0 )
    LOBYTE(g_MixerFormatFlags) = g_MixerFormatFlags & 0xF7;
  if ( (dsCapsFlags & 2) == 0 )
    LOBYTE(g_MixerFormatFlags) = g_MixerFormatFlags & 0xFD;
  result = ((g_MixerFormatFlags & 8) != 0) + 1;
  g_CSS_SampleFrameBytes = result;
  if ( (g_MixerFormatFlags & 2) != 0 )
    g_CSS_SampleFrameBytes = 2 * result;
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 54D368: using guessed type int dword_54D368;
// 54D384: using guessed type int dword_54D384;
// 54D388: using guessed type int dword_54D388;

//----- (0046A750) --------------------------------------------------------
signed int Audio_InitDSoundDevice(void)
{
  unsigned int hr; // eax
  void *v2; // ecx
  int v3; // ecx
  unsigned int rawStreamBytes; // eax
  int alignedStreamBytes; // esi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  __int16 v10; // cx
  int v11; // ecx
  _DWORD bufferCaps[5]; // [esp+24h] [ebp-54h] BYREF
  int bufferDescSize; // [esp+38h] [ebp-40h] BYREF
  int bufferDescFlags CLASH95_UNUSED; // [esp+3Ch] [ebp-3Ch]
  int bufferBytes CLASH95_UNUSED; // [esp+40h] [ebp-38h]
  __int16 *formatPtr CLASH95_UNUSED; // [esp+48h] [ebp-30h]
  __int16 wFormatTag; // [esp+4Ch] [ebp-2Ch] BYREF
  __int16 nChannels CLASH95_UNUSED; // [esp+4Eh] [ebp-2Ah]
  int samplesPerSec CLASH95_UNUSED; // [esp+50h] [ebp-28h]
  int avgBytesPerSec CLASH95_UNUSED; // [esp+54h] [ebp-24h]
  __int16 blockAlign CLASH95_UNUSED; // [esp+58h] [ebp-20h]
  __int16 bitsPerSample CLASH95_UNUSED; // [esp+5Ah] [ebp-1Eh]
  __int16 cbSize CLASH95_UNUSED; // [esp+5Ch] [ebp-1Ch]

  if ( !g_AudioWindowHandle )
    return 1;
  g_DSoundCoopWindowHandle = g_AudioWindowHandle;
  g_CSS_DSoundWritePrimaryMode = 0;
  hr = DirectSoundCreate(0, &g_DirectSoundDevice, 0);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  Audio_ComputeBytesPerFrame(v2);
  if ( g_CSS_DSoundAccelDetectEnabled != 2
    || (*(int (__stdcall **)(int, int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 24))(g_DirectSoundDevice, g_DSoundCoopWindowHandle, 4) )
  {
    if ( !g_CSS_DSoundWritePrimaryMode )
    {
      hr = (*(int (__stdcall **)(int, int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 24))(g_DirectSoundDevice, g_DSoundCoopWindowHandle, 3);
      if ( hr )
        return Audio_ReturnDSoundError(hr);
      memset_(&bufferDescSize, 0);
      bufferBytes = 0;
      formatPtr = 0;
      bufferDescSize = 20;
      bufferDescFlags = 1;
      hr = (*(int (__stdcall **)(int, int, int *, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 12))(
             g_DirectSoundDevice,
             v7,
             &g_DSoundPrimaryBuffer,
             0);
      if ( hr )
        return Audio_ReturnDSoundError(hr);
      memset_(v8, 0);
      wFormatTag = 1;
      nChannels = ((g_MixerFormatFlags & 2) != 0) + 1;
      samplesPerSec = g_AudioSampleRateHz;
      avgBytesPerSec = g_AudioSampleRateHz * g_CSS_SampleFrameBytes;
      blockAlign = g_CSS_SampleFrameBytes;
      if ( (g_MixerFormatFlags & 8) != 0 )
        bitsPerSample = 16;
      else
        bitsPerSample = 8;
      cbSize = 0;
      (*(void (__stdcall **)(int, __int16 *))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 56))(g_DSoundPrimaryBuffer, &wFormatTag);
    }
  }
  else
  {
    g_CSS_DSoundWritePrimaryMode = 1;
  }
  rawStreamBytes = g_CSS_SampleFrameBytes * 3 * g_AudioSampleRateHz / (unsigned int)g_CSS_MixUpdateRateHz;
  alignedStreamBytes = rawStreamBytes + 15;
  g_DSoundStreamWriteOffset = 0;
  LOWORD(alignedStreamBytes) = (rawStreamBytes + 15) & 0xFFF0;
  if ( !g_CSS_DSoundWritePrimaryMode )
  {
    g_DSoundStreamBufferBytes = alignedStreamBytes;
    g_DSoundRefillThresholdBytes = 16;
    memset_(v3, 0);
    wFormatTag = 1;
    nChannels = ((g_MixerFormatFlags & 2) != 0) + 1;
    samplesPerSec = g_AudioSampleRateHz;
    avgBytesPerSec = g_AudioSampleRateHz * g_CSS_SampleFrameBytes;
    blockAlign = g_CSS_SampleFrameBytes;
    if ( (g_MixerFormatFlags & 8) != 0 )
      bitsPerSample = 16;
    else
      bitsPerSample = 8;
    cbSize = 0;
    memset_(20, 0);
    bufferDescSize = v6;
    bufferBytes = g_DSoundStreamBufferBytes;
    formatPtr = &wFormatTag;
    bufferDescFlags = 0x10000;
    hr = (*(int (__stdcall **)(int, int *, int *, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 12))(
           g_DirectSoundDevice,
           &bufferDescSize,
           &g_DSoundPrimaryBuffer,
           0);
    if ( !hr )
    {
      hr = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
      if ( !hr )
        return 0;
    }
    return Audio_ReturnDSoundError(hr);
  }
  memset_(&bufferDescSize, 0);
  bufferDescSize = 20;
  bufferBytes = 0;
  formatPtr = 0;
  bufferDescFlags = 1;
  hr = (*(int (__stdcall **)(int, int, int *, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 12))(
         g_DirectSoundDevice,
         v9,
         &g_DSoundPrimaryBuffer,
         0);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  memset_(1, 0);
  wFormatTag = v10;
  nChannels = v10 + ((g_MixerFormatFlags & 2) != 0);
  samplesPerSec = g_AudioSampleRateHz;
  avgBytesPerSec = g_AudioSampleRateHz * g_CSS_SampleFrameBytes;
  blockAlign = g_CSS_SampleFrameBytes;
  bitsPerSample = (g_MixerFormatFlags & 8) != 0 ? 16 : 8;
  cbSize = 0;
  hr = (*(int (__stdcall **)(int, __int16 *))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 56))(g_DSoundPrimaryBuffer, &wFormatTag);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  memset_(v11, 0);
  bufferCaps[0] = 20;
  hr = (*(int (__stdcall **)(int, _DWORD *))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 12))(g_DSoundPrimaryBuffer, bufferCaps);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  g_DSoundStreamBufferBytes = bufferCaps[2];
  hr = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  if ( alignedStreamBytes + 16 >= (unsigned int)g_DSoundStreamBufferBytes )
    g_DSoundRefillThresholdBytes = 16;
  else
    g_DSoundRefillThresholdBytes = g_DSoundStreamBufferBytes - alignedStreamBytes;
  return 0;
}
// 46A794: variable 'v2' is possibly undefined
// 46A82A: variable 'v3' is possibly undefined
// 46A8AF: variable 'v6' is possibly undefined
// 46A96B: variable 'v7' is possibly undefined
// 46A97D: variable 'v8' is possibly undefined
// 46AA3C: variable 'v9' is possibly undefined
// 46AA62: variable 'v10' is possibly undefined
// 46AAD2: variable 'v11' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 4E979E: using guessed type int __stdcall DirectSoundCreate(_DWORD, _DWORD, _DWORD);
// 519CF4: using guessed type int dword_519CF4;
// 519CF8: using guessed type int dword_519CF8;
// 54D368: using guessed type int dword_54D368;
// 54D36C: using guessed type int dword_54D36C;
// 54D370: using guessed type int dword_54D370;
// 54D378: using guessed type int dword_54D378;
// 54D380: using guessed type int dword_54D380;
// 54D384: using guessed type int dword_54D384;
// 54D388: using guessed type int dword_54D388;
// 54D38C: using guessed type int dword_54D38C;
// 54D398: using guessed type int dword_54D398;
// 54D39C: using guessed type int dword_54D39C;
// 54D470: using guessed type int dword_54D470;

//----- (0046AB70) --------------------------------------------------------
unsigned int Audio_ReleaseDSoundDevice(void)
{
  unsigned int hr; // eax

  hr = (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 72))(g_DSoundPrimaryBuffer);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 8))(g_DSoundPrimaryBuffer);
  (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DirectSoundDevice + 8))(g_DirectSoundDevice);
  return 0;
}
// 54D368: using guessed type int dword_54D368;
// 54D370: using guessed type int dword_54D370;

//----- (0046ABC0) --------------------------------------------------------
signed int __cdecl Audio_InitSoundSystem(int sampleRateHz, char formatFlags)
{
  signed int errCode; // ebx
  signed int result; // eax

  if ( g_CSS_MixUpdateRateHz < 30 )
    g_CSS_MixUpdateRateHz = 30;
  g_AudioSampleRateHz = sampleRateHz;
  InitializeCriticalSection(&stru_54D350);
  EnterCriticalSection(&stru_54D350);
  g_MixerFormatFlags = ((formatFlags & 1) == 0) + 1;
  if ( (formatFlags & 4) != 0 )
    LOBYTE(g_MixerFormatFlags) = g_MixerFormatFlags | 4;
  else
    LOBYTE(g_MixerFormatFlags) = g_MixerFormatFlags | 8;
  g_CSS_SampleFrameBytes = ((g_MixerFormatFlags & 8) != 0) + 1;
  if ( (g_MixerFormatFlags & 2) != 0 )
    g_CSS_SampleFrameBytes = 2 * (((g_MixerFormatFlags & 8) != 0) + 1);
  errCode = Audio_InitDSoundDevice();
  if ( errCode || (CSS_InitMixBuffers(g_AudioSampleRateHz, ((g_MixerFormatFlags & 2) != 0) + 1), (errCode = Audio_ComputeMixChunkSampleCount(100 * g_CSS_MixUpdateRateHz)) != 0) )
  {
    LeaveCriticalSection(&stru_54D350);
    return errCode;
  }
  else
  {
    switch ( g_MixerFormatFlags )
    {
      case 5:
        g_Audio_MixToOutputConvertFn = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8;
        goto LABEL_11;
      case 6:
        g_Audio_MixToOutputConvertFn = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8Stereo;
        goto LABEL_11;
      case 9:
        g_Audio_MixToOutputConvertFn = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_MixInterleaved16;
        goto LABEL_11;
      case 10:
        g_Audio_MixToOutputConvertFn = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM16Stereo;
LABEL_11:
        LeaveCriticalSection(&stru_54D350);
        result = 0;
        break;
      default:
        LeaveCriticalSection(&stru_54D350);
        result = 22;
        break;
    }
  }
  return result;
}
// 519CF4: using guessed type int dword_519CF4;
// 54D37C: using guessed type int (__cdecl *dword_54D37C)(_DWORD, _DWORD, _DWORD, _DWORD);
// 54D384: using guessed type int dword_54D384;
// 54D388: using guessed type int dword_54D388;
// 54D39C: using guessed type int dword_54D39C;

//----- (0046AD10) --------------------------------------------------------
unsigned int Audio_ShutdownSoundSystem(void)
{
  unsigned int errCode; // ebx

  EnterCriticalSection(&stru_54D350);
  CSS_FreeMixBuffers();
  errCode = Audio_ReleaseDSoundDevice();
  LeaveCriticalSection(&stru_54D350);
  if ( errCode )
    return errCode;
  DeleteCriticalSection(&stru_54D350);
  return 0;
}

//----- (0046AD60) --------------------------------------------------------
int __cdecl Audio_GetSoundFormatFlags(_DWORD *flagsOut)
{
  *flagsOut = g_MixerFormatFlags;
  return 0;
}
// 54D384: using guessed type int dword_54D384;

//----- (0046AD70) --------------------------------------------------------
unsigned int Audio_RefreshPlayCursor(void)
{
  unsigned int hr; // eax
  int playCursor; // [esp+Ch] [ebp-8h] BYREF
  _BYTE writeCursor[4]; // [esp+10h] [ebp-4h] BYREF

  EnterCriticalSection(&stru_54D350);
  hr = (*(int (__stdcall **)(int, int *, _BYTE *))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 16))(g_DSoundPrimaryBuffer, &playCursor, writeCursor);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  g_CSS_DSoundPlayCursor = playCursor;
  LeaveCriticalSection(&stru_54D350);
  return 0;
}
// 54D370: using guessed type int dword_54D370;
// 54D374: using guessed type int dword_54D374;

//----- (0046ADC0) --------------------------------------------------------
unsigned int __cdecl Audio_FillDSoundBuffer(_DWORD *mixCompleteOut)
{
  unsigned int mixBufSamples; // ebp
  unsigned int bytesFree; // edi
  DWORD TickCount; // eax
  unsigned int fillBytes; // edi
  unsigned int samplesToFill; // edi
  unsigned int chunkSamples; // esi
  int lockResult; // eax
  unsigned int hr; // ebx
  unsigned int newWriteOffset; // ecx
  int lockPtr1; // [esp+20h] [ebp-20h] BYREF
  int lockPtr2; // [esp+24h] [ebp-1Ch] BYREF
  unsigned int lockBytes1; // [esp+28h] [ebp-18h] BYREF
  _DWORD lockBytes2[5]; // [esp+2Ch] [ebp-14h] BYREF

  EnterCriticalSection(&stru_54D350);
  mixBufSamples = (unsigned int)g_CssMixBufferSizeBytes >> 2;
  if ( (g_MixerFormatFlags & 2) != 0 )
    mixBufSamples = (unsigned int)g_CssMixBufferSizeBytes >> 3;
  if ( g_DSoundStreamWriteOffset > (unsigned int)g_CSS_DSoundPlayCursor )
    bytesFree = g_CSS_DSoundPlayCursor + g_DSoundStreamBufferBytes - g_DSoundStreamWriteOffset;
  else
    bytesFree = g_CSS_DSoundPlayCursor - g_DSoundStreamWriteOffset;
  if ( bytesFree > g_DSoundRefillThresholdBytes )
  {
    TickCount = 0;
    fillBytes = bytesFree - g_DSoundRefillThresholdBytes;
LABEL_7:
    g_DSoundStallTickTimestamp = TickCount;
    goto LABEL_8;
  }
  fillBytes = 0;
  if ( GetForegroundWindow() == (HWND)(uintptr_t)g_DSoundCoopWindowHandle )
  {
    if ( g_CSS_AudioHadForegroundFocus )
    {
      if ( !g_DSoundStallTickTimestamp || GetTickCount() < g_DSoundStallTickTimestamp )
      {
        TickCount = GetTickCount();
        goto LABEL_7;
      }
      if ( GetTickCount() - g_DSoundStallTickTimestamp > 0x3E8 )
      {
        (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 80))(g_DSoundPrimaryBuffer);
        (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
        g_DSoundStallTickTimestamp = 0;
      }
    }
    else
    {
      g_CSS_AudioHadForegroundFocus = 1;
    }
  }
  else
  {
    g_CSS_AudioHadForegroundFocus = 0;
  }
LABEL_8:
  samplesToFill = fillBytes / g_CSS_SampleFrameBytes;
  while ( samplesToFill )
  {
    if ( !g_CSS_MixChunkSamplesRemaining )
      break;
    if ( samplesToFill <= g_CSS_MixChunkSamplesRemaining )
      chunkSamples = samplesToFill;
    else
      chunkSamples = g_CSS_MixChunkSamplesRemaining;
    if ( chunkSamples > mixBufSamples )
      chunkSamples = mixBufSamples;
    samplesToFill -= chunkSamples;
    g_CSS_MixChunkSamplesRemaining -= chunkSamples;
    CSS_TickChannelLevels(mixBufSamples, chunkSamples);
    while ( 1 )
    {
      lockResult = (*(int (__stdcall **)(int, int, unsigned int, int *, unsigned int *, int *, _DWORD *, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 44))(
             g_DSoundPrimaryBuffer,
             g_DSoundStreamWriteOffset,
             chunkSamples * g_CSS_SampleFrameBytes,
             &lockPtr1,
             &lockBytes1,
             &lockPtr2,
             lockBytes2,
             0);
      hr = lockResult;
      if ( !lockResult )
        break;
      if ( lockResult != -2005401450 )
        goto LABEL_19;
      if ( (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 80))(g_DSoundPrimaryBuffer) )
      {
        LeaveCriticalSection(&stru_54D350);
        *mixCompleteOut = 0;
        return 0;
      }
      hr = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
      if ( hr )
        goto LABEL_19;
    }
    if ( lockBytes1 )
      g_Audio_MixToOutputConvertFn(lockBytes1 / g_CSS_SampleFrameBytes, lockPtr1, 0, g_CSS_MixAccumBufferPtr);
    if ( lockBytes2[0] )
      g_Audio_MixToOutputConvertFn(lockBytes2[0] / (unsigned int)g_CSS_SampleFrameBytes, lockPtr2, 0, g_CSS_MixAccumBufferPtr + 4 * (lockBytes1 >> 1));
    newWriteOffset = lockBytes2[0] + lockBytes1 + g_DSoundStreamWriteOffset;
    g_DSoundStreamWriteOffset = newWriteOffset;
    if ( newWriteOffset >= g_DSoundStreamBufferBytes )
      g_DSoundStreamWriteOffset = newWriteOffset - g_DSoundStreamBufferBytes;
    hr = (*(int (__stdcall **)(int, int, unsigned int, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)g_DSoundPrimaryBuffer + 76))(
           g_DSoundPrimaryBuffer,
           lockPtr1,
           lockBytes1,
           lockPtr2,
           lockBytes2[0]);
    if ( hr )
    {
LABEL_19:
      LeaveCriticalSection(&stru_54D350);
      return Audio_ReturnDSoundError(hr);
    }
  }
  if ( g_CSS_MixChunkSamplesRemaining )
  {
    *mixCompleteOut = 0;
  }
  else
  {
    g_CSS_MixChunkSamplesRemaining = g_Audio_MixChunkSampleCount;
    *mixCompleteOut = 1;
  }
  LeaveCriticalSection(&stru_54D350);
  return 0;
}
// 54D36C: using guessed type int dword_54D36C;
// 54D370: using guessed type int dword_54D370;
// 54D374: using guessed type int dword_54D374;
// 54D378: using guessed type int dword_54D378;
// 54D37C: using guessed type int (__cdecl *dword_54D37C)(_DWORD, _DWORD, _DWORD, _DWORD);
// 54D384: using guessed type int dword_54D384;
// 54D388: using guessed type int dword_54D388;
// 54D38C: using guessed type int dword_54D38C;
// 54D390: using guessed type int dword_54D390;
// 54D394: using guessed type int dword_54D394;
// 54D398: using guessed type int dword_54D398;
// 54D3A0: using guessed type int dword_54D3A0;
// 54D3A4: using guessed type int dword_54D3A4;
// 54DB98: using guessed type int dword_54DB98;

//----- (0046B110) --------------------------------------------------------
int __cdecl Audio_ClipMixBufferToPCM16(int sampleCount, int destBase, int destOffset, signed int *mixBuffer)
{
  _WORD *dest; // edi
  int i; // ecx
  int sample; // eax

  dest = (_WORD *)(uintptr_t)(destOffset + destBase);
  for ( i = sampleCount; i; --i )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        sample = *mixBuffer++;
        if ( sample <= 0x7FFF )
          break;
        *dest++ = 0x7FFF;
        if ( !--i )
          return (int)(intptr_t)dest - destBase;
      }
      if ( sample < -32768 )
        break;
      *dest++ = sample;
      if ( !--i )
        return (int)(intptr_t)dest - destBase;
    }
    *dest++ = 0x8000;
  }
  return (int)(intptr_t)dest - destBase;
}

//----- (0046B169) --------------------------------------------------------
_BYTE *__cdecl Audio_ClipMixBufferToPCM8(int sampleCount, int destBase, int destOffset, int *mixBuffer)
{
  _BYTE *dest; // edi
  int i; // ecx
  int sample; // eax
  int biased; // eax

  dest = (_BYTE *)(uintptr_t)(destOffset + destBase);
  for ( i = sampleCount; i; --i )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        sample = *mixBuffer++;
        biased = sample + 0x8000;
        if ( biased <= 0x10000 )
          break;
        *dest++ = -1;
        if ( !--i )
          return &dest[-destBase];
      }
      if ( biased < 0 )
        break;
      *dest++ = BYTE1(biased);
      if ( !--i )
        return &dest[-destBase];
    }
    *dest++ = 0;
  }
  return &dest[-destBase];
}

//----- (0046B1BA) --------------------------------------------------------
int __cdecl Audio_ClipMixBufferToPCM16Stereo(int sampleCount, int destBase, int destOffset, signed int *mixBuffer)
{
  return Audio_MixInterleaved16(2 * sampleCount, destBase, destOffset, mixBuffer);
}

//----- (0046B1D7) --------------------------------------------------------
_BYTE *__cdecl Audio_ClipMixBufferToPCM8Stereo(int sampleCount, int destBase, int destOffset, int *mixBuffer)
{
  return Audio_ClipMixBufferToPCM8(2 * sampleCount, destBase, destOffset, mixBuffer);
}

//----- (0046B200) --------------------------------------------------------
int  Audio_ReadWavHeaderFromStream(int fileName, _DWORD *formatOut)
{
  int result; // eax
  int streamPos; // eax
  void (__fastcall **seekFunc)(_DWORD, int); // ecx
  char formatCode; // al
  char riffTag[8]; // [esp+0h] [ebp-40h] BYREF
  char waveTag[4]; // [esp+8h] [ebp-38h] BYREF
  char fmtTag[4]; // [esp+Ch] [ebp-34h] BYREF
  int fmtChunkSize; // [esp+10h] [ebp-30h]
  unsigned __int16 wFormatTag; // [esp+14h] [ebp-2Ch]
  unsigned __int16 nChannels; // [esp+16h] [ebp-2Ah]
  int sampleRate; // [esp+18h] [ebp-28h]
  unsigned __int16 blockAlign; // [esp+20h] [ebp-20h]
  char dataTag[4]; // [esp+24h] [ebp-1Ch] BYREF
  int stream; // [esp+28h] [ebp-18h]

  result = (*(int (__fastcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_MediaFileStreamProvider + 12))(fileName, fileName);
  stream = result;
  if ( !result )
    return result;
  (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)result + 20))();
  if ( (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)stream + 16))() == -1
    || memcmp(riffTag, aRiff, 4)
    || memcmp(waveTag, aWave, 4)
    || memcmp(fmtTag, aFmt, 4)
    || (streamPos = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)stream + 4))(),
        (*seekFunc)(seekFunc, fmtChunkSize + streamPos - 16),
        (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)stream + 20))(),
        memcmp(dataTag, aData, 4)) )
  {
LABEL_3:
    (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)g_MediaFileStreamProvider + 20))();
    return 0;
  }
  (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)stream + 20))();
  formatOut[2] = sampleRate;
  if ( wFormatTag != 1 )
  {
    if ( wFormatTag == 32787 )
    {
      *formatOut = (char)((nChannels != 1) + 5);
      return stream;
    }
    goto LABEL_3;
  }
  if ( nChannels == 1 )
    formatCode = 1;
  else
    formatCode = 3;
  *formatOut = formatCode;
  if ( blockAlign / (int)nChannels == 2 )
    ++*formatOut;
  sampleRate = formatOut[2];
  return stream;
}
// 46B2D5: variable 'v5' is possibly undefined
// 54D4B8: using guessed type int dword_54D4B8;
