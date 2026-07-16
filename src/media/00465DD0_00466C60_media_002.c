/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00465DD0) --------------------------------------------------------
int  AviPlayer_CloseStreams(int self)
{
  int readIndex; // ebp
  int result; // eax
  int videoStream; // ecx

  CAviDecompressor_RequestDecodeThreadStop(self);
  ++*(_DWORD *)(uintptr_t)(self + 175);
  EnterCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 179));
  LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 179));
  --*(_DWORD *)(uintptr_t)(self + 175);
  while ( 1 )
  {
    readIndex = *(_DWORD *)(uintptr_t)(self + 207);
    if ( *(_DWORD *)(uintptr_t)(self + 211) == readIndex )
      break;
    *(_DWORD *)(uintptr_t)(self + 207) = readIndex + 1;
    PulseEvent(*(HANDLE *)(uintptr_t)(self + 171));
  }
  AviPlayer_FlushVideoFrameQueue(self);
  j_j__nfree_();
  *(_DWORD *)(uintptr_t)(self + 163) = 0;
  result = j_j__nfree_();
  videoStream = *(_DWORD *)(uintptr_t)(self + 7);
  *(_DWORD *)(uintptr_t)(self + 151) = 0;
  if ( videoStream )
  {
    AVIStreamEndStreaming(videoStream);
    result = AVIStreamRelease(*(_DWORD *)(uintptr_t)(self + 7));
    *(_DWORD *)(uintptr_t)(self + 7) = 0;
  }
  if ( *(_DWORD *)(uintptr_t)(self + 3) )
  {
    result = AVIFileRelease(*(_DWORD *)(uintptr_t)(self + 3));
    *(_DWORD *)(uintptr_t)(self + 3) = 0;
  }
  if ( *(_BYTE *)(uintptr_t)self )
  {
    result = AVIFileExit();
    *(_BYTE *)(uintptr_t)self = 0;
  }
  return result;
}
// 4E97B6: using guessed type int AVIFileExit(void);
// 4E97BC: using guessed type int __stdcall AVIStreamEndStreaming(_DWORD);
// 4E97C2: using guessed type int __stdcall AVIStreamRelease(_DWORD);
// 4E97C8: using guessed type int __stdcall AVIFileRelease(_DWORD);

//----- (00465EC0) --------------------------------------------------------
int  AviPlayer_GetBufferedVideoFrame(int self, int targetFrame, _DWORD *frameFlagsOut, _DWORD *frameIndexOut)
{
  int readIndex; // ebx
  int clampedIndex; // edx
  int scanIndex; // eax
  int i; // edx

  readIndex = *(_DWORD *)(uintptr_t)(self + 207);
  if ( *(_DWORD *)(uintptr_t)(self + 211) != readIndex )
  {
    if ( readIndex < targetFrame )
    {
      clampedIndex = *(_DWORD *)(uintptr_t)(self + 211) - 1;
      if ( clampedIndex >= targetFrame )
        clampedIndex = targetFrame;
      scanIndex = clampedIndex;
      for ( i = 12 * clampedIndex; scanIndex > *(_DWORD *)(uintptr_t)(self + 207) && *(_DWORD *)(uintptr_t)(i + *(_DWORD *)(uintptr_t)(self + 203)); i -= 12 )
        --scanIndex;
      if ( scanIndex > *(_DWORD *)(uintptr_t)(self + 207) )
        *(_DWORD *)(uintptr_t)(self + 207) = scanIndex;
    }
    *frameIndexOut = *(_DWORD *)(uintptr_t)(self + 207);
    goto LABEL_12;
  }
  *frameIndexOut = *(_DWORD *)(uintptr_t)(self + 211);
  if ( !WaitForSingleObject(*(HANDLE *)(uintptr_t)(self + 167), 0x3E8u) )
  {
LABEL_12:
    *frameFlagsOut = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 203) + 12 * *(_DWORD *)(uintptr_t)(self + 207));
    return *(_DWORD *)(uintptr_t)(self + 163) + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 203) + 12 * *(_DWORD *)(uintptr_t)(self + 207) + 4);
  }
  return 0;
}

//----- (00465FB0) --------------------------------------------------------
unsigned int  AviPlayer_PopBufferedAudioData(int self, void *destBuffer)
{
  int queueBase; // edx
  _DWORD *entry; // eax
  unsigned int frameBytes; // ebp

  if ( *(_DWORD *)(uintptr_t)(self + 399) == *(_DWORD *)(uintptr_t)(self + 395) )
    return 0;
  queueBase = self + 391;
  entry = (_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 391) + 8 * *(_DWORD *)(uintptr_t)(self + 395));
  frameBytes = entry[1];
  qmemcpy(destBuffer, (const void *)(uintptr_t)(*entry + *(_DWORD *)(uintptr_t)(self + 375)), frameBytes);
  ++*(_DWORD *)(uintptr_t)(queueBase + 4);
  PulseEvent(*(HANDLE *)(uintptr_t)(self + 387));
  return frameBytes;
}

