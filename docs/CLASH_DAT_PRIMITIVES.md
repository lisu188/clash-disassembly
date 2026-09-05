# `CLASH.DAT` compiled primitive-expression recovery

## Status

The retail `CLASH.DAT` contains 5,237 packed CLIPS expressions. Nine
bitmap-backed fact/object matcher primitive types account for **1,273 expression
nodes** that previously appeared only as `?prim*` placeholders. Their bitfield
payloads are decoded by `tools/clash_dat_primitives.py` and locked by
`tools/check_clash_dat_primitives.py`.

A follow-up pass also decoded the 25 serialized deftemplate records. This
changed an earlier assumption: the strategic fact relations are **ordered
implied facts**, not explicit templates with named slots.

- 25 deftemplate records total;
- 24 are `implied` relations;
- `initial-fact` is the only non-implied entry;
- `NumberOfTemplateSlots = 0`;
- every serialized `slotList` is `-1`;
- every `numberOfSlots` is `0`.

Therefore there are no missing fact-slot names to recover from this image. The
fact matcher uses the implied ordered-fact representation (one multislot whose
fields are positional). Object-pattern slot IDs remain a separate class/COOL
recovery problem.

## Reproduction

```sh
python3 tools/analyze_clash_dat_primitives.py CLASH.DAT
python3 tools/analyze_clash_dat_primitives.py CLASH.DAT \
  --json /tmp/clash-primitives.json \
  --text /tmp/clash-primitives.txt
python3 tools/check_clash_dat_primitives.py
python3 tools/check_clash_dat_templates.py
```

## Decoded expression types

| Expression type | Count | Bitmap bytes |
| --- | ---: | ---: |
| `FACT_JN_CMP2` (24) | 103 | 8 |
| `FACT_SLOT_LENGTH` (25) | 32 | 4 |
| `FACT_PN_VAR3` (28) | 4 | 4 |
| `FACT_JN_VAR1` (29) | 36 | 4 |
| `FACT_JN_VAR3` (31) | 421 | 4 |
| `FACT_PN_CONSTANT2` (33) | 30 | 4 |
| `OBJ_GET_SLOT_JNVAR1` (47) | 630 | 8 |
| `OBJ_PN_CONSTANT` (50) | 2 | 4 |
| `OBJ_JN_CMP1` (52) | 15 | 8 |
| **Total** | **1,273** | |

The image additionally contains 47 `HANDLER_GET` (58) and 23 `HANDLER_PUT`
(59) expressions. All 70 reference six-byte bitmap records. Their primitive
identity is confirmed, but the direct message-handler slot-reference layout is
still intentionally kept raw rather than guessed.

## Typed recovery model

`tools/clash_dat_primitives.py` provides typed records layered on top of the raw
BSAVE parser:

- `PackedExpression`
- `DefruleRecord`
- `JoinRecord`
- `PrimitiveDecode`

`tools/clash_dat_templates.py` adds `DeftemplateRecord` and decodes the 24-byte
`bsaveDeftemplate` representation.

The raw arrays returned by `tools/decompile_clash_dat.py` remain the evidence
source. Typed layers are additive and can always be compared with the original
bytes.

## Fact primitive layouts

### `FACT_JN_VAR1` — type 29

```text
bit  0       factAddress
bit  1       allFields
bits 2..9    whichPattern
bits 10..17  whichSlot
bits 18..25  whichField
```

The stored pattern index is source pattern ordinal minus one. For this ruleset,
`whichSlot` addresses the implied relation's ordered multislot and
`whichField`/the multifield offsets identify positional ordered-fact fields.

### `FACT_JN_VAR3` — type 31

```text
bit  0        fromBeginning
bit  1        fromEnd
bits 2..8     beginOffset
bits 9..15    endOffset
bits 16..23   whichPattern
bits 24..31   whichSlot
```

This is the dominant fact accessor: 421 nodes.

### `FACT_PN_VAR3` — type 28

```text
bit  0        fromBeginning
bit  1        fromEnd
bits 2..8     beginOffset
bits 9..15    endOffset
bits 16..23   whichSlot
```

### `FACT_SLOT_LENGTH` — type 25

```text
bits 0..7   minLength
bit  8      exactly
bits 9..16  whichSlot
```

Retail bitmap `04 01 00 00` is an exact four-field length test for slot 0.

### `FACT_PN_CONSTANT2` — type 33

```text
bit  0        testForEquality
bit  1        fromBeginning
bits 2..9     offset
bits 10..17   whichSlot
```

The tested constant is attached through the expression argument tree.

### `FACT_JN_CMP2` — type 24

```text
bit  0        pass
bit  1        fail
bits 2..8     slot1
bit  9        fromBeginning1
bits 10..16   offset1
bits 17..24   pattern2
bits 25..31   slot2
bit  32       fromBeginning2
bits 33..39   offset2
```

The record spans two 32-bit bitfield allocation units, matching the eight-byte
bitmap present in the Win32 image.

## Object primitive layouts

### `OBJ_GET_SLOT_JNVAR1` — type 47

```text
bits 0..14    whichSlot
bits 15..22   whichPattern
bits 23..30   whichField
bit  31       objectAddress
bit  32       allFields
```

This is the largest decoded group: 630 expression nodes.

### `OBJ_PN_CONSTANT` — type 50

```text
bits 0..6   offset
bit  7      pass
bit  8      fail
bit  9      general
bit 10      fromBeginning
```

### `OBJ_JN_CMP1` — type 52

```text
bits 0..14    firstSlot
bit  15       pass
bits 16..30   secondSlot
bit  31       fail
bits 32..39   firstPattern
bits 40..47   secondPattern
```

Retail bitmap `07 80 07 00 03 02 00 00` compares slot 7 of object pattern 3
with slot 7 of object pattern 2.

## Ordered fact relations recovered

The implied relation names are:

```text
gracz misja najblizej kasuj oddz swiatynia skarb pulapka budowanie
usunieto port gameinfo tura zamek zdobyty schemat zginal-zamek
zbudowano wyznaczony zamek_place maszeruj ilosc-zamkow ilosc-twierdz
zamek-wyslal-bron-biologiczna
```

Their serialized `patternNetwork` roots point into the 64-node fact pattern
network recovered by `tools/clash_dat_rete.py`.

## What is now solved

The combination of primitive decoding, ordered-fact recovery, and RETE recovery
means the decompiler can now distinguish:

- the source pattern ordinal referenced by a join expression;
- the strategic ordered relation (`gracz`, `oddz`, `zamek`, ...);
- positional fields and multifield offsets in that relation;
- object pattern and object slot IDs;
- constant pattern tests and join comparisons;
- negated joins and the exact ordered join path for every rule.

See [class, RETE, and LHS recovery](CLASH_DAT_LHS.md#current-recovery-level)
for the 295-join topology and rule-LHS skeleton recovery.

## Remaining primitive-level work

1. Decode the six-byte direct slot reference used by `HANDLER_GET`/`HANDLER_PUT`.
2. Recover class/slot-name metadata so object slot IDs can be rendered by name.
3. Feed decoded primitive accessors into the CLP pretty-printer so remaining
   `?prim*` tokens become stable semantic field references.
4. After the exact access paths are known, perform variable unification. Do not
   invent original variable names that BSAVE does not preserve.
