/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004866CC) --------------------------------------------------------
char * CRT_DetachThreadDataAndMaybeCloseHandle(char *result)
{
  char *closeHandleFlag; // ebx
  void *threadHandle; // esi

  closeHandleFlag = result;
  if ( dwTlsIndex != -1 )
  {
    result = (char *)TlsGetValue(dwTlsIndex);
    if ( result )
    {
      threadHandle = *(void **)(result + 222);
      _RemoveThreadData_();
      result = (char *)(uintptr_t)TlsSetValue(dwTlsIndex, 0);
      if ( threadHandle )
      {
        if ( closeHandleFlag )
          return (char *)(uintptr_t)CloseHandle(threadHandle);
      }
    }
  }
  return result;
}
// 4B583C: using guessed type int _RemoveThreadData_(void);

//----- (00486721) --------------------------------------------------------
char *CRT_DestroyTlsIndexAndThreadData(void)
{
  char *result; // eax

  result = CRT_DetachThreadDataAndMaybeCloseHandle((char *)1);
  if ( dwTlsIndex != -1 )
  {
    result = (char *)(uintptr_t)TlsFree(dwTlsIndex);
    dwTlsIndex = -1;
  }
  return result;
}

//----- (0048674D) --------------------------------------------------------
void CRT_InitializeThreadAndFileHandleHooks(void)
{
  g_CRT_FileHandleLockAcquireHook = (int (__thiscall *)(_DWORD))CRT_AcquireFileHandleLock;
  g_CRT_FileHandleLockReleaseHook = (int (__fastcall *)(_DWORD, _DWORD))CRT_ReleaseFileHandleLock;
  g_CRT_AddFileHandleHook = j___NTAddFileHandle__0;
  g_CRT_FileHandleRemoveHookTable[0] = (int (*)())CRT_ReleaseAndUnregisterFileHandle;
  g_CRT_StaticLock1AcquireHook = (_DWORD (*)())CRT_AcquireStaticLock1;
  g_CRT_StaticLock1ReleaseHook = (_DWORD (*)())CRT_ReleaseStaticLock1;
  g_CRT_StaticLock4AcquireHookTable[0] = (int (*)())CRT_AcquireStaticLock4;
  g_CRT_StaticLock4ReleaseHookTable[0] = (int (*)())CRT_ReleaseStaticLock4;
  g_CRT_LockEnterHookTable[0] = (int (*)())CRT_LockEnter;
  g_CRT_LockLeaveHookTable[0] = (int (*)())CRT_LockLeave;
  g_CRT_LockSlotResetHook = (int (__fastcall *)(_DWORD, _DWORD))CRT_ResetLockSlot;
  g_CRT_StaticLock2AcquireHook = (_DWORD (*)())CRT_AcquireStaticLock2;
  g_CRT_StaticLock3AcquireHookTable[0] = (int (*)())CRT_AcquireStaticLock3;
  g_CRT_StaticLock2ReleaseHook = (_DWORD (*)())CRT_ReleaseStaticLock2;
  g_CRT_StaticLock3ReleaseHookTable[0] = (int (*)())CRT_ReleaseStaticLock3;
  g_CRT_LockInitCriticalSection = (int)(intptr_t)CRT_AllocateLockSlot(CRT_LockLeave);
  InitializeCriticalSection((LPCRITICAL_SECTION)(uintptr_t)g_CRT_LockInitCriticalSection);
  g_CRT_ThreadLockSystemInitialized = 1;
  g_CRT_ThreadDataDestroyHookTable[0] = CRT_DestroyThreadDataBlock;
  g_CRT_TlsIndexDestroyHook = (_DWORD (*)())CRT_DestroyTlsIndexAndThreadData;
  g_CRT_ThreadDataConstructHookTable[0] = CRT_ConstructThreadDataBlock;
  _AddThreadData_(CRT_ConstructThreadDataBlock, lpTlsValue);
  TlsSetValue(dwTlsIndex, lpTlsValue);
  g_CrtThreadDataAccessor = (__int64 (__fastcall *)(_DWORD, _DWORD))CRT_GetOrCreateThreadDataPreserveLastError;
  return;
}
// 4864C7: using guessed type int j___NTAddFileHandle__0();
// 486518: using guessed type int sub_486518();
// 48657E: using guessed type int sub_48657E();
// 4B57DB: using guessed type int __fastcall _AddThreadData_(_DWORD, _DWORD);
// 51A568: using guessed type __int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A56C: using guessed type int (__thiscall *off_51A56C)(_DWORD);
// 51A570: using guessed type int (__fastcall *off_51A570)(_DWORD, _DWORD);
// 51A574: using guessed type _DWORD (*off_51A574)();
// 51A578: using guessed type int (*off_51A578[14])();
// 51A57C: using guessed type _DWORD (*off_51A57C)();
// 51A580: using guessed type _DWORD (*off_51A580)();
// 51A584: using guessed type _DWORD (*off_51A584)();
// 51A588: using guessed type int (*off_51A588[10])();
// 51A58C: using guessed type _DWORD (*off_51A58C)();
// 51A590: using guessed type int (*off_51A590[8])();
// 51A594: using guessed type int (*off_51A594[7])();
// 51A598: using guessed type int (*off_51A598[6])();
// 51A59C: using guessed type int (*off_51A59C[5])();
// 51A5A0: using guessed type int (*off_51A5A0[4])();
// 51A5A4: using guessed type _DWORD (*off_51A5A4)();
// 51A62C: using guessed type int (*off_51A62C[3])();
// 51A630: using guessed type int (*off_51A630[2])();
// 51A634: using guessed type int (__fastcall *off_51A634)(_DWORD, _DWORD);
// 54DECC: using guessed type int dword_54DECC;
// 54DED0: using guessed type int dword_54DED0;

