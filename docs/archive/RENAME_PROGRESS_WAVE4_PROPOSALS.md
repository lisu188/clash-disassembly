# Rename Progress

## Deferred / Ambiguous
- (none)

## Batch 1 - Unit logging strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1|1|global|unit|clash95.c|aUnit_createDDD|kFmtUnitCreateArgs|high|Format string for `Unit_Create` invocation logging.|
|2|2|global|unit|clash95.c|aUnit_createE_0|kLogUnitCreateErrorNoSlot|high|Error log label for lack of free unit slot.|
|3|3|global|unit|clash95.c|aUnit_createErr|kLogUnitCreateGhostError|high|Log message describing ghost/unit mismatch in creation path.|
|4|4|global|unit|clash95.c|aUnit_createE_1|kLogUnitCreateOccupiedError|high|String used when target cell is occupied during `Unit_Create`.|
|5|5|global|unit|clash95.c|aUnit_createE_2|kLogUnitCreateOwnershipError|high|String identifying owner validation failure in `Unit_Create`.|
|6|6|global|unit|clash95.c|aUnit_createOk0|kLogUnitCreateSuccess|high|Success log message for unit creation.|
|7|7|global|unit|clash95.c|aUnit_kill0x08x|kFmtUnitKill|high|Format string for `Unit_Kill` tracing.|
|8|8|global|unit|clash95.c|aUnit_moveDD|kFmtUnitMove|high|Format string describing `Unit_Move` call arguments.|
|9|9|global|unit|clash95.c|aUnit_checklowm|kLogUnitLowMoraleMutiny|high|Message for units mutinying due to low morale.|
|10|10|global|unit|clash95.c|aUnit_checklo_0|kLogUnitLowMoraleDisband|high|Message logged when a unit disbands from morale.|
|11|11|global|unit|clash95.c|aUnit_newturn|kLogUnitNewTurn|high|Marker logged when starting unit turn processing.|
|12|12|global|unit|clash95.c|aUnit_capture0x|kFmtUnitCapture|high|Format string used when logging `Unit_Capture`.|
|13|13|global|unit|clash95.c|aUnit_createnea|kFmtUnitCreateNearbyGroup|high|Format string for `Unit_CreateNearbyUnitGroup` arguments.|
|14|14|global|unit|clash95.c|aUnit_createn_0|kLogUnitCreateNearbyError|high|Error text for nearby unit group creation failures.|
|15|15|global|unit|clash95.c|aUnit_createn_1|kLogUnitCreateNearbyReturn|high|Trace string showing return values from nearby group creation.|

## Batch 2 - Unit movement logging strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|16|16|global|unit|clash95.c|aUnit_movetrack|kFmtUnitMoveTrack|high|Format string tracing `Unit_MoveTrack` arguments.|
|17|17|global|unit|clash95.c|aUnit_movetra_1|kFmtUnitMoveTrackNear|high|Format for logging `Unit_MoveTrackNear`.|
|18|18|global|unit|clash95.c|aUnit_movetra_0|kFmtUnitMoveTrackToBuilding|high|String used when logging pathing to a building.|
|19|19|global|unit|clash95.c|aUnit_movetra_3|kFmtUnitMoveTrackNearBuilding|high|Format for logs when plotting tracks near buildings.|
|20|20|global|unit|clash95.c|aUnit_infoDD0x0|kFmtUnitInfo|high|Log format describing `Unit_Info` inputs.|
|21|21|global|unit|clash95.c|aUnit_attackDD|kFmtUnitAttack|high|Trace string for `Unit_Attack` calls.|
|22|22|global|unit|clash95.c|aUnit_attackbui|kFmtUnitAttackBuilding|high|Trace string for building attack invocations.|
|23|23|global|unit|clash95.c|aUnit_capturebu|kFmtUnitCaptureBuilding|high|Format string for capturing buildings.|
|24|24|global|unit|clash95.c|aUnit_addtogrou|kFmtUnitAddToGroup|high|String describing group addition call arguments.|
|25|25|global|unit|clash95.c|aUnit_movefromg|kFmtUnitMoveFromGroup|high|Trace string for moving squads between groups.|
|26|26|global|unit|clash95.c|aUnit_movetra_2|kFmtUnitMoveTrackToTemple|high|Format for temple move tracking logs.|
|27|27|global|unit|clash95.c|aUnit_canmove00|kFuncUnitCanMove00|high|Script function identifier for `Unit_CanMove00`.|
|28|28|global|unit|clash95.c|aUnit_canmove|kFuncUnitCanMove|high|Script name string for `Unit_CanMove`.|

## Batch 3 - Unit resource strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|29|29|global|unit|clash95.c|aUnitsCacheEntr|kLogUnitsCacheCount|high|Displayed when reporting unit cache size.|
|30|30|global|unit|clash95.c|aUnitscache_cle|kLogUnitsCacheClear|high|Identifier string printed when clearing the unit cache.|
|31|31|global|unit|clash95.c|aUnits_go|kUnitsGoDir|high|Directory prefix literal `"units_go\\"` for movement art.|
|32|32|global|unit|clash95.c|aUnits_i_0|kUnitsIdleDirAlt1|medium|Alternate idle animation directory literal.|
|33|33|global|unit|clash95.c|aUnits_i_1|kUnitsIdleDirAlt2|medium|Second idle animation directory literal.|
|34|34|global|unit|clash95.c|aUnits_i_2|kUnitsIdleDirAlt3|medium|Third idle animation directory literal.|
|35|35|global|unit|clash95.c|aUnits_i|kUnitsIdleDir|medium|Primary idle animation directory literal.|
|36|36|global|unit|clash95.c|aUnits_at_1|kUnitsAttackDirAlt1|medium|Alternate attack animation directory literal.|
|37|37|global|unit|clash95.c|aUnits_at_0|kUnitsAttackDirAlt2|medium|Second alternative attack animation directory literal.|
|38|38|global|unit|clash95.c|aUnits_at|kUnitsAttackDir|medium|Primary attack animation directory literal.|

## Batch 4 - Unit battle tracing strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|39|39|global|unit|clash95.c|aUnitD0x08x|kFmtUnitSummaryLine|high|Detailed format string emitted when printing per-unit summary info.|
|40|40|global|unit|clash95.c|aUnitbattle_m_0|kFmtUnitBattleMoveTrack|high|Format string for `UnitBattle_MoveTrack` logs.|
|41|41|global|unit|clash95.c|aUnitbattle_mov|kFmtUnitBattleMoveTrackNear|high|Format string for near-move battle tracking.|
|42|42|global|unit|clash95.c|aUnitbattle_m_2|kFmtUnitBattleMoveTrackNearWall|high|Format describing unit track attempts near walls.|
|43|43|global|unit|clash95.c|aUnitbattle_m_3|kFmtUnitBattleMoveTrackForce|high|Format string for forced track calculations.|
|44|44|global|unit|clash95.c|aUnitbattle_m_1|kFmtUnitBattleMove|high|Log format for unit battle movement commands.|
|45|45|global|unit|clash95.c|aUnitbattle_att|kFmtUnitBattleAttack|high|Format string for battle attack logs.|
|46|46|global|unit|clash95.c|aUnitbattle_a_0|kFmtUnitBattleAttackWall|high|Format string for `UnitBattle_AttackWall`.|
|47|47|global|unit|clash95.c|aUnitbattle_def|kFmtUnitBattleDefence|high|Format string for defensive action logs.|

## Batch 5 - Unit script host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|48|48|global|unit|clash95.c|aJednostka_bite|kScriptFuncBattleUnitVariant|medium|Internal script identifier string `"jednostka_bitewna00"`.|
|49|49|global|unit|clash95.c|aJednostka_bi_0|kHostFuncBattleUnitVariant|medium|Host-visible function label `"jednostka_bitewna"`.|
|50|50|global|unit|clash95.c|aJednostkidoszk|kScriptFuncUnitsToSchool|high|Script identifier for moving units to school.|
|51|51|global|unit|clash95.c|aJednostkiDoSzk|kHostFuncUnitsToSchool|high|Hyphenated UI label for the same troop action.|
|52|52|global|unit|clash95.c|aJednostkidoszp|kScriptFuncUnitsToHospital|high|Script identifier for moving units to hospital.|
|53|53|global|unit|clash95.c|aJednostkiDoSzp|kHostFuncUnitsToHospital|high|Hyphenated UI label for hospital transfer.|
|54|54|global|unit|clash95.c|aJestjednostkaw|kScriptFuncUnitInCastle|high|Script-facing string "JestJednostkaWZamku".|
|55|55|global|unit|clash95.c|aJestJednostkaW|kHostFuncUnitInCastle|high|Hyphenated presentation string for castle unit check.|
|56|56|global|unit|clash95.c|aArmiamajednost|kScriptFuncArmyHasUnitType|high|Internal identifier for verifying army composition.|
|57|57|global|unit|clash95.c|aArmiaMaJednost|kHostFuncArmyHasUnitType|high|Display label for the same check.|
|58|58|global|unit|clash95.c|aArmiatylkojedn|kScriptFuncArmyOnlyUnitType|high|Internal name for "ArmyOnlyUnitType" rule helper.|
|59|59|global|unit|clash95.c|aArmiaTylkoJedn|kHostFuncArmyOnlyUnitType|high|Display label for the same helper.|
|60|60|global|unit|clash95.c|aMajednostkidol|kScriptFuncUnitsRequireHealing|high|Internal identifier for checking healing needs.|
|61|61|global|unit|clash95.c|aMaJednostkiDoL|kHostFuncUnitsRequireHealing|high|Hyphenated display label for healing requirement.|
|62|62|global|unit|clash95.c|aOdlaczjednostk|kScriptFuncDetachWeakUnits|medium|Internal identifier for detaching weak units.|
|63|63|global|unit|clash95.c|aOdlaczJednostk|kHostFuncDetachWeakUnits|medium|Display label for detaching weak units.|
|64|64|global|unit|clash95.c|aOdlaczjednos_0|kScriptFuncDetachUnitType|medium|Internal identifier for detaching units of a specific type.|
|65|65|global|unit|clash95.c|aOdlaczJednos_0|kHostFuncDetachUnitType|medium|Display label for the typed detachment helper.|

## Batch 6 - Temple host function strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|66|66|global|unit|clash95.c|aSwiatynia_w_za|kScriptFuncTempleWithinArmy|medium|Internal identifier describing temples within army reach.|
|67|67|global|unit|clash95.c|aSwiatynia_w__0|kHostFuncTempleWithinArmy|medium|Display label for the same temple-range rule.|
|68|68|global|unit|clash95.c|aSwiatynia_ok00|kScriptFuncTempleReady|medium|Internal string for "temple ready" check.|
|69|69|global|unit|clash95.c|aSwiatynia_ok|kHostFuncTempleReady|medium|Display label for temple readiness.|
|70|70|global|unit|clash95.c|aSwiatynia00|kScriptFuncTemple|medium|Internal identifier for the `swiatynia` host function.|
|71|71|global|unit|clash95.c|aSwiatynia|kHostFuncTemple|medium|Display label for the same temple helper.|

## Batch 7 - Host rule strings set A
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|72|72|global|unit|clash95.c|aKop_skarb00|kScriptFuncDigTreasure|medium|Internal identifier for the dig-treasure host function.|
|73|73|global|unit|clash95.c|aKop_skarb|kHostFuncDigTreasure|medium|Display label for the dig-treasure command.|
|74|74|global|unit|clash95.c|aPobierz_oddzia|kScriptFuncFetchSquad|medium|Internal identifier for fetching squads.|
|75|75|global|unit|clash95.c|aPobierz_oddz_0|kHostFuncFetchSquad|medium|Display label for the same squad retrieval helper.|
|76|76|global|unit|clash95.c|aPelny_port00|kScriptFuncPortFull|medium|Internal identifier used when checking a port capacity.|
|77|77|global|unit|clash95.c|aPelny_port|kHostFuncPortFull|medium|Display label for the port-full script function.|
|78|78|global|unit|clash95.c|aJest_pracownik|kScriptFuncWorkerAvailable|medium|Internal identifier string for worker availability checks.|
|79|79|global|unit|clash95.c|aJest_pracown_0|kHostFuncWorkerAvailable|medium|Display label for the same worker check.|

## Batch 8 - Road query host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|80|80|global|unit|clash95.c|aJest_droga_w_p|kScriptFuncRoadNear|medium|Internal identifier string for "road nearby" queries.|
|81|81|global|unit|clash95.c|aJest_droga_w_0|kHostFuncRoadNear|medium|Display label for the same near-road helper.|
|82|82|global|unit|clash95.c|aJest_droga_w_1|kScriptFuncRoadNearCastle|medium|Internal identifier for checking roads near a castle.|
|83|83|global|unit|clash95.c|aJest_droga_w_2|kHostFuncRoadNearCastle|medium|Display label for the castle-neighboring road rule.|
|84|84|global|unit|clash95.c|aJest_droga_do_|kScriptFuncRoadToPort|medium|Internal identifier string describing road access to a port.|
|85|85|global|unit|clash95.c|aJest_droga_d_0|kHostFuncRoadToPort|medium|Display label for port-road validations.|
|86|86|global|unit|clash95.c|aJest_droga_d_1|kScriptFuncRoadToCastle|medium|Internal identifier for castle road routes.|
|87|87|global|unit|clash95.c|aJest_droga_d_2|kHostFuncRoadToCastle|medium|Display label for castle road checks.|
|88|88|global|unit|clash95.c|aJest_droga_d_3|kScriptFuncRoadToTemple|medium|Internal identifier for temple road validations.|
|89|89|global|unit|clash95.c|aJest_droga_d_4|kHostFuncRoadToTemple|medium|Display label for temple road queries.|
|90|90|global|unit|clash95.c|aJest_droga00|kScriptFuncRoadExists|medium|Internal identifier for the general road-exists function.|
|91|91|global|unit|clash95.c|aJest_droga|kHostFuncRoadExists|medium|Display label for the same road existence helper.|
|92|92|global|unit|clash95.c|aJest_droga_w_3|kFmtRoadNearQuery|medium|Format string describing the three-argument nearby road query.|

## Batch 9 - Unit host command strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|93|93|global|unit|clash95.c|aOddzial_w_za_0|kScriptFuncSquadWithinArmy|medium|Internal identifier for "squad within army" script helper.|
|94|94|global|unit|clash95.c|aOddzial_w_za_1|kHostFuncSquadWithinArmy|medium|Display label for the same squad-range helper.|
|95|95|global|unit|clash95.c|aBudowla_w_zasi|kScriptFuncBuildingWithinArmy|medium|Internal identifier for evaluating building reachability.|
|96|96|global|unit|clash95.c|aBudowla_w_za_0|kHostFuncBuildingWithinArmy|medium|Display label for building range checks.|
|97|97|global|unit|clash95.c|aOdleglosc_od_o|kScriptFuncDistanceFromObject|medium|Internal identifier string for distance computations.|
|98|98|global|unit|clash95.c|aOdleglosc_od_0|kHostFuncDistanceFromObject|medium|Display label for the distance helper.|
|99|99|global|unit|clash95.c|aMaszeruj00|kScriptFuncMarch|medium|Internal identifier for the march command.|
|100|100|global|unit|clash95.c|aMaszeruj|kHostFuncMarch|medium|Display label for the generic march helper.|
|101|101|global|unit|clash95.c|aMaszeruj_do_sw|kScriptFuncMarchToTemple|medium|Internal identifier guiding temple movement.|
|102|102|global|unit|clash95.c|aMaszeruj_do__0|kHostFuncMarchToTemple|medium|Display label for the same temple march function.|
|103|103|global|unit|clash95.c|aMaszeruj_blisk|kScriptFuncMarchClose|medium|Internal identifier for "march nearby".|
|104|104|global|unit|clash95.c|aMaszeruj_bli_0|kHostFuncMarchClose|medium|Display label for the march-close helper.|
|105|105|global|unit|clash95.c|aAtakuj_oddzial|kScriptFuncAttackSquad|medium|Internal identifier for squad attack actions.|
|106|106|global|unit|clash95.c|aAtakuj_oddzi_0|kHostFuncAttackSquad|medium|Display label for the squad attack function.|
|107|107|global|unit|clash95.c|aPrzejmuj_oddzi|kScriptFuncCaptureSquad|medium|Internal identifier for capturing squads.|
|108|108|global|unit|clash95.c|aPrzejmuj_odd_0|kHostFuncCaptureSquad|medium|Display label for the capture-squad helper.|
|109|109|global|unit|clash95.c|aUkryj_oddzial0|kScriptFuncHideSquad|medium|Internal identifier for hiding squads.|
|110|110|global|unit|clash95.c|aUkryj_oddzial|kHostFuncHideSquad|medium|Display label for the hide-squad helper.|
|111|111|global|unit|clash95.c|aJest_armia00|kScriptFuncArmyExists|medium|Internal identifier verifying if an army exists.|
|112|112|global|unit|clash95.c|aJest_armia|kHostFuncArmyExists|medium|Display label for the same army existence check.|
|113|113|global|unit|clash95.c|aLiczba_jednost|kScriptFuncSquadUnitCount|medium|Internal identifier for retrieving unit counts per squad.|
|114|114|global|unit|clash95.c|aLiczba_jedno_0|kHostFuncSquadUnitCount|medium|Display label for the same unit-count helper.|
|115|115|global|unit|clash95.c|aAtakuj_budowle|kScriptFuncAttackBuilding|medium|Internal identifier for building assaults.|
|116|116|global|unit|clash95.c|aAtakuj_budow_0|kHostFuncAttackBuilding|medium|Display label for attacking buildings.|
|117|117|global|unit|clash95.c|aJest_brod00|kScriptFuncFordExists|medium|Internal identifier checking for a ford.|
|118|118|global|unit|clash95.c|aJest_brod|kHostFuncFordExists|medium|Display label for the ford-existence helper.|
|119|119|global|unit|clash95.c|aBuduj_droge00|kScriptFuncBuildRoad|medium|Internal identifier for building roads.|
|120|120|global|unit|clash95.c|aBuduj_droge|kHostFuncBuildRoad|medium|Display label for the build-road function.|
|121|121|global|unit|clash95.c|aBuduj_pulapke0|kScriptFuncBuildTrap|medium|Internal identifier for trap construction.|
|122|122|global|unit|clash95.c|aBuduj_pulapke|kHostFuncBuildTrap|medium|Display label for the trap construction helper.|

## Batch 10 - Unit format strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|123|123|global|unit|clash95.c|aOddzial_w_za_2|kFmtSquadWithinArmyQuery|medium|Format string echoing arguments to the squad-range rule.|
|124|124|global|unit|clash95.c|aOdleglosc_od_1|kFmtDistanceFromObjectQuery|medium|Format text describing distance query parameters.|
|125|125|global|unit|clash95.c|aMaszeruj_bli_1|kFmtMarchCloseQuery|medium|Formatted log for the march-nearby helper.|


## Batch 11 - Additional movement host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|126|126|global|unit|clash95.c|aMaszerujwzdluz|kScriptFuncMarchAlongRoad|medium|Internal identifier for the "march along road" helper.|
|127|127|global|unit|clash95.c|aMaszerujWzdluz|kHostFuncMarchAlongRoad|medium|Display label for the "march along road" rule hook.|

## Batch 12 - Army utility host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|128|128|global|unit|clash95.c|aZnajdz_najleps|kScriptFuncFindBestTarget|medium|Internal identifier for the "find best" targeting helper.|
|129|129|global|unit|clash95.c|aZnajdzNajlepsz|kHostFuncFindBestTarget|medium|Display label for the "find best" targeting helper.|
|130|130|global|unit|clash95.c|aPrzegrupujar_0|kFmtRegroupArmyCall|medium|Format string logging `PrzegrupujArmie` calls.|
|131|131|global|unit|clash95.c|aPrzegrupujza_0|kFmtRegroupCastleCall|medium|Format string logging `PrzegrupujZamek` calls.|
|132|132|global|unit|clash95.c|aZnajdzdrogewpo|kScriptFuncFindRoadNearCastle|medium|Internal identifier for the road-near-castle query.|
|133|133|global|unit|clash95.c|aZnajdzDrogeWPo|kHostFuncFindRoadNearCastle|medium|Display label for the road-near-castle query.|
|134|134|global|unit|clash95.c|aMocprzeciwnika|kScriptFuncEnemyPowerAtWalls|medium|Internal identifier tracking enemy strength under the walls.|
|135|135|global|unit|clash95.c|aMocPrzeciwnika|kHostFuncEnemyPowerAtWalls|medium|Display label for the same enemy-strength query.|
|136|136|global|unit|clash95.c|aStanosobarmii|kScriptFuncArmyHeadcount|medium|Internal identifier string for reporting army manpower.|
|137|137|global|unit|clash95.c|aStanOsobArmii|kHostFuncArmyHeadcount|medium|Display label for the army manpower report.|

## Batch 13 - Healing and plague host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|138|138|global|unit|clash95.c|aZnajdzzamekdol|kScriptFuncFindCastleForHealing|medium|Internal identifier for finding a healing castle.|
|139|139|global|unit|clash95.c|aZnajdzZamekDoL|kHostFuncFindCastleForHealing|medium|Display label for the healing-castle lookup.|
|140|140|global|unit|clash95.c|aIdzdoleczenia|kScriptFuncSendUnitsToHealing|medium|Internal identifier for dispatching troops to healing.|
|141|141|global|unit|clash95.c|aIdzDoLeczenia|kHostFuncSendUnitsToHealing|medium|Display label for dispatching troops to healing.|
|142|142|global|unit|clash95.c|aJestzarazawzam|kScriptFuncCastlePlague|medium|Internal identifier for castle plague checks.|
|143|143|global|unit|clash95.c|aJestZarazaWZam|kHostFuncCastlePlague|medium|Display label for castle plague checks.|
|144|144|global|unit|clash95.c|aJestzarazawodd|kScriptFuncSquadPlague|medium|Internal identifier for squad-level plague detection.|
|145|145|global|unit|clash95.c|aJestZarazaWOdd|kHostFuncSquadPlague|medium|Display label for that squad plague check.|

## Batch 14 - Castle economy host strings A
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|146|146|global|castle|clash95.c|aLeczenie|kFuncNameCastleHealing|medium|Identifier string for the castle healing action.|
|147|147|global|castle|clash95.c|aSzkolenie|kFuncNameCastleTraining|medium|Identifier string for castle training commands.|
|148|148|global|castle|clash95.c|aPalbudowle|kScriptFuncBurnBuildings|medium|Internal identifier for the burn-buildings host rule.|
|149|149|global|castle|clash95.c|aPalBudowle|kHostFuncBurnBuildings|medium|Display label for the burn-buildings rule.|
|150|150|global|castle|clash95.c|aUpgradewall|kScriptFuncUpgradeWalls|medium|Internal name for wall-upgrade operations.|
|151|151|global|castle|clash95.c|aUpgradeWall|kHostFuncUpgradeWalls|medium|Display label for wall upgrades.|
|152|152|global|castle|clash95.c|aZmienpodatek|kScriptFuncChangeTax|medium|Internal identifier for changing castle tax.|
|153|153|global|castle|clash95.c|aZmienPodatek|kHostFuncChangeTax|medium|Display label for the castle tax change command.|
|154|154|global|castle|clash95.c|aRemovelicence|kScriptFuncRemoveLicence|medium|Internal identifier for removing a licence.|
|155|155|global|castle|clash95.c|aRemoveLicence|kHostFuncRemoveLicence|medium|Display label for the remove-licence rule.|
|156|156|global|castle|clash95.c|aZacznijleczeni|kScriptFuncStartHealing|medium|Internal identifier for starting healing production.|
|157|157|global|castle|clash95.c|aZacznijLeczeni|kHostFuncStartHealing|medium|Display label for the start-healing option.|

