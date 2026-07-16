/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

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
  flipState = *(_BYTE *)(uintptr_t)(self + 2033);
  busyGuardAddr = self + 1985;
  ++*(_DWORD *)(uintptr_t)(self + 1985);
  EnterCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(self + 1989));
  v80 = 1;
  if ( (unsigned __int8)flipState > 3u )
  {
LABEL_19:
    v80 = 0;
    busyGuard = (_DWORD *)(uintptr_t)busyGuardAddr;
    LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(busyGuardAddr + 4));
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
        if ( !*(_BYTE *)(uintptr_t)(self + 1968)
          || !*(_DWORD *)(uintptr_t)(self + 1964)
          || (srcWidth = *(_DWORD *)(uintptr_t)(self + 2087) - *(_DWORD *)(uintptr_t)(self + 2079),
              stretchRatio = 1000 * (*(_DWORD *)(uintptr_t)(self + 2071) - *(_DWORD *)(uintptr_t)(self + 2063)) / srcWidth,
              v17 = 1000 * (*(_DWORD *)(uintptr_t)(self + 2071) - *(_DWORD *)(uintptr_t)(self + 2063)) % srcWidth,
              stretchRatio < *(_DWORD *)(uintptr_t)(self + 2143))
          || stretchRatio > *(_DWORD *)(uintptr_t)(self + 2147) )
        {
          if ( !*(_DWORD *)(uintptr_t)(self + 1964) )
            return AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(uintptr_t)(self + 2017));
          overlayCaps = *(_DWORD *)(uintptr_t)(self + 2171);
          LOBYTE(overlayCaps) = overlayCaps | 2;
          requiredCaps = *(_DWORD *)(uintptr_t)(self + 2175) | overlayCaps;
          v17 = requiredCaps & *(_DWORD *)(uintptr_t)(self + 2119);
          if ( v17 != requiredCaps )
            return AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(uintptr_t)(self + 2017));
        }
        result = AviPlayer_BltFastOverlayFromBackBuffer(self, v17);
      }
      if ( !*(_BYTE *)(uintptr_t)(self + 1968) || !*(_DWORD *)(uintptr_t)(self + 1964) )
        return AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(uintptr_t)(self + 1964));
    }
  }
  else
  {
    switch ( flipState )
    {
      case 0:
        if ( !*(_DWORD *)(uintptr_t)(self + 2025) )
          goto LABEL_86;
        if ( *(_DWORD *)(uintptr_t)(self + 415) )
        {
          v2 = self;
          if ( (!*(_BYTE *)(uintptr_t)(self + 2052) || AviPlayer_TestActiveModeFlag(self))
            && (*(_BYTE *)(uintptr_t)(self + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(self))
            && (AviPlayer_HasValidRateParams(self) && AviPlayer_IsPlaybackRateInRange(self) || *(_DWORD *)(uintptr_t)(self + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(self)) )
          {
            overlaySurface = *(_DWORD *)(uintptr_t)(v2 + 1964);
            v4 = v2;
            srcRectPtr = (int *)(uintptr_t)(v2 + 2095);
            surfaceDesc = 108;
            lockResult = (*(int (__stdcall **)(int, int, int *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 100))(overlaySurface, v2 + 2095, &surfaceDesc, 33, 0);
            if ( !lockResult
              || lockResult == -2005532222
              && ((*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 108))(overlaySurface)
               || !(*(int (__stdcall **)(int, int *, int *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 100))(overlaySurface, srcRectPtr, &surfaceDesc, 33, 0)) )
            {
              v83 = srcRectPtr[3] - srcRectPtr[1];
              rectLeft = *srcRectPtr;
              rectRight = srcRectPtr[2];
              overlayLockedBits = v53;
              frameFlags = *(_DWORD *)(uintptr_t)(v4 + 2029);
              destWidth = rectRight - rectLeft;
              frameData = *(_DWORD *)(uintptr_t)(v4 + 2025);
              bytesPerPixel = Mem_BitsToBytesCeil(*(_DWORD *)(uintptr_t)(v4 + 2123));
              AviPlayer_UpdateStreamRectAndSendICDrawBegin((int *)(uintptr_t)(v4 + 415), overlayLockedBits, v83, destWidth, v11 / bytesPerPixel, frameData, frameFlags);
              unlockResult = (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 128))(overlaySurface, v53);
              if ( unlockResult
                && (unlockResult != -2005532222
                 || !(*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 108))(overlaySurface)
                 && (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 128))(overlaySurface, v53)) )
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
            backSurface = *(_DWORD *)(uintptr_t)(v2 + 2017);
            HIDWORD(lockDesc[0]) = 108;
            overlayLockResult = (*(int (__stdcall **)(int, _DWORD, char *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 100))(
                    backSurface,
                    0,
                    (char *)lockDesc + 4,
                    33,
                    0);
            if ( !overlayLockResult
              || overlayLockResult == -2005532222
              && ((*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 108))(backSurface)
               || !(*(int (__stdcall **)(int, _DWORD, char *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 100))(
                     backSurface,
                     0,
                     (char *)lockDesc + 4,
                     33,
                     0)) )
            {
              AviPlayer_BitmapHeightAbs(v18);
              bitmapWidth = AviPlayer_BitmapWidth(v18);
              backLockedBits = v71;
              drawFlags = *(_DWORD *)(uintptr_t)(v18 + 2029);
              frameBits = *(_DWORD *)(uintptr_t)(v18 + 2025);
              v83 = Mem_BitsToBytesCeil(*(_DWORD *)(uintptr_t)(v18 + 2123));
              AviPlayer_UpdateStreamRectAndSendICDrawBegin((int *)(uintptr_t)(v18 + 415), backLockedBits, v23, bitmapWidth, v22 / v83, frameBits, drawFlags);
              overlayUnlockResult = (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 128))(backSurface, v71);
              if ( overlayUnlockResult
                && (overlayUnlockResult != -2005532222
                 || !(*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 108))(backSurface)
                 && (*(int (__stdcall **)(int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 128))(backSurface, v71)) )
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
          framePtr = *(_DWORD *)(uintptr_t)(self + 2025);
          if ( (!*(_BYTE *)(uintptr_t)(self + 2052) || AviPlayer_TestActiveModeFlag(self))
            && (*(_BYTE *)(uintptr_t)(self + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(self))
            && (AviPlayer_HasValidRateParams(self) && AviPlayer_IsPlaybackRateInRange(self) || *(_DWORD *)(uintptr_t)(self + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(self)) )
          {
            AviPlayer_BlitFrameToSurface(
              (_DWORD *)(uintptr_t)self,
              *(_DWORD *)(uintptr_t)(self + 1964),
              framePtr,
              (int *)(uintptr_t)(self + 2095),
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
              (_DWORD *)(uintptr_t)self,
              *(_DWORD *)(uintptr_t)(self + 2017),
              framePtr,
              (int *)(uintptr_t)(self + 2095),
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
        if ( *(int *)(uintptr_t)(self + 2034) > 0 )
        {
          ++*(_DWORD *)(uintptr_t)(self + 207);
          PulseEvent(*(HANDLE *)(uintptr_t)(self + 171));
          --*(_DWORD *)(uintptr_t)(self + 2034);
        }
        goto LABEL_19;
      case 1:
        decodedFrameBuffer = *(_DWORD *)(uintptr_t)(self + 2179);
        if ( (!*(_BYTE *)(uintptr_t)(self + 2052) || AviPlayer_TestActiveModeFlag(self))
          && (*(_BYTE *)(uintptr_t)(self + 2052) || AviPlayer_TestModeFlagBit2AndSubframe(self))
          && (AviPlayer_HasValidRateParams(self) && AviPlayer_IsPlaybackRateInRange(self) || *(_DWORD *)(uintptr_t)(self + 1964) && AviPlayer_SupportsRequiredPlaybackCaps(self)) )
        {
          AviPlayer_BlitFrameToSurface(
            (_DWORD *)(uintptr_t)self,
            *(_DWORD *)(uintptr_t)(self + 1964),
            decodedFrameBuffer,
            (int *)(uintptr_t)(self + 2095),
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
            (_DWORD *)(uintptr_t)self,
            *(_DWORD *)(uintptr_t)(self + 2017),
            decodedFrameBuffer,
            (int *)(uintptr_t)(self + 2095),
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
        if ( *(_BYTE *)(uintptr_t)(self + 1968)
          && *(_DWORD *)(uintptr_t)(self + 1964)
          && (srcSpan = *(_DWORD *)(uintptr_t)(self + 2087) - *(_DWORD *)(uintptr_t)(self + 2079),
              stretchRate = 1000 * (*(_DWORD *)(uintptr_t)(self + 2071) - *(_DWORD *)(uintptr_t)(self + 2063)) / srcSpan,
              v32 = 1000 * (*(_DWORD *)(uintptr_t)(self + 2071) - *(_DWORD *)(uintptr_t)(self + 2063)) % srcSpan,
              stretchRate >= *(_DWORD *)(uintptr_t)(self + 2143))
          && stretchRate <= *(_DWORD *)(uintptr_t)(self + 2147)
          || *(_DWORD *)(uintptr_t)(self + 1964)
          && (overlayCapsAlt = *(_DWORD *)(uintptr_t)(self + 2171),
              LOBYTE(overlayCapsAlt) = overlayCapsAlt | 2,
              requiredCapsAlt = *(_DWORD *)(uintptr_t)(self + 2175) | overlayCapsAlt,
              v32 = requiredCapsAlt & *(_DWORD *)(uintptr_t)(self + 2119),
              v32 == requiredCapsAlt) )
        {
          AviPlayer_BltFastOverlayFromBackBuffer(self, v32);
          flipState = 3;
          goto LABEL_19;
        }
        AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(uintptr_t)(self + 2017));
        LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(busyGuardAddr + 4));
        return (*(_DWORD *)(uintptr_t)busyGuardAddr)--;
      case 3:
        if ( !*(_BYTE *)(uintptr_t)(self + 1968) || (overlayIface = *(_DWORD *)(uintptr_t)(self + 1964)) == 0 )
        {
          AviPlayer_BltFrameToPrimarySurface(self, *(_DWORD *)(uintptr_t)(self + 1964));
LABEL_86:
          LeaveCriticalSection((LPCRITICAL_SECTION)(uintptr_t)(busyGuardAddr + 4));
          return (*(_DWORD *)(uintptr_t)busyGuardAddr)--;
        }
        if ( !*(_BYTE *)(uintptr_t)(self + 2051) )
          goto LABEL_86;
        flipResult = (*(int (__stdcall **)(int, _DWORD, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlayIface + 44))(overlayIface, 0, 0);
        if ( !flipResult
          || flipResult == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 108))(*(_DWORD *)(uintptr_t)(self + 1964))
           || !(*(int (__stdcall **)(_DWORD, _DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 44))(
                 *(_DWORD *)(uintptr_t)(self + 1964),
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

  self = (_DWORD **)(uintptr_t)result;
  ddObject = *(_DWORD *)(uintptr_t)(result + 2151);
  if ( ddObject )
  {
    result = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)ddObject + 4))();
    if ( result )
    {
      restoreHr = (*(int (__stdcall **)(int, int, int))(uintptr_t)(**(_DWORD **)((char *)self + 2151) + 4))(srcSurface, a2, a3);
      if ( (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)restoreHr + 96))(restoreHr) == -2005532222 )
        (*(void (**)(void))(uintptr_t)(**(_DWORD **)((char *)self + 2151) + 8))();
      v10 = ((__int64 (__thiscall *)(_DWORD, _DWORD, int, _DWORD))(uintptr_t)*(_DWORD *)(uintptr_t)(**(_DWORD **)((char *)self + 2151) + 4))(
              *self[489],
              0,
              0x1000000,
              0);
      return (*(int (__stdcall **)(_DWORD, int, _DWORD))(uintptr_t)(v11 + 20))(HIDWORD(v10), (int)(intptr_t)self + 2155, v10);
    }
    else if ( self[488] )
    {
      result = (***(int (****)(void))((char *)self + 2151))();
      if ( result )
      {
        hr = (***(int (__stdcall ****)(int, int, int))((char *)self + 2151))(srcSurface, a2, a3);
        if ( (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)hr + 96))(hr) == -2005532222 )
          (*(void (**)(void))(uintptr_t)(**(_DWORD **)((char *)self + 2151) + 8))();
        v7 = *self[488];
        v8 = ((__int64 (__cdecl *)(_DWORD, int, _DWORD))(uintptr_t)***(_DWORD ***)((char *)self + 2151))(0, 0x1000000, 0);
        return (*(int (__stdcall **)(_DWORD, int, _DWORD))(uintptr_t)(v7 + 20))(HIDWORD(v8), (int)(intptr_t)self + 2155, v8);
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

  result = (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 28))(
             *(_DWORD *)(uintptr_t)(self + 1964),
             0,
             0,
             *(_DWORD *)(uintptr_t)(self + 2017),
             0,
             0);
  if ( result )
  {
    if ( result == -2005532222 )
    {
      if ( (*(int (__stdcall **)(_DWORD, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 96))(*(_DWORD *)(uintptr_t)(self + 1964), a2) == -2005532222 )
        (*(void (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 108))(*(_DWORD *)(uintptr_t)(self + 1964));
      if ( (*(int (__cdecl **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 2017) + 96))(*(_DWORD *)(uintptr_t)(self + 2017)) == -2005532222 )
        (*(void (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 2017) + 108))(*(_DWORD *)(uintptr_t)(self + 2017));
    }
    return (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 28))(
             *(_DWORD *)(uintptr_t)(self + 1964),
             0,
             0,
             *(_DWORD *)(uintptr_t)(self + 2017),
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

  if ( *(_DWORD *)(uintptr_t)(self + 2175)
    || (result = (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 28))(
                   *(_DWORD *)(uintptr_t)(self + 1956),
                   *(_DWORD *)(uintptr_t)(self + 2063),
                   *(_DWORD *)(uintptr_t)(self + 2067),
                   srcSurface,
                   self + 2079,
                   *(_DWORD *)(uintptr_t)(self + 2115))) != 0 )
  {
    if ( (*(int (__stdcall **)(_DWORD, int, int, int, _DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 20))(
           *(_DWORD *)(uintptr_t)(self + 1956),
           self + 2063,
           srcSurface,
           self + 2079,
           *(_DWORD *)(uintptr_t)(self + 2111),
           0) != -2005532222 )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 20))(
               *(_DWORD *)(uintptr_t)(self + 1956),
               self + 2063,
               srcSurface,
               self + 2079,
               *(_DWORD *)(uintptr_t)(self + 2111) | 0x1000000,
               0);
    if ( (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 96))(*(_DWORD *)(uintptr_t)(self + 1956)) == -2005532222 )
    {
      result = (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956));
      if ( result )
        return result;
      if ( *(_DWORD *)(uintptr_t)(self + 1948) )
        (*(void (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 124))(
          *(_DWORD *)(uintptr_t)(self + 1956),
          *(_DWORD *)(uintptr_t)(self + 1948));
      AviException_RebuildClipperOnSurfaceLoss(self, v5, v6, srcSurface);
    }
    if ( (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)srcSurface + 96))(srcSurface) != -2005532222 )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 20))(
               *(_DWORD *)(uintptr_t)(self + 1956),
               self + 2063,
               srcSurface,
               self + 2079,
               *(_DWORD *)(uintptr_t)(self + 2111) | 0x1000000,
               0);
    result = (*(int (__stdcall **)(int))(uintptr_t)(*(_DWORD *)(uintptr_t)srcSurface + 108))(srcSurface);
    if ( !result )
      return (*(int (__stdcall **)(_DWORD, int, int, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 20))(
               *(_DWORD *)(uintptr_t)(self + 1956),
               self + 2063,
               srcSurface,
               self + 2079,
               *(_DWORD *)(uintptr_t)(self + 2111) | 0x1000000,
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

  *(_DWORD *)(uintptr_t)(self + 2063) = destRect->left;
  *(_DWORD *)(uintptr_t)(self + 2067) = destRect->top;
  *(_DWORD *)(uintptr_t)(self + 2071) = destRect->right;
  *(_DWORD *)(uintptr_t)(self + 2075) = destRect->bottom;
  *(_DWORD *)(uintptr_t)(self + 2079) = *(_DWORD *)(uintptr_t)(self + 2095);
  *(_DWORD *)(uintptr_t)(self + 2083) = *(_DWORD *)(uintptr_t)(self + 2099);
  *(_DWORD *)(uintptr_t)(self + 2087) = *(_DWORD *)(uintptr_t)(self + 2103);
  *(_DWORD *)(uintptr_t)(self + 2091) = *(_DWORD *)(uintptr_t)(self + 2107);
  srcWidth = *(_DWORD *)(uintptr_t)(self + 2087) - *(_DWORD *)(uintptr_t)(self + 2079);
  destHeight = destRect->bottom - destRect->top;
  srcHeight = *(_DWORD *)(uintptr_t)(self + 2091) - *(_DWORD *)(uintptr_t)(self + 2083);
  destWidth = destRect->right - destRect->left;
  IntersectRect((LPRECT)(uintptr_t)(self + 2063), destRect, (const RECT *)(uintptr_t)(self + 1969));
  result = IsRectEmpty((const RECT *)(uintptr_t)(self + 2063));
  if ( !result )
  {
    if ( !EqualRect((const RECT *)(uintptr_t)(self + 2063), destRect) )
    {
      *(_DWORD *)(uintptr_t)(self + 2079) += srcWidth * (*(_DWORD *)(uintptr_t)(self + 2063) - destRect->left) / destWidth;
      *(_DWORD *)(uintptr_t)(self + 2087) += srcWidth * (*(_DWORD *)(uintptr_t)(self + 2071) - destRect->right) / destWidth;
      *(_DWORD *)(uintptr_t)(self + 2083) += srcHeight * (*(_DWORD *)(uintptr_t)(self + 2067) - destRect->top) / destHeight;
      *(_DWORD *)(uintptr_t)(self + 2091) += srcHeight * (*(_DWORD *)(uintptr_t)(self + 2075) - destRect->bottom) / destHeight;
    }
    if ( srcWidth == destWidth && destHeight == srcHeight )
    {
      result = destWidth ^ srcWidth;
      *(_DWORD *)(uintptr_t)(self + 2175) = destWidth ^ srcWidth;
    }
    else
    {
      result = 4;
      *(_DWORD *)(uintptr_t)(self + 2175) = 4;
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

  if ( !*(_BYTE *)(uintptr_t)(self + 2053) || (result = *(_DWORD *)(uintptr_t)(self + 2054), result < *(_DWORD *)(uintptr_t)(self + 2021)) )
  {
    result = WaitForSingleObject(*(HANDLE *)(uintptr_t)(self + 2196), 0);
    if ( !result )
    {
      if ( !*(_BYTE *)(uintptr_t)(self + 2062) )
        AviPlayer_RenderFrame(self, destRect);
      AviPlayer_Flip(self);
      if ( !*(_BYTE *)(uintptr_t)(self + 1968) || !*(_DWORD *)(uintptr_t)(self + 1964) )
        goto LABEL_22;
      destWidthScaled = 1000 * AviPlayer_SpanDelta(self, (_DWORD *)(uintptr_t)(self + 2063));
      stretchRatio = destWidthScaled / AviPlayer_SpanDelta(v6, (_DWORD *)(uintptr_t)(self + 2079));
      if ( stretchRatio < *(_DWORD *)(uintptr_t)(self + 2143) || stretchRatio > *(_DWORD *)(uintptr_t)(self + 2147) )
      {
        if ( !*(_BYTE *)(uintptr_t)(self + 1968) )
          goto LABEL_22;
        overlaySurface = *(_DWORD *)(uintptr_t)(self + 1964);
        if ( !overlaySurface )
          goto LABEL_22;
        hideResult = (*(int (__stdcall **)(int, int, _DWORD, int, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 132))(
                overlaySurface,
                self + 2095,
                *(_DWORD *)(uintptr_t)(self + 1956),
                self + 2063,
                512,
                0);
        if ( !hideResult )
          goto LABEL_22;
        if ( hideResult == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 96))(*(_DWORD *)(uintptr_t)(self + 1964)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 108))(*(_DWORD *)(uintptr_t)(self + 1964))
           || (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 96))(*(_DWORD *)(uintptr_t)(self + 1956)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956))
           || !(*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                 *(_DWORD *)(uintptr_t)(self + 1964),
                 self + 2095,
                 *(_DWORD *)(uintptr_t)(self + 1956),
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
        if ( *(_DWORD *)(uintptr_t)(self + 2171) )
          showFlags = 20480;
        overlayFlags = showFlags;
        updateResult = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                *(_DWORD *)(uintptr_t)(self + 1964),
                self + 2095,
                *(_DWORD *)(uintptr_t)(self + 1956),
                self + 2063,
                showFlags,
                0);
        if ( !updateResult
          || updateResult == -2005532222
          && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 96))(*(_DWORD *)(uintptr_t)(self + 1964)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 108))(*(_DWORD *)(uintptr_t)(self + 1964))
           || (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 96))(*(_DWORD *)(uintptr_t)(self + 1956)) == -2005532222
           && (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956))
           || !(*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                 *(_DWORD *)(uintptr_t)(self + 1964),
                 self + 2095,
                 *(_DWORD *)(uintptr_t)(self + 1956),
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
      ResetEvent(*(HANDLE *)(uintptr_t)(self + 2196));
      result = *(_DWORD *)(uintptr_t)(self + 2021);
      *(_DWORD *)(uintptr_t)(self + 2054) = result;
    }
  }
  return result;
}
// 468281: conditional instruction was optimized away because dh.1!=0
// 4682CF: variable 'v6' is possibly undefined

//----- (00468890) --------------------------------------------------------
int  CAviDecompressor_PresentFrameForRect(int player, const RECT *destRect)
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
  _DWORD sehFrame[3]; // [esp+198h] [ebp-24h] BYREF
  int ehState; // [esp+1A4h] [ebp-18h]

  v2 = player;
  result = (int)(intptr_t)sehFrame;
  sehFrame[0] = NtCurrentTeb()->NtTib.ExceptionList;
  sehFrame[1] = &j____wcpp_4_fs_handler_rtn_;
  sehFrame[2] = &g_AviPresentFrameForRect_EHFrame;
  ehState = 0;
  if ( !*(_BYTE *)(uintptr_t)(v2 + 2062) )
    result = AviPlayer_RenderFrame(v2, destRect);
  self = v2;
  if ( *(_BYTE *)(uintptr_t)(v2 + 1968) && *(_DWORD *)(uintptr_t)(v2 + 1964) )
  {
    destWidthScaled = 1000 * AviPlayer_SpanDelta(v2, (_DWORD *)(uintptr_t)(v2 + 2063));
    result = destWidthScaled / AviPlayer_SpanDelta(v6, (_DWORD *)(uintptr_t)(v6 + 2079));
    if ( result < *(_DWORD *)(uintptr_t)(v7 + 2143) || result > *(_DWORD *)(uintptr_t)(v7 + 2147) )
    {
      if ( *(_BYTE *)(uintptr_t)(self + 1968) )
      {
        if ( *(_DWORD *)(uintptr_t)(self + 1964) )
        {
          result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                     *(_DWORD *)(uintptr_t)(self + 1964),
                     self + 2095,
                     *(_DWORD *)(uintptr_t)(self + 1956),
                     self + 2063,
                     512,
                     0);
          if ( result )
          {
            if ( result != -2005532222
              || ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 96))(*(_DWORD *)(uintptr_t)(self + 1964)) != -2005532222
               || (result = (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 108))(*(_DWORD *)(uintptr_t)(self + 1964))) == 0)
              && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 96))(*(_DWORD *)(uintptr_t)(self + 1956)) != -2005532222
               || (result = (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956))) == 0)
              && (result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                             *(_DWORD *)(uintptr_t)(self + 1964),
                             self + 2095,
                             *(_DWORD *)(uintptr_t)(self + 1956),
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
      if ( *(_DWORD *)(uintptr_t)(v7 + 2171) )
        showFlags = 20480;
      overlayFlags = showFlags;
      result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                 *(_DWORD *)(uintptr_t)(self + 1964),
                 self + 2095,
                 *(_DWORD *)(uintptr_t)(self + 1956),
                 self + 2063,
                 showFlags,
                 0);
      if ( result )
      {
        if ( result != -2005532222
          || ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 96))(*(_DWORD *)(uintptr_t)(self + 1964)) != -2005532222
           || (result = (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 108))(*(_DWORD *)(uintptr_t)(self + 1964))) == 0)
          && ((*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 96))(*(_DWORD *)(uintptr_t)(self + 1956)) != -2005532222
           || (result = (*(int (__stdcall **)(_DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1956) + 108))(*(_DWORD *)(uintptr_t)(self + 1956))) == 0)
          && (result = (*(int (__stdcall **)(_DWORD, int, _DWORD, int, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 1964) + 132))(
                         *(_DWORD *)(uintptr_t)(self + 1964),
                         self + 2095,
                         *(_DWORD *)(uintptr_t)(self + 1956),
                         self + 2063,
                         overlayFlags,
                         0)) != 0 )
        {
          ExcString_Ctor();
          ehState = v10;
          ExcString_Ctor();
          ehState = 0;
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
  if ( *(_DWORD *)(uintptr_t)(result + 2171) )
  {
    colorKeyFlags = 8;
    prevFlagsByte = *(_BYTE *)(uintptr_t)(result + 2112);
    colorKeyHigh = *(_DWORD *)(uintptr_t)(result + 2046);
    *(_BYTE *)(uintptr_t)(result + 2115) |= 1u;
    result = *(_DWORD *)(uintptr_t)(result + 2042);
    *(_BYTE *)(uintptr_t)(self + 2112) = prevFlagsByte | 0x80;
    if ( result == colorKeyHigh )
      colorKeyFlags = 9;
    overlaySurface = *(_DWORD *)(uintptr_t)(self + 1964);
    if ( overlaySurface )
      result = (*(int (__stdcall **)(int, int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)overlaySurface + 116))(overlaySurface, colorKeyFlags, self + 2042);
    backSurface = *(_DWORD *)(uintptr_t)(self + 2017);
    if ( backSurface )
      return (*(int (__stdcall **)(int, int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)backSurface + 116))(backSurface, colorKeyFlags, self + 2042);
  }
  return result;
}

