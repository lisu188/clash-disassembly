# Unit Types and Stats Report

## 1. Overview
- **Analyzed artifacts:** `clash95.c`, `clash95.asm`, `clash95.map`, and `clash95.exe`.
- **Primary reconstruction path:** the 88-byte `unit_stats` record family at `off_512568` / `unit_stats` in the data segment. `clash95.asm` exposes per-record xrefs to both the localized-name pointers and sprite-folder pointers, while `clash95.exe` confirms the folder stems as raw strings.
- **Reliability rule used here:** names and ids are only promoted when at least two independent signals align. Folder order alone was treated as insufficient after the asm pass exposed duplicated localized-name pointers for the final special prisoner records.

## 2. Recovered Unit Roster

### 2.1 Full Roster
| type_id | recovered_name | folder | confidence | evidence summary |
| --- | --- | --- | --- | --- |
| `0` | `UnitType0_Peasant` | `peon` | high | The first `unit_stats` record pairs `Posp. ruszenie / Peasant / Bauern` with `peon`. |
| `1` | `UnitType1_LightInfantry` | `infl` | high | `off_5123F0` (`Lekka piechota / Light infantry`) and `infl` share the same record xrefs. |
| `2` | `UnitType2_HeavyInfantry` | `infh` | high | `off_5123FC` (`Ciężka piechota / Heavy infantry`) resolves to the `infh` folder record. |
| `3` | `UnitType3_Pikeman` | `sprl` | high | `off_512438` (`Pikinier / Pikeman`) and `sprl` resolve to the same 88-byte record. |
| `4` | `UnitType4_HeavySpearman` | `sprh` | high | `off_51242C` (`Halabardnik / Heavy spearman`) pairs with `sprh`. |
| `5` | `UnitType5_LightCavalry` | `cavl` | high | `off_51248C` (`Lekka jazda / Light cavalry`) pairs with `cavl`. |
| `6` | `UnitType6_HeavyCavalry` | `cavh` | high | `off_512498` (`Ciężka jazda / Heavy cavalry`) pairs with `cavh`. |
| `7` | `UnitType7_Knights` | `ryc` | high | `off_5124A4` (`Rycerstwo / Knights`) resolves to `ryc`. |
| `8` | `UnitType8_DragonCavalry` | `drag` | high | `off_5124B0` (`Dragon / Dragon cavalry`) resolves to `drag`. |
| `9` | `UnitType9_Archer` | `arch` | high | `off_5123D8` (`Łucznik / Archer`) resolves to `arch`. |
| `10` | `UnitType10_Crossbower` | `kusza` | high | `off_512414` (`Kusznik / Crossbower`) resolves to `kusza`. |
| `11` | `UnitType11_Musketeer` | `muszk` | high | `off_512420` (`Muszkieter / Musketeer`) resolves to `muszk`. |
| `12` | `UnitType12_Catapult` | `katap` | high | `off_512408` (`Katapulta / Catapult`) resolves to `katap`. |
| `13` | `UnitType13_Ram` | `taran` | high | `off_512468` (`Taran / Rammbock`) resolves to `taran`; ordinary melee code also excludes type `13`. |
| `14` | `UnitType14_Cannon` | `armat` | high | `off_512444` (`Armata / Cannon`) resolves to `armat`. |
| `15` | `UnitType15_Forester` | `lesn` | high | `off_512450` (`Leśnik / Forester`) resolves to `lesn`. |
| `16` | `UnitType16_Goral` | `goral` | high | `off_5123E4` (`Góral / Highlander`) resolves to `goral`. |
| `17` | `UnitType17_Builder` | `budow` | high | `off_51245C` (`Budowniczy / Builder`) resolves to `budow`. |
| `18` | `UnitType18_Worm` | `worm` | high | `off_5124BC` (`Czerw / Worm`) resolves to `worm`. |
| `19` | `UnitType19_Elephant` | `slon` | high | `off_5124C8` (`Słoń / Elephant`) resolves to `slon`. |
| `20` | `UnitType20_Cyclop` | `cykl` | high | `off_5124D4` (`Cyklop / Cyclop`) resolves to `cykl`. |
| `21` | `UnitType21_Troll` | `trol` | high | `off_5124E0` (`Troll`) resolves to `trol`. |
| `22` | `UnitType22_Scorpion` | `scorp` | high | `off_5124EC` (`Skorpion / Scorpion`) resolves to `scorp`. |
| `23` | `UnitType23_Skeleton` | `szk` | high | `off_5124F8` (`Szkielet / Skeleton`) resolves to `szk`. |
| `24` | `UnitType24_Wizard` | `mag` | high | `off_512504` (`Mag / Wizard`) resolves to `mag`. |
| `25` | `UnitType25_Ghost` | `duch` | high | `off_512510` (`Duch / Ghost`) resolves to `duch`. |
| `26` | `UnitType26_Eagle` | `orzel` | high | `off_51251C` (`Orzeł / Eagle`) resolves to `orzel`. |
| `27` | `UnitType27_Pegasus` | `pegaz` | high | `off_512474` (`Pegaz / Pegasus`) resolves to `pegaz`. |
| `28` | `UnitType28_Winger` | `skrz` | high | `off_512528` (`Skrzydlak / Winger`) resolves to `skrz`. |
| `29` | `UnitType29_Fly` | `wazka` | high | `off_512534` (`Ważka / Fly / Riesenlibelle`) resolves to `wazka`. |
| `30` | `UnitType30_Dragon` | `smok` | high | `off_512480` (`Smok / Dragon / Drachen`) resolves to `smok`. |
| `31` | `UnitType31_GoldCargo` | `gold` | high | `off_512540` (`Złoto / Gold`) resolves to `gold`, and stack-action helpers treat type `31` as non-combat cargo excluded from the normal-unit predicate. |
| `32` | `UnitType32_PeasantCargo` | `peas` | high | `off_51254C` (`Chłopi / Peasants`) resolves to `peas`, and capture/building helpers merge and normalize type `32` as transferable peasant cargo rather than an ordinary combat slot. |
| `33` | `UnitType33_SpecialFootPersonage` | `specm` | medium | This record reuses `off_512558` (`Dowódca / Tactician / Soldat`), keeps infantry-like movement assets, enters the prisoner pipeline on capture, and is also instantiated by `Queen_NewTurn` through `Building_CreateSpecialPersonageGarrisonUnit` during the royal birth event. The `specm` code name and the shared commander-like label both argue for a broader special-personage role rather than a prisoner-only one. |
| `34` | `UnitType34_SpecialMountedPersonage` | `speck` | medium | This record reuses the same localized-name triplet, switches to mounted movement assets, participates in the same prisoner pipeline as type `33`, and is also emitted by the queen birth path as the alternate royal special entry. The `speck` code name plus the daughter-birth text about becoming an officer reinforces the same shared special-personage family. |

