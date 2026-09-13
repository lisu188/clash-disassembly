// Actual-source template expanded by test_builder_menu.py; no original oracle.
#include "recovered_layout.h"
#include <bit>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

enum Call { @CALL_ENUM@ };
constexpr uint32_t stateWords = 22;
constexpr size_t arenaBytes = 150200;
static_assert(sizeof(UnitStackRecord) == 725 && sizeof(WorldMapActionWidgetRecord) == 53);
static_assert(std::endian::native == std::endian::little);
int gameData, g_SelectedUnitIndex, g_WorldMapBuilderMenuAction;
int g_ActionButtonSpriteSet, g_BuilderRoadWidgetsInitialized, g_WorldMapActionWidgetsInitialized;
int g_PrimaryRenderSurface;
_UNKNOWN *g_RenderDevice;
char g_LanguageIndex;
template<size_t bytes> struct GuardedTable {
  unsigned char before[16];
  alignas(4) unsigned char data[bytes];
  unsigned char after[16];
};
static GuardedTable<ROAD_BUILD_DATA_BYTES> roadStorage;
static GuardedTable<BUILDER_ACTION_WIDGET_TABLE_BYTES> builderStorage;
static GuardedTable<322> mainStorage;
#define g_RoadBuildData roadStorage.data
#define g_UI_YesNoDims builderStorage.data
#define g_WorldMapActionButtonWidgetTable mainStorage.data
alignas(16) static unsigned char arenas[2][arenaBytes];
struct RenderFixture { unsigned char before[216]; _DWORD state[286]; unsigned char after[40]; };
alignas(256) static RenderFixture renderFixture;
#define g_RenderState renderFixture.state
static char text0[] = "no-builder-0", text1[] = "no-builder-1", text2[] = "no-builder-2";
char *g_Text_NoBuilder[3] = {text0, text1, text2};
static char aWrong_5[] = "wrong-no-selection", aWrong_6[] = "wrong-no-builder";
static char aStruktur[] = "keep", aStruktur_0[] = "fortress", aStruktur_1[] = "castle";
static char g_Building_FootprintTemplate_Type0, g_Building_FootprintTemplate_Type1, g_Building_FootprintTemplate_Type2;
static unsigned char roadReference[706], builderReference[322], mainReference[322];
static unsigned char expectedRoad[706], expectedBuilder[322], expectedMain[322];
static unsigned char entryRoad[706], entryBuilder[322], entryMain[322];
static uint32_t caseIndex, eventIndex, diagnosticCount, builderDraws, mainDraws;
static int initialBuilderGuard, initialMainGuard;
struct Mutation { uint32_t field, value; };
struct Event { uint32_t call, result; std::vector<Mutation> changes; };
static std::vector<Event> script;
static std::vector<uint32_t> output;

