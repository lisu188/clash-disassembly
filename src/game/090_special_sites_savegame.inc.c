/* Ports, temples, treasures, persistence, and related dialogs.
 * Original function-marker range: 0x00441DC0..0x0044FE70.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00441DC0) --------------------------------------------------------
int  Audio_PlayUnitMeleeAttackSound(int result)
{
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v9, aSfxOddzialy_4, sizeof(v9));
    v1 = (&g_UnitTypeResourceKeys)[22 * result];
    v2 = &v9[strlen(v9)];
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
    v5 = aWalka_wav;
    v6 = &v9[strlen(v9)];
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
    return CSS_PlaySound((int)v9, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441E60) --------------------------------------------------------
int  Audio_PlayUnitShotSound(int result)
{
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v9, aSfxOddzialy_5, sizeof(v9));
    v1 = (&g_UnitTypeResourceKeys)[22 * result];
    v2 = &v9[strlen(v9)];
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
    v5 = aGothim_wav;
    v6 = &v9[strlen(v9)];
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
    return CSS_PlaySound((int)v9, 64, 0, 0);
  }
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00441F00) --------------------------------------------------------
void  Audio_PlayWorldMapUnitMoveSound(int a1, int a2, signed int a3, unsigned int a4)
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
  unsigned int v21; // ebx
  char *v22; // esi
  char *v23; // edi
  char v24; // al
  char v25; // al
  unsigned int v26; // eax
  char v27[100]; // [esp+0h] [ebp-E4h] BYREF
  char v28[100]; // [esp+64h] [ebp-80h] BYREF
  signed int v29; // [esp+C8h] [ebp-1Ch]
  int v30; // [esp+CCh] [ebp-18h]
  char v31[4]; // [esp+D0h] [ebp-14h] BYREF
  _BYTE v32[16]; // [esp+D4h] [ebp-10h] BYREF

  v29 = a2;
  if ( !g_UnitSoundsEnabled )
    return;
  if ( a4 != UNIT_TYPE_CANNON && a4 != UNIT_TYPE_RAM && a4 != UNIT_TYPE_CATAPULT && a4 != UNIT_TYPE_FLY )
  {
    if ( a3 % 4 )
      return;
    if ( a4 != g_CurrentUnitMoveSoundTypeId )
    {
      g_CurrentUnitMoveSoundTypeId = a4;
      g_CurrentUnitMoveSoundVariant = 0;
    }
    CSS_StopSound(g_CurrentUnitMoveSoundHandle, 0);
    qmemcpy(v27, aSfxRuchy_0, sizeof(v27));
    v13 = (&g_UnitMoveSoundStems)[22 * a4];
    v14 = &v27[strlen(v27)];
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
    if ( (g_UnitTypeFlags[22 * a4] & 1) != 0 )
    {
      v17 = v32;
      v32[1] = HIBYTE(g_WorldMapUnitMoveSoundSuffixCode);
      v32[0] = g_CurrentUnitMoveSoundVariant + 49;
      goto LABEL_25;
    }
    strcpy(v31, "d0");
    v31[1] = g_CurrentUnitMoveSoundVariant + 49;
    v26 = Map_GetTileSurfaceClassOrUnexplored(a1, v29);
    if ( v26 < 0xB7 )
    {
      if ( v26 < 0x93 )
      {
        if ( v26 != 39 )
        {
          v17 = v31;
          goto LABEL_25;
        }
LABEL_37:
        v31[0] = 116;
        v17 = v31;
        goto LABEL_25;
      }
      if ( v26 > 0x93 )
      {
        if ( v26 == 151 )
          v31[0] = 112;
        v17 = v31;
        goto LABEL_25;
      }
      goto LABEL_35;
    }
    if ( v26 <= 0xB7 )
      goto LABEL_37;
    if ( v26 >= 0xCA )
    {
      if ( v26 <= 0xCA )
        goto LABEL_35;
      if ( v26 < 0xCC )
        goto LABEL_36;
      if ( v26 <= 0xCC || v26 == 207 )
      {
LABEL_35:
        v31[0] = 100;
LABEL_36:
        v17 = v31;
        goto LABEL_25;
      }
      v17 = v31;
    }
    else
    {
      if ( v26 == 185 )
        goto LABEL_37;
      v17 = v31;
    }
LABEL_25:
    v18 = &v27[strlen(v27)];
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
    v21 = 88 * a4;
    v22 = a_wav_0;
    v23 = &v27[strlen(v27)];
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
    g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)v27, (unsigned __int8)g_UnitMoveSoundBaseVolumes[v21], 0, 0);
    g_CurrentUnitMoveSoundVariant = (g_CurrentUnitMoveSoundVariant + 1) % (unsigned __int8)g_UnitMoveSoundVariantCounts[v21];
    return;
  }
  if ( a4 != g_CurrentUnitMoveSoundTypeId )
  {
    g_CurrentUnitMoveSoundTypeId = a4;
    qmemcpy(v28, aSfxRuchy, sizeof(v28));
    v5 = (&g_UnitMoveSoundStems)[22 * a4];
    v6 = &v28[strlen(v28)];
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
    v10 = &v28[strlen(v28)];
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
    g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)v28, (unsigned __int8)g_UnitMoveSoundBaseVolumes[88 * a4], 0, 0);
    if ( a4 > 0xD )
    {
      if ( a4 <= 0xE )
        v30 = 30406;
      else
        v30 = 0;
    }
    else
    {
      v30 = 31336;
    }
    CSS_SetSoundLoop(g_CurrentUnitMoveSoundHandle, v30, -1);
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
void  Audio_PlayBattleMapUnitMoveSound(int a1, int a2, signed int a3, unsigned int a4)
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
  unsigned int v21; // ebx
  char *v22; // esi
  char *v23; // edi
  char v24; // al
  char v25; // al
  unsigned int v26; // eax
  char v27[100]; // [esp+0h] [ebp-E4h] BYREF
  char v28[100]; // [esp+64h] [ebp-80h] BYREF
  int v29; // [esp+C8h] [ebp-1Ch]
  int v30; // [esp+CCh] [ebp-18h]
  char v31[4]; // [esp+D0h] [ebp-14h] BYREF
  _BYTE v32[16]; // [esp+D4h] [ebp-10h] BYREF

  v29 = a2;
  if ( g_UnitSoundsEnabled )
  {
    if ( a4 == UNIT_TYPE_CANNON || a4 == UNIT_TYPE_RAM || a4 == UNIT_TYPE_CATAPULT || a4 == UNIT_TYPE_FLY )
    {
      if ( a4 != g_CurrentUnitMoveSoundTypeId )
      {
        g_CurrentUnitMoveSoundTypeId = a4;
        qmemcpy(v28, aSfxRuchy_1, sizeof(v28));
        v5 = (&g_UnitMoveSoundStems)[22 * a4];
        v6 = &v28[strlen(v28)];
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
        v10 = &v28[strlen(v28)];
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
        g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)v28, (unsigned __int8)g_UnitMoveSoundBaseVolumes[88 * a4], 0, 0);
        if ( a4 > 0xD )
        {
          if ( a4 <= 0xE )
            v30 = 30406;
          else
            v30 = 0;
        }
        else
        {
          v30 = 31336;
        }
        CSS_SetSoundLoop(g_CurrentUnitMoveSoundHandle, v30, -1);
      }
    }
    else if ( !(a3 % 4) )
    {
      if ( a4 != g_CurrentUnitMoveSoundTypeId )
      {
        g_CurrentUnitMoveSoundTypeId = a4;
        g_CurrentUnitMoveSoundVariant = 0;
      }
      CSS_StopSound(g_CurrentUnitMoveSoundHandle, 0);
      qmemcpy(v27, aSfxRuchy_2, sizeof(v27));
      v13 = (&g_UnitMoveSoundStems)[22 * a4];
      v14 = &v27[strlen(v27)];
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
      if ( (g_UnitTypeFlags[22 * a4] & 1) != 0 )
      {
        v17 = v32;
        v32[1] = HIBYTE(g_BattleMapUnitMoveSoundSuffixCode);
        v32[0] = g_CurrentUnitMoveSoundVariant + 49;
      }
      else
      {
        strcpy(v31, "d0");
        v31[1] = g_CurrentUnitMoveSoundVariant + 49;
        v26 = BattleMap_GetMoveSoundSurfaceClass(a1, v29);
        if ( v26 )
        {
          if ( v26 <= 1 )
          {
            v31[0] = 116;
            v17 = v31;
          }
          else
          {
            if ( v26 == 2 )
              v31[0] = 100;
            v17 = v31;
          }
        }
        else
        {
          v31[0] = 112;
          v17 = v31;
        }
      }
      v18 = &v27[strlen(v27)];
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
      v21 = 88 * a4;
      v22 = a_wav_2;
      v23 = &v27[strlen(v27)];
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
      g_CurrentUnitMoveSoundHandle = CSS_PlaySound((int)v27, (unsigned __int8)g_UnitMoveSoundBaseVolumes[v21], 0, 0);
      g_CurrentUnitMoveSoundVariant = (g_CurrentUnitMoveSoundVariant + 1) % (unsigned __int8)g_UnitMoveSoundVariantCounts[v21];
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
  char *v1; // esi
  char *v2; // edi
  char v3; // al
  char v4; // al
  char *v5; // esi
  char *v6; // edi
  char v7; // al
  char v8; // al
  char v9[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    qmemcpy(v9, aSfxButtons, sizeof(v9));
    v1 = result;
    v2 = &v9[strlen(v9)];
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
    v5 = a_wav_3;
    v6 = &v9[strlen(v9)];
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
    return (char *)CSS_PlaySound((int)v9, 32, 0, 0);
  }
  return result;
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00442680) --------------------------------------------------------
int  Audio_PlayArtifactSound(int result)
{
  _BYTE v1[100]; // [esp+0h] [ebp-64h] BYREF

  if ( g_UnitSoundsEnabled )
  {
    sprintf_(v1, "sfx\\artefakt\\%d.wav", result);
    return CSS_PlaySound((int)v1, 64, 0, 0);
  }
  return result;
}
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (004426C0) --------------------------------------------------------
int  Audio_PlaySoundEffectByName(char *a1, int a2)
{
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  char v11[100]; // [esp+0h] [ebp-64h] BYREF

  if ( !g_UnitSoundsEnabled )
    return 0;
  qmemcpy(v11, aSfx, sizeof(v11));
  v4 = &v11[strlen(v11)];
  do
  {
    v5 = *a1;
    *v4 = *a1;
    if ( !v5 )
      break;
    v6 = a1[1];
    a1 += 2;
    v4[1] = v6;
    v4 += 2;
  }
  while ( v6 );
  v7 = a_wav_4;
  v8 = &v11[strlen(v11)];
  do
  {
    v9 = *v7;
    *v8 = *v7;
    if ( !v9 )
      break;
    v10 = v7[1];
    v7 += 2;
    v8[1] = v10;
    v8 += 2;
  }
  while ( v10 );
  return CSS_PlaySound((int)v11, a2, 0, 0);
}
// 5174D4: using guessed type int g_UnitSoundsEnabled;

//----- (00442760) --------------------------------------------------------
int  FileSystem_InitRootMount(int a1, char a2, DWORD a3)
{
  const char **filesystem_root; // eax

  filesystem_root = FileSystem_DiskMountCreate(a1, a2, a3);
  FileSystem_ConstructMountTable((int)&dword_543CC8, (int)filesystem_root, 0, a3);
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
int  FileSystem_ResolveReadPath(char *a1, int a2)
{
  int v3; // esi
  char v13[100]; // [esp+0h] [ebp-7Ch] BYREF
  int v14; // [esp+64h] [ebp-18h]

  v14 = a2;
  dword_54DD08 = 6;
  v3 = Compat_FileSystemQuery((int)&dword_543CC8, a1, 0, FileSystem_TryOpenEntryCallback);
  if ( !v3 )
  {
    strcpy(v13, aCClash);
    strcat(v13, a1);
    dword_54DD08 = 6;
    v3 = Compat_FileSystemQuery((int)&dword_543CC8, v13, 0, FileSystem_TryOpenEntryCallback);
    if ( !v3 && v14 )
      App_RequestQuit((int)aIOCouldnTOpenF);
  }
  return v3;
}
// 54DD08: using guessed type int dword_54DD08;

//----- (00442990) --------------------------------------------------------
char  FileSystem_SetInstallRootPath(char *a1)
{
  char *v1; // edi
  char result; // al

  v1 = aCClash;
  do
  {
    result = *a1;
    *v1 = *a1;
    if ( !result )
      break;
    result = a1[1];
    a1 += 2;
    v1[1] = result;
    v1 += 2;
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
int  FileSystem_MountArchiveAtIndex(int a1, const CHAR *a2, DWORD a3)
{
  int v3; // eax
  unsigned int v4; // eax
  int *v5; // eax
  char v21[100]; // [esp+0h] [ebp-88h] BYREF
  int v22[4]; // [esp+64h] [ebp-24h]

  v3 = Compat_CanOpenReadPath(a2);
  if ( v3 )
  {
    Compat_CopyPrefixN(v21, a2, (unsigned int)strlen(a2) + 1);
  }
  else
  {
    Compat_CopyPrefixN(v21, aCClash, (unsigned int)strlen(aCClash) + 1);
    v4 = (unsigned int)strlen(v21) + 1;
    Compat_CopyPrefixN(&v21[v4 - 1], a2, (unsigned int)strlen(a2) + 1);
    v3 = Compat_CanOpenReadPath(v21);
    if ( !v3 )
    {
      v22[0] = (int)g_ArchiveMountFailedErrorText[0];
      v22[1] = (int)g_ArchiveMountFailedErrorText[1];
      v22[2] = (int)g_ArchiveMountFailedErrorText[2];
      v22[3] = (int)g_ArchiveMountFailedErrorText[3];
      App_RequestQuit(v22[(unsigned __int8)g_LanguageIndex]);
    }
  }
  v5 = File_AllocateReadOnlySource(v21, a3, 0, a3, (int)v21);
  return FileSystem_AddMountEntry(dword_543CC8, (const CHAR *)(uintptr_t)(unsigned int)a1, 0, (DWORD)v5);
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
  CSS_SetFileSystem((int)dword_543CC8);
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
int  loadFileSusp(char *a1, const CHAR *a2)
{
  unsigned char *copy_buffer;
  int query_handle;
  int output_handle;
  int bytes_read;

  copy_buffer = (unsigned char *)(uintptr_t)(unsigned int)nmalloc_(0x80000, 4);
  if ( !copy_buffer )
  {
    Debug_Log(0, (char)a1, (DWORD)a2, (int)aNotEnoughMe_11);
    App_RequestQuit((int)aNotEnoughMe_12);
  }
  query_handle = FileSystem_ResolveReadPath(a1, 1);
  if ( !query_handle )
    App_RequestQuit((int)aBrakPlikuS);

  output_handle = IO_FOpen(a2, (unsigned __int8 *)aWb_2, 0, (DWORD)a2);
  do
  {
    bytes_read = Compat_QueryRead(query_handle, copy_buffer, 0x80000);
    if ( bytes_read )
      fwrite_(copy_buffer, bytes_read, output_handle, 1);
  }
  while ( bytes_read == 0x80000 );
  Compat_FileSystemQueryRelease((int)&dword_543CC8, &query_handle);
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
    if ( rowIndex >= *(_DWORD *)(gameData + 140000) )
      return result;
    columnIndex = 0;
    for ( tileStride = 0; ; tileStride += 14 )
    {
      if ( columnIndex >= *(_DWORD *)(gameData + 140004) )
      {
        rowOffset += 1400;
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
    shoreTileId = *(unsigned __int16 *)(portColumnOffset + gameData + 1400 * PORT_ROW + 2);
    if ( shoreTileId == 726 || shoreTileId == 722 )
    {
      bottomRightTile = (_WORD *)(14 * (PORT_COLUMN + 1) + gameData + 1400 * (PORT_ROW + 1));
      *bottomRightTile = 715;
      *(_WORD *)(gameData + 1400 * (PORT_ROW + 1) + 14 * PORT_COLUMN) = *bottomRightTile;
    }
    else
    {
      bottomLeftTile = (_WORD *)(1400 * (PORT_ROW + 1) + gameData + portColumnOffset);
      *bottomLeftTile = 715;
      *(_WORD *)(14 * PORT_COLUMN + gameData + 1400 * PORT_ROW) = *bottomLeftTile;
    }
    Port_UpdateShorelineVariantTiles();
    Rules_LogPortLocation();
    rowOffset += 1400;
    ++rowIndex;
  }
}
// 5202E4: using guessed type int gameData;

//----- (00442F60) --------------------------------------------------------
_DWORD *Rules_LogPortLocation()
{
  _DWORD *result; // eax
  int v2; // edx
  double v3; // st7
  int v4; // ecx
  char v5[204]; // [esp+0h] [ebp-CCh] BYREF

  result = (_DWORD *)gameData;
  v2 = PORT_ROW;
  if ( v2 != -1 )
  {
    v3 = sprintf_(v5, "(port %d %d)", v2, PORT_COLUMN);
    return Rules_Log(v5, v4, v3);
  }
  return result;
}
// 442F9E: variable 'v4' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 5202E4: using guessed type int gameData;

//----- (00442FB0) --------------------------------------------------------
int  Port_NewTurn(DWORD a1)
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
      if ( *(unsigned __int16 *)(gameData + 140022) >= reinforcementArrivalTurn )
      {
      PORT_SHORE_VARIANT_FLAG = 1;
      PORT_REINFORCEMENT_READY_FLAG = PORT_SHORE_VARIANT_FLAG;
        PORT_REINFORCEMENT_UNIT_COUNT = Rng_RandRange(3, 5);
        Debug_Log(logArg, reinforcementArrivalTurn, a1, (int)aPort_newturnPo);
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
  int v1; // edx
  int v2; // ebp
  int v3; // edx
  int v4; // ecx
  int v5; // eax
  int v6; // ebp
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int i; // [esp+0h] [ebp-1Ch]
  int j; // [esp+4h] [ebp-18h]

  result = gameData;
  v1 = PORT_ROW;
  if ( v1 != -1 )
  {
    if ( PORT_SHORE_VARIANT_FLAG )
    {
      v2 = PORT_ROW;
      for ( i = 1400 * v1; ; i += 1400 )
      {
        result = PORT_ROW + 1;
        if ( v2 > result )
          break;
        v3 = PORT_COLUMN;
        v4 = 14 * v3;
        while ( v3 <= PORT_COLUMN + 1 )
        {
          v5 = v4 + i + gameData;
          switch ( *(_WORD *)(v5 + 2) )
          {
            case 0x2D0:
              *(_WORD *)(v5 + 2) = 718;
              break;
            case 0x2D1:
              *(_WORD *)(v5 + 2) = 719;
              break;
            case 0x2D6:
              *(_WORD *)(v5 + 2) = 722;
              break;
            case 0x2D7:
              *(_WORD *)(v5 + 2) = 724;
              break;
            default:
              break;
          }
          v4 += 14;
          ++v3;
        }
        ++v2;
      }
    }
    else
    {
      v6 = PORT_ROW;
      for ( j = 1400 * v1; ; j += 1400 )
      {
        result = PORT_ROW + 1;
        if ( v6 > result )
          break;
        v7 = PORT_COLUMN;
        v8 = 14 * v7;
        while ( v7 <= PORT_COLUMN + 1 )
        {
          v9 = v8 + j + gameData;
          switch ( *(_WORD *)(v9 + 2) )
          {
            case 0x2CE:
              *(_WORD *)(v9 + 2) = 720;
              break;
            case 0x2CF:
              *(_WORD *)(v9 + 2) = 721;
              break;
            case 0x2D2:
              *(_WORD *)(v9 + 2) = 726;
              break;
            case 0x2D4:
              *(_WORD *)(v9 + 2) = 727;
              break;
            default:
              break;
          }
          v8 += 14;
          ++v7;
        }
        ++v6;
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
int * Port_GenerateApproachTrack(int a1)
{
  int v1; // ecx
  int v2; // ebp
  int v4; // edi
  int v5; // edx
  int v6; // ecx
  int v7; // edx
  __int16 v8; // ax
  int v9; // ebx
  int *v10; // ecx
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
  int v30; // [esp+10h] [ebp-20h]
  int v31; // [esp+14h] [ebp-1Ch]
  int v33; // [esp+20h] [ebp-10h]

  v1 = PORT_ROW;
  if ( v1 == -1 )
    return 0;
  v2 = PORT_ROW;
  v33 = PORT_COLUMN;
  v30 = 1400 * v1;
  v4 = 1400 * v1 + gameData;
  v26 = *(_WORD *)(v4 + 14 * v33);
  v5 = 1400 * (v1 + 1) + gameData;
  v6 = 1400 * (v1 + 1);
  v27 = *(_WORD *)(v5 + 14 * v33);
  v31 = v5;
  v7 = 14 * (v33 + 1);
  v28 = *(_WORD *)(v7 + v4);
  v8 = *(_WORD *)(v7 + v31);
  *(_WORD *)(v4 + 14 * v33) = 0;
  v29 = v8;
  *(_WORD *)(14 * v33 + v6 + gameData) = 0;
  *(_WORD *)(v7 + v30 + gameData) = 0;
  *(_WORD *)(v7 + v6 + gameData) = 0;
  v9 = *(__int16 *)(gameData + 725 * a1 + 147176);
  v10 = Unit_MoveTrack(a1, *(__int16 *)(gameData + 725 * a1 + 147174), v2, v9, v2, v33);
  if ( v10 )
  {
    v11 = (int *)Mem_Alloc(404, (int)v10, v9, v2);
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
        if ( v2 > (unsigned __int8)v22 )
          break;
        if ( (unsigned __int8)v22 > v2 + 1 )
          break;
        if ( BYTE1(v22) < v33 )
          break;
        if ( BYTE1(v22) > v33 + 1 )
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
  v18 = 1400 * v2;
  v19 = 14 * v33;
  *(_WORD *)(v19 + gameData + 1400 * v2) = v26;
  v20 = 1400 * (v2 + 1);
  *(_WORD *)(v20 + gameData + v19) = v27;
  v21 = 14 * (v33 + 1);
  *(_WORD *)(v21 + gameData + v18) = v28;
  *(_WORD *)(v20 + gameData + v21) = v29;
  return v10;
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
  int v6; // edi
  int i; // esi
  int v8; // ebx
  int v9; // ecx
  int v10; // eax
  DWORD v11; // ebp
  char v12; // bl
  int v13; // ecx
  int v14; // edx
  int v15; // esi
  signed int j; // edi
  unsigned int v17; // eax
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
  int v32; // [esp+Ch] [ebp-30h]
  int v33; // [esp+10h] [ebp-2Ch]
  int v34; // [esp+18h] [ebp-24h]
  int v35; // [esp+1Ch] [ebp-20h]
  int v36; // [esp+20h] [ebp-1Ch]

  Debug_Log(a1, a2, a3, (int)aPort_getsupply, v28);
  if ( PORT_ROW == -1 )
    return 0;
  v32 = PORT_ROW;
  v33 = PORT_COLUMN;
  result = Port_IsReinforcementReady();
  if ( result )
  {
    v31 = 0;
    v35 = v5 - 1;
    v30 = v33 - 1;
    v36 = 200 * (v5 - 1);
    if ( v36 <= 200 * (v5 + 2) )
    {
      v34 = 2 * (v33 + 2);
      do
      {
        v25 = 2 * v30;
        if ( 2 * v30 <= v34 )
        {
          while ( 1 )
          {
            v26 = *(unsigned __int16 *)(gameData + v36 + v25 + 556374);
            if ( (unsigned __int16)v26 <= 0x1F4u )
            {
              v27 = 725 * v26;
              if ( (unsigned int)*(__int16 *)(v27 + gameData + 147174 + 6) <= 0x28
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
      v6 = 0;
      for ( i = 0; i < 12; ++i )
      {
        v8 = g_PortReinforcementSpawnRingOffsets[i].row_delta + v32;
        v9 = g_PortReinforcementSpawnRingOffsets[i].column_delta + v33;
        if ( *(unsigned __int16 *)(TILE_INDEX(v8, v9)) == 0xFFFF
          && Map_GetUnitTileMoveCostOrZero(g_CurrentPlayerIndex, 0, v9, v8) )
        {
          break;
        }
        ++v6;
      }
      if ( v6 == 12 )
        return 0;
      v29 = g_PortReinforcementSpawnRingOffsets[v6].column_delta + PORT_COLUMN;
      v10 = g_PortReinforcementSpawnRingOffsets[v6].row_delta;
      v11 = v10 + PORT_ROW;
      v12 = Facing_DirectionFromDelta8(v10, g_PortReinforcementSpawnRingOffsets[v6].column_delta);
      Unit_Create(UNIT_TYPE_PEASANT, g_CurrentPlayerIndex, v11, v12, a4, v29);
      v14 = 145 * *(unsigned __int16 *)(TILE_INDEX(v11, v29));
      v15 = PORT_REINFORCEMENT_UNIT_COUNT - 1;
      for ( j = 725 * *(unsigned __int16 *)(TILE_INDEX(v11, v29)) + gameData + 147174;
            v15 >= 0;
            v13 = v19 - 31 )
      {
        v12 = g_CurrentPlayerIndex;
        v17 = Rng_RandRange(0, 11);
        --v15;
        UnitSlot_InitFromType(v18, g_PortReinforcementUnitTypePool[v17], v12);
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
  char *v11; // eax
  __int16 v12; // ax
  void *result; // eax
  unsigned __int16 v14; // [esp+10h] [ebp-4Ch]
  unsigned __int16 v15; // [esp+10h] [ebp-4Ch]
  unsigned __int16 v16; // [esp+14h] [ebp-48h]
  unsigned __int16 v17; // [esp+18h] [ebp-44h]
  int v18[3]; // [esp+1Ch] [ebp-40h]
  int v19[3]; // [esp+28h] [ebp-34h] BYREF
  _DWORD *v20; // [esp+34h] [ebp-28h] BYREF
  void *v21; // [esp+38h] [ebp-24h]
  int v22; // [esp+3Ch] [ebp-20h]
  int v23; // [esp+40h] [ebp-1Ch]

  v21 = g_RenderDevice;
  g_RenderDevice = &unk_51D4C0;
  Render_Pump();
  v3 = (_DWORD *)Mem_Alloc(4112, v2, a1, a2);
  if ( v3 )
    v3 = DLXSpriteSet_Load(v3, "port.s32");
  v20 = v3;
  v22 = 100;
  v23 = 100;
  Surface = (_DWORD *)Mem_Alloc(188, 100, a1, a2);
  v5 = (int)Surface;
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)v20, 0);
    SpriteHeight = DLX_GetSpriteHeight((int)v20, 0);
    Surface = Render_CreateSurface(v5, SpriteHeight, SpriteWidth);
  }
  v8 = (DWORD)Surface;
  v14 = v23 + DLX_GetSpriteWidth((int)v20, 0) - 1;
  v9 = DLX_GetSpriteHeight((int)v20, 0);
  Render_FillRect(0, (_DWORD *)v8, (unsigned __int16)v23, (unsigned __int16)v22, v22 + v9 - 1, v14, 0, 0);
  Render_ReleaseSurface(7, v8);
  SpriteForChar = DLX_GetSpriteForChar((int)v20, PORT_REINFORCEMENT_READY_FLAG);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    v23,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  if ( g_LanguageIndex == 2 )
    v11 = aHafen;
  else
    v11 = aPort;
  UI_DrawTextFmt((int)v19, v22 + 10, v22 + 235, v23 + 5, 3, (int)v11);
  v19[0] = (int)g_PortReinforcementArrivedTexts[0];
  v19[1] = (int)g_PortReinforcementArrivedTexts[1];
  v19[2] = (int)g_PortReinforcementArrivedTexts[2];
  v18[0] = (int)g_PortEmptyTexts[0];
  v18[1] = (int)g_PortEmptyTexts[1];
  v18[2] = (int)g_PortEmptyTexts[2];
  if ( PORT_REINFORCEMENT_READY_FLAG )
  {
    UI_DrawTextFmt((int)v19, v22 + 122, v22 + 200, v23 + 54, 6, v19[(unsigned __int8)g_LanguageIndex]);
    Render_ReleaseSurface(15, v8);
    UI_DrawTextFmt((int)v19, v22 + 42, v22 + 85, v23 + 29, 1, (int)aD_36);
  }
  else
  {
    UI_DrawTextFmt(
      v18[(unsigned __int8)g_LanguageIndex],
      v22 + 40,
      v22 + 120,
      v23 + 40,
      6,
      v18[(unsigned __int8)g_LanguageIndex]);
  }
  Render_Begin((int)g_RenderState, 0);
  v17 = v23;
  v16 = v22;
  v15 = DLX_GetSpriteWidth((int)v20, 0) - 1;
  v12 = DLX_GetSpriteHeight((int)v20, 0);
  Render_FillRect((_DWORD *)v8, 0, 0, 0, v12 - 1, v15, v16, v17);
  if ( v8 )
    (**(void (__cdecl ***)(int, int, int, int, int, int))(v8 + 184))(v18[0], v18[1], v18[2], v19[0], v19[1], v19[2]);
  DLXSpriteSet_ReleaseAndClear((int *)&v20);
  Render_Present((int)g_RenderState);
  result = v21;
  g_RenderDevice = v21;
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
    if ( i >= *(_DWORD *)(gameData + 140000) )
      break;
    for ( j = 0; j < *(_DWORD *)(gameData + 140004); j = v4 + 1 )
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
BOOL  MapTile_HasHiddenTreasure(int a1, int a2)
{
  int v2; // eax

  v2 = *(unsigned __int16 *)(gameData + 1400 * a1 + 14 * a2);
  return v2 == 755 || v2 == 752;
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
  int v7; // edx
  __int16 *v8; // ebp
  int v9; // ecx
  int v11; // ecx
  _BYTE *v12; // ecx
  _DWORD *v13; // ecx
  unsigned __int16 *v14; // edx
  unsigned __int16 v15; // ax
  DWORD *v16; // ecx
  void *v17; // eax
  int v18; // eax
  _BYTE v19[24]; // [esp+0h] [ebp-40h] BYREF
  _BYTE v20[40]; // [esp+18h] [ebp-28h] BYREF

  Debug_Log(a1, a2, a3, (int)aTreasure_dighe, a1);
  v6 = gameData;
  v8 = (__int16 *)(725 * v7 + gameData + 147174);
  if ( !MapTile_HasHiddenTreasure(*(__int16 *)(gameData + 725 * v7 + 147174), *(__int16 *)(gameData + 725 * v7 + 147176))
    || !UnitStack_HasBuilder(v9) )
  {
    return 0;
  }
  if ( ACTIVE_MISSION_INDEX == 7
    && (*v8 == 55 && v8[1] == 45 || *v8 == 50 && v8[1] == 27 || *v8 == 35 && v8[1] == 63 || *v8 == 14 && v8[1] == 68) )
  {
    qmemcpy(v20, &g_Mission7ScriptedTreasureEventData, 0x18u);
    a5 = (char *)&g_Mission7ScriptedTreasureEventData + 24;
    v12 = v20;
  }
  else if ( ACTIVE_MISSION_INDEX == 17
         && (*v8 == 50 && v8[1] == 34 || *v8 == 51 && v8[1] == 73
                                      || *v8 == 77 && v8[1] == 34
                                      || *v8 == 24 && v8[1] == 49) )
  {
    qmemcpy(v19, &g_Mission17ScriptedTreasureEventData, sizeof(v19));
    a5 = (char *)&g_Mission17ScriptedTreasureEventData + 24;
    v12 = v19;
  }
  else
  {
    if ( *(_DWORD *)(1423 * *((unsigned __int8 *)v8 + 4) + gameData + 140051) )
      v17 = &g_TreasureDigOutcomeTable_TempleActive;
    else
      v17 = &g_TreasureDigOutcomeTable_TempleInactive;
    v18 = Temple_Random((int)v17, v11, v6, (DWORD)v8, a4);
    Debug_Log(v18, v6, (DWORD)v8, (int)aTreasure_dig_0, v18);
  }
  if ( *(_DWORD *)(gameData + 1423 * *((unsigned __int8 *)v8 + 4) + 140051) )
  {
    Win_PlayModeChangeFrameTransition((int)aKop_bud, 1, (int)v12, v6, (DWORD)v8, (char)a5);
    Temple_ShowOutcomePopup(v13[(unsigned __int8)g_LanguageIndex + 3], v13[2], (int)v13, *v13 != 15, (DWORD)v8);
  }
  v14 = (unsigned __int16 *)(1400 * *v8 + gameData + 14 * v8[1]);
  v15 = *v14;
  if ( *v14 >= 0x2F0u )
  {
    if ( v15 > 0x2F0u )
    {
      if ( v15 == 755 )
        *v14 = 4;
    }
    else
    {
      *v14 = 0;
    }
  }
  Rules_RetractTreasureFact(*v8, v8[1], a6);
  Temple_ProcessGift(*v16, (int)v8, v8[1], *v8, a6);
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
signed int  UnitStack_TryHide(int a1, unsigned __int16 a2, DWORD a3, double a4)
{
  __int16 *v4; // esi
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
  int v16[3]; // [esp+0h] [ebp-3Ch]
  int v17[3]; // [esp+Ch] [ebp-30h] BYREF
  int v18; // [esp+18h] [ebp-24h] BYREF
  int v19; // [esp+1Ch] [ebp-20h]
  int v20; // [esp+20h] [ebp-1Ch]

  v4 = (__int16 *)(gameData + 147174 + 725 * a1);
  if ( UnitStack_GetMinCurrentActionPoints((intptr_t)v4) < 0 || *((_BYTE *)v4 + 720) || !UnitStack_HasNormalCombatUnits((intptr_t)v4) )
    return 0;
  if ( UnitStack_GetMaxOrderTier((intptr_t)v4) < 2 )
  {
    if ( *(_DWORD *)(1423 * *((unsigned __int8 *)v4 + 4) + gameData + 140051) )
    {
      v16[0] = (int)g_UnitHideFailedLowRankText[0];
      v16[1] = (int)g_UnitHideFailedLowRankText[1];
      v16[2] = (int)g_UnitHideFailedLowRankText[2];
      Audio_PlaySoundEffectByName(aWrong_0, 64);
      UI_ShowInfoWindow(v16[(unsigned __int8)g_LanguageIndex], 1u, v6, a3, (int)v17, (int)&g_UnitHideFailedLowRankText[3]);
      return 0;
    }
    return 0;
  }
  v18 = 0;
  v20 = -8;
  do
  {
    v7 = -8;
    v19 = v20 * v20;
    while ( 1 )
    {
      if ( Math_CeilSqrt(v19 + v7 * v7) <= 8 )
      {
        a2 = *(_WORD *)(gameData + 200 * (v8 + *v4) + 2 * (v20 + v4[1]) + 556374);
        if ( a2 != 0xFFFF )
        {
          if ( a2 <= 0x1F4u )
          {
            v9 = 725 * a2;
            if ( (unsigned int)*(__int16 *)(gameData + 147174 + v9 + 6) <= 0x28
              && *(_BYTE *)(gameData + v9 + 147178) != *((_BYTE *)v4 + 4) )
            {
              break;
            }
          }
          v11 = a2 - 0x8000;
          if ( v11 <= 0x64 )
          {
            v12 = 467 * v11;
            LOBYTE(a2) = gameData;
            v13 = v12 + gameData + 509674;
            if ( (unsigned int)*(char *)(v13 + 4) < 4
              && *(__int16 *)(v13 + 16) != -1
              && *(_BYTE *)(gameData + v12 + 509676) != *((_BYTE *)v4 + 4) )
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
    v18 = 1;
LABEL_16:
    ++v20;
  }
  while ( v20 < 8 );
  if ( v18 )
  {
    if ( !*(_DWORD *)(1423 * *((unsigned __int8 *)v4 + 4) + gameData + 140051) )
      return 0;
    v17[0] = (int)g_UnitHideFailedNoSpotText[0];
    v17[1] = (int)g_UnitHideFailedNoSpotText[1];
    v17[2] = (int)g_UnitHideFailedNoSpotText[2];
    Audio_PlaySoundEffectByName(aWrong_1, 64);
    UI_ShowInfoWindow(v17[(unsigned __int8)g_LanguageIndex], 0, v10, 0, (int)&v18, (int)&g_UnitHideFailedNoSpotText[3]);
    return 0;
  }
  else
  {
    UnitStack_ClearRemainingActionPoints(v4, 0, a4);
    v15 = 1423 * *((unsigned __int8 *)v4 + 4);
    *((_BYTE *)v4 + 720) = 1;
    if ( *(_DWORD *)(gameData + v15 + 140051) )
      Win_PlayModeChangeFrameTransition(aUkrycie, 1, v14, a2, 0);
    WorldMap_RedrawTileIfVisible(*v4, v4[1]);
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
signed int  UnitStack_RevealHiddenEnemiesAndAttackAdjacent(unsigned int a1, double a2)
{
  __int16 *stack; // ebx
  int result; // [esp+8h] [ebp-2Ch]
  int neighbor_index;

  if ( a1 > 0x1F4 )
    return 0;
  stack = (__int16 *)UNIT_STACK(a1);
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
        Unit_Attack(adjacent_stack_index, a1, (char)stack, 1u, a2);
        UnitStack_ClearRemainingActionPoints(stack, 1u, a2);
        *((_BYTE *)adjacent_stack + 720) = 0;
        result = 1;
        WorldMap_RedrawViewport(1);
      }
    }
    if ( a1 > 0x1F4 )
      break;
    if ( (unsigned int)*(__int16 *)(UNIT_STACK(a1) + 6) > 0x28 )
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
int  SaveSlot_FormatDataFilePath(int a1, char *a2)
{
  return sprintf_(a2, "save\\%d.dat", a1);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004443D0) --------------------------------------------------------
int  SaveSlot_FormatFactsFilePath(int a1, char *a2)
{
  return sprintf_(a2, "save\\%d.fac", a1);
}
// 4761CE: using guessed type _DWORD sprintf_(_DWORD, const char *, ...);

//----- (004443E0) --------------------------------------------------------
signed int  saveGame(int a1, DWORD a2, double a3)
{
  int v5; // ecx
  int v6; // esi
  int v7; // ecx
  int v8; // edx
  CHAR v10[120]; // [esp+0h] [ebp-78h] BYREF

  SaveSlot_FormatDataFilePath(a1, v10);
  PLAYER_CAMERA_LEFT(VIEWED_PLAYER_INDEX) = MAP_VIEW_LEFT;
  PLAYER_CAMERA_TOP(VIEWED_PLAYER_INDEX) = MAP_VIEW_TOP;
  v6 = IO_FOpen(v10, (unsigned __int8 *)aWb_4, v5, a2);
  fwrite_((const void *)a2, 16, v6, 1);
  fwrite_((const void *)gameData, 586398, v6, 1);
  fclose_(v7);
  SaveSlot_FormatFactsFilePath(a1, v10);
  return Rules_SaveFactsToFile(v10, 2, 0, a3);
}
// 44443B: variable 'v5' is possibly undefined
// 44446A: variable 'v7' is possibly undefined
// 444473: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5202E4: using guessed type int gameData;

//----- (00444490) --------------------------------------------------------
signed int  SaveSlot_LoadGame(int a1, DWORD a2, double a3)
{
  int file_handle; // eax
  int trace_load_save; // eax
  int stack_index; // ecx
  int slot_index; // edx
  int building_index; // edx
  int unit_record_index; // ecx
  int unit_record; // edx
  CHAR v19[120]; // [esp+0h] [ebp-78h] BYREF

  trace_load_save = 0;
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-enter\n");
  SaveSlot_FormatDataFilePath(a1, v19);
  if ( trace_load_save )
    fprintf(stderr, "[menu-probe] load-save-path %s\n", v19);
  file_handle = IO_FOpen(v19, (unsigned __int8 *)aRb_5, 0, a2);
  if ( file_handle )
  {
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-file-opened handle=%d\n", file_handle);
    IO_SeekStreamGuarded(file_handle, 16, 1u, a1);
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
      if ( (unsigned int)*(__int16 *)(gameData + 725 * stack_index + 147180) <= 0x28 )
      {
        if ( trace_load_save )
          fprintf(
            stderr,
            "[menu-probe] load-save-link-army stack=%d type=%d x=%d y=%d owner=%u\n",
            stack_index,
            *(unsigned __int16 *)(gameData + 725 * stack_index + 147180),
            *(__int16 *)(gameData + 725 * stack_index + 147174),
            *(__int16 *)(gameData + 725 * stack_index + 147176),
            *(unsigned __int8 *)(gameData + 725 * stack_index + 147178));
        UnitStack_LinkArmyFact((__int16 *)(gameData + 147174 + 725 * stack_index), 1, a2);
      }
      for ( slot_index = 0; slot_index < 10; ++slot_index )
      {
        *(_DWORD *)(gameData + 725 * stack_index + 31 * slot_index + 147198) = 0;
      }
    }
    if ( trace_load_save )
      fprintf(stderr, "[menu-probe] load-save-after-army-loop\n");
    for ( building_index = 0; building_index < *(_DWORD *)(gameData + 140000); ++building_index )
    {
      for ( slot_index = 0; slot_index < *(_DWORD *)(gameData + 140004); ++slot_index )
      {
        *(_DWORD *)(14 * slot_index + 1400 * building_index + gameData + 6) = 0;
        *(_DWORD *)(14 * slot_index + 1400 * building_index + gameData + 10) = 0;
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
    SaveSlot_FormatFactsFilePath(a1, v19);
    Rules_LoadFactsFromFile(v19, 0, a2, a3);
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
char  SaveSlot_LoadLabelOrPlaceholder(int a1, char *a2, DWORD a3)
{
  int file_handle; // eax
  char result; // al
  char *v8; // esi
  CHAR v9[108]; // [esp+0h] [ebp-6Ch] BYREF

  snprintf(v9, sizeof(v9), "save\\%d.dat", a1);
  file_handle = IO_FOpen(v9, (unsigned __int8 *)aRb_7, 0, a3);
  if ( file_handle )
  {
    fread_(a2, 1, file_handle, 16);
    a2[16] = 0;
    return fclose_(file_handle);
  }
  else
  {
    v8 = asc_4F94BB;
    do
    {
      result = *v8;
      *a2 = *v8;
      if ( !result )
        break;
      result = v8[1];
      v8 += 2;
      a2[1] = result;
      a2 += 2;
    }
    while ( result );
  }
  return result;
}
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);

//----- (00444750) --------------------------------------------------------
int  SaveSlot_HasDataFile(int a1, DWORD a2)
{
  int file_handle; // eax
  int result; // eax
  CHAR v5[104]; // [esp-68h] [ebp-68h] BYREF

  snprintf(v5, sizeof(v5), "save\\%d.dat", a1);
  file_handle = IO_FOpen(v5, (unsigned __int8 *)aRb_8, 0, a2);
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
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  int v7; // edi
  unsigned __int16 v8; // si
  int v9; // eax
  int result; // eax
  char v11[20]; // [esp+0h] [ebp-30h] BYREF
  int v12; // [esp+14h] [ebp-1Ch]

  v12 = a1;
  v2 = g_RenderDevice;
  if ( dword_543D1C && a1 == dword_543D18 )
  {
    v3 = byte_543D28;
    v4 = v11;
    do
    {
      v5 = *v3;
      *v4 = *v3;
      if ( !v5 )
        break;
      v6 = v3[1];
      v3 += 2;
      v4[1] = v6;
      v4 += 2;
    }
    while ( v6 );
  }
  else
  {
    SaveSlot_LoadLabelOrPlaceholder(v12, v11, (DWORD)g_RenderDevice);
  }
  g_RenderDevice = &unk_51D4C0;
  v7 = (unsigned __int16)(22 * v12 + 157);
  v8 = 22 * v12 + 137;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xF4u, 0x1A4u, v8, v7);
  Render_FillRect((_DWORD *)dword_5202E0, 0, v8, 244, 0x1A4u, v7, 0xF4u, v8);
  if ( v12 == dword_543D18 )
    v9 = 18;
  else
    v9 = 21;
  Render_ReleaseSurface(v9, (DWORD)v2);
  if ( dword_543D1C )
    UI_SetTextCursorPosition(dword_543D24);
  UI_DrawTextFmt(v7, 244, 410, 22 * v12 + 137, 3, (int)v11);
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
  dword_543D20 = -1;
  dword_543D14 = 1;
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
  if ( dword_543D1C && dword_543D18 != -1 )
  {
    result = saveGame(dword_543D18, (DWORD)byte_543D28, a4);
    dword_543D14 = 1;
    goto LABEL_6;
  }
  result = SaveSlot_HasDataFile(dword_543D18, a3);
  if ( !result )
  {
LABEL_6:
    g_RenderDevice = v6;
    return result;
  }
  result = dword_543D18;
  dword_543D20 = dword_543D18;
  dword_543D14 = 1;
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
  unsigned int v18; // eax
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  const char *v26; // edi
  unsigned int v27; // kr0C_4
  int v28; // edx
  int v29; // ecx
  int v30; // ecx
  unsigned int v31; // eax
  char *v32; // esi
  char *v33; // edi
  char v34; // al
  char v35; // al
  int v36; // edx
  int v37; // edx
  _DWORD v38[40]; // [esp+2Ch] [ebp-E0h] BYREF
  char v39[20]; // [esp+CCh] [ebp-40h] BYREF
  _DWORD *v40; // [esp+E0h] [ebp-2Ch] BYREF
  int v41; // [esp+E4h] [ebp-28h]
  int (*v42)(); // [esp+E8h] [ebp-24h]
  int v43; // [esp+ECh] [ebp-20h]
  char v44; // [esp+F0h] [ebp-1Ch]

  v5 = (_DWORD *)Mem_Alloc(4112, a1, a2, a3);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, a2);
  v40 = v5;
  v43 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v42 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v6, 0, a3, (int)aSetrhS08x_22);
  dword_543D1C = v7;
  dword_543D24 = 0;
  dword_543D18 = -1;
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, v8);
  dword_545150 = (int)&g_CursorDesc_Default;
  g_RenderDevice = (_UNKNOWN *)dword_5202E0;
  SpriteForChar = DLX_GetSpriteForChar((int)v40, dword_543D1C != 0);
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
  g_RenderDevice = &unk_51D4C0;
  v11 = DLX_GetSpriteForChar((int)v40, dword_543D1C != 0);
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
  v38[3] = &v40;
  *(_DWORD *)((char *)&v38[16] + 1) = &v40;
  if ( dword_543D1C )
    v13 = -1;
  else
    v13 = 4;
  LOBYTE(v14) = dword_543D1C;
  *(_DWORD *)((char *)&v38[17] + 1) = v13;
  *(_DWORD *)((char *)&v38[18] + 1) = (dword_543D1C != 0) + 2;
  g_RenderDevice = &unk_51D4C0;
  UIWidgetTable_InitDrawStates(v38);
  dword_543D14 = 0;
  Render_Present((int)g_RenderState);
  v16 = Render_SetResourceHandle((int)&unk_51D4C0, v15);
  v17 = dword_543D14;
  v41 = v16;
  while ( !dword_543D14 )
  {
    if ( dword_543D1C && dword_543D18 != -1 )
    {
      if ( Input_IsKeyPressed(203) )
      {
        LOBYTE(v14) = dword_543D24;
        if ( dword_543D24 )
        {
          --dword_543D24;
          SaveSlotDialog_RepaintRow(dword_543D18);
          Input_ClearKey(203, v23);
        }
      }
      if ( Input_IsKeyPressed(205) && strlen(byte_543D28) > dword_543D24 )
      {
        v17 = ++dword_543D24;
        SaveSlotDialog_RepaintRow(dword_543D18);
        Input_ClearKey(205, v24);
      }
      if ( Input_IsKeyPressed(211) )
      {
        LOBYTE(v14) = strlen(&byte_543D28[dword_543D24 + 1]) + 1;
        memmove_(
          &byte_543D28[dword_543D24],
          &byte_543D28[dword_543D24 + 1],
          strlen(&byte_543D28[dword_543D24 + 1]) + 1);
        SaveSlotDialog_RepaintRow(dword_543D18);
        Input_ClearKey(211, v25);
      }
      if ( Input_IsKeyPressed(14) )
      {
        LOBYTE(v14) = dword_543D24;
        if ( dword_543D24 )
        {
          v26 = &byte_543D28[dword_543D24--];
          v27 = strlen(v26) + 1;
          LOBYTE(v14) = v27;
          memmove_(&byte_543D28[dword_543D24], &byte_543D28[dword_543D24 + 1], v27);
          SaveSlotDialog_RepaintRow(dword_543D18);
          Input_ClearKey(14, v28);
        }
      }
      if ( Input_IsKeyPressed(28) )
        SaveSlotDialog_HandleConfirm(0, v29, v17, a4);
      if ( Input_IsKeyPressed(1) )
        SaveSlotDialog_HandleCancel(0, v30);
      v31 = Input_PopKey();
      v17 = v31;
      if ( v31 != -1 )
      {
        v44 = Input_KeyToChar(v31);
        if ( v44 )
        {
          if ( strlen(byte_543D28) < 0x10 )
          {
            if ( dword_543D1C )
            {
              v32 = byte_543D28;
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
              SaveSlot_LoadLabelOrPlaceholder(dword_543D18, v39, v17);
            }
            Render_ReleaseSurface(21, v17);
            if ( (unsigned __int16)Render_LoadResourceSprite_v3(v39) < 0x97u )
            {
              LOBYTE(v14) = strlen(&byte_543D28[dword_543D24]) + 1;
              memmove_(
                &byte_543D28[dword_543D24 + 1],
                &byte_543D28[dword_543D24],
                strlen(&byte_543D28[dword_543D24]) + 1);
              v36 = dword_543D24;
              byte_543D28[dword_543D24] = v44;
              dword_543D24 = v36 + 1;
              SaveSlotDialog_RepaintRow(dword_543D18);
              Input_ClearKey(v17, v37);
            }
          }
        }
      }
    }
    DD_Pump((int)g_RenderState, v14);
    if ( DD_IsFlipping((int)g_RenderState) )
    {
      if ( dword_544CFC >> byte_54512C >= 244 && dword_544CFC >> byte_54512C <= 410 )
      {
        v18 = ((dword_544D00 >> byte_54512C) - 142) / 22;
        if ( v18 <= 9 )
        {
          v14 = dword_543D18;
          if ( v18 != dword_543D18 )
          {
            dword_543D18 = ((dword_544D00 >> byte_54512C) - 142) / 22;
            dword_543D24 = 0;
            if ( v14 != -1 )
              SaveSlotDialog_RepaintRow(v14);
            if ( dword_543D1C )
            {
              SaveSlot_LoadLabelOrPlaceholder(dword_543D18, byte_543D28, v17);
              if ( !strcmp_(v19, asc_4F94C2) )
                byte_543D28[0] = 0;
            }
            SaveSlotDialog_RepaintRow(dword_543D18);
          }
          if ( RenderState_IsCursorFlipStillActive((int)g_RenderState) )
            SaveSlotDialog_HandleConfirm(0, v20, v17, a4);
        }
      }
    }
    UIWidgetTable_PollHoverAndActions(v38, v17);
  }
  Render_SetResourceHandle((int)&unk_51D4C0, v41);
  Render_Begin((int)g_RenderState, 0);
  Debug_Log(v21, v14, (DWORD)g_RenderHook, (int)aUnsetrh08x_22);
  g_RenderHook = v42;
  Render_SetResourceHandle((int)&unk_51D4C0, v43);
  DLXSpriteSet_ReleaseAndClear((int *)&v40);
  return dword_543D20;
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
        unsigned int a2,
        int a3,
        DWORD a4,
        int a5,
        int a6)
{
  DWORD v7; // ebp
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
  _DWORD *v29; // [esp+68h] [ebp-34h] BYREF
  int (*v30)(); // [esp+6Ch] [ebp-30h]
  const char *v31; // [esp+70h] [ebp-2Ch]
  _DWORD *v32; // [esp+74h] [ebp-28h]
  DWORD v33; // [esp+78h] [ebp-24h]
  int SpriteHeight; // [esp+7Ch] [ebp-20h]
  int v35; // [esp+80h] [ebp-1Ch]
  int SpriteWidth; // [esp+84h] [ebp-18h]
  int info_header_height;
  int info_footer_width;
  int info_header_width;

  v31 = a1;
  Debug_Log(a3, a2, a4, (int)aWindowmessageS);
  v35 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v30 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a2, a4, (int)aSetrhS08x_10);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  v7 = 0;
  Render_ReleaseSurface(17, 0);
  v29 = 0;
  if ( a2 )
  {
    if ( a2 <= 1 )
    {
      v19 = (_DWORD *)Mem_Alloc(4112, v8, a2, 0);
      if ( v19 )
        v19 = DLXSpriteSet_Load(v19, "pergamin.s32");
      v29 = v19;
      a6 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v19, 3u)) / 2;
      a5 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v29, 3u)) / 2;
      SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v29, 3u);
      SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v29, 3u);
      Surface = (_DWORD *)Mem_Alloc(188, v20, a2, 0);
      if ( Surface )
        Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
      v32 = Surface;
      Render_FillRect(
        0,
        Surface,
        (unsigned __int16)a6,
        (unsigned __int16)a5,
        a5 + SpriteHeight - 1,
        a6 + SpriteWidth - 1,
        0,
        0);
      g_RenderDevice = &unk_51D4C0;
      SpriteForChar = DLX_GetSpriteForChar((int)v29, 3);
      v33 = *((_DWORD *)g_RenderDevice + 46);
      v7 = v33;
      Compat_RenderDeviceDrawMenuSprite(a6, a5, SpriteForChar, 1);
      UI_DrawTextFmt(a5, a5, a5 + SpriteHeight, a6 + 18, 3, v31);
    }
    else if ( a2 == 2 )
    {
      v23 = (_DWORD *)Mem_Alloc(4112, v8, 2, 0);
      if ( v23 )
        v23 = DLXSpriteSet_Load(v23, "pergamin.s32");
      v29 = v23;
      a6 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v23, 2u)) / 2;
      a5 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v29, 2u)) / 2;
      SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v29, 2u);
      SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v29, 2u);
      v25 = (_DWORD *)Mem_Alloc(188, v24, 2, 0);
      if ( v25 )
        v25 = Render_CreateSurface((int)v25, SpriteHeight, SpriteWidth);
      v32 = v25;
      Render_FillRect(
        0,
        v25,
        (unsigned __int16)a6,
        (unsigned __int16)a5,
        a5 + SpriteHeight - 1,
        a6 + SpriteWidth - 1,
        0,
        0);
      g_RenderDevice = &unk_51D4C0;
      v26 = DLX_GetSpriteForChar((int)v29, 2);
      v7 = *((_DWORD *)g_RenderDevice + 46);
      Compat_RenderDeviceDrawMenuSprite(a6, a5, v26, 1);
      UI_DrawTextFmt(a5, a5 + 25, a5 + SpriteHeight - 25, a6 + 25, 6, v31);
    }
  }
  else
  {
    v12 = (_DWORD *)Mem_Alloc(4112, v8, 0, 0);
    if ( v12 )
      v12 = DLXSpriteSet_Load(v12, "temple.s32");
    a6 = 150;
    v29 = v12;
    info_footer_width = (unsigned __int16)DLX_GetSpriteWidth((int)v12, 0x17u);
    a5 = 0;
    info_header_width = (unsigned __int16)DLX_GetSpriteWidth((int)v29, 0x16u);
    v15 = info_footer_width + 6;
    SpriteHeight = 640;
    if ( info_header_width > info_footer_width + 6 )
      v15 = info_header_width;
    SpriteWidth = v15;
    v16 = (_DWORD *)Mem_Alloc(188, 0, 0, 0x280u);
    if ( v16 )
      v16 = Render_CreateSurface((int)v16, 640, SpriteWidth);
    v32 = v16;
    Render_FillRect(0, v16, 150, 0, 0x27Fu, SpriteWidth + 149, 0, 0);
    g_RenderDevice = &unk_51D4C0;
    v17 = DLX_GetSpriteForChar((int)v29, 22);
    Compat_RenderDeviceDrawMenuSprite(150, 0, v17, 1);
    info_header_height = (unsigned __int16)DLX_GetSpriteHeight((int)v29, 0x16u);
    v18 = DLX_GetSpriteForChar((int)v29, 23);
    v7 = *((_DWORD *)g_RenderDevice + 46);
    Compat_RenderDeviceDrawMenuSprite(156, info_header_height, v18, 1);
    UI_DrawTextFmt(0, 70, 569, 210, 6, v31);
  }
  DLXSpriteSet_ReleaseAndClear((int *)&v29);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  while ( !DD_IsFlipping((int)g_RenderState) && !DD_IsLost((int)g_RenderState) )
    DD_Pump((int)g_RenderState, 0);
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  Debug_Log((int)g_RenderHook, 0, v7, (int)aUnsetrh08x_10);
  g_RenderHook = v30;
  Render_SetResourceHandle((int)&unk_51D4C0, v35);
  if ( (uintptr_t)v32 >> 32 )
    v32 = 0;
  if ( v32 )
    Render_FillRect(v32, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, a5, a6);
  v27 = v32;
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
  int v4; // ecx
  int result; // eax
  int v6; // ecx
  int v7; // ecx
  _BYTE v8[256]; // [esp+0h] [ebp-120h] BYREF
  int v9[8]; // [esp+100h] [ebp-20h] BYREF

  result = 0;
  v9[6] = a1;
  v4 = 0;
  v9[0] = (int)g_PlagueOutbreakNoticeFmtText[0];
  v9[1] = (int)g_PlagueOutbreakNoticeFmtText[1];
  v9[2] = (int)g_PlagueOutbreakNoticeFmtText[2];
  do
  {
    result = v4 + gameData;
    if ( (*(_BYTE *)(v4 + gameData + 510109) & 7) == 5 )
    {
      result = *(unsigned __int8 *)(result + 509676);
      if ( result == g_CurrentPlayerIndex )
      {
        Diagnostics_TraceWorldMapActionEvent("plague_notice_match", v4 / 467, v4, g_CurrentPlayerIndex, 0);
        Win_PlayModeChangeFrameTransition(aZaraza, 1, v4, (char)a2, a3);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_after_transition", v4 / 467, v4, g_CurrentPlayerIndex, 0);
        a2 = (const char *)v9[(unsigned __int8)g_LanguageIndex];
        sprintf_(v8, a2, gameData + v4 + 509674 + 5);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_before_info_window", v4 / 467, v4, g_CurrentPlayerIndex, 0);
        result = UI_ShowInfoWindow((const char *)v8, 0, 0, a3, (int)&v9[3], (int)&g_PlagueOutbreakNoticeFmtText[3]);
        Diagnostics_TraceWorldMapActionEvent("plague_notice_after_info_window", v4 / 467, v4, g_CurrentPlayerIndex, result);
      }
    }
    v4 += 467;
  }
  while ( v4 != 46700 );
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
  int v4[6]; // [esp+0h] [ebp-18h] BYREF

  v4[0] = (int)g_TechLevelUpNoticeText[0];
  v4[1] = (int)g_TechLevelUpNoticeText[1];
  v4[2] = (int)g_TechLevelUpNoticeText[2];
  if ( *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_TECH_LEVEL_OFFSET) != *(_BYTE *)(PLAYER_DATA(g_CurrentPlayerIndex) + PLAYER_LAST_SHOWN_TECH_LEVEL_OFFSET) )
  {
    Diagnostics_TraceWorldMapActionEvent("color_notice_before_info_window", g_SelectedUnitIndex, g_CurrentPlayerIndex, a1, 0);
    UI_ShowInfoWindow(v4[(unsigned __int8)g_LanguageIndex], 0, a1, a2, (int)&v4[3], (int)&g_TechLevelUpNoticeText[3]);
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
  char v5; // [esp+0h] [ebp-10h]

  v5 = byte_543D48[0];
  strupr_(440, 200);
  byte_543D48[0] = v5;
  RenderState_PumpIfRectInViewBounds(g_RenderState, v2, v3, 0x104u, 0x122u);
  Render_FillRect((_DWORD *)dword_5202E0, 0, 260, 200, 0x1B8u, 0x122u, 0xC8u, 0x104u);
  Render_ReleaseSurface(22, a1);
  UI_SetTextCursorPosition(dword_543D44);
  UI_DrawTextFmt(a2, 200, 440, 260, 3, (int)byte_543D48);
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
  char *v6; // edi
  char *v7; // esi
  char v8; // al
  char v9; // al
  char *v10; // edi
  _DWORD *v11; // eax
  int v12; // ecx
  int SpriteWidth; // edx
  int v14; // ecx
  int v15; // eax
  _DWORD *Surface; // eax
  DWORD v17; // ebp
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
  int v31; // esi
  unsigned int v32; // kr10_4
  unsigned int v33; // kr14_4
  int v34; // eax
  int v35; // edx
  int v36; // ecx
  char *v37; // esi
  char *v38; // edi
  char result; // al
  int v40[3]; // [esp+38h] [ebp-4Ch]
  int v41[3]; // [esp+44h] [ebp-40h]
  _DWORD *v42; // [esp+50h] [ebp-34h] BYREF
  int v43; // [esp+54h] [ebp-30h]
  int (*v44)(); // [esp+58h] [ebp-2Ch]
  int v45; // [esp+5Ch] [ebp-28h]
  int v46; // [esp+60h] [ebp-24h]
  int v47; // [esp+64h] [ebp-20h]
  char v48; // [esp+68h] [ebp-1Ch]

  v46 = a1;
  Debug_Log(a2, a3, a4, (int)aMessage_buildf);
  v45 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v44 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v4, a3, a4, (int)aSetrhS08x_11);
  v41[0] = (int)g_BuildingCompleteNoticeText[0];
  v41[1] = (int)g_BuildingCompleteNoticeText[1];
  v41[2] = (int)g_BuildingCompleteNoticeText[2];
  v40[0] = (int)g_BuildingCompleteNoticeTextAlt[0];
  v40[1] = (int)g_BuildingCompleteNoticeTextAlt[1];
  v40[2] = (int)g_BuildingCompleteNoticeTextAlt[2];
  v6 = byte_543D48;
  v7 = (char *)(v46 + 5);
  do
  {
    v8 = *v7;
    *v6 = *v7;
    if ( !v8 )
      break;
    v9 = v7[1];
    v7 += 2;
    v6[1] = v9;
    v6 += 2;
  }
  while ( v9 );
  v10 = byte_543D48;
  v11 = (_DWORD *)Mem_Alloc(4112, v5, a3, a4);
  if ( v11 )
    v11 = DLXSpriteSet_Load(v11, a3);
  v42 = v11;
  Render_Pump();
  v47 = v12;
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  DLX_GetSpriteWidth((int)v42, 0x17u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v42, 0x16u);
  v15 = v14 + 6;
  if ( (unsigned __int16)SpriteWidth > v14 + 6 )
    v15 = SpriteWidth;
  v43 = v15;
  Surface = (_DWORD *)Mem_Alloc(188, v14, a3, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, 640, v43);
  v17 = (DWORD)Surface;
  Render_FillRect(0, Surface, (unsigned __int16)v47, 0, 0x27Fu, v43 + v47 - 1, 0, 0);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v42, 22);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    v47,
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
    v47 + 6,
    v19,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  Render_ReleaseSurface(17, v17);
  if ( *(_BYTE *)(v46 + 4) == 2 )
    v20 = v41[(unsigned __int8)g_LanguageIndex];
  else
    v20 = v40[(unsigned __int8)g_LanguageIndex];
  UI_DrawTextFmt((int)byte_543D48, 70, 569, v47 + 60, 6, v20);
  v21 = -56;
  Render_FillRect(0, (_DWORD *)dword_5202E0, 260, 200, 0x1B8u, 0x122u, 0xC8u, 0x104u);
  UI_CheatEditRepaint(v17, (int)byte_543D48);
  Render_Present((int)g_RenderState);
  Render_Begin((int)g_RenderState, 0);
  g_DecisionDialogExitSignal = 0;
  while ( !DD_IsFlipping((int)g_RenderState) && !g_DecisionDialogExitSignal )
  {
    DD_Pump((int)g_RenderState, v21);
    if ( Input_IsKeyPressed(203) && dword_543D44 )
    {
      --dword_543D44;
      UI_CheatEditRepaint(v17, (int)v10);
      Input_ClearKey(203, v22);
    }
    if ( Input_IsKeyPressed(205) )
    {
      v23 = strlen(byte_543D48) + 1;
      v10 = &byte_543D48[v23];
      v21 = dword_543D44;
      if ( v23 - 1 > dword_543D44 )
      {
        ++dword_543D44;
        UI_CheatEditRepaint(v17, (int)v10);
        Input_ClearKey(205, v24);
      }
    }
    if ( Input_IsKeyPressed(211) )
    {
      v25 = strlen(&byte_543D48[dword_543D44 + 1]) + 1;
      v10 = (char *)dword_543D44;
      v21 = v25;
      memmove_(&byte_543D48[dword_543D44], &byte_543D48[dword_543D44 + 1], v25);
      UI_CheatEditRepaint(v17, (int)v10);
      Input_ClearKey(211, v26);
    }
    if ( Input_IsKeyPressed(14) && dword_543D44 )
    {
      v27 = &byte_543D48[dword_543D44--];
      v28 = strlen(v27) + 1;
      v10 = (char *)&v27[v28];
      v21 = v28;
      memmove_(&byte_543D48[dword_543D44], &byte_543D48[dword_543D44 + 1], v28);
      UI_CheatEditRepaint(v17, (int)v10);
      Input_ClearKey(14, v29);
    }
    if ( Input_IsKeyPressed(28) )
      g_DecisionDialogExitSignal = 1;
    v30 = Input_PopKey();
    v31 = v30;
    if ( v30 != -1 )
    {
      v48 = Input_KeyToChar(v30);
      if ( v48 )
      {
        v32 = strlen(byte_543D48) + 1;
        v10 = &byte_543D48[v32];
        if ( v32 - 1 < 0xA )
        {
          v33 = strlen(&byte_543D48[dword_543D44]) + 1;
          v10 = &byte_543D48[dword_543D44 + v33];
          v21 = v33;
          memmove_(&byte_543D48[dword_543D44 + 1], &byte_543D48[dword_543D44], v33);
          v34 = dword_543D44 + 1;
          *((_BYTE *)&dword_543D44 + v34 + 3) = v48;
          dword_543D44 = v34;
          UI_CheatEditRepaint(v17, (int)v10);
          Input_ClearKey(v31, v35);
        }
      }
    }
  }
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  Debug_Log(v36, (char)g_RenderHook, v17, (int)aUnsetrh08x_11);
  g_RenderHook = v44;
  Render_SetResourceHandle((int)&unk_51D4C0, v45);
  Render_FillRect((_DWORD *)v17, 0, 0, 0, 0x27Fu, v43 - 1, 0, v47);
  Render_Present((int)g_RenderState);
  if ( v17 )
    (**(void (__cdecl ***)(int, int, int, int, int, int))(v17 + 184))(v40[0], v40[1], v40[2], v41[0], v41[1], v41[2]);
  v37 = byte_543D48;
  v38 = (char *)(v46 + 5);
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
  int v2; // edi
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
  _BYTE v24[100]; // [esp+0h] [ebp-8Ch] BYREF
  _DWORD *v25; // [esp+64h] [ebp-28h] BYREF
  int v26; // [esp+68h] [ebp-24h]
  void *v27; // [esp+6Ch] [ebp-20h]
  int (*v28)(); // [esp+70h] [ebp-1Ch]

  v2 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v28 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v3, a1, a2, (int)aSetrhS08x_23);
  sprintf_(v24, "demo\\tekst%02d.s32", v4 + 1);
  v6 = (_DWORD *)Mem_Alloc(4112, v5, a1, a2);
  if ( v6 )
    v6 = DLXSpriteSet_Load(v6, a1);
  v25 = v6;
  Surface = (_DWORD *)Mem_Alloc(188, v7, a1, a2);
  if ( Surface )
  {
    SpriteWidth = DLX_GetSpriteWidth((int)v25, 0);
    Surface = Render_CreateSurface(v10, 640, SpriteWidth);
  }
  v11 = Surface;
  v12 = Surface;
  v13 = DLX_GetSpriteWidth((int)v25, 0);
  Render_FillRect(0, v11, 0, 0, 0x27Fu, v13 - 1, 0, 0);
  DLXSpriteSet_DrawText((int)v25, 0, (int)&unk_51D59C, (unsigned __int8 *)dword_5202F4);
  v27 = g_RenderDevice;
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v25, 0);
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
  Render_BlitSurface(&unk_51D4C0, v16, 0, (DWORD)v12);
  v17 = g_RenderState;
  while ( !Input_PollEventsUntil((int)v17, (char)&g_InputBackendState) )
  {
    v20 = Time_Now(v19, v18);
    if ( v20 >= v21 || Input_IsAnyKeyPressed() )
      break;
    InputBackend_PollState(&g_InputBackendState, v21, v19);
  }
  Debug_Log(v19, (char)g_RenderHook, (DWORD)v12, (int)aUnsetrh08x_23);
  g_RenderHook = v28;
  Render_SetResourceHandle((int)&unk_51D4C0, v2);
  v22 = DLX_GetSpriteWidth((int)v25, 0);
  Render_FillRect(v12, 0, 0, 0, 0x27Fu, v22 - 1, 0, 0);
  return DLXSpriteSet_ReleaseAndClear((int *)&v25);
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
int  Queen_ShowWhimDecisionDialog(int a1, int a2, int a3, int a4, DWORD a5)
{
  int v6; // ecx
  _DWORD *v7; // eax
  int v8; // ecx
  _DWORD *Surface; // eax
  DWORD v10; // ebp
  int SpriteForChar; // eax
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int result; // eax
  _DWORD v17[40]; // [esp+38h] [ebp-D8h] BYREF
  _DWORD *v18; // [esp+D8h] [ebp-38h] BYREF
  int v19; // [esp+DCh] [ebp-34h]
  int SpriteHeight; // [esp+E0h] [ebp-30h]
  int v21; // [esp+E4h] [ebp-2Ch]
  int v22; // [esp+E8h] [ebp-28h]
  int (*v23)(); // [esp+ECh] [ebp-24h]
  int v24; // [esp+F0h] [ebp-20h]
  int v25; // [esp+F4h] [ebp-1Ch]
  int SpriteWidth; // [esp+F8h] [ebp-18h]
  int v27; // [esp+FCh] [ebp-14h]

  v25 = a1;
  v19 = a4;
  Debug_Log(a3, a4, a5, (int)aQueenwhimmessa);
  v24 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v23 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a4, a5, (int)aSetrhS08x_18);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  Render_ReleaseSurface(17, a5);
  v18 = 0;
  v7 = (_DWORD *)Mem_Alloc(4112, v6, 0, a5);
  if ( v7 )
    v7 = DLXSpriteSet_Load(v7, 0);
  v18 = v7;
  v27 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v7, 0)) / 2;
  v21 = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v18, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v18, 0);
  Surface = (_DWORD *)Mem_Alloc(188, v8, 0, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  v10 = (DWORD)Surface;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)v21,
    (unsigned __int16)v27,
    SpriteHeight + v27 - 1,
    SpriteWidth + v21 - 1,
    0,
    0);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v18, 0);
  v22 = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(v27, v21, SpriteForChar, 1);
  SpriteForChar = DLX_GetSpriteForChar((int)v18, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  v22 = *((_DWORD *)g_RenderDevice + 46);
  Compat_RenderDeviceDrawMenuSprite(v27 + 41, v21 + 18, SpriteForChar, 1);
  Render_ReleaseSurface(17, v10);
  UI_DrawTextFmt(v22, v27 + 175, v27 + 525, v21 + 65, 6, v25);
  Render_ReleaseSurface(18, v10);
  UI_DrawText(v27 + 198, v21 + 12, (int)aD_6);
  UI_DrawTextFmt(v19, v27 + 126, v12, v21 + 207, 3, (int)aD_7);
  g_DecisionDialogConfirmDisabled = a2 > v19;
  qmemcpy(v17, &g_QueenWhimDecisionButtonWidgetsTemplate, 0x9Fu);
  v17[0] = v27 + 126;
  v17[1] = v21 + 175;
  v17[3] = &v18;
  *(_DWORD *)((char *)&v17[13] + 1) = v27 + 451;
  *(_DWORD *)((char *)&v17[14] + 1) = v21 + 175;
  *(_DWORD *)((char *)&v17[16] + 1) = &v18;
  UIWidgetTable_InitDrawStates(v17);
  Render_Present((int)g_RenderState);
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(v17, v10);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v15, (char)g_RenderState, v10, (int)aUnsetrh08x_18);
  g_RenderHook = v23;
  Render_SetResourceHandle((int)&unk_51D4C0, v24);
  Render_FillRect((_DWORD *)v10, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, v27, v21);
  Render_Present((int)g_RenderState);
  if ( v10 )
    RenderSurface_InvokeSlot0((_DWORD *)v10, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&v18);
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
int  YesNoWindow(int a1, _BYTE *a2, int a3, char a4, DWORD a5)
{
  int v6; // ecx
  char v7; // bl
  _DWORD *v8; // eax
  int i; // esi
  int v10; // edx
  int v11; // ecx
  _DWORD *Surface; // eax
  DWORD v13; // ebp
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
  _DWORD *v25; // [esp+BCh] [ebp-30h] BYREF
  int v26; // [esp+C0h] [ebp-2Ch]
  int v27; // [esp+C4h] [ebp-28h]
  int (*v28)(); // [esp+C8h] [ebp-24h]
  int v29; // [esp+CCh] [ebp-20h]
  int SpriteWidth; // [esp+D0h] [ebp-1Ch]
  int SpriteHeight; // [esp+D4h] [ebp-18h]
  int v32; // [esp+D8h] [ebp-14h]

  v27 = a1;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] enter text=%p image=%p\n", (void *)(uintptr_t)a1, (void *)a2);
  Debug_Log(a3, a4, a5, (int)aYesnowindowS);
  v29 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v28 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a4, a5, (int)aSetrhS08x_12);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  Render_ReleaseSurface(17, a5);
  if ( a2 )
    Render_LoadResourceSprite_v4(17, a2, v6, a4, a5);
  v7 = 0;
  v25 = 0;
  v8 = (_DWORD *)Mem_Alloc(4112, v6, 0, a5);
  if ( v8 )
    v8 = DLXSpriteSet_Load(v8, "pergamin.s32");
  v25 = v8;
  g_YesNoWindowWidgetSpriteSet = v25;
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] sprite_load set=%p data=%x\n", (void *)v25, v25 ? (unsigned int)v25[1024] : 0);
  if ( a2 )
  {
    for ( i = 4; i <= 8; ++i )
    {
      v7 = dword_5202F4;
      v10 = i;
      DLXSpriteSet_DrawText((int)v25, v10, (int)a2, (unsigned __int8 *)dword_5202F4);
    }
  }
  v32 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v25, 4u)) / 2;
  v26 = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v25, 4u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v25, 4u);
  Surface = (_DWORD *)Mem_Alloc(188, v11, v7, a5);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  v13 = (DWORD)Surface;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)v26,
    (unsigned __int16)v32,
    SpriteHeight + v32 - 1,
    SpriteWidth + v26 - 1,
    0,
    0);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v25, 4);
  v15 = *((_DWORD *)g_RenderDevice + 46);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] before_background sprite=%x left=%d top=%d\n", SpriteForChar, v32, v26);
  Compat_RenderDeviceDrawMenuSprite(v32, v26, SpriteForChar, 1);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_background\n");
  UI_DrawTextFmt(v15, v32 + 30, v32 + 260, v26 + 15, 3, v27);
  if ( Diagnostics_IsWorldMapClickTraceEnabled() )
    fprintf(stderr, "[yesno] after_text\n");
  v16 = v32;
  YesNoWindow_RebuildButtonWidgets((unsigned char *)v24, v16 + 72, v26 + 38, v32 + 146);
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
    UIWidgetTable_PollHoverAndActions(v24, v13);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v22, (char)g_RenderState, v13, (int)aUnsetrh08x_12);
  g_RenderHook = v28;
  Render_SetResourceHandle((int)&unk_51D4C0, v29);
  Render_FillRect((_DWORD *)v13, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, v32, v26);
  Render_Present((int)g_RenderState);
  if ( v13 )
    RenderSurface_InvokeSlot0((_DWORD *)(uintptr_t)v13, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&v25);
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
  int v6; // edi
  int v7; // ecx
  _DWORD *Surface; // eax
  _DWORD *v9; // esi
  int SpriteForChar; // eax
  DWORD v11; // ebp
  int v12; // ecx
  unsigned __int16 v13; // cx
  _DWORD *v15; // [esp+18h] [ebp-3Ch] BYREF
  int v16; // [esp+1Ch] [ebp-38h]
  int SpriteWidth; // [esp+20h] [ebp-34h]
  int (*v18)(); // [esp+24h] [ebp-30h]
  int SpriteHeight; // [esp+28h] [ebp-2Ch]
  int v20; // [esp+2Ch] [ebp-28h]
  int v21; // [esp+30h] [ebp-24h]
  int v22; // [esp+34h] [ebp-20h]
  int v23; // [esp+38h] [ebp-1Ch]

  v20 = a1;
  Debug_Log(a2, a3, a4, (int)aInfowindowS);
  v16 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v18 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a3, a4, (int)aSetrhS08x_13);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  Render_ReleaseSurface(17, a4);
  v15 = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, v4, 0, a4);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, 0);
  v15 = v5;
  v6 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 9u)) / 2;
  v23 = (480 - (unsigned __int16)DLX_GetSpriteWidth((int)v15, 9u)) / 2;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v15, 4u);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v15, 4u);
  Surface = (_DWORD *)Mem_Alloc(188, v7, 0, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  v9 = Surface;
  v21 = (unsigned __int16)v23;
  v22 = (unsigned __int16)v6;
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)v23,
    (unsigned __int16)v6,
    v6 + SpriteHeight - 1,
    SpriteWidth + v23 - 1,
    0,
    0);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v15, 9);
  v11 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v11 + 52))(
    v23,
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UI_DrawTextFmt(v6 + 25, v6 + 25, v6 + 250, v23 + 34, 3, v20);
  Render_Begin((int)g_RenderState, 0);
  Debug_Log(v12, v6, v11, (int)aUnsetrh08x_13);
  g_RenderHook = v18;
  Render_SetResourceHandle((int)&unk_51D4C0, v16);
  Render_FillRect(v9, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, v6, v13);
  Render_Present((int)g_RenderState);
  if ( v9 )
    (*(void (**)(void))v9[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&v15);
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
  DWORD v8; // ebp
  int SpriteForChar; // eax
  int v10; // eax
  int v11; // ecx
  _DWORD *v12; // edi
  char *v13; // esi
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  _DWORD v18[40]; // [esp+38h] [ebp-DCh] BYREF
  int v19[3]; // [esp+D8h] [ebp-3Ch]
  _DWORD *v20; // [esp+E4h] [ebp-30h] BYREF
  int v21; // [esp+E8h] [ebp-2Ch]
  int v22; // [esp+ECh] [ebp-28h]
  int (*v23)(); // [esp+F0h] [ebp-24h]
  int SpriteWidth; // [esp+F4h] [ebp-20h]
  int v25; // [esp+F8h] [ebp-1Ch]
  int SpriteHeight; // [esp+FCh] [ebp-18h]

  Debug_Log(a1, a2, a3, (int)aNewqueenwindow);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_log",
    g_SelectedUnitIndex,
    a1,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  v25 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v23 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(v3, a2, a3, (int)aSetrhS08x_17);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_set_rh",
    g_SelectedUnitIndex,
    v25,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_render_pump",
    g_SelectedUnitIndex,
    dword_545150,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  Render_ReleaseSurface(17, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_release_surface",
    g_SelectedUnitIndex,
    17,
    ACTIVE_MISSION_INDEX,
    GAME_TURN_COUNTER);
  v20 = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, v4, a2, a3);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, aQueen_s32_0);
  v20 = v5;
  g_QueenMarriageProposalWidgetSpriteSet = v20;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_sprite_load",
    g_SelectedUnitIndex,
    (int)(uintptr_t)v20,
    v20 ? (int)v20[1025] : -1,
    v20 ? (int)v20[1024] : 0);
  v22 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 0)) / 2;
  v21 = 150;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v20, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v20, 0);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_dims",
    g_SelectedUnitIndex,
    SpriteHeight,
    SpriteWidth,
    v22);
  Surface = (_DWORD *)Mem_Alloc(188, v6, 150, a3);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  v8 = (DWORD)Surface;
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_surface_create",
    g_SelectedUnitIndex,
    (int)(uintptr_t)Surface,
    SpriteHeight,
    SpriteWidth);
  Render_FillRect(
    0,
    Surface,
    (unsigned __int16)v21,
    (unsigned __int16)v22,
    SpriteHeight + v22 - 1,
    SpriteWidth + v21 - 1,
    0,
    0);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v20, 0);
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
  Compat_RenderDeviceDrawMenuSprite(v22, v21, SpriteForChar, 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_background_draw",
    g_SelectedUnitIndex,
    v22,
    v21,
    0);
  SpriteForChar = DLX_GetSpriteForChar((int)v20, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
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
  Compat_RenderDeviceDrawMenuSprite(v22 + 41, v21 + 18, SpriteForChar, 1);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_portrait_draw",
    g_SelectedUnitIndex,
    v22 + 41,
    v21 + 18,
    0);
  v19[0] = (int)g_QueenMarriageProposalTexts[0];
  v19[1] = (int)g_QueenMarriageProposalTexts[1];
  v19[2] = (int)g_QueenMarriageProposalTexts[2];
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_before_text",
    g_SelectedUnitIndex,
    (int)(uintptr_t)v19[(unsigned __int8)g_LanguageIndex],
    (unsigned __int8)g_LanguageIndex,
    0);
  UI_DrawTextFmt((int)v18, v22 + 175, v22 + 525, v21 + 55, 6, v19[(unsigned __int8)g_LanguageIndex]);
  Diagnostics_TraceWorldMapActionEvent(
    "queen_dialog_after_text",
    g_SelectedUnitIndex,
    v22 + 175,
    v21 + 55,
    0);
  v10 = v22;
  QueenMarriageProposal_RebuildButtonWidgets(
    (unsigned char *)v18,
    &g_QueenMarriageProposalWidgetSpriteSet,
    v10 + 126,
    v21 + 175,
    v22 + 451);
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
    (int)(uintptr_t)v8,
    0);
  g_DecisionDialogExitSignal = 0;
  do
  {
    DD_Pump((int)g_RenderState, 0);
    UIWidgetTable_PollHoverAndActions(v18, v8);
  }
  while ( !g_DecisionDialogExitSignal );
  Render_Pump();
  Debug_Log(v16, (char)g_RenderState, v8, (int)aUnsetrh08x_17);
  g_RenderHook = v23;
  Render_SetResourceHandle((int)&unk_51D4C0, v25);
  Render_FillRect((_DWORD *)v8, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, v22, v21);
  Render_Present((int)g_RenderState);
  if ( v8 )
    RenderSurface_InvokeSlot0((_DWORD *)v8, 2);
  DLXSpriteSet_ReleaseAndClear((int *)&v20);
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
  int v6; // esi
  int v7; // ecx
  _DWORD *Surface; // eax
  int SpriteForChar; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  _DWORD *v15; // [esp+34h] [ebp-38h] BYREF
  int v16; // [esp+38h] [ebp-34h]
  int v17; // [esp+3Ch] [ebp-30h]
  int (*v18)(); // [esp+40h] [ebp-2Ch]
  _DWORD *v19; // [esp+44h] [ebp-28h]
  int v20; // [esp+48h] [ebp-24h]
  int SpriteWidth; // [esp+4Ch] [ebp-20h]
  int SpriteHeight; // [esp+50h] [ebp-1Ch]

  v16 = a1;
  Debug_Log(a2, a3, a4, (int)aQueenmessageS);
  v20 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v18 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log((int)Render_DefaultRH, a3, a4, (int)aSetrhS08x_16);
  Render_Pump();
  RenderState_SelectCursorDescriptor((int)g_RenderState, dword_545150);
  Render_ReleaseSurface(17, a4);
  v15 = 0;
  v5 = (_DWORD *)Mem_Alloc(4112, v4, 0, a4);
  if ( v5 )
    v5 = DLXSpriteSet_Load(v5, 0);
  v15 = v5;
  v6 = (640 - (unsigned __int16)DLX_GetSpriteHeight((int)v5, 0)) / 2;
  SpriteHeight = (unsigned __int16)DLX_GetSpriteHeight((int)v15, 0);
  SpriteWidth = (unsigned __int16)DLX_GetSpriteWidth((int)v15, 0);
  Surface = (_DWORD *)Mem_Alloc(188, v7, 0, a4);
  if ( Surface )
    Surface = Render_CreateSurface((int)Surface, SpriteHeight, SpriteWidth);
  v19 = Surface;
  Render_FillRect(0, Surface, 150, (unsigned __int16)v6, v6 + SpriteHeight - 1, SpriteWidth + 149, 0, 0);
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar((int)v15, 14);
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
  v10 = DLX_GetSpriteForChar((int)v15, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 1);
  v17 = *((_DWORD *)g_RenderDevice + 46);
  (*(void (__fastcall **)(int, int, int, int, int, int, int, _DWORD, _DWORD))(v17 + 52))(
    168,
    v10,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  UI_DrawTextFmt(150, v6 + 175, v6 + 525, 205, 6, v16);
  Render_Present((int)g_RenderState);
  while ( !DD_IsFlipping(v11) )
    DD_Pump(v12, 0);
  Render_Begin((int)g_RenderState, 0);
  Render_Pump();
  Debug_Log(v13, 0, (DWORD)g_RenderHook, (int)aUnsetrh08x_16);
  g_RenderHook = v18;
  Render_SetResourceHandle((int)&unk_51D4C0, v20);
  Render_FillRect(v19, 0, 0, 0, SpriteHeight - 1, SpriteWidth - 1, v6, 0x96u);
  Render_Present((int)g_RenderState);
  if ( v19 )
    (*(void (**)(void))v19[46])();
  DLXSpriteSet_ReleaseAndClear((int *)&v15);
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
  int v3; // ecx
  const char *v4; // esi
  int v5; // ecx
  int result; // eax
  _BYTE v7[100]; // [esp+0h] [ebp-80h] BYREF
  int v8[7]; // [esp+64h] [ebp-1Ch] BYREF

  v8[6] = a1;
  v8[0] = (int)g_MissionStatusFormatsByLanguage[0];
  v8[1] = (int)g_MissionStatusFormatsByLanguage[1];
  v8[2] = (int)g_MissionStatusFormatsByLanguage[2];
  v3 = ACTIVE_MISSION_INDEX;
  if ( v3 != -1 )
  {
    v4 = (const char *)v8[(unsigned __int8)g_LanguageIndex];
    sprintf_(
      v7,
      v4,
      ACTIVE_MISSION_INDEX % 10 + 1,
      (&g_MissionStatusTextsByLanguage[3 * v3])[(unsigned __int8)g_LanguageIndex]);
    return UI_ShowInfoWindow((const char *)v7, 2u, v5, a2, (int)&v8[3], (int)v4);
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
signed int  UI_WaitForKeyOrTimeout(int a1, int a2)
{
  (void)a2;
  return UI_WaitForAnyKeyOrClick(Time_Now(0, 0) + a1, 0);
}

//----- (004477C0) --------------------------------------------------------
signed int  UI_WaitForAnyKeyOrClick(int a1, int a2)
{
  unsigned int deadline;

  (void)a2;
  deadline = (unsigned int)a1;
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
  previous_resource_handle = Render_SetResourceHandle((int)&unk_51D4C0, 0);
  previous_render_hook = g_RenderHook;
  g_RenderHook = 0;
  Debug_Log(0, 0, a3, (int)aSetrhS08x_14, aNull, 0);
  Palette_ApplyDefaultPalette((int *)&unk_51D4C0);
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
  Render_SetResourceHandle((int)&unk_51D4C0, previous_resource_handle);
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
  _DWORD *v10; // eax
  int v12; // ecx
  int v17; // eax
  int v18; // ecx
  char *v19; // edi
  char *v20; // esi
  int v21; // ecx
  int v24; // ecx
  _DWORD *v25; // eax
  bool i; // zf
  int campaign_menu_cancelled_by_escape; // ecx
  int v33; // ecx
  _DWORD *v40; // eax
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
  _DWORD *v90; // eax
  int v93; // eax
  DWORD v97; // ebp
  int v98; // ecx
  _DWORD *v104; // eax
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
  int v128; // [esp+211Ch] [ebp-20h]
  char v129; // [esp+2120h] [ebp-1Ch]

  Debug_Log(a1, a2, (DWORD)a3, (int)aStartmenu);
  Surface = (_DWORD *)Mem_Alloc(188, 0, 0, 0);
  if ( Surface )
  {
    LOBYTE(a2) = -32;
    Surface = Render_CreateSurface((int)Surface, 640, 480);
  }
  dword_5202E0 = (int)Surface;
  UI_StartAnims(0, a2, (DWORD)a3);
  v126 = Render_SetResourceHandle((int)&unk_51D4C0, 1);
  v110 = Render_DefaultRH;
  v127 = g_RenderHook;
  g_RenderHook = (int (*)())Render_DefaultRH;
  Debug_Log(0, 0, (DWORD)a3, (int)aSetrhS08x_15, aStdrh_10, Render_DefaultRH);
  DD_Pump((int)g_RenderState, a2);
  v128 = 1;
  do
  {
    v10 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
    if ( v10 )
      v10 = DLXSpriteSet_Load(v10, "menu\\main.s32");
    g_PlayGameMenuSpriteSetHandle = (int)v10;
    Render_LoadPCXImage(dword_5202E0, aMenuMain_gfx, 0, (uintptr_t)byte_543D80);
    Palette_LoadOrBuildBlendLookupTable(aMenuMain, (int)byte_543D80, v12, (DWORD)a3);
    if ( v128 && g_Options_MusicEnabledFlag )
      g_MainMenuMusicHandle = Sound_PlayNamedSfxFile(aMusicMenu, 64);
    DD_Pump((int)g_RenderState, 0);
    if ( v128 )
      Palette_ApplyDefaultPalette((int *)&unk_51D4C0);
    DD_Pump((int)g_RenderState, 0);
    Debug_Log(0, 0, (DWORD)a3, (int)aDraw1);
    Render_ClearGameScreen((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
    Debug_Log(0, 0, (DWORD)a3, (int)aDraw2);
    Render_ClearGameScreen((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
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
    a2 = (signed int)&unk_51D4C0;
    g_RenderDevice = &unk_51D4C0;
    UIWidgetTable_InitDrawStates(v120);
    if ( v128 )
    {
      a2 = 60;
      Palette_FadeInFromBlack((int *)&unk_51D4C0, byte_543D80, 60);
    }
    g_PlayGameMenuExitRequested = 0;
    RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)byte_543D80, 0, 0);
    RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
    dword_545150 = (int)&g_CursorDesc_Default;
    Render_Present((int)g_RenderState);
    v128 = 0;
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
        v25 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( v25 )
          v25 = DLXSpriteSet_Load(v25, "menu\\kamp.s32");
        g_PlayGameMenuSpriteSetHandle = (int)v25;
        RenderSurface_InvokeSlot48LoadPCX(
          (_DWORD *)(uintptr_t)(unsigned int)dword_5202E0,
          aMenuMain_gfx_0,
          0,
          (uintptr_t)byte_543D80);
        RenderSurface_InvokeSlot36((_DWORD *)(uintptr_t)(unsigned int)dword_5202E0);
        CampaignMenu_RebuildButtonWidgetTemplate();
        qmemcpy(v124, g_CampaignMenuButtonWidgetsTemplate, sizeof(g_CampaignMenuButtonWidgetsTemplate));
        g_RenderDevice = &unk_51D4C0;
        UIWidgetTable_InitDrawStates(v124);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)byte_543D80, 0, 0);
        a3 = (char *)&g_CursorDesc_Default;
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        dword_545150 = (int)&g_CursorDesc_Default;
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
          Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        if ( !campaign_menu_cancelled_by_escape && dword_544184 != -1 )
        {
          if ( dword_544184 == 1 )
          {
            LOBYTE(a2) = 1;
            CSS_StopSound(g_MainMenuMusicHandle, 1000);
            v128 = 1;
            Scenario_LoadMissionByIndexAndPlay(0, 0, (DWORD)&g_CursorDesc_Default, a4);
          }
          else
          {
            CSS_StopSound(g_MainMenuMusicHandle, 1000);
            Scenario_LoadMissionByIndexAndPlay((char *)0xA, 0, (DWORD)&g_CursorDesc_Default, a4);
            v128 = 1;
          }
        }
        break;
      case MAIN_MENU_REQUEST_CREDITS:
        CSS_StopSound(g_MainMenuMusicHandle, 1000);
        Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
        LOBYTE(a2) = 0;
        Video_Avi_playIn(aCre_an, 0, 1, 0, 1, 1);
        v128 = 1;
        break;
      case MAIN_MENU_REQUEST_MULTIPLAYER:
        memset(byte_544188, 5, 5);
        byte_544188[0] = 3;
        byte_544189 = 0;
        byte_54418B = 1;
        byte_54418A = 2;
        qmemcpy(v125, &g_MultiplayerDefaultRulerNamesTable, sizeof(v125));
        Player_AssignRandomUniqueRulerNames(5, v125);
        dword_5441D8 = 0;
        dword_544198 = -1;
        dword_5441DC = 0;
        v40 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( v40 )
          v40 = DLXSpriteSet_Load(v40, aMenuMultipl_s32);
        g_PlayGameMenuSpriteSetHandle = (int)v40;
        a2 = (signed int)byte_543D80;
        (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(dword_5202E0 + 184) + 48))(0, aMenuMultipl_gf);
        Render_LoadResourceSprite_v4(18, byte_543D80, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, byte_543D80, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)dword_5202E0;
        MultiplayerSetup_RedrawPlayerSlotIcons();
        (*(void (**)(void))(*(_DWORD *)(dword_5202E0 + 184) + 36))();
        for ( j = 0; j < 5; ++j )
          MultiplayerSetup_RepaintPlayerSlotRow(j, j + 1, 0);
        MultiplayerSetup_RedrawOpponentNameList();
        qmemcpy(v122, &g_MultiplayerSetupWidgetTemplateBlob, 265);
        g_RenderDevice = &unk_51D4C0;
        UIWidgetTable_InitDrawStates(v122);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)byte_543D80, 0, 0);
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        dword_545150 = (int)&g_CursorDesc_Default;
        Render_Present((int)g_RenderState);
        while ( !g_PlayGameMenuExitRequested )
        {
          DD_Pump((int)g_RenderState, 0);
          if ( DD_IsFlipping((int)g_RenderState)
            && dword_544CFC >> byte_54512C >= 176
            && dword_544CFC >> byte_54512C <= 236
            && (unsigned int)(((dword_544D00 >> byte_54512C) - 129) / 53) <= 4 )
          {
            multiplayer_player_type_slot = ((dword_544D00 >> byte_54512C) - 129) / 53;
            Audio_PlayButtonSound(aMale_2);
            byte_544188[multiplayer_player_type_slot] = ((unsigned __int8)byte_544188[multiplayer_player_type_slot] + 1) % 6;
            MultiplayerSetup_RedrawPlayerSlotIcons();
            MultiplayerSetup_RepaintPlayerSlotRow(multiplayer_player_type_slot, 0, 0);
            Render_Begin((int)g_RenderState, 0);
          }
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            if ( dword_544CFC >> byte_54512C >= 239 && dword_544CFC >> byte_54512C <= 339 )
            {
              multiplayer_selected_name_slot = ((dword_544D00 >> byte_54512C) - 144) / 53;
              if ( multiplayer_selected_name_slot <= 4 )
              {
                multiplayer_previous_name_slot = dword_544198;
                if ( multiplayer_selected_name_slot != dword_544198 )
                {
                  dword_544198 = multiplayer_selected_name_slot;
                  dword_544194 = 0;
                  if ( multiplayer_previous_name_slot != -1 )
                    MultiplayerSetup_RepaintPlayerSlotRow(multiplayer_previous_name_slot, 0, 0);
                  MultiplayerSetup_RepaintPlayerSlotRow(dword_544198, 0, 0);
                }
              }
            }
          }
          if ( dword_544198 != -1 )
          {
            if ( Input_IsKeyPressed(203) )
            {
              v69 = dword_544194;
              if ( dword_544194 )
              {
                MultiplayerSetup_RepaintPlayerSlotRow(dword_544198, v69, --dword_544194);
                Input_ClearKey(203, v70);
              }
            }
            if ( Input_IsKeyPressed(205) )
            {
              v72 = strlen(&byte_5441A0[11 * dword_544198]) + 1;
              if ( v72 - 1 > dword_544194 )
              {
                ++dword_544194;
                MultiplayerSetup_RepaintPlayerSlotRow(dword_544198, v71, v72 - 1);
                Input_ClearKey(205, v73);
              }
            }
            if ( Input_IsKeyPressed(211) )
            {
              LOBYTE(a2) = strlen(&byte_5441A0[11 * dword_544198 + 1 + dword_544194]) + 1;
              memmove_(
                &byte_5441A0[11 * dword_544198 + dword_544194],
                &byte_5441A0[11 * dword_544198 + dword_544194 + 1],
                strlen(&byte_5441A0[11 * dword_544198 + dword_544194 + 1]) + 1);
              MultiplayerSetup_RepaintPlayerSlotRow(dword_544198, v74, v75);
              Input_ClearKey(211, v76);
            }
            if ( Input_IsKeyPressed(14) )
            {
              LOBYTE(a2) = dword_544194;
              if ( dword_544194 )
              {
                v77 = &byte_5441A0[11 * dword_544198 + dword_544194--];
                v78 = strlen(v77) + 1;
                a3 = (char *)dword_544194;
                LOBYTE(a2) = v78;
                memmove_(
                  &byte_5441A0[11 * dword_544198 + dword_544194],
                  &byte_5441A0[11 * dword_544198 + dword_544194 + 1],
                  v78);
                MultiplayerSetup_RepaintPlayerSlotRow(dword_544198, v79, v80);
                Input_ClearKey(14, v81);
              }
            }
            if ( Input_IsKeyPressed(28) )
            {
              v83 = dword_544198;
              dword_544198 = -1;
              MultiplayerSetup_RepaintPlayerSlotRow(v83, -1, v82);
            }
            v84 = Input_PopKey();
            Render_ReleaseSurface(18, 0);
            if ( v84 != -1 )
            {
              v129 = Input_KeyToChar(v84);
              if ( v129 )
              {
                if ( strlen(&byte_5441A0[11 * dword_544198]) < 0xA )
                {
                  Render_LoadResourceSprite_v3(aW);
                  LOBYTE(a2) = dword_544198;
                  v85 = Render_LoadResourceSprite_v3(&byte_5441A0[11 * dword_544198]);
                  if ( v85 < v86 )
                  {
                    LOBYTE(a2) = strlen(&byte_5441A0[11 * dword_544198 + dword_544194]) + 1;
                    memmove_(
                      &byte_5441A0[11 * dword_544198 + dword_544194 + 1],
                      &byte_5441A0[11 * dword_544198 + dword_544194],
                      strlen(&byte_5441A0[11 * dword_544198 + dword_544194]) + 1);
                    v87 = 11 * dword_544198;
                    v88 = dword_544194 + 1;
                    LOBYTE(v87) = v129;
                    byte_5441A0[11 * dword_544198 + dword_544194] = v129;
                    dword_544194 = v88;
                    MultiplayerSetup_RepaintPlayerSlotRow(dword_544198, v87, v88);
                    Input_ClearKey(v84, v89);
                  }
                }
              }
            }
          }
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            if ( dword_544CFC >> byte_54512C >= 356 && dword_544CFC >> byte_54512C <= 477 )
            {
              multiplayer_map_row = ((dword_544D00 >> byte_54512C) - 134) / 22;
              if ( multiplayer_map_row <= 0xA )
              {
                LOBYTE(a2) = dword_5441DC;
                v54 = dword_5441DC + multiplayer_map_row;
                if ( v54 != dword_5441D8 )
                {
                  dword_5441D8 = v54;
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
        if ( dword_544190 )
          Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        v128 = dword_544190;
        if ( dword_544190 )
        {
          CSS_StopSound(g_MainMenuMusicHandle, 1000);
          WorldMap_Initialize(0, (DWORD)a3);
          for ( multiplayer_player_index = 0; multiplayer_player_index < 5; ++multiplayer_player_index )
          {
            multiplayer_player_state = &multiplayer_player_states[PLAYER_DATA_STRIDE * multiplayer_player_index];
            PlayerRuntimeState_ResetDefaults((uintptr_t)multiplayer_player_state);
            *(_DWORD *)multiplayer_player_state = 1;
            multiplayer_player_type = (unsigned __int8)byte_544188[multiplayer_player_index];
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
            strcpy(multiplayer_player_state + PLAYER_DISPLAY_NAME_OFFSET, &byte_5441A0[11 * multiplayer_player_index]);
          }
          Scenario_LoadMultiplayerMapAndSeedPlayers(dword_5441D8, (uintptr_t)multiplayer_player_states);
          PlayGame(0, 0, (DWORD)a3, 0, a4);
        }
        break;
      case MAIN_MENU_REQUEST_OPTIONS:
        v90 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( v90 )
          v90 = DLXSpriteSet_Load(v90, aMenuOpt_s32);
        g_PlayGameMenuSpriteSetHandle = (int)v90;
        if ( g_LanguageIndex )
        {
          if ( (unsigned __int8)g_LanguageIndex <= 1u )
          {
            a2 = (signed int)byte_543D80;
            (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(dword_5202E0 + 184) + 48))(0, aMenuOpt_a_gfx);
          }
          else if ( g_LanguageIndex == 2 )
          {
            a2 = (signed int)byte_543D80;
            (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(dword_5202E0 + 184) + 48))(0, aMenuOpt_g_gfx);
          }
        }
        else
        {
          a2 = (signed int)byte_543D80;
          (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(dword_5202E0 + 184) + 48))(0, aMenuOpt_p_gfx);
        }
        Render_LoadResourceSprite_v4(18, byte_543D80, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, byte_543D80, 0, 0, 0);
        g_RenderDevice = (_UNKNOWN *)dword_5202E0;
        (*(void (__thiscall **)(int))(*(_DWORD *)(dword_5202E0 + 184) + 36))(92);
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
        g_RenderDevice = &unk_51D4C0;
        UIWidgetTable_InitDrawStates(v113);
        Options_DrawAllSliderThumbs(g_OptionsMenuSliderThumbPositions, a2, v97);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)byte_543D80, 0, 0);
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        dword_545150 = (int)&g_CursorDesc_Default;
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
        dword_5441E0 = -1;
        v104 = (_DWORD *)Mem_Alloc(4112, 0, 0, 0);
        if ( v104 )
          v104 = DLXSpriteSet_Load(v104, aMenuLoad_s32);
        g_PlayGameMenuSpriteSetHandle = (int)v104;
        (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(dword_5202E0 + 184) + 48))(0, aMenuLoad_gfx);
        Render_LoadResourceSprite_v4(18, byte_543D80, 0, 0, 0);
        Render_LoadResourceSprite_v4(21, byte_543D80, 0, 0, 0);
        (*(void (**)(void))(*(_DWORD *)(dword_5202E0 + 184) + 36))();
        for ( k = 0; k < 10; ++k )
          LoadMenu_RedrawSaveSlotRow(k, (DWORD)a3);
        LoadMenu_RebuildButtonWidgetTemplate();
        qmemcpy(v123, &g_LoadMenuButtonWidgetsTemplate, 0x9Fu);
        g_RenderDevice = &unk_51D4C0;
        UIWidgetTable_InitDrawStates(v123);
        g_PlayGameMenuExitRequested = 0;
        RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, (int)byte_543D80, 0, 0);
        RenderState_SelectCursorDescriptor((int)g_RenderState, (int)&g_CursorDesc_Default);
        dword_545150 = (int)&g_CursorDesc_Default;
        Render_Present((int)g_RenderState);
        while ( !g_PlayGameMenuExitRequested )
        {
          DD_Pump((int)g_RenderState, 0);
          if ( DD_IsFlipping((int)g_RenderState) )
          {
            if ( dword_544CFC >> byte_54512C >= 244 && dword_544CFC >> byte_54512C <= 410 )
            {
              v108 = ((dword_544D00 >> byte_54512C) - 155) / 22;
              if ( v108 <= 9 )
              {
                previous_load_slot = dword_5441E0;
                if ( v108 != dword_5441E0 )
                {
                  dword_5441E0 = ((dword_544D00 >> byte_54512C) - 155) / 22;
                  if ( previous_load_slot != -1 )
                    LoadMenu_RedrawSaveSlotRow(previous_load_slot, (DWORD)a3);
                  LoadMenu_RedrawSaveSlotRow(dword_5441E0, (DWORD)a3);
                }
                if ( RenderState_IsCursorFlipStillActive((int)g_RenderState) )
                  LoadMenu_HandleSlotConfirmButtonRelease(0, (DWORD)a3);
              }
            }
          }
          UIWidgetTable_PollHoverAndActions(v123, 0);
        }
        Render_Pump();
        if ( dword_544190 )
          Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
        DLXSpriteSet_ReleaseAndClear(&g_PlayGameMenuSpriteSetHandle);
        if ( !dword_544190 )
          dword_5441E0 = -1;
        selected_load_slot = dword_5441E0;
        if ( selected_load_slot != -1 )
        {
          CSS_StopSound(g_MainMenuMusicHandle, 1000);
          WorldMap_Initialize((char)selected_load_slot, (DWORD)a3);
          v128 = 1;
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
  Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
  Render_UnlockBackbuffer((int)&unk_51D4C0);
  HIBYTE(v110) = HIBYTE(g_RenderHook);
  Debug_Log(v33, a2, (DWORD)g_RenderHook, (int)aUnsetrh08x_15);
  g_RenderHook = v127;
  return Render_SetResourceHandle((int)&unk_51D4C0, v126);
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
  dword_544184 = 1;
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
  dword_544184 = 0;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544184: using guessed type int dword_544184;

//----- (00448D10) --------------------------------------------------------
int  MultiplayerSetup_RepaintPlayerSlotRow(int a1, int a2, int a3)
{
  __int16 v4; // di
  DWORD v5; // ebp
  int v6; // edi
  int v7; // eax
  int result; // eax
  unsigned __int16 v9; // [esp-4h] [ebp-20h]
  int v10; // [esp+0h] [ebp-1Ch]

  v4 = 53 * a1;
  Str_TitleCase(&byte_5441A0[11 * dword_544198], a2, a3);
  v10 = dword_544D10;
  v5 = (unsigned __int16)(v4 + 167);
  v9 = v4 + 167;
  v6 = (unsigned __int16)(v4 + 144);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xEFu, 0x153u, v6, v9);
  Render_FillRect((_DWORD *)dword_5202E0, 0, v6, 234, 0x15Du, v5, 0xEAu, v6);
  Render_ReleaseSurface(18, v5);
  if ( a1 == dword_544198 )
    UI_SetTextCursorPosition(dword_544194);
  v7 = (unsigned __int8)byte_544188[a1];
  g_RenderDevice = &unk_51D4C0;
  if ( v7 != 5 )
    UI_DrawTextFmt(v6, 239, 339, 53 * a1 + 144, 3, (int)&byte_5441A0[11 * a1]);
  result = UI_SetTextCursorPosition(-1);
  if ( v10 )
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
  int v3; // edx
  int v4; // edx

  UIWidget_PlayPressedReleaseAnimation(a1);
  for ( result = 0; result < 5; ++result )
  {
    v3 = (unsigned __int8)byte_544188[result];
    if ( v3 == 3 )
      break;
    if ( v3 == 4 )
      break;
  }
  if ( result != 5 )
  {
    v4 = 0;
    for ( result = 0; result < 5; ++result )
    {
      if ( byte_544188[result] != 5 )
        ++v4;
    }
    if ( v4 > 1 && dword_5441D8 != -1 )
    {
      dword_544190 = 1;
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
  dword_544190 = 0;
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;

//----- (00448EA0) --------------------------------------------------------
int MultiplayerSetup_RedrawPlayerSlotIcons()
{
  int v0; // edi
  int v1; // esi
  int SpriteForChar; // eax
  int v3; // ecx
  int result; // eax
  int v5; // [esp+1Ch] [ebp-1Ch]

  v0 = 129;
  v5 = dword_544D10;
  v1 = 0;
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xB0u, 0xECu, 0x81u, 0x18Au);
  do
  {
    SpriteForChar = DLX_GetSpriteForChar(g_PlayGameMenuSpriteSetHandle, (unsigned __int8)byte_544188[v1] + 8);
    v3 = v0;
    ++v1;
    v0 += 53;
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
  while ( v1 < 5 );
  if ( v5 )
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
  DWORD v0; // ebp
  int v1; // edi
  int v2; // esi
  int result; // eax
  int v4; // eax

  v0 = dword_544D10;
  if ( dword_544D10 )
    RenderState_PumpIfRectInViewBounds(g_RenderState, 0x164u, 0x1DDu, 0x86u, 0x175u);
  v1 = 134;
  v2 = 0;
  g_RenderDevice = &unk_51D4C0;
  do
  {
    result = Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v1, 356, 0x1DDu, v1 + 22, 0x164u, v1);
    if ( v2 + dword_5441DC < 20 )
    {
      if ( v2 + dword_5441DC == dword_5441D8 )
        v4 = 21;
      else
        v4 = 18;
      Render_ReleaseSurface(v4, v0);
      result = UI_DrawText(356, v1, (int)&aKarkhan[13 * v2 + 13 * dword_5441DC]);
    }
    ++v2;
    v1 += 22;
  }
  while ( v2 < 11 );
  if ( v0 )
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
  if ( dword_5441DC < 19 )
    ++dword_5441DC;
  return MultiplayerSetup_RedrawOpponentNameList();
}
// 5441DC: using guessed type int dword_5441DC;

//----- (004494E0) --------------------------------------------------------
int  PlayGameMenu_HandleScrollButtonRelease(int a1)
{
  UIWidget_PlayPressedReleaseAnimation(a1);
  if ( dword_5441DC )
    --dword_5441DC;
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
BOOL  Options_ToggleCheckboxMainMenu(int a1)
{
  char v2; // dl

  v2 = *(_BYTE *)(a1 + 8) ^ 1;
  *(_BYTE *)(a1 + 8) = v2;
  *(_BYTE *)(a1 + 8) = v2 ^ 2;
  Audio_PlayButtonSound(*(char **)(a1 + 49));
  return Render_Begin((int)g_RenderState, 0);
}
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044A110) --------------------------------------------------------
int  LoadMenu_HandleSlotConfirmButtonRelease(int a1, DWORD a2)
{
  int result; // eax

  if ( a1 )
    UIWidget_PlayPressedReleaseAnimation(a1);
  result = SaveSlot_HasDataFile(dword_5441E0, a2);
  if ( result )
  {
    dword_544190 = 1;
    g_PlayGameMenuExitRequested = 1;
  }
  return result;
}
// 543D78: using guessed type int g_PlayGameMenuExitRequested;
// 544190: using guessed type int dword_544190;
// 5441E0: using guessed type int dword_5441E0;

//----- (0044A140) --------------------------------------------------------
void * LoadMenu_RedrawSaveSlotRow(int a1, DWORD a2)
{
  int v4; // edi
  int v5; // eax
  char *row_label; // eax
  void *result; // eax
  void *v8; // [esp+14h] [ebp-20h]
  int v9; // [esp+18h] [ebp-1Ch]

  v8 = g_RenderDevice;
  row_label = (char *)(uintptr_t)(unsigned int)Compat_AllocLow32Bytes(20);
  if ( !row_label )
    return v8;
  SaveSlot_LoadLabelOrPlaceholder(a1, row_label, a2);
  v9 = dword_544D10;
  g_RenderDevice = &unk_51D4C0;
  v4 = (unsigned __int16)(22 * a1 + 155);
  RenderState_PumpIfRectInViewBounds(g_RenderState, 0xF4u, 0x1A4u, v4, 22 * a1 + 175);
  Render_FillRect((_DWORD *)dword_5202E0, 0, (unsigned __int16)v4, 244, 0x1A4u, 22 * a1 + 175, 0xF4u, v4);
  if ( a1 == dword_5441E0 )
    v5 = 18;
  else
    v5 = 21;
  Render_ReleaseSurface(v5, (unsigned __int16)(22 * a1 + 175));
  UI_DrawTextFmt(v4, 244, 410, 22 * a1 + 155, 3, (int)(uintptr_t)row_label);
  if ( v9 )
    Render_Present((int)g_RenderState);
  Compat_FreeLow32Bytes((int)(uintptr_t)row_label);
  result = v8;
  g_RenderDevice = v8;
  return result;
}
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 5202E0: using guessed type int dword_5202E0;
// 5441E0: using guessed type int dword_5441E0;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544D10: using guessed type int dword_544D10;

//----- (0044A510) --------------------------------------------------------
int  Options_DrawSliderThumb(unsigned __int16 *a1, char a2, DWORD a3)
{
  int v4; // ecx
  int v5; // edi
  _DWORD *Surface; // eax
  __int16 SpriteWidth; // bx
  __int16 SpriteHeight; // ax
  int v9; // ecx
  __int16 v10; // ax
  int SpriteForChar; // eax
  int result; // eax
  __int16 v13; // bx
  unsigned __int16 v14; // ax
  unsigned __int16 v15; // [esp+10h] [ebp-2Ch]
  unsigned __int16 v16; // [esp+10h] [ebp-2Ch]
  unsigned __int16 v17; // [esp+14h] [ebp-28h]
  unsigned __int16 v18; // [esp+18h] [ebp-24h]
  void *v19; // [esp+1Ch] [ebp-20h]
  __int16 v20; // [esp+20h] [ebp-1Ch]

  Render_Pump();
  v5 = Render_SetResourceHandle((int)&unk_51D4C0, 0);
  v19 = g_RenderDevice;
  if ( *((_DWORD *)a1 + 8) )
  {
    v18 = a1[4];
    v17 = *a1;
    v16 = DLX_GetSpriteWidth(**((_DWORD **)a1 + 5), a1[12]) - 1;
    v13 = a1[2] - *a1;
    v14 = v13 + DLX_GetSpriteHeight(**((_DWORD **)a1 + 5), a1[12]) - 1;
    Render_FillRect(*((_DWORD **)a1 + 8), 0, 0, 0, v14, v16, v17, v18);
  }
  else
  {
    Surface = (_DWORD *)Mem_Alloc(188, v4, a2, a3);
    if ( Surface )
    {
      SpriteWidth = DLX_GetSpriteWidth(**((_DWORD **)a1 + 5), a1[12]);
      v20 = a1[2] - *a1;
      SpriteHeight = DLX_GetSpriteHeight(**((_DWORD **)a1 + 5), a1[12]);
      Surface = Render_CreateSurface(v9, v20 + SpriteHeight, SpriteWidth);
    }
    *((_DWORD *)a1 + 8) = Surface;
    v15 = a1[4] + DLX_GetSpriteWidth(**((_DWORD **)a1 + 5), a1[12]) - 1;
    v10 = DLX_GetSpriteHeight(**((_DWORD **)a1 + 5), a1[12]);
    Render_FillRect(0, *((_DWORD **)a1 + 8), a1[4], *a1, a1[2] + v10 - 1, v15, 0, 0);
  }
  g_RenderDevice = &unk_51D4C0;
  SpriteForChar = DLX_GetSpriteForChar(**((_DWORD **)a1 + 5), *((_DWORD *)a1 + 6));
  (*(void (__fastcall **)(_DWORD, int, int, int, int, int, int, _DWORD, _DWORD))(*((_DWORD *)g_RenderDevice + 46) + 52))(
    *((_DWORD *)a1 + 2),
    SpriteForChar,
    -1,
    -1,
    -1,
    -1,
    1,
    0,
    0);
  g_RenderDevice = v19;
  Render_Present((int)g_RenderState);
  result = Render_SetResourceHandle((int)&unk_51D4C0, v5);
  if ( *((_DWORD *)a1 + 7) )
    return (*((int (**)(void))a1 + 7))();
  return result;
}
// 44A54B: variable 'v4' is possibly undefined
// 44A591: variable 'v9' is possibly undefined
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044A6D0) --------------------------------------------------------
unsigned int  Options_AnimateSliderThumbDrag(int a1)
{
  unsigned int result; // eax
  int v3; // eax
  int v4; // esi
  int v5; // edx
  int v6; // esi
  int v7; // edi
  DWORD v8; // ebp
  int v9; // edx
  int v10; // esi
  DWORD v11; // ebp
  unsigned __int16 SpriteHeight; // ax
  char v13; // cl

  result = DD_IsFlipping((int)g_RenderState);
  if ( result )
  {
    v3 = *(_DWORD *)(a1 + 12) * (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1);
    v4 = *(_DWORD *)a1 + ((v3 - (__CFSHL__(v3 >> 31, 8) + (v3 >> 31 << 8))) >> 8);
    result = dword_544D00 >> byte_54512C;
    if ( dword_544D00 >> byte_54512C >= *(_DWORD *)(a1 + 8) )
    {
      v5 = (unsigned __int16)DLX_GetSpriteWidth(**(_DWORD **)(a1 + 20), *(_WORD *)(a1 + 24)) + *(_DWORD *)(a1 + 8);
      result = dword_544D00 >> byte_54512C;
      if ( dword_544D00 >> byte_54512C <= v5 )
      {
        if ( v4 > dword_544CFC >> byte_54512C
          || dword_544CFC >> byte_54512C > (unsigned __int16)DLX_GetSpriteHeight(
                                                               **(_DWORD **)(a1 + 20),
                                                               *(_WORD *)(a1 + 24))
                                         + v4 )
        {
          v10 = dword_544CFC;
          v11 = *(_DWORD *)a1;
          SpriteHeight = DLX_GetSpriteHeight(**(_DWORD **)(a1 + 20), *(_WORD *)(a1 + 24));
          result = (int)(((v10 >> v13) - v11 - SpriteHeight / 2) << 8) / (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1);
          if ( result <= 0x100 )
          {
            *(_DWORD *)(a1 + 12) = result;
            return Options_DrawSliderThumb((unsigned __int16 *)a1, a1, v11);
          }
        }
        else
        {
          v6 = dword_544CFC >> byte_54512C;
          v7 = dword_544CFC >> byte_54512C;
          v8 = *(_DWORD *)(a1 + 12);
          while ( 1 )
          {
            result = DD_IsFlipping((int)g_RenderState);
            if ( !result )
              break;
            DD_Pump((int)g_RenderState, a1);
            if ( v6 != dword_544CFC >> byte_54512C )
            {
              v9 = (((dword_544CFC >> byte_54512C) - v7) << 8) / (*(_DWORD *)(a1 + 4) - *(_DWORD *)a1) + v8;
              *(_DWORD *)(a1 + 12) = v9;
              if ( v9 < 0 )
              {
                *(_DWORD *)(a1 + 12) = 0;
              }
              else if ( v9 > 256 )
              {
                *(_DWORD *)(a1 + 12) = 256;
              }
              Options_DrawSliderThumb((unsigned __int16 *)a1, a1, v8);
              v6 = dword_544CFC >> byte_54512C;
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
  unsigned __int16 *v3; // edx
  int v4; // edx

  v3 = result;
  if ( *(_DWORD *)result != -1 )
  {
    do
    {
      result = (unsigned __int16 *)Options_DrawSliderThumb(v3, a2, a3);
      a2 = *(_DWORD *)(v4 + 36);
      v3 = (unsigned __int16 *)(v4 + 36);
    }
    while ( a2 != -1 );
  }
  return result;
}
// 44A893: variable 'v4' is possibly undefined

//----- (0044A8B0) --------------------------------------------------------
_DWORD * Options_AnimateAllSliderThumbs(_DWORD *result)
{
  int v1; // edx
  int v2; // edx
  int v3; // ebx

  v1 = (int)result;
  if ( *result != -1 )
  {
    do
    {
      result = (_DWORD *)Options_AnimateSliderThumbDrag(v1);
      v3 = *(_DWORD *)(v2 + 36);
      v1 = v2 + 36;
    }
    while ( v3 != -1 );
  }
  return result;
}
// 44A8C3: variable 'v2' is possibly undefined

//----- (0044A8E0) --------------------------------------------------------
_DWORD * Options_DestroySliderThumbList(_DWORD *result)
{
  _DWORD *v1; // ecx
  int v2; // esi
  int v3; // ebx

  v1 = result;
  if ( *result != -1 )
  {
    do
    {
      v2 = v1[8];
      if ( v2 )
        result = (_DWORD *)(**(int (***)(void))(v2 + 184))();
      v1[8] = 0;
      v3 = v1[9];
      v1 += 9;
    }
    while ( v3 != -1 );
  }
  return result;
}
// 44A905: variable 'v1' is possibly undefined

//----- (0044A920) --------------------------------------------------------
void  lodaOptionsCfg(DWORD a1)
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // [esp-4h] [ebp-Ch]
  int v6; // [esp+0h] [ebp-8h] BYREF

  v2 = FileSystem_ResolveReadPath(aOptions_cfg, 0);
  v6 = v2;
  if ( v2 )
  {
    v5 = v3;
    (*(void (**)(void))(*(_DWORD *)v2 + 20))();
    Compat_FileSystemQueryRelease(v4, &v6);
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
  int v2; // eax
  int v3; // ecx

  v2 = IO_FOpen(aOptions_cfg_0, (unsigned __int8 *)aWb_1, a1, a2);
  fwrite_(&g_OptionsConfigRecordBase, 27, v2, 1);
  return fclose_(v3);
}
// 44A9AD: variable 'v3' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 5188B0: using guessed type int dword_5188B0;

//----- (0044A9C0) --------------------------------------------------------
void  Options_ApplyRecordSettings(int a1, int a2, DWORD a3)
{
  int v5; // edx
  _DWORD v6[260]; // [esp-40Ch] [ebp-410h] BYREF

  v6[258] = a2;
  Palette_SetBrightnessOffset((int)&unk_51D4C0, *(char *)(a1 + 26));
  _wcpp_4_copy_array__(v6[0]);
  Palette_ApplyWithBrightnessOffset((int *)&unk_51D4C0, v6);
  RenderState_SetMouseSpeed((int)g_RenderState, 8 * *(unsigned __int8 *)(a1 + 25) + 20, a3);
  if ( (int *)a1 == &g_OptionsConfigRecordBase )
  {
    if ( *(_DWORD *)(a1 + 16) )
      Audio_SetMusicActiveFlag();
    else
      Audio_ClearMusicActiveFlag();
  }
  else if ( *(_DWORD *)(a1 + 16) )
  {
    Audio_StartMainMusicIfStopped(v5, a3);
  }
  else
  {
    Audio_StopMainMusicIfPlaying();
  }
  if ( *(_DWORD *)(a1 + 20) )
    Audio_EnableUnitSounds();
  else
    Audio_DisableUnitSounds();
}
// 44AA23: variable 'v5' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);
// 5188B0: using guessed type int dword_5188B0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044AD60) --------------------------------------------------------
char  PlayerRuntimeState_ResetDefaults(uintptr_t a1)
{
  uintptr_t v1; // ecx
  uintptr_t v2; // edx

  v1 = a1;
  *(_DWORD *)(a1 + PLAYER_MINIMAP_VISIBLE_OFFSET) = 0;
  *(_DWORD *)(a1 + 43) = -1;
  *(_DWORD *)(a1 + 35) = 1;
  *(_BYTE *)(a1 + 47) = 1;
  *(_BYTE *)(a1 + 48) = 1;
  *(_DWORD *)(a1 + PLAYER_RELIGION_FLAG_OFFSET) = 1;
  *(_DWORD *)(a1 + PLAYER_IS_HUMAN_OFFSET) = 1;
  *(_DWORD *)(a1 + PLAYER_AI_INTELLIGENCE_OFFSET) = 0;
  *(_DWORD *)a1 = 0;
  *(_WORD *)(a1 + 1417) = 0;
  v2 = a1 + 60;
  *(_BYTE *)(a1 + PLAYER_QUEEN_RELATIONSHIP_STATE_OFFSET) = 0;
  do
  {
    a1 += 6;
    *(_BYTE *)(a1 + 1351) = -1;
  }
  while ( a1 != v2 );
  memset((void *)(v1 + PLAYER_REVEALED_TILES_OFFSET), 0, 0x514u);
  strcpy((char *)(v1 + PLAYER_DISPLAY_NAME_OFFSET), aDoc);
  return 0;
}

//----- (0044AE10) --------------------------------------------------------
char  Game_ResetPlayerRuntimeStateByIndex(int a1)
{
  return PlayerRuntimeState_ResetDefaults(PLAYER_RUNTIME_STATE(a1));
}
// 5202E4: using guessed type int gameData;

//----- (0044AE90) --------------------------------------------------------
int  Map_LoadFromFile(uintptr_t a1)
{
  int v3; // rax
  __int16 *v4; // ebp
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
  int v31; // eax
  int v32; // eax
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
  char v45[100]; // [esp+0h] [ebp-90h] BYREF
  int v46; // [esp+64h] [ebp-2Ch] BYREF
  _BYTE *v47; // [esp+68h] [ebp-28h]
  uintptr_t v48; // [esp+6Ch] [ebp-24h]
  __int16 *v49; // [esp+70h] [ebp-20h]
  int v50; // [esp+74h] [ebp-1Ch]

  v48 = a1;
  memset((void *)(uintptr_t)(unsigned int)gameData, 0, 0x8F29Eu);
  v3 = (int)nmalloc_(0x13880, 1);
  v4 = (__int16 *)(uintptr_t)(unsigned int)v3;
  if ( !v4 )
    return 0;
  strcpy(v45, aMapsDirectory);
  v49 = (__int16 *)(uintptr_t)(unsigned int)v3;
  v6 = (char *)v48;
  v47 = (_BYTE *)(uintptr_t)(unsigned int)v3;
  v7 = &v45[strlen(v45)];
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
  v46 = FileSystem_ResolveReadPath(v45, 1);
  if ( !v46 )
  {
    Compat_FreeLow32Bytes(v3);
    return 0;
  }
  v10 = 0;
  Compat_QueryRead(v46, v4, 0x13880);
  do
  {
    v11 = v4;
    for ( i = 0; i != 1400; *(_WORD *)(i + v10 + gameData - 14) = v13 )
    {
      i += 14;
      v13 = *v11++;
    }
    v10 += 1400;
    v4 += 200;
  }
  while ( v10 != 140000 );
  v14 = v49;
  v15 = 0;
  Compat_QueryRead(v46, v49, 0x13880);
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
  v19 = v49;
  v20 = 0;
  Compat_QueryRead(v46, v49, 0x13880);
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
  v24 = v47;
  v25 = 0;
  Compat_QueryRead(v46, v47, 0x9C40);
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
  Compat_QueryRead(v46, (void *)(uintptr_t)(unsigned int)(gameData + 0x222F0), 1);
  Compat_FileSystemQueryRelease((int)&dword_543CC8, &v46);
  Compat_FreeLow32Bytes(v3);
  v30 = 0;
  v31 = 0;
  do
  {
    if ( *(unsigned __int16 *)(gameData + v30) == 0xFFFF )
      break;
    v30 += 1400;
    ++v31;
  }
  while ( v30 < 140000 );
  MAP_WIDTH_TILES = v31;
  v32 = 0;
  for ( n = 0; n < 1400; n += 14 )
  {
    if ( *(unsigned __int16 *)(gameData + n) == 0xFFFF )
      break;
    ++v32;
  }
  MAP_HEIGHT_TILES = v32;
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
      *(_WORD *)(v39 + gameData + v42 + 556374) = -1;
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
  *(_BYTE *)(gameData + 140021) = 0;
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
  *(_DWORD *)(gameData + 140024) = 1;
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
  *(_DWORD *)(gameData + 140024) = 1;
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
  *(_WORD *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 509690) = 0;
  Unit_UpdatePerTurn(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 509674, v3);
  *(_DWORD *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510112) = 1000;
  v4 = gameData;
  v5 = 467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000);
  v6 = *(_BYTE *)(v5 + gameData + 510118) & 0xF8;
  *(_BYTE *)(v5 + gameData + 510118) = v6;
  *(_BYTE *)(v5 + v4 + 510118) = v6 | 2;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510090) |= 2u;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510090) |= 1u;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510090) |= 8u;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510090) |= 4u;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510090) |= 0x10u;
  *(_DWORD *)(gameData + 140063) = 0;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510119) = 33;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510120) = 2;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510125) = 34;
  *(_BYTE *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 510126) = 4;
  Building_LogBuiltCastleFacts(
    (unsigned __int8 *)(467 * (*(unsigned __int16 *)(gameData + 557382) - 0x8000) + gameData + 509674));
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
  *(_BYTE *)(gameData + 725 * *(unsigned __int16 *)(gameData + 557586) + 147189) = 1;
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
  *(_WORD *)(467 * (*(unsigned __int16 *)(gameData + 557464) - 0x8000) + gameData + 509690) = 0;
  Unit_UpdatePerTurn(467 * (*(unsigned __int16 *)(gameData + 557464) - 0x8000) + gameData + 509674, this);
  result = Building_LogBuiltCastleFacts(
             (unsigned __int8 *)(467 * (*(unsigned __int16 *)(gameData + 557464) - 0x8000) + gameData + 509674));
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
  int v0; // edi
  int v1; // ebp
  int v2; // edx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // edx
  signed int result; // eax

  v0 = 0;
  v1 = 0;
  do
  {
    if ( PLAYER_IS_ACTIVE(v0) )
    {
      v2 = 0;
      v3 = 0;
      while ( *(unsigned __int8 *)(gameData + v3 + 509676) != v0 )
      {
        v3 += 467;
        ++v2;
        if ( v3 >= 46700 )
          goto LABEL_13;
      }
      PLAYER_CAMERA_LEFT(v0) = *(unsigned __int8 *)(gameData + v3 + 509674) - 4;
      if ( PLAYER_CAMERA_LEFT(v0) < 0 )
        PLAYER_CAMERA_LEFT(v0) = 0;
      v4 = MAP_WIDTH_TILES - 9;
      if ( v4 < PLAYER_CAMERA_LEFT(v0) )
        PLAYER_CAMERA_LEFT(v0) = v4;
      PLAYER_CAMERA_TOP(v0) = *(unsigned __int8 *)(467 * v2 + gameData + 509675) - 3;
      if ( PLAYER_CAMERA_TOP(v0) < 0 )
        PLAYER_CAMERA_TOP(v0) = 0;
      v5 = MAP_HEIGHT_TILES - 7;
      if ( v5 < PLAYER_CAMERA_TOP(v0) )
        PLAYER_CAMERA_TOP(v0) = v5;
    }
LABEL_13:
    ++v0;
    v1 += 1423;
  }
  while ( v0 < 5 );
  v6 = 0;
  VIEWED_PLAYER_INDEX = 0;
  v7 = 0;
  while ( !PLAYER_IS_ACTIVE(v6) || !PLAYER_HAS_HUMAN_CONTROLLER(v6) )
  {
    v7 += 1423;
    ++v6;
    if ( v7 >= 7115 )
      goto LABEL_18;
  }
  VIEWED_PLAYER_INDEX = v6;
LABEL_18:
  v8 = 0;
  result = 0;
  while ( !PLAYER_IS_ACTIVE(v8) )
  {
    result += 1423;
    ++v8;
    if ( result >= 7115 )
      return result;
  }
  g_CurrentPlayerIndex = v8;
  TURN_OWNER_PLAYER_INDEX = v8;
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
signed int  Scenario_LoadAllAiMultiplayerMapAndInitView(int a1)
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
  Scenario_LoadMultiplayerMapAndSeedPlayers(a1, (uintptr_t)player_states);
  return Game_InitPlayerViewState();
}

//----- (0044C7F0) --------------------------------------------------------
DWORD  Battle_RunPresetScenarioByIndex(int a1, DWORD a2, double a3)
{
  int v3; // ebx
  int v4; // edx
  __int16 *v5; // esi
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

  switch ( a1 )
  {
    case 0:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + 1400) = 0;
      *(_BYTE *)(gameData + 140016) = 0;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 1:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + 1400) = 0;
      *(_BYTE *)(gameData + 140016) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 2:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + 1400) = 0;
      *(_BYTE *)(gameData + 140016) = 1;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_ARCHER, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 3:
      *(_WORD *)gameData = 4;
      *(_WORD *)(gameData + 1400) = 4;
      *(_BYTE *)(gameData + 140016) = 0;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 4:
      *(_WORD *)gameData = 9;
      *(_WORD *)(gameData + 1400) = 9;
      *(_BYTE *)(gameData + 140016) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CROSSBOWER, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 5:
      *(_WORD *)gameData = 21;
      *(_WORD *)(gameData + 1400) = 21;
      *(_BYTE *)(gameData + 140016) = 1;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_SPEARMAN, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CYCLOP, UNIT_TYPE_SKELETON, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 6:
      *(_WORD *)gameData = 9;
      *(_WORD *)(gameData + 1400) = 9;
      *(_BYTE *)(gameData + 140016) = 0;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_SKELETON, UNIT_TYPE_WORM, UNIT_TYPE_KNIGHTS, -1);
      createUnit(a3, 1, 0, 1, UNIT_TYPE_SKELETON, UNIT_TYPE_WORM, UNIT_TYPE_KNIGHTS, -1);
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
      goto LABEL_3;
    case 7:
      *(_WORD *)gameData = 4;
      *(_WORD *)(gameData + 1400) = 4;
      *(_BYTE *)(gameData + 140016) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_RAM, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createCastle(a3, 1, 0, 1, 2, aZamek, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CYCLOP, -1);
      return Battle_RunTacticalCombat(
               (__int16 *)(725 * *(unsigned __int16 *)(gameData + 556374) + gameData + 147174),
               0,
               0,
               (unsigned __int8 *)(467 * (*(unsigned __int16 *)(gameData + 556574) - 0x8000) + gameData + 509674),
               a2,
               0);
    case 8:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + 1400) = 0;
      *(_BYTE *)(gameData + 140016) = 1;
      createUnit(a3, 0, 0, 1, UNIT_TYPE_CANNON, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(a3, 1, 0, 0, 2, aZamek_0, UNIT_TYPE_CANNON, UNIT_TYPE_WIZARD, UNIT_TYPE_LIGHT_CAVALRY, -1);
      return Battle_RunTacticalCombat(
               (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556374)),
               0,
               0,
               (unsigned __int8 *)(467 * (*(unsigned __int16 *)(gameData + 556574) - 0x8000) + gameData + 509674),
               a2,
               0);
    case 9:
      *(_WORD *)gameData = 28;
      *(_WORD *)(gameData + 1400) = 28;
      *(_BYTE *)(gameData + 140016) = 2;
      createUnit(a3, 0, 0, 0, UNIT_TYPE_GHOST, UNIT_TYPE_WIZARD, UNIT_TYPE_WINGER, -1);
      v8 = gameData;
      v9 = 725 * *(unsigned __int16 *)(gameData + 556374);
      v10 = *(_BYTE *)(gameData + v9 + 147285) & 0xFC;
      *(_BYTE *)(gameData + v9 + 147285) = v10;
      *(_BYTE *)(v8 + v9 + 147285) = v10 | 1;
      createUnit(a3, 1, 0, 1, UNIT_TYPE_DRAGON, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      v11 = gameData;
      v12 = 725 * *(unsigned __int16 *)(gameData + 556574);
      v13 = *(_BYTE *)(gameData + v12 + 147223) & 0xFC;
      *(_BYTE *)(gameData + v12 + 147223) = v13;
      *(_BYTE *)(v11 + v12 + 147223) = v13 | 1;
      v14 = gameData;
      v15 = 725 * *(unsigned __int16 *)(gameData + 556574);
      v16 = *(_BYTE *)(gameData + v15 + 147316) & 0xFC;
      *(_BYTE *)(gameData + v15 + 147316) = v16;
      *(_BYTE *)(v14 + v15 + 147316) = v16 | 1;
      v17 = gameData;
      v18 = 725 * *(unsigned __int16 *)(gameData + 556574);
      v19 = *(_BYTE *)(gameData + v18 + 147378) & 0xFC;
      *(_BYTE *)(gameData + v18 + 147378) = v19;
      *(_BYTE *)(v17 + v18 + 147378) = v19 | 1;
      v3 = gameData + 147174;
      v4 = *(unsigned __int16 *)(gameData + 556374);
      v5 = (__int16 *)(gameData + 147174 + 725 * *(unsigned __int16 *)(gameData + 556574));
      v6 = 144 * (unsigned __int16)v4;
LABEL_3:
      result = Battle_RunTacticalCombat((__int16 *)(v3 + 5 * (v4 + v6)), v5, 0, 0, a2, 0);
      break;
    default:
      result = 1;
      break;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0044D250) --------------------------------------------------------
signed int  Scenario_LoadMultiplayerMapAndSeedPlayers(int a1, uintptr_t a2)
{
  double v4; // st7
  int v7; // esi
  int v8; // eax
  DWORD v10; // ebp
  int v11; // edi
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
  _BYTE v31[100]; // [esp+0h] [ebp-B0h] BYREF
  int v32; // [esp+64h] [ebp-4Ch]
  int v33; // [esp+68h] [ebp-48h]
  unsigned int v34; // [esp+6Ch] [ebp-44h]
  int v35; // [esp+70h] [ebp-40h]
  int v36; // [esp+74h] [ebp-3Ch]
  int v37; // [esp+78h] [ebp-38h]
  int v38; // [esp+7Ch] [ebp-34h]
  int v39; // [esp+80h] [ebp-30h]
  int v40; // [esp+84h] [ebp-2Ch]
  int v41; // [esp+88h] [ebp-28h]
  int v42; // [esp+8Ch] [ebp-24h]
  int v43; // [esp+90h] [ebp-20h]
  int v44; // [esp+94h] [ebp-1Ch]
  int v45; // [esp+98h] [ebp-18h]

  v4 = sprintf_(v31, "multi%d.map", a1 + 1);
  Map_LoadFromFile((uintptr_t)v31);
  qmemcpy((void *)(gameData + PLAYER_RUNTIME_STATE_OFFSET), (const void *)a2, PLAYER_DATA_STRIDE * 5);
  MiniMap_CreateSurface((DWORD)a2);
  v33 = 1;
  v7 = 0;
  v35 = 0;
  v34 = 40 * a1;
  do
  {
    v8 = v35 + gameData;
    if ( *(_DWORD *)(v35 + gameData + 140024) )
    {
      v41 = g_MultiplayerStartRows[v34 / 4];
      v40 = g_MultiplayerStartColumns[v34 / 4];
      v44 = v40 - 1;
      v36 = v40 + 3;
      v39 = v41 + 2;
      v38 = v40 + 2;
      v42 = 200 * v41;
      v10 = v41 + 1;
      v43 = 200 * (v41 + 2);
      v45 = 200 * (v41 + 1);
      v11 = 2 * v40;
      if ( *(_DWORD *)(v8 + 140051) )
      {
        Unit_Create(UNIT_TYPE_BUILDER, v7, v41, 0, v40);
        Unit_Create(UNIT_TYPE_PEASANT, v7, v10, 0, v40);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556374),
          *(unsigned __int16 *)(gameData + v42 + v11 + 556374),
          0,
          v10,
          v4);
        Building_NewAt(v41, v40, 2, *(unsigned __int16 *)(v42 + gameData + v11 + 556374), v4, aCantbelly, 1);
        *(_WORD *)(467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000) + gameData + 509690) = 0;
        v12 = 467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000);
        *(_DWORD *)(v12 + gameData + 510112) += 50;
        Unit_UpdatePerTurn(
          467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000) + gameData + 509674,
          v13);
        v14 = v38;
        Building_LogBuiltCastleFacts(
          (unsigned __int8 *)(467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000)
                            + gameData
                            + 509674));
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, v7, v41, 0, v14);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v38);
        Unit_Create(UNIT_TYPE_ARCHER, v7, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556378),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556378),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, v7, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556378),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_BUILDER, v7, v10, 0, v36);
        Unit_Create(UNIT_TYPE_ARCHER, v7, v39, 0, v36);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556380),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556380),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, v7, v39, 0, v44);
        Unit_Create(UNIT_TYPE_GORAL, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
          0,
          v10,
          v4);
      }
      else
      {
        v30 = v40;
        *(_DWORD *)(v8 + 140063) = v33;
        LOBYTE(v33) = v33 ^ 1;
        Unit_Create(UNIT_TYPE_BUILDER, v7, v41, 0, v30);
        Unit_Create(UNIT_TYPE_PIKEMAN, v7, v10, 0, v40);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556374),
          *(unsigned __int16 *)(gameData + v42 + v11 + 556374),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_HEAVY_SPEARMAN, v7, v10, 0, v40);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556374),
          *(unsigned __int16 *)(gameData + v42 + v11 + 556374),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, v7, v10, 0, v40);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556374),
          *(unsigned __int16 *)(gameData + v42 + v11 + 556374),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, v7, v10, 0, v40);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556374),
          *(unsigned __int16 *)(gameData + v42 + v11 + 556374),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_PEASANT, v7, v10, 0, v40);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v45 + gameData + 556374),
          *(unsigned __int16 *)(gameData + v42 + v11 + 556374),
          0,
          v10,
          v4);
        Building_NewAt(v41, v40, 2, *(unsigned __int16 *)(v11 + v42 + gameData + 556374), v4, aCantbelly_0, 1);
        *(_WORD *)(467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000) + gameData + 509690) = 0;
        v18 = 467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000);
        *(_DWORD *)(v18 + gameData + 510112) += 100;
        Unit_UpdatePerTurn(
          467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000) + gameData + 509674,
          v19);
        v20 = v38;
        Building_LogBuiltCastleFacts(
          (unsigned __int8 *)(467 * (*(unsigned __int16 *)(gameData + v42 + v11 + 556374) - 0x8000)
                            + gameData
                            + 509674));
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, v7, v41, 0, v20);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v38);
        Unit_Create(UNIT_TYPE_GORAL, v7, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556378),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, v7, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556378),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, v7, v39, 0, v38);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556378),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556378),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_BUILDER, v7, v10, 0, v36);
        Unit_Create(UNIT_TYPE_BUILDER, v7, v39, 0, v36);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556380),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556380),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_ARCHER, v7, v39, 0, v36);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v43 + gameData + 556380),
          *(unsigned __int16 *)(gameData + v45 + v11 + 556380),
          0,
          v10,
          v4);
        v32 = v41 - 1;
        Unit_Create(UNIT_TYPE_PEASANT, v7, v41 - 1, 0, v44);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v41, 0, v44);
        v37 = 200 * v32;
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + 200 * v32 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_PIKEMAN, v7, v41, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_PIKEMAN, v7, v41, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_PEASANT, v7, v41, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v41, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v41, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + v11 + 556372),
          0,
          v10,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, v7, v41, 0, v44);
        Unit_AddToGroup(
          *(unsigned __int16 *)(v11 + v42 + gameData + 556372),
          *(unsigned __int16 *)(gameData + v37 + v11 + 556372),
          0,
          v10,
          v4);
        if ( *(int *)(v35 + gameData + 140055) > 0 )
        {
          Unit_Create(UNIT_TYPE_PEASANT, v7, v39, 0, v44);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_ARCHER, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_ARCHER, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, v7, v10, 0, v44);
          Unit_AddToGroup(
            *(unsigned __int16 *)(v11 + v45 + gameData + 556372),
            *(unsigned __int16 *)(gameData + v43 + v11 + 556372),
            0,
            v10,
            v4);
        }
      }
    }
    ++v7;
    v35 += 1423;
    v34 += 8;
  }
  while ( v7 < 5 );
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
char  Player_AssignRandomUniqueRulerNames(int a1, int *a2)
{
  char result; // al
  int v3; // ebp
  unsigned int v4; // ecx
  int v5; // edx
  int v6; // eax
  char *v7; // esi
  char *v8; // edi
  char v9; // al
  char v10; // al
  int v11; // ecx
  int v12[5]; // [esp+0h] [ebp-30h] BYREF
  int v13; // [esp+14h] [ebp-1Ch]
  int *v14; // [esp+18h] [ebp-18h]

  v13 = a1;
  result = (char)a2;
  v3 = 0;
  qmemcpy(v12, &g_RulerNameHistorySeed, sizeof(v12));
  if ( v13 > 0 )
  {
    v14 = a2;
    while ( 1 )
    {
      v4 = Rng_RandRange(0, 38);
      v5 = 0;
      v6 = 0;
      if ( v4 != v12[0] )
      {
        do
        {
          ++v6;
          ++v5;
        }
        while ( v6 < 5 && v4 != v12[v6] );
      }
      if ( v5 == 5 )
      {
        v7 = g_RulerNameCandidatesTable[v4];
        v8 = (char *)*v14;
        do
        {
          v9 = *v7;
          *v8 = *v7;
          if ( !v9 )
            break;
          v10 = v7[1];
          v7 += 2;
          v8[1] = v10;
          v8 += 2;
        }
        while ( v10 );
        result = Str_TitleCase((_BYTE *)*v14, 5, v4);
        v12[v3++] = v11;
        ++v14;
        if ( v3 >= v13 )
          break;
      }
    }
  }
  return result;
}
// 44E32E: variable 'v11' is possibly undefined
// 518C58: using guessed type char *off_518C58[39];

//----- (0044E350) --------------------------------------------------------
BOOL  UI_RunHoverTooltipZones(__int16 *a1)
{
  BOOL result; // eax
  int v2; // edx
  signed int v3; // ebp
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
  int v31; // [esp+0h] [ebp-4Ch]
  int v32; // [esp+4h] [ebp-48h]
  void *v34; // [esp+1Ch] [ebp-30h]
  int v35; // [esp+20h] [ebp-2Ch]
  int v36; // [esp+24h] [ebp-28h]
  int v37; // [esp+28h] [ebp-24h]
  int v38; // [esp+34h] [ebp-18h]
  unsigned __int16 v39; // [esp+38h] [ebp-14h]
  unsigned __int16 v40; // [esp+3Ch] [ebp-10h]
  unsigned __int16 v41; // [esp+40h] [ebp-Ch]
  unsigned __int16 v42; // [esp+44h] [ebp-8h]

  v34 = g_RenderDevice;
  result = DD_IsLost((int)g_RenderState);
  if ( result )
  {
    while ( 1 )
    {
      v2 = *a1;
      if ( v2 == -1 )
        break;
      v3 = a1[3];
      if ( dword_544CFC >> byte_54512C < v2
        || dword_544D00 >> byte_54512C < a1[1]
        || dword_544CFC >> byte_54512C > a1[2]
        || dword_544D00 >> byte_54512C > v3
        || !*(_DWORD *)&a1[2 * (unsigned __int8)g_LanguageIndex + 4] )
      {
        goto LABEL_4;
      }
      Render_ReleaseSurface(8, v3);
      v35 = dword_544D00 >> byte_54512C;
      v37 = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)&a1[2 * (unsigned __int8)g_LanguageIndex + 4])
          + (dword_544CFC >> byte_54512C);
      v4 = dword_544D00 >> byte_54512C;
      v7 = UI_GetTextXOffset(dword_520728) + v4;
      v32 = v5;
      v36 = v7;
      if ( v5 + *(_DWORD *)(dword_544D14 + 12) > v37 )
        v37 = v5 + *(_DWORD *)(dword_544D14 + 12);
      v8 = *(_DWORD *)(dword_544D14 + 16);
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
      Render_SaveBackbuffer((int)&unk_51D4C0);
      Render_Pump();
      Render_FillRect(0, (_DWORD *)v16, (unsigned __int16)v35, (unsigned __int16)v32, v37, v36, 0, 0);
      Render_Present((int)g_RenderState);
      g_RenderDevice = (_UNKNOWN *)v16;
      UI_DrawText(0, 0, *(_DWORD *)&a1[2 * (unsigned __int8)g_LanguageIndex + 4]);
      v38 = Time_Now(v18, v17);
      v20 = 30;
      v42 = v37 - v32;
      v39 = v36 - v35;
      while ( Time_Now(v19, v20) < (unsigned int)(v38 + 30) )
      {
        v22 = Time_Now(v38, v21);
        Render_BlendSurfaceRect(0, v14, 0, v16, 0, v42, v39, v32, v35, 255 * (v22 - v23) / 0x1Eu);
      }
      Render_FillRect((_DWORD *)v16, 0, 0, 0, v42, v39, v32, v35);
      Render_FlipRect((int)g_RenderState, 0);
      v31 = Time_Now(v25, v24);
      v26 = v32;
      v27 = v35;
      v41 = v37 - v32;
      v40 = v36 - v35;
      while ( Time_Now(v26, v27) < (unsigned int)(v31 + 30) )
      {
        v29 = Time_Now(v28, v31);
        Render_BlendSurfaceRect(0, v16, 0, v14, 0, v41, v40, v32, v35, 255 * (v29 - v30) / 0x1Eu);
      }
      Render_FillRect((_DWORD *)v14, 0, 0, 0, v41, v40, v32, v35);
      if ( v14 )
        (**(void (***)(void))(v14 + 184))();
      if ( v16 )
      {
        (**(void (***)(void))(v16 + 184))();
        a1 += 10;
      }
      else
      {
LABEL_4:
        a1 += 10;
      }
    }
    result = (BOOL)v34;
    g_RenderDevice = v34;
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
        char a1,
        int a2,
        __int16 a3,
        int a4,
        DWORD a5,
        __int16 a6)
{
  int v7; // ebx
  int v8; // ebx
  int v9; // edx
  signed int result; // eax
  char v12; // [esp+4h] [ebp-8h]

  v12 = a2;
  v7 = 1423 * a4;
  Debug_Log(a2, v7, a5, (int)aPrisoner_addto);
  v8 = gameData + 140024 + v7;
  v9 = v8;
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
  *(_WORD *)(v8 + 2 * result + 1359) = a3;
  *(_BYTE *)(v8 + 2 * result + 1357) = a1;
  *(_BYTE *)(v8 + 2 * result + 1358) = v12;
  *(_WORD *)(v8 + 2 * result + 1361) = a6;
  return result;
}
// 44E7EC: conditional instruction was optimized away because eax.4<A
// 5202E4: using guessed type int gameData;

//----- (0044E850) --------------------------------------------------------
signed int  Building_FindFreePrisonerSlot(int a1)
{
  signed int result; // eax

  result = 0;
  while ( BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(a1, result)) != -1 )
  {
    ++result;
    if ( result >= BUILDING_PRISONER_SLOT_COUNT )
      return -1;
  }
  return result;
}

//----- (0044E880) --------------------------------------------------------
int  BuildingPrisoner_RecalculateRansomValue(int a1)
{
  int v1; // ebx
  int v2; // edx
  unsigned int v3; // eax
  int v4; // ecx
  int result; // eax
  int v6; // eax

  v1 = AI_TickNationPostTurn(*(unsigned __int8 *)(a1 + 1));
  v3 = v1 * Rng_RandRange(7, v2) / 0x64;
  *(_WORD *)(v4 + 4) = v3;
  if ( !(_WORD)v3 )
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
    sprintf_(&unk_5441F0, message_format, building + 5);
    result = UI_ShowInfoWindow(
               (int)&unk_5441F0,
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
int  BuildingPrisoner_SetAction(int a1, char a2, DWORD a3)
{
  int v3; // edx
  int result; // eax
  int v5; // ecx

  Debug_Log(a1, a2, a3, (int)aBuilding_setpr);
  result = v3;
  BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(v5, v3)) = a2;
  return result;
}
// 44EB80: variable 'v3' is possibly undefined
// 44EB8E: variable 'v5' is possibly undefined

//----- (0044EBA0) --------------------------------------------------------
int  BuildingPrisoner_GetAction(int a1, int a2)
{
  return BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(a1, a2));
}

//----- (0044EBC0) --------------------------------------------------------
int  Prisoner_Kill(int a1, char a2, DWORD a3)
{
  unsigned __int8 prisoner_slot; // edx

  Debug_Log(a1, a2, a3, (int)aPrisoner_kill0);
  prisoner_slot = (unsigned __int8)a2;
  BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(a1, prisoner_slot)) = -1;
  return prisoner_slot;
}

//----- (0044EBF0) --------------------------------------------------------
int  Prisoner_Behead(int a1, int a2, char a3, DWORD a4)
{
  int v4; // ecx
  int v5; // ecx
  int result; // eax
  int v7; // ecx
  const char *v8; // esi
  int v9; // ecx
  _BYTE v10[100]; // [esp+0h] [ebp-74h] BYREF
  int v11[4]; // [esp+64h] [ebp-10h] BYREF

  v11[3] = a2;
  Debug_Log(a1, a3, a4, (int)aPrisoner_behea);
  Prisoner_Kill(v4, a3, a4);
  result = gameData;
  if ( *(_DWORD *)(1423 * *(unsigned __int8 *)(v5 + 2) + gameData + 140051) )
  {
    Win_PlayModeChangeFrameTransition(aZciecie, 1, v5, a3, a4);
    v11[0] = (int)g_PrisonerBeheadingTexts[0];
    v11[1] = (int)g_PrisonerBeheadingTexts[1];
    v11[2] = (int)g_PrisonerBeheadingTexts[2];
    v8 = (const char *)v11[(unsigned __int8)g_LanguageIndex];
    sprintf_(v10, v8, v7 + 5);
    return UI_ShowInfoWindow((const char *)v10, 0, v9, a4, (int)&v11[3], (int)v8);
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
BOOL  Building_IsVisibleToPlayer(unsigned __int8 *a1, int a2)
{
  unsigned __int8 *v3; // ecx
  BOOL result; // eax
  unsigned __int8 *v5; // ecx
  unsigned __int8 *v6; // ecx

  if ( Map_IsTileVisibleToPlayer(*a1, a1[1], a2) )
    return 1;
  if ( Map_IsTileVisibleToPlayer(*v3 + 1, v3[1], a2) )
    return 1;
  if ( Map_IsTileVisibleToPlayer(*v5 + 1, v5[1] + 1, a2) )
    return 1;
  result = Map_IsTileVisibleToPlayer(*v6, v6[1] + 1, a2);
  if ( result )
    return 1;
  return result;
}
// 44ECA6: variable 'v3' is possibly undefined
// 44ECBB: variable 'v5' is possibly undefined
// 44ECD2: variable 'v6' is possibly undefined

//----- (0044ECF0) --------------------------------------------------------
int  Prisoner_FindRichestHiddenEnemyCastle(int a1, int a2)
{
  int v3; // edi
  int v4; // ebx
  int v5; // ecx
  int v7; // eax
  int v9; // [esp+4h] [ebp-18h]

  v3 = 0;
  v4 = 0;
  v5 = 0;
  v9 = -1;
  do
  {
    if ( *(_BYTE *)(v5 + gameData + 509678) == 2
      && *(unsigned __int8 *)(v5 + gameData + 509676) == a1
      && !Building_IsVisibleToPlayer((unsigned __int8 *)(v5 + gameData + 509674), a2) )
    {
      v7 = Building_GetTotalValue(v5 + gameData + 509674);
      if ( v7 > v3 )
      {
        v3 = v7;
        v9 = v4;
      }
    }
    ++v4;
    v5 += 467;
  }
  while ( v4 < 100 );
  if ( v9 == -1 )
    return 0;
  else
    return UNIT_RECORD(v9);
}
// 44ED4A: variable 'v5' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EDB0) --------------------------------------------------------
int  Prisoner_FindAnyHiddenEnemyCastle(int a1, int a2)
{
  int v4; // ecx

  v4 = 0;
  while ( *(_BYTE *)(gameData + v4 + 509678) != 2
       || *(unsigned __int8 *)(gameData + v4 + 509676) != a1
       || Building_IsVisibleToPlayer((unsigned __int8 *)(v4 + gameData + 509674), a2) )
  {
    v4 += 467;
    if ( v4 >= 46700 )
      return 0;
  }
  return v4 + gameData + 509674;
}
// 44EDF0: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EE20) --------------------------------------------------------
int  Prisoner_FindAnyHiddenEnemyUnitStack(int a1, int a2)
{
  int v4; // ecx
  int v5; // edi
  int v6; // eax

  v4 = 0;
LABEL_2:
  if ( (unsigned int)*(__int16 *)(725 * v4 + gameData + 147174 + 6) <= 0x28 )
  {
    v5 = 725 * v4;
    v6 = gameData + 725 * v4;
    if ( *(unsigned __int8 *)(v6 + 147178) == a1
      && !Map_IsTileVisibleToPlayer(*(__int16 *)(v6 + 147174), *(__int16 *)(v6 + 147176), a2) )
    {
      return gameData + 147174 + v5;
    }
  }
  while ( ++v4 < 500 )
  {
    if ( v4 >= 0 )
      goto LABEL_2;
  }
  return 0;
}
// 44EEB0: conditional instruction was optimized away because ecx.4<1F4u
// 44EE57: simplified comparisons for 'eax.4': <0 || >=29 became >=29u
// 44EE9D: variable 'v4' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044EEE0) --------------------------------------------------------
void  Map_RevealTilesInRadius2ForPlayer(int a1, int a2, int a3)
{
  int v3; // edi
  int v4; // esi
  signed int v5; // ecx
  int v7; // [esp+4h] [ebp-24h]
  int v8; // [esp+8h] [ebp-20h]
  int i; // [esp+Ch] [ebp-1Ch]
  int v10; // [esp+14h] [ebp-14h]

  v10 = a2 + 2;
  v3 = a1 - 2;
  v8 = a2 - 2;
  v7 = a1 + 2;
  for ( i = -2; v3 < v7; ++i )
  {
    v4 = v8 - a2;
    if ( v8 < v10 )
    {
      do
      {
        if ( Math_CeilSqrt(i * i + v4 * v4) <= 2 )
          Map_RevealTileWithPropagation(v3, v5, a3);
        ++v4;
      }
      while ( v5 + 1 < v10 );
    }
    ++v3;
  }
  Locale_DrawInteger();
}
// 44EF47: variable 'v5' is possibly undefined

//----- (0044EFA0) --------------------------------------------------------
unsigned int  Prisoner_Torture(int a1, int a2, int a3, char a4, DWORD a5)
{
  unsigned int result; // eax
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  unsigned __int8 *v10; // ebx
  int v11; // ecx
  char **v12; // esi
  int v13; // ecx
  int *v14; // edi
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
      v10 = (unsigned __int8 *)Prisoner_FindRichestHiddenEnemyCastle(*(unsigned __int8 *)(v8 + 6 * a2 + 446), *(unsigned __int8 *)(v8 + 2));
      if ( !v10 )
        return Prisoner_Torture(v9, a2, v9, (char)v10, a5);
      Prisoner_Kill(v9, (char)v10, a5);
      Map_RevealTilesInRadius2ForPlayer(*v10, v10[1], *(unsigned __int8 *)(v11 + 2));
      v27[0] = (int)g_PrisonerTortureRichestCastleRevealTexts[0];
      v27[1] = (int)g_PrisonerTortureRichestCastleRevealTexts[1];
      v27[2] = (int)g_PrisonerTortureRichestCastleRevealTexts[2];
      v12 = &g_PrisonerTortureRichestCastleRevealTexts[3];
      v14 = (int *)v27[(unsigned __int8)g_LanguageIndex];
      sprintf_(&unk_5442C0, (const char *)v14, v13 + 5);
      return UI_ShowInfoWindow((const char *)&unk_5442C0, 0, v15, a5, (int)v14, (int)v12);
    case 1u:
    case 6u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_1);
      v10 = (unsigned __int8 *)Prisoner_FindAnyHiddenEnemyCastle(*(unsigned __int8 *)(v16 + 6 * a2 + 446), *(unsigned __int8 *)(v16 + 2));
      if ( !v10 )
        return Prisoner_Torture(v9, a2, v9, (char)v10, a5);
      Prisoner_Kill(v9, (char)v10, a5);
      Map_RevealTilesInRadius2ForPlayer(*v10, v10[1], *(unsigned __int8 *)(v17 + 2));
      v25[0] = (int)g_PrisonerTortureCastleRevealTexts[0];
      v25[1] = (int)g_PrisonerTortureCastleRevealTexts[1];
      v25[2] = (int)g_PrisonerTortureCastleRevealTexts[2];
      v14 = v26;
      v12 = (char **)v25[(unsigned __int8)g_LanguageIndex];
      sprintf_(&unk_5442C0, (const char *)v12, v18 + 5);
      return UI_ShowInfoWindow((const char *)&unk_5442C0, 0, v15, a5, (int)v14, (int)v12);
    case 2u:
    case 7u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_2);
      v10 = (unsigned __int8 *)Prisoner_FindAnyHiddenEnemyUnitStack(*(unsigned __int8 *)(v19 + 6 * a2 + 446), *(unsigned __int8 *)(v19 + 2));
      if ( !v10 )
        return Prisoner_Torture(v9, a2, v9, (char)v10, a5);
      Prisoner_Kill(v9, (char)v10, a5);
      Map_RevealTilesInRadius2ForPlayer(*(__int16 *)v10, *((__int16 *)v10 + 1), *(unsigned __int8 *)(v20 + 2));
      v29[0] = (int)g_PrisonerTortureEnemyStackRevealTexts[0];
      v29[1] = (int)g_PrisonerTortureEnemyStackRevealTexts[1];
      v29[2] = (int)g_PrisonerTortureEnemyStackRevealTexts[2];
      v12 = &g_PrisonerTortureEnemyStackRevealTexts[3];
      v14 = &v29[3];
      sprintf_(&unk_5442C0, (const char *)v29[(unsigned __int8)g_LanguageIndex], v21 + 5);
      return UI_ShowInfoWindow((const char *)&unk_5442C0, 0, v15, a5, (int)v14, (int)v12);
    case 3u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_3);
      Prisoner_Kill(v22, a4, a5);
      v28[0] = (int)g_PrisonerTortureNoConfessionDeathTexts[0];
      v28[1] = (int)g_PrisonerTortureNoConfessionDeathTexts[1];
      v28[2] = (int)g_PrisonerTortureNoConfessionDeathTexts[2];
      v12 = &g_PrisonerTortureNoConfessionDeathTexts[3];
      v14 = v29;
      sprintf_(&unk_5442C0, (const char *)v28[(unsigned __int8)g_LanguageIndex], v23 + 5);
      return UI_ShowInfoWindow((const char *)&unk_5442C0, 0, v15, a5, (int)v14, (int)v12);
    case 4u:
      Debug_Log(v7, a4, a5, (int)aPrisoner_tor_4);
      BUILDING_PRISONER_ACTION(BUILDING_PRISONER_SLOT(v24, a2)) = BUILDING_PRISONER_ACTION_NONE;
      v26[0] = (int)g_PrisonerTortureResistanceTexts[0];
      v26[1] = (int)g_PrisonerTortureResistanceTexts[1];
      v26[2] = (int)g_PrisonerTortureResistanceTexts[2];
      v12 = &g_PrisonerTortureResistanceTexts[3];
      v14 = v27;
      sprintf_(&unk_5442C0, (const char *)v26[(unsigned __int8)g_LanguageIndex], v24 + 5);
      return UI_ShowInfoWindow((const char *)&unk_5442C0, 0, v15, a5, (int)v14, (int)v12);
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
int  Building_CreateSpecialPersonageGarrisonUnit(DWORD a1, unit_type a2, int a3, char a4, double a5)
{
  int garrison_slot_ptr; // edx
  int slot_index; // eax
  int result; // eax
  int slot_offset; // ecx
  int leave_mask[12]; // [esp+0h] [ebp-48h] BYREF

  Debug_Log(a3, a4, a1, (int)aBuilding_creat);
  garrison_slot_ptr = a1 + 18;
  for ( slot_index = 0; slot_index < 12; ++slot_index )
  {
    if ( *(__int16 *)garrison_slot_ptr == -1 )
      break;
    garrison_slot_ptr += 31;
  }
  if ( slot_index == 12 )
  {
    qmemcpy(leave_mask, &g_SpecialPersonageLeaveMaskTemplate, sizeof(leave_mask));
    Building_UnitsLeave((unsigned __int8 *)a1, leave_mask, a5);
    slot_index = 0;
  }
  slot_offset = 31 * slot_index;
  result = UnitSlot_InitFromType(a1 + 18 + slot_offset, a2, *(_BYTE *)(a1 + 2));
  *(_BYTE *)(a1 + 30 + slot_offset) |= 3u;
  return result;
}

//----- (0044F260) --------------------------------------------------------
unsigned int  Prisoner_Pay(int a1, int a2, DWORD a3, double a4)
{
  DWORD v5; // ecx
  unsigned int result; // eax
  unsigned int v7; // edi
  int v8; // ecx
  int v9; // ecx
  const char *v10; // esi
  int v11; // ecx
  int v12[8]; // [esp+0h] [ebp-20h] BYREF

  Debug_Log(a1, a2, a3, (int)aPrisoner_pay0x);
  if ( *(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(v5 + 2) + 140051) )
  {
    result = BUILDING_PRISONER_RANSOM(BUILDING_PRISONER_SLOT(v5, a2));
    v7 = *(_DWORD *)(v5 + 438);
    if ( result > v7 )
      return result;
    a3 = v7 - result;
    *(_DWORD *)(v5 + 438) = v7 - result;
  }
  Building_CreateSpecialPersonageGarrisonUnit(v5, BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(v5, a2)), v5, a2, a4);
  Prisoner_Kill(v8, a2, a3);
  result = 1423 * *(unsigned __int8 *)(v9 + 2);
  if ( *(_DWORD *)(gameData + result + 140051) )
  {
    v12[0] = (int)g_PrisonerBriberyDefectionTexts[0];
    v12[1] = (int)g_PrisonerBriberyDefectionTexts[1];
    v12[2] = (int)g_PrisonerBriberyDefectionTexts[2];
    v10 = (const char *)v12[(unsigned __int8)g_LanguageIndex];
    sprintf_(&unk_5442C0, v10, v9 + 5);
    return UI_ShowInfoWindow((const char *)&unk_5442C0, 0, v11, a3, (int)&v12[3], (int)v10);
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
char  Prisoner_NewTurn(DWORD a1, int a2, char a3, double a4)
{
  int v5; // edx
  int v6; // eax
  int v7; // ebx
  char *v8; // ecx
  int v9; // ecx
  _BYTE v11[100]; // [esp+0h] [ebp-90h] BYREF
  int v12[3]; // [esp+64h] [ebp-2Ch]
  int v13; // [esp+70h] [ebp-20h] BYREF
  DWORD v14; // [esp+74h] [ebp-1Ch]

  v5 = ACTIVE_MISSION_INDEX;
  if ( v5 != 4 && v5 != 6 || (v6 = 1423 * *(unsigned __int8 *)(a1 + 2), *(_DWORD *)(gameData + v6 + 140051)) )
  {
    Debug_Log(a2, a3, a1, (int)aPrisoner_newtu);
    v14 = a1 + 5;
    v7 = 0;
    v8 = (char *)a1;
    v13 = a1 + 445;
    do
    {
      v6 = v8[445];
      if ( v6 != -1 )
      {
        ++v8[447];
        if ( !*(_DWORD *)(gameData + 1423 * *(unsigned __int8 *)(a1 + 2) + 140051) && v8[447] == 9 )
          v8[448] = BUILDING_PRISONER_ACTION_PAY;
        BuildingPrisoner_RecalculateRansomValue(v13);
        if ( v8[447] == 10 )
        {
          v8[445] = -1;
          v6 = 1423 * *(unsigned __int8 *)(a1 + 2);
          if ( *(_DWORD *)(gameData + v6 + 140051) )
          {
            v12[0] = (int)g_PrisonerDeathByExhaustionTexts[0];
            v12[1] = (int)g_PrisonerDeathByExhaustionTexts[1];
            v12[2] = (int)g_PrisonerDeathByExhaustionTexts[2];
            a4 = sprintf_(v11, (const char *)v12[(unsigned __int8)g_LanguageIndex], v14);
            LOBYTE(v6) = UI_ShowInfoWindow((const char *)v11, 0, v9, a1, (int)&v13, (int)&g_PrisonerDeathByExhaustionTexts[3]);
          }
        }
        else
        {
          LOBYTE(v6) = v8[448];
          if ( (unsigned __int8)v6 >= BUILDING_PRISONER_ACTION_TORTURE )
          {
            if ( (unsigned __int8)v6 <= BUILDING_PRISONER_ACTION_TORTURE )
            {
              LOBYTE(v6) = Prisoner_Torture(a1, v7, (int)v8, v7, a1);
            }
            else if ( (_BYTE)v6 == BUILDING_PRISONER_ACTION_PAY )
            {
              LOBYTE(v6) = Prisoner_Pay(a1, v7, a1, a4);
            }
          }
          else if ( (_BYTE)v6 == BUILDING_PRISONER_ACTION_BEHEAD )
          {
            LOBYTE(v6) = Prisoner_Behead(a1, (int)v8, v7, a1);
          }
        }
      }
      v8 += 6;
      ++v7;
      v13 += 6;
    }
    while ( v7 < 3 );
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
int  Building_CountPrisoners(int a1)
{
  int v1; // ebx
  int v2; // edx

  v1 = a1 + 18;
  v2 = 0;
  do
  {
    if ( *(char *)(a1 + 445) != -1 )
      ++v2;
    a1 += 6;
  }
  while ( a1 != v1 );
  return v2;
}

//----- (0044F510) --------------------------------------------------------
BOOL  BuildingPrisonerActionWidget_HasPrisoner(int a1)
{
  return *(char *)(dword_5443FC + 6 * ((a1 - (int)&g_PrisonerActionButtonWidgets) / 53 / 3) + 445) != -1;
}
// 5443FC: using guessed type int dword_5443FC;

//----- (0044F580) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectBehead(int a1)
{
  char *result; // eax
  unsigned __int8 v4; // ah
  _DWORD *v5; // ebx
  int v6; // ecx

  Render_Begin((int)g_RenderState, 0);
  result = (char *)BuildingPrisonerActionWidget_HasPrisoner(a1);
  if ( result )
  {
    v4 = *(_BYTE *)(a1 + 8) ^ 1;
    *(_BYTE *)(a1 + 8) = v4;
    *(_BYTE *)(a1 + 8) = v4 ^ 2;
    if ( ((v4 ^ 2) & 2) != 0 )
    {
      v5 = g_PrisonerActionButtonWidgets;
      v6 = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * v6) = 1;
        UIWidget_RefreshActionButtonState((int)v5, v6 + 1);
        v5 = (_DWORD *)((char *)v5 + 53);
      }
      while ( v6 < 9 );
      *(_DWORD *)(a1 + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(a1 + 49));
  }
  return result;
}
// 44F5BA: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F5F0) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectTorture(int a1)
{
  char *result; // eax
  unsigned __int8 v4; // ah
  _DWORD *v5; // ebx
  int v6; // ecx

  Render_Begin((int)g_RenderState, 0);
  result = (char *)BuildingPrisonerActionWidget_HasPrisoner(a1);
  if ( result )
  {
    v4 = *(_BYTE *)(a1 + 8) ^ 1;
    *(_BYTE *)(a1 + 8) = v4;
    *(_BYTE *)(a1 + 8) = v4 ^ 2;
    if ( ((v4 ^ 2) & 2) != 0 )
    {
      v5 = g_PrisonerActionButtonWidgets;
      v6 = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * v6) = 1;
        UIWidget_RefreshActionButtonState((int)v5, v6 + 1);
        v5 = (_DWORD *)((char *)v5 + 53);
      }
      while ( v6 < 9 );
      *(_DWORD *)(a1 + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(a1 + 49));
  }
  return result;
}
// 44F62A: variable 'v6' is possibly undefined
// 518DC8: using guessed type _DWORD dword_518DC8[2];
// 518DD0: using guessed type int dword_518DD0;
// 544CD8: using guessed type _DWORD g_RenderState[9];

//----- (0044F660) --------------------------------------------------------
char * BuildingPrisonerActionButton_SelectBribery(int a1)
{
  char *result; // eax
  unsigned __int8 v4; // ah
  _DWORD *v5; // ebx
  int v6; // ecx

  Render_Begin((int)g_RenderState, 0);
  result = (char *)BuildingPrisonerActionWidget_HasPrisoner(a1);
  if ( result )
  {
    v4 = *(_BYTE *)(a1 + 8) ^ 1;
    *(_BYTE *)(a1 + 8) = v4;
    *(_BYTE *)(a1 + 8) = v4 ^ 2;
    if ( ((v4 ^ 2) & 2) != 0 )
    {
      v5 = g_PrisonerActionButtonWidgets;
      v6 = 0;
      do
      {
        *(int *)((char *)&g_PrisonerActionButtonState0 + 53 * v6) = 1;
        UIWidget_RefreshActionButtonState((int)v5, v6 + 1);
        v5 = (_DWORD *)((char *)v5 + 53);
      }
      while ( v6 < 9 );
      *(_DWORD *)(a1 + 8) = 2;
    }
    return Audio_PlayButtonSound(*(char **)(a1 + 49));
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
  dword_5443F4 = v3;
  return result;
}
// 44F6DB: variable 'v3' is possibly undefined
// 5443F4: using guessed type int dword_5443F4;

//----- (0044FC70) --------------------------------------------------------
int  Building_DrawPrisonerRows(DWORD a1)
{
  int v1; // edi
  int v2; // esi
  int result; // eax
  int SpriteForChar; // eax
  int v5; // eax

  v1 = 0;
  v2 = 0;
  g_RenderDevice = &unk_51D4C0;
  Render_ReleaseSurface(18, a1);
  do
  {
    result = *(char *)(v1 + dword_5443FC + 445);
    if ( result != -1 )
    {
      SpriteForChar = DLX_GetSpriteForChar(dword_5443F0, 5);
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
      v5 = DLX_GetSpriteForChar(dword_5443F0, *(unsigned __int8 *)(v1 + dword_5443FC + 446));
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
                 v1,
                 (unsigned __int16)g_PrisonerRowTextXTable[v2] + 1,
                 (unsigned __int16)g_PrisonerRowTextXTable[v2] + 68,
                 461,
                 3,
                 (int)aD_79);
    }
    ++v2;
    v1 += 6;
  }
  while ( v2 != 3 );
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

  g_RenderDevice = &unk_51D4C0;
  queenRelationshipState = PLAYER_QUEEN_RELATIONSHIP_STATE(g_CurrentPlayerIndex);
  if ( queenRelationshipState > 0 )
  {
    SpriteForChar = DLX_GetSpriteForChar(dword_5443F0, PLAYER_QUEEN_PORTRAIT_INDEX(g_CurrentPlayerIndex) + 25);
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
int  Building_ShowPrisonerManagementPanel(int a1, void *a2, DWORD a3)
{
  int i; // eax
  _DWORD *v4; // esi
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
  int v23; // ebp
  int v24; // ecx
  int v25; // esi
  int v26; // edi
  int v27; // ebx
  int v28; // ebx
  int v29; // eax
  int v30; // edx
  int v31; // ebx
  int v32; // eax
  int v33; // eax
  int v34; // ebx
  int v35; // eax
  DWORD v36; // ebp
  int v37; // eax
  int v38; // eax
  int v39; // edi
  int v40; // esi
  int v41; // esi
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
  int v61[5]; // [esp+C4h] [ebp-64h]
  int v62[5]; // [esp+D8h] [ebp-50h]
  int v63[5]; // [esp+ECh] [ebp-3Ch]
  int v64; // [esp+100h] [ebp-28h]
  int v65; // [esp+104h] [ebp-24h]
  int v66; // [esp+108h] [ebp-20h]
  int v67; // [esp+10Ch] [ebp-1Ch]

  dword_5443FC = a1;
  for ( i = 0; i != 477; *(char **)((char *)g_PrisonerDeathByExhaustionTexts + i + 3) = (char *)1 )
    i += 53;
  v4 = g_PrisonerActionButtonWidgets;
  for ( j = 0; j < 3; ++j )
  {
    v6 = BuildingPrisoner_GetAction(dword_5443FC, j);
    if ( v6 >= BUILDING_PRISONER_ACTION_TORTURE )
    {
      if ( v6 <= BUILDING_PRISONER_ACTION_TORTURE )
      {
        *(_DWORD *)((char *)v4 + 61) = v7;
      }
      else if ( v6 == BUILDING_PRISONER_ACTION_PAY )
      {
        *(_DWORD *)((char *)v4 + 114) = v7;
      }
    }
    else if ( v6 == BUILDING_PRISONER_ACTION_BEHEAD )
    {
      v4[2] = v7;
    }
    v4 = (_DWORD *)((char *)v4 + 159);
  }
  v8 = Mem_Alloc(1024, v7, (char)a2, a3);
  if ( v8 )
  {
    a2 = &g_Runtime_PaletteArrayCtorDescriptor;
    v8 = _wcpp_4_ctor_array__(v9, 256);
  }
  dword_5443F8 = v8;
  v10 = (_DWORD *)Mem_Alloc(4112, v9, (char)a2, a3);
  if ( v10 )
    v10 = DLXSpriteSet_Load(v10, (char)a2);
  dword_5443F0 = (int)v10;
  v11 = dword_5443F8;
  (*(void (__fastcall **)(_DWORD, char *))(*(_DWORD *)(dword_5202E0 + 184) + 48))(0, aStat_gfx);
  Palette_LoadOrBuildBlendLookupTable(aStat, dword_5443F8, v12, a3);
  Render_LoadResourceSprite_v4(8, (_BYTE *)dword_5443F8, v13, v11, a3);
  Render_LoadResourceSprite_v4(18, (_BYTE *)dword_5443F8, v14, v11, a3);
  Render_LoadResourceSprite_v4(17, (_BYTE *)dword_5443F8, v15, v11, a3);
  RenderState_LoadOrRenderCursorLabelSprite((int)g_RenderState, dword_5443F8, v16, a3);
  (*(void (__thiscall **)(void *))(*(_DWORD *)(dword_5202E0 + 184) + 36))(&unk_51D4C0);
  g_RenderDevice = v17;
  Render_ReleaseSurface(18, a3);
  if ( *(_DWORD *)(gameData + 140024) )
  {
    SpriteForChar = DLX_GetSpriteForChar(dword_5443F0, (*(_DWORD *)(gameData + 140063) == 0) + 13);
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
    v19 = DLX_GetSpriteForChar(dword_5443F0, (*(_DWORD *)(gameData + 141486) == 0) + 15);
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
    v20 = DLX_GetSpriteForChar(dword_5443F0, (*(_DWORD *)(gameData + 142909) == 0) + 17);
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
    v21 = DLX_GetSpriteForChar(dword_5443F0, (*(_DWORD *)(gameData + 144332) == 0) + 19);
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
    v59 = DLX_GetSpriteForChar(dword_5443F0, (*(_DWORD *)(gameData + 145755) == 0) + 21);
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
  v23 = 0;
  v24 = 0;
  v25 = 0;
  v26 = 0;
  v64 = 0;
  v67 = 0;
  v65 = 0;
  do
  {
    v27 = *(_DWORD *)(v26 + gameData + 140024);
    if ( v24 == v27 )
    {
      v63[v22] = v27;
      v61[v22] = v27;
      v62[v22] = v27;
    }
    else
    {
      v28 = v64;
      v29 = AI_TickNationPostTurn(v25);
      *(int *)((char *)v62 + v30) = v29;
      if ( v29 > v28 )
        v64 = v29;
      v31 = v67;
      v32 = Player_CalcMilitaryStrength(v25);
      v61[v22] = v32;
      if ( v32 > v31 )
        v67 = v32;
      v33 = *(__int16 *)(v26 + gameData + 141441);
      v63[v22] = v33;
      if ( v23 < v33 )
        v23 = v33;
      v34 = v63[v22];
      if ( v24 > v34 && v34 < v65 )
        v65 = v63[v22];
    }
    v26 += 1423;
    ++v25;
    ++v22;
  }
  while ( v25 < 5 );
  g_RenderDevice = (_UNKNOWN *)dword_5202E0;
  v35 = DLX_GetSpriteForChar(dword_5443F0, 24);
  v36 = v23 - v65;
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
  v37 = DLX_GetSpriteForChar(dword_5443F0, 24);
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
  v38 = DLX_GetSpriteForChar(dword_5443F0, 24);
  v39 = 0;
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
  v41 = 0;
  do
  {
    if ( *(_DWORD *)(v66 + gameData + 140024) )
    {
      if ( v64 )
        v42 = v64;
      else
        v42 = 1;
      v43 = 123 * v61[v41];
      v44 = v67;
      v62[v41] = 123 * v62[v41] / v42;
      if ( v44 )
        v45 = v44;
      else
        v45 = 1;
      v46 = v43 / v45;
      v47 = v63[v41];
      v61[v41] = v46;
      v48 = 123 * (v47 - v65);
      if ( v36 )
        v49 = v36;
      else
        v49 = 1;
      v63[v41] = v48 / v49;
      Render_FillRect(
        (_DWORD *)dword_5202E0,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[v39] + 107),
        299,
        LOWORD(v62[v41]) + 299,
        g_PrisonerRowBarBottomYTable[v39] + 107,
        0x12Bu,
        g_PrisonerRowBarTopYTable[v39] + 107);
      Render_FillRect(
        (_DWORD *)dword_5202E0,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[v39] + 107),
        88,
        LOWORD(v61[v41]) + 88,
        g_PrisonerRowBarBottomYTable[v39] + 107,
        0x58u,
        g_PrisonerRowBarTopYTable[v39] + 107);
      Render_FillRect(
        (_DWORD *)dword_5202E0,
        0,
        (unsigned __int16)(g_PrisonerRowBarTopYTable[v39] + 107),
        510,
        LOWORD(v63[v41]) + 510,
        g_PrisonerRowBarBottomYTable[v39] + 107,
        0x1FEu,
        g_PrisonerRowBarTopYTable[v39] + 107);
    }
    ++v39;
    ++v41;
    v66 += 1423;
  }
  while ( v39 != 5 );
  Building_DrawPrisonerRows(v36);
  Queen_DrawRelationshipPanel(v36, 10);
  UIWidgetTable_InitDrawStates(g_PrisonerActionButtonWidgets);
  Palette_FadeInFromBlack((int *)&unk_51D4C0, (unsigned __int8 *)dword_5443F8, 20);
  Render_Present((int)g_RenderState);
  dword_5443F4 = v50;
  do
  {
    DD_Pump((int)g_RenderState, (char)g_RenderState);
    g_RenderDevice = &unk_51D4C0;
    UIWidgetTable_PollHoverAndActions(g_PrisonerActionButtonWidgets, v36);
  }
  while ( v51 == dword_5443F4 );
  if ( g_PrisonerActionButtonState0 == 2 )
  {
    v52 = BUILDING_PRISONER_ACTION_BEHEAD;
LABEL_48:
    v53 = dword_5443FC;
    goto LABEL_49;
  }
  if ( g_PrisonerActionButtonState1 == 2 )
  {
    v53 = dword_5443FC;
    v52 = BUILDING_PRISONER_ACTION_TORTURE;
  }
  else
  {
    if ( g_PrisonerActionButtonState2 == 2 )
    {
      v52 = BUILDING_PRISONER_ACTION_PAY;
      goto LABEL_48;
    }
    v53 = dword_5443FC;
    v52 = BUILDING_PRISONER_ACTION_NONE;
  }
LABEL_49:
  BuildingPrisoner_SetAction(v53, v52, v36);
  if ( g_PrisonerActionButtonState3 == 2 )
  {
    v54 = BUILDING_PRISONER_ACTION_BEHEAD;
    v55 = dword_5443FC;
  }
  else if ( g_PrisonerActionButtonState4 == 2 )
  {
    v55 = dword_5443FC;
    v54 = BUILDING_PRISONER_ACTION_TORTURE;
  }
  else if ( g_PrisonerActionButtonState5 == 2 )
  {
    v54 = BUILDING_PRISONER_ACTION_PAY;
    v55 = dword_5443FC;
  }
  else
  {
    v55 = dword_5443FC;
    v54 = BUILDING_PRISONER_ACTION_NONE;
  }
  BuildingPrisoner_SetAction(v55, v54, v36);
  if ( g_PrisonerActionButtonState6 == 2 )
  {
    v56 = BUILDING_PRISONER_ACTION_BEHEAD;
    v57 = dword_5443FC;
  }
  else if ( g_PrisonerActionButtonState7 == 2 )
  {
    v56 = BUILDING_PRISONER_ACTION_TORTURE;
    v57 = dword_5443FC;
  }
  else if ( g_PrisonerActionButtonState8 == 2 )
  {
    v56 = BUILDING_PRISONER_ACTION_PAY;
    v57 = dword_5443FC;
  }
  else
  {
    v57 = dword_5443FC;
    v56 = BUILDING_PRISONER_ACTION_NONE;
  }
  BuildingPrisoner_SetAction(v57, v56, g_PrisonerActionButtonState6);
  DLXSpriteSet_ReleaseAndClear(&dword_5443F0);
  j__nfree_();
  Render_Pump();
  return Palette_FadeOutToBlack((int *)&unk_51D4C0, 20);
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

