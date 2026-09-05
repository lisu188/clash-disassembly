/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004637B0) --------------------------------------------------------
int * CAviDecompressor_ConstructEmpty(int *instanceOut, DWORD allocContext)
{
  int instance; // eax

  instance = Mem_Alloc(2236, (int)(intptr_t)&g_CAviDecompressor_AllocTypeTag, 0, allocContext);
  if ( instance )
    instance = CAviDecompressor_InitCommon(instance);
  *instanceOut = instance;
  return instanceOut;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00463B10) --------------------------------------------------------
int  CAviDecompressor_dtor(_DWORD *selfPtr)
{
  int v1; // ecx

  CAviDecompressor_Done(selfPtr);
  return v1;
}
// 463B18: variable 'v1' is possibly undefined

//----- (00463B20) --------------------------------------------------------
int * CAviDecompressor_ConstructAndInitCallbacks(
        int *selfOut,
        int (__stdcall ***ddSurface)(_DWORD, void *, _DWORD *),
        int fileName,
        int openFlags)
{
  int instance; // eax

  *selfOut = 0;
  instance = Mem_Alloc(2236, (int)(intptr_t)&stru_50F60C, 0, (DWORD)(intptr_t)ddSurface);
  if ( instance )
    instance = CAviDecompressor_InitCommon(instance);
  *selfOut = instance;
  if ( instance )
    CAviDecompressor_Init(selfOut, ddSurface, fileName, openFlags);
  return selfOut;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00463E90) --------------------------------------------------------
void  CAviDecompressor_Init(
        int *selfPtr,
        int (__stdcall ***ddSurface)(_DWORD, void *, _DWORD *),
        int fileName,
        int openFlags)
{
  int instance; // esi
  _DWORD surface2Out[4]; // [esp+20h] [ebp-10h] BYREF

  instance = *selfPtr;
  surface2Out[0] = 0;
  if ( !(**ddSurface)(ddSurface, &g_AviQueryInterfaceIid, surface2Out) )
  {
    *(_DWORD *)(uintptr_t)(instance + 1952) = ddSurface;
    CAviDecompressor_ApplyDecoderFormatParams(openFlags, fileName);
  }
}
// 4697E0: using guessed type int __fastcall sub_4697E0(_DWORD, _DWORD);

//----- (00463EA0) --------------------------------------------------------
int * CAviDecompressor_ConstructAndInitSource(int *selfOut, DWORD allocContext, int fileName, int openFlags)
{
  int instance; // eax

  *selfOut = 0;
  instance = Mem_Alloc(2236, (int)(intptr_t)&stru_50F6A0, 0, allocContext);
  if ( instance )
    instance = CAviDecompressor_InitCommon(instance);
  *selfOut = instance;
  if ( instance )
    CAviDecompressor_InitSource(openFlags, fileName);
  return selfOut;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00464210) --------------------------------------------------------
void __fastcall CAviDecompressor_InitSource(int openFlags, int fileName)
{
  CAviDecompressor_ApplyDecoderFormatParams(openFlags, fileName);
}
// 4697E0: using guessed type int __fastcall sub_4697E0(_DWORD, _DWORD);

//----- (00464220) --------------------------------------------------------
void  CAviDecompressor_Done(_DWORD *playerHandle)
{
  _DWORD *handlePtr; // ecx
  int instance; // eax

  handlePtr = playerHandle;
  instance = *playerHandle;
  if ( instance )
    (**(void (__fastcall ***)(int, int))(uintptr_t)(instance + 2232))(instance, 2);
  *handlePtr = 0;
}
// 464229: variable 'v1' is possibly undefined

//----- (00464250) --------------------------------------------------------
int  CAviDecompressor_Frames(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 43);
}

//----- (00464260) --------------------------------------------------------
int  CAviDecompressor_Fps(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 35) / *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 31);
}

//----- (00464270) --------------------------------------------------------
void  CAviDecompressor_Start(int *playerHandle)
{
  CAviDecompressor_BeginPlayback(*playerHandle);
}

//----- (00464280) --------------------------------------------------------
void  CAviDecompressor_Stop(int *playerHandle)
{
  CAviDecompressor_RequestRenderStop(*playerHandle);
}

//----- (00464290) --------------------------------------------------------
BOOL  CAviDecompressor_IsPlaying(int playerHandle)
{
  return *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 2191) != 0;
}

//----- (004642B0) --------------------------------------------------------
int  CAviDecompressor_Initialized(_DWORD *playerHandle)
{
  _DWORD *instance; // eax
  int result; // eax
  int v3; // ebx
  _DWORD *blitState; // eax

  instance = (_DWORD *)(uintptr_t)*playerHandle;
  if ( *(_DWORD *)((char *)instance + 7) )
    LOBYTE(result) = *(_DWORD *)((char *)instance + 415) || (v3 = instance[486], blitState = instance + 481, v3) || blitState[4];
  else
    LOBYTE(result) = 0;
  return (unsigned __int8)result;
}

//----- (004642F0) --------------------------------------------------------
void  CAviDecompressor_WaitForNextFrame(int *playerHandle)
{
  int instance; // eax

  instance = *playerHandle;
  if ( *(_BYTE *)(uintptr_t)(instance + 2191) )
    WaitForSingleObject(*(HANDLE *)(uintptr_t)(instance + 2196), 0x1F4u);
}

//----- (00464320) --------------------------------------------------------
int  CAviDecompressor_Palette(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 1948);
}

//----- (00464330) --------------------------------------------------------
int  CAviDecompressor_Header(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 151);
}

//----- (00464340) --------------------------------------------------------
int  CAviDecompressor_PixelSize(int *playerHandle)
{
  return (*(unsigned __int16 *)(uintptr_t)(CAviDecompressor_GetVideoFormat(*playerHandle) + 14) + 7) >> 3;
}

//----- (00464360) --------------------------------------------------------
int  CAviDecompressor_BPP(int playerHandle)
{
  return *(unsigned __int16 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 151) + 14);
}

//----- (00464380) --------------------------------------------------------
int  CAviDecompressor_Width(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 151) + 4);
}

//----- (00464390) --------------------------------------------------------
int  CAviDecompressor_Height(int playerHandle)
{
  __int64 biHeight; // rax

  biHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 151) + 8);
  return (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
}

//----- (004643B0) --------------------------------------------------------
int  CAviDecompressor_DecodedFrame(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 2021);
}

//----- (004643C0) --------------------------------------------------------
int  CAviDecompressor_SetBackground(int *playerHandle, _DWORD *bgRect, int ddObject)
{
  int result; // eax

  result = *playerHandle;
  *(_DWORD *)(uintptr_t)(result + 2155) = *bgRect;
  *(_DWORD *)(uintptr_t)(result + 2159) = bgRect[1];
  *(_DWORD *)(uintptr_t)(result + 2163) = bgRect[2];
  *(_DWORD *)(uintptr_t)(result + 2167) = bgRect[3];
  *(_DWORD *)(uintptr_t)(result + 2151) = ddObject;
  return result;
}

//----- (004643E0) --------------------------------------------------------
void  CAviDecompressor_InitClipRect(_DWORD *playerHandle, _DWORD *clipRect)
{
  _DWORD *clipDest; // edi

  clipDest = (_DWORD *)(uintptr_t)(*playerHandle + 1969);
  *clipDest++ = *clipRect;
  *clipDest++ = clipRect[1];
  *clipDest = clipRect[2];
  clipDest[1] = clipRect[3];
}

