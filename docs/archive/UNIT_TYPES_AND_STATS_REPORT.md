# Unit Types and Stats Report

## 1. Overview
- **Analyzed artifacts:** `clash95.c`, `clash95.asm`, `clash95.map`, and `clash95.exe`.
- **Primary reconstruction path:** the 88-byte unit metadata record family at `off_512568` in the data segment; the public symbol `unit_stats` names its casualty-weight byte at +87. `clash95.asm` exposes per-record xrefs to both the localized-name tables and resource-key pointers, while `clash95.exe` confirms the raw asset stems.
- **Reliability rule used here:** names and ids are only promoted when at least two independent signals align. Resource-key order alone was treated as insufficient after the asm pass exposed duplicated localized-name tables for the final special prisoner records.
- **2026-06-15 maintenance note:** the documentation-tree consolidation batch did not promote new unit, category, stat, or relationship semantics. It moved this report under `docs/archive/` and added current metadata navigation in `docs/STRUCTURES.md`.
- **2026-06-15 maintenance note:** the mission-04 post-breach probe batch did not promote new unit, category, stat, or relationship semantics. It only split minimap diagnostics and added quarantined route evidence for movement through the already breached gate.
- **2026-06-15 maintenance note:** the mission-04 gate-breach batch did not promote new unit, category, stat, or relationship semantics. It repaired the strided wall-factor table consumed alongside the already recovered `UnitStats_CalcEffectiveWallAttack` path, moving route evidence from first gate hit to active-gate breach.
- **2026-06-15 maintenance note:** the soak-harness and route-frame-sampling batch did not promote new unit, category, stat, or relationship semantics. It only adds opt-in endurance evidence capture around already recovered executable/menu/world-map/castle-economy/first-mission-attack/campaign-route behavior.
- **2026-06-15 maintenance note:** mission-04 wall-attack diagnostics exercised the already recovered wall-attack stat path but did not promote new unit, category, stat, or relationship semantics. The observed light-infantry gate hit is route evidence, not a roster/stat reinterpretation.
- **2026-06-15 maintenance note:** the route-regression and artifact-retention batch did not promote new unit, category, stat, or relationship semantics. The first-mission playability and castle/economy probes exercise already recovered stack, slot, building, and UI paths.
- **2026-07-14 metadata-core recovery:** the reconstruction's one-element `byte_512570+` placeholders were not valid stand-ins for the original strided globals. Direct PE initialized-data extraction restored record offsets `+8..+37` for all 35 unit types. The exact rows are recorded in `UNIT_TYPES_AND_STATS.json`; no values from the unrecovered `+38..+87` tail were inferred.

## 2026-09-05: Tactical slot fields and icon consumers

Track: Win95 reconstruction supporting mission-05 tactical panels. Recovered
`BattleUnitEntry.fatigue` at +10 and `morale` at +11 with high confidence.
`Battle_PlaceUnit` copies all 31 source bytes (assembly 77092..77097), and
`HandleBattleResults` copies the complete survivor payload back
(71327..71335 and 71378..71383). Independent panel loads sign-extend morale
at 75483 and fatigue at 75501. The packed record retains its 31-byte size;
the generated catalog now has 21 structures and 181 size/offset assertions.

The selected panel's status, order and volley expressions and both icon-index
helpers previously passed a short pointer to byte-offset macros, advancing to
+24 instead of +12. Typed slot fields restore the actual stance byte. The icon
helpers also use typed unit metadata and retain the original signed morale
division. Their independent assembly evidence is at 25913..25924 and
26014..26025. No formulas, unit ids, names or enum meanings were invented.
The regression deliberately varies byte +24 independently and checks signed
morale, so it detects the former address error rather than merely covering it.

Both compiler profiles compile/link and pass their four asset-free gates.
Generated metadata, struct headers and subsystem/TU include freshness pass.
These recorded checks precede a concurrently appearing consumer shared-state
header rollout, whose files are preserved and require their own validation.
The final unit run has 1058 passed, zero assertion failures and 530 isolated
crashes. Coverage is 6144/6649 lines (92.40%) across all 718 frozen functions,
with none uncovered. The crash count matches the prior run, but the set gains
`cov5_02_crtbeginthread.normal_call_exercises_reachable_lines` and loses
`cov20_crt.tz_year_starts_label6_a1_flag_set`; both existing cases are outside
the changed unit consumers. This variation is retained for investigation.
The initial packed-fixture alignment build failure remains retained;
the fixture now provides explicitly aligned backing storage.

The engine wrote a private mission05 turn1 DAT/FAC snapshot through `saveGame`.
Original Wine loaded those exact bytes through the normal Load menu and reached
the opening mission banner. This provides authentic diagnostic state, not
Campaign-menu progression. The current reconstruction's initial world probe
passes, but the tactical replay stops on turn 2 after a missed Next Unit click.
No tactical panel equivalence or campaign promotion is claimed. The matching
reconstruction opening-banner probes captured no presented frames; the loaded
original banner cannot be compared as the same modal state with the successful
initial-world capture.

Deferred: battle bytes +13..+16 and +23..+30, stance bit 7, metadata +38..+69,
the type-40 scoring boundary, the omitted battle text-surface blend and the
unit-info wrapper/pane pointer and render defects. Full-payload copies alone
do not establish new bit meanings. The audit checked 100 canonical C lines
matching `UNIT_SLOT_`; it does not claim all recovered pointer arithmetic safe.
Evidence and commands: `artifacts/structure-recovery/tactical-validation-20260905/`.

## 2026-09-05: Linux validation of structure recovery

Fresh GCC 13 and Clang 18 builds now compile/link and pass the four asset-free
gates. The recovered metadata matches both original executable copies; all
generated metadata/header checks and the split audit pass. The unit harness
reports 1056 passed, zero assertion failures, and the same 530 isolated crashes
as the preceding readiness run. Coverage is 92.43% across all 718 frozen
functions, with none uncovered. Four production metadata indices now explicitly
preserve the assembly's signed-byte extension. The new unsigned production-list
sentinel assertion was corrected to `UINT32_MAX` without changing game behavior.

Evidence is retained under
`artifacts/structure-recovery/linux-validation-20260905/`. The reconstruction
menu runs headlessly; same-state original tactical frames remain unproven.
The earlier WSL-blocked notes below are historical. Header-surface, warning and
linked-layout ratchets remain unresolved and their baselines are unchanged.

## 2026-09-05: Unit metadata pointer recovery

Track: Win95 reconstruction supporting mission-05 tactical panels and unit
information. The original +0 field points to a 12-byte name triplet, with
Polish, English and German string pointers at +0/+4/+8. The pool contains
34 triplets and 102 strings; types 33 and 34 share the final triplet.
Both original executables agree on every pointer and pointed-to byte string.
`UnitTypeLocalizedNameTable` now records that original packed structure with
size/offset assertions. A separate `UnitTypeRuntimePointerRecord` holds native
name, resource-key and movement-stem pointers, preserving the packed metadata VAs.

All 35 types now use the selected language. Original text is retained as font
bytes, without UTF-8 conversion. Four English labels were corrected from the
reconstructed helper: type 13 `Taran`, 16 `Highlander`, 20 `Cyklop`, and 27
`Pegaz`. The decompiler's `[102]` type was a misleading flattened name pool,
not one unit record. Its earlier ambiguity is resolved; old candidates remain
in the JSON with a resolved status.

Sixteen functions changed in this pointer batch. The remaining fake metadata
and resource-key globals are removed, including the English-only helper table.
Assembly also proves 28 missing numeric format arguments in four panel
functions; these now pass their original values and native format pointers.
The unit-info morale branch now reads its actual slot pointer instead of an
uninitialized register surrogate. Native triplet sharing, exact names and
reserved null pointers have regression assertions.

Evidence: `clash95.asm:409287..409424` defines the triplets;
`10315..10322`, `40714..40721`, and `41610..41620` prove the two dereferences;
`17383..17393` proves unsigned font-byte rendering. Map spellings corroborate
`Highlander`, `Pegaz` and `Cyklop` at lines 1224, 1260 and 1284.
Exact panel-argument evidence and validation commands are retained under
`artifacts/structure-recovery/unit-metadata-pointers-20260905/`.

High confidence applies to the layouts, byte values and assembly-backed reads.
Runtime and visual fidelity remain unverified while WSL returns
`E_ACCESSDENIED`. Existing unsupported-selector helper fallbacks remain
compatibility guards, not original validation behavior. Production-coordinate
and render-call scars, the battle blend omission, opaque metadata +38..+69,
and the type-40 combat-score boundary remain deferred. Full subsystem header
regeneration still requires Linux preprocessing.

## 2026-09-05: Unit metadata layout and consumer recovery

Track: Win95 structure recovery supporting the mission-05 tactical frontier.
The complete physical table has 40 records of 88 bytes, including 35 real
types and five zero reserved records. Both original executables match all
3,520 bytes (table SHA256 `2755d2c58c24a6c7337597a593456a03404850a4c666fd0493c2c372a1310963`).
The next symbol is the language-directory table at `0x00513328`; the original
castle production loop probes exactly 40 slots. The roster remains 35 types.

New high-confidence fields are vision radius (+70), corpse sprite base (+78),
and auto-resolve casualty weight (+87). `clash95.map:6984` identifies the last
as public `unit_stats`; the old alias to +78 was wrong. Vision uses the maximum
radius of occupied stack slots; corpse rendering adds reversed facing; casualty
distribution selects the largest unprocessed weight and deducts it from quantity.
All production, role, sound-frame and movement-audio tail fields retain the
unsigned widths and initialized values proved by their assembly reads.

`UnitTypeRuntimeCoreMetadataRecord` now holds the full initialized bytes, with
compile-time offset pins. Its scalar consumers and movement-sound strings use
the recovered backing. The fake tail globals and incorrect `unit_stats` alias
were removed. The combat-strength scorer also uses the real typed metadata;
the production roster tests original name-pointer presence in the five reserved
records instead of reading beyond an isolated pointer variable.

Rejected: tactical `role` comes from a unit metadata parser. The referenced
literal belongs to CLIPS `Rules_ParseDefclass`, unrelated to unit types.
Unresolved: +38..+69 remain 32 opaque initialized bytes; no terrain-modifier
names are justified. Original +0/+4 name/resource pointers still require full
native resolution in remaining consumers. The old combat-score predicate also
accepts type 40, outside the physical table; no authentic producer of that type
is proven, so this boundary was preserved and remains deferred.