//----- (004660D0) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
char  AviPlayer_OpenVideoCodec(
        int codecState,
        int fccHandler,
        int *outputFormat,
        int inputFormat,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        __int128 a12,
        __int64 a13,
        __int64 a14,
        __int64 a15,
        __int64 a16,
        __int64 a17,
        __int64 a18,
        __int64 a19,
        __int64 a20,
        int a21)
{
  int outFormatDest; // edx
  int hic; // eax
  int hicFallback; // eax
  int inputBmi; // eax
  int srcWidth; // ebx
  int outFormatPtr; // esi
  unsigned int srcHeight; // eax
  int hicHandle; // ecx
  int inputFormatPtr; // edx
  int v31; // [esp+0h] [ebp-120h]
  int v32; // [esp+0h] [ebp-120h]

  *(_DWORD *)((char *)&a20 + 2) = codecState;
  *(_DWORD *)((char *)&a19 + 6) = fccHandler;
  *(_DWORD *)((char *)&a17 + 6) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a18 + 2) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a18 + 6) = &g_AviOpenVideoCodec_EHFrame;
  *(_DWORD *)((char *)&a19 + 2) = 0;
  *(_DWORD *)(uintptr_t)(codecState + 4) = inputFormat;
  if ( outputFormat && (*(unsigned __int16 *)(uintptr_t)(inputFormat + 14) > 8u || outputFormat[2] >= 0) )
  {
    outFormatDest = *(_DWORD *)((char *)&a20 + 2) + 8;
    qmemcpy((void *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 8), outputFormat, *outputFormat);
    hic = ICLocate(1667524982, *(_DWORD *)((char *)&a19 + 6), *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 4), outFormatDest, 2);
    **(_DWORD **)((char *)&a20 + 2) = hic;
  }
  BYTE6(a20) = **(_DWORD **)((char *)&a20 + 2) != 0;
  if ( !**(_DWORD **)((char *)&a20 + 2) )
  {
    hicFallback = ICGetDisplayFormat(
            0,
            *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 4),
            *(_DWORD *)((char *)&a20 + 2) + 8,
            0,
            0,
            0);
    **(_DWORD **)((char *)&a20 + 2) = hicFallback;
  }
  if ( **(_DWORD **)((char *)&a20 + 2) )
  {
    inputBmi = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 4);
    srcWidth = *(_DWORD *)(uintptr_t)(inputBmi + 4);
    outFormatPtr = *(_DWORD *)((char *)&a20 + 2) + 8;
    srcHeight = abs32(*(_DWORD *)(uintptr_t)(inputBmi + 8));
    hicHandle = **(_DWORD **)((char *)&a20 + 2);
    inputFormatPtr = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 4);
    *(_DWORD *)((char *)&a12 + 2) = 0;
    *(_DWORD *)((char *)&a12 + 6) = inputFormatPtr;
    *(_DWORD *)((char *)&a12 + 10) = 0;
    *(_DWORD *)((char *)&a15 + 6) = 0;
    *(_DWORD *)((char *)&a17 + 2) = srcHeight;
    *(_DWORD *)((char *)&a15 + 2) = srcHeight;
    *(_DWORD *)((char *)&a16 + 2) = 0;
    *(_DWORD *)((char *)&a16 + 6) = srcWidth;
    *(_DWORD *)((char *)&a12 + 14) = *(_DWORD *)((char *)&a20 + 2) + 8;
    *(_DWORD *)((char *)&a13 + 2) = 0;
    *(_DWORD *)((char *)&a13 + 6) = 0;
    *(_DWORD *)((char *)&a14 + 2) = 0;
    *(_DWORD *)((char *)&a14 + 6) = srcWidth;
    if ( ICSendMessage(hicHandle, 16444, (char *)&a12 + 2, 52, v31) )
    {
      if ( ICSendMessage(
             **(_DWORD **)((char *)&a20 + 2),
             16396,
             *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 4),
             outFormatPtr,
             v32) )
      {
        ExcString_Ctor();
        *(_DWORD *)((char *)&a19 + 2) = 1;
        ExcString_Ctor();
        *(_DWORD *)((char *)&a19 + 2) = 0;
        CRT_ThrowExcStringException();
      }
      else
      {
        *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 1508) = 0;
        BYTE2(a21) = BYTE6(a20) != 0;
      }
    }
    else
    {
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a20 + 2) + 1508) = 1;
      BYTE2(a21) = BYTE6(a20) != 0;
    }
  }
  else
  {
    BYTE2(a21) = 0;
  }
  return BYTE2(a21);
}
// 4661F8: inconsistent variable size for '^164.16'
// 466203: inconsistent variable size for '^174.8'
// 46620A: inconsistent variable size for '^17C.8'
// 4661E5: inconsistent variable size for '^184.8'
// 4661F5: inconsistent variable size for '^18C.8'
// 4660FD: inconsistent variable size for '^194.8'
// 46610D: inconsistent variable size for '^19C.8'
// 46615B: inconsistent variable size for '^1A4.8'
// 4660E4: inconsistent variable size for '^1A4.8'
// 4E97AA: using guessed type int __stdcall ICGetDisplayFormat(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 4E97B0: using guessed type int __stdcall ICLocate(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 4E980A: using guessed type int __stdcall ICSendMessage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (004662B0) --------------------------------------------------------
_DWORD * CAviDecompressor_CloseCodecHandle(_DWORD *result, int decompressEndParam, int drawEndParam)
{
  _DWORD *codecPtr; // ebx

  codecPtr = result;
  if ( *result )
  {
    if ( *((_BYTE *)result + 1508) )
    {
      ICSendMessage(*result, 16447, 0, 0, drawEndParam);
      result = (_DWORD *)(uintptr_t)ICClose(*codecPtr);
      *codecPtr = 0;
    }
    else
    {
      ICSendMessage(*result, 16398, 0, 0, decompressEndParam);
      result = (_DWORD *)(uintptr_t)ICClose(*codecPtr);
      *codecPtr = 0;
    }
  }
  return result;
}
// 4E97A4: using guessed type int __cdecl ICClose(_DWORD);
// 4E980A: using guessed type int __stdcall ICSendMessage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (00466310) --------------------------------------------------------
void  CAviDecompressor_RenderLoop(int self)
{
  DWORD sleepMs; // esi
  double nextFrameTimeMs; // st7
  int v4; // edx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-44h]
  tagRECT *v6; // [esp+4h] [ebp-40h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v6 = &j____wcpp_4_fs_handler_rtn_;
  while ( *(_BYTE *)(uintptr_t)(self + 2191) )
  {
    if ( AviPlayer_UpdateTargetFrameFromClock(self) && (*(_DWORD *)(uintptr_t)(self + 211) < *(_DWORD *)(uintptr_t)(self + 43) || AviPlayer_QueueBacklogCount(self + 203)) )
    {
      sleepMs = 0;
      if ( AviPlayer_CatchUpToTargetFrame(self) )
      {
        timeGetTime();
        nextFrameTimeMs = (double)*(unsigned int *)(uintptr_t)(self + 31)
           * ((double)(*(_DWORD *)(uintptr_t)(self + 2021) + 1)
            * g_CAviDecompressor_MillisecondsPerSecond)
           / (double)*(unsigned int *)(uintptr_t)(self + 35);
        _CHP(ExceptionList, v6);
        if ( (int)nextFrameTimeMs - v4 + 1 > 0 )
          sleepMs = (int)nextFrameTimeMs - v4 + 1;
      }
      Sleep(sleepMs);
      *(_DWORD *)(uintptr_t)(self + 2038) += sleepMs;
    }
    else
    {
      CAviDecompressor_RequestRenderStop(self);
    }
  }
}
// 4663EE: variable 'ExceptionList' is possibly undefined
// 4663EE: variable 'v6' is possibly undefined
// 4663FB: variable 'v4' is possibly undefined
// 501320: using guessed type double dbl_501320;

