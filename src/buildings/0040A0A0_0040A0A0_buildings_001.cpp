/* Generated from src/recovered/world/00408030_world_map.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "buildings_internal.h"
#include "buildings_state.h"
#include "buildings_shared_state.h"
#include "../units/units_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (0040A0A0) --------------------------------------------------------
int  WorldMap_ComputeBuildMenuActionFromCursor(int widget, int a2)
{
  int result; // eax

  UIWidget_PlayPressedReleaseAnimationWithDelay(widget, a2);
  result = (*(int *)(uintptr_t)(widget + 16) - 15) / 2;
  g_WorldMapBuilderMenuAction = result;
  return result;
}
// 520308: using guessed type int dword_520308;

CLASH95_INTERNAL void WorldMap_EnsureBuilderWidgetTables(void)
{
  static const _BYTE builder_initial[322] = {
    0xa0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00,
    0xa0, 0xa0, 0x40, 0x00, 0x65, 0xcb, 0x4e, 0x00, 0x6b, 0xcb, 0x4e, 0x00, 0x70, 0xcb, 0x4e, 0x00,
    0x01, 0x77, 0xcb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x0c, 0x03, 0x52, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
    0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0x7c, 0xcb, 0x4e, 0x00, 0x84, 0xcb, 0x4e,
    0x00, 0x89, 0xcb, 0x4e, 0x00, 0x01, 0x8f, 0xcb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0x90, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0x94, 0xcb,
    0x4e, 0x00, 0xa4, 0xcb, 0x4e, 0x00, 0xb5, 0xcb, 0x4e, 0x00, 0x01, 0xc1, 0xcb, 0x4e, 0x00, 0xa0,
    0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x15,
    0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0,
    0xa0, 0x40, 0x00, 0xc6, 0xcb, 0x4e, 0x00, 0xcc, 0xcb, 0x4e, 0x00, 0xd1, 0xcb, 0x4e, 0x00, 0x01,
    0xd6, 0xcb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0c, 0x03, 0x52, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0xdb, 0xcb, 0x4e, 0x00, 0xe4, 0xcb, 0x4e, 0x00,
    0xed, 0xcb, 0x4e, 0x00, 0x01, 0xf5, 0xcb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0xb0, 0x01, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00,
    0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0xa0, 0xa0, 0x40, 0x00, 0xfa, 0xcb, 0x4e,
    0x00, 0x00, 0xcc, 0x4e, 0x00, 0x07, 0xcc, 0x4e, 0x00, 0x01, 0x0c, 0xcc, 0x4e, 0x00, 0xff, 0xff,
    0xff, 0xff,
  };
  static const _BYTE road_initial[706] = {
    0x20, 0x02, 0x00, 0x00, 0x25, 0x02, 0x00, 0x00, 0x34, 0x02, 0x00, 0x00, 0x39, 0x02, 0x00, 0x00,
    0x40, 0x02, 0x00, 0x00, 0x45, 0x02, 0x00, 0x00, 0x22, 0x02, 0x00, 0x00, 0x23, 0x02, 0x00, 0x00,
    0x36, 0x02, 0x00, 0x00, 0x37, 0x02, 0x00, 0x00, 0x42, 0x02, 0x00, 0x00, 0x43, 0x02, 0x00, 0x00,
    0x64, 0x03, 0x66, 0x03, 0x6a, 0x03, 0x6c, 0x03, 0x62, 0x03, 0x63, 0x03, 0x67, 0x03, 0x69, 0x03,
    0x6b, 0x03, 0x65, 0x03, 0x68, 0x03, 0x63, 0x03, 0x63, 0x03, 0x62, 0x03, 0x62, 0x03, 0x64, 0x03,
    0x66, 0x03, 0x6a, 0x03, 0x6c, 0x03, 0x62, 0x03, 0x63, 0x03, 0x67, 0x03, 0x69, 0x03, 0x6b, 0x03,
    0x65, 0x03, 0x68, 0x03, 0x62, 0x03, 0x62, 0x03, 0x63, 0x03, 0x63, 0x03, 0x64, 0x03, 0x66, 0x03,
    0x66, 0x03, 0x6a, 0x03, 0x6a, 0x03, 0x6c, 0x03, 0x62, 0x03, 0x63, 0x03, 0x67, 0x03, 0x69, 0x03,
    0x6b, 0x03, 0x65, 0x03, 0x68, 0x03, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x00,
    0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x1b, 0x00, 0x00, 0x00,
    0x1b, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x91, 0x41, 0x00, 0xe0, 0x54, 0x42, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xeb, 0x4e,
    0x00, 0xe0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52,
    0x00, 0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x91, 0x41,
    0x00, 0xe0, 0x54, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xdf, 0xeb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0xf0, 0x91, 0x41, 0x00, 0xe0, 0x54, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xeb, 0x4e, 0x00, 0xa0, 0x01, 0x00, 0x00, 0xb0,
    0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1e,
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x91, 0x41, 0x00, 0xe0, 0x54, 0x42, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0xeb, 0x4e, 0x00,
    0xa0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00,
    0xf0, 0x50, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xee, 0xeb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x0c, 0x03, 0x52, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00,
    0x00, 0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xeb, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0x90, 0x01,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xeb, 0x4e, 0x00, 0xa0,
    0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x15,
    0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0x10,
    0x51, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xfd, 0xeb, 0x4e, 0x00, 0xe0, 0x01, 0x00, 0x00, 0xb0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x0c, 0x03, 0x52, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xec, 0x4e, 0x00, 0x20, 0x02, 0x00, 0x00, 0xb0, 0x01, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x52, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00,
    0x00, 0x0e, 0x00, 0x00, 0x00, 0xf0, 0x91, 0x41, 0x00, 0x10, 0x51, 0x42, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xec, 0x4e, 0x00, 0xff, 0xff,
    0xff, 0xff,
  };
  static const char widget_text_0[] = "\x44\x72\x6f\x67\x61";
  static const char widget_text_1[] = "\x52\x6f\x61\x64";
  static const char widget_text_2[] = "\x53\x74\x72\x61\xe1\x65";
  static const char widget_text_3[] = "\x6d\x61\x6c\x65";
  static const char widget_text_4[] = "\x50\x75\x92\x61\x70\x6b\x61";
  static const char widget_text_5[] = "\x54\x72\x61\x70";
  static const char widget_text_6[] = "\x46\x61\x6c\x6c\x65";
  static const char widget_text_7[] = "\x4b\x6f\x70\x61\x6e\x69\x65\x20\x73\x6b\x61\x72\x62\xa2\x77";
  static const char widget_text_8[] = "\x44\x69\x67\x20\x66\x6f\x72\x20\x74\x72\x65\x61\x73\x75\x72\x65";
  static const char widget_text_9[] = "\x53\x63\x68\x61\x74\x7a\x73\x75\x63\x68\x65";
  static const char widget_text_10[] = "\x57\x69\x65\xa7\x61";
  static const char widget_text_11[] = "\x4b\x65\x65\x70";
  static const char widget_text_12[] = "\x54\x75\x72\x6d";
  static const char widget_text_13[] = "\x54\x77\x69\x65\x72\x64\x7a\x61";
  static const char widget_text_14[] = "\x46\x6f\x72\x74\x72\x65\x73\x73";
  static const char widget_text_15[] = "\x46\x65\x73\x74\x75\x6e\x67";
  static const char widget_text_16[] = "\x5a\x61\x6d\x65\x6b";
  static const char widget_text_17[] = "\x43\x61\x73\x74\x6c\x65";
  static const char widget_text_18[] = "\x42\x75\x72\x67";
  _DWORD pointer_value;

  if ( g_BuilderRoadWidgetsInitialized )
    return;
  /* PE data bytes are retained; only actual pointer fields are relocated.
   * The 48-DWORD shore scan intentionally overlaps the live north marker. */
  memcpy(g_UI_YesNoDims, builder_initial, sizeof(builder_initial));
  memcpy(g_RoadBuildData, road_initial, sizeof(road_initial));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 12, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 28, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 32, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_0;
  memcpy(g_UI_YesNoDims + 36, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_1;
  memcpy(g_UI_YesNoDims + 40, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_2;
  memcpy(g_UI_YesNoDims + 44, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 49, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 65, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 81, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 85, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_4;
  memcpy(g_UI_YesNoDims + 89, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_5;
  memcpy(g_UI_YesNoDims + 93, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_6;
  memcpy(g_UI_YesNoDims + 97, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 102, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 118, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 134, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 138, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_7;
  memcpy(g_UI_YesNoDims + 142, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_8;
  memcpy(g_UI_YesNoDims + 146, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_9;
  memcpy(g_UI_YesNoDims + 150, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 155, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 171, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 187, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 191, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_10;
  memcpy(g_UI_YesNoDims + 195, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_11;
  memcpy(g_UI_YesNoDims + 199, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_12;
  memcpy(g_UI_YesNoDims + 203, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 208, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 224, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 240, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 244, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_13;
  memcpy(g_UI_YesNoDims + 248, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_14;
  memcpy(g_UI_YesNoDims + 252, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_15;
  memcpy(g_UI_YesNoDims + 256, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 261, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_UI_YesNoDims + 277, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_UI_YesNoDims + 293, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&WorldMap_ComputeBuildMenuActionFromCursor;
  memcpy(g_UI_YesNoDims + 297, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_16;
  memcpy(g_UI_YesNoDims + 301, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_17;
  memcpy(g_UI_YesNoDims + 305, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_18;
  memcpy(g_UI_YesNoDims + 309, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_UI_YesNoDims + 314, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 184, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 200, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 204, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 208, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 212, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 216, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 221, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 237, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 253, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 257, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 261, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 265, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 269, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 274, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 290, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 306, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 310, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 314, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 318, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 322, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 327, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 343, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 359, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_BuildInSelectedDirection;
  memcpy(g_RoadBuildData + 363, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 367, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 371, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 375, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 380, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 396, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 412, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExitAfterWidgetPress;
  memcpy(g_RoadBuildData + 416, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 420, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 424, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 428, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 433, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 449, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 465, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 469, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 473, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 477, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 481, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 486, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 502, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 518, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 522, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 526, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 530, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 534, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 539, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 555, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 571, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 575, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 579, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 583, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 587, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 592, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 608, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 624, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 628, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 632, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 636, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 640, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 645, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&g_ActionButtonSpriteSet;
  memcpy(g_RoadBuildData + 661, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&UI_DrawWidgetIcon;
  memcpy(g_RoadBuildData + 677, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)&RoadBuildMode_RequestExit;
  memcpy(g_RoadBuildData + 681, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 685, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 689, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)0;
  memcpy(g_RoadBuildData + 693, &pointer_value, sizeof(pointer_value));
  pointer_value = (_DWORD)(uintptr_t)widget_text_3;
  memcpy(g_RoadBuildData + 698, &pointer_value, sizeof(pointer_value));
  g_BuilderRoadWidgetsInitialized = 1;
}
