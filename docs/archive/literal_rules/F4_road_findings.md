# F4 Road construction AP and marker animation constants

Track: Win95 reconstruction. Frontier: evidence-backed naming of the established Road AP checks and marker animation. This bounded supplement adds four exact-token macro proposals and six file/function/expression-scoped rules in two canonical translation units. Confidence is high for these roles. Production source, headers, public APIs, layout and expressions remain owned by the coordinating agent.

| Proposed macro | Exact lexeme | Source consumers before application | Independent evidence |
| --- | --- | --- | --- |
| `ROAD_BUILD_CONSTRUCTION_ACTION_POINTS` | `1` | `buildings_005.cpp:1180,1225` Road_Build; `:1433` RoadBuildMode_HighlightBuildableAdjacentTile | Original `loc_424B38` increments movement cost before minimum-AP comparison; `loc_424E62` passes one to `sub_410130` after queued movement. `UnitStack_SpendActionPointsClamped` at `src/units/0040F510_00411560_units_001.cpp:550` subtracts the passed spend amount from occupied-slot AP bytes. Highlight `loc_425445` independently increments move cost before its minimum-AP comparison. |
| `ROAD_BUILD_BRIDGE_HIGHLIGHT_MIN_ACTION_POINTS` | `6` | `buildings_005.cpp:1430` RoadBuildMode_HighlightBuildableAdjacentTile | Original `loc_4251B2` calls the two bridge-overlay predicates; `loc_425201` compares minimum current AP against six and branches to `loc_425425`, which enables the target and refreshes the direction widget. This names the bridge-specific highlight threshold; it does not assert a total Road construction cost. |
| `ROAD_BUILD_MARKER_ANIMATION_FRAME_MASK` | `7` | `buildings_006.cpp:54` Builder_StartRoadBuildMode | Original `loc_4255D3` increments `dword_527C38`, masks it with seven and stores the frame index; `sub_425120` uses that index for four marker-position reads from `dword_514294`. The original table and immutable binary fixture agree on the eight-frame bounce sequence. |
| `ROAD_BUILD_MARKER_ANIMATION_INTERVAL_TICKS` | `10` | `buildings_006.cpp:51` Builder_StartRoadBuildMode | Original `loc_4255D3` calls Time_Now, subtracts `0Ah`, and uses unsigned compare/jbe against `dword_527C28`; the eligible branch updates that timestamp, advances the frame and redraws all four adjacent tiles. The highlight callback consumes the frame as a bounce-table index. The existing strict comparison, unsigned behavior and subtraction are preserved. |

Canonical paths are `src/buildings/00422B50_004254E0_buildings_005.cpp` and `src/buildings/00425540_00426FC0_buildings_006.cpp`. Assembly anchors: `clash95.asm:56707` (`loc_424B38`), `:57042` (`loc_424E62`), `:57333` (`sub_425120`), `:57583` (`loc_425445`), `:57736` (`loc_4255D3`), and `:416021` (`dword_514294`). The original minimum-AP helper is `sub_410010`, the AP-spend helper is `sub_410130`, and queued movement is `sub_410330`.

The marker offsets at `tests/tools/fixtures/builder_road/original-road.bin + 0x88` decode as nine signed DWORDs: `(-8, -4, 0, 4, 8, 4, 0, -4, 0)`. The live animation selects the first eight by its mask; the ninth remains part of the backing data and is explicitly exercised by `tests/tools/test_builder_road.py:221`. The macro therefore describes the frame mask rather than asserting table capacity. `WorldMap_EnsureBuilderWidgetTables` in `src/world/0040A0E0_0040B020_world_002.cpp:293` preserves the original table bytes; `g_RoadBuildModeMarkerBounceOffsets` in `src/recovered_types.h` anchors the alias at `ROAD_BUILD_BOUNCE_OFFSETS_OFFSET`.

## Deferred and deliberately excluded

- Surface class `185` (`0xB9` in assembly) requires a recovered surface-enum family; this pass does not invent a surface name.
- Road overlay IDs and sprite lookup payloads require family-level table semantics and remain unchanged.
- The `1` passed as queued-movement animation control in Road_Build is not AP spend; boolean flags, per-frame increment, adjacency offsets and generic return values are outside these rules.
- Marker pixel offsets and castle-foundation query mode `2` remain unnamed pending the corresponding UI/query family evidence.
- The timing macro uses ticks without claiming a wall-clock unit or a precise rendered frame period; the original `Time_Now - 10 > lastTick` condition is unchanged.
- This batch establishes naming evidence only. It does not remove mission05 continuation blockers, promote a campaign route, or make new visual-fidelity claims.

## Validation

Read the scoped source lines and original assembly anchors above; decode the immutable fixture with Python `struct.unpack_from("<9i", fixture.read_bytes(), 0x88)`. Authoring used JSON serialization for both proposal and rule artifacts, and each rule matched one numeric token in one complete original source line. No source mutation or generator ran.

A WSL Python dry run imported `tools/literal_common.py` and `tools/apply_literal_names.py`, overlaid only these four proposed manifest entries and one-token macro bodies in memory, then called `validate_rules` and `resolve` with batch `F4-independent`. Result: six rules, six sites, zero validation errors, zero rejected sites, zero numeric-token respellings. The worktree's Windows `.git` reference is not directly interpretable by WSL, so the resolver's unrelated commit lookup printed a Git diagnostic and returned `unknown`; rule matching and validation completed successfully. Central integration must rerun the normal reviewed-plan and token/object gates with the project's WSL Git configuration.

Commands ran from the repository root through `wsl --cd /mnt/c/Users/andrz/.codex/worktrees/62e9/clash-disassembly python3 -`. The exact independent resolver invocation was:

```python
import json, pathlib, sys
sys.path.insert(0, "tools")
import literal_common as lc
import apply_literal_names as a
rules = json.loads(pathlib.Path("docs/archive/literal_rules/F4_road.json").read_text())
proposals = json.loads(pathlib.Path("docs/archive/literal_rules/F4_constants.json").read_text())
entries, families = lc.load_manifest()
by_name = {entry["name"]: entry for entry in entries}
prelude, enums = lc.parse_prelude_macros(), lc.parse_prelude_enums()
for entry in proposals:
    by_name[entry["name"]] = entry
    prelude[entry["name"]] = {"params": None, "body": entry["spelling"]}
    families.setdefault(entry["family"], set()).add(entry["name"])
assert not a.validate_rules(rules, by_name, prelude, enums)
plan = a.resolve(rules, by_name, families, "F4-independent", enums)
assert len(plan["entries"]) == 6
assert not plan["rejected"]
assert not any(site.get("respell") for site in plan["entries"])
```
