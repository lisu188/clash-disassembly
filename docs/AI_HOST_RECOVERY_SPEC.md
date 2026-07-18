# AI host-function recovery spec (C-B2)

Byte-identity-ready wrapper C for the 87 unrecovered CLIPS AI host handlers
(the `_UNKNOWN Rules_Host*;` data placeholders). Produced 2026-07-18 by a
20-agent workflow: 10 agents authored wrappers from `clash95.asm` + the PE,
10 independently re-derived each from the asm to verify (adversarial).
Every handler is the template shape
(`src/strategic/004506B0_004530D0_strategic_001.c:1464`): read args with
`Rules_RtnLong(k, 0, a2)` and tail-call an already-recovered inner function.

**Totals:** 87 handlers | 79 clean thin-wrappers,
verify-confirmed | 8 need manual review (complex shape or a
verify flag). This turns C-B2 from open-ended RE into mechanical application
under the re-baseline gate flow (obj_diff add-only + link-surface
data→function; see the roadmap plan's C-B2 section).

**STATUS: flow PROVEN, 1/87 recovered.** `Rules_HostUnitCountInTroop` landed
(commit `fef99dd`) validating the full execution playbook below end-to-end:
split audit PASS, full build links clean, gcc link-surface diffs=0, direct-a +
/A5 no-crash. The scripted steps (move decl-DB global→function, add manifest
entry + shrink the registration range, migrate link-surface data→text) are in
`scratchpad/`. Two caveats confirmed live: (1) the audit TOLERATES partial-blob
recovery (gaps for still-unrecovered handlers are fine — recover incrementally),
and (2) link-surface `--mode update` is blocked locally by a pre-existing
83-error manifest crosscheck (a build-config artifact on the clean tree), so the
baseline is hand-migrated locally and must be reverified in CI's production
build config. Remaining: 86 handlers, same flow.

## Compile prerequisites (do these first)

- **`Rules_RtnDouble`** (float/double arg reader, `sub_4811C0`) is declared
  only in `src/media/media_internal.h`; the float-arg handlers need it in
  `media_api.h` (or a local extern). Handlers: `Rules_HostChangeTax`.
- **`Rules_RtnLexeme`** (string arg reader, `sub_481100`,
  `src/media/0047F820_00481100_media_016.c:1427`) is needed for string-arg
  handlers: `Rules_HostBuildCastle`.
- Some inner-function prototypes were collapsed by the decompiler and must be
  corrected to accept the real arg count before the wrapper compiles
  (flagged per-handler below), e.g. `Rules_BuildCastle` 4→5 params.
- Per-handler gate flow (each is a data→function migration): recover body →
  `update_split_manifest_hashes.py --update` → `audit_split_sources.py` →
  obj_diff (add function section, remove the `_UNKNOWN` byte; reviewed) →
  `check_link_surface.py --mode update` (data→function; reviewed) → dual
  builds + ratchet. Batch ~12/commit per the plan.

## Execution mechanics (verified 2026-07-18) — this is manifest surgery

The 87 handlers are NOT standalone in the recovered build; they are packed
INSIDE two dispatcher blobs the decompiler lumped together (no direct calls to
the handler entries — only data refs from the registration table), and the
manifest currently mis-attributes each whole blob to its registration function:
- `Rules_RegisterStrategicActionHostFunctions` — manifest range
  **[0x452390..0x4530A0]**, but the registration calls only occupy
  0x452390..**0x452753**; the 26 strategic handlers (loc_452753..loc_45303F)
  fill the rest.
- `Rules_RegisterBuildingHostFunctions` — manifest range **[0x4561B0..0x4570E3]**,
  registration calls first, then the building handlers (loc_456706..loc_457789).

The recovered C for those two "functions" (the `Rules_RegisterHostFunction(...)`
calls) reproduces only the FIRST part of each blob; the handler bytes are NOT in
the recovered binary — each handler exists solely as a 1-byte `_UNKNOWN
Rules_HostX;` DATA global in the state TU (decl-DB `globals`, owner =
recovered_state.c). Recovery is therefore **purely additive** (the plan's
"add-only obj_diff sections"):

1. Add each handler function body (from this spec) into the owning strategic TU
   (`004506B0_004530D0_strategic_001.c` for the 0x452xxx set,
   `00455740_004582B0_strategic_003.c` for the 0x456xxx set), ordered by
   address so they compile at their original offsets.
2. **Shrink the registration function's manifest range** to end at the first
   handler (strategic: `end_exclusive` 0x4530A0 → 0x452753) and **add a manifest
   `functions` entry per handler** (name, original_address, range to the next
   handler, source, linkage external, subsystem, state_owner, body_sha256 via
   `update_split_manifest_hashes.py`).
3. **Move each symbol from decl-DB `globals` → `functions`** (drop the
   `extern _UNKNOWN Rules_HostX;` global, add
   `int Rules_HostX(int, double);` under functions with `home: strategic`),
   and delete the `_UNKNOWN Rules_HostX;` definition from recovered_state.c.
4. `gen_subsystem_headers.py --write`; build.
5. **obj_diff** — reviewed re-baseline: the strategic TU gains handler function
   sections (add-only), the registration function's compiled range shrinks; the
   state TU loses the `_UNKNOWN` bytes. Re-snapshot after review.
6. **`check_link_surface.py --mode update`** — each handler symbol migrates
   data (D, state TU) → text (T, strategic TU); reviewed.
7. Dual builds + warning ratchet + ctest.

Byte-identity to the ORIGINAL is verified MANUALLY (the per-handler asm analysis
in this spec) — obj_diff is snapshot-relative (guards refactors), it does NOT
compare against the original binary. The registration-function split point
(0x452753 strategic) must be confirmed by building and checking where the
recovered registration function's code actually ends. Do this SEQUENTIALLY (the
manifest / link-surface / obj_diff snapshot are shared global state — not
parallelizable); one dispatcher blob (strategic first) per batch.

## First batch to make the AI visibly move

One movement rule (`maszeruj`) needs its whole dependency set recovered
together. Minimal set (all thin-wrappers, all verified): `Rules_HostMarch`,
`Rules_HostRoadExists`, `Rules_HostRoadExistsNearby`, `Rules_HostFordExists`,
`Rules_HostDistanceFromObject`, `Rules_HostArmyExists`,
`Rules_HostTroopInArmyRange`, `Rules_HostUnitCanMove`, plus the turn/economy
queries the LHS reads (`Rules_HostTurnNumber`, `Rules_HostPeasantCount`,
`Rules_HostArmyHasBuilder` [done]). Recover those, rebuild, re-run the QEMU
tile comparison: the all-AI camera should follow AI marches and the fog-edge
tiles should resolve.

## Handler table

