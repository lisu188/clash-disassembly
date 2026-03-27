# Unit Types and Stats Report

## 1. Overview
- **Analyzed areas:** `clash95.c` sections covering `Unit_Create`, squad-slot initialization (`sub_40F440`), attack/move handlers (`sub_428400`, `sub_4295D0`, `sub_437630`), unit metadata tables (`byte_51257E`..`byte_512586`, `dword_51257A`, `byte_512582`), and movement/pathing helpers (`Map_GetUnitTileMoveCostOrZero`, `sub_422BA0`).
- **Evidence forms:** direct field writes and reads, array lookups indexed by unit type, conditional logic that gates abilities, and formulas applying morale and experience multipliers.
- **Game resemblance:** mechanics (10-man stacks, morale/experience modifiers, Polish localization) match *Clash* (1998 strategy game). No other files in repo reference different gameplay modes.

## 2. Recovered Unit Types / Categories
| recovered_name | confidence | kind | evidence summary | where found | related |
| `UnitType0_Peasant` | high | concrete_type | Sprite loader uses `g_UnitSpriteFolders[22 * type]` and the base entry is the literal `"peon"`, which generates file paths like `units_go\peon?.s32`; CLIPS host functions `IloscChlopow` / `WyprowadzChlopow` operate on the same unit archetype, proving type id 0 represents the Chłopi/Peasant stack. | `clash95.c:8314-8340`, `clash95.c:25320-25480`, `clash95.c:68590-68610` | `UNIT_TYPE_PEASANT`, scripting APIs `IloscChlopow`, `WyprowadzChlopow` |
| `UnitType13_Hero` | high | concrete_type | Type id 13 is repeatedly excluded from standard melee/ranged handlers (`sub_437630`, `sub_428400`) and from general unit menus, implying a unique hero/queen piece that cannot be consumed like regular troops. | `clash95.c:21784-21806`, `49182-49270` | interacts with queen narrative systems.
| `RangedUnitCategory` | high | category | Units with non-zero `byte_512582` entries execute the projectile logic in `sub_437630`/`sub_4287E0` and therefore own ranged stats. | `clash95.c:39803-39820`, `49182-49270` | inherits range/damage stats.
| `ImmobileOrGarrisoned` | medium | category | `dword_51257A` flag bit0 marks units that should be ignored when scanning for mobile squads; formation validators (`sub_422BA0`) and UI highlight suppression rely on it. These units stay inside castles or act as static structures. | `clash95.c:42290-42310`, `27660-27690` | likely includes siege engines/buildings.
| `DefaultFieldUnit` | medium | category | Units with `byte_51257E > 0` and `dword_51257A bit0 == 0` participate in melee, consume stamina, and are eligible for movement UI and morale effects. | `clash95.c:22124-22145`, `39680-39760` | parent archetype for most troop IDs.
| `LightUnitCategory` | high | category | `dword_51257A` bit1 selects “light” units whose veterancy cap is reduced to 6 and whose UI checks use the light threshold in `sub_41E7B0`. | `clash95.c:22133-22144`, `clash95.c:32950-32970` | controls `veterancy` scaling.
| `PeonWorker` | medium | concrete_type | The localized UI name builder pulls the string literal "peon" from `(&off_51256C)[22 * type]`, proving type id 0 is the worker/peon unit. | `clash95.c:25370-25430` | baseline civilian/worker unit.

