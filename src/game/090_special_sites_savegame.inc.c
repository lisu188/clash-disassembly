/* Ports, temples, treasures, persistence, and related dialogs.
 * Original function-marker range: 0x00441DC0..0x0044FE70.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00441DC0) --------------------------------------------------------
int  Audio_PlayUnitMeleeAttackSound(int result)
{
  char *resourceKeyChars; // esi
  char *stemCursor; // edi
  char v3; // al
  char v4; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char v7; // al
  char v8; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPathBuffer, aSfxOddzialy_4, sizeof(soundPathBuffer));
    resourceKeyChars = (&g_UnitTypeResourceKeys)[22 * result];
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v3 = *resourceKeyChars;
      *stemCursor = *resourceKeyChars;
      if ( !v3 )
        break;
      v4 = resourceKeyChars[1];
      resourceKeyChars += 2;
      stemCursor[1] = v4;
      stemCursor += 2;
    }
    while ( v4 );
    suffixChars = aWalka_wav;
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v7 = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !v7 )
        break;
      v8 = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = v8;
      suffixCursor += 2;
    }
    while ( v8 );
    return CSS_PlaySound((int)soundPathBuffer, 64, 0, 0);
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
  char v3; // al
  char v4; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char v7; // al
  char v8; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPathBuffer, aSfxOddzialy_5, sizeof(soundPathBuffer));
    resourceKeyChars = (&g_UnitTypeResourceKeys)[22 * result];
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v3 = *resourceKeyChars;
      *stemCursor = *resourceKeyChars;
      if ( !v3 )
        break;
      v4 = resourceKeyChars[1];
      resourceKeyChars += 2;
      stemCursor[1] = v4;
      stemCursor += 2;
    }
    while ( v4 );
    suffixChars = aGothim_wav;
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v7 = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !v7 )
        break;
      v8 = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = v8;
      suffixCursor += 2;
    }
    while ( v8 );
    return CSS_PlaySound((int)soundPathBuffer, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441F00) --------------------------------------------------------
void  Audio_PlayWorldMapUnitMoveSound(int tileRow, int tileColumn, signed int moveStepCounter, unsigned int unitTypeId)
{
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char *v9; // esi
  char *v10; // edi
  char v11; // al
  char v12; // al
  char *v13; // esi
  char *v14; // edi
  char v15; // al
  char v16; // al
  char *v17; // esi
  char *v18; // edi
  char v19; // al
  char v20; // al
  unsigned int volumeTableIndex; // ebx
  char *v22; // esi
  char *v23; // edi
  char v24; // al
  char v25; // al
  unsigned int tileSurfaceClass; // eax
  char soundPathBuffer[100]; // [esp+0h] [ebp-E4h] BYREF
  char loopSoundPathBuffer[100]; // [esp+64h] [ebp-80h] BYREF
  signed int v29; // [esp+C8h] [ebp-1Ch]
  int loopSampleOffset; // [esp+CCh] [ebp-18h]
  char surfaceSuffix[4]; // [esp+D0h] [ebp-14h] BYREF
  _BYTE airSuffix[16]; // [esp+D4h] [ebp-10h] BYREF

  v29 = tileColumn;
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
    v13 = (&g_UnitMoveSoundStems)[22 * unitTypeId];
    v14 = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v15 = *v13;
      *v14 = *v13;
      if ( !v15 )
        break;
      v16 = v13[1];
      v13 += 2;
      v14[1] = v16;
      v14 += 2;
    }
    while ( v16 );
    if ( (g_UnitTypeFlags[22 * unitTypeId] & 1) != 0 )
    {
      v17 = airSuffix;
      airSuffix[1] = HIBYTE(g_WorldMapUnitMoveSoundSuffixCode);
      airSuffix[0] = g_CurrentUnitMoveSoundVariant + 49;
      goto LABEL_25;
    }
    strcpy(surfaceSuffix, "d0");
    surfaceSuffix[1] = g_CurrentUnitMoveSoundVariant + 49;
    tileSurfaceClass = Map_GetTileSurfaceClassOrUnexplored(tileRow, v29);
    if ( tileSurfaceClass < 0xB7 )
    {
      if ( tileSurfaceClass < 0x93 )
      {
        if ( tileSurfaceClass != 39 )
        {
          v17 = surfaceSuffix;
          goto LABEL_25;
        }
LABEL_37:
        surfaceSuffix[0] = 116;
        v17 = surfaceSuffix;
        goto LABEL_25;
      }
      if ( tileSurfaceClass > 0x93 )
      {
        if ( tileSurfaceClass == 151 )
          surfaceSuffix[0] = 112;
        v17 = surfaceSuffix;
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
        v17 = surfaceSuffix;
        goto LABEL_25;
      }
      v17 = surfaceSuffix;
    }
    else
    {
      if ( tileSurfaceClass == 185 )
        goto LABEL_37;
      v17 = surfaceSuffix;
    }
LABEL_25:
    v18 = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v19 = *v17;
      *v18 = *v17;
      if ( !v19 )
        break;
      v20 = v17[1];
      v17 += 2;
      v18[1] = v20;
      v18 += 2;
    }
    while ( v20 );
    volumeTableIndex = 88 * unitTypeId;
    v22 = a_wav_0;
    v23 = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v24 = *v22;
      *v23 = *v22;
      if ( !v24 )
        break;
      v25 = v22[1];
      v22 += 2;
      v23[1] = v25;
      v23 += 2;
    }
    while ( v25 );
    g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)soundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[volumeTableIndex], 0, 0);
    g_CurrentUnitMoveSoundVariant = (g_CurrentUnitMoveSoundVariant + 1) % (unsigned __int8)g_UnitMoveSoundVariantCounts[volumeTableIndex];
    return;
  }
  if ( unitTypeId != g_CurrentUnitMoveSoundTypeId )
  {
    g_CurrentUnitMoveSoundTypeId = unitTypeId;
    qmemcpy(loopSoundPathBuffer, aSfxRuchy, sizeof(loopSoundPathBuffer));
    v5 = (&g_UnitMoveSoundStems)[22 * unitTypeId];
    v6 = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
    do
    {
      v7 = *v5;
      *v6 = *v5;
      if ( !v7 )
        break;
      v8 = v5[1];
      v5 += 2;
      v6[1] = v8;
      v6 += 2;
    }
    while ( v8 );
    v9 = a_wav;
    v10 = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
    do
    {
      v11 = *v9;
      *v10 = *v9;
      if ( !v11 )
        break;
      v12 = v9[1];
      v9 += 2;
      v10[1] = v12;
      v10 += 2;
    }
    while ( v12 );
    g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)loopSoundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[88 * unitTypeId], 0, 0);
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
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char *v9; // esi
  char *v10; // edi
  char v11; // al
  char v12; // al
  char *v13; // esi
  char *v14; // edi
  char v15; // al
  char v16; // al
  char *v17; // esi
  char *v18; // edi
  char v19; // al
  char v20; // al
  unsigned int volumeTableIndex; // ebx
  char *v22; // esi
  char *v23; // edi
  char v24; // al
  char v25; // al
  unsigned int tileSurfaceClass; // eax
  char soundPathBuffer[100]; // [esp+0h] [ebp-E4h] BYREF
  char loopSoundPathBuffer[100]; // [esp+64h] [ebp-80h] BYREF
  int v29; // [esp+C8h] [ebp-1Ch]
  int loopSampleOffset; // [esp+CCh] [ebp-18h]
  char surfaceSuffix[4]; // [esp+D0h] [ebp-14h] BYREF
  _BYTE airSuffix[16]; // [esp+D4h] [ebp-10h] BYREF

  v29 = tileColumn;
  if ( g_UnitSoundsEnabled )
  {
    if ( unitTypeId == UNIT_TYPE_CANNON || unitTypeId == UNIT_TYPE_RAM || unitTypeId == UNIT_TYPE_CATAPULT || unitTypeId == UNIT_TYPE_FLY )
    {
      if ( unitTypeId != g_CurrentUnitMoveSoundTypeId )
      {
        g_CurrentUnitMoveSoundTypeId = unitTypeId;
        qmemcpy(loopSoundPathBuffer, aSfxRuchy_1, sizeof(loopSoundPathBuffer));
        v5 = (&g_UnitMoveSoundStems)[22 * unitTypeId];
        v6 = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
        do
        {
          v7 = *v5;
          *v6 = *v5;
          if ( !v7 )
            break;
          v8 = v5[1];
          v5 += 2;
          v6[1] = v8;
          v6 += 2;
        }
        while ( v8 );
        v9 = a_wav_1;
        v10 = &loopSoundPathBuffer[strlen(loopSoundPathBuffer)];
        do
        {
          v11 = *v9;
          *v10 = *v9;
          if ( !v11 )
            break;
          v12 = v9[1];
          v9 += 2;
          v10[1] = v12;
          v10 += 2;
        }
        while ( v12 );
        g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)loopSoundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[88 * unitTypeId], 0, 0);
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
      v13 = (&g_UnitMoveSoundStems)[22 * unitTypeId];
      v14 = &soundPathBuffer[strlen(soundPathBuffer)];
      do
      {
        v15 = *v13;
        *v14 = *v13;
        if ( !v15 )
          break;
        v16 = v13[1];
        v13 += 2;
        v14[1] = v16;
        v14 += 2;
      }
      while ( v16 );
      if ( (g_UnitTypeFlags[22 * unitTypeId] & 1) != 0 )
      {
        v17 = airSuffix;
        airSuffix[1] = HIBYTE(g_BattleMapUnitMoveSoundSuffixCode);
        airSuffix[0] = g_CurrentUnitMoveSoundVariant + 49;
      }
      else
      {
        strcpy(surfaceSuffix, "d0");
        surfaceSuffix[1] = g_CurrentUnitMoveSoundVariant + 49;
        tileSurfaceClass = BattleMap_GetMoveSoundSurfaceClass(tileRow, v29);
        if ( tileSurfaceClass )
        {
          if ( tileSurfaceClass <= 1 )
          {
            surfaceSuffix[0] = 116;
            v17 = surfaceSuffix;
          }
          else
          {
            if ( tileSurfaceClass == 2 )
              surfaceSuffix[0] = 100;
            v17 = surfaceSuffix;
          }
        }
        else
        {
          surfaceSuffix[0] = 112;
          v17 = surfaceSuffix;
        }
      }
      v18 = &soundPathBuffer[strlen(soundPathBuffer)];
      do
      {
        v19 = *v17;
        *v18 = *v17;
        if ( !v19 )
          break;
        v20 = v17[1];
        v17 += 2;
        v18[1] = v20;
        v18 += 2;
      }
      while ( v20 );
      volumeTableIndex = 88 * unitTypeId;
      v22 = a_wav_2;
      v23 = &soundPathBuffer[strlen(soundPathBuffer)];
      do
      {
        v24 = *v22;
        *v23 = *v22;
        if ( !v24 )
          break;
        v25 = v22[1];
        v22 += 2;
        v23[1] = v25;
        v23 += 2;
      }
      while ( v25 );
      g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)soundPathBuffer, (unsigned __int8)g_UnitMoveSoundBaseVolumes[volumeTableIndex], 0, 0);
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
void Audio_StopUnitMoveSound()
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
  char v3; // al
  char v4; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char v7; // al
  char v8; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(soundPathBuffer, aSfxButtons, sizeof(soundPathBuffer));
    soundNameChars = result;
    stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v3 = *soundNameChars;
      *stemCursor = *soundNameChars;
      if ( !v3 )
        break;
      v4 = soundNameChars[1];
      soundNameChars += 2;
      stemCursor[1] = v4;
      stemCursor += 2;
    }
    while ( v4 );
    suffixChars = a_wav_3;
    suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
    do
    {
      v7 = *suffixChars;
      *suffixCursor = *suffixChars;
      if ( !v7 )
        break;
      v8 = suffixChars[1];
      suffixChars += 2;
      suffixCursor[1] = v8;
      suffixCursor += 2;
    }
    while ( v8 );
    return (char *)CSS_PlaySound((int)soundPathBuffer, 32, 0, 0);
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
    return CSS_PlaySound((int)soundPathBuffer, 64, 0, 0);
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (004426C0) --------------------------------------------------------
int  Audio_PlaySoundEffectByName(char *soundName, int volume)
{
  char *stemCursor; // edi
  char v5; // al
  char v6; // al
  char *suffixChars; // esi
  char *suffixCursor; // edi
  char v9; // al
  char v10; // al
  char soundPathBuffer[100]; // [esp+0h] [ebp-64h] BYREF

  if ( !g_UnitSoundsEnabled )
    return 0;
  qmemcpy(soundPathBuffer, aSfx, sizeof(soundPathBuffer));
  stemCursor = &soundPathBuffer[strlen(soundPathBuffer)];
  do
  {
    v5 = *soundName;
    *stemCursor = *soundName;
    if ( !v5 )
      break;
    v6 = soundName[1];
    soundName += 2;
    stemCursor[1] = v6;
    stemCursor += 2;
  }
  while ( v6 );
  suffixChars = a_wav_4;
  suffixCursor = &soundPathBuffer[strlen(soundPathBuffer)];
  do
  {
    v9 = *suffixChars;
    *suffixCursor = *suffixChars;
    if ( !v9 )
      break;
    v10 = suffixChars[1];
    suffixChars += 2;
    suffixCursor[1] = v10;
    suffixCursor += 2;
  }
  while ( v10 );
  return CSS_PlaySound((int)soundPathBuffer, volume, 0, 0);
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00442760) --------------------------------------------------------
int  FileSystem_InitRootMount(int a1, char a2, DWORD a3)
{
  const char **filesystem_root; // eax

  filesystem_root = FileSystem_DiskMountCreate(a1, a2, a3);
  FileSystem_ConstructMountTable((int)&g_FileSystemMountTable, (int)filesystem_root, 0, a3);
  return CRT_RegisterFinalizableObject((int)&g_FileSystemRootMountObject, 0);
}

//----- (004427C0) --------------------------------------------------------
int  IO_QueryVTableStreamSize(int a1)
{
  int cursor;
  int size;
  uintptr_t *vtable;

  if ( !a1 )
    return 0;
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)a1;
  if ( !vtable )
    return 0;
  cursor = ((int (*)(int, int))(uintptr_t)vtable[1])(a1, 0);
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)a1;
  ((int (*)(int, int))(uintptr_t)vtable[2])(a1, 0);
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)a1;
  size = ((int (*)(int, int))(uintptr_t)vtable[1])(a1, cursor);
  vtable = (uintptr_t *)(uintptr_t)(unsigned int)*(_DWORD *)a1;
  ((int (*)(int, int))(uintptr_t)vtable[0])(a1, cursor);
  return size;
}

//----- (004427F0) --------------------------------------------------------
int  FileSystem_ResolveReadPath(char *relativePath, int quitOnFailFlag)
{
  int queryHandle; // esi
  char fullPathBuffer[100]; // [esp+0h] [ebp-7Ch] BYREF
  int v14; // [esp+64h] [ebp-18h]

  v14 = quitOnFailFlag;
  g_FileSystemMountOpenMode = 6;
  queryHandle = Compat_FileSystemQuery((int)&g_FileSystemMountTable, relativePath, 0, FileSystem_TryOpenEntryCallback);
  if ( !queryHandle )
  {
    strcpy(fullPathBuffer, aCClash);
    strcat(fullPathBuffer, relativePath);
    g_FileSystemMountOpenMode = 6;
    queryHandle = Compat_FileSystemQuery((int)&g_FileSystemMountTable, fullPathBuffer, 0, FileSystem_TryOpenEntryCallback);
    if ( !queryHandle && v14 )
      App_RequestQuit((int)aIOCouldnTOpenF);
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
char *FileSystem_GetInstallRootPath()
{
  return aCClash;
}

//----- (004429D0) --------------------------------------------------------
int  FileSystem_MountArchiveAtIndex(int mountPrefix, const CHAR *archiveFileName, DWORD mountFlags)
{
  int v3; // eax
  unsigned int v4; // eax
  int *readOnlySource; // eax
  char resolvedPathBuffer[100]; // [esp+0h] [ebp-88h] BYREF
  int errorTextTable[4]; // [esp+64h] [ebp-24h]

  v3 = Compat_CanOpenReadPath(archiveFileName);
  if ( v3 )
  {
    Compat_CopyPrefixN(resolvedPathBuffer, archiveFileName, (unsigned int)strlen(archiveFileName) + 1);
  }
  else
  {
    Compat_CopyPrefixN(resolvedPathBuffer, aCClash, (unsigned int)strlen(aCClash) + 1);
    v4 = (unsigned int)strlen(resolvedPathBuffer) + 1;
    Compat_CopyPrefixN(&resolvedPathBuffer[v4 - 1], archiveFileName, (unsigned int)strlen(archiveFileName) + 1);
    v3 = Compat_CanOpenReadPath(resolvedPathBuffer);
    if ( !v3 )
    {
      errorTextTable[0] = (int)g_ArchiveMountFailedErrorText[0];
      errorTextTable[1] = (int)g_ArchiveMountFailedErrorText[1];
      errorTextTable[2] = (int)g_ArchiveMountFailedErrorText[2];
      errorTextTable[3] = (int)g_ArchiveMountFailedErrorText[3];
      App_RequestQuit(errorTextTable[(unsigned __int8)g_LanguageIndex]);
    }
  }
  readOnlySource = File_AllocateReadOnlySource(resolvedPathBuffer, mountFlags, 0, mountFlags, (int)resolvedPathBuffer);
  return FileSystem_AddMountEntry(g_FileSystemMountTable, (const CHAR *)(uintptr_t)(unsigned int)mountPrefix, 0, (DWORD)readOnlySource);
}
// 442A16: variable 'v3' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 517B14: using guessed type char *off_517B14[3];
// 543CC8: using guessed type int dword_543CC8[11];

//----- (00442AD0) --------------------------------------------------------
int __thiscall ResourceArchives_MountStartupArchives(int this)
{
  const CHAR *v3; // edx
  char *v4; // eax
  const CHAR *v5; // edx
  char *v6; // eax
  int v7; // ecx
  int v9[3]; // [esp+0h] [ebp-1Ch]
  int v10[4]; // [esp+Ch] [ebp-10h] BYREF

  v10[2] = this;
  FileSystem_MountArchiveAtIndex((int)aDot_MinimumResourcePrefix, aDataMinimum_re, 0x14u);
  FileSystem_MountArchiveAtIndex((int)aDot_NormalResourcePrefix, aDataNormal_res, 1u);
  FileSystem_MountArchiveAtIndex((int)aDot_MaximumResourcePrefix, aDataMaximum_re, 1u);
  FileSystem_MountArchiveAtIndex((int)aMaps_0, aDataMaps_res, 1u);
  FileSystem_MountArchiveAtIndex((int)aGfx_6, aDataGfx3_res, 1u);
  if ( !g_LanguageIndex )
  {
    v3 = aDataInfopol_re;
    v4 = aGfxBiginfo_pol;
LABEL_3:
    FileSystem_MountArchiveAtIndex((int)v4, v3, 1u);
    goto LABEL_4;
  }
  if ( (unsigned __int8)g_LanguageIndex <= 1u )
  {
    v3 = aDataInfoang_re;
    v4 = aGfxBiginfo_eng;
    goto LABEL_3;
  }
  if ( g_LanguageIndex == 2 )
  {
    v3 = aDataInfoger_re;
    v4 = aGfxBiginfo_ger;
    goto LABEL_3;
  }
LABEL_4:
  if ( !g_LanguageIndex )
  {
    v5 = aDataMisinfop_r;
    v6 = aGfxMisinfo;
LABEL_6:
    FileSystem_MountArchiveAtIndex((int)v6, v5, 1u);
    goto LABEL_7;
  }
  if ( (unsigned __int8)g_LanguageIndex <= 1u )
  {
    FileSystem_MountArchiveAtIndex((int)aGfxMisinfo_0, aDataMisinfoa_r, 1u);
    v5 = aDataMiswava_re;
    v6 = aSfxMisinfo;
    goto LABEL_6;
  }
  if ( g_LanguageIndex == 2 )
  {
    v5 = aDataMisinfog_r;
    v6 = aGfxMisinfo_1;
    goto LABEL_6;
  }
LABEL_7:
  FileSystem_MountArchiveAtIndex((int)aSfxMusic_0, aDataMusic_res, 1u);
  CSS_SetFileSystem((int)g_FileSystemMountTable);
  v10[0] = FileSystem_ResolveReadPath(aGfxBackgr1_s32, 0);
  if ( !v10[0] )
  {
    v9[0] = (int)g_StartupResourceMissingErrorText[0];
    v9[1] = (int)g_StartupResourceMissingErrorText[1];
    v9[2] = (int)g_StartupResourceMissingErrorText[2];
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
    Debug_Log(0, (char)sourcePath, (DWORD)destPath, (int)aNotEnoughMe_11);
    App_RequestQuit((int)aNotEnoughMe_12);
  }
  query_handle = FileSystem_ResolveReadPath(sourcePath, 1);
  if ( !query_handle )
    App_RequestQuit((int)aBrakPlikuS);

  output_handle = IO_FOpen(destPath, (unsigned __int8 *)aWb_2, 0, (DWORD)destPath);
  do
  {
    bytes_read = Compat_QueryRead(query_handle, copy_buffer, 0x80000);
    if ( bytes_read )
      fwrite_(copy_buffer, bytes_read, output_handle, 1);
  }
  while ( bytes_read == 0x80000 );
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &query_handle);
  fclose_(output_handle);
  Compat_FreeLow32Bytes((int)(uintptr_t)copy_buffer);
  return 0;
}
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00442D90) --------------------------------------------------------
int Port_FindAndInit()
{
  int rowIndex; // esi
  int rowOffset; // edi
  int result; // eax
  int columnIndex; // eax
  int tileStride; // edx
  int tileId; // ecx
  int dataBase; // eax
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
    if ( rowIndex >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      return result;
    columnIndex = 0;
    for ( tileStride = 0; ; tileStride += 14 )
    {
      if ( columnIndex >= *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET) )
      {
        rowOffset += TILE_TERRAIN_ROW_STRIDE;
        ++rowIndex;
        goto LABEL_2;
      }
      tileId = *(unsigned __int16 *)(rowOffset + gameData + tileStride + 2);
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
    shoreTileId = *(unsigned __int16 *)(portColumnOffset + gameData + TILE_TERRAIN_ROW_STRIDE * PORT_ROW + 2);
    if ( shoreTileId == 726 || shoreTileId == 722 )
    {
      bottomRightTile = (_WORD *)(TILE_TERRAIN_RECORD_STRIDE * (PORT_COLUMN + 1) + gameData + TILE_TERRAIN_ROW_STRIDE * (PORT_ROW + 1));
      *bottomRightTile = 715;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE * (PORT_ROW + 1) + TILE_TERRAIN_RECORD_STRIDE * PORT_COLUMN) = *bottomRightTile;
    }
    else
    {
      bottomLeftTile = (_WORD *)(TILE_TERRAIN_ROW_STRIDE * (PORT_ROW + 1) + gameData + portColumnOffset);
      *bottomLeftTile = 715;
      *(_WORD *)(TILE_TERRAIN_RECORD_STRIDE * PORT_COLUMN + gameData + TILE_TERRAIN_ROW_STRIDE * PORT_ROW) = *bottomLeftTile;
    }
    Port_UpdateShorelineVariantTiles();
    Rules_LogPortLocation();
    rowOffset += TILE_TERRAIN_ROW_STRIDE;
    ++rowIndex;
  }
}
// 5202E4: using guessed type int gameData;

//----- (00442F60) --------------------------------------------------------
_DWORD *Rules_LogPortLocation()
{
  _DWORD *result; // eax
  int portRow; // edx
  double v3; // st7
  int v4; // ecx
  char logTextBuffer[204]; // [esp+0h] [ebp-CCh] BYREF

  result = (_DWORD *)gameData;
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
  int dataBase; // eax
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
      if ( *(unsigned __int16 *)(gameData + GAME_TURN_COUNTER_OFFSET) >= reinforcementArrivalTurn )
      {
      PORT_SHORE_VARIANT_FLAG = 1;
      PORT_REINFORCEMENT_READY_FLAG = PORT_SHORE_VARIANT_FLAG;
        PORT_REINFORCEMENT_UNIT_COUNT = Rng_RandRange(3, 5);
        Debug_Log(logArg, reinforcementArrivalTurn, logContext, (int)aPort_newturnPo);
      }
    }
    return Port_UpdateShorelineVariantTiles();
  }
  return result;
}
// 443038: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00443090) --------------------------------------------------------
int Port_UpdateShorelineVariantTiles()
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
          switch ( *(_WORD *)(tileAddr + 2) )
          {
            case 0x2D0:
              *(_WORD *)(tileAddr + 2) = 718;
              break;
            case 0x2D1:
              *(_WORD *)(tileAddr + 2) = 719;
              break;
            case 0x2D6:
              *(_WORD *)(tileAddr + 2) = 722;
              break;
            case 0x2D7:
              *(_WORD *)(tileAddr + 2) = 724;
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
          switch ( *(_WORD *)(tileAddrB + 2) )
          {
            case 0x2CE:
              *(_WORD *)(tileAddrB + 2) = 720;
              break;
            case 0x2CF:
              *(_WORD *)(tileAddrB + 2) = 721;
              break;
            case 0x2D2:
              *(_WORD *)(tileAddrB + 2) = 726;
              break;
            case 0x2D4:
              *(_WORD *)(tileAddrB + 2) = 727;
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
int Port_IsReinforcementReady()
{
  return PORT_REINFORCEMENT_READY_FLAG;
}
// 5202E4: using guessed type int gameData;

//----- (00443240) --------------------------------------------------------
int * Port_GenerateApproachTrack(int unitStackIndex)
{
  int v1; // ecx
  int portRow; // ebp
  int v4; // edi
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  __int16 v8; // ax
  int stackColumn; // ebx
  int *trackList; // ecx
  int *v11; // eax
  int *v12; // ecx
  int *v13; // edx
  int v14; // ebx
  int v15; // edi
  int v16; // esi
  int v17; // esi
  int v18; // ebx
  int v19; // edx
  int v20; // ebp
  int v21; // edx
  int v22; // ebx
  int v23; // esi
  int v24; // esi
  int v25; // eax
  __int16 v26; // [esp+0h] [ebp-30h]
  __int16 v27; // [esp+4h] [ebp-2Ch]
  __int16 v28; // [esp+8h] [ebp-28h]
  __int16 v29; // [esp+Ch] [ebp-24h]
  int portRowByteOffset; // [esp+10h] [ebp-20h]
  int v31; // [esp+14h] [ebp-1Ch]
  int portColumn; // [esp+20h] [ebp-10h]

  v1 = PORT_ROW;
  if ( v1 == -1 )
    return 0;
  portRow = PORT_ROW;
  portColumn = PORT_COLUMN;
  portRowByteOffset = TILE_TERRAIN_ROW_STRIDE * v1;
  v4 = TILE_TERRAIN_ROW_STRIDE * v1 + gameData;
  v26 = *(_WORD *)(v4 + 14 * portColumn);
  v5 = TILE_TERRAIN_ROW_STRIDE * (v1 + 1) + gameData;
  v6 = TILE_TERRAIN_ROW_STRIDE * (v1 + 1);
  v27 = *(_WORD *)(v5 + 14 * portColumn);
  v31 = v5;
  v7 = 14 * (portColumn + 1);
  v28 = *(_WORD *)(v7 + v4);
  v8 = *(_WORD *)(v7 + v31);
  *(_WORD *)(v4 + 14 * portColumn) = 0;
  v29 = v8;
  *(_WORD *)(14 * portColumn + v6 + gameData) = 0;
  *(_WORD *)(v7 + portRowByteOffset + gameData) = 0;
  *(_WORD *)(v7 + v6 + gameData) = 0;
  stackColumn = *(__int16 *)(gameData + UNIT_STACK_STRIDE * unitStackIndex + 147176);
  trackList = Unit_MoveTrack(unitStackIndex, *(__int16 *)(gameData + UNIT_STACK_STRIDE * unitStackIndex + UNIT_STACK_TABLE_OFFSET), portRow, stackColumn, portRow, portColumn);
  if ( trackList )
  {
    v11 = (int *)Mem_Alloc(404, (int)trackList, stackColumn, portRow);
    v13 = v11;
    if ( v11 )
      *v11 = 0;
    while ( *v12 )
    {
      v14 = *v12 - 1;
      *v12 = v14;
      v15 = *v11;
      v16 = v12[v14 + 1];
      if ( *v11 < 100 )
      {
        *v11 = v15 + 1;
        v11[v15 + 1] = v16;
      }
    }
    if ( *v11 )
    {
      do
      {
        v22 = v11[*v11];
        v23 = *v11 - 1;
        if ( portRow > (unsigned __int8)v22 )
          break;
        if ( (unsigned __int8)v22 > portRow + 1 )
          break;
        if ( BYTE1(v22) < portColumn )
          break;
        if ( BYTE1(v22) > portColumn + 1 )
          break;
        *v11 = v23;
      }
      while ( v23 );
    }
    while ( 1 )
    {
      v17 = *v13;
      if ( !*v13 )
        break;
      *v13 = v17 - 1;
      v24 = v13[v17];
      v25 = *v12;
      if ( *v12 < 100 )
      {
        *v12 = v25 + 1;
        v12[v25 + 1] = v24;
      }
    }
    j__nfree_();
  }
  v18 = TILE_TERRAIN_ROW_STRIDE * portRow;
  v19 = 14 * portColumn;
  *(_WORD *)(v19 + gameData + TILE_TERRAIN_ROW_STRIDE * portRow) = v26;
  v20 = TILE_TERRAIN_ROW_STRIDE * (portRow + 1);
  *(_WORD *)(v20 + gameData + v19) = v27;
  v21 = 14 * (portColumn + 1);
  *(_WORD *)(v21 + gameData + v18) = v28;
  *(_WORD *)(v20 + gameData + v21) = v29;
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
  int v5; // edx
  int spawnSlotIndex; // edi
  int i; // esi
  int spawnRow; // ebx
  int spawnColumn; // ecx
  int v10; // eax
  DWORD v11; // ebp
  char v12; // bl
  int v13; // ecx
  int v14; // edx
  int remainingUnitCount; // esi
  signed int j; // edi
  unsigned int unitPoolIndex; // eax
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  unsigned int v23; // eax
  int v24; // ecx
  int v25; // eax
  int v26; // ecx
  int v27; // ecx
  char v28; // [esp+0h] [ebp-3Ch]
  int v29; // [esp+0h] [ebp-3Ch]
  int v30; // [esp+4h] [ebp-38h]
  int v31; // [esp+8h] [ebp-34h]
  int portRow; // [esp+Ch] [ebp-30h]
  int portColumn; // [esp+10h] [ebp-2Ch]
  int v34; // [esp+18h] [ebp-24h]
  int v35; // [esp+1Ch] [ebp-20h]
  int v36; // [esp+20h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)aPort_getsupply, v28);
  if ( PORT_ROW == -1 )
    return 0;
  portRow = PORT_ROW;
  portColumn = PORT_COLUMN;
  result = Port_IsReinforcementReady();
  if ( result )
  {
    v31 = 0;
    v35 = v5 - 1;
    v30 = portColumn - 1;
    v36 = 200 * (v5 - 1);
    if ( v36 <= 200 * (v5 + 2) )
    {
      v34 = 2 * (portColumn + 2);
      do
      {
        v25 = 2 * v30;
        if ( 2 * v30 <= v34 )
        {
          while ( 1 )
          {
            v26 = *(unsigned __int16 *)(gameData + v36 + v25 + TILE_MAP_OFFSET);
            if ( (unsigned __int16)v26 <= 0x1F4u )
            {
              v27 = UNIT_STACK_STRIDE * v26;
              if ( (unsigned int)*(__int16 *)(v27 + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28
                && *(unsigned __int8 *)(v27 + gameData + 147178) == g_CurrentPlayerIndex )
              {
                break;
              }
            }
            v25 += 2;
            if ( v25 > v34 )
              goto LABEL_16;
          }
          v31 = 1;
        }
LABEL_16:
        v36 += 200;
        ++v35;
      }
      while ( v36 <= 200 * (v5 + 2) );
    }
    result = v31;
    if ( v31 )
    {
      spawnSlotIndex = 0;
      for ( i = 0; i < 12; ++i )
      {
        spawnRow = g_PortReinforcementSpawnRingOffsets[i].row_delta + portRow;
        spawnColumn = g_PortReinforcementSpawnRingOffsets[i].column_delta + portColumn;
        if ( *(unsigned __int16 *)(TILE_INDEX(spawnRow, spawnColumn)) == 0xFFFF
          && Map_GetUnitTileMoveCostOrZero(g_CurrentPlayerIndex, 0, spawnColumn, spawnRow) )
        {
          break;
        }
        ++spawnSlotIndex;
      }
      if ( spawnSlotIndex == 12 )
        return 0;
      v29 = g_PortReinforcementSpawnRingOffsets[spawnSlotIndex].column_delta + PORT_COLUMN;
      v10 = g_PortReinforcementSpawnRingOffsets[spawnSlotIndex].row_delta;
      v11 = v10 + PORT_ROW;
      v12 = Facing_DirectionFromDelta8(v10, g_PortReinforcementSpawnRingOffsets[spawnSlotIndex].column_delta);
      Unit_Create(UNIT_TYPE_PEASANT, g_CurrentPlayerIndex, v11, v12, a4, v29);
      v14 = 145 * *(unsigned __int16 *)(TILE_INDEX(v11, v29));
      remainingUnitCount = PORT_REINFORCEMENT_UNIT_COUNT - 1;
      for ( j = UNIT_STACK_STRIDE * *(unsigned __int16 *)(TILE_INDEX(v11, v29)) + gameData + UNIT_STACK_TABLE_OFFSET;
            remainingUnitCount >= 0;
            v13 = v19 - 31 )
      {
        v12 = g_CurrentPlayerIndex;
        unitPoolIndex = Rng_RandRange(0, 11);
        --remainingUnitCount;
        UnitSlot_InitFromType(v18, g_PortReinforcementUnitTypePool[unitPoolIndex], v12);
      }
      Rules_LinkArmyFact(j, v14, v13, a4, v12, v11);
      Rules_SyncArmyFactStrength(j, v20, v21, v12, v11, a4);
      UI_StartWorldMapUnitAttentionFlash(*(unsigned __int16 *)(TILE_INDEX(v11, v29)), 200 * v11 + gameData, v22);
      PORT_REINFORCEMENT_READY_FLAG = 0;
      v23 = Rng_RandRange(8, 10);
      PORT_NEXT_REINFORCEMENT_TURN = v24 + v23;
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
  _DWORD *v3; // eax
  _DWORD *Surface; // eax
  int v5; // ebp
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  DWORD v8; // ebp
  __int16 v9; // ax
  int SpriteForChar; // eax
  char *portLabelText; // eax
  __int16 v12; // ax
  void *result; // eax
  unsigned __int16 v14; // [esp+10h] [ebp-4Ch]
  unsigned __int16 v15; // [esp+10h] [ebp-4Ch]
  unsigned __int16 v16; // [esp+14h] [ebp-48h]
  unsigned __int16 v17; // [esp+18h] [ebp-44h]
  int v18[3]; // [esp+1Ch] [ebp-40h]
  int v19[3]; // [esp+28h] [ebp-34h] BYREF
  _DWORD *portSpriteSet; // [esp+34h] [ebp-28h] BYREF
  void *previousRenderDevice; // [esp+38h] [ebp-24h]
  int panelLeft; // [esp+3Ch] [ebp-20h]
  int panelTop; // [esp+40h] [ebp-1Ch]

  previousRenderDevice = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  Render_Pump();
  v3 = (_DWORD *)Mem_Alloc(4112, v2, a1, a2);
  if ( v3 )
    v3 = DLXSpriteSet_Load(v3, "port.s32");
  portSpriteSet = v3;
  panelLeft = 100;
  panelTop = 100;
  Surface = (_DWORD *)Mem_Alloc(188, 100, a1, a2);
  v5 = (int)Surface;
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)portSpriteSet, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)portSpriteSet, 0);
    Surface = Render_CreateSurface(v5, SpriteHeight, SpriteWidth);
  }
  v8 = (DWORD)Surface;
  v14 = panelTop + DLX_GetSpriteWidth((int)portSpriteSet, 0) - 1;
  v9 = DLX_GetSpriteHeight((int)portSpriteSet, 0);
  Render_FillRect(0, (_DWORD *)v8, (unsigned __int16)panelTop, (unsigned __int16)panelLeft, panelLeft + v9 - 1, v14, 0, 0);
  Render_ReleaseSurface(7, v8);
  SpriteForChar = DLX_GetSpriteForChar((int)portSpriteSet, PORT_REINFORCEMENT_READY_FLAG);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
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
  UI_DrawTextFmt((int)v19, panelLeft + 10, panelLeft + 235, panelTop + 5, 3, (int)portLabelText);
  v19[0] = (int)g_PortReinforcementArrivedTexts[0];
  v19[1] = (int)g_PortReinforcementArrivedTexts[1];
  v19[2] = (int)g_PortReinforcementArrivedTexts[2];
  v18[0] = (int)g_PortEmptyTexts[0];
  v18[1] = (int)g_PortEmptyTexts[1];
  v18[2] = (int)g_PortEmptyTexts[2];
  if ( PORT_REINFORCEMENT_READY_FLAG )
  {
    UI_DrawTextFmt((int)v19, panelLeft + 122, panelLeft + 200, panelTop + 54, 6, v19[(unsigned __int8)g_LanguageIndex]);
    Render_ReleaseSurface(15, v8);
    UI_DrawTextFmt((int)v19, panelLeft + 42, panelLeft + 85, panelTop + 29, 1, (int)aD_36);
  }
  else
  {
    UI_DrawTextFmt(
      v18[(unsigned __int8)g_LanguageIndex],
      panelLeft + 40,
      panelLeft + 120,
      panelTop + 40,
      6,
      v18[(unsigned __int8)g_LanguageIndex]);
  }
  Render_Begin((int)g_RenderState, 0);
  v17 = panelTop;
  v16 = panelLeft;
  v15 = DLX_GetSpriteWidth((int)portSpriteSet, 0) - 1;
  v12 = DLX_GetSpriteHeight((int)portSpriteSet, 0);
  Render_FillRect((_DWORD *)v8, 0, 0, 0, v12 - 1, v15, v16, v17);
  if ( v8 )
    (**(void (__cdecl ***)(int, int, int, int, int, int))(v8 + 184))(v18[0], v18[1], v18[2], v19[0], v19[1], v19[2]);
  DLXSpriteSet_ReleaseAndClear((int *)&portSpriteSet);
  Render_Present((int)g_RenderState);
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
int Rules_RebuildTreasureFacts()
{
  int i; // ebx
  int result; // eax
  int j; // ecx
  int v4; // ecx

  for ( i = 0; ; ++i )
  {
    result = gameData;
    if ( i >= *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET) )
      break;
    for ( j = 0; j < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET); j = v4 + 1 )
    {
      if ( MapTile_HasHiddenTreasure(i, j) )
        Rules_LogTreasureFact(i, v4);
    }
  }
  return result;
}
// 443B98: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00443BB0) --------------------------------------------------------
BOOL  MapTile_HasHiddenTreasure(int tileRow, int tileColumn)
{
  int tileId; // eax

  tileId = *(unsigned __int16 *)(gameData + TILE_TERRAIN_ROW_STRIDE * tileRow + TILE_TERRAIN_RECORD_STRIDE * tileColumn);
  return tileId == 755 || tileId == 752;
}
// 5202E4: using guessed type int gameData;

//----- (00443C20) --------------------------------------------------------
signed int  Treasure_TryDigHere(
        int a1,
        char a2,
        DWORD a3,
        char a4,
        char *a5,
        double a6)
{
  char v6; // bl
  int unitStackIndex; // edx
  __int16 *stackTileRecord; // ebp
  int v9; // ecx
  int v11; // ecx
  _BYTE *v12; // ecx
  _DWORD *v13; // ecx
  unsigned __int16 *tileWordPtr; // edx
  unsigned __int16 tileValue; // ax
  DWORD *v16; // ecx
  void *v17; // eax
  int v18; // eax
  _BYTE v19[24]; // [esp+0h] [ebp-40h] BYREF
  _BYTE v20[40]; // [esp+18h] [ebp-28h] BYREF

  Debug_Log(a1, a2, a3, (int)aTreasure_dighe, a1);
  v6 = gameData;
  stackTileRecord = (__int16 *)(UNIT_STACK_STRIDE * unitStackIndex + gameData + UNIT_STACK_TABLE_OFFSET);
  if ( !MapTile_HasHiddenTreasure(*(__int16 *)(gameData + UNIT_STACK_STRIDE * unitStackIndex + UNIT_STACK_TABLE_OFFSET), *(__int16 *)(gameData + UNIT_STACK_STRIDE * unitStackIndex + 147176))
    || !UnitStack_HasBuilder(v9) )
  {
    return 0;
  }
  if ( ACTIVE_MISSION_INDEX == 7
    && (*stackTileRecord == 55 && stackTileRecord[1] == 45 || *stackTileRecord == 50 && stackTileRecord[1] == 27 || *stackTileRecord == 35 && stackTileRecord[1] == 63 || *stackTileRecord == 14 && stackTileRecord[1] == 68) )
  {
    qmemcpy(v20, &g_Mission7ScriptedTreasureEventData, 0x18u);
    a5 = (char *)&g_Mission7ScriptedTreasureEventData + 24;
    v12 = v20;
  }
  else if ( ACTIVE_MISSION_INDEX == 17
         && (*stackTileRecord == 50 && stackTileRecord[1] == 34 || *stackTileRecord == 51 && stackTileRecord[1] == 73
                                      || *stackTileRecord == 77 && stackTileRecord[1] == 34
                                      || *stackTileRecord == 24 && stackTileRecord[1] == 49) )
  {
    qmemcpy(v19, &g_Mission17ScriptedTreasureEventData, sizeof(v19));
    a5 = (char *)&g_Mission17ScriptedTreasureEventData + 24;
    v12 = v19;
  }
  else
  {
    if ( *(_DWORD *)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackTileRecord + 4) + gameData + 140051) )
      v17 = &g_TreasureDigOutcomeTable_TempleActive;
    else
      v17 = &g_TreasureDigOutcomeTable_TempleInactive;
    v18 = Temple_Random((int)v17, v11, v6, (DWORD)stackTileRecord, a4);
    Debug_Log(v18, v6, (DWORD)stackTileRecord, (int)aTreasure_dig_0, v18);
  }
  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackTileRecord + 4) + 140051) )
  {
    Win_PlayModeChangeFrameTransition((int)aKop_bud, 1, (int)v12, v6, (DWORD)stackTileRecord, (char)a5);
    Temple_ShowOutcomePopup(v13[(unsigned __int8)g_LanguageIndex + 3], v13[2], (int)v13, *v13 != 15, (DWORD)stackTileRecord);
  }
  tileWordPtr = (unsigned __int16 *)(TILE_TERRAIN_ROW_STRIDE * *stackTileRecord + gameData + TILE_TERRAIN_RECORD_STRIDE * stackTileRecord[1]);
  tileValue = *tileWordPtr;
  if ( *tileWordPtr >= 0x2F0u )
  {
    if ( tileValue > 0x2F0u )
    {
      if ( tileValue == 755 )
        *tileWordPtr = 4;
    }
    else
    {
      *tileWordPtr = 0;
    }
  }
  Rules_RetractTreasureFact(*stackTileRecord, stackTileRecord[1], a6);
  Temple_ProcessGift(*v16, (int)stackTileRecord, stackTileRecord[1], *stackTileRecord, a6);
  return 1;
}
// 443C53: variable 'v7' is possibly undefined
// 443C85: variable 'v9' is possibly undefined
// 443CF5: variable 'v12' is possibly undefined
// 443D10: variable 'v13' is possibly undefined
// 443D88: variable 'v16' is possibly undefined
// 443E76: variable 'v11' is possibly undefined
// 511130: using guessed type char byte_511130;
// 5202E4: using guessed type int gameData;

//----- (00443EB0) --------------------------------------------------------
signed int  UnitStack_TryHide(int unitStackIndex, unsigned __int16 neighborStackIndex, DWORD a3, double a4)
{
  __int16 *stackRecord; // esi
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int lowRankMessageTable[3]; // [esp+0h] [ebp-3Ch]
  int noSpotMessageTable[3]; // [esp+Ch] [ebp-30h] BYREF
  int spotBlocked; // [esp+18h] [ebp-24h] BYREF
  int v19; // [esp+1Ch] [ebp-20h]
  int v20; // [esp+20h] [ebp-1Ch]

  stackRecord = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * unitStackIndex);
  if ( UnitStack_GetMinCurrentActionPoints((intptr_t)stackRecord) < 0 || *((_BYTE *)stackRecord + 720) || !UnitStack_HasNormalCombatUnits((intptr_t)stackRecord) )
    return 0;
  if ( UnitStack_GetMaxOrderTier((intptr_t)stackRecord) < 2 )
  {
    if ( *(_DWORD *)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackRecord + 4) + gameData + 140051) )
    {
      lowRankMessageTable[0] = (int)g_UnitHideFailedLowRankText[0];
      lowRankMessageTable[1] = (int)g_UnitHideFailedLowRankText[1];
      lowRankMessageTable[2] = (int)g_UnitHideFailedLowRankText[2];
      Audio_PlaySoundEffectByName(aWrong_0, 64);
      UI_ShowInfoWindow(lowRankMessageTable[(unsigned __int8)g_LanguageIndex], 1u, v6, a3, (int)noSpotMessageTable, (int)&g_UnitHideFailedLowRankText[3]);
      return 0;
    }
    return 0;
  }
  spotBlocked = 0;
  v20 = -8;
  do
  {
    v7 = -8;
    v19 = v20 * v20;
    while ( 1 )
    {
      if ( Math_CeilSqrt(v19 + v7 * v7) <= 8 )
      {
        neighborStackIndex = *(_WORD *)(gameData + TILE_ROW_STRIDE * (v8 + *stackRecord) + 2 * (v20 + stackRecord[1]) + TILE_MAP_OFFSET);
        if ( neighborStackIndex != 0xFFFF )
        {
          if ( neighborStackIndex <= 0x1F4u )
          {
            v9 = UNIT_STACK_STRIDE * neighborStackIndex;
            if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + v9 + 6) <= 0x28
              && *(_BYTE *)(gameData + v9 + 147178) != *((_BYTE *)stackRecord + 4) )
            {
              break;
            }
          }
          v11 = neighborStackIndex - TILE_OCCUPANT_BUILDING_INDEX_BASE;
          if ( v11 <= 0x64 )
          {
            v12 = BUILDING_RECORD_SIZE * v11;
            LOBYTE(neighborStackIndex) = gameData;
            v13 = v12 + gameData + BUILDING_TABLE_OFFSET;
            if ( (unsigned int)*(char *)(v13 + 4) < 4
              && *(__int16 *)(v13 + 16) != -1
              && *(_BYTE *)(gameData + v12 + 509676) != *((_BYTE *)stackRecord + 4) )
            {
              break;
            }
          }
        }
      }
      v7 = v8 + 1;
      if ( v7 >= 8 )
        goto LABEL_16;
    }
    spotBlocked = 1;
LABEL_16:
    ++v20;
  }
  while ( v20 < 8 );
  if ( spotBlocked )
  {
    if ( !*(_DWORD *)(PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackRecord + 4) + gameData + 140051) )
      return 0;
    noSpotMessageTable[0] = (int)g_UnitHideFailedNoSpotText[0];
    noSpotMessageTable[1] = (int)g_UnitHideFailedNoSpotText[1];
    noSpotMessageTable[2] = (int)g_UnitHideFailedNoSpotText[2];
    Audio_PlaySoundEffectByName(aWrong_1, 64);
    UI_ShowInfoWindow(noSpotMessageTable[(unsigned __int8)g_LanguageIndex], 0, v10, 0, (int)&spotBlocked, (int)&g_UnitHideFailedNoSpotText[3]);
    return 0;
  }
  else
  {
    UnitStack_ClearRemainingActionPoints(stackRecord, 0, a4);
    v15 = PLAYER_DATA_STRIDE * *((unsigned __int8 *)stackRecord + 4);
    *((_BYTE *)stackRecord + 720) = 1;
    if ( *(_DWORD *)(gameData + v15 + 140051) )
      Win_PlayModeChangeFrameTransition(aUkrycie, 1, v14, neighborStackIndex, 0);
    WorldMap_RedrawTileIfVisible(*stackRecord, stackRecord[1]);
    return 1;
  }
}
// 443FDF: simplified comparisons for 'eax.4': <0 || >=1F5 became >=1F5u
// 444003: simplified comparisons for 'edi.4': <0 || >=29 became >=29u
// 4440B6: simplified comparisons for 'eax.4': <0 || >=65 became >=65u
// 4440D7: simplified comparisons for 'edi.4': <0 || >=4 became >=4u
// 443F5C: variable 'v6' is possibly undefined
// 443FAA: variable 'v8' is possibly undefined
// 44408D: variable 'v10' is possibly undefined
// 44412B: variable 'v14' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 517DE8: using guessed type char *off_517DE8[6];
// 517DF4: using guessed type char *off_517DF4[3];
// 5202E4: using guessed type int gameData;

//----- (00444150) --------------------------------------------------------
signed int  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(unsigned int attackingStackIndex, double a2)
{
  __int16 *stack; // ebx
  int result; // [esp+8h] [ebp-2Ch]
  int neighbor_index;

  if ( attackingStackIndex > 0x1F4 )
    return 0;
  stack = (__int16 *)UNIT_STACK(attackingStackIndex);
  if ( (unsigned int)stack[3] > 0x28 )
    return 0;

  result = 0;
  if ( UnitStack_GetMaxOrderTier((intptr_t)stack) >= 3 )
  {
    int vision_radius = UnitStack_GetVisionRadius((int)stack);
    int center_row = *stack;
    int center_column = stack[1];
    int row;

    for ( row = center_row - vision_radius; row < center_row + vision_radius; ++row )
    {
      int column;

      if ( row < 0 || row >= MAP_WIDTH_TILES )
        continue;
      for ( column = center_column - vision_radius; column < center_column + vision_radius; ++column )
      {
        unsigned int hidden_stack_index;
        int distance;

        if ( column < 0 || column >= MAP_HEIGHT_TILES )
          continue;
        distance = Math_CeilSqrt(
                     (column - center_column) * (column - center_column)
                   + (row - center_row) * (row - center_row));
        if ( distance > vision_radius )
          continue;
        hidden_stack_index = *(unsigned __int16 *)(TILE_INDEX(row, column));
        if ( hidden_stack_index <= 0x1F4 )
        {
          __int16 *hidden_stack = (__int16 *)UNIT_STACK(hidden_stack_index);
          if ( (unsigned int)hidden_stack[3] <= 0x28
            && UNIT_STACK_OWNER_INDEX((int)hidden_stack) != UNIT_STACK_OWNER_INDEX((int)stack)
            && *((_BYTE *)hidden_stack + 720) )
          {
            *((_BYTE *)hidden_stack + 720) = 0;
            WorldMap_RedrawViewport(1);
          }
        }
      }
    }
  }

  for ( neighbor_index = 0; neighbor_index < 24; neighbor_index += 2 )
  {
    int row = Map_NeighborDX[neighbor_index] + *stack;
    int column = Map_NeighborDY[neighbor_index] + stack[1];
    unsigned int adjacent_stack_index;

    if ( row < 0 || row >= MAP_WIDTH_TILES || column < 0 || column >= MAP_HEIGHT_TILES )
      continue;
    adjacent_stack_index = *(unsigned __int16 *)(TILE_INDEX(row, column));
    if ( adjacent_stack_index <= 0x1F4 )
    {
      __int16 *adjacent_stack = (__int16 *)UNIT_STACK(adjacent_stack_index);
      if ( (unsigned int)adjacent_stack[3] <= 0x28
        && UNIT_STACK_OWNER_INDEX((int)adjacent_stack) != UNIT_STACK_OWNER_INDEX((int)stack)
        && *((_BYTE *)adjacent_stack + 720) )
      {
        Unit_Attack(adjacent_stack_index, attackingStackIndex, (char)stack, 1u, a2);
        UnitStack_ClearRemainingActionPoints(stack, 1u, a2);
        *((_BYTE *)adjacent_stack + 720) = 0;
        result = 1;
        WorldMap_RedrawViewport(1);
      }
    }
    if ( attackingStackIndex > 0x1F4 )
      break;
    if ( (unsigned int)*(__int16 *)(UNIT_STACK(attackingStackIndex) + 6) > 0x28 )
      break;
  }
  return result;
}
// 444212: simplified comparisons for 'edi.4': <0 || >=29 became >=29u
// 44425E: simplified comparisons for '%var_28.4': <0 || >=1F5 became >=1F5u
// 44427C: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 44437B: simplified comparisons for 'edi.4': <0 || >=29 became >=29u
// 444283: variable 'j' is possibly undefined
// 444342: variable 'v12' is possibly undefined
// 4443AC: variable 'v11' is possibly undefined
// 513334: using guessed type int dword_513334[];
// 513338: using guessed type int dword_513338[63];
// 5202E4: using guessed type int gameData;

//----- (004443C0) --------------------------------------------------------
int  SaveSlot_FormatDataFilePath(int slotIndex, char *outPath)
{
  return sprintf_(outPath, "save\\%d.dat", slotIndex);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004443D0) --------------------------------------------------------
int  SaveSlot_FormatFactsFilePath(int slotIndex, char *outPath)
{
  return sprintf_(outPath, "save\\%d.fac", slotIndex);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004443E0) --------------------------------------------------------
signed int  saveGame(int slotIndex, DWORD headerBuffer, double a3)
{
  int v5; // ecx
  int fileHandle; // esi
  int v7; // ecx
  int v8; // edx
  CHAR filePathBuffer[120]; // [esp+0h] [ebp-78h] BYREF

  SaveSlot_FormatDataFilePath(slotIndex, filePathBuffer);
  PLAYER_CAMERA_LEFT(VIEWED_PLAYER_INDEX) = MAP_VIEW_LEFT;
  PLAYER_CAMERA_TOP(VIEWED_PLAYER_INDEX) = MAP_VIEW_TOP;
  fileHandle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aWb_4, v5, headerBuffer);
  fwrite_((const void *)headerBuffer, 16, fileHandle, 1);
  fwrite_((const void *)gameData, 586398, fileHandle, 1);
  fclose_(v7);
  SaveSlot_FormatFactsFilePath(slotIndex, filePathBuffer);
  return Rules_SaveFactsToFile(filePathBuffer, 2, 0, a3);
}
// 44443B: variable 'v5' is possibly undefined
// 44446A: variable 'v7' is possibly undefined
// 444473: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00444490) --------------------------------------------------------
signed int  SaveSlot_LoadGame(int slotIndex, DWORD a2, double a3)
{
  int file_handle; // eax
  int trace_load_save; // eax
  int stack_index; // ecx
  int slot_index; // edx
  int building_index; // edx
  int unit_record_index; // ecx
  int unit_record; // edx
  CHAR filePathBuffer[120]; // [esp+0h] [ebp-78h] BYREF

  trace_load_save = 0;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-enter\n");
  SaveSlot_FormatDataFilePath(slotIndex, filePathBuffer);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-path %s\n", filePathBuffer);
  file_handle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aRb_5, 0, a2);
  if ( file_handle )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-file-opened handle=%d\n", file_handle);
    IO_SeekStreamGuarded(file_handle, 16, 1u, slotIndex);
    fread_((void *)(uintptr_t)(unsigned int)gameData, 0x8F29E, file_handle, 1);
    fclose_(file_handle);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-read\n");
    g_CurrentPlayerIndex = TURN_OWNER_PLAYER_INDEX;
    Rules_ResetEngineOnLoad();
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-fact-reset\n");
    for ( stack_index = 0; stack_index < 500; ++stack_index )
    {
      if ( (unsigned int)*(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147180) <= 0x28 )
      {
        if ( trace_load_save )
          fprintf(
            stderr,
            "[menu-probe] load-save-link-army stack=%d type=%d x=%d y=%d owner=%u\n",
            stack_index,
            *(unsigned __int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147180),
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + UNIT_STACK_TABLE_OFFSET),
            *(__int16 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147176),
            *(unsigned __int8 *)(gameData + UNIT_STACK_STRIDE * stack_index + 147178));
        UnitStack_LinkArmyFact((__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stack_index), 1, a2);
      }
      for ( slot_index = 0; slot_index < 10; ++slot_index )
      {
        *(_DWORD *)(gameData + UNIT_STACK_STRIDE * stack_index + 31 * slot_index + 147198) = 0;
      }
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-army-loop\n");
    for ( building_index = 0; building_index < *(_DWORD *)(gameData + MAP_WIDTH_TILES_OFFSET); ++building_index )
    {
      for ( slot_index = 0; slot_index < *(_DWORD *)(gameData + MAP_HEIGHT_TILES_OFFSET); ++slot_index )
      {
        *(_DWORD *)(TILE_TERRAIN_RECORD_STRIDE * slot_index + TILE_TERRAIN_ROW_STRIDE * building_index + gameData + 6) = 0;
        *(_DWORD *)(TILE_TERRAIN_RECORD_STRIDE * slot_index + TILE_TERRAIN_ROW_STRIDE * building_index + gameData + 10) = 0;
      }
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-building-loop\n");
    for ( unit_record_index = 0; unit_record_index < 100; ++unit_record_index )
    {
      unit_record = UNIT_RECORD(unit_record_index);
      if ( (unsigned int)*(char *)(unit_record + 4) < 4 && *(__int16 *)(unit_record + 16) != -1 )
        Rules_AssertCastleFact((unsigned __int8 *)unit_record, unit_record_index);
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-castle-loop\n");
    SaveSlot_FormatFactsFilePath(slotIndex, filePathBuffer);
    Rules_LoadFactsFromFile(filePathBuffer, 0, a2, a3);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-sidecar-write\n");
    Render_CreateSprite();
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-render-create\n");
    UI_ClearTileHighlight(0);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-ui-clear\n");
    MiniMap_CreateSurface(a2);
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-minimap\n");
    return 1;
  }
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-open-failed\n");
  return file_handle;
}
// 4445A5: conditional instruction was optimized away because ecx.4<1F4u
// 44466F: conditional instruction was optimized away because ecx.4<64u
// 444529: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 444639: simplified comparisons for 'eax.4': <0 || >=4 became >=4u
// 4444A8: variable 'v5' is possibly undefined
// 4444E4: variable 'v8' is possibly undefined
// 44451D: variable 'v9' is possibly undefined
// 444662: variable 'v15' is possibly undefined
// 44467E: variable 'v17' is possibly undefined
// 444688: variable 'v18' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004446E0) --------------------------------------------------------
char  SaveSlot_LoadLabelOrPlaceholder(int slotIndex, char *outLabelBuffer, DWORD a3)
{
  int file_handle; // eax
  char result; // al
  char *placeholderChars; // esi
  CHAR filePathBuffer[108]; // [esp+0h] [ebp-6Ch] BYREF

  snprintf(filePathBuffer, sizeof(filePathBuffer), "save\\%d.dat", slotIndex);
  file_handle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aRb_7, 0, a3);
  if ( file_handle )
  {
    fread_(outLabelBuffer, 1, file_handle, 16);
    outLabelBuffer[16] = 0;
    return fclose_(file_handle);
  }
  else
  {
    placeholderChars = asc_4F94BB;
    do
    {
      result = *placeholderChars;
      *outLabelBuffer = *placeholderChars;
      if ( !result )
        break;
      result = placeholderChars[1];
      placeholderChars += 2;
      outLabelBuffer[1] = result;
      outLabelBuffer += 2;
    }
    while ( result );
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00444750) --------------------------------------------------------
int  SaveSlot_HasDataFile(int slotIndex, DWORD a2)
{
  int file_handle; // eax
  int result; // eax
  CHAR filePathBuffer[104]; // [esp-68h] [ebp-68h] BYREF

  snprintf(filePathBuffer, sizeof(filePathBuffer), "save\\%d.dat", slotIndex);
  file_handle = IO_FOpen(filePathBuffer, (unsigned __int8 *)aRb_8, 0, a2);
  result = file_handle;
  if ( file_handle )
  {
    fclose_(file_handle);
    return 1;
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00444780) --------------------------------------------------------
int  SaveSlotDialog_RepaintRow(int a1)
{
  void *v2; // ebp
  char *editNameChars; // esi
  char *labelCursor; // edi
  char v5; // al
  char v6; // al
  int rowBottomY; // edi
  unsigned __int16 rowTopY; // si
  int v9; // eax
  int result; // eax
  char labelBuffer[20]; // [esp+0h] [ebp-30h] BYREF
  int rowIndex; // [esp+14h] [ebp-1Ch]

  rowIndex = a1;
  v2 = g_RenderDevice;
  if ( g_SaveSlotDialogIsSaveMode && a1 == g_SaveSlotDialogSelectedRow )
  {
    editNameChars = g_SaveSlotNameEditBuffer;
    labelCursor = labelBuffer;
    do
    {
      v5 = *editNameChars;
      *labelCursor = *editNameChars;
      if ( !v5 )
        break;
      v6 = editNameChars[1];
      editNameChars += 2;
      labelCursor[1] = v6;
      labelCursor += 2;
    }
    while ( v6 );
  }
  else
  {
    SaveSlot_LoadLabelOrPlaceholder(rowIndex, labelBuffer, (DWORD)g_RenderDevice);
  }
  g_RenderDevice = &g_MainRenderDevice;
  rowBottomY = (unsigned __int16)(22 * rowIndex + 157);
  rowTopY = 22 * rowIndex + 137;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xF4u, 0x1A4u, rowTopY, rowBottomY);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, rowTopY, 244, 0x1A4u, rowBottomY, 0xF4u, rowTopY);
  if ( rowIndex == g_SaveSlotDialogSelectedRow )
    v9 = 18;
  else
    v9 = 21;
  Render_ReleaseSurface(v9, (DWORD)v2);
  if ( g_SaveSlotDialogIsSaveMode )
    UI_SetTextCursorPosition(g_TextInputCaretPos);
  UI_DrawTextFmt(rowBottomY, 244, 410, 22 * rowIndex + 137, 3, (int)labelBuffer);
  UI_SetTextCursorPosition(-1);
  result = Render_Present((int)g_RenderState);
  g_RenderDevice = v2;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 543D18: using guessed type int dword_543D18;
// 543D1C: using guessed type int dword_543D1C;
// 543D24: using guessed type int dword_543D24;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00444920) --------------------------------------------------------
int  SaveSlotDialog_HandleCancel(int result, int a2)
{
  if ( result )
    result = UIWidget_PlayPressedReleaseAnimationWithDelay(result, a2);
  g_SaveSlotDialogResult = -1;
  g_SaveSlotDialogDone = 1;
  return result;
}
// 543D14: using guessed type int dword_543D14;
// 543D20: using guessed type int dword_543D20;

//----- (00444950) --------------------------------------------------------
signed int  SaveSlotDialog_HandleConfirm(int a1, int a2, DWORD a3, double a4)
{
  signed int result; // eax
  void *v6; // ecx

  if ( a1 )
    UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  if ( g_SaveSlotDialogIsSaveMode && g_SaveSlotDialogSelectedRow != -1 )
  {
    result = saveGame(g_SaveSlotDialogSelectedRow, (DWORD)g_SaveSlotNameEditBuffer, a4);
    g_SaveSlotDialogDone = 1;
    goto LABEL_6;
  }
  result = SaveSlot_HasDataFile(g_SaveSlotDialogSelectedRow, a3);
  if ( !result )
  {
LABEL_6:
    g_RenderDevice = v6;
    return result;
  }
  result = g_SaveSlotDialogSelectedRow;
  g_SaveSlotDialogResult = g_SaveSlotDialogSelectedRow;
  g_SaveSlotDialogDone = 1;
  g_RenderDevice = v6;
  return result;
}
// 444981: variable 'v6' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 543D14: using guessed type int dword_543D14;
// 543D18: using guessed type int dword_543D18;
// 543D1C: using guessed type int dword_543D1C;
// 543D20: using guessed type int dword_543D20;

//----- (00444D50) --------------------------------------------------------
int  SaveSlotDialog_Run(int a1, char a2, DWORD a3, double a4)
{
  _DWORD *v5; // eax
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int SpriteForChar; // eax
  int v10; // ecx
  int v11; // eax
  int i; // edx
  int v13; // eax
  int v14; // ebx
  int v15; // edx
  int v16; // eax
  int v17; // ebp
  unsigned int hoveredRow; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  const char *caretCharPtr; // edi
  unsigned int v27; // kr0C_4
  int v28; // edx
  int v29; // ecx
  int v30; // ecx
  unsigned int poppedKey; // eax
  char *v32; // esi
  char *v33; // edi
  char v34; // al
  char v35; // al
  int v36; // edx
  int v37; // edx
  _DWORD v38[40]; // [esp+2Ch] [ebp-E0h] BYREF
  char v39[20]; // [esp+CCh] [ebp-40h] BYREF
  _DWORD *dialogSpriteSet; // [esp+E0h] [ebp-2Ch] BYREF
  int savedResourceHandle; // [esp+E4h] [ebp-28h]
  int (*previousRenderHook)(); // [esp+E8h] [ebp-24h]
  int previousResourceHandleA; // [esp+ECh] [ebp-20h]
  char typedChar; // [esp+F0h] [ebp-1Ch]

  v5 = (_DWORD *)Mem_Alloc(4112, a1, a2, a3);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a2);
  dialogSpriteSet = v5;
  previousResourceHandleA = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v6, 0, a3, (int)aSetrhS08x_22);
  g_SaveSlotDialogIsSaveMode = v7;
  g_TextInputCaretPos = 0;
  g_SaveSlotDialogSelectedRow = -1;
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, v8);
  g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  SpriteForChar = DLX_GetSpriteForChar((int)dialogSpriteSet, g_SaveSlotDialogIsSaveMode != 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    51,
    SpriteForChar,
    v10,
    v10,
    v10,
    v10,
    1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  v11 = DLX_GetSpriteForChar((int)dialogSpriteSet, g_SaveSlotDialogIsSaveMode != 0);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    51,
    v11,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  for ( i = 0; i < 10; SaveSlotDialog_RepaintRow(i) )
    ;
  qmemcpy(v38, &g_SaveSlotDialogWidgetTemplateBlob, 0x9Fu);
  v38[3] = &dialogSpriteSet;
  *(_DWORD *)((char *)&v38[16] + 1) = &dialogSpriteSet;
  if ( g_SaveSlotDialogIsSaveMode )
    v13 = -1;
  else
    v13 = 4;
  LOBYTE(v14) = g_SaveSlotDialogIsSaveMode;
  *(_DWORD *)((char *)&v38[17] + 1) = v13;
  *(_DWORD *)((char *)&v38[18] + 1) = (g_SaveSlotDialogIsSaveMode != 0) + 2;
  g_RenderDevice = &g_MainRenderDevice;
  UIWidgetTable_InitDrawStates(v38);
  g_SaveSlotDialogDone = 0;
  Render_Present((int)g_RenderState);
  v16 = Render_SetResourceHandle((int)&g_MainRenderDevice, v15);
  v17 = g_SaveSlotDialogDone;
  savedResourceHandle = v16;
  while ( !g_SaveSlotDialogDone )
  {
    if ( g_SaveSlotDialogIsSaveMode && g_SaveSlotDialogSelectedRow != -1 )
    {
      if ( Input_IsKeyPressed(203) )
      {
        LOBYTE(v14) = g_TextInputCaretPos;
        if ( g_TextInputCaretPos )
        {
          --g_TextInputCaretPos;
          SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
          Input_ClearKey(203, v23);
        }
      }
      if ( Input_IsKeyPressed(205) && strlen(g_SaveSlotNameEditBuffer) > g_TextInputCaretPos )
      {
        v17 = ++g_TextInputCaretPos;
        SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
        Input_ClearKey(205, v24);
      }
      if ( Input_IsKeyPressed(211) )
      {
        LOBYTE(v14) = strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1]) + 1;
        memmove_(
          &g_SaveSlotNameEditBuffer[g_TextInputCaretPos],
          &g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1],
          strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1]) + 1);
        SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
        Input_ClearKey(211, v25);
      }
      if ( Input_IsKeyPressed(14) )
      {
        LOBYTE(v14) = g_TextInputCaretPos;
        if ( g_TextInputCaretPos )
        {
          caretCharPtr = &g_SaveSlotNameEditBuffer[g_TextInputCaretPos--];
          v27 = strlen(caretCharPtr) + 1;
          LOBYTE(v14) = v27;
          memmove_(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos], &g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1], v27);
          SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
          Input_ClearKey(14, v28);
        }
      }
      if ( Input_IsKeyPressed(28) )
        SaveSlotDialog_HandleConfirm(0, v29, v17, a4);
      if ( Input_IsKeyPressed(1) )
        SaveSlotDialog_HandleCancel(0, v30);
      poppedKey = Input_PopKey();
      v17 = poppedKey;
      if ( poppedKey != -1 )
      {
        typedChar = Input_KeyToChar(poppedKey);
        if ( typedChar )
        {
          if ( strlen(g_SaveSlotNameEditBuffer) < 0x10 )
          {
            if ( g_SaveSlotDialogIsSaveMode )
            {
              v32 = g_SaveSlotNameEditBuffer;
              v33 = v39;
              do
              {
                v34 = *v32;
                *v33 = *v32;
                if ( !v34 )
                  break;
                v35 = v32[1];
                v32 += 2;
                v33[1] = v35;
                v33 += 2;
              }
              while ( v35 );
            }
            else
            {
              SaveSlot_LoadLabelOrPlaceholder(g_SaveSlotDialogSelectedRow, v39, v17);
            }
            Render_ReleaseSurface(21, v17);
            if ( (unsigned __int16)Render_LoadResourceSprite_v3(v39) < 0x97u )
            {
              LOBYTE(v14) = strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos]) + 1;
              memmove_(
                &g_SaveSlotNameEditBuffer[g_TextInputCaretPos + 1],
                &g_SaveSlotNameEditBuffer[g_TextInputCaretPos],
                strlen(&g_SaveSlotNameEditBuffer[g_TextInputCaretPos]) + 1);
              v36 = g_TextInputCaretPos;
              g_SaveSlotNameEditBuffer[g_TextInputCaretPos] = typedChar;
              g_TextInputCaretPos = v36 + 1;
              SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
              Input_ClearKey(v17, v37);
            }
          }
        }
      }
    }
    DD_Pump((int)g_RenderState, v14);
    if ( DD_IsFlipping((int)g_RenderState) )
    {
      if ( g_MouseCursorRawX >> g_CursorCoordShift >= 244 && g_MouseCursorRawX >> g_CursorCoordShift <= 410 )
      {
        hoveredRow = ((g_MouseCursorRawY >> g_CursorCoordShift) - 142) / 22;
        if ( hoveredRow <= 9 )
        {
          v14 = g_SaveSlotDialogSelectedRow;
          if ( hoveredRow != g_SaveSlotDialogSelectedRow )
          {
            g_SaveSlotDialogSelectedRow = ((g_MouseCursorRawY >> g_CursorCoordShift) - 142) / 22;
            g_TextInputCaretPos = 0;
            if ( v14 != -1 )
              SaveSlotDialog_RepaintRow(v14);
            if ( g_SaveSlotDialogIsSaveMode )
            {
              SaveSlot_LoadLabelOrPlaceholder(g_SaveSlotDialogSelectedRow, g_SaveSlotNameEditBuffer, v17);
              if ( !strcmp_(v19, asc_4F94C2) )
                g_SaveSlotNameEditBuffer[0] = 0;
            }
            SaveSlotDialog_RepaintRow(g_SaveSlotDialogSelectedRow);
          }
          if ( RenderState_IsCursorFlipStillActive((int)g_RenderState) )
            SaveSlotDialog_HandleConfirm(0, v20, v17, a4);
        }
      }
    }
    UIWidgetTable_PollHoverAndActions(v38, v17);
  }
  Render_SetResourceHandle((int)&g_MainRenderDevice, savedResourceHandle);
  Render_Begin((int)g_RenderState, 0);
  Debug_Log(v21, v14, (DWORD)g_RenderHook, (int)aUnsetrh08x_22);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandleA);
  DLXSpriteSet_ReleaseAndClear((int *)&dialogSpriteSet);
  return g_SaveSlotDialogResult;
}
// 444FB0: simplified comparisons for 'eax.4': <0 || >=A became >=Au
// 444DC0: variable 'v6' is possibly undefined
// 444DCD: variable 'v7' is possibly undefined
// 444DF3: variable 'v8' is possibly undefined
// 444E47: variable 'v10' is possibly undefined
// 444EA3: variable 'i' is possibly undefined
// 444F23: variable 'v15' is possibly undefined
// 445006: variable 'v19' is possibly undefined
// 445031: variable 'v20' is possibly undefined
// 445031: variable 'a4' is possibly undefined
// 445073: variable 'v21' is possibly undefined
// 44510E: variable 'v23' is possibly undefined
// 445152: variable 'v24' is possibly undefined
// 4451AD: variable 'v25' is possibly undefined
// 445215: variable 'v28' is possibly undefined
// 44522A: variable 'v29' is possibly undefined
// 44523F: variable 'v30' is possibly undefined
// 445342: variable 'v37' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 543D14: using guessed type int dword_543D14;
// 543D18: using guessed type int dword_543D18;
// 543D1C: using guessed type int dword_543D1C;
// 543D20: using guessed type int dword_543D20;
// 543D24: using guessed type int dword_543D24;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00445360) --------------------------------------------------------
int  UI_ShowInfoWindow(
        const char *a1,
        unsigned int windowStyle,
        int a3,
        DWORD a4,
        int a5,
        int a6)
{
  DWORD deviceVtable; // ebp
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  _DWORD *v12; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // eax
  _DWORD *v16; // eax
  int v17; // eax
  int v18; // eax
  _DWORD *v19; // eax
  int v20; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  _DWORD *v23; // eax
  int v24; // ecx
  _DWORD *v25; // eax
  int v26; // eax
  _DWORD *v27; // ebx
  int result; // eax
  _DWORD *scrollSpriteSet; // [esp+68h] [ebp-34h] BYREF
  int (*previousRenderHook)(); // [esp+6Ch] [ebp-30h]
  const char *messageText; // [esp+70h] [ebp-2Ch]
  _DWORD *backdropSurface; // [esp+74h] [ebp-28h]
  DWORD v33; // [esp+78h] [ebp-24h]
  int SpriteHeight; // [esp+7Ch] [ebp-20h]
  int previousResourceHandle; // [esp+80h] [ebp-1Ch]
  int SpriteWidth; // [esp+84h] [ebp-18h]
  int info_header_height;
  int info_footer_width;
  int info_header_width;

  messageText = a1;
  Debug_Log(a3, windowStyle, a4, (int)aWindowmessageS);
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, windowStyle, a4, (int)aSetrhS08x_10);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  deviceVtable = 0;
  Render_ReleaseSurface(17, 0);
  scrollSpriteSet = 0;
  if ( windowStyle )
  {
    if ( windowStyle <= 1 )
    {
      v19 = (_DWORD *)Mem_Alloc(4112, v8, windowStyle, 0);
      if ( v19 )
        v19 = DLXSpriteSet_Load(v19, "pergamin.s32");
      scrollSpriteSet = v19;
      a6 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v19, 3u)) / 2;
      a5 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 3u)) / 2;
      SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 3u);
      SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)scrollSpriteSet, 3u);
      Surface = (_DWORD *)Mem_Alloc(188, v20, windowStyle, 0);
      if ( Surface )
        Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
      backdropSurface = Surface;
      Render_FillRect(
        0,
        Surface,
        (unsigned __int16)a6,
        (unsigned __int16)a5,
        a5 + SpriteHeight - 1,
        a6 + SpriteWidth - 1,
        0,
        0);
      g_RenderDevice = &g_MainRenderDevice;
      SpriteForChar = DLX_GetSpriteForChar((int)scrollSpriteSet, 3);
      v33 = *((_DWORD *)g_RenderDevice + 46);
      deviceVtable = v33;
      Compat_RenderDeviceDrawMenuSprite(a6, a5, SpriteForChar, 1);
      UI_DrawTextFmt(a5, a5, a5 + SpriteHeight, a6 + 18, 3, messageText);
    }
    else if ( windowStyle == 2 )
    {
      v23 = (_DWORD *)Mem_Alloc(4112, v8, 2, 0);
      if ( v23 )
        v23 = DLXSpriteSet_Load(v23, "pergamin.s32");
      scrollSpriteSet = v23;
      a6 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v23, 2u)) / 2;
      a5 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 2u)) / 2;
      SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 2u);
      SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)scrollSpriteSet, 2u);
      v25 = (_DWORD *)Mem_Alloc(188, v24, 2, 0);
      if ( v25 )
        v25 = Render_CreateSurface((int)v25, SpriteHeight, SpriteWidth);
      backdropSurface = v25;
      Render_FillRect(
        0,
        v25,
        (unsigned __int16)a6,
        (unsigned __int16)a5,
        a5 + SpriteHeight - 1,
        a6 + SpriteWidth - 1,
        0,
        0);
      g_RenderDevice = &g_MainRenderDevice;
      v26 = DLX_GetSpriteForChar((int)scrollSpriteSet, 2);
      deviceVtable = *((_DWORD *)g_RenderDevice + 46);
      Compat_RenderDeviceDrawMenuSprite(a6, a5, v26, 1);
      UI_DrawTextFmt(a5, a5 + 25, a5 + SpriteHeight - 25, a6 + 25, 6, messageText);
    }
  }
  else
  {
    v12 = (_DWORD *)Mem_Alloc(4112, v8, 0, 0);
    if ( v12 )
      v12 = DLXSpriteSet_Load(v12, "temple.s32");
    a6 = 150;
    scrollSpriteSet = v12;
    info_footer_width = (unsigned __int16)DLX_GetSpriteWidth((int)v12, 0x17u);
    a5 = 0;
    info_header_width = (unsigned __int16)DLX_GetSpriteWidth((int)scrollSpriteSet, 0x16u);
    v15 = info_footer_width + 6;
    SpriteHeight = 640;
    if ( info_header_width > info_footer_width + 6 )
      v15 = info_header_width;
    SpriteWidth = v15;
    v16 = (_DWORD *)Mem_Alloc(188, 0, 0, 0x280u);
    if ( v16 )
      v16 = Render_CreateSurface((int)v16, SCREEN_WIDTH, SpriteWidth);
    backdropSurface = v16;
    Render_FillRect(0, v16, 150, 0, SCREEN_MAX_X, SpriteWidth + 149, 0, 0);
    g_RenderDevice = &g_MainRenderDevice;
    v17 = DLX_GetSpriteForChar((int)scrollSpriteSet, 22);
    Compat_RenderDeviceDrawMenuSprite(150, 0, v17, 1);
    info_header_height = (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 0x16u);
    v18 = DLX_GetSpriteForChar((int)scrollSpriteSet, 23);
    deviceVtable = *((_DWORD *)g_RenderDevice + 46);
    Compat_RenderDeviceDrawMenuSprite(156, info_header_height, v18, 1);
    UI_DrawTextFmt(0, 70, 569, 210, 6, messageText);
  }
  DLXSpriteSet_ReleaseAndClear((int *)&scrollSpriteSet);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping((int)g_RenderState) && !DD_IsLost((int)g_RenderState) )
    DD_Pump((int)g_RenderState, 0);
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  Debug_Log((int)g_RenderHook, 0, deviceVtable, (int)aUnsetrh08x_10);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  if ( (uintptr_t)backdropSurface >> 32 )
    backdropSurface = 0;
  if ( backdropSurface )
    Render_FillRect(backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, a5, a6);
  v27 = backdropSurface;
  result = Render_Present((int)g_RenderState);
  if ( v27 )
    return RenderSurface_InvokeSlot0(v27, 2);
  return result;
}
// 445457: variable 'v8' is possibly undefined
// 44541F: variable 'v9' is possibly undefined
// 44542E: variable 'v10' is possibly undefined
// 44543F: variable 'v11' is possibly undefined
// 44549A: variable 'v14' is possibly undefined
// 44561E: variable 'v20' is possibly undefined
// 445767: variable 'v24' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (004458E0) --------------------------------------------------------
int  WorldMap_NotifyPlagueOutbreak(int a1, const char *a2, DWORD a3)
{
  int buildingRecordOffset; // ecx
  int result; // eax
  int v6; // ecx
  int v7; // ecx
  _BYTE messageBuffer[256]; // [esp+0h] [ebp-120h] BYREF
  int noticeTextTable[8]; // [esp+100h] [ebp-20h] BYREF

  result = 0;
  noticeTextTable[6] = a1;
  buildingRecordOffset = 0;
  noticeTextTable[0] = (int)g_PlagueOutbreakNoticeFmtText[0];
  noticeTextTable[1] = (int)g_PlagueOutbreakNoticeFmtText[1];
  noticeTextTable[2] = (int)g_PlagueOutbreakNoticeFmtText[2];
  do
  {
    result = buildingRecordOffset + gameData;
    if ( (*(_BYTE *)(buildingRecordOffset + gameData + 510109) & 7) == 5 )
    {
      result = *(unsigned __int8 *)(result + 509676);
      if ( result == g_CurrentPlayerIndex )
      {
        Diagnostics_TraceWorldMapActionEvent("plague_notice_match", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, 0);
        Win_PlayModeChangeFrameTransition(aZaraza, 1, buildingRecordOffset, (char)a2, a3);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_after_transition", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, 0);
        a2 = (const char *)noticeTextTable[(unsigned __int8)g_LanguageIndex];
        sprintf_(messageBuffer, a2, gameData + buildingRecordOffset + BUILDING_TABLE_OFFSET + 5);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_before_info_window", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, 0);
        result = UI_ShowInfoWindow((const char *)messageBuffer, 0, 0, a3, (int)&noticeTextTable[3], (int)&g_PlagueOutbreakNoticeFmtText[3]);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_after_info_window", buildingRecordOffset / BUILDING_RECORD_SIZE, buildingRecordOffset, g_CurrentPlayerIndex, result);
      }
    }
    buildingRecordOffset += BUILDING_RECORD_SIZE;
  }
  while ( buildingRecordOffset != 46700 );
  return result;
}
// 445949: variable 'v6' is possibly undefined
// 44596F: variable 'v7' is possibly undefined
// 445974: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 517EA0: using guessed type char *off_517EA0[12];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (004459A0) --------------------------------------------------------
int  UI_ShowTechnologyLevelUpIfChanged(int a1, DWORD a2)
{
  int result; // eax
  int noticeTextTable[6]; // [esp+0h] [ebp-18h] BYREF

  noticeTextTable[0] = (int)g_TechLevelUpNoticeText[0];
  noticeTextTable[1] = (int)g_TechLevelUpNoticeText[1];
  noticeTextTable[2] = (int)g_TechLevelUpNoticeText[2];
  if ( *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) != *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_LAST_SHOWN_TECH_LEVEL_OFFSET) )
  {
    Diagnostics_TraceWorldMapActionEvent("color_notice_before_info_window", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
    UI_ShowInfoWindow(noticeTextTable[(unsigned __int8)g_LanguageIndex], 0, a1, a2, (int)&noticeTextTable[3], (int)&g_TechLevelUpNoticeText[3]);
    Diagnostics_TraceWorldMapActionEvent("color_notice_after_info_window", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
  }
  result = PLAYER_DATA(g_CurrentPlayerIndex);
  *(_BYTE *)(result + PLAYER_LAST_SHOWN_TECH_LEVEL_OFFSET) = *(_BYTE *)(result + PLAYER_TECH_LEVEL_OFFSET);
  return result;
}
// 511130: using guessed type char g_LanguageIndex;
// 517EAC: using guessed type char *off_517EAC[9];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (00445A40) --------------------------------------------------------
int  UI_CheatEditRepaint(DWORD a1, int a2)
{
  unsigned __int16 v2; // dx
  unsigned __int16 v3; // cx
  char savedFirstChar; // [esp+0h] [ebp-10h]

  savedFirstChar = g_CheatEntryTextBuffer[0];
  strupr_(440, 200);
  g_CheatEntryTextBuffer[0] = savedFirstChar;
  RenderState_PumpIfRectInViewBounds(g_RenderState, v2, v3, 0x104u, 0x122u);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, 260, 200, 0x1B8u, 0x122u, 0xC8u, 0x104u);
  Render_ReleaseSurface(22, a1);
  UI_SetTextCursorPosition(g_CheatEditCaretIndex);
  UI_DrawTextFmt(a2, 200, 440, 260, 3, (int)g_CheatEntryTextBuffer);
  UI_SetTextCursorPosition(-1);
  return Render_Present((int)g_RenderState);
}
// 445A7C: variable 'v2' is possibly undefined
// 445A7C: variable 'v3' is possibly undefined
// 47BBE3: using guessed type int __fastcall strupr_(_DWORD, _DWORD);
// 5202E0: using guessed type int dword_5202E0;
// 543D44: using guessed type int dword_543D44;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00445CE0) --------------------------------------------------------
char  Building_ShowConstructionFinishedDialog(int a1, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  char *editDstCursor; // edi
  char *buildingNameChars; // esi
  char v8; // al
  char v9; // al
  char *v10; // edi
  _DWORD *v11; // eax
  int v12; // ecx
  int SpriteWidth; // edx
  int v14; // ecx
  int v15; // eax
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int v19; // eax
  int v20; // eax
  char v21; // bl
  int v22; // edx
  unsigned int v23; // kr04_4
  int v24; // edx
  unsigned int v25; // kr08_4
  int v26; // edx
  const char *v27; // edi
  unsigned int v28; // kr0C_4
  int v29; // edx
  unsigned int v30; // eax
  int poppedKey; // esi
  unsigned int v32; // kr10_4
  unsigned int v33; // kr14_4
  int v34; // eax
  int v35; // edx
  int v36; // ecx
  char *v37; // esi
  char *v38; // edi
  char result; // al
  int buildingCompleteAltText[3]; // [esp+38h] [ebp-4Ch]
  int buildingCompleteText[3]; // [esp+44h] [ebp-40h]
  _DWORD *v42; // [esp+50h] [ebp-34h] BYREF
  int panelWidth; // [esp+54h] [ebp-30h]
  int (*v44)(); // [esp+58h] [ebp-2Ch]
  int v45; // [esp+5Ch] [ebp-28h]
  int buildingRecord; // [esp+60h] [ebp-24h]
  int panelLeft; // [esp+64h] [ebp-20h]
  char typedChar; // [esp+68h] [ebp-1Ch]

  buildingRecord = a1;
  Debug_Log(a2, a3, a4, (int)aMessage_buildf);
  v45 = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  v44 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v4, a3, a4, (int)aSetrhS08x_11);
  buildingCompleteText[0] = (int)g_BuildingCompleteNoticeText[0];
  buildingCompleteText[1] = (int)g_BuildingCompleteNoticeText[1];
  buildingCompleteText[2] = (int)g_BuildingCompleteNoticeText[2];
  buildingCompleteAltText[0] = (int)g_BuildingCompleteNoticeTextAlt[0];
  buildingCompleteAltText[1] = (int)g_BuildingCompleteNoticeTextAlt[1];
  buildingCompleteAltText[2] = (int)g_BuildingCompleteNoticeTextAlt[2];
  editDstCursor = g_CheatEntryTextBuffer;
  buildingNameChars = (char *)(buildingRecord + 5);
  do
  {
    v8 = *buildingNameChars;
    *editDstCursor = *buildingNameChars;
    if ( !v8 )
      break;
    v9 = buildingNameChars[1];
    buildingNameChars += 2;
    editDstCursor[1] = v9;
    editDstCursor += 2;
  }
  while ( v9 );
  v10 = g_CheatEntryTextBuffer;
  v11 = (_DWORD *)Mem_Alloc(4112, v5, a3, a4);
  if ( v11 )
    v11 = DLXSpriteSet_Load(v11, a3);
  v42 = v11;
  Render_Pump();
  panelLeft = v12;
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  DLX_GetSpriteWidth((int)v42, 0x17u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v42, 0x16u);
  v15 = v14 + 6;
  if ( (unsigned __int16)SpriteWidth > v14 + 6 )
    v15 = SpriteWidth;
  panelWidth = v15;
  Surface = (_DWORD *)Mem_Alloc(188, v14, a3, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, panelWidth);
  backdropSurface = (DWORD)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)panelLeft, 0, SCREEN_MAX_X, panelWidth + panelLeft - 1, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)v42, 22);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    panelLeft,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  DLX_GetSpriteHeight((int)v42, 0x16u);
  v19 = DLX_GetSpriteForChar((int)v42, 23);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    panelLeft + 6,
    v19,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(17, backdropSurface);
  if ( *(_BYTE *)(buildingRecord + 4) == 2 )
    v20 = buildingCompleteText[(unsigned __int8)g_LanguageIndex];
  else
    v20 = buildingCompleteAltText[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt((int)g_CheatEntryTextBuffer, 70, 569, panelLeft + 60, 6, v20);
  v21 = -56;
  Render_FillRect(0, (_DWORD *)g_PrimaryRenderSurface, 260, 200, 0x1B8u, 0x122u, 0xC8u, 0x104u);
  UI_CheatEditRepaint(backdropSurface, (int)g_CheatEntryTextBuffer);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  g_DecisionDialogExitSignal = 0;
  while ( !DD_IsFlipping((int)g_RenderState) && !g_DecisionDialogExitSignal )
  {
    DD_Pump((int)g_RenderState, v21);
    if ( Input_IsKeyPressed(203) && g_CheatEditCaretIndex )
    {
      --g_CheatEditCaretIndex;
      UI_CheatEditRepaint(backdropSurface, (int)v10);
      Input_ClearKey(203, v22);
    }
    if ( Input_IsKeyPressed(205) )
    {
      v23 = strlen(g_CheatEntryTextBuffer) + 1;
      v10 = &g_CheatEntryTextBuffer[v23];
      v21 = g_CheatEditCaretIndex;
      if ( v23 - 1 > g_CheatEditCaretIndex )
      {
        ++g_CheatEditCaretIndex;
        UI_CheatEditRepaint(backdropSurface, (int)v10);
        Input_ClearKey(205, v24);
      }
    }
    if ( Input_IsKeyPressed(211) )
    {
      v25 = strlen(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1]) + 1;
      v10 = (char *)g_CheatEditCaretIndex;
      v21 = v25;
      memmove_(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex], &g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1], v25);
      UI_CheatEditRepaint(backdropSurface, (int)v10);
      Input_ClearKey(211, v26);
    }
    if ( Input_IsKeyPressed(14) && g_CheatEditCaretIndex )
    {
      v27 = &g_CheatEntryTextBuffer[g_CheatEditCaretIndex--];
      v28 = strlen(v27) + 1;
      v10 = (char *)&v27[v28];
      v21 = v28;
      memmove_(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex], &g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1], v28);
      UI_CheatEditRepaint(backdropSurface, (int)v10);
      Input_ClearKey(14, v29);
    }
    if ( Input_IsKeyPressed(28) )
      g_DecisionDialogExitSignal = 1;
    v30 = Input_PopKey();
    poppedKey = v30;
    if ( v30 != -1 )
    {
      typedChar = Input_KeyToChar(v30);
      if ( typedChar )
      {
        v32 = strlen(g_CheatEntryTextBuffer) + 1;
        v10 = &g_CheatEntryTextBuffer[v32];
        if ( v32 - 1 < 0xA )
        {
          v33 = strlen(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex]) + 1;
          v10 = &g_CheatEntryTextBuffer[g_CheatEditCaretIndex + v33];
          v21 = v33;
          memmove_(&g_CheatEntryTextBuffer[g_CheatEditCaretIndex + 1], &g_CheatEntryTextBuffer[g_CheatEditCaretIndex], v33);
          v34 = g_CheatEditCaretIndex + 1;
          *((_BYTE *)&g_CheatEditCaretIndex + v34 + 3) = typedChar;
          g_CheatEditCaretIndex = v34;
          UI_CheatEditRepaint(backdropSurface, (int)v10);
          Input_ClearKey(poppedKey, v35);
        }
      }
    }
  }
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  Debug_Log(v36, (char)g_RenderHook, backdropSurface, (int)aUnsetrh08x_11);
  g_RenderHook = v44;
  Render_SetResourceHandle((int)&g_MainRenderDevice, v45);
  Render_FillRect((_DWORD *)backdropSurface, 0, 0, 0, SCREEN_MAX_X, panelWidth - 1, 0, panelLeft);
  Render_Present((int)g_RenderState);
  if ( backdropSurface )
    (**(void (__cdecl ***)(int, int, int, int, int, int))(backdropSurface + 184))(buildingCompleteAltText[0], buildingCompleteAltText[1], buildingCompleteAltText[2], buildingCompleteText[0], buildingCompleteText[1], buildingCompleteText[2]);
  v37 = g_CheatEntryTextBuffer;
  v38 = (char *)(buildingRecord + 5);
  DLXSpriteSet_ReleaseAndClear((int *)&v42);
  do
  {
    result = *v37;
    *v38 = *v37;
    if ( !result )
      break;
    result = v37[1];
    v37 += 2;
    v38[1] = result;
    v38 += 2;
  }
  while ( result );
  return result;
}
// 445D46: variable 'v4' is possibly undefined
// 445D86: variable 'v5' is possibly undefined
// 445DB7: variable 'v12' is possibly undefined
// 445DE6: variable 'v14' is possibly undefined
// 445FA7: variable 'v22' is possibly undefined
// 445FE6: variable 'v24' is possibly undefined
// 44603C: variable 'v26' is possibly undefined
// 44609E: variable 'v29' is possibly undefined
// 446148: variable 'v35' is possibly undefined
// 44618F: variable 'v36' is possibly undefined
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 517EB8: using guessed type char *off_517EB8[6];
// 517EC4: using guessed type char *off_517EC4[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 543D44: using guessed type int dword_543D44;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00446230) --------------------------------------------------------
int  Demo_ShowNumberedTextScreen(char a1, DWORD a2)
{
  int previousResourceHandle; // edi
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  _DWORD *v6; // eax
  int v7; // ecx
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // ax
  int v10; // ecx
  _DWORD *v11; // esi
  _DWORD *v12; // ebp
  __int16 v13; // ax
  int SpriteForChar; // eax
  int v15; // ecx
  int v16; // edx
  _DWORD *v17; // ecx
  int v18; // edx
  int v19; // ecx
  unsigned int v20; // eax
  unsigned int v21; // edx
  __int16 v22; // ax
  _BYTE resourcePathBuffer[100]; // [esp+0h] [ebp-8Ch] BYREF
  _DWORD *textSpriteSet; // [esp+64h] [ebp-28h] BYREF
  int v26; // [esp+68h] [ebp-24h]
  void *v27; // [esp+6Ch] [ebp-20h]
  int (*previousRenderHook)(); // [esp+70h] [ebp-1Ch]

  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v3, a1, a2, (int)aSetrhS08x_23);
  sprintf_(resourcePathBuffer, "demo\\tekst%02d.s32", v4 + 1);
  v6 = (_DWORD *)Mem_Alloc(4112, v5, a1, a2);
  if ( v6 )
    v6 = DLXSpriteSet_Load(v6, a1);
  textSpriteSet = v6;
  Surface = (_DWORD *)Mem_Alloc(188, v7, a1, a2);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)textSpriteSet, 0);
    Surface = Render_CreateSurface(v10, SCREEN_WIDTH, SpriteWidth);
  }
  v11 = Surface;
  v12 = Surface;
  v13 = DLX_GetSpriteWidth((int)textSpriteSet, 0);
  Render_FillRect(0, v11, 0, 0, SCREEN_MAX_X, v13 - 1, 0, 0);
  DLXSpriteSet_DrawText((int)textSpriteSet, 0, (int)&g_RenderEnvPaletteContext, (unsigned __int8 *)g_MapPalettePtr);
  v27 = g_RenderDevice;
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)textSpriteSet, 0);
  v26 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, _DWORD, _DWORD, _DWORD))(v26 + 52))(
    0,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    0);
  g_RenderDevice = v27;
  Time_Now(v15, 1);
  Render_BlitSurface(&g_MainRenderDevice, v16, 0, (DWORD)v12);
  v17 = g_RenderState;
  while ( !Input_PollEventsUntil((int)v17, (char)&g_InputBackendState) )
  {
    v20 = Time_Now(v19, v18);
    if ( v20 >= v21 || Input_IsAnyKeyPressed() )
      break;
    InputBackend_PollState(&g_InputBackendState, v21, v19);
  }
  Debug_Log(v19, (char)g_RenderHook, (DWORD)v12, (int)aUnsetrh08x_23);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  v22 = DLX_GetSpriteWidth((int)textSpriteSet, 0);
  Render_FillRect(v12, 0, 0, 0, SCREEN_MAX_X, v22 - 1, 0, 0);
  return DLXSpriteSet_ReleaseAndClear((int *)&textSpriteSet);
}
// 446278: variable 'v3' is possibly undefined
// 446281: variable 'v4' is possibly undefined
// 446299: variable 'v5' is possibly undefined
// 4462B2: variable 'v7' is possibly undefined
// 4462D4: variable 'v10' is possibly undefined
// 446378: variable 'v15' is possibly undefined
// 446384: variable 'v16' is possibly undefined
// 44639B: variable 'v17' is possibly undefined
// 4463A4: variable 'v19' is possibly undefined
// 4463A4: variable 'v18' is possibly undefined
// 4463AB: variable 'v21' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202F4: using guessed type int dword_5202F4;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00446430) --------------------------------------------------------
int  DecisionDialog_ConfirmIfAllowed(uintptr_t a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  if ( !g_DecisionDialogConfirmDisabled )
  {
    g_DecisionDialogExitSignal = 1;
    g_DecisionDialogResult = 1;
  }
  return result;
}
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 543D5C: using guessed type int g_DecisionDialogConfirmDisabled;

//----- (00446460) --------------------------------------------------------
int  DecisionDialog_Cancel(uintptr_t a1, int a2)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimationWithDelay(a1, a2);
  g_DecisionDialogExitSignal = 1;
  g_DecisionDialogResult = 0;
  return result;
}
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;

static _DWORD *g_QueenMarriageProposalWidgetSpriteSet;

static void QueenMarriageProposal_WriteButtonWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        _DWORD **sprite_set_holder,
        const char *sound_name)
{
  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)sprite_set_holder;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

static void QueenMarriageProposal_RebuildButtonWidgets(
        unsigned char *widgets,
        _DWORD **sprite_set_holder,
        int confirm_left,
        int top,
        int cancel_left)
{
  static const char proposal_button_sound[] = "male";

  QueenMarriageProposal_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    confirm_left,
    top,
    10,
    12,
    (int)(uintptr_t)&DecisionDialog_ConfirmIfAllowed,
    sprite_set_holder,
    proposal_button_sound);
  QueenMarriageProposal_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    cancel_left,
    top,
    11,
    13,
    (int)(uintptr_t)&DecisionDialog_Cancel,
    sprite_set_holder,
    proposal_button_sound);
  memset(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2) = -1;
}

//----- (00446480) --------------------------------------------------------
int  Queen_ShowWhimDecisionDialog(int a1, int requiredAmount, int a3, int a4, DWORD a5)
{
  int v6; // ecx
  _DWORD *v7; // eax
  int v8; // ecx
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int result; // eax
  _DWORD v17[40]; // [esp+38h] [ebp-D8h] BYREF
  _DWORD *whimSpriteSet; // [esp+D8h] [ebp-38h] BYREF
  int playerAmount; // [esp+DCh] [ebp-34h]
  int SpriteHeight; // [esp+E0h] [ebp-30h]
  int panelTop; // [esp+E4h] [ebp-2Ch]
  int v22; // [esp+E8h] [ebp-28h]
  int (*previousRenderHook)(); // [esp+ECh] [ebp-24h]
  int previousResourceHandle; // [esp+F0h] [ebp-20h]
  int messageText; // [esp+F4h] [ebp-1Ch]
  int SpriteWidth; // [esp+F8h] [ebp-18h]
  int panelLeft; // [esp+FCh] [ebp-14h]

  messageText = a1;
  playerAmount = a4;
  Debug_Log(a3, a4, a5, (int)aQueenwhimmessa);
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a4, a5, (int)aSetrhS08x_18);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, a5);
  whimSpriteSet = 0;
  v7 = (_DWORD *)Mem_Alloc(4112, v6, 0, a5);
  if ( v7 )
    v7 = DLXSpriteSet_Load(v7, 0);
  whimSpriteSet = v7;
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v7, 0)) / 2;
  panelTop = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)whimSpriteSet, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)whimSpriteSet, 0);
  Surface = (_DWORD *)Mem_Alloc(188, v8, 0, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = (DWORD)Surface;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    SpriteHeight + panelLeft - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)whimSpriteSet, 0);
  v22 = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  SpriteForChar = DLX_GetSpriteForChar((int)whimSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  v22 = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(panelLeft + 41, panelTop + 18, SpriteForChar, 1);
  Render_ReleaseSurface(17, backdropSurface);
  UI_DrawTextFmt(v22, panelLeft + 175, panelLeft + 525, panelTop + 65, 6, messageText);
  Render_ReleaseSurface(18, backdropSurface);
  UI_DrawText(panelLeft + 198, panelTop + 12, (int)aD_6);
  UI_DrawTextFmt(playerAmount, panelLeft + 126, v12, panelTop + 207, 3, (int)aD_7);
  g_DecisionDialogConfirmDisabled = requiredAmount > playerAmount;
  qmemcpy(v17, &g_QueenWhimDecisionButtonWidgetsTemplate, 0x9Fu);
  v17[0] = panelLeft + 126;
  v17[1] = panelTop + 175;
  v17[3] = &whimSpriteSet;
  *(_DWORD *)((char *)&v17[13] + 1) = panelLeft + 451;
  *(_DWORD *)((char *)&v17[14] + 1) = panelTop + 175;
  *(_DWORD *)((char *)&v17[16] + 1) = &whimSpriteSet;
  UIWidgetTable_InitDrawStates(v17);
  Render_Present((int)g_RenderState);
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(v17, backdropSurface);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v15, (char)g_RenderState, backdropSurface, (int)aUnsetrh08x_18);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, panelTop);
  Render_Present((int)g_RenderState);
  if ( backdropSurface )
    RenderSurface_InvokeSlot0((_DWORD *)backdropSurface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&whimSpriteSet);
  result = g_DecisionDialogResult;
  g_DecisionDialogConfirmDisabled = 0;
  return result;
}
// 446527: variable 'v6' is possibly undefined
// 4465A9: variable 'v8' is possibly undefined
// 446776: variable 'v12' is possibly undefined
// 446801: variable 'v13' is possibly undefined
// 44681D: variable 'v14' is possibly undefined
// 446835: variable 'v15' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 543D5C: using guessed type int g_DecisionDialogConfirmDisabled;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

static _DWORD *g_YesNoWindowWidgetSpriteSet;

static void YesNoWindow_WriteButtonWidgetRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback)
{
  static const char yesno_button_sound[] = "male";

  memset(record, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  *(_DWORD *)(record + 8) = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_YesNoWindowWidgetSpriteSet;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIcon;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)yesno_button_sound;
}

static void YesNoWindow_RebuildButtonWidgets(unsigned char *widgets, int confirm_left, int top, int cancel_left)
{
  YesNoWindow_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 0,
    confirm_left,
    top,
    5,
    6,
    (int)(uintptr_t)&DecisionDialog_ConfirmIfAllowed);
  YesNoWindow_WriteButtonWidgetRecord(
    widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 1,
    cancel_left,
    top,
    7,
    8,
    (int)(uintptr_t)&DecisionDialog_Cancel);
  memset(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2, 0, WORLD_MAP_ACTION_WIDGET_RECORD_SIZE);
  *(_DWORD *)(widgets + WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * 2) = -1;
}

//----- (004468F0) --------------------------------------------------------
int  YesNoWindow(int a1, _BYTE *imageData, int a3, char a4, DWORD a5)
{
  int v6; // ecx
  char v7; // bl
  _DWORD *v8; // eax
  int i; // esi
  int v10; // edx
  int v11; // ecx
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  _DWORD *v18; // edi
  char *v19; // esi
  int v20; // edx
  int v21; // ecx
  int v22; // ecx
  _DWORD v24[40]; // [esp+1Ch] [ebp-D0h] BYREF
  _DWORD *scrollSpriteSet; // [esp+BCh] [ebp-30h] BYREF
  int panelTop; // [esp+C0h] [ebp-2Ch]
  int promptText; // [esp+C4h] [ebp-28h]
  int (*previousRenderHook)(); // [esp+C8h] [ebp-24h]
  int previousResourceHandle; // [esp+CCh] [ebp-20h]
  int SpriteWidth; // [esp+D0h] [ebp-1Ch]
  int SpriteHeight; // [esp+D4h] [ebp-18h]
  int panelLeft; // [esp+D8h] [ebp-14h]

  promptText = a1;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] enter text=%p image=%p\n", (void *)(uintptr_t)a1, (void *)imageData);
  Debug_Log(a3, a4, a5, (int)aYesnowindowS);
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a4, a5, (int)aSetrhS08x_12);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, a5);
  if ( imageData )
    Render_LoadResourceSprite_v4(17, imageData, v6, a4, a5);
  v7 = 0;
  scrollSpriteSet = 0;
  v8 = (_DWORD *)Mem_Alloc(4112, v6, 0, a5);
  if ( v8 )
    v8 = DLXSpriteSet_Load(v8, "pergamin.s32");
  scrollSpriteSet = v8;
  g_YesNoWindowWidgetSpriteSet = scrollSpriteSet;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] sprite_load set=%p data=%x\n", (void *)scrollSpriteSet, scrollSpriteSet ? (unsigned int)scrollSpriteSet[1024] : 0);
  if ( imageData )
  {
    for ( i = 4; i <= 8; ++i )
    {
      v7 = g_MapPalettePtr;
      v10 = i;
      DLXSpriteSet_DrawText((int)scrollSpriteSet, v10, (int)imageData, (unsigned __int8 *)g_MapPalettePtr);
    }
  }
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 4u)) / 2;
  panelTop = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 4u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)scrollSpriteSet, 4u);
  Surface = (_DWORD *)Mem_Alloc(188, v11, v7, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = (DWORD)Surface;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    SpriteHeight + panelLeft - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)scrollSpriteSet, 4);
  v15 = *((_DWORD *)g_RenderDevice + 46);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] before_background sprite=%x left=%d top=%d\n", SpriteForChar, panelLeft, panelTop);
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_background\n");
  UI_DrawTextFmt(v15, panelLeft + 30, panelLeft + 260, panelTop + 15, 3, promptText);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_text\n");
  v16 = panelLeft;
  YesNoWindow_RebuildButtonWidgets((unsigned char *)v24, v16 + 72, panelTop + 38, panelLeft + 146);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] before_widget_init holder=%p widget=%p\n", (void *)&g_YesNoWindowWidgetSpriteSet, (void *)v24);
  UIWidgetTable_InitDrawStates(v24);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_widget_init\n");
  Render_Present((int)g_RenderState);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_present\n");
  g_DecisionDialogConfirmDisabled = 0;
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(v24, backdropSurface);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v22, (char)g_RenderState, backdropSurface, (int)aUnsetrh08x_12);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, panelTop);
  Render_Present((int)g_RenderState);
  if ( backdropSurface )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)backdropSurface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&scrollSpriteSet);
  g_YesNoWindowWidgetSpriteSet = 0;
  UI_EndDraw(17);
  return g_DecisionDialogResult;
}
// 44698D: variable 'v6' is possibly undefined
// 446A58: variable 'v11' is possibly undefined
// 446B62: variable 'v17' is possibly undefined
// 446BC6: variable 'v20' is possibly undefined
// 446BE3: variable 'v21' is possibly undefined
// 446BFB: variable 'v22' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202F4: using guessed type int dword_5202F4;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00446CB0) --------------------------------------------------------
int  UI_ShowSimpleTextInfoWindow(int a1, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  _DWORD *v5; // eax
  int panelLeft; // edi
  int v7; // ecx
  _DWORD *Surface; // eax
  _DWORD *backdropSurface; // esi
  int SpriteForChar; // eax
  DWORD v11; // ebp
  int v12; // ecx
  unsigned __int16 v13; // cx
  _DWORD *scrollSpriteSet; // [esp+18h] [ebp-3Ch] BYREF
  int previousResourceHandle; // [esp+1Ch] [ebp-38h]
  int SpriteWidth; // [esp+20h] [ebp-34h]
  int (*previousRenderHook)(); // [esp+24h] [ebp-30h]
  int SpriteHeight; // [esp+28h] [ebp-2Ch]
  int messageText; // [esp+2Ch] [ebp-28h]
  int v21; // [esp+30h] [ebp-24h]
  int v22; // [esp+34h] [ebp-20h]
  int panelTop; // [esp+38h] [ebp-1Ch]

  messageText = a1;
  Debug_Log(a2, a3, a4, (int)aInfowindowS);
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a3, a4, (int)aSetrhS08x_13);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, a4);
  scrollSpriteSet = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, v4, 0, a4);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, 0);
  scrollSpriteSet = v5;
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 9u)) / 2;
  panelTop = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)scrollSpriteSet, 9u)) / 2;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)scrollSpriteSet, 4u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)scrollSpriteSet, 4u);
  Surface = (_DWORD *)Mem_Alloc(188, v7, 0, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = Surface;
  v21 = (unsigned __int16)panelTop;
  v22 = (unsigned __int16)panelLeft;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    panelLeft + SpriteHeight - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)scrollSpriteSet, 9);
  v11 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v11 + 52))(
    panelTop,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UI_DrawTextFmt(panelLeft + 25, panelLeft + 25, panelLeft + 250, panelTop + 34, 3, messageText);
  Render_Begin((int)g_RenderState, 0);
  Debug_Log(v12, panelLeft, v11, (int)aUnsetrh08x_13);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect(backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, v13);
  Render_Present((int)g_RenderState);
  if ( backdropSurface )
    (*(void (**)(void))backdropSurface[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&scrollSpriteSet);
  return UI_EndDraw(17);
}
// 446D40: variable 'v4' is possibly undefined
// 446DCE: variable 'v7' is possibly undefined
// 446EA7: variable 'v12' is possibly undefined
// 446EEE: variable 'v13' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00446F40) --------------------------------------------------------
int  Queen_ShowMarriageProposalDialog(int a1, char a2, DWORD a3)
{
  int v3; // ecx
  int v4; // ecx
  _DWORD *v5; // eax
  int v6; // ecx
  _DWORD *Surface; // eax
  DWORD backdropSurface; // ebp
  int SpriteForChar; // eax
  int v10; // eax
  int v11; // ecx
  _DWORD *v12; // edi
  char *v13; // esi
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _DWORD v18[40]; // [esp+38h] [ebp-DCh] BYREF
  int proposalTextTable[3]; // [esp+D8h] [ebp-3Ch]
  _DWORD *proposalSpriteSet; // [esp+E4h] [ebp-30h] BYREF
  int panelTop; // [esp+E8h] [ebp-2Ch]
  int panelLeft; // [esp+ECh] [ebp-28h]
  int (*previousRenderHook)(); // [esp+F0h] [ebp-24h]
  int SpriteWidth; // [esp+F4h] [ebp-20h]
  int previousResourceHandle; // [esp+F8h] [ebp-1Ch]
  int SpriteHeight; // [esp+FCh] [ebp-18h]

  Debug_Log(a1, a2, a3, (int)aNewqueenwindow);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_log",
    g_SelectedUnitIndex,
    a1,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v3, a2, a3, (int)aSetrhS08x_17);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_set_rh",
    g_SelectedUnitIndex,
    previousResourceHandle,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_render_pump",
    g_SelectedUnitIndex,
    g_ActiveCursorDescriptor,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  Render_ReleaseSurface(17, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_release_surface",
    g_SelectedUnitIndex,
    17,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  proposalSpriteSet = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, v4, a2, a3);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, aQueen_s32_0);
  proposalSpriteSet = v5;
  g_QueenMarriageProposalWidgetSpriteSet = proposalSpriteSet;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_sprite_load",
    g_SelectedUnitIndex,
    (int)(uintptr_t)proposalSpriteSet,
    proposalSpriteSet ? (int)proposalSpriteSet[1025] : -1,
    proposalSpriteSet ? (int)proposalSpriteSet[1024] : 0);
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 0)) / 2;
  panelTop = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)proposalSpriteSet, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)proposalSpriteSet, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_dims",
    g_SelectedUnitIndex,
    SpriteHeight,
    SpriteWidth,
    panelLeft);
  Surface = (_DWORD *)Mem_Alloc(188, v6, 150, a3);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = (DWORD)Surface;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_surface_create",
    g_SelectedUnitIndex,
    (int)(uintptr_t)Surface,
    SpriteHeight,
    SpriteWidth);
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)panelTop,
    (unsigned __int16)panelLeft,
    SpriteHeight + panelLeft - 1,
    SpriteWidth + panelTop - 1,
    0,
    0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)proposalSpriteSet, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_background_lookup",
    g_SelectedUnitIndex,
    SpriteForChar,
    0,
    0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_background_draw",
    g_SelectedUnitIndex,
    *(unsigned __int16 *)(uintptr_t)SpriteForChar,
    *(unsigned __int16 *)(uintptr_t)(SpriteForChar + 2),
    *(int *)(uintptr_t)(SpriteForChar + 14));
  Compat_RenderDeviceDrawMenuSprite(panelLeft, panelTop, SpriteForChar, 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_background_draw",
    g_SelectedUnitIndex,
    panelLeft,
    panelTop,
    0);
  SpriteForChar = DLX_GetSpriteForChar((int)proposalSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_portrait_lookup",
    g_SelectedUnitIndex,
    SpriteForChar,
    PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1,
    0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_portrait_draw",
    g_SelectedUnitIndex,
    *(unsigned __int16 *)(uintptr_t)SpriteForChar,
    *(unsigned __int16 *)(uintptr_t)(SpriteForChar + 2),
    *(int *)(uintptr_t)(SpriteForChar + 14));
  Compat_RenderDeviceDrawMenuSprite(panelLeft + 41, panelTop + 18, SpriteForChar, 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_portrait_draw",
    g_SelectedUnitIndex,
    panelLeft + 41,
    panelTop + 18,
    0);
  proposalTextTable[0] = (int)g_QueenMarriageProposalTexts[0];
  proposalTextTable[1] = (int)g_QueenMarriageProposalTexts[1];
  proposalTextTable[2] = (int)g_QueenMarriageProposalTexts[2];
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_text",
    g_SelectedUnitIndex,
    (int)(uintptr_t)proposalTextTable[(unsigned __int8)g_LanguageIndex],
    (unsigned __int8)g_LanguageIndex,
    0);
  UI_DrawTextFmt((int)v18, panelLeft + 175, panelLeft + 525, panelTop + 55, 6, proposalTextTable[(unsigned __int8)g_LanguageIndex]);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_text",
    g_SelectedUnitIndex,
    panelLeft + 175,
    panelTop + 55,
    0);
  v10 = panelLeft;
  QueenMarriageProposal_RebuildButtonWidgets(
    (unsigned char *)v18,
    &g_QueenMarriageProposalWidgetSpriteSet,
    v10 + 126,
    panelTop + 175,
    panelLeft + 451);
  g_QueenMarriageProposalWidgetTableBase = (uintptr_t)v18;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_widget_rebuild",
    g_SelectedUnitIndex,
    (int)(uintptr_t)v18,
    0x9F,
    0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_widget_init",
    g_SelectedUnitIndex,
    v18[0],
    v18[1],
    *(_DWORD *)((char *)&v18[13] + 1));
  UIWidgetTable_InitDrawStates(v18);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_widget_init",
    g_SelectedUnitIndex,
    (int)(uintptr_t)v18,
    0,
    0);
  Render_Present((int)g_RenderState);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_present",
    g_SelectedUnitIndex,
    (int)(uintptr_t)v18,
    (int)(uintptr_t)backdropSurface,
    0);
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(v18, backdropSurface);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v16, (char)g_RenderState, backdropSurface, (int)aUnsetrh08x_17);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect((_DWORD *)backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, panelTop);
  Render_Present((int)g_RenderState);
  if ( backdropSurface )
    RenderSurface_InvokeSlot0((_DWORD *)backdropSurface, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&proposalSpriteSet);
  g_QueenMarriageProposalWidgetSpriteSet = 0;
  g_QueenMarriageProposalWidgetTableBase = 0;
  UI_EndDraw(17);
  return g_DecisionDialogResult;
}
// 446F9D: variable 'v3' is possibly undefined
// 446FD0: variable 'v4' is possibly undefined
// 447059: variable 'v6' is possibly undefined
// 4471D4: variable 'v11' is possibly undefined
// 447238: variable 'v14' is possibly undefined
// 447255: variable 'v15' is possibly undefined
// 44726D: variable 'v16' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 518010: using guessed type char *g_QueenMarriageProposalTexts[3];
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 543D54: using guessed type int g_DecisionDialogExitSignal;
// 543D58: using guessed type int g_DecisionDialogResult;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00447330) --------------------------------------------------------
int  Queen_ShowMessageDialog(int a1, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  _DWORD *v5; // eax
  int panelLeft; // esi
  int v7; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  _DWORD *queenSpriteSet; // [esp+34h] [ebp-38h] BYREF
  int messageText; // [esp+38h] [ebp-34h]
  int deviceVtable; // [esp+3Ch] [ebp-30h]
  int (*previousRenderHook)(); // [esp+40h] [ebp-2Ch]
  _DWORD *backdropSurface; // [esp+44h] [ebp-28h]
  int previousResourceHandle; // [esp+48h] [ebp-24h]
  int SpriteWidth; // [esp+4Ch] [ebp-20h]
  int SpriteHeight; // [esp+50h] [ebp-1Ch]

  messageText = a1;
  Debug_Log(a2, a3, a4, (int)aQueenmessageS);
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  previousRenderHook = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a3, a4, (int)aSetrhS08x_16);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, g_ActiveCursorDescriptor);
  Render_ReleaseSurface(17, a4);
  queenSpriteSet = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, v4, 0, a4);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, 0);
  queenSpriteSet = v5;
  panelLeft = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 0)) / 2;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)queenSpriteSet, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)queenSpriteSet, 0);
  Surface = (_DWORD *)Mem_Alloc(188, v7, 0, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  backdropSurface = Surface;
  Render_FillRect(0, Surface, 150, (unsigned __int16)panelLeft, panelLeft + SpriteHeight - 1, SpriteWidth + 149, 0, 0);
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar((int)queenSpriteSet, 14);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    150,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v10 = DLX_GetSpriteForChar((int)queenSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  deviceVtable = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(deviceVtable + 52))(
    168,
    v10,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UI_DrawTextFmt(150, panelLeft + 175, panelLeft + 525, 205, 6, messageText);
  Render_Present((int)g_RenderState);
  while ( !DD_IsFlipping(v11) )
    DD_Pump(v12, 0);
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  Debug_Log(v13, 0, (DWORD)g_RenderHook, (int)aUnsetrh08x_16);
  g_RenderHook = previousRenderHook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  Render_FillRect(backdropSurface, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, panelLeft, 0x96u);
  Render_Present((int)g_RenderState);
  if ( backdropSurface )
    (*(void (**)(void))backdropSurface[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&queenSpriteSet);
  return UI_EndDraw(17);
}
// 4473C0: variable 'v4' is possibly undefined
// 447424: variable 'v7' is possibly undefined
// 447537: variable 'v11' is possibly undefined
// 447544: variable 'v12' is possibly undefined
// 447579: variable 'v13' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 545150: using guessed type int dword_545150;

//----- (00447610) --------------------------------------------------------
int  UI_ShowMissionStatusPanel(int a1, DWORD a2)
{
  int missionIndex; // ecx
  const char *formatString; // esi
  int v5; // ecx
  int result; // eax
  _BYTE messageBuffer[100]; // [esp+0h] [ebp-80h] BYREF
  int statusFormatTable[7]; // [esp+64h] [ebp-1Ch] BYREF

  statusFormatTable[6] = a1;
  statusFormatTable[0] = (int)g_MissionStatusFormatsByLanguage[0];
  statusFormatTable[1] = (int)g_MissionStatusFormatsByLanguage[1];
  statusFormatTable[2] = (int)g_MissionStatusFormatsByLanguage[2];
  missionIndex = ACTIVE_MISSION_INDEX;
  if ( missionIndex != -1 )
  {
    formatString = (const char *)statusFormatTable[(unsigned __int8)g_LanguageIndex];
    sprintf_(
      messageBuffer,
      formatString,
      ACTIVE_MISSION_INDEX % 10 + 1,
      (&g_MissionStatusTextsByLanguage[3 * missionIndex])[(unsigned __int8)g_LanguageIndex]);
    return UI_ShowInfoWindow((const char *)messageBuffer, 2u, v5, a2, (int)&statusFormatTable[3], (int)formatString);
  }
  return result;
}
// 44768C: variable 'v5' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 5180C0: using guessed type char *g_MissionStatusTextsByLanguage[63];
// 5181B0: using guessed type char *g_MissionStatusFormatsByLanguage[3];
// 5202E4: using guessed type int gameData;

//----- (004476B0) --------------------------------------------------------
int Debug_GetUsedMemoryCount()
{
  return 0;
}

//----- (004476C0) --------------------------------------------------------
int __thiscall Object_ConstructInt256Array(void *this)
{
  return _wcpp_4_ctor_array__(this, 256);
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);

//----- (004476E0) --------------------------------------------------------
int  MainMenu_RequestExit(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_PlayGameMenuExitRequested = 1;
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_EXIT;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (004476D0) --------------------------------------------------------
static void MainMenu_WriteButtonWidgetTemplateRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        const char *sound_name)
{
  memset(record, 0, 53);
  *(_DWORD *)(record + 0) = left;
  *(_DWORD *)(record + 4) = top;
  record[8] = 1;
  *(_DWORD *)(record + 12) = (int)(uintptr_t)&g_PlayGameMenuSpriteSetHandle;
  *(_DWORD *)(record + 16) = sprite_index_base;
  *(_DWORD *)(record + 20) = sprite_index_selected_base;
  *(_DWORD *)(record + 24) = -1;
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionFast;
  *(_DWORD *)(record + 32) = action_callback;
  *(_DWORD *)(record + 49) = (int)(uintptr_t)sound_name;
}

static void CampaignMenu_WriteButtonWidgetTemplateRecord(
        unsigned char *record,
        int left,
        int top,
        int sprite_index_base,
        int sprite_index_selected_base,
        int action_callback,
        const char *sound_name)
{
  MainMenu_WriteButtonWidgetTemplateRecord(
    record,
    left,
    top,
    sprite_index_base,
    sprite_index_selected_base,
    action_callback,
    sound_name);
  *(_DWORD *)(record + 28) = (int)(uintptr_t)&UI_DrawWidgetIconTransitionSlow;
}

//----- (004476D0) --------------------------------------------------------
void MainMenu_RebuildButtonWidgetTemplate(void)
{
  static const char aMainMenuButtonClickSound[] = "menduze";

  /*
   * The original PE stores the top-level button table as a 0x35-byte record
   * blob at `unk_5181C0`. Rebuild it with live symbol addresses so the
   * recovered runtime sees the real menu layout instead of a one-byte stub.
   */
  memset(g_MainMenuButtonWidgetsTemplate, 0, sizeof(g_MainMenuButtonWidgetsTemplate));
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 0,
    159,
    136,
    0,
    3,
    (int)(uintptr_t)&MainMenu_RequestLoadGameMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 1,
    152,
    168,
    6,
    9,
    (int)(uintptr_t)&MainMenu_RequestCampaignMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 2,
    185,
    204,
    12,
    15,
    (int)(uintptr_t)&MainMenu_RequestExit,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 3,
    357,
    136,
    18,
    21,
    (int)(uintptr_t)&MainMenu_RequestOptionsMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 4,
    344,
    168,
    24,
    27,
    (int)(uintptr_t)&MainMenu_RequestMultiplayerMenu,
    aMainMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_MainMenuButtonWidgetsTemplate + 53 * 5,
    388,
    204,
    30,
    33,
    (int)(uintptr_t)&MainMenu_RequestCreditsCinematic,
    aMainMenuButtonClickSound);
  *(_DWORD *)(g_MainMenuButtonWidgetsTemplate + 53 * 6) = -1;
}