## Batch 15 - Castle economy host strings B
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|158|158|global|castle|clash95.c|aZacznijszkolen|kScriptFuncStartTraining|medium|Internal identifier for starting castle training.|
|159|159|global|castle|clash95.c|aZacznijSzkolen|kHostFuncStartTraining|medium|Display label for the start-training host command.|
|160|160|global|castle|clash95.c|aZacznijprodukc|kScriptFuncStartProduction|medium|Internal identifier for starting castle production.|
|161|161|global|castle|clash95.c|aZacznijProdukc|kHostFuncStartProduction|medium|Display label for the production startup rule.|
|162|162|global|castle|clash95.c|aKupszkola|kScriptFuncBuySchool|medium|Internal identifier for purchasing a school building.|
|163|163|global|castle|clash95.c|aKupSzkola|kHostFuncBuySchool|medium|Display label for buying a school.|
|164|164|global|castle|clash95.c|aKupkuznia|kScriptFuncBuyForge|medium|Internal identifier for buying a forge.|
|165|165|global|castle|clash95.c|aKupKuznia|kHostFuncBuyForge|medium|Display label for buying a forge.|
|166|166|global|castle|clash95.c|aIslicence|kScriptFuncHasLicence|medium|Internal identifier for licence-availability checks.|
|167|167|global|castle|clash95.c|aIsLicence|kHostFuncHasLicence|medium|Display label for checking licence presence.|
|168|168|global|castle|clash95.c|aBuylicence|kScriptFuncBuyLicence|medium|Internal identifier for buying licences.|
|169|169|global|castle|clash95.c|aBuyLicence|kHostFuncBuyLicence|medium|Display label for buying a licence.|
|170|170|global|castle|clash95.c|aKupszpital|kScriptFuncBuyHospital|medium|Internal identifier for buying a hospital.|
|171|171|global|castle|clash95.c|aKupSzpital|kHostFuncBuyHospital|medium|Display label for the hospital purchase command.|
|172|172|global|castle|clash95.c|aBudujzamek|kScriptFuncBuildCastle|medium|Internal identifier for castle construction.|
|173|173|global|castle|clash95.c|aBudujZamek|kHostFuncBuildCastle|medium|Display label for castle construction.|
|174|174|global|castle|clash95.c|aKupkoszary|kScriptFuncBuyBarracks|medium|Internal identifier for purchasing barracks.|
|175|175|global|castle|clash95.c|aKupKoszary|kHostFuncBuyBarracks|medium|Display label for buying barracks.|
|176|176|global|castle|clash95.c|aKupwarsztat|kScriptFuncBuyWorkshop|medium|Internal identifier for purchasing a workshop.|
|177|177|global|castle|clash95.c|aKupWarsztat|kHostFuncBuyWorkshop|medium|Display label for buying a workshop.|
|178|178|global|castle|clash95.c|aIsproduction|kScriptFuncIsProductionRunning|medium|Internal identifier for checking active production.|
|179|179|global|castle|clash95.c|aIsProduction|kHostFuncIsProductionRunning|medium|Display label for the production status check.|
|180|180|global|castle|clash95.c|aCzyminimalny|kScriptFuncIsMinimalTax|medium|Internal identifier for verifying minimum tax levels.|
|181|181|global|castle|clash95.c|aCzyMinimalny|kHostFuncIsMinimalTax|medium|Display label for the same tax-level check.|
|182|182|global|castle|clash95.c|aCanbuylicence|kScriptFuncCanBuyLicence|medium|Internal identifier for whether a licence can be bought.|
|183|183|global|castle|clash95.c|aCanBuyLicence|kHostFuncCanBuyLicence|medium|Display label for the same licence purchase feasibility check.|
|184|184|global|castle|clash95.c|aIsproductionan|kScriptFuncAnyProduction|medium|Internal identifier for checking if any production exists.|
|185|185|global|castle|clash95.c|aIsProductionAn|kHostFuncAnyProduction|medium|Display label for checking any production.|
|186|186|global|castle|clash95.c|aMaxiloscoddzia|kScriptFuncMaxSquadCount|medium|Internal identifier for retrieving max squad count.|
|187|187|global|castle|clash95.c|aMaxIloscOddzia|kHostFuncMaxSquadCount|medium|Display label for the max squad count query.|

## Batch 16 - Castle status host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|188|188|global|castle|clash95.c|aPodatek|kFuncNameCastleTax|medium|Identifier string for querying castle taxes.|
|189|189|global|castle|clash95.c|aPieniadze|kFuncNameCastleGold|medium|Identifier string for querying castle treasury.|
|190|190|global|castle|clash95.c|aSilamurow|kScriptFuncWallStrength|medium|Internal identifier for wall strength checks.|
|191|191|global|castle|clash95.c|aSilaMurow|kHostFuncWallStrength|medium|Display label for wall strength checks.|
|192|192|global|castle|clash95.c|aSilazamku|kScriptFuncCastleStrength|medium|Internal identifier for castle strength queries.|
|193|193|global|castle|clash95.c|aSilaZamku|kHostFuncCastleStrength|medium|Display label for castle strength queries.|
|194|194|global|castle|clash95.c|aNumertury|kScriptFuncTurnNumber|medium|Internal identifier for retrieving the turn number.|
|195|195|global|castle|clash95.c|aNumerTury|kHostFuncTurnNumber|medium|Display label for turn number queries.|
|196|196|global|castle|clash95.c|aPoziomtech|kScriptFuncTechLevel|medium|Internal identifier for stating technology level.|
|197|197|global|castle|clash95.c|aPoziomTech|kHostFuncTechLevel|medium|Display label for technology level queries.|
|198|198|global|castle|clash95.c|aZadowolenie|kFuncNameCastleHappiness|medium|Identifier string for castle happiness queries.|
|199|199|global|castle|clash95.c|aTypbudowli|kScriptFuncBuildingType|medium|Internal identifier for reporting building type.|
|200|200|global|castle|clash95.c|aTypBudowli|kHostFuncBuildingType|medium|Display label for the building-type query.|
|201|201|global|castle|clash95.c|aSilagracza|kScriptFuncPlayerStrength|medium|Internal identifier for player strength queries.|
|202|202|global|castle|clash95.c|aSilaGracza|kHostFuncPlayerStrength|medium|Display label for the player strength function.|
|203|203|global|castle|clash95.c|aIloscchlopow|kScriptFuncPeasantCount|medium|Internal identifier counting peasants.|
|204|204|global|castle|clash95.c|aIloscChlopow|kHostFuncPeasantCount|medium|Display label for the peasant count query.|
|205|205|global|castle|clash95.c|aLicencjaindex|kScriptFuncLicenceIndex|medium|Internal identifier for licence index lookups.|
|206|206|global|castle|clash95.c|aLicencjaIndex|kHostFuncLicenceIndex|medium|Display label for the licence index query.|
|207|207|global|castle|clash95.c|aLicencjaind|kScriptFuncLicenceId|medium|Internal identifier for licence ID lookups.|
|208|208|global|castle|clash95.c|aLicencjaInd|kHostFuncLicenceId|medium|Display label for the licence ID query.|
|209|209|global|castle|clash95.c|aIloscoddzialow|kScriptFuncSquadCount|medium|Internal identifier for total squad count queries.|
|210|210|global|castle|clash95.c|aIloscOddzialow|kHostFuncSquadCount|medium|Display label for the total squad count query.|
|211|211|global|castle|clash95.c|aCanupgradewall|kScriptFuncCanUpgradeWalls|medium|Internal identifier for checking wall upgrade eligibility.|
|212|212|global|castle|clash95.c|aCanUpgradeWall|kHostFuncCanUpgradeWalls|medium|Display label for the wall upgrade eligibility check.|
|213|213|global|castle|clash95.c|aWyprowadzchlop|kScriptFuncEvictPeasants|medium|Internal identifier for removing peasants from the castle.|
|214|214|global|castle|clash95.c|aWyprowadzChlop|kHostFuncEvictPeasants|medium|Display label for the peasants eviction command.|
|215|215|global|castle|clash95.c|aWyprowadzenieo|kScriptFuncEvacuateSquad|medium|Internal identifier for evacuating a squad.|
|216|216|global|castle|clash95.c|aWyprowadzenieO|kHostFuncEvacuateSquad|medium|Display label for the squad evacuation rule.|
|217|217|global|castle|clash95.c|aWyprowadzeni_0|kScriptFuncEvacuateAllUnits|medium|Internal identifier for evacuating all units.|
|218|218|global|castle|clash95.c|aWyprowadzeni_1|kHostFuncEvacuateAllUnits|medium|Display label for evacuating all units.|
|219|219|global|castle|clash95.c|aNazwazamku|kScriptFuncCastleName|medium|Internal identifier for retrieving the castle name.|
|220|220|global|castle|clash95.c|aNazwaZamku|kHostFuncCastleName|medium|Display label for the castle name query.|

## Batch 17 - Castle regrouping host strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|221|221|global|castle|clash95.c|aWejdzdozamku|kScriptFuncEnterCastle|medium|Internal identifier for the enter-castle action.|
|222|222|global|castle|clash95.c|aWejdzDoZamku|kHostFuncEnterCastle|medium|Display label for the enter-castle action.|
|223|223|global|castle|clash95.c|aDolaczdoarmii|kScriptFuncJoinArmy|medium|Internal identifier for attaching units to an army.|
|224|224|global|castle|clash95.c|aDolaczDoOddzia|kHostFuncJoinArmy|medium|Display label for the join-army host command.|
|225|225|global|castle|clash95.c|aPrzegrupujarmi|kScriptFuncRegroupArmy|medium|Internal identifier for regrouping an army.|
|226|226|global|castle|clash95.c|aPrzegrupujOddz|kHostFuncRegroupArmy|medium|Display label for the regroup-army rule.|
|227|227|global|castle|clash95.c|aPrzegrupujzame|kScriptFuncRegroupCastle|medium|Internal identifier for regrouping castle defenses.|
|228|228|global|castle|clash95.c|aPrzegrupujZame|kHostFuncRegroupCastle|medium|Display label for the regroup-castle command.|
|229|229|global|castle|clash95.c|aLiczbawolnychm|kScriptFuncFreeCastleSlots|medium|Internal identifier reporting free castle slots.|
|230|230|global|castle|clash95.c|aLiczbaWolnychM|kHostFuncFreeCastleSlots|medium|Display label for the free castle slots query.|

## Batch 18 - Generic yes/no literals
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|231|231|global|other|clash95.c|aNie|kTextPolishNo|high|Literal Polish "NIE" (No) text constant.|
|232|232|global|other|clash95.c|aTak|kTextPolishYes|high|Literal Polish "TAK" (Yes) text constant.|
|233|233|global|other|clash95.c|aNie_0|kTextPolishNoAlt1|high|Alternate "NIE" literal reused across dialogs.|
|234|234|global|other|clash95.c|aTak_0|kTextPolishYesAlt1|high|Alternate "TAK" literal reused across dialogs.|
|235|235|global|other|clash95.c|aNie_1|kTextPolishNoAlt2|high|Additional "NIE" constant.|
|236|236|global|other|clash95.c|aTak_1|kTextPolishYesAlt2|high|Additional "TAK" constant.|
|237|237|global|other|clash95.c|aNie_2|kTextPolishNoAlt3|high|Third "NIE" literal slot.|
|238|238|global|other|clash95.c|aTak_2|kTextPolishYesAlt3|high|Third "TAK" literal slot.|
|239|239|global|other|clash95.c|aNie_3|kTextPolishNoAlt4|high|Fourth "NIE" literal slot.|
|240|240|global|other|clash95.c|aTak_3|kTextPolishYesAlt4|high|Fourth "TAK" literal slot.|

## Batch 19 - Generic player/power labels
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|241|241|global|other|clash95.c|aGracz|kLabelPlayerLower|high|Literal Polish word for player used in logs.|
|242|242|global|other|clash95.c|aGracz_0|kLabelPlayerLowerAlt|high|Alternate literal "gracz" string.|
|243|243|global|other|clash95.c|aMoc|kLabelPowerLower|medium|Literal "moc" (power) string for UI/logging.|
|244|244|global|other|clash95.c|aMoc_0|kLabelPowerLowerAlt|medium|Alternate "moc" text constant.|
|245|245|global|other|clash95.c|aMoc_1|kLabelPowerLowerAlt2|medium|Third "moc" literal reuse.|
|246|246|global|other|clash95.c|aMoc_2|kLabelPowerLowerAlt3|medium|Fourth "moc" literal reuse.|

## Batch 20 - CLIPS core commands
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|247|247|global|other|clash95.c|aClearcommand|kScriptCmdClear|high|Script identifier for the CLIPS clear command.|
|248|248|global|other|clash95.c|aClear|kHostCmdClear|high|Host-visible name for the clear command.|
|249|249|global|other|clash95.c|aResetcommand|kScriptCmdReset|high|Script identifier for the CLIPS reset command.|
|250|250|global|other|clash95.c|aReset|kHostCmdReset|high|Host-visible name for the reset command.|
|251|251|global|other|clash95.c|aRefreshcommand|kScriptCmdRefresh|high|Script identifier for the refresh command.|
|252|252|global|other|clash95.c|aRefresh|kHostCmdRefresh|high|Host-visible name for the refresh command.|
|253|253|global|other|clash95.c|aRefreshagendac|kScriptCmdRefreshAgenda|high|Script identifier for refreshing the agenda.|
|254|254|global|other|clash95.c|aRefreshAgenda|kHostCmdRefreshAgenda|high|Host-visible name for the refresh-agenda command.|

## Batch 21 - CLIPS fact commands
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|255|255|global|other|clash95.c|aFactscommand|kScriptCmdFacts|high|Script identifier for the CLIPS facts command.|
|256|256|global|other|clash95.c|aFacts_1|kHostCmdFacts|high|Host-visible name for the facts command.|
|257|257|global|other|clash95.c|aAssertcommand|kScriptCmdAssert|high|Script identifier for the assert command.|
|258|258|global|other|clash95.c|aAssert|kHostCmdAssert|high|Host-visible name for the assert command.|
|259|259|global|other|clash95.c|aRetractcommand|kScriptCmdRetract|high|Script identifier for the retract command.|
|260|260|global|other|clash95.c|aRetract_0|kHostCmdRetract|high|Host-visible name for the retract command.|
|261|261|global|other|clash95.c|aAssertstringfu|kScriptCmdAssertString|high|Script identifier for the assert-string helper.|
|262|262|global|other|clash95.c|aAssertString|kHostCmdAssertString|high|Host-visible name for assert-string.|
|263|263|global|other|clash95.c|aStrAssert|kHostCmdAssertStringAlias|high|Alternate host-visible name for assert-string.|
|264|264|global|other|clash95.c|aGetfactduplica|kScriptCmdGetFactDuplication|high|Script identifier for get-fact-duplication.|
|265|265|global|other|clash95.c|aGetFactDuplica|kHostCmdGetFactDuplication|high|Host-visible name for get-fact-duplication.|
|266|266|global|other|clash95.c|aSetfactduplica|kScriptCmdSetFactDuplication|high|Script identifier for set-fact-duplication.|
|267|267|global|other|clash95.c|aSetFactDuplica|kHostCmdSetFactDuplication|high|Host-visible name for set-fact-duplication.|
|268|268|global|other|clash95.c|aSavefactscomma|kScriptCmdSaveFacts|high|Script identifier for save-facts.|
|269|269|global|other|clash95.c|aSaveFacts|kHostCmdSaveFacts|high|Host-visible name for save-facts.|
|270|270|global|other|clash95.c|aLoadfactscomma|kScriptCmdLoadFacts|high|Script identifier for load-facts.|
|271|271|global|other|clash95.c|aLoadFacts|kHostCmdLoadFacts|high|Host-visible name for load-facts.|
|272|272|global|other|clash95.c|aFactindexfunct|kScriptFuncFactIndex|high|Script identifier for the fact-index function.|
|273|273|global|other|clash95.c|aFactIndex|kHostFuncFactIndex|high|Host-visible name for fact-index.|

## Batch 22 - CLIPS agenda commands
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|274|274|global|other|clash95.c|aGetsalienceeva|kScriptCmdGetSalience|high|Script identifier for get-salience-evaluation.|
|275|275|global|other|clash95.c|aGetSalienceEva|kHostCmdGetSalience|high|Host-visible name for get-salience-evaluation.|
|276|276|global|other|clash95.c|aSetsalienceeva|kScriptCmdSetSalience|high|Script identifier for set-salience-evaluation.|
|277|277|global|other|clash95.c|aSetSalienceEva|kHostCmdSetSalience|high|Host-visible name for set-salience-evaluation.|
|278|278|global|other|clash95.c|aAgendacommand|kScriptCmdAgenda|high|Script identifier for the agenda command.|
|279|279|global|other|clash95.c|aAgenda_0|kHostCmdAgenda|high|Host-visible name for the agenda command.|

## Batch 23 - Instance command strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|280|280|global|other|clash95.c|aInitializeinst|kScriptCmdInitializeInstance|high|Script identifier for initialize-instance.|
|281|281|global|other|clash95.c|aInitializeInst|kHostCmdInitializeInstance|high|Host-visible name for initialize-instance.|
|282|282|global|other|clash95.c|aActiveInitiali|kHostCmdActiveInitializeInstance|high|Host-visible name for active-initialize-instance.|
|283|283|global|other|clash95.c|aMakeinstanceco|kScriptCmdMakeInstance|high|Script identifier for make-instance.|
|284|284|global|other|clash95.c|aMakeInstance|kHostCmdMakeInstance|high|Host-visible name for make-instance.|
|285|285|global|other|clash95.c|aActiveMakeInst|kHostCmdActiveMakeInstance|high|Host-visible name for active-make-instance.|
|286|286|global|other|clash95.c|aInitSlots|kHostCmdInitSlots|high|Host-visible name for init-slots.|
|287|287|global|other|clash95.c|aDeleteinstance|kScriptCmdDeleteInstance|high|Script identifier for delete-instance.|
|288|288|global|other|clash95.c|aDeleteInstance|kHostCmdDeleteInstance|high|Host-visible name for delete-instance.|
|289|289|global|other|clash95.c|aUnmakeinstance|kScriptCmdUnmakeInstance|high|Script identifier for unmake-instance.|
|290|290|global|other|clash95.c|aUnmakeInstance|kHostCmdUnmakeInstance|high|Host-visible name for unmake-instance.|
|291|291|global|other|clash95.c|aInstancescomma|kScriptCmdInstances|high|Script identifier for the instances command.|
|292|292|global|other|clash95.c|aInstances|kHostCmdInstances|high|Host-visible name for the instances command.|
|293|293|global|other|clash95.c|aPpinstancecomm|kScriptCmdPpInstance|high|Script identifier for ppinstance.|
|294|294|global|other|clash95.c|aPpinstance|kHostCmdPpInstance|high|Host-visible name for ppinstance.|
|295|295|global|other|clash95.c|aSymboltoinstan|kScriptFuncSymbolToInstanceName|high|Script identifier for symbol-to-instance-name.|
|296|296|global|other|clash95.c|aSymbolToInstan|kHostFuncSymbolToInstanceName|high|Host-visible name for symbol-to-instance-name.|
|297|297|global|other|clash95.c|aInstancenameto|kScriptFuncInstanceNameToSymbol|high|Script identifier for instance-name-to-symbol.|
|298|298|global|other|clash95.c|aInstanceNameTo|kHostFuncInstanceNameToSymbol|high|Host-visible name for instance-name-to-symbol.|
|299|299|global|other|clash95.c|aInstanceaddres|kScriptCmdInstanceAddress|high|Script identifier for instance-address.|
|300|300|global|other|clash95.c|aInstanceAddres|kHostCmdInstanceAddress|high|Host-visible name for instance-address.|
|301|301|global|other|clash95.c|aInstanceaddr_0|kScriptCmdInstanceAddressP|high|Script identifier for instance-addressp.|
|302|302|global|other|clash95.c|aInstanceAddr_0|kHostCmdInstanceAddressP|high|Host-visible name for instance-addressp.|
|303|303|global|other|clash95.c|aInstancenamepc|kScriptCmdInstanceNameP|high|Script identifier for instance-namep.|
|304|304|global|other|clash95.c|aInstanceNamep|kHostCmdInstanceNameP|high|Host-visible name for instance-namep.|
|305|305|global|other|clash95.c|aInstancenameco|kScriptCmdInstanceName|high|Script identifier for instance-name command.|
|306|306|global|other|clash95.c|aInstanceName|kHostCmdInstanceName|high|Host-visible name for instance-name.|
|307|307|global|other|clash95.c|aInstancepcomma|kScriptCmdInstanceP|high|Script identifier for instancep.|
|308|308|global|other|clash95.c|aInstancep|kHostCmdInstanceP|high|Host-visible name for instancep.|
|309|309|global|other|clash95.c|aInstanceexistp|kScriptCmdInstanceExistP|high|Script identifier for instance-existp.|
|310|310|global|other|clash95.c|aInstanceExistp|kHostCmdInstanceExistP|high|Host-visible name for instance-existp.|
|311|311|global|other|clash95.c|aClasscommand_0|kScriptCmdClass|high|Script identifier for the class command.|
|312|312|global|other|clash95.c|aClass|kHostCmdClass|high|Host-visible name for the class command.|

## Batch 24 - Watch command strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|313|313|global|other|clash95.c|aWatchcommand|kScriptCmdWatch|high|Script identifier for the watch command.|
|314|314|global|other|clash95.c|aWatch|kHostCmdWatch|high|Host-visible name for the watch command.|
|315|315|global|other|clash95.c|aUnwatchcommand|kScriptCmdUnwatch|high|Script identifier for the unwatch command.|
|316|316|global|other|clash95.c|aUnwatch|kHostCmdUnwatch|high|Host-visible name for the unwatch command.|
|317|317|global|other|clash95.c|aListwatchitems|kScriptCmdListWatchItems|high|Script identifier for list-watch-items.|
|318|318|global|other|clash95.c|aListWatchItems|kHostCmdListWatchItems|high|Host-visible name for list-watch-items.|

## Batch 25 - Strategy and agenda commands
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|319|319|global|other|clash95.c|aListfocusstack|kScriptCmdListFocusStack|high|Script identifier for the list-focus-stack command.|
|320|320|global|other|clash95.c|aListFocusStack|kHostCmdListFocusStack|high|Host-visible name for the list-focus-stack command.|
|321|321|global|other|clash95.c|aDependenciesco|kScriptCmdDependencies|high|Script identifier for the dependencies command.|
|322|322|global|other|clash95.c|aDependencies|kHostCmdDependencies|high|Host-visible name for the dependencies command.|
|323|323|global|other|clash95.c|aDependentscomm|kScriptCmdDependents|high|Script identifier for the dependents command.|
|324|324|global|other|clash95.c|aDependents|kHostCmdDependents|high|Host-visible name for the dependents command.|
|325|325|global|other|clash95.c|aGetincremental|kScriptCmdGetIncrementalReset|high|Script identifier for the get-incremental-reset command.|
|326|326|global|other|clash95.c|aGetIncremental|kHostCmdGetIncrementalReset|high|Host-visible name for the get-incremental-reset command.|
|327|327|global|other|clash95.c|aSetincremental|kScriptCmdSetIncrementalReset|high|Script identifier for the set-incremental-reset command.|
|328|328|global|other|clash95.c|aSetIncremental|kHostCmdSetIncrementalReset|high|Host-visible name for the set-incremental-reset command.|
|329|329|global|other|clash95.c|aGetstrategycom|kScriptCmdGetStrategy|high|Script identifier for the get-strategy command.|
|330|330|global|other|clash95.c|aGetStrategy|kHostCmdGetStrategy|high|Host-visible name for the get-strategy command.|
|331|331|global|other|clash95.c|aSetstrategycom|kScriptCmdSetStrategy|high|Script identifier for the set-strategy command.|
|332|332|global|other|clash95.c|aSetStrategy|kHostCmdSetStrategy|high|Host-visible name for the set-strategy command.|
|333|333|global|other|clash95.c|aMatchescommand|kScriptCmdMatches|high|Script identifier for the matches command.|
|334|334|global|other|clash95.c|aMatches|kHostCmdMatches|high|Host-visible name for the matches command.|

## Batch 26 - Fact helper functions
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|335|335|global|other|clash95.c|aFactexistpfunc|kScriptFuncFactExistP|high|Script identifier for fact-existp.|
|336|336|global|other|clash95.c|aFactExistp|kHostFuncFactExistP|high|Host-visible name for fact-existp.|
|337|337|global|other|clash95.c|aFactrelationfu|kScriptFuncFactRelation|high|Script identifier for fact-relation.|
|338|338|global|other|clash95.c|aFactRelation|kHostFuncFactRelation|high|Host-visible name for fact-relation.|
|339|339|global|other|clash95.c|aFactslotvaluef|kScriptFuncFactSlotValue|high|Script identifier for fact-slot-value.|
|340|340|global|other|clash95.c|aFactSlotValue|kHostFuncFactSlotValue|high|Host-visible name for fact-slot-value.|
|341|341|global|other|clash95.c|aFactslotnamesf|kScriptFuncFactSlotNames|high|Script identifier for fact-slot-names.|
|342|342|global|other|clash95.c|aFactSlotNames|kHostFuncFactSlotNames|high|Host-visible name for fact-slot-names.|
|343|343|global|other|clash95.c|aGetfactlistfun|kScriptFuncGetFactList|high|Script identifier for get-fact-list.|
|344|344|global|other|clash95.c|aGetFactList|kHostFuncGetFactList|high|Host-visible name for get-fact-list.|