### 2.2 Recovered Categories
| recovered_name | confidence | kind | evidence summary | where found | related |
| --- | --- | --- | --- | --- | --- |
| `RangedUnitCategory` | high | category | Units with non-zero `g_UnitTypeMaxRange` execute projectile logic and use the ranged stat helpers. | `clash95.c:39839-39866`, `clash95.c:49182-49270` | `base_ranged_attack`, `attack_range_max`, `attack_range_min` |
| `FlyingUnitCategory` | high | category | `g_UnitTypeFlags` bit0 marks airborne units. They render in the post-ground pass, use airborne movement-sound variants, and satisfy `UnitStack_HasOnlyFlyingUnits`. | `clash95.c:27660-27690`, `clash95.c:36171-36190`, `clash95.c:39530-39590`, `clash95.c:44795-44910`, `clash95.c:56958-57358` | `UnitType26_Eagle`, `UnitType27_Pegasus`, `UnitType28_Winger`, `UnitType29_Fly`, `UnitType30_Dragon` |
| `GroundUnitCategory` | medium | category | Non-airborne units with non-zero melee stats use ordinary terrain/surface-dependent movement sounds and the normal melee path. | `clash95.c:22124-22145`, `clash95.c:39680-39760`, `clash95.c:56958-57358` | standard infantry, cavalry, siege, and utility units |
| `LightUnitCategory` | high | category | `g_UnitTypeFlags` bit1 selects the 6-point morale seed instead of the default 10-point seed. | `clash95.c:22188-22196`, `clash95.c:32986-32991` | `morale` |
| `SpecialCargoEntryCategory` | high | category | Types `31` and `32` are excluded by `UnitStack_HasNormalCombatUnits`, transferred separately during capture, and are used by gold/peasant-specific UI and economy logic. | `clash95.c:24216-24303`, `clash95.c:30685-30854`, `clash95.c:53970-53975` | `UnitType31_GoldCargo`, `UnitType32_PeasantCargo` |
| `SpecialPersonageCategory` | high | category | Types `33` and `34` are non-standard special personage entries: capture logic routes them through the prisoner pipeline, while `Queen_NewTurn` also creates the same ids directly inside building garrisons during the birth event. The supporting gameplay predicates are now named `UnitStack_HasSpecialPersonageUnits`, `Building_CountSpecialPersonageGarrisonEntries`, and `Building_HasSpecialPersonageGarrisonEntries`, which matches the broader family semantics. | `clash95.c:24393-24472`, `clash95.c:64324-64424`, `clash95.c:65195-65274`, `clash95.asm:118318`, `clash95.asm:121676-121682`, `clash95.exe` strings `specm` / `speck` / `Queen_NewTurn() - nowy potomek` | `UnitType33_SpecialFootPersonage`, `UnitType34_SpecialMountedPersonage` |