void CampaignMenu_RebuildButtonWidgetTemplate(void)
{
  static const char aCampaignMenuButtonClickSound[] = "menduze";

  /*
   * `unk_518338` is the original campaign choice blob: two 0x35-byte
   * button records plus a 0x35-byte terminator slot whose first dword is
   * `-1`. Rebuild it with live callback addresses and the slower
   * `sub_419770` transition used by asm.
   */
  memset(g_CampaignMenuButtonWidgetsTemplate, 0, sizeof(g_CampaignMenuButtonWidgetsTemplate));
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_CampaignMenuButtonWidgetsTemplate + 53 * 0,
    152,
    279,
    0,
    1,
    (int)(uintptr_t)&MultiplayerSetup_HandleConfirmButtonRelease,
    aCampaignMenuButtonClickSound);
  CampaignMenu_WriteButtonWidgetTemplateRecord(
    g_CampaignMenuButtonWidgetsTemplate + 53 * 1,
    384,
    279,
    2,
    3,
    (int)(uintptr_t)&MultiplayerSetup_HandleCancelButtonRelease,
    aCampaignMenuButtonClickSound);
  *(_DWORD *)(g_CampaignMenuButtonWidgetsTemplate + 53 * 2) = -1;
}

void LoadMenu_RebuildButtonWidgetTemplate(void)
{
  static const char aLoadMenuButtonClickSound[] = "menmale";

  /*
   * The original PE stores the load-menu button table as a 0x35-byte record
   * blob at `unk_518808`. Rebuild it with live symbol addresses so the
   * recovered runtime no longer depends on the weak-data stub on this path.
   */
  memset(g_LoadMenuButtonWidgetsTemplate, 0, sizeof(g_LoadMenuButtonWidgetsTemplate));
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_LoadMenuButtonWidgetsTemplate + 53 * 0,
    249,
    392,
    0,
    1,
    (int)(uintptr_t)&LoadMenu_HandleSlotConfirmButtonRelease,
    aLoadMenuButtonClickSound);
  MainMenu_WriteButtonWidgetTemplateRecord(
    g_LoadMenuButtonWidgetsTemplate + 53 * 1,
    329,
    408,
    2,
    3,
    (int)(uintptr_t)&MultiplayerSetup_HandleBackButtonRelease,
    aLoadMenuButtonClickSound);
  *(_DWORD *)(g_LoadMenuButtonWidgetsTemplate + 53 * 2) = -1;
}

