/* Generated from src/recovered/buildings/004338C0_building_ui.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00441C80) --------------------------------------------------------
int  Audio_PlayUnitHitSound(int result)
{
  char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPath[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPath, aSfxOddzialy_2, sizeof(soundPath));
    resourceKey = (&g_UnitTypeResourceKeys)[22 * result];
    writeCursor = &soundPath[strlen(soundPath)];
    do
    {
      keyChar = *resourceKey;
      *writeCursor = *resourceKey;
      if ( !keyChar )
        break;
      keyNextChar = resourceKey[1];
      resourceKey += 2;
      writeCursor[1] = keyNextChar;
      writeCursor += 2;
    }
    while ( keyNextChar );
    suffixCursor = aDostal_wav;
    suffixWriteCursor = &soundPath[strlen(soundPath)];
    do
    {
      suffixChar = *suffixCursor;
      *suffixWriteCursor = *suffixCursor;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixCursor[1];
      suffixCursor += 2;
      suffixWriteCursor[1] = suffixNextChar;
      suffixWriteCursor += 2;
    }
    while ( suffixNextChar );
    return CSS_PlaySound((int)(intptr_t)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441D20) --------------------------------------------------------
int  Audio_PlayUnitDeathSound(int result)
{
  char *resourceKey; // esi
  char *writeCursor; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *suffixCursor; // esi
  char *suffixWriteCursor; // edi
  char suffixChar; // al
  char suffixNextChar; // al
  char soundPath[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPath, aSfxOddzialy_3, sizeof(soundPath));
    resourceKey = (&g_UnitTypeResourceKeys)[22 * result];
    writeCursor = &soundPath[strlen(soundPath)];
    do
    {
      keyChar = *resourceKey;
      *writeCursor = *resourceKey;
      if ( !keyChar )
        break;
      keyNextChar = resourceKey[1];
      resourceKey += 2;
      writeCursor[1] = keyNextChar;
      writeCursor += 2;
    }
    while ( keyNextChar );
    suffixCursor = aDead_wav;
    suffixWriteCursor = &soundPath[strlen(soundPath)];
    do
    {
      suffixChar = *suffixCursor;
      *suffixWriteCursor = *suffixCursor;
      if ( !suffixChar )
        break;
      suffixNextChar = suffixCursor[1];
      suffixCursor += 2;
      suffixWriteCursor[1] = suffixNextChar;
      suffixWriteCursor += 2;
    }
    while ( suffixNextChar );
    return CSS_PlaySound((int)(intptr_t)soundPath, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;