| loc | target symbol | H/L name | ret | args | inner fn | shape | verified |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `loc_452753` | `Rules_HostTemple` | swiatynia | i | 2 | `_plib_malloc_` | thin-wrapper | yes |
| `loc_45279F` | `Rules_HostDigTreasure` | kop_skarb | i | 1 | `_plib_free_` | thin-wrapper | yes |
| `loc_4528AB` | `Rules_HostRoadExists` | jest_droga | int | 3 | `sub_453110` | thin-wrapper | yes |
| `loc_452907` | `Rules_HostRoadExistsNearby` | jest_droga_w_poblize / jest_droga_w_poblize00 | b (int) | 3 | `Rules_QueuePathNearTile` | thin-wrapper | yes |
| `loc_452963` | `Rules_HostRoadExistsNearCastle` | jest_droga_w_poblize_zamku | b | 3 | `Rules_QueuePathNearCastle` | thin-wrapper | **NO** |
| `loc_4529BF` | `Rules_HostRoadExistsToPort` | jest_droga_do_portu | b | 3 | `sub_453600` | thin-wrapper | yes |
| `loc_452A1B` | `Rules_HostRoadExistsToCastle` | jest_droga_do_zamku (C-name jest_droga_do_zamku00) | int | 3 | `sub_453770` | thin-wrapper | yes |
| `loc_452A77` | `Rules_HostRoadExistsToTemple` | jest_droga_do_swiatyni | int | 3 | `Move_IsAtTargetOrCanStay` | thin-wrapper | yes |
| `loc_452AD3` | `Rules_HostTroopInArmyRange` | oddzial_w_zasiegu_armii | b | 3 | `Rules_QueuePathIntoArmyRange` | thin-wrapper | yes |
| `loc_452B2F` | `Rules_HostBuildingInArmyRange` | budowla_w_zasiegu_armii / budowla_w_zasiegu_armii00 | b (int) | 3 | `Move_TryApproachTarget` | thin-wrapper | yes |
| `loc_452B8B` | `Rules_HostDistanceFromObject` | odleglosc_od_obiektu | i | 3 | `sub_453E60` | thin-wrapper | yes |
| `loc_452BE7` | `Rules_HostTempleInArmyRange` | swiatynia_w_zasiegu_armii | b | 3 | `sub_453FE0` | thin-wrapper | yes |
| `loc_452C43` | `Rules_HostTempleOk` | swiatynia_OK | int | 3 | `Move_CanEnterTile` | thin-wrapper | yes |
| `loc_452C9F` | `Rules_HostMarch` | maszeruj / maszeruj00 | i (int) | 3 | `Move_CommitIfWithinCost` | thin-wrapper | yes |
| `loc_452CFB` | `Rules_HostMarchToTemple` | maszeruj_do_swiatyni | i | 3 | `Rules_MarchToTemple` | thin-wrapper | yes |
| `loc_452D57` | `Rules_HostMarchNear` | maszeruj_blisko | i | 3 | `sub_454590` | thin-wrapper | yes |
| `loc_452DB3` | `Rules_HostAttackTroop` | atakuj_oddzial (C-name atakuj_oddzial00) | int | 2 | `sub_4547F0` | thin-wrapper | yes |
| `loc_452DFF` | `Rules_HostCaptureTroop` | przejmuj_oddzial | int | 2 | `sub_454800` | thin-wrapper | yes |
| `loc_452E4B` | `Rules_HostHideTroop` | ukryj_oddzial | i | 3 | `Rules_HostUnitMoveAndHide` | thin-wrapper | yes |
| `loc_452EA7` | `Rules_HostArmyExists` | jest_armia / jest_armia00 | b (int) | 1 | `sub_4549A0` | thin-wrapper | yes |
| `loc_452EE3` | `Rules_HostUnitCountInTroop` | liczba_jednostek_w_oddziale | i | 1 | `sub_4549E0` | thin-wrapper | yes |
| `loc_452F1F` | `Rules_HostAttackBuilding` | atakuj_budowle | i | 2 | `sub_454990` | thin-wrapper | yes |
| `loc_452F6B` | `Rules_HostFordExists` | jest_brod | int | 1 | `sub_454A20` | thin-wrapper | yes |
| `loc_452FA7` | `Rules_HostBuildRoad` | buduj_droge / buduj_droge00 | b (int) | 1 | `Rules_BuildRoadOrStepTowardQueuedPath` | thin-wrapper | yes |
| `loc_452FE3` | `Rules_HostBuildTrap` | buduj_pulapke | i | 3 | `Rules_BuildTrapNearTile` | thin-wrapper | yes |
| `loc_45303F` | `Rules_HostUnitCanMove` | Unit_CanMove | i | 1 | `j_Unit_AttemptNeighborMove` | thin-wrapper | yes |
| `loc_456706` | `Rules_HostHealing` | Leczenie (C-name Leczenie) | void | 1 | `sub_455B50` | thin-wrapper | yes |
| `loc_456736` | `Rules_HostTraining` | Szkolenie | void | 1 | `sub_455AD0` | thin-wrapper | yes |
| `loc_456766` | `Rules_HostBurnBuildings` | Pal-Budowle | v | 1 | `Rules_OnCastleUpdate` | thin-wrapper | yes |
| `loc_456796` | `Rules_HostUpgradeWall` | Upgrade-Wall / UpgradeWall | v (void) | 1 | `sub_455450` | thin-wrapper | yes |
| `loc_4567C6` | `Rules_HostChangeTax` | Zmien-Podatek | v | 1 | `sub_455740` | complex | yes |
| `loc_456806` | `Rules_HostRemoveLicence` | Remove-Licence | v | 2 | `sub_455720` | thin-wrapper | yes |
| `loc_456842` | `Rules_HostStartHealing` | Zacznij-Leczenie | void | 2 | `sub_4556C0` | thin-wrapper | yes |
| `loc_45687E` | `Rules_HostStartTraining` | Zacznij-Szkolenie / ZacznijSzkolenie | v (void) | 2 | `Building_TrainUnitByIndex` | thin-wrapper | yes |
| `loc_4568BA` | `Rules_HostStartProduction` | Zacznij-Produkcje | v | 2 | `Building_SetUnitProductionByIndex` | thin-wrapper | yes |
| `loc_4568F6` | `Rules_HostTax` | Podatek | i | 1 | `sub_455470` | thin-wrapper | yes |
| `loc_45692C` | `Rules_HostIsLicence` | Is-Licence (C-name IsLicence) | int | 2 | `sub_4557C0` | thin-wrapper | yes |
| `loc_45696E` | `Rules_HostBuySchool` | Kup-Szkola | int | 1 | `sub_455490` | thin-wrapper | **NO** |
| `loc_4569A4` | `Rules_HostBuyForge` | Kup-Kuznia | b | 1 | `Building_BuildSmithsByIndex` | thin-wrapper | yes |
| `loc_4569DA` | `Rules_HostMoney` | Pieniadze / Pieniadze | i (int) | 1 | `sub_4554F0` | thin-wrapper | yes |
| `loc_456A10` | `Rules_HostWallStrength` | Sila-Murow | i | 1 | `sub_4554D0` | thin-wrapper | yes |
| `loc_456A46` | `Rules_HostCastleStrength` | Sila-Zamku | i | 1 | `sub_455510` | thin-wrapper | yes |
| `loc_456A7C` | `Rules_HostTurnNumber` | Numer-Tury | int | 0 | `Game_GetTurnNumber` | thin-wrapper | yes |
| `loc_456AA8` | `Rules_HostBuildCastle` | Buduj-Zamek / BudujZamek | b (int) | 4 | `Rules_BuildCastle` | complex | yes |
| `loc_456B0D` | `Rules_HostBuyLicence` | Buy-Licence | b | 2 | `Building_BuyUnitLicenceByIndex` | thin-wrapper | yes |
| `loc_456B4F` | `Rules_HostBuyBarracks` | Kup-Koszary | b | 1 | `sub_455530` | thin-wrapper | yes |
| `loc_456B85` | `Rules_HostBuyHospital` | Kup-Szpital (C-name KupSzpital) | int | 1 | `sub_455550` | thin-wrapper | yes |
| `loc_456BBB` | `Rules_HostTechLevel` | Poziom-Tech | int | 1 | `sub_455580` | thin-wrapper | yes |
| `loc_456BF1` | `Rules_HostBuildingType` | Typ-Budowli | i | 1 | `Building_GetTypeByIndex` | thin-wrapper | yes |
| `loc_456C27` | `Rules_HostPlayerStrength` | Sila-Gracza / SilaGracza | i (int) | 1 | `j_AI_TickNationPostTurn` | thin-wrapper | yes |
| `loc_456C5D` | `Rules_HostBuyWorkshop` | Kup-Warsztat | b | 1 | `sub_4555C0` | thin-wrapper | yes |
| `loc_456C93` | `Rules_HostHappiness` | Zadowolenie | i | 1 | `sub_4555E0` | thin-wrapper | yes |
| `loc_456CC9` | `Rules_HostIsProduction` | Is-Production | int | 1 | `sub_455620` | thin-wrapper | yes |
| `loc_456CFF` | `Rules_HostPeasantCount` | Ilosc-Chlopow / IloscChlopow | i (int) | 1 | `Building_GetPeasantCountByIndex` | thin-wrapper | yes |
| `loc_456D35` | `Rules_HostIsMinimal` | Czy-Minimalny | b | 4 | `Map_IsCastleSiteDistanceMinimal` | thin-wrapper | yes |
| `loc_456D8F` | `Rules_HostCanBuyLicence` | Can-Buy-Licence | b | 2 | `sub_455800` | thin-wrapper | yes |
| `loc_456DD1` | `Rules_HostLicenceIndex` | Licencja-Index (C-name LicencjaIndex) | int | 2 | `sub_455850` | thin-wrapper | yes |
| `loc_456E13` | `Rules_HostLicenceInd` | Licencja-Ind | int | 1 | `sub_455890` | thin-wrapper | yes |
| `loc_456E49` | `Rules_HostCanUpgradeWall` | Can-Upgrade-Wall | i | 1 | `Building_CanStartUpgradeByIndex` | thin-wrapper | yes |
| `loc_456E7F` | `Rules_HostTroopCount` | Ilosc-Oddzialow / IloscOddzialow | i (int) | 1 | `sub_455670` | thin-wrapper | yes |
| `loc_456EB5` | `Rules_HostIsProductionAny` | Is-Production-Any | b | 2 | `sub_455E80` | thin-wrapper | yes |
| `loc_456EF7` | `Rules_HostLeadOutPeasants` | Wyprowadz-Chlopow | i | 4 | `sub_455820` | complex | yes |
| `loc_456F51` | `Rules_HostUnitsToSchool` | Jednostki-Do-Szkoly | int | 1 | `sub_4559D0` | thin-wrapper | yes |
| `loc_456F87` | `Rules_HostMaxTroopCount` | Max-Ilosc-Oddzialow / MaxIloscOddzialow | b (int) | 1 | `Building_IsGarrisonFullByIndex` | thin-wrapper | yes |
| `loc_456FBD` | `Rules_HostUnitInCastleExists` | Jest-Jednostka-W-Zamku | b | 2 | `Building_HasGarrisonUnitTypeByIndex` | thin-wrapper | yes |
| `loc_456FFF` | `Rules_HostUnitsToHospital` | Jednostki-Do-Szpitala | b | 1 | `sub_455A50` | thin-wrapper | yes |
| `loc_457035` | `Rules_HostLeadOutTroop` | Wyprowadzenie-Oddzialu (C-name WyprowadzenieOddzialu) | int | 2 | `sub_455BD0` | thin-wrapper | yes |
| `loc_457077` | `Rules_HostLeadOutTroops` | Wyprowadzenie-Oddzialow | int | 1 | `sub_4558D0` | thin-wrapper | **NO** |
| `loc_4570AD` | `Rules_HostCastleName` | Nazwa-Zamku | s | 1 | `Player_GetInternedNameByIndex` | thin-wrapper | yes |
| `loc_457351` | `Rules_HostEnterCastle` | wejdz-do-zamku / WejdzDoZamku | b (int) | 2 | `sub_457A10` | thin-wrapper | yes |
| `loc_457393` | `Rules_HostJoinTroop` | dolacz-do-oddzialu | b | 2 | `sub_457E50` | thin-wrapper | yes |
| `loc_4573D5` | `Rules_HostRegroupTroops` | przegrupuj-oddzialy | b | 2 | `sub_4582B0` | thin-wrapper | yes |
| `loc_457417` | `Rules_HostRegroupCastle` | przegrupuj-zamek | int | 2 | `sub_4589C0` | thin-wrapper | yes |
| `loc_457459` | `Rules_HostArmyHeadcount` | stan-osob-armii / StanOsobArmii | i (int) | 2 | `UnitStack_GetHealthPercentAggregate` | thin-wrapper | yes |
| `loc_45749B` | `Rules_HostArmyHasUnitsOfType` | armia-ma-jednostki-typu | b | 2 | `UnitStack_HasUnitType` | thin-wrapper | yes |
| `loc_45751F` | `Rules_HostCastleFreeSlotCount` | liczba-wolnych-miejsc-w-zamku | i | 1 | `j_Building_GetCapacity` | thin-wrapper | yes |
| `loc_457555` | `Rules_HostEnemyPowerAtWalls` | moc-przeciwnika-pod-murami (C-name MocPrzeciwnikaPodMurami2) | int | 1 | `sub_457C00` | thin-wrapper | yes |
| `loc_45758B` | `Rules_HostFindRoadNearCastle` | znajdz-droge-w-poblize-zamku | int | 2 | `sub_457BA0` | thin-wrapper | **NO** |
| `loc_4575CD` | `Rules_HostHasUnitsToHeal` | ma-jednostki-do-leczenia | b | 1 | `UnitStack_HasUnitsNeedingHealing` | thin-wrapper | yes |
| `loc_457603` | `Rules_HostFindCastleForHealing` | znajdz-zamek-do-leczenia / ZnajdzZamekDoLeczenia | b (int) | 1 | `sub_457860` | thin-wrapper | yes |
| `loc_457639` | `Rules_HostGoToHealing` | idz-do-leczenia | b | 1 | `sub_4579B0` | thin-wrapper | yes |
| `loc_45766F` | `Rules_HostPlagueInCastleExists` | jest-zaraza-w-zamku | b | 1 | `sub_457DA0` | thin-wrapper | yes |
| `loc_4576A5` | `Rules_HostPlagueInTroopExists` | jest-zaraza-w-oddziale | int | 1 | `sub_457DC0` | thin-wrapper | yes |
| `loc_4576DB` | `Rules_HostDetachWeakUnits` | odlacz-jednostki-slabe / OdlaczJednostkiSlabe | b (int) | 1 | `UnitStack_DetachWeakUnitsToAdjacentTile` | thin-wrapper | yes |
| `loc_457711` | `Rules_HostDetachUnitsOfType` | odlacz-jednostki-typu | b | 2 | `UnitStack_DetachUnitTypeToAdjacentTile` | complex | yes |
| `loc_457753` | `Rules_HostMarchAlongRoad` | maszeruj-wzdluz-drogi | b | 1 | `sub_457E00` | thin-wrapper | yes |
| `loc_457789` | `Rules_HostFindBest` | znajdz-najlepszy (C-name Znajdz_Najlepszy) | int | 5 | `sub_459570` | thin-wrapper | yes |

## Needs manual review at re-baseline

### `Rules_HostChangeTax` (loc_4567C6, complex)

```c
void Rules_HostChangeTax(int a1, double a2)
{
  float tax_delta = Rules_RtnDouble(2, 0, a2);
  int building_index = Rules_RtnLong(1, 0, a2);
  (void)a1;
  Building_AdjustTaxRateByIndex(building_index, 0, tax_delta);
}
```

_Notes:_ MANUAL REVIEW. Only handler in this batch that is NOT the uniform int-reader pattern. CLIPS arg2 is a FLOAT read via sub_4811C0 = Rules_RtnDouble (NOT sub_4812C0/Rules_RtnLong): asm does 'mov eax,2; call sub_4811C0; sub esp,4; fstp [esp] (store st0 as 4-byte float)', THEN 'mov eax,1; call sub_4812C0' for the int, so the float is read BEFORE the int -- wrapper preserves that order. Return type is void (v). Inner sub_455740 = Building_AdjustTaxRateByIndex(int building_index, int ebx0, float tax_delta) [src/strategic/00455740_004582B0_strategic_003.c:15/prototype strategic_internal.h:82; body at strategic_003 line ~15]; asm sig 'void __userpurge sub_455740(int@<eax>, int ebx0@<ebx>, float)'. The handler sets eax(building_index) and the stack float(tax_delta) but does NOT load ebx, so the middle 'ebx0' param is an uninitialized register passthrough (used inside the inner as _CHP(ebx0, ...), an x87 codegen artifact); padded to 0 here per house convention. argcount=1 counts only the single sub_4812C0 read; total CLIPS args = 2 (1 int + 1 float). COMPILE PREREQUISITE: Rules_RtnDouble is currently declared only in src/media/media_internal.h, NOT in media_api.h which strategic TUs include -- add its declaration to media_api.h (or a local extern) before this wrapper will build. Registration: strategic_003.c:593 aZmienPodatek/aZmienpodatek -> &Rules_HostChangeTax, a22iif.

### `Rules_HostBuildCastle` (loc_456AA8, complex)

```c
int Rules_HostBuildCastle(int a1, double a2)
{
  char *castle_name = (char *)Rules_RtnLexeme(5, 0, a2);
  int p4 = Rules_RtnLong(4, 0, a2);
  int p3 = Rules_RtnLong(3, 0, a2);
  int p2 = Rules_RtnLong(2, 0, a2);
  int p1 = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return Rules_BuildCastle(p1, p2, p3, p4, castle_name);
}
```

_Notes:_ MANUAL REVIEW. 5 CLIPS args (registration 55iiiiis = 4 int + 1 string). Args 1-4 read via Rules_RtnLong (sub_4812C0) into eax/edx/ebx/ecx; arg 5 (the castle name string) read via a DIFFERENT reader, Rules_RtnLexeme (sub_481100, confirmed at 0x481100 in src/media/0047F820_00481100_media_016.c:1427), and pushed on the stack. argcount field = 4 (the count of Rules_RtnLong reads); total args = 5. Read/eval order in asm is right-to-left: arg5(lexeme) pushed first, then arg4->ecx, arg3->ebx, arg2->edx, arg1->eax; wrapper declares temporaries in that same order to preserve evaluation order, passing positionally. asm token 'call sub_455830'; recovered as Rules_BuildCastle at 0x455830 (strategic_003.c:60). CAVEAT: recovered prototype BOOL Rules_BuildCastle(int building_type, DWORD a2, double a3, char *castle_name) has only 4 params -- the decompiler collapsed the two middle int args (ebx+ecx = args 3&4, 8 bytes) into a phantom 'double a3'. To accept 5 distinct args the prototype must be corrected to (int, int, int, int, char*); wrapper will not compile against the current 4-param declaration. Frame probe push=24h.

### `Rules_HostLeadOutPeasants` (loc_456EF7, complex)

```c
int Rules_HostLeadOutPeasants(int a1, double a2)
{
  int transferGold = Rules_RtnLong(4, 0, a2);     /* CLIPS arg 4 -> ecx -> param 3 */
  int transferAmount = Rules_RtnLong(3, 0, a2);   /* CLIPS arg 3 -> ebx -> param 4 */
  int targetStackIndex = Rules_RtnLong(2, 0, a2); /* CLIPS arg 2 -> edx -> param 2 */
  int buildingIndex = Rules_RtnLong(1, 0, a2);    /* CLIPS arg 1 -> eax -> param 1 */
  (void)a1;
  return Building_Transfer(buildingIndex, targetStackIndex, transferGold, transferAmount, a2);
}
```