//----- (00486869) --------------------------------------------------------
int __thiscall CRT_ShutdownThreadAndFileHandleHooks(void *this)
{
  int v1; // edx
  int v2; // ecx
  int v3; // ebx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // edx
  int v11; // ecx

  g_CRT_LockSlotResetHook(this, &g_CRT_FileHandleLockSlots);
  v3 = v1 + 256;
  do
    g_CRT_LockSlotResetHook(v2, v1 + 16);
  while ( v1 != v3 );
  g_CRT_LockSlotResetHook(v2, v1);
  j___FreeThreadDataList_();
  g_CRT_LockSlotResetHook(v5, v4);
  g_CRT_LockSlotResetHook(v7, v6);
  g_CRT_LockSlotResetHook(v9, v8);
  g_CRT_LockSlotResetHook(v11, v10);
  return CRT_FreeTlsIndex();
}
// 48687B: variable 'v1' is possibly undefined
// 486886: variable 'v2' is possibly undefined
// 4868A5: variable 'v5' is possibly undefined
// 4868A5: variable 'v4' is possibly undefined
// 4868B0: variable 'v7' is possibly undefined
// 4868B0: variable 'v6' is possibly undefined
// 4868BB: variable 'v9' is possibly undefined
// 4868BB: variable 'v8' is possibly undefined
// 4868C6: variable 'v11' is possibly undefined
// 4868C6: variable 'v10' is possibly undefined
// 48672B: using guessed type _DWORD loc_48672B();
// 4B58FA: using guessed type int j___FreeThreadDataList_(void);
// 51A634: using guessed type int (__fastcall *off_51A634)(_DWORD, _DWORD);

//----- (004869F0) --------------------------------------------------------
int  Surface_DDCopyBitmapToNewSurface(int directDraw, const CHAR *bitmapName, _DWORD *heightOut, int widthOut)
{
  HMODULE ModuleHandleA; // eax
  HANDLE ImageA; // esi
  int v9; // ecx
  _DWORD *width_ptr; // esi
  void *image_handle; // [esp+4h] [ebp-A0h]
  _DWORD surface_desc[2]; // [esp+8h] [ebp-9Ch] BYREF
  int surface_height; // [esp+10h] [ebp-94h]
  int surface_width; // [esp+14h] [ebp-90h]
  int surface_caps CLASH95_UNUSED; // [esp+70h] [ebp-34h]
  _BYTE pv[4]; // [esp+74h] [ebp-30h] BYREF
  int bitmap_width; // [esp+78h] [ebp-2Ch]
  int bitmap_height; // [esp+7Ch] [ebp-28h]
  int new_surface; // [esp+8Ch] [ebp-18h] BYREF
  int v21; // [esp+90h] [ebp-14h]
  _DWORD *height_ptr; // [esp+94h] [ebp-10h]

  v21 = widthOut;
  height_ptr = heightOut;
  ModuleHandleA = GetModuleHandleA(0);
  ImageA = LoadImageA(ModuleHandleA, bitmapName, 0, 0, 0, 0x2000u);
  if ( !ImageA )
  {
    ImageA = LoadImageA(0, bitmapName, 0, 0, 0, 0x2010u);
    if ( !ImageA )
      return 0;
  }
  GetObjectA(ImageA, 24, pv);
  memset_(7, 0);
  surface_width = bitmap_width;
  surface_desc[1] = v9;
  surface_height = bitmap_height;
  surface_desc[0] = 108;
  surface_caps = 64;
  if ( (*(int (__stdcall **)(int, _DWORD *, int *, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)directDraw + 24))(directDraw, surface_desc, &new_surface, 0) )
    return 0;
  Surface_DDCopyBitmap(new_surface, ImageA, 0, 0, 0, 0);
  image_handle = ImageA;
  width_ptr = (_DWORD *)(uintptr_t)v21;
  DeleteObject(image_handle);
  *width_ptr = surface_width;
  *height_ptr = surface_height;
  return new_surface;
}
// 486A9B: variable 'v9' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (00486B10) --------------------------------------------------------
signed int  Surface_DDCopyBitmapFromFile(int surface, const CHAR *bitmapName)
{
  HMODULE ModuleHandleA; // eax
  HANDLE ImageA; // esi
  signed int copyResult; // ebx

  ModuleHandleA = GetModuleHandleA(0);
  ImageA = LoadImageA(ModuleHandleA, bitmapName, 0, 0, 0, 0x2000u);
  if ( !ImageA )
    ImageA = LoadImageA(0, bitmapName, 0, 0, 0, 0x2010u);
  if ( ImageA )
  {
    copyResult = Surface_DDCopyBitmap(surface, ImageA, 0, 0, 0, 0);
    if ( copyResult )
      OutputDebugStringA(aDdcopybitmapFa);
    DeleteObject(ImageA);
    return copyResult;
  }
  else
  {
    OutputDebugStringA(aHandleIsNull);
    return -2147467259;
  }
}

