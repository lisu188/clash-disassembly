# Source organization

`clash95.c` at the repository root remains the only recovered translation unit. It includes canonical recovered fragments from `src/recovered/` in the established translation-unit order.

The recovered fragments are not standalone sources. The one-TU model preserves shared globals, static helper visibility, declaration order, and the direct-include unit-test model.

## Canonical areas

- `src/recovered/` contains behavior attributable to the original executable.
- `src/platform/` contains the separately compiled SDL/X11 host implementation.
- `src/compatibility/` contains decompiler support and quarantined runtime scaffolding.
- `src/instrumentation/` contains mission tracing and other observation-only support.
- `src/bootstrap/` contains the host executable entrypoint.

Existing paths such as `src/game/040_world_map.inc.c` remain as Git symlinks. They preserve recovery-tool manifests and archived evidence while pointing to the single canonical source blob.

## Recovered fragments

| Canonical fragment | Address range | Functions | Purpose |
|---|---:|---:|---|
| `src/recovered/core/00401020_bootstrap.inc.c` | `0x00401020..0x004011F0` | 3 | Application bootstrap, shutdown, and initial game lifecycle |
| `src/recovered/core/004015A0_utilities.inc.c` | `0x004015A0..0x00401A00` | 13 | Strings, memory, containers, paths, and shared utilities |
| `src/recovered/render/00401A40_render.inc.c` | `0x00401A40..0x00407D20` | 128 | Core surfaces, sprites, palettes, fonts, and rendering |
| `src/recovered/world/00408030_world_map.inc.c` | `0x00408030..0x0040F4D0` | 91 | Strategic world map, minimap, camera, fog, roads, and map UI |
| `src/recovered/units/0040F510_units.inc.c` | `0x0040F510..0x0041C8B0` | 167 | Strategic units, stacks, movement, fatigue, morale, and path execution |
| `src/recovered/buildings/0041D030_buildings.inc.c` | `0x0041D030..0x0042C840` | 156 | Buildings, construction, economy, garrisons, and production |
| `src/recovered/battle/0042CB50_battle.inc.c` | `0x0042CB50..0x00433820` | 50 | Tactical battle interaction, simulation, rendering, and outcomes |
| `src/recovered/buildings/004338C0_building_ui.inc.c` | `0x004338C0..0x00441D20` | 167 | Castle, garrison, production, and building modal interfaces |
| `src/recovered/world_and_persistence/00441DC0_special_sites_savegame.inc.c` | `0x00441DC0..0x0044FE70` | 129 | Ports, temples, treasures, persistence, audio helpers, and related dialogs |
| `src/recovered/rules/strategic/004506B0_strategic.inc.c` | `0x004506B0..0x004612E0` | 187 | Strategic rules integration, host functions, campaign, and AI |
| `src/recovered/runtime/00461520_platform_input.inc.c` | `0x00461520..0x004635A0` | 51 | Original input, window, message, and platform-facing behavior |
| `src/recovered/media/004637B0_media.inc.c` | `0x004637B0..0x004814A0` | 724 | Audio, music, AVI, and media support |
| `src/recovered/rules/clips/00481550_language.inc.c` | `0x00481550` | 1 | First CLIPS language fragment |
| `src/recovered/media/00472B00_media_part2.inc.c` | `0x00472B00` | 1 | Non-monotonic media continuation retained in translation-unit order |
| `src/recovered/rules/clips/00481720_language_part2.inc.c` | `0x00481720..0x00491530` | 375 | CLIPS lexer, parser, expressions, and procedural language support |
| `src/recovered/rules/clips/00491580_objects.inc.c` | `0x00491580..0x004943A0` | 75 | CLIPS modules, classes, methods, and object metadata |
| `src/recovered/rules/clips/004943E0_ast.inc.c` | `0x004943E0..0x00495E80` | 42 | CLIPS AST construction, output, and compiler-front-end helpers |
| `src/recovered/rules/clips/00496000_events.inc.c` | `0x00496000..0x0049FF80` | 245 | CLIPS events, handlers, patterns, and runtime metadata |
| `src/recovered/rules/clips/004A0080_symbols.inc.c` | `0x004A0080..0x004ACA00` | 254 | CLIPS symbols, evaluation, lookup, and shared services |
| `src/recovered/rules/clips/004ACB00_compiler.inc.c` | `0x004ACB00..0x004C8290` | 540 | CLIPS compiler marking, dependency, and emission passes |
| `src/recovered/rules/clips/004C82D0_methods.inc.c` | `0x004C82D0..0x004CFFC0` | 169 | CLIPS method lookup, dispatch, and late object-runtime support |
| `src/recovered/runtime/004D0560_legacy_runtime.inc.c` | `0x004D0560..0x004E7F70` | 352 | Recovered CRT, C++ support, streams, threading, and library runtime |

Repeated or non-monotonic fragments remain separate where reordering would alter declaration or definition order.

Future conversion to independent translation units requires explicit internal headers, `extern` ownership for globals, static-helper decisions, and a replacement for `tests/unit/test_all.c` directly including `clash95.c`.

See `docs/SOURCE_LAYOUT.md` for change and validation rules.
