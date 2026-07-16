/* Generated from src/recovered/world_and_persistence/00441DC0_special_sites_savegame.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "persistence_internal.h"
#include "persistence_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../world/world_api.h"
#include "../units/units_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00441DC0) --------------------------------------------------------
int  Audio_PlayUnitMeleeAttackSound(int result)
{
  char *resourceKeyChars; // esi
  char *stemCursor; // edi
  char stemChar; // al
  char stemNextChar; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPathBuffer, aSfxOddzialy_4, sizeof(soundPathBuffer));
    resourceKeyChars = (&g_UnitTypeResourceKeys)[22 * result];
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      stemChar = *resourceKeyChars;
      *stemCursor = *resourceKeyChars;
      if ( !stemChar )
        break;
      stemNextChar = resourceKeyChars[1];
      resourceKeyChars += 2;
      stemCursor[1] = stemNextChar;
      stemCursor += 2;
    }
    while ( stemNextChar );
    suffixChars = aWalka_wav;
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      suffixChar = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = suffixNextChar;
      suffixCursor += 2;
    }
    while ( suffixNextChar );
    return CSS_PlaySound((int)(intptr_t)soundPathBuffer, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441E60) --------------------------------------------------------
int  Audio_PlayUnitShotSound(int result)
{
  char *resourceKeyChars; // esi
  char *stemCursor; // edi
  char stemChar; // al
  char stemNextChar; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPathBuffer, aSfxOddzialy_5, sizeof(soundPathBuffer));
    resourceKeyChars = (&g_UnitTypeResourceKeys)[22 * result];
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      stemChar = *resourceKeyChars;
      *stemCursor = *resourceKeyChars;
      if ( !stemChar )
        break;
      stemNextChar = resourceKeyChars[1];
      resourceKeyChars += 2;
      stemCursor[1] = stemNextChar;
      stemCursor += 2;
    }
    while ( stemNextChar );
    suffixChars = aGothim_wav;
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      suffixChar = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = suffixNextChar;
      suffixCursor += 2;
    }
    while ( suffixNextChar );
    return CSS_PlaySound((int)(intptr_t)soundPathBuffer, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441F00) --------------------------------------------------------
void  Audio_PlayWorldMapUnitMoveSound(int tileRow, int tileColumn, signed int moveStepCounter, unsigned int unitTypeId)
{
  char *loopStemChars; // esi
  char *loopStemCursor; // edi
  char loopStemChar; // al
  char loopStemNextChar; // al
  char *loopExtChars; // esi
  char *loopExtCursor; // edi
  char loopExtChar; // al
  char loopExtNextChar; // al
  char *stemChars; // esi
  char *stemCursor; // edi
  char stemChar; // al
  char stemNextChar; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  unsigned int volumeTableIndex; // ebx
  char *extChars; // esi
  char *extCursor; // edi
  char extChar; // al
  char extNextChar; // al
  unsigned int tileSurfaceClass; // eax
  char soundPathBuffer[100]; // [esp+0h] [ebp-E4h] BYREF
  char loopSoundPathBuffer[100]; // [esp+64h] [ebp-80h] BYREF
  signed int tileColumnCopy; // [esp+C8h] [ebp-1Ch]
  int loopSampleOffset; // [esp+CCh] [ebp-18h]
  char surfaceSuffix[4]; // [esp+D0h] [ebp-14h] BYREF
  _BYTE airSuffix[16]; // [esp+D4h] [ebp-10h] BYREF

  tileColumnCopy = tileColumn;
  if ( !g_UnitSoundsEnabled )
    return;
  if ( unitTypeId != UNIT_TYPE_CANNON && unitTypeId != UNIT_TYPE_RAM && unitTypeId != UNIT_TYPE_CATAPULT && unitTypeId != UNIT_TYPE_FLY )
  {
    if ( moveStepCounter % 4 )
      return;
    if ( unitTypeId != g_CurrentUnitMoveSoundTypeId )
    {
      g_CurrentUnitMoveSoundTypeId = unitTypeId;
      g_CurrentUnitMoveSoundVariant = 0;
    }
    CSS_StopSound(g_CurrentUnitMoveSoundHandle, 0);
    qmemcpy(soundPathBuffer, aSfxRuchy_0, sizeof(soundPathBuffer));
    stemChars = (&g_UnitMoveSoundStems)[22 * unitTypeId];
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      stemChar = *stemChars;
      *stemCursor = *stemChars;
      if ( !stemChar )
        break;
      stemNextChar = stemChars[1];
      stemChars += 2;
      stemCursor[1] = stemNextChar;
      stemCursor += 2;
    }
    while ( stemNextChar );
    if ( (g_UnitTypeFlags[22 * unitTypeId] & 1) != 0 )
    {
      suffixChars = airSuffix;
      airSuffix[1] = HIBYTE(g_WorldMapUnitMoveSoundSuffixCode);
      airSuffix[0] = g_CurrentUnitMoveSoundVariant + 49;
      goto LABEL_25;
    }
    strcpy(surfaceSuffix, "d0");
    surfaceSuffix[1] = g_CurrentUnitMoveSoundVariant + 49;
    tileSurfaceClass = Map_GetTileSurfaceClassOrUnexplored(tileRow, tileColumnCopy);
    if ( tileSurfaceClass < 0xB7 )
    {
      if ( tileSurfaceClass < 0x93 )
      {
        if ( tileSurfaceClass != 39 )
        {
          suffixChars = surfaceSuffix;
          goto LABEL_25;
        }
LABEL_37:
        surfaceSuffix[0] = 116;
        suffixChars = surfaceSuffix;
        goto LABEL_25;
      }
      if ( tileSurfaceClass > 0x93 )
      {
        if ( tileSurfaceClass == 151 )
          surfaceSuffix[0] = 112;
        suffixChars = surfaceSuffix;
        goto LABEL_25;
      }
      goto LABEL_35;
    }
    if ( tileSurfaceClass <= 0xB7 )
      goto LABEL_37;
    if ( tileSurfaceClass >= 0xCA )
    {
      if ( tileSurfaceClass <= 0xCA )
        goto LABEL_35;
      if ( tileSurfaceClass < 0xCC )
        goto LABEL_36;
      if ( tileSurfaceClass <= 0xCC || tileSurfaceClass == 207 )
      {
LABEL_35:
        surfaceSuffix[0] = 100;
LABEL_36:
        suffixChars = surfaceSuffix;
        goto LABEL_25;
      }
      suffixChars = surfaceSuffix;
    }
    else
    {
      if ( tileSurfaceClass == 185 )
        goto LABEL_37;
      suffixChars = surfaceSuffix;
    }
LABEL_25:
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      suffixChar = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = suffixNextChar;
      suffixCursor += 2;
    }
    while ( suffixNextChar );
    volumeTableIndex = 88 * unitTypeId;
    extChars = a_wav_0;
    extCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      extChar = *extChars;
      *extCursor = *extChars;
      if ( !extChar )
        break;
      extNextChar = extChars[1];
      extChars += 2;
      extCursor[1] = extNextChar;
      extCursor += 2;
    }
    while ( extNextChar );
    g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)(intptr_t)soundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[volumeTableIndex], 0, 0);
    g_CurrentUnitMoveSoundVariant = (g_CurrentUnitMoveSoundVariant + 1) % (unsigned __int8)g_UnitMoveSoundVariantCounts[volumeTableIndex];
    return;
  }
  if ( unitTypeId != g_CurrentUnitMoveSoundTypeId )
  {
    g_CurrentUnitMoveSoundTypeId = unitTypeId;
    qmemcpy(loopSoundPathBuffer, aSfxRuchy, sizeof(loopSoundPathBuffer));
    loopStemChars = (&g_UnitMoveSoundStems)[22 * unitTypeId];
    loopStemCursor = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
    do
    {
      loopStemChar = *loopStemChars;
      *loopStemCursor = *loopStemChars;
      if ( !loopStemChar )
        break;
      loopStemNextChar = loopStemChars[1];
      loopStemChars += 2;
      loopStemCursor[1] = loopStemNextChar;
      loopStemCursor += 2;
    }
    while ( loopStemNextChar );
    loopExtChars = a_wav;
    loopExtCursor = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
    do
    {
      loopExtChar = *loopExtChars;
      *loopExtCursor = *loopExtChars;
      if ( !loopExtChar )
        break;
      loopExtNextChar = loopExtChars[1];
      loopExtChars += 2;
      loopExtCursor[1] = loopExtNextChar;
      loopExtCursor += 2;
    }
    while ( loopExtNextChar );
    g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)(intptr_t)loopSoundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[88 * unitTypeId], 0, 0);
    if ( unitTypeId > 0xD )
    {
      if ( unitTypeId <= 0xE )
        loopSampleOffset = 30406;
      else
        loopSampleOffset = 0;
    }
    else
    {
      loopSampleOffset = 31336;
    }
    CSS_SetSoundLoop(g_CurrentUnitMoveSoundHandle, loopSampleOffset, -1);
  }
}
// 441FD2: conditional instruction was optimized away because ebx.4==C
// 442183: conditional instruction was optimized away because ebx.4==1D
// 441FC9: simplified comparisons for 'ebx.4': >=Du && >=Eu became >=Eu
// 51257A: using guessed type int g_UnitTypeFlags[];
// 5125B9: using guessed type char *g_UnitMoveSoundStems;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 5178F4: using guessed type __int16 word_5178F4;
// 543CA8: using guessed type int g_CurrentUnitMoveSoundHandle;
// 543CAC: using guessed type int g_CurrentUnitMoveSoundVariant;
// 543CB0: using guessed type int g_CurrentUnitMoveSoundTypeId;

//----- (00442290) --------------------------------------------------------
void  Audio_PlayBattleMapUnitMoveSound(int tileRow, int tileColumn, signed int moveStepCounter, unsigned int unitTypeId)
{
  char *loopStemChars; // esi
  char *loopStemCursor; // edi
  char loopStemChar; // al
  char loopStemNextChar; // al
  char *loopExtChars; // esi
  char *loopExtCursor; // edi
  char loopExtChar; // al
  char loopExtNextChar; // al
  char *stemChars; // esi
  char *stemCursor; // edi
  char stemChar; // al
  char stemNextChar; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  unsigned int volumeTableIndex; // ebx
  char *extChars; // esi
  char *extCursor; // edi
  char extChar; // al
  char extNextChar; // al
  unsigned int tileSurfaceClass; // eax
  char soundPathBuffer[100]; // [esp+0h] [ebp-E4h] BYREF
  char loopSoundPathBuffer[100]; // [esp+64h] [ebp-80h] BYREF
  int tileColumnCopy; // [esp+C8h] [ebp-1Ch]
  int loopSampleOffset; // [esp+CCh] [ebp-18h]
  char surfaceSuffix[4]; // [esp+D0h] [ebp-14h] BYREF
  _BYTE airSuffix[16]; // [esp+D4h] [ebp-10h] BYREF

  tileColumnCopy = tileColumn;
  if ( g_UnitSoundsEnabled )
  {
    if ( unitTypeId == UNIT_TYPE_CANNON || unitTypeId == UNIT_TYPE_RAM || unitTypeId == UNIT_TYPE_CATAPULT || unitTypeId == UNIT_TYPE_FLY )
    {
      if ( unitTypeId != g_CurrentUnitMoveSoundTypeId )
      {
        g_CurrentUnitMoveSoundTypeId = unitTypeId;
        qmemcpy(loopSoundPathBuffer, aSfxRuchy_1, sizeof(loopSoundPathBuffer));
        loopStemChars = (&g_UnitMoveSoundStems)[22 * unitTypeId];
        loopStemCursor = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
        do
        {
          loopStemChar = *loopStemChars;
          *loopStemCursor = *loopStemChars;
          if ( !loopStemChar )
            break;
          loopStemNextChar = loopStemChars[1];
          loopStemChars += 2;
          loopStemCursor[1] = loopStemNextChar;
          loopStemCursor += 2;
        }
        while ( loopStemNextChar );
        loopExtChars = a_wav_1;
        loopExtCursor = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
        do
        {
          loopExtChar = *loopExtChars;
          *loopExtCursor = *loopExtChars;
          if ( !loopExtChar )
            break;
          loopExtNextChar = loopExtChars[1];
          loopExtChars += 2;
          loopExtCursor[1] = loopExtNextChar;
          loopExtCursor += 2;
        }
        while ( loopExtNextChar );
        g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)(intptr_t)loopSoundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[88 * unitTypeId], 0, 0);
        if ( unitTypeId > 0xD )
        {
          if ( unitTypeId <= 0xE )
            loopSampleOffset = 30406;
          else
            loopSampleOffset = 0;
        }
        else
        {
          loopSampleOffset = 31336;
        }
        CSS_SetSoundLoop(g_CurrentUnitMoveSoundHandle, loopSampleOffset, -1);
      }
    }
    else if ( !(moveStepCounter % 4) )
    {
      if ( unitTypeId != g_CurrentUnitMoveSoundTypeId )
      {
        g_CurrentUnitMoveSoundTypeId = unitTypeId;
        g_CurrentUnitMoveSoundVariant = 0;
      }
      CSS_StopSound(g_CurrentUnitMoveSoundHandle, 0);
      qmemcpy(soundPathBuffer, aSfxRuchy_2, sizeof(soundPathBuffer));
      stemChars = (&g_UnitMoveSoundStems)[22 * unitTypeId];
      stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
      do
      {
        stemChar = *stemChars;
        *stemCursor = *stemChars;
        if ( !stemChar )
          break;
        stemNextChar = stemChars[1];
        stemChars += 2;
        stemCursor[1] = stemNextChar;
        stemCursor += 2;
      }
      while ( stemNextChar );
      if ( (g_UnitTypeFlags[22 * unitTypeId] & 1) != 0 )
      {
        suffixChars = airSuffix;
        airSuffix[1] = HIBYTE(g_BattleMapUnitMoveSoundSuffixCode);
        airSuffix[0] = g_CurrentUnitMoveSoundVariant + 49;
      }
      else
      {
        strcpy(surfaceSuffix, "d0");
        surfaceSuffix[1] = g_CurrentUnitMoveSoundVariant + 49;
        tileSurfaceClass = BattleMap_GetMoveSoundSurfaceClass(tileRow, tileColumnCopy);
        if ( tileSurfaceClass )
        {
          if ( tileSurfaceClass <= 1 )
          {
            surfaceSuffix[0] = 116;
            suffixChars = surfaceSuffix;
          }
          else
          {
            if ( tileSurfaceClass == 2 )
              surfaceSuffix[0] = 100;
            suffixChars = surfaceSuffix;
          }
        }
        else
        {
          surfaceSuffix[0] = 112;
          suffixChars = surfaceSuffix;
        }
      }
      suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
      do
      {
        suffixChar = *suffixChars;
        *suffixCursor = *suffixChars;
        if ( !suffixChar )
          break;
        suffixNextChar = suffixChars[1];
        suffixChars += 2;
        suffixCursor[1] = suffixNextChar;
        suffixCursor += 2;
      }
      while ( suffixNextChar );
      volumeTableIndex = 88 * unitTypeId;
      extChars = a_wav_2;
      extCursor = &soundPathBuffer[strlen(soundPathBuffer)];
      do
      {
        extChar = *extChars;
        *extCursor = *extChars;
        if ( !extChar )
          break;
        extNextChar = extChars[1];
        extChars += 2;
        extCursor[1] = extNextChar;
        extCursor += 2;
      }
      while ( extNextChar );
      g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)(intptr_t)soundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[volumeTableIndex], 0, 0);
      g_CurrentUnitMoveSoundVariant = (g_CurrentUnitMoveSoundVariant + 1) % (unsigned __int8)g_UnitMoveSoundVariantCounts[volumeTableIndex];
    }
  }
}
// 442362: conditional instruction was optimized away because ebx.4==C
// 442513: conditional instruction was optimized away because ebx.4==1D
// 442359: simplified comparisons for 'ebx.4': >=Du && >=Eu became >=Eu
// 51257A: using guessed type int g_UnitTypeFlags[];
// 5125B9: using guessed type char *g_UnitMoveSoundStems;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 5179CC: using guessed type __int16 word_5179CC;
// 543CA8: using guessed type int g_CurrentUnitMoveSoundHandle;
// 543CAC: using guessed type int g_CurrentUnitMoveSoundVariant;
// 543CB0: using guessed type int g_CurrentUnitMoveSoundTypeId;

//----- (004425B0) --------------------------------------------------------
void Audio_StopUnitMoveSound(void)
{
  if ( g_UnitSoundsEnabled )
  {
    CSS_StopSound(g_CurrentUnitMoveSoundHandle, 333);
    g_CurrentUnitMoveSoundTypeId = -1;
  }
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;
// 543CA8: using guessed type int g_CurrentUnitMoveSoundHandle;
// 543CB0: using guessed type int g_CurrentUnitMoveSoundTypeId;

//----- (004425E0) --------------------------------------------------------
char * Audio_PlayButtonSound(char *result)
{
  char *soundNameChars; // esi
  char *stemCursor; // edi
  char stemChar; // al
  char stemNextChar; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPathBuffer, aSfxButtons, sizeof(soundPathBuffer));
    soundNameChars = result;
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      stemChar = *soundNameChars;
      *stemCursor = *soundNameChars;
      if ( !stemChar )
        break;
      stemNextChar = soundNameChars[1];
      soundNameChars += 2;
      stemCursor[1] = stemNextChar;
      stemCursor += 2;
    }
    while ( stemNextChar );
    suffixChars = a_wav_3;
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      suffixChar = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = suffixNextChar;
      suffixCursor += 2;
    }
    while ( suffixNextChar );
    return (char *)(uintptr_t)CSS_PlaySound((int)(intptr_t)soundPathBuffer, 32, 0, 0);
  }
  return result;
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00442680) --------------------------------------------------------
int  Audio_PlayArtifactSound(int result)
{
  _BYTE soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    sprintf_(soundPathBuffer, "sfx\\artefakt\\%d.wav", result);
    return CSS_PlaySound((int)(intptr_t)soundPathBuffer, 64, 0, 0);
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (004426C0) --------------------------------------------------------
int  Audio_PlaySoundEffectByName(char *soundName, int volume)
{
  char *stemCursor; // edi
  char stemChar; // al
  char stemNextChar; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( !g_UnitSoundsEnabled )
    return 0;
  qmemcpy(soundPathBuffer, aSfx, sizeof(soundPathBuffer));
  stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
  do
  {
    stemChar = *soundName;
    *stemCursor = *soundName;
    if ( !stemChar )
      break;
    stemNextChar = soundName[1];
    soundName += 2;
    stemCursor[1] = stemNextChar;
    stemCursor += 2;
  }
  while ( stemNextChar );
  suffixChars = a_wav_4;
  suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
  do
  {
    suffixChar = *suffixChars;
    *suffixCursor = *suffixChars;
    if ( !suffixChar )
      break;
    suffixNextChar = suffixChars[1];
    suffixChars += 2;
    suffixCursor[1] = suffixNextChar;
    suffixCursor += 2;
  }
  while ( suffixNextChar );
  return CSS_PlaySound((int)(intptr_t)soundPathBuffer, volume, 0, 0);
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00442760) --------------------------------------------------------
int  FileSystem_InitRootMount(int a1, char a2, DWORD a3)
{
  const char **filesystem_root; // eax

  filesystem_root = FileSystem_DiskMountCreate(a1, a2, a3);
  FileSystem_ConstructMountTable((int)(intptr_t)&g_FileSystemMountTable, (int)(intptr_t)filesystem_root, 0, a3);
  return CRT_RegisterFinalizableObject((int)(intptr_t)&g_FileSystemRootMountObject, 0);
}

//----- (004427C0) --------------------------------------------------------
int  IO_QueryVTableStreamSize(int streamObject)
{
  int cursor;
  int size;
  uintptr_t *vtable;

  if ( !streamObject )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)streamObject;
  if ( !vtable )
    return 0;
  cursor = ((int (*)(int, int))(uintptr_t)vtable[1])(streamObject, 0);
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)streamObject;
  ((int (*)(int, int))(uintptr_t)vtable[2])(streamObject, 0);
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)streamObject;
  size = ((int (*)(int, int))(uintptr_t)vtable[1])(streamObject, cursor);
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)streamObject;
  ((int (*)(int, int))(uintptr_t)vtable[0])(streamObject, cursor);
  return size;
}

//----- (004427F0) --------------------------------------------------------
int  FileSystem_ResolveReadPath(char *relativePath, int quitOnFailFlag)
{
  int queryHandle; // esi
  char fullPathBuffer[100]; // [esp+0h] [ebp-7Ch] BYREF
  int quitOnFailFlagCopy; // [esp+64h] [ebp-18h]

  quitOnFailFlagCopy = quitOnFailFlag;
  g_FileSystemMountOpenMode = 6;
  queryHandle = Compat_FileSystemQuery((int)(intptr_t)&g_FileSystemMountTable, relativePath, 0, FileSystem_TryOpenEntryCallback);
  if ( !queryHandle )
  {
    strcpy(fullPathBuffer, aCClash);
    strcat(fullPathBuffer, relativePath);
    g_FileSystemMountOpenMode = 6;
    queryHandle = Compat_FileSystemQuery((int)(intptr_t)&g_FileSystemMountTable, fullPathBuffer, 0, FileSystem_TryOpenEntryCallback);
    if ( !queryHandle && quitOnFailFlagCopy )
      App_RequestQuit((int)(intptr_t)aIOCouldnTOpenF);
  }
  return queryHandle;
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00442990) --------------------------------------------------------
char  FileSystem_SetInstallRootPath(char *sourcePath)
{
  char *installRootCursor; // edi
  char result; // al

  installRootCursor = aCClash;
  do
  {
    result = *sourcePath;
    *installRootCursor = *sourcePath;
    if ( !result )
      break;
    result = sourcePath[1];
    sourcePath += 2;
    installRootCursor[1] = result;
    installRootCursor += 2;
  }
  while ( result );
  return result;
}

//----- (004429C0) --------------------------------------------------------
char *FileSystem_GetInstallRootPath(void)
{
  return aCClash;
}

//----- (004429D0) --------------------------------------------------------
int  FileSystem_MountArchiveAtIndex(int mountPrefix, const CHAR *archiveFileName, DWORD mountFlags)
{
  int canOpenPath; // eax
  unsigned int resolvedPathLen; // eax
  int *readOnlySource; // eax
  char resolvedPathBuffer[100]; // [esp+0h] [ebp-88h] BYREF
  int errorTextTable[4]; // [esp+64h] [ebp-24h]

  canOpenPath = Compat_CanOpenReadPath(archiveFileName);
  if ( canOpenPath )
  {
    Compat_CopyPrefixN(resolvedPathBuffer, archiveFileName, (unsigned int)strlen(archiveFileName) + 1);
  }
  else
  {
    Compat_CopyPrefixN(resolvedPathBuffer, aCClash, (unsigned int)strlen(aCClash) + 1);
    resolvedPathLen = (unsigned int)strlen(resolvedPathBuffer) + 1;
    Compat_CopyPrefixN(&resolvedPathBuffer[resolvedPathLen - 1], archiveFileName, (unsigned int)strlen(archiveFileName) + 1);
    canOpenPath = Compat_CanOpenReadPath(resolvedPathBuffer);
    if ( !canOpenPath )
    {
      errorTextTable[0] = (int)(intptr_t)g_ArchiveMountFailedErrorText[0];
      errorTextTable[1] = (int)(intptr_t)g_ArchiveMountFailedErrorText[1];
      errorTextTable[2] = (int)(intptr_t)g_ArchiveMountFailedErrorText[2];
      errorTextTable[3] = (int)(intptr_t)g_ArchiveMountFailedErrorText[3];
      App_RequestQuit(errorTextTable[(unsigned __int8)g_LanguageIndex]);
    }
  }
  readOnlySource = File_AllocateReadOnlySource(resolvedPathBuffer, mountFlags, 0, mountFlags, (int)(intptr_t)resolvedPathBuffer);
  return FileSystem_AddMountEntry(g_FileSystemMountTable, (const CHAR *)(uintptr_t)(unsigned int)mountPrefix, 0, (DWORD)(intptr_t)readOnlySource);
}
// 442A16: variable 'v3' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 517B14: using guessed type char *off_517B14[3];
// 543CC8: using guessed type int dword_543CC8[11];

//----- (00442AD0) --------------------------------------------------------
int __thiscall ResourceArchives_MountStartupArchives(int this)
{
  const CHAR *langInfoArchivePath; // edx
  char *langInfoGfxPrefix; // eax
  const CHAR *langMisinfoArchivePath; // edx
  char *langMisinfoMountPrefix; // eax
  int v7; // ecx
  int v9[3]; // [esp+0h] [ebp-1Ch]
  int v10[4]; // [esp+Ch] [ebp-10h] BYREF

  v10[2] = this;
  FileSystem_MountArchiveAtIndex((int)(intptr_t)aDot_MinimumResourcePrefix, aDataMinimum_re, 0x14u);
  FileSystem_MountArchiveAtIndex((int)(intptr_t)aDot_NormalResourcePrefix, aDataNormal_res, 1u);
  FileSystem_MountArchiveAtIndex((int)(intptr_t)aDot_MaximumResourcePrefix, aDataMaximum_re, 1u);
  FileSystem_MountArchiveAtIndex((int)(intptr_t)aMaps_0, aDataMaps_res, 1u);
  FileSystem_MountArchiveAtIndex((int)(intptr_t)aGfx_6, aDataGfx3_res, 1u);
  if ( !g_LanguageIndex )
  {
    langInfoArchivePath = aDataInfopol_re;
    langInfoGfxPrefix = aGfxBiginfo_pol;
LABEL_3:
    FileSystem_MountArchiveAtIndex((int)(intptr_t)langInfoGfxPrefix, langInfoArchivePath, 1u);
    goto LABEL_4;
  }
  if ( (unsigned __int8)g_LanguageIndex <= 1u )
  {
    langInfoArchivePath = aDataInfoang_re;
    langInfoGfxPrefix = aGfxBiginfo_eng;
    goto LABEL_3;
  }
  if ( g_LanguageIndex == 2 )
  {
    langInfoArchivePath = aDataInfoger_re;
    langInfoGfxPrefix = aGfxBiginfo_ger;
    goto LABEL_3;
  }
LABEL_4:
  if ( !g_LanguageIndex )
  {
    langMisinfoArchivePath = aDataMisinfop_r;
    langMisinfoMountPrefix = aGfxMisinfo;
LABEL_6:
    FileSystem_MountArchiveAtIndex((int)(intptr_t)langMisinfoMountPrefix, langMisinfoArchivePath, 1u);
    goto LABEL_7;
  }
  if ( (unsigned __int8)g_LanguageIndex <= 1u )
  {
    FileSystem_MountArchiveAtIndex((int)(intptr_t)aGfxMisinfo_0, aDataMisinfoa_r, 1u);
    langMisinfoArchivePath = aDataMiswava_re;
    langMisinfoMountPrefix = aSfxMisinfo;
    goto LABEL_6;
  }
  if ( g_LanguageIndex == 2 )
  {
    langMisinfoArchivePath = aDataMisinfog_r;
    langMisinfoMountPrefix = aGfxMisinfo_1;
    goto LABEL_6;
  }
LABEL_7:
  FileSystem_MountArchiveAtIndex((int)(intptr_t)aSfxMusic_0, aDataMusic_res, 1u);
  CSS_SetFileSystem((int)(intptr_t)g_FileSystemMountTable);
  v10[0] = FileSystem_ResolveReadPath(aGfxBackgr1_s32, 0);
  if ( !v10[0] )
  {
    v9[0] = (int)(intptr_t)g_StartupResourceMissingErrorText[0];
    v9[1] = (int)(intptr_t)g_StartupResourceMissingErrorText[1];
    v9[2] = (int)(intptr_t)g_StartupResourceMissingErrorText[2];
    App_RequestQuit(v9[(unsigned __int8)g_LanguageIndex]);
  }
  return Compat_FileSystemQueryRelease(v7, v10);
}
// 442AD0: could not find valid save-restore pair for edi
// 442AD0: could not find valid save-restore pair for esi
// 442BC3: variable 'v7' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 517B24: using guessed type char *off_517B24[3];
// 543CC8: using guessed type int dword_543CC8[11];

//----- (00442C80) --------------------------------------------------------
int  loadFileSusp(char *sourcePath, const CHAR *destPath)
{
  unsigned char *copy_buffer;
  int query_handle;
  int output_handle;
  int bytes_read;

  copy_buffer = (unsigned char *)(uintptr_t)(unsigned int)nmalloc_(0x80000, 4);
  if ( !copy_buffer )
  {
    Debug_Log(0, (char)(intptr_t)sourcePath, (DWORD)(intptr_t)destPath, (int)(intptr_t)aNotEnoughMe_11);
    App_RequestQuit((int)(intptr_t)aNotEnoughMe_12);
  }
  query_handle = FileSystem_ResolveReadPath(sourcePath, 1);
  if ( !query_handle )
    App_RequestQuit((int)(intptr_t)aBrakPlikuS);

  output_handle = IO_FOpen(destPath, (unsigned __int8 *)aWb_2, 0, (DWORD)(intptr_t)destPath);
  do
  {
    bytes_read = Compat_QueryRead(query_handle, copy_buffer, 0x80000);
    if ( bytes_read )
      fwrite_(copy_buffer, bytes_read, output_handle, 1);
  }
  while ( bytes_read == 0x80000 );
  Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
  fclose_(output_handle);
  Compat_FreeLow32Bytes((int)(uintptr_t)copy_buffer);
  return 0;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00442D90) --------------------------------------------------------
int Port_FindAndInit(void)
{
  int rowIndex; // esi
  int rowOffset; // edi
  int result; // eax
  int columnIndex; // eax
  int tileStride; // edx
  int tileId; // ecx
  int dataBase CLASH95_UNUSED; // eax
  int portColumnOffset; // ecx
  int shoreTileId; // edx
  _WORD *bottomRightTile; // edx
  _WORD *bottomLeftTile; // edx

  PORT_ROW = -1;
  rowIndex = 0;
  rowOffset = 0;
  PORT_REINFORCEMENT_READY_FLAG = 0;
LABEL_2:
  while ( 1 )
  {
    result = gameData;
    if ( rowIndex >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
      return result;
    columnIndex = 0;
    for ( tileStride = 0; ; tileStride += 14 )
    {
      if ( columnIndex >= *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET) )
      {
        rowOffset += TILE_TERRAIN_ROW_STRIDE;
        ++rowIndex;
        goto LABEL_2;
      }
      tileId = *(unsigned __int16 *)(uintptr_t)(rowOffset + gameData + tileStride + 2);
      if ( tileId == 716 || tileId == 726 )
        break;
      ++columnIndex;
    }
    PORT_ROW = rowIndex;
    PORT_COLUMN = columnIndex;
    dataBase = gameData;
    PORT_SHORE_VARIANT_FLAG = 1;
    PORT_REINFORCEMENT_READY_FLAG = PORT_SHORE_VARIANT_FLAG;
    PORT_NEXT_REINFORCEMENT_TURN = Rng_RandRange(8, 10);
    PORT_REINFORCEMENT_UNIT_COUNT = Rng_RandRange(3, 5);
    portColumnOffset = 14 * PORT_COLUMN;
    shoreTileId = *(unsigned __int16 *)(uintptr_t)(portColumnOffset + gameData + TILE_TERRAIN_ROW_STRIDE * PORT_ROW + 2);
    if ( shoreTileId == 726 || shoreTileId == 722 )
    {
      bottomRightTile = (_WORD *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * (PORT_COLUMN + 1) + gameData + TILE_TERRAIN_ROW_STRIDE * (PORT_ROW + 1));
      *bottomRightTile = 715;
      *(_WORD *)(uintptr_t)(gameData + TILE_TERRAIN_ROW_STRIDE * (PORT_ROW + 1) + TILE_TERRAIN_RECORD_STRIDE * PORT_COLUMN) = *bottomRightTile;
    }
    else
    {
      bottomLeftTile = (_WORD *)(uintptr_t)(TILE_TERRAIN_ROW_STRIDE * (PORT_ROW + 1) + gameData + portColumnOffset);
      *bottomLeftTile = 715;
      *(_WORD *)(uintptr_t)(TILE_TERRAIN_RECORD_STRIDE * PORT_COLUMN + gameData + TILE_TERRAIN_ROW_STRIDE * PORT_ROW) = *bottomLeftTile;
    }
    Port_UpdateShorelineVariantTiles();
    Rules_LogPortLocation();
    rowOffset += TILE_TERRAIN_ROW_STRIDE;
    ++rowIndex;
  }
}
// 5202E4: using guessed type int gameData;

//----- (00442F60) --------------------------------------------------------
_DWORD *Rules_LogPortLocation(void)
{
  _DWORD *result; // eax
  int portRow; // edx
  double v3; // st7
  int v4; // ecx
  char logTextBuffer[204]; // [esp+0h] [ebp-CCh] BYREF

  result = (_DWORD *)(uintptr_t)gameData;
  portRow = PORT_ROW;
  if ( portRow != -1 )
  {
    v3 = sprintf_(logTextBuffer, "(port %d %d)", portRow, PORT_COLUMN);
    return Rules_Log(logTextBuffer, v4, v3);
  }
  return result;
}
// 442F9E: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5202E4: using guessed type int gameData;

//----- (00442FB0) --------------------------------------------------------
int  Port_NewTurn(DWORD logContext)
{
  int result; // eax
  int dataBase CLASH95_UNUSED; // eax
  int reinforcementArrivalTurn; // ebx
  int logArg; // ecx

  result = gameData;
  if ( PORT_ROW != -1 )
  {
    PORT_SHORE_VARIANT_FLAG = 0;
    dataBase = gameData;
    if ( !PORT_REINFORCEMENT_READY_FLAG )
    {
      reinforcementArrivalTurn = PORT_NEXT_REINFORCEMENT_TURN;
      if ( *(unsigned __int16 *)(uintptr_t)(gameData + GAME_TURN_COUNTER_OFFSET) >= reinforcementArrivalTurn )
      {
      PORT_SHORE_VARIANT_FLAG = 1;
      PORT_REINFORCEMENT_READY_FLAG = PORT_SHORE_VARIANT_FLAG;
        PORT_REINFORCEMENT_UNIT_COUNT = Rng_RandRange(3, 5);
        Debug_Log(logArg, reinforcementArrivalTurn, logContext, (int)(intptr_t)aPort_newturnPo);
      }
    }
    return Port_UpdateShorelineVariantTiles();
  }
  return result;
}
// 443038: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00443090) --------------------------------------------------------
int Port_UpdateShorelineVariantTiles(void)
{
  int result; // eax
  int portRow; // edx
  int rowCursor; // ebp
  int colCursor; // edx
  int colByteOffset; // ecx
  int tileAddr; // eax
  int rowCursorB; // ebp
  int colCursorB; // edx
  int colByteOffsetB; // ecx
  int tileAddrB; // eax
  int i; // [esp+0h] [ebp-1Ch]
  int j; // [esp+4h] [ebp-18h]

  result = gameData;
  portRow = PORT_ROW;
  if ( portRow != -1 )
  {
    if ( PORT_SHORE_VARIANT_FLAG )
    {
      rowCursor = PORT_ROW;
      for ( i = TILE_TERRAIN_ROW_STRIDE * portRow; ; i += TILE_TERRAIN_ROW_STRIDE )
      {
        result = PORT_ROW + 1;
        if ( rowCursor > result )
          break;
        colCursor = PORT_COLUMN;
        colByteOffset = 14 * colCursor;
        while ( colCursor <= PORT_COLUMN + 1 )
        {
          tileAddr = colByteOffset + i + gameData;
          switch ( *(_WORD *)(uintptr_t)(tileAddr + 2) )
          {
            case 0x2D0:
              *(_WORD *)(uintptr_t)(tileAddr + 2) = 718;
              break;
            case 0x2D1:
              *(_WORD *)(uintptr_t)(tileAddr + 2) = 719;
              break;
            case 0x2D6:
              *(_WORD *)(uintptr_t)(tileAddr + 2) = 722;
              break;
            case 0x2D7:
              *(_WORD *)(uintptr_t)(tileAddr + 2) = 724;
              break;
            default:
              break;
          }
          colByteOffset += 14;
          ++colCursor;
        }
        ++rowCursor;
      }
    }
    else
    {
      rowCursorB = PORT_ROW;
      for ( j = TILE_TERRAIN_ROW_STRIDE * portRow; ; j += TILE_TERRAIN_ROW_STRIDE )
      {
        result = PORT_ROW + 1;
        if ( rowCursorB > result )
          break;
        colCursorB = PORT_COLUMN;
        colByteOffsetB = 14 * colCursorB;
        while ( colCursorB <= PORT_COLUMN + 1 )
        {
          tileAddrB = colByteOffsetB + j + gameData;
          switch ( *(_WORD *)(uintptr_t)(tileAddrB + 2) )
          {
            case 0x2CE:
              *(_WORD *)(uintptr_t)(tileAddrB + 2) = 720;
              break;
            case 0x2CF:
              *(_WORD *)(uintptr_t)(tileAddrB + 2) = 721;
              break;
            case 0x2D2:
              *(_WORD *)(uintptr_t)(tileAddrB + 2) = 726;
              break;
            case 0x2D4:
              *(_WORD *)(uintptr_t)(tileAddrB + 2) = 727;
              break;
            default:
              break;
          }
          colByteOffsetB += 14;
          ++colCursorB;
        }
        ++rowCursorB;
      }
    }
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (00443230) --------------------------------------------------------
int Port_IsReinforcementReady(void)
{
  return PORT_REINFORCEMENT_READY_FLAG;
}
// 5202E4: using guessed type int gameData;

//----- (00443240) --------------------------------------------------------
int * Port_GenerateApproachTrack(int unitStackIndex)
{
  int portRowValue; // ecx
  int portRow; // ebp
  int topRowTileBase; // edi
  int bottomRowTileBase; // edx
  int bottomRowByteOffset; // ecx
  int rightColumnByteOffset; // edx
  __int16 bottomRightTile; // ax
  int stackColumn; // ebx
  int *trackList; // ecx
  int *reversedTrack; // eax
  int *sourceTrack; // ecx
  int *trackReadPtr; // edx
  int sourceIndex; // ebx
  int outputCount; // edi
  int stepValue; // esi
  int reverseCount; // esi
  int restoreTopRowByteOffset; // ebx
  int leftColumnByteOffset; // edx
  int restoreBottomRowByteOffset; // ebp
  int restoreRightColumnByteOffset; // edx
  int lastTrackPoint; // ebx
  int trimmedCount; // esi
  int reversedStep; // esi
  int destCount; // eax
  __int16 savedTileTopLeft; // [esp+0h] [ebp-30h]
  __int16 savedTileBottomLeft; // [esp+4h] [ebp-2Ch]
  __int16 savedTileTopRight; // [esp+8h] [ebp-28h]
  __int16 savedTileBottomRight; // [esp+Ch] [ebp-24h]
  int portRowByteOffset; // [esp+10h] [ebp-20h]
  int bottomRowTileBaseCopy; // [esp+14h] [ebp-1Ch]
  int portColumn; // [esp+20h] [ebp-10h]

  portRowValue = PORT_ROW;
  if ( portRowValue == -1 )
    return 0;
  portRow = PORT_ROW;
  portColumn = PORT_COLUMN;
  portRowByteOffset = TILE_TERRAIN_ROW_STRIDE * portRowValue;
  topRowTileBase = TILE_TERRAIN_ROW_STRIDE * portRowValue + gameData;
  savedTileTopLeft = *(_WORD *)(uintptr_t)(topRowTileBase + 14 * portColumn);
  bottomRowTileBase = TILE_TERRAIN_ROW_STRIDE * (portRowValue + 1) + gameData;
  bottomRowByteOffset = TILE_TERRAIN_ROW_STRIDE * (portRowValue + 1);
  savedTileBottomLeft = *(_WORD *)(uintptr_t)(bottomRowTileBase + 14 * portColumn);
  bottomRowTileBaseCopy = bottomRowTileBase;
  rightColumnByteOffset = 14 * (portColumn + 1);
  savedTileTopRight = *(_WORD *)(uintptr_t)(rightColumnByteOffset + topRowTileBase);
  bottomRightTile = *(_WORD *)(uintptr_t)(rightColumnByteOffset + bottomRowTileBaseCopy);
  *(_WORD *)(uintptr_t)(topRowTileBase + 14 * portColumn) = 0;
  savedTileBottomRight = bottomRightTile;
  *(_WORD *)(uintptr_t)(14 * portColumn + bottomRowByteOffset + gameData) = 0;
  *(_WORD *)(uintptr_t)(rightColumnByteOffset + portRowByteOffset + gameData) = 0;
  *(_WORD *)(uintptr_t)(rightColumnByteOffset + bottomRowByteOffset + gameData) = 0;
  stackColumn = *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * unitStackIndex + 147176);
  trackList = Unit_MoveTrack(unitStackIndex, *(__int16 *)(uintptr_t)(gameData + UNIT_STACK_STRIDE * unitStackIndex + UNIT_STACK_TABLE_OFFSET), portRow, stackColumn, portRow, portColumn);
  if ( trackList )
  {
    reversedTrack = (int *)(uintptr_t)Mem_Alloc(404, (int)(intptr_t)trackList, stackColumn, portRow);
    trackReadPtr = reversedTrack;
    if ( reversedTrack )
      *reversedTrack = 0;
    while ( *sourceTrack )
    {
      sourceIndex = *sourceTrack - 1;
      *sourceTrack = sourceIndex;
      outputCount = *reversedTrack;
      stepValue = sourceTrack[sourceIndex + 1];
      if ( *reversedTrack < 100 )
      {
        *reversedTrack = outputCount + 1;
        reversedTrack[outputCount + 1] = stepValue;
      }
    }
    if ( *reversedTrack )
    {
      do
      {
        lastTrackPoint = reversedTrack[*reversedTrack];
        trimmedCount = *reversedTrack - 1;
        if ( portRow > (unsigned __int8)lastTrackPoint )
          break;
        if ( (unsigned __int8)lastTrackPoint > portRow + 1 )
          break;
        if ( BYTE1(lastTrackPoint) < portColumn )
          break;
        if ( BYTE1(lastTrackPoint) > portColumn + 1 )
          break;
        *reversedTrack = trimmedCount;
      }
      while ( trimmedCount );
    }
    while ( 1 )
    {
      reverseCount = *trackReadPtr;
      if ( !*trackReadPtr )
        break;
      *trackReadPtr = reverseCount - 1;
      reversedStep = trackReadPtr[reverseCount];
      destCount = *sourceTrack;
      if ( *sourceTrack < 100 )
      {
        *sourceTrack = destCount + 1;
        sourceTrack[destCount + 1] = reversedStep;
      }
    }
    j__nfree_();
  }
  restoreTopRowByteOffset = TILE_TERRAIN_ROW_STRIDE * portRow;
  leftColumnByteOffset = 14 * portColumn;
  *(_WORD *)(uintptr_t)(leftColumnByteOffset + gameData + TILE_TERRAIN_ROW_STRIDE * portRow) = savedTileTopLeft;
  restoreBottomRowByteOffset = TILE_TERRAIN_ROW_STRIDE * (portRow + 1);
  *(_WORD *)(uintptr_t)(restoreBottomRowByteOffset + gameData + leftColumnByteOffset) = savedTileBottomLeft;
  restoreRightColumnByteOffset = 14 * (portColumn + 1);
  *(_WORD *)(uintptr_t)(restoreRightColumnByteOffset + gameData + restoreTopRowByteOffset) = savedTileTopRight;
  *(_WORD *)(uintptr_t)(restoreBottomRowByteOffset + gameData + restoreRightColumnByteOffset) = savedTileBottomRight;
  return trackList;
}
// 443267: conditional instruction was optimized away because ecx.4!=FFFFFFFF
// 4433C4: variable 'v12' is possibly undefined
// 4434B2: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00443550) --------------------------------------------------------
int  Port_CollectReinforcementShipment(int a1, char a2, DWORD a3, double a4)
{
  int result; // eax
  int scanCenterRow; // edx
  int spawnSlotIndex; // edi
  int i; // esi
  int spawnRow; // ebx
  int spawnColumn; // ecx
  int spawnRowDelta; // eax
  DWORD reinforcementSpawnRow; // ebp
  char v12; // bl
  int v13; // ecx
  int armyFactBase; // edx
  int remainingUnitCount; // esi
  signed int j; // edi
  unsigned int unitPoolIndex; // eax
  int unitSlotPtr; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  unsigned int reinforcementDelay; // eax
  int currentTurn; // ecx
  int colByteOffset; // eax
  int tileUnitIndex; // ecx
  int unitStackBase; // ecx
  char v28; // [esp+0h] [ebp-3Ch]
  int reinforcementSpawnColumn; // [esp+0h] [ebp-3Ch]
  int scanStartColumn; // [esp+4h] [ebp-38h]
  int foundFriendlyUnitNearby; // [esp+8h] [ebp-34h]
  int portRow; // [esp+Ch] [ebp-30h]
  int portColumn; // [esp+10h] [ebp-2Ch]
  int scanColByteOffsetMax; // [esp+18h] [ebp-24h]
  int scanRow; // [esp+1Ch] [ebp-20h]
  int scanRowByteOffset; // [esp+20h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)(intptr_t)aPort_getsupply, v28);
  if ( PORT_ROW == -1 )
    return 0;
  portRow = PORT_ROW;
  portColumn = PORT_COLUMN;
  result = Port_IsReinforcementReady();
  if ( result )
  {
    foundFriendlyUnitNearby = 0;
    scanRow = scanCenterRow - 1;
    scanStartColumn = portColumn - 1;
    scanRowByteOffset = 200 * (scanCenterRow - 1);
    if ( scanRowByteOffset <= 200 * (scanCenterRow + 2) )
    {
      scanColByteOffsetMax = 2 * (portColumn + 2);
      do
      {
        colByteOffset = 2 * scanStartColumn;
        if ( 2 * scanStartColumn <= scanColByteOffsetMax )
        {
          while ( 1 )
          {
            tileUnitIndex = *(unsigned __int16 *)(uintptr_t)(gameData + scanRowByteOffset + colByteOffset + TILE_MAP_OFFSET);
            if ( (unsigned __int16)tileUnitIndex <= 0x1F4u )
            {
              unitStackBase = UNIT_STACK_STRIDE * tileUnitIndex;
              if ( (unsigned int)*(__int16 *)(uintptr_t)(unitStackBase + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28
                && *(unsigned __int8 *)(uintptr_t)(unitStackBase + gameData + 147178) == g_CurrentPlayerIndex )
              {
                break;
              }
            }
            colByteOffset += 2;
            if ( colByteOffset > scanColByteOffsetMax )
              goto LABEL_16;
          }
          foundFriendlyUnitNearby = 1;
        }
LABEL_16:
        scanRowByteOffset += 200;
        ++scanRow;
      }
      while ( scanRowByteOffset <= 200 * (scanCenterRow + 2) );
    }
    result = foundFriendlyUnitNearby;
    if ( foundFriendlyUnitNearby )
    {
      spawnSlotIndex = 0;
      for ( i = 0; i < 12; ++i )
      {
        spawnRow = g_PortReinforcementSpawnRingOffsets[i].row_delta + portRow;
        spawnColumn = g_PortReinforcementSpawnRingOffsets[i].column_delta + portColumn;
        if ( *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(spawnRow, spawnColumn)) == 0xFFFF
          && Map_GetUnitTileMoveCostOrZero(g_CurrentPlayerIndex, 0, spawnColumn, spawnRow) )
        {
          break;
        }
        ++spawnSlotIndex;
      }
      if ( spawnSlotIndex == 12 )
        return 0;
      reinforcementSpawnColumn = g_PortReinforcementSpawnRingOffsets[spawnSlotIndex].column_delta + PORT_COLUMN;
      spawnRowDelta = g_PortReinforcementSpawnRingOffsets[spawnSlotIndex].row_delta;
      reinforcementSpawnRow = spawnRowDelta + PORT_ROW;
      v12 = Facing_DirectionFromDelta8(spawnRowDelta, g_PortReinforcementSpawnRingOffsets[spawnSlotIndex].column_delta);
      Unit_Create(UNIT_TYPE_PEASANT, g_CurrentPlayerIndex, reinforcementSpawnRow, v12, a4, reinforcementSpawnColumn);
      armyFactBase = 145 * *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(reinforcementSpawnRow, reinforcementSpawnColumn));
      remainingUnitCount = PORT_REINFORCEMENT_UNIT_COUNT - 1;
      for ( j = UNIT_STACK_STRIDE * *(unsigned __int16 *)(uintptr_t)(TILE_INDEX(reinforcementSpawnRow, reinforcementSpawnColumn)) + gameData + UNIT_STACK_TABLE_OFFSET;
            remainingUnitCount >= 0;
            v13 = v19 - 31 )
      {
        v12 = g_CurrentPlayerIndex;
        unitPoolIndex = Rng_RandRange(0, 11);
        --remainingUnitCount;
        UnitSlot_InitFromType(unitSlotPtr, g_PortReinforcementUnitTypePool[unitPoolIndex], v12);
      }
      Rules_LinkArmyFact(j, armyFactBase, v13, a4, v12, reinforcementSpawnRow);
      Rules_SyncArmyFactStrength(j, v20, v21, v12, reinforcementSpawnRow, a4);
      UI_StartWorldMapUnitAttentionFlash(*(unsigned __int16 *)(uintptr_t)(TILE_INDEX(reinforcementSpawnRow, reinforcementSpawnColumn)), 200 * reinforcementSpawnRow + gameData, v22);
      PORT_REINFORCEMENT_READY_FLAG = 0;
      reinforcementDelay = Rng_RandRange(8, 10);
      PORT_NEXT_REINFORCEMENT_TURN = currentTurn + reinforcementDelay;
      Port_UpdateShorelineVariantTiles();
      Audio_PlayArtifactSound(1);
      return j;
    }
  }
  return result;
}
// 44385A: simplified comparisons for 'ebx.4': <0 || >=29 became >=29u
// 44355E: variable 'v28' is possibly undefined
// 4435A2: variable 'v5' is possibly undefined
// 443725: variable 'v18' is possibly undefined
// 44372A: variable 'v19' is possibly undefined
// 443742: variable 'v14' is possibly undefined
// 443742: variable 'v13' is possibly undefined
// 443749: variable 'v20' is possibly undefined
// 443749: variable 'v21' is possibly undefined
// 44377F: variable 'v22' is possibly undefined
// 4437B6: variable 'v24' is possibly undefined
// 517B48: using guessed type int dword_517B48[];
// 517B4C: using guessed type int dword_517B4C[23];
// 517BA8: using guessed type unit_type g_PortReinforcementUnitTypePool[12];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004438A0) --------------------------------------------------------
void * UI_DrawPortStatusPanel(char a1, DWORD a2)
{
  int v2; // ecx
  _DWORD *spriteSet; // eax
  _DWORD *Surface; // eax
  int surfacePtr; // ebp
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  DWORD panelSurface; // ebp
  __int16 spriteHeightDraw; // ax
  int SpriteForChar; // eax
  char *portLabelText; // eax
  __int16 spriteHeightRedraw; // ax
  void *result; // eax
  unsigned __int16 rectBottom; // [esp+10h] [ebp-4Ch]
  unsigned __int16 spriteWidthMax; // [esp+10h] [ebp-4Ch]
  unsigned __int16 leftEdge; // [esp+14h] [ebp-48h]
  unsigned __int16 topEdge; // [esp+18h] [ebp-44h]
  int emptyTexts[3]; // [esp+1Ch] [ebp-40h]
  int arrivedTexts[3]; // [esp+28h] [ebp-34h] BYREF
  _DWORD *portSpriteSet; // [esp+34h] [ebp-28h] BYREF
  void *previousRenderDevice; // [esp+38h] [ebp-24h]
  int panelLeft; // [esp+3Ch] [ebp-20h]
  int panelTop; // [esp+40h] [ebp-1Ch]

  previousRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  spriteSet = (_DWORD *)(uintptr_t)Mem_Alloc(4112, v2, a1, a2);
  if ( spriteSet )
    spriteSet = DLXSpriteSet_Load(spriteSet, "port.s32");
  portSpriteSet = spriteSet;
  panelLeft = 100;
  panelTop = 100;
  Surface = (_DWORD *)(uintptr_t)Mem_Alloc(188, 100, a1, a2);
  surfacePtr = (int)(intptr_t)Surface;
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)(intptr_t)portSpriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)(intptr_t)portSpriteSet, 0);
    Surface = Render_CreateSurface(surfacePtr, SpriteHeight, SpriteWidth);
  }
  panelSurface = (DWORD)(intptr_t)Surface;
  rectBottom = panelTop + DLX_GetSpriteWidth((int)(intptr_t)portSpriteSet, 0) - 1;
  spriteHeightDraw = DLX_GetSpriteHeight((int)(intptr_t)portSpriteSet, 0);
  Render_FillRect(0, (_DWORD *)(uintptr_t)panelSurface, (unsigned __int16)panelTop, (unsigned __int16)panelLeft, panelLeft + spriteHeightDraw - 1, rectBottom, 0, 0);
  Render_ReleaseSurface(7, panelSurface);
  SpriteForChar = DLX_GetSpriteForChar((int)(intptr_t)portSpriteSet, PORT_REINFORCEMENT_READY_FLAG);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(uintptr_t)(*((_DWORD *)g_RenderDevice + 46) + 52))(
    panelTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  if ( g_LanguageIndex == 2 )
    portLabelText = aHafen;
  else
    portLabelText = aPort;
  UI_DrawTextFmt((int)(intptr_t)arrivedTexts, panelLeft + 10, panelLeft + 235, panelTop + 5, 3, (int)(intptr_t)portLabelText);
  arrivedTexts[0] = (int)(intptr_t)g_PortReinforcementArrivedTexts[0];
  arrivedTexts[1] = (int)(intptr_t)g_PortReinforcementArrivedTexts[1];
  arrivedTexts[2] = (int)(intptr_t)g_PortReinforcementArrivedTexts[2];
  emptyTexts[0] = (int)(intptr_t)g_PortEmptyTexts[0];
  emptyTexts[1] = (int)(intptr_t)g_PortEmptyTexts[1];
  emptyTexts[2] = (int)(intptr_t)g_PortEmptyTexts[2];
  if ( PORT_REINFORCEMENT_READY_FLAG )
  {
    UI_DrawTextFmt((int)(intptr_t)arrivedTexts, panelLeft + 122, panelLeft + 200, panelTop + 54, 6, arrivedTexts[(unsigned __int8)g_LanguageIndex]);
    Render_ReleaseSurface(15, panelSurface);
    UI_DrawTextFmt((int)(intptr_t)arrivedTexts, panelLeft + 42, panelLeft + 85, panelTop + 29, 1, (int)(intptr_t)aD_36);
  }
  else
  {
    UI_DrawTextFmt(
      emptyTexts[(unsigned __int8)g_LanguageIndex],
      panelLeft + 40,
      panelLeft + 120,
      panelTop + 40,
      6,
      emptyTexts[(unsigned __int8)g_LanguageIndex]);
  }
  Render_Begin((int)(intptr_t)g_RenderState, 0);
  topEdge = panelTop;
  leftEdge = panelLeft;
  spriteWidthMax = DLX_GetSpriteWidth((int)(intptr_t)portSpriteSet, 0) - 1;
  spriteHeightRedraw = DLX_GetSpriteHeight((int)(intptr_t)portSpriteSet, 0);
  Render_FillRect((_DWORD *)(uintptr_t)panelSurface, 0, 0, 0, spriteHeightRedraw - 1, spriteWidthMax, leftEdge, topEdge);
  if ( panelSurface )
    (**(void (__cdecl ***)(int, int, int, int, int, int))(uintptr_t)(panelSurface + 184))(emptyTexts[0], emptyTexts[1], emptyTexts[2], arrivedTexts[0], arrivedTexts[1], arrivedTexts[2]);
  DLXSpriteSet_ReleaseAndClear((int *)&portSpriteSet);
  Render_Present((int)(intptr_t)g_RenderState);
  result = previousRenderDevice;
  g_RenderDevice = previousRenderDevice;
  return result;
}
// 4438CC: variable 'v2' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 517BD8: using guessed type char *g_PortReinforcementArrivedTexts[3];
// 517BE4: using guessed type char *g_PortEmptyTexts[3];
// 5202E4: using guessed type int gameData;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00443B60) --------------------------------------------------------
int Rules_RebuildTreasureFacts(void)
{
  int i; // ebx
  int result; // eax
  int j; // ecx
  int v4; // ecx

  for ( i = 0; ; ++i )
  {
    result = gameData;
    if ( i >= *(_DWORD *)(uintptr_t)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    for ( j = 0; j < *(_DWORD *)(uintptr_t)(gameData + MAP_HEIGHT_TILES_OFFSET); j = v4 + 1 )
    {
      if ( MapTile_HasHiddenTreasure(i, j) )
        Rules_LogTreasureFact(i, v4);
    }
  }
  return result;
}
// 443B98: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;
