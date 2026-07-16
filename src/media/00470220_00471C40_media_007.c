/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "media_internal.h"
#include "media_state.h"
#include "../state/state_shared.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00470220) --------------------------------------------------------
unsigned int __cdecl CSS_OpenWaveOutDevice(int driver CLASH95_UNUSED, char format_flags)
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
      g_CSS_WaveBufferMemHandles[buffer_index] = (int)(intptr_t)buffer_mem_handle;
      if ( !buffer_mem_handle )
        return 2;
      buffer_ptr = GlobalLock(buffer_mem_handle);
      g_CSS_WaveBufferDataPtrs[buffer_index] = (int)(intptr_t)buffer_ptr;
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
        g_CSS_WaveHeaderMemHandles[header_index] = (int)(intptr_t)header_mem_handle;
        if ( !header_mem_handle )
          return 2;
        wave_header = (struct wavehdr_tag *)GlobalLock(header_mem_handle);
        *(LPWAVEHDR *)((char *)&pwh + header_index * 4) = wave_header;
        if ( !wave_header )
          return 43;
        wave_header->lpData = (LPSTR)(uintptr_t)g_CSS_WaveBufferDataPtrs[header_index];
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
signed int CSS_CloseWaveOutDevice(void)
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
    while ( (GlobalUnlock((HGLOBAL)(uintptr_t)g_CSS_WaveBufferMemHandles[buffer_index]) || !GetLastError()) && !GlobalFree((HGLOBAL)(uintptr_t)g_CSS_WaveBufferMemHandles[buffer_index]) )
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
      for ( i = 0; (GlobalUnlock((HGLOBAL)(uintptr_t)g_CSS_WaveHeaderMemHandles[i]) || !GetLastError()) && !GlobalFree((HGLOBAL)(uintptr_t)g_CSS_WaveHeaderMemHandles[i]); ++i )
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
      pwh[g_WaveOutBufferRingIndex]->lpData = (LPSTR)(uintptr_t)g_CSS_WaveBufferDataPtrs[g_WaveOutBufferRingIndex];
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
int CSS_FreeMixBuffers(void)
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
int CSS_FreeMixChannels(void)
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
int CSS_ResetAllMixChannels(void)
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
        *(_DWORD *)(uintptr_t)(table_write_ptr - 4) = scaled_value;
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
  *(_DWORD *)(uintptr_t)(channel_offset + g_CssMixChannels + 96) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 68) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 72) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 4) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 60) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 64) = 1;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 76) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 92) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 104) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 48) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 12) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 16) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 20) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 24) = 0;
  *(_DWORD *)(uintptr_t)(channel_offset + result + 8) = 0;
  return result;
}
// 54DB90: using guessed type int dword_54DB90;

//----- (00470E60) --------------------------------------------------------
void __cdecl CSS_StartMixChannelPlayback(unsigned int channel_index, int playback_rate)
{
  if ( channel_index < g_CssMixChannelCount )
  {
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 96) = 2;
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
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + channel_offset + 12) = 1;
    *(_DWORD *)(uintptr_t)(channels_base + channel_offset + 16) = loop_start;
    if ( loop_end == -1 )
      resolved_end = *(_DWORD *)(uintptr_t)(channels_base + channel_offset + 8);
    v6 = 108 * channel_index;
    v7 = g_CssMixChannels;
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + v6 + 20) = resolved_end;
    *(_DWORD *)(uintptr_t)(v7 + v6 + 24) = 1;
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
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + result + 12) = 0;
    *(_DWORD *)(uintptr_t)(channels_base + result + 16) = 0;
    *(_DWORD *)(uintptr_t)(channels_base + result + 20) = 0;
    *(_DWORD *)(uintptr_t)(channels_base + result + 24) = 0;
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
    *loop_start_out = *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 16);
    result = *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 20);
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
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 96) = 0;
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
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 96) = 3;
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
  return *(_DWORD *)(uintptr_t)(channel_base + 96) == 3 || *(_DWORD *)(uintptr_t)(channel_base + 96) == 2;
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
    channel = (_DWORD *)(uintptr_t)(108 * channel_index + g_CssMixChannels);
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
      result = (_DWORD *)(uintptr_t)(channel_offset + g_CssMixChannels);
      new_volume = *(_DWORD *)(uintptr_t)(channel_offset + g_CssMixChannels + 80);
      if ( *(int *)(uintptr_t)(channel_offset + g_CssMixChannels + 84) <= 0 )
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
    *(_DWORD *)(uintptr_t)(result + 60) = rate;
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
    if ( *(_DWORD *)(uintptr_t)(channel_base + 96) > 1u )
      *rate_out = *(_DWORD *)(uintptr_t)(channel_base + 60);
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
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 80) = 1000 * volume;
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
    result = *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 80) / 0x3E8u;
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
    channel = (_DWORD *)(uintptr_t)(108 * channel_index + g_CssMixChannels);
    queue_slot = g_CSS_QueuedSoundSlotTable + 40 * (queue_slot_index - 1);
    channel[17] = queue_slot_index;
    channel[18] = 1;
    if ( *(_DWORD *)(uintptr_t)(queue_slot + 12) == 5 && channel[24] == 1 )
    {
      channel[24] = 3;
      CSS_ChannelSetPlayPosition(channel_index, *(_DWORD *)(uintptr_t)(queue_slot + 16));
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
  slot = (_DWORD *)(uintptr_t)(40 * (ring_index - 1) + g_CSS_QueuedSoundSlotTable);
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

  result = (_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index);
  queue_slot = (_DWORD *)(uintptr_t)(g_CSS_QueuedSoundSlotTable + 40 * (result[17] - 1));
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
    channel = (int *)(uintptr_t)(g_CssMixChannels + 108 * channel_index);
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
    result = *(_DWORD *)(uintptr_t)(channel_base + 48) << CSS_GetFormatTableValue(*(_DWORD *)(uintptr_t)(channel_base + 4));
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
    if ( *(_DWORD *)(uintptr_t)(channel_base + 4) != 1 && *(_DWORD *)(uintptr_t)(channel_base + 4) != 2 && *(_DWORD *)(uintptr_t)(channel_base + 4) != 5 && panning == 128 )
      adjusted_panning = 0;
    *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 76) = adjusted_panning;
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
    result = *(_DWORD *)(uintptr_t)(g_CssMixChannels + 108 * channel_index + 76);
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
        if ( !*(_DWORD *)(uintptr_t)(channel_offset + g_CssMixChannels + 92) && !g_CSS_MixIdleChannelFlag )
          a1 = 1000;
        channel_offset += 108;
        Audio_MixResampledVoice((int *)(uintptr_t)a1);
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
    channel = (_DWORD *)(uintptr_t)(108 * channel_index + g_CssMixChannels);
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
    *(_DWORD *)(uintptr_t)(channel_base + 56) = a2 >> CSS_GetFormatTableValue(*(_DWORD *)(uintptr_t)(channel_base + 4));
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