//----- (00464400) --------------------------------------------------------
void  CAviDecompressor_UpdatePos(int *playerHandle, LONG x, int a3, LONG y)
{
  int instance; // eax
  int v5; // ecx
  int playerInstance; // ebx
  int destWidthScaled; // esi
  int v8; // ecx
  int stretchRatio; // eax
  int v10; // ecx
  int showFlags; // eax
  int overlayFlags; // edi
  int updateResult; // eax
  __int64 biHeight; // rax
  int overlaySurface; // ebp
  int hideResult; // eax
  RECT frameRect; // [esp+170h] [ebp-30h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList CLASH95_UNUSED; // [esp+180h] [ebp-20h]
  tagRECT *v19 CLASH95_UNUSED; // [esp+184h] [ebp-1Ch]
  void *v20 CLASH95_UNUSED; // [esp+188h] [ebp-18h]
  int v21 CLASH95_UNUSED; // [esp+18Ch] [ebp-14h]
  int v22 CLASH95_UNUSED; // [esp+19Ch] [ebp-4h]

  instance = *playerHandle;
  v22 = a3;
  v5 = instance;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v19 = &j____wcpp_4_fs_handler_rtn_;
  v20 = &g_AviUpdatePos_EHFrame;
  v21 = 0;
  if ( !*(_BYTE *)(uintptr_t)(instance + 2062) )
  {
    frameRect = *(RECT *)g_AviFrameRectInitScratch;
    frameRect.left = x;
    frameRect.top = y;
    frameRect.right = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 151) + 4) + x;
    biHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(instance + 151) + 8);
    frameRect.bottom = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight) + y;
    AviPlayer_RenderFrame(v5, &frameRect);
  }
  playerInstance = v5;
  if ( *(_BYTE *)(uintptr_t)(v5 + 1968) && *(_DWORD *)(uintptr_t)(v5 + 1964) )
  {
    destWidthScaled = 1000 * AviPlayer_SpanDelta(v5, (_DWORD *)(uintptr_t)(v5 + 2063));
    stretchRatio = destWidthScaled / AviPlayer_SpanDelta(v8, (_DWORD *)(uintptr_t)(v8 + 2079));
    if ( stretchRatio < *(_DWORD *)(uintptr_t)(v10 + 2143) || stretchRatio > *(_DWORD *)(uintptr_t)(v10 + 2147) )
    {
      if ( *(_BYTE *)(uintptr_t)(playerInstance + 1968) )
      {
        overlaySurface = *(_DWORD *)(uintptr_t)(playerInstance + 1964);
        if ( overlaySurface )
        {
          hideResult = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 132))(
                  overlaySurface,
                  playerInstance + 2095,
                  *(_DWORD *)(uintptr_t)(playerInstance + 1956),
                  playerInstance + 2063,
                  512,
                  0);
          if ( hideResult )
          {
            if ( hideResult != -2005532222
              || ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 96))(*(_DWORD *)(uintptr_t)(playerInstance + 1964)) != -2005532222
               || !(*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 108))(*(_DWORD *)(uintptr_t)(playerInstance + 1964)))
              && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1956) + 96))(*(_DWORD *)(uintptr_t)(playerInstance + 1956)) != -2005532222
               || !(*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1956) + 108))(*(_DWORD *)(uintptr_t)(playerInstance + 1956)))
              && (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 132))(
                   *(_DWORD *)(uintptr_t)(playerInstance + 1964),
                   playerInstance + 2095,
                   *(_DWORD *)(uintptr_t)(playerInstance + 1956),
                   playerInstance + 2063,
                   512,
                   0) )
            {
              ExcString_Ctor();
              AviException_CtorForDrawFailure();
              CRT_ThrowExcStringException();
            }
          }
        }
      }
    }
    else
    {
      showFlags = 0x4000;
      if ( *(_DWORD *)(uintptr_t)(v10 + 2171) )
        showFlags = 20480;
      overlayFlags = showFlags;
      updateResult = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 132))(
              *(_DWORD *)(uintptr_t)(playerInstance + 1964),
              playerInstance + 2095,
              *(_DWORD *)(uintptr_t)(playerInstance + 1956),
              playerInstance + 2063,
              showFlags,
              0);
      if ( updateResult
        && (updateResult != -2005532222
         || ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 96))(*(_DWORD *)(uintptr_t)(playerInstance + 1964)) != -2005532222
          || !(*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 108))(*(_DWORD *)(uintptr_t)(playerInstance + 1964)))
         && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1956) + 96))(*(_DWORD *)(uintptr_t)(playerInstance + 1956)) != -2005532222
          || !(*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1956) + 108))(*(_DWORD *)(uintptr_t)(playerInstance + 1956)))
         && (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(playerInstance + 1964) + 132))(
              *(_DWORD *)(uintptr_t)(playerInstance + 1964),
              playerInstance + 2095,
              *(_DWORD *)(uintptr_t)(playerInstance + 1956),
              playerInstance + 2063,
              overlayFlags,
              0)) )
      {
        ExcString_Ctor();
        v21 = 1;
        ExcString_Ctor();
        v21 = 0;
        CRT_ThrowExcStringException();
      }
    }
  }
}
// 4685A0: conditional instruction was optimized away because dl.1!=0
// 4685A8: conditional instruction was optimized away because eax.4!=0
// 468586: variable 'v5' is possibly undefined
// 4685E9: variable 'v8' is possibly undefined
// 4685F9: variable 'v10' is possibly undefined

//----- (00464410) --------------------------------------------------------
void  CAviDecompressor_UpdateRect(int *playerHandle, const RECT *destRect)
{
  CAviDecompressor_PresentFrameForRect(*playerHandle, destRect);
}

//----- (00464420) --------------------------------------------------------
void  CAviDecompressor_Blit(int *playerHandle)
{
  int instance; // eax

  instance = *playerHandle;
  if ( *(_BYTE *)(uintptr_t)(instance + 2191) )
    CAviDecompressor_PresentFrameIfStale(instance, 0);
}

//----- (00464440) --------------------------------------------------------
void  CAviDecompressor_BlitTo(int *playerHandle, LONG x, int a3, LONG y)
{
  int instance; // ecx
  int videoFormat; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  RECT destRect; // [esp+0h] [ebp-14h] BYREF
  int v10 CLASH95_UNUSED; // [esp+10h] [ebp-4h]

  v10 = a3;
  instance = *playerHandle;
  if ( *(_BYTE *)(uintptr_t)(*playerHandle + 2191) )
  {
    destRect = *(RECT *)g_AviDecompressorBlitRectTemplate;
    destRect.left = x;
    destRect.top = y;
    videoFormat = CAviDecompressor_GetVideoFormat(instance);
    destRect.right = *(_DWORD *)(uintptr_t)(videoFormat + 4) + v6;
    destRect.bottom = abs32(*(_DWORD *)(uintptr_t)(CAviDecompressor_GetVideoFormat(v7) + 8)) + y;
    CAviDecompressor_PresentFrameIfStale(v8, &destRect);
  }
}
// 464479: variable 'v6' is possibly undefined
// 46447D: variable 'v7' is possibly undefined
// 464496: variable 'v8' is possibly undefined

//----- (004644B0) --------------------------------------------------------
void  CAviDecompressor_StretchTo(int *playerHandle, const RECT *destRect)
{
  int instance; // eax

  instance = *playerHandle;
  if ( *(_BYTE *)(uintptr_t)(instance + 2191) )
    CAviDecompressor_PresentFrameIfStale(instance, destRect);
}

//----- (004644C0) --------------------------------------------------------
void  CAviDecompressor_GetRect(_DWORD *playerHandle, _DWORD *rectOut)
{
  _DWORD *srcRect; // esi

  srcRect = (_DWORD *)(uintptr_t)(*playerHandle + 2063);
  *rectOut = *srcRect++;
  rectOut[1] = *srcRect++;
  rectOut[2] = *srcRect;
  rectOut[3] = srcRect[1];
}