//----- (00486BA0) --------------------------------------------------------
signed int  Surface_DDCopyBitmap(int surface, void *bitmap, int x, int y, int dx, int dy)
{
  HDC CompatibleDC; // ebx
  int copy_width; // eax
  int copy_height; // edi
  _DWORD surface_desc[27]; // [esp+Ch] [ebp-A0h] BYREF
  _BYTE pv[4]; // [esp+78h] [ebp-34h] BYREF
  int bitmap_width; // [esp+7Ch] [ebp-30h]
  int hSrc; // [esp+80h] [ebp-2Ch]
  HDC hdcDest; // [esp+90h] [ebp-1Ch] BYREF
  int hr; // [esp+94h] [ebp-18h]
  int ySrc; // [esp+98h] [ebp-14h]
  int wSrc; // [esp+9Ch] [ebp-10h]

  ySrc = x;
  if ( !bitmap || !surface )
    return -2147467259;
  (*(void (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 108))(surface);
  CompatibleDC = CreateCompatibleDC(0);
  if ( !CompatibleDC )
    OutputDebugStringA(OutputString);
  SelectObject(CompatibleDC, bitmap);
  GetObjectA(bitmap, 24, pv);
  if ( dx )
    copy_width = dx;
  else
    copy_width = bitmap_width;
  wSrc = copy_width;
  if ( dy )
    copy_height = dy;
  else
    copy_height = hSrc;
  surface_desc[0] = 108;
  surface_desc[1] = 6;
  (*(void (__stdcall **)(int, _DWORD *))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 88))(surface, surface_desc);
  hr = (*(int (__stdcall **)(int, HDC *))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 68))(surface, &hdcDest);
  if ( !hr )
  {
    StretchBlt(hdcDest, 0, 0, surface_desc[3], surface_desc[2], CompatibleDC, y, ySrc, wSrc, copy_height, 0xCC0020u);
    (*(void (__stdcall **)(int, HDC))(uintptr_t)(*(_DWORD *)(uintptr_t)surface + 104))(surface, hdcDest);
  }
  DeleteDC(CompatibleDC);
  return hr;
}

//----- (00486CE0) --------------------------------------------------------
int  Surface_BuildPaletteFromBitmap(int pdd, const CHAR *bitmapName)
{
  int colorIndex; // ebx
  int byteOffset; // ecx
  __int64 v6; // rtt
  HRSRC ResourceA; // eax
  HGLOBAL Resource; // eax
  _DWORD *bitmapInfo; // esi
  _BYTE *rgbQuads; // edx
  int colorCount; // esi
  int copyIndex; // ecx
  _BYTE *quadPtr; // eax
  unsigned __int16 bitCount; // ax
  HFILE fileHandle; // ebx
  int fileColorCount; // esi
  int swapIndex; // eax
  char swapTemp; // dl
  _BYTE v20[4]; // [esp+0h] [ebp-458h]
  char paletteEntries[1024]; // [esp+4h] [ebp-454h] BYREF
  _DWORD bmpHeader[3]; // [esp+404h] [ebp-54h] BYREF
  unsigned __int16 biBitCount; // [esp+412h] [ebp-46h]
  int biClrUsed; // [esp+424h] [ebp-34h]
  _BYTE Buffer[16]; // [esp+42Ch] [ebp-2Ch] BYREF
  int ddPalette; // [esp+43Ch] [ebp-1Ch] BYREF
  int v27; // [esp+440h] [ebp-18h]

  colorIndex = 0;
  byteOffset = 0;
  do
  {
    paletteEntries[byteOffset] = 255 * ((colorIndex >> 5) & 7) / 7;
    v27 = 3;
    paletteEntries[byteOffset + 1] = 255 * ((colorIndex >> 2) & 7) / 7;
    LODWORD(v6) = 255 * (colorIndex & 3);
    HIDWORD(v6) = (colorIndex & 3u) / 0x808081;
    byteOffset += 4;
    v20[byteOffset + 2] = v6 / v27;
    ++colorIndex;
    v20[byteOffset + 3] = 0;
  }
  while ( colorIndex < 256 );
  if ( bitmapName && (ResourceA = FindResourceA(0, bitmapName, (LPCSTR)2)) != 0 )
  {
    Resource = LoadResource(0, ResourceA);
    bitmapInfo = LockResource(Resource);
    if ( !bitmapInfo )
      OutputDebugStringA(aLockResourceFa);
    rgbQuads = (char *)bitmapInfo + *bitmapInfo;
    if ( *bitmapInfo < 0x28u || (bitCount = *((_WORD *)bitmapInfo + 7), bitCount > 8u) )
    {
      colorCount = 0;
    }
    else if ( bitmapInfo[8] )
    {
      colorCount = bitmapInfo[8];
    }
    else
    {
      colorCount = 1 << bitCount;
    }
    copyIndex = 0;
    if ( colorCount > 0 )
    {
      quadPtr = rgbQuads;
      do
      {
        paletteEntries[4 * copyIndex] = quadPtr[2];
        paletteEntries[4 * copyIndex++ + 1] = quadPtr[1];
        v20[4 * copyIndex + 2] = *quadPtr;
        quadPtr += 4;
        v20[4 * copyIndex + 3] = 0;
      }
      while ( copyIndex < colorCount );
    }
  }
  else if ( bitmapName )
  {
    fileHandle = lopen(bitmapName, 0);
    if ( fileHandle != -1 )
    {
      lread(fileHandle, Buffer, 0xEu);
      lread(fileHandle, bmpHeader, 0x28u);
      lread(fileHandle, paletteEntries, 0x400u);
      lclose(fileHandle);
      if ( bmpHeader[0] == 40 && biBitCount <= 8u )
        fileColorCount = biClrUsed ? biClrUsed : 1 << biBitCount;
      else
        fileColorCount = 0;
      if ( fileColorCount > 0 )
      {
        swapIndex = 0;
        do
        {
          swapIndex += 4;
          swapTemp = v20[swapIndex];
          v20[swapIndex] = v20[swapIndex + 2];
          v20[swapIndex + 2] = swapTemp;
        }
        while ( swapIndex < 4 * fileColorCount );
      }
    }
  }
  (*(void (__stdcall **)(int, int, char *, int *, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)pdd + 20))(pdd, 4, paletteEntries, &ddPalette, 0);
  return ddPalette;
}
// 486CE0: too many cbuild loops

