/* Generated from src/recovered/media/004637B0_media.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "0046B610_0046E5D0_media_005_local.h"
#include "media_internal.h"
#include "media_state.h"
#include "media_shared_state.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

CLASH95_LOCAL int Audio_MixVoiceSpanDispatch_46BB40 (int stepFixed, int sampleCount, char accumFlag, void *accumBuffer);
CLASH95_LOCAL unsigned int Audio_MixVoiceSpanDispatch_46BB9A (unsigned int result, int stepFixed, unsigned int sampleCount, short int volumeAndFlag, void *accumBuffer);

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
  g_Audio_MixVoice_MixFunc = (int (__fastcall *)(_DWORD, _DWORD))(uintptr_t)mixArgs[3];
  channel = (unsigned int *)(uintptr_t)(108 * mixArgs[2] + g_CssMixChannels);
  g_Audio_CurrentVoiceRecordPtr = (int)(intptr_t)channel;
  g_Audio_MixVoice_LoopCallback = (int (__cdecl *)(_DWORD))(uintptr_t)channel[26];
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
                      && ((queueSlot = 40 * channel[17] + g_CSS_QueuedSoundSlotTable, *(_DWORD *)(uintptr_t)(queueSlot + 12) == 4) || *(_DWORD *)(uintptr_t)(queueSlot + 12) == 5);
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
                Audio_ZeroMixAccumulatorBuffer(spanSamples, (void *)(uintptr_t)g_Audio_MixVoice_AccumBufferPtr);
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
    Audio_ZeroMixAccumulatorBuffer(g_Audio_MixVoice_SamplesRemaining, (void *)(uintptr_t)g_Audio_MixVoice_AccumBufferPtr);
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

  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_MixMonoVoiceDispatchBase;
  if ( sampleCount )
  {
    if ( !accumFlag )
      memset(accumBuffer, 0, 4 * sampleCount);
    mixInnerFunc = *(int (__thiscall **)(signed int))(uintptr_t)(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
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

  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_MixPannedVoiceDispatchBase;
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
    mixInnerFunc = *(int (__thiscall **)(unsigned int))(uintptr_t)(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
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
CLASH95_LOCAL int Audio_MixVoiceSpanDispatch_46BB40(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  int (__thiscall *mixInnerFunc)(signed int); // eax
  int result; // eax

  if ( sampleCount )
  {
    if ( !accumFlag )
      memset(accumBuffer, 0, 4 * sampleCount);
    mixInnerFunc = *(int (__thiscall **)(signed int))(uintptr_t)(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
    g_Audio_MixVoice_StepIntArg = stepFixed >> 16;
    return mixInnerFunc(stepFixed << 16);
  }
  return result;
}

CLASH95_LOCAL unsigned int Audio_MixVoiceSpanDispatch_46BB9A(
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
    mixInnerFunc = *(int (__thiscall **)(unsigned int))(uintptr_t)(g_Audio_MixFormatDispatchTable + -4 * (sampleCount & 3) + 16);
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
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat1MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46BDD1: using guessed type void *off_46BDD1;
// 519B94: using guessed type int dword_519B94;

//----- (0046BF5E) --------------------------------------------------------
unsigned int Audio_SelectMixFormat1Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat1StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46BE97: using guessed type void *off_46BE97;
// 519B94: using guessed type int dword_519B94;

//----- (0046C030) --------------------------------------------------------
int Audio_SelectMixFormat2Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat2MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46BF6D: using guessed type void *off_46BF6D;
// 519B94: using guessed type int dword_519B94;

//----- (0046C1A2) --------------------------------------------------------
unsigned int Audio_SelectMixFormat2Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat2StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46C03F: using guessed type void *off_46C03F;
// 519B94: using guessed type int dword_519B94;

//----- (0046C2FC) --------------------------------------------------------
int Audio_SelectMixFormat3Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat3MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46C1B1: using guessed type void *off_46C1B1;
// 519B94: using guessed type int dword_519B94;

//----- (0046C472) --------------------------------------------------------
unsigned int Audio_SelectMixFormat3Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat3StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46C30B: using guessed type void *off_46C30B;
// 519B94: using guessed type int dword_519B94;

//----- (0046C6B4) --------------------------------------------------------
int Audio_SelectMixFormat4Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat4MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46C481: using guessed type void *off_46C481;
// 519B94: using guessed type int dword_519B94;

//----- (0046C996) --------------------------------------------------------
unsigned int Audio_SelectMixFormat4Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat4StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46C6C3: using guessed type void *off_46C6C3;
// 519B94: using guessed type int dword_519B94;

//----- (0046CE10) --------------------------------------------------------
int Audio_SelectMixFormat5Mono(signed int stepFixed, int sampleCount, char accumFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat5MonoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB40(stepFixed, sampleCount, accumFlag, accumBuffer);
}
// 46C9A5: using guessed type void *off_46C9A5;
// 519B94: using guessed type int dword_519B94;

//----- (0046D2A6) --------------------------------------------------------
unsigned int Audio_SelectMixFormat5Stereo(unsigned int result, signed int stepFixed, unsigned int sampleCount, __int16 volumeAndFlag, void *accumBuffer)
{
  g_Audio_MixFormatDispatchTable = (int)(intptr_t)&g_Audio_SelectMixFormat5StereoDispatchBase;
  return Audio_MixVoiceSpanDispatch_46BB9A(result, stepFixed, sampleCount, volumeAndFlag, accumBuffer);
}
// 46CE1F: using guessed type void *off_46CE1F;
// 519B94: using guessed type int dword_519B94;

//----- (0046D2B5) --------------------------------------------------------
int __cdecl Audio_ClearGlobalMixBuffer(int sampleCount)
{
  Audio_ZeroMixAccumulatorBuffer(sampleCount, (void *)(uintptr_t)g_CSS_MixAccumBufferPtr);
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
int __cdecl Audio_SetMixerParamValue(int driver CLASH95_UNUSED, int volume)
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
    v3 = nmalloc_(v2, ((_DWORD)(uintptr_t)(ptrOut)));
    *(_DWORD *)(uintptr_t)HIDWORD(v3) = v3;
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
  *stream = ((_DWORD)(uintptr_t)(g_CSSFileStream_VTable));
  stream[2] = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)source + 4))();
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
    _wcpp_4_dtor_array_store__(a3, ((_DWORD)(uintptr_t)(&g_CSSFileStream_DtorArrayDescriptor)));
    j_j__nfree_();
    return stream;
  }
  else
  {
    *stream = ((_DWORD)(uintptr_t)(g_CSSFileStream_VTable));
    CSS_Mem_FreeIfSet(stream[15]);
    (*(void (__cdecl **)(int, int, int))(uintptr_t)(*(_DWORD *)(uintptr_t)g_MediaFileStreamProvider + 20))(a3, a5, a4);
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

  result = (*(int (__thiscall **)(int))(uintptr_t)(**(_DWORD **)(uintptr_t)(stream + 4) + 20))(stream);
  *(_DWORD *)(uintptr_t)(v2 + 8) += result;
  return result;
}
// 46D53C: variable 'v2' is possibly undefined

//----- (0046D550) --------------------------------------------------------
int  CSS_FileStream_FillWithLoopWrap(int stream, int loopStart, int fillBytes, int loopEnd)
{
  int readBytes; // ecx
  int bytesRead; // eax
  int v9; // ecx

  if ( fillBytes < loopEnd - *(_DWORD *)(uintptr_t)(stream + 8) )
    return CSS_FileStream_FillSequential(stream);
  readBytes = (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)(stream + 4) + 20))();
  (***(void (__fastcall ****)(int, int))(uintptr_t)(stream + 4))(readBytes, loopStart);
  bytesRead = (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)(stream + 4) + 20))();
  *(_DWORD *)(uintptr_t)(stream + 8) = bytesRead + loopStart;
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
    return CSS_FileStream_FillSequential((int)(intptr_t)stream);
  if ( stream[2] <= stream[6] )
    return CSS_FileStream_FillWithLoopWrap((int)(intptr_t)stream, stream[5], blockBytes, stream[6]);
  return CSS_FileStream_FillWithLoopWrap((int)(intptr_t)stream, stream[3], blockBytes, stream[4]);
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
    result = (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)v1 + 32))();
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
    qmemcpy(dest, (const void *)(uintptr_t)(stream[7] % stream[8] + stream[15]), contiguousBytes);
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
  return (*(int (**)(void))(uintptr_t)(*(_DWORD *)(uintptr_t)stream + 4))();
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
  return *(_DWORD *)(uintptr_t)(stream + 8) - *(_DWORD *)(uintptr_t)(stream + 12);
}

//----- (0046D8A0) --------------------------------------------------------
signed int  CSS_FileStream_DispatchIfInRange(int stream, int offset, int callbackArg)
{
  int basePos; // ecx
  int absPos; // edx

  basePos = *(_DWORD *)(uintptr_t)(stream + 12);
  absPos = basePos + offset;
  if ( absPos < basePos || absPos >= *(_DWORD *)(uintptr_t)(stream + 16) )
    return 0;
  (***(void (__cdecl ****)(int))(uintptr_t)(stream + 4))(callbackArg);
  return 1;
}

//----- (0046D8D0) --------------------------------------------------------
_DWORD * CSS_FileStream_New(int source, int bufferBytes)
{
  _DWORD *stream; // eax
  int v5; // edx
  int v6; // ecx

  stream = (_DWORD *)(uintptr_t)Mem_Alloc(64, bufferBytes, (char)(intptr_t)&j____wcpp_4_fs_handler_rtn_, 0);
  if ( stream )
    return CSS_FileStream_Create(stream, source, v6, v5);
  else
    return 0;
}
// 46D937: variable 'v6' is possibly undefined
// 46D937: variable 'v5' is possibly undefined

//----- (0046D960) --------------------------------------------------------
int CSS_InitStreamingLocks(void)
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
int CSS_StreamService_NoOpHook(void)
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
  channel = (int *)(uintptr_t)(result + g_SoundChannelArrayBase);
  if ( *(_DWORD *)(uintptr_t)(result + g_SoundChannelArrayBase + 40) )
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
        (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(uintptr_t)(*(_DWORD *)(uintptr_t)streamObj + 44))(
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
  bytesRead = (***(int (__fastcall ****)(int, int))(uintptr_t)(channel + 20))(channel, *(_DWORD *)(uintptr_t)(channel + 12) + *(_DWORD *)(uintptr_t)channel);
  *(_DWORD *)(uintptr_t)(v5 + 12) += bytesRead;
  if ( bytesRead >= byteCount )
    return 1;
  result = (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)(v5 + 20) + 4))();
  if ( result )
  {
    silenceBytes = byteCount - v6;
    memset_(v7, *(_DWORD *)(uintptr_t)(v7 + 24));
    *(_DWORD *)(uintptr_t)(v9 + 12) += silenceBytes;
    *(_DWORD *)(uintptr_t)(v9 + 28) += silenceBytes;
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
  if ( (!*(_DWORD *)(uintptr_t)(g_CSS_ActiveSoundDriver + 28) || *(_DWORD *)(uintptr_t)(channel + 28) >= *(_DWORD *)(uintptr_t)(channel + 8))
    && (*(int (**)(void))(uintptr_t)(**(_DWORD **)(uintptr_t)(channel + 20) + 8))() )
  {
    *(_DWORD *)(uintptr_t)(channel + 48) = 1;
    return;
  }
  if ( *(_DWORD *)(uintptr_t)channel && *(_DWORD *)(uintptr_t)(g_CSS_ActiveSoundDriver + 28) )
  {
    CSS_ChannelGetPlayPosition(channelIndex, ((_DWORD*)(&playPosOut)));
    if ( playPosOut )
      playPos = playPosOut;
    else
      playPos = *(_DWORD *)(uintptr_t)(channel + 8);
    writePos = *(_DWORD *)(uintptr_t)(channel + 12);
    bufferBytes = *(_DWORD *)(uintptr_t)(channel + 8);
    if ( playPos <= writePos )
    {
      savedPlayPos = playPos;
      leadBytes = bufferBytes - writePos;
      savedBufferBytes = bufferBytes;
      if ( bufferBytes - writePos > bufferBytes )
        leadBytes = bufferBytes;
      if ( !CSS_Channel_FillSilence(channel, leadBytes) )
        goto LABEL_15;
      *(_DWORD *)(uintptr_t)(v10 + 12) = 0;
      remainingBytes = savedBufferBytes - leadBytes;
      if ( !remainingBytes )
        goto LABEL_15;
      if ( savedPlayPos - *(_DWORD *)(uintptr_t)(v10 + 16) <= remainingBytes )
        fillBytes = savedPlayPos - *(_DWORD *)(uintptr_t)(v10 + 16);
      else
        fillBytes = remainingBytes;
      fillTarget = v10;
    }
    else
    {
      if ( playPos - writePos - *(_DWORD *)(uintptr_t)(channel + 16) <= bufferBytes )
        bufferBytes = playPos - writePos - *(_DWORD *)(uintptr_t)(channel + 16);
      fillBytes = bufferBytes;
      fillTarget = channel;
    }
    CSS_Channel_FillSilence(fillTarget, fillBytes);
LABEL_15:
    CSS_ChannelSetPositionOffset(channelIndex, *(_DWORD *)(uintptr_t)(channel + 12));
  }
}
// 46DD6D: variable 'v10' is possibly undefined
// 54D3D0: using guessed type int dword_54D3D0;
// 54D468: using guessed type int dword_54D468;

//----- (0046DEF0) --------------------------------------------------------
int  CSS_Channel_StoreFormatParams(int channel, int formatCode)
{
  int result; // eax

  *(_DWORD *)(uintptr_t)(channel + 16) = CSS_GetFormatSampleSize(formatCode);
  result = CSS_GetFormatSilenceValue(formatCode);
  *(_DWORD *)(uintptr_t)(channel + 24) = result;
  return result;
}

//----- (0046DF20) --------------------------------------------------------
void  CSS_Channel_StartFileStream(unsigned int channelIndex, int *formatInfo, int panning, int volume, int a5 CLASH95_UNUSED, int channelFlags)
{
  _DWORD *channel; // ebx
  int chunkBytes; // eax
  int voiceId; // eax
  int streamBuffer; // [esp+0h] [ebp-14h] BYREF
  int savedPanning; // [esp+4h] [ebp-10h]

  savedPanning = panning;
  streamBuffer = 0;
  channel = (_DWORD *)(uintptr_t)(52 * channelIndex + g_SoundChannelArrayBase);
  CSS_Channel_StoreFormatParams((int)(intptr_t)channel, *formatInfo);
  chunkBytes = 3 * formatInfo[2] / g_CSS_StreamServiceRateHz;
  LOBYTE(chunkBytes) = chunkBytes & 0xFC;
  channel[1] = chunkBytes;
  channel[2] = channel[1] * channel[4];
  CSS_Mem_TryAlloc(channel[2], ((_DWORD*)(&streamBuffer)));
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
  return CSS_Mem_FreeIfSet((int)(intptr_t)entry);
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
    *entryLink = (int *)(uintptr_t)(*entryLink)[5];
    CSS_SampleCache_FreeEntry(entry);
    return 1;
  }
  else
  {
    channelOffset = 0;
    while ( !*(_DWORD *)(uintptr_t)(channelOffset + g_SoundChannelArrayBase + 40) || *(_DWORD *)(uintptr_t)(channelOffset + g_SoundChannelArrayBase) != **entryLink || !CSS_ChannelIsPlaying(channelIndex) )
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
      if ( bytesNeeded + g_CSS_SampleCacheBytesUsed <= g_CSS_SampleCacheByteBudget || !*(_DWORD *)(uintptr_t)(node + 20) )
        break;
      if ( !CSS_SampleCache_EvictEntry((int **)(uintptr_t)(node + 20)) )
        node = *(_DWORD *)(uintptr_t)(node + 20);
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
  for ( ; *(_DWORD *)(uintptr_t)(result + 20); result = *(_DWORD *)(uintptr_t)(result + 20) )
    ;
  *(_DWORD *)(uintptr_t)(result + 20) = entry;
  return result;
}

//----- (0046E240) --------------------------------------------------------
int  CSS_SampleCache_TouchEntry(int *listHead)
{
  int v2; // ecx
  int result; // eax

  CSS_SampleCache_AppendEntry(*listHead, *listHead);
  *listHead = *(_DWORD *)(uintptr_t)(v2 + 20);
  result = v2;
  *(_DWORD *)(uintptr_t)(v2 + 20) = 0;
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
    while ( *(_DWORD *)(uintptr_t)(v3 + 20) )
    {
      if ( !stricmp_(v3, fileName) )
        return CSS_SampleCache_TouchEntry((int *)(uintptr_t)(v4 + 20));
      v3 = *(_DWORD *)(uintptr_t)(v4 + 20);
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
struct _EXCEPTION_REGISTRATION_RECORD *CSS_SweepFinishedChannels(void)
{
  int channelOffset; // ebx
  signed int i; // ecx
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+0h] [ebp-28h]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  channelOffset = 0;
  for ( i = 0; i < g_CssVoicePoolSize; channelOffset += 52 )
  {
    if ( *(_DWORD *)(uintptr_t)(channelOffset + g_SoundChannelArrayBase + 48) )
      CSS_CloseChannel(i, 0);
    ++i;
  }
  return ExceptionList;
}
// 46E328: variable 'i' is possibly undefined
// 54D3C8: using guessed type int dword_54D3C8;
// 54D3D0: using guessed type int dword_54D3D0;

//----- (0046E350) --------------------------------------------------------
struct _EXCEPTION_REGISTRATION_RECORD *CSS_ServiceStreamingChannels(void)
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
    if ( *(_DWORD *)(uintptr_t)(channelOffset + g_SoundChannelArrayBase + 44)
      && *(_DWORD *)(uintptr_t)(channel + 40)
      && (*(_BYTE *)(uintptr_t)(channel + 36) & 0xC) != 0
      && CSS_ChannelIsPlaying(i) )
    {
      (*(void (__cdecl **)(struct _EXCEPTION_REGISTRATION_RECORD *, tagRECT *, void *, int))(uintptr_t)(**(_DWORD **)(uintptr_t)(channelOffset + g_SoundChannelArrayBase + 20)
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
int __stdcall CSS_StreamReadingThreadProc(int threadParam CLASH95_UNUSED)
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
    Sleep(CSS_MILLISECONDS_PER_SECOND / g_CSS_StreamServiceRateHz);
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
_DWORD *__stdcall CSS_PauseStreamReading(void)
{
  _DWORD *result; // eax
  int *lockCounter; // ebx
  _DWORD ehFrame[3]; // [esp+0h] [ebp-20h] BYREF
  int tryLevel CLASH95_UNUSED; // [esp+Ch] [ebp-14h]
  int *lockCounterPtr; // [esp+14h] [ebp-Ch]

  result = ehFrame;
  ehFrame[0] = ((_DWORD)(uintptr_t)(NtCurrentTeb()->NtTib.ExceptionList));
  ehFrame[1] = ((_DWORD)(uintptr_t)(&j____wcpp_4_fs_handler_rtn_));
  ehFrame[2] = ((_DWORD)(uintptr_t)(&g_CSSPauseStreamReading_EHScopeTable));
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
    return (_DWORD *)(uintptr_t)(*lockCounter)--;
  }
  return result;
}
// 54D3D8: using guessed type int dword_54D3D8;
// 54D414: using guessed type int dword_54D414;

//----- (0046E5C0) --------------------------------------------------------
DWORD __stdcall CSS_ResumeStreamReading(void)
{
  return ResumeThread(hThread);
}

//----- (0046E5D0) --------------------------------------------------------
int __stdcall CSS_StreamBufferServiceThreadProc(int threadParam CLASH95_UNUSED)
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
        if ( *(_DWORD *)(uintptr_t)(channelOffset + g_SoundChannelArrayBase + 44)
          && *(_DWORD *)(uintptr_t)(channel + 40)
          && (*(_BYTE *)(uintptr_t)(channel + 36) & 0xC) != 0
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
    Sleep(CSS_MILLISECONDS_PER_SECOND / g_CSS_StreamServiceRateHz);
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