//----- (004644E0) --------------------------------------------------------
void  CAviDecompressor_InitColorKeys(int *playerHandle, int colorKeyLow, int colorKeyHigh)
{
  int instance; // eax

  instance = *playerHandle;
  *(_DWORD *)(uintptr_t)(instance + 2171) = 8;
  *(_DWORD *)(uintptr_t)(instance + 2042) = colorKeyLow;
  *(_DWORD *)(uintptr_t)(instance + 2046) = colorKeyHigh;
}

//----- (00464500) --------------------------------------------------------
void  CAviDecompressor_InitPos(int *playerHandle, int x, int y)
{
  int instance; // eax

  instance = *playerHandle;
  *(_DWORD *)(uintptr_t)(instance + 2071) = 0;
  *(_DWORD *)(uintptr_t)(instance + 2075) = 0;
  *(_BYTE *)(uintptr_t)(instance + 2062) = 1;
  *(_DWORD *)(uintptr_t)(instance + 2063) = x;
  *(_DWORD *)(uintptr_t)(instance + 2067) = y;
}

//----- (00464530) --------------------------------------------------------
void  CAviDecompressor_InitRect(int *playerHandle, _DWORD *rect)
{
  int instance; // eax

  instance = *playerHandle;
  *(_DWORD *)(uintptr_t)(instance + 2063) = *rect;
  *(_DWORD *)(uintptr_t)(instance + 2067) = rect[1];
  *(_DWORD *)(uintptr_t)(instance + 2071) = rect[2];
  *(_DWORD *)(uintptr_t)(instance + 2075) = rect[3];
  *(_BYTE *)(uintptr_t)(instance + 2062) = 1;
}

//----- (00464550) --------------------------------------------------------
void  CAviDecompressor_InitOverlays(int playerHandle, char enabled)
{
  *(_BYTE *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 2050) = enabled != 0;
}

//----- (00464570) --------------------------------------------------------
unsigned int  CAviDecompressor_TimeMs(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 43)
       * ((unsigned int)(1000 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 31))
        / *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 35));
}

//----- (004645C0) --------------------------------------------------------
int  CAviDecompressor_SumSleepTime(int playerHandle)
{
  return *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)playerHandle + 2038);
}

//----- (004645D0) --------------------------------------------------------
void __stdcall PlayAvi(char *fileName, IDirectDrawSurface *ddSurface, int x, int y, int (*continueCallback)(void), int openFlags)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  char *v9; // [esp+4h] [ebp-24h]
  IDirectDrawSurface *v10; // [esp+8h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-1Ch]
  int aviHandle[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v9 = (char *)&j____wcpp_4_fs_handler_rtn_;
  v10 = &stru_50F734;
  CAviDecompressor_ConstructEmpty(aviHandle, 0);
  v11 = 1;
  CAviDecompressor_InitPos(aviHandle, x, y);
  CAviDecompressor_Init(aviHandle, ddSurface, (int)(intptr_t)fileName, openFlags);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)(intptr_t)aviHandle)
         && (!continueCallback
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, char *, IDirectDrawSurface *, int))continueCallback)(
               ExceptionList,
               v9,
               v10,
               v11)) )
    {
      CAviDecompressor_Blit(aviHandle);
      CAviDecompressor_WaitForNextFrame(aviHandle);
    }
  }
  CAviDecompressor_dtor(aviHandle);
}
// 464699: variable 'ExceptionList' is possibly undefined
// 464699: variable 'v9' is possibly undefined
// 464699: variable 'v10' is possibly undefined
// 464699: variable 'v11' is possibly undefined

//----- (004646B0) --------------------------------------------------------
void __stdcall PlayAviStretch(char *fileName, IDirectDrawSurface *ddSurface, tagRECT *destRect, int (*continueCallback)(void), int openFlags)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  tagRECT *v8; // [esp+4h] [ebp-24h]
  IDirectDrawSurface *v9; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]
  int aviHandle[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v8 = &j____wcpp_4_fs_handler_rtn_;
  v9 = &stru_50F740;
  CAviDecompressor_ConstructEmpty(aviHandle, 0);
  v10 = 1;
  CAviDecompressor_InitRect(aviHandle, destRect);
  CAviDecompressor_Init(aviHandle, ddSurface, (int)(intptr_t)fileName, openFlags);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)(intptr_t)aviHandle)
         && (!continueCallback
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, IDirectDrawSurface *, int))continueCallback)(
               ExceptionList,
               v8,
               v9,
               v10)) )
    {
      CAviDecompressor_Blit(aviHandle);
      CAviDecompressor_WaitForNextFrame(aviHandle);
    }
  }
  CAviDecompressor_dtor(aviHandle);
}
// 464774: variable 'ExceptionList' is possibly undefined
// 464774: variable 'v8' is possibly undefined
// 464774: variable 'v9' is possibly undefined
// 464774: variable 'v10' is possibly undefined

//----- (00464780) --------------------------------------------------------
void __stdcall PlayAviSurface2(char *fileName, IDirectDrawSurface2 *ddSurface2 CLASH95_UNUSED, int x, int y, int (*continueCallback)(void), int openFlags)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  char *v9; // [esp+4h] [ebp-24h]
  IDirectDrawSurface2 *v10; // [esp+8h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-1Ch]
  int aviHandle[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v9 = (char *)&j____wcpp_4_fs_handler_rtn_;
  v10 = &stru_50F74C;
  CAviDecompressor_ConstructEmpty(aviHandle, 0);
  v11 = 1;
  CAviDecompressor_InitPos(aviHandle, x, y);
  CAviDecompressor_InitSource(openFlags, (int)(intptr_t)fileName);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)(intptr_t)aviHandle)
         && (!continueCallback
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, char *, IDirectDrawSurface2 *, int))continueCallback)(
               ExceptionList,
               v9,
               v10,
               v11)) )
    {
      CAviDecompressor_Blit(aviHandle);
      CAviDecompressor_WaitForNextFrame(aviHandle);
    }
  }
  CAviDecompressor_dtor(aviHandle);
}
// 464849: variable 'ExceptionList' is possibly undefined
// 464849: variable 'v9' is possibly undefined
// 464849: variable 'v10' is possibly undefined
// 464849: variable 'v11' is possibly undefined

//----- (00464860) --------------------------------------------------------
void __stdcall PlayAviStretchSurface2(char *fileName, IDirectDrawSurface2 *ddSurface2 CLASH95_UNUSED, tagRECT *destRect, int (*continueCallback)(void), int openFlags)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  tagRECT *v8; // [esp+4h] [ebp-24h]
  IDirectDrawSurface2 *v9; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]
  int aviHandle[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v8 = &j____wcpp_4_fs_handler_rtn_;
  v9 = &stru_50F758;
  CAviDecompressor_ConstructEmpty(aviHandle, 0);
  v10 = 1;
  CAviDecompressor_InitRect(aviHandle, destRect);
  CAviDecompressor_InitSource(openFlags, (int)(intptr_t)fileName);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)(intptr_t)aviHandle)
         && (!continueCallback
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, IDirectDrawSurface2 *, int))continueCallback)(
               ExceptionList,
               v8,
               v9,
               v10)) )
    {
      CAviDecompressor_Blit(aviHandle);
      CAviDecompressor_WaitForNextFrame(aviHandle);
    }
  }
  CAviDecompressor_dtor(aviHandle);
}
// 464924: variable 'ExceptionList' is possibly undefined
// 464924: variable 'v8' is possibly undefined
// 464924: variable 'v9' is possibly undefined
// 464924: variable 'v10' is possibly undefined

//----- (00464930) --------------------------------------------------------
int  CAviDecompressor_InitThreadGuard(int guard)
{
  *(_DWORD *)(uintptr_t)guard = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(guard + 4));
  return guard;
}

