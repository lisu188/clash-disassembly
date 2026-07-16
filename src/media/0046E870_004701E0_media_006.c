/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
#include "../recovered_internal.h"

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