//----- (00486F00) --------------------------------------------------------
int  Surface_MatchColorToNativePixel(int pdds, COLORREF rgb, COLORREF Pixel)
{
  int matchedPixel; // esi
  int hres; // eax
  _DWORD surfaceDesc[21]; // [esp+0h] [ebp-84h] BYREF
  char rgbBitCount; // [esp+54h] [ebp-30h]
  HDC hdc[6]; // [esp+6Ch] [ebp-18h] BYREF

  matchedPixel = -1;
  if ( rgb != -1 && !(*(int (__stdcall **)(int, HDC *))(uintptr_t)(*(_DWORD *)(uintptr_t)pdds + 68))(pdds, hdc) )
  {
    Pixel = GetPixel(hdc[0], 0, 0);
    SetPixel(hdc[0], 0, 0, rgb);
    (*(void (__stdcall **)(int, HDC))(uintptr_t)(*(_DWORD *)(uintptr_t)pdds + 104))(pdds, hdc[0]);
  }
  surfaceDesc[0] = 108;
  do
    hres = (*(int (__stdcall **)(int, _DWORD, _DWORD *, _DWORD, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)pdds + 100))(pdds, 0, surfaceDesc, 0, 0);
  while ( hres == -2005532132 );
  if ( !hres )
  {
    matchedPixel = ((1 << rgbBitCount) - 1) & *(_DWORD *)(uintptr_t)surfaceDesc[9];
    (*(void (__stdcall **)(int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)pdds + 128))(pdds, 0);
  }
  if ( rgb == -1 || (*(int (__stdcall **)(int, HDC *))(uintptr_t)(*(_DWORD *)(uintptr_t)pdds + 68))(pdds, hdc) )
    return matchedPixel;
  SetPixel(hdc[0], 0, 0, Pixel);
  (*(void (__stdcall **)(int, HDC))(uintptr_t)(*(_DWORD *)(uintptr_t)pdds + 104))(pdds, hdc[0]);
  return matchedPixel;
}

//----- (00487002) --------------------------------------------------------
int __fastcall CRT_RunRegisteredFinalizers(int a1 CLASH95_UNUSED, __lock *lock)
{
  int result; // eax
  int finalizerEntry; // edx
  __lock *v4; // [esp-8h] [ebp-8h]
  __lock *v5; // [esp-8h] [ebp-8h]

  v4 = lock;
  while ( 1 )
  {
    __lock_p(v4);
    if ( g_CrtFinalizerListHead )
      g_CrtFinalizerListHead = *(_DWORD *)(uintptr_t)g_CrtFinalizerListHead;
    __lock_v(v5);
    if ( !finalizerEntry )
      break;
    (*(void (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)(finalizerEntry + 4) + 4))();
  }
  return result;
}
// 487009: variable 'v4' is possibly undefined
// 487024: variable 'v5' is possibly undefined
// 48702B: variable 'v3' is possibly undefined
// 51A648: using guessed type int g_CrtFinalizerListHead;