## 3. Recovered Stats
| recovered_name | confidence | semantic meaning | evidence summary | locations | stat_kind | used_by |
| --- | --- | --- | --- | --- | --- | --- |
| `action_points` (slot `+8`, base `byte_512580`) | high | Per-turn stamina / men count used as resource for attacks or movement. Initialized in `sub_40F440` from `byte_512580[88*type]`, checked before melee and reduced by 5 per swing in `sub_428400`. | `clash95.c:22124-22145`, `39680-39760` | base/current | All field units.
| `morale_percent` (slot `+9`) | high | Percentage multiplier applied to damage/defense calculations. Always set to 100 on spawn, later overwritten by combat resolution (`sub_426FC0`), and every stat helper multiplies by `morale / 100`. | `clash95.c:22131-22135`, `23438-23460` | current modifier | All field units.
| `veterancy` (slot `+11`) | high | Small bonus derived from experience/training; default 6 for light units, 10 for heavy (`dword_51257A bit1`). Added as `/5` or `/10` bonus in stat formulas. | `clash95.c:22135-22144`, `23404-23460` | current modifier | All field units.
| `base_melee_attack` (`byte_51257E`) | high | Core melee attack rating. Non-zero entries identify units able to initiate melee; formulas `sub_411120`/`UI_IconIndexFromStats` turn it into actual attack strength via morale/veterancy multipliers. | `clash95.c:23404-23418`, `39680-39760` | base_stat | DefaultFieldUnit.
| `base_secondary_attack` (`byte_51257F`) | medium | Secondary strike (used in ranged targeting and some cost calculations). `sub_4295D0` derives retaliation cost from it, and UI routines use it when `byte_512582` marks ranged capability. | `clash95.c:23419-23434`, `40440-40465` | base_stat | RangedUnitCategory.
| `base_damage_scalar` (`byte_512581`) | medium | Raw damage per volley; converted to actual damage via morale/veterancy in `sub_411280` and `sub_4112C0`. | `clash95.c:23438-23448` | base_stat | Field units when resolving inflicted HP loss.
| `structure_damage_scalar` (`byte_512584`) | medium | Alternate damage table, likely vs buildings, used in `sub_4112F0` where caller passes context flag `a2` (unit attacking fortifications). | `clash95.c:23456-23466` | base_stat | Siege or anti-building scenarios.
| `road_move_cost` (`byte_512585`) | high | Movement allowance when tile provides a built road (`v11[2] != 0xFFFF`); used directly by `Map_GetUnitTileMoveCostOrZero`. | `clash95.c:41380-41410` | base_stat | All movers.
| `terrain_move_cost` (`byte_512586` via `g_TerrainMoveTableOffsets`) | high | Terrain-dependent movement allowance; `Map_GetUnitTileMoveCostOrZero` combines the move table with `dword_52456C[tileType]` to enforce penalties. | `clash95.c:41380-41420`, `413B10-41405` | base_stat | All movers.
| `unit_flags` (`dword_51257A`) | high | Bitfield capturing immobile status (bit0) and the “light unit” template (bit1). Controls spawn of action points, UI highlight, and veterancy caps. | `clash95.c:22133-22144`, `42290-42310`, `32950-32970` | modifier | All unit types.
| `attack_range_max` (`byte_512582`) | high | Maximum squared attack range for ranged units. Projectile routines compare distance to this value before firing. | `clash95.c:39803-39820`, `42779-42865` | base_stat | RangedUnitCategory.
| `attack_range_min` (`byte_512583`) | medium | Minimum squared range (dead zone) for ranged units—catapults/ballistas cannot fire inside this distance. | `clash95.c:39803-39820` | base_stat | RangedUnitCategory.
| `sprite_height` (`byte_512577`) | medium | Per-type sprite extent used to place selection frames and morale bars; UI draw code subtracts this offset to keep icons aligned. | `clash95.c:415F20-41610`, `27624-27695` | base_stat | All units shown in the tactical UI.
| `move_pixel_speed` (`byte_512570`) | medium | Per-frame displacement in marching animations; each tick adds `byte_512570` scaled by direction vectors to `dword_523F70/74`, controlling how quickly sprites cross tiles. | `clash95.c:39240-39330`, `38680-38720` | base_stat | Mobile units.
| `move_tick_delay` (`byte_512571`) | medium | Delay between movement animation updates; movement loops wait for `Time_Now` to exceed this value before emitting the next step. | `clash95.c:38632-38705` | modifier | Mobile units.
| `death_animation_frames` (`byte_512578`) | medium | Maximum frame count for a unit’s death/explosion effect; copied into `dword_512364` and decremented until the effect completes. | `clash95.c:39260-39320` | base_stat | Units with custom death FX.
| `death_frame_interval` (`byte_512572`) | medium | Interval between successive death-effect frames; fed into `Time_Now` inside the same loop that advances `dword_523F7C`. | `clash95.c:39290-39320` | modifier | Units with animated death FX.

## 4. Type-to-Stat Relationships
| unit_type | stat | relationship | confidence | evidence |
| --- | --- | --- | --- | --- |
| UnitType13_Hero | action_points, base_melee_attack | Not consumable: hero units skip stamina deduction and cannot call melee/ranged handlers, so these stats remain unused, indicating a narrative/queen piece. | high | `clash95.c:49182-49270`, `39680-39760`.
| RangedUnitCategory | base_secondary_attack, base_damage_scalar, attack_range_max/min | Ranged units use `byte_51257F`/`byte_512581` for projectile strength and `byte_512582`/`byte_512583` for allowable range in `sub_4287E0`. | high | `clash95.c:39803-39820`, `40440-40465`.
| ImmobileOrGarrisoned | terrain_move_cost/road_move_cost disabled | Flagged units skip map highlighting and `sub_415EA0`, so they effectively ignore move stats and stay inside castles. | medium | `clash95.c:27660-27695`, `42290-42310`.
| DefaultFieldUnit | action_points + morale + veterancy + base_melee_attack | Ordinary squads spawn via `Unit_Create`, consume stamina per melee, and have attack damage derived from the trio of base stats and modifiers. | high | `clash95.c:22124-22145`, `39680-39760`, `23404-23448`.
| LightUnitCategory | veterancy | Light-type units cap `veterancy` at 6 via `sub_41E7B0`, unlike heavy/default units which can reach 10. | high | `clash95.c:22133-22144`, `32950-32970`.

## 5. Ambiguous Findings
- **Unit names:** The pointer table `off_512568` references up to 102 localized strings per type, but the strings themselves (`off_5123CC`) are not emitted in `clash95.c`, preventing direct recovery of human-readable unit names.
- **Exact semantics of `byte_51257F` and `byte_512584`:** Both feed into damage/attack cost formulas, yet the code does not label whether they correspond to ranged vs siege vs anti-building damage. More evidence (e.g., resource tables with column headers) is required.