## 3. Recovered Stats
| recovered_name | confidence | semantic meaning | evidence summary | locations | stat_kind | used_by |
| --- | --- | --- | --- | --- | --- | --- |
| `base_action_points` | high | Per-type maximum action-point budget before fatigue penalties. | Stored in `g_UnitTypeBaseActionPoints`, copied into slot `+8`, and used by `UnitSlot_CalcActionPointsFromFatigue`. | `clash95.c:22183-22205`, `clash95.c:22585-22613` | base stat | most field units |
| `current_action_points` | high | Runtime action points available to the slot this turn. | Lives at UnitSlotRecord `+8` and is refreshed each new turn from the base AP table after fatigue thresholds are applied. | `clash95.c:22558-22575`, `clash95.c:23821-23826` | current stat | most field units |
| `current_health_percent` | high | Runtime health or squad-strength percentage. | Always initialized to `100`, then multiplied into effective attack and damage formulas; zero kills the slot. | `clash95.c:22185-22196`, `clash95.c:23446-23506`, `clash95.c:39790-39810` | current modifier | all field units |
| `fatigue` | high | Runtime exhaustion counter that throttles action points and morale. | Lives at UnitSlotRecord `+10`; thresholds at `80/90/100` reduce action points and severe fatigue lowers morale each new turn. | `clash95.c:22558-22575`, `clash95.c:23768-23837`, `clash95.c:24669-24723` | current modifier | all field units |
| `morale` | high | Runtime `0..20` morale or obedience score that boosts combat stats and can cause order refusal. | Seeded to `6` or `10`, clamped to `0..20`, added by the attack/damage helpers, and checked by `Unit_CheckLowMorale`. | `clash95.c:22188-22205`, `clash95.c:23446-23506`, `clash95.c:23623-23718`, `clash95.c:24759-24823` | current modifier | all field units |
| `stance_bits` | medium | Runtime formation or stance selector used by both combat and garrison helpers. | The low two bits of slot `+12` are added directly into melee, ranged, and siege attack helpers; the full byte is cycled by `Building_UseGarrisonSlot`. | `clash95.c:23446-23506`, `clash95.c:24828-24857` | current modifier | field and garrison units |
| `base_melee_attack` | high | Core melee attack rating. | Non-zero values gate standard melee and feed `UnitStats_CalcEffectiveMeleeAttack`. | `clash95.c:23446-23460`, `clash95.c:39716-39760` | base stat | melee-capable units |
| `base_ranged_attack` | medium | Per-type projectile attack rating. | Stored in `g_UnitTypeBaseRangedAttack` and consumed by `UnitStats_CalcEffectiveRangedAttack`, but the original designer-facing label is still absent. | `clash95.c:23465-23482`, `clash95.c:40447-40513` | base stat | ranged-capable units |
| `base_damage` | high | Raw per-hit damage value before health scaling. | Read by `UnitStats_CalcEffectiveDamagePerHit` and `UnitStats_GetBaseDamage`. | `clash95.c:23487-23494` | base stat | combat resolution |
| `base_siege_attack` | medium | Alternate attack value used in siege or structure-damage contexts. | `UnitStats_CalcEffectiveSiegeAttack` switches to `g_UnitTypeBaseSiegeAttack` for the alternate context. | `clash95.c:23498-23506` | base stat | siege or anti-building cases |
| `road_move_cost` | high | Move cost on road or bridge overlays. | Returned when the tile record carries a road/bridge overlay. | `clash95.c:41380-41410` | base stat | world movement |
| `terrain_move_cost` | high | Terrain-dependent move cost. | Combined with `g_TerrainMoveTableOffsets` by world movement helpers. | `clash95.c:41380-41420`, `clash95.c:413B10-41405` | base stat | world movement |
| `unit_type_flags` | high | Bitfield inside the 88-byte metadata record. | Bit0 is airborne; another bit still controls the light-unit seed path. | `clash95.c:22133-22144`, `clash95.c:27660-27690`, `clash95.c:36171-36190`, `clash95.c:39530-39590`, `clash95.c:44795-44910`, `clash95.c:56958-57358` | modifier | all unit types |
| `attack_range_max` | high | Maximum squared projectile range. | Projectile logic rejects shots beyond this value. | `clash95.c:39803-39820`, `clash95.c:42779-42865` | base stat | ranged units |
| `attack_range_min` | medium | Minimum squared projectile range or dead-zone floor. | Projectile logic also rejects shots inside this lower bound. | `clash95.c:39803-39820` | base stat | ranged units with dead zones |
| `move_pixel_speed` | medium | Per-frame displacement during movement animation. | Movement loops multiply direction vectors by `byte_512570`. | `clash95.c:38680-38720`, `clash95.c:39240-39330` | base stat | mobile units |
| `move_tick_delay` | medium | Delay between movement animation ticks. | `Time_Now` gates animation advancement with `byte_512571`. | `clash95.c:38632-38705` | modifier | mobile units |
| `death_animation_frames` | medium | Number of frames in the death effect. | Copied into the battle death-loop state. | `clash95.c:39260-39320` | base stat | units with animated deaths |
| `death_frame_interval` | medium | Delay between death-animation frames. | Used by the same death loop that advances the effect frame counter. | `clash95.c:39290-39320` | modifier | units with animated deaths |
| `move_sound_stem` | high | Per-unit movement-sound stem inside the metadata record. | `Audio_PlayWorldMapUnitMoveSound` and `Audio_PlayBattleMapUnitMoveSound` build `sfx\\ruchy\\<stem>...` paths from the field at offset `+81`. | `clash95.c:56958-57358`, `clash95.asm:101018-101218`, `clash95.asm:409554-409562` | base stat | all moving units |
| `move_sound_variant_count` | high | Number of alternating step samples per unit type. | The current step variant wraps modulo `g_UnitMoveSoundVariantCounts[88 * type]`. | `clash95.c:57103-57104`, `clash95.c:57331-57332`, `clash95.asm:101212-101218`, `clash95.asm:101564-101570` | base stat | step-based movers |
| `move_sound_base_volume` | high | Default volume used when playing movement sounds. | Both movement-sound helpers pass `g_UnitMoveSoundBaseVolumes[88 * type]` into `CSS_PlaySound`. | `clash95.c:57103`, `clash95.c:57139`, `clash95.c:57234`, `clash95.c:57331`, `clash95.asm:101067`, `clash95.asm:101419` | base stat | all moving units |