Evidence and repeatable static byte verification are under
`artifacts/structure-recovery/unit-metadata-20260905/`; exact byte input is
`data/unit_type_runtime_metadata.json`. `tools/gen_unit_type_runtime_metadata.py`
regenerates the table and native movement-stem pointers without retail assets.
The struct and constant headers were regenerated. Subsystem headers received
only the necessary declaration synchronization; full usage regeneration still
requires Linux preprocessing. Regression assertions were added for the original
values, reserved roster slots, vision, corpse frames and production gates.
Linux builds, executable tests, routes and a fresh original frame pair remain
blocked by WSL `E_ACCESSDENIED`; runtime fidelity is not claimed.

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
| `20` | `UnitType20_Cyclop` | `cykl` | high | `off_5124D4` (`Cyklop / Cyklop / Zyklop`) resolves to `cykl`. |
| `21` | `UnitType21_Troll` | `trol` | high | `off_5124E0` (`Troll`) resolves to `trol`. |
| `22` | `UnitType22_Scorpion` | `scorp` | high | `off_5124EC` (`Skorpion / Scorpion`) resolves to `scorp`. |
| `23` | `UnitType23_Skeleton` | `szk` | high | `off_5124F8` (`Szkielet / Skeleton`) resolves to `szk`. |
| `24` | `UnitType24_Wizard` | `mag` | high | `off_512504` (`Mag / Wizard`) resolves to `mag`. |
| `25` | `UnitType25_Ghost` | `duch` | high | `off_512510` (`Duch / Ghost`) resolves to `duch`. |
| `26` | `UnitType26_Eagle` | `orzel` | high | `off_51251C` (`Orzeł / Eagle`) resolves to `orzel`. |
| `27` | `UnitType27_Pegasus` | `pegaz` | high | `off_512474` (`Pegaz / Pegaz / Pegasus`) resolves to `pegaz`. |
| `28` | `UnitType28_Winger` | `skrz` | high | `off_512528` (`Skrzydlak / Winger`) resolves to `skrz`. |
| `29` | `UnitType29_Fly` | `wazka` | high | `off_512534` (`Ważka / Fly / Riesenlibelle`) resolves to `wazka`. |
| `30` | `UnitType30_Dragon` | `smok` | high | `off_512480` (`Smok / Dragon / Drachen`) resolves to `smok`. |
| `31` | `UnitType31_GoldCargo` | `gold` | high | `off_512540` (`Złoto / Gold`) resolves to `gold`, stack-action helpers treat type `31` as non-combat cargo excluded from the normal-unit predicate, and temple/treasure reward helpers also instantiate type `31` slots as spawned gold payload stacks. |
| `32` | `UnitType32_PeasantCargo` | `peas` | high | `off_51254C` (`Chłopi / Peasants`) resolves to `peas`, and capture/building helpers merge and normalize type `32` as transferable peasant cargo rather than an ordinary combat slot. |
| `33` | `UnitType33_SpecialFootPersonage` | `specm` | medium | This record reuses `off_512558` (`Dowódca / Tactician / Soldat`), keeps infantry-like movement assets, enters the prisoner pipeline on capture, and is also instantiated by `Queen_NewTurn` through `Building_CreateSpecialPersonageGarrisonUnit` during the royal birth event. The queen-turn path binds type `33` specifically to the son outcome before formatting `g_QueenSonBirthTexts`. The asm-backed garrison helper proves these entries are initialized through the ordinary `UnitSlot_InitFromType` path and then flagged as resident special occupants inside the building slot. The `specm` code name and the shared commander-like label both argue for a broader special-personage role rather than a prisoner-only one. |
| `34` | `UnitType34_SpecialMountedPersonage` | `speck` | medium | This record reuses the same localized-name triplet, switches to mounted movement assets, participates in the same prisoner pipeline as type `33`, and is also emitted by the queen birth path as the alternate royal special entry. The queen-turn path binds type `34` specifically to the daughter outcome before formatting `g_QueenDaughterBirthTexts`. The same asm-backed helper shows the mounted variant is installed into normal building garrison slots rather than a separate royal record path. The `speck` code name plus the daughter-birth text about becoming an officer reinforces the same shared special-personage family. |

### 2.2 Recovered Categories
| recovered_name | confidence | kind | evidence summary | where found | related |
| --- | --- | --- | --- | --- | --- |
| `RangedUnitCategory` | high | category | Units with non-zero `g_UnitTypeMaxRange` enter projectile logic and consume the shot-power plus range tables. | `clash95.c:39839-39866`, `clash95.c:40745-40780`, `clash95.c:49182-49270` | `base_shot_power`, `attack_range_max`, `attack_range_min` |
| `FlyingUnitCategory` | high | category | `g_UnitTypeFlags` bit0 marks airborne units. They render in the post-ground pass, use airborne movement-sound variants, and satisfy `UnitStack_HasOnlyFlyingUnits`. | `clash95.c:27660-27690`, `clash95.c:36171-36190`, `clash95.c:39530-39590`, `clash95.c:44795-44910`, `clash95.c:56958-57358` | `UnitType26_Eagle`, `UnitType27_Pegasus`, `UnitType28_Winger`, `UnitType29_Fly`, `UnitType30_Dragon` |
| `GroundUnitCategory` | medium | category | Non-airborne units with non-zero melee stats use ordinary terrain/surface-dependent movement sounds and the normal melee path. | `clash95.c:22124-22145`, `clash95.c:39680-39760`, `clash95.c:56958-57358` | standard infantry, cavalry, siege, and utility units |
| `LightUnitCategory` | high | category | `g_UnitTypeFlags` bit1 selects the 6-point morale seed instead of the default 10-point seed. | `clash95.c:22188-22196`, `clash95.c:32986-32991` | `morale` |
| `SpecialCargoEntryCategory` | high | category | Types `31` and `32` are excluded by `UnitStack_HasNormalCombatUnits`, transferred separately during capture, are used by gold/peasant-specific UI and economy logic, count as noncombat building occupants when present in castle garrisons, and cannot satisfy the port-reinforcement pickup gate because that gate requires at least one normal combat unit in the claiming stack. | `clash95.c:24216-24303`, `clash95.c:30685-30854`, `clash95.c:31367-31380`, `clash95.c:53970-53975`, `clash95.c:54607-54624`, `clash95.c:58286-58736`, `clash95.c:66993-66997` | `UnitType31_GoldCargo`, `UnitType32_PeasantCargo` |
| `SpecialPersonageCategory` | high | category | Types `33` and `34` are non-standard special personage entries: capture logic routes them through the prisoner pipeline, `Queen_NewTurn` creates the same ids directly inside building garrisons during the birth event, fatigue/morale adjustment paths explicitly skip them, military-strength scoring first detects their presence and forwards that fact into the core combat-strength helper, and personage-only stacks still fail the port-reinforcement pickup gate because that gate also requires normal combat units. The asm-backed `Building_CreateSpecialPersonageGarrisonUnit` body shows the same helper scanning the ordinary 12-slot building garrison array, calling `UnitSlot_InitFromType`, and setting the resident-slot flag bits afterward; those same resident-slot bits then exclude special personages from generic castle training, while `Building_CountNonCombatGarrisonEntries` counts them alongside cargo entries in building-engagement gating. The supporting gameplay predicates are now named `UnitStack_HasSpecialPersonageUnits`, `Building_CountSpecialPersonageGarrisonEntries`, and `Building_HasSpecialPersonageGarrisonEntries`, which matches the broader family semantics. | `clash95.c:24393-24472`, `clash95.c:24512-24546`, `clash95.c:24967-25054`, `clash95.c:25279-25329`, `clash95.c:31367-31380`, `clash95.c:54593-54624`, `clash95.c:58286-58736`, `clash95.c:64324-64424`, `clash95.c:64679-64702`, `clash95.c:65195-65274`, `clash95.c:68528-68607`, `clash95.asm:118318`, `clash95.asm:121676-121682`, `clash95.asm:121741-121777`, `clash95.exe` strings `specm` / `speck` / `Queen_NewTurn() - nowy potomek` | `UnitType33_SpecialFootPersonage`, `UnitType34_SpecialMountedPersonage` |
| `PortReinforcementUnitTypePool` | high | roster | `Port_CollectReinforcementShipment` seeds each arriving slot by drawing a random entry from the fixed table `{0, 1, 2, 3, 4, 5, 7, 9, 10, 15, 16, 17}`, so port reinforcements are limited to peasant, light/heavy infantry, pike/spear, light cavalry, knights, archer, crossbower, forester, goral, and builder units rather than cargo, special-personage, siege, or monster ids. | `clash95.c:58690-58723`, `clash95.asm:425504-425533`, `UNIT_TYPES_AND_STATS.json` | `UnitType0_Peasant`, `UnitType1_LightInfantry`, `UnitType2_HeavyInfantry`, `UnitType3_Pikeman`, `UnitType4_HeavySpearman`, `UnitType5_LightCavalry`, `UnitType7_Knights`, `UnitType9_Archer`, `UnitType10_Crossbower`, `UnitType15_Forester`, `UnitType16_Goral`, `UnitType17_Builder` |

