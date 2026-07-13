# Recovered source modules

`clash95.c` (at the repository root, not in this directory) is the only
translation unit. It `#include`s the recovered .inc.c fragments in this
directory in original source order.

These fragment files are not standalone sources. This first-stage split preserves shared globals, static helper visibility, declaration order, and the direct-include unit-test model.

Repeated `_partN` fragments occur where recovered function-marker addresses are not monotonic in the decompiler output; keeping those parts separate prevents source reordering.

| Fragment | Address range | Functions | Purpose |
|---|---:|---:|---|
| `src/core/010_bootstrap.inc.c` | `0x00401020..0x004011F0` | 3 | Application bootstrap, shutdown, and initial game lifecycle |
| `src/core/020_utilities.inc.c` | `0x004015A0..0x00401A00` | 13 | Recovered strings, memory, containers, paths, and shared utilities |
| `src/render/030_render.inc.c` | `0x00401A40..0x00407D20` | 128 | Core surfaces, sprites, palettes, fonts, and rendering |
| `src/game/040_world_map.inc.c` | `0x00408030..0x0040F4D0` | 91 | Strategic world map, minimap, camera, fog, roads, and map UI |
| `src/game/050_units.inc.c` | `0x0040F510..0x0041C8B0` | 167 | Strategic units, stacks, movement, fatigue, morale, and path execution |
| `src/game/060_buildings.inc.c` | `0x0041D030..0x0042C840` | 156 | Buildings, construction, economy, garrisons, and production |
| `src/game/070_battle.inc.c` | `0x0042CB50..0x00433820` | 50 | Tactical battle interaction, simulation, rendering, and outcomes |
| `src/game/080_building_ui.inc.c` | `0x004338C0..0x00441D20` | 167 | Castle, garrison, production, and building modal interfaces |
| `src/game/090_special_sites_savegame.inc.c` | `0x00441DC0..0x0044FE70` | 129 | Ports, temples, treasures, persistence, and related dialogs |
| `src/rules/100_strategic.inc.c` | `0x004506B0..0x004612E0` | 187 | Clash strategic rules integration, host functions, campaign, and AI |
| `src/runtime/110_platform_input.inc.c` | `0x00461520..0x004635A0` | 51 | Recovered input, window, message, and platform-facing behavior |
| `src/render/120_media.inc.c` | `0x004637B0..0x004814A0` | 724 | Recovered audio, music, AVI, and media support |
| `src/rules/130_clips_language.inc.c` | `0x00481550..0x00481550` | 1 | CLIPS lexer, parser, expressions, and procedural language support |
| `src/render/120_media_part2.inc.c` | `0x00472B00..0x00472B00` | 1 | Recovered audio, music, AVI, and media support, continued |
| `src/rules/130_clips_language_part2.inc.c` | `0x00481720..0x00491530` | 375 | CLIPS lexer, parser, expressions, and procedural language support, continued |
| `src/rules/140_clips_objects.inc.c` | `0x00491580..0x004943A0` | 75 | CLIPS modules, classes, methods, and object metadata |
| `src/rules/150_clips_ast.inc.c` | `0x004943E0..0x00495E80` | 42 | CLIPS AST construction, output, and compiler-front-end helpers |
| `src/rules/160_clips_events.inc.c` | `0x00496000..0x0049FF80` | 245 | CLIPS events, handlers, patterns, and runtime metadata |
| `src/rules/170_clips_symbols.inc.c` | `0x004A0080..0x004ACA00` | 254 | CLIPS symbols, lookup, evaluation, and shared rule-engine services |
| `src/rules/180_clips_compiler.inc.c` | `0x004ACB00..0x004C8290` | 540 | CLIPS compiler marking, dependency, and emission passes |
| `src/rules/190_clips_methods.inc.c` | `0x004C82D0..0x004CFFC0` | 169 | CLIPS method lookup, dispatch, and late object-runtime support |
| `src/runtime/200_recovered_runtime.inc.c` | `0x004D0560..0x004E7F70` | 352 | Recovered CRT, C++ support, streams, threading, and library runtime |

Future conversion to independent translation units requires explicit internal headers, `extern` ownership for globals, static-helper decisions, and a replacement for `tests/unit/test_all.c` directly including `clash95.c`.