//----- (00466420) --------------------------------------------------------
DWORD __stdcall CAviDecompressor_RenderThreadProc(char *lpThreadParameter)
{
  if ( lpThreadParameter[2191] )
  {
    ++*((_DWORD *)lpThreadParameter + 550);
    EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 2204));
    SetEvent(*((HANDLE *)lpThreadParameter + 557));
    CAviDecompressor_RenderLoop((int)(intptr_t)lpThreadParameter);
    LeaveCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 2204));
    --*((_DWORD *)lpThreadParameter + 550);
  }
  return 0;
}

//----- (004664E0) --------------------------------------------------------
struct _EXCEPTION_REGISTRATION_RECORD * CAviDecompressor_BeginPlayback(int self)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  AviException_RebuildClipperOnSurfaceLoss(self, (int)(intptr_t)&j____wcpp_4_fs_handler_rtn_, (int)(intptr_t)&g_AviBeginPlayback_EHFrame, 0);
  *(_DWORD *)(uintptr_t)(self + 2183) = 0;
  *(_DWORD *)(uintptr_t)(self + 2034) = 0;
  *(_DWORD *)(uintptr_t)(self + 2038) = 0;
  AviPlayer_CatchUpToTargetFrame(self);
  *(_BYTE *)(uintptr_t)(self + 2) = 1;
  *(_DWORD *)(uintptr_t)(self + 2187) = timeGetTime();
  CSS_ResumeStream(*(_DWORD *)(uintptr_t)(self + 359));
  *(_BYTE *)(uintptr_t)(self + 2191) = 1;
  ResumeThread(*(HANDLE *)(uintptr_t)(self + 2192));
  return ExceptionList;
}

//----- (00466580) --------------------------------------------------------
BOOL  CAviDecompressor_RequestRenderStop(int self)
{
  *(_BYTE *)(uintptr_t)(self + 2191) = 0;
  return SetEvent(*(HANDLE *)(uintptr_t)(self + 2196));
}