//----- (00464950) --------------------------------------------------------
int  CAviDecompressor_DoneThreadGuard(int guard)
{
  DeleteCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(guard + 4));
  return guard;
}

//----- (00464970) --------------------------------------------------------
HANDLE * CAviDecompressor_ConstructEventHandle(HANDLE *eventOut, bool manualReset, bool initialState)
{
  *eventOut = CreateEventA(0, manualReset, initialState, 0);
  return eventOut;
}

//----- (00464990) --------------------------------------------------------
HANDLE * CAviDecompressor_DestroyEventHandle(HANDLE *eventHandlePtr)
{
  CloseHandle(*eventHandlePtr);
  return eventHandlePtr;
}

//----- (004649B0) --------------------------------------------------------
int CAviDecompressor_FreeMemberA(void)
{
  int v2; // ecx

  j_j__nfree_();
  return v2;
}
// 4649BA: variable 'v2' is possibly undefined

//----- (004649C0) --------------------------------------------------------
int CAviDecompressor_FreeMemberB(void)
{
  int v2; // ecx

  j_j__nfree_();
  return v2;
}
// 4649CA: variable 'v2' is possibly undefined

//----- (004649D0) --------------------------------------------------------
int  CAviDecompressor_ConstructSourceInterface(int self)
{
  int fieldPtr; // ebx
  int basePtr; // edx
  HANDLE *eventPtr; // ebx

  *(_BYTE *)(uintptr_t)self = 0;
  *(_BYTE *)(uintptr_t)(self + 1) = 1;
  *(_DWORD *)(uintptr_t)(self + 3) = 0;
  *(_DWORD *)(uintptr_t)(self + 7) = 0;
  *(_DWORD *)(uintptr_t)(self + 151) = 0;
  *(_DWORD *)(uintptr_t)(self + 163) = 0;
  fieldPtr = self + 171;
  *(_DWORD *)(uintptr_t)(self + 167) = CreateEventA(0, 0, 0, 0);
  fieldPtr += 4;
  *(_DWORD *)(uintptr_t)(fieldPtr - 4) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(uintptr_t)fieldPtr = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(fieldPtr + 4));
  *(_DWORD *)(uintptr_t)(fieldPtr + 28) = 0;
  *(_DWORD *)(uintptr_t)(fieldPtr + 32) = 0;
  *(_DWORD *)(uintptr_t)(fieldPtr + 36) = 0;
  basePtr = fieldPtr - 175;
  *(_DWORD *)(uintptr_t)(fieldPtr - 175 + 215) = 0;
  *(_DWORD *)(uintptr_t)(fieldPtr - 175 + 363) = 0;
  *(_DWORD *)(uintptr_t)(fieldPtr - 175 + 375) = 0;
  eventPtr = (HANDLE *)(uintptr_t)(fieldPtr - 175 + 387);
  *(_DWORD *)(uintptr_t)(basePtr + 379) = 0;
  *eventPtr = CreateEventA(0, 0, 0, 0);
  eventPtr[1] = 0;
  eventPtr[2] = 0;
  eventPtr[3] = 0;
  eventPtr += 4;
  *eventPtr++ = CreateEventA(0, 0, 0, 0);
  *eventPtr = CreateEventA(0, 0, 0, 0);
  eventPtr[1] = &g_CAviSourceInterface_Vtable;
  return (int)(intptr_t)eventPtr - 407;
}
// 50FDD4: using guessed type int (*off_50FDD4)();

//----- (00464B50) --------------------------------------------------------
char * CAviDecompressor_DestroySourceInterface(int self, char dtorFlags)
{
  HANDLE *eventPtr; // esi
  char *basePtr; // ecx
  int v6; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(self, &g_CAviSourceInterface_DtorArrayTag);
    j_j__nfree_();
    return (char *)(uintptr_t)v6;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(self + 411) = &g_CAviSourceInterface_Vtable;
    eventPtr = (HANDLE *)(uintptr_t)(self + 407);
    AviPlayer_CloseStreams(self);
    CloseHandle(*eventPtr);
    CloseHandle(*(eventPtr - 1));
    j_j__nfree_();
    CloseHandle(*(eventPtr - 5));
    eventPtr -= 51;
    j_j__nfree_();
    DeleteCriticalSection((LPCRITICAL_SECTION)eventPtr - 1);
    CloseHandle(*(eventPtr - 8));
    CloseHandle(*(eventPtr - 9));
    basePtr = (char *)eventPtr - 203;
    if ( (dtorFlags & 2) != 0 )
      j__nfree_();
    return basePtr;
  }
}
// 464C7C: variable 'v4' is possibly undefined
// 464CA7: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50FDD4: using guessed type int (*off_50FDD4)();

//----- (00464CC0) --------------------------------------------------------
int  CAviDecompressor_GetVideoFormat(int self)
{
  return *(_DWORD *)(uintptr_t)(self + 151);
}

//----- (00464CD0) --------------------------------------------------------
int  CAviDecompressor_ReleaseVideoCodec(_DWORD *codecHandlePtr, int drawEndParam)
{
  int v2; // ecx

  CAviDecompressor_CloseCodecHandle(codecHandlePtr, (int)(intptr_t)codecHandlePtr, drawEndParam);
  return v2;
}
// 464CD8: variable 'v2' is possibly undefined

//----- (00464CE0) --------------------------------------------------------
int  CAviDecompressor_InitCommon(int self)
{
  memset((void *)(uintptr_t)(unsigned int)self, 0, 2236);
  *(_BYTE *)(uintptr_t)self = 0;
  *(_BYTE *)(uintptr_t)(self + 1) = 1;
  *(_DWORD *)(uintptr_t)(self + 167) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(uintptr_t)(self + 171) = CreateEventA(0, 0, 0, 0);
  InitializeCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 179));
  *(_DWORD *)(uintptr_t)(self + 387) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(uintptr_t)(self + 403) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(uintptr_t)(self + 407) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(uintptr_t)(self + 411) = &g_CAviSourceInterface_Vtable;
  InitializeCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 1989));
  *(_DWORD *)(uintptr_t)(self + 2196) = CreateEventA(0, 1, 1, 0);
  InitializeCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 2204));
  *(_DWORD *)(uintptr_t)(self + 2228) = CreateEventA(0, 1, 1, 0);
  *(_DWORD *)(uintptr_t)(self + 2232) = &g_CAviDecompressor_Vtable;
  SetRect((LPRECT)(uintptr_t)(self + 1969), -100000, -100000, 100000, 100000);
  return self;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00464FD0) --------------------------------------------------------
