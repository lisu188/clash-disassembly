/* Application bootstrap, shutdown, and initial game lifecycle.
 * Original function-marker range: 0x00401020..0x004011F0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00401020) --------------------------------------------------------
int App_Shutdown()
{
  int v0; // ecx

  RenderState_ReleaseCursorResources((int)&g_RenderState);
  Noop_AppShutdownPreAudioCloseHook();
  CSS_Close();
  Noop_AppShutdownPostAudioCloseHook(v0);
  return Render_BeginModeSwitch(&unk_51D4C0);
}
// 401036: variable 'v0' is possibly undefined
// 4207F0: using guessed type int __thiscall nullsub_2(_DWORD);
// 461560: using guessed type int nullsub_4(void);

//----- (004011A0) --------------------------------------------------------
int  Game_Init(int a1, char a2, DWORD a3)
{
  int result; // eax

  result = Mem_Alloc(586398, a1, a2, a3);
  if ( result )
  {
    result = _wcpp_4_ctor_array__(result + 147174, 500) - 147174;
    gameData = result;
  }
  else
  {
    gameData = 0;
  }
  dword_5202C0 = 0;
  return result;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;

//----- (004011F0) --------------------------------------------------------
char __thiscall DetectGameCDPath(void *this)
{
  char v1; // bl
  UINT DriveTypeA; // eax
  char *v3; // esi
  char *v4; // edi
  char v5; // al
  char v6; // al
  char *v8; // [esp-4h] [ebp-38h]
  char v9[52]; // [esp+0h] [ebp-34h] BYREF

  *(_DWORD *)&v9[44] = this;
  v1 = 67;
  qmemcpy(v9, &g_CDPathTemplate, 0x1Eu);
  while ( 1 )
  {
    v9[0] = v1;
    DriveTypeA = GetDriveTypeA(v9);
    if ( DriveTypeA == 5 )
      break;
    if ( (unsigned __int8)++v1 > 0x5Au )
      return DriveTypeA;
  }
  v3 = aClash;
  v8 = v9;
  v4 = &v9[strlen(v9)];
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
  LOBYTE(DriveTypeA) = FileSystem_SetInstallRootPath(v9);
  return DriveTypeA;
}

