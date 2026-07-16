/* Generated from src/recovered/core/00401020_bootstrap.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "core_internal.h"
#include "core_state.h"
#include "../state/state_shared.h"
#include "../render/render_api.h"
#include "../persistence/persistence_api.h"
#include "../strategic/strategic_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00401020) --------------------------------------------------------
int App_Shutdown(void)
{
  int v0; // ecx

  RenderState_ReleaseCursorResources((int)&g_RenderState);
  Noop_AppShutdownPreAudioCloseHook();
  CSS_Close();
  Noop_AppShutdownPostAudioCloseHook(v0);
  return Render_BeginModeSwitch(&g_MainRenderDevice);
}
// 401036: variable 'v0' is possibly undefined
// 4207F0: using guessed type int __thiscall nullsub_2(_DWORD);
// 461560: using guessed type int nullsub_4(void);

//----- (004011A0) --------------------------------------------------------
int  Game_Init(int a1, char a2, DWORD allocContext)
{
  int result; // eax

  result = Mem_Alloc(GAMEDATA_SAVE_IMAGE_BYTES, a1, a2, allocContext);
  if ( result )
  {
    result = _wcpp_4_ctor_array__(result + UNIT_STACK_TABLE_OFFSET, UNIT_STACK_TABLE_COUNT) - 147174;
    gameData = result;
  }
  else
  {
    gameData = 0;
  }
  g_WorldMapBackgroundSpriteSet = 0;
  return result;
}
// 472480: using guessed type int __fastcall _wcpp_4_ctor_array__(_DWORD, _DWORD);
// 5202C0: using guessed type int dword_5202C0;
// 5202E4: using guessed type int gameData;

//----- (004011F0) --------------------------------------------------------
char __thiscall DetectGameCDPath(void *this)
{
  char driveLetter; // bl
  UINT DriveTypeA; // eax
  char *suffixSrc; // esi
  char *pathEnd; // edi
  char curChar; // al
  char nextChar; // al
  char *v8; // [esp-4h] [ebp-38h]
  char pathBuffer[52]; // [esp+0h] [ebp-34h] BYREF

  *(_DWORD *)&pathBuffer[44] = (_DWORD)(uintptr_t)this;
  driveLetter = 67;
  qmemcpy(pathBuffer, &g_CDPathTemplate, 0x1Eu);
  while ( 1 )
  {
    pathBuffer[0] = driveLetter;
    DriveTypeA = GetDriveTypeA(pathBuffer);
    if ( DriveTypeA == 5 )
      break;
    if ( (unsigned __int8)++driveLetter > 0x5Au )
      return DriveTypeA;
  }
  suffixSrc = aClash;
  v8 = pathBuffer;
  pathEnd = &pathBuffer[strlen(pathBuffer)];
  do
  {
    curChar = *suffixSrc;
    *pathEnd = *suffixSrc;
    if ( !curChar )
      break;
    nextChar = suffixSrc[1];
    suffixSrc += 2;
    pathEnd[1] = nextChar;
    pathEnd += 2;
  }
  while ( nextChar );
  LOBYTE(DriveTypeA) = FileSystem_SetInstallRootPath(pathBuffer);
  return DriveTypeA;
}