int  CAviDecompressor_Destroy(int self, char dtorFlags)
{
  int v11; // ecx

  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(self, &g_CAviDecompressor_DtorArrayTag);
    j_j__nfree_();
    return v11;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(self + 2232) = &g_CAviDecompressor_Vtable;
    AviPlayer_ShutdownDecodeState(self);
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 2228));
    DeleteCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 2204));
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 2196));
    DeleteCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 1989));
    CAviDecompressor_CloseCodecHandle((_DWORD *)(uintptr_t)(self + 415), self + 415, 16);
    *(_DWORD *)(uintptr_t)(self + 411) = &g_CAviSourceInterface_Vtable;
    AviPlayer_CloseStreams(self);
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 407));
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 403));
    j_j__nfree_();
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 387));
    j_j__nfree_();
    DeleteCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 179));
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 171));
    CloseHandle(*(HANDLE *)(uintptr_t)(self + 167));
    if ( (dtorFlags & 2) != 0 )
      j__nfree_();
    return self;
  }
}
// 4651BB: variable 'v11' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (004651D0) --------------------------------------------------------
DWORD __stdcall StartAddress(char *lpThreadParameter)
{
  _DWORD *guardPtr; // ebx
  int blockAlign; // eax
  int v4; // edx
  int v5; // ecx
  signed int Frame; // esi
  int v7; // ecx
  int v8; // edx
  int queuedSamples; // edi
  int readBlockAlign; // eax
  int v11; // edx
  int sampleWriteIndex; // eax
  signed int *sampleQueueEntry; // edi
  int queuedSampleCount; // esi
  int checkBlockAlign; // eax
  int v16; // edx
  signed int nextOffset; // eax
  signed int sampleOffset; // edi
  int chunkFrameIndex; // esi
  int frameFlagsValue; // eax
  char *v21; // eax
  int chunkWriteIndex; // edx
  int *chunkQueueEntry; // edi
  int Sample; // eax
  int samplesToRead; // [esp-14h] [ebp-70h]
  int startSample; // [esp-10h] [ebp-6Ch]
  int destBuffer; // [esp-Ch] [ebp-68h]
  int entryFlags; // [esp+14h] [ebp-48h]
  signed int entryOffset; // [esp+18h] [ebp-44h]
  int entryBytes; // [esp+1Ch] [ebp-40h]
  signed int chunkBytes; // [esp+24h] [ebp-38h]
  signed int bytesRead; // [esp+28h] [ebp-34h] BYREF
  int audioBytesRead; // [esp+2Ch] [ebp-30h] BYREF
  HANDLE *videoQueueSpaceEvent; // [esp+30h] [ebp-2Ch]
  HANDLE *audioQueueSpaceEvent; // [esp+34h] [ebp-28h]
  HANDLE *decodeStopEvent; // [esp+38h] [ebp-24h]
  char *threadRefCount; // [esp+3Ch] [ebp-20h]
  char *selfPtr; // [esp+40h] [ebp-1Ch]
  char *audioStreamInfo; // [esp+44h] [ebp-18h]
  HANDLE *decodeIdleEvent; // [esp+48h] [ebp-14h]
  char *videoChunkQueue; // [esp+4Ch] [ebp-10h]
  _DWORD *audioSampleQueue; // [esp+50h] [ebp-Ch]
  char frameDecoded; // [esp+54h] [ebp-8h]
  char noQueueSpace; // [esp+58h] [ebp-4h]

  threadRefCount = lpThreadParameter + 175;
  ++*(_DWORD *)(lpThreadParameter + 175);
  EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 179));
  if ( !lpThreadParameter[1] )
  {
    decodeIdleEvent = (HANDLE *)(lpThreadParameter + 407);
    decodeStopEvent = (HANDLE *)(lpThreadParameter + 403);
    audioQueueSpaceEvent = (HANDLE *)(lpThreadParameter + 171);
    videoChunkQueue = lpThreadParameter + 203;
    videoQueueSpaceEvent = (HANDLE *)(lpThreadParameter + 387);
    audioSampleQueue = lpThreadParameter + 391;
    audioStreamInfo = lpThreadParameter + 219;
    do
    {
      if ( *((_DWORD *)videoChunkQueue + 2) < *(_DWORD *)(lpThreadParameter + 43) )
      {
        frameDecoded = 0;
        noQueueSpace = 0;
        if ( *(_DWORD *)(lpThreadParameter + 215) )
        {
          AviPlayer_AudioSampleQueueCount((int)(intptr_t)audioSampleQueue);
          AviPlayer_AudioBytesQueued((int)(intptr_t)lpThreadParameter);
          blockAlign = AviPlayer_AudioBlockAlign((int)(intptr_t)lpThreadParameter);
          if ( v4 / blockAlign * v5 / *(_DWORD *)(lpThreadParameter + 367) - *((_DWORD *)audioStreamInfo + 9) <= *((_DWORD *)videoChunkQueue + 2) )
          {
            Frame = AviPlayer_DecodeNextFrame((int)(intptr_t)lpThreadParameter);
            if ( Frame == -1 )
            {
              noQueueSpace = 1;
            }
            else
            {
              frameDecoded = 1;
              destBuffer = *((_DWORD *)audioStreamInfo + 10);
              startSample = Frame + *(_DWORD *)(lpThreadParameter + 375);
              AviPlayer_AudioSampleQueueBase((int)(intptr_t)lpThreadParameter);
              LOWORD(v7) = *(_WORD *)(uintptr_t)(AviPlayer_AudioFormatPtr((int)(intptr_t)lpThreadParameter) + 12);
              samplesToRead = v8 / v7;
              queuedSamples = AviPlayer_AudioSampleQueueCount((int)(intptr_t)audioSampleQueue);
              AviPlayer_AudioBytesQueued((int)(intptr_t)lpThreadParameter);
              readBlockAlign = AviPlayer_AudioBlockAlign((int)(intptr_t)lpThreadParameter);
              AVIStreamRead(
                readBlockAlign,
                v11 % readBlockAlign,
                *(_DWORD *)(lpThreadParameter + 215),
                queuedSamples * (v11 / readBlockAlign),
                samplesToRead,
                startSample,
                destBuffer,
                &bytesRead,
                0);
              chunkBytes = bytesRead;
              sampleWriteIndex = audioSampleQueue[2];
              sampleQueueEntry = (signed int *)(uintptr_t)(8 * sampleWriteIndex + *audioSampleQueue);
              audioSampleQueue[2] = sampleWriteIndex + 1;
              *sampleQueueEntry = Frame;
              sampleQueueEntry[1] = chunkBytes;
            }
          }
        }
        if ( *(_DWORD *)(lpThreadParameter + 215)
          && (queuedSampleCount = AviPlayer_AudioSampleQueueCount((int)(intptr_t)audioSampleQueue),
              AviPlayer_AudioBytesQueued((int)(intptr_t)lpThreadParameter),
              checkBlockAlign = AviPlayer_AudioBlockAlign((int)(intptr_t)lpThreadParameter),
              *((_DWORD *)videoChunkQueue + 2) > v16 / checkBlockAlign * queuedSampleCount / *(_DWORD *)(lpThreadParameter + 367) - *((_DWORD *)audioStreamInfo + 9)) )
        {
          if ( noQueueSpace )
          {
            PulseEvent(*decodeIdleEvent);
            WaitForSingleObject(*videoQueueSpaceEvent, 0x1F4u);
            continue;
          }
          if ( lpThreadParameter[2] )
            goto LABEL_28;
        }
        else
        {
          nextOffset = CAviDecompressor_GetNextVideoFrameBufferOffset((int)(intptr_t)lpThreadParameter);
          if ( nextOffset != -1 )
          {
            sampleOffset = nextOffset;
            chunkFrameIndex = *((_DWORD *)videoChunkQueue + 2);
            AVIStreamRead(
              *(_DWORD *)(lpThreadParameter + 7),
              *(_DWORD *)(lpThreadParameter + 163),
              *(_DWORD *)(lpThreadParameter + 7),
              chunkFrameIndex,
              1,
              *(_DWORD *)(lpThreadParameter + 163) + nextOffset,
              *(_DWORD *)(lpThreadParameter + 155),
              &audioBytesRead,
              0);
            selfPtr = lpThreadParameter;
            if ( audioBytesRead )
            {
              Sample = AVIStreamFindSample(*(_DWORD *)(lpThreadParameter + 7), chunkFrameIndex, 20);
              if ( Sample == chunkFrameIndex )
                frameFlagsValue = chunkFrameIndex ^ Sample;
              else
                frameFlagsValue = 0x8000000;
            }
            else
            {
              frameFlagsValue = 0x10000000;
            }
            entryFlags = frameFlagsValue;
            entryBytes = audioBytesRead;
            v21 = selfPtr;
            chunkWriteIndex = *(_DWORD *)(selfPtr + 211);
            entryOffset = sampleOffset;
            chunkQueueEntry = (int *)(uintptr_t)(12 * chunkWriteIndex + *(_DWORD *)(selfPtr + 203));
            *(_DWORD *)(selfPtr + 211) = chunkWriteIndex + 1;
            *chunkQueueEntry++ = entryFlags;
            *chunkQueueEntry = entryOffset;
            chunkQueueEntry[1] = entryBytes;
            PulseEvent(*(HANDLE *)(v21 + 167));
            if ( !lpThreadParameter[2] )
              continue;
LABEL_28:
            Sleep(0);
            continue;
          }
          PulseEvent(*decodeIdleEvent);
          if ( frameDecoded )
          {
            if ( lpThreadParameter[2] )
              goto LABEL_28;
          }
          else
          {
            WaitForSingleObject(*audioQueueSpaceEvent, 0x1F4u);
          }
        }
      }
      else
      {
        PulseEvent(*decodeIdleEvent);
        WaitForSingleObject(*decodeStopEvent, 0x1F4u);
      }
    }
    while ( !lpThreadParameter[1] );
  }
  guardPtr = threadRefCount;
  LeaveCriticalSection((LPCRITICAL_SECTION)(threadRefCount + 4));
  --*guardPtr;
  return 0;
}
// 465300: variable 'v4' is possibly undefined
// 465304: variable 'v5' is possibly undefined
// 465375: variable 'v8' is possibly undefined
// 465375: variable 'v7' is possibly undefined
// 465397: variable 'v11' is possibly undefined
// 4653F9: variable 'v16' is possibly undefined
// 4E97FE: using guessed type int __stdcall AVIStreamFindSample(_DWORD, _DWORD, _DWORD);
// 4E9804: using guessed type int __fastcall AVIStreamRead(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (00465560) --------------------------------------------------------
BOOL  CAviDecompressor_RequestDecodeThreadStop(int self)
{
  *(_BYTE *)(uintptr_t)(self + 1) = 1;
  CSS_StopSound(*(_DWORD *)(uintptr_t)(self + 359), 0);
  PulseEvent(*(HANDLE *)(uintptr_t)(self + 403));
  PulseEvent(*(HANDLE *)(uintptr_t)(self + 171));
  return PulseEvent(*(HANDLE *)(uintptr_t)(self + 387));
}