## Batch 27 - Castle prisoner strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|345|345|global|castle|clash95.c|aZamek_1Anim_s3|kCastleAnimSetResource|high|Castle animation resource filename.|
|346|346|global|castle|clash95.c|aZamek_0|kLabelCastleAlt|medium|Secondary castle label string used when creating castles.|
|347|347|global|castle|clash95.c|aZamek|kLabelCastle|medium|Primary castle label string for creation routines.|
|348|348|global|castle|clash95.c|aCantbelly_3|kBuildingLabelCantbellyFort|medium|Name label passed when spawning the Cantbelly fort building.|
|349|349|global|castle|clash95.c|aCantbelly_0|kBuildingLabelCantbellyVillage|medium|Variant Cantbelly label for another structure.|
|350|350|global|castle|clash95.c|aCantbelly|kBuildingLabelCantbellyTown|medium|Cantbelly label used for castle placement.|
|351|351|global|castle|clash95.c|aKopegon|kBuildingLabelKopegon|medium|Label used when creating the Kopegon building.|
|352|352|global|castle|clash95.c|aPrisoner_addto|kFmtPrisonerAddToInWay|high|Format string tracing Prisoner_AddToInWay arguments.|
|353|353|global|castle|clash95.c|aPrisoner_setin|kLogPrisonerSetInCastles|high|Log text for Prisoner_SetInCastles() calls.|
|354|354|global|castle|clash95.c|aUwiezic|kActionLabelImprison|medium|UI/action label for imprisoning a captive.|
|355|355|global|castle|clash95.c|aBuilding_setpr|kFmtBuildingSetPrisonerAction|high|Format string logging Building_SetPrisonerAction.|
|356|356|global|castle|clash95.c|aPrisoner_kill0|kFmtPrisonerKill|high|Format string for Prisoner_Kill invocation.|
|357|357|global|castle|clash95.c|aPrisoner_behea|kFmtPrisonerBehead|high|Format string for Prisoner_Behead logging.|
|358|358|global|castle|clash95.c|aZciecie|kActionLabelBeheading|medium|Localized label for executing a prisoner by beheading.|
|359|359|global|castle|clash95.c|aPrisoner_tortu|kFmtPrisonerTorture|high|Format string for Prisoner_Torture calls.|
|360|360|global|castle|clash95.c|aPrisoner_tor_0|kLogPrisonerTortureResult0|medium|Outcome label when torture produced result 0.|
|361|361|global|castle|clash95.c|aPrisoner_tor_1|kLogPrisonerTortureResult1|medium|Outcome label when torture produced result 1.|
|362|362|global|castle|clash95.c|aPrisoner_tor_2|kLogPrisonerTortureResult2|medium|Outcome label when torture produced result 2.|
|363|363|global|castle|clash95.c|aPrisoner_tor_3|kLogPrisonerTortureResult3|medium|Outcome label when torture produced result 3.|
|364|364|global|castle|clash95.c|aPrisoner_tor_4|kLogPrisonerTortureResult4|medium|Outcome label when torture produced result 4.|
|365|365|global|castle|clash95.c|aBuilding_creat|kFmtBuildingCreateSpecial|high|Format string logging Building_CreateSpecial.|
|366|366|global|castle|clash95.c|aPrisoner_pay0x|kFmtPrisonerPay|high|Format string logging Prisoner_Pay.|
|367|367|global|castle|clash95.c|aPrisoner_newtu|kFmtPrisonerNewTurn|high|Format string logging Prisoner_NewTurn.|

## Batch 28 - Building logging strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|368|368|global|castle|clash95.c|aBuildingsCache|kLogBuildingsCacheEntries|high|Log line reporting building cache size.|
|369|369|global|castle|clash95.c|aBuilding_newDD|kFmtBuildingNew|high|Format string describing Building_New arguments.|
|370|370|global|castle|clash95.c|aBuilding_stop0|kFmtBuildingStop|high|Format string tracing Building_Stop calls.|
|371|371|global|castle|clash95.c|aBuilding_build|kLogBuildingBuildFinished|medium|Polish log emitted when building construction finishes.|
|372|372|global|castle|clash95.c|aBuilding_produ|kLogBuildingProduction|medium|Log text for Building_Production signaling new unit.|
|373|373|global|castle|clash95.c|aBuilding_check|kFmtBuildingCheckTechnology|high|Format string for Building_CheckTechnology.|
|374|374|global|castle|clash95.c|aBuilding_newtu|kLogBuildingNewTurn|high|Log text for Building_NewTurn processing.|
|375|375|global|castle|clash95.c|aBuilding_getin|kFmtBuildingGetInto|high|Format string for Building_GetInto.|
|376|376|global|castle|clash95.c|aBuilding_bui_4|kLogBuildingBuildWorkshop|medium|Log for Building_BuildWorkshop coordinates.|
|377|377|global|castle|clash95.c|aBuilding_bui_2|kLogBuildingBuildBarracks|medium|Log for Building_BuildBarracks coordinates.|
|378|378|global|castle|clash95.c|aBuilding_bui_3|kLogBuildingBuildHospital|medium|Log for Building_BuildHospital coordinates.|
|379|379|global|castle|clash95.c|aBuilding_bui_1|kLogBuildingBuildSmiths|medium|Log for Building_BuildSmiths coordinates.|
|380|380|global|castle|clash95.c|aBuilding_findf|kLogBuildingFindFreePlace|medium|Log for Building_FindFreePlaceNear results.|
|381|381|global|castle|clash95.c|aBuilding_trans|kFmtBuildingTransfer|high|Format string for Building_Transfer arguments.|
|382|382|global|castle|clash95.c|aBuilding_destr|kFmtBuildingDestroy|high|Format string for Building_Destroy.|
|383|383|global|castle|clash95.c|aBuilding_units|kFmtBuildingUnitsLeave|high|Format string for Building_UnitsLeave.|
|384|384|global|castle|clash95.c|aBuildings_unit|kLogBuildingUnitLeaveOk|high|Success log for Buildings_UnitLeave.|
|385|385|global|castle|clash95.c|aBuilding_unitg|kFmtBuildingUnitGetInto|high|Format string for Building_UnitGetInto.|
|386|386|global|castle|clash95.c|aBuilding_buyun|kFmtBuildingBuyUnitLicence|high|Format string for Building_BuyUnitLicence.|
|387|387|global|castle|clash95.c|aBuilding_remov|kFmtBuildingRemoveUnitLicence|high|Format string for Building_RemoveUnitLicence.|
|388|388|global|castle|clash95.c|aBuilding_setun|kFmtBuildingSetUnitProduction|high|Format string for Building_SetUnitProduction.|
|389|389|global|castle|clash95.c|aBuilding_stopu|kFmtBuildingStopUnitProduction|high|Format string for Building_StopUnitProduction.|
|390|390|global|castle|clash95.c|aBuilding_train|kFmtBuildingTrainUnit|high|Format string for Building_TrainUnit.|
|391|391|global|castle|clash95.c|aBuilding_repai|kFmtBuildingRepairUnit|high|Format string for Building_RepairUnit.|

## Batch 29 - Track logging strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|392|392|global|tile|clash95.c|aTrack_bridgeso|kLogTrackBridgesOn|high|Log message emitted when Track_BridgesOn is called.|
|393|393|global|tile|clash95.c|aTrack_bridge_0|kLogTrackBridgesOff|high|Log message emitted when Track_BridgesOff is called.|

## Batch 30 - Temple logs
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|394|394|global|castle|clash95.c|aTemple_random|kLogTempleRandom|medium|Log marker when Temple_Random executes.|
|395|395|global|castle|clash95.c|aTemple_process|kFmtTempleProcessGift|high|Format string for Temple_ProcessGift arguments.|
|396|396|global|castle|clash95.c|aTemple_unitget|kFmtTempleUnitGetInto|high|Format string for Temple_UnitGetInto inputs.|
|397|397|global|castle|clash95.c|aTemple_unitg_0|kLogTempleUnitWrongOwner|medium|Polish message logged when a unit enters another faction's temple.|
|398|398|global|castle|clash95.c|aTemple_unitg_2|kLogTempleUnitAlreadyVisited|medium|Polish message when the temple was already visited.|
|399|399|global|castle|clash95.c|aTemple_unitg_1|kLogTempleUnitRoll|medium|Message logging the random roll for temple outcome.|

## Batch 31 - Misc castle logging
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|400|400|global|castle|clash95.c|aPlayer_surrend|kFmtPlayerSurrender|high|Format string logging Player_Surrender invocations.|

## Batch 32 - Castle resource paths
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|401|401|global|castle|clash95.c|aCastleD|kFmtCastleIndex|medium|castle log string when referencing castle ids.|
|402|402|global|castle|clash95.c|aCastle|kFolderCastle|medium|base path string used when loading castle resources.|
|403|403|global|castle|clash95.c|aCastle_chrDw_1|kCastleChrDw15Gfx|medium|resource path for castle chr dw_15 gfx.|
|404|404|global|castle|clash95.c|aCastle_pogDw_1|kCastlePogDw15Gfx|medium|resource path for castle pog dw_15 gfx.|
|405|405|global|castle|clash95.c|aCastle_chrDw_2|kCastleChrDw15Base|medium|resource path for base castle chr dw_15 asset.|
|406|406|global|castle|clash95.c|aCastle_pogDw_2|kCastlePogDw15Base|medium|resource path for base castle pog dw_15 asset.|
|407|407|global|castle|clash95.c|aCastle_chrD_15|kCastleChrDw12Gfx|medium|chr dw_12 gfx path for castle rendering.|
|408|408|global|castle|clash95.c|aCastle_pogD_15|kCastlePogDw12Gfx|medium|pog dw_12 gfx path for castle rendering.|
|409|409|global|castle|clash95.c|aCastle_chrD_16|kCastleChrDw12Base|medium|non-.gfx castle chr dw_12 resource path.|
|410|410|global|castle|clash95.c|aCastle_pogD_16|kCastlePogDw12Base|medium|non-.gfx castle pog dw_12 resource path.|
|411|411|global|castle|clash95.c|aCastle_chrD_23|kCastleChrDw13Gfx|medium|chr dw_13 gfx resource for castle screens.|
|412|412|global|castle|clash95.c|aCastle_pogD_23|kCastlePogDw13Gfx|medium|pog dw_13 gfx resource for castle screens.|
|413|413|global|castle|clash95.c|aCastle_chrD_17|kCastleChrDw13GfxAlt|medium|alternate chr dw_13 gfx path reused elsewhere.|
|414|414|global|castle|clash95.c|aCastle_pogD_17|kCastlePogDw13GfxAlt|medium|alternate pog dw_13 gfx path reused elsewhere.|
|415|415|global|castle|clash95.c|aCastle_chrD_19|kCastleChrDw13Base|medium|non-.gfx base file for chr dw_13 asset.|
|416|416|global|castle|clash95.c|aCastle_pogD_19|kCastlePogDw13Base|medium|base path for pog dw_13 asset.|
|417|417|global|castle|clash95.c|aCastle_chrDw_3|kCastleChrDw20GfxA|medium|one of several chr dw_20 gfx resources.|
|418|418|global|castle|clash95.c|aCastle_pogDw_3|kCastlePogDw20GfxA|medium|corresponding pog dw_20 gfx resource.|
|419|419|global|castle|clash95.c|aCastle_chrDw_5|kCastleChrDw20BaseA|medium|base file for chr dw_20 asset variant A.|
|420|420|global|castle|clash95.c|aCastle_pogDw_5|kCastlePogDw20BaseA|medium|base file for pog dw_20 asset variant A.|
|421|421|global|castle|clash95.c|aCastle_chrDw_6|kCastleChrDw20GfxB|medium|chr dw_20 gfx variant B.|
|422|422|global|castle|clash95.c|aCastle_pogDw_6|kCastlePogDw20GfxB|medium|pog dw_20 gfx variant B.|
|423|423|global|castle|clash95.c|aCastle_chrDw_8|kCastleChrDw20BaseB|medium|base file for chr dw_20 variant B.|
|424|424|global|castle|clash95.c|aCastle_pogDw_8|kCastlePogDw20BaseB|medium|base file for pog dw_20 variant B.|
|425|425|global|castle|clash95.c|aCastle_chrDw_9|kCastleChrDw20GfxC|medium|chr dw_20 gfx variant C.|
|426|426|global|castle|clash95.c|aCastle_pogDw_9|kCastlePogDw20GfxC|medium|pog dw_20 gfx variant C.|
|427|427|global|castle|clash95.c|aCastle_chrD_11|kCastleChrDw20BaseC|medium|base resource for chr dw_20 variant C.|
|428|428|global|castle|clash95.c|aCastle_pogD_11|kCastlePogDw20BaseC|medium|base resource for pog dw_20 variant C.|
|429|429|global|castle|clash95.c|aCastle_chrD_12|kCastleChrDw20GfxD|medium|chr dw_20 gfx variant D.|
|430|430|global|castle|clash95.c|aCastle_pogD_12|kCastlePogDw20GfxD|medium|pog dw_20 gfx variant D.|
|431|431|global|castle|clash95.c|aCastle_chrD_14|kCastleChrDw20BaseD|medium|base resource for chr dw_20 variant D.|
|432|432|global|castle|clash95.c|aCastle_pogD_14|kCastlePogDw20BaseD|medium|base resource for pog dw_20 variant D.|

## Batch 33 - Battle subsystem strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|433|433|global|unit|clash95.c|aAttackanimDD|kFmtBattleAttackAnim|high|Format string for AttackAnim calls.|
|434|434|global|unit|clash95.c|aDeathanimD|kFmtBattleDeathAnim|high|Format string for DeathAnim logging.|
|435|435|global|unit|clash95.c|a_shotanimDDDDD|kFmtBattleShotAnim|high|Format string for ranged ShotAnim invocations.|
|436|436|global|unit|clash95.c|aLoaded|kLogBattleAssetsLoaded|high|Diagnostic log showing battle assets loaded.|
|437|437|global|unit|clash95.c|aBattleMurek|kBattleWallResource|high|Resource path for battle wall graphics.|
|438|438|global|unit|clash95.c|aBattle_newturn|kLogBattleNewTurn|high|Log label used when Battle_NewTurn runs.|
|439|439|global|unit|clash95.c|aBattleSzarza|kBattleChargeResource|high|Resource path for battle charge graphic set.|
|440|440|global|unit|clash95.c|aHandlebattlere|kFmtHandleBattleResults|high|Format string for HandleBattleResults arguments.|
|441|441|global|unit|clash95.c|aHandlebattle_0|kLogHandleBattleResults|high|Text announcing battle result handling.|
|442|442|global|unit|clash95.c|aBattle_0|kLogBattleStartBanner|high|Shouting banner text printed at battle start.|
|443|443|global|unit|clash95.c|aNewBattle_0|kLogBattleNewBattleBanner|high|Banner text for a newly detected battle.|
|444|444|global|unit|clash95.c|aBattle_1|kFolderBattle|high|Base folder name for battle resources.|
|445|445|global|unit|clash95.c|aBattle_logallu|kCommandBattleLogAllUnits|high|Console command name to dump all battle units.|
|446|446|global|unit|clash95.c|aGodanger|kFuncNameGodAnger|high|Function label for GodAnger scripting hook.|
|447|447|global|unit|clash95.c|aBattle_placeun|kFmtBattlePlaceUnit|high|Format string for Battle_PlaceUnit.|

## Batch 34 - Battle map/log strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|448|448|global|unit|clash95.c|aBattle_log|kFileBattleLog|high|Path to the primary battle log file.|
|449|449|global|unit|clash95.c|aBattle_log_0|kFileBattleLogAlt|high|Alternate reference to battle.log used elsewhere.|
|450|450|global|unit|clash95.c|aBattle|kBattleFolderSimple|high|Generic "battle" folder name used for resources.|
|451|451|global|unit|clash95.c|aBattlemapfilen|kFmtBattleMapFileName|high|Format string for BattleMapFileName inputs.|
|452|452|global|unit|clash95.c|aBattlemapfil_0|kLogBattleMapFileNameResult|high|Message logging the path returned by BattleMapFileName.|

## Batch 35 - Road logging
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|453|453|global|tile|clash95.c|aRoad_buildDD|kFmtRoadBuild|high|Format string logging Road_Build commands.|

## Batch 36 - Trap dialogs
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|454|454|global|tile|clash95.c|Trap_HurtUnit|kFmtTrapHurtUnit|medium|Format string for trap damage events.|
|455|455|global|tile|clash95.c|aWpad_pul|kTrapEventNamePolish|medium|Polish label for falling into the trap event.|
|456|456|global|tile|clash95.c|aThisIsAPitfall|kDialogPitfallEnglish|medium|English dialog shown when discovering a pitfall.|
|457|457|global|tile|clash95.c|aDoYouWantToCov|kDialogPitfallPromptEnglish|medium|English prompt asking to cover the pitfall.|
|458|458|global|tile|clash95.c|aDasIstDieWolfs|kDialogPitfallGerman|medium|German dialog shown for the pitfall event.|
|459|459|global|tile|clash95.c|aWillstDuSieZus|kDialogPitfallPromptGerman|medium|German prompt asking whether to cover the pitfall.|

## Batch 37 - Polish battle commands
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|460|460|global|unit|clash95.c|aCofnij_oddzial|kCmdRetreatUnitFmt|medium|Format string for the Polish "cofnij oddzial" command.|
|461|461|global|unit|clash95.c|aRuch_oddzialem|kCmdMoveShooterFmt|medium|Format string for moving a ranged unit while firing.|
|462|462|global|unit|clash95.c|aOddzial_w_zasi|kCmdUnitInRangeFmt|medium|Format describing the "unit in range" command parameters.|
|463|463|global|unit|clash95.c|aPodejdz_na_bez|kCmdApproachSafeDistanceFmt|medium|Format for approaching to a safe distance command.|

## Batch 38 - Main map resource strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|464|464|global|tile|clash95.c|aMainmap_3|kMainmapResourceAlt4|medium|Alternate mainmap resource identifier used when loading assets.|
|465|465|global|tile|clash95.c|aMainmap_2|kMainmapResourceAlt3|medium|Alternate mainmap resource identifier used elsewhere.|
|466|466|global|tile|clash95.c|aMainmap_1|kMainmapResourceAlt2|medium|Alternate mainmap resource identifier used for map loads.|
|467|467|global|tile|clash95.c|aMainmap_0|kMainmapResourceAlt1|medium|Alternate mainmap resource identifier used for different stage.|
|468|468|global|tile|clash95.c|aMainmap|kMainmapResource|medium|Primary string referencing the mainmap resource.|
|469|469|global|tile|clash95.c|aMap_pal_1|kMapPaletteFileAlt|medium|Secondary map palette filename string.|
|470|470|global|tile|clash95.c|aMap_pal_0|kMapPaletteFile|medium|Base map palette filename string.|

## Batch 39 - Player name labels
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|471|471|global|unit|clash95.c|aDoc|kDefaultPlayerNameDoc|medium|Default player name string "Doc" used during profile creation.|
|472|472|global|unit|clash95.c|aSirArthur|kDefaultPlayerNameSirArthur|medium|Default player name "Sir Arthur".|
|473|473|global|unit|clash95.c|aLester|kDefaultPlayerNameLester|medium|Default player name "Lester".|
|474|474|global|unit|clash95.c|aComputer|kDefaultPlayerNameComputer|medium|Default player name "Computer".|
|475|475|global|unit|clash95.c|aTomek|kDefaultPlayerNameTomek|medium|Default player name "Tomek".|
|476|476|global|unit|clash95.c|aSirArthur_0|kAIPlayerNameSirArthur|medium|Alternate "Sir Arthur" label used for AI.|
|477|477|global|unit|clash95.c|aLester_0|kAIPlayerNameLester|medium|Alternate "Lester" label used for AI.|
|478|478|global|unit|clash95.c|aComputer_0|kAIPlayerNameComputer|medium|Alternate "Computer" label used for AI.|
|479|479|global|unit|clash95.c|aTomek_0|kAIPlayerNameTomek|medium|Alternate "Tomek" label used for AI.|

## Batch 40 - Polish action labels
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|480|480|global|unit|clash95.c|aZniszcze|kActionLabelDestroy|medium|Polish label used for the destroy action string.

## Batch 41 - Strategy/stat assets
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|481|481|global|unit|clash95.c|aStat_gfx|kStatGfxResource|medium|GFX resource for the statistics panel.|
|482|482|global|unit|clash95.c|aStat|kStatResourceFolder|medium|Folder name referenced when loading stats assets.|
|483|483|global|unit|clash95.c|aTeam1_gfx|kTeam1GfxResource|medium|Resource file for team1 graphics.|
|484|484|global|unit|clash95.c|aHeheNoBonus|kLogNoBonusReward|medium|Humorous log when no bonus is granted.|
|485|485|global|unit|clash95.c|aStrategClash_d|kStrategicDataFile|medium|Path to the strategic data file clash.dat.|
|486|486|global|unit|clash95.c|aMkinstArmyS|kFmtMakeInstanceArmy|medium|Format for make-instance army logging.|

## Batch 42 - Map resource strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|487|487|global|tile|clash95.c|aDataMaps_res|kMapsResourceFile|medium|Path to the packed map resources file.|
|488|488|global|tile|clash95.c|aMaps_1|kMapsFolderAlt|medium|Alternate string literal for the maps folder with slash.|
|489|489|global|tile|clash95.c|aMaps_0|kMapsFolderName|medium|Maps folder name without trailing slash.|
|490|490|global|tile|clash95.c|aMaps|kMapsFolderWithSlash|medium|Maps folder path used when building file names.|
|491|491|global|tile|clash95.c|aEndOfBattle|kLogEndOfBattle|medium|Banner text logged when battles end.|

## Batch 43 - Construction resources
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|492|492|global|castle|clash95.c|aBudowaSzkola|kConstructionSchoolGfx|medium|Resource path for school construction graphics.|
|493|493|global|castle|clash95.c|aBudowaWarszt_0|kConstructionWorkshopGfx|medium|Resource path for workshop construction graphics.|
|494|494|global|castle|clash95.c|aBudowaBaraki|kConstructionBarracksGfx|medium|Resource path for barracks construction graphics.|
|495|495|global|castle|clash95.c|aBudowaChrzesci|kConstructionChristianGfx|medium|Resource path for Christian temple construction.|
|496|496|global|castle|clash95.c|aBudowaPoganie|kConstructionPaganGfx|medium|Resource path for pagan temple construction.|
|497|497|global|castle|clash95.c|aBudowaKuznia|kConstructionForgeGfx|medium|Resource path for forge construction graphics.|

## Batch 44 - Player profile functions
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|498|498|function|other|clash95.c|sub_44AD60|PlayerProfile_Reset|medium|Function initializes a player profile block with default values and the name "Doc".
|499|499|function|other|clash95.c|sub_44AE10|PlayerProfile_ResetByIndex|medium|Wrapper that resets a player profile by index via PlayerProfile_Reset.

## Batch 45 - Squad SFX paths
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|500|500|global|unit|clash95.c|aSfxOddzialy|kSfxSquadsPath|medium|Base path for squad sound effects.|
|501|501|global|unit|clash95.c|aSfxOddzialy_0|kSfxSquadsPath0|medium|Duplicate path string for squad sound effects.|
|502|502|global|unit|clash95.c|aSfxOddzialy_1|kSfxSquadsPath1|medium|Duplicate path string for squad sound effects.|
|503|503|global|unit|clash95.c|aSfxOddzialy_2|kSfxSquadsPath2|medium|Duplicate path string for squad sound effects.|
|504|504|global|unit|clash95.c|aSfxOddzialy_3|kSfxSquadsPath3|medium|Duplicate path string for squad sound effects.|
|505|505|global|unit|clash95.c|aSfxOddzialy_4|kSfxSquadsPath4|medium|Duplicate path string for squad sound effects.|
|506|506|global|unit|clash95.c|aSfxOddzialy_5|kSfxSquadsPath5|medium|Duplicate path string for squad sound effects.|

## Batch 46 - SFX directories
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|507|507|global|unit|clash95.c|aSfxMusic|kSfxMusicDir|medium|Music sound effect directory path.|
|508|508|global|unit|clash95.c|aSfxMusic_0|kSfxMusicDirAlt|medium|Alternate reference to the music SFX directory.|
|509|509|global|unit|clash95.c|aSfxMisinfo|kSfxMisinfoDir|medium|Directory for mission info sound effects.|
|510|510|global|unit|clash95.c|aSfxMisinfoC_02|kSfxMisinfoWavePattern|medium|Filename pattern for mission info sounds.|
|511|511|global|unit|clash95.c|aSfx_0|kSfxRootDirAlt|medium|Secondary root SFX directory string.|
|512|512|global|unit|clash95.c|aSfx|kSfxRootDir|medium|Primary root SFX directory string.|
|513|513|global|unit|clash95.c|aSfxRuchy|kSfxMovementDir|medium|Movement SFX directory path.|
|514|514|global|unit|clash95.c|aSfxRuchy_0|kSfxMovementDir0|medium|Duplicate movement SFX directory string.|
|515|515|global|unit|clash95.c|aSfxRuchy_1|kSfxMovementDir1|medium|Duplicate movement SFX directory string.|
|516|516|global|unit|clash95.c|aSfxRuchy_2|kSfxMovementDir2|medium|Duplicate movement SFX directory string.|
|517|517|global|unit|clash95.c|aSfxButtons|kSfxButtonsDir|medium|Button click SFX directory path.|