[[noreturn]] static void fail(const char *message) {
  std::fprintf(stderr, "builder-menu case=%u event=%u: %s\n", caseIndex, eventIndex, message);
  std::exit(1);
}
static uint32_t word(const void *address) { uint32_t value; std::memcpy(&value, address, 4); return value; }
static void put(void *address, uint32_t value) { std::memcpy(address, &value, 4); }
static uint32_t hashBytes(const void *address, size_t bytes) {
  const auto *data = static_cast<const unsigned char *>(address);
  uint32_t value = 2166136261u;
  for (size_t index = 0; index < bytes; ++index) value = (value ^ data[index]) * 16777619u;
  return value;
}
static uint32_t arenaIdentity() {
  for (uint32_t id = 0; id < 4; ++id)
    if ((uint32_t)gameData == (uint32_t)(uintptr_t)arenas[id % 2] + (id >= 2 ? 0x80000000u : 0)) return id;
  fail("unknown arena pointer bits");
}
static uint32_t getState(uint32_t field) {
  if (field >= 6 && field < stateWords) {
    const uint32_t index = field - 6;
    int16_t value;
    std::memcpy(&value, arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, 2);
    return (uint32_t)(int32_t)value;
  }
  switch (field) {
    case 0: return arenaIdentity();
    case 1: return g_SelectedUnitIndex;
    case 2: return g_WorldMapBuilderMenuAction;
    case 3: return g_PrimaryRenderSurface;
    case 4: return (uint32_t)(uintptr_t)g_RenderDevice;
    case 5: return (uint8_t)g_LanguageIndex;
    default: fail("invalid state field");
  }
}
static void setState(uint32_t field, uint32_t value) {
  if (field >= 6 && field < stateWords) {
    const uint32_t index = field - 6;
    const uint16_t coordinate = (uint16_t)value;
    std::memcpy(arenas[index / 8] + UNIT_STACK_TABLE_OFFSET
                + (index % 8 / 2) * UNIT_STACK_STRIDE + (index % 2) * 2, &coordinate, 2);
    return;
  }
  switch (field) {
    case 0:
      if (value >= 4) fail("unbacked arena identity");
      gameData = (int32_t)((uint32_t)(uintptr_t)arenas[value % 2] + (value >= 2 ? 0x80000000u : 0)); return;
    case 1:
      if (value != UINT32_MAX && (value & 0x7fffffffu) > 3) fail("unbacked selected index");
      g_SelectedUnitIndex = (int32_t)value; return;
    case 2: g_WorldMapBuilderMenuAction = (int32_t)value; return;
    case 3: g_PrimaryRenderSurface = (int32_t)value; return;
    case 4: g_RenderDevice = (_UNKNOWN *)(uintptr_t)value; return;
    case 5:
      if (value > 2) fail("unsupported language domain");
      g_LanguageIndex = (char)value; return;
    default: fail("invalid mutation field");
  }
}
static void snapshot() { for (uint32_t field = 0; field < stateWords; ++field) output.push_back(getState(field)); }
static void checkNativeBoundaryTiming() {
  if (!builderDraws && (g_BuilderRoadWidgetsInitialized != initialBuilderGuard
      || std::memcmp(g_RoadBuildData, entryRoad, sizeof entryRoad)
      || std::memcmp(g_UI_YesNoDims, entryBuilder, sizeof entryBuilder)))
    fail("builder tables initialized before their accepted first-use boundary");
  if (!mainDraws && (g_WorldMapActionWidgetsInitialized != initialMainGuard
      || std::memcmp(g_WorldMapActionButtonWidgetTable, entryMain, sizeof entryMain)))
    fail("main tables initialized before cleanup");
}
static uint32_t boundary(uint32_t call, uint32_t a0=0, uint32_t a1=0, uint32_t a2=0,
                         uint32_t a3=0, uint32_t a4=0, uint32_t a5=0, uint32_t a6=0, uint32_t a7=0) {
  checkNativeBoundaryTiming();
  if (eventIndex >= script.size() || script[eventIndex].call != call) {
    std::fprintf(stderr, "actual call=%u expected=%u\n", call,
                 eventIndex < script.size() ? script[eventIndex].call : 0);
    fail("unexpected callback order");
  }
  output.insert(output.end(), {call, a0, a1, a2, a3, a4, a5, a6, a7});
  snapshot();
  const Event &event = script[eventIndex++];
  for (const Mutation &mutation : event.changes) setState(mutation.field, mutation.value);
  return event.result;
}
static uint32_t renderIdentity(int address) {
  if ((uint32_t)address != (uintptr_t)g_RenderState) fail("wrong actual render pointer");
  return 1;
}
static uint32_t tableIdentity(const void *address) {
  if (address == g_UI_YesNoDims) return 1;
  if (address == g_WorldMapActionButtonWidgetTable) return 2;
  fail("wrong actual widget backing");
}
static uint32_t stackBoundary(uint32_t call, uintptr_t address) {
  for (uint32_t arena = 0; arena < 2; ++arena)
    for (uint32_t slot = 0; slot < 4; ++slot)
      if (address == (uintptr_t)(arenas[arena] + UNIT_STACK_TABLE_OFFSET + slot * UNIT_STACK_STRIDE))
        return boundary(call, arena, slot);
  fail("predicate pointer is not a backed stack record");
}
static int WorldMap_HandleBuilderActionMenu(int, int, int, DWORD, double);
static int UIWidget_PlayPressedReleaseAnimationWithDelay(int widget, int delay) {
  return (int32_t)boundary(C_ANIMATION, widget, delay);
}
static int UnitStack_HasBuilder(int selected) { return (int32_t)boundary(C_HAS_BUILDER, selected); }
static void checkDrawEntry(uint32_t table);
static void UIWidgetTable_InitDrawStates(_DWORD *table) {
  const uint32_t identity = tableIdentity(table);
  checkDrawEntry(identity);
  boundary(C_INIT_DRAW, identity);
}
static int WorldMap_RedrawViewport(int argument) { return (int32_t)boundary(C_VIEWPORT, argument); }
static void Diagnostics_TraceWorldMapActionEvent(const char *stage, int selected, int action, int target, int detail) {
  if (++diagnosticCount != 1 || eventIndex != 4 || script[3].call != C_VIEWPORT
      || std::strcmp(stage, "builder_menu_enter") || selected != g_SelectedUnitIndex
      || action != -1 || g_WorldMapBuilderMenuAction != -1 || target || detail)
    fail("native diagnostic arguments or timing");
}
static unsigned int DD_Pump(int state, int carried, ...) {
  return boundary(C_PUMP, renderIdentity(state), carried, (uint8_t)carried, 0);
}
static int WorldMap_RedrawFrame(int carried, ...) { return (int32_t)boundary(C_FRAME, carried); }
static BOOL UI_TrySelectFriendlyStackUnderCursor() { return (int32_t)boundary(C_SELECT_STACK); }
static signed int UIWidgetTable_PollHoverAndActions(_DWORD *table, DWORD context) {
  if (tableIdentity(table) != 1) fail("poll used main table");
  return (int32_t)boundary(C_POLL, 1, context);
}
static BOOL DD_IsFlipping(int state) { return (int32_t)boundary(C_FLIPPING, renderIdentity(state)); }
static int Builder_StartRoadBuildMode(DWORD context, double value) {
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_ROAD, context, (uint32_t)bits, (uint32_t)(bits >> 32));
}
static signed int Treasure_TryDigHere(int selected, char action, DWORD context, char render, char *zero, double value) {
  if (render != (char)(uintptr_t)g_RenderState || zero) fail("Dig pointer-byte or null slot");
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_DIG, selected, (uint32_t)(int32_t)action, context,
                           (uint32_t)(int32_t)render, 0, (uint32_t)bits, (uint32_t)(bits >> 32));
}
static int BuildBuilding(int type, int ignored, char action, double value) {
  if (ignored != 0) fail("discarded Trap slot is not explicitly zero");
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_TRAP, type, (uint8_t)action, (uint32_t)bits, (uint32_t)(bits >> 32));
}
static signed int UnitStack_GetMinCurrentActionPoints(intptr_t address) { return (int32_t)stackBoundary(C_MIN_AP, (uintptr_t)address); }
static signed int UnitStack_HasPeasantCargo(int address) { return (int32_t)stackBoundary(C_CARGO, (uint32_t)address); }
static BOOL Building_New(int type, int selected, double value, char *footprint, int force) {
  const char *templates[] = {&g_Building_FootprintTemplate_Type0, &g_Building_FootprintTemplate_Type1, &g_Building_FootprintTemplate_Type2};
  uint32_t identity = 0;
  for (uint32_t index = 0; index < 3; ++index) if (footprint == templates[index]) identity = index + 1;
  if (!identity) fail("unknown construction footprint");
  const uint64_t bits = std::bit_cast<uint64_t>(value);
  return (int32_t)boundary(C_BUILDING_NEW, type, selected, (uint32_t)bits, (uint32_t)(bits >> 32), identity, force);
}
static void MiniMap_DrawTileCell(void *row, int column) { boundary(C_MINIMAP, (uint32_t)(uintptr_t)row, column); }
static int Audio_PlaySoundEffectByName(const char *name, int volume) {
  const char *sounds[] = {aStruktur, aStruktur_0, aStruktur_1};
  uint32_t identity = 0;
  for (uint32_t index = 0; index < 3; ++index) if (name == sounds[index]) identity = index + 1;
  if (!identity) fail("unknown construction sound");
  return (int32_t)boundary(C_SOUND, identity, volume);
}
static int Audio_PlayButtonSound(const char *name) {
  if (name != aWrong_5 && name != aWrong_6) fail("unknown wrong-action sound");
  return (int32_t)boundary(C_BUTTON_SOUND, name == aWrong_5 ? 1 : 2);
}
static int UI_ShowInfoWindow(const char *message, unsigned int style, int delay, DWORD context, int copyEnd, int globalEnd) {
  uint32_t identity = 0;
  for (uint32_t index = 0; index < 3; ++index) if (message == g_Text_NoBuilder[index]) identity = index + 1;
  if (!identity || (uint32_t)globalEnd != (uintptr_t)&g_Text_NoBuilder[3]) fail("info message/global end identity");
  // The recovered int ABI truncates the local pointer. Reconstruct only within
  // this actual stack's high32 window, then validate all three preceding DWORDs.
  const uintptr_t stack = (uintptr_t)&identity;
  const uintptr_t end = (stack & ~uintptr_t(UINT32_MAX)) | (uint32_t)copyEnd;
  if (end < stack - 1024 * 1024 || end > stack + 1024 * 1024) fail("info copied end is not nearby stack storage");
  for (uint32_t index = 0; index < 3; ++index)
    if (word((const void *)(end - 12 + index * 4)) != (uintptr_t)g_Text_NoBuilder[index]) fail("info three copied DWORDs");
  return (int32_t)boundary(C_INFO, identity, style, delay, context, 4, 5);
}
static BOOL Render_Begin(int state, void (*callback)(void), ...) {
  if (callback) fail("nonzero render callback");
  return (int32_t)boundary(C_BEGIN, renderIdentity(state), 0);
}
static int WorldMap_SyncSelectionForHumanPlayer(DWORD context) { return (int32_t)boundary(C_SYNC, context); }
static int WorldMap_RefreshUnitStatusPanel(DWORD context) { return (int32_t)boundary(C_STATUS, context); }
static int UnitStackSelection_RefreshForSelectedStack(DWORD context) { return (int32_t)boundary(C_REFRESH, context); }
@SPIES@
@INITIALIZERS@
@BODY@
@DATA@