//----- (00447700) --------------------------------------------------------
int  MainMenu_RequestCampaignMenu(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_CAMPAIGN;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447720) --------------------------------------------------------
int  MainMenu_RequestMultiplayerMenu(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_MULTIPLAYER;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447740) --------------------------------------------------------
int  MainMenu_RequestCreditsCinematic(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_CREDITS;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447760) --------------------------------------------------------
int  MainMenu_RequestOptionsMenu(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_OPTIONS;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (00447780) --------------------------------------------------------
int  MainMenu_RequestLoadGameMenu(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_MainMenuRequestedScreen = MAIN_MENU_REQUEST_LOAD_GAME;
  g_PlayGameMenuExitRequested = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;

//----- (004477A0) --------------------------------------------------------
signed int  UI_WaitForKeyOrTimeout(int timeoutMs, int a2)
{
  (void)a2;
  return UI_WaitForAnyKeyOrClick(Time_Now(0, 0) + timeoutMs, 0);
}

//----- (004477C0) --------------------------------------------------------
signed int  UI_WaitForAnyKeyOrClick(int deadlineTime, int a2)
{
  unsigned int deadline;

  (void)a2;
  deadline = (unsigned int)deadlineTime;
  Time_Now(0, 0);
  do
  {
    DD_Pump((int)g_RenderState, 0);
    if ( Input_IsKeyPressed(1)
      || Input_IsKeyPressed(57)
      || Input_IsKeyPressed(28)
      || DD_IsFlipping((int)g_RenderState)
      || DD_IsLost((int)g_RenderState) )
    {
      return 1;
    }
  }
  while ( (unsigned int)Time_Now(0, 0) <= deadline );
  return 0;
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (00447840) --------------------------------------------------------
DWORD  UI_StartAnims(int a1, char a2, DWORD a3)
{
  int (*previous_render_hook)(); // edi
  int previous_resource_handle; // esi

  Debug_Log(a1, a2, a3, (int)aStartanims);
  previous_resource_handle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  previous_render_hook = g_RenderHook;
  g_RenderHook = 0;
  Debug_Log(0, 0, a3, (int)aSetrhS08x_14, aNull, 0);
  Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
  DD_Pump((int)g_RenderState, 0);
  Sleep(0x4B0u);
  Video_Avi_playIn(aLogo_0, 0, 1, 0, 1, 0);
  if ( g_LanguageIndex == 2 )
    Video_Avi_playIn(aSoft2000, 0, 1, 0, 1, 0);
  if ( g_LanguageIndex )
  {
    if ( (unsigned __int8)g_LanguageIndex <= 1u )
    {
      Video_Avi_playIn(aInt_a_0, 0, 1, 0, 1, 1);
    }
    else if ( g_LanguageIndex == 2 )
    {
      Video_Avi_playIn(aInt_g, 0, 1, 0, 1, 1);
    }
  }
  else
  {
    Video_Avi_playIn(aInt_a, 0, 1, 0, 1, 1);
  }
  DD_Pump((int)g_RenderState, 0);
  Debug_Log(0, 0, a3, (int)aUnsetrh08x_14, g_RenderHook);
  g_RenderHook = previous_render_hook;
  Render_SetResourceHandle((int)&g_MainRenderDevice, previous_resource_handle);
  Debug_Log(0, 0, a3, (int)aStartanimsEnd);
  return a3;
}
// 511130: using guessed type char g_LanguageIndex;
// 5199D8: using guessed type int (*g_RenderHook)();
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (004479C0) --------------------------------------------------------
int  PlayGame_Dispatch(int a1, signed int a2, char *a3, double a4)
{
  _DWORD *Surface; // eax
  _DWORD *mainMenuSpriteSet; // eax
  int v12; // ecx
  int v17; // eax
  int v18; // ecx
  char *v19; // edi
  char *v20; // esi
  int v21; // ecx
  int v24; // ecx
  _DWORD *campaignSpriteSet; // eax
  bool i; // zf
  int campaign_menu_cancelled_by_escape; // ecx
  int v33; // ecx
  _DWORD *multiplayerSpriteSet; // eax
  int j; // edx
  int v54; // eax
  int v69; // edx
  int v70; // edx
  int v71; // edx
  unsigned int v72; // kr08_4
  int v73; // edx
  int v74; // edx
  int v75; // ecx
  int v76; // edx
  const char *v77; // edi
  unsigned int v78; // kr10_4
  int v79; // edx
  int v80; // ecx
  int v81; // edx
  int v82; // ecx
  int v83; // eax
  signed int v84; // esi
  unsigned __int16 v85; // ax
  int v86; // edx
  int v87; // edx
  int v88; // ecx
  int v89; // edx
  _DWORD *optionsSpriteSet; // eax
  int v93; // eax
  DWORD v97; // ebp
  int v98; // ecx
  _DWORD *loadMenuSpriteSet; // eax
  int k; // edx
  unsigned int v108; // eax
  int ( *v110)(int, char, DWORD); // [esp-4h] [ebp-2140h]
  _BYTE v112[7112]; // [esp+4h] [ebp-2138h] BYREF
  char v113[8]; // [esp+1BCCh] [ebp-570h] BYREF
  int v114; // [esp+1BD4h] [ebp-568h]
  _DWORD v115[11]; // [esp+1BDCh] [ebp-560h]
  int v116; // [esp+1C09h] [ebp-533h]
  int v117; // [esp+1C3Eh] [ebp-4FEh]
  int v118; // [esp+1C73h] [ebp-4C9h]
  _DWORD v119[8]; // [esp+1D1Fh] [ebp-41Dh]
  char v120[16]; // [esp+1D40h] [ebp-3FCh] BYREF
  _DWORD v121[89]; // [esp+1D50h] [ebp-3ECh]
  char v122[268]; // [esp+1EB4h] [ebp-288h] BYREF
  _DWORD v123[40]; // [esp+1FC0h] [ebp-17Ch] BYREF
  char v124[160]; // [esp+2060h] [ebp-DCh] BYREF
  int v125[5]; // [esp+2100h] [ebp-3Ch] BYREF
  int previous_load_slot;
  int selected_load_slot;
  char multiplayer_player_states[PLAYER_DATA_STRIDE * 5];
  int multiplayer_player_index;
  int multiplayer_player_type;
  char *multiplayer_player_state;
  int multiplayer_player_type_slot;
  int multiplayer_selected_name_slot;
  int multiplayer_previous_name_slot;
  int multiplayer_map_row;
  int v126; // [esp+2114h] [ebp-28h]
  int (*v127)(); // [esp+2118h] [ebp-24h]
  int needMenuFadeIn; // [esp+211Ch] [ebp-20h]
  char v129; // [esp+2120h] [ebp-1Ch]

  Debug_Log(a1, a2, (DWORD)a3, (int)aStartmenu);
  Surface = (_DWORD *)Mem_Alloc(188, 0, 0, 0);
  if ( Surface )
  {
    LOBYTE(a2) = -32;
    Surface = Render_CreateSurface((int)Surface, SCREEN_WIDTH, SCREEN_HEIGHT);
  }
  g_PrimaryRenderSurface = (int)Surface;
  UI_StartAnims(0, a2, (DWORD)a3);
  v126 = Render_SetResourceHandle((int)&g_MainRenderDevice, 1);
  v110 = Render_DefaultRH;
  v127 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(0, 0, (DWORD)a3, (int)aSetrhS08x_15, aStdrh_10, Render_DefaultRH);
  DD_Pump((int)g_RenderState, a2);
  needMenuFadeIn = 1;
  do
  {
    mainMenuSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( mainMenuSpriteSet )
      mainMenuSpriteSet = DLXSpriteSet_Load(mainMenuSpriteSet, "menu\\main.s32");
    g_PlayGameMenuSpriteSetHandle = (int)mainMenuSpriteSet;
    Render_LoadPCXImage(g_PrimaryRenderSurface, aMenuMain_gfx, 0, (uintptr_t)g_MenuScreenPaletteBuffer);
    Palette_LoadOrBuildBlendLookupTable(aMenuMain, (int)g_MenuScreenPaletteBuffer, v12, (DWORD)a3);
    if ( needMenuFadeIn && g_Options_MusicEnabledFlag )
      g_MainMenuMusicHandle = Sound_PlayNamedSfxFile(aMusicMenu, 64);
    DD_Pump((int)g_RenderState, 0);
    if ( needMenuFadeIn )
      Palette_ApplyDefaultPalette((int *)&g_MainRenderDevice);
    DD_Pump((int)g_RenderState, 0);
    Debug_Log(0, 0, (DWORD)a3, (int)aDraw1);
    Render_ClearGameScreen((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
    Debug_Log(0, 0, (DWORD)a3, (int)aDraw2);
    Render_ClearGameScreen((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
    Debug_Log(0, 0, (DWORD)a3, (int)aDrawend);
    MainMenu_RebuildButtonWidgetTemplate();
    v17 = 0;
    qmemcpy(v120, g_MainMenuButtonWidgetsTemplate, sizeof(g_MainMenuButtonWidgetsTemplate));
    do
    {
      a3 = (char *)((unsigned __int8)g_LanguageIndex + *(_DWORD *)((char *)v121 + v17));
      *(_DWORD *)((char *)v121 + v17) = a3;
      v21 = *(_DWORD *)((char *)&v121[1] + v17);
      v17 += 53;
      *(_DWORD *)((char *)v119 + v17) = (unsigned __int8)g_LanguageIndex + v21;
    }
    while ( v17 != 371 );
    a2 = (signed int)&g_MainRenderDevice;
    g_RenderDevice = &g_MainRenderDevice;
    UIWidgetTable_InitDrawStates(v120);
    if ( needMenuFadeIn )
    {
      a2 = 60;
      Palette_FadeInFromBlack((int *)&g_MainRenderDevice, g_MenuScreenPaletteBuffer, 60);
    }
    g_PlayGameMenuExitRequested = 0;
    RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_MenuScreenPaletteBuffer, 0, 0);
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
    g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
    Render_Present((int)g_RenderState);
    needMenuFadeIn = 0;
    if ( !g_PlayGameMenuExitRequested )
    {
      a2 = (signed int)g_RenderState;
      do
      {
        DD_Pump((int)g_RenderState, 0);
        UIWidgetTable_PollHoverAndActions(v120, 0);
      }
      while ( !g_PlayGameMenuExitRequested );
    }
    Render_Pump();
    DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
    switch ( g_MainMenuRequestedScreen )
    {
      case MAIN_MENU_REQUEST_CAMPAIGN:
        campaignSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( campaignSpriteSet )
          campaignSpriteSet = DLXSpriteSet_Load(campaignSpriteSet, "menu\\kamp.s32");
        g_PlayGameMenuSpriteSetHandle = (int)campaignSpriteSet;
        RenderSurface_InvokeSlot48LoadPCX(
          (_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface,
          aMenuMain_gfx_0,
          0,
          (uintptr_t)g_MenuScreenPaletteBuffer);
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)g_PrimaryRenderSurface);
        CampaignMenu_RebuildButtonWidgetTemplate();
        qmemcpy(v124, g_CampaignMenuButtonWidgetsTemplate, sizeof(g_CampaignMenuButtonWidgetsTemplate));
        g_RenderDevice = &g_MainRenderDevice;
        UIWidgetTable_InitDrawStates(v124);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_MenuScreenPaletteBuffer, 0, 0);
        a3 = (char *)&g_CursorDesc_Default;
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
        Render_Present((int)g_RenderState);
        campaign_menu_cancelled_by_escape = 0;
        for ( i = g_PlayGameMenuExitRequested == 0; i; i = g_PlayGameMenuExitRequested == 0 )
        {
          DD_Pump((int)g_RenderState, 0);
          UIWidgetTable_PollHoverAndActions(v124, 0);
          if ( Input_IsKeyPressed(1) )
          {
            campaign_menu_cancelled_by_escape = 1;
            g_PlayGameMenuExitRequested = 1;
            break;
          }
        }
        Render_Pump();
        if ( !campaign_menu_cancelled_by_escape )
          Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        if ( !campaign_menu_cancelled_by_escape && g_PlayGameMenuSelectedAction != -1 )
        {
          if ( g_PlayGameMenuSelectedAction == 1 )
          {
            LOBYTE(a2) = 1;
            CSS_StopSound(g_MainMenuMusicHandle, 1000);
            needMenuFadeIn = 1;
            Scenario_LoadMissionByIndexAndPlay(0, 0, (DWORD)&g_CursorDesc_Default, a4);
          }
          else
          {
            CSS_StopSound(g_MainMenuMusicHandle, 1000);
            Scenario_LoadMissionByIndexAndPlay((char *)0xA, 0, (DWORD)&g_CursorDesc_Default, a4);
            needMenuFadeIn = 1;
          }
        }
        break;
      case MAIN_MENU_REQUEST_CREDITS:
        CSS_StopSound(g_MainMenuMusicHandle, 1000);
        Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        LOBYTE(a2) = 0;
        Video_Avi_playIn(aCre_an, 0, 1, 0, 1, 1);
        needMenuFadeIn = 1;
        break;
      case MAIN_MENU_REQUEST_MULTIPLAYER:
        memset(g_MultiplayerPlayerSlotTypes, 5, 5);
        g_MultiplayerPlayerSlotTypes[0] = 3;
        g_MultiplayerPlayerSlot1Type = 0;
        g_MultiplayerPlayerSlot3Type = 1;
        g_MultiplayerPlayerSlot2Type = 2;
        qmemcpy(v125, &g_MultiplayerDefaultRulerNamesTable, sizeof(v125));
        Player_AssignRandomUniqueRulerNames(5, v125);
        g_MultiplayerSelectedMapIndex = 0;
        g_MpEditNameSlotIndex = -1;
        g_MultiplayerOpponentListScrollOffset = 0;
        multiplayerSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( multiplayerSpriteSet )
          multiplayerSpriteSet = DLXSpriteSet_Load(multiplayerSpriteSet, aMenuMultipl_s32);
        g_PlayGameMenuSpriteSetHandle = (int)multiplayerSpriteSet;
        a2 = (signed int)g_MenuScreenPaletteBuffer;
        (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, aMenuMultipl_gf);
        Render_LoadResourceSprite_v4(18, g_MenuScreenPaletteBuffer, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, g_MenuScreenPaletteBuffer, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
        MultiplayerSetup_RedrawPlayerSlotIcons();
        (*(void (**)(void))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 36))();
        for ( j = 0; j < 5; ++j )
          MultiplayerSetup_RepaintPlayerSlotRow(j, j + 1, 0);
        MultiplayerSetup_RedrawOpponentNameList();
        qmemcpy(v122, &g_MultiplayerSetupWidgetTemplateBlob, 265);
        g_RenderDevice = &g_MainRenderDevice;
        UIWidgetTable_InitDrawStates(v122);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_MenuScreenPaletteBuffer, 0, 0);
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
        Render_Present((int)g_RenderState);
        while ( !g_PlayGameMenuExitRequested )
        {
          DD_Pump((int)g_RenderState, 0);
          if ( DD_IsFlipping((int)g_RenderState)
            && g_MouseCursorRawX >> g_CursorCoordShift >= 176
            && g_MouseCursorRawX >> g_CursorCoordShift <= 236
            && (unsigned int)(((g_MouseCursorRawY >> g_CursorCoordShift) - 129) / 53) <= 4 )
          {
            multiplayer_player_type_slot = ((g_MouseCursorRawY >> g_CursorCoordShift) - 129) / 53;
            Audio_PlayButtonSound(aMale_2);
            g_MultiplayerPlayerSlotTypes[multiplayer_player_type_slot] = ((unsigned __int8)g_MultiplayerPlayerSlotTypes[multiplayer_player_type_slot] + 1) % 6;
            MultiplayerSetup_RedrawPlayerSlotIcons();
            MultiplayerSetup_RepaintPlayerSlotRow(multiplayer_player_type_slot, 0, 0);
            Render_Begin((int)g_RenderState, 0);
          }
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift >= 239 && g_MouseCursorRawX >> g_CursorCoordShift <= 339 )
            {
              multiplayer_selected_name_slot = ((g_MouseCursorRawY >> g_CursorCoordShift) - 144) / 53;
              if ( multiplayer_selected_name_slot <= 4 )
              {
                multiplayer_previous_name_slot = g_MpEditNameSlotIndex;
                if ( multiplayer_selected_name_slot != g_MpEditNameSlotIndex )
                {
                  g_MpEditNameSlotIndex = multiplayer_selected_name_slot;
                  g_PlayerNameEditCaretPos = 0;
                  if ( multiplayer_previous_name_slot != -1 )
                    MultiplayerSetup_RepaintPlayerSlotRow(multiplayer_previous_name_slot, 0, 0);
                  MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, 0, 0);
                }
              }
            }
          }
          if ( g_MpEditNameSlotIndex != -1 )
          {
            if ( Input_IsKeyPressed(203) )
            {
              v69 = g_PlayerNameEditCaretPos;
              if ( g_PlayerNameEditCaretPos )
              {
                MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v69, --g_PlayerNameEditCaretPos);
                Input_ClearKey(203, v70);
              }
            }
            if ( Input_IsKeyPressed(205) )
            {
              v72 = strlen(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex]) + 1;
              if ( v72 - 1 > g_PlayerNameEditCaretPos )
              {
                ++g_PlayerNameEditCaretPos;
                MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v71, v72 - 1);
                Input_ClearKey(205, v73);
              }
            }
            if ( Input_IsKeyPressed(211) )
            {
              LOBYTE(a2) = strlen(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + 1 + g_PlayerNameEditCaretPos]) + 1;
              memmove_(
                &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos],
                &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1],
                strlen(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1]) + 1);
              MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v74, v75);
              Input_ClearKey(211, v76);
            }
            if ( Input_IsKeyPressed(14) )
            {
              LOBYTE(a2) = g_PlayerNameEditCaretPos;
              if ( g_PlayerNameEditCaretPos )
              {
                v77 = &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos--];
                v78 = strlen(v77) + 1;
                a3 = (char *)g_PlayerNameEditCaretPos;
                LOBYTE(a2) = v78;
                memmove_(
                  &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos],
                  &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1],
                  v78);
                MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v79, v80);
                Input_ClearKey(14, v81);
              }
            }
            if ( Input_IsKeyPressed(28) )
            {
              v83 = g_MpEditNameSlotIndex;
              g_MpEditNameSlotIndex = -1;
              MultiplayerSetup_RepaintPlayerSlotRow(v83, -1, v82);
            }
            v84 = Input_PopKey();
            Render_ReleaseSurface(18, 0);
            if ( v84 != -1 )
            {
              v129 = Input_KeyToChar(v84);
              if ( v129 )
              {
                if ( strlen(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex]) < 0xA )
                {
                  Render_LoadResourceSprite_v3(aW);
                  LOBYTE(a2) = g_MpEditNameSlotIndex;
                  v85 = Render_LoadResourceSprite_v3(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex]);
                  if ( v85 < v86 )
                  {
                    LOBYTE(a2) = strlen(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos]) + 1;
                    memmove_(
                      &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos + 1],
                      &g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos],
                      strlen(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos]) + 1);
                    v87 = 11 * g_MpEditNameSlotIndex;
                    v88 = g_PlayerNameEditCaretPos + 1;
                    LOBYTE(v87) = v129;
                    g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex + g_PlayerNameEditCaretPos] = v129;
                    g_PlayerNameEditCaretPos = v88;
                    MultiplayerSetup_RepaintPlayerSlotRow(g_MpEditNameSlotIndex, v87, v88);
                    Input_ClearKey(v84, v89);
                  }
                }
              }
            }
          }
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift >= 356 && g_MouseCursorRawX >> g_CursorCoordShift <= 477 )
            {
              multiplayer_map_row = ((g_MouseCursorRawY >> g_CursorCoordShift) - 134) / 22;
              if ( multiplayer_map_row <= 0xA )
              {
                LOBYTE(a2) = g_MultiplayerOpponentListScrollOffset;
                v54 = g_MultiplayerOpponentListScrollOffset + multiplayer_map_row;
                if ( v54 != g_MultiplayerSelectedMapIndex )
                {
                  g_MultiplayerSelectedMapIndex = v54;
                  Audio_PlayButtonSound(aMale_1);
                  MultiplayerSetup_RedrawOpponentNameList();
                  Render_Begin((int)g_RenderState, 0);
                }
              }
            }
          }
          UIWidgetTable_PollHoverAndActions(v122, 0);
        }
        Render_Pump();
        if ( g_PlayGameMenuLaunchGameFlag )
          Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        needMenuFadeIn = g_PlayGameMenuLaunchGameFlag;
        if ( g_PlayGameMenuLaunchGameFlag )
        {
          CSS_StopSound(g_MainMenuMusicHandle, 1000);
          WorldMap_Initialize(0, (DWORD)a3);
          for ( multiplayer_player_index = 0; multiplayer_player_index < 5; ++multiplayer_player_index )
          {
            multiplayer_player_state = &multiplayer_player_states[PLAYER_DATA_STRIDE * multiplayer_player_index];
            PlayerRuntimeState_ResetDefaults((uintptr_t)multiplayer_player_state);
            *(_DWORD *)multiplayer_player_state = 1;
            multiplayer_player_type = (unsigned __int8)g_MultiplayerPlayerSlotTypes[multiplayer_player_index];
            switch ( multiplayer_player_type )
            {
              case 0:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 0;
                *(_DWORD *)(multiplayer_player_state + PLAYER_AI_INTELLIGENCE_OFFSET) = 0;
                break;
              case 1:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 0;
                *(_DWORD *)(multiplayer_player_state + PLAYER_AI_INTELLIGENCE_OFFSET) = 1;
                break;
              case 2:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 0;
                *(_DWORD *)(multiplayer_player_state + PLAYER_AI_INTELLIGENCE_OFFSET) = 2;
                break;
              case 3:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_MINIMAP_VISIBLE_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_RELIGION_FLAG_OFFSET) = 1;
                break;
              case 4:
                *(_DWORD *)(multiplayer_player_state + PLAYER_IS_HUMAN_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_MINIMAP_VISIBLE_OFFSET) = 1;
                *(_DWORD *)(multiplayer_player_state + PLAYER_RELIGION_FLAG_OFFSET) = 0;
                break;
              case 5:
                *(_DWORD *)multiplayer_player_state = 0;
                break;
              default:
                break;
            }
            strcpy(multiplayer_player_state + PLAYER_DISPLAY_NAME_OFFSET, &g_MultiplayerPlayerNameEditTable[11 * multiplayer_player_index]);
          }
          Scenario_LoadMultiplayerMapAndSeedPlayers(g_MultiplayerSelectedMapIndex, (uintptr_t)multiplayer_player_states);
          PlayGame(0, 0, (DWORD)a3, 0, a4);
        }
        break;
      case MAIN_MENU_REQUEST_OPTIONS:
        optionsSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( optionsSpriteSet )
          optionsSpriteSet = DLXSpriteSet_Load(optionsSpriteSet, aMenuOpt_s32);
        g_PlayGameMenuSpriteSetHandle = (int)optionsSpriteSet;
        if ( g_LanguageIndex )
        {
          if ( (unsigned __int8)g_LanguageIndex <= 1u )
          {
            a2 = (signed int)g_MenuScreenPaletteBuffer;
            (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, aMenuOpt_a_gfx);
          }
          else if ( g_LanguageIndex == 2 )
          {
            a2 = (signed int)g_MenuScreenPaletteBuffer;
            (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, aMenuOpt_g_gfx);
          }
        }
        else
        {
          a2 = (signed int)g_MenuScreenPaletteBuffer;
          (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, aMenuOpt_p_gfx);
        }
        Render_LoadResourceSprite_v4(18, g_MenuScreenPaletteBuffer, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, g_MenuScreenPaletteBuffer, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
        (*(void (__thiscall **)(int))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 36))(92);
        v93 = 0;
        qmemcpy(v113, &g_OptionsMenuWidgetTemplateBlob, 371);
        do
        {
          v97 = (unsigned __int8)g_LanguageIndex + *(_DWORD *)((char *)v115 + v93);
          *(_DWORD *)((char *)v115 + v93) = v97;
          v98 = *(_DWORD *)((char *)&v115[1] + v93);
          v93 += 53;
          *(_DWORD *)&v112[v93 + 7079] = (unsigned __int8)g_LanguageIndex + v98;
        }
        while ( v93 != 212 );
        if ( g_OptionsConfigRecordFlag0C )
          v114 = 2;
        if ( g_OptionsConfigRecordBase )
          v116 = 2;
        if ( g_Options_MusicEnabledFlag )
          v117 = 2;
        if ( g_Options_UnitSoundsEnabledFlag )
          v118 = 2;
        g_Options_BrightnessSliderValue = ((g_OptionsMainMenuMusicVolumeRaw << 8)
                      + 0x4000
                      - (__CFSHL__(((g_OptionsMainMenuMusicVolumeRaw << 8) + 0x4000) >> 31, 7)
                       + (((g_OptionsMainMenuMusicVolumeRaw << 8) + 0x4000) >> 31 << 7))) >> 7;
        g_Options_ScrollSpeedSliderValue = (((unsigned __int8)g_OptionsMainMenuScrollSpeedRaw << 8)
                      - (__CFSHL__((unsigned __int8)g_OptionsMainMenuScrollSpeedRaw << 8 >> 31, 4)
                       + 16 * ((unsigned __int8)g_OptionsMainMenuScrollSpeedRaw << 8 >> 31))) >> 4;
        g_Options_MouseSpeedSliderValue = (((unsigned __int8)g_OptionsMainMenuSoundVolumeRaw << 8)
                      - (__CFSHL__((unsigned __int8)g_OptionsMainMenuSoundVolumeRaw << 8 >> 31, 4)
                       + 16 * ((unsigned __int8)g_OptionsMainMenuSoundVolumeRaw << 8 >> 31))) >> 4;
        g_RenderDevice = &g_MainRenderDevice;
        UIWidgetTable_InitDrawStates(v113);
        Options_DrawAllSliderThumbs(g_OptionsMenuSliderThumbPositions, a2, v97);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_MenuScreenPaletteBuffer, 0, 0);
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
        Render_Present((int)g_RenderState);
        if ( !g_PlayGameMenuExitRequested )
        {
          do
          {
            DD_Pump((int)g_RenderState, 0);
            Options_AnimateAllSliderThumbs(g_OptionsMenuSliderThumbPositions);
            UIWidgetTable_PollHoverAndActions(v113, 0);
          }
          while ( !g_PlayGameMenuExitRequested );
        }
        a2 = g_Options_MusicEnabledFlag;
        g_OptionsConfigRecordFlag0C = v114 == 2;
        g_OptionsConfigRecordBase = v116 == 2;
        g_Options_MusicEnabledFlag = v117 == 2;
        g_Options_UnitSoundsEnabledFlag = v118 == 2;
        g_OptionsMainMenuMusicVolumeRaw = ((unsigned __int16)(((_WORD)g_Options_BrightnessSliderValue << 7)
                                        - (__CFSHL__(g_Options_BrightnessSliderValue << 7 >> 31, 8)
                                         + ((__int16)((unsigned int)g_Options_BrightnessSliderValue >> 9) >> 15 << 8))) >> 8)
                    - 64;
        g_OptionsMainMenuScrollSpeedRaw = (unsigned __int16)(16 * g_Options_ScrollSpeedSliderValue
                                       - (__CFSHL__((16 * g_Options_ScrollSpeedSliderValue) >> 31, 8)
                                        + ((__int16)((unsigned int)g_Options_ScrollSpeedSliderValue >> 12) >> 15 << 8))) >> 8;
        g_OptionsMainMenuSoundVolumeRaw = (unsigned __int16)(16 * g_Options_MouseSpeedSliderValue
                                       - (__CFSHL__((16 * g_Options_MouseSpeedSliderValue) >> 31, 8)
                                        + ((__int16)((unsigned int)g_Options_MouseSpeedSliderValue >> 12) >> 15 << 8))) >> 8;
        if ( v117 == 2 )
        {
          Audio_SetMusicActiveFlag();
          if ( !a2 )
            g_MainMenuMusicHandle = Sound_PlayNamedSfxFile(aMusicMenu_0, 64);
        }
        else
        {
          if ( a2 )
            Audio_StopMusicWithFade(g_MainMenuMusicHandle);
          Audio_ClearMusicActiveFlag();
        }
        Options_ApplyRecordSettings((int)&g_OptionsConfigRecordBase, 0, 0);
        Options_SaveConfigToFile(0, 0);
        Options_DestroySliderThumbList(g_OptionsMenuSliderThumbPositions);
        Render_Pump();
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        break;
      case MAIN_MENU_REQUEST_LOAD_GAME:
        g_LoadMenuSelectedSlotIndex = -1;
        loadMenuSpriteSet = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( loadMenuSpriteSet )
          loadMenuSpriteSet = DLXSpriteSet_Load(loadMenuSpriteSet, aMenuLoad_s32);
        g_PlayGameMenuSpriteSetHandle = (int)loadMenuSpriteSet;
        (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, aMenuLoad_gfx);
        Render_LoadResourceSprite_v4(18, g_MenuScreenPaletteBuffer, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, g_MenuScreenPaletteBuffer, 0, 0, 0);
        (*(void (**)(void))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 36))();
        for ( k = 0; k < 10; ++k )
          LoadMenu_RedrawSaveSlotRow(k, (DWORD)a3);
        LoadMenu_RebuildButtonWidgetTemplate();
        qmemcpy(v123, &g_LoadMenuButtonWidgetsTemplate, 0x9Fu);
        g_RenderDevice = &g_MainRenderDevice;
        UIWidgetTable_InitDrawStates(v123);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)g_MenuScreenPaletteBuffer, 0, 0);
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        g_ActiveCursorDescriptor = (int)&g_CursorDesc_Default;
        Render_Present((int)g_RenderState);
        while ( !g_PlayGameMenuExitRequested )
        {
          DD_Pump((int)g_RenderState, 0);
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            if ( g_MouseCursorRawX >> g_CursorCoordShift >= 244 && g_MouseCursorRawX >> g_CursorCoordShift <= 410 )
            {
              v108 = ((g_MouseCursorRawY >> g_CursorCoordShift) - 155) / 22;
              if ( v108 <= 9 )
              {
                previous_load_slot = g_LoadMenuSelectedSlotIndex;
                if ( v108 != g_LoadMenuSelectedSlotIndex )
                {
                  g_LoadMenuSelectedSlotIndex = ((g_MouseCursorRawY >> g_CursorCoordShift) - 155) / 22;
                  if ( previous_load_slot != -1 )
                    LoadMenu_RedrawSaveSlotRow(previous_load_slot, (DWORD)a3);
                  LoadMenu_RedrawSaveSlotRow(g_LoadMenuSelectedSlotIndex, (DWORD)a3);
                }
                if ( RenderState_IsCursorFlipStillActive((int)g_RenderState) )
                  LoadMenu_HandleSlotConfirmButtonRelease(0, (DWORD)a3);
              }
            }
          }
          UIWidgetTable_PollHoverAndActions(v123, 0);
        }
        Render_Pump();
        if ( g_PlayGameMenuLaunchGameFlag )
          Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        if ( !g_PlayGameMenuLaunchGameFlag )
          g_LoadMenuSelectedSlotIndex = -1;
        selected_load_slot = g_LoadMenuSelectedSlotIndex;
        if ( selected_load_slot != -1 )
        {
          CSS_StopSound(g_MainMenuMusicHandle, 1000);
          WorldMap_Initialize((char)selected_load_slot, (DWORD)a3);
          needMenuFadeIn = 1;
          SaveSlot_LoadGame(selected_load_slot, (DWORD)a3, a4);
          PlayGame(0, (char)selected_load_slot, (DWORD)a3, 1, a4);
        }
        break;
      default:
        break;
    }
  }
  while ( g_MainMenuRequestedScreen );
  CSS_StopSound(g_MainMenuMusicHandle, 1000);
  Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
  Render_UnlockBackbuffer((int)&g_MainRenderDevice);
  HIBYTE(v110) = HIBYTE(g_RenderHook);
  Debug_Log(v33, a2, (DWORD)g_RenderHook, (int)aUnsetrh08x_15);
  g_RenderHook = v127;
  return Render_SetResourceHandle((int)&g_MainRenderDevice, v126);
}
// 44806D: simplified comparisons for 'eax.4': <0 || >=5 became >=5u
// 4480F9: simplified comparisons for 'eax.4': <0 || >=B became >=Bu
// 448AAB: simplified comparisons for 'eax.4': <0 || >=A became >=Au
// 44824F: simplified comparisons for '((($dword_544D00.4 >>a $byte_54512C.1)-#0x81.4) /s #0x35.4)': <0 || >=5 became >=5u
// 4479DE: variable 'v5' is possibly undefined
// 4479F0: variable 'v7' is possibly undefined
// 447A39: variable 'v8' is possibly undefined
// 447A50: variable 'v9' is possibly undefined
// 447A9F: variable 'v12' is possibly undefined
// 447AF1: variable 'v14' is possibly undefined
// 447B0C: variable 'v15' is possibly undefined
// 447B38: variable 'v16' is possibly undefined
// 447B42: variable 'v18' is possibly undefined
// 447BC9: variable 'v23' is possibly undefined
// 447C24: variable 'v24' is possibly undefined
// 447DA4: variable 'v33' is possibly undefined
// 4482D9: variable 'v70' is possibly undefined
// 44831B: variable 'v71' is possibly undefined
// 448325: variable 'v73' is possibly undefined
// 448381: variable 'v74' is possibly undefined
// 448381: variable 'v75' is possibly undefined
// 44838B: variable 'v76' is possibly undefined
// 4483F4: variable 'v79' is possibly undefined
// 4483F4: variable 'v80' is possibly undefined
// 4483FE: variable 'v81' is possibly undefined
// 448421: variable 'v82' is possibly undefined
// 4484B1: variable 'v86' is possibly undefined
// 44852A: variable 'v89' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 47BB96: using guessed type int __fastcall memmove_(_DWORD, _DWORD);
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5184DC: using guessed type char *off_5184DC;
// 518600: using guessed type unsigned __int16 word_518600[6];
// 51860C: using guessed type int dword_51860C;
// 518630: using guessed type int dword_518630;
// 518654: using guessed type int dword_518654;
// 5188B0: using guessed type int dword_5188B0;
// 5188BC: using guessed type int dword_5188BC;
// 5188C0: using guessed type int dword_5188C0;
// 5188C4: using guessed type int dword_5188C4;
// 5188C8: using guessed type char byte_5188C8;
// 5188C9: using guessed type char byte_5188C9;
// 5188CA: using guessed type char byte_5188CA;
// 5199D8: using guessed type int (*g_RenderHook)();
// 5202E0: using guessed type int dword_5202E0;
// 543D74: using guessed type int g_PlayGameMenuSpriteSetHandle;
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 543D7C: using guessed type int g_MainMenuRequestedScreen;
// 543D80: using guessed type unsigned __int8 byte_543D80[1024];
// 544180: using guessed type int g_MainMenuMusicHandle;
// 544184: using guessed type int dword_544184;
// 544189: using guessed type char byte_544189;
// 54418A: using guessed type char byte_54418A;
// 54418B: using guessed type char byte_54418B;
// 544190: using guessed type int dword_544190;
// 544194: using guessed type int dword_544194;
// 544198: using guessed type int dword_544198;
// 5441A0: using guessed type _BYTE byte_5441A0[11];
// 5441D8: using guessed type int dword_5441D8;
// 5441DC: using guessed type int dword_5441DC;
// 5441E0: using guessed type int dword_5441E0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;
// 545150: using guessed type int dword_545150;