//----- (0048703D) --------------------------------------------------------
int  CRT_RegisterFinalizer(int a1, __lock *lock, int a3)
{
  _DWORD *newEntry; // edx
  int result; // eax
  __lock *v6; // [esp-4h] [ebp-4h]

  g_CrtThreadDataAccessor(a3, a1);
  __lock_p(lock);
  *newEntry = g_CrtFinalizerListHead;
  g_CrtFinalizerListHead = (int)(intptr_t)newEntry;
  __lock_v(v6);
  return result;
}
// 487055: variable 'v3' is possibly undefined
// 487062: variable 'v6' is possibly undefined
// 51A568: using guessed type int (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD);
// 51A648: using guessed type int g_CrtFinalizerListHead;

//----- (00487069) --------------------------------------------------------
int  CRT_PrintfFormatEngine(int stream, _BYTE *format, void (*outputFn)(void), int *argList)
{
  char *spec_ptr; // edi
  char specChar; // al
  int v8; // edx
  _DWORD *nFarPtr; // edx
  int farPtrArgSlot; // eoff
  int v11; // eax
  _DWORD *nDwordPtr; // edx
  int v13; // edi
  int v14; // ecx
  int v15; // ebx
  _WORD *nWordPtr; // edx
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  unsigned __int16 *converted_text; // edi
  __int16 wideStrSegment; // dx
  unsigned __int8 *buffer_ptr; // ebx
  int outputStream; // [esp+0h] [ebp-80h] BYREF
  int field_width; // [esp+4h] [ebp-7Ch]
  int char_count; // [esp+10h] [ebp-70h]
  char conversion_char; // [esp+15h] [ebp-6Bh]
  char pad_char; // [esp+16h] [ebp-6Ah]
  __int16 v29 CLASH95_UNUSED; // [esp+1Ch] [ebp-64h]
  __int16 flags; // [esp+1Eh] [ebp-62h]
  int prefix_len; // [esp+20h] [ebp-60h]
  int zero_pad_len; // [esp+24h] [ebp-5Ch]
  int text_len; // [esp+28h] [ebp-58h]
  int v34; // [esp+2Ch] [ebp-54h]
  int v35; // [esp+30h] [ebp-50h]
  int v36; // [esp+34h] [ebp-4Ch]
  unsigned __int8 conversion_buffer[40]; // [esp+38h] [ebp-48h] BYREF
  int argCursor; // [esp+60h] [ebp-20h] BYREF
  int convArgCursor; // [esp+64h] [ebp-1Ch] BYREF
  _BYTE *format_ptr; // [esp+68h] [ebp-18h]
  char v41 CLASH95_UNUSED; // [esp+6Ch] [ebp-14h]

  outputStream = stream;
  v41 = 0;
  format_ptr = format;
  flags = 0;
  v29 = 100;
  char_count = 0;
  while ( *format_ptr )
  {
    if ( *format_ptr == 37 )
    {
      argCursor = *argList;
      spec_ptr = CRT_ParseWidthPrecisionSpec(format_ptr + 1, &argCursor, (int)(intptr_t)&outputStream);
      *argList = argCursor;
      specChar = *spec_ptr;
      conversion_char = specChar;
      format_ptr = spec_ptr + 1;
      if ( !specChar )
        return char_count;
      if ( specChar == 110 )
      {
        if ( (flags & 0x20) != 0 )
        {
          if ( (flags & 0x80u) != 0 )
          {
            v8 = *argList + 8;
            *argList = v8;
            farPtrArgSlot = v8 - 8;
            nFarPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v8 - 8);
            __ES__ = *(_WORD *)(uintptr_t)(farPtrArgSlot + 4);
            goto LABEL_7;
          }
          if ( (flags & 0x40) != 0 )
          {
            v11 = *argList + 4;
            *argList = v11;
            nDwordPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v11 - 4);
            goto LABEL_11;
          }
LABEL_10:
          v13 = *argList + 4;
          *argList = v13;
          nDwordPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v13 - 4);
          goto LABEL_11;
        }
        if ( (flags & 0x10) != 0 )
        {
          if ( (flags & 0x80u) == 0 )
          {
            if ( (flags & 0x40) != 0 )
            {
              v15 = *argList + 4;
              *argList = v15;
              nWordPtr = (_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v15 - 4);
            }
            else
            {
              v17 = *argList + 4;
              *argList = v17;
              nWordPtr = (_WORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v17 - 4);
            }
            *nWordPtr = char_count;
          }
          else
          {
            v14 = *argList + 8;
            *argList = v14;
            *(_DWORD *)MK_FP(*(_WORD *)(v14 - 8 + 4), *(_DWORD *)(uintptr_t)(v14 - 8)) = char_count;
          }
        }
        else if ( (flags & 0x80u) == 0 )
        {
          if ( (flags & 0x40) != 0 )
            goto LABEL_10;
          v19 = *argList + 4;
          *argList = v19;
          nDwordPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v19 - 4);
LABEL_11:
          *nDwordPtr = char_count;
        }
        else
        {
          v18 = *argList + 8;
          *argList = v18;
          nFarPtr = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v18 - 8);
          __ES__ = *(_WORD *)(uintptr_t)(v18 - 8 + 4);