//----- (004665A0) --------------------------------------------------------
_DWORD * AviPlayer_ShutdownDecodeState(int self)
{
  int v2; // esi
  int overlaySurface; // ecx
  int hideResult; // eax
  int sourceSurface; // eax
  int overlayIface; // edx
  int overlaySurface1; // eax
  int backSurface; // ecx
  int *v10; // eax
  int *overlaySurfaceIface; // [esp-4h] [ebp-100h]
  int *backSurfaceIface; // [esp-4h] [ebp-100h]

  if ( *(_BYTE *)(uintptr_t)(self + 2191) )
  {
    CAviDecompressor_RequestRenderStop(self);
    WaitForSingleObject(*(HANDLE *)(uintptr_t)(self + 2228), 0x7D0u);
    ++*(_DWORD *)(uintptr_t)(self + 2200);
    EnterCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 2204));
    LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 2204));
    --*(_DWORD *)(uintptr_t)(self + 2200);
  }
  else
  {
    ResumeThread(*(HANDLE *)(uintptr_t)(self + 2192));
  }
  CAviDecompressor_RequestDecodeThreadStop(self);
  AviPlayer_CloseStreams(self);
  v2 = self;
  if ( *(_BYTE *)(uintptr_t)(self + 1968) )
  {
    overlaySurface = *(_DWORD *)(uintptr_t)(self + 1964);
    if ( overlaySurface )
    {
      hideResult = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 132))(
             overlaySurface,
             self + 2095,
             *(_DWORD *)(uintptr_t)(self + 1956),
             self + 2063,
             512,
             0);
      if ( hideResult )
      {
        if ( hideResult != -2005532222
          || ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 96))(*(_DWORD *)(uintptr_t)(self + 1964)) != -2005532222
           || (overlaySurfaceIface = *(int **)(uintptr_t)(self + 1964), v2 = *overlaySurfaceIface, !(*(int (__stdcall **)(int *))(uintptr_t)(*overlaySurfaceIface + 108))(overlaySurfaceIface)))
          && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 96))(*(_DWORD *)(uintptr_t)(self + 1956)) != -2005532222
           || !(*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956)))
          && (v10 = *(int **)(uintptr_t)(self + 1964),
              v2 = *v10,
              (*(int (__stdcall **)(int *, int, _DWORD, int, int, _DWORD))(uintptr_t)(*v10 + 132))(
                v10,
                self + 2095,
                *(_DWORD *)(uintptr_t)(self + 1956),
                self + 2063,
                512,
                0)) )
        {
          v2 = 1;
          ExcString_Ctor();
          ExcString_Ctor();
          CRT_ThrowExcStringException();
        }
      }
    }
  }
  j_j__nfree_();
  *(_DWORD *)(uintptr_t)(self + 2179) = 0;
  j_j__nfree_();
  sourceSurface = *(_DWORD *)(uintptr_t)(self + 1952);
  *(_DWORD *)(uintptr_t)(self + 2058) = 0;
  if ( sourceSurface && *(_DWORD *)(uintptr_t)(self + 1956) )
  {
    (*(void (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 8))(*(_DWORD *)(uintptr_t)(self + 1956));
    *(_DWORD *)(uintptr_t)(self + 1956) = 0;
    *(_DWORD *)(uintptr_t)(self + 1952) = 0;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(self + 1956) = 0;
    *(_DWORD *)(uintptr_t)(self + 1952) = 0;
  }
  overlayIface = *(_DWORD *)(uintptr_t)(self + 1964);
  if ( overlayIface )
  {
    v2 = *(_DWORD *)(uintptr_t)overlayIface;
    (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlayIface + 8))(overlayIface);
    overlaySurface1 = *(_DWORD *)(uintptr_t)(self + 1960);
    *(_DWORD *)(uintptr_t)(self + 1964) = 0;
    if ( overlaySurface1 )
      (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface1 + 8))(overlaySurface1);
    *(_DWORD *)(uintptr_t)(self + 1960) = 0;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(self + 1960) = 0;
  }
  backSurface = *(_DWORD *)(uintptr_t)(self + 2017);
  if ( backSurface && *(_DWORD *)(uintptr_t)(self + 2013) )
  {
    (*(void (__stdcall **)(int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 152))(backSurface, 0);
    (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 8))(backSurface);
    backSurfaceIface = (int *)(uintptr_t)*(unsigned int *)(uintptr_t)(self + 2013);
    v2 = *backSurfaceIface;
    (*(void (__stdcall **)(int *))(uintptr_t)(*backSurfaceIface + 8))(backSurfaceIface);
    *(_DWORD *)(uintptr_t)(self + 2013) = 0;
    *(_DWORD *)(uintptr_t)(self + 2017) = 0;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(self + 2013) = 0;
    *(_DWORD *)(uintptr_t)(self + 2017) = 0;
  }
  return CAviDecompressor_CloseCodecHandle((_DWORD *)(uintptr_t)(self + 415), backSurface, v2);
}
// 466720: variable 'v8' is possibly undefined

//----- (00466870) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
int  AviPlayer_BlitFrameToSurface(
        _DWORD *self,
        int surface,
        int frameBits,
        int *destRect,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        int a13,
        int a14,
        int a15,
        int a16,
        int a17,
        int a18,
        int a19,
        int a20,
        int a21,
        int a22,
        int a23,
        int a24,
        int a25,
        int a26,
        int a27,
        int a28,
        int a29,
        int a30,
        __int64 blitScratch)
{
  _DWORD *blitState; // eax
  int lockResult; // eax
  int signedPitch; // eax
  int result; // eax
  int v37; // ecx
  int v38; // ecx
  int dcResult; // eax
  const BITMAPINFO *bitmapInfo; // eax
  _DWORD surfaceDesc[4]; // [esp+82h] [ebp-332h] BYREF
  int surfacePitch; // [esp+92h] [ebp-322h]
  char *surfaceBits; // [esp+A6h] [ebp-30Eh]
  int (**v44)(); // [esp+152h] [ebp-262h]
  int (**v45)(); // [esp+1BAh] [ebp-1FAh]
  int v46; // [esp+222h] [ebp-192h]
  int v47; // [esp+28Ah] [ebp-12Ah]

  *(_DWORD *)((char *)&blitScratch + 6) = frameBits;
  blitState = self + 481;
  if ( blitState[5] || blitState[4] )
  {
    surfaceDesc[0] = 108;
    lockResult = (*(int (__stdcall **)(int, int *, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 100))(surface, destRect, surfaceDesc, 1, 0);
    if ( !lockResult
      || lockResult == -2005532222
      && ((*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 108))(surface)
       || !(*(int (__stdcall **)(int, int *, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 100))(surface, destRect, surfaceDesc, 1, 0)) )
    {
      if ( (int)self[484] < 0 )
        signedPitch = -surfacePitch;
      else
        signedPitch = surfacePitch;
      self[484] = signedPitch;
      CAviDecompressor_BlitRows(self + 481, surfaceBits, *(char **)((char *)&blitScratch + 6));
      result = (*(int (__stdcall **)(int, char *))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 128))(surface, surfaceBits);
      if ( result )
      {
        if ( result != -2005532222
          || (result = (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 108))(surface)) == 0
          && (result = (*(int (__stdcall **)(int, char *))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 128))(surface, surfaceBits)) != 0 )
        {
          ExcString_Ctor();
          ExcString_Ctor();
          v46 = v38;
          return CRT_ThrowExcStringException();
        }
      }
    }
    else
    {
      ExcString_Ctor();
      ExcString_Ctor();
      v47 = v37;
      return CRT_ThrowExcStringException();
    }
  }
  else
  {
    dcResult = (*(int (__stdcall **)(int, char *))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 68))(surface, (char *)&blitScratch + 2);
    if ( !dcResult
      || dcResult == -2005532222
      && ((*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 108))(surface)
       || !(*(int (__stdcall **)(int, char *))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 68))(surface, (char *)&blitScratch + 2)) )
    {
      if ( *(_DWORD *)((char *)self + 415) )
        bitmapInfo = (const BITMAPINFO *)((char *)self + 423);
      else
        bitmapInfo = *(const BITMAPINFO **)((char *)self + 151);
      StretchDIBits(
        *(HDC *)((char *)&blitScratch + 2),
        *destRect,
        destRect[1],
        destRect[2] - *destRect,
        destRect[3] - destRect[1],
        0,
        0,
        *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)self + 151) + 4),
        abs32(*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)self + 151) + 8)),
        *(const void **)((char *)&blitScratch + 6),
        bitmapInfo,
        0,
        0xCC0020u);
      result = (*(int (__stdcall **)(int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 104))(surface, *(_DWORD *)((char *)&blitScratch + 2));
      if ( result )
      {
        if ( result != -2005532222
          || (result = (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 108))(surface)) == 0
          && (result = (*(int (__stdcall **)(int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 104))(surface, *(_DWORD *)((char *)&blitScratch + 2))) != 0 )
        {
          ExcString_Ctor();
          ExcString_Ctor();
          v44 = g_AviException_VTable;
          return CRT_ThrowExcStringException();
        }
      }
    }
    else
    {
      ExcString_Ctor();
      ExcString_Ctor();
      v45 = g_AviException_VTable;
      return CRT_ThrowExcStringException();
    }
  }
  return result;
}
// 466AD0: inconsistent variable size for '^460.8'
// 46692A: inconsistent variable size for '^460.8'
// 466885: inconsistent variable size for '^460.8'
// 510374: using guessed type int (*off_510374[2])();