//----- (00448B90) --------------------------------------------------------
int  MultiplayerSetup_HandleConfirmButtonRelease(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_PlayGameMenuExitRequested = 1;
  g_PlayGameMenuSelectedAction = 1;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544184: using guessed type int dword_544184;

//----- (00448BB0) --------------------------------------------------------
int  MultiplayerSetup_HandleCancelButtonRelease(uintptr_t a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_PlayGameMenuExitRequested = 1;
  g_PlayGameMenuSelectedAction = 0;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544184: using guessed type int dword_544184;

//----- (00448D10) --------------------------------------------------------
int  MultiplayerSetup_RepaintPlayerSlotRow(int slotRow, int a2, int a3)
{
  __int16 rowBaseY; // di
  DWORD rowBottomY; // ebp
  int rowTopY; // edi
  int slotType; // eax
  int result; // eax
  unsigned __int16 rowBottomY16; // [esp-4h] [ebp-20h]
  int cursorOverlayPresented; // [esp+0h] [ebp-1Ch]

  rowBaseY = 53 * slotRow;
  Str_TitleCase(&g_MultiplayerPlayerNameEditTable[11 * g_MpEditNameSlotIndex], a2, a3);
  cursorOverlayPresented = g_CursorOverlayPresented;
  rowBottomY = (unsigned __int16)(rowBaseY + 167);
  rowBottomY16 = rowBaseY + 167;
  rowTopY = (unsigned __int16)(rowBaseY + 144);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xEFu, 0x153u, rowTopY, rowBottomY16);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, rowTopY, 234, 0x15Du, rowBottomY, 0xEAu, rowTopY);
  Render_ReleaseSurface(18, rowBottomY);
  if ( slotRow == g_MpEditNameSlotIndex )
    UI_SetTextCursorPosition(g_PlayerNameEditCaretPos);
  slotType = (unsigned __int8)g_MultiplayerPlayerSlotTypes[slotRow];
  g_RenderDevice = &g_MainRenderDevice;
  if ( slotType != 5 )
    UI_DrawTextFmt(rowTopY, 239, 339, 53 * slotRow + 144, 3, (int)&g_MultiplayerPlayerNameEditTable[11 * slotRow]);
  result = UI_SetTextCursorPosition(-1);
  if ( cursorOverlayPresented )
    return Render_Present((int)g_RenderState);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 544194: using guessed type int dword_544194;
// 544198: using guessed type int dword_544198;
// 5441A0: using guessed type _BYTE byte_5441A0[11];
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00448E10) --------------------------------------------------------
signed int  MultiplayerSetup_HandleStartButtonRelease(int a1)
{
  signed int result; // eax
  int slotType; // edx
  int activePlayerCount; // edx

  UIWidget_PlayPressedReleaseAnimation(a1);
  for ( result = 0; result < 5; ++result )
  {
    slotType = (unsigned __int8)g_MultiplayerPlayerSlotTypes[result];
    if ( slotType == 3 )
      break;
    if ( slotType == 4 )
      break;
  }
  if ( result != 5 )
  {
    activePlayerCount = 0;
    for ( result = 0; result < 5; ++result )
    {
      if ( g_MultiplayerPlayerSlotTypes[result] != 5 )
        ++activePlayerCount;
    }
    if ( activePlayerCount > 1 && g_MultiplayerSelectedMapIndex != -1 )
    {
      g_PlayGameMenuLaunchGameFlag = 1;
      g_PlayGameMenuExitRequested = 1;
    }
  }
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;
// 5441D8: using guessed type int dword_5441D8;

//----- (00448E80) --------------------------------------------------------
int  MultiplayerSetup_HandleBackButtonRelease(int a1)
{
  int result; // eax

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_PlayGameMenuExitRequested = 1;
  g_PlayGameMenuLaunchGameFlag = 0;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;

//----- (00448EA0) --------------------------------------------------------
int MultiplayerSetup_RedrawPlayerSlotIcons()
{
  int iconLeftX; // edi
  int slotIndex; // esi
  int SpriteForChar; // eax
  int v3; // ecx
  int result; // eax
  int cursorOverlayPresented; // [esp+1Ch] [ebp-1Ch]

  iconLeftX = 129;
  cursorOverlayPresented = g_CursorOverlayPresented;
  slotIndex = 0;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xB0u, 0xECu, 0x81u, 0x18Au);
  do
  {
    SpriteForChar = DLX_GetSpriteForChar(g_PlayGameMenuSpriteSetHandle, (unsigned __int8)g_MultiplayerPlayerSlotTypes[slotIndex] + 8);
    v3 = iconLeftX;
    ++slotIndex;
    iconLeftX += 53;
    result = (*(int (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46)
                                                                                      + 52))(
               v3,
               SpriteForChar,
               -1,
               -1,
               -1,
               -1,
               1,
               0,
               0);
  }
  while ( slotIndex < 5 );
  if ( cursorOverlayPresented )
    return Render_Present((int)g_RenderState);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 543D74: using guessed type int g_PlayGameMenuSpriteSetHandle;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (00449330) --------------------------------------------------------
int MultiplayerSetup_RedrawOpponentNameList()
{
  DWORD cursorOverlayPresented; // ebp
  int rowTopY; // edi
  int rowIndex; // esi
  int result; // eax
  int rowSpriteId; // eax

  cursorOverlayPresented = g_CursorOverlayPresented;
  if ( g_CursorOverlayPresented )
    RenderState_PumpIfRectInViewBounds(g_RenderState, 0x164u, 0x1DDu, 0x86u, 0x175u);
  rowTopY = 134;
  rowIndex = 0;
  g_RenderDevice = &g_MainRenderDevice;
  do
  {
    result = Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)rowTopY, 356, 0x1DDu, rowTopY + 22, 0x164u, rowTopY);
    if ( rowIndex + g_MultiplayerOpponentListScrollOffset < 20 )
    {
      if ( rowIndex + g_MultiplayerOpponentListScrollOffset == g_MultiplayerSelectedMapIndex )
        rowSpriteId = 21;
      else
        rowSpriteId = 18;
      Render_ReleaseSurface(rowSpriteId, cursorOverlayPresented);
      result = UI_DrawText(356, rowTopY, (int)&aKarkhan[13 * rowIndex + 13 * g_MultiplayerOpponentListScrollOffset]);
    }
    ++rowIndex;
    rowTopY += 22;
  }
  while ( rowIndex < 11 );
  if ( cursorOverlayPresented )
    return Render_Present((int)g_RenderState);
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5441D8: using guessed type int dword_5441D8;
// 5441DC: using guessed type int dword_5441DC;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (004494B0) --------------------------------------------------------
int  MultiplayerSetup_HandleScrollListDownButton(int a1)
{
  UIWidget_PlayPressedReleaseAnimation(a1);
  if ( g_MultiplayerOpponentListScrollOffset < 19 )
    ++g_MultiplayerOpponentListScrollOffset;
  return MultiplayerSetup_RedrawOpponentNameList();
}
// 5441DC: using guessed type int dword_5441DC;

//----- (004494E0) --------------------------------------------------------
int  PlayGameMenu_HandleScrollButtonRelease(int a1)
{
  UIWidget_PlayPressedReleaseAnimation(a1);
  if ( g_MultiplayerOpponentListScrollOffset )
    --g_MultiplayerOpponentListScrollOffset;
  return MultiplayerSetup_RedrawOpponentNameList();
}
// 5441DC: using guessed type int dword_5441DC;

//----- (00449C30) --------------------------------------------------------
void  Options_ApplyMainMenuSliders(int a1, DWORD a2)
{
  g_OptionsMainMenuMusicVolumeRaw = ((unsigned __int16)(((_WORD)g_Options_BrightnessSliderValue << 7)
                                  - (__CFSHL__(g_Options_BrightnessSliderValue << 7 >> 31, 8)
                                   + ((unsigned __int16)(g_Options_BrightnessSliderValue << 7 >> 31) << 8))) >> 8)
              - 64;
  g_OptionsMainMenuSoundVolumeRaw = (unsigned __int16)(16 * g_Options_MouseSpeedSliderValue
                                 - (__CFSHL__((16 * g_Options_MouseSpeedSliderValue) >> 31, 8)
                                  + ((unsigned __int16)((16 * g_Options_MouseSpeedSliderValue) >> 31) << 8))) >> 8;
  Options_ApplyRecordSettings((int)&g_OptionsConfigRecordBase, a1, a2);
}
// 51860C: using guessed type int dword_51860C;
// 518654: using guessed type int dword_518654;
// 5188B0: using guessed type int dword_5188B0;
// 5188C9: using guessed type char byte_5188C9;
// 5188CA: using guessed type char byte_5188CA;

//----- (00449C80) --------------------------------------------------------
int  PlayGameMenu_HandleCloseButton(int a1)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_PlayGameMenuExitRequested = v3;
  return result;
}
// 449C8B: variable 'v3' is possibly undefined
// 543D78: using guessed type int g_PlayGameMenuExitRequested;