## Batch 47 - Data resource archives
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|518|518|global|other|clash95.c|aDataMinimum_re|kResMinimum|high|Resource file name data\minimum.res.|
|519|519|global|other|clash95.c|aDataNormal_res|kResNormal|high|Resource file name data\normal.res.|
|520|520|global|other|clash95.c|aDataMaximum_re|kResMaximum|high|Resource file name data\maximum.res.|
|521|521|global|other|clash95.c|aDataGfx3_res|kResGfx3|high|Resource archive data\gfx3.res.|
|522|522|global|other|clash95.c|aDataInfopol_re|kResInfoPolish|high|Polish info archive data\infopol.res.|
|523|523|global|other|clash95.c|aDataInfoang_re|kResInfoEnglish|high|English info archive data\infoang.res.|
|524|524|global|other|clash95.c|aDataInfoger_re|kResInfoGerman|high|German info archive data\infoger.res.|
|525|525|global|other|clash95.c|aDataMisinfop_r|kResMissionInfoPolish|high|Polish mission info archive data\misinfop.res.|
|526|526|global|other|clash95.c|aDataMisinfoa_r|kResMissionInfoEnglish|high|English mission info archive data\misinfoa.res.|
|527|527|global|other|clash95.c|aDataMiswava_re|kResMissionWavePolish|high|Polish mission wave archive data\miswava.res.|
|528|528|global|other|clash95.c|aDataMisinfog_r|kResMissionInfoGerman|high|German mission info archive data\misinfog.res.|
|529|529|global|other|clash95.c|aDataMusic_res|kResMusic|high|Music archive data\music.res.|
|530|530|global|other|clash95.c|aDataLector_w_0|kResLectorWav|high|Spoken narration file data\lector.wav.|
|531|531|global|other|clash95.c|aDataLector_w_2|kResLectorWavAlt|high|Alternate string for data\lector.wav.|
|532|532|global|other|clash95.c|aData|kFolderData|high|Generic "data" folder literal.|

## Batch 48 - Misc temple/unit commands
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|533|533|global|castle|clash95.c|aKasuj_swiatyni|kFmtDestroyTemple|high|Format string for the Polish command "kasuj_swiatynie" to destroy a shrine.
|534|534|global|unit|clash95.c|aLogallunits|kCommandLogAllUnitsGlobal|high|String constant for invoking the LogAllUnits console command.

## Batch 49 - SetRH logging strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|535|535|global|other|clash95.c|aSetrhS08x|kFmtSetResourceHandle|medium|Log string for SetRH (set resource handle) tracing.|
|536|536|global|other|clash95.c|aSetrhS08x_0|kFmtSetResourceHandle0|medium|Log string for SetRH (set resource handle) tracing.|
|537|537|global|other|clash95.c|aSetrhS08x_1|kFmtSetResourceHandle1|medium|Log string for SetRH (set resource handle) tracing.|
|538|538|global|other|clash95.c|aSetrhS08x_2|kFmtSetResourceHandle2|medium|Log string for SetRH (set resource handle) tracing.|
|539|539|global|other|clash95.c|aSetrhS08x_3|kFmtSetResourceHandle3|medium|Log string for SetRH (set resource handle) tracing.|
|540|540|global|other|clash95.c|aSetrhS08x_4|kFmtSetResourceHandle4|medium|Log string for SetRH (set resource handle) tracing.|
|541|541|global|other|clash95.c|aSetrhS08x_5|kFmtSetResourceHandle5|medium|Log string for SetRH (set resource handle) tracing.|
|542|542|global|other|clash95.c|aSetrhS08x_6|kFmtSetResourceHandle6|medium|Log string for SetRH (set resource handle) tracing.|
|543|543|global|other|clash95.c|aSetrhS08x_7|kFmtSetResourceHandle7|medium|Log string for SetRH (set resource handle) tracing.|
|544|544|global|other|clash95.c|aSetrhS08x_8|kFmtSetResourceHandle8|medium|Log string for SetRH (set resource handle) tracing.|
|545|545|global|other|clash95.c|aSetrhS08x_9|kFmtSetResourceHandle9|medium|Log string for SetRH (set resource handle) tracing.|
|546|546|global|other|clash95.c|aSetrhS08x_10|kFmtSetResourceHandle10|medium|Log string for SetRH (set resource handle) tracing.|
|547|547|global|other|clash95.c|aSetrhS08x_11|kFmtSetResourceHandle11|medium|Log string for SetRH (set resource handle) tracing.|
|548|548|global|other|clash95.c|aSetrhS08x_12|kFmtSetResourceHandle12|medium|Log string for SetRH (set resource handle) tracing.|
|549|549|global|other|clash95.c|aSetrhS08x_13|kFmtSetResourceHandle13|medium|Log string for SetRH (set resource handle) tracing.|
|550|550|global|other|clash95.c|aSetrhS08x_14|kFmtSetResourceHandle14|medium|Log string for SetRH (set resource handle) tracing.|
|551|551|global|other|clash95.c|aSetrhS08x_15|kFmtSetResourceHandle15|medium|Log string for SetRH (set resource handle) tracing.|
|552|552|global|other|clash95.c|aSetrhS08x_16|kFmtSetResourceHandle16|medium|Log string for SetRH (set resource handle) tracing.|
|553|553|global|other|clash95.c|aSetrhS08x_17|kFmtSetResourceHandle17|medium|Log string for SetRH (set resource handle) tracing.|
|554|554|global|other|clash95.c|aSetrhS08x_18|kFmtSetResourceHandle18|medium|Log string for SetRH (set resource handle) tracing.|
|555|555|global|other|clash95.c|aSetrhS08x_19|kFmtSetResourceHandle19|medium|Log string for SetRH (set resource handle) tracing.|
|556|556|global|other|clash95.c|aSetrhS08x_20|kFmtSetResourceHandle20|medium|Log string for SetRH (set resource handle) tracing.|
|557|557|global|other|clash95.c|aSetrhS08x_21|kFmtSetResourceHandle21|medium|Log string for SetRH (set resource handle) tracing.|
|558|558|global|other|clash95.c|aSetrhS08x_22|kFmtSetResourceHandle22|medium|Log string for SetRH (set resource handle) tracing.|
|559|559|global|other|clash95.c|aSetrhS08x_23|kFmtSetResourceHandle23|medium|Log string for SetRH (set resource handle) tracing.|
|560|560|global|other|clash95.c|aSetrhS08x_24|kFmtSetResourceHandle24|medium|Log string for SetRH (set resource handle) tracing.|

## Batch 50 - UnsetRH logging strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|560|560|global|other|clash95.c|aUnsetrh08x|kFmtUnsetResourceHandle|medium|Log string for UnsetRH resource-handle operations.
|561|561|global|other|clash95.c|aUnsetrh08x_0|kFmtUnsetResourceHandle0|medium|Log string for UnsetRH resource-handle operations.
|562|562|global|other|clash95.c|aUnsetrh08x_1|kFmtUnsetResourceHandle1|medium|Log string for UnsetRH resource-handle operations.
|563|563|global|other|clash95.c|aUnsetrh08x_2|kFmtUnsetResourceHandle2|medium|Log string for UnsetRH resource-handle operations.
|564|564|global|other|clash95.c|aUnsetrh08x_3|kFmtUnsetResourceHandle3|medium|Log string for UnsetRH resource-handle operations.
|565|565|global|other|clash95.c|aUnsetrh08x_4|kFmtUnsetResourceHandle4|medium|Log string for UnsetRH resource-handle operations.
|566|566|global|other|clash95.c|aUnsetrh08x_5|kFmtUnsetResourceHandle5|medium|Log string for UnsetRH resource-handle operations.
|567|567|global|other|clash95.c|aUnsetrh08x_6|kFmtUnsetResourceHandle6|medium|Log string for UnsetRH resource-handle operations.
|568|568|global|other|clash95.c|aUnsetrh08x_7|kFmtUnsetResourceHandle7|medium|Log string for UnsetRH resource-handle operations.
|569|569|global|other|clash95.c|aUnsetrh08x_8|kFmtUnsetResourceHandle8|medium|Log string for UnsetRH resource-handle operations.
|570|570|global|other|clash95.c|aUnsetrh08x_9|kFmtUnsetResourceHandle9|medium|Log string for UnsetRH resource-handle operations.
|571|571|global|other|clash95.c|aUnsetrh08x_10|kFmtUnsetResourceHandle10|medium|Log string for UnsetRH resource-handle operations.
|572|572|global|other|clash95.c|aUnsetrh08x_11|kFmtUnsetResourceHandle11|medium|Log string for UnsetRH resource-handle operations.
|573|573|global|other|clash95.c|aUnsetrh08x_12|kFmtUnsetResourceHandle12|medium|Log string for UnsetRH resource-handle operations.
|574|574|global|other|clash95.c|aUnsetrh08x_13|kFmtUnsetResourceHandle13|medium|Log string for UnsetRH resource-handle operations.
|575|575|global|other|clash95.c|aUnsetrh08x_14|kFmtUnsetResourceHandle14|medium|Log string for UnsetRH resource-handle operations.
|576|576|global|other|clash95.c|aUnsetrh08x_15|kFmtUnsetResourceHandle15|medium|Log string for UnsetRH resource-handle operations.
|577|577|global|other|clash95.c|aUnsetrh08x_16|kFmtUnsetResourceHandle16|medium|Log string for UnsetRH resource-handle operations.
|578|578|global|other|clash95.c|aUnsetrh08x_17|kFmtUnsetResourceHandle17|medium|Log string for UnsetRH resource-handle operations.
|579|579|global|other|clash95.c|aUnsetrh08x_18|kFmtUnsetResourceHandle18|medium|Log string for UnsetRH resource-handle operations.
|580|580|global|other|clash95.c|aUnsetrh08x_19|kFmtUnsetResourceHandle19|medium|Log string for UnsetRH resource-handle operations.
|581|581|global|other|clash95.c|aUnsetrh08x_20|kFmtUnsetResourceHandle20|medium|Log string for UnsetRH resource-handle operations.
|582|582|global|other|clash95.c|aUnsetrh08x_21|kFmtUnsetResourceHandle21|medium|Log string for UnsetRH resource-handle operations.
|583|583|global|other|clash95.c|aUnsetrh08x_22|kFmtUnsetResourceHandle22|medium|Log string for UnsetRH resource-handle operations.
|584|584|global|other|clash95.c|aUnsetrh08x_23|kFmtUnsetResourceHandle23|medium|Log string for UnsetRH resource-handle operations.
|585|585|global|other|clash95.c|aUnsetrh08x_24|kFmtUnsetResourceHandle24|medium|Log string for UnsetRH resource-handle operations.

## Batch 51 - Rendering diagnostics
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|586|586|global|other|clash95.c|aSetbitmaptable|kFmtSetBitMapTable|medium|Log format used when SetBitMapTable is invoked.|
|587|587|global|other|clash95.c|aStructBitmapha|kFmtStructBitmapHashNode|medium|Format string used when emitting bitMapHashNode definitions.|
|588|588|global|other|clash95.c|aStructBitmap_0|kFmtStructBitmapPointerTable|medium|Format string for bitmap hash pointer tables.|
|589|589|global|other|clash95.c|aDderr_nomipmap|kTextDdErrNoMipMapHw|medium|Text describing the DirectDraw no mip-map hardware error.|

## Batch 52 - Low memory diagnostics
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|590|590|global|other|clash95.c|aNotEnoughMemor|kLogNotEnoughMemory|medium|Log message before aborting due to low memory.|
|591|591|global|other|clash95.c|aNotEnoughMem_0|kQuitNotEnoughMemory0|medium|Quit-string for low memory condition variant 0.|
|592|592|global|other|clash95.c|aNotEnoughFreeM|kLogNotEnoughFreeMemory|medium|English log stating there is no free memory.|
|593|593|global|other|clash95.c|aNotEnoughMem_1|kLogNotEnoughMemory1|medium|Second log label for insufficient memory.|
|594|594|global|other|clash95.c|aNotEnoughMem_2|kQuitNotEnoughMemory1|medium|Quit-string for insufficient memory variant 1.|
|595|595|global|other|clash95.c|aNotEnoughMem_7|kLogNotEnoughMemory7|medium|Additional log string for low memory (variant 7).|
|596|596|global|other|clash95.c|aNotEnoughMem_8|kQuitNotEnoughMemory7|medium|Quit-string for variant 7 low memory cases.|
|597|597|global|other|clash95.c|aNotEnoughMe_15|kLogNotEnoughMemory15|medium|Log string for low memory variant 15.|
|598|598|global|other|clash95.c|aNotEnoughMe_16|kQuitNotEnoughMemory15|medium|Quit-string for low memory variant 15.|
|599|599|global|other|clash95.c|aNotEnoughMem_3|kLogNotEnoughMemory3|medium|Log string for low memory variant 3.|
|600|600|global|other|clash95.c|aNotEnoughMem_4|kQuitNotEnoughMemory3|medium|Quit-string for low memory variant 3.|
|601|601|global|other|clash95.c|aNotEnoughMem_5|kLogNotEnoughMemory5|medium|Log string for low memory variant 5.|
|602|602|global|other|clash95.c|aNotEnoughMem_6|kQuitNotEnoughMemory5|medium|Quit-string for low memory variant 5.|
|603|603|global|other|clash95.c|aNotEnoughMem_9|kLogNotEnoughMemory9|medium|Log string for low memory variant 9.|
|604|604|global|other|clash95.c|aNotEnoughMe_10|kQuitNotEnoughMemory9|medium|Quit-string for low memory variant 9.|
|605|605|global|other|clash95.c|aNotEnoughMe_11|kLogNotEnoughMemory11|medium|Log string for low memory variant 11.|
|606|606|global|other|clash95.c|aNotEnoughMe_12|kQuitNotEnoughMemory11|medium|Quit-string for low memory variant 11.|
|607|607|global|other|clash95.c|aNotEnoughMe_13|kLogNotEnoughMemory13|medium|Log string for low memory variant 13.|
|608|608|global|other|clash95.c|aNotEnoughMe_14|kQuitNotEnoughMemory13|medium|Quit-string for low memory variant 13.|

## Batch 53 - Turn/banner strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|609|609|global|unit|clash95.c|aGraczSTwojaTur|kBannerPlayerTurnPl|medium|Polish turn banner text.|
|610|610|global|unit|clash95.c|aPlayerSYourTur|kBannerPlayerTurnEn|medium|English turn banner text.|
|611|611|global|unit|clash95.c|aSpielerS|kBannerPlayerTurnDe|medium|German turn banner text.|
|612|612|global|unit|clash95.c|aNextPlayer|kStatusNextPlayer|medium|String literal announcing the next player.|
|613|613|global|unit|clash95.c|aPlayerD|kFmtPlayerIndex|medium|Format string for player index logs.|
|614|614|global|unit|clash95.c|aNextTurnD|kFmtNextTurn|medium|Format string for next turn indicator.|
|615|615|global|unit|clash95.c|aClipsMemoryD|kFmtClipsMemory|medium|Format for reporting CLIPS memory usage.|
|616|616|global|unit|clash95.c|aUsedmemD_3|kFmtUsedMemory|medium|Format for reporting used memory.|
|617|617|global|unit|clash95.c|aAutoMovesBegin|kLogAutoMovesBegin|medium|Log markers for auto-move start.|
|618|618|global|unit|clash95.c|aAutoMovesEnd|kLogAutoMovesEnd|medium|Log markers for auto-move end.|
|619|619|global|unit|clash95.c|aKon_por1|kPortraitResourceKonPor1|medium|Portrait resource name kon_por1.|
|620|620|global|unit|clash95.c|aPlaygame|kLogPlayGame|medium|Log text for PlayGame routine.|
|621|621|global|unit|clash95.c|aStart|kLogPlayStart|medium|Log prefix for start events.|
|622|622|global|unit|clash95.c|aComputerplay|kLogComputerPlay|medium|Log text for ComputerPlay routine.|
|623|623|global|unit|clash95.c|aTuraD|kFmtTurnBanner|medium|Format string for displaying the current turn number.|

## Batch 54 - Menu resource strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|624|624|global|other|clash95.c|aMenuDraw|kLogMenuDraw|medium|Log text for menu draw operations.|
|625|625|global|other|clash95.c|aMenuHide|kLogMenuHide|medium|Log text for menu hide operations.|
|626|626|global|other|clash95.c|aMenuLoad_gfx|kMenuLoadGfx|medium|Path to the menu load graphics.|
|627|627|global|other|clash95.c|aMenuOpt_p_gfx|kMenuOptionsPGfx|medium|Options screen GFX resource (suffix _p).|
|628|628|global|other|clash95.c|aMenuOpt_a_gfx|kMenuOptionsAGfx|medium|Options screen GFX resource (suffix _a).|
|629|629|global|other|clash95.c|aMenuOpt_g_gfx|kMenuOptionsGGfx|medium|Options screen GFX resource (suffix _g).|
|630|630|global|other|clash95.c|aMusicMenu|kMusicMenuDir|medium|Directory containing menu music.|
|631|631|global|other|clash95.c|aMusicMenu_0|kMusicMenuDirAlt|medium|Alternate string for the menu music directory.|
|632|632|global|other|clash95.c|aMenuMain|kMenuMainDir|medium|Main menu resource folder.|
|633|633|global|other|clash95.c|aMenuMain_gfx|kMenuMainGfx|medium|Main menu graphics resource.|
|634|634|global|other|clash95.c|aMenuMain_gfx_0|kMenuMainGfxAlt|medium|Alternate main menu graphics resource.|
|635|635|global|other|clash95.c|aMenuMultipl_gf|kMenuMultiplayerGfx|medium|Multiplayer menu graphics resource.|
|636|636|global|other|clash95.c|aStartmenu|kMenuStartDir|medium|Start menu resource directory.|

## Batch 55 - Audio/menu logistics
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|637|637|global|other|clash95.c|aMusicCampain|kMusicCampaignDir|medium|Campaign music directory path.|
|638|638|global|other|clash95.c|aResumedSoundD|kLogSoundResumed|medium|Log text when a sound resumes.|
|639|639|global|other|clash95.c|aPausedSoundD|kLogSoundPaused|medium|Log text when a sound pauses.|
|640|640|global|other|clash95.c|aOptions_cfg|kOptionsConfigPath|medium|Options configuration file path string.|
|641|641|global|other|clash95.c|aOptions_cfg_0|kOptionsConfigPathAlt|medium|Alternate path string for options.cfg.|

## Batch 56 - File mode literals
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|642|642|global|other|clash95.c|aWb|kFileModeWriteBinary|medium|File open mode string "wb".|
|643|643|global|other|clash95.c|aWb_0|kFileModeWriteBinary0|medium|Duplicate "wb" file mode string.|
|644|644|global|other|clash95.c|aWb_1|kFileModeWriteBinary1|medium|Duplicate "wb" file mode string.|
|645|645|global|other|clash95.c|aWb_2|kFileModeWriteBinary2|medium|Duplicate "wb" file mode string.|
|646|646|global|other|clash95.c|aWb_3|kFileModeWriteBinary3|medium|Duplicate "wb" file mode string.|
|647|647|global|other|clash95.c|aWb_4|kFileModeWriteBinary4|medium|Duplicate "wb" file mode string.|
|648|648|global|other|clash95.c|aWb_5|kFileModeWriteBinary5|medium|Duplicate "wb" file mode string.|
|649|649|global|other|clash95.c|aWb_7|kFileModeWriteBinary7|medium|Duplicate "wb" file mode string.|
|650|650|global|other|clash95.c|aWb_8|kFileModeWriteBinary8|medium|Duplicate "wb" file mode string.|
|651|651|global|other|clash95.c|aRb|kFileModeReadBinary|medium|File open mode string "rb".|
|652|652|global|other|clash95.c|aRb_0|kFileModeReadBinary0|medium|Duplicate "rb" file mode string.|
|653|653|global|other|clash95.c|aRb_1|kFileModeReadBinary1|medium|Duplicate "rb" file mode string.|
|654|654|global|other|clash95.c|aRb_3|kFileModeReadBinary3|medium|Duplicate "rb" file mode string.|
|655|655|global|other|clash95.c|aRb_4|kFileModeReadBinary4|medium|Duplicate "rb" file mode string.|
|656|656|global|other|clash95.c|aRb_5|kFileModeReadBinary5|medium|Duplicate "rb" file mode string.|
|657|657|global|other|clash95.c|aRb_7|kFileModeReadBinary7|medium|Duplicate "rb" file mode string.|
|658|658|global|other|clash95.c|aRb_8|kFileModeReadBinary8|medium|Duplicate "rb" file mode string.|
|659|659|global|other|clash95.c|aRb_9|kFileModeReadBinary9|medium|Duplicate "rb" file mode string.|
|660|660|global|other|clash95.c|aRb_10|kFileModeReadBinary10|medium|Duplicate "rb" file mode string.|
|661|661|global|other|clash95.c|aRb_11|kFileModeReadBinary11|medium|Duplicate "rb" file mode string.|
|662|662|global|other|clash95.c|aAb|kFileModeAppendBinary|medium|File open mode string "ab".|
|663|663|global|other|clash95.c|aAb_0|kFileModeAppendBinary0|medium|Duplicate "ab" file mode string.|

## Batch 57 - Palette resource strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|664|664|global|other|clash95.c|aCas_list_pal|kCastleListPaletteFile|medium|Palette file for castle list UI.|
|665|665|global|other|clash95.c|aDderr_nopale_0|kDdErrNoPaletteHw|medium|DirectDraw error "DDERR_NOPALETTEHW" string.|
|666|666|global|other|clash95.c|aDderr_nopalett|kDdErrNoPaletteAttached|medium|DirectDraw error "DDERR_NOPALETTEATTACHED" string.|
|667|667|global|other|clash95.c|aDderr_notpalet|kDdErrNotPalettized|medium|DirectDraw error "DDERR_NOTPALETTIZED" string.|
|668|668|global|other|clash95.c|aDderr_paletteb|kDdErrPaletteBusy|medium|DirectDraw error "DDERR_PALETTEBUSY" string.|
|669|669|global|other|clash95.c|a_loadpalcolS0x|kFmtLoadPalCol|medium|Format string for _LoadPalCOL calls.|
|670|670|global|other|clash95.c|a_loadpalpcxS0x|kFmtLoadPalPcx|medium|Format string for _LoadPalPCX calls.|
|671|671|global|other|clash95.c|a_pal|kSuffixPalette|medium|String constant for the ".pal" extension.|

