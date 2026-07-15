# Strategic AI Scripting API (CLIPS host functions)

The embedded CLIPS 6.0 rules engine (see
`docs/REVERSE_ENGINEERING.md`, Queue F provenance) drives the game's strategic
AI. The compiled rule base is `strateg\clash.dat`
(`Rules_CompileStrategicRulesFile`, `sub_451E46`). Those rules call back into
the game engine through a fixed set of **host functions** the game registers at
startup with CLIPS `DefineFunction2`, wrapped here as `Rules_RegisterHostFunction`.

This document is the decoded registration table for the **game-specific** host
functions (the standard CLIPS builtins - `cos`, `printout`, `length`, etc. - are
omitted; they are ordinary CLIPS). Every row is taken verbatim from the binary's
own registration call, so the H/L command name, the C-name string, the return
type, and the argument arity are authoritative, not inferred.

## How to read this table

Each registration is
`Rules_RegisterHostFunction(<H/L name>, <ret>, "<C-name>", <fn>, "<restr>")`:

- **H/L name** - the symbol the AI rules use to call the function.
- **C-name** - the game's own internal name for the implementation.
- **ret** - CLIPS return-type letter: `i` integer, `b` boolean, `v` void,
  `s` string/symbol.
- **args** - CLIPS restriction string: first two chars are min/max argument
  count, remaining letters are per-argument types (`i` integer, `f` float,
  `s` string). E.g. `33i` = exactly 3 integer args; `22iif` = 2 args (int,
  float); `55iiiiis` = 5 args (4 int + string).
- **addr** - for functions whose bodies are not yet recovered as C, the source
  address (these appear in the canonical split declarations as `_UNKNOWN
  loc_XXXXXX` externs and in `clash95.asm` as labels inside their owning
  routine); for recovered ones, the C symbol. Resolve the owning split file
  through `data/recovered_sources.json`.

Function bodies at bare `loc_XXXXXX` addresses are packed handlers that the
decompiler did not split into standalone functions; they are documented here by
their registration only. Recovering their bodies is a natural follow-up (the
C-name and arity below define the target contract).

## Terrain, roads, and movement

| H/L name | C-name | ret | args | addr | Meaning |
| --- | --- | --- | --- | --- | --- |
| `jest_droga` | `jest_droga00` | b | 33i | `loc_4528AB` | Is there a road (between two points)? |
| `jest_droga_w_poblize` | `jest_droga_w_poblize00` | b | 33i | `loc_452907` | Is there a road nearby? |
| `jest_droga_w_poblize_zamku` | `jest_droga_w_poblize_zamku00` | b | 33i | `loc_452963` | Is there a road near the castle? |
| `jest_droga_do_portu` | `jest_droga_do_portu00` | b | 33i | `loc_4529BF` | Is there a road to the port? |
| `jest_droga_do_zamku` | `jest_droga_do_zamku00` | b | 33i | `loc_452A1B` | Is there a road to the castle? |
| `jest_droga_do_swiatyni` | `jest_droga_do_swiatyni00` | b | 33i | `loc_452A77` | Is there a road to the temple? |
| `jest_brod` | `jest_brod00` | b | 11i | `loc_452F6B` | Is there a ford? |
| `odleglosc_od_obiektu` | `odleglosc_od_obiektu00` | i | 33i | `loc_452B8B` | Distance from an object. |
| `maszeruj` | `maszeruj00` | i | 33i | `loc_452C9F` | March (to a target). |
| `maszeruj_do_swiatyni` | `maszeruj_do_swiatyni00` | i | 33i | `loc_452CFB` | March to the temple. |
| `maszeruj_blisko` | `maszeruj_blisko00` | i | 33i | `loc_452D57` | March close (to a target). |
| `maszeruj-wzdluz-drogi` | `MaszerujWzdluzDrogi` | b | 11i | `loc_457753` | March along the road. |
| `znajdz-droge-w-poblize-zamku` | `ZnajdzDrogeWPoblizeZamku` | b | 22i | `loc_45758B` | Find a road near the castle. |
| `buduj_droge` | `buduj_droge00` | b | 11i | `loc_452FA7` | Build a road. |
| `Unit_CanMove` | `Unit_CanMove00` | i | 11i | `loc_45303F` | Can the unit move? |