//----- (00468C40) --------------------------------------------------------
char  AviPlayer_ComputeFlipState(int player)
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

  self = player;
  decodedFrameBuffer = *(_DWORD *)(uintptr_t)(player + 2179);
  *(_BYTE *)(uintptr_t)(player + 2033) = 0;
  if ( decodedFrameBuffer )
  {
    *(_BYTE *)(uintptr_t)(player + 2033) = 1;
    return player;
  }
  v3 = player;
  v4 = player;
  if ( *(_BYTE *)(uintptr_t)(player + 2052) )
  {
    v8 = player;
    if ( !AviPlayer_IsIcmDecoderIdle(player) || !AviPlayer_TestModeFlagBit3(self) )
    {
      LOBYTE(player) = AviPlayer_IsIcmDecoderIdle(v8);
      if ( (_BYTE)player )
        goto LABEL_16;
      LOBYTE(player) = AviPlayer_TestModeFlagBit2(v8);
      if ( !(_BYTE)player )
      {
        *(_BYTE *)(uintptr_t)(self + 2033) = 2;
        return player;
      }
    }
  }
  if ( !*(_BYTE *)(uintptr_t)(v4 + 2052) )
  {
    LOBYTE(player) = AviPlayer_TestModeFlagBit2(v4);
    if ( !(_BYTE)player )
      goto LABEL_16;
    LOBYTE(player) = AviPlayer_IsUncompressedFormat(v9);
    if ( !(_BYTE)player )
    {
      *(_BYTE *)(uintptr_t)(self + 2033) = 2;
      return player;
    }
  }
  LOBYTE(player) = *(_BYTE *)(uintptr_t)(v3 + 1968);
  if ( !(_BYTE)player
    || !*(_DWORD *)(uintptr_t)(v3 + 1964)
    || (destWidthScaled = 1000 * AviPlayer_SpanDelta(self, (_DWORD *)(uintptr_t)(v3 + 2063)),
        player = destWidthScaled / AviPlayer_SpanDelta(v6, (_DWORD *)(uintptr_t)(v3 + 2079)),
        player < *(_DWORD *)(uintptr_t)(v3 + 2143))
    || player > *(_DWORD *)(uintptr_t)(v3 + 2147) )
  {
    if ( *(_DWORD *)(uintptr_t)(v3 + 1964) )
    {
      overlayCaps = *(_DWORD *)(uintptr_t)(v3 + 2171);
      LOBYTE(overlayCaps) = overlayCaps | 2;
      player = *(_DWORD *)(uintptr_t)(v3 + 2175) | overlayCaps;
      if ( (player & *(_DWORD *)(uintptr_t)(v3 + 2119)) != player )
      {
        *(_BYTE *)(uintptr_t)(self + 2033) = 2;
        return player;
      }
      goto LABEL_8;
    }
LABEL_16:
    *(_BYTE *)(uintptr_t)(self + 2033) = 2;
    return player;
  }
