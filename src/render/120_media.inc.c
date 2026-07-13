/* Recovered audio, music, AVI, and media support.
 * Original function-marker range: 0x004637B0..0x004814A0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (004637B0) --------------------------------------------------------
int * CAviDecompressor_ConstructEmpty(int *a1, DWORD a2)
{
  int v3; // eax

  v3 = Mem_Alloc(2236, (int)&g_CAviDecompressor_AllocTypeTag, 0, a2);
  if ( v3 )
    v3 = CAviDecompressor_InitCommon(v3);
  *a1 = v3;
  return a1;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00463B10) --------------------------------------------------------
int  CAviDecompressor_dtor(_DWORD *a1)
{
  int v1; // ecx

  CAviDecompressor_Done(a1);
  return v1;
}
// 463B18: variable 'v1' is possibly undefined

//----- (00463B20) --------------------------------------------------------
int * CAviDecompressor_ConstructAndInitCallbacks(
        int *a1,
        int (__stdcall ***a2)(_DWORD, void *, _DWORD *),
        int a3,
        int a4)
{
  int v7; // eax

  *a1 = 0;
  v7 = Mem_Alloc(2236, (int)&stru_50F60C, 0, (DWORD)a2);
  if ( v7 )
    v7 = CAviDecompressor_InitCommon(v7);
  *a1 = v7;
  if ( v7 )
    CAviDecompressor_Init(a1, a2, a3, a4);
  return a1;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00463E90) --------------------------------------------------------
void  CAviDecompressor_Init(
        int *a1,
        int (__stdcall ***a2)(_DWORD, void *, _DWORD *),
        int a3,
        int a4)
{
  int v4; // esi
  _DWORD v7[4]; // [esp+20h] [ebp-10h] BYREF

  v4 = *a1;
  v7[0] = 0;
  if ( !(**a2)(a2, &unk_51C9F8, v7) )
  {
    *(_DWORD *)(v4 + 1952) = a2;
    CAviDecompressor_ApplyDecoderFormatParams(a4, a3);
  }
}
// 4697E0: using guessed type int __fastcall sub_4697E0(_DWORD, _DWORD);

//----- (00463EA0) --------------------------------------------------------
int * CAviDecompressor_ConstructAndInitSource(int *a1, DWORD a2, int a3, int a4)
{
  int v6; // eax

  *a1 = 0;
  v6 = Mem_Alloc(2236, (int)&stru_50F6A0, 0, a2);
  if ( v6 )
    v6 = CAviDecompressor_InitCommon(v6);
  *a1 = v6;
  if ( v6 )
    CAviDecompressor_InitSource(a4, a3);
  return a1;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00464210) --------------------------------------------------------
void __fastcall CAviDecompressor_InitSource(int a1, int a2)
{
  CAviDecompressor_ApplyDecoderFormatParams(a1, a2);
}
// 4697E0: using guessed type int __fastcall sub_4697E0(_DWORD, _DWORD);

//----- (00464220) --------------------------------------------------------
void  CAviDecompressor_Done(_DWORD *a1)
{
  _DWORD *v1; // ecx
  int v2; // eax

  v1 = a1;
  v2 = *a1;
  if ( v2 )
    (**(void (__fastcall ***)(int, int))(v2 + 2232))(v2, 2);
  *v1 = 0;
}
// 464229: variable 'v1' is possibly undefined

//----- (00464250) --------------------------------------------------------
int  CAviDecompressor_Frames(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 43);
}

//----- (00464260) --------------------------------------------------------
int  CAviDecompressor_Fps(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 35) / *(_DWORD *)(*(_DWORD *)a1 + 31);
}

//----- (00464270) --------------------------------------------------------
void  CAviDecompressor_Start(int *a1)
{
  CAviDecompressor_BeginPlayback(*a1);
}

//----- (00464280) --------------------------------------------------------
void  CAviDecompressor_Stop(int *a1)
{
  CAviDecompressor_RequestRenderStop(*a1);
}

//----- (00464290) --------------------------------------------------------
BOOL  CAviDecompressor_IsPlaying(int a1)
{
  return *(_BYTE *)(*(_DWORD *)a1 + 2191) != 0;
}

//----- (004642B0) --------------------------------------------------------
int  CAviDecompressor_Initialized(_DWORD *a1)
{
  _DWORD *v1; // eax
  int result; // eax
  int v3; // ebx
  _DWORD *v4; // eax

  v1 = (_DWORD *)*a1;
  if ( *(_DWORD *)((char *)v1 + 7) )
    LOBYTE(result) = *(_DWORD *)((char *)v1 + 415) || (v3 = v1[486], v4 = v1 + 481, v3) || v4[4];
  else
    LOBYTE(result) = 0;
  return (unsigned __int8)result;
}

//----- (004642F0) --------------------------------------------------------
void  CAviDecompressor_WaitForNextFrame(int *a1)
{
  int v1; // eax

  v1 = *a1;
  if ( *(_BYTE *)(v1 + 2191) )
    WaitForSingleObject(*(HANDLE *)(v1 + 2196), 0x1F4u);
}

//----- (00464320) --------------------------------------------------------
int  CAviDecompressor_Palette(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 1948);
}

//----- (00464330) --------------------------------------------------------
int  CAviDecompressor_Header(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 151);
}

//----- (00464340) --------------------------------------------------------
int  CAviDecompressor_PixelSize(int *a1)
{
  return (*(unsigned __int16 *)(CAviDecompressor_GetVideoFormat(*a1) + 14) + 7) >> 3;
}

//----- (00464360) --------------------------------------------------------
int  CAviDecompressor_BPP(int a1)
{
  return *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)a1 + 151) + 14);
}

//----- (00464380) --------------------------------------------------------
int  CAviDecompressor_Width(int a1)
{
  return *(_DWORD *)(*(_DWORD *)(*(_DWORD *)a1 + 151) + 4);
}

//----- (00464390) --------------------------------------------------------
int  CAviDecompressor_Height(int a1)
{
  __int64 v1; // rax

  v1 = *(int *)(*(_DWORD *)(*(_DWORD *)a1 + 151) + 8);
  return (HIDWORD(v1) ^ v1) - HIDWORD(v1);
}

//----- (004643B0) --------------------------------------------------------
int  CAviDecompressor_DecodedFrame(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 2021);
}

//----- (004643C0) --------------------------------------------------------
int  CAviDecompressor_SetBackground(int *a1, _DWORD *a2, int a3)
{
  int result; // eax

  result = *a1;
  *(_DWORD *)(result + 2155) = *a2;
  *(_DWORD *)(result + 2159) = a2[1];
  *(_DWORD *)(result + 2163) = a2[2];
  *(_DWORD *)(result + 2167) = a2[3];
  *(_DWORD *)(result + 2151) = a3;
  return result;
}

//----- (004643E0) --------------------------------------------------------
void  CAviDecompressor_InitClipRect(_DWORD *a1, _DWORD *a2)
{
  _DWORD *v2; // edi

  v2 = (_DWORD *)(*a1 + 1969);
  *v2++ = *a2;
  *v2++ = a2[1];
  *v2 = a2[2];
  v2[1] = a2[3];
}

//----- (00464400) --------------------------------------------------------
void  CAviDecompressor_UpdatePos(int *a1, LONG a2, int a3, LONG a4)
{
  int v4; // eax
  int v5; // ecx
  int v6; // ebx
  int v7; // esi
  int v8; // ecx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edi
  int v13; // eax
  __int64 v14; // rax
  int v15; // ebp
  int v16; // eax
  RECT v17; // [esp+170h] [ebp-30h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+180h] [ebp-20h]
  tagRECT *v19; // [esp+184h] [ebp-1Ch]
  void *v20; // [esp+188h] [ebp-18h]
  int v21; // [esp+18Ch] [ebp-14h]
  int v22; // [esp+19Ch] [ebp-4h]

  v4 = *a1;
  v22 = a3;
  v5 = v4;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v19 = &j____wcpp_4_fs_handler_rtn_;
  v20 = &g_AviUpdatePos_EHFrame;
  v21 = 0;
  if ( !*(_BYTE *)(v4 + 2062) )
  {
    v17 = *(RECT *)dword_54D340;
    v17.left = a2;
    v17.top = a4;
    v17.right = *(_DWORD *)(*(_DWORD *)(v4 + 151) + 4) + a2;
    v14 = *(int *)(*(_DWORD *)(v4 + 151) + 8);
    v17.bottom = (HIDWORD(v14) ^ v14) - HIDWORD(v14) + a4;
    AviPlayer_RenderFrame(v5, &v17);
  }
  v6 = v5;
  if ( *(_BYTE *)(v5 + 1968) && *(_DWORD *)(v5 + 1964) )
  {
    v7 = 1000 * AviPlayer_SpanDelta(v5, (_DWORD *)(v5 + 2063));
    v9 = v7 / AviPlayer_SpanDelta(v8, (_DWORD *)(v8 + 2079));
    if ( v9 < *(_DWORD *)(v10 + 2143) || v9 > *(_DWORD *)(v10 + 2147) )
    {
      if ( *(_BYTE *)(v6 + 1968) )
      {
        v15 = *(_DWORD *)(v6 + 1964);
        if ( v15 )
        {
          v16 = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(*(_DWORD *)v15 + 132))(
                  v15,
                  v6 + 2095,
                  *(_DWORD *)(v6 + 1956),
                  v6 + 2063,
                  512,
                  0);
          if ( v16 )
          {
            if ( v16 != -2005532222
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
      v11 = 0x4000;
      if ( *(_DWORD *)(v10 + 2171) )
        v11 = 20480;
      v12 = v11;
      v13 = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v6 + 1964) + 132))(
              *(_DWORD *)(v6 + 1964),
              v6 + 2095,
              *(_DWORD *)(v6 + 1956),
              v6 + 2063,
              v11,
              0);
      if ( v13
        && (v13 != -2005532222
         || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1964) + 96))(*(_DWORD *)(v6 + 1964)) != -2005532222
          || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1964) + 108))(*(_DWORD *)(v6 + 1964)))
         && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1956) + 96))(*(_DWORD *)(v6 + 1956)) != -2005532222
          || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v6 + 1956) + 108))(*(_DWORD *)(v6 + 1956)))
         && (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v6 + 1964) + 132))(
              *(_DWORD *)(v6 + 1964),
              v6 + 2095,
              *(_DWORD *)(v6 + 1956),
              v6 + 2063,
              v12,
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
void  CAviDecompressor_UpdateRect(int *a1, const RECT *a2)
{
  CAviDecompressor_PresentFrameForRect(*a1, a2);
}

//----- (00464420) --------------------------------------------------------
void  CAviDecompressor_Blit(int *a1)
{
  int v1; // eax

  v1 = *a1;
  if ( *(_BYTE *)(v1 + 2191) )
    CAviDecompressor_PresentFrameIfStale(v1, 0);
}

//----- (00464440) --------------------------------------------------------
void  CAviDecompressor_BlitTo(int *a1, LONG a2, int a3, LONG a4)
{
  int v4; // ecx
  int v5; // eax
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  RECT v9; // [esp+0h] [ebp-14h] BYREF
  int v10; // [esp+10h] [ebp-4h]

  v10 = a3;
  v4 = *a1;
  if ( *(_BYTE *)(*a1 + 2191) )
  {
    v9 = *(RECT *)dword_54E920;
    v9.left = a2;
    v9.top = a4;
    v5 = CAviDecompressor_GetVideoFormat(v4);
    v9.right = *(_DWORD *)(v5 + 4) + v6;
    v9.bottom = abs32(*(_DWORD *)(CAviDecompressor_GetVideoFormat(v7) + 8)) + a4;
    CAviDecompressor_PresentFrameIfStale(v8, &v9);
  }
}
// 464479: variable 'v6' is possibly undefined
// 46447D: variable 'v7' is possibly undefined
// 464496: variable 'v8' is possibly undefined

//----- (004644B0) --------------------------------------------------------
void  CAviDecompressor_StretchTo(int *a1, const RECT *a2)
{
  int v2; // eax

  v2 = *a1;
  if ( *(_BYTE *)(v2 + 2191) )
    CAviDecompressor_PresentFrameIfStale(v2, a2);
}

//----- (004644C0) --------------------------------------------------------
void  CAviDecompressor_GetRect(_DWORD *a1, _DWORD *a2)
{
  _DWORD *v2; // esi

  v2 = (_DWORD *)(*a1 + 2063);
  *a2 = *v2++;
  a2[1] = *v2++;
  a2[2] = *v2;
  a2[3] = v2[1];
}

//----- (004644E0) --------------------------------------------------------
void  CAviDecompressor_InitColorKeys(int *a1, int a2, int a3)
{
  int v3; // eax

  v3 = *a1;
  *(_DWORD *)(v3 + 2171) = 8;
  *(_DWORD *)(v3 + 2042) = a2;
  *(_DWORD *)(v3 + 2046) = a3;
}

//----- (00464500) --------------------------------------------------------
void  CAviDecompressor_InitPos(int *a1, int a2, int a3)
{
  int v3; // eax

  v3 = *a1;
  *(_DWORD *)(v3 + 2071) = 0;
  *(_DWORD *)(v3 + 2075) = 0;
  *(_BYTE *)(v3 + 2062) = 1;
  *(_DWORD *)(v3 + 2063) = a2;
  *(_DWORD *)(v3 + 2067) = a3;
}

//----- (00464530) --------------------------------------------------------
void  CAviDecompressor_InitRect(int *a1, _DWORD *a2)
{
  int v2; // eax

  v2 = *a1;
  *(_DWORD *)(v2 + 2063) = *a2;
  *(_DWORD *)(v2 + 2067) = a2[1];
  *(_DWORD *)(v2 + 2071) = a2[2];
  *(_DWORD *)(v2 + 2075) = a2[3];
  *(_BYTE *)(v2 + 2062) = 1;
}

//----- (00464550) --------------------------------------------------------
void  CAviDecompressor_InitOverlays(int a1, char a2)
{
  *(_BYTE *)(*(_DWORD *)a1 + 2050) = a2 != 0;
}

//----- (00464570) --------------------------------------------------------
unsigned int  CAviDecompressor_TimeMs(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 43)
       * ((unsigned int)(1000 * *(_DWORD *)(*(_DWORD *)a1 + 31))
        / *(_DWORD *)(*(_DWORD *)a1 + 35));
}

//----- (004645C0) --------------------------------------------------------
int  CAviDecompressor_SumSleepTime(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 2038);
}

//----- (004645D0) --------------------------------------------------------
void __stdcall PlayAvi(char *a1, IDirectDrawSurface *a2, int a3, int a4, int (*a5)(void), int a6)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  char *v9; // [esp+4h] [ebp-24h]
  IDirectDrawSurface *v10; // [esp+8h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-1Ch]
  int v12[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v9 = (char *)&j____wcpp_4_fs_handler_rtn_;
  v10 = &stru_50F734;
  CAviDecompressor_ConstructEmpty(v12, 0);
  v11 = 1;
  CAviDecompressor_InitPos(v12, a3, a4);
  CAviDecompressor_Init(v12, a2, (int)a1, a6);
  if ( CAviDecompressor_Initialized(v12) )
  {
    CAviDecompressor_Start(v12);
    while ( CAviDecompressor_IsPlaying((int)v12)
         && (!a5
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, char *, IDirectDrawSurface *, int))a5)(
               ExceptionList,
               v9,
               v10,
               v11)) )
    {
      CAviDecompressor_Blit(v12);
      CAviDecompressor_WaitForNextFrame(v12);
    }
  }
  CAviDecompressor_dtor(v12);
}
// 464699: variable 'ExceptionList' is possibly undefined
// 464699: variable 'v9' is possibly undefined
// 464699: variable 'v10' is possibly undefined
// 464699: variable 'v11' is possibly undefined

//----- (004646B0) --------------------------------------------------------
void __stdcall PlayAviStretch(char *a1, IDirectDrawSurface *a2, tagRECT *a3, int (*a4)(void), int a5)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  tagRECT *v8; // [esp+4h] [ebp-24h]
  IDirectDrawSurface *v9; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]
  int v11[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v8 = &j____wcpp_4_fs_handler_rtn_;
  v9 = &stru_50F740;
  CAviDecompressor_ConstructEmpty(v11, 0);
  v10 = 1;
  CAviDecompressor_InitRect(v11, a3);
  CAviDecompressor_Init(v11, a2, (int)a1, a5);
  if ( CAviDecompressor_Initialized(v11) )
  {
    CAviDecompressor_Start(v11);
    while ( CAviDecompressor_IsPlaying((int)v11)
         && (!a4
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, IDirectDrawSurface *, int))a4)(
               ExceptionList,
               v8,
               v9,
               v10)) )
    {
      CAviDecompressor_Blit(v11);
      CAviDecompressor_WaitForNextFrame(v11);
    }
  }
  CAviDecompressor_dtor(v11);
}
// 464774: variable 'ExceptionList' is possibly undefined
// 464774: variable 'v8' is possibly undefined
// 464774: variable 'v9' is possibly undefined
// 464774: variable 'v10' is possibly undefined

//----- (00464780) --------------------------------------------------------
void __stdcall PlayAviSurface2(char *a1, IDirectDrawSurface2 *a2, int a3, int a4, int (*a5)(void), int a6)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  char *v9; // [esp+4h] [ebp-24h]
  IDirectDrawSurface2 *v10; // [esp+8h] [ebp-20h]
  int v11; // [esp+Ch] [ebp-1Ch]
  int v12[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v9 = (char *)&j____wcpp_4_fs_handler_rtn_;
  v10 = &stru_50F74C;
  CAviDecompressor_ConstructEmpty(v12, 0);
  v11 = 1;
  CAviDecompressor_InitPos(v12, a3, a4);
  CAviDecompressor_InitSource(a6, (int)a1);
  if ( CAviDecompressor_Initialized(v12) )
  {
    CAviDecompressor_Start(v12);
    while ( CAviDecompressor_IsPlaying((int)v12)
         && (!a5
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, char *, IDirectDrawSurface2 *, int))a5)(
               ExceptionList,
               v9,
               v10,
               v11)) )
    {
      CAviDecompressor_Blit(v12);
      CAviDecompressor_WaitForNextFrame(v12);
    }
  }
  CAviDecompressor_dtor(v12);
}
// 464849: variable 'ExceptionList' is possibly undefined
// 464849: variable 'v9' is possibly undefined
// 464849: variable 'v10' is possibly undefined
// 464849: variable 'v11' is possibly undefined

//----- (00464860) --------------------------------------------------------
void __stdcall PlayAviStretchSurface2(char *a1, IDirectDrawSurface2 *a2, tagRECT *a3, int (*a4)(void), int a5)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]
  tagRECT *v8; // [esp+4h] [ebp-24h]
  IDirectDrawSurface2 *v9; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]
  int v11[5]; // [esp+14h] [ebp-14h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v8 = &j____wcpp_4_fs_handler_rtn_;
  v9 = &stru_50F758;
  CAviDecompressor_ConstructEmpty(v11, 0);
  v10 = 1;
  CAviDecompressor_InitRect(v11, a3);
  CAviDecompressor_InitSource(a5, (int)a1);
  if ( CAviDecompressor_Initialized(v11) )
  {
    CAviDecompressor_Start(v11);
    while ( CAviDecompressor_IsPlaying((int)v11)
         && (!a4
          || ((int (__cdecl *)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, IDirectDrawSurface2 *, int))a4)(
               ExceptionList,
               v8,
               v9,
               v10)) )
    {
      CAviDecompressor_Blit(v11);
      CAviDecompressor_WaitForNextFrame(v11);
    }
  }
  CAviDecompressor_dtor(v11);
}
// 464924: variable 'ExceptionList' is possibly undefined
// 464924: variable 'v8' is possibly undefined
// 464924: variable 'v9' is possibly undefined
// 464924: variable 'v10' is possibly undefined

//----- (00464930) --------------------------------------------------------
int  CAviDecompressor_InitThreadGuard(int a1)
{
  *(_DWORD *)a1 = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(a1 + 4));
  return a1;
}

//----- (00464950) --------------------------------------------------------
int  CAviDecompressor_DoneThreadGuard(int a1)
{
  DeleteCriticalSection((LPCRITICAL_SECTION)(a1 + 4));
  return a1;
}

//----- (00464970) --------------------------------------------------------
HANDLE * CAviDecompressor_ConstructEventHandle(HANDLE *a1, bool a2, bool a3)
{
  *a1 = CreateEventA(0, a2, a3, 0);
  return a1;
}

//----- (00464990) --------------------------------------------------------
HANDLE * CAviDecompressor_DestroyEventHandle(HANDLE *a1)
{
  CloseHandle(*a1);
  return a1;
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
int  CAviDecompressor_ConstructSourceInterface(int a1)
{
  int v1; // ebx
  int v2; // edx
  HANDLE *v3; // ebx

  *(_BYTE *)a1 = 0;
  *(_BYTE *)(a1 + 1) = 1;
  *(_DWORD *)(a1 + 3) = 0;
  *(_DWORD *)(a1 + 7) = 0;
  *(_DWORD *)(a1 + 151) = 0;
  *(_DWORD *)(a1 + 163) = 0;
  v1 = a1 + 171;
  *(_DWORD *)(a1 + 167) = CreateEventA(0, 0, 0, 0);
  v1 += 4;
  *(_DWORD *)(v1 - 4) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)v1 = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(v1 + 4));
  *(_DWORD *)(v1 + 28) = 0;
  *(_DWORD *)(v1 + 32) = 0;
  *(_DWORD *)(v1 + 36) = 0;
  v2 = v1 - 175;
  *(_DWORD *)(v1 - 175 + 215) = 0;
  *(_DWORD *)(v1 - 175 + 363) = 0;
  *(_DWORD *)(v1 - 175 + 375) = 0;
  v3 = (HANDLE *)(v1 - 175 + 387);
  *(_DWORD *)(v2 + 379) = 0;
  *v3 = CreateEventA(0, 0, 0, 0);
  v3[1] = 0;
  v3[2] = 0;
  v3[3] = 0;
  v3 += 4;
  *v3++ = CreateEventA(0, 0, 0, 0);
  *v3 = CreateEventA(0, 0, 0, 0);
  v3[1] = &g_CAviSourceInterface_Vtable;
  return (int)v3 - 407;
}
// 50FDD4: using guessed type int (*off_50FDD4)();

//----- (00464B50) --------------------------------------------------------
char * CAviDecompressor_DestroySourceInterface(int a1, char a2)
{
  HANDLE *v3; // esi
  char *v4; // ecx
  int v6; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_CAviSourceInterface_DtorArrayTag);
    j_j__nfree_();
    return (char *)v6;
  }
  else
  {
    *(_DWORD *)(a1 + 411) = &g_CAviSourceInterface_Vtable;
    v3 = (HANDLE *)(a1 + 407);
    AviPlayer_CloseStreams(a1);
    CloseHandle(*v3);
    CloseHandle(*(v3 - 1));
    j_j__nfree_();
    CloseHandle(*(v3 - 5));
    v3 -= 51;
    j_j__nfree_();
    DeleteCriticalSection((LPCRITICAL_SECTION)v3 - 1);
    CloseHandle(*(v3 - 8));
    CloseHandle(*(v3 - 9));
    v4 = (char *)v3 - 203;
    if ( (a2 & 2) != 0 )
      j__nfree_();
    return v4;
  }
}
// 464C7C: variable 'v4' is possibly undefined
// 464CA7: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50FDD4: using guessed type int (*off_50FDD4)();

//----- (00464CC0) --------------------------------------------------------
int  CAviDecompressor_GetVideoFormat(int a1)
{
  return *(_DWORD *)(a1 + 151);
}

//----- (00464CD0) --------------------------------------------------------
int  CAviDecompressor_ReleaseVideoCodec(_DWORD *a1, int a2)
{
  int v2; // ecx

  CAviDecompressor_CloseCodecHandle(a1, (int)a1, a2);
  return v2;
}
// 464CD8: variable 'v2' is possibly undefined

//----- (00464CE0) --------------------------------------------------------
int  CAviDecompressor_InitCommon(int a1)
{
  memset((void *)(uintptr_t)(unsigned int)a1, 0, 2236);
  *(_BYTE *)a1 = 0;
  *(_BYTE *)(a1 + 1) = 1;
  *(_DWORD *)(a1 + 167) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(a1 + 171) = CreateEventA(0, 0, 0, 0);
  InitializeCriticalSection((LPCRITICAL_SECTION)(a1 + 179));
  *(_DWORD *)(a1 + 387) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(a1 + 403) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(a1 + 407) = CreateEventA(0, 0, 0, 0);
  *(_DWORD *)(a1 + 411) = &g_CAviSourceInterface_Vtable;
  InitializeCriticalSection((LPCRITICAL_SECTION)(a1 + 1989));
  *(_DWORD *)(a1 + 2196) = CreateEventA(0, 1, 1, 0);
  InitializeCriticalSection((LPCRITICAL_SECTION)(a1 + 2204));
  *(_DWORD *)(a1 + 2228) = CreateEventA(0, 1, 1, 0);
  *(_DWORD *)(a1 + 2232) = &g_CAviDecompressor_Vtable;
  SetRect((LPRECT)(a1 + 1969), -100000, -100000, 100000, 100000);
  return a1;
}
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (00464FD0) --------------------------------------------------------
int  CAviDecompressor_Destroy(int a1, char a2)
{
  int v11; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_CAviDecompressor_DtorArrayTag);
    j_j__nfree_();
    return v11;
  }
  else
  {
    *(_DWORD *)(a1 + 2232) = &g_CAviDecompressor_Vtable;
    AviPlayer_ShutdownDecodeState(a1);
    CloseHandle(*(HANDLE *)(a1 + 2228));
    DeleteCriticalSection((LPCRITICAL_SECTION)(a1 + 2204));
    CloseHandle(*(HANDLE *)(a1 + 2196));
    DeleteCriticalSection((LPCRITICAL_SECTION)(a1 + 1989));
    CAviDecompressor_CloseCodecHandle((_DWORD *)(a1 + 415), a1 + 415, 16);
    *(_DWORD *)(a1 + 411) = &g_CAviSourceInterface_Vtable;
    AviPlayer_CloseStreams(a1);
    CloseHandle(*(HANDLE *)(a1 + 407));
    CloseHandle(*(HANDLE *)(a1 + 403));
    j_j__nfree_();
    CloseHandle(*(HANDLE *)(a1 + 387));
    j_j__nfree_();
    DeleteCriticalSection((LPCRITICAL_SECTION)(a1 + 179));
    CloseHandle(*(HANDLE *)(a1 + 171));
    CloseHandle(*(HANDLE *)(a1 + 167));
    if ( (a2 & 2) != 0 )
      j__nfree_();
    return a1;
  }
}
// 4651BB: variable 'v11' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 50FDD4: using guessed type int (*off_50FDD4)();
// 50FDE4: using guessed type int (*off_50FDE4)();

//----- (004651D0) --------------------------------------------------------
DWORD __stdcall StartAddress(char *lpThreadParameter)
{
  _DWORD *v1; // ebx
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  signed int Frame; // esi
  int v7; // ecx
  int v8; // edx
  int v9; // edi
  int v10; // eax
  int v11; // edx
  int v12; // eax
  signed int *v13; // edi
  int v14; // esi
  int v15; // eax
  int v16; // edx
  signed int v17; // eax
  signed int v18; // edi
  int v19; // esi
  int v20; // eax
  char *v21; // eax
  int v22; // edx
  int *v23; // edi
  int Sample; // eax
  int v25; // [esp-14h] [ebp-70h]
  int v26; // [esp-10h] [ebp-6Ch]
  int v27; // [esp-Ch] [ebp-68h]
  int v28; // [esp+14h] [ebp-48h]
  signed int v29; // [esp+18h] [ebp-44h]
  int v30; // [esp+1Ch] [ebp-40h]
  signed int v31; // [esp+24h] [ebp-38h]
  signed int v32; // [esp+28h] [ebp-34h] BYREF
  int v33; // [esp+2Ch] [ebp-30h] BYREF
  HANDLE *v34; // [esp+30h] [ebp-2Ch]
  HANDLE *v35; // [esp+34h] [ebp-28h]
  HANDLE *v36; // [esp+38h] [ebp-24h]
  char *v37; // [esp+3Ch] [ebp-20h]
  char *v38; // [esp+40h] [ebp-1Ch]
  char *v39; // [esp+44h] [ebp-18h]
  HANDLE *v40; // [esp+48h] [ebp-14h]
  char *v41; // [esp+4Ch] [ebp-10h]
  _DWORD *v42; // [esp+50h] [ebp-Ch]
  char v43; // [esp+54h] [ebp-8h]
  char v44; // [esp+58h] [ebp-4h]

  v37 = lpThreadParameter + 175;
  ++*(_DWORD *)(lpThreadParameter + 175);
  EnterCriticalSection((LPCRITICAL_SECTION)(lpThreadParameter + 179));
  if ( !lpThreadParameter[1] )
  {
    v40 = (HANDLE *)(lpThreadParameter + 407);
    v36 = (HANDLE *)(lpThreadParameter + 403);
    v35 = (HANDLE *)(lpThreadParameter + 171);
    v41 = lpThreadParameter + 203;
    v34 = (HANDLE *)(lpThreadParameter + 387);
    v42 = lpThreadParameter + 391;
    v39 = lpThreadParameter + 219;
    do
    {
      if ( *((_DWORD *)v41 + 2) < *(_DWORD *)(lpThreadParameter + 43) )
      {
        v43 = 0;
        v44 = 0;
        if ( *(_DWORD *)(lpThreadParameter + 215) )
        {
          AviPlayer_AudioSampleQueueCount((int)v42);
          AviPlayer_AudioBytesQueued((int)lpThreadParameter);
          v3 = AviPlayer_AudioBlockAlign((int)lpThreadParameter);
          if ( v4 / v3 * v5 / *(_DWORD *)(lpThreadParameter + 367) - *((_DWORD *)v39 + 9) <= *((_DWORD *)v41 + 2) )
          {
            Frame = AviPlayer_DecodeNextFrame((int)lpThreadParameter);
            if ( Frame == -1 )
            {
              v44 = 1;
            }
            else
            {
              v43 = 1;
              v27 = *((_DWORD *)v39 + 10);
              v26 = Frame + *(_DWORD *)(lpThreadParameter + 375);
              AviPlayer_AudioSampleQueueBase((int)lpThreadParameter);
              LOWORD(v7) = *(_WORD *)(AviPlayer_AudioFormatPtr((int)lpThreadParameter) + 12);
              v25 = v8 / v7;
              v9 = AviPlayer_AudioSampleQueueCount((int)v42);
              AviPlayer_AudioBytesQueued((int)lpThreadParameter);
              v10 = AviPlayer_AudioBlockAlign((int)lpThreadParameter);
              AVIStreamRead(
                v10,
                v11 % v10,
                *(_DWORD *)(lpThreadParameter + 215),
                v9 * (v11 / v10),
                v25,
                v26,
                v27,
                &v32,
                0);
              v31 = v32;
              v12 = v42[2];
              v13 = (signed int *)(8 * v12 + *v42);
              v42[2] = v12 + 1;
              *v13 = Frame;
              v13[1] = v31;
            }
          }
        }
        if ( *(_DWORD *)(lpThreadParameter + 215)
          && (v14 = AviPlayer_AudioSampleQueueCount((int)v42),
              AviPlayer_AudioBytesQueued((int)lpThreadParameter),
              v15 = AviPlayer_AudioBlockAlign((int)lpThreadParameter),
              *((_DWORD *)v41 + 2) > v16 / v15 * v14 / *(_DWORD *)(lpThreadParameter + 367) - *((_DWORD *)v39 + 9)) )
        {
          if ( v44 )
          {
            PulseEvent(*v40);
            WaitForSingleObject(*v34, 0x1F4u);
            continue;
          }
          if ( lpThreadParameter[2] )
            goto LABEL_28;
        }
        else
        {
          v17 = CAviDecompressor_GetNextAudioSampleOffset((int)lpThreadParameter);
          if ( v17 != -1 )
          {
            v18 = v17;
            v19 = *((_DWORD *)v41 + 2);
            AVIStreamRead(
              *(_DWORD *)(lpThreadParameter + 7),
              *(_DWORD *)(lpThreadParameter + 163),
              *(_DWORD *)(lpThreadParameter + 7),
              v19,
              1,
              *(_DWORD *)(lpThreadParameter + 163) + v17,
              *(_DWORD *)(lpThreadParameter + 155),
              &v33,
              0);
            v38 = lpThreadParameter;
            if ( v33 )
            {
              Sample = AVIStreamFindSample(*(_DWORD *)(lpThreadParameter + 7), v19, 20);
              if ( Sample == v19 )
                v20 = v19 ^ Sample;
              else
                v20 = 0x8000000;
            }
            else
            {
              v20 = 0x10000000;
            }
            v28 = v20;
            v30 = v33;
            v21 = v38;
            v22 = *(_DWORD *)(v38 + 211);
            v29 = v18;
            v23 = (int *)(12 * v22 + *(_DWORD *)(v38 + 203));
            *(_DWORD *)(v38 + 211) = v22 + 1;
            *v23++ = v28;
            *v23 = v29;
            v23[1] = v30;
            PulseEvent(*(HANDLE *)(v21 + 167));
            if ( !lpThreadParameter[2] )
              continue;
LABEL_28:
            Sleep(0);
            continue;
          }
          PulseEvent(*v40);
          if ( v43 )
          {
            if ( lpThreadParameter[2] )
              goto LABEL_28;
          }
          else
          {
            WaitForSingleObject(*v35, 0x1F4u);
          }
        }
      }
      else
      {
        PulseEvent(*v40);
        WaitForSingleObject(*v36, 0x1F4u);
      }
    }
    while ( !lpThreadParameter[1] );
  }
  v1 = v37;
  LeaveCriticalSection((LPCRITICAL_SECTION)(v37 + 4));
  --*v1;
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
BOOL  CAviDecompressor_RequestDecodeThreadStop(int a1)
{
  *(_BYTE *)(a1 + 1) = 1;
  CSS_StopSound(*(_DWORD *)(a1 + 359), 0);
  PulseEvent(*(HANDLE *)(a1 + 403));
  PulseEvent(*(HANDLE *)(a1 + 171));
  return PulseEvent(*(HANDLE *)(a1 + 387));
}

//----- (004655B0) --------------------------------------------------------
signed int  CAviDecompressor_GetNextAudioSampleOffset(int a1)
{
  int v1; // ecx
  int v2; // edx
  int v3; // esi

  if ( *(_DWORD *)(a1 + 211) == *(_DWORD *)(a1 + 207) )
    v1 = 0;
  else
    v1 = *(_DWORD *)(12 * (*(_DWORD *)(a1 + 211) - 1) + *(_DWORD *)(a1 + 203) + 4)
       + *(_DWORD *)(12 * (*(_DWORD *)(a1 + 211) - 1) + *(_DWORD *)(a1 + 203) + 8);
  v2 = *(_DWORD *)(a1 + 211) - *(_DWORD *)(a1 + 207);
  if ( v2 )
    v2 = *(_DWORD *)(*(_DWORD *)(a1 + 203) + 12 * *(_DWORD *)(a1 + 207) + 4);
  if ( v2 <= v1 )
  {
    v3 = *(_DWORD *)(a1 + 155);
    if ( *(_DWORD *)(a1 + 159) - v1 >= v3 )
      return v1;
    if ( v2 > v3 )
      return 0;
    return -1;
  }
  if ( v2 - v1 <= *(_DWORD *)(a1 + 155) )
    return -1;
  return v1;
}

//----- (00465670) --------------------------------------------------------
signed int  AviPlayer_DecodeNextFrame(int a1)
{
  int v1; // edx
  int v2; // ecx
  int v3; // esi
  int v4; // eax

  v1 = *(_DWORD *)(a1 + 399) - *(_DWORD *)(a1 + 395);
  if ( v1 )
    v1 = *(_DWORD *)(*(_DWORD *)(a1 + 391) + 8 * (*(_DWORD *)(a1 + 399) - 1) + 4)
       + *(_DWORD *)(*(_DWORD *)(a1 + 391) + 8 * (*(_DWORD *)(a1 + 399) - 1));
  v2 = *(_DWORD *)(a1 + 399) - *(_DWORD *)(a1 + 395);
  if ( v2 )
    v2 = *(_DWORD *)(*(_DWORD *)(a1 + 391) + 8 * *(_DWORD *)(a1 + 395));
  if ( v2 <= v1 )
  {
    v3 = *(_DWORD *)(a1 + 371);
    v4 = *(_DWORD *)(a1 + 259);
    if ( v3 - v1 >= v4 )
      return v1;
    if ( v2 > v4 )
      return 0;
    return -1;
  }
  if ( v2 - v1 <= *(_DWORD *)(a1 + 259) )
    return -1;
  return v1;
}

//----- (00465710) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
HANDLE  AviPlayer_OpenFileAndStartDecodeThread(
        int a1,
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
  int v31; // eax
  char v32; // dl
  unsigned int v33; // eax
  unsigned int v34; // eax
  int v35; // ecx
  unsigned int v36; // ebx
  signed int v37; // eax
  __int64 v38; // rax
  int v39; // ebx
  int v40; // eax
  _DWORD v41[10]; // [esp+82h] [ebp-2Ah] BYREF

  *(_DWORD *)((char *)&ThreadId_2 + 2) = a3;
  *(_DWORD *)(&Buffer_30a + 2) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a23 + 2) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a23 + 6) = &g_AviOpenFileDecodeThread_EHFrame;
  *(_DWORD *)((char *)&a24 + 2) = 0;
  if ( !*(_BYTE *)a1 )
  {
    AVIFileInit();
    *(_BYTE *)a1 = 1;
  }
  result = (HANDLE)AVIFileOpenA(a1 + 3, a2, 0, 0);
  if ( result )
  {
    *(_DWORD *)(a1 + 3) = 0;
  }
  else
  {
    AVIFileInfoA(*(_DWORD *)(a1 + 3), v41, 108);
    if ( AVIFileGetStream(*(_DWORD *)(a1 + 3), a1 + 7, 1935960438, 0) )
    {
      result = (HANDLE)AVIFileRelease(*(_DWORD *)(a1 + 3));
      *(_DWORD *)(a1 + 3) = 0;
      *(_DWORD *)(a1 + 7) = 0;
    }
    else
    {
      AVIStreamReadFormat(*(_DWORD *)(a1 + 7), 0, 0, (char *)&a25 + 2);
      *(_DWORD *)(a1 + 151) = j_Mem_Alloc(v30);
      AVIStreamReadFormat(*(_DWORD *)(a1 + 7), 0, *(_DWORD *)(a1 + 151), (char *)&a25 + 2);
      v31 = *(_DWORD *)(a1 + 151);
      v32 = *(_BYTE *)(v31 + 13);
      if ( v32 < 0 )
      {
        *(_BYTE *)(v31 + 13) = v32 ^ 0x80;
        *(_DWORD *)(*(_DWORD *)(a1 + 151) + 16) ^= 0x3ADE68B1u;
      }
      AVIStreamInfoA(*(_DWORD *)(a1 + 7), a1 + 11, 140);
      AVIStreamBeginStreaming(*(_DWORD *)(a1 + 7), 0, *(_DWORD *)(a1 + 43) - 1, 1000);
      if ( *(_DWORD *)(a1 + 51) )
        v33 = *(_DWORD *)(a1 + 51);
      else
        v33 = abs32(*(_DWORD *)(*(_DWORD *)(a1 + 151) + 8))
            * (*(_DWORD *)(*(_DWORD *)(a1 + 151) + 4) / 20 + *(_DWORD *)(*(_DWORD *)(a1 + 151) + 4) + 1)
            * ((*(unsigned __int16 *)(*(_DWORD *)(a1 + 151) + 14) + 7) >> 3);
      *(_DWORD *)(a1 + 155) = v33;
      v34 = v33 + 3;
      LOBYTE(v34) = v34 & 0xFC;
      v35 = 1000;
      *(_DWORD *)(a1 + 155) = v34 + 16;
      v36 = *(_DWORD *)(a1 + 31);
      *(_DWORD *)(a1 + 159) = (*(_DWORD *)((char *)&ThreadId_2 + 2) - 500)
                            * ((int)(20000 * (v41[0] / 0x3E8u))
                             / (int)(v41[0] / 0x3E8u + 20000));
      v37 = (*(_DWORD *)(a1 + 155) * (*(_DWORD *)(a1 + 35) / v36)) >> 1;
      if ( v37 > *(_DWORD *)(a1 + 159) )
        goto LABEL_11;
      v39 = *(_DWORD *)(a1 + 35) / *(_DWORD *)(a1 + 31);
      v40 = *(_DWORD *)(a1 + 43) * *(_DWORD *)(a1 + 155);
      if ( *(_DWORD *)(a1 + 43) / v39 * v41[0] < (unsigned int)v40 )
        v40 = *(_DWORD *)(a1 + 43) / v39 * v41[0];
      if ( v40 < *(_DWORD *)(a1 + 159) )
        *(_DWORD *)(a1 + 159) = v40;
      GlobalMemoryStatus((LPMEMORYSTATUS)((char *)&a15 + 2));
      v35 = *(_DWORD *)(a1 + 159);
      v37 = *(_DWORD *)((char *)&Buffer_6 + 2) >> 4;
      if ( *(_DWORD *)((char *)&Buffer_6 + 2) >> 4 < v35 )
LABEL_11:
        *(_DWORD *)(a1 + 159) = v37;
      *(_DWORD *)(a1 + 163) = j_Mem_Alloc(v35);
      v38 = j_Mem_Alloc(*(_DWORD *)(a1 + 43) + 1);
      *(_QWORD *)(HIDWORD(v38) + 4) = 0LL;
      *(_DWORD *)HIDWORD(v38) = v38;
      *(_BYTE *)(a1 + 2) = 0;
      AviPlayer_OpenAndPrepare((unsigned int *)a1);
      *(_BYTE *)(a1 + 1) = 0;
      return CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, (LPVOID)a1, 0, (LPDWORD)((char *)&a26 + 2));
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
char  AviPlayer_OpenAndPrepare(unsigned int *a1)
{
  int v2; // ecx
  __int64 v3; // rax
  unsigned int *v4; // ebx
  __int64 v5; // rax
  double v6; // st7
  int v7; // edx
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  __int64 v11; // rax
  _DWORD *v12; // ebx
  __int64 v13; // rax
  int v14; // ecx
  int v15; // esi
  int v16; // eax
  int v17; // edx
  int v18; // ecx
  signed int Frame; // esi
  int v20; // ecx
  int v21; // ecx
  int v22; // edx
  int v23; // edi
  int v24; // eax
  int v25; // edx
  int v26; // eax
  signed int *v27; // edi
  int v28; // eax
  int v29; // edx
  int v30; // [esp-14h] [ebp-4Ch]
  int v31; // [esp-10h] [ebp-48h]
  int v32; // [esp-Ch] [ebp-44h]
  double v33; // [esp+8h] [ebp-30h]
  signed int v34; // [esp+1Ch] [ebp-1Ch]
  __int64 v35; // [esp+20h] [ebp-18h]
  signed int v36; // [esp+28h] [ebp-10h] BYREF
  int v37; // [esp+2Ch] [ebp-Ch] BYREF
  int v38; // [esp+30h] [ebp-8h]
  unsigned int *v39; // [esp+34h] [ebp-4h]

  v39 = a1;
  if ( AVIFileGetStream(*(unsigned int *)((char *)a1 + 3), (char *)a1 + 215, 1935963489, 0) )
  {
    *(unsigned int *)((char *)v39 + 215) = 0;
    return 0;
  }
  else
  {
    AVIStreamReadFormat(*(unsigned int *)((char *)v39 + 215), 0, 0, &v37);
    v3 = j_Mem_Alloc(v2);
    *(_DWORD *)(HIDWORD(v3) + 363) = v3;
    v4 = v39;
    AVIStreamReadFormat(*(_DWORD *)(HIDWORD(v3) + 215), 0, *(_DWORD *)(HIDWORD(v3) + 363), &v37);
    v4 = (unsigned int *)((char *)v4 + 219);
    AVIStreamInfoA(*(unsigned int *)((char *)v39 + 215), v4, 140);
    v5 = j_Mem_Alloc(*(unsigned int *)((char *)v39 + 251));
    *(_QWORD *)(HIDWORD(v5) + 391) = (unsigned int)v5;
    *(_DWORD *)(HIDWORD(v5) + 399) = 0;
    v35 = *(unsigned int *)(HIDWORD(v5) + 31);
    v33 = (double)v4[6] * (double)v35;
    LODWORD(v35) = *(_DWORD *)(HIDWORD(v5) + 35);
    v6 = v33 / ((double)v4[5] * (double)v35);
    _CHP(v4[5], 0);
    *(_DWORD *)(v7 + 367) = (int)v6;
    v8 = (int)v39;
    v9 = *(unsigned int *)((char *)v39 + 367)
       * *(unsigned __int16 *)(*(unsigned int *)((char *)v39 + 363) + 12)
       * (3 * *(_DWORD *)(v7 + 159) / (int)(2 * *(unsigned int *)((char *)v39 + 155)) + v4[9]);
    *(unsigned int *)((char *)v39 + 371) = v9;
    v10 = 4 * v4[10];
    if ( v10 > v9 )
      *(_DWORD *)(v8 + 371) = v10;
    v11 = j_Mem_Alloc(v8);
    *(_DWORD *)(HIDWORD(v11) + 156) = v11;
    v12 = (unsigned int *)((char *)v39 + 391);
    v13 = j_Mem_Alloc(v39);
    *(_DWORD *)(v14 + 383) = 0;
    v38 = HIDWORD(v13);
    *(_DWORD *)(v14 + 379) = v13;
    while ( 1 )
    {
      v15 = AviPlayer_AudioSampleQueueCount((int)v12);
      AviPlayer_AudioBytesQueued((int)v39);
      v16 = AviPlayer_AudioBlockAlign((int)v39);
      if ( v17 / v16 * v15 / *(int *)((char *)v39 + 367) >= *(_DWORD *)(v38 + 36) )
        break;
      Frame = AviPlayer_DecodeNextFrame((int)v39);
      if ( Frame == -1 )
        break;
      v32 = *(_DWORD *)(v38 + 40);
      v31 = Frame + *(_DWORD *)(v18 + 375);
      AviPlayer_AudioSampleQueueBase(v18);
      LOWORD(v21) = *(_WORD *)(AviPlayer_AudioFormatPtr(v20) + 12);
      v30 = v22 / v21;
      v23 = AviPlayer_AudioSampleQueueCount((int)v12);
      AviPlayer_AudioBytesQueued((int)v39);
      v24 = AviPlayer_AudioBlockAlign((int)v39);
      AVIStreamRead(v24, v25 % v24, *(unsigned int *)((char *)v39 + 215), v23 * (v25 / v24), v30, v31, v32, &v36, 0);
      v34 = v36;
      v26 = v12[2];
      v12[2] = v26 + 1;
      v27 = (signed int *)(*v12 + 8 * v26);
      *v27 = Frame;
      v27[1] = v34;
    }
    v28 = CSS_StartStreamVoice((int)v39, 64, 0, 0);
    v29 = (int)v39;
    *(unsigned int *)((char *)v39 + 359) = v28;
    if ( v28 )
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
int  AviPlayer_FlushVideoFrameQueue(int a1)
{
  int v2; // ebx
  HANDLE *i; // esi
  int v4; // edx
  int result; // eax

  v2 = a1 + 391;
  for ( i = (HANDLE *)(a1 + 387); ; PulseEvent(*i) )
  {
    v4 = *(_DWORD *)(v2 + 4);
    if ( *(_DWORD *)(v2 + 8) == v4 )
      break;
    *(_DWORD *)(v2 + 4) = v4 + 1;
  }
  j_j__nfree_();
  *(_DWORD *)(a1 + 379) = 0;
  j_j__nfree_();
  *(_DWORD *)(a1 + 375) = 0;
  j_j__nfree_();
  result = *(_DWORD *)(a1 + 215);
  *(_DWORD *)(a1 + 363) = 0;
  if ( result )
  {
    result = AVIStreamRelease(result);
    *(_DWORD *)(a1 + 215) = 0;
  }
  return result;
}
// 4E97C2: using guessed type int __stdcall AVIStreamRelease(_DWORD);

//----- (00465DD0) --------------------------------------------------------
int  AviPlayer_CloseStreams(int a1)
{
  int v2; // ebp
  int result; // eax
  int v4; // ecx

  CAviDecompressor_RequestDecodeThreadStop(a1);
  ++*(_DWORD *)(a1 + 175);
  EnterCriticalSection((LPCRITICAL_SECTION)(a1 + 179));
  LeaveCriticalSection((LPCRITICAL_SECTION)(a1 + 179));
  --*(_DWORD *)(a1 + 175);
  while ( 1 )
  {
    v2 = *(_DWORD *)(a1 + 207);
    if ( *(_DWORD *)(a1 + 211) == v2 )
      break;
    *(_DWORD *)(a1 + 207) = v2 + 1;
    PulseEvent(*(HANDLE *)(a1 + 171));
  }
  AviPlayer_FlushVideoFrameQueue(a1);
  j_j__nfree_();
  *(_DWORD *)(a1 + 163) = 0;
  result = j_j__nfree_();
  v4 = *(_DWORD *)(a1 + 7);
  *(_DWORD *)(a1 + 151) = 0;
  if ( v4 )
  {
    AVIStreamEndStreaming(v4);
    result = AVIStreamRelease(*(_DWORD *)(a1 + 7));
    *(_DWORD *)(a1 + 7) = 0;
  }
  if ( *(_DWORD *)(a1 + 3) )
  {
    result = AVIFileRelease(*(_DWORD *)(a1 + 3));
    *(_DWORD *)(a1 + 3) = 0;
  }
  if ( *(_BYTE *)a1 )
  {
    result = AVIFileExit();
    *(_BYTE *)a1 = 0;
  }
  return result;
}
// 4E97B6: using guessed type int AVIFileExit(void);
// 4E97BC: using guessed type int __stdcall AVIStreamEndStreaming(_DWORD);
// 4E97C2: using guessed type int __stdcall AVIStreamRelease(_DWORD);
// 4E97C8: using guessed type int __stdcall AVIFileRelease(_DWORD);

//----- (00465EC0) --------------------------------------------------------
int  AviPlayer_GetBufferedAudioSample(int a1, int a2, _DWORD *a3, _DWORD *a4)
{
  int v7; // ebx
  int v8; // edx
  int v9; // eax
  int i; // edx

  v7 = *(_DWORD *)(a1 + 207);
  if ( *(_DWORD *)(a1 + 211) != v7 )
  {
    if ( v7 < a2 )
    {
      v8 = *(_DWORD *)(a1 + 211) - 1;
      if ( v8 >= a2 )
        v8 = a2;
      v9 = v8;
      for ( i = 12 * v8; v9 > *(_DWORD *)(a1 + 207) && *(_DWORD *)(i + *(_DWORD *)(a1 + 203)); i -= 12 )
        --v9;
      if ( v9 > *(_DWORD *)(a1 + 207) )
        *(_DWORD *)(a1 + 207) = v9;
    }
    *a4 = *(_DWORD *)(a1 + 207);
    goto LABEL_12;
  }
  *a4 = *(_DWORD *)(a1 + 211);
  if ( !WaitForSingleObject(*(HANDLE *)(a1 + 167), 0x3E8u) )
  {
LABEL_12:
    *a3 = *(_DWORD *)(*(_DWORD *)(a1 + 203) + 12 * *(_DWORD *)(a1 + 207));
    return *(_DWORD *)(a1 + 163) + *(_DWORD *)(*(_DWORD *)(a1 + 203) + 12 * *(_DWORD *)(a1 + 207) + 4);
  }
  return 0;
}

//----- (00465FB0) --------------------------------------------------------
unsigned int  AviPlayer_PopBufferedVideoFrame(int a1, void *a2)
{
  int v5; // edx
  _DWORD *v6; // eax
  unsigned int v7; // ebp

  if ( *(_DWORD *)(a1 + 399) == *(_DWORD *)(a1 + 395) )
    return 0;
  v5 = a1 + 391;
  v6 = (_DWORD *)(*(_DWORD *)(a1 + 391) + 8 * *(_DWORD *)(a1 + 395));
  v7 = v6[1];
  qmemcpy(a2, (const void *)(*v6 + *(_DWORD *)(a1 + 375)), v7);
  ++*(_DWORD *)(v5 + 4);
  PulseEvent(*(HANDLE *)(a1 + 387));
  return v7;
}

//----- (004660D0) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
char  AviPlayer_OpenVideoCodec(
        int a1,
        int a2,
        int *a3,
        int a4,
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
  int v21; // edx
  int v22; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ebx
  int v27; // esi
  unsigned int v28; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // [esp+0h] [ebp-120h]
  int v32; // [esp+0h] [ebp-120h]

  *(_DWORD *)((char *)&a20 + 2) = a1;
  *(_DWORD *)((char *)&a19 + 6) = a2;
  *(_DWORD *)((char *)&a17 + 6) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a18 + 2) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a18 + 6) = &g_AviOpenVideoCodec_EHFrame;
  *(_DWORD *)((char *)&a19 + 2) = 0;
  *(_DWORD *)(a1 + 4) = a4;
  if ( a3 && (*(unsigned __int16 *)(a4 + 14) > 8u || a3[2] >= 0) )
  {
    v21 = *(_DWORD *)((char *)&a20 + 2) + 8;
    qmemcpy((void *)(*(_DWORD *)((char *)&a20 + 2) + 8), a3, *a3);
    v22 = ICLocate(1667524982, *(_DWORD *)((char *)&a19 + 6), *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4), v21, 2);
    **(_DWORD **)((char *)&a20 + 2) = v22;
  }
  BYTE6(a20) = **(_DWORD **)((char *)&a20 + 2) != 0;
  if ( !**(_DWORD **)((char *)&a20 + 2) )
  {
    v24 = ICGetDisplayFormat(
            0,
            *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4),
            *(_DWORD *)((char *)&a20 + 2) + 8,
            0,
            0,
            0);
    **(_DWORD **)((char *)&a20 + 2) = v24;
  }
  if ( **(_DWORD **)((char *)&a20 + 2) )
  {
    v25 = *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4);
    v26 = *(_DWORD *)(v25 + 4);
    v27 = *(_DWORD *)((char *)&a20 + 2) + 8;
    v28 = abs32(*(_DWORD *)(v25 + 8));
    v29 = **(_DWORD **)((char *)&a20 + 2);
    v30 = *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4);
    *(_DWORD *)((char *)&a12 + 2) = 0;
    *(_DWORD *)((char *)&a12 + 6) = v30;
    *(_DWORD *)((char *)&a12 + 10) = 0;
    *(_DWORD *)((char *)&a15 + 6) = 0;
    *(_DWORD *)((char *)&a17 + 2) = v28;
    *(_DWORD *)((char *)&a15 + 2) = v28;
    *(_DWORD *)((char *)&a16 + 2) = 0;
    *(_DWORD *)((char *)&a16 + 6) = v26;
    *(_DWORD *)((char *)&a12 + 14) = *(_DWORD *)((char *)&a20 + 2) + 8;
    *(_DWORD *)((char *)&a13 + 2) = 0;
    *(_DWORD *)((char *)&a13 + 6) = 0;
    *(_DWORD *)((char *)&a14 + 2) = 0;
    *(_DWORD *)((char *)&a14 + 6) = v26;
    if ( ICSendMessage(v29, 16444, (char *)&a12 + 2, 52, v31) )
    {
      if ( ICSendMessage(
             **(_DWORD **)((char *)&a20 + 2),
             16396,
             *(_DWORD *)(*(_DWORD *)((char *)&a20 + 2) + 4),
             v27,
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
_DWORD * CAviDecompressor_CloseCodecHandle(_DWORD *result, int a2, int a3)
{
  _DWORD *v3; // ebx

  v3 = result;
  if ( *result )
  {
    if ( *((_BYTE *)result + 1508) )
    {
      ICSendMessage(*result, 16447, 0, 0, a3);
      result = (_DWORD *)ICClose(*v3);
      *v3 = 0;
    }
    else
    {
      ICSendMessage(*result, 16398, 0, 0, a2);
      result = (_DWORD *)ICClose(*v3);
      *v3 = 0;
    }
  }
  return result;
}
// 4E97A4: using guessed type int __cdecl ICClose(_DWORD);
// 4E980A: using guessed type int __stdcall ICSendMessage(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD);

//----- (00466310) --------------------------------------------------------
void  CAviDecompressor_RenderLoop(int a1)
{
  DWORD v2; // esi
  double v3; // st7
  int v4; // edx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-44h]
  tagRECT *v6; // [esp+4h] [ebp-40h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v6 = &j____wcpp_4_fs_handler_rtn_;
  while ( *(_BYTE *)(a1 + 2191) )
  {
    if ( AviPlayer_UpdateTargetFrameFromClock(a1) && (*(_DWORD *)(a1 + 211) < *(_DWORD *)(a1 + 43) || AviPlayer_QueueBacklogCount(a1 + 203)) )
    {
      v2 = 0;
      if ( AviPlayer_CatchUpToTargetFrame(a1) )
      {
        timeGetTime();
        v3 = (double)*(unsigned int *)(a1 + 31)
           * ((double)(*(_DWORD *)(a1 + 2021) + 1)
            * g_CAviDecompressor_MillisecondsPerSecond)
           / (double)*(unsigned int *)(a1 + 35);
        _CHP(ExceptionList, v6);
        if ( (int)v3 - v4 + 1 > 0 )
          v2 = (int)v3 - v4 + 1;
      }
      Sleep(v2);
      *(_DWORD *)(a1 + 2038) += v2;
    }
    else
    {
      CAviDecompressor_RequestRenderStop(a1);
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
struct _EXCEPTION_REGISTRATION_RECORD * CAviDecompressor_BeginPlayback(int a1)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  AviException_RebuildClipperOnSurfaceLoss(a1, (int)&j____wcpp_4_fs_handler_rtn_, (int)&g_AviBeginPlayback_EHFrame, 0);
  *(_DWORD *)(a1 + 2183) = 0;
  *(_DWORD *)(a1 + 2034) = 0;
  *(_DWORD *)(a1 + 2038) = 0;
  AviPlayer_CatchUpToTargetFrame(a1);
  *(_BYTE *)(a1 + 2) = 1;
  *(_DWORD *)(a1 + 2187) = timeGetTime();
  CSS_ResumeStream(*(_DWORD *)(a1 + 359));
  *(_BYTE *)(a1 + 2191) = 1;
  ResumeThread(*(HANDLE *)(a1 + 2192));
  return ExceptionList;
}

//----- (00466580) --------------------------------------------------------
BOOL  CAviDecompressor_RequestRenderStop(int a1)
{
  *(_BYTE *)(a1 + 2191) = 0;
  return SetEvent(*(HANDLE *)(a1 + 2196));
}

//----- (004665A0) --------------------------------------------------------
_DWORD * AviPlayer_ShutdownDecodeState(int a1)
{
  int v2; // esi
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int *v10; // eax
  int *v11; // [esp-4h] [ebp-100h]
  int *v12; // [esp-4h] [ebp-100h]

  if ( *(_BYTE *)(a1 + 2191) )
  {
    CAviDecompressor_RequestRenderStop(a1);
    WaitForSingleObject(*(HANDLE *)(a1 + 2228), 0x7D0u);
    ++*(_DWORD *)(a1 + 2200);
    EnterCriticalSection((LPCRITICAL_SECTION)(a1 + 2204));
    LeaveCriticalSection((LPCRITICAL_SECTION)(a1 + 2204));
    --*(_DWORD *)(a1 + 2200);
  }
  else
  {
    ResumeThread(*(HANDLE *)(a1 + 2192));
  }
  CAviDecompressor_RequestDecodeThreadStop(a1);
  AviPlayer_CloseStreams(a1);
  v2 = a1;
  if ( *(_BYTE *)(a1 + 1968) )
  {
    v3 = *(_DWORD *)(a1 + 1964);
    if ( v3 )
    {
      v4 = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(*(_DWORD *)v3 + 132))(
             v3,
             a1 + 2095,
             *(_DWORD *)(a1 + 1956),
             a1 + 2063,
             512,
             0);
      if ( v4 )
      {
        if ( v4 != -2005532222
          || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 96))(*(_DWORD *)(a1 + 1964)) != -2005532222
           || (v11 = *(int **)(a1 + 1964), v2 = *v11, !(*(int (__stdcall **)(int *))(*v11 + 108))(v11)))
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 96))(*(_DWORD *)(a1 + 1956)) != -2005532222
           || !(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 108))(*(_DWORD *)(a1 + 1956)))
          && (v10 = *(int **)(a1 + 1964),
              v2 = *v10,
              (*(int (__stdcall **)(int *, int, _DWORD, int, int, _DWORD))(*v10 + 132))(
                v10,
                a1 + 2095,
                *(_DWORD *)(a1 + 1956),
                a1 + 2063,
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
  *(_DWORD *)(a1 + 2179) = 0;
  j_j__nfree_();
  v5 = *(_DWORD *)(a1 + 1952);
  *(_DWORD *)(a1 + 2058) = 0;
  if ( v5 && *(_DWORD *)(a1 + 1956) )
  {
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 8))(*(_DWORD *)(a1 + 1956));
    *(_DWORD *)(a1 + 1956) = 0;
    *(_DWORD *)(a1 + 1952) = 0;
  }
  else
  {
    *(_DWORD *)(a1 + 1956) = 0;
    *(_DWORD *)(a1 + 1952) = 0;
  }
  v6 = *(_DWORD *)(a1 + 1964);
  if ( v6 )
  {
    v2 = *(_DWORD *)v6;
    (*(void (__stdcall **)(int))(*(_DWORD *)v6 + 8))(v6);
    v7 = *(_DWORD *)(a1 + 1960);
    *(_DWORD *)(a1 + 1964) = 0;
    if ( v7 )
      (*(void (__stdcall **)(int))(*(_DWORD *)v7 + 8))(v7);
    *(_DWORD *)(a1 + 1960) = 0;
  }
  else
  {
    *(_DWORD *)(a1 + 1960) = 0;
  }
  v8 = *(_DWORD *)(a1 + 2017);
  if ( v8 && *(_DWORD *)(a1 + 2013) )
  {
    (*(void (__stdcall **)(int, _DWORD))(*(_DWORD *)v8 + 152))(v8, 0);
    (*(void (__stdcall **)(int))(*(_DWORD *)v8 + 8))(v8);
    v12 = (int *)(uintptr_t)*(unsigned int *)(a1 + 2013);
    v2 = *v12;
    (*(void (__stdcall **)(int *))(*v12 + 8))(v12);
    *(_DWORD *)(a1 + 2013) = 0;
    *(_DWORD *)(a1 + 2017) = 0;
  }
  else
  {
    *(_DWORD *)(a1 + 2013) = 0;
    *(_DWORD *)(a1 + 2017) = 0;
  }
  return CAviDecompressor_CloseCodecHandle((_DWORD *)(a1 + 415), v8, v2);
}
// 466720: variable 'v8' is possibly undefined

//----- (00466870) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
int  AviPlayer_BlitFrameToSurface(
        _DWORD *a1,
        int a2,
        int a3,
        int *a4,
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
  _DWORD *v33; // eax
  int v34; // eax
  int v35; // eax
  int result; // eax
  int v37; // ecx
  int v38; // ecx
  int v39; // eax
  const BITMAPINFO *v40; // eax
  _DWORD v41[4]; // [esp+82h] [ebp-332h] BYREF
  int v42; // [esp+92h] [ebp-322h]
  char *v43; // [esp+A6h] [ebp-30Eh]
  int (**v44)(); // [esp+152h] [ebp-262h]
  int (**v45)(); // [esp+1BAh] [ebp-1FAh]
  int v46; // [esp+222h] [ebp-192h]
  int v47; // [esp+28Ah] [ebp-12Ah]

  *(_DWORD *)((char *)&a31 + 6) = a3;
  v33 = a1 + 481;
  if ( v33[5] || v33[4] )
  {
    v41[0] = 108;
    v34 = (*(int (__stdcall **)(int, int *, _DWORD *, int, _DWORD))(*(_DWORD *)a2 + 100))(a2, a4, v41, 1, 0);
    if ( !v34
      || v34 == -2005532222
      && ((*(int (__stdcall **)(int))(*(_DWORD *)a2 + 108))(a2)
       || !(*(int (__stdcall **)(int, int *, _DWORD *, int, _DWORD))(*(_DWORD *)a2 + 100))(a2, a4, v41, 1, 0)) )
    {
      if ( (int)a1[484] < 0 )
        v35 = -v42;
      else
        v35 = v42;
      a1[484] = v35;
      CAviDecompressor_BlitRows(a1 + 481, v43, *(char **)((char *)&a31 + 6));
      result = (*(int (__stdcall **)(int, char *))(*(_DWORD *)a2 + 128))(a2, v43);
      if ( result )
      {
        if ( result != -2005532222
          || (result = (*(int (__stdcall **)(int))(*(_DWORD *)a2 + 108))(a2)) == 0
          && (result = (*(int (__stdcall **)(int, char *))(*(_DWORD *)a2 + 128))(a2, v43)) != 0 )
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
    v39 = (*(int (__stdcall **)(int, char *))(*(_DWORD *)a2 + 68))(a2, (char *)&a31 + 2);
    if ( !v39
      || v39 == -2005532222
      && ((*(int (__stdcall **)(int))(*(_DWORD *)a2 + 108))(a2)
       || !(*(int (__stdcall **)(int, char *))(*(_DWORD *)a2 + 68))(a2, (char *)&a31 + 2)) )
    {
      if ( *(_DWORD *)((char *)a1 + 415) )
        v40 = (const BITMAPINFO *)((char *)a1 + 423);
      else
        v40 = *(const BITMAPINFO **)((char *)a1 + 151);
      StretchDIBits(
        *(HDC *)((char *)&a31 + 2),
        *a4,
        a4[1],
        a4[2] - *a4,
        a4[3] - a4[1],
        0,
        0,
        *(_DWORD *)(*(_DWORD *)((char *)a1 + 151) + 4),
        abs32(*(_DWORD *)(*(_DWORD *)((char *)a1 + 151) + 8)),
        *(const void **)((char *)&a31 + 6),
        v40,
        0,
        0xCC0020u);
      result = (*(int (__stdcall **)(int, _DWORD))(*(_DWORD *)a2 + 104))(a2, *(_DWORD *)((char *)&a31 + 2));
      if ( result )
      {
        if ( result != -2005532222
          || (result = (*(int (__stdcall **)(int))(*(_DWORD *)a2 + 108))(a2)) == 0
          && (result = (*(int (__stdcall **)(int, _DWORD))(*(_DWORD *)a2 + 104))(a2, *(_DWORD *)((char *)&a31 + 2))) != 0 )
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
bool  AviPlayer_UpdateTargetFrameFromClock(int a1)
{
  DWORD Time; // eax
  double v3; // st7
  double v4; // st7
  __int64 v6; // [esp+8h] [ebp-18h]

  Time = timeGetTime();
  v6 = *(unsigned int *)(a1 + 35);
  v3 = ((double)Time - (double)*(int *)(a1 + 2187)) * (double)v6;
  LODWORD(v6) = *(_DWORD *)(a1 + 31);
  v4 = v3 / ((double)v6 * g_AviPlayer_MillisecondsPerSecond);
  _CHP(Time, 0);
  *(_DWORD *)(a1 + 2183) = (int)v4;
  return *(_DWORD *)(a1 + 43) > *(_DWORD *)(a1 + 2183);
}
// 501370: using guessed type float flt_501370;

//----- (00466C60) --------------------------------------------------------
char  AviPlayer_CatchUpToTargetFrame(int a1)
{
  int v2; // ecx
  HANDLE *v3; // edx
  int v4; // eax
  unsigned __int8 v5; // dl
  _DWORD *v6; // ecx
  int v7; // ebx
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int v11; // esi
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  int *v17; // ecx
  int v18; // ebx
  int v21; // esi
  int v22; // eax
  int v23; // ebx
  int v24; // ecx
  int v25; // edx
  int v26; // eax
  int v27; // ebx
  int v28; // edx
  int v29; // eax
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int *v33; // edx
  int v34; // eax
  int v35; // esi
  int v36; // eax
  int v37; // ebx
  int v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // ebx
  int v42; // edx
  int v43; // eax
  int v44; // ecx
  int v45; // edx
  int v46; // eax
  int *v47; // edx
  int v48; // eax
  int v49; // edx
  HANDLE *v50; // ecx
  int v51; // eax
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
  _DWORD v82[9]; // [esp+82h] [ebp-71Ah] BYREF
  int v83; // [esp+A6h] [ebp-6F6h]
  _DWORD v84[9]; // [esp+EEh] [ebp-6AEh] BYREF
  int v85; // [esp+112h] [ebp-68Ah]
  int (**v86)(); // [esp+1BEh] [ebp-5DEh]
  int (**v87)(); // [esp+226h] [ebp-576h]
  int (**v88)(); // [esp+28Eh] [ebp-50Eh]
  int (**v89)(); // [esp+3C6h] [ebp-3D6h]
  int (**v90)(); // [esp+42Eh] [ebp-36Eh]
  int v91; // [esp+7D2h] [ebp+36h]
  int v92; // [esp+7DAh] [ebp+3Eh]
  int v93; // [esp+7DEh] [ebp+42h]
  int v94; // [esp+7E2h] [ebp+46h]
  int v95; // [esp+7EAh] [ebp+4Eh]
  int v96; // [esp+7EEh] [ebp+52h]
  int v97; // [esp+7F2h] [ebp+56h]
  int v98; // [esp+7F6h] [ebp+5Ah]
  int v99; // [esp+7F6h] [ebp+5Ah]
  int v100; // [esp+7F6h] [ebp+5Ah]
  int v101; // [esp+7FAh] [ebp+5Eh]
  int v102; // [esp+7FEh] [ebp+62h]
  int v103; // [esp+802h] [ebp+66h]
  int v104; // [esp+806h] [ebp+6Ah]
  int v105; // [esp+80Eh] [ebp+72h]
  int v106; // [esp+81Ah] [ebp+7Eh]

  if ( *(_DWORD *)(a1 + 2183) != *(_DWORD *)(a1 + 2021) )
  {
    v105 = a1 + 203;
    if ( *(char *)(a1 + 2033) <= 0 )
    {
      v103 = a1 + 1985;
      ++*(_DWORD *)(a1 + 1985);
      EnterCriticalSection((LPCRITICAL_SECTION)(a1 + 1989));
      if ( *(_DWORD *)(a1 + 2034) )
      {
        v49 = v105;
        do
        {
          if ( *(int *)(a1 + 2034) > 0 )
          {
            AviPlayer_IncrementFramesRenderedCount(v49);
            AviPlayer_PulseEventHandle(v50);
            --*(_DWORD *)(a1 + 2034);
          }
        }
        while ( *(_DWORD *)(a1 + 2034) );
      }
      v51 = AviPlayer_GetBufferedAudioSample(a1, *(_DWORD *)(a1 + 2183), (_DWORD *)(a1 + 2029), (_DWORD *)(a1 + 2021));
      *(_DWORD *)(a1 + 2025) = v51;
      if ( v51 )
        ++*(_DWORD *)(a1 + 2034);
      v18 = v103;
    }
    else
    {
      if ( *(_DWORD *)(a1 + 2034) )
      {
        v2 = a1 + 203;
        do
        {
          if ( *(int *)(a1 + 2034) > 0 )
          {
            AviPlayer_IncrementFramesRenderedCount(v2);
            AviPlayer_PulseEventHandle(v3);
            --*(_DWORD *)(a1 + 2034);
          }
        }
        while ( *(_DWORD *)(a1 + 2034) );
      }
      v4 = AviPlayer_GetBufferedAudioSample(a1, *(_DWORD *)(a1 + 2183), (_DWORD *)(a1 + 2029), (_DWORD *)(a1 + 2021));
      *(_DWORD *)(a1 + 2025) = v4;
      if ( !v4 )
        return 0;
      ++*(_DWORD *)(a1 + 2034);
      ++*(_DWORD *)(a1 + 1985);
      EnterCriticalSection((LPCRITICAL_SECTION)(a1 + 1989));
      v5 = *(_BYTE *)(a1 + 2033);
      v6 = (_DWORD *)(a1 + 415);
      if ( v5 >= 2u )
      {
        if ( v5 <= 2u )
        {
          if ( *v6 )
          {
            v21 = *(_DWORD *)(a1 + 2017);
            v84[0] = 108;
            v22 = (*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)v21 + 100))(v21, 0, v84, 33, 0);
            if ( !v22
              || v22 == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)v21 + 108))(v21)
               || !(*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)v21 + 100))(v21, 0, v84, 33, 0)) )
            {
              CAviDecompressor_GetVideoFormat(a1);
              v91 = *(_DWORD *)(CAviDecompressor_GetVideoFormat(a1) + 4);
              v92 = v85;
              v93 = *(_DWORD *)(a1 + 2025);
              v101 = *(_DWORD *)(a1 + 2029);
              v23 = v84[4] / ((*(_DWORD *)(a1 + 2123) + 7) >> 3);
              *(_DWORD *)(AviPlayer_StreamBitmapInfoPtr(a1 + 415) + 4) = v23;
              v99 = v24 * v23;
              v26 = AviPlayer_StreamBitmapInfoPtr(v25);
              v27 = Mem_BitsToBytesCeil(*(unsigned __int16 *)(v26 + 14)) * v99;
              v29 = AviPlayer_StreamBitmapInfoPtr(v28);
              v53 = v30;
              *(_DWORD *)(v29 + 20) = v27;
              v32 = AviPlayer_StreamBitmapInfoPtr(v31);
              if ( AviPlayer_SendICDrawBegin(
                     *v33,
                     v101,
                     v33[1],
                     v93,
                     0,
                     0,
                     *(_DWORD *)(v33[1] + 4),
                     *(_DWORD *)(v33[1] + 8),
                     v32,
                     v92,
                     0,
                     0,
                     v91,
                     v53) < 0 )
              {
                ExcString_Ctor();
                AviException_CtorForDrawFailure();
                CRT_ThrowExcStringException();
              }
              v34 = (*(int (__stdcall **)(int, int))(*(_DWORD *)v21 + 128))(v21, v85);
              if ( v34
                && (v34 != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)v21 + 108))(v21)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)v21 + 128))(v21, v85)) )
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
              (_DWORD *)a1,
              *(_DWORD *)(a1 + 2017),
              *(_DWORD *)(a1 + 2025),
              (int *)(a1 + 2095),
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
        else if ( v5 == 3 )
        {
          if ( *v6 )
          {
            v35 = *(_DWORD *)(a1 + 1964);
            v82[0] = 108;
            v36 = (*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)v35 + 100))(v35, 0, v82, 33, 0);
            if ( !v36
              || v36 == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)v35 + 108))(v35)
               || !(*(int (__stdcall **)(int, _DWORD, _DWORD *, int, _DWORD))(*(_DWORD *)v35 + 100))(v35, 0, v82, 33, 0)) )
            {
              CAviDecompressor_GetVideoFormat(a1);
              v94 = *(_DWORD *)(CAviDecompressor_GetVideoFormat(a1) + 4);
              v95 = v83;
              v96 = *(_DWORD *)(a1 + 2025);
              v97 = *(_DWORD *)(a1 + 2029);
              v37 = v82[4] / ((*(_DWORD *)(a1 + 2123) + 7) >> 3);
              *(_DWORD *)(AviPlayer_StreamBitmapInfoPtr(a1 + 415) + 4) = v37;
              v100 = v38 * v37;
              v40 = AviPlayer_StreamBitmapInfoPtr(v39);
              v41 = Mem_BitsToBytesCeil(*(unsigned __int16 *)(v40 + 14)) * v100;
              v43 = AviPlayer_StreamBitmapInfoPtr(v42);
              v54 = v44;
              *(_DWORD *)(v43 + 20) = v41;
              v46 = AviPlayer_StreamBitmapInfoPtr(v45);
              if ( AviPlayer_SendICDrawBegin(
                     *v47,
                     v97,
                     v47[1],
                     v96,
                     0,
                     0,
                     *(_DWORD *)(v47[1] + 4),
                     *(_DWORD *)(v47[1] + 8),
                     v46,
                     v95,
                     0,
                     0,
                     v94,
                     v54) < 0 )
              {
                ExcString_Ctor();
                AviException_CtorForDrawFailure();
                CRT_ThrowExcStringException();
              }
              v48 = (*(int (__stdcall **)(int, int))(*(_DWORD *)v35 + 128))(v35, v83);
              if ( v48
                && (v48 != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)v35 + 108))(v35)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)v35 + 128))(v35, v83)) )
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
              (_DWORD *)a1,
              *(_DWORD *)(a1 + 1964),
              *(_DWORD *)(a1 + 2025),
              (int *)(a1 + 2095),
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
      else if ( v5 == 1 )
      {
        v104 = *(_DWORD *)(a1 + 2179);
        v102 = *(_DWORD *)(a1 + 2025);
        v106 = *(_DWORD *)(a1 + 2029);
        if ( *(_BYTE *)(a1 + 1923) )
        {
          v7 = *(_DWORD *)(a1 + 427);
          *(_DWORD *)(AviPlayer_StreamBitmapInfoPtr(a1 + 415) + 4) = v7;
          v98 = v7 * v8;
          v10 = AviPlayer_StreamBitmapInfoPtr(v9);
          v11 = Mem_BitsToBytesCeil(*(unsigned __int16 *)(v10 + 14)) * v98;
          v13 = AviPlayer_StreamBitmapInfoPtr(v12);
          v52 = v14;
          *(_DWORD *)(v13 + 20) = v11;
          v16 = AviPlayer_StreamBitmapInfoPtr(v15);
          if ( AviPlayer_SendICDrawBegin(
                 *v17,
                 v106,
                 v17[1],
                 v102,
                 0,
                 0,
                 *(_DWORD *)(v17[1] + 4),
                 *(_DWORD *)(v17[1] + 8),
                 v16,
                 v104,
                 0,
                 0,
                 v7,
                 v52) < 0 )
          {
            ExcString_Ctor();
            AviException_CtorForDrawFailure();
            CRT_ThrowExcStringException();
          }
        }
        else if ( ICDecompress(
                    *(_DWORD *)(a1 + 415),
                    *(_DWORD *)(a1 + 2029),
                    *(_DWORD *)(a1 + 419),
                    v102,
                    a1 + 423,
                    v104) < 0 )
        {
          ExcString_Ctor();
          ExcString_Ctor();
          v88 = g_AviException_VTable;
          CRT_ThrowExcStringException();
        }
      }
      if ( *(int *)(a1 + 2034) > 0 )
      {
        ++*(_DWORD *)(a1 + 207);
        PulseEvent(*(HANDLE *)(a1 + 171));
        --*(_DWORD *)(a1 + 2034);
      }
      v18 = a1 + 1985;
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(v18 + 4));
    --*(_DWORD *)v18;
    SetEvent(*(HANDLE *)(a1 + 2196));
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
int  AviPlayer_Flip(int a1)
{
  int v2; // edx
  int v3; // edi
  int v4; // ebx
  int *v5; // ebp
  int v6; // eax
  int v7; // ecx
  int v8; // ebp
  int v9; // ebp
  int v10; // eax
  int v11; // edx
  int v12; // eax
  _DWORD *v13; // ebx
  int result; // eax
  int v15; // ebx
  int v16; // eax
  int v17; // edx
  int v18; // ebx
  int v19; // edi
  int v20; // eax
  int v21; // ebp
  int v22; // edx
  int v23; // ecx
  int v24; // eax
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  int v31; // eax
  int v32; // edx
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // eax
  int v37; // ecx
  int v38; // eax
  int v39; // eax
  int v40; // [esp+10h] [ebp-51Ch]
  int v41; // [esp+10h] [ebp-51Ch]
  int v42; // [esp+14h] [ebp-518h]
  int v43; // [esp+14h] [ebp-518h]
  int v44; // [esp+18h] [ebp-514h] BYREF
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
  __int64 v70[2]; // [esp+80h] [ebp-4ACh] BYREF
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
  int v81; // [esp+500h] [ebp-2Ch]
  int v82; // [esp+504h] [ebp-28h]
  int v83; // [esp+508h] [ebp-24h]
  int v84; // [esp+50Ch] [ebp-20h]
  char v85; // [esp+510h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v78 = &j____wcpp_4_fs_handler_rtn_;
  v79 = &g_AviPlayerFlip_EHFrame;
  v80 = 0;
  v85 = *(_BYTE *)(a1 + 2033);
  v81 = a1 + 1985;
  ++*(_DWORD *)(a1 + 1985);
  EnterCriticalSection((LPCRITICAL_SECTION)(a1 + 1989));
  v80 = 1;
  if ( (unsigned __int8)v85 > 3u )
  {
LABEL_19:
    v80 = 0;
    v13 = (_DWORD *)v81;
    LeaveCriticalSection((LPCRITICAL_SECTION)(v81 + 4));
    result = (*v13)--;
    if ( (unsigned __int8)v85 >= 2u )
    {
      if ( (unsigned __int8)v85 > 2u )
      {
        if ( v85 != 3 )
          return result;
      }
      else
      {
        if ( !*(_BYTE *)(a1 + 1968)
          || !*(_DWORD *)(a1 + 1964)
          || (v15 = *(_DWORD *)(a1 + 2087) - *(_DWORD *)(a1 + 2079),
              v16 = 1000 * (*(_DWORD *)(a1 + 2071) - *(_DWORD *)(a1 + 2063)) / v15,
              v17 = 1000 * (*(_DWORD *)(a1 + 2071) - *(_DWORD *)(a1 + 2063)) % v15,
              v16 < *(_DWORD *)(a1 + 2143))
          || v16 > *(_DWORD *)(a1 + 2147) )
        {
          if ( !*(_DWORD *)(a1 + 1964) )
            return AviPlayer_BltFrameToPrimarySurface(a1, *(_DWORD *)(a1 + 2017));
          v38 = *(_DWORD *)(a1 + 2171);
          LOBYTE(v38) = v38 | 2;
          v39 = *(_DWORD *)(a1 + 2175) | v38;
          v17 = v39 & *(_DWORD *)(a1 + 2119);
          if ( v17 != v39 )
            return AviPlayer_BltFrameToPrimarySurface(a1, *(_DWORD *)(a1 + 2017));
        }
        result = AviPlayer_BltFastOverlayFromBackBuffer(a1, v17);
      }
      if ( !*(_BYTE *)(a1 + 1968) || !*(_DWORD *)(a1 + 1964) )
        return AviPlayer_BltFrameToPrimarySurface(a1, *(_DWORD *)(a1 + 1964));
    }
  }
  else
  {
    switch ( v85 )
    {
      case 0:
        if ( !*(_DWORD *)(a1 + 2025) )
          goto LABEL_86;
        if ( *(_DWORD *)(a1 + 415) )
        {
          v2 = a1;
          if ( (!*(_BYTE *)(a1 + 2052) || AviPlayer_TestActiveModeFlag(a1))
            && (*(_BYTE *)(a1 + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(a1))
            && (AviPlayer_HasValidRateParams(a1) && AviPlayer_IsPlaybackRateInRange(a1) || *(_DWORD *)(a1 + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(a1)) )
          {
            v3 = *(_DWORD *)(v2 + 1964);
            v4 = v2;
            v5 = (int *)(v2 + 2095);
            v44 = 108;
            v6 = (*(int (__stdcall **)(int, int, int *, int, _DWORD))(*(_DWORD *)v3 + 100))(v3, v2 + 2095, &v44, 33, 0);
            if ( !v6
              || v6 == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)v3 + 108))(v3)
               || !(*(int (__stdcall **)(int, int *, int *, int, _DWORD))(*(_DWORD *)v3 + 100))(v3, v5, &v44, 33, 0)) )
            {
              v83 = v5[3] - v5[1];
              v7 = *v5;
              v8 = v5[2];
              v84 = v53;
              v42 = *(_DWORD *)(v4 + 2029);
              v9 = v8 - v7;
              v40 = *(_DWORD *)(v4 + 2025);
              v10 = Mem_BitsToBytesCeil(*(_DWORD *)(v4 + 2123));
              AviPlayer_UpdateStreamRectAndSendICDrawBegin((int *)(v4 + 415), v84, v83, v9, v11 / v10, v40, v42);
              v12 = (*(int (__stdcall **)(int, int))(*(_DWORD *)v3 + 128))(v3, v53);
              if ( v12
                && (v12 != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)v3 + 108))(v3)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)v3 + 128))(v3, v53)) )
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
            v85 = 3;
          }
          else
          {
            v18 = v2;
            v19 = *(_DWORD *)(v2 + 2017);
            HIDWORD(v70[0]) = 108;
            v20 = (*(int (__stdcall **)(int, _DWORD, char *, int, _DWORD))(*(_DWORD *)v19 + 100))(
                    v19,
                    0,
                    (char *)v70 + 4,
                    33,
                    0);
            if ( !v20
              || v20 == -2005532222
              && ((*(int (__stdcall **)(int))(*(_DWORD *)v19 + 108))(v19)
               || !(*(int (__stdcall **)(int, _DWORD, char *, int, _DWORD))(*(_DWORD *)v19 + 100))(
                     v19,
                     0,
                     (char *)v70 + 4,
                     33,
                     0)) )
            {
              AviPlayer_BitmapHeightAbs(v18);
              v21 = AviPlayer_BitmapWidth(v18);
              v82 = v71;
              v43 = *(_DWORD *)(v18 + 2029);
              v41 = *(_DWORD *)(v18 + 2025);
              v83 = Mem_BitsToBytesCeil(*(_DWORD *)(v18 + 2123));
              AviPlayer_UpdateStreamRectAndSendICDrawBegin((int *)(v18 + 415), v82, v23, v21, v22 / v83, v41, v43);
              v24 = (*(int (__stdcall **)(int, int))(*(_DWORD *)v19 + 128))(v19, v71);
              if ( v24
                && (v24 != -2005532222
                 || !(*(int (__stdcall **)(int))(*(_DWORD *)v19 + 108))(v19)
                 && (*(int (__stdcall **)(int, int))(*(_DWORD *)v19 + 128))(v19, v71)) )
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
            v85 = 2;
          }
        }
        else
        {
          v28 = *(_DWORD *)(a1 + 2025);
          if ( (!*(_BYTE *)(a1 + 2052) || AviPlayer_TestActiveModeFlag(a1))
            && (*(_BYTE *)(a1 + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(a1))
            && (AviPlayer_HasValidRateParams(a1) && AviPlayer_IsPlaybackRateInRange(a1) || *(_DWORD *)(a1 + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(a1)) )
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)a1,
              *(_DWORD *)(a1 + 1964),
              v28,
              (int *)(a1 + 2095),
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
              v70[0]);
            v85 = 3;
          }
          else
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)a1,
              *(_DWORD *)(a1 + 2017),
              v28,
              (int *)(a1 + 2095),
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
              v70[0]);
            v85 = 2;
          }
        }
        if ( *(int *)(a1 + 2034) > 0 )
        {
          ++*(_DWORD *)(a1 + 207);
          PulseEvent(*(HANDLE *)(a1 + 171));
          --*(_DWORD *)(a1 + 2034);
        }
        goto LABEL_19;
      case 1:
        v29 = *(_DWORD *)(a1 + 2179);
        if ( (!*(_BYTE *)(a1 + 2052) || AviPlayer_TestActiveModeFlag(a1))
          && (*(_BYTE *)(a1 + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(a1))
          && (AviPlayer_HasValidRateParams(a1) && AviPlayer_IsPlaybackRateInRange(a1) || *(_DWORD *)(a1 + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(a1)) )
        {
          AviPlayer_BlitFrameToSurface(
            (_DWORD *)a1,
            *(_DWORD *)(a1 + 1964),
            v29,
            (int *)(a1 + 2095),
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
            v70[0]);
          v85 = 3;
        }
        else
        {
          AviPlayer_BlitFrameToSurface(
            (_DWORD *)a1,
            *(_DWORD *)(a1 + 2017),
            v29,
            (int *)(a1 + 2095),
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
            v70[0]);
          v85 = 2;
        }
        goto LABEL_19;
      case 2:
        if ( *(_BYTE *)(a1 + 1968)
          && *(_DWORD *)(a1 + 1964)
          && (v30 = *(_DWORD *)(a1 + 2087) - *(_DWORD *)(a1 + 2079),
              v31 = 1000 * (*(_DWORD *)(a1 + 2071) - *(_DWORD *)(a1 + 2063)) / v30,
              v32 = 1000 * (*(_DWORD *)(a1 + 2071) - *(_DWORD *)(a1 + 2063)) % v30,
              v31 >= *(_DWORD *)(a1 + 2143))
          && v31 <= *(_DWORD *)(a1 + 2147)
          || *(_DWORD *)(a1 + 1964)
          && (v33 = *(_DWORD *)(a1 + 2171),
              LOBYTE(v33) = v33 | 2,
              v34 = *(_DWORD *)(a1 + 2175) | v33,
              v32 = v34 & *(_DWORD *)(a1 + 2119),
              v32 == v34) )
        {
          AviPlayer_BltFastOverlayFromBackBuffer(a1, v32);
          v85 = 3;
          goto LABEL_19;
        }
        AviPlayer_BltFrameToPrimarySurface(a1, *(_DWORD *)(a1 + 2017));
        LeaveCriticalSection((LPCRITICAL_SECTION)(v81 + 4));
        return (*(_DWORD *)v81)--;
      case 3:
        if ( !*(_BYTE *)(a1 + 1968) || (v35 = *(_DWORD *)(a1 + 1964)) == 0 )
        {
          AviPlayer_BltFrameToPrimarySurface(a1, *(_DWORD *)(a1 + 1964));
LABEL_86:
          LeaveCriticalSection((LPCRITICAL_SECTION)(v81 + 4));
          return (*(_DWORD *)v81)--;
        }
        if ( !*(_BYTE *)(a1 + 2051) )
          goto LABEL_86;
        v36 = (*(int (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v35 + 44))(v35, 0, 0);
        if ( !v36
          || v36 == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 108))(*(_DWORD *)(a1 + 1964))
           || !(*(int (__stdcall **)(_DWORD, _DWORD, _DWORD))(**(_DWORD **)(a1 + 1964) + 44))(
                 *(_DWORD *)(a1 + 1964),
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
int  AviException_RebuildClipperOnSurfaceLoss(int result, int a2, int a3, int a4)
{
  _DWORD **v4; // ebx
  int v5; // edx
  int v6; // eax
  int v7; // esi
  __int64 v8; // rax
  int v9; // eax
  __int64 v10; // rax
  int v11; // ecx

  v4 = (_DWORD **)result;
  v5 = *(_DWORD *)(result + 2151);
  if ( v5 )
  {
    result = (*(int (**)(void))(*(_DWORD *)v5 + 4))();
    if ( result )
    {
      v9 = (*(int (__stdcall **)(int, int, int))(**(_DWORD **)((char *)v4 + 2151) + 4))(a4, a2, a3);
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)v9 + 96))(v9) == -2005532222 )
        (*(void (**)(void))(**(_DWORD **)((char *)v4 + 2151) + 8))();
      v10 = ((__int64 (__thiscall *)(_DWORD, _DWORD, int, _DWORD))*(_DWORD *)(**(_DWORD **)((char *)v4 + 2151) + 4))(
              *v4[489],
              0,
              0x1000000,
              0);
      return (*(int (__stdcall **)(_DWORD, int, _DWORD))(v11 + 20))(HIDWORD(v10), (int)v4 + 2155, v10);
    }
    else if ( v4[488] )
    {
      result = (***(int (****)(void))((char *)v4 + 2151))();
      if ( result )
      {
        v6 = (***(int (__stdcall ****)(int, int, int))((char *)v4 + 2151))(a4, a2, a3);
        if ( (*(int (__stdcall **)(int))(*(_DWORD *)v6 + 96))(v6) == -2005532222 )
          (*(void (**)(void))(**(_DWORD **)((char *)v4 + 2151) + 8))();
        v7 = *v4[488];
        v8 = ((__int64 (__cdecl *)(_DWORD, int, _DWORD))***(_DWORD ***)((char *)v4 + 2151))(0, 0x1000000, 0);
        return (*(int (__stdcall **)(_DWORD, int, _DWORD))(v7 + 20))(HIDWORD(v8), (int)v4 + 2155, v8);
      }
    }
  }
  return result;
}
// 467DE0: could not find valid save-restore pair for esi
// 467EAD: variable 'v11' is possibly undefined

//----- (00467EC0) --------------------------------------------------------
int  AviPlayer_BltFastOverlayFromBackBuffer(int a1, int a2)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(**(_DWORD **)(a1 + 1964) + 28))(
             *(_DWORD *)(a1 + 1964),
             0,
             0,
             *(_DWORD *)(a1 + 2017),
             0,
             0);
  if ( result )
  {
    if ( result == -2005532222 )
    {
      if ( (*(int (__stdcall **)(_DWORD, int))(**(_DWORD **)(a1 + 1964) + 96))(*(_DWORD *)(a1 + 1964), a2) == -2005532222 )
        (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 108))(*(_DWORD *)(a1 + 1964));
      if ( (*(int (__cdecl **)(_DWORD))(**(_DWORD **)(a1 + 2017) + 96))(*(_DWORD *)(a1 + 2017)) == -2005532222 )
        (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 2017) + 108))(*(_DWORD *)(a1 + 2017));
    }
    return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int))(**(_DWORD **)(a1 + 1964) + 28))(
             *(_DWORD *)(a1 + 1964),
             0,
             0,
             *(_DWORD *)(a1 + 2017),
             0,
             16);
  }
  return result;
}

//----- (00467F50) --------------------------------------------------------
int  AviPlayer_BltFrameToPrimarySurface(int a1, int a2)
{
  int result; // eax
  int v5; // edx
  int v6; // ecx

  if ( *(_DWORD *)(a1 + 2175)
    || (result = (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, _DWORD))(**(_DWORD **)(a1 + 1956) + 28))(
                   *(_DWORD *)(a1 + 1956),
                   *(_DWORD *)(a1 + 2063),
                   *(_DWORD *)(a1 + 2067),
                   a2,
                   a1 + 2079,
                   *(_DWORD *)(a1 + 2115))) != 0 )
  {
    if ( (*(int (__stdcall **)(_DWORD, int, int, int, _DWORD, _DWORD))(**(_DWORD **)(a1 + 1956) + 20))(
           *(_DWORD *)(a1 + 1956),
           a1 + 2063,
           a2,
           a1 + 2079,
           *(_DWORD *)(a1 + 2111),
           0) != -2005532222 )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(**(_DWORD **)(a1 + 1956) + 20))(
               *(_DWORD *)(a1 + 1956),
               a1 + 2063,
               a2,
               a1 + 2079,
               *(_DWORD *)(a1 + 2111) | 0x1000000,
               0);
    if ( (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 96))(*(_DWORD *)(a1 + 1956)) == -2005532222 )
    {
      result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 108))(*(_DWORD *)(a1 + 1956));
      if ( result )
        return result;
      if ( *(_DWORD *)(a1 + 1948) )
        (*(void (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 1956) + 124))(
          *(_DWORD *)(a1 + 1956),
          *(_DWORD *)(a1 + 1948));
      AviException_RebuildClipperOnSurfaceLoss(a1, v5, v6, a2);
    }
    if ( (*(int (__stdcall **)(int))(*(_DWORD *)a2 + 96))(a2) != -2005532222 )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(**(_DWORD **)(a1 + 1956) + 20))(
               *(_DWORD *)(a1 + 1956),
               a1 + 2063,
               a2,
               a1 + 2079,
               *(_DWORD *)(a1 + 2111) | 0x1000000,
               0);
    result = (*(int (__stdcall **)(int))(*(_DWORD *)a2 + 108))(a2);
    if ( !result )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(**(_DWORD **)(a1 + 1956) + 20))(
               *(_DWORD *)(a1 + 1956),
               a1 + 2063,
               a2,
               a1 + 2079,
               *(_DWORD *)(a1 + 2111) | 0x1000000,
               0);
  }
  return result;
}
// 468020: variable 'v5' is possibly undefined
// 468020: variable 'v6' is possibly undefined

//----- (00468060) --------------------------------------------------------
signed int  AviPlayer_RenderFrame(int a1, const RECT *a2)
{
  int v4; // esi
  signed int result; // eax
  int v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+4h] [ebp-1Ch]
  int v8; // [esp+8h] [ebp-18h]

  *(_DWORD *)(a1 + 2063) = a2->left;
  *(_DWORD *)(a1 + 2067) = a2->top;
  *(_DWORD *)(a1 + 2071) = a2->right;
  *(_DWORD *)(a1 + 2075) = a2->bottom;
  *(_DWORD *)(a1 + 2079) = *(_DWORD *)(a1 + 2095);
  *(_DWORD *)(a1 + 2083) = *(_DWORD *)(a1 + 2099);
  *(_DWORD *)(a1 + 2087) = *(_DWORD *)(a1 + 2103);
  *(_DWORD *)(a1 + 2091) = *(_DWORD *)(a1 + 2107);
  v7 = *(_DWORD *)(a1 + 2087) - *(_DWORD *)(a1 + 2079);
  v4 = a2->bottom - a2->top;
  v8 = *(_DWORD *)(a1 + 2091) - *(_DWORD *)(a1 + 2083);
  v6 = a2->right - a2->left;
  IntersectRect((LPRECT)(a1 + 2063), a2, (const RECT *)(a1 + 1969));
  result = IsRectEmpty((const RECT *)(a1 + 2063));
  if ( !result )
  {
    if ( !EqualRect((const RECT *)(a1 + 2063), a2) )
    {
      *(_DWORD *)(a1 + 2079) += v7 * (*(_DWORD *)(a1 + 2063) - a2->left) / v6;
      *(_DWORD *)(a1 + 2087) += v7 * (*(_DWORD *)(a1 + 2071) - a2->right) / v6;
      *(_DWORD *)(a1 + 2083) += v8 * (*(_DWORD *)(a1 + 2067) - a2->top) / v4;
      *(_DWORD *)(a1 + 2091) += v8 * (*(_DWORD *)(a1 + 2075) - a2->bottom) / v4;
    }
    if ( v7 == v6 && v4 == v8 )
    {
      result = v6 ^ v7;
      *(_DWORD *)(a1 + 2175) = v6 ^ v7;
    }
    else
    {
      result = 4;
      *(_DWORD *)(a1 + 2175) = 4;
    }
  }
  return result;
}

//----- (004681C0) --------------------------------------------------------
int  CAviDecompressor_PresentFrameIfStale(int a1, const RECT *a2)
{
  int result; // eax
  int v5; // edi
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ebp
  int v10; // eax
  int v11; // ecx
  int v12; // eax

  if ( !*(_BYTE *)(a1 + 2053) || (result = *(_DWORD *)(a1 + 2054), result < *(_DWORD *)(a1 + 2021)) )
  {
    result = WaitForSingleObject(*(HANDLE *)(a1 + 2196), 0);
    if ( !result )
    {
      if ( !*(_BYTE *)(a1 + 2062) )
        AviPlayer_RenderFrame(a1, a2);
      AviPlayer_Flip(a1);
      if ( !*(_BYTE *)(a1 + 1968) || !*(_DWORD *)(a1 + 1964) )
        goto LABEL_22;
      v5 = 1000 * AviPlayer_SpanDelta(a1, (_DWORD *)(a1 + 2063));
      v7 = v5 / AviPlayer_SpanDelta(v6, (_DWORD *)(a1 + 2079));
      if ( v7 < *(_DWORD *)(a1 + 2143) || v7 > *(_DWORD *)(a1 + 2147) )
      {
        if ( !*(_BYTE *)(a1 + 1968) )
          goto LABEL_22;
        v11 = *(_DWORD *)(a1 + 1964);
        if ( !v11 )
          goto LABEL_22;
        v12 = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(*(_DWORD *)v11 + 132))(
                v11,
                a1 + 2095,
                *(_DWORD *)(a1 + 1956),
                a1 + 2063,
                512,
                0);
        if ( !v12 )
          goto LABEL_22;
        if ( v12 == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 96))(*(_DWORD *)(a1 + 1964)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 108))(*(_DWORD *)(a1 + 1964))
           || (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 96))(*(_DWORD *)(a1 + 1956)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 108))(*(_DWORD *)(a1 + 1956))
           || !(*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(a1 + 1964) + 132))(
                 *(_DWORD *)(a1 + 1964),
                 a1 + 2095,
                 *(_DWORD *)(a1 + 1956),
                 a1 + 2063,
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
        v8 = 0x4000;
        if ( *(_DWORD *)(a1 + 2171) )
          v8 = 20480;
        v9 = v8;
        v10 = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(a1 + 1964) + 132))(
                *(_DWORD *)(a1 + 1964),
                a1 + 2095,
                *(_DWORD *)(a1 + 1956),
                a1 + 2063,
                v8,
                0);
        if ( !v10
          || v10 == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 96))(*(_DWORD *)(a1 + 1964)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1964) + 108))(*(_DWORD *)(a1 + 1964))
           || (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 96))(*(_DWORD *)(a1 + 1956)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 108))(*(_DWORD *)(a1 + 1956))
           || !(*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(a1 + 1964) + 132))(
                 *(_DWORD *)(a1 + 1964),
                 a1 + 2095,
                 *(_DWORD *)(a1 + 1956),
                 a1 + 2063,
                 v9,
                 0)) )
        {
          goto LABEL_22;
        }
        ExcString_Ctor();
        ExcString_Ctor();
      }
      CRT_ThrowExcStringException();
LABEL_22:
      ResetEvent(*(HANDLE *)(a1 + 2196));
      result = *(_DWORD *)(a1 + 2021);
      *(_DWORD *)(a1 + 2054) = result;
    }
  }
  return result;
}
// 468281: conditional instruction was optimized away because dh.1!=0
// 4682CF: variable 'v6' is possibly undefined

//----- (00468890) --------------------------------------------------------
int  CAviDecompressor_PresentFrameForRect(int a1, const RECT *a2)
{
  int v2; // ecx
  int result; // eax
  int v4; // ebx
  int v5; // esi
  int v6; // ecx
  int v7; // ecx
  int v8; // eax
  int v9; // edi
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
    result = AviPlayer_RenderFrame(v2, a2);
  v4 = v2;
  if ( *(_BYTE *)(v2 + 1968) && *(_DWORD *)(v2 + 1964) )
  {
    v5 = 1000 * AviPlayer_SpanDelta(v2, (_DWORD *)(v2 + 2063));
    result = v5 / AviPlayer_SpanDelta(v6, (_DWORD *)(v6 + 2079));
    if ( result < *(_DWORD *)(v7 + 2143) || result > *(_DWORD *)(v7 + 2147) )
    {
      if ( *(_BYTE *)(v4 + 1968) )
      {
        if ( *(_DWORD *)(v4 + 1964) )
        {
          result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v4 + 1964) + 132))(
                     *(_DWORD *)(v4 + 1964),
                     v4 + 2095,
                     *(_DWORD *)(v4 + 1956),
                     v4 + 2063,
                     512,
                     0);
          if ( result )
          {
            if ( result != -2005532222
              || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1964) + 96))(*(_DWORD *)(v4 + 1964)) != -2005532222
               || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1964) + 108))(*(_DWORD *)(v4 + 1964))) == 0)
              && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1956) + 96))(*(_DWORD *)(v4 + 1956)) != -2005532222
               || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1956) + 108))(*(_DWORD *)(v4 + 1956))) == 0)
              && (result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v4 + 1964) + 132))(
                             *(_DWORD *)(v4 + 1964),
                             v4 + 2095,
                             *(_DWORD *)(v4 + 1956),
                             v4 + 2063,
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
      v8 = 0x4000;
      if ( *(_DWORD *)(v7 + 2171) )
        v8 = 20480;
      v9 = v8;
      result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v4 + 1964) + 132))(
                 *(_DWORD *)(v4 + 1964),
                 v4 + 2095,
                 *(_DWORD *)(v4 + 1956),
                 v4 + 2063,
                 v8,
                 0);
      if ( result )
      {
        if ( result != -2005532222
          || ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1964) + 96))(*(_DWORD *)(v4 + 1964)) != -2005532222
           || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1964) + 108))(*(_DWORD *)(v4 + 1964))) == 0)
          && ((*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1956) + 96))(*(_DWORD *)(v4 + 1956)) != -2005532222
           || (result = (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(v4 + 1956) + 108))(*(_DWORD *)(v4 + 1956))) == 0)
          && (result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(v4 + 1964) + 132))(
                         *(_DWORD *)(v4 + 1964),
                         v4 + 2095,
                         *(_DWORD *)(v4 + 1956),
                         v4 + 2063,
                         v9,
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
  int v1; // ebx
  int v2; // esi
  char v3; // dl
  int v4; // ecx
  int v5; // edi
  int v6; // ebp

  v1 = result;
  if ( *(_DWORD *)(result + 2171) )
  {
    v2 = 8;
    v3 = *(_BYTE *)(result + 2112);
    v4 = *(_DWORD *)(result + 2046);
    *(_BYTE *)(result + 2115) |= 1u;
    result = *(_DWORD *)(result + 2042);
    *(_BYTE *)(v1 + 2112) = v3 | 0x80;
    if ( result == v4 )
      v2 = 9;
    v5 = *(_DWORD *)(v1 + 1964);
    if ( v5 )
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)v5 + 116))(v5, v2, v1 + 2042);
    v6 = *(_DWORD *)(v1 + 2017);
    if ( v6 )
      return (*(int (__stdcall **)(int, int, int))(*(_DWORD *)v6 + 116))(v6, v2, v1 + 2042);
  }
  return result;
}

//----- (00468C40) --------------------------------------------------------
char  AviPlayer_ComputeFlipState(int a1)
{
  int v1; // ecx
  int v2; // edx
  int v3; // esi
  int v4; // edx
  int v5; // edi
  int v6; // ecx
  int v7; // eax
  int v8; // ebx
  int v9; // edx
  int v10; // eax

  v1 = a1;
  v2 = *(_DWORD *)(a1 + 2179);
  *(_BYTE *)(a1 + 2033) = 0;
  if ( v2 )
  {
    *(_BYTE *)(a1 + 2033) = 1;
    return a1;
  }
  v3 = a1;
  v4 = a1;
  if ( *(_BYTE *)(a1 + 2052) )
  {
    v8 = a1;
    if ( !AviPlayer_IsIcmDecoderIdle(a1) || !AviPlayer_TestModeFlagBit3(v1) )
    {
      LOBYTE(a1) = AviPlayer_IsIcmDecoderIdle(v8);
      if ( (_BYTE)a1 )
        goto LABEL_16;
      LOBYTE(a1) = AviPlayer_TestModeFlagBit2(v8);
      if ( !(_BYTE)a1 )
      {
        *(_BYTE *)(v1 + 2033) = 2;
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
      *(_BYTE *)(v1 + 2033) = 2;
      return a1;
    }
  }
  LOBYTE(a1) = *(_BYTE *)(v3 + 1968);
  if ( !(_BYTE)a1
    || !*(_DWORD *)(v3 + 1964)
    || (v5 = 1000 * AviPlayer_SpanDelta(v1, (_DWORD *)(v3 + 2063)),
        a1 = v5 / AviPlayer_SpanDelta(v6, (_DWORD *)(v3 + 2079)),
        a1 < *(_DWORD *)(v3 + 2143))
    || a1 > *(_DWORD *)(v3 + 2147) )
  {
    if ( *(_DWORD *)(v3 + 1964) )
    {
      v10 = *(_DWORD *)(v3 + 2171);
      LOBYTE(v10) = v10 | 2;
      a1 = *(_DWORD *)(v3 + 2175) | v10;
      if ( (a1 & *(_DWORD *)(v3 + 2119)) != a1 )
      {
        *(_BYTE *)(v1 + 2033) = 2;
        return a1;
      }
      goto LABEL_8;
    }
LABEL_16:
    *(_BYTE *)(v1 + 2033) = 2;
    return a1;
  }
LABEL_8:
  if ( !*(_BYTE *)(v1 + 1968) || !*(_DWORD *)(v1 + 1964) )
  {
    if ( *(_DWORD *)(v1 + 1964) )
    {
      v7 = *(_DWORD *)(v1 + 2171);
      LOBYTE(v7) = v7 | 2;
      a1 = *(_DWORD *)(v1 + 2175) | v7;
      if ( (a1 & *(_DWORD *)(v1 + 2119)) == a1 )
        *(_BYTE *)(v1 + 2033) = 3;
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
        int a1,
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
  int v22; // eax
  int v23; // edx
  int v24; // edx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // ebx
  int v30; // esi
  int v31; // eax
  int v32; // edx
  __int64 v33; // rax
  int v34; // edx
  __int64 v35; // rax
  int v36; // eax
  int v39; // ebx
  __int64 v40; // rax
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
  int v61; // [esp+82h] [ebp-28Ah] BYREF
  char v62; // [esp+86h] [ebp-286h]
  char v63; // [esp+87h] [ebp-285h]
  char v64; // [esp+88h] [ebp-284h]
  char v65; // [esp+89h] [ebp-283h]
  char v66; // [esp+8Fh] [ebp-27Dh]
  char v67; // [esp+9Eh] [ebp-26Eh]
  char v68; // [esp+9Fh] [ebp-26Dh]
  char v69; // [esp+A0h] [ebp-26Ch]
  int v70; // [esp+10Ah] [ebp-202h]
  int v71; // [esp+10Eh] [ebp-1FEh]
  int v72[79]; // [esp+1BEh] [ebp-14Eh] BYREF
  _DWORD v73[4]; // [esp+2FAh] [ebp-12h] BYREF

  *(_DWORD *)((char *)&a18 + 6) = a1;
  *(_DWORD *)((char *)&a17 + 2) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&a17 + 6) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&a17 + 10) = &g_AviApplyOpenOptions_EHFrame;
  *(_DWORD *)((char *)&a17 + 14) = 0;
  memset_(a2, 0);
  memset_(v18, 0);
  v61 = 316;
  v72[0] = 316;
  (*(void (__stdcall **)(int, int *, int *))(*(_DWORD *)v19 + 44))(v19, &v61, v72);
  memset_(v20, 0);
  v73[0] = 108;
  (*(void (__stdcall **)(_DWORD, _DWORD *))(**(_DWORD **)(*(_DWORD *)((char *)&a18 + 6) + 1956) + 88))(
    *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 1956),
    v73);
  if ( (a15 & 0x800000000000000LL) != 0 )
    v22 = 1;
  else
    v22 = 256;
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2119) = v22;
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
    *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2143) = v70;
    *(_DWORD *)(v24 + 2147) = v71;
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
            v73,
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
  v29 = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 151);
  *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2052) = 0;
  v30 = *(_DWORD *)(v29 + 16);
  if ( !v30 || v30 == 3 )
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
           v29,
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
    v39 = *(_DWORD *)((char *)&a18 + 6) + 423;
    v40 = j_Mem_Alloc(0);
    *(_DWORD *)(HIDWORD(v40) + 2179) = v40;
    CAviDecompressor_SetupBlitFormat((int (*)())(*(_DWORD *)((char *)&a18 + 6) + 1924), *(_DWORD *)(HIDWORD(v40) + 2058), v41, v39, 0);
  }
  *(_BYTE *)(*(_DWORD *)((char *)&a18 + 6) + 2052) = 1;
LABEL_39:
  v31 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2095) = 0;
  *(_DWORD *)(v31 + 2099) = 0;
  v32 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2103) = *(_DWORD *)(*(_DWORD *)(v31 + 151) + 4);
  v33 = *(int *)(*(_DWORD *)(v32 + 151) + 8);
  LODWORD(v33) = (HIDWORD(v33) ^ v33) - HIDWORD(v33);
  HIDWORD(v33) = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2107) = v33;
  if ( *(_BYTE *)(HIDWORD(v33) + 2062) )
  {
    if ( !*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071) && !*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2075) )
    {
      v34 = *(_DWORD *)((char *)&a18 + 6);
      *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 151)
                                                                    + 4)
                                                        + *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2063);
      v35 = *(int *)(*(_DWORD *)(v34 + 151) + 8);
      *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2075) = (HIDWORD(v35) ^ v35)
                                                        - HIDWORD(v35)
                                                        + *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2067);
    }
    *(_DWORD *)((char *)&a16 + 2) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2063);
    *(_DWORD *)((char *)&a16 + 6) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2067);
    *(_DWORD *)((char *)&a16 + 10) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071);
    *(_DWORD *)((char *)&a16 + 14) = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2075);
    AviPlayer_RenderFrame(*(int *)((char *)&a18 + 6), (const RECT *)((char *)&a16 + 2));
    v36 = 1000
        * (*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2071) - *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2063))
        / (*(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2087) - *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2079));
    if ( v36 < *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2143)
      || v36 > *(_DWORD *)(*(_DWORD *)((char *)&a18 + 6) + 2147) )
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
int  AviPlayer_CreateSystemMemoryBackSurface(int a1, int a2)
{
  __int64 v3; // rax
  int v4; // ecx
  int result; // eax
  int v6; // ecx
  int v7; // ecx
  _DWORD v8[183]; // [esp+0h] [ebp-2F4h] BYREF
  int v9; // [esp+2DCh] [ebp-18h]

  v8[180] = NtCurrentTeb()->NtTib.ExceptionList;
  v8[181] = &j____wcpp_4_fs_handler_rtn_;
  v8[182] = &g_AviPlayerCreateBackSurface_EHScopeTable;
  v9 = 0;
  memset_(a2, 0);
  v8[0] = 108;
  v8[3] = *(_DWORD *)(*(_DWORD *)(a1 + 151) + 4);
  v3 = *(int *)(*(_DWORD *)(a1 + 151) + 8);
  v8[2] = (HIDWORD(v3) ^ v3) - HIDWORD(v3);
  v8[1] = 7;
  v8[26] = 2112;
  if ( (*(int (__stdcall **)(int, _DWORD *, int, _DWORD))(*(_DWORD *)v4 + 24))(v4, v8, a1 + 2013, 0) )
  {
    ExcString_Ctor();
    v9 = 1;
    ExcString_Ctor();
    v8[52] = v6;
    v9 = 0;
    return CRT_ThrowExcStringException();
  }
  else if ( (***(int (__stdcall ****)(_DWORD, void *, int))(a1 + 2013))(*(_DWORD *)(a1 + 2013), &unk_51C9F8, a1 + 2017) )
  {
    ExcString_Ctor();
    v9 = 3;
    ExcString_Ctor();
    v9 = 0;
    v8[104] = g_AviException_VTable;
    return CRT_ThrowExcStringException();
  }
  else
  {
    result = (*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 2017) + 148))(*(_DWORD *)(a1 + 2017), 0);
    if ( result )
    {
      ExcString_Ctor();
      v9 = v7;
      ExcString_Ctor();
      v8[78] = g_AviException_VTable;
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
int  AviPlayer_CreateOverlaySurface(int a1, int a2, int a3)
{
  __int64 v4; // rax
  int v5; // ecx
  int result; // eax
  _DWORD v7[31]; // [esp+0h] [ebp-7Ch] BYREF

  v7[29] = a3;
  memset_(a2, 0);
  v7[0] = 108;
  v7[3] = *(_DWORD *)(*(_DWORD *)(a1 + 151) + 4);
  v4 = *(int *)(*(_DWORD *)(a1 + 151) + 8);
  v7[2] = (HIDWORD(v4) ^ v4) - HIDWORD(v4);
  v7[1] = 7;
  v7[26] = 16448;
  result = (*(int (__stdcall **)(int, _DWORD *, int, _DWORD))(*(_DWORD *)v5 + 24))(v5, v7, a1 + 1960, 0);
  if ( !result )
    return (***(int (__stdcall ****)(_DWORD, void *, int))(a1 + 1960))(*(_DWORD *)(a1 + 1960), &unk_51C9F8, a1 + 1964);
  return result;
}
// 46955F: variable 'v5' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00469590) --------------------------------------------------------
int  AviPlayer_CreateOverlaySurfaceAndEnable(int a1, int a2)
{
  __int64 v3; // rax
  int v4; // ecx
  __int64 v5; // rax
  int v6; // ecx
  int result; // eax
  int v8; // [esp+0h] [ebp-80h] BYREF
  int v9; // [esp+4h] [ebp-7Ch]
  int v10; // [esp+8h] [ebp-78h]
  int v11; // [esp+Ch] [ebp-74h]
  int v12; // [esp+14h] [ebp-6Ch]
  int v13; // [esp+68h] [ebp-18h]

  memset_(a2, 0);
  v8 = 108;
  v11 = *(_DWORD *)(*(_DWORD *)(a1 + 151) + 4);
  v3 = *(int *)(*(_DWORD *)(a1 + 151) + 8);
  v10 = (HIDWORD(v3) ^ v3) - HIDWORD(v3);
  v12 = 1;
  v9 = 39;
  v13 = 16536;
  memset_(v4, 0);
  v8 = 108;
  v11 = *(_DWORD *)(*(_DWORD *)(a1 + 151) + 4);
  v5 = *(int *)(*(_DWORD *)(a1 + 151) + 8);
  v10 = (HIDWORD(v5) ^ v5) - HIDWORD(v5);
  v13 = 16512;
  v9 = 7;
  result = (*(int (__stdcall **)(int, int *, int, _DWORD))(*(_DWORD *)v6 + 24))(v6, &v8, a1 + 1960, 0);
  if ( !result )
  {
    result = (***(int (__stdcall ****)(_DWORD, void *, int))(a1 + 1960))(*(_DWORD *)(a1 + 1960), &unk_51C9F8, a1 + 1964);
    *(_BYTE *)(a1 + 1968) = 1;
    *(_BYTE *)(a1 + 2051) = 0;
  }
  return result;
}
// 4695F4: variable 'v4' is possibly undefined
// 46963F: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00469680) --------------------------------------------------------
int  AviPlayer_AllocDecodedBitmapInfo(int a1, int a2)
{
  int v3; // edx
  int v4; // edx
  int v5; // ebp
  __int64 v6; // rax
  int v7; // edx
  int result; // eax
  int v9; // [esp+0h] [ebp-20h]
  int v10; // [esp+4h] [ebp-1Ch]

  v3 = *(_DWORD *)(a1 + 2123);
  v10 = (v3 + 7) >> 3;
  if ( v3 == 24 || v3 == 8 )
    v4 = 0;
  else
    v4 = 3;
  v5 = v4;
  if ( v4 )
    a2 = **(_DWORD **)(a1 + 151);
  v6 = j_Mem_Alloc(a2);
  *(_DWORD *)(a1 + 2058) = v6;
  v9 = HIDWORD(v6);
  if ( SHIDWORD(v6) > **(_DWORD **)(a1 + 151) )
    HIDWORD(v6) = **(_DWORD **)(a1 + 151);
  qmemcpy(*(void **)(a1 + 2058), *(const void **)(a1 + 151), HIDWORD(v6));
  **(_DWORD **)(a1 + 2058) = v9;
  *(_WORD *)(*(_DWORD *)(a1 + 2058) + 14) = *(_WORD *)(a1 + 2123);
  *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 16) = v5;
  *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 20) = *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 4)
                                           * abs32(*(_DWORD *)(*(_DWORD *)(a1 + 2058) + 8))
                                           * v10;
  *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 32) = 0;
  v7 = *(_DWORD *)(a1 + 2058);
  result = *(_DWORD *)(v7 + 8);
  if ( result > 0 )
  {
    result = -result;
    *(_DWORD *)(v7 + 8) = result;
  }
  if ( v5 == 3 )
  {
    *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 40) = *(_DWORD *)(a1 + 2127);
    *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 44) = *(_DWORD *)(a1 + 2131);
    *(_DWORD *)(*(_DWORD *)(a1 + 2058) + 48) = *(_DWORD *)(a1 + 2135);
    result = *(_DWORD *)(a1 + 2058);
    *(_DWORD *)(result + 52) = *(_DWORD *)(a1 + 2139);
  }
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (004697E0) --------------------------------------------------------
// Deferred to compat/decomp_runtime_stubs.c until the late AVI init loop is reconstructed.

//----- (00469C90) --------------------------------------------------------
_DWORD * AviPlayer_CreatePaletteFromBitmap(int a1, int a2)
{
  _DWORD *result; // eax
  int i; // eax
  int v5; // ecx
  _BYTE v6[2]; // [esp+0h] [ebp-5BEh]
  char v7[1024]; // [esp+2h] [ebp-5BCh] BYREF
  int (**v8)(); // [esp+466h] [ebp-158h]
  int (**v9)(); // [esp+4CEh] [ebp-F0h]
  _DWORD v10[3]; // [esp+59Ah] [ebp-24h] BYREF
  int v11; // [esp+5A6h] [ebp-18h]

  result = v10;
  v10[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v10[1] = &j____wcpp_4_fs_handler_rtn_;
  v10[2] = &g_AviPlayerCreatePalette_EHScopeTable;
  v11 = 0;
  if ( (*(_BYTE *)(a1 + 2120) & 2) != 0 )
  {
    for ( i = 0; i != 1024; v6[i + 1] = 0 )
    {
      v7[i] = *(_BYTE *)(**(_DWORD **)(a1 + 151) + *(_DWORD *)(a1 + 151) + i + 2);
      v7[i + 1] = *(_BYTE *)(**(_DWORD **)(a1 + 151) + *(_DWORD *)(a1 + 151) + i + 1);
      i += 4;
      v6[i] = *(_BYTE *)(**(_DWORD **)(a1 + 151) + *(_DWORD *)(a1 + 151) + i - 4);
    }
    if ( (*(int (__stdcall **)(int, int, char *, int, _DWORD))(*(_DWORD *)a2 + 20))(a2, 4, v7, a1 + 1948, 0) )
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
      result = (_DWORD *)(*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 1956) + 124))(
                           *(_DWORD *)(a1 + 1956),
                           *(_DWORD *)(a1 + 1948));
      if ( result )
      {
        if ( result != (_DWORD *)-2005532222
          || (result = (_DWORD *)(*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 1956) + 108))(*(_DWORD *)(a1 + 1956))) == 0
          && (result = (_DWORD *)(*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(a1 + 1956) + 124))(
                                   *(_DWORD *)(a1 + 1956),
                                   *(_DWORD *)(a1 + 1948))) != 0 )
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
        int a1,
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
        int a13,
        int a14)
{
  _DWORD v15[13]; // [esp+0h] [ebp-34h] BYREF

  v15[0] = a2;
  v15[1] = a3;
  v15[2] = a4;
  v15[9] = a5;
  v15[10] = a6;
  v15[11] = a7;
  v15[12] = a8;
  v15[3] = a9;
  v15[4] = a10;
  v15[5] = a11;
  v15[6] = a12;
  v15[7] = a13;
  v15[8] = a14;
  return ICSendMessage(a1, 16446, (DWORD)v15, 52, 0);
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
int  AviException_ScalarDeletingDtor(int a1, char a2)
{
  int v3; // ecx
  int v5; // ecx

  v3 = a1;
  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_AviException_DtorArrayDescriptor);
    j_j__nfree_();
    return v5;
  }
  else
  {
    if ( (a2 & 2) != 0 )
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
BOOL  AviPlayer_PulseEventHandle(HANDLE *a1)
{
  return PulseEvent(*a1);
}

//----- (0046A110) --------------------------------------------------------
int  AviPlayer_LeaveBusySectionAndRelease(int a1)
{
  _DWORD *v2; // ebx

  v2 = *(_DWORD **)a1;
  LeaveCriticalSection((LPCRITICAL_SECTION)(*(_DWORD *)a1 + 4));
  --*v2;
  return a1;
}

//----- (0046A130) --------------------------------------------------------
int  Mem_BitsToBytesCeil(int a1)
{
  return (a1 + 7) >> 3;
}

//----- (0046A140) --------------------------------------------------------
int  AviPlayer_QueueBacklogCount(int a1)
{
  return *(_DWORD *)(a1 + 8) - *(_DWORD *)(a1 + 4);
}

//----- (0046A150) --------------------------------------------------------
int  AviPlayer_IncrementFramesRenderedCount(int result)
{
  ++*(_DWORD *)(result + 4);
  return result;
}

//----- (0046A160) --------------------------------------------------------
int  AviPlayer_AudioBytesQueued(int a1)
{
  return *(_DWORD *)(a1 + 259);
}

//----- (0046A170) --------------------------------------------------------
int  AviPlayer_AudioSampleQueueCount(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

//----- (0046A180) --------------------------------------------------------
int  AviPlayer_AudioSampleQueueBase(int a1)
{
  return a1 + 219;
}

//----- (0046A190) --------------------------------------------------------
int  AviPlayer_AudioFormatPtr(int a1)
{
  return *(_DWORD *)(a1 + 363);
}

//----- (0046A1A0) --------------------------------------------------------
int  AviPlayer_BitmapWidth(int a1)
{
  return *(_DWORD *)(*(_DWORD *)(a1 + 151) + 4);
}

//----- (0046A1B0) --------------------------------------------------------
int  AviPlayer_BitmapHeightAbs(int a1)
{
  __int64 v1; // rax

  v1 = *(int *)(*(_DWORD *)(a1 + 151) + 8);
  return (HIDWORD(v1) ^ v1) - HIDWORD(v1);
}

//----- (0046A1D0) --------------------------------------------------------
int  AviPlayer_AudioBlockAlign(int a1)
{
  return *(unsigned __int16 *)(*(_DWORD *)(a1 + 363) + 12);
}

//----- (0046A1E0) --------------------------------------------------------
int  AviPlayer_UpdateStreamRectAndSendICDrawBegin(int *a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v8; // edx
  int v9; // esi
  int result; // eax
  int v11; // [esp+0h] [ebp-124h]
  _DWORD v12[16]; // [esp+CCh] [ebp-58h] BYREF
  int v13; // [esp+10Ch] [ebp-18h]
  int v14; // [esp+110h] [ebp-14h]
  int v15; // [esp+114h] [ebp-10h]

  v12[13] = NtCurrentTeb()->NtTib.ExceptionList;
  v12[14] = &j____wcpp_4_fs_handler_rtn_;
  v13 = 0;
  v12[15] = &g_AviStreamRectDrawBegin_EHFrame;
  a1[3] = a5;
  a1[7] = a5 * a3 * ((*((unsigned __int16 *)a1 + 11) + 7) >> 3);
  v8 = a1[1];
  v14 = *a1;
  v15 = *(_DWORD *)(v8 + 4);
  v9 = *(_DWORD *)(v8 + 8);
  v12[0] = a7;
  v12[1] = v8;
  v12[12] = v9;
  v12[3] = a1 + 2;
  v12[4] = a2;
  v12[8] = a3;
  v12[2] = a6;
  v12[5] = 0;
  v12[6] = 0;
  v12[9] = 0;
  v12[10] = 0;
  v12[7] = a4;
  v12[11] = v15;
  result = ICSendMessage(v14, 16446, v12, 52, v11);
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
int  AviPlayer_StreamBitmapInfoPtr(int a1)
{
  return a1 + 8;
}

//----- (0046A360) --------------------------------------------------------
int __fastcall AviPlayer_SpanDelta(int a1, _DWORD *a2)
{
  return a2[2] - *a2;
}

//----- (0046A370) --------------------------------------------------------
bool  AviPlayer_IsUncompressedFormat(int a1)
{
  return *(_BYTE *)(a1 + 1923) != 0;
}

//----- (0046A380) --------------------------------------------------------
bool  AviPlayer_IsIcmDecoderIdle(int a1)
{
  int v1; // edx
  int v2; // eax
  bool result; // al

  result = 0;
  if ( *(_BYTE *)(a1 + 2052) )
  {
    v1 = *(_DWORD *)(a1 + 1944);
    v2 = a1 + 1924;
    if ( !v1 && !*(_DWORD *)(v2 + 16) )
      return 1;
  }
  return result;
}

//----- (0046A3B0) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit2(int a1)
{
  return (*(_BYTE *)(a1 + 2120) & 4) != 0;
}

//----- (0046A3C0) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit3(int a1)
{
  return (*(_BYTE *)(a1 + 2120) & 8) != 0;
}

//----- (0046A3D0) --------------------------------------------------------
bool  AviPlayer_TestActiveModeFlag(int a1)
{
  return *(_BYTE *)(a1 + 2052) && !*(_DWORD *)(a1 + 1944) && !*(_DWORD *)(a1 + 1940) && (*(_BYTE *)(a1 + 2120) & 8) != 0
      || (!*(_BYTE *)(a1 + 2052) || *(_DWORD *)(a1 + 1944) || *(_DWORD *)(a1 + 1940))
      && (*(_BYTE *)(a1 + 2120) & 4) != 0;
}

//----- (0046A430) --------------------------------------------------------
bool  AviPlayer_TestModeFlagBit2AndSubframe(int a1)
{
  return (*(_BYTE *)(a1 + 2120) & 4) != 0 && *(_BYTE *)(a1 + 1923);
}

//----- (0046A450) --------------------------------------------------------
bool  AviPlayer_SupportsRequiredPlaybackCaps(int a1)
{
  int v1; // edx

  v1 = *(_DWORD *)(a1 + 2171);
  LOBYTE(v1) = v1 | 2;
  return ((*(_DWORD *)(a1 + 2175) | v1) & *(_DWORD *)(a1 + 2119)) == (*(_DWORD *)(a1 + 2175) | v1);
}

//----- (0046A480) --------------------------------------------------------
bool  AviPlayer_HasValidRateParams(int a1)
{
  return *(_BYTE *)(a1 + 1968) && *(_DWORD *)(a1 + 1964);
}

//----- (0046A4A0) --------------------------------------------------------
bool  AviPlayer_IsPlaybackRateInRange(int a1)
{
  int v2; // eax

  v2 = 1000 * (*(_DWORD *)(a1 + 2071) - *(_DWORD *)(a1 + 2063)) / (*(_DWORD *)(a1 + 2087) - *(_DWORD *)(a1 + 2079));
  return v2 >= *(_DWORD *)(a1 + 2143) && v2 <= *(_DWORD *)(a1 + 2147);
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
int __cdecl Audio_ComputeMixChunkSampleCount(unsigned int a1)
{
  unsigned int v1; // eax

  v1 = 100 * dword_54D39C / a1 + 1;
  LOBYTE(v1) = v1 & 0xFE;
  dword_54D390 = v1;
  dword_54D394 = v1;
  return 0;
}
// 54D390: using guessed type int dword_54D390;
// 54D394: using guessed type int dword_54D394;
// 54D39C: using guessed type int dword_54D39C;

//----- (0046A610) --------------------------------------------------------
signed int __cdecl Audio_DetectDSoundHardwareAccel(_DWORD *a1)
{
  signed int result; // eax
  int v2; // ecx
  int v3; // [esp+4h] [ebp-68h] BYREF
  char v4; // [esp+8h] [ebp-64h]

  if ( g_CSS_DSoundAccelDetectEnabled )
  {
    if ( dword_54D470 )
    {
      dword_54D378 = dword_54D470;
      if ( DirectSoundCreate(0, &dword_54D368, 0) )
      {
        *a1 = 0;
        return 0;
      }
      else
      {
        memset_(&v3, 0);
        v3 = 96;
        if ( (*(int (__stdcall **)(int, int))(*(_DWORD *)dword_54D368 + 16))(dword_54D368, v2) || (v4 & 0x20) != 0 )
        {
          *a1 = 0;
          (*(void (__stdcall **)(int))(*(_DWORD *)dword_54D368 + 8))(dword_54D368);
          return 0;
        }
        else
        {
          *a1 = 1;
          (*(void (__stdcall **)(int))(*(_DWORD *)dword_54D368 + 8))(dword_54D368);
          return 0;
        }
      }
    }
    else
    {
      result = 1;
      *a1 = 0;
    }
  }
  else
  {
    result = 0;
    *a1 = 0;
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
  int v2; // [esp+4h] [ebp-6Ch] BYREF
  char v3; // [esp+8h] [ebp-68h]
  void *v4; // [esp+68h] [ebp-8h]

  v4 = this;
  memset_(this, 0);
  v2 = 96;
  (*(void (__stdcall **)(int, int *))(*(_DWORD *)dword_54D368 + 16))(dword_54D368, &v2);
  if ( (v3 & 8) == 0 )
    LOBYTE(dword_54D384) = dword_54D384 & 0xF7;
  if ( (v3 & 2) == 0 )
    LOBYTE(dword_54D384) = dword_54D384 & 0xFD;
  result = ((dword_54D384 & 8) != 0) + 1;
  dword_54D388 = result;
  if ( (dword_54D384 & 2) != 0 )
    dword_54D388 = 2 * result;
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 54D368: using guessed type int dword_54D368;
// 54D384: using guessed type int dword_54D384;
// 54D388: using guessed type int dword_54D388;

//----- (0046A750) --------------------------------------------------------
signed int Audio_InitDSoundDevice()
{
  unsigned int v1; // eax
  void *v2; // ecx
  int v3; // ecx
  unsigned int v4; // eax
  int v5; // esi
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  __int16 v10; // cx
  int v11; // ecx
  _DWORD v12[5]; // [esp+24h] [ebp-54h] BYREF
  int v13; // [esp+38h] [ebp-40h] BYREF
  int v14; // [esp+3Ch] [ebp-3Ch]
  int v15; // [esp+40h] [ebp-38h]
  __int16 *v16; // [esp+48h] [ebp-30h]
  __int16 v17; // [esp+4Ch] [ebp-2Ch] BYREF
  __int16 v18; // [esp+4Eh] [ebp-2Ah]
  int v19; // [esp+50h] [ebp-28h]
  int v20; // [esp+54h] [ebp-24h]
  __int16 v21; // [esp+58h] [ebp-20h]
  __int16 v22; // [esp+5Ah] [ebp-1Eh]
  __int16 v23; // [esp+5Ch] [ebp-1Ch]

  if ( !dword_54D470 )
    return 1;
  dword_54D378 = dword_54D470;
  dword_54D380 = 0;
  v1 = DirectSoundCreate(0, &dword_54D368, 0);
  if ( v1 )
    return Audio_ReturnDSoundError(v1);
  Audio_ComputeBytesPerFrame(v2);
  if ( g_CSS_DSoundAccelDetectEnabled != 2
    || (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_54D368 + 24))(dword_54D368, dword_54D378, 4) )
  {
    if ( !dword_54D380 )
    {
      v1 = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_54D368 + 24))(dword_54D368, dword_54D378, 3);
      if ( v1 )
        return Audio_ReturnDSoundError(v1);
      memset_(&v13, 0);
      v15 = 0;
      v16 = 0;
      v13 = 20;
      v14 = 1;
      v1 = (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)dword_54D368 + 12))(
             dword_54D368,
             v7,
             &dword_54D370,
             0);
      if ( v1 )
        return Audio_ReturnDSoundError(v1);
      memset_(v8, 0);
      v17 = 1;
      v18 = ((dword_54D384 & 2) != 0) + 1;
      v19 = dword_54D39C;
      v20 = dword_54D39C * dword_54D388;
      v21 = dword_54D388;
      if ( (dword_54D384 & 8) != 0 )
        v22 = 16;
      else
        v22 = 8;
      v23 = 0;
      (*(void (__stdcall **)(int, __int16 *))(*(_DWORD *)dword_54D370 + 56))(dword_54D370, &v17);
    }
  }
  else
  {
    dword_54D380 = 1;
  }
  v4 = dword_54D388 * 3 * dword_54D39C / (unsigned int)g_CSS_MixUpdateRateHz;
  v5 = v4 + 15;
  dword_54D36C = 0;
  LOWORD(v5) = (v4 + 15) & 0xFFF0;
  if ( !dword_54D380 )
  {
    dword_54D38C = v5;
    dword_54D398 = 16;
    memset_(v3, 0);
    v17 = 1;
    v18 = ((dword_54D384 & 2) != 0) + 1;
    v19 = dword_54D39C;
    v20 = dword_54D39C * dword_54D388;
    v21 = dword_54D388;
    if ( (dword_54D384 & 8) != 0 )
      v22 = 16;
    else
      v22 = 8;
    v23 = 0;
    memset_(20, 0);
    v13 = v6;
    v15 = dword_54D38C;
    v16 = &v17;
    v14 = 0x10000;
    v1 = (*(int (__stdcall **)(int, int *, int *, _DWORD))(*(_DWORD *)dword_54D368 + 12))(
           dword_54D368,
           &v13,
           &dword_54D370,
           0);
    if ( !v1 )
    {
      v1 = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)dword_54D370 + 48))(dword_54D370, 0, 0, 1);
      if ( !v1 )
        return 0;
    }
    return Audio_ReturnDSoundError(v1);
  }
  memset_(&v13, 0);
  v13 = 20;
  v15 = 0;
  v16 = 0;
  v14 = 1;
  v1 = (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)dword_54D368 + 12))(
         dword_54D368,
         v9,
         &dword_54D370,
         0);
  if ( v1 )
    return Audio_ReturnDSoundError(v1);
  memset_(1, 0);
  v17 = v10;
  v18 = v10 + ((dword_54D384 & 2) != 0);
  v19 = dword_54D39C;
  v20 = dword_54D39C * dword_54D388;
  v21 = dword_54D388;
  v22 = (dword_54D384 & 8) != 0 ? 16 : 8;
  v23 = 0;
  v1 = (*(int (__stdcall **)(int, __int16 *))(*(_DWORD *)dword_54D370 + 56))(dword_54D370, &v17);
  if ( v1 )
    return Audio_ReturnDSoundError(v1);
  memset_(v11, 0);
  v12[0] = 20;
  v1 = (*(int (__stdcall **)(int, _DWORD *))(*(_DWORD *)dword_54D370 + 12))(dword_54D370, v12);
  if ( v1 )
    return Audio_ReturnDSoundError(v1);
  dword_54D38C = v12[2];
  v1 = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)dword_54D370 + 48))(dword_54D370, 0, 0, 1);
  if ( v1 )
    return Audio_ReturnDSoundError(v1);
  if ( v5 + 16 >= (unsigned int)dword_54D38C )
    dword_54D398 = 16;
  else
    dword_54D398 = dword_54D38C - v5;
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
  unsigned int v0; // eax

  v0 = (*(int (__stdcall **)(int))(*(_DWORD *)dword_54D370 + 72))(dword_54D370);
  if ( v0 )
    return Audio_ReturnDSoundError(v0);
  (*(void (__stdcall **)(int))(*(_DWORD *)dword_54D370 + 8))(dword_54D370);
  (*(void (__stdcall **)(int))(*(_DWORD *)dword_54D368 + 8))(dword_54D368);
  return 0;
}
// 54D368: using guessed type int dword_54D368;
// 54D370: using guessed type int dword_54D370;

//----- (0046ABC0) --------------------------------------------------------
signed int __cdecl Audio_InitSoundSystem(int a1, char a2)
{
  signed int v2; // ebx
  signed int result; // eax

  if ( g_CSS_MixUpdateRateHz < 30 )
    g_CSS_MixUpdateRateHz = 30;
  dword_54D39C = a1;
  InitializeCriticalSection(&stru_54D350);
  EnterCriticalSection(&stru_54D350);
  dword_54D384 = ((a2 & 1) == 0) + 1;
  if ( (a2 & 4) != 0 )
    LOBYTE(dword_54D384) = dword_54D384 | 4;
  else
    LOBYTE(dword_54D384) = dword_54D384 | 8;
  dword_54D388 = ((dword_54D384 & 8) != 0) + 1;
  if ( (dword_54D384 & 2) != 0 )
    dword_54D388 = 2 * (((dword_54D384 & 8) != 0) + 1);
  v2 = Audio_InitDSoundDevice();
  if ( v2 || (CSS_InitMixBuffers(dword_54D39C, ((dword_54D384 & 2) != 0) + 1), (v2 = Audio_ComputeMixChunkSampleCount(100 * g_CSS_MixUpdateRateHz)) != 0) )
  {
    LeaveCriticalSection(&stru_54D350);
    return v2;
  }
  else
  {
    switch ( dword_54D384 )
    {
      case 5:
        dword_54D37C = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8;
        goto LABEL_11;
      case 6:
        dword_54D37C = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8Stereo;
        goto LABEL_11;
      case 9:
        dword_54D37C = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_MixInterleaved16;
        goto LABEL_11;
      case 10:
        dword_54D37C = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM16Stereo;
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
  unsigned int v0; // ebx

  EnterCriticalSection(&stru_54D350);
  CSS_FreeMixBuffers();
  v0 = Audio_ReleaseDSoundDevice();
  LeaveCriticalSection(&stru_54D350);
  if ( v0 )
    return v0;
  DeleteCriticalSection(&stru_54D350);
  return 0;
}

//----- (0046AD60) --------------------------------------------------------
int __cdecl Audio_GetSoundFormatFlags(_DWORD *a1)
{
  *a1 = dword_54D384;
  return 0;
}
// 54D384: using guessed type int dword_54D384;

//----- (0046AD70) --------------------------------------------------------
unsigned int Audio_RefreshPlayCursor()
{
  unsigned int v0; // eax
  int v2; // [esp+Ch] [ebp-8h] BYREF
  _BYTE v3[4]; // [esp+10h] [ebp-4h] BYREF

  EnterCriticalSection(&stru_54D350);
  v0 = (*(int (__stdcall **)(int, int *, _BYTE *))(*(_DWORD *)dword_54D370 + 16))(dword_54D370, &v2, v3);
  if ( v0 )
    return Audio_ReturnDSoundError(v0);
  dword_54D374 = v2;
  LeaveCriticalSection(&stru_54D350);
  return 0;
}
// 54D370: using guessed type int dword_54D370;
// 54D374: using guessed type int dword_54D374;

//----- (0046ADC0) --------------------------------------------------------
unsigned int __cdecl Audio_FillDSoundBuffer(_DWORD *a1)
{
  unsigned int v1; // ebp
  unsigned int v2; // edi
  DWORD TickCount; // eax
  unsigned int v4; // edi
  unsigned int v5; // edi
  unsigned int v6; // esi
  int v7; // eax
  unsigned int v8; // ebx
  unsigned int v10; // ecx
  int v11; // [esp+20h] [ebp-20h] BYREF
  int v12; // [esp+24h] [ebp-1Ch] BYREF
  unsigned int v13; // [esp+28h] [ebp-18h] BYREF
  _DWORD v14[5]; // [esp+2Ch] [ebp-14h] BYREF

  EnterCriticalSection(&stru_54D350);
  v1 = (unsigned int)dword_54DB98 >> 2;
  if ( (dword_54D384 & 2) != 0 )
    v1 = (unsigned int)dword_54DB98 >> 3;
  if ( dword_54D36C > (unsigned int)dword_54D374 )
    v2 = dword_54D374 + dword_54D38C - dword_54D36C;
  else
    v2 = dword_54D374 - dword_54D36C;
  if ( v2 > dword_54D398 )
  {
    TickCount = 0;
    v4 = v2 - dword_54D398;
LABEL_7:
    dword_54D3A4 = TickCount;
    goto LABEL_8;
  }
  v4 = 0;
  if ( GetForegroundWindow() == (HWND)dword_54D378 )
  {
    if ( dword_54D3A0 )
    {
      if ( !dword_54D3A4 || GetTickCount() < dword_54D3A4 )
      {
        TickCount = GetTickCount();
        goto LABEL_7;
      }
      if ( GetTickCount() - dword_54D3A4 > 0x3E8 )
      {
        (*(void (__stdcall **)(int))(*(_DWORD *)dword_54D370 + 80))(dword_54D370);
        (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)dword_54D370 + 48))(dword_54D370, 0, 0, 1);
        dword_54D3A4 = 0;
      }
    }
    else
    {
      dword_54D3A0 = 1;
    }
  }
  else
  {
    dword_54D3A0 = 0;
  }
LABEL_8:
  v5 = v4 / dword_54D388;
  while ( v5 )
  {
    if ( !dword_54D394 )
      break;
    if ( v5 <= dword_54D394 )
      v6 = v5;
    else
      v6 = dword_54D394;
    if ( v6 > v1 )
      v6 = v1;
    v5 -= v6;
    dword_54D394 -= v6;
    CSS_TickChannelLevels(v1, v6);
    while ( 1 )
    {
      v7 = (*(int (__stdcall **)(int, int, unsigned int, int *, unsigned int *, int *, _DWORD *, _DWORD))(*(_DWORD *)dword_54D370 + 44))(
             dword_54D370,
             dword_54D36C,
             v6 * dword_54D388,
             &v11,
             &v13,
             &v12,
             v14,
             0);
      v8 = v7;
      if ( !v7 )
        break;
      if ( v7 != -2005401450 )
        goto LABEL_19;
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)dword_54D370 + 80))(dword_54D370) )
      {
        LeaveCriticalSection(&stru_54D350);
        *a1 = 0;
        return 0;
      }
      v8 = (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)dword_54D370 + 48))(dword_54D370, 0, 0, 1);
      if ( v8 )
        goto LABEL_19;
    }
    if ( v13 )
      dword_54D37C(v13 / dword_54D388, v11, 0, dword_54DBA0);
    if ( v14[0] )
      dword_54D37C(v14[0] / (unsigned int)dword_54D388, v12, 0, dword_54DBA0 + 4 * (v13 >> 1));
    v10 = v14[0] + v13 + dword_54D36C;
    dword_54D36C = v10;
    if ( v10 >= dword_54D38C )
      dword_54D36C = v10 - dword_54D38C;
    v8 = (*(int (__stdcall **)(int, int, unsigned int, int, _DWORD))(*(_DWORD *)dword_54D370 + 76))(
           dword_54D370,
           v11,
           v13,
           v12,
           v14[0]);
    if ( v8 )
    {
LABEL_19:
      LeaveCriticalSection(&stru_54D350);
      return Audio_ReturnDSoundError(v8);
    }
  }
  if ( dword_54D394 )
  {
    *a1 = 0;
  }
  else
  {
    dword_54D394 = dword_54D390;
    *a1 = 1;
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
int __cdecl Audio_ClipMixBufferToPCM16(int a1, int a2, int a3, signed int *a4)
{
  _WORD *v4; // edi
  int i; // ecx
  int v7; // eax

  v4 = (_WORD *)(a3 + a2);
  for ( i = a1; i; --i )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        v7 = *a4++;
        if ( v7 <= 0x7FFF )
          break;
        *v4++ = 0x7FFF;
        if ( !--i )
          return (int)v4 - a2;
      }
      if ( v7 < -32768 )
        break;
      *v4++ = v7;
      if ( !--i )
        return (int)v4 - a2;
    }
    *v4++ = 0x8000;
  }
  return (int)v4 - a2;
}

//----- (0046B169) --------------------------------------------------------
_BYTE *__cdecl Audio_ClipMixBufferToPCM8(int a1, int a2, int a3, int *a4)
{
  _BYTE *v4; // edi
  int i; // ecx
  int v7; // eax
  int v8; // eax

  v4 = (_BYTE *)(a3 + a2);
  for ( i = a1; i; --i )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        v7 = *a4++;
        v8 = v7 + 0x8000;
        if ( v8 <= 0x10000 )
          break;
        *v4++ = -1;
        if ( !--i )
          return &v4[-a2];
      }
      if ( v8 < 0 )
        break;
      *v4++ = BYTE1(v8);
      if ( !--i )
        return &v4[-a2];
    }
    *v4++ = 0;
  }
  return &v4[-a2];
}

//----- (0046B1BA) --------------------------------------------------------
int __cdecl Audio_ClipMixBufferToPCM16Stereo(int a1, int a2, int a3, signed int *a4)
{
  return Audio_MixInterleaved16(2 * a1, a2, a3, a4);
}

//----- (0046B1D7) --------------------------------------------------------
_BYTE *__cdecl Audio_ClipMixBufferToPCM8Stereo(int a1, int a2, int a3, int *a4)
{
  return Audio_ClipMixBufferToPCM8(2 * a1, a2, a3, a4);
}

//----- (0046B200) --------------------------------------------------------
int  Audio_ReadWavHeaderFromStream(int a1, _DWORD *a2)
{
  int result; // eax
  int v4; // eax
  void (__fastcall **v5)(_DWORD, int); // ecx
  char v6; // al
  char v7[8]; // [esp+0h] [ebp-40h] BYREF
  char v8[4]; // [esp+8h] [ebp-38h] BYREF
  char v9[4]; // [esp+Ch] [ebp-34h] BYREF
  int v10; // [esp+10h] [ebp-30h]
  unsigned __int16 v11; // [esp+14h] [ebp-2Ch]
  unsigned __int16 v12; // [esp+16h] [ebp-2Ah]
  int v13; // [esp+18h] [ebp-28h]
  unsigned __int16 v14; // [esp+20h] [ebp-20h]
  char v15[4]; // [esp+24h] [ebp-1Ch] BYREF
  int v16; // [esp+28h] [ebp-18h]

  result = (*(int (__fastcall **)(int, int))(*(_DWORD *)dword_54D4B8 + 12))(a1, a1);
  v16 = result;
  if ( !result )
    return result;
  (*(void (**)(void))(*(_DWORD *)result + 20))();
  if ( (*(int (**)(void))(*(_DWORD *)v16 + 16))() == -1
    || memcmp(v7, aRiff, 4)
    || memcmp(v8, aWave, 4)
    || memcmp(v9, aFmt, 4)
    || (v4 = (*(int (**)(void))(*(_DWORD *)v16 + 4))(),
        (*v5)(v5, v10 + v4 - 16),
        (*(void (**)(void))(*(_DWORD *)v16 + 20))(),
        memcmp(v15, aData, 4)) )
  {
LABEL_3:
    (*(void (**)(void))(*(_DWORD *)dword_54D4B8 + 20))();
    return 0;
  }
  (*(void (**)(void))(*(_DWORD *)v16 + 20))();
  a2[2] = v13;
  if ( v11 != 1 )
  {
    if ( v11 == 32787 )
    {
      *a2 = (char)((v12 != 1) + 5);
      return v16;
    }
    goto LABEL_3;
  }
  if ( v12 == 1 )
    v6 = 1;
  else
    v6 = 3;
  *a2 = v6;
  if ( v14 / (int)v12 == 2 )
    ++*a2;
  v13 = a2[2];
  return v16;
}
// 46B2D5: variable 'v5' is possibly undefined
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046B610) --------------------------------------------------------
void  Audio_MixResampledVoice(int *a1)
{
  unsigned int *v2; // ebx
  unsigned int v3; // edx
  unsigned __int64 v4; // rtt
  unsigned int v5; // eax
  int v6; // esi
  unsigned int v7; // edx
  unsigned int v8; // eax
  unsigned int v9; // eax
  unsigned __int64 v10; // rax
  int v11; // eax
  unsigned __int64 v12; // rt2
  int v13; // esi
  int v14; // ebp
  int v15; // edx
  int v16; // edi
  int v17; // edx
  int v18; // esi
  int v19; // edi
  int v20; // eax
  __int64 v21; // rax
  int v22; // eax
  __int64 v23; // rax
  int *v24; // [esp-2Ch] [ebp-2Ch]

  g_Audio_MixVoice_SamplesRemaining = a1[5];
  g_Audio_MixVoice_ChannelIndexArg = a1[2];
  g_Audio_MixVoice_AccumBufferPtr = dword_54DBA0;
  g_Audio_MixVoice_MixFunc = (int (__fastcall *)(_DWORD, _DWORD))a1[3];
  v2 = (unsigned int *)(108 * a1[2] + dword_54DB90);
  g_Audio_CurrentVoiceRecordPtr = (int)v2;
  g_Audio_MixVoice_LoopCallback = (int (__cdecl *)(_DWORD))v2[26];
  g_Audio_MixVoice_LoopDirection = v2[16];
  g_Audio_MixVoice_PositionInt = v2[12];
  g_Audio_MixVoice_PositionFrac = v2[13];
  g_Audio_MixVoice_SampleHistory0 = v2[10];
  g_Audio_MixVoice_SampleHistory1 = v2[11];
  if ( v2[1] && v2[24] == 3 )
  {
    g_Audio_MixVoice_Pan = v2[19];
    v3 = v2[15];
    LODWORD(v4) = v3 << 16;
    HIDWORD(v4) = HIWORD(v3);
    g_Audio_MixVoice_ResampleStep = v4 / (unsigned int)dword_54DB9C;
    g_Audio_MixVoice_MaxSourceAdvance = (((unsigned int)g_Audio_MixVoice_ResampleStep * (unsigned __int64)(unsigned int)a1[5]) >> 16) + 2;
LABEL_4:
    v5 = v2[24];
    if ( v5 > 2 )
    {
      if ( v5 == 3 )
      {
        g_Audio_MixVoice_LoopBoundsSwitchPending = 0;
      }
      else
      {
        if ( v2[25] == 2 )
        {
          g_Audio_MixVoice_LoopBoundLow = v2[7];
          g_Audio_MixVoice_LoopBoundHigh = v2[8];
          g_Audio_MixVoice_LoopMode = v2[9];
LABEL_11:
          g_Audio_MixVoice_LoopFinalFlag = v2[18]
                      && (v2[3] == 5 || v2[3] == 4)
                      && ((v6 = 40 * v2[17] + dword_54DB94, *(_DWORD *)(v6 + 12) == 4) || *(_DWORD *)(v6 + 12) == 5);
          v7 = *v2;
          v8 = v2[1];
          switch ( v8 )
          {
            case 3u:
            case 2u:
              goto LABEL_22;
            case 4u:
              v7 >>= 2;
              break;
            case 6u:
LABEL_22:
              v7 >>= 1;
              break;
          }
          g_Audio_VoiceMixSampleStep = v7;
          while ( 1 )
          {
            if ( !g_Audio_MixVoice_SamplesRemaining )
              goto LABEL_80;
            if ( v2[17] == 5 )
            {
              v9 = v2[14];
              if ( v9 >= g_Audio_MixVoice_PositionInt )
              {
                if ( v9 == g_Audio_MixVoice_PositionInt )
                  goto LABEL_78;
                goto LABEL_37;
              }
            }
            if ( !g_Audio_MixVoice_LoopMode )
            {
              v9 = v2[2];
              goto LABEL_37;
            }
            if ( g_Audio_MixVoice_LoopMode == 1 )
              break;
            if ( g_Audio_MixVoice_LoopDirection != -1 )
            {
              v9 = g_Audio_MixVoice_LoopBoundHigh;
LABEL_37:
              g_Audio_MixVoice_NextChunkEndScratch = v9 + g_Audio_VoiceMixSampleStep;
              v10 = ((unsigned __int64)(v9 - g_Audio_MixVoice_PositionInt) << 16) - (unsigned int)g_Audio_MixVoice_PositionFrac;
              goto LABEL_38;
            }
            v10 = (unsigned int)g_Audio_MixVoice_PositionFrac + ((unsigned __int64)(unsigned int)(g_Audio_MixVoice_PositionInt - g_Audio_MixVoice_LoopBoundLow) << 16);
LABEL_38:
            if ( HIWORD(g_Audio_MixVoice_MaxSourceAdvance) < HIDWORD(v10) || g_Audio_MixVoice_MaxSourceAdvance << 16 < (unsigned int)v10 )
            {
              v11 = g_Audio_MixVoice_SamplesRemaining;
            }
            else
            {
              v12 = v10 % (unsigned int)g_Audio_MixVoice_ResampleStep;
              v11 = v10 / (unsigned int)g_Audio_MixVoice_ResampleStep;
              if ( (_DWORD)v12 )
                ++v11;
              if ( v11 > (unsigned int)g_Audio_MixVoice_SamplesRemaining )
                v11 = g_Audio_MixVoice_SamplesRemaining;
            }
            g_Audio_MixVoice_SamplesRemaining -= v11;
            if ( a1[4] )
            {
              v24 = a1;
              v13 = g_Audio_MixVoice_PositionInt + g_Audio_VoiceMixSampleStep;
              v14 = g_Audio_MixVoice_PositionFrac;
              v15 = g_Audio_MixVoice_ResampleStep;
              v16 = g_Audio_MixVoice_AccumBufferPtr;
              if ( g_Audio_MixVoice_LoopDirection == -1 )
                v15 = -g_Audio_MixVoice_ResampleStep;
              g_Audio_MixVoice_MixFunc(v11, v15);
              g_Audio_MixVoice_PositionFrac = v14;
              g_Audio_MixVoice_PositionInt = v13 - g_Audio_VoiceMixSampleStep;
              g_Audio_MixVoice_AccumBufferPtr = v16;
              a1 = v24;
            }
            else
            {
              v17 = g_Audio_MixVoice_ResampleStep;
              if ( g_Audio_MixVoice_LoopDirection == -1 )
                v17 = -g_Audio_MixVoice_ResampleStep;
              v18 = g_Audio_MixVoice_PositionInt << 16;
              LOWORD(v18) = g_Audio_MixVoice_PositionFrac;
              LOWORD(g_Audio_MixVoice_PositionFrac) = v17 * v11 + g_Audio_MixVoice_PositionFrac;
              g_Audio_MixVoice_PositionInt = (__int64)(v17 * (__int64)v11 + __PAIR64__(g_Audio_MixVoice_PositionInt >> 16, v18)) >> 16;
              if ( !a1[2] )
              {
                v19 = g_Audio_MixVoice_AccumBufferPtr;
                Audio_ZeroMixAccumulatorBuffer(v11, (void *)g_Audio_MixVoice_AccumBufferPtr);
                g_Audio_MixVoice_AccumBufferPtr = v19;
              }
            }
            if ( !g_Audio_MixVoice_LoopMode )
            {
              if ( g_Audio_MixVoice_PositionInt < v2[2] )
                goto LABEL_80;
              if ( g_Audio_MixVoice_LoopFinalFlag != 1 )
              {
                v2[24] = 1;
                goto LABEL_78;
              }
LABEL_74:
              CSS_ChannelLoadQueuedSound(a1[2]);
              if ( v2[3] == 5 )
              {
                g_Audio_MixVoice_PositionInt = v2[4];
                g_Audio_MixVoice_PositionFrac = 0;
                goto LABEL_4;
              }
              v2[24] = 1;
              goto LABEL_78;
            }
            if ( g_Audio_MixVoice_LoopDirection == -1 )
            {
              v22 = g_Audio_MixVoice_PositionInt;
              if ( g_Audio_MixVoice_PositionInt >= g_Audio_MixVoice_LoopBoundLow )
                goto LABEL_80;
              if ( g_Audio_MixVoice_LoopCallback )
                v22 = g_Audio_MixVoice_LoopCallback(a1[2]);
              g_Audio_MixVoice_LoopDirection = 1;
              HIDWORD(v23) = v22;
              LODWORD(v23) = v22 << 16;
              SHIDWORD(v23) >>= 16;
              LOWORD(v23) = g_Audio_MixVoice_PositionFrac;
              LOWORD(g_Audio_MixVoice_PositionFrac) = -(__int16)g_Audio_MixVoice_PositionFrac;
              g_Audio_MixVoice_PositionInt = ((2 * __PAIR64__(HIWORD(g_Audio_MixVoice_LoopBoundLow), g_Audio_MixVoice_LoopBoundLow << 16) - v23) >> 32 << 16) | ((unsigned int)((g_Audio_MixVoice_LoopBoundLow << 17) - v23) >> 16);
              goto LABEL_72;
            }
            v20 = g_Audio_MixVoice_PositionInt;
            if ( g_Audio_MixVoice_PositionInt >= (unsigned int)g_Audio_MixVoice_LoopBoundHigh )
            {
              if ( g_Audio_MixVoice_LoopCallback )
                v20 = g_Audio_MixVoice_LoopCallback(a1[2]);
              if ( g_Audio_MixVoice_LoopFinalFlag == 1 )
                goto LABEL_74;
              if ( g_Audio_MixVoice_LoopBoundsSwitchPending == 1 )
              {
                v2[25] = 2;
                g_Audio_MixVoice_LoopBoundsSwitchPending = 0;
                g_Audio_MixVoice_LoopBoundLow = v2[7];
                g_Audio_MixVoice_LoopBoundHigh = v2[8];
                g_Audio_MixVoice_LoopMode = v2[9];
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
                  HIDWORD(v21) = v20;
                  LODWORD(v21) = v20 << 16;
                  SHIDWORD(v21) >>= 16;
                  LOWORD(v21) = g_Audio_MixVoice_PositionFrac;
                  LOWORD(g_Audio_MixVoice_PositionFrac) = -(__int16)g_Audio_MixVoice_PositionFrac;
                  g_Audio_MixVoice_PositionInt = ((2 * __PAIR64__(HIWORD(g_Audio_MixVoice_LoopBoundHigh), g_Audio_MixVoice_LoopBoundHigh << 16) - v21) >> 32 << 16) | ((unsigned int)((g_Audio_MixVoice_LoopBoundHigh << 17) - v21) >> 16);
                }
LABEL_72:
                if ( !g_Audio_MixVoice_SamplesRemaining )
                  goto LABEL_80;
              }
            }
            else if ( v2[17] != 5 )
            {
              goto LABEL_80;
            }
          }
          v9 = g_Audio_MixVoice_LoopBoundHigh;
          goto LABEL_37;
        }
        g_Audio_MixVoice_LoopBoundsSwitchPending = 1;
      }
      g_Audio_MixVoice_LoopBoundLow = v2[4];
      g_Audio_MixVoice_LoopBoundHigh = v2[5];
      g_Audio_MixVoice_LoopMode = v2[6];
      goto LABEL_11;
    }
  }
LABEL_78:
  if ( !a1[2] )
    Audio_ZeroMixAccumulatorBuffer(g_Audio_MixVoice_SamplesRemaining, (void *)g_Audio_MixVoice_AccumBufferPtr);
LABEL_80:
  v2[12] = g_Audio_MixVoice_PositionInt;
  v2[13] = g_Audio_MixVoice_PositionFrac;
  v2[16] = g_Audio_MixVoice_LoopDirection;
  v2[10] = g_Audio_MixVoice_SampleHistory0;
  v2[11] = g_Audio_MixVoice_SampleHistory1;
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
int  Audio_MixMonoVoiceIntoBuffer(signed int a1, int a2, char a3, void *a4)
{
  int (__thiscall *v4)(signed int); // eax
  int result; // eax

  g_Audio_MixFormatDispatchTable = (int)&g_Audio_MixMonoVoiceDispatchBase;
  if ( a2 )
  {
    if ( !a3 )
      memset(a4, 0, 4 * a2);
    v4 = *(int (__thiscall **)(signed int))(g_Audio_MixFormatDispatchTable + -4 * (a2 & 3) + 16);
    g_Audio_MixVoice_StepIntArg = a1 >> 16;
    return v4(a1 << 16);
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
        signed int a2,
        unsigned int a3,
        __int16 a4,
        void *a5)
{
  int (__thiscall *v5)(unsigned int); // eax
  __int16 v6; // cx

  g_Audio_MixFormatDispatchTable = (int)&g_Audio_MixPannedVoiceDispatchBase;
  if ( a3 )
  {
    if ( !(_BYTE)a4 )
    {
      HIWORD(result) = 0;
      memset(a5, 0, 8 * a3);
    }
    if ( (_BYTE)g_Audio_MixVoice_Pan == 0x80 )
    {
      g_Audio_MixVoice_LeftVolumeStep = -1;
      g_Audio_MixVoice_RightVolumeStep = 1;
      g_Audio_MixVoice_LeftVolume = HIBYTE(a4);
      g_Audio_MixVoice_RightVolume = HIBYTE(a4);
    }
    else
    {
      g_Audio_MixVoice_LeftVolumeStep = 0;
      g_Audio_MixVoice_RightVolumeStep = 0;
      if ( (g_Audio_MixVoice_Pan & 0x80u) == 0 )
      {
        g_Audio_MixVoice_RightVolume = HIBYTE(a4);
        LOWORD(result) = (unsigned __int8)(64 - g_Audio_MixVoice_Pan) * HIBYTE(a4);
        g_Audio_MixVoice_LeftVolume = result >> 6;
      }
      else
      {
        g_Audio_MixVoice_LeftVolume = HIBYTE(a4);
        LOWORD(result) = (unsigned __int8)(g_Audio_MixVoice_Pan + 64) * HIBYTE(a4);
        g_Audio_MixVoice_RightVolume = result >> 6;
      }
    }
    g_Audio_MixVoice_PanStepFracArg = a2 << 16;
    v5 = *(int (__thiscall **)(unsigned int))(g_Audio_MixFormatDispatchTable + -4 * (a3 & 3) + 16);
    LOBYTE(v6) = (a3 >> 2) + 1;
    g_Audio_MixVoice_StepIntArg = a2 >> 16;
    HIBYTE(v6) = (unsigned __int8)(g_Audio_MixVoice_RightVolume + 1) >> 1;
    return v5(((unsigned int)dword_54DB8C >> 2) + (v6 & 0xFF00));
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
static int Audio_MixVoiceSpanDispatch_46BB40(signed int a1, int a2, char a3, void *a4)
{
  int (__thiscall *v4)(signed int); // eax
  int result; // eax

  if ( a2 )
  {
    if ( !a3 )
      memset(a4, 0, 4 * a2);
    v4 = *(int (__thiscall **)(signed int))(g_Audio_MixFormatDispatchTable + -4 * (a2 & 3) + 16);
    g_Audio_MixVoice_StepIntArg = a1 >> 16;
    return v4(a1 << 16);
  }
  return result;
}

static unsigned int Audio_MixVoiceSpanDispatch_46BB9A(
        unsigned int result,
        signed int a2,
        unsigned int a3,
        __int16 a4,
        void *a5)
{
  int (__thiscall *v5)(unsigned int); // eax
  __int16 v6; // cx

  if ( a3 )
  {
    if ( !(_BYTE)a4 )
    {
      HIWORD(result) = 0;
      memset(a5, 0, 8 * a3);
    }
    if ( (_BYTE)g_Audio_MixVoice_Pan == 0x80 )
    {
      g_Audio_MixVoice_LeftVolumeStep = -1;
      g_Audio_MixVoice_RightVolumeStep = 1;
      g_Audio_MixVoice_LeftVolume = HIBYTE(a4);
      g_Audio_MixVoice_RightVolume = HIBYTE(a4);
    }
    else
    {
      g_Audio_MixVoice_LeftVolumeStep = 0;
      g_Audio_MixVoice_RightVolumeStep = 0;
      if ( (g_Audio_MixVoice_Pan & 0x80u) == 0 )
      {
        g_Audio_MixVoice_RightVolume = HIBYTE(a4);
        LOWORD(result) = (unsigned __int8)(64 - g_Audio_MixVoice_Pan) * HIBYTE(a4);
        g_Audio_MixVoice_LeftVolume = result >> 6;
      }
      else
      {
        g_Audio_MixVoice_LeftVolume = HIBYTE(a4);
        LOWORD(result) = (unsigned __int8)(g_Audio_MixVoice_Pan + 64) * HIBYTE(a4);
        g_Audio_MixVoice_RightVolume = result >> 6;
      }
    }
    g_Audio_MixVoice_PanStepFracArg = a2 << 16;
    v5 = *(int (__thiscall **)(unsigned int))(g_Audio_MixFormatDispatchTable + -4 * (a3 & 3) + 16);
    LOBYTE(v6) = (a3 >> 2) + 1;
    g_Audio_MixVoice_StepIntArg = a2 >> 16;
    HIBYTE(v6) = (unsigned __int8)(g_Audio_MixVoice_RightVolume + 1) >> 1;
    return v5(((unsigned int)dword_54DB8C >> 2) + (v6 & 0xFF00));
  }
  return result;
}

//----- (0046BE88) --------------------------------------------------------
int Audio_SelectMixFormat1Mono(signed int a1, int a2, char a3, void *a4)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat1MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(a1, a2, a3, a4);
}
// 46BDD1: using guessed type void *off_46BDD1;
// 519B94: using guessed type int dword_519B94;

//----- (0046BF5E) --------------------------------------------------------
unsigned int Audio_SelectMixFormat1Stereo(unsigned int result, signed int a2, unsigned int a3, __int16 a4, void *a5)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat1StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, a2, a3, a4, a5);
}
// 46BE97: using guessed type void *off_46BE97;
// 519B94: using guessed type int dword_519B94;

//----- (0046C030) --------------------------------------------------------
int Audio_SelectMixFormat2Mono(signed int a1, int a2, char a3, void *a4)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat2MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(a1, a2, a3, a4);
}
// 46BF6D: using guessed type void *off_46BF6D;
// 519B94: using guessed type int dword_519B94;

//----- (0046C1A2) --------------------------------------------------------
unsigned int Audio_SelectMixFormat2Stereo(unsigned int result, signed int a2, unsigned int a3, __int16 a4, void *a5)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat2StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, a2, a3, a4, a5);
}
// 46C03F: using guessed type void *off_46C03F;
// 519B94: using guessed type int dword_519B94;

//----- (0046C2FC) --------------------------------------------------------
int Audio_SelectMixFormat3Mono(signed int a1, int a2, char a3, void *a4)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat3MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(a1, a2, a3, a4);
}
// 46C1B1: using guessed type void *off_46C1B1;
// 519B94: using guessed type int dword_519B94;

//----- (0046C472) --------------------------------------------------------
unsigned int Audio_SelectMixFormat3Stereo(unsigned int result, signed int a2, unsigned int a3, __int16 a4, void *a5)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat3StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, a2, a3, a4, a5);
}
// 46C30B: using guessed type void *off_46C30B;
// 519B94: using guessed type int dword_519B94;

//----- (0046C6B4) --------------------------------------------------------
int Audio_SelectMixFormat4Mono(signed int a1, int a2, char a3, void *a4)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat4MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(a1, a2, a3, a4);
}
// 46C481: using guessed type void *off_46C481;
// 519B94: using guessed type int dword_519B94;

//----- (0046C996) --------------------------------------------------------
unsigned int Audio_SelectMixFormat4Stereo(unsigned int result, signed int a2, unsigned int a3, __int16 a4, void *a5)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat4StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, a2, a3, a4, a5);
}
// 46C6C3: using guessed type void *off_46C6C3;
// 519B94: using guessed type int dword_519B94;

//----- (0046CE10) --------------------------------------------------------
int Audio_SelectMixFormat5Mono(signed int a1, int a2, char a3, void *a4)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat5MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(a1, a2, a3, a4);
}
// 46C9A5: using guessed type void *off_46C9A5;
// 519B94: using guessed type int dword_519B94;

//----- (0046D2A6) --------------------------------------------------------
unsigned int Audio_SelectMixFormat5Stereo(unsigned int result, signed int a2, unsigned int a3, __int16 a4, void *a5)
{
  g_Audio_MixFormatDispatchTable = (int)&g_Audio_SelectMixFormat5StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, a2, a3, a4, a5);
}
// 46CE1F: using guessed type void *off_46CE1F;
// 519B94: using guessed type int dword_519B94;

//----- (0046D2B5) --------------------------------------------------------
int __cdecl Audio_ClearGlobalMixBuffer(int a1)
{
  Audio_ZeroMixAccumulatorBuffer(a1, (void *)dword_54DBA0);
  return 0;
}

//----- (0046D2D1) --------------------------------------------------------
int  Audio_ZeroMixAccumulatorBuffer(int a1, void *a2)
{
  int result; // eax

  if ( a1 )
  {
    result = 0;
    if ( dword_54DBA4 == 2 )
      a1 *= 2;
    memset(a2, 0, 4 * a1);
  }
  return result;
}
// 54DBA4: using guessed type int dword_54DBA4;

//----- (0046D2F0) --------------------------------------------------------
int __cdecl Audio_GetFixedCapabilityFlag(_DWORD *a1)
{
  *a1 = 1;
  return 0;
}

//----- (0046D300) --------------------------------------------------------
int __cdecl Audio_SetMixerParamValue(int a1, int a2)
{
  g_CSS_NullDriverMasterVolume = a2;
  return 0;
}
// 519BD0: using guessed type int dword_519BD0;

//----- (0046D320) --------------------------------------------------------
int __cdecl CSS_NullDriver_GetZero(_DWORD *a1)
{
  *a1 = 0;
  return 0;
}

//----- (0046D330) --------------------------------------------------------
int __cdecl CSS_NullDriver_GetMasterVolume(_DWORD *a1)
{
  *a1 = g_CSS_NullDriverMasterVolume;
  return 0;
}
// 519BD0: using guessed type int dword_519BD0;

//----- (0046D350) --------------------------------------------------------
int __cdecl CSS_Mem_TryAllocRaw(int a1, _DWORD *a2)
{
  int v2; // ecx
  __int64 v3; // rax

  LODWORD(v3) = a1;
  *a2 = 0;
  if ( a1 )
  {
    v3 = nmalloc_(v2, a2);
    *(_DWORD *)HIDWORD(v3) = v3;
  }
  return v3;
}
// 46D363: variable 'v2' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);

//----- (0046D370) --------------------------------------------------------
int __cdecl CSS_Mem_TryAlloc(int a1, _DWORD *a2)
{
  return CSS_Mem_TryAllocRaw(a1, a2);
}

//----- (0046D390) --------------------------------------------------------
int __cdecl CSS_Mem_FreeIfSet(int a1)
{
  int v1; // ecx
  int result; // eax

  result = a1;
  if ( a1 )
    return nfree_(v1);
  return result;
}
// 46D396: variable 'v1' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);

//----- (0046D3A0) --------------------------------------------------------
_DWORD * CSS_FileStream_Create(_DWORD *a1, int a2, int a3, int a4)
{
  int v5; // edx
  int v6; // edx
  int v7; // edx

  a1[1] = a2;
  a1[7] = 0;
  a1[8] = 0;
  a1[9] = 0;
  a1[10] = 0;
  a1[14] = a3;
  *a1 = g_CSSFileStream_VTable;
  a1[2] = (*(int (**)(void))(*(_DWORD *)a2 + 4))();
  a1[3] = a1[2];
  a1[4] = a4 + a1[3];
  a1[5] = a1[3];
  a1[6] = 0x7FFFFFFF;
  a1[11] = 0;
  v5 = a1[14];
  a1[13] = 0x4000;
  v6 = v5 / a1[13];
  if ( v6 < 2 )
    v6 = 2;
  v7 = a1[13] * (v6 + 1);
  a1[14] = v7;
  a1[12] = 0;
  CSS_Mem_TryAlloc(v7, a1 + 15);
  a1[8] = a1[14];
  a1[10] = a1[14];
  return a1;
}
// 5105B4: using guessed type int (*off_5105B4[12])();

//----- (0046D460) --------------------------------------------------------
_DWORD * CSS_FileStream_Destroy(_DWORD *a1, char a2, int a3, int a4, int a5)
{
  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a3, &g_CSSFileStream_DtorArrayDescriptor);
    j_j__nfree_();
    return a1;
  }
  else
  {
    *a1 = g_CSSFileStream_VTable;
    CSS_Mem_FreeIfSet(a1[15]);
    (*(void (__cdecl **)(int, int, int))(*(_DWORD *)dword_54D4B8 + 20))(a3, a5, a4);
    if ( (a2 & 2) != 0 )
      j__nfree_();
    return a1;
  }
}
// 46D460: could not find valid save-restore pair for edi
// 46D460: could not find valid save-restore pair for esi
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 5105B4: using guessed type int (*off_5105B4[12])();
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046D530) --------------------------------------------------------
int  CSS_FileStream_FillSequential(int a1)
{
  int result; // eax
  int v2; // ecx

  result = (*(int (__thiscall **)(int))(**(_DWORD **)(a1 + 4) + 20))(a1);
  *(_DWORD *)(v2 + 8) += result;
  return result;
}
// 46D53C: variable 'v2' is possibly undefined

//----- (0046D550) --------------------------------------------------------
int  CSS_FileStream_FillWithLoopWrap(int a1, int a2, int a3, int a4)
{
  int v7; // ecx
  int v8; // eax
  int v9; // ecx

  if ( a3 < a4 - *(_DWORD *)(a1 + 8) )
    return CSS_FileStream_FillSequential(a1);
  v7 = (*(int (**)(void))(**(_DWORD **)(a1 + 4) + 20))();
  (***(void (__fastcall ****)(int, int))(a1 + 4))(v7, a2);
  v8 = (*(int (**)(void))(**(_DWORD **)(a1 + 4) + 20))();
  *(_DWORD *)(a1 + 8) = v8 + a2;
  return v9 + v8;
}
// 46D5B2: variable 'v9' is possibly undefined

//----- (0046D5C0) --------------------------------------------------------
int  CSS_FileStream_FillOneBlock(_DWORD *a1, int a2)
{
  int v3; // esi

  if ( !a2 )
    return 0;
  v3 = a1[4];
  if ( a1[6] > v3 )
    return CSS_FileStream_FillSequential((int)a1);
  if ( a1[2] <= a1[6] )
    return CSS_FileStream_FillWithLoopWrap((int)a1, a1[5], a2, a1[6]);
  return CSS_FileStream_FillWithLoopWrap((int)a1, a1[3], a2, a1[4]);
}

//----- (0046D620) --------------------------------------------------------
int  CSS_FileStream_RefillBuffer(_DWORD *a1)
{
  _DWORD *v1; // ecx
  int v2; // eax
  int v3; // ebp
  int v4; // eax
  int v5; // edi
  _DWORD *v6; // esi
  int v8; // eax
  int v9; // [esp+4h] [ebp-1Ch]

  v1 = a1;
  v2 = a1[9] - a1[7];
  v3 = 0;
  if ( v1[14] - v2 < v1[13] )
    v4 = 0;
  else
    v4 = (3 * v2 <= v1[14]) + 1;
  v9 = v4;
  v5 = 0;
  if ( v4 > 0 )
  {
    v6 = v1 + 9;
    do
    {
      if ( v1[11] )
        break;
      v8 = CSS_FileStream_FillOneBlock(v1, v1[13]);
      *v6 += v8;
      if ( v8 != v1[13] )
        v1[11] = 1;
      ++v5;
      v3 += v8;
    }
    while ( v5 < v9 );
  }
  return v3;
}
// 46D66B: variable 'v1' is possibly undefined

//----- (0046D6C0) --------------------------------------------------------
int  CSS_FileStream_PreloadFully(int a1)
{
  int v1; // edx
  int result; // eax

  v1 = a1;
  do
    result = (*(int (**)(void))(*(_DWORD *)v1 + 32))();
  while ( result );
  return result;
}
// 46D6C4: variable 'v1' is possibly undefined

//----- (0046D6E0) --------------------------------------------------------
int  CSS_FileStream_Read(_DWORD *a1, char *a2, int a3)
{
  signed int v3; // ebx
  int v6; // [esp+8h] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-14h]

  v8 = a3;
  v6 = 0;
  if ( a1[9] - a1[7] < a3 )
    v8 = a1[9] - a1[7];
  while ( v8 )
  {
    v3 = a1[8] - a1[7] % a1[8];
    if ( v3 >= v8 )
      v3 = v8;
    qmemcpy(a2, (const void *)(a1[7] % a1[8] + a1[15]), v3);
    a1[7] += v3;
    a2 += v3;
    v6 += v3;
    v8 -= v3;
  }
  if ( v6 < a3 )
    ++a1[12];
  return v6;
}

//----- (0046D7C0) --------------------------------------------------------
BOOL  CSS_FileStream_IsFinished(_DWORD *a1)
{
  return a1[11] && a1[9] == a1[7];
}

//----- (0046D7F0) --------------------------------------------------------
int  CSS_FileStream_QueryDone(int a1)
{
  return (*(int (**)(void))(*(_DWORD *)a1 + 4))();
}

//----- (0046D800) --------------------------------------------------------
signed int  CSS_FileStream_SetLoopRange(_DWORD *a1, int a2, int a3)
{
  a1[5] = a2 + a1[3];
  if ( a3 < 0 )
    a3 = a1[4];
  a1[6] = a3;
  return 1;
}

//----- (0046D830) --------------------------------------------------------
_DWORD * CSS_FileStream_GetLoopRange(_DWORD *result, _DWORD *a2, _DWORD *a3)
{
  if ( result[6] == 0x7FFFFFFF )
  {
    *a2 = 0;
    *a3 = 0;
  }
  else
  {
    *a2 = result[5] - result[3];
    *a3 = result[6] - result[3];
  }
  return result;
}

//----- (0046D870) --------------------------------------------------------
signed int  CSS_FileStream_ClearLoop(_DWORD *a1)
{
  a1[5] = a1[3];
  a1[6] = 0x7FFFFFFF;
  return 1;
}

//----- (0046D890) --------------------------------------------------------
int  CSS_FileStream_GetSourceBytesFetched(int a1)
{
  return *(_DWORD *)(a1 + 8) - *(_DWORD *)(a1 + 12);
}

//----- (0046D8A0) --------------------------------------------------------
signed int  CSS_FileStream_DispatchIfInRange(int a1, int a2, int a3)
{
  int v3; // ecx
  int v4; // edx

  v3 = *(_DWORD *)(a1 + 12);
  v4 = v3 + a2;
  if ( v4 < v3 || v4 >= *(_DWORD *)(a1 + 16) )
    return 0;
  (***(void (__cdecl ****)(int))(a1 + 4))(a3);
  return 1;
}

//----- (0046D8D0) --------------------------------------------------------
_DWORD * CSS_FileStream_New(int a1, int a2)
{
  _DWORD *v4; // eax
  int v5; // edx
  int v6; // ecx

  v4 = (_DWORD *)Mem_Alloc(64, a2, (char)&j____wcpp_4_fs_handler_rtn_, 0);
  if ( v4 )
    return CSS_FileStream_Create(v4, a1, v6, v5);
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

  dword_54D3D8 = 0;
  InitializeCriticalSection(&CriticalSection);
  CRT_RegisterFinalizableObject(v1, v0);
  dword_54D3F8 = 0;
  InitializeCriticalSection(&stru_54D3FC);
  CRT_RegisterFinalizableObject(v3, v2);
  dword_54D420 = 0;
  InitializeCriticalSection(&stru_54D424);
  CRT_RegisterFinalizableObject(v5, v4);
  dword_54D440 = 0;
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
unsigned int  CSS_CloseChannel(unsigned int a1, signed int a2)
{
  unsigned int result; // eax
  int *v4; // ebx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-30h]
  int v6; // [esp+14h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  result = 52 * a1;
  v4 = (int *)(result + dword_54D3D0);
  if ( *(_DWORD *)(result + dword_54D3D0 + 40) )
  {
    v4[10] = 0;
    if ( (v4[9] & 0xC) != 0 )
    {
      CSS_ChannelStop(a1);
      ++dword_54D3D8;
      EnterCriticalSection(&CriticalSection);
      ++dword_54D3F8;
      EnterCriticalSection(&stru_54D3FC);
      v4[9] = 0;
      v4[11] = 0;
      CSS_Mem_FreeIfSet(*v4);
      *v4 = 0;
      v6 = v4[5];
      if ( v6 )
        (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(*(_DWORD *)v6 + 44))(
          ExceptionList,
          &j____wcpp_4_fs_handler_rtn_,
          &g_CSSCloseChannel_EHScopeTable,
          1);
      v4[5] = 0;
      --dword_54D3C4;
      LeaveCriticalSection(&CriticalSection);
      --dword_54D3D8;
      LeaveCriticalSection(&stru_54D3FC);
      return dword_54D3F8--;
    }
    else
    {
      if ( a2 )
        result = CSS_ChannelBeginVolumeFade(a1, 0, a2);
      else
        result = CSS_ChannelMarkIdle(a1);
      *v4 = 0;
      v4[9] = 0;
    }
  }
  return result;
}
// 54D3C4: using guessed type int dword_54D3C4;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046DB80) --------------------------------------------------------
int  CSS_Channel_FillSilence(int a1, int a2)
{
  int result; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // esi
  int v9; // ecx

  if ( !a2 )
    return 1;
  v4 = (***(int (__fastcall ****)(int, int))(a1 + 20))(a1, *(_DWORD *)(a1 + 12) + *(_DWORD *)a1);
  *(_DWORD *)(v5 + 12) += v4;
  if ( v4 >= a2 )
    return 1;
  result = (*(int (**)(void))(**(_DWORD **)(v5 + 20) + 4))();
  if ( result )
  {
    v8 = a2 - v6;
    memset_(v7, *(_DWORD *)(v7 + 24));
    *(_DWORD *)(v9 + 12) += v8;
    *(_DWORD *)(v9 + 28) += v8;
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
void  CSS_Channel_ServiceStream(unsigned int a1)
{
  int v2; // ebx
  int v3; // esi
  int v4; // edx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // esi
  int v9; // edi
  int v10; // ecx
  int v11; // edi
  int v12; // [esp+0h] [ebp-14h] BYREF
  int v13; // [esp+4h] [ebp-10h]

  v2 = dword_54D3D0 + 52 * a1;
  if ( (!*(_DWORD *)(dword_54D468 + 28) || *(_DWORD *)(v2 + 28) >= *(_DWORD *)(v2 + 8))
    && (*(int (**)(void))(**(_DWORD **)(v2 + 20) + 8))() )
  {
    *(_DWORD *)(v2 + 48) = 1;
    return;
  }
  if ( *(_DWORD *)v2 && *(_DWORD *)(dword_54D468 + 28) )
  {
    CSS_ChannelGetPlayPosition(a1, &v12);
    if ( v12 )
      v3 = v12;
    else
      v3 = *(_DWORD *)(v2 + 8);
    v4 = *(_DWORD *)(v2 + 12);
    v5 = *(_DWORD *)(v2 + 8);
    if ( v3 <= v4 )
    {
      v13 = v3;
      v8 = v5 - v4;
      v9 = v5;
      if ( v5 - v4 > v5 )
        v8 = v5;
      if ( !CSS_Channel_FillSilence(v2, v8) )
        goto LABEL_15;
      *(_DWORD *)(v10 + 12) = 0;
      v11 = v9 - v8;
      if ( !v11 )
        goto LABEL_15;
      if ( v13 - *(_DWORD *)(v10 + 16) <= v11 )
        v6 = v13 - *(_DWORD *)(v10 + 16);
      else
        v6 = v11;
      v7 = v10;
    }
    else
    {
      if ( v3 - v4 - *(_DWORD *)(v2 + 16) <= v5 )
        v5 = v3 - v4 - *(_DWORD *)(v2 + 16);
      v6 = v5;
      v7 = v2;
    }
    CSS_Channel_FillSilence(v7, v6);
LABEL_15:
    CSS_ChannelSetPositionOffset(a1, *(_DWORD *)(v2 + 12));
  }
}
// 46DD6D: variable 'v10' is possibly undefined
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046DEF0) --------------------------------------------------------
int  CSS_Channel_StoreFormatParams(int a1, int a2)
{
  int result; // eax

  *(_DWORD *)(a1 + 16) = CSS_GetFormatSampleSize(a2);
  result = CSS_GetFormatSilenceValue(a2);
  *(_DWORD *)(a1 + 24) = result;
  return result;
}

//----- (0046DF20) --------------------------------------------------------
void  CSS_Channel_StartFileStream(unsigned int a1, int *a2, int a3, int a4, int a5, int a6)
{
  _DWORD *v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // [esp+0h] [ebp-14h] BYREF
  int v13; // [esp+4h] [ebp-10h]

  v13 = a3;
  v12 = 0;
  v9 = (_DWORD *)(52 * a1 + dword_54D3D0);
  CSS_Channel_StoreFormatParams((int)v9, *a2);
  v10 = 3 * a2[2] / g_CSS_StreamServiceRateHz;
  LOBYTE(v10) = v10 & 0xFC;
  v9[1] = v10;
  v9[2] = v9[1] * v9[4];
  CSS_Mem_TryAlloc(v9[2], &v12);
  v9[3] = 0;
  v9[7] = 0;
  CSS_ChannelInitPlayback(a1, v12, v9[2], *a2, a2[2]);
  CSS_ChannelMarkIdle(a1);
  CSS_ChannelSetVolumeImmediate(a1, a4);
  CSS_ChannelSetPanning(a1, v13);
  v9[12] = 0;
  v9[11] = 0;
  v9[9] = a6;
  v11 = g_CSS_VoiceSequenceCounter++;
  v9[10] = v11;
  *v9 = v12;
  CSS_Channel_ServiceStream(a1);
  ++dword_54D3C4;
}
// 519CB0: using guessed type int dword_519CB0;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C4: using guessed type int dword_54D3C4;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E100) --------------------------------------------------------
int  CSS_SampleCache_FreeEntry(int *a1)
{
  dword_54D3BC -= a1[2];
  CSS_Mem_FreeIfSet(*a1);
  CSS_Mem_FreeIfSet(a1[4]);
  return CSS_Mem_FreeIfSet((int)a1);
}
// 54D3BC: using guessed type int dword_54D3BC;

//----- (0046E140) --------------------------------------------------------
signed int  CSS_SampleCache_EvictEntry(int **a1)
{
  signed int v2; // ebx
  int v3; // esi
  int *v4; // eax

  v2 = 0;
  if ( dword_54D3C8 <= 0 )
  {
LABEL_7:
    v4 = *a1;
    *a1 = (int *)(*a1)[5];
    CSS_SampleCache_FreeEntry(v4);
    return 1;
  }
  else
  {
    v3 = 0;
    while ( !*(_DWORD *)(v3 + dword_54D3D0 + 40) || *(_DWORD *)(v3 + dword_54D3D0) != **a1 || !CSS_ChannelIsPlaying(v2) )
    {
      ++v2;
      v3 += 52;
      if ( v2 >= dword_54D3C8 )
        goto LABEL_7;
    }
    return 0;
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E1B0) --------------------------------------------------------
int  CSS_SampleCache_MakeRoom(int a1)
{
  int **v1; // edx
  int v2; // ecx
  int result; // eax
  int v4; // edx

  v1 = (int **)&dword_54D3B8;
  v2 = a1;
  while ( v2 + dword_54D3BC > dword_54D3C0 && CSS_SampleCache_EvictEntry(v1) )
    ;
  result = v2 + dword_54D3BC;
  if ( v2 + dword_54D3BC > dword_54D3C0 )
  {
    v4 = dword_54D3B8;
    while ( 1 )
    {
      result = v2 + dword_54D3BC;
      if ( v2 + dword_54D3BC <= dword_54D3C0 || !*(_DWORD *)(v4 + 20) )
        break;
      if ( !CSS_SampleCache_EvictEntry((int **)(v4 + 20)) )
        v4 = *(_DWORD *)(v4 + 20);
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
int  CSS_SampleCache_AppendEntry(int result, int a2)
{
  for ( ; *(_DWORD *)(result + 20); result = *(_DWORD *)(result + 20) )
    ;
  *(_DWORD *)(result + 20) = a2;
  return result;
}

//----- (0046E240) --------------------------------------------------------
int  CSS_SampleCache_TouchEntry(int *a1)
{
  int v2; // ecx
  int result; // eax

  CSS_SampleCache_AppendEntry(*a1, *a1);
  *a1 = *(_DWORD *)(v2 + 20);
  result = v2;
  *(_DWORD *)(v2 + 20) = 0;
  return result;
}
// 46E250: variable 'v2' is possibly undefined

//----- (0046E270) --------------------------------------------------------
int  CSS_SampleCache_FindAndTouch(int a1)
{
  int v3; // ecx
  int v4; // ecx

  if ( !dword_54D3B8 )
    return 0;
  if ( stricmp_(dword_54D3B8, a1) )
  {
    while ( *(_DWORD *)(v3 + 20) )
    {
      if ( !stricmp_(v3, a1) )
        return CSS_SampleCache_TouchEntry((int *)(v4 + 20));
      v3 = *(_DWORD *)(v4 + 20);
    }
    return 0;
  }
  return CSS_SampleCache_TouchEntry(&dword_54D3B8);
}
// 46E293: variable 'v3' is possibly undefined
// 46E2AA: variable 'v4' is possibly undefined
// 484E2A: using guessed type int __fastcall stricmp_(_DWORD, _DWORD);
// 54D3B8: using guessed type int dword_54D3B8;

//----- (0046E2D0) --------------------------------------------------------
struct _EXCEPTION_REGISTRATION_RECORD *CSS_SweepFinishedChannels()
{
  int v0; // ebx
  signed int i; // ecx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v0 = 0;
  for ( i = 0; i < dword_54D3C8; v0 += 52 )
  {
    if ( *(_DWORD *)(v0 + dword_54D3D0 + 48) )
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
  int v0; // ebx
  signed int i; // esi
  int v2; // eax
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-2Ch]
  tagRECT *v5; // [esp+4h] [ebp-28h]
  void *v6; // [esp+8h] [ebp-24h]
  int v7; // [esp+Ch] [ebp-20h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v0 = 0;
  v5 = &j____wcpp_4_fs_handler_rtn_;
  v6 = &g_CSSServiceStreamingChannels_EHScopeTable;
  v7 = 0;
  CSS_StreamService_NoOpHook();
  for ( i = 0; i < dword_54D3C8; v0 += 52 )
  {
    v2 = v0 + dword_54D3D0;
    if ( *(_DWORD *)(v0 + dword_54D3D0 + 44)
      && *(_DWORD *)(v2 + 40)
      && (*(_BYTE *)(v2 + 36) & 0xC) != 0
      && CSS_ChannelIsPlaying(i) )
    {
      (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(**(_DWORD **)(v0 + dword_54D3D0 + 20)
                                                                                           + 32))(
        ExceptionList,
        v5,
        v6,
        v7);
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
int __stdcall CSS_StreamReadingThreadProc(int a1)
{
  ++dword_54D420;
  EnterCriticalSection(&stru_54D424);
  while ( dword_54D414 )
  {
    ++dword_54D3D8;
    EnterCriticalSection(&CriticalSection);
    CSS_ServiceStreamingChannels();
    LeaveCriticalSection((LPCRITICAL_SECTION)(&dword_54D3D8 + 1));
    --dword_54D3D8;
    Sleep(1000 / g_CSS_StreamServiceRateHz);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(&dword_54D420 + 1));
  --dword_54D420;
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
  int *v1; // ebx
  _DWORD v2[3]; // [esp+0h] [ebp-20h] BYREF
  int v3; // [esp+Ch] [ebp-14h]
  int *v4; // [esp+14h] [ebp-Ch]

  result = v2;
  v2[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v2[1] = &j____wcpp_4_fs_handler_rtn_;
  v2[2] = &g_CSSPauseStreamReading_EHScopeTable;
  v3 = 0;
  if ( dword_54D414 )
  {
    v4 = &dword_54D3D8;
    ++dword_54D3D8;
    EnterCriticalSection(&CriticalSection);
    v3 = 1;
    SuspendThread(hThread);
    v3 = 0;
    v1 = v4;
    LeaveCriticalSection((LPCRITICAL_SECTION)(v4 + 1));
    return (_DWORD *)(*v1)--;
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
int __stdcall CSS_StreamBufferServiceThreadProc(int a1)
{
  signed int v1; // ebx
  int v2; // esi
  int v3; // eax

  ++dword_54D440;
  EnterCriticalSection(&stru_54D444);
  while ( dword_54D45C )
  {
    ++dword_54D3F8;
    EnterCriticalSection(&stru_54D3FC);
    v1 = 0;
    if ( dword_54D3C8 > 0 )
    {
      v2 = 0;
      do
      {
        v3 = v2 + dword_54D3D0;
        if ( *(_DWORD *)(v2 + dword_54D3D0 + 44)
          && *(_DWORD *)(v3 + 40)
          && (*(_BYTE *)(v3 + 36) & 0xC) != 0
          && CSS_ChannelIsPlaying(v1) )
        {
          CSS_Channel_ServiceStream(v1);
        }
        ++v1;
        v2 += 52;
      }
      while ( v1 < dword_54D3C8 );
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(&dword_54D3F8 + 1));
    --dword_54D3F8;
    Sleep(1000 / g_CSS_StreamServiceRateHz);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(&dword_54D440 + 1));
  --dword_54D440;
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
  int v1; // ebx
  signed int i; // ecx
  char v3; // dl
  int *v4; // eax
  _DWORD v5[6]; // [esp+Ch] [ebp-18h] BYREF

  result = v5;
  v5[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v1 = 0;
  v5[1] = &j____wcpp_4_fs_handler_rtn_;
  v5[2] = &g_CSSEmptySampleCache_EHScopeTable;
  v5[3] = 0;
  for ( i = 0; i < dword_54D3C8; v1 += 52 )
  {
    result = (_DWORD *)(v1 + dword_54D3D0);
    v3 = *(_BYTE *)(v1 + dword_54D3D0 + 36);
    if ( (v3 & 1) != 0 || (v3 & 2) != 0 )
      result = (_DWORD *)CSS_CloseChannel(i, 0);
    ++i;
  }
  while ( dword_54D3B8 )
  {
    v4 = (int *)dword_54D3B8;
    dword_54D3B8 = *(_DWORD *)(dword_54D3B8 + 20);
    result = (_DWORD *)CSS_SampleCache_FreeEntry(v4);
  }
  return result;
}
// 46E8D1: variable 'i' is possibly undefined
// 54D3B8: using guessed type int dword_54D3B8;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E910) --------------------------------------------------------
void  CSS_Channel_StartMemSound(unsigned int a1, int a2, int a3, int *a4, int a5, signed int a6)
{
  int v8; // edx
  int v9; // ecx

  CSS_Channel_StoreFormatParams(52 * a1 + dword_54D3D0, a4[1]);
  v8 = dword_54D3D0;
  *(_DWORD *)(v9 + dword_54D3D0 + 36) = 1;
  *(_DWORD *)(v9 + v8 + 48) = 0;
  *(_DWORD *)(v9 + v8 + 40) = a2;
  *(_DWORD *)(v8 + v9) = *a4;
  CSS_ChannelQueueSound(a1, *a4, a4[2], a4[3], a4[1]);
  CSS_ChannelSetVolumeImmediate(a1, 0);
  CSS_ChannelBeginVolumeFade(a1, a3, a6);
  CSS_ChannelSetPanning(a1, a5);
}
// 46E937: variable 'v9' is possibly undefined
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E9A0) --------------------------------------------------------
int  CSS_Channel_SelectAndPlay(int *a1, int a2, signed int a3, int a4)
{
  unsigned int v5; // edi
  int v6; // eax
  int v7; // ebx
  int v8; // ecx
  int v9; // esi
  int v10; // esi

  v5 = -1;
  v6 = 0;
  v7 = g_CSS_MemSoundStealBias + g_CSS_VoiceSequenceCounter;
  if ( dword_54D3C8 > 0 )
  {
    v8 = 0;
    do
    {
      v9 = *(_DWORD *)(v8 + dword_54D3D0 + 36);
      if ( g_CSS_ChannelPriorityWeightTable[v9] + *(_DWORD *)(v8 + dword_54D3D0 + 40) < v7 )
      {
        v7 = g_CSS_ChannelPriorityWeightTable[v9] + *(_DWORD *)(v8 + dword_54D3D0 + 40);
        v5 = v6;
      }
      ++v6;
      v8 += 52;
    }
    while ( v6 < dword_54D3C8 );
  }
  if ( v5 == -1 )
    return 0;
  CSS_CloseChannel(v5, 0);
  v10 = g_CSS_VoiceSequenceCounter++;
  CSS_Channel_StartMemSound(v5, v10, a2, a1, a4, a3);
  return v10;
}
// 519C8C: using guessed type int dword_519C8C[];
// 519C90: using guessed type int dword_519C90;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046EA90) --------------------------------------------------------
_DWORD * CSS_CreateSampleCacheEntry(int a1, int a2, _DWORD *a3)
{
  _BYTE *v4; // edi
  char v5; // al
  char v6; // al
  _DWORD *v7; // edi
  _DWORD *v10; // [esp+4h] [ebp-14h] BYREF

  CSS_StreamService_NoOpHook();
  CSS_SampleCache_MakeRoom(a3[1]);
  CSS_Mem_TryAlloc(24, &v10);
  CSS_Mem_TryAlloc(strlen((const char *)a2) + 1, v10 + 4);
  v4 = (_BYTE *)v10[4];
  do
  {
    v5 = *(_BYTE *)a2;
    *v4 = *(_BYTE *)a2;
    if ( !v5 )
      break;
    v6 = *(_BYTE *)(a2 + 1);
    a2 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  CSS_Mem_TryAlloc(a3[1], v10);
  (*(void (**)(void))(*(_DWORD *)a1 + 20))();
  (*(void (**)(void))(*(_DWORD *)dword_54D4B8 + 20))();
  v10[5] = 0;
  v7 = v10 + 1;
  v10[1] = *a3;
  *++v7 = a3[1];
  v7[1] = a3[2];
  if ( dword_54D3B8 )
    CSS_SampleCache_AppendEntry(dword_54D3B8, (int)v10);
  else
    dword_54D3B8 = (int)v10;
  dword_54D3BC += a3[1];
  return v10;
}
// 54D3B8: using guessed type int dword_54D3B8;
// 54D3BC: using guessed type int dword_54D3BC;
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046EB80) --------------------------------------------------------
int  CSS_StartSampleVoice(int a1, int *a2, int a3, int a4, int a5)
{
  unsigned int v6; // edi
  int v7; // eax
  int v8; // ebx
  int v9; // ecx
  int v10; // esi
  int v11; // esi
  int v12; // ebx
  int v13; // eax

  v6 = -1;
  v7 = 0;
  v8 = g_CSS_SampleVoiceStealBias + g_CSS_VoiceSequenceCounter;
  if ( dword_54D3C8 > 0 )
  {
    v9 = 0;
    do
    {
      v10 = *(_DWORD *)(v9 + dword_54D3D0 + 36);
      if ( g_CSS_ChannelPriorityWeightTable[v10] + *(_DWORD *)(v9 + dword_54D3D0 + 40) < v8 )
      {
        v8 = g_CSS_ChannelPriorityWeightTable[v10] + *(_DWORD *)(v9 + dword_54D3D0 + 40);
        v6 = v7;
      }
      ++v7;
      v9 += 52;
    }
    while ( v7 < dword_54D3C8 );
  }
  if ( v6 != -1 )
    CSS_CloseChannel(v6, 0);
  v11 = 52 * v6;
  v12 = dword_54D3CC * a2[2] / 1000;
  v13 = CSS_GetFormatSampleSize(*a2);
  *(_DWORD *)(dword_54D3D0 + v11 + 20) = CSS_FileStream_New(a1, v13 * v12);
  CSS_Channel_StartFileStream(v6, a2, a3, a4, a5, 4);
  *(_DWORD *)(v11 + dword_54D3D0 + 44) = 1;
  CSS_ChannelMarkPlaying(v6);
  return *(_DWORD *)(dword_54D3D0 + 52 * v6 + 40);
}
// 46EB80: could not find valid save-restore pair for ebx
// 519C8C: using guessed type int dword_519C8C[];
// 519C9C: using guessed type int dword_519C9C;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3CC: using guessed type int dword_54D3CC;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046ECB0) --------------------------------------------------------
int __stdcall CSS_ResumeStream(int a1)
{
  int result; // eax
  unsigned int v2; // edx

  result = a1;
  if ( a1 )
  {
    v2 = 0;
    if ( dword_54D3C8 > 0 )
    {
      result = 0;
      while ( a1 != *(_DWORD *)(result + dword_54D3D0 + 40) )
      {
        result += 52;
        ++v2;
        if ( result >= 52 * dword_54D3C8 )
          return result;
      }
      if ( v2 != -1 )
      {
        *(_DWORD *)(result + dword_54D3D0 + 44) = 1;
        return CSS_ChannelMarkPlaying(v2);
      }
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046ED10) --------------------------------------------------------
int  CSS_StartStreamVoice(int a1, int a2, int a3, DWORD a4)
{
  int v7; // ecx
  char v8; // al
  unsigned int v9; // edi
  int v10; // eax
  int v11; // ebx
  int v12; // ecx
  int v13; // esi
  int v14[3]; // [esp+14h] [ebp-24h] BYREF
  _DWORD *v15; // [esp+20h] [ebp-18h]
  int v16; // [esp+24h] [ebp-14h]
  int v17; // [esp+28h] [ebp-10h]

  v17 = a2;
  v16 = a3;
  if ( !dword_54D468 || !dword_54D3D0 || CSS_IsNullSoundDevice() )
    return 0;
  if ( *(_WORD *)(*(_DWORD *)(a1 + 363) + 2) == 1 )
    v8 = 1;
  else
    v8 = 3;
  v14[0] = v8;
  if ( *(_WORD *)(*(_DWORD *)(a1 + 363) + 14) == 16 )
    ++v14[0];
  v14[1] = *(_DWORD *)(a1 + 251);
  v14[2] = *(_DWORD *)(*(_DWORD *)(a1 + 363) + 4);
  v15 = IO_StreamAdapterAlloc(v7, 0, a4);
  if ( !v15 )
    return 0;
  v9 = -1;
  v10 = 0;
  v11 = g_CSS_StreamVoiceStealBias + g_CSS_VoiceSequenceCounter;
  if ( dword_54D3C8 > 0 )
  {
    v12 = 0;
    do
    {
      v13 = *(_DWORD *)(v12 + dword_54D3D0 + 36);
      if ( g_CSS_ChannelPriorityWeightTable[v13] + *(_DWORD *)(v12 + dword_54D3D0 + 40) < v11 )
      {
        v11 = g_CSS_ChannelPriorityWeightTable[v13] + *(_DWORD *)(v12 + dword_54D3D0 + 40);
        v9 = v10;
      }
      ++v10;
      v12 += 52;
    }
    while ( v10 < dword_54D3C8 );
  }
  if ( v9 != -1 )
    CSS_CloseChannel(v9, 0);
  *(_DWORD *)(dword_54D3D0 + 52 * v9 + 20) = v15;
  CSS_Channel_StartFileStream(v9, v14, a4, v17, v16, 8);
  return *(_DWORD *)(52 * v9 + dword_54D3D0 + 40);
}
// 46EDCD: variable 'v7' is possibly undefined
// 519C8C: using guessed type int dword_519C8C[];
// 519CAC: using guessed type int dword_519CAC;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046EE90) --------------------------------------------------------
void __stdcall CSS_LoadSample(int a1)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // esi
  _DWORD v4[4]; // [esp+0h] [ebp-10h] BYREF

  if ( dword_54D468 )
  {
    if ( dword_54D3D0 )
    {
      if ( !CSS_SampleCache_FindAndTouch(a1) )
      {
        v3 = Audio_ReadWavHeaderFromStream(v1, v4);
        if ( v3 )
        {
          if ( v4[1] < dword_54D3C0 )
            CSS_CreateSampleCacheEntry(v3, v2, v4);
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
int __stdcall CSS_PlayMemSound(int a1, int a2, signed int a3, int a4, int a5, int a6, signed int a7)
{
  unsigned int v9; // edi
  int v10; // ebx
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  int v14; // ebx
  int v15; // eax
  int v16; // ecx

  if ( !dword_54D468 || !dword_54D3D0 || CSS_IsNullSoundDevice() )
    return 0;
  v9 = -1;
  v10 = g_CSS_MemSoundStealBias + g_CSS_VoiceSequenceCounter;
  v11 = 0;
  if ( dword_54D3C8 > 0 )
  {
    v12 = 0;
    do
    {
      v13 = *(_DWORD *)(v12 + dword_54D3D0 + 36);
      if ( g_CSS_ChannelPriorityWeightTable[v13] + *(_DWORD *)(v12 + dword_54D3D0 + 40) < v10 )
      {
        v10 = g_CSS_ChannelPriorityWeightTable[v13] + *(_DWORD *)(v12 + dword_54D3D0 + 40);
        v9 = v11;
      }
      ++v11;
      v12 += 52;
    }
    while ( v11 < dword_54D3C8 );
  }
  if ( v9 == -1 )
    return 0;
  CSS_CloseChannel(v9, 0);
  v14 = g_CSS_VoiceSequenceCounter++;
  CSS_Channel_StoreFormatParams(52 * v9 + dword_54D3D0, a2);
  v15 = dword_54D3D0;
  *(_DWORD *)(v16 + dword_54D3D0 + 36) = 1;
  *(_DWORD *)(v16 + v15 + 48) = 0;
  *(_DWORD *)(v16 + v15 + 40) = v14;
  *(_DWORD *)(v16 + v15) = a1;
  CSS_ChannelQueueSound(v9, a1, a3, a4, a2);
  CSS_ChannelSetVolumeImmediate(v9, 0);
  CSS_ChannelBeginVolumeFade(v9, a5, a7);
  CSS_ChannelSetPanning(v9, a6);
  return v14;
}
// 46EFDA: variable 'v16' is possibly undefined
// 519C8C: using guessed type int dword_519C8C[];
// 519C90: using guessed type int dword_519C90;
// 519CB4: using guessed type int dword_519CB4;
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046F040) --------------------------------------------------------
int __stdcall CSS_PlaySound(int a1, int a2, int a3, signed int a4)
{
  int *v6; // eax
  int v7; // esi
  int *v8; // esi
  int v9[7]; // [esp+14h] [ebp-1Ch] BYREF

  if ( !dword_54D468 || !dword_54D3D0 || CSS_IsNullSoundDevice() )
    return 0;
  v6 = (int *)CSS_SampleCache_FindAndTouch(a1);
  if ( v6 )
    return CSS_Channel_SelectAndPlay(v6, a2, a4, a3);
  v7 = Audio_ReadWavHeaderFromStream(a1, v9);
  if ( !v7 )
    return 0;
  if ( v9[1] >= dword_54D3C0 )
    return CSS_StartSampleVoice(v7, v9, a3, a2, a4);
  CSS_PauseStreamReading();
  v8 = CSS_CreateSampleCacheEntry(v7, a1, v9);
  CSS_ResumeStreamReading();
  return CSS_Channel_SelectAndPlay(v8, a2, a4, a3);
}
// 54D3C0: using guessed type int dword_54D3C0;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046F140) --------------------------------------------------------
int __stdcall CSS_StopSound(int a1, signed int a2)
{
  int result; // eax
  unsigned int v3; // ecx
  _DWORD v4[8]; // [esp+0h] [ebp-20h] BYREF

  result = (int)v4;
  v4[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v4[1] = &j____wcpp_4_fs_handler_rtn_;
  v4[2] = &g_CSSStopSound_EHScopeTable;
  v4[3] = 0;
  if ( a1 )
  {
    v3 = 0;
    if ( dword_54D3C8 > 0 )
    {
      result = 0;
      while ( a1 != *(_DWORD *)(dword_54D3D0 + result + 40) )
      {
        result += 52;
        ++v3;
        if ( result >= 52 * dword_54D3C8 )
          return result;
      }
      if ( v3 != -1 )
        return CSS_CloseChannel(v3, a2);
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F1E0) --------------------------------------------------------
int __stdcall CSS_GetSoundPos(int a1)
{
  unsigned int v1; // edx
  int v2; // eax
  unsigned int v3; // ebx
  int v4; // ecx
  unsigned int v6[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( a1 && (v1 = 0, dword_54D3C8 > 0) )
  {
    v2 = 0;
    while ( a1 != *(_DWORD *)(dword_54D3D0 + v2 + 40) )
    {
      v2 += 52;
      ++v1;
      if ( v2 >= 52 * dword_54D3C8 )
        goto LABEL_10;
    }
  }
  else
  {
LABEL_10:
    v1 = -1;
  }
  v3 = v1;
  if ( v1 == -1 )
    return 0;
  v4 = *(_DWORD *)(52 * v1 + dword_54D3D0 + 36);
  if ( v4 == 4 || v4 == 8 )
    v6[0] = (*(int (**)(void))(**(_DWORD **)(dword_54D3D0 + 52 * v1 + 20) + 24))();
  else
    CSS_ChannelGetPlayPosition(v1, v6);
  return v6[0] / *(_DWORD *)(dword_54D3D0 + 52 * v3 + 16);
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F280) --------------------------------------------------------
void __stdcall CSS_SetSoundPos(int a1, int a2)
{
  unsigned int v2; // edx
  int v3; // eax
  unsigned int v4; // ebx
  int v5; // esi
  int v6; // ecx
  _DWORD *v7; // esi
  unsigned int v8; // [esp-4h] [ebp-30h]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-2Ch]
  unsigned int v10[6]; // [esp+14h] [ebp-18h] BYREF

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  if ( a1 && (v2 = 0, dword_54D3C8 > 0) )
  {
    v3 = 0;
    while ( a1 != *(_DWORD *)(dword_54D3D0 + v3 + 40) )
    {
      v3 += 52;
      ++v2;
      if ( v3 >= 52 * dword_54D3C8 )
        goto LABEL_12;
    }
  }
  else
  {
LABEL_12:
    v2 = -1;
  }
  v4 = v2;
  if ( v2 != -1 )
  {
    v5 = dword_54D3D0 + 52 * v2;
    v6 = *(_DWORD *)(v5 + 36);
    if ( v6 == 4 || v6 == 8 )
    {
      ++dword_54D3D8;
      EnterCriticalSection(&CriticalSection);
      ++dword_54D3F8;
      EnterCriticalSection(&stru_54D3FC);
      (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(**(_DWORD **)(v5 + 20) + 28))(
        ExceptionList,
        &j____wcpp_4_fs_handler_rtn_,
        &g_CSSSetSoundPos_EHScopeTable,
        1);
      v7 = (_DWORD *)(52 * v4 + dword_54D3D0);
      if ( *v7 )
      {
        CSS_ChannelGetPlayPosition(v4, v10);
        v8 = v10[0];
        v7[3] = v10[0];
        CSS_ChannelSetPositionOffset(v4, v8);
      }
      CSS_Channel_ServiceStream(v4);
      LeaveCriticalSection(&CriticalSection);
      --dword_54D3D8;
      LeaveCriticalSection(&stru_54D3FC);
      --dword_54D3F8;
    }
    else
    {
      CSS_ChannelSetPlayPosition(v2, *(_DWORD *)(v5 + 16) * a2);
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046F420) --------------------------------------------------------
int __stdcall CSS_PauseSound(int a1, signed int a2)
{
  int result; // eax
  unsigned int v3; // ebx

  result = a1;
  if ( a1 )
  {
    v3 = 0;
    if ( dword_54D3C8 > 0 )
    {
      result = 0;
      while ( a1 != *(_DWORD *)(result + dword_54D3D0 + 40) )
      {
        result += 52;
        ++v3;
        if ( result >= 52 * dword_54D3C8 )
          return result;
      }
      if ( v3 != -1 )
      {
        CSS_ChannelGetVolume(v3, (_DWORD *)(result + dword_54D3D0 + 32));
        return CSS_ChannelBeginVolumeFade(v3, 0, a2);
      }
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F490) --------------------------------------------------------
int __stdcall CSS_ResumeSound(int a1, signed int a2)
{
  int result; // eax
  unsigned int v3; // edx

  result = a1;
  if ( a1 )
  {
    v3 = 0;
    if ( dword_54D3C8 > 0 )
    {
      result = 0;
      while ( a1 != *(_DWORD *)(result + dword_54D3D0 + 40) )
      {
        result += 52;
        ++v3;
        if ( result >= 52 * dword_54D3C8 )
          return result;
      }
      if ( v3 != -1 )
        return CSS_ChannelBeginVolumeFade(v3, *(_DWORD *)(result + dword_54D3D0 + 32), a2);
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F4F0) --------------------------------------------------------
void __stdcall CSS_SetSoundLoop(int a1, int a2, int a3)
{
  unsigned int v3; // edx
  int v4; // eax
  int v5; // ebx
  int v6; // ebp

  if ( a1 )
  {
    v3 = 0;
    if ( dword_54D3C8 > 0 )
    {
      v4 = 0;
      while ( 1 )
      {
        v5 = v4 + dword_54D3D0;
        if ( a1 == *(_DWORD *)(v4 + dword_54D3D0 + 40) )
          break;
        v4 += 52;
        ++v3;
        if ( v4 >= 52 * dword_54D3C8 )
          return;
      }
      if ( v3 != -1 )
      {
        v6 = *(_DWORD *)(v5 + 36);
        if ( v6 == 4 || v6 == 8 )
        {
          (*(void (__fastcall **)(_DWORD, int))(**(_DWORD **)(v5 + 20) + 12))(
            *(_DWORD *)(v5 + 20),
            *(_DWORD *)(v5 + 16) * a2);
        }
        else
        {
          CSS_SetMixChannelLoopPoints(v3, a2, a3);
          *(_DWORD *)(v5 + 36) = 2;
        }
      }
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F580) --------------------------------------------------------
int __stdcall CSS_GetSoundLoop(int a1, _DWORD *a2, _DWORD *a3)
{
  int result; // eax
  unsigned int v4; // ecx
  int v5; // edx
  int v6; // ebx
  int v7; // esi

  result = a1;
  if ( !a1 )
    goto LABEL_10;
  v4 = 0;
  if ( dword_54D3C8 <= 0 )
    goto LABEL_10;
  result = 0;
  while ( 1 )
  {
    v5 = result + dword_54D3D0;
    if ( a1 == *(_DWORD *)(result + dword_54D3D0 + 40) )
      break;
    result += 52;
    ++v4;
    if ( result >= 52 * dword_54D3C8 )
      goto LABEL_10;
  }
  if ( v4 == -1 )
  {
LABEL_10:
    *a2 = 0;
    *a3 = 0;
  }
  else
  {
    v6 = *(_DWORD *)(v5 + 36);
    v7 = result + dword_54D3D0;
    if ( v6 == 4 || v6 == 8 )
    {
      (*(void (**)(void))(**(_DWORD **)(v5 + 20) + 16))();
      *a2 /= *(_DWORD *)(v7 + 16);
      result = *a3 / *(_DWORD *)(v7 + 16);
      *a3 = result;
    }
    else
    {
      return CSS_ChannelGetLoopRange(v4, a2, a3);
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F620) --------------------------------------------------------
int __stdcall CSS_UnLoopSound(int a1)
{
  int result; // eax
  unsigned int v2; // edx
  int v3; // ebx
  int v4; // esi

  result = a1;
  if ( a1 && (v2 = 0, dword_54D3C8 > 0) )
  {
    result = 0;
    while ( a1 != *(_DWORD *)(dword_54D3D0 + result + 40) )
    {
      result += 52;
      ++v2;
      if ( result >= 52 * dword_54D3C8 )
        goto LABEL_11;
    }
  }
  else
  {
LABEL_11:
    v2 = -1;
  }
  if ( v2 != -1 )
  {
    v3 = 52 * v2;
    v4 = *(_DWORD *)(52 * v2 + dword_54D3D0 + 36);
    if ( v4 == 4 || v4 == 8 )
    {
      return (*(int (**)(void))(**(_DWORD **)(dword_54D3D0 + 52 * v2 + 20) + 20))();
    }
    else
    {
      CSS_ClearMixChannelLoopPoints(v2);
      result = dword_54D3D0;
      *(_DWORD *)(v3 + dword_54D3D0 + 36) = 1;
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F6B0) --------------------------------------------------------
void __stdcall CSS_SetSoundRate(int a1, unsigned __int32 a2)
{
  unsigned int v2; // edx
  int v3; // eax

  if ( a1 )
  {
    v2 = 0;
    if ( dword_54D3C8 > 0 )
    {
      v3 = 0;
      while ( a1 != *(_DWORD *)(dword_54D3D0 + v3 + 40) )
      {
        v3 += 52;
        ++v2;
        if ( v3 >= 52 * dword_54D3C8 )
          return;
      }
      if ( v2 != -1 )
        CSS_ChannelSetRate(v2, a2);
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F710) --------------------------------------------------------
int __stdcall CSS_GetSoundRate(int a1)
{
  unsigned int v1; // edx
  int v2; // eax
  _DWORD v4[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !a1 )
    return 0;
  v1 = 0;
  if ( dword_54D3C8 <= 0 )
    return 0;
  v2 = 0;
  while ( a1 != *(_DWORD *)(dword_54D3D0 + v2 + 40) )
  {
    v2 += 52;
    ++v1;
    if ( v2 >= 52 * dword_54D3C8 )
      return 0;
  }
  if ( v1 == -1 )
    return 0;
  CSS_ChannelGetRate(v1, v4);
  return v4[0];
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F770) --------------------------------------------------------
int __stdcall CSS_SetSoundVolume(int a1, int a2, signed int a3)
{
  int result; // eax
  unsigned int v4; // edx

  result = a1;
  if ( a1 )
  {
    v4 = 0;
    if ( dword_54D3C8 > 0 )
    {
      result = 0;
      while ( a1 != *(_DWORD *)(result + dword_54D3D0 + 40) )
      {
        result += 52;
        ++v4;
        if ( result >= 52 * dword_54D3C8 )
          return result;
      }
      if ( v4 != -1 )
      {
        *(_DWORD *)(result + dword_54D3D0 + 32) = a2;
        return CSS_ChannelBeginVolumeFade(v4, a2, a3);
      }
    }
  }
  return result;
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F7D0) --------------------------------------------------------
int __stdcall CSS_GetSoundVolume(int a1)
{
  unsigned int v1; // edx
  int v2; // eax
  _DWORD v4[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !a1 )
    return 0;
  v1 = 0;
  if ( dword_54D3C8 <= 0 )
    return 0;
  v2 = 0;
  while ( a1 != *(_DWORD *)(dword_54D3D0 + v2 + 40) )
  {
    v2 += 52;
    ++v1;
    if ( v2 >= 52 * dword_54D3C8 )
      return 0;
  }
  if ( v1 == -1 )
    return 0;
  CSS_ChannelGetVolume(v1, v4);
  return v4[0];
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F830) --------------------------------------------------------
void __stdcall CSS_SetSoundPanning(int a1, int a2)
{
  unsigned int v2; // edx
  int v3; // eax

  if ( a1 )
  {
    v2 = 0;
    if ( dword_54D3C8 > 0 )
    {
      v3 = 0;
      while ( a1 != *(_DWORD *)(dword_54D3D0 + v3 + 40) )
      {
        v3 += 52;
        ++v2;
        if ( v3 >= 52 * dword_54D3C8 )
          return;
      }
      if ( v2 != -1 )
        CSS_ChannelSetPanning(v2, a2);
    }
  }
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F890) --------------------------------------------------------
int __stdcall CSS_GetSoundPanning(int a1)
{
  unsigned int v1; // edx
  int v2; // eax
  _DWORD v4[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( !a1 )
    return 0;
  v1 = 0;
  if ( dword_54D3C8 <= 0 )
    return 0;
  v2 = 0;
  while ( a1 != *(_DWORD *)(dword_54D3D0 + v2 + 40) )
  {
    v2 += 52;
    ++v1;
    if ( v2 >= 52 * dword_54D3C8 )
      return 0;
  }
  if ( v1 == -1 )
    return 0;
  CSS_ChannelGetPanning(v1, v4);
  return v4[0];
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F8F0) --------------------------------------------------------
BOOL __stdcall CSS_IsPlaying(int a1)
{
  unsigned int v1; // edx
  int v2; // eax

  if ( !a1 )
    return 0;
  v1 = 0;
  if ( dword_54D3C8 <= 0 )
    return 0;
  v2 = 0;
  while ( a1 != *(_DWORD *)(dword_54D3D0 + v2 + 40) )
  {
    v2 += 52;
    ++v1;
    if ( v2 >= 52 * dword_54D3C8 )
      return 0;
  }
  return v1 != -1 && CSS_ChannelIsPlaying(v1);
}
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046F950) --------------------------------------------------------
signed int  CSS_InitVoicePool(int a1, int a2, int a3)
{
  int v6; // ebx
  int v7; // eax
  int v8; // edx
  _BYTE v10[20]; // [esp+14h] [ebp-14h] BYREF

  dword_54D3C8 = a1;
  v6 = 52 * a1;
  CSS_Mem_TryAlloc(52 * a1, &dword_54D3D0);
  if ( a1 > 0 )
  {
    v7 = 0;
    do
    {
      v8 = dword_54D3D0;
      *(_DWORD *)(dword_54D3D0 + v7) = 0;
      v7 += 52;
      *(_DWORD *)(v8 + v7 - 12) = 0;
      *(_DWORD *)(v8 + v7 - 16) = 0;
      *(_DWORD *)(v8 + v7 - 4) = 0;
    }
    while ( v7 < v6 );
  }
  dword_54D3CC = a2;
  dword_54D3C0 = a3 << 10;
  dword_54D414 = 1;
  dword_54D45C = 1;
  hThread = (HANDLE)beginthreadex_(0, v10);
  dword_54D41C = beginthreadex_(0, v10);
  SetThreadPriority((HANDLE)dword_54D41C, 2);
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
  _DWORD v5[3]; // [esp+0h] [ebp-30h] BYREF
  int v6; // [esp+Ch] [ebp-24h]
  int *v7; // [esp+14h] [ebp-1Ch]
  int *v8; // [esp+18h] [ebp-18h]

  result = v5;
  v5[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v5[1] = &j____wcpp_4_fs_handler_rtn_;
  v5[2] = &g_CSSShutdownVoicePool_EHScopeTable;
  v6 = 0;
  if ( dword_54D3D0 )
  {
    dword_54D414 = 0;
    dword_54D45C = 0;
    v7 = &dword_54D420;
    ++dword_54D420;
    EnterCriticalSection(&stru_54D424);
    v6 = 1;
    v8 = &dword_54D440;
    ++dword_54D440;
    EnterCriticalSection(&stru_54D444);
    v6 = 2;
    CRT_WatcomEHUnwindToExceptionList(v2, v1);
    for ( i = 0; i < dword_54D3C8; i = v4 + 1 )
      CSS_CloseChannel(i, 0);
    CSS_EmptySampleCache();
    result = (_DWORD *)CSS_Mem_FreeIfSet(dword_54D3D0);
    dword_54D3D0 = 0;
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
  ++dword_54D3D8;
  EnterCriticalSection(&CriticalSection);
  ++dword_54D3F8;
  EnterCriticalSection(&stru_54D3FC);
  return a1;
}
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046FBC0) --------------------------------------------------------
int  CSS_UnlockAudioThreads(int a1)
{
  LeaveCriticalSection(&CriticalSection);
  --dword_54D3D8;
  LeaveCriticalSection(&stru_54D3FC);
  --dword_54D3F8;
  return a1;
}
// 54D3D8: using guessed type int dword_54D3D8;
// 54D3F8: using guessed type int dword_54D3F8;

//----- (0046FC00) --------------------------------------------------------
int CSS_InitDeviceSearchState()
{
  int v0; // edx
  int v1; // ecx

  dword_54D498 = 0;
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
  return dword_54D468 == (_DWORD)&g_CSS_NullDriverSentinel;
}
// 54D468: using guessed type int dword_54D468;

//----- (0046FC50) --------------------------------------------------------
int CSS_PollAudioDeviceChange()
{
  _DWORD *v0; // eax
  int result; // eax

  v0 = (_DWORD *)(*(int (**)(void))(dword_54D468 + 88))();
  CSS_AdvanceVolumeFades(v0);
  do
    result = (*(int (__cdecl **)(int *))(dword_54D468 + 92))(&dword_54D460);
  while ( !result && dword_54D460 );
  return result;
}
// 54D460: using guessed type int dword_54D460;
// 54D468: using guessed type int dword_54D468;

//----- (0046FC80) --------------------------------------------------------
int __stdcall CSS_DeviceSearchThreadProc(int a1)
{
  ++dword_54D498;
  EnterCriticalSection(&stru_54D49C);
  while ( dword_54D4B4 )
  {
    CSS_PollAudioDeviceChange();
    Sleep(1000 / g_CSS_MixUpdateRateHz);
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)(&dword_54D498 + 1));
  --dword_54D498;
  return 0;
}
// 519CF4: using guessed type int dword_519CF4;
// 54D498: using guessed type int dword_54D498;
// 54D4B4: using guessed type int dword_54D4B4;

//----- (0046FE10) --------------------------------------------------------
int __stdcall CSS_SetDirectSoundHWnd(int a1)
{
  int result; // eax

  result = a1;
  dword_54D470 = a1;
  return result;
}
// 54D470: using guessed type int dword_54D470;

//----- (0046FE20) --------------------------------------------------------
int __stdcall CSS_SetDeviceSearch(int a1)
{
  int result; // eax

  result = a1;
  dword_54D48C = a1;
  return result;
}
// 54D48C: using guessed type int dword_54D48C;

//----- (0046FE30) --------------------------------------------------------
signed int CSS_ResetDeviceConfigDefaults()
{
  signed int result; // eax

  result = 10;
  dword_54D488 = 0;
  dword_54D480 = 0;
  dword_54D478 = 0;
  dword_54D474 = 44100;
  dword_54D47C = -1;
  dword_54D46C = 0;
  g_CSS_MixUpdateRateHz = 10;
  dword_54D468 = 0;
  g_CSS_DSoundAccelDetectEnabled = 1;
  dword_54D490 = (int)CSS_FatalErrorExit;
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
int __stdcall CSS_SetMasterVolume(int a1)
{
  return CSS_SetMixMasterVolume(a1);
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
  dword_54D4B4 = 0;
  ++dword_54D498;
  EnterCriticalSection(&stru_54D49C);
  LeaveCriticalSection((LPCRITICAL_SECTION)(&dword_54D498 + 1));
  --dword_54D498;
  CSS_ResetDeviceHandleCache();
  if ( dword_54D488 )
  {
    CSS_ShutdownVoicePool();
    CSS_FreeMixChannels();
    dword_54D480 = 0;
    (*(void (**)(void))(dword_54D468 + 56))();
    dword_54D488 = 0;
    dword_54D468 = 0;
  }
}
// 54D468: using guessed type int dword_54D468;
// 54D480: using guessed type int dword_54D480;
// 54D488: using guessed type int dword_54D488;
// 54D498: using guessed type int dword_54D498;
// 54D4B4: using guessed type int dword_54D4B4;

//----- (0046FF80) --------------------------------------------------------
int __stdcall CSS_SetFileSystem(int a1)
{
  int result; // eax

  result = a1;
  dword_54D4B8 = a1;
  return result;
}
// 54D4B8: using guessed type int dword_54D4B8;

//----- (0046FF90) --------------------------------------------------------
signed int __stdcall CSS_Init(int a1, int a2, int a3, int a4)
{
  int v4; // ebx
  int v5; // esi
  int v6; // eax
  void *v9; // eax
  int v10; // [esp+14h] [ebp-18h] BYREF
  _BYTE v11[20]; // [esp+18h] [ebp-14h] BYREF

  CSS_ResetDeviceConfigDefaults();
  if ( g_CSS_DeviceHandleCache_DriverIndex == -1 )
  {
    v4 = dword_54D48C;
    if ( dword_54D48C < 3 )
    {
      v5 = 4 * dword_54D48C;
      do
      {
        if ( g_CSS_DeviceHandleCache_DriverIndex != -1 )
          break;
        if ( !(*(int (__cdecl ***)(int *))((char *)&g_CSS_DriverDescriptorTable + v5))[12](&v10) && v10 == 1 )
          g_CSS_DeviceHandleCache_DriverIndex = v4;
        ++v4;
        v5 += 4;
      }
      while ( v4 < 3 );
    }
  }
  else
  {
    (*((void (__cdecl **)(int *))*(&g_CSS_DriverDescriptorTable + g_CSS_DeviceHandleCache_DriverIndex) + 12))(&v10);
  }
  v6 = (int)*(&g_CSS_DriverDescriptorTable + g_CSS_DeviceHandleCache_DriverIndex);
  dword_54D468 = v6;
  if ( g_CSS_DeviceHandleCache_Param1 != -1 )
    *(_DWORD *)(v6 + 8) = g_CSS_DeviceHandleCache_Param1;
  if ( g_CSS_DeviceHandleCache_Param2 != -1 )
    *(_DWORD *)(dword_54D468 + 12) = g_CSS_DeviceHandleCache_Param2;
  if ( g_CSS_DeviceHandleCacheParam3 != -1 )
    *(_DWORD *)(dword_54D468 + 16) = g_CSS_DeviceHandleCacheParam3;
  if ( g_CSS_DeviceHandleCacheParam4 != -1 )
    *(_DWORD *)(dword_54D468 + 20) = g_CSS_DeviceHandleCacheParam4;
  if ( (*(int (__cdecl **)(int, int))(dword_54D468 + 52))(dword_54D474, dword_54D478) )
  {
    dword_54D468 = 0;
    g_CSS_DeviceHandleCache_DriverIndex = -1;
    return 0;
  }
  else
  {
    dword_54D480 = a1;
    dword_54D488 = 1;
    CSS_InitMixChannels(a1);
    CSS_BuildVolumeScaleTable(a2);
    dword_54D4B4 = 1;
    v9 = (void *)beginthreadex_(0, v11);
    SetThreadPriority(v9, 2);
    CSS_InitVoicePool(a1, a3, a4);
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
int __cdecl CSS_QueryWaveOutDevicePresent(_DWORD *a1)
{
  *a1 = waveOutGetNumDevs() != 0;
  return 0;
}

//----- (00470220) --------------------------------------------------------
unsigned int __cdecl CSS_OpenWaveOutDevice(int a1, char a2)
{
  bool v2; // zf
  unsigned int v3; // eax
  MMRESULT v4; // eax
  unsigned int v5; // esi
  int v6; // ebx
  HGLOBAL v7; // eax
  unsigned int result; // eax
  LPVOID v9; // eax
  unsigned int v10; // esi
  int v11; // ebx
  HGLOBAL v12; // eax
  struct wavehdr_tag *v13; // eax
  SIZE_T v14; // edx
  unsigned int v15; // edi
  struct tagWAVEOUTCAPSA pwoc; // [esp+0h] [ebp-58h] BYREF
  WAVEFORMATEX pwfx; // [esp+34h] [ebp-24h] BYREF

  dword_54D768 = 44100;
  dword_54D75C = ((a2 & 1) == 0) + 1;
  if ( (a2 & 4) != 0 )
    LOBYTE(dword_54D75C) = dword_54D75C | 4;
  else
    LOBYTE(dword_54D75C) = dword_54D75C | 8;
  waveOutGetDevCapsA(0xFFFFFFFF, &pwoc, 0x34u);
  if ( (dword_54D75C & 8) != 0 && (pwoc.dwFormats & 0x40) == 0 )
    LOBYTE(dword_54D75C) = dword_54D75C & 0xF7;
  if ( (dword_54D75C & 2) != 0 && SLOBYTE(pwoc.dwFormats) >= 0 && (pwoc.dwFormats & 2) == 0 )
    LOBYTE(dword_54D75C) = dword_54D75C & 0xFD;
  if ( (dword_54D75C & 2) != 0 )
  {
    if ( (dword_54D75C & 8) != 0 )
    {
      if ( (pwoc.dwFormats & 0x800) == 0 )
        dword_54D768 = 22050;
      if ( SLOBYTE(pwoc.dwFormats) >= 0 )
        dword_54D768 = 11025;
      v2 = (pwoc.dwFormats & 8) == 0;
LABEL_17:
      if ( v2 )
        LOBYTE(dword_54D75C) = dword_54D75C & 0xF7;
      goto LABEL_19;
    }
    if ( (pwoc.dwFormats & 0x200) == 0 )
      dword_54D768 = 22050;
    if ( (pwoc.dwFormats & 0x20) == 0 )
      dword_54D768 = 11025;
    if ( (pwoc.dwFormats & 2) == 0 )
      LOBYTE(dword_54D75C) = dword_54D75C & 0xFD;
  }
  else
  {
    if ( (dword_54D75C & 8) != 0 )
    {
      if ( (pwoc.dwFormats & 0x400) == 0 )
        dword_54D768 = 22050;
      if ( (pwoc.dwFormats & 0x40) == 0 )
        dword_54D768 = 11025;
      v2 = (pwoc.dwFormats & 4) == 0;
      goto LABEL_17;
    }
    if ( (pwoc.dwFormats & 0x100) == 0 )
      dword_54D768 = 22050;
    if ( (pwoc.dwFormats & 0x10) == 0 )
      dword_54D768 = 11025;
  }
LABEL_19:
  dword_54D744 = ((dword_54D75C & 8) != 0) + 1;
  if ( (dword_54D75C & 2) != 0 )
    dword_54D744 = 2 * (((dword_54D75C & 8) != 0) + 1);
  dword_54D760 = 8;
  dword_54D754 = 0;
  dword_54D740 = 0;
  v3 = dword_54D744 * (3 * dword_54D768 / (unsigned int)g_CSS_MixUpdateRateHz) / 8 + 15;
  LOBYTE(v3) = v3 & 0xF0;
  pwfx.wFormatTag = 1;
  dwBytes = v3;
  pwfx.nChannels = ((dword_54D75C & 2) != 0) + 1;
  pwfx.nSamplesPerSec = dword_54D768;
  pwfx.nAvgBytesPerSec = dword_54D768 * dword_54D744;
  pwfx.nBlockAlign = dword_54D744;
  if ( (dword_54D75C & 8) != 0 )
    pwfx.wBitsPerSample = 16;
  else
    pwfx.wBitsPerSample = 8;
  pwfx.cbSize = 0;
  v4 = waveOutOpen(&hwo, 0xFFFFFFFF, &pwfx, 0, 0, 0);
  if ( v4 )
    return CSS_TranslateWaveOutError(v4);
  v5 = 0;
  if ( dword_54D760 )
  {
    v6 = 0;
    while ( 1 )
    {
      v7 = GlobalAlloc(0x2002u, dwBytes);
      dword_54D540[v6] = (int)v7;
      if ( !v7 )
        return 2;
      v9 = GlobalLock(v7);
      dword_54D4C0[v6] = (int)v9;
      if ( !v9 )
        return 43;
      ++v5;
      ++v6;
      if ( v5 >= dword_54D760 )
        goto LABEL_50;
    }
  }
  else
  {
LABEL_50:
    v10 = 0;
    if ( dword_54D760 )
    {
      v11 = 0;
      while ( 1 )
      {
        v12 = GlobalAlloc(0x2002u, 0x20u);
        dword_54D640[v11] = (int)v12;
        if ( !v12 )
          return 2;
        v13 = (struct wavehdr_tag *)GlobalLock(v12);
        *(LPWAVEHDR *)((char *)&pwh + v11 * 4) = v13;
        if ( !v13 )
          return 43;
        v13->lpData = (LPSTR)dword_54D4C0[v11];
        v14 = dwBytes;
        v13->dwFlags = 1;
        ++v11;
        v13->dwLoops = 0;
        ++v10;
        v13->dwBufferLength = v14;
        v15 = dword_54D760;
        dword_54D5BC[v11] = 0;
        if ( v10 >= v15 )
          goto LABEL_57;
      }
    }
    else
    {
LABEL_57:
      CSS_InitMixBuffers(dword_54D768, ((dword_54D75C & 2) != 0) + 1);
      result = CSS_SetWaveOutRefillThreshold(100 * g_CSS_MixUpdateRateHz);
      if ( !result )
      {
        switch ( dword_54D75C )
        {
          case 5:
            dword_54D750 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8;
            goto LABEL_60;
          case 6:
            dword_54D750 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM8Stereo;
            goto LABEL_60;
          case 9:
            dword_54D750 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_MixInterleaved16;
            goto LABEL_60;
          case 10:
            dword_54D750 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))Audio_ClipMixBufferToPCM16Stereo;
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
  MMRESULT v0; // eax
  int v1; // ebx
  unsigned int v2; // eax
  int v3; // edx
  unsigned int v4; // esi
  int v5; // ebx
  unsigned int v6; // esi
  int v7; // ebx
  int v8; // esi
  int i; // ebx

  CSS_FreeMixBuffers();
  v0 = waveOutReset(hwo);
  if ( v0 )
    return CSS_TranslateWaveOutError(v0);
  while ( 1 )
  {
    v1 = 1;
    v2 = 0;
    if ( dword_54D760 )
    {
      v3 = 0;
      do
      {
        if ( ((*(LPWAVEHDR *)((char *)&pwh + v3))->dwFlags & 1) == 0 )
          v1 = 0;
        ++v2;
        v3 += 4;
      }
      while ( v2 < dword_54D760 );
    }
    if ( v1 )
      break;
    Sleep(0x14u);
  }
  v4 = 0;
  if ( dword_54D760 )
  {
    v5 = 0;
    do
    {
      if ( dword_54D5C0[v5] )
      {
        v0 = waveOutUnprepareHeader(hwo, *(LPWAVEHDR *)((char *)&pwh + v5 * 4), 0x20u);
        if ( v0 )
          return CSS_TranslateWaveOutError(v0);
      }
      ++v4;
      ++v5;
    }
    while ( v4 < dword_54D760 );
  }
  v0 = waveOutClose(hwo);
  if ( v0 )
    return CSS_TranslateWaveOutError(v0);
  v6 = 0;
  if ( dword_54D760 )
  {
    v7 = 0;
    while ( (GlobalUnlock((HGLOBAL)dword_54D540[v7]) || !GetLastError()) && !GlobalFree((HGLOBAL)dword_54D540[v7]) )
    {
      ++v6;
      ++v7;
      if ( v6 >= dword_54D760 )
        goto LABEL_20;
    }
    return 3;
  }
  else
  {
LABEL_20:
    v8 = 0;
    if ( dword_54D760 )
    {
      for ( i = 0; (GlobalUnlock((HGLOBAL)dword_54D640[i]) || !GetLastError()) && !GlobalFree((HGLOBAL)dword_54D640[i]); ++i )
      {
        if ( ++v8 >= (unsigned int)dword_54D760 )
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
int __cdecl CSS_GetWaveOutFormatFlags(_DWORD *a1)
{
  *a1 = dword_54D75C;
  return 0;
}
// 54D75C: using guessed type int dword_54D75C;

//----- (004707C0) --------------------------------------------------------
int __cdecl CSS_SetWaveOutRefillThreshold(unsigned int a1)
{
  unsigned int v1; // eax

  v1 = 100 * dword_54D768 / a1 + 1;
  LOBYTE(v1) = v1 & 0xFE;
  dword_54D748 = v1;
  dword_54D74C = v1;
  return 0;
}
// 54D748: using guessed type int dword_54D748;
// 54D74C: using guessed type int dword_54D74C;
// 54D768: using guessed type int dword_54D768;

//----- (004707F0) --------------------------------------------------------
unsigned int __cdecl CSS_PumpWaveOutBuffer(_DWORD *a1)
{
  unsigned int v1; // esi
  LPWAVEHDR v2; // eax
  SIZE_T v3; // ebx
  MMRESULT v5; // eax
  HWAVEOUT v6; // [esp-Ch] [ebp-1Ch]
  struct wavehdr_tag *v7; // [esp-8h] [ebp-18h]

  v1 = (unsigned int)dword_54DB98 >> 2;
  if ( (dword_54D75C & 2) != 0 )
    v1 = (unsigned int)dword_54DB98 >> 3;
  while ( 1 )
  {
    v2 = pwh[dword_54D740];
    if ( (v2->dwFlags & 1) == 0 )
      break;
    if ( dword_54D5C0[dword_54D740] )
    {
      v5 = waveOutUnprepareHeader(hwo, v2, 0x20u);
      if ( v5 )
        return CSS_TranslateWaveOutError(v5);
      dword_54D5C0[dword_54D740] = 0;
    }
    v3 = (dwBytes - dword_54D754) / dword_54D744;
    if ( v3 > dword_54D74C )
      v3 = dword_54D74C;
    if ( v3 > v1 )
      v3 = v1;
    dword_54D74C -= v3;
    CSS_TickChannelLevels(dword_54D744, v3);
    dword_54D754 = dword_54D750(v3, dword_54D4C0[dword_54D740], dword_54D754, dword_54DBA0);
    if ( dword_54D754 >= dwBytes )
    {
      pwh[dword_54D740]->dwFlags = 0;
      pwh[dword_54D740]->lpData = (LPSTR)dword_54D4C0[dword_54D740];
      pwh[dword_54D740]->dwBufferLength = dwBytes;
      pwh[dword_54D740]->dwFlags = 0;
      pwh[dword_54D740]->dwLoops = 0;
      v5 = waveOutPrepareHeader(hwo, pwh[dword_54D740], 0x20u);
      if ( v5 )
        return CSS_TranslateWaveOutError(v5);
      v7 = pwh[dword_54D740];
      v6 = hwo;
      dword_54D5C0[dword_54D740] = 1;
      v5 = waveOutWrite(v6, v7, 0x20u);
      if ( v5 )
        return CSS_TranslateWaveOutError(v5);
      dword_54D754 = 0;
      if ( ++dword_54D740 >= (unsigned int)dword_54D760 )
        dword_54D740 = 0;
    }
    if ( !dword_54D74C )
    {
      dword_54D74C = dword_54D748;
      *a1 = 1;
      return 0;
    }
  }
  *a1 = 0;
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
int __cdecl CSS_GetFormatTableValue(int a1)
{
  return g_CSS_FormatShiftTable[a1];
}
// 519E90: using guessed type int dword_519E90[];

//----- (00470A40) --------------------------------------------------------
int __cdecl CSS_GetFormatSampleSize(int a1)
{
  return g_CSS_FormatSampleSizeTable[a1];
}
// 519EAC: using guessed type int dword_519EAC[7];

//----- (00470A50) --------------------------------------------------------
int __cdecl CSS_GetFormatSilenceValue(int a1)
{
  return g_CSS_FormatSilenceValueTable[a1];
}
// 519EC8: using guessed type int dword_519EC8[8];

//----- (00470A60) --------------------------------------------------------
int  CSS_BuildMixLookupTables(int a1, int a2)
{
  int i; // eax
  double v3; // st7
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  int result; // eax
  int v8; // edx
  int v9; // [esp-8h] [ebp-14h]
  int v10; // [esp-4h] [ebp-10h]

  v10 = a1;
  v9 = a2;
  for ( i = 0; i < 0x8000; i = v4 + 1 )
  {
    v3 = (double)i / g_CSS_MixLookupIndexScale + g_CSS_MixLookupIndexBias;
    _CHP(v9, v10);
    if ( v4 - (int)v3 > v6 )
      *(int *)((char *)&dword_54D770 + v5) = v4;
  }
  for ( result = 0; result != 128; dword_54D968[result] = v8 - 1 )
    v8 = -dword_54D76C[result++];
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
int __cdecl CSS_InitMixBuffers(int a1, int a2)
{
  int v2; // eax
  int v3; // ebx
  int v4; // ecx
  int v5; // eax
  int v6; // ecx

  dword_54DB9C = a1;
  dword_54DBA4 = a2;
  dword_54DB80 = 0;
  dword_54DB78 = 0;
  dword_54DB90 = 0;
  dword_54DB6C = 0;
  dword_54DB74 = 0;
  dword_54DB88 = 64;
  dword_54DB84 = 5 * a1 / (unsigned int)g_CSS_MixUpdateRateHz;
  if ( a2 == 2 )
    dword_54DB84 = 2 * (5 * a1 / (unsigned int)g_CSS_MixUpdateRateHz);
  v2 = 4 * dword_54DB84 + 15;
  LOBYTE(v2) = v2 & 0xF0;
  dword_54DB98 = v2;
  v3 = v2 + 34832;
  CSS_Mem_TryAlloc(v2 + 34832, &dword_54DB70);
  memset_(v4, 0);
  v5 = dword_54DB70 + 1023;
  LOWORD(v5) = (dword_54DB70 + 1023) & 0xFC00;
  dword_54DB8C = v5;
  dword_54DBA0 = v5 + 33792;
  CSS_Mem_TryAlloc(160, &dword_54DB94);
  return CSS_BuildMixLookupTables(v6, v3);
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
  CSS_Mem_FreeIfSet(dword_54DB70);
  return CSS_Mem_FreeIfSet(dword_54DB94);
}
// 54DB70: using guessed type int dword_54DB70;
// 54DB94: using guessed type int dword_54DB94;

//----- (00470BF0) --------------------------------------------------------
int __cdecl CSS_GetMixSampleRate(_DWORD *a1)
{
  int result; // eax

  result = dword_54DB9C;
  *a1 = dword_54DB9C;
  return result;
}
// 54DB9C: using guessed type int dword_54DB9C;

//----- (00470C00) --------------------------------------------------------
int __cdecl CSS_InitMixChannels(int a1)
{
  int result; // eax

  dword_54DB78 = 0;
  dword_54DB80 = a1;
  dword_54DB6C = 0;
  dword_54DB74 = 0;
  CSS_Mem_TryAlloc(108 * a1, &dword_54DB90);
  result = CSS_ResetAllMixChannels();
  dword_54DB78 = 1;
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

  if ( dword_54DB80 )
  {
    dword_54DB78 = 0;
    result = CSS_Mem_FreeIfSet(dword_54DB90);
    dword_54DB80 = 0;
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

  for ( i = 0; i < dword_54DB80; ++i )
    result = CSS_ResetMixChannelRecord(i);
  return result;
}
// 54DB80: using guessed type int dword_54DB80;

//----- (00470CD0) --------------------------------------------------------
int __cdecl CSS_SetMixIdleChannelFlag(int a1)
{
  int result; // eax

  result = a1;
  dword_54DB6C = a1;
  return result;
}
// 54DB6C: using guessed type int dword_54DB6C;

//----- (00470CE0) --------------------------------------------------------
int __cdecl CSS_SetMixSuspended(int a1)
{
  int result; // eax

  result = a1;
  dword_54DB74 = a1;
  return result;
}
// 54DB74: using guessed type int dword_54DB74;

//----- (00470CF0) --------------------------------------------------------
int __cdecl CSS_SetMixMasterVolume(int a1)
{
  int result; // eax

  result = a1;
  dword_54DB88 = a1;
  return result;
}
// 54DB88: using guessed type int dword_54DB88;

//----- (00470D00) --------------------------------------------------------
int __cdecl CSS_GetMixMasterVolume(_DWORD *a1)
{
  int result; // eax

  result = dword_54DB88;
  *a1 = dword_54DB88;
  return result;
}
// 54DB88: using guessed type int dword_54DB88;

//----- (00470D10) --------------------------------------------------------
int __cdecl CSS_BuildVolumeScaleTable(int a1)
{
  int v1; // esi
  int v2; // ecx
  int v3; // ebx
  int v4; // eax
  int result; // eax
  int v6; // [esp+0h] [ebp-18h]
  int v7; // [esp+4h] [ebp-14h]

  v1 = dword_54DB8C;
  if ( dword_54DB8C )
  {
    dword_54DB7C = a1;
    v7 = 0;
    v6 = 0;
    do
    {
      v2 = -128;
      v3 = -512 * v7;
      do
      {
        v4 = v3 * a1 / (32 * dword_54DB80);
        v1 += 4;
        ++v2;
        v3 += v6;
        *(_DWORD *)(v1 - 4) = v4;
      }
      while ( v2 < 128 );
      result = v7 + 1;
      v6 += 4;
      v7 = result;
    }
    while ( result < 33 );
  }
  return result;
}
// 54DB7C: using guessed type int dword_54DB7C;
// 54DB80: using guessed type int dword_54DB80;
// 54DB8C: using guessed type int dword_54DB8C;

//----- (00470DC0) --------------------------------------------------------
int __cdecl CSS_ResetMixChannelRecord(int a1)
{
  int v1; // edx
  int result; // eax

  v1 = 108 * a1;
  result = dword_54DB90;
  *(_DWORD *)(v1 + dword_54DB90 + 96) = 0;
  *(_DWORD *)(v1 + result + 68) = 0;
  *(_DWORD *)(v1 + result + 72) = 0;
  *(_DWORD *)(v1 + result + 4) = 0;
  *(_DWORD *)(v1 + result + 60) = 0;
  *(_DWORD *)(v1 + result + 64) = 1;
  *(_DWORD *)(v1 + result + 76) = 0;
  *(_DWORD *)(v1 + result + 92) = 0;
  *(_DWORD *)(v1 + result + 104) = 0;
  *(_DWORD *)(v1 + result + 48) = 0;
  *(_DWORD *)(v1 + result + 12) = 0;
  *(_DWORD *)(v1 + result + 16) = 0;
  *(_DWORD *)(v1 + result + 20) = 0;
  *(_DWORD *)(v1 + result + 24) = 0;
  *(_DWORD *)(v1 + result + 8) = 0;
  return result;
}
// 54DB90: using guessed type int dword_54DB90;

//----- (00470E60) --------------------------------------------------------
void __cdecl CSS_StartMixChannelPlayback(unsigned int a1, int a2)
{
  if ( a1 < dword_54DB80 )
  {
    *(_DWORD *)(dword_54DB90 + 108 * a1 + 96) = 2;
    CSS_ChannelSetRate(a1, a2);
    CSS_ChannelSetPlayPosition(a1, 0);
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470EC0) --------------------------------------------------------
void __cdecl CSS_SetMixChannelLoopPoints(unsigned int a1, int a2, int a3)
{
  int v3; // ecx
  unsigned int v4; // eax
  int v5; // edx
  unsigned int v6; // eax
  int v7; // edx

  v3 = a3;
  if ( a1 < dword_54DB80 )
  {
    v4 = 108 * a1;
    v5 = dword_54DB90;
    *(_DWORD *)(dword_54DB90 + v4 + 12) = 1;
    *(_DWORD *)(v5 + v4 + 16) = a2;
    if ( a3 == -1 )
      v3 = *(_DWORD *)(v5 + v4 + 8);
    v6 = 108 * a1;
    v7 = dword_54DB90;
    *(_DWORD *)(dword_54DB90 + v6 + 20) = v3;
    *(_DWORD *)(v7 + v6 + 24) = 1;
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470F40) --------------------------------------------------------
unsigned int __cdecl CSS_ClearMixChannelLoopPoints(unsigned int a1)
{
  unsigned int result; // eax
  int v2; // edx

  if ( a1 < dword_54DB80 )
  {
    result = 108 * a1;
    v2 = dword_54DB90;
    *(_DWORD *)(dword_54DB90 + result + 12) = 0;
    *(_DWORD *)(v2 + result + 16) = 0;
    *(_DWORD *)(v2 + result + 20) = 0;
    *(_DWORD *)(v2 + result + 24) = 0;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00470F90) --------------------------------------------------------
int __cdecl CSS_ChannelGetLoopRange(unsigned int a1, _DWORD *a2, _DWORD *a3)
{
  int result; // eax

  if ( a1 < dword_54DB80 )
  {
    *a2 = *(_DWORD *)(dword_54DB90 + 108 * a1 + 16);
    result = *(_DWORD *)(dword_54DB90 + 108 * a1 + 20);
    *a3 = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471030) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelMarkIdle(unsigned int a1)
{
  unsigned int result; // eax

  if ( a1 < dword_54DB80 )
  {
    result = 108 * a1;
    *(_DWORD *)(dword_54DB90 + 108 * a1 + 96) = 0;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471070) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelMarkPlaying(unsigned int a1)
{
  unsigned int result; // eax

  if ( a1 < dword_54DB80 )
  {
    result = 108 * a1;
    *(_DWORD *)(dword_54DB90 + 108 * a1 + 96) = 3;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004710B0) --------------------------------------------------------
BOOL __cdecl CSS_ChannelIsPlaying(unsigned int a1)
{
  unsigned int v1; // eax

  if ( a1 >= dword_54DB80 )
    return 0;
  v1 = dword_54DB90 + 108 * a1;
  return *(_DWORD *)(v1 + 96) == 3 || *(_DWORD *)(v1 + 96) == 2;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471100) --------------------------------------------------------
int __cdecl CSS_ChannelBeginVolumeFade(unsigned int a1, int a2, signed int a3)
{
  signed int v3; // ebx
  _DWORD *v4; // ecx
  int result; // eax

  v3 = a3;
  if ( a1 < dword_54DB80 )
  {
    v4 = (_DWORD *)(108 * a1 + dword_54DB90);
    if ( !a3 )
      v3 = 1;
    v4[21] = 1000 * (1000 * a2 - v4[20]) / (g_CSS_MixUpdateRateHz * v3);
    result = 1000 * a2;
    v4[22] = 1000 * a2;
    if ( (int)v4[21] > 0 && !v4[20] && !v4[24] )
      v4[24] = 3;
  }
  return result;
}
// 519CF4: using guessed type int dword_519CF4;
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004711F0) --------------------------------------------------------
_DWORD * CSS_AdvanceVolumeFades(_DWORD *result)
{
  int v1; // ebx
  int v2; // ecx
  int v3; // edx

  v1 = 0;
  if ( dword_54DB80 > 0 )
  {
    v2 = 0;
    do
    {
      result = (_DWORD *)(v2 + dword_54DB90);
      v3 = *(_DWORD *)(v2 + dword_54DB90 + 80);
      if ( *(int *)(v2 + dword_54DB90 + 84) <= 0 )
      {
        if ( (int)result[21] < 0 )
        {
          v3 += result[21];
          if ( v3 <= result[22] )
          {
            result[21] = 0;
            v3 = result[22];
            if ( !v3 && result[24] == 3 )
              result[24] = 0;
          }
        }
      }
      else
      {
        v3 += result[21];
        if ( v3 >= result[22] )
        {
          result[21] = 0;
          v3 = result[22];
        }
      }
      result[20] = v3;
      ++v1;
      v2 += 108;
    }
    while ( v1 < dword_54DB80 );
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471260) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelSetRate(unsigned int a1, int a2)
{
  unsigned int result; // eax

  if ( a1 < dword_54DB80 )
  {
    result = dword_54DB90 + 108 * a1;
    *(_DWORD *)(result + 60) = a2;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004712A0) --------------------------------------------------------
void __cdecl CSS_ChannelGetRate(unsigned int a1, _DWORD *a2)
{
  unsigned int v2; // eax

  if ( a1 < dword_54DB80 )
  {
    v2 = dword_54DB90 + 108 * a1;
    if ( *(_DWORD *)(v2 + 96) > 1u )
      *a2 = *(_DWORD *)(v2 + 60);
    else
      *a2 = 0;
  }
}
// 4712D7: simplified comparisons for '[ds.2:(eax.4+#0x60.4)].4': !=0 && !=1 became >=2u
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004712F0) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelSetVolumeImmediate(unsigned int a1, int a2)
{
  unsigned int result; // eax

  result = a1;
  if ( a1 < dword_54DB80 )
  {
    result = 108 * a1;
    *(_DWORD *)(dword_54DB90 + 108 * a1 + 80) = 1000 * a2;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471350) --------------------------------------------------------
unsigned int __cdecl CSS_ChannelGetVolume(unsigned int a1, _DWORD *a2)
{
  unsigned int result; // eax

  if ( a1 < dword_54DB80 )
  {
    result = *(_DWORD *)(dword_54DB90 + 108 * a1 + 80) / 0x3E8u;
    *a2 = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (004713A0) --------------------------------------------------------
void __cdecl CSS_ChannelAssignQueueSlot(unsigned int a1, int a2)
{
  _DWORD *v2; // edx
  int v3; // eax

  if ( a1 < dword_54DB80 )
  {
    v2 = (_DWORD *)(108 * a1 + dword_54DB90);
    v3 = dword_54DB94 + 40 * (a2 - 1);
    v2[17] = a2;
    v2[18] = 1;
    if ( *(_DWORD *)(v3 + 12) == 5 && v2[24] == 1 )
    {
      v2[24] = 3;
      CSS_ChannelSetPlayPosition(a1, *(_DWORD *)(v3 + 16));
    }
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;
// 54DB94: using guessed type int dword_54DB94;

//----- (00471430) --------------------------------------------------------
void __cdecl CSS_ChannelQueueSound(unsigned int a1, int a2, signed int a3, int a4, int a5)
{
  unsigned int v5; // ebx

  v5 = CSS_QueueSoundDescriptor(a2, a3, a5);
  CSS_ResetMixChannelRecord(a1);
  CSS_ChannelAssignQueueSlot(a1, v5);
  CSS_StartMixChannelPlayback(a1, a4);
}

//----- (00471480) --------------------------------------------------------
unsigned int __cdecl CSS_QueueSoundDescriptor(int a1, signed int a2, int a3)
{
  unsigned int v3; // edx
  unsigned int v4; // esi
  _DWORD *v5; // ebx
  char v6; // al

  v3 = g_CSS_SoundDescriptorRingIndex + 1;
  g_CSS_SoundDescriptorRingIndex = v3;
  v4 = v3;
  if ( v3 >= 4 )
    g_CSS_SoundDescriptorRingIndex = 0;
  v5 = (_DWORD *)(40 * (v3 - 1) + dword_54DB94);
  *v5 = a1;
  v6 = CSS_GetFormatTableValue(a3);
  v5[3] = 0;
  v5[4] = 0;
  v5[5] = 0;
  v5[6] = 0;
  v5[7] = 0;
  v5[8] = 0;
  v5[9] = 0;
  v5[1] = a3;
  v5[2] = a2 >> v6;
  return v4;
}
// 519E38: using guessed type int dword_519E38;
// 54DB94: using guessed type int dword_54DB94;

//----- (00471560) --------------------------------------------------------
_DWORD *__cdecl CSS_ChannelLoadQueuedSound(int a1)
{
  _DWORD *result; // eax
  _DWORD *v2; // edx

  result = (_DWORD *)(dword_54DB90 + 108 * a1);
  v2 = (_DWORD *)(dword_54DB94 + 40 * (result[17] - 1));
  *result = *v2;
  result[2] = v2[2];
  result[3] = v2[3];
  result[4] = v2[4];
  result[5] = v2[5];
  result[6] = v2[6];
  result[7] = v2[7];
  result[8] = v2[8];
  result[9] = v2[9];
  result[10] = 0;
  result[11] = 0;
  result[18] = 0;
  result[1] = v2[1];
  return result;
}
// 54DB90: using guessed type int dword_54DB90;
// 54DB94: using guessed type int dword_54DB94;

//----- (00471610) --------------------------------------------------------
void __cdecl CSS_ChannelSetPlayPosition(unsigned int a1, unsigned int a2)
{
  int *v2; // ebx
  unsigned int v3; // esi
  unsigned int v4; // eax
  unsigned int v5; // eax

  if ( a1 < dword_54DB80 )
  {
    v2 = (int *)(dword_54DB90 + 108 * a1);
    v3 = a2 >> CSS_GetFormatTableValue(v2[1]);
    if ( !v2[18] || (CSS_ChannelLoadQueuedSound(a1), v2[3] == 2) || v2[3] == 3 || v2[24] != 4 )
    {
      if ( v2[17] && v2[15] )
      {
        switch ( v2[24] )
        {
          case 1:
          case 2:
          case 3:
            v2[25] = 1;
            v4 = v2[6];
            if ( v4 )
            {
              if ( v4 > 1 )
              {
                if ( v4 == 2 )
                {
                  if ( v3 < v2[5] )
                  {
                    v2[12] = v3;
                    v2[16] = 1;
                  }
                  else
                  {
                    v2[12] = v2[5];
                    v2[16] = -1;
                  }
                  v2[13] = 0;
                  v2[24] = 3;
                }
              }
              else
              {
                if ( v3 >= v2[5] )
                  v2[12] = v2[4];
                else
                  v2[12] = v3;
                v2[13] = 0;
                v2[16] = 1;
                v2[24] = 3;
              }
            }
            else
            {
              if ( v3 >= v2[2] )
                goto LABEL_10;
              v2[12] = v3;
              v2[13] = 0;
              v2[16] = 1;
              v2[24] = 3;
            }
            break;
          case 4:
            v2[25] = 2;
            v5 = v2[9];
            if ( v5 )
            {
              if ( v5 > 1 )
              {
                if ( v5 == 2 )
                {
                  if ( v3 < v2[8] )
                  {
                    v2[12] = v3;
                    v2[16] = 1;
                  }
                  else
                  {
                    v2[12] = v2[8];
                    v2[16] = -1;
                  }
                  v2[13] = 0;
                  v2[24] = 3;
                }
              }
              else
              {
                if ( v3 >= v2[8] )
                  v2[12] = v2[7];
                else
                  v2[12] = v3;
                v2[13] = 0;
                v2[16] = 1;
                v2[24] = 3;
              }
            }
            else
            {
              if ( v3 >= v2[2] )
                goto LABEL_10;
              v2[12] = v3;
              v2[13] = 0;
              v2[16] = 1;
              v2[24] = 3;
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
      v2[24] = 1;
    }
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471800) --------------------------------------------------------
int __cdecl CSS_ChannelGetPlayPosition(unsigned int a1, _DWORD *a2)
{
  unsigned int v2; // ebx
  int result; // eax

  if ( a1 < dword_54DB80 )
  {
    v2 = 108 * a1 + dword_54DB90;
    result = *(_DWORD *)(v2 + 48) << CSS_GetFormatTableValue(*(_DWORD *)(v2 + 4));
    *a2 = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471890) --------------------------------------------------------
void __cdecl CSS_ChannelSetPanning(unsigned int a1, int a2)
{
  int v2; // ecx
  unsigned int v3; // eax

  v2 = a2;
  if ( a1 < dword_54DB80 )
  {
    v3 = 108 * a1 + dword_54DB90;
    if ( *(_DWORD *)(v3 + 4) != 1 && *(_DWORD *)(v3 + 4) != 2 && *(_DWORD *)(v3 + 4) != 5 && a2 == 128 )
      v2 = 0;
    *(_DWORD *)(dword_54DB90 + 108 * a1 + 76) = v2;
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471910) --------------------------------------------------------
int __cdecl CSS_ChannelGetPanning(unsigned int a1, _DWORD *a2)
{
  int result; // eax

  if ( a1 < dword_54DB80 )
  {
    result = *(_DWORD *)(dword_54DB90 + 108 * a1 + 76);
    *a2 = result;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471990) --------------------------------------------------------
void  CSS_TickChannelLevels(int a1, int a2)
{
  unsigned int v2; // ebx
  int v3; // esi

  if ( !dword_54DB74 && dword_54DB80 && dword_54DB78 )
  {
    v2 = 0;
    if ( dword_54DB80 )
    {
      v3 = 0;
      do
      {
        if ( !*(_DWORD *)(v3 + dword_54DB90 + 92) && !dword_54DB6C )
          a1 = 1000;
        v3 += 108;
        Audio_MixResampledVoice((int *)a1);
        a1 = dword_54DB80;
        ++v2;
      }
      while ( v2 < dword_54DB80 );
    }
  }
  else
  {
    Audio_ClearGlobalMixBuffer(a2);
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
unsigned int __cdecl CSS_ChannelInitPlayback(unsigned int a1, int a2, unsigned int a3, int a4, unsigned int a5)
{
  unsigned int result; // eax
  _DWORD *v6; // ebx

  result = a1;
  if ( a1 < dword_54DB80 )
  {
    v6 = (_DWORD *)(108 * a1 + dword_54DB90);
    *v6 = a2;
    v6[3] = 1;
    v6[13] = 0;
    v6[12] = v6[13];
    v6[8] = 0;
    v6[7] = v6[8];
    v6[9] = 0;
    v6[4] = 0;
    v6[6] = 1;
    v6[5] = a3 >> CSS_GetFormatTableValue(a4);
    v6[2] = a3 >> CSS_GetFormatTableValue(a4);
    result = a5;
    v6[15] = a5;
    v6[16] = 1;
    v6[17] = 5;
    v6[18] = 0;
    v6[19] = 0;
    v6[20] = 64000;
    v6[21] = 0;
    v6[22] = 0;
    v6[23] = 0;
    v6[25] = 1;
    v6[14] = 0;
    v6[1] = a4;
    v6[10] = 0;
    v6[11] = 0;
    v6[24] = 3;
  }
  return result;
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471B40) --------------------------------------------------------
void __cdecl CSS_ChannelStop(unsigned int a1)
{
  CSS_ChannelMarkIdle(a1);
}

//----- (00471BA0) --------------------------------------------------------
void __cdecl CSS_ChannelSetPositionOffset(unsigned int a1, unsigned int a2)
{
  unsigned int v2; // ebx

  if ( a1 < dword_54DB80 )
  {
    v2 = 108 * a1 + dword_54DB90;
    *(_DWORD *)(v2 + 56) = a2 >> CSS_GetFormatTableValue(*(_DWORD *)(v2 + 4));
  }
}
// 54DB80: using guessed type int dword_54DB80;
// 54DB90: using guessed type int dword_54DB90;

//----- (00471BF0) --------------------------------------------------------
char  Compat_StringHolderDestructor(_DWORD *a1)
{
  Compat_StringHolderFreeText(a1);
  return 0;
}

//----- (00471C40) --------------------------------------------------------
int Compat_StringHolderFreeText(_DWORD *a1)
{
  if ( a1 )
  {
    if ( *a1 )
      j__nfree_(*a1);
    *a1 = 0;
  }
  return 0;
}

//----- (00471C60) --------------------------------------------------------
int  Compat_StringHolderScalarDeletingDtor(int a1, char a2)
{
  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_CompatStringHolder_DtorArrayDescriptor);
    j_j__nfree_();
    return a1;
  }
  *(_DWORD *)(a1 + 4) = &g_CompatStringHolder_Vtable;
  Compat_StringHolderFreeText((_DWORD *)a1);
  if ( (a2 & 2) != 0 )
    j__nfree_(a1);
  return a1;
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
_DWORD * Compat_StringHolderConstructJoined(_DWORD *a1, _DWORD *a2, const char *a3)
{
  a1[0] = 0;
  a1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderAssignJoined(a1, Compat_StringHolderGetText(a2), a3);
  a1[1] = &g_PathEntry_Vtable;
  return a1;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00471D10) --------------------------------------------------------
const char ** Compat_StringHolderAppendText(const char **a1, const char *a2)
{
  _DWORD *holder;

  holder = (_DWORD *)(uintptr_t)a1;
  if ( a2 && *a2 )
    Compat_StringHolderAssignJoined(holder, Compat_StringHolderGetText(holder), a2);
  return a1;
}

//----- (00471DE0) --------------------------------------------------------
const char ** Compat_StringHolderPrependText(const char **a1, const char *a2)
{
  _DWORD *holder;

  holder = (_DWORD *)(uintptr_t)a1;
  if ( a2 && *a2 )
    Compat_StringHolderAssignJoined(holder, a2, Compat_StringHolderGetText(holder));
  return a1;
}

//----- (00471EE0) --------------------------------------------------------
int  Compat_StringHolderFindSubstringOffset(_DWORD *a1, int a2, int a3)
{
  int v4; // eax
  _DWORD *v5; // ecx

  if ( a2 && *a1 && (v4 = ((int (__cdecl *)(int))strstr_)(a3)) != 0 )
    return v4 - *v5;
  else
    return -1;
}
// 471EFD: variable 'v5' is possibly undefined

//----- (00471F10) --------------------------------------------------------
const char ** Compat_StringHolderUppercaseInPlace(const char **a1, unsigned int a2)
{
  const char *v3; // eax

  v3 = Compat_StringHolderGetText((_DWORD *)a1);
  if ( v3 && *v3 )
  {
    Compat_StringHolderAssignJoined((_DWORD *)a1, v3, 0);
    Compat_StruprAsciiInPlace((char *)Compat_StringHolderGetText((_DWORD *)a1));
  }
  return a1;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 47BBE3: using guessed type int __fastcall strupr_(_DWORD, _DWORD);

//----- (00472120) --------------------------------------------------------
int  Compat_StringHolderFindCharFrom(const char **a1, char a2, signed int a3)
{
  const char *text;
  const char *match;
  unsigned int text_len;

  text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a1);
  if ( !text || !*text || a3 < 0 )
    return -1;
  text_len = (unsigned int)strlen(text);
  if ( (unsigned int)a3 >= text_len )
    return -1;
  match = strchr(text + a3, a2);
  if ( !match )
    return -1;
  return (int)(match - text);
}

//----- (00472190) --------------------------------------------------------
int  Compat_StringHolderFindLastBackslash(_BYTE **a1)
{
  const char *text;
  char *last_slash;

  text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a1);
  if ( !text || !*text )
    return -1;
  last_slash = Compat_StrrchrChar(text, '\\');
  if ( !last_slash )
    return -1;
  return (int)(last_slash - text);
}

//----- (004721C0) --------------------------------------------------------
int  Compat_StringHolderFindLastBackslashBefore(char **a1, signed int a2)
{
  _DWORD *holder;
  char *text;
  unsigned int text_len;
  char saved_char;
  char *last_slash;

  holder = (_DWORD *)(uintptr_t)a1;
  text = (char *)Compat_StringHolderGetText(holder);
  if ( !text || !*text || a2 < 0 )
    return -1;
  text_len = (unsigned int)strlen(text);
  if ( (unsigned int)a2 >= text_len )
    return -1;
  saved_char = text[a2 + 1];
  text[a2 + 1] = 0;
  last_slash = Compat_StrrchrChar(text, '\\');
  text[a2 + 1] = saved_char;
  if ( !last_slash )
    return -1;
  return (int)(last_slash - text);
}

//----- (00472230) --------------------------------------------------------
char ** Compat_StringHolderRemoveRange(char **a1, int a2, unsigned int a3, int a4)
{
  _DWORD *holder;
  const char *text;
  unsigned int text_len;
  char *copy;

  holder = (_DWORD *)(uintptr_t)a1;
  text = Compat_StringHolderGetText(holder);
  if ( !text || !*text || a2 < 0 )
    return a1;
  text_len = (unsigned int)strlen(text);
  a3 = text_len;
  if ( text_len != (unsigned int)a4 )
  {
    copy = (char *)(uintptr_t)(unsigned int)j_Mem_Alloc(a3 + 1);
    if ( !copy )
      return a1;
    Compat_CopyPrefixN(copy, text, a2);
    copy[a2] = 0;
    if ( (unsigned int)(a2 + a4) < text_len )
      Compat_CopyPrefixN(copy + a2, text + a2 + a4, text_len - (unsigned int)(a2 + a4) + 1);
    Compat_StringHolderFreeText(holder);
    *holder = (int)(uintptr_t)copy;
    j_j__nfree_();
    return a1;
  }
  Compat_StringHolderDestructor((const char **)holder);
  return a1;
}
// 47228D: variable 'v9' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00472320) --------------------------------------------------------
const char ** Compat_StringHolderInsertTextChecked(const char **result, signed int a2, const char *a3)
{
  if ( a2 >= 0 && a3 && *a3 )
    Compat_StringHolderInsertText((_DWORD *)result, a2, a3);
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
void  __noreturn CRT_ExitProcessWithFinalizers(int a1, int a2, int a3)
{
  (void)a2;
  (void)a3;

  /*
   * The original CRT finalizer band is still under-recovered and currently
   * crashes inside `sub_4B52E6` on fatal quit paths under WSL. For process
   * termination we only need a reliable exit, so quarantine the finalizer walk
   * until its object-registration contract is reconstructed safely.
   */
  ExitProcess((UINT)a1);
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
  UINT v5; // ebx
  int v6; // ecx

  g_CRT_ExitFinalizerCallbackA(a3, a1);
  g_CRT_ExitFinalizerCallbackB(a2);
  if ( g_CRT_ExitProcessFinalizerHook )
    g_CRT_ExitProcessFinalizerHook();
  v5 = v3;
  if ( dword_54DD90 )
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
  ExitProcess(v5);
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
  dword_54DBA8 = nmalloc_(0x7D0, 0);
  if ( !dword_54DBA8 )
  {
    Rules_PrintErrorID((int)aMemory, 1, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutOfMemory_, v3);
    IO_RunRouterExitCallbacks();
  }
  for ( result = 0; result != 2000; result += 4 )
    *(_DWORD *)(dword_54DBA8 + result) = 0;
  return result;
}
// 472605: variable 'v3' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472620) --------------------------------------------------------
signed int  Mem_HeapAllocWithRetry(_DWORD *a1)
{
  int request_size;
  int grow_size;
  signed int result; // eax
  signed int (__fastcall *allocator_callback)(int);

  request_size = (int)(uintptr_t)a1;
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
int unknown_libname_4(int a1)
{
  int previous_handler;

  previous_handler = (int)(intptr_t)g_Mem_OutOfMemoryHandler;
  g_Mem_OutOfMemoryHandler = (signed int (*)())(intptr_t)a1;
  return previous_handler;
}

//----- (00472710) --------------------------------------------------------
signed int  Mem_ReleasePoolBlock(int a1, int a2)
{
  int v2; // ecx
  signed int result; // eax
  int v4; // ecx

  if ( Mem_PoolFreeCoalesce(a1, a2) )
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
_DWORD * Mem_Realloc(char *a1, unsigned int a2, unsigned int a3)
{
  _DWORD *v5; // eax
  int v6; // edx
  int v7; // edi
  unsigned int v8; // eax
  _DWORD *v9; // edx
  char *v10; // ecx
  char v11; // bl
  _BYTE *v12; // edx
  _DWORD *v14; // [esp+0h] [ebp-10h]

  if ( a3 )
    v5 = Mem_SmallBlockAlloc(a3);
  else
    v5 = 0;
  v14 = v5;
  if ( a1 )
  {
    if ( a2 >= a3 )
      v6 = a3;
    else
      v6 = a2;
    v7 = v6;
    v8 = 0;
    if ( v6 > 0 )
    {
      v9 = v14;
      v10 = a1;
      do
      {
        v9 = (_DWORD *)((char *)v9 + 1);
        v11 = *v10++;
        ++v8;
        *((_BYTE *)v9 - 1) = v11;
      }
      while ( (int)v8 < v7 );
    }
    v12 = (char *)v14 + v8;
    while ( v8 < a3 )
    {
      ++v8;
      *v12++ = 0;
    }
    Mem_SmallBlockFree(a1, a2);
  }
  return v14;
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
int  Mem_PurgeFreeListsForSpace(int a1, int a2, int a3)
{
  int v4; // esi
  unsigned int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // ebx

  v4 = 0;
  if ( a2 == 1 )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aDeallocatingMe, a3);
  v5 = 499;
  v6 = 1996;
  do
  {
    v7 = *(_DWORD *)(v6 + dword_54DBA8);
    if ( v7 )
    {
      do
      {
        v8 = *(_DWORD *)(uintptr_t)(unsigned int)v7;
        Mem_ReleasePoolBlock((int)v7, v5);
        v4 += v5;
        v7 = v8;
      }
      while ( v8 );
    }
    *(_DWORD *)(v6 + dword_54DBA8) = 0;
    if ( v4 > a1 && a1 > 0 )
      break;
    --v5;
    v6 -= 4;
  }
  while ( v5 >= 4 );
  if ( a2 == 1 )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aMemoryDealloca, v5);
  return v4;
}
// 47288E: variable 'v5' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 54DBA8: using guessed type int dword_54DBA8;

//----- (004728F0) --------------------------------------------------------
_BYTE * Mem_SmallBlockAllocZeroed(unsigned int a1)
{
  signed int v1; // ecx
  int free_list_slot; // eax
  int free_node; // edx
  int block; // esi
  signed int i; // eax
  _BYTE *v7; // edx
  int allocation_size; // ecx
  int allocated_block; // esi
  int j; // eax

  v1 = a1;
  if ( a1 >= 4 )
  {
    if ( (int)a1 >= 500 )
      return (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)a1);
  }
  else
  {
    v1 = 4;
  }
  free_list_slot = 4 * v1 + dword_54DBA8;
  free_node = *(_DWORD *)free_list_slot;
  if ( free_node )
  {
    block = free_node;
    *(_DWORD *)free_list_slot = *(_DWORD *)free_node;
    for ( i = 0; i < v1; ++free_node )
    {
      ++i;
      *(_BYTE *)free_node = 0;
    }
    return (_BYTE *)block;
  }
  else
  {
    allocation_size = v1;
    v7 = (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)allocation_size);
    allocated_block = (int)v7;
    for ( j = 0; j < allocation_size; ++v7 )
    {
      ++j;
      *v7 = 0;
    }
    return (_BYTE *)allocated_block;
  }
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472980) --------------------------------------------------------
_DWORD * Mem_SmallBlockAlloc(unsigned int a1)
{
  int free_list_slot; // ecx
  int free_node; // edx

  if ( a1 >= 4 )
  {
    if ( (int)a1 >= 500 )
      return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)a1);
  }
  else
  {
    a1 = 4;
  }
  free_list_slot = dword_54DBA8 + 4 * a1;
  free_node = *(_DWORD *)free_list_slot;
  if ( free_node )
  {
    *(_DWORD *)free_list_slot = *(_DWORD *)free_node;
    return (_DWORD *)free_node;
  }
  return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)a1);
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (004729C0) --------------------------------------------------------
_DWORD * Mem_NewArray(unsigned int a1)
{
  int free_list_slot; // ecx
  int free_node; // edx

  if ( a1 >= 4 )
  {
    if ( (int)a1 >= 500 )
      return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)a1);
  }
  else
  {
    a1 = 4;
  }
  free_list_slot = dword_54DBA8 + 4 * a1;
  free_node = *(_DWORD *)free_list_slot;
  if ( free_node )
  {
    *(_DWORD *)free_list_slot = *(_DWORD *)free_node;
    return (_DWORD *)free_node;
  }
  return (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)a1);
}
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472A00) --------------------------------------------------------
signed int  Mem_SmallBlockFree(_DWORD *a1, int a2)
{
  int v3; // ecx

  v3 = a2;
  if ( !a2 )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( (unsigned int)v3 < 4 )
  {
    v3 = 4;
LABEL_5:
    *a1 = *(_DWORD *)(dword_54DBA8 + 4 * v3);
    *(_DWORD *)(dword_54DBA8 + 4 * v3) = a1;
    return 1;
  }
  if ( v3 < 500 )
    goto LABEL_5;
  return Mem_ReleasePoolBlock((int)a1, v3);
}
// 472A0D: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;

//----- (00472A60) --------------------------------------------------------
signed int  Mem_SmallBlockRelease(_DWORD *a1, int a2)
{
  int v3; // ecx

  v3 = a2;
  if ( !a2 )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( (unsigned int)v3 < 4 )
  {
    v3 = 4;
LABEL_5:
    *a1 = *(_DWORD *)(dword_54DBA8 + 4 * v3);
    *(_DWORD *)(dword_54DBA8 + 4 * v3) = a1;
    return 1;
  }
  if ( v3 < 500 )
    goto LABEL_5;
  return Mem_ReleasePoolBlock((int)a1, v3);
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
signed int  Mem_InitPool(unsigned int a1, char a2)
{
  unsigned int request_size;
  int block_header_bytes;
  int available_size;
  int first_block;
  int tail_header;

  request_size = a1;
  dword_54DBC0 = 16;
  dword_54DBB8 = 16;
  if ( a1 < 0x3E800 )
    a1 = 256000;
  block_header_bytes = 2 * dword_54DBC0;
  available_size = 8 * ((dword_54DBB8 + block_header_bytes + a1 - 1) >> 3) + 8 - block_header_bytes - dword_54DBB8;
  if ( request_size < 0x3E800 && (unsigned int)available_size <= request_size + dword_54DBC0 )
    available_size = 8 * ((dword_54DBB8 + request_size + block_header_bytes - 1) >> 3) + 8 - block_header_bytes - dword_54DBB8;
  dword_54DBBC = nmalloc_(available_size, 0);
  if ( dword_54DBBC )
  {
    *(_DWORD *)dword_54DBBC = 0;
    *(_DWORD *)(dword_54DBBC + 4) = 0;
    first_block = dword_54DBBC + dword_54DBB8;
    *(_DWORD *)(dword_54DBBC + 8) = first_block;
    *(_DWORD *)(dword_54DBBC + 12) = available_size;
    tail_header = dword_54DBBC + dword_54DBB8 + dword_54DBC0 + available_size;
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
int  Mem_GrowPoolChain(int a1, unsigned int a2)
{
  int available_size;
  int new_pool;
  int first_block;
  int tail_header;

  if ( a2 < 0x3E800 )
    a2 = 256000;
  available_size = 8 * ((a2 + 2 * dword_54DBC0 + dword_54DBB8 - 1) >> 3) + 8 - dword_54DBB8 - 2 * dword_54DBC0;
  new_pool = nmalloc_(available_size, 0);
  if ( new_pool )
  {
    *(_DWORD *)new_pool = 0;
    *(_DWORD *)(new_pool + 4) = a1;
    first_block = new_pool + dword_54DBB8;
    *(_DWORD *)(new_pool + 12) = available_size;
    *(_DWORD *)(new_pool + 8) = first_block;
    *(_DWORD *)a1 = new_pool;
    tail_header = new_pool + dword_54DBB8 + dword_54DBC0 + available_size;
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
signed int  Mem_PoolAllocBlock(unsigned int a1, _DWORD *a2)
{
  _DWORD *pool;
  _DWORD *block;
  unsigned int requested_size;
  signed int result; // eax
  int callback_arg;

  if ( !g_Mem_PoolInitializedFlag )
  {
    result = Mem_InitPool(a1, a1);
    if ( !result )
      return result;
    IO_AddRouter((int)aBmexit, -2000, 0, 0, 0, 0, (int)Mem_HeapExitHandler);
  }
  requested_size = 8 * ((a1 - 1) >> 3) + 8;
  if ( dword_54DBBC )
  {
    pool = (_DWORD *)(uintptr_t)dword_54DBBC;
    while ( 1 )
    {
      block = (_DWORD *)(uintptr_t)pool[2];
      while ( block )
      {
        if ( requested_size == (unsigned int)block[3] || requested_size + dword_54DBC0 < (unsigned int)block[3] )
        {
          Mem_PoolSplitBlock((int)(uintptr_t)pool, block, requested_size);
          return (int)(uintptr_t)((char *)block + dword_54DBC0);
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
    callback_arg = (int)(uintptr_t)a2;
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
int  Mem_PoolSplitBlock(int result, _DWORD *a2, int a3)
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
  block_size = a2[3];
  if ( a3 == block_size )
  {
    previous_free = a2[2];
    a2[3] = -a3;
    if ( previous_free )
    {
      *(_DWORD *)(previous_free + 4) = a2[1];
    }
    else
    {
      next_free = a2[1];
      if ( next_free )
        *(_DWORD *)(pool + 8) = next_free;
      else
        *(_DWORD *)(pool + 8) = 0;
    }
    next_free = a2[1];
    if ( next_free )
    {
      *(_DWORD *)(next_free + 8) = a2[2];
    }
    a2[2] = 0;
    a2[1] = 0;
  }
  else
  {
    tail_header = (_DWORD *)((char *)a2 + dword_54DBC0 + block_size);
    split_block = (_DWORD *)((char *)a2 + dword_54DBC0 + a3);
    split_block[3] = block_size - (a3 + dword_54DBC0);
    *split_block = a2;
    split_block[1] = a2[1];
    split_block[2] = a2[2];
    *tail_header = split_block;
    prev_of_split = split_block[2];
    if ( prev_of_split )
      *(_DWORD *)(prev_of_split + 4) = (int)(uintptr_t)split_block;
    else
      *(_DWORD *)(pool + 8) = (int)(uintptr_t)split_block;
    next_of_split = split_block[1];
    if ( next_of_split )
      *(_DWORD *)(next_of_split + 8) = (int)(uintptr_t)split_block;
    a2[2] = 0;
    a2[1] = 0;
    a2[3] = -a3;
    result = -a3;
  }
  return result;
}
// 54DBC0: using guessed type int dword_54DBC0;

//----- (00472F00) --------------------------------------------------------
signed int  Mem_PoolFreeCoalesce(int a1, int a2)
{
  unsigned int v3; // ebx
  _DWORD *v4; // edx
  int v5; // edi
  int v7; // ecx
  _DWORD *v8; // eax
  int *v9; // eax
  _DWORD *v10; // ebx
  int v11; // esi
  _DWORD *v12; // ecx
  int v13; // esi
  int v14; // edi
  int v15; // ebp
  int v16; // esi
  int v17; // ebp
  _DWORD *v18; // ecx
  int v19; // esi
  int *v20; // ecx
  int v21; // edx
  int v22; // ecx

  v3 = 8 * ((unsigned int)(a2 - 1) >> 3) + 8;
  v4 = (_DWORD *)(a1 - dword_54DBC0);
  if ( a1 == dword_54DBC0 )
    return 0;
  v5 = v4[3];
  if ( v5 >= 0 || -v3 != v5 )
    return 0;
  v7 = *v4;
  v4[3] = v3;
  v8 = v4;
  if ( v7 )
  {
    do
      v8 = (_DWORD *)*v8;
    while ( *v8 );
  }
  v9 = (_DWORD *)((char *)v8 - dword_54DBB8);
  v10 = (_DWORD *)(a1 + v3);
  v11 = v9[2];
  v12 = (_DWORD *)*v4;
  if ( v11 )
    *(_DWORD *)(v11 + 8) = v4;
  v13 = v9[2];
  v4[2] = 0;
  v4[1] = v13;
  v9[2] = (int)v4;
  if ( v12 )
  {
    v14 = v12[3];
    if ( v14 > 0 )
    {
      v12[3] = v4[3] + dword_54DBC0 + v14;
      if ( !v10 )
        return 0;
      *v10 = v12;
      v15 = v12[2];
      if ( v15 )
        *(_DWORD *)(v15 + 4) = v12[1];
      if ( v12[1] )
        *(_DWORD *)(v12[1] + 8) = v12[2];
      v16 = v4[1];
      v12[1] = v16;
      if ( v16 )
        *(_DWORD *)(v16 + 8) = v12;
      v12[2] = 0;
      v9[2] = (int)v12;
      v4[2] = 0;
      v4[1] = 0;
      v4 = v12;
    }
  }
  if ( !v10 || !v4 )
    return 0;
  v17 = v10[3];
  if ( v17 > 0 )
  {
    v4[3] += v17 + dword_54DBC0;
    v18 = (_DWORD *)((char *)v10 + v10[3] + dword_54DBC0);
    if ( v18 )
    {
      *v18 = v4;
      if ( v10[2] )
        *(_DWORD *)(v10[2] + 4) = v10[1];
      v19 = v10[1];
      if ( v19 )
        *(_DWORD *)(v19 + 8) = v10[2];
      goto LABEL_27;
    }
    return 0;
  }
LABEL_27:
  if ( *v4 || v4[3] != v9[3] )
    return 1;
  if ( v9[1] )
  {
    v20 = (int *)v9[1];
    v21 = *v9;
    *v20 = *v9;
    if ( v21 )
    {
      v20 = (int *)v21;
      *(_DWORD *)(v21 + 4) = v9[1];
    }
    nfree_(v20);
    return 1;
  }
  v22 = *v9;
  if ( !*v9 )
    return 1;
  *(_DWORD *)(v22 + 4) = 0;
  dword_54DBBC = *v9;
  nfree_(v22);
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

  if ( dword_54DBBC )
  {
    do
    {
      next_pool = *(_DWORD *)dword_54DBBC;
      nfree_(dword_54DBBC);
      dword_54DBBC = next_pool;
    }
    while ( next_pool );
  }
  result = g_Mem_ReservedBlockListHead;
  dword_54DBBC = 0;
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
_DWORD * Surface_ConstructWithSurface(_DWORD *a1, _DWORD *a2, int a3, int a4)
{
  a1[43] = g_Surface_BlitFunctionTable;
  if ( !Surface_CreateDDSurface(a1, a2, a3, a4) )
    return 0;
  return a1;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (004732E0) --------------------------------------------------------
int  Surface_Destruct(int result)
{
  int v1; // ebx
  int v2; // edx

  v1 = result;
  v2 = *(_DWORD *)(result + 164);
  *(_DWORD *)(result + 172) = g_Surface_BlitFunctionTable;
  if ( v2 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)v2 + 8))(v2);
    *(_DWORD *)(v1 + 164) = 0;
    return v1;
  }
  return result;
}
// 5108E0: using guessed type int (*off_5108E0[3])();

//----- (00473320) --------------------------------------------------------
signed int  Surface_CreateDDSurface(_DWORD *a1, _DWORD *a2, int a3, int a4)
{
  HRESULT hr;
  int direct_draw_handle;

  if ( !a1 )
    return 0;
  memset(a1 + 14, 0, 108);
  a1[14] = 108;
  a1[15] = 7;
  a1[40] = 64;
  a1[16] = a3;
  a1[17] = a4;
  if ( !a2 )
    return 0;
  direct_draw_handle = *a2;
  if ( !direct_draw_handle )
    return 0;
  hr = Compat_DirectDraw_CreateSurface(
         (LPDIRECTDRAW)(uintptr_t)(unsigned int)direct_draw_handle,
         (int *)(a1 + 14),
         a1 + 41);
  if ( hr )
  {
    Render_HandleDirectDrawFatalError(hr, a2[9]);
    return 0;
  }
  a1[4] = -1;
  a1[10] = 0;
  a1[9] = 0;
  a1[6] = 0;
  a1[5] = 0;
  a1[3] = 0;
  a1[13] = 0;
  a1[2] = 0;
  a1[42] = a2;
  a1[1] = a3;
  *a1 = a4;
  a1[12] = a1[1];
  a1[11] = *a1;
  a1[8] = a1[1];
  a1[7] = *a1;
  return 1;
}

//----- (004733F0) --------------------------------------------------------
int  Surface_CreateFromBitmapFile(_DWORD *a1, int *a2, const CHAR *a3)
{
  int result; // eax
  int v6; // ecx
  int v7; // eax

  if ( !a3 )
    return 0;
  result = Surface_DDCopyBitmapToNewSurface(*a2, a3, a1 + 1, (int)a1);
  a1[41] = result;
  if ( result )
  {
    a1[3] = 0;
    a1[13] = 0;
    a1[4] = -1;
    a1[10] = 0;
    a1[9] = 0;
    a1[6] = 0;
    a1[5] = 0;
    v7 = a1[1];
    a1[2] = a3;
    a1[12] = v7;
    a1[11] = *a1;
    a1[8] = a1[1];
    a1[7] = *a1;
    a1[42] = a2;
    memset_(v6, 0);
    a1[14] = 108;
    a1[15] = 7;
    a1[40] = 64;
    a1[17] = *a1;
    a1[16] = a1[1];
    return 1;
  }
  return result;
}
// 473477: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004734B0) --------------------------------------------------------
int  Surface_BltOntoSurface(int a1, int a2)
{
  int result; // eax
  int v4; // edx

  result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(**(_DWORD **)(a2 + 164) + 20))(
             *(_DWORD *)(a2 + 164),
             a1 + 36,
             *(_DWORD *)(a1 + 164),
             a1 + 20,
             0x1000000,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore(a1);
    return v4;
  }
  return result;
}
// 4734EB: variable 'v4' is possibly undefined

//----- (004734F0) --------------------------------------------------------
int  Surface_BltFastOpaqueTo(int a1, int a2, int a3, int a4)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, int, int))(**(_DWORD **)(a3 + 164) + 28))(
             *(_DWORD *)(a3 + 164),
             a2,
             a4,
             *(_DWORD *)(a1 + 164),
             a1 + 20,
             16);
  if ( result == -2005532222 )
  {
    Surface_Restore(a1);
    return -2005532222;
  }
  return result;
}

//----- (00473530) --------------------------------------------------------
int  Surface_BltFastKeyedTo(int a1, int a2, int a3, int a4)
{
  int result; // eax

  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, int, int))(**(_DWORD **)(a3 + 164) + 28))(
             *(_DWORD *)(a3 + 164),
             a2,
             a4,
             *(_DWORD *)(a1 + 164),
             a1 + 20,
             17);
  if ( result == -2005532222 )
  {
    Surface_Restore(a1);
    return -2005532222;
  }
  return result;
}

//----- (00473570) --------------------------------------------------------
int  Surface_BltFastKeyedClippedTo(_DWORD *a1, int a2, int a3, int a4, _DWORD *a5)
{
  int result; // eax
  int v7; // edx
  _DWORD v8[4]; // [esp+0h] [ebp-28h] BYREF
  int v9; // [esp+10h] [ebp-18h] BYREF
  int v10; // [esp+14h] [ebp-14h] BYREF
  int v11; // [esp+18h] [ebp-10h]

  v9 = a2;
  v10 = a4;
  v11 = a3;
  v8[0] = a1[5];
  v8[1] = a1[6];
  v8[2] = a1[7];
  v8[3] = a1[8];
  Render_ClampBlitRectToBounds(&v9, &v10, a5, v8);
  result = (*(int (__stdcall **)(_DWORD, int, int, _DWORD, _DWORD *, int))(**(_DWORD **)(v11 + 164) + 28))(
             *(_DWORD *)(v11 + 164),
             v9,
             v10,
             a1[41],
             v8,
             17);
  if ( result == -2005532222 )
  {
    Surface_Restore((int)a1);
    return v7;
  }
  return result;
}
// 473570: could not find valid save-restore pair for ebx
// 4735E3: variable 'v7' is possibly undefined

//----- (004735F0) --------------------------------------------------------
int  Surface_BltToWindowClient(int a1, int a2)
{
  int result; // eax
  struct tagRECT v5[2]; // [esp+0h] [ebp-24h] BYREF

  GetClientRect(*(HWND *)(*(_DWORD *)(a1 + 168) + 36), v5);
  ClientToScreen(*(HWND *)(*(_DWORD *)(a1 + 168) + 36), (LPPOINT)v5);
  ClientToScreen(*(HWND *)(*(_DWORD *)(a1 + 168) + 36), (LPPOINT)&v5[0].right);
  result = (*(int (__stdcall **)(_DWORD, struct tagRECT *, _DWORD, _DWORD, int, _DWORD))(**(_DWORD **)(a2 + 164) + 20))(
             *(_DWORD *)(a2 + 164),
             v5,
             *(_DWORD *)(a1 + 164),
             0,
             0x1000000,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore(a1);
    return -2005532222;
  }
  return result;
}

//----- (00473690) --------------------------------------------------------
int  Surface_BltScaledKeyedOnto(_DWORD *a1, int a2, int a3, float a4, int a5)
{
  int v6; // ecx
  double v7; // st6
  int *v8; // eax
  int v9; // ebx
  int v10; // edx
  double v11; // st7
  int v12; // eax
  int result; // eax
  int v14; // edx
  int v15; // [esp+4h] [ebp-Ch]

  v6 = a1[1];
  a1[10] = a2;
  v7 = (double)(v6 + a2) * a4;
  _CHP(v6 + a2, a3);
  v8[12] = (int)v7;
  v9 = *v8;
  v8[9] = v10;
  v11 = a4 * (double)(v9 + v10);
  _CHP(v9 + v10, v15);
  *(_DWORD *)(v12 + 44) = (int)v11;
  result = (*(int (__stdcall **)(_DWORD, _DWORD *, _DWORD, _DWORD *, int, _DWORD))(**(_DWORD **)(a5 + 164) + 20))(
             *(_DWORD *)(a5 + 164),
             a1 + 9,
             a1[41],
             a1 + 5,
             16809984,
             0);
  if ( result == -2005532222 )
  {
    Surface_Restore((int)a1);
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
int  Surface_BltMirrorLeftRight(int a1)
{
  _DWORD v2[25]; // [esp+0h] [ebp-64h] BYREF

  v2[0] = 100;
  v2[1] = 2;
  return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int, _DWORD *))(**(_DWORD **)(a1 + 164) + 20))(
           *(_DWORD *)(a1 + 164),
           0,
           0,
           0,
           16779264,
           v2);
}

//----- (00473770) --------------------------------------------------------
int  Surface_BltMirrorUpDown(int a1)
{
  _DWORD v2[25]; // [esp+0h] [ebp-64h] BYREF

  v2[0] = 100;
  v2[1] = 4;
  return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, int, _DWORD *))(**(_DWORD **)(a1 + 164) + 20))(
           *(_DWORD *)(a1 + 164),
           0,
           0,
           0,
           16779264,
           v2);
}

//----- (004737B0) --------------------------------------------------------
_DWORD * Surface_SetDestRect(_DWORD *result, int a2, int a3, int a4, int a5)
{
  result[10] = a2;
  result[9] = a4;
  result[12] = a3;
  result[11] = a5;
  return result;
}

//----- (004737D0) --------------------------------------------------------
_DWORD * Surface_SetSrcRect(_DWORD *result, int a2, int a3, int a4, int a5)
{
  result[6] = a2;
  result[5] = a4;
  result[8] = a3;
  result[7] = a5;
  return result;
}

//----- (004737F0) --------------------------------------------------------
int  Surface_SetSrcColorKey(int a1, int a2, int a3)
{
  _DWORD v4[3]; // [esp+0h] [ebp-Ch] BYREF

  v4[2] = a3;
  *(_DWORD *)(a1 + 16) = a2;
  v4[0] = a2;
  v4[1] = a2;
  return (*(int (__stdcall **)(_DWORD, int, _DWORD *))(**(_DWORD **)(a1 + 164) + 116))(*(_DWORD *)(a1 + 164), 8, v4);
}

//----- (00473820) --------------------------------------------------------
int  Surface_Restore(int a1)
{
  return (*(int (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 164) + 108))(*(_DWORD *)(a1 + 164));
}

//----- (00473840) --------------------------------------------------------
int  Surface_LockWithRestore(int a1, int a2)
{
  int v3; // edi
  int v4; // eax
  int result; // eax

  v3 = a1 + 56;
  memset_(a2, 0);
  v4 = *(_DWORD *)(a1 + 164);
  *(_DWORD *)(a1 + 56) = 108;
  result = (*(int (__stdcall **)(int, _DWORD, int, int, _DWORD))(*(_DWORD *)v4 + 100))(v4, 0, v3, 1, 0);
  if ( result == -2005532222 )
  {
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(a1 + 164) + 108))(*(_DWORD *)(a1 + 164));
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int, _DWORD))(**(_DWORD **)(a1 + 164) + 100))(
      *(_DWORD *)(a1 + 164),
      0,
      v3,
      1,
      0);
    return -2005532222;
  }
  return result;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004738B0) --------------------------------------------------------
int  Surface_Unlock(int a1)
{
  return (*(int (__stdcall **)(_DWORD, int))(**(_DWORD **)(a1 + 164) + 128))(*(_DWORD *)(a1 + 164), a1 + 56);
}

//----- (004739C0) --------------------------------------------------------
int  Surface_SetPixelByte(int result, int a2, char a3, int a4)
{
  *(_BYTE *)(*(_DWORD *)(result + 72) * a4 + a2 + *(_DWORD *)(result + 92)) = a3;
  return result;
}

//----- (004739D0) --------------------------------------------------------
int  Surface_GetPixelByte(int a1, int a2, int a3)
{
  return *(unsigned __int8 *)(*(_DWORD *)(a1 + 92) + *(_DWORD *)(a1 + 72) * a3 + a2);
}

//----- (004739F0) --------------------------------------------------------
int * Mem_SwapDwordPair(int *result, int *a2)
{
  int v2; // ebx

  v2 = *result;
  *result = *a2;
  *a2 = v2;
  return result;
}

//----- (00473A00) --------------------------------------------------------
int  Surface_DrawRectBorderByte(int a1, int a2, int a3, int a4, int a5, char a6)
{
  int i; // ebp
  int j; // ebp

  for ( i = a2; i < a3; ++i )
  {
    Surface_SetPixelByte(a1, i, a6, a4);
    Surface_SetPixelByte(a1, i, a6, a5);
  }
  for ( j = a4; j < a5; ++j )
  {
    Surface_SetPixelByte(a1, a2, a6, j);
    Surface_SetPixelByte(a1, a3, a6, j);
  }
  Surface_SetPixelByte(a1, a2, a6, a4);
  return Surface_SetPixelByte(a1, a3, a6, a5);
}

//----- (00473AB0) --------------------------------------------------------
int  Surface_FillRectColor(int a1, int a2, int a3, int a4, int a5, int a6)
{
  _DWORD v7[25]; // [esp+0h] [ebp-7Ch] BYREF
  _DWORD v8[6]; // [esp+64h] [ebp-18h] BYREF

  v8[0] = a2;
  v8[3] = a5;
  v7[0] = 100;
  v7[20] = a6;
  v8[1] = a4;
  v8[2] = a3;
  return (*(int (__stdcall **)(_DWORD, _DWORD *, _DWORD, _DWORD, int, _DWORD *))(**(_DWORD **)(a1 + 164) + 20))(
           *(_DWORD *)(a1 + 164),
           v8,
           0,
           0,
           16778240,
           v7);
}

//----- (00473B10) --------------------------------------------------------
int  Render_DrawLine(int a1, int a2, int a3, int a4, int a5, char a6)
{
  char v6; // bp
  signed int v8; // esi
  signed int v9; // eax
  int result; // eax
  int v11; // esi
  int v12; // esi
  int v13; // [esp+0h] [ebp-3Ch]
  double v14; // [esp+0h] [ebp-3Ch]
  int v15; // [esp+4h] [ebp-38h]
  double v16; // [esp+8h] [ebp-34h]
  double j; // [esp+10h] [ebp-2Ch]
  double i; // [esp+18h] [ebp-24h]
  int v19; // [esp+20h] [ebp-1Ch] BYREF
  int v20; // [esp+24h] [ebp-18h] BYREF
  int v21; // [esp+28h] [ebp-14h] BYREF
  int v22; // [esp+2Ch] [ebp-10h]

  v6 = a6;
  v19 = a2;
  v20 = a4;
  v21 = a3;
  v8 = abs32(a3 - a2);
  v9 = abs32(a5 - a4);
  if ( !v8 )
    return Render_DrawVerticalRun(a1, v20, v19, a5, a6);
  if ( !v9 )
    return Render_DrawHorizontalRun(a1, v19, v20, v21, a6);
  if ( v8 <= v9 )
  {
    if ( v20 > a5 )
    {
      Mem_SwapDwordPair(&v19, &v21);
      Mem_SwapDwordPair(&v20, &a5);
    }
    result = a5 - v20;
    v14 = (double)(v21 - v19) / (double)(a5 - v20);
    v22 = v19;
    v12 = v20;
    for ( i = (double)v19; v12 <= a5; i = i + v14 )
    {
      _CHP(LODWORD(v14), HIDWORD(v14));
      v22 = (int)i;
      result = Surface_SetPixelByte(a1, (int)i, v6, v12++);
    }
  }
  else
  {
    if ( v19 > v21 )
    {
      Mem_SwapDwordPair(&v19, &v21);
      Mem_SwapDwordPair(&v20, &a5);
    }
    result = v21 - v19;
    v16 = (double)(a5 - v20) / (double)(v21 - v19);
    v22 = v20;
    v11 = v19;
    for ( j = (double)v20; v11 <= v21; j = j + v16 )
    {
      _CHP(v13, v15);
      v22 = (int)j;
      Surface_SetPixelByte(a1, v11++, v6, (int)j);
      result = v21;
    }
  }
  return result;
}
// 473BC2: variable 'v13' is possibly undefined
// 473BC2: variable 'v15' is possibly undefined
// 473C9E: variable 'v14' is possibly undefined

//----- (00473CE0) --------------------------------------------------------
int  Render_DrawVerticalRun(int a1, int a2, int a3, int a4, char a5)
{
  int v6; // ebp
  int result; // eax
  int v8; // edx

  v6 = *(_DWORD *)(a1 + 92);
  for ( result = a2; result < a4; *(_BYTE *)(v8 + v6) = a5 )
  {
    v8 = a3 + result * *(_DWORD *)(a1 + 72);
    ++result;
  }
  return result;
}

//----- (00473D20) --------------------------------------------------------
int  Render_DrawHorizontalRun(int result, int a2, int a3, int a4, char a5)
{
  int v5; // edi
  int i; // esi

  v5 = result;
  for ( i = a2; i < a4; ++i )
    result = Surface_SetPixelByte(v5, i, a5, a3);
  return result;
}
// 473D20: could not find valid save-restore pair for ebx

//----- (00473E30) --------------------------------------------------------
int  Render_FillSurfaceSolidColor(int a1, int a2, int a3)
{
  _DWORD v4[26]; // [esp+0h] [ebp-68h] BYREF

  v4[25] = a3;
  v4[20] = a2;
  v4[0] = 100;
  return Compat_DirectDrawSurface_Blt(
           (LPDIRECTDRAWSURFACE)*(int *)(a1 + 164),
           0,
           0,
           0,
           16778240,
           v4);
}

//----- (00473E60) --------------------------------------------------------
int  Render_ClampBlitRectToBounds(_DWORD *a1, _DWORD *a2, _DWORD *a3, _DWORD *a4)
{
  int v4; // edi
  int v5; // esi
  int v6; // esi
  int v7; // ebp
  int result; // eax

  v4 = a3[2];
  v5 = *a1 + a4[2] - *a4;
  if ( v5 > v4 )
    a4[2] -= v5 - v4;
  if ( *a1 < *a3 )
  {
    *a4 += *a3 - *a1;
    *a1 = *a3;
  }
  v6 = a3[1];
  if ( *a2 < v6 )
  {
    a4[1] += v6 - *a2;
    *a2 = a3[1];
  }
  v7 = a3[3];
  result = *a2 + a4[3] - a4[1];
  if ( result > v7 )
  {
    result -= v7;
    a4[3] -= result;
  }
  return result;
}

//----- (00473EE0) --------------------------------------------------------
int __fastcall Compat_FileSystemQueryRelease(int a1, int *a2)
{
  int object_handle;
  int result;
  uintptr_t *vtable;

  (void)a1;
  if ( !a2 )
    return 0;
  object_handle = *a2;
  if ( !object_handle )
  {
    *a2 = 0;
    return 0;
  }
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)object_handle;
  result = ((int (*)(int, int))(uintptr_t)vtable[3])(object_handle, 2);
  *a2 = 0;
  return result;
}

//----- (00473F10) --------------------------------------------------------
int  FileSystem_OpenViaOpenSlotAndNotify(int a1)
{
  int result; // eax
  int v3; // ecx

  result = (*(int (__thiscall **)(int))(*(_DWORD *)a1 + 12))(a1);
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
int  Compat_FileSystemOpenIfReady(int a1, int a2)
{
  _DWORD *opened_query; // ecx

  opened_query = Compat_FileSystemQueryOpen(a1, a2);
  if ( opened_query && Compat_FileSystemQueryResultIsReady(opened_query) == 1 )
    return (int)opened_query;
  if ( opened_query )
    Compat_FileSystemQueryResultRelease(opened_query);
  return 0;
}
// 473F9E: variable 'v3' is possibly undefined

//----- (004741F0) --------------------------------------------------------
void  __noreturn Render_HandleDirectDrawFatalError(unsigned int a1, int a2)
{
  const char *v2; // eax
  char v3[256]; // [esp+0h] [ebp-104h] BYREF
  int v4; // [esp+100h] [ebp-4h]

  v4 = a2;
  if ( a1 >= 0x8876019A )
  {
    if ( a1 <= 0x8876019A )
    {
      v2 = aDderr_surfacea;
      goto LABEL_10;
    }
    if ( a1 >= 0x8876023B )
    {
      if ( a1 <= 0x8876023B )
      {
        v2 = aDderr_hwndalre;
        goto LABEL_10;
      }
      if ( a1 < 0x88760248 )
      {
        if ( a1 >= 0x88760241 )
        {
          if ( a1 <= 0x88760241 )
          {
            v2 = aDderr_overlayn;
          }
          else if ( a1 >= 0x88760244 )
          {
            if ( a1 <= 0x88760244 )
            {
              v2 = aDderr_notaover;
            }
            else if ( a1 < 0x88760246 )
            {
              v2 = aDderr_exclusiv;
            }
            else if ( a1 <= 0x88760246 )
            {
              v2 = aDderr_notflipp;
            }
            else
            {
              v2 = aDderr_cantdupl;
            }
          }
          else if ( a1 <= 0x88760242 )
          {
            v2 = aDderr_nooverla;
          }
          else
          {
            v2 = aDderr_invalidp;
          }
        }
        else if ( a1 >= 0x8876023E )
        {
          if ( a1 <= 0x8876023E )
          {
            v2 = aDderr_bltfastc;
          }
          else if ( a1 <= 0x8876023F )
          {
            v2 = aDderr_noblthw;
          }
          else
          {
            v2 = aDderr_noddrops;
          }
        }
        else if ( a1 <= 0x8876023C )
        {
          v2 = aDderr_nopalett;
        }
        else
        {
          v2 = aDderr_nopale_0;
        }
        goto LABEL_10;
      }
      if ( a1 <= 0x88760248 )
      {
        v2 = aDderr_notlocke;
        goto LABEL_10;
      }
      if ( a1 < 0x8876024E )
      {
        if ( a1 >= 0x8876024B )
        {
          if ( a1 <= 0x8876024B )
          {
            sprintf_(v3, aDderr_wrongmod);
          }
          else if ( a1 <= 0x8876024C )
          {
            sprintf_(v3, aDderr_implicit);
          }
          else
          {
            sprintf_(v3, aDderr_notpalet);
          }
        }
        else
        {
          if ( a1 <= 0x88760249 )
          {
            v2 = aDderr_cantcrea;
            goto LABEL_10;
          }
          sprintf_(v3, aDderr_nodc);
        }
LABEL_11:
        sprintf_(&unk_54DBE0, "DirectDraw Error %s", v3);
        App_RequestQuit((int)aDirectdrawEr_0);
      }
      if ( a1 <= 0x8876024E )
      {
        sprintf_(v3, aDderr_unsupp_0);
        goto LABEL_11;
      }
      if ( a1 >= 0x8876026C )
      {
        if ( a1 <= 0x8876026C )
        {
          sprintf_(v3, aDderr_dcalread);
          goto LABEL_11;
        }
        if ( a1 >= 0x88760294 )
        {
          if ( a1 <= 0x88760294 )
          {
            sprintf_(v3, aDderr_cantpa_0);
            goto LABEL_11;
          }
          if ( a1 == -2005531992 )
          {
            sprintf_(v3, aDderr_notpagel);
            goto LABEL_11;
          }
        }
        else if ( a1 == -2005532032 )
        {
          sprintf_(v3, aDderr_cantpage);
          goto LABEL_11;
        }
      }
      else
      {
        if ( a1 <= 0x8876024F )
        {
          sprintf_(v3, aDderr_nomipmap);
          goto LABEL_11;
        }
        if ( a1 == -2005532080 )
        {
          sprintf_(v3, aDderr_invalids);
          goto LABEL_11;
        }
      }
    }
    else if ( a1 >= 0x88760219 )
    {
      if ( a1 <= 0x88760219 )
      {
        v2 = aDderr_vertical;
        goto LABEL_10;
      }
      if ( a1 >= 0x88760234 )
      {
        if ( a1 <= 0x88760234 )
        {
          v2 = aDderr_primarys;
        }
        else if ( a1 >= 0x88760237 )
        {
          if ( a1 <= 0x88760237 )
          {
            v2 = aDderr_clipperi;
          }
          else if ( a1 < 0x88760239 )
          {
            v2 = aDderr_noclippe;
          }
          else if ( a1 <= 0x88760239 )
          {
            v2 = aDderr_nohwnd;
          }
          else
          {
            v2 = aDderr_hwndsubc;
          }
        }
        else if ( a1 <= 0x88760235 )
        {
          v2 = aDderr_noemulat;
        }
        else
        {
          v2 = aDderr_regionto;
        }
        goto LABEL_10;
      }
      if ( a1 >= 0x88760231 )
      {
        if ( a1 <= 0x88760231 )
        {
          v2 = aDderr_invalidd;
        }
        else if ( a1 <= 0x88760232 )
        {
          v2 = aDderr_directdr;
        }
        else
        {
          v2 = aDderr_nodirect;
        }
        goto LABEL_10;
      }
      if ( a1 >= 0x8876021C )
      {
        if ( a1 <= 0x8876021C )
        {
          v2 = aDderr_wasstill;
          goto LABEL_10;
        }
        if ( a1 == -2005532112 )
        {
          v2 = aDderr_xalign;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x887601CC )
    {
      if ( a1 <= 0x887601CC )
      {
        v2 = aDderr_surfacen;
        goto LABEL_10;
      }
      if ( a1 >= 0x887601EA )
      {
        if ( a1 <= 0x887601EA )
        {
          v2 = aDderr_toobigwi;
          goto LABEL_10;
        }
        if ( a1 >= 0x887601FE )
        {
          if ( a1 <= 0x887601FE )
          {
            v2 = aDderr_unsupp_1;
            goto LABEL_10;
          }
          if ( a1 == -2005532152 )
          {
            v2 = aDderr_unsupp_2;
            goto LABEL_10;
          }
        }
      }
      else if ( a1 >= 0x887601D6 )
      {
        if ( a1 <= 0x887601D6 )
        {
          v2 = aDderr_toobighe;
          goto LABEL_10;
        }
        if ( a1 == -2005532192 )
        {
          v2 = aDderr_toobigsi;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x887601B3 )
    {
      if ( a1 <= 0x887601B3 )
      {
        v2 = aDderr_cantlock;
        goto LABEL_10;
      }
      if ( a1 >= 0x887601B8 )
      {
        if ( a1 <= 0x887601B8 )
        {
          v2 = aDderr_surfacei;
          goto LABEL_10;
        }
        if ( a1 == -2005532222 )
        {
          v2 = aDderr_surfacel;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x887601A4 )
    {
      if ( a1 <= 0x887601A4 )
      {
        v2 = aDderr_surfac_0;
        goto LABEL_10;
      }
      if ( a1 == -2005532242 )
      {
        v2 = aDderr_surfaceb;
        goto LABEL_10;
      }
    }
  }
  else if ( a1 >= 0x887600D7 )
  {
    if ( a1 <= 0x887600D7 )
    {
      v2 = aDderr_nocolork;
      goto LABEL_10;
    }
    if ( a1 >= 0x8876013C )
    {
      if ( a1 <= 0x8876013C )
      {
        v2 = aDderr_not4bitc;
        goto LABEL_10;
      }
      if ( a1 >= 0x8876015E )
      {
        if ( a1 <= 0x8876015E )
        {
          v2 = aDderr_nozoverl;
          goto LABEL_10;
        }
        if ( a1 >= 0x8876017E )
        {
          if ( a1 <= 0x8876017E )
          {
            v2 = aDderr_overlayc;
            goto LABEL_10;
          }
          if ( a1 >= 0x88760183 )
          {
            if ( a1 <= 0x88760183 )
            {
              v2 = aDderr_paletteb;
              goto LABEL_10;
            }
            if ( a1 == -2005532272 )
            {
              v2 = aDderr_colorkey;
              goto LABEL_10;
            }
          }
          else if ( a1 == -2005532288 )
          {
            v2 = aDderr_overla_0;
            goto LABEL_10;
          }
        }
        else if ( a1 >= 0x88760168 )
        {
          if ( a1 <= 0x88760168 )
          {
            v2 = aDderr_outofcap;
            goto LABEL_10;
          }
          if ( a1 == -2005532292 )
          {
            v2 = aDderr_outofvid;
            goto LABEL_10;
          }
        }
      }
      else if ( a1 >= 0x8876014A )
      {
        if ( a1 <= 0x8876014A )
        {
          v2 = aDderr_notextur;
          goto LABEL_10;
        }
        if ( a1 >= 0x8876014F )
        {
          if ( a1 <= 0x8876014F )
          {
            v2 = aDderr_novsynch;
            goto LABEL_10;
          }
          if ( a1 == -2005532332 )
          {
            v2 = aDderr_nozbuffe;
            goto LABEL_10;
          }
        }
      }
      else
      {
        if ( a1 <= 0x8876013D )
        {
          v2 = aDderr_not4bi_0;
          goto LABEL_10;
        }
        if ( a1 == -2005532352 )
        {
          v2 = aDderr_not8bitc;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x887600FA )
    {
      if ( a1 <= 0x887600FA )
      {
        v2 = aDderr_nomirror;
        goto LABEL_10;
      }
      if ( a1 >= 0x88760118 )
      {
        if ( a1 <= 0x88760118 )
        {
          v2 = aDderr_noraster;
          goto LABEL_10;
        }
        if ( a1 >= 0x88760122 )
        {
          if ( a1 <= 0x88760122 )
          {
            v2 = aDderr_norotati;
            goto LABEL_10;
          }
          if ( a1 == -2005532362 )
          {
            v2 = aDderr_nostretc;
            goto LABEL_10;
          }
        }
      }
      else if ( a1 >= 0x887600FF )
      {
        if ( a1 <= 0x887600FF )
        {
          v2 = aDderr_notfound;
          goto LABEL_10;
        }
        if ( a1 == -2005532412 )
        {
          v2 = aDderr_noover_0;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x887600E1 )
    {
      if ( a1 <= 0x887600E1 )
      {
        v2 = aDderr_noexclus;
        goto LABEL_10;
      }
      if ( a1 >= 0x887600E6 )
      {
        if ( a1 <= 0x887600E6 )
        {
          v2 = aDderr_nofliphw;
          goto LABEL_10;
        }
        if ( a1 == -2005532432 )
        {
          v2 = aDderr_nogdi;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x887600DC )
    {
      if ( a1 <= 0x887600DC )
      {
        v2 = aDderr_nocolo_0;
        goto LABEL_10;
      }
      if ( a1 == -2005532450 )
      {
        v2 = aDderr_nodire_0;
        goto LABEL_10;
      }
    }
  }
  else if ( a1 >= 0x8876005F )
  {
    if ( a1 <= 0x8876005F )
    {
      v2 = aDderr_incompat;
      goto LABEL_10;
    }
    if ( a1 >= 0x88760096 )
    {
      if ( a1 <= 0x88760096 )
      {
        v2 = aDderr_invalidr;
        goto LABEL_10;
      }
      if ( a1 >= 0x887600B4 )
      {
        if ( a1 <= 0x887600B4 )
        {
          v2 = aDderr_noalphah;
          goto LABEL_10;
        }
        if ( a1 >= 0x887600D2 )
        {
          if ( a1 <= 0x887600D2 )
          {
            v2 = aDderr_nocolorc;
            goto LABEL_10;
          }
          if ( a1 == -2005532460 )
          {
            v2 = aDderr_nocooper;
            goto LABEL_10;
          }
        }
        else if ( a1 == -2005532467 )
        {
          v2 = aDderr_noclipli;
          goto LABEL_10;
        }
      }
      else if ( a1 >= 0x887600A0 )
      {
        if ( a1 <= 0x887600A0 )
        {
          v2 = aDderr_lockedsu;
          goto LABEL_10;
        }
        if ( a1 == -2005532502 )
        {
          v2 = aDderr_no3d;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x88760078 )
    {
      if ( a1 <= 0x88760078 )
      {
        v2 = aDderr_invalidm;
        goto LABEL_10;
      }
      if ( a1 >= 0x88760082 )
      {
        if ( a1 <= 0x88760082 )
        {
          v2 = aDderr_invalido;
          goto LABEL_10;
        }
        if ( a1 == -2005532527 )
        {
          v2 = aDderr_invali_1;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x88760064 )
    {
      if ( a1 <= 0x88760064 )
      {
        v2 = aDderr_invalidc;
        goto LABEL_10;
      }
      if ( a1 == -2005532562 )
      {
        v2 = aDderr_invali_0;
        goto LABEL_10;
      }
    }
  }
  else if ( a1 >= 0x88760005 )
  {
    if ( a1 <= 0x88760005 )
    {
      v2 = aDderr_alreadyi;
      goto LABEL_10;
    }
    if ( a1 >= 0x88760028 )
    {
      if ( a1 <= 0x88760028 )
      {
        v2 = aDderr_currentl;
        goto LABEL_10;
      }
      if ( a1 >= 0x88760037 )
      {
        if ( a1 <= 0x88760037 )
        {
          v2 = aDderr_exceptio;
          goto LABEL_10;
        }
        if ( a1 == -2005532582 )
        {
          v2 = aDderr_heightal;
          goto LABEL_10;
        }
      }
    }
    else if ( a1 >= 0x8876000A )
    {
      if ( a1 <= 0x8876000A )
      {
        v2 = aDderr_cannotat;
        goto LABEL_10;
      }
      if ( a1 == -2005532652 )
      {
        v2 = aDderr_cannotde;
        goto LABEL_10;
      }
    }
  }
  else if ( a1 >= 0x800401F0 )
  {
    if ( a1 <= 0x800401F0 )
    {
      v2 = aDderr_notiniti;
      goto LABEL_10;
    }
    if ( a1 >= 0x8007000E )
    {
      if ( a1 <= 0x8007000E )
      {
        v2 = aDderr_outofmem;
        goto LABEL_10;
      }
      if ( a1 == -2147024809 )
      {
        v2 = aDderr_invali_2;
        goto LABEL_10;
      }
    }
  }
  else if ( a1 >= 0x80004001 )
  {
    if ( a1 <= 0x80004001 )
    {
      v2 = aDderr_unsuppor;
      goto LABEL_10;
    }
    if ( a1 == -2147467259 )
    {
      v2 = aDderr_generic;
LABEL_10:
      sprintf_(v3, v2);
      goto LABEL_11;
    }
  }
  sprintf_(v3, aUnknownError);
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
_DWORD * Render_DestroyDirectDrawObject(_DWORD *a1)
{
  int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // esi
  int v6; // edi

  if ( *a1 )
    Compat_InvokeNativeComMethod0(*a1, 76);
  v2 = a1[2];
  if ( v2 )
  {
    Surface_Destruct(v2);
    j__nfree_();
  }
  v3 = a1[1];
  if ( v3 )
  {
    Surface_Destruct(v3);
    j__nfree_();
  }
  v4 = a1[3];
  if ( v4 )
  {
    Compat_InvokeNativeComMethod0(v4, 8);
    a1[3] = 0;
  }
  v5 = a1[5];
  if ( v5 )
  {
    Compat_InvokeNativeComMethod0(v5, 8);
    a1[5] = 0;
  }
  v6 = a1[4];
  if ( v6 )
  {
    Compat_InvokeNativeComMethod0(v6, 8);
    a1[4] = 0;
  }
  if ( *a1 )
  {
    Compat_InvokeNativeComMethod0(*a1, 8);
    *a1 = 0;
  }
  return a1;
}

//----- (00474E80) --------------------------------------------------------
signed int  Render_InitDirectDrawWindowedMode(LPVOID *a1, void *a2, void *a3, DWORD a4, int a5)
{
  HDC DC; // ebx
  HRESULT v9; // eax
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // ecx
  unsigned int v13; // eax
  int v14; // ecx
  _DWORD *v15; // eax
  unsigned int v16; // eax
  int v17; // ecx
  _DWORD *v18; // eax
  unsigned int v19; // eax
  int v20; // ecx
  unsigned int v21; // eax
  int v22; // ecx
  unsigned int v23; // eax
  int v24; // ecx
  unsigned int v25; // eax
  int v26; // ecx
  int v28; // [esp+2Ch] [ebp-84h] BYREF
  int v29; // [esp+30h] [ebp-80h]
  int v30; // [esp+34h] [ebp-7Ch]
  DWORD v31; // [esp+38h] [ebp-78h]
  int v32; // [esp+94h] [ebp-1Ch]
  LPDIRECTDRAW lpDD; // [esp+98h] [ebp-18h] BYREF
  int DeviceCaps; // [esp+9Ch] [ebp-14h]
  int v35; // [esp+A0h] [ebp-10h]

  v35 = (int)a3;
  *a1 = 0;
  a1[10] = 0;
  a1[4] = 0;
  a1[6] = (LPVOID)a4;
  a1[7] = a3;
  a1[9] = a2;
  DC = GetDC(0);
  DeviceCaps = GetDeviceCaps(DC, 14);
  a1[8] = (LPVOID)(GetDeviceCaps(DC, 12) * DeviceCaps);
  ReleaseDC(0, DC);
  v9 = DirectDrawCreate(0, &lpDD, 0);
  if ( v9 )
    Render_HandleDirectDrawFatalError(v9, v10);
  v11 = lpDD->lpVtbl->QueryInterface(lpDD, &stru_51CA08, a1);
  if ( v11 )
    Render_HandleDirectDrawFatalError(v11, v12);
  if ( lpDD )
  {
    lpDD->lpVtbl->Release(lpDD);
    lpDD = 0;
  }
  v13 = (*(int (__stdcall **)(LPVOID, void *, int))(*(_DWORD *)*a1 + 80))(*a1, a2, 8);
  if ( v13 )
    Render_HandleDirectDrawFatalError(v13, v14);
  v28 = 108;
  v29 = 1;
  v32 = 512;
  v15 = (_DWORD *)Mem_Alloc(176, v14, 108, a4);
  if ( v15 )
    v15 = Surface_Construct(v15);
  a1[1] = v15;
  v16 = (*(int (__stdcall **)(LPVOID, int *, int, _DWORD))(*(_DWORD *)*a1 + 24))(*a1, &v28, (int)a1[1] + 164, 0);
  if ( v16 )
    Render_HandleDirectDrawFatalError(v16, v17);
  if ( a5 )
  {
    v18 = (_DWORD *)Mem_Alloc(176, v17, (char)&v28, a4);
    if ( v18 )
      v18 = Surface_Construct(v18);
    a1[2] = v18;
    v29 = 7;
    v32 = 64;
    v31 = a4;
    v30 = v35;
    v19 = (*(int (__stdcall **)(LPVOID, int *, int, _DWORD))(*(_DWORD *)*a1 + 24))(*a1, &v28, (int)a1[2] + 164, 0);
    if ( v19 )
      Render_HandleDirectDrawFatalError(v19, v20);
  }
  v21 = (*(int (__stdcall **)(LPVOID, _DWORD, LPVOID *, _DWORD))(*(_DWORD *)*a1 + 16))(*a1, 0, a1 + 5, 0);
  if ( v21 )
    Render_HandleDirectDrawFatalError(v21, v22);
  v23 = (*(int (__stdcall **)(LPVOID, _DWORD, void *))(*(_DWORD *)a1[5] + 32))(a1[5], 0, a2);
  if ( v23 )
    Render_HandleDirectDrawFatalError(v23, v24);
  v25 = (*(int (__stdcall **)(_DWORD, LPVOID))(**((_DWORD **)a1[1] + 41) + 112))(*((_DWORD *)a1[1] + 41), a1[5]);
  if ( v25 )
    Render_HandleDirectDrawFatalError(v25, v26);
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
        LPVOID *a1,
        _DWORD *a2,
        _DWORD *a3,
        _DWORD *a4,
        _DWORD *a5,
        int a6,
        DWORD a7)
{
  _DWORD *raw;
  HRESULT hr;
  _DWORD *v15; // ebx
  _DWORD *v18; // eax
  int v19; // ebx
  _DWORD *v23; // eax
  int v26; // [esp+34h] [ebp-80h] BYREF
  int v27; // [esp+38h] [ebp-7Ch]
  BOOL v28; // [esp+48h] [ebp-6Ch]
  int v29; // [esp+9Ch] [ebp-18h]
  int v30; // [esp+A0h] [ebp-14h] BYREF
  LPDIRECTDRAW lpDD; // [esp+A4h] [ebp-10h] BYREF

  raw = (_DWORD *)a1;
  raw[0] = 0;
  raw[10] = 1;
  raw[4] = 0;
  raw[6] = (int)(uintptr_t)a4;
  raw[7] = (int)(uintptr_t)a3;
  raw[2] = 0;
  raw[8] = (int)(uintptr_t)a5;
  raw[1] = raw[2];
  raw[9] = (int)(uintptr_t)a2;
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
  hr = Compat_DirectDraw_SetCooperativeLevel((LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0], (HWND)(uintptr_t)a2, 83);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( a6 )
  {
    v15 = (_DWORD *)(uintptr_t)(unsigned int)raw[6];
    hr = Compat_DirectDraw_SetDisplayMode(
           (LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0],
           (int)(uintptr_t)v15,
           raw[7],
           raw[8],
           0,
           1);
  }
  else
  {
    v15 = (_DWORD *)(uintptr_t)(unsigned int)raw[7];
    hr = Compat_DirectDraw_SetDisplayMode(
           (LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0],
           raw[6],
           (int)(uintptr_t)v15,
           raw[8],
           0,
           0);
  }
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  v18 = (_DWORD *)Mem_Alloc(176, 0, (char)v15, a7);
  if ( v18 )
    v18 = Surface_Construct(v18);
  raw[1] = (int)(uintptr_t)v18;
  v27 = 1;
  v29 = 512;
  v26 = 108;
  if ( a7 )
  {
    v27 = 33;
    v29 = 536;
  }
  v28 = a7 != 0;
  v19 = raw[0];
  hr = Compat_DirectDraw_CreateSurface((LPDIRECTDRAW)(uintptr_t)(unsigned int)raw[0], &v26, (_DWORD *)(uintptr_t)(unsigned int)raw[1] + 41);
  if ( hr )
    Render_HandleDirectDrawFatalError(hr, 0);
  if ( a7 )
  {
    v23 = (_DWORD *)Mem_Alloc(176, 0, v19, a7);
    if ( v23 )
      v23 = Surface_Construct(v23);
    raw[2] = (int)(uintptr_t)v23;
    v30 = 4;
    hr = Compat_DirectDrawSurface_GetAttachedSurface(
           (LPDIRECTDRAWSURFACE)*((_DWORD *)(uintptr_t)(unsigned int)raw[1] + 41),
           &v30,
           (_DWORD *)(uintptr_t)(unsigned int)raw[2] + 41);
    if ( hr )
      Render_HandleDirectDrawFatalError(hr, 0);
  }
  return 1;
}
// 51CA08: using guessed type IID stru_51CA08;

//----- (004753E0) --------------------------------------------------------
int  Render_RestoreLostSurfaceIfNeeded(int a1)
{
  int result; // eax
  int v3; // edx

  result = *(_DWORD *)(a1 + 4);
  if ( !result )
    return 0;
  v3 = *(_DWORD *)(result + 164);
  if ( v3 )
  {
    result = Compat_DirectDrawSurface_IsLost((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)v3);
    if ( result )
      return Compat_DirectDrawSurface_Restore((LPDIRECTDRAWSURFACE)(uintptr_t)(unsigned int)v3);
  }
  return result;
}

//----- (00475420) --------------------------------------------------------
int  Render_SetPaletteEntryColor(int a1, int a2, char a3, int a4, char a5)
{
  _BYTE v9[4]; // [esp+14h] [ebp-10h] BYREF
  int v10; // [esp+18h] [ebp-Ch]

  v10 = a4;
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int, _BYTE *))(**(_DWORD **)(a1 + 16) + 16))(
    *(_DWORD *)(a1 + 16),
    0,
    a2,
    1,
    v9);
  v9[0] = v10;
  v9[1] = a3;
  v9[2] = a5;
  return (*(int (__stdcall **)(_DWORD, _DWORD, int, int, _BYTE *))(**(_DWORD **)(a1 + 16) + 24))(
           *(_DWORD *)(a1 + 16),
           0,
           a2,
           1,
           v9);
}

//----- (004754B0) --------------------------------------------------------
int  IO_StreamWrite(int result, int a2, int a3, int a4)
{
  int v4; // esi

  v4 = *(_DWORD *)(result + 16);
  if ( v4 )
    return (*(int (__stdcall **)(int, _DWORD, int, int, int))(*(_DWORD *)v4 + 24))(v4, 0, a2, a4, a3);
  return result;
}

//----- (00475A83) --------------------------------------------------------
int  IO_ParseOpenModeFlags(unsigned __int8 *a1, _DWORD *a2)
{
  unsigned __int8 *v2; // ebx
  int v3; // ecx
  int v4; // ebp
  int v5; // esi
  int v6; // edi
  unsigned __int8 v7; // al
  unsigned __int8 v9; // al
  int Value; // [esp+0h] [ebp-18h]

  v2 = a1;
  v3 = 1;
  v4 = 0;
  v5 = 0;
  v6 = 0;
  Value = 0;
  if ( a2 )
    *a2 = dword_51A64C == 1;
  v7 = *a1;
  if ( *v2 < 0x72u )
  {
    if ( v7 == 97 )
    {
      LOBYTE(Value) = -126;
      goto LABEL_15;
    }
LABEL_14:
    _set_errno_(0);
    return 0;
  }
  if ( *v2 > 0x72u )
  {
    if ( v7 == 119 )
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
    v9 = *++v2;
    if ( !*v2 || !v3 )
      break;
    if ( v9 < 0x63u )
    {
      if ( v9 >= 0x2Bu )
      {
        if ( v9 <= 0x2Bu )
        {
          if ( v4 )
            goto LABEL_28;
          v4 = 1;
          LOBYTE(Value) = Value | 3;
        }
        else if ( v9 == 98 )
        {
          if ( v5 )
            goto LABEL_28;
          v5 = 1;
          LOBYTE(Value) = Value | 0x40;
        }
      }
    }
    else if ( v9 <= 0x63u )
    {
      if ( v6 )
        goto LABEL_28;
      v6 = 1;
      *(_BYTE *)a2 |= 1u;
    }
    else if ( v9 >= 0x6Eu )
    {
      if ( v9 <= 0x6Eu )
      {
        if ( v6 )
        {
LABEL_28:
          v3 = 0;
        }
        else
        {
          v6 = 1;
          *(_BYTE *)a2 &= ~1u;
        }
      }
      else if ( v9 == 116 )
      {
        if ( v5 )
          goto LABEL_28;
        v5 = 1;
      }
    }
  }
  if ( !v5 && g_CRT_DefaultFileTranslationMode == 512 )
    LOBYTE(Value) = Value | 0x40;
  return Value;
}
// 51A549: using guessed type int dword_51A549;
// 51A64C: using guessed type int dword_51A64C;

//----- (00475B9E) --------------------------------------------------------
int  IO_OpenStreamWithMode(
        const CHAR *a1,
        int a2,
        int a3,
        DWORD a4,
        int a5,
        int a6,
        int a7)
{
  unsigned int open_flags;
  int fd_index;
  int mode_char;

  (void)a5;
  (void)a6;
  *(_BYTE *)(a7 + 12) &= 0xFCu;
  *(_BYTE *)(a7 + 12) |= (unsigned __int8)a3;
  if ( (a3 & 0x80u) != 0 )
    mode_char = 'a';
  else if ( (a3 & 2) != 0 )
    mode_char = 'w';
  else
    mode_char = 'r';
  if ( mode_char == 'r' )
  {
    open_flags = 0;
    if ( (a3 & 2) != 0 )
      open_flags = 2;
    if ( (a3 & 0x40) != 0 )
      open_flags |= 0x200u;
    else
      open_flags |= 0x100u;
    fd_index = Compat_OpenFileDescriptor(a1, mode_char, a3);
  }
  else
  {
    open_flags = ((a3 & 1) != 0) + 33;
    if ( (a3 & 0x80u) == 0 )
      open_flags |= 0x40u;
    else
      open_flags |= 0x10u;
    if ( (a3 & 0x40) != 0 )
      open_flags |= 0x200u;
    else
      open_flags |= 0x100u;
    fd_index = Compat_OpenFileDescriptor(a1, mode_char, a3);
  }
  if ( fd_index == -1 )
  {
    Compat_FreeFileStream(a7);
    return 0;
  }
  Compat_InitFileStream(a7, fd_index, mode_char, a3);
  if ( (a3 & 0x80u) != 0 )
    Compat_StreamSeek(a7, 0, 2);
  _chktty_();
  return a7;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);
// 4884E3: using guessed type int _chktty_(void);

//----- (00475C84) --------------------------------------------------------
int  IO_OpenStream(
        const CHAR *a1,
        unsigned __int8 *a2,
        int a3,
        int a4,
        DWORD a5)
{
  int result; // eax
  int open_flags; // ebx
  int stream_ptr; // eax
  int v11[4]; // [esp+0h] [ebp-10h] BYREF

  v11[3] = a3;
  result = IO_ParseOpenModeFlags(a2, v11);
  open_flags = result;
  if ( result )
  {
    stream_ptr = Compat_AllocFileStream();
    if ( stream_ptr )
      return IO_OpenStreamWithMode(a1, v11[0], open_flags, a5, a4, 0, stream_ptr);
    return 0;
  }
  return result;
}

//----- (00475CC8) --------------------------------------------------------
int  IO_FOpen(const CHAR *a1, unsigned __int8 *a2, int a3, DWORD a4)
{
  return IO_OpenStream(a1, a2, a3, 0, a4);
}

//----- (00475CD2) --------------------------------------------------------
int  IO_CloseStream(int a1, int a2)
{
  int v3; // ecx
  _DWORD *i; // eax
  int v5; // edx
  int *j; // edx
  int *v8; // eax
  int v9; // edx

  g_CRT_StaticLock1AcquireHook();
  for ( i = (_DWORD *)dword_54DD88; i; i = (_DWORD *)*i )
  {
    v5 = i[1];
    if ( a1 == v5 )
    {
      if ( (*(_BYTE *)(v5 + 12) & 3) != 0 )
        _doclose_(v3, 1);
LABEL_6:
      g_CRT_StaticLock1ReleaseHook();
      return a1;
    }
  }
  for ( j = &dword_54DD8C; ; j = (int *)*j )
  {
    v8 = (int *)*j;
    if ( !*j )
      break;
    if ( a1 == v8[1] )
    {
      *j = *v8;
      v9 = dword_54DD88;
      dword_54DD88 = (int)v8;
      *v8 = v9;
      goto LABEL_6;
    }
  }
  _set_errno_(a2);
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
char * Str_FormatUnsignedRadixDigits(unsigned int a1, char *a2, unsigned int a3)
{
  char *v3; // esi
  char *v4; // ecx
  char v5; // al
  char v7; // [esp+1h] [ebp-37h] BYREF
  unsigned int v8; // [esp+24h] [ebp-14h]

  v3 = a2;
  v4 = &v7;
  do
  {
    v8 = a1 / a3;
    *v4 = g_Str_RadixDigitCharacters[a1 % a3];
    a1 = v8;
    ++v4;
  }
  while ( v8 );
  do
  {
    v5 = *--v4;
    *v3++ = *v4;
  }
  while ( v5 );
  return a2;
}

//----- (00476238) --------------------------------------------------------
int  Str_FormatSignedRadixDigits(signed int a1, char *a2, unsigned int a3)
{
  int v3; // ecx

  if ( a3 == 10 && a1 < 0 )
  {
    a1 = -a1;
    *a2++ = 45;
  }
  Str_FormatUnsignedRadixDigits(a1, a2, a3);
  return v3;
}
// 47624F: variable 'v3' is possibly undefined

//----- (004762AE) --------------------------------------------------------
unsigned int  IO_OpenFileDescriptorBinaryMode(const CHAR *a1, DWORD a2)
{
  return CRT_OpenFile(a2, a1, 98);
}

//----- (00476301) --------------------------------------------------------
int Output_WriteFormatted(int a1, int a2, int a3, int a4, ...)
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
  if ( !a3 || !a4 )
    return 0;

  format = (const char *)(uintptr_t)(unsigned int)a4;
  arg_count = Compat_CountPrintfArgs32(format);
  if ( arg_count <= 0 )
  {
    cursor = 0;
    return CRT_VfprintfLockedWrite(a3, a4, &cursor);
  }

  args_ptr = Compat_AllocLow32Bytes(4 * arg_count);
  if ( !args_ptr )
    return 0;

  va_start(args, a4);
  for ( i = 0; i < arg_count; ++i )
    *(_DWORD *)(uintptr_t)(unsigned int)(args_ptr + 4 * i) = va_arg(args, int);
  va_end(args);

  cursor = args_ptr;
  result = CRT_VfprintfLockedWrite(a3, a4, &cursor);
  Compat_FreeLow32Bytes(args_ptr);
  return result;
}

//----- (00476A0C) --------------------------------------------------------
void __thiscall Compat_TriggerFatalRuntimeErrorOnce(void *this)
{
  if ( !word_51A644 )
  {
    word_51A644 = 1;
    _wcpp_4_fatal_runtime_error__(this, 1);
  }
}
// 486342: using guessed type int __fastcall _wcpp_4_fatal_runtime_error__(_DWORD, _DWORD);
// 51A644: using guessed type __int16 word_51A644;

//----- (00476A80) --------------------------------------------------------
int FileSystem_InitCurrentEntryPathHolder()
{
  dword_54DD00 = 0;
  dword_54DD04 = (int)&g_PathEntry_Vtable;
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
int  FileSystem_ConstructMountTable(int a1, int a2, const CHAR *a3, DWORD a4)
{
  int entry_path_holder; // [esp+4h] [ebp-1Ch] BYREF
  int (**entry_path_vtable)(); // [esp+8h] [ebp-18h]
  int open_mode_handle; // [esp+Ch] [ebp-14h]
  _DWORD *entry_record;
  int entry_index;
  int child_path;

  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)(a1 + 8) = (int)&g_PathEntry_Vtable;
  *(_DWORD *)(a1 + 12) = 0;
  *(_DWORD *)(a1 + 16) = (int)&g_PathEntry_Vtable;
  *(_DWORD *)(a1 + 24) = 1;
  *(_DWORD *)(a1 + 28) = 0;
  *(_DWORD *)(a1 + 32) = 0;
  *(_DWORD *)(a1 + 36) = (int)g_PathEntryArray_Vtable;
  *(_DWORD *)(a1 + 20) = 0;
  *(_DWORD *)a1 = (int)g_FileSystemMountTable_VTable;
  open_mode_handle = 0;
  if ( a3 )
    open_mode_handle = IO_FOpen(a3, (unsigned __int8 *)aWt, a1, a4);
  entry_path_holder = 0;
  entry_path_vtable = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&entry_path_holder);
  entry_path_vtable = &g_PathEntry_Vtable;
  if ( *(_DWORD *)(a1 + 28) == *(_DWORD *)(a1 + 32) )
    PathEntryArray_GrowByDelta((_DWORD *)(a1 + 20), *(_DWORD *)(a1 + 24));
  entry_index = *(_DWORD *)(a1 + 28);
  *(_DWORD *)(a1 + 28) = entry_index + 1;
  entry_record = (_DWORD *)(16 * entry_index + *(_DWORD *)(a1 + 20));
  *entry_record = a2;
  Compat_StringHolderCopyText(entry_record + 1, Compat_StringHolderGetText((_DWORD *)&entry_path_holder));
  entry_record[3] = open_mode_handle;
  FileSystem_DiskMountResolveRegisteredRootPath(a2, a1);
  child_path = (int)(intptr_t)FileSystem_DiskMountGetCurrentDirectory((void *)(intptr_t)a2);
  if ( child_path )
    FileSystem_SetCurrentDirectoryFromPath((const char **)(intptr_t)a1, child_path);
  Compat_StringHolderDestroyStack((_DWORD *)&entry_path_holder, 0);
  return a1;
}

//----- (00476C30) --------------------------------------------------------
int  FileSystem_DestructMountTable(_DWORD *a1, char a2)
{
  _DWORD *v3; // ecx
  int v4; // ecx
  int v5; // eax
  int v6; // eax
  int v8; // ecx
  int v9; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileSystemMountTable_DtorArrayTag);
    j_j__nfree_();
    return v8;
  }
  else
  {
    *a1 = g_FileSystemMountTable_VTable;
    FileSystem_RemoveMountsFromIndex((int)a1, 0);
    v3[4] = g_PathEntryArray_Vtable;
    PathEntryArray_DestructElements(v3);
    v5 = Compat_StringHolderScalarDeletingDtor(v4 - 8, 0);
    v6 = Compat_StringHolderScalarDeletingDtor(v5 - 8, 0);
    if ( (a2 & 2) != 0 )
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
_DWORD * FileSystem_RemoveMountsFromIndex(int a1, int a2)
{
  int v2; // ecx
  _DWORD *result; // eax
  _DWORD *v4; // edi
  _DWORD *v5; // ebp
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  _DWORD *v9; // [esp+0h] [ebp-1Ch]

  v2 = *(_DWORD *)(a1 + 28) - 1;
  result = (_DWORD *)(a1 + 20);
  if ( v2 >= a2 )
  {
    v4 = result;
    v5 = result;
    v9 = result;
    v6 = 16 * v2;
    do
    {
      v7 = *(_DWORD *)(v6 + *v9);
      if ( v7 )
        (*(void (**)(void))(*(_DWORD *)v7 + 8))();
      if ( *(_DWORD *)(v6 + *v5 + 12) )
      {
        fclose_(v2);
        *(_DWORD *)(v6 + *v5 + 12) = 0;
      }
      result = PathEntryArray_RemoveAt(v4, v2, 1);
      v2 = v8 - 1;
      v6 -= 16;
    }
    while ( v2 >= a2 );
  }
  return result;
}
// 476CDD: variable 'v2' is possibly undefined
// 476CFF: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00476D20) --------------------------------------------------------
char  FileSystem_NormalizePath(int a1, const char **a2)
{
  const char *path_text;
  signed int colon_index;
  signed int search_index;
  int dot_index;
  int dot_next_index;
  int parent_index;
  _DWORD v18[2];

  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a2);
  if ( !path_text || !*path_text )
    return 0;
  if ( Compat_StringHolderFindCharFrom(a2, 58, 0) == -1 )
  {
    if ( *path_text == 92 )
    {
      Compat_StringHolderPrependText(a2, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 4));
    }
    else
    {
      v18[0] = 0;
      v18[1] = (int)&g_PathEntry_Vtable;
      Compat_StringHolderConstructJoined(v18, (_DWORD *)(uintptr_t)(unsigned int)(a1 + 4), (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 12));
      Compat_StringHolderPrependText(a2, Compat_StringHolderGetText(v18));
      Compat_StringHolderDestroyStack(v18, 1);
    }
  }
  colon_index = Compat_StringHolderFindCharFrom(a2, 58, 0) + 1;
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a2);
  if ( !path_text || path_text[colon_index] != 92 )
    Compat_StringHolderInsertTextChecked(a2, colon_index, asc_5024B0);
  search_index = 0;
  while ( 1 )
  {
    dot_index = Compat_StringHolderFindCharFrom(a2, 46, search_index);
    if ( dot_index == -1 )
      break;
    dot_next_index = dot_index + 1;
    path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a2);
    if ( !path_text )
      break;
    if ( path_text[dot_next_index] == 46 )
    {
      if ( path_text[dot_index - 1] != 92 || (parent_index = Compat_StringHolderFindLastBackslashBefore((char **)a2, dot_index - 2), parent_index == -1) )
      {
        Compat_StringHolderCopyText((_DWORD *)a2, "");
        return 0;
      }
      Compat_StringHolderRemoveRange((char **)a2, parent_index, (unsigned int)(uintptr_t)a2, dot_index - parent_index + 2);
    }
    else if ( path_text[dot_index - 1] == 92 )
    {
      Compat_StringHolderRemoveRange((char **)a2, dot_index - 1, (unsigned int)(uintptr_t)a2, 2);
    }
    else
    {
      search_index = dot_next_index;
    }
  }
  colon_index = Compat_StringHolderFindCharFrom(a2, 58, 0) + 1;
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a2);
  if ( !path_text || path_text[colon_index] != 92 )
    Compat_StringHolderInsertTextChecked(a2, colon_index, asc_5024B4);
  return (char)(unsigned __int8)(uintptr_t)Compat_StringHolderUppercaseInPlace(a2, (unsigned int)(uintptr_t)a2);
}

//----- (00476ED0) --------------------------------------------------------
const char ** FileSystem_StripMountPrefix(int a1, int a2, unsigned int a3, const char **a4)
{
  const char *entry_path;
  const char *holder_text;
  unsigned int holder_len;
  int entry_path_len;
  const char **result; // eax

  entry_path = Compat_StringHolderGetText((_DWORD *)(uintptr_t)(16 * a2 + *(_DWORD *)(a1 + 20) + 4));
  if ( entry_path )
  {
    a3 = (unsigned int)strlen(entry_path);
    entry_path_len = (int)a3;
  }
  else
  {
    entry_path_len = 0;
  }
  result = Compat_StringHolderRemoveRange((char **)a4, 0, a3, entry_path_len);
  holder_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)a4);
  if ( holder_text )
  {
    holder_len = (unsigned int)strlen(holder_text) + 1;
    if ( holder_len != 1 && *(const unsigned char *)holder_text == 92 )
      return Compat_StringHolderRemoveRange((char **)a4, 0, holder_len - 1, 1);
  }
  return a4;
}

//----- (00476F40) --------------------------------------------------------
int  FileSystem_CallEntryOpSlot12(int a1)
{
  return (*(int (**)(void))(**(_DWORD **)a1 + 48))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00476F60) --------------------------------------------------------
signed int  FileSystem_FindMatchingMountIndex(int a1, const char **a2, int a3)
{
  const char *entry_path;
  unsigned int entry_path_len;
  unsigned int requested_path_len;
  int current_index;
  int current_offset;
  int limit_offset;

  current_index = a3;
  if ( a3 >= *(_DWORD *)(a1 + 28) )
    return -1;
  current_offset = 16 * a3;
  limit_offset = 16 * *(_DWORD *)(a1 + 28);
  do
  {
    entry_path = Compat_StringHolderGetText((_DWORD *)(current_offset + *(_DWORD *)(a1 + 20) + 4));
    if ( entry_path )
      entry_path_len = strlen(entry_path);
    else
      entry_path_len = 0;
    if ( !entry_path_len )
      return current_index;
    if ( *a2 )
      requested_path_len = strlen(*a2);
    else
      requested_path_len = 0;
    if ( entry_path_len < requested_path_len )
    {
      if ( !memcmp(*a2, entry_path, entry_path_len) && (*a2)[entry_path_len] == 92 )
        return current_index;
    }
    else if ( entry_path_len == requested_path_len && !memcmp(*a2, entry_path, requested_path_len) )
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
int  FileSystem_ResolveAndInvokeForPath(int a1, int a2, int (*a3)(void))
{
  int matched_index; // eax
  int callback_result; // eax
  int next_index; // eax
  const char *v11; // [esp+0h] [ebp-18h] BYREF
  int (**v12)(); // [esp+4h] [ebp-14h]
  int v13; // [esp+8h] [ebp-10h]

  v11 = 0;
  v12 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v11);
  v12 = &g_PathEntry_Vtable;
  FileSystem_NormalizePath(a1, &v11);
  if ( v11 && *v11 )
  {
    v13 = a1 + 20;
    next_index = 0;
    while ( 1 )
    {
      matched_index = FileSystem_FindMatchingMountIndex(a1, &v11, next_index);
      if ( matched_index == -1 )
        break;
      Compat_StringHolderDestructor(&dword_54DD00);
      FileSystem_StripMountPrefix(a1, matched_index, matched_index, (const char **)&dword_54DD00);
      callback_result = a3();
      if ( callback_result != a2 )
      {
        Compat_StringHolderDestroyStack((_DWORD *)&v11, 1);
        return callback_result;
      }
      next_index = matched_index + 1;
    }
  }
  Compat_StringHolderDestroyStack((_DWORD *)&v11, 1);
  return a2;
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
      Compat_StringHolderCopyText(&dword_54DD00, Compat_StringHolderGetText((_DWORD *)&normalized_path));
      FileSystem_StripMountPrefix(filesystem, current_entry, current_entry, (const char **)&dword_54DD00);
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
int  FileSystem_TryOpenEntryCallback(int a1)
{
  int v3; // ebx

  v3 = Compat_FileSystemOpenIfReady(*(_DWORD *)a1, dword_54DD08);
  if ( !*(_DWORD *)(a1 + 12) )
    return v3;
  if ( v3 )
  {
    Output_WriteFormatted(a1 + 12, dword_54DD00, *(_DWORD *)(a1 + 12), (int)aS_15, dword_54DD00);
    return v3;
  }
  Output_WriteFormatted(a1 + 12, dword_54DD00, *(_DWORD *)(a1 + 12), (int)aS_2, dword_54DD00);
  return v3;
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (004771D0) --------------------------------------------------------
signed int  FileSystem_SetCurrentDirectoryFromPath(const char **a1, int a2)
{
  _DWORD *fs_words;
  unsigned int path_len_with_nul;
  int colon_index;
  const char *root_text;
  unsigned int root_text_len;
  unsigned int normalized_text_len;
  const char *v10; // [esp+0h] [ebp-20h] BYREF
  int (**v11)(); // [esp+4h] [ebp-1Ch]

  fs_words = (_DWORD *)(uintptr_t)a1;
  if ( !(*((int (__thiscall **)(int))*a1 + 12))(a2) )
    return 0;
  v10 = 0;
  v11 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderInitText((_DWORD *)&v10, (const char *)(uintptr_t)(unsigned int)a2);
  v11 = &g_PathEntry_Vtable;
  FileSystem_NormalizePath((int)a1, &v10);
  if ( v10 && *v10 )
  {
    path_len_with_nul = (unsigned int)strlen(v10) + 1;
    if ( path_len_with_nul >= 2 && v10[path_len_with_nul - 2] != 92 )
      Compat_StringHolderInsertTextChecked(&v10, path_len_with_nul - 1, asc_5024C0);
    colon_index = Compat_StringHolderFindCharFrom(&v10, 58, 0);
    Compat_StringHolderCopyText(fs_words + 1, v10);
    root_text = Compat_StringHolderGetText(fs_words + 1);
    if ( root_text )
      root_text_len = (unsigned int)strlen(root_text);
    else
      root_text_len = 0;
    Compat_StringHolderRemoveRange((char **)(fs_words + 1), colon_index + 1, root_text_len, (int)(root_text_len - (unsigned int)(colon_index + 1)));
    normalized_text_len = (unsigned int)strlen(v10);
    Compat_StringHolderRemoveRange(&v10, 0, normalized_text_len, colon_index + 1);
    Compat_StringHolderCopyText(fs_words + 3, v10);
    Compat_StringHolderScalarDeletingDtor((int)&v10, 1);
    return 1;
  }
  else
  {
    Compat_StringHolderScalarDeletingDtor((int)&v10, 1);
    return 0;
  }
}
// 477288: variable 'v5' is possibly undefined
// 4772A3: variable 'v7' is possibly undefined
// 4772B1: variable 'v9' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00477300) --------------------------------------------------------
int  FileSystem_ResolveRelativeToCurrentDir(int a1, int a2)
{
  int v3; // edx
  int v5; // [esp-10h] [ebp-14h]
  _DWORD v6[4]; // [esp-Ch] [ebp-10h] BYREF

  v3 = a1;
  if ( (byte_54DCF8 & 1) == 0 )
  {
    v5 = a2;
    byte_54DCF8 |= 1u;
    dword_54DCF0 = 0;
    dword_54DCF4 = (int)&g_PathEntry_Vtable;
    CRT_RegisterFinalizableObject(0, a1);
    a2 = v5;
  }
  Compat_StringHolderConstructJoined(v6, a2, *(const char **)(v3 + 12));
  Compat_StringHolderDestructor(&dword_54DCF0);
  Compat_StringHolderScalarDeletingDtor((int)v6, 1);
  return dword_54DCF0;
}
// 477312: variable 'v3' is possibly undefined
// 473ED5: using guessed type int __fastcall CRT_RegisterFinalizableObject(_DWORD, _DWORD);
// 50EC94: using guessed type int (*off_50EC94)();
// 54DCF0: using guessed type int dword_54DCF0;
// 54DCF4: using guessed type int dword_54DCF4;
// 54DCF8: using guessed type char byte_54DCF8;

//----- (00477370) --------------------------------------------------------
int  FileSystem_AddMountEntry(int *a1, const CHAR *a2, const CHAR *a3, DWORD a4)
{
  int archive_mode; // eax
  const char *v6; // eax
  unsigned int v8; // ecx
  _DWORD *v10; // ecx
  int v11; // edx
  _DWORD *v12; // ecx
  _DWORD *v13; // ebx
  const char *v18; // [esp+10h] [ebp-18h] BYREF
  int (**v19)(); // [esp+14h] [ebp-14h]
  const CHAR *v20; // [esp+18h] [ebp-10h]

  archive_mode = 0;
  v20 = a3;
  v18 = 0;
  v19 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderInitText((_DWORD *)&v18, a2);
  FileSystem_NormalizePath((int)a1, &v18);
  v6 = Compat_StringHolderGetText((_DWORD *)&v18);
  if ( v6 && *v6 )
  {
    v8 = strlen(v6);
    if ( v8 && v6[v8 - 1] == 92 )
    {
      Compat_StringHolderRemoveRange((char **)&v18, (int)(v8 - 1), (unsigned int)(uintptr_t)&v18, 1);
    }
    if ( v20 )
      archive_mode = IO_FOpen(v20, (unsigned __int8 *)aWt_0, 0, a4);
    v10 = a1 + 5;
    if ( a1[7] == a1[8] )
      PathEntryArray_GrowByDelta(a1 + 5, a1[6]);
    v11 = v10[2];
    v10[2] = v11 + 1;
    v12 = (_DWORD *)(16 * v11 + *v10);
    *v12 = a4;
    v13 = v12 + 1;
    Compat_StringHolderCopyText(v13, Compat_StringHolderGetText((_DWORD *)&v18));
    v12[3] = archive_mode;
    Compat_FileSystemOnMounted((int)a4, a1);
  }
  return Compat_StringHolderDestroyStack((_DWORD *)&v18, 1);
}
// 477460: variable 'v9' is possibly undefined
// 477478: variable 'v10' is possibly undefined
// 4774A6: variable 'v14' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004774D0) --------------------------------------------------------
_DWORD * FileSystem_CreateEntryHandleWrapper(DWORD *a1, int a2, int a3)
{
  _DWORD *result; // eax
  DWORD v6; // ebp
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  _DWORD *v10; // esi
  _DWORD *v11; // [esp+0h] [ebp-10h]

  result = (_DWORD *)(*(int (__fastcall **)(int, int))(*a1 + 12))(a2, a3);
  v11 = result;
  if ( result )
  {
    v6 = *a1;
    if ( (*(int (**)(void))(*a1 + 16))() )
    {
      result = (_DWORD *)Mem_Alloc(16, v7, 10, v6);
      v10 = result;
      if ( result )
      {
        *result = v9;
        result[2] = v11;
        result[3] = v8;
        result[1] = j_Mem_Alloc(v9);
        return v10;
      }
    }
    else
    {
      (*(void (**)(void))(*a1 + 20))();
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
int  FileSystem_AdvanceEntryEnumerator(int a1)
{
  int v1; // esi
  int v2; // ecx

  v1 = (*(int (__fastcall **)(int, _DWORD))(**(_DWORD **)(a1 + 8) + 20))(a1, *(_DWORD *)(a1 + 4));
  (*(void (__fastcall **)(int, _DWORD))(**(_DWORD **)(v2 + 12) + 24))(v2, *(_DWORD *)(v2 + 4));
  return v1;
}
// 477566: variable 'v2' is possibly undefined

//----- (00477580) --------------------------------------------------------
int  Compat_FileSystemReleaseFileRecord(int a1, int *a2)
{
  int v3; // ecx
  int result; // eax

  (*(void (__fastcall **)(int, int))(*(_DWORD *)a1 + 20))(a1, *a2 + 8);
  (*(void (__fastcall **)(int, int))(*(_DWORD *)v3 + 20))(v3, *a2 + 12);
  result = *a2;
  if ( *a2 )
  {
    Compat_FileSystemFreeFileRecordName();
    result = j__nfree_();
  }
  *a2 = 0;
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
signed int  Compat_FileSystemVisitFile(DWORD *a1, int a2, int a3)
{
  int v5; // ecx
  _DWORD *v7; // [esp+0h] [ebp-8h] BYREF

  v7 = FileSystem_CreateEntryHandleWrapper(a1, a2, a3);
  if ( !v7 )
    return -1;
  while ( FileSystem_AdvanceEntryEnumerator((int)v7) )
    ;
  Compat_FileSystemReleaseFileRecord((int)a1, (int *)&v7);
  return v5;
}
// 47760B: variable 'v5' is possibly undefined

//----- (00477620) --------------------------------------------------------
_DWORD * Compat_FileSystemReleaseMountedPaths(int a1)
{
  int v1; // ecx
  _DWORD *result; // eax
  _DWORD *v3; // esi
  int v4; // edx

  v1 = *(_DWORD *)(a1 + 28) - 1;
  result = (_DWORD *)(a1 + 20);
  if ( v1 >= 0 )
  {
    v3 = result;
    v4 = 16 * v1;
    do
      result = (_DWORD *)(*(int (__fastcall **)(int, int))(**(_DWORD **)(v4 + *v3) + 40))(v1 - 1, v4 - 16);
    while ( v4 >= 0 );
  }
  return result;
}
// 477638: variable 'v4' is possibly undefined
// 477640: variable 'v1' is possibly undefined

//----- (00477660) --------------------------------------------------------
int  Compat_FileSystemProcessDirectChildren(int (__thiscall ***a1)(_DWORD), int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v8; // [esp+0h] [ebp-18h] BYREF
  int v9; // [esp+4h] [ebp-14h]
  int v10; // [esp+8h] [ebp-10h]
  int v11; // [esp+10h] [ebp-8h]

  v11 = a2;
  v8 = (**a1)(0);
  v9 = (int)a1;
  v10 = v3;
  FileSystem_WalkEntryListInvokingCleanup((int)&v8);
  for ( ; v8; v4 = v5 + 1 )
  {
    if ( !(*(int (**)(void))(*(_DWORD *)v8 + 12))() )
      break;
    (*(void (**)(void))(*(_DWORD *)v8 + 16))();
    FileSystem_WalkEntryListInvokingCleanup((int)&v8);
  }
  (*(void (__fastcall **)(int, int))(*(_DWORD *)v9 + 4))(v4, v8);
  return v6;
}
// 477677: variable 'v3' is possibly undefined
// 4776A7: variable 'v5' is possibly undefined
// 4776B9: variable 'v4' is possibly undefined
// 4776BC: variable 'v6' is possibly undefined

//----- (004776D0) --------------------------------------------------------
int  Compat_FileSystemFindMountedPathById(int a1, int a2)
{
  int v3; // edx
  _DWORD *v4; // eax
  _DWORD *v5; // esi
  int v6; // eax
  _DWORD *v7; // ecx

  v3 = *(_DWORD *)(a1 + 28) - 1;
  v4 = (_DWORD *)(a1 + 20);
  if ( v3 < 0 )
    return 0;
  v5 = v4;
  v6 = 16 * v3;
  while ( 1 )
  {
    v7 = (_DWORD *)(v6 + *v5);
    if ( a2 == *v7 )
      break;
    v6 -= 16;
    --v3;
    if ( v6 < 0 )
      return 0;
  }
  return v7[1];
}

//----- (00477710) --------------------------------------------------------
signed int  Compat_FileSystemWalkDirectoryTree(int (***a1)(void), int a2, int a3)
{
  const char *v4; // ecx
  int v5; // edi
  const char *v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v14; // ebx
  int v15; // ecx
  int v16; // [esp+0h] [ebp-48h] BYREF
  int (***v17)(void); // [esp+4h] [ebp-44h]
  int v18; // [esp+8h] [ebp-40h]
  _DWORD v19[2]; // [esp+Ch] [ebp-3Ch] BYREF
  const char *v20; // [esp+14h] [ebp-34h] BYREF
  int (**v21)(); // [esp+18h] [ebp-30h]
  const char *v22; // [esp+1Ch] [ebp-2Ch] BYREF
  int (**v23)(); // [esp+20h] [ebp-28h]
  const char *v24; // [esp+24h] [ebp-24h] BYREF
  int (**v25)(); // [esp+28h] [ebp-20h]
  _DWORD v26[2]; // [esp+2Ch] [ebp-1Ch] BYREF
  _DWORD v27[2]; // [esp+34h] [ebp-14h] BYREF
  _DWORD v28[2]; // [esp+3Ch] [ebp-Ch] BYREF
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
  v16 = (**a1)();
  v18 = v29;
  v17 = a1;
  FileSystem_WalkEntryListInvokingCleanup((int)&v16);
  v5 = 0;
  if ( v16 )
  {
    while ( (*(int (**)(void))(*(_DWORD *)v16 + 12))() )
    {
      (**(void (__thiscall ***)(_DWORD))v16)(0);
      v24 = v6;
      v25 = &g_CompatStringHolder_Vtable;
      Compat_StringHolderDestructor(&v24);
      v25 = &g_PathEntry_Vtable;
      Compat_StringHolderConstructJoined(v28, v7, v24);
      if ( strcmp_(v8, a__34) && strcmp_(v9, a___1) )
      {
        if ( ((*(int (**)(void))(*(_DWORD *)v16 + 4))() & 0x10) != 0 )
        {
          Compat_StringHolderConstructJoined(v27, v10, v24);
          v5 += Compat_FileSystemProcessDirectChildren((int (__thiscall ***)(_DWORD))a1, v11);
          Compat_StringHolderScalarDeletingDtor((int)v27, 1);
          (*a1)[6]();
          Compat_StringHolderConstructJoined(v19, v29, v24);
          Compat_FileSystemWalkDirectoryTree((int)a1, v12, a3);
          Compat_StringHolderScalarDeletingDtor((int)v19, 1);
        }
        else
        {
          v14 = *Compat_StringHolderConstructJoined(v26, a3, v24);
          LOBYTE(v14) = Compat_FileSystemVisitFile((DWORD *)a1, v15, v14) == -1;
          Compat_StringHolderScalarDeletingDtor((int)v26, 1);
          if ( (_BYTE)v14 )
          {
            Compat_StringHolderScalarDeletingDtor((int)v28, 1);
            v5 = -1;
            Compat_StringHolderScalarDeletingDtor((int)&v24, 1);
            break;
          }
        }
      }
      Compat_StringHolderScalarDeletingDtor((int)v28, 1);
      Compat_StringHolderScalarDeletingDtor((int)&v24, 1);
      (*(void (**)(void))(*(_DWORD *)v16 + 16))();
      FileSystem_WalkEntryListInvokingCleanup((int)&v16);
      if ( !v16 )
        break;
    }
  }
  (*v17)[1]();
  Compat_StringHolderScalarDeletingDtor((int)&v22, 1);
  Compat_StringHolderScalarDeletingDtor((int)&v20, 1);
  return v5;
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
  bool v11; // bl
  int v12; // ebx
  int v14; // esi
  int v15; // [esp+0h] [ebp-40h] BYREF
  int v16; // [esp+4h] [ebp-3Ch]
  int v17; // [esp+8h] [ebp-38h]
  _DWORD v18[2]; // [esp+Ch] [ebp-34h] BYREF
  _DWORD v19[2]; // [esp+14h] [ebp-2Ch] BYREF
  const char *v20; // [esp+1Ch] [ebp-24h] BYREF
  int (**v21)(); // [esp+20h] [ebp-20h]
  const char *v22; // [esp+24h] [ebp-1Ch] BYREF
  int (**v23)(); // [esp+28h] [ebp-18h]

  v22 = 0;
  v23 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v22);
  v23 = &g_PathEntry_Vtable;
  Compat_StringHolderAppendText(&v22, asc_5024CE);
  v15 = (**v3)(v3, v22);
  v16 = v4;
  v17 = 0;
  FileSystem_WalkEntryListInvokingCleanup((int)&v15);
  if ( v15 )
  {
    while ( (*(int (**)(void))(*(_DWORD *)v15 + 12))() )
    {
      (**(void (***)(void))v15)();
      v20 = 0;
      v21 = &g_CompatStringHolder_Vtable;
      Compat_StringHolderDestructor(&v20);
      v21 = &g_PathEntry_Vtable;
      if ( strcmp_(v6, a__35) && strcmp_(v7, a___2) )
      {
        if ( ((*(int (**)(void))(*(_DWORD *)v15 + 4))() & 0x10) != 0 )
        {
          v9 = Compat_StringHolderConstructJoined(v19, (int)v8, v20);
          v11 = Compat_FileSystemWalkDirectoryEntries(v10, *v9) == -1;
          Compat_StringHolderScalarDeletingDtor((int)v19, 1);
          if ( v11 )
          {
            Compat_StringHolderScalarDeletingDtor((int)&v20, 1);
            (*(void (**)(void))(*(_DWORD *)v16 + 4))();
            Compat_StringHolderScalarDeletingDtor((int)&v22, 1);
            return -1;
          }
        }
        else
        {
          v14 = *v8;
          Compat_StringHolderConstructJoined(v18, (int)v8, v20);
          (*(void (**)(void))(v14 + 32))();
          Compat_StringHolderScalarDeletingDtor((int)v18, 1);
        }
      }
      Compat_StringHolderScalarDeletingDtor((int)&v20, 1);
      (*(void (**)(void))(*(_DWORD *)v15 + 16))();
      FileSystem_WalkEntryListInvokingCleanup((int)&v15);
      if ( !v15 )
        break;
    }
  }
  v12 = (*(int (__fastcall **)(int, int))(*(_DWORD *)v5 + 28))(v5, a2);
  (*(void (**)(void))(*(_DWORD *)v16 + 4))();
  Compat_StringHolderScalarDeletingDtor((int)&v22, 1);
  return v12;
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
int __fastcall Compat_FileSystemCloseQuery(int a1, int a2)
{
  int result; // eax

  result = a2;
  if ( a2 )
    return (*(int (__cdecl **)(int))(*(_DWORD *)a2 + 20))(a1);
  return result;
}

//----- (00477B40) --------------------------------------------------------
int  Compat_FileSystemInvokeInnerHandleMethod(int a1, int a2)
{
  int v2; // ecx

  (*(void (__cdecl **)(int))(**(_DWORD **)(a1 + 4) + 4))(a2);
  return v2;
}
// 477B4E: variable 'v2' is possibly undefined

//----- (00477B60) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot16(int a1)
{
  return (*(int (**)(void))(**(_DWORD **)a1 + 16))();
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (00477B80) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot32(int a1)
{
  return (*(int (**)(void))(**(_DWORD **)a1 + 32))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477BA0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot24(int a1)
{
  return (*(int (**)(void))(**(_DWORD **)a1 + 24))();
}
// 54DD00: using guessed type int dword_54DD00;
// 54DD08: using guessed type int dword_54DD08;

//----- (00477BC0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot28(int a1)
{
  return (*(int (**)(void))(**(_DWORD **)a1 + 28))();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477BE0) --------------------------------------------------------
int  Compat_FileSystemMountInvokeSlot0(int (****a1)(void))
{
  return (***a1)();
}
// 54DD00: using guessed type int dword_54DD00;

//----- (00477C00) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot0(int a1)
{
  return FileSystem_ResolveAndInvokeForPath(a1, 0, (int (*)(void))Compat_FileSystemMountInvokeSlot0);
}

//----- (00477C20) --------------------------------------------------------
int  Compat_FileSystemForEachMountPrintSearchResult(int a1, int a2)
{
  dword_54DD08 = a2;
  return FileSystem_ResolveAndInvokeForPath(a1, 0, (int (*)(void))FileSystem_TryOpenEntryCallback);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477C40) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot16(int a1, int a2)
{
  dword_54DD08 = a2;
  return FileSystem_ResolveAndInvokeForPath(a1, 0, (int (*)(void))Compat_FileSystemMountInvokeSlot16);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477C60) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot32(int a1)
{
  return FileSystem_ResolveAndInvokeForPath(a1, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot32);
}

//----- (00477C80) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot24(int a1, int a2)
{
  dword_54DD08 = a2;
  return FileSystem_ResolveAndInvokeForPath(a1, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot24);
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00477CA0) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeSlot28(int a1)
{
  return FileSystem_ResolveAndInvokeForPath(a1, -1, (int (*)(void))Compat_FileSystemMountInvokeSlot28);
}

//----- (00477CC0) --------------------------------------------------------
int  Compat_FileSystemForEachMountInvokeCallback(int a1)
{
  return FileSystem_ResolveAndInvokeForPath(a1, 0, (int (*)(void))FileSystem_CallEntryOpSlot12);
}

//----- (00477CE0) --------------------------------------------------------
_DWORD * Compat_FileStreamOpen(_DWORD *a1, const CHAR *a2, int a3, char a4, DWORD a5)
{
  char *v7; // edx

  *a1 = g_CompatFileStream_VTable;
  if ( (a4 & 0x10) != 0 )
  {
    if ( (a4 & 2) != 0 )
      v7 = aAb_0;
    else
      v7 = aA_3;
  }
  else if ( (a4 & 8) != 0 )
  {
    if ( (a4 & 2) != 0 )
      v7 = aWb_8;
    else
      v7 = aW_7;
  }
  else if ( (a4 & 2) != 0 )
  {
    v7 = aRb_10;
  }
  else
  {
    v7 = aR_7;
  }
  a1[1] = IO_FOpen(a2, (unsigned __int8 *)v7, a3, a5);
  if ( (a4 & 0x20) != 0 )
    Compat_StreamSetBuffer((int)a1[1], 0x1800);
  return a1;
}
// 5109C4: using guessed type int (*off_5109C4[9])();

//----- (00477D60) --------------------------------------------------------
_DWORD * Compat_FileStreamRelease(_DWORD *result, char a2)
{
  int v3; // ebx
  int v4; // ecx
  int v5; // ecx
  int v7; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatFileStream_DtorArrayDescriptor);
    j_j__nfree_();
    return (_DWORD *)v4;
  }
  v3 = result[1];
  *result = g_CompatFileStream_VTable;
  if ( v3 )
  {
    fclose_(v3);
    if ( (a2 & 2) == 0 )
      return (_DWORD *)v5;
    goto LABEL_8;
  }
  if ( (a2 & 2) != 0 )
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
int Compat_FileStreamRead(int a1, void *a2, int a3)
{
  return fread_(a2, 1, *(_DWORD *)(a1 + 4), a3);
}

//----- (00477DE0) --------------------------------------------------------
int  Compat_FileStreamReadChar(int a1, unsigned int a2)
{
  int stream_ptr;
  unsigned __int8 next_byte;

  (void)a2;
  stream_ptr = *(_DWORD *)(a1 + 4);
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
signed int  Compat_FileStreamUngetChar(int a1, signed int a2)
{
  return CRT_FlushBufferAndPutChar(a2, a1);
}

//----- (00477E40) --------------------------------------------------------
int  Compat_FileStreamWrite(int a1, const void *a2, int a3)
{
  return fwrite_(a2, 1, *(_DWORD *)(a1 + 4), a3);
}

//----- (00477E60) --------------------------------------------------------
signed int  Compat_FileStreamSeekFromStart(int a1, int a2, int a3)
{
  return IO_SeekStreamGuarded(*(_DWORD *)(a1 + 4), a2, 0, a3);
}

//----- (00477E70) --------------------------------------------------------
signed int  Compat_FileStreamSeekFromEnd(int a1, int a2, int a3)
{
  return IO_SeekStreamGuarded(*(_DWORD *)(a1 + 4), a2, 2u, a3);
}

//----- (00477E80) --------------------------------------------------------
int __fastcall Compat_FileStreamTell(int a1, int a2)
{
  return Compat_StreamTell(*(_DWORD *)(a1 + 4));
}

//----- (00477E90) --------------------------------------------------------
signed int  Compat_FileStreamIsReady(int a1)
{
  int v1; // edx

  v1 = *(_DWORD *)(a1 + 4);
  if ( !v1 )
    return -2;
  if ( (*(_BYTE *)(v1 + 12) & 0x10) != 0 )
    return -1;
  return 1;
}

//----- (00477EC0) --------------------------------------------------------
int  Compat_FileFinderOpen(_DWORD *a1, int a2)
{
  int v2; // ecx
  signed int v3; // eax
  int v4; // ecx
  int v5; // ecx
  const char *v7; // [esp+0h] [ebp-18h] BYREF
  int (**v8)(); // [esp+4h] [ebp-14h]
  int v9; // [esp+10h] [ebp-8h]

  v9 = a2;
  a1[71] = -1;
  *a1 = g_CompatFileFinder_VTable;
  v7 = 0;
  v8 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v7);
  v8 = &g_PathEntry_Vtable;
  Compat_StringHolderAppendText(&v7, a__31);
  v3 = CRT_FindFirstFile(v7, (_DWORD *)(v2 + 4), v2);
  *(_DWORD *)(v4 + 284) = v3;
  *(_DWORD *)(v4 + 288) = v3;
  Compat_StringHolderScalarDeletingDtor((int)&v7, 1);
  return v5;
}
// 477F06: variable 'v2' is possibly undefined
// 477F0E: variable 'v4' is possibly undefined
// 477F26: variable 'v5' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();
// 5109F4: using guessed type int (*off_5109F4[6])();

//----- (00477F30) --------------------------------------------------------
_DWORD * Compat_FileFinderRelease(_DWORD *result, char a2)
{
  int v3; // ebx
  int v4; // ecx
  int v5; // ecx
  char v6; // dl
  int v7; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatFileFinder_DtorArrayDescriptor);
    j_j__nfree_();
    return (_DWORD *)v4;
  }
  v3 = result[71];
  *result = g_CompatFileFinder_VTable;
  if ( v3 == -1 )
  {
    findclose_(result);
    if ( (v6 & 2) == 0 )
      return (_DWORD *)v5;
    goto LABEL_8;
  }
  if ( (a2 & 2) != 0 )
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
int  Compat_FileFinderAdvance(int a1)
{
  int result; // eax
  int v2; // ecx

  result = findnext_(a1, a1 + 4);
  *(_DWORD *)(v2 + 288) = result;
  return result;
}
// 477FB2: variable 'v2' is possibly undefined
// 489F5D: using guessed type int __fastcall findnext_(_DWORD, _DWORD);

//----- (00477FC0) --------------------------------------------------------
int  Compat_FileFinderGetName(int a1)
{
  return a1 + 24;
}

//----- (00477FD0) --------------------------------------------------------
int  Compat_FileFinderGetAttributes(int a1)
{
  return *(_DWORD *)(a1 + 4);
}

//----- (00477FE0) --------------------------------------------------------
int  Compat_FileFinderGetSize(int a1)
{
  return *(_DWORD *)(a1 + 20);
}

//----- (00477FF0) --------------------------------------------------------
int  Compat_FileFinderCreate(int a1, char a2, DWORD a3)
{
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // ecx

  v4 = (_DWORD *)Mem_Alloc(292, a1, a2, a3);
  if ( v4 )
    v4 = (_DWORD *)Compat_FileFinderOpen(v4, v5);
  if ( (*(int (__cdecl **)(int))(*v4 + 12))(a1) )
    return v6;
  (*(void (__fastcall **)(int, int))(*(_DWORD *)v6 + 20))(v6, 2);
  return 0;
}
// 478010: variable 'v5' is possibly undefined
// 47800C: variable 'v6' is possibly undefined

//----- (00478030) --------------------------------------------------------
const char ** FileSystem_DiskMountCtor(const char **a1, int a2)
{
  const char *path_text;
  unsigned int path_len;

  *(_DWORD *)(a1 + 4) = 0;
  *(_DWORD *)(a1 + 8) = (int)&g_PathEntry_Vtable;
  *(_DWORD *)a1 = (int)g_FileSystemDiskMount_VTable;
  if ( !a2 )
    return a1;
  Compat_StringHolderDestructor((const char **)(uintptr_t)((unsigned int)(uintptr_t)a1 + 4));
  path_text = Compat_StringHolderGetText((_DWORD *)(uintptr_t)((unsigned int)(uintptr_t)a1 + 4));
  path_len = path_text ? (unsigned int)strlen(path_text) : 0;
  if ( !path_len || path_text[path_len - 1] == 92 )
    return a1;
  Compat_StringHolderAppendText((const char **)(uintptr_t)((unsigned int)(uintptr_t)a1 + 4), asc_5024EA);
  return a1;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510A14: using guessed type int (*off_510A14[4])();

//----- (004780A0) --------------------------------------------------------
int  FileSystem_DiskMountScalarDeletingDtor(_DWORD *a1, char a2)
{
  int v3; // eax
  int v5; // ecx
  int v6; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileSystemDiskMount_DtorArrayDescriptor);
    j_j__nfree_();
    return v5;
  }
  else
  {
    *a1 = g_FileSystemDiskMount_VTable;
    v3 = Compat_StringHolderScalarDeletingDtor((int)(a1 + 1), 0);
    if ( (a2 & 2) != 0 )
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
int  FileSystem_DiskMountOpenFileQuery(int a1, char a2, DWORD a3)
{
  _DWORD *result; // ecx
  _DWORD joined_path[2]; // [esp+0h] [ebp-8h] BYREF

  joined_path[0] = 0;
  joined_path[1] = &g_CompatStringHolder_Vtable;
  result = (_DWORD *)Mem_Alloc(8, a1, a2, a3);
  if ( result )
  {
    Compat_StringHolderConstructJoined(joined_path, (_DWORD *)(uintptr_t)(unsigned int)(a1 + 4), 0);
    result = Compat_FileStreamOpen(result, (const CHAR *)(uintptr_t)(unsigned int)joined_path[0], 0, a2, a3);
  }
  Compat_StringHolderDestroyStack(joined_path, 1);
  return (int)result;
}

//----- (00478140) --------------------------------------------------------
int __fastcall FileSystem_DiskMountDeleteFile(int a1, const char *a2)
{
  int v3; // ecx
  char v4; // dl
  int v5; // ecx
  _DWORD v7[4]; // [esp-Ch] [ebp-10h] BYREF

  v7[2] = a1;
  Compat_StringHolderConstructJoined(v7, a1, a2);
  IO_RemoveFileByPath(v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)v7, v4);
  return v5;
}
// 478158: variable 'v3' is possibly undefined
// 478161: variable 'v4' is possibly undefined
// 478166: variable 'v5' is possibly undefined
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);

//----- (00478170) --------------------------------------------------------
int __fastcall FileSystem_DiskMountCreateDirectory(int a1, const char *a2)
{
  const CHAR **v3; // eax
  char v4; // dl
  int v5; // ecx
  _DWORD v7[3]; // [esp-Ch] [ebp-Ch] BYREF

  v7[2] = a1;
  v3 = (const CHAR **)Compat_StringHolderConstructJoined(v7, a1, a2);
  CRT_MakeDirectory(*v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)v7, v4);
  return v5;
}
// 478190: variable 'v4' is possibly undefined
// 478195: variable 'v5' is possibly undefined

//----- (004781A0) --------------------------------------------------------
int __fastcall FileSystem_DiskMountRemoveDirectory(int a1, const char *a2)
{
  const CHAR **v3; // eax
  char v4; // dl
  int v5; // ecx
  _DWORD v7[4]; // [esp-Ch] [ebp-10h] BYREF

  v7[2] = a1;
  v3 = (const CHAR **)Compat_StringHolderConstructJoined(v7, a1, a2);
  CRT_RemoveDirectory(*v3, 1);
  Compat_StringHolderScalarDeletingDtor((int)v7, v4);
  return v5;
}
// 4781C1: variable 'v4' is possibly undefined
// 4781C6: variable 'v5' is possibly undefined

//----- (004781E0) --------------------------------------------------------
char *__thiscall FileSystem_DiskMountGetCurrentDirectory(void *this)
{
  char *v2; // esi
  char *v3; // edi
  char v4; // al
  char v5; // al

  (void)this;
  getcwd_(g_FileSystem_CurrentDirectoryBuffer, 100);
  if ( g_FileSystem_CwdBufferSentinel[strlen(g_FileSystem_CurrentDirectoryBuffer)] == 92 )
    return g_FileSystem_CurrentDirectoryBuffer;
  v2 = asc_5024EC;
  v3 = &g_FileSystem_CurrentDirectoryBuffer[strlen(g_FileSystem_CurrentDirectoryBuffer)];
  do
  {
    v4 = *v2;
    *v3 = *v2;
    if ( !v4 )
      break;
    v5 = v2[1];
    v2 += 2;
    v3[1] = v5;
    v3 += 2;
  }
  while ( v5 );
  return g_FileSystem_CurrentDirectoryBuffer;
}
// 489FF2: using guessed type int __fastcall getcwd_(_DWORD, _DWORD);

//----- (00478250) --------------------------------------------------------
int __thiscall FileSystem_DiskMountDirectoryExists(void *this)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v5; // [esp-118h] [ebp-130h] BYREF
  const char *v6; // [esp+0h] [ebp-18h] BYREF
  int (**v7)(); // [esp+4h] [ebp-14h]
  void *v8; // [esp+10h] [ebp-8h]

  v8 = this;
  v6 = 0;
  v7 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v6);
  v7 = &g_PathEntry_Vtable;
  if ( v6 && *v6 && v6[strlen(v6) - 1] != 92 )
    Compat_StringHolderAppendText(&v6, asc_5024EE);
  Compat_StringHolderAppendText(&v6, a__36);
  if ( CRT_FindFirstFile(v6, &v5, v1) == -1 )
  {
    Compat_StringHolderScalarDeletingDtor((int)&v6, 1);
    return 0;
  }
  else
  {
    findclose_(v2);
    Compat_StringHolderScalarDeletingDtor((int)&v6, 1);
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
char  FileSystem_DiskMountResolveRegisteredRootPath(int a1, int a2)
{
  const char *resolved_path; // eax

  resolved_path = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 4);
  if ( !resolved_path || !*resolved_path )
    Compat_StringHolderCopyText((_DWORD *)(a1 + 4), (const char *)(uintptr_t)(unsigned int)Compat_FileSystemFindMountedPathById(a2, a1));
  return a2;
}

//----- (00478370) --------------------------------------------------------
const char ** FileSystem_DiskMountCreate(int a1, char a2, DWORD a3)
{
  const char **result; // eax

  result = (const char **)Mem_Alloc(12, a1, a2, a3);
  if ( result )
    return FileSystem_DiskMountCtor(result, a1);
  return result;
}

//----- (004783B0) --------------------------------------------------------
int  FileSystem_DiskMountRegisterNestedMount(int a1, int *a2, char a3, DWORD a4)
{
  _DWORD *v5; // eax

  v5 = IO_StreambufAlloc(a1, a3, a4);
  return FileSystem_AddMountEntry(
           a2,
           (const CHAR *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 4),
           0,
           (DWORD)v5);
}

//----- (004783D0) --------------------------------------------------------
int  FileSystem_DiskMountVariantScalarDeletingDtor(_DWORD *a1, char a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileSystemDiskMountVariant_DtorArrayDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = FileSystem_DiskMountScalarDeletingDtor(a1, 1);
    if ( (a2 & 2) != 0 )
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
int  FileSystem_ArchiveGenerateBlankRecord(int a1)
{
  int v1; // edx

  FileSystem_ArchiveFillBlankRecordBytes(a1);
  return v1;
}
// 478418: variable 'v1' is possibly undefined

//----- (00478420) --------------------------------------------------------
int  FileSystem_ArchiveFillBlankRecordBytes(int a1)
{
  __int64 v2; // rax
  int v3; // ecx

  HIDWORD(v2) = a1;
  v3 = a1 + 26;
  do
  {
    v2 = rand_(v3, HIDWORD(v2) + 1);
    *(_BYTE *)(HIDWORD(v2) - 1) = v2;
  }
  while ( HIDWORD(v2) != v3 );
  *(_DWORD *)(a1 + 14) = 0;
  return v2;
}
// 478431: variable 'v3' is possibly undefined
// 47619A: using guessed type __int64 __fastcall rand_(_DWORD, _DWORD);

//----- (00478450) --------------------------------------------------------
const char ** FileSystem_PathTrimToParentDir(const char **a1)
{
  const char *v2; // eax
  int v3; // edx
  unsigned int v4; // ecx

  *a1 = 0;
  a1[1] = (const char *)&g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(a1);
  a1[1] = (const char *)&g_PathEntry_Vtable;
  if ( Compat_StringHolderFindLastBackslash((_BYTE **)a1) == -1 )
  {
    Compat_StringHolderDestructor(a1);
    return a1;
  }
  else
  {
    v2 = (const char *)ExcString_GetTextPtr((int)a1);
    if ( v2 )
      v4 = strlen(v2);
    else
      v4 = 0;
    Compat_StringHolderRemoveRange(a1, v3, v4, v4 - v3);
    return a1;
  }
}
// 4784A9: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (004784E0) --------------------------------------------------------
_DWORD * FileSystem_PathExtractFileName(_DWORD *a1)
{
  int v2; // eax
  unsigned int v3; // ecx

  *a1 = 0;
  a1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(a1);
  a1[1] = &g_PathEntry_Vtable;
  v2 = Compat_StringHolderFindLastBackslash((_BYTE **)a1);
  if ( v2 != -1 )
    Compat_StringHolderRemoveRange((const char **)a1, 0, v3, v2 + 1);
  return a1;
}
// 478524: variable 'v3' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478540) --------------------------------------------------------
int * FileSystem_ArchiveRecordCacheCtor(int *a1, int a2, int a3, int a4)
{
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int *result; // eax

  a1[3] = 0;
  *a1 = a4;
  a1[5] = a2;
  v5 = *a1;
  a1[6] = a3;
  if ( v5 >= 200 )
    v6 = 200;
  else
    v6 = v5;
  a1[2] = v6;
  a1[4] = Compat_WcppCtorArrayStorage1m(
            (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(26 * a1[2]),
            a1[2],
            &g_FileSystemArchiveRecordCache_CtorArrayDescriptor);
  v7 = a1[2];
  a1[1] = v7;
  result = a1;
  a1[1] = -v7;
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00478590) --------------------------------------------------------
_DWORD * FileSystem_ArchiveRecordCacheCopyCtor(int *a1, int *a2)
{
  int v4; // eax
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  _DWORD *v9; // ecx
  int v10; // ebx
  _DWORD *result; // eax

  v4 = *a2;
  a1[3] = 0;
  *a1 = v4;
  a1[5] = a2[5];
  v5 = a2[6];
  v6 = *a1;
  a1[6] = v5;
  if ( v6 >= 200 )
    v7 = 200;
  else
    v7 = v6;
  a1[2] = v7;
  v8 = Compat_WcppCtorArrayStorage1m(
         (void *)(uintptr_t)(unsigned int)j_Mem_Alloc(26 * a1[2]),
         a1[2],
         &g_FileSystemArchiveRecordCache_CtorArrayDescriptor);
  a1[4] = v8;
  v10 = a1[2];
  a1[1] = v10;
  result = (_DWORD *)a1;
  a1[1] = -v10;
  return result;
}
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (004785F0) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheDestruct(_DWORD *a1)
{
  FileSystem_ArchiveRecordCacheFlushWindow(a1);
  j_j__nfree_(a1[4]);
  return (int)a1;
}

//----- (00478610) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheGetRecord(_DWORD *a1, int a2)
{
  int v3; // ebp

  ++dword_54DD0C;
  v3 = a1[1];
  if ( a2 >= v3 && a2 < a1[2] + v3 )
    return a1[4] + 26 * (a2 - a1[1]);
  FileSystem_ArchiveRecordCacheLoadWindow(a1, a2);
  ++dword_54DD10;
  return a1[4] + 26 * (a2 - a1[1]);
}
// 54DD0C: using guessed type int dword_54DD0C;
// 54DD10: using guessed type int dword_54DD10;

//----- (00478670) --------------------------------------------------------
int  FileSystem_ArchiveRecordCacheLoadWindow(_DWORD *a1, int a2)
{
  int v3; // edx
  int *v4; // esi
  unsigned __int8 *v5; // edi
  int result; // eax

  FileSystem_ArchiveRecordCacheFlushWindow(a1);
  v3 = a2 - a1[2] + 1;
  a1[1] = v3;
  if ( v3 < 0 )
    a1[1] = 0;
  v4 = (int *)a1[5];
  v5 = (unsigned __int8 *)a1[4];
  File_SeekIfPositionChangedMode1(v4, a1[6] + 26 * a1[1], (int)v5);
  result = Compat_StreamRead(v4[2], v5, 26 * a1[2]);
  if ( v4[5] )
  {
    Compat_QueryXorDecodeBuffer((int)v4, v5, result);
  }
  v4[12] += result;
  return result;
}

//----- (004786E0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveRecordCacheFlushWindow(_DWORD *result)
{
  unsigned int v1; // ebx
  int *v2; // esi
  const void *v3; // edi

  if ( result[3] )
  {
    v1 = 26 * result[2];
    v2 = (int *)result[5];
    v3 = (const void *)result[4];
    File_SeekIfPositionChangedMode2(v2, result[6] + 26 * result[1], (int)v3);
    Res_StreamWriteWithXorCipher(v2, v3, v1, v1);
    result[3] = 0;
  }
  return result;
}
// 47870B: variable 'v4' is possibly undefined
// 478710: variable 'v5' is possibly undefined

//----- (00478720) --------------------------------------------------------
int  FileSystem_ArchiveEntryCopyConstruct(_DWORD *a1, int a2)
{
  _DWORD *v3; // ecx
  int v4; // ecx

  *a1 = 0;
  a1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(a1);
  v3[1] = &g_PathEntry_Vtable;
  v3[2] = *(_DWORD *)(a2 + 8);
  v3[3] = 0;
  FileSystem_ArchiveRecordCacheCopyCtor(v3 + 4, (int *)(a2 + 16));
  FileSystem_ArchiveEntryReaderFlushHeader(a2);
  return v4;
}
// 47873A: variable 'v3' is possibly undefined
// 478765: variable 'v4' is possibly undefined
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478770) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderCtor(_DWORD *a1, int *a2, int a3, int a4, const void *a5)
{
  int *v9; // eax
  int v10; // esi
  int v11; // eax
  int result; // eax
  const char *v14; // edx
  unsigned __int8 *v15; // [esp+0h] [ebp-10h]

  *a1 = 0;
  a1[1] = &g_CompatStringHolder_Vtable;
  Compat_StringHolderFreeText(a1);
  v14 = Compat_StringArgGetText(a5);
  if ( v14 && *v14 )
  {
    *a1 = (int)(uintptr_t)j_Mem_Alloc((unsigned int)strlen(v14) + 1);
    Compat_CopyPrefixN((char *)(uintptr_t)*a1, v14, (unsigned int)strlen(v14) + 1);
  }
  a1[1] = &g_PathEntry_Vtable;
  a1[3] = 0;
  v9 = FileSystem_ArchiveRecordCacheCtor(a1 + 4, (int)a2, a3 + 4, (a4 - 4) / 0x1Au);
  v10 = (int)(v9 - 4);
  v15 = (unsigned __int8 *)(v9 - 2);
  File_SeekIfPositionChangedMode1(a2, a3, 0);
  v11 = Compat_StreamRead((int)a2, v15, 4);
  if ( a2[5] )
  {
    Compat_QueryXorDecodeBuffer((int)a2, v15, v11);
    result = v10;
    a2[12] += v11;
  }
  else
  {
    a2[12] += v11;
    result = v10;
  }
  return result;
}
// 50EC84: using guessed type int (*off_50EC84)();
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478830) --------------------------------------------------------
int  FileSystem_ArchiveIndexCreateEmpty(_DWORD *a1, int a2, int a3)
{
  int *v3; // edi
  int v4; // eax

  *a1 = 0;
  a1[1] = &g_PathEntry_Vtable;
  a1[2] = 0;
  a1[3] = 0;
  v3 = a1 + 4;
  v4 = File_SeekStreamEndAndRecordPos(a2, (int)(a1 + 4));
  FileSystem_ArchiveRecordCacheCtor(v3, a2, v4 + 4, a3);
  FileSystem_ArchiveWritePaddingRecords((int)v3, a3, (int)v3);
  return (int)v3;
}
// 50EC94: using guessed type int (*off_50EC94)();

//----- (00478880) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderScalarDeletingDtor(int a1)
{
  FileSystem_ArchiveEntryReaderFlushHeader(a1);
  return Compat_StringHolderScalarDeletingDtor(FileSystem_ArchiveRecordCacheDestruct((_DWORD *)(a1 + 16)) - 16, 0);
}

//----- (004788A0) --------------------------------------------------------
int  FileSystem_ArchiveEntryReaderFlushHeader(int a1)
{
  int result; // eax
  int *v3; // esi
  const void *v4; // edi

  FileSystem_ArchiveRecordCacheFlushWindow((_DWORD *)(a1 + 16));
  result = *(_DWORD *)(a1 + 12);
  if ( result )
  {
    v3 = *(int **)(a1 + 36);
    v4 = (const void *)(a1 + 8);
    File_SeekIfPositionChangedMode2(v3, *(_DWORD *)(a1 + 40) - 4, (int)v4);
    result = Res_StreamWriteWithXorCipher(v3, v4, 4, 4u);
    *(_DWORD *)(a1 + 12) = 0;
  }
  return result;
}

//----- (004788F0) --------------------------------------------------------
unsigned int  FileSystem_ArchiveNameHash(int a1, const char **a2)
{
  const char *text;
  unsigned int hash_value;
  unsigned int text_len;
  unsigned int index;

  text = Compat_StringArgGetText((const void *)a2);
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
  return hash_value % *(_DWORD *)(a1 + 16);
}

//----- (00478950) --------------------------------------------------------
int  FileSystem_ArchiveHashTableFind(int a1, const char **a2)
{
  const char *text;
  unsigned int slot_index; // ecx
  _DWORD *table; // edi
  int entry; // esi

  text = Compat_StringArgGetText((const void *)a2);
  if ( !text || !*text )
    return 0;
  slot_index = FileSystem_ArchiveNameHash(a1, a2);
  table = (_DWORD *)(a1 + 16);
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
unsigned int  FileSystem_ArchiveHashTableFindFreeSlot(int a1, const char **a2)
{
  unsigned int slot_index; // ecx
  _DWORD *table; // ebx

  slot_index = FileSystem_ArchiveNameHash(a1, a2);
  table = (_DWORD *)(a1 + 16);
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
_DWORD * FileSystem_ArchiveOpenEntryReader(int a1, const void *a2)
{
  const char *path_text;
  const char *leaf_text;
  int entry; // ecx
  _DWORD *result; // eax
  _DWORD v8[2]; // [esp+0h] [ebp-8h] BYREF
  _DWORD savedregs[4]; // [esp+8h] [ebp+0h] BYREF

  v8[0] = 0;
  v8[1] = (int)&g_PathEntry_Vtable;
  path_text = Compat_StringArgGetText(a2);
  if ( path_text && *path_text )
  {
    leaf_text = Compat_StrrchrChar(path_text, '\\');
    if ( leaf_text )
      ++leaf_text;
    else
      leaf_text = path_text;
    Compat_StringHolderCopyText(v8, leaf_text);
  }
  entry = FileSystem_ArchiveHashTableFind(a1, (const char **)v8);
  Compat_StringHolderDestroyStack(v8, 1);
  if ( !entry || (*(_DWORD *)(entry + 14) & 2) == 0 )
    return 0;
  result = (_DWORD *)Mem_Alloc(44, entry, a2, (DWORD)savedregs);
  if ( result )
    return (_DWORD *)FileSystem_ArchiveEntryReaderCtor(
                       result,
                       (int *)(uintptr_t)(unsigned int)*(_DWORD *)(a1 + 36),
                       *(_DWORD *)(entry + 18),
                       *(_DWORD *)(entry + 22),
                       a2);
  return result;
}

//----- (00478A60) --------------------------------------------------------
signed int  FileSystem_ArchiveHashTableInsert(_DWORD *a1, const char **a2, int a3, int a4)
{
  unsigned int slot_index; // ebp
  int entry; // eax
  int v9; // edx

  if ( a1[2] == a1[4] - 1 || !*a2 || !**a2 )
    return -1;
  slot_index = FileSystem_ArchiveHashTableFindFreeSlot((int)a1, a2);
  entry = FileSystem_ArchiveRecordCacheGetRecord(a1 + 4, slot_index);
  *(_BYTE *)(entry + 13) = 0;
  Compat_CopyPrefixN((char *)(uintptr_t)entry, *a2, 13);
  *(_DWORD *)(entry + 14) = a4;
  *(_DWORD *)(entry + 18) = File_SeekStreamEndAndRecordPos(a1[9], (int)a2);
  *(_DWORD *)(entry + 22) = a3;
  a1[7] = 1;
  v9 = a1[2];
  a1[3] = 1;
  a1[2] = v9 + 1;
  return slot_index;
}

//----- (00478B10) --------------------------------------------------------
int  FileSystem_ArchiveWritePaddingRecords(int a1, int a2, int a3)
{
  int result; // eax
  int v6; // ecx
  const void *v7; // edx
  int v8; // ecx
  _BYTE v9[28]; // [esp-1Ch] [ebp-30h] BYREF
  _DWORD v10[5]; // [esp+0h] [ebp-14h] BYREF

  v10[3] = a3;
  v10[0] = 0;
  Res_StreamWriteWithXorCipher(*(int **)(a1 + 36), v10, a3, 4u);
  result = FileSystem_ArchiveGenerateBlankRecord((int)v9);
  if ( a2 > 0 )
  {
    do
    {
      FileSystem_ArchiveFillBlankRecordBytes((int)v9);
      result = Res_StreamWriteWithXorCipher(*(int **)(a1 + 36), v7, v6 + 1, 0x1Au);
    }
    while ( v8 < a2 );
  }
  return result;
}
// 478B51: variable 'v7' is possibly undefined
// 478B50: variable 'v6' is possibly undefined
// 478B58: variable 'v8' is possibly undefined

//----- (00478B70) --------------------------------------------------------
signed int  FileSystem_ArchiveInsertFileEntry(_DWORD *a1, const char **a2, int a3)
{
  signed int result; // eax
  int v5; // ecx

  result = FileSystem_ArchiveHashTableInsert(a1, a2, 26 * a3, 2);
  if ( result != -1 )
  {
    FileSystem_ArchiveWritePaddingRecords((int)a1, a3, v5);
    return 0;
  }
  return result;
}
// 478B91: variable 'v5' is possibly undefined

//----- (00478BA0) --------------------------------------------------------
int  FileSystem_ArchiveInsertDirectoryEntry(_DWORD *a1, const char **a2)
{
  signed int v3; // eax

  v3 = FileSystem_ArchiveHashTableInsert(a1, a2, 0, 1);
  if ( v3 == -1 )
    return 0;
  else
    return FileSystem_ArchiveRecordCacheGetRecord(a1 + 4, v3);
}

//----- (00478BD0) --------------------------------------------------------
_DWORD * FileSystem_ArchiveEntryStreamCtor(_DWORD *result, int a2, int a3)
{
  int v3; // ecx
  int v4; // edx

  v3 = *(_DWORD *)(a2 + 18);
  result[2] = 0;
  result[1] = v3;
  v4 = *(_DWORD *)(a2 + 22);
  *result = g_FileSystemArchiveEntryStream_VTable;
  result[3] = v4;
  result[4] = a3;
  return result;
}
// 510BD4: using guessed type int (*off_510BD4[10])();

//----- (00478BF0) --------------------------------------------------------
signed int  FileSystem_ArchiveStreamHasRemainingData(int a1)
{
  if ( *(_DWORD *)(a1 + 8) == *(_DWORD *)(a1 + 12) )
    return -1;
  else
    return 1;
}

//----- (00478C20) --------------------------------------------------------
int  FileSystem_ArchiveStreamReadBytes(_DWORD *a1, unsigned __int8 *a2, int a3)
{
  int *v4; // edi
  int v5; // ebx
  int remaining_bytes;
  int result; // eax

  if ( a1[3] == a1[2] )
    return 0;
  remaining_bytes = a1[3] - a1[2];
  if ( a3 > remaining_bytes )
    a3 = remaining_bytes;
  v4 = (int *)a1[4];
  File_SeekIfPositionChangedMode1(v4, a1[2] + a1[1], (int)v4);
  v5 = Compat_StreamRead(v4[2], a2, a3);
  if ( v4[5] )
    Compat_QueryXorDecodeBuffer((int)v4, a2, v5);
  v4[12] += v5;
  result = v5;
  a1[2] += v5;
  return result;
}

//----- (00478CA0) --------------------------------------------------------
int FileSystem_ArchiveStreamNoOpFlush()
{
  return 0;
}

//----- (00478CB0) --------------------------------------------------------
int  FileSystem_ArchiveStreamReadByte(int a1, int a2)
{
  int result; // eax
  int *v3; // ecx
  int v6; // edi
  unsigned __int8 next_byte;

  if ( *(_DWORD *)(a1 + 12) == *(_DWORD *)(a1 + 8) )
    return -1;
  v3 = *(int **)(a1 + 16);
  File_SeekIfPositionChangedMode1(v3, *(_DWORD *)(a1 + 8) + *(_DWORD *)(a1 + 4), a2);
  ++*(_DWORD *)(a1 + 8);
  if ( Compat_StreamRead(v3[2], &next_byte, 1) == 1 )
    result = next_byte;
  else
    result = -1;
  v6 = v3[5];
  if ( v6 )
    result ^= v6 + v3[12];
  ++v3[12];
  return result;
}

//----- (00478D10) --------------------------------------------------------
signed int  Res_StreamPutBackDecodedByte(int a1, int a2)
{
  int v3; // eax
  signed int v4; // eax
  signed int result; // eax
  int v6; // ecx

  v3 = *(_DWORD *)(a1 + 16);
  if ( a2 != -1 )
    --*(_DWORD *)(v3 + 48);
  if ( *(_DWORD *)(v3 + 20) )
    v4 = a2 ^ (*(_DWORD *)(v3 + 48) + *(_DWORD *)(v3 + 20));
  else
    v4 = a2;
  result = CRT_FlushBufferAndPutChar(v4, a2);
  if ( v6 != -1 )
    --*(_DWORD *)(a1 + 8);
  return result;
}
// 478D3E: variable 'v6' is possibly undefined

//----- (00478D70) --------------------------------------------------------
int  Res_StreamWriteBytes(int a1, const void *a2, unsigned int a3)
{
  int result; // eax
  int v4; // ecx
  int v5; // ebx

  result = Res_StreamWriteWithXorCipher(*(int **)(a1 + 16), a2, a1, a3);
  v5 = result + *(_DWORD *)(v4 + 12);
  *(_DWORD *)(v4 + 8) += result;
  *(_DWORD *)(v4 + 12) = v5;
  return result;
}
// 478D7E: variable 'v4' is possibly undefined

//----- (00478D90) --------------------------------------------------------
int  Res_StreamSeekClamped(int result, int a2)
{
  int v2; // ecx

  if ( a2 < 0 )
  {
    *(_DWORD *)(result + 8) = 0;
  }
  else
  {
    v2 = *(_DWORD *)(result + 12);
    if ( a2 <= v2 )
      *(_DWORD *)(result + 8) = a2;
    else
      *(_DWORD *)(result + 8) = v2;
  }
  return result;
}

//----- (00478DB0) --------------------------------------------------------
int  File_DirNodeScalarDtor(_DWORD *a1, char a2, DWORD a3)
{
  int v4; // ecx
  int v6; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileDirNode_DtorArrayDescriptor);
    j_j__nfree_();
    return v6;
  }
  else
  {
    *a1 = g_FileDirNode_VTable;
    File_ApplyResolvedEntryFlag(a1[4], a1[3], a3);
    if ( (a2 & 2) != 0 )
      j__nfree_();
    return v4;
  }
}
// 478DD1: variable 'v4' is possibly undefined
// 478DE5: variable 'v6' is possibly undefined
// 47312B: using guessed type int __fastcall _wcpp_4_dtor_array_store__(_DWORD, _DWORD);
// 510BA4: using guessed type int (*off_510BA4[4])();

//----- (00478E00) --------------------------------------------------------
_DWORD * Res_BuildTaggedRecordHeader(_DWORD *result, int a2, int a3, int a4)
{
  result[1] = a2;
  result[3] = a3;
  result[2] = a4;
  qmemcpy(result, aLlrs, sizeof(_DWORD));
  return result;
}

//----- (00478E30) --------------------------------------------------------
int  File_SourceEntryConstructor(_DWORD *a1, int a2, int a3, DWORD a4)
{
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  _DWORD *v9; // eax
  _DWORD *v10; // ecx
  int v11; // ecx
  int v12; // [esp+0h] [ebp-14h] BYREF
  int (**v13)(); // [esp+4h] [ebp-10h]
  int v14; // [esp+10h] [ebp-4h]

  v14 = a3;
  a1[2] = 0;
  a1[3] = 0;
  a1[4] = -1;
  *a1 = g_FileCacheNode_VTable;
  a1[1] = a2;
  v12 = 0;
  v13 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v12);
  v13 = &g_PathEntry_Vtable;
  v5 = File_ResolveCachedPathEntry(*(_DWORD **)(v4 + 4), &v12, (const char *)v4, a4);
  *(_DWORD *)(v6 + 8) = v5;
  Compat_StringHolderScalarDeletingDtor((int)&v12, 1);
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
_DWORD * File_CacheNodeScalarDtor(_DWORD *a1, char a2)
{
  int v4; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_FileCacheNode_DtorArrayDescriptor);
    j_j__nfree_();
    return (_DWORD *)v6;
  }
  *a1 = g_FileCacheNode_VTable;
  v4 = a1[2];
  if ( v4 )
  {
    FileSystem_ArchiveEntryReaderScalarDeletingDtor(v4);
    j__nfree_();
    if ( (a2 & 2) == 0 )
      return (_DWORD *)v7;
  }
  else if ( (a2 & 2) == 0 )
  {
    return a1;
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
  int v1; // edx

  v1 = *(_DWORD *)(result + 8);
  if ( !v1 || *(_DWORD *)(v1 + 16) <= *(_DWORD *)(result + 16) )
    return 0;
  return result;
}

//----- (00478F50) --------------------------------------------------------
_DWORD * File_CacheNodeRebalance(_DWORD *a1)
{
  _DWORD *v1; // ecx
  int v2; // eax
  int v3; // edx
  _DWORD *result; // eax
  int v5; // eax

  v1 = a1;
  ++a1[4];
  while ( 1 )
  {
    v2 = v1[2];
    v3 = *(_DWORD *)(v2 + 16);
    result = (_DWORD *)(v2 + 16);
    if ( v3 <= v1[4] )
      break;
    v5 = FileSystem_ArchiveRecordCacheGetRecord(result, v1[4]);
    v1[3] = v5;
    result = *(_DWORD **)(v5 + 14);
    if ( result )
      break;
    ++v1[4];
  }
  return result;
}
// 478F58: variable 'v1' is possibly undefined

//----- (00478F90) --------------------------------------------------------
int  File_CacheNodeGetTag(int a1)
{
  return *(_DWORD *)(a1 + 12);
}

//----- (00478FA0) --------------------------------------------------------
signed int  File_CacheNodeGetEntrySize(int a1)
{
  if ( (*(_DWORD *)(*(_DWORD *)(a1 + 12) + 14) & 2) != 0 )
    return 16;
  else
    return FileSystem_ArchiveStreamNoOpFlush();
}

//----- (00478FC0) --------------------------------------------------------
int  File_CacheNodeGetChildTag(int a1)
{
  return *(_DWORD *)(*(_DWORD *)(a1 + 12) + 22);
}

//----- (00478FD0) --------------------------------------------------------
int * File_SourceConstructFromStream(
        int *a1,
        const CHAR *a2,
        unsigned __int8 *a3,
        int a4,
        int a5,
        int a6)
{
  a1[3] = 0;
  a1[4] = (int)&g_PathEntry_Vtable;
  a1[8] = 0;
  a1[5] = a4;
  a1[9] = 0;
  a1[7] = a6;
  *a1 = (int)g_FileSource_VTable;
  File_SourceReadAndDecodeHeader(a1, a2, (int)a3, a3, a5);
  return a1;
}
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (00479020) --------------------------------------------------------
int * File_SourceBuildAndWriteHeader(
        int *a1,
        const CHAR *a2,
        int a3,
        int a4,
        DWORD a5,
        int a6)
{
  const CHAR *v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  _DWORD *v11; // eax
  _DWORD v13[6]; // [esp+0h] [ebp-18h] BYREF

  a1[2] = 0;
  a1[3] = 0;
  a1[4] = (int)&g_PathEntry_Vtable;
  a1[8] = 0;
  a1[9] = 0;
  a1[6] = a4;
  a1[7] = a6;
  a1[5] = a3;
  *a1 = (int)g_FileSource_VTable;
  CRT_DeleteFile(a2, (int)a2);
  a1[2] = Res_OpenBufferedStreamForWrite(v7, 0, (unsigned __int8 *)aWB, a5);
  Res_BuildTaggedRecordHeader(v13, 1, v8, a4);
  a1[13] = 0;
  File_SeekIfPositionChangedMode2(a1, 0, a4);
  Res_StreamWriteWithXorCipher(a1, v13, v9, 0x10u);
  v11 = (_DWORD *)Mem_Alloc(44, v10, 16, a5);
  if ( v11 )
    a1[1] = FileSystem_ArchiveIndexCreateEmpty(v11, (int)a1, a4);
  else
    a1[1] = 0;
  return a1;
}
// 479074: variable 'v7' is possibly undefined
// 479085: variable 'v8' is possibly undefined
// 4790A3: variable 'v9' is possibly undefined
// 4790AD: variable 'v10' is possibly undefined
// 50EC94: using guessed type int (*off_50EC94)();
// 510B34: using guessed type int (*off_510B34[4])();

//----- (004790E0) --------------------------------------------------------
int  File_SourceScalarDtor(_DWORD *a1, char a2)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  int v7; // ecx
  int v8; // ecx

  if ( (a2 & 4) != 0 )
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
    if ( (a2 & 2) != 0 )
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
int  Res_OpenBufferedStreamForRead(const CHAR *a1, int a2, unsigned __int8 *a3, DWORD a4)
{
  int stream_ptr;

  stream_ptr = IO_FOpen(a1, a3, a2, a4);
  Compat_StreamSetBuffer(stream_ptr, 0x1800);
  return stream_ptr;
}

//----- (00479170) --------------------------------------------------------
int  Res_OpenBufferedStreamForWrite(const CHAR *a1, int a2, unsigned __int8 *a3, DWORD a4)
{
  int stream_ptr;

  stream_ptr = IO_FOpen(a1, a3, a2, a4);
  Compat_StreamSetBuffer(stream_ptr, 0x1800);
  return stream_ptr;
}

//----- (004791A0) --------------------------------------------------------
int  File_SourceReadAndDecodeHeader(
        int *a1,
        const CHAR *a2,
        int a3,
        unsigned __int8 *a4,
        int a5)
{
  int stream_ptr; // eax
  unsigned __int8 *v9; // esi
  int i; // ecx
  int v11; // ebx
  unsigned __int8 v12; // al
  int v13; // ecx
  int v18; // eax
  _DWORD *v19; // esi
  _DWORD v21[4]; // [esp+0h] [ebp-28h] BYREF
  _DWORD source_name_holder[2]; // [esp+10h] [ebp-18h] BYREF
  int v24; // [esp+18h] [ebp-10h]
  int *v25; // [esp+1Ch] [ebp-Ch]
  int *v26; // [esp+20h] [ebp-8h]
  int *v27; // [esp+24h] [ebp-4h]
  _DWORD savedregs[4]; // [esp+28h] [ebp+0h] BYREF

  v26 = a1;
  stream_ptr = Res_OpenBufferedStreamForRead(a2, a3, a4, (DWORD)savedregs);
  v26[13] = 0;
  v25 = v26;
  v26[2] = stream_ptr;
  v24 = Compat_StreamRead(stream_ptr, v21, 16);
  if ( v26[5] )
  {
    v9 = (unsigned __int8 *)v21;
    v27 = v26;
    a5 = v24;
    for ( i = v26[12]; a5; *(v9 - 1) = v12 )
    {
      --a5;
      v11 = *v9++;
      v12 = Res_XorDecodeByte((int)v27, i, v11);
      i = v13 + 1;
    }
  }
  v25[12] += v24;
  Compat_StreamSeek(v26[2], v21[3], 1);
  v26[12] = Compat_StreamTell(v26[2]);
  v18 = Mem_Alloc(44, 0, 1, (DWORD)savedregs);
  v19 = (_DWORD *)v18;
  source_name_holder[0] = 0;
  source_name_holder[1] = (int)&g_PathEntry_Vtable;
  if ( v18 )
  {
    v18 = FileSystem_ArchiveEntryReaderCtor(v19, v26, v26[12], 26 * v21[2] + 4, (const void *)source_name_holder);
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
int * File_CacheNodeFreeTree(int *a1)
{
  int *v1; // ecx

  v1 = a1;
  if ( *a1 )
  {
    FileSystem_ArchiveEntryReaderScalarDeletingDtor(*a1);
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
int  File_CacheInsertWithEviction(int *a1, int a2, char a3, DWORD a4)
{
  _DWORD *cache_node; // eax

  (void)a3;
  (void)a4;
  if ( !a2 )
    return 0;
  while ( a1[8] >= a1[7] && a1[9] )
    File_CacheTreeUnlinkLeftmost(a1);
  cache_node = (_DWORD *)Mem_Alloc(8, (int)a1, 0, a4);
  if ( cache_node )
  {
    cache_node[0] = a2;
    cache_node[1] = a1[9];
  }
  a1[9] = (int)cache_node;
  ++a1[8];
  if ( !cache_node )
    return 0;
  return cache_node[0];
}

//----- (00479420) --------------------------------------------------------
int  File_ResolveCachedPathEntry(_DWORD *a1, _DWORD *a2, const char *a3, DWORD a4)
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
  path_text = Compat_StringHolderGetText(a2);
  if ( !path_text || !*path_text )
    return a1[1];
  a1[11] = 0;
  a1[10] = a1[9];
  cache_node = (_DWORD *)(uintptr_t)(unsigned int)a1[10];
  while ( cache_node )
  {
    entry = cache_node[0];
    entry_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)entry;
    if ( entry_name && !strcmp_(path_text, entry_name) )
      return File_CacheTreeAdvanceSuccessor(a1);
    a1[11] = (int)cache_node;
    a1[10] = cache_node[1];
    cache_node = (_DWORD *)(uintptr_t)(unsigned int)a1[10];
  }
  ++dword_54DD18;
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
  parent_entry = File_ResolveCachedPathEntry(a1, parent_holder, 0, a4);
  Compat_StringHolderDestroyStack(parent_holder, 1);
  if ( !parent_entry )
    return 0;
  resolved_entry = FileSystem_ArchiveOpenEntryReader(parent_entry, a2);
  if ( !resolved_entry )
    return 0;
  return File_CacheInsertWithEviction((int *)a1, (int)resolved_entry, 0, a4);
}
// 54DD18: using guessed type int dword_54DD18;

//----- (004794F0) --------------------------------------------------------
int  File_ResolvePathByParentAndLeaf(_DWORD *a1, const char *a2, DWORD a3)
{
  _DWORD parent_path_holder[2]; // [esp+0h] [ebp-118h] BYREF
  _DWORD leaf_name_holder[2]; // [esp+8h] [ebp-110h] BYREF
  int parent_entry; // ebx
  int result; // ecx

  ++dword_54DD14;
  if ( !a2 || !*a2 )
    return 0;
  Compat_StringHolderBuildParentPath(parent_path_holder, a2);
  parent_entry = File_ResolveCachedPathEntry(a1, parent_path_holder, 0, a3);
  Compat_StringHolderDestroyStack(parent_path_holder, 1);
  Compat_StringHolderBuildLeafName(leaf_name_holder, a2);
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
char  File_ApplyResolvedEntryFlag(int a1, int a2, DWORD a3)
{
  _DWORD *v4; // ecx

  *(_DWORD *)(File_ResolveAbsolutePathEntry((const char *)(a1 + 12), a3) + 22) = a2;
  return Compat_StringHolderDestructor(v4);
}
// 4795E8: variable 'v4' is possibly undefined

//----- (004795F0) --------------------------------------------------------
_DWORD * File_OpenNodeByFlags(char a1)
{
  char *v1; // ecx
  int v2; // edi
  int v3; // ecx
  _DWORD *result; // eax
  int v5; // ecx
  int v6; // ebx
  const char **v7; // eax
  char *v8; // ecx
  _DWORD *v9; // ebx
  int v10; // ecx
  int v11; // edi
  _DWORD *v12; // ebx
  int v13; // ecx
  _DWORD *v14; // eax
  int v15; // ecx
  _DWORD *v16; // ebx
  int v17; // [esp+0h] [ebp-40h] BYREF
  int (**v18)(); // [esp+4h] [ebp-3Ch]
  int v19; // [esp+8h] [ebp-38h] BYREF
  int (**v20)(); // [esp+Ch] [ebp-34h]
  int v21; // [esp+10h] [ebp-30h] BYREF
  int (**v22)(); // [esp+14h] [ebp-2Ch]
  int v23; // [esp+18h] [ebp-28h] BYREF
  int (**v24)(); // [esp+1Ch] [ebp-24h]
  const char *v25[2]; // [esp+20h] [ebp-20h] BYREF
  const char *v26[6]; // [esp+28h] [ebp-18h] BYREF

  v17 = 0;
  v18 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v17);
  v18 = &g_PathEntry_Vtable;
  v2 = File_ResolvePathByParentAndLeaf(v1, v1, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)&v17, 1);
  if ( v2 )
  {
    if ( (a1 & 8) == 0 )
    {
      result = (_DWORD *)Mem_Alloc(20, v3, a1, (DWORD)&g_PathEntry_Vtable);
      if ( result )
      {
        result = FileSystem_ArchiveEntryStreamCtor(result, v2, v5);
        *result = g_FileArchiveEntryStream_VTable;
      }
      return result;
    }
    return 0;
  }
  if ( (a1 & 8) == 0 )
    return 0;
  v6 = v3 + 12;
  if ( ExcString_GetTextPtr(v3 + 12) && *(_BYTE *)ExcString_GetTextPtr(v6) )
    return 0;
  v21 = 0;
  v22 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v21);
  v22 = &g_PathEntry_Vtable;
  v7 = FileSystem_PathTrimToParentDir(v25);
  v9 = (_DWORD *)File_ResolveCachedPathEntry(v8, v7, v8, (DWORD)&g_PathEntry_Vtable);
  Compat_StringHolderScalarDeletingDtor((int)v25, 1);
  Compat_StringHolderScalarDeletingDtor((int)&v21, 1);
  v19 = 0;
  v20 = &g_CompatStringHolder_Vtable;
  Compat_StringHolderDestructor(&v19);
  v20 = &g_PathEntry_Vtable;
  FileSystem_PathExtractFileName(v26);
  Compat_StringHolderScalarDeletingDtor((int)&v19, 1);
  if ( v9 && (v11 = FileSystem_ArchiveInsertDirectoryEntry(v9, v26)) != 0 )
  {
    v24 = &g_CompatStringHolder_Vtable;
    v23 = 0;
    v12 = (_DWORD *)(v10 + 12);
    Compat_StringHolderDestructor(&v23);
    v24 = &g_PathEntry_Vtable;
    ExcString_GetTextPtr((int)&v23);
    ExcString_ReleaseText(v12);
    Compat_StringHolderScalarDeletingDtor((int)&v23, 1);
    v14 = (_DWORD *)Mem_Alloc(20, v13, (char)v12, (DWORD)&g_CompatStringHolder_Vtable);
    if ( v14 )
    {
      v14 = FileSystem_ArchiveEntryStreamCtor(v14, v11, v15);
      *v14 = g_FileDirNode_VTable;
    }
    v16 = v14;
    Compat_StringHolderScalarDeletingDtor((int)v26, 1);
    return v16;
  }
  else
  {
    Compat_StringHolderScalarDeletingDtor((int)v26, 1);
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
signed int  File_OpenEntryForWrite(int a1, int a2)
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
  if ( !a2 )
    a2 = *(_DWORD *)(v3 + 24);
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
    v7 = FileSystem_ArchiveInsertFileEntry(v6, v10, a2);
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
int  File_SeekStreamEndAndRecordPos(int a1, int a2)
{
  int result; // eax

  IO_SeekStreamGuarded(*(_DWORD *)(a1 + 8), 0, 2u, a2);
  result = Compat_StreamTell(*(_DWORD *)(a1 + 8));
  *(_DWORD *)(a1 + 48) = result;
  return result;
}

//----- (004799B0) --------------------------------------------------------
int * File_SeekIfPositionChangedMode1(int *result, int a2, int a3)
{
  if ( a2 != result[12] || result[13] != 1 )
  {
    IO_SeekStreamGuarded(result[2], a2, 0, a3);
    result[13] = 1;
    result[12] = a2;
  }
  return result;
}

//----- (004799E0) --------------------------------------------------------
int * File_SeekIfPositionChangedMode2(int *result, int a2, int a3)
{
  if ( a2 != result[12] || result[13] != 2 )
  {
    IO_SeekStreamGuarded(result[2], a2, 0, a3);
    result[13] = 2;
    result[12] = a2;
  }
  return result;
}

//----- (00479A10) --------------------------------------------------------
int  Res_StreamWriteWithXorCipher(int *a1, const void *a2, int a3, unsigned int a4)
{
  unsigned int v5; // ecx
  unsigned __int8 *v6; // eax
  int i; // edx
  int v8; // ecx
  int result; // eax
  int v10; // [esp+0h] [ebp-18h]
  unsigned __int8 *v11; // [esp+4h] [ebp-14h]

  if ( a1[5] )
  {
    v11 = (unsigned __int8 *)j_Mem_Alloc(a3);
    qmemcpy(v11, a2, a4);
    v5 = a4;
    v6 = v11;
    for ( i = a1[12]; v5; *(v6 - 1) = v10 )
    {
      --v5;
      v10 = (i + a1[5]) ^ *v6++;
      ++i;
    }
    fwrite_(v11, 1, a1[2], a4);
    j_j__nfree_();
    a1[12] += v8;
    return v8;
  }
  else
  {
    result = fwrite_(a2, 1, a1[2], a4);
    a1[12] += result;
  }
  return result;
}
// 479AA7: variable 'v8' is possibly undefined
// 4730FB: using guessed type __int64 __thiscall j_Mem_Alloc(_DWORD);

//----- (00479AE0) --------------------------------------------------------
int * File_ConstructReadOnlySource(int *a1, const CHAR *a2, int a3, int a4, int a5)
{
  int *result; // eax

  result = File_SourceConstructFromStream(a1, a2, (unsigned __int8 *)aRb_11, a4, a5, a3);
  *result = (int)g_FileReadOnlySource_VTable;
  return result;
}
// 510C04: using guessed type int (*off_510C04[4])();

//----- (00479B00) --------------------------------------------------------
_DWORD * File_OpenMountRootEntry(int a1, char a2, DWORD a3)
{
  _DWORD *result; // eax
  int v5; // esi

  if ( (a2 & 8) != 0 )
    return 0;
  v5 = File_ResolvePathByParentAndLeaf((_DWORD *)a1, (const char *)(uintptr_t)(unsigned int)dword_54DD00, a3);
  if ( !v5 )
    return 0;
  result = (_DWORD *)Mem_Alloc(20, a1, a2, a3);
  if ( result )
  {
    result = FileSystem_ArchiveEntryStreamCtor(result, v5, a1);
    *result = g_FileArchiveEntryStream_VTable;
  }
  return result;
}
// 510B74: using guessed type int (*off_510B74[10])();

//----- (00479BE0) --------------------------------------------------------
int * File_AllocateReadOnlySource(const CHAR *a1, int a2, char a3, DWORD a4, int a5)
{
  int *result; // eax

  result = (int *)Mem_Alloc(56, a2, a3, a4);
  if ( result )
    return File_ConstructReadOnlySource(result, a1, a2, a3, a5);
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
int  Res_XorDecodeByte(int a1, int a2, int a3)
{
  return a3 ^ (a2 + *(_DWORD *)(a1 + 20));
}

//----- (00479C40) --------------------------------------------------------
unsigned __int8 * Compat_QueryXorDecodeBuffer(int a1, unsigned __int8 *a2, int a3)
{
  unsigned __int8 *result; // eax
  int i; // edx
  int v6; // [esp+0h] [ebp-10h]

  result = a2;
  for ( i = *(_DWORD *)(a1 + 48); a3; *(result - 1) = v6 )
  {
    --a3;
    v6 = (i + *(_DWORD *)(a1 + 20)) ^ *result++;
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
int  Compat_QuerySkipBytes(int a1, int a2)
{
  uintptr_t *vtable;

  if ( !a1 )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)a1;
  return ((int (*)(int, int))(uintptr_t)vtable[9])(a1, a2);
}

//----- (00479CC0) --------------------------------------------------------
int  Compat_QuerySkipBytesFromBase(int a1, int a2)
{
  uintptr_t *vtable;

  if ( !a1 )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)a1;
  return ((int (*)(int, int))(uintptr_t)vtable[9])(a1, a2 + *(_DWORD *)(a1 + 12));
}

//----- (00479CD0) --------------------------------------------------------
int  Compat_QueryGetLength(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

//----- (00479CE0) --------------------------------------------------------
int  Compat_QueryDestruct(int result, char a2)
{
  int v3; // ecx
  int v4; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(result, &g_CompatQuery_DtorArrayDescriptor);
    j_j__nfree_();
    return v3;
  }
  else if ( (a2 & 2) != 0 )
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
int  Compat_QueryCloseAndDestruct(_DWORD *a1, char a2)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx

  if ( (a2 & 4) != 0 )
  {
    _wcpp_4_dtor_array_store__(a1, &g_CompatQueryCloseAndDestruct_DtorArrayDescriptor);
    j_j__nfree_();
    return v4;
  }
  else
  {
    result = File_SourceScalarDtor(a1, 1);
    if ( (a2 & 2) != 0 )
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
signed int __fastcall Rules_PrintFactWithIndex(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  _BYTE v6[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  sprintf_(v6, "f-%-5ld ", *(_DWORD *)(a2 + 24));
  Output_Write(v3, (int)v6, v3);
  return Rules_PrintFact(v4, a2);
}
// 479E03: variable 'v3' is possibly undefined
// 479E0C: variable 'v4' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (00479E20) --------------------------------------------------------
signed int __fastcall Rules_PrintFactLabel(int a1, int a2)
{
  int v2; // ecx
  _BYTE v4[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v5; // [esp+14h] [ebp-8h]

  v5 = a1;
  sprintf_(v4, "f-%ld", *(_DWORD *)(a2 + 24));
  return Output_Write(v2, (int)v4, v2);
}
// 479E41: variable 'v2' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (00479E50) --------------------------------------------------------
signed int  Rules_PrintFactIdentifier(int a1, int a2)
{
  int v2; // ecx
  int v4; // ecx
  char *v5; // edx
  signed int result; // eax
  int v7; // ecx

  v2 = a1;
  if ( g_Print_AddressesToStringsFlag )
    Output_Write(a1, (int)asc_502524, a1);
  if ( (void **)a2 == &g_Rules_DummyFactPtr )
  {
    v5 = aDummyFact;
  }
  else
  {
    Output_Write(v2, (int)aFact_2, v2);
    Rules_PrintLongInteger(v4, *(_DWORD *)(a2 + 24));
    v5 = asc_502530;
  }
  result = Output_Write(v2, (int)v5, v2);
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
signed int  Rules_PrintFact(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // edi

  if ( (*(_BYTE *)(*(_DWORD *)(a2 + 16) + 24) & 1) == 0 )
    return Rules_PrintTemplateFactSlots(a1, a2, a2);
  Output_Write(a1, (int)asc_502544, a2);
  Output_Write(a1, *(_DWORD *)(**(_DWORD **)(v3 + 16) + 16), v3);
  v5 = *(_DWORD *)(v4 + 56);
  if ( *(_DWORD *)(v5 + 6) )
  {
    Output_Write(a1, (int)asc_502548, v4);
    Lexer_OutputFieldRange(a1, v5, *(_DWORD *)(v5 + 6) - 1, 0, 0);
  }
  return Output_Write(a1, (int)asc_50254C, v4);
}
// 479EFC: variable 'v3' is possibly undefined
// 479F0B: variable 'v4' is possibly undefined

//----- (00479F50) --------------------------------------------------------
int  Rules_NetworkAssertFact(int a1, double a2)
{
  return Rules_MatchFactAgainstPatternNetwork(a1, *(_DWORD *)(*(_DWORD *)(a1 + 16) + 32), 0, 0, a2, 0);
}

//----- (00479F70) --------------------------------------------------------
signed int  Rules_RetractFact(int a1, double a2)
{
  uintptr_t fact; // ecx

  fact = (uintptr_t)(unsigned int)a1;
  if ( dword_51A954 )
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
  ++dword_51A934;
  dword_51A938 += 6 * *(_DWORD *)(fact + 46) + 60;
  *(_DWORD *)(fact + 36) = g_Rules_GarbageFactListHead;
  g_Rules_GarbageFactListHead = (int)fact;
  *(_BYTE *)(fact + 29) |= 0x80u;
  Lexer_ErrorRecover(0);
  dword_51A954 = 1;
  Rules_RetractFactFromNetwork(*(_DWORD **)(fact + 20), a2);
  dword_51A954 = 0;
  if ( !g_Rules_CurrentlyExecutingRule )
    Rules_FlushPendingNetworkGarbage();
  Rules_FlushPendingDependencyDestructors();
  if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
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
        if ( !result[2] && (result[7] & 0x7FFF) > dword_51A96C )
          break;
        result = (_DWORD *)result[9];
        if ( !v1 )
          return result;
      }
      --dword_51A934;
      dword_51A938 -= 6 * *(_DWORD *)((char *)result + 46) + 60;
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
_DWORD * Rules_AssertFactDriver(_DWORD *a1, double a2)
{
  char *v3; // eax
  int v4; // ecx
  int v5; // ebx
  char *v6; // edx
  signed int *v7; // eax
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _DWORD *v17; // ecx

  if ( dword_51A954 )
  {
    Rules_ReturnFact(a1);
    Rules_PrintErrorID((int)aFactmngr, 2, 1);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFactsMayNotBeA, v9);
    return 0;
  }
  v3 = (char *)a1 + 54;
  v4 = *((_DWORD *)v3 - 2);
  v5 = 0;
  if ( v4 > 0 )
  {
    v6 = v3;
    do
    {
      if ( *(_WORD *)v6 == 105 )
      {
        *(_WORD *)v6 = 2;
        v7 = Str_Intern(aNil_2, v4);
        *(_DWORD *)(v6 + 2) = v7;
      }
      ++v5;
      v6 += 6;
    }
    while ( v5 < v4 );
  }
  v10 = Rules_DeduplicateFactOnAssert((int)a1);
  if ( v10 < 0 )
    return 0;
  if ( Rules_AddLogicalDependencyLink((int)a1, 0) )
  {
    Rules_InsertFactHashEntry((int)a1, v10);
    a1[9] = 0;
    a1[5] = 0;
    v11 = g_Rules_LastFactPointer;
    a1[8] = g_Rules_LastFactPointer;
    if ( v11 )
      *(_DWORD *)(v11 + 36) = a1;
    else
      g_Rules_FactListHead = (int)a1;
    v12 = g_Rules_NextFactIndex;
    g_Rules_LastFactPointer = (int)a1;
    ++g_Rules_NextFactIndex;
    a1[6] = v12;
    v13 = dword_51A998++;
    a1[3] = v13;
    Rules_InstallFact(a1);
    if ( (*(_BYTE *)(a1[4] + 24) & 2) != 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_5025D4, v14);
      Rules_PrintFactWithIndex(v15, (int)a1);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502598, v16);
    }
    g_Rules_FactListChangedFlag = 1;
    Rules_CheckFactAgainstSlotConstraints((int)a1);
    Lexer_ErrorRecover(0);
    dword_51A954 = 1;
    Rules_MatchFactAgainstPatternNetwork((int)a1, *(_DWORD *)(a1[4] + 32), 0, 0, a2, 0);
    dword_51A954 = 0;
    Rules_FlushPendingDependencyDestructors();
    if ( !g_Rules_CurrentlyExecutingRule )
      Rules_FlushPendingNetworkGarbage();
    if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
      Rules_RunPeriodicCleanup(1, 0);
    return a1;
  }
  else
  {
    Rules_ReturnFact(a1);
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
int  Lexer_EmitSlotBinding(int a1, char *a2, int a3, _DWORD *a4)
{
  int v5; // edi
  int result; // eax
  int v7; // eax
  signed int *v8; // eax
  _DWORD *v9; // ecx
  int v10; // edx
  int v11; // eax
  _DWORD v12[4]; // [esp+0h] [ebp-10h] BYREF

  v12[3] = a3;
  v5 = *(_DWORD *)(a1 + 16);
  if ( (*(_BYTE *)(v5 + 24) & 1) != 0 )
  {
    if ( !a2 )
    {
      a4[1] = *(__int16 *)(a1 + 54);
      a4[2] = *(_DWORD *)(a1 + 56);
      v7 = a4[2];
      a4[3] = 0;
      a4[4] = *(_DWORD *)(v7 + 6) - 1;
      return 1;
    }
    return 0;
  }
  v8 = Str_Intern(a2, (int)a4);
  result = (int)Lexer_FindTemplateSlot(v5, (int)v8, v12);
  if ( result )
  {
    v9[1] = *(__int16 *)(a1 + 6 * (v12[0] - 1) + 54);
    v10 = v9[1];
    v9[2] = *(_DWORD *)(a1 + 6 * (v12[0] - 1) + 56);
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
_DWORD * Rules_CreateFact(signed int a1)
{
  signed int v1; // ecx
  signed int v2; // edx
  int v3; // eax
  _DWORD *result; // eax
  __int16 v5; // dx
  __int16 v6; // bx
  int v7; // edi
  __int16 v8; // dx

  v1 = a1;
  if ( a1 <= 0 )
    v2 = 1;
  else
    v2 = a1;
  if ( (unsigned int)(6 * (v2 - 1) + 60) < 0x1F4 && *(_DWORD *)(dword_54DBA8 + 24 * (v2 - 1) + 240) )
  {
    v3 = dword_54DBA8 + 24 * (v2 - 1);
    dword_54DBAC = *(_DWORD *)(v3 + 240);
    *(_DWORD *)(v3 + 240) = *(_DWORD *)dword_54DBAC;
    result = (_DWORD *)dword_54DBAC;
  }
  else
  {
    result = Mem_NewArray(6 * (v2 - 1) + 60);
  }
  v5 = dword_51A96C;
  result[6] = 0;
  result[2] = 0;
  *result = &unk_51A8EC;
  result[1] = 0;
  result[4] = 0;
  v6 = *((_WORD *)result + 14);
  result[9] = 0;
  result[8] = 0;
  *((_WORD *)result + 14) = v6 & 0x8000;
  v7 = result[7];
  result[5] = 0;
  result[7] = v5 & 0x7FFF | v7;
  LOBYTE(v5) = *((_BYTE *)result + 29);
  *(_DWORD *)((char *)result + 46) = v1;
  *((_BYTE *)result + 29) = v5 & 0x7F;
  v8 = dword_51A96C;
  result[10] = 0;
  *((_WORD *)result + 22) = v8;
  return result;
}
// 47A802: variable 'v1' is possibly undefined
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0047A850) --------------------------------------------------------
_DWORD * Rules_ReturnFact(_DWORD *a1)
{
  _DWORD *v2; // ebx
  int v3; // ecx
  _DWORD *v4; // edx
  int v5; // eax
  unsigned int v6; // eax
  _DWORD *result; // eax

  v2 = a1 + 10;
  v3 = 0;
  if ( *(int *)((char *)a1 + 46) > 0 )
  {
    v4 = a1 + 10;
    do
    {
      if ( *((_WORD *)v4 + 7) == 4 )
        Rules_ReturnMultifieldToPool((_DWORD *)v4[4]);
      ++v3;
      v4 = (_DWORD *)((char *)v4 + 6);
    }
    while ( v3 < *(_DWORD *)((char *)v2 + 6) );
  }
  if ( *(_DWORD *)((char *)a1 + 46) )
    v5 = *(_DWORD *)((char *)a1 + 46);
  else
    v5 = 1;
  v6 = 6 * (v5 - 1) + 60;
  dword_54DBB4 = v6;
  if ( v6 >= 0x1F4 )
    return (_DWORD *)Mem_SmallBlockRelease(a1, v6);
  dword_54DBAC = (int)a1;
  *a1 = *(_DWORD *)(dword_54DBA8 + 4 * v6);
  result = (_DWORD *)(dword_54DBA8 + 4 * dword_54DBB4);
  *result = dword_54DBAC;
  return result;
}
// 47A86D: variable 'v3' is possibly undefined
// 47A871: variable 'v4' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DBB4: using guessed type int dword_54DBB4;

//----- (0047A900) --------------------------------------------------------
int  Rules_InstallFact(_DWORD *a1)
{
  int result; // eax
  int v3; // ebx
  int v4; // ecx
  int v5; // ecx

  ++g_Rules_InstalledFactCount;
  result = a1[4];
  ++*(_DWORD *)(result + 28);
  v3 = 0;
  if ( *(int *)((char *)a1 + 46) > 0 )
  {
    v4 = (int)(a1 + 10);
    do
    {
      Rules_AtomInstall(*(__int16 *)(v4 + 14), *(_DWORD *)(v4 + 16), v4);
      ++v3;
      result = *(_DWORD *)((char *)a1 + 46);
      v4 = v5 + 6;
    }
    while ( v3 < result );
  }
  ++a1[2];
  return result;
}
// 47A936: variable 'v5' is possibly undefined
// 51A164: using guessed type int dword_51A164;

//----- (0047A950) --------------------------------------------------------
int  Rules_DeinstallFact(int a1)
{
  int v2; // esi
  int result; // eax
  int v4; // ebx
  int v5; // ecx
  int v6; // ecx

  v2 = a1 + 40;
  --g_Rules_InstalledFactCount;
  result = *(_DWORD *)(a1 + 16);
  --*(_DWORD *)(result + 28);
  v4 = 0;
  if ( *(int *)(v2 + 6) > 0 )
  {
    v5 = v2;
    do
    {
      Rules_AtomDeinstall(*(__int16 *)(v5 + 14), *(__int16 **)(v5 + 16), v5);
      ++v4;
      result = *(_DWORD *)(v2 + 6);
      v5 = v6 + 6;
    }
    while ( v4 < result );
  }
  --*(_DWORD *)(a1 + 8);
  return result;
}
// 47A989: variable 'v6' is possibly undefined
// 51A164: using guessed type int dword_51A164;

//----- (0047A9A0) --------------------------------------------------------
int  Rules_GetNextFact(int a1)
{
  if ( !a1 )
    return g_Rules_FactListHead;
  if ( *(char *)(a1 + 29) >= 0 )
    return *(_DWORD *)(a1 + 36);
  return 0;
}
// 51A15C: using guessed type int dword_51A15C;

//----- (0047A9C0) --------------------------------------------------------
int  Rules_GetNextFactInModule(int a1)
{
  int v1; // edx

  if ( a1 )
  {
    if ( *(char *)(a1 + 29) < 0 )
      return 0;
    v1 = *(_DWORD *)(a1 + 36);
  }
  else
  {
    v1 = g_Rules_FactListHead;
    if ( g_Rules_LastFactModuleCache != dword_51A9C0 )
    {
      Lexer_MarkImpliedTemplates();
      g_Rules_LastFactModuleCache = dword_51A9C0;
    }
  }
  while ( v1 && (*(_BYTE *)(*(_DWORD *)(v1 + 16) + 24) & 4) == 0 )
    v1 = *(_DWORD *)(v1 + 36);
  return v1;
}
// 47A9DD: variable 'v1' is possibly undefined
// 51A15C: using guessed type int dword_51A15C;
// 51A168: using guessed type int dword_51A168;
// 51A9C0: using guessed type int dword_51A9C0;

//----- (0047AA40) --------------------------------------------------------
int  Rules_GetFactIndex(int a1)
{
  return *(_DWORD *)(a1 + 24);
}

//----- (0047AA50) --------------------------------------------------------
_DWORD * Rules_Log(const char *a1, int a2, double a3)
{
  _DWORD *result; // eax

  result = Rules_StringToFact(a1, a2, a3);
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
  int v1; // ecx

  result = Rules_GetNextFact(0);
  if ( !result )
    return 0;
  while ( v1 != *(_DWORD *)(result + 24) )
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
_DWORD * Rules_AssertCommand(uintptr_t a1, uintptr_t a2, double a3)
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
  out = a1;
  *(_DWORD *)(out + 4) = 2;
  *(_DWORD *)(out + 8) = dword_54DD70;
  expression = (uintptr_t)(unsigned int)*(_DWORD *)(dword_51A960 + 6);
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
    Parser_ParseForm((__int16 *)expression, parsed, (int)slot_constraint, a3);
    if ( slot_constraint && (*(_BYTE *)(slot_constraint + 4) & 1) == 0 && parsed[1] == 4 )
    {
      multifield_reorder_needed = 1;
      Rules_ReportMultifieldAssertIntoSingleSlotError((int)slot_constraint, (int)deftemplate_record);
      parsed[1] = 2;
      parsed[2] = dword_54DD70;
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
  result = Rules_AssertFactDriver(fact, a3);
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
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // [esp-4h] [ebp-3Ch] BYREF
  int v12; // [esp+0h] [ebp-38h]
  int v13; // [esp+4h] [ebp-34h]
  _BYTE v14[24]; // [esp+14h] [ebp-24h] BYREF
  int v15; // [esp+2Ch] [ebp-Ch]
  int v16; // [esp+30h] [ebp-8h]

  v16 = a2;
  v15 = a1;
  v3 = *(__int16 **)(dword_51A960 + 6);
  for ( i = 1; v3; ++i )
  {
    while ( 1 )
    {
      Parser_ParseForm(v3, &v11, (int)v3, a3);
      if ( v12 != 1 )
        break;
      if ( *(int *)(v13 + 16) < 0 )
      {
        Parser_ReportError(i, (int)aFactAddressFac);
        return;
      }
      v6 = Rules_FindFactByIndex();
      if ( !v6 )
      {
        a3 = sprintf_(v14, "f-%ld", v7);
        Rules_ReportCantFindItem(v9, (int)v14);
        goto LABEL_6;
      }
LABEL_5:
      Rules_RetractFact(v6, a3);
LABEL_6:
      v3 = *(__int16 **)(v8 + 10);
      ++i;
      if ( !v3 )
        return;
    }
    if ( v12 == 6 )
    {
      v6 = v13;
      goto LABEL_5;
    }
    if ( v12 == 2 && !strcmp_(v5, asc_502790) )
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
  int v3; // esi
  int v4; // ecx
  int v5; // eax
  _DWORD v6[10]; // [esp-4h] [ebp-28h] BYREF

  v6[8] = a1;
  v3 = Rules_GetFactDuplicationFlag();
  if ( Lexer_TokenExpect(1) == -1 )
    return v4;
  Rules_RtnUnknown(1, v6, a2);
  v5 = 1;
  if ( v6[0] == 2 && v6[1] == dword_54DD70 )
    v5 = 0;
  unknown_libname_8(v5);
  return v3;
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
  int v3; // [esp+4h] [ebp-18h]

  result = Lexer_TokenExpect(1);
  if ( result != -1 )
  {
    Rules_RtnUnknown(1, v2, a1);
    if ( v2[1] == 6 )
    {
      if ( *(char *)(v3 + 29) >= 0 )
        return Rules_GetFactIndex(v3);
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
  int v6; // ebp
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // [esp+0h] [ebp-30h] BYREF
  int v11; // [esp+4h] [ebp-2Ch]
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
  if ( v11 != 2 )
  {
    if ( v11 != 1 || (v5 = *(_DWORD *)(v12 + 16), v5 < 0) )
    {
      Parser_ReportError(1, (int)aSymbolOrPositi);
      Rules_SetEvaluationErrorFlag(1);
      return Lexer_ErrorRecover(1);
    }
    v6 = 0;
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
    v6 = 1;
LABEL_8:
    result = Rules_ParsePositiveIntArg(v6 + 2, v3, v4, a1);
    if ( result != -2 )
    {
      result = Rules_ParsePositiveIntArg(v6 + 3, v3, result, a1);
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
int  Rules_PrintFactRange(int a1, int a2, int a3, int a4)
{
  int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v14; // [esp+0h] [ebp-18h]
  int v16; // [esp+8h] [ebp-10h]

  v7 = 0;
  v14 = Module_GetCurrent();
  v16 = 0;
  if ( v8 )
  {
    Module_SetCurrent(v8);
    v9 = 0;
LABEL_3:
    v10 = Rules_GetNextFactInModule(v9);
    goto LABEL_4;
  }
  v16 = 1;
  v10 = Rules_GetNextFact(0);
LABEL_4:
  while ( v10 )
  {
    if ( Rules_GetEvaluationErrorFlag() == 1 )
      return Module_SetCurrent(v14);
    if ( a2 < *(_DWORD *)(v11 + 24) && a2 != -1 || !a4 )
      break;
    if ( a3 <= *(_DWORD *)(v11 + 24) )
    {
      Rules_PrintFactWithIndex(v11, v11);
      ++v7;
      Output_Write(a1, (int)asc_5027CC, v12);
      if ( a4 > 0 )
        --a4;
    }
    if ( !v16 )
    {
      v9 = v11;
      goto LABEL_3;
    }
    v10 = Rules_GetNextFact(v11);
  }
  Rules_PrintTally(a1, v7, (int)aFacts_1, (int)aFact);
  return Module_SetCurrent(v14);
}
// 47B1C2: variable 'v8' is possibly undefined
// 47B1EA: variable 'v11' is possibly undefined
// 47B215: variable 'v12' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047B270) --------------------------------------------------------
signed int  Rules_ParsePositiveIntArg(int a1, int a2, int a3, double a4)
{
  signed int result; // eax
  _DWORD v6[9]; // [esp-8h] [ebp-24h] BYREF

  v6[7] = a3;
  if ( a1 > a2 )
    return -1;
  if ( !Lexer_ParseValueList(a1, v6, 1, a4) )
    return -2;
  result = *(_DWORD *)(v6[2] + 16);
  if ( result < 0 )
  {
    Parser_ReportError(a1, (int)aPositiveNumber);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -2;
  }
  return result;
}

//----- (0047B2F0) --------------------------------------------------------
_DWORD * Rules_AssertStringFunction(int a1, int a2, double a3)
{
  _DWORD *result; // eax
  int v5; // ecx
  _DWORD v6[10]; // [esp-8h] [ebp-28h] BYREF

  v6[8] = a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = dword_54DD70;
  result = (_DWORD *)Lexer_TokenExpect(1);
  if ( result != (_DWORD *)-1 )
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v6, 3, a3);
    if ( result )
    {
      result = Rules_Log(*(const char **)(v6[2] + 16), v5, a3);
      if ( result )
      {
        *(_DWORD *)(a1 + 4) = 6;
        *(_DWORD *)(a1 + 8) = result;
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
  int v1; // esi
  _DWORD *v2; // edi
  int v3; // ecx
  int result; // eax
  int v5; // ecx
  const CHAR *v6; // ebp
  int v7; // ecx
  _DWORD v8[6]; // [esp+0h] [ebp-34h] BYREF
  int v9; // [esp+18h] [ebp-1Ch]

  v1 = 1;
  v2 = 0;
  v3 = Lexer_TokenExpect(1);
  v9 = v3;
  if ( v3 == -1 )
    return 0;
  result = Rules_GetFileNameArg(1, v3, a1);
  v6 = (const CHAR *)result;
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
        v1 = 2;
      }
    }
    if ( v9 > 2 )
      v2 = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(dword_51A960 + 6) + 10) + 10);
    result = Rules_SaveFactsToFile(v6, v1, v2, a1);
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
signed int  Rules_SaveFactsToFile(const CHAR *a1, int a2, _DWORD *a3, double a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // esi
  int v8; // ecx
  int v9; // ecx
  int i; // ebx
  int v12; // ecx
  int v13; // eax
  _DWORD *v14; // edx
  int v15; // [esp+0h] [ebp-30h] BYREF
  int v16; // [esp+4h] [ebp-2Ch] BYREF
  int v17; // [esp+8h] [ebp-28h]
  int v18; // [esp+Ch] [ebp-24h]
  int v19; // [esp+10h] [ebp-20h]
  int v20; // [esp+14h] [ebp-1Ch]
  int v21; // [esp+18h] [ebp-18h]
  _DWORD *v22; // [esp+1Ch] [ebp-14h]

  v21 = a2;
  v5 = IO_FOpen(a1, (unsigned __int8 *)aW_0, (int)a1, (DWORD)a3);
  v7 = v5;
  if ( v5 )
  {
    IO_SetFastSaveFile(v5);
    v17 = g_Print_PreserveEscapedCharactersFlag;
    g_Print_PreserveEscapedCharactersFlag = 1;
    v18 = g_Print_AddressesToStringsFlag;
    g_Print_AddressesToStringsFlag = 1;
    v19 = g_Print_InstanceAddressesToNamesFlag;
    g_Print_InstanceAddressesToNamesFlag = 1;
    v22 = Rules_CollectFactsToArray(a3, v21, &v16, &v15, a4);
    if ( v16 )
    {
      g_Print_PreserveEscapedCharactersFlag = v17;
      g_Print_AddressesToStringsFlag = v18;
      g_Print_InstanceAddressesToNamesFlag = v19;
      fclose_(v8);
      IO_SetFastSaveFile(0);
      return 0;
    }
    else
    {
      v20 = Module_GetCurrent();
      for ( i = Rules_GetNextFactInModule(0); i; i = Rules_GetNextFactInModule(i) )
      {
        if ( v21 == 1 && v20 != **(_DWORD **)(*(_DWORD *)(i + 16) + 8) )
          continue;
        if ( a3 )
        {
          v13 = 0;
          if ( v15 <= 0 )
            continue;
          v14 = v22;
          while ( v14[2] != *(_DWORD *)(i + 16) )
          {
            ++v13;
            v14 += 6;
            if ( v13 >= v15 )
              goto LABEL_6;
          }
        }
        Rules_PrintFact(v7, i);
        Output_Write(v7, (int)asc_5027CC, v12);
LABEL_6:
        ;
      }
      g_Print_PreserveEscapedCharactersFlag = v17;
      g_Print_AddressesToStringsFlag = v18;
      g_Print_InstanceAddressesToNamesFlag = v19;
      fclose_(v9);
      IO_SetFastSaveFile(0);
      if ( a3 )
        Mem_SmallBlockRelease(v22, 24 * v15);
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
        int a2,
        _DWORD *a3,
        int *a4,
        double a5)
{
  int v5; // edi
  _DWORD *v7; // eax
  int v8; // ecx
  int v9; // ebx
  _DWORD *v10; // esi
  int v11; // eax
  int v12; // edx
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // edx
  int v17; // [esp+0h] [ebp-28h] BYREF
  _DWORD *v18; // [esp+4h] [ebp-24h]
  _DWORD *v19; // [esp+8h] [ebp-20h]
  int v20; // [esp+Ch] [ebp-1Ch]
  int v21; // [esp+10h] [ebp-18h]
  int v22; // [esp+14h] [ebp-14h]
  int v23; // [esp+18h] [ebp-10h]

  v5 = (int)result;
  v20 = a2;
  v19 = a3;
  *a3 = 0;
  if ( !result )
  {
    *a4 = 0;
    return result;
  }
  *a4 = 0;
  do
  {
    result = *(_DWORD **)((char *)result + 10);
    ++*a4;
  }
  while ( result );
  v7 = Mem_NewArray(24 * *a4);
  v8 = 0;
  v18 = v7;
  v9 = *a4;
  v23 = 0;
  if ( v9 <= 0 )
    return v18;
  v10 = v7;
  v21 = 3;
  while ( 1 )
  {
    Parser_ParseForm((__int16 *)v5, v10, v8, a5);
    if ( dword_51A964 )
    {
      *v19 = 1;
      Mem_SmallBlockRelease(v18, 24 * *a4);
      return 0;
    }
    if ( v10[1] != 2 )
    {
      v13 = v21;
      *v19 = 1;
      Parser_ReportError(v13, (int)aSymbol_1);
      Mem_SmallBlockRelease(v18, 24 * *a4);
      return 0;
    }
    if ( v20 != 1 )
      break;
    v22 = Rules_FindDeftemplateByName(*(_BYTE **)(v10[2] + 16), 1);
    if ( !v22 )
    {
      v15 = v21;
      *v19 = v14;
      Parser_ReportError(v15, (int)aLocalDeftempla);
      Mem_SmallBlockRelease(v18, 24 * *a4);
      return 0;
    }
LABEL_11:
    v10 += 6;
    v11 = v22;
    v12 = v23;
    *(v10 - 5) = 35;
    *(v10 - 4) = v11;
    v23 = v12 + 1;
    v5 = *(_DWORD *)(v5 + 10);
    v8 = *a4;
    ++v21;
    if ( v12 + 1 >= v8 )
      return v18;
  }
  if ( v20 != 2 )
    goto LABEL_11;
  v22 = Rules_FindImportExportConstruct(aDeftemplate_4, &v17, *(_BYTE **)(v10[2] + 16), 1, dword_51A964);
  if ( v22 )
    goto LABEL_11;
  v16 = v21;
  *v19 = 1;
  Parser_ReportError(v16, (int)aVisibleDeftemp);
  Mem_SmallBlockRelease(v18, 24 * *a4);
  return 0;
}
// 47B696: conditional instruction was optimized away because eax.4!=0
// 47B818: variable 'v14' is possibly undefined
// 51A964: using guessed type int dword_51A964;

//----- (0047B890) --------------------------------------------------------
BOOL  Rules_LoadFactsFromFile(const CHAR *a1, int a2, DWORD a3, double a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // ebx
  __int16 *v8; // eax
  int v9; // ecx
  int v10; // ecx
  int v12; // [esp-18h] [ebp-34h] BYREF
  _DWORD v13[7]; // [esp+0h] [ebp-1Ch] BYREF

  v13[5] = a2;
  v5 = IO_FOpen(a1, (unsigned __int8 *)aR_0, (int)a1, a3);
  v7 = v5;
  if ( !v5 )
  {
    Rules_OpenFileErrorMessage(v6, v6);
    return 0;
  }
  IO_SetFastLoadFile(v5);
  v13[0] = 100;
  do
  {
    v8 = (__int16 *)Rules_ParseAssertFormFromFile(v7, v13);
    v9 = (int)v8;
    if ( v8 )
      Parser_ParseForm(v8, &v12, (int)v8, a4);
    else
      v13[0] = 102;
    AST_Free(v9);
  }
  while ( v13[0] != 102 );
  IO_SetFastLoadFile(0);
  fclose_(v10);
  return !dword_51A964;
}
// 47B8D3: variable 'v9' is possibly undefined
// 47B8E8: variable 'v10' is possibly undefined
// 47B907: variable 'v6' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A964: using guessed type int dword_51A964;

//----- (0047B930) --------------------------------------------------------
int  Rules_ParseAssertFormFromFile(int a1, _DWORD *a2)
{
  int **Symbol; // eax
  signed int v6; // esi
  int v7; // ecx
  int v8[6]; // [esp+0h] [ebp-18h] BYREF

  v8[0] = 0;
  Parser_NextToken(a1, (int)a2);
  if ( *a2 != 100 )
    return 0;
  Symbol = Rules_MakeSymbol(aAssert);
  v6 = AST_NewNode(10, (int)Symbol);
  *(_DWORD *)(v6 + 6) = Rules_ParseAssertRHSPattern(a1, (int)a2, 1, v8, 0, 1, 101);
  if ( v8[0] == 1 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunctionLoadFa, v7);
    Lexer_ErrorRecover(1);
  }
  else if ( !AST_TreeContainsSpecialTag(v6, 1) )
  {
    return v6;
  }
  AST_Free(v6);
  return 0;
}
// 47B9B8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047B9E0) --------------------------------------------------------
int  Rules_AssertParsedFact(int a1, int a2, int a3)
{
  int v4; // edx
  _DWORD v6[3]; // [esp+0h] [ebp-1Ch] BYREF
  int v7[4]; // [esp+Ch] [ebp-10h] BYREF

  v7[2] = a3;
  AST_Free(a1);
  IO_OutWriteToken(asc_502890);
  Rules_IncrementIndentDepth(8);
  Rules_ParseAssertCommand(a2, v6, 1, v7, 1, (int)aAssertCommand);
  Rules_DecrementIndentDepth(8);
  return v4;
}
// 47BA28: variable 'v4' is possibly undefined

//----- (0047BA31) --------------------------------------------------------
signed int  IO_AdvanceBufferCursor(int a1, int a2)
{
  int v2; // edi
  int v3; // esi
  int v4; // edi
  signed int result; // eax

  if ( a1 > *(_DWORD *)(a2 + 4) || a1 < *(_DWORD *)(*(_DWORD *)(a2 + 8) + 8) - *(_DWORD *)a2 )
    return 1;
  v2 = *(_DWORD *)(a2 + 4);
  v3 = a1 + *(_DWORD *)a2;
  *(_BYTE *)(a2 + 12) &= ~0x10u;
  v4 = v2 - a1;
  *(_DWORD *)a2 = v3;
  result = 0;
  *(_DWORD *)(a2 + 4) = v4;
  return result;
}

//----- (0047BA70) --------------------------------------------------------
int  IO_ResetBufferCursor(int result)
{
  int v1; // edx

  *(_BYTE *)(result + 12) &= ~0x10u;
  v1 = *(_DWORD *)(*(_DWORD *)(result + 8) + 8);
  *(_DWORD *)(result + 4) = 0;
  *(_DWORD *)result = v1;
  return result;
}

//----- (0047BA86) --------------------------------------------------------
signed int  IO_SeekStreamGuarded(int a1, int a2, unsigned int a3, int a4)
{
  int fd_index;
  int seek_result;

  (void)a4;
  fd_index = *(_DWORD *)(a1 + 16);
  g_CRT_FileHandleLockAcquireHook(fd_index);
  seek_result = Compat_StreamSeek(a1, a2, (int)a3);
  g_CRT_FileHandleLockReleaseHook(fd_index, seek_result);
  if ( seek_result == -1 )
    return -1;
  return 0;
}
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);

//----- (0047BC10) --------------------------------------------------------
BOOL __stdcall InputBackend_StoreEnumeratedDevice(int a1, int a2)
{
  return (*(int (__stdcall **)(int, int, int *, _DWORD))(*(_DWORD *)a2 + 12))(a2, a1 + 4, &g_InputBackendTempJoystickDevice, 0) != 0;
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
InputBackendState * InputBackend_ReleaseDevices(InputBackendState *a1)
{
  _DWORD *raw; // esi
  int v2; // edx
  int v3; // ecx
  int v4; // esi

  raw = (_DWORD *)a1;
  v2 = raw[1];
  if ( v2 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)v2 + 8))(v2);
    raw[1] = 0;
  }
  v3 = raw[2];
  if ( v3 )
  {
    (*(void (__thiscall **)(int, _DWORD))(*(_DWORD *)v3 + 8))(v3, raw[2]);
    raw[2] = 0;
  }
  v4 = raw[3];
  if ( v4 )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)v4 + 8))(raw[3]);
    raw[3] = 0;
  }
  if ( raw[0] )
  {
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)raw[0] + 8))(raw[0]);
    raw[0] = 0;
  }
  return a1;
}

//----- (0047BD10) --------------------------------------------------------
signed int  InputBackend_Initialize(InputBackendState *a1, int a2, int a3)
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

  raw = (_DWORD *)a1;
  if ( DirectInputCreateA(a2, 768, raw, 0) )
    return 0;
  if ( !(*(int (__stdcall **)(_DWORD, void *, _DWORD *, _DWORD))(*(_DWORD *)raw[0] + 12))(raw[0], &g_InputBackendMouseDeviceGuid, raw + 2, 0) )
  {
    (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[2] + 44))(raw[2], g_InputBackendMouseDataFormat);
    (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[2] + 52))(raw[2], a3, 5);
    if ( (*(int (__stdcall **)(_DWORD))(*(_DWORD *)raw[2] + 28))(raw[2]) )
      return 0;
    raw[77] = 1;
  }
  if ( (*(int (__stdcall **)(_DWORD, void *, _DWORD *, _DWORD))(*(_DWORD *)raw[0] + 12))(raw[0], &g_InputBackendKeyboardDeviceGuid, raw + 1, 0) )
    goto LABEL_9;
  (*(void (__stdcall **)(_DWORD, int *))(*(_DWORD *)raw[1] + 44))(raw[1], g_InputBackendKeyboardDataFormat);
  (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[1] + 52))(raw[1], a3, 6);
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
  (*(void (__stdcall **)(_DWORD, int, int))(*(_DWORD *)raw[3] + 52))(raw[3], a3, 6);
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
int  InputBackend_PollState(InputBackendState *state, int a2, int a3)
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
  v11 = a2;
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
  _DWORD *v0; // ecx
  int v1; // ecx

  v0 = (_DWORD *)g_Rules_ConstructTypeListHead;
  if ( !g_Rules_ConstructTypeListHead )
    return 0;
  while ( strcmp_(v0, *v0) )
  {
    v0 = *(_DWORD **)(v1 + 48);
    if ( !v0 )
      return 0;
  }
  return v1;
}
// 47C21C: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A194: using guessed type int dword_51A194;

//----- (0047C2B0) --------------------------------------------------------
signed int  Rules_Save(const CHAR *a1, int a2, DWORD a3)
{
  signed int result; // eax
  int v4; // ecx
  int i; // edx
  int v6; // edx

  result = IO_FOpen(a1, (unsigned __int8 *)aW_1, a2, a3);
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
  int v0; // edx
  int *v2; // eax

  if ( !g_Rules_ResetInProgressFlag )
  {
    g_Rules_ResetInProgressFlag = 1;
    if ( !dword_51A96C )
      Rules_SetEvaluationErrorFlag(0);
    if ( !g_Rules_BeforeResetCallback || g_Rules_BeforeResetCallback() )
    {
      if ( g_Rules_ResetFunctionListHead )
      {
        v0 = g_Rules_ResetFunctionListHead;
        do
        {
          if ( Rules_GetEvaluationErrorFlag() )
            break;
          ((void (*)(void))(uintptr_t)(unsigned int)*(_DWORD *)(v0 + 4))();
          v0 = *(_DWORD *)(v0 + 12);
        }
        while ( v0 );
      }
      v2 = Module_FindByName(aMain);
      Module_SetCurrent((int)v2);
      if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
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
signed int  Rules_AddResetFunction(int a1, int a2, int a3)
{
  g_Rules_ResetFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_ResetFunctionListHead, a2);
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
    if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
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
signed int  Rules_AddClearReadyFunction(int a1, int a2, int a3)
{
  g_Rules_ClearReadyFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_ClearReadyFunctionListHead, a2);
  return 1;
}
// 51A1A0: using guessed type int dword_51A1A0;

//----- (0047C660) --------------------------------------------------------
signed int  Rules_AddClearFunction(int a1, int a2, int a3)
{
  g_Rules_ClearFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_ClearFunctionListHead, a2);
  return 1;
}
// 51A19C: using guessed type int dword_51A19C;

//----- (0047C680) --------------------------------------------------------
BOOL Rules_RemoveClearFunction(int a1)
{
  _DWORD v3[3]; // [esp+0h] [ebp-Ch] BYREF

  g_Rules_ClearFunctionListHead = Rules_RemoveNamedCallbackReturningHead(a1, g_Rules_ClearFunctionListHead, v3);
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
_DWORD * Module_BuildNameListMultifield(_DWORD *a1, int (*a2)(void), int (*a3)(void))
{
  signed int v6; // ecx
  int v7; // eax
  int v8; // ecx
  _DWORD *v9; // ebx
  _DWORD *result; // eax
  char *v11; // eax
  int v12; // ecx
  int v13; // ecx

  if ( ((int (__thiscall *)(_DWORD))a2)(0) )
  {
    do
    {
      v7 = a2();
      v6 = v8 + 1;
    }
    while ( v7 );
  }
  a1[1] = 4;
  a1[4] = v6 - 1;
  a1[3] = 0;
  v9 = Rules_CreateEphemeralMultifield(v6);
  a1[2] = v9;
  result = (_DWORD *)((int (__thiscall *)(int))a2)(1);
  if ( result )
  {
    while ( dword_51A968 != 1 )
    {
      *((_WORD *)v9 + 7) = 2;
      v9 = (_DWORD *)((char *)v9 + 6);
      v11 = (char *)a3();
      *(_DWORD *)((char *)v9 + 10) = Str_Intern(v11, v12);
      result = (_DWORD *)((int (__thiscall *)(int))a2)(v13 + 1);
      if ( !result )
        return result;
    }
    return Rules_SetMultifieldErrorValue((int)a1);
  }
  return result;
}
// 47C6E6: variable 'v8' is possibly undefined
// 47C6F0: variable 'v6' is possibly undefined
// 47C737: variable 'v12' is possibly undefined
// 47C741: variable 'v13' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (0047C760) --------------------------------------------------------
int  Rules_FreeConstructHeaderString(int *a1, int a2)
{
  int result; // eax
  const char *v4; // edx

  result = Rules_DecrementSymbolCount(*a1, a2);
  v4 = (const char *)a1[1];
  if ( v4 )
  {
    result = Mem_SmallBlockFree((_DWORD *)a1[1], strlen(v4) + 1);
    a1[1] = 0;
  }
  return result;
}

//----- (0047C7A0) --------------------------------------------------------
_DWORD * Rules_RegisterConstructType(
        int a1,
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
        int a12)
{
  _DWORD *v13; // edi
  _DWORD *result; // eax

  v13 = *(_DWORD **)(dword_54DBA8 + 208);
  if ( v13 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 208);
    *(_DWORD *)(dword_54DBA8 + 208) = *v13;
    result = (_DWORD *)dword_54DBAC;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x34);
  }
  *result = a1;
  result[1] = a2;
  result[2] = a4;
  result[3] = a3;
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
signed int  Rules_AddSaveFunction(int a1, int a2, int a3)
{
  g_Rules_SaveFunctionListHead = (int)Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_SaveFunctionListHead, a2);
  return 1;
}
// 51A188: using guessed type int dword_51A188;

//----- (0047C850) --------------------------------------------------------
signed int  Rules_Bload(int a1, DWORD a2)
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

  result = Rules_BloadOpenFile((const CHAR *)(uintptr_t)(unsigned int)a1, a2);
  if ( !result )
    return result;
  Rules_BloadReadBlock((uintptr_t)header, strlen((const char *)g_Rules_BloadFileHeaderID) + 1);
  if ( strcmp(header, (const char *)g_Rules_BloadFileHeaderID) )
  {
    Rules_PrintErrorID((int)aBload_0, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFile, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotABinaryCo, 0);
    Rules_BloadCloseFile(0);
    return 0;
  }
  Rules_BloadReadBlock((uintptr_t)header, strlen(g_Rules_BsaveVersionID) + 1);
  if ( strcmp(header, g_Rules_BsaveVersionID) )
  {
    Rules_PrintErrorID((int)aBload_0, 3, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFile, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, 0);
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
  dword_54DD24 = Rules_ReadNeededFunctions(&function_table_count, &missing_functions);
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
    construct = dword_51AA3C;
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
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], a1, 0);
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
    construct_table = dword_51AA3C;
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
  if ( dword_54DD24 )
    Mem_ReleasePoolBlock(dword_54DD24, 4 * function_table_count);
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
        int a2,
        void (__fastcall *a3)(signed int, signed int))
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

  previous_allocator_handler = unknown_libname_4((int)CSyncObject_Unlock);
  chunk_count = result;
  do
  {
    chunk_bytes = a2 * chunk_count;
    chunk_base = Mem_HeapAllocWithRetry((_DWORD *)chunk_bytes);
    if ( !chunk_base )
    {
      if ( chunk_count / 2 )
      {
        chunk_count /= 2;
      }
      else if ( ((int (__cdecl *)(int))(intptr_t)previous_allocator_handler)(chunk_bytes) == 1 )
      {
        return unknown_libname_4(previous_allocator_handler);
      }
    }
  }
  while ( !chunk_base );

  unknown_libname_4(previous_allocator_handler);
  initialized_count = 0;
  while ( initialized_count < result )
  {
    entries_this_pass = result - initialized_count;
    if ( entries_this_pass > chunk_count )
      entries_this_pass = chunk_count;
    Rules_BloadReadBlock(chunk_base, entries_this_pass * a2);
    if ( entries_this_pass > 0 )
    {
      entry_ptr = chunk_base;
      for ( entry_index = 0; entry_index < entries_this_pass; ++entry_index )
      {
        a3(entry_ptr, initialized_count);
        ++initialized_count;
        entry_ptr += a2;
      }
    }
  }
  return Mem_ReleasePoolBlock(chunk_base, chunk_bytes);
}

//----- (0047CCF0) --------------------------------------------------------
int  Rules_ReadNeededFunctions(int *a1, int *a2)
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

  Rules_BloadReadBlock((uintptr_t)a1, 4u);
  Rules_BloadReadBlock((uintptr_t)&string_bytes, 4u);
  unresolved = 0;
  function_count = *a1;
  if ( !function_count )
  {
    *a2 = 0;
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
  *a2 = unresolved;
  return table;
}
// 47CDD0: variable 'v13' is possibly undefined
// 47CDE4: variable 'v14' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0047CE60) --------------------------------------------------------
int __fastcall Rules_FindFunctionByName(int a1, int a2)
{
  int head; // edi
  int current; // ecx
  int next; // ecx
  const char *registered_name; // edx

  head = Rules_GetFunctionDefinitionListHead();
  if ( !head )
    return 0;
  current = a2 ? *(_DWORD *)(a2 + 27) : head;
  while ( current )
  {
    registered_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(*(_DWORD *)current + 16);
    if ( !strcmp((const char *)(uintptr_t)(unsigned int)a1, registered_name) )
      return current;
    next = *(_DWORD *)(current + 27);
    if ( next == a2 )
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
    for ( construct_node = dword_51AA3C; construct_node; construct_node = *(_DWORD *)(construct_node + 36) )
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
_DWORD * Rules_AddBeforeBloadFunction(int a1, int a2, int a3)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_BeforeBloadFunctionListHead, a2);
  g_Rules_BeforeBloadFunctionListHead = (int)result;
  return result;
}
// 51A1B0: using guessed type int dword_51A1B0;

//----- (0047CFE0) --------------------------------------------------------
_DWORD * Rules_AddAfterBloadFunction(int a1, int a2, int a3)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_AfterBloadCallbackListHead, a2);
  g_Rules_AfterBloadCallbackListHead = (int)result;
  return result;
}
// 51A1B4: using guessed type int dword_51A1B4;

//----- (0047D020) --------------------------------------------------------
_DWORD * Rules_AddAbortBloadFunction(int a1, int a2, int a3)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(a1, a3, g_Rules_AbortBloadCallbackListHead, a2);
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
int  Rules_SystemCommand(double a1)
{
  char *v1; // edi
  int result; // eax
  int v3; // ebp
  int v4; // esi
  int v5; // edx
  int v6; // [esp+0h] [ebp-38h] BYREF
  int v7; // [esp+4h] [ebp-34h]
  int v8; // [esp+8h] [ebp-30h]
  int v9; // [esp+18h] [ebp-20h] BYREF
  unsigned int v10[7]; // [esp+1Ch] [ebp-1Ch] BYREF

  v1 = 0;
  v9 = 0;
  v10[0] = 0;
  result = Lexer_TokenExpect(1);
  v3 = result;
  if ( result != -1 )
  {
    v4 = 1;
    if ( result < 1 )
    {
LABEL_6:
      if ( v1 )
      {
        if ( g_Rules_SystemCommandPreShellHook )
          g_Rules_SystemCommandPreShellHook();
        system_(v1);
        if ( g_Rules_SystemCommandPostShellHookA )
          g_Rules_SystemCommandPostShellHookA();
        if ( g_Rules_SystemCommandPostShellHookB )
          g_Rules_SystemCommandPostShellHookB();
        return Mem_SmallBlockFree(v1, v10[0]);
      }
    }
    else
    {
      while ( 1 )
      {
        Rules_RtnUnknown(v4, &v6, a1);
        if ( v7 != 3 && v7 != 2 )
          break;
        ++v4;
        result = (int)Str_Append(*(const char **)(v8 + 16), v1, v10, &v9);
        v1 = (char *)result;
        if ( v4 > v3 )
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
BOOL __fastcall Rules_BloadDeleteFile(int a1, int a2)
{
  return IO_RemoveFileByPath(a1, a2) == 0;
}
// 476A78: using guessed type int __fastcall sub_476A78(_DWORD, _DWORD);

//----- (0047D550) --------------------------------------------------------
BOOL  Rules_RenameFile(const CHAR *a1, const CHAR *a2, int a3)
{
  return IO_RenameFile(a1, a2, a3) == 0;
}

//----- (0047D560) --------------------------------------------------------
signed int  Rules_BloadOpenFile(const CHAR *a1, DWORD a2)
{
  int v2; // ecx

  dword_54DD30 = IO_FOpen(a1, (unsigned __int8 *)aRb_1, (int)a1, a2);
  if ( dword_54DD30 )
    return 1;
  Rules_OpenFileErrorMessage(v2, v2);
  return 0;
}
// 47D587: variable 'v2' is possibly undefined
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D5A0) --------------------------------------------------------
int  Rules_BloadReadBlock(uintptr_t a1, unsigned int a2)
{
  if ( !a2 )
    return 0;
  return fread_((void *)a1, a2, dword_54DD30, 1);
}
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D600) --------------------------------------------------------
signed int  Rules_BloadSeekFile(int a1, int a2)
{
  return IO_SeekStreamGuarded(dword_54DD30, a1, 1u, a2);
}
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D630) --------------------------------------------------------
int __thiscall Rules_BloadCloseFile(void *this)
{
  (void)this;
  return fclose_(dword_54DD30);
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 54DD30: using guessed type int dword_54DD30;

//----- (0047D660) --------------------------------------------------------
_DWORD * Rules_InsertActivationSorted(int *a1, _DWORD *activation)
{
  uintptr_t list_ref; // ebx
  uintptr_t node; // ecx
  uintptr_t current; // esi
  uintptr_t predecessor; // edx
  uintptr_t next; // eax

  Rules_SetAgendaChanged(1);
  list_ref = (uintptr_t)a1;
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
_DWORD * Rules_PlaceInDepthList(_DWORD *a1, int a2)
{
  int v2; // ecx
  unsigned int v3; // ebx
  _DWORD *v4; // edx
  int v5; // esi

  v2 = *(_DWORD *)(a2 + 8);
  v3 = *(_DWORD *)(a2 + 12);
  v4 = 0;
  if ( !a1 )
    return v4;
  while ( 1 )
  {
    v5 = a1[2];
    if ( v2 >= v5 )
    {
      if ( v2 > v5 )
        return v4;
      if ( v3 >= a1[3] )
        break;
    }
    v4 = a1;
    a1 = (_DWORD *)a1[7];
    if ( !a1 )
      return v4;
  }
  return v4;
}

//----- (0047D760) --------------------------------------------------------
_DWORD * Rules_PlaceInBreadthList(_DWORD *a1, int a2)
{
  int v2; // ecx
  unsigned int v3; // ebx
  _DWORD *v4; // edx
  int v5; // esi

  v2 = *(_DWORD *)(a2 + 8);
  v3 = *(_DWORD *)(a2 + 12);
  v4 = 0;
  if ( !a1 )
    return v4;
  while ( 1 )
  {
    v5 = a1[2];
    if ( v2 >= v5 )
    {
      if ( v2 > v5 )
        return v4;
      if ( v3 <= a1[3] )
        break;
    }
    v4 = a1;
    a1 = (_DWORD *)a1[7];
    if ( !a1 )
      return v4;
  }
  return v4;
}

//----- (0047D7A0) --------------------------------------------------------
_DWORD * Rules_PlaceInLexList(_DWORD *a1, int a2)
{
  _DWORD *v2; // ecx
  unsigned int v4; // ebp
  int v5; // edi
  _DWORD *v6; // ebx
  int v7; // eax
  signed int v9; // eax

  v2 = a1;
  if ( !*(_DWORD *)(a2 + 16) )
    *(_DWORD *)(a2 + 16) = Rules_BuildLexBasisOrder(*(int **)(a2 + 4));
  v4 = *(_DWORD *)(a2 + 12);
  v5 = *(_DWORD *)(a2 + 8);
  v6 = 0;
  if ( !v2 )
    return v6;
  while ( 1 )
  {
    v7 = v2[2];
    if ( v5 >= v7 )
    {
      if ( v5 > v7 )
        return v6;
      v9 = Rules_CompareActivationBasis((int)v2, (_DWORD **)a2);
      if ( v9 )
      {
        if ( v9 == 1 )
          return v6;
        if ( v4 <= v2[3] )
          break;
      }
    }
    v6 = v2;
    v2 = (_DWORD *)v2[7];
    if ( !v2 )
      return v6;
  }
  return v6;
}
// 47D7B9: variable 'v2' is possibly undefined

//----- (0047D810) --------------------------------------------------------
_DWORD * Rules_PlaceInMeaList(_DWORD *a1, int a2)
{
  _DWORD *v2; // ecx
  _DWORD *v4; // esi
  int v5; // eax
  int v7; // edi
  int v8; // edx
  int v9; // eax
  int v10; // ebp
  signed int v11; // eax
  unsigned int v12; // [esp+0h] [ebp-1Ch]
  int v13; // [esp+4h] [ebp-18h]

  v2 = a1;
  if ( !*(_DWORD *)(a2 + 16) )
    *(_DWORD *)(a2 + 16) = Rules_BuildLexBasisOrder(*(int **)(a2 + 4));
  v12 = *(_DWORD *)(a2 + 12);
  v4 = 0;
  v13 = *(_DWORD *)(a2 + 8);
  if ( !v2 )
    return v4;
  while ( 1 )
  {
    v5 = v2[2];
    if ( v5 > v13 )
      goto LABEL_5;
    if ( v5 < v13 )
      return v4;
    v7 = *(_DWORD *)(*(_DWORD *)(a2 + 4) + 8);
    v8 = -1;
    v9 = -1;
    if ( *(_DWORD *)v7 )
      v8 = *(_DWORD *)(*(_DWORD *)v7 + 12);
    v10 = **(_DWORD **)(v2[1] + 8);
    if ( v10 )
      v9 = *(_DWORD *)(v10 + 12);
    if ( v9 < v8 )
    {
      if ( v8 > 0 )
        return v4;
      goto LABEL_5;
    }
    if ( v9 > v8 )
    {
      if ( v9 <= 0 )
        return v4;
      goto LABEL_5;
    }
    v11 = Rules_CompareActivationBasis((int)v2, (_DWORD **)a2);
    if ( v11 )
    {
      if ( v11 == 1 )
        return v4;
      if ( v12 <= v2[3] )
        return v4;
    }
LABEL_5:
    v4 = v2;
    v2 = (_DWORD *)v2[7];
    if ( !v2 )
      return v4;
  }
}
// 47D833: variable 'v2' is possibly undefined

//----- (0047D8D0) --------------------------------------------------------
_DWORD * Rules_PlaceInComplexityList(_DWORD *a1, _DWORD *a2)
{
  unsigned int v2; // edi
  int v3; // ebx
  int v4; // esi
  _DWORD *v5; // edx
  int v6; // ecx
  int v8; // ecx

  v2 = a2[3];
  v3 = a2[2];
  v4 = *(_DWORD *)(*a2 + 28) & 0x7FF;
  v5 = 0;
  if ( !a1 )
    return v5;
  while ( 1 )
  {
    v6 = a1[2];
    if ( v3 >= v6 )
    {
      if ( v3 > v6 )
        return v5;
      v8 = *(_DWORD *)(*a1 + 28) & 0x7FF;
      if ( v4 >= v8 )
      {
        if ( v4 > v8 )
          return v5;
        if ( v2 <= a1[3] )
          break;
      }
    }
    v5 = a1;
    a1 = (_DWORD *)a1[7];
    if ( !a1 )
      return v5;
  }
  return v5;
}

//----- (0047D930) --------------------------------------------------------
_DWORD * Rules_PlaceInSimplicityList(_DWORD *a1, _DWORD *a2)
{
  unsigned int v2; // edi
  int v3; // ebx
  int v4; // esi
  _DWORD *v5; // edx
  int v6; // ecx
  int v8; // ecx

  v2 = a2[3];
  v3 = a2[2];
  v4 = *(_DWORD *)(*a2 + 28) & 0x7FF;
  v5 = 0;
  if ( !a1 )
    return v5;
  while ( 1 )
  {
    v6 = a1[2];
    if ( v3 >= v6 )
    {
      if ( v3 > v6 )
        return v5;
      v8 = *(_DWORD *)(*a1 + 28) & 0x7FF;
      if ( v4 <= v8 )
      {
        if ( v4 < v8 )
          return v5;
        if ( v2 <= a1[3] )
          break;
      }
    }
    v5 = a1;
    a1 = (_DWORD *)a1[7];
    if ( !a1 )
      return v5;
  }
  return v5;
}

//----- (0047D990) --------------------------------------------------------
_DWORD * Rules_PlaceInRandomList(_DWORD *a1, _DWORD *a2)
{
  unsigned int v2; // esi
  int v3; // ecx
  int v4; // ebx
  _DWORD *v5; // edx
  int v6; // edi
  int v8; // edi

  v2 = a2[3];
  v3 = a2[2];
  v4 = a2[5];
  v5 = 0;
  if ( !a1 )
    return v5;
  while ( 1 )
  {
    v6 = a1[2];
    if ( v3 >= v6 )
    {
      if ( v3 > v6 )
        return v5;
      v8 = a1[5];
      if ( v4 <= v8 )
      {
        if ( v4 < v8 )
          return v5;
        if ( v2 <= a1[3] )
          break;
      }
    }
    v5 = a1;
    a1 = (_DWORD *)a1[7];
    if ( !a1 )
      return v5;
  }
  return v5;
}

//----- (0047D9E0) --------------------------------------------------------
_DWORD * Rules_BuildLexBasisOrder(int *a1)
{
  _DWORD *v1; // ecx
  int v2; // ebp
  int v3; // ebx
  _DWORD *v4; // eax
  int v5; // edx
  int v6; // ecx
  _DWORD *v8; // [esp+0h] [ebp-20h]
  int v9; // [esp+4h] [ebp-1Ch]

  v8 = Rules_MultifieldCopyWithMarkers(a1, 0, 0);
  v2 = (*v1 << 17 >> 23) - 1;
  do
  {
    v3 = 0;
    v9 = 0;
    if ( v2 > 0 )
    {
      v4 = v8;
      do
      {
        v5 = v4[2];
        if ( *(_DWORD *)v5 )
        {
          v6 = v4[3];
          if ( *(_DWORD *)v6 )
          {
            if ( *(_DWORD *)(*(_DWORD *)v5 + 12) < *(_DWORD *)(*(_DWORD *)v6 + 12) )
            {
              v4[3] = v5;
              v4[2] = v6;
              v9 = 1;
            }
          }
        }
        ++v3;
        ++v4;
      }
      while ( v3 < v2 );
    }
    --v2;
  }
  while ( v9 == 1 );
  return v8;
}
// 47D9F4: variable 'v1' is possibly undefined

//----- (0047DA60) --------------------------------------------------------
signed int  Rules_CompareActivationBasis(int a1, _DWORD **a2)
{
  int v3; // eax
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
  int v17; // [esp+0h] [ebp-24h]
  int v18; // [esp+4h] [ebp-20h]
  int v19; // [esp+8h] [ebp-1Ch]

  if ( !*(_DWORD *)(a1 + 16) )
  {
    v15 = Rules_BuildLexBasisOrder(*(int **)(a1 + 4));
    *(_DWORD *)(v16 + 16) = v15;
  }
  v18 = *a2[4] << 17 >> 23;
  v17 = **(_DWORD **)(a1 + 16) << 17 >> 23;
  if ( v17 <= v18 )
    v19 = **(_DWORD **)(a1 + 16) << 17 >> 23;
  else
    v19 = *a2[4] << 17 >> 23;
  v3 = 0;
  if ( v19 > 0 )
  {
    v4 = *(_DWORD *)(a1 + 16);
    v5 = a2[4];
    do
    {
      v6 = *(int **)(v4 + 8);
      if ( *v6 && (v7 = (int *)a2[4][v3 + 2], (v8 = *v7) != 0) )
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
        if ( **(_DWORD **)(*(_DWORD *)(a1 + 16) + 4 * v3 + 8) )
          return 0;
      }
      v4 += 4;
      ++v3;
      ++v5;
    }
    while ( v3 < v19 );
  }
  if ( v18 < v17 )
    return 0;
  if ( v18 > v17 )
    return 1;
  v11 = *(_DWORD *)(*(_DWORD *)a1 + 28) & 0x7FF;
  v12 = (*a2)[7] & 0x7FF;
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
int  Rules_SetStrategy(int a1)
{
  int v1; // edx

  v1 = g_Rules_ConflictResolutionStrategy;
  g_Rules_ConflictResolutionStrategy = a1;
  if ( v1 != a1 )
    Rules_ReorderAgenda(0);
  return v1;
}
// 47DBC0: variable 'v1' is possibly undefined
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DBE0) --------------------------------------------------------
signed int *Rules_GetStrategyCommand()
{
  char *v0; // eax
  int v1; // ecx

  Lexer_TokenExpect(0);
  v0 = Rules_GetStrategyName(g_Rules_ConflictResolutionStrategy);
  return Str_Intern(v0, v1);
}
// 47DBFA: variable 'v1' is possibly undefined
// 51A1D8: using guessed type int dword_51A1D8;

//----- (0047DC10) --------------------------------------------------------
signed int * Rules_SetStrategyCommand(int a1, double a2)
{
  int v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  char *v7; // eax
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  char *v15; // eax
  int v16; // ecx
  _DWORD v17[10]; // [esp-8h] [ebp-28h] BYREF

  v17[8] = a1;
  v3 = g_Rules_ConflictResolutionStrategy;
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, v17, 2, a2) )
  {
    v6 = g_Rules_ConflictResolutionStrategy;
    goto LABEL_5;
  }
  v4 = strcmp_(*(_DWORD *)(v17[2] + 16), aDepth);
  if ( !v4 )
  {
LABEL_4:
    Rules_SetStrategy(v4);
    v6 = v3;
LABEL_5:
    v7 = Rules_GetStrategyName(v6);
    return Str_Intern(v7, v8);
  }
  if ( !strcmp_(v5, aBreadth) )
  {
    v4 = 1;
    goto LABEL_4;
  }
  if ( !strcmp_(v10, aLex) )
  {
    v4 = 2;
    goto LABEL_4;
  }
  if ( !strcmp_(v11, aMea) )
  {
    v4 = 3;
    goto LABEL_4;
  }
  if ( !strcmp_(v12, aComplexity) )
  {
    v4 = 4;
    goto LABEL_4;
  }
  if ( !strcmp_(v13, aSimplicity) )
  {
    v4 = 5;
    goto LABEL_4;
  }
  if ( !strcmp_(v14, aRandom_0) )
  {
    v4 = 6;
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
char * Rules_GetStrategyName(int a1)
{
  char *result; // eax

  switch ( a1 )
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
_DWORD * Rules_AddActivation(int a1, int a2, double a3)
{
  uintptr_t join; // ebx
  uintptr_t partial_match; // edx
  uintptr_t activation; // ecx
  uintptr_t free_head; // ecx
  uintptr_t agenda; // eax
  int salience; // eax
  int sequence; // eax
  int bucket; // eax

  join = (uintptr_t)(unsigned int)a1;
  partial_match = (uintptr_t)(unsigned int)a2;
  if ( (*(_BYTE *)(join + 29) & 0x40) != 0 )
  {
    agenda = (uintptr_t)(unsigned int)*(_DWORD *)(join + 8);
    Rules_PushFocus(*(_DWORD *)agenda);
  }
  free_head = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)dword_54DBA8 + 128);
  if ( free_head )
  {
    dword_54DBAC = (int)free_head;
    *(_DWORD *)((uintptr_t)(unsigned int)dword_54DBA8 + 128) = *(_DWORD *)free_head;
    activation = (uintptr_t)(unsigned int)dword_54DBAC;
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
  _DWORD *v1; // ecx
  int v2; // edi
  _DWORD *v3; // esi

  v1 = *(_DWORD **)(*(_DWORD *)(result + 8) + 12);
  v2 = result;
  if ( v1 )
  {
    do
    {
      while ( 1 )
      {
        result = v2;
        v3 = (_DWORD *)v1[7];
        if ( v2 )
          break;
LABEL_5:
        v1 = v3;
        if ( !v3 )
          return result;
      }
      do
      {
        if ( result == *v1 )
        {
          result = Rules_RemoveActivation(v1, 1, 1);
          goto LABEL_5;
        }
        result = *(_DWORD *)(result + 48);
      }
      while ( result );
      v1 = (_DWORD *)v1[7];
    }
    while ( v3 );
  }
  return result;
}

//----- (0047DFE0) --------------------------------------------------------
int  Rules_GetNextActivation(int a1)
{
  int result; // eax

  if ( a1 )
    return *(_DWORD *)(a1 + 28);
  result = Module_GetItem(0, dword_54E64C);
  if ( result )
    return *(_DWORD *)(result + 12);
  return result;
}
// 54E64C: using guessed type int dword_54E64C;

//----- (0047E000) --------------------------------------------------------
int  Rules_GetActivationRuleName(int a1)
{
  return *(_DWORD *)(**(_DWORD **)a1 + 16);
}

//----- (0047E0D0) --------------------------------------------------------
signed int  Rules_DetachActivation(_DWORD *a1)
{
  _DWORD *v1; // ecx
  int v2; // eax
  _DWORD *v3; // edx
  int v4; // ebx
  int v5; // esi

  v1 = a1;
  if ( !a1 )
    Rules_ReportSystemError(0, 1);
  v2 = *(_DWORD *)(*v1 + 8);
  v3 = *(_DWORD **)(v2 + 12);
  if ( v1 == v3 )
    *(_DWORD *)(v2 + 12) = v3[7];
  v4 = v1[6];
  if ( v4 )
    *(_DWORD *)(v4 + 28) = v1[7];
  v5 = v1[7];
  if ( v5 )
    *(_DWORD *)(v5 + 24) = v1[6];
  v1[6] = 0;
  v1[7] = 0;
  g_Rules_AgendaChangedFlag = 1;
  return 1;
}
// 47E0DB: variable 'v1' is possibly undefined
// 51A1E8: using guessed type int dword_51A1E8;

//----- (0047E140) --------------------------------------------------------
signed int __fastcall Rules_PrintActivation(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  _BYTE v8[20]; // [esp+0h] [ebp-1Ch] BYREF
  int v9; // [esp+14h] [ebp-8h]

  v9 = a1;
  sprintf_(v8, "%-6d ", *(_DWORD *)(a2 + 8));
  Output_Write(v3, (int)v8, v3);
  Output_Write(v4, *(_DWORD *)(**(_DWORD **)a2 + 16), v4);
  Output_Write(v5, (int)asc_502D44, v5);
  return Rules_PrintArgumentValueList(v6, *(_DWORD **)(a2 + 4));
}
// 47E163: variable 'v3' is possibly undefined
// 47E171: variable 'v4' is possibly undefined
// 47E17D: variable 'v5' is possibly undefined
// 47E187: variable 'v6' is possibly undefined
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (0047E1A0) --------------------------------------------------------
int  Rules_ActivationsCommand(int a1, int a2)
{
  return Rules_ListConstructsAcrossModules(
           a1,
           a2,
           (int)aActivations,
           (int)aActivation_1,
           (int (__cdecl *)(int))Rules_GetNextActivation,
           0,
           (void (__fastcall *)(int, int))Rules_PrintActivation,
           0);
}

//----- (0047E1D0) --------------------------------------------------------
int  Rules_RemoveActivation(_DWORD *a1, int a2, int a3)
{
  _DWORD *v4; // ecx
  int v5; // edx
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // ecx
  _DWORD *v10; // edx
  int result; // eax
  int v12; // edx

  v4 = a1;
  v5 = *(_DWORD *)(*a1 + 8);
  if ( a2 == 1 )
  {
    v6 = a1[6];
    if ( v6 )
    {
      v12 = a1[7];
      *(_DWORD *)(v6 + 28) = v12;
      if ( v12 )
        *(_DWORD *)(v12 + 24) = a1[6];
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
  if ( a3 == 1 )
  {
    v10 = (_DWORD *)v4[1];
    if ( v10 )
      *(_DWORD *)(v4[1] + 4 * (*v10 << 17 >> 23) + 8) = 0;
  }
  --g_Rules_ActivationCount;
  if ( v4[4] )
    Rules_FreePartialMatch(v4[4]);
  dword_54DBAC = (int)v4;
  *v4 = *(_DWORD *)(dword_54DBA8 + 128);
  result = dword_54DBA8;
  *(_DWORD *)(dword_54DBA8 + 128) = dword_54DBAC;
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
  _DWORD *v1; // ecx

  result = *(_DWORD **)(Rules_GetDefruleModuleItem(0) + 12);
  if ( result )
  {
    do
    {
      Rules_RemoveActivation(result, 1, 1);
      result = v1;
    }
    while ( v1 );
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
  int v1; // esi
  int v2; // edi
  int Enum; // eax
  int v4; // ecx
  int *v5; // ebx
  int v6; // ecx

  v1 = result;
  v2 = 0;
  if ( result || (Enum = Module_NextEnum(0), v2 = 1, (v1 = Enum) != 0) )
  {
    do
    {
      v4 = Rules_GetDefruleModuleItem(v1);
      Enum = *(_DWORD *)(v4 + 12);
      *(_DWORD *)(v4 + 12) = 0;
      if ( Enum )
      {
        v5 = (int *)(v4 + 12);
        do
        {
          *(_DWORD *)(Enum + 24) = 0;
          v6 = *(_DWORD *)(Enum + 28);
          *(_DWORD *)(Enum + 28) = 0;
          Rules_InsertActivationSorted(v5, (_DWORD *)(uintptr_t)(unsigned int)Enum);
          Enum = v6;
        }
        while ( v6 );
      }
      if ( !v2 )
        break;
      Enum = Module_NextEnum(v1);
      v1 = Enum;
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
  int v4; // eax
  int v5; // edx
  int v6; // ecx

  result = (_BYTE *)Rules_GetConstructNameArg((int)aRuleName, a1, a2);
  if ( result )
  {
    v4 = Rules_FindDefruleByName(result, v3);
    if ( v4 )
      return (_BYTE *)Rules_RefreshRule(v4, a2);
    else
      return (_BYTE *)Rules_ReportCantFindItem(v6, v5);
  }
  return result;
}
// 47E3C8: variable 'v3' is possibly undefined
// 47E3D6: variable 'v6' is possibly undefined
// 47E3D6: variable 'v5' is possibly undefined

//----- (0047E3F0) --------------------------------------------------------
signed int  Rules_RefreshRule(int a1, double a2)
{
  int i; // ebx
  int j; // ecx

  for ( i = a1; i; i = *(_DWORD *)(i + 48) )
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
  int v2; // ebx
  int v3; // edx
  int v4; // esi
  int *i; // edx
  int v6; // ecx
  int v7; // ecx

  Module_BeginEnum();
  v2 = 0;
  if ( !v3 )
  {
    v2 = 1;
    Enum = Module_NextEnum(0);
  }
  v4 = g_Rules_SalienceEvaluationMode;
  for ( g_Rules_SalienceEvaluationMode = 1; Enum; Enum = Module_NextEnum(v7) )
  {
    Module_SetCurrent(Enum);
    for ( i = (int *)Rules_GetNextActivation(0); i; i = (int *)Rules_GetNextActivation((int)i) )
      i[2] = Rules_EvaluateSalience(*i, a1);
    Rules_ReorderAgenda(v6);
    if ( !v2 )
      break;
  }
  g_Rules_SalienceEvaluationMode = v4;
  return Module_EndEnum();
}
// 47E5D1: variable 'v3' is possibly undefined
// 47E5E6: variable 'Enum' is possibly undefined
// 47E5FE: variable 'a1' is possibly undefined
// 47E615: variable 'v6' is possibly undefined
// 47E620: variable 'v7' is possibly undefined
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E650) --------------------------------------------------------
signed int * Rules_SetSalienceEvaluationCommand(int a1, double a2)
{
  char *v3; // esi
  int v4; // ecx
  char *v5; // eax
  int v7; // ecx
  int v8; // ecx
  _DWORD v9[11]; // [esp-8h] [ebp-2Ch] BYREF

  v9[9] = a1;
  v3 = Rules_SalienceEvaluationModeName(g_Rules_SalienceEvaluationMode);
  if ( Lexer_TokenExpect(1) == -1 || !Lexer_ParseValueList(1, v9, 2, a2) )
  {
    v5 = v3;
    return Str_Intern(v5, v4);
  }
  if ( !strcmp_(*(_DWORD *)(v9[2] + 16), aWhenDefined) )
  {
    g_Rules_SalienceEvaluationMode = 0;
    v5 = v3;
    return Str_Intern(v5, v4);
  }
  if ( !strcmp_(v4, aWhenActivated) )
  {
    g_Rules_SalienceEvaluationMode = 1;
    return Str_Intern(v3, v7);
  }
  else
  {
    if ( !strcmp_(v7, aEveryCycle) )
      g_Rules_SalienceEvaluationMode = 2;
    else
      Parser_ReportError(1, (int)aSymbolWithVa_1);
    return Str_Intern(v3, v8);
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
  char *v0; // eax
  int v1; // ecx

  Lexer_TokenExpect(0);
  v0 = Rules_SalienceEvaluationModeName(g_Rules_SalienceEvaluationMode);
  return Str_Intern(v0, v1);
}
// 47E75A: variable 'v1' is possibly undefined
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E770) --------------------------------------------------------
char * Rules_SalienceEvaluationModeName(unsigned int a1)
{
  if ( !a1 )
    return aWhenDefined;
  if ( a1 <= 1 )
    return aWhenActivated;
  if ( a1 == 2 )
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
int __fastcall unknown_libname_7(int a1)
{
  int result; // eax

  result = g_Rules_SalienceEvaluationMode;
  g_Rules_SalienceEvaluationMode = a1;
  return result;
}
// 51A1EC: using guessed type int dword_51A1EC;

//----- (0047E7C0) --------------------------------------------------------
signed int  Rules_EvaluateSalience(int a1, double a2)
{
  signed int result; // eax
  int v4; // ecx
  _DWORD *v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // [esp+0h] [ebp-20h]
  int v10; // [esp+4h] [ebp-1Ch]

  if ( !g_Rules_SalienceEvaluationMode || !*(_DWORD *)(a1 + 32) )
    return *(_DWORD *)(a1 + 20);
  Lexer_ErrorRecover(0);
  if ( Parser_ParseForm(*(__int16 **)(v4 + 32), v5, v4, a2) )
  {
    Rules_SalienceInformationError();
    return *(_DWORD *)(v7 + 20);
  }
  else if ( v9 == 1 )
  {
    result = *(_DWORD *)(v10 + 16);
    if ( result > 10000 || result < -10000 )
    {
      Rules_SalienceRangeError();
      Lexer_ErrorRecover(1);
      Rules_SalienceInformationError();
      return *(_DWORD *)(a1 + 20);
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
  int v4; // eax
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
      v4 = Module_GetCurrent();
      return (int *)Rules_ActivationsCommand((int)g_IO_LogicalName_WDisplay, v4);
    }
  }
  return result;
}
// 47E8C5: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047E8E4) --------------------------------------------------------
int __fastcall IO_PrintfToStdout(int a1, int a2, int a3, char a4)
{
  int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[0] = (int)&a4;
  return CRT_VfprintfLockedWrite((int)&g_CRT_StdoutStream, a1, v5);
}

//----- (0047E910) --------------------------------------------------------
int  Rules_RunAgendaLoop(int a1, int a2, double a3)
{
  int v3; // ecx
  int *v4; // edi
  int v5; // edx
  int v6; // ebp
  _DWORD *v7; // esi
  unsigned int v8; // ebx
  _DWORD *v9; // edx
  int v10; // eax
  int result; // eax
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  _DWORD *v20; // ebx
  unsigned int v21; // edx
  unsigned int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // edi
  int v27; // esi
  int v28; // eax
  int v29; // ebp
  int v30; // eax
  int v31; // ecx
  int i; // edx
  int v33; // edx
  int v34; // eax
  int v35; // ecx
  int v36; // eax
  int v37; // ecx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  int v42; // edx
  int v43; // ecx
  char *v44; // edx
  int v45; // ecx
  int v46; // ecx
  int v47; // ecx
  double v48; // [esp+0h] [ebp-ECh]
  int v49; // [esp+4h] [ebp-E8h]
  int v50; // [esp+8h] [ebp-E4h]
  int v51; // [esp+8h] [ebp-E4h]
  int v52; // [esp+8h] [ebp-E4h]
  _DWORD v53[15]; // [esp+Ch] [ebp-E0h] BYREF
  _BYTE v54[60]; // [esp+48h] [ebp-A4h] BYREF
  int v55[6]; // [esp+84h] [ebp-68h] BYREF
  double v56; // [esp+9Ch] [ebp-50h]
  double v57; // [esp+A4h] [ebp-48h]
  int v59; // [esp+B4h] [ebp-38h]
  int v60; // [esp+B8h] [ebp-34h]
  int v61; // [esp+BCh] [ebp-30h]
  int v62; // [esp+C0h] [ebp-2Ch]
  int v63; // [esp+C4h] [ebp-28h]
  int v64; // [esp+C8h] [ebp-24h]
  int v65; // [esp+CCh] [ebp-20h]
  int v66; // [esp+D0h] [ebp-1Ch]
  int v67; // [esp+D4h] [ebp-18h]

  v66 = a1;
  v65 = 0;
  v64 = 0;
  v61 = 0;
  v60 = 0;
  v63 = 0;
  v59 = 0;
  v62 = 0;
  v57 = 0.0;
  if ( g_Rules_AgendaLoopRunningFlag )
    return 0;
  g_Rules_AgendaLoopRunningFlag = 1;
  if ( g_Rules_WatchStatisticsFlag )
  {
    v60 = Rules_GetInstalledFactCount();
    v63 = v60;
    v59 = Rules_GetActiveInstanceCount();
    v62 = v59;
    v64 = Rules_GetActivationCount();
    v61 = v64;
    v57 = Rules_TimeCommand();
  }
  if ( !dword_51A96C )
    Rules_SetEvaluationErrorFlag(0);
  v50 = a2;
  g_Rules_HaltRulesFlag = 0;
  v4 = (int *)Rules_NextActivationToFire();
  while ( v4 )
  {
    if ( !v66 || dword_51A968 || g_Rules_HaltRulesFlag )
      break;
    Rules_DetachActivation(v4);
    v6 = Rules_GetActivationRuleName((int)v4);
    v7 = (_DWORD *)v4[1];
    g_Rules_CurrentlyExecutingRule = *v4;
    ++v65;
    if ( v5 > 0 )
      v66 = v5 - 1;
    if ( (*(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) & 0x20) != 0 )
    {
      a3 = sprintf_(v53, "FIRE %4ld ", v65);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)v53, v12);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], v6, v13);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E90, v14);
      Rules_PrintArgumentValueList((int)g_IO_LogicalNameTable_WTrace[0], v7);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E94, v15);
    }
    v7[(*v7 << 17 >> 23) + 2] = 0;
    v8 = 0;
    *(_BYTE *)v7 |= 2u;
    dword_51ACFC = (int)v7;
    dword_51AD00 = 0;
    v9 = v7;
    while ( v8 < *v7 << 17 >> 23 )
    {
      v10 = *(_DWORD *)v9[2];
      if ( v10 )
        (*(void (**)(void))(*(_DWORD *)v10 + 52))();
      ++v9;
      ++v8;
    }
    g_Rules_CurrentLogicalJoin = *(_DWORD *)(g_Rules_CurrentlyExecutingRule + 40);
    ++dword_51A96C;
    Lexer_ErrorRecover(0);
    *(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) |= 0x80u;
    Rules_ExecuteRuleActions(
      **(_DWORD **)(g_Rules_CurrentlyExecutingRule + 8),
      *(__int16 **)(g_Rules_CurrentlyExecutingRule + 36),
      v55,
      *(_DWORD *)(g_Rules_CurrentlyExecutingRule + 24),
      a3,
      0);
    *(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) &= ~0x80u;
    Lexer_ErrorRecover(0);
    g_Rules_CurrentLogicalJoin = v16;
    --dword_51A96C;
    if ( dword_51A968 || g_Rules_HaltRulesFlag && (*(_BYTE *)(g_Rules_CurrentlyExecutingRule + 29) & 0x20) != 0 )
    {
      Rules_PrintErrorID((int)aPrccode, 4, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExecutionHalte, v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v6, v18);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDotNewline_RuleRuntime, v19);
    }
    v20 = v7;
    v21 = 0;
    *(_BYTE *)v7 &= ~2u;
    while ( 1 )
    {
      v22 = (*v7 << 17 >> 23) - 1;
      if ( v21 >= v22 )
        break;
      v23 = *(_DWORD *)v20[2];
      if ( v23 )
        (*(void (**)(void))(*(_DWORD *)v23 + 48))();
      ++v20;
      ++v21;
    }
    if ( (*(_BYTE *)v7 & 0x20) == 0 )
    {
      v24 = *(_DWORD *)v7[v22 + 2];
      if ( v24 )
        (*(void (__cdecl **)(int))(*(_DWORD *)v24 + 48))(v50);
    }
    Rules_RemoveActivation(v4, 0, 0);
    Rules_FlushPendingNetworkGarbage();
    Rules_RunPeriodicCleanup(0, 1);
    if ( g_Rules_WatchStatisticsFlag )
    {
      v25 = Rules_GetInstalledFactCount();
      if ( v25 > v60 )
        v60 = v25;
      v26 = v59;
      v27 = v25 + v63;
      v28 = Rules_GetActiveInstanceCount();
      v63 = v27;
      if ( v28 > v26 )
        v59 = v28;
      v29 = v28 + v62;
      v30 = Rules_GetActivationCount();
      v62 = v29;
      if ( v30 > v31 )
        v64 = v30;
      v61 += v30;
    }
    if ( Rules_GetSalienceEvaluation() == 2 )
      Rules_RefreshAgenda(a3);
    for ( i = g_Rules_PostRuleFireCallbackListHead; i; i = *(_DWORD *)(v33 + 12) )
      (*(void (**)(void))(i + 4))();
    if ( qword_51ACC0 == 1 )
      Rules_RemoveModuleFocus(**(_DWORD **)(g_Rules_CurrentlyExecutingRule + 8));
    qword_51ACC0 = 0;
    v34 = Rules_NextActivationToFire();
    v3 = v34;
    v4 = (int *)v34;
    if ( v34 && (*(_BYTE *)(*(_DWORD *)v34 + 29) & 8) != 0 )
    {
      g_Rules_HaltRulesFlag = 1;
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aBreakingOnRule, v34);
      v36 = Rules_GetActivationRuleName(v35);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], v36, (int)g_IO_LogicalNameTable_WDialog[0]);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aDotNewline_RuleRuntime, v37);
    }
  }
  if ( v66 == v65 )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aRuleFiringLimi, v3);
  g_Rules_CurrentlyExecutingRule = 0;
  g_Rules_HaltRulesFlag = 0;
  if ( g_Rules_WatchStatisticsFlag )
  {
    double runtime_end;
    double runtime_elapsed;
    double sample_count;

    runtime_end = Rules_TimeCommand();
    v56 = runtime_end;
    Rules_PrintLongInteger(v38, v65);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aRulesFired, v39);
    if ( v57 >= runtime_end )
    {
      v44 = asc_502E94;
    }
    else
    {
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aRunTimeIs, v40);
      runtime_elapsed = runtime_end - v57;
      v56 = runtime_elapsed;
      Rules_PrintFloat((int)g_IO_LogicalNameTable_WDialog[0], runtime_elapsed);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)" seconds.\n", 0);
      v48 = (double)v65 / runtime_elapsed;
      Rules_PrintFloat((int)g_IO_LogicalNameTable_WDialog[0], v48);
      v44 = " rules per second.\n";
    }
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v44, v40);
    sample_count = (double)(v65 + 1);
    v67 = (int)((double)v63 / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(v54, "%ld mean number of facts (%ld maximum).\n", v67, v60);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v54, v45);
    v67 = (int)((double)v62 / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(v54, "%ld mean number of instances (%ld maximum).\n", v67, v59);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v54, v46);
    v67 = (int)((double)v61 / sample_count + g_Rules_AverageRoundingBias);
    sprintf_(v54, "%ld mean number of activations (%ld maximum).\n", v67, v64);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)v54, v47);
  }
  if ( g_Rules_FocusStackTop && Module_GetCurrent() != *(_DWORD *)g_Rules_FocusStackTop )
    Module_SetCurrent(*(_DWORD *)g_Rules_FocusStackTop);
  result = v65;
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
  int v0; // edx
  int *v2; // eax

  if ( !g_Rules_FocusStackTop )
  {
    v2 = Module_FindByName(aMain_0);
    Rules_PushFocus((int)v2);
  }
  v0 = *(_DWORD *)(*(_DWORD *)(g_Rules_FocusStackTop + 4) + 12);
  while ( !v0 )
  {
    if ( !g_Rules_FocusStackTop )
      break;
    Rules_PopFocus();
    if ( g_Rules_FocusStackTop )
      v0 = *(_DWORD *)(*(_DWORD *)(g_Rules_FocusStackTop + 4) + 12);
  }
  return v0;
}
// 47F039: variable 'v0' is possibly undefined
// 51A200: using guessed type int dword_51A200;

//----- (0047F060) --------------------------------------------------------
int  Rules_RemoveModuleFocus(int a1)
{
  int v2; // ebx
  int v3; // ebp
  _DWORD *v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int result; // eax

  v2 = 0;
  v3 = 0;
  if ( !g_Rules_FocusStackTop )
    return 0;
  v4 = (_DWORD *)g_Rules_FocusStackTop;
  v5 = 0;
  do
  {
    if ( v2 )
      break;
    if ( a1 == *v4 )
    {
      v6 = v4[2];
      dword_54DBAC = (int)v4;
      *v4 = *(_DWORD *)(dword_54DBA8 + 48);
      v2 = 1;
      *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
      v4 = (_DWORD *)v6;
      if ( v5 )
      {
        *(_DWORD *)(v5 + 8) = v6;
      }
      else
      {
        v3 = 1;
        g_Rules_FocusStackTop = v6;
      }
    }
    else
    {
      v5 = (int)v4;
      v4 = (_DWORD *)v4[2];
    }
  }
  while ( v4 );
  if ( !v2 )
    return *(_DWORD *)g_Rules_FocusStackTop;
  if ( g_Rules_WatchFocusFlag )
  {
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aFocus, v5);
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(*(_DWORD *)a1 + 16), v7);
    if ( g_Rules_FocusStackTop && v3 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)aTo_0, v8);
      Output_Write((int)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(**(_DWORD **)g_Rules_FocusStackTop + 16), v9);
    }
    Output_Write((int)g_IO_LogicalNameTable_WTrace[0], (int)asc_502E94, v8);
  }
  if ( g_Rules_FocusStackTop )
  {
    if ( v3 )
      Module_SetCurrent(*(_DWORD *)g_Rules_FocusStackTop);
  }
  result = a1;
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
    focus_entry = *(_DWORD *)(dword_54DBA8 + 48);
    if ( focus_entry )
    {
      dword_54DBAC = focus_entry;
      *(_DWORD *)(dword_54DBA8 + 48) = *(_DWORD *)focus_entry;
      focus_entry = dword_54DBAC;
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
  int v5; // [esp+0h] [ebp-1Ch]
  int v6; // [esp+14h] [ebp-8h]

  v6 = a1;
  result = Lexer_TokenExpect(1);
  if ( result != v3 )
  {
    if ( result == 1 )
    {
      result = Lexer_ParseValueList(1, &v4, 1, a2);
      if ( result )
        return Rules_RunAgendaLoop(*(_DWORD *)(v5 + 16), *(_DWORD *)(v5 + 16), a2);
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
signed int  Rules_ClearBreakFlag(int a1)
{
  int v1; // edx
  char v2; // bl

  v1 = 0;
  if ( !a1 )
    return v1;
  do
  {
    while ( 1 )
    {
      v2 = *(_BYTE *)(a1 + 29);
      if ( (v2 & 8) != 0 )
        break;
      a1 = *(_DWORD *)(a1 + 48);
      if ( !a1 )
        return v1;
    }
    v1 = 1;
    *(_BYTE *)(a1 + 29) = v2 & 0xF7;
    a1 = *(_DWORD *)(a1 + 48);
  }
  while ( a1 );
  return 1;
}

//----- (0047F480) --------------------------------------------------------
void Rules_RemoveAllBreakFlags()
{
  int v0; // ecx
  int v1; // edx

  v0 = 0;
  while ( 1 )
  {
    v0 = Module_NextEnum(v0);
    if ( !v0 )
      return;
    v1 = 0;
    while ( (v1 = Rules_GetNextDefrule(v1)) != 0 )
      Rules_ClearBreakFlag(v1);
  }
}

//----- (0047F4B0) --------------------------------------------------------
int  Rules_ListRuleBreakpoints(int a1, int a2)
{
  return Rules_ListConstructsAcrossModules(
           a1,
           a2,
           0,
           0,
           (int (__cdecl *)(int))Rules_GetNextDefrule,
           (int (*)(void))Rules_GetConstructNameString,
           0,
           (int (*)(void))Rules_RuleHasBreakFlag);
}

//----- (0047F4D0) --------------------------------------------------------
int  Rules_RuleHasBreakFlag(int a1)
{
  return *(_DWORD *)(a1 + 28) << 20 >> 31;
}

//----- (0047F4E0) --------------------------------------------------------
int  Rules_SetBreakCommand(int a1, double a2)
{
  int result; // eax
  int v3; // ecx
  int v4; // eax
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
      v4 = Rules_FindDefruleByName(*(_BYTE **)(v7[2] + 16), v3);
      if ( v4 )
        return Rules_SetBreakFlag(v4);
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
  int v3; // eax
  int v4; // eax
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
  v3 = Lexer_TokenExpect(1);
  if ( v3 != -1 )
  {
    if ( v3 )
    {
      if ( Lexer_ParseValueList(1, &v9, 2, a2) )
      {
        v4 = Rules_FindDefruleByName(*(_BYTE **)(v10 + 16), *(_DWORD *)(v10 + 16));
        if ( v4 )
        {
          if ( !Rules_ClearBreakFlag(v4) )
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
  int v4; // eax
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
      v4 = Module_GetCurrent();
      return (int *)Rules_ListRuleBreakpoints((int)g_IO_LogicalName_WDisplay, v4);
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
  int v1; // ebx
  int *v2; // ecx
  int Name; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  v1 = result;
  v2 = (int *)g_Rules_FocusStackTop;
  if ( g_Rules_FocusStackTop )
  {
    do
    {
      Name = Module_GetName(*v2);
      Output_Write(v1, Name, v4);
      result = Output_Write(v1, (int)asc_502E94, v5);
      v2 = *(int **)(v6 + 8);
    }
    while ( v2 );
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
  _DWORD *v1; // ecx

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Rules_BuildFocusStackList(v1);
  return result;
}
// 47F70E: variable 'v1' is possibly undefined

//----- (0047F720) --------------------------------------------------------
signed int  Rules_BuildFocusStackList(_DWORD *a1)
{
  int v2; // edx
  signed int v3; // eax
  _DWORD *v4; // eax
  int v5; // ecx
  _DWORD *v6; // ebx
  int v7; // edx
  signed int result; // eax
  _DWORD *v9; // ecx
  int v10; // ecx

  v2 = g_Rules_FocusStackTop;
  v3 = 0;
  if ( g_Rules_FocusStackTop )
  {
    do
    {
      v2 = *(_DWORD *)(v2 + 8);
      ++v3;
    }
    while ( v2 );
    a1[1] = 4;
    a1[3] = 0;
    a1[4] = v3 - 1;
    v4 = Rules_CreateEphemeralMultifield(v3);
    *(_DWORD *)(v5 + 8) = v4;
    v6 = v4;
    v7 = g_Rules_FocusStackTop;
    result = 1;
    if ( g_Rules_FocusStackTop )
    {
      v9 = v6;
      do
      {
        *((_WORD *)v9 + 7) = 2;
        v9[4] = **(_DWORD **)v7;
        v9 = (_DWORD *)((char *)v9 + 6);
        v7 = *(_DWORD *)(v7 + 8);
        ++result;
      }
      while ( v7 );
    }
  }
  else
  {
    a1[1] = 4;
    a1[4] = -1;
    a1[3] = 0;
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
  int v0; // eax

  Lexer_TokenExpect(0);
  v0 = Rules_PopFocus();
  if ( v0 )
    return *(_DWORD *)v0;
  else
    return dword_54DD70;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (0047F7F0) --------------------------------------------------------
int Rules_GetFocusFunction()
{
  int v0; // eax

  Lexer_TokenExpect(0);
  v0 = Rules_GetCurrentFocus();
  if ( v0 )
    return *(_DWORD *)v0;
  else
    return dword_54DD70;
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
  int v3; // esi
  signed int result; // eax
  int *v5; // eax
  int v6; // edx
  int v7; // ecx
  _DWORD v8[10]; // [esp-8h] [ebp-28h] BYREF

  v8[8] = a1;
  v2 = Lexer_TokenExpect(1);
  if ( v2 == -1 )
    return 0;
  v3 = v2;
  if ( v2 <= 0 )
    return 1;
  while ( 1 )
  {
    result = Lexer_ParseValueList(v3, v8, 2, a2);
    if ( !result )
      break;
    v5 = Module_FindByName(*(_BYTE **)(v8[2] + 16));
    if ( !v5 )
    {
      Rules_ReportCantFindItem(v7, v6);
      return 0;
    }
    --v3;
    Rules_PushFocus((int)v5);
    if ( v3 <= 0 )
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
signed int  Rules_RetractFactById(int a1, double a2)
{
  int v2; // ecx
  int v3; // edx

  v2 = 1;
  if ( a1 )
    return Instance_DeleteInstance(a1, a2);
  v3 = dword_51AD0C;
  while ( v3 )
  {
    if ( !Instance_DeleteInstance(v3, a2) )
      v2 = 0;
  }
  if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
    Rules_RunPeriodicCleanup(1, 0);
  return v2;
}
// 47FBAA: variable 'v3' is possibly undefined
// 47FBDF: variable 'v2' is possibly undefined
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51AD0C: using guessed type int dword_51AD0C;

//----- (0047FBF0) --------------------------------------------------------
BOOL  Rules_UnmakeInstance(int a1, double a2)
{
  BOOL v3; // edi
  int v4; // ebp
  int i; // esi

  v3 = 1;
  v4 = g_Instance_PurgeInProgress;
  g_Instance_PurgeInProgress = 1;
  if ( a1 )
  {
    MessageHandler_SendToInstanceAddress(dword_51AD38, a1, 0, 0, a2);
    v3 = (*(_BYTE *)(a1 + 24) & 2) != 0;
  }
  else
  {
    i = dword_51AD0C;
    while ( i )
    {
      MessageHandler_SendToInstanceAddress(dword_51AD38, i, 0, 0, a2);
      if ( (*(_BYTE *)(i + 24) & 2) == 0 )
        v3 = 0;
      for ( i = *(_DWORD *)(i + 68); i; i = *(_DWORD *)(i + 68) )
      {
        if ( (*(_DWORD *)(i + 24) & 2) == 0 )
          break;
      }
    }
  }
  g_Instance_PurgeInProgress = v4;
  Instance_PurgeDeletedInstances();
  if ( dword_51A96C || dword_51A97C || dword_51A960 )
    return v3;
  Rules_RunPeriodicCleanup(1, 0);
  return v3;
}
// 51A280: using guessed type int dword_51A280;
// 51A960: using guessed type int dword_51A960;
// 51A96C: using guessed type int dword_51A96C;
// 51A97C: using guessed type int dword_51A97C;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD38: using guessed type int dword_51AD38;

//----- (0047FCB0) --------------------------------------------------------
void  Rules_InstancesCommand(double a1)
{
  int v1; // ebp
  _BYTE *v2; // esi
  int v3; // ecx
  int v4; // ecx
  int v5; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  _DWORD v10[2]; // [esp+0h] [ebp-34h] BYREF
  int v11; // [esp+8h] [ebp-2Ch]
  int v12; // [esp+18h] [ebp-1Ch]

  Module_GetCurrent();
  v1 = 0;
  v2 = 0;
  v12 = Rules_RtnArgCount();
  if ( v12 <= 0 )
    goto LABEL_16;
  if ( !Lexer_ParseValueList(1, v10, 2, a1) )
    return;
  if ( !Module_FindByName(*(_BYTE **)(v11 + 16)) && strcmp_(v3, asc_5033CC) )
  {
    Lexer_ErrorRecover(1);
    Parser_ReportError(v5, (int)aDefmoduleName);
    return;
  }
  if ( v12 <= 1 )
    goto LABEL_16;
  if ( !Lexer_ParseValueList(2, v10, 2, a1) )
    return;
  v2 = *(_BYTE **)(v11 + 16);
  if ( !Class_LookupByModule(v4, v2) )
  {
    if ( strcmp_(v6, asc_5033CC) )
    {
      Class_ReportLookupError(v7, (int)v2);
      return;
    }
    v2 = 0;
  }
  if ( v12 <= 2 )
  {
LABEL_16:
    Rules_PrintInstancesByModule((int)g_IO_LogicalName_WDisplay, v1, (int)v2);
    return;
  }
  if ( Lexer_ParseValueList(3, v10, 2, a1) )
  {
    if ( strcmp_(v8, aInherit) )
    {
      Lexer_ErrorRecover(1);
      Parser_ReportError(v9, (int)aKeywordInherit);
      return;
    }
    v1 = 1;
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
  int v2; // edx
  int v3; // ecx

  result = MessageHandler_CheckCurrentMessage((int)this, 1);
  if ( result )
  {
    result = MessageHandler_GetNthArgument(0);
    v2 = *(_DWORD *)(result + 8);
    if ( (*(_BYTE *)(v2 + 24) & 2) == 0 )
    {
      Rules_PrintInstanceSlots((int)g_IO_LogicalName_WDisplay, v2, (int)asc_5033FC);
      return Output_Write((int)g_IO_LogicalName_WDisplay, (int)asc_5033FC, v3);
    }
  }
  return result;
}
// 47FE70: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (0047FE80) --------------------------------------------------------
void  Rules_PrintInstancesByModule(int a1, int a2, int a3)
{
  signed int v4; // esi
  int v5; // edx
  int i; // esi
  int Name; // eax
  int v8; // ecx
  int v9; // ecx
  signed int v10; // [esp+0h] [ebp-18h]
  int v12; // [esp+8h] [ebp-10h]

  v4 = Class_NewTraversalID();
  v10 = v4;
  v12 = 0;
  if ( v4 != -1 )
  {
    Module_BeginEnum();
    if ( v5 )
    {
      Module_SetCurrent(v5);
      v12 = Rules_ListInstancesForClassOrModule(v4, a1, a3, v9);
    }
    else
    {
      for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
      {
        Name = Module_GetName(i);
        Output_Write(a1, Name, v8);
        Output_Write(a1, (int)asc_503400, a2);
        Module_SetCurrent(i);
        v12 += Rules_ListInstancesForClassOrModule(v10, a1, a3, 1);
      }
    }
    Module_EndEnum();
    Class_ReleaseTraversalID();
    if ( !dword_51A968 )
      Rules_PrintTally(a1, v12, (int)aInstances, (int)aInstance_1);
  }
}
// 47FEB1: variable 'v5' is possibly undefined
// 47FECF: variable 'v8' is possibly undefined
// 47FF63: variable 'v9' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (0047FF70) --------------------------------------------------------
_DWORD * Rules_AssertFact(const char *a1, int a2, double a3)
{
  _DWORD *result; // eax
  int **Symbol; // eax
  signed int v5; // ebx
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
    fprintf(stderr, "[menu-probe] rules-assert-enter %s\n", a1);
  if ( trace_rules_assert )
  {
    fprintf(stderr, "[rules] assert-enter fact=\"%s\" caller=%p\n", a1 ? a1 : "<null>", __builtin_return_address(0));
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
  parse_buffer[2] = dword_54DD70;
  result = (_DWORD *)IO_OpenStringSource((int)aMkins, a1, 0);
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
        a1 ? a1 : "<null>");
      fflush(stderr);
    }
    if ( token_buffer[0] == 100 )
    {
      if ( !dword_54DD40 )
      {
        if ( trace_load_save )
          fprintf(stderr, "[menu-probe] rules-assert-seed-make-instance-symbol\n");
        Rules_RegisterHostFunction(aMakeInstance, 117, (int)aMakeinstanceco, (int)Instance_MakeInstanceFunction, 0);
      }
      Symbol = Rules_MakeSymbol(aMakeInstance);
      if ( trace_load_save )
        fprintf(stderr, "[menu-probe] rules-assert-after-make-symbol symbol=%p\n", Symbol);
      v5 = AST_NewNode(10, (int)Symbol);
      if ( trace_load_save )
        fprintf(stderr, "[menu-probe] rules-assert-after-ast-new-node node=%d\n", v5);
      if ( Rules_ParseMakeInstanceNode(v5, (int)aMkins) )
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
            a1 ? a1 : "<null>");
          fflush(stderr);
        }
        if ( token_buffer[0] == 102 )
          Parser_ParseForm((__int16 *)v5, parse_buffer, (int)aMkins, a3);
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
            a1 ? a1 : "<null>");
          fflush(stderr);
        }
        AST_Free(v5);
      }
    }
    else
    {
      Parser_ReportSyntaxError();
    }
    IO_CloseStringRouter((int)aMkins);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] rules-assert-after-router-remove\n");
    if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
      Rules_RunPeriodicCleanup(1, 0);
    if ( trace_rules_assert )
    {
      fprintf(
        stderr,
        "[rules] assert-result-candidate type=%08x value=%08x nil=%08x fact=\"%s\"\n",
        parse_buffer[1],
        parse_buffer[2],
        dword_54DD70,
        a1 ? a1 : "<null>");
      fflush(stderr);
    }
    if ( parse_buffer[1] == 2 && parse_buffer[2] == dword_54DD70 )
      result = (_DWORD *)(dword_54DD70 ^ parse_buffer[2]);
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
int  Rules_GetInstanceSlotValue(int a1, _BYTE *a2, int a3, _DWORD *a4)
{
  int *v4; // eax
  int result; // eax

  (void)a3;
  if ( (*(_BYTE *)(a1 + 24) & 2) != 0 || (v4 = Rules_FindInstanceSlot(a1, a2)) == 0 )
  {
    Lexer_ErrorRecover(1);
    a4[1] = 2;
    result = dword_54DD70;
    a4[2] = dword_54DD70;
  }
  else
  {
    a4[1] = (unsigned int)(v4[1] << 24) >> 26;
    a4[2] = v4[2];
    if ( (v4[1] & 0xFC) == 0x10 )
    {
      a4[3] = 0;
      a4[4] = *(_DWORD *)(v4[2] + 6) - 1;
    }
    return Rules_PropagateReturnValueDepth((uintptr_t)a4);
  }
  return result;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (00480160) --------------------------------------------------------
signed int  Rules_PutInstanceSlotValue(int a1, _BYTE *a2, int a3, _DWORD *a4, double a5)
{
  int *v6; // eax
  signed int result; // eax

  (void)a3;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
  {
    fprintf(
      stderr,
      "[world_action] fact_external_put_enter selected=%d a=%d b=%d c=%d key=%s arg1=%d arg2=%d cursor=%d,%d flipping=%d lost=%d\n",
      g_SelectedUnitIndex,
      a1,
      (int)(intptr_t)a2,
      (int)(intptr_t)a4,
      a2 ? (const char *)a2 : "(null)",
      a4 ? a4[1] : -1,
      a4 ? a4[2] : -1,
      dword_544CFC >> byte_54512C,
      dword_544D00 >> byte_54512C,
      DD_IsFlipping((int)&g_RenderState),
      DD_IsLost((int)&g_RenderState));
    fflush(stderr);
  }
  if ( (*(_BYTE *)(a1 + 24) & 2) == 0 && a4 && (v6 = Rules_FindInstanceSlot(a1, a2)) != 0 )
  {
    result = Instance_PutSlotValue((_DWORD *)a1, v6, a4, a5);
    if ( result )
    {
      if ( !dword_51A96C && !dword_51A97C && !dword_51A960 )
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
int  Rules_GetInstanceClassName(int a1)
{
  if ( (*(_BYTE *)(a1 + 24) & 2) != 0 )
    return 0;
  else
    return *(_DWORD *)(*(_DWORD *)(a1 + 28) + 16);
}

//----- (004801F0) --------------------------------------------------------
int Rules_GetActiveInstanceCount()
{
  return dword_51AD10;
}
// 51AD10: using guessed type int dword_51AD10;

//----- (00480200) --------------------------------------------------------
int  Rules_GetNextInstance(int a1)
{
  if ( !a1 )
    return dword_51AD0C;
  if ( (*(_BYTE *)(a1 + 24) & 2) != 0 )
    return 0;
  return *(_DWORD *)(a1 + 68);
}
// 51AD0C: using guessed type int dword_51AD0C;

//----- (00480220) --------------------------------------------------------
int  Rules_GetNextInstanceInScope(int a1)
{
  int v1; // ecx
  int v3; // ecx

  if ( !a1 )
  {
    v1 = dword_51AD0C;
    if ( dword_51AD0C )
      goto LABEL_7;
    return 0;
  }
  if ( (*(_BYTE *)(a1 + 24) & 2) != 0 )
    return 0;
  v1 = *(_DWORD *)(a1 + 68);
  if ( !v1 )
    return 0;
LABEL_7:
  while ( !Class_IsInScope(*(_DWORD *)(v1 + 44), 0) )
  {
    v1 = *(_DWORD *)(v3 + 68);
    if ( !v1 )
      return 0;
  }
  return v3;
}
// 48025C: variable 'v3' is possibly undefined
// 51AD0C: using guessed type int dword_51AD0C;

//----- (00480270) --------------------------------------------------------
int  Rules_GetNextInstanceInClass(int a1, int a2)
{
  if ( !a2 )
    return *(_DWORD *)(a1 + 80);
  if ( (*(_BYTE *)(a2 + 24) & 2) != 0 )
    return 0;
  return *(_DWORD *)(a2 + 52);
}

//----- (004802F0) --------------------------------------------------------
int  Rules_ClassCommand(int a1, int a2, double a3)
{
  int v3; // esi
  _DWORD *v4; // eax
  int result; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // [esp-4h] [ebp-24h] BYREF
  int v13; // [esp+0h] [ebp-20h]
  int v14; // [esp+4h] [ebp-1Ch]
  int v15; // [esp+1Ch] [ebp-4h]

  v15 = a2;
  v3 = *(_DWORD *)(**(_DWORD **)(dword_51A960 + 2) + 16);
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = dword_54DD70;
  Parser_ParseForm(*(__int16 **)(dword_51A960 + 6), &v12, a1, a3);
  if ( v13 == 7 )
  {
    v4 = (_DWORD *)v14;
    if ( (*(_BYTE *)(v14 + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      return Lexer_ErrorRecover(1);
    }
LABEL_5:
    result = Rules_GetConstructNameSymbol(v4[11]);
    *(_DWORD *)(v6 + 8) = result;
    return result;
  }
  if ( v13 == 8 )
  {
    v4 = Instance_FindByName(v14);
    if ( !v4 )
      return Instance_ReportNoSuchInstanceError(v8, v3);
    goto LABEL_5;
  }
  switch ( v13 )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      result = Rules_GetConstructNameSymbol(dword_51AD7C[v13]);
      *(_DWORD *)(v7 + 8) = result;
      break;
    default:
      Rules_PrintErrorID((int)aInscom, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUndefinedTypeI, v9);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], v3, v10);
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
  int v3; // eax

  result = MessageHandler_CheckCurrentMessage(a1, 1);
  if ( result )
  {
    v3 = MessageHandler_GetNthArgument(0);
    return Instance_DeleteInstance(*(_DWORD *)(v3 + 8), a2);
  }
  return result;
}

//----- (00480430) --------------------------------------------------------
signed int  Rules_UnmakeInstanceCommand(int a1, double a2)
{
  int v3; // esi
  int v4; // ebx
  int v5; // edi
  _DWORD *v6; // ecx
  int v8; // [esp-4h] [ebp-2Ch] BYREF
  int v9; // [esp+0h] [ebp-28h]
  int v10; // [esp+4h] [ebp-24h]
  int v11; // [esp+20h] [ebp-8h]

  v11 = a1;
  v3 = 1;
  v4 = *(_DWORD *)(dword_51A960 + 6);
  v5 = 1;
  if ( v4 )
  {
    while ( 1 )
    {
      Parser_ParseForm((__int16 *)v4, &v8, a1, a2);
      if ( v9 == 8 || v9 == 2 )
      {
        v6 = Instance_FindByName(v10);
        if ( !v6 && strcmp_(0, asc_5033CC) )
        {
          Instance_ReportNoSuchInstanceError((int)v6, (int)aUnmakeInstance);
          return 0;
        }
      }
      else
      {
        if ( v9 != 7 )
        {
          Parser_ReportError(v3, (int)aInstanceAddr_4);
          Lexer_ErrorRecover(1);
          return 0;
        }
        v6 = (_DWORD *)v10;
        if ( (*(_BYTE *)(v10 + 24) & 2) != 0 )
        {
          Instance_ReportInvalidInstanceAddressError();
          Lexer_ErrorRecover(1);
          return 0;
        }
      }
      if ( !Rules_UnmakeInstance((int)v6, a2) )
        v5 = 0;
      if ( a1 )
      {
        v4 = *(_DWORD *)(v4 + 10);
        ++v3;
        if ( v4 )
          continue;
      }
      return v5;
    }
  }
  return v5;
}
// 480450: variable 'a1' is possibly undefined
// 480478: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A960: using guessed type int dword_51A960;

//----- (00480520) --------------------------------------------------------
signed int  Rules_SymbolToInstanceName(_DWORD *a1, double a2)
{
  signed int result; // eax

  result = Lexer_ParseValueList(1, a1, 2, a2);
  if ( result )
  {
    a1[1] = 8;
  }
  else
  {
    a1[1] = 2;
    result = dword_54DD70;
    a1[2] = dword_54DD70;
  }
  return result;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (00480560) --------------------------------------------------------
int  Rules_InstanceNameToSymbol(int a1, double a2)
{
  _DWORD v4[9]; // [esp-8h] [ebp-24h] BYREF

  v4[7] = a1;
  if ( Lexer_ParseValueList(1, v4, 8, a2) )
    return v4[2];
  else
    return dword_54DD70;
}
// 54DD70: using guessed type int dword_54DD70;

//----- (004805A0) --------------------------------------------------------
_DWORD * Rules_InstanceAddressCommand(int a1, double a2)
{
  _DWORD *result; // eax
  int v4; // ecx
  int *v5; // edi
  int v6; // ebp
  int v7; // eax
  int v8; // ecx
  _DWORD v9[2]; // [esp+0h] [ebp-30h] BYREF
  int v10; // [esp+8h] [ebp-28h]

  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = dword_54DD70;
  if ( Rules_RtnArgCount() <= 1 )
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v9, 112, a2);
    if ( result )
    {
      if ( v9[1] == 7 )
      {
        if ( (*(_BYTE *)(v10 + 24) & 2) != 0 )
        {
          Instance_ReportInvalidInstanceAddressError();
          return (_DWORD *)Lexer_ErrorRecover(1);
        }
        else
        {
          *(_DWORD *)(a1 + 4) = 7;
          result = (_DWORD *)v10;
          *(_DWORD *)(a1 + 8) = v10;
        }
      }
      else
      {
        result = Instance_FindByName(v10);
        if ( !result )
          return (_DWORD *)Instance_ReportNoSuchInstanceError(v8, (int)aInstanceAddres);
        *(_DWORD *)(a1 + 4) = 7;
        *(_DWORD *)(a1 + 8) = result;
      }
    }
  }
  else
  {
    result = (_DWORD *)Lexer_ParseValueList(1, v9, 2, a2);
    if ( result )
    {
      v5 = Module_FindByName(*(_BYTE **)(v10 + 16));
      if ( !v5 && strcmp_(v4, asc_5033CC) )
      {
        Parser_ReportError(1, (int)aModuleName);
        return (_DWORD *)Lexer_ErrorRecover(1);
      }
      if ( v5 )
      {
        v6 = 0;
      }
      else
      {
        v6 = 1;
        v5 = (int *)Module_GetCurrent();
      }
      result = (_DWORD *)Lexer_ParseValueList(2, v9, 8, a2);
      if ( result )
      {
        v7 = Module_GetCurrent();
        result = Instance_LookupInHashBucket(v10, (int)v5, (_DWORD *)v6, v7);
        if ( result )
        {
          *(_DWORD *)(a1 + 4) = 7;
          *(_DWORD *)(a1 + 8) = result;
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
int  Rules_InstanceNameCommand(int a1, int a2, double a3)
{
  int result; // eax
  _DWORD *v5; // edx
  int v6; // ecx
  _DWORD v7[2]; // [esp-4h] [ebp-28h] BYREF
  int v8; // [esp+4h] [ebp-20h]
  int v9; // [esp+1Ch] [ebp-8h]

  v9 = a2;
  *(_DWORD *)(a1 + 4) = 2;
  *(_DWORD *)(a1 + 8) = dword_54DD70;
  result = Lexer_ParseValueList(1, v7, 112, a3);
  if ( result )
  {
    if ( v7[1] == 7 )
    {
      v5 = (_DWORD *)v8;
      if ( (*(_BYTE *)(v8 + 24) & 2) != 0 )
      {
        Instance_ReportInvalidInstanceAddressError();
        return Lexer_ErrorRecover(1);
      }
    }
    else
    {
      v5 = Instance_FindByName(v8);
      if ( !v5 )
        return Instance_ReportNoSuchInstanceError(v6, (int)aInstanceName);
    }
    *(_DWORD *)(a1 + 4) = 8;
    result = v5[7];
    *(_DWORD *)(a1 + 8) = result;
  }
  return result;
}
// 4807D9: variable 'v6' is possibly undefined
// 54DD70: using guessed type int dword_54DD70;

//----- (004807F0) --------------------------------------------------------
BOOL  Rules_InstanceAddressPCommand(int a1, double a2)
{
  _DWORD v3[7]; // [esp-4h] [ebp-1Ch] BYREF

  Parser_ParseForm(*(__int16 **)(dword_51A960 + 6), v3, a1, a2);
  return v3[1] == 7;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480820) --------------------------------------------------------
BOOL  Rules_InstanceNamePCommand(int a1, double a2)
{
  _DWORD v3[7]; // [esp-4h] [ebp-1Ch] BYREF

  Parser_ParseForm(*(__int16 **)(dword_51A960 + 6), v3, a1, a2);
  return v3[1] == 8;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480850) --------------------------------------------------------
BOOL  Rules_InstancePCommand(int a1, double a2)
{
  int v3; // [esp-4h] [ebp-1Ch] BYREF
  int v4; // [esp+0h] [ebp-18h]

  Parser_ParseForm(*(__int16 **)(dword_51A960 + 6), &v3, a1, a2);
  return v4 == 8 || v4 == 7;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480890) --------------------------------------------------------
int  Rules_InstanceExistPCommand(int a1, double a2)
{
  int result; // eax
  int v3; // [esp-4h] [ebp-1Ch] BYREF
  int v4; // [esp+0h] [ebp-18h]
  int v5; // [esp+4h] [ebp-14h]

  Parser_ParseForm(*(__int16 **)(dword_51A960 + 6), &v3, a1, a2);
  if ( v4 == 7 )
  {
    LOBYTE(result) = (*(_BYTE *)(v5 + 24) & 2) == 0;
    return (unsigned __int8)result;
  }
  if ( v4 == 8 || v4 == 2 )
  {
    LOBYTE(result) = Instance_FindByName(v5) != 0;
    return (unsigned __int8)result;
  }
  Parser_ReportError(1, (int)aInstanceNameIn);
  Lexer_ErrorRecover(1);
  return 0;
}
// 51A960: using guessed type int dword_51A960;

//----- (00480910) --------------------------------------------------------
int  Rules_ListInstancesForClassOrModule(signed int a1, int a2, int a3, int a4)
{
  int v5; // edi
  int i; // esi
  int v8; // esi
  int v9; // ecx
  _BYTE *v10; // edx
  int v11; // ecx
  int *v12; // eax
  int v13; // ecx

  v5 = 0;
  if ( a3 )
  {
    Module_GetCurrent();
    v12 = Class_LookupByModule(v11, v10);
    if ( v12 )
      return Rules_ListInstancesOfClassRecursive(a1, a2, v13, (int)v12, a4);
    if ( !a4 )
    {
      Class_ReportLookupError(v13, a3);
      return 0;
    }
    return v5;
  }
  if ( a4 )
  {
    for ( i = Class_GetNextRecord(0); i; i = Class_GetNextRecord(i) )
      v5 += Rules_ListInstancesOfClassRecursive(a1, a2, 0, i, a4);
    return v5;
  }
  v8 = Rules_GetNextInstanceInScope(0);
  if ( !v8 )
    return v5;
  v9 = 1;
  do
  {
    Instance_PrintNameOfClass(a2, v8, v9);
    ++v5;
    v8 = Rules_GetNextInstanceInScope(v8);
  }
  while ( v8 );
  return v5;
}
// 480983: variable 'v9' is possibly undefined
// 4809A8: variable 'v11' is possibly undefined
// 4809A8: variable 'v10' is possibly undefined
// 4809BF: variable 'v13' is possibly undefined

//----- (004809F0) --------------------------------------------------------
int  Rules_ListInstancesOfClassRecursive(signed int a1, int a2, int a3, int a4, int a5)
{
  int v6; // ebx
  int v7; // eax
  int v8; // edi
  int v9; // ecx
  int v10; // ecx
  int v11; // ebp
  unsigned int i; // [esp+Ch] [ebp-10h]

  v6 = ((a1 - (__CFSHL__(a1 >> 31, 3) + 8 * (a1 >> 31))) >> 3) + a4;
  v7 = 1 << (a1 % 8);
  v8 = 0;
  if ( ((unsigned __int8)v7 & *(_BYTE *)(v6 + 108)) != 0 )
    return 0;
  *(_BYTE *)(v6 + 108) |= v7;
  v9 = *(_DWORD *)(a4 + 80);
  if ( v9 )
  {
    while ( !dword_51A968 )
    {
      if ( a5 )
        Output_Write(a2, (int)asc_5034F8, v9);
      Instance_PrintNameOfClass(a2, v9, 1);
      v9 = *(_DWORD *)(v10 + 52);
      ++v8;
      if ( !v9 )
        goto LABEL_7;
    }
  }
  else
  {
LABEL_7:
    if ( a3 )
    {
      v11 = 0;
      for ( i = 0; *(unsigned __int16 *)(a4 + 40) > i && !dword_51A968; ++i )
      {
        v8 += Rules_ListInstancesOfClassRecursive(a1, a2, a3, *(_DWORD *)(*(_DWORD *)(a4 + 42) + v11), a5);
        v11 += 4;
      }
    }
  }
  return v8;
}
// 480A76: variable 'v9' is possibly undefined
// 480A7B: variable 'v10' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (00480AF0) --------------------------------------------------------
signed int  Rules_PrintInstanceSlots(int a1, int a2, int a3)
{
  signed int result; // eax
  unsigned int v5; // edi
  int v6; // ebp
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  result = Instance_PrintNameOfClass(a1, a2, 0);
  v5 = 0;
  v6 = 0;
  while ( v5 < *(_DWORD *)(*(_DWORD *)(a2 + 44) + 72) )
  {
    Output_Write(a1, a3, a2);
    Output_Write(a1, (int)asc_5034FC, *(_DWORD *)(*(_DWORD *)(v7 + 72) + v6));
    Output_Write(a1, *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v8 + 8) + 12) + 16), v8);
    if ( (*(_DWORD *)(v9 + 4) & 0xFC) == 0x10 )
    {
      if ( *(_DWORD *)(*(_DWORD *)(v9 + 8) + 6) )
      {
        Output_Write(a1, (int)asc_503458, v9);
        Lexer_OutputFieldRange(a1, *(_DWORD *)(v11 + 8), *(_DWORD *)(*(_DWORD *)(v11 + 8) + 6) - 1, 0, 0);
      }
    }
    else
    {
      Output_Write(a1, (int)asc_503458, v9);
      Rules_PrintAtomValue(a1, *(_DWORD *)(v10 + 4) << 24 >> 26, *(int **)(v10 + 8));
    }
    result = Output_Write(a1, (int)asc_503500, v9);
    v6 += 4;
    ++v5;
  }
  return result;
}
// 480B2D: variable 'v7' is possibly undefined
// 480B3F: variable 'v8' is possibly undefined
// 480B51: variable 'v9' is possibly undefined
// 480B6B: variable 'v10' is possibly undefined
// 480BA8: variable 'v11' is possibly undefined

//----- (00480BC0) --------------------------------------------------------
int *__fastcall Rules_FindInstanceSlot(int a1, _BYTE *a2)
{
  int *result; // eax

  result = Rules_FindSymbolEntry(a2);
  if ( result )
    return (int *)Instance_GetSlotValueBySymbol(a1, (int)(uintptr_t)result);
  return result;
}

//----- (00480BE0) --------------------------------------------------------
signed int  Rules_RegisterHostFunctionNoRestrictions(char *a1, int a2, int a3, int a4)
{
  return Rules_RegisterHostFunction(a1, a2, a3, a4, 0);
}

//----- (00480BF0) --------------------------------------------------------
signed int  Rules_RegisterHostFunction(
        char *a1,
        int a2,
        int a3,
        int a4,
        int a5)
{
  int host_function_ptr; // ebx
  _DWORD *free_node; // eax
  signed int *symbol; // eax
  int symbol_ptr; // eax
  int argument_spec_len; // eax

  if ( a2 != 97
    && a2 != 98
    && a2 != 99
    && a2 != 100
    && a2 != 102
    && a2 != 105
    && a2 != 106
    && a2 != 107
    && a2 != 108
    && a2 != 109
    && a2 != 110
    && a2 != 111
    && a2 != 115
    && a2 != 117
    && a2 != 118
    && a2 != 120
    && a2 != 119 )
  {
    return 0;
  }
  free_node = *(_DWORD **)(dword_54DBA8 + 124);
  if ( free_node )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 124);
    *(_DWORD *)(dword_54DBA8 + 124) = *free_node;
    host_function_ptr = dword_54DBAC;
  }
  else
  {
    host_function_ptr = Mem_HeapAllocWithRetry((_DWORD *)0x1F);
  }
  symbol = Str_Intern(a1, host_function_ptr);
  *(_DWORD *)(host_function_ptr + 0) = symbol;
  *(_BYTE *)(host_function_ptr + 8) = a2;
  *(_DWORD *)(host_function_ptr + 9) = a4;
  *(_DWORD *)(host_function_ptr + 27) = g_Rules_HostFunctionListHead;
  *(_DWORD *)(host_function_ptr + 4) = a3;
  if ( a5
    && ((argument_spec_len = strlen((const char *)a5), argument_spec_len < 2)
     || (IsTable[(unsigned __int8)(*(_BYTE *)a5 + 1)] & 0x20) == 0 && *(_BYTE *)a5 != 42
     || (IsTable[(unsigned __int8)(*(_BYTE *)(a5 + 1) + 1)] & 0x20) == 0 && *(_BYTE *)(a5 + 1) != 42) )
  {
    a5 = 0;
  }
  *(_DWORD *)(host_function_ptr + 13) = 0;
  *(_WORD *)(host_function_ptr + 21) = 1;
  *(_WORD *)(host_function_ptr + 23) = 1;
  symbol_ptr = *(_DWORD *)(host_function_ptr + 0);
  *(_DWORD *)(host_function_ptr + 17) = a5;
  ++*(_DWORD *)(symbol_ptr + 4);
  g_Rules_HostFunctionListHead = host_function_ptr;
  Rules_InsertFunctionHashEntry(host_function_ptr);
  return 1;
}
// 51A264: using guessed type int dword_51A264;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00480D60) --------------------------------------------------------
signed int  Rules_AddFunctionParser(_BYTE *a1)
{
  int **Symbol; // eax
  int *v2; // edx
  int v3; // ecx

  Symbol = Rules_MakeSymbol(a1);
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
signed int  Rules_SetFunctionSeqOverloadFlags(_BYTE *a1, int a2)
{
  int **Symbol; // eax
  int v3; // edx

  Symbol = Rules_MakeSymbol(a1);
  if ( Symbol )
  {
    *(_WORD *)((char *)Symbol + 23) = v3 != 0;
    *(_WORD *)((char *)Symbol + 21) = a2 != 0;
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
char * Rules_GetArgTypeName(char a1)
{
  char *result; // eax

  switch ( a1 )
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
signed int  Rules_GetArgRestrictionType(int a1, int a2)
{
  signed int result; // eax
  unsigned int v4; // kr04_4

  if ( !a1 )
    return 117;
  if ( !*(_DWORD *)(a1 + 17) )
    return 117;
  v4 = strlen(*(const char **)(a1 + 17)) + 1;
  if ( (int)(v4 - 1) < 3 )
    return 117;
  result = *(unsigned __int8 *)(*(_DWORD *)(a1 + 17) + 2);
  if ( result == 42 )
    result = 117;
  if ( (int)(v4 - 1) >= a2 + 3 )
    return *(unsigned __int8 *)(a2 + *(_DWORD *)(a1 + 17) + 2);
  return result;
}

//----- (00480F70) --------------------------------------------------------
int Rules_GetFunctionDefinitionListHead()
{
  return g_Rules_HostFunctionListHead;
}
// 51A264: using guessed type int dword_51A264;

//----- (00481010) --------------------------------------------------------
int ** Rules_MakeSymbol(_BYTE *a1)
{
  int hash_bucket; // edx
  int interned_name; // ecx
  int bucket_entry; // eax
  int symbol; // edx

  hash_bucket = Rules_HashSymbolName(a1, 0x33u);
  interned_name = (int)Rules_FindSymbolEntry((int)a1);
  bucket_entry = *(_DWORD *)(dword_54DD40 + 4 * hash_bucket);
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

  dword_54DD40 = (int)Mem_SmallBlockAlloc(0xCCu);
  for ( result = 0; result != 204; result += 4 )
    *(_DWORD *)(dword_54DD40 + result) = 0;
  return result;
}
// 54DD40: using guessed type int dword_54DD40;

//----- (00481090) --------------------------------------------------------
int * Rules_InsertFunctionHashEntry(int a1)
{
  _DWORD *free_node; // ebx
  int *bucket_head_ptr; // eax
  int existing_head; // edx
  int host_function_ptr; // ecx
  int symbol_record; // eax
  int symbol_name; // eax

  if ( !dword_54DD40 )
    Rules_InitFunctionNameHashTable();
  free_node = *(_DWORD **)(dword_54DBA8 + 32);
  if ( free_node )
  {
    dword_54DBAC = (int)free_node;
    *(_DWORD *)(dword_54DBA8 + 32) = *free_node;
    host_function_ptr = dword_54DBAC;
  }
  else
  {
    host_function_ptr = Mem_HeapAllocWithRetry((_DWORD *)8);
  }
  *(_DWORD *)(host_function_ptr + 0) = a1;
  symbol_record = *(_DWORD *)(uintptr_t)(unsigned int)a1;
  symbol_name = *(_DWORD *)((uintptr_t)(unsigned int)symbol_record + 16);
  bucket_head_ptr = (int *)(dword_54DD40
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
int  Rules_RtnLexeme(int a1, int a2, double a3)
{
  int v5; // eax
  int i; // edx
  int v8; // [esp-4h] [ebp-20h] BYREF
  int v9; // [esp+0h] [ebp-1Ch]
  int v10; // [esp+4h] [ebp-18h]

  v5 = *(_DWORD *)(dword_51A960 + 6);
  for ( i = 1; v5; ++i )
  {
    if ( i >= a1 )
      break;
    v5 = *(_DWORD *)(v5 + 10);
  }
  if ( v5 )
  {
    Parser_ParseForm((__int16 *)v5, &v8, a2, a3);
    if ( v9 == 2 || v9 == 8 || v9 == 3 )
    {
      return *(_DWORD *)(v10 + 16);
    }
    else
    {
      Rules_ExpectedTypeError((int)aRtnlexeme, *(_DWORD *)(**(_DWORD **)(dword_51A960 + 2) + 16), a1);
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD **)(dword_51A960 + 2) + 16), a1);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return 0;
  }
}
// 51A960: using guessed type int dword_51A960;

//----- (004811C0) --------------------------------------------------------
double  Rules_RtnDouble(int a1, int a2, double a3)
{
  int v4; // eax
  int i; // edx
  int v7; // eax
  int v8; // [esp+0h] [ebp-30h] BYREF
  int v9; // [esp+4h] [ebp-2Ch]
  int v10; // [esp+8h] [ebp-28h]
  double v11; // [esp+18h] [ebp-18h]

  v4 = *(_DWORD *)(dword_51A960 + 6);
  for ( i = 1; v4; ++i )
  {
    if ( i >= a1 )
      break;
    v4 = *(_DWORD *)(v4 + 10);
  }
  if ( !v4 )
  {
    Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD **)(dword_51A960 + 2) + 16), a1);
    v11 = 1.0;
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return v11;
  }
  Parser_ParseForm((__int16 *)v4, &v8, a2, a3);
  if ( !v9 )
  {
    v7 = *(_DWORD *)(v10 + 20);
    LODWORD(v11) = *(_DWORD *)(v10 + 16);
    HIDWORD(v11) = v7;
    return v11;
  }
  if ( v9 == 1 )
    return (double)*(int *)(v10 + 16);
  Rules_ExpectedTypeError((int)aRtndouble, *(_DWORD *)(**(_DWORD **)(dword_51A960 + 2) + 16), a1);
  HIDWORD(v11) = 1072693248;
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  LODWORD(v11) = 0;
  return v11;
}
// 51A960: using guessed type int dword_51A960;

//----- (004812C0) --------------------------------------------------------
signed int  Rules_RtnLong(int a1, int a2, double a3)
{
  uintptr_t expression; // eax
  uintptr_t current; // eax
  int i; // edx
  uintptr_t function_node; // edx
  uintptr_t function_symbol; // edx
  _DWORD parsed[6]; // [esp+0h] [ebp-28h] BYREF

  expression = (uintptr_t)(unsigned int)dword_51A960;
  current = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 6) : 0;
  for ( i = 1; current; ++i )
  {
    if ( i >= a1 )
      break;
    current = (uintptr_t)(unsigned int)*(_DWORD *)(current + 10);
  }
  if ( !current )
  {
    function_node = expression ? (uintptr_t)(unsigned int)*(_DWORD *)(expression + 2) : 0;
    function_symbol = function_node ? (uintptr_t)(unsigned int)*(_DWORD *)function_node : 0;
    Rules_NonexistentArgError(function_symbol ? *(_DWORD *)(function_symbol + 16) : 0, a1);
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
  Rules_ExpectedTypeError((int)aRtnlong, function_symbol ? *(_DWORD *)(function_symbol + 16) : 0, a1);
  Rules_SetEvaluationErrorFlag(1);
  Lexer_ErrorRecover(1);
  return 1;
}
// 51A960: using guessed type int dword_51A960;

//----- (004813B0) --------------------------------------------------------
int  Rules_RtnUnknown(int a1, _DWORD *a2, double a3)
{
  int v5; // eax
  int i; // edx
  int v8; // ecx

  v5 = *(_DWORD *)(dword_51A960 + 6);
  for ( i = 1; v5; ++i )
  {
    if ( i >= a1 )
      break;
    v5 = *(_DWORD *)(v5 + 10);
  }
  if ( v5 )
  {
    Parser_ParseForm((__int16 *)v5, a2, (int)a2, a3);
    return v8;
  }
  else
  {
    Rules_NonexistentArgError(*(_DWORD *)(**(_DWORD **)(dword_51A960 + 2) + 16), a1);
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
  int v0; // eax
  int i; // edx

  v0 = *(_DWORD *)(dword_51A960 + 6);
  for ( i = 0; v0; ++i )
    v0 = *(_DWORD *)(v0 + 10);
  return i;
}
// 51A960: using guessed type int dword_51A960;

//----- (00481450) --------------------------------------------------------
int Lexer_TokenExpect(int a1)
{
  int result; // eax
  int v2; // edx
  int v3; // ecx

  result = Rules_RtnArgCount();
  if ( !v2 )
  {
    if ( result == a1 )
      return result;
LABEL_9:
    Rules_ExpectedCountError(v3, a1);
    Rules_SetEvaluationErrorFlag(1);
    Lexer_ErrorRecover(1);
    return -1;
  }
  if ( v2 == 1 )
  {
    if ( result < a1 )
      goto LABEL_9;
  }
  else if ( v2 != 2 || result > a1 )
  {
    goto LABEL_9;
  }
  return result;
}
// 48145A: variable 'v2' is possibly undefined
// 481478: variable 'v3' is possibly undefined

//----- (004814A0) --------------------------------------------------------
int  Rules_ArgRangeCheck(int a1, int a2)
{
  int result; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  result = Rules_RtnArgCount();
  if ( result < v4 || result > a2 )
  {
    Rules_PrintErrorID((int)aArgacces, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFunction, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], a1, v6);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aExpectedAtLeas, v7);
    Rules_PrintLongInteger(v8, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAndNoMoreThan, v9);
    Rules_PrintLongInteger(v10, a2);
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