## 4. Type-to-Stat Relationships
| unit_type | stat | relationship | confidence | evidence |
| --- | --- | --- | --- | --- |
| `UnitType13_Ram` | `action_points`, `base_melee_attack` | Standard melee handlers reject type `13`, so its primary interaction path is not the ordinary melee routine despite sharing generic unit-slot state. | high | `clash95.c:39688`, `clash95.c:49195` |
| `UnitType29_Fly` | `move_sound_stem` | Type `29` is one of the looped non-footstep movers, grouped with siege engines in both world and battle movement audio. | high | `clash95.c:56992`, `clash95.c:57200` |
| `UnitType30_Dragon` | `unit_type_flags` | Type `30` resolves to `smok` and belongs to the airborne class governed by `g_UnitTypeFlags` bit0. | high | `clash95.asm:409287-409426`, `clash95.c:44795-44910`, `clash95.c:56958-57358` |
| `UnitType33_SpecialFootPersonage` | `localized_name_ptrs` | Type `33` shares the `Dowódca / Tactician / Soldat` localized-name triplet, is handled as a capturable special entry in the prisoner pipeline, and is also created by the queen birth event. | high | `clash95.c:24393-24472`, `clash95.c:64324-64424`, `clash95.c:65195-65274`, `clash95.asm:385244-385246`, `clash95.asm:409419-409423`, `clash95.exe` |
| `UnitType34_SpecialMountedPersonage` | `localized_name_ptrs` | Type `34` is the mounted sibling of type `33`; it shares the same localized-name triplet, follows the prisoner workflow when captured, and is also emitted by the queen birth path. | high | `clash95.c:24393-24472`, `clash95.c:64324-64424`, `clash95.c:65195-65274`, `clash95.asm:412173-412174`, `clash95.exe` |
| `RangedUnitCategory` | `base_ranged_attack`, `base_damage`, `attack_range_max`, `attack_range_min` | Projectile units use `g_UnitTypeBaseRangedAttack`, `g_UnitTypeBaseDamage`, `g_UnitTypeMaxRange`, and `g_UnitTypeMinRange` together. | high | `clash95.c:39839-39866`, `clash95.c:40447-40513` |
| `FlyingUnitCategory` | `unit_type_flags`, `move_sound_stem` | Airborne units are identified by bit0 and use single-digit airborne movement-sound suffixes instead of terrain-surface suffixes. | high | `clash95.c:57018-57025`, `clash95.c:57273-57282` |
| `LightUnitCategory` | `morale` | Light units seed at `6` rather than `10`, proving that the bit1 class split affects starting morale rather than a hidden veterancy counter. | high | `clash95.c:22188-22196`, `clash95.c:32986-32991` |

