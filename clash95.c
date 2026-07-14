/* Recovered Win95 implementation.
 *
 * The source remains one translation unit to preserve recovered symbol
 * visibility, declaration order, static helpers, and direct test access.
 * Logical implementation fragments live under src/ and must not be
 * compiled independently. */

#include "src/clash95_prelude.inc.c"
#include "src/core/005_constant_guard.inc.c"
#include "src/core/010_bootstrap.inc.c"
#include "src/core/020_utilities.inc.c"
#include "src/render/030_render.inc.c"
#include "src/game/040_world_map.inc.c"
#include "src/game/050_units.inc.c"
#include "src/game/060_buildings.inc.c"
#include "src/game/070_battle.inc.c"
#include "src/game/080_building_ui.inc.c"
#include "src/game/090_special_sites_savegame.inc.c"
#include "src/rules/100_strategic.inc.c"
#include "src/runtime/110_platform_input.inc.c"
#include "src/render/120_media.inc.c"
#include "src/rules/130_clips_language.inc.c"
#include "src/render/120_media_part2.inc.c"
#include "src/rules/130_clips_language_part2.inc.c"
#include "src/rules/140_clips_objects.inc.c"
#include "src/rules/150_clips_ast.inc.c"
#include "src/rules/160_clips_events.inc.c"
#include "src/rules/170_clips_symbols.inc.c"
#include "src/rules/180_clips_compiler.inc.c"
#include "src/rules/190_clips_methods.inc.c"
#include "src/runtime/200_recovered_runtime.inc.c"