//----- (004655B0) --------------------------------------------------------
signed int  CAviDecompressor_GetNextVideoFrameBufferOffset(int self)
{
  int writeEnd; // ecx
  int readStart; // edx
  int bufferSize; // esi

  if ( *(_DWORD *)(uintptr_t)(self + 211) == *(_DWORD *)(uintptr_t)(self + 207) )
    writeEnd = 0;
  else
    writeEnd = *(_DWORD *)(uintptr_t)(12 * (*(_DWORD *)(uintptr_t)(self + 211) - 1) + *(_DWORD *)(uintptr_t)(self + 203) + 4)
       + *(_DWORD *)(uintptr_t)(12 * (*(_DWORD *)(uintptr_t)(self + 211) - 1) + *(_DWORD *)(uintptr_t)(self + 203) + 8);
  readStart = *(_DWORD *)(uintptr_t)(self + 211) - *(_DWORD *)(uintptr_t)(self + 207);
  if ( readStart )
    readStart = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 203) + 12 * *(_DWORD *)(uintptr_t)(self + 207) + 4);
  if ( readStart <= writeEnd )
  {
    bufferSize = *(_DWORD *)(uintptr_t)(self + 155);
    if ( *(_DWORD *)(uintptr_t)(self + 159) - writeEnd >= bufferSize )
      return writeEnd;
    if ( readStart > bufferSize )
      return 0;
    return -1;
  }
  if ( readStart - writeEnd <= *(_DWORD *)(uintptr_t)(self + 155) )
    return -1;
  return writeEnd;
}

//----- (00465670) --------------------------------------------------------
signed int  AviPlayer_DecodeNextFrame(int self)
{
  int writeEnd; // edx
  int readStart; // ecx
  int bufferSize; // esi
  int suggestedBufferSize; // eax

  writeEnd = *(_DWORD *)(uintptr_t)(self + 399) - *(_DWORD *)(uintptr_t)(self + 395);
  if ( writeEnd )
    writeEnd = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 391) + 8 * (*(_DWORD *)(uintptr_t)(self + 399) - 1) + 4)
       + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 391) + 8 * (*(_DWORD *)(uintptr_t)(self + 399) - 1));
  readStart = *(_DWORD *)(uintptr_t)(self + 399) - *(_DWORD *)(uintptr_t)(self + 395);
  if ( readStart )
    readStart = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 391) + 8 * *(_DWORD *)(uintptr_t)(self + 395));
  if ( readStart <= writeEnd )
  {
    bufferSize = *(_DWORD *)(uintptr_t)(self + 371);
    suggestedBufferSize = *(_DWORD *)(uintptr_t)(self + 259);
    if ( bufferSize - writeEnd >= suggestedBufferSize )
      return writeEnd;
    if ( readStart > suggestedBufferSize )
      return 0;
    return -1;
  }
  if ( readStart - writeEnd <= *(_DWORD *)(uintptr_t)(self + 259) )
    return -1;
  return writeEnd;
}