//----- (00449CA0) --------------------------------------------------------
unsigned __int16 * Options_InitMainMenuSlidersAndWidgets(int a1, int a2, DWORD a3)
{
  int v4; // ecx

  UIWidget_PlayPressedReleaseAnimation(a1);
  if ( (*(_BYTE *)(v4 - 98) & 2) == 0 )
  {
    *(_DWORD *)(v4 - 98) = 2;
    UIWidget_RefreshActionButtonState(v4 - 106, v4);
  }
  if ( (*(_BYTE *)(v4 - 151) & 2) == 0 )
  {
    *(_DWORD *)(v4 - 151) = 2;
    UIWidget_RefreshActionButtonState(v4 - 159, v4);
  }
  if ( (*(_BYTE *)(v4 - 204) & 2) == 0 )
  {
    *(_DWORD *)(v4 - 204) = 2;
    UIWidget_RefreshActionButtonState(v4 - 212, v4);
  }
  if ( (*(_BYTE *)(v4 - 257) & 1) == 0 )
  {
    *(_DWORD *)(v4 - 257) = 1;
    UIWidget_RefreshActionButtonState(v4 - 265, v4);
  }
  g_Options_BrightnessSliderValue = 128;
  g_Options_ScrollSpeedSliderValue = 128;
  g_Options_MouseSpeedSliderValue = 128;
  return Options_DrawAllSliderThumbs(g_OptionsMenuSliderThumbPositions, a2, a3);
}
// 449CA9: variable 'v4' is possibly undefined
// 518600: using guessed type unsigned __int16 word_518600[6];
// 51860C: using guessed type int dword_51860C;
// 518630: using guessed type int dword_518630;
// 518654: using guessed type int dword_518654;

//----- (00449D60) --------------------------------------------------------
BOOL  Options_ToggleCheckboxMainMenu(int widgetRecord)
{
  char toggledState; // dl

  toggledState = *(_BYTE *)(widgetRecord + 8) ^ 1;
  *(_BYTE *)(widgetRecord + 8) = toggledState;
  *(_BYTE *)(widgetRecord + 8) = toggledState ^ 2;
  Audio_PlayButtonSound(*(char **)(widgetRecord + 49));
  return Render_Begin((int)g_RenderState, 0);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044A110) --------------------------------------------------------