## Batch 58 - DirectDraw error strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|672|672|global|other|clash95.c|aDderr_alreadyi|kDdErrAlreadyinitialized|medium|DirectDraw error literal ALREADYINITIALIZED.|
|673|673|global|other|clash95.c|aDderr_cannotat|kDdErrCannotattachsurface|medium|DirectDraw error literal CANNOTATTACHSURFACE.|
|674|674|global|other|clash95.c|aDderr_cannotde|kDdErrCannotdetachsurface|medium|DirectDraw error literal CANNOTDETACHSURFACE.|
|675|675|global|other|clash95.c|aDderr_currentl|kDdErrCurrentlynotavail|medium|DirectDraw error literal CURRENTLYNOTAVAIL.|
|676|676|global|other|clash95.c|aDderr_exceptio|kDdErrException|medium|DirectDraw error literal EXCEPTION.|
|677|677|global|other|clash95.c|aDderr_generic|kDdErrGeneric|medium|DirectDraw error literal GENERIC.|
|678|678|global|other|clash95.c|aDderr_heightal|kDdErrHeightalign|medium|DirectDraw error literal HEIGHTALIGN.|
|679|679|global|other|clash95.c|aDderr_incompat|kDdErrIncompatibleprimary|medium|DirectDraw error literal INCOMPATIBLEPRIMARY.|
|680|680|global|other|clash95.c|aDderr_invalidc|kDdErrInvalidcaps|medium|DirectDraw error literal INVALIDCAPS.|
|681|681|global|other|clash95.c|aDderr_invali_0|kDdErrInvalidcliplist|medium|DirectDraw error literal INVALIDCLIPLIST.|
|682|682|global|other|clash95.c|aDderr_invalidm|kDdErrInvalidmode|medium|DirectDraw error literal INVALIDMODE.|
|683|683|global|other|clash95.c|aDderr_invalido|kDdErrInvalidobject|medium|DirectDraw error literal INVALIDOBJECT.|
|684|684|global|other|clash95.c|aDderr_invali_2|kDdErrInvalidparams|medium|DirectDraw error literal INVALIDPARAMS.|
|685|685|global|other|clash95.c|aDderr_invali_1|kDdErrInvalidpixelformat|medium|DirectDraw error literal INVALIDPIXELFORMAT.|
|686|686|global|other|clash95.c|aDderr_invalidr|kDdErrInvalidrect|medium|DirectDraw error literal INVALIDRECT.|
|687|687|global|other|clash95.c|aDderr_lockedsu|kDdErrLockedsurfaces|medium|DirectDraw error literal LOCKEDSURFACES.|
|688|688|global|other|clash95.c|aDderr_no3d|kDdErrNo3d|medium|DirectDraw error literal NO3D.|
|689|689|global|other|clash95.c|aDderr_noalphah|kDdErrNoalphahw|medium|DirectDraw error literal NOALPHAHW.|
|690|690|global|other|clash95.c|aDderr_noclipli|kDdErrNocliplist|medium|DirectDraw error literal NOCLIPLIST.|
|691|691|global|other|clash95.c|aDderr_nocolorc|kDdErrNocolorconvhw|medium|DirectDraw error literal NOCOLORCONVHW.|
|692|692|global|other|clash95.c|aDderr_nocooper|kDdErrNocooperativelevelset|medium|DirectDraw error literal NOCOOPERATIVELEVELSET.|
|693|693|global|other|clash95.c|aDderr_nocolork|kDdErrNocolorkey|medium|DirectDraw error literal NOCOLORKEY.|
|694|694|global|other|clash95.c|aDderr_nocolo_0|kDdErrNocolorkeyhw|medium|DirectDraw error literal NOCOLORKEYHW.|
|695|695|global|other|clash95.c|aDderr_nodire_0|kDdErrNodirectdrawsupport|medium|DirectDraw error literal NODIRECTDRAWSUPPORT.|
|696|696|global|other|clash95.c|aDderr_noexclus|kDdErrNoexclusivemode|medium|DirectDraw error literal NOEXCLUSIVEMODE.|
|697|697|global|other|clash95.c|aDderr_nofliphw|kDdErrNofliphw|medium|DirectDraw error literal NOFLIPHW.|
|698|698|global|other|clash95.c|aDderr_nogdi|kDdErrNogdi|medium|DirectDraw error literal NOGDI.|
|699|699|global|other|clash95.c|aDderr_nomirror|kDdErrNomirrorhw|medium|DirectDraw error literal NOMIRRORHW.|
|700|700|global|other|clash95.c|aDderr_notfound|kDdErrNotfound|medium|DirectDraw error literal NOTFOUND.|
|701|701|global|other|clash95.c|aDderr_noover_0|kDdErrNooverlayhw|medium|DirectDraw error literal NOOVERLAYHW.|
|702|702|global|other|clash95.c|aDderr_noraster|kDdErrNorasterophw|medium|DirectDraw error literal NORASTEROPHW.|
|703|703|global|other|clash95.c|aDderr_norotati|kDdErrNorotationhw|medium|DirectDraw error literal NOROTATIONHW.|
|704|704|global|other|clash95.c|aDderr_nostretc|kDdErrNostretchhw|medium|DirectDraw error literal NOSTRETCHHW.|
|705|705|global|other|clash95.c|aDderr_not4bitc|kDdErrNot4bitcolor|medium|DirectDraw error literal NOT4BITCOLOR.|
|706|706|global|other|clash95.c|aDderr_not4bi_0|kDdErrNot4bitcolorindex|medium|DirectDraw error literal NOT4BITCOLORINDEX.|
|707|707|global|other|clash95.c|aDderr_not8bitc|kDdErrNot8bitcolor|medium|DirectDraw error literal NOT8BITCOLOR.|
|708|708|global|other|clash95.c|aDderr_notextur|kDdErrNotexturehw|medium|DirectDraw error literal NOTEXTUREHW.|
|709|709|global|other|clash95.c|aDderr_novsynch|kDdErrNovsynchw|medium|DirectDraw error literal NOVSYNCHW.|
|710|710|global|other|clash95.c|aDderr_nozbuffe|kDdErrNozbufferhw|medium|DirectDraw error literal NOZBUFFERHW.|
|711|711|global|other|clash95.c|aDderr_nozoverl|kDdErrNozoverlayhw|medium|DirectDraw error literal NOZOVERLAYHW.|
|712|712|global|other|clash95.c|aDderr_outofcap|kDdErrOutofcaps|medium|DirectDraw error literal OUTOFCAPS.|
|713|713|global|other|clash95.c|aDderr_outofmem|kDdErrOutofmemory|medium|DirectDraw error literal OUTOFMEMORY.|
|714|714|global|other|clash95.c|aDderr_outofvid|kDdErrOutofvideomemory|medium|DirectDraw error literal OUTOFVIDEOMEMORY.|
|715|715|global|other|clash95.c|aDderr_overlayc|kDdErrOverlaycantclip|medium|DirectDraw error literal OVERLAYCANTCLIP.|
|716|716|global|other|clash95.c|aDderr_overla_0|kDdErrOverlaycolorkeyonlyoneactive|medium|DirectDraw error literal OVERLAYCOLORKEYONLYONEACTIVE.|
|717|717|global|other|clash95.c|aDderr_paletteb|kDdErrPalettebusy|medium|DirectDraw error literal PALETTEBUSY.|
|718|718|global|other|clash95.c|aDderr_colorkey|kDdErrColorkeynotset|medium|DirectDraw error literal COLORKEYNOTSET.|
|719|719|global|other|clash95.c|aDderr_surfacea|kDdErrSurfacealreadyattached|medium|DirectDraw error literal SURFACEALREADYATTACHED.|
|720|720|global|other|clash95.c|aDderr_surfac_0|kDdErrSurfacealreadydependent|medium|DirectDraw error literal SURFACEALREADYDEPENDENT.|
|721|721|global|other|clash95.c|aDderr_surfaceb|kDdErrSurfacebusy|medium|DirectDraw error literal SURFACEBUSY.|
|722|722|global|other|clash95.c|aDderr_cantlock|kDdErrCantlocksurface|medium|DirectDraw error literal CANTLOCKSURFACE.|
|723|723|global|other|clash95.c|aDderr_surfacei|kDdErrSurfaceisobscured|medium|DirectDraw error literal SURFACEISOBSCURED.|
|724|724|global|other|clash95.c|aDderr_surfacel|kDdErrSurfacelost|medium|DirectDraw error literal SURFACELOST.|
|725|725|global|other|clash95.c|aDderr_surfacen|kDdErrSurfacenotattached|medium|DirectDraw error literal SURFACENOTATTACHED.|
|726|726|global|other|clash95.c|aDderr_toobighe|kDdErrToobigheight|medium|DirectDraw error literal TOOBIGHEIGHT.|
|727|727|global|other|clash95.c|aDderr_toobigsi|kDdErrToobigsize|medium|DirectDraw error literal TOOBIGSIZE.|
|728|728|global|other|clash95.c|aDderr_toobigwi|kDdErrToobigwidth|medium|DirectDraw error literal TOOBIGWIDTH.|
|729|729|global|other|clash95.c|aDderr_unsuppor|kDdErrUnsupported|medium|DirectDraw error literal UNSUPPORTED.|
|730|730|global|other|clash95.c|aDderr_unsupp_1|kDdErrUnsupportedformat|medium|DirectDraw error literal UNSUPPORTEDFORMAT.|
|731|731|global|other|clash95.c|aDderr_unsupp_2|kDdErrUnsupportedmask|medium|DirectDraw error literal UNSUPPORTEDMASK.|
|732|732|global|other|clash95.c|aDderr_vertical|kDdErrVerticalblankinprogress|medium|DirectDraw error literal VERTICALBLANKINPROGRESS.|
|733|733|global|other|clash95.c|aDderr_wasstill|kDdErrWasstilldrawing|medium|DirectDraw error literal WASSTILLDRAWING.|
|734|734|global|other|clash95.c|aDderr_xalign|kDdErrXalign|medium|DirectDraw error literal XALIGN.|
|735|735|global|other|clash95.c|aDderr_invalidd|kDdErrInvaliddirectdrawguid|medium|DirectDraw error literal INVALIDDIRECTDRAWGUID.|
|736|736|global|other|clash95.c|aDderr_directdr|kDdErrDirectdrawalreadycreated|medium|DirectDraw error literal DIRECTDRAWALREADYCREATED.|
|737|737|global|other|clash95.c|aDderr_nodirect|kDdErrNodirectdrawhw|medium|DirectDraw error literal NODIRECTDRAWHW.|
|738|738|global|other|clash95.c|aDderr_primarys|kDdErrPrimarysurfacealreadyexists|medium|DirectDraw error literal PRIMARYSURFACEALREADYEXISTS.|
|739|739|global|other|clash95.c|aDderr_noemulat|kDdErrNoemulation|medium|DirectDraw error literal NOEMULATION.|
|740|740|global|other|clash95.c|aDderr_regionto|kDdErrRegiontoosmall|medium|DirectDraw error literal REGIONTOOSMALL.|
|741|741|global|other|clash95.c|aDderr_clipperi|kDdErrClipperisusinghwnd|medium|DirectDraw error literal CLIPPERISUSINGHWND.|
|742|742|global|other|clash95.c|aDderr_noclippe|kDdErrNoclipperattached|medium|DirectDraw error literal NOCLIPPERATTACHED.|
|743|743|global|other|clash95.c|aDderr_nohwnd|kDdErrNohwnd|medium|DirectDraw error literal NOHWND.|
|744|744|global|other|clash95.c|aDderr_hwndsubc|kDdErrHwndsubclassed|medium|DirectDraw error literal HWNDSUBCLASSED.|
|745|745|global|other|clash95.c|aDderr_hwndalre|kDdErrHwndalreadyset|medium|DirectDraw error literal HWNDALREADYSET.|
|746|746|global|other|clash95.c|aDderr_nopalett|kDdErrNopaletteattached|medium|DirectDraw error literal NOPALETTEATTACHED.|
|747|747|global|other|clash95.c|aDderr_nopale_0|kDdErrNopalettehw|medium|DirectDraw error literal NOPALETTEHW.|
|748|748|global|other|clash95.c|aDderr_bltfastc|kDdErrBltfastcantclip|medium|DirectDraw error literal BLTFASTCANTCLIP.|
|749|749|global|other|clash95.c|aDderr_noblthw|kDdErrNoblthw|medium|DirectDraw error literal NOBLTHW.|
|750|750|global|other|clash95.c|aDderr_noddrops|kDdErrNoddropshw|medium|DirectDraw error literal NODDROPSHW.|
|751|751|global|other|clash95.c|aDderr_overlayn|kDdErrOverlaynotvisible|medium|DirectDraw error literal OVERLAYNOTVISIBLE.|
|752|752|global|other|clash95.c|aDderr_nooverla|kDdErrNooverlaydest|medium|DirectDraw error literal NOOVERLAYDEST.|
|753|753|global|other|clash95.c|aDderr_invalidp|kDdErrInvalidposition|medium|DirectDraw error literal INVALIDPOSITION.|
|754|754|global|other|clash95.c|aDderr_notaover|kDdErrNotaoverlaysurface|medium|DirectDraw error literal NOTAOVERLAYSURFACE.|
|755|755|global|other|clash95.c|aDderr_exclusiv|kDdErrExclusivemodealreadyset|medium|DirectDraw error literal EXCLUSIVEMODEALREADYSET.|
|756|756|global|other|clash95.c|aDderr_notflipp|kDdErrNotflippable|medium|DirectDraw error literal NOTFLIPPABLE.|
|757|757|global|other|clash95.c|aDderr_cantdupl|kDdErrCantduplicate|medium|DirectDraw error literal CANTDUPLICATE.|
|758|758|global|other|clash95.c|aDderr_notlocke|kDdErrNotlocked|medium|DirectDraw error literal NOTLOCKED.|
|759|759|global|other|clash95.c|aDderr_cantcrea|kDdErrCantcreatedc|medium|DirectDraw error literal CANTCREATEDC.|
|760|760|global|other|clash95.c|aDderr_nodc|kDdErrNodc|medium|DirectDraw error literal NODC.|
|761|761|global|other|clash95.c|aDderr_wrongmod|kDdErrWrongmode|medium|DirectDraw error literal WRONGMODE.|
|762|762|global|other|clash95.c|aDderr_implicit|kDdErrImplicitlycreated|medium|DirectDraw error literal IMPLICITLYCREATED.|
|763|763|global|other|clash95.c|aDderr_notpalet|kDdErrNotpalettized|medium|DirectDraw error literal NOTPALETTIZED.|
|764|764|global|other|clash95.c|aDderr_unsupp_0|kDdErrUnsupportedmode|medium|DirectDraw error literal UNSUPPORTEDMODE.|
|765|765|global|other|clash95.c|aDderr_nomipmap|kDdErrNomipmaphw|medium|DirectDraw error literal NOMIPMAPHW.|
|766|766|global|other|clash95.c|aDderr_invalids|kDdErrInvalidsurfacetype|medium|DirectDraw error literal INVALIDSURFACETYPE.|
|767|767|global|other|clash95.c|aDderr_dcalread|kDdErrDcalreadycreated|medium|DirectDraw error literal DCALREADYCREATED.|
|768|768|global|other|clash95.c|aDderr_cantpage|kDdErrCantpagelock|medium|DirectDraw error literal CANTPAGELOCK.|
|769|769|global|other|clash95.c|aDderr_cantpa_0|kDdErrCantpageunlock|medium|DirectDraw error literal CANTPAGEUNLOCK.|
|770|770|global|other|clash95.c|aDderr_notpagel|kDdErrNotpagelocked|medium|DirectDraw error literal NOTPAGELOCKED.|
|771|771|global|other|clash95.c|aDderr_notiniti|kDdErrNotinitialized|medium|DirectDraw error literal NOTINITIALIZED.|