## 5. Ambiguous Findings
- `UnitType33_SpecialFootPersonage` and `UnitType34_SpecialMountedPersonage` are still only medium-confidence names. The recovered code now proves these ids are not prisoner-only because `Queen_NewTurn` also creates them, and the `specm` / `speck` code names plus the officer-flavored birth text narrow the family further, but the exact original designer-facing label behind `Dowódca / Tactician / Soldat` remains inconsistent across languages.
- `UnitType31_GoldCargo` and `UnitType32_PeasantCargo` are behaviorally secure as cargo-style special entries, but the exact original distinction between stack payload and ordinary recruitable peasant units is still partly unresolved from code alone.
- `g_UnitTypeBaseRangedAttack` remains only medium-confidence as a pure ranged-attack stat. It behaves like a second attack value, but the code does not yet expose a canonical gameplay label.
- `g_UnitTypeBaseSiegeAttack` still looks like an alternate damage table for buildings or fortifications, but the exact original design label remains unresolved.
- UnitSlotRecord `+12` is clearly a stance/formation byte, but its upper subfields are still only partially recovered.
- UnitSlotRecord `+13` bit `0x8` appears on special-entry and cargo-related flows, but its full gameplay meaning is still unresolved.
- The decompiler’s `char *(*...)[102]` type on `g_UnitTypeMetadataRecords` is misleading if read literally as “34 unit types x 3 languages.” The asm/xref pass shows at least 35 record slots, with the final two special prisoner records reusing one localized-name pointer triplet.