_Notes:_ FLAG FOR MANUAL REVIEW - non-obvious arg mapping. asm at clash95.asm:132112. Register-only reverse read: arg4->ecx, arg3->ebx, arg2->edx, arg1->eax. sub_455820 is a bp-frame THUNK (jmp sub_41F1A0); sub_41F1A0 = recovered Building_Transfer(int buildingIndex, int targetStackIndex, int transferGold, int transferAmount, double a5) at src/buildings/0041F1A0_00421010_buildings_002.c:17, __usercall(int@eax,int@edx,int@ecx,int@ebx,double@st0). CRITICAL: the inner's register order is eax,edx,ECX,EBX (param3@ecx, param4@ebx), i.e. NON-standard for the 3rd/4th slots. The handler loads ecx=arg4 and ebx=arg3, so at runtime transferGold(param3)=CLIPS arg4 and transferAmount(param4)=CLIPS arg3 -- args 3 and 4 are SWAPPED relative to positional order. wrapper reproduces the actual register values; do NOT 'fix' it to Building_Transfer(...,arg3,arg4,...). double a5(st0) unset by handler -> threaded host a2. Registration: aWyprowadzchlop -> &Rules_HostLeadOutPeasants, code 105='i', a44i (strategic_003.c:628).

### `Rules_HostDetachUnitsOfType` (loc_457711, complex)

```c
int Rules_HostDetachUnitsOfType(int a1, double a2)
{
  unit_type type;
  int army_index;

  (void)a1;
  type = (unit_type)Rules_RtnLong(2, 0, a2);
  army_index = Rules_RtnLong(1, 0, a2);
  return UnitStack_DetachUnitTypeToAdjacentTile(army_index, type, 0, 0, a2);
}
```

_Notes:_ NEEDS MANUAL REVIEW. asm call target = sub_457FE0 (verified recovered at 00457FE0 = UnitStack_DetachUnitTypeToAdjacentTile(int army_index,unit_type type,int dest_tile_x,int dest_tile_y,double a5), src/strategic/00455740_004582B0_strategic_003.c:960). Registration: strategic_003.c:655 (&Rules_HostDetachUnitsOfType, aOdlaczjednos_0='OdlaczJednostkiTypu', a22i). The handler reads only 2 CLIPS args (22i, reverse: arg2->edx=type, arg1->eax=army_index) but the recovered inner has 5 params. Params 3/4 (dest_tile_x, dest_tile_y) correspond to unloaded scratch registers ebx/ecx and are ALWAYS overwritten before any read inside the inner (assigned in the offset_x/offset_y search loop), so passing 0,0 is behaviorally identical to the asm's undefined-register values. Param 5 'double a5' is the threaded context a2 (forwarded to Unit_MoveSelectionFromGroupToTile). Structurally a single inner call, but flagged complex due to the 2-read-vs-5-param reconstruction of the scratch middle args.

### `Rules_HostRoadExistsNearCastle` (loc_452963, thin-wrapper, VERIFY-FLAGGED)

```c
int Rules_HostRoadExistsNearCastle(int a1, double a2)
{
  int stack_index;
  int castle_x;
  int castle_y;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  castle_x = Rules_RtnLong(2, 0, a2);
  castle_y = Rules_RtnLong(3, 0, a2);
  return Rules_QueuePathNearCastle(stack_index, castle_x, castle_y, a2);
}
```

_Notes:_ asm call target = sub_453440 (verified recovered at 00453440 = Rules_QueuePathNearCastle, src/strategic/00453110_00455720_strategic_002.c:104). Registration: strategic_001.c:1422 (&Rules_HostRoadExistsNearCastle, aJest_droga_w_1='jest_droga_w_poblize_zamku00', a33i). 33i: args read forward 1,2,3 into [ebp-0Ch],[ebp-8],[ebp-4]; call passes eax=arg1,edx=arg2,ebx=arg3. Inner's 4th param 'DWORD a4' is the threaded context slot = a2; passing a2 (double) to a DWORD param yields a double->unsigned conversion (a4 is also overwritten/dead before use inside the inner) -- REVIEW: reviewer may prefer 0 instead of a2 for this DWORD trailing arg.

_Verify flag:_ Structure (inner_fn=sub_453440=Rules_QueuePathNearCastle, 3 forward reads, order eax=stack_index/edx=castle_x/ebx=castle_y, int return) is correct, BUT the note's justification for the 4th arg is false. It claims 'a4 is overwritten/dead before use inside the inner'; in Rules_QueuePathNearCastle (strategic_002.c:104) a4 is only conditionally overwritten at line 116 (inside the if at line 113) and is read LIVE at lines 126-128 (Pathing_EnableBridgeCrossings/Building_GenerateNearApproachTrack/Pathing_DisableBridgeCrossings) on the flag-zero path. a4 is also a DWORD integer scratch, not a forwarded double context like the double-a4 siblings. The asm never loads ecx, so the 4th arg is an undefined register; passing a2 (double->DWORD narrowing) fabricates a defined value the asm lacks, under an incorrect safety rationale. Trailing arg needs conscious review, not the stated 'dead' claim.

### `Rules_HostBuySchool` (loc_45696E, thin-wrapper, VERIFY-FLAGGED)

```c
int Rules_HostBuySchool(int a1, double a2)
{
  (void)a1;
  return Building_BuildSchoolByIndex(Rules_RtnLong(1, 0, a2), 0, 0);
}
```

_Notes:_ FLAG FOR MANUAL BYTE-IDENTITY REVIEW. Registration ret 'b' -> int (strategic_003.c:598). asm reads only 1 arg (eax=arg1) then 'call sub_455490' with EDX/EBX NOT set. sub_455490 is recovered as signed int Building_BuildSchoolByIndex(int building_index, char a2, DWORD a3) at strategic_002.c:1298, which forwards a2/a3 to Building_BuildSchool -> the char/DWORD are real register-passed (EDX/EBX) 'ghost tail' params the loc does not populate. Wrapper 0-fills them following the merged precedent Rules_HostCollectPortSupply -> Rules_PortCollectSupply(0,0,0,0.0) (strategic_001.c:1456). Caveat: 0-fill emits register-zeroing that is NOT in the loc (which leaves EDX/EBX as Rules_RtnLong left them), so this is NOT strictly byte-identical for the ghost tail; verify against object diff, or trim the inner prototype to its true arity.

_Verify flag:_ loc assembles ONLY arg1 (eax); it never sets EDX/EBX before 'call sub_455490'. Inner Building_BuildSchoolByIndex(int, char/*EDX*/, DWORD/*EBX*/) forwards a2/a3 to Building_BuildSchool. Wrapper's (x, 0, 0) invents two args the asm never assembles, emitting register-zeroing (xor edx/ebx) absent from the loc and substituting 0 for the leftover EDX/EBX the asm actually forwards. Not byte-faithful; recoverer self-flagged. Fix: trim inner prototype to arity-1.

### `Rules_HostLeadOutTroops` (loc_457077, thin-wrapper, VERIFY-FLAGGED)

```c
int Rules_HostLeadOutTroops(int a1, double a2)
{
  (void)a1;
  return Building_UnitsLeaveReadyGarrisonSlots(Rules_RtnLong(1, 0, a2), 0, a2);
}
```

_Notes:_ FLAG FOR MANUAL BYTE-IDENTITY REVIEW. Registration ret 'i' -> int, C-name WyprowadzenieOddzialow, symbol &Rules_HostLeadOutTroops (strategic_003.c:630). asm reads only 1 arg (eax=arg1) then 'call sub_4558D0' with EDX not set. sub_4558D0 recovered as signed int Building_UnitsLeaveReadyGarrisonSlots(int building_index, int a2, double a3) at strategic_003.c:104. The middle int a2 (EDX) is an unpopulated 'ghost' register param -> 0-filled per the CollectPortSupply precedent (adds EDX-zeroing not in the loc; verify object diff). The trailing double a3 IS the ambient CLIPS double (ST0), passed byte-free as a2 (loc emits no fp setup).

_Verify flag:_ loc assembles ONLY arg1 (eax); EDX is never set before 'call sub_4558D0'. Inner Building_UnitsLeaveReadyGarrisonSlots(int, int/*EDX*/, double). Wrapper 0-fills the middle int a2, adding register-zeroing not in the loc and passing 0 instead of the leftover EDX the asm forwards. Not byte-faithful (trailing double a3=a2 forwarding is fine). Recoverer self-flagged. Fix: trim ghost EDX param.

### `Rules_HostFindRoadNearCastle` (loc_45758B, thin-wrapper, VERIFY-FLAGGED)

```c
int Rules_HostFindRoadNearCastle(int a1, double a2)
{
  int a4 = Rules_RtnLong(2, 0, a2);
  int a3 = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return UnitStack_QueuePathNearBuilding(a3, a4, 0, 0);
}
```

_Notes:_ FLAG FOR MANUAL BYTE-IDENTITY REVIEW. Registration ret 'b' -> int (strategic_003.c:644). Register-form (no arg spill): asm reads arg2 first into edx (mov eax,2;call;mov edx,eax) then arg1 into eax (mov eax,1;call) then 'call sub_457BA0' -> exactly the reverse-read order of the recovered 2-arg template Rules_HostArmyHasOnlyUnitType (strategic_003.c:1078), hence temporaries a4=arg2 read first, a3=arg1 second. sub_457BA0 recovered as int UnitStack_QueuePathNearBuilding(int stack_index, int building_index, char a3, DWORD a4) at strategic_003.c:786; the trailing char a3 (EBX) and DWORD a4 (ECX) are unpopulated ghost register params, 0-filled per the CollectPortSupply precedent (adds EBX/ECX-zeroing not present in the loc; verify object diff or trim inner prototype).

_Verify flag:_ Read order (arg2->edx then arg1->eax) and 2-int forwarding are correct, but loc never sets EBX/ECX before 'call sub_457BA0'. Inner UnitStack_QueuePathNearBuilding(int, int, char/*EBX*/, DWORD/*ECX*/). Wrapper 0-fills char a3/DWORD a4, emitting xor ebx/ecx absent from the loc and passing 0 vs the leftover EBX/ECX. Not byte-faithful; recoverer self-flagged. Fix: trim ghost EBX/ECX params.

## Clean thin-wrappers (verify-confirmed, ready to paste)

Each is the template shape; inner function and arg order verified against the
asm. Notes carry the exact `sub_XXXX` → recovered-name mapping and any
int→char narrowing / trailing decompiler-artifact params.

### `Rules_HostTemple` (loc_452753, swiatynia, i, 2 args)

```c
int Rules_HostTemple(int a1, double a2)
{
  int tileX = Rules_RtnLong(1, 0, a2);
  int tileY = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return MapTile_GetReligiousSiteCategory(tileX, tileY);
}
```

_Notes:_ Registration confirmed in sub_452390 (mov ecx,offset aSwiatynia00 / mov ebx,offset loc_452753 / mov eax,offset aSwiatynia / call Rules_RegisterHostFunction) -> &Rules_HostTemple, a22i. The asm 'call _plib_malloc_' is an IDA-mislabeled 5-byte COLLAPSED jmp thunk at VA 0x453080 that does 'jmp 0x43FB10'. I resolved this by parsing C:\Clash\clash95.exe (PE imagebase 0x400000): thunk 0x453080 -> 0x43FB10. 0x43FB10 = MapTile_GetReligiousSiteCategory(int tileX, int tileY) [src/buildings/0043E500_0043FDE0_buildings_006.c:1185, prototype in buildings_api.h:154], asm sig 'signed int __usercall sub_43FB10@<eax>(int@<eax>, int@<edx>)'. Handler reads CLIPS arg1 then arg2 (forward order, spilled to [ebp-8]/[ebp-4]), then eax=arg1, edx=arg2 -> f(tileX=arg1, tileY=arg2). wrapper_c uses the resolved semantic name so it compiles; inner_fn field cites the literal asm call token '_plib_malloc_' as instructed.

### `Rules_HostDistanceFromObject` (loc_452B8B, odleglosc_od_obiektu, i, 3 args)

```c
int Rules_HostDistanceFromObject(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int target_x = Rules_RtnLong(2, 0, a2);
  int target_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_GetPathDistanceToObject(stack_index, target_x, target_y, 0);
}
```

_Notes:_ sub_453E60 = Rules_GetPathDistanceToObject(int stack_index, int target_x, int target_y, DWORD a4) [src/strategic/00453110_00455720_strategic_002.c:360, prototype strategic_internal.h:41]; asm sig 'signed int __usercall sub_453E60@<eax>(int@<eax>, int@<edx>, int@<ebx>, DWORD@<ebp>)'. Handler reads args 1,2,3 in order, passes eax=arg1, edx=arg2, ebx=arg3 (matches Rules_HostMarch 3-arg template). The 4th param (DWORD a4) is an ebp-frame IDA artifact not set by the handler; padded to 0 per house convention (cf. Rules_PortCollectSupply(0,0,0,0.0)).

### `Rules_HostUnitCountInTroop` (loc_452EE3, liczba_jednostek_w_oddziale, i, 1 args)

