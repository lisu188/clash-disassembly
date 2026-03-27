# Unit Types and Stats Report

## 1. Overview
- **Analyzed artifacts:** `clash95.c`, `clash95.asm`, `clash95.map`, and `clash95.exe`.
- **Primary reconstruction path:** the 88-byte `unit_stats` record family at `off_512568` / `unit_stats` in the data segment. `clash95.asm` exposes per-record xrefs to both the localized-name pointers and sprite-folder pointers, while `clash95.exe` confirms the folder stems as raw strings.
- **Reliability rule used here:** names and ids are only promoted when at least two independent signals align. Folder order alone was treated as insufficient after the asm pass exposed duplicated localized-name pointers for the final commander records.

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
| `31` | `UnitType31_Gold` | `gold` | high | `off_512540` (`Złoto / Gold`) resolves to `gold`. |
| `32` | `UnitType32_Peasants` | `peas` | high | `off_51254C` (`Chłopi / Peasants`) resolves to `peas`. |
| `33` | `UnitType33_TacticianFootVariant` | `specm` | medium | This record reuses `off_512558` (`Dowódca / Tactician / Soldat`) but carries infantry-like movement assets such as `b_lekkie\\krokb`. |
| `34` | `UnitType34_TacticianMountedVariant` | `speck` | medium | This record also reuses `off_512558`, but its movement assets switch to cavalry-like stems, suggesting a mounted commander variant. |

### 2.2 Recovered Categories
| recovered_name | confidence | kind | evidence summary | where found | related |
| --- | --- | --- | --- | --- | --- |
| `RangedUnitCategory` | high | category | Units with non-zero `byte_512582` execute projectile logic and use the ranged stat helpers. | `clash95.c:39803-39820`, `clash95.c:49182-49270` | `base_secondary_attack`, `attack_range_max`, `attack_range_min` |
| `FlyingUnitCategory` | high | category | `g_UnitTypeFlags` bit0 marks airborne units. They render in the post-ground pass, use airborne movement-sound variants, and satisfy `UnitStack_HasOnlyFlyingUnits`. | `clash95.c:27660-27690`, `clash95.c:36171-36190`, `clash95.c:39530-39590`, `clash95.c:44795-44910`, `clash95.c:56958-57358` | `UnitType26_Eagle`, `UnitType27_Pegasus`, `UnitType28_Winger`, `UnitType29_Fly`, `UnitType30_Dragon` |
| `GroundUnitCategory` | medium | category | Non-airborne units with non-zero melee stats use ordinary terrain/surface-dependent movement sounds and the normal melee path. | `clash95.c:22124-22145`, `clash95.c:39680-39760`, `clash95.c:56958-57358` | standard infantry, cavalry, siege, and utility units |
| `LightUnitCategory` | high | category | `g_UnitTypeFlags` bit1 selects the 6-point veterancy seed instead of the default 10-point seed. | `clash95.c:22133-22144`, `clash95.c:32950-32970` | `veterancy` |

## 3. Recovered Stats
| recovered_name | confidence | semantic meaning | evidence summary | locations | stat_kind | used_by |
| --- | --- | --- | --- | --- | --- | --- |
| `action_points` | high | Per-turn stamina or readiness budget used by attacks and movement logic. | Seeded in `UnitSlot_InitFromType`, consumed by ordinary melee. | `clash95.c:22124-22145`, `clash95.c:39680-39760` | base/current | most field units |
| `morale_percent` | high | Percentage multiplier applied to combat stats. | Always initialized to `100`, then used in all attack/damage formulas. | `clash95.c:22131-22135`, `clash95.c:23438-23460` | current modifier | all field units |
| `veterancy` | high | Experience or training bonus added before morale scaling. | Seeded to `6` or `10` based on `g_UnitTypeFlags` bit1 and consumed by attack helpers. | `clash95.c:22135-22144`, `clash95.c:23404-23460` | current modifier | all field units |
| `base_melee_attack` | high | Core melee attack rating. | Non-zero values gate standard melee and feed `UnitStats_CalcMeleeAttack`. | `clash95.c:23404-23418`, `clash95.c:39680-39760` | base stat | melee-capable units |
| `base_secondary_attack` | medium | Secondary attack value, strongly associated with ranged/projectile strength. | Used by ranged damage and retaliation-like calculations, but still lacks an explicit label. | `clash95.c:23419-23434`, `clash95.c:40440-40465` | base stat | ranged-capable units |
| `base_damage_scalar` | medium | Raw damage scalar before morale/veterancy scaling. | Read by `UnitStats_CalcDamagePerHit` and `UnitStats_GetBaseDamage`. | `clash95.c:23438-23448` | base stat | combat resolution |
| `structure_damage_scalar` | medium | Alternate damage scalar used in building or fortification contexts. | `UnitStats_CalcSiegeAttack` switches to `byte_512584` for the alternate context. | `clash95.c:23456-23466` | base stat | siege or anti-building cases |
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
| `RangedUnitCategory` | `base_secondary_attack`, `base_damage_scalar`, `attack_range_max`, `attack_range_min` | Projectile units use `byte_51257F`, `byte_512581`, `byte_512582`, and `byte_512583` together. | high | `clash95.c:39803-39820`, `clash95.c:40440-40465` |
| `FlyingUnitCategory` | `unit_type_flags`, `move_sound_stem` | Airborne units are identified by bit0 and use single-digit airborne movement-sound suffixes instead of terrain-surface suffixes. | high | `clash95.c:57018-57025`, `clash95.c:57273-57282` |
| `LightUnitCategory` | `veterancy` | Light units seed at `6` rather than `10`. | high | `clash95.c:22135-22144`, `clash95.c:32950-32970` |

## 5. Ambiguous Findings
- `UnitType33_TacticianFootVariant` and `UnitType34_TacticianMountedVariant` are still medium-confidence recovered names. The folder stems and movement-sound families diverge, but both records reuse the same localized-name pointer triplet.
- `byte_51257F` remains only medium-confidence as a pure ranged-attack stat. It behaves like a second attack value, but the code does not yet expose a canonical gameplay label.
- `byte_512584` still looks like an alternate damage table for buildings or fortifications, but the exact original design label remains unresolved.
- The decompiler’s `char *(*...)[102]` type on `g_UnitTypeMetadataRecords` is misleading if read literally as “34 unit types x 3 languages.” The asm/xref pass shows at least 35 record slots, with the final two commander records reusing one localized-name pointer triplet.
