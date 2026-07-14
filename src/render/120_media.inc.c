/* Recovered audio, music, AVI, and media support.
 * Original function-marker range: 0x004637B0..0x004814A0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004637B0) --------------------------------------------------------
int * CAviDecompressor_ConstructEmpty(int *instanceOut, DWORD allocContext)
{
  int instance; // eax

  instance = Mem_Alloc(2236, (int)&g_CAviDecompressor_AllocTypeTag, 0, allocContext);
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
  instance = Mem_Alloc(2236, (int)&stru_50F60C, 0, (DWORD)ddSurface);
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
    *(_DWORD *)(instance + 1952) = ddSurface;
    CAviDecompressor_ApplyDecoderFormatParams(openFlags, fileName);
  }
}
// 4697E0: using guessed type int __fastcall sub_4697E0(_DWORD, _DWORD);

//----- (00463EA0) --------------------------------------------------------
int * CAviDecompressor_ConstructAndInitSource(int *selfOut, DWORD allocContext, int fileName, int openFlags)
{
  int instance; // eax

  *selfOut = 0;
  instance = Mem_Alloc(2236, (int)&stru_50F6A0, 0, allocContext);
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
    (**(void (__fastcall ***)(int, int))(instance + 2232))(instance, 2);
  *handlePtr = 0;
}
// 464229: variable 'v1' is possibly undefined

//----- (00464250) --------------------------------------------------------
int  CAviDecompressor_Frames(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 43);
}

//----- (00464260) --------------------------------------------------------
int  CAviDecompressor_Fps(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 35) / *(_DWORD *)(*(_DWORD *)playerHandle + 31);
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
  return *(_BYTE *)(*(_DWORD *)playerHandle + 2191) != 0;
}

//----- (004642B0) --------------------------------------------------------
int  CAviDecompressor_Initialized(_DWORD *playerHandle)
{
  _DWORD *instance; // eax
  int result; // eax
  int v3; // ebx
  _DWORD *blitState; // eax

  instance = (_DWORD *)*playerHandle;
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
  if ( *(_BYTE *)(instance + 2191) )
    WaitForSingleObject(*(HANDLE *)(instance + 2196), 0x1F4u);
}

//----- (00464320) --------------------------------------------------------
int  CAviDecompressor_Palette(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 1948);
}

//----- (00464330) --------------------------------------------------------
int  CAviDecompressor_Header(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 151);
}

//----- (00464340) --------------------------------------------------------
int  CAviDecompressor_PixelSize(int *playerHandle)
{
  return (*(unsigned __int16 *)(CAviDecompressor_GetVideoFormat(*playerHandle) + 14) + 7) >> 3;
}

//----- (00464360) --------------------------------------------------------
int  CAviDecompressor_BPP(int playerHandle)
{
  return *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)playerHandle + 151) + 14);
}

//----- (00464380) --------------------------------------------------------
int  CAviDecompressor_Width(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)(*(_DWORD *)playerHandle + 151) + 4);
}

//----- (00464390) --------------------------------------------------------
int  CAviDecompressor_Height(int playerHandle)
{
  __int64 biHeight; // rax

  biHeight = *(int *)(*(_DWORD *)(*(_DWORD *)playerHandle + 151) + 8);
  return (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
}

//----- (004643B0) --------------------------------------------------------
int  CAviDecompressor_DecodedFrame(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 2021);
}

//----- (004643C0) --------------------------------------------------------
int  CAviDecompressor_SetBackground(int *playerHandle, _DWORD *bgRect, int ddObject)
{
  int result; // eax

  result = *playerHandle;
  *(_DWORD *)(result + 2155) = *bgRect;
  *(_DWORD *)(result + 2159) = bgRect[1];
  *(_DWORD *)(result + 2163) = bgRect[2];
  *(_DWORD *)(result + 2167) = bgRect[3];
  *(_DWORD *)(result + 2151) = ddObject;
  return result;
}

//----- (004643E0) --------------------------------------------------------
void  CAviDecompressor_InitClipRect(_DWORD *playerHandle, _DWORD *clipRect)
{
  _DWORD *clipDest; // edi

  clipDest = (_DWORD *)(*playerHandle + 1969);
  *clipDest++ = *clipRect;
  *clipDest++ = clipRect[1];
  *clipDest = clipRect[2];
  clipDest[1] = clipRect[3];
}

//----- (00464400) --------------------------------------------------------
void  CAviDecompressor_UpdatePos(int *playerHandle, LONG x, int a3, LONG y)
{
  int v4; // eax
  int v5; // ecx
  int v6; // ebx
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
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+180h] [ebp-20h]
  tagRECT *v19; // [esp+184h] [ebp-1Ch]
  void *v20; // [esp+188h] [ebp-18h]
  int v21; // [esp+18Ch] [ebp-14h]
  int v22; // [esp+19Ch] [ebp-4h]

  v4 = *playerHandle;
  v22 = a3;
  v5 = v4;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v19 = &j____wcpp_4_fs_handler_rtn_;
  v20 = &g_AviUpdatePos_EHFrame;
  v21 = 0;
  if ( !*(_BYTE *)(v4 + 2062) )
  {
    frameRect = *(RECT *)g_AviFrameRectInitScratch;
    frameRect.left = x;
    frameRect.top = y;
    frameRect.right = *(_DWORD *)(*(_DWORD *)(v4 + 151) + 4) + x;
    biHeight = *(int *)(*(_DWORD *)(v4 + 151) + 8);
    frameRect.bottom = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight) + y;
    AviPlayer_RenderFrame(v5, &frameRect);
  }
  v6 = v5;
  if ( *(_BYTE *)(v5 + 1968) && *(_DWORD *)(v5 + 1964) )
  {
    destWidthScaled = 1000 * AviPlayer_SpanDelta(v5, (_DWORD *)(v5 + 2063));
    stretchRatio = destWidthScaled / AviPlayer_SpanDelta(v8, (_DWORD *)(v8 + 2079));
    if ( stretchRatio < *(_DWORD *)(v10 + 2143) || stretchRatio > *(_DWORD *)(v10 + 2147) )
    {
      if ( *(_BYTE *)(v6 + 1968) )
      {
        overlaySurface = *(_DWORD *)(v6 + 1964);
        if ( overlaySurface )
        {
          hideResult = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(*(_DWORD *)overlaySurface + 132))(
                  overlaySurface,
                  v6 + 2095,
                  *(_DWORD *)(v6 + 1956),
                  v6 + 2063,
                  512,
                  0);
          if ( hideResult )
          {
            if ( hideResult != -2005532222
              || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1964) + 96))(*(_DWORD *)(v6 + 1964)) != -2005532222
               || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1964) + 108))(*(_DWORD *)(v6 + 1964)))
              && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1956) + 96))(*(_DWORD *)(v6 + 1956)) != -2005532222
               || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1956) + 108))(*(_DWORD *)(v6 + 1956)))
              && (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v6 + 1964) + 132))(
                   *(_DWORD *)(v6 + 1964),
                   v6 + 2095,
                   *(_DWORD *)(v6 + 1956),
                   v6 + 2063,
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
      if ( *(_DWORD *)(v10 + 2171) )
        showFlags = 20480;
      overlayFlags = showFlags;
      updateResult = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v6 + 1964) + 132))(
              *(_DWORD *)(v6 + 1964),
              v6 + 2095,
              *(_DWORD *)(v6 + 1956),
              v6 + 2063,
              showFlags,
              0);
      if ( updateResult
        && (updateResult != -2005532222
         || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1964) + 96))(*(_DWORD *)(v6 + 1964)) != -2005532222
          || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1964) + 108))(*(_DWORD *)(v6 + 1964)))
         && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1956) + 96))(*(_DWORD *)(v6 + 1956)) != -2005532222
          || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1956) + 108))(*(_DWORD *)(v6 + 1956)))
         && (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v6 + 1964) + 132))(
              *(_DWORD *)(v6 + 1964),
              v6 + 2095,
              *(_DWORD *)(v6 + 1956),
              v6 + 2063,
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
  if ( *(_BYTE *)(instance + 2191) )
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
  int v10; // [esp+10h] [ebp-4h]

  v10 = a3;
  instance = *playerHandle;
  if ( *(_BYTE *)(*playerHandle + 2191) )
  {
    destRect = *(RECT *)g_AviDecompressorBlitRectTemplate;
    destRect.left = x;
    destRect.top = y;
    videoFormat = CAviDecompressor_GetVideoFormat(instance);
    destRect.right = *(_DWORD *)(videoFormat + 4) + v6;
    destRect.bottom = abs32(*(_DWORD *)(CAviDecompressor_GetVideoFormat(v7) + 8)) + y;
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
  if ( *(_BYTE *)(instance + 2191) )
    CAviDecompressor_PresentFrameIfStale(instance, destRect);
}

//----- (004644C0) --------------------------------------------------------
void  CAviDecompressor_GetRect(_DWORD *playerHandle, _DWORD *rectOut)
{
  _DWORD *srcRect; // esi

  srcRect = (_DWORD *)(*playerHandle + 2063);
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
  *(_DWORD *)(instance + 2171) = 8;
  *(_DWORD *)(instance + 2042) = colorKeyLow;
  *(_DWORD *)(instance + 2046) = colorKeyHigh;
}

//----- (00464500) --------------------------------------------------------
void  CAviDecompressor_InitPos(int *playerHandle, int x, int y)
{
  int instance; // eax

  instance = *playerHandle;
  *(_DWORD *)(instance + 2071) = 0;
  *(_DWORD *)(instance + 2075) = 0;
  *(_BYTE *)(instance + 2062) = 1;
  *(_DWORD *)(instance + 2063) = x;
  *(_DWORD *)(instance + 2067) = y;
}

//----- (00464530) --------------------------------------------------------
void  CAviDecompressor_InitRect(int *playerHandle, _DWORD *rect)
{
  int instance; // eax

  instance = *playerHandle;
  *(_DWORD *)(instance + 2063) = *rect;
  *(_DWORD *)(instance + 2067) = rect[1];
  *(_DWORD *)(instance + 2071) = rect[2];
  *(_DWORD *)(instance + 2075) = rect[3];
  *(_BYTE *)(instance + 2062) = 1;
}

//----- (00464550) --------------------------------------------------------
void  CAviDecompressor_InitOverlays(int playerHandle, char enabled)
{
  *(_BYTE *)(*(_DWORD *)playerHandle + 2050) = enabled != 0;
}

//----- (00464570) --------------------------------------------------------
unsigned int  CAviDecompressor_TimeMs(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 43)
       * ((unsigned int)(1000 * *(_DWORD *)(*(_DWORD *)playerHandle + 31))
        / *(_DWORD *)(*(_DWORD *)playerHandle + 35));
}

//----- (004645C0) --------------------------------------------------------
int  CAviDecompressor_SumSleepTime(int playerHandle)
{
  return *(_DWORD *)(*(_DWORD *)playerHandle + 2038);
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
  CAviDecompressor_Init(aviHandle, ddSurface, (int)fileName, openFlags);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)aviHandle)
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
  CAviDecompressor_Init(aviHandle, ddSurface, (int)fileName, openFlags);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)aviHandle)
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
void __stdcall PlayAviSurface2(char *fileName, IDirectDrawSurface2 *ddSurface2, int x, int y, int (*continueCallback)(void), int openFlags)
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
  CAviDecompressor_InitSource(openFlags, (int)fileName);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)aviHandle)
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
void __stdcall PlayAviStretchSurface2(char *fileName, IDirectDrawSurface2 *ddSurface2, tagRECT *destRect, int (*continueCallback)(void), int openFlags)
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
  CAviDecompressor_InitSource(openFlags, (int)fileName);
  if ( CAviDecompressor_Initialized(aviHandle) )
  {
    CAviDecompressor_Start(aviHandle);
    while ( CAviDecompressor_IsPlaying((int)aviHandle)
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
  *(_DWORD *)guard = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(guard + 4));
  return guard;
}

//----- (00464950) --------------------------------------------------------
int  CAviDecompressor_DoneThreadGuard(int guard)
{
  DeleteCriticalSection((LPCRITICAL_SECTION)(guard + 4));
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
int CAviDecompressor_FreeMemberA()
{
  int v2; // ecx

  j_j__nfree_();
  return v2;
}
// 4649BA: variable 'v2' is possibly undefined

//----- (004649C0) --------------------------------------------------------
int CAviDecompressor_FreeMemberB()
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

  *(_BYTE *)self = 0;
  *(_BYTE *)(self + 1) = 1;
  *(_DWORD *)(self + 3) = 0;
  *(_DWORD *)(self + 7) = 0;
  *(_DWORD *)(self + 151) = 0;
  *(_DWORD *)(self + 163) = 0;
  fieldPtr = self + 171;
  *(_DWORD *)(self + 167) = CreateEventA(0, 0, 0, 0);
  fieldPtr += 4;
  *(_DWORD *)(fieldPtr - 4) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)fieldPtr = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(fieldPtr + 4));
  *(_DWORD *)(fieldPtr + 28) = 0;
  *(_DWORD *)(fieldPtr + 32) = 0;
  *(_DWORD *)(fieldPtr + 36) = 0;
  basePtr = fieldPtr - 175;
  *(_DWORD *)(fieldPtr - 175 + 215) = 0;
  *(_DWORD *)(fieldPtr - 175 + 363) = 0;
  *(_DWORD *)(fieldPtr - 175 + 375) = 0;
  eventPtr = (HANDLE *)(fieldPtr - 175 + 387);
  *(_DWORD *)(basePtr + 379) = 0;
  *eventPtr = CreateEventA(0, 0, 0, 0);
  eventPtr[1] = 0;
  eventPtr[2] = 0;
  eventPtr[3] = 0;
  eventPtr += 4;
  *eventPtr++ = CreateEventA(0, 0, 0, 0);
  *eventPtr = CreateEventA(0, 0, 0, 0);
  eventPtr[1] = &g_CAviSourceInterface_Vtable;
  return (int)eventPtr - 407;
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
    return (char *)v6;
  }
  else
  {
    *(_DWORD *)(self + 411) = &g_CAviSourceInterface_Vtable;
    eventPtr = (HANDLE *)(self + 407);
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
  return *(_DWORD *)(self + 151);
}

//----- (00464CD0) --------------------------------------------------------
int  CAviDecompressor_ReleaseVideoCodec(_DWORD *codecHandlePtr, int drawEndParam)
{
  int v2; // ecx

  CAviDecompressor_CloseCodecHandle(codecHandlePtr, (int)codecHandlePtr, drawEndParam);
  return v2;
}
// 464CD8: variable 'v2' is possibly undefined

//----- (00464CE0) --------------------------------------------------------
int  CAviDecompressor_InitCommon(int self)
{
  memset((void *)(uintptr_t)(unsigned int)self, 0, 2236);
  *(_BYTE *)self = 0;
  *(_BYTE *)(self + 1) = 1;
  *(_DWORD *)(self + 167) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(self + 171) = CreateEventA(0, 0, 0, 0);
  InitializeCriticalSection((LPCRITICAL_SECTION)(self + 179));
  *(_DWORD *)(self + 387) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(self + 403) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(self + 407) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(self + 411) = &g_CAviSourceInterface_Vtable;
  InitializeCriticalSection((LPCRITICAL_SECTION)(self + 1989));
  *(_DWORD *)(self + 2196) = CreateEventA(0, 1, 1, 0);
  InitializeCriticalSection((LPCRITICAL_SECTION)(self + 2204));
  *(_DWORD *)(self + 2228) = CreateEventA(0, 1, 1, 0);
  *(_DWORD *)(self + 2232) = &g_CAviDecompressor_Vtable;
  SetRect((LPRECT)(self + 1969), -100000, -100000, 100000, 100000);
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
    *(_DWORD *)(self + 2232) = &g_CAviDecompressor_Vtable;
    AviPlayer_ShutdownDecodeState(self);
    CloseHandle(*(HANDLE *)(self + 2228));
    DeleteCriticalSection((LPCRITICAL_SECTION)(self + 2204));
    CloseHandle(*(HANDLE *)(self + 2196));
    DeleteCriticalSection((LPCRITICAL_SECTION)(self + 1989));
    CAviDecompressor_CloseCodecHandle((_DWORD *)(self + 415), self + 415, 16);
    *(_DWORD *)(self + 411) = &g_CAviSourceInterface_Vtable;
    AviPlayer_CloseStreams(self);
    CloseHandle(*(HANDLE *)(self + 407));
    CloseHandle(*(HANDLE *)(self + 403));
    j_j__nfree_();
    CloseHandle(*(HANDLE *)(self + 387));
    j_j__nfree_();
    DeleteCriticalSection((LPCRITICAL_SECTION)(self + 179));
    CloseHandle(*(HANDLE *)(self + 171));
    CloseHandle(*(HANDLE *)(self + 167));
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
  char *audioChunkQueue; // [esp+4Ch] [ebp-10h]
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
    audioChunkQueue = lpThreadParameter + 203;
    videoQueueSpaceEvent = (HANDLE *)(lpThreadParameter + 387);
    audioSampleQueue = lpThreadParameter + 391;
    audioStreamInfo = lpThreadParameter + 219;
    do
    {
      if ( *((_DWORD *)audioChunkQueue + 2) < *(_DWORD *)(lpThreadParameter + 43) )
      {
        frameDecoded = 0;
        noQueueSpace = 0;
        if ( *(_DWORD *)(lpThreadParameter + 215) )
        {
          AviPlayer_AudioSampleQueueCount((int)audioSampleQueue);
          AviPlayer_AudioBytesQueued((int)lpThreadParameter);
          blockAlign = AviPlayer_AudioBlockAlign((int)lpThreadParameter);
          if ( v4 / blockAlign * v5 / *(_DWORD *)(lpThreadParameter + 367) - *((_DWORD *)audioStreamInfo + 9) <= *((_DWORD *)audioChunkQueue + 2) )
          {
            Frame = AviPlayer_DecodeNextFrame((int)lpThreadParameter);
            if ( Frame == -1 )
            {
              noQueueSpace = 1;
            }
            else
            {
              frameDecoded = 1;
              destBuffer = *((_DWORD *)audioStreamInfo + 10);
              startSample = Frame + *(_DWORD *)(lpThreadParameter + 375);
              AviPlayer_AudioSampleQueueBase((int)lpThreadParameter);
              LOWORD(v7) = *(_WORD *)(AviPlayer_AudioFormatPtr((int)lpThreadParameter) + 12);
              samplesToRead = v8 / v7;
              queuedSamples = AviPlayer_AudioSampleQueueCount((int)audioSampleQueue);
              AviPlayer_AudioBytesQueued((int)lpThreadParameter);
              readBlockAlign = AviPlayer_AudioBlockAlign((int)lpThreadParameter);
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
              sampleQueueEntry = (signed int *)(8 * sampleWriteIndex + *audioSampleQueue);
              audioSampleQueue[2] = sampleWriteIndex + 1;
              *sampleQueueEntry = Frame;
              sampleQueueEntry[1] = chunkBytes;
            }
          }
        }
        if ( *(_DWORD *)(lpThreadParameter + 215)
          && (queuedSampleCount = AviPlayer_AudioSampleQueueCount((int)audioSampleQueue),
              AviPlayer_AudioBytesQueued((int)lpThreadParameter),
              checkBlockAlign = AviPlayer_AudioBlockAlign((int)lpThreadParameter),
              *((_DWORD *)audioChunkQueue + 2) > v16 / checkBlockAlign * queuedSampleCount / *(_DWORD *)(lpThreadParameter + 367) - *((_DWORD *)audioStreamInfo + 9)) )
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
          nextOffset = CAviDecompressor_GetNextAudioSampleOffset((int)lpThreadParameter);
          if ( nextOffset != -1 )
          {
            sampleOffset = nextOffset;
            chunkFrameIndex = *((_DWORD *)audioChunkQueue + 2);
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
            chunkQueueEntry = (int *)(12 * chunkWriteIndex + *(_DWORD *)(selfPtr + 203));
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
  *(_BYTE *)(self + 1) = 1;
  CSS_StopSound(*(_DWORD *)(self + 359), 0);
  PulseEvent(*(HANDLE *)(self + 403));
  PulseEvent(*(HANDLE *)(self + 171));
  return PulseEvent(*(HANDLE *)(self + 387));
}

//----- (004655B0) --------------------------------------------------------
signed int  CAviDecompressor_GetNextAudioSampleOffset(int self)
{
  int writeEnd; // ecx
  int readStart; // edx
  int bufferSize; // esi

  if ( *(_DWORD *)(self + 211) == *(_DWORD *)(self + 207) )
    writeEnd = 0;
  else
    writeEnd = *(_DWORD *)(12 * (*(_DWORD *)(self + 211) - 1) + *(_DWORD *)(self + 203) + 4)
       + *(_DWORD *)(12 * (*(_DWORD *)(self + 211) - 1) + *(_DWORD *)(self + 203) + 8);
  readStart = *(_DWORD *)(self + 211) - *(_DWORD *)(self + 207);
  if ( readStart )
    readStart = *(_DWORD *)(*(_DWORD *)(self + 203) + 12 * *(_DWORD *)(self + 207) + 4);
  if ( readStart <= writeEnd )
  {
    bufferSize = *(_DWORD *)(self + 155);
    if ( *(_DWORD *)(self + 159) - writeEnd >= bufferSize )
      return writeEnd;
    if ( readStart > bufferSize )
      return 0;
    return -1;
  }
  if ( readStart - writeEnd <= *(_DWORD *)(self + 155) )
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

  writeEnd = *(_DWORD *)(self + 399) - *(_DWORD *)(self + 395);
  if ( writeEnd )
    writeEnd = *(_DWORD *)(*(_DWORD *)(self + 391) + 8 * (*(_DWORD *)(self + 399) - 1) + 4)
       + *(_DWORD *)(*(_DWORD *)(self + 391) + 8 * (*(_DWORD *)(self + 399) - 1));
  readStart = *(_DWORD *)(self + 399) - *(_DWORD *)(self + 395);
  if ( readStart )
    readStart = *(_DWORD *)(*(_DWORD *)(self + 391) + 8 * *(_DWORD *)(self + 395));
  if ( readStart <= writeEnd )
  {
    bufferSize = *(_DWORD *)(self + 371);
    suggestedBufferSize = *(_DWORD *)(self + 259);
    if ( bufferSize - writeEnd >= suggestedBufferSize )
      return writeEnd;
    if ( readStart > suggestedBufferSize )
      return 0;
    return -1;
  }
  if ( readStart - writeEnd <= *(_DWORD *)(self + 259) )
    return -1;
  return writeEnd;
}

//----- (00465710) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
HANDLE  AviPlayer_OpenFileAndStartDecodeThread(
        int self,
        int fileName,
        int a3,
        int a4,
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
        int Buffer_2,
        __int64 Buffer_6,
        int Buffer_18,
        int Buffer_22,
        int Buffer_26,
        char Buffer_30,
        char Buffer_30a,
        __int64 a23,
        __int64 a24,
        int a25,
        int a26,
        __int64 ThreadId_2)
{
  HANDLE result; // eax
  int v30; // ecx
  int videoFormatHdr; // eax
  char v32; // dl
  unsigned int frameBufferBytes; // eax
  unsigned int alignedBytes; // eax
  int v35; // ecx
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
  if ( !*(_BYTE *)self )
  {
    AVIFileInit();
    *(_BYTE *)self = 1;
  }
  result = (HANDLE)AVIFileOpenA(self + 3, fileName, 0, 0);
  if ( result )
  {
    *(_DWORD *)(self + 3) = 0;
  }
  else
  {
    AVIFileInfoA(*(_DWORD *)(self + 3), fileInfo, 108);
    if ( AVIFileGetStream(*(_DWORD *)(self + 3), self + 7, 1935960438, 0) )
    {
      result = (HANDLE)AVIFileRelease(*(_DWORD *)(self + 3));
      *(_DWORD *)(self + 3) = 0;
      *(_DWORD *)(self + 7) = 0;
    }
    else
    {
      AVIStreamReadFormat(*(_DWORD *)(self + 7), 0, 0, (char *)&a25 + 2);
      *(_DWORD *)(self + 151) = j_Mem_Alloc(v30);
      AVIStreamReadFormat(*(_DWORD *)(self + 7), 0, *(_DWORD *)(self + 151), (char *)&a25 + 2);
      videoFormatHdr = *(_DWORD *)(self + 151);
      v32 = *(_BYTE *)(videoFormatHdr + 13);
      if ( v32 < 0 )
      {
        *(_BYTE *)(videoFormatHdr + 13) = v32 ^ 0x80;
        *(_DWORD *)(*(_DWORD *)(self + 151) + 16) ^= 0x3ADE68B1u;
      }
      AVIStreamInfoA(*(_DWORD *)(self + 7), self + 11, 140);
      AVIStreamBeginStreaming(*(_DWORD *)(self + 7), 0, *(_DWORD *)(self + 43) - 1, 1000);
      if ( *(_DWORD *)(self + 51) )
        frameBufferBytes = *(_DWORD *)(self + 51);
      else
        frameBufferBytes = abs32(*(_DWORD *)(*(_DWORD *)(self + 151) + 8))
            * (*(_DWORD *)(*(_DWORD *)(self + 151) + 4) / 20 + *(_DWORD *)(*(_DWORD *)(self + 151) + 4) + 1)
            * ((*(unsigned __int16 *)(*(_DWORD *)(self + 151) + 14) + 7) >> 3);
      *(_DWORD *)(self + 155) = frameBufferBytes;
      alignedBytes = frameBufferBytes + 3;
      LOBYTE(alignedBytes) = alignedBytes & 0xFC;
      v35 = 1000;
      *(_DWORD *)(self + 155) = alignedBytes + 16;
      dwScale = *(_DWORD *)(self + 31);
      *(_DWORD *)(self + 159) = (*(_DWORD *)((char *)&ThreadId_2 + 2) - 500)
                            * ((int)(20000 * (fileInfo[0] / 0x3E8u))
                             / (int)(fileInfo[0] / 0x3E8u + 20000));
      memoryCap = (*(_DWORD *)(self + 155) * (*(_DWORD *)(self + 35) / dwScale)) >> 1;
      if ( memoryCap > *(_DWORD *)(self + 159) )
        goto LABEL_11;
      fps = *(_DWORD *)(self + 35) / *(_DWORD *)(self + 31);
      totalVideoBytes = *(_DWORD *)(self + 43) * *(_DWORD *)(self + 155);
      if ( *(_DWORD *)(self + 43) / fps * fileInfo[0] < (unsigned int)totalVideoBytes )
        totalVideoBytes = *(_DWORD *)(self + 43) / fps * fileInfo[0];
      if ( totalVideoBytes < *(_DWORD *)(self + 159) )
        *(_DWORD *)(self + 159) = totalVideoBytes;
      GlobalMemoryStatus((LPMEMORYSTATUS)((char *)&a15 + 2));
      v35 = *(_DWORD *)(self + 159);
      memoryCap = *(_DWORD *)((char *)&Buffer_6 + 2) >> 4;
      if ( *(_DWORD *)((char *)&Buffer_6 + 2) >> 4 < v35 )
LABEL_11:
        *(_DWORD *)(self + 159) = memoryCap;
      *(_DWORD *)(self + 163) = j_Mem_Alloc(v35);
      frameFlagsAlloc = j_Mem_Alloc(*(_DWORD *)(self + 43) + 1);
      *(_QWORD *)(HIDWORD(frameFlagsAlloc) + 4) = 0LL;
      *(_DWORD *)HIDWORD(frameFlagsAlloc) = frameFlagsAlloc;
      *(_BYTE *)(self + 2) = 0;
      AviPlayer_OpenAndPrepare((unsigned int *)self);
      *(_BYTE *)(self + 1) = 0;
      return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, (LPVOID)self, 0, (LPDWORD)((char *)&a26 + 2));
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
  int v8; // ecx
  int audioBufferBytes; // edx
  int suggestedBytes; // eax
  __int64 chunkBufAlloc; // rax
  _DWORD *audioSampleQueue; // ebx
  __int64 frameIndexAlloc; // rax
  int v14; // ecx
  int queuedSamples; // esi
  int blockAlign; // eax
  int v17; // edx
  int v18; // ecx
  signed int Frame; // esi
  int v20; // ecx
  int v21; // ecx
  int v22; // edx
  int sampleCount; // edi
  int readBlockAlign; // eax
  int v25; // edx
  int sampleWriteIndex; // eax
  signed int *sampleQueueEntry; // edi
  int soundHandle; // eax
  int v29; // edx
  int samplesToRead; // [esp-14h] [ebp-4Ch]
  int startSample; // [esp-10h] [ebp-48h]
  int destBuffer; // [esp-Ch] [ebp-44h]
  double lengthScaled; // [esp+8h] [ebp-30h]
  signed int chunkBytes; // [esp+1Ch] [ebp-1Ch]
  __int64 rateScale64; // [esp+20h] [ebp-18h]
  signed int bytesRead; // [esp+28h] [ebp-10h] BYREF
  int v37; // [esp+2Ch] [ebp-Ch] BYREF
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
    AVIStreamReadFormat(*(unsigned int *)((char *)player + 215), 0, 0, &v37);
    formatAlloc = j_Mem_Alloc(v2);
    *(_DWORD *)(HIDWORD(formatAlloc) + 363) = formatAlloc;
    audioStreamInfo = player;
    AVIStreamReadFormat(*(_DWORD *)(HIDWORD(formatAlloc) + 215), 0, *(_DWORD *)(HIDWORD(formatAlloc) + 363), &v37);
    audioStreamInfo = (unsigned int *)((char *)audioStreamInfo + 219);
    AVIStreamInfoA(*(unsigned int *)((char *)player + 215), audioStreamInfo, 140);
    queueAlloc = j_Mem_Alloc(*(unsigned int *)((char *)player + 251));
    *(_QWORD *)(HIDWORD(queueAlloc) + 391) = (unsigned int)queueAlloc;
    *(_DWORD *)(HIDWORD(queueAlloc) + 399) = 0;
    rateScale64 = *(unsigned int *)(HIDWORD(queueAlloc) + 31);
    lengthScaled = (double)audioStreamInfo[6] * (double)rateScale64;
    LODWORD(rateScale64) = *(_DWORD *)(HIDWORD(queueAlloc) + 35);
    resampleRatio = lengthScaled / ((double)audioStreamInfo[5] * (double)rateScale64);
    _CHP(audioStreamInfo[5], 0);
    *(_DWORD *)(v7 + 367) = (int)resampleRatio;
    v8 = (int)player;
    audioBufferBytes = *(unsigned int *)((char *)player + 367)
       * *(unsigned __int16 *)(*(unsigned int *)((char *)player + 363) + 12)
       * (3 * *(_DWORD *)(v7 + 159) / (int)(2 * *(unsigned int *)((char *)player + 155)) + audioStreamInfo[9]);
    *(unsigned int *)((char *)player + 371) = audioBufferBytes;
    suggestedBytes = 4 * audioStreamInfo[10];
    if ( suggestedBytes > audioBufferBytes )
      *(_DWORD *)(v8 + 371) = suggestedBytes;
    chunkBufAlloc = j_Mem_Alloc(v8);
    *(_DWORD *)(HIDWORD(chunkBufAlloc) + 156) = chunkBufAlloc;
    audioSampleQueue = (unsigned int *)((char *)player + 391);
    frameIndexAlloc = j_Mem_Alloc(player);
    *(_DWORD *)(v14 + 383) = 0;
    v38 = HIDWORD(frameIndexAlloc);
    *(_DWORD *)(v14 + 379) = frameIndexAlloc;
    while ( 1 )
    {
      queuedSamples = AviPlayer_AudioSampleQueueCount((int)audioSampleQueue);
      AviPlayer_AudioBytesQueued((int)player);
      blockAlign = AviPlayer_AudioBlockAlign((int)player);
      if ( v17 / blockAlign * queuedSamples / *(int *)((char *)player + 367) >= *(_DWORD *)(v38 + 36) )
        break;
      Frame = AviPlayer_DecodeNextFrame((int)player);
      if ( Frame == -1 )
        break;
      destBuffer = *(_DWORD *)(v38 + 40);
      startSample = Frame + *(_DWORD *)(v18 + 375);
      AviPlayer_AudioSampleQueueBase(v18);
      LOWORD(v21) = *(_WORD *)(AviPlayer_AudioFormatPtr(v20) + 12);
      samplesToRead = v22 / v21;
      sampleCount = AviPlayer_AudioSampleQueueCount((int)audioSampleQueue);
      AviPlayer_AudioBytesQueued((int)player);
      readBlockAlign = AviPlayer_AudioBlockAlign((int)player);
      AVIStreamRead(readBlockAlign, v25 % readBlockAlign, *(unsigned int *)((char *)player + 215), sampleCount * (v25 / readBlockAlign), samplesToRead, startSample, destBuffer, &bytesRead, 0);
      chunkBytes = bytesRead;
      sampleWriteIndex = audioSampleQueue[2];
      audioSampleQueue[2] = sampleWriteIndex + 1;
      sampleQueueEntry = (signed int *)(*audioSampleQueue + 8 * sampleWriteIndex);
      *sampleQueueEntry = Frame;
      sampleQueueEntry[1] = chunkBytes;
    }
    soundHandle = CSS_StartStreamVoice((int)player, 64, 0, 0);
    v29 = (int)player;
    *(unsigned int *)((char *)player + 359) = soundHandle;
    if ( soundHandle )
    {
      return 1;
    }
    else
    {
      AviPlayer_FlushVideoFrameQueue(v29);
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
  for ( i = (HANDLE *)(self + 387); ; PulseEvent(*i) )
  {
    readIndex = *(_DWORD *)(queueBase + 4);
    if ( *(_DWORD *)(queueBase + 8) == readIndex )
      break;
    *(_DWORD *)(queueBase + 4) = readIndex + 1;
  }
  j_j__nfree_();
  *(_DWORD *)(self + 379) = 0;
  j_j__nfree_();
  *(_DWORD *)(self + 375) = 0;
  j_j__nfree_();
  result = *(_DWORD *)(self + 215);
  *(_DWORD *)(self + 363) = 0;
  if ( result )
  {
    result = AVIStreamRelease(result);
    *(_DWORD *)(self + 215) = 0;
  }
  return result;
}
// 4E97C2: using guessed type int __stdcall AVIStreamRelease(_DWORD);

//----- (00465DD0) --------------------------------------------------------
int  AviPlayer_CloseStreams(int self)
{
  int readIndex; // ebp
  int result; // eax
  int videoStream; // ecx

  CAviDecompressor_RequestDecodeThreadStop(self);
  ++*(_DWORD *)(self + 175);
  EnterCriticalSection((LPCRITICAL_SECTION)(self + 179));
  LeaveCriticalSection((LPCRITICAL_SECTION)(self + 179));
  --*(_DWORD *)(self + 175);
  while ( 1 )
  {
    readIndex = *(_DWORD *)(self + 207);
    if ( *(_DWORD *)(self + 211) == readIndex )
      break;
    *(_DWORD *)(self + 207) = readIndex + 1;
    PulseEvent(*(HANDLE *)(self + 171));
  }
  AviPlayer_FlushVideoFrameQueue(self);
  j_j__nfree_();
  *(_DWORD *)(self + 163) = 0;
  result = j_j__nfree_();
  videoStream = *(_DWORD *)(self + 7);
  *(_DWORD *)(self + 151) = 0;
  if ( videoStream )
  {
    AVIStreamEndStreaming(videoStream);
    result = AVIStreamRelease(*(_DWORD *)(self + 7));
    *(_DWORD *)(self + 7) = 0;
  }
  if ( *(_DWORD *)(self + 3) )
  {
    result = AVIFileRelease(*(_DWORD *)(self + 3));
    *(_DWORD *)(self + 3) = 0;
  }
  if ( *(_BYTE *)self )
  {
    result = AVIFileExit();
    *(_BYTE *)self = 0;
  }
  return result;
}
// 4E97B6: using guessed type int AVIFileExit(void);
// 4E97BC: using guessed type int __stdcall AVIStreamEndStreaming(_DWORD);
// 4E97C2: using guessed type int __stdcall AVIStreamRelease(_DWORD);
// 4E97C8: using guessed type int __stdcall AVIFileRelease(_DWORD);

//----- (00465EC0) --------------------------------------------------------
int  AviPlayer_GetBufferedAudioSample(int self, int targetFrame, _DWORD *frameFlagsOut, _DWORD *frameIndexOut)
{
  int readIndex; // ebx
  int clampedIndex; // edx
  int scanIndex; // eax
  int i; // edx

  readIndex = *(_DWORD *)(self + 207);
  if ( *(_DWORD *)(self + 211) != readIndex )
  {
    if ( readIndex < targetFrame )
    {
      clampedIndex = *(_DWORD *)(self + 211) - 1;
      if ( clampedIndex >= targetFrame )
        clampedIndex = targetFrame;
      scanIndex = clampedIndex;
      for ( i = 12 * clampedIndex; scanIndex > *(_DWORD *)(self + 207) && *(_DWORD *)(i + *(_DWORD *)(self + 203)); i -= 12 )
        --scanIndex;
      if ( scanIndex > *(_DWORD *)(self + 207) )
        *(_DWORD *)(self + 207) = scanIndex;
    }
    *frameIndexOut = *(_DWORD *)(self + 207);
    goto LABEL_12;
  }
  *frameIndexOut = *(_DWORD *)(self + 211);
  if ( !WaitForSingleObject(*(HANDLE *)(self + 167), 0x3E8u) )
  {
LABEL_12:
    *frameFlagsOut = *(_DWORD *)(*(_DWORD *)(self + 203) + 12 * *(_DWORD *)(self + 207));
    return *(_DWORD *)(self + 163) + *(_DWORD *)(*(_DWORD *)(self + 203) + 12 * *(_DWORD *)(self + 207) + 4);
  }
  return 0;
}

//----- (00465FB0) --------------------------------------------------------
unsigned int  AviPlayer_PopBufferedVideoFrame(int self, void *destBuffer)
{
  int queueBase; // edx
  _DWORD *entry; // eax
  unsigned int frameBytes; // ebp

  if ( *(_DWORD *)(self + 399) == *(_DWORD *)(self + 395) )
    return 0;
  queueBase = self + 391;
  entry = (_DWORD *)(*(_DWORD *)(self + 391) + 8 * *(_DWORD *)(self + 395));
  frameBytes = entry[1];
  qmemcpy(destBuffer, (const void *)(*entry + *(_DWORD *)(self + 375)), frameBytes);
  ++*(_DWORD *)(queueBase + 4);
  PulseEvent(*(HANDLE *)(self + 387));
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
  int v30; // edx
  int v31; // [esp+0h] [ebp-120h]
  int v32; // [esp+0h] [ebp-120h]

  *(_DWORD *)((char *)&a20 + 2) = codecState;
  *(_DWORD *)((char *)&a19 + 6) = fccHandler;
  *(_DWORD *)((char *)&a17 + 6) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a18 + 2) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a18 + 6) = &g_AviOpenVideoCodec_EHFrame;
  *(_DWORD *)((char *)&a19 + 2) = 0;
  *(_DWORD *)(codecState + 4) = inputFormat;
  if ( outputFormat && (*(unsigned __int16 *)(inputFormat + 14) > 8u || outputFormat[2] >= 0) )
  {
    outFormatDest = *(_DWORD *)((char *)&a20 + 2) + 8;
    qmemcpy((void *)(*(_DWORD *)((char *)&a20 + 2) + 8), outputFormat, *outputFormat);
    hic = ICLocate(1667524982, *(_DWORD *)((char *)&a19 + 6), *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4), outFormatDest, 2);
    **(_DWORD **)((char *)&a20 + 2) = hic;
  }
  BYTE6(a20) = **(_DWORD **)((char *)&a20 + 2) != 0;
  if ( !**(_DWORD **)((char *)&a20 + 2) )
  {
    hicFallback = ICGetDisplayFormat(
            0,
            *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4),
            *(_DWORD *)((char *)&a20 + 2) + 8,
            0,
            0,
            0);
    **(_DWORD **)((char *)&a20 + 2) = hicFallback;
  }
  if ( **(_DWORD **)((char *)&a20 + 2) )
  {
    inputBmi = *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4);
    srcWidth = *(_DWORD *)(inputBmi + 4);
    outFormatPtr = *(_DWORD *)((char *)&a20 + 2) + 8;
    srcHeight = abs32(*(_DWORD *)(inputBmi + 8));
    hicHandle = **(_DWORD **)((char *)&a20 + 2);
    v30 = *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4);
    *(_DWORD *)((char *)&a12 + 2) = 0;
    *(_DWORD *)((char *)&a12 + 6) = v30;
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
             *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4),
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
        *(_BYTE *)(*(_DWORD *)((char *)&a20 + 2) + 1508) = 0;
        BYTE2(a21) = BYTE6(a20) != 0;
      }
    }
    else
    {
      *(_BYTE *)(*(_DWORD *)((char *)&a20 + 2) + 1508) = 1;
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
      result = (_DWORD *)ICClose(*codecPtr);
      *codecPtr = 0;
    }
    else
    {
      ICSendMessage(*result, 16398, 0, 0, decompressEndParam);
      result = (_DWORD *)ICClose(*codecPtr);
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
  while ( *(_BYTE *)(self + 2191) )
  {
    if ( AviPlayer_UpdateTargetFrameFromClock(self) && (*(_DWORD *)(self + 211) < *(_DWORD *)(self + 43) || AviPlayer_QueueBacklogCount(self + 203)) )
    {
      sleepMs = 0;
      if ( AviPlayer_CatchUpToTargetFrame(self) )
      {
        timeGetTime();
        nextFrameTimeMs = (double)*(unsigned int *)(self + 31)
           * ((double)(*(_DWORD *)(self + 2021) + 1)
            * g_CAviDecompressor_MillisecondsPerSecond)
           / (double)*(unsigned int *)(self + 35);
        _CHP(ExceptionList, v6);
        if ( (int)nextFrameTimeMs - v4 + 1 > 0 )
          sleepMs = (int)nextFrameTimeMs - v4 + 1;
      }
      Sleep(sleepMs);
      *(_DWORD *)(self + 2038) += sleepMs;
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
    CAviDecompressor_RenderLoop((int)lpThreadParameter);
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
  AviException_RebuildClipperOnSurfaceLoss(self, (int)&j____wcpp_4_fs_handler_rtn_, (int)&g_AviBeginPlayback_EHFrame, 0);
  *(_DWORD *)(self + 2183) = 0;
  *(_DWORD *)(self + 2034) = 0;
  *(_DWORD *)(self + 2038) = 0;
  AviPlayer_CatchUpToTargetFrame(self);
  *(_BYTE *)(self + 2) = 1;
  *(_DWORD *)(self + 2187) = timeGetTime();
  CSS_ResumeStream(*(_DWORD *)(self + 359));
  *(_BYTE *)(self + 2191) = 1;
  ResumeThread(*(HANDLE *)(self + 2192));
  return ExceptionList;
}

//----- (00466580) --------------------------------------------------------
BOOL  CAviDecompressor_RequestRenderStop(int self)
{
  *(_BYTE *)(self + 2191) = 0;
  return SetEvent(*(HANDLE *)(self + 2196));
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
  int *v11; // [esp-4h] [ebp-100h]
  int *v12; // [esp-4h] [ebp-100h]

  if ( *(_BYTE *)(self + 2191) )
  {
    CAviDecompressor_RequestRenderStop(self);
    WaitForSingleObject(*(HANDLE *)(self + 2228), 0x7D0u);
    ++*(_DWORD *)(self + 2200);
    EnterCriticalSection((LPCRITICAL_SECTION)(self + 2204));
    LeaveCriticalSection((LPCRITICAL_SECTION)(self + 2204));
    --*(_DWORD *)(self + 2200);
  }
  else
  {
    ResumeThread(*(HANDLE *)(self + 2192));
  }
  CAviDecompressor_RequestDecodeThreadStop(self);
  AviPlayer_CloseStreams(self);
  v2 = self;
  if ( *(_BYTE *)(self + 1968) )
  {
    overlaySurface = *(_DWORD *)(self + 1964);
    if ( overlaySurface )
    {
      hideResult = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(*(_DWORD *)overlaySurface + 132))(
             overlaySurface,
             self + 2095,
             *(_DWORD *)(self + 1956),
             self + 2063,
             512,
             0);
      if ( hideResult )
      {
        if ( hideResult != -2005532222
          || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 96))(*(_DWORD *)(self + 1964)) != -2005532222
           || (v11 = *(int **)(self + 1964), v2 = *v11, !(*(int (__stdcall **)(int *))(*v11 + 108))(v11)))
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 96))(*(_DWORD *)(self + 1956)) != -2005532222
           || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956)))
          && (v10 = *(int **)(self + 1964),
              v2 = *v10,
              (*(int (__stdcall **)(int *, int, _DWORD, int, int, _DWORD))(*v10 + 132))(
                v10,
                self + 2095,
                *(_DWORD *)(self + 1956),
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
  *(_DWORD *)(self + 2179) = 0;
  j_j__nfree_();
  sourceSurface = *(_DWORD *)(self + 1952);
  *(_DWORD *)(self + 2058) = 0;
  if ( sourceSurface && *(_DWORD *)(self + 1956) )
  {
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 8))(*(_DWORD *)(self + 1956));
    *(_DWORD *)(self + 1956) = 0;
    *(_DWORD *)(self + 1952) = 0;
  }
  else
  {
    *(_DWORD *)(self + 1956) = 0;
    *(_DWORD *)(self + 1952) = 0;
  }
  overlayIface = *(_DWORD *)(self + 1964);
  if ( overlayIface )
  {
    v2 = *(_DWORD *)overlayIface;
    (*(void (__stdcall **)(int))(*(_DWORD *)overlayIface + 8))(overlayIface);
    overlaySurface1 = *(_DWORD *)(self + 1960);
    *(_DWORD *)(self + 1964) = 0;
    if ( overlaySurface1 )
      (*(void (__stdcall **)(int))(*(_DWORD *)overlaySurface1 + 8))(overlaySurface1);
    *(_DWORD *)(self + 1960) = 0;
  }
  else
  {
    *(_DWORD *)(self + 1960) = 0;
  }
  backSurface = *(_DWORD *)(self + 2017);
  if ( backSurface && *(_DWORD *)(self + 2013) )
  {
    (*(void (__stdcall **)(int, _DWORD))(*(_DWORD *)backSurface + 152))(backSurface, 0);
    (*(void (__stdcall **)(int))(*(_DWORD *)backSurface + 8))(backSurface);
    v12 = (int *)(uintptr_t)*(unsigned int *)(self + 2013);
    v2 = *v12;
    (*(void (__stdcall **)(int *))(*v12 + 8))(v12);
    *(_DWORD *)(self + 2013) = 0;
    *(_DWORD *)(self + 2017) = 0;
  }
  else
  {
    *(_DWORD *)(self + 2013) = 0;
    *(_DWORD *)(self + 2017) = 0;
  }
  return CAviDecompressor_CloseCodecHandle((_DWORD *)(self + 415), backSurface, v2);
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
        __int64 a31)
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

  *(_DWORD *)((char *)&a31 + 6) = frameBits;
  blitState = self + 481;
  if ( blitState[5] || blitState[4] )
  {
    surfaceDesc[0] = 108;
    lockResult = (*(int (__stdcall **)(int, int *, _DWORD *, int, _DWORD))(*(_DWORD *)surface + 100))(surface, destRect, surfaceDesc, 1, 0);
    if ( !lockResult
      || lockResult == -2005532222
      && ((*(int (__stdcall **)(int))(*(_DWORD *)surface + 108))(surface)
       || !(*(int (__stdcall **)(int, int *, _DWORD *, int, _DWORD))(*(_DWORD *)surface + 100))(surface, destRect, surfaceDesc, 1, 0)) )
    {
      if ( (int)self[484] < 0 )
        signedPitch = -surfacePitch;
      else
        signedPitch = surfacePitch;
      self[484] = signedPitch;
      CAviDecompressor_BlitRows(self + 481, surfaceBits, *(char **)((char *)&a31 + 6));
      result = (*(int (__stdcall **)(int, char *))(*(_DWORD *)surface + 128))(surface, surfaceBits);
      if ( result )
      {
        if ( result != -2005532222
          || (result = (*(int (__stdcall **)(int))(*(_DWORD *)surface + 108))(surface)) == 0
          && (result = (*(int (__stdcall **)(int, char *))(*(_DWORD *)surface + 128))(surface, surfaceBits)) != 0 )
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
    dcResult = (*(int (__stdcall **)(int, char *))(*(_DWORD *)surface + 68))(surface, (char *)&a31 + 2);
    if ( !dcResult
      || dcResult == -2005532222
      && ((*(int (__stdcall **)(int))(*(_DWORD *)surface + 108))(surface)
       || !(*(int (__stdcall **)(int, char *))(*(_DWORD *)surface + 68))(surface, (char *)&a31 + 2)) )
    {
      if ( *(_DWORD *)((char *)self + 415) )
        bitmapInfo = (const BITMAPINFO *)((char *)self + 423);
      else
        bitmapInfo = *(const BITMAPINFO **)((char *)self + 151);
      StretchDIBits(
        *(HDC *)((char *)&a31 + 2),
        *destRect,
        destRect[1],
        destRect[2] - *destRect,
        destRect[3] - destRect[1],
        0,
        0,
        *(_DWORD *)(*(_DWORD *)((char *)self + 151) + 4),
        abs32(*(_DWORD *)(*(_DWORD *)((char *)self + 151) + 8)),
        *(const void **)((char *)&a31 + 6),
        bitmapInfo,
        0,
        0xCC0020u);
      result = (*(int (__stdcall **)(int, _DWORD))(*(_DWORD *)surface + 104))(surface, *(_DWORD *)((char *)&a31 + 2));
      if ( result )
      {
        if ( result != -2005532222
          || (result = (*(int (__stdcall **)(int))(*(_DWORD *)surface + 108))(surface)) == 0
          && (result = (*(int (__stdcall **)(int, _DWORD))(*(_DWORD *)surface + 104))(surface, *(_DWORD *)((char *)&a31 + 2))) != 0 )
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
  v6 = *(unsigned int *)(self + 35);
  elapsedScaled = ((double)Time - (double)*(int *)(self + 2187)) * (double)v6;
  LODWORD(v6) = *(_DWORD *)(self + 31);
  targetFrame = elapsedScaled / ((double)v6 * g_AviPlayer_MillisecondsPerSecond);
  _CHP(Time, 0);
  *(_DWORD *)(self + 2183) = (int)targetFrame;
  return *(_DWORD *)(self + 43) > *(_DWORD *)(self + 2183);
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

  if ( *(_DWORD *)(self + 2183) != *(_DWORD *)(self + 2021) )
  {
    frameQueuePtr = self + 203;
    if ( *(char *)(self + 2033) <= 0 )
    {
      busyGuardPtr = self + 1985;
      ++*(_DWORD *)(self + 1985);
      EnterCriticalSection((LPCRITICAL_SECTION)(self + 1989));
      if ( *(_DWORD *)(self + 2034) )
      {
        v49 = frameQueuePtr;
        do
        {
          if ( *(int *)(self + 2034) > 0 )
          {
            AviPlayer_IncrementFramesRenderedCount(v49);
            AviPlayer_PulseEventHandle(v50);
            --*(_DWORD *)(self + 2034);
          }
        }
        while ( *(_DWORD *)(self + 2034) );
      }
      frameData = AviPlayer_GetBufferedAudioSample(self, *(_DWORD *)(self + 2183), (_DWORD *)(self + 2029), (_DWORD *)(self + 2021));
      *(_DWORD *)(self + 2025) = frameData;
      if ( frameData )
        ++*(_DWORD *)(self + 2034);
      busyGuard = busyGuardPtr;
    }
    else
    {
      if ( *(_DWORD *)(self + 2034) )
      {
        frameQueue = self + 203;
        do
        {
          if ( *(int *)(self + 2034) > 0 )
          {
            AviPlayer_IncrementFramesRenderedCount(frameQueue);
            AviPlayer_PulseEventHandle(v3);
            --*(_DWORD *)(self + 2034);
          }
        }
        while ( *(_DWORD *)(self + 2034) );
      }
      frameDataPtr = AviPlayer_GetBufferedAudioSample(self, *(_DWORD *)(self + 2183), (_DWORD *)(self + 2029), (_DWORD *)(self + 2021));
      *(_DWORD *)(self + 2025) = frameDataPtr;
      if ( !frameDataPtr )
        return 0;
      ++*(_DWORD *)(self + 2034);
      ++*(_DWORD *)(self + 1985);
      EnterCriticalSection((LPCRITICAL_SECTION)(self + 1989));
      flipState = *(_BYTE *)(self + 2033);
      codecPtr = (_DWORD *)(self + 415);
      if ( flipState >= 2u )
      {
        if ( flipState <= 2u )
        {
          if ( *codecPtr )
          {
            backSurface = *(_DWORD *)(self + 2017);
            surfaceDesc[0] = 108;
            lockResult = (*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)backSurface + 100))(backSurface, 0, surfaceDesc, 33, 0);
            if ( !lockResult
              || lockResult == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)backSurface + 108))(backSurface)
               || !(*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)backSurface + 100))(backSurface, 0, surfaceDesc, 33, 0)) )
            {
              CAviDecompressor_GetVideoFormat(self);
              videoWidth = *(_DWORD *)(CAviDecompressor_GetVideoFormat(self) + 4);
              lockedBitsSaved = lockedBits;
              frameBits = *(_DWORD *)(self + 2025);
              frameFlags = *(_DWORD *)(self + 2029);
              pitchPixels = surfaceDesc[4] / ((*(_DWORD *)(self + 2123) + 7) >> 3);
              *(_DWORD *)(AviPlayer_StreamBitmapInfoPtr(self + 415) + 4) = pitchPixels;
              pixelCountBack = videoHeightBack * pitchPixels;
              v26 = AviPlayer_StreamBitmapInfoPtr(v25);
              imageBytes = Mem_BitsToBytesCeil(*(unsigned __int16 *)(v26 + 14)) * pixelCountBack;
              v29 = AviPlayer_StreamBitmapInfoPtr(v28);
              v53 = v30;
              *(_DWORD *)(v29 + 20) = imageBytes;
              bitmapInfoHeaderBack = AviPlayer_StreamBitmapInfoPtr(v31);
              if ( AviPlayer_SendICDrawBegin(
                     *drawContextBack,
                     frameFlags,
                     drawContextBack[1],
                     frameBits,
                     0,
                     0,
                     *(_DWORD *)(drawContextBack[1] + 4),
                     *(_DWORD *)(drawContextBack[1] + 8),
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
              unlockResult = (*(int (__stdcall **)(int, int))(*(_DWORD *)backSurface + 128))(backSurface, lockedBits);
              if ( unlockResult
                && (unlockResult != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)backSurface + 108))(backSurface)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)backSurface + 128))(backSurface, lockedBits)) )
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
              (_DWORD *)self,
              *(_DWORD *)(self + 2017),
              *(_DWORD *)(self + 2025),
              (int *)(self + 2095),
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
            overlaySurface = *(_DWORD *)(self + 1964);
            overlayDesc[0] = 108;
            lockResultOvl = (*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)overlaySurface + 100))(overlaySurface, 0, overlayDesc, 33, 0);
            if ( !lockResultOvl
              || lockResultOvl == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)overlaySurface + 108))(overlaySurface)
               || !(*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)overlaySurface + 100))(overlaySurface, 0, overlayDesc, 33, 0)) )
            {
              CAviDecompressor_GetVideoFormat(self);
              videoWidthOvl = *(_DWORD *)(CAviDecompressor_GetVideoFormat(self) + 4);
              lockedBitsOvlSaved = overlayLockedBits;
              frameBitsOvl = *(_DWORD *)(self + 2025);
              frameFlagsOvl = *(_DWORD *)(self + 2029);
              pitchPixelsOvl = overlayDesc[4] / ((*(_DWORD *)(self + 2123) + 7) >> 3);
              *(_DWORD *)(AviPlayer_StreamBitmapInfoPtr(self + 415) + 4) = pitchPixelsOvl;
              pixelCountOvl = videoHeightOvl * pitchPixelsOvl;
              v40 = AviPlayer_StreamBitmapInfoPtr(v39);
              imageBytesOvl = Mem_BitsToBytesCeil(*(unsigned __int16 *)(v40 + 14)) * pixelCountOvl;
              v43 = AviPlayer_StreamBitmapInfoPtr(v42);
              v54 = v44;
              *(_DWORD *)(v43 + 20) = imageBytesOvl;
              bitmapInfoHeaderOvl = AviPlayer_StreamBitmapInfoPtr(v45);
              if ( AviPlayer_SendICDrawBegin(
                     *drawContextOvl,
                     frameFlagsOvl,
                     drawContextOvl[1],
                     frameBitsOvl,
                     0,
                     0,
                     *(_DWORD *)(drawContextOvl[1] + 4),
                     *(_DWORD *)(drawContextOvl[1] + 8),
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
              unlockResultOvl = (*(int (__stdcall **)(int, int))(*(_DWORD *)overlaySurface + 128))(overlaySurface, overlayLockedBits);
              if ( unlockResultOvl
                && (unlockResultOvl != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)overlaySurface + 108))(overlaySurface)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)overlaySurface + 128))(overlaySurface, overlayLockedBits)) )
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
              (_DWORD *)self,
              *(_DWORD *)(self + 1964),
              *(_DWORD *)(self + 2025),
              (int *)(self + 2095),
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
        decodeBuffer = *(_DWORD *)(self + 2179);
        frameBitsSw = *(_DWORD *)(self + 2025);
        frameFlagsSw = *(_DWORD *)(self + 2029);
        if ( *(_BYTE *)(self + 1923) )
        {
          decodedWidth = *(_DWORD *)(self + 427);
          *(_DWORD *)(AviPlayer_StreamBitmapInfoPtr(self + 415) + 4) = decodedWidth;
          pixelCountSw = decodedWidth * videoHeight;
          v10 = AviPlayer_StreamBitmapInfoPtr(v9);
          imageBytesSw = Mem_BitsToBytesCeil(*(unsigned __int16 *)(v10 + 14)) * pixelCountSw;
          v13 = AviPlayer_StreamBitmapInfoPtr(v12);
          v52 = v14;
          *(_DWORD *)(v13 + 20) = imageBytesSw;
          bitmapInfoHeaderSw = AviPlayer_StreamBitmapInfoPtr(v15);
          if ( AviPlayer_SendICDrawBegin(
                 *drawContextSw,
                 frameFlagsSw,
                 drawContextSw[1],
                 frameBitsSw,
                 0,
                 0,
                 *(_DWORD *)(drawContextSw[1] + 4),
                 *(_DWORD *)(drawContextSw[1] + 8),
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
                    *(_DWORD *)(self + 415),
                    *(_DWORD *)(self + 2029),
                    *(_DWORD *)(self + 419),
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
      if ( *(int *)(self + 2034) > 0 )
      {
        ++*(_DWORD *)(self + 207);
        PulseEvent(*(HANDLE *)(self + 171));
        --*(_DWORD *)(self + 2034);
      }
      busyGuard = self + 1985;
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(busyGuard + 4));
    --*(_DWORD *)busyGuard;
    SetEvent(*(HANDLE *)(self + 2196));
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

//----- (004674A0) --------------------------------------------------------
int  AviPlayer_Flip(int self)
{
  int v2; // edx
  int overlaySurface; // edi
  int v4; // ebx
  int *srcRectPtr; // ebp
  int lockResult; // eax
  int rectLeft; // ecx
  int rectRight; // ebp
  int destWidth; // ebp
  int bytesPerPixel; // eax
  int v11; // edx
  int unlockResult; // eax
  _DWORD *busyGuard; // ebx
  int result; // eax
  int srcWidth; // ebx
  int stretchRatio; // eax
  int v17; // edx
  int v18; // ebx
  int backSurface; // edi
  int overlayLockResult; // eax
  int bitmapWidth; // ebp
  int v22; // edx
  int v23; // ecx
  int overlayUnlockResult; // eax
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int framePtr; // ecx
  int decodedFrameBuffer; // ecx
  int srcSpan; // ecx
  int stretchRate; // eax
  int v32; // edx
  int overlayCapsAlt; // eax
  int requiredCapsAlt; // eax
  int overlayIface; // eax
  int flipResult; // eax
  int v37; // ecx
  int overlayCaps; // eax
  int requiredCaps; // eax
  int frameData; // [esp+10h] [ebp-51Ch]
  int frameBits; // [esp+10h] [ebp-51Ch]
  int frameFlags; // [esp+14h] [ebp-518h]
  int drawFlags; // [esp+14h] [ebp-518h]
  int surfaceDesc; // [esp+18h] [ebp-514h] BYREF
  int v45; // [esp+1Ch] [ebp-510h]
  int v46; // [esp+20h] [ebp-50Ch]
  int v47; // [esp+24h] [ebp-508h]
  int v48; // [esp+28h] [ebp-504h]
  int v49; // [esp+2Ch] [ebp-500h]
  int v50; // [esp+30h] [ebp-4FCh]
  int v51; // [esp+34h] [ebp-4F8h]
  int v52; // [esp+38h] [ebp-4F4h]
  int v53; // [esp+3Ch] [ebp-4F0h]
  int v54; // [esp+40h] [ebp-4ECh]
  int v55; // [esp+44h] [ebp-4E8h]
  int v56; // [esp+48h] [ebp-4E4h]
  int v57; // [esp+4Ch] [ebp-4E0h]
  int v58; // [esp+50h] [ebp-4DCh]
  int v59; // [esp+54h] [ebp-4D8h]
  int v60; // [esp+58h] [ebp-4D4h]
  int v61; // [esp+5Ch] [ebp-4D0h]
  int v62; // [esp+60h] [ebp-4CCh]
  int v63; // [esp+64h] [ebp-4C8h]
  int v64; // [esp+68h] [ebp-4C4h]
  int v65; // [esp+6Ch] [ebp-4C0h]
  int v66; // [esp+70h] [ebp-4BCh]
  int v67; // [esp+74h] [ebp-4B8h]
  int v68; // [esp+78h] [ebp-4B4h]
  int v69; // [esp+7Ch] [ebp-4B0h]
  __int64 lockDesc[2]; // [esp+80h] [ebp-4ACh] BYREF
  int v71; // [esp+A8h] [ebp-484h]
  int (**v72)(); // [esp+154h] [ebp-3D8h]
  int v73; // [esp+1BCh] [ebp-370h]
  int (**v74)(); // [esp+224h] [ebp-308h]
  int v75; // [esp+28Ch] [ebp-2A0h]
  int (**v76)(); // [esp+2F4h] [ebp-238h]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+4ECh] [ebp-40h]
  tagRECT *v78; // [esp+4F0h] [ebp-3Ch]
  void *v79; // [esp+4F4h] [ebp-38h]
  int v80; // [esp+4F8h] [ebp-34h]
  int busyGuardAddr; // [esp+500h] [ebp-2Ch]
  int backLockedBits; // [esp+504h] [ebp-28h]
  int v83; // [esp+508h] [ebp-24h]
  int overlayLockedBits; // [esp+50Ch] [ebp-20h]
  char flipState; // [esp+510h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v78 = &j____wcpp_4_fs_handler_rtn_;
  v79 = &g_AviPlayerFlip_EHFrame;
  v80 = 0;
  flipState = *(_BYTE *)(self + 2033);
  busyGuardAddr = self + 1985;
  ++*(_DWORD *)(self + 1985);
  EnterCriticalSection((LPCRITICAL_SECTION)(self + 1989));
  v80 = 1;
  if ( (unsigned __int8)flipState > 3u )
  {
LABEL_19:
    v80 = 0;
    busyGuard = (_DWORD *)busyGuardAddr;
    LeaveCriticalSection((LPCRITICAL_SECTION)(busyGuardAddr + 4));
    result = (*busyGuard)--;
    if ( (unsigned __int8)flipState >= 2u )
    {
      if ( (unsigned __int8)flipState > 2u )
      {
        if ( flipState != 3 )
          return result;
      }
      else
      {
        if ( !*(_BYTE *)(self + 1968)
          || !*(_DWORD *)(self + 1964)
          || (srcWidth = *(_DWORD *)(self + 2087) - *(_DWORD *)(self + 2079),
              stretchRatio = 1000 * (*(_DWORD *)(self + 2071) - *(_DWORD *)(self + 2063)) / srcWidth,
              v17 = 1000 * (*(_DWORD *)(self + 2071) - *(_DWORD *)(self + 2063)) % srcWidth,
              stretchRatio < *(_DWORD *)(self + 2143))
          || stretchRatio > *(_DWORD *)(self + 2147) )
        {
          if ( !*(_DWORD *)(self + 1964) )
            return AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(self + 2017));
          overlayCaps = *(_DWORD *)(self + 2171);
          LOBYTE(overlayCaps) = overlayCaps | 2;
          requiredCaps = *(_DWORD *)(self + 2175) | overlayCaps;
          v17 = requiredCaps & *(_DWORD *)(self + 2119);
          if ( v17 != requiredCaps )
            return AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(self + 2017));
        }
        result = AviPlayer_BltFastOverlayFromBackBuffer(self, v17);
      }
      if ( !*(_BYTE *)(self + 1968) || !*(_DWORD *)(self + 1964) )
        return AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(self + 1964));
    }
  }
  else
  {
    switch ( flipState )
    {
      case 0:
        if ( !*(_DWORD *)(self + 2025) )
          goto LABEL_86;
        if ( *(_DWORD *)(self + 415) )
        {
          v2 = self;
          if ( (!*(_BYTE *)(self + 2052) || AviPlayer_TestActiveModeFlag(self))
            && (*(_BYTE *)(self + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(self))
            && (AviPlayer_HasValidRateParams(self) && AviPlayer_IsPlaybackRateInRange(self) || *(_DWORD *)(self + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(self)) )
          {
            overlaySurface = *(_DWORD *)(v2 + 1964);
            v4 = v2;
            srcRectPtr = (int *)(v2 + 2095);
            surfaceDesc = 108;
            lockResult = (*(int (__stdcall **)(int, int, int *, int, _DWORD))(*(_DWORD *)overlaySurface + 100))(overlaySurface, v2 + 2095, &surfaceDesc, 33, 0);
            if ( !lockResult
              || lockResult == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)overlaySurface + 108))(overlaySurface)
               || !(*(int (__stdcall **)(int, int *, int *, int, _DWORD))(*(_DWORD *)overlaySurface + 100))(overlaySurface, srcRectPtr, &surfaceDesc, 33, 0)) )
            {
              v83 = srcRectPtr[3] - srcRectPtr[1];
              rectLeft = *srcRectPtr;
              rectRight = srcRectPtr[2];
              overlayLockedBits = v53;
              frameFlags = *(_DWORD *)(v4 + 2029);
              destWidth = rectRight - rectLeft;
              frameData = *(_DWORD *)(v4 + 2025);
              bytesPerPixel = Mem_BitsToBytesCeil(*(_DWORD *)(v4 + 2123));
              AviPlayer_UpdateStreamRectAndSendICDrawBegin((int *)(v4 + 415), overlayLockedBits, v83, destWidth, v11 / bytesPerPixel, frameData, frameFlags);
              unlockResult = (*(int (__stdcall **)(int, int))(*(_DWORD *)overlaySurface + 128))(overlaySurface, v53);
              if ( unlockResult
                && (unlockResult != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)overlaySurface + 108))(overlaySurface)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)overlaySurface + 128))(overlaySurface, v53)) )
              {
                ExcString_Ctor();
                v80 = 8;
                ExcString_Ctor();
                v73 = v27;
                v80 = 1;
                CRT_ThrowExcStringException();
              }
            }
            else
            {
              ExcString_Ctor();
              v80 = v26;
              ExcString_Ctor();
              v76 = g_AviException_VTable;
              v80 = 1;
              CRT_ThrowExcStringException();
            }
            v80 = 0;
            flipState = 3;
          }
          else
          {
            v18 = v2;
            backSurface = *(_DWORD *)(v2 + 2017);
            HIDWORD(lockDesc[0]) = 108;
            overlayLockResult = (*(int (__stdcall **)(int, _DWORD, char *, int, _DWORD))(*(_DWORD *)backSurface + 100))(
                    backSurface,
                    0,
                    (char *)lockDesc + 4,
                    33,
                    0);
            if ( !overlayLockResult
              || overlayLockResult == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)backSurface + 108))(backSurface)
               || !(*(int (__stdcall **)(int, _DWORD, char *, int, _DWORD))(*(_DWORD *)backSurface + 100))(
                     backSurface,
                     0,
                     (char *)lockDesc + 4,
                     33,
                     0)) )
            {
              AviPlayer_BitmapHeightAbs(v18);
              bitmapWidth = AviPlayer_BitmapWidth(v18);
              backLockedBits = v71;
              drawFlags = *(_DWORD *)(v18 + 2029);
              frameBits = *(_DWORD *)(v18 + 2025);
              v83 = Mem_BitsToBytesCeil(*(_DWORD *)(v18 + 2123));
              AviPlayer_UpdateStreamRectAndSendICDrawBegin((int *)(v18 + 415), backLockedBits, v23, bitmapWidth, v22 / v83, frameBits, drawFlags);
              overlayUnlockResult = (*(int (__stdcall **)(int, int))(*(_DWORD *)backSurface + 128))(backSurface, v71);
              if ( overlayUnlockResult
                && (overlayUnlockResult != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)backSurface + 108))(backSurface)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)backSurface + 128))(backSurface, v71)) )
              {
                ExcString_Ctor();
                v80 = 4;
                ExcString_Ctor();
                v74 = g_AviException_VTable;
                v80 = 1;
                CRT_ThrowExcStringException();
              }
            }
            else
            {
              ExcString_Ctor();
              v80 = v25;
              ExcString_Ctor();
              v72 = g_AviException_VTable;
              v80 = 1;
              CRT_ThrowExcStringException();
            }
            v80 = 0;
            flipState = 2;
          }
        }
        else
        {
          framePtr = *(_DWORD *)(self + 2025);
          if ( (!*(_BYTE *)(self + 2052) || AviPlayer_TestActiveModeFlag(self))
            && (*(_BYTE *)(self + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(self))
            && (AviPlayer_HasValidRateParams(self) && AviPlayer_IsPlaybackRateInRange(self) || *(_DWORD *)(self + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(self)) )
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)self,
              *(_DWORD *)(self + 1964),
              framePtr,
              (int *)(self + 2095),
              surfaceDesc,
              v45,
              v46,
              v47,
              v48,
              v49,
              v50,
              v51,
              v52,
              v53,
              v54,
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
              lockDesc[0]);
            flipState = 3;
          }
          else
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)self,
              *(_DWORD *)(self + 2017),
              framePtr,
              (int *)(self + 2095),
              surfaceDesc,
              v45,
              v46,
              v47,
              v48,
              v49,
              v50,
              v51,
              v52,
              v53,
              v54,
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
              lockDesc[0]);
            flipState = 2;
          }
        }
        if ( *(int *)(self + 2034) > 0 )
        {
          ++*(_DWORD *)(self + 207);
          PulseEvent(*(HANDLE *)(self + 171));
          --*(_DWORD *)(self + 2034);
        }
        goto LABEL_19;
      case 1:
        decodedFrameBuffer = *(_DWORD *)(self + 2179);
        if ( (!*(_BYTE *)(self + 2052) || AviPlayer_TestActiveModeFlag(self))
          && (*(_BYTE *)(self + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(self))
          && (AviPlayer_HasValidRateParams(self) && AviPlayer_IsPlaybackRateInRange(self) || *(_DWORD *)(self + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(self)) )
        {
          AviPlayer_BlitFrameToSurface(
            (_DWORD *)self,
            *(_DWORD *)(self + 1964),
            decodedFrameBuffer,
            (int *)(self + 2095),
            surfaceDesc,
            v45,
            v46,
            v47,
            v48,
            v49,
            v50,
            v51,
            v52,
            v53,
            v54,
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
            lockDesc[0]);
          flipState = 3;
        }
        else
        {
          AviPlayer_BlitFrameToSurface(
            (_DWORD *)self,
            *(_DWORD *)(self + 2017),
            decodedFrameBuffer,
            (int *)(self + 2095),
            surfaceDesc,
            v45,
            v46,
            v47,
            v48,
            v49,
            v50,
            v51,
            v52,
            v53,
            v54,
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
            lockDesc[0]);
          flipState = 2;
        }
        goto LABEL_19;
      case 2:
        if ( *(_BYTE *)(self + 1968)
          && *(_DWORD *)(self + 1964)
          && (srcSpan = *(_DWORD *)(self + 2087) - *(_DWORD *)(self + 2079),
              stretchRate = 1000 * (*(_DWORD *)(self + 2071) - *(_DWORD *)(self + 2063)) / srcSpan,
              v32 = 1000 * (*(_DWORD *)(self + 2071) - *(_DWORD *)(self + 2063)) % srcSpan,
              stretchRate >= *(_DWORD *)(self + 2143))
          && stretchRate <= *(_DWORD *)(self + 2147)
          || *(_DWORD *)(self + 1964)
          && (overlayCapsAlt = *(_DWORD *)(self + 2171),
              LOBYTE(overlayCapsAlt) = overlayCapsAlt | 2,
              requiredCapsAlt = *(_DWORD *)(self + 2175) | overlayCapsAlt,
              v32 = requiredCapsAlt & *(_DWORD *)(self + 2119),
              v32 == requiredCapsAlt) )
        {
          AviPlayer_BltFastOverlayFromBackBuffer(self, v32);
          flipState = 3;
          goto LABEL_19;
        }
        AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(self + 2017));
        LeaveCriticalSection((LPCRITICAL_SECTION)(busyGuardAddr + 4));
        return (*(_DWORD *)busyGuardAddr)--;
      case 3:
        if ( !*(_BYTE *)(self + 1968) || (overlayIface = *(_DWORD *)(self + 1964)) == 0 )
        {
          AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(self + 1964));
LABEL_86:
          LeaveCriticalSection((LPCRITICAL_SECTION)(busyGuardAddr + 4));
          return (*(_DWORD *)busyGuardAddr)--;
        }
        if ( !*(_BYTE *)(self + 2051) )
          goto LABEL_86;
        flipResult = (*(int (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)overlayIface + 44))(overlayIface, 0, 0);
        if ( !flipResult
          || flipResult == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 108))(*(_DWORD *)(self + 1964))
           || !(*(int (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)(self + 1964) + 44))(
                 *(_DWORD *)(self + 1964),
                 0,
                 0)) )
        {
          goto LABEL_86;
        }
        ExcString_Ctor();
        ExcString_Ctor();
        v75 = v37;
        v80 = 1;
        result = CRT_ThrowExcStringException();
        break;
    }
  }
  return result;
}
// 4675AC: variable 'v2' is possibly undefined
// 46763D: variable 'v11' is possibly undefined
// 46786C: variable 'v23' is possibly undefined
// 46785C: variable 'v22' is possibly undefined
// 467918: variable 'v25' is possibly undefined
// 4679FD: variable 'v26' is possibly undefined
// 467A84: variable 'v27' is possibly undefined
// 467AEA: variable 'v28' is possibly undefined
// 467B8B: variable 'v29' is possibly undefined
// 467D64: variable 'v37' is possibly undefined
// 510374: using guessed type int (*off_510374[2])();

//----- (00467DE0) --------------------------------------------------------
int  AviException_RebuildClipperOnSurfaceLoss(int result, int a2, int a3, int srcSurface)
{
  _DWORD **self; // ebx
  int ddObject; // edx
  int hr; // eax
  int v7; // esi
  __int64 v8; // rax
  int restoreHr; // eax
  __int64 v10; // rax
  int v11; // ecx

  self = (_DWORD **)result;
  ddObject = *(_DWORD *)(result + 2151);
  if ( ddObject )
  {
    result = (*(int (**)(void))(*(_DWORD *)ddObject + 4))();
    if ( result )
    {
      restoreHr = (*(int (__stdcall **)(int, int, int))(**(_DWORD **)((char *)self + 2151) + 4))(srcSurface, a2, a3);
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)restoreHr + 96))(restoreHr) == -2005532222 )
        (*(void (**)(void))(**(_DWORD **)((char *)self + 2151) + 8))();
      v10 = ((__int64 (__thiscall *)(_DWORD, _DWORD, int, _DWORD))*(_DWORD *)(**(_DWORD **)((char *)self + 2151) + 4))(
              *self[489],
              0,
              0x1000000,
              0);
      return (*(int (__stdcall **)(_DWORD, int, _DWORD))(v11 + 20))(HIDWORD(v10), (int)self + 2155, v10);
    }
    else if ( self[488] )
    {
      result = (***(int (****)(void))((char *)self + 2151))();
      if ( result )
      {
        hr = (***(int (__stdcall ****)(int, int, int))((char *)self + 2151))(srcSurface, a2, a3);
        if ( (*(int (__stdcall **)(int))(*(_DWORD *)hr + 96))(hr) == -2005532222 )
          (*(void (**)(void))(**(_DWORD **)((char *)self + 2151) + 8))();
        v7 = *self[488];
        v8 = ((__int64 (__cdecl *)(_DWORD, int, _DWORD))***(_DWORD ***)((char *)self + 2151))(0, 0x1000000, 0);
        return (*(int (__stdcall **)(_DWORD, int, _DWORD))(v7 + 20))(HIDWORD(v8), (int)self + 2155, v8);
      }
    }
  }
  return result;
}
// 467DE0: could not find valid save-restore pair for esi
// 467EAD: variable 'v11' is possibly undefined

//----- (00467EC0) --------------------------------------------------------
int  AviPlayer_BltFastOverlayFromBackBuffer(int self, int a2)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(**(_DWORD **)(self + 1964) + 28))(
             *(_DWORD *)(self + 1964),
             0,
             0,
             *(_DWORD *)(self + 2017),
             0,
             0);
  if ( result )
  {
    if ( result == -2005532222 )
    {
      if ( (*(int (__stdcall **)(_DWORD, int))(**(_DWORD **)(self + 1964) + 96))(*(_DWORD *)(self + 1964), a2) == -2005532222 )
        (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 108))(*(_DWORD *)(self + 1964));
      if ( (*(int (__cdecl **)(_DWORD))(**(_DWORD **)(self + 2017) + 96))(*(_DWORD *)(self + 2017)) == -2005532222 )
        (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(self + 2017) + 108))(*(_DWORD *)(self + 2017));
    }
    return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int))(**(_DWORD **)(self + 1964) + 28))(
             *(_DWORD *)(self + 1964),
             0,
             0,
             *(_DWORD *)(self + 2017),
             0,
             16);
  }
  return result;
}

//----- (00467F50) --------------------------------------------------------
int  AviPlayer_BltFrameToPrimarySurface(int self, int srcSurface)
{
  int result; // eax
  int v5; // edx
  int v6; // ecx

  if ( *(_DWORD *)(self + 2175)
    || (result = (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1956) + 28))(
                   *(_DWORD *)(self + 1956),
                   *(_DWORD *)(self + 2063),
                   *(_DWORD *)(self + 2067),
                   srcSurface,
                   self + 2079,
                   *(_DWORD *)(self + 2115))) != 0 )
  {
    if ( (*(int (__stdcall **)(_DWORD, int, int, int, _DWORD, _DWORD))(**(_DWORD **)(self + 1956) + 20))(
           *(_DWORD *)(self + 1956),
           self + 2063,
           srcSurface,
           self + 2079,
           *(_DWORD *)(self + 2111),
           0) != -2005532222 )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(**(_DWORD **)(self + 1956) + 20))(
               *(_DWORD *)(self + 1956),
               self + 2063,
               srcSurface,
               self + 2079,
               *(_DWORD *)(self + 2111) | 0x1000000,
               0);
    if ( (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 96))(*(_DWORD *)(self + 1956)) == -2005532222 )
    {
      result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956));
      if ( result )
        return result;
      if ( *(_DWORD *)(self + 1948) )
        (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(self + 1956) + 124))(
          *(_DWORD *)(self + 1956),
          *(_DWORD *)(self + 1948));
      AviException_RebuildClipperOnSurfaceLoss(self, v5, v6, srcSurface);
    }
    if ( (*(int (__stdcall **)(int))(*(_DWORD *)srcSurface + 96))(srcSurface) != -2005532222 )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(**(_DWORD **)(self + 1956) + 20))(
               *(_DWORD *)(self + 1956),
               self + 2063,
               srcSurface,
               self + 2079,
               *(_DWORD *)(self + 2111) | 0x1000000,
               0);
    result = (*(int (__stdcall **)(int))(*(_DWORD *)srcSurface + 108))(srcSurface);
    if ( !result )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(**(_DWORD **)(self + 1956) + 20))(
               *(_DWORD *)(self + 1956),
               self + 2063,
               srcSurface,
               self + 2079,
               *(_DWORD *)(self + 2111) | 0x1000000,
               0);
  }
  return result;
}
// 468020: variable 'v5' is possibly undefined
// 468020: variable 'v6' is possibly undefined

//----- (00468060) --------------------------------------------------------
signed int  AviPlayer_RenderFrame(int self, const RECT *destRect)
{
  int destHeight; // esi
  signed int result; // eax
  int destWidth; // [esp+0h] [ebp-20h]
  int srcWidth; // [esp+4h] [ebp-1Ch]
  int srcHeight; // [esp+8h] [ebp-18h]

  *(_DWORD *)(self + 2063) = destRect->left;
  *(_DWORD *)(self + 2067) = destRect->top;
  *(_DWORD *)(self + 2071) = destRect->right;
  *(_DWORD *)(self + 2075) = destRect->bottom;
  *(_DWORD *)(self + 2079) = *(_DWORD *)(self + 2095);
  *(_DWORD *)(self + 2083) = *(_DWORD *)(self + 2099);
  *(_DWORD *)(self + 2087) = *(_DWORD *)(self + 2103);
  *(_DWORD *)(self + 2091) = *(_DWORD *)(self + 2107);
  srcWidth = *(_DWORD *)(self + 2087) - *(_DWORD *)(self + 2079);
  destHeight = destRect->bottom - destRect->top;
  srcHeight = *(_DWORD *)(self + 2091) - *(_DWORD *)(self + 2083);
  destWidth = destRect->right - destRect->left;
  IntersectRect((LPRECT)(self + 2063), destRect, (const RECT *)(self + 1969));
  result = IsRectEmpty((const RECT *)(self + 2063));
  if ( !result )
  {
    if ( !EqualRect((const RECT *)(self + 2063), destRect) )
    {
      *(_DWORD *)(self + 2079) += srcWidth * (*(_DWORD *)(self + 2063) - destRect->left) / destWidth;
      *(_DWORD *)(self + 2087) += srcWidth * (*(_DWORD *)(self + 2071) - destRect->right) / destWidth;
      *(_DWORD *)(self + 2083) += srcHeight * (*(_DWORD *)(self + 2067) - destRect->top) / destHeight;
      *(_DWORD *)(self + 2091) += srcHeight * (*(_DWORD *)(self + 2075) - destRect->bottom) / destHeight;
    }
    if ( srcWidth == destWidth && destHeight == srcHeight )
    {
      result = destWidth ^ srcWidth;
      *(_DWORD *)(self + 2175) = destWidth ^ srcWidth;
    }
    else
    {
      result = 4;
      *(_DWORD *)(self + 2175) = 4;
    }
  }
  return result;
}

//----- (004681C0) --------------------------------------------------------
int  CAviDecompressor_PresentFrameIfStale(int self, const RECT *destRect)
{
  int result; // eax
  int destWidthScaled; // edi
  int v6; // ecx
  int stretchRatio; // eax
  int showFlags; // eax
  int overlayFlags; // ebp
  int updateResult; // eax
  int overlaySurface; // ecx
  int hideResult; // eax

  if ( !*(_BYTE *)(self + 2053) || (result = *(_DWORD *)(self + 2054), result < *(_DWORD *)(self + 2021)) )
  {
    result = WaitForSingleObject(*(HANDLE *)(self + 2196), 0);
    if ( !result )
    {
      if ( !*(_BYTE *)(self + 2062) )
        AviPlayer_RenderFrame(self, destRect);
      AviPlayer_Flip(self);
      if ( !*(_BYTE *)(self + 1968) || !*(_DWORD *)(self + 1964) )
        goto LABEL_22;
      destWidthScaled = 1000 * AviPlayer_SpanDelta(self, (_DWORD *)(self + 2063));
      stretchRatio = destWidthScaled / AviPlayer_SpanDelta(v6, (_DWORD *)(self + 2079));
      if ( stretchRatio < *(_DWORD *)(self + 2143) || stretchRatio > *(_DWORD *)(self + 2147) )
      {
        if ( !*(_BYTE *)(self + 1968) )
          goto LABEL_22;
        overlaySurface = *(_DWORD *)(self + 1964);
        if ( !overlaySurface )
          goto LABEL_22;
        hideResult = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(*(_DWORD *)overlaySurface + 132))(
                overlaySurface,
                self + 2095,
                *(_DWORD *)(self + 1956),
                self + 2063,
                512,
                0);
        if ( !hideResult )
          goto LABEL_22;
        if ( hideResult == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 96))(*(_DWORD *)(self + 1964)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 108))(*(_DWORD *)(self + 1964))
           || (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 96))(*(_DWORD *)(self + 1956)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956))
           || !(*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                 *(_DWORD *)(self + 1964),
                 self + 2095,
                 *(_DWORD *)(self + 1956),
                 self + 2063,
                 512,
                 0)) )
        {
          goto LABEL_22;
        }
        ExcString_Ctor();
        AviException_CtorForDrawFailure();
      }
      else
      {
        showFlags = 0x4000;
        if ( *(_DWORD *)(self + 2171) )
          showFlags = 20480;
        overlayFlags = showFlags;
        updateResult = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                *(_DWORD *)(self + 1964),
                self + 2095,
                *(_DWORD *)(self + 1956),
                self + 2063,
                showFlags,
                0);
        if ( !updateResult
          || updateResult == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 96))(*(_DWORD *)(self + 1964)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 108))(*(_DWORD *)(self + 1964))
           || (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 96))(*(_DWORD *)(self + 1956)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956))
           || !(*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                 *(_DWORD *)(self + 1964),
                 self + 2095,
                 *(_DWORD *)(self + 1956),
                 self + 2063,
                 overlayFlags,
                 0)) )
        {
          goto LABEL_22;
        }
        ExcString_Ctor();
        ExcString_Ctor();
      }
      CRT_ThrowExcStringException();
LABEL_22:
      ResetEvent(*(HANDLE *)(self + 2196));
      result = *(_DWORD *)(self + 2021);
      *(_DWORD *)(self + 2054) = result;
    }
  }
  return result;
}
// 468281: conditional instruction was optimized away because dh.1!=0
// 4682CF: variable 'v6' is possibly undefined

//----- (00468890) --------------------------------------------------------
int  CAviDecompressor_PresentFrameForRect(int a1, const RECT *destRect)
{
  int v2; // ecx
  int result; // eax
  int self; // ebx
  int destWidthScaled; // esi
  int v6; // ecx
  int v7; // ecx
  int showFlags; // eax
  int overlayFlags; // edi
  int v10; // ecx
  _DWORD v11[3]; // [esp+198h] [ebp-24h] BYREF
  int v12; // [esp+1A4h] [ebp-18h]

  v2 = a1;
  result = (int)v11;
  v11[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v11[1] = &j____wcpp_4_fs_handler_rtn_;
  v11[2] = &g_AviPresentFrameForRect_EHFrame;
  v12 = 0;
  if ( !*(_BYTE *)(v2 + 2062) )
    result = AviPlayer_RenderFrame(v2, destRect);
  self = v2;
  if ( *(_BYTE *)(v2 + 1968) && *(_DWORD *)(v2 + 1964) )
  {
    destWidthScaled = 1000 * AviPlayer_SpanDelta(v2, (_DWORD *)(v2 + 2063));
    result = destWidthScaled / AviPlayer_SpanDelta(v6, (_DWORD *)(v6 + 2079));
    if ( result < *(_DWORD *)(v7 + 2143) || result > *(_DWORD *)(v7 + 2147) )
    {
      if ( *(_BYTE *)(self + 1968) )
      {
        if ( *(_DWORD *)(self + 1964) )
        {
          result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                     *(_DWORD *)(self + 1964),
                     self + 2095,
                     *(_DWORD *)(self + 1956),
                     self + 2063,
                     512,
                     0);
          if ( result )
          {
            if ( result != -2005532222
              || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 96))(*(_DWORD *)(self + 1964)) != -2005532222
               || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 108))(*(_DWORD *)(self + 1964))) == 0)
              && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 96))(*(_DWORD *)(self + 1956)) != -2005532222
               || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956))) == 0)
              && (result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                             *(_DWORD *)(self + 1964),
                             self + 2095,
                             *(_DWORD *)(self + 1956),
                             self + 2063,
                             512,
                             0)) != 0 )
            {
              ExcString_Ctor();
              AviException_CtorForDrawFailure();
              return CRT_ThrowExcStringException();
            }
          }
        }
      }
    }
    else
    {
      showFlags = 0x4000;
      if ( *(_DWORD *)(v7 + 2171) )
        showFlags = 20480;
      overlayFlags = showFlags;
      result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                 *(_DWORD *)(self + 1964),
                 self + 2095,
                 *(_DWORD *)(self + 1956),
                 self + 2063,
                 showFlags,
                 0);
      if ( result )
      {
        if ( result != -2005532222
          || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 96))(*(_DWORD *)(self + 1964)) != -2005532222
           || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1964) + 108))(*(_DWORD *)(self + 1964))) == 0)
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 96))(*(_DWORD *)(self + 1956)) != -2005532222
           || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956))) == 0)
          && (result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(self + 1964) + 132))(
                         *(_DWORD *)(self + 1964),
                         self + 2095,
                         *(_DWORD *)(self + 1956),
                         self + 2063,
                         overlayFlags,
                         0)) != 0 )
        {
          ExcString_Ctor();
          v12 = v10;
          ExcString_Ctor();
          v12 = 0;
          return CRT_ThrowExcStringException();
        }
      }
    }
  }
  return result;
}
// 468901: conditional instruction was optimized away because dl.1!=0
// 468909: conditional instruction was optimized away because ebp.4!=0
// 4688E7: variable 'v2' is possibly undefined
// 46894A: variable 'v6' is possibly undefined
// 46895A: variable 'v7' is possibly undefined
// 468A92: variable 'v10' is possibly undefined

//----- (00468BB0) --------------------------------------------------------
int  AviPlayer_UpdateOverlayColorKey(int result)
{
  int self; // ebx
  int colorKeyFlags; // esi
  char prevFlagsByte; // dl
  int colorKeyHigh; // ecx
  int overlaySurface; // edi
  int backSurface; // ebp

  self = result;
  if ( *(_DWORD *)(result + 2171) )
  {
    colorKeyFlags = 8;
    prevFlagsByte = *(_BYTE *)(result + 2112);
    colorKeyHigh = *(_DWORD *)(result + 2046);
    *(_BYTE *)(result + 2115) |= 1u;
    result = *(_DWORD *)(result + 2042);
    *(_BYTE *)(self + 2112) = prevFlagsByte | 0x80;
    if ( result == colorKeyHigh )
      colorKeyFlags = 9;
    overlaySurface = *(_DWORD *)(self + 1964);
    if ( overlaySurface )
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)overlaySurface + 116))(overlaySurface, colorKeyFlags, self + 2042);
    backSurface = *(_DWORD *)(self + 2017);
    if ( backSurface )
      return (*(int (__stdcall **)(int, int, int))(*(_DWORD *)backSurface + 116))(backSurface, colorKeyFlags, self + 2042);
  }
  return result;
}

//----- (00468C40) --------------------------------------------------------
char  AviPlayer_ComputeFlipState(int a1)
{
  int self; // ecx
  int decodedFrameBuffer; // edx
  int v3; // esi
  int v4; // edx
  int destWidthScaled; // edi
  int v6; // ecx
  int requiredCaps; // eax
  int v8; // ebx
  int v9; // edx
  int overlayCaps; // eax

  self = a1;
  decodedFrameBuffer = *(_DWORD *)(a1 + 2179);
  *(_BYTE *)(a1 + 2033) = 0;
  if ( decodedFrameBuffer )
  {
    *(_BYTE *)(a1 + 2033) = 1;
    return a1;
  }
  v3 = a1;
  v4 = a1;
  if ( *(_BYTE *)(a1 + 2052) )
  {
    v8 = a1;
    if ( !AviPlayer_IsIcmDecoderIdle(a1) || !AviPlayer_TestModeFlagBit3(self) )
    {
      LOBYTE(a1) = AviPlayer_IsIcmDecoderIdle(v8);
      if ( (_BYTE)a1 )
        goto LABEL_16;
      LOBYTE(a1) = AviPlayer_TestModeFlagBit2(v8);
      if ( !(_BYTE)a1 )
      {
        *(_BYTE *)(self + 2033) = 2;
        return a1;
      }
    }
  }
  if ( !*(_BYTE *)(v4 + 2052) )
  {
    LOBYTE(a1) = AviPlayer_TestModeFlagBit2(v4);
    if ( !(_BYTE)a1 )
      goto LABEL_16;
    LOBYTE(a1) = AviPlayer_IsUncompressedFormat(v9);
    if ( !(_BYTE)a1 )
    {
      *(_BYTE *)(self + 2033) = 2;
      return a1;
    }
  }
  LOBYTE(a1) = *(_BYTE *)(v3 + 1968);
  if ( !(_BYTE)a1
    || !*(_DWORD *)(v3 + 1964)
    || (destWidthScaled = 1000 * AviPlayer_SpanDelta(self, (_DWORD *)(v3 + 2063)),
        a1 = destWidthScaled / AviPlayer_SpanDelta(v6, (_DWORD *)(v3 + 2079)),
        a1 < *(_DWORD *)(v3 + 2143))
    || a1 > *(_DWORD *)(v3 + 2147) )
  {
    if ( *(_DWORD *)(v3 + 1964) )
    {
      overlayCaps = *(_DWORD *)(v3 + 2171);
      LOBYTE(overlayCaps) = overlayCaps | 2;
      a1 = *(_DWORD *)(v3 + 2175) | overlayCaps;
      if ( (a1 & *(_DWORD *)(v3 + 2119)) != a1 )
      {
        *(_BYTE *)(self + 2033) = 2;
        return a1;
      }
      goto LABEL_8;
    }
LABEL_16:
    *(_BYTE *)(self + 2033) = 2;
    return a1;
  }
LABEL_8:
  if ( !*(_BYTE *)(self + 1968) || !*(_DWORD *)(self + 1964) )
  {
    if ( *(_DWORD *)(self + 1964) )
    {
      requiredCaps = *(_DWORD *)(self + 2171);
      LOBYTE(requiredCaps) = requiredCaps | 2;
      a1 = *(_DWORD *)(self + 2175) | requiredCaps;
      if ( (a1 & *(_DWORD *)(self + 2119)) == a1 )
        *(_BYTE *)(self + 2033) = 3;
    }
  }
  return a1;
}
// 468C6E: variable 'v4' is possibly undefined
// 468CA0: variable 'v1' is possibly undefined
// 468CD1: variable 'v6' is possibly undefined
// 468DA9: variable 'v9' is possibly undefined

//----- (00468E10) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
char  AviPlayer_ApplyOpenOptionsAndInitDecoder(
        int self,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12,
        __int64 a13,
        __int64 a14,
        __int64 a15,
        __int128 a16,
        __int128 a17,
        __int64 a18)
{
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int capsFlags; // eax
  int v23; // edx
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int videoFormat; // ebx
  int biCompression; // esi
  int v31; // eax
  int v32; // edx
  __int64 frameHeight; // rax
  int v34; // edx
  __int64 frameHeight2; // rax
  int stretchRatio; // eax
  int decodedFormatPtr; // ebx
  __int64 frameBufferAlloc; // rax
  int v41; // ecx
  int v42; // eax
  int v43; // ecx
  int v44; // [esp+0h] [ebp-30Ch]
  int v45; // [esp+4h] [ebp-308h]
  int v46; // [esp+8h] [ebp-304h]
  int v47; // [esp+Ch] [ebp-300h]
  int v48; // [esp+10h] [ebp-2FCh]
  int v49; // [esp+14h] [ebp-2F8h]
  int v50; // [esp+18h] [ebp-2F4h]
  __int128 v51; // [esp+1Ch] [ebp-2F0h]
  __int64 v52; // [esp+2Ch] [ebp-2E0h]
  __int64 v53; // [esp+34h] [ebp-2D8h]
  __int64 v54; // [esp+3Ch] [ebp-2D0h]
  __int64 v55; // [esp+44h] [ebp-2C8h]
  __int64 v56; // [esp+4Ch] [ebp-2C0h]
  __int64 v57; // [esp+54h] [ebp-2B8h]
  __int64 v58; // [esp+5Ch] [ebp-2B0h]
  __int64 v59; // [esp+64h] [ebp-2A8h]
  int v60; // [esp+6Ch] [ebp-2A0h]
  int driverCaps; // [esp+82h] [ebp-28Ah] BYREF
  char v62; // [esp+86h] [ebp-286h]
  char v63; // [esp+87h] [ebp-285h]
  char v64; // [esp+88h] [ebp-284h]
  char v65; // [esp+89h] [ebp-283h]
  char v66; // [esp+8Fh] [ebp-27Dh]
  char v67; // [esp+9Eh] [ebp-26Eh]
  char v68; // [esp+9Fh] [ebp-26Dh]
  char v69; // [esp+A0h] [ebp-26Ch]
  int minStretchRate; // [esp+10Ah] [ebp-202h]
  int maxStretchRate; // [esp+10Eh] [ebp-1FEh]
  int helCaps[79]; // [esp+1BEh] [ebp-14Eh] BYREF
  _DWORD surfaceDesc[4]; // [esp+2FAh] [ebp-12h] BYREF

  *(_DWORD *)((char *)&a18 + 6) = self;
  *(_DWORD *)((char *)&a17 + 2) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a17 + 6) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a17 + 10) = &g_AviApplyOpenOptions_EHFrame;
  *(_DWORD *)((char *)&a17 + 14) = 0;
  memset_(a2, 0);
  memset_(v18, 0);
  driverCaps = 316;
  helCaps[0] = 316;
  (*(void (__stdcall **)(int, int *, int *))(*(_DWORD *)v19 + 44))(v19, &driverCaps, helCaps);
  memset_(v20, 0);
  surfaceDesc[0] = 108;
  (*(void (__stdcall **)(_DWORD, _DWORD *))(**(_DWORD **)(*(_DWORD *)((char *)&a18 + 6) + 1956) + 88))(
    *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 1956),
    surfaceDesc);
  if ( (a15 & 0x800000000000000LL) != 0 )
    capsFlags = 1;
  else
    capsFlags = 256;
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2119) = capsFlags;
  if ( (a15 & 0x200000000000000LL) != 0 )
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2121) |= 1u;
  v23 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2123) = *(_DWORD *)((char *)&a13 + 2);
  if ( *(_DWORD *)((char *)&a13 + 2) == 8 )
  {
    *(_BYTE *)(v23 + 2120) |= 2u;
  }
  else
  {
    *(_DWORD *)(v23 + 2127) = *(_DWORD *)((char *)&a13 + 6);
    *(_DWORD *)(v23 + 2131) = *(_DWORD *)((char *)&a14 + 2);
    *(_DWORD *)(v23 + 2135) = *(_DWORD *)((char *)&a14 + 6);
    *(_DWORD *)(v23 + 2139) = *(_DWORD *)((char *)&a15 + 2);
  }
  if ( (v62 & 0x40) != 0 )
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 2u;
  if ( (v63 & 2) != 0 )
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 4u;
  if ( v62 < 0 )
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x80u;
  if ( (v63 & 8) != 0 )
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 0x20u;
  if ( (v63 & 0x40) != 0 )
  {
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 0x40u;
    v24 = *(_DWORD *)((char *)&a18 + 6);
    *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2143) = minStretchRate;
    *(_DWORD *)(v24 + 2147) = maxStretchRate;
  }
  if ( (v64 & 0x40) != 0 )
  {
    if ( (v66 & 2) != 0 )
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 8u;
    if ( (v66 & 0x20) != 0 )
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 0x80u;
  }
  if ( (v62 & 0x16) != 0 )
  {
    v25 = *(_DWORD *)((char *)&a18 + 6);
    *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2121) |= 2u;
    *(_BYTE *)(v25 + 2120) &= 0x1Fu;
  }
  if ( v65 < 0 )
  {
    if ( (v67 & 0x40) != 0 )
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x10u;
    if ( (v68 & 2) != 0 )
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x20u;
    if ( (v69 & 0x40) != 0 )
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x40u;
  }
  if ( (*(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2119) & 1) != 0 || (v65 & 8) == 0 )
  {
    if ( !(*(int (__stdcall **)(_DWORD, _DWORD, _DWORD *, int, _DWORD))(**(_DWORD **)(*(_DWORD *)((char *)&a18 + 6)
                                                                                    + 1956)
                                                                      + 100))(
            *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 1956),
            0,
            surfaceDesc,
            1,
            0) )
    {
      v26 = *(_DWORD *)((char *)&a18 + 6);
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 4u;
      (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(v26 + 1956) + 128))(*(_DWORD *)(v26 + 1956), 0);
    }
    if ( !(*(int (__stdcall **)(_DWORD, char *))(**(_DWORD **)(*(_DWORD *)((char *)&a18 + 6) + 1956) + 68))(
            *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 1956),
            (char *)&a18 + 2) )
    {
      v27 = *(_DWORD *)((char *)&a18 + 6);
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 8u;
      (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(v27 + 1952) + 104))(
        *(_DWORD *)(v27 + 1952),
        *(_DWORD *)((char *)&a18 + 2));
    }
  }
  AviPlayer_AllocDecodedBitmapInfo(*(int *)((char *)&a18 + 6), v21);
  v28 = *(_DWORD *)((char *)&a18 + 6);
  videoFormat = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 151);
  *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2052) = 0;
  biCompression = *(_DWORD *)(videoFormat + 16);
  if ( !biCompression || biCompression == 3 )
  {
    CAviDecompressor_SetupBlitFormat(
      (int (*)())(*(_DWORD *)((char *)&a18 + 6) + 1924),
      *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2058),
      0,
      *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 151),
      0);
  }
  else
  {
    if ( AviPlayer_OpenVideoCodec(
           v28 + 415,
           *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 15),
           *(int **)(v28 + 2058),
           videoFormat,
           v44,
           v45,
           v46,
           v47,
           v48,
           v49,
           v50,
           v51,
           v52,
           v53,
           v54,
           v55,
           v56,
           v57,
           v58,
           v59,
           v60) )
    {
      goto LABEL_39;
    }
    if ( !*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 415) )
      return 0;
    decodedFormatPtr = *(_DWORD *)((char *)&a18 + 6) + 423;
    frameBufferAlloc = j_Mem_Alloc(0);
    *(_DWORD *)(HIDWORD(frameBufferAlloc) + 2179) = frameBufferAlloc;
    CAviDecompressor_SetupBlitFormat((int (*)())(*(_DWORD *)((char *)&a18 + 6) + 1924), *(_DWORD *)(HIDWORD(frameBufferAlloc) + 2058), v41, decodedFormatPtr, 0);
  }
  *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2052) = 1;
LABEL_39:
  v31 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2095) = 0;
  *(_DWORD *)(v31 + 2099) = 0;
  v32 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2103) = *(_DWORD *)(*(_DWORD *)(v31 + 151) + 4);
  frameHeight = *(int *)(*(_DWORD *)(v32 + 151) + 8);
  LODWORD(frameHeight) = (HIDWORD(frameHeight) ^ frameHeight) - HIDWORD(frameHeight);
  HIDWORD(frameHeight) = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2107) = frameHeight;
  if ( *(_BYTE *)(HIDWORD(frameHeight) + 2062) )
  {
    if ( !*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071) && !*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2075) )
    {
      v34 = *(_DWORD *)((char *)&a18 + 6);
      *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 151)
                                                                    + 4)
                                                        + *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2063);
      frameHeight2 = *(int *)(*(_DWORD *)(v34 + 151) + 8);
      *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2075) = (HIDWORD(frameHeight2) ^ frameHeight2)
                                                        - HIDWORD(frameHeight2)
                                                        + *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2067);
    }
    *(_DWORD *)((char *)&a16 + 2) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2063);
    *(_DWORD *)((char *)&a16 + 6) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2067);
    *(_DWORD *)((char *)&a16 + 10) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071);
    *(_DWORD *)((char *)&a16 + 14) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2075);
    AviPlayer_RenderFrame(*(int *)((char *)&a18 + 6), (const RECT *)((char *)&a16 + 2));
    stretchRatio = 1000
        * (*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071) - *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2063))
        / (*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2087) - *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2079));
    if ( stretchRatio < *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2143)
      || stretchRatio > *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2147) )
    {
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) &= 0x1Fu;
    }
  }
  else
  {
    v42 = *(_DWORD *)((char *)&a18 + 6);
    v43 = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2143);
    *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2175) = 4;
    if ( v43 > 1000 || *(int *)(v42 + 2147) < 4000 )
      *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2120) &= 0x1Fu;
  }
  return 1;
}
// 468E10: variables would overlap: ^360.8 and ^360.10
// 468E10: variables would overlap: ^36A.8 and ^368.10
// 468E10: variables would overlap: ^368.8 and ^36A.8
// 468E10: variables would overlap: ^36A.8 and ^366.4
// 468E10: variables would overlap: ^372.4 and ^370.8
// 468E10: variables would overlap: ^372.4 and ^36E.4
// 468E10: variables would overlap: ^377.1 and ^370.8
// 46918C: inconsistent variable size for '^378.16'
// 468E59: inconsistent variable size for '^388.16'
// 469087: inconsistent variable size for '^398.8'
// 46918D: inconsistent variable size for '^398.8'
// 468E23: inconsistent variable size for '^398.8'
// 468EB5: inconsistent variable size for '^398.8'
// 468ED4: inconsistent variable size for '^398.8'
// 468EE3: inconsistent variable size for '^398.8'
// 468EEA: inconsistent variable size for '^398.8'
// 468EF0: inconsistent variable size for '^398.8'
// 468F12: inconsistent variable size for '^398.8'
// 468F25: inconsistent variable size for '^398.8'
// 468F38: inconsistent variable size for '^398.8'
// 468F4B: inconsistent variable size for '^398.8'
// 468F5E: inconsistent variable size for '^398.8'
// 468F65: inconsistent variable size for '^398.8'
// 468F6E: inconsistent variable size for '^398.8'
// 468F95: inconsistent variable size for '^398.8'
// 468FA8: inconsistent variable size for '^398.8'
// 468FB8: inconsistent variable size for '^398.8'
// 468FBB: inconsistent variable size for '^398.8'
// 468FDE: inconsistent variable size for '^398.8'
// 468FF1: inconsistent variable size for '^398.8'
// 469004: inconsistent variable size for '^398.8'
// 46900E: inconsistent variable size for '^398.8'
// 469026: inconsistent variable size for '^398.8'
// 469038: inconsistent variable size for '^398.8'
// 46903B: inconsistent variable size for '^398.8'
// 46905A: inconsistent variable size for '^398.8'
// 46906A: inconsistent variable size for '^398.8'
// 46906D: inconsistent variable size for '^398.8'
// 46908C: inconsistent variable size for '^398.8'
// 46908F: inconsistent variable size for '^398.8'
// 469095: inconsistent variable size for '^398.8'
// 4690B4: inconsistent variable size for '^398.8'
// 4690BF: inconsistent variable size for '^398.8'
// 4690B9: inconsistent variable size for '^398.8'
// 4690CD: inconsistent variable size for '^398.8'
// 4690D4: inconsistent variable size for '^398.8'
// 4690D7: inconsistent variable size for '^398.8'
// 4690F1: inconsistent variable size for '^398.8'
// 4690F7: inconsistent variable size for '^398.8'
// 46910B: inconsistent variable size for '^398.8'
// 46910E: inconsistent variable size for '^398.8'
// 469124: inconsistent variable size for '^398.8'
// 46912D: inconsistent variable size for '^398.8'
// 46914A: inconsistent variable size for '^398.8'
// 469136: inconsistent variable size for '^398.8'
// 469142: inconsistent variable size for '^398.8'
// 46914D: inconsistent variable size for '^398.8'
// 469166: inconsistent variable size for '^398.8'
// 469171: inconsistent variable size for '^398.8'
// 46917D: inconsistent variable size for '^398.8'
// 469189: inconsistent variable size for '^398.8'
// 46918A: inconsistent variable size for '^398.8'
// 46918B: inconsistent variable size for '^398.8'
// 469195: inconsistent variable size for '^398.8'
// 46919B: inconsistent variable size for '^398.8'
// 4691CC: inconsistent variable size for '^398.8'
// 4691D2: inconsistent variable size for '^398.8'
// 4691E6: inconsistent variable size for '^398.8'
// 4691F2: inconsistent variable size for '^398.8'
// 469273: inconsistent variable size for '^398.8'
// 469286: inconsistent variable size for '^398.8'
// 469296: inconsistent variable size for '^398.8'
// 4692BA: inconsistent variable size for '^398.8'
// 4692C7: inconsistent variable size for '^398.8'
// 4692D3: inconsistent variable size for '^398.8'
// 4692D6: inconsistent variable size for '^398.8'
// 4692DC: inconsistent variable size for '^398.8'
// 4692F1: inconsistent variable size for '^398.8'
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00469310) --------------------------------------------------------
int  AviPlayer_CreateSystemMemoryBackSurface(int self, int a2)
{
  __int64 biHeight; // rax
  int v4; // ecx
  int result; // eax
  int v6; // ecx
  int v7; // ecx
  _DWORD surfaceDesc[183]; // [esp+0h] [ebp-2F4h] BYREF
  int v9; // [esp+2DCh] [ebp-18h]

  surfaceDesc[180] = NtCurrentTeb()->NtTib.ExceptionList;
  surfaceDesc[181] = &j____wcpp_4_fs_handler_rtn_;
  surfaceDesc[182] = &g_AviPlayerCreateBackSurface_EHScopeTable;
  v9 = 0;
  memset_(a2, 0);
  surfaceDesc[0] = 108;
  surfaceDesc[3] = *(_DWORD *)(*(_DWORD *)(self + 151) + 4);
  biHeight = *(int *)(*(_DWORD *)(self + 151) + 8);
  surfaceDesc[2] = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
  surfaceDesc[1] = 7;
  surfaceDesc[26] = 2112;
  if ( (*(int (__stdcall **)(int, _DWORD *, int, _DWORD))(*(_DWORD *)v4 + 24))(v4, surfaceDesc, self + 2013, 0) )
  {
    ExcString_Ctor();
    v9 = 1;
    ExcString_Ctor();
    surfaceDesc[52] = v6;
    v9 = 0;
    return CRT_ThrowExcStringException();
  }
  else if ( (***(int (__stdcall ****)(_DWORD, void *, int))(self + 2013))(*(_DWORD *)(self + 2013), &g_AviQueryInterfaceIid, self + 2017) )
  {
    ExcString_Ctor();
    v9 = 3;
    ExcString_Ctor();
    v9 = 0;
    surfaceDesc[104] = g_AviException_VTable;
    return CRT_ThrowExcStringException();
  }
  else
  {
    result = (*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(self + 2017) + 148))(*(_DWORD *)(self + 2017), 0);
    if ( result )
    {
      ExcString_Ctor();
      v9 = v7;
      ExcString_Ctor();
      surfaceDesc[78] = g_AviException_VTable;
      v9 = 0;
      return CRT_ThrowExcStringException();
    }
  }
  return result;
}
// 4693AA: variable 'v4' is possibly undefined
// 469439: variable 'v6' is possibly undefined
// 4694C8: variable 'v7' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 510374: using guessed type int (*off_510374[2])();

//----- (00469500) --------------------------------------------------------
int  AviPlayer_CreateOverlaySurface(int self, int a2, int a3)
{
  __int64 biHeight; // rax
  int v5; // ecx
  int result; // eax
  _DWORD surfaceDesc[31]; // [esp+0h] [ebp-7Ch] BYREF

  surfaceDesc[29] = a3;
  memset_(a2, 0);
  surfaceDesc[0] = 108;
  surfaceDesc[3] = *(_DWORD *)(*(_DWORD *)(self + 151) + 4);
  biHeight = *(int *)(*(_DWORD *)(self + 151) + 8);
  surfaceDesc[2] = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
  surfaceDesc[1] = 7;
  surfaceDesc[26] = 16448;
  result = (*(int (__stdcall **)(int, _DWORD *, int, _DWORD))(*(_DWORD *)v5 + 24))(v5, surfaceDesc, self + 1960, 0);
  if ( !result )
    return (***(int (__stdcall ****)(_DWORD, void *, int))(self + 1960))(*(_DWORD *)(self + 1960), &g_AviQueryInterfaceIid, self + 1964);
  return result;
}
// 46955F: variable 'v5' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00469590) --------------------------------------------------------
int  AviPlayer_CreateOverlaySurfaceAndEnable(int self, int a2)
{
  __int64 biHeight; // rax
  int v4; // ecx
  __int64 biHeightRetry; // rax
  int v6; // ecx
  int result; // eax
  int descSize; // [esp+0h] [ebp-80h] BYREF
  int descFlags; // [esp+4h] [ebp-7Ch]
  int surfaceHeight; // [esp+8h] [ebp-78h]
  int surfaceWidth; // [esp+Ch] [ebp-74h]
  int backBufferCount; // [esp+14h] [ebp-6Ch]
  int surfaceCaps; // [esp+68h] [ebp-18h]

  memset_(a2, 0);
  descSize = 108;
  surfaceWidth = *(_DWORD *)(*(_DWORD *)(self + 151) + 4);
  biHeight = *(int *)(*(_DWORD *)(self + 151) + 8);
  surfaceHeight = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
  backBufferCount = 1;
  descFlags = 39;
  surfaceCaps = 16536;
  memset_(v4, 0);
  descSize = 108;
  surfaceWidth = *(_DWORD *)(*(_DWORD *)(self + 151) + 4);
  biHeightRetry = *(int *)(*(_DWORD *)(self + 151) + 8);
  surfaceHeight = (HIDWORD(biHeightRetry) ^ biHeightRetry) - HIDWORD(biHeightRetry);
  surfaceCaps = 16512;
  descFlags = 7;
  result = (*(int (__stdcall **)(int, int *, int, _DWORD))(*(_DWORD *)v6 + 24))(v6, &descSize, self + 1960, 0);
  if ( !result )
  {
    result = (***(int (__stdcall ****)(_DWORD, void *, int))(self + 1960))(*(_DWORD *)(self + 1960), &g_AviQueryInterfaceIid, self + 1964);
    *(_BYTE *)(self + 1968) = 1;
    *(_BYTE *)(self + 2051) = 0;
  }
  return result;
}
// 4695F4: variable 'v4' is possibly undefined
// 46963F: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

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

  bitCount = *(_DWORD *)(self + 2123);
  bytesPerPixel = (bitCount + 7) >> 3;
  if ( bitCount == 24 || bitCount == 8 )
    compressionSel = 0;
  else
    compressionSel = 3;
  compression = compressionSel;
  if ( compressionSel )
    headerBytes = **(_DWORD **)(self + 151);
  allocResult = j_Mem_Alloc(headerBytes);
  *(_DWORD *)(self + 2058) = allocResult;
  headerSize = HIDWORD(allocResult);
  if ( SHIDWORD(allocResult) > **(_DWORD **)(self + 151) )
    HIDWORD(allocResult) = **(_DWORD **)(self + 151);
  qmemcpy(*(void **)(self + 2058), *(const void **)(self + 151), HIDWORD(allocResult));
  **(_DWORD **)(self + 2058) = headerSize;
  *(_WORD *)(*(_DWORD *)(self + 2058) + 14) = *(_WORD *)(self + 2123);
  *(_DWORD *)(*(_DWORD *)(self + 2058) + 16) = compression;
  *(_DWORD *)(*(_DWORD *)(self + 2058) + 20) = *(_DWORD *)(*(_DWORD *)(self + 2058) + 4)
                                           * abs32(*(_DWORD *)(*(_DWORD *)(self + 2058) + 8))
                                           * bytesPerPixel;
  *(_DWORD *)(*(_DWORD *)(self + 2058) + 32) = 0;
  decodedBmi = *(_DWORD *)(self + 2058);
  result = *(_DWORD *)(decodedBmi + 8);
  if ( result > 0 )
  {
    result = -result;
    *(_DWORD *)(decodedBmi + 8) = result;
  }
  if ( compression == 3 )
  {
    *(_DWORD *)(*(_DWORD *)(self + 2058) + 40) = *(_DWORD *)(self + 2127);
    *(_DWORD *)(*(_DWORD *)(self + 2058) + 44) = *(_DWORD *)(self + 2131);
    *(_DWORD *)(*(_DWORD *)(self + 2058) + 48) = *(_DWORD *)(self + 2135);
    result = *(_DWORD *)(self + 2058);
    *(_DWORD *)(result + 52) = *(_DWORD *)(self + 2139);
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
  _BYTE v6[2]; // [esp+0h] [ebp-5BEh]
  char paletteEntries[1024]; // [esp+2h] [ebp-5BCh] BYREF
  int (**v8)(); // [esp+466h] [ebp-158h]
  int (**v9)(); // [esp+4CEh] [ebp-F0h]
  _DWORD v10[3]; // [esp+59Ah] [ebp-24h] BYREF
  int v11; // [esp+5A6h] [ebp-18h]

  result = v10;
  v10[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v10[1] = &j____wcpp_4_fs_handler_rtn_;
  v10[2] = &g_AviPlayerCreatePalette_EHScopeTable;
  v11 = 0;
  if ( (*(_BYTE *)(self + 2120) & 2) != 0 )
  {
    for ( i = 0; i != 1024; v6[i + 1] = 0 )
    {
      paletteEntries[i] = *(_BYTE *)(**(_DWORD **)(self + 151) + *(_DWORD *)(self + 151) + i + 2);
      paletteEntries[i + 1] = *(_BYTE *)(**(_DWORD **)(self + 151) + *(_DWORD *)(self + 151) + i + 1);
      i += 4;
      v6[i] = *(_BYTE *)(**(_DWORD **)(self + 151) + *(_DWORD *)(self + 151) + i - 4);
    }
    if ( (*(int (__stdcall **)(int, int, char *, int, _DWORD))(*(_DWORD *)ddInterface + 20))(ddInterface, 4, paletteEntries, self + 1948, 0) )
    {
      ExcString_Ctor();
      v11 = v5;
      ExcString_Ctor();
      v9 = g_AviException_VTable;
      v11 = 0;
      return (_DWORD *)CRT_ThrowExcStringException();
    }
    else
    {
      result = (_DWORD *)(*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(self + 1956) + 124))(
                           *(_DWORD *)(self + 1956),
                           *(_DWORD *)(self + 1948));
      if ( result )
      {
        if ( result != (_DWORD *)-2005532222
          || (result = (_DWORD *)(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(self + 1956) + 108))(*(_DWORD *)(self + 1956))) == 0
          && (result = (_DWORD *)(*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(self + 1956) + 124))(
                                   *(_DWORD *)(self + 1956),
                                   *(_DWORD *)(self + 1948))) != 0 )
        {
          ExcString_Ctor();
          v11 = 3;
          ExcString_Ctor();
          v8 = g_AviException_VTable;
          v11 = 0;
          return (_DWORD *)CRT_ThrowExcStringException();
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
  return ICSendMessage(hic, 16446, (DWORD)drawBeginParams, 52, 0);
}
// 4E980A: using guessed type int __stdcall ICSendMessage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (00469EF0) --------------------------------------------------------
int AviException_CtorFromExceptionList()
{
  int result; // eax

  result = ExcString_CtorFromPtr((void *)NtCurrentTeb()->NtTib.ExceptionList);
  *(_DWORD *)(result + 100) = g_AviException_VTable;
  return result;
}
// 510374: using guessed type int (*off_510374[2])();

//----- (00469F50) --------------------------------------------------------
int AviException_CtorForSurfaceCreateFailure()
{
  int result; // eax

  result = ExcString_Ctor();
  *(_DWORD *)(result + 100) = g_AviException_VTable;
  return result;
}
// 510374: using guessed type int (*off_510374[2])();

//----- (00469FB0) --------------------------------------------------------
int AviException_CtorForDrawFailure()
{
  int result; // eax

  result = ExcString_Ctor();
  *(_DWORD *)(result + 100) = g_AviException_VTable;
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
int AviException_GetMessage()
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

  counter = *(_DWORD **)guardPtr;
  LeaveCriticalSection((LPCRITICAL_SECTION)(*(_DWORD *)guardPtr + 4));
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
  return *(_DWORD *)(queue + 8) - *(_DWORD *)(queue + 4);
}

//----- (0046A150) --------------------------------------------------------
int  AviPlayer_IncrementFramesRenderedCount(int result)
{
  ++*(_DWORD *)(result + 4);
  return result;
}

//----- (0046A160) --------------------------------------------------------
int  AviPlayer_AudioBytesQueued(int self)
{
  return *(_DWORD *)(self + 259);
}

//----- (0046A170) --------------------------------------------------------
int  AviPlayer_AudioSampleQueueCount(int queue)
{
  return *(_DWORD *)(queue + 8);
}

//----- (0046A180) --------------------------------------------------------
int  AviPlayer_AudioSampleQueueBase(int self)
{
  return self + 219;
}

//----- (0046A190) --------------------------------------------------------
int  AviPlayer_AudioFormatPtr(int self)
{
  return *(_DWORD *)(self + 363);
}

//----- (0046A1A0) --------------------------------------------------------
int  AviPlayer_BitmapWidth(int self)
{
  return *(_DWORD *)(*(_DWORD *)(self + 151) + 4);
}

//----- (0046A1B0) --------------------------------------------------------
int  AviPlayer_BitmapHeightAbs(int self)
{
  __int64 biHeight; // rax

  biHeight = *(int *)(*(_DWORD *)(self + 151) + 8);
  return (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
}

//----- (0046A1D0) --------------------------------------------------------
int  AviPlayer_AudioBlockAlign(int self)
{
  return *(unsigned __int16 *)(*(_DWORD *)(self + 363) + 12);
}

//----- (0046A1E0) --------------------------------------------------------
int  AviPlayer_UpdateStreamRectAndSendICDrawBegin(int *codecPtr, int lockedBits, int destHeight, int destWidth, int pitchPixels, int frameData, int frameFlags)
{
  int inputFormat; // edx
  int biHeight; // esi
  int result; // eax
  int v11; // [esp+0h] [ebp-124h]
  _DWORD drawParams[16]; // [esp+CCh] [ebp-58h] BYREF
  int v13; // [esp+10Ch] [ebp-18h]
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
  biWidth = *(_DWORD *)(inputFormat + 4);
  biHeight = *(_DWORD *)(inputFormat + 8);
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
int __fastcall AviPlayer_SpanDelta(int a1, _DWORD *rect)
{
  return rect[2] - *rect;
}

//----- (0046A370) --------------------------------------------------------
bool  AviPlayer_IsUncompressedFormat(int self)
{
  return *(_BYTE *)(self + 1923) != 0;
}

//----- (0046A380) --------------------------------------------------------
bool  AviPlayer_IsIcmDecoderIdle(int self)
{
  int pendingCount; // edx
  int blitState; // eax
  bool result; // al

  result = 0;
  if ( *(_BYTE *)(self + 2052) )
  {
    pendingCount = *(_DWORD *)(self + 1944);
    blitState = self + 1924;
    if ( !pendingCount && !*(_DWORD *)(blitState + 16) )
      return 1;
  }
  return result;
}

//----- (0046A3B0) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit2(int self)
{
  return (*(_BYTE *)(self + 2120) & 4) != 0;
}

//----- (0046A3C0) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit3(int self)
{
  return (*(_BYTE *)(self + 2120) & 8) != 0;
}

//----- (0046A3D0) --------------------------------------------------------
bool  AviPlayer_TestActiveModeFlag(int self)
{
  return *(_BYTE *)(self + 2052) && !*(_DWORD *)(self + 1944) && !*(_DWORD *)(self + 1940) && (*(_BYTE *)(self + 2120) & 8) != 0
      || (!*(_BYTE *)(self + 2052) || *(_DWORD *)(self + 1944) || *(_DWORD *)(self + 1940))
      && (*(_BYTE *)(self + 2120) & 4) != 0;
}

//----- (0046A430) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit2AndSubframe(int self)
{
  return (*(_BYTE *)(self + 2120) & 4) != 0 && *(_BYTE *)(self + 1923);
}

//----- (0046A450) --------------------------------------------------------
bool  AviPlayer_SupportsRequiredPlaybackCaps(int self)
{
  int requiredCaps; // edx

  requiredCaps = *(_DWORD *)(self + 2171);
  LOBYTE(requiredCaps) = requiredCaps | 2;
  return ((*(_DWORD *)(self + 2175) | requiredCaps) & *(_DWORD *)(self + 2119)) == (*(_DWORD *)(self + 2175) | requiredCaps);
}

//----- (0046A480) --------------------------------------------------------
bool  AviPlayer_HasValidRateParams(int self)
{
  return *(_BYTE *)(self + 1968) && *(_DWORD *)(self + 1964);
}

//----- (0046A4A0) --------------------------------------------------------
bool  AviPlayer_IsPlaybackRateInRange(int self)
{
  int stretchRatio; // eax

  stretchRatio = 1000 * (*(_DWORD *)(self + 2071) - *(_DWORD *)(self + 2063)) / (*(_DWORD *)(self + 2087) - *(_DWORD *)(self + 2079));
  return stretchRatio >= *(_DWORD *)(self + 2143) && stretchRatio <= *(_DWORD *)(self + 2147);
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
        if ( (*(int (__stdcall **)(int, int))(*(_DWORD *)g_DirectSoundDevice + 16))(g_DirectSoundDevice, v2) || (dsCapsFlags & 0x20) != 0 )
        {
          *accelFlagOut = 0;
          (*(void (__stdcall **)(int))(*(_DWORD *)g_DirectSoundDevice + 8))(g_DirectSoundDevice);
          return 0;
        }
        else
        {
          *accelFlagOut = 1;
          (*(void (__stdcall **)(int))(*(_DWORD *)g_DirectSoundDevice + 8))(g_DirectSoundDevice);
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
  void *v4; // [esp+68h] [ebp-8h]

  v4 = this;
  memset_(this, 0);
  dsCaps = 96;
  (*(void (__stdcall **)(int, int *))(*(_DWORD *)g_DirectSoundDevice + 16))(g_DirectSoundDevice, &dsCaps);
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
signed int Audio_InitDSoundDevice()
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
  int bufferDescFlags; // [esp+3Ch] [ebp-3Ch]
  int bufferBytes; // [esp+40h] [ebp-38h]
  __int16 *formatPtr; // [esp+48h] [ebp-30h]
  __int16 wFormatTag; // [esp+4Ch] [ebp-2Ch] BYREF
  __int16 nChannels; // [esp+4Eh] [ebp-2Ah]
  int samplesPerSec; // [esp+50h] [ebp-28h]
  int avgBytesPerSec; // [esp+54h] [ebp-24h]
  __int16 blockAlign; // [esp+58h] [ebp-20h]
  __int16 bitsPerSample; // [esp+5Ah] [ebp-1Eh]
  __int16 cbSize; // [esp+5Ch] [ebp-1Ch]

  if ( !g_AudioWindowHandle )
    return 1;
  g_DSoundCoopWindowHandle = g_AudioWindowHandle;
  g_CSS_DSoundWritePrimaryMode = 0;
  hr = DirectSoundCreate(0, &g_DirectSoundDevice, 0);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  Audio_ComputeBytesPerFrame(v2);
  if ( g_CSS_DSoundAccelDetectEnabled != 2
    || (*(int (__stdcall **)(int, int, int))(*(_DWORD *)g_DirectSoundDevice + 24))(g_DirectSoundDevice, g_DSoundCoopWindowHandle, 4) )
  {
    if ( !g_CSS_DSoundWritePrimaryMode )
    {
      hr = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)g_DirectSoundDevice + 24))(g_DirectSoundDevice, g_DSoundCoopWindowHandle, 3);
      if ( hr )
        return Audio_ReturnDSoundError(hr);
      memset_(&bufferDescSize, 0);
      bufferBytes = 0;
      formatPtr = 0;
      bufferDescSize = 20;
      bufferDescFlags = 1;
      hr = (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)g_DirectSoundDevice + 12))(
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
      (*(void (__stdcall **)(int, __int16 *))(*(_DWORD *)g_DSoundPrimaryBuffer + 56))(g_DSoundPrimaryBuffer, &wFormatTag);
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
    hr = (*(int (__stdcall **)(int, int *, int *, _DWORD))(*(_DWORD *)g_DirectSoundDevice + 12))(
           g_DirectSoundDevice,
           &bufferDescSize,
           &g_DSoundPrimaryBuffer,
           0);
    if ( !hr )
    {
      hr = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
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
  hr = (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)g_DirectSoundDevice + 12))(
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
  hr = (*(int (__stdcall **)(int, __int16 *))(*(_DWORD *)g_DSoundPrimaryBuffer + 56))(g_DSoundPrimaryBuffer, &wFormatTag);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  memset_(v11, 0);
  bufferCaps[0] = 20;
  hr = (*(int (__stdcall **)(int, _DWORD *))(*(_DWORD *)g_DSoundPrimaryBuffer + 12))(g_DSoundPrimaryBuffer, bufferCaps);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  g_DSoundStreamBufferBytes = bufferCaps[2];
  hr = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
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
unsigned int Audio_ReleaseDSoundDevice()
{
  unsigned int hr; // eax

  hr = (*(int (__stdcall **)(int))(*(_DWORD *)g_DSoundPrimaryBuffer + 72))(g_DSoundPrimaryBuffer);
  if ( hr )
    return Audio_ReturnDSoundError(hr);
  (*(void (__stdcall **)(int))(*(_DWORD *)g_DSoundPrimaryBuffer + 8))(g_DSoundPrimaryBuffer);
  (*(void (__stdcall **)(int))(*(_DWORD *)g_DirectSoundDevice + 8))(g_DirectSoundDevice);
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
unsigned int Audio_ShutdownSoundSystem()
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
unsigned int Audio_RefreshPlayCursor()
{
  unsigned int hr; // eax
  int playCursor; // [esp+Ch] [ebp-8h] BYREF
  _BYTE writeCursor[4]; // [esp+10h] [ebp-4h] BYREF

  EnterCriticalSection(&stru_54D350);
  hr = (*(int (__stdcall **)(int, int *, _BYTE *))(*(_DWORD *)g_DSoundPrimaryBuffer + 16))(g_DSoundPrimaryBuffer, &playCursor, writeCursor);
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
  if ( GetForegroundWindow() == (HWND)g_DSoundCoopWindowHandle )
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
        (*(void (__stdcall **)(int))(*(_DWORD *)g_DSoundPrimaryBuffer + 80))(g_DSoundPrimaryBuffer);
        (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
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
      lockResult = (*(int (__stdcall **)(int, int, unsigned int, int *, unsigned int *, int *, _DWORD *, _DWORD))(*(_DWORD *)g_DSoundPrimaryBuffer + 44))(
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
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)g_DSoundPrimaryBuffer + 80))(g_DSoundPrimaryBuffer) )
      {
        LeaveCriticalSection(&stru_54D350);
        *mixCompleteOut = 0;
        return 0;
      }
      hr = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)g_DSoundPrimaryBuffer + 48))(g_DSoundPrimaryBuffer, 0, 0, 1);
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
    hr = (*(int (__stdcall **)(int, int, unsigned int, int, _DWORD))(*(_DWORD *)g_DSoundPrimaryBuffer + 76))(
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

  dest = (_WORD *)(destOffset + destBase);
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
          return (int)dest - destBase;
      }
      if ( sample < -32768 )
        break;
      *dest++ = sample;
      if ( !--i )
        return (int)dest - destBase;
    }
    *dest++ = 0x8000;
  }
  return (int)dest - destBase;
}

//----- (0046B169) --------------------------------------------------------
_BYTE *__cdecl Audio_ClipMixBufferToPCM8(int sampleCount, int destBase, int destOffset, int *mixBuffer)
{
  _BYTE *dest; // edi
  int i; // ecx
  int sample; // eax
  int biased; // eax

  dest = (_BYTE *)(destOffset + destBase);
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

  result = (*(int (__fastcall **)(int, int))(*(_DWORD *)g_MediaFileStreamProvider + 12))(fileName, fileName);
  stream = result;
  if ( !result )
    return result;
  (*(void (**)(void))(*(_DWORD *)result + 20))();
  if ( (*(int (**)(void))(*(_DWORD *)stream + 16))() == -1
    || memcmp(riffTag, aRiff, 4)
    || memcmp(waveTag, aWave, 4)
    || memcmp(fmtTag, aFmt, 4)
    || (streamPos = (*(int (**)(void))(*(_DWORD *)stream + 4))(),
        (*seekFunc)(seekFunc, fmtChunkSize + streamPos - 16),
        (*(void (**)(void))(*(_DWORD *)stream + 20))(),
        memcmp(dataTag, aData, 4)) )
  {
LABEL_3:
    (*(void (**)(void))(*(_DWORD *)g_MediaFileStreamProvider + 20))();
    return 0;
  }
  (*(void (**)(void))(*(_DWORD *)stream + 20))();
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

//----- (0046B610) --------------------------------------------------------
void  Audio_MixResampledVoice(int *mixArgs)
{
  unsigned int *channel; // ebx
  unsigned int playbackRate; // edx
  unsigned __int64 rateFixed; // rtt
  unsigned int queuedState; // eax
  int queueSlot; // esi
  unsigned int sampleStep; // edx
  unsigned int formatCode; // eax
  unsigned int endPos; // eax
  unsigned __int64 distanceFixed; // rax
  int spanSamples; // eax
  unsigned __int64 stepRemainder; // rt2
  int savedPosPlusStep; // esi
  int savedFrac; // ebp
  int stepValue; // edx
  int savedAccum; // edi
  int signedStep; // edx
  int posFixed; // esi
  int accumPtrSaved; // edi
  int loopReturnPos; // eax
  __int64 reflected64; // rax
  int reversePos; // eax
  __int64 reflectedPos; // rax
  int *savedArgs; // [esp-2Ch] [ebp-2Ch]

  g_Audio_MixVoice_SamplesRemaining = mixArgs[5];
  g_Audio_MixVoice_ChannelIndexArg = mixArgs[2];
  g_Audio_MixVoice_AccumBufferPtr = g_CSS_MixAccumBufferPtr;
  g_Audio_MixVoice_MixFunc = (int (__fastcall *)(_DWORD, _DWORD))mixArgs[3];
  channel = (unsigned int *)(108 * mixArgs[2] + g_CssMixChannels);
  g_Audio_CurrentVoiceRecordPtr = (int)channel;
  g_Audio_MixVoice_LoopCallback = (int (__cdecl *)(_DWORD))channel[26];
  g_Audio_MixVoice_LoopDirection = channel[16];
  g_Audio_MixVoice_PositionInt = channel[12];
  g_Audio_MixVoice_PositionFrac = channel[13];
  g_Audio_MixVoice_SampleHistory0 = channel[10];
  g_Audio_MixVoice_SampleHistory1 = channel[11];
  if ( channel[1] && channel[24] == 3 )
  {
    g_Audio_MixVoice_Pan = channel[19];
    playbackRate = channel[15];
    LODWORD(rateFixed) = playbackRate << 16;
    HIDWORD(rateFixed) = HIWORD(playbackRate);
    g_Audio_MixVoice_ResampleStep = rateFixed / (unsigned int)g_CSS_MixSampleRate;
    g_Audio_MixVoice_MaxSourceAdvance = (((unsigned int)g_Audio_MixVoice_ResampleStep * (unsigned __int64)(unsigned int)mixArgs[5]) >> 16) + 2;
LABEL_4:
    queuedState = channel[24];
    if ( queuedState > 2 )
    {
      if ( queuedState == 3 )
      {
        g_Audio_MixVoice_LoopBoundsSwitchPending = 0;
      }
      else
      {
        if ( channel[25] == 2 )
        {
          g_Audio_MixVoice_LoopBoundLow = channel[7];
          g_Audio_MixVoice_LoopBoundHigh = channel[8];
          g_Audio_MixVoice_LoopMode = channel[9];
LABEL_11:
          g_Audio_MixVoice_LoopFinalFlag = channel[18]
                      && (channel[3] == 5 || channel[3] == 4)
                      && ((queueSlot = 40 * channel[17] + g_CSS_QueuedSoundSlotTable, *(_DWORD *)(queueSlot + 12) == 4) || *(_DWORD *)(queueSlot + 12) == 5);
          sampleStep = *channel;
          formatCode = channel[1];
          switch ( formatCode )
          {
            case 3u:
            case 2u:
              goto LABEL_22;
            case 4u:
              sampleStep >>= 2;
              break;
            case 6u:
LABEL_22:
              sampleStep >>= 1;
              break;
          }
          g_Audio_VoiceMixSampleStep = sampleStep;
          while ( 1 )
          {
            if ( !g_Audio_MixVoice_SamplesRemaining )
              goto LABEL_80;
            if ( channel[17] == 5 )
            {
              endPos = channel[14];
              if ( endPos >= g_Audio_MixVoice_PositionInt )
              {
                if ( endPos == g_Audio_MixVoice_PositionInt )
                  goto LABEL_78;
                goto LABEL_37;
              }
            }
            if ( !g_Audio_MixVoice_LoopMode )
            {
              endPos = channel[2];
              goto LABEL_37;
            }
            if ( g_Audio_MixVoice_LoopMode == 1 )
              break;
            if ( g_Audio_MixVoice_LoopDirection != -1 )
            {
              endPos = g_Audio_MixVoice_LoopBoundHigh;
LABEL_37:
              g_Audio_MixVoice_NextChunkEndScratch = endPos + g_Audio_VoiceMixSampleStep;
              distanceFixed = ((unsigned __int64)(endPos - g_Audio_MixVoice_PositionInt) << 16) - (unsigned int)g_Audio_MixVoice_PositionFrac;
              goto LABEL_38;
            }
            distanceFixed = (unsigned int)g_Audio_MixVoice_PositionFrac + ((unsigned __int64)(unsigned int)(g_Audio_MixVoice_PositionInt - g_Audio_MixVoice_LoopBoundLow) << 16);
LABEL_38:
            if ( HIWORD(g_Audio_MixVoice_MaxSourceAdvance) < HIDWORD(distanceFixed) || g_Audio_MixVoice_MaxSourceAdvance << 16 < (unsigned int)distanceFixed )
            {
              spanSamples = g_Audio_MixVoice_SamplesRemaining;
            }
            else
            {
              stepRemainder = distanceFixed % (unsigned int)g_Audio_MixVoice_ResampleStep;
              spanSamples = distanceFixed / (unsigned int)g_Audio_MixVoice_ResampleStep;
              if ( (_DWORD)stepRemainder )
                ++spanSamples;
              if ( spanSamples > (unsigned int)g_Audio_MixVoice_SamplesRemaining )
                spanSamples = g_Audio_MixVoice_SamplesRemaining;
            }
            g_Audio_MixVoice_SamplesRemaining -= spanSamples;
            if ( mixArgs[4] )
            {
              savedArgs = mixArgs;
              savedPosPlusStep = g_Audio_MixVoice_PositionInt + g_Audio_VoiceMixSampleStep;
              savedFrac = g_Audio_MixVoice_PositionFrac;
              stepValue = g_Audio_MixVoice_ResampleStep;
              savedAccum = g_Audio_MixVoice_AccumBufferPtr;
              if ( g_Audio_MixVoice_LoopDirection == -1 )
                stepValue = -g_Audio_MixVoice_ResampleStep;
              g_Audio_MixVoice_MixFunc(spanSamples, stepValue);
              g_Audio_MixVoice_PositionFrac = savedFrac;
              g_Audio_MixVoice_PositionInt = savedPosPlusStep - g_Audio_VoiceMixSampleStep;
              g_Audio_MixVoice_AccumBufferPtr = savedAccum;
              mixArgs = savedArgs;
            }
            else
            {
              signedStep = g_Audio_MixVoice_ResampleStep;
              if ( g_Audio_MixVoice_LoopDirection == -1 )
                signedStep = -g_Audio_MixVoice_ResampleStep;
              posFixed = g_Audio_MixVoice_PositionInt << 16;
              LOWORD(posFixed) = g_Audio_MixVoice_PositionFrac;
              LOWORD(g_Audio_MixVoice_PositionFrac) = signedStep * spanSamples + g_Audio_MixVoice_PositionFrac;
              g_Audio_MixVoice_PositionInt = (__int64)(signedStep * (__int64)spanSamples + __PAIR64__(g_Audio_MixVoice_PositionInt >> 16, posFixed)) >> 16;
              if ( !mixArgs[2] )
              {
                accumPtrSaved = g_Audio_MixVoice_AccumBufferPtr;
                Audio_ZeroMixAccumulatorBuffer(spanSamples, (void *)g_Audio_MixVoice_AccumBufferPtr);
                g_Audio_MixVoice_AccumBufferPtr = accumPtrSaved;
              }
            }
            if ( !g_Audio_MixVoice_LoopMode )
            {
              if ( g_Audio_MixVoice_PositionInt < channel[2] )
                goto LABEL_80;
              if ( g_Audio_MixVoice_LoopFinalFlag != 1 )
              {
                channel[24] = 1;
                goto LABEL_78;
              }
LABEL_74:
              CSS_ChannelLoadQueuedSound(mixArgs[2]);
              if ( channel[3] == 5 )
              {
                g_Audio_MixVoice_PositionInt = channel[4];
                g_Audio_MixVoice_PositionFrac = 0;
                goto LABEL_4;
              }
              channel[24] = 1;
              goto LABEL_78;
            }
            if ( g_Audio_MixVoice_LoopDirection == -1 )
            {
              reversePos = g_Audio_MixVoice_PositionInt;
              if ( g_Audio_MixVoice_PositionInt >= g_Audio_MixVoice_LoopBoundLow )
                goto LABEL_80;
              if ( g_Audio_MixVoice_LoopCallback )
                reversePos = g_Audio_MixVoice_LoopCallback(mixArgs[2]);
              g_Audio_MixVoice_LoopDirection = 1;
              HIDWORD(reflectedPos) = reversePos;
              LODWORD(reflectedPos) = reversePos << 16;
              SHIDWORD(reflectedPos) >>= 16;
              LOWORD(reflectedPos) = g_Audio_MixVoice_PositionFrac;
              LOWORD(g_Audio_MixVoice_PositionFrac) = -(__int16)g_Audio_MixVoice_PositionFrac;
              g_Audio_MixVoice_PositionInt = ((2 * __PAIR64__(HIWORD(g_Audio_MixVoice_LoopBoundLow), g_Audio_MixVoice_LoopBoundLow << 16) - reflectedPos) >> 32 << 16) | ((unsigned int)((g_Audio_MixVoice_LoopBoundLow << 17) - reflectedPos) >> 16);
              goto LABEL_72;
            }
            loopReturnPos = g_Audio_MixVoice_PositionInt;
            if ( g_Audio_MixVoice_PositionInt >= (unsigned int)g_Audio_MixVoice_LoopBoundHigh )
            {
              if ( g_Audio_MixVoice_LoopCallback )
                loopReturnPos = g_Audio_MixVoice_LoopCallback(mixArgs[2]);
              if ( g_Audio_MixVoice_LoopFinalFlag == 1 )
                goto LABEL_74;
              if ( g_Audio_MixVoice_LoopBoundsSwitchPending == 1 )
              {
                channel[25] = 2;
                g_Audio_MixVoice_LoopBoundsSwitchPending = 0;
                g_Audio_MixVoice_LoopBoundLow = channel[7];
                g_Audio_MixVoice_LoopBoundHigh = channel[8];
                g_Audio_MixVoice_LoopMode = channel[9];
              }
              else
              {
                if ( g_Audio_MixVoice_LoopMode == 1 )
                {
                  g_Audio_MixVoice_PositionInt -= g_Audio_MixVoice_LoopBoundHigh - g_Audio_MixVoice_LoopBoundLow;
                }
                else
                {
                  g_Audio_MixVoice_LoopDirection = -1;
                  HIDWORD(reflected64) = loopReturnPos;
                  LODWORD(reflected64) = loopReturnPos << 16;
                  SHIDWORD(reflected64) >>= 16;
                  LOWORD(reflected64) = g_Audio_MixVoice_PositionFrac;
                  LOWORD(g_Audio_MixVoice_PositionFrac) = -(__int16)g_Audio_MixVoice_PositionFrac;
                  g_Audio_MixVoice_PositionInt = ((2 * __PAIR64__(HIWORD(g_Audio_MixVoice_LoopBoundHigh), g_Audio_MixVoice_LoopBoundHigh << 16) - reflected64) >> 32 << 16) | ((unsigned int)((g_Audio_MixVoice_LoopBoundHigh << 17) - reflected64) >> 16);
                }
LABEL_72:
                if ( !g_Audio_MixVoice_SamplesRemaining )
                  goto LABEL_80;
              }
            }
            else if ( channel[17] != 5 )
            {
              goto LABEL_80;
            }
          }
          endPos = g_Audio_MixVoice_LoopBoundHigh;
          goto LABEL_37;
        }
        g_Audio_MixVoice_LoopBoundsSwitchPending = 1;
      }
      g_Audio_MixVoice_LoopBoundLow = channel[4];
      g_Audio_MixVoice_LoopBoundHigh = channel[5];
      g_Audio_MixVoice_LoopMode = channel[6];
      goto LABEL_11;
    }
  }
LABEL_78:
  if ( !mixArgs[2] )
    Audio_ZeroMixAccumulatorBuffer(g_Audio_MixVoice_SamplesRemaining, (void *)g_Audio_MixVoice_AccumBufferPtr);
LABEL_80:
  channel[12] = g_Audio_MixVoice_PositionInt;
  channel[13] = g_Audio_MixVoice_PositionFrac;
  channel[16] = g_Audio_MixVoice_LoopDirection;
  channel[10] = g_Audio_MixVoice_SampleHistory0;
  channel[11] = g_Audio_MixVoice_SampleHistory1;
}
// 46B6CF: simplified comparisons for 'eax.4': ==0 || ==1 became <2u
// 46B6CF: simplified comparisons for 'eax.4': <2u || ==2 became <3u
// 519B58: using guessed type int dword_519B58;
// 519B5C: using guessed type int dword_519B5C;
// 519B60: using guessed type int dword_519B60;
// 519B64: using guessed type int dword_519B64;
// 519B68: using guessed type int dword_519B68;
// 519B6C: using guessed type int dword_519B6C;
// 519B70: using guessed type int dword_519B70;
// 519B74: using guessed type int dword_519B74;
// 519B78: using guessed type int dword_519B78;
// 519B7C: using guessed type int dword_519B7C;
// 519B80: using guessed type int dword_519B80;
// 519B84: using guessed type int dword_519B84;
// 519B88: using guessed type int dword_519B88;
// 519B8C: using guessed type int dword_519B8C;
// 519B90: using guessed type int (__fastcall *dword_519B90)(_DWORD, _DWORD);
// 519B98: using guessed type int dword_519B98;
// 519BA4: using guessed type int dword_519BA4;
// 519BA8: using guessed type int (__cdecl *dword_519BA8)(_DWORD);
// 519BAE: using guessed type int dword_519BAE;
// 519BB2: using guessed type int dword_519BB2;
// 519BC6: using guessed type int dword_519BC6;
// 54DB90: using guessed type int dword_54DB90;
// 54DB94: using guessed type int dword_54DB94;
// 54DB9C: using guessed type int dword_54DB9C;

//----- (0046BCE4) --------------------------------------------------------
int  Audio_MixMonoVoiceIntoBuffer(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  int (__thiscall *mixInnerFunc)(signed int); // eax
  int result; // eax

  g_Audio_MixFormatDispatchTable = (int)&g_Audio_MixMonoVoiceDispatchBase;
  if ( sampleCount )
  {
    if ( !accumFlag )
      memset(accumBuffer, 0, 4 * sampleCount);
    mixInnerFunc = *(int (__thiscall **)(signed int))(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
    g_Audio_MixVoice_StepIntArg = stepFixed >> 16;
    return mixInnerFunc(stepFixed << 16);
  }
  return result;
}
// 46BC89: using guessed type void *off_46BC89;
// 519B94: using guessed type int dword_519B94;
// 519BA0: using guessed type int dword_519BA0;
// 54DB8C: using guessed type int dword_54DB8C;

//----- (0046BDC2) --------------------------------------------------------
unsigned int  Audio_MixPannedVoiceIntoBuffer(
        unsigned int result,
        signed int stepFixed,
        unsigned int sampleCount,
        __int16 volumeAndFlag,
        void *accumBuffer)
{
  int (__thiscall *mixInnerFunc)(unsigned int); // eax
  __int16 packedCount; // cx

  g_Audio_MixFormatDispatchTable = (int)&g_Audio_MixPannedVoiceDispatchBase;
  if ( sampleCount )
  {
    if ( !(_BYTE)volumeAndFlag )
    {
      HIWORD(result) = 0;
      memset(accumBuffer, 0, 8 * sampleCount);
    }
    if ( (_BYTE)g_Audio_MixVoice_Pan == 0x80 )
    {
      g_Audio_MixVoice_LeftVolumeStep = -1;
      g_Audio_MixVoice_RightVolumeStep = 1;
      g_Audio_MixVoice_LeftVolume = HIBYTE(volumeAndFlag);
      g_Audio_MixVoice_RightVolume = HIBYTE(volumeAndFlag);
    }
    else
    {
      g_Audio_MixVoice_LeftVolumeStep = 0;
      g_Audio_MixVoice_RightVolumeStep = 0;
      if ( (g_Audio_MixVoice_Pan & 0x80u) == 0 )
      {
        g_Audio_MixVoice_RightVolume = HIBYTE(volumeAndFlag);
        LOWORD(result) = (unsigned __int8)(64 - g_Audio_MixVoice_Pan) * HIBYTE(volumeAndFlag);
        g_Audio_MixVoice_LeftVolume = result >> 6;
      }
      else
      {
        g_Audio_MixVoice_LeftVolume = HIBYTE(volumeAndFlag);
        LOWORD(result) = (unsigned __int8)(g_Audio_MixVoice_Pan + 64) * HIBYTE(volumeAndFlag);
        g_Audio_MixVoice_RightVolume = result >> 6;
      }
    }
    g_Audio_MixVoice_PanStepFracArg = stepFixed << 16;
    mixInnerFunc = *(int (__thiscall **)(unsigned int))(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
    LOBYTE(packedCount) = (sampleCount >> 2) + 1;
    g_Audio_MixVoice_StepIntArg = stepFixed >> 16;
    HIBYTE(packedCount) = (unsigned __int8)(g_Audio_MixVoice_RightVolume + 1) >> 1;
    return mixInnerFunc(((unsigned int)g_CssMixBufferAlignedBase >> 2) + (packedCount & 0xFF00));
  }
  return result;
}
// 46BCF3: using guessed type void *off_46BCF3;
// 519B94: using guessed type int dword_519B94;
// 519B98: using guessed type int dword_519B98;
// 519B9C: using guessed type int dword_519B9C;
// 519BA0: using guessed type int dword_519BA0;
// 519BAC: using guessed type char byte_519BAC;
// 519BAD: using guessed type char byte_519BAD;
// 519BB6: using guessed type int dword_519BB6;
// 519BBA: using guessed type int dword_519BBA;
// 54DB8C: using guessed type int dword_54DB8C;

// Recovered shared voice-mix span-dispatch chunks (loc_46BB40 / loc_46BB9A
// in clash95.asm). Each Audio_SelectMixFormat* entry below first loads its own
// inner-loop pointer table into g_Audio_MixFormatDispatchTable, then tail-jumps
// into one of these shared chunks, which selects an unrolled mix variant by
// destination alignment and calls it. Audio_MixMonoVoiceIntoBuffer and
// Audio_MixPannedVoiceIntoBuffer inline these same two chunks directly.
static int Audio_MixVoiceSpanDispatch_46BB40(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  int (__thiscall *mixInnerFunc)(signed int); // eax
  int result; // eax

  if ( sampleCount )
  {
    if ( !accumFlag )
      memset(accumBuffer, 0, 4 * sampleCount);
    mixInnerFunc = *(int (__thiscall **)(signed int))(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
    g_Audio_MixVoice_StepIntArg = stepFixed >> 16;
    return mixInnerFunc(stepFixed << 16);
  }
  return result;
}

static unsigned int Audio_MixVoiceSpanDispatch_46BB9A(
        unsigned int result,
        signed int stepFixed,
        unsigned int sampleCount,
        __int16 volumeAndFlag,
        void *accumBuffer)
{
  int (__thiscall *mixInnerFunc)(unsigned int); // eax
  __int16 packedCount; // cx

  if ( sampleCount )
  {
    if ( !(_BYTE)volumeAndFlag )
    {
      HIWORD(result) = 0;
      memset(accumBuffer, 0, 8 * sampleCount);
    }
    if ( (_BYTE)g_Audio_MixVoice_Pan == 0x80 )
    {
      g_Audio_MixVoice_LeftVolumeStep = -1;
      g_Audio_MixVoice_RightVolumeStep = 1;
      g_Audio_MixVoice_LeftVolume = HIBYTE(volumeAndFlag);
      g_Audio_MixVoice_RightVolume = HIBYTE(volumeAndFlag);
    }
    else
    {
      g_Audio_MixVoice_LeftVolumeStep = 0;
      g_Audio_MixVoice_RightVolumeStep = 0;
      if ( (g_Audio_MixVoice_Pan & 0x80u) == 0 )
      {
        g_Audio_MixVoice_RightVolume = HIBYTE(volumeAndFlag);
        LOWORD(result) = (unsigned __int8)(64 - g_Audio_MixVoice_Pan) * HIBYTE(volumeAndFlag);
        g_Audio_MixVoice_LeftVolume = result >> 6;
      }
      else
      {
        g_Audio_MixVoice_LeftVolume = HIBYTE(volumeAndFlag);
        LOWORD(result) = (unsigned __int8)(g_Audio_MixVoice_Pan + 64) * HIBYTE(volumeAndFlag);
        g_Audio_MixVoice_RightVolume = result >> 6;
      }
    }
    g_Audio_MixVoice_PanStepFracArg = stepFixed << 16;
    mixInnerFunc = *(int (__thiscall **)(unsigned int))(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
    LOBYTE(packedCount) = (sampleCount >> 2) + 1;
    g_Audio_MixVoice_StepIntArg = stepFixed >> 16;
    HIBYTE(packedCount) = (unsigned __int8)(g_Audio_MixVoice_RightVolume + 1) >> 1;
    return mixInnerFunc(((unsigned int)g_CssMixBufferAlignedBase >> 2) + (packedCount & 0xFF00));
  }
  return result;
}

//----- (0046BE88) --------------------------------------------------------
int Audio_SelectMixFormat1Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat1MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46BDD1: using guessed type void *off_46BDD1;
// 519B94: using guessed type int dword_519B94;

//----- (0046BF5E) --------------------------------------------------------
unsigned int Audio_SelectMixFormat1Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat1StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46BE97: using guessed type void *off_46BE97;
// 519B94: using guessed type int dword_519B94;

//----- (0046C030) --------------------------------------------------------
int Audio_SelectMixFormat2Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat2MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46BF6D: using guessed type void *off_46BF6D;
// 519B94: using guessed type int dword_519B94;

//----- (0046C1A2) --------------------------------------------------------
unsigned int Audio_SelectMixFormat2Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat2StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46C03F: using guessed type void *off_46C03F;
// 519B94: using guessed type int dword_519B94;

//----- (0046C2FC) --------------------------------------------------------
int Audio_SelectMixFormat3Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat3MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46C1B1: using guessed type void *off_46C1B1;
// 519B94: using guessed type int dword_519B94;

//----- (0046C472) --------------------------------------------------------
unsigned int Audio_SelectMixFormat3Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat3StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46C30B: using guessed type void *off_46C30B;
// 519B94: using guessed type int dword_519B94;

//----- (0046C6B4) --------------------------------------------------------
int Audio_SelectMixFormat4Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat4MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46C481: using guessed type void *off_46C481;
// 519B94: using guessed type int dword_519B94;

//----- (0046C996) --------------------------------------------------------
unsigned int Audio_SelectMixFormat4Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat4StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46C6C3: using guessed type void *off_46C6C3;
// 519B94: using guessed type int dword_519B94;

//----- (0046CE10) --------------------------------------------------------
int Audio_SelectMixFormat5Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat5MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46C9A5: using guessed type void *off_46C9A5;
// 519B94: using guessed type int dword_519B94;

//----- (0046D2A6) --------------------------------------------------------
unsigned int Audio_SelectMixFormat5Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat5StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46CE1F: using guessed type void *off_46CE1F;
// 519B94: using guessed type int dword_519B94;

//----- (0046D2B5) --------------------------------------------------------
int __cdecl Audio_ClearGlobalMixBuffer(int sampleCount)
{
  Audio_ZeroMixAccumulatorBuffer(sampleCount, (void *)g_CSS_MixAccumBufferPtr);
  return 0;
}

//----- (0046D2D1) --------------------------------------------------------
int  Audio_ZeroMixAccumulatorBuffer(int sampleCount, void *accumBuffer)
{
  int result; // eax

  if ( sampleCount )
  {
    result = 0;
    if ( g_CSS_MixChannelCount_54DBA4 == 2 )
      sampleCount *= 2;
    memset(accumBuffer, 0, 4 * sampleCount);
  }
  return result;
}
// 54DBA4: using guessed type int dword_54DBA4;

//----- (0046D2F0) --------------------------------------------------------
int __cdecl Audio_GetFixedCapabilityFlag(_DWORD *capabilityOut)
{
  *capabilityOut = 1;
  return 0;
}

//----- (0046D300) --------------------------------------------------------
int __cdecl Audio_SetMixerParamValue(int driver, int volume)
{
  g_CSS_NullDriverMasterVolume = volume;
  return 0;
}
// 519BD0: using guessed type int dword_519BD0;

//----- (0046D320) --------------------------------------------------------
int __cdecl CSS_NullDriver_GetZero(_DWORD *valueOut)
{
  *valueOut = 0;
  return 0;
}

//----- (0046D330) --------------------------------------------------------
int __cdecl CSS_NullDriver_GetMasterVolume(_DWORD *volumeOut)
{
  *volumeOut = g_CSS_NullDriverMasterVolume;
  return 0;
}
// 519BD0: using guessed type int dword_519BD0;

//----- (0046D350) --------------------------------------------------------
int __cdecl CSS_Mem_TryAllocRaw(int byteCount, _DWORD *ptrOut)
{
  int v2; // ecx
  __int64 v3; // rax

  LODWORD(v3) = byteCount;
  *ptrOut = 0;
  if ( byteCount )
  {
    v3 = nmalloc_(v2, ptrOut);
    *(_DWORD *)HIDWORD(v3) = v3;
  }
  return v3;
}
// 46D363: variable 'v2' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);

//----- (0046D370) --------------------------------------------------------
int __cdecl CSS_Mem_TryAlloc(int byteCount, _DWORD *ptrOut)
{
  return CSS_Mem_TryAllocRaw(byteCount, ptrOut);
}

//----- (0046D390) --------------------------------------------------------
int __cdecl CSS_Mem_FreeIfSet(int ptr)
{
  int v1; // ecx
  int result; // eax

  result = ptr;
  if ( ptr )
    return nfree_(v1);
  return result;
}
// 46D396: variable 'v1' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);

//----- (0046D3A0) --------------------------------------------------------
_DWORD * CSS_FileStream_Create(_DWORD *stream, int source, int bufferSizeHint, int dataBytes)
{
  int hintBytes; // edx
  int blockCount; // edx
  int totalBytes; // edx

  stream[1] = source;
  stream[7] = 0;
  stream[8] = 0;
  stream[9] = 0;
  stream[10] = 0;
  stream[14] = bufferSizeHint;
  *stream = g_CSSFileStream_VTable;
  stream[2] = (*(int (**)(void))(*(_DWORD *)source + 4))();
  stream[3] = stream[2];
  stream[4] = dataBytes + stream[3];
  stream[5] = stream[3];
  stream[6] = 0x7FFFFFFF;
  stream[11] = 0;
  hintBytes = stream[14];
  stream[13] = 0x4000;
  blockCount = hintBytes / stream[13];
  if ( blockCount < 2 )
    blockCount = 2;
  totalBytes = stream[13] * (blockCount + 1);
  stream[14] = totalBytes;
  stream[12] = 0;
  CSS_Mem_TryAlloc(totalBytes, stream + 15);
  stream[8] = stream[14];
  stream[10] = stream[14];
  return stream;
}
// 5105B4: using guessed type int (*off_5105B4[12])();

//----- (0046D460) --------------------------------------------------------
_DWORD * CSS_FileStream_Destroy(_DWORD *stream, char dtorFlags, int a3, int a4, int a5)
{
  if ( (dtorFlags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a3, &g_CSSFileStream_DtorArrayDescriptor);
    j_j__nfree_();
    return stream;
  }
  else
  {
    *stream = g_CSSFileStream_VTable;
    CSS_Mem_FreeIfSet(stream[15]);
    (*(void (__cdecl **)(int, int, int))(*(_DWORD *)g_MediaFileStreamProvider + 20))(a3, a5, a4);
    if ( (dtorFlags & 2) != 0 )
      j__nfree_();
    return stream;
  }
}
// 46D460: could not find valid save-restore pair for edi
// 46D460: could not find valid save-restore pair for esi
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 5105B4: using guessed type int (*off_5105B4[12])();
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046D530) --------------------------------------------------------
int  CSS_FileStream_FillSequential(int stream)
{
  int result; // eax
  int v2; // ecx

  result = (*(int (__thiscall **)(int))(**(_DWORD **)(stream + 4) + 20))(stream);
  *(_DWORD *)(v2 + 8) += result;
  return result;
}
// 46D53C: variable 'v2' is possibly undefined

//----- (0046D550) --------------------------------------------------------
int  CSS_FileStream_FillWithLoopWrap(int stream, int loopStart, int fillBytes, int loopEnd)
{
  int readBytes; // ecx
  int bytesRead; // eax
  int v9; // ecx

  if ( fillBytes < loopEnd - *(_DWORD *)(stream + 8) )
    return CSS_FileStream_FillSequential(stream);
  readBytes = (*(int (**)(void))(**(_DWORD **)(stream + 4) + 20))();
  (***(void (__fastcall ****)(int, int))(stream + 4))(readBytes, loopStart);
  bytesRead = (*(int (**)(void))(**(_DWORD **)(stream + 4) + 20))();
  *(_DWORD *)(stream + 8) = bytesRead + loopStart;
  return v9 + bytesRead;
}
// 46D5B2: variable 'v9' is possibly undefined

//----- (0046D5C0) --------------------------------------------------------
int  CSS_FileStream_FillOneBlock(_DWORD *stream, int blockBytes)
{
  int dataEnd; // esi

  if ( !blockBytes )
    return 0;
  dataEnd = stream[4];
  if ( stream[6] > dataEnd )
    return CSS_FileStream_FillSequential((int)stream);
  if ( stream[2] <= stream[6] )
    return CSS_FileStream_FillWithLoopWrap((int)stream, stream[5], blockBytes, stream[6]);
  return CSS_FileStream_FillWithLoopWrap((int)stream, stream[3], blockBytes, stream[4]);
}

//----- (0046D620) --------------------------------------------------------
int  CSS_FileStream_RefillBuffer(_DWORD *stream)
{
  _DWORD *v1; // ecx
  int bufferedBytes; // eax
  int totalRead; // ebp
  int blocksToRead; // eax
  int blockIndex; // edi
  _DWORD *writePosPtr; // esi
  int bytesRead; // eax
  int maxBlocks; // [esp+4h] [ebp-1Ch]

  v1 = stream;
  bufferedBytes = stream[9] - stream[7];
  totalRead = 0;
  if ( v1[14] - bufferedBytes < v1[13] )
    blocksToRead = 0;
  else
    blocksToRead = (3 * bufferedBytes <= v1[14]) + 1;
  maxBlocks = blocksToRead;
  blockIndex = 0;
  if ( blocksToRead > 0 )
  {
    writePosPtr = v1 + 9;
    do
    {
      if ( v1[11] )
        break;
      bytesRead = CSS_FileStream_FillOneBlock(v1, v1[13]);
      *writePosPtr += bytesRead;
      if ( bytesRead != v1[13] )
        v1[11] = 1;
      ++blockIndex;
      totalRead += bytesRead;
    }
    while ( blockIndex < maxBlocks );
  }
  return totalRead;
}
// 46D66B: variable 'v1' is possibly undefined

//----- (0046D6C0) --------------------------------------------------------
int  CSS_FileStream_PreloadFully(int stream)
{
  int v1; // edx
  int result; // eax

  v1 = stream;
  do
    result = (*(int (**)(void))(*(_DWORD *)v1 + 32))();
  while ( result );
  return result;
}
// 46D6C4: variable 'v1' is possibly undefined

//----- (0046D6E0) --------------------------------------------------------
int  CSS_FileStream_Read(_DWORD *stream, char *dest, int byteCount)
{
  signed int contiguousBytes; // ebx
  int totalCopied; // [esp+8h] [ebp-1Ch]
  int bytesWanted; // [esp+10h] [ebp-14h]

  bytesWanted = byteCount;
  totalCopied = 0;
  if ( stream[9] - stream[7] < byteCount )
    bytesWanted = stream[9] - stream[7];
  while ( bytesWanted )
  {
    contiguousBytes = stream[8] - stream[7] % stream[8];
    if ( contiguousBytes >= bytesWanted )
      contiguousBytes = bytesWanted;
    qmemcpy(dest, (const void *)(stream[7] % stream[8] + stream[15]), contiguousBytes);
    stream[7] += contiguousBytes;
    dest += contiguousBytes;
    totalCopied += contiguousBytes;
    bytesWanted -= contiguousBytes;
  }
  if ( totalCopied < byteCount )
    ++stream[12];
  return totalCopied;
}

//----- (0046D7C0) --------------------------------------------------------
BOOL  CSS_FileStream_IsFinished(_DWORD *stream)
{
  return stream[11] && stream[9] == stream[7];
}

//----- (0046D7F0) --------------------------------------------------------
int  CSS_FileStream_QueryDone(int stream)
{
  return (*(int (**)(void))(*(_DWORD *)stream + 4))();
}

//----- (0046D800) --------------------------------------------------------
signed int  CSS_FileStream_SetLoopRange(_DWORD *stream, int loopStart, int loopEnd)
{
  stream[5] = loopStart + stream[3];
  if ( loopEnd < 0 )
    loopEnd = stream[4];
  stream[6] = loopEnd;
  return 1;
}

//----- (0046D830) --------------------------------------------------------
_DWORD * CSS_FileStream_GetLoopRange(_DWORD *result, _DWORD *loopStartOut, _DWORD *loopEndOut)
{
  if ( result[6] == 0x7FFFFFFF )
  {
    *loopStartOut = 0;
    *loopEndOut = 0;
  }
  else
  {
    *loopStartOut = result[5] - result[3];
    *loopEndOut = result[6] - result[3];
  }
  return result;
}

//----- (0046D870) --------------------------------------------------------
signed int  CSS_FileStream_ClearLoop(_DWORD *stream)
{
  stream[5] = stream[3];
  stream[6] = 0x7FFFFFFF;
  return 1;
}

//----- (0046D890) --------------------------------------------------------
int  CSS_FileStream_GetSourceBytesFetched(int stream)
{
  return *(_DWORD *)(stream + 8) - *(_DWORD *)(stream + 12);
}

//----- (0046D8A0) --------------------------------------------------------
signed int  CSS_FileStream_DispatchIfInRange(int stream, int offset, int callbackArg)
{
  int basePos; // ecx
  int absPos; // edx

  basePos = *(_DWORD *)(stream + 12);
  absPos = basePos + offset;
  if ( absPos < basePos || absPos >= *(_DWORD *)(stream + 16) )
    return 0;
  (***(void (__cdecl ****)(int))(stream + 4))(callbackArg);
  return 1;
}

//----- (0046D8D0) --------------------------------------------------------
_DWORD * CSS_FileStream_New(int source, int bufferBytes)
{
  _DWORD *stream; // eax
  int v5; // edx
  int v6; // ecx

  stream = (_DWORD *)Mem_Alloc(64, bufferBytes, (char)&j____wcpp_4_fs_handler_rtn_, 0);
  if ( stream )
    return CSS_FileStream_Create(stream, source, v6, v5);
  else
    return 0;
}
// 46D937: variable 'v6' is possibly undefined
// 46D937: variable 'v5' is possibly undefined

//----- (0046D960) --------------------------------------------------------
int CSS_InitStreamingLocks()
{
  int v0; // edx
  int v1; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx

  g_StreamServiceLockEntryCount = 0;
  InitializeCriticalSection(&CriticalSection);
  CRT_RegisterFinalizableObject(v1, v0);
  g_CSS_MixerLockNestingCount = 0;
  InitializeCriticalSection(&stru_54D3FC);
  CRT_RegisterFinalizableObject(v3, v2);
  g_CSS_StreamReadThreadLockRefCount = 0;
  InitializeCriticalSection(&stru_54D424);
  CRT_RegisterFinalizableObject(v5, v4);
  g_CSS_StreamServiceThreadLockRefCount = 0;
  InitializeCriticalSection(&stru_54D444);
  return CRT_RegisterFinalizableObject(v7, v6);
}
// 46D97C: variable 'v1' is possibly undefined
// 46D97C: variable 'v0' is possibly undefined
// 46D99C: variable 'v3' is possibly undefined
// 46D99C: variable 'v2' is possibly undefined
// 46D9B8: variable 'v5' is possibly undefined
// 46D9B8: variable 'v4' is possibly undefined
// 46D9D4: variable 'v7' is possibly undefined
// 46D9D4: variable 'v6' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;
// 54D420: using guessed type int dword_54D420;
// 54D440: using guessed type int dword_54D440;

//----- (0046D9F0) --------------------------------------------------------
int CSS_StreamService_NoOpHook()
{
  return 0;
}

//----- (0046DA00) --------------------------------------------------------
unsigned int  CSS_CloseChannel(unsigned int channelIndex, signed int fadeMs)
{
  unsigned int result; // eax
  int *channel; // ebx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-30h]
  int streamObj; // [esp+14h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  result = 52 * channelIndex;
  channel = (int *)(result + g_SoundChannelArrayBase);
  if ( *(_DWORD *)(result + g_SoundChannelArrayBase + 40) )
  {
    channel[10] = 0;
    if ( (channel[9] & 0xC) != 0 )
    {
      CSS_ChannelStop(channelIndex);
      ++g_StreamServiceLockEntryCount;
      EnterCriticalSection(&CriticalSection);
      ++g_CSS_MixerLockNestingCount;
      EnterCriticalSection(&stru_54D3FC);
      channel[9] = 0;
      channel[11] = 0;
      CSS_Mem_FreeIfSet(*channel);
      *channel = 0;
      streamObj = channel[5];
      if ( streamObj )
        (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(*(_DWORD *)streamObj + 44))(
          ExceptionList,
          &j____wcpp_4_fs_handler_rtn_,
          &g_CSSCloseChannel_EHScopeTable,
          1);
      channel[5] = 0;
      --g_CSS_ActiveVoiceCount;
      LeaveCriticalSection(&CriticalSection);
      --g_StreamServiceLockEntryCount;
      LeaveCriticalSection(&stru_54D3FC);
      return g_CSS_MixerLockNestingCount--;
    }
    else
    {
      if ( fadeMs )
        result = CSS_ChannelBeginVolumeFade(channelIndex, 0, fadeMs);
      else
        result = CSS_ChannelMarkIdle(channelIndex);
      *channel = 0;
      channel[9] = 0;
    }
  }
  return result;
}
// 54D3C4: using guessed type int dword_54D3C4;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046DB80) --------------------------------------------------------
int  CSS_Channel_FillSilence(int channel, int byteCount)
{
  int result; // eax
  int bytesRead; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int silenceBytes; // esi
  int v9; // ecx

  if ( !byteCount )
    return 1;
  bytesRead = (***(int (__fastcall ****)(int, int))(channel + 20))(channel, *(_DWORD *)(channel + 12) + *(_DWORD *)channel);
  *(_DWORD *)(v5 + 12) += bytesRead;
  if ( bytesRead >= byteCount )
    return 1;
  result = (*(int (**)(void))(**(_DWORD **)(v5 + 20) + 4))();
  if ( result )
  {
    silenceBytes = byteCount - v6;
    memset_(v7, *(_DWORD *)(v7 + 24));
    *(_DWORD *)(v9 + 12) += silenceBytes;
    *(_DWORD *)(v9 + 28) += silenceBytes;
    return 1;
  }
  return result;
}
// 46DBA8: variable 'v5' is possibly undefined
// 46DBBB: variable 'v6' is possibly undefined
// 46DBC9: variable 'v7' is possibly undefined
// 46DBCE: variable 'v9' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (0046DCA0) --------------------------------------------------------
void  CSS_Channel_ServiceStream(unsigned int channelIndex)
{
  int channel; // ebx
  int playPos; // esi
  int writePos; // edx
  int bufferBytes; // eax
  int fillBytes; // edx
  int fillTarget; // eax
  int leadBytes; // esi
  int savedBufferBytes; // edi
  int v10; // ecx
  int remainingBytes; // edi
  int playPosOut; // [esp+0h] [ebp-14h] BYREF
  int savedPlayPos; // [esp+4h] [ebp-10h]

  channel = g_SoundChannelArrayBase + 52 * channelIndex;
  if ( (!*(_DWORD *)(g_CSS_ActiveSoundDriver + 28) || *(_DWORD *)(channel + 28) >= *(_DWORD *)(channel + 8))
    && (*(int (**)(void))(**(_DWORD **)(channel + 20) + 8))() )
  {
    *(_DWORD *)(channel + 48) = 1;
    return;
  }
  if ( *(_DWORD *)channel && *(_DWORD *)(g_CSS_ActiveSoundDriver + 28) )
  {
    CSS_ChannelGetPlayPosition(channelIndex, &playPosOut);
    if ( playPosOut )
      playPos = playPosOut;
    else
      playPos = *(_DWORD *)(channel + 8);
    writePos = *(_DWORD *)(channel + 12);
    bufferBytes = *(_DWORD *)(channel + 8);
    if ( playPos <= writePos )
    {
      savedPlayPos = playPos;
      leadBytes = bufferBytes - writePos;
      savedBufferBytes = bufferBytes;
      if ( bufferBytes - writePos > bufferBytes )
        leadBytes = bufferBytes;
      if ( !CSS_Channel_FillSilence(channel, leadBytes) )
        goto LABEL_15;
      *(_DWORD *)(v10 + 12) = 0;
      remainingBytes = savedBufferBytes - leadBytes;
      if ( !remainingBytes )
        goto LABEL_15;
      if ( savedPlayPos - *(_DWORD *)(v10 + 16) <= remainingBytes )
        fillBytes = savedPlayPos - *(_DWORD *)(v10 + 16);
      else
        fillBytes = remainingBytes;
      fillTarget = v10;
    }
    else
    {
      if ( playPos - writePos - *(_DWORD *)(channel + 16) <= bufferBytes )
        bufferBytes = playPos - writePos - *(_DWORD *)(channel + 16);
      fillBytes = bufferBytes;
      fillTarget = channel;
    }
    CSS_Channel_FillSilence(fillTarget, fillBytes);
LABEL_15:
    CSS_ChannelSetPositionOffset(channelIndex, *(_DWORD *)(channel + 12));
  }
}
// 46DD6D: variable 'v10' is possibly undefined
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046DEF0) --------------------------------------------------------
int  CSS_Channel_StoreFormatParams(int channel, int formatCode)
{
  int result; // eax

  *(_DWORD *)(channel + 16) = CSS_GetFormatSampleSize(formatCode);
  result = CSS_GetFormatSilenceValue(formatCode);
  *(_DWORD *)(channel + 24) = result;
  return result;
}

//----- (0046DF20) --------------------------------------------------------
void  CSS_Channel_StartFileStream(unsigned int channelIndex, int *formatInfo, int panning, int volume, int a5, int channelFlags)
{
  _DWORD *channel; // ebx
  int chunkBytes; // eax
  int voiceId; // eax
  int streamBuffer; // [esp+0h] [ebp-14h] BYREF
  int savedPanning; // [esp+4h] [ebp-10h]

  savedPanning = panning;
  streamBuffer = 0;
  channel = (_DWORD *)(52 * channelIndex + g_SoundChannelArrayBase);
  CSS_Channel_StoreFormatParams((int)channel, *formatInfo);
  chunkBytes = 3 * formatInfo[2] / g_CSS_StreamServiceRateHz;
  LOBYTE(chunkBytes) = chunkBytes & 0xFC;
  channel[1] = chunkBytes;
  channel[2] = channel[1] * channel[4];
  CSS_Mem_TryAlloc(channel[2], &streamBuffer);
  channel[3] = 0;
  channel[7] = 0;
  CSS_ChannelInitPlayback(channelIndex, streamBuffer, channel[2], *formatInfo, formatInfo[2]);
  CSS_ChannelMarkIdle(channelIndex);
  CSS_ChannelSetVolumeImmediate(channelIndex, volume);
  CSS_ChannelSetPanning(channelIndex, savedPanning);
  channel[12] = 0;
  channel[11] = 0;
  channel[9] = channelFlags;
  voiceId = g_CSS_VoiceSequenceCounter++;
  channel[10] = voiceId;
  *channel = streamBuffer;
  CSS_Channel_ServiceStream(channelIndex);
  ++g_CSS_ActiveVoiceCount;
}
// 519CB0: using guessed type int dword_519CB0;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C4: using guessed type int dword_54D3C4;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E100) --------------------------------------------------------
int  CSS_SampleCache_FreeEntry(int *entry)
{
  g_CSS_SampleCacheBytesUsed -= entry[2];
  CSS_Mem_FreeIfSet(*entry);
  CSS_Mem_FreeIfSet(entry[4]);
  return CSS_Mem_FreeIfSet((int)entry);
}
// 54D3BC: using guessed type int dword_54D3BC;

//----- (0046E140) --------------------------------------------------------
signed int  CSS_SampleCache_EvictEntry(int **entryLink)
{
  signed int channelIndex; // ebx
  int channelOffset; // esi
  int *entry; // eax

  channelIndex = 0;
  if ( g_CssVoicePoolSize <= 0 )
  {
LABEL_7:
    entry = *entryLink;
    *entryLink = (int *)(*entryLink)[5];
    CSS_SampleCache_FreeEntry(entry);
    return 1;
  }
  else
  {
    channelOffset = 0;
    while ( !*(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40) || *(_DWORD *)(channelOffset + g_SoundChannelArrayBase) != **entryLink || !CSS_ChannelIsPlaying(channelIndex) )
    {
      ++channelIndex;
      channelOffset += 52;
      if ( channelIndex >= g_CssVoicePoolSize )
        goto LABEL_7;
    }
    return 0;
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E1B0) --------------------------------------------------------
int  CSS_SampleCache_MakeRoom(int byteCount)
{
  int **link; // edx
  int bytesNeeded; // ecx
  int result; // eax
  int node; // edx

  link = (int **)&g_SampleCacheListHead;
  bytesNeeded = byteCount;
  while ( bytesNeeded + g_CSS_SampleCacheBytesUsed > g_CSS_SampleCacheByteBudget && CSS_SampleCache_EvictEntry(link) )
    ;
  result = bytesNeeded + g_CSS_SampleCacheBytesUsed;
  if ( bytesNeeded + g_CSS_SampleCacheBytesUsed > g_CSS_SampleCacheByteBudget )
  {
    node = g_SampleCacheListHead;
    while ( 1 )
    {
      result = bytesNeeded + g_CSS_SampleCacheBytesUsed;
      if ( bytesNeeded + g_CSS_SampleCacheBytesUsed <= g_CSS_SampleCacheByteBudget || !*(_DWORD *)(node + 20) )
        break;
      if ( !CSS_SampleCache_EvictEntry((int **)(node + 20)) )
        node = *(_DWORD *)(node + 20);
    }
  }
  return result;
}
// 46E1C7: variable 'v2' is possibly undefined
// 46E1F5: variable 'v4' is possibly undefined
// 46E203: variable 'v1' is possibly undefined
// 54D3B8: using guessed type int dword_54D3B8;
// 54D3BC: using guessed type int dword_54D3BC;
// 54D3C0: using guessed type int dword_54D3C0;

//----- (0046E220) --------------------------------------------------------
int  CSS_SampleCache_AppendEntry(int result, int entry)
{
  for ( ; *(_DWORD *)(result + 20); result = *(_DWORD *)(result + 20) )
    ;
  *(_DWORD *)(result + 20) = entry;
  return result;
}

//----- (0046E240) --------------------------------------------------------
int  CSS_SampleCache_TouchEntry(int *listHead)
{
  int v2; // ecx
  int result; // eax

  CSS_SampleCache_AppendEntry(*listHead, *listHead);
  *listHead = *(_DWORD *)(v2 + 20);
  result = v2;
  *(_DWORD *)(v2 + 20) = 0;
  return result;
}
// 46E250: variable 'v2' is possibly undefined

//----- (0046E270) --------------------------------------------------------
int  CSS_SampleCache_FindAndTouch(int fileName)
{
  int v3; // ecx
  int v4; // ecx

  if ( !g_SampleCacheListHead )
    return 0;
  if ( stricmp_(g_SampleCacheListHead, fileName) )
  {
    while ( *(_DWORD *)(v3 + 20) )
    {
      if ( !stricmp_(v3, fileName) )
        return CSS_SampleCache_TouchEntry((int *)(v4 + 20));
      v3 = *(_DWORD *)(v4 + 20);
    }
    return 0;
  }
  return CSS_SampleCache_TouchEntry(&g_SampleCacheListHead);
}
// 46E293: variable 'v3' is possibly undefined
// 46E2AA: variable 'v4' is possibly undefined
// 484E2A: using guessed type int __fastcall stricmp_(_DWORD, _DWORD);
// 54D3B8: using guessed type int dword_54D3B8;

//----- (0046E2D0) --------------------------------------------------------
struct _EXCEPTION_REGISTRATION_RECORD *CSS_SweepFinishedChannels()
{
  int channelOffset; // ebx
  signed int i; // ecx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  channelOffset = 0;
  for ( i = 0; i < g_CssVoicePoolSize; channelOffset += 52 )
  {
    if ( *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 48) )
      CSS_CloseChannel(i, 0);
    ++i;
  }
  return ExceptionList;
}
// 46E328: variable 'i' is possibly undefined
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E350) --------------------------------------------------------
struct _EXCEPTION_REGISTRATION_RECORD *CSS_ServiceStreamingChannels()
{
  int channelOffset; // ebx
  signed int i; // esi
  int channel; // eax
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-2Ch]
  tagRECT *ehHandler; // [esp+4h] [ebp-28h]
  void *ehScopeTable; // [esp+8h] [ebp-24h]
  int tryLevel; // [esp+Ch] [ebp-20h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  channelOffset = 0;
  ehHandler = &j____wcpp_4_fs_handler_rtn_;
  ehScopeTable = &g_CSSServiceStreamingChannels_EHScopeTable;
  tryLevel = 0;
  CSS_StreamService_NoOpHook();
  for ( i = 0; i < g_CssVoicePoolSize; channelOffset += 52 )
  {
    channel = channelOffset + g_SoundChannelArrayBase;
    if ( *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 44)
      && *(_DWORD *)(channel + 40)
      && (*(_BYTE *)(channel + 36) & 0xC) != 0
      && CSS_ChannelIsPlaying(i) )
    {
      (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(**(_DWORD **)(channelOffset + g_SoundChannelArrayBase + 20)
                                                                                           + 32))(
        ExceptionList,
        ehHandler,
        ehScopeTable,
        tryLevel);
    }
    ++i;
  }
  return CSS_SweepFinishedChannels();
}
// 46E3C9: variable 'ExceptionList' is possibly undefined
// 46E3C9: variable 'v5' is possibly undefined
// 46E3C9: variable 'v6' is possibly undefined
// 46E3C9: variable 'v7' is possibly undefined
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E400) --------------------------------------------------------
int __stdcall CSS_StreamReadingThreadProc(int threadParam)
{
  ++g_CSS_StreamReadThreadLockRefCount;
  EnterCriticalSection(&stru_54D424);
  while ( g_CSS_StreamReadingActive )
  {
    ++g_StreamServiceLockEntryCount;
    EnterCriticalSection(&CriticalSection);
    CSS_ServiceStreamingChannels();
    LeaveCriticalSection((LPCRITICAL_SECTION)(&g_StreamServiceLockEntryCount + 1));
    --g_StreamServiceLockEntryCount;
    Sleep(1000 / g_CSS_StreamServiceRateHz);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(&g_CSS_StreamReadThreadLockRefCount + 1));
  --g_CSS_StreamReadThreadLockRefCount;
  return 0;
}
// 519CB0: using guessed type int dword_519CB0;
// 54D3D8: using guessed type int dword_54D3D8;
// 54D414: using guessed type int dword_54D414;
// 54D420: using guessed type int dword_54D420;

//----- (0046E510) --------------------------------------------------------
_DWORD *__stdcall CSS_PauseStreamReading()
{
  _DWORD *result; // eax
  int *lockCounter; // ebx
  _DWORD ehFrame[3]; // [esp+0h] [ebp-20h] BYREF
  int tryLevel; // [esp+Ch] [ebp-14h]
  int *lockCounterPtr; // [esp+14h] [ebp-Ch]

  result = ehFrame;
  ehFrame[0] = NtCurrentTeb()->NtTib.ExceptionList;
  ehFrame[1] = &j____wcpp_4_fs_handler_rtn_;
  ehFrame[2] = &g_CSSPauseStreamReading_EHScopeTable;
  tryLevel = 0;
  if ( g_CSS_StreamReadingActive )
  {
    lockCounterPtr = &g_StreamServiceLockEntryCount;
    ++g_StreamServiceLockEntryCount;
    EnterCriticalSection(&CriticalSection);
    tryLevel = 1;
    SuspendThread(hThread);
    tryLevel = 0;
    lockCounter = lockCounterPtr;
    LeaveCriticalSection((LPCRITICAL_SECTION)(lockCounterPtr + 1));
    return (_DWORD *)(*lockCounter)--;
  }
  return result;
}
// 54D3D8: using guessed type int dword_54D3D8;
// 54D414: using guessed type int dword_54D414;

//----- (0046E5C0) --------------------------------------------------------
DWORD __stdcall CSS_ResumeStreamReading()
{
  return ResumeThread(hThread);
}

//----- (0046E5D0) --------------------------------------------------------
int __stdcall CSS_StreamBufferServiceThreadProc(int threadParam)
{
  signed int channelIndex; // ebx
  int channelOffset; // esi
  int channel; // eax

  ++g_CSS_StreamServiceThreadLockRefCount;
  EnterCriticalSection(&stru_54D444);
  while ( g_CSS_StreamThreadRunning )
  {
    ++g_CSS_MixerLockNestingCount;
    EnterCriticalSection(&stru_54D3FC);
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      channelOffset = 0;
      do
      {
        channel = channelOffset + g_SoundChannelArrayBase;
        if ( *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 44)
          && *(_DWORD *)(channel + 40)
          && (*(_BYTE *)(channel + 36) & 0xC) != 0
          && CSS_ChannelIsPlaying(channelIndex) )
        {
          CSS_Channel_ServiceStream(channelIndex);
        }
        ++channelIndex;
        channelOffset += 52;
      }
      while ( channelIndex < g_CssVoicePoolSize );
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(&g_CSS_MixerLockNestingCount + 1));
    --g_CSS_MixerLockNestingCount;
    Sleep(1000 / g_CSS_StreamServiceRateHz);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(&g_CSS_StreamServiceThreadLockRefCount + 1));
  --g_CSS_StreamServiceThreadLockRefCount;
  return 0;
}
// 519CB0: using guessed type int dword_519CB0;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D3F8: using guessed type int dword_54D3F8;
// 54D440: using guessed type int dword_54D440;
// 54D45C: using guessed type int dword_54D45C;

//----- (0046E870) --------------------------------------------------------
_DWORD *__stdcall CSS_EmptySampleCache()
{
  _DWORD *result; // eax
  int channelOffset; // ebx
  signed int i; // ecx
  char channelFlags; // dl
  int *entry; // eax
  _DWORD ehFrame[6]; // [esp+Ch] [ebp-18h] BYREF

  result = ehFrame;
  ehFrame[0] = NtCurrentTeb()->NtTib.ExceptionList;
  channelOffset = 0;
  ehFrame[1] = &j____wcpp_4_fs_handler_rtn_;
  ehFrame[2] = &g_CSSEmptySampleCache_EHScopeTable;
  ehFrame[3] = 0;
  for ( i = 0; i < g_CssVoicePoolSize; channelOffset += 52 )
  {
    result = (_DWORD *)(channelOffset + g_SoundChannelArrayBase);
    channelFlags = *(_BYTE *)(channelOffset + g_SoundChannelArrayBase + 36);
    if ( (channelFlags & 1) != 0 || (channelFlags & 2) != 0 )
      result = (_DWORD *)CSS_CloseChannel(i, 0);
    ++i;
  }
  while ( g_SampleCacheListHead )
  {
    entry = (int *)g_SampleCacheListHead;
    g_SampleCacheListHead = *(_DWORD *)(g_SampleCacheListHead + 20);
    result = (_DWORD *)CSS_SampleCache_FreeEntry(entry);
  }
  return result;
}
// 46E8D1: variable 'i' is possibly undefined
// 54D3B8: using guessed type int dword_54D3B8;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E910) --------------------------------------------------------
void  CSS_Channel_StartMemSound(unsigned int channelIndex, int voiceId, int volume, int *sampleEntry, int panning, signed int fadeMs)
{
  int channelBase; // edx
  int v9; // ecx

  CSS_Channel_StoreFormatParams(52 * channelIndex + g_SoundChannelArrayBase, sampleEntry[1]);
  channelBase = g_SoundChannelArrayBase;
  *(_DWORD *)(v9 + g_SoundChannelArrayBase + 36) = 1;
  *(_DWORD *)(v9 + channelBase + 48) = 0;
  *(_DWORD *)(v9 + channelBase + 40) = voiceId;
  *(_DWORD *)(channelBase + v9) = *sampleEntry;
  CSS_ChannelQueueSound(channelIndex, *sampleEntry, sampleEntry[2], sampleEntry[3], sampleEntry[1]);
  CSS_ChannelSetVolumeImmediate(channelIndex, 0);
  CSS_ChannelBeginVolumeFade(channelIndex, volume, fadeMs);
  CSS_ChannelSetPanning(channelIndex, panning);
}
// 46E937: variable 'v9' is possibly undefined
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E9A0) --------------------------------------------------------
int  CSS_Channel_SelectAndPlay(int *sampleEntry, int volume, signed int fadeMs, int panning)
{
  unsigned int bestChannel; // edi
  int scanIndex; // eax
  int bestScore; // ebx
  int channelOffset; // ecx
  int channelState; // esi
  int voiceId; // esi

  bestChannel = -1;
  scanIndex = 0;
  bestScore = g_CSS_MemSoundStealBias + g_CSS_VoiceSequenceCounter;
  if ( g_CssVoicePoolSize > 0 )
  {
    channelOffset = 0;
    do
    {
      channelState = *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 36);
      if ( g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40) < bestScore )
      {
        bestScore = g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40);
        bestChannel = scanIndex;
      }
      ++scanIndex;
      channelOffset += 52;
    }
    while ( scanIndex < g_CssVoicePoolSize );
  }
  if ( bestChannel == -1 )
    return 0;
  CSS_CloseChannel(bestChannel, 0);
  voiceId = g_CSS_VoiceSequenceCounter++;
  CSS_Channel_StartMemSound(bestChannel, voiceId, volume, sampleEntry, panning, fadeMs);
  return voiceId;
}
// 519C8C: using guessed type int dword_519C8C[];
// 519C90: using guessed type int dword_519C90;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046EA90) --------------------------------------------------------
_DWORD * CSS_CreateSampleCacheEntry(int stream, int fileName, _DWORD *formatInfo)
{
  _BYTE *nameDest; // edi
  char ch; // al
  char ch2; // al
  _DWORD *fieldPtr; // edi
  _DWORD *entry; // [esp+4h] [ebp-14h] BYREF

  CSS_StreamService_NoOpHook();
  CSS_SampleCache_MakeRoom(formatInfo[1]);
  CSS_Mem_TryAlloc(24, &entry);
  CSS_Mem_TryAlloc(strlen((const char *)fileName) + 1, entry + 4);
  nameDest = (_BYTE *)entry[4];
  do
  {
    ch = *(_BYTE *)fileName;
    *nameDest = *(_BYTE *)fileName;
    if ( !ch )
      break;
    ch2 = *(_BYTE *)(fileName + 1);
    fileName += 2;
    nameDest[1] = ch2;
    nameDest += 2;
  }
  while ( ch2 );
  CSS_Mem_TryAlloc(formatInfo[1], entry);
  (*(void (**)(void))(*(_DWORD *)stream + 20))();
  (*(void (**)(void))(*(_DWORD *)g_MediaFileStreamProvider + 20))();
  entry[5] = 0;
  fieldPtr = entry + 1;
  entry[1] = *formatInfo;
  *++fieldPtr = formatInfo[1];
  fieldPtr[1] = formatInfo[2];
  if ( g_SampleCacheListHead )
    CSS_SampleCache_AppendEntry(g_SampleCacheListHead, (int)entry);
  else
    g_SampleCacheListHead = (int)entry;
  g_CSS_SampleCacheBytesUsed += formatInfo[1];
  return entry;
}
// 54D3B8: using guessed type int dword_54D3B8;
// 54D3BC: using guessed type int dword_54D3BC;
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046EB80) --------------------------------------------------------
int  CSS_StartSampleVoice(int stream, int *formatInfo, int panning, int volume, int fadeMs)
{
  unsigned int bestChannel; // edi
  int scanIndex; // eax
  int bestScore; // ebx
  int channelOffset; // ecx
  int channelState; // esi
  int channelByteOffset; // esi
  int bufferBytes; // ebx
  int sampleSize; // eax

  bestChannel = -1;
  scanIndex = 0;
  bestScore = g_CSS_SampleVoiceStealBias + g_CSS_VoiceSequenceCounter;
  if ( g_CssVoicePoolSize > 0 )
  {
    channelOffset = 0;
    do
    {
      channelState = *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 36);
      if ( g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40) < bestScore )
      {
        bestScore = g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40);
        bestChannel = scanIndex;
      }
      ++scanIndex;
      channelOffset += 52;
    }
    while ( scanIndex < g_CssVoicePoolSize );
  }
  if ( bestChannel != -1 )
    CSS_CloseChannel(bestChannel, 0);
  channelByteOffset = 52 * bestChannel;
  bufferBytes = g_CSS_StreamBufferMs * formatInfo[2] / 1000;
  sampleSize = CSS_GetFormatSampleSize(*formatInfo);
  *(_DWORD *)(g_SoundChannelArrayBase + channelByteOffset + 20) = CSS_FileStream_New(stream, sampleSize * bufferBytes);
  CSS_Channel_StartFileStream(bestChannel, formatInfo, panning, volume, fadeMs, 4);
  *(_DWORD *)(channelByteOffset + g_SoundChannelArrayBase + 44) = 1;
  CSS_ChannelMarkPlaying(bestChannel);
  return *(_DWORD *)(g_SoundChannelArrayBase + 52 * bestChannel + 40);
}
// 46EB80: could not find valid save-restore pair for ebx
// 519C8C: using guessed type int dword_519C8C[];
// 519C9C: using guessed type int dword_519C9C;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3CC: using guessed type int dword_54D3CC;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046ECB0) --------------------------------------------------------
int __stdcall CSS_ResumeStream(int soundHandle)
{
  int result; // eax
  unsigned int channelIndex; // edx

  result = soundHandle;
  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      result = 0;
      while ( soundHandle != *(_DWORD *)(result + g_SoundChannelArrayBase + 40) )
      {
        result += 52;
        ++channelIndex;
        if ( result >= 52 * g_CssVoicePoolSize )
          return result;
      }
      if ( channelIndex != -1 )
      {
        *(_DWORD *)(result + g_SoundChannelArrayBase + 44) = 1;
        return CSS_ChannelMarkPlaying(channelIndex);
      }
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046ED10) --------------------------------------------------------
int  CSS_StartStreamVoice(int aviPlayer, int volume, int a3, DWORD panning)
{
  int v7; // ecx
  char formatCode; // al
  unsigned int bestChannel; // edi
  int scanIndex; // eax
  int bestScore; // ebx
  int channelOffset; // ecx
  int channelState; // esi
  int formatInfo[3]; // [esp+14h] [ebp-24h] BYREF
  _DWORD *streamAdapter; // [esp+20h] [ebp-18h]
  int savedPanArg; // [esp+24h] [ebp-14h]
  int savedVolume; // [esp+28h] [ebp-10h]

  savedVolume = volume;
  savedPanArg = a3;
  if ( !g_CSS_ActiveSoundDriver || !g_SoundChannelArrayBase || CSS_IsNullSoundDevice() )
    return 0;
  if ( *(_WORD *)(*(_DWORD *)(aviPlayer + 363) + 2) == 1 )
    formatCode = 1;
  else
    formatCode = 3;
  formatInfo[0] = formatCode;
  if ( *(_WORD *)(*(_DWORD *)(aviPlayer + 363) + 14) == 16 )
    ++formatInfo[0];
  formatInfo[1] = *(_DWORD *)(aviPlayer + 251);
  formatInfo[2] = *(_DWORD *)(*(_DWORD *)(aviPlayer + 363) + 4);
  streamAdapter = IO_StreamAdapterAlloc(v7, 0, panning);
  if ( !streamAdapter )
    return 0;
  bestChannel = -1;
  scanIndex = 0;
  bestScore = g_CSS_StreamVoiceStealBias + g_CSS_VoiceSequenceCounter;
  if ( g_CssVoicePoolSize > 0 )
  {
    channelOffset = 0;
    do
    {
      channelState = *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 36);
      if ( g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40) < bestScore )
      {
        bestScore = g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40);
        bestChannel = scanIndex;
      }
      ++scanIndex;
      channelOffset += 52;
    }
    while ( scanIndex < g_CssVoicePoolSize );
  }
  if ( bestChannel != -1 )
    CSS_CloseChannel(bestChannel, 0);
  *(_DWORD *)(g_SoundChannelArrayBase + 52 * bestChannel + 20) = streamAdapter;
  CSS_Channel_StartFileStream(bestChannel, formatInfo, panning, savedVolume, savedPanArg, 8);
  return *(_DWORD *)(52 * bestChannel + g_SoundChannelArrayBase + 40);
}
// 46EDCD: variable 'v7' is possibly undefined
// 519C8C: using guessed type int dword_519C8C[];
// 519CAC: using guessed type int dword_519CAC;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046EE90) --------------------------------------------------------
void __stdcall CSS_LoadSample(int fileName)
{
  int v1; // ecx
  int v2; // ecx
  int stream; // esi
  _DWORD formatInfo[4]; // [esp+0h] [ebp-10h] BYREF

  if ( g_CSS_ActiveSoundDriver )
  {
    if ( g_SoundChannelArrayBase )
    {
      if ( !CSS_SampleCache_FindAndTouch(fileName) )
      {
        stream = Audio_ReadWavHeaderFromStream(v1, formatInfo);
        if ( stream )
        {
          if ( formatInfo[1] < g_CSS_SampleCacheByteBudget )
            CSS_CreateSampleCacheEntry(stream, v2, formatInfo);
        }
      }
    }
  }
}
// 46EEC0: variable 'v1' is possibly undefined
// 46EEE0: variable 'v2' is possibly undefined
// 54D3C0: using guessed type int dword_54D3C0;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046EEF0) --------------------------------------------------------
int __stdcall CSS_PlayMemSound(int sampleData, int formatCode, signed int dataBytes, int sampleRate, int volume, int panning, signed int fadeMs)
{
  unsigned int bestChannel; // edi
  int bestScore; // ebx
  int scanIndex; // eax
  int channelOffset; // ecx
  int channelState; // esi
  int voiceId; // ebx
  int channelBase; // eax
  int v16; // ecx

  if ( !g_CSS_ActiveSoundDriver || !g_SoundChannelArrayBase || CSS_IsNullSoundDevice() )
    return 0;
  bestChannel = -1;
  bestScore = g_CSS_MemSoundStealBias + g_CSS_VoiceSequenceCounter;
  scanIndex = 0;
  if ( g_CssVoicePoolSize > 0 )
  {
    channelOffset = 0;
    do
    {
      channelState = *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 36);
      if ( g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40) < bestScore )
      {
        bestScore = g_CSS_ChannelPriorityWeightTable[channelState] + *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40);
        bestChannel = scanIndex;
      }
      ++scanIndex;
      channelOffset += 52;
    }
    while ( scanIndex < g_CssVoicePoolSize );
  }
  if ( bestChannel == -1 )
    return 0;
  CSS_CloseChannel(bestChannel, 0);
  voiceId = g_CSS_VoiceSequenceCounter++;
  CSS_Channel_StoreFormatParams(52 * bestChannel + g_SoundChannelArrayBase, formatCode);
  channelBase = g_SoundChannelArrayBase;
  *(_DWORD *)(v16 + g_SoundChannelArrayBase + 36) = 1;
  *(_DWORD *)(v16 + channelBase + 48) = 0;
  *(_DWORD *)(v16 + channelBase + 40) = voiceId;
  *(_DWORD *)(v16 + channelBase) = sampleData;
  CSS_ChannelQueueSound(bestChannel, sampleData, dataBytes, sampleRate, formatCode);
  CSS_ChannelSetVolumeImmediate(bestChannel, 0);
  CSS_ChannelBeginVolumeFade(bestChannel, volume, fadeMs);
  CSS_ChannelSetPanning(bestChannel, panning);
  return voiceId;
}
// 46EFDA: variable 'v16' is possibly undefined
// 519C8C: using guessed type int dword_519C8C[];
// 519C90: using guessed type int dword_519C90;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046F040) --------------------------------------------------------
int __stdcall CSS_PlaySound(int fileName, int volume, int panning, signed int fadeMs)
{
  int *cachedEntry; // eax
  int stream; // esi
  int *newEntry; // esi
  int formatInfo[7]; // [esp+14h] [ebp-1Ch] BYREF

  if ( !g_CSS_ActiveSoundDriver || !g_SoundChannelArrayBase || CSS_IsNullSoundDevice() )
    return 0;
  cachedEntry = (int *)CSS_SampleCache_FindAndTouch(fileName);
  if ( cachedEntry )
    return CSS_Channel_SelectAndPlay(cachedEntry, volume, fadeMs, panning);
  stream = Audio_ReadWavHeaderFromStream(fileName, formatInfo);
  if ( !stream )
    return 0;
  if ( formatInfo[1] >= g_CSS_SampleCacheByteBudget )
    return CSS_StartSampleVoice(stream, formatInfo, panning, volume, fadeMs);
  CSS_PauseStreamReading();
  newEntry = CSS_CreateSampleCacheEntry(stream, fileName, formatInfo);
  CSS_ResumeStreamReading();
  return CSS_Channel_SelectAndPlay(newEntry, volume, fadeMs, panning);
}
// 54D3C0: using guessed type int dword_54D3C0;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046F140) --------------------------------------------------------
int __stdcall CSS_StopSound(int soundHandle, signed int fadeMs)
{
  int result; // eax
  unsigned int channelIndex; // ecx
  _DWORD ehFrame[8]; // [esp+0h] [ebp-20h] BYREF

  result = (int)ehFrame;
  ehFrame[0] = NtCurrentTeb()->NtTib.ExceptionList;
  ehFrame[1] = &j____wcpp_4_fs_handler_rtn_;
  ehFrame[2] = &g_CSSStopSound_EHScopeTable;
  ehFrame[3] = 0;
  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      result = 0;
      while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + result + 40) )
      {
        result += 52;
        ++channelIndex;
        if ( result >= 52 * g_CssVoicePoolSize )
          return result;
      }
      if ( channelIndex != -1 )
        return CSS_CloseChannel(channelIndex, fadeMs);
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F1E0) --------------------------------------------------------
int __stdcall CSS_GetSoundPos(int soundHandle)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax
  unsigned int foundChannel; // ebx
  int channelState; // ecx
  unsigned int playPosOut[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( soundHandle && (channelIndex = 0, g_CssVoicePoolSize > 0) )
  {
    channelOffset = 0;
    while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + channelOffset + 40) )
    {
      channelOffset += 52;
      ++channelIndex;
      if ( channelOffset >= 52 * g_CssVoicePoolSize )
        goto LABEL_10;
    }
  }
  else
  {
LABEL_10:
    channelIndex = -1;
  }
  foundChannel = channelIndex;
  if ( channelIndex == -1 )
    return 0;
  channelState = *(_DWORD *)(52 * channelIndex + g_SoundChannelArrayBase + 36);
  if ( channelState == 4 || channelState == 8 )
    playPosOut[0] = (*(int (**)(void))(**(_DWORD **)(g_SoundChannelArrayBase + 52 * channelIndex + 20) + 24))();
  else
    CSS_ChannelGetPlayPosition(channelIndex, playPosOut);
  return playPosOut[0] / *(_DWORD *)(g_SoundChannelArrayBase + 52 * foundChannel + 16);
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F280) --------------------------------------------------------
void __stdcall CSS_SetSoundPos(int soundHandle, int samplePos)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax
  unsigned int foundChannel; // ebx
  int channelBase; // esi
  int channelState; // ecx
  _DWORD *channel; // esi
  unsigned int savedPlayPos; // [esp-4h] [ebp-30h]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-2Ch]
  unsigned int playPosOut[6]; // [esp+14h] [ebp-18h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  if ( soundHandle && (channelIndex = 0, g_CssVoicePoolSize > 0) )
  {
    channelOffset = 0;
    while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + channelOffset + 40) )
    {
      channelOffset += 52;
      ++channelIndex;
      if ( channelOffset >= 52 * g_CssVoicePoolSize )
        goto LABEL_12;
    }
  }
  else
  {
LABEL_12:
    channelIndex = -1;
  }
  foundChannel = channelIndex;
  if ( channelIndex != -1 )
  {
    channelBase = g_SoundChannelArrayBase + 52 * channelIndex;
    channelState = *(_DWORD *)(channelBase + 36);
    if ( channelState == 4 || channelState == 8 )
    {
      ++g_StreamServiceLockEntryCount;
      EnterCriticalSection(&CriticalSection);
      ++g_CSS_MixerLockNestingCount;
      EnterCriticalSection(&stru_54D3FC);
      (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(**(_DWORD **)(channelBase + 20) + 28))(
        ExceptionList,
        &j____wcpp_4_fs_handler_rtn_,
        &g_CSSSetSoundPos_EHScopeTable,
        1);
      channel = (_DWORD *)(52 * foundChannel + g_SoundChannelArrayBase);
      if ( *channel )
      {
        CSS_ChannelGetPlayPosition(foundChannel, playPosOut);
        savedPlayPos = playPosOut[0];
        channel[3] = playPosOut[0];
        CSS_ChannelSetPositionOffset(foundChannel, savedPlayPos);
      }
      CSS_Channel_ServiceStream(foundChannel);
      LeaveCriticalSection(&CriticalSection);
      --g_StreamServiceLockEntryCount;
      LeaveCriticalSection(&stru_54D3FC);
      --g_CSS_MixerLockNestingCount;
    }
    else
    {
      CSS_ChannelSetPlayPosition(channelIndex, *(_DWORD *)(channelBase + 16) * samplePos);
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046F420) --------------------------------------------------------
int __stdcall CSS_PauseSound(int soundHandle, signed int fadeMs)
{
  int result; // eax
  unsigned int channelIndex; // ebx

  result = soundHandle;
  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      result = 0;
      while ( soundHandle != *(_DWORD *)(result + g_SoundChannelArrayBase + 40) )
      {
        result += 52;
        ++channelIndex;
        if ( result >= 52 * g_CssVoicePoolSize )
          return result;
      }
      if ( channelIndex != -1 )
      {
        CSS_ChannelGetVolume(channelIndex, (_DWORD *)(result + g_SoundChannelArrayBase + 32));
        return CSS_ChannelBeginVolumeFade(channelIndex, 0, fadeMs);
      }
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F490) --------------------------------------------------------
int __stdcall CSS_ResumeSound(int soundHandle, signed int fadeMs)
{
  int result; // eax
  unsigned int channelIndex; // edx

  result = soundHandle;
  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      result = 0;
      while ( soundHandle != *(_DWORD *)(result + g_SoundChannelArrayBase + 40) )
      {
        result += 52;
        ++channelIndex;
        if ( result >= 52 * g_CssVoicePoolSize )
          return result;
      }
      if ( channelIndex != -1 )
        return CSS_ChannelBeginVolumeFade(channelIndex, *(_DWORD *)(result + g_SoundChannelArrayBase + 32), fadeMs);
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F4F0) --------------------------------------------------------
void __stdcall CSS_SetSoundLoop(int soundHandle, int loopStart, int loopEnd)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax
  int channelBase; // ebx
  int channelState; // ebp

  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      channelOffset = 0;
      while ( 1 )
      {
        channelBase = channelOffset + g_SoundChannelArrayBase;
        if ( soundHandle == *(_DWORD *)(channelOffset + g_SoundChannelArrayBase + 40) )
          break;
        channelOffset += 52;
        ++channelIndex;
        if ( channelOffset >= 52 * g_CssVoicePoolSize )
          return;
      }
      if ( channelIndex != -1 )
      {
        channelState = *(_DWORD *)(channelBase + 36);
        if ( channelState == 4 || channelState == 8 )
        {
          (*(void (__fastcall **)(_DWORD, int))(**(_DWORD **)(channelBase + 20) + 12))(
            *(_DWORD *)(channelBase + 20),
            *(_DWORD *)(channelBase + 16) * loopStart);
        }
        else
        {
          CSS_SetMixChannelLoopPoints(channelIndex, loopStart, loopEnd);
          *(_DWORD *)(channelBase + 36) = 2;
        }
      }
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F580) --------------------------------------------------------
int __stdcall CSS_GetSoundLoop(int soundHandle, _DWORD *loopStartOut, _DWORD *loopEndOut)
{
  int result; // eax
  unsigned int channelIndex; // ecx
  int channelBase; // edx
  int channelState; // ebx
  int channelRec; // esi

  result = soundHandle;
  if ( !soundHandle )
    goto LABEL_10;
  channelIndex = 0;
  if ( g_CssVoicePoolSize <= 0 )
    goto LABEL_10;
  result = 0;
  while ( 1 )
  {
    channelBase = result + g_SoundChannelArrayBase;
    if ( soundHandle == *(_DWORD *)(result + g_SoundChannelArrayBase + 40) )
      break;
    result += 52;
    ++channelIndex;
    if ( result >= 52 * g_CssVoicePoolSize )
      goto LABEL_10;
  }
  if ( channelIndex == -1 )
  {
LABEL_10:
    *loopStartOut = 0;
    *loopEndOut = 0;
  }
  else
  {
    channelState = *(_DWORD *)(channelBase + 36);
    channelRec = result + g_SoundChannelArrayBase;
    if ( channelState == 4 || channelState == 8 )
    {
      (*(void (**)(void))(**(_DWORD **)(channelBase + 20) + 16))();
      *loopStartOut /= *(_DWORD *)(channelRec + 16);
      result = *loopEndOut / *(_DWORD *)(channelRec + 16);
      *loopEndOut = result;
    }
    else
    {
      return CSS_ChannelGetLoopRange(channelIndex, loopStartOut, loopEndOut);
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F620) --------------------------------------------------------
int __stdcall CSS_UnLoopSound(int soundHandle)
{
  int result; // eax
  unsigned int channelIndex; // edx
  int channelByteOffset; // ebx
  int channelState; // esi

  result = soundHandle;
  if ( soundHandle && (channelIndex = 0, g_CssVoicePoolSize > 0) )
  {
    result = 0;
    while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + result + 40) )
    {
      result += 52;
      ++channelIndex;
      if ( result >= 52 * g_CssVoicePoolSize )
        goto LABEL_11;
    }
  }
  else
  {
LABEL_11:
    channelIndex = -1;
  }
  if ( channelIndex != -1 )
  {
    channelByteOffset = 52 * channelIndex;
    channelState = *(_DWORD *)(52 * channelIndex + g_SoundChannelArrayBase + 36);
    if ( channelState == 4 || channelState == 8 )
    {
      return (*(int (**)(void))(**(_DWORD **)(g_SoundChannelArrayBase + 52 * channelIndex + 20) + 20))();
    }
    else
    {
      CSS_ClearMixChannelLoopPoints(channelIndex);
      result = g_SoundChannelArrayBase;
      *(_DWORD *)(channelByteOffset + g_SoundChannelArrayBase + 36) = 1;
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F6B0) --------------------------------------------------------
void __stdcall CSS_SetSoundRate(int soundHandle, unsigned __int32 sampleRate)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax

  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      channelOffset = 0;
      while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + channelOffset + 40) )
      {
        channelOffset += 52;
        ++channelIndex;
        if ( channelOffset >= 52 * g_CssVoicePoolSize )
          return;
      }
      if ( channelIndex != -1 )
        CSS_ChannelSetRate(channelIndex, sampleRate);
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F710) --------------------------------------------------------
int __stdcall CSS_GetSoundRate(int soundHandle)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax
  _DWORD rateOut[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !soundHandle )
    return 0;
  channelIndex = 0;
  if ( g_CssVoicePoolSize <= 0 )
    return 0;
  channelOffset = 0;
  while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + channelOffset + 40) )
  {
    channelOffset += 52;
    ++channelIndex;
    if ( channelOffset >= 52 * g_CssVoicePoolSize )
      return 0;
  }
  if ( channelIndex == -1 )
    return 0;
  CSS_ChannelGetRate(channelIndex, rateOut);
  return rateOut[0];
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F770) --------------------------------------------------------
int __stdcall CSS_SetSoundVolume(int soundHandle, int volume, signed int fadeMs)
{
  int result; // eax
  unsigned int channelIndex; // edx

  result = soundHandle;
  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      result = 0;
      while ( soundHandle != *(_DWORD *)(result + g_SoundChannelArrayBase + 40) )
      {
        result += 52;
        ++channelIndex;
        if ( result >= 52 * g_CssVoicePoolSize )
          return result;
      }
      if ( channelIndex != -1 )
      {
        *(_DWORD *)(result + g_SoundChannelArrayBase + 32) = volume;
        return CSS_ChannelBeginVolumeFade(channelIndex, volume, fadeMs);
      }
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F7D0) --------------------------------------------------------
int __stdcall CSS_GetSoundVolume(int soundHandle)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax
  _DWORD volumeOut[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !soundHandle )
    return 0;
  channelIndex = 0;
  if ( g_CssVoicePoolSize <= 0 )
    return 0;
  channelOffset = 0;
  while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + channelOffset + 40) )
  {
    channelOffset += 52;
    ++channelIndex;
    if ( channelOffset >= 52 * g_CssVoicePoolSize )
      return 0;
  }
  if ( channelIndex == -1 )
    return 0;
  CSS_ChannelGetVolume(channelIndex, volumeOut);
  return volumeOut[0];
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F830) --------------------------------------------------------
void __stdcall CSS_SetSoundPanning(int soundHandle, int panning)
{
  unsigned int channelIndex; // edx
  int channelOffset; // eax

  if ( soundHandle )
  {
    channelIndex = 0;
    if ( g_CssVoicePoolSize > 0 )
    {
      channelOffset = 0;
      while ( soundHandle != *(_DWORD *)(g_SoundChannelArrayBase + channelOffset + 40) )
      {
        channelOffset += 52;
        ++channelIndex;
        if ( channelOffset >= 52 * g_CssVoicePoolSize )
          return;
      }
      if ( channelIndex != -1 )
        CSS_ChannelSetPanning(channelIndex, panning);
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F890) --------------------------------------------------------
int __stdcall CSS_GetSoundPanning(int sound_handle)
{
  unsigned int channel_index; // edx
  int channel_offset; // eax
  _DWORD panning_out[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !sound_handle )
    return 0;
  channel_index = 0;
  if ( g_CssVoicePoolSize <= 0 )
    return 0;
  channel_offset = 0;
  while ( sound_handle != *(_DWORD *)(g_SoundChannelArrayBase + channel_offset + 40) )
  {
    channel_offset += 52;
    ++channel_index;
    if ( channel_offset >= 52 * g_CssVoicePoolSize )
      return 0;
  }
  if ( channel_index == -1 )
    return 0;
  CSS_ChannelGetPanning(channel_index, panning_out);
  return panning_out[0];
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F8F0) --------------------------------------------------------
BOOL __stdcall CSS_IsPlaying(int sound_handle)
{
  unsigned int channel_index; // edx
  int channel_offset; // eax

  if ( !sound_handle )
    return 0;
  channel_index = 0;
  if ( g_CssVoicePoolSize <= 0 )
    return 0;
  channel_offset = 0;
  while ( sound_handle != *(_DWORD *)(g_SoundChannelArrayBase + channel_offset + 40) )
  {
    channel_offset += 52;
    ++channel_index;
    if ( channel_offset >= 52 * g_CssVoicePoolSize )
      return 0;
  }
  return channel_index != -1 && CSS_ChannelIsPlaying(channel_index);
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F950) --------------------------------------------------------
signed int  CSS_InitVoicePool(int voice_count, int stream_buffer_ms, int sample_cache_kb)
{
  int pool_bytes; // ebx
  int channel_offset; // eax
  int array_base; // edx
  _BYTE thread_args[20]; // [esp+14h] [ebp-14h] BYREF

  g_CssVoicePoolSize = voice_count;
  pool_bytes = 52 * voice_count;
  CSS_Mem_TryAlloc(52 * voice_count, &g_SoundChannelArrayBase);
  if ( voice_count > 0 )
  {
    channel_offset = 0;
    do
    {
      array_base = g_SoundChannelArrayBase;
      *(_DWORD *)(g_SoundChannelArrayBase + channel_offset) = 0;
      channel_offset += 52;
      *(_DWORD *)(array_base + channel_offset - 12) = 0;
      *(_DWORD *)(array_base + channel_offset - 16) = 0;
      *(_DWORD *)(array_base + channel_offset - 4) = 0;
    }
    while ( channel_offset < pool_bytes );
  }
  g_CSS_StreamBufferMs = stream_buffer_ms;
  g_CSS_SampleCacheByteBudget = sample_cache_kb << 10;
  g_CSS_StreamReadingActive = 1;
  g_CSS_StreamThreadRunning = 1;
  hThread = (HANDLE)beginthreadex_(0, thread_args);
  g_CSS_StreamThreadHandle = beginthreadex_(0, thread_args);
  SetThreadPriority((HANDLE)g_CSS_StreamThreadHandle, 2);
  return 1;
}
// 484E65: using guessed type _DWORD __stdcall beginthreadex_(_DWORD, _DWORD);
// 54D3C0: using guessed type int dword_54D3C0;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3CC: using guessed type int dword_54D3CC;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D414: using guessed type int dword_54D414;
// 54D41C: using guessed type int dword_54D41C;
// 54D45C: using guessed type int dword_54D45C;

//----- (0046FA60) --------------------------------------------------------
_DWORD *CSS_ShutdownVoicePool()
{
  _DWORD *result; // eax
  int v1; // edx
  int v2; // ecx
  signed int i; // ecx
  int v4; // ecx
  _DWORD eh_frame[3]; // [esp+0h] [ebp-30h] BYREF
  int try_level; // [esp+Ch] [ebp-24h]
  int *read_lock_refcount; // [esp+14h] [ebp-1Ch]
  int *service_lock_refcount; // [esp+18h] [ebp-18h]

  result = eh_frame;
  eh_frame[0] = NtCurrentTeb()->NtTib.ExceptionList;
  eh_frame[1] = &j____wcpp_4_fs_handler_rtn_;
  eh_frame[2] = &g_CSSShutdownVoicePool_EHScopeTable;
  try_level = 0;
  if ( g_SoundChannelArrayBase )
  {
    g_CSS_StreamReadingActive = 0;
    g_CSS_StreamThreadRunning = 0;
    read_lock_refcount = &g_CSS_StreamReadThreadLockRefCount;
    ++g_CSS_StreamReadThreadLockRefCount;
    EnterCriticalSection(&stru_54D424);
    try_level = 1;
    service_lock_refcount = &g_CSS_StreamServiceThreadLockRefCount;
    ++g_CSS_StreamServiceThreadLockRefCount;
    EnterCriticalSection(&stru_54D444);
    try_level = 2;
    CRT_WatcomEHUnwindToExceptionList(v2, v1);
    for ( i = 0; i < g_CssVoicePoolSize; i = v4 + 1 )
      CSS_CloseChannel(i, 0);
    CSS_EmptySampleCache();
    result = (_DWORD *)CSS_Mem_FreeIfSet(g_SoundChannelArrayBase);
    g_SoundChannelArrayBase = 0;
  }
  return result;
}
// 46FB1A: variable 'v2' is possibly undefined
// 46FB1A: variable 'v1' is possibly undefined
// 46FB39: variable 'v4' is possibly undefined
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D414: using guessed type int dword_54D414;
// 54D420: using guessed type int dword_54D420;
// 54D440: using guessed type int dword_54D440;
// 54D45C: using guessed type int dword_54D45C;

//----- (0046FB70) --------------------------------------------------------
int  CSS_LockAudioThreads(int a1)
{
  ++g_StreamServiceLockEntryCount;
  EnterCriticalSection(&CriticalSection);
  ++g_CSS_MixerLockNestingCount;
  EnterCriticalSection(&stru_54D3FC);
  return a1;
}
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046FBC0) --------------------------------------------------------
int  CSS_UnlockAudioThreads(int a1)
{
  LeaveCriticalSection(&CriticalSection);
  --g_StreamServiceLockEntryCount;
  LeaveCriticalSection(&stru_54D3FC);
  --g_CSS_MixerLockNestingCount;
  return a1;
}
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046FC00) --------------------------------------------------------
int CSS_InitDeviceSearchState()
{
  int v0; // edx
  int v1; // ecx

  g_CSS_DeviceSearchThreadRefCount = 0;
  InitializeCriticalSection(&stru_54D49C);
  return CRT_RegisterFinalizableObject(v1, v0);
}
// 46FC1B: variable 'v1' is possibly undefined
// 46FC1B: variable 'v0' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 54D498: using guessed type int dword_54D498;

//----- (0046FC30) --------------------------------------------------------
BOOL CSS_IsNullSoundDevice()
{
  return g_CSS_ActiveSoundDriver == (_DWORD)&g_CSS_NullDriverSentinel;
}
// 54D468: using guessed type int dword_54D468;

//----- (0046FC50) --------------------------------------------------------
int CSS_PollAudioDeviceChange()
{
  _DWORD *v0; // eax
  int result; // eax

  v0 = (_DWORD *)(*(int (**)(void))(g_CSS_ActiveSoundDriver + 88))();
  CSS_AdvanceVolumeFades(v0);
  do
    result = (*(int (__cdecl **)(int *))(g_CSS_ActiveSoundDriver + 92))(&g_CSS_DevicePollPending);
  while ( !result && g_CSS_DevicePollPending );
  return result;
}
// 54D460: using guessed type int dword_54D460;
// 54D468: using guessed type int dword_54D468;

//----- (0046FC80) --------------------------------------------------------
int __stdcall CSS_DeviceSearchThreadProc(int thread_param)
{
  ++g_CSS_DeviceSearchThreadRefCount;
  EnterCriticalSection(&stru_54D49C);
  while ( g_CSS_DevicePollThreadRunning )
  {
    CSS_PollAudioDeviceChange();
    Sleep(1000 / g_CSS_MixUpdateRateHz);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(&g_CSS_DeviceSearchThreadRefCount + 1));
  --g_CSS_DeviceSearchThreadRefCount;
  return 0;
}
// 519CF4: using guessed type int dword_519CF4;
// 54D498: using guessed type int dword_54D498;
// 54D4B4: using guessed type int dword_54D4B4;

//----- (0046FE10) --------------------------------------------------------
int __stdcall CSS_SetDirectSoundHWnd(int hwnd)
{
  int result; // eax

  result = hwnd;
  g_AudioWindowHandle = hwnd;
  return result;
}
// 54D470: using guessed type int dword_54D470;

//----- (0046FE20) --------------------------------------------------------
int __stdcall CSS_SetDeviceSearch(int search_index)
{
  int result; // eax

  result = search_index;
  g_CSS_DeviceSearchIndex = search_index;
  return result;
}
// 54D48C: using guessed type int dword_54D48C;

//----- (0046FE30) --------------------------------------------------------
signed int CSS_ResetDeviceConfigDefaults()
{
  signed int result; // eax

  result = 10;
  g_CSS_AudioDeviceActive = 0;
  g_CSS_VoiceCount = 0;
  g_CSS_DeviceOpenParam2 = 0;
  g_CSS_DeviceSampleRateHz = 44100;
  g_CSS_DeviceConfigDefaultNegOne = -1;
  g_CSS_DeviceConfigDefaultZero = 0;
  g_CSS_MixUpdateRateHz = 10;
  g_CSS_ActiveSoundDriver = 0;
  g_CSS_DSoundAccelDetectEnabled = 1;
  g_CSS_FatalErrorHandler = (int)CSS_FatalErrorExit;
  return result;
}
// 519CF4: using guessed type int dword_519CF4;
// 519CF8: using guessed type int dword_519CF8;
// 54D468: using guessed type int dword_54D468;
// 54D46C: using guessed type int dword_54D46C;
// 54D474: using guessed type int dword_54D474;
// 54D478: using guessed type int dword_54D478;
// 54D47C: using guessed type int dword_54D47C;
// 54D480: using guessed type int dword_54D480;
// 54D488: using guessed type int dword_54D488;
// 54D490: using guessed type int dword_54D490;

//----- (0046FEA0) --------------------------------------------------------
int __stdcall CSS_SetMasterVolume(int volume)
{
  return CSS_SetMixMasterVolume(volume);
}

//----- (0046FEB0) --------------------------------------------------------
void __stdcall CSS_SetDefaults()
{
  CSS_ResetDeviceConfigDefaults();
  CSS_ResetDeviceHandleCache();
}

//----- (0046FEC0) --------------------------------------------------------
void CSS_ResetDeviceHandleCache()
{
  g_CSS_DeviceHandleCache_DriverIndex = -1;
  g_CSS_DeviceHandleCache_Param1 = -1;
  g_CSS_DeviceHandleCache_Param2 = -1;
  g_CSS_DeviceHandleCacheParam3 = -1;
  g_CSS_DeviceHandleCacheParam4 = -1;
}
// 519D08: using guessed type int dword_519D08;
// 519D0C: using guessed type int dword_519D0C;
// 519D10: using guessed type int dword_519D10;
// 519D14: using guessed type int dword_519D14;
// 519D18: using guessed type int dword_519D18;

//----- (0046FEF0) --------------------------------------------------------
void __stdcall CSS_Close()
{
  g_CSS_DevicePollThreadRunning = 0;
  ++g_CSS_DeviceSearchThreadRefCount;
  EnterCriticalSection(&stru_54D49C);
  LeaveCriticalSection((LPCRITICAL_SECTION)(&g_CSS_DeviceSearchThreadRefCount + 1));
  --g_CSS_DeviceSearchThreadRefCount;
  CSS_ResetDeviceHandleCache();
  if ( g_CSS_AudioDeviceActive )
  {
    CSS_ShutdownVoicePool();
    CSS_FreeMixChannels();
    g_CSS_VoiceCount = 0;
    (*(void (**)(void))(g_CSS_ActiveSoundDriver + 56))();
    g_CSS_AudioDeviceActive = 0;
    g_CSS_ActiveSoundDriver = 0;
  }
}
// 54D468: using guessed type int dword_54D468;
// 54D480: using guessed type int dword_54D480;
// 54D488: using guessed type int dword_54D488;
// 54D498: using guessed type int dword_54D498;
// 54D4B4: using guessed type int dword_54D4B4;

//----- (0046FF80) --------------------------------------------------------
int __stdcall CSS_SetFileSystem(int file_stream_provider)
{
  int result; // eax

  result = file_stream_provider;
  g_MediaFileStreamProvider = file_stream_provider;
  return result;
}
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046FF90) --------------------------------------------------------
signed int __stdcall CSS_Init(int voice_count, int volume_scale, int stream_buffer_ms, int sample_cache_kb)
{
  int driver_index; // ebx
  int driver_table_offset; // esi
  int driver_ptr; // eax
  void *thread_handle; // eax
  int device_available; // [esp+14h] [ebp-18h] BYREF
  _BYTE thread_args[20]; // [esp+18h] [ebp-14h] BYREF

  CSS_ResetDeviceConfigDefaults();
  if ( g_CSS_DeviceHandleCache_DriverIndex == -1 )
  {
    driver_index = g_CSS_DeviceSearchIndex;
    if ( g_CSS_DeviceSearchIndex < 3 )
    {
      driver_table_offset = 4 * g_CSS_DeviceSearchIndex;
      do
      {
        if ( g_CSS_DeviceHandleCache_DriverIndex != -1 )
          break;
        if ( !(*(int (__cdecl ***)(int *))((char *)&g_CSS_DriverDescriptorTable + driver_table_offset))[12](&device_available) && device_available == 1 )
          g_CSS_DeviceHandleCache_DriverIndex = driver_index;
        ++driver_index;
        driver_table_offset += 4;
      }
      while ( driver_index < 3 );
    }
  }
  else
  {
    (*((void (__cdecl **)(int *))*(&g_CSS_DriverDescriptorTable + g_CSS_DeviceHandleCache_DriverIndex) + 12))(&device_available);
  }
  driver_ptr = (int)*(&g_CSS_DriverDescriptorTable + g_CSS_DeviceHandleCache_DriverIndex);
  g_CSS_ActiveSoundDriver = driver_ptr;
  if ( g_CSS_DeviceHandleCache_Param1 != -1 )
    *(_DWORD *)(driver_ptr + 8) = g_CSS_DeviceHandleCache_Param1;
  if ( g_CSS_DeviceHandleCache_Param2 != -1 )
    *(_DWORD *)(g_CSS_ActiveSoundDriver + 12) = g_CSS_DeviceHandleCache_Param2;
  if ( g_CSS_DeviceHandleCacheParam3 != -1 )
    *(_DWORD *)(g_CSS_ActiveSoundDriver + 16) = g_CSS_DeviceHandleCacheParam3;
  if ( g_CSS_DeviceHandleCacheParam4 != -1 )
    *(_DWORD *)(g_CSS_ActiveSoundDriver + 20) = g_CSS_DeviceHandleCacheParam4;
  if ( (*(int (__cdecl **)(int, int))(g_CSS_ActiveSoundDriver + 52))(g_CSS_DeviceSampleRateHz, g_CSS_DeviceOpenParam2) )
  {
    g_CSS_ActiveSoundDriver = 0;
    g_CSS_DeviceHandleCache_DriverIndex = -1;
    return 0;
  }
  else
  {
    g_CSS_VoiceCount = voice_count;
    g_CSS_AudioDeviceActive = 1;
    CSS_InitMixChannels(voice_count);
    CSS_BuildVolumeScaleTable(volume_scale);
    g_CSS_DevicePollThreadRunning = 1;
    thread_handle = (void *)beginthreadex_(0, thread_args);
    SetThreadPriority(thread_handle, 2);
    CSS_InitVoicePool(voice_count, stream_buffer_ms, sample_cache_kb);
    return 1;
  }
}
// 484E65: using guessed type _DWORD __stdcall beginthreadex_(_DWORD, _DWORD);
// 519CFC: using guessed type void *off_519CFC;
// 519D08: using guessed type int dword_519D08;
// 519D0C: using guessed type int dword_519D0C;
// 519D10: using guessed type int dword_519D10;
// 519D14: using guessed type int dword_519D14;
// 519D18: using guessed type int dword_519D18;
// 54D468: using guessed type int dword_54D468;
// 54D474: using guessed type int dword_54D474;
// 54D478: using guessed type int dword_54D478;
// 54D480: using guessed type int dword_54D480;
// 54D488: using guessed type int dword_54D488;
// 54D48C: using guessed type int dword_54D48C;
// 54D4B4: using guessed type int dword_54D4B4;

//----- (00470150) --------------------------------------------------------
unsigned int  CSS_TranslateWaveOutError(unsigned int result)
{
  if ( result >= 7 )
  {
    if ( result <= 7 )
      return 2;
    if ( result >= 0xC )
    {
      if ( result <= 0xC )
        return 41;
      if ( result < 0x21 )
      {
        if ( result == 32 )
          return 42;
        return 1;
      }
      if ( result <= 0x21 )
        return 41;
      if ( result > 0x22 )
      {
        if ( result == 35 )
          return 38;
        return 1;
      }
    }
    else if ( result < 0xA )
    {
      if ( result == 8 )
        return 39;
      return 1;
    }
    return 22;
  }
  if ( result >= 3 )
  {
    if ( result <= 3 )
      return 38;
    if ( result >= 5 )
    {
      if ( result > 5 )
        return 40;
      return 38;
    }
    return 41;
  }
  if ( result )
  {
    if ( result <= 1 )
      return 1;
    return 38;
  }
  return result;
}

//----- (004701E0) --------------------------------------------------------
int __cdecl CSS_QueryWaveOutDevicePresent(_DWORD *device_present_out)
{
  *device_present_out = waveOutGetNumDevs() != 0;
  return 0;
}

//----- (00470220) --------------------------------------------------------
unsigned int __cdecl CSS_OpenWaveOutDevice(int driver, char format_flags)
{
  bool format_unsupported; // zf
  unsigned int buffer_bytes; // eax
  MMRESULT mm_result; // eax
  unsigned int buffer_count; // esi
  int buffer_index; // ebx
  HGLOBAL buffer_mem_handle; // eax
  unsigned int result; // eax
  LPVOID buffer_ptr; // eax
  unsigned int header_count; // esi
  int header_index; // ebx
  HGLOBAL header_mem_handle; // eax
  struct wavehdr_tag *wave_header; // eax
  SIZE_T buffer_length; // edx
  unsigned int mix_channel_count; // edi
  struct tagWAVEOUTCAPSA pwoc; // [esp+0h] [ebp-58h] BYREF
  WAVEFORMATEX pwfx; // [esp+34h] [ebp-24h] BYREF

  g_CSS_SampleRateHz = 44100;
  g_WaveOutFormatFlags = ((format_flags & 1) == 0) + 1;
  if ( (format_flags & 4) != 0 )
    LOBYTE(g_WaveOutFormatFlags) = g_WaveOutFormatFlags | 4;
  else
    LOBYTE(g_WaveOutFormatFlags) = g_WaveOutFormatFlags | 8;
  waveOutGetDevCapsA(0xFFFFFFFF, &pwoc, 0x34u);
  if ( (g_WaveOutFormatFlags & 8) != 0 && (pwoc.dwFormats & 0x40) == 0 )
    LOBYTE(g_WaveOutFormatFlags) = g_WaveOutFormatFlags & 0xF7;
  if ( (g_WaveOutFormatFlags & 2) != 0 && SLOBYTE(pwoc.dwFormats) >= 0 && (pwoc.dwFormats & 2) == 0 )
    LOBYTE(g_WaveOutFormatFlags) = g_WaveOutFormatFlags & 0xFD;
  if ( (g_WaveOutFormatFlags & 2) != 0 )
  {
    if ( (g_WaveOutFormatFlags & 8) != 0 )
    {
      if ( (pwoc.dwFormats & 0x800) == 0 )
        g_CSS_SampleRateHz = 22050;
      if ( SLOBYTE(pwoc.dwFormats) >= 0 )
        g_CSS_SampleRateHz = 11025;
      format_unsupported = (pwoc.dwFormats & 8) == 0;
LABEL_17:
      if ( format_unsupported )
        LOBYTE(g_WaveOutFormatFlags) = g_WaveOutFormatFlags & 0xF7;
      goto LABEL_19;
    }
    if ( (pwoc.dwFormats & 0x200) == 0 )
      g_CSS_SampleRateHz = 22050;
    if ( (pwoc.dwFormats & 0x20) == 0 )
      g_CSS_SampleRateHz = 11025;
    if ( (pwoc.dwFormats & 2) == 0 )
      LOBYTE(g_WaveOutFormatFlags) = g_WaveOutFormatFlags & 0xFD;
  }
  else
  {
    if ( (g_WaveOutFormatFlags & 8) != 0 )
    {
      if ( (pwoc.dwFormats & 0x400) == 0 )
        g_CSS_SampleRateHz = 22050;
      if ( (pwoc.dwFormats & 0x40) == 0 )
        g_CSS_SampleRateHz = 11025;
      format_unsupported = (pwoc.dwFormats & 4) == 0;
      goto LABEL_17;
    }
    if ( (pwoc.dwFormats & 0x100) == 0 )
      g_CSS_SampleRateHz = 22050;
    if ( (pwoc.dwFormats & 0x10) == 0 )
      g_CSS_SampleRateHz = 11025;
  }
LABEL_19:
  g_CSS_WaveBlockAlign = ((g_WaveOutFormatFlags & 8) != 0) + 1;
  if ( (g_WaveOutFormatFlags & 2) != 0 )
    g_CSS_WaveBlockAlign = 2 * (((g_WaveOutFormatFlags & 8) != 0) + 1);
  g_CSS_MixChannelCount = 8;
  g_CSS_WaveOutFillByteOffset = 0;
  g_WaveOutBufferRingIndex = 0;
  buffer_bytes = g_CSS_WaveBlockAlign * (3 * g_CSS_SampleRateHz / (unsigned int)g_CSS_MixUpdateRateHz) / 8 + 15;
  LOBYTE(buffer_bytes) = buffer_bytes & 0xF0;
  pwfx.wFormatTag = 1;
  dwBytes = buffer_bytes;
  pwfx.nChannels = ((g_WaveOutFormatFlags & 2) != 0) + 1;
  pwfx.nSamplesPerSec = g_CSS_SampleRateHz;
  pwfx.nAvgBytesPerSec = g_CSS_SampleRateHz * g_CSS_WaveBlockAlign;
  pwfx.nBlockAlign = g_CSS_WaveBlockAlign;
  if ( (g_WaveOutFormatFlags & 8) != 0 )
    pwfx.wBitsPerSample = 16;
  else
    pwfx.wBitsPerSample = 8;
  pwfx.cbSize = 0;
  mm_result = waveOutOpen(&hwo, 0xFFFFFFFF, &pwfx, 0, 0, 0);
  if ( mm_result )
    return CSS_TranslateWaveOutError(mm_result);
  buffer_count = 0;
  if ( g_CSS_MixChannelCount )
  {
    buffer_index = 0;
    while ( 1 )
    {
      buffer_mem_handle = GlobalAlloc(0x2002u, dwBytes);
      g_CSS_WaveBufferMemHandles[buffer_index] = (int)buffer_mem_handle;
      if ( !buffer_mem_handle )
        return 2;
      buffer_ptr = GlobalLock(buffer_mem_handle);
      g_CSS_WaveBufferDataPtrs[buffer_index] = (int)buffer_ptr;
      if ( !buffer_ptr )
        return 43;
      ++buffer_count;
      ++buffer_index;
      if ( buffer_count >= g_CSS_MixChannelCount )
        goto LABEL_50;
    }
  }
  else
  {
LABEL_50:
    header_count = 0;
    if ( g_CSS_MixChannelCount )
    {
      header_index = 0;
      while ( 1 )
      {
        header_mem_handle = GlobalAlloc(0x2002u, 0x20u);
        g_CSS_WaveHeaderMemHandles[header_index] = (int)header_mem_handle;
        if ( !header_mem_handle )
          return 2;
        wave_header = (struct wavehdr_tag *)GlobalLock(header_mem_handle);
        *(LPWAVEHDR *)((char *)&pwh + header_index * 4) = wave_header;
        if ( !wave_header )
          return 43;
        wave_header->lpData = (LPSTR)g_CSS_WaveBufferDataPtrs[header_index];
        buffer_length = dwBytes;
        wave_header->dwFlags = 1;
        ++header_index;
        wave_header->dwLoops = 0;
        ++header_count;
        wave_header->dwBufferLength = buffer_length;
        mix_channel_count = g_CSS_MixChannelCount;
        g_CSS_WaveBufferStateArray[header_index] = 0;
        if ( header_count >= mix_channel_count )
          goto LABEL_57;
      }
    }
    else
    {
LABEL_57:
      CSS_InitMixBuffers(g_CSS_SampleRateHz, ((g_WaveOutFormatFlags & 2) != 0) + 1);
      result = CSS_SetWaveOutRefillThreshold(100 * g_CSS_MixUpdateRateHz);
      if ( !result )
      {
        switch ( g_WaveOutFormatFlags )
        {
          case 5:
            g_AudioMixToOutputFunc = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8;
            goto LABEL_60;
          case 6:
            g_AudioMixToOutputFunc = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8Stereo;
            goto LABEL_60;
          case 9:
            g_AudioMixToOutputFunc = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_MixInterleaved16;
            goto LABEL_60;
          case 10:
            g_AudioMixToOutputFunc = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM16Stereo;
LABEL_60:
            result = 0;
            break;
          default:
            result = 22;
            break;
        }
      }
    }
  }
  return result;
}
// 519CF4: using guessed type int dword_519CF4;
// 54D4C0: using guessed type int dword_54D4C0[];
// 54D540: using guessed type int dword_54D540[];
// 54D5BC: using guessed type int dword_54D5BC[];
// 54D640: using guessed type int dword_54D640[];
// 54D740: using guessed type int dword_54D740;
// 54D744: using guessed type int dword_54D744;
// 54D750: using guessed type int (__cdecl *dword_54D750)(_DWORD, _DWORD, _DWORD, _DWORD);
// 54D75C: using guessed type int dword_54D75C;
// 54D760: using guessed type int dword_54D760;
// 54D768: using guessed type int dword_54D768;

//----- (00470620) --------------------------------------------------------
signed int CSS_CloseWaveOutDevice()
{
  MMRESULT mm_result; // eax
  int all_buffers_done; // ebx
  unsigned int check_count; // eax
  int header_offset; // edx
  unsigned int unprepare_count; // esi
  int unprepare_index; // ebx
  unsigned int free_count; // esi
  int buffer_index; // ebx
  int header_free_count; // esi
  int i; // ebx

  CSS_FreeMixBuffers();
  mm_result = waveOutReset(hwo);
  if ( mm_result )
    return CSS_TranslateWaveOutError(mm_result);
  while ( 1 )
  {
    all_buffers_done = 1;
    check_count = 0;
    if ( g_CSS_MixChannelCount )
    {
      header_offset = 0;
      do
      {
        if ( ((*(LPWAVEHDR *)((char *)&pwh + header_offset))->dwFlags & 1) == 0 )
          all_buffers_done = 0;
        ++check_count;
        header_offset += 4;
      }
      while ( check_count < g_CSS_MixChannelCount );
    }
    if ( all_buffers_done )
      break;
    Sleep(0x14u);
  }
  unprepare_count = 0;
  if ( g_CSS_MixChannelCount )
  {
    unprepare_index = 0;
    do
    {
      if ( g_CSS_WaveHeaderPreparedFlags[unprepare_index] )
      {
        mm_result = waveOutUnprepareHeader(hwo, *(LPWAVEHDR *)((char *)&pwh + unprepare_index * 4), 0x20u);
        if ( mm_result )
          return CSS_TranslateWaveOutError(mm_result);
      }
      ++unprepare_count;
      ++unprepare_index;
    }
    while ( unprepare_count < g_CSS_MixChannelCount );
  }
  mm_result = waveOutClose(hwo);
  if ( mm_result )
    return CSS_TranslateWaveOutError(mm_result);
  free_count = 0;
  if ( g_CSS_MixChannelCount )
  {
    buffer_index = 0;
    while ( (GlobalUnlock((HGLOBAL)g_CSS_WaveBufferMemHandles[buffer_index]) || !GetLastError()) && !GlobalFree((HGLOBAL)g_CSS_WaveBufferMemHandles[buffer_index]) )
    {
      ++free_count;
      ++buffer_index;
      if ( free_count >= g_CSS_MixChannelCount )
        goto LABEL_20;
    }
    return 3;
  }
  else
  {
LABEL_20:
    header_free_count = 0;
    if ( g_CSS_MixChannelCount )
    {
      for ( i = 0; (GlobalUnlock((HGLOBAL)g_CSS_WaveHeaderMemHandles[i]) || !GetLastError()) && !GlobalFree((HGLOBAL)g_CSS_WaveHeaderMemHandles[i]); ++i )
      {
        if ( ++header_free_count >= (unsigned int)g_CSS_MixChannelCount )
          return 0;
      }
      return 3;
    }
    else
    {
      return 0;
    }
  }
}
// 54D540: using guessed type int dword_54D540[];
// 54D5C0: using guessed type int dword_54D5C0[];
// 54D640: using guessed type int dword_54D640[];
// 54D760: using guessed type int dword_54D760;

//----- (004707B0) --------------------------------------------------------
int __cdecl CSS_GetWaveOutFormatFlags(_DWORD *format_flags_out)
{
  *format_flags_out = g_WaveOutFormatFlags;
  return 0;
}
// 54D75C: using guessed type int dword_54D75C;

//----- (004707C0) --------------------------------------------------------
int __cdecl CSS_SetWaveOutRefillThreshold(unsigned int refill_rate)
{
  unsigned int chunk_samples; // eax

  chunk_samples = 100 * g_CSS_SampleRateHz / refill_rate + 1;
  LOBYTE(chunk_samples) = chunk_samples & 0xFE;
  g_CSS_WaveOutChunkSampleCount = chunk_samples;
  g_CSS_WaveOutRefillRemaining = chunk_samples;
  return 0;
}
// 54D748: using guessed type int dword_54D748;
// 54D74C: using guessed type int dword_54D74C;
// 54D768: using guessed type int dword_54D768;

//----- (004707F0) --------------------------------------------------------
unsigned int __cdecl CSS_PumpWaveOutBuffer(_DWORD *chunk_completed_out)
{
  unsigned int samples_per_buffer; // esi
  LPWAVEHDR wave_header; // eax
  SIZE_T samples_to_mix; // ebx
  MMRESULT mm_result; // eax
  HWAVEOUT wave_out_handle; // [esp-Ch] [ebp-1Ch]
  struct wavehdr_tag *header_to_write; // [esp-8h] [ebp-18h]

  samples_per_buffer = (unsigned int)g_CssMixBufferSizeBytes >> 2;
  if ( (g_WaveOutFormatFlags & 2) != 0 )
    samples_per_buffer = (unsigned int)g_CssMixBufferSizeBytes >> 3;
  while ( 1 )
  {
    wave_header = pwh[g_WaveOutBufferRingIndex];
    if ( (wave_header->dwFlags & 1) == 0 )
      break;
    if ( g_CSS_WaveHeaderPreparedFlags[g_WaveOutBufferRingIndex] )
    {
      mm_result = waveOutUnprepareHeader(hwo, wave_header, 0x20u);
      if ( mm_result )
        return CSS_TranslateWaveOutError(mm_result);
      g_CSS_WaveHeaderPreparedFlags[g_WaveOutBufferRingIndex] = 0;
    }
    samples_to_mix = (dwBytes - g_CSS_WaveOutFillByteOffset) / g_CSS_WaveBlockAlign;
    if ( samples_to_mix > g_CSS_WaveOutRefillRemaining )
      samples_to_mix = g_CSS_WaveOutRefillRemaining;
    if ( samples_to_mix > samples_per_buffer )
      samples_to_mix = samples_per_buffer;
    g_CSS_WaveOutRefillRemaining -= samples_to_mix;
    CSS_TickChannelLevels(g_CSS_WaveBlockAlign, samples_to_mix);
    g_CSS_WaveOutFillByteOffset = g_AudioMixToOutputFunc(samples_to_mix, g_CSS_WaveBufferDataPtrs[g_WaveOutBufferRingIndex], g_CSS_WaveOutFillByteOffset, g_CSS_MixAccumBufferPtr);
    if ( g_CSS_WaveOutFillByteOffset >= dwBytes )
    {
      pwh[g_WaveOutBufferRingIndex]->dwFlags = 0;
      pwh[g_WaveOutBufferRingIndex]->lpData = (LPSTR)g_CSS_WaveBufferDataPtrs[g_WaveOutBufferRingIndex];
      pwh[g_WaveOutBufferRingIndex]->dwBufferLength = dwBytes;
      pwh[g_WaveOutBufferRingIndex]->dwFlags = 0;
      pwh[g_WaveOutBufferRingIndex]->dwLoops = 0;
      mm_result = waveOutPrepareHeader(hwo, pwh[g_WaveOutBufferRingIndex], 0x20u);
      if ( mm_result )
        return CSS_TranslateWaveOutError(mm_result);
      header_to_write = pwh[g_WaveOutBufferRingIndex];
      wave_out_handle = hwo;
      g_CSS_WaveHeaderPreparedFlags[g_WaveOutBufferRingIndex] = 1;
      mm_result = waveOutWrite(wave_out_handle, header_to_write, 0x20u);
      if ( mm_result )
        return CSS_TranslateWaveOutError(mm_result);
      g_CSS_WaveOutFillByteOffset = 0;
      if ( ++g_WaveOutBufferRingIndex >= (unsigned int)g_CSS_MixChannelCount )
        g_WaveOutBufferRingIndex = 0;
    }
    if ( !g_CSS_WaveOutRefillRemaining )
    {
      g_CSS_WaveOutRefillRemaining = g_CSS_WaveOutChunkSampleCount;
      *chunk_completed_out = 1;
      return 0;
    }
  }
  *chunk_completed_out = 0;
  return 0;
}
// 54D4C0: using guessed type int dword_54D4C0[32];
// 54D5C0: using guessed type int dword_54D5C0[32];
// 54D6C0: using guessed type LPWAVEHDR pwh[32];
// 54D740: using guessed type int dword_54D740;
// 54D744: using guessed type int dword_54D744;
// 54D748: using guessed type int dword_54D748;
// 54D74C: using guessed type int dword_54D74C;
// 54D750: using guessed type int (__cdecl *dword_54D750)(_DWORD, _DWORD, _DWORD, _DWORD);
// 54D75C: using guessed type int dword_54D75C;
// 54D760: using guessed type int dword_54D760;
// 54DB98: using guessed type int dword_54DB98;

//----- (00470A00) --------------------------------------------------------
void __thiscall __noreturn CSS_FatalErrorExit(void *this)
{
  int v1; // ecx
  int v2; // edx
  int v3; // ecx

  fputs_(this, &g_CRT_StderrOutputStream);
  fputs_(v1, &g_CRT_StderrOutputStream);
  CRT_ExitProcessWithFinalizers(255, v2, v3);
}
// 470A18: variable 'v1' is possibly undefined
// 470A22: variable 'v2' is possibly undefined
// 470A22: variable 'v3' is possibly undefined
// 4850C6: using guessed type int __fastcall fputs_(_DWORD, _DWORD);

//----- (00470A30) --------------------------------------------------------
int __cdecl CSS_GetFormatTableValue(int format_index)
{
  return g_CSS_FormatShiftTable[format_index];
}
// 519E90: using guessed type int dword_519E90[];

//----- (00470A40) --------------------------------------------------------
int __cdecl CSS_GetFormatSampleSize(int format_index)
{
  return g_CSS_FormatSampleSizeTable[format_index];
}
// 519EAC: using guessed type int dword_519EAC[7];

//----- (00470A50) --------------------------------------------------------
int __cdecl CSS_GetFormatSilenceValue(int format_index)
{
  return g_CSS_FormatSilenceValueTable[format_index];
}
// 519EC8: using guessed type int dword_519EC8[8];

//----- (00470A60) --------------------------------------------------------
int  CSS_BuildMixLookupTables(int a1, int a2)
{
  int i; // eax
  double scaled_value; // st7
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int result; // eax
  int negated_entry; // edx
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-4h] [ebp-10h]

  v10 = a1;
  v9 = a2;
  for ( i = 0; i < 0x8000; i = v4 + 1 )
  {
    scaled_value = (double)i / g_CSS_MixLookupIndexScale + g_CSS_MixLookupIndexBias;
    _CHP(v9, v10);
    if ( v4 - (int)scaled_value > v6 )
      *(int *)((char *)&g_CSS_MixLookupTableWriteBase + v5) = v4;
  }
  for ( result = 0; result != 128; g_CSS_MixLookupComplementTable[result] = negated_entry - 1 )
    negated_entry = -g_CSS_MixLookupTable[result++];
  return result * 4;
}
// 470A60: could not find valid save-restore pair for ebx
// 470A94: variable 'v9' is possibly undefined
// 470A94: variable 'v10' is possibly undefined
// 470A9F: variable 'v4' is possibly undefined
// 470AA5: variable 'v6' is possibly undefined
// 470AE0: variable 'v5' is possibly undefined
// 501984: using guessed type double dbl_501984;
// 50198C: using guessed type double dbl_50198C;
// 54D76C: using guessed type int dword_54D76C[];
// 54D770: using guessed type int dword_54D770;
// 54D968: using guessed type int dword_54D968[];

//----- (00470AF0) --------------------------------------------------------
int __cdecl CSS_InitMixBuffers(int sample_rate, int channel_count)
{
  int buffer_bytes; // eax
  int total_alloc_bytes; // ebx
  int v4; // ecx
  int aligned_base; // eax
  int v6; // ecx

  g_CSS_MixSampleRate = sample_rate;
  g_CSS_MixChannelCount_54DBA4 = channel_count;
  g_CssMixChannelCount = 0;
  g_CssMixChannelsReadyFlag = 0;
  g_CssMixChannels = 0;
  g_CSS_MixIdleChannelFlag = 0;
  g_CSS_MixSuspendedFlag = 0;
  g_CSS_MixMasterVolume = 64;
  g_CSS_MixBufferSampleCount = 5 * sample_rate / (unsigned int)g_CSS_MixUpdateRateHz;
  if ( channel_count == 2 )
    g_CSS_MixBufferSampleCount = 2 * (5 * sample_rate / (unsigned int)g_CSS_MixUpdateRateHz);
  buffer_bytes = 4 * g_CSS_MixBufferSampleCount + 15;
  LOBYTE(buffer_bytes) = buffer_bytes & 0xF0;
  g_CssMixBufferSizeBytes = buffer_bytes;
  total_alloc_bytes = buffer_bytes + 34832;
  CSS_Mem_TryAlloc(buffer_bytes + 34832, &g_CSS_MixBufferAllocBase);
  memset_(v4, 0);
  aligned_base = g_CSS_MixBufferAllocBase + 1023;
  LOWORD(aligned_base) = (g_CSS_MixBufferAllocBase + 1023) & 0xFC00;
  g_CssMixBufferAlignedBase = aligned_base;
  g_CSS_MixAccumBufferPtr = aligned_base + 33792;
  CSS_Mem_TryAlloc(160, &g_CSS_QueuedSoundSlotTable);
  return CSS_BuildMixLookupTables(v6, total_alloc_bytes);
}
// 470B8C: variable 'v4' is possibly undefined
// 470BC1: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 519CF4: using guessed type int dword_519CF4;
// 54DB6C: using guessed type int dword_54DB6C;
// 54DB70: using guessed type int dword_54DB70;
// 54DB74: using guessed type int dword_54DB74;
// 54DB78: using guessed type int dword_54DB78;
// 54DB80: using guessed type int dword_54DB80;
// 54DB84: using guessed type int dword_54DB84;
// 54DB88: using guessed type int dword_54DB88;
// 54DB8C: using guessed type int dword_54DB8C;
// 54DB90: using guessed type int dword_54DB90;
// 54DB94: using guessed type int dword_54DB94;
// 54DB98: using guessed type int dword_54DB98;
// 54DB9C: using guessed type int dword_54DB9C;
// 54DBA4: using guessed type int dword_54DBA4;

//----- (00470BD0) --------------------------------------------------------
int CSS_FreeMixBuffers()
{
  CSS_Mem_FreeIfSet(g_CSS_MixBufferAllocBase);
  return CSS_Mem_FreeIfSet(g_CSS_QueuedSoundSlotTable);
}
// 54DB70: using guessed type int dword_54DB70;
// 54DB94: using guessed type int dword_54DB94;

//----- (00470BF0) --------------------------------------------------------
int __cdecl CSS_GetMixSampleRate(_DWORD *sample_rate_out)
{
  int result; // eax

  result = g_CSS_MixSampleRate;
  *sample_rate_out = g_CSS_MixSampleRate;
  return result;
}
// 54DB9C: using guessed type int dword_54DB9C;

//----- (00470C00) --------------------------------------------------------
int __cdecl CSS_InitMixChannels(int channel_count)
{
  int result; // eax

  g_CssMixChannelsReadyFlag = 0;
  g_CssMixChannelCount = channel_count;
  g_CSS_MixIdleChannelFlag = 0;
  g_CSS_MixSuspendedFlag = 0;
  CSS_Mem_TryAlloc(108 * channel_count, &g_CssMixChannels);
  result = CSS_ResetAllMixChannels();
  g_CssMixChannelsReadyFlag = 1;
  return result;
}
// 54DB6C: using guessed type int dword_54DB6C;
// 54DB74: using guessed type int dword_54DB74;
// 54DB78: using guessed type int dword_54DB78;
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470C60) --------------------------------------------------------
int CSS_FreeMixChannels()
{
  int result; // eax

  if ( g_CssMixChannelCount )
  {
    g_CssMixChannelsReadyFlag = 0;
    result = CSS_Mem_FreeIfSet(g_CssMixChannels);
    g_CssMixChannelCount = 0;
  }
  return result;
}
// 54DB78: using guessed type int dword_54DB78;
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470C90) --------------------------------------------------------
int CSS_ResetAllMixChannels()
{
  unsigned int i; // ebx
  int result; // eax

  for ( i = 0; i < g_CssMixChannelCount; ++i )
    result = CSS_ResetMixChannelRecord(i);
  return result;
}
// 54DB80: using guessed type int dword_54DB80;

//----- (00470CD0) --------------------------------------------------------
int __cdecl CSS_SetMixIdleChannelFlag(int idle_flag)
{
  int result; // eax

  result = idle_flag;
  g_CSS_MixIdleChannelFlag = idle_flag;
  return result;
}
// 54DB6C: using guessed type int dword_54DB6C;

//----- (00470CE0) --------------------------------------------------------
int __cdecl CSS_SetMixSuspended(int suspended_flag)
{
  int result; // eax

  result = suspended_flag;
  g_CSS_MixSuspendedFlag = suspended_flag;
  return result;
}
// 54DB74: using guessed type int dword_54DB74;

//----- (00470CF0) --------------------------------------------------------
int __cdecl CSS_SetMixMasterVolume(int master_volume)
{
  int result; // eax

  result = master_volume;
  g_CSS_MixMasterVolume = master_volume;
  return result;
}
// 54DB88: using guessed type int dword_54DB88;

//----- (00470D00) --------------------------------------------------------
int __cdecl CSS_GetMixMasterVolume(_DWORD *master_volume_out)
{
  int result; // eax

  result = g_CSS_MixMasterVolume;
  *master_volume_out = g_CSS_MixMasterVolume;
  return result;
}
// 54DB88: using guessed type int dword_54DB88;

//----- (00470D10) --------------------------------------------------------
int __cdecl CSS_BuildVolumeScaleTable(int volume_scale)
{
  int table_write_ptr; // esi
  int sample_index; // ecx
  int weighted_sum; // ebx
  int scaled_value; // eax
  int result; // eax
  int row_step; // [esp+0h] [ebp-18h]
  int row_index; // [esp+4h] [ebp-14h]

  table_write_ptr = g_CssMixBufferAlignedBase;
  if ( g_CssMixBufferAlignedBase )
  {
    g_CSS_CurrentVolumeScaleLevel = volume_scale;
    row_index = 0;
    row_step = 0;
    do
    {
      sample_index = -128;
      weighted_sum = -512 * row_index;
      do
      {
        scaled_value = weighted_sum * volume_scale / (32 * g_CssMixChannelCount);
        table_write_ptr += 4;
        ++sample_index;
        weighted_sum += row_step;
        *(_DWORD *)(table_write_ptr - 4) = scaled_value;
      }
      while ( sample_index < 128 );
      result = row_index + 1;
      row_step += 4;
      row_index = result;
    }
    while ( result < 33 );
  }
  return result;
}
// 54DB7C: using guessed type int dword_54DB7C;
// 54DB80: using guessed type int dword_54DB80;
// 54DB8C: using guessed type int dword_54DB8C;

//----- (00470DC0) --------------------------------------------------------
int __cdecl CSS_ResetMixChannelRecord(int channel_index)
{
  int channel_offset; // edx
  int result; // eax

  channel_offset = 108 * channel_index;
  result = g_CssMixChannels;
  *(_DWORD *)(channel_offset + g_CssMixChannels + 96) = 0;
  *(_DWORD *)(channel_offset + result + 68) = 0;
  *(_DWORD *)(channel_offset + result + 72) = 0;
  *(_DWORD *)(channel_offset + result + 4) = 0;
  *(_DWORD *)(channel_offset + result + 60) = 0;
  *(_DWORD *)(channel_offset + result + 64) = 1;
  *(_DWORD *)(channel_offset + result + 76) = 0;
  *(_DWORD *)(channel_offset + result + 92) = 0;
  *(_DWORD *)(channel_offset + result + 104) = 0;
  *(_DWORD *)(channel_offset + result + 48) = 0;
  *(_DWORD *)(channel_offset + result + 12) = 0;
  *(_DWORD *)(channel_offset + result + 16) = 0;
  *(_DWORD *)(channel_offset + result + 20) = 0;
  *(_DWORD *)(channel_offset + result + 24) = 0;
  *(_DWORD *)(channel_offset + result + 8) = 0;
  return result;
}
// 54DB90: using guessed type int dword_54DB90;

//----- (00470E60) --------------------------------------------------------
void __cdecl CSS_StartMixChannelPlayback(unsigned int channel_index, int playback_rate)
{
  if ( channel_index < g_CssMixChannelCount )
  {
    *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 96) = 2;
    CSS_ChannelSetRate(channel_index, playback_rate);
    CSS_ChannelSetPlayPosition(channel_index, 0);
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470EC0) --------------------------------------------------------
void __cdecl CSS_SetMixChannelLoopPoints(unsigned int channel_index, int loop_start, int loop_end)
{
  int resolved_end; // ecx
  unsigned int channel_offset; // eax
  int channels_base; // edx
  unsigned int v6; // eax
  int v7; // edx

  resolved_end = loop_end;
  if ( channel_index < g_CssMixChannelCount )
  {
    channel_offset = 108 * channel_index;
    channels_base = g_CssMixChannels;
    *(_DWORD *)(g_CssMixChannels + channel_offset + 12) = 1;
    *(_DWORD *)(channels_base + channel_offset + 16) = loop_start;
    if ( loop_end == -1 )
      resolved_end = *(_DWORD *)(channels_base + channel_offset + 8);
    v6 = 108 * channel_index;
    v7 = g_CssMixChannels;
    *(_DWORD *)(g_CssMixChannels + v6 + 20) = resolved_end;
    *(_DWORD *)(v7 + v6 + 24) = 1;
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470F40) --------------------------------------------------------
unsigned int __cdecl CSS_ClearMixChannelLoopPoints(unsigned int channel_index)
{
  unsigned int result; // eax
  int channels_base; // edx

  if ( channel_index < g_CssMixChannelCount )
  {
    result = 108 * channel_index;
    channels_base = g_CssMixChannels;
    *(_DWORD *)(g_CssMixChannels + result + 12) = 0;
    *(_DWORD *)(channels_base + result + 16) = 0;
    *(_DWORD *)(channels_base + result + 20) = 0;
    *(_DWORD *)(channels_base + result + 24) = 0;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470F90) --------------------------------------------------------
int __cdecl CSS_ChannelGetLoopRange(unsigned int channel_index, _DWORD *loop_start_out, _DWORD *loop_end_out)
{
  int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    *loop_start_out = *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 16);
    result = *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 20);
    *loop_end_out = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471030) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelMarkIdle(unsigned int channel_index)
{
  unsigned int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    result = 108 * channel_index;
    *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 96) = 0;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471070) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelMarkPlaying(unsigned int channel_index)
{
  unsigned int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    result = 108 * channel_index;
    *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 96) = 3;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004710B0) --------------------------------------------------------
BOOL __cdecl CSS_ChannelIsPlaying(unsigned int channel_index)
{
  unsigned int channel_base; // eax

  if ( channel_index >= g_CssMixChannelCount )
    return 0;
  channel_base = g_CssMixChannels + 108 * channel_index;
  return *(_DWORD *)(channel_base + 96) == 3 || *(_DWORD *)(channel_base + 96) == 2;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471100) --------------------------------------------------------
int __cdecl CSS_ChannelBeginVolumeFade(unsigned int channel_index, int target_volume, signed int fade_duration)
{
  signed int duration; // ebx
  _DWORD *channel; // ecx
  int result; // eax

  duration = fade_duration;
  if ( channel_index < g_CssMixChannelCount )
  {
    channel = (_DWORD *)(108 * channel_index + g_CssMixChannels);
    if ( !fade_duration )
      duration = 1;
    channel[21] = 1000 * (1000 * target_volume - channel[20]) / (g_CSS_MixUpdateRateHz * duration);
    result = 1000 * target_volume;
    channel[22] = 1000 * target_volume;
    if ( (int)channel[21] > 0 && !channel[20] && !channel[24] )
      channel[24] = 3;
  }
  return result;
}
// 519CF4: using guessed type int dword_519CF4;
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004711F0) --------------------------------------------------------
_DWORD * CSS_AdvanceVolumeFades(_DWORD *result)
{
  int channel_counter; // ebx
  int channel_offset; // ecx
  int new_volume; // edx

  channel_counter = 0;
  if ( g_CssMixChannelCount > 0 )
  {
    channel_offset = 0;
    do
    {
      result = (_DWORD *)(channel_offset + g_CssMixChannels);
      new_volume = *(_DWORD *)(channel_offset + g_CssMixChannels + 80);
      if ( *(int *)(channel_offset + g_CssMixChannels + 84) <= 0 )
      {
        if ( (int)result[21] < 0 )
        {
          new_volume += result[21];
          if ( new_volume <= result[22] )
          {
            result[21] = 0;
            new_volume = result[22];
            if ( !new_volume && result[24] == 3 )
              result[24] = 0;
          }
        }
      }
      else
      {
        new_volume += result[21];
        if ( new_volume >= result[22] )
        {
          result[21] = 0;
          new_volume = result[22];
        }
      }
      result[20] = new_volume;
      ++channel_counter;
      channel_offset += 108;
    }
    while ( channel_counter < g_CssMixChannelCount );
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471260) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelSetRate(unsigned int channel_index, int rate)
{
  unsigned int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    result = g_CssMixChannels + 108 * channel_index;
    *(_DWORD *)(result + 60) = rate;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004712A0) --------------------------------------------------------
void __cdecl CSS_ChannelGetRate(unsigned int channel_index, _DWORD *rate_out)
{
  unsigned int channel_base; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    channel_base = g_CssMixChannels + 108 * channel_index;
    if ( *(_DWORD *)(channel_base + 96) > 1u )
      *rate_out = *(_DWORD *)(channel_base + 60);
    else
      *rate_out = 0;
  }
}
// 4712D7: simplified comparisons for '[ds.2:(eax.4+#0x60.4)].4': !=0 && !=1 became >=2u
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004712F0) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelSetVolumeImmediate(unsigned int channel_index, int volume)
{
  unsigned int result; // eax

  result = channel_index;
  if ( channel_index < g_CssMixChannelCount )
  {
    result = 108 * channel_index;
    *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 80) = 1000 * volume;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471350) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelGetVolume(unsigned int channel_index, _DWORD *volume_out)
{
  unsigned int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    result = *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 80) / 0x3E8u;
    *volume_out = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004713A0) --------------------------------------------------------
void __cdecl CSS_ChannelAssignQueueSlot(unsigned int channel_index, int queue_slot_index)
{
  _DWORD *channel; // edx
  int queue_slot; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    channel = (_DWORD *)(108 * channel_index + g_CssMixChannels);
    queue_slot = g_CSS_QueuedSoundSlotTable + 40 * (queue_slot_index - 1);
    channel[17] = queue_slot_index;
    channel[18] = 1;
    if ( *(_DWORD *)(queue_slot + 12) == 5 && channel[24] == 1 )
    {
      channel[24] = 3;
      CSS_ChannelSetPlayPosition(channel_index, *(_DWORD *)(queue_slot + 16));
    }
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;
// 54DB94: using guessed type int dword_54DB94;

//----- (00471430) --------------------------------------------------------
void __cdecl CSS_ChannelQueueSound(unsigned int channel_index, int sample_data, signed int sample_bytes, int playback_rate, int format_index)
{
  unsigned int queue_slot_index; // ebx

  queue_slot_index = CSS_QueueSoundDescriptor(sample_data, sample_bytes, format_index);
  CSS_ResetMixChannelRecord(channel_index);
  CSS_ChannelAssignQueueSlot(channel_index, queue_slot_index);
  CSS_StartMixChannelPlayback(channel_index, playback_rate);
}

//----- (00471480) --------------------------------------------------------
unsigned int __cdecl CSS_QueueSoundDescriptor(int sample_data, signed int sample_bytes, int format_index)
{
  unsigned int ring_index; // edx
  unsigned int slot_number; // esi
  _DWORD *slot; // ebx
  char format_shift; // al

  ring_index = g_CSS_SoundDescriptorRingIndex + 1;
  g_CSS_SoundDescriptorRingIndex = ring_index;
  slot_number = ring_index;
  if ( ring_index >= 4 )
    g_CSS_SoundDescriptorRingIndex = 0;
  slot = (_DWORD *)(40 * (ring_index - 1) + g_CSS_QueuedSoundSlotTable);
  *slot = sample_data;
  format_shift = CSS_GetFormatTableValue(format_index);
  slot[3] = 0;
  slot[4] = 0;
  slot[5] = 0;
  slot[6] = 0;
  slot[7] = 0;
  slot[8] = 0;
  slot[9] = 0;
  slot[1] = format_index;
  slot[2] = sample_bytes >> format_shift;
  return slot_number;
}
// 519E38: using guessed type int dword_519E38;
// 54DB94: using guessed type int dword_54DB94;

//----- (00471560) --------------------------------------------------------
_DWORD *__cdecl CSS_ChannelLoadQueuedSound(int channel_index)
{
  _DWORD *result; // eax
  _DWORD *queue_slot; // edx

  result = (_DWORD *)(g_CssMixChannels + 108 * channel_index);
  queue_slot = (_DWORD *)(g_CSS_QueuedSoundSlotTable + 40 * (result[17] - 1));
  *result = *queue_slot;
  result[2] = queue_slot[2];
  result[3] = queue_slot[3];
  result[4] = queue_slot[4];
  result[5] = queue_slot[5];
  result[6] = queue_slot[6];
  result[7] = queue_slot[7];
  result[8] = queue_slot[8];
  result[9] = queue_slot[9];
  result[10] = 0;
  result[11] = 0;
  result[18] = 0;
  result[1] = queue_slot[1];
  return result;
}
// 54DB90: using guessed type int dword_54DB90;
// 54DB94: using guessed type int dword_54DB94;

//----- (00471610) --------------------------------------------------------
void __cdecl CSS_ChannelSetPlayPosition(unsigned int channel_index, unsigned int a2)
{
  int *channel; // ebx
  unsigned int sample_position; // esi
  unsigned int loop_mode; // eax
  unsigned int queued_loop_mode; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    channel = (int *)(g_CssMixChannels + 108 * channel_index);
    sample_position = a2 >> CSS_GetFormatTableValue(channel[1]);
    if ( !channel[18] || (CSS_ChannelLoadQueuedSound(channel_index), channel[3] == 2) || channel[3] == 3 || channel[24] != 4 )
    {
      if ( channel[17] && channel[15] )
      {
        switch ( channel[24] )
        {
          case 1:
          case 2:
          case 3:
            channel[25] = 1;
            loop_mode = channel[6];
            if ( loop_mode )
            {
              if ( loop_mode > 1 )
              {
                if ( loop_mode == 2 )
                {
                  if ( sample_position < channel[5] )
                  {
                    channel[12] = sample_position;
                    channel[16] = 1;
                  }
                  else
                  {
                    channel[12] = channel[5];
                    channel[16] = -1;
                  }
                  channel[13] = 0;
                  channel[24] = 3;
                }
              }
              else
              {
                if ( sample_position >= channel[5] )
                  channel[12] = channel[4];
                else
                  channel[12] = sample_position;
                channel[13] = 0;
                channel[16] = 1;
                channel[24] = 3;
              }
            }
            else
            {
              if ( sample_position >= channel[2] )
                goto LABEL_10;
              channel[12] = sample_position;
              channel[13] = 0;
              channel[16] = 1;
              channel[24] = 3;
            }
            break;
          case 4:
            channel[25] = 2;
            queued_loop_mode = channel[9];
            if ( queued_loop_mode )
            {
              if ( queued_loop_mode > 1 )
              {
                if ( queued_loop_mode == 2 )
                {
                  if ( sample_position < channel[8] )
                  {
                    channel[12] = sample_position;
                    channel[16] = 1;
                  }
                  else
                  {
                    channel[12] = channel[8];
                    channel[16] = -1;
                  }
                  channel[13] = 0;
                  channel[24] = 3;
                }
              }
              else
              {
                if ( sample_position >= channel[8] )
                  channel[12] = channel[7];
                else
                  channel[12] = sample_position;
                channel[13] = 0;
                channel[16] = 1;
                channel[24] = 3;
              }
            }
            else
            {
              if ( sample_position >= channel[2] )
                goto LABEL_10;
              channel[12] = sample_position;
              channel[13] = 0;
              channel[16] = 1;
              channel[24] = 3;
            }
            break;
          default:
            return;
        }
      }
    }
    else
    {
LABEL_10:
      channel[24] = 1;
    }
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471800) --------------------------------------------------------
int __cdecl CSS_ChannelGetPlayPosition(unsigned int channel_index, _DWORD *position_out)
{
  unsigned int channel_base; // ebx
  int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    channel_base = 108 * channel_index + g_CssMixChannels;
    result = *(_DWORD *)(channel_base + 48) << CSS_GetFormatTableValue(*(_DWORD *)(channel_base + 4));
    *position_out = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471890) --------------------------------------------------------
void __cdecl CSS_ChannelSetPanning(unsigned int channel_index, int panning)
{
  int adjusted_panning; // ecx
  unsigned int channel_base; // eax

  adjusted_panning = panning;
  if ( channel_index < g_CssMixChannelCount )
  {
    channel_base = 108 * channel_index + g_CssMixChannels;
    if ( *(_DWORD *)(channel_base + 4) != 1 && *(_DWORD *)(channel_base + 4) != 2 && *(_DWORD *)(channel_base + 4) != 5 && panning == 128 )
      adjusted_panning = 0;
    *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 76) = adjusted_panning;
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471910) --------------------------------------------------------
int __cdecl CSS_ChannelGetPanning(unsigned int channel_index, _DWORD *panning_out)
{
  int result; // eax

  if ( channel_index < g_CssMixChannelCount )
  {
    result = *(_DWORD *)(g_CssMixChannels + 108 * channel_index + 76);
    *panning_out = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471990) --------------------------------------------------------
void  CSS_TickChannelLevels(int a1, int sample_count)
{
  unsigned int channel_index; // ebx
  int channel_offset; // esi

  if ( !g_CSS_MixSuspendedFlag && g_CssMixChannelCount && g_CssMixChannelsReadyFlag )
  {
    channel_index = 0;
    if ( g_CssMixChannelCount )
    {
      channel_offset = 0;
      do
      {
        if ( !*(_DWORD *)(channel_offset + g_CssMixChannels + 92) && !g_CSS_MixIdleChannelFlag )
          a1 = 1000;
        channel_offset += 108;
        Audio_MixResampledVoice((int *)a1);
        a1 = g_CssMixChannelCount;
        ++channel_index;
      }
      while ( channel_index < g_CssMixChannelCount );
    }
  }
  else
  {
    Audio_ClearGlobalMixBuffer(sample_count);
  }
}
// 54DB6C: using guessed type int dword_54DB6C;
// 54DB74: using guessed type int dword_54DB74;
// 54DB78: using guessed type int dword_54DB78;
// 54DB80: using guessed type int dword_54DB80;
// 54DB88: using guessed type int dword_54DB88;
// 54DB90: using guessed type int dword_54DB90;
// 54DBA4: using guessed type int dword_54DBA4;

//----- (00471A30) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelInitPlayback(unsigned int channel_index, int sample_data, unsigned int sample_bytes, int format_index, unsigned int playback_rate)
{
  unsigned int result; // eax
  _DWORD *channel; // ebx

  result = channel_index;
  if ( channel_index < g_CssMixChannelCount )
  {
    channel = (_DWORD *)(108 * channel_index + g_CssMixChannels);
    *channel = sample_data;
    channel[3] = 1;
    channel[13] = 0;
    channel[12] = channel[13];
    channel[8] = 0;
    channel[7] = channel[8];
    channel[9] = 0;
    channel[4] = 0;
    channel[6] = 1;
    channel[5] = sample_bytes >> CSS_GetFormatTableValue(format_index);
    channel[2] = sample_bytes >> CSS_GetFormatTableValue(format_index);
    result = playback_rate;
    channel[15] = playback_rate;
    channel[16] = 1;
    channel[17] = 5;
    channel[18] = 0;
    channel[19] = 0;
    channel[20] = 64000;
    channel[21] = 0;
    channel[22] = 0;
    channel[23] = 0;
    channel[25] = 1;
    channel[14] = 0;
    channel[1] = format_index;
    channel[10] = 0;
    channel[11] = 0;
    channel[24] = 3;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471B40) --------------------------------------------------------
void __cdecl CSS_ChannelStop(unsigned int channel_index)
{
  CSS_ChannelMarkIdle(channel_index);
}

//----- (00471BA0) --------------------------------------------------------
void __cdecl CSS_ChannelSetPositionOffset(unsigned int channel_index, unsigned int a2)
{
  unsigned int channel_base; // ebx

  if ( channel_index < g_CssMixChannelCount )
  {
    channel_base = 108 * channel_index + g_CssMixChannels;
    *(_DWORD *)(channel_base + 56) = a2 >> CSS_GetFormatTableValue(*(_DWORD *)(channel_base + 4));
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471BF0) --------------------------------------------------------
char  Compat_StringHolderDestructor(_DWORD *holder)
{
  Compat_StringHolderFreeText(holder);
  return 0;
}

//----- (00471C40) --------------------------------------------------------
int Compat_StringHolderFreeText(_DWORD *holder)
{
  if ( holder )
  {
    if ( *holder )
      j__nfree_(*holder);
    *holder = 0;
  }
  return 0;
}

//----- (00471C60) --------------------------------------------------------
int  Compat_StringHolderScalarDeletingDtor(int holder, char flags)
{
  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(holder, &g_CompatStringHolder_DtorArrayDescriptor);
    j_j__nfree_();
    return holder;
  }
  *(_DWORD *)(holder + 4) = &g_CompatStringHolder_Vtable;
  Compat_StringHolderFreeText((_DWORD *)holder);
  if ( (flags & 2) != 0 )
    j__nfree_(holder);
  return holder;
}
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();

static const char *Compat_StringHolderGetText(_DWORD *holder)
{
  if ( !holder || !*holder )
    return 0;
  return (const char *)(uintptr_t)(unsigned int)*holder;
}

static const char *Compat_StringArgGetText(const void *arg)
{
  const _DWORD *words;
  uintptr_t native_text_ptr;

  if ( !arg )
    return 0;
  words = (const _DWORD *)(uintptr_t)arg;
  if ( words[1] == (unsigned int)(uintptr_t)&g_CompatStringHolder_Vtable || words[1] == (unsigned int)(uintptr_t)&g_PathEntry_Vtable )
    return Compat_StringHolderGetText((_DWORD *)(uintptr_t)arg);
  native_text_ptr = *(const uintptr_t *)arg;
  if ( !native_text_ptr )
    return 0;
  return (const char *)native_text_ptr;
}

static int Compat_QueryRead(int query_handle, void *buffer, int byte_count)
{
  uintptr_t *vtable;

  if ( !query_handle )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query_handle;
  if ( !vtable || !vtable[5] )
    return 0;
  return ((int (*)(int, void *, int))(uintptr_t)vtable[5])(query_handle, buffer, byte_count);
}

static int Compat_QuerySeek(int query_handle, int offset)
{
  uintptr_t *vtable;

  if ( !query_handle )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query_handle;
  if ( !vtable || !vtable[0] )
    return 0;
  return ((int (*)(int, int))(uintptr_t)vtable[0])(query_handle, offset);
}

static void Compat_StringHolderAssignJoined(_DWORD *holder, const char *prefix, const char *suffix)
{
  unsigned int prefix_size;
  unsigned int suffix_size;
  unsigned int total_size;
  unsigned char *copy;

  if ( !holder )
    return;
  if ( prefix )
    prefix_size = (unsigned int)strlen(prefix);
  else
    prefix_size = 0;
  if ( suffix )
    suffix_size = (unsigned int)strlen(suffix);
  else
    suffix_size = 0;
  if ( !prefix_size && !suffix_size )
  {
    Compat_StringHolderFreeText(holder);
    return;
  }
  total_size = prefix_size + suffix_size;
  copy = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)(total_size + 1));
  if ( !copy )
  {
    Compat_StringHolderFreeText(holder);
    return;
  }
  if ( prefix_size )
    memcpy(copy, prefix, prefix_size);
  if ( suffix_size )
    memcpy(copy + prefix_size, suffix, suffix_size);
  copy[total_size] = 0;
  Compat_StringHolderFreeText(holder);
  *holder = (int)(uintptr_t)copy;
}

static void Compat_StringHolderInsertText(_DWORD *holder, signed int index, const char *inserted_text)
{
  const char *existing_text;
  unsigned int existing_size;
  unsigned int inserted_size;
  unsigned int total_size;
  unsigned char *copy;

  if ( !holder )
    return;
  existing_text = Compat_StringHolderGetText(holder);
  if ( existing_text )
    existing_size = (unsigned int)strlen(existing_text);
  else
    existing_size = 0;
  if ( inserted_text )
    inserted_size = (unsigned int)strlen(inserted_text);
  else
    inserted_size = 0;
  if ( index < 0 || (unsigned int)index > existing_size || !inserted_size )
    return;
  total_size = existing_size + inserted_size;
  copy = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)(total_size + 1));
  if ( !copy )
    return;
  if ( index > 0 )
    memcpy(copy, existing_text, (unsigned int)index);
  memcpy(copy + index, inserted_text, inserted_size);
  if ( existing_size > (unsigned int)index )
    memcpy(copy + index + inserted_size, existing_text + index, existing_size - (unsigned int)index);
  copy[total_size] = 0;
  Compat_StringHolderFreeText(holder);
  *holder = (int)(uintptr_t)copy;
}

static void Compat_StringHolderCopyText(_DWORD *holder, const char *source)
{
  unsigned char *copy;
  unsigned int copy_size;

  if ( !holder )
    return;
  Compat_StringHolderFreeText(holder);
  if ( !source || !*source )
    return;
  copy_size = (unsigned int)strlen(source) + 1;
  copy = (unsigned char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes((int)copy_size);
  if ( !copy )
    return;
  memcpy(copy, source, copy_size);
  *holder = (int)(uintptr_t)copy;
}

static void Compat_StringHolderInitText(_DWORD *holder, const char *source)
{
  if ( !holder )
    return;
  Compat_StringHolderFreeText(holder);
  if ( source && *source )
    Compat_StringHolderCopyText(holder, source);
}

static const char **Compat_StringHolderBuildParentPath(_DWORD *holder, const char *source_text)
{
  unsigned int text_len;
  int slash_index;

  holder[0] = 0;
  holder[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor((const char **)holder);
  holder[1] = &g_PathEntry_Vtable;
  if ( source_text && *source_text )
    Compat_StringHolderCopyText(holder, source_text);
  slash_index = Compat_StringHolderFindLastBackslash((_BYTE **)holder);
  if ( slash_index == -1 )
  {
    Compat_StringHolderCopyText(holder, "");
    return (const char **)holder;
  }
  source_text = Compat_StringHolderGetText(holder);
  text_len = source_text ? (unsigned int)strlen(source_text) : 0;
  Compat_StringHolderRemoveRange((char **)holder, slash_index, text_len, (int)(text_len - (unsigned int)slash_index));
  return (const char **)holder;
}

static _DWORD *Compat_StringHolderBuildLeafName(_DWORD *holder, const char *source_text)
{
  unsigned int text_len;
  int slash_index;

  holder[0] = 0;
  holder[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor((const char **)holder);
  holder[1] = &g_PathEntry_Vtable;
  if ( source_text && *source_text )
    Compat_StringHolderCopyText(holder, source_text);
  slash_index = Compat_StringHolderFindLastBackslash((_BYTE **)holder);
  if ( slash_index == -1 )
    return holder;
  source_text = Compat_StringHolderGetText(holder);
  text_len = source_text ? (unsigned int)strlen(source_text) : 0;
  Compat_StringHolderRemoveRange((char **)holder, 0, text_len, slash_index + 1);
  return holder;
}

static int Compat_StringHolderDestroyStack(_DWORD *holder, char flags)
{
  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__((int)(uintptr_t)holder, &g_CompatStringHolder_DtorArrayDescriptor);
    j_j__nfree_();
    return (int)(uintptr_t)holder;
  }
  holder[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderFreeText(holder);
  if ( (flags & 2) != 0 )
    j__nfree_((int)(uintptr_t)holder);
  return (int)(uintptr_t)holder;
}

//----- (00471CA0) --------------------------------------------------------
_DWORD * Compat_StringHolderConstructJoined(_DWORD *holder, _DWORD *prefix_holder, const char *suffix)
{
  holder[0] = 0;
  holder[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderAssignJoined(holder, Compat_StringHolderGetText(prefix_holder), suffix);
  holder[1] = &g_PathEntry_Vtable;
  return holder;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00471D10) --------------------------------------------------------
const char ** Compat_StringHolderAppendText(const char **holder_ref, const char *appended_text)
{
  _DWORD *holder;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  if ( appended_text && *appended_text )
    Compat_StringHolderAssignJoined(holder, Compat_StringHolderGetText(holder), appended_text);
  return holder_ref;
}

//----- (00471DE0) --------------------------------------------------------
const char ** Compat_StringHolderPrependText(const char **holder_ref, const char *prepended_text)
{
  _DWORD *holder;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  if ( prepended_text && *prepended_text )
    Compat_StringHolderAssignJoined(holder, prepended_text, Compat_StringHolderGetText(holder));
  return holder_ref;
}

//----- (00471EE0) --------------------------------------------------------
int  Compat_StringHolderFindSubstringOffset(_DWORD *holder, int a2, int needle)
{
  int match_ptr; // eax
  _DWORD *v5; // ecx

  if ( a2 && *holder && (match_ptr = ((int (__cdecl *)(int))strstr_)(needle)) != 0 )
    return match_ptr - *v5;
  else
    return -1;
}
// 471EFD: variable 'v5' is possibly undefined

//----- (00471F10) --------------------------------------------------------
const char ** Compat_StringHolderUppercaseInPlace(const char **holder_ref, unsigned int a2)
{
  const char *text; // eax

  text = Compat_StringHolderGetText((_DWORD *)holder_ref);
  if ( text && *text )
  {
    Compat_StringHolderAssignJoined((_DWORD *)holder_ref, text, 0);
    Compat_StruprAsciiInPlace((char *)Compat_StringHolderGetText((_DWORD *)holder_ref));
  }
  return holder_ref;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 47BBE3: using guessed type int __fastcall strupr_(_DWORD, _DWORD);

//----- (00472120) --------------------------------------------------------
int  Compat_StringHolderFindCharFrom(const char **holder_ref, char search_char, signed int start_index)
{
  const char *text;
  const char *match;
  unsigned int text_len;

  text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)holder_ref);
  if ( !text || !*text || start_index < 0 )
    return -1;
  text_len = (unsigned int)strlen(text);
  if ( (unsigned int)start_index >= text_len )
    return -1;
  match = strchr(text + start_index, search_char);
  if ( !match )
    return -1;
  return (int)(match - text);
}

//----- (00472190) --------------------------------------------------------
int  Compat_StringHolderFindLastBackslash(_BYTE **holder_ref)
{
  const char *text;
  char *last_slash;

  text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)holder_ref);
  if ( !text || !*text )
    return -1;
  last_slash = Compat_StrrchrChar(text, '\\');
  if ( !last_slash )
    return -1;
  return (int)(last_slash - text);
}

//----- (004721C0) --------------------------------------------------------
int  Compat_StringHolderFindLastBackslashBefore(char **holder_ref, signed int end_index)
{
  _DWORD *holder;
  char *text;
  unsigned int text_len;
  char saved_char;
  char *last_slash;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  text = (char *)Compat_StringHolderGetText(holder);
  if ( !text || !*text || end_index < 0 )
    return -1;
  text_len = (unsigned int)strlen(text);
  if ( (unsigned int)end_index >= text_len )
    return -1;
  saved_char = text[end_index + 1];
  text[end_index + 1] = 0;
  last_slash = Compat_StrrchrChar(text, '\\');
  text[end_index + 1] = saved_char;
  if ( !last_slash )
    return -1;
  return (int)(last_slash - text);
}

//----- (00472230) --------------------------------------------------------
char ** Compat_StringHolderRemoveRange(char **holder_ref, int start_index, unsigned int a3, int remove_count)
{
  _DWORD *holder;
  const char *text;
  unsigned int text_len;
  char *copy;

  holder = (_DWORD *)(uintptr_t)holder_ref;
  text = Compat_StringHolderGetText(holder);
  if ( !text || !*text || start_index < 0 )
    return holder_ref;
  text_len = (unsigned int)strlen(text);
  a3 = text_len;
  if ( text_len != (unsigned int)remove_count )
  {
    copy = (char *)(uintptr_t)(unsigned int)j_Mem_Alloc(a3 + 1);
    if ( !copy )
      return holder_ref;
    Compat_CopyPrefixN(copy, text, start_index);
    copy[start_index] = 0;
    if ( (unsigned int)(start_index + remove_count) < text_len )
      Compat_CopyPrefixN(copy + start_index, text + start_index + remove_count, text_len - (unsigned int)(start_index + remove_count) + 1);
    Compat_StringHolderFreeText(holder);
    *holder = (int)(uintptr_t)copy;
    j_j__nfree_();
    return holder_ref;
  }
  Compat_StringHolderDestructor((const char **)holder);
  return holder_ref;
}
// 47228D: variable 'v9' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00472320) --------------------------------------------------------
const char ** Compat_StringHolderInsertTextChecked(const char **result, signed int insert_index, const char *inserted_text)
{
  if ( insert_index >= 0 && inserted_text && *inserted_text )
    Compat_StringHolderInsertText((_DWORD *)result, insert_index, inserted_text);
  return result;
}

//----- (00472470) --------------------------------------------------------
_DWORD * Compat_StringHolderInitBase(_DWORD *result)
{
  *result = 0;
  result[1] = &g_CompatStringHolder_Vtable;
  return result;
}
// 50EC84: using guessed type int (*off_50EC84)();

//----- (00472558) --------------------------------------------------------
void  __noreturn CRT_ExitProcessWithFinalizers(int exit_code, int a2, int a3)
{
  (void)a2;
  (void)a3;

  /*
   * The original CRT finalizer band is still under-recovered and currently
   * crashes inside `sub_4B52E6` on fatal quit paths under WSL. For process
   * termination we only need a reliable exit, so quarantine the finalizer walk
   * until its object-registration contract is reconstructed safely.
   */
  ExitProcess((UINT)exit_code);
}
// 472575: variable 'v5' is possibly undefined
// 47257C: variable 'v4' is possibly undefined
// 48569B: using guessed type int __fastcall _FiniRtns(_DWORD, _DWORD);
// 519EF4: using guessed type int (__fastcall *off_519EF4)(_DWORD, _DWORD);

//----- (00472584) --------------------------------------------------------
void  __noreturn CRT_ExitProcessRunFinalizers(int a1, int a2, int a3)
{
  int v3; // edx
  int v4; // ecx
  UINT exit_code; // ebx
  int v6; // ecx

  g_CRT_ExitFinalizerCallbackA(a3, a1);
  g_CRT_ExitFinalizerCallbackB(a2);
  if ( g_CRT_ExitProcessFinalizerHook )
    g_CRT_ExitProcessFinalizerHook();
  exit_code = v3;
  if ( g_CrtThreadDataMgmtDisabledFlag )
  {
    if ( g_CRT_ProcessExitThreadHook )
      g_CRT_ProcessExitThreadHook(v4, 255);
  }
  else
  {
    CRT_RemoveUnhandledExceptionFilter(v4, v3);
    _FiniRtns(v6, 15);
    g_CRT_TlsIndexDestroyHook();
  }
  ExitProcess(exit_code);
}
// 485601: variable 'v3' is possibly undefined
// 48561C: variable 'v4' is possibly undefined
// 485630: variable 'v6' is possibly undefined
// 485379: using guessed type _DWORD nullsub_8();
// 48569B: using guessed type int __fastcall _FiniRtns(_DWORD, _DWORD);
// 519EF4: using guessed type int (__fastcall *off_519EF4)(_DWORD, _DWORD);
// 519EF8: using guessed type int (__cdecl *off_519EF8)(_DWORD);
// 51A5A4: using guessed type _DWORD (*off_51A5A4)();
// 51A5B0: using guessed type int (__fastcall *dword_51A5B0)(_DWORD, _DWORD);
// 51A5F4: using guessed type int (*dword_51A5F4)(void);

//----- (004725B0) --------------------------------------------------------
int __fastcall Mem_InitReserveBlock(int a1, int a2)
{
  int result; // eax
  int v3; // ecx

  (void)a1;
  (void)a2;
  g_ClipsMemoryTable = nmalloc_(0x7D0, 0);
  if ( !g_ClipsMemoryTable )
  {
    Rules_PrintErrorID((int)aMemory, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutOfMemory_, v3);
    IO_RunRouterExitCallbacks();
  }
  for ( result = 0; result != 2000; result += 4 )
    *(_DWORD *)(g_ClipsMemoryTable + result) = 0;
  return result;
}
// 472605: variable 'v3' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472620) --------------------------------------------------------
signed int  Mem_HeapAllocWithRetry(_DWORD *requested_bytes)
{
  int request_size;
  int grow_size;
  signed int result; // eax
  signed int (__fastcall *allocator_callback)(int);

  request_size = (int)(uintptr_t)requested_bytes;
  result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size);
  if ( result )
    goto LABEL_5;
  grow_size = 5 * request_size;
  if ( (unsigned int)grow_size <= 0x1000 )
    grow_size = 4096;
  Mem_PurgeFreeListsForSpace(grow_size, 0, request_size);
  result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size);
  if ( result || (Mem_PurgeFreeListsForSpace(-1, 1, request_size), (result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size)) != 0) )
  {
LABEL_5:
    g_Mem_TotalAllocatedBytes += request_size;
    ++g_Mem_TotalAllocationCount;
  }
  else
  {
    allocator_callback = (signed int (__fastcall *)(int))g_Mem_OutOfMemoryHandler;
    while ( !allocator_callback(request_size) )
    {
      result = Mem_PoolAllocBlock((unsigned int)request_size, (_DWORD *)(uintptr_t)request_size);
      if ( result )
        goto LABEL_5;
    }
    return 0;
  }
  return result;
}
// 519EFC: using guessed type int dword_519EFC;
// 519F00: using guessed type int dword_519F00;
// 519F10: using guessed type signed int (*off_519F10)();

//----- (004726C0) --------------------------------------------------------
signed int Mem_FatalOutOfMemory()
{
  int v0; // ecx

  Rules_PrintErrorID((int)aMemory, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutOfMemory_, v0);
  IO_RunRouterExitCallbacks();
  return 1;
}
// 4726DD: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00472700) --------------------------------------------------------
int Mem_SetOutOfMemoryHandler(int a1)
{
  int previous_handler;

  previous_handler = (int)(intptr_t)g_Mem_OutOfMemoryHandler;
  g_Mem_OutOfMemoryHandler = (signed int (*)())(intptr_t)a1;
  return previous_handler;
}

//----- (00472710) --------------------------------------------------------
signed int  Mem_ReleasePoolBlock(int block, int block_size)
{
  int v2; // ecx
  signed int result; // eax
  int v4; // ecx

  if ( Mem_PoolFreeCoalesce(block, block_size) )
  {
    result = 0;
    g_Mem_TotalAllocatedBytes -= v2;
    --g_Mem_TotalAllocationCount;
  }
  else
  {
    Rules_PrintErrorID((int)aMemory, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReleaseErrorIn, v4);
    return -1;
  }
  return result;
}
// 47272D: variable 'v2' is possibly undefined
// 47275A: variable 'v4' is possibly undefined
// 519EFC: using guessed type int dword_519EFC;
// 519F00: using guessed type int dword_519F00;
// 51A614: using guessed type char *off_51A614[5];

//----- (00472770) --------------------------------------------------------
_DWORD * Mem_Realloc(char *old_block, unsigned int old_size, unsigned int new_size)
{
  _DWORD *alloc_result; // eax
  int copy_size; // edx
  int copy_limit; // edi
  unsigned int v8; // eax
  _DWORD *dest_cursor; // edx
  char *src_cursor; // ecx
  char v11; // bl
  _BYTE *zero_cursor; // edx
  _DWORD *new_block; // [esp+0h] [ebp-10h]

  if ( new_size )
    alloc_result = Mem_SmallBlockAlloc(new_size);
  else
    alloc_result = 0;
  new_block = alloc_result;
  if ( old_block )
  {
    if ( old_size >= new_size )
      copy_size = new_size;
    else
      copy_size = old_size;
    copy_limit = copy_size;
    v8 = 0;
    if ( copy_size > 0 )
    {
      dest_cursor = new_block;
      src_cursor = old_block;
      do
      {
        dest_cursor = (_DWORD *)((char *)dest_cursor + 1);
        v11 = *src_cursor++;
        ++v8;
        *((_BYTE *)dest_cursor - 1) = v11;
      }
      while ( (int)v8 < copy_limit );
    }
    zero_cursor = (char *)new_block + v8;
    while ( v8 < new_size )
    {
      ++v8;
      *zero_cursor++ = 0;
    }
    Mem_SmallBlockFree(old_block, old_size);
  }
  return new_block;
}

//----- (00472800) --------------------------------------------------------
int Mem_GetTotalAllocatedBytes()
{
  return g_Mem_TotalAllocatedBytes;
}
// 519EFC: using guessed type int dword_519EFC;

//----- (00472810) --------------------------------------------------------
int Mem_GetTotalAllocationCount()
{
  return g_Mem_TotalAllocationCount;
}
// 519F00: using guessed type int dword_519F00;

//----- (00472860) --------------------------------------------------------
int  Mem_PurgeFreeListsForSpace(int bytes_needed, int verbose_flag, int request_size)
{
  int freed_bytes; // esi
  unsigned int size_class; // ecx
  int table_offset; // edi
  int free_node; // eax
  int next_node; // ebx

  freed_bytes = 0;
  if ( verbose_flag == 1 )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aDeallocatingMe, request_size);
  size_class = 499;
  table_offset = 1996;
  do
  {
    free_node = *(_DWORD *)(table_offset + g_ClipsMemoryTable);
    if ( free_node )
    {
      do
      {
        next_node = *(_DWORD *)(uintptr_t)(unsigned int)free_node;
        Mem_ReleasePoolBlock((int)free_node, size_class);
        freed_bytes += size_class;
        free_node = next_node;
      }
      while ( next_node );
    }
    *(_DWORD *)(table_offset + g_ClipsMemoryTable) = 0;
    if ( freed_bytes > bytes_needed && bytes_needed > 0 )
      break;
    --size_class;
    table_offset -= 4;
  }
  while ( size_class >= 4 );
  if ( verbose_flag == 1 )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aMemoryDealloca, size_class);
  return freed_bytes;
}
// 47288E: variable 'v5' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 54DBA8: using guessed type int dword_54DBA8;

//----- (004728F0) --------------------------------------------------------
_BYTE * Mem_SmallBlockAllocZeroed(unsigned int size)
{
  signed int clamped_size; // ecx
  int free_list_slot; // eax
  int free_node; // edx
  int block; // esi
  signed int i; // eax
  _BYTE *zero_cursor; // edx
  int allocation_size; // ecx
  int allocated_block; // esi
  int j; // eax

  clamped_size = size;
  if ( size >= 4 )
  {
    if ( (int)size >= 500 )
      return (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)size);
  }
  else
  {
    clamped_size = 4;
  }
  free_list_slot = 4 * clamped_size + g_ClipsMemoryTable;
  free_node = *(_DWORD *)free_list_slot;
  if ( free_node )
  {
    block = free_node;
    *(_DWORD *)free_list_slot = *(_DWORD *)free_node;
    for ( i = 0; i < clamped_size; ++free_node )
    {
      ++i;
      *(_BYTE *)free_node = 0;
    }
    return (_BYTE *)block;
  }
  else
  {
    allocation_size = clamped_size;
    zero_cursor = (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)allocation_size);
    allocated_block = (int)zero_cursor;
    for ( j = 0; j < allocation_size; ++zero_cursor )
    {
      ++j;
      *zero_cursor = 0;
    }
    return (_BYTE *)allocated_block;
  }
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472980) --------------------------------------------------------
_DWORD * Mem_SmallBlockAlloc(unsigned int size)
{
  int free_list_slot; // ecx
  int free_node; // edx

  if ( size >= 4 )
  {
    if ( (int)size >= 500 )
      return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)size);
  }
  else
  {
    size = 4;
  }
  free_list_slot = g_ClipsMemoryTable + 4 * size;
  free_node = *(_DWORD *)free_list_slot;
  if ( free_node )
  {
    *(_DWORD *)free_list_slot = *(_DWORD *)free_node;
    return (_DWORD *)free_node;
  }
  return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)size);
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (004729C0) --------------------------------------------------------
_DWORD * Mem_NewArray(unsigned int size)
{
  int free_list_slot; // ecx
  int free_node; // edx

  if ( size >= 4 )
  {
    if ( (int)size >= 500 )
      return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)size);
  }
  else
  {
    size = 4;
  }
  free_list_slot = g_ClipsMemoryTable + 4 * size;
  free_node = *(_DWORD *)free_list_slot;
  if ( free_node )
  {
    *(_DWORD *)free_list_slot = *(_DWORD *)free_node;
    return (_DWORD *)free_node;
  }
  return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)size);
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472A00) --------------------------------------------------------
signed int  Mem_SmallBlockFree(_DWORD *block, int size)
{
  int clamped_size; // ecx

  clamped_size = size;
  if ( !size )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( (unsigned int)clamped_size < 4 )
  {
    clamped_size = 4;
LABEL_5:
    *block = *(_DWORD *)(g_ClipsMemoryTable + 4 * clamped_size);
    *(_DWORD *)(g_ClipsMemoryTable + 4 * clamped_size) = block;
    return 1;
  }
  if ( clamped_size < 500 )
    goto LABEL_5;
  return Mem_ReleasePoolBlock((int)block, clamped_size);
}
// 472A0D: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472A60) --------------------------------------------------------
signed int  Mem_SmallBlockRelease(_DWORD *block, int size)
{
  int clamped_size; // ecx

  clamped_size = size;
  if ( !size )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( (unsigned int)clamped_size < 4 )
  {
    clamped_size = 4;
LABEL_5:
    *block = *(_DWORD *)(g_ClipsMemoryTable + 4 * clamped_size);
    *(_DWORD *)(g_ClipsMemoryTable + 4 * clamped_size) = block;
    return 1;
  }
  if ( clamped_size < 500 )
    goto LABEL_5;
  return Mem_ReleasePoolBlock((int)block, clamped_size);
}
// 472A6D: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472B10) --------------------------------------------------------
int Mem_GetAllocFlag()
{
  return g_Mem_AllocFlag;
}
// 519F04: using guessed type int dword_519F04;

//----- (00472B50) --------------------------------------------------------
signed int  Mem_InitPool(unsigned int requested_bytes, char a2)
{
  unsigned int request_size;
  int block_header_bytes;
  int available_size;
  int first_block;
  int tail_header;

  request_size = requested_bytes;
  g_MemPoolBlockHeaderSize = 16;
  g_HeapChunkHeaderSize = 16;
  if ( requested_bytes < 0x3E800 )
    requested_bytes = 256000;
  block_header_bytes = 2 * g_MemPoolBlockHeaderSize;
  available_size = 8 * ((g_HeapChunkHeaderSize + block_header_bytes + requested_bytes - 1) >> 3) + 8 - block_header_bytes - g_HeapChunkHeaderSize;
  if ( request_size < 0x3E800 && (unsigned int)available_size <= request_size + g_MemPoolBlockHeaderSize )
    available_size = 8 * ((g_HeapChunkHeaderSize + request_size + block_header_bytes - 1) >> 3) + 8 - block_header_bytes - g_HeapChunkHeaderSize;
  g_MemPoolListHead = nmalloc_(available_size, 0);
  if ( g_MemPoolListHead )
  {
    *(_DWORD *)g_MemPoolListHead = 0;
    *(_DWORD *)(g_MemPoolListHead + 4) = 0;
    first_block = g_MemPoolListHead + g_HeapChunkHeaderSize;
    *(_DWORD *)(g_MemPoolListHead + 8) = first_block;
    *(_DWORD *)(g_MemPoolListHead + 12) = available_size;
    tail_header = g_MemPoolListHead + g_HeapChunkHeaderSize + g_MemPoolBlockHeaderSize + available_size;
    *(_DWORD *)(tail_header + 4) = 0;
    *(_DWORD *)(tail_header + 8) = 0;
    *(_DWORD *)(tail_header + 12) = 0;
    *(_DWORD *)tail_header = first_block;
    *(_DWORD *)(first_block + 4) = 0;
    *(_DWORD *)(first_block + 8) = 0;
    *(_DWORD *)first_block = 0;
    *(_DWORD *)(first_block + 12) = available_size;
    g_Mem_PoolInitializedFlag = 1;
    return 1;
  }
  else
  {
    Output_WriteFormatted(0, 0, (int)&g_CRT_StdoutStream, (int)aUnableToAlloca, a2);
    return 0;
  }
}
// 472B50: could not find valid save-restore pair for esi
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 519F0C: using guessed type int dword_519F0C;
// 54DBB8: using guessed type int dword_54DBB8;
// 54DBBC: using guessed type int dword_54DBBC;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472CB0) --------------------------------------------------------
int  Mem_GrowPoolChain(int pool, unsigned int requested_bytes)
{
  int available_size;
  int new_pool;
  int first_block;
  int tail_header;

  if ( requested_bytes < 0x3E800 )
    requested_bytes = 256000;
  available_size = 8 * ((requested_bytes + 2 * g_MemPoolBlockHeaderSize + g_HeapChunkHeaderSize - 1) >> 3) + 8 - g_HeapChunkHeaderSize - 2 * g_MemPoolBlockHeaderSize;
  new_pool = nmalloc_(available_size, 0);
  if ( new_pool )
  {
    *(_DWORD *)new_pool = 0;
    *(_DWORD *)(new_pool + 4) = pool;
    first_block = new_pool + g_HeapChunkHeaderSize;
    *(_DWORD *)(new_pool + 12) = available_size;
    *(_DWORD *)(new_pool + 8) = first_block;
    *(_DWORD *)pool = new_pool;
    tail_header = new_pool + g_HeapChunkHeaderSize + g_MemPoolBlockHeaderSize + available_size;
    *(_DWORD *)(tail_header + 4) = 0;
    *(_DWORD *)(tail_header + 8) = 0;
    *(_DWORD *)(tail_header + 12) = 0;
    *(_DWORD *)tail_header = first_block;
    *(_DWORD *)(first_block + 4) = 0;
    *(_DWORD *)(first_block + 8) = 0;
    *(_DWORD *)first_block = 0;
    *(_DWORD *)(first_block + 12) = available_size;
    return 1;
  }
  return 0;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 54DBB8: using guessed type int dword_54DBB8;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472D70) --------------------------------------------------------
signed int  Mem_PoolAllocBlock(unsigned int size, _DWORD *error_context)
{
  _DWORD *pool;
  _DWORD *block;
  unsigned int requested_size;
  signed int result; // eax
  int callback_arg;

  if ( !g_Mem_PoolInitializedFlag )
  {
    result = Mem_InitPool(size, size);
    if ( !result )
      return result;
    IO_AddRouter((int)aBmexit, -2000, 0, 0, 0, 0, (int)Mem_HeapExitHandler);
  }
  requested_size = 8 * ((size - 1) >> 3) + 8;
  if ( g_MemPoolListHead )
  {
    pool = (_DWORD *)(uintptr_t)g_MemPoolListHead;
    while ( 1 )
    {
      block = (_DWORD *)(uintptr_t)pool[2];
      while ( block )
      {
        if ( requested_size == (unsigned int)block[3] || requested_size + g_MemPoolBlockHeaderSize < (unsigned int)block[3] )
        {
          Mem_PoolSplitBlock((int)(uintptr_t)pool, block, requested_size);
          return (int)(uintptr_t)((char *)block + g_MemPoolBlockHeaderSize);
        }
        block = (_DWORD *)(uintptr_t)block[1];
      }
      if ( !*pool )
      {
        result = Mem_GrowPoolChain((int)(uintptr_t)pool, requested_size);
        if ( !result )
          return result;
      }
      pool = (_DWORD *)(uintptr_t)*pool;
      if ( !pool )
        break;
    }
LABEL_10:
    callback_arg = (int)(uintptr_t)error_context;
    Rules_ReportSystemError(callback_arg, 2);
    IO_RunRouterExitCallbacks();
    return 0;
  }
  goto LABEL_10;
}
// 519F0C: using guessed type int dword_519F0C;
// 54DBBC: using guessed type int dword_54DBBC;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472E40) --------------------------------------------------------
int  Mem_PoolSplitBlock(int result, _DWORD *block, int alloc_size)
{
  int pool;
  int block_size;
  int previous_free;
  int next_free;
  _DWORD *tail_header;
  _DWORD *split_block;
  int prev_of_split;
  int next_of_split;

  pool = result;
  block_size = block[3];
  if ( alloc_size == block_size )
  {
    previous_free = block[2];
    block[3] = -alloc_size;
    if ( previous_free )
    {
      *(_DWORD *)(previous_free + 4) = block[1];
    }
    else
    {
      next_free = block[1];
      if ( next_free )
        *(_DWORD *)(pool + 8) = next_free;
      else
        *(_DWORD *)(pool + 8) = 0;
    }
    next_free = block[1];
    if ( next_free )
    {
      *(_DWORD *)(next_free + 8) = block[2];
    }
    block[2] = 0;
    block[1] = 0;
  }
  else
  {
    tail_header = (_DWORD *)((char *)block + g_MemPoolBlockHeaderSize + block_size);
    split_block = (_DWORD *)((char *)block + g_MemPoolBlockHeaderSize + alloc_size);
    split_block[3] = block_size - (alloc_size + g_MemPoolBlockHeaderSize);
    *split_block = block;
    split_block[1] = block[1];
    split_block[2] = block[2];
    *tail_header = split_block;
    prev_of_split = split_block[2];
    if ( prev_of_split )
      *(_DWORD *)(prev_of_split + 4) = (int)(uintptr_t)split_block;
    else
      *(_DWORD *)(pool + 8) = (int)(uintptr_t)split_block;
    next_of_split = split_block[1];
    if ( next_of_split )
      *(_DWORD *)(next_of_split + 8) = (int)(uintptr_t)split_block;
    block[2] = 0;
    block[1] = 0;
    block[3] = -alloc_size;
    result = -alloc_size;
  }
  return result;
}
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472F00) --------------------------------------------------------
signed int  Mem_PoolFreeCoalesce(int block_ptr, int block_size)
{
  unsigned int aligned_size; // ebx
  _DWORD *block_record; // edx
  int stored_size; // edi
  int next_link; // ecx
  _DWORD *chain_cursor; // eax
  int *pool_header; // eax
  _DWORD *adjacent_block; // ebx
  int freelist_head; // esi
  _DWORD *chained_block; // ecx
  int old_freelist_head; // esi
  int chained_size; // edi
  int prev_free; // ebp
  int next_free; // esi
  int adjacent_size; // ebp
  _DWORD *following_block; // ecx
  int adjacent_next; // esi
  int *unlink_node; // ecx
  int chain_next; // edx
  int pool_next; // ecx

  aligned_size = 8 * ((unsigned int)(block_size - 1) >> 3) + 8;
  block_record = (_DWORD *)(block_ptr - g_MemPoolBlockHeaderSize);
  if ( block_ptr == g_MemPoolBlockHeaderSize )
    return 0;
  stored_size = block_record[3];
  if ( stored_size >= 0 || -aligned_size != stored_size )
    return 0;
  next_link = *block_record;
  block_record[3] = aligned_size;
  chain_cursor = block_record;
  if ( next_link )
  {
    do
      chain_cursor = (_DWORD *)*chain_cursor;
    while ( *chain_cursor );
  }
  pool_header = (_DWORD *)((char *)chain_cursor - g_HeapChunkHeaderSize);
  adjacent_block = (_DWORD *)(block_ptr + aligned_size);
  freelist_head = pool_header[2];
  chained_block = (_DWORD *)*block_record;
  if ( freelist_head )
    *(_DWORD *)(freelist_head + 8) = block_record;
  old_freelist_head = pool_header[2];
  block_record[2] = 0;
  block_record[1] = old_freelist_head;
  pool_header[2] = (int)block_record;
  if ( chained_block )
  {
    chained_size = chained_block[3];
    if ( chained_size > 0 )
    {
      chained_block[3] = block_record[3] + g_MemPoolBlockHeaderSize + chained_size;
      if ( !adjacent_block )
        return 0;
      *adjacent_block = chained_block;
      prev_free = chained_block[2];
      if ( prev_free )
        *(_DWORD *)(prev_free + 4) = chained_block[1];
      if ( chained_block[1] )
        *(_DWORD *)(chained_block[1] + 8) = chained_block[2];
      next_free = block_record[1];
      chained_block[1] = next_free;
      if ( next_free )
        *(_DWORD *)(next_free + 8) = chained_block;
      chained_block[2] = 0;
      pool_header[2] = (int)chained_block;
      block_record[2] = 0;
      block_record[1] = 0;
      block_record = chained_block;
    }
  }
  if ( !adjacent_block || !block_record )
    return 0;
  adjacent_size = adjacent_block[3];
  if ( adjacent_size > 0 )
  {
    block_record[3] += adjacent_size + g_MemPoolBlockHeaderSize;
    following_block = (_DWORD *)((char *)adjacent_block + adjacent_block[3] + g_MemPoolBlockHeaderSize);
    if ( following_block )
    {
      *following_block = block_record;
      if ( adjacent_block[2] )
        *(_DWORD *)(adjacent_block[2] + 4) = adjacent_block[1];
      adjacent_next = adjacent_block[1];
      if ( adjacent_next )
        *(_DWORD *)(adjacent_next + 8) = adjacent_block[2];
      goto LABEL_27;
    }
    return 0;
  }
LABEL_27:
  if ( *block_record || block_record[3] != pool_header[3] )
    return 1;
  if ( pool_header[1] )
  {
    unlink_node = (int *)pool_header[1];
    chain_next = *pool_header;
    *unlink_node = *pool_header;
    if ( chain_next )
    {
      unlink_node = (int *)chain_next;
      *(_DWORD *)(chain_next + 4) = pool_header[1];
    }
    nfree_(unlink_node);
    return 1;
  }
  pool_next = *pool_header;
  if ( !*pool_header )
    return 1;
  *(_DWORD *)(pool_next + 4) = 0;
  g_MemPoolListHead = *pool_header;
  nfree_(pool_next);
  return 1;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 54DBB8: using guessed type int dword_54DBB8;
// 54DBBC: using guessed type int dword_54DBBC;
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00473090) --------------------------------------------------------
int __thiscall Mem_ReleaseAllPools(void *this)
{
  int result; // eax
  int next_pool;
  int freelist_next;

  (void)this;

  if ( g_MemPoolListHead )
  {
    do
    {
      next_pool = *(_DWORD *)g_MemPoolListHead;
      nfree_(g_MemPoolListHead);
      g_MemPoolListHead = next_pool;
    }
    while ( next_pool );
  }
  result = g_Mem_ReservedBlockListHead;
  g_MemPoolListHead = 0;
  if ( g_Mem_ReservedBlockListHead )
  {
    do
    {
      freelist_next = *(_DWORD *)(result + 4);
      Mem_ReleasePoolBlock(result, *(_DWORD *)(result + 8));
      result = freelist_next;
    }
    while ( freelist_next );
  }
  g_Mem_ReservedBlockListHead = 0;
  return result;
}
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 519F08: using guessed type int dword_519F08;
// 54DBBC: using guessed type int dword_54DBBC;

//----- (004730F0) --------------------------------------------------------
int __thiscall Mem_HeapExitHandler(void *this)
{
  Mem_ReleaseAllPools(this);
  return 1;
}

//----- (00473250) --------------------------------------------------------
_DWORD * Surface_Construct(_DWORD *result)
{
  result[43] = g_Surface_BlitFunctionTable;
  result[41] = 0;
  result[3] = 0;
  result[13] = 0;
  result[42] = 0;
  result[4] = -1;
  result[10] = 0;
  result[9] = 0;
  result[12] = 0;
  result[11] = 0;
  return result;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (004732A0) --------------------------------------------------------
_DWORD * Surface_ConstructWithSurface(_DWORD *surface, _DWORD *ddraw_obj, int height, int width)
{
  surface[43] = g_Surface_BlitFunctionTable;
  if ( !Surface_CreateDDSurface(surface, ddraw_obj, height, width) )
    return 0;
  return surface;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (004732E0) --------------------------------------------------------
int  Surface_Destruct(int result)
{
  int surface; // ebx
  int dd_surface; // edx

  surface = result;
  dd_surface = *(_DWORD *)(result + 164);
  *(_DWORD *)(result + 172) = g_Surface_BlitFunctionTable;
  if ( dd_surface )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)dd_surface + 8))(dd_surface);
    *(_DWORD *)(surface + 164) = 0;
    return surface;
  }
  return result;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (00473320) --------------------------------------------------------
signed int  Surface_CreateDDSurface(_DWORD *surface, _DWORD *ddraw_obj, int height, int width)
{
  HRESULT hr;
  int direct_draw_handle;

  if ( !surface )
    return 0;
  memset(surface + 14, 0, 108);
  surface[14] = 108;
  surface[15] = 7;
  surface[40] = 64;
  surface[16] = height;
  surface[17] = width;
  if ( !ddraw_obj )
    return 0;
  direct_draw_handle = *ddraw_obj;
  if ( !direct_draw_handle )
    return 0;
  hr = Compat_DirectDraw_CreateSurface(
         (LPDIRECTDRAW)(uintptr_t)(unsigned int)direct_draw_handle,
         (int *)(surface + 14),
         surface + 41);
  if ( hr )
  {
    Render_HandleDirectDrawFatalError(hr, ddraw_obj[9]);
    return 0;
  }
  surface[4] = -1;
  surface[10] = 0;
  surface[9] = 0;
  surface[6] = 0;
  surface[5] = 0;
  surface[3] = 0;
  surface[13] = 0;
  surface[2] = 0;
  surface[42] = ddraw_obj;
  surface[1] = height;
  *surface = width;
  surface[12] = surface[1];
  surface[11] = *surface;
  surface[8] = surface[1];
  surface[7] = *surface;
  return 1;
}

//----- (004733F0) --------------------------------------------------------
int  Surface_CreateFromBitmapFile(_DWORD *surface, int *ddraw_obj, const CHAR *bitmap_path)
{
  int result; // eax
  int v6; // ecx
  int surface_height; // eax

  if ( !bitmap_path )
    return 0;
  result = Surface_DDCopyBitmapToNewSurface(*ddraw_obj, bitmap_path, surface + 1, (int)surface);
  surface[41] = result;
  if ( result )
  {
    surface[3] = 0;
    surface[13] = 0;
    surface[4] = -1;
    surface[10] = 0;
    surface[9] = 0;
    surface[6] = 0;
    surface[5] = 0;
    surface_height = surface[1];
    surface[2] = bitmap_path;
    surface[12] = surface_height;
    surface[11] = *surface;
    surface[8] = surface[1];
    surface[7] = *surface;
    surface[42] = ddraw_obj;
    memset_(v6, 0);
    surface[14] = 108;
    surface[15] = 7;
    surface[40] = 64;
    surface[17] = *surface;
    surface[16] = surface[1];
    return 1;
  }
  return result;
}
// 473477: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004734B0) --------------------------------------------------------
int  Surface_BltOntoSurface(int surface, int dest_surface)
{
  int result; // eax
  int v4; // edx

  result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(dest_surface + 164) + 20))(
             *(_DWORD *)(dest_surface + 164),
             surface + 36,
             *(_DWORD *)(surface + 164),
             surface + 20,
             0x1000000,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore(surface);
    return v4;
  }
  return result;
}
// 4734EB: variable 'v4' is possibly undefined

//----- (004734F0) --------------------------------------------------------
int  Surface_BltFastOpaqueTo(int src_surface, int dest_x, int dest_surface, int dest_y)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, int, int))(**(_DWORD **)(dest_surface + 164) + 28))(
             *(_DWORD *)(dest_surface + 164),
             dest_x,
             dest_y,
             *(_DWORD *)(src_surface + 164),
             src_surface + 20,
             16);
  if ( result == -2005532222 )
  {
    Surface_Restore(src_surface);
    return -2005532222;
  }
  return result;
}

//----- (00473530) --------------------------------------------------------
int  Surface_BltFastKeyedTo(int src_surface, int dest_x, int dest_surface, int dest_y)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, int, int))(**(_DWORD **)(dest_surface + 164) + 28))(
             *(_DWORD *)(dest_surface + 164),
             dest_x,
             dest_y,
             *(_DWORD *)(src_surface + 164),
             src_surface + 20,
             17);
  if ( result == -2005532222 )
  {
    Surface_Restore(src_surface);
    return -2005532222;
  }
  return result;
}

//----- (00473570) --------------------------------------------------------
int  Surface_BltFastKeyedClippedTo(_DWORD *src_surface, int dest_x, int dest_surface, int dest_y, _DWORD *clip_bounds)
{
  int result; // eax
  int v7; // edx
  _DWORD src_rect[4]; // [esp+0h] [ebp-28h] BYREF
  int blit_x; // [esp+10h] [ebp-18h] BYREF
  int blit_y; // [esp+14h] [ebp-14h] BYREF
  int target_surface; // [esp+18h] [ebp-10h]

  blit_x = dest_x;
  blit_y = dest_y;
  target_surface = dest_surface;
  src_rect[0] = src_surface[5];
  src_rect[1] = src_surface[6];
  src_rect[2] = src_surface[7];
  src_rect[3] = src_surface[8];
  Render_ClampBlitRectToBounds(&blit_x, &blit_y, clip_bounds, src_rect);
  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, _DWORD *, int))(**(_DWORD **)(target_surface + 164) + 28))(
             *(_DWORD *)(target_surface + 164),
             blit_x,
             blit_y,
             src_surface[41],
             src_rect,
             17);
  if ( result == -2005532222 )
  {
    Surface_Restore((int)src_surface);
    return v7;
  }
  return result;
}
// 473570: could not find valid save-restore pair for ebx
// 4735E3: variable 'v7' is possibly undefined

//----- (004735F0) --------------------------------------------------------
int  Surface_BltToWindowClient(int surface, int dest_surface)
{
  int result; // eax
  struct tagRECT client_rect[2]; // [esp+0h] [ebp-24h] BYREF

  GetClientRect(*(HWND *)(*(_DWORD *)(surface + 168) + 36), client_rect);
  ClientToScreen(*(HWND *)(*(_DWORD *)(surface + 168) + 36), (LPPOINT)client_rect);
  ClientToScreen(*(HWND *)(*(_DWORD *)(surface + 168) + 36), (LPPOINT)&client_rect[0].right);
  result = (*(int (__stdcall **)(_DWORD, struct tagRECT *, _DWORD, _DWORD, int, _DWORD))(**(_DWORD **)(dest_surface + 164) + 20))(
             *(_DWORD *)(dest_surface + 164),
             client_rect,
             *(_DWORD *)(surface + 164),
             0,
             0x1000000,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore(surface);
    return -2005532222;
  }
  return result;
}

//----- (00473690) --------------------------------------------------------
int  Surface_BltScaledKeyedOnto(_DWORD *src_surface, int dest_top, int a3, float scale, int dest_surface)
{
  int height; // ecx
  double scaled_bottom; // st6
  int *v8; // eax
  int width; // ebx
  int v10; // edx
  double scaled_right; // st7
  int v12; // eax
  int result; // eax
  int v14; // edx
  int v15; // [esp+4h] [ebp-Ch]

  height = src_surface[1];
  src_surface[10] = dest_top;
  scaled_bottom = (double)(height + dest_top) * scale;
  _CHP(height + dest_top, a3);
  v8[12] = (int)scaled_bottom;
  width = *v8;
  v8[9] = v10;
  scaled_right = scale * (double)(width + v10);
  _CHP(width + v10, v15);
  *(_DWORD *)(v12 + 44) = (int)scaled_right;
  result = (*(int (__stdcall **)(_DWORD, _DWORD *, _DWORD, _DWORD *, int, _DWORD))(**(_DWORD **)(dest_surface + 164) + 20))(
             *(_DWORD *)(dest_surface + 164),
             src_surface + 9,
             src_surface[41],
             src_surface + 5,
             16809984,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore((int)src_surface);
    return v14;
  }
  return result;
}
// 4736B1: variable 'v8' is possibly undefined
// 4736B6: variable 'v10' is possibly undefined
// 4736C3: variable 'v15' is possibly undefined
// 4736C8: variable 'v12' is possibly undefined
// 47370C: variable 'v14' is possibly undefined

//----- (00473730) --------------------------------------------------------
int  Surface_BltMirrorLeftRight(int surface)
{
  _DWORD blt_fx[25]; // [esp+0h] [ebp-64h] BYREF

  blt_fx[0] = 100;
  blt_fx[1] = 2;
  return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int, _DWORD *))(**(_DWORD **)(surface + 164) + 20))(
           *(_DWORD *)(surface + 164),
           0,
           0,
           0,
           16779264,
           blt_fx);
}

//----- (00473770) --------------------------------------------------------
int  Surface_BltMirrorUpDown(int surface)
{
  _DWORD blt_fx[25]; // [esp+0h] [ebp-64h] BYREF

  blt_fx[0] = 100;
  blt_fx[1] = 4;
  return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int, _DWORD *))(**(_DWORD **)(surface + 164) + 20))(
           *(_DWORD *)(surface + 164),
           0,
           0,
           0,
           16779264,
           blt_fx);
}

//----- (004737B0) --------------------------------------------------------
_DWORD * Surface_SetDestRect(_DWORD *result, int top, int bottom, int left, int right)
{
  result[10] = top;
  result[9] = left;
  result[12] = bottom;
  result[11] = right;
  return result;
}

//----- (004737D0) --------------------------------------------------------
_DWORD * Surface_SetSrcRect(_DWORD *result, int top, int bottom, int left, int right)
{
  result[6] = top;
  result[5] = left;
  result[8] = bottom;
  result[7] = right;
  return result;
}

//----- (004737F0) --------------------------------------------------------
int  Surface_SetSrcColorKey(int surface, int color_key, int a3)
{
  _DWORD color_key_struct[3]; // [esp+0h] [ebp-Ch] BYREF

  color_key_struct[2] = a3;
  *(_DWORD *)(surface + 16) = color_key;
  color_key_struct[0] = color_key;
  color_key_struct[1] = color_key;
  return (*(int (__stdcall **)(_DWORD, int, _DWORD *))(**(_DWORD **)(surface + 164) + 116))(*(_DWORD *)(surface + 164), 8, color_key_struct);
}

//----- (00473820) --------------------------------------------------------
int  Surface_Restore(int surface)
{
  return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(surface + 164) + 108))(*(_DWORD *)(surface + 164));
}

//----- (00473840) --------------------------------------------------------
int  Surface_LockWithRestore(int surface, int a2)
{
  int surface_desc; // edi
  int dd_surface; // eax
  int result; // eax

  surface_desc = surface + 56;
  memset_(a2, 0);
  dd_surface = *(_DWORD *)(surface + 164);
  *(_DWORD *)(surface + 56) = 108;
  result = (*(int (__stdcall **)(int, _DWORD, int, int, _DWORD))(*(_DWORD *)dd_surface + 100))(dd_surface, 0, surface_desc, 1, 0);
  if ( result == -2005532222 )
  {
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(surface + 164) + 108))(*(_DWORD *)(surface + 164));
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int, _DWORD))(**(_DWORD **)(surface + 164) + 100))(
      *(_DWORD *)(surface + 164),
      0,
      surface_desc,
      1,
      0);
    return -2005532222;
  }
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004738B0) --------------------------------------------------------
int  Surface_Unlock(int surface)
{
  return (*(int (__stdcall **)(_DWORD, int))(**(_DWORD **)(surface + 164) + 128))(*(_DWORD *)(surface + 164), surface + 56);
}

//----- (004739C0) --------------------------------------------------------
int  Surface_SetPixelByte(int result, int x, char color, int y)
{
  *(_BYTE *)(*(_DWORD *)(result + 72) * y + x + *(_DWORD *)(result + 92)) = color;
  return result;
}

//----- (004739D0) --------------------------------------------------------
int  Surface_GetPixelByte(int surface, int x, int y)
{
  return *(unsigned __int8 *)(*(_DWORD *)(surface + 92) + *(_DWORD *)(surface + 72) * y + x);
}

//----- (004739F0) --------------------------------------------------------
int * Mem_SwapDwordPair(int *result, int *other)
{
  int temp; // ebx

  temp = *result;
  *result = *other;
  *other = temp;
  return result;
}

//----- (00473A00) --------------------------------------------------------
int  Surface_DrawRectBorderByte(int surface, int left, int right, int top, int bottom, char color)
{
  int i; // ebp
  int j; // ebp

  for ( i = left; i < right; ++i )
  {
    Surface_SetPixelByte(surface, i, color, top);
    Surface_SetPixelByte(surface, i, color, bottom);
  }
  for ( j = top; j < bottom; ++j )
  {
    Surface_SetPixelByte(surface, left, color, j);
    Surface_SetPixelByte(surface, right, color, j);
  }
  Surface_SetPixelByte(surface, left, color, top);
  return Surface_SetPixelByte(surface, right, color, bottom);
}

//----- (00473AB0) --------------------------------------------------------
int  Surface_FillRectColor(int surface, int left, int right, int top, int bottom, int fill_color)
{
  _DWORD blt_fx[25]; // [esp+0h] [ebp-7Ch] BYREF
  _DWORD dest_rect[6]; // [esp+64h] [ebp-18h] BYREF

  dest_rect[0] = left;
  dest_rect[3] = bottom;
  blt_fx[0] = 100;
  blt_fx[20] = fill_color;
  dest_rect[1] = top;
  dest_rect[2] = right;
  return (*(int (__stdcall **)(_DWORD, _DWORD *, _DWORD, _DWORD, int, _DWORD *))(**(_DWORD **)(surface + 164) + 20))(
           *(_DWORD *)(surface + 164),
           dest_rect,
           0,
           0,
           16778240,
           blt_fx);
}

//----- (00473B10) --------------------------------------------------------
int  Render_DrawLine(int surface, int x0, int x1, int y0, int y1, char color)
{
  char color_byte; // bp
  signed int delta_x; // esi
  signed int delta_y; // eax
  int result; // eax
  int cur_x; // esi
  int cur_y; // esi
  int v13; // [esp+0h] [ebp-3Ch]
  double x_step; // [esp+0h] [ebp-3Ch]
  int v15; // [esp+4h] [ebp-38h]
  double y_step; // [esp+8h] [ebp-34h]
  double j; // [esp+10h] [ebp-2Ch]
  double i; // [esp+18h] [ebp-24h]
  int x_start; // [esp+20h] [ebp-1Ch] BYREF
  int y_start; // [esp+24h] [ebp-18h] BYREF
  int x_end; // [esp+28h] [ebp-14h] BYREF
  int last_plot; // [esp+2Ch] [ebp-10h]

  color_byte = color;
  x_start = x0;
  y_start = y0;
  x_end = x1;
  delta_x = abs32(x1 - x0);
  delta_y = abs32(y1 - y0);
  if ( !delta_x )
    return Render_DrawVerticalRun(surface, y_start, x_start, y1, color);
  if ( !delta_y )
    return Render_DrawHorizontalRun(surface, x_start, y_start, x_end, color);
  if ( delta_x <= delta_y )
  {
    if ( y_start > y1 )
    {
      Mem_SwapDwordPair(&x_start, &x_end);
      Mem_SwapDwordPair(&y_start, &y1);
    }
    result = y1 - y_start;
    x_step = (double)(x_end - x_start) / (double)(y1 - y_start);
    last_plot = x_start;
    cur_y = y_start;
    for ( i = (double)x_start; cur_y <= y1; i = i + x_step )
    {
      _CHP(LODWORD(x_step), HIDWORD(x_step));
      last_plot = (int)i;
      result = Surface_SetPixelByte(surface, (int)i, color_byte, cur_y++);
    }
  }
  else
  {
    if ( x_start > x_end )
    {
      Mem_SwapDwordPair(&x_start, &x_end);
      Mem_SwapDwordPair(&y_start, &y1);
    }
    result = x_end - x_start;
    y_step = (double)(y1 - y_start) / (double)(x_end - x_start);
    last_plot = y_start;
    cur_x = x_start;
    for ( j = (double)y_start; cur_x <= x_end; j = j + y_step )
    {
      _CHP(v13, v15);
      last_plot = (int)j;
      Surface_SetPixelByte(surface, cur_x++, color_byte, (int)j);
      result = x_end;
    }
  }
  return result;
}
// 473BC2: variable 'v13' is possibly undefined
// 473BC2: variable 'v15' is possibly undefined
// 473C9E: variable 'v14' is possibly undefined

//----- (00473CE0) --------------------------------------------------------
int  Render_DrawVerticalRun(int surface, int y_start, int x, int y_end, char color)
{
  int pixels_base; // ebp
  int result; // eax
  int row_offset; // edx

  pixels_base = *(_DWORD *)(surface + 92);
  for ( result = y_start; result < y_end; *(_BYTE *)(row_offset + pixels_base) = color )
  {
    row_offset = x + result * *(_DWORD *)(surface + 72);
    ++result;
  }
  return result;
}

//----- (00473D20) --------------------------------------------------------
int  Render_DrawHorizontalRun(int result, int x_start, int y, int x_end, char color)
{
  int surface; // edi
  int i; // esi

  surface = result;
  for ( i = x_start; i < x_end; ++i )
    result = Surface_SetPixelByte(surface, i, color, y);
  return result;
}
// 473D20: could not find valid save-restore pair for ebx

//----- (00473E30) --------------------------------------------------------
int  Render_FillSurfaceSolidColor(int surface, int fill_color, int a3)
{
  _DWORD blt_fx[26]; // [esp+0h] [ebp-68h] BYREF

  blt_fx[25] = a3;
  blt_fx[20] = fill_color;
  blt_fx[0] = 100;
  return Compat_DirectDrawSurface_Blt(
           (LPDIRECTDRAWSURFACE)*(int *)(surface + 164),
           0,
           0,
           0,
           16778240,
           blt_fx);
}

//----- (00473E60) --------------------------------------------------------
int  Render_ClampBlitRectToBounds(_DWORD *x_ptr, _DWORD *y_ptr, _DWORD *bounds_rect, _DWORD *src_rect)
{
  int bounds_right; // edi
  int right_edge; // esi
  int bounds_top; // esi
  int bounds_bottom; // ebp
  int result; // eax

  bounds_right = bounds_rect[2];
  right_edge = *x_ptr + src_rect[2] - *src_rect;
  if ( right_edge > bounds_right )
    src_rect[2] -= right_edge - bounds_right;
  if ( *x_ptr < *bounds_rect )
  {
    *src_rect += *bounds_rect - *x_ptr;
    *x_ptr = *bounds_rect;
  }
  bounds_top = bounds_rect[1];
  if ( *y_ptr < bounds_top )
  {
    src_rect[1] += bounds_top - *y_ptr;
    *y_ptr = bounds_rect[1];
  }
  bounds_bottom = bounds_rect[3];
  result = *y_ptr + src_rect[3] - src_rect[1];
  if ( result > bounds_bottom )
  {
    result -= bounds_bottom;
    src_rect[3] -= result;
  }
  return result;
}

//----- (00473EE0) --------------------------------------------------------
int __fastcall Compat_FileSystemQueryRelease(int a1, int *handle_ptr)
{
  int object_handle;
  int result;
  uintptr_t *vtable;

  (void)a1;
  if ( !handle_ptr )
    return 0;
  object_handle = *handle_ptr;
  if ( !object_handle )
  {
    *handle_ptr = 0;
    return 0;
  }
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)object_handle;
  result = ((int (*)(int, int))(uintptr_t)vtable[3])(object_handle, 2);
  *handle_ptr = 0;
  return result;
}

//----- (00473F10) --------------------------------------------------------
int  FileSystem_OpenViaOpenSlotAndNotify(int entry)
{
  int result; // eax
  int v3; // ecx

  result = (*(int (__thiscall **)(int))(*(_DWORD *)entry + 12))(entry);
  if ( result )
  {
    (*(void (__cdecl **)(int))(*(_DWORD *)v3 + 20))(result);
    return 1;
  }
  return result;
}
// 473F30: variable 'v3' is possibly undefined

//----- (00473F50) --------------------------------------------------------
int Compat_NoOpQueryCallback()
{
  return 0;
}

static _DWORD *Compat_FileSystemQueryOpen(int file_system, int mode_flags)
{
  uintptr_t *vtable;
  char query_mode;

  if ( !file_system )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)file_system;
  if ( !vtable )
    return 0;
  query_mode = (char)(mode_flags | 4);
  if ( vtable[0] == (uintptr_t)Compat_FileFinderCreate
    && vtable[1] == (uintptr_t)Compat_FileSystemCloseQuery )
  {
    if ( vtable[2] == (uintptr_t)FileSystem_DiskMountScalarDeletingDtor
      || vtable[2] == (uintptr_t)FileSystem_DiskMountVariantScalarDeletingDtor )
      return (_DWORD *)FileSystem_DiskMountOpenFileQuery(file_system, query_mode, 0);
  }
  return File_OpenMountRootEntry(file_system, query_mode, 0);
}

static int Compat_FileSystemQueryResultIsReady(_DWORD *opened_query)
{
  uintptr_t *vtable;

  if ( !opened_query )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)opened_query;
  if ( !vtable )
    return 0;
  if ( vtable[0] == (uintptr_t)Compat_FileStreamSeekFromStart
    && vtable[1] == (uintptr_t)Compat_FileStreamTell
    && vtable[2] == (uintptr_t)Compat_FileStreamSeekFromEnd )
    return Compat_FileStreamIsReady((int)opened_query);
  if ( vtable[0] == (uintptr_t)Compat_QuerySkipBytes
    && vtable[1] == (uintptr_t)Compat_QueryGetLength
    && vtable[2] == (uintptr_t)Compat_QuerySkipBytesFromBase )
    return FileSystem_ArchiveStreamHasRemainingData((int)opened_query);
  return 0;
}

static void Compat_FileSystemQueryResultRelease(_DWORD *opened_query)
{
  uintptr_t *vtable;

  if ( !opened_query )
    return;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)opened_query;
  if ( !vtable )
    return;
  if ( vtable[0] == (uintptr_t)Compat_FileStreamSeekFromStart
    && vtable[1] == (uintptr_t)Compat_FileStreamTell
    && vtable[2] == (uintptr_t)Compat_FileStreamSeekFromEnd )
  {
    Compat_FileStreamRelease(opened_query, 2);
    return;
  }
  if ( vtable[0] == (uintptr_t)Compat_QuerySkipBytes
    && vtable[1] == (uintptr_t)Compat_QueryGetLength
    && vtable[2] == (uintptr_t)Compat_QuerySkipBytesFromBase )
    Compat_QueryDestruct((int)opened_query, 2);
}

static int Compat_FileSystemOnMounted(int mounted_file_system, int *root_file_system)
{
  uintptr_t *vtable;

  if ( !mounted_file_system )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)mounted_file_system;
  if ( !vtable )
    return 0;
  if ( vtable[0] == (uintptr_t)Compat_FileFinderCreate
    && vtable[1] == (uintptr_t)Compat_FileSystemCloseQuery )
  {
    if ( vtable[2] == (uintptr_t)FileSystem_DiskMountScalarDeletingDtor )
      return FileSystem_DiskMountResolveRegisteredRootPath(mounted_file_system, (int)root_file_system);
    if ( vtable[2] == (uintptr_t)FileSystem_DiskMountVariantScalarDeletingDtor )
      return FileSystem_DiskMountRegisterNestedMount(mounted_file_system, root_file_system, 0, 0);
  }
  if ( vtable[0] == (uintptr_t)File_CacheNodeNewValidated
    && vtable[1] == (uintptr_t)Compat_FileSystemCloseQuery )
  {
    if ( vtable[2] == (uintptr_t)Compat_QueryCloseAndDestruct )
      return (int)(uintptr_t)File_OpenMountRootEntry(mounted_file_system, 0, 0);
  }
  return 0;
}

//----- (00473F70) --------------------------------------------------------
int  Compat_FileSystemOpenIfReady(int file_system, int mode_flags)
{
  _DWORD *opened_query; // ecx

  opened_query = Compat_FileSystemQueryOpen(file_system, mode_flags);
  if ( opened_query && Compat_FileSystemQueryResultIsReady(opened_query) == 1 )
    return (int)opened_query;
  if ( opened_query )
    Compat_FileSystemQueryResultRelease(opened_query);
  return 0;
}
// 473F9E: variable 'v3' is possibly undefined

//----- (004741F0) --------------------------------------------------------
void  __noreturn Render_HandleDirectDrawFatalError(unsigned int error_code, int a2)
{
  const char *error_name; // eax
  char message_buffer[256]; // [esp+0h] [ebp-104h] BYREF
  int saved_context; // [esp+100h] [ebp-4h]

  saved_context = a2;
  if ( error_code >= 0x8876019A )
  {
    if ( error_code <= 0x8876019A )
    {
      error_name = aDderr_surfacea;
      goto LABEL_10;
    }
    if ( error_code >= 0x8876023B )
    {
      if ( error_code <= 0x8876023B )
      {
        error_name = aDderr_hwndalre;
        goto LABEL_10;
      }
      if ( error_code < 0x88760248 )
      {
        if ( error_code >= 0x88760241 )
        {
          if ( error_code <= 0x88760241 )
          {
            error_name = aDderr_overlayn;
          }
          else if ( error_code >= 0x88760244 )
          {
            if ( error_code <= 0x88760244 )
            {
              error_name = aDderr_notaover;
            }
            else if ( error_code < 0x88760246 )
            {
              error_name = aDderr_exclusiv;
            }
            else if ( error_code <= 0x88760246 )
            {
              error_name = aDderr_notflipp;
            }
            else
            {
              error_name = aDderr_cantdupl;
            }
          }
          else if ( error_code <= 0x88760242 )
          {
            error_name = aDderr_nooverla;
          }
          else
          {
            error_name = aDderr_invalidp;
          }
        }
        else if ( error_code >= 0x8876023E )
        {
          if ( error_code <= 0x8876023E )
          {
            error_name = aDderr_bltfastc;
          }
          else if ( error_code <= 0x8876023F )
          {
            error_name = aDderr_noblthw;
          }
          else
          {
            error_name = aDderr_noddrops;
          }
        }
        else if ( error_code <= 0x8876023C )
        {
          error_name = aDderr_nopalett;
        }
        else
        {
          error_name = aDderr_nopale_0;
        }
        goto LABEL_10;
      }
      if ( error_code <= 0x88760248 )
      {
        error_name = aDderr_notlocke;
        goto LABEL_10;
      }
      if ( error_code < 0x8876024E )
      {
        if ( error_code >= 0x8876024B )
        {
          if ( error_code <= 0x8876024B )
          {
            sprintf_(message_buffer, aDderr_wrongmod);
          }
          else if ( error_code <= 0x8876024C )
          {
            sprintf_(message_buffer, aDderr_implicit);
          }
          else
          {
            sprintf_(message_buffer, aDderr_notpalet);
          }
        }
        else
        {
          if ( error_code <= 0x88760249 )
          {
            error_name = aDderr_cantcrea;
            goto LABEL_10;
          }
          sprintf_(message_buffer, aDderr_nodc);
        }
LABEL_11:
        sprintf_(&g_DirectDrawErrorMessageBuffer, "DirectDraw Error %s", message_buffer);
        App_RequestQuit((int)aDirectdrawEr_0);
      }
      if ( error_code <= 0x8876024E )
      {
        sprintf_(message_buffer, aDderr_unsupp_0);
        goto LABEL_11;
      }
      if ( error_code >= 0x8876026C )
      {
        if ( error_code <= 0x8876026C )
        {
          sprintf_(message_buffer, aDderr_dcalread);
          goto LABEL_11;
        }
        if ( error_code >= 0x88760294 )
        {
          if ( error_code <= 0x88760294 )
          {
            sprintf_(message_buffer, aDderr_cantpa_0);
            goto LABEL_11;
          }
          if ( error_code == -2005531992 )
          {
            sprintf_(message_buffer, aDderr_notpagel);
            goto LABEL_11;
          }
        }
        else if ( error_code == -2005532032 )
        {
          sprintf_(message_buffer, aDderr_cantpage);
          goto LABEL_11;
        }
      }
      else
      {
        if ( error_code <= 0x8876024F )
        {
          sprintf_(message_buffer, aDderr_nomipmap);
          goto LABEL_11;
        }
        if ( error_code == -2005532080 )
        {
          sprintf_(message_buffer, aDderr_invalids);
          goto LABEL_11;
        }
      }
    }
    else if ( error_code >= 0x88760219 )
    {
      if ( error_code <= 0x88760219 )
      {
        error_name = aDderr_vertical;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760234 )
      {
        if ( error_code <= 0x88760234 )
        {
          error_name = aDderr_primarys;
        }
        else if ( error_code >= 0x88760237 )
        {
          if ( error_code <= 0x88760237 )
          {
            error_name = aDderr_clipperi;
          }
          else if ( error_code < 0x88760239 )
          {
            error_name = aDderr_noclippe;
          }
          else if ( error_code <= 0x88760239 )
          {
            error_name = aDderr_nohwnd;
          }
          else
          {
            error_name = aDderr_hwndsubc;
          }
        }
        else if ( error_code <= 0x88760235 )
        {
          error_name = aDderr_noemulat;
        }
        else
        {
          error_name = aDderr_regionto;
        }
        goto LABEL_10;
      }
      if ( error_code >= 0x88760231 )
      {
        if ( error_code <= 0x88760231 )
        {
          error_name = aDderr_invalidd;
        }
        else if ( error_code <= 0x88760232 )
        {
          error_name = aDderr_directdr;
        }
        else
        {
          error_name = aDderr_nodirect;
        }
        goto LABEL_10;
      }
      if ( error_code >= 0x8876021C )
      {
        if ( error_code <= 0x8876021C )
        {
          error_name = aDderr_wasstill;
          goto LABEL_10;
        }
        if ( error_code == -2005532112 )
        {
          error_name = aDderr_xalign;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887601CC )
    {
      if ( error_code <= 0x887601CC )
      {
        error_name = aDderr_surfacen;
        goto LABEL_10;
      }
      if ( error_code >= 0x887601EA )
      {
        if ( error_code <= 0x887601EA )
        {
          error_name = aDderr_toobigwi;
          goto LABEL_10;
        }
        if ( error_code >= 0x887601FE )
        {
          if ( error_code <= 0x887601FE )
          {
            error_name = aDderr_unsupp_1;
            goto LABEL_10;
          }
          if ( error_code == -2005532152 )
          {
            error_name = aDderr_unsupp_2;
            goto LABEL_10;
          }
        }
      }
      else if ( error_code >= 0x887601D6 )
      {
        if ( error_code <= 0x887601D6 )
        {
          error_name = aDderr_toobighe;
          goto LABEL_10;
        }
        if ( error_code == -2005532192 )
        {
          error_name = aDderr_toobigsi;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887601B3 )
    {
      if ( error_code <= 0x887601B3 )
      {
        error_name = aDderr_cantlock;
        goto LABEL_10;
      }
      if ( error_code >= 0x887601B8 )
      {
        if ( error_code <= 0x887601B8 )
        {
          error_name = aDderr_surfacei;
          goto LABEL_10;
        }
        if ( error_code == -2005532222 )
        {
          error_name = aDderr_surfacel;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887601A4 )
    {
      if ( error_code <= 0x887601A4 )
      {
        error_name = aDderr_surfac_0;
        goto LABEL_10;
      }
      if ( error_code == -2005532242 )
      {
        error_name = aDderr_surfaceb;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x887600D7 )
  {
    if ( error_code <= 0x887600D7 )
    {
      error_name = aDderr_nocolork;
      goto LABEL_10;
    }
    if ( error_code >= 0x8876013C )
    {
      if ( error_code <= 0x8876013C )
      {
        error_name = aDderr_not4bitc;
        goto LABEL_10;
      }
      if ( error_code >= 0x8876015E )
      {
        if ( error_code <= 0x8876015E )
        {
          error_name = aDderr_nozoverl;
          goto LABEL_10;
        }
        if ( error_code >= 0x8876017E )
        {
          if ( error_code <= 0x8876017E )
          {
            error_name = aDderr_overlayc;
            goto LABEL_10;
          }
          if ( error_code >= 0x88760183 )
          {
            if ( error_code <= 0x88760183 )
            {
              error_name = aDderr_paletteb;
              goto LABEL_10;
            }
            if ( error_code == -2005532272 )
            {
              error_name = aDderr_colorkey;
              goto LABEL_10;
            }
          }
          else if ( error_code == -2005532288 )
          {
            error_name = aDderr_overla_0;
            goto LABEL_10;
          }
        }
        else if ( error_code >= 0x88760168 )
        {
          if ( error_code <= 0x88760168 )
          {
            error_name = aDderr_outofcap;
            goto LABEL_10;
          }
          if ( error_code == -2005532292 )
          {
            error_name = aDderr_outofvid;
            goto LABEL_10;
          }
        }
      }
      else if ( error_code >= 0x8876014A )
      {
        if ( error_code <= 0x8876014A )
        {
          error_name = aDderr_notextur;
          goto LABEL_10;
        }
        if ( error_code >= 0x8876014F )
        {
          if ( error_code <= 0x8876014F )
          {
            error_name = aDderr_novsynch;
            goto LABEL_10;
          }
          if ( error_code == -2005532332 )
          {
            error_name = aDderr_nozbuffe;
            goto LABEL_10;
          }
        }
      }
      else
      {
        if ( error_code <= 0x8876013D )
        {
          error_name = aDderr_not4bi_0;
          goto LABEL_10;
        }
        if ( error_code == -2005532352 )
        {
          error_name = aDderr_not8bitc;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887600FA )
    {
      if ( error_code <= 0x887600FA )
      {
        error_name = aDderr_nomirror;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760118 )
      {
        if ( error_code <= 0x88760118 )
        {
          error_name = aDderr_noraster;
          goto LABEL_10;
        }
        if ( error_code >= 0x88760122 )
        {
          if ( error_code <= 0x88760122 )
          {
            error_name = aDderr_norotati;
            goto LABEL_10;
          }
          if ( error_code == -2005532362 )
          {
            error_name = aDderr_nostretc;
            goto LABEL_10;
          }
        }
      }
      else if ( error_code >= 0x887600FF )
      {
        if ( error_code <= 0x887600FF )
        {
          error_name = aDderr_notfound;
          goto LABEL_10;
        }
        if ( error_code == -2005532412 )
        {
          error_name = aDderr_noover_0;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887600E1 )
    {
      if ( error_code <= 0x887600E1 )
      {
        error_name = aDderr_noexclus;
        goto LABEL_10;
      }
      if ( error_code >= 0x887600E6 )
      {
        if ( error_code <= 0x887600E6 )
        {
          error_name = aDderr_nofliphw;
          goto LABEL_10;
        }
        if ( error_code == -2005532432 )
        {
          error_name = aDderr_nogdi;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x887600DC )
    {
      if ( error_code <= 0x887600DC )
      {
        error_name = aDderr_nocolo_0;
        goto LABEL_10;
      }
      if ( error_code == -2005532450 )
      {
        error_name = aDderr_nodire_0;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x8876005F )
  {
    if ( error_code <= 0x8876005F )
    {
      error_name = aDderr_incompat;
      goto LABEL_10;
    }
    if ( error_code >= 0x88760096 )
    {
      if ( error_code <= 0x88760096 )
      {
        error_name = aDderr_invalidr;
        goto LABEL_10;
      }
      if ( error_code >= 0x887600B4 )
      {
        if ( error_code <= 0x887600B4 )
        {
          error_name = aDderr_noalphah;
          goto LABEL_10;
        }
        if ( error_code >= 0x887600D2 )
        {
          if ( error_code <= 0x887600D2 )
          {
            error_name = aDderr_nocolorc;
            goto LABEL_10;
          }
          if ( error_code == -2005532460 )
          {
            error_name = aDderr_nocooper;
            goto LABEL_10;
          }
        }
        else if ( error_code == -2005532467 )
        {
          error_name = aDderr_noclipli;
          goto LABEL_10;
        }
      }
      else if ( error_code >= 0x887600A0 )
      {
        if ( error_code <= 0x887600A0 )
        {
          error_name = aDderr_lockedsu;
          goto LABEL_10;
        }
        if ( error_code == -2005532502 )
        {
          error_name = aDderr_no3d;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x88760078 )
    {
      if ( error_code <= 0x88760078 )
      {
        error_name = aDderr_invalidm;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760082 )
      {
        if ( error_code <= 0x88760082 )
        {
          error_name = aDderr_invalido;
          goto LABEL_10;
        }
        if ( error_code == -2005532527 )
        {
          error_name = aDderr_invali_1;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x88760064 )
    {
      if ( error_code <= 0x88760064 )
      {
        error_name = aDderr_invalidc;
        goto LABEL_10;
      }
      if ( error_code == -2005532562 )
      {
        error_name = aDderr_invali_0;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x88760005 )
  {
    if ( error_code <= 0x88760005 )
    {
      error_name = aDderr_alreadyi;
      goto LABEL_10;
    }
    if ( error_code >= 0x88760028 )
    {
      if ( error_code <= 0x88760028 )
      {
        error_name = aDderr_currentl;
        goto LABEL_10;
      }
      if ( error_code >= 0x88760037 )
      {
        if ( error_code <= 0x88760037 )
        {
          error_name = aDderr_exceptio;
          goto LABEL_10;
        }
        if ( error_code == -2005532582 )
        {
          error_name = aDderr_heightal;
          goto LABEL_10;
        }
      }
    }
    else if ( error_code >= 0x8876000A )
    {
      if ( error_code <= 0x8876000A )
      {
        error_name = aDderr_cannotat;
        goto LABEL_10;
      }
      if ( error_code == -2005532652 )
      {
        error_name = aDderr_cannotde;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x800401F0 )
  {
    if ( error_code <= 0x800401F0 )
    {
      error_name = aDderr_notiniti;
      goto LABEL_10;
    }
    if ( error_code >= 0x8007000E )
    {
      if ( error_code <= 0x8007000E )
      {
        error_name = aDderr_outofmem;
        goto LABEL_10;
      }
      if ( error_code == -2147024809 )
      {
        error_name = aDderr_invali_2;
        goto LABEL_10;
      }
    }
  }
  else if ( error_code >= 0x80004001 )
  {
    if ( error_code <= 0x80004001 )
    {
      error_name = aDderr_unsuppor;
      goto LABEL_10;
    }
    if ( error_code == -2147467259 )
    {
      error_name = aDderr_generic;
LABEL_10:
      sprintf_(message_buffer, error_name);
      goto LABEL_11;
    }
  }
  sprintf_(message_buffer, aUnknownError);
  goto LABEL_11;
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00474D60) --------------------------------------------------------
_DWORD * Render_ZeroDirectDrawObjectFields(_DWORD *result)
{
  *result = 0;
  result[1] = 0;
  result[2] = 0;
  result[4] = 0;
  result[5] = 0;
  result[3] = 0;
  return result;
}

//----- (00474DE0) --------------------------------------------------------
_DWORD * Render_DestroyDirectDrawObject(_DWORD *dd_object)
{
  int back_surface; // eax
  int primary_surface; // eax
  int v4; // ecx
  int clipper; // esi
  int v6; // edi

  if ( *dd_object )
    Compat_InvokeNativeComMethod0(*dd_object, 76);
  back_surface = dd_object[2];
  if ( back_surface )
  {
    Surface_Destruct(back_surface);
    j__nfree_();
  }
  primary_surface = dd_object[1];
  if ( primary_surface )
  {
    Surface_Destruct(primary_surface);
    j__nfree_();
  }
  v4 = dd_object[3];
  if ( v4 )
  {
    Compat_InvokeNativeComMethod0(v4, 8);
    dd_object[3] = 0;
  }
  clipper = dd_object[5];
  if ( clipper )
  {
    Compat_InvokeNativeComMethod0(clipper, 8);
    dd_object[5] = 0;
  }
  v6 = dd_object[4];
  if ( v6 )
  {
    Compat_InvokeNativeComMethod0(v6, 8);
    dd_object[4] = 0;
  }
  if ( *dd_object )
  {
    Compat_InvokeNativeComMethod0(*dd_object, 8);
    *dd_object = 0;
  }
  return dd_object;
}

//----- (00474E80) --------------------------------------------------------
signed int  Render_InitDirectDrawWindowedMode(LPVOID *dd_context, void *hwnd, void *height, DWORD width, int create_back_surface)
{
  HDC DC; // ebx
  HRESULT dd_create_hr; // eax
  int v10; // ecx
  unsigned int query_hr; // eax
  int v12; // ecx
  unsigned int coop_hr; // eax
  int v14; // ecx
  _DWORD *primary_surface_obj; // eax
  unsigned int create_primary_hr; // eax
  int v17; // ecx
  _DWORD *back_surface_obj; // eax
  unsigned int create_back_hr; // eax
  int v20; // ecx
  unsigned int create_clipper_hr; // eax
  int v22; // ecx
  unsigned int clipper_hwnd_hr; // eax
  int v24; // ecx
  unsigned int set_clipper_hr; // eax
  int v26; // ecx
  int surface_desc; // [esp+2Ch] [ebp-84h] BYREF
  int surface_flags; // [esp+30h] [ebp-80h]
  int desc_height; // [esp+34h] [ebp-7Ch]
  DWORD desc_width; // [esp+38h] [ebp-78h]
  int surface_caps; // [esp+94h] [ebp-1Ch]
  LPDIRECTDRAW lpDD; // [esp+98h] [ebp-18h] BYREF
  int DeviceCaps; // [esp+9Ch] [ebp-14h]
  int saved_height; // [esp+A0h] [ebp-10h]

  saved_height = (int)height;
  *dd_context = 0;
  dd_context[10] = 0;
  dd_context[4] = 0;
  dd_context[6] = (LPVOID)width;
  dd_context[7] = height;
  dd_context[9] = hwnd;
  DC = GetDC(0);
  DeviceCaps = GetDeviceCaps(DC, 14);
  dd_context[8] = (LPVOID)(GetDeviceCaps(DC, 12) * DeviceCaps);
  ReleaseDC(0, DC);
  dd_create_hr = DirectDrawCreate(0, &lpDD, 0);
  if ( dd_create_hr )
    Render_HandleDirectDrawFatalError(dd_create_hr, v10);
  query_hr = lpDD->lpVtbl->QueryInterface(lpDD, &stru_51CA08, dd_context);
  if ( query_hr )
    Render_HandleDirectDrawFatalError(query_hr, v12);
  if ( lpDD )
  {
    lpDD->lpVtbl->Release(lpDD);
    lpDD = 0;
  }
  coop_hr = (*(int (__stdcall **)(LPVOID, void *, int))(*(_DWORD *)*dd_context + 80))(*dd_context, hwnd, 8);
  if ( coop_hr )
    Render_HandleDirectDrawFatalError(coop_hr, v14);
  surface_desc = 108;
  surface_flags = 1;
  surface_caps = 512;
  primary_surface_obj = (_DWORD *)Mem_Alloc(176, v14, 108, width);
  if ( primary_surface_obj )
    primary_surface_obj = Surface_Construct(primary_surface_obj);
  dd_context[1] = primary_surface_obj;
  create_primary_hr = (*(int (__stdcall **)(LPVOID, int *, int, _DWORD))(*(_DWORD *)*dd_context + 24))(*dd_context, &surface_desc, (int)dd_context[1] + 164, 0);
  if ( create_primary_hr )
    Render_HandleDirectDrawFatalError(create_primary_hr, v17);
  if ( create_back_surface )
  {
    back_surface_obj = (_DWORD *)Mem_Alloc(176, v17, (char)&surface_desc, width);
    if ( back_surface_obj )
      back_surface_obj = Surface_Construct(back_surface_obj);
    dd_context[2] = back_surface_obj;
    surface_flags = 7;
    surface_caps = 64;
    desc_width = width;
    desc_height = saved_height;
    create_back_hr = (*(int (__stdcall **)(LPVOID, int *, int, _DWORD))(*(_DWORD *)*dd_context + 24))(*dd_context, &surface_desc, (int)dd_context[2] + 164, 0);
    if ( create_back_hr )
      Render_HandleDirectDrawFatalError(create_back_hr, v20);
  }
  create_clipper_hr = (*(int (__stdcall **)(LPVOID, _DWORD, LPVOID *, _DWORD))(*(_DWORD *)*dd_context + 16))(*dd_context, 0, dd_context + 5, 0);
  if ( create_clipper_hr )
    Render_HandleDirectDrawFatalError(create_clipper_hr, v22);
  clipper_hwnd_hr = (*(int (__stdcall **)(LPVOID, _DWORD, void *))(*(_DWORD *)dd_context[5] + 32))(dd_context[5], 0, hwnd);
  if ( clipper_hwnd_hr )
    Render_HandleDirectDrawFatalError(clipper_hwnd_hr, v24);
  set_clipper_hr = (*(int (__stdcall **)(_DWORD, LPVOID))(**((_DWORD **)dd_context[1] + 41) + 112))(*((_DWORD *)dd_context[1] + 41), dd_context[5]);
  if ( set_clipper_hr )
    Render_HandleDirectDrawFatalError(set_clipper_hr, v26);
  return 1;
}
// 474F18: variable 'v12' is possibly undefined
// 474F41: variable 'v14' is possibly undefined
// 474F95: variable 'v17' is possibly undefined
// 474FF7: variable 'v20' is possibly undefined
// 475012: variable 'v22' is possibly undefined
// 475029: variable 'v24' is possibly undefined
// 475055: variable 'v10' is possibly undefined
// 475061: variable 'v26' is possibly undefined
// 51CA08: using guessed type IID stru_51CA08;

//----- (00475080) --------------------------------------------------------
signed int  Render_InitDirectDrawFullscreenMode(
        LPVOID *dd_context,
        _DWORD *hwnd,
        _DWORD *height,
        _DWORD *width,
        _DWORD *bpp,
        int mode_flag,
        DWORD use_flip_chain)
{
  _DWORD *raw;
  HRESULT hr;
  _DWORD *display_dim; // ebx
  _DWORD *primary_surface; // eax
  int ddraw_handle; // ebx
  _DWORD *back_surface; // eax
  int surface_desc_size; // [esp+34h] [ebp-80h] BYREF
  int desc_flags; // [esp+38h] [ebp-7Ch]
  BOOL has_backbuffer; // [esp+48h] [ebp-6Ch]
  int surface_caps; // [esp+9Ch] [ebp-18h]
  int attach_caps; // [esp+A0h] [ebp-14h] BYREF
  LPDIRECTDRAW lpDD; // [esp+A4h] [ebp-10h] BYREF

  raw = (_DWORD *)dd_context;
  raw[0] = 0;
  raw[10] = 1;
  raw[4] = 0;
  raw[6] = (int)(uintptr_t)width;
  raw[7] = (int)(uintptr_t)height;
  raw[2] = 0;
  raw[8] = (int)(uintptr_t)bpp;
  raw[1] = raw[2];
  raw[9] = (int)(uintptr_t)hwnd;
  hr = DirectDrawCreate(0, &lpDD, 0);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  hr = Compat_DirectDraw_QueryInterface(lpDD, &stru_51CA08, raw);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( lpDD )
  {
    Compat_DirectDraw_Release(lpDD);
    lpDD = 0;
  }
  hr = Compat_DirectDraw_SetCooperativeLevel((LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0], (HWND)(uintptr_t)hwnd, 83);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( mode_flag )
  {
    display_dim = (_DWORD *)(uintptr_t)(unsigned int)raw[6];
    hr = Compat_DirectDraw_SetDisplayMode(
           (LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0],
           (int)(uintptr_t)display_dim,
           raw[7],
           raw[8],
           0,
           1);
  }
  else
  {
    display_dim = (_DWORD *)(uintptr_t)(unsigned int)raw[7];
    hr = Compat_DirectDraw_SetDisplayMode(
           (LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0],
           raw[6],
           (int)(uintptr_t)display_dim,
           raw[8],
           0,
           0);
  }
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  primary_surface = (_DWORD *)Mem_Alloc(176, 0, (char)display_dim, use_flip_chain);
  if ( primary_surface )
    primary_surface = Surface_Construct(primary_surface);
  raw[1] = (int)(uintptr_t)primary_surface;
  desc_flags = 1;
  surface_caps = 512;
  surface_desc_size = 108;
  if ( use_flip_chain )
  {
    desc_flags = 33;
    surface_caps = 536;
  }
  has_backbuffer = use_flip_chain != 0;
  ddraw_handle = raw[0];
  hr = Compat_DirectDraw_CreateSurface((LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0], &surface_desc_size, (_DWORD *)(uintptr_t)(unsigned int)raw[1] + 41);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( use_flip_chain )
  {
    back_surface = (_DWORD *)Mem_Alloc(176, 0, ddraw_handle, use_flip_chain);
    if ( back_surface )
      back_surface = Surface_Construct(back_surface);
    raw[2] = (int)(uintptr_t)back_surface;
    attach_caps = 4;
    hr = Compat_DirectDrawSurface_GetAttachedSurface(
           (LPDIRECTDRAWSURFACE)*((_DWORD *)(uintptr_t)(unsigned int)raw[1] + 41),
           &attach_caps,
           (_DWORD *)(uintptr_t)(unsigned int)raw[2] + 41);
    if ( hr )
      Render_HandleDirectDrawFatalError(hr, 0);
  }
  return 1;
}
// 51CA08: using guessed type IID stru_51CA08;

//----- (004753E0) --------------------------------------------------------
int  Render_RestoreLostSurfaceIfNeeded(int ddraw_ctx)
{
  int result; // eax
  int dd_surface; // edx

  result = *(_DWORD *)(ddraw_ctx + 4);
  if ( !result )
    return 0;
  dd_surface = *(_DWORD *)(result + 164);
  if ( dd_surface )
  {
    result = Compat_DirectDrawSurface_IsLost((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)dd_surface);
    if ( result )
      return Compat_DirectDrawSurface_Restore((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)dd_surface);
  }
  return result;
}

//----- (00475420) --------------------------------------------------------
int  Render_SetPaletteEntryColor(int ddraw_ctx, int entry_index, char green, int red, char blue)
{
  _BYTE palette_entry[4]; // [esp+14h] [ebp-10h] BYREF
  int red_value; // [esp+18h] [ebp-Ch]

  red_value = red;
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int, _BYTE *))(**(_DWORD **)(ddraw_ctx + 16) + 16))(
    *(_DWORD *)(ddraw_ctx + 16),
    0,
    entry_index,
    1,
    palette_entry);
  palette_entry[0] = red_value;
  palette_entry[1] = green;
  palette_entry[2] = blue;
  return (*(int (__stdcall **)(_DWORD, _DWORD, int, int, _BYTE *))(**(_DWORD **)(ddraw_ctx + 16) + 24))(
           *(_DWORD *)(ddraw_ctx + 16),
           0,
           entry_index,
           1,
           palette_entry);
}

//----- (004754B0) --------------------------------------------------------
int  IO_StreamWrite(int result, int a2, int a3, int a4)
{
  int backing_stream; // esi

  backing_stream = *(_DWORD *)(result + 16);
  if ( backing_stream )
    return (*(int (__stdcall **)(int, _DWORD, int, int, int))(*(_DWORD *)backing_stream + 24))(backing_stream, 0, a2, a4, a3);
  return result;
}

//----- (00475A83) --------------------------------------------------------
int  IO_ParseOpenModeFlags(unsigned __int8 *mode_string, _DWORD *commit_mode_out)
{
  unsigned __int8 *mode_cursor; // ebx
  int parse_ok; // ecx
  int plus_seen; // ebp
  int text_mode_seen; // esi
  int commit_seen; // edi
  unsigned __int8 first_char; // al
  unsigned __int8 mode_char; // al
  int Value; // [esp+0h] [ebp-18h]

  mode_cursor = mode_string;
  parse_ok = 1;
  plus_seen = 0;
  text_mode_seen = 0;
  commit_seen = 0;
  Value = 0;
  if ( commit_mode_out )
    *commit_mode_out = g_CRT_DefaultCommitMode == 1;
  first_char = *mode_string;
  if ( *mode_cursor < 0x72u )
  {
    if ( first_char == 97 )
    {
      LOBYTE(Value) = -126;
      goto LABEL_15;
    }
LABEL_14:
    _set_errno_(0);
    return 0;
  }
  if ( *mode_cursor > 0x72u )
  {
    if ( first_char == 119 )
    {
      LOBYTE(Value) = 2;
      goto LABEL_15;
    }
    goto LABEL_14;
  }
  LOBYTE(Value) = 1;
LABEL_15:
  while ( 1 )
  {
    mode_char = *++mode_cursor;
    if ( !*mode_cursor || !parse_ok )
      break;
    if ( mode_char < 0x63u )
    {
      if ( mode_char >= 0x2Bu )
      {
        if ( mode_char <= 0x2Bu )
        {
          if ( plus_seen )
            goto LABEL_28;
          plus_seen = 1;
          LOBYTE(Value) = Value | 3;
        }
        else if ( mode_char == 98 )
        {
          if ( text_mode_seen )
            goto LABEL_28;
          text_mode_seen = 1;
          LOBYTE(Value) = Value | 0x40;
        }
      }
    }
    else if ( mode_char <= 0x63u )
    {
      if ( commit_seen )
        goto LABEL_28;
      commit_seen = 1;
      *(_BYTE *)commit_mode_out |= 1u;
    }
    else if ( mode_char >= 0x6Eu )
    {
      if ( mode_char <= 0x6Eu )
      {
        if ( commit_seen )
        {
LABEL_28:
          parse_ok = 0;
        }
        else
        {
          commit_seen = 1;
          *(_BYTE *)commit_mode_out &= ~1u;
        }
      }
      else if ( mode_char == 116 )
      {
        if ( text_mode_seen )
          goto LABEL_28;
        text_mode_seen = 1;
      }
    }
  }
  if ( !text_mode_seen && g_CRT_DefaultFileTranslationMode == 512 )
    LOBYTE(Value) = Value | 0x40;
  return Value;
}
// 51A549: using guessed type int dword_51A549;
// 51A64C: using guessed type int dword_51A64C;

//----- (00475B9E) --------------------------------------------------------
int  IO_OpenStreamWithMode(
        const CHAR *file_path,
        int a2,
        int stream_flags,
        DWORD a4,
        int a5,
        int a6,
        int stream)
{
  unsigned int open_flags;
  int fd_index;
  int mode_char;

  (void)a5;
  (void)a6;
  *(_BYTE *)(stream + 12) &= 0xFCu;
  *(_BYTE *)(stream + 12) |= (unsigned __int8)stream_flags;
  if ( (stream_flags & 0x80u) != 0 )
    mode_char = 'a';
  else if ( (stream_flags & 2) != 0 )
    mode_char = 'w';
  else
    mode_char = 'r';
  if ( mode_char == 'r' )
  {
    open_flags = 0;
    if ( (stream_flags & 2) != 0 )
      open_flags = 2;
    if ( (stream_flags & 0x40) != 0 )
      open_flags |= 0x200u;
    else
      open_flags |= 0x100u;
    fd_index = Compat_OpenFileDescriptor(file_path, mode_char, stream_flags);
  }
  else
  {
    open_flags = ((stream_flags & 1) != 0) + 33;
    if ( (stream_flags & 0x80u) == 0 )
      open_flags |= 0x40u;
    else
      open_flags |= 0x10u;
    if ( (stream_flags & 0x40) != 0 )
      open_flags |= 0x200u;
    else
      open_flags |= 0x100u;
    fd_index = Compat_OpenFileDescriptor(file_path, mode_char, stream_flags);
  }
  if ( fd_index == -1 )
  {
    Compat_FreeFileStream(stream);
    return 0;
  }
  Compat_InitFileStream(stream, fd_index, mode_char, stream_flags);
  if ( (stream_flags & 0x80u) != 0 )
    Compat_StreamSeek(stream, 0, 2);
  _chktty_();
  return stream;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);
// 4884E3: using guessed type int _chktty_(void);

//----- (00475C84) --------------------------------------------------------
int  IO_OpenStream(
        const CHAR *file_path,
        unsigned __int8 *mode_string,
        int a3,
        int a4,
        DWORD a5)
{
  int result; // eax
  int open_flags; // ebx
  int stream_ptr; // eax
  int mode_info[4]; // [esp+0h] [ebp-10h] BYREF

  mode_info[3] = a3;
  result = IO_ParseOpenModeFlags(mode_string, mode_info);
  open_flags = result;
  if ( result )
  {
    stream_ptr = Compat_AllocFileStream();
    if ( stream_ptr )
      return IO_OpenStreamWithMode(file_path, mode_info[0], open_flags, a5, a4, 0, stream_ptr);
    return 0;
  }
  return result;
}

//----- (00475CC8) --------------------------------------------------------
int  IO_FOpen(const CHAR *file_path, unsigned __int8 *mode_string, int a3, DWORD a4)
{
  return IO_OpenStream(file_path, mode_string, a3, 0, a4);
}

//----- (00475CD2) --------------------------------------------------------
int  IO_CloseStream(int stream, int error_code)
{
  int v3; // ecx
  _DWORD *i; // eax
  int stream_handle; // edx
  int *j; // edx
  int *list_node; // eax
  int old_head; // edx

  g_CRT_StaticLock1AcquireHook();
  for ( i = (_DWORD *)g_CRT_OpenStreamListHead; i; i = (_DWORD *)*i )
  {
    stream_handle = i[1];
    if ( stream == stream_handle )
    {
      if ( (*(_BYTE *)(stream_handle + 12) & 3) != 0 )
        _doclose_(v3, 1);
LABEL_6:
      g_CRT_StaticLock1ReleaseHook();
      return stream;
    }
  }
  for ( j = &g_IO_OpenStreamListHead; ; j = (int *)*j )
  {
    list_node = (int *)*j;
    if ( !*j )
      break;
    if ( stream == list_node[1] )
    {
      *j = *list_node;
      old_head = g_CRT_OpenStreamListHead;
      g_CRT_OpenStreamListHead = (int)list_node;
      *list_node = old_head;
      goto LABEL_6;
    }
  }
  _set_errno_(error_code);
  g_CRT_StaticLock1ReleaseHook();
  return 0;
}
// 475CFA: variable 'v3' is possibly undefined
// 475ECD: using guessed type int __fastcall _doclose_(_DWORD, _DWORD);
// 485379: using guessed type _DWORD nullsub_8();
// 51A57C: using guessed type _DWORD (*off_51A57C)();
// 51A580: using guessed type _DWORD (*off_51A580)();
// 54DD88: using guessed type int dword_54DD88;
// 54DD8C: using guessed type int dword_54DD8C;

//----- (004761EF) --------------------------------------------------------
char * Str_FormatUnsignedRadixDigits(unsigned int value, char *buffer, unsigned int radix)
{
  char *out_cursor; // esi
  char *digit_cursor; // ecx
  char digit_char; // al
  char digit_stack; // [esp+1h] [ebp-37h] BYREF
  unsigned int quotient; // [esp+24h] [ebp-14h]

  out_cursor = buffer;
  digit_cursor = &digit_stack;
  do
  {
    quotient = value / radix;
    *digit_cursor = g_Str_RadixDigitCharacters[value % radix];
    value = quotient;
    ++digit_cursor;
  }
  while ( quotient );
  do
  {
    digit_char = *--digit_cursor;
    *out_cursor++ = *digit_cursor;
  }
  while ( digit_char );
  return buffer;
}

//----- (00476238) --------------------------------------------------------
int  Str_FormatSignedRadixDigits(signed int value, char *buffer, unsigned int radix)
{
  int v3; // ecx

  if ( radix == 10 && value < 0 )
  {
    value = -value;
    *buffer++ = 45;
  }
  Str_FormatUnsignedRadixDigits(value, buffer, radix);
  return v3;
}
// 47624F: variable 'v3' is possibly undefined

//----- (004762AE) --------------------------------------------------------
unsigned int  IO_OpenFileDescriptorBinaryMode(const CHAR *file_path, DWORD a2)
{
  return CRT_OpenFile(a2, file_path, 98);
}

//----- (00476301) --------------------------------------------------------
int Output_WriteFormatted(int a1, int a2, int output_stream, int format_string, ...)
{
  const char *format;
  int arg_count;
  int args_ptr;
  int cursor;
  int result;
  int i;
  va_list args;

  (void)a1;
  (void)a2;
  if ( !output_stream || !format_string )
    return 0;

  format = (const char *)(uintptr_t)(unsigned int)format_string;
  arg_count = Compat_CountPrintfArgs32(format);
  if ( arg_count <= 0 )
  {
    cursor = 0;
    return CRT_VfprintfLockedWrite(output_stream, format_string, &cursor);
  }

  args_ptr = Compat_AllocLow32Bytes(4 * arg_count);
  if ( !args_ptr )
    return 0;

  va_start(args, format_string);
  for ( i = 0; i < arg_count; ++i )
    *(_DWORD *)(uintptr_t)(unsigned int)(args_ptr + 4 * i) = va_arg(args, int);
  va_end(args);

  cursor = args_ptr;
  result = CRT_VfprintfLockedWrite(output_stream, format_string, &cursor);
  Compat_FreeLow32Bytes(args_ptr);
  return result;
}

//----- (00476A0C) --------------------------------------------------------
void __thiscall Compat_TriggerFatalRuntimeErrorOnce(void *this)
{
  if ( !g_FatalRuntimeErrorOnceGuard )
  {
    g_FatalRuntimeErrorOnceGuard = 1;
    _wcpp_4_fatal_runtime_error__(this, 1);
  }
}
// 486342: using guessed type int __fastcall _wcpp_4_fatal_runtime_error__(_DWORD, _DWORD);
// 51A644: using guessed type __int16 word_51A644;

//----- (00476A80) --------------------------------------------------------
int FileSystem_InitCurrentEntryPathHolder()
{
  g_FileSystemStrippedPathHolderText = 0;
  g_CurrentEntryPathHolder_VtablePtr = (int)&g_PathEntry_Vtable;
  return CRT_RegisterFinalizableObject(&g_PathEntry_Vtable, 0);
}
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50EC94: using guessed type int (*off_50EC94)();
// 54DD00: using guessed type int dword_54DD00;
// 54DD04: using guessed type int dword_54DD04;

//----- (00476AB0) --------------------------------------------------------
int  FileSystem_WalkEntryListInvokingCleanup(int result)
{
  int i; // ecx
  _DWORD *v2; // ecx
  int (__fastcall ***v3)(_DWORD *, _DWORD); // esi
  int v4; // ecx

  for ( i = result; *(_DWORD *)i; result = (*(int (**)(void))(**(_DWORD **)v4 + 16))() )
  {
    result = (*(int (**)(void))(**(_DWORD **)i + 12))();
    if ( !result )
      break;
    v3 = (int (__fastcall ***)(_DWORD *, _DWORD))v2[2];
    if ( !v3 )
      break;
    result = (**v3)(v2, *v2);
    if ( result )
      break;
  }
  return result;
}
// 476ABC: variable 'i' is possibly undefined
// 476AC7: variable 'v2' is possibly undefined
// 476ADF: variable 'v4' is possibly undefined

//----- (00476AF0) --------------------------------------------------------
int  FileSystem_ConstructMountTable(int mount_table, int file_system, const CHAR *log_file_path, DWORD alloc_context)
{
  int entry_path_holder; // [esp+4h] [ebp-1Ch] BYREF
  int (**entry_path_vtable)(); // [esp+8h] [ebp-18h]
  int open_mode_handle; // [esp+Ch] [ebp-14h]
  _DWORD *entry_record;
  int entry_index;
  int child_path;

  *(_DWORD *)(mount_table + 4) = 0;
  *(_DWORD *)(mount_table + 8) = (int)&g_PathEntry_Vtable;
  *(_DWORD *)(mount_table + 12) = 0;
  *(_DWORD *)(mount_table + 16) = (int)&g_PathEntry_Vtable;
  *(_DWORD *)(mount_table + 24) = 1;
  *(_DWORD *)(mount_table + 28) = 0;
  *(_DWORD *)(mount_table + 32) = 0;
  *(_DWORD *)(mount_table + 36) = (int)g_PathEntryArray_Vtable;
  *(_DWORD *)(mount_table + 20) = 0;
  *(_DWORD *)mount_table = (int)g_FileSystemMountTable_VTable;
  open_mode_handle = 0;
  if ( log_file_path )
    open_mode_handle = IO_FOpen(log_file_path, (unsigned __int8 *)aWt, mount_table, alloc_context);
  entry_path_holder = 0;
  entry_path_vtable = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&entry_path_holder);
  entry_path_vtable = &g_PathEntry_Vtable;
  if ( *(_DWORD *)(mount_table + 28) == *(_DWORD *)(mount_table + 32) )
    PathEntryArray_GrowByDelta((_DWORD *)(mount_table + 20), *(_DWORD *)(mount_table + 24));
  entry_index = *(_DWORD *)(mount_table + 28);
  *(_DWORD *)(mount_table + 28) = entry_index + 1;
  entry_record = (_DWORD *)(16 * entry_index + *(_DWORD *)(mount_table + 20));
  *entry_record = file_system;
  Compat_StringHolderCopyText(entry_record + 1, Compat_StringHolderGetText((_DWORD *)&entry_path_holder));
  entry_record[3] = open_mode_handle;
  FileSystem_DiskMountResolveRegisteredRootPath(file_system, mount_table);
  child_path = (int)(intptr_t)FileSystem_DiskMountGetCurrentDirectory((void *)(intptr_t)file_system);
  if ( child_path )
    FileSystem_SetCurrentDirectoryFromPath((const char **)(intptr_t)mount_table, child_path);
  Compat_StringHolderDestroyStack((_DWORD *)&entry_path_holder, 0);
  return mount_table;
}

//----- (00476C30) --------------------------------------------------------
int  FileSystem_DestructMountTable(_DWORD *mount_table, char flags)
{
  _DWORD *v3; // ecx
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v8; // ecx
  int v9; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(mount_table, &g_FileSystemMountTable_DtorArrayTag);
    j_j__nfree_();
    return v8;
  }
  else
  {
    *mount_table = g_FileSystemMountTable_VTable;
    FileSystem_RemoveMountsFromIndex((int)mount_table, 0);
    v3[4] = g_PathEntryArray_Vtable;
    PathEntryArray_DestructElements(v3);
    v5 = Compat_StringHolderScalarDeletingDtor(v4 - 8, 0);
    v6 = Compat_StringHolderScalarDeletingDtor(v5 - 8, 0);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v9;
    }
    else
    {
      return v6 - 4;
    }
  }
}
// 476C4D: variable 'v3' is possibly undefined
// 476C5B: variable 'v4' is possibly undefined
// 476C89: variable 'v8' is possibly undefined
// 476C95: variable 'v9' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50ECA4: using guessed type int (*off_50ECA4[2])();
// 510964: using guessed type int (*off_510964[13])();

//----- (00476CA0) --------------------------------------------------------
_DWORD * FileSystem_RemoveMountsFromIndex(int mount_table, int start_index)
{
  int entry_index; // ecx
  _DWORD *result; // eax
  _DWORD *v4; // edi
  _DWORD *v5; // ebp
  int entry_offset; // esi
  int mount_obj; // eax
  int v8; // ecx
  _DWORD *v9; // [esp+0h] [ebp-1Ch]

  entry_index = *(_DWORD *)(mount_table + 28) - 1;
  result = (_DWORD *)(mount_table + 20);
  if ( entry_index >= start_index )
  {
    v4 = result;
    v5 = result;
    v9 = result;
    entry_offset = 16 * entry_index;
    do
    {
      mount_obj = *(_DWORD *)(entry_offset + *v9);
      if ( mount_obj )
        (*(void (**)(void))(*(_DWORD *)mount_obj + 8))();
      if ( *(_DWORD *)(entry_offset + *v5 + 12) )
      {
        fclose_(entry_index);
        *(_DWORD *)(entry_offset + *v5 + 12) = 0;
      }
      result = PathEntryArray_RemoveAt(v4, entry_index, 1);
      entry_index = v8 - 1;
      entry_offset -= 16;
    }
    while ( entry_index >= start_index );
  }
  return result;
}
// 476CDD: variable 'v2' is possibly undefined
// 476CFF: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00476D20) --------------------------------------------------------
char  FileSystem_NormalizePath(int mount_table, const char **path_holder)
{
  const char *path_text;
  signed int colon_index;
  signed int search_index;
  int dot_index;
  int dot_next_index;
  int parent_index;
  _DWORD v18[2];

  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( !path_text || !*path_text )
    return 0;
  if ( Compat_StringHolderFindCharFrom(path_holder, 58, 0) == -1 )
  {
    if ( *path_text == 92 )
    {
      Compat_StringHolderPrependText(path_holder, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(mount_table + 4));
    }
    else
    {
      v18[0] = 0;
      v18[1] = (int)&g_PathEntry_Vtable;
      Compat_StringHolderConstructJoined(v18, (_DWORD *)(uintptr_t)(unsigned int)(mount_table + 4), (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(mount_table + 12));
      Compat_StringHolderPrependText(path_holder, Compat_StringHolderGetText(v18));
      Compat_StringHolderDestroyStack(v18, 1);
    }
  }
  colon_index = Compat_StringHolderFindCharFrom(path_holder, 58, 0) + 1;
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( !path_text || path_text[colon_index] != 92 )
    Compat_StringHolderInsertTextChecked(path_holder, colon_index, asc_5024B0);
  search_index = 0;
  while ( 1 )
  {
    dot_index = Compat_StringHolderFindCharFrom(path_holder, 46, search_index);
    if ( dot_index == -1 )
      break;
    dot_next_index = dot_index + 1;
    path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
    if ( !path_text )
      break;
    if ( path_text[dot_next_index] == 46 )
    {
      if ( path_text[dot_index - 1] != 92 || (parent_index = Compat_StringHolderFindLastBackslashBefore((char **)path_holder, dot_index - 2), parent_index == -1) )
      {
        Compat_StringHolderCopyText((_DWORD *)path_holder, "");
        return 0;
      }
      Compat_StringHolderRemoveRange((char **)path_holder, parent_index, (unsigned int)(uintptr_t)path_holder, dot_index - parent_index + 2);
    }
    else if ( path_text[dot_index - 1] == 92 )
    {
      Compat_StringHolderRemoveRange((char **)path_holder, dot_index - 1, (unsigned int)(uintptr_t)path_holder, 2);
    }
    else
    {
      search_index = dot_next_index;
    }
  }
  colon_index = Compat_StringHolderFindCharFrom(path_holder, 58, 0) + 1;
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( !path_text || path_text[colon_index] != 92 )
    Compat_StringHolderInsertTextChecked(path_holder, colon_index, asc_5024B4);
  return (char)(unsigned __int8)(uintptr_t)Compat_StringHolderUppercaseInPlace(path_holder, (unsigned int)(uintptr_t)path_holder);
}

//----- (00476ED0) --------------------------------------------------------
const char ** FileSystem_StripMountPrefix(int mount_table, int entry_index, unsigned int a3, const char **path_holder)
{
  const char *entry_path;
  const char *holder_text;
  unsigned int holder_len;
  int entry_path_len;
  const char **result; // eax

  entry_path = Compat_StringHolderGetText((_DWORD *)(uintptr_t)(16 * entry_index + *(_DWORD *)(mount_table + 20) + 4));
  if ( entry_path )
  {
    a3 = (unsigned int)strlen(entry_path);
    entry_path_len = (int)a3;
  }
  else
  {
    entry_path_len = 0;
  }
  result = Compat_StringHolderRemoveRange((char **)path_holder, 0, a3, entry_path_len);
  holder_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)path_holder);
  if ( holder_text )
  {
    holder_len = (unsigned int)strlen(holder_text) + 1;
    if ( holder_len != 1 && *(const unsigned char *)holder_text == 92 )
      return Compat_StringHolderRemoveRange((char **)path_holder, 0, holder_len - 1, 1);
  }
  return path_holder;
}

//----- (00476F40) --------------------------------------------------------
int  FileSystem_CallEntryOpSlot12(int entry)
{
  return (*(int (**)(void))(**(_DWORD **)entry + 48))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00476F60) --------------------------------------------------------
signed int  FileSystem_FindMatchingMountIndex(int mount_table, const char **path_holder, int start_index)
{
  const char *entry_path;
  unsigned int entry_path_len;
  unsigned int requested_path_len;
  int current_index;
  int current_offset;
  int limit_offset;

  current_index = start_index;
  if ( start_index >= *(_DWORD *)(mount_table + 28) )
    return -1;
  current_offset = 16 * start_index;
  limit_offset = 16 * *(_DWORD *)(mount_table + 28);
  do
  {
    entry_path = Compat_StringHolderGetText((_DWORD *)(current_offset + *(_DWORD *)(mount_table + 20) + 4));
    if ( entry_path )
      entry_path_len = strlen(entry_path);
    else
      entry_path_len = 0;
    if ( !entry_path_len )
      return current_index;
    if ( *path_holder )
      requested_path_len = strlen(*path_holder);
    else
      requested_path_len = 0;
    if ( entry_path_len < requested_path_len )
    {
      if ( !memcmp(*path_holder, entry_path, entry_path_len) && (*path_holder)[entry_path_len] == 92 )
        return current_index;
    }
    else if ( entry_path_len == requested_path_len && !memcmp(*path_holder, entry_path, requested_path_len) )
    {
      return current_index;
    }
    current_offset += 16;
    ++current_index;
  }
  while ( current_offset < limit_offset );
  return -1;
}

//----- (004770B0) --------------------------------------------------------
int  FileSystem_ResolveAndInvokeForPath(int mount_table, int default_result, int (*callback)(void))
{
  int matched_index; // eax
  int callback_result; // eax
  int next_index; // eax
  const char *normalized_path; // [esp+0h] [ebp-18h] BYREF
  int (**normalized_vtable)(); // [esp+4h] [ebp-14h]
  int entries_ptr; // [esp+8h] [ebp-10h]

  normalized_path = 0;
  normalized_vtable = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&normalized_path);
  normalized_vtable = &g_PathEntry_Vtable;
  FileSystem_NormalizePath(mount_table, &normalized_path);
  if ( normalized_path && *normalized_path )
  {
    entries_ptr = mount_table + 20;
    next_index = 0;
    while ( 1 )
    {
      matched_index = FileSystem_FindMatchingMountIndex(mount_table, &normalized_path, next_index);
      if ( matched_index == -1 )
        break;
      Compat_StringHolderDestructor(&g_FileSystemStrippedPathHolderText);
      FileSystem_StripMountPrefix(mount_table, matched_index, matched_index, (const char **)&g_FileSystemStrippedPathHolderText);
      callback_result = callback();
      if ( callback_result != default_result )
      {
        Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
        return callback_result;
      }
      next_index = matched_index + 1;
    }
  }
  Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
  return default_result;
}
// 54DD00: using guessed type int dword_54DD00;

static int Compat_FileSystemQuery(int filesystem, const char *requested_path, int expected_result, int (*callback)(int))
{
  int callback_result;
  int current_entry;
  int next_entry;
  int entry_base;
  const char *normalized_path; // [esp+0h] [ebp-18h] BYREF
  int (**normalized_vtable)(); // [esp+4h] [ebp-14h]

  normalized_path = 0;
  normalized_vtable = &g_CompatStringHolder_Vtable;
  Compat_StringHolderCopyText((_DWORD *)&normalized_path, requested_path);
  normalized_vtable = &g_PathEntry_Vtable;
  FileSystem_NormalizePath(filesystem, &normalized_path);
  if ( normalized_path && *normalized_path )
  {
    next_entry = 0;
    entry_base = *(_DWORD *)(filesystem + 20);
    while ( 1 )
    {
      current_entry = FileSystem_FindMatchingMountIndex(filesystem, &normalized_path, next_entry);
      if ( current_entry == -1 )
        break;
      Compat_StringHolderCopyText(&g_FileSystemStrippedPathHolderText, Compat_StringHolderGetText((_DWORD *)&normalized_path));
      FileSystem_StripMountPrefix(filesystem, current_entry, current_entry, (const char **)&g_FileSystemStrippedPathHolderText);
      callback_result = callback(entry_base + 16 * current_entry);
      if ( callback_result != expected_result )
      {
        Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
        return callback_result;
      }
      next_entry = current_entry + 1;
    }
  }
  Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
  return expected_result;
}

//----- (00477170) --------------------------------------------------------
int  FileSystem_TryOpenEntryCallback(int entry)
{
  int opened_query; // ebx

  opened_query = Compat_FileSystemOpenIfReady(*(_DWORD *)entry, g_FileSystemMountOpenMode);
  if ( !*(_DWORD *)(entry + 12) )
    return opened_query;
  if ( opened_query )
  {
    Output_WriteFormatted(entry + 12, g_FileSystemStrippedPathHolderText, *(_DWORD *)(entry + 12), (int)aS_15, g_FileSystemStrippedPathHolderText);
    return opened_query;
  }
  Output_WriteFormatted(entry + 12, g_FileSystemStrippedPathHolderText, *(_DWORD *)(entry + 12), (int)aS_2, g_FileSystemStrippedPathHolderText);
  return opened_query;
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (004771D0) --------------------------------------------------------
signed int  FileSystem_SetCurrentDirectoryFromPath(const char **file_system, int dir_path)
{
  _DWORD *fs_words;
  unsigned int path_len_with_nul;
  int colon_index;
  const char *root_text;
  unsigned int root_text_len;
  unsigned int normalized_text_len;
  const char *normalized_path; // [esp+0h] [ebp-20h] BYREF
  int (**normalized_vtable)(); // [esp+4h] [ebp-1Ch]

  fs_words = (_DWORD *)(uintptr_t)file_system;
  if ( !(*((int (__thiscall **)(int))*file_system + 12))(dir_path) )
    return 0;
  normalized_path = 0;
  normalized_vtable = &g_CompatStringHolder_Vtable;
  Compat_StringHolderInitText((_DWORD *)&normalized_path, (const char *)(uintptr_t)(unsigned int)dir_path);
  normalized_vtable = &g_PathEntry_Vtable;
  FileSystem_NormalizePath((int)file_system, &normalized_path);
  if ( normalized_path && *normalized_path )
  {
    path_len_with_nul = (unsigned int)strlen(normalized_path) + 1;
    if ( path_len_with_nul >= 2 && normalized_path[path_len_with_nul - 2] != 92 )
      Compat_StringHolderInsertTextChecked(&normalized_path, path_len_with_nul - 1, asc_5024C0);
    colon_index = Compat_StringHolderFindCharFrom(&normalized_path, 58, 0);
    Compat_StringHolderCopyText(fs_words + 1, normalized_path);
    root_text = Compat_StringHolderGetText(fs_words + 1);
    if ( root_text )
      root_text_len = (unsigned int)strlen(root_text);
    else
      root_text_len = 0;
    Compat_StringHolderRemoveRange((char **)(fs_words + 1), colon_index + 1, root_text_len, (int)(root_text_len - (unsigned int)(colon_index + 1)));
    normalized_text_len = (unsigned int)strlen(normalized_path);
    Compat_StringHolderRemoveRange(&normalized_path, 0, normalized_text_len, colon_index + 1);
    Compat_StringHolderCopyText(fs_words + 3, normalized_path);
    Compat_StringHolderScalarDeletingDtor((int)&normalized_path, 1);
    return 1;
  }
  else
  {
    Compat_StringHolderScalarDeletingDtor((int)&normalized_path, 1);
    return 0;
  }
}
// 477288: variable 'v5' is possibly undefined
// 4772A3: variable 'v7' is possibly undefined
// 4772B1: variable 'v9' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477300) --------------------------------------------------------
int  FileSystem_ResolveRelativeToCurrentDir(int file_system, int path_holder)
{
  int fs_saved; // edx
  int path_holder_saved; // [esp-10h] [ebp-14h]
  _DWORD joined_holder[4]; // [esp-Ch] [ebp-10h] BYREF

  fs_saved = file_system;
  if ( (g_FileSystem_CwdHolderInitFlag & 1) == 0 )
  {
    path_holder_saved = path_holder;
    g_FileSystem_CwdHolderInitFlag |= 1u;
    g_FS_ResolvedPathEntryHolder = 0;
    g_CurrentDirPathHolder_VtablePtr = (int)&g_PathEntry_Vtable;
    CRT_RegisterFinalizableObject(0, file_system);
    path_holder = path_holder_saved;
  }
  Compat_StringHolderConstructJoined(joined_holder, path_holder, *(const char **)(fs_saved + 12));
  Compat_StringHolderDestructor(&g_FS_ResolvedPathEntryHolder);
  Compat_StringHolderScalarDeletingDtor((int)joined_holder, 1);
  return g_FS_ResolvedPathEntryHolder;
}
// 477312: variable 'v3' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50EC94: using guessed type int (*off_50EC94)();
// 54DCF0: using guessed type int dword_54DCF0;
// 54DCF4: using guessed type int dword_54DCF4;
// 54DCF8: using guessed type char byte_54DCF8;

//----- (00477370) --------------------------------------------------------
int  FileSystem_AddMountEntry(int *mount_table, const CHAR *mount_path, const CHAR *log_file_path, DWORD mount)
{
  int archive_mode; // eax
  const char *path_text; // eax
  unsigned int path_len; // ecx
  _DWORD *entry_array; // ecx
  int entry_index; // edx
  _DWORD *entry_record; // ecx
  _DWORD *entry_path_holder; // ebx
  const char *normalized_path; // [esp+10h] [ebp-18h] BYREF
  int (**vtable_ptr)(); // [esp+14h] [ebp-14h]
  const CHAR *log_path_saved; // [esp+18h] [ebp-10h]

  archive_mode = 0;
  log_path_saved = log_file_path;
  normalized_path = 0;
  vtable_ptr = &g_CompatStringHolder_Vtable;
  Compat_StringHolderInitText((_DWORD *)&normalized_path, mount_path);
  FileSystem_NormalizePath((int)mount_table, &normalized_path);
  path_text = Compat_StringHolderGetText((_DWORD *)&normalized_path);
  if ( path_text && *path_text )
  {
    path_len = strlen(path_text);
    if ( path_len && path_text[path_len - 1] == 92 )
    {
      Compat_StringHolderRemoveRange((char **)&normalized_path, (int)(path_len - 1), (unsigned int)(uintptr_t)&normalized_path, 1);
    }
    if ( log_path_saved )
      archive_mode = IO_FOpen(log_path_saved, (unsigned __int8 *)aWt_0, 0, mount);
    entry_array = mount_table + 5;
    if ( mount_table[7] == mount_table[8] )
      PathEntryArray_GrowByDelta(mount_table + 5, mount_table[6]);
    entry_index = entry_array[2];
    entry_array[2] = entry_index + 1;
    entry_record = (_DWORD *)(16 * entry_index + *entry_array);
    *entry_record = mount;
    entry_path_holder = entry_record + 1;
    Compat_StringHolderCopyText(entry_path_holder, Compat_StringHolderGetText((_DWORD *)&normalized_path));
    entry_record[3] = archive_mode;
    Compat_FileSystemOnMounted((int)mount, mount_table);
  }
  return Compat_StringHolderDestroyStack((_DWORD *)&normalized_path, 1);
}
// 477460: variable 'v9' is possibly undefined
// 477478: variable 'v10' is possibly undefined
// 4774A6: variable 'v14' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004774D0) --------------------------------------------------------
_DWORD * FileSystem_CreateEntryHandleWrapper(DWORD *file_system, int a2, int a3)
{
  _DWORD *result; // eax
  DWORD vtable; // ebp
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  _DWORD *wrapper; // esi
  _DWORD *opened_entry; // [esp+0h] [ebp-10h]

  result = (_DWORD *)(*(int (__fastcall **)(int, int))(*file_system + 12))(a2, a3);
  opened_entry = result;
  if ( result )
  {
    vtable = *file_system;
    if ( (*(int (**)(void))(*file_system + 16))() )
    {
      result = (_DWORD *)Mem_Alloc(16, v7, 10, vtable);
      wrapper = result;
      if ( result )
      {
        *result = v9;
        result[2] = opened_entry;
        result[3] = v8;
        result[1] = j_Mem_Alloc(v9);
        return wrapper;
      }
    }
    else
    {
      (*(void (**)(void))(*file_system + 20))();
      return 0;
    }
  }
  return result;
}
// 47750D: variable 'v7' is possibly undefined
// 47751B: variable 'v9' is possibly undefined
// 477522: variable 'v8' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00477550) --------------------------------------------------------
int  FileSystem_AdvanceEntryEnumerator(int enumerator)
{
  int advance_result; // esi
  int v2; // ecx

  advance_result = (*(int (__fastcall **)(int, _DWORD))(**(_DWORD **)(enumerator + 8) + 20))(enumerator, *(_DWORD *)(enumerator + 4));
  (*(void (__fastcall **)(int, _DWORD))(**(_DWORD **)(v2 + 12) + 24))(v2, *(_DWORD *)(v2 + 4));
  return advance_result;
}
// 477566: variable 'v2' is possibly undefined

//----- (00477580) --------------------------------------------------------
int  Compat_FileSystemReleaseFileRecord(int file_system, int *record_ptr)
{
  int v3; // ecx
  int result; // eax

  (*(void (__fastcall **)(int, int))(*(_DWORD *)file_system + 20))(file_system, *record_ptr + 8);
  (*(void (__fastcall **)(int, int))(*(_DWORD *)v3 + 20))(v3, *record_ptr + 12);
  result = *record_ptr;
  if ( *record_ptr )
  {
    Compat_FileSystemFreeFileRecordName();
    result = j__nfree_();
  }
  *record_ptr = 0;
  return result;
}
// 477591: variable 'v3' is possibly undefined

//----- (004775D0) --------------------------------------------------------
int Compat_FileSystemFreeFileRecordName()
{
  int v1; // ecx

  j_j__nfree_();
  return v1;
}
// 4775DB: variable 'v1' is possibly undefined

//----- (004775E0) --------------------------------------------------------
signed int  Compat_FileSystemVisitFile(DWORD *file_system, int a2, int a3)
{
  int v5; // ecx
  _DWORD *wrapper; // [esp+0h] [ebp-8h] BYREF

  wrapper = FileSystem_CreateEntryHandleWrapper(file_system, a2, a3);
  if ( !wrapper )
    return -1;
  while ( FileSystem_AdvanceEntryEnumerator((int)wrapper) )
    ;
  Compat_FileSystemReleaseFileRecord((int)file_system, (int *)&wrapper);
  return v5;
}
// 47760B: variable 'v5' is possibly undefined

//----- (00477620) --------------------------------------------------------
_DWORD * Compat_FileSystemReleaseMountedPaths(int mount_table)
{
  int entry_index; // ecx
  _DWORD *result; // eax
  _DWORD *entries_ptr; // esi
  int entry_offset; // edx

  entry_index = *(_DWORD *)(mount_table + 28) - 1;
  result = (_DWORD *)(mount_table + 20);
  if ( entry_index >= 0 )
  {
    entries_ptr = result;
    entry_offset = 16 * entry_index;
    do
      result = (_DWORD *)(*(int (__fastcall **)(int, int))(**(_DWORD **)(entry_offset + *entries_ptr) + 40))(entry_index - 1, entry_offset - 16);
    while ( entry_offset >= 0 );
  }
  return result;
}
// 477638: variable 'v4' is possibly undefined
// 477640: variable 'v1' is possibly undefined

//----- (00477660) --------------------------------------------------------
int  Compat_FileSystemProcessDirectChildren(int (__thiscall ***file_system)(_DWORD), int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int entry_list; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+4h] [ebp-14h]
  int v10; // [esp+8h] [ebp-10h]
  int v11; // [esp+10h] [ebp-8h]

  v11 = a2;
  entry_list = (**file_system)(0);
  v9 = (int)file_system;
  v10 = v3;
  FileSystem_WalkEntryListInvokingCleanup((int)&entry_list);
  for ( ; entry_list; v4 = v5 + 1 )
  {
    if ( !(*(int (**)(void))(*(_DWORD *)entry_list + 12))() )
      break;
    (*(void (**)(void))(*(_DWORD *)entry_list + 16))();
    FileSystem_WalkEntryListInvokingCleanup((int)&entry_list);
  }
  (*(void (__fastcall **)(int, int))(*(_DWORD *)v9 + 4))(v4, entry_list);
  return v6;
}
// 477677: variable 'v3' is possibly undefined
// 4776A7: variable 'v5' is possibly undefined
// 4776B9: variable 'v4' is possibly undefined
// 4776BC: variable 'v6' is possibly undefined

//----- (004776D0) --------------------------------------------------------
int  Compat_FileSystemFindMountedPathById(int mount_table, int mount_id)
{
  int entry_index; // edx
  _DWORD *v4; // eax
  _DWORD *entries_ptr; // esi
  int entry_offset; // eax
  _DWORD *entry_record; // ecx

  entry_index = *(_DWORD *)(mount_table + 28) - 1;
  v4 = (_DWORD *)(mount_table + 20);
  if ( entry_index < 0 )
    return 0;
  entries_ptr = v4;
  entry_offset = 16 * entry_index;
  while ( 1 )
  {
    entry_record = (_DWORD *)(entry_offset + *entries_ptr);
    if ( mount_id == *entry_record )
      break;
    entry_offset -= 16;
    --entry_index;
    if ( entry_offset < 0 )
      return 0;
  }
  return entry_record[1];
}

//----- (00477710) --------------------------------------------------------
signed int  Compat_FileSystemWalkDirectoryTree(int (***file_system)(void), int a2, int a3)
{
  const char *v4; // ecx
  int visit_result; // edi
  const char *v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int file_visit_failed; // ebx
  int v15; // ecx
  int enumerator; // [esp+0h] [ebp-48h] BYREF
  int (***v17)(void); // [esp+4h] [ebp-44h]
  int v18; // [esp+8h] [ebp-40h]
  _DWORD recurse_path_holder[2]; // [esp+Ch] [ebp-3Ch] BYREF
  const char *v20; // [esp+14h] [ebp-34h] BYREF
  int (**v21)(); // [esp+18h] [ebp-30h]
  const char *v22; // [esp+1Ch] [ebp-2Ch] BYREF
  int (**v23)(); // [esp+20h] [ebp-28h]
  const char *entry_name_holder; // [esp+24h] [ebp-24h] BYREF
  int (**v25)(); // [esp+28h] [ebp-20h]
  _DWORD file_path_holder[2]; // [esp+2Ch] [ebp-1Ch] BYREF
  _DWORD subdir_path_holder[2]; // [esp+34h] [ebp-14h] BYREF
  _DWORD joined_path_holder[2]; // [esp+3Ch] [ebp-Ch] BYREF
  int v29; // [esp+44h] [ebp-4h]

  v29 = a2;
  v20 = 0;
  v21 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v20);
  v21 = &g_PathEntry_Vtable;
  Compat_StringHolderAppendText(&v20, asc_5024C5);
  v22 = v4;
  v23 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v22);
  v23 = &g_PathEntry_Vtable;
  Compat_StringHolderAppendText(&v22, asc_5024C7);
  enumerator = (**file_system)();
  v18 = v29;
  v17 = file_system;
  FileSystem_WalkEntryListInvokingCleanup((int)&enumerator);
  visit_result = 0;
  if ( enumerator )
  {
    while ( (*(int (**)(void))(*(_DWORD *)enumerator + 12))() )
    {
      (**(void (__thiscall ***)(_DWORD))enumerator)(0);
      entry_name_holder = v6;
      v25 = &g_CompatStringHolder_Vtable;
      Compat_StringHolderDestructor(&entry_name_holder);
      v25 = &g_PathEntry_Vtable;
      Compat_StringHolderConstructJoined(joined_path_holder, v7, entry_name_holder);
      if ( strcmp_(v8, a__34) && strcmp_(v9, a___1) )
      {
        if ( ((*(int (**)(void))(*(_DWORD *)enumerator + 4))() & 0x10) != 0 )
        {
          Compat_StringHolderConstructJoined(subdir_path_holder, v10, entry_name_holder);
          visit_result += Compat_FileSystemProcessDirectChildren((int (__thiscall ***)(_DWORD))file_system, v11);
          Compat_StringHolderScalarDeletingDtor((int)subdir_path_holder, 1);
          (*file_system)[6]();
          Compat_StringHolderConstructJoined(recurse_path_holder, v29, entry_name_holder);
          Compat_FileSystemWalkDirectoryTree((int)file_system, v12, a3);
          Compat_StringHolderScalarDeletingDtor((int)recurse_path_holder, 1);
        }
        else
        {
          file_visit_failed = *Compat_StringHolderConstructJoined(file_path_holder, a3, entry_name_holder);
          LOBYTE(file_visit_failed) = Compat_FileSystemVisitFile((DWORD *)file_system, v15, file_visit_failed) == -1;
          Compat_StringHolderScalarDeletingDtor((int)file_path_holder, 1);
          if ( (_BYTE)file_visit_failed )
          {
            Compat_StringHolderScalarDeletingDtor((int)joined_path_holder, 1);
            visit_result = -1;
            Compat_StringHolderScalarDeletingDtor((int)&entry_name_holder, 1);
            break;
          }
        }
      }
      Compat_StringHolderScalarDeletingDtor((int)joined_path_holder, 1);
      Compat_StringHolderScalarDeletingDtor((int)&entry_name_holder, 1);
      (*(void (**)(void))(*(_DWORD *)enumerator + 16))();
      FileSystem_WalkEntryListInvokingCleanup((int)&enumerator);
      if ( !enumerator )
        break;
    }
  }
  (*v17)[1]();
  Compat_StringHolderScalarDeletingDtor((int)&v22, 1);
  Compat_StringHolderScalarDeletingDtor((int)&v20, 1);
  return visit_result;
}
// 47774A: variable 'v4' is possibly undefined
// 4777B9: variable 'v6' is possibly undefined
// 4777D8: variable 'v7' is possibly undefined
// 4777E5: variable 'v8' is possibly undefined
// 4777FA: variable 'v9' is possibly undefined
// 477823: variable 'v10' is possibly undefined
// 47782C: variable 'v11' is possibly undefined
// 477875: variable 'v12' is possibly undefined
// 477905: variable 'v15' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477950) --------------------------------------------------------
signed int __fastcall Compat_FileSystemWalkDirectoryEntries(int a1, int a2)
{
  int (__fastcall ***v3)(_DWORD, const char *); // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int *v8; // ecx
  int *v9; // eax
  int v10; // ecx
  bool recurse_failed; // bl
  int callback_result; // ebx
  int v14; // esi
  int enumerator; // [esp+0h] [ebp-40h] BYREF
  int v16; // [esp+4h] [ebp-3Ch]
  int v17; // [esp+8h] [ebp-38h]
  _DWORD file_path_holder[2]; // [esp+Ch] [ebp-34h] BYREF
  _DWORD subdir_path_holder[2]; // [esp+14h] [ebp-2Ch] BYREF
  const char *entry_name_holder; // [esp+1Ch] [ebp-24h] BYREF
  int (**v21)(); // [esp+20h] [ebp-20h]
  const char *pattern_holder; // [esp+24h] [ebp-1Ch] BYREF
  int (**v23)(); // [esp+28h] [ebp-18h]

  pattern_holder = 0;
  v23 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&pattern_holder);
  v23 = &g_PathEntry_Vtable;
  Compat_StringHolderAppendText(&pattern_holder, asc_5024CE);
  enumerator = (**v3)(v3, pattern_holder);
  v16 = v4;
  v17 = 0;
  FileSystem_WalkEntryListInvokingCleanup((int)&enumerator);
  if ( enumerator )
  {
    while ( (*(int (**)(void))(*(_DWORD *)enumerator + 12))() )
    {
      (**(void (***)(void))enumerator)();
      entry_name_holder = 0;
      v21 = &g_CompatStringHolder_Vtable;
      Compat_StringHolderDestructor(&entry_name_holder);
      v21 = &g_PathEntry_Vtable;
      if ( strcmp_(v6, a__35) && strcmp_(v7, a___2) )
      {
        if ( ((*(int (**)(void))(*(_DWORD *)enumerator + 4))() & 0x10) != 0 )
        {
          v9 = Compat_StringHolderConstructJoined(subdir_path_holder, (int)v8, entry_name_holder);
          recurse_failed = Compat_FileSystemWalkDirectoryEntries(v10, *v9) == -1;
          Compat_StringHolderScalarDeletingDtor((int)subdir_path_holder, 1);
          if ( recurse_failed )
          {
            Compat_StringHolderScalarDeletingDtor((int)&entry_name_holder, 1);
            (*(void (**)(void))(*(_DWORD *)v16 + 4))();
            Compat_StringHolderScalarDeletingDtor((int)&pattern_holder, 1);
            return -1;
          }
        }
        else
        {
          v14 = *v8;
          Compat_StringHolderConstructJoined(file_path_holder, (int)v8, entry_name_holder);
          (*(void (**)(void))(v14 + 32))();
          Compat_StringHolderScalarDeletingDtor((int)file_path_holder, 1);
        }
      }
      Compat_StringHolderScalarDeletingDtor((int)&entry_name_holder, 1);
      (*(void (**)(void))(*(_DWORD *)enumerator + 16))();
      FileSystem_WalkEntryListInvokingCleanup((int)&enumerator);
      if ( !enumerator )
        break;
    }
  }
  callback_result = (*(int (__fastcall **)(int, int))(*(_DWORD *)v5 + 28))(v5, a2);
  (*(void (**)(void))(*(_DWORD *)v16 + 4))();
  Compat_StringHolderScalarDeletingDtor((int)&pattern_holder, 1);
  return callback_result;
}
// 477991: variable 'v3' is possibly undefined
// 47799C: variable 'v4' is possibly undefined
// 4779FB: variable 'v6' is possibly undefined
// 477A0D: variable 'v7' is possibly undefined
// 477A32: variable 'v8' is possibly undefined
// 477A3B: variable 'v10' is possibly undefined
// 477A7F: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477B20) --------------------------------------------------------
int __fastcall Compat_FileSystemCloseQuery(int a1, int query)
{
  int result; // eax

  result = query;
  if ( query )
    return (*(int (__cdecl **)(int))(*(_DWORD *)query + 20))(a1);
  return result;
}

//----- (00477B40) --------------------------------------------------------
int  Compat_FileSystemInvokeInnerHandleMethod(int wrapper, int method_arg)
{
  int v2; // ecx

  (*(void (__cdecl **)(int))(**(_DWORD **)(wrapper + 4) + 4))(method_arg);
  return v2;
}
// 477B4E: variable 'v2' is possibly undefined

//----- (00477B60) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot16(int entry)
{
  return (*(int (**)(void))(**(_DWORD **)entry + 16))();
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (00477B80) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot32(int entry)
{
  return (*(int (**)(void))(**(_DWORD **)entry + 32))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477BA0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot24(int entry)
{
  return (*(int (**)(void))(**(_DWORD **)entry + 24))();
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (00477BC0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot28(int entry)
{
  return (*(int (**)(void))(**(_DWORD **)entry + 28))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477BE0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot0(int (****mount_entry)(void))
{
  return (***mount_entry)();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477C00) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot0(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))Compat_FileSystemMountInvokeSlot0);
}

//----- (00477C20) --------------------------------------------------------
int  Compat_FileSystemForEachMountPrintSearchResult(int mount_table, int open_mode)
{
  g_FileSystemMountOpenMode = open_mode;
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))FileSystem_TryOpenEntryCallback);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477C40) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot16(int mount_table, int open_mode)
{
  g_FileSystemMountOpenMode = open_mode;
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))Compat_FileSystemMountInvokeSlot16);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477C60) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot32(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot32);
}

//----- (00477C80) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot24(int mount_table, int open_mode)
{
  g_FileSystemMountOpenMode = open_mode;
  return FileSystem_ResolveAndInvokeForPath(mount_table, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot24);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477CA0) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot28(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot28);
}

//----- (00477CC0) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeCallback(int mount_table)
{
  return FileSystem_ResolveAndInvokeForPath(mount_table, 0, (int (*)(void))FileSystem_CallEntryOpSlot12);
}

//----- (00477CE0) --------------------------------------------------------
_DWORD * Compat_FileStreamOpen(_DWORD *stream, const CHAR *file_path, int a3, char mode_flags, DWORD a5)
{
  char *mode_string; // edx

  *stream = g_CompatFileStream_VTable;
  if ( (mode_flags & 0x10) != 0 )
  {
    if ( (mode_flags & 2) != 0 )
      mode_string = aAb_0;
    else
      mode_string = aA_3;
  }
  else if ( (mode_flags & 8) != 0 )
  {
    if ( (mode_flags & 2) != 0 )
      mode_string = aWb_8;
    else
      mode_string = aW_7;
  }
  else if ( (mode_flags & 2) != 0 )
  {
    mode_string = aRb_10;
  }
  else
  {
    mode_string = aR_7;
  }
  stream[1] = IO_FOpen(file_path, (unsigned __int8 *)mode_string, a3, a5);
  if ( (mode_flags & 0x20) != 0 )
    Compat_StreamSetBuffer((int)stream[1], 0x1800);
  return stream;
}
// 5109C4: using guessed type int (*off_5109C4[9])();

//----- (00477D60) --------------------------------------------------------
_DWORD * Compat_FileStreamRelease(_DWORD *result, char flags)
{
  int stream_handle; // ebx
  int v4; // ecx
  int v5; // ecx
  int v7; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatFileStream_DtorArrayDescriptor);
    j_j__nfree_();
    return (_DWORD *)v4;
  }
  stream_handle = result[1];
  *result = g_CompatFileStream_VTable;
  if ( stream_handle )
  {
    fclose_(stream_handle);
    if ( (flags & 2) == 0 )
      return (_DWORD *)v5;
    goto LABEL_8;
  }
  if ( (flags & 2) != 0 )
  {
LABEL_8:
    j__nfree_();
    return (_DWORD *)v7;
  }
  return result;
}
// 477D8F: variable 'v4' is possibly undefined
// 477DA0: variable 'v5' is possibly undefined
// 477DAC: variable 'v7' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5109C4: using guessed type int (*off_5109C4[9])();

//----- (00477DC0) --------------------------------------------------------
int Compat_FileStreamRead(int stream, void *buffer, int a3)
{
  return fread_(buffer, 1, *(_DWORD *)(stream + 4), a3);
}

//----- (00477DE0) --------------------------------------------------------
int  Compat_FileStreamReadChar(int stream, unsigned int a2)
{
  int stream_ptr;
  unsigned __int8 next_byte;

  (void)a2;
  stream_ptr = *(_DWORD *)(stream + 4);
  if ( *(_DWORD *)(stream_ptr + 4) > 0 )
  {
    next_byte = *(unsigned __int8 *)*(_DWORD *)stream_ptr;
    if ( (unsigned int)(next_byte - 13) > 0xFD )
    {
      --*(_DWORD *)(stream_ptr + 4);
      ++*(_DWORD *)stream_ptr;
      return next_byte;
    }
  }
  if ( Compat_StreamRead(stream_ptr, &next_byte, 1) == 1 )
    return next_byte;
  return -1;
}

//----- (00477E30) --------------------------------------------------------
signed int  Compat_FileStreamUngetChar(int stream, signed int pushed_char)
{
  return CRT_FlushBufferAndPutChar(pushed_char, stream);
}

//----- (00477E40) --------------------------------------------------------
int  Compat_FileStreamWrite(int stream, const void *buffer, int a3)
{
  return fwrite_(buffer, 1, *(_DWORD *)(stream + 4), a3);
}

//----- (00477E60) --------------------------------------------------------
signed int  Compat_FileStreamSeekFromStart(int stream, int offset, int a3)
{
  return IO_SeekStreamGuarded(*(_DWORD *)(stream + 4), offset, 0, a3);
}

//----- (00477E70) --------------------------------------------------------
signed int  Compat_FileStreamSeekFromEnd(int stream, int offset, int a3)
{
  return IO_SeekStreamGuarded(*(_DWORD *)(stream + 4), offset, 2u, a3);
}

//----- (00477E80) --------------------------------------------------------
int __fastcall Compat_FileStreamTell(int stream, int a2)
{
  return Compat_StreamTell(*(_DWORD *)(stream + 4));
}

//----- (00477E90) --------------------------------------------------------
signed int  Compat_FileStreamIsReady(int stream)
{
  int stream_handle; // edx

  stream_handle = *(_DWORD *)(stream + 4);
  if ( !stream_handle )
    return -2;
  if ( (*(_BYTE *)(stream_handle + 12) & 0x10) != 0 )
    return -1;
  return 1;
}

//----- (00477EC0) --------------------------------------------------------
int  Compat_FileFinderOpen(_DWORD *finder, int search_path)
{
  int v2; // ecx
  signed int find_handle; // eax
  int v4; // ecx
  int v5; // ecx
  const char *pattern_holder; // [esp+0h] [ebp-18h] BYREF
  int (**vtable_ptr)(); // [esp+4h] [ebp-14h]
  int search_path_saved; // [esp+10h] [ebp-8h]

  search_path_saved = search_path;
  finder[71] = -1;
  *finder = g_CompatFileFinder_VTable;
  pattern_holder = 0;
  vtable_ptr = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&pattern_holder);
  vtable_ptr = &g_PathEntry_Vtable;
  Compat_StringHolderAppendText(&pattern_holder, a__31);
  find_handle = CRT_FindFirstFile(pattern_holder, (_DWORD *)(v2 + 4), v2);
  *(_DWORD *)(v4 + 284) = find_handle;
  *(_DWORD *)(v4 + 288) = find_handle;
  Compat_StringHolderScalarDeletingDtor((int)&pattern_holder, 1);
  return v5;
}
// 477F06: variable 'v2' is possibly undefined
// 477F0E: variable 'v4' is possibly undefined
// 477F26: variable 'v5' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 5109F4: using guessed type int (*off_5109F4[6])();

//----- (00477F30) --------------------------------------------------------
_DWORD * Compat_FileFinderRelease(_DWORD *result, char flags)
{
  int find_handle; // ebx
  int v4; // ecx
  int v5; // ecx
  char v6; // dl
  int v7; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatFileFinder_DtorArrayDescriptor);
    j_j__nfree_();
    return (_DWORD *)v4;
  }
  find_handle = result[71];
  *result = g_CompatFileFinder_VTable;
  if ( find_handle == -1 )
  {
    findclose_(result);
    if ( (v6 & 2) == 0 )
      return (_DWORD *)v5;
    goto LABEL_8;
  }
  if ( (flags & 2) != 0 )
  {
LABEL_8:
    j__nfree_();
    return (_DWORD *)v7;
  }
  return result;
}
// 477F63: variable 'v4' is possibly undefined
// 477F6F: variable 'v6' is possibly undefined
// 477F74: variable 'v5' is possibly undefined
// 477F80: variable 'v7' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 489F44: using guessed type int __thiscall findclose_(_DWORD);
// 5109F4: using guessed type int (*off_5109F4[6])();

//----- (00477F90) --------------------------------------------------------
int  Compat_FileFinderHasEntry(int result)
{
  if ( *(_DWORD *)(result + 288) == -1 )
    return 0;
  return result;
}

//----- (00477FA0) --------------------------------------------------------
int  Compat_FileFinderAdvance(int finder)
{
  int result; // eax
  int v2; // ecx

  result = findnext_(finder, finder + 4);
  *(_DWORD *)(v2 + 288) = result;
  return result;
}
// 477FB2: variable 'v2' is possibly undefined
// 489F5D: using guessed type int __fastcall findnext_(_DWORD, _DWORD);

//----- (00477FC0) --------------------------------------------------------
int  Compat_FileFinderGetName(int finder)
{
  return finder + 24;
}

//----- (00477FD0) --------------------------------------------------------
int  Compat_FileFinderGetAttributes(int finder)
{
  return *(_DWORD *)(finder + 4);
}

//----- (00477FE0) --------------------------------------------------------
int  Compat_FileFinderGetSize(int finder)
{
  return *(_DWORD *)(finder + 20);
}

//----- (00477FF0) --------------------------------------------------------
int  Compat_FileFinderCreate(int search_path, char a2, DWORD alloc_context)
{
  _DWORD *finder; // eax
  int v5; // ecx
  int v6; // ecx

  finder = (_DWORD *)Mem_Alloc(292, search_path, a2, alloc_context);
  if ( finder )
    finder = (_DWORD *)Compat_FileFinderOpen(finder, v5);
  if ( (*(int (__cdecl **)(int))(*finder + 12))(search_path) )
    return v6;
  (*(void (__fastcall **)(int, int))(*(_DWORD *)v6 + 20))(v6, 2);
  return 0;
}
// 478010: variable 'v5' is possibly undefined
// 47800C: variable 'v6' is possibly undefined

//----- (00478030) --------------------------------------------------------
const char ** FileSystem_DiskMountCtor(const char **mount, int root_path)
{
  const char *path_text;
  unsigned int path_len;

  *(_DWORD *)(mount + 4) = 0;
  *(_DWORD *)(mount + 8) = (int)&g_PathEntry_Vtable;
  *(_DWORD *)mount = (int)g_FileSystemDiskMount_VTable;
  if ( !root_path )
    return mount;
  Compat_StringHolderDestructor((const char **)(uintptr_t)((unsigned int)(uintptr_t)mount + 4));
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)((unsigned int)(uintptr_t)mount + 4));
  path_len = path_text ? (unsigned int)strlen(path_text) : 0;
  if ( !path_len || path_text[path_len - 1] == 92 )
    return mount;
  Compat_StringHolderAppendText((const char **)(uintptr_t)((unsigned int)(uintptr_t)mount + 4), asc_5024EA);
  return mount;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510A14: using guessed type int (*off_510A14[4])();

//----- (004780A0) --------------------------------------------------------
int  FileSystem_DiskMountScalarDeletingDtor(_DWORD *mount, char flags)
{
  int v3; // eax
  int v5; // ecx
  int v6; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(mount, &g_FileSystemDiskMount_DtorArrayDescriptor);
    j_j__nfree_();
    return v5;
  }
  else
  {
    *mount = g_FileSystemDiskMount_VTable;
    v3 = Compat_StringHolderScalarDeletingDtor((int)(mount + 1), 0);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v6;
    }
    else
    {
      return v3 - 4;
    }
  }
}
// 4780D7: variable 'v5' is possibly undefined
// 4780E3: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510A14: using guessed type int (*off_510A14[4])();

//----- (004780F0) --------------------------------------------------------
int  FileSystem_DiskMountOpenFileQuery(int mount, char mode_flags, DWORD alloc_context)
{
  _DWORD *result; // ecx
  _DWORD joined_path[2]; // [esp+0h] [ebp-8h] BYREF

  joined_path[0] = 0;
  joined_path[1] = &g_CompatStringHolder_Vtable;
  result = (_DWORD *)Mem_Alloc(8, mount, mode_flags, alloc_context);
  if ( result )
  {
    Compat_StringHolderConstructJoined(joined_path, (_DWORD *)(uintptr_t)(unsigned int)(mount + 4), 0);
    result = Compat_FileStreamOpen(result, (const CHAR *)(uintptr_t)(unsigned int)joined_path[0], 0, mode_flags, alloc_context);
  }
  Compat_StringHolderDestroyStack(joined_path, 1);
  return (int)result;
}

//----- (00478140) --------------------------------------------------------
int __fastcall FileSystem_DiskMountDeleteFile(int mount, const char *file_name)
{
  int v3; // ecx
  char v4; // dl
  int v5; // ecx
  _DWORD joined_path[4]; // [esp-Ch] [ebp-10h] BYREF

  joined_path[2] = mount;
  Compat_StringHolderConstructJoined(joined_path, mount, file_name);
  IO_RemoveFileByPath(v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)joined_path, v4);
  return v5;
}
// 478158: variable 'v3' is possibly undefined
// 478161: variable 'v4' is possibly undefined
// 478166: variable 'v5' is possibly undefined
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);

//----- (00478170) --------------------------------------------------------
int __fastcall FileSystem_DiskMountCreateDirectory(int mount, const char *dir_name)
{
  const CHAR **v3; // eax
  char v4; // dl
  int v5; // ecx
  _DWORD joined_path[3]; // [esp-Ch] [ebp-Ch] BYREF

  joined_path[2] = mount;
  v3 = (const CHAR **)Compat_StringHolderConstructJoined(joined_path, mount, dir_name);
  CRT_MakeDirectory(*v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)joined_path, v4);
  return v5;
}
// 478190: variable 'v4' is possibly undefined
// 478195: variable 'v5' is possibly undefined

//----- (004781A0) --------------------------------------------------------
int __fastcall FileSystem_DiskMountRemoveDirectory(int mount, const char *dir_name)
{
  const CHAR **v3; // eax
  char v4; // dl
  int v5; // ecx
  _DWORD joined_path[4]; // [esp-Ch] [ebp-10h] BYREF

  joined_path[2] = mount;
  v3 = (const CHAR **)Compat_StringHolderConstructJoined(joined_path, mount, dir_name);
  CRT_RemoveDirectory(*v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)joined_path, v4);
  return v5;
}
// 4781C1: variable 'v4' is possibly undefined
// 4781C6: variable 'v5' is possibly undefined

//----- (004781E0) --------------------------------------------------------
char *__thiscall FileSystem_DiskMountGetCurrentDirectory(void *this)
{
  char *suffix_cursor; // esi
  char *buffer_end; // edi
  char first_char; // al
  char second_char; // al

  (void)this;
  getcwd_(g_FileSystem_CurrentDirectoryBuffer, 100);
  if ( g_FileSystem_CwdBufferSentinel[strlen(g_FileSystem_CurrentDirectoryBuffer)] == 92 )
    return g_FileSystem_CurrentDirectoryBuffer;
  suffix_cursor = asc_5024EC;
  buffer_end = &g_FileSystem_CurrentDirectoryBuffer[strlen(g_FileSystem_CurrentDirectoryBuffer)];
  do
  {
    first_char = *suffix_cursor;
    *buffer_end = *suffix_cursor;
    if ( !first_char )
      break;
    second_char = suffix_cursor[1];
    suffix_cursor += 2;
    buffer_end[1] = second_char;
    buffer_end += 2;
  }
  while ( second_char );
  return g_FileSystem_CurrentDirectoryBuffer;
}
// 489FF2: using guessed type int __fastcall getcwd_(_DWORD, _DWORD);

//----- (00478250) --------------------------------------------------------
int __thiscall FileSystem_DiskMountDirectoryExists(void *this)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int find_data; // [esp-118h] [ebp-130h] BYREF
  const char *search_pattern; // [esp+0h] [ebp-18h] BYREF
  int (**vtable_ptr)(); // [esp+4h] [ebp-14h]
  void *this_saved; // [esp+10h] [ebp-8h]

  this_saved = this;
  search_pattern = 0;
  vtable_ptr = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&search_pattern);
  vtable_ptr = &g_PathEntry_Vtable;
  if ( search_pattern && *search_pattern && search_pattern[strlen(search_pattern) - 1] != 92 )
    Compat_StringHolderAppendText(&search_pattern, asc_5024EE);
  Compat_StringHolderAppendText(&search_pattern, a__36);
  if ( CRT_FindFirstFile(search_pattern, &find_data, v1) == -1 )
  {
    Compat_StringHolderScalarDeletingDtor((int)&search_pattern, 1);
    return 0;
  }
  else
  {
    findclose_(v2);
    Compat_StringHolderScalarDeletingDtor((int)&search_pattern, 1);
    return v3;
  }
}
// 4782AC: variable 'v1' is possibly undefined
// 4782B6: variable 'v2' is possibly undefined
// 4782CE: variable 'v3' is possibly undefined
// 489F44: using guessed type int __thiscall findclose_(_DWORD);
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478340) --------------------------------------------------------
char  FileSystem_DiskMountResolveRegisteredRootPath(int mount, int mount_table)
{
  const char *resolved_path; // eax

  resolved_path = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(mount + 4);
  if ( !resolved_path || !*resolved_path )
    Compat_StringHolderCopyText((_DWORD *)(mount + 4), (const char *)(uintptr_t)(unsigned int)Compat_FileSystemFindMountedPathById(mount_table, mount));
  return mount_table;
}

//----- (00478370) --------------------------------------------------------
const char ** FileSystem_DiskMountCreate(int root_path, char a2, DWORD alloc_context)
{
  const char **result; // eax

  result = (const char **)Mem_Alloc(12, root_path, a2, alloc_context);
  if ( result )
    return FileSystem_DiskMountCtor(result, root_path);
  return result;
}

//----- (004783B0) --------------------------------------------------------
int  FileSystem_DiskMountRegisterNestedMount(int mount, int *mount_table, char a3, DWORD alloc_context)
{
  _DWORD *stream_buf; // eax

  stream_buf = IO_StreambufAlloc(mount, a3, alloc_context);
  return FileSystem_AddMountEntry(
           mount_table,
           (const CHAR *)(uintptr_t)(unsigned int)*(_DWORD *)(mount + 4),
           0,
           (DWORD)stream_buf);
}

//----- (004783D0) --------------------------------------------------------
int  FileSystem_DiskMountVariantScalarDeletingDtor(_DWORD *mount, char flags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(mount, &g_FileSystemDiskMountVariant_DtorArrayDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = FileSystem_DiskMountScalarDeletingDtor(mount, 1);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 478400: variable 'v4' is possibly undefined
// 47840A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00478410) --------------------------------------------------------
int  FileSystem_ArchiveGenerateBlankRecord(int record)
{
  int v1; // edx

  FileSystem_ArchiveFillBlankRecordBytes(record);
  return v1;
}
// 478418: variable 'v1' is possibly undefined

//----- (00478420) --------------------------------------------------------
int  FileSystem_ArchiveFillBlankRecordBytes(int record)
{
  __int64 v2; // rax
  int record_end; // ecx

  HIDWORD(v2) = record;
  record_end = record + 26;
  do
  {
    v2 = rand_(record_end, HIDWORD(v2) + 1);
    *(_BYTE *)(HIDWORD(v2) - 1) = v2;
  }
  while ( HIDWORD(v2) != record_end );
  *(_DWORD *)(record + 14) = 0;
  return v2;
}
// 478431: variable 'v3' is possibly undefined
// 47619A: using guessed type __int64 __fastcall rand_(_DWORD, _DWORD);

//----- (00478450) --------------------------------------------------------
const char ** FileSystem_PathTrimToParentDir(const char **path_holder)
{
  const char *text; // eax
  int v3; // edx
  unsigned int text_len; // ecx

  *path_holder = 0;
  path_holder[1] = (const char *)&g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(path_holder);
  path_holder[1] = (const char *)&g_PathEntry_Vtable;
  if ( Compat_StringHolderFindLastBackslash((_BYTE **)path_holder) == -1 )
  {
    Compat_StringHolderDestructor(path_holder);
    return path_holder;
  }
  else
  {
    text = (const char *)ExcString_GetTextPtr((int)path_holder);
    if ( text )
      text_len = strlen(text);
    else
      text_len = 0;
    Compat_StringHolderRemoveRange(path_holder, v3, text_len, text_len - v3);
    return path_holder;
  }
}
// 4784A9: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004784E0) --------------------------------------------------------
_DWORD * FileSystem_PathExtractFileName(_DWORD *path_holder)
{
  int slash_index; // eax
  unsigned int v3; // ecx

  *path_holder = 0;
  path_holder[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(path_holder);
  path_holder[1] = &g_PathEntry_Vtable;
  slash_index = Compat_StringHolderFindLastBackslash((_BYTE **)path_holder);
  if ( slash_index != -1 )
    Compat_StringHolderRemoveRange((const char **)path_holder, 0, v3, slash_index + 1);
  return path_holder;
}
// 478524: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478540) --------------------------------------------------------
int * FileSystem_ArchiveRecordCacheCtor(int *cache, int stream, int base_offset, int record_count)
{
  int total_records; // edx
  int window_size; // eax
  int capacity; // ecx
  int *result; // eax

  cache[3] = 0;
  *cache = record_count;
  cache[5] = stream;
  total_records = *cache;
  cache[6] = base_offset;
  if ( total_records >= 200 )
    window_size = 200;
  else
    window_size = total_records;
  cache[2] = window_size;
  cache[4] = Compat_WcppCtorArrayStorage1m(
            (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(26 * cache[2]),
            cache[2],
            &g_FileSystemArchiveRecordCache_CtorArrayDescriptor);
  capacity = cache[2];
  cache[1] = capacity;
  result = cache;
  cache[1] = -capacity;
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00478590) --------------------------------------------------------
_DWORD * FileSystem_ArchiveRecordCacheCopyCtor(int *cache, int *source_cache)
{
  int record_count; // eax
  int base_offset; // eax
  int total_records; // edx
  int window_size; // eax
  int records_buffer; // eax
  _DWORD *v9; // ecx
  int capacity; // ebx
  _DWORD *result; // eax

  record_count = *source_cache;
  cache[3] = 0;
  *cache = record_count;
  cache[5] = source_cache[5];
  base_offset = source_cache[6];
  total_records = *cache;
  cache[6] = base_offset;
  if ( total_records >= 200 )
    window_size = 200;
  else
    window_size = total_records;
  cache[2] = window_size;
  records_buffer = Compat_WcppCtorArrayStorage1m(
         (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(26 * cache[2]),
         cache[2],
         &g_FileSystemArchiveRecordCache_CtorArrayDescriptor);
  cache[4] = records_buffer;
  capacity = cache[2];
  cache[1] = capacity;
  result = (_DWORD *)cache;
  cache[1] = -capacity;
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (004785F0) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheDestruct(_DWORD *cache)
{
  FileSystem_ArchiveRecordCacheFlushWindow(cache);
  j_j__nfree_(cache[4]);
  return (int)cache;
}

//----- (00478610) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheGetRecord(_DWORD *cache, int record_index)
{
  int window_start; // ebp

  ++g_FS_ArchiveRecordCacheAccessCount;
  window_start = cache[1];
  if ( record_index >= window_start && record_index < cache[2] + window_start )
    return cache[4] + 26 * (record_index - cache[1]);
  FileSystem_ArchiveRecordCacheLoadWindow(cache, record_index);
  ++g_FS_ArchiveRecordCacheMissCount;
  return cache[4] + 26 * (record_index - cache[1]);
}
// 54DD0C: using guessed type int dword_54DD0C;
// 54DD10: using guessed type int dword_54DD10;

//----- (00478670) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheLoadWindow(_DWORD *cache, int record_index)
{
  int window_start; // edx
  int *stream; // esi
  unsigned __int8 *records_buffer; // edi
  int result; // eax

  FileSystem_ArchiveRecordCacheFlushWindow(cache);
  window_start = record_index - cache[2] + 1;
  cache[1] = window_start;
  if ( window_start < 0 )
    cache[1] = 0;
  stream = (int *)cache[5];
  records_buffer = (unsigned __int8 *)cache[4];
  File_SeekIfPositionChangedMode1(stream, cache[6] + 26 * cache[1], (int)records_buffer);
  result = Compat_StreamRead(stream[2], records_buffer, 26 * cache[2]);
  if ( stream[5] )
  {
    Compat_QueryXorDecodeBuffer((int)stream, records_buffer, result);
  }
  stream[12] += result;
  return result;
}

//----- (004786E0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveRecordCacheFlushWindow(_DWORD *result)
{
  unsigned int window_bytes; // ebx
  int *stream; // esi
  const void *records_buffer; // edi

  if ( result[3] )
  {
    window_bytes = 26 * result[2];
    stream = (int *)result[5];
    records_buffer = (const void *)result[4];
    File_SeekIfPositionChangedMode2(stream, result[6] + 26 * result[1], (int)records_buffer);
    Res_StreamWriteWithXorCipher(stream, records_buffer, window_bytes, window_bytes);
    result[3] = 0;
  }
  return result;
}
// 47870B: variable 'v4' is possibly undefined
// 478710: variable 'v5' is possibly undefined

//----- (00478720) --------------------------------------------------------
int  FileSystem_ArchiveEntryCopyConstruct(_DWORD *entry, int source_reader)
{
  _DWORD *v3; // ecx
  int v4; // ecx

  *entry = 0;
  entry[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(entry);
  v3[1] = &g_PathEntry_Vtable;
  v3[2] = *(_DWORD *)(source_reader + 8);
  v3[3] = 0;
  FileSystem_ArchiveRecordCacheCopyCtor(v3 + 4, (int *)(source_reader + 16));
  FileSystem_ArchiveEntryReaderFlushHeader(source_reader);
  return v4;
}
// 47873A: variable 'v3' is possibly undefined
// 478765: variable 'v4' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478770) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderCtor(_DWORD *reader, int *stream, int base_offset, int data_size, const void *entry_name)
{
  int *cache_ptr; // eax
  int reader_base; // esi
  int bytes_read; // eax
  int result; // eax
  const char *name_text; // edx
  unsigned __int8 *header_buf; // [esp+0h] [ebp-10h]

  *reader = 0;
  reader[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderFreeText(reader);
  name_text = Compat_StringArgGetText(entry_name);
  if ( name_text && *name_text )
  {
    *reader = (int)(uintptr_t)j_Mem_Alloc((unsigned int)strlen(name_text) + 1);
    Compat_CopyPrefixN((char *)(uintptr_t)*reader, name_text, (unsigned int)strlen(name_text) + 1);
  }
  reader[1] = &g_PathEntry_Vtable;
  reader[3] = 0;
  cache_ptr = FileSystem_ArchiveRecordCacheCtor(reader + 4, (int)stream, base_offset + 4, (data_size - 4) / 0x1Au);
  reader_base = (int)(cache_ptr - 4);
  header_buf = (unsigned __int8 *)(cache_ptr - 2);
  File_SeekIfPositionChangedMode1(stream, base_offset, 0);
  bytes_read = Compat_StreamRead((int)stream, header_buf, 4);
  if ( stream[5] )
  {
    Compat_QueryXorDecodeBuffer((int)stream, header_buf, bytes_read);
    result = reader_base;
    stream[12] += bytes_read;
  }
  else
  {
    stream[12] += bytes_read;
    result = reader_base;
  }
  return result;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478830) --------------------------------------------------------
int  FileSystem_ArchiveIndexCreateEmpty(_DWORD *index, int stream, int record_count)
{
  int *cache_ptr; // edi
  int end_offset; // eax

  *index = 0;
  index[1] = &g_PathEntry_Vtable;
  index[2] = 0;
  index[3] = 0;
  cache_ptr = index + 4;
  end_offset = File_SeekStreamEndAndRecordPos(stream, (int)(index + 4));
  FileSystem_ArchiveRecordCacheCtor(cache_ptr, stream, end_offset + 4, record_count);
  FileSystem_ArchiveWritePaddingRecords((int)cache_ptr, record_count, (int)cache_ptr);
  return (int)cache_ptr;
}
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478880) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderScalarDeletingDtor(int reader)
{
  FileSystem_ArchiveEntryReaderFlushHeader(reader);
  return Compat_StringHolderScalarDeletingDtor(FileSystem_ArchiveRecordCacheDestruct((_DWORD *)(reader + 16)) - 16, 0);
}

//----- (004788A0) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderFlushHeader(int reader)
{
  int result; // eax
  int *stream; // esi
  const void *header_ptr; // edi

  FileSystem_ArchiveRecordCacheFlushWindow((_DWORD *)(reader + 16));
  result = *(_DWORD *)(reader + 12);
  if ( result )
  {
    stream = *(int **)(reader + 36);
    header_ptr = (const void *)(reader + 8);
    File_SeekIfPositionChangedMode2(stream, *(_DWORD *)(reader + 40) - 4, (int)header_ptr);
    result = Res_StreamWriteWithXorCipher(stream, header_ptr, 4, 4u);
    *(_DWORD *)(reader + 12) = 0;
  }
  return result;
}

//----- (004788F0) --------------------------------------------------------
unsigned int  FileSystem_ArchiveNameHash(int archive, const char **name_holder)
{
  const char *text;
  unsigned int hash_value;
  unsigned int text_len;
  unsigned int index;

  text = Compat_StringArgGetText((const void *)name_holder);
  if ( !text || !*text )
    return 0;
  hash_value = (unsigned __int8)*text;
  text_len = (unsigned int)strlen(text);
  index = 1;
  while ( index < text_len )
  {
    hash_value *= (unsigned __int8)text[index];
    ++index;
  }
  return hash_value % *(_DWORD *)(archive + 16);
}

//----- (00478950) --------------------------------------------------------
int  FileSystem_ArchiveHashTableFind(int archive, const char **name_holder)
{
  const char *text;
  unsigned int slot_index; // ecx
  _DWORD *table; // edi
  int entry; // esi

  text = Compat_StringArgGetText((const void *)name_holder);
  if ( !text || !*text )
    return 0;
  slot_index = FileSystem_ArchiveNameHash(archive, name_holder);
  table = (_DWORD *)(archive + 16);
  while ( 1 )
  {
    entry = FileSystem_ArchiveRecordCacheGetRecord(table, slot_index);
    if ( !*(_DWORD *)(entry + 14) )
      return 0;
    if ( !strncmp_(text, (const char *)(uintptr_t)entry, 13) )
      return entry;
    if ( slot_index )
      --slot_index;
    else
      slot_index = *table - 1;
  }
}
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);

//----- (004789C0) --------------------------------------------------------
unsigned int  FileSystem_ArchiveHashTableFindFreeSlot(int archive, const char **name_holder)
{
  unsigned int slot_index; // ecx
  _DWORD *table; // ebx

  slot_index = FileSystem_ArchiveNameHash(archive, name_holder);
  table = (_DWORD *)(archive + 16);
  while ( *(_DWORD *)(FileSystem_ArchiveRecordCacheGetRecord(table, slot_index) + 14) )
  {
    if ( slot_index )
      --slot_index;
    else
      slot_index = *table - 1;
  }
  return slot_index;
}

//----- (004789F0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveOpenEntryReader(int archive, const void *path_arg)
{
  const char *path_text;
  const char *leaf_text;
  int entry; // ecx
  _DWORD *result; // eax
  _DWORD leaf_holder[2]; // [esp+0h] [ebp-8h] BYREF
  _DWORD savedregs[4]; // [esp+8h] [ebp+0h] BYREF

  leaf_holder[0] = 0;
  leaf_holder[1] = (int)&g_PathEntry_Vtable;
  path_text = Compat_StringArgGetText(path_arg);
  if ( path_text && *path_text )
  {
    leaf_text = Compat_StrrchrChar(path_text, '\\');
    if ( leaf_text )
      ++leaf_text;
    else
      leaf_text = path_text;
    Compat_StringHolderCopyText(leaf_holder, leaf_text);
  }
  entry = FileSystem_ArchiveHashTableFind(archive, (const char **)leaf_holder);
  Compat_StringHolderDestroyStack(leaf_holder, 1);
  if ( !entry || (*(_DWORD *)(entry + 14) & 2) == 0 )
    return 0;
  result = (_DWORD *)Mem_Alloc(44, entry, path_arg, (DWORD)savedregs);
  if ( result )
    return (_DWORD *)FileSystem_ArchiveEntryReaderCtor(
                       result,
                       (int *)(uintptr_t)(unsigned int)*(_DWORD *)(archive + 36),
                       *(_DWORD *)(entry + 18),
                       *(_DWORD *)(entry + 22),
                       path_arg);
  return result;
}

//----- (00478A60) --------------------------------------------------------
signed int  FileSystem_ArchiveHashTableInsert(_DWORD *archive, const char **name_holder, int data_size, int entry_flags)
{
  unsigned int slot_index; // ebp
  int entry; // eax
  int entry_count; // edx

  if ( archive[2] == archive[4] - 1 || !*name_holder || !**name_holder )
    return -1;
  slot_index = FileSystem_ArchiveHashTableFindFreeSlot((int)archive, name_holder);
  entry = FileSystem_ArchiveRecordCacheGetRecord(archive + 4, slot_index);
  *(_BYTE *)(entry + 13) = 0;
  Compat_CopyPrefixN((char *)(uintptr_t)entry, *name_holder, 13);
  *(_DWORD *)(entry + 14) = entry_flags;
  *(_DWORD *)(entry + 18) = File_SeekStreamEndAndRecordPos(archive[9], (int)name_holder);
  *(_DWORD *)(entry + 22) = data_size;
  archive[7] = 1;
  entry_count = archive[2];
  archive[3] = 1;
  archive[2] = entry_count + 1;
  return slot_index;
}

//----- (00478B10) --------------------------------------------------------
int  FileSystem_ArchiveWritePaddingRecords(int archive, int record_count, int a3)
{
  int result; // eax
  int v6; // ecx
  const void *v7; // edx
  int v8; // ecx
  _BYTE blank_record[28]; // [esp-1Ch] [ebp-30h] BYREF
  _DWORD header_words[5]; // [esp+0h] [ebp-14h] BYREF

  header_words[3] = a3;
  header_words[0] = 0;
  Res_StreamWriteWithXorCipher(*(int **)(archive + 36), header_words, a3, 4u);
  result = FileSystem_ArchiveGenerateBlankRecord((int)blank_record);
  if ( record_count > 0 )
  {
    do
    {
      FileSystem_ArchiveFillBlankRecordBytes((int)blank_record);
      result = Res_StreamWriteWithXorCipher(*(int **)(archive + 36), v7, v6 + 1, 0x1Au);
    }
    while ( v8 < record_count );
  }
  return result;
}
// 478B51: variable 'v7' is possibly undefined
// 478B50: variable 'v6' is possibly undefined
// 478B58: variable 'v8' is possibly undefined

//----- (00478B70) --------------------------------------------------------
signed int  FileSystem_ArchiveInsertFileEntry(_DWORD *archive, const char **name_holder, int record_count)
{
  signed int result; // eax
  int v5; // ecx

  result = FileSystem_ArchiveHashTableInsert(archive, name_holder, 26 * record_count, 2);
  if ( result != -1 )
  {
    FileSystem_ArchiveWritePaddingRecords((int)archive, record_count, v5);
    return 0;
  }
  return result;
}
// 478B91: variable 'v5' is possibly undefined

//----- (00478BA0) --------------------------------------------------------
int  FileSystem_ArchiveInsertDirectoryEntry(_DWORD *archive, const char **name_holder)
{
  signed int slot_index; // eax

  slot_index = FileSystem_ArchiveHashTableInsert(archive, name_holder, 0, 1);
  if ( slot_index == -1 )
    return 0;
  else
    return FileSystem_ArchiveRecordCacheGetRecord(archive + 4, slot_index);
}

//----- (00478BD0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveEntryStreamCtor(_DWORD *result, int entry_record, int stream)
{
  int data_offset; // ecx
  int data_size; // edx

  data_offset = *(_DWORD *)(entry_record + 18);
  result[2] = 0;
  result[1] = data_offset;
  data_size = *(_DWORD *)(entry_record + 22);
  *result = g_FileSystemArchiveEntryStream_VTable;
  result[3] = data_size;
  result[4] = stream;
  return result;
}
// 510BD4: using guessed type int (*off_510BD4[10])();

//----- (00478BF0) --------------------------------------------------------
signed int  FileSystem_ArchiveStreamHasRemainingData(int stream)
{
  if ( *(_DWORD *)(stream + 8) == *(_DWORD *)(stream + 12) )
    return -1;
  else
    return 1;
}

//----- (00478C20) --------------------------------------------------------
int  FileSystem_ArchiveStreamReadBytes(_DWORD *stream, unsigned __int8 *buffer, int a3)
{
  int *source_stream; // edi
  int bytes_read; // ebx
  int remaining_bytes;
  int result; // eax

  if ( stream[3] == stream[2] )
    return 0;
  remaining_bytes = stream[3] - stream[2];
  if ( a3 > remaining_bytes )
    a3 = remaining_bytes;
  source_stream = (int *)stream[4];
  File_SeekIfPositionChangedMode1(source_stream, stream[2] + stream[1], (int)source_stream);
  bytes_read = Compat_StreamRead(source_stream[2], buffer, a3);
  if ( source_stream[5] )
    Compat_QueryXorDecodeBuffer((int)source_stream, buffer, bytes_read);
  source_stream[12] += bytes_read;
  result = bytes_read;
  stream[2] += bytes_read;
  return result;
}

//----- (00478CA0) --------------------------------------------------------
int FileSystem_ArchiveStreamNoOpFlush()
{
  return 0;
}

//----- (00478CB0) --------------------------------------------------------
int  FileSystem_ArchiveStreamReadByte(int stream, int a2)
{
  int result; // eax
  int *source_stream; // ecx
  int xor_key; // edi
  unsigned __int8 next_byte;

  if ( *(_DWORD *)(stream + 12) == *(_DWORD *)(stream + 8) )
    return -1;
  source_stream = *(int **)(stream + 16);
  File_SeekIfPositionChangedMode1(source_stream, *(_DWORD *)(stream + 8) + *(_DWORD *)(stream + 4), a2);
  ++*(_DWORD *)(stream + 8);
  if ( Compat_StreamRead(source_stream[2], &next_byte, 1) == 1 )
    result = next_byte;
  else
    result = -1;
  xor_key = source_stream[5];
  if ( xor_key )
    result ^= xor_key + source_stream[12];
  ++source_stream[12];
  return result;
}

//----- (00478D10) --------------------------------------------------------
signed int  Res_StreamPutBackDecodedByte(int entry_stream, int putback_byte)
{
  int source_stream; // eax
  signed int encoded_byte; // eax
  signed int result; // eax
  int v6; // ecx

  source_stream = *(_DWORD *)(entry_stream + 16);
  if ( putback_byte != -1 )
    --*(_DWORD *)(source_stream + 48);
  if ( *(_DWORD *)(source_stream + 20) )
    encoded_byte = putback_byte ^ (*(_DWORD *)(source_stream + 48) + *(_DWORD *)(source_stream + 20));
  else
    encoded_byte = putback_byte;
  result = CRT_FlushBufferAndPutChar(encoded_byte, putback_byte);
  if ( v6 != -1 )
    --*(_DWORD *)(entry_stream + 8);
  return result;
}
// 478D3E: variable 'v6' is possibly undefined

//----- (00478D70) --------------------------------------------------------
int  Res_StreamWriteBytes(int stream, const void *buffer, unsigned int a3)
{
  int result; // eax
  int v4; // ecx
  int new_length; // ebx

  result = Res_StreamWriteWithXorCipher(*(int **)(stream + 16), buffer, stream, a3);
  new_length = result + *(_DWORD *)(v4 + 12);
  *(_DWORD *)(v4 + 8) += result;
  *(_DWORD *)(v4 + 12) = new_length;
  return result;
}
// 478D7E: variable 'v4' is possibly undefined

//----- (00478D90) --------------------------------------------------------
int  Res_StreamSeekClamped(int result, int position)
{
  int stream_length; // ecx

  if ( position < 0 )
  {
    *(_DWORD *)(result + 8) = 0;
  }
  else
  {
    stream_length = *(_DWORD *)(result + 12);
    if ( position <= stream_length )
      *(_DWORD *)(result + 8) = position;
    else
      *(_DWORD *)(result + 8) = stream_length;
  }
  return result;
}

//----- (00478DB0) --------------------------------------------------------
int  File_DirNodeScalarDtor(_DWORD *node, char flags, DWORD a3)
{
  int v4; // ecx
  int v6; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(node, &g_FileDirNode_DtorArrayDescriptor);
    j_j__nfree_();
    return v6;
  }
  else
  {
    *node = g_FileDirNode_VTable;
    File_ApplyResolvedEntryFlag(node[4], node[3], a3);
    if ( (flags & 2) != 0 )
      j__nfree_();
    return v4;
  }
}
// 478DD1: variable 'v4' is possibly undefined
// 478DE5: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510BA4: using guessed type int (*off_510BA4[4])();

//----- (00478E00) --------------------------------------------------------
_DWORD * Res_BuildTaggedRecordHeader(_DWORD *result, int version, int data_offset, int record_count)
{
  result[1] = version;
  result[3] = data_offset;
  result[2] = record_count;
  qmemcpy(result, aLlrs, sizeof(_DWORD));
  return result;
}

//----- (00478E30) --------------------------------------------------------
int  File_SourceEntryConstructor(_DWORD *node, int a2, int a3, DWORD a4)
{
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  _DWORD *v9; // eax
  _DWORD *v10; // ecx
  int v11; // ecx
  int path_holder; // [esp+0h] [ebp-14h] BYREF
  int (**vtable_ptr)(); // [esp+4h] [ebp-10h]
  int v14; // [esp+10h] [ebp-4h]

  v14 = a3;
  node[2] = 0;
  node[3] = 0;
  node[4] = -1;
  *node = g_FileCacheNode_VTable;
  node[1] = a2;
  path_holder = 0;
  vtable_ptr = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&path_holder);
  vtable_ptr = &g_PathEntry_Vtable;
  v5 = File_ResolveCachedPathEntry(*(_DWORD **)(v4 + 4), &path_holder, (const char *)v4, a4);
  *(_DWORD *)(v6 + 8) = v5;
  Compat_StringHolderScalarDeletingDtor((int)&path_holder, 1);
  if ( !*(_DWORD *)(v7 + 8) )
    return v7;
  v9 = (_DWORD *)Mem_Alloc(44, v7, 0, a4);
  if ( v9 )
    v9 = (_DWORD *)FileSystem_ArchiveEntryCopyConstruct(v9, v10[2]);
  v10[2] = v9;
  File_CacheNodeRebalance(v10);
  return v11;
}
// 478E7A: variable 'v4' is possibly undefined
// 478E87: variable 'v6' is possibly undefined
// 478E91: variable 'v7' is possibly undefined
// 478EAE: variable 'v10' is possibly undefined
// 478EC0: variable 'v11' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 510B14: using guessed type int (*off_510B14[6])();

//----- (00478ED0) --------------------------------------------------------
_DWORD * File_CacheNodeScalarDtor(_DWORD *node, char flags)
{
  int entry_reader; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(node, &g_FileCacheNode_DtorArrayDescriptor);
    j_j__nfree_();
    return (_DWORD *)v6;
  }
  *node = g_FileCacheNode_VTable;
  entry_reader = node[2];
  if ( entry_reader )
  {
    FileSystem_ArchiveEntryReaderScalarDeletingDtor(entry_reader);
    j__nfree_();
    if ( (flags & 2) == 0 )
      return (_DWORD *)v7;
  }
  else if ( (flags & 2) == 0 )
  {
    return node;
  }
  j__nfree_();
  return (_DWORD *)v8;
}
// 478F01: variable 'v6' is possibly undefined
// 478F17: variable 'v7' is possibly undefined
// 478F23: variable 'v8' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510B14: using guessed type int (*off_510B14[6])();

//----- (00478F30) --------------------------------------------------------
int  File_CacheNodeCheckChildHeight(int result)
{
  int child_node; // edx

  child_node = *(_DWORD *)(result + 8);
  if ( !child_node || *(_DWORD *)(child_node + 16) <= *(_DWORD *)(result + 16) )
    return 0;
  return result;
}

//----- (00478F50) --------------------------------------------------------
_DWORD * File_CacheNodeRebalance(_DWORD *cache_node)
{
  _DWORD *v1; // ecx
  int entry_reader; // eax
  int total_records; // edx
  _DWORD *result; // eax
  int record; // eax

  v1 = cache_node;
  ++cache_node[4];
  while ( 1 )
  {
    entry_reader = v1[2];
    total_records = *(_DWORD *)(entry_reader + 16);
    result = (_DWORD *)(entry_reader + 16);
    if ( total_records <= v1[4] )
      break;
    record = FileSystem_ArchiveRecordCacheGetRecord(result, v1[4]);
    v1[3] = record;
    result = *(_DWORD **)(record + 14);
    if ( result )
      break;
    ++v1[4];
  }
  return result;
}
// 478F58: variable 'v1' is possibly undefined

//----- (00478F90) --------------------------------------------------------
int  File_CacheNodeGetTag(int node)
{
  return *(_DWORD *)(node + 12);
}

//----- (00478FA0) --------------------------------------------------------
signed int  File_CacheNodeGetEntrySize(int node)
{
  if ( (*(_DWORD *)(*(_DWORD *)(node + 12) + 14) & 2) != 0 )
    return 16;
  else
    return FileSystem_ArchiveStreamNoOpFlush();
}

//----- (00478FC0) --------------------------------------------------------
int  File_CacheNodeGetChildTag(int node)
{
  return *(_DWORD *)(*(_DWORD *)(node + 12) + 22);
}

//----- (00478FD0) --------------------------------------------------------
int * File_SourceConstructFromStream(
        int *source,
        const CHAR *path,
        unsigned __int8 *mode,
        int a4,
        int a5,
        int a6)
{
  source[3] = 0;
  source[4] = (int)&g_PathEntry_Vtable;
  source[8] = 0;
  source[5] = a4;
  source[9] = 0;
  source[7] = a6;
  *source = (int)g_FileSource_VTable;
  File_SourceReadAndDecodeHeader(source, path, (int)mode, mode, a5);
  return source;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479020) --------------------------------------------------------
int * File_SourceBuildAndWriteHeader(
        int *source,
        const CHAR *path,
        int a3,
        int a4,
        DWORD heap_ctx,
        int a6)
{
  const CHAR *v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  _DWORD *v11; // eax
  _DWORD v13[6]; // [esp+0h] [ebp-18h] BYREF

  source[2] = 0;
  source[3] = 0;
  source[4] = (int)&g_PathEntry_Vtable;
  source[8] = 0;
  source[9] = 0;
  source[6] = a4;
  source[7] = a6;
  source[5] = a3;
  *source = (int)g_FileSource_VTable;
  CRT_DeleteFile(path, (int)path);
  source[2] = Res_OpenBufferedStreamForWrite(v7, 0, (unsigned __int8 *)aWB, heap_ctx);
  Res_BuildTaggedRecordHeader(v13, 1, v8, a4);
  source[13] = 0;
  File_SeekIfPositionChangedMode2(source, 0, a4);
  Res_StreamWriteWithXorCipher(source, v13, v9, 0x10u);
  v11 = (_DWORD *)Mem_Alloc(44, v10, 16, heap_ctx);
  if ( v11 )
    source[1] = FileSystem_ArchiveIndexCreateEmpty(v11, (int)source, a4);
  else
    source[1] = 0;
  return source;
}
// 479074: variable 'v7' is possibly undefined
// 479085: variable 'v8' is possibly undefined
// 4790A3: variable 'v9' is possibly undefined
// 4790AD: variable 'v10' is possibly undefined
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (004790E0) --------------------------------------------------------
int  File_SourceScalarDtor(_DWORD *a1, char flags)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v7; // ecx
  int v8; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileSource_DtorArrayDescriptor);
    j_j__nfree_();
    return v7;
  }
  else
  {
    *a1 = g_FileSource_VTable;
    File_CacheClearEntryTree((int)a1);
    v4 = *(_DWORD *)(v3 + 4);
    if ( v4 )
    {
      FileSystem_ArchiveEntryReaderScalarDeletingDtor(v4);
      j__nfree_();
    }
    v5 = Compat_StringHolderScalarDeletingDtor(v3 + 12, 0);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v8;
    }
    else
    {
      return v5 - 12;
    }
  }
}
// 4790F6: variable 'v3' is possibly undefined
// 47912F: variable 'v7' is possibly undefined
// 47913B: variable 'v8' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479140) --------------------------------------------------------
int  Res_OpenBufferedStreamForRead(const CHAR *path, int a2, unsigned __int8 *mode, DWORD heap_ctx)
{
  int stream_ptr;

  stream_ptr = IO_FOpen(path, mode, a2, heap_ctx);
  Compat_StreamSetBuffer(stream_ptr, 0x1800);
  return stream_ptr;
}

//----- (00479170) --------------------------------------------------------
int  Res_OpenBufferedStreamForWrite(const CHAR *path, int a2, unsigned __int8 *mode, DWORD heap_ctx)
{
  int stream_ptr;

  stream_ptr = IO_FOpen(path, mode, a2, heap_ctx);
  Compat_StreamSetBuffer(stream_ptr, 0x1800);
  return stream_ptr;
}

//----- (004791A0) --------------------------------------------------------
int  File_SourceReadAndDecodeHeader(
        int *source,
        const CHAR *path,
        int a3,
        unsigned __int8 *mode,
        int a5)
{
  int stream_ptr; // eax
  unsigned __int8 *v9; // esi
  int i; // ecx
  int raw_byte; // ebx
  unsigned __int8 decoded_byte; // al
  int v13; // ecx
  int v18; // eax
  _DWORD *v19; // esi
  _DWORD header[4]; // [esp+0h] [ebp-28h] BYREF
  _DWORD source_name_holder[2]; // [esp+10h] [ebp-18h] BYREF
  int bytes_read; // [esp+18h] [ebp-10h]
  int *v25; // [esp+1Ch] [ebp-Ch]
  int *v26; // [esp+20h] [ebp-8h]
  int *v27; // [esp+24h] [ebp-4h]
  _DWORD savedregs[4]; // [esp+28h] [ebp+0h] BYREF

  v26 = source;
  stream_ptr = Res_OpenBufferedStreamForRead(path, a3, mode, (DWORD)savedregs);
  v26[13] = 0;
  v25 = v26;
  v26[2] = stream_ptr;
  bytes_read = Compat_StreamRead(stream_ptr, header, 16);
  if ( v26[5] )
  {
    v9 = (unsigned __int8 *)header;
    v27 = v26;
    a5 = bytes_read;
    for ( i = v26[12]; a5; *(v9 - 1) = decoded_byte )
    {
      --a5;
      raw_byte = *v9++;
      decoded_byte = Res_XorDecodeByte((int)v27, i, raw_byte);
      i = v13 + 1;
    }
  }
  v25[12] += bytes_read;
  Compat_StreamSeek(v26[2], header[3], 1);
  v26[12] = Compat_StreamTell(v26[2]);
  v18 = Mem_Alloc(44, 0, 1, (DWORD)savedregs);
  v19 = (_DWORD *)v18;
  source_name_holder[0] = 0;
  source_name_holder[1] = (int)&g_PathEntry_Vtable;
  if ( v18 )
  {
    v18 = FileSystem_ArchiveEntryReaderCtor(v19, v26, v26[12], 26 * header[2] + 4, (const void *)source_name_holder);
  }
  else
  {
    v18 = 0;
  }
  v26[1] = v18;
  return v18;
}
// 479202: variable 'v13' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004792B0) --------------------------------------------------------
_DWORD * File_CacheNodeNewValidated(int a1, char a2, int a3, DWORD a4)
{
  _DWORD *v4; // eax
  int v5; // ecx
  _DWORD *v6; // ebx

  v4 = (_DWORD *)Mem_Alloc(20, a1, a2, a4);
  if ( v4 )
    v4 = (_DWORD *)File_SourceEntryConstructor(v4, v5, v5, a4);
  v6 = v4;
  if ( (*(int (__cdecl **)(int))(*v4 + 12))(a3) )
    return v6;
  (*(void (**)(void))(*v6 + 20))();
  return 0;
}
// 4792D8: variable 'v5' is possibly undefined

//----- (004792F0) --------------------------------------------------------
int  File_CacheTreeAdvanceSuccessor(_DWORD *a1)
{
  if ( a1[11] )
  {
    *(_DWORD *)(a1[11] + 4) = *(_DWORD *)(a1[10] + 4);
    *(_DWORD *)(a1[10] + 4) = a1[9];
    a1[9] = a1[10];
  }
  return *(_DWORD *)a1[9];
}

//----- (00479330) --------------------------------------------------------
int * File_CacheNodeFreeTree(int *node)
{
  int *v1; // ecx

  v1 = node;
  if ( *node )
  {
    FileSystem_ArchiveEntryReaderScalarDeletingDtor(*node);
    j__nfree_();
  }
  if ( v1[1] )
  {
    File_CacheNodeFreeTree((int *)v1[1]);
    j__nfree_();
  }
  return v1;
}
// 479353: conditional instruction was optimized away because ebx.4!=0
// 47934A: variable 'v1' is possibly undefined

//----- (00479370) --------------------------------------------------------
int * File_CacheTreeUnlinkLeftmost(int *result)
{
  int *v1; // ecx
  int i; // eax
  int v3; // eax
  int v4; // esi

  v1 = result;
  if ( result[9] )
  {
    result[11] = 0;
    for ( i = result[9]; ; i = *(_DWORD *)(v3 + 4) )
    {
      v1[10] = i;
      v3 = v1[10];
      if ( !*(_DWORD *)(v3 + 4) )
        break;
      v1[11] = v3;
    }
    v4 = v1[11];
    if ( v4 )
      *(_DWORD *)(v4 + 4) = 0;
    else
      v1[9] = 0;
    result = (int *)v1[10];
    if ( result )
    {
      File_CacheNodeFreeTree(result);
      result = (int *)j__nfree_();
    }
    --v1[8];
  }
  return result;
}
// 4793B1: variable 'v1' is possibly undefined

//----- (004793D0) --------------------------------------------------------
int  File_CacheInsertWithEviction(int *cache, int entry, char a3, DWORD heap_ctx)
{
  _DWORD *cache_node; // eax

  (void)a3;
  (void)heap_ctx;
  if ( !entry )
    return 0;
  while ( cache[8] >= cache[7] && cache[9] )
    File_CacheTreeUnlinkLeftmost(cache);
  cache_node = (_DWORD *)Mem_Alloc(8, (int)cache, 0, heap_ctx);
  if ( cache_node )
  {
    cache_node[0] = entry;
    cache_node[1] = cache[9];
  }
  cache[9] = (int)cache_node;
  ++cache[8];
  if ( !cache_node )
    return 0;
  return cache_node[0];
}

//----- (00479420) --------------------------------------------------------
int  File_ResolveCachedPathEntry(_DWORD *fs, _DWORD *path_holder, const char *a3, DWORD heap_ctx)
{
  const char *path_text;
  _DWORD *cache_node;
  int entry;
  const char *entry_name;
  const char *last_slash;
  size_t path_len;
  size_t parent_len;
  _DWORD parent_holder[2];
  int parent_entry;
  _DWORD *resolved_entry;

  (void)a3;
  path_text = Compat_StringHolderGetText(path_holder);
  if ( !path_text || !*path_text )
    return fs[1];
  fs[11] = 0;
  fs[10] = fs[9];
  cache_node = (_DWORD *)(uintptr_t)(unsigned int)fs[10];
  while ( cache_node )
  {
    entry = cache_node[0];
    entry_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)entry;
    if ( entry_name && !strcmp_(path_text, entry_name) )
      return File_CacheTreeAdvanceSuccessor(fs);
    fs[11] = (int)cache_node;
    fs[10] = cache_node[1];
    cache_node = (_DWORD *)(uintptr_t)(unsigned int)fs[10];
  }
  ++g_FS_PathEntryCacheMissCount;
  parent_holder[0] = 0;
  parent_holder[1] = (int)&g_PathEntry_Vtable;
  last_slash = Compat_StrrchrChar(path_text, '\\');
  if ( last_slash )
  {
    Compat_StringHolderCopyText(parent_holder, path_text);
    path_len = strlen(path_text);
    parent_len = (size_t)(last_slash - path_text);
    Compat_StringHolderRemoveRange((char **)parent_holder, (int)parent_len, (unsigned int)path_len, (int)(path_len - parent_len));
  }
  parent_entry = File_ResolveCachedPathEntry(fs, parent_holder, 0, heap_ctx);
  Compat_StringHolderDestroyStack(parent_holder, 1);
  if ( !parent_entry )
    return 0;
  resolved_entry = FileSystem_ArchiveOpenEntryReader(parent_entry, path_holder);
  if ( !resolved_entry )
    return 0;
  return File_CacheInsertWithEviction((int *)fs, (int)resolved_entry, 0, heap_ctx);
}
// 54DD18: using guessed type int dword_54DD18;

//----- (004794F0) --------------------------------------------------------
int  File_ResolvePathByParentAndLeaf(_DWORD *fs, const char *path, DWORD heap_ctx)
{
  _DWORD parent_path_holder[2]; // [esp+0h] [ebp-118h] BYREF
  _DWORD leaf_name_holder[2]; // [esp+8h] [ebp-110h] BYREF
  int parent_entry; // ebx
  int result; // ecx

  ++g_FS_ResolvePathByParentLeafCount;
  if ( !path || !*path )
    return 0;
  Compat_StringHolderBuildParentPath(parent_path_holder, path);
  parent_entry = File_ResolveCachedPathEntry(fs, parent_path_holder, 0, heap_ctx);
  Compat_StringHolderDestroyStack(parent_path_holder, 1);
  Compat_StringHolderBuildLeafName(leaf_name_holder, path);
  if ( parent_entry )
    result = FileSystem_ArchiveHashTableFind(parent_entry, (const char **)leaf_name_holder);
  else
    result = 0;
  Compat_StringHolderDestroyStack(leaf_name_holder, 1);
  return result;
}
// 54DD14: using guessed type int dword_54DD14;

//----- (00479560) --------------------------------------------------------
int  File_ResolveAbsolutePathEntry(const char *a1, DWORD a2)
{
  const char **v3; // eax
  char *v4; // ecx
  int v5; // ecx
  int result; // eax
  const char **v7; // eax
  int v8; // ecx
  int v9; // ebx
  int v10; // ecx
  _DWORD v11[2]; // [esp-8h] [ebp-18h] BYREF
  const char *v12[4]; // [esp+0h] [ebp-10h] BYREF

  v12[2] = a1;
  v3 = FileSystem_PathTrimToParentDir(v12);
  File_ResolveCachedPathEntry(v4, v3, v4, a2);
  Compat_StringHolderScalarDeletingDtor((int)v12, 1);
  if ( !v5 )
    return 0;
  v7 = (const char **)FileSystem_PathExtractFileName(v11);
  v9 = FileSystem_ArchiveHashTableFind(v8, v7);
  Compat_StringHolderScalarDeletingDtor((int)v11, 1);
  *(_DWORD *)(v10 + 28) = 1;
  result = v9;
  *(_DWORD *)(v10 + 12) = 1;
  return result;
}
// 479576: variable 'v4' is possibly undefined
// 47958D: variable 'v5' is possibly undefined
// 4795A4: variable 'v8' is possibly undefined
// 4795BA: variable 'v10' is possibly undefined

//----- (004795D0) --------------------------------------------------------
char  File_ApplyResolvedEntryFlag(int a1, int flag_value, DWORD heap_ctx)
{
  _DWORD *v4; // ecx

  *(_DWORD *)(File_ResolveAbsolutePathEntry((const char *)(a1 + 12), heap_ctx) + 22) = flag_value;
  return Compat_StringHolderDestructor(v4);
}
// 4795E8: variable 'v4' is possibly undefined

//----- (004795F0) --------------------------------------------------------
_DWORD * File_OpenNodeByFlags(char flags)
{
  char *v1; // ecx
  int resolvedEntry; // edi
  int v3; // ecx
  _DWORD *result; // eax
  int v5; // ecx
  int excStringField; // ebx
  const char **parentDir; // eax
  char *v8; // ecx
  _DWORD *parentEntry; // ebx
  int v10; // ecx
  int dirEntry; // edi
  _DWORD *v12; // ebx
  int v13; // ecx
  _DWORD *dirStream; // eax
  int v15; // ecx
  _DWORD *resultNode; // ebx
  int v17; // [esp+0h] [ebp-40h] BYREF
  int (**v18)(); // [esp+4h] [ebp-3Ch]
  int v19; // [esp+8h] [ebp-38h] BYREF
  int (**v20)(); // [esp+Ch] [ebp-34h]
  int v21; // [esp+10h] [ebp-30h] BYREF
  int (**v22)(); // [esp+14h] [ebp-2Ch]
  int v23; // [esp+18h] [ebp-28h] BYREF
  int (**v24)(); // [esp+1Ch] [ebp-24h]
  const char *parentDirPath[2]; // [esp+20h] [ebp-20h] BYREF
  const char *fileName[6]; // [esp+28h] [ebp-18h] BYREF

  v17 = 0;
  v18 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v17);
  v18 = &g_PathEntry_Vtable;
  resolvedEntry = File_ResolvePathByParentAndLeaf(v1, v1, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)&v17, 1);
  if ( resolvedEntry )
  {
    if ( (flags & 8) == 0 )
    {
      result = (_DWORD *)Mem_Alloc(20, v3, flags, (DWORD)&g_PathEntry_Vtable);
      if ( result )
      {
        result = FileSystem_ArchiveEntryStreamCtor(result, resolvedEntry, v5);
        *result = g_FileArchiveEntryStream_VTable;
      }
      return result;
    }
    return 0;
  }
  if ( (flags & 8) == 0 )
    return 0;
  excStringField = v3 + 12;
  if ( ExcString_GetTextPtr(v3 + 12) && *(_BYTE *)ExcString_GetTextPtr(excStringField) )
    return 0;
  v21 = 0;
  v22 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v21);
  v22 = &g_PathEntry_Vtable;
  parentDir = FileSystem_PathTrimToParentDir(parentDirPath);
  parentEntry = (_DWORD *)File_ResolveCachedPathEntry(v8, parentDir, v8, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)parentDirPath, 1);
  Compat_StringHolderScalarDeletingDtor((int)&v21, 1);
  v19 = 0;
  v20 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v19);
  v20 = &g_PathEntry_Vtable;
  FileSystem_PathExtractFileName(fileName);
  Compat_StringHolderScalarDeletingDtor((int)&v19, 1);
  if ( parentEntry && (dirEntry = FileSystem_ArchiveInsertDirectoryEntry(parentEntry, fileName)) != 0 )
  {
    v24 = &g_CompatStringHolder_Vtable;
    v23 = 0;
    v12 = (_DWORD *)(v10 + 12);
    Compat_StringHolderDestructor(&v23);
    v24 = &g_PathEntry_Vtable;
    ExcString_GetTextPtr((int)&v23);
    ExcString_ReleaseText(v12);
    Compat_StringHolderScalarDeletingDtor((int)&v23, 1);
    dirStream = (_DWORD *)Mem_Alloc(20, v13, (char)v12, (DWORD)&g_CompatStringHolder_Vtable);
    if ( dirStream )
    {
      dirStream = FileSystem_ArchiveEntryStreamCtor(dirStream, dirEntry, v15);
      *dirStream = g_FileDirNode_VTable;
    }
    resultNode = dirStream;
    Compat_StringHolderScalarDeletingDtor((int)fileName, 1);
    return resultNode;
  }
  else
  {
    Compat_StringHolderScalarDeletingDtor((int)fileName, 1);
    return 0;
  }
}
// 47961F: variable 'v1' is possibly undefined
// 479640: variable 'v3' is possibly undefined
// 47964D: variable 'v5' is possibly undefined
// 4796BB: variable 'v8' is possibly undefined
// 479749: variable 'v10' is possibly undefined
// 47977F: variable 'v13' is possibly undefined
// 47978C: variable 'v15' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 510B74: using guessed type int (*off_510B74[10])();
// 510BA4: using guessed type int (*off_510BA4[4])();

//----- (004797F0) --------------------------------------------------------
signed int  File_OpenEntryForWrite(int a1, int access_mode)
{
  int v2; // edx
  int v3; // ecx
  const char **v4; // eax
  char *v5; // ecx
  _DWORD *v6; // ecx
  signed int v7; // eax
  signed int v8; // ebx
  const char *v10[2]; // [esp+0h] [ebp-2Ch] BYREF
  int v11; // [esp+8h] [ebp-24h] BYREF
  int (**v12)(); // [esp+Ch] [ebp-20h]
  int v13; // [esp+10h] [ebp-1Ch] BYREF
  int (**v14)(); // [esp+14h] [ebp-18h]
  const char *v15[5]; // [esp+18h] [ebp-14h] BYREF

  if ( ExcString_GetTextPtr(a1 + 12) && *(_BYTE *)ExcString_GetTextPtr(v2) )
    return -1;
  if ( !access_mode )
    access_mode = *(_DWORD *)(v3 + 24);
  v13 = 0;
  v14 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v13);
  v14 = &g_PathEntry_Vtable;
  v4 = FileSystem_PathTrimToParentDir(v15);
  File_ResolveCachedPathEntry(v5, v4, v5, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)v15, 1);
  Compat_StringHolderScalarDeletingDtor((int)&v13, 1);
  v11 = 0;
  v12 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v11);
  v12 = &g_PathEntry_Vtable;
  FileSystem_PathExtractFileName(v10);
  Compat_StringHolderScalarDeletingDtor((int)&v11, 1);
  if ( v6 )
    v7 = FileSystem_ArchiveInsertFileEntry(v6, v10, access_mode);
  else
    v7 = -1;
  v8 = v7;
  Compat_StringHolderScalarDeletingDtor((int)v10, 1);
  return v8;
}
// 479810: variable 'v3' is possibly undefined
// 479848: variable 'v5' is possibly undefined
// 4798A1: variable 'v6' is possibly undefined
// 4798CA: variable 'v2' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004798F0) --------------------------------------------------------
int * File_CacheClearEntryTree(int a1)
{
  int v1; // ecx
  int *result; // eax

  fflush_(a1);
  result = *(int **)(v1 + 36);
  if ( result )
  {
    File_CacheNodeFreeTree(result);
    result = (int *)j__nfree_();
  }
  *(_DWORD *)(v1 + 36) = 0;
  *(_DWORD *)(v1 + 32) = 0;
  return result;
}
// 4798FB: variable 'v1' is possibly undefined
// 48A216: using guessed type int __thiscall fflush_(_DWORD);

//----- (00479930) --------------------------------------------------------
int  File_PrimePathCacheEntry(int a1, DWORD a2)
{
  char *v2; // ecx
  int v3; // ecx
  int v5; // [esp+0h] [ebp-18h] BYREF
  int (**v6)(); // [esp+4h] [ebp-14h]
  int v7; // [esp+10h] [ebp-8h]

  v7 = a1;
  v5 = 0;
  v6 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v5);
  v6 = &g_PathEntry_Vtable;
  File_ResolveCachedPathEntry(v2, &v5, v2, a2);
  Compat_StringHolderScalarDeletingDtor((int)&v5, 1);
  return v3;
}
// 47995B: variable 'v2' is possibly undefined
// 479975: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00479980) --------------------------------------------------------
int  File_SeekStreamEndAndRecordPos(int source, int heap_ctx)
{
  int result; // eax

  IO_SeekStreamGuarded(*(_DWORD *)(source + 8), 0, 2u, heap_ctx);
  result = Compat_StreamTell(*(_DWORD *)(source + 8));
  *(_DWORD *)(source + 48) = result;
  return result;
}

//----- (004799B0) --------------------------------------------------------
int * File_SeekIfPositionChangedMode1(int *result, int position, int heap_ctx)
{
  if ( position != result[12] || result[13] != 1 )
  {
    IO_SeekStreamGuarded(result[2], position, 0, heap_ctx);
    result[13] = 1;
    result[12] = position;
  }
  return result;
}

//----- (004799E0) --------------------------------------------------------
int * File_SeekIfPositionChangedMode2(int *result, int position, int heap_ctx)
{
  if ( position != result[12] || result[13] != 2 )
  {
    IO_SeekStreamGuarded(result[2], position, 0, heap_ctx);
    result[13] = 2;
    result[12] = position;
  }
  return result;
}

//----- (00479A10) --------------------------------------------------------
int  Res_StreamWriteWithXorCipher(int *stream, const void *buffer, int a3, unsigned int a4)
{
  unsigned int remaining; // ecx
  unsigned __int8 *v6; // eax
  int i; // edx
  int v8; // ecx
  int result; // eax
  int encoded_byte; // [esp+0h] [ebp-18h]
  unsigned __int8 *temp_buffer; // [esp+4h] [ebp-14h]

  if ( stream[5] )
  {
    temp_buffer = (unsigned __int8 *)j_Mem_Alloc(a3);
    qmemcpy(temp_buffer, buffer, a4);
    remaining = a4;
    v6 = temp_buffer;
    for ( i = stream[12]; remaining; *(v6 - 1) = encoded_byte )
    {
      --remaining;
      encoded_byte = (i + stream[5]) ^ *v6++;
      ++i;
    }
    fwrite_(temp_buffer, 1, stream[2], a4);
    j_j__nfree_();
    stream[12] += v8;
    return v8;
  }
  else
  {
    result = fwrite_(buffer, 1, stream[2], a4);
    stream[12] += result;
  }
  return result;
}
// 479AA7: variable 'v8' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00479AE0) --------------------------------------------------------
int * File_ConstructReadOnlySource(int *source, const CHAR *path, int a3, int a4, int a5)
{
  int *result; // eax

  result = File_SourceConstructFromStream(source, path, (unsigned __int8 *)aRb_11, a4, a5, a3);
  *result = (int)g_FileReadOnlySource_VTable;
  return result;
}
// 510C04: using guessed type int (*off_510C04[4])();

//----- (00479B00) --------------------------------------------------------
_DWORD * File_OpenMountRootEntry(int fs, char flags, DWORD heap_ctx)
{
  _DWORD *result; // eax
  int root_entry; // esi

  if ( (flags & 8) != 0 )
    return 0;
  root_entry = File_ResolvePathByParentAndLeaf((_DWORD *)fs, (const char *)(uintptr_t)(unsigned int)g_FileSystemStrippedPathHolderText, heap_ctx);
  if ( !root_entry )
    return 0;
  result = (_DWORD *)Mem_Alloc(20, fs, flags, heap_ctx);
  if ( result )
  {
    result = FileSystem_ArchiveEntryStreamCtor(result, root_entry, fs);
    *result = g_FileArchiveEntryStream_VTable;
  }
  return result;
}
// 510B74: using guessed type int (*off_510B74[10])();

//----- (00479BE0) --------------------------------------------------------
int * File_AllocateReadOnlySource(const CHAR *path, int a2, char cipher_key, DWORD heap_ctx, int a5)
{
  int *result; // eax

  result = (int *)Mem_Alloc(56, a2, cipher_key, heap_ctx);
  if ( result )
    return File_ConstructReadOnlySource(result, path, a2, cipher_key, a5);
  return result;
}

//----- (00479C20) --------------------------------------------------------
_DWORD * File_CacheNodeConstructBase(_DWORD *result)
{
  *result = g_FileCacheNode_VTable;
  return result;
}
// 510B14: using guessed type int (*off_510B14[6])();

//----- (00479C30) --------------------------------------------------------
int  Res_XorDecodeByte(int stream, int a2, int encoded_byte)
{
  return encoded_byte ^ (a2 + *(_DWORD *)(stream + 20));
}

//----- (00479C40) --------------------------------------------------------
unsigned __int8 * Compat_QueryXorDecodeBuffer(int stream, unsigned __int8 *buffer, int length)
{
  unsigned __int8 *result; // eax
  int i; // edx
  int decoded_byte; // [esp+0h] [ebp-10h]

  result = buffer;
  for ( i = *(_DWORD *)(stream + 48); length; *(result - 1) = decoded_byte )
  {
    --length;
    decoded_byte = (i + *(_DWORD *)(stream + 20)) ^ *result++;
    ++i;
  }
  return result;
}

//----- (00479C80) --------------------------------------------------------
_DWORD * Compat_QueryConstructDefault(int a1)
{
  _DWORD *v1; // eax
  _DWORD *result; // eax

  v1 = (_DWORD *)(a1 + 12);
  *v1 = 0;
  result = v1 - 3;
  result[4] = &g_PathEntry_Vtable;
  result[7] = 0;
  *result = g_FileSource_VTable;
  return result;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479CB0) --------------------------------------------------------
int  Compat_QuerySkipBytes(int query, int count)
{
  uintptr_t *vtable;

  if ( !query )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query;
  return ((int (*)(int, int))(uintptr_t)vtable[9])(query, count);
}

//----- (00479CC0) --------------------------------------------------------
int  Compat_QuerySkipBytesFromBase(int query, int offset)
{
  uintptr_t *vtable;

  if ( !query )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)query;
  return ((int (*)(int, int))(uintptr_t)vtable[9])(query, offset + *(_DWORD *)(query + 12));
}

//----- (00479CD0) --------------------------------------------------------
int  Compat_QueryGetLength(int query)
{
  return *(_DWORD *)(query + 8);
}

//----- (00479CE0) --------------------------------------------------------
int  Compat_QueryDestruct(int result, char flags)
{
  int v3; // ecx
  int v4; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatQuery_DtorArrayDescriptor);
    j_j__nfree_();
    return v3;
  }
  else if ( (flags & 2) != 0 )
  {
    j__nfree_();
    return v4;
  }
  return result;
}
// 479D09: variable 'v4' is possibly undefined
// 479D00: variable 'v3' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00479D20) --------------------------------------------------------
int  Compat_QueryCloseAndDestruct(_DWORD *query, char flags)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (flags & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(query, &g_CompatQueryCloseAndDestruct_DtorArrayDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = File_SourceScalarDtor(query, 1);
    if ( (flags & 2) != 0 )
    {
      j__nfree_();
      return v5;
    }
  }
  return result;
}
// 479D50: variable 'v4' is possibly undefined
// 479D5A: variable 'v5' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);

//----- (00479D60) --------------------------------------------------------
int Rules_InitFacts()
{
  Rules_InitFactHashTable();
  Rules_AddResetFunction((int)aFacts_0, (int)Rules_ResetFacts, 60);
  Rules_AddClearReadyFunction((int)aFacts_0, (int)Rules_ClearFacts, 0);
  Rules_AddPeriodicFunction((int)aFacts_0, (int)Rules_RemoveGarbageFacts, 0);
  Rules_RegisterFactsConstruct();
  Rules_AddWatchItem((int)aFacts_0, 0, 80, (int)&g_Rules_WatchFactsFlag, (int)Rules_ToggleFactWatchFlag, (int)Rules_WatchPrintFactsState);
  Rules_RegisterFactCommands();
  Rules_RegisterFactQueryFunctions();
  Rules_RegisterFactPatternNetworkPersistence();
  return Rules_RegisterFactPatternNetworkCodeGen();
}
// 51A150: using guessed type int dword_51A150;

//----- (00479DE0) --------------------------------------------------------
signed int __fastcall Rules_PrintFactWithIndex(int logicalName, int fact)
{
  int v3; // ecx
  int v4; // ecx
  _BYTE buffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v7; // [esp+14h] [ebp-8h]

  v7 = logicalName;
  sprintf_(buffer, "f-%-5ld ", *(_DWORD *)(fact + 24));
  Output_Write(v3, (int)buffer, v3);
  return Rules_PrintFact(v4, fact);
}
// 479E03: variable 'v3' is possibly undefined
// 479E0C: variable 'v4' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00479E20) --------------------------------------------------------
signed int __fastcall Rules_PrintFactLabel(int logicalName, int fact)
{
  int v2; // ecx
  _BYTE buffer[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v5; // [esp+14h] [ebp-8h]

  v5 = logicalName;
  sprintf_(buffer, "f-%ld", *(_DWORD *)(fact + 24));
  return Output_Write(v2, (int)buffer, v2);
}
// 479E41: variable 'v2' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00479E50) --------------------------------------------------------
signed int  Rules_PrintFactIdentifier(int logicalName, int fact)
{
  int v2; // ecx
  int v4; // ecx
  char *label_text; // edx
  signed int result; // eax
  int v7; // ecx

  v2 = logicalName;
  if ( g_Print_AddressesToStringsFlag )
    Output_Write(logicalName, (int)asc_502524, logicalName);
  if ( (void **)fact == &g_Rules_DummyFactPtr )
  {
    label_text = aDummyFact;
  }
  else
  {
    Output_Write(v2, (int)aFact_2, v2);
    Rules_PrintLongInteger(v4, *(_DWORD *)(fact + 24));
    label_text = asc_502530;
  }
  result = Output_Write(v2, (int)label_text, v2);
  if ( g_Print_AddressesToStringsFlag )
    return Output_Write(v7, (int)asc_502524, v7);
  return result;
}
// 479E6E: variable 'v2' is possibly undefined
// 479E78: variable 'v4' is possibly undefined
// 479EAF: variable 'v7' is possibly undefined
// 51A114: using guessed type void *off_51A114;
// 51A5FC: using guessed type int dword_51A5FC;

//----- (00479EC0) --------------------------------------------------------
int  Rules_DecrementFactRefCount(int result)
{
  --*(_DWORD *)(result + 8);
  return result;
}

//----- (00479ED0) --------------------------------------------------------
int  Rules_IncrementFactRefCount(int result)
{
  ++*(_DWORD *)(result + 8);
  return result;
}

//----- (00479EE0) --------------------------------------------------------
signed int  Rules_PrintFact(int logicalName, int fact)
{
  int v3; // ecx
  int v4; // ecx
  int multifield; // edi

  if ( (*(_BYTE *)(*(_DWORD *)(fact + 16) + 24) & 1) == 0 )
    return Rules_PrintTemplateFactSlots(logicalName, fact, fact);
  Output_Write(logicalName, (int)asc_502544, fact);
  Output_Write(logicalName, *(_DWORD *)(**(_DWORD **)(v3 + 16) + 16), v3);
  multifield = *(_DWORD *)(v4 + 56);
  if ( *(_DWORD *)(multifield + 6) )
  {
    Output_Write(logicalName, (int)asc_502548, v4);
    Lexer_OutputFieldRange(logicalName, multifield, *(_DWORD *)(multifield + 6) - 1, 0, 0);
  }
  return Output_Write(logicalName, (int)asc_50254C, v4);
}
// 479EFC: variable 'v3' is possibly undefined
// 479F0B: variable 'v4' is possibly undefined

//----- (00479F50) --------------------------------------------------------
int  Rules_NetworkAssertFact(int fact, double a2)
{
  return Rules_MatchFactAgainstPatternNetwork(fact, *(_DWORD *)(*(_DWORD *)(fact + 16) + 32), 0, 0, a2, 0);
}

//----- (00479F70) --------------------------------------------------------
signed int  Rules_RetractFact(int fact_ptr, double a2)
{
  uintptr_t fact; // ecx

  fact = (uintptr_t)(unsigned int)fact_ptr;
  if ( g_Rules_JoinOperationInProgress )
  {
    Rules_PrintErrorID((int)aFactmngr, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFactsMayNotBeR, 0);
    return 0;
  }
  if ( !fact )
  {
    while ( g_Rules_FactListHead )
      Rules_RetractFact(g_Rules_FactListHead, a2);
    return 1;
  }
  if ( *(char *)(fact + 29) < 0 )
    return 0;
  if ( (*(_BYTE *)((uintptr_t)(unsigned int)*(_DWORD *)(fact + 16) + 24) & 2) != 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502590, 0);
    Rules_PrintFactWithIndex((int)g_IO_LogicalNameTable_WTrace[0], (int)fact);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502598, 0);
  }
  g_Rules_FactListChangedFlag = 1;
  Rules_ReleaseLogicalSupportList((int)fact);
  Rules_RemoveFactHashEntry((int)fact);
  if ( (int)fact == g_Rules_LastFactPointer )
    g_Rules_LastFactPointer = *(_DWORD *)(fact + 32);
  if ( *(_DWORD *)(fact + 32) )
  {
    uintptr_t previous = (uintptr_t)(unsigned int)*(_DWORD *)(fact + 32);
    int next = *(_DWORD *)(fact + 36);
    *(_DWORD *)(previous + 36) = next;
    if ( next )
      *(_DWORD *)((uintptr_t)(unsigned int)next + 32) = *(_DWORD *)(fact + 32);
  }
  else
  {
    int new_head = *(_DWORD *)((uintptr_t)(unsigned int)g_Rules_FactListHead + 36);
    g_Rules_FactListHead = new_head;
    if ( new_head )
      *(_DWORD *)((uintptr_t)(unsigned int)new_head + 32) = 0;
  }
  Rules_DeinstallFact((int)fact);
  ++g_ClipsEphemeralItemCount;
  g_ClipsEphemeralItemBytes += 6 * *(_DWORD *)(fact + 46) + 60;
  *(_DWORD *)(fact + 36) = g_Rules_GarbageFactListHead;
  g_Rules_GarbageFactListHead = (int)fact;
  *(_BYTE *)(fact + 29) |= 0x80u;
  Lexer_ErrorRecover(0);
  g_Rules_JoinOperationInProgress = 1;
  Rules_RetractFactFromNetwork(*(_DWORD **)(fact + 20), a2);
  g_Rules_JoinOperationInProgress = 0;
  if ( !g_Rules_CurrentlyExecutingRule )
    Rules_FlushPendingNetworkGarbage();
  Rules_FlushPendingDependencyDestructors();
  if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
    Rules_RunPeriodicCleanup(1, 0);
  return 1;
}
// 51A110: using guessed type int dword_51A110;
// 51A154: using guessed type int dword_51A154;
// 51A158: using guessed type int dword_51A158;
// 51A15C: using guessed type int dword_51A15C;
// 51A1F0: using guessed type int dword_51A1F0;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A954: using guessed type int dword_51A954;
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (0047A120) --------------------------------------------------------
_DWORD *Rules_RemoveGarbageFacts()
{
  _DWORD *result; // eax
  int v1; // edx
  _DWORD *v2; // edx
  int v3; // ecx

  result = (_DWORD *)g_Rules_GarbageFactListHead;
  if ( g_Rules_GarbageFactListHead )
  {
    do
    {
      while ( 1 )
      {
        v1 = result[9];
        if ( !result[2] && (result[7] & 0x7FFF) > g_ClipsCurrentEvaluationDepth )
          break;
        result = (_DWORD *)result[9];
        if ( !v1 )
          return result;
      }
      --g_ClipsEphemeralItemCount;
      g_ClipsEphemeralItemBytes -= 6 * *(_DWORD *)((char *)result + 46) + 60;
      Rules_ReturnFact(result);
      if ( v3 )
        *(_DWORD *)(v3 + 36) = v2;
      else
        g_Rules_GarbageFactListHead = (int)v2;
      result = v2;
    }
    while ( v2 );
  }
  return result;
}
// 47A16E: variable 'v3' is possibly undefined
// 47A170: variable 'v2' is possibly undefined
// 51A154: using guessed type int dword_51A154;
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A96C: using guessed type int dword_51A96C;

//----- (0047A1A0) --------------------------------------------------------
_DWORD * Rules_AssertFactDriver(_DWORD *fact, double a2)
{
  char *slot_ptr; // eax
  int slot_count; // ecx
  int slot_index; // ebx
  char *slot_cursor; // edx
  signed int *interned_nil; // eax
  int v9; // ecx
  int hash_value; // ecx
  int prev_fact; // eax
  int fact_index; // eax
  int time_tag; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _DWORD *v17; // ecx

  if ( g_Rules_JoinOperationInProgress )
  {
    Rules_ReturnFact(fact);
    Rules_PrintErrorID((int)aFactmngr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFactsMayNotBeA, v9);
    return 0;
  }
  slot_ptr = (char *)fact + 54;
  slot_count = *((_DWORD *)slot_ptr - 2);
  slot_index = 0;
  if ( slot_count > 0 )
  {
    slot_cursor = slot_ptr;
    do
    {
      if ( *(_WORD *)slot_cursor == 105 )
      {
        *(_WORD *)slot_cursor = 2;
        interned_nil = Str_Intern(aNil_2, slot_count);
        *(_DWORD *)(slot_cursor + 2) = interned_nil;
      }
      ++slot_index;
      slot_cursor += 6;
    }
    while ( slot_index < slot_count );
  }
  hash_value = Rules_DeduplicateFactOnAssert((int)fact);
  if ( hash_value < 0 )
    return 0;
  if ( Rules_AddLogicalDependencyLink((int)fact, 0) )
  {
    Rules_InsertFactHashEntry((int)fact, hash_value);
    fact[9] = 0;
    fact[5] = 0;
    prev_fact = g_Rules_LastFactPointer;
    fact[8] = g_Rules_LastFactPointer;
    if ( prev_fact )
      *(_DWORD *)(prev_fact + 36) = fact;
    else
      g_Rules_FactListHead = (int)fact;
    fact_index = g_Rules_NextFactIndex;
    g_Rules_LastFactPointer = (int)fact;
    ++g_Rules_NextFactIndex;
    fact[6] = fact_index;
    time_tag = g_Rules_EntityTimeTagCounter++;
    fact[3] = time_tag;
    Rules_InstallFact(fact);
    if ( (*(_BYTE *)(fact[4] + 24) & 2) != 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_5025D4, v14);
      Rules_PrintFactWithIndex(v15, (int)fact);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502598, v16);
    }
    g_Rules_FactListChangedFlag = 1;
    Rules_CheckFactAgainstSlotConstraints((int)fact);
    Lexer_ErrorRecover(0);
    g_Rules_JoinOperationInProgress = 1;
    Rules_MatchFactAgainstPatternNetwork((int)fact, *(_DWORD *)(fact[4] + 32), 0, 0, a2, 0);
    g_Rules_JoinOperationInProgress = 0;
    Rules_FlushPendingDependencyDestructors();
    if ( !g_Rules_CurrentlyExecutingRule )
      Rules_FlushPendingNetworkGarbage();
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      Rules_RunPeriodicCleanup(1, 0);
    return fact;
  }
  else
  {
    Rules_ReturnFact(fact);
    return 0;
  }
}
// 47A1CF: variable 'v4' is possibly undefined
// 47A1D4: variable 'v6' is possibly undefined
// 47A217: variable 'v9' is possibly undefined
// 47A233: variable 'v10' is possibly undefined
// 47A29E: variable 'v14' is possibly undefined
// 47A2AA: variable 'v15' is possibly undefined
// 47A2B9: variable 'v16' is possibly undefined
// 47A2ED: variable 'v17' is possibly undefined
// 51A110: using guessed type int dword_51A110;
// 51A158: using guessed type int dword_51A158;
// 51A15C: using guessed type int dword_51A15C;
// 51A160: using guessed type int dword_51A160;
// 51A1F0: using guessed type int dword_51A1F0;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A954: using guessed type int dword_51A954;
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51A998: using guessed type int dword_51A998;

//----- (0047A350) --------------------------------------------------------
signed int  Rules_RemoveAllFacts(double a1)
{
  signed int result; // eax

  for ( ; g_Rules_FactListHead; result = Rules_RetractFact(g_Rules_FactListHead, a1) )
    ;
  return result;
}
// 51A15C: using guessed type int dword_51A15C;

//----- (0047A3F0) --------------------------------------------------------
int  Lexer_EmitSlotBinding(int fact, char *slot_name, int a3, _DWORD *result_value)
{
  int deftemplate; // edi
  int result; // eax
  int v7; // eax
  signed int *slot_symbol; // eax
  _DWORD *v9; // ecx
  int v10; // edx
  int v11; // eax
  _DWORD v12[4]; // [esp+0h] [ebp-10h] BYREF

  v12[3] = a3;
  deftemplate = *(_DWORD *)(fact + 16);
  if ( (*(_BYTE *)(deftemplate + 24) & 1) != 0 )
  {
    if ( !slot_name )
    {
      result_value[1] = *(__int16 *)(fact + 54);
      result_value[2] = *(_DWORD *)(fact + 56);
      v7 = result_value[2];
      result_value[3] = 0;
      result_value[4] = *(_DWORD *)(v7 + 6) - 1;
      return 1;
    }
    return 0;
  }
  slot_symbol = Str_Intern(slot_name, (int)result_value);
  result = (int)Lexer_FindTemplateSlot(deftemplate, (int)slot_symbol, v12);
  if ( result )
  {
    v9[1] = *(__int16 *)(fact + 6 * (v12[0] - 1) + 54);
    v10 = v9[1];
    v9[2] = *(_DWORD *)(fact + 6 * (v12[0] - 1) + 56);
    if ( v10 == 4 )
    {
      v11 = v9[2];
      v9[3] = 0;
      v9[4] = *(_DWORD *)(v11 + 6) - 1;
    }
    return v9[1] != 105;
  }
  return result;
}
// 47A45D: variable 'v9' is possibly undefined

//----- (0047A730) --------------------------------------------------------
_DWORD * Rules_CreateFact(signed int slot_count)
{
  signed int v1; // ecx
  signed int effective_count; // edx
  int v3; // eax
  _DWORD *result; // eax
  __int16 eval_depth; // dx
  __int16 v6; // bx
  int v7; // edi
  __int16 v8; // dx

  v1 = slot_count;
  if ( slot_count <= 0 )
    effective_count = 1;
  else
    effective_count = slot_count;
  if ( (unsigned int)(6 * (effective_count - 1) + 60) < 0x1F4 && *(_DWORD *)(g_ClipsMemoryTable + 24 * (effective_count - 1) + 240) )
  {
    v3 = g_ClipsMemoryTable + 24 * (effective_count - 1);
    g_ClipsMemFreeListTemp = *(_DWORD *)(v3 + 240);
    *(_DWORD *)(v3 + 240) = *(_DWORD *)g_ClipsMemFreeListTemp;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = Mem_NewArray(6 * (effective_count - 1) + 60);
  }
  eval_depth = g_ClipsCurrentEvaluationDepth;
  result[6] = 0;
  result[2] = 0;
  *result = &g_Rules_FactPatternEntityRecord;
  result[1] = 0;
  result[4] = 0;
  v6 = *((_WORD *)result + 14);
  result[9] = 0;
  result[8] = 0;
  *((_WORD *)result + 14) = v6 & 0x8000;
  v7 = result[7];
  result[5] = 0;
  result[7] = eval_depth & 0x7FFF | v7;
  LOBYTE(eval_depth) = *((_BYTE *)result + 29);
  *(_DWORD *)((char *)result + 46) = v1;
  *((_BYTE *)result + 29) = eval_depth & 0x7F;
  v8 = g_ClipsCurrentEvaluationDepth;
  result[10] = 0;
  *((_WORD *)result + 22) = v8;
  return result;
}
// 47A802: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047A850) --------------------------------------------------------
_DWORD * Rules_ReturnFact(_DWORD *fact)
{
  _DWORD *v2; // ebx
  int slot_index; // ecx
  _DWORD *slot_cursor; // edx
  int v5; // eax
  unsigned int bucket_size; // eax
  _DWORD *result; // eax

  v2 = fact + 10;
  slot_index = 0;
  if ( *(int *)((char *)fact + 46) > 0 )
  {
    slot_cursor = fact + 10;
    do
    {
      if ( *((_WORD *)slot_cursor + 7) == 4 )
        Rules_ReturnMultifieldToPool((_DWORD *)slot_cursor[4]);
      ++slot_index;
      slot_cursor = (_DWORD *)((char *)slot_cursor + 6);
    }
    while ( slot_index < *(_DWORD *)((char *)v2 + 6) );
  }
  if ( *(_DWORD *)((char *)fact + 46) )
    v5 = *(_DWORD *)((char *)fact + 46);
  else
    v5 = 1;
  bucket_size = 6 * (v5 - 1) + 60;
  g_ClipsMemPoolReturnBucketIndex = bucket_size;
  if ( bucket_size >= 0x1F4 )
    return (_DWORD *)Mem_SmallBlockRelease(fact, bucket_size);
  g_ClipsMemFreeListTemp = (int)fact;
  *fact = *(_DWORD *)(g_ClipsMemoryTable + 4 * bucket_size);
  result = (_DWORD *)(g_ClipsMemoryTable + 4 * g_ClipsMemPoolReturnBucketIndex);
  *result = g_ClipsMemFreeListTemp;
  return result;
}
// 47A86D: variable 'v3' is possibly undefined
// 47A871: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0047A900) --------------------------------------------------------
int  Rules_InstallFact(_DWORD *fact)
{
  int result; // eax
  int slot_index; // ebx
  int slot_cursor; // ecx
  int v5; // ecx

  ++g_Rules_InstalledFactCount;
  result = fact[4];
  ++*(_DWORD *)(result + 28);
  slot_index = 0;
  if ( *(int *)((char *)fact + 46) > 0 )
  {
    slot_cursor = (int)(fact + 10);
    do
    {
      Rules_AtomInstall(*(__int16 *)(slot_cursor + 14), *(_DWORD *)(slot_cursor + 16), slot_cursor);
      ++slot_index;
      result = *(_DWORD *)((char *)fact + 46);
      slot_cursor = v5 + 6;
    }
    while ( slot_index < result );
  }
  ++fact[2];
  return result;
}
// 47A936: variable 'v5' is possibly undefined
// 51A164: using guessed type int dword_51A164;

//----- (0047A950) --------------------------------------------------------
int  Rules_DeinstallFact(int fact)
{
  int slot_base; // esi
  int result; // eax
  int slot_index; // ebx
  int slot_cursor; // ecx
  int v6; // ecx

  slot_base = fact + 40;
  --g_Rules_InstalledFactCount;
  result = *(_DWORD *)(fact + 16);
  --*(_DWORD *)(result + 28);
  slot_index = 0;
  if ( *(int *)(slot_base + 6) > 0 )
  {
    slot_cursor = slot_base;
    do
    {
      Rules_AtomDeinstall(*(__int16 *)(slot_cursor + 14), *(__int16 **)(slot_cursor + 16), slot_cursor);
      ++slot_index;
      result = *(_DWORD *)(slot_base + 6);
      slot_cursor = v6 + 6;
    }
    while ( slot_index < result );
  }
  --*(_DWORD *)(fact + 8);
  return result;
}
// 47A989: variable 'v6' is possibly undefined
// 51A164: using guessed type int dword_51A164;

//----- (0047A9A0) --------------------------------------------------------
int  Rules_GetNextFact(int fact)
{
  if ( !fact )
    return g_Rules_FactListHead;
  if ( *(char *)(fact + 29) >= 0 )
    return *(_DWORD *)(fact + 36);
  return 0;
}
// 51A15C: using guessed type int dword_51A15C;

//----- (0047A9C0) --------------------------------------------------------
int  Rules_GetNextFactInModule(int fact)
{
  int next_fact; // edx

  if ( fact )
  {
    if ( *(char *)(fact + 29) < 0 )
      return 0;
    next_fact = *(_DWORD *)(fact + 36);
  }
  else
  {
    next_fact = g_Rules_FactListHead;
    if ( g_Rules_LastFactModuleCache != g_Module_ChangeGeneration )
    {
      Lexer_MarkImpliedTemplates();
      g_Rules_LastFactModuleCache = g_Module_ChangeGeneration;
    }
  }
  while ( next_fact && (*(_BYTE *)(*(_DWORD *)(next_fact + 16) + 24) & 4) == 0 )
    next_fact = *(_DWORD *)(next_fact + 36);
  return next_fact;
}
// 47A9DD: variable 'v1' is possibly undefined
// 51A15C: using guessed type int dword_51A15C;
// 51A168: using guessed type int dword_51A168;
// 51A9C0: using guessed type int dword_51A9C0;

//----- (0047AA40) --------------------------------------------------------
int  Rules_GetFactIndex(int fact)
{
  return *(_DWORD *)(fact + 24);
}

//----- (0047AA50) --------------------------------------------------------
_DWORD * Rules_Log(const char *string, int a2, double a3)
{
  _DWORD *result; // eax

  result = Rules_StringToFact(string, a2, a3);
  if ( result )
    return Rules_AssertFactDriver(result, a3);
  return result;
}

//----- (0047AA80) --------------------------------------------------------
int Rules_GetInstalledFactCount()
{
  return g_Rules_InstalledFactCount;
}
// 51A164: using guessed type int dword_51A164;

//----- (0047AA90) --------------------------------------------------------
signed int  Rules_ResetFacts(double a1)
{
  signed int result; // eax

  for ( g_Rules_NextFactIndex = 0; g_Rules_FactListHead; result = Rules_RetractFact(g_Rules_FactListHead, a1) )
    ;
  return result;
}
// 51A15C: using guessed type int dword_51A15C;
// 51A160: using guessed type int dword_51A160;

//----- (0047AAD0) --------------------------------------------------------
BOOL  Rules_ClearFacts(double a1)
{
  g_Rules_NextFactIndex = 0;
  while ( g_Rules_FactListHead )
    Rules_RetractFact(g_Rules_FactListHead, a1);
  return Rules_GetNextFact(0) == 0;
}
// 51A15C: using guessed type int dword_51A15C;
// 51A160: using guessed type int dword_51A160;

//----- (0047AB20) --------------------------------------------------------
int Rules_FindFactByIndex()
{
  int result; // eax
  int target_index; // ecx

  result = Rules_GetNextFact(0);
  if ( !result )
    return 0;
  while ( target_index != *(_DWORD *)(result + 24) )
  {
    result = Rules_GetNextFact(result);
    if ( !result )
      return 0;
  }
  return result;
}
// 47AB31: variable 'v1' is possibly undefined

//----- (0047AB50) --------------------------------------------------------
signed int Rules_RegisterFactCommands()
{
  Rules_RegisterHostFunction(aFacts_1, 118, (int)aFactscommand, (int)Rules_FactsCommand, (int)a4iu);
  Rules_RegisterHostFunctionNoRestrictions(aAssert, 117, (int)aAssertcommand, (int)Rules_AssertCommand);
  Rules_RegisterHostFunction(aRetract_0, 118, (int)aRetractcommand, (int)Rules_RetractCommand, (int)a1Z);
  Rules_RegisterHostFunction(aAssertString, 117, (int)aAssertstringfu, (int)Rules_AssertStringFunction, (int)a11s);
  Rules_RegisterHostFunction(aStrAssert, 117, (int)aAssertstringfu, (int)Rules_AssertStringFunction, (int)a11s);
  Rules_RegisterHostFunction(aGetFactDuplica, 98, (int)aGetfactduplica, (int)Rules_GetFactDuplicationCommand, (int)a00_1);
  Rules_RegisterHostFunction(aSetFactDuplica, 98, (int)aSetfactduplica, (int)Rules_SetFactDuplicationCommand, (int)a11);
  Rules_RegisterHostFunction(aSaveFacts, 98, (int)aSavefactscomma, (int)Rules_ParseSaveFactsCommand, (int)a1Wk);
  Rules_RegisterHostFunction(aLoadFacts, 98, (int)aLoadfactscomma, (int)Rules_ParseLoadFactsCommand, (int)a11k);
  Rules_RegisterHostFunction(aFactIndex, 108, (int)aFactindexfunct, (int)Rules_FactIndexFunction, (int)a11y);
  Rules_AddFunctionParser(aAssert);
  return Rules_SetFunctionSeqOverloadFlags(aAssert, 0);
}

//----- (0047ACA0) --------------------------------------------------------
_DWORD * Rules_AssertCommand(uintptr_t returnValue, uintptr_t a2, double eval_context)
{
  uintptr_t out; // eax
  uintptr_t expression; // ebx
  uintptr_t deftemplate_record; // edi
  int multifield_reorder_needed; // ebp
  uintptr_t slot_constraint; // ecx
  _DWORD *fact; // [esp+1Ch] [ebp-1Ch]
  char *slot_value; // esi
  _DWORD *result; // eax
  _DWORD parsed[6]; // [esp+0h] [ebp-38h] BYREF

  (void)a2;
  out = returnValue;
  *(_DWORD *)(out + 4) = 2;
  *(_DWORD *)(out + 8) = g_ClipsFalseSymbol;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(g_ClipsCurrentExpression + 6);
  deftemplate_record = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2);
  multifield_reorder_needed = 0;
  if ( (*(_BYTE *)(deftemplate_record + 24) & 1) != 0 )
  {
    fact = Module_AllocList(1);
    if ( !*(_DWORD *)(expression + 10) )
    {
      *((_WORD *)fact + 27) = 4;
      fact[14] = (int)(uintptr_t)Rules_CreateMultifield(0);
    }
    slot_constraint = 0;
  }
  else
  {
    fact = Module_AllocList(((unsigned int)*(_DWORD *)(deftemplate_record + 24) << 16) >> 19);
    slot_constraint = (uintptr_t)(unsigned int)*(_DWORD *)(deftemplate_record + 20);
  }
  fact[4] = (int)deftemplate_record;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
  slot_value = (char *)fact + 54;
  while ( expression )
  {
    Parser_ParseForm((__int16 *)expression, parsed, (int)slot_constraint, eval_context);
    if ( slot_constraint && (*(_BYTE *)(slot_constraint + 4) & 1) == 0 && parsed[1] == 4 )
    {
      multifield_reorder_needed = 1;
      Rules_ReportMultifieldAssertIntoSingleSlotError((int)slot_constraint, (int)deftemplate_record);
      parsed[1] = 2;
      parsed[2] = g_ClipsFalseSymbol;
    }
    *(_WORD *)slot_value = parsed[1];
    *(_DWORD *)(slot_value + 2) = parsed[2];
    if ( slot_constraint )
      slot_constraint = (uintptr_t)(unsigned int)*(_DWORD *)(slot_constraint + 16);
    expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
    slot_value += 6;
  }
  if ( multifield_reorder_needed )
    return Rules_ReturnFact(fact);
  result = Rules_AssertFactDriver(fact, eval_context);
  if ( result )
  {
    *(_DWORD *)(out + 4) = 6;
    *(_DWORD *)(out + 8) = (int)(uintptr_t)result;
  }
  return result;
}
// 47AD18: variable 'v9' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 54DD70: using guessed type int dword_54DD70;

//----- (0047ADD0) --------------------------------------------------------
void  Rules_RetractCommand(int a1, int a2, double a3)
{
  __int16 *v3; // ecx
  int i; // esi
  int v5; // ecx
  int fact; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // [esp-4h] [ebp-3Ch] BYREF
  int arg_type; // [esp+0h] [ebp-38h]
  int arg_value; // [esp+4h] [ebp-34h]
  _BYTE buffer[24]; // [esp+14h] [ebp-24h] BYREF
  int v15; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+30h] [ebp-8h]

  v16 = a2;
  v15 = a1;
  v3 = *(__int16 **)(g_ClipsCurrentExpression + 6);
  for ( i = 1; v3; ++i )
  {
    while ( 1 )
    {
      Parser_ParseForm(v3, &v11, (int)v3, a3);
      if ( arg_type != 1 )
        break;
      if ( *(int *)(arg_value + 16) < 0 )
      {
        Parser_ReportError(i, (int)aFactAddressFac);
        return;
      }
      fact = Rules_FindFactByIndex();
      if ( !fact )
      {
        a3 = sprintf_(buffer, "f-%ld", v7);
        Rules_ReportCantFindItem(v9, (int)buffer);
        goto LABEL_6;
      }
LABEL_5:
      Rules_RetractFact(fact, a3);
LABEL_6:
      v3 = *(__int16 **)(v8 + 10);
      ++i;
      if ( !v3 )
        return;
    }
    if ( arg_type == 6 )
    {
      fact = arg_value;
      goto LABEL_5;
    }
    if ( arg_type == 2 && !strcmp_(v5, asc_502790) )
    {
      Rules_RemoveAllFacts(a3);
      return;
    }
    Parser_ReportError(i, (int)aFactAddressFac);
    Lexer_ErrorRecover(1);
    v3 = *(__int16 **)(v10 + 10);
  }
}
// 47AE16: variable 'v8' is possibly undefined
// 47AE44: variable 'v7' is possibly undefined
// 47AE55: variable 'v9' is possibly undefined
// 47AE72: variable 'v5' is possibly undefined
// 47AE9E: variable 'v10' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (0047AED0) --------------------------------------------------------
int  Rules_SetFactDuplicationCommand(int a1, double a2)
{
  int old_flag; // esi
  int v4; // ecx
  int new_flag; // eax
  _DWORD v6[10]; // [esp-4h] [ebp-28h] BYREF

  v6[8] = a1;
  old_flag = Rules_GetFactDuplicationFlag();
  if ( Lexer_TokenExpect(1) == -1 )
    return v4;
  Rules_RtnUnknown(1, v6, a2);
  new_flag = 1;
  if ( v6[0] == 2 && v6[1] == g_ClipsFalseSymbol )
    new_flag = 0;
  Rules_SetFactDuplicationEnabled(new_flag);
  return old_flag;
}
// 47AEF6: variable 'v4' is possibly undefined
// 48AC80: using guessed type int __fastcall unknown_libname_8(int);
// 54DD70: using guessed type int dword_54DD70;

//----- (0047AF50) --------------------------------------------------------
int Rules_GetFactDuplicationCommand()
{
  int v0; // ecx

  Rules_GetFactDuplicationFlag();
  Lexer_TokenExpect(0);
  return v0;
}
// 47AF6B: variable 'v0' is possibly undefined

//----- (0047AF80) --------------------------------------------------------
int  Rules_FactIndexFunction(double a1)
{
  int result; // eax
  _DWORD v2[2]; // [esp-4h] [ebp-20h] BYREF
  int fact; // [esp+4h] [ebp-18h]

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    Rules_RtnUnknown(1, v2, a1);
    if ( v2[1] == 6 )
    {
      if ( *(char *)(fact + 29) >= 0 )
        return Rules_GetFactIndex(fact);
      else
        return -1;
    }
    else
    {
      Parser_ReportError(1, (int)aFactAddress_0);
      return -1;
    }
  }
  return result;
}

//----- (0047B000) --------------------------------------------------------
signed int  Rules_FactsCommand(double a1)
{
  signed int result; // eax
  signed int v2; // esi
  int v3; // ebx
  int v4; // ecx
  int v5; // esi
  int arg_offset; // ebp
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // [esp+0h] [ebp-30h] BYREF
  int arg_type; // [esp+4h] [ebp-2Ch]
  int v12; // [esp+8h] [ebp-28h]

  result = Lexer_TokenExpect(4);
  v2 = result;
  v3 = result;
  if ( result == -1 )
    return result;
  Module_GetCurrent();
  if ( !v2 )
    return Rules_PrintFactRange((int)g_IO_LogicalName_WDisplay, -1, -1, -1);
  Rules_RtnUnknown(1, &v10, a1);
  if ( arg_type != 2 )
  {
    if ( arg_type != 1 || (v5 = *(_DWORD *)(v12 + 16), v5 < 0) )
    {
      Parser_ReportError(1, (int)aSymbolOrPositi);
      Rules_SetEvaluationErrorFlag(1);
      return Lexer_ErrorRecover(1);
    }
    arg_offset = 0;
    goto LABEL_8;
  }
  if ( !Module_FindByName(*(_BYTE **)(v12 + 16)) && strcmp_(v8, asc_502790) )
  {
    Lexer_ErrorRecover(1);
    return Rules_ReportCantFindItem(v9, *(_DWORD *)(v12 + 16));
  }
  result = Rules_ParsePositiveIntArg(2, v3, v8, a1);
  v5 = result;
  if ( result != -2 )
  {
    arg_offset = 1;
LABEL_8:
    result = Rules_ParsePositiveIntArg(arg_offset + 2, v3, v4, a1);
    if ( result != -2 )
    {
      result = Rules_ParsePositiveIntArg(arg_offset + 3, v3, result, a1);
      if ( result != -2 )
        return Rules_PrintFactRange((int)g_IO_LogicalName_WDisplay, v7, v5, result);
    }
  }
  return result;
}
// 47B06F: variable 'v4' is possibly undefined
// 47B094: variable 'v7' is possibly undefined
// 47B0E3: variable 'v8' is possibly undefined
// 47B123: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A624: using guessed type char *off_51A624;

//----- (0047B1A0) --------------------------------------------------------
int  Rules_PrintFactRange(int logicalName, int end_index, int start_index, int max_count)
{
  int printed_count; // edi
  int v8; // edx
  int v9; // eax
  int fact; // eax
  int fact_cursor; // ecx
  int v12; // ecx
  int saved_module; // [esp+0h] [ebp-18h]
  int scan_all_modules; // [esp+8h] [ebp-10h]

  printed_count = 0;
  saved_module = Module_GetCurrent();
  scan_all_modules = 0;
  if ( v8 )
  {
    Module_SetCurrent(v8);
    v9 = 0;
LABEL_3:
    fact = Rules_GetNextFactInModule(v9);
    goto LABEL_4;
  }
  scan_all_modules = 1;
  fact = Rules_GetNextFact(0);
LABEL_4:
  while ( fact )
  {
    if ( Rules_GetEvaluationErrorFlag() == 1 )
      return Module_SetCurrent(saved_module);
    if ( end_index < *(_DWORD *)(fact_cursor + 24) && end_index != -1 || !max_count )
      break;
    if ( start_index <= *(_DWORD *)(fact_cursor + 24) )
    {
      Rules_PrintFactWithIndex(fact_cursor, fact_cursor);
      ++printed_count;
      Output_Write(logicalName, (int)asc_5027CC, v12);
      if ( max_count > 0 )
        --max_count;
    }
    if ( !scan_all_modules )
    {
      v9 = fact_cursor;
      goto LABEL_3;
    }
    fact = Rules_GetNextFact(fact_cursor);
  }
  Rules_PrintTally(logicalName, printed_count, (int)aFacts_1, (int)aFact);
  return Module_SetCurrent(saved_module);
}
// 47B1C2: variable 'v8' is possibly undefined
// 47B1EA: variable 'v11' is possibly undefined
// 47B215: variable 'v12' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047B270) --------------------------------------------------------
signed int  Rules_ParsePositiveIntArg(int arg_index, int max_args, int a3, double a4)
{
  signed int result; // eax
  _DWORD v6[9]; // [esp-8h] [ebp-24h] BYREF

  v6[7] = a3;
  if ( arg_index > max_args )
    return -1;
  if ( !Lexer_ParseValueList(arg_index, v6, 1, a4) )
    return -2;
  result = *(_DWORD *)(v6[2] + 16);
  if ( result < 0 )
  {
    Parser_ReportError(arg_index, (int)aPositiveNumber);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -2;
  }
  return result;
}

//----- (0047B2F0) --------------------------------------------------------
_DWORD * Rules_AssertStringFunction(int returnValue, int a2, double a3)
{
  _DWORD *result; // eax
  int v5; // ecx
  _DWORD v6[10]; // [esp-8h] [ebp-28h] BYREF

  v6[8] = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v6, 3, a3);
    if ( result )
    {
      result = Rules_Log(*(const char **)(v6[2] + 16), v5, a3);
      if ( result )
      {
        *(_DWORD *)(returnValue + 4) = 6;
        *(_DWORD *)(returnValue + 8) = result;
      }
    }
  }
  return result;
}
// 47B347: variable 'v5' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (0047B370) --------------------------------------------------------
int  Rules_ParseSaveFactsCommand(double a1)
{
  int save_scope; // esi
  _DWORD *template_list; // edi
  int v3; // ecx
  int result; // eax
  int v5; // ecx
  const CHAR *filename; // ebp
  int v7; // ecx
  _DWORD v8[6]; // [esp+0h] [ebp-34h] BYREF
  int arg_count; // [esp+18h] [ebp-1Ch]

  save_scope = 1;
  template_list = 0;
  v3 = Lexer_TokenExpect(1);
  arg_count = v3;
  if ( v3 == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v3, a1);
  filename = (const CHAR *)result;
  if ( result )
  {
    if ( v5 > 1 )
    {
      result = Lexer_ParseValueList(2, v8, 2, a1);
      if ( !result )
        return result;
      if ( strcmp_(*(_DWORD *)(v8[2] + 16), aLocal) )
      {
        if ( strcmp_(v7, aVisible) )
        {
          Parser_ReportError(2, (int)aSymbolWithValu);
          return 0;
        }
        save_scope = 2;
      }
    }
    if ( arg_count > 2 )
      template_list = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(g_ClipsCurrentExpression + 6) + 10) + 10);
    result = Rules_SaveFactsToFile(filename, save_scope, template_list, a1);
    if ( result )
      return 1;
  }
  return result;
}
// 47B3B9: variable 'v5' is possibly undefined
// 47B422: variable 'v7' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (0047B470) --------------------------------------------------------
signed int  Rules_ParseLoadFactsCommand(DWORD a1, double a2)
{
  int v2; // ecx
  signed int result; // eax
  int v4; // ecx

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, a2);
  if ( result )
  {
    result = Rules_LoadFactsFromFile((const CHAR *)result, v4, a1, a2);
    if ( result )
      return 1;
  }
  return result;
}
// 47B497: variable 'v2' is possibly undefined
// 47B4A0: variable 'v4' is possibly undefined

//----- (0047B4C0) --------------------------------------------------------
signed int  Rules_SaveFactsToFile(const CHAR *fileName, int saveScope, _DWORD *importList, double frame)
{
  int v5; // eax
  int v6; // ecx
  int file; // esi
  int v8; // ecx
  int v9; // ecx
  int i; // ebx
  int v12; // ecx
  int matchIndex; // eax
  _DWORD *matchScan; // edx
  int arrayCount; // [esp+0h] [ebp-30h] BYREF
  int errorFlag; // [esp+4h] [ebp-2Ch] BYREF
  int savedPreserveEscapedFlag; // [esp+8h] [ebp-28h]
  int savedAddressesToStringsFlag; // [esp+Ch] [ebp-24h]
  int savedInstanceAddressesFlag; // [esp+10h] [ebp-20h]
  int currentModule; // [esp+14h] [ebp-1Ch]
  int v21; // [esp+18h] [ebp-18h]
  _DWORD *deftemplateArray; // [esp+1Ch] [ebp-14h]

  v21 = saveScope;
  v5 = IO_FOpen(fileName, (unsigned __int8 *)aW_0, (int)fileName, (DWORD)importList);
  file = v5;
  if ( v5 )
  {
    IO_SetFastSaveFile(v5);
    savedPreserveEscapedFlag = g_Print_PreserveEscapedCharactersFlag;
    g_Print_PreserveEscapedCharactersFlag = 1;
    savedAddressesToStringsFlag = g_Print_AddressesToStringsFlag;
    g_Print_AddressesToStringsFlag = 1;
    savedInstanceAddressesFlag = g_Print_InstanceAddressesToNamesFlag;
    g_Print_InstanceAddressesToNamesFlag = 1;
    deftemplateArray = Rules_CollectFactsToArray(importList, v21, &errorFlag, &arrayCount, frame);
    if ( errorFlag )
    {
      g_Print_PreserveEscapedCharactersFlag = savedPreserveEscapedFlag;
      g_Print_AddressesToStringsFlag = savedAddressesToStringsFlag;
      g_Print_InstanceAddressesToNamesFlag = savedInstanceAddressesFlag;
      fclose_(v8);
      IO_SetFastSaveFile(0);
      return 0;
    }
    else
    {
      currentModule = Module_GetCurrent();
      for ( i = Rules_GetNextFactInModule(0); i; i = Rules_GetNextFactInModule(i) )
      {
        if ( v21 == 1 && currentModule != **(_DWORD **)(*(_DWORD *)(i + 16) + 8) )
          continue;
        if ( importList )
        {
          matchIndex = 0;
          if ( arrayCount <= 0 )
            continue;
          matchScan = deftemplateArray;
          while ( matchScan[2] != *(_DWORD *)(i + 16) )
          {
            ++matchIndex;
            matchScan += 6;
            if ( matchIndex >= arrayCount )
              goto LABEL_6;
          }
        }
        Rules_PrintFact(file, i);
        Output_Write(file, (int)asc_5027CC, v12);
LABEL_6:
        ;
      }
      g_Print_PreserveEscapedCharactersFlag = savedPreserveEscapedFlag;
      g_Print_AddressesToStringsFlag = savedAddressesToStringsFlag;
      g_Print_InstanceAddressesToNamesFlag = savedInstanceAddressesFlag;
      fclose_(v9);
      IO_SetFastSaveFile(0);
      if ( importList )
        Mem_SmallBlockRelease(deftemplateArray, 24 * arrayCount);
      return 1;
    }
  }
  else
  {
    Rules_OpenFileErrorMessage(v6, v6);
    return 0;
  }
}
// 47B599: variable 'v9' is possibly undefined
// 47B5D9: variable 'v6' is possibly undefined
// 47B605: variable 'v8' is possibly undefined
// 47B62F: variable 'v12' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A5F8: using guessed type int dword_51A5F8;
// 51A5FC: using guessed type int dword_51A5FC;
// 51A600: using guessed type int dword_51A600;

//----- (0047B670) --------------------------------------------------------
_DWORD * Rules_CollectFactsToArray(
        _DWORD *result,
        int saveScope,
        _DWORD *errorFlagPtr,
        int *countPtr,
        double frame)
{
  int listNode; // edi
  _DWORD *v7; // eax
  int v8; // ecx
  int entryCount; // ebx
  _DWORD *arrayEntry; // esi
  int v11; // eax
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // edx
  int v17; // [esp+0h] [ebp-28h] BYREF
  _DWORD *deftemplateArray; // [esp+4h] [ebp-24h]
  _DWORD *v19; // [esp+8h] [ebp-20h]
  int v20; // [esp+Ch] [ebp-1Ch]
  int exprIndex; // [esp+10h] [ebp-18h]
  int deftemplate; // [esp+14h] [ebp-14h]
  int writtenCount; // [esp+18h] [ebp-10h]

  listNode = (int)result;
  v20 = saveScope;
  v19 = errorFlagPtr;
  *errorFlagPtr = 0;
  if ( !result )
  {
    *countPtr = 0;
    return result;
  }
  *countPtr = 0;
  do
  {
    result = *(_DWORD **)((char *)result + 10);
    ++*countPtr;
  }
  while ( result );
  v7 = Mem_NewArray(24 * *countPtr);
  v8 = 0;
  deftemplateArray = v7;
  entryCount = *countPtr;
  writtenCount = 0;
  if ( entryCount <= 0 )
    return deftemplateArray;
  arrayEntry = v7;
  exprIndex = 3;
  while ( 1 )
  {
    Parser_ParseForm((__int16 *)listNode, arrayEntry, v8, frame);
    if ( g_ClipsEvaluationError )
    {
      *v19 = 1;
      Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
      return 0;
    }
    if ( arrayEntry[1] != 2 )
    {
      v13 = exprIndex;
      *v19 = 1;
      Parser_ReportError(v13, (int)aSymbol_1);
      Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
      return 0;
    }
    if ( v20 != 1 )
      break;
    deftemplate = Rules_FindDeftemplateByName(*(_BYTE **)(arrayEntry[2] + 16), 1);
    if ( !deftemplate )
    {
      v15 = exprIndex;
      *v19 = v14;
      Parser_ReportError(v15, (int)aLocalDeftempla);
      Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
      return 0;
    }
LABEL_11:
    arrayEntry += 6;
    v11 = deftemplate;
    v12 = writtenCount;
    *(arrayEntry - 5) = 35;
    *(arrayEntry - 4) = v11;
    writtenCount = v12 + 1;
    listNode = *(_DWORD *)(listNode + 10);
    v8 = *countPtr;
    ++exprIndex;
    if ( v12 + 1 >= v8 )
      return deftemplateArray;
  }
  if ( v20 != 2 )
    goto LABEL_11;
  deftemplate = Rules_FindImportExportConstruct(aDeftemplate_4, &v17, *(_BYTE **)(arrayEntry[2] + 16), 1, g_ClipsEvaluationError);
  if ( deftemplate )
    goto LABEL_11;
  v16 = exprIndex;
  *v19 = 1;
  Parser_ReportError(v16, (int)aVisibleDeftemp);
  Mem_SmallBlockRelease(deftemplateArray, 24 * *countPtr);
  return 0;
}
// 47B696: conditional instruction was optimized away because eax.4!=0
// 47B818: variable 'v14' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (0047B890) --------------------------------------------------------
BOOL  Rules_LoadFactsFromFile(const CHAR *fileName, int a2, DWORD a3, double a4)
{
  int v5; // eax
  int v6; // ecx
  int file; // ebx
  __int16 *parsedForm; // eax
  int v9; // ecx
  int v10; // ecx
  int v12; // [esp-18h] [ebp-34h] BYREF
  _DWORD v13[7]; // [esp+0h] [ebp-1Ch] BYREF

  v13[5] = a2;
  v5 = IO_FOpen(fileName, (unsigned __int8 *)aR_0, (int)fileName, a3);
  file = v5;
  if ( !v5 )
  {
    Rules_OpenFileErrorMessage(v6, v6);
    return 0;
  }
  IO_SetFastLoadFile(v5);
  v13[0] = 100;
  do
  {
    parsedForm = (__int16 *)Rules_ParseAssertFormFromFile(file, v13);
    v9 = (int)parsedForm;
    if ( parsedForm )
      Parser_ParseForm(parsedForm, &v12, (int)parsedForm, a4);
    else
      v13[0] = 102;
    AST_Free(v9);
  }
  while ( v13[0] != 102 );
  IO_SetFastLoadFile(0);
  fclose_(v10);
  return !g_ClipsEvaluationError;
}
// 47B8D3: variable 'v9' is possibly undefined
// 47B8E8: variable 'v10' is possibly undefined
// 47B907: variable 'v6' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A964: using guessed type int dword_51A964;

//----- (0047B930) --------------------------------------------------------
int  Rules_ParseAssertFormFromFile(int readSource, _DWORD *parseState)
{
  int **Symbol; // eax
  signed int assertNode; // esi
  int v7; // ecx
  int errorFlag[6]; // [esp+0h] [ebp-18h] BYREF

  errorFlag[0] = 0;
  Parser_NextToken(readSource, (int)parseState);
  if ( *parseState != 100 )
    return 0;
  Symbol = Rules_MakeSymbol(aAssert);
  assertNode = AST_NewNode(10, (int)Symbol);
  *(_DWORD *)(assertNode + 6) = Rules_ParseAssertRHSPattern(readSource, (int)parseState, 1, errorFlag, 0, 1, 101);
  if ( errorFlag[0] == 1 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionLoadFa, v7);
    Lexer_ErrorRecover(1);
  }
  else if ( !AST_TreeContainsSpecialTag(assertNode, 1) )
  {
    return assertNode;
  }
  AST_Free(assertNode);
  return 0;
}
// 47B9B8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047B9E0) --------------------------------------------------------
int  Rules_AssertParsedFact(int parseTree, int readSource, int a3)
{
  int v4; // edx
  _DWORD v6[3]; // [esp+0h] [ebp-1Ch] BYREF
  int v7[4]; // [esp+Ch] [ebp-10h] BYREF

  v7[2] = a3;
  AST_Free(parseTree);
  IO_OutWriteToken(asc_502890);
  Rules_IncrementIndentDepth(8);
  Rules_ParseAssertCommand(readSource, v6, 1, v7, 1, (int)aAssertCommand);
  Rules_DecrementIndentDepth(8);
  return v4;
}
// 47BA28: variable 'v4' is possibly undefined

//----- (0047BA31) --------------------------------------------------------
signed int  IO_AdvanceBufferCursor(int offset, int bufferState)
{
  int remaining; // edi
  int newPosition; // esi
  int newRemaining; // edi
  signed int result; // eax

  if ( offset > *(_DWORD *)(bufferState + 4) || offset < *(_DWORD *)(*(_DWORD *)(bufferState + 8) + 8) - *(_DWORD *)bufferState )
    return 1;
  remaining = *(_DWORD *)(bufferState + 4);
  newPosition = offset + *(_DWORD *)bufferState;
  *(_BYTE *)(bufferState + 12) &= ~0x10u;
  newRemaining = remaining - offset;
  *(_DWORD *)bufferState = newPosition;
  result = 0;
  *(_DWORD *)(bufferState + 4) = newRemaining;
  return result;
}

//----- (0047BA70) --------------------------------------------------------
int  IO_ResetBufferCursor(int result)
{
  int basePtr; // edx

  *(_BYTE *)(result + 12) &= ~0x10u;
  basePtr = *(_DWORD *)(*(_DWORD *)(result + 8) + 8);
  *(_DWORD *)(result + 4) = 0;
  *(_DWORD *)result = basePtr;
  return result;
}

//----- (0047BA86) --------------------------------------------------------
signed int  IO_SeekStreamGuarded(int stream, int offset, unsigned int whence, int a4)
{
  int fd_index;
  int seek_result;

  (void)a4;
  fd_index = *(_DWORD *)(stream + 16);
  g_CRT_FileHandleLockAcquireHook(fd_index);
  seek_result = Compat_StreamSeek(stream, offset, (int)whence);
  g_CRT_FileHandleLockReleaseHook(fd_index, seek_result);
  if ( seek_result == -1 )
    return -1;
  return 0;
}
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

//----- (0047BC10) --------------------------------------------------------
BOOL __stdcall InputBackend_StoreEnumeratedDevice(int deviceInstance, int directInput)
{
  return (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)directInput + 12))(directInput, deviceInstance + 4, &g_InputBackendTempJoystickDevice, 0) != 0;
}
// 54DD20: using guessed type int g_InputBackendTempJoystickDevice;

//----- (0047BC40) --------------------------------------------------------
InputBackendState * InputBackend_ResetState(InputBackendState *result)
{
  memset(result->keyboard_state, 0, sizeof(result->keyboard_state));
  result->direct_input = 0;
  result->keyboard_device = 0;
  result->mouse_device = 0;
  result->joystick_device = 0;
  result->mouse_delta_x = 0;
  result->mouse_delta_y = 0;
  result->joystick_axis_x = 0;
  result->joystick_axis_y = 0;
  result->mouse_device_ready = 0;
  result->keyboard_device_ready = 0;
  result->joystick_device_ready = 0;
  Platform_ResetInputFallbackState();
  return result;
}

//----- (0047BCA0) --------------------------------------------------------
InputBackendState * InputBackend_ReleaseDevices(InputBackendState *state)
{
  _DWORD *raw; // esi
  int keyboardDevice; // edx
  int mouseDevice; // ecx
  int joystickDevice; // esi

  raw = (_DWORD *)state;
  keyboardDevice = raw[1];
  if ( keyboardDevice )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)keyboardDevice + 8))(keyboardDevice);
    raw[1] = 0;
  }
  mouseDevice = raw[2];
  if ( mouseDevice )
  {
    (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)mouseDevice + 8))(mouseDevice, raw[2]);
    raw[2] = 0;
  }
  joystickDevice = raw[3];
  if ( joystickDevice )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)joystickDevice + 8))(raw[3]);
    raw[3] = 0;
  }
  if ( raw[0] )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)raw[0] + 8))(raw[0]);
    raw[0] = 0;
  }
  return state;
}

//----- (0047BD10) --------------------------------------------------------
signed int  InputBackend_Initialize(InputBackendState *state, int hInstance, int hwnd)
{
  _DWORD *raw; // esi
  _DWORD v5[2]; // [esp+94h] [ebp-3Ch] BYREF
  int v6; // [esp+9Ch] [ebp-34h]
  int v7; // [esp+A0h] [ebp-30h]
  int v8; // [esp+A4h] [ebp-2Ch]
  int v9; // [esp+A8h] [ebp-28h]
  _DWORD v10[2]; // [esp+ACh] [ebp-24h] BYREF
  int v11; // [esp+B4h] [ebp-1Ch]
  int v12; // [esp+B8h] [ebp-18h]
  int v13; // [esp+BCh] [ebp-14h]

  raw = (_DWORD *)state;
  if ( DirectInputCreateA(hInstance, 768, raw, 0) )
    return 0;
  if ( !(*(int (__stdcall **)(_DWORD, void *, _DWORD *, _DWORD))(*(_DWORD *)raw[0] + 12))(raw[0], &g_InputBackendMouseDeviceGuid, raw + 2, 0) )
  {
    (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[2] + 44))(raw[2], g_InputBackendMouseDataFormat);
    (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[2] + 52))(raw[2], hwnd, 5);
    if ( (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[2] + 28))(raw[2]) )
      return 0;
    raw[77] = 1;
  }
  if ( (*(int (__stdcall **)(_DWORD, void *, _DWORD *, _DWORD))(*(_DWORD *)raw[0] + 12))(raw[0], &g_InputBackendKeyboardDeviceGuid, raw + 1, 0) )
    goto LABEL_9;
  (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[1] + 44))(raw[1], g_InputBackendKeyboardDataFormat);
  (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[1] + 52))(raw[1], hwnd, 6);
  if ( (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[1] + 28))(raw[1]) )
    return 0;
  raw[78] = 1;
LABEL_9:
  (*(void (__stdcall **)(_DWORD, int, BOOL (__stdcall *)(int, int), _DWORD, int))(*(_DWORD *)raw[0] + 16))(
    raw[0],
    4,
    InputBackend_StoreEnumeratedDevice,
    raw[0],
    1);
  if ( !g_InputBackendTempJoystickDevice )
    return 1;
  if ( (**(int (__stdcall ***)(int, void *, int))g_InputBackendTempJoystickDevice)(
         g_InputBackendTempJoystickDevice,
         &g_InputBackendJoystickInterfaceIid,
         (int)(raw + 3)) )
    return 0;
  if ( g_InputBackendTempJoystickDevice )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)g_InputBackendTempJoystickDevice + 8))(g_InputBackendTempJoystickDevice);
    g_InputBackendTempJoystickDevice = 0;
  }
  (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[3] + 44))(raw[3], g_InputBackendJoystickDataFormat);
  (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[3] + 52))(raw[3], hwnd, 6);
  v5[0] = 24;
  v8 = -1000;
  v9 = 1000;
  v5[1] = 16;
  v6 = 0;
  v7 = 1;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 4, v5) )
    return 0;
  v6 = 4;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 4, v5) )
    return 0;
  v13 = 1000;
  v10[0] = 20;
  v10[1] = 16;
  v11 = 0;
  v12 = 1;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 5, v10) )
    return 0;
  v11 = 4;
  if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(*(_DWORD *)raw[3] + 24))(raw[3], 5, v10)
    || (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[3] + 28))(raw[3]) )
  {
    return 0;
  }
  raw[79] = 1;
  return 1;
}
// 4E80F0: using guessed type int g_InputBackendMouseDataFormat[5];
// 4E9110: using guessed type int g_InputBackendKeyboardDataFormat[5];
// 4E93F0: using guessed type int g_InputBackendJoystickDataFormat[5];
// 4E9792: using guessed type int __stdcall DirectInputCreateA(_DWORD, _DWORD, _DWORD, _DWORD);
// 54DD20: using guessed type int g_InputBackendTempJoystickDevice;

//----- (0047BF30) --------------------------------------------------------
int  InputBackend_Acquire(InputBackendState *state)
{
  _DWORD *raw; // ebx

  raw = (_DWORD *)state;
  if ( raw[77] && raw[2] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[2] + 28))(raw[2]);
  if ( raw[78] && raw[1] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[1] + 28))(raw[1]);
  if ( raw[79] && raw[3] )
    return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 28))(raw[3]);
  return 0;
}

//----- (0047BF80) --------------------------------------------------------
int  InputBackend_Unacquire(InputBackendState *state)
{
  _DWORD *raw; // ebx

  raw = (_DWORD *)state;
  if ( raw[77] && raw[2] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[2] + 32))(raw[2]);
  if ( raw[78] && raw[1] )
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[1] + 32))(raw[1]);
  if ( raw[79] && raw[3] )
    return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 32))(raw[3]);
  return 0;
}

static int InputBackend_ScaleHostMouseDeltaToRecoveredUnits(int render_state, int host_delta)
{
  int sensitivity;
  int fixed_shift;
  int sign;
  unsigned int abs_delta;
  unsigned long long scaled_delta;

  if ( !render_state || !host_delta )
    return host_delta;
  sensitivity = *(_DWORD *)(render_state + 32);
  fixed_shift = *(unsigned __int8 *)(render_state + 1108);
  if ( sensitivity <= 0 || fixed_shift < 0 || fixed_shift >= 24 )
    return host_delta;
  sign = host_delta < 0 ? -1 : 1;
  abs_delta = (unsigned int)(host_delta < 0 ? -host_delta : host_delta);
  scaled_delta = ((unsigned long long)abs_delta << fixed_shift) + (unsigned int)(sensitivity / 2);
  return sign * (int)(scaled_delta / (unsigned int)sensitivity);
}

//----- (0047BFD0) --------------------------------------------------------
int  InputBackend_PollState(InputBackendState *state, int renderState, int a3)
{
  int result; // eax
  _DWORD *raw; // ebx
  _DWORD v4[12]; // [esp+24h] [ebp-6Ch] BYREF
  unsigned __int8 v5; // [esp+54h] [ebp-3Ch]
  unsigned __int8 v6; // [esp+55h] [ebp-3Bh]
  _DWORD v7[3]; // [esp+74h] [ebp-1Ch] BYREF
  unsigned __int8 v8; // [esp+80h] [ebp-10h]
  unsigned __int8 v9; // [esp+81h] [ebp-Fh]
  unsigned __int8 v10; // [esp+82h] [ebp-Eh]
  int v11; // [esp+84h] [ebp-Ch]
  int v12; // [esp+88h] [ebp-8h]
  int fallback_mouse_delta_x;
  int fallback_mouse_delta_y;
  signed char fallback_mouse_primary;
  signed char fallback_mouse_secondary;
  signed char fallback_keyboard_state[256];
  int fallback_mouse_delta_is_host_pixels;

  v12 = a3;
  v11 = renderState;
  result = 0;
  raw = (_DWORD *)state;
  fallback_mouse_delta_x = 0;
  fallback_mouse_delta_y = 0;
  fallback_mouse_primary = 0;
  fallback_mouse_secondary = 0;
  fallback_mouse_delta_is_host_pixels = 0;
  memset(fallback_keyboard_state, 0, sizeof(fallback_keyboard_state));
  if ( !(raw[77] && raw[2]) || !(raw[78] && raw[1]) )
  {
    Platform_ReadInputFallbackState(
      &fallback_mouse_delta_x,
      &fallback_mouse_delta_y,
      &fallback_mouse_primary,
      &fallback_mouse_secondary,
      fallback_keyboard_state,
      sizeof(fallback_keyboard_state),
      &fallback_mouse_delta_is_host_pixels);
    if ( fallback_mouse_delta_is_host_pixels )
    {
      fallback_mouse_delta_x = InputBackend_ScaleHostMouseDeltaToRecoveredUnits(v11, fallback_mouse_delta_x);
      fallback_mouse_delta_y = InputBackend_ScaleHostMouseDeltaToRecoveredUnits(v11, fallback_mouse_delta_y);
    }
  }
  if ( raw[77] && raw[2] )
  {
    if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(**(_DWORD **)&raw[2] + 36))(raw[2], 16, v7) == -2147024866 )
      (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[2] + 28))(raw[2]);
    state->mouse_delta_x = v7[0];
    state->mouse_delta_y = v7[1];
    state->mouse_button_primary = v8;
    state->mouse_button_secondary = v9;
    state->mouse_button_middle = v10;
  }
  else
  {
    state->mouse_delta_x = fallback_mouse_delta_x;
    state->mouse_delta_y = fallback_mouse_delta_y;
    state->mouse_button_primary = fallback_mouse_primary;
    state->mouse_button_secondary = fallback_mouse_secondary;
    state->mouse_button_middle = 0;
  }
  if ( raw[78] && raw[1] )
  {
    result = (*(int (__stdcall **)(_DWORD, int, int))(**(_DWORD **)&raw[1] + 36))(raw[1], 256, (int)&state->keyboard_state[0]);
    if ( result == -2147024866 )
      result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)&raw[1] + 28))(raw[1]);
  }
  else
  {
    qmemcpy(&state->keyboard_state[0], fallback_keyboard_state, sizeof(fallback_keyboard_state));
  }
  if ( raw[79] && raw[3] )
  {
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 100))(raw[3]);
    if ( (*(int (__stdcall **)(_DWORD, int, _DWORD *))(**(_DWORD **)&raw[3] + 36))(raw[3], 80, v4) == -2147024866 )
      (*(void (__stdcall **)(_DWORD))(**(_DWORD **)&raw[3] + 28))(raw[3]);
    state->joystick_axis_x = v4[0];
    state->joystick_axis_y = v4[1];
    state->joystick_button_primary = v5;
    result = v6;
    state->joystick_button_secondary = v6;
  }
  return result;
}

//----- (0047C200) --------------------------------------------------------
int Rules_FindConstructByName()
{
  _DWORD *current; // ecx
  int v1; // ecx

  current = (_DWORD *)g_Rules_ConstructTypeListHead;
  if ( !g_Rules_ConstructTypeListHead )
    return 0;
  while ( strcmp_(current, *current) )
  {
    current = *(_DWORD **)(v1 + 48);
    if ( !current )
      return 0;
  }
  return v1;
}
// 47C21C: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A194: using guessed type int dword_51A194;

//----- (0047C2B0) --------------------------------------------------------
signed int  Rules_Save(const CHAR *fileName, int a2, DWORD a3)
{
  signed int result; // eax
  int v4; // ecx
  int i; // edx
  int v6; // edx

  result = IO_FOpen(fileName, (unsigned __int8 *)aW_1, a2, a3);
  if ( result )
  {
    IO_SetFastSaveFile(result);
    for ( i = g_Rules_SaveFunctionListHead; i; i = *(_DWORD *)(v6 + 12) )
      (*(void (**)(void))(i + 4))();
    fclose_(v4);
    IO_SetFastSaveFile(0);
    return 1;
  }
  return result;
}
// 47C2D9: variable 'v6' is possibly undefined
// 47C2E2: variable 'v4' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A188: using guessed type int dword_51A188;

//----- (0047C340) --------------------------------------------------------
int Rules_GetWatchCompilations()
{
  return g_Rules_WatchCompilationsFlag;
}
// 51A190: using guessed type int dword_51A190;

//----- (0047C350) --------------------------------------------------------
int  Rules_SetLoadInProgress(int result)
{
  g_Rules_LoadInProgressFlag = result;
  return result;
}
// 51A18C: using guessed type int dword_51A18C;

//----- (0047C360) --------------------------------------------------------
int Rules_GetLoadInProgress()
{
  return g_Rules_LoadInProgressFlag;
}
// 51A18C: using guessed type int dword_51A18C;

//----- (0047C370) --------------------------------------------------------
int Rules_RegisterClearResetCommands()
{
  Rules_RegisterHostFunction(aClear, 118, (int)aClearcommand, (int)Rules_ClearCommand, (int)a00_13);
  Rules_RegisterHostFunction(aReset, 118, (int)aResetcommand, (int)Rules_ResetCommand, (int)a00_13);
  return Rules_AddWatchItem((int)aCompilations, 0, 30, (int)&g_Rules_WatchCompilationsFlag, 0, 0);
}
// 51A190: using guessed type int dword_51A190;

//----- (0047C3D0) --------------------------------------------------------
int Rules_ClearCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Rules_Clear();
  return result;
}

//----- (0047C3F0) --------------------------------------------------------
void Rules_ResetCommand()
{
  if ( Lexer_TokenExpect(0) != -1 )
    Rules_Reset();
}

//----- (0047C410) --------------------------------------------------------
void Rules_Reset()
{
  int resetNode; // edx
  int *mainModule; // eax

  if ( !g_Rules_ResetInProgressFlag )
  {
    g_Rules_ResetInProgressFlag = 1;
    if ( !g_ClipsCurrentEvaluationDepth )
      Rules_SetEvaluationErrorFlag(0);
    if ( !g_Rules_BeforeResetCallback || g_Rules_BeforeResetCallback() )
    {
      if ( g_Rules_ResetFunctionListHead )
      {
        resetNode = g_Rules_ResetFunctionListHead;
        do
        {
          if ( Rules_GetEvaluationErrorFlag() )
            break;
          ((void (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(resetNode + 4))();
          resetNode = *(_DWORD *)(resetNode + 12);
        }
        while ( resetNode );
      }
      mainModule = Module_FindByName(aMain);
      Module_SetCurrent((int)mainModule);
      if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
        Rules_RunPeriodicCleanup(1, 0);
      g_Rules_ResetInProgressFlag = 0;
    }
    else
    {
      g_Rules_ResetInProgressFlag = 0;
    }
  }
}
// 47C45A: variable 'v0' is possibly undefined
// 47C45D: variable 'v1' is possibly undefined
// 51A184: using guessed type int dword_51A184;
// 51A198: using guessed type int dword_51A198;
// 51A1A8: using guessed type int (*dword_51A1A8)(void);
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (0047C4E0) --------------------------------------------------------
signed int  Rules_AddResetFunction(int name, int priority, int callback)
{
  g_Rules_ResetFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_ResetFunctionListHead, priority);
  return 1;
}
// 51A198: using guessed type int dword_51A198;

//----- (0047C530) --------------------------------------------------------
signed int Rules_Clear()
{
  int i; // edx
  int (*clear_callback)(void); // eax
  signed int result; // eax

  IO_ActivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
  if ( Rules_ClearReady() )
  {
    g_Rules_ClearInProgressFlag = 1;
    for ( i = g_Rules_ClearFunctionListHead; i; i = *(_DWORD *)(i + 12) )
    {
      clear_callback = (int (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(i + 4);
      clear_callback();
    }
    result = IO_DeactivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
    if ( !g_ClipsCurrentEvaluationDepth && !g_ClipsCommandEvalInProgress && !g_ClipsCurrentExpression )
      result = Rules_RunPeriodicCleanup(1, 0);
    g_Rules_ClearInProgressFlag = 0;
  }
  else
  {
    Rules_PrintErrorID((int)aConstrct, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSomeConstructs, 0);
    return IO_DeactivateRouter((int)g_IO_LogicalNameTable_WTrace[0]);
  }
  return result;
}
// 51A180: using guessed type int dword_51A180;
// 51A19C: using guessed type int dword_51A19C;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;

//----- (0047C5E0) --------------------------------------------------------
int Rules_ClearReady()
{
  int item; // edx
  int result; // eax
  int (*query_callback)(void); // eax

  item = g_Rules_ClearReadyFunctionListHead;
  if ( !item )
    return 1;
  while ( 1 )
  {
    query_callback = (int (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(item + 4);
    result = query_callback();
    if ( !result )
      break;
    item = *(_DWORD *)(item + 12);
    if ( !item )
      return 1;
  }
  return result;
}
// 51A1A0: using guessed type int dword_51A1A0;

//----- (0047C610) --------------------------------------------------------
signed int  Rules_AddClearReadyFunction(int name, int priority, int callback)
{
  g_Rules_ClearReadyFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_ClearReadyFunctionListHead, priority);
  return 1;
}
// 51A1A0: using guessed type int dword_51A1A0;

//----- (0047C660) --------------------------------------------------------
signed int  Rules_AddClearFunction(int name, int priority, int callback)
{
  g_Rules_ClearFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_ClearFunctionListHead, priority);
  return 1;
}
// 51A19C: using guessed type int dword_51A19C;

//----- (0047C680) --------------------------------------------------------
BOOL Rules_RemoveClearFunction(int name)
{
  _DWORD v3[3]; // [esp+0h] [ebp-Ch] BYREF

  g_Rules_ClearFunctionListHead = Rules_RemoveNamedCallbackReturningHead(name, g_Rules_ClearFunctionListHead, v3);
  return v3[0] != 0;
}
// 51A19C: using guessed type int dword_51A19C;

//----- (0047C6B0) --------------------------------------------------------
int Rules_GetReentryGuardFlag()
{
  return g_Rules_ReentryGuardFlag;
}
// 51A1A4: using guessed type int dword_51A1A4;

//----- (0047C6C0) --------------------------------------------------------
int  Rules_SetReentryGuardFlag(int result)
{
  g_Rules_ReentryGuardFlag = result;
  return result;
}
// 51A1A4: using guessed type int dword_51A1A4;

//----- (0047C6D0) --------------------------------------------------------
_DWORD * Module_BuildNameListMultifield(_DWORD *multifield, int (*getNextFn)(void), int (*getNameFn)(void))
{
  signed int count; // ecx
  int v7; // eax
  int v8; // ecx
  _DWORD *fieldPtr; // ebx
  _DWORD *result; // eax
  char *name; // eax
  int v12; // ecx
  int v13; // ecx

  if ( ((int (__thiscall *)(_DWORD))getNextFn)(0) )
  {
    do
    {
      v7 = getNextFn();
      count = v8 + 1;
    }
    while ( v7 );
  }
  multifield[1] = 4;
  multifield[4] = count - 1;
  multifield[3] = 0;
  fieldPtr = Rules_CreateEphemeralMultifield(count);
  multifield[2] = fieldPtr;
  result = (_DWORD *)((int (__thiscall *)(int))getNextFn)(1);
  if ( result )
  {
    while ( g_ClipsHaltExecution != 1 )
    {
      *((_WORD *)fieldPtr + 7) = 2;
      fieldPtr = (_DWORD *)((char *)fieldPtr + 6);
      name = (char *)getNameFn();
      *(_DWORD *)((char *)fieldPtr + 10) = Str_Intern(name, v12);
      result = (_DWORD *)((int (__thiscall *)(int))getNextFn)(v13 + 1);
      if ( !result )
        return result;
    }
    return Rules_SetMultifieldErrorValue((int)multifield);
  }
  return result;
}
// 47C6E6: variable 'v8' is possibly undefined
// 47C6F0: variable 'v6' is possibly undefined
// 47C737: variable 'v12' is possibly undefined
// 47C741: variable 'v13' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (0047C760) --------------------------------------------------------
int  Rules_FreeConstructHeaderString(int *header, int a2)
{
  int result; // eax
  const char *ppForm; // edx

  result = Rules_DecrementSymbolCount(*header, a2);
  ppForm = (const char *)header[1];
  if ( ppForm )
  {
    result = Mem_SmallBlockFree((_DWORD *)header[1], strlen(ppForm) + 1);
    header[1] = 0;
  }
  return result;
}

//----- (0047C7A0) --------------------------------------------------------
_DWORD * Rules_RegisterConstructType(
        int constructName,
        int pluralName,
        int parseFunction,
        int findFunction,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        int a12)
{
  _DWORD *block; // edi
  _DWORD *result; // eax

  block = *(_DWORD **)(g_ClipsMemoryTable + 208);
  if ( block )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 208);
    *(_DWORD *)(g_ClipsMemoryTable + 208) = *block;
    result = (_DWORD *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x34);
  }
  *result = constructName;
  result[1] = pluralName;
  result[2] = findFunction;
  result[3] = parseFunction;
  result[4] = a5;
  result[5] = a6;
  result[6] = a7;
  result[7] = a8;
  result[8] = a9;
  result[9] = a10;
  result[10] = a11;
  result[11] = a12;
  result[12] = g_Rules_ConstructTypeListHead;
  g_Rules_ConstructTypeListHead = (int)result;
  return result;
}
// 47C7CE: variable 'a3' is possibly undefined
// 51A194: using guessed type int dword_51A194;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047C830) --------------------------------------------------------
signed int  Rules_AddSaveFunction(int name, int priority, int callback)
{
  g_Rules_SaveFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_SaveFunctionListHead, priority);
  return 1;
}
// 51A188: using guessed type int dword_51A188;

//----- (0047C850) --------------------------------------------------------
signed int  Rules_Bload(int fileName, DWORD a2)
{
  signed int result; // eax
  int i; // edx
  int callback; // eax
  int construct; // ecx
  int next_construct; // ecx
  int construct_table; // ecx
  int skip_size; // [esp+2Ch] [ebp-20h] BYREF
  int function_table_count; // [esp+28h] [ebp-24h] BYREF
  int missing_functions; // [esp+30h] [ebp-1Ch] BYREF
  char construct_name[20]; // [esp+0h] [ebp-4Ch] BYREF
  char header[20]; // [esp+14h] [ebp-38h] BYREF

  result = Rules_BloadOpenFile((const CHAR *)(uintptr_t)(unsigned int)fileName, a2);
  if ( !result )
    return result;
  Rules_BloadReadBlock((uintptr_t)header, strlen((const char *)g_Rules_BloadFileHeaderID) + 1);
  if ( strcmp(header, (const char *)g_Rules_BloadFileHeaderID) )
  {
    Rules_PrintErrorID((int)aBload_0, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFile, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], fileName, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotABinaryCo, 0);
    Rules_BloadCloseFile(0);
    return 0;
  }
  Rules_BloadReadBlock((uintptr_t)header, strlen(g_Rules_BsaveVersionID) + 1);
  if ( strcmp(header, g_Rules_BsaveVersionID) )
  {
    Rules_PrintErrorID((int)aBload_0, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFile, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], fileName, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsAnIncompatib, 0);
LABEL_20:
    Rules_BloadCloseFile(0);
    return 0;
  }
  if ( g_Rules_FactsBloadedFlag && !Rules_ClearBload() )
    goto LABEL_20;
  if ( !Rules_ClearReady() )
  {
    Rules_BloadCloseFile(0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheClipsEnviro, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBinaryLoadCann, 0);
    return 0;
  }
  for ( i = g_Rules_BeforeBloadFunctionListHead; i; i = *(_DWORD *)(i + 12) )
  {
    callback = *(_DWORD *)(i + 4);
    if ( callback )
      ((void (*)(void))(uintptr_t)(unsigned int)callback)();
  }
  g_Rules_BloadFunctionPtrTable = Rules_ReadNeededFunctions(&function_table_count, &missing_functions);
  if ( missing_functions )
  {
    Rules_BloadCloseFile(0);
    Rules_CallAbortBloadFunctions();
    return 0;
  }
  Rules_BloadAtomTables();
  Rules_BloadAllocExpressionArray();
  Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
  while ( strncmp(construct_name, (const char *)g_Rules_BloadFileHeaderID, 0x14u) )
  {
    construct = g_BinaryItemListHead;
    if ( construct )
    {
      while ( strncmp((const char *)(uintptr_t)(unsigned int)*(_DWORD *)construct, construct_name, 0x14u) )
      {
        construct = *(_DWORD *)(construct + 36);
        if ( !construct )
          goto LABEL_29;
      }
      callback = *(_DWORD *)(construct + 8);
      if ( callback )
      {
        ((void (*)(void))(uintptr_t)(unsigned int)callback)();
        goto LABEL_27;
      }
    }
LABEL_29:
    Rules_BloadReadBlock((uintptr_t)&skip_size, 4u);
    Rules_BloadSeekFile(skip_size, 0);
    if ( skip_size )
    {
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aSkipping, 0);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], fileName, 0);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aConstructsBeca, 0);
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
    else
    {
LABEL_27:
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
  }
  Rules_BloadRefreshExpressions();
  Rules_BloadConstraints();
  Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
  while ( strncmp(construct_name, (const char *)g_Rules_BloadFileHeaderID, 0x14u) )
  {
    construct_table = g_BinaryItemListHead;
    if ( !construct_table )
      goto LABEL_32;
    while ( strncmp((const char *)(uintptr_t)(unsigned int)*(_DWORD *)construct_table, construct_name, 0x14u) )
    {
      construct_table = *(_DWORD *)(construct_table + 36);
      if ( !construct_table )
        goto LABEL_32;
    }
    next_construct = *(_DWORD *)(construct_table + 12);
    if ( next_construct )
    {
      ((void (*)(void))(uintptr_t)(unsigned int)next_construct)();
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
    else
    {
LABEL_32:
      Rules_BloadReadBlock((uintptr_t)&skip_size, 4u);
      Rules_BloadSeekFile(skip_size, 0);
      Rules_BloadReadBlock((uintptr_t)construct_name, 0x14u);
    }
  }
  Rules_BloadCloseFile(0);
  if ( g_Rules_BloadFunctionPtrTable )
    Mem_ReleasePoolBlock(g_Rules_BloadFunctionPtrTable, 4 * function_table_count);
  Rules_FreeBloadAtomTables();
  for ( i = g_Rules_AfterBloadCallbackListHead; i; i = *(_DWORD *)(i + 12) )
  {
    callback = *(_DWORD *)(i + 4);
    if ( callback )
      ((void (*)(void))(uintptr_t)(unsigned int)callback)();
  }
  g_Rules_FactsBloadedFlag = 1;
  Rules_AddClearFunction((int)aBload, (int)Rules_ClearBload, 10000);
  return 1;
}
// 47CAF7: conditional instruction was optimized away because edi.4==0
// 47C89B: variable 'v4' is possibly undefined
// 47C8CE: variable 'v5' is possibly undefined
// 47C90B: variable 'v9' is possibly undefined
// 47C965: variable 'v10' is possibly undefined
// 47C99B: variable 'v11' is possibly undefined
// 47C9C9: variable 'v14' is possibly undefined
// 47C9FB: variable 'v15' is possibly undefined
// 47CA07: variable 'v16' is possibly undefined
// 47CA16: variable 'v17' is possibly undefined
// 47CA1B: variable 'v18' is possibly undefined
// 47CA47: variable 'v19' is possibly undefined
// 47CA53: variable 'v20' is possibly undefined
// 47CA62: variable 'v21' is possibly undefined
// 47CA67: variable 'v6' is possibly undefined
// 47CA78: variable 'v7' is possibly undefined
// 47CA87: variable 'v22' is possibly undefined
// 47CA96: variable 'v23' is possibly undefined
// 47CAD8: variable 'v25' is possibly undefined
// 47CB20: variable 'v26' is possibly undefined
// 47CB2C: variable 'v27' is possibly undefined
// 47CB3B: variable 'v28' is possibly undefined
// 47CB86: variable 'v12' is possibly undefined
// 47CBB9: variable 'v30' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 48A1ED: using guessed type int __fastcall strncmp_(_DWORD, _DWORD);
// 51A1AC: using guessed type int dword_51A1AC;
// 51A1B0: using guessed type int dword_51A1B0;
// 51A1B4: using guessed type int dword_51A1B4;
// 51A1C0: using guessed type void *off_51A1C0;
// 51A1C4: using guessed type char *off_51A1C4;
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51AA3C: using guessed type int dword_51AA3C;
// 54DD24: using guessed type int dword_54DD24;

//----- (0047CBF0) --------------------------------------------------------
signed int  Rules_BloadAndRefresh(
        signed int result,
        int itemSize,
        void (__fastcall *updateFunction)(signed int, signed int))
{
  int previous_allocator_handler;
  signed int chunk_count;
  int chunk_bytes;
  signed int chunk_base;
  signed int initialized_count;
  int entries_this_pass;
  int entry_index;
  int entry_ptr;

  if ( !result )
    return result;

  previous_allocator_handler = Mem_SetOutOfMemoryHandler((int)CSyncObject_Unlock);
  chunk_count = result;
  do
  {
    chunk_bytes = itemSize * chunk_count;
    chunk_base = Mem_HeapAllocWithRetry((_DWORD *)chunk_bytes);
    if ( !chunk_base )
    {
      if ( chunk_count / 2 )
      {
        chunk_count /= 2;
      }
      else if ( ((int (__cdecl *)(int))(intptr_t)previous_allocator_handler)(chunk_bytes) == 1 )
      {
        return Mem_SetOutOfMemoryHandler(previous_allocator_handler);
      }
    }
  }
  while ( !chunk_base );

  Mem_SetOutOfMemoryHandler(previous_allocator_handler);
  initialized_count = 0;
  while ( initialized_count < result )
  {
    entries_this_pass = result - initialized_count;
    if ( entries_this_pass > chunk_count )
      entries_this_pass = chunk_count;
    Rules_BloadReadBlock(chunk_base, entries_this_pass * itemSize);
    if ( entries_this_pass > 0 )
    {
      entry_ptr = chunk_base;
      for ( entry_index = 0; entry_index < entries_this_pass; ++entry_index )
      {
        updateFunction(entry_ptr, initialized_count);
        ++initialized_count;
        entry_ptr += itemSize;
      }
    }
  }
  return Mem_ReleasePoolBlock(chunk_base, chunk_bytes);
}

//----- (0047CCF0) --------------------------------------------------------
int  Rules_ReadNeededFunctions(int *functionCountPtr, int *errorFlagPtr)
{
  int unresolved; // ebx
  int string_bytes; // [esp+0h] [ebp-28h] BYREF
  char *function_name; // esi
  int function_count; // edi
  int table_bytes; // [esp+Ch] [ebp-1Ch]
  int table; // [esp+10h] [ebp-18h]
  int resolved_function; // ebp
  int i; // [esp+1Ch] [ebp-Ch]
  char *names; // [esp+4h] [ebp-24h]

  Rules_BloadReadBlock((uintptr_t)functionCountPtr, 4u);
  Rules_BloadReadBlock((uintptr_t)&string_bytes, 4u);
  unresolved = 0;
  function_count = *functionCountPtr;
  if ( !function_count )
  {
    *errorFlagPtr = 0;
    return 0;
  }
  names = (char *)(uintptr_t)(unsigned int)Mem_HeapAllocWithRetry((_DWORD *)string_bytes);
  Rules_BloadReadBlock((uintptr_t)names, (unsigned int)string_bytes);
  table_bytes = 4 * function_count;
  table = Mem_HeapAllocWithRetry((_DWORD *)table_bytes);
  resolved_function = 0;
  function_name = names;
  for ( i = 0; i < function_count; ++i )
  {
    resolved_function = Rules_FindFunctionByName((int)(uintptr_t)function_name, resolved_function);
    if ( !resolved_function )
    {
      if ( !unresolved )
      {
        Rules_PrintErrorID((int)aBload_0, 6, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheFollowingUn, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aReferencedByTh, 0);
      }
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_502A88, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)(uintptr_t)function_name, 0);
      unresolved = 1;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_502A8C, 0);
    }
    *(_DWORD *)(table + 4 * i) = resolved_function;
    function_name += strlen(function_name) + 1;
  }
  Mem_ReleasePoolBlock((int)(uintptr_t)names, string_bytes);
  if ( unresolved )
  {
    Mem_ReleasePoolBlock(table, table_bytes);
    table = 0;
  }
  *errorFlagPtr = unresolved;
  return table;
}
// 47CDD0: variable 'v13' is possibly undefined
// 47CDE4: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047CE60) --------------------------------------------------------
int __fastcall Rules_FindFunctionByName(int functionName, int lastFound)
{
  int head; // edi
  int current; // ecx
  int next; // ecx
  const char *registered_name; // edx

  head = Rules_GetFunctionDefinitionListHead();
  if ( !head )
    return 0;
  current = lastFound ? *(_DWORD *)(lastFound + 27) : head;
  while ( current )
  {
    registered_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(*(_DWORD *)current + 16);
    if ( !strcmp((const char *)(uintptr_t)(unsigned int)functionName, registered_name) )
      return current;
    next = *(_DWORD *)(current + 27);
    if ( next == lastFound )
      return 0;
    current = next ? next : head;
  }
  return 0;
}

//----- (0047CEB0) --------------------------------------------------------
int Rules_IsBloaded()
{
  return g_Rules_FactsBloadedFlag;
}
// 51A1AC: using guessed type int dword_51A1AC;

//----- (0047CEC0) --------------------------------------------------------
signed int Rules_ClearBload()
{
  int failed; // edx
  int callback_node; // ecx
  int construct_node; // edx
  int callback; // eax

  failed = 0;
  for ( callback_node = g_Rules_BloadClearReadyCallbackListHead; callback_node; callback_node = *(_DWORD *)(callback_node + 12) )
  {
    callback = *(_DWORD *)(callback_node + 4);
    if ( callback && !((int (*)(void))(uintptr_t)(unsigned int)callback)() )
    {
      if ( !failed )
      {
        Rules_PrintErrorID((int)aBload_0, 5, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSomeConstruc_0, 0);
      }
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_502A88, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(callback_node + 0), 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_502A8C, 0);
      failed = 1;
    }
  }
  if ( failed == 1 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBinaryClearCan, 0);
    return 0;
  }
  else
  {
    for ( construct_node = g_BinaryItemListHead; construct_node; construct_node = *(_DWORD *)(construct_node + 36) )
    {
      callback = *(_DWORD *)(construct_node + 16);
      if ( callback )
        ((void (*)(void))(uintptr_t)(unsigned int)callback)();
    }
    Rules_FreeBloadedExpressions();
    Rules_ClearBloadedConstraints();
    g_Rules_FactsBloadedFlag = 0;
    Rules_RemoveClearFunction((int)aBload);
    return 1;
  }
}
// 51A1AC: using guessed type int dword_51A1AC;
// 51A1B8: using guessed type int dword_51A1B8;
// 51A614: using guessed type char *off_51A614[5];
// 51AA3C: using guessed type int dword_51AA3C;

//----- (0047CF90) --------------------------------------------------------
int Rules_CallAbortBloadFunctions()
{
  int callback_node; // edx
  int callback; // eax
  int result; // eax

  result = 0;
  for ( callback_node = g_Rules_AbortBloadCallbackListHead; callback_node; callback_node = *(_DWORD *)(callback_node + 12) )
  {
    callback = *(_DWORD *)(callback_node + 4);
    if ( callback )
      result = ((int (*)(void))(uintptr_t)(unsigned int)callback)();
  }
  return result;
}
// 51A1BC: using guessed type int dword_51A1BC;

//----- (0047CFC0) --------------------------------------------------------
_DWORD * Rules_AddBeforeBloadFunction(int name, int priority, int callback)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_BeforeBloadFunctionListHead, priority);
  g_Rules_BeforeBloadFunctionListHead = (int)result;
  return result;
}
// 51A1B0: using guessed type int dword_51A1B0;

//----- (0047CFE0) --------------------------------------------------------
_DWORD * Rules_AddAfterBloadFunction(int name, int priority, int callback)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_AfterBloadCallbackListHead, priority);
  g_Rules_AfterBloadCallbackListHead = (int)result;
  return result;
}
// 51A1B4: using guessed type int dword_51A1B4;

//----- (0047D020) --------------------------------------------------------
_DWORD * Rules_AddAbortBloadFunction(int name, int priority, int callback)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, callback, g_Rules_AbortBloadCallbackListHead, priority);
  g_Rules_AbortBloadCallbackListHead = (int)result;
  return result;
}
// 51A1BC: using guessed type int dword_51A1BC;

//----- (0047D050) --------------------------------------------------------
signed int Rules_ReportCannotLoadWithBload()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aBload_0, 1, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotLoad, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aConstructWithB, v2);
}
// 47D070: variable 'v0' is possibly undefined
// 47D07C: variable 'v1' is possibly undefined
// 47D08B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047D0A0) --------------------------------------------------------
int  Rules_BloadCommand(DWORD a1, double a2)
{
  int v2; // ecx
  int result; // eax

  if ( Lexer_TokenExpect(1) == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v2, a2);
  if ( result )
    return Rules_Bload(result, a1);
  return result;
}
// 47D0C7: variable 'v2' is possibly undefined

//----- (0047D0E0) --------------------------------------------------------
void __fastcall Rules_InitializeEngine(int a1, int a2)
{
  (void)a1;
  (void)a2;
  if ( !g_Rules_EngineInitializedFlag )
  {
    Mem_InitReserveBlock(0, 0);
    Rules_InitAtomTables();
    Rules_RegisterExitFunction();
    CRT_RegisterSignalHandler(1, Rules_ShutdownEngine);
    Rules_RegisterBuiltinFunctionGroups();
    Rules_RegisterAllHostFunctions();
    Rules_RegisterConstraintCheckingCommands();
    Rules_InitExpressionHashTable();
    Rules_RegisterClearResetCommands();
    Rules_InitializeDefrules();
    Rules_InitDeffactsConstruct();
    Defgeneric_SetupConstruct();
    Deffunction_InitConstructType();
    Defglobal_InitConstructType();
    Rules_RegisterDeftemplateConstruct();
    Rules_InitObjectSystem(0);
    Module_InitializeDefmodules();
    ProcParam_RegisterPrimitiveTypes();
    Rules_Clear();
    g_Rules_EngineInitializedFlag = 1;
  }
}
// 47D4E0: using guessed type int sub_47D4E0();
// 49A0E0: using guessed type int __cdecl sub_49A0E0(void);
// 496643: using guessed type int __fastcall sub_496643(_DWORD, _DWORD);
// 51A1D4: using guessed type int dword_51A1D4;

//----- (0047D320) --------------------------------------------------------
signed int Rules_RegisterBuiltinFunctionGroups()
{
  Rules_RegisterControlFlowFunctions();
  Rules_RegisterMiscFunctions();
  Rules_RegisterIOHostFunctions();
  Rules_RegisterPredicateHostFunctions();
  Rules_RegisterArithmeticFunctions();
  Rules_RegisterFileIOCommands();
  Rules_RegisterWatchFunctions();
  Rules_RegisterMultifieldFunctions();
  Rules_RegisterStringBuiltins();
  Rules_RegisterMathBuiltins();
  Rules_RegisterHelpFunctions();
  return Rules_RegisterConstructsToCFunction();
}

//----- (0047D360) --------------------------------------------------------
double Rules_TimeCommand()
{
  struct
  {
    int time_value;
    unsigned __int16 milliseconds;
    __int16 timezone_minutes;
    __int16 dst_flag;
  } v4;

  ftime_(&v4);
  return (double)(v4.time_value % 10000) + (double)v4.milliseconds / g_Rules_MillisecondsPerSecond;
}
// 502B70: using guessed type double dbl_502B70;

//----- (0047D3D0) --------------------------------------------------------
int  Rules_SystemCommand(double frame)
{
  char *commandBuffer; // edi
  int result; // eax
  int argCount; // ebp
  int argIndex; // esi
  int v5; // edx
  int v6; // [esp+0h] [ebp-38h] BYREF
  int v7; // [esp+4h] [ebp-34h]
  int v8; // [esp+8h] [ebp-30h]
  int v9; // [esp+18h] [ebp-20h] BYREF
  unsigned int v10[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  commandBuffer = 0;
  v9 = 0;
  v10[0] = 0;
  result = Lexer_TokenExpect(1);
  argCount = result;
  if ( result != -1 )
  {
    argIndex = 1;
    if ( result < 1 )
    {
LABEL_6:
      if ( commandBuffer )
      {
        if ( g_Rules_SystemCommandPreShellHook )
          g_Rules_SystemCommandPreShellHook();
        system_(commandBuffer);
        if ( g_Rules_SystemCommandPostShellHookA )
          g_Rules_SystemCommandPostShellHookA();
        if ( g_Rules_SystemCommandPostShellHookB )
          g_Rules_SystemCommandPostShellHookB();
        return Mem_SmallBlockFree(commandBuffer, v10[0]);
      }
    }
    else
    {
      while ( 1 )
      {
        Rules_RtnUnknown(argIndex, &v6, frame);
        if ( v7 != 3 && v7 != 2 )
          break;
        ++argIndex;
        result = (int)Str_Append(*(const char **)(v8 + 16), commandBuffer, v10, &v9);
        commandBuffer = (char *)result;
        if ( argIndex > argCount )
          goto LABEL_6;
      }
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return (int)Rules_ReportSymbolTypeError(aSystem_0, v5);
    }
  }
  return result;
}
// 47D4AD: variable 'v5' is possibly undefined
// 51A1C8: using guessed type int (*dword_51A1C8)(void);
// 51A1CC: using guessed type int (*dword_51A1CC)(void);
// 51A1D0: using guessed type int (*dword_51A1D0)(void);

//----- (0047D4E0) --------------------------------------------------------
int Rules_ShutdownEngine()
{
  void *v0; // ecx
  int v1; // edx
  int v2; // ecx

  Rules_SetEvaluationErrorFlag(1);
  Rules_CloseAllBatchSources(v0);
  return CRT_RegisterSignalHandler(v2, v1);
}
// 47D4F0: variable 'v0' is possibly undefined
// 47D4FA: variable 'v2' is possibly undefined
// 47D4FA: variable 'v1' is possibly undefined
// 47D4E0: using guessed type int sub_47D4E0();
// 496643: using guessed type int __fastcall sub_496643(_DWORD, _DWORD);

//----- (0047D540) --------------------------------------------------------
BOOL __fastcall Rules_BloadDeleteFile(int path, int a2)
{
  return IO_RemoveFileByPath(path, a2) == 0;
}
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);

//----- (0047D550) --------------------------------------------------------
BOOL  Rules_RenameFile(const CHAR *oldFileName, const CHAR *newFileName, int a3)
{
  return IO_RenameFile(oldFileName, newFileName, a3) == 0;
}

//----- (0047D560) --------------------------------------------------------
signed int  Rules_BloadOpenFile(const CHAR *fileName, DWORD a2)
{
  int v2; // ecx

  g_ClipsBloadFileHandle = IO_FOpen(fileName, (unsigned __int8 *)aRb_1, (int)fileName, a2);
  if ( g_ClipsBloadFileHandle )
    return 1;
  Rules_OpenFileErrorMessage(v2, v2);
  return 0;
}
// 47D587: variable 'v2' is possibly undefined
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D5A0) --------------------------------------------------------
int  Rules_BloadReadBlock(uintptr_t buffer, unsigned int size)
{
  if ( !size )
    return 0;
  return fread_((void *)buffer, size, g_ClipsBloadFileHandle, 1);
}
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D600) --------------------------------------------------------
signed int  Rules_BloadSeekFile(int offset, int a2)
{
  return IO_SeekStreamGuarded(g_ClipsBloadFileHandle, offset, 1u, a2);
}
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D630) --------------------------------------------------------
int __thiscall Rules_BloadCloseFile(void *this)
{
  (void)this;
  return fclose_(g_ClipsBloadFileHandle);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D660) --------------------------------------------------------
_DWORD * Rules_InsertActivationSorted(int *agenda, _DWORD *activation)
{
  uintptr_t list_ref; // ebx
  uintptr_t node; // ecx
  uintptr_t current; // esi
  uintptr_t predecessor; // edx
  uintptr_t next; // eax

  Rules_SetAgendaChanged(1);
  list_ref = (uintptr_t)agenda;
  node = (uintptr_t)activation;
  current = (uintptr_t)(unsigned int)*(_DWORD *)list_ref;
  predecessor = 0;
  if ( current )
  {
    switch ( g_Rules_ConflictResolutionStrategy )
    {
      case 0:
        predecessor = (uintptr_t)Rules_PlaceInDepthList((_DWORD *)current, (int)node);
        break;
      case 1:
        predecessor = (uintptr_t)Rules_PlaceInBreadthList((_DWORD *)current, (int)node);
        break;
      case 2:
        predecessor = (uintptr_t)Rules_PlaceInLexList((_DWORD *)current, (int)node);
        break;
      case 3:
        predecessor = (uintptr_t)Rules_PlaceInMeaList((_DWORD *)current, (int)node);
        break;
      case 4:
        predecessor = (uintptr_t)Rules_PlaceInComplexityList((_DWORD *)current, (_DWORD *)node);
        break;
      case 5:
        predecessor = (uintptr_t)Rules_PlaceInSimplicityList((_DWORD *)current, (_DWORD *)node);
        break;
      case 6:
        predecessor = (uintptr_t)Rules_PlaceInRandomList((_DWORD *)current, (_DWORD *)node);
        break;
      default:
        break;
    }
  }
  if ( predecessor )
  {
    next = (uintptr_t)(unsigned int)*(_DWORD *)(predecessor + 28);
    *(_DWORD *)(node + 28) = (int)next;
    *(_DWORD *)(node + 24) = (int)predecessor;
    *(_DWORD *)(predecessor + 28) = (int)node;
    if ( next )
      *(_DWORD *)(next + 24) = (int)node;
  }
  else
  {
    next = (uintptr_t)(unsigned int)*(_DWORD *)list_ref;
    *(_DWORD *)(node + 28) = (int)next;
    *(_DWORD *)list_ref = (int)node;
    if ( next )
      *(_DWORD *)(next + 24) = (int)node;
  }
  return (_DWORD *)next;
}
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047D720) --------------------------------------------------------
_DWORD * Rules_PlaceInDepthList(_DWORD *listHead, int newActivation)
{
  int salience; // ecx
  unsigned int timeTag; // ebx
  _DWORD *insertAfter; // edx
  int nodeSalience; // esi

  salience = *(_DWORD *)(newActivation + 8);
  timeTag = *(_DWORD *)(newActivation + 12);
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      if ( timeTag >= listHead[3] )
        break;
    }
    insertAfter = listHead;
    listHead = (_DWORD *)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D760) --------------------------------------------------------
_DWORD * Rules_PlaceInBreadthList(_DWORD *listHead, int newActivation)
{
  int salience; // ecx
  unsigned int timeTag; // ebx
  _DWORD *insertAfter; // edx
  int nodeSalience; // esi

  salience = *(_DWORD *)(newActivation + 8);
  timeTag = *(_DWORD *)(newActivation + 12);
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      if ( timeTag <= listHead[3] )
        break;
    }
    insertAfter = listHead;
    listHead = (_DWORD *)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D7A0) --------------------------------------------------------
_DWORD * Rules_PlaceInLexList(_DWORD *listHead, int newActivation)
{
  _DWORD *current; // ecx
  unsigned int timeTag; // ebp
  int salience; // edi
  _DWORD *insertAfter; // ebx
  int nodeSalience; // eax
  signed int comparison; // eax

  current = listHead;
  if ( !*(_DWORD *)(newActivation + 16) )
    *(_DWORD *)(newActivation + 16) = Rules_BuildLexBasisOrder(*(int **)(newActivation + 4));
  timeTag = *(_DWORD *)(newActivation + 12);
  salience = *(_DWORD *)(newActivation + 8);
  insertAfter = 0;
  if ( !current )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = current[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      comparison = Rules_CompareActivationBasis((int)current, (_DWORD **)newActivation);
      if ( comparison )
      {
        if ( comparison == 1 )
          return insertAfter;
        if ( timeTag <= current[3] )
          break;
      }
    }
    insertAfter = current;
    current = (_DWORD *)current[7];
    if ( !current )
      return insertAfter;
  }
  return insertAfter;
}
// 47D7B9: variable 'v2' is possibly undefined

//----- (0047D810) --------------------------------------------------------
_DWORD * Rules_PlaceInMeaList(_DWORD *listHead, int newActivation)
{
  _DWORD *current; // ecx
  _DWORD *insertAfter; // esi
  int v5; // eax
  int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // ebp
  signed int comparison; // eax
  unsigned int timeTag; // [esp+0h] [ebp-1Ch]
  int salience; // [esp+4h] [ebp-18h]

  current = listHead;
  if ( !*(_DWORD *)(newActivation + 16) )
    *(_DWORD *)(newActivation + 16) = Rules_BuildLexBasisOrder(*(int **)(newActivation + 4));
  timeTag = *(_DWORD *)(newActivation + 12);
  insertAfter = 0;
  salience = *(_DWORD *)(newActivation + 8);
  if ( !current )
    return insertAfter;
  while ( 1 )
  {
    v5 = current[2];
    if ( v5 > salience )
      goto LABEL_5;
    if ( v5 < salience )
      return insertAfter;
    v7 = *(_DWORD *)(*(_DWORD *)(newActivation + 4) + 8);
    v8 = -1;
    v9 = -1;
    if ( *(_DWORD *)v7 )
      v8 = *(_DWORD *)(*(_DWORD *)v7 + 12);
    v10 = **(_DWORD **)(current[1] + 8);
    if ( v10 )
      v9 = *(_DWORD *)(v10 + 12);
    if ( v9 < v8 )
    {
      if ( v8 > 0 )
        return insertAfter;
      goto LABEL_5;
    }
    if ( v9 > v8 )
    {
      if ( v9 <= 0 )
        return insertAfter;
      goto LABEL_5;
    }
    comparison = Rules_CompareActivationBasis((int)current, (_DWORD **)newActivation);
    if ( comparison )
    {
      if ( comparison == 1 )
        return insertAfter;
      if ( timeTag <= current[3] )
        return insertAfter;
    }
LABEL_5:
    insertAfter = current;
    current = (_DWORD *)current[7];
    if ( !current )
      return insertAfter;
  }
}
// 47D833: variable 'v2' is possibly undefined

//----- (0047D8D0) --------------------------------------------------------
_DWORD * Rules_PlaceInComplexityList(_DWORD *listHead, _DWORD *newActivation)
{
  unsigned int timeTag; // edi
  int salience; // ebx
  int complexity; // esi
  _DWORD *insertAfter; // edx
  int nodeSalience; // ecx
  int nodeComplexity; // ecx

  timeTag = newActivation[3];
  salience = newActivation[2];
  complexity = *(_DWORD *)(*newActivation + 28) & 0x7FF;
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      nodeComplexity = *(_DWORD *)(*listHead + 28) & 0x7FF;
      if ( complexity >= nodeComplexity )
      {
        if ( complexity > nodeComplexity )
          return insertAfter;
        if ( timeTag <= listHead[3] )
          break;
      }
    }
    insertAfter = listHead;
    listHead = (_DWORD *)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D930) --------------------------------------------------------
_DWORD * Rules_PlaceInSimplicityList(_DWORD *listHead, _DWORD *newActivation)
{
  unsigned int timeTag; // edi
  int salience; // ebx
  int complexity; // esi
  _DWORD *insertAfter; // edx
  int nodeSalience; // ecx
  int nodeComplexity; // ecx

  timeTag = newActivation[3];
  salience = newActivation[2];
  complexity = *(_DWORD *)(*newActivation + 28) & 0x7FF;
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      nodeComplexity = *(_DWORD *)(*listHead + 28) & 0x7FF;
      if ( complexity <= nodeComplexity )
      {
        if ( complexity < nodeComplexity )
          return insertAfter;
        if ( timeTag <= listHead[3] )
          break;
      }
    }
    insertAfter = listHead;
    listHead = (_DWORD *)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D990) --------------------------------------------------------
_DWORD * Rules_PlaceInRandomList(_DWORD *listHead, _DWORD *newActivation)
{
  unsigned int timeTag; // esi
  int salience; // ecx
  int randomValue; // ebx
  _DWORD *insertAfter; // edx
  int nodeSalience; // edi
  int nodeRandom; // edi

  timeTag = newActivation[3];
  salience = newActivation[2];
  randomValue = newActivation[5];
  insertAfter = 0;
  if ( !listHead )
    return insertAfter;
  while ( 1 )
  {
    nodeSalience = listHead[2];
    if ( salience >= nodeSalience )
    {
      if ( salience > nodeSalience )
        return insertAfter;
      nodeRandom = listHead[5];
      if ( randomValue <= nodeRandom )
      {
        if ( randomValue < nodeRandom )
          return insertAfter;
        if ( timeTag <= listHead[3] )
          break;
      }
    }
    insertAfter = listHead;
    listHead = (_DWORD *)listHead[7];
    if ( !listHead )
      return insertAfter;
  }
  return insertAfter;
}

//----- (0047D9E0) --------------------------------------------------------
_DWORD * Rules_BuildLexBasisOrder(int *pattern)
{
  _DWORD *v1; // ecx
  int count; // ebp
  int index; // ebx
  _DWORD *entry; // eax
  int v5; // edx
  int v6; // ecx
  _DWORD *orderArray; // [esp+0h] [ebp-20h]
  int swapped; // [esp+4h] [ebp-1Ch]

  orderArray = Rules_MultifieldCopyWithMarkers(pattern, 0, 0);
  count = (*v1 << 17 >> 23) - 1;
  do
  {
    index = 0;
    swapped = 0;
    if ( count > 0 )
    {
      entry = orderArray;
      do
      {
        v5 = entry[2];
        if ( *(_DWORD *)v5 )
        {
          v6 = entry[3];
          if ( *(_DWORD *)v6 )
          {
            if ( *(_DWORD *)(*(_DWORD *)v5 + 12) < *(_DWORD *)(*(_DWORD *)v6 + 12) )
            {
              entry[3] = v5;
              entry[2] = v6;
              swapped = 1;
            }
          }
        }
        ++index;
        ++entry;
      }
      while ( index < count );
    }
    --count;
  }
  while ( swapped == 1 );
  return orderArray;
}
// 47D9F4: variable 'v1' is possibly undefined

//----- (0047DA60) --------------------------------------------------------
signed int  Rules_CompareActivationBasis(int activation, _DWORD **candidate)
{
  int index; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  int *v6; // esi
  int *v7; // ebx
  int v8; // edi
  int v9; // esi
  int v10; // ebx
  unsigned int v11; // edx
  unsigned int v12; // eax
  _DWORD *v15; // eax
  int v16; // edx
  int count1; // [esp+0h] [ebp-24h]
  int count2; // [esp+4h] [ebp-20h]
  int minCount; // [esp+8h] [ebp-1Ch]

  if ( !*(_DWORD *)(activation + 16) )
  {
    v15 = Rules_BuildLexBasisOrder(*(int **)(activation + 4));
    *(_DWORD *)(v16 + 16) = v15;
  }
  count2 = *candidate[4] << 17 >> 23;
  count1 = **(_DWORD **)(activation + 16) << 17 >> 23;
  if ( count1 <= count2 )
    minCount = **(_DWORD **)(activation + 16) << 17 >> 23;
  else
    minCount = *candidate[4] << 17 >> 23;
  index = 0;
  if ( minCount > 0 )
  {
    v4 = *(_DWORD *)(activation + 16);
    v5 = candidate[4];
    do
    {
      v6 = *(int **)(v4 + 8);
      if ( *v6 && (v7 = (int *)candidate[4][index + 2], (v8 = *v7) != 0) )
      {
        v9 = *v6;
        v10 = *v7;
        if ( *(_DWORD *)(v8 + 12) < *(_DWORD *)(v9 + 12) )
          return 0;
        if ( *(_DWORD *)(v10 + 12) > *(_DWORD *)(v9 + 12) )
          return 1;
      }
      else
      {
        if ( *(_DWORD *)v5[2] )
          return 1;
        if ( **(_DWORD **)(*(_DWORD *)(activation + 16) + 4 * index + 8) )
          return 0;
      }
      v4 += 4;
      ++index;
      ++v5;
    }
    while ( index < minCount );
  }
  if ( count2 < count1 )
    return 0;
  if ( count2 > count1 )
    return 1;
  v11 = *(_DWORD *)(*(_DWORD *)activation + 28) & 0x7FF;
  v12 = (*candidate)[7] & 0x7FF;
  if ( v12 < v11 )
  {
    return 0;
  }
  else
  {
    if ( v12 > v11 )
      return 1;
    return 2;
  }
}
// 47DB58: variable 'v16' is possibly undefined

//----- (0047DBB0) --------------------------------------------------------
int  Rules_SetStrategy(int strategy)
{
  int oldStrategy; // edx

  oldStrategy = g_Rules_ConflictResolutionStrategy;
  g_Rules_ConflictResolutionStrategy = strategy;
  if ( oldStrategy != strategy )
    Rules_ReorderAgenda(0);
  return oldStrategy;
}
// 47DBC0: variable 'v1' is possibly undefined
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DBE0) --------------------------------------------------------
signed int *Rules_GetStrategyCommand()
{
  char *strategyName; // eax
  int v1; // ecx

  Lexer_TokenExpect(0);
  strategyName = Rules_GetStrategyName(g_Rules_ConflictResolutionStrategy);
  return Str_Intern(strategyName, v1);
}
// 47DBFA: variable 'v1' is possibly undefined
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DC10) --------------------------------------------------------
signed int * Rules_SetStrategyCommand(int a1, double frame)
{
  int oldStrategy; // esi
  int newStrategy; // eax
  int v5; // ecx
  int v6; // eax
  char *strategyName; // eax
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  char *v15; // eax
  int v16; // ecx
  _DWORD argValue[10]; // [esp-8h] [ebp-28h] BYREF

  argValue[8] = a1;
  oldStrategy = g_Rules_ConflictResolutionStrategy;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, argValue, 2, frame) )
  {
    v6 = g_Rules_ConflictResolutionStrategy;
    goto LABEL_5;
  }
  newStrategy = strcmp_(*(_DWORD *)(argValue[2] + 16), aDepth);
  if ( !newStrategy )
  {
LABEL_4:
    Rules_SetStrategy(newStrategy);
    v6 = oldStrategy;
LABEL_5:
    strategyName = Rules_GetStrategyName(v6);
    return Str_Intern(strategyName, v8);
  }
  if ( !strcmp_(v5, aBreadth) )
  {
    newStrategy = 1;
    goto LABEL_4;
  }
  if ( !strcmp_(v10, aLex) )
  {
    newStrategy = 2;
    goto LABEL_4;
  }
  if ( !strcmp_(v11, aMea) )
  {
    newStrategy = 3;
    goto LABEL_4;
  }
  if ( !strcmp_(v12, aComplexity) )
  {
    newStrategy = 4;
    goto LABEL_4;
  }
  if ( !strcmp_(v13, aSimplicity) )
  {
    newStrategy = 5;
    goto LABEL_4;
  }
  if ( !strcmp_(v14, aRandom_0) )
  {
    newStrategy = 6;
    goto LABEL_4;
  }
  Parser_ReportError(1, (int)aSymbolWithVa_0);
  v15 = Rules_GetStrategyName(g_Rules_ConflictResolutionStrategy);
  return Str_Intern(v15, v16);
}
// 47DC70: variable 'v8' is possibly undefined
// 47DC8B: variable 'v5' is possibly undefined
// 47DCA2: variable 'v10' is possibly undefined
// 47DCB9: variable 'v11' is possibly undefined
// 47DCD0: variable 'v12' is possibly undefined
// 47DCE7: variable 'v13' is possibly undefined
// 47DD01: variable 'v14' is possibly undefined
// 47DD32: variable 'v16' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DD60) --------------------------------------------------------
char * Rules_GetStrategyName(int strategy)
{
  char *result; // eax

  switch ( strategy )
  {
    case 0:
      result = aDepth;
      break;
    case 1:
      result = aBreadth;
      break;
    case 2:
      result = aLex;
      break;
    case 3:
      result = aMea;
      break;
    case 4:
      result = aComplexity;
      break;
    case 5:
      result = aSimplicity;
      break;
    case 6:
      result = aRandom_0;
      break;
    default:
      result = aUnknown_0;
      break;
  }
  return result;
}

//----- (0047DDA0) --------------------------------------------------------
signed int Rules_RegisterAgendaCommands()
{
  Rules_AddClearFunction((int)aAgenda_0, (int)Rules_ResetActivationSequence, 0);
  Rules_AddWatchItem((int)aActivations, 1, 40, (int)&g_Rules_WatchActivationsFlag, (int)Rules_DefruleWatchAccess, (int)Rules_DefruleWatchPrint);
  Rules_RegisterHostFunction(aRefresh, 118, (int)aRefreshcommand, (int)Rules_RefreshCommand, (int)a11w);
  Rules_RegisterHostFunction(aRefreshAgenda, 118, (int)aRefreshagendac, (int)Rules_RefreshAgendaCommand, (int)a01w);
  Rules_RegisterHostFunction(aGetSalienceEva, 119, (int)aGetsalienceeva, (int)Rules_GetSalienceEvaluationCommand, (int)a00);
  Rules_RegisterHostFunction(aSetSalienceEva, 119, (int)aSetsalienceeva, (int)Rules_SetSalienceEvaluationCommand, (int)a11w);
  return Rules_RegisterHostFunction(aAgenda_0, 118, (int)aAgendacommand, (int)Rules_AgendaCommand, (int)a01w);
}
// 51A1DC: using guessed type int dword_51A1DC;

//----- (0047DE80) --------------------------------------------------------
_DWORD * Rules_AddActivation(int rule, int binds, double a3)
{
  uintptr_t join; // ebx
  uintptr_t partial_match; // edx
  uintptr_t activation; // ecx
  uintptr_t free_head; // ecx
  uintptr_t agenda; // eax
  int salience; // eax
  int sequence; // eax
  int bucket; // eax

  join = (uintptr_t)(unsigned int)rule;
  partial_match = (uintptr_t)(unsigned int)binds;
  if ( (*(_BYTE *)(join + 29) & 0x40) != 0 )
  {
    agenda = (uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
    Rules_PushFocus(*(_DWORD *)agenda);
  }
  free_head = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 128);
  if ( free_head )
  {
    g_ClipsMemFreeListTemp = (int)free_head;
    *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsMemoryTable + 128) = *(_DWORD *)free_head;
    activation = (uintptr_t)(unsigned int)g_ClipsMemFreeListTemp;
  }
  else
  {
    activation = (uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  *(_DWORD *)activation = (int)join;
  *(_DWORD *)(activation + 4) = (int)partial_match;
  sequence = g_Rules_ActivationSequenceCounter++;
  *(_DWORD *)(activation + 12) = sequence;
  salience = Rules_EvaluateSalience((int)join, a3);
  *(_DWORD *)(activation + 16) = 0;
  *(_DWORD *)(activation + 8) = salience;
  *(_DWORD *)(activation + 24) = 0;
  *(_DWORD *)(activation + 28) = 0;
  *(_DWORD *)(activation + 20) = j_rand_();
  ++g_Rules_ActivationCount;
  bucket = ((unsigned int)*(_DWORD *)partial_match << 17) >> 23;
  *(_DWORD *)(partial_match + 4 * bucket + 8) = (int)activation;
  if ( (*(_BYTE *)(join + 29) & 0x10) != 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aActivation_0, (int)activation);
    Rules_PrintActivation((int)g_IO_LogicalNameTable_WTrace[0], (int)activation);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502D24, (int)activation);
  }
  agenda = (uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
  return Rules_InsertActivationSorted((int *)(agenda + 12), (_DWORD *)activation);
}
// 47D520: using guessed type __int64 j_rand_(void);
// 51A1E0: using guessed type int dword_51A1E0;
// 51A1E4: using guessed type int dword_51A1E4;
// 51A618: using guessed type char *off_51A618[4];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047DF90) --------------------------------------------------------
int  Rules_ClearActivationsForRule(int result)
{
  _DWORD *activation; // ecx
  int v2; // edi
  _DWORD *nextActivation; // esi

  activation = *(_DWORD **)(*(_DWORD *)(result + 8) + 12);
  v2 = result;
  if ( activation )
  {
    do
    {
      while ( 1 )
      {
        result = v2;
        nextActivation = (_DWORD *)activation[7];
        if ( v2 )
          break;
LABEL_5:
        activation = nextActivation;
        if ( !nextActivation )
          return result;
      }
      do
      {
        if ( result == *activation )
        {
          result = Rules_RemoveActivation(activation, 1, 1);
          goto LABEL_5;
        }
        result = *(_DWORD *)(result + 48);
      }
      while ( result );
      activation = (_DWORD *)activation[7];
    }
    while ( nextActivation );
  }
  return result;
}

//----- (0047DFE0) --------------------------------------------------------
int  Rules_GetNextActivation(int activation)
{
  int result; // eax

  if ( activation )
    return *(_DWORD *)(activation + 28);
  result = Module_GetItem(0, g_DefruleConstructClass);
  if ( result )
    return *(_DWORD *)(result + 12);
  return result;
}
// 54E64C: using guessed type int dword_54E64C;

//----- (0047E000) --------------------------------------------------------
int  Rules_GetActivationRuleName(int activation)
{
  return *(_DWORD *)(**(_DWORD **)activation + 16);
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
  v2 = *(_DWORD *)(*v1 + 8);
  agendaHead = *(_DWORD **)(v2 + 12);
  if ( v1 == agendaHead )
    *(_DWORD *)(v2 + 12) = agendaHead[7];
  prevActivation = v1[6];
  if ( prevActivation )
    *(_DWORD *)(prevActivation + 28) = v1[7];
  nextActivation = v1[7];
  if ( nextActivation )
    *(_DWORD *)(nextActivation + 24) = v1[6];
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
  int v9; // [esp+14h] [ebp-8h]

  v9 = logicalName;
  sprintf_(buffer, "%-6d ", *(_DWORD *)(activation + 8));
  Output_Write(v3, (int)buffer, v3);
  Output_Write(v4, *(_DWORD *)(**(_DWORD **)activation + 16), v4);
  Output_Write(v5, (int)asc_502D44, v5);
  return Rules_PrintArgumentValueList(v6, *(_DWORD **)(activation + 4));
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
           (int)aActivations,
           (int)aActivation_1,
           (int (__cdecl *)(int))Rules_GetNextActivation,
           0,
           (void (__fastcall *)(int, int))Rules_PrintActivation,
           0);
}

//----- (0047E1D0) --------------------------------------------------------
int  Rules_RemoveActivation(_DWORD *theActivation, int updateAgenda, int updateLinks)
{
  _DWORD *v4; // ecx
  int v5; // edx
  int prevActivation; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  _DWORD *binds; // edx
  int result; // eax
  int nextActivation; // edx

  v4 = theActivation;
  v5 = *(_DWORD *)(*theActivation + 8);
  if ( updateAgenda == 1 )
  {
    prevActivation = theActivation[6];
    if ( prevActivation )
    {
      nextActivation = theActivation[7];
      *(_DWORD *)(prevActivation + 28) = nextActivation;
      if ( nextActivation )
        *(_DWORD *)(nextActivation + 24) = theActivation[6];
    }
    else
    {
      v7 = *(_DWORD *)(*(_DWORD *)(v5 + 12) + 28);
      *(_DWORD *)(v5 + 12) = v7;
      if ( v7 )
        *(_DWORD *)(v7 + 24) = 0;
    }
    if ( (*(_BYTE *)(*v4 + 29) & 0x10) != 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aActivation, (int)v4);
      Rules_PrintActivation(v8, v8);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502D24, v9);
    }
    g_Rules_AgendaChangedFlag = 1;
  }
  if ( updateLinks == 1 )
  {
    binds = (_DWORD *)v4[1];
    if ( binds )
      *(_DWORD *)(v4[1] + 4 * (*binds << 17 >> 23) + 8) = 0;
  }
  --g_Rules_ActivationCount;
  if ( v4[4] )
    Rules_FreePartialMatch(v4[4]);
  g_ClipsMemFreeListTemp = (int)v4;
  *v4 = *(_DWORD *)(g_ClipsMemoryTable + 128);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
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
void Rules_ResetActivationSequence()
{
  g_Rules_ActivationSequenceCounter = 0;
}
// 51A1E4: using guessed type int dword_51A1E4;

//----- (0047E2C0) --------------------------------------------------------
_DWORD *Rules_ClearActivationsForModule()
{
  _DWORD *result; // eax
  _DWORD *nextActivation; // ecx

  result = *(_DWORD **)(Rules_GetDefruleModuleItem(0) + 12);
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
      Enum = *(_DWORD *)(v4 + 12);
      *(_DWORD *)(v4 + 12) = 0;
      if ( Enum )
      {
        agendaListHead = (int *)(v4 + 12);
        do
        {
          *(_DWORD *)(Enum + 24) = 0;
          nextActivation = *(_DWORD *)(Enum + 28);
          *(_DWORD *)(Enum + 28) = 0;
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
int Rules_GetActivationCount()
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

  result = (_BYTE *)Rules_GetConstructNameArg((int)aRuleName, a1, a2);
  if ( result )
  {
    defrule = Rules_FindDefruleByName(result, v3);
    if ( defrule )
      return (_BYTE *)Rules_RefreshRule(defrule, a2);
    else
      return (_BYTE *)Rules_ReportCantFindItem(v6, v5);
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

  for ( i = defrule; i; i = *(_DWORD *)(i + 48) )
  {
    for ( j = *(_DWORD *)(*(_DWORD *)(i + 44) + 8); j; j = *(_DWORD *)(j + 4) )
    {
      if ( (*(_BYTE *)j & 4) != 0 && (*(_BYTE *)j & 0x20) == 0 && !*(_DWORD *)(j + 4 * (*(_DWORD *)j << 17 >> 23) + 8) )
        Rules_AddActivation(i, j, a2);
    }
  }
  return 1;
}
// 47E429: variable 'j' is possibly undefined

//----- (0047E450) --------------------------------------------------------
signed int Rules_SalienceInformationError()
{
  int v0; // ecx
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)aAgenda, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThisErrorOccur, v0);
  if ( !v1 )
    return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_Agenda, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForRule, v1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v3, v3);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_Agenda, v4);
}
// 47E473: variable 'v0' is possibly undefined
// 47E47A: variable 'v1' is possibly undefined
// 47E4A5: variable 'v3' is possibly undefined
// 47E4B4: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047E4C0) --------------------------------------------------------
signed int Rules_SalienceRangeError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx

  Rules_PrintErrorID((int)aAgenda, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSalienceValueO, v0);
  Rules_PrintLongInteger(v1, -10000);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTo, v2);
  Rules_PrintLongInteger(v3, 10000);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_Agenda, v4);
}
// 47E4E0: variable 'v0' is possibly undefined
// 47E4EF: variable 'v1' is possibly undefined
// 47E4FE: variable 'v2' is possibly undefined
// 47E50D: variable 'v3' is possibly undefined
// 47E51C: variable 'v4' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047E530) --------------------------------------------------------
signed int Rules_SalienceNonIntegerError()
{
  int v0; // ecx

  Rules_PrintErrorID((int)aAgenda, 1, 1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSalienceValueM, v0);
}
// 47E54D: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047E560) --------------------------------------------------------
int * Rules_RefreshAgendaCommand(double a1)
{
  int *result; // eax
  int v2; // ecx
  _DWORD v3[3]; // [esp+0h] [ebp-Ch] BYREF

  result = (int *)Lexer_TokenExpect(1);
  if ( result != (int *)-1 )
  {
    if ( result == (int *)1 )
    {
      result = Rules_GetModuleNameArg(1, v2, v3, a1);
      if ( !v3[0] )
        return (int *)Rules_RefreshAgenda(a1);
    }
    else
    {
      Module_GetCurrent();
      return (int *)Rules_RefreshAgenda(a1);
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
    for ( i = (int *)Rules_GetNextActivation(0); i; i = (int *)Rules_GetNextActivation((int)i) )
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
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, v9, 2, a2) )
  {
    v5 = currentModeName;
    return Str_Intern(v5, v4);
  }
  if ( !strcmp_(*(_DWORD *)(v9[2] + 16), aWhenDefined) )
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
      Parser_ReportError(1, (int)aSymbolWithVa_1);
    return Str_Intern(currentModeName, v8);
  }
}
// 47E6B4: variable 'v4' is possibly undefined
// 47E6E2: variable 'v7' is possibly undefined
// 47E70C: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E740) --------------------------------------------------------
signed int *Rules_GetSalienceEvaluationCommand()
{
  char *modeName; // eax
  int v1; // ecx

  Lexer_TokenExpect(0);
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
int Rules_GetSalienceEvaluation()
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
  int v4; // ecx
  _DWORD *v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int tokenType; // [esp+0h] [ebp-20h]
  int valueNode; // [esp+4h] [ebp-1Ch]

  if ( !g_Rules_SalienceEvaluationMode || !*(_DWORD *)(defrule + 32) )
    return *(_DWORD *)(defrule + 20);
  Lexer_ErrorRecover(0);
  if ( Parser_ParseForm(*(__int16 **)(v4 + 32), v5, v4, a2) )
  {
    Rules_SalienceInformationError();
    return *(_DWORD *)(v7 + 20);
  }
  else if ( tokenType == 1 )
  {
    result = *(_DWORD *)(valueNode + 16);
    if ( result > 10000 || result < -10000 )
    {
      Rules_SalienceRangeError();
      Lexer_ErrorRecover(1);
      Rules_SalienceInformationError();
      return *(_DWORD *)(defrule + 20);
    }
    else
    {
      *(_DWORD *)(v6 + 20) = result;
    }
  }
  else
  {
    Rules_SalienceNonIntegerError();
    Rules_SalienceInformationError();
    Lexer_ErrorRecover(1);
    return *(_DWORD *)(v8 + 20);
  }
  return result;
}
// 47E7EC: variable 'v4' is possibly undefined
// 47E7EF: variable 'v5' is possibly undefined
// 47E7FD: variable 'v9' is possibly undefined
// 47E803: variable 'v10' is possibly undefined
// 47E814: variable 'v6' is possibly undefined
// 47E828: variable 'v7' is possibly undefined
// 47E84B: variable 'v8' is possibly undefined
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E880) --------------------------------------------------------
int * Rules_AgendaCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx
  int currentModule; // eax
  _DWORD v5[4]; // [esp+0h] [ebp-10h] BYREF

  v5[2] = a1;
  result = (int *)Lexer_TokenExpect(1);
  if ( result != (int *)-1 )
  {
    if ( result == (int *)1 )
    {
      result = Rules_GetModuleNameArg(1, v3, v5, a2);
      if ( !v5[0] )
        return (int *)Rules_ActivationsCommand((int)g_IO_LogicalName_WDisplay, (int)result);
    }
    else
    {
      currentModule = Module_GetCurrent();
      return (int *)Rules_ActivationsCommand((int)g_IO_LogicalName_WDisplay, currentModule);
    }
  }
  return result;
}
// 47E8C5: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047E8E4) --------------------------------------------------------
int __fastcall IO_PrintfToStdout(int format, int a2, int a3, char firstArg)
{
  int args[3]; // [esp+0h] [ebp-Ch] BYREF

  args[0] = (int)&firstArg;
  return CRT_VfprintfLockedWrite((int)&g_CRT_StdoutStream, format, args);
}

//----- (0047E910) --------------------------------------------------------
int  Rules_RunAgendaLoop(int runLimit, int a2, double a3)
{
  int v3; // ecx
  int *activation; // edi
  int v5; // edx
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
  int v16; // ecx
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
  int v33; // edx
  int nextActivation; // eax
  int v35; // ecx
  int nextRuleName; // eax
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v42; // edx
  int v43; // ecx
  char *messageString; // edx
  int v45; // ecx
  int v46; // ecx
  int v47; // ecx
  double rulesPerSecond; // [esp+0h] [ebp-ECh]
  int v49; // [esp+4h] [ebp-E8h]
  int v50; // [esp+8h] [ebp-E4h]
  int v51; // [esp+8h] [ebp-E4h]
  int v52; // [esp+8h] [ebp-E4h]
  _DWORD fireTraceBuffer[15]; // [esp+Ch] [ebp-E0h] BYREF
  _BYTE statsBuffer[60]; // [esp+48h] [ebp-A4h] BYREF
  int returnValue[6]; // [esp+84h] [ebp-68h] BYREF
  double runtimeSeconds; // [esp+9Ch] [ebp-50h]
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
  activation = (int *)Rules_NextActivationToFire();
  while ( activation )
  {
    if ( !remainingFires || g_ClipsHaltExecution || g_Rules_HaltRulesFlag )
      break;
    Rules_DetachActivation(activation);
    ruleName = Rules_GetActivationRuleName((int)activation);
    binds = (_DWORD *)activation[1];
    g_Rules_CurrentlyExecutingRule = *activation;
    ++fireCount;
    if ( v5 > 0 )
      remainingFires = v5 - 1;
    if ( (*(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) & 0x20) != 0 )
    {
      a3 = sprintf_(fireTraceBuffer, "FIRE %4ld ", fireCount);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)fireTraceBuffer, v12);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], ruleName, v13);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E90, v14);
      Rules_PrintArgumentValueList((int)g_IO_LogicalNameTable_WTrace[0], binds);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E94, v15);
    }
    binds[(*binds << 17 >> 23) + 2] = 0;
    bindIndex = 0;
    *(_BYTE *)binds |= 2u;
    g_Clips_CurrentPartialMatch = (int)binds;
    g_Rules_GlobalRHSBinds = 0;
    bindWalker = binds;
    while ( bindIndex < *binds << 17 >> 23 )
    {
      matchEntity = *(_DWORD *)bindWalker[2];
      if ( matchEntity )
        (*(void (**)(void))(*(_DWORD *)matchEntity + 52))();
      ++bindWalker;
      ++bindIndex;
    }
    g_Rules_CurrentLogicalJoin = *(_DWORD *)(g_Rules_CurrentlyExecutingRule + 40);
    ++g_ClipsCurrentEvaluationDepth;
    Lexer_ErrorRecover(0);
    *(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) |= 0x80u;
    Rules_ExecuteRuleActions(
      **(_DWORD **)(g_Rules_CurrentlyExecutingRule + 8),
      *(__int16 **)(g_Rules_CurrentlyExecutingRule + 36),
      returnValue,
      *(_DWORD *)(g_Rules_CurrentlyExecutingRule + 24),
      a3,
      0);
    *(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) &= ~0x80u;
    Lexer_ErrorRecover(0);
    g_Rules_CurrentLogicalJoin = v16;
    --g_ClipsCurrentEvaluationDepth;
    if ( g_ClipsHaltExecution || g_Rules_HaltRulesFlag && (*(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) & 0x20) != 0 )
    {
      Rules_PrintErrorID((int)aPrccode, 4, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExecutionHalte, v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], ruleName, v18);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_RuleRuntime, v19);
    }
    bindPtr = binds;
    cleanupIndex = 0;
    *(_BYTE *)binds &= ~2u;
    while ( 1 )
    {
      lastBindIndex = (*binds << 17 >> 23) - 1;
      if ( cleanupIndex >= lastBindIndex )
        break;
      cleanupEntity = *(_DWORD *)bindPtr[2];
      if ( cleanupEntity )
        (*(void (**)(void))(*(_DWORD *)cleanupEntity + 48))();
      ++bindPtr;
      ++cleanupIndex;
    }
    if ( (*(_BYTE *)binds & 0x20) == 0 )
    {
      finalEntity = *(_DWORD *)binds[lastBindIndex + 2];
      if ( finalEntity )
        (*(void (__cdecl **)(int))(*(_DWORD *)finalEntity + 48))(v50);
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
    for ( i = g_Rules_PostRuleFireCallbackListHead; i; i = *(_DWORD *)(v33 + 12) )
      (*(void (**)(void))(i + 4))();
    if ( g_ClipsHaltExecutionFlag == 1 )
      Rules_RemoveModuleFocus(**(_DWORD **)(g_Rules_CurrentlyExecutingRule + 8));
    g_ClipsHaltExecutionFlag = 0;
    nextActivation = Rules_NextActivationToFire();
    v3 = nextActivation;
    activation = (int *)nextActivation;
    if ( nextActivation && (*(_BYTE *)(*(_DWORD *)nextActivation + 29) & 8) != 0 )
    {
      g_Rules_HaltRulesFlag = 1;
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aBreakingOnRule, nextActivation);
      nextRuleName = Rules_GetActivationRuleName(v35);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], nextRuleName, (int)g_IO_LogicalNameTable_WDialog[0]);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aDotNewline_RuleRuntime, v37);
    }
  }
  if ( remainingFires == fireCount )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aRuleFiringLimi, v3);
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
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aRulesFired, v39);
    if ( startTime >= runtime_end )
    {
      messageString = asc_502E94;
    }
    else
    {
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aRunTimeIs, v40);
      runtime_elapsed = runtime_end - startTime;
      runtimeSeconds = runtime_elapsed;
      Rules_PrintFloat((int)g_IO_LogicalNameTable_WDialog[0], runtime_elapsed);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)" seconds.\n", 0);
      rulesPerSecond = (double)fireCount / runtime_elapsed;
      Rules_PrintFloat((int)g_IO_LogicalNameTable_WDialog[0], rulesPerSecond);
      messageString = " rules per second.\n";
    }
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)messageString, v40);
    sample_count = (double)(fireCount + 1);
    meanValue = (int)((double)factSum / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(statsBuffer, "%ld mean number of facts (%ld maximum).\n", meanValue, maxFacts);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)statsBuffer, v45);
    meanValue = (int)((double)instanceSum / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(statsBuffer, "%ld mean number of instances (%ld maximum).\n", meanValue, maxInstances);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)statsBuffer, v46);
    meanValue = (int)((double)activationSum / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(statsBuffer, "%ld mean number of activations (%ld maximum).\n", meanValue, maxActivations);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)statsBuffer, v47);
  }
  if ( g_Rules_FocusStackTop && Module_GetCurrent() != *(_DWORD *)g_Rules_FocusStackTop )
    Module_SetCurrent(*(_DWORD *)g_Rules_FocusStackTop);
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
int Rules_NextActivationToFire()
{
  int activation; // edx
  int *mainModule; // eax

  if ( !g_Rules_FocusStackTop )
  {
    mainModule = Module_FindByName(aMain_0);
    Rules_PushFocus((int)mainModule);
  }
  activation = *(_DWORD *)(*(_DWORD *)(g_Rules_FocusStackTop + 4) + 12);
  while ( !activation )
  {
    if ( !g_Rules_FocusStackTop )
      break;
    Rules_PopFocus();
    if ( g_Rules_FocusStackTop )
      activation = *(_DWORD *)(*(_DWORD *)(g_Rules_FocusStackTop + 4) + 12);
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
  focusEntry = (_DWORD *)g_Rules_FocusStackTop;
  prevEntry = 0;
  do
  {
    if ( found )
      break;
    if ( module == *focusEntry )
    {
      nextEntry = focusEntry[2];
      g_ClipsMemFreeListTemp = (int)focusEntry;
      *focusEntry = *(_DWORD *)(g_ClipsMemoryTable + 48);
      found = 1;
      *(_DWORD *)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
      focusEntry = (_DWORD *)nextEntry;
      if ( prevEntry )
      {
        *(_DWORD *)(prevEntry + 8) = nextEntry;
      }
      else
      {
        removedTop = 1;
        g_Rules_FocusStackTop = nextEntry;
      }
    }
    else
    {
      prevEntry = (int)focusEntry;
      focusEntry = (_DWORD *)focusEntry[2];
    }
  }
  while ( focusEntry );
  if ( !found )
    return *(_DWORD *)g_Rules_FocusStackTop;
  if ( g_Rules_WatchFocusFlag )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aFocus, prevEntry);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)module + 16), v7);
    if ( g_Rules_FocusStackTop && removedTop )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aTo_0, v8);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(**(_DWORD **)g_Rules_FocusStackTop + 16), v9);
    }
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E94, v8);
  }
  if ( g_Rules_FocusStackTop )
  {
    if ( removedTop )
      Module_SetCurrent(*(_DWORD *)g_Rules_FocusStackTop);
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
int Rules_PopFocus()
{
  if ( g_Rules_FocusStackTop )
    return Rules_RemoveModuleFocus(*(_DWORD *)g_Rules_FocusStackTop);
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
  if ( !g_Rules_FocusStackTop || module != *(_DWORD *)g_Rules_FocusStackTop )
  {
    if ( g_Rules_WatchFocusFlag )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aFocus_0, 0);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)module + 16), module);
      if ( g_Rules_FocusStackTop )
      {
        Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aFrom, 0);
        Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)*(_DWORD *)g_Rules_FocusStackTop + 16), g_Rules_FocusStackTop);
      }
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E94, 0);
    }
    focus_entry = *(_DWORD *)(g_ClipsMemoryTable + 48);
    if ( focus_entry )
    {
      g_ClipsMemFreeListTemp = focus_entry;
      *(_DWORD *)(g_ClipsMemoryTable + 48) = *(_DWORD *)focus_entry;
      focus_entry = g_ClipsMemFreeListTemp;
    }
    else
    {
      focus_entry = Mem_HeapAllocWithRetry((_DWORD *)0xC);
    }
    *(_DWORD *)focus_entry = module;
    *(_DWORD *)(focus_entry + 4) = Rules_GetDefruleModuleItem(module);
    *(_DWORD *)(focus_entry + 8) = g_Rules_FocusStackTop;
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
int Rules_ClearFocusStackCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Rules_ClearFocusStack();
  return result;
}

//----- (0047F2C0) --------------------------------------------------------
int Rules_ClearFocusStack()
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
int Rules_RegisterAgendaWatchFlags()
{
  Rules_AddWatchItem((int)aStatistics, 0, 20, (int)&g_Rules_WatchStatisticsFlag, 0, 0);
  return Rules_AddWatchItem((int)aFocus_1, 0, 0, (int)&g_Rules_WatchFocusFlag, 0, 0);
}
// 51A208: using guessed type int dword_51A208;
// 51A20C: using guessed type int dword_51A20C;

//----- (0047F380) --------------------------------------------------------
int  Rules_RunCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // [esp-8h] [ebp-24h] BYREF
  int argValue; // [esp+0h] [ebp-1Ch]
  int savedContext; // [esp+14h] [ebp-8h]

  savedContext = a1;
  result = Lexer_TokenExpect(1);
  if ( result != v3 )
  {
    if ( result == 1 )
    {
      result = Lexer_ParseValueList(1, &v4, 1, a2);
      if ( result )
        return Rules_RunAgendaLoop(*(_DWORD *)(argValue + 16), *(_DWORD *)(argValue + 16), a2);
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
int Rules_HaltCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  g_Rules_HaltRulesFlag = 1;
  return result;
}
// 51A1F4: using guessed type int dword_51A1F4;

//----- (0047F410) --------------------------------------------------------
int  Rules_SetBreakFlag(int result)
{
  for ( ; result; result = *(_DWORD *)(result + 48) )
    *(_BYTE *)(result + 29) |= 8u;
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
      flags = *(_BYTE *)(disjunct + 29);
      if ( (flags & 8) != 0 )
        break;
      disjunct = *(_DWORD *)(disjunct + 48);
      if ( !disjunct )
        return cleared;
    }
    cleared = 1;
    *(_BYTE *)(disjunct + 29) = flags & 0xF7;
    disjunct = *(_DWORD *)(disjunct + 48);
  }
  while ( disjunct );
  return 1;
}

//----- (0047F480) --------------------------------------------------------
void Rules_RemoveAllBreakFlags()
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
  return *(_DWORD *)(defrule + 28) << 20 >> 31;
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
  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, v7, 2, a2);
    if ( result )
    {
      defrule = Rules_FindDefruleByName(*(_BYTE **)(v7[2] + 16), v3);
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
  int v9; // [esp-8h] [ebp-24h] BYREF
  int v10; // [esp+0h] [ebp-1Ch]
  int v11; // [esp+10h] [ebp-Ch]
  int v12; // [esp+14h] [ebp-8h]

  v12 = a1;
  v11 = a3;
  tokenType = Lexer_TokenExpect(1);
  if ( tokenType != -1 )
  {
    if ( tokenType )
    {
      if ( Lexer_ParseValueList(1, &v9, 2, a2) )
      {
        defrule = Rules_FindDefruleByName(*(_BYTE **)(v10 + 16), *(_DWORD *)(v10 + 16));
        if ( defrule )
        {
          if ( !Rules_ClearBreakFlag(defrule) )
          {
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aRule, v6);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], v7, v7);
            Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotHaveABr, v8);
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
  result = (int *)Lexer_TokenExpect(1);
  if ( result != (int *)-1 )
  {
    if ( result == (int *)1 )
    {
      result = Rules_GetModuleNameArg(1, v3, v5, a2);
      if ( !v5[0] )
        return (int *)Rules_ListRuleBreakpoints((int)g_IO_LogicalName_WDisplay, (int)result);
    }
    else
    {
      currentModule = Module_GetCurrent();
      return (int *)Rules_ListRuleBreakpoints((int)g_IO_LogicalName_WDisplay, currentModule);
    }
  }
  return result;
}
// 47F645: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047F670) --------------------------------------------------------
int Rules_ListFocusStackCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Rules_PrintFocusStack((signed int)g_IO_LogicalName_WDisplay);
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
  focusEntry = (int *)g_Rules_FocusStackTop;
  if ( g_Rules_FocusStackTop )
  {
    do
    {
      Name = Module_GetName(*focusEntry);
      Output_Write(logicalName_copy, Name, v4);
      result = Output_Write(logicalName_copy, (int)asc_502E94, v5);
      focusEntry = *(int **)(v6 + 8);
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
int Rules_GetFocusStackFunction()
{
  int result; // eax
  _DWORD *returnValue; // ecx

  result = Lexer_TokenExpect(0);
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
  int v10; // ecx

  focusEntry = g_Rules_FocusStackTop;
  count = 0;
  if ( g_Rules_FocusStackTop )
  {
    do
    {
      focusEntry = *(_DWORD *)(focusEntry + 8);
      ++count;
    }
    while ( focusEntry );
    returnValue[1] = 4;
    returnValue[3] = 0;
    returnValue[4] = count - 1;
    multifield = Rules_CreateEphemeralMultifield(count);
    *(_DWORD *)(v5 + 8) = multifield;
    multifield_ptr = multifield;
    focusEntry_walk = g_Rules_FocusStackTop;
    result = 1;
    if ( g_Rules_FocusStackTop )
    {
      element = multifield_ptr;
      do
      {
        *((_WORD *)element + 7) = 2;
        element[4] = **(_DWORD **)focusEntry_walk;
        element = (_DWORD *)((char *)element + 6);
        focusEntry_walk = *(_DWORD *)(focusEntry_walk + 8);
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
    result = (signed int)Rules_CreateEphemeralMultifield(0);
    *(_DWORD *)(v10 + 8) = result;
  }
  return result;
}
// 47F759: variable 'v5' is possibly undefined
// 47F7AA: variable 'v10' is possibly undefined
// 51A200: using guessed type int dword_51A200;

//----- (0047F7C0) --------------------------------------------------------
int Rules_PopFocusFunction()
{
  int focusModule; // eax

  Lexer_TokenExpect(0);
  focusModule = Rules_PopFocus();
  if ( focusModule )
    return *(_DWORD *)focusModule;
  else
    return g_ClipsFalseSymbol;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (0047F7F0) --------------------------------------------------------
int Rules_GetFocusFunction()
{
  int focusModule; // eax

  Lexer_TokenExpect(0);
  focusModule = Rules_GetCurrentFocus();
  if ( focusModule )
    return *(_DWORD *)focusModule;
  else
    return g_ClipsFalseSymbol;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (0047F820) --------------------------------------------------------
int Rules_GetCurrentFocus()
{
  if ( g_Rules_FocusStackTop )
    return *(_DWORD *)g_Rules_FocusStackTop;
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
  v2 = Lexer_TokenExpect(1);
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
    module = Module_FindByName(*(_BYTE **)(v8[2] + 16));
    if ( !module )
    {
      Rules_ReportCantFindItem(v7, v6);
      return 0;
    }
    --argCount;
    Rules_PushFocus((int)module);
    if ( argCount <= 0 )
      return 1;
  }
  return result;
}
// 47F8B4: variable 'v7' is possibly undefined
// 47F8B4: variable 'v6' is possibly undefined

//----- (0047F8F0) --------------------------------------------------------
signed int Rules_RegisterInstanceFunctions()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_EnsureObjectPatternVTable();
  Instance_InitHashTable();
  Rules_RegisterEvaluationHandler((int)(uintptr_t)g_Rules_ObjectPatternVTable, 7);
  Rules_RegisterHostFunction(aInitializeInst, 117, v0, (int)Instance_InitializeInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveInitiali, 117, (int)aInitializeinst, (int)Instance_ActiveInitializeInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveInitiali);
  Rules_RegisterHostFunction(aMakeInstance, 117, v1, (int)Instance_MakeInstanceFunction, 0);
  Rules_RegisterHostFunction(aActiveMakeInst, 117, (int)aMakeinstanceco, (int)Instance_ActiveMakeInstanceFunction, 0);
  Rules_AddFunctionParser(aActiveMakeInst);
  Rules_AddFunctionParser(aInitializeInst);
  Rules_AddFunctionParser(aMakeInstance);
  Rules_RegisterHostFunction(aInitSlots, 117, v2, (int)Instance_InitSlotsCommand, (int)a00_3);
  Rules_RegisterHostFunction(aDeleteInstance, 98, (int)aDeleteinstance, (int)Rules_DeleteInstanceCommand, (int)a00_3);
  Rules_RegisterHostFunction(aUnmakeInstance, 98, (int)aUnmakeinstance, (int)Rules_UnmakeInstanceCommand, (int)a1E);
  Rules_RegisterHostFunction(aInstances, 118, (int)aInstancescomma, (int)Rules_InstancesCommand, (int)a3w);
  Rules_RegisterHostFunction(aPpinstance, 118, (int)aPpinstancecomm, (int)Rules_PPInstanceCommand, (int)a00_3);
  Rules_RegisterHostFunction(aSymbolToInstan, 117, (int)aSymboltoinstan, (int)Rules_SymbolToInstanceName, (int)a11w_4);
  Rules_RegisterHostFunction(aInstanceNameTo, 119, (int)aInstancenameto, (int)Rules_InstanceNameToSymbol, (int)a11p);
  Rules_RegisterHostFunction(aInstanceAddres, 117, (int)aInstanceaddres, (int)Rules_InstanceAddressCommand, (int)a12eep);
  Rules_RegisterHostFunction(aInstanceAddr_0, 98, (int)aInstanceaddr_0, (int)Rules_InstanceAddressPCommand, (int)a11_2);
  Rules_RegisterHostFunction(aInstanceNamep, 98, (int)aInstancenamepc, (int)Rules_InstanceNamePCommand, (int)a11_2);
  Rules_RegisterHostFunction(aInstanceName, 117, (int)aInstancenameco, (int)Rules_InstanceNameCommand, (int)a11e);
  Rules_RegisterHostFunction(aInstancep, 98, (int)aInstancepcomma, (int)Rules_InstancePCommand, (int)a11_2);
  Rules_RegisterHostFunction(aInstanceExistp, 98, (int)aInstanceexistp, (int)Rules_InstanceExistPCommand, (int)a11e);
  Rules_RegisterHostFunction(aClass, 117, (int)aClasscommand_0, (int)Rules_ClassCommand, (int)a11_2);
  Instance_RegisterModifyAndDuplicateFunctions();
  Rules_RegisterInstanceIOCommands();
  Rules_RegisterMultifieldSlotCommands();
  Rules_AddPeriodicFunction((int)aInstances, (int)Instance_PurgeDeletedInstances, 0);
  return Rules_AddResetFunction((int)aInstances, (int)Instance_PrintClassInstanceSummary, 60);
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
    allDeleted = (*(_BYTE *)(instance + 24) & 2) != 0;
  }
  else
  {
    i = g_Clips_InstanceListHead;
    while ( i )
    {
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, i, 0, 0, a2);
      if ( (*(_BYTE *)(i + 24) & 2) == 0 )
        allDeleted = 0;
      for ( i = *(_DWORD *)(i + 68); i; i = *(_DWORD *)(i + 68) )
      {
        if ( (*(_DWORD *)(i + 24) & 2) == 0 )
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
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  _DWORD v10[2]; // [esp+0h] [ebp-34h] BYREF
  int v11; // [esp+8h] [ebp-2Ch]
  int argCount; // [esp+18h] [ebp-1Ch]

  Module_GetCurrent();
  includeInherited = 0;
  className = 0;
  argCount = Rules_RtnArgCount();
  if ( argCount <= 0 )
    goto LABEL_16;
  if ( !Lexer_ParseValueList(1, v10, 2, context) )
    return;
  if ( !Module_FindByName(*(_BYTE **)(v11 + 16)) && strcmp_(v3, asc_5033CC) )
  {
    Lexer_ErrorRecover(1);
    Parser_ReportError(v5, (int)aDefmoduleName);
    return;
  }
  if ( argCount <= 1 )
    goto LABEL_16;
  if ( !Lexer_ParseValueList(2, v10, 2, context) )
    return;
  className = *(_BYTE **)(v11 + 16);
  if ( !Class_LookupByModule(v4, className) )
  {
    if ( strcmp_(v6, asc_5033CC) )
    {
      Class_ReportLookupError(v7, (int)className);
      return;
    }
    className = 0;
  }
  if ( argCount <= 2 )
  {
LABEL_16:
    Rules_PrintInstancesByModule((int)g_IO_LogicalName_WDisplay, includeInherited, (int)className);
    return;
  }
  if ( Lexer_ParseValueList(3, v10, 2, context) )
  {
    if ( strcmp_(v8, aInherit) )
    {
      Lexer_ErrorRecover(1);
      Parser_ReportError(v9, (int)aKeywordInherit);
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

  result = MessageHandler_CheckCurrentMessage((int)this, 1);
  if ( result )
  {
    result = MessageHandler_GetNthArgument(0);
    instance = *(_DWORD *)(result + 8);
    if ( (*(_BYTE *)(instance + 24) & 2) == 0 )
    {
      Rules_PrintInstanceSlots((int)g_IO_LogicalName_WDisplay, instance, (int)asc_5033FC);
      return Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5033FC, v3);
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
        Output_Write(logicalName, (int)asc_503400, a2);
        Module_SetCurrent(i);
        instanceCount += Rules_ListInstancesForClassOrModule(v10, logicalName, className, 1);
      }
    }
    Module_EndEnum();
    Class_ReleaseTraversalID();
    if ( !g_ClipsHaltExecution )
      Rules_PrintTally(logicalName, instanceCount, (int)aInstances, (int)aInstance_1);
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
  result = (_DWORD *)IO_OpenStringSource((int)aMkins, factString, 0);
  if ( result )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-assert-after-router-add\n");
    Parser_NextToken((int)aMkins, token_buffer_ptr);
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
        Rules_RegisterHostFunction(aMakeInstance, 117, (int)aMakeinstanceco, (int)Instance_MakeInstanceFunction, 0);
      }
      Symbol = Rules_MakeSymbol(aMakeInstance);
      if ( trace_load_save )
        fprintf(stderr, "[menu-probe] rules-assert-after-make-symbol symbol=%p\n", Symbol);
      astNode = AST_NewNode(10, (int)Symbol);
      if ( trace_load_save )
        fprintf(stderr, "[menu-probe] rules-assert-after-ast-new-node node=%d\n", astNode);
      if ( Rules_ParseMakeInstanceNode(astNode, (int)aMkins) )
      {
        if ( trace_load_save )
          fprintf(stderr, "[menu-probe] rules-assert-after-instance-head\n");
        Parser_NextToken((int)aMkins, token_buffer_ptr);
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
          Parser_ParseForm((__int16 *)astNode, parse_buffer, (int)aMkins, a3);
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
    IO_CloseStringRouter((int)aMkins);
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
      result = (_DWORD *)(g_ClipsFalseSymbol ^ parse_buffer[2]);
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
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 || (slot = Rules_FindInstanceSlot(instance, slotName)) == 0 )
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
      returnValue[4] = *(_DWORD *)(slot[2] + 6) - 1;
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
      DD_IsFlipping((int)&g_RenderState),
      DD_IsLost((int)&g_RenderState));
    fflush(stderr);
  }
  if ( (*(_BYTE *)(instance + 24) & 2) == 0 && value && (slot = Rules_FindInstanceSlot(instance, slotName)) != 0 )
  {
    result = Instance_PutSlotValue((_DWORD *)instance, slot, value, a5);
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
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 )
    return 0;
  else
    return *(_DWORD *)(*(_DWORD *)(instance + 28) + 16);
}

//----- (004801F0) --------------------------------------------------------
int Rules_GetActiveInstanceCount()
{
  return g_Rules_ActiveInstanceCount;
}
// 51AD10: using guessed type int dword_51AD10;

//----- (00480200) --------------------------------------------------------
int  Rules_GetNextInstance(int instance)
{
  if ( !instance )
    return g_Clips_InstanceListHead;
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 )
    return 0;
  return *(_DWORD *)(instance + 68);
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
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 )
    return 0;
  candidateInstance = *(_DWORD *)(instance + 68);
  if ( !candidateInstance )
    return 0;
LABEL_7:
  while ( !Class_IsInScope(*(_DWORD *)(candidateInstance + 44), 0) )
  {
    candidateInstance = *(_DWORD *)(v3 + 68);
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
    return *(_DWORD *)(classPtr + 80);
  if ( (*(_BYTE *)(instance + 24) & 2) != 0 )
    return 0;
  return *(_DWORD *)(instance + 52);
}

//----- (004802F0) --------------------------------------------------------
int  Rules_ClassCommand(int a1, int a2, double a3)
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
  int v12; // [esp-4h] [ebp-24h] BYREF
  int valueType; // [esp+0h] [ebp-20h]
  int valueField; // [esp+4h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-4h]

  v15 = a2;
  argName = *(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16);
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = g_ClipsFalseSymbol;
  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &v12, a1, a3);
  if ( valueType == 7 )
  {
    instance = (_DWORD *)valueField;
    if ( (*(_BYTE *)(valueField + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      return Lexer_ErrorRecover(1);
    }
LABEL_5:
    result = Rules_GetConstructNameSymbol(instance[11]);
    *(_DWORD *)(v6 + 8) = result;
    return result;
  }
  if ( valueType == 8 )
  {
    instance = Instance_FindByName(valueField);
    if ( !instance )
      return Instance_ReportNoSuchInstanceError(v8, argName);
    goto LABEL_5;
  }
  switch ( valueType )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      result = Rules_GetConstructNameSymbol(g_ClipsPrimitiveTypeClassMap[valueType]);
      *(_DWORD *)(v7 + 8) = result;
      break;
    default:
      Rules_PrintErrorID((int)aInscom, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUndefinedTypeI, v9);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], argName, v10);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a__32, v11);
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
    return Instance_DeleteInstance(*(_DWORD *)(argument + 8), a2);
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
  int v8; // [esp-4h] [ebp-2Ch] BYREF
  int resultType; // [esp+0h] [ebp-28h]
  int resultValue; // [esp+4h] [ebp-24h]
  int v11; // [esp+20h] [ebp-8h]

  v11 = a1;
  argumentIndex = 1;
  argExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  returnCode = 1;
  if ( argExpr )
  {
    while ( 1 )
    {
      Parser_ParseForm((__int16 *)argExpr, &v8, a1, a2);
      if ( resultType == 8 || resultType == 2 )
      {
        instance = Instance_FindByName(resultValue);
        if ( !instance && strcmp_(0, asc_5033CC) )
        {
          Instance_ReportNoSuchInstanceError((int)instance, (int)aUnmakeInstance);
          return 0;
        }
      }
      else
      {
        if ( resultType != 7 )
        {
          Parser_ReportError(argumentIndex, (int)aInstanceAddr_4);
          Lexer_ErrorRecover(1);
          return 0;
        }
        instance = (_DWORD *)resultValue;
        if ( (*(_BYTE *)(resultValue + 24) & 2) != 0 )
        {
          Instance_ReportInvalidInstanceAddressError();
          Lexer_ErrorRecover(1);
          return 0;
        }
      }
      if ( !Rules_UnmakeInstance((int)instance, a2) )
        returnCode = 0;
      if ( a1 )
      {
        argExpr = *(_DWORD *)(argExpr + 10);
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
  int resultValue; // [esp+8h] [ebp-28h]

  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  if ( Rules_RtnArgCount() <= 1 )
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v9, 112, a2);
    if ( result )
    {
      if ( v9[1] == 7 )
      {
        if ( (*(_BYTE *)(resultValue + 24) & 2) != 0 )
        {
          Instance_ReportInvalidInstanceAddressError();
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        else
        {
          *(_DWORD *)(returnValue + 4) = 7;
          result = (_DWORD *)resultValue;
          *(_DWORD *)(returnValue + 8) = resultValue;
        }
      }
      else
      {
        result = Instance_FindByName(resultValue);
        if ( !result )
          return (_DWORD *)Instance_ReportNoSuchInstanceError(v8, (int)aInstanceAddres);
        *(_DWORD *)(returnValue + 4) = 7;
        *(_DWORD *)(returnValue + 8) = result;
      }
    }
  }
  else
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v9, 2, a2);
    if ( result )
    {
      theModule = Module_FindByName(*(_BYTE **)(resultValue + 16));
      if ( !theModule && strcmp_(v4, asc_5033CC) )
      {
        Parser_ReportError(1, (int)aModuleName);
        return (_DWORD *)Lexer_ErrorRecover(1);
      }
      if ( theModule )
      {
        searchImports = 0;
      }
      else
      {
        searchImports = 1;
        theModule = (int *)Module_GetCurrent();
      }
      result = (_DWORD *)Lexer_ParseValueList(2, v9, 8, a2);
      if ( result )
      {
        v7 = Module_GetCurrent();
        result = Instance_LookupInHashBucket(resultValue, (int)theModule, (_DWORD *)searchImports, v7);
        if ( result )
        {
          *(_DWORD *)(returnValue + 4) = 7;
          *(_DWORD *)(returnValue + 8) = result;
          return result;
        }
        return (_DWORD *)Instance_ReportNoSuchInstanceError(v8, (int)aInstanceAddres);
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
  int resultValue; // [esp+4h] [ebp-20h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a2;
  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = Lexer_ParseValueList(1, v7, 112, a3);
  if ( result )
  {
    if ( v7[1] == 7 )
    {
      instance = (_DWORD *)resultValue;
      if ( (*(_BYTE *)(resultValue + 24) & 2) != 0 )
      {
        Instance_ReportInvalidInstanceAddressError();
        return Lexer_ErrorRecover(1);
      }
    }
    else
    {
      instance = Instance_FindByName(resultValue);
      if ( !instance )
        return Instance_ReportNoSuchInstanceError(v6, (int)aInstanceName);
    }
    *(_DWORD *)(returnValue + 4) = 8;
    result = instance[7];
    *(_DWORD *)(returnValue + 8) = result;
  }
  return result;
}
// 4807D9: variable 'v6' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004807F0) --------------------------------------------------------
BOOL  Rules_InstanceAddressPCommand(int a1, double a2)
{
  _DWORD theResult[7]; // [esp-4h] [ebp-1Ch] BYREF

  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), theResult, a1, a2);
  return theResult[1] == 7;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480820) --------------------------------------------------------
BOOL  Rules_InstanceNamePCommand(int a1, double a2)
{
  _DWORD theResult[7]; // [esp-4h] [ebp-1Ch] BYREF

  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), theResult, a1, a2);
  return theResult[1] == 8;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480850) --------------------------------------------------------
BOOL  Rules_InstancePCommand(int a1, double a2)
{
  int theResult; // [esp-4h] [ebp-1Ch] BYREF
  int resultType; // [esp+0h] [ebp-18h]

  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &theResult, a1, a2);
  return resultType == 8 || resultType == 7;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480890) --------------------------------------------------------
int  Rules_InstanceExistPCommand(int a1, double a2)
{
  int result; // eax
  int theResult; // [esp-4h] [ebp-1Ch] BYREF
  int resultType; // [esp+0h] [ebp-18h]
  int resultValue; // [esp+4h] [ebp-14h]

  Parser_ParseForm(*(__int16 **)(g_ClipsCurrentExpression + 6), &theResult, a1, a2);
  if ( resultType == 7 )
  {
    LOBYTE(result) = (*(_BYTE *)(resultValue + 24) & 2) == 0;
    return (unsigned __int8)result;
  }
  if ( resultType == 8 || resultType == 2 )
  {
    LOBYTE(result) = Instance_FindByName(resultValue) != 0;
    return (unsigned __int8)result;
  }
  Parser_ReportError(1, (int)aInstanceNameIn);
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
      return Rules_ListInstancesOfClassRecursive(a1, logicalName, v13, (int)theClass, showModulePrefix);
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
  if ( ((unsigned __int8)markMask & *(_BYTE *)(markByte + 108)) != 0 )
    return 0;
  *(_BYTE *)(markByte + 108) |= markMask;
  instance = *(_DWORD *)(theClass + 80);
  if ( instance )
  {
    while ( !g_ClipsHaltExecution )
    {
      if ( showModulePrefix )
        Output_Write(logicalName, (int)asc_5034F8, instance);
      Instance_PrintNameOfClass(logicalName, instance, 1);
      instance = *(_DWORD *)(v10 + 52);
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
      for ( i = 0; *(unsigned __int16 *)(theClass + 40) > i && !g_ClipsHaltExecution; ++i )
      {
        count += Rules_ListInstancesOfClassRecursive(traversalID, logicalName, inheritFlag, *(_DWORD *)(*(_DWORD *)(theClass + 42) + subclassOffset), showModulePrefix);
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
  while ( slotIndex < *(_DWORD *)(*(_DWORD *)(instance + 44) + 72) )
  {
    Output_Write(logicalName, separatorString, instance);
    Output_Write(logicalName, (int)asc_5034FC, *(_DWORD *)(*(_DWORD *)(v7 + 72) + slotOffset));
    Output_Write(logicalName, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v8 + 8) + 12) + 16), v8);
    if ( (*(_DWORD *)(v9 + 4) & 0xFC) == 0x10 )
    {
      if ( *(_DWORD *)(*(_DWORD *)(v9 + 8) + 6) )
      {
        Output_Write(logicalName, (int)asc_503458, v9);
        Lexer_OutputFieldRange(logicalName, *(_DWORD *)(v11 + 8), *(_DWORD *)(*(_DWORD *)(v11 + 8) + 6) - 1, 0, 0);
      }
    }
    else
    {
      Output_Write(logicalName, (int)asc_503458, v9);
      Rules_PrintAtomValue(logicalName, *(_DWORD *)(v10 + 4) << 24 >> 26, *(int **)(v10 + 8));
    }
    result = Output_Write(logicalName, (int)asc_503500, v9);
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
    return (int *)Instance_GetSlotValueBySymbol(instance, (int)(uintptr_t)result);
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
  free_node = *(_DWORD **)(g_ClipsMemoryTable + 124);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 124);
    *(_DWORD *)(g_ClipsMemoryTable + 124) = *free_node;
    host_function_ptr = g_ClipsMemFreeListTemp;
  }
  else
  {
    host_function_ptr = Mem_HeapAllocWithRetry((_DWORD *)0x1F);
  }
  symbol = Str_Intern(functionName, host_function_ptr);
  *(_DWORD *)(host_function_ptr + 0) = symbol;
  *(_BYTE *)(host_function_ptr + 8) = returnType;
  *(_DWORD *)(host_function_ptr + 9) = actualName;
  *(_DWORD *)(host_function_ptr + 27) = g_Rules_HostFunctionListHead;
  *(_DWORD *)(host_function_ptr + 4) = functionPointer;
  if ( restrictions
    && ((argument_spec_len = strlen((const char *)restrictions), argument_spec_len < 2)
     || (IsTable[(unsigned __int8)(*(_BYTE *)restrictions + 1)] & 0x20) == 0 && *(_BYTE *)restrictions != 42
     || (IsTable[(unsigned __int8)(*(_BYTE *)(restrictions + 1) + 1)] & 0x20) == 0 && *(_BYTE *)(restrictions + 1) != 42) )
  {
    restrictions = 0;
  }
  *(_DWORD *)(host_function_ptr + 13) = 0;
  *(_WORD *)(host_function_ptr + 21) = 1;
  *(_WORD *)(host_function_ptr + 23) = 1;
  symbol_ptr = *(_DWORD *)(host_function_ptr + 0);
  *(_DWORD *)(host_function_ptr + 17) = restrictions;
  ++*(_DWORD *)(symbol_ptr + 4);
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
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionParser, v3);
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
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOnlyExistingFu, 0);
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
  if ( !*(_DWORD *)(theFunction + 17) )
    return 117;
  v4 = strlen(*(const char **)(theFunction + 17)) + 1;
  if ( (int)(v4 - 1) < 3 )
    return 117;
  result = *(unsigned __int8 *)(*(_DWORD *)(theFunction + 17) + 2);
  if ( result == 42 )
    result = 117;
  if ( (int)(v4 - 1) >= position + 3 )
    return *(unsigned __int8 *)(position + *(_DWORD *)(theFunction + 17) + 2);
  return result;
}

//----- (00480F70) --------------------------------------------------------
int Rules_GetFunctionDefinitionListHead()
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
  interned_name = (int)Rules_FindSymbolEntry((int)functionName);
  bucket_entry = *(_DWORD *)(g_ClipsFunctionNameHashTable + 4 * hash_bucket);
  while ( bucket_entry )
  {
    symbol = *(_DWORD *)bucket_entry;
    if ( interned_name == *(_DWORD *)symbol )
      return (int **)symbol;
    bucket_entry = *(_DWORD *)(bucket_entry + 4);
  }
  return 0;
}
// 54DD40: using guessed type int dword_54DD40;

//----- (00481050) --------------------------------------------------------
int Rules_InitFunctionNameHashTable()
{
  int result; // eax

  g_ClipsFunctionNameHashTable = (int)Mem_SmallBlockAlloc(0xCCu);
  for ( result = 0; result != 204; result += 4 )
    *(_DWORD *)(g_ClipsFunctionNameHashTable + result) = 0;
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
  free_node = *(_DWORD **)(g_ClipsMemoryTable + 32);
  if ( free_node )
  {
    g_ClipsMemFreeListTemp = (int)free_node;
    *(_DWORD *)(g_ClipsMemoryTable + 32) = *free_node;
    host_function_ptr = g_ClipsMemFreeListTemp;
  }
  else
  {
    host_function_ptr = Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *(_DWORD *)(host_function_ptr + 0) = functionDef;
  symbol_record = *(_DWORD *)(uintptr_t)(unsigned int)functionDef;
  symbol_name = *(_DWORD *)((uintptr_t)(unsigned int)symbol_record + 16);
  bucket_head_ptr = (int *)(g_ClipsFunctionNameHashTable
                          + 4 * Rules_HashSymbolName((_BYTE *)(uintptr_t)(unsigned int)symbol_name, 0x33u));
  existing_head = *bucket_head_ptr;
  *bucket_head_ptr = host_function_ptr;
  *(_DWORD *)(host_function_ptr + 4) = existing_head;
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
  int v8; // [esp-4h] [ebp-20h] BYREF
  int resultType; // [esp+0h] [ebp-1Ch]
  int resultValue; // [esp+4h] [ebp-18h]

  argExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    if ( i >= argumentPosition )
      break;
    argExpr = *(_DWORD *)(argExpr + 10);
  }
  if ( argExpr )
  {
    Parser_ParseForm((__int16 *)argExpr, &v8, a2, a3);
    if ( resultType == 2 || resultType == 8 || resultType == 3 )
    {
      return *(_DWORD *)(resultValue + 16);
    }
    else
    {
      Rules_ExpectedTypeError((int)aRtnlexeme, *(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 51A960: using guessed type int dword_51A960;

//----- (004811C0) --------------------------------------------------------
double  Rules_RtnDouble(int argumentPosition, int a2, double a3)
{
  int argExpr; // eax
  int i; // edx
  int v7; // eax
  int v8; // [esp+0h] [ebp-30h] BYREF
  int resultType; // [esp+4h] [ebp-2Ch]
  int resultValue; // [esp+8h] [ebp-28h]
  double returnValue; // [esp+18h] [ebp-18h]

  argExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    if ( i >= argumentPosition )
      break;
    argExpr = *(_DWORD *)(argExpr + 10);
  }
  if ( !argExpr )
  {
    Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
    returnValue = 1.0;
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return returnValue;
  }
  Parser_ParseForm((__int16 *)argExpr, &v8, a2, a3);
  if ( !resultType )
  {
    v7 = *(_DWORD *)(resultValue + 20);
    LODWORD(returnValue) = *(_DWORD *)(resultValue + 16);
    HIDWORD(returnValue) = v7;
    return returnValue;
  }
  if ( resultType == 1 )
    return (double)*(int *)(resultValue + 16);
  Rules_ExpectedTypeError((int)aRtndouble, *(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
  HIDWORD(returnValue) = 1072693248;
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  LODWORD(returnValue) = 0;
  return returnValue;
}
// 51A960: using guessed type int dword_51A960;

//----- (004812C0) --------------------------------------------------------
signed int  Rules_RtnLong(int argumentPosition, int a2, double a3)
{
  uintptr_t expression; // eax
  uintptr_t current; // eax
  int i; // edx
  uintptr_t function_node; // edx
  uintptr_t function_symbol; // edx
  _DWORD parsed[6]; // [esp+0h] [ebp-28h] BYREF

  expression = (uintptr_t)(unsigned int)g_ClipsCurrentExpression;
  current = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 6) : 0;
  for ( i = 1; current; ++i )
  {
    if ( i >= argumentPosition )
      break;
    current = (uintptr_t)(unsigned int)*(_DWORD *)(current + 10);
  }
  if ( !current )
  {
    function_node = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2) : 0;
    function_symbol = function_node ? (uintptr_t)(unsigned int)*(_DWORD *)function_node : 0;
    Rules_NonexistentArgError(function_symbol ? *(_DWORD *)(function_symbol + 16) : 0, argumentPosition);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 1;
  }
  Parser_ParseForm((__int16 *)current, parsed, a2, a3);
  if ( !parsed[1] )
    return (int)Parser_NumberValueAsDouble(parsed[2]);
  if ( parsed[1] == 1 )
    return Parser_NumberValueAsInt(parsed[2]);
  function_node = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2) : 0;
  function_symbol = function_node ? (uintptr_t)(unsigned int)*(_DWORD *)function_node : 0;
  Rules_ExpectedTypeError((int)aRtnlong, function_symbol ? *(_DWORD *)(function_symbol + 16) : 0, argumentPosition);
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (004813B0) --------------------------------------------------------
int  Rules_RtnUnknown(int argumentPosition, _DWORD *returnValue, double a3)
{
  int argExpr; // eax
  int i; // edx
  int resultType; // ecx

  argExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 1; argExpr; ++i )
  {
    if ( i >= argumentPosition )
      break;
    argExpr = *(_DWORD *)(argExpr + 10);
  }
  if ( argExpr )
  {
    Parser_ParseForm((__int16 *)argExpr, returnValue, (int)returnValue, a3);
    return resultType;
  }
  else
  {
    Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD **)(g_ClipsCurrentExpression + 2) + 16), argumentPosition);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 48140E: variable 'v8' is possibly undefined
// 51A960: using guessed type int dword_51A960;

//----- (00481420) --------------------------------------------------------
int Rules_RtnArgCount()
{
  int argExpr; // eax
  int i; // edx

  argExpr = *(_DWORD *)(g_ClipsCurrentExpression + 6);
  for ( i = 0; argExpr; ++i )
    argExpr = *(_DWORD *)(argExpr + 10);
  return i;
}
// 51A960: using guessed type int dword_51A960;

//----- (00481450) --------------------------------------------------------
int Lexer_TokenExpect(int expectedNumber)
{
  int result; // eax
  int countRelation; // edx
  int functionName; // ecx

  result = Rules_RtnArgCount();
  if ( !countRelation )
  {
    if ( result == expectedNumber )
      return result;
LABEL_9:
    Rules_ExpectedCountError(functionName, expectedNumber);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -1;
  }
  if ( countRelation == 1 )
  {
    if ( result < expectedNumber )
      goto LABEL_9;
  }
  else if ( countRelation != 2 || result > expectedNumber )
  {
    goto LABEL_9;
  }
  return result;
}
// 48145A: variable 'v2' is possibly undefined
// 481478: variable 'v3' is possibly undefined

//----- (004814A0) --------------------------------------------------------
int  Rules_ArgRangeCheck(int functionName, int maxArgs)
{
  int result; // eax
  int minArgs; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  result = Rules_RtnArgCount();
  if ( result < minArgs || result > maxArgs )
  {
    Rules_PrintErrorID((int)aArgacces, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAtLeas, v7);
    Rules_PrintLongInteger(v8, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAndNoMoreThan, v9);
    Rules_PrintLongInteger(v10, maxArgs);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aArguments_, v11);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -1;
  }
  return result;
}
// 4814B0: variable 'v4' is possibly undefined
// 4814D5: variable 'v5' is possibly undefined
// 4814E1: variable 'v6' is possibly undefined
// 4814F0: variable 'v7' is possibly undefined
// 4814FC: variable 'v8' is possibly undefined
// 48150B: variable 'v9' is possibly undefined
// 481517: variable 'v10' is possibly undefined
// 481526: variable 'v11' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

