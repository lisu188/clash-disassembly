# Save Slot DAT Format

This document covers the save-slot `save/N.dat` files, not `strateg/clash.dat`.
The boot-time `strateg/clash.dat` file is a separate CLIPS binary construct file.

## Evidence

The recovered save writer and loader in the manifest-backed persistence sources under `src/persistence/` show the complete outer file shape:

- `saveGame` writes a 16-byte slot label and then `586398` bytes from `gameData` (`GAMEDATA_SAVE_IMAGE_BYTES`).
- `SaveSlot_LoadGame` skips 16 bytes and reads `0x8F29E` bytes back into `gameData`.
- `SaveSlot_LoadLabelOrPlaceholder` reads only the first 16 bytes for the load-menu label.
- `SaveSlot_FormatFactsFilePath` uses the separate `save/N.fac` CLIPS facts sidecar.

Therefore a normal DAT is exactly **586414 bytes** (`16 + 0x8F29E`).

## DAT Layout

All recovered integer payload fields are little-endian.

| File offset | Size | Meaning | Confidence |
| --- | ---: | --- | --- |
| `0x000000` | `0x10` | Save-slot label bytes. | High |
| `0x000010` | `0x8F29E` | Raw `gameData` image. | High |

Formula:

```text
DAT file offset = 0x10 + gameData offset
```

The label is byte-exact storage. Existing saves commonly contain a short NUL-padded ASCII-compatible name; the precise legacy text encoding outside that range remains intentionally unspecified.

## gameData Payload Map

| gameData offset | File offset | Size | Region | Confidence |
| ---: | ---: | ---: | --- | --- |
| `0` | `0x10` | `140000` | 100x100 map tile records, 14 bytes per tile. | High |
| `140000` | `0x222F0` | `24` | World/session header. | High |
| `140024` | `0x22308` | `7115` | Five player runtime records, 1423 bytes each. | High |
| `147139` | `0x23ED3` | `8` | Turn owner and viewed-player indices. | High |
| `147147` | `0x23EDB` | `27` | Persistent options record: six dwords followed by three slider bytes. | High for layout |
| `147174` | `0x23EF6` | `362500` | 500 `UnitStackRecord` records, 725 bytes each. | High |
| `509674` | `0x7C6FA` | `46700` | 100 `BuildingRecord` records, 467 bytes each. | High |
| `556374` | `0x87D66` | `20000` | Unit/building occupancy index layer, 10000 uint16 cells. | High |
| `576374` | `0x8CB86` | `10000` | Trap owner-mask layer, 100x100 bytes. | High |
| `586374` | `0x8F286` | `24` | Port runtime state, six dwords. | High |

The payload ends at `gameData` offset `586398`, file offset `0x8F2AE`.

## World/session header

The 24-byte header at `gameData + 140000` is:

| Relative offset | Size | Meaning |
| ---: | ---: | --- |
| `+0` | 4 | map width |
| `+4` | 4 | map height |
| `+8` | 4 | map-view left/camera X |
| `+12` | 4 | map-view top/camera Y |
| `+16` | 1 | map theme index |
| `+17` | 4 | signed active mission index |
| `+21` | 1 | mission-failure/state flag |
| `+22` | 2 | game turn counter |

This one-byte theme field is why treating `gameData + 140016` as a four-byte mission id is incorrect.

## Persistent options record

`gameData + 147147` is not padding. Campaign transitions copy all 27 bytes verbatim, the options UI reads/writes the block, and `Options_ApplyRecordSettings` consumes it.

| Relative offset | Size | Recovered role | Confidence |
| ---: | ---: | --- | --- |
| `+0` | 4 | transition/event-animation enable flag | High |
| `+4` | 4 | world/battle grid overlay flag | High |
| `+8` | 4 | world-map information/status overlay flag | High |
| `+12` | 4 | movement-animation suppression/fast-movement flag | High |
| `+16` | 4 | music enabled | High |
| `+20` | 4 | unit/sound-effects enabled | High |
| `+24` | 1 | scroll-speed raw slider value | High |
| `+25` | 1 | sound-volume raw slider value | High |
| `+26` | 1 | signed music-volume raw slider value; one shared options-application path also feeds this byte into brightness-offset code | Medium/High |

The first four names intentionally describe observed behavior rather than claiming exact localized checkbox captions.

## Unit stack tail and rules fact handle

Each 725-byte `UnitStackRecord` ends with:

| Relative offset | Size | Meaning | Confidence |
| ---: | ---: | --- | --- |
| `+720` | 1 | hidden-on-world-map flag | High |
| `+721` | 4 | cached CLIPS/rules army-fact handle | High |

The four bytes at `+721..+724` are not padding. `Rules_CreateArmyFact` stores the returned asserted-fact handle there; `Rules_LinkArmyFact` / `Rules_SyncArmyFactStrength` and copy/reset paths reuse the same dword. The value is runtime-local implementation state, not a portable army identifier.

## Unit slot packed state

The 31-byte `UnitSlotRecord` contains two packed state bytes whose historical interpretations are easy to get wrong:

- `+12` bits `0..1`: status level used by combat-stat helpers.
- `+12` bits `2..3`: order/state subfield.
- `+12` bits `4..6`: ranged volleys already used.
- `+12` bit `7`: unresolved.
- `+13` bit `0x01`: ready/turn-state flag.
- `+13` bit `0x02`: spent-turn flag; suppresses fatigue recovery.
- `+13` bit `0x04`: low-morale refusal flag.
- `+13` bit `0x08`: plague flag.
- `+13` upper four bits: unresolved.

The low two bits at `+12` should therefore not be documented as a generic experience level, and bits `2..3` are not experience progress.

## Building record highlights

The authoritative building layout is recorded in `RECOVERED_STRUCTURES.json`. Save-editor consumers should particularly note:

- `+4`: signed building type; `-1` marks an unused record.
- `+5..+15`: 11-byte display-name buffer.
- `+16`: signed construction work remaining; `0` means complete and `-1` is the unused/destroyed sentinel.
- `+18`: twelve 31-byte garrison slots.
- `+390..+401`: garrison service state; bits `0..2` training countdown, bits `3..5` repair countdown.
- `+402..+413`: unit-production licence type ids, `-1` empty; these are not castle add-on ids.
- `+414`: active production-licence slot index.
- `+415`: production turns remaining.
- `+416`: permanent castle add-on flags.
- `+420`: staged construction/upgrade lock.
- `+421`: wall strength (`SilaMurow`).
- `+422..+428`: seven wall/building section-integrity bytes.
- `+430`: peasant count in the low 12 bits.
- `+432`: signed 12-bit population-growth delta in the low 12 bits.
- `+434`: satisfaction.
- `+435`: plague state in the low three bits.
- `+436`: tax rate in the low six bits.
- `+437`: still unresolved; preserve it.
- `+438`: stored money.
- `+442`: last collected gold income.
- `+444`: technology level in the low three bits.
- `+445`: three six-byte prisoner records.
- `+463`: cached CLIPS/rules castle-fact handle.

The six-byte prisoner subrecord is `type:int8`, captured owner `uint8`, turns-held `uint8`, pending-action `uint8`, ransom value `uint16`.

## Occupancy layer

The 20,000-byte region at `gameData + 556374` is 10,000 little-endian uint16 cells, indexed on the logical 100x100 world grid.

Recovered encoding:

- `0xFFFF`: empty;
- `0..499`: army-stack index;
- `0x8000..0x8063`: building index `value - 0x8000`.

This is a separate occupancy/index layer, not part of the 14-byte terrain record array. A save editor should cross-check edited army/building coordinates against this layer rather than treating it as opaque tail data.

## Trap mask and port tail

`gameData + 576374` is one trap owner/reveal mask byte per 100x100 tile. Trap creation sets player bits and trigger/clear paths zero the tile byte.

The final six dwords at `gameData + 586374` are:

1. signed port row (`-1` = no port),
2. signed port column,
3. next reinforcement turn,
4. reinforcement-ready flag,
5. pending reinforcement unit count,
6. shoreline visual-variant flag.

## Sidecar FAC Format

The `.fac` sidecar is not embedded in the DAT file. It is a text facts file written and loaded through the CLIPS facts interface. Nonempty samples begin with `(initial-fact)` and may contain facts such as traps, castle-placement state, and staged-building facts.

The DAT loader rebuilds transient army and castle facts from raw `gameData` before loading the `.fac` sidecar, so a full save slot consists of both pieces of state.

## Editor safety rules

- Preserve all bytes and high bits that have no proven semantic name.
- Do not resize the DAT.
- Treat rules fact handles as transient/runtime state, even though their storage fields are structurally recovered.
- Do not allow historical editor terminology to override executable-backed field meanings.
- Packed fields must be updated with read-modify-write masks.
- When changing army/building position or lifecycle state, maintain the occupancy layer consistently.