//----- (00466BE0) --------------------------------------------------------
bool  AviPlayer_UpdateTargetFrameFromClock(int self)
{
  DWORD Time; // eax
  double elapsedScaled; // st7
  double targetFrame; // st7
  __int64 v6; // [esp+8h] [ebp-18h]

  Time = timeGetTime();
  v6 = *(unsigned int *)(uintptr_t)(self + 35);
  elapsedScaled = ((double)Time - (double)*(int *)(uintptr_t)(self + 2187)) * (double)v6;
  LODWORD(v6) = *(_DWORD *)(uintptr_t)(self + 31);
  targetFrame = elapsedScaled / ((double)v6 * g_AviPlayer_MillisecondsPerSecond);
  _CHP(Time, 0);
  *(_DWORD *)(uintptr_t)(self + 2183) = (int)targetFrame;
  return *(_DWORD *)(uintptr_t)(self + 43) > *(_DWORD *)(uintptr_t)(self + 2183);
}
// 501370: using guessed type float flt_501370;

//----- (00466C60) --------------------------------------------------------
char  AviPlayer_CatchUpToTargetFrame(int self)
{
  int frameQueue; // ecx
  HANDLE *v3; // edx
  int frameDataPtr; // eax
  unsigned __int8 flipState; // dl
  _DWORD *codecPtr; // ecx
  int decodedWidth; // ebx
  int videoHeight; // edx
  int v9; // ecx
  int v10; // eax
  int imageBytesSw; // esi
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int bitmapInfoHeaderSw; // eax
  int *drawContextSw; // ecx
  int busyGuard; // ebx
  int backSurface; // esi
  int lockResult; // eax
  int pitchPixels; // ebx
  int videoHeightBack; // ecx
  int v25; // edx
  int v26; // eax
  int imageBytes; // ebx
  int v28; // edx
  int v29; // eax
  int v30; // ecx
  int v31; // edx
  int bitmapInfoHeaderBack; // eax
  int *drawContextBack; // edx
  int unlockResult; // eax
  int overlaySurface; // esi
  int lockResultOvl; // eax
  int pitchPixelsOvl; // ebx
  int videoHeightOvl; // ecx
  int v39; // edx
  int v40; // eax
  int imageBytesOvl; // ebx
  int v42; // edx
  int v43; // eax
  int v44; // ecx
  int v45; // edx
  int bitmapInfoHeaderOvl; // eax
  int *drawContextOvl; // edx
  int unlockResultOvl; // eax
  int v49; // edx
  HANDLE *v50; // ecx
  int frameData; // eax
  int v52; // [esp-4h] [ebp-7A0h]
  int v53; // [esp-4h] [ebp-7A0h]
  int v54; // [esp-4h] [ebp-7A0h]
  int v55; // [esp+0h] [ebp-79Ch]
  int v56; // [esp+4h] [ebp-798h]
  int v57; // [esp+8h] [ebp-794h]
  int v58; // [esp+Ch] [ebp-790h]
  int v59; // [esp+10h] [ebp-78Ch]
  int v60; // [esp+14h] [ebp-788h]
  int v61; // [esp+18h] [ebp-784h]
  int v62; // [esp+1Ch] [ebp-780h]
  int v63; // [esp+20h] [ebp-77Ch]
  int v64; // [esp+24h] [ebp-778h]
  int v65; // [esp+28h] [ebp-774h]
  int v66; // [esp+2Ch] [ebp-770h]
  int v67; // [esp+30h] [ebp-76Ch]
  int v68; // [esp+34h] [ebp-768h]
  int v69; // [esp+38h] [ebp-764h]
  int v70; // [esp+3Ch] [ebp-760h]
  int v71; // [esp+40h] [ebp-75Ch]
  int v72; // [esp+44h] [ebp-758h]
  int v73; // [esp+48h] [ebp-754h]
  int v74; // [esp+4Ch] [ebp-750h]
  int v75; // [esp+50h] [ebp-74Ch]
  int v76; // [esp+54h] [ebp-748h]
  int v77; // [esp+58h] [ebp-744h]
  int v78; // [esp+5Ch] [ebp-740h]
  int v79; // [esp+60h] [ebp-73Ch]
  int v80; // [esp+64h] [ebp-738h]
  __int64 v81; // [esp+68h] [ebp-734h]
  _DWORD overlayDesc[9]; // [esp+82h] [ebp-71Ah] BYREF
  int overlayLockedBits; // [esp+A6h] [ebp-6F6h]
  _DWORD surfaceDesc[9]; // [esp+EEh] [ebp-6AEh] BYREF
  int lockedBits; // [esp+112h] [ebp-68Ah]
  int (**v86)(); // [esp+1BEh] [ebp-5DEh]
  int (**v87)(); // [esp+226h] [ebp-576h]
  int (**v88)(); // [esp+28Eh] [ebp-50Eh]
  int (**v89)(); // [esp+3C6h] [ebp-3D6h]
  int (**v90)(); // [esp+42Eh] [ebp-36Eh]
  int videoWidth; // [esp+7D2h] [ebp+36h]
  int lockedBitsSaved; // [esp+7DAh] [ebp+3Eh]
  int frameBits; // [esp+7DEh] [ebp+42h]
  int videoWidthOvl; // [esp+7E2h] [ebp+46h]
  int lockedBitsOvlSaved; // [esp+7EAh] [ebp+4Eh]
  int frameBitsOvl; // [esp+7EEh] [ebp+52h]
  int frameFlagsOvl; // [esp+7F2h] [ebp+56h]
  int pixelCountSw; // [esp+7F6h] [ebp+5Ah]
  int pixelCountBack; // [esp+7F6h] [ebp+5Ah]
  int pixelCountOvl; // [esp+7F6h] [ebp+5Ah]
  int frameFlags; // [esp+7FAh] [ebp+5Eh]
  int frameBitsSw; // [esp+7FEh] [ebp+62h]
  int busyGuardPtr; // [esp+802h] [ebp+66h]
  int decodeBuffer; // [esp+806h] [ebp+6Ah]
  int frameQueuePtr; // [esp+80Eh] [ebp+72h]
  int frameFlagsSw; // [esp+81Ah] [ebp+7Eh]

  if ( *(_DWORD *)(uintptr_t)(self + 2183) != *(_DWORD *)(uintptr_t)(self + 2021) )
  {
    frameQueuePtr = self + 203;
    if ( *(char *)(uintptr_t)(self + 2033) <= 0 )
    {
      busyGuardPtr = self + 1985;
      ++*(_DWORD *)(uintptr_t)(self + 1985);
      EnterCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 1989));
      if ( *(_DWORD *)(uintptr_t)(self + 2034) )
      {
        v49 = frameQueuePtr;
        do
        {
          if ( *(int *)(uintptr_t)(self + 2034) > 0 )
          {
            AviPlayer_IncrementFramesRenderedCount(v49);
            AviPlayer_PulseEventHandle(v50);
            --*(_DWORD *)(uintptr_t)(self + 2034);
          }
        }
        while ( *(_DWORD *)(uintptr_t)(self + 2034) );
      }
      frameData = AviPlayer_GetBufferedVideoFrame(self, *(_DWORD *)(uintptr_t)(self + 2183), (_DWORD *)(uintptr_t)(self + 2029), (_DWORD *)(uintptr_t)(self + 2021));
      *(_DWORD *)(uintptr_t)(self + 2025) = frameData;
      if ( frameData )
        ++*(_DWORD *)(uintptr_t)(self + 2034);
      busyGuard = busyGuardPtr;
    }
    else
    {
      if ( *(_DWORD *)(uintptr_t)(self + 2034) )
      {
        frameQueue = self + 203;
        do
        {
          if ( *(int *)(uintptr_t)(self + 2034) > 0 )
          {
            AviPlayer_IncrementFramesRenderedCount(frameQueue);
            AviPlayer_PulseEventHandle(v3);
            --*(_DWORD *)(uintptr_t)(self + 2034);
          }
        }
        while ( *(_DWORD *)(uintptr_t)(self + 2034) );
      }
      frameDataPtr = AviPlayer_GetBufferedVideoFrame(self, *(_DWORD *)(uintptr_t)(self + 2183), (_DWORD *)(uintptr_t)(self + 2029), (_DWORD *)(uintptr_t)(self + 2021));
      *(_DWORD *)(uintptr_t)(self + 2025) = frameDataPtr;
      if ( !frameDataPtr )
        return 0;
      ++*(_DWORD *)(uintptr_t)(self + 2034);
      ++*(_DWORD *)(uintptr_t)(self + 1985);
      EnterCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 1989));
      flipState = *(_BYTE *)(uintptr_t)(self + 2033);
      codecPtr = (_DWORD *)(uintptr_t)(self + 415);
      if ( flipState >= 2u )
      {
        if ( flipState <= 2u )
        {
          if ( *codecPtr )
          {
            backSurface = *(_DWORD *)(uintptr_t)(self + 2017);
            surfaceDesc[0] = 108;
            lockResult = (*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 100))(backSurface, 0, surfaceDesc, 33, 0);
            if ( !lockResult
              || lockResult == -2005532222
              && ((*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 108))(backSurface)
               || !(*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 100))(backSurface, 0, surfaceDesc, 33, 0)) )
            {
              CAviDecompressor_GetVideoFormat(self);
              videoWidth = *(_DWORD *)(uintptr_t)(CAviDecompressor_GetVideoFormat(self) + 4);
              lockedBitsSaved = lockedBits;
              frameBits = *(_DWORD *)(uintptr_t)(self + 2025);
              frameFlags = *(_DWORD *)(uintptr_t)(self + 2029);
              pitchPixels = surfaceDesc[4] / ((*(_DWORD *)(uintptr_t)(self + 2123) + 7) >> 3);
              *(_DWORD *)(uintptr_t)(AviPlayer_StreamBitmapInfoPtr(self + 415) + 4) = pitchPixels;
              pixelCountBack = videoHeightBack * pitchPixels;
              v26 = AviPlayer_StreamBitmapInfoPtr(v25);
              imageBytes = Mem_BitsToBytesCeil(*(unsigned __int16 *)(uintptr_t)(v26 + 14)) * pixelCountBack;
              v29 = AviPlayer_StreamBitmapInfoPtr(v28);
              v53 = v30;
              *(_DWORD *)(uintptr_t)(v29 + 20) = imageBytes;
              bitmapInfoHeaderBack = AviPlayer_StreamBitmapInfoPtr(v31);
              if ( AviPlayer_SendICDrawBegin(
                     *drawContextBack,
                     frameFlags,
                     drawContextBack[1],
                     frameBits,
                     0,
                     0,
                     *(_DWORD *)(uintptr_t)(drawContextBack[1] + 4),
                     *(_DWORD *)(uintptr_t)(drawContextBack[1] + 8),
                     bitmapInfoHeaderBack,
                     lockedBitsSaved,
                     0,
                     0,
                     videoWidth,
                     v53) < 0 )
              {
                ExcString_Ctor();
                AviException_CtorForDrawFailure();
                CRT_ThrowExcStringException();
              }
              unlockResult = (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 128))(backSurface, lockedBits);
              if ( unlockResult
                && (unlockResult != -2005532222
                 || !(*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 108))(backSurface)
                 && (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 128))(backSurface, lockedBits)) )
              {
                ExcString_Ctor();
                ExcString_Ctor();
                v87 = g_AviException_VTable;
                CRT_ThrowExcStringException();
              }
            }
            else
            {
              ExcString_Ctor();
              ExcString_Ctor();
              v89 = g_AviException_VTable;
              CRT_ThrowExcStringException();
            }
          }
          else
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)(uintptr_t)self,
              *(_DWORD *)(uintptr_t)(self + 2017),
              *(_DWORD *)(uintptr_t)(self + 2025),
              (int *)(uintptr_t)(self + 2095),
              v55,
              v56,
              v57,
              v58,
              v59,
              v60,
              v61,
              v62,
              v63,
              v64,
              v65,
              v66,
              v67,
              v68,
              v69,
              v70,
              v71,
              v72,
              v73,
              v74,
              v75,
              v76,
              v77,
              v78,
              v79,
              v80,
              v81);
          }
        }
        else if ( flipState == 3 )
        {
          if ( *codecPtr )
          {
            overlaySurface = *(_DWORD *)(uintptr_t)(self + 1964);
            overlayDesc[0] = 108;
            lockResultOvl = (*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 100))(overlaySurface, 0, overlayDesc, 33, 0);
            if ( !lockResultOvl
              || lockResultOvl == -2005532222
              && ((*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 108))(overlaySurface)
               || !(*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 100))(overlaySurface, 0, overlayDesc, 33, 0)) )
            {
              CAviDecompressor_GetVideoFormat(self);
              videoWidthOvl = *(_DWORD *)(uintptr_t)(CAviDecompressor_GetVideoFormat(self) + 4);
              lockedBitsOvlSaved = overlayLockedBits;
              frameBitsOvl = *(_DWORD *)(uintptr_t)(self + 2025);
              frameFlagsOvl = *(_DWORD *)(uintptr_t)(self + 2029);
              pitchPixelsOvl = overlayDesc[4] / ((*(_DWORD *)(uintptr_t)(self + 2123) + 7) >> 3);
              *(_DWORD *)(uintptr_t)(AviPlayer_StreamBitmapInfoPtr(self + 415) + 4) = pitchPixelsOvl;
              pixelCountOvl = videoHeightOvl * pitchPixelsOvl;
              v40 = AviPlayer_StreamBitmapInfoPtr(v39);
              imageBytesOvl = Mem_BitsToBytesCeil(*(unsigned __int16 *)(uintptr_t)(v40 + 14)) * pixelCountOvl;
              v43 = AviPlayer_StreamBitmapInfoPtr(v42);
              v54 = v44;
              *(_DWORD *)(uintptr_t)(v43 + 20) = imageBytesOvl;
              bitmapInfoHeaderOvl = AviPlayer_StreamBitmapInfoPtr(v45);
              if ( AviPlayer_SendICDrawBegin(
                     *drawContextOvl,
                     frameFlagsOvl,
                     drawContextOvl[1],
                     frameBitsOvl,
                     0,
                     0,
                     *(_DWORD *)(uintptr_t)(drawContextOvl[1] + 4),
                     *(_DWORD *)(uintptr_t)(drawContextOvl[1] + 8),
                     bitmapInfoHeaderOvl,
                     lockedBitsOvlSaved,
                     0,
                     0,
                     videoWidthOvl,
                     v54) < 0 )
              {
                ExcString_Ctor();
                AviException_CtorForDrawFailure();
                CRT_ThrowExcStringException();
              }
              unlockResultOvl = (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 128))(overlaySurface, overlayLockedBits);
              if ( unlockResultOvl
                && (unlockResultOvl != -2005532222
                 || !(*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 108))(overlaySurface)
                 && (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 128))(overlaySurface, overlayLockedBits)) )
              {
                ExcString_Ctor();
                ExcString_Ctor();
                v90 = g_AviException_VTable;
                CRT_ThrowExcStringException();
              }
            }
            else
            {
              ExcString_Ctor();
              ExcString_Ctor();
              v86 = g_AviException_VTable;
              CRT_ThrowExcStringException();
            }
          }
          else
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)(uintptr_t)self,
              *(_DWORD *)(uintptr_t)(self + 1964),
              *(_DWORD *)(uintptr_t)(self + 2025),
              (int *)(uintptr_t)(self + 2095),
              v55,
              v56,
              v57,
              v58,
              v59,
              v60,
              v61,
              v62,
              v63,
              v64,
              v65,
              v66,
              v67,
              v68,
              v69,
              v70,
              v71,
              v72,
              v73,
              v74,
              v75,
              v76,
              v77,
              v78,
              v79,
              v80,
              v81);
          }
        }
      }
      else if ( flipState == 1 )
      {
        decodeBuffer = *(_DWORD *)(uintptr_t)(self + 2179);
        frameBitsSw = *(_DWORD *)(uintptr_t)(self + 2025);
        frameFlagsSw = *(_DWORD *)(uintptr_t)(self + 2029);
        if ( *(_BYTE *)(uintptr_t)(self + 1923) )
        {
          decodedWidth = *(_DWORD *)(uintptr_t)(self + 427);
          *(_DWORD *)(uintptr_t)(AviPlayer_StreamBitmapInfoPtr(self + 415) + 4) = decodedWidth;
          pixelCountSw = decodedWidth * videoHeight;
          v10 = AviPlayer_StreamBitmapInfoPtr(v9);
          imageBytesSw = Mem_BitsToBytesCeil(*(unsigned __int16 *)(uintptr_t)(v10 + 14)) * pixelCountSw;
          v13 = AviPlayer_StreamBitmapInfoPtr(v12);
          v52 = v14;
          *(_DWORD *)(uintptr_t)(v13 + 20) = imageBytesSw;
          bitmapInfoHeaderSw = AviPlayer_StreamBitmapInfoPtr(v15);
          if ( AviPlayer_SendICDrawBegin(
                 *drawContextSw,
                 frameFlagsSw,
                 drawContextSw[1],
                 frameBitsSw,
                 0,
                 0,
                 *(_DWORD *)(uintptr_t)(drawContextSw[1] + 4),
                 *(_DWORD *)(uintptr_t)(drawContextSw[1] + 8),
                 bitmapInfoHeaderSw,
                 decodeBuffer,
                 0,
                 0,
                 decodedWidth,
                 v52) < 0 )
          {
            ExcString_Ctor();
            AviException_CtorForDrawFailure();
            CRT_ThrowExcStringException();
          }
        }
        else if ( ICDecompress(
                    *(_DWORD *)(uintptr_t)(self + 415),
                    *(_DWORD *)(uintptr_t)(self + 2029),
                    *(_DWORD *)(uintptr_t)(self + 419),
                    frameBitsSw,
                    self + 423,
                    decodeBuffer) < 0 )
        {
          ExcString_Ctor();
          ExcString_Ctor();
          v88 = g_AviException_VTable;
          CRT_ThrowExcStringException();
        }
      }
      if ( *(int *)(uintptr_t)(self + 2034) > 0 )
      {
        ++*(_DWORD *)(uintptr_t)(self + 207);
        PulseEvent(*(HANDLE *)(uintptr_t)(self + 171));
        --*(_DWORD *)(uintptr_t)(self + 2034);
      }
      busyGuard = self + 1985;
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(busyGuard + 4));
    --*(_DWORD *)(uintptr_t)busyGuard;
    SetEvent(*(HANDLE *)(uintptr_t)(self + 2196));
  }
  return 1;
}
// 466CED: variable 'v2' is possibly undefined
// 466CF4: variable 'v3' is possibly undefined
// 466DC6: variable 'v8' is possibly undefined
// 466DCB: variable 'v9' is possibly undefined
// 466DE6: variable 'v12' is possibly undefined
// 466DEB: variable 'v14' is possibly undefined
// 466DFA: variable 'v15' is possibly undefined
// 466E1A: variable 'v17' is possibly undefined
// 466FE6: variable 'v24' is possibly undefined
// 466FEB: variable 'v25' is possibly undefined
// 467006: variable 'v28' is possibly undefined
// 46700B: variable 'v30' is possibly undefined
// 46701D: variable 'v31' is possibly undefined
// 46703D: variable 'v33' is possibly undefined
// 467174: variable 'v55' is possibly undefined
// 467174: variable 'v56' is possibly undefined
// 467174: variable 'v57' is possibly undefined
// 467174: variable 'v58' is possibly undefined
// 467174: variable 'v59' is possibly undefined
// 467174: variable 'v60' is possibly undefined
// 467174: variable 'v61' is possibly undefined
// 467174: variable 'v62' is possibly undefined
// 467174: variable 'v63' is possibly undefined
// 467174: variable 'v64' is possibly undefined
// 467174: variable 'v65' is possibly undefined
// 467174: variable 'v66' is possibly undefined
// 467174: variable 'v67' is possibly undefined
// 467174: variable 'v68' is possibly undefined
// 467174: variable 'v69' is possibly undefined
// 467174: variable 'v70' is possibly undefined
// 467174: variable 'v71' is possibly undefined
// 467174: variable 'v72' is possibly undefined
// 467174: variable 'v73' is possibly undefined
// 467174: variable 'v74' is possibly undefined
// 467174: variable 'v75' is possibly undefined
// 467174: variable 'v76' is possibly undefined
// 467174: variable 'v77' is possibly undefined
// 467174: variable 'v78' is possibly undefined
// 467174: variable 'v79' is possibly undefined
// 467174: variable 'v80' is possibly undefined
// 467174: variable 'v81' is possibly undefined
// 46723B: variable 'v38' is possibly undefined
// 467240: variable 'v39' is possibly undefined
// 46725B: variable 'v42' is possibly undefined
// 467260: variable 'v44' is possibly undefined
// 467272: variable 'v45' is possibly undefined
// 467292: variable 'v47' is possibly undefined
// 467431: variable 'v49' is possibly undefined
// 467438: variable 'v50' is possibly undefined
// 4E97F8: using guessed type int __cdecl ICDecompress(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);
// 510374: using guessed type int (*off_510374[2])();