LABEL_7:
          *nFarPtr = char_count;
        }
      }
      else
      {
        convArgCursor = *argList;
        converted_text = CRT_ConvertPrintfArgument(conversion_buffer, &convArgCursor, (int)(intptr_t)&outputStream);
        __ES__ = wideStrSegment;
        *argList = convArgCursor;
        field_width -= v36 + v35 + v34 + text_len + zero_pad_len + prefix_len;
        if ( (flags & 8) == 0 && pad_char == 32 )
        {
          while ( field_width > 0 )
          {
            outputFn();
            --field_width;
          }
        }
        buffer_ptr = conversion_buffer;
        while ( prefix_len > 0 )
        {
          outputFn();
          ++buffer_ptr;
          --prefix_len;
        }
        while ( zero_pad_len > 0 )
        {
          outputFn();
          --zero_pad_len;
        }
        if ( conversion_char == 115 )
        {
          if ( (flags & 0x20) != 0 )
            goto LABEL_37;
          while ( text_len > 0 )
          {
            outputFn();
            converted_text = (unsigned __int16 *)((char *)converted_text + 1);
            --text_len;
          }
        }
        else
        {
          if ( conversion_char == 83 )
          {
LABEL_37:
            CRT_OutputWideStringAsMultiByte(converted_text, __ES__, (unsigned __int8 *)outputFn, (int)(intptr_t)&outputStream);
            goto LABEL_43;
          }
          while ( text_len > 0 )
          {
            ((void (__cdecl *)(int))outputFn)(outputStream);
            converted_text = (unsigned __int16 *)((char *)converted_text + 1);
            --text_len;
          }
        }
LABEL_43:
        while ( v34 > 0 )
        {
          outputFn();
          --v34;
        }
        while ( v35 > 0 )
        {
          outputFn();
          converted_text = (unsigned __int16 *)((char *)converted_text + 1);
          --v35;
        }
        while ( v36 > 0 )
        {
          outputFn();
          --v36;
        }
        if ( (flags & 8) != 0 )
        {
          while ( field_width > 0 )
          {
            outputFn();
            --field_width;
          }
        }
      }
    }
    else
    {
      ++format_ptr;
      outputFn();
    }
  }
  return char_count;
}
// 4871CA: variable 'v21' is possibly undefined

//----- (0048732A) --------------------------------------------------------
char * CRT_ParseWidthPrecisionSpec(char *formatPtr, int *args, int spec)
{
  char *result; // eax
  int v5; // edx
  int widthValue; // edx
  char v7; // ch
  int v8; // edx
  int v9; // edx
  int precisionValue; // edx
  int v11; // edx
  char modifierChar; // dl

  *(_BYTE *)(uintptr_t)(spec + 22) = 32;
  result = CRT_ParsePrintfFlags(formatPtr, spec);
  *(_DWORD *)(uintptr_t)(spec + 4) = 0;
  if ( *result == 42 )
  {
    v5 = *args + 4;
    *args = v5;
    widthValue = *(_DWORD *)(uintptr_t)(v5 - 4);
    *(_DWORD *)(uintptr_t)(spec + 4) = widthValue;
    if ( widthValue < 0 )
    {
      v7 = *(_BYTE *)(uintptr_t)(spec + 30) | 8;
      *(_DWORD *)(uintptr_t)(spec + 4) = -widthValue;
      *(_BYTE *)(uintptr_t)(spec + 30) = v7;
    }
    ++result;
  }
  else
  {
    while ( (unsigned __int8)*result >= 0x30u && (unsigned __int8)*result <= 0x39u )
    {
      v8 = (unsigned __int8)*result++ - 48;
      *(_DWORD *)(uintptr_t)(spec + 4) = v8 + 10 * *(_DWORD *)(uintptr_t)(spec + 4);
    }
  }
  *(_DWORD *)(uintptr_t)(spec + 8) = -1;
  if ( *result == 46 )
  {
    ++result;
    *(_DWORD *)(uintptr_t)(spec + 8) = 0;
    if ( *result == 42 )
    {
      v9 = *args + 4;
      *args = v9;
      precisionValue = *(_DWORD *)(uintptr_t)(v9 - 4);
      *(_DWORD *)(uintptr_t)(spec + 8) = precisionValue;
      if ( precisionValue < 0 )
        *(_DWORD *)(uintptr_t)(spec + 8) = -1;
      ++result;
    }
    else
    {
      while ( (unsigned __int8)*result >= 0x30u && (unsigned __int8)*result <= 0x39u )
      {
        v11 = (unsigned __int8)*result++ - 48;
        *(_DWORD *)(uintptr_t)(spec + 8) = v11 + 10 * *(_DWORD *)(uintptr_t)(spec + 8);
      }
    }
    if ( *(_DWORD *)(uintptr_t)(spec + 8) != -1 )
      *(_BYTE *)(uintptr_t)(spec + 22) = 32;
  }
  modifierChar = *result;
  if ( (unsigned __int8)*result >= 0x4Eu )
  {
    if ( (unsigned __int8)*result <= 0x4Eu )
    {
      *(_BYTE *)(uintptr_t)(spec + 30) |= 0x40u;
    }
    else
    {
      if ( (unsigned __int8)modifierChar >= 0x6Cu )
      {
        if ( (unsigned __int8)modifierChar <= 0x6Cu || modifierChar == 119 )
        {
          ++result;
          *(_BYTE *)(uintptr_t)(spec + 30) |= 0x20u;
        }
        return result;
      }
      if ( modifierChar != 104 )
        return result;
      *(_BYTE *)(uintptr_t)(spec + 30) |= 0x10u;
    }
    return ++result;
  }
  if ( (unsigned __int8)modifierChar < 0x49u )
  {
    if ( modifierChar != 70 )
      return result;
    *(_BYTE *)(uintptr_t)(spec + 30) |= 0x80u;
    return ++result;
  }
  if ( (unsigned __int8)modifierChar <= 0x49u )
  {
    if ( result[1] == 54 && result[2] == 52 )
    {
      result += 3;
      *(_BYTE *)(uintptr_t)(spec + 31) |= 1u;
    }
  }
  else if ( modifierChar == 76 )
  {
    ++result;
    *(_BYTE *)(uintptr_t)(spec + 31) |= 1u;
  }
  return result;
}