## Batch 59 - CLIPS function names
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|772|772|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|773|773|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|774|774|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|775|775|global|other|clash95.c|aUndeffunction|kClipsFuncUndef|medium|CLIPS function name literal for Undef.|
|776|776|global|other|clash95.c|aPpdeffunction|kClipsFuncPpdef|medium|CLIPS function name literal for Ppdef.|
|777|777|global|other|clash95.c|aPpdeffunction|kClipsFuncPpdef|medium|CLIPS function name literal for Ppdef.|
|778|778|global|other|clash95.c|aGetdeffunction|kClipsFuncGetdef|medium|CLIPS function name literal for Getdef.|
|779|779|global|other|clash95.c|aGetDeffunction|kClipsFuncGetDef|medium|CLIPS function name literal for GetDef.|
|780|780|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|781|781|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|782|782|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|783|783|global|other|clash95.c|aIffunction|kClipsFuncIf|medium|CLIPS function name literal for If.|
|784|784|global|other|clash95.c|aWhilefunction|kClipsFuncWhile|medium|CLIPS function name literal for While.|
|785|785|global|other|clash95.c|aBindfunction|kClipsFuncBind|medium|CLIPS function name literal for Bind.|
|786|786|global|other|clash95.c|aPrognfunction|kClipsFuncProgn|medium|CLIPS function name literal for Progn.|
|787|787|global|other|clash95.c|aReturnfunction|kClipsFuncReturn|medium|CLIPS function name literal for Return.|
|788|788|global|other|clash95.c|aBreakfunction|kClipsFuncBreak|medium|CLIPS function name literal for Break.|
|789|789|global|other|clash95.c|aSwitchfunction|kClipsFuncSwitch|medium|CLIPS function name literal for Switch.|
|790|790|global|other|clash95.c|aGensymfunction|kClipsFuncGensym|medium|CLIPS function name literal for Gensym.|
|791|791|global|other|clash95.c|aSetgenfunction|kClipsFuncSetgen|medium|CLIPS function name literal for Setgen.|
|792|792|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS function name literal for Length.|
|793|793|global|other|clash95.c|aRandomfunction|kClipsFuncRandom|medium|CLIPS function name literal for Random.|
|794|794|global|other|clash95.c|aSeedfunction|kClipsFuncSeed|medium|CLIPS function name literal for Seed.|
|795|795|global|other|clash95.c|aGetfunction|kClipsFuncGet|medium|CLIPS function name literal for Get.|
|796|796|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS function name literal for Create.|
|797|797|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|798|798|global|other|clash95.c|aReadfunction|kClipsFuncRead|medium|CLIPS function name literal for Read.|
|799|799|global|other|clash95.c|aOpenfunction|kClipsFuncOpen|medium|CLIPS function name literal for Open.|
|800|800|global|other|clash95.c|aClosefunction|kClipsFuncClose|medium|CLIPS function name literal for Close.|
|801|801|global|other|clash95.c|aRemovefunction|kClipsFuncRemove|medium|CLIPS function name literal for Remove.|
|802|802|global|other|clash95.c|aRenamefunction|kClipsFuncRename|medium|CLIPS function name literal for Rename.|
|803|803|global|other|clash95.c|aFormatfunction|kClipsFuncFormat|medium|CLIPS function name literal for Format.|
|804|804|global|other|clash95.c|aNotfunction|kClipsFuncNot|medium|CLIPS function name literal for Not.|
|805|805|global|other|clash95.c|aAndfunction|kClipsFuncAnd|medium|CLIPS function name literal for And.|
|806|806|global|other|clash95.c|aOrfunction|kClipsFuncOr|medium|CLIPS function name literal for Or.|
|807|807|global|other|clash95.c|aEqfunction|kClipsFuncEq|medium|CLIPS function name literal for Eq.|
|808|808|global|other|clash95.c|aNeqfunction|kClipsFuncNeq|medium|CLIPS function name literal for Neq.|
|809|809|global|other|clash95.c|aFloatpfunction|kClipsFuncFloatp|medium|CLIPS function name literal for Floatp.|
|810|810|global|other|clash95.c|aOddpfunction|kClipsFuncOddp|medium|CLIPS function name literal for Oddp.|
|811|811|global|other|clash95.c|aEvenpfunction|kClipsFuncEvenp|medium|CLIPS function name literal for Evenp.|
|812|812|global|other|clash95.c|aDivfunction|kClipsFuncDiv|medium|CLIPS function name literal for Div.|
|813|813|global|other|clash95.c|aFloatfunction|kClipsFuncFloat|medium|CLIPS function name literal for Float.|
|814|814|global|other|clash95.c|aAbsfunction|kClipsFuncAbs|medium|CLIPS function name literal for Abs.|
|815|815|global|other|clash95.c|aMinfunction|kClipsFuncMin|medium|CLIPS function name literal for Min.|
|816|816|global|other|clash95.c|aMaxfunction|kClipsFuncMax|medium|CLIPS function name literal for Max.|
|817|817|global|other|clash95.c|aFirstfunction|kClipsFuncFirst|medium|CLIPS function name literal for First.|
|818|818|global|other|clash95.c|aRestfunction|kClipsFuncRest|medium|CLIPS function name literal for Rest.|
|819|819|global|other|clash95.c|aSubseqfunction|kClipsFuncSubseq|medium|CLIPS function name literal for Subseq.|
|820|820|global|other|clash95.c|aDeletefunction|kClipsFuncDelete|medium|CLIPS function name literal for Delete.|
|821|821|global|other|clash95.c|aInsertfunction|kClipsFuncInsert|medium|CLIPS function name literal for Insert.|
|822|822|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS function name literal for Nth.|
|823|823|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS function name literal for Member.|
|824|824|global|other|clash95.c|aStrcatfunction|kClipsFuncStrcat|medium|CLIPS function name literal for Strcat.|
|825|825|global|other|clash95.c|aSymcatfunction|kClipsFuncSymcat|medium|CLIPS function name literal for Symcat.|
|826|826|global|other|clash95.c|aUpcasefunction|kClipsFuncUpcase|medium|CLIPS function name literal for Upcase.|
|827|827|global|other|clash95.c|aEvalfunction|kClipsFuncEval|medium|CLIPS function name literal for Eval.|
|828|828|global|other|clash95.c|aBuildfunction|kClipsFuncBuild|medium|CLIPS function name literal for Build.|
|829|829|global|other|clash95.c|aCosfunction|kClipsFuncCos|medium|CLIPS function name literal for Cos.|
|830|830|global|other|clash95.c|aSinfunction|kClipsFuncSin|medium|CLIPS function name literal for Sin.|
|831|831|global|other|clash95.c|aTanfunction|kClipsFuncTan|medium|CLIPS function name literal for Tan.|
|832|832|global|other|clash95.c|aSecfunction|kClipsFuncSec|medium|CLIPS function name literal for Sec.|
|833|833|global|other|clash95.c|aCscfunction|kClipsFuncCsc|medium|CLIPS function name literal for Csc.|
|834|834|global|other|clash95.c|aCotfunction|kClipsFuncCot|medium|CLIPS function name literal for Cot.|
|835|835|global|other|clash95.c|aAcosfunction|kClipsFuncAcos|medium|CLIPS function name literal for Acos.|
|836|836|global|other|clash95.c|aAsinfunction|kClipsFuncAsin|medium|CLIPS function name literal for Asin.|
|837|837|global|other|clash95.c|aAtanfunction|kClipsFuncAtan|medium|CLIPS function name literal for Atan.|
|838|838|global|other|clash95.c|aAsecfunction|kClipsFuncAsec|medium|CLIPS function name literal for Asec.|
|839|839|global|other|clash95.c|aAcscfunction|kClipsFuncAcsc|medium|CLIPS function name literal for Acsc.|
|840|840|global|other|clash95.c|aAcotfunction|kClipsFuncAcot|medium|CLIPS function name literal for Acot.|
|841|841|global|other|clash95.c|aCoshfunction|kClipsFuncCosh|medium|CLIPS function name literal for Cosh.|
|842|842|global|other|clash95.c|aSinhfunction|kClipsFuncSinh|medium|CLIPS function name literal for Sinh.|
|843|843|global|other|clash95.c|aTanhfunction|kClipsFuncTanh|medium|CLIPS function name literal for Tanh.|
|844|844|global|other|clash95.c|aSechfunction|kClipsFuncSech|medium|CLIPS function name literal for Sech.|
|845|845|global|other|clash95.c|aCschfunction|kClipsFuncCsch|medium|CLIPS function name literal for Csch.|
|846|846|global|other|clash95.c|aCothfunction|kClipsFuncCoth|medium|CLIPS function name literal for Coth.|
|847|847|global|other|clash95.c|aAcoshfunction|kClipsFuncAcosh|medium|CLIPS function name literal for Acosh.|
|848|848|global|other|clash95.c|aAsinhfunction|kClipsFuncAsinh|medium|CLIPS function name literal for Asinh.|
|849|849|global|other|clash95.c|aAtanhfunction|kClipsFuncAtanh|medium|CLIPS function name literal for Atanh.|
|850|850|global|other|clash95.c|aAsechfunction|kClipsFuncAsech|medium|CLIPS function name literal for Asech.|
|851|851|global|other|clash95.c|aAcschfunction|kClipsFuncAcsch|medium|CLIPS function name literal for Acsch.|
|852|852|global|other|clash95.c|aAcothfunction|kClipsFuncAcoth|medium|CLIPS function name literal for Acoth.|
|853|853|global|other|clash95.c|aModfunction|kClipsFuncMod|medium|CLIPS function name literal for Mod.|
|854|854|global|other|clash95.c|aExpfunction|kClipsFuncExp|medium|CLIPS function name literal for Exp.|
|855|855|global|other|clash95.c|aLogfunction|kClipsFuncLog|medium|CLIPS function name literal for Log.|
|856|856|global|other|clash95.c|aLog10function|kClipsFuncLog10|medium|CLIPS function name literal for Log10.|
|857|857|global|other|clash95.c|aSqrtfunction|kClipsFuncSqrt|medium|CLIPS function name literal for Sqrt.|
|858|858|global|other|clash95.c|aPifunction|kClipsFuncPi|medium|CLIPS function name literal for Pi.|
|859|859|global|other|clash95.c|aDegradfunction|kClipsFuncDegrad|medium|CLIPS function name literal for Degrad.|
|860|860|global|other|clash95.c|aRaddegfunction|kClipsFuncRaddeg|medium|CLIPS function name literal for Raddeg.|
|861|861|global|other|clash95.c|aPowfunction|kClipsFuncPow|medium|CLIPS function name literal for Pow.|
|862|862|global|other|clash95.c|aRoundfunction|kClipsFuncRound|medium|CLIPS function name literal for Round.|
|863|863|global|other|clash95.c|aHelpfunction|kClipsFuncHelp|medium|CLIPS function name literal for Help.|
|864|864|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|865|865|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|866|866|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|867|867|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|868|868|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|869|869|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|870|870|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|871|871|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|872|872|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|873|873|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|874|874|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|875|875|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|876|876|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|877|877|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|878|878|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|879|879|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|880|880|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|881|881|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|882|882|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|883|883|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|884|884|global|other|clash95.c|aUndeffunction|kClipsFuncUndef|medium|CLIPS function name literal for Undef.|
|885|885|global|other|clash95.c|aPpdeffunction|kClipsFuncPpdef|medium|CLIPS function name literal for Ppdef.|
|886|886|global|other|clash95.c|aPpdeffunction|kClipsFuncPpdef|medium|CLIPS function name literal for Ppdef.|
|887|887|global|other|clash95.c|aGetDeffunction|kClipsFuncGetDef|medium|CLIPS function name literal for GetDef.|
|888|888|global|other|clash95.c|aGetdeffunction|kClipsFuncGetdef|medium|CLIPS function name literal for Getdef.|
|889|889|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|890|890|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|891|891|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|892|892|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|893|893|global|other|clash95.c|aIffunction|kClipsFuncIf|medium|CLIPS function name literal for If.|
|894|894|global|other|clash95.c|aWhilefunction|kClipsFuncWhile|medium|CLIPS function name literal for While.|
|895|895|global|other|clash95.c|aBindfunction|kClipsFuncBind|medium|CLIPS function name literal for Bind.|
|896|896|global|other|clash95.c|aPrognfunction|kClipsFuncProgn|medium|CLIPS function name literal for Progn.|
|897|897|global|other|clash95.c|aReturnfunction|kClipsFuncReturn|medium|CLIPS function name literal for Return.|
|898|898|global|other|clash95.c|aBreakfunction|kClipsFuncBreak|medium|CLIPS function name literal for Break.|
|899|899|global|other|clash95.c|aSwitchfunction|kClipsFuncSwitch|medium|CLIPS function name literal for Switch.|
|900|900|global|other|clash95.c|aGensymfunction|kClipsFuncGensym|medium|CLIPS function name literal for Gensym.|
|901|901|global|other|clash95.c|aSetgenfunction|kClipsFuncSetgen|medium|CLIPS function name literal for Setgen.|
|902|902|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS function name literal for Length.|
|903|903|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS function name literal for Length.|
|904|904|global|other|clash95.c|aRandomfunction|kClipsFuncRandom|medium|CLIPS function name literal for Random.|
|905|905|global|other|clash95.c|aSeedfunction|kClipsFuncSeed|medium|CLIPS function name literal for Seed.|
|906|906|global|other|clash95.c|aGetfunction|kClipsFuncGet|medium|CLIPS function name literal for Get.|
|907|907|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS function name literal for Create.|
|908|908|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS function name literal for Create.|
|909|909|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|910|910|global|other|clash95.c|aReadfunction|kClipsFuncRead|medium|CLIPS function name literal for Read.|
|911|911|global|other|clash95.c|aOpenfunction|kClipsFuncOpen|medium|CLIPS function name literal for Open.|
|912|912|global|other|clash95.c|aClosefunction|kClipsFuncClose|medium|CLIPS function name literal for Close.|
|913|913|global|other|clash95.c|aRemovefunction|kClipsFuncRemove|medium|CLIPS function name literal for Remove.|
|914|914|global|other|clash95.c|aRenamefunction|kClipsFuncRename|medium|CLIPS function name literal for Rename.|
|915|915|global|other|clash95.c|aFormatfunction|kClipsFuncFormat|medium|CLIPS function name literal for Format.|
|916|916|global|other|clash95.c|aNotfunction|kClipsFuncNot|medium|CLIPS function name literal for Not.|
|917|917|global|other|clash95.c|aAndfunction|kClipsFuncAnd|medium|CLIPS function name literal for And.|
|918|918|global|other|clash95.c|aOrfunction|kClipsFuncOr|medium|CLIPS function name literal for Or.|
|919|919|global|other|clash95.c|aEqfunction|kClipsFuncEq|medium|CLIPS function name literal for Eq.|
|920|920|global|other|clash95.c|aNeqfunction|kClipsFuncNeq|medium|CLIPS function name literal for Neq.|
|921|921|global|other|clash95.c|aFloatpfunction|kClipsFuncFloatp|medium|CLIPS function name literal for Floatp.|
|922|922|global|other|clash95.c|aOddpfunction|kClipsFuncOddp|medium|CLIPS function name literal for Oddp.|
|923|923|global|other|clash95.c|aEvenpfunction|kClipsFuncEvenp|medium|CLIPS function name literal for Evenp.|
|924|924|global|other|clash95.c|aDivfunction|kClipsFuncDiv|medium|CLIPS function name literal for Div.|
|925|925|global|other|clash95.c|aFloatfunction|kClipsFuncFloat|medium|CLIPS function name literal for Float.|
|926|926|global|other|clash95.c|aAbsfunction|kClipsFuncAbs|medium|CLIPS function name literal for Abs.|
|927|927|global|other|clash95.c|aMinfunction|kClipsFuncMin|medium|CLIPS function name literal for Min.|
|928|928|global|other|clash95.c|aMaxfunction|kClipsFuncMax|medium|CLIPS function name literal for Max.|
|929|929|global|other|clash95.c|aFirstfunction|kClipsFuncFirst|medium|CLIPS function name literal for First.|
|930|930|global|other|clash95.c|aRestfunction|kClipsFuncRest|medium|CLIPS function name literal for Rest.|
|931|931|global|other|clash95.c|aSubseqfunction|kClipsFuncSubseq|medium|CLIPS function name literal for Subseq.|
|932|932|global|other|clash95.c|aDeletefunction|kClipsFuncDelete|medium|CLIPS function name literal for Delete.|
|933|933|global|other|clash95.c|aInsertfunction|kClipsFuncInsert|medium|CLIPS function name literal for Insert.|
|934|934|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS function name literal for Nth.|
|935|935|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS function name literal for Member.|
|936|936|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS function name literal for Nth.|
|937|937|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS function name literal for Member.|
|938|938|global|other|clash95.c|aStrcatfunction|kClipsFuncStrcat|medium|CLIPS function name literal for Strcat.|
|939|939|global|other|clash95.c|aSymcatfunction|kClipsFuncSymcat|medium|CLIPS function name literal for Symcat.|
|940|940|global|other|clash95.c|aUpcasefunction|kClipsFuncUpcase|medium|CLIPS function name literal for Upcase.|
|941|941|global|other|clash95.c|aEvalfunction|kClipsFuncEval|medium|CLIPS function name literal for Eval.|
|942|942|global|other|clash95.c|aBuildfunction|kClipsFuncBuild|medium|CLIPS function name literal for Build.|
|943|943|global|other|clash95.c|aCosfunction|kClipsFuncCos|medium|CLIPS function name literal for Cos.|
|944|944|global|other|clash95.c|aSinfunction|kClipsFuncSin|medium|CLIPS function name literal for Sin.|
|945|945|global|other|clash95.c|aTanfunction|kClipsFuncTan|medium|CLIPS function name literal for Tan.|
|946|946|global|other|clash95.c|aSecfunction|kClipsFuncSec|medium|CLIPS function name literal for Sec.|
|947|947|global|other|clash95.c|aCscfunction|kClipsFuncCsc|medium|CLIPS function name literal for Csc.|
|948|948|global|other|clash95.c|aCotfunction|kClipsFuncCot|medium|CLIPS function name literal for Cot.|
|949|949|global|other|clash95.c|aAcosfunction|kClipsFuncAcos|medium|CLIPS function name literal for Acos.|
|950|950|global|other|clash95.c|aAsinfunction|kClipsFuncAsin|medium|CLIPS function name literal for Asin.|
|951|951|global|other|clash95.c|aAtanfunction|kClipsFuncAtan|medium|CLIPS function name literal for Atan.|
|952|952|global|other|clash95.c|aAsecfunction|kClipsFuncAsec|medium|CLIPS function name literal for Asec.|
|953|953|global|other|clash95.c|aAcscfunction|kClipsFuncAcsc|medium|CLIPS function name literal for Acsc.|
|954|954|global|other|clash95.c|aAcotfunction|kClipsFuncAcot|medium|CLIPS function name literal for Acot.|
|955|955|global|other|clash95.c|aCoshfunction|kClipsFuncCosh|medium|CLIPS function name literal for Cosh.|
|956|956|global|other|clash95.c|aSinhfunction|kClipsFuncSinh|medium|CLIPS function name literal for Sinh.|
|957|957|global|other|clash95.c|aTanhfunction|kClipsFuncTanh|medium|CLIPS function name literal for Tanh.|
|958|958|global|other|clash95.c|aSechfunction|kClipsFuncSech|medium|CLIPS function name literal for Sech.|
|959|959|global|other|clash95.c|aCschfunction|kClipsFuncCsch|medium|CLIPS function name literal for Csch.|
|960|960|global|other|clash95.c|aCothfunction|kClipsFuncCoth|medium|CLIPS function name literal for Coth.|
|961|961|global|other|clash95.c|aAcoshfunction|kClipsFuncAcosh|medium|CLIPS function name literal for Acosh.|
|962|962|global|other|clash95.c|aAsinhfunction|kClipsFuncAsinh|medium|CLIPS function name literal for Asinh.|
|963|963|global|other|clash95.c|aAtanhfunction|kClipsFuncAtanh|medium|CLIPS function name literal for Atanh.|
|964|964|global|other|clash95.c|aAsechfunction|kClipsFuncAsech|medium|CLIPS function name literal for Asech.|
|965|965|global|other|clash95.c|aAcschfunction|kClipsFuncAcsch|medium|CLIPS function name literal for Acsch.|
|966|966|global|other|clash95.c|aAcothfunction|kClipsFuncAcoth|medium|CLIPS function name literal for Acoth.|
|967|967|global|other|clash95.c|aModfunction|kClipsFuncMod|medium|CLIPS function name literal for Mod.|
|968|968|global|other|clash95.c|aExpfunction|kClipsFuncExp|medium|CLIPS function name literal for Exp.|
|969|969|global|other|clash95.c|aLogfunction|kClipsFuncLog|medium|CLIPS function name literal for Log.|
|970|970|global|other|clash95.c|aLog10function|kClipsFuncLog10|medium|CLIPS function name literal for Log10.|
|971|971|global|other|clash95.c|aSqrtfunction|kClipsFuncSqrt|medium|CLIPS function name literal for Sqrt.|
|972|972|global|other|clash95.c|aPifunction|kClipsFuncPi|medium|CLIPS function name literal for Pi.|
|973|973|global|other|clash95.c|aDegradfunction|kClipsFuncDegrad|medium|CLIPS function name literal for Degrad.|
|974|974|global|other|clash95.c|aRaddegfunction|kClipsFuncRaddeg|medium|CLIPS function name literal for Raddeg.|
|975|975|global|other|clash95.c|aPowfunction|kClipsFuncPow|medium|CLIPS function name literal for Pow.|
|976|976|global|other|clash95.c|aRoundfunction|kClipsFuncRound|medium|CLIPS function name literal for Round.|
|977|977|global|other|clash95.c|aHelpfunction|kClipsFuncHelp|medium|CLIPS function name literal for Help.|
|978|978|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|979|979|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|980|980|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|981|981|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|982|982|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|983|983|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|984|984|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|985|985|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|986|986|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|987|987|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|988|988|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|989|989|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|990|990|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|991|991|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|
|992|992|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS function name literal for Def.|

## Batch 59 - CLIPS function names
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|772|772|global|other|clash95.c|aUndeffunction|kClipsFuncUndef|medium|CLIPS function literal for Undef.|
|773|773|global|other|clash95.c|aGetdeffunction|kClipsFuncGetdef|medium|CLIPS function literal for Getdef.|
|774|774|global|other|clash95.c|aGetDeffunction|kClipsFuncGetDef|medium|CLIPS function literal for GetDef.|
|775|775|global|other|clash95.c|aIffunction|kClipsFuncIf|medium|CLIPS function literal for If.|
|776|776|global|other|clash95.c|aWhilefunction|kClipsFuncWhile|medium|CLIPS function literal for While.|
|777|777|global|other|clash95.c|aBindfunction|kClipsFuncBind|medium|CLIPS function literal for Bind.|
|778|778|global|other|clash95.c|aPrognfunction|kClipsFuncProgn|medium|CLIPS function literal for Progn.|
|779|779|global|other|clash95.c|aReturnfunction|kClipsFuncReturn|medium|CLIPS function literal for Return.|
|780|780|global|other|clash95.c|aBreakfunction|kClipsFuncBreak|medium|CLIPS function literal for Break.|
|781|781|global|other|clash95.c|aSwitchfunction|kClipsFuncSwitch|medium|CLIPS function literal for Switch.|
|782|782|global|other|clash95.c|aGensymfunction|kClipsFuncGensym|medium|CLIPS function literal for Gensym.|
|783|783|global|other|clash95.c|aSetgenfunction|kClipsFuncSetgen|medium|CLIPS function literal for Setgen.|
|784|784|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS function literal for Length.|
|785|785|global|other|clash95.c|aRandomfunction|kClipsFuncRandom|medium|CLIPS function literal for Random.|
|786|786|global|other|clash95.c|aSeedfunction|kClipsFuncSeed|medium|CLIPS function literal for Seed.|
|787|787|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS function literal for Create.|
|788|788|global|other|clash95.c|aReadfunction|kClipsFuncRead|medium|CLIPS function literal for Read.|
|789|789|global|other|clash95.c|aOpenfunction|kClipsFuncOpen|medium|CLIPS function literal for Open.|
|790|790|global|other|clash95.c|aClosefunction|kClipsFuncClose|medium|CLIPS function literal for Close.|
|791|791|global|other|clash95.c|aRemovefunction|kClipsFuncRemove|medium|CLIPS function literal for Remove.|
|792|792|global|other|clash95.c|aRenamefunction|kClipsFuncRename|medium|CLIPS function literal for Rename.|
|793|793|global|other|clash95.c|aFormatfunction|kClipsFuncFormat|medium|CLIPS function literal for Format.|
|794|794|global|other|clash95.c|aNotfunction|kClipsFuncNot|medium|CLIPS function literal for Not.|
|795|795|global|other|clash95.c|aAndfunction|kClipsFuncAnd|medium|CLIPS function literal for And.|
|796|796|global|other|clash95.c|aOrfunction|kClipsFuncOr|medium|CLIPS function literal for Or.|
|797|797|global|other|clash95.c|aEqfunction|kClipsFuncEq|medium|CLIPS function literal for Eq.|
|798|798|global|other|clash95.c|aNeqfunction|kClipsFuncNeq|medium|CLIPS function literal for Neq.|
|799|799|global|other|clash95.c|aFloatpfunction|kClipsFuncFloatp|medium|CLIPS function literal for Floatp.|
|800|800|global|other|clash95.c|aOddpfunction|kClipsFuncOddp|medium|CLIPS function literal for Oddp.|
|801|801|global|other|clash95.c|aEvenpfunction|kClipsFuncEvenp|medium|CLIPS function literal for Evenp.|
|802|802|global|other|clash95.c|aDivfunction|kClipsFuncDiv|medium|CLIPS function literal for Div.|
|803|803|global|other|clash95.c|aFloatfunction|kClipsFuncFloat|medium|CLIPS function literal for Float.|
|804|804|global|other|clash95.c|aAbsfunction|kClipsFuncAbs|medium|CLIPS function literal for Abs.|
|805|805|global|other|clash95.c|aMinfunction|kClipsFuncMin|medium|CLIPS function literal for Min.|
|806|806|global|other|clash95.c|aMaxfunction|kClipsFuncMax|medium|CLIPS function literal for Max.|
|807|807|global|other|clash95.c|aFirstfunction|kClipsFuncFirst|medium|CLIPS function literal for First.|
|808|808|global|other|clash95.c|aRestfunction|kClipsFuncRest|medium|CLIPS function literal for Rest.|
|809|809|global|other|clash95.c|aSubseqfunction|kClipsFuncSubseq|medium|CLIPS function literal for Subseq.|
|810|810|global|other|clash95.c|aDeletefunction|kClipsFuncDelete|medium|CLIPS function literal for Delete.|
|811|811|global|other|clash95.c|aInsertfunction|kClipsFuncInsert|medium|CLIPS function literal for Insert.|
|812|812|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS function literal for Nth.|
|813|813|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS function literal for Member.|
|814|814|global|other|clash95.c|aStrcatfunction|kClipsFuncStrcat|medium|CLIPS function literal for Strcat.|
|815|815|global|other|clash95.c|aSymcatfunction|kClipsFuncSymcat|medium|CLIPS function literal for Symcat.|
|816|816|global|other|clash95.c|aUpcasefunction|kClipsFuncUpcase|medium|CLIPS function literal for Upcase.|
|817|817|global|other|clash95.c|aEvalfunction|kClipsFuncEval|medium|CLIPS function literal for Eval.|
|818|818|global|other|clash95.c|aBuildfunction|kClipsFuncBuild|medium|CLIPS function literal for Build.|
|819|819|global|other|clash95.c|aCosfunction|kClipsFuncCos|medium|CLIPS function literal for Cos.|
|820|820|global|other|clash95.c|aSinfunction|kClipsFuncSin|medium|CLIPS function literal for Sin.|
|821|821|global|other|clash95.c|aTanfunction|kClipsFuncTan|medium|CLIPS function literal for Tan.|
|822|822|global|other|clash95.c|aSecfunction|kClipsFuncSec|medium|CLIPS function literal for Sec.|
|823|823|global|other|clash95.c|aCscfunction|kClipsFuncCsc|medium|CLIPS function literal for Csc.|
|824|824|global|other|clash95.c|aCotfunction|kClipsFuncCot|medium|CLIPS function literal for Cot.|
|825|825|global|other|clash95.c|aAcosfunction|kClipsFuncAcos|medium|CLIPS function literal for Acos.|
|826|826|global|other|clash95.c|aAsinfunction|kClipsFuncAsin|medium|CLIPS function literal for Asin.|
|827|827|global|other|clash95.c|aAtanfunction|kClipsFuncAtan|medium|CLIPS function literal for Atan.|
|828|828|global|other|clash95.c|aAsecfunction|kClipsFuncAsec|medium|CLIPS function literal for Asec.|
|829|829|global|other|clash95.c|aAcscfunction|kClipsFuncAcsc|medium|CLIPS function literal for Acsc.|
|830|830|global|other|clash95.c|aAcotfunction|kClipsFuncAcot|medium|CLIPS function literal for Acot.|
|831|831|global|other|clash95.c|aCoshfunction|kClipsFuncCosh|medium|CLIPS function literal for Cosh.|
|832|832|global|other|clash95.c|aSinhfunction|kClipsFuncSinh|medium|CLIPS function literal for Sinh.|
|833|833|global|other|clash95.c|aTanhfunction|kClipsFuncTanh|medium|CLIPS function literal for Tanh.|
|834|834|global|other|clash95.c|aSechfunction|kClipsFuncSech|medium|CLIPS function literal for Sech.|
|835|835|global|other|clash95.c|aCschfunction|kClipsFuncCsch|medium|CLIPS function literal for Csch.|
|836|836|global|other|clash95.c|aCothfunction|kClipsFuncCoth|medium|CLIPS function literal for Coth.|
|837|837|global|other|clash95.c|aAcoshfunction|kClipsFuncAcosh|medium|CLIPS function literal for Acosh.|
|838|838|global|other|clash95.c|aAsinhfunction|kClipsFuncAsinh|medium|CLIPS function literal for Asinh.|
|839|839|global|other|clash95.c|aAtanhfunction|kClipsFuncAtanh|medium|CLIPS function literal for Atanh.|
|840|840|global|other|clash95.c|aAsechfunction|kClipsFuncAsech|medium|CLIPS function literal for Asech.|
|841|841|global|other|clash95.c|aAcschfunction|kClipsFuncAcsch|medium|CLIPS function literal for Acsch.|
|842|842|global|other|clash95.c|aAcothfunction|kClipsFuncAcoth|medium|CLIPS function literal for Acoth.|
|843|843|global|other|clash95.c|aModfunction|kClipsFuncMod|medium|CLIPS function literal for Mod.|
|844|844|global|other|clash95.c|aExpfunction|kClipsFuncExp|medium|CLIPS function literal for Exp.|
|845|845|global|other|clash95.c|aLogfunction|kClipsFuncLog|medium|CLIPS function literal for Log.|
|846|846|global|other|clash95.c|aLog10function|kClipsFuncLog10|medium|CLIPS function literal for Log10.|
|847|847|global|other|clash95.c|aSqrtfunction|kClipsFuncSqrt|medium|CLIPS function literal for Sqrt.|
|848|848|global|other|clash95.c|aPifunction|kClipsFuncPi|medium|CLIPS function literal for Pi.|
|849|849|global|other|clash95.c|aDegradfunction|kClipsFuncDegrad|medium|CLIPS function literal for Degrad.|
|850|850|global|other|clash95.c|aRaddegfunction|kClipsFuncRaddeg|medium|CLIPS function literal for Raddeg.|
|851|851|global|other|clash95.c|aPowfunction|kClipsFuncPow|medium|CLIPS function literal for Pow.|
|852|852|global|other|clash95.c|aRoundfunction|kClipsFuncRound|medium|CLIPS function literal for Round.|
|853|853|global|other|clash95.c|aHelpfunction|kClipsFuncHelp|medium|CLIPS function literal for Help.|
|854|854|global|other|clash95.c|aUndeffunction|kClipsFuncUndef|medium|CLIPS function literal for Undef.|
|855|855|global|other|clash95.c|aGetDeffunction|kClipsFuncGetDef|medium|CLIPS function literal for GetDef.|
|856|856|global|other|clash95.c|aGetdeffunction|kClipsFuncGetdef|medium|CLIPS function literal for Getdef.|
|857|857|global|other|clash95.c|aIffunction|kClipsFuncIf|medium|CLIPS function literal for If.|
|858|858|global|other|clash95.c|aWhilefunction|kClipsFuncWhile|medium|CLIPS function literal for While.|
|859|859|global|other|clash95.c|aBindfunction|kClipsFuncBind|medium|CLIPS function literal for Bind.|
|860|860|global|other|clash95.c|aPrognfunction|kClipsFuncProgn|medium|CLIPS function literal for Progn.|
|861|861|global|other|clash95.c|aReturnfunction|kClipsFuncReturn|medium|CLIPS function literal for Return.|
|862|862|global|other|clash95.c|aBreakfunction|kClipsFuncBreak|medium|CLIPS function literal for Break.|
|863|863|global|other|clash95.c|aSwitchfunction|kClipsFuncSwitch|medium|CLIPS function literal for Switch.|
|864|864|global|other|clash95.c|aGensymfunction|kClipsFuncGensym|medium|CLIPS function literal for Gensym.|
|865|865|global|other|clash95.c|aSetgenfunction|kClipsFuncSetgen|medium|CLIPS function literal for Setgen.|
|866|866|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS function literal for Length.|
|867|867|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS function literal for Length.|
|868|868|global|other|clash95.c|aRandomfunction|kClipsFuncRandom|medium|CLIPS function literal for Random.|
|869|869|global|other|clash95.c|aSeedfunction|kClipsFuncSeed|medium|CLIPS function literal for Seed.|
|870|870|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS function literal for Create.|
|871|871|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS function literal for Create.|
|872|872|global|other|clash95.c|aReadfunction|kClipsFuncRead|medium|CLIPS function literal for Read.|
|873|873|global|other|clash95.c|aOpenfunction|kClipsFuncOpen|medium|CLIPS function literal for Open.|
|874|874|global|other|clash95.c|aClosefunction|kClipsFuncClose|medium|CLIPS function literal for Close.|
|875|875|global|other|clash95.c|aRemovefunction|kClipsFuncRemove|medium|CLIPS function literal for Remove.|
|876|876|global|other|clash95.c|aRenamefunction|kClipsFuncRename|medium|CLIPS function literal for Rename.|
|877|877|global|other|clash95.c|aFormatfunction|kClipsFuncFormat|medium|CLIPS function literal for Format.|
|878|878|global|other|clash95.c|aNotfunction|kClipsFuncNot|medium|CLIPS function literal for Not.|
|879|879|global|other|clash95.c|aAndfunction|kClipsFuncAnd|medium|CLIPS function literal for And.|
|880|880|global|other|clash95.c|aOrfunction|kClipsFuncOr|medium|CLIPS function literal for Or.|
|881|881|global|other|clash95.c|aEqfunction|kClipsFuncEq|medium|CLIPS function literal for Eq.|
|882|882|global|other|clash95.c|aNeqfunction|kClipsFuncNeq|medium|CLIPS function literal for Neq.|
|883|883|global|other|clash95.c|aFloatpfunction|kClipsFuncFloatp|medium|CLIPS function literal for Floatp.|
|884|884|global|other|clash95.c|aOddpfunction|kClipsFuncOddp|medium|CLIPS function literal for Oddp.|
|885|885|global|other|clash95.c|aEvenpfunction|kClipsFuncEvenp|medium|CLIPS function literal for Evenp.|
|886|886|global|other|clash95.c|aDivfunction|kClipsFuncDiv|medium|CLIPS function literal for Div.|
|887|887|global|other|clash95.c|aFloatfunction|kClipsFuncFloat|medium|CLIPS function literal for Float.|
|888|888|global|other|clash95.c|aAbsfunction|kClipsFuncAbs|medium|CLIPS function literal for Abs.|
|889|889|global|other|clash95.c|aMinfunction|kClipsFuncMin|medium|CLIPS function literal for Min.|
|890|890|global|other|clash95.c|aMaxfunction|kClipsFuncMax|medium|CLIPS function literal for Max.|
|891|891|global|other|clash95.c|aFirstfunction|kClipsFuncFirst|medium|CLIPS function literal for First.|
|892|892|global|other|clash95.c|aRestfunction|kClipsFuncRest|medium|CLIPS function literal for Rest.|
|893|893|global|other|clash95.c|aSubseqfunction|kClipsFuncSubseq|medium|CLIPS function literal for Subseq.|
|894|894|global|other|clash95.c|aDeletefunction|kClipsFuncDelete|medium|CLIPS function literal for Delete.|
|895|895|global|other|clash95.c|aInsertfunction|kClipsFuncInsert|medium|CLIPS function literal for Insert.|
|896|896|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS function literal for Nth.|
|897|897|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS function literal for Member.|
|898|898|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS function literal for Nth.|
|899|899|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS function literal for Member.|
|900|900|global|other|clash95.c|aStrcatfunction|kClipsFuncStrcat|medium|CLIPS function literal for Strcat.|
|901|901|global|other|clash95.c|aSymcatfunction|kClipsFuncSymcat|medium|CLIPS function literal for Symcat.|
|902|902|global|other|clash95.c|aUpcasefunction|kClipsFuncUpcase|medium|CLIPS function literal for Upcase.|
|903|903|global|other|clash95.c|aEvalfunction|kClipsFuncEval|medium|CLIPS function literal for Eval.|
|904|904|global|other|clash95.c|aBuildfunction|kClipsFuncBuild|medium|CLIPS function literal for Build.|
|905|905|global|other|clash95.c|aCosfunction|kClipsFuncCos|medium|CLIPS function literal for Cos.|
|906|906|global|other|clash95.c|aSinfunction|kClipsFuncSin|medium|CLIPS function literal for Sin.|
|907|907|global|other|clash95.c|aTanfunction|kClipsFuncTan|medium|CLIPS function literal for Tan.|
|908|908|global|other|clash95.c|aSecfunction|kClipsFuncSec|medium|CLIPS function literal for Sec.|
|909|909|global|other|clash95.c|aCscfunction|kClipsFuncCsc|medium|CLIPS function literal for Csc.|
|910|910|global|other|clash95.c|aCotfunction|kClipsFuncCot|medium|CLIPS function literal for Cot.|
|911|911|global|other|clash95.c|aAcosfunction|kClipsFuncAcos|medium|CLIPS function literal for Acos.|
|912|912|global|other|clash95.c|aAsinfunction|kClipsFuncAsin|medium|CLIPS function literal for Asin.|
|913|913|global|other|clash95.c|aAtanfunction|kClipsFuncAtan|medium|CLIPS function literal for Atan.|
|914|914|global|other|clash95.c|aAsecfunction|kClipsFuncAsec|medium|CLIPS function literal for Asec.|
|915|915|global|other|clash95.c|aAcscfunction|kClipsFuncAcsc|medium|CLIPS function literal for Acsc.|
|916|916|global|other|clash95.c|aAcotfunction|kClipsFuncAcot|medium|CLIPS function literal for Acot.|
|917|917|global|other|clash95.c|aCoshfunction|kClipsFuncCosh|medium|CLIPS function literal for Cosh.|
|918|918|global|other|clash95.c|aSinhfunction|kClipsFuncSinh|medium|CLIPS function literal for Sinh.|
|919|919|global|other|clash95.c|aTanhfunction|kClipsFuncTanh|medium|CLIPS function literal for Tanh.|
|920|920|global|other|clash95.c|aSechfunction|kClipsFuncSech|medium|CLIPS function literal for Sech.|
|921|921|global|other|clash95.c|aCschfunction|kClipsFuncCsch|medium|CLIPS function literal for Csch.|
|922|922|global|other|clash95.c|aCothfunction|kClipsFuncCoth|medium|CLIPS function literal for Coth.|
|923|923|global|other|clash95.c|aAcoshfunction|kClipsFuncAcosh|medium|CLIPS function literal for Acosh.|
|924|924|global|other|clash95.c|aAsinhfunction|kClipsFuncAsinh|medium|CLIPS function literal for Asinh.|
|925|925|global|other|clash95.c|aAtanhfunction|kClipsFuncAtanh|medium|CLIPS function literal for Atanh.|
|926|926|global|other|clash95.c|aAsechfunction|kClipsFuncAsech|medium|CLIPS function literal for Asech.|
|927|927|global|other|clash95.c|aAcschfunction|kClipsFuncAcsch|medium|CLIPS function literal for Acsch.|
|928|928|global|other|clash95.c|aAcothfunction|kClipsFuncAcoth|medium|CLIPS function literal for Acoth.|
|929|929|global|other|clash95.c|aModfunction|kClipsFuncMod|medium|CLIPS function literal for Mod.|
|930|930|global|other|clash95.c|aExpfunction|kClipsFuncExp|medium|CLIPS function literal for Exp.|
|931|931|global|other|clash95.c|aLogfunction|kClipsFuncLog|medium|CLIPS function literal for Log.|
|932|932|global|other|clash95.c|aLog10function|kClipsFuncLog10|medium|CLIPS function literal for Log10.|
|933|933|global|other|clash95.c|aSqrtfunction|kClipsFuncSqrt|medium|CLIPS function literal for Sqrt.|
|934|934|global|other|clash95.c|aPifunction|kClipsFuncPi|medium|CLIPS function literal for Pi.|
|935|935|global|other|clash95.c|aDegradfunction|kClipsFuncDegrad|medium|CLIPS function literal for Degrad.|
|936|936|global|other|clash95.c|aRaddegfunction|kClipsFuncRaddeg|medium|CLIPS function literal for Raddeg.|
|937|937|global|other|clash95.c|aPowfunction|kClipsFuncPow|medium|CLIPS function literal for Pow.|
|938|938|global|other|clash95.c|aRoundfunction|kClipsFuncRound|medium|CLIPS function literal for Round.|
|939|939|global|other|clash95.c|aHelpfunction|kClipsFuncHelp|medium|CLIPS function literal for Help.|

