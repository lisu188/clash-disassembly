# Save Slot DAT Format

This document covers the save-slot `save/N.dat` files, not `strateg/clash.dat`.
The boot-time `strateg/clash.dat` file is a separate CLIPS binary construct file.

## Evidence

The recovered save writer and loader in `clash95.c` show the complete outer file
shape:

- `saveGame` formats `save\\%d.dat`, writes a 16-byte slot label, then writes
  `586398` bytes from `gameData` (`GAMEDATA_SAVE_IMAGE_BYTES`).
- `SaveSlot_LoadGame` opens `save\\%d.dat`, skips 16 bytes, then reads
  `0x8F29E` bytes (`GAMEDATA_SAVE_IMAGE_BYTES`) back into `gameData`.
- `SaveSlot_LoadLabelOrPlaceholder` reads only the first 16 bytes for load-menu
  labels.
- `SaveSlot_FormatFactsFilePath` formats `save\\%d.fac`; the save/load path
  stores and reloads rules facts there through the CLIPS `save-facts` /
  `load-facts` helpers.

Local installed saves under `/mnt/c/clash/save` corroborate this: `0.dat..5.dat`
are all exactly `586414` bytes, which is `16 + 0x8F29E`.

## DAT Layout

All integer payload fields currently recovered from `gameData` are little-endian.

| File offset | Size | Meaning | Confidence |
| --- | ---: | --- | --- |
| `0x000000` | `0x10` | Save-slot label bytes. The load menu reads these 16 bytes and appends a temporary NUL when displaying them. | High |
| `0x000010` | `0x8F29E` | Raw `gameData` image. This is copied directly into the runtime allocation on load. | High |

Formula:

```text
DAT file offset = 0x10 + gameData offset
```

The label is byte-exact storage. Existing samples decode as short NUL-padded
ASCII-compatible strings such as `asd`, `cam`, and `xd`, but the original text
encoding beyond that remains ambiguous.

## gameData Payload Map

| gameData offset | File offset | Size | Region | Confidence |
| ---: | ---: | ---: | --- | --- |
| `0` | `0x10` | `140000` | 100x100 map tile records, 14 bytes per tile. | High |
| `140000` | `0x222F0` | `24` | World/session header: map dimensions, camera, theme, mission id, turn counter. | High |
| `140024` | `0x22308` | `7115` | Five player runtime records, 1423 bytes each. | High |
| `147139` | `0x23ED3` | `8` | Turn owner and viewed-player indices. | High |
| `147147` | `0x23EDB` | `27` | Gap before unit stacks; not fully named. | Low |
| `147174` | `0x23EF6` | `362500` | `UNIT_STACK_TABLE_COUNT` (500) unit stack records, `UNIT_STACK_STRIDE` (725) bytes each. | High |
| `509674` | `0x7C6FA` | `46700` | 100 building records, 467 bytes each. | High |
| `556374` | `0x87D66` | `20000` | Unit/building occupancy index layer, 100 rows x 200 bytes. | High |
| `576374` | `0x8CB86` | `10000` | Trap owner-mask layer, 100x100 bytes. | High |
| `586374` | `0x8F286` | `24` | Port runtime state, six dwords. | High |

The payload ends at `gameData` offset `586398`, file offset `0x8F2AE`.

## Sidecar FAC Format

The `.fac` sidecar is not embedded in the DAT file. It is a text facts file
written and loaded through the CLIPS facts interface. Local samples are CRLF
text and begin with `(initial-fact)` when nonempty, followed by facts such as:

```clips
(pulapka 0 11)
(zamek_place row col)
(budowanie transfer 0 0 ...)
```

The DAT loader rebuilds transient army and castle facts from the raw `gameData`
image before loading the `.fac` sidecar, so both files are needed to faithfully
restore a save slot.

## Ambiguity Rules

- Unknown bytes inside known regions remain unknown until code evidence names
  them.
- External game terminology does not override the recovered offset evidence.
- This format pass is read-only. No save writer/editor is claimed.