## Armies and units

| H/L name | C-name | ret | args | addr | Meaning |
| --- | --- | --- | --- | --- | --- |
| `jest_armia` | `jest_armia00` | b | 11i | `loc_452EA7` | Is there an army? |
| `jest_pracownik_w_armii` | `jest_pracownik_w_armii00` | b | 11i | `Rules_HostArmyHasBuilder` | Does the army contain a worker/builder? |
| `jednostka_bitewna` | `jednostka_bitewna00` | b | 11i | `Rules_HostArmyHasNormalCombatUnits` | Does the army have battle-capable units? |
| `oddzial_w_zasiegu_armii` | `oddzial_w_zasiegu_armii00` | b | 33i | `loc_452AD3` | Is a squad within the army's range? |
| `liczba_jednostek_w_oddziale` | `liczba_jednostek_w_oddziale00` | i | 11i | `loc_452EE3` | Number of units in the squad. |
| `Ilosc-Oddzialow` | `IloscOddzialow` | i | 11i | `loc_456E7F` | Number of squads. |
| `Max-Ilosc-Oddzialow` | `MaxIloscOddzialow` | b | 11i | `loc_456F87` | Maximum number of squads. |
| `stan-osob-armii` | `StanOsobArmii` | i | 22i | `loc_457459` | Personnel state/count of the army. |
| `armia-ma-jednostki-typu` | `ArmiaMaJednostkiTypu` | b | 22i | `loc_45749B` | Does the army have units of a given type? |
| `armia-tylko-jednostki-typu` | `ArmiaTylkoJednostkiTypu` | b | 22i | `Rules_HostArmyHasOnlyUnitType` | Does the army have *only* units of a given type? |
| `pobierz_oddzial_z_portu` | `pobierz_oddzial_z_portu00` | i | 00i | `Rules_HostCollectPortSupply` | Collect a squad arriving at the port. |
| `pelny_port` | `pelny_port00` | b | 00i | `Rules_HostPortHasSupplyReady` | Is the port's supply/reinforcement ready? |

## Squad orders

| H/L name | C-name | ret | args | addr | Meaning |
| --- | --- | --- | --- | --- | --- |
| `atakuj_oddzial` | `atakuj_oddzial00` | i | 22i | `loc_452DB3` | Attack an enemy squad. |
| `atakuj_budowle` | `atakuj_budowle00` | i | 22i | `loc_452F1F` | Attack a building. |
| `przejmuj_oddzial` | `przejmuj_oddzial00` | i | 22i | `loc_452DFF` | Capture/take over a squad. |
| `ukryj_oddzial` | `ukryj_oddzial00` | i | 33i | `loc_452E4B` | Hide a squad. |
| `dolacz-do-oddzialu` | `DolaczDoArmii` | b | 22i | `loc_457393` | Join a squad/army. |
| `przegrupuj-oddzialy` | `PrzegrupujArmie` | b | 22i | `loc_4573D5` | Regroup squads. |
| `przegrupuj-zamek` | `PrzegrupujZamek` | b | 22i | `loc_457417` | Regroup the castle garrison. |
| `odlacz-jednostki-slabe` | `OdlaczJednostkiSlabe` | b | 11i | `loc_4576DB` | Detach weak units. |
| `odlacz-jednostki-typu` | `OdlaczJednostkiTypu` | b | 22i | `loc_457711` | Detach units of a given type. |
| `wejdz-do-zamku` | `WejdzDoZamku` | b | 22i | `loc_457351` | Enter the castle. |
| `Wyprowadzenie-Oddzialu` | `WyprowadzenieOddzialu` | i | 22i | `loc_457035` | Deploy/lead out a squad. |
| `Wyprowadzenie-Oddzialow` | `WyprowadzenieOddzialow` | i | 11i | `loc_457077` | Deploy/lead out squads. |
| `Wyprowadz-Chlopow` | `WyprowadzChlopow` | i | 44i | `loc_456EF7` | Lead out peasants. |
| `znajdz-najlepszy` | `Znajdz_Najlepszy` | i | 55i | `loc_457789` | Find the best (target/option). |