//----- (00487477) --------------------------------------------------------
char * CRT_ParsePrintfFlags(char *result, int spec)
{
  char flagChar; // bl
  char v3; // ch
  char v4; // bh

  *(_WORD *)(uintptr_t)(spec + 30) = 0;
  while ( 1 )
  {
    flagChar = *result;
    if ( *result == 45 )
    {
      *(_BYTE *)(uintptr_t)(spec + 30) |= 8u;
      goto LABEL_13;
    }
    if ( flagChar == 35 )
    {
      *(_BYTE *)(uintptr_t)(spec + 30) |= 1u;
      goto LABEL_13;
    }
    if ( flagChar == 43 )
    {
      v3 = *(_BYTE *)(uintptr_t)(spec + 30) | 4;
      *(_BYTE *)(uintptr_t)(spec + 30) = v3;
      *(_BYTE *)(uintptr_t)(spec + 30) = v3 & 0xFD;
      goto LABEL_13;
    }
    if ( flagChar != 32 )
      break;
    v4 = *(_BYTE *)(uintptr_t)(spec + 30);
    if ( (v4 & 4) == 0 )
      *(_BYTE *)(uintptr_t)(spec + 30) = v4 | 2;
LABEL_13:
    ++result;
  }
  if ( flagChar == 48 )
  {
    *(_BYTE *)(uintptr_t)(spec + 22) = 48;
    goto LABEL_13;
  }
  return result;
}

//----- (004874D4) --------------------------------------------------------
int  CRT_FarStrLenBounded(int stringOffset, __int16 stringSegment CLASH95_UNUSED, int maxLength)
{
  int result; // eax
  char curr_char; // bl

  for ( result = 0; ; ++result )
  {
    curr_char = *(_BYTE *)MK_FP(stringSegment, stringOffset++);
    if ( !curr_char || result == maxLength )
      break;
  }
  return result;
}

//----- (004874F8) --------------------------------------------------------
int  CRT_WideCharToMultiByteLenBounded(unsigned __int16 *wideStr, __int16 segment, int maxLength)
{
  int byteCount; // ecx
  unsigned __int16 wideChar; // dx
  int charBytes; // eax
  int v10; // eax

  __ES__ = segment;
  byteCount = 0;
  if ( maxLength == -1 )
  {
    while ( *wideStr )
    {
      wideChar = *wideStr++;
      charBytes = wctomb_(byteCount, wideChar);
      if ( charBytes != -1 )
        byteCount += charBytes;
    }
    return byteCount;
  }
  while ( *wideStr && byteCount <= maxLength )
  {
    v10 = wctomb_(byteCount, *wideStr++);
    if ( v10 != -1 )
      byteCount += v10;
  }
  if ( byteCount <= maxLength )
    return byteCount;
  return maxLength;
}
// 48751E: variable 'v6' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);

//----- (00487561) --------------------------------------------------------
int  CRT_FormatPaddedHexDigits(signed int value, char *buffer, int digitCount)
{
  int result; // eax
  char *srcPtr; // edx
  char *destPtr; // ebx
  char *padPtr; // edx

  Str_FormatSignedRadixDigits(value, buffer, 0x10u);
  result = digitCount - 1;
  srcPtr = &buffer[strlen(buffer)];
  destPtr = &buffer[digitCount - 1];
  while ( srcPtr != buffer )
  {
    --srcPtr;
    --result;
    *destPtr-- = *srcPtr;
  }
  padPtr = &buffer[result];
  while ( result >= 0 )
  {
    --result;
    *padPtr-- = 48;
  }
  buffer[digitCount] = 0;
  return result;
}