```c
int Rules_HostUnitCountInTroop(int a1, double a2)
{
  (void)a1;
  return UnitStack_GetSquadCountByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ sub_4549E0 = UnitStack_GetSquadCountByIndex(int stack_index) [src/strategic/00453110_00455720_strategic_002.c:695, prototype strategic_internal.h:52]; asm sig 'signed int __usercall sub_4549E0@<eax>(int@<eax>)'. Clean single-arg wrapper, byte-identical to the ArmyHasBuilder template.

### `Rules_HostWallStrength` (loc_456A10, Sila-Murow, i, 1 args)

```c
int Rules_HostWallStrength(int a1, double a2)
{
  (void)a1;
  return Building_GetWallStrengthByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ sub_4554D0 = Building_GetWallStrengthByIndex(int building_index) [src/strategic/00453110_00455720_strategic_002.c:1311, prototype strategic_internal.h:64]; asm sig 'int __usercall sub_4554D0@<eax>(int@<eax>)'. Clean single-arg wrapper. Registration: strategic_003.c:616 -> &Rules_HostWallStrength, a11i.

### `Rules_HostBuyWorkshop` (loc_456C5D, Kup-Warsztat, b, 1 args)

```c
int Rules_HostBuyWorkshop(int a1, double a2)
{
  (void)a1;
  return Building_BuildWorkshopByIndex(Rules_RtnLong(1, 0, a2), 0);
}
```

_Notes:_ sub_4555C0 = Building_BuildWorkshopByIndex(char a1, DWORD a2) [src/strategic/00453110_00455720_strategic_002.c:1360, prototype strategic_internal.h:71]; asm sig 'signed int __usercall sub_4555C0@<eax>(char@<bl>, DWORD@<ebp>)'. Handler reads a single CLIPS int (mov eax,1; call sub_4812C0) and passes it; the inner's 1st param is char (low byte / bl) so the int value narrows on the call, and the 2nd param (DWORD a2) is an ebp IDA artifact padded to 0 per house convention. ret b -> int. Registration: strategic_003.c:605 -> &Rules_HostBuyWorkshop, a11i.

### `Rules_HostIsProductionAny` (loc_456EB5, Is-Production-Any, b, 2 args)

```c
int Rules_HostIsProductionAny(int a1, double a2)
{
  unit_type licence_type;
  int building_index;

  (void)a1;
  licence_type = (unit_type)Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_SelectedUnitLicenceMatchesTypeByIndex(building_index, licence_type);
}
```

_Notes:_ sub_455E80 = Building_SelectedUnitLicenceMatchesTypeByIndex(int building_index, unit_type licence_type) [src/strategic/00455740_004582B0_strategic_003.c:411, prototype strategic_internal.h:99]; asm sig 'BOOL __usercall sub_455E80@<eax>(int@<eax>, int@<edx>)'. Reverse read order: asm reads CLIPS arg2 first (mov eax,2; call; mov edx,eax) then arg1 (mov eax,1; call), passing eax=arg1, edx=arg2 -> f(building_index=arg1, licence_type=arg2). Wrapper mirrors the recovered Rules_HostArmyHasOnlyUnitType precedent (strategic_003.c:1078) exactly: named temps, arg2 read before arg1, unit_type cast on the 2nd param. Note the inner's semantic name (licence-matches-type) differs from the CLIPS name IsProductionAny; the loc->symbol mapping is registration-verified (strategic_003.c:609). ret b -> int (BOOL).

### `Rules_HostJoinTroop` (loc_457393, dolacz-do-oddzialu, b, 2 args)

```c
int Rules_HostJoinTroop(int a1, double a2)
{
  int group_index = Rules_RtnLong(2, 0, a2);
  unsigned int unit_index = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return Script_UnitAddToGroup(unit_index, group_index, 0, 0.0);
}
```

_Notes:_ sub_457E50 = Script_UnitAddToGroup(unsigned int unit_index, int group_index, DWORD a3, double a4) [src/strategic/00455740_004582B0_strategic_003.c:884, prototype strategic_internal.h:116]; asm sig 'int __usercall sub_457E50@<eax>(unsigned int@<eax>, int@<edx>, DWORD@<ebp>, double@<st0>)'. Reverse read order: asm reads CLIPS arg2 first into edx (group_index) then arg1 into eax (unit_index); wrapper reads arg2 before arg1 to match. The trailing DWORD a3 (ebp) and double a4 (st0) are IDA frame/x87 artifacts not set by the handler; padded to 0 and 0.0 per house convention (cf. Rules_PortCollectSupply). ret b -> int. Registration: strategic_003.c:640 aDolaczDoOddzia/aDolaczdoarmii -> &Rules_HostJoinTroop, a22i.

### `Rules_HostGoToHealing` (loc_457639, idz-do-leczenia, b, 1 args)

```c
int Rules_HostGoToHealing(int a1, double a2)
{
  (void)a1;
  return UnitStack_ExecuteHealingPathAndCheckArrival(Rules_RtnLong(1, 0, a2), 0, 0, 0.0);
}
```

_Notes:_ sub_4579B0 = UnitStack_ExecuteHealingPathAndCheckArrival(unsigned int stack_index, char a2, DWORD a3, double a4) [src/strategic/00455740_004582B0_strategic_003.c:747, prototype strategic_internal.h:109]; asm sig 'BOOL __usercall sub_4579B0@<eax>(unsigned int@<eax>, char@<bl>, DWORD@<ebp>, double@<st0>)'. Handler reads a single CLIPS int (eax=arg1 -> stack_index); the trailing char a2 (bl), DWORD a3 (ebp) and double a4 (st0) are register/frame/x87 IDA artifacts not set by the handler, padded to 0, 0, 0.0 per house convention. ret b -> int (BOOL). Registration: strategic_003.c:651 -> &Rules_HostGoToHealing, a11i.

### `Rules_HostDigTreasure` (loc_45279F, kop_skarb, i, 1 args)

```c
int Rules_HostDigTreasure(int a1, double a2)
{
  (void)a1;
  return Treasure_TryDigHere(Rules_RtnLong(1, 0, a2), 0, 0, 0, 0, a2);
}
```

_Notes:_ asm at clash95.asm:124445. Reads 1 CLIPS arg into eax and calls _plib_free_. _plib_free_ is a MISLABELED 5-byte thunk (jmp sub_443C20); sub_443C20 = recovered Treasure_TryDigHere(int a1, char a2, DWORD a3, char a4, char *a5, double a6) at src/persistence/00443BB0_00445CE0_persistence_002.c:29. Handler only sets eax=arg1; the inner's a2..a5 params (char@bl, DWORD@ebp [ebp is the frame pointer -> IDA-spurious], char@dil, char*@esi) are left UNSET by the handler, and st0=a6 carries the host double a2. Filler 0/NULL and trailing a2 supplied so it compiles against the current 6-param prototype; verify whether that prototype should be trimmed. wrapper_c calls the recovered target name, not the _plib_free_ thunk label.

### `Rules_HostTempleInArmyRange` (loc_452BE7, swiatynia_w_zasiegu_armii, b, 3 args)

```c
int Rules_HostTempleInArmyRange(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int temple_x = Rules_RtnLong(2, 0, a2);
  int temple_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_IsTempleWithinArmyRange(stack_index, temple_x, temple_y);
}
```

_Notes:_ asm at clash95.asm:124915. Clean 3-int handler, forward read order (args 1,2,3 spilled to locals then loaded eax=arg1, edx=arg2, ebx=arg3). sub_453FE0 = BOOL __usercall(int@eax,int@edx,int@ebx) = recovered Rules_IsTempleWithinArmyRange(int stack_index, int temple_x, int temple_y) at src/strategic/00453110_00455720_strategic_002.c:414. Register->param mapping is direct 1:1, no swap, no filler. Registration: aSwiatynia_w_za -> &Rules_HostTempleInArmyRange, code 98='b', a33i (strategic_001.c:1429).

### `Rules_HostAttackBuilding` (loc_452F1F, atakuj_budowle, i, 2 args)

```c
int Rules_HostAttackBuilding(int a1, double a2)
{
  int army_index = Rules_RtnLong(1, 0, a2);
  int building_index = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Rules_HostUnitAttackBuilding(army_index, building_index, 0, 0, a2);
}
```

_Notes:_ asm at clash95.asm:125261. Forward read (arg1->[ebp-8], arg2->[ebp-4]; call with eax=arg1, edx=arg2). sub_454990 = signed int __usercall(int@eax,int@edx,char@bl,DWORD@ebp,double@st0) = recovered Rules_HostUnitAttackBuilding(int army_index, int building_index, char a3, DWORD a4, double a5) at src/strategic/00453110_00455720_strategic_002.c:682. Handler sets only eax=arg1, edx=arg2; the inner's char a3 (bl), DWORD a4 (ebp = frame pointer -> IDA-spurious), and double a5 (st0) are UNSET. Filler 0/0 and trailing a2 supplied to compile against the current 5-param prototype; confirm the inner prototype/fillers. Registration: aAtakuj_budowle -> &Rules_HostAttackBuilding, code 105='i', a22i (strategic_001.c:1439).

### `Rules_HostRemoveLicence` (loc_456806, Remove-Licence, v, 2 args)

```c
void Rules_HostRemoveLicence(int a1, double a2)
{
  unit_type licence_type = (unit_type)Rules_RtnLong(2, 0, a2);
  int building_index = Rules_RtnLong(1, 0, a2);
  (void)a1;
  Building_RemoveUnitLicenceByIndex(building_index, licence_type, 0);
}
```

_Notes:_ asm at clash95.asm:131264. VOID return (no eax stored/returned after the call). Register-only reverse read: arg2 computed first into edx, then arg1 into eax (no local spill) -> temporaries ordered to match. sub_455720 = int __usercall(int@eax,int@edx,DWORD@ebp) = recovered Building_RemoveUnitLicenceByIndex(int building_index, unit_type licence_type, DWORD a3) at src/strategic/00453110_00455720_strategic_002.c:1435. building_index=arg1(eax), licence_type=arg2(edx); DWORD a3 (ebp = frame pointer -> IDA-spurious) UNSET -> passed 0. unit_type cast mirrors the recovered sibling Rules_HostArmyHasOnlyUnitType (strategic_003.c:1084). Inner returns int but handler discards it (void). Registration: aRemovelicence -> &Rules_HostRemoveLicence, code 118='v', a22i (strategic_003.c:594).

### `Rules_HostCastleStrength` (loc_456A46, Sila-Zamku, i, 1 args)

```c
int Rules_HostCastleStrength(int a1, double a2)
{
  (void)a1;
  return Building_GetCastleStrengthByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ asm at clash95.asm:131541. Textbook 1-arg thin wrapper (eax=arg1 -> call -> return eax). sub_455510 = int __usercall(int@eax) = recovered Building_GetCastleStrengthByIndex(int building_index) at src/strategic/00453110_00455720_strategic_002.c:1326. No filler, byte-identical to the ArmyHasBuilder template. Registration: aSilazamku -> &Rules_HostCastleStrength, code 105='i', a11i (strategic_003.c:617).

### `Rules_HostHappiness` (loc_456C93, Zadowolenie, i, 1 args)

```c
int Rules_HostHappiness(int a1, double a2)
{
  (void)a1;
  return Building_GetSatisfactionByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ asm at clash95.asm:131824. Textbook 1-arg thin wrapper (eax=arg1 -> call -> return eax). sub_4555E0 = int __usercall(int@eax) = recovered Building_GetSatisfactionByIndex(int building_index) at src/strategic/00453110_00455720_strategic_002.c:1368. No filler, template-identical. Registration: aZadowolenie -> &Rules_HostHappiness, code 105='i', a11i (strategic_003.c:620).

### `Rules_HostRegroupTroops` (loc_4573D5, przegrupuj-oddzialy, b, 2 args)

```c
int Rules_HostRegroupTroops(int a1, double a2)
{
  int stack_b = Rules_RtnLong(2, 0, a2);
  int stack_a = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return UnitStack_RegroupWithOtherStackByHealth(stack_a, stack_b, 0, 0, a2);
}
```

_Notes:_ asm at clash95.asm:132563. Register-only reverse read: arg2->edx first, then arg1->eax (temporaries ordered to match). sub_4582B0 = int __usercall(int@eax,int@edx,char@bl,DWORD@ebp,double@st0) = recovered UnitStack_RegroupWithOtherStackByHealth(int a1, int a2, char a3, DWORD a4, double a5) at src/strategic/00455740_004582B0_strategic_003.c:1135. param1(eax)=arg1, param2(edx)=arg2; char a3(bl), DWORD a4(ebp = frame pointer -> IDA-spurious) UNSET -> 0; double a5(st0) unset -> host a2 threaded. Fillers supplied to compile against current 5-param prototype. Registration: aPrzegrupujarmi -> &Rules_HostRegroupTroops, code 98='b', a22i_0 (strategic_003.c:641).

### `Rules_HostPlagueInCastleExists` (loc_45766F, jest-zaraza-w-zamku, b, 1 args)

```c
int Rules_HostPlagueInCastleExists(int a1, double a2)
{
  (void)a1;
  return Building_GetPlagueState(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ asm at clash95.asm:132878. Textbook 1-arg thin wrapper (eax=arg1 -> call -> return eax). sub_457DA0 = int __usercall(int@eax) = recovered Building_GetPlagueState(int building_index) at src/strategic/00455740_004582B0_strategic_003.c:860. No filler, template-identical. Registration: aJestzarazawzam -> &Rules_HostPlagueInCastleExists, code 98='b', a11i_0 (strategic_003.c:652).

### `Rules_HostRoadExists` (loc_4528AB, jest_droga, int, 3 args)

```c
int Rules_HostRoadExists(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathToTile(a3, a4, a5);
}
```

_Notes:_ ret letter b (98). Handler spills 3 args to stack locals [ebp-0Ch]/[ebp-8]/[ebp-4] then loads eax=arg1, edx=arg2, ebx=arg3 and calls sub_453110 -> recovered C Rules_QueuePathToTile (@0x453110, src/strategic/00453110_00455720_strategic_002.c:16), signed int __usercall(int@eax stack_index, int@edx target_x, int@ebx target_y, DWORD@ebp a4). The 4th DWORD param is NOT supplied by the handler (same convention as the Rules_HostMarch/Move_CommitIfWithinCost template which passes only the 3 read args against a 4-param signature). asm call token is sub_453110; wrapper uses the recovered C name so it compiles (matches template precedent: UnitStack_HasBuilder is likewise absent from clash95.asm).

### `Rules_HostTempleOk` (loc_452C43, swiatynia_OK, int, 3 args)

```c
int Rules_HostTempleOk(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Player_CanEnterReligiousSiteTile(a3, a4, a5);
}
```

_Notes:_ ret letter b (98). Same 3-arg shape as loc_4528AB: spills 3 args, loads eax=arg1/edx=arg2/ebx=arg3. asm call token Move_CanEnterTile is at 0x4541B0 and is recovered in C as Player_CanEnterReligiousSiteTile(int player_index, int tile_x, int tile_y) (src/strategic/00453110_00455720_strategic_002.c:450), BOOL __usercall(int@eax, int@edx, int@ebx). The 'temple OK' (swiatynia_OK) meaning aligns with the religious-site name — cross-check passes. wrapper_c uses the current C symbol Player_CanEnterReligiousSiteTile (the asm 'Move_CanEnterTile' name has been renamed in the C tree).

### `Rules_HostFordExists` (loc_452F6B, jest_brod, int, 1 args)

```c
int Rules_HostFordExists(int a1, double a2)
{
  (void)a1;
  return Rules_IsQueuedPathTargetBridgeCrossing(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ ret letter b (98). Single-arg handler: reads arg1, calls sub_454A20 -> recovered C Rules_IsQueuedPathTargetBridgeCrossing(int stack_index) (@0x454A20, src/strategic/00453110_00455720_strategic_002.c:703), signed int __usercall(int@eax). Byte-identical form to the recovered Rules_HostArmyHasBuilder template.

### `Rules_HostStartHealing` (loc_456842, Zacznij-Leczenie, void, 2 args)

```c
void Rules_HostStartHealing(int a1, double a2)
{
  (void)a1;
  Building_RepairUnitByIndex(Rules_RtnLong(1, 0, a2), Rules_RtnLong(2, 0, a2));
}
```

_Notes:_ ret letter v (118) -> void, result NOT stored. asm call token sub_4556C0 -> recovered C Building_RepairUnitByIndex(int building_index, int slot_index, DWORD a3) (@0x4556C0, src/strategic/00453110_00455720_strategic_002.c:1414), __int16 __usercall(int@eax, int@edx, DWORD@ebp). ATTENTION (differs from the standard multi-arg pattern): this 2-arg handler does NOT spill args to stack — it reads arg2 into edx FIRST (mov eax,2;call;mov edx,eax) then arg1 into eax (mov eax,1;call) and calls directly. That is the Watcom right-to-left evaluation of an INLINED nested call; using explicit ordered temporaries would spill both to stack (sub esp,8) and would NOT be byte-identical. Hence the inlined form is used here (relies on Rules_RtnLong preserving edx across the arg1 read, which the correct game requires). Only 2 of the 3 params are supplied (trailing DWORD a3 not passed). Flag the inline-vs-temporary choice for manual review at re-baseline.

### `Rules_HostTurnNumber` (loc_456A7C, Numer-Tury, int, 0 args)

```c
int Rules_HostTurnNumber(void)
{
  return Game_GetTurnNumber();
}
```

_Notes:_ ret letter i (105). Zero-arg handler: no Rules_RtnLong reads, does not reference a1/a2 — declared (void) to match the recovered 0-arg template Rules_HostPortHasSupplyReady(void). asm calls Game_GetTurnNumber which is recovered in C under the same name (src/strategic/00453110_00455720_strategic_002.c:1270), int(void). Handler spills the result to [ebp-4] before returning; 'return Game_GetTurnNumber();' is the equivalent source (the local is a compiler artifact, matching how the template inlines its return).

### `Rules_HostIsProduction` (loc_456CC9, Is-Production, int, 1 args)

```c
int Rules_HostIsProduction(int a1, double a2)
{
  (void)a1;
  return Building_HasProductionByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ ret letter b (98). Single-arg handler: reads arg1 into eax, calls sub_455620 -> recovered C Building_HasProductionByIndex(int building_index) (@0x455620, src/strategic/00453110_00455720_strategic_002.c:1386), BOOL __usercall(int@eax). Byte-identical to the Rules_HostArmyHasBuilder template.

### `Rules_HostUnitsToSchool` (loc_456F51, Jednostki-Do-Szkoly, int, 1 args)

```c
int Rules_HostUnitsToSchool(int a1, double a2)
{
  (void)a1;
  return Building_HasTrainableIdleGarrisonUnit(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ ret letter b (98). Single-arg handler: reads arg1 into eax, calls sub_4559D0 -> recovered C Building_HasTrainableIdleGarrisonUnit(int building_index) (@0x4559D0, src/strategic/00455740_004582B0_strategic_003.c:151), signed int __usercall(int@eax). Byte-identical to the Rules_HostArmyHasBuilder template.

### `Rules_HostRegroupCastle` (loc_457417, przegrupuj-zamek, int, 2 args)

```c
int Rules_HostRegroupCastle(int a1, double a2)
{
  (void)a1;
  return UnitStack_RegroupWithBuildingGarrisonByHealth(Rules_RtnLong(1, 0, a2), Rules_RtnLong(2, 0, a2));
}
```

_Notes:_ ret letter b (98). asm call token sub_4589C0 -> recovered C UnitStack_RegroupWithBuildingGarrisonByHealth(int army_index, int building_index, char a3, DWORD a4, double a5) (@0x4589C0, first fn of src/strategic/004589C0_004602F0_strategic_004.c:20), signed int __usercall(int@eax, int@edx, char@bl, DWORD@ebp, double@st0). ATTENTION: same 2-arg no-spill codegen as loc_456842 — reads arg2 into edx FIRST then arg1 into eax and calls; only 2 of 5 params supplied (trailing char/DWORD/double not passed by the handler). The inlined nested form is required for byte-identity (explicit temporaries would spill to stack and diverge). Result is stored to [ebp-4] then returned (int). Flag inline-vs-temporary for manual review at re-baseline.

### `Rules_HostPlagueInTroopExists` (loc_4576A5, jest-zaraza-w-oddziale, int, 1 args)

```c
int Rules_HostPlagueInTroopExists(int a1, double a2)
{
  (void)a1;
  return UnitStack_HasPlagueByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ ret letter b (98). Single-arg handler: reads arg1 into eax, calls sub_457DC0 -> recovered C UnitStack_HasPlagueByIndex(int stack_index) (@0x457DC0, src/strategic/00455740_004582B0_strategic_003.c:867), signed int __usercall(int@eax). Byte-identical to the Rules_HostArmyHasBuilder template.

### `Rules_HostRoadExistsNearby` (loc_452907, jest_droga_w_poblize / jest_droga_w_poblize00, b (int), 3 args)

```c
int Rules_HostRoadExistsNearby(int a1, double a2)
{
  int stack_index = Rules_RtnLong(1, 0, a2);
  int target_x = Rules_RtnLong(2, 0, a2);
  int target_y = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathNearTile(stack_index, target_x, target_y);
}
```

_Notes:_ Standard 3-arg spilled pattern: args 1,2,3 read into locals [ebp-0Ch],[ebp-8],[ebp-4] in order, then eax=arg1, edx=arg2, ebx=arg3 at the call. asm token is 'call sub_4532A0'; recovered in src as Rules_QueuePathNearTile at 0x4532A0 (src/strategic/00453110_00455720_strategic_002.c:54). Recovered prototype declares a 4th param (DWORD a4) that the handler never sets (ecx unloaded) -- decompiler artifact; wrapper passes the 3 register args the asm supplies, matching the March-template precedent. Frame probe push=2Ch.

### `Rules_HostMarch` (loc_452C9F, maszeruj / maszeruj00, i (int), 3 args)

```c
int Rules_HostMarch(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Move_CommitIfWithinCost(a3, a4, a5);
}
```

_Notes:_ Byte-for-byte the supplied March template. asm call token is already the recovered name 'Move_CommitIfWithinCost' (src/strategic/00453110_00455720_strategic_002.c:461; declared strategic_internal.h:44 as 4-param with a trailing double a4 artifact -- handler supplies 3, same precedent as all others). eax=arg1, edx=arg2, ebx=arg3 spilled in order. Confirmed by AI_SCRIPTING_API.md line 81 which spells out this exact body. Frame probe push=2Ch.

### `Rules_HostBuildRoad` (loc_452FA7, buduj_droge / buduj_droge00, b (int), 1 args)

```c
int Rules_HostBuildRoad(int a1, double a2)
{
  (void)a1;
  return Rules_BuildRoadOrStepTowardQueuedPath(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Single-arg wrapper. asm token 'call sub_454AE0'; recovered as Rules_BuildRoadOrStepTowardQueuedPath at 0x454AE0 (src/strategic/00453110_00455720_strategic_002.c:721). Recovered prototype (int stack_index, DWORD a2, double a3) has 2 extra params; handler sets only eax=arg1 -- extra params are decompiler artifacts, wrapper passes 1 arg. Frame probe push=24h.

### `Rules_HostStartTraining` (loc_45687E, Zacznij-Szkolenie / ZacznijSzkolenie, v (void), 2 args)

```c
void Rules_HostStartTraining(int a1, double a2)
{
  int unit_type = Rules_RtnLong(2, 0, a2);
  int building_index = Rules_RtnLong(1, 0, a2);
  (void)a1;
  Building_TrainUnitByIndex(building_index, unit_type);
}
```

_Notes:_ VOID host fn (reg type 118='v'): no [ebp-4] store after the call, return value discarded. Register-only 2-arg handler (no local spill): reads arg2 into edx first, then arg1 into eax, then calls -- I follow the repo's own read-order-temporaries convention (see recovered Rules_HostArmyHasOnlyUnitType, strategic_003.c:1084-1086) so evaluation order matches the asm. asm token 'call sub_4556E0'; recovered as Building_TrainUnitByIndex at 0x4556E0 (strategic_002.c:1421). Recovered prototype (int building_index, char a2, DWORD a3): 2nd param is char (int arg narrows implicitly), 3rd param is an artifact the handler never sets. Frame probe push=20h.

### `Rules_HostPeasantCount` (loc_456CFF, Ilosc-Chlopow / IloscChlopow, i (int), 1 args)

```c
int Rules_HostPeasantCount(int a1, double a2)
{
  (void)a1;
  return Building_GetPeasantCountByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Clean single-arg wrapper; inner prototype arity matches exactly. asm token 'call sub_455600'; recovered as Building_GetPeasantCountByIndex(int building_index) at 0x455600 (strategic_002.c:1375). Frame probe push=20h.

### `Rules_HostMaxTroopCount` (loc_456F87, Max-Ilosc-Oddzialow / MaxIloscOddzialow, b (int), 1 args)

```c
int Rules_HostMaxTroopCount(int a1, double a2)
{
  (void)a1;
  return Building_IsGarrisonFullByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Clean single-arg wrapper; inner prototype arity matches exactly (returns BOOL). asm token 'call sub_455690'; recovered as Building_IsGarrisonFullByIndex(int building_index) at 0x455690 (strategic_002.c:1407). Frame probe push=20h.

### `Rules_HostArmyHeadcount` (loc_457459, stan-osob-armii / StanOsobArmii, i (int), 2 args)

```c
int Rules_HostArmyHeadcount(int a1, double a2)
{
  int aggregate_mode = Rules_RtnLong(2, 0, a2);
  int stack_index = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return UnitStack_GetHealthPercentAggregate(stack_index, aggregate_mode);
}
```

_Notes:_ Register-only 2-arg handler: reads arg2 into edx first, then arg1 into eax; follows the repo read-order-temporaries convention. Inner prototype matches exactly: UnitStack_GetHealthPercentAggregate(int stack_index, int aggregate_mode) at 0x458220 (strategic_003.c:1090), so eax=arg1=stack_index, edx=arg2=aggregate_mode. asm token 'call sub_458220'. Frame probe push=20h.

### `Rules_HostDetachWeakUnits` (loc_4576DB, odlacz-jednostki-slabe / OdlaczJednostkiSlabe, b (int), 1 args)

```c
int Rules_HostDetachWeakUnits(int a1, double a2)
{
  (void)a1;
  return UnitStack_DetachWeakUnitsToAdjacentTile(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Single-arg wrapper. asm token 'call sub_457E60'; recovered as UnitStack_DetachWeakUnitsToAdjacentTile at 0x457E60 (strategic_003.c:891). Recovered prototype (int army_index, int dest_tile_y, int dest_tile_x, double a4) has 3 extra params; handler sets only eax=arg1 -- extra params are decompiler artifacts, wrapper passes 1 arg. Frame probe push=20h.

### `Rules_HostMarchToTemple` (loc_452CFB, maszeruj_do_swiatyni, i, 3 args)

```c
int Rules_HostMarchToTemple(int a1, double a2)
{
  int stack_index;
  int temple_x;
  int temple_y;

  (void)a1;
  stack_index = Rules_RtnLong(1, 0, a2);
  temple_x = Rules_RtnLong(2, 0, a2);
  temple_y = Rules_RtnLong(3, 0, a2);
  return Rules_MarchToTemple(stack_index, temple_x, temple_y, a2);
}
```

_Notes:_ asm call target = sub_454330 (verified recovered at 00454330 = Rules_MarchToTemple(unsigned int stack_index,int temple_x,int temple_y,double a4), src/strategic/00453110_00455720_strategic_002.c:508). Registration: strategic_001.c:1432 (&Rules_HostMarchToTemple, aMaszeruj_do_sw='maszeruj_do_swiatyni00', a33i). 33i forward read; call passes eax=arg1,edx=arg2,ebx=arg3. Inner's 4th param is genuine 'double a4' = threaded context a2 -> clean pass of a2. stack_index param is unsigned int (implicit int->unsigned at call).

### `Rules_HostBuildTrap` (loc_452FE3, buduj_pulapke, i, 3 args)

```c
int Rules_HostBuildTrap(int a1, double a2)
{
  int target_x;
  int target_y;
  int stack_index;

  (void)a1;
  target_x = Rules_RtnLong(1, 0, a2);
  target_y = Rules_RtnLong(2, 0, a2);
  stack_index = Rules_RtnLong(3, 0, a2);
  return Rules_BuildTrapNearTile(target_x, target_y, stack_index, a2);
}
```

_Notes:_ asm call target = sub_454D20 (verified recovered at 00454D20 = Rules_BuildTrapNearTile(DWORD target_x,int target_y,DWORD stack_index,double a4), src/strategic/00453110_00455720_strategic_002.c:837). Registration: strategic_001.c:1442 (&Rules_HostBuildTrap, aBuduj_pulapke0='buduj_pulapke00', a33i). 33i forward read; call passes eax=arg1,edx=arg2,ebx=arg3. Inner's 4th param is genuine 'double a4' = threaded context a2 -> clean pass of a2. params 1/3 typed DWORD (implicit int->unsigned at call, matches registers holding CLIPS ints).

### `Rules_HostStartProduction` (loc_4568BA, Zacznij-Produkcje, v, 2 args)

```c
void Rules_HostStartProduction(int a1, double a2)
{
  int production_type;
  int building_index;

  (void)a1;
  production_type = Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  Building_SetUnitProductionByIndex(building_index, production_type, a2);
}
```

_Notes:_ asm call target = sub_455700 (verified recovered at 00455700 = Building_SetUnitProductionByIndex(int building_index,char a2,DWORD a3), src/strategic/00453110_00455720_strategic_002.c:1428). Registration: strategic_003.c:597 (&Rules_HostStartProduction, aZacznijprodukc='ZacznijProdukcje', 118='v', a22i). VOID return: asm has no [ebp-4] store after the call and discards eax -> wrapper returns void. 22i reverse read (arg2 into edx first, then arg1 into eax); call passes eax=arg1=building_index, edx=arg2=production char. Inner's 3rd param 'DWORD a3' is the threaded context = a2 (flows onward as Building_SetUnitProduction's 3rd arg) -- REVIEW: double a2 passed to a DWORD param (narrowing conversion). production_type (int temp) narrows to the inner's char param at the call boundary.

### `Rules_HostBuyLicence` (loc_456B0D, Buy-Licence, b, 2 args)

```c
int Rules_HostBuyLicence(int a1, double a2)
{
  unit_type licence_type;
  int building_index;

  (void)a1;
  licence_type = (unit_type)Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_BuyUnitLicenceByIndex(building_index, licence_type, a2);
}
```

_Notes:_ asm call target = sub_4557E0 (verified recovered at 004557E0 = Building_BuyUnitLicenceByIndex(int building_index,unit_type licence_type,DWORD a3), src/strategic/00455740_004582B0_strategic_003.c:46). Registration: strategic_003.c:601 (&Rules_HostBuyLicence, aBuylicence='BuyLicence', a22i). 22i reverse read (arg2->edx, arg1->eax); call passes eax=building_index, edx=licence_type. Inner's 3rd param 'DWORD a3' is the threaded context = a2 (flows to Building_BuyUnitLicence's DWORD gameContext) -- REVIEW: double a2 passed to a DWORD param (narrowing conversion). unit_type cast matches recovered sibling Rules_HostArmyHasOnlyUnitType style.

### `Rules_HostIsMinimal` (loc_456D35, Czy-Minimalny, b, 4 args)

```c
int Rules_HostIsMinimal(int a1, double a2)
{
  int site_row;
  int site_column;
  int candidate_column;
  int candidate_row;

  (void)a1;
  site_row = Rules_RtnLong(4, 0, a2);
  site_column = Rules_RtnLong(3, 0, a2);
  candidate_column = Rules_RtnLong(2, 0, a2);
  candidate_row = Rules_RtnLong(1, 0, a2);
  return Map_IsCastleSiteDistanceMinimal(candidate_row, candidate_column, site_column, site_row);
}
```

_Notes:_ asm call target = sub_455F60 (verified recovered at 00455F60 = Map_IsCastleSiteDistanceMinimal(int candidate_row,int candidate_column,int site_column,int site_row), src/strategic/00455740_004582B0_strategic_003.c:476). Registration: strategic_003.c:607 (&Rules_HostIsMinimal, aCzyminimalny='CzyMinimalny', a44i). 44i reverse read (arg4->ecx first, then 3->ebx, 2->edx, 1->eax); call passes eax=arg1,edx=arg2,ebx=arg3,ecx=arg4 = (candidate_row,candidate_column,site_column,site_row). Inner has exactly 4 int params and no trailing context param -> a2 is NOT threaded to the inner (matches all 4 registers being loaded in the asm).

### `Rules_HostUnitInCastleExists` (loc_456FBD, Jest-Jednostka-W-Zamku, b, 2 args)

```c
int Rules_HostUnitInCastleExists(int a1, double a2)
{
  unit_type sought_type;
  int building_index;

  (void)a1;
  sought_type = (unit_type)Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_HasGarrisonUnitTypeByIndex(building_index, sought_type);
}
```

_Notes:_ asm call target = sub_455F20 (verified recovered at 00455F20 = Building_HasGarrisonUnitTypeByIndex(int building_index,unit_type sought_type), src/strategic/00455740_004582B0_strategic_003.c:458). Registration: strategic_003.c:613 (&Rules_HostUnitInCastleExists, aJestjednostkaw='JestJednostkaWZamku', a22i). 22i reverse read (arg2->edx, arg1->eax); call passes eax=building_index, edx=sought_type. Inner has exactly 2 params, no trailing context -> a2 not threaded. Clean thin-wrapper.

### `Rules_HostArmyHasUnitsOfType` (loc_45749B, armia-ma-jednostki-typu, b, 2 args)

```c
int Rules_HostArmyHasUnitsOfType(int a1, double a2)
{
  unit_type sought_type;
  int stack_index;

  (void)a1;
  sought_type = (unit_type)Rules_RtnLong(2, 0, a2);
  stack_index = Rules_RtnLong(1, 0, a2);
  return UnitStack_HasUnitType(stack_index, sought_type);
}
```

_Notes:_ asm call target = sub_458160 (verified recovered at 00458160 = UnitStack_HasUnitType(int stack_index,unit_type sought_type), src/strategic/00455740_004582B0_strategic_003.c:1034). Registration: strategic_003.c:647 (&Rules_HostArmyHasUnitsOfType, aArmiamajednost='ArmiaMaJednostkiTypu', a22i). 22i reverse read (arg2->edx, arg1->eax); call passes eax=stack_index, edx=sought_type. Inner has exactly 2 params, no trailing context -> a2 not threaded. Byte-for-byte parallel to already-recovered sibling Rules_HostArmyHasOnlyUnitType (strategic_003.c:1078).

### `Rules_HostRoadExistsToPort` (loc_4529BF, jest_droga_do_portu, b, 3 args)

```c
int Rules_HostRoadExistsToPort(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathToPort(a3, a4, a5);
}
```

_Notes:_ sub_453600 = recovered C Rules_QueuePathToPort (strategic_002.c:146). Registered strategic_001.c:1423 (ret 98='b', restr a33i). asm: reads arg1->[ebp-0Ch], arg2->[ebp-8], arg3->[ebp-4]; then ebx=arg3, edx=arg2, eax=arg1; call. So call is (arg1,arg2,arg3) in Watcom eax/edx/ebx order = same three-temp shape as the Rules_HostMarch template. MANUAL-REVIEW: Rules_QueuePathToPort's prototype has a 4th param `DWORD a4` (strategic_internal.h:36) that the handler does NOT set (no ecx move before call) -- a genuine leftover-ecx quirk of the original; wrapper passes exactly the 3 CLIPS args (byte-identical, matches the template which likewise omits its inner's trailing param). Header proto may need the phantom a4 trimmed for a clean build.

### `Rules_HostMarchNear` (loc_452D57, maszeruj_blisko, i, 3 args)

```c
int Rules_HostMarchNear(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_MarchNearTile(a3, a4, a5);
}
```

_Notes:_ sub_454590 = recovered C Rules_MarchNearTile (strategic_002.c:564). Registered strategic_001.c:1433 (ret 105='i', restr a33i). asm identical 3-arg shape to loc_452C9F template: arg1->eax, arg2->edx, arg3->ebx at the call. Rules_MarchNearTile's prototype has a trailing `double a4` (strategic_internal.h:46) that is the host double a2, already live in st0 -- not passed explicitly, exactly as the Move_CommitIfWithinCost template omits its trailing double (byte-identical either way since st0 already holds a2).

### `Rules_HostUnitCanMove` (loc_45303F, Unit_CanMove, i, 1 args)

```c
int Rules_HostUnitCanMove(int a1, double a2)
{
  (void)a1;
  return Unit_AttemptNeighborMove(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ asm calls thunk j_Unit_AttemptNeighborMove -> recovered C Unit_AttemptNeighborMove(int stackIndex) (units_002.c:507). Registered strategic_001.c:1443 (ret 105='i', restr a11i). Matches the doc's own decode note (AI_SCRIPTING_API.md line ~80). MANUAL-REVIEW: unlike the other 1-arg handlers here, this one's asm has an extra arg store+reload (`sub esp,8`; mov [ebp-4],eax; mov eax,[ebp-4]) before the call, whereas the inline form typically emits no arg store -- a codegen nuance the byte-diff gate should confirm; the inline form is used to match the documented template and doc note.

### `Rules_HostTax` (loc_4568F6, Podatek, i, 1 args)

```c
int Rules_HostTax(int a1, double a2)
{
  (void)a1;
  return Building_GetTaxRateByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ sub_455470 = recovered C Building_GetTaxRateByIndex(int building_index) (strategic_002.c:1291). Registered strategic_003.c:614 (ret 105='i', restr a11i). asm passes arg1 straight in eax to the inner call (no intervening store), so the inline template form is exactly byte-faithful.

### `Rules_HostBuyBarracks` (loc_456B4F, Kup-Koszary, b, 1 args)

```c
int Rules_HostBuyBarracks(int a1, double a2)
{
  (void)a1;
  return Building_BuildBarracksByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ sub_455530 = recovered C Building_BuildBarracksByIndex (strategic_002.c:1333, itself a thin forwarder to Building_BuildBarracks). Registered strategic_003.c:604 (ret 98='b', restr a11i). asm passes arg1 in eax, no store. MANUAL-REVIEW: inner prototype has trailing `char a2, DWORD a3` (strategic_internal.h:67) that the handler leaves unset (edx/ebx leftover) -- wrapper passes only the 1 CLIPS arg, consistent with the template's pass-exactly-N-CLIPS-args convention; header proto may need those trailing params trimmed.

### `Rules_HostCanBuyLicence` (loc_456D8F, Can-Buy-Licence, b, 2 args)

```c
int Rules_HostCanBuyLicence(int a1, double a2)
{
  unit_type licence_type;
  int building_index;

  (void)a1;
  licence_type = (unit_type)Rules_RtnLong(2, 0, a2);
  building_index = Rules_RtnLong(1, 0, a2);
  return Building_CanBuyUnitLicenceByIndex(building_index, licence_type);
}
```

_Notes:_ sub_455800 = recovered C Building_CanBuyUnitLicenceByIndex(int building_index, unit_type licence_type) (strategic_003.c:53). Registered strategic_003.c:608 (ret 98='b', restr a22i). asm is the canonical 2-arg shape (mov eax,2/call/mov edx,eax then mov eax,1/call then call): arg2 read first into edx, arg1 into eax, so call = (building_index=arg1, licence_type=arg2). Body mirrors the already-recovered 2-arg sibling Rules_HostArmyHasOnlyUnitType (strategic_003.c:1078) exactly, including the (unit_type) cast on the 2nd arg.

### `Rules_HostUnitsToHospital` (loc_456FFF, Jednostki-Do-Szpitala, b, 1 args)

```c
int Rules_HostUnitsToHospital(int a1, double a2)
{
  (void)a1;
  return Building_HasRepairableIdleGarrisonUnit(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ sub_455A50 = recovered C Building_HasRepairableIdleGarrisonUnit(int building_index) (strategic_003.c:180). Registered strategic_003.c:612 (ret 98='b', restr a11i). Clean 1-in/1-out: inner takes exactly one int, asm passes arg1 in eax with no store -- inline template form is byte-faithful.

### `Rules_HostCastleFreeSlotCount` (loc_45751F, liczba-wolnych-miejsc-w-zamku, i, 1 args)

```c
int Rules_HostCastleFreeSlotCount(int a1, double a2)
{
  (void)a1;
  return Building_CountFreeGarrisonSlots(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ asm calls thunk j_Building_GetCapacity -> asm proc `Building_GetCapacity` (clash95.asm:94293, 1 int in eax). NAME DIVERGENCE: that proc's recovered C definition is named Building_CountFreeGarrisonSlots(int buildingId) (buildings_005.c:1434, addr 0x43E4B0) -- verified body-identical to the asm (imul eax,1D3h; per-slot loop, slotLimit byte[+4]?12:10, word[+18]==-1 counts free, stride 0x1F). The disassembly's semantic label (Building_GetCapacity) was applied after C recovery, so no 'Building_GetCapacity' symbol exists in src/. Wrapper must call the linkable C name Building_CountFreeGarrisonSlots. Registered strategic_003.c:643 (ret 105='i', restr a11i).

### `Rules_HostMarchAlongRoad` (loc_457753, maszeruj-wzdluz-drogi, b, 1 args)

```c
int Rules_HostMarchAlongRoad(int a1, double a2)
{
  (void)a1;
  return Unit_ExecuteQueuedPathAndCheckFinished(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ sub_457E00 = recovered C Unit_ExecuteQueuedPathAndCheckFinished (strategic_003.c:874). Registered strategic_003.c:656 (ret 98='b', restr a11i). asm passes arg1 in eax, no store. MANUAL-REVIEW: inner prototype has trailing `char a2, DWORD a3, double a4` (strategic_internal.h:115); the char/DWORD are unset leftovers (edx/ebx) and the double a4 is the host a2 live in st0. Wrapper passes only the 1 CLIPS arg per the pass-exactly-N-CLIPS-args template convention; header proto's extra params may need trimming for a clean build.

### `Rules_HostRoadExistsToCastle` (loc_452A1B, jest_droga_do_zamku (C-name jest_droga_do_zamku00), int, 3 args)

```c
int Rules_HostRoadExistsToCastle(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathToCastle(a3, a4, a5);
}
```

_Notes:_ Doc: b/33i "Is there a road to the castle?". Reads args 1,2,3 left-to-right into locals ([ebp-0Ch],[ebp-8],[ebp-4]) then loads eax=arg1, edx=arg2, ebx=arg3 (Watcom reg convention) and calls sub_453770. sub_453770 is recovered as `signed int Rules_QueuePathToCastle(int stack_index, int castle_x, int castle_y, DWORD a4)` at src/strategic/00453110_00455720_strategic_002.c:182 -- wrapper_c calls it by that recovered name. Inner has a trailing 4th DWORD context param the handler leaves unset; omitted from the call exactly like the Move_CommitIfWithinCost template omits its trailing DWORD/double. Registered at strategic_001.c:1424 (&Rules_HostRoadExistsToCastle). Matches the 3-arg March template verbatim.

### `Rules_HostAttackTroop` (loc_452DB3, atakuj_oddzial (C-name atakuj_oddzial00), int, 2 args)

```c
int Rules_HostAttackTroop(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Rules_HostUnitAttack(a3, a4);
}
```

_Notes:_ Doc: i/22i "Attack an enemy squad.". Reads args 1,2 left-to-right into locals ([ebp-8],[ebp-4]) then loads eax=arg1, edx=arg2 and calls sub_4547F0. sub_4547F0 is recovered as `signed int Rules_HostUnitAttack(int army_index, int target_army_index, char a3, DWORD a4, double a5)` at strategic_002.c:621 (note: the recovered inner name confusingly starts with Rules_Host but it is the worker, not the CLIPS handler). Inner carries trailing char/DWORD/double context params the handler leaves unset; omitted from the call per the template convention. Registered at strategic_001.c:1434 (&Rules_HostAttackTroop).

### `Rules_HostHealing` (loc_456706, Leczenie (C-name Leczenie), void, 1 args)

```c
void Rules_HostHealing(int a1, double a2)
{
  (void)a1;
  Building_StartRepairIdleGarrisonUnits(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Doc: v/11i "Healing.". Void handler: reads arg1 (eax) then calls sub_455B50 and returns with NO [ebp-4] store/reload of eax (distinguishing it from the int handlers). sub_455B50 is recovered as `__int16 Building_StartRepairIdleGarrisonUnits(int building_index)` at strategic_003.c:248 -- exact 1 param, its __int16 return is discarded (void). Registered at strategic_003.c:589 (&Rules_HostHealing).

### `Rules_HostIsLicence` (loc_45692C, Is-Licence (C-name IsLicence), int, 2 args)

```c
int Rules_HostIsLicence(int a1, double a2)
{
  int a4 = Rules_RtnLong(2, 0, a2);
  int a3 = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return Building_HasUnitLicenceByIndex(a3, a4);
}
```

_Notes:_ Doc: b/22i "Does the player hold a licence?". REVERSED read order: asm reads arg2 first (eax=2 -> mov edx,eax) then arg1 (eax=1) directly into registers (no arg spill locals), so temps are declared a4=RtnLong(2) before a3=RtnLong(1) to preserve the read order; inner called (a3,a4)=(arg1,arg2) with correct positions. sub_4557C0 recovered as `signed int Building_HasUnitLicenceByIndex(int building_index, unit_type licence_type)` at strategic_003.c:39 -- exact 2 params. Registered at strategic_003.c:600 (&Rules_HostIsLicence).

### `Rules_HostBuyHospital` (loc_456B85, Kup-Szpital (C-name KupSzpital), int, 1 args)

```c
int Rules_HostBuyHospital(int a1, double a2)
{
  (void)a1;
  return Building_BuildHospitalByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Doc: b/11i "Buy a hospital.". Reads arg1 (eax), calls sub_455550, stores/reloads eax, returns. sub_455550 recovered as `signed int Building_BuildHospitalByIndex(char a1, DWORD a2)` at strategic_002.c:1340; it has a trailing 2nd DWORD context param the handler leaves unset -- omitted from the call per the template convention. Registered at strategic_003.c:602 (&Rules_HostBuyHospital).

### `Rules_HostLicenceIndex` (loc_456DD1, Licencja-Index (C-name LicencjaIndex), int, 2 args)

```c
int Rules_HostLicenceIndex(int a1, double a2)
{
  int a4 = Rules_RtnLong(2, 0, a2);
  int a3 = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return Building_FindUnitLicenceSlotIndexOrZero(a3, a4);
}
```

_Notes:_ Doc: i/22i "Licence index (2-arg form).". REVERSED read order: asm reads arg2 first (mov edx,eax) then arg1 (eax) directly into registers, so a4=RtnLong(2) is declared before a3=RtnLong(1); inner called (a3,a4)=(arg1,arg2). sub_455850 recovered as `signed int Building_FindUnitLicenceSlotIndexOrZero(int building_index, unit_type licence_type)` at strategic_003.c:66 -- exact 2 params. Registered at strategic_003.c:624 (&Rules_HostLicenceIndex).

### `Rules_HostLeadOutTroop` (loc_457035, Wyprowadzenie-Oddzialu (C-name WyprowadzenieOddzialu), int, 2 args)

```c
int Rules_HostLeadOutTroop(int a1, double a2)
{
  int a4 = Rules_RtnLong(2, 0, a2);
  int a3 = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return Building_UnitsLeaveByUnitType(a3, a4);
}
```

_Notes:_ Doc: i/22i "Deploy/lead out a squad.". REVERSED read order: asm reads arg2 first (mov edx,eax) then arg1 (eax) directly into registers, so a4=RtnLong(2) declared before a3=RtnLong(1); inner called (a3,a4)=(arg1,arg2). sub_455BD0 recovered as `signed int Building_UnitsLeaveByUnitType(int building_index, unit_type leave_type, int a3, double a4)` at strategic_003.c:282; trailing int a3 + double a4 context params left unset by the handler are omitted per the template convention. Registered at strategic_003.c:629 (&Rules_HostLeadOutTroop).

### `Rules_HostEnemyPowerAtWalls` (loc_457555, moc-przeciwnika-pod-murami (C-name MocPrzeciwnikaPodMurami2), int, 1 args)

```c
int Rules_HostEnemyPowerAtWalls(int a1, double a2)
{
  (void)a1;
  return Building_GetMaxEnemyStrengthUnderWalls(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Doc: i/11i "Enemy strength massed under the walls.". Reads arg1 (eax), calls sub_457C00, stores/reloads eax, returns. sub_457C00 recovered as `int Building_GetMaxEnemyStrengthUnderWalls(int building_index)` at strategic_003.c:804 -- exact 1 param. Registered at strategic_003.c:645 (&Rules_HostEnemyPowerAtWalls).

### `Rules_HostFindBest` (loc_457789, znajdz-najlepszy (C-name Znajdz_Najlepszy), int, 5 args)

```c
int Rules_HostFindBest(int a1, double a2)
{
  int a7 = Rules_RtnLong(5, 0, a2);
  int a6 = Rules_RtnLong(4, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a3 = Rules_RtnLong(1, 0, a2);
  (void)a1;
  return AI_FindBestStrategicTargetNearTile(a3, a4, a5, a6, a7);
}
```

_Notes:_ Doc: i/55i "Find the best (target/option).". Five-arg Watcom register+stack convention with REVERSED read order: asm reads arg5 first (push eax), then arg4 (mov ecx,eax), arg3 (mov ebx,eax), arg2 (mov edx,eax), arg1 (eax), then calls. Temps declared in read order a7..a3 (arg5..arg1); inner called (a3,a4,a5,a6,a7)=(arg1..arg5) so eax=arg1, edx=arg2, ebx=arg3, ecx=arg4, stack=arg5. sub_459570 recovered as `int AI_FindBestStrategicTargetNearTile(int type_filter, int owner_filter, int origin_x, int origin_y, signed int search_radius)` at strategic_004.c:380 -- exact 5 params, clean 1:1 mapping (no extra context params). Registered at strategic_003.c:657 (&Rules_HostFindBest).

### `Rules_HostRoadExistsToTemple` (loc_452A77, jest_droga_do_swiatyni, int, 3 args)

```c
int Rules_HostRoadExistsToTemple(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Move_IsAtTargetOrCanStay(a3, a4, a5);
}
```

_Notes:_ Clean 3-int thin-wrapper. Registration ret letter 'b' -> int (strategic_001.c:1425). asm reads args 1,2,3 into [ebp-0Ch]/[ebp-8]/[ebp-4] (forward spill order) then loads eax=arg1, edx=arg2, ebx=arg3 -> inner(a3,a4,a5). Inner is already named in the asm 'call Move_IsAtTargetOrCanStay' and is recovered as signed int Move_IsAtTargetOrCanStay(int stack_index,int target_x,int target_y) at strategic_002.c:229. Arity matches exactly; byte-identical.

### `Rules_HostCaptureTroop` (loc_452DFF, przejmuj_oddzial, int, 2 args)

```c
int Rules_HostCaptureTroop(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return Rules_HostUnitCaptureDefeatedStack(a3, a4, a2);
}
```

_Notes:_ Registration ret 'i' -> int (strategic_001.c:1435). asm reads arg1->[ebp-8], arg2->[ebp-4] (forward spill) then eax=arg1, edx=arg2, call sub_454800. sub_454800 is recovered as signed int Rules_HostUnitCaptureDefeatedStack(int capturing_stack_index,int defeated_stack_index,double a3) at strategic_002.c:628 (declared strategic_internal.h:48). Its trailing double a3 is the ambient CLIPS double, which sits in ST0 for the whole handler and is passed byte-free (loc emits NO fp instruction before the inner call), so pass a2 (NOT 0.0). Thin-wrapper, byte-identical.

### `Rules_HostTraining` (loc_456736, Szkolenie, void, 1 args)

```c
void Rules_HostTraining(int a1, double a2)
{
  (void)a1;
  Building_StartTrainingIdleGarrisonUnits(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration ret 'v' -> void (strategic_003.c:590). asm: mov eax,1; call sub_4812C0 (eax=arg1); call sub_455AD0; then restores frame WITHOUT saving eax (no 'mov [ebp-4],eax') -> result discarded, confirming void. sub_455AD0 recovered as int Building_StartTrainingIdleGarrisonUnits(int building_index) at strategic_003.c:209 (int return, discarded here). 1 clean int arg, inline form like the ArmyHasBuilder template. Byte-identical.

### `Rules_HostTechLevel` (loc_456BBB, Poziom-Tech, int, 1 args)

```c
int Rules_HostTechLevel(int a1, double a2)
{
  (void)a1;
  return Building_GetTechLevelByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration ret 'i' -> int (strategic_003.c:619). asm reads 1 arg (eax=arg1), call sub_455580, save eax->[ebp-4]->return. sub_455580 recovered as int Building_GetTechLevelByIndex(int building_index) at strategic_002.c:1347. 1 clean int param, inline form. Byte-identical thin-wrapper.

### `Rules_HostLicenceInd` (loc_456E13, Licencja-Ind, int, 1 args)

```c
int Rules_HostLicenceInd(int a1, double a2)
{
  (void)a1;
  return Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration ret 'i' -> int (strategic_003.c:625). asm reads 1 arg (eax=arg1), call sub_455890, save eax->return. sub_455890 recovered as signed int Building_FindFirstNonPeasantNonBuilderLicenceSlotOrZero(int building_index) at strategic_003.c:83. 1 clean int param, inline form. Byte-identical thin-wrapper.

### `Rules_HostTroopInArmyRange` (loc_452AD3, oddzial_w_zasiegu_armii, b, 3 args)

```c
int Rules_HostTroopInArmyRange(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_QueuePathIntoArmyRange(a3, a4, a5);
}
```

_Notes:_ Registration: strategic_001.c:1426 (&Rules_HostTroopInArmyRange, ret 98='b', a33i). Asm call token is raw `sub_453C90`; resolved to src Rules_QueuePathIntoArmyRange at 0x453C90 (strategic_002.c:306) via its log string 'oddzial_w_zasiegu_armii2(%d,%d,%d)'. Handler loads ebx=arg3,edx=arg2,eax=arg1 -> inner receives (eax,edx,ebx)=(arg1,arg2,arg3). ARITY NOTE: src prototype has a 4th param `DWORD a4` (dead-on-entry; handler sets no 4th reg/stack arg). Per task template (pass exactly K args) I pass 3; reviewer must trim the inner's dead trailing param for a byte-identical build, else this call won't compile against the current 4-param prototype.

### `Rules_HostHideTroop` (loc_452E4B, ukryj_oddzial, i, 3 args)

```c
int Rules_HostHideTroop(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Rules_HostUnitMoveAndHide(a3, a4, a5);
}
```

_Notes:_ Registration: strategic_001.c:1436 (&Rules_HostHideTroop, ret 105='i', a33i). Asm call token raw `sub_454860`; resolved to src Rules_HostUnitMoveAndHide at 0x454860 (strategic_002.c:641). NOTE the impl fn is confusingly named Rules_Host* but is NOT a registered CLIPS host fn (it's the implementation). Register order eax=arg1,edx=arg2,ebx=arg3 -> Inner(arg1,arg2,arg3). ARITY NOTE: src prototype (unsigned int, unsigned int, DWORD, double a4) has a trailing `double a4` (threaded-a2 / dead) beyond the 3 asm-loaded args; I pass 3 per template, reviewer reconciles the trailing param.

### `Rules_HostBurnBuildings` (loc_456766, Pal-Budowle, v, 1 args)

```c
void Rules_HostBurnBuildings(int a1, double a2)
{
  (void)a1;
  Rules_OnCastleUpdate(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration: strategic_003.c:591 (aPalBudowle, ret 118='v', a11i). Asm already shows the semantic token `call Rules_OnCastleUpdate` (strategic_002.c:1277). void return: handler does `sub esp,4` but performs NO store-back and NO `mov eax` result load — it just reads arg1 into eax then tail-uses it. Passes 1 arg (building_index=arg1). ARITY NOTE: src prototype has 4 params (int building_index, char a2, DWORD a3, double a4); extras are dead edx/ebx + the threaded double a2 in ST0. Per template I pass only the 1 asm-loaded arg; reviewer must reconcile the inner's dead trailing params.

### `Rules_HostBuyForge` (loc_4569A4, Kup-Kuznia, b, 1 args)

```c
int Rules_HostBuyForge(int a1, double a2)
{
  (void)a1;
  return Building_BuildSmithsByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration: strategic_003.c:599 (aKupKuznia, ret 98='b', a11i). Asm call token raw `sub_4554B0`; resolved to Building_BuildSmithsByIndex at 0x4554B0 (strategic_002.c:1305). Handler loads eax=arg1, stores result to [ebp-4] and returns it. ARITY NOTE: src prototype (char a1, DWORD a2) has 2 params vs 1 asm-loaded arg (the 2nd is the dead/threaded value); I pass 1 per template, reviewer reconciles.

### `Rules_HostBuildingType` (loc_456BF1, Typ-Budowli, i, 1 args)

```c
int Rules_HostBuildingType(int a1, double a2)
{
  (void)a1;
  return Building_GetTypeByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration: strategic_003.c:621 (aTypBudowli, ret 105='i', a11i). Asm call token raw `sub_4555A0`; resolved to Building_GetTypeByIndex(int building_index) at 0x4555A0 (strategic_002.c:1354). Clean 1-param arity — compiles as-is, no reconciliation needed.

### `Rules_HostCanUpgradeWall` (loc_456E49, Can-Upgrade-Wall, i, 1 args)

```c
int Rules_HostCanUpgradeWall(int a1, double a2)
{
  (void)a1;
  return Building_CanStartUpgradeByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration: strategic_003.c:627 (aCanUpgradeWall, ret 105='i', a11i). Asm call token raw `sub_455650`; resolved to Building_CanStartUpgradeByIndex(int building_index) returning BOOL at 0x455650 (strategic_002.c:1393). Clean 1-param arity — compiles as-is. BOOL result narrows to int via eax passthrough, consistent with other wrappers returning int.

### `Rules_HostCastleName` (loc_4570AD, Nazwa-Zamku, s, 1 args)

```c
int Rules_HostCastleName(int a1, double a2)
{
  (void)a1;
  return Player_GetInternedNameByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration: strategic_003.c:631 (aNazwaZamku, ret 115='s', a11i). Asm call token raw `sub_455EC0`; resolved to Player_GetInternedNameByIndex(int player_index, int a2, int a3) at 0x455EC0 (strategic_003.c:424). Host CLIPS ret type 's' (string), but the impl returns int (interned-name handle) via eax; wrapper typed int to match src/eax passthrough and the existing-wrapper convention (all non-void wrappers return int). ARITY NOTE: src prototype has 3 params vs 1 asm-loaded arg — the extra int a2,int a3 are almost certainly the two 4-byte halves of the split threaded double; I pass 1 per template, reviewer reconciles.

### `Rules_HostHasUnitsToHeal` (loc_4575CD, ma-jednostki-do-leczenia, b, 1 args)

```c
int Rules_HostHasUnitsToHeal(int a1, double a2)
{
  (void)a1;
  return UnitStack_HasUnitsNeedingHealing(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Registration: strategic_003.c:649 (aMaJednostkiDoL, ret 98='b', a11i, args a11i_0). Asm call token raw `sub_4577F0`; resolved to UnitStack_HasUnitsNeedingHealing(int stack_index) at 0x4577F0 (strategic_003.c:662). Note this handler sits inside sub_4570E3 (DATA XREF sub_4570E3+159), not sub_4561B0. Clean 1-param arity — compiles as-is, no reconciliation needed.

### `Rules_HostBuildingInArmyRange` (loc_452B2F, budowla_w_zasiegu_armii / budowla_w_zasiegu_armii00, b (int), 3 args)

```c
int Rules_HostBuildingInArmyRange(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  int a5 = Rules_RtnLong(3, 0, a2);
  (void)a1;
  return Move_TryApproachTarget(a3, a4, a5);
}
```

_Notes:_ 3-arg handler, stored-to-locals asm shape (args written to ebp-0Ch/-8/-4 then reloaded), so explicit temporaries per convention. Reg mapping at the inner call: eax=[ebp-0Ch]=RtnLong(1), edx=[ebp-8]=RtnLong(2), ebx=[ebp-4]=RtnLong(3) -> Move_TryApproachTarget(stack_index, target_x, target_y). Inner recovered at src/strategic/00453110_00455720_strategic_002.c:256 (signed int Move_TryApproachTarget(int, DWORD, int)), declared strategic_internal.h:39. Registration verified in asm at clash95.asm:124285-124289 (aBudowla_w_zasi/'b'/a33i). Semantic note: this query handler ('is a building within the army's range?') calls a Move_-named inner returning signed int -- asm-faithful; the inner is evidently a dual-purpose reachability/approach routine. No double threading (inner takes only ints).

### `Rules_HostArmyExists` (loc_452EA7, jest_armia / jest_armia00, b (int), 1 args)

```c
int Rules_HostArmyExists(int a1, double a2)
{
  (void)a1;
  return UnitStack_HasNormalCombatUnitsByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Single-arg thin wrapper. asm: read arg1 (eax=1;call sub_4812C0)->[ebp-4], then mov eax,[ebp-4];call sub_4549A0. sub_4549A0 is recovered as BOOL UnitStack_HasNormalCombatUnitsByIndex(int stack_index) at src/strategic/00453110_00455720_strategic_002.c:688, declared strategic_internal.h:51 -- wrapper uses the recovered name. Registration: strategic_001.c:1437 (aJest_armia -> &Rules_HostArmyExists, a11i).

### `Rules_HostUpgradeWall` (loc_456796, Upgrade-Wall / UpgradeWall, v (void), 1 args)

```c
void Rules_HostUpgradeWall(int a1, double a2)
{
  (void)a1;
  Building_TryStartUpgradeByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Void return (registration type 118='v', strategic_003.c:592). asm reads arg1 then 'call sub_455450' with NO eax store afterward -> inner result discarded. sub_455450 recovered as BOOL Building_TryStartUpgradeByIndex(int building_index) at src/strategic/00453110_00455720_strategic_002.c:1283, declared strategic_internal.h:60.

### `Rules_HostMoney` (loc_4569DA, Pieniadze / Pieniadze, i (int), 1 args)

```c
int Rules_HostMoney(int a1, double a2)
{
  (void)a1;
  return Building_GetMoneyByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Single-arg thin wrapper returning int. sub_4554F0 recovered as int Building_GetMoneyByIndex(int building_index) at src/strategic/00453110_00455720_strategic_002.c:1318, declared strategic_internal.h:65. Registration: strategic_003.c:615 (aPieniadze -> &Rules_HostMoney, type 105='i', a11i_3).

### `Rules_HostPlayerStrength` (loc_456C27, Sila-Gracza / SilaGracza, i (int), 1 args)

```c
int Rules_HostPlayerStrength(int a1, double a2)
{
  (void)a1;
  return AI_TickNationPostTurn(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ inner_fn cited as it appears in asm: 'call j_AI_TickNationPostTurn'. j_AI_TickNationPostTurn is a 5-byte jump thunk (COLLAPSED FUNCTION at clash95.asm:129206) that jmps to AI_TickNationPostTurn; C has no thunk, so wrapper calls the real target. AI_TickNationPostTurn(int playerIndex)->int recovered at src/buildings/0043E500_0043FDE0_buildings_006.c:807, declared buildings_api.h:146 (cross-TU decl present). The name 'TickNationPostTurn' is a mislabel: this fn computes a nation/player power score (used as basePower/nationScore in persistence_006.c and strategic_001.c:249), matching Sila-Gracza ('player's overall strength'). Registration: strategic_003.c:622 (aSilaGracza -> &Rules_HostPlayerStrength, type 105='i').

### `Rules_HostTroopCount` (loc_456E7F, Ilosc-Oddzialow / IloscOddzialow, i (int), 1 args)

```c
int Rules_HostTroopCount(int a1, double a2)
{
  (void)a1;
  return Building_GetGarrisonCountByIndex(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Single-arg thin wrapper returning int. sub_455670 recovered as int Building_GetGarrisonCountByIndex(int building_index) at src/strategic/00453110_00455720_strategic_002.c:1399, declared strategic_internal.h:76. Registration: strategic_003.c:626 (aIloscOddzialow -> &Rules_HostTroopCount, type 105='i', a11i_3). ('Number of squads' = garrison count of the building/castle.)

### `Rules_HostEnterCastle` (loc_457351, wejdz-do-zamku / WejdzDoZamku, b (int), 2 args)

```c
int Rules_HostEnterCastle(int a1, double a2)
{
  int a3 = Rules_RtnLong(1, 0, a2);
  int a4 = Rules_RtnLong(2, 0, a2);
  (void)a1;
  return (int)(intptr_t)UnitStack_MoveToBuildingAndCheckArrival(a3, a4, a2);
}
```

_Notes:_ REVIEW RECOMMENDED (a2-threading + pointer->int cast). 2-arg, DIRECT-REGISTER asm shape (no stack locals for args): asm does eax=2;call sub_4812C0;mov edx,eax (edx=RtnLong(2)=building_index); eax=1;call sub_4812C0 (eax=RtnLong(1)=stack_index); call sub_457A10. Inner recovered as const void *UnitStack_MoveToBuildingAndCheckArrival(unsigned int stack_index, int building_index, double a3) at src/strategic/00455740_004582B0_strategic_003.c:759 (same TU), declared strategic_internal.h:110. The inner's 3rd param (double a3) IS used (passed to UnitStack_ExecuteQueuedPath at line 779); the handler supplies no explicit double, so a2 is threaded implicitly (same mechanism as Rules_RtnLong's 3rd arg) -> pass a2 as the 3rd argument. Inner returns const void* that is really 0/1 (line 780), cast to int for the 'b' return. intptr_t is available in this TU (registration code already uses (int)(intptr_t)...). Explicit temporaries used per task convention; the original compiler emitted the inlined right-to-left form UnitStack_MoveToBuildingAndCheckArrival(Rules_RtnLong(1,0,a2), Rules_RtnLong(2,0,a2), a2) (semantically identical). Registration: strategic_003.c:639 (aWejdzDoZamku -> &Rules_HostEnterCastle, type 98='b', a22i_0).

### `Rules_HostFindCastleForHealing` (loc_457603, znajdz-zamek-do-leczenia / ZnajdzZamekDoLeczenia, b (int), 1 args)

```c
int Rules_HostFindCastleForHealing(int a1, double a2)
{
  (void)a1;
  return UnitStack_FindPathToNearestHospitalCastle(Rules_RtnLong(1, 0, a2));
}
```

_Notes:_ Single-arg thin wrapper returning bool. sub_457860 recovered as BOOL UnitStack_FindPathToNearestHospitalCastle(DWORD stack_index) at src/strategic/00455740_004582B0_strategic_003.c:684 (same TU), declared strategic_internal.h:108. Registration: strategic_003.c:650 (aZnajdzZamekDoL -> &Rules_HostFindCastleForHealing, type 98='b', a11i_0).