## Batch 59 - CLIPS function names
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|772|772|global|other|clash95.c|aAbsfunction|kClipsFuncAbs|medium|CLIPS builtin function literal for Abs.|
|773|773|global|other|clash95.c|aAcosfunction|kClipsFuncAcos|medium|CLIPS builtin function literal for Acos.|
|774|774|global|other|clash95.c|aAcoshfunction|kClipsFuncAcosh|medium|CLIPS builtin function literal for Acosh.|
|775|775|global|other|clash95.c|aAcotfunction|kClipsFuncAcot|medium|CLIPS builtin function literal for Acot.|
|776|776|global|other|clash95.c|aAcothfunction|kClipsFuncAcoth|medium|CLIPS builtin function literal for Acoth.|
|777|777|global|other|clash95.c|aAcscfunction|kClipsFuncAcsc|medium|CLIPS builtin function literal for Acsc.|
|778|778|global|other|clash95.c|aAcschfunction|kClipsFuncAcsch|medium|CLIPS builtin function literal for Acsch.|
|779|779|global|other|clash95.c|aAndfunction|kClipsFuncAnd|medium|CLIPS builtin function literal for And.|
|780|780|global|other|clash95.c|aAsecfunction|kClipsFuncAsec|medium|CLIPS builtin function literal for Asec.|
|781|781|global|other|clash95.c|aAsechfunction|kClipsFuncAsech|medium|CLIPS builtin function literal for Asech.|
|782|782|global|other|clash95.c|aAsinfunction|kClipsFuncAsin|medium|CLIPS builtin function literal for Asin.|
|783|783|global|other|clash95.c|aAsinhfunction|kClipsFuncAsinh|medium|CLIPS builtin function literal for Asinh.|
|784|784|global|other|clash95.c|aAtanfunction|kClipsFuncAtan|medium|CLIPS builtin function literal for Atan.|
|785|785|global|other|clash95.c|aAtanhfunction|kClipsFuncAtanh|medium|CLIPS builtin function literal for Atanh.|
|786|786|global|other|clash95.c|aBindfunction|kClipsFuncBind|medium|CLIPS builtin function literal for Bind.|
|787|787|global|other|clash95.c|aBreakfunction|kClipsFuncBreak|medium|CLIPS builtin function literal for Break.|
|788|788|global|other|clash95.c|aBuildfunction|kClipsFuncBuild|medium|CLIPS builtin function literal for Build.|
|789|789|global|other|clash95.c|aClosefunction|kClipsFuncClose|medium|CLIPS builtin function literal for Close.|
|790|790|global|other|clash95.c|aCosfunction|kClipsFuncCos|medium|CLIPS builtin function literal for Cos.|
|791|791|global|other|clash95.c|aCoshfunction|kClipsFuncCosh|medium|CLIPS builtin function literal for Cosh.|
|792|792|global|other|clash95.c|aCotfunction|kClipsFuncCot|medium|CLIPS builtin function literal for Cot.|
|793|793|global|other|clash95.c|aCothfunction|kClipsFuncCoth|medium|CLIPS builtin function literal for Coth.|
|794|794|global|other|clash95.c|aCreatefunction|kClipsFuncCreate|medium|CLIPS builtin function literal for Create.|
|795|795|global|other|clash95.c|aCscfunction|kClipsFuncCsc|medium|CLIPS builtin function literal for Csc.|
|796|796|global|other|clash95.c|aCschfunction|kClipsFuncCsch|medium|CLIPS builtin function literal for Csch.|
|797|797|global|other|clash95.c|aDeffunction|kClipsFuncDef|medium|CLIPS builtin function literal for Def.|
|798|798|global|other|clash95.c|aDegradfunction|kClipsFuncDegrad|medium|CLIPS builtin function literal for Degrad.|
|799|799|global|other|clash95.c|aDeletefunction|kClipsFuncDelete|medium|CLIPS builtin function literal for Delete.|
|800|800|global|other|clash95.c|aDivfunction|kClipsFuncDiv|medium|CLIPS builtin function literal for Div.|
|801|801|global|other|clash95.c|aEqfunction|kClipsFuncEq|medium|CLIPS builtin function literal for Eq.|
|802|802|global|other|clash95.c|aEvalfunction|kClipsFuncEval|medium|CLIPS builtin function literal for Eval.|
|803|803|global|other|clash95.c|aEvenpfunction|kClipsFuncEvenp|medium|CLIPS builtin function literal for Evenp.|
|804|804|global|other|clash95.c|aExpfunction|kClipsFuncExp|medium|CLIPS builtin function literal for Exp.|
|805|805|global|other|clash95.c|aFirstfunction|kClipsFuncFirst|medium|CLIPS builtin function literal for First.|
|806|806|global|other|clash95.c|aFloatfunction|kClipsFuncFloat|medium|CLIPS builtin function literal for Float.|
|807|807|global|other|clash95.c|aFloatpfunction|kClipsFuncFloatp|medium|CLIPS builtin function literal for Floatp.|
|808|808|global|other|clash95.c|aFormatfunction|kClipsFuncFormat|medium|CLIPS builtin function literal for Format.|
|809|809|global|other|clash95.c|aGensymfunction|kClipsFuncGensym|medium|CLIPS builtin function literal for Gensym.|
|810|810|global|other|clash95.c|aGetDeffunction|kClipsFuncGetDef|medium|CLIPS builtin function literal for GetDef.|
|811|811|global|other|clash95.c|aGetdeffunction|kClipsFuncGetdef|medium|CLIPS builtin function literal for Getdef.|
|812|812|global|other|clash95.c|aHelpfunction|kClipsFuncHelp|medium|CLIPS builtin function literal for Help.|
|813|813|global|other|clash95.c|aIffunction|kClipsFuncIf|medium|CLIPS builtin function literal for If.|
|814|814|global|other|clash95.c|aInsertfunction|kClipsFuncInsert|medium|CLIPS builtin function literal for Insert.|
|815|815|global|other|clash95.c|aLengthfunction|kClipsFuncLength|medium|CLIPS builtin function literal for Length.|
|816|816|global|other|clash95.c|aLogfunction|kClipsFuncLog|medium|CLIPS builtin function literal for Log.|
|817|817|global|other|clash95.c|aLog10function|kClipsFuncLog10|medium|CLIPS builtin function literal for Log10.|
|818|818|global|other|clash95.c|aMaxfunction|kClipsFuncMax|medium|CLIPS builtin function literal for Max.|
|819|819|global|other|clash95.c|aMemberfunction|kClipsFuncMember|medium|CLIPS builtin function literal for Member.|
|820|820|global|other|clash95.c|aMinfunction|kClipsFuncMin|medium|CLIPS builtin function literal for Min.|
|821|821|global|other|clash95.c|aModfunction|kClipsFuncMod|medium|CLIPS builtin function literal for Mod.|
|822|822|global|other|clash95.c|aNeqfunction|kClipsFuncNeq|medium|CLIPS builtin function literal for Neq.|
|823|823|global|other|clash95.c|aNotfunction|kClipsFuncNot|medium|CLIPS builtin function literal for Not.|
|824|824|global|other|clash95.c|aNthfunction|kClipsFuncNth|medium|CLIPS builtin function literal for Nth.|
|825|825|global|other|clash95.c|aOddpfunction|kClipsFuncOddp|medium|CLIPS builtin function literal for Oddp.|
|826|826|global|other|clash95.c|aOpenfunction|kClipsFuncOpen|medium|CLIPS builtin function literal for Open.|
|827|827|global|other|clash95.c|aOrfunction|kClipsFuncOr|medium|CLIPS builtin function literal for Or.|
|828|828|global|other|clash95.c|aPifunction|kClipsFuncPi|medium|CLIPS builtin function literal for Pi.|
|829|829|global|other|clash95.c|aPowfunction|kClipsFuncPow|medium|CLIPS builtin function literal for Pow.|
|830|830|global|other|clash95.c|aPpdeffunction|kClipsFuncPpdef|medium|CLIPS builtin function literal for Ppdef.|
|831|831|global|other|clash95.c|aPrognfunction|kClipsFuncProgn|medium|CLIPS builtin function literal for Progn.|
|832|832|global|other|clash95.c|aRaddegfunction|kClipsFuncRaddeg|medium|CLIPS builtin function literal for Raddeg.|
|833|833|global|other|clash95.c|aRandomfunction|kClipsFuncRandom|medium|CLIPS builtin function literal for Random.|
|834|834|global|other|clash95.c|aReadfunction|kClipsFuncRead|medium|CLIPS builtin function literal for Read.|
|835|835|global|other|clash95.c|aRemovefunction|kClipsFuncRemove|medium|CLIPS builtin function literal for Remove.|
|836|836|global|other|clash95.c|aRenamefunction|kClipsFuncRename|medium|CLIPS builtin function literal for Rename.|
|837|837|global|other|clash95.c|aRestfunction|kClipsFuncRest|medium|CLIPS builtin function literal for Rest.|
|838|838|global|other|clash95.c|aReturnfunction|kClipsFuncReturn|medium|CLIPS builtin function literal for Return.|
|839|839|global|other|clash95.c|aRoundfunction|kClipsFuncRound|medium|CLIPS builtin function literal for Round.|
|840|840|global|other|clash95.c|aSecfunction|kClipsFuncSec|medium|CLIPS builtin function literal for Sec.|
|841|841|global|other|clash95.c|aSechfunction|kClipsFuncSech|medium|CLIPS builtin function literal for Sech.|
|842|842|global|other|clash95.c|aSeedfunction|kClipsFuncSeed|medium|CLIPS builtin function literal for Seed.|
|843|843|global|other|clash95.c|aSetgenfunction|kClipsFuncSetgen|medium|CLIPS builtin function literal for Setgen.|
|844|844|global|other|clash95.c|aSinfunction|kClipsFuncSin|medium|CLIPS builtin function literal for Sin.|
|845|845|global|other|clash95.c|aSinhfunction|kClipsFuncSinh|medium|CLIPS builtin function literal for Sinh.|
|846|846|global|other|clash95.c|aSqrtfunction|kClipsFuncSqrt|medium|CLIPS builtin function literal for Sqrt.|
|847|847|global|other|clash95.c|aStrcatfunction|kClipsFuncStrcat|medium|CLIPS builtin function literal for Strcat.|
|848|848|global|other|clash95.c|aSubseqfunction|kClipsFuncSubseq|medium|CLIPS builtin function literal for Subseq.|
|849|849|global|other|clash95.c|aSwitchfunction|kClipsFuncSwitch|medium|CLIPS builtin function literal for Switch.|
|850|850|global|other|clash95.c|aSymcatfunction|kClipsFuncSymcat|medium|CLIPS builtin function literal for Symcat.|
|851|851|global|other|clash95.c|aTanfunction|kClipsFuncTan|medium|CLIPS builtin function literal for Tan.|
|852|852|global|other|clash95.c|aTanhfunction|kClipsFuncTanh|medium|CLIPS builtin function literal for Tanh.|
|853|853|global|other|clash95.c|aUndeffunction|kClipsFuncUndef|medium|CLIPS builtin function literal for Undef.|
|854|854|global|other|clash95.c|aUpcasefunction|kClipsFuncUpcase|medium|CLIPS builtin function literal for Upcase.|
|855|855|global|other|clash95.c|aWhilefunction|kClipsFuncWhile|medium|CLIPS builtin function literal for While.|