## 3. Recovered Stats
| recovered_name | confidence | semantic meaning | evidence summary | locations | stat_kind | used_by |
| --- | --- | --- | --- | --- | --- | --- |
| `base_action_points` | high | Per-type maximum action-point budget before fatigue penalties. | Stored in `g_UnitTypeBaseActionPoints`, copied into slot `+8`, and used by `UnitSlot_CalcActionPointsFromFatigue`. | `clash95.c:22183-22205`, `clash95.c:22585-22613` | base stat | most field units |
| `current_action_points` | high | Runtime action points available to the slot this turn. | Lives at UnitSlotRecord `+8`, is refreshed each new turn from the base AP table after fatigue thresholds are applied, and tactical battle restores the pre-battle source value before survivors are copied back out through `Battle_RestoreSavedActionPointsBeforeResultCopy`. | `clash95.c:22558-22575`, `clash95.c:23821-23826`, `clash95.c:46495-46509`, `clash95.c:46533-46539` | current stat | most field units |
| `current_health_percent` | high | Runtime health or squad-strength percentage, with cargo-specific payload reuse on special transfer units. | Ordinary units initialize this byte to `100` and multiply it into effective attack and damage formulas; zero kills the slot. The army split/regroup helpers also classify slots from the same byte, using `<= 10` as the weak-unit cutoff and `>= 8` as the stronger regroup threshold. Cargo types `31` and `32` reuse the same byte as carried gold/population quantity during transfer and reward flows. | `clash95.c:22185-22196`, `clash95.c:23446-23506`, `clash95.c:33746-33871`, `clash95.c:39790-39810`, `clash95.c:54271-54355`, `clash95.c:55665-55704`, `clash95.c:69015-69683` | current modifier | all field units, special cargo entries |
| `fatigue` | high | Runtime exhaustion counter that throttles action points and morale. | Lives at UnitSlotRecord `+10`; thresholds at `80/90/100` reduce action points and severe fatigue lowers morale each new turn. | `clash95.c:22558-22575`, `clash95.c:23768-23837`, `clash95.c:24669-24723` | current modifier | all field units |
| `morale` | high | Runtime `0..20` morale or obedience score that boosts combat stats and can cause order refusal. | Seeded to `6` or `10`, clamped to `0..20`, added by the attack/damage helpers, checked by `Unit_CheckLowMorale`, and shown in the selected-unit battle panel through the same five-tier `0..20` presentation bucket. | `clash95.c:22188-22205`, `clash95.c:23446-23506`, `clash95.c:23623-23718`, `clash95.c:24759-24823`, `clash95.c:45590-46197`, `clash95.c:9565-9590` | current modifier | all field units |
| `stance_bits` | medium | Runtime packed status/order/volley byte used by both combat and garrison helpers. | Bits `0..1` of slot `+12` feed melee, defense-power, and wall-attack helpers directly, and value `3` marks the resident special-occupant state written by `Building_CreateSpecialPersonageGarrisonUnit`. Bits `2..3` form a separate order/state subfield, bits `4..6` track `volleys_used` and are incremented by ranged fire before being compared against `status_level + 1`, and only bit `7` remains unresolved. | `clash95.c:23446-23506`, `clash95.c:24828-24857`, `clash95.c:40800-40968`, `clash95.c:45590-46197`, `clash95.c:54500-54518`, `clash95.c:64679-64703`, `clash95.c:68528-68607`, `clash95.c:9565-9590` | current modifier | field and garrison units |
| `state_flags` | high | Runtime ready/spent-turn/refusal/plague flag byte. | Bit `0x1` drives `UnitStack_HasReadyUnits`, bit `0x2` is set and cleared by the spent-turn helpers and gates fatigue recovery, bit `0x4` marks low-morale refusal, and bit `0x8` is the plague marker used by plague spread and peasant-cargo attrition. | `clash95.c:22726-22771`, `clash95.c:23944-24062`, `clash95.c:25197-25229` | current flags | all field units, plague-carrying cargo |
| `base_melee_attack` | high | Core melee attack rating. | Non-zero values gate standard melee and feed `UnitStats_CalcEffectiveMeleeAttack`. | `clash95.c:23446-23460`, `clash95.c:39716-39760` | base stat | melee-capable units |
| `base_defense_power` | high | Per-type defence rating shown in the battle sidebar and used by combat resistance math. | Stored in `g_UnitTypeBaseDefensePower`, consumed by `UnitStats_CalcEffectiveDefensePower`, summed by `UnitSlots_CalcDefenseScore`, used by `UnitBattle_CalcMeleeExchange`, and also reduces trap/shot damage. | `clash95.c:23665-23720`, `clash95.c:31677-31690`, `clash95.c:39160-39210`, `clash95.c:40745-40780`, `clash95.c:42070-42105`, `clash95.c:45590-46197`, `clash95.c:46990-47080`, `clash95.c:9565-9590` | base stat | combat-capable units |
| `base_shot_power` | high | Per-type projectile or shot-power value before health scaling. | Stored in `g_UnitTypeBaseShotPower`, consumed by `UnitStats_CalcEffectiveShotPower` and `UnitStats_GetBaseShotPower`, displayed under the `Shot power` UI row, and used by projectile damage projection. | `clash95.c:23684-23732`, `clash95.c:30395-30445`, `clash95.c:31623-31668`, `clash95.c:40745-40780`, `clash95.c:45590-46197`, `clash95.c:46990-47080`, `clash95.c:9565-9590` | base stat | shot-capable units |
| `base_wall_attack` | high | Per-type wall-assault strength used against fortification sections. | `UnitStats_CalcEffectiveWallAttack` only feeds direct wall assaults and the ram's building-assault combat-strength branch, and `UnitBattle_AttackWall` subtracts its result straight from wall-section health. | `clash95.c:23736-23744`, `clash95.c:31606-31620`, `clash95.c:40846-40940` | base stat | wall-assault-capable units, especially `UnitType13_Ram` |
| `road_move_cost` | high | Move cost on road or bridge overlays. | Returned from `g_UnitTypeRoadMoveCost` whenever the tile record carries a road/bridge overlay. | `clash95.c:26703-26710`, `clash95.c:41380-41410` | base stat | world movement |
| `world_surface_move_costs[8]` | high | Eight-lane normalized world-surface movement profile. | Combined with `g_TerrainMoveTableOffsets` by world movement helpers after raw terrain ids collapse into one of eight normalized lanes; the currently recovered lane order is `plain_class_a`, `forest`, `desert_class`, `swamp`, `plain_class_b`, `water_surface`, `hills`, `mountains`. | `clash95.c:26459-26517`, `clash95.c:26529-26589`, `clash95.c:26703-26748`, `clash95.asm:19368-19440` | base stat | world movement |
| `battle_tile_move_cost` | medium | Tactical per-tile movement cost used by battle pathing. | `UnitBattle_InitPathingTables` precomputes a tactical cost grid from `BattleRuntimeState.default_tile_move_cost`, while `UnitBattle_GetTileMoveCostOrZero` switches airborne unit types to a fixed cost `5`. | `clash95.c:38152-38226` | derived stat | tactical movement/pathing |
| `unit_type_flags` | high | Bitfield inside the 88-byte metadata record. | Bit0 is airborne; another bit still controls the light-unit seed path. | `clash95.c:22133-22144`, `clash95.c:27660-27690`, `clash95.c:36171-36190`, `clash95.c:39530-39590`, `clash95.c:44795-44910`, `clash95.c:56958-57358` | modifier | all unit types |
| `attack_range_max` | high | Maximum projectile range in tiles. | `UnitBattle_IsTileWithinRange` compares the ceil-sqrt tile distance against this value, and ranged-action setup treats zero as no shot mode. | `clash95.c:40095-40135`, `clash95.c:43226-43307` | base stat | ranged units |
| `attack_range_min` | high | Minimum projectile range or dead-zone floor in tiles. | `UnitBattle_IsTileWithinRange` rejects shots whose ceil-sqrt tile distance is not greater than this lower bound. | `clash95.c:40095-40135`, `clash95.c:49360-49370` | base stat | ranged units with dead zones |
| `production_time` | high | Per-type number of production turns needed to finish one queued unit. | `Building_SetUnitProduction` copies `g_UnitTypeProductionTime` into the building countdown byte at `+415`, and `Building_ProcessUnitProductionTurn` decrements that byte each turn before reloading the same table after a completed unit. | `clash95.c:33039-33080`, `clash95.c:54470-54484`, `clash95.asm:386429`, `clash95.asm:409528-409532` | base stat | buildable production units |
| `production_cost` | high | Per-type money cost charged when a queued unit finishes production. | `Building_ProcessUnitProductionTurn` reads `g_UnitTypeProductionCost`, requires that value to be available in `BuildingRecord.stored_money`, and subtracts it on completion; the localized building-info row labels the same metadata family as `production cost`. | `clash95.c:33057-33073`, `clash95.asm:386426`, `clash95.asm:409531-409532`, `RECOVERED_STRUCTURES.json` | base stat | buildable production units |
| `production_licence_cost` | high | Per-type money cost to buy the unit's production licence into a building. | `Building_BuyUnitLicence` debits `g_UnitTypeProductionLicenceCost` before appending the unit type into the building's 12-slot licence array, and `Building_GetTotalValue` adds the same word back for each installed licence. | `clash95.c:54403-54437`, `clash95.c:55032-55058`, `clash95.asm:94731-94823`, `clash95.asm:409533-409538` | base stat | buildable production units |
| `production_required_tech_level_mode_2` | high | Per-type tech-level threshold used when the production building's mode byte equals `2`. | `Building_IsUnitLicenceEligible` selects `g_UnitTypeProductionRequiredTechLevelMode2[88 * unitType]` when `building[4] == 2`, compares that byte against `BuildingRecord.tech_level_bits & 7`, and `CastleProduction_RebuildAvailableUnitList` uses the same gate to decide which unit types appear as licensable options. | `clash95.c:48320-48339`, `clash95.c:54713-54733`, `clash95.asm:95408-95447`, `clash95.asm:409538-409543` | base stat | buildable production units in mode-2 production buildings |
| `production_required_tech_level_other_modes` | high | Per-type tech-level threshold used when the production building's mode byte is non-zero but not `2`. | `Building_IsUnitLicenceEligible` switches to `g_UnitTypeProductionRequiredTechLevelOtherModes[88 * unitType]` for the alternate production-building modes and applies the same `tech_level_bits & 7` gate before the castle panel or purchase flow allows the unit licence. | `clash95.c:48320-48339`, `clash95.c:54713-54733`, `clash95.asm:95408-95452`, `clash95.asm:409541-409545` | base stat | buildable production units in non-2 production buildings |
| `production_requires_smiths` | high | Per-type production-licence gate that requires the smiths add-on before the unit may be licensed. | `Building_IsUnitLicenceEligible` scans `g_ProductionLicenceSmithsRequiredUnitTypes` only when the smiths bit `0x10` is absent in `BuildingRecord.castle_addon_flags`, so membership in that fixed unit-id table is a hard smiths prerequisite for licence eligibility. | `clash95.c:54726-54741`, `clash95.asm:409548-409567` | derived stat | buildable production units gated by smiths |
| `production_requires_workshop` | high | Per-type production-licence gate that requires the workshop add-on before the unit may be licensed. | `Building_IsUnitLicenceEligible` returns early once the workshop bit `0x04` is present, and otherwise scans `g_ProductionLicenceWorkshopRequiredUnitTypes`, so membership in that fixed unit-id table is a hard workshop prerequisite for licence eligibility. | `clash95.c:54743-54752`, `clash95.asm:409570-409585` | derived stat | buildable production units gated by workshop |
| `construction_progress_per_turn` | high | Fixed construction throughput contributed by each garrisoned builder to staged stronghold construction. | `Building_NewTurn` adds `g_BuilderConstructionProgressPerTurn` for every type-`17` garrison slot while reducing `BuildingRecord.construction_turns_remaining`, and `Building_CalcRemainingConstructionTurns` divides the pending timer by the same constant to estimate the remaining turns shown in the construction dialog. | `clash95.c:33458-33469`, `clash95.c:34142-34158`, `clash95.c:34483-34490` | derived stat | `UnitType17_Builder` |
| `role` | high | Per-type tactical role class used by battle AI and healing eligibility. | The statically initialized byte at metadata +77 indexes battle priority/deployment tables, and the healing gate reads role >= 3. The former parser claim was rejected: `aRole` belongs to CLIPS class concrete/abstract parsing. | `clash95.asm:92815-92820`, `clash95.c:49816-49834`, `clash95.c:50323-50335`, `clash95.c:50576-50584`, `clash95.c:51608-51618`, `clash95.c:52082-52090`, `clash95.c:52568-52631`, `clash95.c:53501-53651`, `clash95.c:69105-69118` | base stat | all combat-capable unit types |
| `move_pixel_speed` | medium | Per-frame displacement during movement animation. | Movement loops multiply direction vectors by `byte_512570`. | `clash95.c:38680-38720`, `clash95.c:39240-39330` | base stat | mobile units |
| `move_tick_delay` | medium | Delay between movement animation ticks. | `Time_Now` gates movement animation advancement with `byte_512571`. | `clash95.c:38632-38705` | modifier | mobile units |
| `animation_frame_interval` | high | Shared per-type frame delay for idle and attack animation loops. | World idle animation, battle idle animation, melee attack loops, and ranged attack loops all gate frame advancement with `byte_512572`. | `clash95.c:24096-24105`, `clash95.c:39393-39406`, `clash95.c:40211-40224`, `clash95.c:45849-45874` | modifier | animated units |
| `animation_flags` | medium | Per-type animation-behavior bits. | Bit0 gates whether the world/battle idle-animation updaters advance the unit's looping frame state. | `clash95.c:24098-24104`, `clash95.c:45849-45856` | modifier | looping animated units |
| `sprite_vertical_offset_px` | high | Per-type sprite Y lift in pixels, also reused as an overhang-presence test. | Rendering subtracts `byte_512577` directly from the sprite Y origin, world and battle redraw helpers use non-zero values to invalidate neighboring tiles, and only the large overhanging flyers carry non-zero byte values. | `clash95.c:23969-24017`, `clash95.c:24317-24320`, `clash95.c:27713-27722`, `clash95.c:40229-40243`, `clash95.c:44814-44875`, `clash95.c:45932-45960`, `clash95.exe` metadata bytes |
| `melee_attack_frame_count` | high | Number of frames in the melee attack sheet. | The melee attack animation loop copies `byte_512578` into its frame-count limit before stepping the `_a.s32` sheet. | `clash95.c:39377-39408` | animation stat | melee-capable units |
| `ranged_attack_frame_count` | high | Number of frames in the ranged attack sheet. | The shot-animation loop copies `byte_512579` into its frame-count limit before stepping the `_s.s32` sheet. | `clash95.c:40079-40100`, `clash95.c:40211-40266` | animation stat | ranged-capable units |
| `melee_attack_sound_frame` | high | Frame index that triggers the melee attack sound. | The melee attack loop plays `Audio_PlayUnitMeleeAttackSound` exactly when the current frame matches `byte_5125B7`. | `clash95.c:39393-39401` | animation stat | melee-capable units |
| `ranged_attack_sound_frame` | high | Frame index that triggers the ranged attack sound. | Both ranged attack animation branches play `Audio_PlayUnitRangedAttackSound` when the current frame matches `byte_5125B8`. | `clash95.c:40213-40217`, `clash95.c:40257-40261` | animation stat | ranged-capable units |
| `move_sound_stem` | high | Per-unit movement-sound stem inside the metadata record. | `Audio_PlayWorldMapUnitMoveSound` and `Audio_PlayBattleMapUnitMoveSound` build `sfx\\ruchy\\<stem>...` paths from the field at offset `+81`. | `clash95.c:56958-57358`, `clash95.asm:101018-101218`, `clash95.asm:409554-409562` | base stat | all moving units |
| `move_sound_variant_count` | high | Number of alternating step samples per unit type. | The current step variant wraps modulo `g_UnitMoveSoundVariantCounts[88 * type]`. | `clash95.c:57103-57104`, `clash95.c:57331-57332`, `clash95.asm:101212-101218`, `clash95.asm:101564-101570` | base stat | step-based movers |
| `move_sound_base_volume` | high | Default volume used when playing movement sounds. | Both movement-sound helpers pass `g_UnitMoveSoundBaseVolumes[88 * type]` into `CSS_PlaySound`. | `clash95.c:57103`, `clash95.c:57139`, `clash95.c:57234`, `clash95.c:57331`, `clash95.asm:101067`, `clash95.asm:101419` | base stat | all moving units |