## Castle, economy, and licences

| H/L name | C-name | ret | args | addr | Meaning |
| --- | --- | --- | --- | --- | --- |
| `Pieniadze` | `Pieniadze` | i | 11i | `loc_4569DA` | Money/treasury. |
| `Podatek` | `Podatek` | i | 11i | `loc_4568F6` | Current tax. |
| `Zmien-Podatek` | `ZmienPodatek` | v | 22iif | `loc_4567C6` | Change the tax rate. |
| `Numer-Tury` | `NumerTury` | i | 00i | `loc_456A7C` | Turn number. |
| `Poziom-Tech` | `PoziomTech` | i | 11i | `loc_456BBB` | Technology level. |
| `Zadowolenie` | `Zadowolenie` | i | 11i | `loc_456C93` | Population satisfaction/happiness. |
| `Ilosc-Chlopow` | `IloscChlopow` | i | 11i | `loc_456CFF` | Peasant count. |
| `Sila-Gracza` | `SilaGracza` | i | 11i | `loc_456C27` | Player's overall strength. |
| `Sila-Zamku` | `SilaZamku` | i | 11i | `loc_456A46` | Castle strength. |
| `Sila-Murow` | `SilaMurow` | i | 11i | `loc_456A10` | Wall strength. |
| `moc-przeciwnika-pod-murami` | `MocPrzeciwnikaPodMurami2` | i | 11i | `loc_457555` | Enemy strength massed under the walls. |
| `Typ-Budowli` | `TypBudowli` | i | 11i | `loc_456BF1` | Building type. |
| `Nazwa-Zamku` | `NazwaZamku` | s | 11i | `loc_4570AD` | Castle name. |
| `liczba-wolnych-miejsc-w-zamku` | `LiczbaWolnychMiejscWZamku` | i | 11i | `loc_45751F` | Number of free garrison slots in the castle. |
| `Jest-Jednostka-W-Zamku` | `JestJednostkaWZamku` | b | 22i | `loc_456FBD` | Is there a unit in the castle? |
| `Upgrade-Wall` | `UpgradeWall` | v | 11i | `loc_456796` | Upgrade the walls. |
| `Can-Upgrade-Wall` | `CanUpgradeWall` | i | 11i | `loc_456E49` | Can the walls be upgraded? |
| `Is-Licence` | `IsLicence` | b | 22i | `loc_45692C` | Does the player hold a licence? |
| `Buy-Licence` | `BuyLicence` | b | 22i | `loc_456B0D` | Buy a licence. |
| `Can-Buy-Licence` | `CanBuyLicence` | b | 22i | `loc_456D8F` | Can a licence be bought? |
| `Remove-Licence` | `RemoveLicence` | v | 22i | `loc_456806` | Remove a licence. |
| `Licencja-Index` | `LicencjaIndex` | i | 22i | `loc_456DD1` | Licence index (2-arg form). |
| `Licencja-Ind` | `LicencjaInd` | i | 11i | `loc_456E13` | Licence index (1-arg form). |

## Construction and production

