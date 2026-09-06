# F3: folded game-state field offsets

Track: Win95 reconstruction; behavior-preserving constant naming.

The 477 function/expression-scoped rules replace 604 literal sites using 45 exact-spelling macros. Names describe the existing recovered field, retaining the original absolute displacement rather than changing pointer arithmetic or introducing new layouts. The value is the recorded table base plus the existing field offset. Recovered metadata and original assembly memory operands provide the layout evidence; the application freezes each original expression and function.

Direct expressions must contain the matching game-state base. An additional 59 sites use 34 reviewed local aliases with preceding sole assignments; their proofs are retained in `artifacts/magic-numbers-20260906/field-alias-proofs.json`. In `Scenario_SeedCantbellyAndKopegonCastles`, `gameDataBase = gameData` supplies the base and `buildingRecordOffset` supplies only the scaled displacement.

Independent review corrected six tactical assembly references that initially matched stack offset declarations or sprite values instead of memory operands. The final constants/rules contain the corrected memory-operand references. No semantic meaning was inferred from a bare numeric match. Existing casts, access widths, arithmetic grouping and suffixes remain intact.

| Constant | Value / existing layout | Sites | Example original source site |
| --- | --- | ---: | --- |
| `BATTLE_UNIT_OWNER_PLAYER_INDEX_TABLE_OFFSET` | `854 = 852 + 2`; `BattleUnitEntry.owner_player_index` | 24 | `src/battle/0042CB50_0042E8B0_battle_001.cpp:77` (`UnitBattle_HandleBattlefieldInteraction`) |
| `BATTLE_UNIT_FACING_DIRECTION_TABLE_OFFSET` | `855 = 852 + 3`; `BattleUnitEntry.facing_direction` | 11 | `src/battle/0042E9E0_00430C20_battle_002.cpp:658` (`UnitBattle_DrawUnitSprite`) |
| `BATTLE_UNIT_GRID_X_TABLE_OFFSET` | `856 = 852 + 4`; `BattleUnitEntry.grid_x` | 38 | `src/battle/0042CB50_0042E8B0_battle_001.cpp:108` (`UnitBattle_HandleBattlefieldInteraction`) |
| `BATTLE_UNIT_GRID_Y_TABLE_OFFSET` | `858 = 852 + 6`; `BattleUnitEntry.grid_y` | 36 | `src/battle/0042CB50_0042E8B0_battle_001.cpp:111` (`UnitBattle_HandleBattlefieldInteraction`) |
| `BATTLE_UNIT_ACTION_POINTS_TABLE_OFFSET` | `860 = 852 + 8`; `BattleUnitEntry.action_points` | 19 | `src/battle/0042CB50_0042E8B0_battle_001.cpp:121` (`UnitBattle_HandleBattlefieldInteraction`) |
| `BATTLE_UNIT_HEALTH_PERCENT_TABLE_OFFSET` | `861 = 852 + 9`; `BattleUnitEntry.health_percent` | 4 | `src/buildings/00428880_0042A890_buildings_008.cpp:666` (`UnitBattle_CalcShotTargetHealthAfterHit`) |
| `BATTLE_UNIT_STANCE_BITS_TABLE_OFFSET` | `864 = 852 + 12`; `BattleUnitEntry.stance_bits` | 31 | `src/battle/0042CB50_0042E8B0_battle_001.cpp:147` (`UnitBattle_HandleBattlefieldInteraction`) |
| `BATTLE_UNIT_ANIM_FRAME_AND_EFFECT_BITS_TABLE_OFFSET` | `869 = 852 + 17`; `BattleUnitEntry.anim_frame_and_effect_bits` | 1 | `src/battle/0042E9E0_00430C20_battle_002.cpp:657` (`UnitBattle_DrawUnitSprite`) |
| `BATTLE_UNIT_BATTLE_STATE_BITS_TABLE_OFFSET` | `874 = 852 + 22`; `BattleUnitEntry.battle_state_bits` | 4 | `src/battle/0042CB50_0042E8B0_battle_001.cpp:551` (`UnitBattle_HandlePrepareDefenceAction`) |
| `PLAYER_DISPLAY_NAME_TABLE_OFFSET` | `140028 = 140024 + 4`; `PlayerRuntimeState.display_name` | 3 | `src/persistence/0044AE90_0044E850_persistence_005.cpp:267` (`Scenario_SetupSirArthurRosterVariantA`) |
| `PLAYER_CAMERA_LEFT_TABLE_OFFSET` | `140039 = 140024 + 15`; `PlayerRuntimeState.camera_left` | 1 | `src/world/0040B0A0_0040D560_world_003.cpp:295` (`PlayGame`) |
| `PLAYER_CAMERA_TOP_TABLE_OFFSET` | `140043 = 140024 + 19`; `PlayerRuntimeState.camera_top` | 1 | `src/world/0040B0A0_0040D560_world_003.cpp:296` (`PlayGame`) |
| `PLAYER_CONTROLLER_MODE_TABLE_OFFSET` | `140051 = 140024 + 27`; `PlayerRuntimeState.controller_mode` | 45 | `src/battle/0042E9E0_00430C20_battle_002.cpp:500` (`Battle_RunTacticalCombat`) |
| `PLAYER_RELIGION_FLAG_TABLE_OFFSET` | `140063 = 140024 + 39`; `PlayerRuntimeState.religion_flag` | 10 | `src/buildings/0043CD00_0043E4B0_buildings_005.cpp:956` (`Building_ShowGateDoorDialog_v1`) |
| `PLAYER_TECH_LEVEL_TABLE_OFFSET` | `140071 = 140024 + 47`; `PlayerRuntimeState.tech_level` | 1 | `src/buildings/0041F1A0_00421010_buildings_002.cpp:301` (`Unit_CaptureBuilding`) |
| `PLAYER_BATTLE_ACTION_TAKEN_FLAG_TABLE_OFFSET` | `140073 = 140024 + 49`; `PlayerRuntimeState.battle_action_taken_flag` | 6 | `src/battle/0042E9E0_00430C20_battle_002.cpp:192` (`Battle_RunTacticalCombat`) |
| `PLAYER_CONSECUTIVE_IDLE_BATTLE_TURNS_TABLE_OFFSET` | `140077 = 140024 + 53`; `PlayerRuntimeState.consecutive_idle_battle_turns` | 1 | `src/battle/0042E9E0_00430C20_battle_002.cpp:190` (`Battle_RunTacticalCombat`) |
| `PLAYER_QUEEN_RELATIONSHIP_STATE_TABLE_OFFSET` | `141443 = 140024 + 1419`; `PlayerRuntimeState.queen_relationship_state` | 2 | `src/strategic/004506B0_004530D0_strategic_001.cpp:281` (`Queen_NewTurn`) |
| `UNIT_STACK_TILE_COLUMN_TABLE_OFFSET` | `147176 = 147174 + 2`; `UnitStackRecord.tile_column` | 77 | `src/buildings/0041D030_0041F0C0_buildings_001.cpp:86` (`Building_New`) |
| `UNIT_STACK_OWNER_PLAYER_INDEX_TABLE_OFFSET` | `147178 = 147174 + 4`; `UnitStackRecord.owner_player_index` | 37 | `src/buildings/0041D030_0041F0C0_buildings_001.cpp:77` (`Building_New`) |
| `UNIT_STACK_FACING_DIRECTION_TABLE_OFFSET` | `147179 = 147174 + 5`; `UnitStackRecord.facing_direction` | 2 | `src/units/00414390_00416750_units_004.cpp:1193` (`WorldMap_DrawUnitStackWithOverlays`) |
| `UNIT_STACK_UNIT_SLOTS_TABLE_OFFSET` | `147180 = 147174 + 6`; `UnitStackRecord.unit_slots` | 44 | `src/buildings/0042A910_0042C4E0_buildings_009.cpp:828` (`Trap_New`) |
| `UNIT_STACK_SLOT_CURRENT_HEALTH_PERCENT_TABLE_OFFSET` | `147189 = 147180 + 9`; `UnitSlotRecord.current_health_percent` | 2 | `src/buildings/0043E500_0043FDE0_buildings_006.cpp:846` (`AI_TickNationPostTurn`) |
| `UNIT_STACK_SLOT_STANCE_BITS_TABLE_OFFSET` | `147192 = 147180 + 12`; `UnitSlotRecord.stance_bits` | 2 | `src/strategic/004506B0_004530D0_strategic_001.cpp:839` (`Cheat_ClearSelectedSquadDamageFlags`) |
| `UNIT_STACK_SLOT_AUX_RUNTIME_STATE_TABLE_OFFSET` | `147198 = 147180 + 18`; `UnitSlotRecord.aux_runtime_state` | 1 | `src/persistence/00443BB0_00445CE0_persistence_002.cpp:454` (`SaveSlot_LoadGame`) |
| `UNIT_STACK_QUEUED_PATH_TABLE_OFFSET` | `147490 = 147174 + 316`; `UnitStackRecord.queued_path` | 50 | `src/strategic/00453110_00455720_strategic_002.cpp:30` (`Rules_QueuePathToTile`) |
| `UNIT_STACK_IS_HIDDEN_ON_WORLD_MAP_TABLE_OFFSET` | `147894 = 147174 + 720`; `UnitStackRecord.is_hidden_on_world_map` | 5 | `src/render/00405DB0_00407D20_render_004.cpp:1447` (`WorldMap_HandleScrollKeysAndIdle`) |
| `BUILDING_TILE_COLUMN_TABLE_OFFSET` | `509675 = 509674 + 1`; `BuildingRecord.tile_column` | 15 | `src/buildings/0041F1A0_00421010_buildings_002.cpp:338` (`Unit_CaptureBuilding`) |
| `BUILDING_OWNER_PLAYER_INDEX_TABLE_OFFSET` | `509676 = 509674 + 2`; `BuildingRecord.owner_player_index` | 47 | `src/buildings/0041D030_0041F0C0_buildings_001.cpp:1127` (`Building_NewTurn`) |
| `BUILDING_FOOTPRINT_CLASS_TABLE_OFFSET` | `509678 = 509674 + 4`; `BuildingRecord.footprint_class` | 19 | `src/buildings/0041D030_0041F0C0_buildings_001.cpp:120` (`Building_New`) |
| `BUILDING_CONSTRUCTION_TURNS_REMAINING_TABLE_OFFSET` | `509690 = 509674 + 16`; `BuildingRecord.construction_turns_remaining` | 16 | `src/buildings/0041D030_0041F0C0_buildings_001.cpp:1131` (`Building_NewTurn`) |
| `BUILDING_GARRISON_SLOTS_TABLE_OFFSET` | `509692 = 509674 + 18`; `BuildingRecord.garrison_slots` | 8 | `src/buildings/0041D030_0041F0C0_buildings_001.cpp:1138` (`Building_NewTurn`) |
| `BUILDING_GARRISON_SERVICE_STATE_TABLE_OFFSET` | `510064 = 509674 + 390`; `BuildingRecord.garrison_service_state` | 2 | `src/strategic/00455740_004582B0_strategic_003.cpp:176` (`Building_HasTrainableIdleGarrisonUnit`) |
| `BUILDING_UNIT_LICENCE_TYPE_IDS_TABLE_OFFSET` | `510076 = 509674 + 402`; `BuildingRecord.unit_licence_type_ids` | 3 | `src/strategic/00455740_004582B0_strategic_003.cpp:83` (`Building_FindUnitLicenceSlotIndexOrZero`) |
| `BUILDING_ACTIVE_PRODUCTION_LICENCE_SLOT_INDEX_TABLE_OFFSET` | `510088 = 509674 + 414`; `BuildingRecord.active_production_licence_slot_index` | 1 | `src/strategic/00453110_00455720_strategic_002.cpp:1404` (`Building_HasProductionByIndex`) |
| `BUILDING_CASTLE_ADDON_FLAGS_TABLE_OFFSET` | `510090 = 509674 + 416`; `BuildingRecord.castle_addon_flags` | 5 | `src/persistence/0044AE90_0044E850_persistence_005.cpp:448` (`Scenario_SeedCantbellyAndKopegonCastles`) |
| `BUILDING_WALL_STRENGTH_TABLE_OFFSET` | `510095 = 509674 + 421`; `BuildingRecord.wall_strength` | 1 | `src/strategic/00453110_00455720_strategic_002.cpp:1325` (`Building_GetWallStrengthByIndex`) |
| `BUILDING_PEASANT_COUNT_TABLE_OFFSET` | `510104 = 509674 + 430`; `BuildingRecord.peasant_count` | 1 | `src/strategic/00453110_00455720_strategic_002.cpp:1395` (`Building_GetPeasantCountByIndex`) |
| `BUILDING_SATISFACTION_TABLE_OFFSET` | `510108 = 509674 + 434`; `BuildingRecord.satisfaction` | 1 | `src/strategic/00453110_00455720_strategic_002.cpp:1386` (`Building_GetSatisfactionByIndex`) |
| `BUILDING_PLAGUE_STATE_TABLE_OFFSET` | `510109 = 509674 + 435`; `BuildingRecord.plague_state` | 5 | `src/persistence/00443BB0_00445CE0_persistence_002.cpp:1137` (`WorldMap_NotifyPlagueOutbreak`) |
| `BUILDING_TAX_RATE_TABLE_OFFSET` | `510110 = 509674 + 436`; `BuildingRecord.tax_rate` | 5 | `src/strategic/00453110_00455720_strategic_002.cpp:1300` (`Building_GetTaxRateByIndex`) |
| `BUILDING_STORED_MONEY_TABLE_OFFSET` | `510112 = 509674 + 438`; `BuildingRecord.stored_money` | 7 | `src/buildings/0043E500_0043FDE0_buildings_006.cpp:876` (`Player_CalcAvailableStrongholdFunds`) |
| `BUILDING_TECH_LEVEL_BITS_TABLE_OFFSET` | `510118 = 509674 + 444`; `BuildingRecord.tech_level_bits` | 8 | `src/buildings/0041F1A0_00421010_buildings_002.cpp:300` (`Unit_CaptureBuilding`) |
| `BUILDING_PRISONER_SLOTS_TABLE_OFFSET` | `510119 = 509674 + 445`; `BuildingRecord.prisoner_slots` | 1 | `src/persistence/0044AE90_0044E850_persistence_005.cpp:454` (`Scenario_SeedCantbellyAndKopegonCastles`) |
| `BUILDING_CASTLE_FACT_ID_TABLE_OFFSET` | `510137 = 509674 + 463`; `BuildingRecord.castle_fact_id` | 1 | `src/strategic/00455740_004582B0_strategic_003.cpp:593` (`Building_OnGarrisonChange`) |

## Remaining evidence queue

The pre-application `field-deferrals.json` retains candidates rejected for missing direct base evidence, unsafe expression shape or differing spelling, including sites subsequently resolved by the separately reviewed local aliases. It is historical input, not the final queue. The final complete census and F5 dispositions describe remaining occurrences. No casted word/DWORD index is renamed as a byte offset; unrelated arithmetic and opaque record fields remain unchanged.

Confidence is high for the bounded literal/layout correspondence. This batch neither recovers new field behavior nor establishes whole-game state or visual equivalence. The aggregate validation and exact commands are recorded in `docs/MAGIC_NUMBER_RECOVERY.md`.