int  LoadMenu_HandleSlotConfirmButtonRelease(int a1, DWORD a2)
{
  int result; // eax

  if ( a1 )
    UIWidget_PlayPressedReleaseAnimation(a1);
  result = SaveSlot_HasDataFile(g_LoadMenuSelectedSlotIndex, a2);
  if ( result )
  {
    g_PlayGameMenuLaunchGameFlag = 1;
    g_PlayGameMenuExitRequested = 1;
  }
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;
// 5441E0: using guessed type int dword_5441E0;

//----- (0044A140) --------------------------------------------------------
void * LoadMenu_RedrawSaveSlotRow(int slotRow, DWORD a2)
{
  int rowTopY; // edi
  int rowSpriteId; // eax
  char *row_label; // eax
  void *result; // eax
  void *previousRenderDevice; // [esp+14h] [ebp-20h]
  int cursorOverlayPresented; // [esp+18h] [ebp-1Ch]

  previousRenderDevice = g_RenderDevice;
  row_label = (char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes(20);
  if ( !row_label )
    return previousRenderDevice;
  SaveSlot_LoadLabelOrPlaceholder(slotRow, row_label, a2);
  cursorOverlayPresented = g_CursorOverlayPresented;
  g_RenderDevice = &g_MainRenderDevice;
  rowTopY = (unsigned __int16)(22 * slotRow + 155);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xF4u, 0x1A4u, rowTopY, 22 * slotRow + 175);
  Render_FillRect((_DWORD *)g_PrimaryRenderSurface, 0, (unsigned __int16)rowTopY, 244, 0x1A4u, 22 * slotRow + 175, 0xF4u, rowTopY);
  if ( slotRow == g_LoadMenuSelectedSlotIndex )
    rowSpriteId = 18;
  else
    rowSpriteId = 21;
  Render_ReleaseSurface(rowSpriteId, (unsigned __int16)(22 * slotRow + 175));
  UI_DrawTextFmt(rowTopY, 244, 410, 22 * slotRow + 155, 3, (int)(uintptr_t)row_label);
  if ( cursorOverlayPresented )
    Render_Present((int)g_RenderState);
  Compat_FreeLow32Bytes((int)(uintptr_t)row_label);
  result = previousRenderDevice;
  g_RenderDevice = previousRenderDevice;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5441E0: using guessed type int dword_5441E0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (0044A510) --------------------------------------------------------
int  Options_DrawSliderThumb(unsigned __int16 *sliderRecord, char a2, DWORD a3)
{
  int v4; // ecx
  int previousResourceHandle; // edi
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v9; // ecx
  __int16 v10; // ax
  int SpriteForChar; // eax
  int result; // eax
  __int16 thumbTravel16; // bx
  unsigned __int16 v14; // ax
  unsigned __int16 v15; // [esp+10h] [ebp-2Ch]
  unsigned __int16 v16; // [esp+10h] [ebp-2Ch]
  unsigned __int16 v17; // [esp+14h] [ebp-28h]
  unsigned __int16 v18; // [esp+18h] [ebp-24h]
  void *previousRenderDevice; // [esp+1Ch] [ebp-20h]
  __int16 thumbTravel; // [esp+20h] [ebp-1Ch]

  Render_Pump();
  previousResourceHandle = Render_SetResourceHandle((int)&g_MainRenderDevice, 0);
  previousRenderDevice = g_RenderDevice;
  if ( *((_DWORD *)sliderRecord + 8) )
  {
    v18 = sliderRecord[4];
    v17 = *sliderRecord;
    v16 = DLX_GetSpriteWidth(**((_DWORD **)sliderRecord + 5), sliderRecord[12]) - 1;
    thumbTravel16 = sliderRecord[2] - *sliderRecord;
    v14 = thumbTravel16 + DLX_GetSpriteHeight(**((_DWORD **)sliderRecord + 5), sliderRecord[12]) - 1;
    Render_FillRect(*((_DWORD **)sliderRecord + 8), 0, 0, 0, v14, v16, v17, v18);
  }
  else
  {
    Surface = (_DWORD *)Mem_Alloc(188, v4, a2, a3);
    if ( Surface )
    {
      SpriteWidth = DLX_GetSpriteWidth(**((_DWORD **)sliderRecord + 5), sliderRecord[12]);
      thumbTravel = sliderRecord[2] - *sliderRecord;
      SpriteHeight = DLX_GetSpriteHeight(**((_DWORD **)sliderRecord + 5), sliderRecord[12]);
      Surface = Render_CreateSurface(v9, thumbTravel + SpriteHeight, SpriteWidth);
    }
    *((_DWORD *)sliderRecord + 8) = Surface;
    v15 = sliderRecord[4] + DLX_GetSpriteWidth(**((_DWORD **)sliderRecord + 5), sliderRecord[12]) - 1;
    v10 = DLX_GetSpriteHeight(**((_DWORD **)sliderRecord + 5), sliderRecord[12]);
    Render_FillRect(0, *((_DWORD **)sliderRecord + 8), sliderRecord[4], *sliderRecord, sliderRecord[2] + v10 - 1, v15, 0, 0);
  }
  g_RenderDevice = &g_MainRenderDevice;
  SpriteForChar = DLX_GetSpriteForChar(**((_DWORD **)sliderRecord + 5), *((_DWORD *)sliderRecord + 6));
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    *((_DWORD *)sliderRecord + 2),
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  g_RenderDevice = previousRenderDevice;
  Render_Present((int)g_RenderState);
  result = Render_SetResourceHandle((int)&g_MainRenderDevice, previousResourceHandle);
  if ( *((_DWORD *)sliderRecord + 7) )
    return (*((int (**)(void))sliderRecord + 7))();
  return result;
}
// 44A54B: variable 'v4' is possibly undefined
// 44A591: variable 'v9' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044A6D0) --------------------------------------------------------
unsigned int  Options_AnimateSliderThumbDrag(int sliderRecord)
{
  unsigned int result; // eax
  int v3; // eax
  int thumbLeftEdge; // esi
  int v5; // edx
  int v6; // esi
  int v7; // edi
  DWORD dragBaseValue; // ebp
  int v9; // edx
  int v10; // esi
  DWORD sliderMinX; // ebp
  unsigned __int16 SpriteHeight; // ax
  char v13; // cl

  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    v3 = *(_DWORD *)(sliderRecord + 12) * (*(_DWORD *)(sliderRecord + 4) - *(_DWORD *)sliderRecord);
    thumbLeftEdge = *(_DWORD *)sliderRecord + ((v3 - (__CFSHL__(v3 >> 31, 8) + (v3 >> 31 << 8))) >> 8);
    result = g_MouseCursorRawY >> g_CursorCoordShift;
    if ( g_MouseCursorRawY >> g_CursorCoordShift >= *(_DWORD *)(sliderRecord + 8) )
    {
      v5 = (unsigned __int16)DLX_GetSpriteWidth(**(_DWORD **)(sliderRecord + 20), *(_WORD *)(sliderRecord + 24)) + *(_DWORD *)(sliderRecord + 8);
      result = g_MouseCursorRawY >> g_CursorCoordShift;
      if ( g_MouseCursorRawY >> g_CursorCoordShift <= v5 )
      {
        if ( thumbLeftEdge > g_MouseCursorRawX >> g_CursorCoordShift
          || g_MouseCursorRawX >> g_CursorCoordShift > (unsigned __int16)DLX_GetSpriteHeight(
                                                               **(_DWORD **)(sliderRecord + 20),
                                                               *(_WORD *)(sliderRecord + 24))
                                         + thumbLeftEdge )
        {
          v10 = g_MouseCursorRawX;
          sliderMinX = *(_DWORD *)sliderRecord;
          SpriteHeight = DLX_GetSpriteHeight(**(_DWORD **)(sliderRecord + 20), *(_WORD *)(sliderRecord + 24));
          result = (int)(((v10 >> v13) - sliderMinX - SpriteHeight / 2) << 8) / (*(_DWORD *)(sliderRecord + 4) - *(_DWORD *)sliderRecord);
          if ( result <= 0x100 )
          {
            *(_DWORD *)(sliderRecord + 12) = result;
            return Options_DrawSliderThumb((unsigned __int16 *)sliderRecord, sliderRecord, sliderMinX);
          }
        }
        else
        {
          v6 = g_MouseCursorRawX >> g_CursorCoordShift;
          v7 = g_MouseCursorRawX >> g_CursorCoordShift;
          dragBaseValue = *(_DWORD *)(sliderRecord + 12);
          while ( 1 )
          {
            result = DD_IsFlipping((int)g_RenderState);
            if ( !result )
              break;
            DD_Pump((int)g_RenderState, sliderRecord);
            if ( v6 != g_MouseCursorRawX >> g_CursorCoordShift )
            {
              v9 = (((g_MouseCursorRawX >> g_CursorCoordShift) - v7) << 8) / (*(_DWORD *)(sliderRecord + 4) - *(_DWORD *)sliderRecord) + dragBaseValue;
              *(_DWORD *)(sliderRecord + 12) = v9;
              if ( v9 < 0 )
              {
                *(_DWORD *)(sliderRecord + 12) = 0;
              }
              else if ( v9 > 256 )
              {
                *(_DWORD *)(sliderRecord + 12) = 256;
              }
              Options_DrawSliderThumb((unsigned __int16 *)sliderRecord, sliderRecord, dragBaseValue);
              v6 = g_MouseCursorRawX >> g_CursorCoordShift;
            }
          }
        }
      }
    }
  }
  return result;
}
// 44A851: simplified comparisons for 'eax.4': <0 || >=101 became >=101u
// 44A836: variable 'v13' is possibly undefined
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 54512C: using guessed type char byte_54512C;

//----- (0044A880) --------------------------------------------------------
unsigned __int16 * Options_DrawAllSliderThumbs(unsigned __int16 *result, int a2, DWORD a3)
{
  unsigned __int16 *currentSlider; // edx
  int v4; // edx

  currentSlider = result;
  if ( *(_DWORD *)result != -1 )
  {
    do
    {
      result = (unsigned __int16 *)Options_DrawSliderThumb(currentSlider, a2, a3);
      a2 = *(_DWORD *)(v4 + 36);
      currentSlider = (unsigned __int16 *)(v4 + 36);
    }
    while ( a2 != -1 );
  }
  return result;
}
// 44A893: variable 'v4' is possibly undefined

//----- (0044A8B0) --------------------------------------------------------
_DWORD * Options_AnimateAllSliderThumbs(_DWORD *result)
{
  int currentSlider; // edx
  int v2; // edx
  int nextLink; // ebx

  currentSlider = (int)result;
  if ( *result != -1 )
  {
    do
    {
      result = (_DWORD *)Options_AnimateSliderThumbDrag(currentSlider);
      nextLink = *(_DWORD *)(v2 + 36);
      currentSlider = v2 + 36;
    }
    while ( nextLink != -1 );
  }
  return result;
}
// 44A8C3: variable 'v2' is possibly undefined

//----- (0044A8E0) --------------------------------------------------------
_DWORD * Options_DestroySliderThumbList(_DWORD *result)
{
  _DWORD *currentSlider; // ecx
  int thumbSurface; // esi
  int nextLink; // ebx

  currentSlider = result;
  if ( *result != -1 )
  {
    do
    {
      thumbSurface = currentSlider[8];
      if ( thumbSurface )
        result = (_DWORD *)(**(int (***)(void))(thumbSurface + 184))();
      currentSlider[8] = 0;
      nextLink = currentSlider[9];
      currentSlider += 9;
    }
    while ( nextLink != -1 );
  }
  return result;
}
// 44A905: variable 'v1' is possibly undefined

//----- (0044A920) --------------------------------------------------------
void  lodaOptionsCfg(DWORD a1)
{
  int configStream; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // [esp-4h] [ebp-Ch]
  int configStreamHandle; // [esp+0h] [ebp-8h] BYREF

  configStream = FileSystem_ResolveReadPath(aOptions_cfg, 0);
  configStreamHandle = configStream;
  if ( configStream )
  {
    v5 = v3;
    (*(void (**)(void))(*(_DWORD *)configStream + 20))();
    Compat_FileSystemQueryRelease(v4, &configStreamHandle);
    Options_ApplyRecordSettings((int)&g_OptionsConfigRecordBase, v5, a1);
  }
  else
  {
    Options_ApplyRecordSettings((int)&g_OptionsConfigRecordBase, v3, a1);
  }
}
// 44A93C: variable 'v3' is possibly undefined
// 44A960: variable 'v4' is possibly undefined
// 5188B0: using guessed type int dword_5188B0;

//----- (0044A980) --------------------------------------------------------
int  Options_SaveConfigToFile(int a1, DWORD a2)
{
  int fileHandle; // eax
  int v3; // ecx

  fileHandle = IO_FOpen(aOptions_cfg_0, (unsigned __int8 *)aWb_1, a1, a2);
  fwrite_(&g_OptionsConfigRecordBase, 27, fileHandle, 1);
  return fclose_(v3);
}
// 44A9AD: variable 'v3' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5188B0: using guessed type int dword_5188B0;

//----- (0044A9C0) --------------------------------------------------------
void  Options_ApplyRecordSettings(int configRecord, int a2, DWORD a3)
{
  int v5; // edx
  _DWORD paletteArray[260]; // [esp-40Ch] [ebp-410h] BYREF

  paletteArray[258] = a2;
  Palette_SetBrightnessOffset((int)&g_MainRenderDevice, *(char *)(configRecord + 26));
  _wcpp_4_copy_array__(paletteArray[0]);
  Palette_ApplyWithBrightnessOffset((int *)&g_MainRenderDevice, paletteArray);
  RenderState_SetMouseSpeed((int)g_RenderState, 8 * *(unsigned __int8 *)(configRecord + 25) + 20, a3);
  if ( (int *)configRecord == &g_OptionsConfigRecordBase )
  {
    if ( *(_DWORD *)(configRecord + 16) )
      Audio_SetMusicActiveFlag();
    else
      Audio_ClearMusicActiveFlag();
  }
  else if ( *(_DWORD *)(configRecord + 16) )
  {
    Audio_StartMainMusicIfStopped(v5, a3);
  }
  else
  {
    Audio_StopMainMusicIfPlaying();
  }
  if ( *(_DWORD *)(configRecord + 20) )
    Audio_EnableUnitSounds();
  else
    Audio_DisableUnitSounds();
}
// 44AA23: variable 'v5' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 5188B0: using guessed type int dword_5188B0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044AD60) --------------------------------------------------------
char  PlayerRuntimeState_ResetDefaults(uintptr_t playerState)
{
  uintptr_t playerStateBase; // ecx
  uintptr_t queenSlotLoopEnd; // edx

  playerStateBase = playerState;
  *(_DWORD *)(playerState + PLAYER_MINIMAP_VISIBLE_OFFSET) = 0;
  *(_DWORD *)(playerState + 43) = -1;
  *(_DWORD *)(playerState + 35) = 1;
  *(_BYTE *)(playerState + 47) = 1;
  *(_BYTE *)(playerState + 48) = 1;
  *(_DWORD *)(playerState + PLAYER_RELIGION_FLAG_OFFSET) = 1;
  *(_DWORD *)(playerState + PLAYER_IS_HUMAN_OFFSET) = 1;
  *(_DWORD *)(playerState + PLAYER_AI_INTELLIGENCE_OFFSET) = 0;
  *(_DWORD *)playerState = 0;
  *(_WORD *)(playerState + 1417) = 0;
  queenSlotLoopEnd = playerState + 60;
  *(_BYTE *)(playerState + PLAYER_QUEEN_RELATIONSHIP_STATE_OFFSET) = 0;
  do
  {
    playerState += 6;
    *(_BYTE *)(playerState + 1351) = -1;
  }
  while ( playerState != queenSlotLoopEnd );
  memset((void *)(playerStateBase + PLAYER_REVEALED_TILES_OFFSET), 0, 0x514u);
  strcpy((char *)(playerStateBase + PLAYER_DISPLAY_NAME_OFFSET), aDoc);
  return 0;
}

//----- (0044AE10) --------------------------------------------------------
char  Game_ResetPlayerRuntimeStateByIndex(int playerIndex)
{
  return PlayerRuntimeState_ResetDefaults(PLAYER_RUNTIME_STATE(playerIndex));
}
// 5202E4: using guessed type int gameData;

//----- (0044AE90) --------------------------------------------------------
int  Map_LoadFromFile(uintptr_t a1)
{
  int v3; // rax
  __int16 *tileScratchBuffer; // ebp
  char *v6; // esi
  char *v7; // edi
  char v8; // al
  char v9; // al
  int v10; // edi
  __int16 *v11; // ebx
  int i; // ecx
  __int16 v13; // ax
  __int16 *v14; // ebp
  int v15; // edi
  __int16 *v16; // ebx
  int j; // ecx
  __int16 v18; // ax
  __int16 *v19; // ebp
  int v20; // edi
  __int16 *v21; // ebx
  int k; // ecx
  int v23; // eax
  _BYTE *v24; // edi
  int v25; // esi
  _BYTE *v26; // ebx
  int m; // ecx
  int v30; // edx
  int mapWidthTiles; // eax
  int mapHeightTiles; // eax
  int n; // edx
  int v35; // eax
  int ii; // edx
  int jj; // ecx
  int kk; // eax
  int v39; // ebp
  int v40; // edi
  int v41; // ecx
  int v42; // ebx
  int v43; // edi
  int result; // eax
  char mapPathBuffer[100]; // [esp+0h] [ebp-90h] BYREF
  int readQueryHandle; // [esp+64h] [ebp-2Ch] BYREF
  _BYTE *trapScratchBuffer; // [esp+68h] [ebp-28h]
  uintptr_t mapFileName; // [esp+6Ch] [ebp-24h]
  __int16 *layerScratchBuffer; // [esp+70h] [ebp-20h]
  int v50; // [esp+74h] [ebp-1Ch]

  mapFileName = a1;
  memset((void *)(uintptr_t)(unsigned int)gameData, 0, 0x8F29Eu);
  v3 = (int)nmalloc_(0x13880, 1);
  tileScratchBuffer = (__int16 *)(uintptr_t)(unsigned int)v3;
  if ( !tileScratchBuffer )
    return 0;
  strcpy(mapPathBuffer, aMapsDirectory);
  layerScratchBuffer = (__int16 *)(uintptr_t)(unsigned int)v3;
  v6 = (char *)mapFileName;
  trapScratchBuffer = (_BYTE *)(uintptr_t)(unsigned int)v3;
  v7 = &mapPathBuffer[strlen(mapPathBuffer)];
  do
  {
    v8 = *v6;
    *v7 = *v6;
    if ( !v8 )
      break;
    v9 = v6[1];
    v6 += 2;
    v7[1] = v9;
    v7 += 2;
  }
  while ( v9 );
  readQueryHandle = FileSystem_ResolveReadPath(mapPathBuffer, 1);
  if ( !readQueryHandle )
  {
    Compat_FreeLow32Bytes(v3);
    return 0;
  }
  v10 = 0;
  Compat_QueryRead(readQueryHandle, tileScratchBuffer, 0x13880);
  do
  {
    v11 = tileScratchBuffer;
    for ( i = 0; i != 1400; *(_WORD *)(i + v10 + gameData - 14) = v13 )
    {
      i += 14;
      v13 = *v11++;
    }
    v10 += 1400;
    tileScratchBuffer += 200;
  }
  while ( v10 != 140000 );
  v14 = layerScratchBuffer;
  v15 = 0;
  Compat_QueryRead(readQueryHandle, layerScratchBuffer, 0x13880);
  do
  {
    v16 = v14;
    for ( j = 0; j != 1400; *(_WORD *)(j + v15 + gameData - 12) = v18 )
    {
      j += 14;
      v18 = *v16++;
    }
    v15 += 1400;
    v14 += 200;
  }
  while ( v15 != 140000 );
  v19 = layerScratchBuffer;
  v20 = 0;
  Compat_QueryRead(readQueryHandle, layerScratchBuffer, 0x13880);
  do
  {
    v21 = v19;
    for ( k = 0; k != 1400; k += 14 )
    {
      ++v21;
      v23 = v20 + gameData + k;
      *(_WORD *)(v23 + 4) = *(v21 - 1);
    }
    v20 += 1400;
    v19 += 200;
  }
  while ( v20 != 140000 );
  Rules_ResetEngineOnLoad();
  v24 = trapScratchBuffer;
  v25 = 0;
  Compat_QueryRead(readQueryHandle, trapScratchBuffer, 0x9C40);
  do
  {
    v26 = v24;
    for ( m = 0; m < 100; ++m )
    {
      if ( *v26 )
        Rules_LogTrapFact(v25, m);
      ++v26;
    }
    ++v25;
    v24 += 200;
  }
  while ( v25 < 100 );
  Compat_QueryRead(readQueryHandle, (void *)(uintptr_t)(unsigned int)(gameData + MAP_THEME_INDEX_OFFSET), 1);
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &readQueryHandle);
  Compat_FreeLow32Bytes(v3);
  v30 = 0;
  mapWidthTiles = 0;
  do
  {
    if ( *(unsigned __int16 *)(gameData + v30) == 0xFFFF )
      break;
    v30 += 1400;
    ++mapWidthTiles;
  }
  while ( v30 < 140000 );
  MAP_WIDTH_TILES = mapWidthTiles;
  mapHeightTiles = 0;
  for ( n = 0; n < 1400; n += 14 )
  {
    if ( *(unsigned __int16 *)(gameData + n) == 0xFFFF )
      break;
    ++mapHeightTiles;
  }
  MAP_HEIGHT_TILES = mapHeightTiles;
  Port_FindAndInit();
  Rules_RebuildTempleFacts();
  Rules_RebuildTreasureFacts();
  Rules_RebuildCastleSiteFacts();
  Render_CreateSprite();
  UI_ClearTileHighlight(0);
  *(_DWORD *)(gameData + 147147) = 1;
  *(_DWORD *)(gameData + 147151) = 0;
  *(_DWORD *)(gameData + 147155) = 0;
  *(_DWORD *)(gameData + 147159) = 0;
  MAP_VIEW_LEFT = 0;
  MAP_VIEW_TOP = 0;
  GAME_TURN_COUNTER = 1;
  v35 = gameData;
  VIEWED_PLAYER_INDEX = 0;
  TURN_OWNER_PLAYER_INDEX = VIEWED_PLAYER_INDEX;
  for ( ii = 0; ii != 362500; ii += 725 )
  {
    for ( jj = 0; jj != 310; *(_WORD *)(jj + ii + gameData + 147149) = -1 )
      jj += 31;
  }
  for ( kk = 0; kk != 46700; *(_BYTE *)(gameData + kk + 509211) = -1 )
    kk += 467;
  v39 = 0;
  v50 = 0;
  do
  {
    v40 = v50;
    v41 = 0;
    v42 = 0;
    do
    {
      *(_WORD *)(v39 + gameData + v42 + TILE_MAP_OFFSET) = -1;
      ++v41;
      v42 += 2;
      *(_BYTE *)(v41 + v40 + gameData + 576373) = 0;
    }
    while ( v41 < 100 );
    v39 += 200;
    v50 += 100;
  }
  while ( v39 != 20000 );
  v43 = gameData + 147147;
  qmemcpy((void *)(gameData + 147147), &g_OptionsConfigRecordBase, 0x18u);
  v43 += 24;
  *(_WORD *)v43 = *((_WORD *)&g_OptionsConfigRecordBase + 12);
  *(_BYTE *)(v43 + 2) = *((_BYTE *)&g_OptionsConfigRecordBase + 26);
  ACTIVE_MISSION_INDEX = -1;
  result = gameData;
  *(_BYTE *)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
  return result;
}
// 44B059: variable 'm' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 5188B0: using guessed type int dword_5188B0;
// 5202E4: using guessed type int gameData;

//----- (0044B2F0) --------------------------------------------------------
char Scenario_SetupSirArthurRosterVariantA()
{
  int i; // edx
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char *v9; // esi
  char *v10; // edi
  char v11; // al
  char v12; // al
  char *v13; // esi
  char *v14; // edi
  char result; // al

  for ( i = 0; i < 5; Game_ResetPlayerRuntimeStateByIndex(i) )
    ;
  *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) = 1;
  *(_DWORD *)(gameData + 141447) = 1;
  *(_DWORD *)(gameData + 142870) = 1;
  *(_DWORD *)(gameData + 140051) = 0;
  *(_DWORD *)(gameData + 140051) = 0;
  *(_DWORD *)(gameData + 142897) = 0;
  PLAYER_MINIMAP_VISIBLE(0) = 1;
  v1 = aSirArthur;
  v2 = (char *)(gameData + 140028);
  do
  {
    v3 = *v1;
    *v2 = *v1;
    if ( !v3 )
      break;
    v4 = v1[1];
    v1 += 2;
    v2[1] = v4;
    v2 += 2;
  }
  while ( v4 );
  v5 = aLester;
  v6 = (char *)(gameData + 141451);
  do
  {
    v7 = *v5;
    *v6 = *v5;
    if ( !v7 )
      break;
    v8 = v5[1];
    v5 += 2;
    v6[1] = v8;
    v6 += 2;
  }
  while ( v8 );
  v9 = aComputer;
  v10 = (char *)(gameData + 142874);
  do
  {
    v11 = *v9;
    *v10 = *v9;
    if ( !v11 )
      break;
    v12 = v9[1];
    v9 += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  v13 = aTomek;
  v14 = (char *)(gameData + 144297);
  do
  {
    result = *v13;
    *v14 = *v13;
    if ( !result )
      break;
    result = v13[1];
    v13 += 2;
    v14[1] = result;
    v14 += 2;
  }
  while ( result );
  return result;
}
// 44B2F8: variable 'i' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044B430) --------------------------------------------------------
char Scenario_SetupSirArthurRosterVariantB()
{
  int i; // edx
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char *v9; // esi
  char *v10; // edi
  char v11; // al
  char v12; // al
  char *v13; // esi
  char *v14; // edi
  char result; // al

  for ( i = 0; i < 5; Game_ResetPlayerRuntimeStateByIndex(i) )
    ;
  *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) = 1;
  *(_DWORD *)(gameData + 142870) = 1;
  *(_DWORD *)(gameData + 140051) = 1;
  *(_DWORD *)(gameData + 142897) = 0;
  PLAYER_MINIMAP_VISIBLE(0) = 1;
  v1 = aSirArthur_0;
  v2 = (char *)(gameData + 140028);
  do
  {
    v3 = *v1;
    *v2 = *v1;
    if ( !v3 )
      break;
    v4 = v1[1];
    v1 += 2;
    v2[1] = v4;
    v2 += 2;
  }
  while ( v4 );
  v5 = aLester_0;
  v6 = (char *)(gameData + 141451);
  do
  {
    v7 = *v5;
    *v6 = *v5;
    if ( !v7 )
      break;
    v8 = v5[1];
    v5 += 2;
    v6[1] = v8;
    v6 += 2;
  }
  while ( v8 );
  v9 = aComputer_0;
  v10 = (char *)(gameData + 142874);
  do
  {
    v11 = *v9;
    *v10 = *v9;
    if ( !v11 )
      break;
    v12 = v9[1];
    v9 += 2;
    v10[1] = v12;
    v10 += 2;
  }
  while ( v12 );
  v13 = aTomek_0;
  v14 = (char *)(gameData + 144297);
  do
  {
    result = *v13;
    *v14 = *v13;
    if ( !result )
      break;
    result = v13[1];
    v13 += 2;
    v14[1] = result;
    v14 += 2;
  }
  while ( result );
  return result;
}
// 44B438: variable 'i' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044B550) --------------------------------------------------------
_DWORD * Scenario_SeedCantbellyAndKopegonCastles(int this, DWORD a2, double a3)
{
  int v3; // ecx
  int v4; // eax
  int v5; // edx
  char v6; // bl
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  _DWORD *result; // eax
  int v19; // edx

  Unit_Create(UNIT_TYPE_BUILDER, 0, 5, 0, 4);
  Unit_Create(UNIT_TYPE_RAM, 0, 5, 0, 5);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557384), *(unsigned __int16 *)(gameData + 557382), 0, a2, a3);
  Building_New(1, *(unsigned __int16 *)(gameData + 557382), a3, aCantbelly_3, 1);
  *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
  Unit_UpdatePerTurn(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET, v3);
  *(_DWORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510112) = 1000;
  v4 = gameData;
  v5 = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  v6 = *(_BYTE *)(v5 + gameData + 510118) & 0xF8;
  *(_BYTE *)(v5 + gameData + 510118) = v6;
  *(_BYTE *)(v5 + v4 + 510118) = v6 | 2;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 2u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 1u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 8u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 4u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 0x10u;
  *(_DWORD *)(gameData + 140063) = 0;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510119) = 33;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510120) = 2;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510125) = 34;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510126) = 4;
  Building_LogBuiltCastleFacts(
    (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET));
  Unit_Create(UNIT_TYPE_BUILDER, 0, v7, 0, 6);
  Unit_Create(UNIT_TYPE_FLY, 0, 6, 0, 6);
  Unit_Create(UNIT_TYPE_ARCHER, 0, 7, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  Unit_Create(UNIT_TYPE_CYCLOP, 0, v8, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  Unit_Create(UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, 0, v9, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  Unit_Create(UNIT_TYPE_HEAVY_SPEARMAN, 0, v10, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  *(_BYTE *)(gameData + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 557586) + 147189) = 1;
  Unit_Create(UNIT_TYPE_PEGASUS, 2, 10, 0, 7);
  Unit_Create(UNIT_TYPE_WINGER, 0, 10, 0, 8);
  Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, 0, 5, 0, 45);
  Unit_Create(UNIT_TYPE_BUILDER, 0, 5, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, 0, 5, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_EAGLE, 0, v11, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_RAM, 0, v12, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v13, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v14, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v15, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v16, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v17, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Building_New(0, *(unsigned __int16 *)(gameData + 557464), a3, aKopegon, 1);
  *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557464) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
  Unit_UpdatePerTurn(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557464) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET, this);
  result = Building_LogBuiltCastleFacts(
             (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557464) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET));
  g_CurrentPlayerIndex = v19;
  return result;
}
// 44B611: variable 'v3' is possibly undefined
// 44B7E9: variable 'v7' is possibly undefined
// 44B849: variable 'v8' is possibly undefined
// 44B87F: variable 'v9' is possibly undefined
// 44B8B5: variable 'v10' is possibly undefined
// 44B9C6: variable 'v11' is possibly undefined
// 44B9FC: variable 'v12' is possibly undefined
// 44BA32: variable 'v13' is possibly undefined
// 44BA68: variable 'v14' is possibly undefined
// 44BA9E: variable 'v15' is possibly undefined
// 44BAD4: variable 'v16' is possibly undefined
// 44BB0A: variable 'v17' is possibly undefined
// 44BBCF: variable 'v19' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044C2A0) --------------------------------------------------------
signed int Game_InitPlayerViewState()
{
  int playerIndex; // edi
  int v1; // ebp
  int castleIndex; // edx
  int castleRecordOffset; // eax
  int v4; // eax
  int v5; // eax
  int humanPlayerIndex; // ecx
  int humanPlayerOffset; // eax
  int activePlayerIndex; // edx
  signed int result; // eax

  playerIndex = 0;
  v1 = 0;
  do
  {
    if ( PLAYER_IS_ACTIVE(playerIndex) )
    {
      castleIndex = 0;
      castleRecordOffset = 0;
      while ( *(unsigned __int8 *)(gameData + castleRecordOffset + 509676) != playerIndex )
      {
        castleRecordOffset += BUILDING_RECORD_SIZE;
        ++castleIndex;
        if ( castleRecordOffset >= 46700 )
          goto LABEL_13;
      }
      PLAYER_CAMERA_LEFT(playerIndex) = *(unsigned __int8 *)(gameData + castleRecordOffset + BUILDING_TABLE_OFFSET) - 4;
      if ( PLAYER_CAMERA_LEFT(playerIndex) < 0 )
        PLAYER_CAMERA_LEFT(playerIndex) = 0;
      v4 = MAP_WIDTH_TILES - 9;
      if ( v4 < PLAYER_CAMERA_LEFT(playerIndex) )
        PLAYER_CAMERA_LEFT(playerIndex) = v4;
      PLAYER_CAMERA_TOP(playerIndex) = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * castleIndex + gameData + 509675) - 3;
      if ( PLAYER_CAMERA_TOP(playerIndex) < 0 )
        PLAYER_CAMERA_TOP(playerIndex) = 0;
      v5 = MAP_HEIGHT_TILES - 7;
      if ( v5 < PLAYER_CAMERA_TOP(playerIndex) )
        PLAYER_CAMERA_TOP(playerIndex) = v5;
    }
LABEL_13:
    ++playerIndex;
    v1 += 1423;
  }
  while ( playerIndex < 5 );
  humanPlayerIndex = 0;
  VIEWED_PLAYER_INDEX = 0;
  humanPlayerOffset = 0;
  while ( !PLAYER_IS_ACTIVE(humanPlayerIndex) || !PLAYER_HAS_HUMAN_CONTROLLER(humanPlayerIndex) )
  {
    humanPlayerOffset += 1423;
    ++humanPlayerIndex;
    if ( humanPlayerOffset >= 7115 )
      goto LABEL_18;
  }
  VIEWED_PLAYER_INDEX = humanPlayerIndex;
LABEL_18:
  activePlayerIndex = 0;
  result = 0;
  while ( !PLAYER_IS_ACTIVE(activePlayerIndex) )
  {
    result += 1423;
    ++activePlayerIndex;
    if ( result >= 7115 )
      return result;
  }
  g_CurrentPlayerIndex = activePlayerIndex;
  TURN_OWNER_PLAYER_INDEX = activePlayerIndex;
  return result;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044C400) --------------------------------------------------------
signed int  SaveSlot_LoadReservedSlot10(DWORD a1, double a2)
{
  return SaveSlot_LoadGame(10, a1, a2);
}