static void check_pointer(const void *field, uintptr_t expected) {
  if (expected > INT_MAX || word(field) != expected) fail("initializer callback/sprite identity");
}
static void check_text(const void *field, const void *expected, size_t bytes) {
  const uintptr_t value = word(field);
  if (value < 0x10000 || value > INT_MAX || std::memcmp((const void *)value, expected, bytes)) fail("initializer text identity");
}
static void checkBuilderInitialization() {
  if (g_BuilderRoadWidgetsInitialized != 1) fail("builder initialization guard");
  for (size_t index = 0; index < sizeof original_road; ++index)
    if (!road_pointer_mask[index] && g_RoadBuildData[index] != original_road[index]) fail("Road nonpointer template byte");
  for (size_t index = 0; index < sizeof original_builder; ++index)
    if (!builder_pointer_mask[index] && g_UI_YesNoDims[index] != original_builder[index]) fail("Builder nonpointer template byte");
  @POINTER_CHECKS@
}
static void checkMainCallbacks() {
  const uintptr_t callbacks[] = {@MAIN_CALLBACKS@};
  for (size_t index = 0; index < 6; ++index)
    check_pointer(g_WorldMapActionButtonWidgetTable + index * 53 + 32, callbacks[index]);
  if (word(g_WorldMapActionButtonWidgetTable + 318) != UINT32_MAX) fail("main table sentinel");
}
static void captureInitializers() {
  std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
  std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
  g_BuilderRoadWidgetsInitialized = 0;
  WorldMap_EnsureBuilderWidgetTables();
  checkBuilderInitialization();
  std::memcpy(roadReference, g_RoadBuildData, sizeof roadReference);
  std::memcpy(builderReference, g_UI_YesNoDims, sizeof builderReference);
  std::memset(g_WorldMapActionButtonWidgetTable, 0, sizeof g_WorldMapActionButtonWidgetTable);
  g_WorldMapActionWidgetsInitialized = 0;
  WorldMap_EnsureActionButtonWidgetTable();
  checkMainCallbacks();
  std::memcpy(mainReference, g_WorldMapActionButtonWidgetTable, sizeof mainReference);
}
static void checkDrawEntry(uint32_t table) {
  if (table == 1) {
    if (++builderDraws != 1 || eventIndex != 2) fail("builder initializer/draw order");
    if (!initialBuilderGuard) checkBuilderInitialization();
    if (g_BuilderRoadWidgetsInitialized != (initialBuilderGuard ? initialBuilderGuard : 1)) fail("builder guard changed");
    if (std::memcmp(g_UI_YesNoDims, expectedBuilder, sizeof expectedBuilder)
        || std::memcmp(g_RoadBuildData, expectedRoad, sizeof expectedRoad)) fail("builder cold/warm table contract");
  } else {
    if (++mainDraws != 1 || !builderDraws) fail("main initializer/draw order");
    if (g_WorldMapActionWidgetsInitialized != (initialMainGuard ? initialMainGuard : 1)) fail("main guard changed");
    if (std::memcmp(g_WorldMapActionButtonWidgetTable, expectedMain, sizeof expectedMain)) fail("main cold/warm table contract");
    checkMainCallbacks();
  }
}
static uint32_t readInput() {
  uint32_t value;
  if (std::fread(&value, 4, 1, stdin) != 1) fail("incomplete fixture");
  return value;
}
template<size_t bytes> static void resetSentinels(GuardedTable<bytes> &table) {
  std::memset(table.before, 0xC3, sizeof table.before);
  std::memset(table.after, 0x3C, sizeof table.after);
}
template<size_t bytes> static void checkSentinels(const GuardedTable<bytes> &table) {
  for (unsigned char byte : table.before) if (byte != 0xC3) fail("widget prefix sentinel");
  for (unsigned char byte : table.after) if (byte != 0x3C) fail("widget suffix sentinel");
}
static void finish(uint32_t result) {
  if (eventIndex != script.size()) fail("missing callback event");
  const bool accepted = script.size() > 2 && script[2].call == C_INIT_DRAW;
  if (diagnosticCount != (unsigned)accepted || builderDraws != (unsigned)accepted || mainDraws != (unsigned)accepted)
    fail("native initialization/diagnostic count");
  if (!accepted) {
    if (g_BuilderRoadWidgetsInitialized != initialBuilderGuard || g_WorldMapActionWidgetsInitialized != initialMainGuard)
      fail("rejected menu changed initialization guards");
  }
  if (std::memcmp(g_UI_YesNoDims, expectedBuilder, sizeof expectedBuilder)
      || std::memcmp(g_RoadBuildData, expectedRoad, sizeof expectedRoad)
      || std::memcmp(g_WorldMapActionButtonWidgetTable, expectedMain, sizeof expectedMain)) fail("final widget backings differ");
  for (unsigned char byte : renderFixture.before) if (byte != 0xC3) fail("render prefix sentinel");
  for (unsigned char byte : renderFixture.after) if (byte != 0x3C) fail("render suffix sentinel");
  checkSentinels(roadStorage); checkSentinels(builderStorage); checkSentinels(mainStorage);
  output.push_back(result);
  snapshot();
  output.push_back(hashBytes(arenas[0], arenaBytes));
  output.push_back(hashBytes(arenas[1], arenaBytes));
  output.push_back(hashBytes(g_RenderState, sizeof g_RenderState));
}
int main() {
  if ((uintptr_t)arenas + sizeof arenas > INT_MAX || (uintptr_t)g_RenderState + sizeof g_RenderState > INT_MAX
      || ((uintptr_t)g_RenderState & 255) != 0xD8) fail("fixture backing must fit positive low32 and original render byte");
  captureInitializers();
  const uint32_t count = readInput();
  for (caseIndex = 0; caseIndex < count; ++caseIndex) {
    initialBuilderGuard = (int32_t)readInput(); initialMainGuard = (int32_t)readInput();
    const int widget = (int32_t)readInput(), delay = (int32_t)readInput(), frame = (int32_t)readInput();
    const DWORD context = readInput();
    const uint32_t low = readInput(), high = readInput(), eventCount = readInput();
    if (!eventCount || eventCount > 96) fail("invalid script size");
    std::memset(arenas, 0x5A, sizeof arenas);
    std::memset(g_RenderState, 0xA5, sizeof g_RenderState);
    std::memset(renderFixture.before, 0xC3, sizeof renderFixture.before);
    std::memset(renderFixture.after, 0x3C, sizeof renderFixture.after);
    resetSentinels(roadStorage); resetSentinels(builderStorage); resetSentinels(mainStorage);
    for (uint32_t field = 0; field < stateWords; ++field) setState(field, readInput());
    script.clear(); output.clear(); eventIndex = diagnosticCount = builderDraws = mainDraws = 0;
    for (uint32_t index = 0; index < eventCount; ++index) {
      Event event; event.call = readInput(); event.result = readInput();
      const uint32_t changes = readInput();
      if (changes > stateWords) fail("excess state mutations");
      for (uint32_t mutation = 0; mutation < changes; ++mutation) {
        const uint32_t field = readInput(), value = readInput();
        event.changes.push_back({field, value});
      }
      script.push_back(event);
    }
    const bool accepted = script.size() > 2 && script[2].call == C_INIT_DRAW;
    std::memcpy(g_RoadBuildData, roadReference, sizeof roadReference);
    std::memcpy(g_UI_YesNoDims, builderReference, sizeof builderReference);
    std::memcpy(g_WorldMapActionButtonWidgetTable, mainReference, sizeof mainReference);
    g_BuilderRoadWidgetsInitialized = initialBuilderGuard;
    g_WorldMapActionWidgetsInitialized = initialMainGuard;
    if (initialBuilderGuard) {
      put(g_RoadBuildData + 180, 0x99887766); put(g_UI_YesNoDims + 8, 0x12345678);
    } else {
      std::memset(g_RoadBuildData, 0xA5, sizeof g_RoadBuildData);
      std::memset(g_UI_YesNoDims, 0x5A, sizeof g_UI_YesNoDims);
    }
    if (initialMainGuard) {
      put(g_WorldMapActionButtonWidgetTable + 8, 0x78563412);
      put(g_WorldMapActionButtonWidgetTable + 167, 0xA1B2C3D4);
    } else {
      std::memset(g_WorldMapActionButtonWidgetTable, 0x6B, sizeof g_WorldMapActionButtonWidgetTable);
      put(g_WorldMapActionButtonWidgetTable + 8, 1); put(g_WorldMapActionButtonWidgetTable + 167, 1);
    }
    std::memcpy(expectedRoad, !initialBuilderGuard && accepted ? roadReference : g_RoadBuildData, sizeof expectedRoad);
    std::memcpy(expectedBuilder, !initialBuilderGuard && accepted ? builderReference : g_UI_YesNoDims, sizeof expectedBuilder);
    std::memcpy(expectedMain, !initialMainGuard && accepted ? mainReference : g_WorldMapActionButtonWidgetTable, sizeof expectedMain);
    std::memcpy(entryRoad, g_RoadBuildData, sizeof entryRoad);
    std::memcpy(entryBuilder, g_UI_YesNoDims, sizeof entryBuilder);
    std::memcpy(entryMain, g_WorldMapActionButtonWidgetTable, sizeof entryMain);
    const double value = std::bit_cast<double>((uint64_t)low | ((uint64_t)high << 32));
    finish((uint32_t)WorldMap_HandleBuilderActionMenu(widget, delay, frame, context, value));
    if (std::fwrite(output.data(), 4, output.size(), stdout) != output.size()) fail("trace write failed");
  }
  if (std::fgetc(stdin) != EOF) fail("trailing fixture input");
}