### 3.1 Battle UI Label Corroboration
| ui_label | mapped_stat_or_family | confidence | evidence summary | locations |
| --- | --- | --- | --- | --- |
| `Quantity` | `current_health_percent` | medium | `UnitBattle_DrawSelectedUnitPanel` formats slot byte `+9` under the localized `Quantity` row, which supports reading that byte as the battle-visible squad strength/quantity measure rather than an opaque HP counter. | `clash95.c:43800-43910`, `clash95.c:45590-46197`, `clash95.c:9565-9590` |
| `Action points` | `current_action_points` | high | The selected-unit panel prints slot byte `+8` under the `Action points` row from `off_514DC8`, matching the already recovered runtime AP field. | `clash95.c:45590-46197`, `clash95.c:9565-9590` |
| `Attack power` | `base_melee_attack` family | high | The battle sidebar includes a dedicated `Attack power` row, reinforcing that the existing melee-attack table is a first-class displayed combat stat rather than a hidden scalar. | `clash95.c:45590-46197`, `clash95.c:9565-9590` |
| `Shot power` | `base_shot_power` | high | The battle sidebar and other unit-detail panels only show the `Shot power` row when metadata byte `+25` is non-zero, and the displayed numeric helper is `UnitStats_GetBaseShotPower`. | `clash95.c:30395-30445`, `clash95.c:45590-46197`, `clash95.c:46990-47080`, `clash95.c:9565-9590` |
| `Defence power` | `base_defense_power` | high | The battle sidebar's unconditional `Defence power` row is filled from `UnitStats_GetDefenseIconIndex`, and the same helper family drives stack defense scoring, melee exchange resistance, and trap damage mitigation. | `clash95.c:31677-31690`, `clash95.c:39160-39210`, `clash95.c:42070-42105`, `clash95.c:45590-46197`, `clash95.c:46990-47080`, `clash95.c:9565-9590` |
| `Morale` | `morale` | high | The selected-unit panel prints the runtime morale row directly from the same localized label table, matching the recovered slot `+11` morale field. | `clash95.c:45590-46197`, `clash95.c:9565-9590` |
| `Tiredness` | `fatigue` | high | The final localized row in the same table is `Tiredness`, which aligns with the recovered fatigue byte at slot `+10` and its turn-by-turn AP penalties. | `clash95.c:45590-46197`, `clash95.c:9565-9590` |