//----- (0044C410) --------------------------------------------------------
signed int  Scenario_LoadAllAiMultiplayerMapAndInitView(int mapIndex)
{
  int player_index; // ecx
  _BYTE player_states[PLAYER_DATA_STRIDE * 5]; // [esp+0h] [ebp-1BE4h] BYREF

  for ( player_index = 0; player_index < 5; ++player_index )
    PlayerRuntimeState_ResetDefaults((uintptr_t)&player_states[PLAYER_DATA_STRIDE * player_index]);
  for ( player_index = 0; player_index < 5; ++player_index )
  {
    *(_DWORD *)&player_states[PLAYER_DATA_STRIDE * player_index] = 1;
    *(_DWORD *)&player_states[PLAYER_DATA_STRIDE * player_index + PLAYER_IS_HUMAN_OFFSET] = 0;
  }
  *(_DWORD *)&player_states[PLAYER_DATA_STRIDE + PLAYER_AI_INTELLIGENCE_OFFSET] = 2;
  *(_DWORD *)&player_states[2 * PLAYER_DATA_STRIDE + PLAYER_AI_INTELLIGENCE_OFFSET] = 2;
  *(_DWORD *)&player_states[PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  *(_DWORD *)&player_states[PLAYER_DATA_STRIDE + PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  *(_DWORD *)&player_states[2 * PLAYER_DATA_STRIDE + PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  *(_DWORD *)&player_states[3 * PLAYER_DATA_STRIDE + PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  Scenario_LoadMultiplayerMapAndSeedPlayers(mapIndex, (uintptr_t)player_states);
  return Game_InitPlayerViewState();
}

//----- (0044C7F0) --------------------------------------------------------
DWORD  Battle_RunPresetScenarioByIndex(int scenarioIndex, DWORD a2, double a3)
{
  int unitStackTableBase; // ebx
  int attackerStackIndex; // edx
  __int16 *defenderStackPtr; // esi
  int v6; // eax
  DWORD result; // eax
  int v8; // ecx
  int v9; // eax
  char v10; // dl
  int v11; // ecx
  int v12; // eax
  char v13; // bl
  int v14; // ecx
  int v15; // eax
  char v16; // dl
  int v17; // ecx
  int v18; // eax
  char v19; // bl

  switch ( scenarioIndex )
  {
    case 0:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 0;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 1:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 2:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 1;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_ARCHER, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 3:
      *(_WORD *)gameData = 4;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 4;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 0;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 4:
      *(_WORD *)gameData = 9;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 9;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CROSSBOWER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 5:
      *(_WORD *)gameData = 21;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 21;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 1;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_SPEARMAN, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CYCLOP, UNIT_TYPE_SKELETON, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 6:
      *(_WORD *)gameData = 9;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 9;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 0;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_SKELETON, UNIT_TYPE_WORM, UNIT_TYPE_KNIGHTS, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_SKELETON, UNIT_TYPE_WORM, UNIT_TYPE_KNIGHTS, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 7:
      *(_WORD *)gameData = 4;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 4;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_RAM, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createCastle(a3, 1, 0, 1, 2, aZamek, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CYCLOP, -1);
      return Battle_RunTacticalCombat(
               (__int16 *)(UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET) + gameData + UNIT_STACK_TABLE_OFFSET),
               0,
               0,
               (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 556574) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET),
               a2,
               0);
    case 8:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 1;
      createUnit(a3, 0, 0, 1, UNIT_TYPE_CANNON, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a3, 1, 0, 0, 2, aZamek_0, UNIT_TYPE_CANNON, UNIT_TYPE_WIZARD, UNIT_TYPE_LIGHT_CAVALRY, -1);
      return Battle_RunTacticalCombat(
               (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET)),
               0,
               0,
               (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 556574) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET),
               a2,
               0);
    case 9:
      *(_WORD *)gameData = 28;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 28;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_GHOST, UNIT_TYPE_WIZARD, UNIT_TYPE_WINGER, -1);
      v8 = gameData;
      v9 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      v10 = *(_BYTE *)(gameData + v9 + 147285) & 0xFC;
      *(_BYTE *)(gameData + v9 + 147285) = v10;
      *(_BYTE *)(v8 + v9 + 147285) = v10 | 1;
      createUnit(a3, 1, 0, 1, UNIT_TYPE_DRAGON, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      v11 = gameData;
      v12 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574);
      v13 = *(_BYTE *)(gameData + v12 + 147223) & 0xFC;
      *(_BYTE *)(gameData + v12 + 147223) = v13;
      *(_BYTE *)(v11 + v12 + 147223) = v13 | 1;
      v14 = gameData;
      v15 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574);
      v16 = *(_BYTE *)(gameData + v15 + 147316) & 0xFC;
      *(_BYTE *)(gameData + v15 + 147316) = v16;
      *(_BYTE *)(v14 + v15 + 147316) = v16 | 1;
      v17 = gameData;
      v18 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574);
      v19 = *(_BYTE *)(gameData + v18 + 147378) & 0xFC;
      *(_BYTE *)(gameData + v18 + 147378) = v19;
      *(_BYTE *)(v17 + v18 + 147378) = v19 | 1;
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)attackerStackIndex;
LABEL_3:
      result = Battle_RunTacticalCombat((__int16 *)(unitStackTableBase + 5 * (attackerStackIndex + v6)), defenderStackPtr, 0, 0, a2, 0);
      break;
    default:
      result = 1;
      break;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0044D250) --------------------------------------------------------
signed int  Scenario_LoadMultiplayerMapAndSeedPlayers(int mapIndex, uintptr_t playerStatesSource)
{
  double v4; // st7
  int playerIndex; // esi
  int v8; // eax
  DWORD startRowPlus1; // ebp
  int startColumnDoubled; // edi
  int v12; // edx
  int v13; // ecx
  int v14; // ebx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // ebx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // [esp-4h] [ebp-B4h]
  _BYTE mapPathBuffer[100]; // [esp+0h] [ebp-B0h] BYREF
  int v32; // [esp+64h] [ebp-4Ch]
  int religionToggle; // [esp+68h] [ebp-48h]
  unsigned int startPosTableIndex; // [esp+6Ch] [ebp-44h]
  int playerRecordOffset; // [esp+70h] [ebp-40h]
  int v36; // [esp+74h] [ebp-3Ch]
  int v37; // [esp+78h] [ebp-38h]
  int v38; // [esp+7Ch] [ebp-34h]
  int v39; // [esp+80h] [ebp-30h]
  int startColumn; // [esp+84h] [ebp-2Ch]
  int startRow; // [esp+88h] [ebp-28h]
  int v42; // [esp+8Ch] [ebp-24h]
  int v43; // [esp+90h] [ebp-20h]
  int v44; // [esp+94h] [ebp-1Ch]
  int v45; // [esp+98h] [ebp-18h]

  v4 = sprintf_(mapPathBuffer, "multi%d.map", mapIndex + 1);
  Map_LoadFromFile((uintptr_t)mapPathBuffer);
  qmemcpy((void *)(gameData + PLAYER_RUNTIME_STATE_OFFSET), (const void *)playerStatesSource, PLAYER_DATA_STRIDE * 5);
  MiniMap_CreateSurface((DWORD)playerStatesSource);
  religionToggle = 1;
  playerIndex = 0;
  playerRecordOffset = 0;
  startPosTableIndex = 40 * mapIndex;
  do
  {
    v8 = playerRecordOffset + gameData;
    if ( *(_DWORD *)(playerRecordOffset + gameData + PLAYER_RUNTIME_STATE_OFFSET) )
    {
      startRow = g_MultiplayerStartRows[startPosTableIndex / 4];
      startColumn = g_MultiplayerStartColumns[startPosTableIndex / 4];
      v44 = startColumn - 1;
      v36 = startColumn + 3;
      v39 = startRow + 2;
      v38 = startColumn + 2;
      v42 = 200 * startRow;
      startRowPlus1 = startRow + 1;
      v43 = 200 * (startRow + 2);
      v45 = 200 * (startRow + 1);
      startColumnDoubled = 2 * startColumn;
      if ( *(_DWORD *)(v8 + 140051) )
      {
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRow, 0, startColumn);
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Building_NewAt(startRow, startColumn, 2, *(unsigned __int16 *)(v42 + gameData + startColumnDoubled + TILE_MAP_OFFSET), v4, aCantbelly, 1);
        *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
        v12 = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
        *(_DWORD *)(v12 + gameData + 510112) += 50;
        Unit_UpdatePerTurn(
          BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET,
          v13);
        v14 = v38;
        Building_LogBuiltCastleFacts(
          (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE)
                            + gameData
                            + BUILDING_TABLE_OFFSET));
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, playerIndex, startRow, 0, v14);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v38);
        Unit_Create(UNIT_TYPE_ARCHER, playerIndex, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, playerIndex, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRowPlus1, 0, v36);
        Unit_Create(UNIT_TYPE_ARCHER, playerIndex, v39, 0, v36);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556380),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556380),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, v39, 0, v44);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
      }
      else
      {
        v30 = startColumn;
        *(_DWORD *)(v8 + 140063) = religionToggle;
        LOBYTE(religionToggle) = religionToggle ^ 1;
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRow, 0, v30);
        Unit_Create(UNIT_TYPE_PIKEMAN, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_HEAVY_SPEARMAN, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Building_NewAt(startRow, startColumn, 2, *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + TILE_MAP_OFFSET), v4, aCantbelly_0, 1);
        *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
        v18 = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
        *(_DWORD *)(v18 + gameData + 510112) += 100;
        Unit_UpdatePerTurn(
          BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET,
          v19);
        v20 = v38;
        Building_LogBuiltCastleFacts(
          (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + v42 + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE)
                            + gameData
                            + BUILDING_TABLE_OFFSET));
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, playerIndex, startRow, 0, v20);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v38);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, playerIndex, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, playerIndex, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRowPlus1, 0, v36);
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, v39, 0, v36);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556380),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556380),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_ARCHER, playerIndex, v39, 0, v36);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v43 + gameData + 556380),
          *(unsigned __int16 *)(gameData + v45 + startColumnDoubled + 556380),
          0,
          startRowPlus1,
          v4);
        v32 = startRow - 1;
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRow - 1, 0, v44);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRow, 0, v44);
        v37 = 200 * v32;
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + 200 * v32 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PIKEMAN, playerIndex, startRow, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PIKEMAN, playerIndex, startRow, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRow, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRow, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRow, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, startRow, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        if ( *(int *)(playerRecordOffset + gameData + 140055) > 0 )
        {
          Unit_Create(UNIT_TYPE_PEASANT, playerIndex, v39, 0, v44);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_ARCHER, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_ARCHER, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
        }
      }
    }
    ++playerIndex;
    playerRecordOffset += PLAYER_DATA_STRIDE;
    startPosTableIndex += 8;
  }
  while ( playerIndex < 5 );
  Rules_LogMissionSetupInfo();
  return Game_InitPlayerViewState();
}
// 44D4E8: variable 'v13' is possibly undefined
// 44D536: variable 'v15' is possibly undefined
// 44D607: variable 'v16' is possibly undefined
// 44D6C1: variable 'v17' is possibly undefined
// 44DB7B: variable 'v19' is possibly undefined
// 44DBC9: variable 'v21' is possibly undefined
// 44DC49: variable 'v22' is possibly undefined
// 44DC9A: variable 'v23' is possibly undefined
// 44DD51: variable 'v24' is possibly undefined
// 44DE25: variable 'v25' is possibly undefined
// 44DE76: variable 'v26' is possibly undefined
// 44DEC4: variable 'v27' is possibly undefined
// 44DF15: variable 'v28' is possibly undefined
// 44DFB7: variable 'v29' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 518938: using guessed type int g_MultiplayerStartRows[];
// 51893C: using guessed type int g_MultiplayerStartColumns[];
// 5202E4: using guessed type int gameData;

//----- (0044E2A0) --------------------------------------------------------
char  Player_AssignRandomUniqueRulerNames(int a1, int *nameSlotPtrs)
{
  char result; // al
  int assignedCount; // ebp
  unsigned int candidateIndex; // ecx
  int v5; // edx
  int v6; // eax
  char *candidateNameChars; // esi
  char *destNameChars; // edi
  char v9; // al
  char v10; // al
  int v11; // ecx
  int usedNameHistory[5]; // [esp+0h] [ebp-30h] BYREF
  int nameCount; // [esp+14h] [ebp-1Ch]
  int *slotCursor; // [esp+18h] [ebp-18h]

  nameCount = a1;
  result = (char)nameSlotPtrs;
  assignedCount = 0;
  qmemcpy(usedNameHistory, &g_RulerNameHistorySeed, sizeof(usedNameHistory));
  if ( nameCount > 0 )
  {
    slotCursor = nameSlotPtrs;
    while ( 1 )
    {
      candidateIndex = Rng_RandRange(0, 38);
      v5 = 0;
      v6 = 0;
      if ( candidateIndex != usedNameHistory[0] )
      {
        do
        {
          ++v6;
          ++v5;
        }
        while ( v6 < 5 && candidateIndex != usedNameHistory[v6] );
      }
      if ( v5 == 5 )
      {
        candidateNameChars = g_RulerNameCandidatesTable[candidateIndex];
        destNameChars = (char *)*slotCursor;
        do
        {
          v9 = *candidateNameChars;
          *destNameChars = *candidateNameChars;
          if ( !v9 )
            break;
          v10 = candidateNameChars[1];
          candidateNameChars += 2;
          destNameChars[1] = v10;
          destNameChars += 2;
        }
        while ( v10 );
        result = Str_TitleCase((_BYTE *)*slotCursor, 5, candidateIndex);
        usedNameHistory[assignedCount++] = v11;
        ++slotCursor;
        if ( assignedCount >= nameCount )
          break;
      }
    }
  }
  return result;
}
// 44E32E: variable 'v11' is possibly undefined
// 518C58: using guessed type char *off_518C58[39];

//----- (0044E350) --------------------------------------------------------
BOOL  UI_RunHoverTooltipZones(__int16 *tooltipZoneTable)
{
  BOOL result; // eax
  int v2; // edx
  signed int zoneBottom; // ebp
  int v4; // ebx
  int v5; // edx
  int v6; // ecx
  int v7; // ebx
  int v8; // edi
  DWORD v9; // ebp
  int v10; // eax
  int v11; // ebx
  _DWORD *Surface; // eax
  int v13; // ecx
  int v14; // esi
  _DWORD *v15; // eax
  int v16; // ebp
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // edx
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int v29; // eax
  int v30; // edx
  int fadeOutStartTime; // [esp+0h] [ebp-4Ch]
  int v32; // [esp+4h] [ebp-48h]
  void *previousRenderDevice; // [esp+1Ch] [ebp-30h]
  int v35; // [esp+20h] [ebp-2Ch]
  int v36; // [esp+24h] [ebp-28h]
  int v37; // [esp+28h] [ebp-24h]
  int fadeStartTime; // [esp+34h] [ebp-18h]
  unsigned __int16 v39; // [esp+38h] [ebp-14h]
  unsigned __int16 v40; // [esp+3Ch] [ebp-10h]
  unsigned __int16 v41; // [esp+40h] [ebp-Ch]
  unsigned __int16 v42; // [esp+44h] [ebp-8h]

  previousRenderDevice = g_RenderDevice;
  result = DD_IsLost((int)g_RenderState);
  if ( result )
  {
    while ( 1 )
    {
      v2 = *tooltipZoneTable;
      if ( v2 == -1 )
        break;
      zoneBottom = tooltipZoneTable[3];
      if ( g_MouseCursorRawX >> g_CursorCoordShift < v2
        || g_MouseCursorRawY >> g_CursorCoordShift < tooltipZoneTable[1]
        || g_MouseCursorRawX >> g_CursorCoordShift > tooltipZoneTable[2]
        || g_MouseCursorRawY >> g_CursorCoordShift > zoneBottom
        || !*(_DWORD *)&tooltipZoneTable[2 * (unsigned __int8)g_LanguageIndex + 4] )
      {
        goto LABEL_4;
      }
      Render_ReleaseSurface(8, zoneBottom);
      v35 = g_MouseCursorRawY >> g_CursorCoordShift;
      v37 = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)&tooltipZoneTable[2 * (unsigned __int8)g_LanguageIndex + 4])
          + (g_MouseCursorRawX >> g_CursorCoordShift);
      v4 = g_MouseCursorRawY >> g_CursorCoordShift;
      v7 = UI_GetTextXOffset(g_ActiveTextSpriteSlot) + v4;
      v32 = v5;
      v36 = v7;
      if ( v5 + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12) > v37 )
        v37 = v5 + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12);
      v8 = *(_DWORD *)(g_ActiveCursorDescriptorPtr + 16);
      v9 = v7;
      if ( v35 + v8 > v7 )
        v36 = v35 + v8;
      if ( v37 > 639 )
      {
        v10 = v37 - 639;
        v6 = 639;
        LOWORD(v37) = 639;
        v32 = v5 - v10;
      }
      v11 = v36;
      if ( v36 > 479 )
      {
        LOWORD(v36) = 479;
        v35 -= v11 - 479;
      }
      Surface = (_DWORD *)Mem_Alloc(188, v6, v11, v9);
      if ( Surface )
      {
        LOWORD(v11) = v36 - v35 + 1;
        Surface = Render_CreateSurface((int)Surface, v37 - v32 + 1, v11);
      }
      v14 = (int)Surface;
      v15 = (_DWORD *)Mem_Alloc(188, v13, v11, v9);
      if ( v15 )
        v15 = Render_CreateSurface((int)v15, v37 - v32 + 1, v36 - v35 + 1);
      v16 = (int)v15;
      Render_FillRect(0, (_DWORD *)v14, (unsigned __int16)v35, (unsigned __int16)v32, v37, v36, 0, 0);
      Render_SaveBackbuffer((int)&g_MainRenderDevice);
      Render_Pump();
      Render_FillRect(0, (_DWORD *)v16, (unsigned __int16)v35, (unsigned __int16)v32, v37, v36, 0, 0);
      Render_Present((int)g_RenderState);
      g_RenderDevice = (_UNKNOWN *)v16;
      UI_DrawText(0, 0, *(_DWORD *)&tooltipZoneTable[2 * (unsigned __int8)g_LanguageIndex + 4]);
      fadeStartTime = Time_Now(v18, v17);
      v20 = 30;
      v42 = v37 - v32;
      v39 = v36 - v35;
      while ( Time_Now(v19, v20) < (unsigned int)(fadeStartTime + 30) )
      {
        v22 = Time_Now(fadeStartTime, v21);
        Render_BlendSurfaceRect(0, v14, 0, v16, 0, v42, v39, v32, v35, 255 * (v22 - v23) / 0x1Eu);
      }
      Render_FillRect((_DWORD *)v16, 0, 0, 0, v42, v39, v32, v35);
      Render_FlipRect((int)g_RenderState, 0);
      fadeOutStartTime = Time_Now(v25, v24);
      v26 = v32;
      v27 = v35;
      v41 = v37 - v32;
      v40 = v36 - v35;
      while ( Time_Now(v26, v27) < (unsigned int)(fadeOutStartTime + 30) )
      {
        v29 = Time_Now(v28, fadeOutStartTime);
        Render_BlendSurfaceRect(0, v16, 0, v14, 0, v41, v40, v32, v35, 255 * (v29 - v30) / 0x1Eu);
      }
      Render_FillRect((_DWORD *)v14, 0, 0, 0, v41, v40, v32, v35);
      if ( v14 )
        (**(void (***)(void))(v14 + 184))();
      if ( v16 )
      {
        (**(void (***)(void))(v16 + 184))();
        tooltipZoneTable += 10;
      }
      else
      {
LABEL_4:
        tooltipZoneTable += 10;
      }
    }
    result = (BOOL)previousRenderDevice;
    g_RenderDevice = previousRenderDevice;
  }
  return result;
}
// 44E456: variable 'v5' is possibly undefined
// 44E4D7: variable 'v6' is possibly undefined
// 44E50B: variable 'v13' is possibly undefined
// 44E5E4: variable 'v18' is possibly undefined
// 44E5E4: variable 'v17' is possibly undefined
// 44E612: variable 'v19' is possibly undefined
// 44E612: variable 'v20' is possibly undefined
// 44E61F: variable 'v21' is possibly undefined
// 44E624: variable 'v23' is possibly undefined
// 44E69D: variable 'v25' is possibly undefined
// 44E69D: variable 'v24' is possibly undefined
// 44E6CD: variable 'v26' is possibly undefined
// 44E6CD: variable 'v27' is possibly undefined
// 44E6DA: variable 'v28' is possibly undefined
// 44E6DF: variable 'v30' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520728: using guessed type int dword_520728;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (0044E7A0) --------------------------------------------------------
signed int  Prisoner_QueueCapturedUnit(
        char capturedUnitType,
        int a2,
        __int16 a3,
        int playerIndex,
        DWORD a5,
        __int16 a6)
{
  int playerRecordOffset; // ebx
  int prisonerQueueBase; // ebx
  int v9; // edx
  signed int result; // eax
  char capturedOwner; // [esp+4h] [ebp-8h]

  capturedOwner = a2;
  playerRecordOffset = PLAYER_DATA_STRIDE * playerIndex;
  Debug_Log(a2, playerRecordOffset, a5, (int)aPrisoner_addto);
  prisonerQueueBase = gameData + PLAYER_RUNTIME_STATE_OFFSET + playerRecordOffset;
  v9 = prisonerQueueBase;
  result = 0;
  while ( *(char *)(v9 + 1357) != -1 )
  {
    ++result;
    v9 += 6;
    if ( result >= 10 )
    {
      if ( result == 10 )
        return result;
      break;
    }
  }
  result *= 3;
  *(_WORD *)(prisonerQueueBase + 2 * result + 1359) = a3;
  *(_BYTE *)(prisonerQueueBase + 2 * result + 1357) = capturedUnitType;
  *(_BYTE *)(prisonerQueueBase + 2 * result + 1358) = capturedOwner;
  *(_WORD *)(prisonerQueueBase + 2 * result + 1361) = a6;
  return result;
}
// 44E7EC: conditional instruction was optimized away because eax.4<A
// 5202E4: using guessed type int gameData;

//----- (0044E850) --------------------------------------------------------
signed int  Building_FindFreePrisonerSlot(int buildingRecord)
{
  signed int result; // eax

  result = 0;
  while ( BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(buildingRecord, result)) != -1 )
  {
    ++result;
    if ( result >= BUILDING_PRISONER_SLOT_COUNT )
      return -1;
  }
  return result;
}

//----- (0044E880) --------------------------------------------------------
int  BuildingPrisoner_RecalculateRansomValue(int prisonerRecord)
{
  int basePower; // ebx
  int v2; // edx
  unsigned int ransomValue; // eax
  int v4; // ecx
  int result; // eax
  int v6; // eax

  basePower = AI_TickNationPostTurn(*(unsigned __int8 *)(prisonerRecord + 1));
  ransomValue = basePower * Rng_RandRange(7, v2) / 0x64;
  *(_WORD *)(v4 + 4) = ransomValue;
  if ( !(_WORD)ransomValue )
  {
    v6 = AI_TickNationPostTurn(g_CurrentPlayerIndex);
    *(_WORD *)(v4 + 4) = 13 * v6 / 10;
  }
  result = 10 * (*(unsigned __int16 *)(v4 + 4) / 10);
  *(_WORD *)(v4 + 4) = result;
  return result;
}
// 44E89B: variable 'v2' is possibly undefined
// 44E8AC: variable 'v4' is possibly undefined
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044E900) --------------------------------------------------------
signed int  Prisoner_SetInCastles(int a1, char a2, DWORD a3)
{
  int queued_index; // ecx
  signed int result; // eax
  int queued_prisoner; // edx
  int building_index; // esi
  int best_building_index; // edi
  int building; // ebx
  int best_distance; // [esp+10h] [ebp-1Ch]
  int distance; // eax
  int dx; // ebp/ebx
  int dy; // ebp/edi
  int prisoner_slot; // eax
  int prisoner; // eax
  int building_offset; // ebp
  char prisoner_owner; // bl
  const char *message_format; // edi
  int message_table[3]; // [esp+0h] [ebp-2Ch]

  Debug_Log(a1, a2, a3, (int)aPrisoner_setin);
  result = 0;
  for ( queued_index = 0; queued_index < 10; ++queued_index )
  {
    queued_prisoner = PLAYER_DATA(g_CurrentPlayerIndex) + 1357 + 6 * queued_index;
    if ( *(char *)queued_prisoner == -1 )
      continue;

    building_index = 0;
    best_building_index = -1;
    best_distance = MAP_WIDTH_TILES + MAP_HEIGHT_TILES;
    while ( building_index < 100 )
    {
      building = UNIT_RECORD(building_index);
      result = *(char *)(building + 4);
      if ( (unsigned int)result < 4 && *(__int16 *)(building + 16) != -1 )
      {
        if ( *(char *)(building + 4) == 2 && *(unsigned __int8 *)(building + 2) == g_CurrentPlayerIndex )
        {
          dx = *(unsigned __int16 *)(queued_prisoner + 4) - *(unsigned __int8 *)(building + 1);
          dy = *(unsigned __int16 *)(queued_prisoner + 2) - *(unsigned __int8 *)building;
          distance = Math_CeilSqrt(dx * dx + dy * dy);
          if ( distance < best_distance && Building_FindFreePrisonerSlot(building) != -1 )
          {
            best_distance = distance;
            best_building_index = building_index;
          }
        }
      }
      ++building_index;
    }

    if ( best_building_index == -1 )
    {
      *(_BYTE *)queued_prisoner = -1;
      continue;
    }

    building_offset = BUILDING_RECORD_SIZE * best_building_index;
    building = UNIT_RECORD(best_building_index);
    prisoner_slot = Building_FindFreePrisonerSlot(building);
    prisoner = BUILDING_PRISONER_SLOT(building, prisoner_slot);
    BUILDING_PRISONER_TYPE(prisoner) = *(char *)queued_prisoner;
    prisoner_owner = *(_BYTE *)(queued_prisoner + 1);
    *(_BYTE *)(prisoner + 2) = 0;
    BUILDING_PRISONER_ACTION(prisoner) = 0;
    BUILDING_PRISONER_OWNER(prisoner) = prisoner_owner;
    BuildingPrisoner_RecalculateRansomValue(prisoner);
    *(_BYTE *)queued_prisoner = -1;
    result = PLAYER_DATA_STRIDE * g_CurrentPlayerIndex;
    if ( !PLAYER_HAS_HUMAN_CONTROLLER(g_CurrentPlayerIndex) )
      continue;
    Win_PlayModeChangeFrameTransition(aUwiezic, 1, queued_index, prisoner_owner, building_offset);
    message_table[0] = (int)g_PrisonerCastleIntakeTexts[0];
    message_table[1] = (int)g_PrisonerCastleIntakeTexts[1];
    message_table[2] = (int)g_PrisonerCastleIntakeTexts[2];
    message_format = (const char *)message_table[(unsigned __int8)g_LanguageIndex];
    sprintf_(&g_PrisonerIntakeMessageBuffer, message_format, building + 5);
    result = UI_ShowInfoWindow(
               (int)&g_PrisonerIntakeMessageBuffer,
               0,
               0,
               building_offset,
               (int)message_format,
               (int)&g_PrisonerCastleIntakeTexts[3]);
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D08: using guessed type char *g_PrisonerCastleIntakeTexts[21];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044EB70) --------------------------------------------------------
int  BuildingPrisoner_SetAction(int a1, char actionCode, DWORD a3)
{
  int slotIndex; // edx
  int result; // eax
  int buildingRecord; // ecx

  Debug_Log(a1, actionCode, a3, (int)aBuilding_setpr);
  result = slotIndex;
  BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(buildingRecord, slotIndex)) = actionCode;
  return result;
}
// 44EB80: variable 'v3' is possibly undefined
// 44EB8E: variable 'v5' is possibly undefined

//----- (0044EBA0) --------------------------------------------------------
int  BuildingPrisoner_GetAction(int buildingRecord, int prisonerSlot)
{
  return BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(buildingRecord, prisonerSlot));
}

//----- (0044EBC0) --------------------------------------------------------
int  Prisoner_Kill(int buildingRecord, char prisonerSlot, DWORD a3)
{
  unsigned __int8 prisoner_slot; // edx

  Debug_Log(buildingRecord, prisonerSlot, a3, (int)aPrisoner_kill0);
  prisoner_slot = (unsigned __int8)prisonerSlot;
  BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(buildingRecord, prisoner_slot)) = -1;
  return prisoner_slot;
}

//----- (0044EBF0) --------------------------------------------------------
int  Prisoner_Behead(int a1, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  const char *formatString; // esi
  int v9; // ecx
  _BYTE messageBuffer[100]; // [esp+0h] [ebp-74h] BYREF
  int beheadTextTable[4]; // [esp+64h] [ebp-10h] BYREF

  beheadTextTable[3] = a2;
  Debug_Log(a1, a3, a4, (int)aPrisoner_behea);
  Prisoner_Kill(v4, a3, a4);
  result = gameData;
  if ( *(_DWORD *)(PLAYER_DATA_STRIDE * *(unsigned __int8 *)(v5 + 2) + gameData + 140051) )
  {
    Win_PlayModeChangeFrameTransition(aZciecie, 1, v5, a3, a4);
    beheadTextTable[0] = (int)g_PrisonerBeheadingTexts[0];
    beheadTextTable[1] = (int)g_PrisonerBeheadingTexts[1];
    beheadTextTable[2] = (int)g_PrisonerBeheadingTexts[2];
    formatString = (const char *)beheadTextTable[(unsigned __int8)g_LanguageIndex];
    sprintf_(messageBuffer, formatString, v7 + 5);
    return UI_ShowInfoWindow((const char *)messageBuffer, 0, v9, a4, (int)&beheadTextTable[3], (int)formatString);
  }
  return result;
}
// 44EC07: variable 'v4' is possibly undefined
// 44EC0E: variable 'v5' is possibly undefined
// 44EC52: variable 'v7' is possibly undefined
// 44EC6B: variable 'v9' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D14: using guessed type char *g_PrisonerBeheadingTexts[18];
// 5202E4: using guessed type int gameData;

//----- (0044EC80) --------------------------------------------------------
BOOL  Building_IsVisibleToPlayer(unsigned __int8 *buildingCoords, int playerIndex)
{
  unsigned __int8 *v3; // ecx
  BOOL result; // eax
  unsigned __int8 *v5; // ecx
  unsigned __int8 *v6; // ecx

  if ( Map_IsTileVisibleToPlayer(*buildingCoords, buildingCoords[1], playerIndex) )
    return 1;
  if ( Map_IsTileVisibleToPlayer(*v3 + 1, v3[1], playerIndex) )
    return 1;
  if ( Map_IsTileVisibleToPlayer(*v5 + 1, v5[1] + 1, playerIndex) )
    return 1;
  result = Map_IsTileVisibleToPlayer(*v6, v6[1] + 1, playerIndex);
  if ( result )
    return 1;
  return result;
}
// 44ECA6: variable 'v3' is possibly undefined
// 44ECBB: variable 'v5' is possibly undefined
// 44ECD2: variable 'v6' is possibly undefined

//----- (0044ECF0) --------------------------------------------------------
int  Prisoner_FindRichestHiddenEnemyCastle(int enemyPlayerIndex, int viewerPlayerIndex)
{
  int bestValue; // edi
  int castleIndex; // ebx
  int castleRecordOffset; // ecx
  int castleValue; // eax
  int bestCastleIndex; // [esp+4h] [ebp-18h]

  bestValue = 0;
  castleIndex = 0;
  castleRecordOffset = 0;
  bestCastleIndex = -1;
  do
  {
    if ( *(_BYTE *)(castleRecordOffset + gameData + 509678) == 2
      && *(unsigned __int8 *)(castleRecordOffset + gameData + 509676) == enemyPlayerIndex
      && !Building_IsVisibleToPlayer((unsigned __int8 *)(castleRecordOffset + gameData + BUILDING_TABLE_OFFSET), viewerPlayerIndex) )
    {
      castleValue = Building_GetTotalValue(castleRecordOffset + gameData + BUILDING_TABLE_OFFSET);
      if ( castleValue > bestValue )
      {
        bestValue = castleValue;
        bestCastleIndex = castleIndex;
      }
    }
    ++castleIndex;
    castleRecordOffset += 467;
  }
  while ( castleIndex < 100 );
  if ( bestCastleIndex == -1 )
    return 0;
  else
    return UNIT_RECORD(bestCastleIndex);
}
// 44ED4A: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EDB0) --------------------------------------------------------
int  Prisoner_FindAnyHiddenEnemyCastle(int enemyPlayerIndex, int viewerPlayerIndex)
{
  int castleRecordOffset; // ecx

  castleRecordOffset = 0;
  while ( *(_BYTE *)(gameData + castleRecordOffset + 509678) != 2
       || *(unsigned __int8 *)(gameData + castleRecordOffset + 509676) != enemyPlayerIndex
       || Building_IsVisibleToPlayer((unsigned __int8 *)(castleRecordOffset + gameData + BUILDING_TABLE_OFFSET), viewerPlayerIndex) )
  {
    castleRecordOffset += 467;
    if ( castleRecordOffset >= 46700 )
      return 0;
  }
  return castleRecordOffset + gameData + BUILDING_TABLE_OFFSET;
}
// 44EDF0: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EE20) --------------------------------------------------------
int  Prisoner_FindAnyHiddenEnemyUnitStack(int enemyPlayerIndex, int viewerPlayerIndex)
{
  int stackIndex; // ecx
  int stackRecordOffset; // edi
  int stackRecordBase; // eax

  stackIndex = 0;
LABEL_2:
  if ( (unsigned int)*(__int16 *)(UNIT_STACK_STRIDE * stackIndex + gameData + UNIT_STACK_TABLE_OFFSET + 6) <= 0x28 )
  {
    stackRecordOffset = UNIT_STACK_STRIDE * stackIndex;
    stackRecordBase = gameData + UNIT_STACK_STRIDE * stackIndex;
    if ( *(unsigned __int8 *)(stackRecordBase + 147178) == enemyPlayerIndex
      && !Map_IsTileVisibleToPlayer(*(__int16 *)(stackRecordBase + 147174), *(__int16 *)(stackRecordBase + 147176), viewerPlayerIndex) )
    {
      return gameData + UNIT_STACK_TABLE_OFFSET + stackRecordOffset;
    }
  }
  while ( ++stackIndex < 500 )
  {
    if ( stackIndex >= 0 )
      goto LABEL_2;
  }
  return 0;
}
// 44EEB0: conditional instruction was optimized away because ecx.4<1F4u
// 44EE57: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 44EE9D: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EEE0) --------------------------------------------------------
void  Map_RevealTilesInRadius2ForPlayer(int centerRow, int centerColumn, int playerIndex)
{
  int rowCursor; // edi
  int colDelta; // esi
  signed int colCursor; // ecx
  int rowMax; // [esp+4h] [ebp-24h]
  int colMin; // [esp+8h] [ebp-20h]
  int i; // [esp+Ch] [ebp-1Ch]
  int colMax; // [esp+14h] [ebp-14h]

  colMax = centerColumn + 2;
  rowCursor = centerRow - 2;
  colMin = centerColumn - 2;
  rowMax = centerRow + 2;
  for ( i = -2; rowCursor < rowMax; ++i )
  {
    colDelta = colMin - centerColumn;
    if ( colMin < colMax )
    {
      do
      {
        if ( Math_CeilSqrt(i * i + colDelta * colDelta) <= 2 )
          Map_RevealTileWithPropagation(rowCursor, colCursor, playerIndex);
        ++colDelta;
      }
      while ( colCursor + 1 < colMax );
    }
    ++rowCursor;
  }
  Locale_DrawInteger();
}
// 44EF47: variable 'v5' is possibly undefined

