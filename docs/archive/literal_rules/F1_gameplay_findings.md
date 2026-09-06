# F1 gameplay literal review

Track: Win95 reconstruction. Frontier: behavior-preserving literal naming across the seven assigned gameplay subsystems. Road construction and normal turn refresh are the first reached family. No campaign endpoint is promoted.

The manifest-backed review covers all **48** assigned translation units. Rules freeze the canonical source file, enclosing function, complete original source line/expression, and individual numeric lexeme. Only tokens are replaced; expressions, pointer casts, operators, layouts and state are preserved.

F1_constants.json contains proposals for central integration. Resolve F1_gameplay.json together with other batch rules against one source freeze: a full-line match can contain another rule target. Existing deferred:true entries are used only by exact-site regex rules, never value-only matching. Macro replacements preserve exact lexemes; Direction8 enum-member replacements require the object-code gate.

## Evidence-backed families

- Shared slots and tactical entries: pinned 31-byte UnitSlotRecord/BattleUnitEntry layouts, readers/writers and copies. Garrison and detached formation slots use UNIT_SLOT_RECORD_BYTES; g_MapData tactical traversal uses BATTLE_UNIT_ENTRY_STRIDE.
- Shared metadata: typed unit-ID multiplication selects 88-byte metadata records. g_UnitTypeFlags is explicitly a const _DWORD alias, making its 22-element stride the same88-byte displacement.
- Capacities and byte extents: 500*725 stacks, 100*467 buildings, 22*31 tactical entries, 12*31 garrison slots and10*31 stack slots. Element limits and byte limits have separate names.
- Road and battle facing: Direction8 and Facing_DirectionFromDelta8 at0040FA80; original sub_4254E0 at004254E0 independently maps widget IDs27..30 to0/2/4/6. Road highlight's widget-order index0..3 is separate.
- Paths: QueuedPathBuffer is a count plus100 four-byte waypoints. Only actual world-stack path allocations receive decimal UNIT_STACK_PATH_ALLOCATION_BYTES404; tactical paths, sprites and temporary special-entry arrays remain separate.
- Widgets: 53-byte parser stepping, memset size and declared widget tables. Multiplayer53-pixel row/icon spacing remains independent.
- Table bases, path offsets and terrain rows: local aliases are checked against named bases and recovered layout evidence. DWORD79/WORD158 expressions representing byte316 retain their pointer-index units.

Original instruction anchors include clash95.asm Unit_NewTurn at004118E0, Road_Build at00424400 and sub_4254E0 at004254E0. RECOVERED_STRUCTURES.json and src/recovered_structs.h provide independent layout/copy evidence recorded in each rule. No external terminology or retail assets are needed.

## Proposed constants

| Name | Exact lexeme | Independent evidence |
| --- | --- | --- |

| UNIT_SLOT_RECORD_BYTES | 31 | src/recovered_structs.h:135-160 sizeof(UnitSlotRecord)==31; RECOVERED_STRUCTURES.json:1135 BuildingRecord.garrison_slots[12] uses 31-byte UnitSlot records copied by Building_UnitsLeave. |
| UNIT_STACK_PATH_ALLOCATION_BYTES | 404 | src/recovered_structs.h:171-178 QueuedPathBuffer is 404 bytes; Unit_MoveTrack 00414390 allocates 404 and stores count plus up to 100 four-byte waypoints, later copied as UNIT_STACK_PATH_BYTES. |
| BATTLE_UNIT_ENTRIES_BYTES | 682 | RECOVERED_STRUCTURES.json:1476 battle_unit_entries[22] starts at 852 and occupancy begins 1534 (difference682); Battle_PlaceUnit 004327B0 and HandleBattleResults traverse offsets 0..682 by31. |
| BUILDING_TABLE_BYTES | 46700 | RECOVERED_STRUCTURES.json:4518 BuildingRecord[100] and BuildingRecord size467; Building_New scans records by467 until46700 and the table at509674 ends556374. |
| UNIT_STACK_TABLE_BYTES | 362500 | RECOVERED_STRUCTURES.json:4510 UnitStackRecord[500] and src/recovered_structs.h sizeof725; gameData stack region147174 ends509674 and AI_TickNationPostTurn traverses362500 bytes by725. |
| BUILDING_GARRISON_SLOTS_BYTES | 372 | RECOVERED_STRUCTURES.json:1135 garrison_slots[12] begins18, next service state begins390 (difference372); Building_New, Building_NewTurn and Building_CalcGarrisonFactStrength traverse12 slots by31. |
| UNIT_STACK_SLOTS_BYTES | 310 | src/recovered_structs.h:185 embeds10 UnitSlotRecord entries size31; slots start6 and queued_path begins316 (difference310), with AI_TickNationPostTurn traversing j<310 by31. |
| BATTLE_UNIT_ENTRY_COUNT | 22 | RECOVERED_STRUCTURES.json:1476 battle_unit_entries[22]; Battle_RestoreSavedActionPointsBeforeResultCopy advances31 bytes and restores22 saved AP entries, matching Battle_PlaceUnit byte bound682. |
| BUILDING_GARRISON_SLOT_COUNT | 12 | RECOVERED_STRUCTURES.json:1135 garrison_slots[12] stores31-byte entries; Building_Destroy/Building_CountFreeGarrisonSlots bound slot-index traversal at12 with base+18. |
| UNIT_TYPE_METADATA_DWORD_STRIDE | 22 | src/recovered_structs.h UnitTypeMetadataRecord is88 bytes; g_UnitTypeFlags is int/DWORD-addressed at type_flags offset18, and 22*unit_type selects the same 88-byte table entry. Only g_UnitTypeFlags indexing is matched. |

Authored: 1110 rules, 1132 independently matched/function-filtered numeric token sites, 10 new numeric constant proposals.

## Rejected collisions and residual decisions

- src/strategic/004506B0_004530D0_strategic_001.cpp:840 and:874: numeric31 is added to compensating absolute bases147161/147158 in cheat writes. A forward slot-step role is unproven at those expressions; preserve pending effective-address/data-flow proof.
- src/battle/0042E9E0_00430C20_battle_002.cpp:943: wallSpriteChar +=404 selects a themed wall-sprite range (siblings412 and420). Reject path-size naming.
- src/persistence/0044AE90_0044E850_persistence_005.cpp: source-file layer/scratch200-byte row steps differ in role from occupancy rows. Only tileInitRowOffset +=200 is named TILE_ROW_STRIDE. Source-format rows need their own proven family.
- Numeric31 in sign extension, pixel extents, frames, IDs and mission coordinates is unchanged. Numeric88 in fatigue-bar geometry, coordinates and controller-backup traversal is not metadata stride.
- Road overlays866..952, bridge terrain ranges, surface/palette185, widget IDs, cost thresholds, animation timings and pixel geometry need distinct semantic families and independent instruction/data anchors. Do not infer terrain names from palette bytes.
- Zero/one control values, arithmetic increments, bit shifts and all-ones sentinels remain when syntax already explains them or width/domain evidence is incomplete. Do not replace signed -1 sites with a universal unsigned sentinel.
- Packed resource bytes, strings/comments/preprocessor definitions and widget relocation offsets are outside occurrence replacement. Preserve original evidence and overlap.
- Folded gameData/g_MapData field addresses are owned by the coordinating F3 pass; its independent effective-address proof is required.
- Core Mem_ZeroFieldOffset316 is not proven to be a stack-path helper. Core holder/path-array fields, destructor flags and capacity256 require a distinct structure/protocol proof.

The baseline automatic inventory reports42 eligible tokens. F1 covers39; the only three omitted are the two compensating31 cheat writes and404 wall sprite. Generic eligibility therefore is not semantic permission.

## Manifest-complete review coverage

Counts include self-explanatory syntax literals, so a residual count is not a defect count. Remaining rows below group every nontrivial raw literal by its function and retain representative source locations. This is a literal audit, not a claim of complete semantic decoding. Full baseline site records remain at artifacts/magic-numbers-20260906/inventory-before.json.

| Canonical translation unit | Numeric-bearing functions | Numeric tokens before | Selected sites | Remaining evidence family |
| --- | ---: | ---: | ---: | --- |
| src/battle/0042CB50_0042E8B0_battle_001.cpp | 21 | 647 | 85 | tactical grids/layers, ownership/action modes, HP/AP/score constants and wall/sprite ranges |
| src/battle/0042E9E0_00430C20_battle_002.cpp | 7 | 792 | 29 | tactical grids/layers, ownership/action modes, HP/AP/score constants and wall/sprite ranges |
| src/battle/00430F80_00433820_battle_003.cpp | 18 | 754 | 30 | tactical grids/layers, ownership/action modes, HP/AP/score constants and wall/sprite ranges |
| src/buildings/0041D030_0041F0C0_buildings_001.cpp | 27 | 616 | 20 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0041F1A0_00421010_buildings_002.cpp | 26 | 674 | 15 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00421240_00422020_buildings_003.cpp | 5 | 300 | 0 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00422100_00422AC0_buildings_004.cpp | 31 | 413 | 17 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00422B50_004254E0_buildings_005.cpp | 32 | 571 | 42 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00425540_00426FC0_buildings_006.cpp | 12 | 567 | 48 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/004272A0_00428850_buildings_007.cpp | 6 | 512 | 104 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00428880_0042A890_buildings_008.cpp | 13 | 1027 | 38 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0042A910_0042C4E0_buildings_009.cpp | 27 | 591 | 18 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0042C560_0042C840_buildings_010.cpp | 3 | 147 | 16 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/004338C0_00436100_buildings_001.cpp | 30 | 580 | 1 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00436180_00437A90_buildings_002.cpp | 16 | 520 | 77 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/004382E0_0043A880_buildings_003.cpp | 3 | 666 | 104 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0043A8B0_0043CC50_buildings_004.cpp | 7 | 714 | 103 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0043CD00_0043E4B0_buildings_005.cpp | 29 | 382 | 8 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0043E500_0043FDE0_buildings_006.cpp | 35 | 509 | 43 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/0043FEF0_00441BE0_buildings_007.cpp | 28 | 494 | 5 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/buildings/00441C80_00441D20_buildings_008.cpp | 2 | 24 | 0 | garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry |
| src/core/00401020_004011F0_core_001.cpp | 2 | 15 | 1 | holder/array layouts, destructor flags and path/device protocols |
| src/core/004015A0_00401A00_core_001.cpp | 13 | 121 | 0 | holder/array layouts, destructor flags and path/device protocols |
| src/persistence/00441DC0_00443B60_persistence_001.cpp | 23 | 455 | 5 | save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions |
| src/persistence/00443BB0_00445CE0_persistence_002.cpp | 17 | 584 | 3 | save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions |
| src/persistence/00446230_00447840_persistence_003.cpp | 31 | 613 | 21 | save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions |
| src/persistence/004479C0_0044AE10_persistence_004.cpp | 24 | 635 | 2 | save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions |
| src/persistence/0044AE90_0044E850_persistence_005.cpp | 13 | 838 | 24 | save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions |
| src/persistence/0044E880_0044FE70_persistence_006.cpp | 21 | 573 | 17 | save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions |
| src/strategic/004506B0_004530D0_strategic_001.cpp | 34 | 596 | 7 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/00452753_0045303F_strategic_007.cpp | 26 | 155 | 0 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/00453110_00455720_strategic_002.cpp | 44 | 341 | 39 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/00455740_004582B0_strategic_003.cpp | 45 | 497 | 37 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/00456706_00457789_strategic_008.cpp | 60 | 225 | 0 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/004589C0_004602F0_strategic_004.cpp | 15 | 680 | 47 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/00460360_00460910_strategic_005.cpp | 14 | 2787 | 5 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/strategic/00460950_004612E0_strategic_006.cpp | 23 | 270 | 0 | mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields |
| src/units/0040F510_00411560_units_001.cpp | 34 | 427 | 20 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/units/004115E0_00412BE0_units_002.cpp | 37 | 454 | 55 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/units/00412C00_00414350_units_003.cpp | 26 | 425 | 3 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/units/00414390_00416750_units_004.cpp | 19 | 510 | 12 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/units/00416850_00419120_units_005.cpp | 18 | 518 | 3 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/units/004191F0_0041A690_units_006.cpp | 21 | 599 | 7 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/units/0041A960_0041C8B0_units_007.cpp | 10 | 610 | 16 | AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments |
| src/world/00408030_0040A0A0_world_001.cpp | 19 | 333 | 4 | viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources |
| src/world/0040A0E0_0040B020_world_002.cpp | 23 | 1694 | 0 | viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources |
| src/world/0040B0A0_0040D560_world_003.cpp | 27 | 760 | 0 | viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources |
| src/world/0040D6D0_0040F4D0_world_004.cpp | 24 | 521 | 1 | viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources |

## Validation and handoff

- Author changed only F1_gameplay.json, F1_constants.json and this findings file. No production source/header, shared index, generated manifest or baseline changed in this subtask.
- Commands: manifest-backed literal_common.apply_files/token scans across all48 files; targeted rg/source and original-assembly reads; baseline42-site cross-check; in-memory apply_literal_names.validate_rules/resolve with proposed constants overlaid only in memory.
- Central acceptance: integrate reviewed numeric macros/manifest entries; resolve all batch rules once; inspect conflicts/respellings; require macro preprocessor-token identity and Direction8 object-code identity; update only normal affected catalogs/body hashes and run required public gates.
- Final in-memory validation: 1110 rules, 1132 resolved sites, 0 rejects, no macro respellings, 130 enum sites; validation errors: 0.
- No build/runtime/frame/campaign milestone is claimed by this authoring subtask.

## Complete residual lexeme/function inventory

### src/battle/0042CB50_0042E8B0_battle_001.cpp

Missing evidence: tactical grids/layers, ownership/action modes, HP/AP/score constants and wall/sprite ranges. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_HandleBattlefieldInteraction | `32` | 3 | 50, 51, 52 |
| UnitBattle_HandleBattlefieldInteraction | `31` | 4 | 51, 52, 55, 56 |
| UnitBattle_HandleBattlefieldInteraction | `6` | 8 | 51, 52, 52, 55 ... |
| UnitBattle_HandleBattlefieldInteraction | `16` | 5 | 54, 55, 56, 129 ... |
| UnitBattle_HandleBattlefieldInteraction | `808` | 1 | 57 |
| UnitBattle_HandleBattlefieldInteraction | `812` | 1 | 58 |
| UnitBattle_HandleBattlefieldInteraction | `1534` | 2 | 63, 74 |
| UnitBattle_HandleBattlefieldInteraction | `2` | 4 | 63, 74, 89, 241 |
| UnitBattle_HandleBattlefieldInteraction | `40` | 2 | 63, 74 |
| UnitBattle_HandleBattlefieldInteraction | `20` | 2 | 66, 83 |
| UnitBattle_HandleBattlefieldInteraction | `3134` | 2 | 66, 83 |
| UnitBattle_HandleBattlefieldInteraction | `100` | 6 | 67, 67, 71, 71 ... |
| UnitBattle_HandleBattlefieldInteraction | `854` | 3 | 77, 79, 256 |
| UnitBattle_HandleBattlefieldInteraction | `5u` | 3 | 88, 136, 240 |
| UnitBattle_HandleBattlefieldInteraction | `860` | 9 | 88, 121, 136, 152 ... |
| UnitBattle_HandleBattlefieldInteraction | `3` | 2 | 89, 241 |
| UnitBattle_HandleBattlefieldInteraction | `5` | 4 | 89, 121, 222, 241 |
| UnitBattle_HandleBattlefieldInteraction | `864` | 5 | 89, 89, 147, 241 ... |
| UnitBattle_HandleBattlefieldInteraction | `856` | 3 | 108, 110, 145 |
| UnitBattle_HandleBattlefieldInteraction | `858` | 2 | 111, 146 |
| UnitBattle_HandleBattlefieldInteraction | `1000` | 2 | 129, 178 |
| UnitBattle_HandleBattlefieldInteraction | `8` | 1 | 145 |
| UnitBattle_HandleBattlefieldInteraction | `875` | 1 | 194 |
| UnitBattle_EnableSelectedChargeMode | `2` | 3 | 305, 306, 307 |
| UnitBattle_RefreshSelectedActionButtons | `2` | 2 | 348, 356 |
| UnitBattle_SelectNextControllableUnit | `854` | 2 | 384, 406 |
| UnitBattle_SelectNextControllableUnit | `856` | 2 | 392, 396 |
| UnitBattle_SelectNextControllableUnit | `858` | 2 | 393, 397 |
| UnitBattle_SelectNextControllableUnit | `140051` | 1 | 406 |
| UnitBattle_ToggleSelectedShootingMode | `2` | 1 | 441 |
| UnitBattle_ToggleSelectedShootingMode | `8` | 2 | 441, 448 |
| UnitBattle_HandleRetreatAction | `4` | 1 | 466 |
| UnitBattle_HandleRetreatAction | `840` | 1 | 470 |
| UnitBattle_HandleRetreatAction | `848` | 1 | 470 |
| UnitBattle_HandleRetreatAction | `2` | 2 | 474, 474 |
| UnitBattle_ToggleSelectedChargeMode | `64` | 1 | 507 |
| UnitBattle_ToggleSelectedChargeMode | `2` | 1 | 509 |
| UnitBattle_ToggleSelectedChargeMode | `8` | 2 | 509, 520 |
| UnitBattle_HandlePrepareDefenceAction | `6` | 1 | 545 |
| UnitBattle_HandlePrepareDefenceAction | `4` | 1 | 548 |
| UnitBattle_HandlePrepareDefenceAction | `874` | 1 | 551 |
| UnitBattle_HandlePrepareDefenceAction | `2` | 2 | 558, 558 |
| UnitBattle_HandlePrepareDefenceAction | `3` | 1 | 559 |
| UnitBattle_HandlePrepareDefenceAction | `860` | 1 | 565 |
| UnitBattle_HandlePrepareDefenceAction | `864` | 1 | 566 |
| UnitBattle_RequestActionLoopExit | `4u` | 1 | 591 |
| UnitBattle_RequestActionLoopExit | `8` | 1 | 591 |
| UnitBattle_ShowPlayerMessageBanner | `3` | 4 | 619, 665, 669, 670 |
| UnitBattle_ShowPlayerMessageBanner | `2` | 6 | 620, 649, 650, 663 ... |
| UnitBattle_ShowPlayerMessageBanner | `4112` | 1 | 641 |
| UnitBattle_ShowPlayerMessageBanner | `8` | 3 | 645, 666, 679 |
| UnitBattle_ShowPlayerMessageBanner | `7` | 2 | 646, 660 |
| UnitBattle_ShowPlayerMessageBanner | `32` | 1 | 649 |
| UnitBattle_ShowPlayerMessageBanner | `448` | 1 | 649 |
| UnitBattle_ShowPlayerMessageBanner | `480` | 1 | 650 |
| UnitBattle_ShowPlayerMessageBanner | `188` | 1 | 653 |
| UnitBattle_ShowPlayerMessageBanner | `40` | 1 | 665 |
| UnitBattle_ShowPlayerMessageBanner | `55` | 1 | 669 |
| UnitBattle_ShowPlayerMessageBanner | `100` | 1 | 670 |
| UnitBattle_ShowPlayerMessageBanner | `0x140u` | 1 | 696 |
| UnitBattle_ShowPlayerMessageBanner | `0xF0u` | 1 | 696 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `40` | 2 | 758, 810 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `3` | 6 | 759, 785, 810, 813 ... |
| UnitBattle_ShowCurrentPlayerPromptDialog | `4112` | 1 | 770 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `8` | 2 | 774, 811 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `7` | 2 | 775, 805 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `2` | 5 | 778, 779, 808, 808 ... |
| UnitBattle_ShowCurrentPlayerPromptDialog | `32` | 1 | 778 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `448` | 1 | 778 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `480` | 1 | 779 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `0x9Fu` | 1 | 782 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `232` | 1 | 783 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `108` | 2 | 784, 787 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `13` | 1 | 786 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `27` | 1 | 786 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `14` | 1 | 787 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `16` | 1 | 788 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `188` | 1 | 789 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `46` | 1 | 795 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `52` | 1 | 795 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `55` | 1 | 813 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `100` | 1 | 814 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `4` | 1 | 814 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `0x140u` | 1 | 824 |
| UnitBattle_ShowCurrentPlayerPromptDialog | `0xF0u` | 1 | 824 |
| UnitBattle_AnimateSelectedUnitPanel | `6` | 2 | 871, 908 |
| UnitBattle_AnimateSelectedUnitPanel | `3` | 1 | 879 |
| UnitBattle_AnimateSelectedUnitPanel | `864` | 1 | 879 |
| UnitBattle_AnimateSelectedUnitPanel | `9` | 2 | 880, 913 |
| UnitBattle_AnimateSelectedUnitPanel | `863` | 1 | 881 |
| UnitBattle_AnimateSelectedUnitPanel | `4` | 1 | 882 |
| UnitBattle_AnimateSelectedUnitPanel | `72` | 1 | 884 |
| UnitBattle_AnimateSelectedUnitPanel | `10` | 1 | 886 |
| UnitBattle_AnimateSelectedUnitPanel | `5` | 1 | 886 |
| UnitBattle_AnimateSelectedUnitPanel | `11` | 1 | 888 |
| UnitBattle_AnimateSelectedUnitPanel | `15` | 2 | 888, 944 |
| UnitBattle_AnimateSelectedUnitPanel | `45` | 1 | 889 |
| UnitBattle_AnimateSelectedUnitPanel | `54` | 1 | 891 |
| UnitBattle_AnimateSelectedUnitPanel | `63` | 1 | 895 |
| UnitBattle_AnimateSelectedUnitPanel | `8` | 3 | 902, 911, 933 |
| UnitBattle_AnimateSelectedUnitPanel | `2` | 1 | 938 |
| UnitBattle_UpdateActionTooltip | `535` | 1 | 976 |
| UnitBattle_UpdateActionTooltip | `30` | 1 | 977 |
| UnitBattle_UpdateActionTooltip | `623` | 8 | 978, 983, 988, 993 ... |
| UnitBattle_UpdateActionTooltip | `83` | 1 | 979 |
| UnitBattle_UpdateActionTooltip | `499` | 7 | 981, 986, 991, 996 ... |
| UnitBattle_UpdateActionTooltip | `91` | 1 | 982 |
| UnitBattle_UpdateActionTooltip | `137` | 1 | 984 |
| UnitBattle_UpdateActionTooltip | `145` | 1 | 987 |
| UnitBattle_UpdateActionTooltip | `179` | 2 | 989, 992 |
| UnitBattle_UpdateActionTooltip | `213` | 2 | 994, 997 |
| UnitBattle_UpdateActionTooltip | `247` | 2 | 999, 1002 |
| UnitBattle_UpdateActionTooltip | `281` | 2 | 1004, 1007 |
| UnitBattle_UpdateActionTooltip | `315` | 2 | 1009, 1012 |
| UnitBattle_UpdateActionTooltip | `349` | 1 | 1014 |
| UnitBattle_UpdateActionTooltip | `7` | 1 | 1020 |
| UnitBattle_UpdateActionTooltip | `6` | 1 | 1025 |
| UnitBattle_UpdateActionTooltip | `5` | 1 | 1030 |
| UnitBattle_UpdateActionTooltip | `4` | 2 | 1035, 1057 |
| UnitBattle_UpdateActionTooltip | `3` | 3 | 1040, 1066, 1066 |
| UnitBattle_UpdateActionTooltip | `2` | 1 | 1045 |
| UnitBattle_RunTurnLoop | `9` | 1 | 1090 |
| UnitBattle_RunTurnLoop | `3944` | 1 | 1093 |
| UnitBattle_RunTurnLoop | `4` | 1 | 1093 |
| UnitBattle_RunTurnLoop | `854` | 1 | 1106 |
| UnitBattle_RunTurnLoop | `2` | 4 | 1118, 1119, 1127, 1127 |
| UnitBattle_RunTurnLoop | `3934` | 1 | 1118 |
| UnitBattle_RunTurnLoop | `808` | 3 | 1118, 1120, 1122 |
| UnitBattle_RunTurnLoop | `3935` | 1 | 1119 |
| UnitBattle_RunTurnLoop | `812` | 3 | 1119, 1120, 1122 |
| UnitBattle_RunTurnLoop | `3` | 1 | 1158 |
| HandleBattleResults | `6` | 4 | 1209, 1217, 1236, 1238 |
| HandleBattleResults | `10` | 2 | 1210, 1218 |
| HandleBattleResults | `18` | 2 | 1227, 1240 |
| HandleBattleResults | `12` | 1 | 1234 |
| HandleBattleResults | `836` | 1 | 1247 |
| HandleBattleResults | `854` | 1 | 1247 |
| HandleBattleResults | `0x1Cu` | 1 | 1259 |
| HandleBattleResults | `28` | 2 | 1260, 1261 |
| HandleBattleResults | `2` | 2 | 1264, 1264 |
| UnitBattle_TemporarilyClearGateBlocker | `828` | 3 | 1283, 1285, 1290 |
| UnitBattle_TemporarilyClearGateBlocker | `20` | 2 | 1285, 1290 |
| UnitBattle_TemporarilyClearGateBlocker | `824` | 2 | 1285, 1290 |
| UnitBattle_TemporarilyClearGateBlocker | `3134` | 2 | 1286, 1291 |
| UnitBattle_TemporarilyClearGateBlocker | `832` | 1 | 1289 |
| UnitBattle_RestoreGateBlocker | `828` | 2 | 1303, 1306 |
| UnitBattle_RestoreGateBlocker | `832` | 1 | 1305 |
| UnitBattle_RestoreGateBlocker | `20` | 1 | 1306 |
| UnitBattle_RestoreGateBlocker | `3134` | 1 | 1306 |
| UnitBattle_RestoreGateBlocker | `824` | 1 | 1306 |
| UnitBattle_OverrideControllerOrderBits | `3` | 1 | 1324 |
| UnitBattle_OverrideControllerOrderBits | `864` | 2 | 1324, 1328 |
| UnitBattle_OverrideControllerOrderBits | `854` | 2 | 1325, 1326 |
| UnitBattle_OverrideControllerOrderBits | `3u` | 1 | 1328 |
| UnitBattle_OverrideControllerOrderBits | `4` | 1 | 1330 |
| UnitBattle_OverrideControllerOrderBits | `88` | 1 | 1333 |
| UnitBattle_RestoreControllerOrderBits | `3` | 1 | 1353 |
| UnitBattle_RestoreControllerOrderBits | `864` | 1 | 1354 |
| UnitBattle_RestoreControllerOrderBits | `0xFCu` | 1 | 1356 |
| UnitBattle_RestoreControllerOrderBits | `833` | 2 | 1357, 1359 |
| UnitBattle_RestoreControllerOrderBits | `4` | 1 | 1358 |
| UnitBattle_RestoreControllerOrderBits | `88` | 1 | 1361 |
| UnitBattle_InitBattleScreenFrame | `2` | 1 | 1383 |
| UnitBattle_InitBattleScreenFrame | `243` | 2 | 1384, 1387 |
| UnitBattle_InitBattleScreenFrame | `3` | 1 | 1385 |
| UnitBattle_InitBattleScreenFrame | `46` | 1 | 1386 |
| UnitBattle_InitBattleScreenFrame | `20` | 2 | 1389, 1391 |

### src/battle/0042E9E0_00430C20_battle_002.cpp

Missing evidence: tactical grids/layers, ownership/action modes, HP/AP/score constants and wall/sprite ranges. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Battle_RunTacticalCombat | `100` | 1 | 90 |
| Battle_RunTacticalCombat | `3` | 5 | 91, 168, 331, 334 ... |
| Battle_RunTacticalCombat | `2` | 16 | 126, 166, 187, 267 ... |
| Battle_RunTacticalCombat | `4112` | 5 | 130, 139, 143, 147 ... |
| Battle_RunTacticalCombat | `13` | 1 | 154 |
| Battle_RunTacticalCombat | `243` | 2 | 167, 169 |
| Battle_RunTacticalCombat | `160` | 1 | 171 |
| Battle_RunTacticalCombat | `467` | 1 | 171 |
| Battle_RunTacticalCombat | `473` | 1 | 171 |
| Battle_RunTacticalCombat | `7` | 5 | 171, 275, 354, 359 ... |
| Battle_RunTacticalCombat | `76` | 1 | 171 |
| Battle_RunTacticalCombat | `0xF7C` | 2 | 173, 174 |
| Battle_RunTacticalCombat | `4` | 9 | 173, 182, 185, 197 ... |
| Battle_RunTacticalCombat | `211` | 1 | 177 |
| Battle_RunTacticalCombat | `836` | 18 | 183, 189, 190, 192 ... |
| Battle_RunTacticalCombat | `840` | 14 | 188, 189, 191, 193 ... |
| Battle_RunTacticalCombat | `140077` | 2 | 190, 191 |
| Battle_RunTacticalCombat | `140073` | 2 | 192, 193 |
| Battle_RunTacticalCombat | `720` | 2 | 195, 199 |
| Battle_RunTacticalCombat | `844` | 5 | 197, 201, 205, 207 ... |
| Battle_RunTacticalCombat | `0x320` | 5 | 253, 254, 279, 280 ... |
| Battle_RunTacticalCombat | `40` | 2 | 258, 267 |
| Battle_RunTacticalCombat | `800` | 8 | 258, 275, 278, 291 ... |
| Battle_RunTacticalCombat | `804` | 9 | 264, 278, 291, 293 ... |
| Battle_RunTacticalCombat | `808` | 2 | 276, 455 |
| Battle_RunTacticalCombat | `812` | 2 | 277, 456 |
| Battle_RunTacticalCombat | `0x5FE` | 2 | 279, 280 |
| Battle_RunTacticalCombat | `0x2AA` | 1 | 281 |
| Battle_RunTacticalCombat | `0x335` | 1 | 282 |
| Battle_RunTacticalCombat | `0x190` | 2 | 284, 285 |
| Battle_RunTacticalCombat | `0xC3E` | 1 | 284 |
| Battle_RunTacticalCombat | `0xDCE` | 1 | 285 |
| Battle_RunTacticalCombat | `828` | 8 | 286, 288, 305, 316 ... |
| Battle_RunTacticalCombat | `0x91E` | 1 | 287 |
| Battle_RunTacticalCombat | `5` | 1 | 290 |
| Battle_RunTacticalCombat | `816` | 2 | 290, 291 |
| Battle_RunTacticalCombat | `848` | 2 | 296, 297 |
| Battle_RunTacticalCombat | `824` | 9 | 303, 307, 309, 311 ... |
| Battle_RunTacticalCombat | `832` | 5 | 304, 316, 317, 405 ... |
| Battle_RunTacticalCombat | `20` | 12 | 311, 375, 377, 379 ... |
| Battle_RunTacticalCombat | `3534` | 2 | 312, 315 |
| Battle_RunTacticalCombat | `3134` | 4 | 316, 405, 406, 410 |
| Battle_RunTacticalCombat | `18` | 1 | 333 |
| Battle_RunTacticalCombat | `6` | 1 | 335 |
| Battle_RunTacticalCombat | `3934` | 3 | 355, 360, 455 |
| Battle_RunTacticalCombat | `3935` | 4 | 362, 363, 363, 456 |
| Battle_RunTacticalCombat | `3944` | 4 | 367, 373, 454, 480 |
| Battle_RunTacticalCombat | `854` | 1 | 435 |
| Battle_RunTacticalCombat | `860` | 1 | 438 |
| Battle_RunTacticalCombat | `0x8Fu` | 1 | 439 |
| Battle_RunTacticalCombat | `864` | 1 | 439 |
| Battle_RunTacticalCombat | `140051` | 2 | 500, 501 |
| UnitBattle_DrawUnitSprite | `3` | 2 | 641, 701 |
| UnitBattle_DrawUnitSprite | `854` | 4 | 656, 717, 717, 722 |
| UnitBattle_DrawUnitSprite | `7` | 1 | 657 |
| UnitBattle_DrawUnitSprite | `869` | 1 | 657 |
| UnitBattle_DrawUnitSprite | `855` | 3 | 658, 661, 666 |
| UnitBattle_DrawUnitSprite | `8` | 2 | 661, 733 |
| UnitBattle_DrawUnitSprite | `2` | 3 | 677, 712, 730 |
| UnitBattle_DrawUnitSprite | `90` | 1 | 677 |
| UnitBattle_DrawUnitSprite | `16` | 2 | 678, 721 |
| UnitBattle_DrawUnitSprite | `200` | 1 | 678 |
| UnitBattle_DrawUnitSprite | `50` | 2 | 678, 678 |
| UnitBattle_DrawUnitSprite | `63` | 6 | 678, 678, 691, 691 ... |
| UnitBattle_DrawUnitSprite | `6` | 2 | 708, 709 |
| UnitBattle_DrawUnitSprite | `40` | 1 | 711 |
| UnitBattle_DrawUnitSprite | `856` | 1 | 711 |
| UnitBattle_DrawUnitSprite | `858` | 1 | 712 |
| UnitBattle_DrawUnitSprite | `1534` | 1 | 713 |
| UnitBattle_DrawUnitSprite | `10` | 1 | 719 |
| UnitBattle_DrawUnitSprite | `120` | 1 | 721 |
| UnitBattle_DrawUnitSprite | `836` | 1 | 722 |
| UnitBattle_DrawUnitSprite | `17` | 1 | 723 |
| UnitBattle_DrawUnitSprite | `25` | 1 | 725 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `27` | 1 | 778 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `30` | 1 | 778 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `1532` | 3 | 782, 806, 822 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `2` | 8 | 782, 788, 794, 800 ... |
| UnitBattle_DrawMovingUnitInAdjacentTile | `40` | 8 | 782, 788, 794, 800 ... |
| UnitBattle_DrawMovingUnitInAdjacentTile | `64` | 6 | 784, 790, 808, 815 ... |
| UnitBattle_DrawMovingUnitInAdjacentTile | `804` | 4 | 786, 798, 820, 830 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `1536` | 3 | 788, 813, 832 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `1534` | 2 | 794, 800 |
| UnitBattle_DrawMovingUnitInAdjacentTile | `800` | 2 | 811, 827 |
| UnitBattle_DrawTileContents | `32` | 1 | 898 |
| UnitBattle_DrawTileContents | `6` | 2 | 898, 899 |
| UnitBattle_DrawTileContents | `808` | 2 | 898, 1176 |
| UnitBattle_DrawTileContents | `16` | 2 | 899, 1161 |
| UnitBattle_DrawTileContents | `812` | 2 | 899, 1173 |
| UnitBattle_DrawTileContents | `804` | 4 | 902, 1077, 1127, 1136 |
| UnitBattle_DrawTileContents | `800` | 4 | 903, 1077, 1103, 1118 |
| UnitBattle_DrawTileContents | `40` | 12 | 905, 907, 1042, 1056 ... |
| UnitBattle_DrawTileContents | `2` | 21 | 906, 907, 926, 941 ... |
| UnitBattle_DrawTileContents | `2334` | 1 | 910 |
| UnitBattle_DrawTileContents | `2335` | 1 | 913 |
| UnitBattle_DrawTileContents | `63` | 4 | 915, 915, 1174, 1177 |
| UnitBattle_DrawTileContents | `828` | 8 | 917, 957, 1003, 1005 ... |
| UnitBattle_DrawTileContents | `20` | 7 | 919, 955, 970, 1000 ... |
| UnitBattle_DrawTileContents | `3134` | 4 | 920, 962, 1001, 1033 |
| UnitBattle_DrawTileContents | `33` | 2 | 923, 965 |
| UnitBattle_DrawTileContents | `66` | 2 | 924, 966 |
| UnitBattle_DrawTileContents | `3534` | 6 | 930, 957, 970, 1013 ... |
| UnitBattle_DrawTileContents | `3` | 3 | 932, 972, 1037 |
| UnitBattle_DrawTileContents | `820` | 3 | 934, 975, 1019 |
| UnitBattle_DrawTileContents | `412` | 1 | 939 |
| UnitBattle_DrawTileContents | `404` | 1 | 943 |
| UnitBattle_DrawTileContents | `420` | 1 | 948 |
| UnitBattle_DrawTileContents | `840` | 1 | 959 |
| UnitBattle_DrawTileContents | `832` | 3 | 960, 1023, 1035 |
| UnitBattle_DrawTileContents | `416` | 1 | 980 |
| UnitBattle_DrawTileContents | `408` | 1 | 984 |
| UnitBattle_DrawTileContents | `424` | 1 | 989 |
| UnitBattle_DrawTileContents | `3133` | 3 | 1005, 1015, 1035 |
| UnitBattle_DrawTileContents | `428` | 1 | 1019 |
| UnitBattle_DrawTileContents | `5` | 1 | 1019 |
| UnitBattle_DrawTileContents | `4` | 1 | 1025 |
| UnitBattle_DrawTileContents | `1534` | 5 | 1042, 1089, 1092, 1139 ... |
| UnitBattle_DrawTileContents | `1532` | 4 | 1056, 1059, 1070, 1129 |
| UnitBattle_DrawTileContents | `64` | 6 | 1064, 1074, 1083, 1114 ... |
| UnitBattle_DrawTileContents | `1536` | 4 | 1079, 1106, 1109, 1120 |
| UnitBattle_DrawTileContents | `854` | 1 | 1158 |
| UnitBattle_DrawTileContents | `874` | 1 | 1159 |
| UnitBattle_DrawTileContents | `147151` | 1 | 1171 |
| UnitBattle_RedrawTile | `7` | 2 | 1215, 1216 |
| UnitBattle_RedrawTile | `808` | 3 | 1215, 1217, 1220 |
| UnitBattle_RedrawTile | `812` | 3 | 1216, 1218, 1221 |
| UnitBattle_RedrawTile | `6` | 3 | 1220, 1222, 1224 |
| UnitBattle_RedrawTile | `16` | 1 | 1222 |
| UnitBattle_RedrawTile | `80` | 1 | 1224 |
| UnitBattle_RedrawTile | `32` | 3 | 1226, 1227, 1227 |
| UnitBattle_RedrawTile | `96` | 1 | 1226 |
| UnitBattle_RedrawTile | `63` | 1 | 1227 |
| UnitBattle_RedrawTile | `95` | 1 | 1227 |
| UnitBattle_RedrawVisibleGrid | `808` | 3 | 1254, 1258, 1258 |
| UnitBattle_RedrawVisibleGrid | `812` | 3 | 1255, 1260, 1260 |
| UnitBattle_RedrawVisibleGrid | `800` | 1 | 1256 |
| UnitBattle_RedrawVisibleGrid | `804` | 1 | 1257 |
| UnitBattle_RedrawVisibleGrid | `7` | 2 | 1258, 1260 |
| UnitBattle_RedrawVisibleGrid | `1534` | 2 | 1267, 1275 |
| UnitBattle_RedrawVisibleGrid | `2` | 2 | 1267, 1275 |
| UnitBattle_RedrawVisibleGrid | `40` | 2 | 1267, 1275 |
| UnitBattle_RedrawVisibleGrid | `12` | 1 | 1281 |
| UnitBattle_RedrawVisibleGrid | `16` | 5 | 1282, 1287, 1302, 1304 ... |
| UnitBattle_RedrawVisibleGrid | `32` | 7 | 1284, 1287, 1290, 1292 ... |
| UnitBattle_RedrawVisibleGrid | `480` | 1 | 1284 |
| UnitBattle_RedrawVisibleGrid | `0x10u` | 2 | 1287, 1315 |
| UnitBattle_RedrawVisibleGrid | `0x1CFu` | 2 | 1287, 1343 |
| UnitBattle_RedrawVisibleGrid | `0x1DFu` | 4 | 1287, 1315, 1337, 1343 |
| UnitBattle_RedrawVisibleGrid | `0x20u` | 4 | 1287, 1315, 1317, 1343 |
| UnitBattle_RedrawVisibleGrid | `479` | 3 | 1296, 1298, 1334 |
| UnitBattle_RedrawVisibleGrid | `463` | 3 | 1308, 1310, 1340 |

### src/battle/00430F80_00433820_battle_003.cpp

Missing evidence: tactical grids/layers, ownership/action modes, HP/AP/score constants and wall/sprite ranges. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_DrawSelectedUnitPanel | `92` | 1 | 56 |
| UnitBattle_DrawSelectedUnitPanel | `12` | 2 | 87, 220 |
| UnitBattle_DrawSelectedUnitPanel | `2` | 20 | 87, 117, 139, 142 ... |
| UnitBattle_DrawSelectedUnitPanel | `3` | 4 | 87, 92, 204, 273 |
| UnitBattle_DrawSelectedUnitPanel | `9` | 3 | 87, 96, 299 |
| UnitBattle_DrawSelectedUnitPanel | `335` | 2 | 91, 94 |
| UnitBattle_DrawSelectedUnitPanel | `79` | 2 | 93, 103 |
| UnitBattle_DrawSelectedUnitPanel | `243` | 2 | 94, 287 |
| UnitBattle_DrawSelectedUnitPanel | `100` | 3 | 100, 116, 116 |
| UnitBattle_DrawSelectedUnitPanel | `188` | 3 | 103, 124, 131 |
| UnitBattle_DrawSelectedUnitPanel | `0xAu` | 4 | 106, 107, 267, 270 |
| UnitBattle_DrawSelectedUnitPanel | `10` | 2 | 113, 270 |
| UnitBattle_DrawSelectedUnitPanel | `0x1Au` | 1 | 116 |
| UnitBattle_DrawSelectedUnitPanel | `0x216u` | 1 | 116 |
| UnitBattle_DrawSelectedUnitPanel | `0x38u` | 1 | 116 |
| UnitBattle_DrawSelectedUnitPanel | `88` | 1 | 116 |
| UnitBattle_DrawSelectedUnitPanel | `7` | 2 | 122, 290 |
| UnitBattle_DrawSelectedUnitPanel | `21` | 3 | 127, 128, 133 |
| UnitBattle_DrawSelectedUnitPanel | `119` | 2 | 128, 133 |
| UnitBattle_DrawSelectedUnitPanel | `0x26Au` | 2 | 136, 137 |
| UnitBattle_DrawSelectedUnitPanel | `0x59u` | 2 | 136, 137 |
| UnitBattle_DrawSelectedUnitPanel | `500` | 8 | 136, 137, 147, 155 ... |
| UnitBattle_DrawSelectedUnitPanel | `69` | 2 | 136, 137 |
| UnitBattle_DrawSelectedUnitPanel | `118` | 1 | 139 |
| UnitBattle_DrawSelectedUnitPanel | `0x14u` | 1 | 141 |
| UnitBattle_DrawSelectedUnitPanel | `0x1F4u` | 1 | 141 |
| UnitBattle_DrawSelectedUnitPanel | `0x45u` | 1 | 141 |
| UnitBattle_DrawSelectedUnitPanel | `0x76u` | 1 | 141 |
| UnitBattle_DrawSelectedUnitPanel | `15` | 2 | 146, 189 |
| UnitBattle_DrawSelectedUnitPanel | `106` | 1 | 147 |
| UnitBattle_DrawSelectedUnitPanel | `618` | 7 | 147, 155, 166, 178 ... |
| UnitBattle_DrawSelectedUnitPanel | `8` | 9 | 147, 149, 160, 170 ... |
| UnitBattle_DrawSelectedUnitPanel | `14` | 1 | 148 |
| UnitBattle_DrawSelectedUnitPanel | `140051` | 6 | 150, 163, 173, 218 ... |
| UnitBattle_DrawSelectedUnitPanel | `151` | 1 | 155 |
| UnitBattle_DrawSelectedUnitPanel | `143` | 1 | 161 |
| UnitBattle_DrawSelectedUnitPanel | `498` | 3 | 161, 270, 302 |
| UnitBattle_DrawSelectedUnitPanel | `219` | 1 | 166 |
| UnitBattle_DrawSelectedUnitPanel | `211` | 1 | 171 |
| UnitBattle_DrawSelectedUnitPanel | `497` | 5 | 171, 184, 232, 241 ... |
| UnitBattle_DrawSelectedUnitPanel | `185` | 1 | 178 |
| UnitBattle_DrawSelectedUnitPanel | `177` | 1 | 184 |
| UnitBattle_DrawSelectedUnitPanel | `11` | 5 | 186, 188, 189, 191 ... |
| UnitBattle_DrawSelectedUnitPanel | `4` | 3 | 186, 222, 284 |
| UnitBattle_DrawSelectedUnitPanel | `16` | 1 | 192 |
| UnitBattle_DrawSelectedUnitPanel | `20` | 1 | 192 |
| UnitBattle_DrawSelectedUnitPanel | `0x03` | 3 | 195, 210, 222 |
| UnitBattle_DrawSelectedUnitPanel | `5` | 1 | 200 |
| UnitBattle_DrawSelectedUnitPanel | `0xDu` | 2 | 209, 215 |
| UnitBattle_DrawSelectedUnitPanel | `13` | 1 | 212 |
| UnitBattle_DrawSelectedUnitPanel | `255` | 1 | 213 |
| UnitBattle_DrawSelectedUnitPanel | `529` | 1 | 217 |
| UnitBattle_DrawSelectedUnitPanel | `0x07` | 1 | 222 |
| UnitBattle_DrawSelectedUnitPanel | `180` | 1 | 225 |
| UnitBattle_DrawSelectedUnitPanel | `245` | 1 | 232 |
| UnitBattle_DrawSelectedUnitPanel | `287` | 1 | 236 |
| UnitBattle_DrawSelectedUnitPanel | `279` | 2 | 241, 302 |
| UnitBattle_DrawSelectedUnitPanel | `321` | 1 | 245 |
| UnitBattle_DrawSelectedUnitPanel | `313` | 1 | 250 |
| UnitBattle_DrawSelectedUnitPanel | `4112` | 1 | 256 |
| UnitBattle_DrawSelectedUnitPanel | `24` | 1 | 261 |
| UnitBattle_DrawSelectedUnitPanel | `501` | 1 | 261 |
| UnitBattle_DrawSelectedUnitPanel | `0x162u` | 2 | 267, 270 |
| UnitBattle_DrawSelectedUnitPanel | `0x1F2u` | 2 | 267, 270 |
| UnitBattle_DrawSelectedUnitPanel | `0x270u` | 2 | 267, 270 |
| UnitBattle_DrawSelectedUnitPanel | `6` | 1 | 279 |
| UnitBattle_DrawSelectedUnitPanel | `488` | 1 | 287 |
| UnitBattle_ShowWallInfoPopup | `3` | 2 | 370, 424 |
| UnitBattle_ShowWallInfoPopup | `4112` | 1 | 384 |
| UnitBattle_ShowWallInfoPopup | `188` | 1 | 388 |
| UnitBattle_ShowWallInfoPopup | `0xCu` | 6 | 391, 392, 443, 444 ... |
| UnitBattle_ShowWallInfoPopup | `7` | 1 | 396 |
| UnitBattle_ShowWallInfoPopup | `46` | 5 | 398, 411, 430, 461 ... |
| UnitBattle_ShowWallInfoPopup | `52` | 4 | 398, 411, 430, 461 |
| UnitBattle_ShowWallInfoPopup | `14` | 2 | 408, 425 |
| UnitBattle_ShowWallInfoPopup | `820` | 1 | 408 |
| UnitBattle_ShowWallInfoPopup | `17` | 1 | 412 |
| UnitBattle_ShowWallInfoPopup | `2` | 4 | 423, 423, 426, 427 |
| UnitBattle_ShowWallInfoPopup | `189` | 1 | 424 |
| UnitBattle_ShowWallInfoPopup | `5` | 3 | 424, 431, 449 |
| UnitBattle_ShowWallInfoPopup | `51` | 1 | 424 |
| UnitBattle_ShowWallInfoPopup | `111` | 1 | 426 |
| UnitBattle_ShowWallInfoPopup | `53` | 2 | 426, 427 |
| UnitBattle_ShowWallInfoPopup | `177` | 1 | 427 |
| UnitBattle_ShowWallInfoPopup | `8` | 3 | 428, 458, 459 |
| UnitBattle_ShowWallInfoPopup | `840` | 2 | 428, 459 |
| UnitBattle_ShowWallInfoPopup | `11` | 1 | 450 |
| UnitBattle_ShowWallInfoPopup | `10` | 1 | 454 |
| UnitBattle_UpdateIdleAnimatedUnits | `0x354` | 1 | 514 |
| UnitBattle_UpdateIdleAnimatedUnits | `0x12` | 4 | 522, 525, 536, 539 |
| UnitBattle_UpdateIdleAnimatedUnits | `0x11` | 3 | 526, 527, 527 |
| UnitBattle_UpdateIdleAnimatedUnits | `0xF8` | 1 | 526 |
| UnitBattle_UpdateIdleAnimatedUnits | `7` | 2 | 527, 527 |
| UnitBattle_UpdateIdleAnimatedUnits | `3` | 1 | 534 |
| UnitBattle_RedrawUnitFootprint | `0x28` | 1 | 572 |
| UnitBattle_RedrawUnitFootprint | `2` | 1 | 574 |
| UnitBattle_RedrawUnitFootprint | `3` | 2 | 575, 581 |
| UnitBattle_RedrawUnitFootprint | `0x1B` | 2 | 577, 579 |
| UnitBattle_RedrawUnitFootprint | `30` | 1 | 616 |
| UnitBattle_RedrawUnitNeighborhood | `0x28` | 1 | 652 |
| UnitBattle_RedrawUnitNeighborhood | `2` | 1 | 654 |
| UnitBattle_RedrawUnitNeighborhood | `3` | 1 | 655 |
| Battle_PlaceReservedUnitSlotAtTile | `1503` | 2 | 701, 702 |
| Battle_PlaceReservedUnitSlotAtTile | `0x1Cu` | 1 | 702 |
| Battle_PlaceReservedUnitSlotAtTile | `28` | 2 | 703, 704 |
| Battle_PlaceReservedUnitSlotAtTile | `2` | 4 | 705, 708, 711, 713 |
| Battle_PlaceReservedUnitSlotAtTile | `30` | 1 | 705 |
| Battle_PlaceReservedUnitSlotAtTile | `1507` | 1 | 706 |
| Battle_PlaceReservedUnitSlotAtTile | `1509` | 1 | 707 |
| Battle_PlaceReservedUnitSlotAtTile | `804` | 1 | 708 |
| Battle_PlaceReservedUnitSlotAtTile | `6` | 1 | 709 |
| Battle_PlaceReservedUnitSlotAtTile | `1506` | 1 | 712 |
| Battle_PlaceReservedUnitSlotAtTile | `1534` | 1 | 713 |
| Battle_PlaceReservedUnitSlotAtTile | `21` | 3 | 713, 714, 715 |
| Battle_PlaceReservedUnitSlotAtTile | `40` | 1 | 713 |
| Battle_ClearReservedUnitSlot | `1503` | 2 | 730, 736 |
| Battle_ClearReservedUnitSlot | `1507` | 1 | 733 |
| Battle_ClearReservedUnitSlot | `1509` | 1 | 734 |
| Battle_ClearReservedUnitSlot | `1534` | 1 | 737 |
| Battle_ClearReservedUnitSlot | `2` | 1 | 737 |
| Battle_ClearReservedUnitSlot | `40` | 1 | 737 |
| Battle_RestoreSavedActionPointsBeforeResultCopy | `860` | 1 | 763 |
| Battle_PlaceUnit | `2` | 6 | 783, 786, 793, 813 ... |
| Battle_PlaceUnit | `1534` | 3 | 786, 793, 813 |
| Battle_PlaceUnit | `40` | 3 | 786, 793, 813 |
| Battle_PlaceUnit | `0x1Fu` | 1 | 804 |
| Battle_PlaceUnit | `856` | 1 | 805 |
| Battle_PlaceUnit | `858` | 1 | 806 |
| Battle_PlaceUnit | `855` | 1 | 807 |
| Battle_PlaceUnit | `8` | 1 | 808 |
| Battle_PlaceUnit | `860` | 1 | 810 |
| Battle_PlaceUnit | `874` | 1 | 811 |
| Battle_PlaceUnit | `0x8Fu` | 1 | 812 |
| Battle_PlaceUnit | `864` | 1 | 812 |
| Battle_PlaceUnit | `3944` | 1 | 814 |
| Battle_PlaceUnit | `4` | 1 | 814 |
| BuildingGarrisonDialog_CountSelectedSlots | `12` | 1 | 837 |
| BuildingGarrisonDialog_DrawSlotGrid | `4` | 2 | 864, 900 |
| BuildingGarrisonDialog_DrawSlotGrid | `184` | 1 | 878 |
| BuildingGarrisonDialog_DrawSlotGrid | `2` | 1 | 881 |
| BuildingGarrisonDialog_DrawSlotGrid | `3` | 4 | 882, 931, 939, 962 |
| BuildingGarrisonDialog_DrawSlotGrid | `32` | 3 | 884, 948, 950 |
| BuildingGarrisonDialog_DrawSlotGrid | `63` | 1 | 884 |
| BuildingGarrisonDialog_DrawSlotGrid | `126` | 1 | 891 |
| BuildingGarrisonDialog_DrawSlotGrid | `6` | 8 | 891, 892, 931, 937 ... |
| BuildingGarrisonDialog_DrawSlotGrid | `71` | 1 | 891 |
| BuildingGarrisonDialog_DrawSlotGrid | `131` | 7 | 892, 931, 937, 939 ... |
| BuildingGarrisonDialog_DrawSlotGrid | `75` | 3 | 892, 931, 937 |
| BuildingGarrisonDialog_DrawSlotGrid | `18` | 1 | 893 |
| BuildingGarrisonDialog_DrawSlotGrid | `15` | 3 | 896, 903, 925 |
| BuildingGarrisonDialog_DrawSlotGrid | `23` | 1 | 912 |
| BuildingGarrisonDialog_DrawSlotGrid | `10` | 1 | 916 |
| BuildingGarrisonDialog_DrawSlotGrid | `24` | 1 | 918 |
| BuildingGarrisonDialog_DrawSlotGrid | `5` | 2 | 923, 961 |
| BuildingGarrisonDialog_DrawSlotGrid | `14` | 1 | 928 |
| BuildingGarrisonDialog_DrawSlotGrid | `13` | 1 | 935 |
| BuildingGarrisonDialog_DrawSlotGrid | `125` | 1 | 939 |
| BuildingGarrisonDialog_DrawSlotGrid | `33` | 1 | 939 |
| BuildingGarrisonDialog_DrawSlotGrid | `22` | 1 | 942 |
| BuildingGarrisonDialog_DrawSlotGrid | `138` | 1 | 950 |
| BuildingGarrisonDialog_DrawSlotGrid | `139` | 2 | 951, 952 |
| BuildingGarrisonDialog_DrawSlotGrid | `12` | 1 | 959 |
| BuildingGarrisonDialog_DrawSlotGrid | `438` | 1 | 962 |
| BuildingGarrisonDialog_DrawSlotGrid | `53` | 1 | 962 |
| BuildingGarrisonDialog_DrawSlotGrid | `545` | 1 | 962 |
| BuildingGarrisonDialog_DrawSlotGrid | `613` | 1 | 962 |
| BuildingGarrisonDialog_ReloadSlotSprite | `104` | 1 | 986 |
| BuildingGarrisonDialog_ReloadSlotSprite | `18` | 2 | 999, 1001 |
| BuildingGarrisonDialog_ReloadSlotSprite | `4112` | 1 | 1002 |
| BuildingGarrisonDialog_RebuildSlotSprites | `12` | 1 | 1017 |
| BuildingGarrisonDialog_TickExitCountdown | `14` | 1 | 1027 |
| BuildingGarrisonDialog_TickExitCountdown | `10` | 1 | 1033 |
| BuildingGarrisonDialog_TickExitCountdown | `12` | 2 | 1036, 1046 |
| BuildingGarrisonDialog_TickExitCountdown | `7` | 2 | 1037, 1042 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `2` | 11 | 1112, 1113, 1178, 1232 ... |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `6` | 4 | 1124, 1191, 1296, 1311 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `18` | 6 | 1135, 1147, 1149, 1168 ... |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `31` | 3 | 1138, 1144, 1320 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `47` | 1 | 1140 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `3` | 5 | 1142, 1176, 1229, 1296 ... |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `289` | 3 | 1143, 1333, 1337 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `220` | 3 | 1148, 1335, 1337 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `33` | 3 | 1152, 1201, 1208 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `10` | 4 | 1154, 1203, 1210, 1315 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `46` | 6 | 1161, 1228, 1242, 1251 ... |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `7` | 1 | 1165 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `64` | 2 | 1173, 1229 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `162` | 1 | 1174 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `8` | 2 | 1175, 1191 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `15` | 2 | 1178, 1238 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `32` | 2 | 1178, 1313 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `88` | 1 | 1178 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `34` | 1 | 1179 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `20` | 2 | 1180, 1247 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `93` | 1 | 1180 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `0xAu` | 2 | 1193, 1195 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `4` | 2 | 1194, 1235 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `49` | 1 | 1198 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `192` | 1 | 1229 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `5` | 1 | 1229 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `105` | 2 | 1232, 1267 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `50` | 3 | 1232, 1264, 1266 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `85` | 2 | 1232, 1269 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `132` | 2 | 1234, 1264 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `148` | 2 | 1234, 1264 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `95` | 2 | 1234, 1268 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `11` | 5 | 1235, 1237, 1238, 1246 ... |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `27` | 1 | 1240 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `16` | 2 | 1247, 1311 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `26` | 1 | 1249 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `28` | 1 | 1256 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `106` | 1 | 1262 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `21` | 1 | 1262 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `160` | 1 | 1266 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `191` | 1 | 1266 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `74` | 1 | 1276 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `12` | 2 | 1282, 1311 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `62` | 2 | 1283, 1292 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `65` | 3 | 1283, 1292, 1328 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `30` | 1 | 1301 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `71` | 1 | 1309 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `178` | 1 | 1310 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `29` | 1 | 1325 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `149` | 1 | 1328 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `0x19u` | 2 | 1333, 1334 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `0x121u` | 1 | 1335 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `0xDCu` | 1 | 1335 |
| BuildingGarrisonDialog_DrawSelectedUnitPanel | `25` | 1 | 1336 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `256` | 1 | 1370 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `104` | 1 | 1372 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `18` | 4 | 1387, 1389, 1395, 1403 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `4112` | 1 | 1397 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `224` | 1 | 1409 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `255` | 1 | 1409 |
| BuildingGarrisonDialog_RebuildSelectedUnitPanelAssets | `4` | 1 | 1410 |
| BuildingGarrisonDialog_AnimateSelectedUnit | `10` | 1 | 1437 |
| BuildingGarrisonDialog_AnimateSelectedUnit | `7` | 1 | 1440 |
| BuildingGarrisonDialog_HitTestSlotGrid | `126` | 3 | 1455, 1457, 1459 |
| BuildingGarrisonDialog_HitTestSlotGrid | `75` | 2 | 1456, 1457 |
| BuildingGarrisonDialog_HitTestSlotGrid | `33` | 1 | 1457 |
| BuildingGarrisonDialog_HitTestSlotGrid | `71` | 2 | 1457, 1459 |
| BuildingGarrisonDialog_HitTestSlotGrid | `131` | 2 | 1458, 1459 |
| BuildingGarrisonDialog_HitTestSlotGrid | `64` | 1 | 1458 |
| BuildingGarrisonDialog_HitTestSlotGrid | `6` | 2 | 1459, 1462 |

### src/buildings/0041D030_0041F0C0_buildings_001.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Building_New | `147178` | 1 | 77 |
| Building_New | `147176` | 1 | 86 |
| Building_New | `2` | 11 | 101, 104, 107, 136 ... |
| Building_New | `0xFFFF` | 4 | 102, 105, 108, 112 |
| Building_New | `200` | 5 | 104, 107, 159, 224 ... |
| Building_New | `556376` | 4 | 104, 107, 226, 227 |
| Building_New | `509678` | 1 | 120 |
| Building_New | `3` | 1 | 135 |
| Building_New | `4` | 10 | 137, 237, 256, 263 ... |
| Building_New | `421` | 2 | 139, 193 |
| Building_New | `434` | 1 | 140 |
| Building_New | `50` | 1 | 140 |
| Building_New | `416` | 3 | 141, 144, 195 |
| Building_New | `16` | 1 | 142 |
| Building_New | `435` | 2 | 143, 146 |
| Building_New | `0xE0` | 1 | 144 |
| Building_New | `420` | 2 | 145, 148 |
| Building_New | `0xF8` | 2 | 146, 153 |
| Building_New | `436` | 2 | 147, 150 |
| Building_New | `0xFE` | 1 | 148 |
| Building_New | `432` | 2 | 149, 151 |
| Building_New | `0xC0` | 2 | 150, 174 |
| Building_New | `0xF000` | 3 | 151, 168, 194 |
| Building_New | `7` | 3 | 152, 190, 219 |
| Building_New | `444` | 3 | 153, 154, 155 |
| Building_New | `300` | 1 | 161 |
| Building_New | `438` | 1 | 162 |
| Building_New | `430` | 3 | 163, 194, 196 |
| Building_New | `100` | 1 | 165 |
| Building_New | `250` | 1 | 167 |
| Building_New | `0xFu` | 1 | 169 |
| Building_New | `5` | 1 | 173 |
| Building_New | `437` | 3 | 174, 176, 177 |
| Building_New | `442` | 1 | 175 |
| Building_New | `0x32` | 1 | 177 |
| Building_New | `422` | 1 | 190 |
| Building_New | `6` | 1 | 201 |
| Building_New | `439` | 1 | 202 |
| Building_New | `18` | 1 | 204 |
| Building_New | `13` | 1 | 209 |
| Building_New | `402` | 1 | 213 |
| Building_New | `401` | 1 | 215 |
| Building_New | `12` | 1 | 216 |
| Building_New | `707` | 2 | 231, 250 |
| Building_New | `711` | 2 | 235, 254 |
| Building_New | `14` | 2 | 240, 243 |
| Building_New | `140067` | 2 | 283, 284 |
| Building_LogBuiltCastleFacts | `2` | 1 | 340 |
| MapTile_IsCastleFoundationTile | `147` | 1 | 354 |
| MapTile_IsCastleFoundationTile | `185` | 1 | 354 |
| MapTile_IsCastleFoundationTile | `202` | 1 | 354 |
| MapTile_IsCastleFoundationTile | `204` | 1 | 354 |
| MapTile_IsCastleFoundationTile | `207` | 1 | 354 |
| MapTile_IsCastleFoundationTile | `39` | 1 | 354 |
| MapTile_IsCastleFoundationTile | `2` | 2 | 358, 362 |
| MapTile_IsCastleFoundationTile | `0x2C3u` | 1 | 360 |
| MapTile_IsCastleFoundationTile | `0x2CAu` | 1 | 360 |
| MapTile_IsCastleFoundationTile | `7` | 2 | 360, 360 |
| MapTile_IsCastleFoundationAnchorTile | `147` | 1 | 375 |
| MapTile_IsCastleFoundationAnchorTile | `185` | 1 | 375 |
| MapTile_IsCastleFoundationAnchorTile | `202` | 1 | 375 |
| MapTile_IsCastleFoundationAnchorTile | `204` | 1 | 375 |
| MapTile_IsCastleFoundationAnchorTile | `207` | 1 | 375 |
| MapTile_IsCastleFoundationAnchorTile | `39` | 1 | 375 |
| MapTile_IsCastleFoundationAnchorTile | `707` | 1 | 380 |
| MapTile_IsCastleFoundationAnchorTile | `711` | 1 | 380 |
| MapTile_IsCastleFoundationAnchorTile | `2` | 1 | 382 |
| Rules_RebuildCastleSiteFacts | `707` | 1 | 408 |
| Rules_RebuildCastleSiteFacts | `711` | 1 | 408 |
| Rules_RebuildCastleSiteFacts | `14` | 1 | 410 |
| BuildCursor_IsPlacementValid | `3` | 3 | 447, 483, 535 |
| BuildCursor_IsPlacementValid | `2` | 8 | 451, 452, 492, 495 ... |
| BuildCursor_IsPlacementValid | `147178` | 1 | 458 |
| BuildCursor_IsPlacementValid | `147176` | 3 | 466, 468, 474 |
| BuildCursor_IsPlacementValid | `200` | 5 | 479, 488, 489, 503 ... |
| BuildCursor_IsPlacementValid | `0x8000u` | 1 | 497 |
| BuildCursor_IsPlacementValid | `0xFFFF` | 2 | 498, 531 |
| BuildCursor_IsPlacementValid | `147` | 1 | 528 |
| BuildCursor_IsPlacementValid | `185` | 1 | 528 |
| BuildCursor_IsPlacementValid | `202` | 1 | 528 |
| BuildCursor_IsPlacementValid | `204` | 1 | 528 |
| BuildCursor_IsPlacementValid | `39` | 1 | 528 |
| Building_Stop | `12` | 2 | 557, 578 |
| Building_Stop | `16` | 2 | 561, 582 |
| Building_Stop | `18` | 1 | 569 |
| Building_Stop | `10` | 1 | 579 |
| Building_AssignUniqueGeneratedName | `24` | 1 | 593 |
| Building_AssignUniqueGeneratedName | `5` | 1 | 595 |
| Building_AssignUniqueGeneratedName | `47` | 2 | 599, 607 |
| Building_AssignUniqueGeneratedName | `48` | 1 | 605 |
| Building_FinishConstruction | `2` | 7 | 641, 642, 643, 645 ... |
| Building_FinishConstruction | `4` | 4 | 644, 647, 648, 677 |
| Building_FinishConstruction | `15` | 9 | 652, 653, 654, 655 ... |
| Building_FinishConstruction | `140051` | 1 | 681 |
| Building_FinishConstruction | `5` | 1 | 684 |
| Building_ProcessUnitProductionTurn | `416` | 1 | 708 |
| Building_ProcessUnitProductionTurn | `402` | 4 | 717, 735, 736, 741 |
| Building_ProcessUnitProductionTurn | `438` | 3 | 718, 736, 738 |
| Building_ProcessUnitProductionTurn | `18` | 2 | 725, 735 |
| Building_ProcessUnitProductionTurn | `12` | 1 | 729 |
| Building_ProcessUnitProductionTurn | `2` | 2 | 735, 737 |
| Building_ProcessUnitProductionTurn | `140051` | 1 | 739 |
| Building_UpdateGarrisonTrainRepairTimers | `18` | 1 | 782 |
| Building_UpdateGarrisonTrainRepairTimers | `9` | 1 | 786 |
| Building_UpdateGarrisonTrainRepairTimers | `4` | 1 | 792 |
| Building_UpdateGarrisonTrainRepairTimers | `5` | 1 | 792 |
| Building_UpdateGarrisonTrainRepairTimers | `7` | 2 | 792, 806 |
| Building_UpdateGarrisonTrainRepairTimers | `0xC7` | 1 | 793 |
| Building_UpdateGarrisonTrainRepairTimers | `8` | 1 | 795 |
| Building_UpdateGarrisonTrainRepairTimers | `0x3800` | 1 | 798 |
| Building_UpdateGarrisonTrainRepairTimers | `100` | 1 | 801 |
| Building_UpdateGarrisonTrainRepairTimers | `27` | 1 | 801 |
| Building_UpdateGarrisonTrainRepairTimers | `0xF8` | 1 | 807 |
| Building_UpdateGarrisonTrainRepairTimers | `0x700` | 1 | 811 |
| Building_UpdateGarrisonTrainRepairTimers | `140051` | 1 | 813 |
| Building_UpdateGarrisonTrainRepairTimers | `2` | 1 | 813 |
| Building_UpdateGarrisonTrainRepairTimers | `3` | 2 | 819, 824 |
| Building_UpdateGarrisonTrainRepairTimers | `30` | 5 | 819, 822, 823, 825 ... |
| Building_UpdateGarrisonTrainRepairTimers | `3u` | 1 | 820 |
| Building_UpdateGarrisonTrainRepairTimers | `0xFC` | 1 | 822 |
| Building_UpdateGarrisonTrainRepairTimers | `0xF3` | 2 | 826, 828 |
| Building_UpdateGarrisonTrainRepairTimers | `12` | 1 | 838 |
| Unit_NewTurnRegen | `429` | 3 | 862, 864, 865 |
| Unit_NewTurnRegen | `421` | 1 | 867 |
| Unit_NewTurnRegen | `7` | 1 | 869 |
| Unit_NewTurnRegen | `422` | 3 | 872, 875, 877 |
| Unit_NewTurnRegen | `0x64u` | 2 | 873, 876 |
| Unit_NewTurnRegen | `10` | 2 | 875, 876 |
| Unit_NewTurnRegen | `100` | 1 | 877 |
| Unit_UpdatePerTurn | `16` | 1 | 898 |
| Unit_UpdatePerTurn | `100` | 4 | 901, 905, 917, 919 |
| Unit_UpdatePerTurn | `422` | 2 | 901, 902 |
| Unit_UpdatePerTurn | `7` | 2 | 901, 924 |
| Unit_UpdatePerTurn | `4` | 1 | 904 |
| Unit_UpdatePerTurn | `10` | 2 | 906, 907 |
| Unit_UpdatePerTurn | `421` | 1 | 922 |
| UnitSlot_NeedsMoraleRecovery | `2` | 1 | 932 |
| UnitSlot_NeedsMoraleRecovery | `11` | 2 | 933, 935 |
| UnitSlot_NeedsMoraleRecovery | `6` | 1 | 933 |
| UnitSlot_NeedsMoraleRecovery | `10` | 1 | 935 |
| Building_RecoverGarrisonFatigueAndMorale | `18` | 1 | 948 |
| Building_RecoverGarrisonFatigueAndMorale | `12` | 1 | 950 |
| Building_RecoverGarrisonFatigueAndMorale | `50` | 1 | 955 |
| Player_UpdateTechnologyLevelFromSettlements | `3` | 2 | 993, 1013 |
| Player_UpdateTechnologyLevelFromSettlements | `4` | 2 | 995, 1000 |
| Player_UpdateTechnologyLevelFromSettlements | `2` | 5 | 996, 1000, 1008, 1011 ... |
| Player_UpdateTechnologyLevelFromSettlements | `416` | 1 | 998 |
| Player_UpdateTechnologyLevelFromSettlements | `0x10` | 1 | 1000 |
| Player_UpdateTechnologyLevelFromSettlements | `8` | 1 | 1000 |
| Player_UpdateTechnologyLevelFromSettlements | `100` | 2 | 1007, 1036 |
| Player_UpdateTechnologyLevelFromSettlements | `140071` | 2 | 1020, 1022 |
| Player_UpdateTechnologyLevelFromSettlements | `444` | 4 | 1027, 1029, 1030, 1031 |
| Player_UpdateTechnologyLevelFromSettlements | `7` | 2 | 1027, 1031 |
| Player_UpdateTechnologyLevelFromSettlements | `0xF8` | 1 | 1029 |
| Building_DebugDump | `4` | 1 | 1055 |
| Building_DebugDump | `2` | 1 | 1056 |
| Building_DebugDump | `438` | 1 | 1057 |
| Building_DebugDump | `0xFFF` | 1 | 1058 |
| Building_DebugDump | `430` | 1 | 1058 |
| Building_DebugDump | `16` | 1 | 1059 |
| Building_DebugDump | `18` | 2 | 1061, 1065 |
| Building_DebugDump | `49` | 1 | 1066 |
| Building_DebugDump | `80` | 1 | 1067 |
| Building_DebugDump | `111` | 1 | 1068 |
| Building_DebugDump | `142` | 1 | 1069 |
| Building_DebugDump | `173` | 1 | 1070 |
| Building_DebugDump | `204` | 1 | 1071 |
| Building_DebugDump | `235` | 1 | 1072 |
| Building_DebugDump | `266` | 1 | 1073 |
| Building_DebugDump | `297` | 1 | 1074 |
| Building_DebugDump | `328` | 1 | 1075 |
| Building_DebugDump | `359` | 1 | 1076 |
| LogAllBuildings | `4` | 1 | 1090 |
| LogAllBuildings | `100` | 2 | 1094, 1100 |
| Building_NewTurn | `509678` | 1 | 1123 |
| Building_NewTurn | `509676` | 1 | 1127 |
| Building_NewTurn | `420` | 1 | 1130 |
| Building_NewTurn | `509690` | 5 | 1131, 1133, 1145, 1146 ... |
| Building_NewTurn | `509692` | 1 | 1138 |
| Building_NewTurn | `17` | 1 | 1139 |
| Building_NewTurn | `2` | 2 | 1158, 1166 |
| Building_NewTurn | `4` | 2 | 1158, 1165 |
| Building_GetInto | `16` | 2 | 1202, 1230 |
| Building_GetInto | `4` | 3 | 1204, 1217, 1228 |
| Building_GetInto | `2u` | 1 | 1217 |
| Building_GetInto | `2` | 1 | 1229 |
| Building_BuildSchool | `2` | 1 | 1264 |
| Building_BuildSchool | `400` | 1 | 1265 |
| Building_BuildSchool | `140051` | 1 | 1266 |
| Building_BuildSchool | `300` | 1 | 1267 |
| Building_BuildSchool | `420` | 3 | 1268, 1273, 1278 |
| Building_BuildSchool | `438` | 2 | 1270, 1275 |
| Building_BuildSchool | `416` | 2 | 1274, 1276 |
| Building_BuildWorkshop | `2` | 1 | 1302 |
| Building_BuildWorkshop | `190` | 1 | 1303 |
| Building_BuildWorkshop | `140051` | 1 | 1304 |
| Building_BuildWorkshop | `90` | 1 | 1305 |
| Building_BuildWorkshop | `420` | 3 | 1306, 1311, 1316 |
| Building_BuildWorkshop | `438` | 2 | 1308, 1313 |
| Building_BuildWorkshop | `416` | 2 | 1312, 1314 |
| Building_BuildBarracks | `420` | 2 | 1333, 1341 |
| Building_BuildBarracks | `438` | 2 | 1335, 1338 |
| Building_BuildBarracks | `0xC8` | 1 | 1336 |
| Building_BuildBarracks | `200` | 1 | 1338 |
| Building_BuildBarracks | `416` | 1 | 1339 |
| Building_BuildHospital | `2` | 1 | 1366 |
| Building_BuildHospital | `200` | 1 | 1367 |
| Building_BuildHospital | `140051` | 1 | 1368 |
| Building_BuildHospital | `100` | 1 | 1369 |
| Building_BuildHospital | `420` | 3 | 1370, 1375, 1380 |
| Building_BuildHospital | `438` | 2 | 1372, 1377 |
| Building_BuildHospital | `416` | 2 | 1376, 1378 |
| Building_BuildSmiths | `2` | 1 | 1409 |
| Building_BuildSmiths | `230` | 1 | 1410 |
| Building_BuildSmiths | `140051` | 1 | 1411 |
| Building_BuildSmiths | `130` | 1 | 1412 |
| Building_BuildSmiths | `420` | 3 | 1413, 1418, 1423 |
| Building_BuildSmiths | `438` | 2 | 1415, 1420 |
| Building_BuildSmiths | `416` | 2 | 1419, 1421 |
| Building_FindFreeAdjacentSpawnTile | `0xFFFF` | 1 | 1445 |
| Building_FindFreeAdjacentSpawnTile | `2` | 4 | 1445, 1447, 1453, 1454 |
| Building_FindFreeAdjacentSpawnTile | `31` | 1 | 1445 |
| Building_FindFreeAdjacentSpawnTile | `24` | 1 | 1450 |
| Building_FindFreeAdjacentSpawnTile | `12` | 1 | 1451 |

### src/buildings/0041F1A0_00421010_buildings_002.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Building_Transfer | `3` | 5 | 61, 99, 100, 110 ... |
| Building_Transfer | `438` | 2 | 72, 126 |
| Building_Transfer | `215` | 5 | 76, 131, 135, 138 ... |
| Building_Transfer | `0xFu` | 3 | 77, 132, 137 |
| Building_Transfer | `2` | 13 | 86, 87, 88, 89 ... |
| Building_Transfer | `200` | 5 | 87, 88, 174, 193 ... |
| Building_Transfer | `556376` | 4 | 87, 88, 193, 195 |
| Building_Transfer | `31` | 2 | 89, 118 |
| Building_Transfer | `6` | 1 | 94 |
| Building_Transfer | `100` | 6 | 95, 96, 116, 119 ... |
| Building_Transfer | `0x1Cu` | 2 | 100, 112 |
| Building_Transfer | `14` | 2 | 101, 113 |
| Building_Transfer | `28` | 2 | 103, 114 |
| Building_Transfer | `30` | 2 | 104, 115 |
| Building_Transfer | `10` | 1 | 107 |
| Building_Transfer | `0xFFFFF000` | 1 | 136 |
| Building_Transfer | `4` | 2 | 155, 200 |
| Building_Transfer | `158` | 1 | 175 |
| Building_Transfer | `556374` | 1 | 176 |
| Building_Transfer | `435` | 1 | 197 |
| Building_Transfer | `7` | 1 | 197 |
| Building_Transfer | `140051` | 1 | 200 |
| Building_CalcGarrisonAverageHealthPercent | `7` | 2 | 220, 229 |
| Building_CalcGarrisonAverageHealthPercent | `422` | 1 | 224 |
| Building_CalcGarrisonAverageHealthPercent | `100` | 1 | 229 |
| Building_CanStartUpgrade | `2u` | 1 | 240 |
| Building_CanStartUpgrade | `421` | 2 | 240, 240 |
| Building_CanStartUpgrade | `429` | 1 | 240 |
| Building_CanStartUpgrade | `444` | 1 | 240 |
| Building_CanStartUpgrade | `7` | 1 | 240 |
| Building_TryStartUpgrade | `4` | 3 | 252, 254, 256 |
| Building_TryStartUpgrade | `421` | 3 | 252, 254, 256 |
| Building_TryStartUpgrade | `438` | 2 | 252, 256 |
| Building_TryStartUpgrade | `429` | 1 | 254 |
| Unit_CaptureBuilding | `45` | 1 | 294 |
| Unit_CaptureBuilding | `509690` | 1 | 296 |
| Unit_CaptureBuilding | `147178` | 3 | 298, 301, 311 |
| Unit_CaptureBuilding | `509676` | 2 | 298, 312 |
| Unit_CaptureBuilding | `510118` | 4 | 300, 304, 305, 306 |
| Unit_CaptureBuilding | `7` | 2 | 300, 306 |
| Unit_CaptureBuilding | `140071` | 1 | 301 |
| Unit_CaptureBuilding | `0xF8` | 1 | 304 |
| Unit_CaptureBuilding | `140067` | 2 | 313, 314 |
| Unit_CaptureBuilding | `3` | 1 | 318 |
| Unit_CaptureBuilding | `445` | 1 | 320 |
| Unit_CaptureBuilding | `2` | 1 | 321 |
| Unit_CaptureBuilding | `446` | 1 | 321 |
| Unit_CaptureBuilding | `6` | 1 | 326 |
| Unit_CaptureBuilding | `12` | 1 | 328 |
| Unit_CaptureBuilding | `509675` | 2 | 338, 338 |
| Building_Destroy | `11` | 1 | 359 |
| Building_Destroy | `18` | 4 | 364, 370, 380, 385 |
| Building_Destroy | `10` | 2 | 368, 377 |
| Building_Destroy | `16` | 2 | 396, 401 |
| Building_Destroy | `4` | 2 | 400, 400 |
| Building_Destroy | `509678` | 1 | 402 |
| Building_Destroy | `2` | 2 | 403, 412 |
| Building_Destroy | `509676` | 1 | 403 |
| Building_Destroy | `100` | 2 | 405, 411 |
| Building_Destroy | `141443` | 1 | 412 |
| Building_CalcRemainingConstructionTurns | `16` | 2 | 428, 440 |
| Building_CalcRemainingConstructionTurns | `18` | 1 | 434 |
| Building_CalcRemainingConstructionTurns | `50` | 1 | 442 |
| Building_FindRandomOwnedCompletedCastle | `113` | 1 | 453 |
| Building_FindRandomOwnedCompletedCastle | `2` | 1 | 463 |
| Building_FindRandomOwnedCompletedCastle | `509676` | 1 | 463 |
| Building_FindRandomOwnedCompletedCastle | `509678` | 1 | 463 |
| Building_FindRandomOwnedCompletedCastle | `509690` | 1 | 463 |
| Building_FindRandomOwnedCompletedCastle | `100` | 1 | 468 |
| Building_ShowHoverInfoPopup | `3` | 4 | 514, 575, 609, 623 |
| Building_ShowHoverInfoPopup | `4112` | 1 | 525 |
| Building_ShowHoverInfoPopup | `100` | 3 | 529, 530, 531 |
| Building_ShowHoverInfoPopup | `188` | 1 | 531 |
| Building_ShowHoverInfoPopup | `7` | 2 | 542, 578 |
| Building_ShowHoverInfoPopup | `4` | 3 | 543, 572, 573 |
| Building_ShowHoverInfoPopup | `2` | 17 | 545, 576, 580, 593 ... |
| Building_ShowHoverInfoPopup | `46` | 4 | 546, 560, 581, 610 |
| Building_ShowHoverInfoPopup | `52` | 4 | 546, 561, 581, 611 |
| Building_ShowHoverInfoPopup | `6` | 1 | 559 |
| Building_ShowHoverInfoPopup | `10` | 2 | 575, 623 |
| Building_ShowHoverInfoPopup | `235` | 1 | 575 |
| Building_ShowHoverInfoPopup | `5` | 3 | 575, 575, 623 |
| Building_ShowHoverInfoPopup | `435` | 1 | 578 |
| Building_ShowHoverInfoPopup | `37` | 1 | 582 |
| Building_ShowHoverInfoPopup | `25` | 2 | 593, 625 |
| Building_ShowHoverInfoPopup | `89` | 2 | 593, 598 |
| Building_ShowHoverInfoPopup | `150` | 5 | 594, 602, 603, 612 ... |
| Building_ShowHoverInfoPopup | `210` | 1 | 595 |
| Building_ShowHoverInfoPopup | `62` | 1 | 598 |
| Building_ShowHoverInfoPopup | `208` | 1 | 605 |
| Building_ShowHoverInfoPopup | `99` | 3 | 606, 612, 614 |
| Building_ShowHoverInfoPopup | `421` | 1 | 608 |
| Building_ShowHoverInfoPopup | `205` | 1 | 614 |
| Building_ShowHoverInfoPopup | `175` | 1 | 623 |
| Building_ShowHoverInfoPopup | `87` | 1 | 625 |
| Building_ShowConstructionProgressDialog | `12` | 2 | 690, 761 |
| Building_ShowConstructionProgressDialog | `3` | 12 | 691, 692, 693, 694 ... |
| Building_ShowConstructionProgressDialog | `4112` | 1 | 712 |
| Building_ShowConstructionProgressDialog | `2` | 15 | 716, 717, 743, 743 ... |
| Building_ShowConstructionProgressDialog | `640` | 1 | 716 |
| Building_ShowConstructionProgressDialog | `480` | 1 | 717 |
| Building_ShowConstructionProgressDialog | `188` | 1 | 718 |
| Building_ShowConstructionProgressDialog | `17` | 1 | 729 |
| Building_ShowConstructionProgressDialog | `46` | 1 | 731 |
| Building_ShowConstructionProgressDialog | `52` | 2 | 731, 764 |
| Building_ShowConstructionProgressDialog | `30` | 2 | 760, 761 |
| Building_ShowConstructionProgressDialog | `250` | 1 | 761 |
| Building_ShowConstructionProgressDialog | `32` | 1 | 762 |
| Building_ShowConstructionProgressDialog | `4` | 3 | 763, 763, 771 |
| Building_ShowConstructionProgressDialog | `77` | 1 | 766 |
| Building_ShowConstructionProgressDialog | `103` | 1 | 782 |
| Building_ShowConstructionProgressDialog | `220` | 1 | 783 |
| Building_ShowConstructionProgressDialog | `175` | 1 | 784 |
| Building_ShowConstructionProgressDialog | `100` | 1 | 785 |
| Building_ShowConstructionProgressDialog | `117` | 1 | 786 |
| Building_ShowConstructionProgressDialog | `92` | 1 | 787 |
| Building_ShowConstructionProgressDialog | `113` | 1 | 788 |
| Building_ShowConstructionProgressDialog | `60` | 1 | 789 |
| Timer_InitPerfCounterFrequency | `100` | 1 | 853 |
| Mem_ConstructObjectArray256 | `256` | 1 | 893 |
| Castle_RebuildMissingAddonFlags | `416` | 5 | 914, 915, 916, 917 ... |
| Castle_RebuildMissingAddonFlags | `10` | 1 | 920 |
| Castle_RebuildMissingAddonFlags | `50` | 1 | 920 |
| Castle_RebuildMissingAddonFlags | `4` | 1 | 927 |
| Castle_ShowNewBuildingMenu | `509` | 1 | 956 |
| Castle_ShowNewBuildingMenu | `66` | 1 | 956 |
| Castle_ShowNewBuildingMenu | `5` | 3 | 960, 976, 992 |
| Castle_ShowNewBuildingMenu | `3` | 2 | 966, 967 |
| Castle_ShowNewBuildingMenu | `46` | 1 | 977 |
| Castle_ShowNewBuildingMenu | `2` | 1 | 978 |
| Castle_ShowNewBuildingMenu | `52` | 1 | 979 |
| Castle_ShowNewBuildingMenu | `0x12Cu` | 2 | 994, 994 |
| Castle_ShowNewBuildingMenu | `300` | 1 | 994 |
| Castle_PlayAddonConstructionReveal | `639` | 1 | 1048 |
| Castle_PlayAddonConstructionReveal | `479` | 1 | 1053 |
| Castle_PlayAddonConstructionReveal | `184` | 1 | 1058 |
| Castle_PlayAddonConstructionReveal | `4` | 1 | 1058 |
| Castle_PlayAddonConstructionReveal | `640` | 1 | 1059 |
| Castle_PlayAddonConstructionReveal | `16` | 1 | 1061 |
| Castle_PlayAddonConstructionReveal | `12` | 1 | 1072 |
| Castle_PlayAddonConstructionReveal | `2` | 1 | 1075 |
| Castle_PlayAddonConstructionReveal | `480` | 1 | 1077 |
| Castle_PlayAddonConstructionReveal | `50` | 1 | 1078 |
| Castle_PlayAddonConstructionReveal | `250` | 1 | 1081 |
| Castle_PlayAddonConstructionReveal | `254` | 1 | 1081 |
| Castle_PlayAddonConstructionReveal | `200` | 1 | 1088 |
| Castle_PlayAddonConstructionReveal | `0xC8u` | 1 | 1101 |
| Castle_PlayAddonConstructionReveal | `255` | 1 | 1101 |
| Castle_BuildSchoolWithAnimation | `116` | 2 | 1143, 1152 |
| Castle_BuildSchoolWithAnimation | `416` | 2 | 1150, 1160 |
| Castle_BuildSchoolWithAnimation | `4` | 3 | 1154, 1155, 1156 |
| Castle_BuildSchoolWithAnimation | `2` | 2 | 1158, 1158 |
| Castle_BuildSchoolWithAnimation | `64` | 1 | 1161 |
| Castle_BuildSchoolWithAnimation | `251` | 1 | 1162 |
| Castle_BuildWorkshopWithAnimation | `416` | 2 | 1185, 1195 |
| Castle_BuildWorkshopWithAnimation | `116` | 1 | 1187 |
| Castle_BuildWorkshopWithAnimation | `4` | 3 | 1189, 1190, 1191 |
| Castle_BuildWorkshopWithAnimation | `2` | 2 | 1193, 1193 |
| Castle_BuildWorkshopWithAnimation | `64` | 1 | 1196 |
| Castle_BuildWorkshopWithAnimation | `252` | 1 | 1197 |
| Castle_BuildBarracksWithAnimation | `416` | 2 | 1219, 1229 |
| Castle_BuildBarracksWithAnimation | `116` | 1 | 1221 |
| Castle_BuildBarracksWithAnimation | `4` | 3 | 1223, 1224, 1225 |
| Castle_BuildBarracksWithAnimation | `2` | 2 | 1227, 1227 |
| Castle_BuildBarracksWithAnimation | `64` | 1 | 1230 |
| Castle_BuildBarracksWithAnimation | `254` | 1 | 1231 |
| Castle_BuildHospitalWithAnimation | `416` | 2 | 1255, 1264 |
| Castle_BuildHospitalWithAnimation | `116` | 1 | 1257 |
| Castle_BuildHospitalWithAnimation | `4` | 3 | 1259, 1260, 1261 |
| Castle_BuildHospitalWithAnimation | `2` | 3 | 1263, 1263, 1266 |
| Castle_BuildHospitalWithAnimation | `64` | 1 | 1270 |
| Castle_BuildHospitalWithAnimation | `250` | 1 | 1271 |
| Castle_BuildSmithsWithAnimation | `416` | 2 | 1296, 1306 |
| Castle_BuildSmithsWithAnimation | `116` | 1 | 1298 |
| Castle_BuildSmithsWithAnimation | `4` | 3 | 1300, 1301, 1302 |
| Castle_BuildSmithsWithAnimation | `2` | 2 | 1304, 1304 |
| Castle_BuildSmithsWithAnimation | `64` | 1 | 1307 |
| Castle_BuildSmithsWithAnimation | `253` | 1 | 1308 |
| Castle_ConfirmDestroyCurrentBuilding | `6` | 1 | 1334 |
| Castle_ConfirmDestroyCurrentBuilding | `2` | 2 | 1338, 1338 |
| Castle_DrawStatusPanel | `5` | 9 | 1366, 1366, 1369, 1375 ... |
| Castle_DrawStatusPanel | `9` | 2 | 1370, 1370 |
| Castle_DrawStatusPanel | `7` | 2 | 1372, 1382 |
| Castle_DrawStatusPanel | `11` | 1 | 1373 |
| Castle_DrawStatusPanel | `3` | 2 | 1373, 1375 |
| Castle_DrawStatusPanel | `421` | 1 | 1373 |
| Castle_DrawStatusPanel | `156` | 1 | 1374 |
| Castle_DrawStatusPanel | `26` | 1 | 1374 |
| Castle_DrawStatusPanel | `10` | 2 | 1375, 1384 |
| Castle_DrawStatusPanel | `275` | 1 | 1375 |
| Castle_DrawStatusPanel | `41` | 1 | 1375 |
| Castle_DrawStatusPanel | `2` | 4 | 1376, 1377, 1379, 1380 |
| Castle_DrawStatusPanel | `30` | 4 | 1376, 1377, 1379, 1380 |
| Castle_DrawStatusPanel | `58` | 4 | 1376, 1377, 1379, 1380 |
| Castle_DrawStatusPanel | `87` | 1 | 1376 |
| Castle_DrawStatusPanel | `149` | 1 | 1377 |
| Castle_DrawStatusPanel | `211` | 1 | 1379 |
| Castle_DrawStatusPanel | `273` | 1 | 1380 |
| Castle_DrawStatusPanel | `435` | 1 | 1382 |
| Castle_DrawStatusPanel | `127` | 1 | 1385 |
| Castle_DrawStatusPanel | `43` | 1 | 1385 |
| Castle_EnsureCompositeStatusWidget | `31` | 1 | 1409 |
| Castle_EnsureCompositeStatusWidget | `4` | 1 | 1410 |
| Castle_EnsureCompositeStatusWidget | `432` | 1 | 1410 |
| Castle_EnsureCompositeStatusWidget | `8` | 1 | 1411 |
| Castle_EnsureCompositeStatusWidget | `12` | 1 | 1412 |
| Castle_EnsureCompositeStatusWidget | `16` | 1 | 1413 |
| Castle_EnsureCompositeStatusWidget | `6` | 1 | 1413 |
| Castle_EnsureCompositeStatusWidget | `20` | 1 | 1414 |
| Castle_EnsureCompositeStatusWidget | `7` | 1 | 1414 |
| Castle_EnsureCompositeStatusWidget | `24` | 1 | 1415 |
| Castle_EnsureCompositeStatusWidget | `28` | 1 | 1416 |
| Castle_EnsureCompositeStatusWidget | `32` | 1 | 1417 |
| Castle_EnsureCompositeStatusWidget | `49` | 1 | 1418 |

### src/buildings/00421240_00422020_buildings_003.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Castle_RenderCompositeSceneLayers | `256` | 1 | 74 |
| Castle_RenderCompositeSceneLayers | `10` | 1 | 75 |
| Castle_RenderCompositeSceneLayers | `8` | 5 | 76, 216, 223, 226 ... |
| Castle_RenderCompositeSceneLayers | `49` | 2 | 88, 89 |
| Castle_RenderCompositeSceneLayers | `6` | 1 | 89 |
| Castle_RenderCompositeSceneLayers | `2` | 31 | 90, 93, 96, 99 ... |
| Castle_RenderCompositeSceneLayers | `416` | 10 | 92, 95, 98, 101 ... |
| Castle_RenderCompositeSceneLayers | `4` | 8 | 93, 96, 99, 102 ... |
| Castle_RenderCompositeSceneLayers | `0x10` | 3 | 216, 223, 226 |
| Castle_DrawAmbientAnimationLayer | `416` | 11 | 404, 419, 429, 438 ... |
| Castle_DrawAmbientAnimationLayer | `4` | 4 | 405, 436, 437, 455 |
| Castle_DrawAmbientAnimationLayer | `20` | 21 | 407, 410, 411, 422 ... |
| Castle_DrawAmbientAnimationLayer | `2` | 1 | 417 |
| Castle_DrawAmbientAnimationLayer | `0x10` | 1 | 420 |
| Castle_DrawAmbientAnimationLayer | `8` | 2 | 420, 472 |
| Castle_DrawAmbientAnimationLayer | `12` | 1 | 424 |
| Castle_DrawAmbientAnimationLayer | `3` | 2 | 427, 440 |
| Castle_DrawAmbientAnimationLayer | `24` | 1 | 433 |
| Castle_DrawAmbientAnimationLayer | `28` | 1 | 438 |
| Castle_DrawAmbientAnimationLayer | `31` | 2 | 438, 441 |
| Castle_DrawAmbientAnimationLayer | `30` | 1 | 441 |
| Castle_DrawAmbientAnimationLayer | `36` | 1 | 445 |
| Castle_DrawAmbientAnimationLayer | `5` | 1 | 449 |
| Castle_DrawAmbientAnimationLayer | `48` | 1 | 452 |
| Castle_DrawAmbientAnimationLayer | `6` | 1 | 454 |
| Castle_DrawAmbientAnimationLayer | `71` | 1 | 460 |
| Castle_DrawAmbientAnimationLayer | `7` | 1 | 463 |
| Castle_DrawAmbientAnimationLayer | `83` | 1 | 469 |
| Castle_DrawAmbientAnimationLayer | `95` | 1 | 478 |
| Castle_DrawAmbientAnimationLayer | `9` | 1 | 481 |
| Castle_DrawAmbientAnimationLayer | `136` | 1 | 487 |
| Castle_DrawAmbientAnimationLayer | `10` | 1 | 490 |
| Castle_DrawAmbientAnimationLayer | `167` | 1 | 496 |
| Castle_DrawAllAmbientAnimationLayers | `10` | 1 | 545 |
| Castle_UpdateAmbientAnimationLayers | `10` | 11 | 606, 614, 622, 641 ... |
| Castle_UpdateAmbientAnimationLayers | `0xCu` | 6 | 610, 611, 618, 626 ... |
| Castle_UpdateAmbientAnimationLayers | `2` | 2 | 620, 645 |
| Castle_UpdateAmbientAnimationLayers | `4` | 1 | 628 |
| Castle_UpdateAmbientAnimationLayers | `3` | 1 | 636 |
| Castle_UpdateAmbientAnimationLayers | `12` | 1 | 639 |
| Castle_UpdateAmbientAnimationLayers | `500` | 5 | 642, 660, 692, 709 ... |
| Castle_UpdateAmbientAnimationLayers | `5` | 2 | 655, 670 |
| Castle_UpdateAmbientAnimationLayers | `23` | 1 | 656 |
| Castle_UpdateAmbientAnimationLayers | `2000` | 4 | 660, 691, 708, 721 |
| Castle_UpdateAmbientAnimationLayers | `15` | 1 | 670 |
| Castle_UpdateAmbientAnimationLayers | `6` | 1 | 671 |
| Castle_UpdateAmbientAnimationLayers | `7` | 1 | 679 |
| Castle_UpdateAmbientAnimationLayers | `8` | 1 | 687 |
| Castle_UpdateAmbientAnimationLayers | `41` | 1 | 688 |
| Castle_UpdateAmbientAnimationLayers | `9` | 1 | 704 |
| Castle_UpdateAmbientAnimationLayers | `31` | 3 | 705, 718, 721 |
| Castle_RebuildSceneBuffers | `20` | 2 | 800, 841 |
| Castle_RebuildSceneBuffers | `49` | 1 | 807 |
| Castle_RebuildSceneBuffers | `6` | 1 | 807 |
| Castle_RebuildSceneBuffers | `8` | 1 | 809 |
| Castle_RebuildSceneBuffers | `7` | 1 | 810 |
| Castle_RebuildSceneBuffers | `13` | 1 | 811 |
| Castle_RebuildSceneBuffers | `0xD0` | 2 | 818, 830 |

### src/buildings/00422100_00422AC0_buildings_004.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Castle_UpdateGateToggles | `420` | 1 | 36 |
| Castle_UpdateGateToggles | `2` | 2 | 41, 43 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `4` | 1 | 77 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `8` | 1 | 78 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `12` | 1 | 79 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `16` | 1 | 80 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `20` | 1 | 81 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `24` | 1 | 82 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `28` | 1 | 83 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `32` | 1 | 84 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `36` | 1 | 85 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `40` | 1 | 86 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `44` | 1 | 87 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `2` | 1 | 88 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `48` | 1 | 88 |
| BuildingGarrisonDialog_WriteActionWidgetRecord | `49` | 1 | 89 |
| BuildingGarrisonDialog_EnsureActionWidgets | `416` | 1 | 112 |
| BuildingGarrisonDialog_EnsureActionWidgets | `39` | 1 | 116 |
| BuildingGarrisonDialog_EnsureActionWidgets | `426` | 5 | 117, 129, 141, 153 ... |
| BuildingGarrisonDialog_EnsureActionWidgets | `1000` | 3 | 128, 140, 152 |
| BuildingGarrisonDialog_EnsureActionWidgets | `155` | 1 | 128 |
| BuildingGarrisonDialog_EnsureActionWidgets | `2` | 3 | 128, 131, 139 |
| BuildingGarrisonDialog_EnsureActionWidgets | `3` | 2 | 132, 151 |
| BuildingGarrisonDialog_EnsureActionWidgets | `272` | 1 | 140 |
| BuildingGarrisonDialog_EnsureActionWidgets | `4` | 2 | 143, 163 |
| BuildingGarrisonDialog_EnsureActionWidgets | `5` | 1 | 144 |
| BuildingGarrisonDialog_EnsureActionWidgets | `385` | 1 | 152 |
| BuildingGarrisonDialog_EnsureActionWidgets | `8` | 2 | 152, 167 |
| BuildingGarrisonDialog_EnsureActionWidgets | `6` | 1 | 155 |
| BuildingGarrisonDialog_EnsureActionWidgets | `7` | 1 | 156 |
| BuildingGarrisonDialog_EnsureActionWidgets | `503` | 1 | 164 |
| BuildingGarrisonDialog_EnsureActionWidgets | `9` | 1 | 168 |
| BuildingGarrisonDialog_Run | `2` | 3 | 204, 378, 382 |
| BuildingGarrisonDialog_Run | `12` | 3 | 207, 209, 363 |
| BuildingGarrisonDialog_Run | `7` | 2 | 210, 247 |
| BuildingGarrisonDialog_Run | `188` | 2 | 214, 218 |
| BuildingGarrisonDialog_Run | `33` | 2 | 216, 220 |
| BuildingGarrisonDialog_Run | `64` | 3 | 216, 220, 318 |
| BuildingGarrisonDialog_Run | `1024` | 1 | 222 |
| BuildingGarrisonDialog_Run | `256` | 1 | 224 |
| BuildingGarrisonDialog_Run | `4112` | 1 | 237 |
| BuildingGarrisonDialog_Run | `5` | 1 | 246 |
| BuildingGarrisonDialog_Run | `8` | 1 | 252 |
| BuildingGarrisonDialog_Run | `20` | 7 | 261, 264, 270, 334 ... |
| BuildingGarrisonDialog_Run | `18` | 3 | 303, 305, 328 |
| BuildingGarrisonDialog_Run | `10` | 1 | 308 |
| Diagnostics_PrimeBattleSafeCursorOnTurnLoop | `370` | 1 | 497 |
| Diagnostics_PrimeBattleSafeCursorOnTurnLoop | `560` | 1 | 497 |
| Diagnostics_CountBattleUnitsForOwner | `854` | 1 | 511 |
| Diagnostics_TraceBattleUnitSnapshot | `2` | 1 | 553 |
| Diagnostics_TraceBattleUnitSnapshot | `4` | 1 | 555 |
| Diagnostics_TraceBattleUnitSnapshot | `6` | 1 | 556 |
| Diagnostics_TraceBattleUnitSnapshot | `8` | 1 | 557 |
| Diagnostics_TraceBattleUnitSnapshot | `9` | 1 | 558 |
| Diagnostics_TraceBattleUnitSnapshot | `12` | 1 | 559 |
| Diagnostics_TraceBattleUnitSnapshot | `808` | 1 | 562 |
| Diagnostics_TraceBattleUnitSnapshot | `812` | 1 | 563 |
| Diagnostics_CountBattleDeploymentBucketEntries | `48` | 1 | 574 |
| Diagnostics_ShouldTraceWorldMapActionStage | `21` | 1 | 641 |
| Diagnostics_ShouldTraceWorldMapActionStage | `16` | 1 | 643 |
| Diagnostics_ShouldTraceWorldMapActionStage | `13` | 1 | 645 |
| Diagnostics_ShouldTraceWorldMapActionStage | `0xFF` | 2 | 656, 664 |
| Diagnostics_ShouldTraceWorldMapActionStage | `32` | 1 | 656 |
| Diagnostics_ShouldTraceWorldMapActionStage | `64` | 1 | 664 |
| Diagnostics_ShouldTraceWorldMapActionStage | `23` | 1 | 666 |
| Diagnostics_SurfaceByteChecksum | `1024` | 1 | 696 |
| Diagnostics_SurfaceByteChecksum | `2166136261u` | 1 | 699 |
| Diagnostics_SurfaceByteChecksum | `16777619u` | 1 | 701 |
| Diagnostics_TraceCastleHotspots | `8` | 6 | 713, 714, 715, 716 ... |
| Diagnostics_TraceCastleHotspots | `640` | 2 | 727, 734 |
| Diagnostics_TraceCastleHotspots | `480` | 2 | 728, 732 |
| Diagnostics_TraceCastleHotspots | `248` | 4 | 737, 739, 751, 753 |
| Diagnostics_TraceCastleHotspots | `255` | 2 | 737, 751 |
| Diagnostics_TraceCastleHotspots | `2` | 2 | 765, 766 |
| Diagnostics_TraceWorldMapClickEvent | `100` | 1 | 795 |
| Diagnostics_TraceWorldMapClickEvent | `2` | 1 | 801 |
| Diagnostics_TraceWorldMapClickEvent | `4` | 1 | 802 |
| Diagnostics_TraceWorldMapClickEvent | `16` | 1 | 803 |
| Diagnostics_TraceBattlefieldClickEvent | `854` | 1 | 861 |
| Diagnostics_TraceBattlefieldClickEvent | `860` | 1 | 862 |
| Diagnostics_TraceBattlefieldClickEvent | `864` | 1 | 863 |
| Diagnostics_TraceBattlefieldClickEvent | `808` | 1 | 875 |
| Diagnostics_TraceBattlefieldClickEvent | `812` | 1 | 876 |
| Diagnostics_TraceWorldMapUnitSnapshot | `0x28` | 1 | 952 |
| Diagnostics_TraceWorldMapUnitSnapshot | `8` | 2 | 966, 991 |
| Diagnostics_TraceWorldMapUnitSnapshot | `9` | 2 | 967, 992 |
| Diagnostics_TraceWorldMapUnitSnapshot | `11` | 2 | 968, 993 |
| Diagnostics_TraceWorldMapUnitSnapshot | `10` | 2 | 969, 994 |
| Diagnostics_TraceWorldMapUnitSnapshot | `720` | 1 | 972 |
| Diagnostics_TraceWorldMapUnitSnapshot | `12` | 1 | 995 |
| Diagnostics_TraceWorldMapUnitSnapshot | `13` | 1 | 996 |
| Castle_OpenManagementScreen | `20` | 4 | 1095, 1148, 1274, 1313 |
| Castle_OpenManagementScreen | `2` | 6 | 1115, 1116, 1134, 1136 ... |
| Castle_OpenManagementScreen | `49` | 2 | 1120, 1139 |
| Castle_OpenManagementScreen | `6` | 2 | 1120, 1139 |
| Castle_OpenManagementScreen | `4112` | 4 | 1121, 1140, 1144, 1315 |
| Castle_OpenManagementScreen | `188` | 2 | 1150, 1285 |
| Castle_OpenManagementScreen | `3` | 10 | 1156, 1196, 1205, 1213 ... |
| Castle_OpenManagementScreen | `4` | 1 | 1157 |
| Castle_OpenManagementScreen | `10` | 1 | 1158 |
| Castle_OpenManagementScreen | `57` | 1 | 1160 |
| Castle_OpenManagementScreen | `190` | 1 | 1161 |
| Castle_OpenManagementScreen | `248` | 2 | 1161, 1191 |
| Castle_OpenManagementScreen | `455` | 2 | 1161, 1161 |
| Castle_OpenManagementScreen | `7` | 2 | 1161, 1296 |
| Castle_OpenManagementScreen | `134` | 2 | 1193, 1195 |
| Castle_OpenManagementScreen | `250` | 1 | 1199 |
| Castle_OpenManagementScreen | `153` | 2 | 1201, 1204 |
| Castle_OpenManagementScreen | `251` | 1 | 1208 |
| Castle_OpenManagementScreen | `156` | 2 | 1210, 1212 |
| Castle_OpenManagementScreen | `252` | 1 | 1216 |
| Castle_OpenManagementScreen | `159` | 2 | 1218, 1220 |
| Castle_OpenManagementScreen | `253` | 1 | 1224 |
| Castle_OpenManagementScreen | `166` | 2 | 1226, 1228 |
| Castle_OpenManagementScreen | `254` | 1 | 1232 |
| Castle_OpenManagementScreen | `99` | 2 | 1234, 1241 |
| Castle_OpenManagementScreen | `416` | 1 | 1236 |
| Castle_OpenManagementScreen | `8` | 3 | 1239, 1272, 1295 |
| Castle_OpenManagementScreen | `255` | 1 | 1245 |
| Castle_OpenManagementScreen | `135` | 2 | 1247, 1249 |
| Castle_OpenManagementScreen | `32` | 1 | 1288 |
| Castle_OpenManagementScreen | `13` | 1 | 1297 |
| Castle_OpenManagementScreen | `400` | 1 | 1312 |
| Castle_OpenManagementScreen | `144` | 1 | 1315 |
| Tooltip_CaptureBackdrop | `2` | 1 | 1407 |
| Tooltip_CaptureBackdrop | `188` | 1 | 1408 |
| Tooltip_ReleaseBackdropSurface | `2` | 1 | 1440 |
| Tooltip_ShowText | `2` | 2 | 1485, 1487 |

### src/buildings/00422B50_004254E0_buildings_005.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Unit_CountSelectedGroupMembers | `6` | 1 | 42 |
| Unit_CountSelectedGroupMembers | `10` | 1 | 43 |
| UnitStack_HasOnlyFlyingUnits | `6` | 1 | 59 |
| UnitStack_HasOnlyFlyingUnits | `10` | 1 | 70 |
| Unit_AddToGroup | `4` | 2 | 118, 120 |
| Unit_AddToGroup | `720` | 1 | 128 |
| Unit_CanMoveSelectionFromGroupToTile | `0x1F4u` | 1 | 178 |
| Unit_CanMoveSelectionFromGroupToTile | `4` | 3 | 180, 187, 190 |
| Unit_CanMoveSelectionFromGroupToTile | `0x28` | 1 | 185 |
| Unit_MoveSelectionFromGroupToTile | `4` | 2 | 213, 257 |
| Unit_MoveSelectionFromGroupToTile | `0x8000` | 1 | 231 |
| Unit_MoveSelectionFromGroupToTile | `0xFFFFFFFF` | 1 | 247 |
| Unit_MoveSelectionFromGroupToTile | `8` | 1 | 257 |
| Unit_MoveSelectionFromGroupToTile | `720` | 1 | 262 |
| UI_LoadCurrentPlayerInfoSpriteSet | `24` | 1 | 279 |
| UI_LoadCurrentPlayerInfoSpriteSet | `4112` | 1 | 290 |
| UnitStackSelection_RedrawPanel | `11` | 1 | 337 |
| UnitStackSelection_RedrawPanel | `8` | 2 | 346, 351 |
| UnitStackSelection_RedrawPanel | `16` | 1 | 353 |
| UnitStackSelection_RedrawPanel | `5` | 1 | 353 |
| UnitStackSelection_RedrawPanel | `10` | 2 | 356, 374 |
| UnitStackSelection_RedrawPanel | `0x28` | 1 | 358 |
| UnitStackSelection_RedrawPanel | `6` | 3 | 358, 376, 378 |
| UnitStackSelection_RedrawPanel | `12` | 1 | 360 |
| UnitStackSelection_RedrawPanel | `2` | 3 | 362, 362, 363 |
| UnitStackSelection_RedrawPanel | `4` | 5 | 369, 380, 387, 391 ... |
| UnitStackSelection_RedrawPanel | `35` | 2 | 372, 379 |
| UnitStackSelection_RedrawPanel | `29` | 1 | 373 |
| UnitStackSelection_RedrawPanel | `400` | 1 | 373 |
| UnitStackSelection_RedrawPanel | `38` | 5 | 379, 383, 388, 388 ... |
| UnitStackSelection_RedrawPanel | `401` | 1 | 379 |
| UnitStackSelection_RedrawPanel | `19` | 1 | 380 |
| UnitStackSelection_RedrawPanel | `33` | 1 | 382 |
| UnitStackSelection_RedrawPanel | `40` | 1 | 383 |
| UnitStackSelection_RedrawPanel | `405` | 1 | 383 |
| UnitStackSelection_RedrawPanel | `7` | 1 | 385 |
| UnitStackSelection_RedrawPanel | `3` | 1 | 388 |
| UnitStackSelection_RedrawPanel | `32` | 1 | 388 |
| UnitStackSelection_RedrawPanel | `450` | 1 | 388 |
| UnitStackSelection_RedrawPanel | `70` | 1 | 388 |
| UnitStackSelection_RedrawPanel | `14` | 1 | 391 |
| UnitStackSelection_RedrawPanel | `4u` | 1 | 391 |
| UnitStackSelection_RedrawPanel | `402` | 1 | 392 |
| UnitStackSelection_RedrawPanel | `58` | 1 | 392 |
| UnitStack_ShowSelectionDialog | `40` | 1 | 422 |
| UnitStackSelection_HandleInput | `12` | 1 | 466 |
| UnitStackSelection_HandleInput | `35` | 1 | 470 |
| UnitStackSelection_HandleInput | `38` | 1 | 470 |
| UnitStackSelection_HandleInput | `400` | 1 | 472 |
| UnitStackSelection_HandleInput | `464` | 1 | 473 |
| UnitStackSelection_HandleInput | `9` | 1 | 475 |
| UnitStackSelection_HandleInput | `6` | 3 | 478, 481, 484 |
| UnitStackSelection_HandleInput | `100` | 2 | 481, 481 |
| UnitStackSelection_HandleInput | `32` | 1 | 534 |
| UnitStackSelection_HandleInput | `64` | 2 | 534, 535 |
| UnitStackSelection_HandleInput | `16` | 1 | 535 |
| UnitStackSelection_HandleInput | `2` | 1 | 541 |
| UnitStackSelection_HandleInput | `10` | 1 | 548 |
| UnitStackSelection_HasSelectedSlots | `4` | 1 | 603 |
| UnitStackSelection_HasSelectedSlots | `40` | 1 | 604 |
| MapTile_HasNorthRoadConnection | `4` | 1 | 673 |
| MapTile_HasNorthRoadConnection | `867` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `868` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `869` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `871` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `872` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `874` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `875` | 1 | 674 |
| MapTile_HasNorthRoadConnection | `952` | 1 | 674 |
| MapTile_HasSouthRoadConnection | `4` | 1 | 683 |
| MapTile_HasSouthRoadConnection | `867` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `869` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `870` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `872` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `873` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `875` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `876` | 1 | 684 |
| MapTile_HasSouthRoadConnection | `951` | 1 | 684 |
| MapTile_HasWestRoadConnection | `2` | 3 | 699, 703, 705 |
| MapTile_HasWestRoadConnection | `556370` | 1 | 699 |
| MapTile_HasWestRoadConnection | `0x8000` | 1 | 701 |
| MapTile_HasWestRoadConnection | `65534` | 1 | 702 |
| MapTile_HasWestRoadConnection | `4` | 2 | 703, 707 |
| MapTile_HasWestRoadConnection | `866` | 1 | 708 |
| MapTile_HasWestRoadConnection | `868` | 1 | 708 |
| MapTile_HasWestRoadConnection | `869` | 1 | 708 |
| MapTile_HasWestRoadConnection | `870` | 1 | 708 |
| MapTile_HasWestRoadConnection | `871` | 1 | 708 |
| MapTile_HasWestRoadConnection | `872` | 1 | 708 |
| MapTile_HasWestRoadConnection | `873` | 1 | 708 |
| MapTile_HasWestRoadConnection | `949` | 1 | 708 |
| MapTile_HasEastRoadConnection | `4` | 1 | 720 |
| MapTile_HasEastRoadConnection | `866` | 1 | 721 |
| MapTile_HasEastRoadConnection | `871` | 1 | 721 |
| MapTile_HasEastRoadConnection | `876` | 1 | 721 |
| MapTile_HasEastRoadConnection | `950` | 1 | 721 |
| Map_RebuildRoadOverlayAtTile | `8` | 1 | 746 |
| Map_RebuildRoadOverlayAtTile | `4` | 3 | 747, 753, 755 |
| Map_RebuildRoadOverlayAtTile | `2` | 1 | 748 |
| Map_NormalizeRoadOverlayTileId | `819` | 1 | 768 |
| Map_NormalizeRoadOverlayTileId | `861` | 1 | 768 |
| Map_NormalizeRoadOverlayTileId | `877` | 2 | 770, 771 |
| Map_NormalizeRoadOverlayTileId | `949` | 1 | 770 |
| Map_NormalizeRoadOverlayTileId | `3` | 1 | 771 |
| Map_NormalizeRoadOverlayTileId | `6` | 1 | 771 |
| Map_NormalizeRoadOverlayTileId | `866` | 1 | 771 |
| MapTile_HasAlignedBridgeApproachRoadOverlay | `2` | 2 | 791, 813 |
| MapTile_HasAlignedBridgeApproachRoadOverlay | `0x30` | 1 | 801 |
| MapTile_HasAlignedBridgeApproachRoadOverlay | `6` | 1 | 802 |
| MapTile_HasAlignedBridgeApproachRoadOverlay | `0x25Bu` | 1 | 814 |
| MapTile_HasAlignedBridgeApproachRoadOverlay | `7` | 2 | 814, 815 |
| MapTile_HasAlignedBridgeApproachRoadOverlay | `0x262u` | 1 | 815 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `4` | 13 | 839, 841, 842, 843 ... |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `0x36D` | 1 | 844 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `0x3B4u` | 4 | 844, 847, 852, 857 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `6` | 4 | 845, 849, 854, 859 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `877` | 4 | 845, 849, 854, 859 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `0x36Du` | 3 | 846, 851, 856 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `0xFFFF` | 1 | 863 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `2` | 1 | 866 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `3` | 1 | 866 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `5` | 1 | 866 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `603` | 1 | 866 |
| MapTile_IsBareBridgeCrossingRoadOverlayCandidate | `610` | 1 | 866 |
| Map_GetBridgeCrossingCostOrZero | `2` | 1 | 881 |
| Map_GetBridgeCrossingCostOrZero | `0x25Bu` | 1 | 882 |
| Map_GetBridgeCrossingCostOrZero | `0x262u` | 1 | 882 |
| Map_GetBridgeCrossingCostOrZero | `7` | 2 | 882, 882 |
| Map_GetBridgeCrossingCostOrZero | `5` | 1 | 885 |
| Road_Build | `147176` | 2 | 930, 1216 |
| Road_Build | `876` | 2 | 944, 1066 |
| Road_Build | `874` | 2 | 949, 969 |
| Road_Build | `871` | 3 | 958, 979, 1018 |
| Road_Build | `868` | 2 | 974, 1002 |
| Road_Build | `869` | 3 | 986, 1007, 1046 |
| Road_Build | `870` | 2 | 997, 1061 |
| Road_Build | `873` | 2 | 1013, 1037 |
| Road_Build | `866` | 1 | 1024 |
| Road_Build | `875` | 1 | 1042 |
| Road_Build | `872` | 1 | 1051 |
| Road_Build | `867` | 1 | 1056 |
| Road_Build | `0x25Bu` | 1 | 1071 |
| Road_Build | `642` | 1 | 1074 |
| Road_Build | `2` | 3 | 1075, 1081, 1172 |
| Road_Build | `0x236u` | 2 | 1082, 1084 |
| Road_Build | `877` | 1 | 1086 |
| Road_Build | `0x240u` | 2 | 1088, 1090 |
| Road_Build | `904` | 1 | 1092 |
| Road_Build | `0x243u` | 2 | 1094, 1096 |
| Road_Build | `903` | 1 | 1098 |
| Road_Build | `581` | 1 | 1100 |
| Road_Build | `906` | 1 | 1102 |
| Road_Build | `578` | 1 | 1105 |
| Road_Build | `901` | 1 | 1107 |
| Road_Build | `0x237u` | 1 | 1110 |
| Road_Build | `879` | 1 | 1112 |
| Road_Build | `569` | 1 | 1114 |
| Road_Build | `882` | 1 | 1116 |
| Road_Build | `0x223u` | 2 | 1119, 1121 |
| Road_Build | `927` | 1 | 1123 |
| Road_Build | `0x225u` | 2 | 1125, 1127 |
| Road_Build | `930` | 1 | 1129 |
| Road_Build | `564` | 1 | 1131 |
| Road_Build | `880` | 1 | 1133 |
| Road_Build | `0x220u` | 2 | 1137, 1139 |
| Road_Build | `928` | 1 | 1141 |
| Road_Build | `546` | 1 | 1143 |
| Road_Build | `925` | 1 | 1145 |
| Road_Build | `4` | 11 | 1149, 1151, 1165, 1167 ... |
| Road_Build | `10` | 2 | 1152, 1168 |
| Road_Build | `881` | 1 | 1158 |
| Road_Build | `878` | 1 | 1162 |
| Road_Build | `145` | 1 | 1171 |
| Road_Build | `185` | 2 | 1184, 1185 |
| Road_Build | `0xFFFF` | 2 | 1194, 1199 |
| UnitStack_MoveOneTileInDirection | `147176` | 1 | 1263 |
| UnitStack_MoveOneTileInDirection | `2` | 2 | 1267, 1270 |
| Map_TileHasOwner | `0xFFFF` | 1 | 1290 |
| Map_TileHasOwner | `4` | 1 | 1290 |
| Map_AutoUpgradeVillages | `0x36Du` | 1 | 1318 |
| Map_AutoUpgradeVillages | `4` | 7 | 1318, 1319, 1320, 1321 ... |
| Map_AutoUpgradeVillages | `0x37Eu` | 1 | 1319 |
| Map_AutoUpgradeVillages | `0x385u` | 1 | 1320 |
| Map_AutoUpgradeVillages | `0x396u` | 1 | 1321 |
| Map_AutoUpgradeVillages | `0x39Du` | 1 | 1322 |
| Map_AutoUpgradeVillages | `0x3AEu` | 1 | 1323 |
| Map_AutoUpgradeVillages | `10` | 2 | 1326, 1330 |
| Map_AutoUpgradeVillages | `30` | 1 | 1326 |
| Map_AutoUpgradeVillages | `0xFFFF` | 1 | 1327 |
| Map_AutoUpgradeVillages | `6` | 1 | 1329 |
| Map_AutoUpgradeVillages | `2` | 1 | 1334 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `147176` | 5 | 1378, 1388, 1400, 1412 ... |
| RoadBuildMode_HighlightBuildableAdjacentTile | `6` | 9 | 1380, 1381, 1391, 1394 ... |
| RoadBuildMode_HighlightBuildableAdjacentTile | `57` | 2 | 1381, 1403 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `59` | 1 | 1383 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `42` | 1 | 1392 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `41` | 2 | 1394, 1420 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `2` | 2 | 1404, 1432 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `26` | 1 | 1405 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `3` | 1 | 1415 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `75` | 1 | 1419 |
| RoadBuildMode_HighlightBuildableAdjacentTile | `185` | 1 | 1434 |
| RoadBuildMode_BuildInSelectedDirection | `16` | 1 | 1471 |
| RoadBuildMode_BuildInSelectedDirection | `0x1B` | 1 | 1473 |
| RoadBuildMode_BuildInSelectedDirection | `0x1C` | 1 | 1476 |
| RoadBuildMode_BuildInSelectedDirection | `0x1D` | 1 | 1479 |
| RoadBuildMode_BuildInSelectedDirection | `0x1E` | 1 | 1482 |

### src/buildings/00425540_00426FC0_buildings_006.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Builder_StartRoadBuildMode | `147176` | 6 | 33, 58, 61, 64 ... |
| Builder_StartRoadBuildMode | `185` | 1 | 34 |
| Builder_StartRoadBuildMode | `2` | 3 | 41, 120, 120 |
| Builder_StartRoadBuildMode | `10` | 1 | 51 |
| Builder_StartRoadBuildMode | `7` | 1 | 54 |
| Builder_StartRoadBuildMode | `32` | 3 | 83, 84, 85 |
| Builder_StartRoadBuildMode | `31` | 4 | 84, 85, 91, 92 |
| Builder_StartRoadBuildMode | `6` | 6 | 84, 85, 85, 91 ... |
| Builder_StartRoadBuildMode | `16` | 3 | 90, 91, 92 |
| UnitBattle_InitPathingTables | `804` | 1 | 182 |
| UnitBattle_InitPathingTables | `800` | 1 | 188 |
| UnitBattle_InitPathingTables | `313` | 1 | 191 |
| UnitBattle_InitPathingTables | `315` | 1 | 192 |
| UnitBattle_InitPathingTables | `320` | 1 | 192 |
| UnitBattle_InitPathingTables | `322` | 1 | 193 |
| UnitBattle_InitPathingTables | `325` | 1 | 194 |
| UnitBattle_InitPathingTables | `328` | 1 | 195 |
| UnitBattle_InitPathingTables | `329` | 1 | 195 |
| UnitBattle_InitPathingTables | `338` | 1 | 196 |
| UnitBattle_InitPathingTables | `341` | 1 | 196 |
| UnitBattle_InitPathingTables | `344` | 1 | 197 |
| UnitBattle_InitPathingTables | `352` | 1 | 197 |
| UnitBattle_InitPathingTables | `356` | 1 | 198 |
| UnitBattle_InitPathingTables | `816` | 1 | 204 |
| UnitBattle_InitPathingTables | `2` | 1 | 206 |
| UnitBattle_InitPathingTables | `40` | 2 | 211, 224 |
| UnitBattle_InitPathingTables | `32` | 1 | 212 |
| UnitBattle_InitPathingTables | `22` | 1 | 221 |
| UnitBattle_GetTileMoveCostOrZero | `1534` | 1 | 233 |
| UnitBattle_GetTileMoveCostOrZero | `2` | 1 | 233 |
| UnitBattle_GetTileMoveCostOrZero | `40` | 1 | 233 |
| UnitBattle_GetTileMoveCostOrZero | `5` | 1 | 236 |
| UnitBattle_GetTileMoveCostOrZero | `20` | 1 | 237 |
| UnitBattle_GetTileMoveCostOrZero | `3134` | 1 | 237 |
| UnitBattle_GetTileMoveCostOrZero | `32` | 1 | 239 |
| UnitBattle_MoveTrack | `401` | 1 | 295 |
| UnitBattle_MoveTrack | `856` | 1 | 327 |
| UnitBattle_MoveTrack | `858` | 1 | 328 |
| UnitBattle_MoveTrack | `804` | 4 | 331, 365, 382, 499 |
| UnitBattle_MoveTrack | `800` | 4 | 332, 370, 382, 504 |
| UnitBattle_MoveTrack | `40` | 13 | 337, 340, 347, 349 ... |
| UnitBattle_MoveTrack | `20` | 13 | 338, 360, 398, 406 ... |
| UnitBattle_MoveTrack | `2` | 14 | 343, 344, 344, 350 ... |
| UnitBattle_MoveTrack | `1534` | 3 | 351, 352, 605 |
| UnitBattle_MoveTrack | `836` | 2 | 354, 606 |
| UnitBattle_MoveTrack | `840` | 2 | 355, 607 |
| UnitBattle_MoveTrack | `854` | 2 | 355, 607 |
| UnitBattle_MoveTrack | `0xFFFF` | 1 | 374 |
| UnitBattle_MoveTrack | `65534` | 2 | 374, 465 |
| UnitBattle_MoveTrack | `4` | 8 | 380, 381, 384, 384 ... |
| UnitBattle_MoveTrack | `23` | 6 | 389, 390, 391, 513 ... |
| UnitBattle_MoveTrack | `31` | 4 | 390, 391, 513, 513 |
| UnitBattle_MoveTrack | `16` | 2 | 391, 513 |
| UnitBattle_MoveTrack | `3134` | 8 | 398, 407, 418, 427 ... |
| UnitBattle_MoveTrack | `8` | 1 | 450 |
| UnitBattle_MoveTrack | `64` | 1 | 452 |
| UnitBattle_MoveTrack | `404` | 1 | 470 |
| UnitBattle_MoveTrack | `100` | 2 | 480, 591 |
| UnitBattle_MoveTrackNear | `804` | 1 | 643 |
| UnitBattle_MoveTrackNear | `800` | 1 | 644 |
| UnitBattle_MoveTrackNear | `40` | 1 | 648 |
| UnitBattle_MoveTrackNear | `20` | 1 | 649 |
| UnitBattle_MoveTrackNear | `1534` | 1 | 650 |
| UnitBattle_MoveTrackNear | `2` | 1 | 650 |
| UnitBattle_MoveTrackNear | `3134` | 1 | 651 |
| UnitBattle_MoveTrackNear | `404` | 1 | 670 |
| UnitBattle_MoveTrackNear | `100` | 2 | 680, 694 |
| UnitBattle_MoveTrackNearWall | `800` | 1 | 733 |
| UnitBattle_MoveTrackNearWall | `856` | 1 | 735 |
| UnitBattle_MoveTrackNearWall | `858` | 1 | 736 |
| UnitBattle_MoveTrackNearWall | `804` | 1 | 749 |
| UnitBattle_MoveTrackNearWall | `404` | 1 | 761 |
| UnitBattle_MoveTrackNearWall | `100` | 1 | 769 |
| UnitBattle_MoveTrackForce | `800` | 1 | 796 |
| UnitBattle_MoveTrackForce | `804` | 1 | 796 |
| UnitBattle_MoveTrackForce | `20` | 1 | 799 |
| UnitBattle_MoveTrackForce | `3134` | 1 | 799 |
| UnitBattle_MoveTrackForce | `856` | 1 | 801 |
| UnitBattle_Move | `100` | 2 | 864, 1050 |
| UnitBattle_Move | `23` | 4 | 879, 916, 1048, 1062 |
| UnitBattle_Move | `3` | 15 | 887, 928, 934, 981 ... |
| UnitBattle_Move | `2` | 19 | 888, 929, 930, 981 ... |
| UnitBattle_Move | `22` | 1 | 893 |
| UnitBattle_Move | `854` | 1 | 896 |
| UnitBattle_Move | `4112` | 1 | 898 |
| UnitBattle_Move | `27` | 1 | 903 |
| UnitBattle_Move | `30` | 1 | 903 |
| UnitBattle_Move | `17` | 1 | 904 |
| UnitBattle_Move | `7` | 2 | 904, 980 |
| UnitBattle_Move | `8` | 5 | 910, 922, 948, 1059 ... |
| UnitBattle_Move | `64` | 2 | 940, 941 |
| UnitBattle_Move | `858` | 1 | 942 |
| UnitBattle_Move | `6` | 2 | 943, 944 |
| UnitBattle_Move | `856` | 1 | 943 |
| UnitBattle_Move | `4` | 4 | 1034, 1035, 1053, 1055 |
| UnitBattle_Move | `1534` | 2 | 1039, 1042 |
| UnitBattle_Move | `40` | 2 | 1039, 1042 |
| UnitBattle_Move | `140073` | 1 | 1063 |
| UnitBattle_CenterViewOnUnit | `3` | 2 | 1112, 1113 |
| UnitBattle_CenterViewOnUnit | `808` | 5 | 1112, 1114, 1115, 1117 ... |
| UnitBattle_CenterViewOnUnit | `856` | 1 | 1112 |
| UnitBattle_CenterViewOnUnit | `812` | 5 | 1113, 1119, 1120, 1123 ... |
| UnitBattle_CenterViewOnUnit | `858` | 1 | 1113 |
| UnitBattle_CenterViewOnUnit | `804` | 1 | 1116 |
| UnitBattle_CenterViewOnUnit | `7` | 4 | 1117, 1118, 1123, 1124 |
| UnitBattle_CenterViewOnUnit | `800` | 1 | 1122 |
| UnitBattle_CountAdjacentEnemies | `4` | 1 | 1140 |
| UnitBattle_CountAdjacentEnemies | `16` | 1 | 1141 |
| UnitBattle_CountAdjacentEnemies | `2` | 2 | 1141, 1149 |
| UnitBattle_CountAdjacentEnemies | `804` | 1 | 1144 |
| UnitBattle_CountAdjacentEnemies | `6` | 1 | 1146 |
| UnitBattle_CountAdjacentEnemies | `800` | 1 | 1147 |
| UnitBattle_CountAdjacentEnemies | `1534` | 1 | 1149 |
| UnitBattle_CountAdjacentEnemies | `40` | 1 | 1149 |
| UnitBattle_CountAdjacentEnemies | `854` | 1 | 1150 |
| UnitBattle_GetTargetCrowdingScale | `2` | 1 | 1170 |
| UnitBattle_GetTargetCrowdingScale | `256` | 1 | 1171 |
| UnitBattle_GetTargetCrowdingScale | `3` | 1 | 1173 |
| UnitBattle_GetTargetCrowdingScale | `230` | 1 | 1174 |
| UnitBattle_GetTargetCrowdingScale | `4` | 1 | 1176 |
| UnitBattle_GetTargetCrowdingScale | `204` | 1 | 1177 |
| UnitBattle_GetTargetCrowdingScale | `5` | 1 | 1179 |
| UnitBattle_GetTargetCrowdingScale | `179` | 1 | 1180 |
| UnitBattle_GetTargetCrowdingScale | `128` | 1 | 1183 |
| UnitBattle_CalcMeleeExchange | `9` | 2 | 1211, 1212 |
| UnitBattle_CalcMeleeExchange | `31` | 8 | 1215, 1215, 1222, 1222 ... |
| UnitBattle_CalcMeleeExchange | `8` | 12 | 1215, 1215, 1215, 1222 ... |
| UnitBattle_CalcMeleeExchange | `1024` | 1 | 1230 |
| UnitBattle_CalcMeleeExchange | `192` | 3 | 1233, 1233, 1233 |
| UnitBattle_CalcMeleeExchange | `384` | 1 | 1234 |
| UnitBattle_CalcMeleeExchange | `512` | 1 | 1236 |
| UnitBattle_CalcMeleeExchange | `640` | 1 | 1238 |
| UnitBattle_CalcMeleeExchange | `768` | 1 | 1240 |
| UnitBattle_CalcMeleeExchange | `15` | 1 | 1241 |
| UnitBattle_CalcMeleeExchange | `12` | 1 | 1243 |
| UnitBattle_CalcMeleeExchange | `10` | 1 | 1247 |
| UnitBattle_CalcMeleeExchange | `7` | 1 | 1252 |
| UnitBattle_CalcMeleeExchange | `5` | 1 | 1257 |
| UnitBattle_CalcMeleeExchange | `100` | 2 | 1261, 1262 |

### src/buildings/004272A0_00428850_buildings_007.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_PlayAttackAnimation | `100` | 1 | 110 |
| UnitBattle_PlayAttackAnimation | `2` | 37 | 129, 130, 136, 136 ... |
| UnitBattle_PlayAttackAnimation | `3` | 38 | 129, 130, 136, 136 ... |
| UnitBattle_PlayAttackAnimation | `4112` | 4 | 139, 147, 359, 439 |
| UnitBattle_PlayAttackAnimation | `8` | 6 | 161, 187, 237, 243 ... |
| UnitBattle_PlayAttackAnimation | `7` | 4 | 273, 407, 419, 457 |
| UnitBattle_PlayAttackAnimation | `27` | 2 | 298, 461 |
| UnitBattle_PlayAttackAnimation | `30` | 2 | 298, 461 |
| UnitBattle_PlayAttackAnimation | `3u` | 2 | 315, 478 |
| UnitBattle_PlayAttackAnimation | `5u` | 2 | 321, 484 |
| UnitBattle_PlayAttackAnimation | `7u` | 2 | 324, 487 |
| UnitBattle_PlayDeathAnimation | `2` | 11 | 621, 621, 624, 627 ... |
| UnitBattle_PlayDeathAnimation | `2334` | 4 | 621, 631, 664, 666 |
| UnitBattle_PlayDeathAnimation | `3` | 5 | 621, 627, 630, 664 ... |
| UnitBattle_PlayDeathAnimation | `40` | 6 | 621, 627, 630, 663 ... |
| UnitBattle_PlayDeathAnimation | `48` | 1 | 621 |
| UnitBattle_PlayDeathAnimation | `255` | 4 | 622, 622, 670, 670 |
| UnitBattle_PlayDeathAnimation | `4` | 1 | 622 |
| UnitBattle_PlayDeathAnimation | `2335` | 2 | 627, 697 |
| UnitBattle_PlayDeathAnimation | `56` | 1 | 631 |
| UnitBattle_PlayDeathAnimation | `10` | 1 | 633 |
| UnitBattle_PlayDeathAnimation | `855` | 4 | 644, 647, 678, 681 |
| UnitBattle_PlayDeathAnimation | `856` | 3 | 645, 679, 705 |
| UnitBattle_PlayDeathAnimation | `858` | 3 | 646, 680, 704 |
| UnitBattle_PlayDeathAnimation | `8` | 1 | 670 |
| UnitBattle_PlayDeathAnimation | `1534` | 1 | 705 |
| UnitBattle_GetCorpseSpriteIndex | `3` | 1 | 722 |
| UnitBattle_GetCorpseSpriteIndex | `4` | 1 | 722 |
| UnitBattle_GetCorpseSpriteIndex | `8` | 1 | 722 |
| UnitBattle_Attack | `2` | 20 | 764, 764, 774, 799 ... |
| UnitBattle_Attack | `3` | 14 | 767, 767, 775, 799 ... |
| UnitBattle_Attack | `5` | 2 | 780, 796 |
| UnitBattle_Attack | `8` | 3 | 780, 794, 796 |
| UnitBattle_Attack | `23` | 4 | 785, 787, 789, 790 |
| UnitBattle_Attack | `5u` | 1 | 794 |
| UnitBattle_Attack | `0xFEu` | 1 | 797 |
| UnitBattle_Attack | `22` | 1 | 797 |
| UnitBattle_Attack | `9` | 6 | 806, 807, 819, 825 ... |
| UnitBattle_Attack | `2334` | 2 | 822, 828 |
| UnitBattle_Attack | `40` | 6 | 822, 823, 828, 829 ... |
| UnitBattle_Attack | `2335` | 2 | 823, 829 |
| UnitBattle_Attack | `1534` | 2 | 837, 844 |
| UnitBattle_Attack | `140051` | 1 | 845 |
| UnitBattle_Attack | `140073` | 1 | 848 |
| UnitBattle_IsTileWithinRange | `4` | 2 | 888, 889 |
| UnitBattle_IsTileWithinRange | `6` | 2 | 890, 891 |
| UnitBattle_IsUnitWithinRange | `856` | 1 | 903 |
| UnitBattle_IsUnitWithinRange | `858` | 1 | 904 |

### src/buildings/00428880_0042A890_buildings_008.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_PlayShotAnimation | `384` | 1 | 129 |
| UnitBattle_PlayShotAnimation | `44` | 1 | 130 |
| UnitBattle_PlayShotAnimation | `56` | 1 | 131 |
| UnitBattle_PlayShotAnimation | `74` | 1 | 132 |
| UnitBattle_PlayShotAnimation | `2` | 31 | 165, 167, 167, 168 ... |
| UnitBattle_PlayShotAnimation | `3` | 15 | 165, 167, 168, 168 ... |
| UnitBattle_PlayShotAnimation | `808` | 7 | 167, 169, 170, 172 ... |
| UnitBattle_PlayShotAnimation | `812` | 7 | 168, 174, 175, 177 ... |
| UnitBattle_PlayShotAnimation | `804` | 1 | 171 |
| UnitBattle_PlayShotAnimation | `7` | 9 | 172, 173, 177, 178 ... |
| UnitBattle_PlayShotAnimation | `800` | 1 | 176 |
| UnitBattle_PlayShotAnimation | `4112` | 6 | 184, 198, 208, 483 ... |
| UnitBattle_PlayShotAnimation | `32` | 3 | 219, 220, 335 |
| UnitBattle_PlayShotAnimation | `6` | 19 | 221, 234, 235, 243 ... |
| UnitBattle_PlayShotAnimation | `0xFu` | 2 | 224, 226 |
| UnitBattle_PlayShotAnimation | `26` | 1 | 228 |
| UnitBattle_PlayShotAnimation | `5` | 9 | 230, 232, 276, 283 ... |
| UnitBattle_PlayShotAnimation | `256` | 1 | 231 |
| UnitBattle_PlayShotAnimation | `8` | 13 | 231, 242, 245, 252 ... |
| UnitBattle_PlayShotAnimation | `10` | 8 | 235, 244, 254, 263 ... |
| UnitBattle_PlayShotAnimation | `0x1Cu` | 2 | 237, 239 |
| UnitBattle_PlayShotAnimation | `192` | 1 | 246 |
| UnitBattle_PlayShotAnimation | `196` | 1 | 247 |
| UnitBattle_PlayShotAnimation | `30` | 1 | 249 |
| UnitBattle_PlayShotAnimation | `4` | 6 | 257, 280, 377, 378 ... |
| UnitBattle_PlayShotAnimation | `20` | 1 | 260 |
| UnitBattle_PlayShotAnimation | `320` | 1 | 265 |
| UnitBattle_PlayShotAnimation | `0xAu` | 3 | 272, 274, 384 |
| UnitBattle_PlayShotAnimation | `128` | 1 | 279 |
| UnitBattle_PlayShotAnimation | `12` | 1 | 285 |
| UnitBattle_PlayShotAnimation | `9` | 1 | 295 |
| UnitBattle_PlayShotAnimation | `64` | 2 | 300, 340 |
| UnitBattle_PlayShotAnimation | `856` | 3 | 323, 367, 470 |
| UnitBattle_PlayShotAnimation | `858` | 3 | 323, 367, 470 |
| UnitBattle_PlayShotAnimation | `16` | 3 | 338, 398, 399 |
| UnitBattle_PlayShotAnimation | `48` | 1 | 341 |
| UnitBattle_PlayShotAnimation | `464` | 2 | 396, 397 |
| UnitBattle_PlayShotAnimation | `46` | 1 | 456 |
| UnitBattle_PlayShotAnimation | `52` | 1 | 456 |
| UnitBattle_PlayShotAnimation | `24` | 1 | 490 |
| UnitBattle_PlayShotAnimation | `17` | 4 | 519, 521, 522, 523 |
| UnitBattle_PlayShotAnimation | `0xF8` | 1 | 521 |
| UnitBattle_CalcShotTargetHealthAfterHit | `2` | 4 | 648, 649, 657, 661 |
| UnitBattle_CalcShotTargetHealthAfterHit | `4` | 3 | 648, 649, 664 |
| UnitBattle_CalcShotTargetHealthAfterHit | `3` | 3 | 650, 651, 659 |
| UnitBattle_CalcShotTargetHealthAfterHit | `6` | 2 | 650, 651 |
| UnitBattle_CalcShotTargetHealthAfterHit | `31` | 2 | 654, 654 |
| UnitBattle_CalcShotTargetHealthAfterHit | `8` | 3 | 654, 654, 654 |
| UnitBattle_CalcShotTargetHealthAfterHit | `861` | 1 | 666 |
| UnitBattle_Shot | `5u` | 1 | 693 |
| UnitBattle_Shot | `8` | 2 | 693, 695 |
| UnitBattle_Shot | `5` | 1 | 695 |
| UnitBattle_Shot | `9` | 3 | 700, 706, 718 |
| UnitBattle_Shot | `6` | 2 | 704, 721 |
| UnitBattle_Shot | `4` | 2 | 705, 720 |
| UnitBattle_Shot | `2` | 3 | 722, 725, 727 |
| UnitBattle_Shot | `2334` | 1 | 722 |
| UnitBattle_Shot | `40` | 2 | 722, 725 |
| UnitBattle_Shot | `1534` | 1 | 725 |
| UnitBattle_Shot | `140073` | 1 | 727 |
| UnitBattle_AttackWall | `20` | 2 | 759, 814 |
| UnitBattle_AttackWall | `3134` | 7 | 759, 815, 820, 821 ... |
| UnitBattle_AttackWall | `4` | 5 | 764, 766, 787, 789 ... |
| UnitBattle_AttackWall | `6` | 5 | 769, 771, 792, 794 ... |
| UnitBattle_AttackWall | `23` | 3 | 778, 780, 784 |
| UnitBattle_AttackWall | `8` | 2 | 797, 839 |
| UnitBattle_AttackWall | `5u` | 1 | 798 |
| UnitBattle_AttackWall | `5` | 1 | 800 |
| UnitBattle_AttackWall | `820` | 1 | 816 |
| UnitBattle_AttackWall | `2` | 2 | 817, 853 |
| UnitBattle_AttackWall | `256` | 1 | 819 |
| UnitBattle_AttackWall | `828` | 2 | 826, 846 |
| UnitBattle_AttackWall | `832` | 2 | 827, 847 |
| UnitBattle_AttackWall | `64` | 1 | 851 |
| UnitBattle_AttackWall | `140073` | 1 | 853 |
| UnitBattle_ShotWall | `5u` | 1 | 891 |
| UnitBattle_ShotWall | `8` | 3 | 891, 893, 913 |
| UnitBattle_ShotWall | `5` | 1 | 893 |
| UnitBattle_ShotWall | `4` | 3 | 900, 902, 907 |
| UnitBattle_ShotWall | `6` | 2 | 903, 905 |
| UnitBattle_ShotWall | `10` | 2 | 908, 910 |
| UnitBattle_ShotWall | `9` | 2 | 908, 910 |
| UnitBattle_ShotWall | `3` | 1 | 909 |
| UnitBattle_ShotWall | `40` | 1 | 911 |
| UnitBattle_ShotWall | `2` | 2 | 912, 925 |
| UnitBattle_ShotWall | `820` | 1 | 912 |
| UnitBattle_ShotWall | `3134` | 3 | 913, 914, 917 |
| UnitBattle_ShotWall | `828` | 1 | 918 |
| UnitBattle_ShotWall | `832` | 1 | 919 |
| UnitBattle_ShotWall | `64` | 1 | 923 |
| UnitBattle_ShotWall | `140073` | 1 | 925 |
| UnitBattle_Defence | `5u` | 1 | 938 |
| UnitBattle_Defence | `860` | 2 | 938, 940 |
| UnitBattle_Defence | `874` | 1 | 941 |
| BuildCursor_DrawPlacementOverlay | `32` | 1 | 976 |
| BuildCursor_DrawPlacementOverlay | `6` | 2 | 976, 977 |
| BuildCursor_DrawPlacementOverlay | `16` | 1 | 977 |
| BuildCursor_DrawPlacementOverlay | `215` | 1 | 979 |
| BuildCursor_DrawPlacementOverlay | `76` | 1 | 981 |
| BuildCursor_DrawPlacementOverlay | `3` | 1 | 982 |
| BuildCursor_DrawPlacementOverlay | `147176` | 1 | 991 |
| BuildCursor_DrawPlacementOverlay | `24` | 1 | 994 |
| BuildCursor_DrawPlacementOverlay | `46` | 10 | 994, 1012, 1017, 1031 ... |
| BuildCursor_DrawPlacementOverlay | `63` | 12 | 995, 997, 1013, 1020 ... |
| BuildCursor_DrawPlacementOverlay | `20` | 8 | 1012, 1017, 1031, 1036 ... |
| BuildCursor_DrawPlacementOverlay | `8` | 1 | 1085 |
| BuildCursor_DrawPlacementOverlay | `52` | 1 | 1086 |
| BuildCursor_EnsureWidgetTable | `0x03` | 6 | 1113, 1117, 1120, 1123 ... |
| BuildCursor_EnsureWidgetTable | `0x0c` | 6 | 1113, 1117, 1120, 1123 ... |
| BuildCursor_EnsureWidgetTable | `0x52` | 6 | 1113, 1117, 1120, 1123 ... |
| BuildCursor_EnsureWidgetTable | `0x90` | 3 | 1113, 1116, 1129 |
| BuildCursor_EnsureWidgetTable | `0xa0` | 2 | 1113, 1119 |
| BuildCursor_EnsureWidgetTable | `0x0e` | 7 | 1114, 1117, 1118, 1121 ... |
| BuildCursor_EnsureWidgetTable | `0x0f` | 1 | 1114 |
| BuildCursor_EnsureWidgetTable | `0x10` | 1 | 1114 |
| BuildCursor_EnsureWidgetTable | `0x41` | 7 | 1114, 1118, 1121, 1122 ... |
| BuildCursor_EnsureWidgetTable | `0x91` | 6 | 1114, 1118, 1121, 1124 ... |
| BuildCursor_EnsureWidgetTable | `0xf0` | 6 | 1114, 1118, 1121, 1124 ... |
| BuildCursor_EnsureWidgetTable | `0x04` | 1 | 1115 |
| BuildCursor_EnsureWidgetTable | `0x42` | 6 | 1115, 1118, 1121, 1125 ... |
| BuildCursor_EnsureWidgetTable | `0x4e` | 18 | 1115, 1115, 1116, 1118 ... |
| BuildCursor_EnsureWidgetTable | `0x9e` | 6 | 1115, 1118, 1121, 1125 ... |
| BuildCursor_EnsureWidgetTable | `0xb0` | 9 | 1115, 1118, 1119, 1121 ... |
| BuildCursor_EnsureWidgetTable | `0xed` | 1 | 1115 |
| BuildCursor_EnsureWidgetTable | `0xee` | 17 | 1115, 1116, 1118, 1118 ... |
| BuildCursor_EnsureWidgetTable | `0xfe` | 1 | 1115 |
| BuildCursor_EnsureWidgetTable | `0x02` | 2 | 1116, 1126 |
| BuildCursor_EnsureWidgetTable | `0x09` | 1 | 1116 |
| BuildCursor_EnsureWidgetTable | `0x20` | 3 | 1116, 1121, 1126 |
| BuildCursor_EnsureWidgetTable | `0x11` | 1 | 1117 |
| BuildCursor_EnsureWidgetTable | `0x12` | 1 | 1117 |
| BuildCursor_EnsureWidgetTable | `0x16` | 2 | 1118, 1120 |
| BuildCursor_EnsureWidgetTable | `0x1b` | 1 | 1119 |
| BuildCursor_EnsureWidgetTable | `0x15` | 1 | 1120 |
| BuildCursor_EnsureWidgetTable | `0x30` | 1 | 1122 |
| BuildCursor_EnsureWidgetTable | `0xe0` | 2 | 1122, 1129 |
| BuildCursor_EnsureWidgetTable | `0x17` | 1 | 1123 |
| BuildCursor_EnsureWidgetTable | `0x18` | 1 | 1124 |
| BuildCursor_EnsureWidgetTable | `0x46` | 1 | 1125 |
| BuildCursor_EnsureWidgetTable | `0x4c` | 1 | 1125 |
| BuildCursor_EnsureWidgetTable | `0x51` | 1 | 1126 |
| BuildCursor_EnsureWidgetTable | `0x19` | 1 | 1127 |
| BuildCursor_EnsureWidgetTable | `0x1a` | 1 | 1127 |
| BuildCursor_EnsureWidgetTable | `0x56` | 1 | 1128 |
| BuildCursor_EnsureWidgetTable | `0x5f` | 1 | 1128 |
| BuildCursor_EnsureWidgetTable | `0x68` | 1 | 1129 |
| BuildCursor_EnsureWidgetTable | `0x13` | 1 | 1130 |
| BuildCursor_EnsureWidgetTable | `0x14` | 1 | 1130 |
| BuildCursor_EnsureWidgetTable | `0x6d` | 1 | 1131 |
| BuildCursor_EnsureWidgetTable | `0x73` | 1 | 1132 |
| BuildCursor_EnsureWidgetTable | `0x7a` | 1 | 1132 |
| BuildCursor_EnsureWidgetTable | `0xff` | 4 | 1132, 1132, 1133, 1133 |
| BuildCursor_EnsureWidgetTable | `12` | 1 | 1159 |
| BuildCursor_EnsureWidgetTable | `28` | 1 | 1161 |
| BuildCursor_EnsureWidgetTable | `32` | 1 | 1163 |
| BuildCursor_EnsureWidgetTable | `36` | 1 | 1165 |
| BuildCursor_EnsureWidgetTable | `40` | 1 | 1167 |
| BuildCursor_EnsureWidgetTable | `49` | 1 | 1169 |
| BuildCursor_EnsureWidgetTable | `65` | 1 | 1171 |
| BuildCursor_EnsureWidgetTable | `81` | 1 | 1173 |
| BuildCursor_EnsureWidgetTable | `85` | 1 | 1175 |
| BuildCursor_EnsureWidgetTable | `89` | 1 | 1177 |
| BuildCursor_EnsureWidgetTable | `93` | 1 | 1179 |
| BuildCursor_EnsureWidgetTable | `102` | 1 | 1181 |
| BuildCursor_EnsureWidgetTable | `118` | 1 | 1183 |
| BuildCursor_EnsureWidgetTable | `134` | 1 | 1185 |
| BuildCursor_EnsureWidgetTable | `138` | 1 | 1187 |
| BuildCursor_EnsureWidgetTable | `142` | 1 | 1189 |
| BuildCursor_EnsureWidgetTable | `146` | 1 | 1191 |
| BuildCursor_EnsureWidgetTable | `155` | 1 | 1193 |
| BuildCursor_EnsureWidgetTable | `171` | 1 | 1195 |
| BuildCursor_EnsureWidgetTable | `187` | 1 | 1197 |
| BuildCursor_EnsureWidgetTable | `191` | 1 | 1199 |
| BuildCursor_EnsureWidgetTable | `195` | 1 | 1201 |
| BuildCursor_EnsureWidgetTable | `199` | 1 | 1203 |
| BuildCursor_EnsureWidgetTable | `208` | 1 | 1205 |
| BuildCursor_EnsureWidgetTable | `224` | 1 | 1207 |
| BuildCursor_EnsureWidgetTable | `240` | 1 | 1209 |
| BuildCursor_EnsureWidgetTable | `244` | 1 | 1211 |
| BuildCursor_EnsureWidgetTable | `248` | 1 | 1213 |
| BuildCursor_EnsureWidgetTable | `252` | 1 | 1215 |
| BuildCursor_EnsureWidgetTable | `261` | 1 | 1217 |
| BuildCursor_EnsureWidgetTable | `277` | 1 | 1219 |
| BuildCursor_EnsureWidgetTable | `293` | 1 | 1221 |
| BuildCursor_EnsureWidgetTable | `297` | 1 | 1223 |
| BuildCursor_EnsureWidgetTable | `301` | 1 | 1225 |
| BuildCursor_EnsureWidgetTable | `305` | 1 | 1227 |
| BuildCursor_EnsureWidgetTable | `314` | 1 | 1229 |
| BuildBuilding | `9` | 1 | 1252 |
| BuildBuilding | `2` | 7 | 1257, 1261, 1306, 1315 ... |
| BuildBuilding | `31` | 10 | 1266, 1266, 1270, 1271 ... |
| BuildBuilding | `32` | 6 | 1266, 1266, 1266, 1284 ... |
| BuildBuilding | `6` | 15 | 1266, 1266, 1266, 1270 ... |
| BuildBuilding | `16` | 9 | 1269, 1270, 1271, 1292 ... |
| BuildBuilding | `3` | 4 | 1324, 1333, 1333, 1334 |
| BuildBuilding | `3u` | 2 | 1329, 1333 |
| BuildBuilding | `64` | 1 | 1350 |
| UI_DrawNoticeBoxSmall | `0x104u` | 1 | 1397 |
| UI_DrawNoticeBoxSmall | `0xC6u` | 1 | 1397 |
| UI_DrawNoticeBoxSmall | `0xD0u` | 1 | 1397 |
| UI_DrawNoticeBoxSmall | `0xDAu` | 1 | 1397 |
| UI_DrawNoticeBoxSmall | `198` | 2 | 1397, 1400 |
| UI_DrawNoticeBoxSmall | `208` | 3 | 1397, 1400, 1400 |
| UI_DrawNoticeBoxSmall | `5` | 2 | 1398, 1412 |
| UI_DrawNoticeBoxSmall | `0x3F` | 1 | 1399 |
| UI_DrawNoticeBoxSmall | `436` | 1 | 1399 |
| UI_DrawNoticeBoxSmall | `10` | 2 | 1400, 1400 |
| UI_DrawNoticeBoxSmall | `260` | 1 | 1400 |
| UI_DrawNoticeBoxSmall | `3` | 2 | 1400, 1408 |
| UI_DrawNoticeBoxSmall | `16` | 2 | 1401, 1404 |
| UI_DrawNoticeBoxSmall | `4` | 3 | 1401, 1404, 1406 |
| UI_DrawNoticeBoxSmall | `432` | 2 | 1401, 1404 |
| UI_DrawNoticeBoxSmall | `435` | 2 | 1402, 1405 |
| UI_DrawNoticeBoxSmall | `7` | 2 | 1402, 1405 |
| UI_DrawNoticeBoxSmall | `19` | 1 | 1415 |
| UI_DrawNoticeBoxSmall | `383` | 1 | 1415 |
| UI_DrawConfirmTop | `5` | 1 | 1430 |
| UI_DrawConfirmTop | `0x168u` | 1 | 1432 |
| UI_DrawConfirmTop | `0x17Cu` | 1 | 1432 |
| UI_DrawConfirmTop | `0x224u` | 1 | 1432 |
| UI_DrawConfirmTop | `0x259u` | 1 | 1432 |
| UI_DrawConfirmTop | `360` | 2 | 1432, 1433 |
| UI_DrawConfirmTop | `548` | 3 | 1432, 1433, 1433 |
| UI_DrawConfirmTop | `3` | 1 | 1433 |
| UI_DrawConfirmTop | `601` | 1 | 1433 |

### src/buildings/0042A910_0042C4E0_buildings_009.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UI_DrawConfirmBottom | `5` | 1 | 30 |
| UI_DrawConfirmBottom | `0x110u` | 1 | 32 |
| UI_DrawConfirmBottom | `0x124u` | 1 | 32 |
| UI_DrawConfirmBottom | `0x224u` | 1 | 32 |
| UI_DrawConfirmBottom | `0x259u` | 1 | 32 |
| UI_DrawConfirmBottom | `272` | 2 | 32, 33 |
| UI_DrawConfirmBottom | `548` | 3 | 32, 33, 33 |
| UI_DrawConfirmBottom | `3` | 1 | 33 |
| UI_DrawConfirmBottom | `601` | 1 | 33 |
| BuildingEconomyDialog_InitWidget | `4` | 1 | 57 |
| BuildingEconomyDialog_InitWidget | `8` | 1 | 58 |
| BuildingEconomyDialog_InitWidget | `12` | 1 | 59 |
| BuildingEconomyDialog_InitWidget | `16` | 1 | 60 |
| BuildingEconomyDialog_InitWidget | `20` | 1 | 61 |
| BuildingEconomyDialog_InitWidget | `24` | 1 | 62 |
| BuildingEconomyDialog_InitWidget | `28` | 1 | 63 |
| BuildingEconomyDialog_InitWidget | `32` | 1 | 64 |
| BuildingEconomyDialog_InitWidget | `36` | 1 | 65 |
| BuildingEconomyDialog_InitWidget | `40` | 1 | 66 |
| BuildingEconomyDialog_InitWidget | `44` | 1 | 67 |
| BuildingEconomyDialog_InitWidget | `48` | 1 | 68 |
| BuildingEconomyDialog_InitWidget | `49` | 1 | 69 |
| BuildingEconomyDialog_EnsureWidgets | `174` | 2 | 89, 102 |
| BuildingEconomyDialog_EnsureWidgets | `173` | 1 | 90 |
| BuildingEconomyDialog_EnsureWidgets | `6` | 2 | 91, 166 |
| BuildingEconomyDialog_EnsureWidgets | `7` | 2 | 92, 179 |
| BuildingEconomyDialog_EnsureWidgets | `206` | 1 | 103 |
| BuildingEconomyDialog_EnsureWidgets | `8` | 2 | 104, 192 |
| BuildingEconomyDialog_EnsureWidgets | `9` | 2 | 105, 205 |
| BuildingEconomyDialog_EnsureWidgets | `2` | 3 | 114, 202, 215 |
| BuildingEconomyDialog_EnsureWidgets | `459` | 2 | 115, 128 |
| BuildingEconomyDialog_EnsureWidgets | `270` | 1 | 116 |
| BuildingEconomyDialog_EnsureWidgets | `10` | 1 | 117 |
| BuildingEconomyDialog_EnsureWidgets | `11` | 1 | 118 |
| BuildingEconomyDialog_EnsureWidgets | `3` | 1 | 127 |
| BuildingEconomyDialog_EnsureWidgets | `323` | 1 | 129 |
| BuildingEconomyDialog_EnsureWidgets | `12` | 1 | 130 |
| BuildingEconomyDialog_EnsureWidgets | `13` | 1 | 131 |
| BuildingEconomyDialog_EnsureWidgets | `4` | 1 | 140 |
| BuildingEconomyDialog_EnsureWidgets | `513` | 4 | 141, 154, 167, 180 |
| BuildingEconomyDialog_EnsureWidgets | `331` | 1 | 142 |
| BuildingEconomyDialog_EnsureWidgets | `18` | 1 | 143 |
| BuildingEconomyDialog_EnsureWidgets | `19` | 1 | 144 |
| BuildingEconomyDialog_EnsureWidgets | `5` | 1 | 153 |
| BuildingEconomyDialog_EnsureWidgets | `365` | 1 | 155 |
| BuildingEconomyDialog_EnsureWidgets | `20` | 1 | 156 |
| BuildingEconomyDialog_EnsureWidgets | `21` | 1 | 157 |
| BuildingEconomyDialog_EnsureWidgets | `247` | 1 | 168 |
| BuildingEconomyDialog_EnsureWidgets | `14` | 1 | 169 |
| BuildingEconomyDialog_EnsureWidgets | `15` | 1 | 170 |
| BuildingEconomyDialog_EnsureWidgets | `281` | 1 | 181 |
| BuildingEconomyDialog_EnsureWidgets | `16` | 1 | 182 |
| BuildingEconomyDialog_EnsureWidgets | `17` | 1 | 183 |
| BuildingEconomyDialog_EnsureWidgets | `42` | 1 | 193 |
| BuildingEconomyDialog_EnsureWidgets | `426` | 2 | 194, 207 |
| BuildingEconomyDialog_EnsureWidgets | `22` | 1 | 195 |
| BuildingEconomyDialog_EnsureWidgets | `23` | 1 | 196 |
| BuildingEconomyDialog_EnsureWidgets | `505` | 1 | 206 |
| BuildingEconomyDialog_EnsureWidgets | `24` | 1 | 208 |
| BuildingEconomyDialog_EnsureWidgets | `25` | 1 | 209 |
| BuildingEconomyDialog_CommitTransfers | `2` | 4 | 250, 253, 268, 284 |
| BuildingEconomyDialog_CommitTransfers | `509678` | 1 | 250 |
| BuildingEconomyDialog_CommitTransfers | `45` | 2 | 255, 270 |
| BuildingEconomyDialog_CommitTransfers | `0x14u` | 1 | 282 |
| BuildingEconomyDialog_CommitTransfers | `0x17Cu` | 1 | 282 |
| BuildingEconomyDialog_CommitTransfers | `0x41u` | 1 | 282 |
| BuildingEconomyDialog_CommitTransfers | `0xC8u` | 1 | 282 |
| BuildingEconomyDialog_CommitTransfers | `20` | 2 | 282, 284 |
| BuildingEconomyDialog_CommitTransfers | `200` | 1 | 282 |
| BuildingEconomyDialog_CommitTransfers | `16` | 1 | 283 |
| BuildingEconomyDialog_CommitTransfers | `370` | 1 | 284 |
| BuildingEconomyDialog_CommitTransfers | `0x1Eu` | 1 | 286 |
| BuildingEconomyDialog_CommitTransfers | `0x221u` | 1 | 286 |
| BuildingEconomyDialog_CommitTransfers | `0x25Au` | 1 | 286 |
| BuildingEconomyDialog_CommitTransfers | `0x32u` | 1 | 286 |
| BuildingEconomyDialog_CommitTransfers | `30` | 2 | 286, 288 |
| BuildingEconomyDialog_CommitTransfers | `545` | 2 | 286, 288 |
| BuildingEconomyDialog_CommitTransfers | `5` | 1 | 287 |
| BuildingEconomyDialog_CommitTransfers | `3` | 1 | 288 |
| BuildingEconomyDialog_CommitTransfers | `602` | 1 | 288 |
| BuildingEconomyDialog_DecreaseTaxRate | `436` | 8 | 326, 329, 330, 331 ... |
| BuildingEconomyDialog_DecreaseTaxRate | `0x3F` | 5 | 327, 331, 331, 333 ... |
| BuildingEconomyDialog_DecreaseTaxRate | `0xC0` | 2 | 329, 344 |
| BuildingEconomyDialog_DecreaseTaxRate | `0x15Eu` | 1 | 339 |
| BuildingEconomyDialog_IncreaseTaxRate | `0x3F` | 4 | 389, 389, 393, 405 |
| BuildingEconomyDialog_IncreaseTaxRate | `436` | 8 | 389, 390, 391, 392 ... |
| BuildingEconomyDialog_IncreaseTaxRate | `0xC0` | 2 | 390, 403 |
| BuildingEconomyDialog_IncreaseTaxRate | `0x15Eu` | 2 | 399, 406 |
| BuildingEconomyDialog_IncreaseTaxRate | `40` | 2 | 400, 401 |
| BuildingTransferDialog_DecreasePeasantTransferAmount | `10` | 2 | 442, 449 |
| BuildingTransferDialog_DecreasePeasantTransferAmount | `0x32u` | 1 | 449 |
| BuildingTransferDialog_DecreasePeasantTransferAmount | `0xA` | 1 | 449 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `10` | 2 | 489, 496 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `0x32u` | 1 | 496 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `0xA` | 1 | 496 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `1000` | 2 | 497, 498 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `430` | 1 | 499 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `0xFu` | 1 | 500 |
| BuildingTransferDialog_IncreasePeasantTransferAmount | `0xAu` | 1 | 503 |
| BuildingTransferDialog_DecreaseGoldTransferAmount | `10` | 2 | 540, 547 |
| BuildingTransferDialog_DecreaseGoldTransferAmount | `0x32u` | 1 | 547 |
| BuildingTransferDialog_DecreaseGoldTransferAmount | `0xA` | 1 | 547 |
| BuildingTransferDialog_IncreaseGoldTransferAmount | `10` | 2 | 587, 594 |
| BuildingTransferDialog_IncreaseGoldTransferAmount | `0x32u` | 1 | 594 |
| BuildingTransferDialog_IncreaseGoldTransferAmount | `0xA` | 1 | 594 |
| BuildingTransferDialog_IncreaseGoldTransferAmount | `1000` | 2 | 595, 596 |
| BuildingTransferDialog_IncreaseGoldTransferAmount | `438` | 2 | 597, 599 |
| BuildingEconomyDialog_Run | `2` | 4 | 638, 640, 678, 684 |
| BuildingEconomyDialog_Run | `0x400u` | 1 | 645 |
| BuildingEconomyDialog_Run | `4112` | 1 | 655 |
| BuildingEconomyDialog_Run | `149` | 1 | 670 |
| BuildingEconomyDialog_Run | `267` | 3 | 670, 678, 678 |
| BuildingEconomyDialog_Run | `5` | 3 | 673, 675, 693 |
| BuildingEconomyDialog_Run | `9` | 1 | 676 |
| BuildingEconomyDialog_Run | `16` | 2 | 677, 683 |
| BuildingEconomyDialog_Run | `343` | 1 | 678 |
| BuildingEconomyDialog_Run | `434` | 1 | 678 |
| BuildingEconomyDialog_Run | `90` | 1 | 678 |
| BuildingEconomyDialog_Run | `198` | 1 | 679 |
| BuildingEconomyDialog_Run | `3` | 2 | 679, 694 |
| BuildingEconomyDialog_Run | `442` | 1 | 679 |
| BuildingEconomyDialog_Run | `444` | 2 | 679, 679 |
| BuildingEconomyDialog_Run | `503` | 1 | 679 |
| BuildingEconomyDialog_Run | `0x14u` | 1 | 682 |
| BuildingEconomyDialog_Run | `0x17Cu` | 1 | 682 |
| BuildingEconomyDialog_Run | `0x41u` | 1 | 682 |
| BuildingEconomyDialog_Run | `0xC8u` | 1 | 682 |
| BuildingEconomyDialog_Run | `20` | 4 | 682, 684, 695, 726 |
| BuildingEconomyDialog_Run | `200` | 1 | 682 |
| BuildingEconomyDialog_Run | `370` | 1 | 684 |
| BuildingEconomyDialog_Run | `430` | 1 | 684 |
| BuildingEconomyDialog_Run | `184` | 1 | 687 |
| BuildingEconomyDialog_Run | `279` | 1 | 687 |
| BuildingEconomyDialog_Run | `0x1Eu` | 1 | 692 |
| BuildingEconomyDialog_Run | `0x221u` | 1 | 692 |
| BuildingEconomyDialog_Run | `0x25Au` | 1 | 692 |
| BuildingEconomyDialog_Run | `0x32u` | 1 | 692 |
| BuildingEconomyDialog_Run | `30` | 2 | 692, 694 |
| BuildingEconomyDialog_Run | `545` | 3 | 692, 694, 694 |
| BuildingEconomyDialog_Run | `438` | 1 | 694 |
| BuildingEconomyDialog_Run | `602` | 1 | 694 |
| Trap_CanPlaceAtTile | `185` | 1 | 756 |
| Trap_CanPlaceAtTile | `39` | 1 | 757 |
| Trap_CanPlaceAtTile | `204` | 1 | 758 |
| Trap_CanPlaceAtTile | `202` | 1 | 759 |
| Trap_CanPlaceAtTile | `147` | 1 | 760 |
| Trap_CanPlaceAtTile | `2` | 1 | 762 |
| Trap_CanPlaceAtTile | `0xFFFF` | 1 | 763 |
| Trap_New | `147176` | 2 | 806, 808 |
| Trap_New | `100` | 1 | 812 |
| Trap_New | `147178` | 1 | 813 |
| Trap_New | `147180` | 1 | 828 |
| Trap_HurtStack | `3` | 1 | 871 |
| Trap_HurtStack | `270` | 1 | 879 |
| Trap_HurtStack | `340` | 1 | 879 |
| Trap_HurtStack | `9` | 3 | 880, 884, 886 |
| Trap_HurtStack | `23` | 1 | 890 |
| Trap_HurtStack | `10` | 1 | 892 |
| Trap_TriggerAtStackTile | `3` | 1 | 936 |
| Trap_TriggerAtStackTile | `100` | 3 | 941, 969, 973 |
| Trap_TriggerAtStackTile | `4` | 1 | 958 |
| Trap_TriggerAtStackTile | `147176` | 5 | 973, 974, 979, 994 ... |
| Trap_TriggerAtStackTile | `147178` | 1 | 976 |
| Trap_TriggerAtStackTile | `140059` | 1 | 977 |
| Trap_TriggerAtStackTile | `200` | 1 | 982 |
| Trap_ShowPitfallDiscoveryDialog | `3` | 6 | 1036, 1095, 1096, 1101 ... |
| Trap_ShowPitfallDiscoveryDialog | `4112` | 1 | 1054 |
| Trap_ShowPitfallDiscoveryDialog | `2` | 7 | 1058, 1059, 1072, 1089 ... |
| Trap_ShowPitfallDiscoveryDialog | `640` | 1 | 1058 |
| Trap_ShowPitfallDiscoveryDialog | `480` | 1 | 1059 |
| Trap_ShowPitfallDiscoveryDialog | `188` | 1 | 1060 |
| Trap_ShowPitfallDiscoveryDialog | `17` | 1 | 1071 |
| Trap_ShowPitfallDiscoveryDialog | `10` | 1 | 1073 |
| Trap_ShowPitfallDiscoveryDialog | `46` | 2 | 1077, 1147 |
| Trap_ShowPitfallDiscoveryDialog | `52` | 2 | 1077, 1092 |
| Trap_ShowPitfallDiscoveryDialog | `250` | 3 | 1095, 1101, 1106 |
| Trap_ShowPitfallDiscoveryDialog | `30` | 3 | 1095, 1101, 1106 |
| Trap_ShowPitfallDiscoveryDialog | `32` | 2 | 1095, 1101 |
| Trap_ShowPitfallDiscoveryDialog | `42` | 1 | 1106 |
| Trap_ShowPitfallDiscoveryDialog | `175` | 1 | 1110 |
| Trap_ShowPitfallDiscoveryDialog | `220` | 1 | 1111 |
| Trap_ShowPitfallDiscoveryDialog | `103` | 1 | 1112 |
| Trap_ShowPitfallDiscoveryDialog | `60` | 1 | 1113 |
| Trap_ShowPitfallDiscoveryDialog | `117` | 1 | 1114 |
| Trap_ShowPitfallDiscoveryDialog | `100` | 1 | 1115 |
| Trap_ShowPitfallDiscoveryDialog | `113` | 1 | 1116 |
| Trap_ShowPitfallDiscoveryDialog | `92` | 1 | 1117 |
| Battle_LoadWallSegmentsFromBuildingRecord | `40` | 4 | 1185, 1198, 1199, 1209 |
| Battle_LoadWallSegmentsFromBuildingRecord | `20` | 2 | 1187, 1211 |
| Battle_LoadWallSegmentsFromBuildingRecord | `804` | 1 | 1188 |
| Battle_LoadWallSegmentsFromBuildingRecord | `800` | 2 | 1193, 1214 |
| Battle_LoadWallSegmentsFromBuildingRecord | `388` | 3 | 1196, 1199, 1199 |
| Battle_LoadWallSegmentsFromBuildingRecord | `403` | 3 | 1196, 1199, 1199 |
| Battle_LoadWallSegmentsFromBuildingRecord | `3134` | 1 | 1201 |
| Battle_LoadWallSegmentsFromBuildingRecord | `422` | 1 | 1201 |
| Battle_LoadWallSegmentsFromBuildingRecord | `100` | 1 | 1202 |
| Battle_LoadWallSegmentsFromBuildingRecord | `3534` | 1 | 1202 |
| Battle_LoadWallSegmentsFromBuildingRecord | `2` | 2 | 1205, 1214 |
| Battle_LoadWallSegmentsFromBuildingRecord | `828` | 1 | 1214 |
| Battle_LoadWallSegmentsFromBuildingRecord | `421` | 1 | 1215 |
| Battle_LoadWallSegmentsFromBuildingRecord | `820` | 1 | 1216 |
| Battle_SaveWallSegmentsToBuildingRecord | `20` | 2 | 1233, 1237 |
| Battle_SaveWallSegmentsToBuildingRecord | `3534` | 1 | 1233 |
| Battle_SaveWallSegmentsToBuildingRecord | `804` | 1 | 1233 |
| Battle_SaveWallSegmentsToBuildingRecord | `800` | 1 | 1238 |
| Battle_SaveWallSegmentsToBuildingRecord | `3134` | 1 | 1241 |
| Battle_SaveWallSegmentsToBuildingRecord | `421` | 1 | 1242 |
| Battle_SaveWallSegmentsToBuildingRecord | `840` | 1 | 1245 |
| Battle_SaveWallSegmentsToBuildingRecord | `832` | 1 | 1247 |
| Battle_SaveWallSegmentsToBuildingRecord | `422` | 1 | 1248 |
| Battle_SaveWallSegmentsToBuildingRecord | `828` | 1 | 1248 |
| UnitBattle_IsTileInViewport | `808` | 1 | 1262 |
| UnitBattle_IsTileInViewport | `7` | 2 | 1264, 1267 |
| UnitBattle_IsTileInViewport | `812` | 1 | 1266 |
| GodAnger | `1024` | 2 | 1336, 1337 |
| GodAnger | `3` | 1 | 1338 |
| GodAnger | `2` | 3 | 1345, 1345, 1408 |
| GodAnger | `140059` | 1 | 1346 |
| GodAnger | `4112` | 1 | 1354 |
| GodAnger | `300` | 1 | 1358 |
| GodAnger | `450` | 1 | 1361 |
| GodAnger | `100` | 1 | 1365 |
| GodAnger | `16` | 3 | 1365, 1370, 1373 |
| GodAnger | `150` | 4 | 1368, 1372, 1382, 1385 |
| GodAnger | `200` | 4 | 1368, 1373, 1378, 1381 |
| GodAnger | `10` | 1 | 1369 |
| GodAnger | `0x10u` | 1 | 1373 |
| GodAnger | `0x32u` | 1 | 1373 |
| GodAnger | `50` | 1 | 1373 |
| GodAnger | `60` | 1 | 1377 |
| GodAnger | `0x96` | 1 | 1381 |
| GodAnger | `854` | 1 | 1399 |
| GodAnger | `20` | 1 | 1402 |
| GodAnger | `30` | 1 | 1402 |
| GodAnger | `861` | 2 | 1402, 1403 |
| GodAnger | `858` | 1 | 1407 |
| GodAnger | `1534` | 1 | 1408 |
| GodAnger | `40` | 1 | 1408 |
| GodAnger | `856` | 1 | 1408 |
| Battle_NewTurn | `2` | 1 | 1440 |
| Battle_HasUnitsForBothSides | `854` | 1 | 1460 |
| Battle_HasUnitsForBothSides | `836` | 1 | 1461 |
| Battle_HasUnitsForBothSides | `840` | 1 | 1465 |

### src/buildings/0042C560_0042C840_buildings_010.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Battle_ApplyPeriodicDamageToSideUnits | `2` | 1 | 31 |
| Battle_ApplyPeriodicDamageToSideUnits | `15` | 1 | 33 |
| Battle_ApplyPeriodicDamageToSideUnits | `25` | 1 | 34 |
| Battle_ApplyPeriodicDamageToSideUnits | `35` | 1 | 34 |
| Battle_ApplyPeriodicDamageToSideUnits | `9` | 4 | 37, 38, 39, 40 |
| UnitBattle_HandleManualRotateAndMoveInput | `34` | 1 | 79 |
| UnitBattle_HandleManualRotateAndMoveInput | `147151` | 4 | 81, 83, 86, 88 |
| UnitBattle_HandleManualRotateAndMoveInput | `56` | 1 | 93 |
| UnitBattle_HandleManualRotateAndMoveInput | `205` | 2 | 96, 104 |
| UnitBattle_HandleManualRotateAndMoveInput | `855` | 6 | 100, 101, 102, 114 ... |
| UnitBattle_HandleManualRotateAndMoveInput | `7` | 2 | 102, 116 |
| UnitBattle_HandleManualRotateAndMoveInput | `203` | 2 | 110, 118 |
| UnitBattle_HandleManualRotateAndMoveInput | `200` | 1 | 124 |
| UnitBattle_HandleManualRotateAndMoveInput | `3` | 1 | 130 |
| UnitBattle_HandleManualRotateAndMoveInput | `2` | 2 | 131, 134 |
| UnitBattle_HandleManualRotateAndMoveInput | `4` | 2 | 134, 142 |
| UnitBattle_HandleManualRotateAndMoveInput | `6` | 1 | 136 |
| UnitBattle_HandleManualRotateAndMoveInput | `875` | 1 | 139 |
| UnitBattle_HandleManualRotateAndMoveInput | `23` | 2 | 142, 146 |
| UnitBattle_HandleManualRotateAndMoveInput | `8` | 1 | 143 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `147171` | 1 | 185 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `16` | 4 | 185, 227, 228, 229 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `56` | 1 | 187 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `203` | 1 | 189 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `808` | 10 | 191, 194, 198, 200 ... |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `205` | 1 | 198 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `7` | 6 | 198, 212, 265, 266 ... |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `804` | 2 | 198, 264 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `200` | 1 | 203 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `812` | 10 | 205, 208, 212, 214 ... |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `208` | 1 | 212 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `800` | 2 | 212, 269 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `40` | 1 | 218 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `32` | 3 | 221, 222, 223 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `31` | 8 | 222, 223, 228, 229 ... |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `6` | 6 | 222, 223, 223, 228 ... |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `2` | 1 | 225 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `1534` | 1 | 231 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `8` | 4 | 246, 251, 257, 261 |
| UnitBattle_UpdateViewportFromInputAndGetHoveredSlot | `3` | 4 | 256, 257, 260, 261 |

### src/buildings/004338C0_00436100_buildings_001.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| BuildingGarrisonDialog_ShowProductionDialog | `416` | 1 | 45 |
| BuildingGarrisonDialog_ShowProductionDialog | `20` | 3 | 47, 75, 76 |
| BuildingGarrisonDialog_ShowProductionDialog | `5` | 1 | 66 |
| BuildingGarrisonDialog_ShowProductionDialog | `7` | 1 | 67 |
| BuildingGarrisonDialog_ToggleRepairSelectedUnits | `416` | 1 | 108 |
| BuildingGarrisonDialog_ToggleRepairSelectedUnits | `12` | 1 | 124 |
| BuildingGarrisonDialog_ToggleTrainingSelectedUnits | `416` | 1 | 142 |
| BuildingGarrisonDialog_ToggleTrainingSelectedUnits | `4` | 1 | 153 |
| BuildingGarrisonDialog_ToggleTrainingSelectedUnits | `12` | 1 | 158 |
| BuildingGarrisonDialog_BeginSelectedUnitsExit | `16` | 1 | 174 |
| BuildingGarrisonDialog_BeginSelectedUnitsExit | `12` | 1 | 191 |
| BuildingGarrisonDialog_BeginSelectedUnitsExit | `64` | 1 | 214 |
| CastleProduction_DrawSelectedUnitPortrait | `0x50u` | 1 | 248 |
| CastleProduction_DrawSelectedUnitPortrait | `0xC3u` | 1 | 248 |
| CastleProduction_DrawSelectedUnitPortrait | `195` | 1 | 248 |
| CastleProduction_DrawSelectedUnitPortrait | `80` | 1 | 248 |
| CastleProduction_DrawSelectedUnitPortrait | `46` | 1 | 251 |
| CastleProduction_DrawSelectedUnitPortrait | `52` | 1 | 252 |
| CastleProduction_DrawSelectedUnitPortrait | `193` | 1 | 253 |
| CastleProduction_AnimateSelectedUnitPortrait | `10` | 1 | 281 |
| CastleProduction_AnimateSelectedUnitPortrait | `7` | 1 | 285 |
| CastleProduction_RedrawSelectedUnitPanel | `100` | 1 | 331 |
| CastleProduction_RedrawSelectedUnitPanel | `0x1010` | 1 | 339 |
| CastleProduction_RedrawSelectedUnitPanel | `4112` | 1 | 339 |
| CastleProduction_RedrawSelectedUnitPanel | `224` | 1 | 346 |
| CastleProduction_RedrawSelectedUnitPanel | `4` | 6 | 351, 377, 380, 382 ... |
| CastleProduction_RedrawSelectedUnitPanel | `255` | 1 | 354 |
| CastleProduction_RedrawSelectedUnitPanel | `20` | 2 | 357, 402 |
| CastleProduction_RedrawSelectedUnitPanel | `46` | 4 | 359, 423, 445, 454 |
| CastleProduction_RedrawSelectedUnitPanel | `52` | 4 | 360, 424, 447, 456 |
| CastleProduction_RedrawSelectedUnitPanel | `28` | 3 | 361, 465, 467 |
| CastleProduction_RedrawSelectedUnitPanel | `5` | 7 | 374, 393, 407, 431 ... |
| CastleProduction_RedrawSelectedUnitPanel | `2` | 15 | 375, 377, 378, 430 ... |
| CastleProduction_RedrawSelectedUnitPanel | `35` | 1 | 376 |
| CastleProduction_RedrawSelectedUnitPanel | `17` | 4 | 384, 396, 418, 422 |
| CastleProduction_RedrawSelectedUnitPanel | `0x2Du` | 4 | 388, 393, 402, 407 |
| CastleProduction_RedrawSelectedUnitPanel | `9` | 1 | 388 |
| CastleProduction_RedrawSelectedUnitPanel | `45` | 3 | 390, 404, 412 |
| CastleProduction_RedrawSelectedUnitPanel | `186` | 3 | 424, 468, 470 |
| CastleProduction_RedrawSelectedUnitPanel | `7` | 1 | 426 |
| CastleProduction_RedrawSelectedUnitPanel | `133` | 1 | 429 |
| CastleProduction_RedrawSelectedUnitPanel | `191` | 1 | 429 |
| CastleProduction_RedrawSelectedUnitPanel | `261` | 1 | 429 |
| CastleProduction_RedrawSelectedUnitPanel | `3` | 1 | 429 |
| CastleProduction_RedrawSelectedUnitPanel | `69` | 7 | 429, 431, 432, 433 ... |
| CastleProduction_RedrawSelectedUnitPanel | `10` | 1 | 430 |
| CastleProduction_RedrawSelectedUnitPanel | `6` | 1 | 430 |
| CastleProduction_RedrawSelectedUnitPanel | `201` | 2 | 431, 433 |
| CastleProduction_RedrawSelectedUnitPanel | `217` | 2 | 431, 433 |
| CastleProduction_RedrawSelectedUnitPanel | `95` | 4 | 431, 440, 448, 457 |
| CastleProduction_RedrawSelectedUnitPanel | `154` | 9 | 432, 439, 439, 440 ... |
| CastleProduction_RedrawSelectedUnitPanel | `174` | 4 | 432, 439, 448, 457 |
| CastleProduction_RedrawSelectedUnitPanel | `50` | 2 | 432, 433 |
| CastleProduction_RedrawSelectedUnitPanel | `229` | 1 | 434 |
| CastleProduction_RedrawSelectedUnitPanel | `260` | 1 | 434 |
| CastleProduction_RedrawSelectedUnitPanel | `74` | 1 | 439 |
| CastleProduction_RedrawSelectedUnitPanel | `19` | 1 | 444 |
| CastleProduction_RedrawSelectedUnitPanel | `18` | 1 | 453 |
| CastleProduction_RedrawSelectedUnitPanel | `0x138u` | 1 | 459 |
| CastleProduction_RedrawSelectedUnitPanel | `0x154u` | 1 | 459 |
| CastleProduction_RedrawSelectedUnitPanel | `0x16Eu` | 1 | 459 |
| CastleProduction_RedrawSelectedUnitPanel | `0x48u` | 1 | 459 |
| CastleProduction_RedrawSelectedUnitPanel | `340` | 1 | 459 |
| CastleProduction_RedrawSelectedUnitPanel | `72` | 1 | 459 |
| CastleProduction_RedrawSelectedUnitPanel | `119` | 1 | 462 |
| CastleProduction_RedrawSelectedUnitPanel | `348` | 3 | 462, 463, 464 |
| CastleProduction_RedrawSelectedUnitPanel | `215` | 1 | 463 |
| CastleProduction_RedrawSelectedUnitPanel | `311` | 1 | 464 |
| CastleProduction_RedrawSelectedUnitPanel | `0x14u` | 2 | 465, 466 |
| CastleProduction_RedrawSelectedUnitPanel | `0x1Cu` | 1 | 467 |
| CastleProduction_RedrawSelectedUnitPanel | `0x28u` | 1 | 467 |
| CastleProduction_RedrawSelectedUnitPanel | `40` | 2 | 467, 467 |
| CastleProduction_RedrawSelectedUnitPanel | `0x11u` | 2 | 468, 469 |
| CastleProduction_RedrawSelectedUnitPanel | `0x45u` | 1 | 470 |
| CastleProduction_RedrawSelectedUnitPanel | `0xBAu` | 1 | 470 |
| CastleProduction_DrawLicenceGrid | `4` | 5 | 524, 525, 526, 527 ... |
| CastleProduction_DrawLicenceGrid | `426` | 1 | 524 |
| CastleProduction_DrawLicenceGrid | `48` | 2 | 524, 527 |
| CastleProduction_DrawLicenceGrid | `2` | 5 | 525, 525, 526, 561 ... |
| CastleProduction_DrawLicenceGrid | `31` | 5 | 525, 525, 529, 561 ... |
| CastleProduction_DrawLicenceGrid | `32` | 2 | 525, 559 |
| CastleProduction_DrawLicenceGrid | `82` | 2 | 525, 561 |
| CastleProduction_DrawLicenceGrid | `425` | 1 | 527 |
| CastleProduction_DrawLicenceGrid | `63` | 1 | 529 |
| CastleProduction_DrawLicenceGrid | `402` | 1 | 530 |
| CastleProduction_DrawLicenceGrid | `22` | 2 | 532, 587 |
| CastleProduction_DrawLicenceGrid | `46` | 6 | 533, 547, 560, 574 ... |
| CastleProduction_DrawLicenceGrid | `52` | 6 | 533, 547, 560, 574 ... |
| CastleProduction_DrawLicenceGrid | `33` | 1 | 561 |
| CastleProduction_DrawLicenceGrid | `21` | 1 | 573 |
| CastleProduction_DrawLicenceGrid | `30` | 1 | 601 |
| CastleProduction_DrawLicenceGrid | `12` | 1 | 619 |
| CastleProduction_ReloadLicenceSlotSprite | `112` | 1 | 641 |
| CastleProduction_ReloadLicenceSlotSprite | `402` | 2 | 643, 661 |
| CastleProduction_ReloadLicenceSlotSprite | `0x1010` | 1 | 662 |
| CastleProduction_ReloadLicenceSlotSprite | `4112` | 1 | 662 |
| CastleProduction_ReloadLicenceSlotSprites | `12` | 1 | 678 |
| CastleProduction_TickLicenceGridAnimations | `10` | 1 | 692 |
| CastleProduction_TickLicenceGridAnimations | `12` | 1 | 696 |
| CastleProduction_TickLicenceGridAnimations | `7` | 1 | 697 |
| CastleProduction_TickLicenceGridAnimations | `8` | 1 | 698 |
| CastleProduction_TickLicenceGridAnimations | `402` | 1 | 702 |
| CastleProduction_DrawProductionStatus | `3` | 12 | 735, 736, 737, 738 ... |
| CastleProduction_DrawProductionStatus | `2` | 15 | 740, 754, 761, 761 ... |
| CastleProduction_DrawProductionStatus | `9` | 1 | 742 |
| CastleProduction_DrawProductionStatus | `0x120u` | 1 | 744 |
| CastleProduction_DrawProductionStatus | `0x165u` | 1 | 744 |
| CastleProduction_DrawProductionStatus | `0x191u` | 1 | 744 |
| CastleProduction_DrawProductionStatus | `0x251u` | 1 | 744 |
| CastleProduction_DrawProductionStatus | `288` | 1 | 744 |
| CastleProduction_DrawProductionStatus | `401` | 8 | 744, 772, 774, 778 ... |
| CastleProduction_DrawProductionStatus | `5` | 1 | 746 |
| CastleProduction_DrawProductionStatus | `297` | 1 | 772 |
| CastleProduction_DrawProductionStatus | `593` | 7 | 772, 774, 778, 782 ... |
| CastleProduction_DrawProductionStatus | `317` | 1 | 774 |
| CastleProduction_DrawProductionStatus | `337` | 3 | 778, 782, 786 |
| CastleProduction_DrawProductionStatus | `4` | 1 | 780 |
| CastleProduction_DrawProductionStatus | `307` | 1 | 797 |
| CastleProduction_DrawProductionStatus | `327` | 1 | 798 |
| UI_DrawActionBox | `0x11Du` | 1 | 823 |
| UI_DrawActionBox | `0x15Eu` | 1 | 823 |
| UI_DrawActionBox | `0x1A9u` | 1 | 823 |
| UI_DrawActionBox | `0x1C2u` | 1 | 823 |
| UI_DrawActionBox | `285` | 2 | 823, 824 |
| UI_DrawActionBox | `425` | 1 | 823 |
| UI_DrawActionBox | `3` | 1 | 824 |
| UI_DrawActionBox | `349` | 1 | 824 |
| UI_DrawActionBox | `430` | 1 | 824 |
| UI_GetGridIndexFromMouse | `426` | 3 | 841, 843, 845 |
| UI_GetGridIndexFromMouse | `32` | 2 | 842, 843 |
| UI_GetGridIndexFromMouse | `33` | 1 | 843 |
| UI_GetGridIndexFromMouse | `48` | 2 | 843, 845 |
| UI_GetGridIndexFromMouse | `64` | 1 | 844 |
| UI_GetGridIndexFromMouse | `82` | 2 | 844, 845 |
| UI_GetGridIndexFromMouse | `4` | 2 | 845, 848 |
| UI_GetGridIndexFromMouse | `3` | 1 | 846 |
| CastleProduction_HandleBuyLicenceAction | `402` | 1 | 930 |
| CastleProduction_HandleBuyLicenceAction | `64` | 1 | 934 |
| CastleProduction_HandleRemoveLicenceAction | `64` | 1 | 965 |
| CastleProduction_HandleInfoAction | `108` | 1 | 1023 |
| CastleProduction_HandleInfoAction | `20` | 6 | 1029, 1037, 1041, 1056 ... |
| CastleProduction_HandleInfoAction | `184` | 1 | 1046 |
| CastleProduction_HandleInfoAction | `6` | 1 | 1052 |
| CastleProduction_RebuildAvailableUnitList | `0xA4` | 1 | 1082 |
| CastleProduction_RebuildAvailableUnitList | `0xFF` | 1 | 1082 |
| CastleProduction_HandleLicenceGridClick | `402` | 2 | 1115, 1121 |
| CastleProduction_HandleLicenceGridClick | `64` | 1 | 1118 |
| CastleProduction_HandleAvailableUnitStripClick | `17` | 1 | 1162 |
| CastleProduction_HandleAvailableUnitStripClick | `2` | 3 | 1162, 1170, 1171 |
| CastleProduction_HandleAvailableUnitStripClick | `35` | 1 | 1162 |
| CastleProduction_HandleAvailableUnitStripClick | `40` | 2 | 1166, 1168 |
| CastleProduction_HandleAvailableUnitStripClick | `0x14u` | 1 | 1168 |
| Castle_ShowUnitProductionPanel | `140063` | 1 | 1239 |
| Castle_ShowUnitProductionPanel | `2` | 1 | 1239 |
| Castle_ShowUnitProductionPanel | `12` | 2 | 1243, 1311 |
| Castle_ShowUnitProductionPanel | `7` | 2 | 1244, 1278 |
| Castle_ShowUnitProductionPanel | `1024` | 1 | 1249 |
| Castle_ShowUnitProductionPanel | `256` | 1 | 1251 |
| Castle_ShowUnitProductionPanel | `184` | 1 | 1258 |
| Castle_ShowUnitProductionPanel | `6` | 1 | 1265 |
| Castle_ShowUnitProductionPanel | `4112` | 1 | 1266 |
| Castle_ShowUnitProductionPanel | `5` | 1 | 1275 |
| Castle_ShowUnitProductionPanel | `20` | 5 | 1276, 1286, 1287, 1290 ... |
| Castle_ShowUnitProductionPanel | `9` | 1 | 1277 |
| Castle_ShowUnitProductionPanel | `8` | 1 | 1280 |
| Palette_LoadOrBuildBlendLookupTable | `256` | 1 | 1366 |
| BuildingTransferDialog_DrawSourceRemainingValue | `5` | 1 | 1402 |
| BuildingTransferDialog_DrawSourceRemainingValue | `0x190u` | 1 | 1404 |
| BuildingTransferDialog_DrawSourceRemainingValue | `0x1BBu` | 1 | 1404 |
| BuildingTransferDialog_DrawSourceRemainingValue | `0x30u` | 1 | 1404 |
| BuildingTransferDialog_DrawSourceRemainingValue | `0x3Cu` | 1 | 1404 |
| BuildingTransferDialog_DrawSourceRemainingValue | `400` | 1 | 1404 |
| BuildingTransferDialog_DrawSourceRemainingValue | `48` | 2 | 1404, 1405 |
| BuildingTransferDialog_DrawSourceRemainingValue | `3` | 1 | 1405 |
| BuildingTransferDialog_DrawSourceRemainingValue | `347` | 1 | 1405 |
| BuildingTransferDialog_DrawSourceRemainingValue | `445` | 1 | 1405 |
| BuildingTransferDialog_DrawTransferAmountValue | `5` | 1 | 1423 |
| BuildingTransferDialog_DrawTransferAmountValue | `0x110u` | 1 | 1425 |
| BuildingTransferDialog_DrawTransferAmountValue | `0x12Cu` | 1 | 1425 |
| BuildingTransferDialog_DrawTransferAmountValue | `0x224u` | 1 | 1425 |
| BuildingTransferDialog_DrawTransferAmountValue | `0x259u` | 1 | 1425 |
| BuildingTransferDialog_DrawTransferAmountValue | `272` | 2 | 1425, 1426 |
| BuildingTransferDialog_DrawTransferAmountValue | `548` | 2 | 1425, 1426 |
| BuildingTransferDialog_DrawTransferAmountValue | `3` | 1 | 1426 |
| BuildingTransferDialog_DrawTransferAmountValue | `601` | 1 | 1426 |
| BuildingTransferDialog_CommitTransfer | `2` | 1 | 1458 |
| BuildingTransferDialog_CommitTransfer | `467` | 2 | 1462, 1463 |

### src/buildings/00436180_00437A90_buildings_002.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| BuildingTransferDialog_IncreaseTransferAmount | `10` | 4 | 35, 42, 48, 49 |
| BuildingTransferDialog_IncreaseTransferAmount | `0x32u` | 1 | 42 |
| BuildingTransferDialog_IncreaseTransferAmount | `0xA` | 1 | 42 |
| BuildingTransferDialog_IncreaseTransferAmount | `1000` | 2 | 43, 44 |
| BuildingTransferDialog_IncreaseTransferAmount | `438` | 2 | 45, 49 |
| BuildingTransferDialog_IncreaseTransferAmount | `0xAu` | 1 | 49 |
| BuildingTransferDialog_DecreaseTransferAmount | `10` | 2 | 87, 94 |
| BuildingTransferDialog_DecreaseTransferAmount | `0x32u` | 1 | 94 |
| BuildingTransferDialog_DecreaseTransferAmount | `0xA` | 1 | 94 |
| BuildingTransferTargetList_Draw | `3` | 1 | 135 |
| BuildingTransferTargetList_Draw | `4112` | 1 | 144 |
| BuildingTransferTargetList_Draw | `5` | 3 | 150, 172, 191 |
| BuildingTransferTargetList_Draw | `2` | 7 | 151, 154, 175, 179 ... |
| BuildingTransferTargetList_Draw | `18` | 3 | 153, 216, 217 |
| BuildingTransferTargetList_Draw | `266` | 1 | 161 |
| BuildingTransferTargetList_Draw | `9` | 1 | 170 |
| BuildingTransferTargetList_Draw | `108` | 1 | 194 |
| BuildingTransferTargetList_Draw | `4` | 1 | 195 |
| BuildingTransferTargetList_Draw | `124` | 1 | 199 |
| BuildingTransferTargetList_Draw | `430` | 1 | 202 |
| BuildingTransferTargetList_Draw | `170` | 1 | 205 |
| BuildingTransferTargetList_Draw | `206` | 1 | 210 |
| BuildingTransferTargetList_Draw | `438` | 1 | 213 |
| BuildingTransferTargetList_Rebuild | `0xFF` | 1 | 288 |
| BuildingTransferTargetList_Rebuild | `2` | 2 | 289, 299 |
| BuildingTransferTargetList_Rebuild | `509678` | 2 | 297, 298 |
| BuildingTransferTargetList_Rebuild | `16` | 1 | 301 |
| BuildingTransferTargetList_Rebuild | `100` | 1 | 310 |
| BuildingTransferTargetList_HandleClick | `18` | 1 | 325 |
| BuildingTransferTargetList_HandleClick | `2` | 3 | 325, 333, 334 |
| BuildingTransferTargetList_HandleClick | `266` | 2 | 331, 332 |
| UI_DrawFormattedTokenLine | `150` | 1 | 391 |
| UI_DrawFormattedTokenLine | `50` | 2 | 394, 420 |
| UI_DrawFormattedTokenLine | `4` | 2 | 398, 406 |
| UI_DrawFormattedTokenLine | `5` | 2 | 418, 420 |
| UnitBattle_ResetAiReachGridForSide | `854` | 1 | 468 |
| UnitBattle_ResetAiReachGridForSide | `160` | 3 | 472, 475, 484 |
| UnitBattle_ResetAiReachGridForSide | `8` | 1 | 478 |
| UnitBattle_ResetAiReachGridForSide | `20` | 1 | 486 |
| UnitBattle_ResetAiReachGridForSide | `3204` | 1 | 489 |
| UnitBattle_ResetAiReachGridForSide | `70488` | 1 | 492 |
| UnitBattle_RetreatUnit | `2` | 11 | 542, 546, 548, 553 ... |
| UnitBattle_RetreatUnit | `3` | 3 | 545, 575, 585 |
| UnitBattle_RetreatUnit | `804` | 2 | 561, 562 |
| UnitBattle_RetreatUnit | `800` | 2 | 565, 567 |
| UnitBattle_RetreatUnit | `1534` | 1 | 568 |
| UnitBattle_RetreatUnit | `40` | 1 | 568 |
| UnitBattle_RetreatUnit | `854` | 1 | 579 |
| UnitBattle_RetreatUnit | `858` | 2 | 581, 588 |
| UnitBattle_RetreatUnit | `856` | 2 | 582, 586 |
| UnitBattle_RetreatUnit | `23` | 3 | 590, 609, 612 |
| UnitBattle_IsTileWithinMinRange | `4` | 2 | 649, 650 |
| UnitBattle_IsTileWithinMinRange | `6` | 2 | 651, 652 |
| UnitBattle_MoveShootingUnit | `40` | 3 | 712, 808, 813 |
| UnitBattle_MoveShootingUnit | `1534` | 4 | 713, 716, 808, 813 |
| UnitBattle_MoveShootingUnit | `2` | 4 | 713, 716, 808, 813 |
| UnitBattle_MoveShootingUnit | `5u` | 6 | 722, 724, 819, 821 ... |
| UnitBattle_MoveShootingUnit | `860` | 6 | 722, 724, 819, 821 ... |
| UnitBattle_MoveShootingUnit | `20` | 3 | 740, 806, 837 |
| UnitBattle_MoveShootingUnit | `3134` | 3 | 740, 806, 837 |
| UnitBattle_MoveShootingUnit | `836` | 2 | 741, 807 |
| UnitBattle_MoveShootingUnit | `854` | 3 | 741, 807, 809 |
| UnitBattle_MoveShootingUnit | `23` | 13 | 749, 750, 751, 752 ... |
| UnitBattle_MoveShootingUnit | `4` | 1 | 765 |
| UnitBattle_MoveShootingUnit | `5` | 2 | 766, 778 |
| UnitBattle_MoveShootingUnit | `8` | 2 | 766, 778 |
| UnitBattle_MoveShootingUnit | `0xFFFFFFFF` | 2 | 797, 798 |
| UnitBattle_EstimateDamageScoreAgainstUnit | `2` | 5 | 891, 918, 932, 937 ... |
| UnitBattle_EstimateDamageScoreAgainstUnit | `3` | 5 | 892, 919, 933, 938 ... |
| UnitBattle_EstimateDamageScoreAgainstUnit | `8` | 16 | 893, 921, 935, 939 ... |
| UnitBattle_EstimateDamageScoreAgainstUnit | `6` | 1 | 901 |
| UnitBattle_EstimateDamageScoreAgainstUnit | `9` | 15 | 912, 948, 957, 979 ... |
| UnitBattle_EstimateDamageScoreAgainstUnit | `5` | 6 | 946, 949, 969, 981 ... |
| UnitBattle_EstimateDamageScoreAgainstUnit | `100` | 4 | 960, 995, 1002, 1022 |
| UnitBattle_EstimateDamageScoreAgainstUnit | `5u` | 2 | 997, 1008 |
| UnitBattle_EstimateDamageScoreAgainstUnit | `861` | 1 | 999 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `4` | 1 | 1100 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `854` | 1 | 1100 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `858` | 2 | 1109, 1233 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `856` | 1 | 1110 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `3` | 8 | 1115, 1128, 1142, 1158 ... |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `864` | 16 | 1115, 1117, 1128, 1128 ... |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `2` | 10 | 1117, 1126, 1128, 1142 ... |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `5` | 10 | 1117, 1128, 1142, 1158 ... |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `20` | 2 | 1125, 1251 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `3134` | 2 | 1125, 1251 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `1534` | 2 | 1126, 1258 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `40` | 2 | 1126, 1257 |
| UnitBattle_ScoreTileAgainstRangedUnitsOfSide | `8` | 7 | 1170, 1193, 1196, 1217 ... |

### src/buildings/004382E0_0043A880_buildings_003.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_ScoreAiActionGridForUnit | `801` | 4 | 228, 406, 468, 477 |
| UnitBattle_ScoreAiActionGridForUnit | `854` | 3 | 234, 462, 487 |
| UnitBattle_ScoreAiActionGridForUnit | `856` | 13 | 238, 409, 413, 420 ... |
| UnitBattle_ScoreAiActionGridForUnit | `858` | 13 | 239, 410, 414, 421 ... |
| UnitBattle_ScoreAiActionGridForUnit | `160` | 10 | 240, 423, 435, 455 ... |
| UnitBattle_ScoreAiActionGridForUnit | `4` | 7 | 240, 420, 435, 455 ... |
| UnitBattle_ScoreAiActionGridForUnit | `2` | 77 | 241, 242, 246, 247 ... |
| UnitBattle_ScoreAiActionGridForUnit | `40` | 19 | 241, 275, 358, 360 ... |
| UnitBattle_ScoreAiActionGridForUnit | `1534` | 13 | 243, 244, 276, 360 ... |
| UnitBattle_ScoreAiActionGridForUnit | `800` | 2 | 246, 499 |
| UnitBattle_ScoreAiActionGridForUnit | `15` | 2 | 249, 501 |
| UnitBattle_ScoreAiActionGridForUnit | `860` | 2 | 252, 504 |
| UnitBattle_ScoreAiActionGridForUnit | `3` | 31 | 259, 278, 293, 306 ... |
| UnitBattle_ScoreAiActionGridForUnit | `864` | 56 | 259, 261, 278, 278 ... |
| UnitBattle_ScoreAiActionGridForUnit | `5` | 43 | 261, 278, 293, 306 ... |
| UnitBattle_ScoreAiActionGridForUnit | `20` | 16 | 269, 522, 644, 657 ... |
| UnitBattle_ScoreAiActionGridForUnit | `3134` | 17 | 269, 522, 644, 657 ... |
| UnitBattle_ScoreAiActionGridForUnit | `8` | 22 | 318, 329, 350, 353 ... |
| UnitBattle_ScoreAiActionGridForUnit | `700` | 2 | 364, 553 |
| UnitBattle_ScoreAiActionGridForUnit | `836` | 1 | 392 |
| UnitBattle_ScoreAiActionGridForUnit | `840` | 1 | 399 |
| UnitBattle_ScoreAiActionGridForUnit | `120` | 1 | 412 |
| UnitBattle_ScoreAiActionGridForUnit | `500` | 6 | 415, 426, 436, 447 ... |
| UnitBattle_ScoreAiActionGridForUnit | `200` | 1 | 444 |
| UnitBattle_ScoreAiActionGridForUnit | `6` | 1 | 451 |
| UnitBattle_ScoreAiActionGridForUnit | `3204` | 5 | 907, 1002, 1096, 1190 ... |
| UnitBattle_ScoreAiActionGridForUnit | `640` | 6 | 908, 911, 1003, 1006 ... |
| UnitBattle_ScoreAiActionGridForUnit | `650` | 1 | 1291 |
| WCIsvListBase_TransferAllInto | `8` | 1 | 1415 |
| WCIsvListBase_PopUntilMatchOrEmpty | `8` | 2 | 1432, 1439 |

### src/buildings/0043A8B0_0043CC50_buildings_004.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_SelectAiActionForUnit | `66` | 3 | 65, 265, 284 |
| UnitBattle_SelectAiActionForUnit | `4` | 3 | 91, 193, 302 |
| UnitBattle_SelectAiActionForUnit | `2` | 29 | 92, 118, 120, 129 ... |
| UnitBattle_SelectAiActionForUnit | `3` | 11 | 92, 129, 155, 171 ... |
| UnitBattle_SelectAiActionForUnit | `5` | 14 | 92, 94, 129, 157 ... |
| UnitBattle_SelectAiActionForUnit | `864` | 18 | 92, 92, 129, 129 ... |
| UnitBattle_SelectAiActionForUnit | `42` | 1 | 94 |
| UnitBattle_SelectAiActionForUnit | `801` | 7 | 94, 120, 123, 143 ... |
| UnitBattle_SelectAiActionForUnit | `804` | 1 | 99 |
| UnitBattle_SelectAiActionForUnit | `800` | 1 | 103 |
| UnitBattle_SelectAiActionForUnit | `3204` | 4 | 105, 237, 242, 255 |
| UnitBattle_SelectAiActionForUnit | `8` | 8 | 112, 138, 204, 215 ... |
| UnitBattle_SelectAiActionForUnit | `160` | 3 | 116, 237, 242 |
| UnitBattle_SelectAiActionForUnit | `6` | 3 | 118, 120, 196 |
| UnitBattle_SelectAiActionForUnit | `40` | 15 | 120, 136, 138, 143 ... |
| UnitBattle_SelectAiActionForUnit | `20` | 6 | 134, 162, 233, 290 ... |
| UnitBattle_SelectAiActionForUnit | `3134` | 3 | 134, 162, 233 |
| UnitBattle_SelectAiActionForUnit | `836` | 2 | 135, 234 |
| UnitBattle_SelectAiActionForUnit | `854` | 4 | 135, 234, 269, 343 |
| UnitBattle_SelectAiActionForUnit | `1534` | 8 | 136, 169, 235, 274 ... |
| UnitBattle_SelectAiActionForUnit | `7` | 1 | 256 |
| UnitBattle_SelectAiActionForUnit | `856` | 7 | 271, 275, 277, 307 ... |
| UnitBattle_SelectAiActionForUnit | `858` | 7 | 273, 276, 279, 308 ... |
| UnitBattle_ApproachToSafeDistance | `8` | 5 | 508, 703, 714, 736 ... |
| UnitBattle_ApproachToSafeDistance | `40` | 6 | 510, 582, 619, 625 ... |
| UnitBattle_ApproachToSafeDistance | `1534` | 6 | 511, 582, 621, 625 ... |
| UnitBattle_ApproachToSafeDistance | `2` | 10 | 511, 582, 620, 625 ... |
| UnitBattle_ApproachToSafeDistance | `23` | 23 | 515, 519, 521, 523 ... |
| UnitBattle_ApproachToSafeDistance | `5` | 7 | 544, 577, 636, 642 ... |
| UnitBattle_ApproachToSafeDistance | `255` | 2 | 550, 589 |
| UnitBattle_ApproachToSafeDistance | `4` | 1 | 584 |
| UnitBattle_ApproachToSafeDistance | `20` | 2 | 587, 645 |
| UnitBattle_ApproachToSafeDistance | `31` | 2 | 617, 624 |
| UnitBattle_ApproachToSafeDistance | `3` | 4 | 634, 653, 669, 688 |
| UnitBattle_ApproachToSafeDistance | `864` | 8 | 634, 636, 653, 653 ... |
| UnitBattle_ApproachToSafeDistance | `3134` | 1 | 645 |
| UnitBattle_ExecuteAiActionForUnit | `801` | 1 | 802 |
| UnitBattle_ExecuteAiActionForUnit | `2` | 8 | 806, 811, 829, 833 ... |
| UnitBattle_ExecuteAiActionForUnit | `40` | 6 | 806, 829, 833, 835 ... |
| UnitBattle_ExecuteAiActionForUnit | `12` | 2 | 811, 874 |
| UnitBattle_ExecuteAiActionForUnit | `3` | 2 | 811, 874 |
| UnitBattle_ExecuteAiActionForUnit | `5` | 2 | 811, 874 |
| UnitBattle_ExecuteAiActionForUnit | `6` | 2 | 811, 874 |
| UnitBattle_ExecuteAiActionForUnit | `23` | 6 | 817, 820, 823, 860 ... |
| UnitBattle_ExecuteAiActionForUnit | `1534` | 5 | 829, 833, 835, 841 ... |
| UnitBattle_ExecuteAiActionForUnit | `861` | 1 | 831 |
| UnitBattle_ExecuteAiActionForUnit | `9` | 1 | 832 |
| UnitBattle_ExecuteAiActionForUnit | `4u` | 2 | 849, 889 |
| UnitBattle_ExecuteAiActionForUnit | `860` | 2 | 849, 889 |
| UnitBattle_ExecuteAiActionForUnit | `20` | 1 | 888 |
| UnitBattle_ExecuteAiActionForUnit | `3134` | 1 | 888 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `5` | 1 | 945 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `0xFF` | 1 | 966 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `20` | 6 | 966, 1006, 1066, 1076 ... |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `804` | 2 | 970, 1004 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `2` | 16 | 975, 982, 988, 992 ... |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `800` | 1 | 976 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `1534` | 2 | 979, 987 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `854` | 1 | 980 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `40` | 1 | 996 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `6` | 1 | 1001 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `856` | 1 | 1003 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `18` | 1 | 1018 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `10` | 2 | 1057, 1127 |
| UnitBattle_BuildAiUnitQueueForCurrentMode | `4` | 3 | 1069, 1094, 1132 |
| UnitBattle_ScanAiPlanRangeLine | `20` | 2 | 1209, 1285 |
| UnitBattle_ScanAiPlanRangeLine | `836` | 1 | 1211 |
| UnitBattle_ScanAiPlanRangeLine | `840` | 1 | 1218 |
| UnitBattle_ScanAiPlanRangeLine | `854` | 2 | 1228, 1251 |
| UnitBattle_ScanAiPlanRangeLine | `856` | 1 | 1230 |
| UnitBattle_ScanAiPlanRangeLine | `3` | 5 | 1237, 1278, 1288, 1302 ... |
| UnitBattle_ScanAiPlanRangeLine | `800` | 1 | 1238 |
| UnitBattle_ScanAiPlanRangeLine | `804` | 1 | 1239 |
| UnitBattle_ScanAiPlanRangeLine | `858` | 1 | 1253 |
| UnitBattle_ScanAiPlanRangeLine | `1534` | 2 | 1265, 1286 |
| UnitBattle_ScanAiPlanRangeLine | `2` | 6 | 1265, 1280, 1286, 1288 ... |
| UnitBattle_ScanAiPlanRangeLine | `40` | 2 | 1265, 1286 |
| UnitBattle_ScanAiPlanRangeLine | `864` | 8 | 1278, 1280, 1288, 1288 ... |
| UnitBattle_ScanAiPlanRangeLine | `5` | 4 | 1280, 1288, 1302, 1318 |
| UnitBattle_ScanAiPlanRangeLine | `3134` | 1 | 1285 |
| UnitBattle_ScanAiPlanRangeLine | `8` | 5 | 1325, 1347, 1350, 1362 ... |
| UnitBattle_ScanAiWallTargetColumns | `800` | 1 | 1400 |
| UnitBattle_ScanAiWallTargetColumns | `804` | 1 | 1401 |
| UnitBattle_ScanAiWallTargetColumns | `828` | 1 | 1402 |
| UnitBattle_ScanAiWallTargetColumns | `2` | 2 | 1404, 1404 |
| UnitBattle_ScanAiWallTargetColumns | `20` | 3 | 1411, 1416, 1422 |
| UnitBattle_ScanAiWallTargetColumns | `3135` | 1 | 1414 |
| UnitBattle_ScanAiWallTargetColumns | `3134` | 3 | 1426, 1426, 1426 |
| UnitBattle_SelectAiPlanMode | `3` | 3 | 1451, 1457, 1459 |
| UnitBattle_SelectAiPlanMode | `828` | 1 | 1453 |
| UnitBattle_SelectAiPlanMode | `6` | 1 | 1455 |
| UnitBattle_SelectAiPlanMode | `840` | 1 | 1455 |
| UnitBattle_SelectAiPlanMode | `836` | 2 | 1457, 1459 |

### src/buildings/0043CD00_0043E4B0_buildings_005.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitBattle_RunAiTurnForSide | `828` | 2 | 56, 61 |
| UnitBattle_RunAiTurnForSide | `800` | 1 | 62 |
| UnitBattle_RunAiTurnForSide | `804` | 1 | 63 |
| UnitBattle_RunAiTurnForSide | `4` | 1 | 81 |
| UnitBattle_RunAiTurnForSide | `2` | 1 | 83 |
| UnitBattle_RunAiTurnForSide | `6` | 1 | 103 |
| UnitBattle_RunAiTurnForSide | `854` | 1 | 141 |
| WCIsvListBase_dtorRoot | `4` | 1 | 213 |
| WCIsvListBase_dtorRoot | `2` | 1 | 219 |
| WCIsvListBase_ctorVariant124 | `2` | 1 | 247 |
| WCIsvListBase_ctorVariant124 | `3` | 1 | 248 |
| WCIsvListBase_ctorVariant124 | `4` | 1 | 249 |
| WCIsvListBase_ctorVariant124 | `5` | 1 | 250 |
| WCIsvListBase_dtorVariant124 | `4` | 1 | 268 |
| WCIsvListBase_dtorVariant124 | `2` | 1 | 277 |
| WCIsvListBase_ctorVariant124AndCopy | `2` | 1 | 296 |
| WCIsvListBase_ctorVariant124AndCopy | `3` | 1 | 297 |
| WCIsvListBase_ctorVariant124AndCopy | `4` | 1 | 298 |
| WCIsvListBase_ctorVariant124AndCopy | `5` | 1 | 299 |
| WCIsvListBase_ctorVariant134 | `2` | 1 | 317 |
| WCIsvListBase_ctorVariant134 | `3` | 1 | 318 |
| WCIsvListBase_ctorVariant134 | `4` | 1 | 319 |
| WCIsvListBase_ctorVariant134 | `5` | 1 | 320 |
| WCIsvListBase_dtorVariant134 | `4` | 1 | 338 |
| WCIsvListBase_dtorVariant134 | `2` | 1 | 347 |
| WCIsvListBase_base_destroy | `8` | 1 | 479 |
| WCIsvListBase_AllocLinkNode | `8` | 2 | 503, 505 |
| WCIsvListBase_ReleaseLinkNode | `20` | 2 | 518, 519 |
| WCIsvListBase_CopyAppendAll | `4` | 2 | 530, 530 |
| WCIsvListBase_CopyAppendAll | `5` | 2 | 531, 531 |
| WCIsvListBase_PopFrontValue | `8` | 1 | 591 |
| WCIsvListBase_CopyCtor | `2` | 1 | 603 |
| WCIsvListBase_CopyCtor | `3` | 1 | 604 |
| WCIsvListBase_CopyCtor | `4` | 2 | 605, 611 |
| WCIsvListBase_CopyCtor | `5` | 1 | 606 |
| Battle_DeploySideUnitsByRoleBuckets | `1065353216` | 1 | 683 |
| Battle_DeploySideUnitsByRoleBuckets | `2` | 1 | 696 |
| Battle_BuildRoleDeploymentBuckets | `0xC0` | 1 | 715 |
| Battle_BuildRoleDeploymentBuckets | `7` | 1 | 726 |
| Battle_BuildRoleDeploymentBuckets | `10` | 6 | 727, 727, 729, 729 ... |
| Battle_BuildRoleDeploymentBuckets | `2` | 1 | 729 |
| Battle_BuildRoleDeploymentBuckets | `3` | 1 | 732 |
| Battle_BuildRoleDeploymentBuckets | `4` | 1 | 734 |
| Battle_PlaceUnitAtNextOpenDeploymentTile | `2` | 6 | 768, 769, 778, 785 ... |
| Battle_PlaceUnitAtNextOpenDeploymentTile | `3` | 4 | 768, 773, 785, 791 |
| Battle_PlaceUnitAtNextOpenDeploymentTile | `804` | 2 | 768, 785 |
| Battle_PlaceUnitAtNextOpenDeploymentTile | `800` | 3 | 769, 770, 786 |
| Battle_PlaceUnitAtNextOpenDeploymentTile | `6` | 2 | 778, 796 |
| Battle_PlaceRoleDeploymentBuckets | `48` | 4 | 844, 874, 904, 914 |
| Battle_PlaceRoleDeploymentBuckets | `3` | 1 | 850 |
| Battle_PlaceRoleDeploymentBuckets | `7` | 2 | 872, 873 |
| Battle_PlaceRoleDeploymentBuckets | `4` | 5 | 874, 897, 899, 904 ... |
| Battle_PlaceRoleDeploymentBuckets | `10` | 2 | 877, 879 |
| Battle_PlaceRoleDeploymentBuckets | `10LL` | 2 | 880, 881 |
| Battle_PlaceRoleDeploymentBuckets | `12` | 2 | 901, 913 |
| Building_ShowGateDoorDialog_v1 | `1040` | 1 | 954 |
| Building_ShowGateDoorDialog_v1 | `140063` | 1 | 956 |
| Building_ShowGateDoorDialog_v1 | `2` | 1 | 956 |
| Building_ShowGateDoorDialog_v1 | `256` | 1 | 957 |
| Building_ShowGateDoorDialog_v1 | `184` | 1 | 962 |
| Building_ShowGateDoorDialog_v1 | `48` | 1 | 963 |
| Building_ShowGateDoorDialog_v1 | `4112` | 1 | 964 |
| Building_ShowGateDoorDialog_v1 | `10` | 2 | 974, 979 |
| Building_ShowGateDoorDialog_v1 | `8` | 2 | 975, 977 |
| Building_ShowGateDoorDialog_v1 | `193` | 1 | 978 |
| Building_ShowGateDoorDialog_v1 | `3` | 1 | 978 |
| Building_ShowGateDoorDialog_v1 | `439` | 1 | 978 |
| Building_ShowGateDoorDialog_v1 | `80` | 1 | 978 |
| Building_ShowGateDoorDialog_v1 | `140` | 1 | 980 |
| Building_ShowGateDoorDialog_v1 | `95` | 1 | 980 |
| Building_ShowGateDoorDialog_v1 | `36` | 1 | 982 |
| Building_ShowGateDoorDialog_v1 | `46` | 1 | 982 |
| Building_ShowGateDoorDialog_v1 | `20` | 2 | 983, 996 |
| Building_ShowGateDoorDialog_v2 | `1040` | 1 | 1048 |
| Building_ShowGateDoorDialog_v2 | `140063` | 1 | 1050 |
| Building_ShowGateDoorDialog_v2 | `2` | 1 | 1050 |
| Building_ShowGateDoorDialog_v2 | `256` | 1 | 1051 |
| Building_ShowGateDoorDialog_v2 | `184` | 1 | 1056 |
| Building_ShowGateDoorDialog_v2 | `48` | 1 | 1057 |
| Building_ShowGateDoorDialog_v2 | `4112` | 1 | 1058 |
| Building_ShowGateDoorDialog_v2 | `10` | 2 | 1068, 1073 |
| Building_ShowGateDoorDialog_v2 | `8` | 2 | 1069, 1071 |
| Building_ShowGateDoorDialog_v2 | `193` | 1 | 1072 |
| Building_ShowGateDoorDialog_v2 | `3` | 1 | 1072 |
| Building_ShowGateDoorDialog_v2 | `439` | 1 | 1072 |
| Building_ShowGateDoorDialog_v2 | `80` | 1 | 1072 |
| Building_ShowGateDoorDialog_v2 | `140` | 1 | 1074 |
| Building_ShowGateDoorDialog_v2 | `95` | 1 | 1074 |
| Building_ShowGateDoorDialog_v2 | `36` | 1 | 1076 |
| Building_ShowGateDoorDialog_v2 | `46` | 1 | 1076 |
| Building_ShowGateDoorDialog_v2 | `20` | 2 | 1077, 1090 |
| Building_ShowGateDoorDialog_v3 | `1040` | 1 | 1142 |
| Building_ShowGateDoorDialog_v3 | `140063` | 1 | 1144 |
| Building_ShowGateDoorDialog_v3 | `2` | 1 | 1144 |
| Building_ShowGateDoorDialog_v3 | `256` | 1 | 1145 |
| Building_ShowGateDoorDialog_v3 | `184` | 1 | 1150 |
| Building_ShowGateDoorDialog_v3 | `48` | 1 | 1151 |
| Building_ShowGateDoorDialog_v3 | `4112` | 1 | 1152 |
| Building_ShowGateDoorDialog_v3 | `10` | 2 | 1162, 1167 |
| Building_ShowGateDoorDialog_v3 | `8` | 2 | 1163, 1165 |
| Building_ShowGateDoorDialog_v3 | `193` | 1 | 1166 |
| Building_ShowGateDoorDialog_v3 | `3` | 1 | 1166 |
| Building_ShowGateDoorDialog_v3 | `439` | 1 | 1166 |
| Building_ShowGateDoorDialog_v3 | `80` | 1 | 1166 |
| Building_ShowGateDoorDialog_v3 | `140` | 1 | 1168 |
| Building_ShowGateDoorDialog_v3 | `95` | 1 | 1168 |
| Building_ShowGateDoorDialog_v3 | `36` | 1 | 1170 |
| Building_ShowGateDoorDialog_v3 | `46` | 1 | 1170 |
| Building_ShowGateDoorDialog_v3 | `20` | 2 | 1171, 1184 |
| Building_ShowGateDoorDialog_v4 | `1040` | 1 | 1236 |
| Building_ShowGateDoorDialog_v4 | `140063` | 1 | 1238 |
| Building_ShowGateDoorDialog_v4 | `2` | 1 | 1238 |
| Building_ShowGateDoorDialog_v4 | `256` | 1 | 1239 |
| Building_ShowGateDoorDialog_v4 | `184` | 1 | 1244 |
| Building_ShowGateDoorDialog_v4 | `48` | 1 | 1245 |
| Building_ShowGateDoorDialog_v4 | `4112` | 1 | 1246 |
| Building_ShowGateDoorDialog_v4 | `10` | 2 | 1256, 1261 |
| Building_ShowGateDoorDialog_v4 | `8` | 2 | 1257, 1259 |
| Building_ShowGateDoorDialog_v4 | `193` | 1 | 1260 |
| Building_ShowGateDoorDialog_v4 | `3` | 1 | 1260 |
| Building_ShowGateDoorDialog_v4 | `439` | 1 | 1260 |
| Building_ShowGateDoorDialog_v4 | `80` | 1 | 1260 |
| Building_ShowGateDoorDialog_v4 | `140` | 1 | 1262 |
| Building_ShowGateDoorDialog_v4 | `95` | 1 | 1262 |
| Building_ShowGateDoorDialog_v4 | `36` | 1 | 1264 |
| Building_ShowGateDoorDialog_v4 | `46` | 1 | 1264 |
| Building_ShowGateDoorDialog_v4 | `20` | 2 | 1265, 1278 |
| Building_HasFreeAdjacentExitTile | `4` | 1 | 1307 |
| Building_HasFreeAdjacentExitTile | `12` | 2 | 1311, 1326 |
| Building_HasFreeAdjacentExitTile | `0xFFFF` | 1 | 1319 |
| Building_HasFreeAdjacentExitTile | `2` | 2 | 1320, 1324 |
| Building_UnitsLeave | `2` | 6 | 1357, 1372, 1376, 1380 ... |
| Building_UnitsLeave | `3` | 2 | 1357, 1395 |
| Building_UnitsLeave | `4` | 1 | 1358 |
| Building_UnitsLeave | `12` | 2 | 1363, 1378 |
| Building_UnitsLeave | `0xFFFF` | 1 | 1371 |
| Building_UnitsLeave | `0xFFFFFFFF` | 1 | 1385 |
| Building_UnitsLeave | `18` | 2 | 1400, 1405 |
| Building_UnitsLeave | `0x1Cu` | 1 | 1401 |
| Building_UnitsLeave | `28` | 1 | 1402 |
| Building_UnitsLeave | `14` | 1 | 1403 |
| Building_UnitsLeave | `30` | 1 | 1404 |
| Building_UnitsLeave | `10` | 1 | 1412 |
| Building_CountFreeGarrisonSlots | `10` | 1 | 1448 |
| Building_CountFreeGarrisonSlots | `12` | 1 | 1448 |
| Building_CountFreeGarrisonSlots | `4` | 1 | 1448 |
| Building_CountFreeGarrisonSlots | `18` | 1 | 1451 |

### src/buildings/0043E500_0043FDE0_buildings_006.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Building_UnitGetInto | `435` | 3 | 47, 48, 48 |
| Building_UnitGetInto | `7` | 1 | 47 |
| Building_UnitGetInto | `0xF8` | 1 | 48 |
| Building_UnitGetInto | `6` | 1 | 48 |
| Building_UnitGetInto | `4` | 2 | 50, 62 |
| Building_UnitGetInto | `100` | 4 | 57, 57, 69, 69 |
| Building_UnitGetInto | `438` | 1 | 57 |
| Building_UnitGetInto | `9` | 2 | 57, 69 |
| Building_UnitGetInto | `2` | 1 | 62 |
| Building_UnitGetInto | `0x0FFF` | 2 | 69, 71 |
| Building_UnitGetInto | `430` | 3 | 69, 70, 71 |
| Building_UnitGetInto | `0xF000` | 1 | 71 |
| Building_UnitGetInto | `12` | 1 | 96 |
| Building_UnitGetInto | `18` | 1 | 98 |
| Building_UnitGetInto | `463` | 1 | 118 |
| Building_CanAcceptUnitStack | `16` | 1 | 146 |
| Building_CanAcceptUnitStack | `4` | 1 | 148 |
| Building_CanAcceptUnitStack | `2` | 1 | 152 |
| Building_HasUnitLicence | `12` | 1 | 167 |
| Building_HasUnitLicence | `402` | 1 | 171 |
| Building_BuyUnitLicence | `2` | 2 | 195, 197 |
| Building_BuyUnitLicence | `140051` | 1 | 197 |
| Building_BuyUnitLicence | `140055` | 1 | 197 |
| Building_BuyUnitLicence | `100` | 1 | 198 |
| Building_BuyUnitLicence | `75` | 1 | 198 |
| Building_BuyUnitLicence | `438` | 2 | 199, 214 |
| Building_BuyUnitLicence | `402` | 2 | 203, 215 |
| Building_BuyUnitLicence | `12` | 2 | 207, 209 |
| Building_RemoveUnitLicence | `402` | 3 | 233, 237, 239 |
| Building_RemoveUnitLicence | `12` | 2 | 235, 243 |
| Building_SetUnitProduction | `2` | 1 | 257 |
| Building_SetUnitProduction | `402` | 1 | 258 |
| Building_SetUnitProduction | `140051` | 1 | 259 |
| Building_SetUnitProduction | `140055` | 1 | 260 |
| Building_TrainUnit | `3` | 2 | 288, 289 |
| Building_TrainUnit | `30` | 1 | 288 |
| Building_TrainUnit | `140051` | 1 | 292 |
| Building_TrainUnit | `2` | 3 | 292, 293, 295 |
| Building_TrainUnit | `4` | 3 | 293, 295, 295 |
| Building_TrainUnit | `0xF8` | 1 | 296 |
| Building_TrainUnit | `0xC7u` | 1 | 299 |
| Building_RepairUnit | `27` | 1 | 320 |
| Building_RepairUnit | `100` | 1 | 321 |
| Building_RepairUnit | `2` | 2 | 324, 324 |
| Building_RepairUnit | `4` | 1 | 324 |
| Building_RepairUnit | `0xC0` | 1 | 325 |
| Building_RepairUnit | `3` | 1 | 325 |
| Building_RepairUnit | `7` | 1 | 325 |
| Building_CountGarrison | `18` | 1 | 347 |
| Building_CountSpecialPersonageGarrisonEntries | `18` | 1 | 368 |
| Building_CountNonCombatGarrisonEntries | `18` | 1 | 407 |
| Building_HasSpecialPersonageGarrisonEntries | `18` | 1 | 438 |
| Building_CompactGarrison | `11` | 2 | 463, 469 |
| Building_CompactGarrison | `9` | 2 | 465, 482 |
| Building_CompactGarrison | `2` | 2 | 469, 469 |
| Building_CompactGarrison | `18` | 2 | 471, 473 |
| Building_CompactGarrison | `0x1Cu` | 1 | 476 |
| Building_CompactGarrison | `28` | 2 | 477, 478 |
| Building_IsUnitLicenceEligible | `4` | 1 | 509 |
| Building_IsUnitLicenceEligible | `2` | 1 | 513 |
| Building_IsUnitLicenceEligible | `444` | 1 | 516 |
| Building_IsUnitLicenceEligible | `7` | 1 | 516 |
| Building_IsUnitLicenceEligible | `416` | 2 | 518, 529 |
| Building_AdjustAllGarrisonMoraleByDelta | `18` | 1 | 547 |
| Building_CycleAllGarrisonOrdersOnce | `18` | 2 | 568, 576 |
| Building_GetTaxBurdenTier | `430` | 1 | 601 |
| Building_GetTaxBurdenTier | `0xFu` | 1 | 602 |
| Building_GetTaxBurdenTier | `0x1F4u` | 1 | 603 |
| Building_GetTaxBurdenTier | `0x3E8u` | 1 | 605 |
| Building_GetTaxBurdenTier | `2` | 1 | 606 |
| Building_GetTaxBurdenTier | `4` | 1 | 614 |
| Building_GetTaxBurdenTier | `0x3F` | 1 | 616 |
| Building_GetTaxBurdenTier | `436` | 1 | 616 |
| Building_GetTaxBurdenTier | `3` | 2 | 620, 621 |
| Building_UpdatePopulationGrowth | `16` | 2 | 641, 691 |
| Building_UpdatePopulationGrowth | `4` | 3 | 641, 660, 691 |
| Building_UpdatePopulationGrowth | `432` | 3 | 641, 686, 689 |
| Building_UpdatePopulationGrowth | `2` | 2 | 643, 681 |
| Building_UpdatePopulationGrowth | `3` | 3 | 645, 653, 669 |
| Building_UpdatePopulationGrowth | `434` | 3 | 646, 651, 674 |
| Building_UpdatePopulationGrowth | `100` | 4 | 647, 648, 685, 696 |
| Building_UpdatePopulationGrowth | `5` | 2 | 653, 657 |
| Building_UpdatePopulationGrowth | `10` | 1 | 663 |
| Building_UpdatePopulationGrowth | `15` | 1 | 663 |
| Building_UpdatePopulationGrowth | `416` | 2 | 668, 670 |
| Building_UpdatePopulationGrowth | `444` | 2 | 672, 673 |
| Building_UpdatePopulationGrowth | `7u` | 1 | 672 |
| Building_UpdatePopulationGrowth | `7` | 1 | 673 |
| Building_UpdatePopulationGrowth | `75` | 1 | 675 |
| Building_UpdatePopulationGrowth | `30` | 1 | 679 |
| Building_UpdatePopulationGrowth | `0x0FFF` | 4 | 684, 687, 692, 697 |
| Building_UpdatePopulationGrowth | `430` | 4 | 684, 688, 693, 698 |
| Building_UpdatePopulationGrowth | `0xF000` | 2 | 686, 688 |
| Building_UpdatePopulationGrowth | `2000` | 2 | 694, 696 |
| Building_CollectGoldIncome | `140051` | 1 | 712 |
| Building_CollectGoldIncome | `2` | 3 | 712, 722, 723 |
| Building_CollectGoldIncome | `400` | 1 | 713 |
| Building_CollectGoldIncome | `200` | 1 | 715 |
| Building_CollectGoldIncome | `430` | 1 | 716 |
| Building_CollectGoldIncome | `0xFu` | 1 | 717 |
| Building_CollectGoldIncome | `0x3F` | 1 | 718 |
| Building_CollectGoldIncome | `436` | 1 | 718 |
| Building_CollectGoldIncome | `434` | 1 | 719 |
| Building_CollectGoldIncome | `25` | 1 | 720 |
| Building_CollectGoldIncome | `435` | 1 | 725 |
| Building_CollectGoldIncome | `7` | 1 | 725 |
| Building_CollectGoldIncome | `438` | 2 | 727, 729 |
| Building_CollectGoldIncome | `442` | 1 | 728 |
| Building_UpdatePlagueState | `435` | 5 | 746, 749, 750, 765 ... |
| Building_UpdatePlagueState | `7` | 2 | 746, 750 |
| Building_UpdatePlagueState | `0xF8` | 2 | 749, 765 |
| Building_UpdatePlagueState | `0x0FFF` | 3 | 751, 755, 759 |
| Building_UpdatePlagueState | `430` | 4 | 751, 754, 755, 759 |
| Building_UpdatePlagueState | `15` | 1 | 752 |
| Building_UpdatePlagueState | `25` | 1 | 752 |
| Building_UpdatePlagueState | `100` | 2 | 753, 763 |
| Building_UpdatePlagueState | `0xF000` | 1 | 754 |
| Building_UpdatePlagueState | `1000` | 1 | 760 |
| Building_UpdatePlagueState | `2000` | 1 | 762 |
| Building_UpdatePlagueState | `300` | 1 | 762 |
| Building_UpdatePlagueState | `5` | 1 | 766 |
| Building_GetTotalValue | `438` | 1 | 782 |
| Building_GetTotalValue | `430` | 1 | 783 |
| Building_GetTotalValue | `0xFu` | 1 | 784 |
| Building_GetTotalValue | `190` | 1 | 785 |
| Building_GetTotalValue | `29` | 1 | 785 |
| Building_GetTotalValue | `31` | 4 | 785, 786, 787, 788 |
| Building_GetTotalValue | `416` | 5 | 785, 786, 787, 788 ... |
| Building_GetTotalValue | `200` | 2 | 786, 789 |
| Building_GetTotalValue | `30` | 1 | 786 |
| Building_GetTotalValue | `230` | 1 | 787 |
| Building_GetTotalValue | `27` | 1 | 787 |
| Building_GetTotalValue | `28` | 1 | 788 |
| Building_GetTotalValue | `400` | 1 | 788 |
| Building_GetTotalValue | `12` | 1 | 793 |
| Building_GetTotalValue | `402` | 1 | 796 |
| AI_TickNationPostTurn | `509678` | 1 | 824 |
| AI_TickNationPostTurn | `2` | 1 | 825 |
| AI_TickNationPostTurn | `509676` | 1 | 825 |
| AI_TickNationPostTurn | `16` | 1 | 828 |
| AI_TickNationPostTurn | `4` | 2 | 828, 828 |
| AI_TickNationPostTurn | `100` | 1 | 837 |
| AI_TickNationPostTurn | `147178` | 1 | 840 |
| AI_TickNationPostTurn | `147180` | 2 | 840, 844 |
| AI_TickNationPostTurn | `147189` | 1 | 846 |
| Player_CalcAvailableStrongholdFunds | `509678` | 1 | 871 |
| Player_CalcAvailableStrongholdFunds | `2` | 1 | 872 |
| Player_CalcAvailableStrongholdFunds | `509676` | 1 | 872 |
| Player_CalcAvailableStrongholdFunds | `16` | 1 | 875 |
| Player_CalcAvailableStrongholdFunds | `4` | 2 | 875, 875 |
| Player_CalcAvailableStrongholdFunds | `510112` | 1 | 876 |
| Player_CalcAvailableStrongholdFunds | `100` | 1 | 881 |
| Player_SpendStrongholdFundsEvenly | `509678` | 2 | 904, 921 |
| Player_SpendStrongholdFundsEvenly | `2` | 2 | 905, 922 |
| Player_SpendStrongholdFundsEvenly | `509676` | 2 | 906, 925 |
| Player_SpendStrongholdFundsEvenly | `510112` | 4 | 907, 927, 933, 939 |
| BuildingSpriteCache_Reset | `13` | 1 | 959 |
| BuildingSpriteCache_Reset | `650` | 1 | 959 |
| BuildingSpriteCache_LoadEntry | `9` | 3 | 1007, 1022, 1053 |
| BuildingSpriteCache_LoadEntry | `5` | 8 | 1014, 1061, 1062, 1069 ... |
| BuildingSpriteCache_LoadEntry | `3` | 3 | 1025, 1041, 1043 |
| BuildingSpriteCache_LoadEntry | `12` | 1 | 1027 |
| BuildingSpriteCache_LoadEntry | `4` | 2 | 1027, 1034 |
| BuildingSpriteCache_LoadEntry | `32` | 1 | 1032 |
| BuildingSpriteCache_LoadEntry | `180` | 1 | 1037 |
| BuildingSpriteCache_LoadEntry | `36` | 1 | 1037 |
| BuildingSpriteCache_LoadEntry | `45` | 1 | 1037 |
| BuildingSpriteCache_LoadEntry | `8` | 1 | 1048 |
| BuildingSpriteCache_LoadEntry | `22` | 3 | 1058, 1066, 1074 |
| BuildingSpriteCache_LoadEntry | `2` | 1 | 1072 |
| BuildingSpriteCache_GetOrLoadEntry | `9` | 1 | 1106 |
| BuildingSpriteCache_GetOrLoadEntry | `5` | 1 | 1107 |
| BuildingSpriteCache_Clear | `13` | 2 | 1125, 1132 |
| BuildingSpriteCache_Clear | `650` | 2 | 1125, 1133 |
| BuildingSpriteCache_Clear | `5` | 2 | 1137, 1138 |
| BuildingSpriteCache_CountEntries | `13` | 1 | 1151 |
| BuildingSpriteCache_CountEntries | `650` | 1 | 1151 |
| MapTile_GetReligiousSiteCategory | `2` | 1 | 1188 |
| Temple_GenerateApproachTrack | `14` | 1 | 1229 |
| Temple_GenerateApproachTrack | `2` | 3 | 1231, 1232, 1243 |
| Temple_GenerateApproachTrack | `147176` | 1 | 1233 |
| Temple_SpawnGiftUnitGroup | `172` | 1 | 1267 |
| Temple_SpawnGiftUnitGroup | `5` | 1 | 1273 |
| Temple_SpawnGiftUnitGroup | `12` | 2 | 1274, 1293 |
| Temple_SpawnGiftUnitGroup | `16` | 2 | 1274, 1293 |
| Temple_SpawnGiftUnitGroup | `2` | 2 | 1274, 1293 |
| Temple_SpawnGiftUnitGroup | `58` | 1 | 1274 |
| Temple_SpawnGiftUnitGroup | `77` | 1 | 1274 |
| Temple_SpawnGiftUnitGroup | `95` | 1 | 1274 |
| Temple_SpawnGiftUnitGroup | `4` | 3 | 1277, 1282, 1301 |
| Temple_SpawnGiftUnitGroup | `6` | 2 | 1293, 1295 |
| Temple_SpawnGiftUnitGroup | `200` | 1 | 1318 |
| Temple_SpawnGiftGoldCargoStack | `4` | 1 | 1339 |
| Temple_SpawnGiftGoldCargoStack | `335` | 1 | 1340 |
| Temple_SpawnGiftGoldCargoStack | `100` | 4 | 1349, 1355, 1355, 1355 |
| Temple_SpawnGiftGoldCargoStack | `200` | 1 | 1364 |

### src/buildings/0043FEF0_00441BE0_buildings_007.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Temple_ShowOutcomePopup | `4112` | 1 | 45 |
| Temple_ShowOutcomePopup | `0x17u` | 1 | 51 |
| Temple_ShowOutcomePopup | `0x16u` | 2 | 52, 75 |
| Temple_ShowOutcomePopup | `6` | 3 | 53, 54, 105 |
| Temple_ShowOutcomePopup | `188` | 1 | 57 |
| Temple_ShowOutcomePopup | `149` | 1 | 61 |
| Temple_ShowOutcomePopup | `150` | 2 | 61, 66 |
| Temple_ShowOutcomePopup | `22` | 1 | 63 |
| Temple_ShowOutcomePopup | `46` | 3 | 64, 77, 92 |
| Temple_ShowOutcomePopup | `52` | 3 | 65, 79, 93 |
| Temple_ShowOutcomePopup | `23` | 1 | 76 |
| Temple_ShowOutcomePopup | `156` | 1 | 80 |
| Temple_ShowOutcomePopup | `285` | 1 | 94 |
| Temple_ShowOutcomePopup | `17` | 1 | 104 |
| Temple_ShowOutcomePopup | `210` | 1 | 105 |
| Temple_ShowOutcomePopup | `569` | 1 | 105 |
| Temple_ShowOutcomePopup | `70` | 1 | 105 |
| Temple_ShowOutcomePopup | `7` | 1 | 115 |
| Temple_ShowOutcomePopup | `0x96u` | 1 | 119 |
| Temple_ShowOutcomePopup | `2` | 1 | 122 |
| Temple_Random | `6` | 3 | 154, 155, 162 |
| Temple_ProcessGift | `100` | 4 | 203, 220, 233, 259 |
| Temple_ProcessGift | `200` | 7 | 204, 208, 240, 256 ... |
| Temple_ProcessGift | `20` | 2 | 207, 271 |
| Temple_ProcessGift | `3` | 3 | 215, 229, 245 |
| Temple_ProcessGift | `16` | 2 | 220, 233 |
| Temple_ProcessGift | `10` | 2 | 222, 237 |
| Temple_ProcessGift | `15` | 1 | 235 |
| Temple_ProcessGift | `2` | 2 | 248, 254 |
| Temple_ProcessGift | `4` | 4 | 259, 262, 265, 268 |
| Temple_ProcessGift | `50` | 2 | 265, 276 |
| Temple_ProcessGift | `300` | 1 | 268 |
| Temple_UnitGetInto | `3` | 5 | 321, 322, 323, 351 ... |
| Temple_UnitGetInto | `4` | 9 | 332, 349, 351, 352 ... |
| Temple_UnitGetInto | `140063` | 5 | 333, 350, 352, 393 ... |
| Temple_UnitGetInto | `140051` | 6 | 335, 340, 359, 391 ... |
| Temple_UnitGetInto | `2` | 14 | 353, 358, 358, 373 ... |
| Temple_UnitGetInto | `11` | 1 | 370 |
| Temple_UnitGetInto | `14` | 3 | 372, 434, 435 |
| Temple_UnitGetInto | `12` | 2 | 405, 409 |
| Temple_UnitGetInto | `16` | 2 | 405, 408 |
| Temple_UnitGetInto | `6` | 1 | 405 |
| Temple_UnitGetInto | `95` | 1 | 408 |
| Temple_UnitGetInto | `58` | 1 | 409 |
| Temple_UnitGetInto | `77` | 1 | 409 |
| Temple_UnitGetInto | `15` | 1 | 415 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `11` | 1 | 493 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `10` | 3 | 511, 523, 526 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `64` | 1 | 516 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `12` | 1 | 517 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `46` | 1 | 532 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `52` | 1 | 533 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `148` | 1 | 534 |
| Temple_OutcomePopup_HandleAcceptUnitsClick | `5` | 1 | 550 |
| RenderHook_DemoText | `188` | 1 | 587 |
| RenderHook_DemoText | `46` | 5 | 597, 615, 627, 632 ... |
| RenderHook_DemoText | `52` | 5 | 597, 615, 628, 633 ... |
| RenderHook_DemoText | `18` | 1 | 612 |
| RenderHook_DemoText | `5` | 6 | 614, 631, 634, 662 ... |
| RenderHook_DemoText | `50` | 1 | 634 |
| RenderHook_DemoText | `78` | 2 | 634, 664 |
| RenderHook_DemoText | `28` | 1 | 644 |
| RenderHook_DemoText | `3` | 2 | 646, 665 |
| RenderHook_DemoText | `49` | 1 | 649 |
| RenderHook_DemoText | `7` | 1 | 659 |
| RenderHook_DemoText | `32` | 1 | 663 |
| RenderHook_DemoText | `98` | 1 | 664 |
| RenderHook_DemoText | `10` | 1 | 672 |
| RenderHook_DemoText | `0x64u` | 1 | 676 |
| RenderHook_DemoText | `0xC8u` | 1 | 676 |
| RenderHook_DemoText | `2` | 1 | 679 |
| UI_DemoTextPresent | `100` | 3 | 716, 784, 784 |
| UI_DemoTextPresent | `4112` | 2 | 724, 737 |
| UI_DemoTextPresent | `18` | 4 | 733, 736, 771, 783 |
| UI_DemoTextPresent | `20` | 1 | 735 |
| UI_DemoTextPresent | `4` | 2 | 742, 768 |
| UI_DemoTextPresent | `40` | 2 | 745, 747 |
| UI_DemoTextPresent | `10` | 3 | 746, 748, 803 |
| UI_DemoTextPresent | `148` | 1 | 756 |
| UI_DemoTextPresent | `78` | 1 | 756 |
| UI_DemoTextPresent | `200` | 1 | 758 |
| UI_DemoTextPresent | `32` | 1 | 762 |
| UI_DemoTextPresent | `5` | 2 | 767, 770 |
| UI_DemoTextPresent | `64` | 1 | 776 |
| BattleMapFileName | `2` | 1 | 844 |
| BattleMapFileName | `4` | 1 | 845 |
| BattleMapFileName | `0xFFFF` | 2 | 846, 850 |
| BattleMapFileName | `7` | 3 | 846, 850, 856 |
| BattleMapFileName | `48` | 1 | 860 |
| Str_SwapAndConcatInPlace | `2` | 6 | 894, 896, 908, 910 ... |
| BattleMap_GetMoveSoundSurfaceClass | `2` | 1 | 961 |
| BattleMap_GetMoveSoundSurfaceClass | `40` | 1 | 961 |
| Sound_BuildMusicTrackPath | `28` | 1 | 980 |
| Sound_BuildMusicTrackPath | `2` | 6 | 991, 993, 1004, 1006 ... |
| Sound_PlayNamedSfxFile | `100` | 1 | 1040 |
| Sound_PlayNamedSfxFile | `2` | 4 | 1053, 1055, 1067, 1069 |
| Music_PlayMainMapTrack | `100` | 2 | 1095, 1096 |
| Music_PlayMainMapTrack | `2000` | 1 | 1119 |
| Music_PlayMainMapTrack | `64` | 1 | 1119 |
| Audio_PauseMusicAndPlayLoopedSound | `108` | 1 | 1149 |
| Audio_PauseMusicAndPlayLoopedSound | `2000` | 2 | 1153, 1155 |
| Audio_PauseMusicAndPlayLoopedSound | `64` | 1 | 1155 |
| Audio_ResumeMusicAndStopLoopedSound | `2000` | 1 | 1172 |
| Audio_ResumeMusicAndStopLoopedSound | `1000` | 1 | 1173 |
| Audio_ResumeMusicAndStopLoopedSound | `64` | 1 | 1173 |
| Audio_StopMusicWithFade | `1000` | 1 | 1195 |
| Audio_DuckMusicVolume | `1000` | 1 | 1207 |
| Audio_DuckMusicVolume | `16` | 1 | 1207 |
| Audio_RestoreMusicVolume | `1000` | 1 | 1216 |
| Audio_RestoreMusicVolume | `64` | 1 | 1216 |
| Audio_PlayUnitActivateSound | `5` | 1 | 1311 |
| Audio_PlayUnitActivateSound | `100` | 1 | 1312 |
| Audio_PlayUnitActivateSound | `2` | 4 | 1326, 1328, 1340, 1342 |
| Audio_PlayUnitActivateSound | `49` | 1 | 1345 |
| Audio_PlayUnitActivateSound | `50` | 1 | 1345 |
| Audio_PlayUnitActivateSound | `64` | 1 | 1346 |
| Audio_PlayUnitMoveOrderSound | `5` | 1 | 1366 |
| Audio_PlayUnitMoveOrderSound | `104` | 1 | 1367 |
| Audio_PlayUnitMoveOrderSound | `500` | 1 | 1371 |
| Audio_PlayUnitMoveOrderSound | `0x64u` | 1 | 1372 |
| Audio_PlayUnitMoveOrderSound | `2` | 4 | 1382, 1384, 1396, 1398 |
| Audio_PlayUnitMoveOrderSound | `49` | 1 | 1401 |
| Audio_PlayUnitMoveOrderSound | `50` | 1 | 1401 |
| Audio_PlayUnitMoveOrderSound | `64` | 1 | 1402 |
| Audio_PlayUnitRangedAttackSound | `100` | 1 | 1421 |
| Audio_PlayUnitRangedAttackSound | `2` | 4 | 1435, 1437, 1449, 1451 |
| Audio_PlayUnitRangedAttackSound | `64` | 1 | 1454 |

### src/buildings/00441C80_00441D20_buildings_008.cpp

Missing evidence: garrison/service subfields, building/Road overlay IDs and costs, tactical grids/score flags and sprite geometry. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Audio_PlayUnitHitSound | `100` | 1 | 21 |
| Audio_PlayUnitHitSound | `2` | 4 | 35, 37, 49, 51 |
| Audio_PlayUnitHitSound | `64` | 1 | 54 |
| Audio_PlayUnitDeathSound | `100` | 1 | 72 |
| Audio_PlayUnitDeathSound | `2` | 4 | 86, 88, 100, 102 |
| Audio_PlayUnitDeathSound | `64` | 1 | 105 |

### src/core/00401020_004011F0_core_001.cpp

Missing evidence: holder/array layouts, destructor flags and path/device protocols. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| DetectGameCDPath | `52` | 1 | 62 |
| DetectGameCDPath | `44` | 1 | 64 |
| DetectGameCDPath | `67` | 1 | 65 |
| DetectGameCDPath | `0x1Eu` | 1 | 66 |
| DetectGameCDPath | `5` | 1 | 71 |
| DetectGameCDPath | `0x5Au` | 1 | 73 |
| DetectGameCDPath | `2` | 2 | 86, 88 |

### src/core/004015A0_00401A00_core_001.cpp

Missing evidence: holder/array layouts, destructor flags and path/device protocols. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Str_ConstructHolderViaBaseCtor | `4` | 1 | 21 |
| Mem_ZeroFourByteGlobal | `2` | 1 | 44 |
| Mem_ZeroFourByteGlobal | `3` | 1 | 45 |
| PathEntryArray_ConstructCapacity256 | `256` | 1 | 52 |
| PathEntryArray_CopyConstruct | `4` | 2 | 68, 81 |
| PathEntryArray_CopyConstruct | `2` | 4 | 70, 70, 84, 99 |
| PathEntryArray_CopyConstruct | `3` | 6 | 71, 72, 81, 82 ... |
| PathEntryArray_CopyConstruct | `16` | 2 | 81, 97 |
| PathEntryArray_Destruct | `4` | 2 | 112, 120 |
| PathEntryArray_Destruct | `2` | 1 | 122 |
| PathEntryArray_DestructElements | `2` | 3 | 150, 167, 172 |
| PathEntryArray_DestructElements | `4` | 2 | 156, 162 |
| PathEntryArray_DestructElements | `12` | 1 | 161 |
| PathEntryArray_DestructElements | `16` | 1 | 165 |
| PathEntryArray_DestructElements | `3` | 1 | 173 |
| PathEntryArray_GrowByDelta | `3` | 7 | 195, 196, 196, 206 ... |
| PathEntryArray_GrowByDelta | `16` | 3 | 206, 216, 217 |
| PathEntryArray_GrowByDelta | `4` | 3 | 206, 213, 222 |
| PathEntryArray_GrowByDelta | `2` | 2 | 211, 224 |
| PathEntryArray_RemoveAt | `4` | 2 | 253, 261 |
| PathEntryArray_RemoveAt | `16` | 5 | 254, 267, 267, 270 ... |
| PathEntryArray_RemoveAt | `3` | 3 | 260, 274, 275 |
| PathEntryArray_RemoveAt | `2` | 3 | 265, 279, 281 |
| Mem_ZeroFieldOffset316 | `316` | 1 | 294 |
| Mem_ZeroFieldOffset316 | `79` | 1 | 296 |
| PathEntry_CopyConstruct | `2` | 2 | 304, 306 |
| PathEntry_CopyConstruct | `3` | 2 | 307, 307 |
| PathEntry_Destruct | `4` | 1 | 320 |
| PathEntry_Destruct | `2` | 1 | 329 |
| PathEntry_ConstructDefault | `4` | 3 | 353, 354, 355 |
| PathEntry_ConstructDefault | `12` | 1 | 355 |

### src/persistence/00441DC0_00443B60_persistence_001.cpp

Missing evidence: save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Audio_PlayUnitMeleeAttackSound | `100` | 1 | 29 |
| Audio_PlayUnitMeleeAttackSound | `2` | 4 | 43, 45, 57, 59 |
| Audio_PlayUnitMeleeAttackSound | `64` | 1 | 62 |
| Audio_PlayUnitShotSound | `100` | 1 | 80 |
| Audio_PlayUnitShotSound | `2` | 4 | 94, 96, 108, 110 |
| Audio_PlayUnitShotSound | `64` | 1 | 113 |
| Audio_PlayWorldMapUnitMoveSound | `100` | 3 | 145, 146, 224 |
| Audio_PlayWorldMapUnitMoveSound | `4` | 2 | 149, 157 |
| Audio_PlayWorldMapUnitMoveSound | `16` | 1 | 150 |
| Audio_PlayWorldMapUnitMoveSound | `2` | 10 | 175, 177, 246, 248 ... |
| Audio_PlayWorldMapUnitMoveSound | `49` | 2 | 184, 188 |
| Audio_PlayWorldMapUnitMoveSound | `0xB7` | 2 | 190, 213 |
| Audio_PlayWorldMapUnitMoveSound | `0x93` | 2 | 192, 204 |
| Audio_PlayWorldMapUnitMoveSound | `39` | 1 | 194 |
| Audio_PlayWorldMapUnitMoveSound | `116` | 1 | 200 |
| Audio_PlayWorldMapUnitMoveSound | `151` | 1 | 206 |
| Audio_PlayWorldMapUnitMoveSound | `112` | 1 | 207 |
| Audio_PlayWorldMapUnitMoveSound | `0xCA` | 2 | 215, 217 |
| Audio_PlayWorldMapUnitMoveSound | `0xCC` | 2 | 219, 221 |
| Audio_PlayWorldMapUnitMoveSound | `207` | 1 | 221 |
| Audio_PlayWorldMapUnitMoveSound | `185` | 1 | 233 |
| Audio_PlayWorldMapUnitMoveSound | `0xD` | 1 | 303 |
| Audio_PlayWorldMapUnitMoveSound | `0xE` | 1 | 305 |
| Audio_PlayWorldMapUnitMoveSound | `30406` | 1 | 306 |
| Audio_PlayWorldMapUnitMoveSound | `31336` | 1 | 312 |
| Audio_PlayBattleMapUnitMoveSound | `100` | 3 | 353, 354, 456 |
| Audio_PlayBattleMapUnitMoveSound | `4` | 2 | 357, 412 |
| Audio_PlayBattleMapUnitMoveSound | `16` | 1 | 358 |
| Audio_PlayBattleMapUnitMoveSound | `2` | 11 | 378, 380, 392, 394 ... |
| Audio_PlayBattleMapUnitMoveSound | `0xD` | 1 | 398 |
| Audio_PlayBattleMapUnitMoveSound | `0xE` | 1 | 400 |
| Audio_PlayBattleMapUnitMoveSound | `30406` | 1 | 401 |
| Audio_PlayBattleMapUnitMoveSound | `31336` | 1 | 407 |
| Audio_PlayBattleMapUnitMoveSound | `49` | 2 | 439, 444 |
| Audio_PlayBattleMapUnitMoveSound | `116` | 1 | 450 |
| Audio_PlayBattleMapUnitMoveSound | `112` | 1 | 462 |
| Audio_StopUnitMoveSound | `333` | 1 | 515 |
| Audio_PlayButtonSound | `100` | 1 | 534 |
| Audio_PlayButtonSound | `2` | 4 | 548, 550, 562, 564 |
| Audio_PlayButtonSound | `32` | 1 | 567 |
| Audio_PlayArtifactSound | `100` | 1 | 576 |
| Audio_PlayArtifactSound | `64` | 1 | 581 |
| Audio_PlaySoundEffectByName | `100` | 1 | 598 |
| Audio_PlaySoundEffectByName | `2` | 4 | 611, 613, 625, 627 |
| IO_QueryVTableStreamSize | `2` | 1 | 658 |
| FileSystem_ResolveReadPath | `100` | 1 | 670 |
| FileSystem_ResolveReadPath | `6` | 2 | 674, 680 |
| FileSystem_SetInstallRootPath | `2` | 2 | 703, 705 |
| FileSystem_MountArchiveAtIndex | `100` | 1 | 723 |
| FileSystem_MountArchiveAtIndex | `4` | 1 | 724 |
| FileSystem_MountArchiveAtIndex | `2` | 2 | 741, 741 |
| FileSystem_MountArchiveAtIndex | `3` | 2 | 742, 742 |
| ResourceArchives_MountStartupArchives | `3` | 1 | 762 |
| ResourceArchives_MountStartupArchives | `4` | 1 | 763 |
| ResourceArchives_MountStartupArchives | `2` | 5 | 765, 785, 807, 821 ... |
| ResourceArchives_MountStartupArchives | `0x14u` | 1 | 766 |
| loadFileSusp | `0x80000` | 3 | 841, 854, 858 |
| loadFileSusp | `4` | 1 | 841 |
| Port_FindAndInit | `14` | 2 | 893, 913 |
| Port_FindAndInit | `2` | 2 | 901, 914 |
| Port_FindAndInit | `716` | 1 | 902 |
| Port_FindAndInit | `726` | 2 | 902, 915 |
| Port_FindAndInit | `10` | 1 | 911 |
| Port_FindAndInit | `8` | 1 | 911 |
| Port_FindAndInit | `3` | 1 | 912 |
| Port_FindAndInit | `5` | 1 | 912 |
| Port_FindAndInit | `722` | 1 | 915 |
| Port_FindAndInit | `715` | 2 | 918, 924 |
| Rules_LogPortLocation | `204` | 1 | 942 |
| Port_NewTurn | `3` | 1 | 977 |
| Port_NewTurn | `5` | 1 | 977 |
| Port_UpdateShorelineVariantTiles | `14` | 4 | 1017, 1038, 1053, 1074 |
| Port_UpdateShorelineVariantTiles | `2` | 10 | 1021, 1024, 1027, 1030 ... |
| Port_UpdateShorelineVariantTiles | `0x2D0` | 1 | 1023 |
| Port_UpdateShorelineVariantTiles | `718` | 1 | 1024 |
| Port_UpdateShorelineVariantTiles | `0x2D1` | 1 | 1026 |
| Port_UpdateShorelineVariantTiles | `719` | 1 | 1027 |
| Port_UpdateShorelineVariantTiles | `0x2D6` | 1 | 1029 |
| Port_UpdateShorelineVariantTiles | `722` | 1 | 1030 |
| Port_UpdateShorelineVariantTiles | `0x2D7` | 1 | 1032 |
| Port_UpdateShorelineVariantTiles | `724` | 1 | 1033 |
| Port_UpdateShorelineVariantTiles | `0x2CE` | 1 | 1059 |
| Port_UpdateShorelineVariantTiles | `720` | 1 | 1060 |
| Port_UpdateShorelineVariantTiles | `0x2CF` | 1 | 1062 |
| Port_UpdateShorelineVariantTiles | `721` | 1 | 1063 |
| Port_UpdateShorelineVariantTiles | `0x2D2` | 1 | 1065 |
| Port_UpdateShorelineVariantTiles | `726` | 1 | 1066 |
| Port_UpdateShorelineVariantTiles | `0x2D4` | 1 | 1068 |
| Port_UpdateShorelineVariantTiles | `727` | 1 | 1069 |
| Port_GenerateApproachTrack | `14` | 7 | 1134, 1137, 1139, 1142 ... |
| Port_GenerateApproachTrack | `147176` | 1 | 1147 |
| Port_GenerateApproachTrack | `100` | 2 | 1161, 1193 |
| Port_CollectReinforcementShipment | `200` | 5 | 1264, 1265, 1292, 1295 ... |
| Port_CollectReinforcementShipment | `2` | 7 | 1265, 1267, 1267, 1270 ... |
| Port_CollectReinforcementShipment | `0x1F4u` | 1 | 1276 |
| Port_CollectReinforcementShipment | `0x28` | 1 | 1279 |
| Port_CollectReinforcementShipment | `6` | 1 | 1279 |
| Port_CollectReinforcementShipment | `147178` | 1 | 1280 |
| Port_CollectReinforcementShipment | `12` | 2 | 1301, 1312 |
| Port_CollectReinforcementShipment | `0xFFFF` | 1 | 1305 |
| Port_CollectReinforcementShipment | `145` | 1 | 1320 |
| Port_CollectReinforcementShipment | `31` | 1 | 1324 |
| Port_CollectReinforcementShipment | `11` | 1 | 1327 |
| Port_CollectReinforcementShipment | `10` | 1 | 1335 |
| Port_CollectReinforcementShipment | `8` | 1 | 1335 |
| UI_DrawPortStatusPanel | `3` | 3 | 1380, 1381, 1424 |
| UI_DrawPortStatusPanel | `4112` | 1 | 1390 |
| UI_DrawPortStatusPanel | `100` | 3 | 1394, 1395, 1396 |
| UI_DrawPortStatusPanel | `188` | 1 | 1396 |
| UI_DrawPortStatusPanel | `7` | 1 | 1408 |
| UI_DrawPortStatusPanel | `46` | 1 | 1410 |
| UI_DrawPortStatusPanel | `52` | 1 | 1410 |
| UI_DrawPortStatusPanel | `2` | 6 | 1420, 1427, 1427, 1430 ... |
| UI_DrawPortStatusPanel | `10` | 1 | 1424 |
| UI_DrawPortStatusPanel | `235` | 1 | 1424 |
| UI_DrawPortStatusPanel | `5` | 1 | 1424 |
| UI_DrawPortStatusPanel | `122` | 1 | 1433 |
| UI_DrawPortStatusPanel | `200` | 1 | 1433 |
| UI_DrawPortStatusPanel | `54` | 1 | 1433 |
| UI_DrawPortStatusPanel | `6` | 2 | 1433, 1444 |
| UI_DrawPortStatusPanel | `15` | 1 | 1434 |
| UI_DrawPortStatusPanel | `29` | 1 | 1435 |
| UI_DrawPortStatusPanel | `42` | 1 | 1435 |
| UI_DrawPortStatusPanel | `85` | 1 | 1435 |
| UI_DrawPortStatusPanel | `40` | 2 | 1441, 1443 |
| UI_DrawPortStatusPanel | `120` | 1 | 1442 |

### src/persistence/00443BB0_00445CE0_persistence_002.cpp

Missing evidence: save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| MapTile_HasHiddenTreasure | `752` | 1 | 24 |
| MapTile_HasHiddenTreasure | `755` | 1 | 24 |
| Treasure_TryDigHere | `24` | 4 | 49, 80, 86, 89 |
| Treasure_TryDigHere | `40` | 1 | 50 |
| Treasure_TryDigHere | `147176` | 1 | 71 |
| Treasure_TryDigHere | `7` | 1 | 76 |
| Treasure_TryDigHere | `14` | 1 | 77 |
| Treasure_TryDigHere | `27` | 1 | 77 |
| Treasure_TryDigHere | `35` | 1 | 77 |
| Treasure_TryDigHere | `45` | 1 | 77 |
| Treasure_TryDigHere | `50` | 2 | 77, 84 |
| Treasure_TryDigHere | `55` | 1 | 77 |
| Treasure_TryDigHere | `63` | 1 | 77 |
| Treasure_TryDigHere | `68` | 1 | 77 |
| Treasure_TryDigHere | `0x18u` | 1 | 79 |
| Treasure_TryDigHere | `17` | 1 | 83 |
| Treasure_TryDigHere | `34` | 2 | 84, 85 |
| Treasure_TryDigHere | `51` | 1 | 84 |
| Treasure_TryDigHere | `73` | 1 | 84 |
| Treasure_TryDigHere | `77` | 1 | 85 |
| Treasure_TryDigHere | `49` | 1 | 86 |
| Treasure_TryDigHere | `140051` | 2 | 94, 118 |
| Treasure_TryDigHere | `4` | 3 | 94, 118, 130 |
| Treasure_TryDigHere | `15` | 1 | 121 |
| Treasure_TryDigHere | `2` | 1 | 121 |
| Treasure_TryDigHere | `3` | 1 | 121 |
| Treasure_TryDigHere | `0x2F0u` | 2 | 125, 127 |
| Treasure_TryDigHere | `755` | 1 | 129 |
| UnitStack_TryHide | `3` | 4 | 164, 165, 181, 240 |
| UnitStack_TryHide | `720` | 2 | 171, 247 |
| UnitStack_TryHide | `2` | 6 | 173, 179, 179, 196 ... |
| UnitStack_TryHide | `140051` | 3 | 175, 234, 248 |
| UnitStack_TryHide | `4` | 7 | 175, 203, 214, 214 ... |
| UnitStack_TryHide | `64` | 2 | 180, 239 |
| UnitStack_TryHide | `8` | 5 | 187, 190, 194, 224 ... |
| UnitStack_TryHide | `0xFFFF` | 1 | 197 |
| UnitStack_TryHide | `0x1F4u` | 1 | 199 |
| UnitStack_TryHide | `0x28` | 1 | 202 |
| UnitStack_TryHide | `6` | 1 | 202 |
| UnitStack_TryHide | `147178` | 1 | 203 |
| UnitStack_TryHide | `0x64` | 1 | 209 |
| UnitStack_TryHide | `16` | 1 | 215 |
| UnitStack_TryHide | `509676` | 1 | 216 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `0x1F4` | 4 | 274, 307, 331, 345 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `0x28` | 4 | 277, 310, 334, 347 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `3` | 4 | 277, 281, 310, 334 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `720` | 4 | 312, 314, 336, 340 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `2` | 1 | 322 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `24` | 1 | 322 |
| UnitStack_RevealHiddenEnemiesAndAttackAdjacent | `6` | 1 | 347 |
| saveGame | `120` | 1 | 384 |
| saveGame | `16` | 1 | 390 |
| saveGame | `2` | 1 | 397 |
| SaveSlot_LoadGame | `120` | 1 | 415 |
| SaveSlot_LoadGame | `16` | 2 | 428, 472 |
| SaveSlot_LoadGame | `0x28` | 1 | 439 |
| SaveSlot_LoadGame | `147180` | 2 | 439, 446 |
| SaveSlot_LoadGame | `147176` | 1 | 448 |
| SaveSlot_LoadGame | `147178` | 1 | 449 |
| SaveSlot_LoadGame | `10` | 2 | 452, 464 |
| SaveSlot_LoadGame | `147198` | 1 | 454 |
| SaveSlot_LoadGame | `6` | 1 | 463 |
| SaveSlot_LoadGame | `100` | 1 | 469 |
| SaveSlot_LoadGame | `4` | 2 | 472, 472 |
| SaveSlot_LoadLabelOrPlaceholder | `108` | 1 | 516 |
| SaveSlot_LoadLabelOrPlaceholder | `16` | 2 | 522, 523 |
| SaveSlot_LoadLabelOrPlaceholder | `2` | 2 | 536, 538 |
| SaveSlot_HasDataFile | `104` | 1 | 551 |
| SaveSlotDialog_RepaintRow | `20` | 1 | 577 |
| SaveSlotDialog_RepaintRow | `2` | 2 | 593, 595 |
| SaveSlotDialog_RepaintRow | `157` | 1 | 604 |
| SaveSlotDialog_RepaintRow | `22` | 3 | 604, 605, 615 |
| SaveSlotDialog_RepaintRow | `137` | 2 | 605, 615 |
| SaveSlotDialog_RepaintRow | `0x1A4u` | 2 | 606, 607 |
| SaveSlotDialog_RepaintRow | `0xF4u` | 2 | 606, 607 |
| SaveSlotDialog_RepaintRow | `244` | 2 | 607, 615 |
| SaveSlotDialog_RepaintRow | `18` | 1 | 609 |
| SaveSlotDialog_RepaintRow | `21` | 1 | 611 |
| SaveSlotDialog_RepaintRow | `3` | 1 | 615 |
| SaveSlotDialog_RepaintRow | `410` | 1 | 615 |
| SaveSlotDialog_Run | `40` | 1 | 709 |
| SaveSlotDialog_Run | `20` | 1 | 710 |
| SaveSlotDialog_Run | `4112` | 1 | 717 |
| SaveSlotDialog_Run | `46` | 2 | 733, 745 |
| SaveSlotDialog_Run | `52` | 2 | 733, 745 |
| SaveSlotDialog_Run | `51` | 2 | 734, 746 |
| SaveSlotDialog_Run | `10` | 1 | 755 |
| SaveSlotDialog_Run | `0x9Fu` | 1 | 757 |
| SaveSlotDialog_Run | `3` | 1 | 758 |
| SaveSlotDialog_Run | `16` | 1 | 759 |
| SaveSlotDialog_Run | `4` | 1 | 763 |
| SaveSlotDialog_Run | `17` | 1 | 765 |
| SaveSlotDialog_Run | `18` | 1 | 766 |
| SaveSlotDialog_Run | `2` | 3 | 766, 841, 843 |
| SaveSlotDialog_Run | `203` | 2 | 778, 785 |
| SaveSlotDialog_Run | `205` | 2 | 788, 792 |
| SaveSlotDialog_Run | `211` | 2 | 794, 802 |
| SaveSlotDialog_Run | `14` | 2 | 804, 814 |
| SaveSlotDialog_Run | `28` | 1 | 817 |
| SaveSlotDialog_Run | `0x10` | 1 | 828 |
| SaveSlotDialog_Run | `21` | 1 | 851 |
| SaveSlotDialog_Run | `0x97u` | 1 | 852 |
| SaveSlotDialog_Run | `244` | 1 | 872 |
| SaveSlotDialog_Run | `410` | 1 | 872 |
| SaveSlotDialog_Run | `142` | 2 | 874, 880 |
| SaveSlotDialog_Run | `22` | 2 | 874, 880 |
| SaveSlotDialog_Run | `9` | 1 | 875 |
| UI_ShowInfoWindow | `17` | 1 | 993 |
| UI_ShowInfoWindow | `4112` | 3 | 999, 1029, 1059 |
| UI_ShowInfoWindow | `2` | 9 | 1003, 1004, 1027, 1029 ... |
| UI_ShowInfoWindow | `3u` | 4 | 1003, 1004, 1005, 1006 |
| UI_ShowInfoWindow | `480` | 2 | 1003, 1033 |
| UI_ShowInfoWindow | `640` | 3 | 1004, 1034, 1068 |
| UI_ShowInfoWindow | `188` | 3 | 1007, 1037, 1072 |
| UI_ShowInfoWindow | `3` | 2 | 1021, 1025 |
| UI_ShowInfoWindow | `46` | 3 | 1022, 1052, 1082 |
| UI_ShowInfoWindow | `18` | 1 | 1025 |
| UI_ShowInfoWindow | `2u` | 4 | 1033, 1034, 1035, 1036 |
| UI_ShowInfoWindow | `25` | 3 | 1054, 1054, 1054 |
| UI_ShowInfoWindow | `6` | 4 | 1054, 1067, 1069, 1084 |
| UI_ShowInfoWindow | `150` | 3 | 1062, 1076, 1079 |
| UI_ShowInfoWindow | `0x17u` | 1 | 1064 |
| UI_ShowInfoWindow | `0x16u` | 2 | 1066, 1080 |
| UI_ShowInfoWindow | `0x280u` | 1 | 1072 |
| UI_ShowInfoWindow | `149` | 1 | 1076 |
| UI_ShowInfoWindow | `22` | 1 | 1078 |
| UI_ShowInfoWindow | `23` | 1 | 1081 |
| UI_ShowInfoWindow | `156` | 1 | 1083 |
| UI_ShowInfoWindow | `210` | 1 | 1084 |
| UI_ShowInfoWindow | `569` | 1 | 1084 |
| UI_ShowInfoWindow | `70` | 1 | 1084 |
| UI_ShowInfoWindow | `32` | 1 | 1096 |
| WorldMap_NotifyPlagueOutbreak | `256` | 1 | 1125 |
| WorldMap_NotifyPlagueOutbreak | `8` | 1 | 1126 |
| WorldMap_NotifyPlagueOutbreak | `6` | 1 | 1129 |
| WorldMap_NotifyPlagueOutbreak | `2` | 2 | 1133, 1133 |
| WorldMap_NotifyPlagueOutbreak | `5` | 2 | 1137, 1146 |
| WorldMap_NotifyPlagueOutbreak | `510109` | 1 | 1137 |
| WorldMap_NotifyPlagueOutbreak | `7` | 1 | 1137 |
| WorldMap_NotifyPlagueOutbreak | `509676` | 1 | 1139 |
| WorldMap_NotifyPlagueOutbreak | `3` | 2 | 1148, 1148 |
| UI_ShowTechnologyLevelUpIfChanged | `6` | 1 | 1170 |
| UI_ShowTechnologyLevelUpIfChanged | `2` | 2 | 1174, 1174 |
| UI_ShowTechnologyLevelUpIfChanged | `3` | 2 | 1178, 1178 |
| UI_CheatEditRepaint | `200` | 3 | 1198, 1201, 1204 |
| UI_CheatEditRepaint | `440` | 2 | 1198, 1204 |
| UI_CheatEditRepaint | `0x104u` | 2 | 1200, 1201 |
| UI_CheatEditRepaint | `0x122u` | 2 | 1200, 1201 |
| UI_CheatEditRepaint | `0x1B8u` | 1 | 1201 |
| UI_CheatEditRepaint | `0xC8u` | 1 | 1201 |
| UI_CheatEditRepaint | `260` | 2 | 1201, 1204 |
| UI_CheatEditRepaint | `22` | 1 | 1202 |
| UI_CheatEditRepaint | `3` | 1 | 1204 |
| Building_ShowConstructionFinishedDialog | `3` | 3 | 1254, 1255, 1403 |
| Building_ShowConstructionFinishedDialog | `2` | 10 | 1272, 1272, 1275, 1275 ... |
| Building_ShowConstructionFinishedDialog | `5` | 2 | 1277, 1421 |
| Building_ShowConstructionFinishedDialog | `4112` | 1 | 1291 |
| Building_ShowConstructionFinishedDialog | `0x17u` | 1 | 1298 |
| Building_ShowConstructionFinishedDialog | `0x16u` | 2 | 1299, 1321 |
| Building_ShowConstructionFinishedDialog | `6` | 4 | 1300, 1301, 1324, 1338 |
| Building_ShowConstructionFinishedDialog | `188` | 1 | 1304 |
| Building_ShowConstructionFinishedDialog | `22` | 1 | 1310 |
| Building_ShowConstructionFinishedDialog | `46` | 2 | 1311, 1323 |
| Building_ShowConstructionFinishedDialog | `52` | 2 | 1311, 1323 |
| Building_ShowConstructionFinishedDialog | `23` | 1 | 1322 |
| Building_ShowConstructionFinishedDialog | `17` | 1 | 1333 |
| Building_ShowConstructionFinishedDialog | `4` | 1 | 1334 |
| Building_ShowConstructionFinishedDialog | `569` | 1 | 1338 |
| Building_ShowConstructionFinishedDialog | `60` | 1 | 1338 |
| Building_ShowConstructionFinishedDialog | `70` | 1 | 1338 |
| Building_ShowConstructionFinishedDialog | `56` | 1 | 1339 |
| Building_ShowConstructionFinishedDialog | `0x104u` | 1 | 1340 |
| Building_ShowConstructionFinishedDialog | `0x122u` | 1 | 1340 |
| Building_ShowConstructionFinishedDialog | `0x1B8u` | 1 | 1340 |
| Building_ShowConstructionFinishedDialog | `0xC8u` | 1 | 1340 |
| Building_ShowConstructionFinishedDialog | `200` | 1 | 1340 |
| Building_ShowConstructionFinishedDialog | `260` | 1 | 1340 |
| Building_ShowConstructionFinishedDialog | `203` | 2 | 1348, 1352 |
| Building_ShowConstructionFinishedDialog | `205` | 2 | 1354, 1363 |
| Building_ShowConstructionFinishedDialog | `211` | 2 | 1366, 1373 |
| Building_ShowConstructionFinishedDialog | `14` | 2 | 1375, 1383 |
| Building_ShowConstructionFinishedDialog | `28` | 1 | 1385 |
| Building_ShowConstructionFinishedDialog | `0xA` | 1 | 1396 |

### src/persistence/00446230_00447840_persistence_003.cpp

Missing evidence: save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Demo_ShowNumberedTextScreen | `100` | 1 | 51 |
| Demo_ShowNumberedTextScreen | `4112` | 1 | 62 |
| Demo_ShowNumberedTextScreen | `188` | 1 | 66 |
| Demo_ShowNumberedTextScreen | `46` | 1 | 80 |
| Demo_ShowNumberedTextScreen | `52` | 1 | 81 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `4` | 1 | 175 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `8` | 1 | 176 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `12` | 1 | 177 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `16` | 1 | 178 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `20` | 1 | 179 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `24` | 1 | 180 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `28` | 1 | 181 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `32` | 1 | 182 |
| QueenMarriageProposal_WriteButtonWidgetRecord | `49` | 1 | 183 |
| QueenMarriageProposal_RebuildButtonWidgets | `10` | 1 | 199 |
| QueenMarriageProposal_RebuildButtonWidgets | `12` | 1 | 200 |
| QueenMarriageProposal_RebuildButtonWidgets | `11` | 1 | 208 |
| QueenMarriageProposal_RebuildButtonWidgets | `13` | 1 | 209 |
| QueenMarriageProposal_RebuildButtonWidgets | `2` | 2 | 213, 214 |
| Queen_ShowWhimDecisionDialog | `40` | 1 | 231 |
| Queen_ShowWhimDecisionDialog | `17` | 2 | 252, 282 |
| Queen_ShowWhimDecisionDialog | `4112` | 1 | 254 |
| Queen_ShowWhimDecisionDialog | `2` | 2 | 258, 311 |
| Queen_ShowWhimDecisionDialog | `640` | 1 | 258 |
| Queen_ShowWhimDecisionDialog | `150` | 1 | 259 |
| Queen_ShowWhimDecisionDialog | `188` | 1 | 262 |
| Queen_ShowWhimDecisionDialog | `46` | 2 | 277, 280 |
| Queen_ShowWhimDecisionDialog | `18` | 2 | 281, 284 |
| Queen_ShowWhimDecisionDialog | `41` | 1 | 281 |
| Queen_ShowWhimDecisionDialog | `175` | 3 | 283, 290, 293 |
| Queen_ShowWhimDecisionDialog | `525` | 1 | 283 |
| Queen_ShowWhimDecisionDialog | `6` | 1 | 283 |
| Queen_ShowWhimDecisionDialog | `65` | 1 | 283 |
| Queen_ShowWhimDecisionDialog | `12` | 1 | 285 |
| Queen_ShowWhimDecisionDialog | `198` | 1 | 285 |
| Queen_ShowWhimDecisionDialog | `126` | 2 | 286, 289 |
| Queen_ShowWhimDecisionDialog | `207` | 1 | 286 |
| Queen_ShowWhimDecisionDialog | `3` | 2 | 286, 291 |
| Queen_ShowWhimDecisionDialog | `0x9Fu` | 1 | 288 |
| Queen_ShowWhimDecisionDialog | `13` | 1 | 292 |
| Queen_ShowWhimDecisionDialog | `451` | 1 | 292 |
| Queen_ShowWhimDecisionDialog | `14` | 1 | 293 |
| Queen_ShowWhimDecisionDialog | `16` | 1 | 294 |
| YesNoWindow_WriteButtonWidgetRecord | `4` | 1 | 347 |
| YesNoWindow_WriteButtonWidgetRecord | `8` | 1 | 348 |
| YesNoWindow_WriteButtonWidgetRecord | `12` | 1 | 349 |
| YesNoWindow_WriteButtonWidgetRecord | `16` | 1 | 350 |
| YesNoWindow_WriteButtonWidgetRecord | `20` | 1 | 351 |
| YesNoWindow_WriteButtonWidgetRecord | `24` | 1 | 352 |
| YesNoWindow_WriteButtonWidgetRecord | `28` | 1 | 353 |
| YesNoWindow_WriteButtonWidgetRecord | `32` | 1 | 354 |
| YesNoWindow_WriteButtonWidgetRecord | `49` | 1 | 355 |
| YesNoWindow_RebuildButtonWidgets | `5` | 1 | 364 |
| YesNoWindow_RebuildButtonWidgets | `6` | 1 | 365 |
| YesNoWindow_RebuildButtonWidgets | `7` | 1 | 371 |
| YesNoWindow_RebuildButtonWidgets | `8` | 1 | 372 |
| YesNoWindow_RebuildButtonWidgets | `2` | 2 | 374, 375 |
| YesNoWindow | `40` | 1 | 398 |
| YesNoWindow | `17` | 3 | 418, 420, 495 |
| YesNoWindow | `4112` | 1 | 423 |
| YesNoWindow | `1024` | 1 | 429 |
| YesNoWindow | `4` | 2 | 432, 457 |
| YesNoWindow | `8` | 1 | 432 |
| YesNoWindow | `2` | 2 | 439, 492 |
| YesNoWindow | `4u` | 3 | 439, 441, 442 |
| YesNoWindow | `640` | 1 | 439 |
| YesNoWindow | `150` | 1 | 440 |
| YesNoWindow | `188` | 1 | 443 |
| YesNoWindow | `46` | 1 | 458 |
| YesNoWindow | `15` | 1 | 464 |
| YesNoWindow | `260` | 1 | 464 |
| YesNoWindow | `3` | 1 | 464 |
| YesNoWindow | `30` | 1 | 464 |
| YesNoWindow | `146` | 1 | 468 |
| YesNoWindow | `38` | 1 | 468 |
| YesNoWindow | `72` | 1 | 468 |
| UI_ShowSimpleTextInfoWindow | `17` | 2 | 543, 591 |
| UI_ShowSimpleTextInfoWindow | `4112` | 1 | 545 |
| UI_ShowSimpleTextInfoWindow | `2` | 2 | 549, 550 |
| UI_ShowSimpleTextInfoWindow | `640` | 1 | 549 |
| UI_ShowSimpleTextInfoWindow | `9u` | 2 | 549, 550 |
| UI_ShowSimpleTextInfoWindow | `480` | 1 | 550 |
| UI_ShowSimpleTextInfoWindow | `4u` | 2 | 551, 552 |
| UI_ShowSimpleTextInfoWindow | `188` | 1 | 553 |
| UI_ShowSimpleTextInfoWindow | `9` | 1 | 569 |
| UI_ShowSimpleTextInfoWindow | `46` | 2 | 570, 589 |
| UI_ShowSimpleTextInfoWindow | `52` | 1 | 571 |
| UI_ShowSimpleTextInfoWindow | `25` | 2 | 581, 581 |
| UI_ShowSimpleTextInfoWindow | `250` | 1 | 581 |
| UI_ShowSimpleTextInfoWindow | `3` | 1 | 581 |
| UI_ShowSimpleTextInfoWindow | `34` | 1 | 581 |
| Queen_ShowMarriageProposalDialog | `40` | 1 | 619 |
| Queen_ShowMarriageProposalDialog | `3` | 1 | 620 |
| Queen_ShowMarriageProposalDialog | `17` | 3 | 654, 658, 811 |
| Queen_ShowMarriageProposalDialog | `4112` | 1 | 662 |
| Queen_ShowMarriageProposalDialog | `1025` | 1 | 671 |
| Queen_ShowMarriageProposalDialog | `1024` | 1 | 672 |
| Queen_ShowMarriageProposalDialog | `2` | 6 | 673, 714, 734, 745 ... |
| Queen_ShowMarriageProposalDialog | `640` | 1 | 673 |
| Queen_ShowMarriageProposalDialog | `150` | 2 | 674, 683 |
| Queen_ShowMarriageProposalDialog | `188` | 1 | 683 |
| Queen_ShowMarriageProposalDialog | `14` | 2 | 715, 735 |
| Queen_ShowMarriageProposalDialog | `18` | 2 | 736, 741 |
| Queen_ShowMarriageProposalDialog | `41` | 2 | 736, 740 |
| Queen_ShowMarriageProposalDialog | `175` | 3 | 752, 756, 764 |
| Queen_ShowMarriageProposalDialog | `525` | 1 | 752 |
| Queen_ShowMarriageProposalDialog | `55` | 2 | 752, 757 |
| Queen_ShowMarriageProposalDialog | `6` | 1 | 752 |
| Queen_ShowMarriageProposalDialog | `126` | 1 | 763 |
| Queen_ShowMarriageProposalDialog | `451` | 1 | 765 |
| Queen_ShowMarriageProposalDialog | `0x9F` | 1 | 771 |
| Queen_ShowMarriageProposalDialog | `13` | 1 | 778 |
| Queen_ShowMessageDialog | `17` | 2 | 862, 914 |
| Queen_ShowMessageDialog | `4112` | 1 | 864 |
| Queen_ShowMessageDialog | `2` | 1 | 868 |
| Queen_ShowMessageDialog | `640` | 1 | 868 |
| Queen_ShowMessageDialog | `188` | 1 | 871 |
| Queen_ShowMessageDialog | `149` | 1 | 875 |
| Queen_ShowMessageDialog | `150` | 3 | 875, 879, 900 |
| Queen_ShowMessageDialog | `14` | 1 | 877 |
| Queen_ShowMessageDialog | `46` | 3 | 878, 889, 912 |
| Queen_ShowMessageDialog | `52` | 2 | 878, 890 |
| Queen_ShowMessageDialog | `168` | 1 | 891 |
| Queen_ShowMessageDialog | `175` | 1 | 900 |
| Queen_ShowMessageDialog | `205` | 1 | 900 |
| Queen_ShowMessageDialog | `525` | 1 | 900 |
| Queen_ShowMessageDialog | `6` | 1 | 900 |
| Queen_ShowMessageDialog | `0x96u` | 1 | 909 |
| UI_ShowMissionStatusPanel | `100` | 1 | 935 |
| UI_ShowMissionStatusPanel | `7` | 1 | 936 |
| UI_ShowMissionStatusPanel | `6` | 1 | 938 |
| UI_ShowMissionStatusPanel | `2` | 2 | 941, 941 |
| UI_ShowMissionStatusPanel | `10` | 1 | 949 |
| UI_ShowMissionStatusPanel | `3` | 2 | 950, 951 |
| UI_ShowMissionStatusPanel | `2u` | 1 | 951 |
| Object_ConstructInt256Array | `256` | 1 | 971 |
| MainMenu_WriteButtonWidgetTemplateRecord | `4` | 1 | 1000 |
| MainMenu_WriteButtonWidgetTemplateRecord | `8` | 1 | 1001 |
| MainMenu_WriteButtonWidgetTemplateRecord | `12` | 1 | 1002 |
| MainMenu_WriteButtonWidgetTemplateRecord | `16` | 1 | 1003 |
| MainMenu_WriteButtonWidgetTemplateRecord | `20` | 1 | 1004 |
| MainMenu_WriteButtonWidgetTemplateRecord | `24` | 1 | 1005 |
| MainMenu_WriteButtonWidgetTemplateRecord | `28` | 1 | 1006 |
| MainMenu_WriteButtonWidgetTemplateRecord | `32` | 1 | 1007 |
| MainMenu_WriteButtonWidgetTemplateRecord | `49` | 1 | 1008 |
| CampaignMenu_WriteButtonWidgetTemplateRecord | `28` | 1 | 1028 |
| MainMenu_RebuildButtonWidgetTemplate | `159` | 1 | 1044 |
| MainMenu_RebuildButtonWidgetTemplate | `136` | 2 | 1045, 1069 |
| MainMenu_RebuildButtonWidgetTemplate | `3` | 2 | 1047, 1067 |
| MainMenu_RebuildButtonWidgetTemplate | `152` | 1 | 1052 |
| MainMenu_RebuildButtonWidgetTemplate | `168` | 2 | 1053, 1077 |
| MainMenu_RebuildButtonWidgetTemplate | `6` | 2 | 1054, 1090 |
| MainMenu_RebuildButtonWidgetTemplate | `9` | 1 | 1055 |
| MainMenu_RebuildButtonWidgetTemplate | `2` | 1 | 1059 |
| MainMenu_RebuildButtonWidgetTemplate | `185` | 1 | 1060 |
| MainMenu_RebuildButtonWidgetTemplate | `204` | 2 | 1061, 1085 |
| MainMenu_RebuildButtonWidgetTemplate | `12` | 1 | 1062 |
| MainMenu_RebuildButtonWidgetTemplate | `15` | 1 | 1063 |
| MainMenu_RebuildButtonWidgetTemplate | `357` | 1 | 1068 |
| MainMenu_RebuildButtonWidgetTemplate | `18` | 1 | 1070 |
| MainMenu_RebuildButtonWidgetTemplate | `21` | 1 | 1071 |
| MainMenu_RebuildButtonWidgetTemplate | `4` | 1 | 1075 |
| MainMenu_RebuildButtonWidgetTemplate | `344` | 1 | 1076 |
| MainMenu_RebuildButtonWidgetTemplate | `24` | 1 | 1078 |
| MainMenu_RebuildButtonWidgetTemplate | `27` | 1 | 1079 |
| MainMenu_RebuildButtonWidgetTemplate | `5` | 1 | 1083 |
| MainMenu_RebuildButtonWidgetTemplate | `388` | 1 | 1084 |
| MainMenu_RebuildButtonWidgetTemplate | `30` | 1 | 1086 |
| MainMenu_RebuildButtonWidgetTemplate | `33` | 1 | 1087 |
| CampaignMenu_RebuildButtonWidgetTemplate | `152` | 1 | 1106 |
| CampaignMenu_RebuildButtonWidgetTemplate | `279` | 2 | 1107, 1115 |
| CampaignMenu_RebuildButtonWidgetTemplate | `384` | 1 | 1114 |
| CampaignMenu_RebuildButtonWidgetTemplate | `2` | 2 | 1116, 1120 |
| CampaignMenu_RebuildButtonWidgetTemplate | `3` | 1 | 1117 |
| LoadMenu_RebuildButtonWidgetTemplate | `249` | 1 | 1135 |
| LoadMenu_RebuildButtonWidgetTemplate | `392` | 1 | 1136 |
| LoadMenu_RebuildButtonWidgetTemplate | `329` | 1 | 1143 |
| LoadMenu_RebuildButtonWidgetTemplate | `408` | 1 | 1144 |
| LoadMenu_RebuildButtonWidgetTemplate | `2` | 2 | 1145, 1149 |
| LoadMenu_RebuildButtonWidgetTemplate | `3` | 1 | 1146 |
| Options_WriteSliderThumbRecord | `36` | 1 | 1167 |
| Options_WriteSliderThumbRecord | `4` | 1 | 1169 |
| Options_WriteSliderThumbRecord | `8` | 1 | 1170 |
| Options_WriteSliderThumbRecord | `12` | 1 | 1171 |
| Options_WriteSliderThumbRecord | `16` | 1 | 1172 |
| Options_WriteSliderThumbRecord | `20` | 1 | 1173 |
| Options_WriteSliderThumbRecord | `24` | 1 | 1174 |
| Options_WriteSliderThumbRecord | `28` | 2 | 1174, 1175 |
| Options_WriteSliderThumbRecord | `32` | 1 | 1176 |
| Options_RebuildMainMenuWidgetTemplates | `180` | 4 | 1198, 1206, 1214, 1222 |
| Options_RebuildMainMenuWidgetTemplates | `246` | 1 | 1199 |
| Options_RebuildMainMenuWidgetTemplates | `3` | 2 | 1200, 1221 |
| Options_RebuildMainMenuWidgetTemplates | `280` | 1 | 1207 |
| Options_RebuildMainMenuWidgetTemplates | `9` | 1 | 1208 |
| Options_RebuildMainMenuWidgetTemplates | `6` | 2 | 1209, 1244 |
| Options_RebuildMainMenuWidgetTemplates | `2` | 2 | 1213, 1263 |
| Options_RebuildMainMenuWidgetTemplates | `312` | 1 | 1215 |
| Options_RebuildMainMenuWidgetTemplates | `15` | 1 | 1216 |
| Options_RebuildMainMenuWidgetTemplates | `12` | 1 | 1217 |
| Options_RebuildMainMenuWidgetTemplates | `344` | 1 | 1223 |
| Options_RebuildMainMenuWidgetTemplates | `21` | 1 | 1224 |
| Options_RebuildMainMenuWidgetTemplates | `18` | 1 | 1225 |
| Options_RebuildMainMenuWidgetTemplates | `4` | 2 | 1229, 1260 |
| Options_RebuildMainMenuWidgetTemplates | `248` | 1 | 1230 |
| Options_RebuildMainMenuWidgetTemplates | `392` | 1 | 1231 |
| Options_RebuildMainMenuWidgetTemplates | `24` | 1 | 1232 |
| Options_RebuildMainMenuWidgetTemplates | `25` | 1 | 1233 |
| Options_RebuildMainMenuWidgetTemplates | `5` | 1 | 1237 |
| Options_RebuildMainMenuWidgetTemplates | `329` | 1 | 1238 |
| Options_RebuildMainMenuWidgetTemplates | `408` | 1 | 1239 |
| Options_RebuildMainMenuWidgetTemplates | `26` | 1 | 1240 |
| Options_RebuildMainMenuWidgetTemplates | `27` | 1 | 1241 |
| Options_RebuildMainMenuWidgetTemplates | `36` | 3 | 1255, 1262, 1263 |
| Options_RebuildMainMenuWidgetTemplates | `323` | 3 | 1256, 1262, 1263 |
| Options_RebuildMainMenuWidgetTemplates | `473` | 3 | 1257, 1262, 1263 |
| Options_RebuildMainMenuWidgetTemplates | `140` | 1 | 1258 |
| Options_RebuildMainMenuWidgetTemplates | `128` | 3 | 1259, 1262, 1263 |
| Options_RebuildMainMenuWidgetTemplates | `166` | 1 | 1262 |
| Options_RebuildMainMenuWidgetTemplates | `192` | 1 | 1263 |
| Options_RebuildMainMenuWidgetTemplates | `108` | 1 | 1264 |
| UI_WaitForAnyKeyOrClick | `57` | 1 | 1351 |
| UI_WaitForAnyKeyOrClick | `28` | 1 | 1352 |
| UI_StartAnims | `0x4B0u` | 1 | 1377 |
| UI_StartAnims | `2` | 2 | 1379, 1387 |

### src/persistence/004479C0_0044AE10_persistence_004.cpp

Missing evidence: save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| PlayGame_Dispatch | `7112` | 1 | 66 |
| PlayGame_Dispatch | `371` | 4 | 79, 86, 153, 516 |
| PlayGame_Dispatch | `268` | 1 | 87 |
| PlayGame_Dispatch | `40` | 1 | 88 |
| PlayGame_Dispatch | `160` | 1 | 89 |
| PlayGame_Dispatch | `5` | 7 | 90, 93, 248, 248 ... |
| PlayGame_Dispatch | `188` | 1 | 107 |
| PlayGame_Dispatch | `32` | 1 | 110 |
| PlayGame_Dispatch | `4112` | 5 | 124, 187, 258, 476 ... |
| PlayGame_Dispatch | `64` | 3 | 131, 570, 581 |
| PlayGame_Dispatch | `16` | 7 | 155, 540, 543, 571 ... |
| PlayGame_Dispatch | `20` | 6 | 156, 221, 242, 426 ... |
| PlayGame_Dispatch | `60` | 2 | 163, 164 |
| PlayGame_Dispatch | `1000` | 6 | 228, 234, 241, 431 ... |
| PlayGame_Dispatch | `0xA` | 3 | 235, 379, 408 |
| PlayGame_Dispatch | `3` | 1 | 249 |
| PlayGame_Dispatch | `2` | 11 | 252, 491, 527, 529 ... |
| PlayGame_Dispatch | `18` | 4 | 268, 373, 510, 606 |
| PlayGame_Dispatch | `21` | 3 | 269, 511, 607 |
| PlayGame_Dispatch | `265` | 1 | 276 |
| PlayGame_Dispatch | `176` | 1 | 288 |
| PlayGame_Dispatch | `236` | 1 | 289 |
| PlayGame_Dispatch | `129` | 2 | 290, 292 |
| PlayGame_Dispatch | `4` | 6 | 290, 304, 539, 540 ... |
| PlayGame_Dispatch | `53` | 3 | 290, 292, 303 |
| PlayGame_Dispatch | `6` | 1 | 294 |
| PlayGame_Dispatch | `239` | 1 | 301 |
| PlayGame_Dispatch | `339` | 1 | 301 |
| PlayGame_Dispatch | `144` | 1 | 303 |
| PlayGame_Dispatch | `203` | 2 | 320, 326 |
| PlayGame_Dispatch | `205` | 2 | 329, 336 |
| PlayGame_Dispatch | `11` | 17 | 331, 341, 343, 344 ... |
| PlayGame_Dispatch | `211` | 2 | 339, 347 |
| PlayGame_Dispatch | `14` | 2 | 349, 363 |
| PlayGame_Dispatch | `28` | 1 | 366 |
| PlayGame_Dispatch | `356` | 1 | 405 |
| PlayGame_Dispatch | `477` | 1 | 405 |
| PlayGame_Dispatch | `134` | 1 | 407 |
| PlayGame_Dispatch | `22` | 3 | 407, 627, 633 |
| PlayGame_Dispatch | `0x10` | 2 | 519, 520 |
| PlayGame_Dispatch | `0x14` | 1 | 521 |
| PlayGame_Dispatch | `0x21` | 1 | 523 |
| PlayGame_Dispatch | `212` | 1 | 525 |
| PlayGame_Dispatch | `0x08` | 2 | 527, 563 |
| PlayGame_Dispatch | `0x3D` | 2 | 529, 564 |
| PlayGame_Dispatch | `0x72` | 3 | 531, 565, 577 |
| PlayGame_Dispatch | `0xA7` | 2 | 533, 566 |
| PlayGame_Dispatch | `8` | 18 | 534, 536, 537, 538 ... |
| PlayGame_Dispatch | `0x4000` | 3 | 535, 536, 537 |
| PlayGame_Dispatch | `31` | 9 | 536, 537, 539, 540 ... |
| PlayGame_Dispatch | `7` | 5 | 536, 537, 537, 567 ... |
| PlayGame_Dispatch | `15` | 3 | 569, 573, 576 |
| PlayGame_Dispatch | `9` | 2 | 569, 628 |
| PlayGame_Dispatch | `12` | 2 | 573, 576 |
| PlayGame_Dispatch | `10` | 1 | 609 |
| PlayGame_Dispatch | `0x9Fu` | 1 | 612 |
| PlayGame_Dispatch | `244` | 1 | 625 |
| PlayGame_Dispatch | `410` | 1 | 625 |
| PlayGame_Dispatch | `155` | 2 | 627, 633 |
| MultiplayerSetup_RepaintPlayerSlotRow | `53` | 2 | 779, 793 |
| MultiplayerSetup_RepaintPlayerSlotRow | `11` | 2 | 780, 793 |
| MultiplayerSetup_RepaintPlayerSlotRow | `167` | 2 | 782, 783 |
| MultiplayerSetup_RepaintPlayerSlotRow | `144` | 2 | 784, 793 |
| MultiplayerSetup_RepaintPlayerSlotRow | `0x153u` | 1 | 785 |
| MultiplayerSetup_RepaintPlayerSlotRow | `0xEFu` | 1 | 785 |
| MultiplayerSetup_RepaintPlayerSlotRow | `0x15Du` | 1 | 786 |
| MultiplayerSetup_RepaintPlayerSlotRow | `0xEAu` | 1 | 786 |
| MultiplayerSetup_RepaintPlayerSlotRow | `234` | 1 | 786 |
| MultiplayerSetup_RepaintPlayerSlotRow | `18` | 1 | 787 |
| MultiplayerSetup_RepaintPlayerSlotRow | `5` | 1 | 792 |
| MultiplayerSetup_RepaintPlayerSlotRow | `239` | 1 | 793 |
| MultiplayerSetup_RepaintPlayerSlotRow | `3` | 1 | 793 |
| MultiplayerSetup_RepaintPlayerSlotRow | `339` | 1 | 793 |
| MultiplayerSetup_HandleStartButtonRelease | `5` | 4 | 815, 823, 826, 828 |
| MultiplayerSetup_HandleStartButtonRelease | `3` | 1 | 818 |
| MultiplayerSetup_HandleStartButtonRelease | `4` | 1 | 820 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `129` | 1 | 866 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `0x18Au` | 1 | 869 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `0x81u` | 1 | 869 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `0xB0u` | 1 | 869 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `0xECu` | 1 | 869 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `8` | 1 | 872 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `53` | 1 | 875 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `46` | 1 | 876 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `52` | 1 | 877 |
| MultiplayerSetup_RedrawPlayerSlotIcons | `5` | 1 | 888 |
| MultiplayerSetup_RedrawOpponentNameList | `0x164u` | 2 | 909, 915 |
| MultiplayerSetup_RedrawOpponentNameList | `0x175u` | 1 | 909 |
| MultiplayerSetup_RedrawOpponentNameList | `0x1DDu` | 2 | 909, 915 |
| MultiplayerSetup_RedrawOpponentNameList | `0x86u` | 1 | 909 |
| MultiplayerSetup_RedrawOpponentNameList | `134` | 1 | 910 |
| MultiplayerSetup_RedrawOpponentNameList | `22` | 2 | 915, 926 |
| MultiplayerSetup_RedrawOpponentNameList | `356` | 2 | 915, 923 |
| MultiplayerSetup_RedrawOpponentNameList | `20` | 1 | 916 |
| MultiplayerSetup_RedrawOpponentNameList | `21` | 1 | 919 |
| MultiplayerSetup_RedrawOpponentNameList | `18` | 1 | 921 |
| MultiplayerSetup_RedrawOpponentNameList | `13` | 2 | 923, 923 |
| MultiplayerSetup_RedrawOpponentNameList | `11` | 1 | 928 |
| MultiplayerSetup_HandleScrollListDownButton | `19` | 1 | 944 |
| Options_ApplyMainMenuSliders | `7` | 3 | 963, 964, 965 |
| Options_ApplyMainMenuSliders | `31` | 4 | 964, 965, 968, 969 |
| Options_ApplyMainMenuSliders | `8` | 6 | 964, 965, 965, 968 ... |
| Options_ApplyMainMenuSliders | `64` | 1 | 966 |
| Options_ApplyMainMenuSliders | `16` | 3 | 967, 968, 969 |
| Options_InitMainMenuSlidersAndWidgets | `2` | 6 | 1009, 1011, 1014, 1016 ... |
| Options_InitMainMenuSlidersAndWidgets | `98` | 2 | 1009, 1011 |
| Options_InitMainMenuSlidersAndWidgets | `106` | 1 | 1012 |
| Options_InitMainMenuSlidersAndWidgets | `151` | 2 | 1014, 1016 |
| Options_InitMainMenuSlidersAndWidgets | `159` | 1 | 1017 |
| Options_InitMainMenuSlidersAndWidgets | `204` | 2 | 1019, 1021 |
| Options_InitMainMenuSlidersAndWidgets | `212` | 1 | 1022 |
| Options_InitMainMenuSlidersAndWidgets | `257` | 2 | 1024, 1026 |
| Options_InitMainMenuSlidersAndWidgets | `265` | 1 | 1027 |
| Options_InitMainMenuSlidersAndWidgets | `128` | 3 | 1029, 1030, 1031 |
| Options_ToggleCheckboxMainMenu | `8` | 3 | 1047, 1048, 1049 |
| Options_ToggleCheckboxMainMenu | `2` | 1 | 1049 |
| Options_ToggleCheckboxMainMenu | `49` | 1 | 1050 |
| LoadMenu_RedrawSaveSlotRow | `20` | 1 | 1085 |
| LoadMenu_RedrawSaveSlotRow | `155` | 2 | 1091, 1099 |
| LoadMenu_RedrawSaveSlotRow | `22` | 5 | 1091, 1092, 1093, 1098 ... |
| LoadMenu_RedrawSaveSlotRow | `0x1A4u` | 2 | 1092, 1093 |
| LoadMenu_RedrawSaveSlotRow | `0xF4u` | 2 | 1092, 1093 |
| LoadMenu_RedrawSaveSlotRow | `175` | 3 | 1092, 1093, 1098 |
| LoadMenu_RedrawSaveSlotRow | `244` | 2 | 1093, 1099 |
| LoadMenu_RedrawSaveSlotRow | `18` | 1 | 1095 |
| LoadMenu_RedrawSaveSlotRow | `21` | 1 | 1097 |
| LoadMenu_RedrawSaveSlotRow | `3` | 1 | 1099 |
| LoadMenu_RedrawSaveSlotRow | `410` | 1 | 1099 |
| Options_DrawSliderThumb | `8` | 5 | 1137, 1145, 1166, 1171 ... |
| Options_DrawSliderThumb | `4` | 3 | 1139, 1167, 1172 |
| Options_DrawSliderThumb | `12` | 6 | 1141, 1143, 1159, 1161 ... |
| Options_DrawSliderThumb | `5` | 7 | 1141, 1143, 1159, 1161 ... |
| Options_DrawSliderThumb | `2` | 4 | 1142, 1160, 1174, 1192 |
| Options_DrawSliderThumb | `188` | 1 | 1156 |
| Options_DrawSliderThumb | `6` | 1 | 1180 |
| Options_DrawSliderThumb | `3` | 1 | 1191 |
| Options_DrawSliderThumb | `7` | 2 | 1198, 1199 |
| Options_AnimateSliderThumbDrag | `12` | 6 | 1226, 1247, 1255, 1265 ... |
| Options_AnimateSliderThumbDrag | `4` | 3 | 1226, 1244, 1264 |
| Options_AnimateSliderThumbDrag | `31` | 2 | 1227, 1227 |
| Options_AnimateSliderThumbDrag | `8` | 7 | 1227, 1227, 1227, 1229 ... |
| Options_AnimateSliderThumbDrag | `20` | 3 | 1231, 1237, 1243 |
| Options_AnimateSliderThumbDrag | `24` | 3 | 1231, 1238, 1243 |
| Options_AnimateSliderThumbDrag | `2` | 1 | 1244 |
| Options_AnimateSliderThumbDrag | `0x100` | 1 | 1245 |
| Options_AnimateSliderThumbDrag | `256` | 2 | 1270, 1272 |
| Options_DrawAllSliderThumbs | `36` | 2 | 1308, 1309 |
| Options_AnimateAllSliderThumbs | `36` | 2 | 1331, 1332 |
| Options_DestroySliderThumbList | `8` | 2 | 1352, 1357 |
| Options_DestroySliderThumbList | `2` | 1 | 1356 |
| Options_DestroySliderThumbList | `9` | 2 | 1358, 1359 |
| lodaOptionsCfg | `20` | 1 | 1381 |
| Options_SaveConfigToFile | `27` | 1 | 1401 |
| Options_ApplyRecordSettings | `260` | 1 | 1412 |
| Options_ApplyRecordSettings | `26` | 1 | 1415 |
| Options_ApplyRecordSettings | `0xDC` | 1 | 1423 |
| Options_ApplyRecordSettings | `1024` | 1 | 1423 |
| Options_ApplyRecordSettings | `20` | 2 | 1425, 1441 |
| Options_ApplyRecordSettings | `25` | 1 | 1425 |
| Options_ApplyRecordSettings | `8` | 1 | 1425 |
| Options_ApplyRecordSettings | `16` | 2 | 1428, 1433 |
| PlayerRuntimeState_ResetDefaults | `43` | 1 | 1459 |
| PlayerRuntimeState_ResetDefaults | `35` | 1 | 1460 |
| PlayerRuntimeState_ResetDefaults | `47` | 1 | 1461 |
| PlayerRuntimeState_ResetDefaults | `48` | 1 | 1462 |
| PlayerRuntimeState_ResetDefaults | `1417` | 1 | 1467 |
| PlayerRuntimeState_ResetDefaults | `60` | 1 | 1468 |
| PlayerRuntimeState_ResetDefaults | `6` | 1 | 1472 |
| PlayerRuntimeState_ResetDefaults | `1351` | 1 | 1473 |
| PlayerRuntimeState_ResetDefaults | `0x514u` | 1 | 1476 |

### src/persistence/0044AE90_0044E850_persistence_005.cpp

Missing evidence: save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Map_LoadFromFile | `100` | 5 | 60, 148, 157, 217 ... |
| Map_LoadFromFile | `0x13880` | 4 | 69, 97, 112, 127 |
| Map_LoadFromFile | `2` | 4 | 85, 87, 214, 226 |
| Map_LoadFromFile | `200` | 4 | 107, 122, 138, 155 |
| Map_LoadFromFile | `140000` | 4 | 109, 124, 140, 170 |
| Map_LoadFromFile | `12` | 2 | 116, 225 |
| Map_LoadFromFile | `4` | 1 | 135 |
| Map_LoadFromFile | `0x9C40` | 1 | 144 |
| Map_LoadFromFile | `0xFFFF` | 2 | 165, 175 |
| Map_LoadFromFile | `147147` | 3 | 186, 222, 223 |
| Map_LoadFromFile | `147151` | 1 | 187 |
| Map_LoadFromFile | `147155` | 1 | 188 |
| Map_LoadFromFile | `147159` | 1 | 189 |
| Map_LoadFromFile | `147149` | 1 | 198 |
| Map_LoadFromFile | `509211` | 1 | 201 |
| Map_LoadFromFile | `576373` | 1 | 215 |
| Map_LoadFromFile | `20000` | 1 | 221 |
| Map_LoadFromFile | `0x18u` | 1 | 223 |
| Map_LoadFromFile | `24` | 1 | 224 |
| Map_LoadFromFile | `26` | 1 | 226 |
| Scenario_SetupSirArthurRosterVariantA | `5` | 1 | 257 |
| Scenario_SetupSirArthurRosterVariantA | `141447` | 1 | 260 |
| Scenario_SetupSirArthurRosterVariantA | `142870` | 1 | 261 |
| Scenario_SetupSirArthurRosterVariantA | `140051` | 2 | 262, 263 |
| Scenario_SetupSirArthurRosterVariantA | `142897` | 1 | 264 |
| Scenario_SetupSirArthurRosterVariantA | `140028` | 1 | 267 |
| Scenario_SetupSirArthurRosterVariantA | `2` | 8 | 275, 277, 289, 291 ... |
| Scenario_SetupSirArthurRosterVariantA | `141451` | 1 | 281 |
| Scenario_SetupSirArthurRosterVariantA | `142874` | 1 | 295 |
| Scenario_SetupSirArthurRosterVariantA | `144297` | 1 | 309 |
| Scenario_SetupSirArthurRosterVariantB | `5` | 1 | 347 |
| Scenario_SetupSirArthurRosterVariantB | `142870` | 1 | 350 |
| Scenario_SetupSirArthurRosterVariantB | `140051` | 1 | 351 |
| Scenario_SetupSirArthurRosterVariantB | `142897` | 1 | 352 |
| Scenario_SetupSirArthurRosterVariantB | `140028` | 1 | 355 |
| Scenario_SetupSirArthurRosterVariantB | `2` | 8 | 363, 365, 377, 379 ... |
| Scenario_SetupSirArthurRosterVariantB | `141451` | 1 | 369 |
| Scenario_SetupSirArthurRosterVariantB | `142874` | 1 | 383 |
| Scenario_SetupSirArthurRosterVariantB | `144297` | 1 | 397 |
| Scenario_SeedCantbellyAndKopegonCastles | `4` | 2 | 436, 457 |
| Scenario_SeedCantbellyAndKopegonCastles | `5` | 6 | 436, 437, 437, 473 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `557382` | 16 | 438, 439, 440, 441 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `557384` | 1 | 438 |
| Scenario_SeedCantbellyAndKopegonCastles | `509690` | 2 | 440, 493 |
| Scenario_SeedCantbellyAndKopegonCastles | `1000` | 1 | 442 |
| Scenario_SeedCantbellyAndKopegonCastles | `510112` | 1 | 442 |
| Scenario_SeedCantbellyAndKopegonCastles | `0xF8` | 1 | 445 |
| Scenario_SeedCantbellyAndKopegonCastles | `510118` | 3 | 445, 446, 447 |
| Scenario_SeedCantbellyAndKopegonCastles | `2` | 3 | 447, 455, 471 |
| Scenario_SeedCantbellyAndKopegonCastles | `2u` | 1 | 448 |
| Scenario_SeedCantbellyAndKopegonCastles | `510090` | 5 | 448, 449, 450, 451 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `8u` | 1 | 450 |
| Scenario_SeedCantbellyAndKopegonCastles | `4u` | 1 | 451 |
| Scenario_SeedCantbellyAndKopegonCastles | `0x10u` | 1 | 452 |
| Scenario_SeedCantbellyAndKopegonCastles | `140063` | 1 | 453 |
| Scenario_SeedCantbellyAndKopegonCastles | `33` | 1 | 454 |
| Scenario_SeedCantbellyAndKopegonCastles | `510119` | 1 | 454 |
| Scenario_SeedCantbellyAndKopegonCastles | `510120` | 1 | 455 |
| Scenario_SeedCantbellyAndKopegonCastles | `34` | 1 | 456 |
| Scenario_SeedCantbellyAndKopegonCastles | `510125` | 1 | 456 |
| Scenario_SeedCantbellyAndKopegonCastles | `510126` | 1 | 457 |
| Scenario_SeedCantbellyAndKopegonCastles | `6` | 3 | 460, 461, 461 |
| Scenario_SeedCantbellyAndKopegonCastles | `7` | 6 | 462, 462, 464, 466 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `557586` | 5 | 463, 465, 467, 469 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `557788` | 4 | 463, 465, 467, 469 |
| Scenario_SeedCantbellyAndKopegonCastles | `147189` | 1 | 470 |
| Scenario_SeedCantbellyAndKopegonCastles | `10` | 2 | 471, 472 |
| Scenario_SeedCantbellyAndKopegonCastles | `8` | 1 | 472 |
| Scenario_SeedCantbellyAndKopegonCastles | `45` | 1 | 473 |
| Scenario_SeedCantbellyAndKopegonCastles | `46` | 9 | 474, 476, 478, 480 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `557464` | 13 | 475, 477, 479, 481 ... |
| Scenario_SeedCantbellyAndKopegonCastles | `557466` | 9 | 475, 477, 479, 481 ... |
| Game_InitPlayerViewState | `509676` | 1 | 538 |
| Game_InitPlayerViewState | `4` | 1 | 545 |
| Game_InitPlayerViewState | `9` | 1 | 548 |
| Game_InitPlayerViewState | `3` | 1 | 551 |
| Game_InitPlayerViewState | `509675` | 1 | 551 |
| Game_InitPlayerViewState | `7` | 1 | 554 |
| Game_InitPlayerViewState | `5` | 1 | 562 |
| Game_InitPlayerViewState | `7115` | 2 | 570, 581 |
| SaveSlot_LoadReservedSlot10 | `10` | 1 | 594 |
| Scenario_LoadAllAiMultiplayerMapAndInitView | `5` | 3 | 601, 603, 605 |
| Scenario_LoadAllAiMultiplayerMapAndInitView | `2` | 4 | 610, 611, 611, 614 |
| Scenario_LoadAllAiMultiplayerMapAndInitView | `3` | 1 | 615 |
| Battle_RunPresetScenarioByIndex | `556574` | 13 | 651, 662, 673, 684 ... |
| Battle_RunPresetScenarioByIndex | `144` | 8 | 652, 663, 674, 685 ... |
| Battle_RunPresetScenarioByIndex | `2` | 7 | 657, 665, 690, 723 ... |
| Battle_RunPresetScenarioByIndex | `3` | 1 | 676 |
| Battle_RunPresetScenarioByIndex | `4` | 5 | 677, 678, 687, 721 ... |
| Battle_RunPresetScenarioByIndex | `9` | 5 | 688, 689, 710, 711 ... |
| Battle_RunPresetScenarioByIndex | `5` | 2 | 698, 777 |
| Battle_RunPresetScenarioByIndex | `21` | 2 | 699, 700 |
| Battle_RunPresetScenarioByIndex | `6` | 1 | 709 |
| Battle_RunPresetScenarioByIndex | `7` | 1 | 720 |
| Battle_RunPresetScenarioByIndex | `8` | 1 | 733 |
| Battle_RunPresetScenarioByIndex | `28` | 2 | 747, 748 |
| Battle_RunPresetScenarioByIndex | `0xFC` | 4 | 753, 759, 764, 769 |
| Battle_RunPresetScenarioByIndex | `147285` | 3 | 753, 754, 755 |
| Battle_RunPresetScenarioByIndex | `147223` | 3 | 759, 760, 761 |
| Battle_RunPresetScenarioByIndex | `147316` | 3 | 764, 765, 766 |
| Battle_RunPresetScenarioByIndex | `147378` | 3 | 769, 770, 771 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `100` | 2 | 814, 1002 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `5` | 2 | 832, 1167 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `40` | 1 | 837 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `4` | 2 | 843, 844 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `3` | 1 | 846 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `2` | 6 | 847, 848, 851, 853 ... |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `200` | 5 | 849, 851, 852, 1052 ... |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `140051` | 1 | 854 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `509690` | 2 | 865, 1000 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `50` | 1 | 867 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `510112` | 2 | 867, 1002 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `556378` | 12 | 880, 881, 887, 888 ... |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `556380` | 6 | 902, 903, 1037, 1038 ... |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `556372` | 44 | 910, 911, 917, 918 ... |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `140063` | 1 | 961 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `140055` | 1 | 1101 |
| Scenario_LoadMultiplayerMapAndSeedPlayers | `8` | 1 | 1165 |
| Player_AssignRandomUniqueRulerNames | `5` | 4 | 1203, 1226, 1228, 1244 |
| Player_AssignRandomUniqueRulerNames | `38` | 1 | 1216 |
| Player_AssignRandomUniqueRulerNames | `2` | 2 | 1239, 1241 |
| UI_RunHoverTooltipZones | `3` | 1 | 1311 |
| UI_RunHoverTooltipZones | `2` | 6 | 1314, 1316, 1322, 1364 ... |
| UI_RunHoverTooltipZones | `4` | 3 | 1316, 1322, 1364 |
| UI_RunHoverTooltipZones | `8` | 1 | 1320 |
| UI_RunHoverTooltipZones | `12` | 2 | 1328, 1329 |
| UI_RunHoverTooltipZones | `16` | 1 | 1330 |
| UI_RunHoverTooltipZones | `639` | 4 | 1334, 1336, 1337, 1338 |
| UI_RunHoverTooltipZones | `479` | 3 | 1342, 1344, 1345 |
| UI_RunHoverTooltipZones | `188` | 2 | 1347, 1354 |
| UI_RunHoverTooltipZones | `30` | 3 | 1366, 1369, 1381 |
| UI_RunHoverTooltipZones | `0x1Eu` | 2 | 1372, 1384 |
| UI_RunHoverTooltipZones | `255` | 2 | 1372, 1384 |
| UI_RunHoverTooltipZones | `10` | 2 | 1392, 1397 |
| Prisoner_QueueCapturedUnit | `1357` | 2 | 1450, 1463 |
| Prisoner_QueueCapturedUnit | `6` | 1 | 1453 |
| Prisoner_QueueCapturedUnit | `10` | 2 | 1454, 1456 |
| Prisoner_QueueCapturedUnit | `3` | 1 | 1461 |
| Prisoner_QueueCapturedUnit | `1359` | 1 | 1462 |
| Prisoner_QueueCapturedUnit | `2` | 4 | 1462, 1463, 1464, 1465 |
| Prisoner_QueueCapturedUnit | `1358` | 1 | 1464 |
| Prisoner_QueueCapturedUnit | `1361` | 1 | 1465 |

### src/persistence/0044E880_0044FE70_persistence_006.cpp

Missing evidence: save/map/wire fields, menu widget IDs and pixel spacing, palette/audio scales and raw file-layer dimensions. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| BuildingPrisoner_RecalculateRansomValue | `0x64` | 1 | 28 |
| BuildingPrisoner_RecalculateRansomValue | `7` | 1 | 28 |
| BuildingPrisoner_RecalculateRansomValue | `4` | 4 | 29, 33, 35, 36 |
| BuildingPrisoner_RecalculateRansomValue | `10` | 3 | 33, 35, 35 |
| BuildingPrisoner_RecalculateRansomValue | `13` | 1 | 33 |
| Prisoner_SetInCastles | `3` | 2 | 61, 127 |
| Prisoner_SetInCastles | `10` | 1 | 65 |
| Prisoner_SetInCastles | `1357` | 1 | 67 |
| Prisoner_SetInCastles | `6` | 1 | 67 |
| Prisoner_SetInCastles | `100` | 1 | 74 |
| Prisoner_SetInCastles | `4` | 4 | 77, 78, 80, 82 |
| Prisoner_SetInCastles | `16` | 1 | 78 |
| Prisoner_SetInCastles | `2` | 6 | 80, 80, 83, 107 ... |
| Prisoner_SetInCastles | `5` | 1 | 120 |
| Prisoner_Behead | `100` | 1 | 178 |
| Prisoner_Behead | `4` | 1 | 179 |
| Prisoner_Behead | `3` | 2 | 181, 193 |
| Prisoner_Behead | `140051` | 1 | 185 |
| Prisoner_Behead | `2` | 3 | 185, 190, 190 |
| Prisoner_Behead | `5` | 1 | 192 |
| Prisoner_FindRichestHiddenEnemyCastle | `2` | 1 | 244 |
| Prisoner_FindRichestHiddenEnemyCastle | `509678` | 1 | 244 |
| Prisoner_FindRichestHiddenEnemyCastle | `509676` | 1 | 245 |
| Prisoner_FindRichestHiddenEnemyCastle | `100` | 1 | 258 |
| Prisoner_FindAnyHiddenEnemyCastle | `2` | 1 | 273 |
| Prisoner_FindAnyHiddenEnemyCastle | `509678` | 1 | 273 |
| Prisoner_FindAnyHiddenEnemyCastle | `509676` | 1 | 274 |
| Prisoner_FindAnyHiddenEnemyUnitStack | `0x28` | 1 | 295 |
| Prisoner_FindAnyHiddenEnemyUnitStack | `6` | 1 | 295 |
| Prisoner_FindAnyHiddenEnemyUnitStack | `147178` | 1 | 299 |
| Prisoner_FindAnyHiddenEnemyUnitStack | `147176` | 1 | 300 |
| Map_RevealTilesInRadius2ForPlayer | `2` | 6 | 328, 329, 330, 331 ... |
| Prisoner_Torture | `3` | 9 | 373, 374, 375, 376 ... |
| Prisoner_Torture | `7` | 2 | 377, 381 |
| Prisoner_Torture | `5` | 6 | 379, 397, 412, 427 ... |
| Prisoner_Torture | `5u` | 1 | 385 |
| Prisoner_Torture | `2` | 16 | 387, 391, 394, 394 ... |
| Prisoner_Torture | `446` | 3 | 387, 402, 417 |
| Prisoner_Torture | `6` | 3 | 387, 402, 417 |
| Prisoner_Torture | `6u` | 1 | 400 |
| Prisoner_Torture | `2u` | 1 | 414 |
| Prisoner_Torture | `7u` | 1 | 415 |
| Prisoner_Torture | `3u` | 1 | 429 |
| Prisoner_Torture | `4u` | 1 | 439 |
| Building_CreateSpecialPersonageGarrisonUnit | `12` | 3 | 483, 487, 493 |
| Building_CreateSpecialPersonageGarrisonUnit | `18` | 2 | 486, 500 |
| Building_CreateSpecialPersonageGarrisonUnit | `2` | 1 | 500 |
| Building_CreateSpecialPersonageGarrisonUnit | `30` | 1 | 501 |
| Building_CreateSpecialPersonageGarrisonUnit | `3u` | 1 | 501 |
| Prisoner_Pay | `8` | 1 | 515 |
| Prisoner_Pay | `140051` | 2 | 518, 530 |
| Prisoner_Pay | `2` | 4 | 518, 529, 534, 534 |
| Prisoner_Pay | `438` | 2 | 521, 525 |
| Prisoner_Pay | `5` | 1 | 536 |
| Prisoner_Pay | `3` | 1 | 537 |
| Prisoner_NewTurn | `100` | 1 | 558 |
| Prisoner_NewTurn | `3` | 3 | 559, 590, 617 |
| Prisoner_NewTurn | `140051` | 3 | 564, 577, 584 |
| Prisoner_NewTurn | `2` | 5 | 564, 577, 583, 588 ... |
| Prisoner_NewTurn | `4` | 1 | 564 |
| Prisoner_NewTurn | `6` | 3 | 564, 613, 615 |
| Prisoner_NewTurn | `5` | 1 | 567 |
| Prisoner_NewTurn | `445` | 3 | 570, 573, 582 |
| Prisoner_NewTurn | `447` | 3 | 576, 577, 580 |
| Prisoner_NewTurn | `9` | 1 | 577 |
| Prisoner_NewTurn | `448` | 2 | 578, 595 |
| Prisoner_NewTurn | `10` | 1 | 580 |
| Building_CountPrisoners | `18` | 1 | 634 |
| Building_CountPrisoners | `445` | 1 | 638 |
| Building_CountPrisoners | `6` | 1 | 640 |
| BuildingPrisonerActionWidget_HasPrisoner | `3` | 1 | 649 |
| BuildingPrisonerActionWidget_HasPrisoner | `445` | 1 | 649 |
| BuildingPrisonerActionWidget_HasPrisoner | `6` | 1 | 649 |
| BuildingPrisonerActionButton_SelectBehead | `8` | 4 | 665, 666, 667, 679 |
| BuildingPrisonerActionButton_SelectBehead | `2` | 4 | 667, 668, 668, 679 |
| BuildingPrisonerActionButton_SelectBehead | `9` | 1 | 678 |
| BuildingPrisonerActionButton_SelectBehead | `49` | 1 | 681 |
| BuildingPrisonerActionButton_SelectTorture | `8` | 4 | 702, 703, 704, 716 |
| BuildingPrisonerActionButton_SelectTorture | `2` | 4 | 704, 705, 705, 716 |
| BuildingPrisonerActionButton_SelectTorture | `9` | 1 | 715 |
| BuildingPrisonerActionButton_SelectTorture | `49` | 1 | 718 |
| BuildingPrisonerActionButton_SelectBribery | `8` | 4 | 739, 740, 741, 753 |
| BuildingPrisonerActionButton_SelectBribery | `2` | 4 | 741, 742, 742, 753 |
| BuildingPrisonerActionButton_SelectBribery | `9` | 1 | 752 |
| BuildingPrisonerActionButton_SelectBribery | `49` | 1 | 755 |
| Building_DrawPrisonerRows | `18` | 1 | 789 |
| Building_DrawPrisonerRows | `445` | 1 | 792 |
| Building_DrawPrisonerRows | `5` | 1 | 795 |
| Building_DrawPrisonerRows | `46` | 2 | 796, 807 |
| Building_DrawPrisonerRows | `52` | 2 | 796, 807 |
| Building_DrawPrisonerRows | `368` | 1 | 797 |
| Building_DrawPrisonerRows | `446` | 1 | 806 |
| Building_DrawPrisonerRows | `378` | 1 | 808 |
| Building_DrawPrisonerRows | `68` | 1 | 820 |
| Building_DrawPrisonerRows | `461` | 1 | 821 |
| Building_DrawPrisonerRows | `3` | 2 | 822, 828 |
| Building_DrawPrisonerRows | `6` | 1 | 826 |
| Queen_DrawRelationshipPanel | `25` | 1 | 846 |
| Queen_DrawRelationshipPanel | `46` | 1 | 847 |
| Queen_DrawRelationshipPanel | `52` | 1 | 847 |
| Queen_DrawRelationshipPanel | `199` | 1 | 848 |
| Queen_DrawRelationshipPanel | `17` | 1 | 858 |
| Queen_DrawRelationshipPanel | `180` | 1 | 863 |
| Queen_DrawRelationshipPanel | `500` | 1 | 864 |
| Queen_DrawRelationshipPanel | `215` | 1 | 865 |
| Queen_DrawRelationshipPanel | `6` | 1 | 866 |
| Queen_DrawRelationshipPanel | `3` | 1 | 867 |
| Building_ShowPrisonerManagementPanel | `5` | 5 | 936, 937, 938, 1111 ... |
| Building_ShowPrisonerManagementPanel | `3` | 7 | 945, 948, 1006, 1022 ... |
| Building_ShowPrisonerManagementPanel | `477` | 1 | 945 |
| Building_ShowPrisonerManagementPanel | `61` | 1 | 955 |
| Building_ShowPrisonerManagementPanel | `114` | 1 | 959 |
| Building_ShowPrisonerManagementPanel | `2` | 10 | 964, 1221, 1228, 1235 ... |
| Building_ShowPrisonerManagementPanel | `159` | 1 | 966 |
| Building_ShowPrisonerManagementPanel | `1024` | 1 | 968 |
| Building_ShowPrisonerManagementPanel | `256` | 1 | 972 |
| Building_ShowPrisonerManagementPanel | `4112` | 1 | 975 |
| Building_ShowPrisonerManagementPanel | `8` | 4 | 986, 997, 1013, 1028 |
| Building_ShowPrisonerManagementPanel | `18` | 2 | 987, 992 |
| Building_ShowPrisonerManagementPanel | `17` | 2 | 988, 1026 |
| Building_ShowPrisonerManagementPanel | `13` | 1 | 995 |
| Building_ShowPrisonerManagementPanel | `140063` | 1 | 995 |
| Building_ShowPrisonerManagementPanel | `46` | 8 | 996, 1011, 1027, 1042 ... |
| Building_ShowPrisonerManagementPanel | `52` | 10 | 996, 1012, 1027, 1042 ... |
| Building_ShowPrisonerManagementPanel | `140028` | 1 | 1006 |
| Building_ShowPrisonerManagementPanel | `214` | 1 | 1006 |
| Building_ShowPrisonerManagementPanel | `30` | 3 | 1006, 1022, 1037 |
| Building_ShowPrisonerManagementPanel | `88` | 3 | 1006, 1188, 1189 |
| Building_ShowPrisonerManagementPanel | `141447` | 1 | 1008 |
| Building_ShowPrisonerManagementPanel | `141486` | 1 | 1010 |
| Building_ShowPrisonerManagementPanel | `15` | 1 | 1010 |
| Building_ShowPrisonerManagementPanel | `141451` | 1 | 1022 |
| Building_ShowPrisonerManagementPanel | `254` | 1 | 1022 |
| Building_ShowPrisonerManagementPanel | `380` | 1 | 1022 |
| Building_ShowPrisonerManagementPanel | `142870` | 1 | 1024 |
| Building_ShowPrisonerManagementPanel | `142909` | 1 | 1026 |
| Building_ShowPrisonerManagementPanel | `142874` | 1 | 1037 |
| Building_ShowPrisonerManagementPanel | `420` | 1 | 1037 |
| Building_ShowPrisonerManagementPanel | `546` | 1 | 1037 |
| Building_ShowPrisonerManagementPanel | `144293` | 1 | 1039 |
| Building_ShowPrisonerManagementPanel | `144332` | 1 | 1041 |
| Building_ShowPrisonerManagementPanel | `19` | 1 | 1041 |
| Building_ShowPrisonerManagementPanel | `144297` | 1 | 1052 |
| Building_ShowPrisonerManagementPanel | `172` | 1 | 1052 |
| Building_ShowPrisonerManagementPanel | `298` | 1 | 1052 |
| Building_ShowPrisonerManagementPanel | `75` | 2 | 1052, 1068 |
| Building_ShowPrisonerManagementPanel | `145716` | 1 | 1054 |
| Building_ShowPrisonerManagementPanel | `145755` | 1 | 1056 |
| Building_ShowPrisonerManagementPanel | `21` | 1 | 1056 |
| Building_ShowPrisonerManagementPanel | `145720` | 1 | 1068 |
| Building_ShowPrisonerManagementPanel | `336` | 1 | 1068 |
| Building_ShowPrisonerManagementPanel | `462` | 1 | 1068 |
| Building_ShowPrisonerManagementPanel | `141441` | 1 | 1099 |
| Building_ShowPrisonerManagementPanel | `24` | 3 | 1113, 1125, 1136 |
| Building_ShowPrisonerManagementPanel | `107` | 12 | 1116, 1127, 1141, 1178 ... |
| Building_ShowPrisonerManagementPanel | `123` | 3 | 1159, 1161, 1169 |
| Building_ShowPrisonerManagementPanel | `299` | 2 | 1179, 1180 |
| Building_ShowPrisonerManagementPanel | `0x12Bu` | 1 | 1182 |
| Building_ShowPrisonerManagementPanel | `0x58u` | 1 | 1191 |
| Building_ShowPrisonerManagementPanel | `510` | 2 | 1197, 1198 |
| Building_ShowPrisonerManagementPanel | `0x1FEu` | 1 | 1200 |
| Building_ShowPrisonerManagementPanel | `10` | 1 | 1209 |
| Building_ShowPrisonerManagementPanel | `20` | 2 | 1211, 1290 |

### src/strategic/004506B0_004530D0_strategic_001.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Queen_FindEligibleBirthHostBuilding | `16` | 1 | 28 |
| Queen_FindEligibleBirthHostBuilding | `4` | 2 | 28, 28 |
| Queen_FindEligibleBirthHostBuilding | `509678` | 1 | 30 |
| Queen_FindEligibleBirthHostBuilding | `2` | 1 | 31 |
| Queen_FindEligibleBirthHostBuilding | `509676` | 1 | 31 |
| Queen_FindEligibleBirthHostBuilding | `100` | 1 | 34 |
| Queen_NewTurn | `3` | 5 | 100, 101, 135, 143 ... |
| Queen_NewTurn | `6` | 2 | 102, 105 |
| Queen_NewTurn | `0x32` | 1 | 116 |
| Queen_NewTurn | `100` | 1 | 116 |
| Queen_NewTurn | `33` | 2 | 116, 131 |
| Queen_NewTurn | `5` | 9 | 121, 127, 172, 184 ... |
| Queen_NewTurn | `2` | 7 | 126, 126, 130, 130 ... |
| Queen_NewTurn | `510112` | 1 | 168 |
| Queen_NewTurn | `2u` | 1 | 175 |
| Queen_NewTurn | `0xF8` | 1 | 182 |
| Queen_NewTurn | `510109` | 3 | 182, 183, 184 |
| Queen_NewTurn | `3u` | 1 | 191 |
| Queen_NewTurn | `141445` | 1 | 211 |
| Queen_NewTurn | `140051` | 1 | 213 |
| Queen_NewTurn | `24` | 1 | 215 |
| Queen_NewTurn | `7` | 1 | 221 |
| Queen_NewTurn | `141443` | 8 | 227, 228, 233, 234 ... |
| Queen_NewTurn | `9` | 2 | 227, 240 |
| Queen_NewTurn | `14` | 1 | 238 |
| Queen_NewTurn | `8` | 3 | 244, 253, 283 |
| Queen_NewTurn | `1000` | 1 | 251 |
| Player_Surrender | `4` | 2 | 335, 335 |
| Player_Surrender | `16` | 1 | 336 |
| Player_Surrender | `509676` | 1 | 337 |
| Player_Surrender | `100` | 1 | 341 |
| Player_Surrender | `0x28` | 1 | 348 |
| Player_Surrender | `147180` | 1 | 348 |
| Player_Surrender | `147178` | 1 | 349 |
| AI_ComputeNationStrengthPercent | `200` | 1 | 391 |
| AI_ComputeNationStrengthPercent | `7` | 1 | 392 |
| AI_ComputeNationStrengthPercent | `5` | 3 | 394, 421, 435 |
| AI_ComputeNationStrengthPercent | `4` | 3 | 399, 399, 447 |
| AI_ComputeNationStrengthPercent | `16` | 1 | 400 |
| AI_ComputeNationStrengthPercent | `509678` | 1 | 401 |
| AI_ComputeNationStrengthPercent | `509676` | 1 | 402 |
| AI_ComputeNationStrengthPercent | `100` | 2 | 404, 430 |
| AI_ComputeNationStrengthPercent | `0x28` | 1 | 411 |
| AI_ComputeNationStrengthPercent | `6` | 1 | 411 |
| AI_ComputeNationStrengthPercent | `147178` | 1 | 412 |
| AI_ComputeNationStrengthPercent | `10` | 1 | 431 |
| AI_ComputeNationStrengthPercent | `140024` | 1 | 438 |
| AI_ComputeNationStrengthPercent | `140051` | 1 | 438 |
| AI_ComputeNationStrengthPercent | `2` | 2 | 445, 445 |
| AI_ComputeNationStrengthPercent | `3` | 1 | 448 |
| Player_CheckForDefeatAndHandleElimination | `0x28` | 1 | 482 |
| Player_CheckForDefeatAndHandleElimination | `147180` | 1 | 482 |
| Player_CheckForDefeatAndHandleElimination | `147178` | 1 | 484 |
| Player_CheckForDefeatAndHandleElimination | `4` | 2 | 496, 496 |
| Player_CheckForDefeatAndHandleElimination | `16` | 1 | 497 |
| Player_CheckForDefeatAndHandleElimination | `509678` | 1 | 498 |
| Player_CheckForDefeatAndHandleElimination | `509676` | 1 | 500 |
| Player_CheckForDefeatAndHandleElimination | `100` | 1 | 504 |
| Player_CheckForDefeatAndHandleElimination | `140024` | 1 | 517 |
| Player_CheckForDefeatAndHandleElimination | `140051` | 1 | 519 |
| Player_CheckForDefeatAndHandleElimination | `5` | 1 | 522 |
| Player_CheckSoleSurvivorAndShowVictoryBanner | `7115` | 1 | 550 |
| Player_CheckSoleSurvivorAndShowVictoryBanner | `56` | 1 | 556 |
| Options_ApplyInGameSliders | `147173` | 1 | 577 |
| Options_ApplyInGameSliders | `7` | 3 | 577, 578, 579 |
| Options_ApplyInGameSliders | `31` | 4 | 578, 579, 582, 583 |
| Options_ApplyInGameSliders | `8` | 6 | 578, 579, 579, 582 ... |
| Options_ApplyInGameSliders | `64` | 1 | 580 |
| Options_ApplyInGameSliders | `147172` | 1 | 581 |
| Options_ApplyInGameSliders | `16` | 3 | 581, 582, 583 |
| Options_ApplyInGameSliders | `147147` | 1 | 584 |
| Options_InitInGameSlidersAndWidgets | `2` | 6 | 609, 611, 614, 616 ... |
| Options_InitInGameSlidersAndWidgets | `98` | 2 | 609, 611 |
| Options_InitInGameSlidersAndWidgets | `106` | 1 | 612 |
| Options_InitInGameSlidersAndWidgets | `151` | 2 | 614, 616 |
| Options_InitInGameSlidersAndWidgets | `159` | 1 | 617 |
| Options_InitInGameSlidersAndWidgets | `204` | 2 | 619, 621 |
| Options_InitInGameSlidersAndWidgets | `212` | 1 | 622 |
| Options_InitInGameSlidersAndWidgets | `257` | 2 | 624, 626 |
| Options_InitInGameSlidersAndWidgets | `265` | 1 | 627 |
| Options_InitInGameSlidersAndWidgets | `128` | 3 | 629, 630, 631 |
| Options_ToggleCheckboxInGame | `8` | 3 | 645, 646, 647 |
| Options_ToggleCheckboxInGame | `2` | 1 | 647 |
| Options_ToggleCheckboxInGame | `49` | 1 | 648 |
| Options_RunInGameSettingsDialog | `29` | 1 | 668 |
| Options_RunInGameSettingsDialog | `371` | 1 | 681 |
| Options_RunInGameSettingsDialog | `4112` | 1 | 684 |
| Options_RunInGameSettingsDialog | `25` | 1 | 690 |
| Options_RunInGameSettingsDialog | `92` | 2 | 693, 697 |
| Options_RunInGameSettingsDialog | `4` | 7 | 698, 699, 700, 725 ... |
| Options_RunInGameSettingsDialog | `2` | 10 | 702, 702, 715, 717 ... |
| Options_RunInGameSettingsDialog | `0x10` | 1 | 708 |
| Options_RunInGameSettingsDialog | `0x14` | 1 | 709 |
| Options_RunInGameSettingsDialog | `0x21` | 1 | 711 |
| Options_RunInGameSettingsDialog | `212` | 1 | 713 |
| Options_RunInGameSettingsDialog | `147159` | 2 | 714, 752 |
| Options_RunInGameSettingsDialog | `0x08` | 2 | 715, 752 |
| Options_RunInGameSettingsDialog | `147147` | 3 | 716, 753, 766 |
| Options_RunInGameSettingsDialog | `0x3D` | 2 | 717, 753 |
| Options_RunInGameSettingsDialog | `147163` | 2 | 718, 754 |
| Options_RunInGameSettingsDialog | `0x72` | 2 | 719, 754 |
| Options_RunInGameSettingsDialog | `147167` | 2 | 720, 755 |
| Options_RunInGameSettingsDialog | `0xA7` | 2 | 721, 755 |
| Options_RunInGameSettingsDialog | `0x4000` | 1 | 722 |
| Options_RunInGameSettingsDialog | `147173` | 2 | 722, 756 |
| Options_RunInGameSettingsDialog | `8` | 16 | 722, 724, 725, 726 ... |
| Options_RunInGameSettingsDialog | `31` | 12 | 723, 723, 725, 726 ... |
| Options_RunInGameSettingsDialog | `7` | 6 | 723, 723, 723, 756 ... |
| Options_RunInGameSettingsDialog | `147171` | 4 | 724, 725, 726, 760 |
| Options_RunInGameSettingsDialog | `16` | 8 | 726, 729, 760, 761 ... |
| Options_RunInGameSettingsDialog | `147172` | 4 | 727, 728, 729, 763 |
| Options_RunInGameSettingsDialog | `46` | 1 | 732 |
| Options_RunInGameSettingsDialog | `52` | 1 | 732 |
| Options_RunInGameSettingsDialog | `82` | 1 | 733 |
| Options_RunInGameSettingsDialog | `132` | 2 | 743, 747 |
| Options_RunInGameSettingsDialog | `64` | 1 | 759 |
| Cheat_FillSelectedSquadWithCannons | `6` | 1 | 814 |
| Cheat_FillSelectedSquadWithCannons | `147178` | 1 | 816 |
| Cheat_ClearSelectedSquadDamageFlags | `147192` | 2 | 839, 843 |
| Cheat_ClearSelectedSquadDamageFlags | `3u` | 1 | 839 |
| Cheat_ClearSelectedSquadDamageFlags | `147161` | 1 | 840 |
| Cheat_ClearSelectedSquadDamageFlags | `31` | 1 | 840 |
| Cheat_ClearSelectedSquadDamageFlags | `0xF3` | 1 | 843 |
| Cheat_HealSelectedSquadAndClearDamage | `100` | 1 | 874 |
| Cheat_HealSelectedSquadAndClearDamage | `147158` | 1 | 874 |
| Cheat_HealSelectedSquadAndClearDamage | `31` | 1 | 874 |
| Cheat_KillUnitOrBuildingUnderCursor | `200` | 1 | 894 |
| Cheat_KillUnitOrBuildingUnderCursor | `32` | 3 | 896, 897, 898 |
| Cheat_KillUnitOrBuildingUnderCursor | `31` | 4 | 897, 898, 904, 905 |
| Cheat_KillUnitOrBuildingUnderCursor | `6` | 6 | 897, 898, 898, 904 ... |
| Cheat_KillUnitOrBuildingUnderCursor | `2` | 1 | 901 |
| Cheat_KillUnitOrBuildingUnderCursor | `16` | 3 | 903, 904, 905 |
| Cheat_KillUnitOrBuildingUnderCursor | `0xFFFF` | 1 | 908 |
| Cheat_KillUnitOrBuildingUnderCursor | `0x1F4` | 1 | 910 |
| Cheat_KillUnitOrBuildingUnderCursor | `0x28` | 1 | 910 |
| Cheat_KillUnitOrBuildingUnderCursor | `147180` | 1 | 910 |
| Cheat_TeleportSelectedUnitToCursor | `32` | 3 | 938, 939, 940 |
| Cheat_TeleportSelectedUnitToCursor | `31` | 4 | 939, 940, 944, 945 |
| Cheat_TeleportSelectedUnitToCursor | `6` | 6 | 939, 940, 940, 944 ... |
| Cheat_TeleportSelectedUnitToCursor | `16` | 3 | 943, 944, 945 |
| Cheat_TeleportSelectedUnitToCursor | `147176` | 2 | 951, 955 |
| Cheat_TeleportSelectedUnitToCursor | `2` | 1 | 951 |
| Cheat_FillSelectedSquadWithPegasi | `6` | 1 | 981 |
| Cheat_FillSelectedSquadWithPegasi | `147178` | 1 | 983 |
| Cheat_ShowDeveloperTeamImage | `20` | 5 | 1006, 1021, 1024, 1026 ... |
| Cheat_ShowDeveloperTeamImage | `1024` | 1 | 1007 |
| Cheat_ShowDeveloperTeamImage | `256` | 1 | 1011 |
| Cheat_ShowDeveloperTeamImage | `188` | 1 | 1014 |
| Cheat_ShowDeveloperTeamImage | `2` | 1 | 1030 |
| Cheat_SetFactionColorAndCastleFlags | `3` | 2 | 1054, 1066 |
| Cheat_SetFactionColorAndCastleFlags | `16` | 1 | 1059 |
| Cheat_SetFactionColorAndCastleFlags | `4` | 2 | 1059, 1059 |
| Cheat_SetFactionColorAndCastleFlags | `509676` | 1 | 1062 |
| Cheat_SetFactionColorAndCastleFlags | `0xF8` | 1 | 1064 |
| Cheat_SetFactionColorAndCastleFlags | `510118` | 3 | 1064, 1065, 1066 |
| Cheat_SetFactionColorAndCastleFlags | `100` | 1 | 1071 |
| UI_ReadCheatString | `124` | 1 | 1098 |
| UI_ReadCheatString | `2` | 1 | 1100 |
| UI_ReadCheatString | `25` | 1 | 1101 |
| UI_ReadCheatString | `46` | 1 | 1103 |
| UI_ReadCheatString | `28` | 1 | 1127 |
| UI_ReadCheatString | `0x32u` | 1 | 1137 |
| UI_ReadCheatString | `8` | 1 | 1149 |
| Rules_ShowBanner_StrategicClash | `6` | 1 | 1170 |
| Rules_ShowBanner_StrategicClash | `32` | 1 | 1172 |
| Rules_ShowBanner_StrategicClash | `4` | 1 | 1173 |
| Rules_ShowBanner_StrategicClash | `3` | 1 | 1174 |
| Rules_ResetEngineOnLoad | `32` | 1 | 1187 |
| Rules_CompileStrategicRulesFile | `6` | 1 | 1198 |
| Rules_CompileStrategicRulesFile | `32` | 1 | 1200 |
| Rules_CompileStrategicRulesFile | `4` | 1 | 1201 |
| Rules_CompileStrategicRulesFile | `3` | 1 | 1202 |
| Rules_RegisterAllHostFunctions | `32` | 1 | 1216 |
| Rules_LogMissionSetupInfo | `124` | 1 | 1230 |
| Rules_LogMissionSetupInfo | `5` | 1 | 1236 |
| Rules_LogMissionSetupInfo | `140024` | 1 | 1239 |
| Rules_LogMissionSetupInfo | `140051` | 1 | 1245 |
| Rules_LogMissionSetupInfo | `140055` | 1 | 1246 |
| Rules_LogMissionSetupInfo | `140063` | 1 | 1247 |
| Rules_ExecuteAITurn | `224` | 1 | 1273 |
| Rules_ExecuteAITurn | `0xC8` | 1 | 1281 |
| Rules_ExecuteAITurn | `16` | 2 | 1286, 1303 |
| Rules_ExecuteAITurn | `4` | 4 | 1286, 1286, 1303, 1303 |
| Rules_ExecuteAITurn | `2` | 1 | 1289 |
| Rules_ExecuteAITurn | `509676` | 2 | 1289, 1306 |
| Rules_ExecuteAITurn | `509678` | 2 | 1289, 1306 |
| Rules_ExecuteAITurn | `100` | 2 | 1292, 1309 |
| Rules_CreateArmyFact | `1000` | 1 | 1353 |
| Rules_CreateArmyFact | `3` | 1 | 1356 |
| Rules_CreateArmyFact | `0x28` | 1 | 1357 |
| Rules_CreateArmyFact | `4` | 1 | 1365 |
| Rules_CreateArmyFact | `100` | 2 | 1366, 1367 |
| Rules_CreateArmyFact | `721` | 1 | 1376 |
| Rules_RetractArmyFact | `1000` | 1 | 1396 |
| Rules_RetractArmyFact | `721` | 4 | 1403, 1405, 1408, 1412 |
| Rules_RegisterStrategicActionHostFunctions | `36` | 1 | 1422 |
| Rules_RegisterStrategicActionHostFunctions | `105` | 14 | 1423, 1424, 1425, 1437 ... |
| Rules_RegisterStrategicActionHostFunctions | `98` | 16 | 1426, 1427, 1428, 1429 ... |

### src/strategic/00452753_0045303F_strategic_007.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Rules_HostTemple | `2` | 1 | 17 |
| Rules_HostDigTreasure | `4` | 3 | 34, 41, 44 |
| Rules_HostDigTreasure | `9` | 1 | 35 |
| Rules_HostDigTreasure | `8` | 1 | 36 |
| Rules_HostDigTreasure | `3` | 1 | 43 |
| Rules_HostDigTreasure | `12` | 1 | 44 |
| Rules_HostDigTreasure | `24` | 1 | 44 |
| Rules_HostRoadExists | `2` | 1 | 55 |
| Rules_HostRoadExists | `3` | 1 | 56 |
| Rules_HostRoadExistsNearby | `2` | 1 | 65 |
| Rules_HostRoadExistsNearby | `3` | 1 | 66 |
| Rules_HostRoadExistsNearCastle | `2` | 1 | 75 |
| Rules_HostRoadExistsNearCastle | `3` | 1 | 76 |
| Rules_HostRoadExistsToPort | `2` | 1 | 85 |
| Rules_HostRoadExistsToPort | `3` | 1 | 86 |
| Rules_HostRoadExistsToCastle | `2` | 1 | 95 |
| Rules_HostRoadExistsToCastle | `3` | 1 | 96 |
| Rules_HostRoadExistsToTemple | `2` | 1 | 105 |
| Rules_HostRoadExistsToTemple | `3` | 1 | 106 |
| Rules_HostTroopInArmyRange | `2` | 1 | 115 |
| Rules_HostTroopInArmyRange | `3` | 1 | 116 |
| Rules_HostBuildingInArmyRange | `2` | 1 | 125 |
| Rules_HostBuildingInArmyRange | `3` | 1 | 126 |
| Rules_HostDistanceFromObject | `2` | 1 | 135 |
| Rules_HostDistanceFromObject | `3` | 1 | 136 |
| Rules_HostTempleInArmyRange | `2` | 1 | 145 |
| Rules_HostTempleInArmyRange | `3` | 1 | 146 |
| Rules_HostTempleOk | `2` | 1 | 155 |
| Rules_HostTempleOk | `3` | 1 | 156 |
| Rules_HostMarch | `2` | 1 | 165 |
| Rules_HostMarch | `3` | 1 | 166 |
| Rules_HostMarchToTemple | `2` | 1 | 180 |
| Rules_HostMarchToTemple | `3` | 1 | 181 |
| Rules_HostMarchNear | `2` | 1 | 189 |
| Rules_HostMarchNear | `3` | 1 | 190 |
| Rules_HostAttackTroop | `2` | 1 | 199 |
| Rules_HostCaptureTroop | `2` | 1 | 208 |
| Rules_HostHideTroop | `2` | 1 | 217 |
| Rules_HostHideTroop | `3` | 1 | 218 |
| Rules_HostAttackBuilding | `2` | 1 | 245 |
| Rules_HostBuildTrap | `2` | 1 | 268 |
| Rules_HostBuildTrap | `3` | 1 | 269 |

### src/strategic/00453110_00455720_strategic_002.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Rules_QueuePathToTile | `147490` | 3 | 30, 48, 49 |
| Rules_QueuePathToTile | `320` | 1 | 32 |
| Rules_QueuePathToTile | `147176` | 1 | 42 |
| Rules_QueuePathNearTile | `320` | 1 | 74 |
| Rules_QueuePathNearTile | `2` | 2 | 75, 78 |
| Rules_QueuePathNearTile | `147490` | 2 | 93, 94 |
| Rules_QueuePathNearCastle | `147490` | 3 | 109, 130, 131 |
| Rules_QueuePathNearCastle | `320` | 1 | 111 |
| Rules_QueuePathNearCastle | `3` | 2 | 113, 113 |
| Rules_QueuePathToPort | `147490` | 2 | 161, 174 |
| Rules_QueuePathToPort | `320` | 1 | 163 |
| Rules_QueuePathToCastle | `147490` | 3 | 187, 212, 213 |
| Rules_QueuePathToCastle | `320` | 1 | 189 |
| Rules_QueuePathToCastle | `2` | 2 | 191, 191 |
| Move_IsAtTargetOrCanStay | `147490` | 2 | 232, 243 |
| Move_IsAtTargetOrCanStay | `320` | 1 | 234 |
| Move_TryApproachTarget | `147490` | 2 | 263, 288 |
| Move_TryApproachTarget | `2` | 2 | 264, 265 |
| Move_TryApproachTarget | `320` | 1 | 264 |
| Move_TryApproachTarget | `4` | 1 | 280 |
| Rules_QueuePathIntoArmyRange | `147490` | 3 | 317, 339, 340 |
| Rules_QueuePathIntoArmyRange | `320` | 1 | 318 |
| Rules_QueuePathIntoArmyRange | `4` | 1 | 331 |
| Rules_GetPathDistanceToObject | `147490` | 2 | 368, 373 |
| Rules_GetPathDistanceToObject | `320` | 1 | 371 |
| Rules_GetPathDistanceToObject | `147176` | 1 | 385 |
| Rules_GetPathDistanceToObject | `1000` | 1 | 398 |
| Rules_IsTempleWithinArmyRange | `147490` | 3 | 418, 422, 424 |
| Rules_IsTempleWithinArmyRange | `320` | 1 | 420 |
| Move_CommitIfWithinCost | `9` | 1 | 468 |
| Move_CommitIfWithinCost | `8` | 1 | 479 |
| Move_CommitIfWithinCost | `147490` | 1 | 480 |
| Move_CommitIfWithinCost | `147176` | 2 | 485, 497 |
| Move_CommitIfWithinCost | `0x1F4` | 1 | 491 |
| Move_CommitIfWithinCost | `0x28` | 1 | 491 |
| Move_CommitIfWithinCost | `147180` | 1 | 491 |
| Move_CommitIfWithinCost | `2` | 1 | 502 |
| Move_CommitIfWithinCost | `147895` | 1 | 504 |
| Rules_MarchToTemple | `6` | 1 | 527 |
| Rules_MarchToTemple | `147490` | 4 | 530, 534, 536, 545 |
| Rules_MarchToTemple | `320` | 1 | 532 |
| Rules_MarchToTemple | `147176` | 2 | 549, 557 |
| Rules_MarchToTemple | `0x1F4` | 1 | 551 |
| Rules_MarchToTemple | `0x28` | 1 | 551 |
| Rules_MarchToTemple | `147180` | 2 | 551, 555 |
| Rules_MarchToTemple | `2` | 1 | 560 |
| Rules_MarchToTemple | `147895` | 1 | 561 |
| Rules_MarchNearTile | `6` | 1 | 584 |
| Rules_MarchNearTile | `147490` | 4 | 588, 592, 594, 603 |
| Rules_MarchNearTile | `320` | 1 | 590 |
| Rules_MarchNearTile | `147176` | 2 | 607, 612 |
| Rules_MarchNearTile | `0x1F4` | 1 | 609 |
| Rules_MarchNearTile | `0x28` | 1 | 609 |
| Rules_MarchNearTile | `147180` | 1 | 609 |
| Rules_MarchNearTile | `2` | 1 | 615 |
| Rules_MarchNearTile | `147895` | 1 | 616 |
| Rules_HostUnitMoveAndHide | `147176` | 2 | 664, 675 |
| Rules_HostUnitMoveAndHide | `147490` | 2 | 670, 671 |
| Rules_IsQueuedPathTargetBridgeCrossing | `147490` | 1 | 717 |
| Rules_IsQueuedPathTargetBridgeCrossing | `320` | 2 | 721, 722 |
| Rules_IsQueuedPathTargetBridgeCrossing | `4` | 2 | 721, 722 |
| Rules_BuildRoadOrStepTowardQueuedPath | `4` | 2 | 750, 750 |
| Rules_BuildRoadOrStepTowardQueuedPath | `147176` | 2 | 753, 754 |
| Rules_BuildTrapNearTile | `2` | 2 | 867, 870 |
| Rules_BuildTrapNearTile | `147176` | 1 | 869 |
| UnitStack_CalcArmyFactStrength | `6` | 1 | 897 |
| Rules_EnsureArmyFactForStack | `0x28` | 1 | 913 |
| Rules_EnsureArmyFactForStack | `3` | 1 | 913 |
| Rules_EnsureArmyFactForStack | `721` | 2 | 913, 918 |
| Rules_EnsureArmyFactForStack | `2` | 1 | 924 |
| Rules_LinkArmyFact | `6` | 5 | 944, 945, 946, 953 ... |
| Rules_LinkArmyFact | `721` | 1 | 956 |
| Rules_LinkArmyFact | `16` | 3 | 960, 969, 977 |
| Rules_LinkArmyFact | `2` | 7 | 960, 963, 969, 971 ... |
| Rules_LinkArmyFact | `4` | 1 | 975 |
| Rules_SyncArmyFactStrength | `6` | 2 | 1003, 1010 |
| Rules_SyncArmyFactStrength | `721` | 1 | 1013 |
| Rules_SyncArmyFactStrength | `16` | 1 | 1016 |
| Rules_SyncArmyFactStrength | `2` | 2 | 1016, 1021 |
| Rules_SyncArmyFactOwner | `7` | 1 | 1039 |
| Rules_SyncArmyFactOwner | `6` | 1 | 1044 |
| Rules_SyncArmyFactOwner | `2` | 1 | 1048 |
| Rules_SyncArmyFactOwner | `4` | 1 | 1048 |
| Rules_SyncArmyFactOwner | `721` | 1 | 1049 |
| Rules_SyncCastleFactOwner | `9` | 1 | 1066 |
| Rules_SyncCastleFactOwner | `7` | 1 | 1069 |
| Rules_SyncCastleFactOwner | `2` | 2 | 1071, 1072 |
| Rules_SyncCastleFactOwner | `463` | 2 | 1073, 1093 |
| Rules_SyncCastleFactOwner | `100u` | 1 | 1081 |
| Rules_LogTrapFact | `200` | 1 | 1115 |
| Rules_RetractTrapFact | `200` | 1 | 1128 |
| Rules_LogTempleFact | `200` | 1 | 1141 |
| Rules_LogTreasureFact | `200` | 1 | 1154 |
| Rules_RetractTreasureFact | `200` | 1 | 1167 |
| Rules_RetractTempleFact | `200` | 1 | 1182 |
| Rules_AssertCastleFact | `1000` | 1 | 1212 |
| Rules_AssertCastleFact | `416` | 5 | 1216, 1221, 1226, 1231 ... |
| Rules_AssertCastleFact | `2` | 1 | 1245 |
| Rules_AssertCastleFact | `463` | 1 | 1254 |
| Rules_RetractCastleFact | `463` | 3 | 1267, 1268, 1270 |
| Rules_RetractCastleFact | `2` | 1 | 1271 |
| Building_GetTaxRateByIndex | `0x3F` | 1 | 1300 |
| Building_GetTaxRateByIndex | `510110` | 1 | 1300 |
| Building_GetWallStrengthByIndex | `510095` | 1 | 1325 |
| Building_GetMoneyByIndex | `510112` | 1 | 1332 |
| Building_GetTechLevelByIndex | `510118` | 1 | 1364 |
| Building_GetTechLevelByIndex | `7` | 1 | 1364 |
| Building_GetTypeByIndex | `509678` | 1 | 1371 |
| Building_GetSatisfactionByIndex | `510108` | 1 | 1386 |
| Building_GetPeasantCountByIndex | `510104` | 1 | 1395 |
| Building_GetPeasantCountByIndex | `0xFu` | 1 | 1396 |
| Building_HasProductionByIndex | `510088` | 1 | 1404 |

### src/strategic/00455740_004582B0_strategic_003.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Building_AdjustTaxRateByIndex | `0x3F` | 2 | 30, 38 |
| Building_AdjustTaxRateByIndex | `510110` | 4 | 30, 36, 37, 38 |
| Building_AdjustTaxRateByIndex | `0xC0` | 1 | 36 |
| Building_FindUnitLicenceSlotIndexOrZero | `510076` | 1 | 83 |
| Building_FindUnitLicenceSlotIndexOrZero | `12` | 1 | 85 |
| Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero | `510076` | 1 | 103 |
| Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero | `12` | 1 | 106 |
| Building_UnitsLeaveReadyGarrisonSlots | `10` | 3 | 123, 130, 150 |
| Building_UnitsLeaveReadyGarrisonSlots | `509692` | 1 | 140 |
| Building_UnitsLeaveReadyGarrisonSlots | `100` | 1 | 141 |
| Building_UnitsLeaveReadyGarrisonSlots | `509701` | 1 | 141 |
| Building_UnitsLeaveReadyGarrisonSlots | `4` | 1 | 142 |
| Building_UnitsLeaveReadyGarrisonSlots | `5` | 2 | 142, 150 |
| Building_UnitsLeaveReadyGarrisonSlots | `510064` | 2 | 142, 143 |
| Building_UnitsLeaveReadyGarrisonSlots | `7` | 1 | 143 |
| Building_HasTrainableIdleGarrisonUnit | `509692` | 1 | 174 |
| Building_HasTrainableIdleGarrisonUnit | `2` | 1 | 175 |
| Building_HasTrainableIdleGarrisonUnit | `3u` | 1 | 175 |
| Building_HasTrainableIdleGarrisonUnit | `509704` | 1 | 175 |
| Building_HasTrainableIdleGarrisonUnit | `510064` | 1 | 176 |
| Building_HasTrainableIdleGarrisonUnit | `7` | 1 | 176 |
| Building_HasRepairableIdleGarrisonUnit | `509692` | 1 | 203 |
| Building_HasRepairableIdleGarrisonUnit | `50` | 1 | 204 |
| Building_HasRepairableIdleGarrisonUnit | `509701` | 1 | 204 |
| Building_HasRepairableIdleGarrisonUnit | `4` | 1 | 205 |
| Building_HasRepairableIdleGarrisonUnit | `5` | 1 | 205 |
| Building_HasRepairableIdleGarrisonUnit | `510064` | 1 | 205 |
| Building_StartTrainingIdleGarrisonUnits | `509692` | 1 | 234 |
| Building_StartTrainingIdleGarrisonUnits | `3` | 1 | 236 |
| Building_StartTrainingIdleGarrisonUnits | `509704` | 1 | 236 |
| Building_StartTrainingIdleGarrisonUnits | `2` | 1 | 237 |
| Building_StartTrainingIdleGarrisonUnits | `510064` | 2 | 240, 242 |
| Building_StartTrainingIdleGarrisonUnits | `7` | 1 | 240 |
| Building_StartTrainingIdleGarrisonUnits | `4` | 1 | 242 |
| Building_StartTrainingIdleGarrisonUnits | `5` | 1 | 242 |
| Building_StartRepairIdleGarrisonUnits | `509692` | 1 | 275 |
| Building_StartRepairIdleGarrisonUnits | `509701` | 1 | 276 |
| Building_StartRepairIdleGarrisonUnits | `90` | 1 | 276 |
| Building_StartRepairIdleGarrisonUnits | `4` | 1 | 279 |
| Building_StartRepairIdleGarrisonUnits | `5` | 1 | 279 |
| Building_StartRepairIdleGarrisonUnits | `510064` | 2 | 279, 279 |
| Building_StartRepairIdleGarrisonUnits | `7` | 1 | 279 |
| Building_UnitsLeaveByUnitType | `14` | 1 | 298 |
| Building_UnitsLeaveByUnitType | `12` | 1 | 300 |
| Building_UnitsLeaveByUnitType | `10` | 1 | 301 |
| Building_UnitsLeaveByUnitType | `509692` | 1 | 305 |
| Building_UnitsLeaveByUnitType | `310` | 1 | 309 |
| Rules_LogCastleSiteFact | `52` | 1 | 331 |
| Rules_LogBuildingTransferFact | `52` | 1 | 340 |
| Rules_LogNewCastleFact | `52` | 1 | 349 |
| Rules_LogCastleDestroyedFact | `52` | 1 | 358 |
| Rules_LogCastleSchemeFact | `52` | 1 | 368 |
| Rules_LogCastleSchemeFact | `3` | 1 | 370 |
| Rules_LogBuildingCapturedFact | `52` | 1 | 378 |
| Rules_LogCastleUnderConstructionFact | `52` | 1 | 387 |
| Rules_LogCastleBuiltFactAndScheme | `52` | 1 | 396 |
| Rules_LogAssignedCastleFact | `52` | 1 | 406 |
| Rules_LogAssignedPlayerFact | `52` | 1 | 415 |
| Building_SelectedUnitLicenceMatchesTypeByIndex | `509674` | 1 | 428 |
| Building_SelectedUnitLicenceMatchesTypeByIndex | `510076` | 1 | 429 |
| Player_GetInternedNameByIndex | `140028` | 1 | 452 |
| Player_GetInternedNameByIndex | `11` | 2 | 455, 456 |
| Building_HasGarrisonUnitTypeByIndex | `509692` | 1 | 475 |
| Building_HasGarrisonUnitTypeByIndex | `310` | 1 | 478 |
| Map_RebuildCastleSiteAnchorCache | `2` | 1 | 523 |
| Building_CalcGarrisonFactStrength | `509692` | 1 | 551 |
| Building_OnGarrisonChange | `6` | 1 | 576 |
| Building_OnGarrisonChange | `510137` | 3 | 582, 585, 593 |
| Building_OnGarrisonChange | `16` | 1 | 587 |
| Building_OnGarrisonChange | `2` | 2 | 587, 592 |
| Rules_RegisterBuildingHostFunctions | `36` | 1 | 603 |
| Rules_RegisterBuildingHostFunctions | `118` | 9 | 604, 605, 606, 607 ... |
| Rules_RegisterBuildingHostFunctions | `98` | 16 | 613, 614, 615, 616 ... |
| Rules_RegisterBuildingHostFunctions | `105` | 17 | 629, 630, 631, 632 ... |
| Rules_RegisterBuildingHostFunctions | `115` | 1 | 646 |
| Rules_RegisterArmyHostFunctions | `36` | 1 | 653 |
| Rules_RegisterArmyHostFunctions | `98` | 15 | 654, 655, 656, 657 ... |
| Rules_RegisterArmyHostFunctions | `105` | 4 | 658, 660, 661, 672 |
| UnitStack_HasUnitsNeedingHealing | `6` | 1 | 685 |
| UnitStack_HasUnitsNeedingHealing | `10` | 1 | 686 |
| UnitStack_HasUnitsNeedingHealing | `3u` | 1 | 691 |
| UnitStack_HasUnitsNeedingHealing | `50` | 1 | 691 |
| UnitStack_HasUnitsNeedingHealing | `9` | 1 | 691 |
| UnitStack_FindPathToNearestHospitalCastle | `4` | 2 | 719, 720 |
| UnitStack_FindPathToNearestHospitalCastle | `16` | 1 | 720 |
| UnitStack_FindPathToNearestHospitalCastle | `416` | 1 | 720 |
| UnitStack_FindPathToNearestHospitalCastle | `100` | 1 | 750 |
| UnitStack_ExecuteHealingPathAndCheckArrival | `147180` | 1 | 768 |
| UnitStack_MoveToBuildingAndCheckArrival | `509675` | 1 | 782 |
| UnitStack_MoveToBuildingAndCheckArrival | `147490` | 1 | 783 |
| UnitStack_MoveToBuildingAndCheckArrival | `3` | 2 | 784, 785 |
| UnitStack_MoveToBuildingAndCheckArrival | `320` | 1 | 784 |
| UnitStack_MoveToBuildingAndCheckArrival | `147180` | 1 | 795 |
| Building_GetMaxEnemyStrengthUnderWalls | `509675` | 1 | 838 |
| Building_GetMaxEnemyStrengthUnderWalls | `2` | 4 | 841, 842, 847, 847 |
| Building_GetMaxEnemyStrengthUnderWalls | `200` | 2 | 844, 844 |
| Building_GetMaxEnemyStrengthUnderWalls | `0x1F4u` | 1 | 853 |
| Building_GetMaxEnemyStrengthUnderWalls | `0x28` | 1 | 854 |
| Building_GetMaxEnemyStrengthUnderWalls | `6` | 1 | 854 |
| Building_GetMaxEnemyStrengthUnderWalls | `147178` | 1 | 857 |
| Building_GetMaxEnemyStrengthUnderWalls | `509676` | 1 | 857 |
| Building_GetPlagueState | `510109` | 1 | 877 |
| Building_GetPlagueState | `7` | 1 | 877 |
| Unit_ExecuteQueuedPathAndCheckFinished | `147490` | 1 | 894 |
| UnitStack_DetachWeakUnitsToAdjacentTile | `10` | 4 | 914, 925, 929, 939 |
| UnitStack_DetachWeakUnitsToAdjacentTile | `3` | 1 | 923 |
| UnitStack_DetachWeakUnitsToAdjacentTile | `9` | 1 | 929 |
| UnitStack_DetachWeakUnitsToAdjacentTile | `4` | 1 | 959 |
| UnitStack_DetachUnitTypeToAdjacentTile | `10` | 3 | 985, 998, 1013 |
| UnitStack_DetachUnitTypeToAdjacentTile | `3` | 1 | 996 |
| UnitStack_DetachUnitTypeToAdjacentTile | `4` | 1 | 1033 |
| UnitStack_HasUnitType | `6` | 1 | 1057 |
| UnitStack_HasUnitType | `10` | 1 | 1064 |
| UnitStack_HasOnlyUnitType | `6` | 1 | 1079 |
| UnitStack_HasOnlyUnitType | `10` | 1 | 1086 |
| Rules_HostArmyHasOnlyUnitType | `2` | 1 | 1099 |
| UnitStack_GetHealthPercentAggregate | `6` | 1 | 1113 |
| UnitStack_GetHealthPercentAggregate | `9` | 4 | 1115, 1121, 1129, 1132 |
| UnitStack_GetHealthPercentAggregate | `10` | 1 | 1140 |
| UnitStack_RegroupWithOtherStackByHealth | `620` | 1 | 1179 |
| UnitStack_RegroupWithOtherStackByHealth | `28` | 9 | 1180, 1248, 1263, 1293 ... |
| UnitStack_RegroupWithOtherStackByHealth | `3` | 1 | 1181 |
| UnitStack_RegroupWithOtherStackByHealth | `147176` | 8 | 1199, 1199, 1206, 1216 ... |
| UnitStack_RegroupWithOtherStackByHealth | `43` | 1 | 1212 |
| UnitStack_RegroupWithOtherStackByHealth | `111` | 1 | 1229 |
| UnitStack_RegroupWithOtherStackByHealth | `6` | 4 | 1242, 1255, 1327, 1346 |
| UnitStack_RegroupWithOtherStackByHealth | `0x1Cu` | 6 | 1247, 1262, 1295, 1297 ... |
| UnitStack_RegroupWithOtherStackByHealth | `14` | 4 | 1248, 1263, 1337, 1357 |
| UnitStack_RegroupWithOtherStackByHealth | `3u` | 6 | 1248, 1263, 1296, 1298 ... |
| UnitStack_RegroupWithOtherStackByHealth | `10` | 8 | 1254, 1269, 1321, 1322 ... |
| UnitStack_RegroupWithOtherStackByHealth | `9` | 3 | 1288, 1288, 1315 |
| UnitStack_RegroupWithOtherStackByHealth | `8` | 1 | 1315 |

### src/strategic/00456706_00457789_strategic_008.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Rules_HostChangeTax | `2` | 1 | 46 |
| Rules_HostRemoveLicence | `2` | 1 | 57 |
| Rules_HostStartHealing | `2` | 1 | 69 |
| Rules_HostStartTraining | `2` | 1 | 82 |
| Rules_HostStartProduction | `2` | 1 | 90 |
| Rules_HostIsLicence | `2` | 1 | 111 |
| Rules_HostBuildCastle | `2` | 1 | 162 |
| Rules_HostBuildCastle | `3` | 1 | 163 |
| Rules_HostBuildCastle | `4` | 1 | 164 |
| Rules_HostBuildCastle | `5` | 1 | 166 |
| Rules_HostBuyLicence | `2` | 1 | 176 |
| Rules_HostIsMinimal | `2` | 1 | 255 |
| Rules_HostIsMinimal | `3` | 1 | 256 |
| Rules_HostIsMinimal | `4` | 1 | 257 |
| Rules_HostCanBuyLicence | `2` | 1 | 269 |
| Rules_HostLicenceIndex | `2` | 1 | 280 |
| Rules_HostIsProductionAny | `2` | 1 | 313 |
| Rules_HostLeadOutPeasants | `2` | 1 | 324 |
| Rules_HostLeadOutPeasants | `4` | 1 | 325 |
| Rules_HostLeadOutPeasants | `3` | 1 | 326 |
| Rules_HostUnitInCastleExists | `2` | 1 | 352 |
| Rules_HostLeadOutTroop | `2` | 1 | 367 |
| Rules_HostEnterCastle | `2` | 1 | 396 |
| Rules_HostJoinTroop | `2` | 1 | 409 |
| Rules_HostRegroupTroops | `2` | 1 | 420 |
| Rules_HostRegroupCastle | `2` | 1 | 431 |
| Rules_HostArmyHeadcount | `2` | 1 | 445 |
| Rules_HostArmyHasUnitsOfType | `2` | 1 | 457 |
| Rules_HostFindRoadNearCastle | `2` | 1 | 483 |
| Rules_HostDetachUnitsOfType | `2` | 1 | 539 |
| Rules_HostFindBest | `2` | 1 | 558 |
| Rules_HostFindBest | `4` | 1 | 559 |
| Rules_HostFindBest | `3` | 1 | 560 |
| Rules_HostFindBest | `5` | 1 | 561 |

### src/strategic/004589C0_004602F0_strategic_004.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `684` | 1 | 60 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `28` | 9 | 61, 144, 159, 189 ... |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `3` | 1 | 62 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `147176` | 8 | 81, 86, 91, 97 ... |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `509675` | 8 | 81, 86, 91, 98 ... |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `111` | 1 | 106 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `6` | 2 | 138, 223 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `0x1Cu` | 6 | 143, 158, 191, 193 ... |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `14` | 4 | 144, 159, 233, 253 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `3u` | 6 | 144, 159, 192, 194 ... |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `10` | 4 | 150, 217, 218, 239 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `18` | 2 | 152, 242 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `9` | 3 | 184, 184, 211 |
| UnitStack_RegroupWithBuildingGarrisonByHealth | `8` | 1 | 211 |
| AI_CalcStrategicPriorityScore | `80` | 2 | 273, 285 |
| AI_EvaluateStrategicTargetAtTile | `0x1F4u` | 1 | 324 |
| AI_EvaluateStrategicTargetAtTile | `0x28` | 1 | 327 |
| AI_EvaluateStrategicTargetAtTile | `147180` | 1 | 327 |
| AI_EvaluateStrategicTargetAtTile | `0x64` | 1 | 330 |
| AI_EvaluateStrategicTargetAtTile | `4` | 3 | 331, 331, 342 |
| AI_EvaluateStrategicTargetAtTile | `16` | 1 | 332 |
| AI_EvaluateStrategicTargetAtTile | `3` | 1 | 336 |
| AI_EvaluateStrategicTargetAtTile | `2` | 2 | 353, 359 |
| AI_EvaluateStrategicTargetAtTile | `509676` | 1 | 358 |
| AI_EvaluateStrategicTargetAtTile | `147178` | 1 | 359 |
| AI_FindBestStrategicTargetNearTile | `1082130432` | 1 | 405 |
| AI_FindBestStrategicTargetNearTile | `3` | 1 | 444 |
| AI_FindBestStrategicTargetNearTile | `4` | 1 | 444 |
| AI_FindBestStrategicTargetNearTile | `100` | 2 | 445, 446 |
| createUnit | `200` | 1 | 466 |
| createUnit | `2` | 1 | 467 |
| createUnit | `6` | 1 | 471 |
| createUnit | `145` | 1 | 478 |
| createCastle | `200` | 1 | 510 |
| createCastle | `2` | 1 | 513 |
| createCastle | `6` | 1 | 517 |
| createCastle | `145` | 1 | 524 |
| createCastle | `509690` | 1 | 533 |
| WorldMap_DrawMission01ShrineMarker | `11` | 2 | 551, 553 |
| WorldMap_DrawMission01ShrineMarker | `16` | 2 | 551, 554 |
| WorldMap_DrawMission01ShrineMarker | `2` | 1 | 554 |
| WorldMap_DrawMission01ShrineMarker | `50` | 2 | 554, 554 |
| WorldMap_DrawMission01ShrineMarker | `90` | 1 | 554 |
| WorldMap_DrawMission01ShrineMarker | `730` | 1 | 555 |
| WorldMap_DrawMission01ShrineMarker | `63` | 2 | 556, 556 |
| Mission05_MarkFailureOnFriendlyAttack | `2` | 1 | 565 |
| WorldMap_DrawMission07TreasureMarker | `45` | 2 | 587, 587 |
| WorldMap_DrawMission07TreasureMarker | `55` | 2 | 587, 587 |
| WorldMap_DrawMission07TreasureMarker | `27` | 2 | 588, 588 |
| WorldMap_DrawMission07TreasureMarker | `50` | 2 | 588, 588 |
| WorldMap_DrawMission07TreasureMarker | `35` | 2 | 589, 589 |
| WorldMap_DrawMission07TreasureMarker | `63` | 2 | 589, 589 |
| WorldMap_DrawMission07TreasureMarker | `962` | 1 | 591 |
| WorldMap_DrawMission07TreasureMarker | `46` | 2 | 592, 607 |
| WorldMap_DrawMission07TreasureMarker | `52` | 2 | 592, 607 |
| WorldMap_DrawMission07TreasureMarker | `14` | 2 | 601, 603 |
| WorldMap_DrawMission07TreasureMarker | `68` | 2 | 601, 603 |
| WorldMap_DrawMission07TreasureMarker | `961` | 1 | 606 |
| WorldMap_DrawMission11ShrineMarker | `2` | 2 | 629, 632 |
| WorldMap_DrawMission11ShrineMarker | `44` | 2 | 629, 631 |
| WorldMap_DrawMission11ShrineMarker | `16` | 1 | 632 |
| WorldMap_DrawMission11ShrineMarker | `50` | 2 | 632, 632 |
| WorldMap_DrawMission11ShrineMarker | `90` | 1 | 632 |
| WorldMap_DrawMission11ShrineMarker | `738` | 1 | 633 |
| WorldMap_DrawMission11ShrineMarker | `63` | 2 | 634, 634 |
| Mission_MarkObjective15CompleteOnAttack | `2` | 1 | 643 |
| Mission_MarkObjective15CompleteOnAttack | `3` | 1 | 643 |
| WorldMap_DrawMission17TreasureMarker | `34` | 4 | 658, 658, 660, 660 |
| WorldMap_DrawMission17TreasureMarker | `50` | 2 | 658, 658 |
| WorldMap_DrawMission17TreasureMarker | `51` | 2 | 659, 659 |
| WorldMap_DrawMission17TreasureMarker | `73` | 2 | 659, 659 |
| WorldMap_DrawMission17TreasureMarker | `77` | 2 | 660, 660 |
| WorldMap_DrawMission17TreasureMarker | `24` | 2 | 661, 661 |
| WorldMap_DrawMission17TreasureMarker | `49` | 2 | 661, 661 |
| WorldMap_DrawMission17TreasureMarker | `962` | 1 | 663 |
| WorldMap_DrawMission17TreasureMarker | `46` | 1 | 664 |
| WorldMap_DrawMission17TreasureMarker | `52` | 1 | 664 |
| Mission_CheckObjectiveComplete | `0x28` | 7 | 754, 823, 857, 899 ... |
| Mission_CheckObjectiveComplete | `147180` | 6 | 754, 823, 899, 945 ... |
| Mission_CheckObjectiveComplete | `147178` | 8 | 755, 824, 833, 859 ... |
| Mission_CheckObjectiveComplete | `147176` | 7 | 765, 905, 909, 952 ... |
| Mission_CheckObjectiveComplete | `11` | 4 | 777, 779, 779, 964 |
| Mission_CheckObjectiveComplete | `16` | 10 | 777, 779, 779, 813 ... |
| Mission_CheckObjectiveComplete | `2` | 10 | 781, 785, 844, 860 ... |
| Mission_CheckObjectiveComplete | `509676` | 17 | 782, 788, 797, 803 ... |
| Mission_CheckObjectiveComplete | `564710` | 2 | 782, 788 |
| Mission_CheckObjectiveComplete | `41` | 2 | 786, 878 |
| Mission_CheckObjectiveComplete | `68` | 3 | 787, 882, 893 |
| Mission_CheckObjectiveComplete | `3` | 3 | 790, 814, 824 |
| Mission_CheckObjectiveComplete | `0xD` | 1 | 791 |
| Mission_CheckObjectiveComplete | `0xAu` | 1 | 792 |
| Mission_CheckObjectiveComplete | `10` | 2 | 794, 949 |
| Mission_CheckObjectiveComplete | `4` | 12 | 796, 800, 812, 812 ... |
| Mission_CheckObjectiveComplete | `567712` | 2 | 797, 803 |
| Mission_CheckObjectiveComplete | `56` | 1 | 801 |
| Mission_CheckObjectiveComplete | `69` | 1 | 802 |
| Mission_CheckObjectiveComplete | `5` | 5 | 805, 833, 836, 846 ... |
| Mission_CheckObjectiveComplete | `100` | 5 | 816, 850, 911, 995 ... |
| Mission_CheckObjectiveComplete | `6` | 4 | 857, 872, 876, 1074 |
| Mission_CheckObjectiveComplete | `574456` | 2 | 873, 879 |
| Mission_CheckObjectiveComplete | `90` | 1 | 877 |
| Mission_CheckObjectiveComplete | `7` | 2 | 881, 887 |
| Mission_CheckObjectiveComplete | `14` | 4 | 882, 893, 972, 979 |
| Mission_CheckObjectiveComplete | `27` | 2 | 882, 891 |
| Mission_CheckObjectiveComplete | `35` | 2 | 882, 892 |
| Mission_CheckObjectiveComplete | `45` | 3 | 882, 889, 890 |
| Mission_CheckObjectiveComplete | `50` | 5 | 882, 891, 1028, 1034 ... |
| Mission_CheckObjectiveComplete | `55` | 3 | 882, 888, 890 |
| Mission_CheckObjectiveComplete | `63` | 2 | 882, 892 |
| Mission_CheckObjectiveComplete | `8` | 4 | 893, 922, 930, 1039 |
| Mission_CheckObjectiveComplete | `509692` | 2 | 924, 1070 |
| Mission_CheckObjectiveComplete | `562420` | 1 | 924 |
| Mission_CheckObjectiveComplete | `23` | 1 | 930 |
| Mission_CheckObjectiveComplete | `30` | 1 | 930 |
| Mission_CheckObjectiveComplete | `9` | 2 | 932, 940 |
| Mission_CheckObjectiveComplete | `7115` | 2 | 937, 1088 |
| Mission_CheckObjectiveComplete | `0xA` | 1 | 942 |
| Mission_CheckObjectiveComplete | `0xB` | 1 | 961 |
| Mission_CheckObjectiveComplete | `44` | 3 | 962, 964, 964 |
| Mission_CheckObjectiveComplete | `0xC` | 1 | 966 |
| Mission_CheckObjectiveComplete | `568202` | 2 | 967, 973 |
| Mission_CheckObjectiveComplete | `12` | 1 | 970 |
| Mission_CheckObjectiveComplete | `59` | 1 | 971 |
| Mission_CheckObjectiveComplete | `0xE` | 1 | 975 |
| Mission_CheckObjectiveComplete | `566822` | 2 | 976, 982 |
| Mission_CheckObjectiveComplete | `52` | 1 | 980 |
| Mission_CheckObjectiveComplete | `24` | 3 | 981, 1028, 1039 |
| Mission_CheckObjectiveComplete | `0xF` | 1 | 984 |
| Mission_CheckObjectiveComplete | `15` | 2 | 992, 1006 |
| Mission_CheckObjectiveComplete | `0x10` | 1 | 1018 |
| Mission_CheckObjectiveComplete | `574660` | 2 | 1019, 1025 |
| Mission_CheckObjectiveComplete | `91` | 1 | 1023 |
| Mission_CheckObjectiveComplete | `43` | 1 | 1024 |
| Mission_CheckObjectiveComplete | `0x11` | 1 | 1027 |
| Mission_CheckObjectiveComplete | `34` | 5 | 1028, 1028, 1035, 1036 ... |
| Mission_CheckObjectiveComplete | `49` | 2 | 1028, 1039 |
| Mission_CheckObjectiveComplete | `51` | 2 | 1028, 1037 |
| Mission_CheckObjectiveComplete | `73` | 2 | 1028, 1037 |
| Mission_CheckObjectiveComplete | `77` | 2 | 1028, 1038 |
| Mission_CheckObjectiveComplete | `17` | 1 | 1033 |
| Mission_CheckObjectiveComplete | `0x12` | 1 | 1066 |
| Mission_CheckObjectiveComplete | `573450` | 1 | 1070 |
| Mission_CheckObjectiveComplete | `18` | 1 | 1076 |
| Mission_CheckObjectiveComplete | `38` | 1 | 1076 |
| Mission_CheckObjectiveComplete | `85` | 1 | 1076 |
| Mission_CheckObjectiveComplete | `0x13` | 1 | 1078 |
| Mission_CheckObjectiveComplete | `19` | 2 | 1081, 1091 |
| Mission_CheckObjectiveComplete | `2846` | 1 | 1084 |
| Mission_CheckFailureCondition | `3` | 1 | 1152 |
| Mission_CheckFailureCondition | `509676` | 4 | 1153, 1185, 1201, 1232 |
| Mission_CheckFailureCondition | `560616` | 1 | 1153 |
| Mission_CheckFailureCondition | `4` | 5 | 1154, 1183, 1183, 1230 ... |
| Mission_CheckFailureCondition | `0xE` | 1 | 1155 |
| Mission_CheckFailureCondition | `0x14u` | 1 | 1156 |
| Mission_CheckFailureCondition | `5` | 1 | 1157 |
| Mission_CheckFailureCondition | `8` | 1 | 1162 |
| Mission_CheckFailureCondition | `0x28` | 2 | 1166, 1212 |
| Mission_CheckFailureCondition | `147178` | 2 | 1166, 1213 |
| Mission_CheckFailureCondition | `147180` | 4 | 1166, 1170, 1212, 1217 |
| Mission_CheckFailureCondition | `10` | 2 | 1168, 1215 |
| Mission_CheckFailureCondition | `16` | 2 | 1184, 1231 |
| Mission_CheckFailureCondition | `509692` | 2 | 1189, 1236 |
| Mission_CheckFailureCondition | `100` | 2 | 1194, 1241 |
| Mission_CheckFailureCondition | `12` | 1 | 1199 |
| Mission_CheckFailureCondition | `0xD` | 1 | 1200 |
| Mission_CheckFailureCondition | `561026` | 1 | 1201 |
| Mission_CheckFailureCondition | `0xF` | 1 | 1202 |
| Mission_CheckFailureCondition | `0x12` | 1 | 1204 |
| Mission_CheckFailureCondition | `6` | 1 | 1246 |

### src/strategic/00460360_00460910_strategic_005.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Scenario_LoadMissionByIndex | `5` | 50 | 39, 74, 104, 145 ... |
| Scenario_LoadMissionByIndex | `2` | 261 | 52, 85, 87, 101 ... |
| Scenario_LoadMissionByIndex | `30` | 10 | 52, 54, 223, 337 ... |
| Scenario_LoadMissionByIndex | `42` | 8 | 52, 214, 301, 304 ... |
| Scenario_LoadMissionByIndex | `44` | 12 | 54, 55, 56, 85 ... |
| Scenario_LoadMissionByIndex | `31` | 10 | 55, 134, 173, 188 ... |
| Scenario_LoadMissionByIndex | `32` | 11 | 56, 232, 583, 588 ... |
| Scenario_LoadMissionByIndex | `45` | 12 | 58, 279, 388, 426 ... |
| Scenario_LoadMissionByIndex | `46` | 3 | 58, 85, 124 |
| Scenario_LoadMissionByIndex | `15` | 13 | 59, 174, 183, 615 ... |
| Scenario_LoadMissionByIndex | `6` | 17 | 59, 128, 184, 316 ... |
| Scenario_LoadMissionByIndex | `14` | 10 | 60, 335, 336, 391 ... |
| Scenario_LoadMissionByIndex | `48` | 15 | 60, 86, 92, 182 ... |
| Scenario_LoadMissionByIndex | `11` | 16 | 61, 479, 568, 578 ... |
| Scenario_LoadMissionByIndex | `35` | 12 | 61, 132, 191, 390 ... |
| Scenario_LoadMissionByIndex | `39` | 9 | 62, 188, 189, 191 ... |
| Scenario_LoadMissionByIndex | `49` | 10 | 62, 192, 692, 769 ... |
| Scenario_LoadMissionByIndex | `3` | 138 | 63, 142, 144, 150 ... |
| Scenario_LoadMissionByIndex | `40` | 12 | 63, 127, 186, 794 ... |
| Scenario_LoadMissionByIndex | `12` | 19 | 64, 93, 177, 178 ... |
| Scenario_LoadMissionByIndex | `19` | 6 | 64, 417, 853, 855 ... |
| Scenario_LoadMissionByIndex | `23` | 23 | 87, 165, 166, 167 ... |
| Scenario_LoadMissionByIndex | `18` | 23 | 88, 92, 121, 127 ... |
| Scenario_LoadMissionByIndex | `25` | 21 | 90, 116, 117, 238 ... |
| Scenario_LoadMissionByIndex | `24` | 8 | 91, 115, 118, 174 ... |
| Scenario_LoadMissionByIndex | `91` | 10 | 96, 128, 137, 689 ... |
| Scenario_LoadMissionByIndex | `21` | 15 | 97, 99, 138, 140 ... |
| Scenario_LoadMissionByIndex | `90` | 3 | 98, 139, 368 |
| Scenario_LoadMissionByIndex | `98` | 7 | 115, 116, 119, 831 ... |
| Scenario_LoadMissionByIndex | `97` | 8 | 117, 118, 509, 517 ... |
| Scenario_LoadMissionByIndex | `26` | 11 | 119, 288, 720, 728 ... |
| Scenario_LoadMissionByIndex | `41` | 15 | 120, 172, 212, 213 ... |
| Scenario_LoadMissionByIndex | `68` | 9 | 120, 131, 131, 294 ... |
| Scenario_LoadMissionByIndex | `16` | 7 | 123, 577, 621, 795 ... |
| Scenario_LoadMissionByIndex | `83` | 7 | 123, 591, 682, 1024 ... |
| Scenario_LoadMissionByIndex | `69` | 13 | 124, 132, 216, 298 ... |
| Scenario_LoadMissionByIndex | `61` | 8 | 125, 562, 830, 946 ... |
| Scenario_LoadMissionByIndex | `87` | 3 | 125, 311, 836 |
| Scenario_LoadMissionByIndex | `52` | 11 | 126, 130, 566, 567 ... |
| Scenario_LoadMissionByIndex | `58` | 8 | 126, 292, 568, 572 ... |
| Scenario_LoadMissionByIndex | `85` | 8 | 129, 342, 504, 513 ... |
| Scenario_LoadMissionByIndex | `9` | 17 | 129, 170, 185, 218 ... |
| Scenario_LoadMissionByIndex | `43` | 15 | 130, 187, 215, 305 ... |
| Scenario_LoadMissionByIndex | `77` | 9 | 133, 294, 429, 431 ... |
| Scenario_LoadMissionByIndex | `94` | 4 | 133, 551, 557, 693 |
| Scenario_LoadMissionByIndex | `74` | 8 | 134, 348, 349, 886 ... |
| Scenario_LoadMissionByIndex | `300` | 3 | 162, 1111, 1117 |
| Scenario_LoadMissionByIndex | `438` | 25 | 162, 280, 289, 373 ... |
| Scenario_LoadMissionByIndex | `20` | 14 | 164, 164, 165, 166 ... |
| Scenario_LoadMissionByIndex | `22` | 16 | 171, 176, 480, 487 ... |
| Scenario_LoadMissionByIndex | `34` | 11 | 172, 414, 590, 626 ... |
| Scenario_LoadMissionByIndex | `13` | 13 | 173, 175, 334, 547 ... |
| Scenario_LoadMissionByIndex | `37` | 6 | 176, 626, 852, 1057 ... |
| Scenario_LoadMissionByIndex | `0xFC` | 4 | 180, 512, 520, 778 |
| Scenario_LoadMissionByIndex | `10` | 16 | 181, 380, 382, 465 ... |
| Scenario_LoadMissionByIndex | `27` | 22 | 181, 389, 415, 424 ... |
| Scenario_LoadMissionByIndex | `29` | 8 | 183, 475, 476, 477 ... |
| Scenario_LoadMissionByIndex | `204` | 1 | 190 |
| Scenario_LoadMissionByIndex | `3u` | 20 | 190, 223, 310, 345 ... |
| Scenario_LoadMissionByIndex | `47` | 9 | 193, 281, 282, 283 ... |
| Scenario_LoadMissionByIndex | `4` | 84 | 197, 199, 244, 334 ... |
| Scenario_LoadMissionByIndex | `50` | 16 | 213, 214, 215, 235 ... |
| Scenario_LoadMissionByIndex | `56` | 18 | 216, 219, 221, 230 ... |
| Scenario_LoadMissionByIndex | `71` | 14 | 219, 221, 229, 230 ... |
| Scenario_LoadMissionByIndex | `567716` | 1 | 220 |
| Scenario_LoadMissionByIndex | `55` | 10 | 229, 388, 428, 562 ... |
| Scenario_LoadMissionByIndex | `57` | 14 | 231, 291, 347, 410 ... |
| Scenario_LoadMissionByIndex | `36` | 16 | 232, 416, 417, 660 ... |
| Scenario_LoadMissionByIndex | `567712` | 1 | 244 |
| Scenario_LoadMissionByIndex | `200` | 7 | 280, 357, 366, 790 ... |
| Scenario_LoadMissionByIndex | `70` | 11 | 281, 299, 407, 678 ... |
| Scenario_LoadMissionByIndex | `72` | 6 | 283, 286, 409, 410 ... |
| Scenario_LoadMissionByIndex | `73` | 7 | 284, 293, 297, 688 ... |
| Scenario_LoadMissionByIndex | `1000` | 3 | 289, 373, 845 |
| Scenario_LoadMissionByIndex | `67` | 6 | 295, 372, 430, 686 ... |
| Scenario_LoadMissionByIndex | `79` | 12 | 295, 296, 298, 299 ... |
| Scenario_LoadMissionByIndex | `63` | 10 | 297, 390, 564, 567 ... |
| Scenario_LoadMissionByIndex | `59` | 8 | 300, 485, 488, 490 ... |
| Scenario_LoadMissionByIndex | `54` | 8 | 301, 338, 341, 419 ... |
| Scenario_LoadMissionByIndex | `53` | 8 | 307, 411, 412, 559 ... |
| Scenario_LoadMissionByIndex | `564880` | 1 | 308 |
| Scenario_LoadMissionByIndex | `66` | 8 | 311, 488, 500, 501 ... |
| Scenario_LoadMissionByIndex | `81` | 7 | 342, 678, 679, 841 ... |
| Scenario_LoadMissionByIndex | `92` | 3 | 343, 344, 888 |
| Scenario_LoadMissionByIndex | `251` | 1 | 345 |
| Scenario_LoadMissionByIndex | `17` | 10 | 346, 622, 740, 791 ... |
| Scenario_LoadMissionByIndex | `38` | 6 | 347, 732, 843, 945 ... |
| Scenario_LoadMissionByIndex | `28` | 21 | 351, 482, 486, 723 ... |
| Scenario_LoadMissionByIndex | `145` | 2 | 354, 363 |
| Scenario_LoadMissionByIndex | `82` | 6 | 359, 360, 680, 681 ... |
| Scenario_LoadMissionByIndex | `2000` | 2 | 375, 854 |
| Scenario_LoadMissionByIndex | `7` | 15 | 385, 387, 657, 658 ... |
| Scenario_LoadMissionByIndex | `51` | 9 | 408, 767, 833, 911 ... |
| Scenario_LoadMissionByIndex | `33` | 10 | 427, 428, 589, 620 ... |
| Scenario_LoadMissionByIndex | `75` | 3 | 430, 436, 851 |
| Scenario_LoadMissionByIndex | `78` | 4 | 432, 433, 838, 1122 |
| Scenario_LoadMissionByIndex | `76` | 4 | 437, 438, 890, 898 |
| Scenario_LoadMissionByIndex | `0xFCu` | 5 | 443, 973, 1043, 1053 ... |
| Scenario_LoadMissionByIndex | `8` | 6 | 451, 453, 471, 475 ... |
| Scenario_LoadMissionByIndex | `100` | 6 | 474, 549, 617, 936 ... |
| Scenario_LoadMissionByIndex | `60` | 4 | 491, 574, 829, 952 |
| Scenario_LoadMissionByIndex | `62` | 10 | 492, 559, 563, 566 ... |
| Scenario_LoadMissionByIndex | `64` | 8 | 493, 494, 495, 496 ... |
| Scenario_LoadMissionByIndex | `84` | 7 | 493, 500, 501, 583 ... |
| Scenario_LoadMissionByIndex | `86` | 12 | 505, 506, 587, 588 ... |
| Scenario_LoadMissionByIndex | `96` | 6 | 506, 508, 513, 580 ... |
| Scenario_LoadMissionByIndex | `88` | 5 | 507, 508, 509, 1110 ... |
| Scenario_LoadMissionByIndex | `95` | 7 | 507, 551, 558, 577 ... |
| Scenario_LoadMissionByIndex | `103` | 1 | 510 |
| Scenario_LoadMissionByIndex | `102` | 2 | 514, 518 |
| Scenario_LoadMissionByIndex | `0xF8` | 4 | 550, 554, 586, 885 |
| Scenario_LoadMissionByIndex | `444` | 8 | 550, 550, 554, 554 ... |
| Scenario_LoadMissionByIndex | `500` | 2 | 553, 585 |
| Scenario_LoadMissionByIndex | `3000` | 2 | 561, 570 |
| Scenario_LoadMissionByIndex | `430` | 4 | 618, 619, 764, 765 |
| Scenario_LoadMissionByIndex | `0x32` | 1 | 619 |
| Scenario_LoadMissionByIndex | `0xF000` | 2 | 619, 765 |
| Scenario_LoadMissionByIndex | `0xFFF` | 2 | 619, 619 |
| Scenario_LoadMissionByIndex | `5000` | 1 | 685 |
| Scenario_LoadMissionByIndex | `0xF` | 1 | 772 |
| Scenario_LoadMissionByIndex | `80` | 5 | 840, 842, 1051, 1052 ... |
| Scenario_LoadMissionByIndex | `93` | 1 | 889 |
| Scenario_LoadMissionByIndex | `65` | 4 | 967, 968, 1114, 1115 |
| Scenario_LoadMissionByIndex | `2u` | 2 | 974, 1044 |
| Scenario_LoadMissionByIndex | `89` | 2 | 1012, 1115 |
| Scenario_LoadMissionByIndex | `600` | 1 | 1096 |
| Scenario_LoadMissionByIndexAndPlay | `27` | 1 | 1142 |
| Scenario_LoadMissionByIndexAndPlay | `0x1Bu` | 2 | 1145, 1152 |
| Scenario_LoadMissionByIndexAndPlay | `147147` | 2 | 1145, 1152 |
| Scenario_LoadMissionByIndexAndPlay | `10` | 2 | 1146, 1151 |
| RenderState_ConstructGlobalInstance | `9` | 2 | 1181, 1183 |
| Compat_SyncRenderCursorGlobals | `9` | 1 | 1190 |
| Compat_SyncRenderCursorGlobals | `10` | 1 | 1191 |
| Compat_SyncRenderCursorGlobals | `277` | 1 | 1192 |
| Compat_MenuProbeTraceRenderInput | `1024` | 1 | 1235 |
| Compat_MenuProbeTraceRenderInput | `44` | 1 | 1247 |
| Compat_MenuProbeTraceRenderInput | `1108` | 3 | 1248, 1249, 1250 |
| Compat_MenuProbeTraceRenderInput | `36` | 1 | 1248 |
| Compat_MenuProbeTraceRenderInput | `40` | 1 | 1249 |
| RenderState_ConstructDefault | `80` | 1 | 1263 |
| RenderState_ConstructDefault | `64` | 2 | 1264, 1268 |
| RenderState_ConstructDefault | `60` | 1 | 1265 |
| RenderState_ConstructDefault | `56` | 1 | 1266 |
| RenderState_ConstructDefault | `639` | 1 | 1266 |
| RenderState_ConstructDefault | `479` | 1 | 1267 |
| RenderState_ConstructDefault | `52` | 1 | 1267 |
| RenderState_ConstructDefault | `48` | 1 | 1268 |
| RenderState_ConstructDefault | `16` | 1 | 1269 |
| RenderState_ConstructDefault | `256` | 2 | 1270, 1271 |
| RenderState_ConstructDefault | `50` | 1 | 1271 |
| RenderState_ConstructDefault | `257` | 1 | 1272 |
| RenderState_ConstructDefault | `6` | 1 | 1272 |
| RenderState_ConstructDefault | `2` | 1 | 1273 |
| RenderState_ConstructDefault | `258` | 1 | 1273 |
| RenderState_ConstructDefault | `259` | 1 | 1274 |
| RenderState_ConstructDefault | `5` | 1 | 1274 |
| RenderState_ConstructDefault | `260` | 1 | 1275 |
| RenderState_ConstructDefault | `20` | 1 | 1276 |
| RenderState_InitCursorResources | `44` | 1 | 1288 |
| RenderState_InitCursorResources | `4112` | 1 | 1289 |
| RenderState_InitCursorResources | `64` | 6 | 1292, 1296, 1297, 1297 ... |
| RenderState_InitCursorResources | `188` | 2 | 1293, 1300 |
| RenderState_InitCursorResources | `8` | 1 | 1299 |
| RenderState_InitCursorResources | `12` | 1 | 1303 |
| RenderState_InitCursorResources | `20` | 2 | 1305, 1306 |
| RenderState_InitCursorResources | `1108` | 2 | 1306, 1307 |
| RenderState_InitCursorResources | `36` | 1 | 1306 |
| RenderState_InitCursorResources | `48` | 1 | 1306 |
| RenderState_InitCursorResources | `60` | 2 | 1306, 1307 |
| RenderState_InitCursorResources | `24` | 1 | 1307 |
| RenderState_InitCursorResources | `40` | 1 | 1307 |
| RenderState_InitCursorResources | `52` | 1 | 1307 |
| RenderState_InitCursorResources | `480` | 1 | 1308 |
| RenderState_InitCursorResources | `640` | 1 | 1308 |
| RenderState_InitCursorResources | `80` | 1 | 1309 |
| RenderState_ReleaseCursorResources | `64` | 1 | 1320 |
| RenderState_ReleaseCursorResources | `8` | 1 | 1321 |
| RenderState_ReleaseCursorResources | `184` | 2 | 1324, 1331 |
| RenderState_ReleaseCursorResources | `2` | 2 | 1326, 1333 |
| RenderState_ReleaseCursorResources | `12` | 1 | 1328 |
| DD_Pump | `1112` | 2 | 1372, 1375 |
| DD_Pump | `20` | 2 | 1376, 1403 |
| DD_Pump | `68` | 1 | 1379 |
| DD_Pump | `1108` | 4 | 1380, 1381, 1403, 1404 |
| DD_Pump | `36` | 2 | 1380, 1403 |
| DD_Pump | `72` | 1 | 1380 |
| DD_Pump | `40` | 2 | 1381, 1404 |
| DD_Pump | `76` | 1 | 1381 |
| DD_Pump | `4` | 6 | 1384, 1412, 1418, 1448 ... |
| DD_Pump | `8` | 4 | 1387, 1398, 1399, 1416 |
| DD_Pump | `28` | 2 | 1391, 1395 |
| DD_Pump | `32` | 3 | 1396, 1432, 1473 |
| DD_Pump | `48` | 7 | 1403, 1411, 1418, 1466 ... |
| DD_Pump | `24` | 1 | 1404 |
| DD_Pump | `52` | 6 | 1405, 1418, 1465, 1468 ... |
| DD_Pump | `12` | 5 | 1417, 1426, 1445, 1458 ... |
| DD_Pump | `16` | 4 | 1427, 1446, 1459, 1468 |
| DD_Pump | `64` | 2 | 1431, 1472 |
| RenderState_SetMouseSpeed | `32` | 1 | 1512 |
| DD_IsFlipping | `44` | 1 | 1518 |
| DD_IsLost | `2` | 1 | 1524 |
| DD_IsLost | `44` | 1 | 1524 |
| Input_PollEventsUntil | `56` | 3 | 1532, 1533, 1535 |
| Input_PollEventsUntil | `9` | 1 | 1543 |

### src/strategic/00460950_004612E0_strategic_006.cpp

Missing evidence: mission IDs/coordinates and scenario data, objective thresholds, host argument indexes, rule protocols and device fields. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| RenderState_IsCursorFlipStillActive | `1104` | 1 | 31 |
| RenderState_IsCursorFlipStillActive | `68` | 1 | 31 |
| RenderState_IsCursorFlipStillActive | `1108` | 4 | 33, 35, 38, 40 |
| RenderState_IsCursorFlipStillActive | `36` | 2 | 33, 35 |
| RenderState_IsCursorFlipStillActive | `72` | 2 | 33, 35 |
| RenderState_IsCursorFlipStillActive | `1116` | 2 | 36, 41 |
| RenderState_IsCursorFlipStillActive | `40` | 2 | 38, 40 |
| RenderState_IsCursorFlipStillActive | `76` | 2 | 38, 40 |
| Render_FlipRect | `56` | 3 | 80, 81, 83 |
| Render_FlipRect | `20` | 1 | 84 |
| RenderState_PollInputAndClampCursor | `8` | 2 | 110, 111 |
| RenderState_PollInputAndClampCursor | `9` | 5 | 110, 120, 121, 126 ... |
| RenderState_PollInputAndClampCursor | `10` | 6 | 112, 114, 123, 124 ... |
| RenderState_PollInputAndClampCursor | `11` | 3 | 113, 116, 118 |
| RenderState_PollInputAndClampCursor | `2` | 1 | 118 |
| RenderState_PollInputAndClampCursor | `4` | 1 | 119 |
| RenderState_PollInputAndClampCursor | `5` | 1 | 122 |
| RenderState_PollInputAndClampCursor | `6` | 1 | 125 |
| RenderState_PollInputAndClampCursor | `7` | 1 | 129 |
| RenderState_WarpCursorAndPump | `277` | 2 | 144, 145 |
| RenderState_WarpCursorAndPump | `9` | 1 | 144 |
| RenderState_WarpCursorAndPump | `10` | 1 | 145 |
| RenderState_RecalculateCursorBoundsForRect | `15` | 1 | 164 |
| RenderState_RecalculateCursorBoundsForRect | `10` | 2 | 165, 167 |
| RenderState_RecalculateCursorBoundsForRect | `12` | 2 | 166, 169 |
| RenderState_RecalculateCursorBoundsForRect | `6` | 2 | 167, 172 |
| RenderState_RecalculateCursorBoundsForRect | `8` | 1 | 168 |
| RenderState_RecalculateCursorBoundsForRect | `277` | 4 | 170, 171, 172, 173 |
| RenderState_RecalculateCursorBoundsForRect | `4` | 1 | 170 |
| RenderState_RecalculateCursorBoundsForRect | `5` | 1 | 171 |
| RenderState_RecalculateCursorBoundsForRect | `7` | 1 | 173 |
| RenderState_PumpIfRectInViewBounds | `15` | 1 | 187 |
| RenderState_PumpIfRectInViewBounds | `12` | 3 | 188, 188, 189 |
| RenderState_PumpIfRectInViewBounds | `13` | 2 | 190, 191 |
| RenderState_PumpIfRectInViewBounds | `16` | 1 | 190 |
| RenderState_LoadDefaultCursorSprite | `64` | 4 | 202, 203, 208, 212 |
| RenderState_LoadDefaultCursorSprite | `4112` | 1 | 204 |
| RenderState_LoadOrRenderCursorLabelSprite | `104` | 2 | 227, 228 |
| RenderState_LoadOrRenderCursorLabelSprite | `64` | 5 | 230, 231, 254, 259 ... |
| RenderState_LoadOrRenderCursorLabelSprite | `768` | 1 | 235 |
| RenderState_LoadOrRenderCursorLabelSprite | `4112` | 1 | 251 |
| RenderState_LoadOrRenderCursorLabelSprite | `80` | 1 | 259 |
| Compat_RenderStateMethodPointer | `1120` | 1 | 270 |
| Compat_RenderStateMethodPointer | `4` | 1 | 273 |
| Compat_RenderStateCursorDescriptor | `60` | 2 | 294, 298 |
| Compat_PresentPrimaryIndexedSurfaceToPlatform | `0xD0` | 1 | 307 |
| Compat_PresentPrimaryIndexedSurfaceToPlatform | `220` | 1 | 312 |
| Compat_RenderClearPresentedRect | `8` | 1 | 326 |
| Compat_RenderClearPresentedRect | `12` | 1 | 333 |
| Compat_RenderClearPresentedRect | `16` | 1 | 334 |
| Compat_RenderClearPresentedRect | `4` | 1 | 336 |
| RenderState_SelectCursorDescriptor | `60` | 4 | 355, 358, 363, 364 |
| RenderState_SelectCursorDescriptor | `4` | 2 | 367, 382 |
| RenderState_SelectCursorDescriptor | `64` | 2 | 369, 370 |
| RenderState_SelectCursorDescriptor | `12` | 1 | 376 |
| RenderState_SelectCursorDescriptor | `16` | 1 | 377 |
| RenderState_SelectCursorDescriptor | `32` | 1 | 378 |
| RenderState_SelectCursorDescriptor | `28` | 1 | 379 |
| RenderState_SelectCursorDescriptor | `480` | 1 | 380 |
| RenderState_SelectCursorDescriptor | `640` | 1 | 380 |
| RenderState_SelectCursorDescriptor | `20` | 2 | 381, 383 |
| RenderState_SelectCursorDescriptor | `1108` | 2 | 383, 384 |
| RenderState_SelectCursorDescriptor | `36` | 1 | 383 |
| RenderState_SelectCursorDescriptor | `48` | 1 | 383 |
| RenderState_SelectCursorDescriptor | `24` | 1 | 384 |
| RenderState_SelectCursorDescriptor | `40` | 1 | 384 |
| RenderState_SelectCursorDescriptor | `52` | 1 | 384 |
| Render_Present | `8` | 1 | 401 |
| Render_Present | `52` | 4 | 412, 415, 433, 437 |
| Render_Present | `48` | 4 | 413, 414, 432, 436 |
| Render_Present | `12` | 1 | 414 |
| Render_Present | `16` | 1 | 415 |
| Render_Present | `64` | 1 | 420 |
| Render_Present | `32` | 1 | 421 |
| Render_Present | `4` | 1 | 437 |
| Render_Pump | `8` | 1 | 464 |
| Render_Pump | `12` | 1 | 471 |
| Render_Pump | `16` | 1 | 472 |
| Render_Pump | `4` | 1 | 474 |
| RenderState_DrawCursorSpriteToPrimarySurface | `64` | 1 | 498 |
| Device_GetParamA | `280` | 1 | 513 |
| Device_GetParamB | `44` | 1 | 555 |
| Device_GetParamB | `1108` | 2 | 556, 557 |
| Device_GetParamB | `36` | 2 | 556, 562 |
| Device_GetParamB | `40` | 2 | 557, 563 |
| Device_GetParamB | `2` | 3 | 564, 567, 568 |
| Device_GetParamB | `4` | 1 | 570 |
| Device_UpdateRect | `8` | 7 | 624, 628, 629, 629 ... |
| Device_UpdateRect | `9` | 2 | 626, 643 |
| Device_UpdateRect | `31` | 4 | 628, 629, 632, 633 |
| Device_UpdateRect | `10` | 2 | 634, 644 |
| Device_UpdateRect | `11` | 1 | 647 |
| Device_UpdateRect | `0x10` | 1 | 648 |
| Device_UpdateRect | `12` | 1 | 648 |
| Device_UpdateRect | `2` | 2 | 651, 652 |
| Device_UpdateRect | `4` | 1 | 655 |

### src/units/0040F510_00411560_units_001.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Unit_Create | `0xFFFF` | 1 | 54 |
| Unit_Create | `2` | 1 | 54 |
| Camera_CenterOnUnit | `4` | 1 | 338 |
| Camera_CenterOnUnit | `3` | 1 | 339 |
| Camera_CenterOnUnit | `9` | 2 | 345, 346 |
| Camera_CenterOnUnit | `7` | 2 | 348, 349 |
| UnitSlot_CalcActionPointsFromFatigue | `80` | 1 | 367 |
| UnitSlot_CalcActionPointsFromFatigue | `89` | 1 | 367 |
| UnitSlot_CalcActionPointsFromFatigue | `192` | 3 | 368, 368, 368 |
| UnitSlot_CalcActionPointsFromFatigue | `31` | 4 | 368, 368, 370, 370 |
| UnitSlot_CalcActionPointsFromFatigue | `8` | 6 | 368, 368, 368, 370 ... |
| UnitSlot_CalcActionPointsFromFatigue | `90` | 1 | 369 |
| UnitSlot_CalcActionPointsFromFatigue | `99` | 1 | 369 |
| UnitSlot_CalcActionPointsFromFatigue | `7` | 3 | 370, 370, 370 |
| UnitSlot_CalcActionPointsFromFatigue | `100` | 1 | 371 |
| UnitStack_ClearRemainingActionPoints | `3` | 1 | 417 |
| UnitStack_ClearRemainingActionPoints | `23` | 1 | 424 |
| WorldMap_HandleViewportScrollKeys | `203` | 1 | 440 |
| WorldMap_HandleViewportScrollKeys | `205` | 1 | 452 |
| WorldMap_HandleViewportScrollKeys | `9` | 1 | 452 |
| WorldMap_HandleViewportScrollKeys | `200` | 1 | 459 |
| WorldMap_HandleViewportScrollKeys | `208` | 1 | 468 |
| WorldMap_HandleViewportScrollKeys | `7` | 1 | 471 |
| UnitStack_GetMinCurrentActionPoints | `37` | 1 | 491 |
| UnitStack_GetMinCurrentActionPoints | `23` | 1 | 493 |
| UnitStack_GetMinCurrentActionPoints | `8` | 2 | 498, 499 |
| UnitStack_GetMaxOrderTier | `3` | 3 | 515, 522, 523 |
| UnitStack_GetMaxOrderTier | `18` | 2 | 522, 523 |
| UnitStack_HasPlagueFlag | `6` | 1 | 537 |
| UnitStack_HasPlagueFlag | `19` | 1 | 539 |
| UnitStack_SpendActionPointsClamped | `3` | 1 | 557 |
| UnitStack_SpendActionPointsClamped | `8` | 3 | 563, 564, 565 |
| UnitStack_SpendActionPointsClamped | `23` | 1 | 568 |
| UnitStack_SpendActionPointsUnchecked | `6` | 1 | 579 |
| UnitStack_SubtractActionPointsFloorZero | `3` | 1 | 599 |
| UnitStack_SubtractActionPointsFloorZero | `8` | 3 | 605, 608, 613 |
| UnitStack_CanReachQueuedPathTileWithFogOverlay | `100` | 1 | 632 |
| UnitStack_CanReachQueuedPathTileWithFogOverlay | `4` | 1 | 642 |
| UnitStack_ExecuteQueuedPath | `100` | 2 | 743, 922 |
| UnitStack_ExecuteQueuedPath | `79` | 5 | 772, 917, 1133, 1155 ... |
| UnitStack_ExecuteQueuedPath | `158` | 3 | 773, 853, 1154 |
| UnitStack_ExecuteQueuedPath | `9` | 3 | 803, 809, 883 |
| UnitStack_ExecuteQueuedPath | `7` | 7 | 807, 812, 885, 986 ... |
| UnitStack_ExecuteQueuedPath | `147159` | 3 | 826, 941, 1107 |
| UnitStack_ExecuteQueuedPath | `4` | 10 | 828, 868, 868, 898 ... |
| UnitStack_ExecuteQueuedPath | `6` | 7 | 829, 937, 950, 951 ... |
| UnitStack_ExecuteQueuedPath | `4112` | 1 | 830 |
| UnitStack_ExecuteQueuedPath | `720` | 1 | 844 |
| UnitStack_ExecuteQueuedPath | `0x64` | 2 | 867, 894 |
| UnitStack_ExecuteQueuedPath | `16` | 2 | 869, 898 |
| UnitStack_ExecuteQueuedPath | `200` | 2 | 891, 1061 |
| UnitStack_ExecuteQueuedPath | `2` | 8 | 892, 937, 1014, 1018 ... |
| UnitStack_ExecuteQueuedPath | `140051` | 1 | 915 |
| UnitStack_ExecuteQueuedPath | `5` | 8 | 934, 935, 1014, 1020 ... |
| UnitStack_ExecuteQueuedPath | `147176` | 2 | 951, 1149 |
| UnitStack_ExecuteQueuedPath | `3` | 7 | 978, 987, 1014, 1018 ... |
| UnitStack_ExecuteQueuedPath | `64` | 2 | 1051, 1057 |
| UnitStack_ExecuteQueuedPath | `0x1F4` | 3 | 1071, 1077, 1122 |
| UnitStack_ExecuteQueuedPath | `0x28` | 3 | 1074, 1077, 1122 |
| UnitStack_ExecuteQueuedPath | `147180` | 2 | 1074, 1077 |
| UnitStack_ExecuteQueuedPath | `10` | 1 | 1112 |
| UnitStack_ExecuteQueuedPath | `509676` | 1 | 1131 |
| UnitStack_ExecuteQueuedPath | `147490` | 1 | 1142 |
| UnitStats_CalcEffectiveMeleeAttack | `3` | 1 | 1246 |
| UnitStats_CalcEffectiveMeleeAttack | `100` | 1 | 1249 |
| UnitStats_CalcEffectiveMeleeAttack | `11` | 1 | 1249 |
| UnitStats_CalcEffectiveMeleeAttack | `5` | 1 | 1249 |
| UnitStats_CalcEffectiveMeleeAttack | `9` | 1 | 1249 |
| UnitStats_GetMeleeIconIndex | `0x03` | 1 | 1256 |
| UnitStats_GetMeleeIconIndex | `5` | 1 | 1256 |
| UnitStats_CalcEffectiveDefensePower | `22` | 1 | 1266 |
| UnitStats_CalcEffectiveDefensePower | `31` | 2 | 1267, 1267 |
| UnitStats_CalcEffectiveDefensePower | `320` | 3 | 1267, 1267, 1267 |
| UnitStats_CalcEffectiveDefensePower | `8` | 3 | 1267, 1267, 1267 |
| UnitStats_CalcEffectiveDefensePower | `3` | 1 | 1269 |
| UnitStats_CalcEffectiveDefensePower | `100` | 1 | 1272 |
| UnitStats_CalcEffectiveDefensePower | `11` | 1 | 1272 |
| UnitStats_CalcEffectiveDefensePower | `5` | 1 | 1272 |
| UnitStats_CalcEffectiveDefensePower | `9` | 1 | 1272 |
| UnitStats_GetDefenseIconIndex | `0x03` | 1 | 1279 |
| UnitStats_GetDefenseIconIndex | `5` | 1 | 1279 |
| UnitStats_CalcEffectiveShotPower | `10` | 1 | 1285 |
| UnitStats_CalcEffectiveShotPower | `100` | 1 | 1285 |
| UnitStats_CalcEffectiveShotPower | `11` | 1 | 1285 |
| UnitStats_CalcEffectiveShotPower | `9` | 1 | 1285 |
| UnitStats_GetBaseShotPower | `10` | 1 | 1291 |
| UnitStats_GetBaseShotPower | `11` | 1 | 1291 |
| UnitStats_CalcEffectiveWallAttack | `3` | 1 | 1300 |
| UnitStats_CalcEffectiveWallAttack | `100` | 1 | 1303 |
| UnitStats_CalcEffectiveWallAttack | `11` | 1 | 1303 |
| UnitStats_CalcEffectiveWallAttack | `5` | 1 | 1303 |
| UnitStats_CalcEffectiveWallAttack | `9` | 1 | 1303 |
| LogAllUnits | `6` | 1 | 1353 |
| UnitSlots_RemoveGaps | `0x1Fu` | 1 | 1430 |

### src/units/004115E0_00412BE0_units_002.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Unit_CheckLowMorale | `3` | 2 | 28, 75 |
| Unit_CheckLowMorale | `7` | 1 | 29 |
| Unit_CheckLowMorale | `100` | 2 | 45, 48 |
| Unit_CheckLowMorale | `200` | 1 | 45 |
| Unit_CheckLowMorale | `0x32` | 2 | 46, 48 |
| Unit_CheckLowMorale | `140051` | 1 | 68 |
| Unit_CheckLowMorale | `5` | 1 | 71 |
| Unit_CheckLowMorale | `2` | 3 | 74, 74, 77 |
| Unit_CheckLowMorale | `0x2D4u` | 1 | 84 |
| Unit_CheckLowMorale | `724` | 2 | 85, 85 |
| UnitStack_ApplyPlagueAttritionToPeasantCargo | `15` | 1 | 125 |
| UnitStack_ApplyPlagueAttritionToPeasantCargo | `25` | 1 | 125 |
| UnitSlot_ShouldGainFatigueFromLowActionPoints | `3u` | 1 | 155 |
| UnitSlot_HasSevereFatigue | `80` | 1 | 169 |
| Unit_NewTurn | `147178` | 1 | 191 |
| Unit_NewTurn | `147180` | 1 | 191 |
| Unit_NewTurn | `2` | 13 | 198, 205, 216, 223 ... |
| Unit_NewTurn | `0xFFFFFFFF` | 8 | 200, 209, 210, 248 ... |
| Unit_NewTurn | `20` | 1 | 200 |
| Unit_NewTurn | `140051` | 1 | 207 |
| Unit_NewTurn | `4` | 3 | 207, 286, 286 |
| Unit_NewTurn | `10` | 1 | 209 |
| Unit_NewTurn | `6` | 3 | 229, 234, 238 |
| Unit_NewTurn | `17` | 1 | 239 |
| Unit_NewTurn | `320` | 2 | 278, 279 |
| Unit_NewTurn | `0x64` | 1 | 282 |
| Unit_NewTurn | `16` | 1 | 287 |
| Unit_NewTurn | `509676` | 1 | 288 |
| UnitStack_HasBuilder | `6` | 1 | 340 |
| Map_RedrawUnitFootprintByIndex | `3` | 1 | 372 |
| Map_RedrawUnitFootprintByIndex | `0x1Bu` | 2 | 376, 378 |
| Map_RedrawUnitFootprintByIndex | `0x1E` | 1 | 380 |
| Map_RedrawUnitFootprintByIndex | `5` | 1 | 390 |
| Map_UpdateIdleAnimatedUnits | `6` | 1 | 475 |
| Map_UpdateIdleAnimatedUnits | `24` | 2 | 481, 485 |
| Map_UpdateIdleAnimatedUnits | `23` | 6 | 486, 487, 488, 490 ... |
| Map_UpdateIdleAnimatedUnits | `7` | 2 | 486, 486 |
| Map_UpdateIdleAnimatedUnits | `0xF8` | 2 | 487, 491 |
| Unit_GetSpriteVerticalOffsetPx | `147180` | 1 | 509 |
| Unit_AttemptNeighborMove | `3` | 1 | 529 |
| Unit_AttemptNeighborMove | `16` | 1 | 532 |
| Unit_AttemptNeighborMove | `2` | 4 | 534, 542, 544, 554 |
| UnitStack_CanExecuteQueuedPathNow | `4` | 2 | 577, 577 |
| UnitSlots_ExtractSpecialEntries | `0x1Fu` | 2 | 608, 615 |
| UnitStack_HasGoldCargo | `6` | 1 | 726 |
| UnitStack_HasPeasantCargo | `6` | 1 | 748 |
| UnitStack_NormalizePeasantCargo | `3` | 4 | 782, 802, 807, 808 |
| UnitStack_NormalizePeasantCargo | `9` | 1 | 793 |
| UnitStack_NormalizePeasantCargo | `100` | 4 | 816, 825, 830, 833 |
| UnitStack_NormalizePeasantCargo | `17` | 2 | 818, 837 |
| UnitStack_NormalizePeasantCargo | `25` | 1 | 824 |
| UnitStack_NormalizePeasantCargo | `16` | 2 | 825, 835 |
| UnitStack_NormalizePeasantCargo | `15` | 2 | 826, 833 |
| UnitStack_NormalizePeasantCargo | `10` | 2 | 827, 837 |
| UnitStack_NormalizePeasantCargo | `14` | 2 | 827, 831 |
| UnitStack_NormalizePeasantCargo | `6` | 2 | 832, 838 |
| UnitStack_CaptureDefeatedStack | `2` | 4 | 888, 889, 913, 966 |
| UnitStack_CaptureDefeatedStack | `3` | 3 | 892, 898, 924 |
| UnitStack_CaptureDefeatedStack | `13` | 1 | 988 |
| Unit_CreateNearbyUnitGroup | `7` | 1 | 1034 |
| Unit_CreateNearbyUnitGroup | `2` | 5 | 1035, 1041, 1050, 1051 ... |
| Unit_CreateNearbyUnitGroup | `16` | 1 | 1044 |
| Unit_CreateNearbyUnitGroup | `6` | 2 | 1062, 1066 |
| Unit_CreateNearbyUnitGroup | `9` | 1 | 1063 |
| UnitSlot_AdjustFatigueByPredicate | `100` | 2 | 1110, 1111 |
| UnitStack_AdjustFatigueByPredicate | `100` | 2 | 1161, 1162 |
| UnitSlot_AdjustMoraleByPredicate | `20` | 2 | 1197, 1198 |
| UnitStack_AdjustMoraleByPredicate | `20` | 2 | 1241, 1242 |
| UnitSlot_CycleOrderState | `2` | 1 | 1262 |
| UnitSlot_CycleOrderState | `3` | 4 | 1262, 1270, 1273, 1273 |
| UnitSlot_CycleOrderState | `0xF3` | 2 | 1263, 1269 |
| UnitSlot_CycleOrderState | `4` | 2 | 1265, 1273 |
| UnitSlot_CycleOrderState | `16` | 1 | 1267 |
| UnitSlot_CycleOrderState | `2u` | 1 | 1267 |
| UnitSlot_CycleOrderState | `6` | 1 | 1267 |
| UnitSlot_CycleOrderState | `3u` | 1 | 1270 |
| UnitSlot_CycleOrderState | `0xF0` | 2 | 1272, 1273 |
| UnitStackSelection_BuildSelectedSlotIndexList | `4` | 1 | 1406 |
| UnitStack_CalcMilitaryStrength | `6` | 1 | 1471 |

### src/units/00412C00_00414350_units_003.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| Player_CalcMilitaryStrength | `4` | 2 | 50, 50 |
| Player_CalcMilitaryStrength | `16` | 1 | 51 |
| Player_CalcMilitaryStrength | `509676` | 1 | 52 |
| Player_CalcMilitaryStrength | `100` | 1 | 57 |
| Player_CalcMilitaryStrength | `147178` | 1 | 65 |
| Player_CalcMilitaryStrength | `147180` | 1 | 65 |
| UnitStack_CopyFromTemplate | `2` | 2 | 95, 95 |
| UnitStack_CopyFromTemplate | `310` | 1 | 98 |
| UnitStack_CopyFromTemplate | `400` | 1 | 100 |
| UnitStack_CopyFromTemplate | `720` | 1 | 100 |
| UnitStack_CopyFromTemplate | `320` | 1 | 101 |
| UnitStack_CopyFromTemplate | `721` | 2 | 102, 102 |
| BattleUnitEntry_CopyMergingPackedFlags | `3` | 3 | 129, 129, 137 |
| BattleUnitEntry_CopyMergingPackedFlags | `4` | 3 | 130, 130, 158 |
| BattleUnitEntry_CopyMergingPackedFlags | `6` | 2 | 131, 131 |
| BattleUnitEntry_CopyMergingPackedFlags | `0xFC` | 1 | 136 |
| BattleUnitEntry_CopyMergingPackedFlags | `0xC` | 1 | 141 |
| BattleUnitEntry_CopyMergingPackedFlags | `0xF3` | 2 | 142, 143 |
| BattleUnitEntry_CopyMergingPackedFlags | `0x70` | 1 | 145 |
| BattleUnitEntry_CopyMergingPackedFlags | `0x8F` | 2 | 146, 147 |
| BattleUnitEntry_CopyMergingPackedFlags | `13` | 8 | 150, 152, 153, 155 ... |
| BattleUnitEntry_CopyMergingPackedFlags | `0xFE` | 2 | 151, 167 |
| BattleUnitEntry_CopyMergingPackedFlags | `2u` | 1 | 154 |
| BattleUnitEntry_CopyMergingPackedFlags | `2` | 1 | 155 |
| BattleUnitEntry_CopyMergingPackedFlags | `4u` | 1 | 157 |
| BattleUnitEntry_CopyMergingPackedFlags | `8u` | 1 | 160 |
| BattleUnitEntry_CopyMergingPackedFlags | `8` | 1 | 161 |
| BattleUnitEntry_CopyMergingPackedFlags | `17` | 4 | 162, 163, 164, 165 |
| BattleUnitEntry_CopyMergingPackedFlags | `7` | 1 | 162 |
| BattleUnitEntry_CopyMergingPackedFlags | `0xF8` | 1 | 163 |
| BattleUnitEntry_CopyMergingPackedFlags | `23` | 2 | 171, 171 |
| BattleUnitEntry_CopyMergingPackedFlags | `27` | 2 | 172, 172 |
| UnitTrackElementStack_CopyFromTemplate | `4` | 1 | 180 |
| UnitTrackElement_CopyFromTemplate | `2` | 2 | 189, 189 |
| UnitSpriteCache_GetOrLoadEntry | `100` | 1 | 218 |
| UnitSpriteCache_GetOrLoadEntry | `0xFFFFFFFFu` | 1 | 230 |
| UnitSpriteCache_GetOrLoadEntry | `11` | 3 | 235, 237, 254 |
| UnitSpriteCache_GetOrLoadEntry | `7` | 3 | 243, 246, 260 |
| UnitSpriteCache_GetOrLoadEntry | `4` | 1 | 251 |
| UnitSpriteCache_GetOrLoadEntry | `5` | 1 | 252 |
| UnitSpriteCache_GetOrLoadEntry | `6` | 1 | 253 |
| UnitSpriteCache_GetOrLoadEntry | `22` | 1 | 257 |
| UnitSpriteCache_GetOrLoadEntry | `8` | 1 | 259 |
| UnitSpriteCache_FindEntryOrLoad | `4` | 1 | 288 |
| UnitSpriteCache_FindEntryOrLoad | `5` | 1 | 289 |
| UnitSpriteCache_FindEntryOrLoad | `6` | 1 | 290 |
| UnitSpriteCache_FindEntryOrLoad | `11` | 1 | 292 |
| UnitSpriteCache_FindEntryOrLoad | `7` | 1 | 293 |
| UnitSpriteCache_FreeAllEntries | `7` | 2 | 314, 319 |
| UnitSpriteCache_CountActiveEntries | `15` | 1 | 336 |
| UnitSpriteCache_CountActiveEntries | `1500` | 1 | 336 |
| Unit_BuildGoSpriteFilePath | `20` | 1 | 370 |
| Unit_BuildGoSpriteFilePath | `49` | 1 | 374 |
| Unit_BuildGoSpriteFilePath | `2` | 8 | 383, 385, 397, 399 ... |
| UI_BeginUnitInfo | `20` | 1 | 456 |
| UI_BeginUnitInfo | `49` | 1 | 460 |
| UI_BeginUnitInfo | `2` | 10 | 469, 471, 483, 485 ... |
| Unit_BuildGarrisonSlotIconSpritePath | `12` | 1 | 556 |
| Unit_BuildGarrisonSlotIconSpritePath | `2` | 10 | 570, 572, 584, 586 ... |
| Unit_BuildSelectedUnitPanelIconSpritePath | `12` | 1 | 657 |
| Unit_BuildSelectedUnitPanelIconSpritePath | `2` | 10 | 671, 673, 685, 687 ... |
| Unit_BuildSelectedUnitPanelIconPalettePath | `12` | 1 | 758 |
| Unit_BuildSelectedUnitPanelIconPalettePath | `2` | 10 | 772, 774, 786, 788 ... |
| Unit_BuildAttackAnimSpritePath | `20` | 1 | 859 |
| Unit_BuildAttackAnimSpritePath | `49` | 1 | 863 |
| Unit_BuildAttackAnimSpritePath | `2` | 10 | 872, 874, 886, 888 ... |
| Unit_BuildShotAnimSpritePath | `20` | 1 | 959 |
| Unit_BuildShotAnimSpritePath | `49` | 1 | 963 |
| Unit_BuildShotAnimSpritePath | `2` | 10 | 972, 974, 986, 988 ... |
| Unit_BuildShotAnimPaletteSpritePath | `2` | 8 | 1065, 1067, 1079, 1081 ... |
| Unit_BuildBigInfoGraphicPath | `7` | 1 | 1135 |
| Unit_BuildBigInfoGraphicPath | `5` | 1 | 1137 |
| Unit_BuildBigInfoGraphicPath | `2` | 10 | 1140, 1140, 1150, 1152 ... |
| UnitStack_BuildMergedTerrainMoveProfile | `4` | 1 | 1217 |
| UnitStack_BuildMergedTerrainMoveProfile | `29` | 3 | 1218, 1228, 1230 |
| UnitStack_BuildMergedTerrainMoveProfile | `9` | 1 | 1218 |
| UnitStack_BuildMergedTerrainMoveProfile | `6` | 1 | 1227 |
| UnitStack_BuildMergedTerrainMoveProfile | `37` | 1 | 1228 |
| UnitStack_BuildMergedTerrainMoveProfile | `30` | 1 | 1232 |
| Map_InitTerrainMoveTableOffsets | `3` | 1 | 1257 |
| Map_InitTerrainMoveTableOffsets | `4` | 1 | 1259 |
| Map_InitTerrainMoveTableOffsets | `6` | 1 | 1259 |
| Map_InitTerrainMoveTableOffsets | `7` | 1 | 1261 |
| Map_InitTerrainMoveTableOffsets | `15` | 1 | 1262 |
| Map_InitTerrainMoveTableOffsets | `8` | 1 | 1262 |
| Map_InitTerrainMoveTableOffsets | `16` | 1 | 1264 |
| Map_InitTerrainMoveTableOffsets | `19` | 1 | 1264 |
| Map_InitTerrainMoveTableOffsets | `20` | 1 | 1266 |
| Map_InitTerrainMoveTableOffsets | `31` | 1 | 1266 |
| Map_InitTerrainMoveTableOffsets | `32` | 1 | 1268 |
| Map_InitTerrainMoveTableOffsets | `44` | 1 | 1268 |
| Map_InitTerrainMoveTableOffsets | `160` | 1 | 1270 |
| Map_InitTerrainMoveTableOffsets | `45` | 1 | 1270 |
| Map_InitTerrainMoveTableOffsets | `161` | 1 | 1272 |
| Map_InitTerrainMoveTableOffsets | `185` | 1 | 1272 |
| Map_InitTerrainMoveTableOffsets | `186` | 1 | 1274 |
| Map_InitTerrainMoveTableOffsets | `221` | 1 | 1274 |
| Map_InitTerrainMoveTableOffsets | `222` | 1 | 1276 |
| Map_InitTerrainMoveTableOffsets | `706` | 1 | 1276 |
| Map_InitTerrainMoveTableOffsets | `707` | 1 | 1278 |
| Map_InitTerrainMoveTableOffsets | `710` | 1 | 1278 |
| Map_InitTerrainMoveTableOffsets | `711` | 1 | 1280 |
| Map_InitTerrainMoveTableOffsets | `714` | 1 | 1280 |
| Map_InitTerrainMoveTableOffsets | `715` | 1 | 1282 |
| Map_InitTerrainMoveTableOffsets | `745` | 1 | 1282 |
| Map_InitTerrainMoveTableOffsets | `746` | 1 | 1284 |
| Map_InitTerrainMoveTableOffsets | `750` | 1 | 1284 |
| Map_InitTerrainMoveTableOffsets | `751` | 1 | 1286 |
| Map_InitTerrainMoveTableOffsets | `753` | 1 | 1286 |
| Map_InitTerrainMoveTableOffsets | `754` | 1 | 1288 |
| Map_InitTerrainMoveTableOffsets | `756` | 1 | 1288 |
| Map_InitTerrainMoveTableOffsets | `757` | 1 | 1290 |
| Map_InitTerrainMoveTableOffsets | `770` | 1 | 1290 |
| Map_InitTerrainMoveTableOffsets | `1024` | 2 | 1292, 1294 |
| Map_InitTerrainMoveTableOffsets | `771` | 1 | 1292 |
| Map_GetUnitTileMoveCostOrZero | `2` | 2 | 1307, 1320 |
| Map_GetUnitTileMoveCostOrZero | `0xFFFF` | 2 | 1308, 1320 |
| Map_GetUnitTileMoveCostOrZero | `0x8000` | 1 | 1310 |
| Map_GetUnitTileMoveCostOrZero | `147178` | 1 | 1313 |
| Map_GetUnitTileMoveCostOrZero | `147894` | 1 | 1313 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `0xFFFF` | 3 | 1343, 1354, 1369 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `0x7FFF` | 1 | 1345 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `720` | 2 | 1346, 1359 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `4` | 4 | 1347, 1360, 1363, 1363 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `0x8000` | 1 | 1356 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `2` | 1 | 1369 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `29` | 1 | 1370 |
| UnitStack_GetTileMoveCostFromMergedProfileOrZero | `30` | 2 | 1372, 1375 |
| UnitStack_GetTileMoveCostOrZero | `96` | 1 | 1391 |
| UnitStack_GetTileMoveCostOrZero | `0xFFFF` | 3 | 1397, 1409, 1424 |
| UnitStack_GetTileMoveCostOrZero | `0x7FFF` | 2 | 1399, 1411 |
| UnitStack_GetTileMoveCostOrZero | `720` | 2 | 1400, 1414 |
| UnitStack_GetTileMoveCostOrZero | `4` | 4 | 1401, 1415, 1418, 1418 |
| UnitStack_GetTileMoveCostOrZero | `2` | 1 | 1424 |
| UnitStack_GetTileMoveCostOrZero | `29` | 1 | 1425 |
| UnitStack_GetTileMoveCostOrZero | `30` | 2 | 1427, 1430 |

### src/units/00414390_00416750_units_004.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UnitStack_GetMoveCostToTileIgnoringOccupancy | `2` | 2 | 23, 27 |
| Path_InsertBridgeCornerWaypoints | `101` | 1 | 37 |
| Path_InsertBridgeCornerWaypoints | `100` | 8 | 59, 65, 93, 95 ... |
| Path_InsertBridgeCornerWaypoints | `0xFFFF` | 6 | 86, 87, 88, 89 ... |
| Path_InsertBridgeCornerWaypoints | `2` | 10 | 86, 87, 88, 89 ... |
| Unit_MoveTrack | `2` | 17 | 264, 265, 295, 297 ... |
| Unit_MoveTrack | `200` | 12 | 265, 302, 325, 326 ... |
| Unit_MoveTrack | `556374` | 2 | 266, 267 |
| Unit_MoveTrack | `0x4E20` | 1 | 272 |
| Unit_MoveTrack | `4` | 9 | 272, 278, 365, 366 ... |
| Unit_MoveTrack | `0x10000` | 1 | 278 |
| Unit_MoveTrack | `256` | 1 | 301 |
| Unit_MoveTrack | `25` | 1 | 327 |
| Unit_MoveTrack | `0xFFFF` | 1 | 351 |
| Unit_MoveTrack | `65534` | 3 | 351, 399, 421 |
| Unit_MoveTrack | `16` | 3 | 354, 366, 464 |
| Unit_MoveTrack | `8` | 2 | 360, 460 |
| Unit_MoveTrack | `23` | 6 | 364, 365, 366, 462 ... |
| Unit_MoveTrack | `31` | 4 | 365, 366, 463, 464 |
| Unit_MoveTrack | `100` | 3 | 436, 488, 493 |
| Unit_MoveTrack | `3` | 1 | 537 |
| Unit_MoveTrackNearTile | `100` | 2 | 678, 693 |
| Building_GenerateApproachTrack | `4` | 10 | 734, 748, 749, 752 ... |
| Building_GenerateApproachTrack | `2` | 5 | 738, 750, 793, 824 ... |
| Building_GenerateApproachTrack | `872` | 4 | 749, 752, 753, 754 |
| Building_GenerateApproachTrack | `100` | 2 | 774, 810 |
| Building_GenerateNearApproachTrack | `509678` | 1 | 882 |
| Building_GenerateNearApproachTrack | `509675` | 1 | 883 |
| Building_GenerateNearApproachTrack | `2` | 10 | 887, 890, 891, 892 ... |
| Building_GenerateNearApproachTrack | `200` | 4 | 889, 892, 979, 982 |
| Building_GenerateNearApproachTrack | `556376` | 4 | 891, 892, 981, 982 |
| Building_GenerateNearApproachTrack | `100` | 2 | 933, 968 |
| QueuedPath_StartsInBuildingFootprint | `4` | 1 | 1042 |
| Math_SinDegreesQ16 | `360` | 4 | 1065, 1066, 1071, 1072 |
| Rng_RandRange | `0x34523471u` | 1 | 1097 |
| Rng_RandRange | `0x83356532u` | 1 | 1098 |
| Math_CeilSqrt | `4` | 1 | 1114 |
| Math_CeilSqrt | `2` | 2 | 1116, 1122 |
| Math_CeilSqrt | `20` | 1 | 1116 |
| WorldMap_DrawUnitStackOverlayGlyph | `0x2D` | 1 | 1141 |
| WorldMap_DrawUnitStackOverlayGlyph | `0x58u` | 1 | 1141 |
| WorldMap_DrawUnitStackOverlayGlyph | `2` | 1 | 1143 |
| WorldMap_DrawUnitStackOverlayGlyph | `0xFFFF` | 1 | 1144 |
| WorldMap_DrawUnitStackOverlayGlyph | `45` | 1 | 1147 |
| WorldMap_DrawUnitStackWithOverlays | `0x8000` | 1 | 1179 |
| WorldMap_DrawUnitStackWithOverlays | `147180` | 4 | 1182, 1187, 1190, 1226 |
| WorldMap_DrawUnitStackWithOverlays | `147178` | 2 | 1184, 1191 |
| WorldMap_DrawUnitStackWithOverlays | `147894` | 3 | 1184, 1217, 1239 |
| WorldMap_DrawUnitStackWithOverlays | `147197` | 1 | 1192 |
| WorldMap_DrawUnitStackWithOverlays | `7` | 1 | 1192 |
| WorldMap_DrawUnitStackWithOverlays | `147179` | 2 | 1193, 1195 |
| WorldMap_DrawUnitStackWithOverlays | `8` | 1 | 1195 |
| WorldMap_DrawUnitStackWithOverlays | `63` | 4 | 1197, 1201, 1203, 1219 |
| WorldMap_DrawUnitStackWithOverlays | `30` | 2 | 1202, 1237 |
| WorldMap_DrawUnitStackWithOverlays | `126` | 3 | 1211, 1211, 1211 |
| WorldMap_DrawUnitStackWithOverlays | `128` | 2 | 1211, 1219 |
| WorldMap_DrawUnitStackWithOverlays | `16` | 3 | 1211, 1211, 1211 |
| WorldMap_DrawUnitStackWithOverlays | `31` | 2 | 1211, 1211 |
| WorldMap_DrawUnitStackWithOverlays | `5` | 2 | 1231, 1242 |
| WorldMap_DrawUnitStackWithOverlays | `12` | 1 | 1232 |
| WorldMap_DrawUnitStackWithOverlays | `48` | 2 | 1232, 1237 |
| WorldMap_DrawUnitStackWithOverlays | `33` | 1 | 1236 |
| WorldMap_DrawUnitStackWithOverlays | `39` | 1 | 1241 |
| WorldMap_DrawUnitStackWithOverlays | `10` | 1 | 1242 |
| WorldMap_DrawUnitStackWithOverlays | `147155` | 1 | 1250 |
| WorldMap_DrawUnitStackWithOverlays | `3` | 1 | 1252 |
| WorldMap_DrawUnitStackWithOverlays | `76` | 1 | 1252 |
| WorldMap_DrawUnitStackWithOverlays | `20` | 1 | 1253 |
| WorldMap_DrawUnitStackWithOverlays | `25` | 1 | 1253 |
| Map_InitBuildingSwayJitterOffsets | `20` | 4 | 1289, 1289, 1291, 1291 |
| Map_InitBuildingSwayJitterOffsets | `2` | 1 | 1290 |
| Map_InitBuildingSwayJitterOffsets | `30` | 1 | 1294 |
| Map_UpdateConstructionSiteSwayAnimation | `20` | 2 | 1312, 1317 |
| Map_UpdateConstructionSiteSwayAnimation | `2` | 1 | 1315 |
| Map_UpdateConstructionSiteSwayAnimation | `30` | 1 | 1315 |
| Map_UpdateConstructionSiteSwayAnimation | `0x11` | 1 | 1317 |
| Map_UpdateConstructionSiteSwayAnimation | `10` | 8 | 1319, 1319, 1321, 1321 ... |
| Map_UpdateConstructionSiteSwayAnimation | `5` | 4 | 1319, 1321, 1335, 1337 |
| Map_UpdateConstructionSiteSwayAnimation | `16` | 1 | 1357 |
| Map_UpdateConstructionSiteSwayAnimation | `4` | 1 | 1359 |
| Map_UpdateIdleAnimatedBuildings | `10` | 1 | 1386 |
| Map_UpdateIdleAnimatedBuildings | `0xF` | 1 | 1389 |
| Map_UpdateIdleAnimatedBuildings | `16` | 1 | 1394 |
| Map_UpdateIdleAnimatedBuildings | `4` | 2 | 1394, 1396 |
| Map_UpdateIdleAnimatedBuildings | `2u` | 1 | 1399 |
| WorldMap_DrawUnitAttentionFlashGlow | `2` | 3 | 1437, 1440, 1449 |
| WorldMap_DrawUnitAttentionFlashGlow | `64` | 1 | 1439 |
| WorldMap_DrawUnitAttentionFlashGlow | `3` | 2 | 1444, 1458 |
| WorldMap_DrawUnitAttentionFlashGlow | `30` | 1 | 1449 |
| WorldMap_DrawUnitAttentionFlashGlow | `52` | 1 | 1452 |
| WorldMap_DrawUnitAttentionFlashGlow | `50` | 1 | 1458 |
| WorldMap_DrawUnitAttentionFlashGlow | `36` | 1 | 1459 |
| WorldMap_DrawUnitAttentionFlashGlow | `63` | 2 | 1460, 1460 |

### src/units/00416850_00419120_units_005.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| WorldMap_DrawMapTile | `0x20` | 1 | 127 |
| WorldMap_DrawMapTile | `0x21` | 3 | 127, 127, 127 |
| WorldMap_DrawMapTile | `0x23` | 1 | 127 |
| WorldMap_DrawMapTile | `0x38` | 1 | 127 |
| WorldMap_DrawMapTile | `0x3C` | 1 | 127 |
| WorldMap_DrawMapTile | `0x3E` | 1 | 127 |
| WorldMap_DrawMapTile | `0x41` | 2 | 127, 127 |
| WorldMap_DrawMapTile | `10` | 1 | 127 |
| WorldMap_DrawMapTile | `100` | 2 | 129, 130 |
| WorldMap_DrawMapTile | `14` | 2 | 129, 130 |
| WorldMap_DrawMapTile | `63` | 7 | 131, 132, 135, 614 ... |
| WorldMap_DrawMapTile | `2` | 28 | 143, 176, 191, 191 ... |
| WorldMap_DrawMapTile | `0xFFFF` | 21 | 146, 152, 160, 170 ... |
| WorldMap_DrawMapTile | `0xCFu` | 4 | 160, 264, 280, 499 |
| WorldMap_DrawMapTile | `0xD2u` | 4 | 160, 264, 280, 499 |
| WorldMap_DrawMapTile | `187` | 4 | 163, 264, 280, 499 |
| WorldMap_DrawMapTile | `0xD3u` | 4 | 170, 259, 275, 493 |
| WorldMap_DrawMapTile | `0xD7u` | 4 | 170, 259, 275, 493 |
| WorldMap_DrawMapTile | `7` | 1 | 183 |
| WorldMap_DrawMapTile | `17` | 1 | 187 |
| WorldMap_DrawMapTile | `0x362u` | 1 | 191 |
| WorldMap_DrawMapTile | `0x36Cu` | 2 | 191, 206 |
| WorldMap_DrawMapTile | `5` | 3 | 196, 475, 483 |
| WorldMap_DrawMapTile | `0x364u` | 1 | 197 |
| WorldMap_DrawMapTile | `0x369u` | 1 | 197 |
| WorldMap_DrawMapTile | `866` | 2 | 197, 206 |
| WorldMap_DrawMapTile | `863` | 2 | 199, 238 |
| WorldMap_DrawMapTile | `99` | 2 | 202, 220 |
| WorldMap_DrawMapTile | `9` | 2 | 205, 604 |
| WorldMap_DrawMapTile | `0x367u` | 1 | 206 |
| WorldMap_DrawMapTile | `862` | 1 | 208 |
| WorldMap_DrawMapTile | `698` | 1 | 214 |
| WorldMap_DrawMapTile | `0x363u` | 1 | 215 |
| WorldMap_DrawMapTile | `0x365u` | 1 | 215 |
| WorldMap_DrawMapTile | `871` | 1 | 215 |
| WorldMap_DrawMapTile | `872` | 2 | 215, 224 |
| WorldMap_DrawMapTile | `874` | 1 | 215 |
| WorldMap_DrawMapTile | `875` | 2 | 215, 224 |
| WorldMap_DrawMapTile | `864` | 1 | 217 |
| WorldMap_DrawMapTile | `702` | 1 | 223 |
| WorldMap_DrawMapTile | `867` | 1 | 224 |
| WorldMap_DrawMapTile | `869` | 1 | 224 |
| WorldMap_DrawMapTile | `870` | 1 | 224 |
| WorldMap_DrawMapTile | `873` | 1 | 224 |
| WorldMap_DrawMapTile | `876` | 1 | 224 |
| WorldMap_DrawMapTile | `865` | 1 | 226 |
| WorldMap_DrawMapTile | `200` | 14 | 231, 232, 289, 304 ... |
| WorldMap_DrawMapTile | `556370` | 2 | 231, 232 |
| WorldMap_DrawMapTile | `0x8000u` | 2 | 232, 451 |
| WorldMap_DrawMapTile | `4` | 5 | 235, 466, 472, 479 ... |
| WorldMap_DrawMapTile | `8` | 2 | 236, 557 |
| WorldMap_DrawMapTile | `6` | 3 | 246, 477, 484 |
| WorldMap_DrawMapTile | `0x7FFFu` | 1 | 254 |
| WorldMap_DrawMapTile | `147180` | 1 | 255 |
| WorldMap_DrawMapTile | `556372` | 6 | 289, 304, 372, 402 ... |
| WorldMap_DrawMapTile | `64` | 13 | 297, 309, 321, 353 ... |
| WorldMap_DrawMapTile | `556376` | 6 | 316, 344, 360, 408 ... |
| WorldMap_DrawMapTile | `16` | 5 | 457, 466, 470, 478 ... |
| WorldMap_DrawMapTile | `509678` | 1 | 458 |
| WorldMap_DrawMapTile | `3` | 4 | 460, 476, 483, 607 |
| WorldMap_DrawMapTile | `509690` | 1 | 460 |
| WorldMap_DrawMapTile | `509674` | 1 | 463 |
| WorldMap_DrawMapTile | `509675` | 1 | 463 |
| WorldMap_DrawMapTile | `509676` | 1 | 464 |
| WorldMap_DrawMapTile | `509677` | 1 | 464 |
| WorldMap_DrawMapTile | `80` | 1 | 482 |
| WorldMap_DrawMapTile | `32` | 1 | 485 |
| WorldMap_DrawMapTile | `147176` | 1 | 551 |
| WorldMap_DrawMapTile | `65` | 1 | 564 |
| WorldMap_DrawMapTile | `12` | 1 | 580 |
| WorldMap_DrawMapTile | `11` | 1 | 588 |
| WorldMap_DrawMapTile | `147155` | 1 | 601 |
| WorldMap_DrawMapTile | `76` | 1 | 606 |
| WorldMap_DrawMapTile | `147151` | 1 | 611 |
| WorldMap_RedrawViewport | `16` | 5 | 670, 699, 716, 744 ... |
| WorldMap_RedrawViewport | `32` | 6 | 674, 694, 720, 756 ... |
| WorldMap_RedrawViewport | `64` | 3 | 684, 688, 704 |
| WorldMap_RedrawViewport | `9` | 1 | 686 |
| WorldMap_RedrawViewport | `6` | 3 | 690, 699, 706 |
| WorldMap_RedrawViewport | `12` | 1 | 713 |
| WorldMap_RedrawViewport | `0x20u` | 5 | 718, 724, 756, 757 ... |
| WorldMap_RedrawViewport | `33` | 1 | 726 |
| WorldMap_RedrawViewport | `0x25Fu` | 5 | 730, 736, 756, 769 ... |
| WorldMap_RedrawViewport | `607` | 2 | 732, 763 |
| WorldMap_RedrawViewport | `606` | 1 | 738 |
| WorldMap_RedrawViewport | `0x10u` | 2 | 742, 756 |
| WorldMap_RedrawViewport | `0x1CFu` | 2 | 748, 774 |
| WorldMap_RedrawViewport | `463` | 2 | 750, 773 |
| WorldMap_RedrawViewport | `36` | 2 | 754, 758 |
| WorldMap_RedrawViewport | `52` | 2 | 754, 758 |
| WorldMap_RedrawTileIfVisible | `9` | 1 | 798 |
| WorldMap_RedrawTileIfVisible | `7` | 1 | 799 |
| WorldMap_RedrawTileIfVisible | `6` | 5 | 804, 804, 805, 807 ... |
| WorldMap_RedrawTileIfVisible | `32` | 1 | 807 |
| WorldMap_RedrawTileIfVisible | `16` | 1 | 808 |
| WorldMap_RedrawTileIfVisible | `64` | 2 | 812, 812 |
| WorldMap_RedrawTileIfVisible | `63` | 2 | 813, 813 |
| UI_CenterWorldMapViewportOnRectIfFit | `7` | 2 | 833, 841 |
| UI_CenterWorldMapViewportOnRectIfFit | `9` | 2 | 833, 838 |
| UI_CenterWorldMapViewportOnRectIfFit | `2` | 2 | 835, 836 |
| UI_CenterWorldMapViewportOnRectIfFit | `3` | 2 | 835, 836 |
| UI_CenterWorldMapViewportOnRectIfFit | `10` | 1 | 839 |
| UI_CenterWorldMapViewportOnRectIfFit | `8` | 1 | 842 |
| UI_CenterWorldMapViewportOnTile | `3` | 2 | 859, 860 |
| UI_CenterWorldMapViewportOnTile | `9` | 1 | 862 |
| UI_CenterWorldMapViewportOnTile | `10` | 1 | 863 |
| UI_CenterWorldMapViewportOnTile | `7` | 1 | 865 |
| UI_CenterWorldMapViewportOnTile | `8` | 1 | 866 |
| UI_UpdateWorldMapUnitAttentionFlash | `147176` | 1 | 899 |
| UI_UpdateWorldMapUnitAttentionFlash | `0x708` | 1 | 900 |
| UI_UpdateWorldMapUnitAttentionFlash | `30` | 1 | 900 |
| UI_UpdateUnitBlinkFlash | `10` | 3 | 943, 945, 947 |
| UI_UpdateUnitBlinkFlash | `0xAu` | 2 | 946, 947 |
| UI_UpdateUnitBlinkFlash | `12` | 1 | 949 |
| UI_UpdateTileBlinkFlash | `10` | 3 | 982, 984, 986 |
| UI_UpdateTileBlinkFlash | `0xAu` | 2 | 985, 986 |
| UI_UpdateTileBlinkFlash | `8` | 1 | 988 |
| UI_HighlightTile | `8` | 4 | 1007, 1021, 1027, 1030 |
| UI_ClearTileHighlight | `0xFF` | 1 | 1037 |
| UI_DrawTileHighlightOverlay | `8` | 1 | 1058 |
| UI_DrawTileHighlightOverlay | `0x28u` | 2 | 1061, 1063 |
| UI_DrawTileHighlightOverlay | `2` | 2 | 1062, 1064 |
| UI_DrawTileHighlightOverlay | `64` | 2 | 1062, 1064 |
| UI_DrawTileHighlightOverlay | `40` | 1 | 1065 |
| UI_DrawTileHighlightOverlay | `63` | 2 | 1066, 1066 |
| UI_DrawTileHighlightOverlay | `80` | 1 | 1066 |
| Compat_CountPrintfArgs32 | `2` | 1 | 1159 |
| Compat_CountPrintfArgs32 | `3` | 1 | 1160 |

### src/units/004191F0_0041A690_units_006.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UI_DrawWidgetIcon | `4` | 2 | 42, 78 |
| UI_DrawWidgetIcon | `8` | 1 | 43 |
| UI_DrawWidgetIcon | `12` | 1 | 44 |
| UI_DrawWidgetIcon | `16` | 1 | 46 |
| UI_DrawWidgetIcon | `20` | 1 | 46 |
| UI_DrawWidgetIcon | `24` | 1 | 47 |
| UI_DrawWidgetIcon | `2` | 4 | 67, 73, 94, 100 |
| Compat_RenderDeviceDrawMenuSprite | `2` | 2 | 313, 393 |
| Compat_RenderDeviceDrawMenuSprite | `4` | 2 | 314, 398 |
| Compat_RenderDeviceDrawMenuSprite | `10` | 3 | 318, 322, 324 |
| Compat_RenderDeviceDrawMenuSprite | `14` | 1 | 321 |
| Compat_RenderDeviceDrawMenuSprite | `0x80u` | 1 | 351 |
| Compat_RenderDeviceDrawMenuSprite | `0x7F` | 1 | 353 |
| Compat_RenderDeviceDrawMenuSprite | `8` | 1 | 392 |
| Compat_RenderDeviceDrawMenuSprite | `16` | 1 | 393 |
| Compat_RenderDeviceDrawMenuSprite | `24` | 1 | 394 |
| Compat_RenderDeviceDrawMenuSprite | `3` | 1 | 394 |
| UI_DrawWidgetIconWithTransition | `4` | 8 | 466, 474, 475, 485 ... |
| UI_DrawWidgetIconWithTransition | `8` | 1 | 467 |
| UI_DrawWidgetIconWithTransition | `12` | 1 | 468 |
| UI_DrawWidgetIconWithTransition | `24` | 1 | 473 |
| UI_DrawWidgetIconWithTransition | `5` | 1 | 477 |
| UI_DrawWidgetIconWithTransition | `2` | 9 | 497, 499, 537, 537 ... |
| UI_DrawWidgetIconWithTransition | `6` | 4 | 511, 513, 570, 572 |
| UI_DrawWidgetIconWithTransition | `188` | 2 | 525, 532 |
| UI_DrawWidgetIconWithTransition | `255` | 1 | 553 |
| UI_DrawWidgetIconTransitionSlow | `20` | 1 | 596 |
| UI_DrawWidgetIconTransitionFast | `10` | 1 | 602 |
| UI_InvokeWidgetTransitionCallback | `28` | 1 | 609 |
| UI_InvokeWidgetActionCallback | `32` | 1 | 619 |
| Compat_WidgetSpriteSetHandle | `12` | 1 | 634 |
| UIWidget_ShowTextWithFadeTransition | `36` | 2 | 702, 746 |
| UIWidget_ShowTextWithFadeTransition | `4` | 2 | 702, 746 |
| UIWidget_ShowTextWithFadeTransition | `12` | 2 | 709, 710 |
| UIWidget_ShowTextWithFadeTransition | `16` | 1 | 711 |
| UIWidget_ShowTextWithFadeTransition | `639` | 3 | 714, 716, 718 |
| UIWidget_ShowTextWithFadeTransition | `479` | 4 | 721, 724, 725, 726 |
| UIWidget_ShowTextWithFadeTransition | `33` | 1 | 723 |
| UIWidget_ShowTextWithFadeTransition | `188` | 2 | 728, 735 |
| UIWidget_ShowTextWithFadeTransition | `30` | 3 | 748, 751, 759 |
| UIWidget_ShowTextWithFadeTransition | `0x1Eu` | 2 | 754, 767 |
| UIWidget_ShowTextWithFadeTransition | `255` | 2 | 754, 767 |
| UIWidget_ShowTextWithFadeTransition | `2` | 2 | 771, 773 |
| UIWidget_PollHitHoverAndClick | `2` | 5 | 824, 925, 942, 954 ... |
| UIWidget_PollHitHoverAndClick | `16` | 4 | 830, 861, 887, 894 |
| UIWidget_PollHitHoverAndClick | `20` | 7 | 830, 830, 861, 861 ... |
| UIWidget_PollHitHoverAndClick | `4` | 17 | 835, 837, 843, 865 ... |
| UIWidget_PollHitHoverAndClick | `8` | 9 | 844, 876, 900, 907 ... |
| UIWidget_PollHitHoverAndClick | `32` | 4 | 850, 927, 938, 949 |
| UIWidget_PollHitHoverAndClick | `36` | 3 | 903, 966, 967 |
| UIWidget_PollHitHoverAndClick | `48` | 3 | 904, 925, 966 |
| UIWidget_PollHitHoverAndClick | `4u` | 2 | 907, 969 |
| UIWidget_PollHitHoverAndClick | `24` | 1 | 909 |
| UIWidget_PollHitHoverAndClick | `3` | 3 | 953, 967, 973 |
| UIWidget_RefreshActionButtonState | `3` | 1 | 991 |
| UIWidget_RefreshActionButtonState | `640` | 1 | 997 |
| UIWidgetTable_InitDrawStates | `640` | 1 | 1016 |
| UIWidgetTable_PollHoverAndActions | `4` | 1 | 1051 |
| UIWidgetTable_PollHoverAndActions | `8` | 1 | 1051 |
| UIWidget_PlayPressedReleaseAnimationWithDelay | `49` | 2 | 1085, 1086 |
| UIWidget_PlayPressedReleaseAnimationWithDelay | `6` | 1 | 1087 |
| UIWidget_PlayPressedReleaseAnimationWithDelay | `8` | 2 | 1087, 1093 |
| UIWidget_PlayPressedReleaseAnimationWithDelay | `20` | 1 | 1089 |
| UIWidget_PlayPressedReleaseAnimationWithDelay | `5` | 1 | 1093 |
| UIWidget_PlayPressedReleaseAnimation | `49` | 2 | 1101, 1102 |
| UIWidget_PlayPressedReleaseAnimation | `6` | 1 | 1103 |
| UIWidget_PlayPressedReleaseAnimation | `8` | 2 | 1103, 1106 |
| UIWidget_PlayPressedReleaseAnimation | `5` | 1 | 1106 |
| UIWidget_ShowPressedState | `49` | 2 | 1114, 1115 |
| UIWidget_ShowPressedState | `6` | 1 | 1116 |
| UIWidget_ShowPressedState | `8` | 1 | 1116 |
| UIWidget_ShowReleasedState | `5` | 1 | 1124 |
| UIWidget_ShowReleasedState | `8` | 1 | 1124 |
| UI_DrawUnitInfoPane | `4112` | 1 | 1189 |
| UI_DrawUnitInfoPane | `7` | 7 | 1193, 1324, 1330, 1335 ... |
| UI_DrawUnitInfoPane | `2` | 13 | 1194, 1231, 1251, 1261 ... |
| UI_DrawUnitInfoPane | `46` | 9 | 1209, 1232, 1248, 1269 ... |
| UI_DrawUnitInfoPane | `52` | 8 | 1210, 1233, 1271, 1279 ... |
| UI_DrawUnitInfoPane | `100` | 3 | 1220, 1244, 1244 |
| UI_DrawUnitInfoPane | `9` | 4 | 1220, 1244, 1278, 1426 |
| UI_DrawUnitInfoPane | `188` | 1 | 1223 |
| UI_DrawUnitInfoPane | `2u` | 3 | 1226, 1227, 1245 |
| UI_DrawUnitInfoPane | `106` | 1 | 1244 |
| UI_DrawUnitInfoPane | `5` | 5 | 1244, 1246, 1246, 1250 ... |
| UI_DrawUnitInfoPane | `42` | 1 | 1246 |
| UI_DrawUnitInfoPane | `192` | 1 | 1250 |
| UI_DrawUnitInfoPane | `3` | 5 | 1250, 1300, 1338, 1347 ... |
| UI_DrawUnitInfoPane | `64` | 1 | 1250 |
| UI_DrawUnitInfoPane | `95` | 2 | 1253, 1337 |
| UI_DrawUnitInfoPane | `85` | 2 | 1254, 1291 |
| UI_DrawUnitInfoPane | `105` | 2 | 1255, 1291 |
| UI_DrawUnitInfoPane | `74` | 1 | 1261 |
| UI_DrawUnitInfoPane | `10` | 4 | 1268, 1329, 1334, 1359 |
| UI_DrawUnitInfoPane | `50` | 3 | 1291, 1328, 1334 |
| UI_DrawUnitInfoPane | `8` | 3 | 1291, 1373, 1411 |
| UI_DrawUnitInfoPane | `11` | 7 | 1292, 1294, 1295, 1297 ... |
| UI_DrawUnitInfoPane | `4` | 2 | 1292, 1304 |
| UI_DrawUnitInfoPane | `15` | 1 | 1295 |
| UI_DrawUnitInfoPane | `16` | 2 | 1298, 1353 |
| UI_DrawUnitInfoPane | `20` | 1 | 1298 |
| UI_DrawUnitInfoPane | `21` | 1 | 1313 |
| UI_DrawUnitInfoPane | `13` | 3 | 1326, 1332, 1407 |
| UI_DrawUnitInfoPane | `132` | 2 | 1328, 1337 |
| UI_DrawUnitInfoPane | `148` | 2 | 1328, 1337 |
| UI_DrawUnitInfoPane | `90` | 1 | 1329 |
| UI_DrawUnitInfoPane | `160` | 1 | 1334 |
| UI_DrawUnitInfoPane | `191` | 1 | 1334 |
| UI_DrawUnitInfoPane | `6` | 3 | 1338, 1353, 1378 |
| UI_DrawUnitInfoPane | `71` | 1 | 1351 |
| UI_DrawUnitInfoPane | `178` | 1 | 1352 |
| UI_DrawUnitInfoPane | `12` | 2 | 1353, 1401 |
| UI_DrawUnitInfoPane | `14` | 1 | 1355 |
| UI_DrawUnitInfoPane | `65` | 1 | 1382 |
| UI_DrawUnitInfoPane | `33` | 1 | 1410 |
| UI_DrawUnitInfoPane | `76` | 1 | 1410 |
| UI_DrawUnitInfoPane | `34` | 1 | 1411 |
| UI_DrawUnitInfoPane | `41` | 1 | 1426 |
| UI_DrawUnitInfoPane | `70` | 1 | 1426 |
| UI_DrawUnitInfoPane | `98` | 1 | 1426 |
| Unit_Info | `100` | 1 | 1467 |
| Unit_Info | `2` | 2 | 1485, 1549 |
| Unit_Info | `4112` | 1 | 1487 |
| Unit_Info | `188` | 1 | 1497 |
| Unit_Info | `116` | 1 | 1499 |
| Unit_Info | `201` | 1 | 1499 |
| Unit_Info | `115` | 1 | 1501 |
| Unit_Info | `200` | 1 | 1501 |
| Unit_Info | `5` | 2 | 1505, 1509 |
| Unit_Info | `46` | 2 | 1506, 1532 |
| Unit_Info | `11` | 1 | 1507 |
| Unit_Info | `52` | 2 | 1508, 1533 |
| Unit_Info | `10` | 1 | 1526 |
| Unit_Info | `8` | 1 | 1530 |
| Unit_Info | `0x73u` | 1 | 1546 |
| Unit_Info | `0xC8u` | 1 | 1546 |

### src/units/0041A960_0041C8B0_units_007.cpp

Missing evidence: AP/fatigue/morale thresholds, path and terrain costs, sprite geometry, sentinels and register-residue arguments. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UI_DrawSpecialUnitInfoPane | `100` | 1 | 53 |
| UI_DrawSpecialUnitInfoPane | `4112` | 2 | 64, 70 |
| UI_DrawSpecialUnitInfoPane | `2` | 3 | 68, 122, 124 |
| UI_DrawSpecialUnitInfoPane | `188` | 1 | 75 |
| UI_DrawSpecialUnitInfoPane | `116` | 1 | 77 |
| UI_DrawSpecialUnitInfoPane | `201` | 1 | 77 |
| UI_DrawSpecialUnitInfoPane | `115` | 1 | 79 |
| UI_DrawSpecialUnitInfoPane | `200` | 1 | 79 |
| UI_DrawSpecialUnitInfoPane | `7` | 2 | 81, 123 |
| UI_DrawSpecialUnitInfoPane | `24` | 1 | 82 |
| UI_DrawSpecialUnitInfoPane | `46` | 5 | 83, 110, 131, 156 ... |
| UI_DrawSpecialUnitInfoPane | `52` | 5 | 84, 111, 131, 132 ... |
| UI_DrawSpecialUnitInfoPane | `26` | 1 | 97 |
| UI_DrawSpecialUnitInfoPane | `25` | 1 | 100 |
| UI_DrawSpecialUnitInfoPane | `28` | 1 | 104 |
| UI_DrawSpecialUnitInfoPane | `20` | 1 | 112 |
| UI_DrawSpecialUnitInfoPane | `15` | 2 | 121, 124 |
| UI_DrawSpecialUnitInfoPane | `120` | 1 | 122 |
| UI_DrawSpecialUnitInfoPane | `173` | 1 | 122 |
| UI_DrawSpecialUnitInfoPane | `30` | 1 | 122 |
| UI_DrawSpecialUnitInfoPane | `9` | 1 | 122 |
| UI_DrawSpecialUnitInfoPane | `32` | 1 | 124 |
| UI_DrawSpecialUnitInfoPane | `8` | 4 | 124, 126, 127, 153 |
| UI_DrawSpecialUnitInfoPane | `88` | 1 | 124 |
| UI_DrawSpecialUnitInfoPane | `162` | 1 | 126 |
| UI_DrawSpecialUnitInfoPane | `3` | 1 | 126 |
| UI_DrawSpecialUnitInfoPane | `64` | 1 | 126 |
| UI_DrawSpecialUnitInfoPane | `13` | 1 | 127 |
| UI_DrawSpecialUnitInfoPane | `27` | 1 | 129 |
| UI_DrawSpecialUnitInfoPane | `105` | 1 | 130 |
| UI_DrawSpecialUnitInfoPane | `11` | 1 | 143 |
| UI_DrawSpecialUnitInfoPane | `5` | 1 | 145 |
| UI_DrawSpecialUnitInfoPane | `10` | 1 | 149 |
| UI_DrawSpecialUnitInfoPane | `0x73u` | 1 | 168 |
| UI_DrawSpecialUnitInfoPane | `0xC8u` | 1 | 168 |
| Unit_Attack | `404` | 2 | 260, 261 |
| Unit_Attack | `4` | 24 | 278, 281, 339, 339 ... |
| Unit_Attack | `140051` | 4 | 281, 281, 349, 350 |
| Unit_Attack | `158` | 1 | 307 |
| Unit_Attack | `60` | 1 | 308 |
| Unit_Attack | `79` | 2 | 314, 316 |
| Unit_Attack | `0x28` | 3 | 316, 442, 462 |
| Unit_Attack | `3` | 11 | 316, 355, 357, 357 ... |
| Unit_Attack | `10` | 3 | 336, 337, 429 |
| Unit_Attack | `15` | 1 | 338 |
| Unit_Attack | `5` | 3 | 340, 401, 423 |
| Unit_Attack | `6` | 6 | 345, 348, 390, 412 ... |
| Unit_Attack | `720` | 1 | 366 |
| Unit_Attack | `141441` | 8 | 407, 408, 430, 431 ... |
| Unit_Attack | `2` | 2 | 410, 560 |
| Unit_Attack | `20` | 1 | 519 |
| Unit_Attack | `4112` | 4 | 548, 555, 562, 567 |
| Unit_Attack | `160` | 1 | 571 |
| Unit_Attack | `467` | 1 | 571 |
| Unit_Attack | `473` | 1 | 571 |
| Unit_Attack | `76` | 1 | 571 |
| Unit_AttackBuilding | `404` | 2 | 661, 662 |
| Unit_AttackBuilding | `2` | 9 | 676, 706, 708, 711 ... |
| Unit_AttackBuilding | `158` | 1 | 695 |
| Unit_AttackBuilding | `60` | 1 | 696 |
| Unit_AttackBuilding | `79` | 1 | 697 |
| Unit_AttackBuilding | `5` | 4 | 700, 702, 707, 785 |
| Unit_AttackBuilding | `10` | 1 | 704 |
| Unit_AttackBuilding | `15` | 1 | 705 |
| Unit_AttackBuilding | `4` | 10 | 706, 708, 732, 737 ... |
| Unit_AttackBuilding | `12` | 2 | 719, 756 |
| Unit_AttackBuilding | `18` | 4 | 719, 754, 755, 800 |
| Unit_AttackBuilding | `3` | 4 | 719, 740, 767, 881 |
| Unit_AttackBuilding | `141441` | 8 | 737, 738, 786, 787 ... |
| Unit_AttackBuilding | `6` | 2 | 752, 780 |
| Unit_AttackBuilding | `20` | 1 | 828 |
| Unit_AttackBuilding | `4112` | 4 | 853, 862, 871, 876 |
| Unit_AttackBuilding | `45` | 1 | 879 |
| Unit_AttackBuilding | `160` | 1 | 881 |
| Unit_AttackBuilding | `467` | 1 | 881 |
| Unit_AttackBuilding | `473` | 1 | 881 |
| Unit_AttackBuilding | `76` | 1 | 881 |
| Unit_AttackBuilding | `211` | 1 | 885 |
| UnitSlots_CalcCombatStrengthScore | `0x28` | 1 | 930 |
| UnitSlots_CalcCombatStrengthScore | `13` | 1 | 936 |
| UnitSlots_CalcCombatStrengthScore | `2` | 3 | 941, 953, 988 |
| UnitSlots_CalcCombatStrengthScore | `5` | 6 | 941, 951, 963, 964 ... |
| UnitSlots_CalcCombatStrengthScore | `100` | 1 | 953 |
| UnitSlots_CalcCombatStrengthScore | `12` | 3 | 962, 984, 985 |
| UnitSlots_CalcCombatStrengthScore | `3` | 4 | 962, 984, 985, 987 |
| UnitSlots_CalcCombatStrengthScore | `6` | 1 | 982 |
| UnitSlots_CalcDefenseScore | `0x28` | 1 | 1006 |
| UnitSlots_CalcDefenseScore | `300` | 3 | 1011, 1011, 1011 |
| UnitSlots_CalcDefenseScore | `31` | 2 | 1011, 1011 |
| UnitSlots_CalcDefenseScore | `8` | 3 | 1011, 1011, 1011 |
| Building_ApplySiegeDamageToWallSections | `100` | 3 | 1029, 1030, 1031 |
| Building_ApplySiegeDamageToWallSections | `2` | 2 | 1031, 1032 |
| Building_ApplySiegeDamageToWallSections | `6` | 3 | 1035, 1043, 1044 |
| Building_ApplySiegeDamageToWallSections | `422` | 5 | 1036, 1037, 1044, 1047 ... |
| Building_ApplySiegeDamageToWallSections | `10` | 1 | 1045 |
| Building_ApplySiegeDamageToWallSections | `25` | 1 | 1045 |
| Building_CalcWallDefenseBonus | `100` | 1 | 1069 |
| Building_CalcWallDefenseBonus | `7` | 2 | 1071, 1082 |
| Building_CalcWallDefenseBonus | `422` | 4 | 1073, 1075, 1084, 1085 |
| Building_CalcWallDefenseBonus | `2` | 2 | 1088, 1088 |
| Building_CalcWallDefenseBonus | `421` | 1 | 1088 |
| Building_CalcWallDefenseBonus | `31` | 2 | 1089, 1089 |
| Building_CalcWallDefenseBonus | `8` | 3 | 1089, 1089, 1089 |
| CalculateBattleResult | `12` | 1 | 1105 |
| CalculateBattleResult | `100` | 1 | 1157 |
| CalculateBattleResult | `135` | 1 | 1157 |
| CalculateBattleResult | `9` | 4 | 1182, 1211, 1224, 1233 |
| CalculateBattleResult | `10` | 1 | 1215 |
| UI_PromptLeadTroopsPersonally | `100` | 2 | 1296, 1297 |
| UI_PromptLeadTroopsPersonally | `3` | 6 | 1298, 1341, 1345, 1346 ... |
| UI_PromptLeadTroopsPersonally | `4112` | 3 | 1329, 1359, 1389 |
| UI_PromptLeadTroopsPersonally | `2` | 12 | 1335, 1336, 1345, 1346 ... |
| UI_PromptLeadTroopsPersonally | `640` | 1 | 1335 |
| UI_PromptLeadTroopsPersonally | `480` | 1 | 1336 |
| UI_PromptLeadTroopsPersonally | `441` | 1 | 1342 |
| UI_PromptLeadTroopsPersonally | `59` | 1 | 1342 |
| UI_PromptLeadTroopsPersonally | `7` | 1 | 1344 |
| UI_PromptLeadTroopsPersonally | `166` | 1 | 1345 |
| UI_PromptLeadTroopsPersonally | `4` | 6 | 1345, 1346, 1362, 1363 ... |
| UI_PromptLeadTroopsPersonally | `42` | 1 | 1345 |
| UI_PromptLeadTroopsPersonally | `85` | 2 | 1345, 1346 |
| UI_PromptLeadTroopsPersonally | `395` | 1 | 1346 |
| UI_PromptLeadTroopsPersonally | `518` | 1 | 1346 |
| UI_PromptLeadTroopsPersonally | `110` | 2 | 1350, 1380 |
| UI_PromptLeadTroopsPersonally | `18` | 1 | 1352 |
| UI_PromptLeadTroopsPersonally | `31` | 4 | 1362, 1362, 1392, 1392 |
| UI_PromptLeadTroopsPersonally | `76` | 2 | 1362, 1392 |
| UI_PromptLeadTroopsPersonally | `48` | 2 | 1363, 1393 |
| UI_PromptLeadTroopsPersonally | `140051` | 2 | 1367, 1397 |
| UI_PromptLeadTroopsPersonally | `32` | 2 | 1368, 1398 |
| UI_PromptLeadTroopsPersonally | `50` | 2 | 1368, 1398 |
| UI_PromptLeadTroopsPersonally | `371` | 1 | 1382 |
| UI_PromptLeadTroopsPersonally | `17` | 1 | 1410 |
| UI_PromptLeadTroopsPersonally | `10` | 1 | 1411 |
| UI_PromptLeadTroopsPersonally | `160` | 1 | 1411 |
| UI_PromptLeadTroopsPersonally | `390` | 1 | 1411 |
| UI_PromptLeadTroopsPersonally | `6` | 1 | 1411 |
| UI_PromptLeadTroopsPersonally | `61` | 1 | 1416 |
| UI_PromptLeadTroopsPersonally | `279` | 1 | 1417 |
| UI_PromptLeadTroopsPersonally | `201` | 1 | 1418 |
| UI_PromptLeadTroopsPersonally | `2u` | 4 | 1429, 1430, 1448, 1449 |

### src/world/00408030_0040A0A0_world_001.cpp

Missing evidence: viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| UI_TrySelectFriendlyStackUnderCursor | `16` | 3 | 27, 28, 29 |
| UI_TrySelectFriendlyStackUnderCursor | `31` | 6 | 28, 29, 34, 35 ... |
| UI_TrySelectFriendlyStackUnderCursor | `6` | 11 | 28, 29, 29, 31 ... |
| UI_TrySelectFriendlyStackUnderCursor | `32` | 6 | 33, 34, 35, 40 ... |
| UI_TrySelectFriendlyStackUnderCursor | `0x7FFF` | 1 | 45 |
| UI_TrySelectFriendlyStackUnderCursor | `147178` | 1 | 45 |
| MapTile_HasOwnUnitStack | `0x1F4u` | 1 | 75 |
| MapTile_HasOwnUnitStack | `0x28` | 1 | 76 |
| MapTile_HasOwnUnitStack | `147180` | 1 | 76 |
| MapTile_HasOwnUnitStack | `147178` | 1 | 77 |
| MapTile_HasVisibleEnemyUnitStack | `0x1F4u` | 1 | 92 |
| MapTile_HasVisibleEnemyUnitStack | `0x28` | 1 | 92 |
| MapTile_HasVisibleEnemyUnitStack | `147180` | 1 | 92 |
| MapTile_HasVisibleEnemyUnitStack | `147178` | 1 | 95 |
| MapTile_HasVisibleEnemyUnitStack | `147894` | 1 | 95 |
| MapTile_HasOwnBuilding | `0x64` | 1 | 127 |
| MapTile_HasOwnBuilding | `16` | 1 | 130 |
| MapTile_HasOwnBuilding | `4` | 2 | 130, 130 |
| MapTile_HasOwnBuilding | `509676` | 1 | 133 |
| MapTile_HasOwnBuilding | `509690` | 1 | 133 |
| MapTile_HasEnemyBuilding | `0x64` | 1 | 154 |
| MapTile_HasEnemyBuilding | `16` | 1 | 157 |
| MapTile_HasEnemyBuilding | `4` | 2 | 157, 157 |
| MapTile_HasEnemyBuilding | `509676` | 1 | 160 |
| MapTile_HasEnemyBuilding | `509690` | 1 | 160 |
| WorldMap_HandleTileHoverAndClick | `3` | 9 | 277, 278, 279, 280 ... |
| WorldMap_HandleTileHoverAndClick | `32` | 4 | 287, 292, 293, 294 |
| WorldMap_HandleTileHoverAndClick | `16` | 4 | 289, 297, 298, 299 |
| WorldMap_HandleTileHoverAndClick | `31` | 4 | 293, 294, 298, 299 |
| WorldMap_HandleTileHoverAndClick | `6` | 9 | 293, 294, 294, 298 ... |
| WorldMap_HandleTileHoverAndClick | `0xC8` | 1 | 350 |
| WorldMap_HandleTileHoverAndClick | `0xFFFF` | 1 | 351 |
| WorldMap_HandleTileHoverAndClick | `0xB7` | 2 | 361, 363 |
| WorldMap_HandleTileHoverAndClick | `0xCA` | 2 | 370, 372 |
| WorldMap_HandleTileHoverAndClick | `0xCC` | 2 | 379, 381 |
| WorldMap_HandleTileHoverAndClick | `207` | 1 | 388 |
| WorldMap_HandleTileHoverAndClick | `185` | 1 | 397 |
| WorldMap_HandleTileHoverAndClick | `0x93` | 2 | 405, 407 |
| WorldMap_HandleTileHoverAndClick | `151` | 1 | 414 |
| WorldMap_HandleTileHoverAndClick | `39` | 1 | 422 |
| WorldMap_HandleTileHoverAndClick | `2` | 21 | 434, 531, 569, 602 ... |
| WorldMap_HandleTileHoverAndClick | `147490` | 10 | 467, 664, 677, 697 ... |
| WorldMap_HandleTileHoverAndClick | `200` | 5 | 474, 532, 570, 768 ... |
| WorldMap_HandleTileHoverAndClick | `278187` | 1 | 475 |
| WorldMap_HandleTileHoverAndClick | `509678` | 2 | 537, 774 |
| WorldMap_HandleTileHoverAndClick | `556374` | 2 | 537, 549 |
| WorldMap_HandleTileHoverAndClick | `100` | 2 | 575, 575 |
| WorldMap_HandleTileHoverAndClick | `509690` | 4 | 588, 590, 744, 787 |
| WorldMap_HandleTileHoverAndClick | `509676` | 1 | 590 |
| WorldMap_HandleTileHoverAndClick | `26` | 1 | 680 |
| WorldMap_HandleTileHoverAndClick | `320` | 3 | 684, 685, 923 |
| WorldMap_HandleTileHoverAndClick | `147180` | 5 | 693, 813, 849, 878 ... |
| WorldMap_HandleTileHoverAndClick | `145` | 2 | 699, 843 |
| WorldMap_HandleTileHoverAndClick | `147176` | 4 | 703, 725, 875, 926 |
| WorldMap_HandleTileHoverAndClick | `48` | 1 | 946 |
| WorldMap_HandleSurrenderAction | `6` | 1 | 1076 |
| WorldMap_HandleSurrenderAction | `2` | 2 | 1080, 1080 |
| WorldMap_HandleDeselectUnitAction | `49` | 1 | 1106 |
| WorldMap_SelectNextActiveUnitStack | `147180` | 2 | 1147, 1168 |
| WorldMap_SelectNextActiveUnitStack | `147178` | 1 | 1148 |
| WorldMap_SelectNextActiveUnitStack | `147176` | 1 | 1176 |
| WorldMap_CenterViewOnNextOwnedBuildingWithUnit | `100` | 3 | 1193, 1194, 1206 |
| WorldMap_CenterViewOnNextOwnedBuildingWithUnit | `0x64` | 1 | 1196 |
| WorldMap_CenterViewOnNextOwnedBuildingWithUnit | `4` | 2 | 1199, 1199 |
| WorldMap_CenterViewOnNextOwnedBuildingWithUnit | `16` | 1 | 1200 |
| WorldMap_CenterViewOnNextOwnedBuildingWithUnit | `509676` | 1 | 1201 |
| WorldMap_CenterViewOnNextOwnedBuildingWithUnit | `509675` | 1 | 1210 |
| WorldMap_ToggleSelectedUnitModeFlag | `49` | 1 | 1250 |
| WorldMap_ToggleSelectedUnitModeFlag | `8` | 2 | 1254, 1259 |
| WorldMap_ToggleSelectedUnitModeFlag | `2` | 1 | 1259 |
| WorldMap_ComputeBuildMenuActionFromCursor | `15` | 1 | 1275 |
| WorldMap_ComputeBuildMenuActionFromCursor | `16` | 1 | 1275 |
| WorldMap_ComputeBuildMenuActionFromCursor | `2` | 1 | 1275 |

### src/world/0040A0E0_0040B020_world_002.cpp

Missing evidence: viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| WorldMap_HandleBuilderActionMenu | `7` | 1 | 36 |
| WorldMap_HandleBuilderActionMenu | `0x40u` | 6 | 57, 65, 68, 116 ... |
| WorldMap_HandleBuilderActionMenu | `2` | 4 | 70, 96, 126, 126 |
| WorldMap_HandleBuilderActionMenu | `3` | 4 | 71, 73, 132, 133 |
| WorldMap_HandleBuilderActionMenu | `147176` | 1 | 81 |
| WorldMap_HandleBuilderActionMenu | `64` | 3 | 82, 91, 97 |
| WorldMap_HandleBuilderActionMenu | `4` | 1 | 86 |
| WorldMap_HandleBuilderActionMenu | `5` | 1 | 94 |
| WorldMap_WriteActionWidgetRecord | `4` | 1 | 166 |
| WorldMap_WriteActionWidgetRecord | `8` | 1 | 167 |
| WorldMap_WriteActionWidgetRecord | `12` | 1 | 168 |
| WorldMap_WriteActionWidgetRecord | `16` | 1 | 169 |
| WorldMap_WriteActionWidgetRecord | `20` | 1 | 170 |
| WorldMap_WriteActionWidgetRecord | `14` | 1 | 171 |
| WorldMap_WriteActionWidgetRecord | `24` | 1 | 171 |
| WorldMap_WriteActionWidgetRecord | `28` | 1 | 172 |
| WorldMap_WriteActionWidgetRecord | `32` | 1 | 173 |
| WorldMap_WriteActionWidgetRecord | `36` | 1 | 174 |
| WorldMap_WriteActionWidgetRecord | `40` | 1 | 175 |
| WorldMap_WriteActionWidgetRecord | `44` | 1 | 176 |
| WorldMap_WriteActionWidgetRecord | `48` | 1 | 177 |
| WorldMap_WriteActionWidgetRecord | `49` | 1 | 178 |
| WorldMap_EnsureActionButtonWidgetTable | `416` | 2 | 219, 255 |
| WorldMap_EnsureActionButtonWidgetTable | `400` | 3 | 220, 232, 244 |
| WorldMap_EnsureActionButtonWidgetTable | `480` | 2 | 231, 267 |
| WorldMap_EnsureActionButtonWidgetTable | `2` | 2 | 234, 242 |
| WorldMap_EnsureActionButtonWidgetTable | `3` | 2 | 235, 254 |
| WorldMap_EnsureActionButtonWidgetTable | `544` | 2 | 243, 279 |
| WorldMap_EnsureActionButtonWidgetTable | `4` | 2 | 246, 266 |
| WorldMap_EnsureActionButtonWidgetTable | `5` | 2 | 247, 278 |
| WorldMap_EnsureActionButtonWidgetTable | `432` | 3 | 256, 268, 280 |
| WorldMap_EnsureActionButtonWidgetTable | `6` | 1 | 258 |
| WorldMap_EnsureActionButtonWidgetTable | `7` | 1 | 259 |
| WorldMap_EnsureActionButtonWidgetTable | `8` | 1 | 270 |
| WorldMap_EnsureActionButtonWidgetTable | `9` | 1 | 271 |
| WorldMap_EnsureActionButtonWidgetTable | `10` | 1 | 282 |
| WorldMap_EnsureActionButtonWidgetTable | `11` | 1 | 283 |
| WorldMap_EnsureBuilderWidgetTables | `322` | 2 | 295, 515 |
| WorldMap_EnsureBuilderWidgetTables | `0x03` | 59 | 296, 300, 303, 306 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x0c` | 17 | 296, 300, 303, 306 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x52` | 16 | 296, 300, 303, 306 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x90` | 9 | 296, 299, 302, 330 ... |
| WorldMap_EnsureBuilderWidgetTables | `0xa0` | 18 | 296, 298, 298, 301 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x0e` | 12 | 297, 300, 304, 307 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x0f` | 2 | 297, 344 |
| WorldMap_EnsureBuilderWidgetTables | `0x10` | 7 | 297, 344, 348, 351 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x41` | 16 | 297, 301, 304, 307 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x91` | 16 | 297, 301, 304, 307 ... |
| WorldMap_EnsureBuilderWidgetTables | `0xf0` | 17 | 297, 301, 304, 307 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x40` | 7 | 298, 301, 304, 308 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x4e` | 34 | 298, 298, 298, 299 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x65` | 4 | 298, 323, 325, 327 |
| WorldMap_EnsureBuilderWidgetTables | `0x6b` | 4 | 298, 323, 324, 327 |
| WorldMap_EnsureBuilderWidgetTables | `0x70` | 1 | 298 |
| WorldMap_EnsureBuilderWidgetTables | `0xcb` | 21 | 298, 298, 298, 299 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x77` | 1 | 299 |
| WorldMap_EnsureBuilderWidgetTables | `0xe0` | 9 | 299, 309, 331, 333 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x13` | 2 | 300, 347 |
| WorldMap_EnsureBuilderWidgetTables | `0x14` | 2 | 300, 347 |
| WorldMap_EnsureBuilderWidgetTables | `0x7c` | 1 | 301 |
| WorldMap_EnsureBuilderWidgetTables | `0x84` | 1 | 301 |
| WorldMap_EnsureBuilderWidgetTables | `0x02` | 18 | 302, 312, 319, 319 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x20` | 6 | 302, 312, 319, 336 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x89` | 1 | 302 |
| WorldMap_EnsureBuilderWidgetTables | `0x8f` | 1 | 302 |
| WorldMap_EnsureBuilderWidgetTables | `0x11` | 2 | 303, 350 |
| WorldMap_EnsureBuilderWidgetTables | `0x12` | 2 | 303, 350 |
| WorldMap_EnsureBuilderWidgetTables | `0x94` | 1 | 304 |
| WorldMap_EnsureBuilderWidgetTables | `0xa4` | 1 | 305 |
| WorldMap_EnsureBuilderWidgetTables | `0xb5` | 1 | 305 |
| WorldMap_EnsureBuilderWidgetTables | `0xc1` | 1 | 305 |
| WorldMap_EnsureBuilderWidgetTables | `0x15` | 2 | 306, 353 |
| WorldMap_EnsureBuilderWidgetTables | `0xb0` | 7 | 306, 309, 312, 339 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x16` | 2 | 307, 354 |
| WorldMap_EnsureBuilderWidgetTables | `0xc6` | 1 | 308 |
| WorldMap_EnsureBuilderWidgetTables | `0xcc` | 4 | 308, 315, 315, 315 |
| WorldMap_EnsureBuilderWidgetTables | `0xd1` | 1 | 308 |
| WorldMap_EnsureBuilderWidgetTables | `0xd6` | 1 | 309 |
| WorldMap_EnsureBuilderWidgetTables | `0x17` | 2 | 310, 357 |
| WorldMap_EnsureBuilderWidgetTables | `0x18` | 2 | 310, 357 |
| WorldMap_EnsureBuilderWidgetTables | `0xdb` | 1 | 311 |
| WorldMap_EnsureBuilderWidgetTables | `0xe4` | 2 | 311, 339 |
| WorldMap_EnsureBuilderWidgetTables | `0xed` | 1 | 312 |
| WorldMap_EnsureBuilderWidgetTables | `0xf5` | 1 | 312 |
| WorldMap_EnsureBuilderWidgetTables | `0x19` | 2 | 313, 360 |
| WorldMap_EnsureBuilderWidgetTables | `0x1a` | 2 | 313, 360 |
| WorldMap_EnsureBuilderWidgetTables | `0xfa` | 1 | 314 |
| WorldMap_EnsureBuilderWidgetTables | `0x07` | 2 | 315, 362 |
| WorldMap_EnsureBuilderWidgetTables | `0xff` | 33 | 315, 315, 316, 316 ... |
| WorldMap_EnsureBuilderWidgetTables | `706` | 1 | 318 |
| WorldMap_EnsureBuilderWidgetTables | `0x25` | 1 | 319 |
| WorldMap_EnsureBuilderWidgetTables | `0x34` | 1 | 319 |
| WorldMap_EnsureBuilderWidgetTables | `0x39` | 1 | 319 |
| WorldMap_EnsureBuilderWidgetTables | `0x22` | 1 | 320 |
| WorldMap_EnsureBuilderWidgetTables | `0x23` | 1 | 320 |
| WorldMap_EnsureBuilderWidgetTables | `0x45` | 1 | 320 |
| WorldMap_EnsureBuilderWidgetTables | `0x36` | 1 | 321 |
| WorldMap_EnsureBuilderWidgetTables | `0x37` | 1 | 321 |
| WorldMap_EnsureBuilderWidgetTables | `0x42` | 11 | 321, 331, 335, 338 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x43` | 1 | 321 |
| WorldMap_EnsureBuilderWidgetTables | `0x62` | 7 | 322, 323, 323, 324 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x63` | 7 | 322, 323, 323, 324 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x64` | 3 | 322, 323, 325 |
| WorldMap_EnsureBuilderWidgetTables | `0x66` | 4 | 322, 324, 325, 326 |
| WorldMap_EnsureBuilderWidgetTables | `0x67` | 3 | 322, 324, 326 |
| WorldMap_EnsureBuilderWidgetTables | `0x69` | 3 | 322, 324, 326 |
| WorldMap_EnsureBuilderWidgetTables | `0x6a` | 4 | 322, 324, 326, 326 |
| WorldMap_EnsureBuilderWidgetTables | `0x6c` | 3 | 322, 324, 326 |
| WorldMap_EnsureBuilderWidgetTables | `0x68` | 3 | 323, 325, 327 |
| WorldMap_EnsureBuilderWidgetTables | `0xf8` | 2 | 327, 352 |
| WorldMap_EnsureBuilderWidgetTables | `0xfc` | 2 | 327, 329 |
| WorldMap_EnsureBuilderWidgetTables | `0x04` | 2 | 328, 328 |
| WorldMap_EnsureBuilderWidgetTables | `0x08` | 1 | 328 |
| WorldMap_EnsureBuilderWidgetTables | `0x1b` | 2 | 330, 331 |
| WorldMap_EnsureBuilderWidgetTables | `0x54` | 4 | 331, 335, 338, 341 |
| WorldMap_EnsureBuilderWidgetTables | `0xda` | 1 | 332 |
| WorldMap_EnsureBuilderWidgetTables | `0xeb` | 8 | 332, 336, 339, 342 ... |
| WorldMap_EnsureBuilderWidgetTables | `0x1c` | 2 | 334, 334 |
| WorldMap_EnsureBuilderWidgetTables | `0xdf` | 1 | 336 |
| WorldMap_EnsureBuilderWidgetTables | `0x1d` | 2 | 337, 337 |
| WorldMap_EnsureBuilderWidgetTables | `0x1e` | 2 | 340, 340 |
| WorldMap_EnsureBuilderWidgetTables | `0xe9` | 1 | 342 |
| WorldMap_EnsureBuilderWidgetTables | `0x50` | 1 | 345 |
| WorldMap_EnsureBuilderWidgetTables | `0xee` | 1 | 346 |
| WorldMap_EnsureBuilderWidgetTables | `0x51` | 5 | 348, 351, 355, 358 ... |
| WorldMap_EnsureBuilderWidgetTables | `0xf3` | 1 | 349 |
| WorldMap_EnsureBuilderWidgetTables | `0xfd` | 1 | 356 |
| WorldMap_EnsureBuilderWidgetTables | `0xec` | 2 | 359, 362 |
| WorldMap_EnsureBuilderWidgetTables | `12` | 1 | 393 |
| WorldMap_EnsureBuilderWidgetTables | `28` | 1 | 395 |
| WorldMap_EnsureBuilderWidgetTables | `32` | 1 | 397 |
| WorldMap_EnsureBuilderWidgetTables | `36` | 1 | 399 |
| WorldMap_EnsureBuilderWidgetTables | `40` | 1 | 401 |
| WorldMap_EnsureBuilderWidgetTables | `44` | 1 | 403 |
| WorldMap_EnsureBuilderWidgetTables | `49` | 1 | 405 |
| WorldMap_EnsureBuilderWidgetTables | `65` | 1 | 407 |
| WorldMap_EnsureBuilderWidgetTables | `81` | 1 | 409 |
| WorldMap_EnsureBuilderWidgetTables | `85` | 1 | 411 |
| WorldMap_EnsureBuilderWidgetTables | `89` | 1 | 413 |
| WorldMap_EnsureBuilderWidgetTables | `93` | 1 | 415 |
| WorldMap_EnsureBuilderWidgetTables | `97` | 1 | 417 |
| WorldMap_EnsureBuilderWidgetTables | `102` | 1 | 419 |
| WorldMap_EnsureBuilderWidgetTables | `118` | 1 | 421 |
| WorldMap_EnsureBuilderWidgetTables | `134` | 1 | 423 |
| WorldMap_EnsureBuilderWidgetTables | `138` | 1 | 425 |
| WorldMap_EnsureBuilderWidgetTables | `142` | 1 | 427 |
| WorldMap_EnsureBuilderWidgetTables | `146` | 1 | 429 |
| WorldMap_EnsureBuilderWidgetTables | `150` | 1 | 431 |
| WorldMap_EnsureBuilderWidgetTables | `155` | 1 | 433 |
| WorldMap_EnsureBuilderWidgetTables | `171` | 1 | 435 |
| WorldMap_EnsureBuilderWidgetTables | `187` | 1 | 437 |
| WorldMap_EnsureBuilderWidgetTables | `191` | 1 | 439 |
| WorldMap_EnsureBuilderWidgetTables | `195` | 1 | 441 |
| WorldMap_EnsureBuilderWidgetTables | `199` | 1 | 443 |
| WorldMap_EnsureBuilderWidgetTables | `203` | 1 | 445 |
| WorldMap_EnsureBuilderWidgetTables | `208` | 2 | 447, 483 |
| WorldMap_EnsureBuilderWidgetTables | `224` | 1 | 449 |
| WorldMap_EnsureBuilderWidgetTables | `240` | 1 | 451 |
| WorldMap_EnsureBuilderWidgetTables | `244` | 1 | 453 |
| WorldMap_EnsureBuilderWidgetTables | `248` | 1 | 455 |
| WorldMap_EnsureBuilderWidgetTables | `252` | 1 | 457 |
| WorldMap_EnsureBuilderWidgetTables | `256` | 1 | 459 |
| WorldMap_EnsureBuilderWidgetTables | `261` | 2 | 461, 497 |
| WorldMap_EnsureBuilderWidgetTables | `277` | 1 | 463 |
| WorldMap_EnsureBuilderWidgetTables | `293` | 1 | 465 |
| WorldMap_EnsureBuilderWidgetTables | `297` | 1 | 467 |
| WorldMap_EnsureBuilderWidgetTables | `301` | 1 | 469 |
| WorldMap_EnsureBuilderWidgetTables | `305` | 1 | 471 |
| WorldMap_EnsureBuilderWidgetTables | `309` | 1 | 473 |
| WorldMap_EnsureBuilderWidgetTables | `314` | 2 | 475, 511 |
| WorldMap_EnsureBuilderWidgetTables | `184` | 1 | 477 |
| WorldMap_EnsureBuilderWidgetTables | `200` | 1 | 479 |
| WorldMap_EnsureBuilderWidgetTables | `204` | 1 | 481 |
| WorldMap_EnsureBuilderWidgetTables | `212` | 1 | 485 |
| WorldMap_EnsureBuilderWidgetTables | `216` | 1 | 487 |
| WorldMap_EnsureBuilderWidgetTables | `221` | 1 | 489 |
| WorldMap_EnsureBuilderWidgetTables | `237` | 1 | 491 |
| WorldMap_EnsureBuilderWidgetTables | `253` | 1 | 493 |
| WorldMap_EnsureBuilderWidgetTables | `257` | 1 | 495 |
| WorldMap_EnsureBuilderWidgetTables | `265` | 1 | 499 |
| WorldMap_EnsureBuilderWidgetTables | `269` | 1 | 501 |
| WorldMap_EnsureBuilderWidgetTables | `274` | 1 | 503 |
| WorldMap_EnsureBuilderWidgetTables | `290` | 1 | 505 |
| WorldMap_EnsureBuilderWidgetTables | `306` | 1 | 507 |
| WorldMap_EnsureBuilderWidgetTables | `310` | 1 | 509 |
| WorldMap_EnsureBuilderWidgetTables | `318` | 1 | 513 |
| WorldMap_EnsureBuilderWidgetTables | `327` | 1 | 517 |
| WorldMap_EnsureBuilderWidgetTables | `343` | 1 | 519 |
| WorldMap_EnsureBuilderWidgetTables | `359` | 1 | 521 |
| WorldMap_EnsureBuilderWidgetTables | `363` | 1 | 523 |
| WorldMap_EnsureBuilderWidgetTables | `367` | 1 | 525 |
| WorldMap_EnsureBuilderWidgetTables | `371` | 1 | 527 |
| WorldMap_EnsureBuilderWidgetTables | `375` | 1 | 529 |
| WorldMap_EnsureBuilderWidgetTables | `380` | 1 | 531 |
| WorldMap_EnsureBuilderWidgetTables | `396` | 1 | 533 |
| WorldMap_EnsureBuilderWidgetTables | `412` | 1 | 535 |
| WorldMap_EnsureBuilderWidgetTables | `416` | 1 | 537 |
| WorldMap_EnsureBuilderWidgetTables | `420` | 1 | 539 |
| WorldMap_EnsureBuilderWidgetTables | `424` | 1 | 541 |
| WorldMap_EnsureBuilderWidgetTables | `428` | 1 | 543 |
| WorldMap_EnsureBuilderWidgetTables | `433` | 1 | 545 |
| WorldMap_EnsureBuilderWidgetTables | `449` | 1 | 547 |
| WorldMap_EnsureBuilderWidgetTables | `465` | 1 | 549 |
| WorldMap_EnsureBuilderWidgetTables | `469` | 1 | 551 |
| WorldMap_EnsureBuilderWidgetTables | `473` | 1 | 553 |
| WorldMap_EnsureBuilderWidgetTables | `477` | 1 | 555 |
| WorldMap_EnsureBuilderWidgetTables | `481` | 1 | 557 |
| WorldMap_EnsureBuilderWidgetTables | `486` | 1 | 559 |
| WorldMap_EnsureBuilderWidgetTables | `502` | 1 | 561 |
| WorldMap_EnsureBuilderWidgetTables | `518` | 1 | 563 |
| WorldMap_EnsureBuilderWidgetTables | `522` | 1 | 565 |
| WorldMap_EnsureBuilderWidgetTables | `526` | 1 | 567 |
| WorldMap_EnsureBuilderWidgetTables | `530` | 1 | 569 |
| WorldMap_EnsureBuilderWidgetTables | `534` | 1 | 571 |
| WorldMap_EnsureBuilderWidgetTables | `539` | 1 | 573 |
| WorldMap_EnsureBuilderWidgetTables | `555` | 1 | 575 |
| WorldMap_EnsureBuilderWidgetTables | `571` | 1 | 577 |
| WorldMap_EnsureBuilderWidgetTables | `575` | 1 | 579 |
| WorldMap_EnsureBuilderWidgetTables | `579` | 1 | 581 |
| WorldMap_EnsureBuilderWidgetTables | `583` | 1 | 583 |
| WorldMap_EnsureBuilderWidgetTables | `587` | 1 | 585 |
| WorldMap_EnsureBuilderWidgetTables | `592` | 1 | 587 |
| WorldMap_EnsureBuilderWidgetTables | `608` | 1 | 589 |
| WorldMap_EnsureBuilderWidgetTables | `624` | 1 | 591 |
| WorldMap_EnsureBuilderWidgetTables | `628` | 1 | 593 |
| WorldMap_EnsureBuilderWidgetTables | `632` | 1 | 595 |
| WorldMap_EnsureBuilderWidgetTables | `636` | 1 | 597 |
| WorldMap_EnsureBuilderWidgetTables | `640` | 1 | 599 |
| WorldMap_EnsureBuilderWidgetTables | `645` | 1 | 601 |
| WorldMap_EnsureBuilderWidgetTables | `661` | 1 | 603 |
| WorldMap_EnsureBuilderWidgetTables | `677` | 1 | 605 |
| WorldMap_EnsureBuilderWidgetTables | `681` | 1 | 607 |
| WorldMap_EnsureBuilderWidgetTables | `685` | 1 | 609 |
| WorldMap_EnsureBuilderWidgetTables | `689` | 1 | 611 |
| WorldMap_EnsureBuilderWidgetTables | `693` | 1 | 613 |
| WorldMap_EnsureBuilderWidgetTables | `698` | 1 | 615 |
| UnitBattle_WriteActionWidgetRecord | `4` | 1 | 635 |
| UnitBattle_WriteActionWidgetRecord | `8` | 1 | 636 |
| UnitBattle_WriteActionWidgetRecord | `12` | 1 | 637 |
| UnitBattle_WriteActionWidgetRecord | `16` | 1 | 638 |
| UnitBattle_WriteActionWidgetRecord | `20` | 1 | 639 |
| UnitBattle_WriteActionWidgetRecord | `24` | 1 | 640 |
| UnitBattle_WriteActionWidgetRecord | `28` | 1 | 641 |
| UnitBattle_WriteActionWidgetRecord | `32` | 1 | 642 |
| UnitBattle_WriteActionWidgetRecord | `36` | 1 | 643 |
| UnitBattle_WriteActionWidgetRecord | `40` | 1 | 644 |
| UnitBattle_WriteActionWidgetRecord | `44` | 1 | 645 |
| UnitBattle_WriteActionWidgetRecord | `48` | 1 | 646 |
| UnitBattle_WriteActionWidgetRecord | `49` | 1 | 647 |
| UnitBattle_EnsureActionButtonWidgetTable | `13` | 1 | 685 |
| UnitBattle_EnsureActionButtonWidgetTable | `498` | 3 | 689, 715, 728 |
| UnitBattle_EnsureActionButtonWidgetTable | `370` | 2 | 690, 703 |
| UnitBattle_EnsureActionButtonWidgetTable | `7` | 1 | 692 |
| UnitBattle_EnsureActionButtonWidgetTable | `8` | 1 | 693 |
| UnitBattle_EnsureActionButtonWidgetTable | `561` | 2 | 702, 741 |
| UnitBattle_EnsureActionButtonWidgetTable | `2` | 2 | 706, 714 |
| UnitBattle_EnsureActionButtonWidgetTable | `401` | 2 | 716, 742 |
| UnitBattle_EnsureActionButtonWidgetTable | `3` | 2 | 718, 727 |
| UnitBattle_EnsureActionButtonWidgetTable | `4` | 2 | 719, 740 |
| UnitBattle_EnsureActionButtonWidgetTable | `432` | 1 | 729 |
| UnitBattle_EnsureActionButtonWidgetTable | `5` | 2 | 731, 753 |
| UnitBattle_EnsureActionButtonWidgetTable | `6` | 1 | 732 |
| UnitBattle_EnsureActionButtonWidgetTable | `9` | 1 | 744 |
| UnitBattle_EnsureActionButtonWidgetTable | `10` | 1 | 745 |
| UnitBattle_EnsureActionButtonWidgetTable | `11` | 1 | 746 |
| UnitBattle_EnsureActionButtonWidgetTable | `505` | 1 | 754 |
| UnitBattle_EnsureActionButtonWidgetTable | `12` | 2 | 757, 758 |
| WorldMap_RefreshActionButtonBarState | `2` | 2 | 784, 788 |
| WorldMap_RefreshActionButtonBarState | `3` | 1 | 796 |
| WorldMap_LoadActionButtonSprites | `4112` | 1 | 812 |
| WorldMap_SyncSelectionForHumanPlayer | `147180` | 1 | 874 |
| WorldMap_DrawTurnBannerReveal | `400` | 5 | 940, 962, 963, 965 ... |
| WorldMap_DrawTurnBannerReveal | `416` | 6 | 940, 946, 965, 965 ... |
| WorldMap_DrawTurnBannerReveal | `5` | 1 | 941 |
| WorldMap_DrawTurnBannerReveal | `46` | 1 | 943 |
| WorldMap_DrawTurnBannerReveal | `404` | 1 | 944 |
| WorldMap_DrawTurnBannerReveal | `568` | 1 | 944 |
| WorldMap_DrawTurnBannerReveal | `7` | 1 | 945 |
| WorldMap_DrawTurnBannerReveal | `3` | 2 | 946, 949 |
| WorldMap_DrawTurnBannerReveal | `436` | 1 | 946 |
| WorldMap_DrawTurnBannerReveal | `608` | 1 | 946 |
| WorldMap_DrawTurnBannerReveal | `147155` | 1 | 947 |
| WorldMap_DrawTurnBannerReveal | `76` | 1 | 949 |
| WorldMap_DrawTurnBannerReveal | `405` | 1 | 950 |
| WorldMap_DrawTurnBannerReveal | `421` | 1 | 950 |
| WorldMap_DrawTurnBannerReveal | `0x1A0u` | 2 | 965, 970 |
| WorldMap_DrawTurnBannerReveal | `399` | 1 | 968 |
| WorldMap_DrawTurnBannerReveal | `0x190u` | 1 | 970 |
| WorldMap_RenderPlayerTurnIntroScreen | `16` | 1 | 991 |
| WorldMap_RenderPlayerTurnIntroScreen | `188` | 2 | 1001, 1004 |
| WorldMap_RenderPlayerTurnIntroScreen | `20` | 4 | 1011, 1043, 1047, 1050 |
| WorldMap_RenderPlayerTurnIntroScreen | `1024` | 1 | 1012 |
| WorldMap_RenderPlayerTurnIntroScreen | `256` | 1 | 1014 |
| WorldMap_RenderPlayerTurnIntroScreen | `7` | 1 | 1016 |
| WorldMap_RenderPlayerTurnIntroScreen | `184` | 1 | 1018 |
| WorldMap_RenderPlayerTurnIntroScreen | `6` | 3 | 1024, 1025, 1051 |
| WorldMap_RenderPlayerTurnIntroScreen | `3` | 3 | 1031, 1035, 1040 |
| WorldMap_RenderPlayerTurnIntroScreen | `370` | 3 | 1031, 1035, 1040 |
| WorldMap_RenderPlayerTurnIntroScreen | `4` | 3 | 1031, 1035, 1040 |
| WorldMap_RenderPlayerTurnIntroScreen | `639` | 3 | 1031, 1035, 1040 |
| WorldMap_RenderPlayerTurnIntroScreen | `2` | 3 | 1033, 1057, 1059 |
| Game_AdvanceToNextPlayerTurn | `5` | 1 | 1106 |
| Game_AdvanceToNextPlayerTurn | `0xFFFFFFFF` | 7 | 1166, 1183, 1191, 1192 ... |
| Game_AdvanceToNextPlayerTurn | `19` | 1 | 1182 |
| Game_AdvanceToNextPlayerTurn | `9` | 1 | 1182 |
| Game_AdvanceToNextPlayerTurn | `0x140u` | 1 | 1222 |
| Game_AdvanceToNextPlayerTurn | `0xF0u` | 1 | 1222 |
| WorldMap_RenderHook | `7` | 2 | 1255, 1256 |
| WorldMap_RenderHook | `160` | 1 | 1256 |
| WorldMap_RenderHook | `467` | 1 | 1256 |
| WorldMap_RenderHook | `473` | 1 | 1256 |
| WorldMap_RenderHook | `76` | 1 | 1256 |
| WorldMap_RenderHook | `20` | 1 | 1259 |
| WorldMap_RedrawFrame | `11` | 2 | 1289, 1292 |
| WorldMap_RedrawFrame | `16` | 1 | 1289 |
| WorldMap_RedrawFrame | `2` | 1 | 1294 |
| WorldMap_RedrawFrame | `44` | 1 | 1294 |
| WorldMap_LoadResources | `4112` | 7 | 1347, 1351, 1355, 1359 ... |
| WorldMap_LoadResources | `188` | 1 | 1377 |
| WorldMap_LoadResources | `1024` | 1 | 1382 |
| WorldMap_RunInputScriptStep | `256` | 1 | 1440 |
| WorldMap_RunInputScriptStep | `32` | 1 | 1477 |
| WorldMap_RunInputScriptStep | `2` | 7 | 1492, 1523, 1529, 1531 ... |
| WorldMap_RunInputScriptStep | `3` | 6 | 1500, 1507, 1514, 1521 ... |
| WorldMap_RunInputScriptStep | `4` | 3 | 1523, 1540, 1541 |
| WorldMap_RunInputScriptStep | `5` | 2 | 1540, 1541 |
| WorldMap_RunInputScriptStep | `6` | 1 | 1544 |
| WorldMap_RunInputScriptStep | `16` | 1 | 1586 |
| Battle_RunInputScriptStep | `256` | 1 | 1628 |
| Battle_RunInputScriptStep | `32` | 1 | 1663 |
| Battle_RunInputScriptStep | `2` | 4 | 1678, 1709, 1715, 1717 |
| Battle_RunInputScriptStep | `3` | 6 | 1686, 1693, 1700, 1707 ... |
| Battle_RunInputScriptStep | `4` | 3 | 1709, 1726, 1727 |
| Battle_RunInputScriptStep | `5` | 2 | 1726, 1727 |
| Battle_RunInputScriptStep | `6` | 1 | 1730 |

### src/world/0040B0A0_0040D560_world_003.cpp

Missing evidence: viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| WorldMap_RunHumanTurnLoop | `5` | 2 | 42, 54 |
| WorldMap_RunHumanTurnLoop | `6` | 2 | 43, 55 |
| WorldMap_RunHumanTurnLoop | `480` | 1 | 46 |
| WorldMap_RunHumanTurnLoop | `640` | 1 | 46 |
| WorldMap_RunHumanTurnLoop | `277` | 2 | 53, 54 |
| WorldMap_RunHumanTurnLoop | `4` | 1 | 53 |
| WorldMap_RunHumanTurnLoop | `56` | 2 | 78, 95 |
| WorldMap_RunHumanTurnLoop | `34` | 1 | 80 |
| WorldMap_RunHumanTurnLoop | `147151` | 4 | 82, 84, 88, 90 |
| WorldMap_RunHumanTurnLoop | `205` | 2 | 97, 103 |
| WorldMap_RunHumanTurnLoop | `7` | 2 | 101, 112 |
| WorldMap_RunHumanTurnLoop | `203` | 2 | 106, 114 |
| WorldMap_RunHumanTurnLoop | `200` | 1 | 118 |
| WorldMap_RunHumanTurnLoop | `2` | 2 | 127, 131 |
| WorldMap_RunHumanTurnLoop | `20` | 1 | 186 |
| PlayGame | `5` | 3 | 255, 303, 314 |
| PlayGame | `4112` | 2 | 281, 285 |
| PlayGame | `8` | 1 | 294 |
| PlayGame | `140039` | 1 | 295 |
| PlayGame | `140043` | 1 | 296 |
| PlayGame | `7` | 2 | 298, 301 |
| PlayGame | `160` | 1 | 301 |
| PlayGame | `467` | 1 | 301 |
| PlayGame | `473` | 1 | 301 |
| PlayGame | `76` | 1 | 301 |
| PlayGame | `6` | 2 | 304, 315 |
| PlayGame | `480` | 1 | 307 |
| PlayGame | `640` | 1 | 307 |
| PlayGame | `277` | 2 | 313, 314 |
| PlayGame | `4` | 1 | 313 |
| PlayGame | `20` | 7 | 318, 321, 322, 323 ... |
| PlayGame | `19` | 1 | 395 |
| PlayGame | `9` | 2 | 395, 398 |
| Render_ReleaseSurface | `4112` | 1 | 459 |
| Render_ReleaseSurface | `12` | 1 | 464 |
| TextSprite_ActivateResourceSlot | `4112` | 1 | 485 |
| TextSprite_DrawGlyphAndAdvance | `32` | 1 | 517 |
| TextSprite_MeasureStringExtent | `10` | 1 | 572 |
| TextSprite_MeasureStringExtent | `32` | 1 | 578 |
| TextSprite_FindWordWrapBreak | `10` | 1 | 603 |
| TextSprite_FindWordWrapBreak | `32` | 2 | 605, 608 |
| Str_CountSpaces | `32` | 1 | 629 |
| UI_RenderAlignedTextWithCursor | `2` | 2 | 686, 690 |
| UI_RenderAlignedTextWithCursor | `3` | 4 | 689, 717, 726, 732 |
| UI_RenderAlignedTextWithCursor | `4` | 1 | 692 |
| UI_RenderAlignedTextWithCursor | `5` | 4 | 702, 717, 726, 732 |
| UI_RenderAlignedTextWithCursor | `6` | 1 | 703 |
| UI_RenderAlignedTextWithCursor | `10` | 2 | 713, 751 |
| UI_RenderAlignedTextWithCursor | `32` | 1 | 747 |
| UI_RenderAlignedTextWithCursor | `0x5Fu` | 2 | 754, 758 |
| UI_DrawTextFmtV | `524` | 1 | 784 |
| TextSprite_BuildOrLoadCachedFont | `1024` | 1 | 829 |
| TextSprite_BuildOrLoadCachedFont | `100` | 2 | 830, 831 |
| TextSprite_BuildOrLoadCachedFont | `768` | 1 | 848 |
| TextSprite_BuildOrLoadCachedFont | `4112` | 2 | 858, 865 |
| TextSprite_BuildOrLoadCachedFont | `2` | 2 | 879, 881 |
| TextSprite_BuildOrLoadCachedFont | `97` | 1 | 885 |
| TextSprite_BuildOrLoadCachedFont | `12` | 1 | 886 |
| UI_EndDraw | `3` | 1 | 917 |
| Font_ResetGlyphFallbackTable | `1536` | 1 | 975 |
| Font_ResetGlyphFallbackTable | `3` | 1 | 979 |
| Font_SetGlyphFallbackEntry | `3` | 1 | 991 |
| Font_BuildGlyphFallbackChain | `0xFFFE` | 1 | 1010 |
| Font_BuildGlyphFallbackChain | `0xFFFF` | 2 | 1010, 1010 |
| Font_BuildGlyphFallbackChain | `3` | 1 | 1010 |
| Font_InitGlyphFallbackTablesForLanguage | `0x400u` | 1 | 1030 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24Bu` | 2 | 1032, 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24Cu` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24Du` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24Eu` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24Fu` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x250u` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x251u` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `0x252u` | 1 | 1032 |
| Font_InitGlyphFallbackTablesForLanguage | `15` | 6 | 1032, 1037, 1061, 1081 ... |
| Font_InitGlyphFallbackTablesForLanguage | `0xDF` | 1 | 1033 |
| Font_InitGlyphFallbackTablesForLanguage | `0xEA` | 1 | 1033 |
| Font_InitGlyphFallbackTablesForLanguage | `0x0C` | 1 | 1039 |
| Font_InitGlyphFallbackTablesForLanguage | `0x18` | 4 | 1040, 1085, 1110, 1127 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24` | 1 | 1041 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30` | 4 | 1042, 1088, 1113, 1130 |
| Font_InitGlyphFallbackTablesForLanguage | `0x3C` | 1 | 1043 |
| Font_InitGlyphFallbackTablesForLanguage | `0x48` | 3 | 1044, 1091, 1133 |
| Font_InitGlyphFallbackTablesForLanguage | `0x54` | 1 | 1045 |
| Font_InitGlyphFallbackTablesForLanguage | `0x60` | 3 | 1046, 1094, 1136 |
| Font_InitGlyphFallbackTablesForLanguage | `0x6C` | 1 | 1047 |
| Font_InitGlyphFallbackTablesForLanguage | `0x78` | 3 | 1048, 1097, 1139 |
| Font_InitGlyphFallbackTablesForLanguage | `0x84` | 1 | 1049 |
| Font_InitGlyphFallbackTablesForLanguage | `0x90` | 1 | 1050 |
| Font_InitGlyphFallbackTablesForLanguage | `0x9C` | 1 | 1051 |
| Font_InitGlyphFallbackTablesForLanguage | `0xA8` | 1 | 1052 |
| Font_InitGlyphFallbackTablesForLanguage | `0xB4` | 1 | 1053 |
| Font_InitGlyphFallbackTablesForLanguage | `6` | 3 | 1056, 1068, 1159 |
| Font_InitGlyphFallbackTablesForLanguage | `9` | 1 | 1056 |
| Font_InitGlyphFallbackTablesForLanguage | `0x253` | 2 | 1058, 1149 |
| Font_InitGlyphFallbackTablesForLanguage | `8` | 5 | 1058, 1083, 1108, 1125 ... |
| Font_InitGlyphFallbackTablesForLanguage | `2` | 5 | 1064, 1118, 1155, 1163 ... |
| Font_InitGlyphFallbackTablesForLanguage | `3` | 2 | 1065, 1156 |
| Font_InitGlyphFallbackTablesForLanguage | `4` | 2 | 1066, 1157 |
| Font_InitGlyphFallbackTablesForLanguage | `5` | 4 | 1067, 1147, 1158, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `7` | 2 | 1069, 1160 |
| Font_InitGlyphFallbackTablesForLanguage | `0x19F` | 3 | 1077, 1102, 1119 |
| Font_InitGlyphFallbackTablesForLanguage | `0x1A6` | 3 | 1077, 1102, 1119 |
| Font_InitGlyphFallbackTablesForLanguage | `0x10` | 3 | 1084, 1109, 1126 |
| Font_InitGlyphFallbackTablesForLanguage | `0x20` | 3 | 1086, 1111, 1128 |
| Font_InitGlyphFallbackTablesForLanguage | `0x28` | 3 | 1087, 1112, 1129 |
| Font_InitGlyphFallbackTablesForLanguage | `0x38` | 3 | 1089, 1114, 1131 |
| Font_InitGlyphFallbackTablesForLanguage | `0x40` | 2 | 1090, 1132 |
| Font_InitGlyphFallbackTablesForLanguage | `0x50` | 2 | 1092, 1134 |
| Font_InitGlyphFallbackTablesForLanguage | `0x58` | 2 | 1093, 1135 |
| Font_InitGlyphFallbackTablesForLanguage | `0x68` | 2 | 1095, 1137 |
| Font_InitGlyphFallbackTablesForLanguage | `0x70` | 2 | 1096, 1138 |
| Font_InitGlyphFallbackTablesForLanguage | `10` | 16 | 1123, 1152, 1164, 1172 ... |
| Font_InitGlyphFallbackTablesForLanguage | `0x2BDu` | 1 | 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0x2BEu` | 1 | 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0x2BFu` | 1 | 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0x2C0u` | 1 | 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0x2C1u` | 1 | 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0x2C2u` | 1 | 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0xBBu` | 2 | 1164, 1164 |
| Font_InitGlyphFallbackTablesForLanguage | `0x303u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x304u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x305u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x306u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x307u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x308u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x309u` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30Au` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0xFFFFu` | 2 | 1166, 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x24u` | 1 | 1168 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30Bu` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30Cu` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30Du` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30Eu` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x30Fu` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x310u` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x311u` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0x312u` | 3 | 1172, 1181, 1186 |
| Font_InitGlyphFallbackTablesForLanguage | `0xFFFEu` | 13 | 1172, 1173, 1174, 1175 ... |
| Font_InitGlyphFallbackTablesForLanguage | `0x313u` | 3 | 1173, 1181, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x314u` | 3 | 1173, 1181, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x315u` | 3 | 1173, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x316u` | 3 | 1173, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x317u` | 3 | 1173, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x318u` | 3 | 1173, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x319u` | 3 | 1173, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x31Au` | 3 | 1173, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x31Bu` | 3 | 1174, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x31Cu` | 3 | 1174, 1182, 1187 |
| Font_InitGlyphFallbackTablesForLanguage | `0x31Du` | 3 | 1174, 1182, 1188 |
| Font_InitGlyphFallbackTablesForLanguage | `0x31Eu` | 3 | 1174, 1182, 1188 |
| Font_InitGlyphFallbackTablesForLanguage | `0x31Fu` | 2 | 1174, 1188 |
| Font_InitGlyphFallbackTablesForLanguage | `0x320u` | 2 | 1174, 1188 |
| Font_InitGlyphFallbackTablesForLanguage | `0x321u` | 2 | 1175, 1188 |
| Font_InitGlyphFallbackTablesForLanguage | `0x322u` | 2 | 1175, 1188 |
| Font_InitGlyphFallbackTablesForLanguage | `0x323u` | 2 | 1175, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x324u` | 2 | 1175, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x325u` | 2 | 1175, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x326u` | 2 | 1175, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x327u` | 2 | 1176, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x328u` | 2 | 1176, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x329u` | 2 | 1176, 1189 |
| Font_InitGlyphFallbackTablesForLanguage | `0x32Au` | 2 | 1176, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x32Bu` | 2 | 1176, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x32Cu` | 2 | 1176, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x32Du` | 2 | 1176, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x32Eu` | 2 | 1177, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x32Fu` | 2 | 1177, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x330u` | 2 | 1177, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x331u` | 2 | 1177, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x332u` | 2 | 1177, 1190 |
| Font_InitGlyphFallbackTablesForLanguage | `0x333u` | 1 | 1190 |
| MiniMap_BuildTileColorTables | `2` | 1 | 1216 |
| MiniMap_BuildTileColorTables | `0x004` | 9 | 1230, 1231, 1241, 1250 ... |
| MiniMap_BuildTileColorTables | `0xB7` | 4 | 1230, 1234, 1241, 1245 |
| MiniMap_BuildTileColorTables | `0x003` | 9 | 1231, 1245, 1246, 1251 ... |
| MiniMap_BuildTileColorTables | `0x97` | 12 | 1231, 1233, 1235, 1242 ... |
| MiniMap_BuildTileColorTables | `0x007` | 3 | 1232, 1252, 1272 |
| MiniMap_BuildTileColorTables | `0x27` | 2 | 1232, 1252 |
| MiniMap_BuildTileColorTables | `0x008` | 9 | 1233, 1233, 1248, 1253 ... |
| MiniMap_BuildTileColorTables | `0x010` | 6 | 1234, 1234, 1254, 1254 ... |
| MiniMap_BuildTileColorTables | `0x00D` | 3 | 1235, 1255, 1275 |
| MiniMap_BuildTileColorTables | `0x020` | 3 | 1235, 1255, 1275 |
| MiniMap_BuildTileColorTables | `0x02D` | 3 | 1236, 1256, 1276 |
| MiniMap_BuildTileColorTables | `0x074` | 3 | 1236, 1256, 1276 |
| MiniMap_BuildTileColorTables | `0xB9` | 2 | 1236, 1256 |
| MiniMap_BuildTileColorTables | `0x019` | 3 | 1237, 1257, 1277 |
| MiniMap_BuildTileColorTables | `0x0A1` | 3 | 1237, 1257, 1277 |
| MiniMap_BuildTileColorTables | `0xCC` | 6 | 1237, 1240, 1257, 1260 ... |
| MiniMap_BuildTileColorTables | `0x024` | 3 | 1238, 1258, 1278 |
| MiniMap_BuildTileColorTables | `0x0BA` | 3 | 1238, 1258, 1278 |
| MiniMap_BuildTileColorTables | `0xCA` | 6 | 1238, 1244, 1258, 1264 ... |
| MiniMap_BuildTileColorTables | `0x0DE` | 3 | 1239, 1259, 1279 |
| MiniMap_BuildTileColorTables | `0x1D6` | 3 | 1239, 1259, 1279 |
| MiniMap_BuildTileColorTables | `0x93` | 9 | 1239, 1243, 1247, 1259 ... |
| MiniMap_BuildTileColorTables | `0x00F` | 3 | 1240, 1260, 1280 |
| MiniMap_BuildTileColorTables | `0x2B4` | 3 | 1240, 1260, 1280 |
| MiniMap_BuildTileColorTables | `0x2C3` | 3 | 1241, 1261, 1281 |
| MiniMap_BuildTileColorTables | `0x005` | 6 | 1242, 1244, 1262, 1264 ... |
| MiniMap_BuildTileColorTables | `0x2C7` | 3 | 1242, 1262, 1282 |
| MiniMap_BuildTileColorTables | `0x01E` | 3 | 1243, 1263, 1283 |
| MiniMap_BuildTileColorTables | `0x2CC` | 3 | 1243, 1263, 1283 |
| MiniMap_BuildTileColorTables | `0x2EA` | 3 | 1244, 1264, 1284 |
| MiniMap_BuildTileColorTables | `0x2EF` | 3 | 1245, 1265, 1285 |
| MiniMap_BuildTileColorTables | `0x2F2` | 3 | 1246, 1266, 1286 |
| MiniMap_BuildTileColorTables | `0x00E` | 3 | 1247, 1267, 1287 |
| MiniMap_BuildTileColorTables | `0x2F5` | 3 | 1247, 1267, 1287 |
| MiniMap_BuildTileColorTables | `0x303` | 3 | 1248, 1268, 1288 |
| MiniMap_BuildTileColorTables | `0x4C` | 4 | 1250, 1254, 1261, 1265 |
| MiniMap_BuildTileColorTables | `0x7F` | 4 | 1270, 1274, 1281, 1285 |
| MiniMap_BuildTileColorTables | `0xC0` | 6 | 1271, 1273, 1275, 1282 ... |
| MiniMap_BuildTileColorTables | `0xC4` | 1 | 1272 |
| MiniMap_BuildTileColorTables | `0x80` | 1 | 1276 |
| MiniMap_CreateSurface | `2` | 1 | 1358 |
| MiniMap_CreateSurface | `2500` | 1 | 1359 |
| MiniMap_CreateSurface | `4` | 2 | 1360, 1370 |
| MiniMap_CreateSurface | `14` | 2 | 1361, 1362 |
| MiniMap_CreateSurface | `16` | 2 | 1363, 1365 |
| MiniMap_CreateSurface | `608` | 1 | 1364 |
| MiniMap_CreateSurface | `188` | 1 | 1365 |
| MiniMap_DestroySurface | `2` | 1 | 1392 |
| MiniMap_BlitDirtyRectAndDrawViewportBox | `7` | 3 | 1431, 1434, 1434 |
| MiniMap_BlitDirtyRectAndDrawViewportBox | `9` | 1 | 1431 |
| MiniMap_BlitDirtyRectAndDrawViewportBox | `6` | 2 | 1432, 1433 |
| MiniMap_BlitDirtyRectAndDrawViewportBox | `0x4Cu` | 1 | 1435 |

### src/world/0040D6D0_0040F4D0_world_004.cpp

Missing evidence: viewport and fog geometry, bitfield units, palette/overlay domains and packed widget/relocation resources. Each row is one raw lexeme/function family; instruction/data cross-references are needed before naming. Trivial0/1 tokens are omitted.

| Function | Literal | Occurrences | Source line(s) |
| --- | --- | ---: | --- |
| MiniMap_RedrawTileRect | `7` | 4 | 55, 56, 57, 58 |
| MiniMap_DrawTileCell | `0xCFu` | 1 | 132 |
| MiniMap_DrawTileCell | `0xFFFF` | 2 | 136, 153 |
| MiniMap_DrawTileCell | `2` | 3 | 136, 139, 154 |
| MiniMap_DrawTileCell | `0x1F4u` | 1 | 142 |
| MiniMap_DrawTileCell | `0x28` | 1 | 143 |
| MiniMap_DrawTileCell | `6` | 3 | 143, 171, 172 |
| MiniMap_DrawTileCell | `720` | 1 | 146 |
| MiniMap_DrawTileCell | `4` | 2 | 147, 150 |
| MiniMap_DrawTileCell | `0x8000` | 1 | 153 |
| MiniMap_DrawTileCell | `7` | 4 | 163, 163, 169, 170 |
| Map_GetTileSurfaceClassOrUnexplored | `0xFFFF` | 1 | 193 |
| Map_GetTileSurfaceClassOrUnexplored | `2` | 1 | 193 |
| Map_GetTileSurfaceClassOrUnexplored | `207` | 1 | 196 |
| MiniMap_UpdateViewportFromCursor | `220` | 2 | 230, 232 |
| MiniMap_UpdateViewportFromCursor | `7` | 3 | 251, 252, 273 |
| MiniMap_UpdateViewportFromCursor | `9` | 1 | 267 |
| MiniMap_ShowAllLayers | `7` | 1 | 332 |
| MiniMap_ShowUnitsOnly | `2` | 1 | 344 |
| MiniMap_ShowBuildingsOnly | `4` | 1 | 356 |
| UI_MenuHitTestEntry | `4` | 2 | 392, 408 |
| UI_MenuHitTestEntry | `3u` | 1 | 394 |
| UI_MenuHitTestEntry | `2` | 4 | 395, 397, 398, 411 |
| UI_MenuHitTestEntry | `5` | 2 | 395, 411 |
| UI_MenuHitTestEntry | `20` | 2 | 399, 419 |
| UI_MenuHitTestEntry | `25` | 1 | 405 |
| UI_MenuHitTestEntry | `22` | 2 | 415, 420 |
| UI_RunMenu | `3u` | 11 | 525, 527, 560, 561 ... |
| UI_RunMenu | `4u` | 4 | 529, 618, 741, 760 |
| UI_RunMenu | `188` | 1 | 531 |
| UI_RunMenu | `3` | 2 | 546, 712 |
| UI_RunMenu | `46` | 5 | 547, 558, 604, 757 ... |
| UI_RunMenu | `52` | 2 | 548, 604 |
| UI_RunMenu | `25` | 1 | 559 |
| UI_RunMenu | `28` | 2 | 563, 762 |
| UI_RunMenu | `19` | 3 | 565, 710, 712 |
| UI_RunMenu | `4` | 3 | 567, 581, 603 |
| UI_RunMenu | `2` | 10 | 570, 572, 573, 598 ... |
| UI_RunMenu | `5` | 6 | 570, 598, 682, 687 ... |
| UI_RunMenu | `20` | 8 | 574, 599, 667, 680 ... |
| UI_RunMenu | `13` | 5 | 583, 667, 693, 724 ... |
| UI_RunMenu | `0xFFFFFF` | 2 | 585, 670 |
| UI_RunMenu | `10395294` | 2 | 590, 675 |
| UI_RunMenu | `22` | 5 | 601, 683, 686, 702 ... |
| UI_RunMenu | `30` | 1 | 657 |
| UI_RunMenu | `40` | 1 | 657 |
| UI_RunMenu | `3342130` | 1 | 697 |
| UI_RunMenu | `15` | 2 | 721, 726 |
| UI_RunMenu | `17` | 1 | 772 |
| WorldMap_HandleTopMenuBar | `640` | 2 | 819, 875 |
| WorldMap_HandleTopMenuBar | `5` | 1 | 820 |
| WorldMap_HandleTopMenuBar | `0x18Fu` | 2 | 830, 917 |
| WorldMap_HandleTopMenuBar | `188` | 1 | 832 |
| WorldMap_HandleTopMenuBar | `400` | 1 | 834 |
| WorldMap_HandleTopMenuBar | `3` | 2 | 838, 853 |
| WorldMap_HandleTopMenuBar | `0x20` | 1 | 849 |
| WorldMap_HandleTopMenuBar | `2` | 6 | 850, 854, 856, 858 ... |
| WorldMap_HandleTopMenuBar | `76` | 1 | 851 |
| WorldMap_HandleTopMenuBar | `13` | 1 | 853 |
| WorldMap_HandleTopMenuBar | `10` | 1 | 854 |
| WorldMap_HandleTopMenuBar | `11` | 3 | 854, 856, 858 |
| WorldMap_HandleTopMenuBar | `585` | 2 | 854, 856 |
| WorldMap_HandleTopMenuBar | `14` | 1 | 855 |
| WorldMap_HandleTopMenuBar | `4` | 1 | 855 |
| WorldMap_HandleTopMenuBar | `20` | 1 | 856 |
| WorldMap_HandleTopMenuBar | `570` | 1 | 858 |
| WorldMap_HandleTopMenuBar | `0x23u` | 1 | 869 |
| WorldMap_HandleTopMenuBar | `0x27Fu` | 1 | 869 |
| WorldMap_HandleTopMenuBar | `25` | 2 | 876, 904 |
| WorldMap_HandleTopMenuBar | `430` | 1 | 900 |
| WorldMap_HandleTopMenuBar | `470` | 1 | 900 |
| WorldMap_HandleTopMenuBar | `590` | 1 | 903 |
| WorldMapTopMenu_LoadSpriteSet | `4112` | 1 | 956 |
| UI_MenuEntry_Enable | `26` | 1 | 984 |
| UI_MenuEntry_Enable | `40` | 1 | 984 |
| UI_MenuEntry_Disable | `26` | 1 | 994 |
| UI_MenuEntry_Disable | `40` | 1 | 994 |
| Map_RevealAllTilesForPlayer | `100` | 1 | 1011 |
| Map_RevealAllTilesForPlayer | `3` | 2 | 1013, 1013 |
| Map_RevealAllTilesForPlayer | `31` | 2 | 1013, 1013 |
| Map_RevealAllTilesForPlayer | `8` | 1 | 1013 |
| Map_RevealAllTilesForPlayer | `7` | 1 | 1014 |
| Map_RevealAllTilesForPlayer | `13` | 1 | 1017 |
| Map_RevealAllTilesForPlayer | `1300` | 1 | 1019 |
| Map_RevealTileWithPropagation | `3` | 2 | 1038, 1038 |
| Map_RevealTileWithPropagation | `31` | 2 | 1038, 1038 |
| Map_RevealTileWithPropagation | `8` | 1 | 1038 |
| Map_RevealTileWithPropagation | `7` | 1 | 1039 |
| Map_RevealTileWithPropagation | `2` | 12 | 1041, 1043, 1045, 1047 ... |
| Map_IsTileVisibleToPlayer | `7` | 1 | 1072 |
| Map_IsTileVisibleToPlayer | `3` | 2 | 1074, 1074 |
| Map_IsTileVisibleToPlayer | `31` | 2 | 1074, 1074 |
| Map_IsTileVisibleToPlayer | `8` | 1 | 1074 |
| Map_ClassifyFogOfWarOverlayForPlayer | `7` | 2 | 1087, 1108 |
| Map_ClassifyFogOfWarOverlayForPlayer | `6` | 2 | 1088, 1120 |
| Map_ClassifyFogOfWarOverlayForPlayer | `5` | 2 | 1089, 1112 |
| Map_ClassifyFogOfWarOverlayForPlayer | `4` | 3 | 1090, 1103, 1110 |
| Map_ClassifyFogOfWarOverlayForPlayer | `3` | 2 | 1091, 1118 |
| Map_ClassifyFogOfWarOverlayForPlayer | `2` | 3 | 1092, 1107, 1114 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x5A` | 4 | 1099, 1101, 1103, 1105 |
| Map_ClassifyFogOfWarOverlayForPlayer | `12` | 1 | 1100 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x80` | 1 | 1101 |
| Map_ClassifyFogOfWarOverlayForPlayer | `9` | 1 | 1102 |
| Map_ClassifyFogOfWarOverlayForPlayer | `11` | 1 | 1104 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x20` | 1 | 1105 |
| Map_ClassifyFogOfWarOverlayForPlayer | `10` | 1 | 1106 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x58` | 1 | 1107 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x10` | 1 | 1109 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x4A` | 1 | 1109 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x52` | 1 | 1111 |
| Map_ClassifyFogOfWarOverlayForPlayer | `8` | 2 | 1111, 1122 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x1A` | 1 | 1113 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x40` | 1 | 1113 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x50` | 3 | 1115, 1115, 1121 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0xA` | 3 | 1115, 1121, 1121 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x12` | 3 | 1117, 1119, 1119 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x48` | 3 | 1117, 1117, 1119 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x18` | 2 | 1123, 1123 |
| Map_ClassifyFogOfWarOverlayForPlayer | `0x42` | 2 | 1123, 1123 |
| Map_ClassifyFogOfWarOverlayForPlayer | `255` | 1 | 1126 |
| Map_ClassifyFogOfWarOverlayForPlayer | `13` | 1 | 1127 |
| Map_ClassifyFogOfWarOverlayForPlayer | `14` | 1 | 1128 |
| UnitStack_IsIndexOnMap | `2` | 1 | 1145 |
| UnitStack_IsIndexOnMap | `200` | 1 | 1149 |
| UnitSlot_InitFromType | `4` | 1 | 1170 |
| UnitSlot_InitFromType | `6` | 2 | 1171, 1182 |
| UnitSlot_InitFromType | `3` | 1 | 1172 |
| UnitSlot_InitFromType | `23` | 1 | 1173 |
| UnitSlot_InitFromType | `100` | 1 | 1178 |
| UnitSlot_InitFromType | `2` | 1 | 1181 |
| UnitSlot_InitFromType | `10` | 1 | 1184 |
| UnitSlot_InitFromType | `17` | 2 | 1190, 1193 |
| UnitSlot_InitFromType | `0x80` | 1 | 1191 |
| UnitSlot_InitFromType | `0xF8` | 1 | 1193 |
| UnitSlot_InitFromType | `0xFE` | 1 | 1195 |
| UnitSlot_InitFromType | `0xF0` | 1 | 1196 |