## 4. Type-to-Stat Relationships
| unit_type | stat | relationship | confidence | evidence |
| --- | --- | --- | --- | --- |
| `UnitType13_Ram` | `action_points`, `base_melee_attack` | Standard melee handlers reject type `13`, so its primary interaction path is not the ordinary melee routine despite sharing generic unit-slot state. | high | `clash95.c:39688`, `clash95.c:49195` |
| `UnitType13_Ram` | `base_wall_attack` | The ram's building-assault combat-strength branch ignores ordinary unit combat and switches to the wall-attack helper when fortifications are present; direct tactical wall assaults also spend AP and apply this stat straight to wall health. | high | `clash95.c:31606-31620`, `clash95.c:40846-40940` |
| `UnitType0_Peasant` | `building_unit_licence_roster` | Newly created buildings seed `unit_licence_type_ids[0] = 0`, so the first castle production-licence slot is a built-in peasant licence rather than an empty entry. The one-argument licence host helper then skips that seeded peasant slot when searching for later licence entries. | high | `clash95.c:32488-32494`, `clash95.c:68455` |
| `UnitType17_Builder` | `bridge_crossing_pathing_access` | `UnitStack_HasBuilder` is an exact type-17 membership check, and the strategic queue helpers enable bridge-crossing path generation only when that predicate succeeds, so stacks containing at least one builder can route through bridge crossings unavailable to ordinary stacks. | high | `clash95.c:24134-24152`, `clash95.c:26703-26710`, `clash95.c:66973-67109` |
| `UnitType17_Builder` | `building_unit_licence_roster` | The one-argument castle licence helper explicitly skips builder licences while scanning for later roster entries, and the same subsystem treats type `17` as construction labor by subtracting each garrisoned builder from remaining build time. | high | `clash95.c:33447-33472`, `clash95.c:34148-34158`, `clash95.c:68455` |
| `UnitType17_Builder` | `construction_progress_per_turn` | Each garrisoned builder adds the literal constant `26` from `g_BuilderConstructionProgressPerTurn` to the per-turn construction reduction path, and the construction-progress dialog divides the remaining timer by the same constant to estimate turns left. | high | `clash95.c:33458-33469`, `clash95.c:34142-34158`, `clash95.c:34483-34490` |
| `UnitType17_Builder` | `PortReinforcementUnitTypePool` | The fixed port-shipment roster includes unit type `17`, so ports can deliver builders as reinforcement cargo alongside the other recovered human/worker units. | high | `clash95.c:58690-58723`, `clash95.asm:425504-425533` |
| `UnitType2_HeavyInfantry` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `2` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `2` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType4_HeavySpearman` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `4` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `4` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType5_LightCavalry` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `5` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `5` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType6_HeavyCavalry` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `6` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `6` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType7_Knights` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `7` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `7` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType8_DragonCavalry` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `8` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `8` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType11_Musketeer` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `11` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `11` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType14_Cannon` | `production_requires_smiths` | `Building_IsUnitLicenceEligible` rejects unit type `14` when smiths bit `0x10` is absent, and the fixed smiths-gated licence table contains `14` explicitly. | high | `clash95.c:54726-54741` |
| `UnitType9_Archer` | `production_requires_workshop` | `Building_IsUnitLicenceEligible` rejects unit type `9` unless workshop bit `0x04` is present, and the fixed workshop-gated licence table contains `9` explicitly. | high | `clash95.c:54743-54752` |
| `UnitType10_Crossbower` | `production_requires_workshop` | `Building_IsUnitLicenceEligible` rejects unit type `10` unless workshop bit `0x04` is present, and the fixed workshop-gated licence table contains `10` explicitly. | high | `clash95.c:54743-54752` |
| `UnitType12_Catapult` | `production_requires_workshop` | `Building_IsUnitLicenceEligible` rejects unit type `12` unless workshop bit `0x04` is present, and the fixed workshop-gated licence table contains `12` explicitly. | high | `clash95.c:54743-54752` |
| `UnitType13_Ram` | `production_requires_workshop` | `Building_IsUnitLicenceEligible` rejects unit type `13` unless workshop bit `0x04` is present, and the fixed workshop-gated licence table contains `13` explicitly. | high | `clash95.c:54743-54752` |
| `UnitType15_Forester` | `production_requires_workshop` | `Building_IsUnitLicenceEligible` rejects unit type `15` unless workshop bit `0x04` is present, and the fixed workshop-gated licence table contains `15` explicitly. | high | `clash95.c:54743-54752` |
| `SpecialPersonageCategory` | `birth_spawn_host` | `Queen_NewTurn` spawns types `33` and `34` directly into ordinary owned stronghold garrisons through `Building_CreateSpecialPersonageGarrisonUnit`, proving the family uses the normal 12-slot building garrison container rather than a separate royal-only roster. | high | `clash95.c:65564-65665`, `clash95.c:64716-64740`, `clash95.asm:121650-121666` |
| `UnitType29_Fly` | `move_sound_stem` | Type `29` is one of the looped non-footstep movers, grouped with siege engines in both world and battle movement audio. | high | `clash95.c:56992`, `clash95.c:57200` |
| `UnitType30_Dragon` | `unit_type_flags` | Type `30` resolves to `smok` and belongs to the airborne class governed by `g_UnitTypeFlags` bit0. | high | `clash95.asm:409287-409426`, `clash95.c:44795-44910`, `clash95.c:56958-57358` |
| `UnitType31_GoldCargo` | `current_health_percent` | `Building_Transfer` exports stored treasury as type `31` cargo in 100-sized chunks plus a remainder written into slot byte `+9`, `Building_UnitGetInto` adds that byte back into building treasury on delivery, and `Temple_SpawnGiftGoldCargoStack` reuses the same quantity byte for `50/100/200/300` treasure rewards. | high | `clash95.c:33746-33854`, `clash95.c:54271-54290`, `clash95.c:55665-55704`, `clash95.c:55949-55958` |
| `UnitType32_PeasantCargo` | `current_health_percent` | `Building_Transfer` exports building population as type `32` cargo in 100-sized chunks plus a remainder written into slot byte `+9`, `Building_UnitGetInto` adds that byte back into the low 12 bits of building population storage on delivery, and plague/founding logic also treats the unit as transferable population cargo rather than ordinary infantry. | high | `clash95.c:33746-33871`, `clash95.c:54271-54308`, `clash95.c:23976-23986`, `clash95.c:32355-32367` |
| `UnitType33_SpecialFootPersonage` | `localized_name_table` | Type `33` shares the `Dowódca / Tactician / Soldat` localized-name triplet, is handled as a capturable special entry in the prisoner pipeline, and is also created by the queen birth event. | high | `clash95.c:24393-24472`, `clash95.c:64324-64424`, `clash95.c:65195-65274`, `clash95.asm:385244-385246`, `clash95.asm:409419-409423`, `clash95.exe` |
| `UnitType34_SpecialMountedPersonage` | `localized_name_table` | Type `34` is the mounted sibling of type `33`; it shares the same localized-name triplet, follows the prisoner workflow when captured, and is also emitted by the queen birth path. | high | `clash95.c:24393-24472`, `clash95.c:64324-64424`, `clash95.c:65195-65274`, `clash95.asm:412173-412174`, `clash95.exe` |
| `UnitType31_GoldCargo` | `resource_key` | The 88-byte metadata row for type `31` stores the front-edge resource key `gold`, and sprite/audio path builders reuse that same stem when loading cargo assets. | high | `clash95.asm:385309`, `clash95.asm:412015-412016`, `clash95.c:25686-26519`, `clash95.c:57011-57358` |
| `UnitType32_PeasantCargo` | `resource_key` | Type `32` stores the resource key `peas` at metadata `+4`, and the same stem is reused across unit sprite and sound path construction. | high | `clash95.asm:385311`, `clash95.asm:412094-412095`, `clash95.c:25686-26519`, `clash95.c:57011-57358` |
| `UnitType33_SpecialFootPersonage` | `resource_key` | The same record stores the distinct resource key `specm`, which is reused as the sprite/audio path stem despite sharing a localized-name table with type `34`. | high | `clash95.asm:385313`, `clash95.asm:412094-412095`, `clash95.c:25686-26519`, `clash95.c:57011-57358` |
| `UnitType34_SpecialMountedPersonage` | `resource_key` | The mounted sibling keeps its own resource key `speck`, showing that metadata `+4` is a per-type asset stem rather than a shared localized-name alias. | high | `clash95.asm:385315`, `clash95.asm:412173-412174`, `clash95.c:25686-26519`, `clash95.c:57011-57358` |
| `UnitType33_SpecialFootPersonage` | `queen_birth_outcome` | `Queen_NewTurn` selects type `33` for the son branch and formats `g_QueenSonBirthTexts`, so this id is the male birth outcome within the shared special-personage family. | high | `clash95.c:65660-65680`, `clash95.asm:389425-389455`, `clash95.exe` |
| `UnitType34_SpecialMountedPersonage` | `queen_birth_outcome` | `Queen_NewTurn` selects type `34` for the daughter branch and formats `g_QueenDaughterBirthTexts`, so this id is the female birth outcome within the same family. | high | `clash95.c:65660-65680`, `clash95.asm:389425-389455`, `clash95.exe` |
| `SpecialPersonageCategory` | `fatigue`, `morale` | Special personages are explicitly skipped by the generic fatigue and morale adjustment passes, so they do not follow the ordinary troop exhaustion/obedience lifecycle. | high | `clash95.c:24967-25054` |
| `SpecialPersonageCategory` | `combat_strength_score` | Military-strength scoring first scans for types `33` or `34` and forwards that presence flag into the core combat-strength helper, so special personages influence stack and garrison strength evaluation as a distinct class. | high | `clash95.c:25279-25329`, `clash95.asm:29202-29255` |
| `SpecialPersonageCategory` | `captured_owner_player_index` | The capture pipeline preserves the captured special person's original owner id through the prisoner transfer queue and into the building prison slot, and ransom recalculation consumes that stored player id rather than the imprisoning building's owner. | high | `clash95.c:24748-24761`, `clash95.c:64160-64192`, `clash95.c:64217-64234`, `clash95.c:64337-64343` |
| `SpecialPersonageCategory` | `queen_relationship_state` | `Queen_NewTurn` only enters the birth branch when `PLAYER_QUEEN_RELATIONSHIP_STATE == 9`; that branch creates type `33` or `34` inside a host building garrison and then resets the byte to `5`, so value `9` is a confirmed childbirth-pending phase that directly spawns the special-personage family. | high | `clash95.c:65653-65679` |
| `SpecialPersonageCategory` | `garrison_training_eligibility` | `Building_CreateSpecialPersonageGarrisonUnit` marks the resident slot with low bits `3`, and the generic castle-training helpers only accept occupied idle slots whose low status bits stay below `2`, so special personages are not trainable while resident in building garrisons. | high | `clash95.c:64679-64702`, `clash95.c:68528-68607` |
| `SpecialPersonageCategory` | `noncombat_garrison_entry` | `Building_CountNonCombatGarrisonEntries` counts types `33` and `34` together with gold and peasant cargo, and the building-engagement gate treats a garrison whose total occupants equal that noncombat count as lacking ordinary combat occupants. | high | `clash95.c:31367-31380`, `clash95.c:54607-54624` |
| `SpecialCargoEntryCategory` | `noncombat_garrison_entry` | `Building_CountNonCombatGarrisonEntries` counts gold and peasant cargo together with the special personage types, and the building-engagement gate treats a garrison whose total occupants equal that noncombat count as lacking ordinary combat occupants. | high | `clash95.c:31367-31380`, `clash95.c:54607-54624` |
| `RangedUnitCategory` | `base_shot_power`, `attack_range_max`, `attack_range_min` | Projectile units require non-zero max range, use `UnitStats_CalcEffectiveShotPower` as their shot-strength family, and apply the min/max range tables during tactical targeting. | high | `clash95.c:39839-39866`, `clash95.c:40095-40135`, `clash95.c:40745-40780` |
| `FlyingUnitCategory` | `unit_type_flags`, `move_sound_stem` | Airborne units are identified by bit0 and use single-digit airborne movement-sound suffixes instead of terrain-surface suffixes. | high | `clash95.c:57018-57025`, `clash95.c:57273-57282` |
| `FlyingUnitCategory` | `battle_tile_move_cost` | Tactical battle pathing bypasses the ground-cost grid and returns fixed cost `5` whenever the airborne bit is set in the per-type flag table. | high | `clash95.c:38198-38226` |
| `LightUnitCategory` | `morale` | Light units seed at `6` rather than `10`, proving that the bit1 class split affects starting morale rather than a hidden veterancy counter. | high | `clash95.c:22188-22196`, `clash95.c:32986-32991` |
| `MixedStackCategory` | `road_move_cost`, `world_surface_move_costs[8]` | `UnitStack_BuildMergedTerrainMoveProfile` merges metadata bytes `+29..+37` by keeping the highest non-zero cost for each normalized lane and collapsing to `0` when any member has `0`, so world-map movement follows the slowest traversable unit in the stack. | high | `clash95.c:26459-26517`, `clash95.c:26703-26748`, `clash95.c:27094-27134` |
| `PortReinforcementUnitTypePool` | `unit_type_id roster` | `Port_CollectReinforcementShipment` draws each spawned slot from the fixed table `{0, 1, 2, 3, 4, 5, 7, 9, 10, 15, 16, 17}`, so the port's arriving reinforcements are constrained to the recovered human/worker roster rather than cargo, special-personage, siege, or monster ids. | high | `clash95.c:58690-58723`, `clash95.asm:425504-425533`, `UNIT_TYPES_AND_STATS.json` |

## 5. Ambiguous Findings
- `UnitType33_SpecialFootPersonage` and `UnitType34_SpecialMountedPersonage` are still only medium-confidence names. The recovered code now proves these ids are not prisoner-only because `Queen_NewTurn` also creates them, and the `specm` / `speck` code names plus the officer-flavored birth text narrow the family further, but the exact original designer-facing label behind `Dowódca / Tactician / Soldat` remains inconsistent across languages.
- `UnitType31_GoldCargo` is effectively exact as a mobile treasury cargo entry. `UnitType32_PeasantCargo` is behaviorally secure as transferable building population cargo, but the exact original public label beyond peasant/population cargo remains unresolved from code alone.
- `PlayerRuntimeState.queen_relationship_state` now has one confirmed enum fragment: value `9` is childbirth pending. Other live values remain broader and ambiguous: `5` is reused after marriage acceptance and after birth, while `1` leads into the queen-departure branch.
- The eight normalized world-surface move lanes at metadata `+30..+37` are now partially recovered: `forest`, `swamp`, `hills`, and `mountains` are secure, while `desert_class`, `water_surface`, and the paired `plain_class_a/plain_class_b` labels remain conservative placeholders pending tighter tileset-specific corroboration.
- `production_required_tech_level_mode_2` and `production_required_tech_level_other_modes` are secure as per-unit licence tech thresholds, but the original designer-facing labels for the production-building mode byte values are still unresolved beyond the literal split `mode == 2` versus `mode != 2`.
- UnitSlotRecord `+12` is clearly a stance/formation byte, but its upper subfields are still only partially recovered.
- The decompiler’s `char *(*...)[102]` type on `g_UnitTypeMetadataRecords` is misleading if read literally as “34 unit types x 3 languages.” The asm/xref pass shows at least 35 record slots, with the final two special prisoner records reusing one localized-name table.

## 6. Batch 135 Note
- `Batch 135` stayed intentionally on the SDL/main-menu display frontier. No new unit-type or stat semantics were promoted in this wave; the unit/stat artifacts remain unchanged apart from this maintenance note while the executable-first menu-display repair was prioritized.

## 7. Batch 136 Note
- `Batch 136` stayed intentionally on the executable-first main-menu display frontier. The active work repaired the top-level menu text-cache and first-present corridor, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while the black-frame / post-present menu-display seam is still being recovered.

## 8. Batch 137 Note
- `Batch 137` stayed intentionally on the executable-first main-menu display frontier. The active work recovered the contained SDL present step for the top-level menu surface and proved stable nonblack menu frames under the gdb-contained probe lane, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while plain-run startup fidelity and interactive menu behavior remain the next blockers.

## 9. Batch 138 Note
- `Batch 138` stayed intentionally on the executable-first main-menu display frontier. The active work removed the plain-run `Render_CreateSprite` startup crash and brought the same stable nonblack menu-frame result onto the non-`gdb` executable lane, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while interactive menu behavior remains the next blocker.

## 10. Batch 139 Note
- `Batch 139` stayed intentionally on the executable-first main-menu display frontier. The active work removed a remaining non-authentic extra post-present pump from the contained top-level menu loop and proved the same stable nonblack menu-frame milestone still holds on the plainer one-present-then-loop path, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while real menu hover/click responsiveness remains the next blocker.

## 11. Batch 140 Note
- `Batch 140` stayed intentionally on the executable-first main-menu interaction frontier. The active work recovered the top-level menu widget record geometry, restored the contained widget draw helper to the corroborated `left/x, top/y` lane, and added a contained auto-click smoke path through the SDL fallback input seam, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while the render-state/input dispatch corridor still leaves the recovered cursor and button state inert in the live menu loop.

## 12. Batch 140 Note
- `Batch 140` stayed intentionally on the executable-first main-menu widget/text frontier. The active work relinked the local bootstrap target through the `_CHP` compatibility repair, tightened the SDL input/message seam, and revalidated the asm-backed `left/x` then `top/y` main-menu widget ordering, but it still did not promote any new unit-type or stat semantics; the contained SDL-presented frame remains a stable backdrop-only menu loop while the visible widget/text layer stays blocked.

## 13. Batch 141 Note
- `Batch 141` stayed intentionally on the executable-first menu-interaction frontier. The active work restored native render-state slot dispatch, removed the decompiler-scarred `Render_Begin` reentry crash, and switched the contained synthetic button-down to a one-read SDL fallback pulse, which is enough for the authentic top-level `Load Game` button to hover, click, and advance `g_MainMenuRequestedScreen` to `MAIN_MENU_REQUEST_LOAD_GAME` (`screen = 5`). It did not promote any new unit-type or stat semantics; the next blocker is the still-unlifted load-menu subtree rooted at `unk_518808`.

## 14. Batch 142 Note
- `Batch 142` stayed intentionally on the executable-first load-menu frontier. The active work rebuilt the weak `unk_518808` load-menu button blob into `g_LoadMenuButtonWidgetsTemplate`, replaced the broken `Render_LoadResourceSprite_v4` forwarding wrapper with the asm-backed cache/recolor helper shape, and extended the contained probe far enough to enter the load menu and click the `back` button through its own recovered callback. It still did not promote any new unit-type or stat semantics; the remaining blocker is now the save-slot row/resource corridor behind `sub_44A140`, `sub_4446E0`, and resource ids `18/21`.

## 14. Batch 143 Note
- `Batch 143` stayed intentionally on the executable-first load-menu frontier. The active work repaired the save-slot label/existence helper band, hardened `UI_DrawTextFmt` and the lazy text-sprite slot loader against the current x86-64 decompiler scars, and extended the contained probe far enough to prove authentic load-menu slot-strip selection state (`selected_slot = 0`) in addition to the earlier contained `back` button exit. It still did not promote any new unit-type or stat semantics; the next blocker is now the split text-sprite table and save-name repaint corridor behind `off_511EC8` / `dword_511ECC` / `word_511ED0`, plus the downstream widget-focus crash in `sub_419DC0 -> sub_460D80`.

## 15. Batch 144 Note
- `Batch 144` stayed intentionally on the executable-first load-menu frontier. The active work mirrored the active cursor descriptor into `dword_544D14`, promoted the recovered text/font slot seam into the live explicit `g_TextSpriteResourceSlots` table, and proved that the contained load menu now survives `row-strip hover -> bottom-button return -> back click` in one authentic submenu loop. It still did not promote any new unit-type or stat semantics; the next blocker is now the concrete row-resource preload crash at `Render_LoadResourceSprite_v4(18/21) -> DLXSpriteSet_Load`.

## 16. Batch 146 Note
- `Batch 146` stayed intentionally on the executable-first load-menu frontier. The active work proved the contained authentic slot-click/confirm lane on a real occupied save slot and characterized the first post-confirm `sub_444490` link/runtime blocker, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while the executable work stays on the load-menu-to-session-init corridor.

## 17. Batch 147 Note
- `Batch 147` stayed intentionally on the executable-first load-menu/session-load frontier. The active work repaired the recovered `sub_4163F0` world-map-init tail and widened `sub_4443C0` / `sub_4443D0` so the `.dat` / `.fac` save-path builders no longer truncate stack buffers, which moved the contained authentic `Load Game` lane through `WorldMap_Initialize`, through `sub_444490`, to `load-menu-post-confirm-after-save`, and back to `main-after-menu-probe`. It did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note while the next blocker shifts to the post-save `PlayGame` handoff.

## 18. Batch 149 Note
- `Batch 149` stayed intentionally on the retained executable-regeneration handoff between the already-green startup-prelude probes and the deeper mission/session path. The active work reduced the retained `PlayGame_Dispatch` frontier past `UI_CheckConfirmQuit`, `UI_CheckDialogAccepted`, the queen departure-event slab, the reached `unit_stats` byte lane, and the local control-flow scars in `Map_RebuildCastleSiteAnchorCache` / `sub_4602F0`, but it did not promote any new unit-type or stat semantics. The unit/stat artifacts remain unchanged apart from this maintenance note while the next retained blocker is now the chunked mission-loader switch `Scenario_LoadMissionByIndex` / `sub_460360`.

## 19. Batch 157 Note
- `Batch 157` materialized an evidence-backed `unit_type` enum directly in `clash95.c` from the existing recovered roster in `UNIT_TYPES_AND_STATS.json` and rewrote every `createUnit(...)` and `createCastle(...)` roster in `clash95.c` to use `UNIT_TYPE_*` constants instead of raw numeric ids. This wave did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, and the special-personage labels for ids `33` and `34` remain medium-confidence.

## 20. Batch 158 Note
- `Batch 158` rewrote the remaining direct `Unit_Create(...)` callsites with literal unit ids to use `UNIT_TYPE_*` constants instead of raw numeric values, covering the static setup lanes in `sub_44B550`, `Game_InitPlayerViewState`, `Scenario_LoadMissionByIndex`, and the port-reinforcement helper. This wave still did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the special-personage labels for ids `33` and `34` remain medium-confidence.

## 21. Batch 159 Note
- `Batch 159` replaced the remaining fixed `UnitSlot_InitFromType(...)` unit-id literals with `UNIT_TYPE_*` constants in `Temple_SpawnGiftGoldCargoStack`, `sub_4516B0`, and `sub_451A60`, covering the `UNIT_TYPE_GOLD_CARGO`, `UNIT_TYPE_CANNON`, and `UNIT_TYPE_PEGASUS` lanes. This wave still did not promote any new unit-type or stat semantics; pool/table-driven unit types remain dynamic, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the special-personage labels for ids `33` and `34` remain medium-confidence.

## 22. Batch 160 Note
- `Batch 160` typed the remaining pool-driven unit sources with `unit_type` enums by converting `g_PortReinforcementUnitTypePool`, `dword_515D10`, `dword_515D24`, and `dword_515D40` from raw numeric initializers to `UNIT_TYPE_*` constants. This wave still did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the `dword_515D10` / `dword_515D24` / `dword_515D40` symbol semantics remain under-evidenced even though their contents are now explicit.

## 23. Batch 161 Note
- `Batch 161` typed the safe unit-spawn helper signatures with `unit_type`, covering `UnitSlot_InitFromType`, `UnitStack_ResetRecord`, `createUnit`, `createCastle`, `Building_CreateSpecialPersonageGarrisonUnit`, the pool-selected local in `Temple_SpawnGiftUnitGroup`, and the stale guessed-type comments for the already-typed pool tables. This wave still did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, the `Unit_Create()` declaration intentionally stays loose because recovered call sites still use the old no-prototype extra-argument form, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the `dword_515D10` / `dword_515D24` / `dword_515D40` symbol semantics remain under-evidenced.

## 24. Batch 162 Note
- `Batch 162` typed the production-licence and unit-type predicate helpers with `unit_type`, covering the building licence helpers and wrappers, `UnitStack_DetachUnitTypeToAdjacentTile`, `UnitStack_HasUnitType`, `UnitStack_HasOnlyUnitType`, the `CastleProduction_RebuildAvailableUnitList` iterator, and the `g_ProductionLicenceSmithsRequiredUnitTypes` / `g_ProductionLicenceWorkshopRequiredUnitTypes` requirement tables. This wave still did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, the requirement tables stay byte-backed because the recovered storage uses `char` slots with `-1` sentinels, the `Unit_Create()` declaration intentionally stays loose, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the `dword_515D10` / `dword_515D24` / `dword_515D40` symbol semantics remain under-evidenced.

## 25. Batch 163 Note
- `Batch 163` typed the castle-production available-unit cache by converting `dword_532224` from a generic `int[]` to a `unit_type[41]` sentinel-terminated buffer, and rewired the nearby production-panel readers in `CastleProduction_RedrawSelectedUnitPanel` and `CastleProduction_HandleLicenceGridClick` to use typed array indexing instead of byte-offset pointer casts. This wave still did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, the production-licence requirement tables stay byte-backed because the recovered storage uses `char` slots with `-1` sentinels, the `Unit_Create()` declaration intentionally stays loose, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the `dword_515D10` / `dword_515D24` / `dword_515D40` symbol semantics remain under-evidenced.

## 26. Batch 164 Note
- `Batch 164` replaced the remaining confirmed gameplay/unit-slot raw unit-id literals with `UNIT_TYPE_*` names in `UI_DrawUnitInfoPane`, `UnitBattle_PlayShotAnimation`, `UnitBattle_ShotWall`, `Building_CalcRemainingConstructionTurns`, `Trap_New`, `UnitBattle_HandleBattlefieldInteraction`, `Building_UnitGetInto`, and the case-8 mission garrison scan, covering the `UNIT_TYPE_FORESTER`, `UNIT_TYPE_GORAL`, `UNIT_TYPE_BUILDER`, `UNIT_TYPE_RAM`, `UNIT_TYPE_CATAPULT`, `UNIT_TYPE_CANNON`, `UNIT_TYPE_DRAGON`, `UNIT_TYPE_WINGER`, `UNIT_TYPE_WIZARD`, `UNIT_TYPE_GOLD_CARGO`, `UNIT_TYPE_PEASANT_CARGO`, and `UNIT_TYPE_SPECIAL_FOOT_PERSONAGE` lanes. This wave still did not promote any new unit-type or stat semantics; the roster names and confidence levels remain unchanged, the remaining mixed-domain raw ids stay deferred where the field is not yet securely a `unit_type`, the `Unit_Create()` declaration intentionally stays loose, the `0xFFFFFFFF` sentinel lane remains a non-enum special case, and the `dword_515D10` / `dword_515D24` / `dword_515D40` symbol semantics remain under-evidenced.

## 27. Batch 175 Note
- `Batch 175` stayed on the executable startup/runtime frontier. The active work restored the retained `createLogFiles` side effect on the full bootstrap route, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note.

## 28. Batch 179 Note
- `Batch 179` stayed on the executable startup/runtime frontier. The active work moved the direct `a` game route past the resource-context, building-sprite-cache, and frame-rendering crashes into the visible-tile renderer, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note.

## 29. Batch 180 Note
- `Batch 180` stayed on the executable startup/runtime frontier. The active work moved the direct `a` game route from a `sub_416850` visible-tile-rendering crash to a CTest-covered liveness milestone, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note.

## 30. Batch 181 Note
- `Batch 181` stayed on the executable startup/runtime frontier. The active work repaired reached world-map action-widget, redraw-loop, fade-loop, diagnostic-loop, and turn-advance decompiler scars, but it did not promote any new unit-type or stat semantics; the unit/stat artifacts remain unchanged apart from this maintenance note.

## 31. Batch 182 Note
- `Batch 182` stayed on the executable startup/runtime frontier. The active work moved the direct `/A0` scenario-start route through map loading, player-state seeding, first unit creation, minimap creation, and vision propagation under a headless timeout smoke, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 32. Batch 183 Note
- `Batch 183` stayed on the executable startup/runtime frontier. The active work repaired reached army-fact, unit-stack merge, fact-retract, and unit-stack delete decompiler scars on the direct `/A0` route, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 33. Batch 184 Note
- `Batch 184` stayed on the executable startup/runtime validation frontier. The active work added CTest liveness coverage for the direct `/A0` route on both executable paths, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 34. Batch 185 Note
- `Batch 186` stayed on the first-campaign executable/runtime frontier. The active work repaired the reached mission-0 battle transition and GodAnger visual-effect stack-buffer path; no new unit type, category, stat, or relationship semantics were promoted.
- `Batch 185` stayed on the executable startup/runtime frontier. The active work repaired the reached direct `/A0` new-turn corridor across parser/fact queue coalescing, building population/plague/technology updates, garrison morale delta handling, prisoner castle placement, unit fatigue/morale predicates, queen birth/marriage/departure timing, and low32 allocator pressure. This did not promote any new unit-type or stat semantics; the only unit-facing semantic guard added in this wave is the explicit `UNIT_TYPE_COUNT` bound and invalid trailing-slot sentinel handling, leaving the recovered roster names, stats, relationships, and confidence levels unchanged.

## 35. Batch 186 Note
- `Batch 186` stayed on the executable startup/runtime frontier. The active work repaired the reached render companion surface construction path for longer direct `/A0` liveness by reconstructing the `sub_4041D0` / `sub_473320` DirectDraw descriptor and creation call. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 36. Batch 187 Note
- `Batch 187` stayed on the executable startup/runtime frontier. The active work clarified the direct `/A0` route as an all-AI/autoplay turn-advance path by renaming `sub_44C410` and removing undefined decompiler locals from `Game_AdvanceToNextPlayerTurn`. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 37. Batch 188 Note
- `Batch 188` stayed on the executable startup/runtime frontier. The active work removed reached `PlayGame` setup/loop/teardown register-loss scars and named the world-map theme selector at `gameData + 140016`, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 38. Batch 189 Note
- `Batch 189` stayed on the executable startup/runtime frontier. The active work restored the asm-backed minimap frame sprite draw in `MiniMap_CreateSurface`, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 39. Batch 190 Note
- `Batch 190` stayed on the executable startup/runtime frontier. The active work guarded the `Render_FillRect` primary-surface fallback during SIGTERM/mode-switch teardown, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 40. Batch 191 Note
- `Batch 191` stayed on the executable startup/runtime frontier. The active work set SDL's no-signal-handlers hint before `SDL_Init` so `/A0` terminates under plain POSIX `SIGTERM`, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 41. Batch 192 Note
- `Batch 192` stayed on the executable front-end and human-route frontier. The active work rebuilt the campaign-choice widget blob and repaired the first campaign selector callback so the real main-menu Campaign path can reach `Scenario_LoadMissionByIndexAndPlay` with a human-controlled player. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 42. Batch 193 Note
- `Batch 193` stayed on the executable front-end and human-route frontier. The active work removed remaining decompiler ghost operands from the campaign submenu branch, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 43. Batch 194 Note
- `Batch 194` stayed on the executable front-end and human-route frontier. The active work removed top-level main-menu prologue ghost operands around intro render-hook state, menu allocations, first-frame pumps, and submenu sprite allocations, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 44. Batch 195 Note
- `Batch 195` stayed on the executable front-end and human-route frontier. The active work restored the Options/Load `.s32` menu resource strings and removed additional decompiler ghost operands from those submenu setup and polling paths, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 45. Batch 203 Note
- `Batch 203` stayed on the SDL executable front-end input frontier. The active work made real top-level main-menu mouse input responsive through the SDL/X11 fallback corridor and proved an Exit-button click from a real Xvfb window reaches the recovered widget loop, but it did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 46. Batch 204 Note
- `Batch 204` stayed on the executable front-end and campaign session-route frontier. The active work drove real Xvfb input through the Campaign menu into `Scenario_LoadMissionByIndexAndPlay -> sub_462480 -> UI_WaitForAnyKeyOrClick` and repaired reached render dispatch, file-copy, callback-pointer, PCX-palette width, army-fact strength sync, `createCastle`, and mission-fact logging hazards. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 47. Batch 205 Note
- `Batch 205` stayed on the executable front-end / human-turn runtime recovery frontier. The active work drove real Xvfb input through Campaign, skip-clicked mission/status panels, reached the live world-map human-turn loop, and repaired reached info-window, text-layout, palette-fade, unit-redraw, and animated-tile runtime hazards. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 48. Batch 206 Note
- `Batch 206` stayed on the executable first-mission rendering/runtime frontier. The active work repaired the turn-banner-to-world-map palette handoff by fixing the fade source palette, presenting primary saveback through the SDL indexed surface seam, and preserving/restoring the primary and world-map pixel buffers around transient `tura*.gfx` loads. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 49. Batch 207 Note
- `Batch 207` stayed on the executable first-mission castle-management frontier. The active work proved the real world-map click route into `Building_GetInto -> Castle_OpenManagementScreen` and restored the castle composite palette handoff into `byte_526A70`, eliminating the black castle-screen fade. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 50. Batch 208 Note
- `Batch 208` stayed on the executable first-mission castle-management frontier. The active work recovered the economy panel resource load, widget table, transfer-target list storage/draw path, and tested Back/list-arrow interaction from the real first-mission castle route. It did not promote any new unit-type or stat semantics; the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 51. Batch 212 Note
- `Batch 212` stayed on the executable first-mission playable-action frontier. The active work repaired reached stack movement predicates and `UnitStack_ExecuteQueuedPath` enough for a real-input first-mission owned stack to move from `(31,44)` to `(31,45)` through the authentic world-map path. This did not promote new unit-type or stat semantics; the only category rule touched was the already-known normal-combat exclusion for type ids `31..34`, and the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 52. Batch 214 Note
- `Batch 214` stayed on the executable first-mission playable-action frontier. The active work only stretched pending SDL host-click fallback pulses across multiple recovered input polls so real X11 clicks are less likely to be missed by the world-map handler; it did not promote any new unit-type or stat semantics, and the recovered roster names, stats, relationships, and confidence levels remain unchanged.

## 53. Batch 215 Note
- `Batch 215` stayed on the executable first-mission playable-action frontier. The active work added an opt-in Xvfb/xdotool CTest harness for the real-input first-mission movement route, but it did not recover or promote any new unit-type or stat semantics; the roster names, stats, relationships, and confidence levels remain unchanged.

## 54. Batch 216 Note
- `Batch 216` stayed on the executable first-mission playable-action frontier. The active work only hardened the opt-in real-input movement smoke with route breadcrumbs, process-group cleanup checks, and optional frame-capture assertions; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 55. Batch 217 Note
- `Batch 217` stayed on the executable first-mission playable-action frontier. The active work only hardened the opt-in Xvfb startup path and smoke diagnostics for the real-input movement harness; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 56. Batch 218 Note
- `Batch 218` stayed on the executable first-mission playable-action frontier. The active work only added artifact preservation and richer expected-log assertions to the opt-in real-input movement smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 57. Batch 219 Note
- `Batch 219` stayed on the executable first-mission playable-action frontier. The active work only added frame counting and optional all-black-frame rejection to the opt-in real-input movement smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 58. Batch 220 Note
- `Batch 220` stayed on the executable first-mission playable-action frontier. The active work only added an opt-in second-action phase and timing controls to the real-input movement smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 59. Batch 221 Note
- `Batch 221` stayed on the executable first-mission playable-action frontier. The active work only tightened successful-run cleanup in the opt-in real-input movement smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 60. Batch 222 Note
- `Batch 222` stayed on the executable first-mission playable-action frontier. The active work only isolated the opt-in real-input movement CTest with serial execution and manual/real-input labels; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 61. Batch 223 Note
- `Batch 223` stayed on the executable first-mission playable-action frontier. The active work only added a disabled-by-default end-turn phase to the opt-in real-input smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 62. Batch 224 Note
- `Batch 224` stayed on the executable first-mission playable-action frontier. The active work only added disabled-by-default post-end-turn skip clicks to the opt-in real-input smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 63. Batch 225 Note
- `Batch 225` stayed on the executable first-mission playable-action frontier. The active work only added expected-log assertion presets to the opt-in real-input smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 64. Batch 226 Note
- `Batch 226` stayed on the executable first-mission playable-action frontier. The active work only documented the opt-in real-input smoke controls inside the harness script; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 65. Batch 227 Note
- `Batch 227` stayed on the executable first-mission playable-action frontier. The active work only added a CTest-wired playability-probe wrapper around the opt-in real-input smoke; it did not recover or promote any new unit-type or stat semantics, and the roster names, stats, relationships, and confidence levels remain unchanged.

## 52. Batch 213 Note
- `Batch 213` stayed on the executable first-mission split-move frontier. The active work repaired the selected-slot split validator/executor enough for stack `1` at `(31,44)` to detach selected slot `0` into new stack `10` at `(31,45)` under GDB validation. This did not promote new unit-type or stat semantics; the repaired code only moves already-selected 31-byte unit slots and leaves recovered roster names, stats, relationships, and confidence levels unchanged.

## 53. Batch 214 Note
- `Batch 214` stayed on the executable first-mission playable-action frontier. The active work removed the reached selected-stack panel `memset_` scars and proved a pure real-input split move through the authentic Next Unit and selected-slot UI route. This did not promote new unit-type or stat semantics; no unit roster, stat table, category, or relationship interpretation changed.
### 2026-04-25 Runtime Batch Note
- No new unit-type or unit-stat semantics were recovered in this batch.
- Runtime frontier moved in the tactical-entry path: the PCX palette loader now follows the recovered `gfx\\pal_grey.pcx` evidence, and unit/stat conclusions remain unchanged pending the next successful mission smoke.
### Batch 233 - First-mission end-turn GDB breakpoint script
- Stayed on executable first-mission playable-turn recovery. Added a GDB breakpoint script for the suspected end-turn evidence chain: `UI_CheckEndTurnHotkey`, `Game_AdvanceToNextPlayerTurn`, and `UI_LoadTurnBannerGfx`.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The recovered roster/stat confidence remains unchanged.
- Validation remains blocked in this session by WSL `E_ACCESSDENIED`; the breakpoint script is queued for the next runnable WSL/SDL pass.

### Batch 234 - First-mission playable split action
- Stayed on executable first-mission playability. The real-input route now reaches the first human turn, selects owned stack `1` at `(31,44)` through the authentic Next Unit widget, toggles selected slot `0`, and completes a split move to `(31,45)`.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. This validates movement of already recovered stack/slot records and leaves roster/stat confidence unchanged.
- Remaining gameplay semantics are unchanged: end-turn, combat/building interaction, repeated turns, and full mission completion are still outside the claimed unit/stat evidence.

### Batch 235 - Mission objective gate correction
- Stayed on executable first-mission completion recovery. The active-mission human-turn exit callsite now names `sub_460270` as `Mission_CheckObjectiveComplete`, reflecting its switch over `ACTIVE_MISSION_INDEX`.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. For mission `0`, the gate checks remaining player-1 unit stacks; that uses existing stack ownership evidence and does not change roster/stat interpretation.
- The next unit/stat-adjacent frontier is objective/combat execution evidence only if it exposes new unit relationships; otherwise roster/stat confidence remains unchanged.

### Batch 236 - First-mission enemy attack probe
- Stayed on executable first-mission completion recovery. The real-input route now selects split stack `10` and reaches the recovered strategic `Unit_Attack` path against owner-1 stack `3` at `(46,45)`.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The attack probe uses already recovered stack owner, tile, slot-count, and normal-combat predicates; roster/stat confidence remains unchanged.
- New diagnostics around defeated-stack capture and kill paths are for future combat/objective evidence. They do not change any unit/stat interpretation until a run actually mutates or removes stacks through those branches.

### Batch 237 - First-mission autoresolve combat return
- Stayed on executable first-mission completion recovery. The real-input route now clicks the recovered battle prompt, runs autoresolve against owner-1 stack `3`, and returns from `Unit_Attack` with the defender squad count reduced to zero.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The score-helper repairs only remove decompiler scars around already identified metadata fields such as base action points and do not change roster/stat confidence.
- Mission `0` now advances its objective blocker from stack `3` at `(46,45)` to stack `4` at `(15,6)`. That is runtime objective-flow evidence, not a new unit/stat interpretation.

### Batch 238 - First-mission tactical battle entry and return
- Stayed on executable first-mission completion recovery. The real-input route now enters authentic tactical battle UI from the recovered `Unit_Attack` path, reaches the tactical turn loop after input widgets, and returns from battle without the previous post-return resource/allocator abort.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The repaired selected-unit panel, tactical grid, banner, idle-animation walker, and post-battle resource reload expose runtime stability, not new roster/stat meanings.
- The tactical frame evidence confirms already recovered unit slots can be presented in battle, but selected-unit panel stat text formatting and broader tactical action callbacks remain deferred before promoting any additional unit/stat semantics.

### Batch 232 - End-turn hotkey probe hook
- Stayed on executable first-mission playable-turn recovery. Added an optional hotkey injection point before the end-turn click route so future runs can probe the suspected `UI_CheckEndTurnHotkey` path without harness edits.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The recovered roster/stat confidence remains unchanged.
- Validation remains blocked in this session by WSL `E_ACCESSDENIED`; the actual end-turn key/button condition is still unproven.

### Batch 231 - End-turn route evidence checkpoint
- Stayed on executable first-mission playable-turn recovery. Consolidated connector-backed evidence for the likely human end-turn path: `UI_CheckEndTurnHotkey` as the UI-side candidate, `Game_AdvanceToNextPlayerTurn` as the turn-advance target, and `UI_LoadTurnBannerGfx` as the expected visual transition corridor.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The recovered roster/stat confidence remains unchanged.
- Validation remains blocked in this session by WSL `E_ACCESSDENIED`; exact hotkey/body evidence and runtime assertions remain deferred.

### Batch 230 - Host-click pulse trace gate
- Stayed on executable first-mission playable-turn recovery. Added an env-gated SDL fallback-input trace for host-click pulse state so the next real-input run can separate input sampling failures from movement helper failures.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The recovered roster/stat confidence remains unchanged.
- Validation remains blocked in this session by WSL `E_ACCESSDENIED`; the trace is diagnostic-only until a real WSL/SDL run captures logs and nonblank frames.

### Batch 229 - First-mission turn probe wrapper
- Stayed on executable first-mission playable-turn recovery. Added a manual turn probe that extends the real-input first-mission smoke through second-action, end-turn, and post-end-turn skip checks when host validation is available.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The recovered roster/stat confidence remains unchanged.
- Validation remains blocked in this session by WSL `E_ACCESSDENIED`; the turn probe is a future validation gate, not a claimed playable mission milestone.

### Batch 228 - Playability probe skip handling
- Stayed on executable first-mission playable-action recovery. The new CTest-wired playability probe now inherits the smoke script's skip-code behavior for hosts that cannot run the real-input route.
- No new unit-type, unit-stat, category, or relationship semantics were promoted. The recovered roster/stat confidence remains unchanged.
- Validation is still blocked in this session by WSL `E_ACCESSDENIED`; a future pass must run the probe under WSL/SDL and inspect nonblank presented frames before claiming progress toward a playable first mission.
## 2026-05-05 Runtime-Route Note

- No unit-type or stat semantics were changed in this batch.
- Runtime evidence still uses mission-0 blocker stack identities as route targets only: stack5 at tile 48,14 and stack6 at tile 35,11 were exercised through authentic `enemy_attack_call`/mission-objective logging. Stack7/8/9 remain route targets to validate, not recovered unit/stat semantic claims.
- JSON unit/stat artifacts were intentionally left untouched while WSL read/validation access is blocked, to avoid unvalidated structure churn.
# 2026-05-11 stack6 runtime probe note

This batch did not add new unit type or stat recoveries. Work stayed on the first-mission runtime path and stack6 manual battle harness so the recovered tactical loop can be driven through SDL input instead of autoresolve.

# 2026-05-11 barracks UI runtime note

This batch did not add new unit type or stat recoveries. Work stayed on the castle-management to barracks/garrison UI runtime path: the dialog now presents through recovered SDL rendering enough to show the 12-slot barracks layout, but the visible roster/stat meanings and slot-action semantics remain unchanged pending deeper interaction evidence.

# 2026-05-11 barracks slot-text runtime note

This batch did not promote new unit type or stat meanings. It only repaired reached barracks UI text plumbing so already-known unit-slot fields display correctly: slot health at `slot +9`, building funds at `building +438`, and existing recovered stat helpers in the selected-unit panel. The selected slot in the current probe is identified as `Builder` through the existing `UnitType_GetLocalizedName` helper, not as a new semantic recovery.

# 2026-05-11 barracks selected-detail runtime note

No new unit type or stat meanings were promoted in this batch. Work stayed on executable UI/runtime stability: the fresh `bin/clash95_bootstrap` route now survives the minimap viewport-box draw, opens the barracks dialog, and drives the right-click selected-detail path for the already recovered `Builder` slot. The remaining visual-detail issue is a presentation/copy/palette frontier, not new roster/stat evidence.

# 2026-05-11 save-slot DAT format note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work recovered and documented the save-slot DAT container shape: a 16-byte label followed by the raw `gameData` image, with rules facts stored in the companion `.fac` file. Existing unit stack and slot regions are only reported by the new read-only parser using previously recovered offsets.

# 2026-05-28 mission-01 bridge route note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on executable campaign routing: a builder-containing stack now executes queued bridge-terrain steps consistently with the recovered bridge-aware path-generation seam, and mission `01` completes through authentic barracks release, turn advancement, bridge movement, and shrine entry. The only unit-related fact used here is the existing `UnitStack_HasBuilder` predicate; roster/stat confidence remains unchanged.

# 2026-06-03 mission-02 Treg Rock route note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on executable campaign routing and rules-fact recovery: mission `02` now completes through authentic stack movement/rest cycles and Treg Rock castle capture, while `BuildingRecord.castle_fact_id` handling was repaired for direct mission capture paths. Roster/stat confidence remains unchanged.

# 2026-06-04 mission-03 survival route note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on executable campaign routing and the world-map input/cursor seam: mission `03` now completes by authentic turn advancement through the recovered top-menu path until the existing survival objective sees `GAME_TURN_COUNTER > 10`. Roster/stat confidence remains unchanged.

# 2026-06-04 artifact retention controls note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on campaign-route harness hygiene: durable route artifacts now retain bounded frame/log evidence and prune old runs so long playable-campaign probes remain diagnosable without unbounded `artifacts/` growth.

# 2026-06-05 repo-wide artifact pruning note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on harness hygiene: `tests/prune_artifacts.sh` can dry-run or explicitly apply cleanup of recognized durable probe run directories under repo-owned `artifacts/` roots, with optional whole-folder byte caps.

# 2026-06-15 mission-04 tactical gate attack note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on executable tactical-battle routing for mission `04`: the castle gate click now reaches `UnitBattle_AttackWall`, exercises the already recovered wall-attack metadata path, returns from the attack animation, and presents a nonblank tactical frame. The exact gate durability, repeat-attack count, breach/capture route, and objective-completion sequence remain deferred route work rather than new unit/stat semantics.

# 2026-06-15 campaign route visual regression note

No new unit type, stat, category, or relationship meanings were promoted in this batch. Work stayed on deterministic route-test protection: retained SDL frame dumps now receive loose visual assertions and opt-in campaign route CTest entries protect the already recovered direct-route milestones. Roster/stat confidence remains unchanged.

# 2026-07-10 centisecond timer and mission-04 frontier note

No new unit type, stat, category, or relationship meanings were promoted in
Batch 258. The assembly-backed startup timer now runs at 100 Hz and the UI wait
helpers preserve their real delay/deadline values; this changes runtime pacing,
not unit semantics. The strongest retained mission `04` diagnostic reaches a
second castle assault and returns with three defenders remaining, which is
route/capture evidence only. Roster/stat confidence and all ambiguous unit
candidates remain unchanged.

# 2026-07-12 mission-04 completion route note

No new unit type, stat, category, or relationship meanings were promoted in
Batch 259. The recovered route now clears Hopenberg over three authentic
tactical assaults, captures the empty-garrison castle, and reaches the natural
mission-04 objective check. Dynamic deployment changed the clicked infantry's
tactical slot index between retained runs, so the harness resolves that runtime
occupant index instead of assigning a new unit identity. The next-frontier
mission-05 audit recovered language-dependent player-elimination and friendly-
attack failure predicates, not unit semantics. Roster/stat confidence and all
ambiguous unit candidates remain unchanged.

# 2026-07-14 executable-backed unit metadata core

High-confidence structural and numeric recovery was promoted for the existing
`UnitTypeMetadataRecord` family. The original globals beginning at VA
`0x00512570` are field aliases into records whose base is `0x00512568` and whose
stride is 88 bytes; they are not independent one-element arrays. The original
PE maps DGROUP VMA `0x004EC000` to file offset `0x000EA200`, placing the record
table at file offset `0x00110768`. Direct bytes from all 35 records now back the
runtime animation, flags, combat/AP/range, road-cost, and eight surface-cost
fields at offsets `+8..+37`.

The Mission 05 blocker made the false reconstruction observable. Player-0
stack 4 contains type 17, whose exact recovered core is movement step `3`,
movement tick `3`, animation interval `10`, attack/shot frames `8/8`, flags
`0`, melee `1`, defence `1`, base AP `26`, shot/ranges `0/0/0`, wall attack
`1`, road cost `3`, and surface costs `{4,6,5,0,7,0,8,0}`. The mixed stack's
live AP floor is therefore `20`, not the earlier host-memory artifact `255`.
That correction removes the invalid tactical animation frame count that had
eventually requested sprite character `50` and crashed the first direct
exchange.

The exact 35-row numeric table is in `UNIT_TYPES_AND_STATS.json` under
`unit_type_runtime_core_table`. The record tail `+38..+87` remains explicitly
unrecovered in the new C representation even though separately recovered late
field semantics remain documented above. This batch does not claim that the
whole 88-byte initialized record has been materialized yet.
