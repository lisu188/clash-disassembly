/* Recovered Win95 implementation.
 *
 * The source remains one translation unit to preserve recovered symbol
 * visibility, declaration order, static helpers, and direct test access.
 * Canonical implementation fragments live under src/recovered/ and must not
 * be compiled independently. Legacy paths remain as compatibility symlinks. */

#include "src/recovered/prelude/00000000_clash95_prelude.inc.c"
#include "src/recovered/core/005_constant_guard.inc.c"
#include "src/recovered/core/00401020_bootstrap.inc.c"
#include "src/recovered/core/004015A0_utilities.inc.c"
#include "src/recovered/render/00401A40_render.inc.c"
#include "src/recovered/world/00408030_world_map.inc.c"
#include "src/recovered/units/0040F510_units.inc.c"
#include "src/recovered/buildings/0041D030_buildings.inc.c"
#include "src/recovered/battle/0042CB50_battle.inc.c"
#include "src/recovered/buildings/004338C0_building_ui.inc.c"
#include "src/recovered/world_and_persistence/00441DC0_special_sites_savegame.inc.c"
#include "src/recovered/rules/strategic/004506B0_strategic.inc.c"
#include "src/recovered/runtime/00461520_platform_input.inc.c"
#include "src/recovered/media/004637B0_media.inc.c"
#include "src/recovered/rules/clips/00481550_language.inc.c"
#include "src/recovered/media/00472B00_media_part2.inc.c"
#include "src/recovered/rules/clips/00481720_language_part2.inc.c"
#include "src/recovered/rules/clips/00491580_objects.inc.c"
#include "src/recovered/rules/clips/004943E0_ast.inc.c"
#include "src/recovered/rules/clips/00496000_events.inc.c"
#include "src/recovered/rules/clips/004A0080_symbols.inc.c"
#include "src/recovered/rules/clips/004ACB00_compiler.inc.c"
#include "src/recovered/rules/clips/004C82D0_methods.inc.c"
#include "src/recovered/runtime/004D0560_legacy_runtime.inc.c"