LABEL_8:
  if ( !*(_BYTE *)(uintptr_t)(self + 1968) || !*(_DWORD *)(uintptr_t)(self + 1964) )
  {
    if ( *(_DWORD *)(uintptr_t)(self + 1964) )
    {
      requiredCaps = *(_DWORD *)(uintptr_t)(self + 2171);
      LOBYTE(requiredCaps) = requiredCaps | 2;
      player = *(_DWORD *)(uintptr_t)(self + 2175) | requiredCaps;
      if ( (player & *(_DWORD *)(uintptr_t)(self + 2119)) == player )
        *(_BYTE *)(uintptr_t)(self + 2033) = 3;
    }
  }
  return player;
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
  (*(void (__stdcall **)(int, int *, int *))(uintptr_t)(*(_DWORD *)(uintptr_t)v19 + 44))(v19, &driverCaps, helCaps);
  memset_(v20, 0);
  surfaceDesc[0] = 108;
  (*(void (__stdcall **)(_DWORD, _DWORD *))(uintptr_t)(**(_DWORD **)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1956) + 88))(
    *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1956),
    surfaceDesc);
  if ( (a15 & 0x800000000000000LL) != 0 )
    capsFlags = 1;
  else
    capsFlags = 256;
  *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) = capsFlags;
  if ( (a15 & 0x200000000000000LL) != 0 )
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2121) |= 1u;
  v23 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2123) = *(_DWORD *)((char *)&a13 + 2);
  if ( *(_DWORD *)((char *)&a13 + 2) == 8 )
  {
    *(_BYTE *)(uintptr_t)(v23 + 2120) |= 2u;
  }
  else
  {
    *(_DWORD *)(uintptr_t)(v23 + 2127) = *(_DWORD *)((char *)&a13 + 6);
    *(_DWORD *)(uintptr_t)(v23 + 2131) = *(_DWORD *)((char *)&a14 + 2);
    *(_DWORD *)(uintptr_t)(v23 + 2135) = *(_DWORD *)((char *)&a14 + 6);
    *(_DWORD *)(uintptr_t)(v23 + 2139) = *(_DWORD *)((char *)&a15 + 2);
  }
  if ( (v62 & 0x40) != 0 )
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 2u;
  if ( (v63 & 2) != 0 )
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 4u;
  if ( v62 < 0 )
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x80u;
  if ( (v63 & 8) != 0 )
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 0x20u;
  if ( (v63 & 0x40) != 0 )
  {
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 0x40u;
    v24 = *(_DWORD *)((char *)&a18 + 6);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2143) = minStretchRate;
    *(_DWORD *)(uintptr_t)(v24 + 2147) = maxStretchRate;
  }
  if ( (v64 & 0x40) != 0 )
  {
    if ( (v66 & 2) != 0 )
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 8u;
    if ( (v66 & 0x20) != 0 )
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 0x80u;
  }
  if ( (v62 & 0x16) != 0 )
  {
    v25 = *(_DWORD *)((char *)&a18 + 6);
    *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2121) |= 2u;
    *(_BYTE *)(uintptr_t)(v25 + 2120) &= 0x1Fu;
  }
  if ( v65 < 0 )
  {
    if ( (v67 & 0x40) != 0 )
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x10u;
    if ( (v68 & 2) != 0 )
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x20u;
    if ( (v69 & 0x40) != 0 )
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) |= 0x40u;
  }
  if ( (*(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2119) & 1) != 0 || (v65 & 8) == 0 )
  {
    if ( !(*(int (__stdcall **)(_DWORD, _DWORD, _DWORD *, int, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6)
                                                                                    + 1956)
                                                                      + 100))(
            *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1956),
            0,
            surfaceDesc,
            1,
            0) )
    {
      v26 = *(_DWORD *)((char *)&a18 + 6);
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 4u;
      (*(void (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(v26 + 1956) + 128))(*(_DWORD *)(uintptr_t)(v26 + 1956), 0);
    }
    if ( !(*(int (__stdcall **)(_DWORD, char *))(uintptr_t)(**(_DWORD **)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1956) + 68))(
            *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1956),
            (char *)&a18 + 2) )
    {
      v27 = *(_DWORD *)((char *)&a18 + 6);
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) |= 8u;
      (*(void (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(v27 + 1952) + 104))(
        *(_DWORD *)(uintptr_t)(v27 + 1952),
        *(_DWORD *)((char *)&a18 + 2));
    }
  }
  AviPlayer_AllocDecodedBitmapInfo(*(int *)((char *)&a18 + 6), v21);
  v28 = *(_DWORD *)((char *)&a18 + 6);
  videoFormat = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 151);
  *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2052) = 0;
  biCompression = *(_DWORD *)(uintptr_t)(videoFormat + 16);
  if ( !biCompression || biCompression == 3 )
  {
    CAviDecompressor_SetupBlitFormat(
      (int (*)())(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1924),
      *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2058),
      0,
      *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 151),
      0);
  }
  else
  {
    if ( AviPlayer_OpenVideoCodec(
           v28 + 415,
           *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 15),
           *(int **)(uintptr_t)(v28 + 2058),
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
    if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 415) )
      return 0;
    decodedFormatPtr = *(_DWORD *)((char *)&a18 + 6) + 423;
    frameBufferAlloc = j_Mem_Alloc(0);
    *(_DWORD *)(uintptr_t)(HIDWORD(frameBufferAlloc) + 2179) = frameBufferAlloc;
    CAviDecompressor_SetupBlitFormat((int (*)())(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 1924), *(_DWORD *)(uintptr_t)(HIDWORD(frameBufferAlloc) + 2058), v41, decodedFormatPtr, 0);
  }
  *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2052) = 1;