//----- (004875BF) --------------------------------------------------------
char  CRT_FormatFixedDecimal(char *buffer, int value, int spec)
{
  char *digitsDest; // ecx
  _BYTE *v5; // eax
  _BYTE *digitPtr; // ecx
  _BYTE *digitsStart; // ebx
  _BYTE *roundPtr; // ecx
  int absValue; // [esp+0h] [ebp-10h]

  digitsDest = buffer;
  absValue = value;
  if ( value < 0 )
  {
    digitsDest = buffer + 1;
    *buffer = 45;
    absValue = -value;
  }
  if ( *(_DWORD *)(uintptr_t)(spec + 8) == -1 )
    *(_DWORD *)(uintptr_t)(spec + 8) = 4;
  LOBYTE(v5) = Str_FormatSignedRadixDigits(HIWORD(absValue), digitsDest, 0xAu);
  digitsStart = digitPtr;
  while ( *digitPtr )
    ++digitPtr;
  if ( *(_DWORD *)(uintptr_t)(spec + 8) )
  {
    *digitPtr = 46;
    v5 = 0;
    ++digitPtr;
    while ( (int)(intptr_t)v5 < *(_DWORD *)(uintptr_t)(spec + 8) )
    {
      absValue = 10 * (unsigned __int16)absValue;
      ++v5;
      *digitPtr++ = BYTE2(absValue) + 48;
    }
    *digitPtr = 0;
  }
  if ( (absValue & 0x8000) != 0 )
  {
    while ( digitPtr != digitsStart )
    {
      if ( *--digitPtr == 46 )
        --digitPtr;
      LOBYTE(v5) = *digitPtr;
      if ( *digitPtr != 57 )
      {
        *digitPtr = (_BYTE)(intptr_t)v5 + 1;
        return (char)(intptr_t)v5;
      }
      *digitPtr = 48;
    }
    roundPtr = digitsStart + 1;
    *digitsStart = 49;
    while ( 1 )
    {
      v5 = roundPtr + 1;
      if ( *roundPtr != 48 )
        break;
      ++roundPtr;
    }
    if ( *roundPtr == 46 )
    {
      *roundPtr = 48;
      roundPtr += 2;
      *v5 = 46;
      while ( *roundPtr == 48 )
        ++roundPtr;
    }
    *roundPtr = 48;
    roundPtr[1] = 0;
  }
  return (char)(intptr_t)v5;
}
// 4875FB: variable 'v6' is possibly undefined

//----- (0048769A) --------------------------------------------------------
// attributes: thunk
int CRT_DispatchFloatFormat(void)
{
  return g_FloatEfgFormatFn();
}
// 51AF04: using guessed type int (*off_51AF04)();

//----- (004876A1) --------------------------------------------------------
int  CRT_ApplyZeroPadWidth(int result)
{
  int v1; // esi
  int v2; // edi
  int v3; // ebp
  int v4; // ebx

  if ( (*(_BYTE *)(uintptr_t)(result + 30) & 8) == 0 && *(_BYTE *)(uintptr_t)(result + 22) == 48 )
  {
    v1 = *(_DWORD *)(uintptr_t)(result + 40);
    v2 = *(_DWORD *)(uintptr_t)(result + 44);
    v3 = *(_DWORD *)(uintptr_t)(result + 48);
    v4 = *(_DWORD *)(uintptr_t)(result + 52);
    if ( *(_DWORD *)(uintptr_t)(result + 4) - *(_DWORD *)(uintptr_t)(result + 32) - *(_DWORD *)(uintptr_t)(result + 36) - v1 - v2 - v3 - v4 > 0 )
      *(_DWORD *)(uintptr_t)(result + 36) = *(_DWORD *)(uintptr_t)(result + 4) - *(_DWORD *)(uintptr_t)(result + 32) - v1 - v2 - v3 - v4;
  }
  return result;
}

//----- (004876E4) --------------------------------------------------------
unsigned __int16 * CRT_OutputWideStringAsMultiByte(
        unsigned __int16 *result,
        __int16 segment,
        unsigned __int8 *a3,
        int spec)
{
  unsigned __int16 *widePtr; // esi
  void (__fastcall *putcFn)(unsigned __int8 *, _DWORD); // ebp
  int mbLength; // edi
  int v7; // ecx
  int mbBuffer; // [esp+0h] [ebp-14h] BYREF

  __ES__ = segment;
  widePtr = result;
  putcFn = (void (__fastcall *)(unsigned __int8 *, _DWORD))a3;
  while ( *(int *)(uintptr_t)(spec + 40) > 0 )
  {
    result = (unsigned __int16 *)(uintptr_t)wctomb_(a3, *widePtr++);
    mbLength = (int)(intptr_t)result;
    if ( result != (unsigned __int16 *)-1 )
    {
      if ( (int)(intptr_t)result > *(_DWORD *)(uintptr_t)(spec + 40) )
      {
        *(_DWORD *)(uintptr_t)(spec + 40) = 0;
        return result;
      }
      a3 = (unsigned __int8 *)&mbBuffer;
      while ( --mbLength != -1 )
      {
        putcFn(a3, *a3);
        result = (unsigned __int16 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(spec + 40) - 1);
        a3 = (unsigned __int8 *)(uintptr_t)(v7 + 1);
        *(_DWORD *)(uintptr_t)(spec + 40) = result;
      }
    }
  }
  return result;
}
// 4876FF: variable 'a3' is possibly undefined
// 487727: variable 'v7' is possibly undefined
// 4B58FF: using guessed type int __fastcall wctomb_(_DWORD, _DWORD);