//----- (00465710) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
HANDLE  AviPlayer_OpenFileAndStartDecodeThread(
        int self,
        int fileName,
        int a3,
        int a4 CLASH95_UNUSED,
        int a5 CLASH95_UNUSED,
        int a6 CLASH95_UNUSED,
        int a7 CLASH95_UNUSED,
        int a8 CLASH95_UNUSED,
        int a9 CLASH95_UNUSED,
        int a10 CLASH95_UNUSED,
        int a11 CLASH95_UNUSED,
        int a12 CLASH95_UNUSED,
        int a13 CLASH95_UNUSED,
        int a14 CLASH95_UNUSED,
        int a15,
        int Buffer_2 CLASH95_UNUSED,
        __int64 Buffer_6,
        int Buffer_18 CLASH95_UNUSED,
        int Buffer_22 CLASH95_UNUSED,
        int Buffer_26 CLASH95_UNUSED,
        char Buffer_30 CLASH95_UNUSED,
        char Buffer_30a,
        __int64 a23,
        __int64 a24,
        int a25,
        int a26,
        __int64 ThreadId_2)
{
  HANDLE result; // eax
  int formatSize; // ecx
  int videoFormatHdr; // eax
  char formatFlagByte; // dl
  unsigned int frameBufferBytes; // eax
  unsigned int alignedBytes; // eax
  int allocSize; // ecx
  unsigned int dwScale; // ebx
  signed int memoryCap; // eax
  __int64 frameFlagsAlloc; // rax
  int fps; // ebx
  int totalVideoBytes; // eax
  _DWORD fileInfo[10]; // [esp+82h] [ebp-2Ah] BYREF

  *(_DWORD *)((char *)&ThreadId_2 + 2) = a3;
  *(_DWORD *)(&Buffer_30a + 2) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a23 + 2) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a23 + 6) = &g_AviOpenFileDecodeThread_EHFrame;
  *(_DWORD *)((char *)&a24 + 2) = 0;
  if ( !*(_BYTE *)(uintptr_t)self )
  {
    AVIFileInit();
    *(_BYTE *)(uintptr_t)self = 1;
  }
  result = (HANDLE)(uintptr_t)AVIFileOpenA(self + 3, fileName, 0, 0);
  if ( result )
  {
    *(_DWORD *)(uintptr_t)(self + 3) = 0;
  }
  else
  {
    AVIFileInfoA(*(_DWORD *)(uintptr_t)(self + 3), fileInfo, 108);
    if ( AVIFileGetStream(*(_DWORD *)(uintptr_t)(self + 3), self + 7, 1935960438, 0) )
    {
      result = (HANDLE)(uintptr_t)AVIFileRelease(*(_DWORD *)(uintptr_t)(self + 3));
      *(_DWORD *)(uintptr_t)(self + 3) = 0;
      *(_DWORD *)(uintptr_t)(self + 7) = 0;
    }
    else
    {
      AVIStreamReadFormat(*(_DWORD *)(uintptr_t)(self + 7), 0, 0, (char *)&a25 + 2);
      *(_DWORD *)(uintptr_t)(self + 151) = j_Mem_Alloc(formatSize);
      AVIStreamReadFormat(*(_DWORD *)(uintptr_t)(self + 7), 0, *(_DWORD *)(uintptr_t)(self + 151), (char *)&a25 + 2);
      videoFormatHdr = *(_DWORD *)(uintptr_t)(self + 151);
      formatFlagByte = *(_BYTE *)(uintptr_t)(videoFormatHdr + 13);
      if ( formatFlagByte < 0 )
      {
        *(_BYTE *)(uintptr_t)(videoFormatHdr + 13) = formatFlagByte ^ 0x80;
        *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 16) ^= 0x3ADE68B1u;
      }
      AVIStreamInfoA(*(_DWORD *)(uintptr_t)(self + 7), self + 11, 140);
      AVIStreamBeginStreaming(*(_DWORD *)(uintptr_t)(self + 7), 0, *(_DWORD *)(uintptr_t)(self + 43) - 1, 1000);
      if ( *(_DWORD *)(uintptr_t)(self + 51) )
        frameBufferBytes = *(_DWORD *)(uintptr_t)(self + 51);
      else
        frameBufferBytes = abs32(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 8))
            * (*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4) / 20 + *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4) + 1)
            * ((*(unsigned __int16 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 14) + 7) >> 3);
      *(_DWORD *)(uintptr_t)(self + 155) = frameBufferBytes;
      alignedBytes = frameBufferBytes + 3;
      LOBYTE(alignedBytes) = alignedBytes & 0xFC;
      allocSize = 1000;
      *(_DWORD *)(uintptr_t)(self + 155) = alignedBytes + 16;
      dwScale = *(_DWORD *)(uintptr_t)(self + 31);
      *(_DWORD *)(uintptr_t)(self + 159) = (*(_DWORD *)((char *)&ThreadId_2 + 2) - 500)
                            * ((int)(20000 * (fileInfo[0] / 0x3E8u))
                             / (int)(fileInfo[0] / 0x3E8u + 20000));
      memoryCap = (*(_DWORD *)(uintptr_t)(self + 155) * (*(_DWORD *)(uintptr_t)(self + 35) / dwScale)) >> 1;
      if ( memoryCap > *(_DWORD *)(uintptr_t)(self + 159) )
        goto LABEL_11;
      fps = *(_DWORD *)(uintptr_t)(self + 35) / *(_DWORD *)(uintptr_t)(self + 31);
      totalVideoBytes = *(_DWORD *)(uintptr_t)(self + 43) * *(_DWORD *)(uintptr_t)(self + 155);
      if ( *(_DWORD *)(uintptr_t)(self + 43) / fps * fileInfo[0] < (unsigned int)totalVideoBytes )
        totalVideoBytes = *(_DWORD *)(uintptr_t)(self + 43) / fps * fileInfo[0];
      if ( totalVideoBytes < *(_DWORD *)(uintptr_t)(self + 159) )
        *(_DWORD *)(uintptr_t)(self + 159) = totalVideoBytes;
      GlobalMemoryStatus((LPMEMORYSTATUS)((char *)&a15 + 2));
      allocSize = *(_DWORD *)(uintptr_t)(self + 159);
      memoryCap = *(_DWORD *)((char *)&Buffer_6 + 2) >> 4;
      if ( *(_DWORD *)((char *)&Buffer_6 + 2) >> 4 < allocSize )
LABEL_11:
        *(_DWORD *)(uintptr_t)(self + 159) = memoryCap;
      *(_DWORD *)(uintptr_t)(self + 163) = j_Mem_Alloc(allocSize);
      frameFlagsAlloc = j_Mem_Alloc(*(_DWORD *)(uintptr_t)(self + 43) + 1);
      *(_QWORD *)(uintptr_t)(HIDWORD(frameFlagsAlloc) + 4) = 0LL;
      *(_DWORD *)(uintptr_t)HIDWORD(frameFlagsAlloc) = frameFlagsAlloc;
      *(_BYTE *)(uintptr_t)(self + 2) = 0;
      AviPlayer_OpenAndPrepare((unsigned int *)(uintptr_t)self);
      *(_BYTE *)(uintptr_t)(self + 1) = 0;
      return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, (LPVOID)(uintptr_t)self, 0, (LPDWORD)((char *)&a26 + 2));
    }
  }
  return result;
}
// 46573D: inconsistent variable size for '^124.1(Buffer_30a)'
// 46574A: inconsistent variable size for '^128.8'
// 465710: too many cbuild loops
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 4E97C8: using guessed type int __stdcall AVIFileRelease(_DWORD);
// 4E97CE: using guessed type int __stdcall AVIStreamBeginStreaming(_DWORD, _DWORD, _DWORD, _DWORD);
// 4E97D4: using guessed type int __stdcall AVIStreamInfoA(_DWORD, _DWORD, _DWORD);
// 4E97DA: using guessed type int __stdcall AVIStreamReadFormat(_DWORD, _DWORD, _DWORD, _DWORD);
// 4E97E0: using guessed type int __stdcall AVIFileGetStream(_DWORD, _DWORD, _DWORD, _DWORD);
// 4E97E6: using guessed type int __stdcall AVIFileInfoA(_DWORD, _DWORD, _DWORD);
// 4E97EC: using guessed type int __stdcall AVIFileOpenA(_DWORD, _DWORD, _DWORD, _DWORD);
// 4E97F2: using guessed type int AVIFileInit(void);