//----- (0044EFA0) --------------------------------------------------------
unsigned int  Prisoner_Torture(int a1, int prisonerSlot, int a3, char a4, DWORD a5)
{
  unsigned int result; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  unsigned __int8 *revealTarget; // ebx
  int v11; // ecx
  char **revealTextTablePtr; // esi
  int v13; // ecx
  int *revealFormatArg; // edi
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25[3]; // [esp+0h] [ebp-4Ch]
  int v26[3]; // [esp+Ch] [ebp-40h] BYREF
  int v27[3]; // [esp+18h] [ebp-34h] BYREF
  int v28[3]; // [esp+24h] [ebp-28h]
  int v29[7]; // [esp+30h] [ebp-1Ch] BYREF

  v29[5] = a3;
  Debug_Log(a1, a4, a5, (int)aPrisoner_tortu);
  result = Rng_RandRange(0, 7);
  switch ( result )
  {
    case 0u:
    case 5u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_0);
      revealTarget = (unsigned __int8 *)Prisoner_FindRichestHiddenEnemyCastle(*(unsigned __int8 *)(v8 + 6 * prisonerSlot + 446), *(unsigned __int8 *)(v8 + 2));
      if ( !revealTarget )
        return Prisoner_Torture(v9, prisonerSlot, v9, (char)revealTarget, a5);
      Prisoner_Kill(v9, (char)revealTarget, a5);
      Map_RevealTilesInRadius2ForPlayer(*revealTarget, revealTarget[1], *(unsigned __int8 *)(v11 + 2));
      v27[0] = (int)g_PrisonerTortureRichestCastleRevealTexts[0];
      v27[1] = (int)g_PrisonerTortureRichestCastleRevealTexts[1];
      v27[2] = (int)g_PrisonerTortureRichestCastleRevealTexts[2];
      revealTextTablePtr = &g_PrisonerTortureRichestCastleRevealTexts[3];
      revealFormatArg = (int *)v27[(unsigned __int8)g_LanguageIndex];
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)revealFormatArg, v13 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, a5, (int)revealFormatArg, (int)revealTextTablePtr);
    case 1u:
    case 6u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_1);
      revealTarget = (unsigned __int8 *)Prisoner_FindAnyHiddenEnemyCastle(*(unsigned __int8 *)(v16 + 6 * prisonerSlot + 446), *(unsigned __int8 *)(v16 + 2));
      if ( !revealTarget )
        return Prisoner_Torture(v9, prisonerSlot, v9, (char)revealTarget, a5);
      Prisoner_Kill(v9, (char)revealTarget, a5);
      Map_RevealTilesInRadius2ForPlayer(*revealTarget, revealTarget[1], *(unsigned __int8 *)(v17 + 2));
      v25[0] = (int)g_PrisonerTortureCastleRevealTexts[0];
      v25[1] = (int)g_PrisonerTortureCastleRevealTexts[1];
      v25[2] = (int)g_PrisonerTortureCastleRevealTexts[2];
      revealFormatArg = v26;
      revealTextTablePtr = (char **)v25[(unsigned __int8)g_LanguageIndex];
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)revealTextTablePtr, v18 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, a5, (int)revealFormatArg, (int)revealTextTablePtr);
    case 2u:
    case 7u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_2);
      revealTarget = (unsigned __int8 *)Prisoner_FindAnyHiddenEnemyUnitStack(*(unsigned __int8 *)(v19 + 6 * prisonerSlot + 446), *(unsigned __int8 *)(v19 + 2));
      if ( !revealTarget )
        return Prisoner_Torture(v9, prisonerSlot, v9, (char)revealTarget, a5);
      Prisoner_Kill(v9, (char)revealTarget, a5);
      Map_RevealTilesInRadius2ForPlayer(*(__int16 *)revealTarget, *((__int16 *)revealTarget + 1), *(unsigned __int8 *)(v20 + 2));
      v29[0] = (int)g_PrisonerTortureEnemyStackRevealTexts[0];
      v29[1] = (int)g_PrisonerTortureEnemyStackRevealTexts[1];
      v29[2] = (int)g_PrisonerTortureEnemyStackRevealTexts[2];
      revealTextTablePtr = &g_PrisonerTortureEnemyStackRevealTexts[3];
      revealFormatArg = &v29[3];
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)v29[(unsigned __int8)g_LanguageIndex], v21 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, a5, (int)revealFormatArg, (int)revealTextTablePtr);
    case 3u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_3);
      Prisoner_Kill(v22, a4, a5);
      v28[0] = (int)g_PrisonerTortureNoConfessionDeathTexts[0];
      v28[1] = (int)g_PrisonerTortureNoConfessionDeathTexts[1];
      v28[2] = (int)g_PrisonerTortureNoConfessionDeathTexts[2];
      revealTextTablePtr = &g_PrisonerTortureNoConfessionDeathTexts[3];
      revealFormatArg = v29;
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)v28[(unsigned __int8)g_LanguageIndex], v23 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, a5, (int)revealFormatArg, (int)revealTextTablePtr);
    case 4u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_4);
      BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(v24, prisonerSlot)) = BUILDING_PRISONER_ACTION_NONE;
      v26[0] = (int)g_PrisonerTortureResistanceTexts[0];
      v26[1] = (int)g_PrisonerTortureResistanceTexts[1];
      v26[2] = (int)g_PrisonerTortureResistanceTexts[2];
      revealTextTablePtr = &g_PrisonerTortureResistanceTexts[3];
      revealFormatArg = v27;
      sprintf_(&g_InfoWindowFormatBuffer, (const char *)v26[(unsigned __int8)g_LanguageIndex], v24 + 5);
      return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v15, a5, (int)revealFormatArg, (int)revealTextTablePtr);
    default:
      return result;
  }
}
// 44EFDB: variable 'v7' is possibly undefined
// 44EFF1: variable 'v8' is possibly undefined
// 44F010: variable 'v9' is possibly undefined
// 44F015: variable 'v11' is possibly undefined
// 44F03B: variable 'v13' is possibly undefined
// 44F055: variable 'v15' is possibly undefined
// 44F08E: variable 'v16' is possibly undefined
// 44F0B9: variable 'v17' is possibly undefined
// 44F0DA: variable 'v18' is possibly undefined
// 44F100: variable 'v19' is possibly undefined
// 44F12E: variable 'v20' is possibly undefined
// 44F14F: variable 'v21' is possibly undefined
// 44F174: variable 'v22' is possibly undefined
// 44F186: variable 'v23' is possibly undefined
// 44F1AA: variable 'v24' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D20: using guessed type char *g_PrisonerTortureRichestCastleRevealTexts[15];
// 518D2C: using guessed type char *g_PrisonerTortureCastleRevealTexts[12];
// 518D38: using guessed type char *g_PrisonerTortureEnemyStackRevealTexts[9];
// 518D44: using guessed type char *g_PrisonerTortureNoConfessionDeathTexts[6];
// 518D50: using guessed type char *g_PrisonerTortureResistanceTexts[3];

//----- (0044F1E0) --------------------------------------------------------
int  Building_CreateSpecialPersonageGarrisonUnit(DWORD buildingRecord, unit_type unitType, int a3, char a4, double a5)
{
  int garrison_slot_ptr; // edx
  int slot_index; // eax
  int result; // eax
  int slot_offset; // ecx
  int leave_mask[12]; // [esp+0h] [ebp-48h] BYREF

  Debug_Log(a3, a4, buildingRecord, (int)aBuilding_creat);
  garrison_slot_ptr = buildingRecord + 18;
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( *(__int16 *)garrison_slot_ptr == -1 )
      break;
    garrison_slot_ptr += 31;
  }
  if ( slot_index == 12 )
  {
    qmemcpy(leave_mask, &g_SpecialPersonageLeaveMaskTemplate, sizeof(leave_mask));
    Building_UnitsLeave((unsigned __int8 *)buildingRecord, leave_mask, a5);
    slot_index = 0;
  }
  slot_offset = 31 * slot_index;
  result = UnitSlot_InitFromType(buildingRecord + 18 + slot_offset, unitType, *(_BYTE *)(buildingRecord + 2));
  *(_BYTE *)(buildingRecord + 30 + slot_offset) |= 3u;
  return result;
}

//----- (0044F260) --------------------------------------------------------
unsigned int  Prisoner_Pay(int a1, int prisonerSlot, DWORD a3, double a4)
{
  DWORD buildingRecord; // ecx
  unsigned int result; // eax
  unsigned int playerGold; // edi
  int v8; // ecx
  int v9; // ecx
  const char *v10; // esi
  int v11; // ecx
  int v12[8]; // [esp+0h] [ebp-20h] BYREF

  Debug_Log(a1, prisonerSlot, a3, (int)aPrisoner_pay0x);
  if ( *(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingRecord + 2) + 140051) )
  {
    result = BUILDING_PRISONER_RANSOM(BUILDING_PRISONER_SLOT(buildingRecord, prisonerSlot));
    playerGold = *(_DWORD *)(buildingRecord + 438);
    if ( result > playerGold )
      return result;
    a3 = playerGold - result;
    *(_DWORD *)(buildingRecord + 438) = playerGold - result;
  }
  Building_CreateSpecialPersonageGarrisonUnit(buildingRecord, BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(buildingRecord, prisonerSlot)), buildingRecord, prisonerSlot, a4);
  Prisoner_Kill(v8, prisonerSlot, a3);
  result = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(v9 + 2);
  if ( *(_DWORD *)(gameData + result + 140051) )
  {
    v12[0] = (int)g_PrisonerBriberyDefectionTexts[0];
    v12[1] = (int)g_PrisonerBriberyDefectionTexts[1];
    v12[2] = (int)g_PrisonerBriberyDefectionTexts[2];
    v10 = (const char *)v12[(unsigned __int8)g_LanguageIndex];
    sprintf_(&g_InfoWindowFormatBuffer, v10, v9 + 5);
    return UI_ShowInfoWindow((const char *)&g_InfoWindowFormatBuffer, 0, v11, a3, (int)&v12[3], (int)v10);
  }
  return result;
}
// 44F27A: variable 'v5' is possibly undefined
// 44F2E3: variable 'v8' is possibly undefined
// 44F2EA: variable 'v9' is possibly undefined
// 44F33A: variable 'v11' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D8C: using guessed type char *g_PrisonerBriberyDefectionTexts[6];
// 5202E4: using guessed type int gameData;

//----- (0044F350) --------------------------------------------------------
char  Prisoner_NewTurn(DWORD buildingRecord, int a2, char a3, double a4)
{
  int v5; // edx
  int v6; // eax
  int slotIndex; // ebx
  char *prisonerCursor; // ecx
  int v9; // ecx
  _BYTE messageBuffer[100]; // [esp+0h] [ebp-90h] BYREF
  int exhaustionTextTable[3]; // [esp+64h] [ebp-2Ch]
  int prisonerSlotPtr; // [esp+70h] [ebp-20h] BYREF
  DWORD buildingNamePtr; // [esp+74h] [ebp-1Ch]

  v5 = ACTIVE_MISSION_INDEX;
  if ( v5 != 4 && v5 != 6 || (v6 = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingRecord + 2), *(_DWORD *)(gameData + v6 + 140051)) )
  {
    Debug_Log(a2, a3, buildingRecord, (int)aPrisoner_newtu);
    buildingNamePtr = buildingRecord + 5;
    slotIndex = 0;
    prisonerCursor = (char *)buildingRecord;
    prisonerSlotPtr = buildingRecord + 445;
    do
    {
      v6 = prisonerCursor[445];
      if ( v6 != -1 )
      {
        ++prisonerCursor[447];
        if ( !*(_DWORD *)(gameData + PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingRecord + 2) + 140051) && prisonerCursor[447] == 9 )
          prisonerCursor[448] = BUILDING_PRISONER_ACTION_PAY;
        BuildingPrisoner_RecalculateRansomValue(prisonerSlotPtr);
        if ( prisonerCursor[447] == 10 )
        {
          prisonerCursor[445] = -1;
          v6 = PLAYER_DATA_STRIDE * *(unsigned __int8 *)(buildingRecord + 2);
          if ( *(_DWORD *)(gameData + v6 + 140051) )
          {
            exhaustionTextTable[0] = (int)g_PrisonerDeathByExhaustionTexts[0];
            exhaustionTextTable[1] = (int)g_PrisonerDeathByExhaustionTexts[1];
            exhaustionTextTable[2] = (int)g_PrisonerDeathByExhaustionTexts[2];
            a4 = sprintf_(messageBuffer, (const char *)exhaustionTextTable[(unsigned __int8)g_LanguageIndex], buildingNamePtr);
            LOBYTE(v6) = UI_ShowInfoWindow((const char *)messageBuffer, 0, v9, buildingRecord, (int)&prisonerSlotPtr, (int)&g_PrisonerDeathByExhaustionTexts[3]);
          }
        }
        else
        {
          LOBYTE(v6) = prisonerCursor[448];
          if ( (unsigned __int8)v6 >= BUILDING_PRISONER_ACTION_TORTURE )
          {
            if ( (unsigned __int8)v6 <= BUILDING_PRISONER_ACTION_TORTURE )
            {
              LOBYTE(v6) = Prisoner_Torture(buildingRecord, slotIndex, (int)prisonerCursor, slotIndex, buildingRecord);
            }
            else if ( (_BYTE)v6 == BUILDING_PRISONER_ACTION_PAY )
            {
              LOBYTE(v6) = Prisoner_Pay(buildingRecord, slotIndex, buildingRecord, a4);
            }
          }
          else if ( (_BYTE)v6 == BUILDING_PRISONER_ACTION_BEHEAD )
          {
            LOBYTE(v6) = Prisoner_Behead(buildingRecord, (int)prisonerCursor, slotIndex, buildingRecord);
          }
        }
      }
      prisonerCursor += 6;
      ++slotIndex;
      prisonerSlotPtr += 6;
    }
    while ( slotIndex < 3 );
  }
  return v6;
}
// 44F3F1: variable 'v8' is possibly undefined
// 44F450: variable 'v9' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 511130: using guessed type char g_LanguageIndex;
// 518D98: using guessed type char *g_PrisonerDeathByExhaustionTexts[3];
// 5202E4: using guessed type int gameData;

//----- (0044F4E0) --------------------------------------------------------
int  Building_CountPrisoners(int buildingRecord)
{
  int slotLoopEnd; // ebx
  int prisonerCount; // edx

  slotLoopEnd = buildingRecord + 18;
  prisonerCount = 0;
  do
  {
    if ( *(char *)(buildingRecord + 445) != -1 )
      ++prisonerCount;
    buildingRecord += 6;
  }
  while ( buildingRecord != slotLoopEnd );
  return prisonerCount;
}

//----- (0044F510) --------------------------------------------------------
BOOL  BuildingPrisonerActionWidget_HasPrisoner(int a1)
{
  return *(char *)(g_CurrentPrisonBuildingRecord + 6 * ((a1 - (int)&g_PrisonerActionButtonWidgets) / 53 / 3) + 445) != -1;
}
// 5443FC: using guessed type int dword_5443FC;

//----- (0044F580) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectBehead(int widgetRecord)
{
  char *result; // eax
  unsigned __int8 toggledState; // ah
  _DWORD *widgetCursor; // ebx
  int buttonIndex; // ecx

  Render_Begin((int)g_RenderState, 0);
  result = (char *)BuildingPrisonerActionWidget_HasPrisoner(widgetRecord);
  if ( result )
  {
    toggledState = *(_BYTE *)(widgetRecord + 8) ^ 1;
    *(_BYTE *)(widgetRecord + 8) = toggledState;
    *(_BYTE *)(widgetRecord + 8) = toggledState ^ 2;
    if ( ((toggledState ^ 2) & 2) != 0 )
    {
      widgetCursor = g_PrisonerActionButtonWidgets;
      buttonIndex = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * buttonIndex) = 1;
        UIWidget_RefreshActionButtonState((int)widgetCursor, buttonIndex + 1);
        widgetCursor = (_DWORD *)((char *)widgetCursor + 53);
      }
      while ( buttonIndex < 9 );
      *(_DWORD *)(widgetRecord + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(widgetRecord + 49));
  }
  return result;
}
// 44F5BA: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F5F0) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectTorture(int widgetRecord)
{
  char *result; // eax
  unsigned __int8 toggledState; // ah
  _DWORD *widgetCursor; // ebx
  int buttonIndex; // ecx

  Render_Begin((int)g_RenderState, 0);
  result = (char *)BuildingPrisonerActionWidget_HasPrisoner(widgetRecord);
  if ( result )
  {
    toggledState = *(_BYTE *)(widgetRecord + 8) ^ 1;
    *(_BYTE *)(widgetRecord + 8) = toggledState;
    *(_BYTE *)(widgetRecord + 8) = toggledState ^ 2;
    if ( ((toggledState ^ 2) & 2) != 0 )
    {
      widgetCursor = g_PrisonerActionButtonWidgets;
      buttonIndex = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * buttonIndex) = 1;
        UIWidget_RefreshActionButtonState((int)widgetCursor, buttonIndex + 1);
        widgetCursor = (_DWORD *)((char *)widgetCursor + 53);
      }
      while ( buttonIndex < 9 );
      *(_DWORD *)(widgetRecord + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(widgetRecord + 49));
  }
  return result;
}
// 44F62A: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F660) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectBribery(int widgetRecord)
{
  char *result; // eax
  unsigned __int8 toggledState; // ah
  _DWORD *widgetCursor; // ebx
  int buttonIndex; // ecx

  Render_Begin((int)g_RenderState, 0);
  result = (char *)BuildingPrisonerActionWidget_HasPrisoner(widgetRecord);
  if ( result )
  {
    toggledState = *(_BYTE *)(widgetRecord + 8) ^ 1;
    *(_BYTE *)(widgetRecord + 8) = toggledState;
    *(_BYTE *)(widgetRecord + 8) = toggledState ^ 2;
    if ( ((toggledState ^ 2) & 2) != 0 )
    {
      widgetCursor = g_PrisonerActionButtonWidgets;
      buttonIndex = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * buttonIndex) = 1;
        UIWidget_RefreshActionButtonState((int)widgetCursor, buttonIndex + 1);
        widgetCursor = (_DWORD *)((char *)widgetCursor + 53);
      }
      while ( buttonIndex < 9 );
      *(_DWORD *)(widgetRecord + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(widgetRecord + 49));
  }
  return result;
}
// 44F69A: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F6D0) --------------------------------------------------------
int  BuildingPrisonerPanel_BackButton(int a1)
{
  int result; // eax
  int v3; // edx

  result = UIWidget_PlayPressedReleaseAnimation(a1);
  g_PrisonerDialogExitSignal = v3;
  return result;
}
// 44F6DB: variable 'v3' is possibly undefined
// 5443F4: using guessed type int dword_5443F4;

//----- (0044FC70) --------------------------------------------------------
int  Building_DrawPrisonerRows(DWORD a1)
{
  int prisonerRecordOffset; // edi
  int rowIndex; // esi
  int result; // eax
  int SpriteForChar; // eax
  int v5; // eax

  prisonerRecordOffset = 0;
  rowIndex = 0;
  g_RenderDevice = &g_MainRenderDevice;
  Render_ReleaseSurface(18, a1);
  do
  {
    result = *(char *)(prisonerRecordOffset + g_CurrentPrisonBuildingRecord + 445);
    if ( result != -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 5);
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        368,
        SpriteForChar,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      v5 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, *(unsigned __int8 *)(prisonerRecordOffset + g_CurrentPrisonBuildingRecord + 446));
      (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
        378,
        v5,
        -1,
        -1,
        -1,
        -1,
        1,
        0,
        0);
      result = UI_DrawTextFmt(
                 prisonerRecordOffset,
                 (unsigned __int16)g_PrisonerRowTextXTable[rowIndex] + 1,
                 (unsigned __int16)g_PrisonerRowTextXTable[rowIndex] + 68,
                 461,
                 3,
                 (int)aD_79);
    }
    ++rowIndex;
    prisonerRecordOffset += 6;
  }
  while ( rowIndex != 3 );
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 518DBC: using guessed type __int16 word_518DBC[];
// 5443F0: using guessed type int dword_5443F0;
// 5443FC: using guessed type int dword_5443FC;

//----- (0044FD90) --------------------------------------------------------
int  Queen_DrawRelationshipPanel(DWORD a1, int a2)
{
  int SpriteForChar; // eax
  int queenRelationshipState; // eax

  g_RenderDevice = &g_MainRenderDevice;
  queenRelationshipState = PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex);
  if ( queenRelationshipState > 0 )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_StatScreenSpriteSet, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 25);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      199,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
  }
  Render_ReleaseSurface(17, a1);
  if ( queenRelationshipState == -1 )
    queenRelationshipState = 0;
  return UI_DrawTextFmt(
           a2,
           180,
           500,
           215,
           6,
           (int)(&g_QueenRelationshipStateTexts[3 * queenRelationshipState])[(unsigned __int8)g_LanguageIndex]);
}
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 519010: using guessed type char *g_QueenRelationshipStateTexts[30];
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;
// 5443F0: using guessed type int dword_5443F0;

//----- (0044FE70) --------------------------------------------------------
int  Building_ShowPrisonerManagementPanel(int buildingRecord, void *a2, DWORD a3)
{
  int i; // eax
  _DWORD *actionWidgetCursor; // esi
  int j; // edi
  unsigned int v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  char v11; // bl
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  void *v17; // ecx
  int SpriteForChar; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // edx
  int maxPopulation; // ebp
  int v24; // ecx
  int playerIndex; // esi
  int playerRecordOffset; // edi
  int v27; // ebx
  int v28; // ebx
  int v29; // eax
  int v30; // edx
  int v31; // ebx
  int v32; // eax
  int v33; // eax
  int v34; // ebx
  int v35; // eax
  DWORD populationRange; // ebp
  int v37; // eax
  int v38; // eax
  int barRowIndex; // edi
  int v40; // esi
  int barValueIndex; // esi
  int v42; // ecx
  int v43; // edx
  int v44; // ebx
  int v45; // ecx
  int v46; // eax
  int v47; // edx
  int v48; // edx
  int v49; // ecx
  int v50; // ecx
  int v51; // ecx
  char v52; // bl
  int v53; // eax
  char v54; // bl
  int v55; // eax
  char v56; // bl
  int v57; // eax
  int v59; // eax
  int v60; // edi
  int militaryStrengthBars[5]; // [esp+C4h] [ebp-64h]
  int nationScoreBars[5]; // [esp+D8h] [ebp-50h]
  int populationBars[5]; // [esp+ECh] [ebp-3Ch]
  int maxNationScore; // [esp+100h] [ebp-28h]
  int minPopulation; // [esp+104h] [ebp-24h]
  int v66; // [esp+108h] [ebp-20h]
  int maxMilitaryStrength; // [esp+10Ch] [ebp-1Ch]

  g_CurrentPrisonBuildingRecord = buildingRecord;
  for ( i = 0; i != 477; *(char **)((char *)g_PrisonerDeathByExhaustionTexts + i + 3) = (char *)1 )
    i += 53;
  actionWidgetCursor = g_PrisonerActionButtonWidgets;
  for ( j = 0; j < 3; ++j )
  {
    v6 = BuildingPrisoner_GetAction(g_CurrentPrisonBuildingRecord, j);
    if ( v6 >= BUILDING_PRISONER_ACTION_TORTURE )
    {
      if ( v6 <= BUILDING_PRISONER_ACTION_TORTURE )
      {
        *(_DWORD *)((char *)actionWidgetCursor + 61) = v7;
      }
      else if ( v6 == BUILDING_PRISONER_ACTION_PAY )
      {
        *(_DWORD *)((char *)actionWidgetCursor + 114) = v7;
      }
    }
    else if ( v6 == BUILDING_PRISONER_ACTION_BEHEAD )
    {
      actionWidgetCursor[2] = v7;
    }
    actionWidgetCursor = (_DWORD *)((char *)actionWidgetCursor + 159);
  }
  v8 = Mem_Alloc(1024, v7, (char)a2, a3);
  if ( v8 )
  {
    a2 = &g_Runtime_PaletteArrayCtorDescriptor;
    v8 = _wcpp_4_ctor_array__(v9, 256);
  }
  g_StatScreenPaletteBuffer = v8;
  v10 = (_DWORD *)Mem_Alloc(4112, v9, (char)a2, a3);
  if ( v10 )
    v10 = DLXSpriteSet_Load(v10, (char)a2);
  g_StatScreenSpriteSet = (int)v10;
  v11 = g_StatScreenPaletteBuffer;
  (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 48))(0, aStat_gfx);
  Palette_LoadOrBuildBlendLookupTable(aStat, g_StatScreenPaletteBuffer, v12, a3);
  Render_LoadResourceSprite_v4(8, (_BYTE *)g_StatScreenPaletteBuffer, v13, v11, a3);
  Render_LoadResourceSprite_v4(18, (_BYTE *)g_StatScreenPaletteBuffer, v14, v11, a3);
  Render_LoadResourceSprite_v4(17, (_BYTE *)g_StatScreenPaletteBuffer, v15, v11, a3);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, g_StatScreenPaletteBuffer, v16, a3);
  (*(void (__thiscall **)(void *))(*(_DWORD *)(g_PrimaryRenderSurface + 184) + 36))(&g_MainRenderDevice);
  g_RenderDevice = v17;
  Render_ReleaseSurface(18, a3);
  if ( *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) )
  {
    SpriteForChar = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(gameData + 140063) == 0) + 13);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      8,
      SpriteForChar,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 88, 214, 30, 3, gameData + 140028);
  }
  if ( *(_DWORD *)(gameData + 141447) )
  {
    v19 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(gameData + 141486) == 0) + 15);
    j = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(j + 52))(
      8,
      v19,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 254, 380, 30, 3, gameData + 141451);
  }
  if ( *(_DWORD *)(gameData + 142870) )
  {
    v20 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(gameData + 142909) == 0) + 17);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      8,
      v20,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 420, 546, 30, 3, gameData + 142874);
  }
  if ( *(_DWORD *)(gameData + 144293) )
  {
    v21 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(gameData + 144332) == 0) + 19);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
      52,
      v21,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(j, 172, 298, 75, 3, gameData + 144297);
  }
  if ( *(_DWORD *)(gameData + 145716) )
  {
    v59 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, (*(_DWORD *)(gameData + 145755) == 0) + 21);
    v60 = *((_DWORD *)g_RenderDevice + 46);
    (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v60 + 52))(
      52,
      v59,
      -1,
      -1,
      -1,
      -1,
      1,
      0,
      0);
    UI_DrawTextFmt(v60, 336, 462, 75, 3, gameData + 145720);
  }
  v22 = 0;
  maxPopulation = 0;
  v24 = 0;
  playerIndex = 0;
  playerRecordOffset = 0;
  maxNationScore = 0;
  maxMilitaryStrength = 0;
  minPopulation = 0;
  do
  {
    v27 = *(_DWORD *)(playerRecordOffset + gameData + PLAYER_RUNTIME_STATE_OFFSET);
    if ( v24 == v27 )
    {
      populationBars[v22] = v27;
      militaryStrengthBars[v22] = v27;
      nationScoreBars[v22] = v27;
    }
    else
    {
      v28 = maxNationScore;
      v29 = AI_TickNationPostTurn(playerIndex);
      *(int *)((char *)nationScoreBars + v30) = v29;
      if ( v29 > v28 )
        maxNationScore = v29;
      v31 = maxMilitaryStrength;
      v32 = Player_CalcMilitaryStrength(playerIndex);
      militaryStrengthBars[v22] = v32;
      if ( v32 > v31 )
        maxMilitaryStrength = v32;
      v33 = *(__int16 *)(playerRecordOffset + gameData + 141441);
      populationBars[v22] = v33;
      if ( maxPopulation < v33 )
        maxPopulation = v33;
      v34 = populationBars[v22];
      if ( v24 > v34 && v34 < minPopulation )
        minPopulation = populationBars[v22];
    }
    playerRecordOffset += 1423;
    ++playerIndex;
    ++v22;
  }
  while ( playerIndex < 5 );
  g_RenderDevice = (_UNKNOWN *)g_PrimaryRenderSurface;
  v35 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 24);
  populationRange = maxPopulation - minPopulation;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    107,
    v35,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v37 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 24);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    107,
    v37,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  v38 = DLX_GetSpriteForChar(g_StatScreenSpriteSet, 24);
  barRowIndex = 0;
  v40 = *((_DWORD *)g_RenderDevice + 46);
  v66 = 0;
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v40 + 52))(
    107,
    v38,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  barValueIndex = 0;
  do
  {
    if ( *(_DWORD *)(v66 + gameData + PLAYER_RUNTIME_STATE_OFFSET) )
    {
      if ( maxNationScore )
        v42 = maxNationScore;
      else
        v42 = 1;
      v43 = 123 * militaryStrengthBars[barValueIndex];
      v44 = maxMilitaryStrength;
      nationScoreBars[barValueIndex] = 123 * nationScoreBars[barValueIndex] / v42;
      if ( v44 )
        v45 = v44;
      else
        v45 = 1;
      v46 = v43 / v45;
      v47 = populationBars[barValueIndex];
      militaryStrengthBars[barValueIndex] = v46;
      v48 = 123 * (v47 - minPopulation);
      if ( populationRange )
        v49 = populationRange;
      else
        v49 = 1;
      populationBars[barValueIndex] = v48 / v49;
      Render_FillRect(
        (_DWORD *)g_PrimaryRenderSurface,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[barRowIndex] + 107),
        299,
        LOWORD(nationScoreBars[barValueIndex]) + 299,
        g_PrisonerRowBarBottomYTable[barRowIndex] + 107,
        0x12Bu,
        g_PrisonerRowBarTopYTable[barRowIndex] + 107);
      Render_FillRect(
        (_DWORD *)g_PrimaryRenderSurface,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[barRowIndex] + 107),
        88,
        LOWORD(militaryStrengthBars[barValueIndex]) + 88,
        g_PrisonerRowBarBottomYTable[barRowIndex] + 107,
        0x58u,
        g_PrisonerRowBarTopYTable[barRowIndex] + 107);
      Render_FillRect(
        (_DWORD *)g_PrimaryRenderSurface,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[barRowIndex] + 107),
        510,
        LOWORD(populationBars[barValueIndex]) + 510,
        g_PrisonerRowBarBottomYTable[barRowIndex] + 107,
        0x1FEu,
        g_PrisonerRowBarTopYTable[barRowIndex] + 107);
    }
    ++barRowIndex;
    ++barValueIndex;
    v66 += 1423;
  }
  while ( barRowIndex != 5 );
  Building_DrawPrisonerRows(populationRange);
  Queen_DrawRelationshipPanel(populationRange, 10);
  UIWidgetTable_InitDrawStates(g_PrisonerActionButtonWidgets);
  Palette_FadeInFromBlack((int *)&g_MainRenderDevice, (unsigned __int8 *)g_StatScreenPaletteBuffer, 20);
  Render_Present((int)g_RenderState);
  g_PrisonerDialogExitSignal = v50;
  do
  {
    DD_Pump((int)g_RenderState, (char)g_RenderState);
    g_RenderDevice = &g_MainRenderDevice;
    UIWidgetTable_PollHoverAndActions(g_PrisonerActionButtonWidgets, populationRange);
  }
  while ( v51 == g_PrisonerDialogExitSignal );
  if ( g_PrisonerActionButtonState0 == 2 )
  {
    v52 = BUILDING_PRISONER_ACTION_BEHEAD;
LABEL_48:
    v53 = g_CurrentPrisonBuildingRecord;
    goto LABEL_49;
  }
  if ( g_PrisonerActionButtonState1 == 2 )
  {
    v53 = g_CurrentPrisonBuildingRecord;
    v52 = BUILDING_PRISONER_ACTION_TORTURE;
  }
  else
  {
    if ( g_PrisonerActionButtonState2 == 2 )
    {
      v52 = BUILDING_PRISONER_ACTION_PAY;
      goto LABEL_48;
    }
    v53 = g_CurrentPrisonBuildingRecord;
    v52 = BUILDING_PRISONER_ACTION_NONE;
  }
LABEL_49:
  BuildingPrisoner_SetAction(v53, v52, populationRange);
  if ( g_PrisonerActionButtonState3 == 2 )
  {
    v54 = BUILDING_PRISONER_ACTION_BEHEAD;
    v55 = g_CurrentPrisonBuildingRecord;
  }
  else if ( g_PrisonerActionButtonState4 == 2 )
  {
    v55 = g_CurrentPrisonBuildingRecord;
    v54 = BUILDING_PRISONER_ACTION_TORTURE;
  }
  else if ( g_PrisonerActionButtonState5 == 2 )
  {
    v54 = BUILDING_PRISONER_ACTION_PAY;
    v55 = g_CurrentPrisonBuildingRecord;
  }
  else
  {
    v55 = g_CurrentPrisonBuildingRecord;
    v54 = BUILDING_PRISONER_ACTION_NONE;
  }
  BuildingPrisoner_SetAction(v55, v54, populationRange);
  if ( g_PrisonerActionButtonState6 == 2 )
  {
    v56 = BUILDING_PRISONER_ACTION_BEHEAD;
    v57 = g_CurrentPrisonBuildingRecord;
  }
  else if ( g_PrisonerActionButtonState7 == 2 )
  {
    v56 = BUILDING_PRISONER_ACTION_TORTURE;
    v57 = g_CurrentPrisonBuildingRecord;
  }
  else if ( g_PrisonerActionButtonState8 == 2 )
  {
    v56 = BUILDING_PRISONER_ACTION_PAY;
    v57 = g_CurrentPrisonBuildingRecord;
  }
  else
  {
    v57 = g_CurrentPrisonBuildingRecord;
    v56 = BUILDING_PRISONER_ACTION_NONE;
  }
  BuildingPrisoner_SetAction(v57, v56, g_PrisonerActionButtonState6);
  DLXSpriteSet_ReleaseAndClear(&g_StatScreenSpriteSet);
  j__nfree_();
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&g_MainRenderDevice, 20);
}
// 44FEBB: variable 'v7' is possibly undefined
// 44FEE2: variable 'v9' is possibly undefined
// 44FF2F: variable 'v12' is possibly undefined
// 44FF3F: variable 'v13' is possibly undefined
// 44FF4F: variable 'v14' is possibly undefined
// 44FF5F: variable 'v15' is possibly undefined
// 44FF6F: variable 'v16' is possibly undefined
// 44FF8C: variable 'v17' is possibly undefined
// 45019B: variable 'v24' is possibly undefined
// 4501AC: variable 'v30' is possibly undefined
// 4501C3: variable 'v22' is possibly undefined
// 450464: variable 'v50' is possibly undefined
// 450495: variable 'v51' is possibly undefined
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 518D98: using guessed type char *off_518D98[3];
// 518DB0: using guessed type __int16 word_518DB0[];
// 518DB2: using guessed type __int16 word_518DB2[];
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 518E05: using guessed type int dword_518E05;
// 518E3A: using guessed type int dword_518E3A;
// 518E6F: using guessed type int dword_518E6F;
// 518EA4: using guessed type int dword_518EA4;
// 518ED9: using guessed type int dword_518ED9;
// 518F0E: using guessed type int dword_518F0E;
// 518F43: using guessed type int dword_518F43;
// 518F78: using guessed type int dword_518F78;
// 5202E0: using guessed type int dword_5202E0;
// 5202E4: using guessed type int gameData;
// 5443F0: using guessed type int dword_5443F0;
// 5443F4: using guessed type int dword_5443F4;
// 5443F8: using guessed type int dword_5443F8;
// 5443FC: using guessed type int dword_5443FC;
// 544CD8: using guessed type _DWORD g_RenderState[9];