LABEL_39:
  v31 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2095) = 0;
  *(_DWORD *)(uintptr_t)(v31 + 2099) = 0;
  v32 = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2103) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v31 + 151) + 4);
  frameHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v32 + 151) + 8);
  LODWORD(frameHeight) = (HIDWORD(frameHeight) ^ frameHeight) - HIDWORD(frameHeight);
  HIDWORD(frameHeight) = *(_DWORD *)((char *)&a18 + 6);
  *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2107) = frameHeight;
  if ( *(_BYTE *)(uintptr_t)(HIDWORD(frameHeight) + 2062) )
  {
    if ( !*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2071) && !*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2075) )
    {
      v34 = *(_DWORD *)((char *)&a18 + 6);
      *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2071) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 151)
                                                                    + 4)
                                                        + *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2063);
      frameHeight2 = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v34 + 151) + 8);
      *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2075) = (HIDWORD(frameHeight2) ^ frameHeight2)
                                                        - HIDWORD(frameHeight2)
                                                        + *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2067);
    }
    *(_DWORD *)((char *)&a16 + 2) = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2063);
    *(_DWORD *)((char *)&a16 + 6) = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2067);
    *(_DWORD *)((char *)&a16 + 10) = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2071);
    *(_DWORD *)((char *)&a16 + 14) = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2075);
    AviPlayer_RenderFrame(*(int *)((char *)&a18 + 6), (const RECT *)((char *)&a16 + 2));
    stretchRatio = 1000
        * (*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2071) - *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2063))
        / (*(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2087) - *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2079));
    if ( stretchRatio < *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2143)
      || stretchRatio > *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2147) )
    {
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) &= 0x1Fu;
    }
  }
  else
  {
    v42 = *(_DWORD *)((char *)&a18 + 6);
    v43 = *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2143);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2175) = 4;
    if ( v43 > 1000 || *(int *)(uintptr_t)(v42 + 2147) < 4000 )
      *(_BYTE *)(uintptr_t)(*(_DWORD *)((char *)&a18 + 6) + 2120) &= 0x1Fu;
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
  surfaceDesc[3] = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4);
  biHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 8);
  surfaceDesc[2] = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
  surfaceDesc[1] = 7;
  surfaceDesc[26] = 2112;
  if ( (*(int (__stdcall **)(int, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)v4 + 24))(v4, surfaceDesc, self + 2013, 0) )
  {
    ExcString_Ctor();
    v9 = 1;
    ExcString_Ctor();
    surfaceDesc[52] = v6;
    v9 = 0;
    return CRT_ThrowExcStringException();
  }
  else if ( (***(int (__stdcall ****)(_DWORD, void *, int))(uintptr_t)(self + 2013))(*(_DWORD *)(uintptr_t)(self + 2013), &g_AviQueryInterfaceIid, self + 2017) )
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
    result = (*(int (__stdcall **)(_DWORD, _DWORD))(uintptr_t)(**(_DWORD **)(uintptr_t)(self + 2017) + 148))(*(_DWORD *)(uintptr_t)(self + 2017), 0);
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
  surfaceDesc[3] = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4);
  biHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 8);
  surfaceDesc[2] = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
  surfaceDesc[1] = 7;
  surfaceDesc[26] = 16448;
  result = (*(int (__stdcall **)(int, _DWORD *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)v5 + 24))(v5, surfaceDesc, self + 1960, 0);
  if ( !result )
    return (***(int (__stdcall ****)(_DWORD, void *, int))(uintptr_t)(self + 1960))(*(_DWORD *)(uintptr_t)(self + 1960), &g_AviQueryInterfaceIid, self + 1964);
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
  surfaceWidth = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4);
  biHeight = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 8);
  surfaceHeight = (HIDWORD(biHeight) ^ biHeight) - HIDWORD(biHeight);
  backBufferCount = 1;
  descFlags = 39;
  surfaceCaps = 16536;
  memset_(v4, 0);
  descSize = 108;
  surfaceWidth = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 4);
  biHeightRetry = *(int *)(uintptr_t)(*(_DWORD *)(uintptr_t)(self + 151) + 8);
  surfaceHeight = (HIDWORD(biHeightRetry) ^ biHeightRetry) - HIDWORD(biHeightRetry);
  surfaceCaps = 16512;
  descFlags = 7;
  result = (*(int (__stdcall **)(int, int *, int, _DWORD))(uintptr_t)(*(_DWORD *)(uintptr_t)v6 + 24))(v6, &descSize, self + 1960, 0);
  if ( !result )
  {
    result = (***(int (__stdcall ****)(_DWORD, void *, int))(uintptr_t)(self + 1960))(*(_DWORD *)(uintptr_t)(self + 1960), &g_AviQueryInterfaceIid, self + 1964);
    *(_BYTE *)(uintptr_t)(self + 1968) = 1;
    *(_BYTE *)(uintptr_t)(self + 2051) = 0;
  }
  return result;
}
// 4695F4: variable 'v4' is possibly undefined
// 46963F: variable 'v6' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