//----- (00465A10) --------------------------------------------------------
char  AviPlayer_OpenAndPrepare(unsigned int *self)
{
  int v2; // ecx
  __int64 formatAlloc; // rax
  unsigned int *audioStreamInfo; // ebx
  __int64 queueAlloc; // rax
  double resampleRatio; // st7
  int v7; // edx
  int playerInt; // ecx
  int audioBufferBytes; // edx
  int suggestedBytes; // eax
  __int64 chunkBufAlloc; // rax
  _DWORD *audioSampleQueue; // ebx
  __int64 frameIndexAlloc; // rax
  int v14; // ecx
  int queuedSamples; // esi
  int blockAlign; // eax
  int audioBytesQueued; // edx
  int v18; // ecx
  signed int Frame; // esi
  int v20; // ecx
  int audioBlockAlign; // ecx
  int bytesForSampleCalc; // edx
  int sampleCount; // edi
  int readBlockAlign; // eax
  int bytesForStreamRead; // edx
  int sampleWriteIndex; // eax
  signed int *sampleQueueEntry; // edi
  int soundHandle; // eax
  int playerForFlush; // edx
  int samplesToRead; // [esp-14h] [ebp-4Ch]
  int startSample; // [esp-10h] [ebp-48h]
  int destBuffer; // [esp-Ch] [ebp-44h]
  double lengthScaled; // [esp+8h] [ebp-30h]
  signed int chunkBytes; // [esp+1Ch] [ebp-1Ch]
  __int64 rateScale64; // [esp+20h] [ebp-18h]
  signed int bytesRead; // [esp+28h] [ebp-10h] BYREF
  int formatSize; // [esp+2Ch] [ebp-Ch] BYREF
  int v38; // [esp+30h] [ebp-8h]
  unsigned int *player; // [esp+34h] [ebp-4h]

  player = self;
  if ( AVIFileGetStream(*(unsigned int *)((char *)self + 3), (char *)self + 215, 1935963489, 0) )
  {
    *(unsigned int *)((char *)player + 215) = 0;
    return 0;
  }
  else
  {
    AVIStreamReadFormat(*(unsigned int *)((char *)player + 215), 0, 0, &formatSize);
    formatAlloc = j_Mem_Alloc(v2);
    *(_DWORD *)(uintptr_t)(HIDWORD(formatAlloc) + 363) = formatAlloc;
    audioStreamInfo = player;
    AVIStreamReadFormat(*(_DWORD *)(uintptr_t)(HIDWORD(formatAlloc) + 215), 0, *(_DWORD *)(uintptr_t)(HIDWORD(formatAlloc) + 363), &formatSize);
    audioStreamInfo = (unsigned int *)((char *)audioStreamInfo + 219);
    AVIStreamInfoA(*(unsigned int *)((char *)player + 215), audioStreamInfo, 140);
    queueAlloc = j_Mem_Alloc(*(unsigned int *)((char *)player + 251));
    *(_QWORD *)(uintptr_t)(HIDWORD(queueAlloc) + 391) = (unsigned int)queueAlloc;
    *(_DWORD *)(uintptr_t)(HIDWORD(queueAlloc) + 399) = 0;
    rateScale64 = *(unsigned int *)(uintptr_t)(HIDWORD(queueAlloc) + 31);
    lengthScaled = (double)audioStreamInfo[6] * (double)rateScale64;
    LODWORD(rateScale64) = *(_DWORD *)(uintptr_t)(HIDWORD(queueAlloc) + 35);
    resampleRatio = lengthScaled / ((double)audioStreamInfo[5] * (double)rateScale64);
    _CHP(audioStreamInfo[5], 0);
    *(_DWORD *)(uintptr_t)(v7 + 367) = (int)resampleRatio;
    playerInt = (int)(intptr_t)player;
    audioBufferBytes = *(unsigned int *)((char *)player + 367)
       * *(unsigned __int16 *)(uintptr_t)(*(unsigned int *)((char *)player + 363) + 12)
       * (3 * *(_DWORD *)(uintptr_t)(v7 + 159) / (int)(2 * *(unsigned int *)((char *)player + 155)) + audioStreamInfo[9]);
    *(unsigned int *)((char *)player + 371) = audioBufferBytes;
    suggestedBytes = 4 * audioStreamInfo[10];
    if ( suggestedBytes > audioBufferBytes )
      *(_DWORD *)(uintptr_t)(playerInt + 371) = suggestedBytes;
    chunkBufAlloc = j_Mem_Alloc(playerInt);
    *(_DWORD *)(uintptr_t)(HIDWORD(chunkBufAlloc) + 156) = chunkBufAlloc;
    audioSampleQueue = (unsigned int *)((char *)player + 391);
    frameIndexAlloc = j_Mem_Alloc(player);
    *(_DWORD *)(uintptr_t)(v14 + 383) = 0;
    v38 = HIDWORD(frameIndexAlloc);
    *(_DWORD *)(uintptr_t)(v14 + 379) = frameIndexAlloc;
    while ( 1 )
    {
      queuedSamples = AviPlayer_AudioSampleQueueCount((int)(intptr_t)audioSampleQueue);
      AviPlayer_AudioBytesQueued((int)(intptr_t)player);
      blockAlign = AviPlayer_AudioBlockAlign((int)(intptr_t)player);
      if ( audioBytesQueued / blockAlign * queuedSamples / *(int *)((char *)player + 367) >= *(_DWORD *)(uintptr_t)(v38 + 36) )
        break;
      Frame = AviPlayer_DecodeNextFrame((int)(intptr_t)player);
      if ( Frame == -1 )
        break;
      destBuffer = *(_DWORD *)(uintptr_t)(v38 + 40);
      startSample = Frame + *(_DWORD *)(uintptr_t)(v18 + 375);
      AviPlayer_AudioSampleQueueBase(v18);
      LOWORD(audioBlockAlign) = *(_WORD *)(uintptr_t)(AviPlayer_AudioFormatPtr(v20) + 12);
      samplesToRead = bytesForSampleCalc / audioBlockAlign;
      sampleCount = AviPlayer_AudioSampleQueueCount((int)(intptr_t)audioSampleQueue);
      AviPlayer_AudioBytesQueued((int)(intptr_t)player);
      readBlockAlign = AviPlayer_AudioBlockAlign((int)(intptr_t)player);
      AVIStreamRead(readBlockAlign, bytesForStreamRead % readBlockAlign, *(unsigned int *)((char *)player + 215), sampleCount * (bytesForStreamRead / readBlockAlign), samplesToRead, startSample, destBuffer, &bytesRead, 0);
      chunkBytes = bytesRead;
      sampleWriteIndex = audioSampleQueue[2];
      audioSampleQueue[2] = sampleWriteIndex + 1;
      sampleQueueEntry = (signed int *)(uintptr_t)(*audioSampleQueue + 8 * sampleWriteIndex);
      *sampleQueueEntry = Frame;
      sampleQueueEntry[1] = chunkBytes;
    }
    soundHandle = CSS_StartStreamVoice((int)(intptr_t)player, 64, 0, 0);
    playerForFlush = (int)(intptr_t)player;
    *(unsigned int *)((char *)player + 359) = soundHandle;
    if ( soundHandle )
    {
      return 1;
    }
    else
    {
      AviPlayer_FlushVideoFrameQueue(playerForFlush);
      return 0;
    }
  }
}
// 465A70: variable 'v2' is possibly undefined
// 465B51: variable 'v7' is possibly undefined
// 465BE2: variable 'v14' is possibly undefined
// 465C17: variable 'v17' is possibly undefined
// 465C5B: variable 'v18' is possibly undefined
// 465C72: variable 'v20' is possibly undefined
// 465C82: variable 'v22' is possibly undefined
// 465C82: variable 'v21' is possibly undefined
// 465CA5: variable 'v25' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 4E97D4: using guessed type int __stdcall AVIStreamInfoA(_DWORD, _DWORD, _DWORD);
// 4E97DA: using guessed type int __stdcall AVIStreamReadFormat(_DWORD, _DWORD, _DWORD, _DWORD);
// 4E97E0: using guessed type int __stdcall AVIFileGetStream(_DWORD, _DWORD, _DWORD, _DWORD);
// 4E9804: using guessed type int __fastcall AVIStreamRead(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (00465D30) --------------------------------------------------------
int  AviPlayer_FlushVideoFrameQueue(int self)
{
  int queueBase; // ebx
  HANDLE *i; // esi
  int readIndex; // edx
  int result; // eax

  queueBase = self + 391;
  for ( i = (HANDLE *)(uintptr_t)(self + 387); ; PulseEvent(*i) )
  {
    readIndex = *(_DWORD *)(uintptr_t)(queueBase + 4);
    if ( *(_DWORD *)(uintptr_t)(queueBase + 8) == readIndex )
      break;
    *(_DWORD *)(uintptr_t)(queueBase + 4) = readIndex + 1;
  }
  j_j__nfree_();
  *(_DWORD *)(uintptr_t)(self + 379) = 0;
  j_j__nfree_();
  *(_DWORD *)(uintptr_t)(self + 375) = 0;
  j_j__nfree_();
  result = *(_DWORD *)(uintptr_t)(self + 215);
  *(_DWORD *)(uintptr_t)(self + 363) = 0;
  if ( result )
  {
    result = AVIStreamRelease(result);
    *(_DWORD *)(uintptr_t)(self + 215) = 0;
  }
  return result;
}
// 4E97C2: using guessed type int __stdcall AVIStreamRelease(_DWORD);
