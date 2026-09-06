/* Generated from src/recovered/runtime/00461520_platform_input.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00463220) --------------------------------------------------------
__int16  CAviDecompressor_SetupBlitFormat(int (*blitDesc)(), int dstBmiHeader, int dstPitch, int srcBmiHeader, int srcPitch)
{
  int (*desc)(); // esi
  int dstCompression; // ecx
  unsigned int srcBitCount; // edi
  int srcCompression; // ecx
  int v10; // ecx
  int srcBitDepth; // ecx
  int srcBlueMaskTmp; // eax
  int srcStride; // eax
  int srcHeight; // ebx
  int dstHeight; // ecx
  int absHeight; // eax
  int dstStride; // eax
  int srcRedMask; // [esp+0h] [ebp-28h] BYREF
  int srcGreenMask; // [esp+4h] [ebp-24h]
  int srcBlueMask; // [esp+8h] [ebp-20h]
  int dstRedMask; // [esp+Ch] [ebp-1Ch] BYREF
  int dstGreenMask; // [esp+10h] [ebp-18h]
  int dstBlueMask; // [esp+14h] [ebp-14h]
  int dstBitCount; // [esp+18h] [ebp-10h]

  desc = blitDesc;
  dstCompression = *(_DWORD *)(uintptr_t)(dstBmiHeader + 16);
  LOWORD(blitDesc) = *(_WORD *)(uintptr_t)(dstBmiHeader + 14);
  srcBitCount = *(unsigned __int16 *)(uintptr_t)(srcBmiHeader + 14);
  dstBitCount = (unsigned __int16)(intptr_t)blitDesc;
  if ( dstCompression && dstCompression != 3 )
    return (__int16)(intptr_t)blitDesc;
  srcCompression = *(_DWORD *)(uintptr_t)(srcBmiHeader + 16);
  if ( srcCompression )
  {
    if ( srcCompression != 3 )
      return (__int16)(intptr_t)blitDesc;
  }
  v10 = *(_DWORD *)(uintptr_t)(dstBmiHeader + 16);
  if ( v10 )
  {
    dstRedMask = *(_DWORD *)(uintptr_t)(dstBmiHeader + 40);
    dstGreenMask = *(_DWORD *)(uintptr_t)(dstBmiHeader + 44);
    dstBlueMask = *(_DWORD *)(uintptr_t)(dstBmiHeader + 48);
  }
  else
  {
    LOWORD(v10) = *(_WORD *)(uintptr_t)(dstBmiHeader + 14);
    if ( (unsigned __int16)v10 == 16 )
    {
      dstRedMask = 63488;
      dstGreenMask = 2016;
      dstBlueMask = 31;
    }
    else if ( v10 == 24 )
    {
      dstRedMask = 16711680;
      dstGreenMask = 65280;
      dstBlueMask = 255;
    }
    else
    {
      dstRedMask = 1 << v10;
      dstGreenMask = 1 << v10;
      dstBlueMask = 1 << v10;
    }
  }
  if ( *(_DWORD *)(uintptr_t)(srcBmiHeader + 16) )
  {
    srcRedMask = *(_DWORD *)(uintptr_t)(srcBmiHeader + 40);
    srcGreenMask = *(_DWORD *)(uintptr_t)(srcBmiHeader + 44);
    srcBlueMaskTmp = *(_DWORD *)(uintptr_t)(srcBmiHeader + 48);
  }
  else
  {
    srcBitDepth = *(unsigned __int16 *)(uintptr_t)(srcBmiHeader + 14);
    if ( (unsigned __int16)srcBitDepth == 16 )
    {
      srcRedMask = 63488;
      srcBlueMaskTmp = 31;
      srcGreenMask = 2016;
    }
    else
    {
      if ( srcBitDepth == 24 )
      {
        srcRedMask = 16711680;
        srcGreenMask = 65280;
        srcBlueMask = 255;
        goto LABEL_12;
      }
      srcBlueMaskTmp = 1 << srcBitDepth;
      srcRedMask = 1 << srcBitDepth;
      srcGreenMask = 1 << srcBitDepth;
    }
  }
  srcBlueMask = srcBlueMaskTmp;
LABEL_12:
  *(_DWORD *)desc = *(_DWORD *)(uintptr_t)(srcBmiHeader + 4);
  if ( srcPitch )
  {
    srcStride = srcPitch;
  }
  else
  {
    srcStride = *(_DWORD *)desc * ((int)(srcBitCount + 7) >> 3) + 3;
    LOBYTE(srcStride) = srcStride & 0xFC;
  }
  *((_DWORD *)desc + 2) = srcStride;
  if ( !dstPitch )
  {
    dstStride = *(_DWORD *)desc * ((dstBitCount + 7) >> 3) + 3;
    LOBYTE(dstStride) = dstStride & 0xFC;
    dstPitch = dstStride;
  }
  *((_DWORD *)desc + 3) = dstPitch;
  srcHeight = *(_DWORD *)(uintptr_t)(srcBmiHeader + 8);
  dstHeight = *(_DWORD *)(uintptr_t)(dstBmiHeader + 8);
  if ( srcHeight < 0 )
    absHeight = -srcHeight;
  else
    absHeight = srcHeight;
  *((_DWORD *)desc + 1) = absHeight;
  if ( srcRedMask == dstRedMask && srcGreenMask == dstGreenMask && srcBlueMask == dstBlueMask )
  {
    LOWORD(blitDesc) = dstHeight * srcHeight;
    if ( dstHeight * srcHeight <= 0 )
    {
      if ( srcBitCount >= 0x18 )
      {
        if ( srcBitCount <= 0x18 )
        {
          *((_DWORD *)desc + 5) = (_DWORD)(uintptr_t)CAviDecompressor_CopyPixelRow24bpp;
        }
        else if ( srcBitCount == 32 )
        {
          *((_DWORD *)desc + 5) = (_DWORD)(uintptr_t)CAviDecompressor_CopyPixelRow32bpp;
        }
      }
      else if ( srcBitCount == 16 )
      {
        *((_DWORD *)desc + 5) = (_DWORD)(uintptr_t)CAviDecompressor_CopyPixelRow16bpp;
      }
    }
    else
    {
      *((_DWORD *)desc + 4) = (int)(srcBitCount + 7) >> 3;
    }
  }
  else
  {
    blitDesc = CAviDecompressor_FindColorConvertRoutine((int (**)())&srcRedMask, (int (**)())&dstRedMask);
    *((_DWORD *)desc + 5) = (_DWORD)(uintptr_t)blitDesc;
  }
  if ( srcHeight >= 0 )
  {
    if ( dstHeight >= 0 )
      return (__int16)(intptr_t)blitDesc;
    goto LABEL_47;
  }
  *((_DWORD *)desc + 2) = -*((_DWORD *)desc + 2);
  if ( dstHeight < 0 )
LABEL_47:
    *((_DWORD *)desc + 3) = -*((_DWORD *)desc + 3);
  return (__int16)(intptr_t)blitDesc;
}
// 46333D: variable 'v15' is possibly undefined

//----- (004634A0) --------------------------------------------------------
signed int  CAviDecompressor_BlitRows(_DWORD *blitDesc, char *dest, char *src)
{
  _DWORD *desc; // ecx
  int bytesPerPixel; // edx
  char *destRow; // esi
  char *srcRow; // edi
  signed int result; // eax
  int i; // ebp

  desc = blitDesc;
  bytesPerPixel = blitDesc[4];
  if ( bytesPerPixel )
  {
    result = blitDesc[1] * *blitDesc * bytesPerPixel;
    qmemcpy(dest, src, result);
  }
  else
  {
    destRow = dest;
    srcRow = src;
    if ( (int)blitDesc[2] < 0 )
      srcRow = &src[(blitDesc[1] - 1) * -blitDesc[2]];
    result = blitDesc[3];
    if ( result < 0 )
      destRow += -result * (desc[1] - 1);
    for ( i = 0; i < desc[1]; destRow += desc[3] )
    {
      ++i;
      ((void (__fastcall *)(_DWORD *, char *))(uintptr_t)desc[5])(desc, srcRow);
      result = desc[2];
      srcRow += result;
    }
  }
  return result;
}
// 4634D1: variable 'v3' is possibly undefined

//----- (004635A0) --------------------------------------------------------
unsigned int  CAviDecompressor_NormalizeColorMask(unsigned int mask)
{
  char shiftCount; // cl
  char lowBit; // cf

  shiftCount = 0;
  do
  {
    ++shiftCount;
    lowBit = mask & 1;
    mask >>= 1;
  }
  while ( !lowBit );
  return mask << shiftCount;
}
