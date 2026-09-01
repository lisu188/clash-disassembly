# `CLASH.DAT` compiled primitive-expression recovery

## Status

The first expression-level recovery pass after the base BSAVE parser is complete.
The retail `CLASH.DAT` contains 5,237 packed expressions. Nine bitmap-backed
fact/object matcher primitive types account for **1,273 expressions** that were
previously emitted only as `?prim*` placeholders. Their bitfield payloads are now
decoded by `tools/clash_dat_primitives.py` and regression-checked by
`tools/check_clash_dat_primitives.py`.

This work deliberately separates two confidence levels:

- **decoded:** the bitmap layout is supported by the CLIPS 6.0 structure layout,
  generator semantics, the recovered runtime, and the byte sizes observed in
  the retail image;
- **typed but unresolved:** the primitive type itself is known, but its internal
  bitmap structure is not yet promoted to semantic fields.

The latter currently applies to `HANDLER_GET`/`HANDLER_PUT` direct-slot
references. No guessed layout is committed for those 70 expressions.

## Reproduction

```sh
python3 tools/analyze_clash_dat_primitives.py CLASH.DAT
python3 tools/analyze_clash_dat_primitives.py CLASH.DAT \
  --json /tmp/clash-primitives.json \
  --text /tmp/clash-primitives.txt
python3 tools/check_clash_dat_primitives.py
```

Expected decoded counts:

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

Additionally the image contains 47 `HANDLER_GET` (58) and 23 `HANDLER_PUT`
(59) expressions. Every one references a six-byte bitmap. Their type identity
is known from the CLIPS evaluator registration, but the six-byte direct-slot
reference record remains unresolved.

## Typed BSAVE model

`tools/clash_dat_primitives.py` introduces typed Python records for the parts of
the already-parsed image that are needed by the next recovery stages:

- `PackedExpression`
- `DefruleRecord`
- `JoinRecord`
- `PrimitiveDecode`

The original dictionaries/raw arrays are still retained by
`tools/decompile_clash_dat.py`; the typed layer is additive. This is intentional:
raw BSAVE data remains the evidence source while higher-level recovery code can
stop depending on positional integer arrays.

## Fact matcher layouts

### `FACT_JN_VAR1` — type 29

CLIPS `factGetVarJN1Call` layout:

```text
bit  0       factAddress
bit  1       allFields
bits 2..9    whichPattern
bits 10..17  whichSlot
bits 18..25  whichField
```

The CLIPS generator stores `pattern - 1`, therefore the decoder exposes both
`which_pattern` (the stored value) and `source_pattern_ordinal` (stored + 1).

Retail example:

```text
bitmap 05 00 00 00
factAddress = 1
whichPattern = 1
sourcePatternOrdinal = 2
```

Semantically this is a reference to the fact matched by source pattern 2 rather
than the opaque former `?prim29_5`.

### `FACT_JN_VAR3` — type 31

CLIPS `factGetVarJN3Call` layout:

```text
bit  0        fromBeginning
bit  1        fromEnd
bits 2..8     beginOffset
bits 9..15    endOffset
bits 16..23   whichPattern
bits 24..31   whichSlot
```

This is the dominant fact accessor in the image: 421 expression nodes. It
represents access to fields in multifield fact slots from a previous pattern in
the join network.

### `FACT_PN_VAR3` — type 28

Pattern-network counterpart of the multifield accessor:

```text
bit  0        fromBeginning
bit  1        fromEnd
bits 2..8     beginOffset
bits 9..15    endOffset
bits 16..23   whichSlot
```

### `FACT_SLOT_LENGTH` — type 25

CLIPS `factCheckLengthPNCall`:

```text
bits 0..7   minLength
bit  8      exactly
bits 9..16  whichSlot
```

Retail sample `04 01 00 00` decodes as an exact length check of 4 fields for
slot 0.

### `FACT_PN_CONSTANT2` — type 33

CLIPS `factConstantPN2Call`:

```text
bit  0        testForEquality
bit  1        fromBeginning
bits 2..9     offset
bits 10..17   whichSlot
```

The compared constant is carried as the expression's argument list, not in the
bitmap itself.

### `FACT_JN_CMP2` — type 24

CLIPS `factCompVarsJN2Call` spans two 32-bit compiler bitfield allocation units,
which explains the eight-byte bitmap in this Win32 image:

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

This makes 103 previously anonymous join predicates structurally inspectable.

## Object matcher layouts

### `OBJ_GET_SLOT_JNVAR1` — type 47

CLIPS `ObjectMatchVar1`:

```text
bits 0..14    whichSlot
bits 15..22   whichPattern
bits 23..30   whichField
bit  31       objectAddress
bit  32       allFields
```

The final bit requires a second 32-bit storage unit, matching the eight-byte
retail bitmap. This is the largest recovered group: 630 expressions.

Retail sample:

```text
02 80 02 00 01 00 00 00
whichSlot    = 2
whichPattern = 5
whichField   = 0
objectAddress = 0
allFields     = 1
```

The source-like semantic form is therefore `object[p5].slot[2]`.

### `OBJ_PN_CONSTANT` — type 50

CLIPS `ObjectCmpPNConstant`:

```text
bits 0..6   offset
bit  7      pass
bit  8      fail
bit  9      general
bit 10      fromBeginning
```

The constant/test expression is attached through the expression argument.

### `OBJ_JN_CMP1` — type 52

CLIPS `ObjectCmpJoinSingleSlotVars1`:

```text
bits 0..14    firstSlot
bit  15       pass
bits 16..30   secondSlot
bit  31       fail
bits 32..39   firstPattern
bits 40..47   secondPattern
```

Retail sample `07 80 07 00 03 02 00 00` decodes to a comparison between slot 7
of object pattern 3 and slot 7 of object pattern 2.

## Provenance

The numeric expression type IDs follow CLIPS 6.0 `constant.h`. The fact bitfield
layouts and generator behavior correspond to `factgen.h`/`factgen.c`; object
layouts correspond to `objrtfnx.h` and the object pattern generator. The
recovered Clash runtime independently confirms the evaluator/BSAVE machinery
and registers types 58/59 as direct message-handler slot get/put operations.

This is stronger than deriving semantics from Polish rule/function strings:
the decoder maps the exact bytes consumed by the CLIPS evaluator to the exact
compiler-side field definitions.

## What this unlocks

Before this pass, access expressions in RHS/join tests appeared as forms such as
`?prim29_5`, `?prim31_...`, or `?prim47_b...`. The decoder can now describe them
in terms of:

- fact pattern ordinal;
- object pattern index;
- slot index;
- field index;
- multifield begin/end offsets;
- constant-test direction/equality mode;
- join comparison operands.

The remaining missing mapping is **slot index -> slot name** and
**pattern index -> reconstructed LHS pattern**. Those come from the next two
stages: `deftemplate`/class slot recovery and the 295-node RETE graph.

## Next implementation target

1. Decode all 25 serialized `deftemplate` records and their slot chains.
2. Decode class slot descriptors required by the object-pattern accessors.
3. Give semantic slot names to type 29/31/47 accessors.
4. Recover the field meanings of the eight serialized integers in each of the
   295 join records from the matching `DefruleBinaryData` refresh/save code.
5. Emit a directed RETE graph with rule terminal joins and expression roots.
6. Walk each terminal join back to the root to construct source-like rule LHS.
7. Only after that, infer stable variable names; do not invent original source
   names that BSAVE did not preserve.