## Batch 60 - CLIPS keyword strings
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|856|856|global|other|clash95.c|aRemsc|kKeywordRemsc|medium|CLIPS keyword literal for Remsc.|
|857|857|global|other|clash95.c|aZwy02|kKeywordZwy02|medium|CLIPS keyword literal for Zwy02.|
|858|858|global|other|clash95.c|aUcatblad|kKeywordUcatblad|medium|CLIPS keyword literal for Ucatblad.|
|859|859|global|other|clash95.c|aChlop|kKeywordChlop|medium|CLIPS keyword literal for Chlop.|
|860|860|global|other|clash95.c|aNiszcz|kKeywordNiszcz|medium|CLIPS keyword literal for Niszcz.|
|861|861|global|other|clash95.c|aDopen|kKeywordDopen|medium|CLIPS keyword literal for Dopen.|
|862|862|global|other|clash95.c|aHafen|kKeywordHafen|medium|CLIPS keyword literal for Hafen.|
|863|863|global|other|clash95.c|aUkrycie|kKeywordUkrycie|medium|CLIPS keyword literal for Ukrycie.|
|864|864|global|other|clash95.c|aZaraza|kKeywordZaraza|medium|CLIPS keyword literal for Zaraza.|
|865|865|global|other|clash95.c|aSoft2000|kKeywordSoft2000|medium|CLIPS keyword literal for Soft2000.|
|866|866|global|other|clash95.c|aDraw1|kKeywordDraw1|medium|CLIPS keyword literal for Draw1.|
|867|867|global|other|clash95.c|aDraw2|kKeywordDraw2|medium|CLIPS keyword literal for Draw2.|
|868|868|global|other|clash95.c|aDrawend|kKeywordDrawend|medium|CLIPS keyword literal for Drawend.|
|869|869|global|other|clash95.c|aStrategprior|kKeywordStrategprior|medium|CLIPS keyword literal for Strategprior.|
|870|870|global|other|clash95.c|aAcquire|kKeywordAcquire|medium|CLIPS keyword literal for Acquire.|
|871|871|global|other|clash95.c|aUnacquire|kKeywordUnacquire|medium|CLIPS keyword literal for Unacquire.|
|872|872|global|other|clash95.c|aRiff|kKeywordRiff|medium|CLIPS keyword literal for Riff.|
|873|873|global|other|clash95.c|aWave|kKeywordWave|medium|CLIPS keyword literal for Wave.|
|874|874|global|other|clash95.c|aBmexit|kKeywordBmexit|medium|CLIPS keyword literal for Bmexit.|
|875|875|global|other|clash95.c|aLlrs|kKeywordLlrs|medium|CLIPS keyword literal for Llrs.|
|876|876|global|other|clash95.c|aFactmngr|kKeywordFactmngr|medium|CLIPS keyword literal for Factmngr.|
|877|877|global|other|clash95.c|aCompilations|kKeywordCompilations|medium|CLIPS keyword literal for Compilations.|
|878|878|global|other|clash95.c|aConstrct|kKeywordConstrct|medium|CLIPS keyword literal for Constrct.|
|879|879|global|other|clash95.c|aDepth|kKeywordDepth|medium|CLIPS keyword literal for Depth.|
|880|880|global|other|clash95.c|aBreadth|kKeywordBreadth|medium|CLIPS keyword literal for Breadth.|
|881|881|global|other|clash95.c|aMea|kKeywordMea|medium|CLIPS keyword literal for Mea.|
|882|882|global|other|clash95.c|aComplexity|kKeywordComplexity|medium|CLIPS keyword literal for Complexity.|
|883|883|global|other|clash95.c|aSimplicity|kKeywordSimplicity|medium|CLIPS keyword literal for Simplicity.|
|884|884|global|other|clash95.c|aAgenda|kKeywordAgenda|medium|CLIPS keyword literal for Agenda.|
|885|885|global|other|clash95.c|aStatistics|kKeywordStatistics|medium|CLIPS keyword literal for Statistics.|
|886|886|global|other|clash95.c|aInscom|kKeywordInscom|medium|CLIPS keyword literal for Inscom.|
|887|887|global|other|clash95.c|aRtnlexeme|kKeywordRtnlexeme|medium|CLIPS keyword literal for Rtnlexeme.|
|888|888|global|other|clash95.c|aRtndouble|kKeywordRtndouble|medium|CLIPS keyword literal for Rtndouble.|
|889|889|global|other|clash95.c|aRtnlong|kKeywordRtnlong|medium|CLIPS keyword literal for Rtnlong.|
|890|890|global|other|clash95.c|aArgacces|kKeywordArgacces|medium|CLIPS keyword literal for Argacces.|
|891|891|global|other|clash95.c|aInsfun|kKeywordInsfun|medium|CLIPS keyword literal for Insfun.|
|892|892|global|other|clash95.c|aExitcommand|kKeywordExitcommand|medium|CLIPS keyword literal for Exitcommand.|
|893|893|global|other|clash95.c|aExit|kKeywordExit|medium|CLIPS keyword literal for Exit.|
|894|894|global|other|clash95.c|aRouter|kKeywordRouter|medium|CLIPS keyword literal for Router.|
|895|895|global|other|clash95.c|aTmpltdef|kKeywordTmpltdef|medium|CLIPS keyword literal for Tmpltdef.|
|896|896|global|other|clash95.c|aFactmch|kKeywordFactmch|medium|CLIPS keyword literal for Factmch.|
|897|897|global|other|clash95.c|aDrive|kKeywordDrive|medium|CLIPS keyword literal for Drive.|
|898|898|global|other|clash95.c|aEvaluatn|kKeywordEvaluatn|medium|CLIPS keyword literal for Evaluatn.|
|899|899|global|other|clash95.c|aCommline|kKeywordCommline|medium|CLIPS keyword literal for Commline.|
|900|900|global|other|clash95.c|aDerive|kKeywordDerive|medium|CLIPS keyword literal for Derive.|
|901|901|global|other|clash95.c|aModuldef|kKeywordModuldef|medium|CLIPS keyword literal for Moduldef.|
|902|902|global|other|clash95.c|aFactrhs|kKeywordFactrhs|medium|CLIPS keyword literal for Factrhs.|
|903|903|global|other|clash95.c|aDeftemplates|kKeywordDeftemplates|medium|CLIPS keyword literal for Deftemplates.|
|904|904|global|other|clash95.c|aStop|kKeywordStop|medium|CLIPS keyword literal for Stop.|
|905|905|global|other|clash95.c|aScanner|kKeywordScanner|medium|CLIPS keyword literal for Scanner.|
|906|906|global|other|clash95.c|aCstrnbin|kKeywordCstrnbin|medium|CLIPS keyword literal for Cstrnbin.|
|907|907|global|other|clash95.c|aGdccommand|kKeywordGdccommand|medium|CLIPS keyword literal for Gdccommand.|
|908|908|global|other|clash95.c|aSdccommand|kKeywordSdccommand|medium|CLIPS keyword literal for Sdccommand.|
|909|909|global|other|clash95.c|aGsccommand|kKeywordGsccommand|medium|CLIPS keyword literal for Gsccommand.|
|910|910|global|other|clash95.c|aSsccommand|kKeywordSsccommand|medium|CLIPS keyword literal for Ssccommand.|
|911|911|global|other|clash95.c|aDefmethods|kKeywordDefmethods|medium|CLIPS keyword literal for Defmethods.|
|912|912|global|other|clash95.c|aUndefgeneric|kKeywordUndefgeneric|medium|CLIPS keyword literal for Undefgeneric.|
|913|913|global|other|clash95.c|aCallnextmethod|kKeywordCallnextmethod|medium|CLIPS keyword literal for Callnextmethod.|
|914|914|global|other|clash95.c|aPreviewgeneric|kKeywordPreviewgeneric|medium|CLIPS keyword literal for Previewgeneric.|
|915|915|global|other|clash95.c|aClasscommand|kKeywordClasscommand|medium|CLIPS keyword literal for Classcommand.|
|916|916|global|other|clash95.c|aMethods|kKeywordMethods|medium|CLIPS keyword literal for Methods.|
|917|917|global|other|clash95.c|aGenrccom|kKeywordGenrccom|medium|CLIPS keyword literal for Genrccom.|
|918|918|global|other|clash95.c|aDffnxfun|kKeywordDffnxfun|medium|CLIPS keyword literal for Dffnxfun.|
|919|919|global|other|clash95.c|aDefglobals|kKeywordDefglobals|medium|CLIPS keyword literal for Defglobals.|
|920|920|global|other|clash95.c|aGlobldef|kKeywordGlobldef|medium|CLIPS keyword literal for Globldef.|
|921|921|global|other|clash95.c|aName|kKeywordName|medium|CLIPS keyword literal for Name.|
|922|922|global|other|clash95.c|aDefclasses|kKeywordDefclasses|medium|CLIPS keyword literal for Defclasses.|
|923|923|global|other|clash95.c|aUndefclass|kKeywordUndefclass|medium|CLIPS keyword literal for Undefclass.|
|924|924|global|other|clash95.c|aBatchcommand|kKeywordBatchcommand|medium|CLIPS keyword literal for Batchcommand.|
|925|925|global|other|clash95.c|aSavecommand|kKeywordSavecommand|medium|CLIPS keyword literal for Savecommand.|
|926|926|global|other|clash95.c|aLoadcommand|kKeywordLoadcommand|medium|CLIPS keyword literal for Loadcommand.|
|927|927|global|other|clash95.c|aBsavecommand|kKeywordBsavecommand|medium|CLIPS keyword literal for Bsavecommand.|
|928|928|global|other|clash95.c|aBloadcommand|kKeywordBloadcommand|medium|CLIPS keyword literal for Bloadcommand.|
|929|929|global|other|clash95.c|aCstrcpsr|kKeywordCstrcpsr|medium|CLIPS keyword literal for Cstrcpsr.|
|930|930|global|other|clash95.c|aGetloopcount|kKeywordGetloopcount|medium|CLIPS keyword literal for Getloopcount.|
|931|931|global|other|clash95.c|aReturn|kKeywordReturn|medium|CLIPS keyword literal for Return.|
|932|932|global|other|clash95.c|aSwitch|kKeywordSwitch|medium|CLIPS keyword literal for Switch.|
|933|933|global|other|clash95.c|aSetgen|kKeywordSetgen|medium|CLIPS keyword literal for Setgen.|
|934|934|global|other|clash95.c|aGensystem|kKeywordGensystem|medium|CLIPS keyword literal for Gensystem.|
|935|935|global|other|clash95.c|aGentime|kKeywordGentime|medium|CLIPS keyword literal for Gentime.|
|936|936|global|other|clash95.c|aTime|kKeywordTime|medium|CLIPS keyword literal for Time.|
|937|937|global|other|clash95.c|aSeed|kKeywordSeed|medium|CLIPS keyword literal for Seed.|
|938|938|global|other|clash95.c|aMemusedcommand|kKeywordMemusedcommand|medium|CLIPS keyword literal for Memusedcommand.|
|939|939|global|other|clash95.c|aOptionscommand|kKeywordOptionscommand|medium|CLIPS keyword literal for Optionscommand.|
|940|940|global|other|clash95.c|aExpandfunccall|kKeywordExpandfunccall|medium|CLIPS keyword literal for Expandfunccall.|
|941|941|global|other|clash95.c|aSetsorcommand|kKeywordSetsorcommand|medium|CLIPS keyword literal for Setsorcommand.|
|942|942|global|other|clash95.c|aAproposcommand|kKeywordAproposcommand|medium|CLIPS keyword literal for Aproposcommand.|
|943|943|global|other|clash95.c|aApropos|kKeywordApropos|medium|CLIPS keyword literal for Apropos.|
|944|944|global|other|clash95.c|aOpen|kKeywordOpen|medium|CLIPS keyword literal for Open.|
|945|945|global|other|clash95.c|aRename|kKeywordRename|medium|CLIPS keyword literal for Rename.|
|946|946|global|other|clash95.c|aFormat|kKeywordFormat|medium|CLIPS keyword literal for Format.|
|947|947|global|other|clash95.c|aCrlf|kKeywordCrlf|medium|CLIPS keyword literal for Crlf.|
|948|948|global|other|clash95.c|aTab|kKeywordTab|medium|CLIPS keyword literal for Tab.|
|949|949|global|other|clash95.c|aVtab|kKeywordVtab|medium|CLIPS keyword literal for Vtab.|
|950|950|global|other|clash95.c|aFf|kKeywordFf|medium|CLIPS keyword literal for Ff.|
|951|951|global|other|clash95.c|aEof|kKeywordEof|medium|CLIPS keyword literal for Eof.|
|952|952|global|other|clash95.c|aIofun|kKeywordIofun|medium|CLIPS keyword literal for Iofun.|
|953|953|global|other|clash95.c|aWordp|kKeywordWordp|medium|CLIPS keyword literal for Wordp.|
|954|954|global|other|clash95.c|aFloatp|kKeywordFloatp|medium|CLIPS keyword literal for Floatp.|
|955|955|global|other|clash95.c|aOddp|kKeywordOddp|medium|CLIPS keyword literal for Oddp.|
|956|956|global|other|clash95.c|aEvenp|kKeywordEvenp|medium|CLIPS keyword literal for Evenp.|
|957|957|global|other|clash95.c|aSequencep|kKeywordSequencep|medium|CLIPS keyword literal for Sequencep.|
|958|958|global|other|clash95.c|aMultifun|kKeywordMultifun|medium|CLIPS keyword literal for Multifun.|
|959|959|global|other|clash95.c|aUpcase|kKeywordUpcase|medium|CLIPS keyword literal for Upcase.|
|960|960|global|other|clash95.c|aEval|kKeywordEval|medium|CLIPS keyword literal for Eval.|
|961|961|global|other|clash95.c|aStrngfun|kKeywordStrngfun|medium|CLIPS keyword literal for Strngfun.|
|962|962|global|other|clash95.c|aCos|kKeywordCos|medium|CLIPS keyword literal for Cos.|
|963|963|global|other|clash95.c|aTan|kKeywordTan|medium|CLIPS keyword literal for Tan.|
|964|964|global|other|clash95.c|aSec|kKeywordSec|medium|CLIPS keyword literal for Sec.|
|965|965|global|other|clash95.c|aCsc|kKeywordCsc|medium|CLIPS keyword literal for Csc.|
|966|966|global|other|clash95.c|aCot|kKeywordCot|medium|CLIPS keyword literal for Cot.|
|967|967|global|other|clash95.c|aAcos|kKeywordAcos|medium|CLIPS keyword literal for Acos.|
|968|968|global|other|clash95.c|aAsin|kKeywordAsin|medium|CLIPS keyword literal for Asin.|
|969|969|global|other|clash95.c|aAtan|kKeywordAtan|medium|CLIPS keyword literal for Atan.|
|970|970|global|other|clash95.c|aAsec|kKeywordAsec|medium|CLIPS keyword literal for Asec.|
|971|971|global|other|clash95.c|aAcsc|kKeywordAcsc|medium|CLIPS keyword literal for Acsc.|
|972|972|global|other|clash95.c|aAcot|kKeywordAcot|medium|CLIPS keyword literal for Acot.|
|973|973|global|other|clash95.c|aCosh|kKeywordCosh|medium|CLIPS keyword literal for Cosh.|
|974|974|global|other|clash95.c|aSinh|kKeywordSinh|medium|CLIPS keyword literal for Sinh.|
|975|975|global|other|clash95.c|aTanh|kKeywordTanh|medium|CLIPS keyword literal for Tanh.|
|976|976|global|other|clash95.c|aSech|kKeywordSech|medium|CLIPS keyword literal for Sech.|
|977|977|global|other|clash95.c|aCsch|kKeywordCsch|medium|CLIPS keyword literal for Csch.|
|978|978|global|other|clash95.c|aCoth|kKeywordCoth|medium|CLIPS keyword literal for Coth.|
|979|979|global|other|clash95.c|aAcosh|kKeywordAcosh|medium|CLIPS keyword literal for Acosh.|
|980|980|global|other|clash95.c|aAsinh|kKeywordAsinh|medium|CLIPS keyword literal for Asinh.|
|981|981|global|other|clash95.c|aAtanh|kKeywordAtanh|medium|CLIPS keyword literal for Atanh.|
|982|982|global|other|clash95.c|aAsech|kKeywordAsech|medium|CLIPS keyword literal for Asech.|
|983|983|global|other|clash95.c|aAcsch|kKeywordAcsch|medium|CLIPS keyword literal for Acsch.|
|984|984|global|other|clash95.c|aAcoth|kKeywordAcoth|medium|CLIPS keyword literal for Acoth.|
|985|985|global|other|clash95.c|aLog10|kKeywordLog10|medium|CLIPS keyword literal for Log10.|
|986|986|global|other|clash95.c|aSqrt|kKeywordSqrt|medium|CLIPS keyword literal for Sqrt.|
|987|987|global|other|clash95.c|aPi|kKeywordPi|medium|CLIPS keyword literal for Pi.|
|988|988|global|other|clash95.c|aRound|kKeywordRound|medium|CLIPS keyword literal for Round.|
|989|989|global|other|clash95.c|aEmathfun|kKeywordEmathfun|medium|CLIPS keyword literal for Emathfun.|
|990|990|global|other|clash95.c|aTextpro|kKeywordTextpro|medium|CLIPS keyword literal for Textpro.|
|991|991|global|other|clash95.c|aWhelp|kKeywordWhelp|medium|CLIPS keyword literal for Whelp.|
|992|992|global|other|clash95.c|aFetch|kKeywordFetch|medium|CLIPS keyword literal for Fetch.|
|993|993|global|other|clash95.c|aToss|kKeywordToss|medium|CLIPS keyword literal for Toss.|
|994|994|global|other|clash95.c|aFetchcommand|kKeywordFetchcommand|medium|CLIPS keyword literal for Fetchcommand.|
|995|995|global|other|clash95.c|aTosscommand|kKeywordTosscommand|medium|CLIPS keyword literal for Tosscommand.|
|996|996|global|other|clash95.c|aConscomp|kKeywordConscomp|medium|CLIPS keyword literal for Conscomp.|
|997|997|global|other|clash95.c|aModifyinstance|kKeywordModifyinstance|medium|CLIPS keyword literal for Modifyinstance.|
|998|998|global|other|clash95.c|aInsmoddp|kKeywordInsmoddp|medium|CLIPS keyword literal for Insmoddp.|
|999|999|global|other|clash95.c|aInsfile|kKeywordInsfile|medium|CLIPS keyword literal for Insfile.|
|1000|1000|global|other|clash95.c|aInsmult|kKeywordInsmult|medium|CLIPS keyword literal for Insmult.|
|1001|1001|global|other|clash95.c|aMsgfun|kKeywordMsgfun|medium|CLIPS keyword literal for Msgfun.|
|1002|1002|global|other|clash95.c|aWerror|kKeywordWerror|medium|CLIPS keyword literal for Werror.|
|1003|1003|global|other|clash95.c|aMsgpass|kKeywordMsgpass|medium|CLIPS keyword literal for Msgpass.|
|1004|1004|global|other|clash95.c|aClassfun|kKeywordClassfun|medium|CLIPS keyword literal for Classfun.|
|1005|1005|global|other|clash95.c|aObjrtmch|kKeywordObjrtmch|medium|CLIPS keyword literal for Objrtmch.|
|1006|1006|global|other|clash95.c|aFileio|kKeywordFileio|medium|CLIPS keyword literal for Fileio.|
|1007|1007|global|other|clash95.c|aFactlhs|kKeywordFactlhs|medium|CLIPS keyword literal for Factlhs.|
|1008|1008|global|other|clash95.c|aIncrrset|kKeywordIncrrset|medium|CLIPS keyword literal for Incrrset.|
|1009|1009|global|other|clash95.c|aExprnpsr|kKeywordExprnpsr|medium|CLIPS keyword literal for Exprnpsr.|
|1010|1010|global|other|clash95.c|aPrcdrpsr|kKeywordPrcdrpsr|medium|CLIPS keyword literal for Prcdrpsr.|
|1011|1011|global|other|clash95.c|aThen|kKeywordThen|medium|CLIPS keyword literal for Then.|
|1012|1012|global|other|clash95.c|aCase|kKeywordCase|medium|CLIPS keyword literal for Case.|
|1013|1013|global|other|clash95.c|aRuncommand|kKeywordRuncommand|medium|CLIPS keyword literal for Runcommand.|
|1014|1014|global|other|clash95.c|aHaltcommand|kKeywordHaltcommand|medium|CLIPS keyword literal for Haltcommand.|
|1015|1015|global|other|clash95.c|aHalt|kKeywordHalt|medium|CLIPS keyword literal for Halt.|
|1016|1016|global|other|clash95.c|aFocuscommand|kKeywordFocuscommand|medium|CLIPS keyword literal for Focuscommand.|
|1017|1017|global|other|clash95.c|aExport|kKeywordExport|medium|CLIPS keyword literal for Export.|
|1018|1018|global|other|clash95.c|aModulpsr|kKeywordModulpsr|medium|CLIPS keyword literal for Modulpsr.|
|1019|1019|global|other|clash95.c|aTmpltrhs|kKeywordTmpltrhs|medium|CLIPS keyword literal for Tmpltrhs.|
|1020|1020|global|other|clash95.c|aModifycommand|kKeywordModifycommand|medium|CLIPS keyword literal for Modifycommand.|
|1021|1021|global|other|clash95.c|aGenrcfun|kKeywordGenrcfun|medium|CLIPS keyword literal for Genrcfun.|
|1022|1022|global|other|clash95.c|aGenerics|kKeywordGenerics|medium|CLIPS keyword literal for Generics.|
|1023|1023|global|other|clash95.c|aGenrcpsr|kKeywordGenrcpsr|medium|CLIPS keyword literal for Genrcpsr.|
|1024|1024|global|other|clash95.c|aGenrcexe|kKeywordGenrcexe|medium|CLIPS keyword literal for Genrcexe.|
|1025|1025|global|other|clash95.c|aDffnxpsr|kKeywordDffnxpsr|medium|CLIPS keyword literal for Dffnxpsr.|
|1026|1026|global|other|clash95.c|aDfnxpsr|kKeywordDfnxpsr|medium|CLIPS keyword literal for Dfnxpsr.|
|1027|1027|global|other|clash95.c|aGlobals|kKeywordGlobals|medium|CLIPS keyword literal for Globals.|
|1028|1028|global|other|clash95.c|aGloblpsr|kKeywordGloblpsr|medium|CLIPS keyword literal for Globlpsr.|
|1029|1029|global|other|clash95.c|aSendcommand|kKeywordSendcommand|medium|CLIPS keyword literal for Sendcommand.|
|1030|1030|global|other|clash95.c|aMessages|kKeywordMessages|medium|CLIPS keyword literal for Messages.|
|1031|1031|global|other|clash95.c|aMsgcom|kKeywordMsgcom|medium|CLIPS keyword literal for Msgcom.|
|1032|1032|global|other|clash95.c|aAnyinstances|kKeywordAnyinstances|medium|CLIPS keyword literal for Anyinstances.|
|1033|1033|global|other|clash95.c|aObjrtbld|kKeywordObjrtbld|medium|CLIPS keyword literal for Objrtbld.|
|1034|1034|global|other|clash95.c|aRole|kKeywordRole|medium|CLIPS keyword literal for Role.|
|1035|1035|global|other|clash95.c|aClasspsr|kKeywordClasspsr|medium|CLIPS keyword literal for Classpsr.|
|1036|1036|global|other|clash95.c|aClassexm|kKeywordClassexm|medium|CLIPS keyword literal for Classexm.|
|1037|1037|global|other|clash95.c|aCstrncmp|kKeywordCstrncmp|medium|CLIPS keyword literal for Cstrncmp.|
|1038|1038|global|other|clash95.c|aDeclare|kKeywordDeclare|medium|CLIPS keyword literal for Declare.|
|1039|1039|global|other|clash95.c|aRulelhs|kKeywordRulelhs|medium|CLIPS keyword literal for Rulelhs.|
|1040|1040|global|other|clash95.c|aCstrnpsr|kKeywordCstrnpsr|medium|CLIPS keyword literal for Cstrnpsr.|
|1041|1041|global|other|clash95.c|aAnalysis|kKeywordAnalysis|medium|CLIPS keyword literal for Analysis.|
|1042|1042|global|other|clash95.c|aRulecstr|kKeywordRulecstr|medium|CLIPS keyword literal for Rulecstr.|
|1043|1043|global|other|clash95.c|aInsqypsr|kKeywordInsqypsr|medium|CLIPS keyword literal for Insqypsr.|
|1044|1044|global|other|clash95.c|aInherpsr|kKeywordInherpsr|medium|CLIPS keyword literal for Inherpsr.|
|1045|1045|global|other|clash95.c|aAccess|kKeywordAccess|medium|CLIPS keyword literal for Access.|
|1046|1046|global|other|clash95.c|aStorage|kKeywordStorage|medium|CLIPS keyword literal for Storage.|
|1047|1047|global|other|clash95.c|aPropagation|kKeywordPropagation|medium|CLIPS keyword literal for Propagation.|
|1048|1048|global|other|clash95.c|aComposite|kKeywordComposite|medium|CLIPS keyword literal for Composite.|
|1049|1049|global|other|clash95.c|aExclusive|kKeywordExclusive|medium|CLIPS keyword literal for Exclusive.|
|1050|1050|global|other|clash95.c|aVisibility|kKeywordVisibility|medium|CLIPS keyword literal for Visibility.|
|1051|1051|global|other|clash95.c|aPublic|kKeywordPublic|medium|CLIPS keyword literal for Public.|
|1052|1052|global|other|clash95.c|aClsltpsr|kKeywordClsltpsr|medium|CLIPS keyword literal for Clsltpsr.|
|1053|1053|global|other|clash95.c|aKarkhan|kKeywordKarkhan|medium|CLIPS keyword literal for Karkhan.|

## Batch 61 - Unit attack power functions
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1054|1054|function|unit|clash95.c|sub_412B90|Unit_CalcFormationAttackPower|medium|Scans each 31-byte squad slot to note siege types (33/34) before delegating to the attack-strength aggregator `sub_41C100`, so it measures a raw formation's offensive rating with a supplied hero bonus.|
|1055|1055|function|unit|clash95.c|sub_412BE0|Unit_CalcArmyAttackPower|medium|Wraps `Unit_CalcFormationAttackPower` for full army records at `gameData + 147174 + 725 * i`, using the formation pointer at `+6` and no hero bonus, so it returns that army's attack power baseline.|
|1056|1056|function|unit|clash95.c|sub_412C30|Player_CalcTotalAttackPower|medium|Iterates every hero roster entry and roaming army for a player, summing `sub_412C00` and `Unit_CalcArmyAttackPower` results, so it totals the player's combined army attack rating.|

## Batch 62 - Battle attack calculators
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1057|1057|function|unit|clash95.c|sub_41C100|Unit_CalcAttackPower|high|Aggregates each formation slot via `Unit_CalcEffectiveness*` tables, applies hero bonus (4th arg), and handles catapult unit id 13 separately, so it directly computes an army's offensive score used by both battle resolution and garrison power queries.|
|1058|1058|function|unit|clash95.c|sub_41C300|Unit_CalcDefensePower|medium|Sums the per-unit effectiveness-B values, scales them by 300/256, and is only used to oppose `Unit_CalcAttackPower` inside `CalculateBattleResult`, indicating it's the defensive strength counterpart.|
|1059|1059|function|unit|clash95.c|sub_41C410|Hero_CalcAttackBonus|medium|Examines the seven bytes at offsets 422..428, finds the two smallest pools, and multiplies their average by a lookup keyed on the commander tier at +421, so it produces the commander/hero attack bonus passed into formation attack calculations.|

## Batch 63 - Unit capture & grouping
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1060|1060|function|unit|clash95.c|sub_412300|Unit_Capture|high|Logs via `kFmtUnitCapture`, removes siege slots, compact squads, transfers ownership, and links army facts when one force captures another, so it clearly implements the capture routine.|
|1061|1061|function|unit|clash95.c|sub_412520|Unit_CreateNearbyUnitGroup|high|Logs `Unit_CreateNearbyUnitGroup(...)`, iterates Map neighbor offsets to spawn a formation, and copies template squads into the new army, matching the nearby unit creation behavior.|
|1062|1062|function|unit|clash95.c|sub_422BE0|Unit_AddToGroup|high|Uses the `kFmtUnitAddToGroup` trace, merges two armies if there is capacity, and updates CLIPS facts plus rendering, so it implements the Unit_AddToGroup action.|

## Batch 64 - Unit siege helpers
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1063|1063|function|unit|clash95.c|sub_412B60|Unit_FormationHasSiegeEngine|medium|Scans the first ten slots of an army for unit ids 33 or 34 and returns 1 only when one is present, matching the flag used elsewhere to gate siege-specific behaviors.|

## Batch 65 - Unit formation helpers
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1064|1064|function|unit|clash95.c|sub_412000|Unit_ExtractSiegeUnits|high|Walks a formation, copies any squad with ids 31–34 into a temporary buffer, removes it from the source array, and null-terminates the buffer, so it clearly extracts siege/special squads before combat resolution.|
|1065|1065|function|unit|clash95.c|sub_4120B0|Unit_AppendFormation|high|Finds the first empty slot in the destination formation and `qmemcpy`s an entire formation block into it, which is exactly appending squads back after temporary extraction.|
|1066|1066|function|unit|clash95.c|sub_412100|Unit_HasRegularTroops|medium|Returns false when only unit ids 31–34 are present and true once any other squad appears, so it detects whether an army still has regular (non-siege) troops available.|

## Batch 66 - Army redeploy helpers
| # | Cumulative | Kind | Subsystem | File | Old Name | New Name | Confidence | Rationale |
|---|------------|------|-----------|------|----------|----------|------------|-----------|
|1067|1067|function|unit|clash95.c|sub_423050|Unit_MoveFromGroup|high|Uses the `kFmtUnitMoveFromGroup` trace, removes indexed squads from one army, plants them at a map location or merges into another army, then updates CLIPS army facts, matching the MoveFromGroup action.|

## Final Summary
- **Total Renames:** 1067
- **By Category:** globals 1051, functions 16, locals 0, parameters 0, statics 0.
- **By Wave:** unit 233, castle 178, tile 21, other 635.
- **Unresolved Identifiers:** `sub_412170` (unit id 31 check), `sub_4121A0` (unit id 32 handling), `sub_4128E0` helper callbacks, plus numerous numeric CLIPS keywords whose semantics remain unclear.
- **Patterns Observed:** Units store formations as 10 slots of 31 bytes, with ids 31–34 reserved for siege/special squads; hero/commander bonuses live near offsets 421–428; most logging strings in Polish map cleanly to gameplay actions, enabling reliable renames.
- **Suggested Next Targets:** clarify the role of unit ids 31/32 to safely rename `sub_412170`/`sub_4121A0`, derive semantics for `sub_4128E0` (battle morale adjustments), and expand renames into castle/tile subsystems where `sub_42xxxx` functions still dominate.