| H/L name | C-name | ret | args | addr | Meaning |
| --- | --- | --- | --- | --- | --- |
| `Buduj-Zamek` | `BudujZamek` | b | 55iiiiis | `loc_456AA8` | Build a castle (4 int params + name). |
| `Kup-Szkola` | `KupSzkola` | b | 11i | `loc_45696E` | Buy a school. |
| `Kup-Kuznia` | `KupKuznia` | b | 11i | `loc_4569A4` | Buy a forge/smithy. |
| `Kup-Szpital` | `KupSzpital` | b | 11i | `loc_456B85` | Buy a hospital. |
| `Kup-Koszary` | `KupKoszary` | b | 11i | `loc_456B4F` | Buy barracks. |
| `Kup-Warsztat` | `KupWarsztat` | b | 11i | `loc_456C5D` | Buy a workshop. |
| `buduj_pulapke` | `buduj_pulapke00` | i | 33i | `loc_452FE3` | Build a trap. |
| `Zacznij-Produkcje` | `ZacznijProdukcje` | v | 22i | `loc_4568BA` | Start production. |
| `Is-Production` | `IsProduction` | b | 11i | `loc_456CC9` | Is production active (in a building)? |
| `Is-Production-Any` | `IsProductionAny` | b | 22i | `loc_456EB5` | Is any production active? |
| `Czy-Minimalny` | `CzyMinimalny` | b | 44i | `loc_456D35` | Is (something) at its minimum? |
| `swiatynia` | `swiatynia00` | i | 22i | `loc_452753` | Temple action/query. |
| `swiatynia_OK` | `swiatynia_OK00` | b | 33i | `loc_452C43` | Is the temple usable/valid? |
| `swiatynia_w_zasiegu_armii` | `swiatynia_w_zasiegu_armii00` | b | 33i | `loc_452BE7` | Is a temple within the army's range? |
| `budowla_w_zasiegu_armii` | `budowla_w_zasiegu_armii00` | b | 33i | `loc_452B2F` | Is a building within the army's range? |
| `kop_skarb` | `kop_skarb00` | i | 11i | `loc_45279F` | Dig for treasure. |
| `Pal-Budowle` | `PalBudowle` | v | 11i | `loc_456766` | Burn buildings. |

## Healthcare, training, and plague

| H/L name | C-name | ret | args | addr | Meaning |
| --- | --- | --- | --- | --- | --- |
| `Leczenie` | `Leczenie` | v | 11i | `loc_456706` | Healing. |
| `Zacznij-Leczenie` | `ZacznijLeczenie` | v | 22i | `loc_456842` | Start healing. |
| `ma-jednostki-do-leczenia` | `MaJednostkiDoLeczenia` | b | 11i | `loc_4575CD` | Are there units that need healing? |
| `znajdz-zamek-do-leczenia` | `ZnajdzZamekDoLeczenia` | b | 11i | `loc_457603` | Find a castle for healing. |
| `idz-do-leczenia` | `IdzDoLeczenia` | b | 11i | `loc_457639` | Go to healing. |
| `Jednostki-Do-Szpitala` | `JednostkiDoSzpitala` | b | 11i | `loc_456FFF` | Send units to the hospital. |
| `jest-zaraza-w-zamku` | `JestZarazaWZamku` | b | 11i | `loc_45766F` | Is there plague in the castle? |
| `jest-zaraza-w-oddziale` | `JestZarazaWOddziale` | b | 11i | `loc_4576A5` | Is there plague in the squad? |
| `Szkolenie` | `Szkolenie` | v | 11i | `loc_456736` | Training. |
| `Zacznij-Szkolenie` | `ZacznijSzkolenie` | v | 22i | `loc_45687E` | Start training. |
| `Jednostki-Do-Szkoly` | `JednostkiDoSzkoly` | b | 11i | `loc_456F51` | Send units to the school. |

## Recovery notes

- The `Rules_Host*` rows are already recovered as C functions; the remaining
  `loc_XXXXXX` rows are packed handlers (adjacent ~76-byte routines owned by the
  dispatchers around `sub_452390` and `sub_456700`) whose bodies are not yet
  split out. Their contracts (name, return type, arity) are fixed by the
  registration and make good next recovery targets.
- Polish glosses are translations of the game's own H/L command names; where a
  function's exact effect is unproven the meaning column states the literal
  translation, not a verified behavioral claim.
- Argument-type letters follow the CLIPS restriction-string convention; the
  leading count digits are min/max arity.
