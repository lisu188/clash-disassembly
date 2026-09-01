# `strateg\\clash.dat` CLIPS BSAVE format and strategic-AI recovery

## Status

`CLASH.DAT` is not a Clash savegame or a bespoke game-data container. It is a
CLIPS 6.00 binary image produced by the CLIPS `bsave` machinery and loaded by
the embedded rules engine with `bload`.

Confidence: **high**. The identification is supported independently by:

- the file prefix `01 02 03 04 "CLIPS\\0" "V6.00\\0"`;
- recovered runtime state containing `g_Rules_BsaveVersionID = "V6.00"` and the
  `strateg\\clash.dat` path;
- recovered `Rules_Bload*`/`Rules_Bsave*` code in `src/clips/` matching the
  serialized tables parsed from the retail file;
- successful structure-by-structure parsing through both CLIPS binary
  separators to the end of the file.

The current parser/decompiler is `tools/decompile_clash_dat.py`. Its readable
output is committed as `data/strategic_ai/CLASH_decompiled.clp`; a lossless-ish
JSON IR can be regenerated locally and is intentionally not committed because
it is generated data (~0.7 MB for this image).

## Reproduction

```sh
python3 tools/decompile_clash_dat.py CLASH.DAT \
  --clp data/strategic_ai/CLASH_decompiled.clp \
  --json /tmp/CLASH_decompiled_ir.json
```

For the checked-in `CLASH.DAT` the parser reports:

```text
version=V6.00
functions=122
symbols=316
expressions=5237
rules=95
joins=295
deftemplates=25
deffunctions=7
defglobals=6
```

## File prefix and atom tables

All integers below are little-endian unless stated otherwise.

| Order | Encoding | Retail value | Meaning |
| --- | --- | ---: | --- |
| 1 | 10 bytes | `01 02 03 04 43 4c 49 50 53 00` | CLIPS binary prefix |
| 2 | NUL string | `V6.00` | binary format/version ID |
| 3 | `u32 count`, `u32 bytes`, NUL strings | 122 / 1692 bytes | functions required by the image |
| 4 | `u32 count`, `u32 bytes`, NUL strings | 316 | symbol table |
| 5 | `u32 count`, `double[count]` | 9 | floating-point atom table |
| 6 | `u32 count`, `i32[count]` | 48 | integer atom table |
| 7 | `u32 count`, `u32 bytes`, sized blobs | 210 | bitmap table |
| 8 | `u32` | 5237 | packed expression count |

The bitmap encoding matches the recovered `Rules_BloadAtomTables` path: each
entry starts with one byte containing the blob length, followed by that many
bytes of payload.

## Binary-item storage headers

After the atom tables and expression count, the image contains 11 named storage
records. Each record is serialized as:

```text
char name[20]   // NUL-terminated inside the fixed-width field
u32  byte_count
u8   payload[byte_count]
```

Retail order and payload sizes:

| Item | Bytes |
| --- | ---: |
| `defrule` | 12 |
| `defmodule` | 8 |
| `object patterns` | 8 |
| `defclass` | 36 |
| `definstances` | 8 |
| `deftemplate` | 12 |
| `facts` | 4 |
| `defglobal` | 8 |
| `deffunctions` | 8 |
| `generic functions` | 20 |
| `deffacts` | 8 |

The storage header is followed by a 20-byte CLIPS binary separator and then the
packed expression array.

## Packed expressions

The retail image contains 5237 packed expression records, each exactly 14
bytes:

```c
struct BsaveExpression {
    uint16_t type;
    int32_t value;
    int32_t arg_list;
    int32_t next_arg;
};
```

This size and field behavior are directly corroborated by the recovered CLIPS
runtime:

- `Rules_BloadAllocExpressionArray` allocates `14 * expression_count` bytes;
- `Rules_BloadRefreshExpressions` refreshes 14-byte records;
- `Rules_RefreshExpressionEntry` interprets `value` according to `type` and
  converts `arg_list`/`next_arg` indices into pointers;
- `Rules_BsaveWriteExpression` writes the same index-based representation.

The most important decoded types for the current decompiler are:

| Type | Meaning in this image |
| ---: | --- |
| 0 | float atom |
| 1 | integer atom |
| 2 | symbol atom |
| 3 | string atom |
| 8 | instance-name symbol |
| 10 | registered function call |
| 12 | `deffunction` call |
| 13 | global-variable symbol form |
| 34 | fact-field expression helper |
| 35 | `deftemplate` reference |
| 57 | `defclass` reference |
| 60 | `defglobal` reference |
| 65/66 | compiled deffunction parameter access |
| 67/68 | compiled variable/bind access forms |

Other primitive expression types remain represented conservatively as
`?prim<type>_<value>` placeholders until their CLIPS primitive payload encoding
is recovered.

## Binary-item data records

After the expression table and the constraint block, the same 11 binary items
appear again with their concrete serialized records. Retail payload sizes are:

| Item | Bytes |
| --- | ---: |
| `defrule` | 13632 |
| `defmodule` | 20 |
| `object patterns` | 1008 |
| `defclass` | 5908 |
| `definstances` | 28 |
| `deftemplate` | 612 |
| `facts` | 2048 |
| `defglobal` | 108 |
| `deffunctions` | 236 |
| `generic functions` | 12 |
| `deffacts` | 28 |

A second 20-byte CLIPS separator terminates the binary image.

## Strategic AI recovered from the image

### Defglobals

The six global tuning values are recovered exactly from the expression table:

```clips
(defglobal
  ?*zasieg_dzialan* = 10
  ?*koszt_ruchu* = 8
  ?*odleglosc_waga* = 0
  ?*atak_zamku_waga* = 0.9
  ?*atak_oddzialu_waga* = 0.8
  ?*waga_komputer* = 0.5
)
```

These values are stronger evidence for strategic-AI behavior than earlier
string-only guesses because they are the actual constant-expression roots wired
into the serialized `defglobal` records.

### Deffunctions

Seven CLIPS deffunctions are present and their expression bodies can be
reconstructed from BSAVE:

| Name | Parameters |
| --- | ---: |
| `atakowanie_oddzialu` | 5 |
| `atakowanie_zamku` | 6 |
| `Licence_To_Buy_Kuznia` | 3 |
| `Licence_To_Buy_Warsztat` | 3 |
| `Licence_To_Buy_Koszary` | 3 |
| `Licence-Product` | 4 |
| `Procent` | 2 |

The generated CLP contains the recovered bodies. Parameter names are synthetic
(`?p1`, `?p2`, ...), because BSAVE preserves positional access rather than the
original source spelling.

### Defrules and RETE network

The image contains 95 `defrule` records and 295 join records. Rule metadata
including rule names, static salience, dynamic-salience expression roots, RHS
action roots, terminal join indices, and disjunct links is decoded.

The RHS expression trees are substantially recoverable. For example the
`postaw_zamek` rule has salience 991 and its actions include the diagnostic
`"Wykonuje sie regula postaw_zamek"`, three retracts, and a `Buduj-Zamek` call.

The original LHS text is **not** currently reconstructed. CLIPS BSAVE stores the
compiled pattern/join network rather than the pretty-printed source form, so the
remaining work is a RETE/object-pattern decompiler rather than a string
extraction task. Until that work is complete the generated file records the
terminal join and leaves the LHS explicitly unresolved.

## `PRIOR` target-weight table

`PRIOR` is a separate text configuration consumed by the recovered strategic
code, not part of the CLIPS BSAVE image:

```text
1 15.0    ;;; budowla
2 20.0    ;;; oddzial
3 10.0    ;;; skarb
4 10.0    ;;; swiatynia
```

The recovered reader opens `strateg\\prior`, reads each line with `fgets`, parses
`"%d %f"`, compares the requested target type with the parsed integer, and
returns the matching float. The default is `-1.0` if no matching entry is found.
Therefore the numeric values are confirmed target-type weights, not merely
comments inferred from the file names.

What still requires call-site analysis is the exact optimization direction and
how this base weight combines with distance, strength, and the CLIPS globals.
Do not describe a larger `PRIOR` value as universally "better" until the
selection function's arithmetic is fully recovered.

## Relationship to the recovered host API

`docs/AI_SCRIPTING_API.md` describes the native functions registered with CLIPS.
`CLASH.DAT` is the other side of that boundary: it contains the rules that call
those functions. Together they now expose both halves of the strategic-AI
interface:

```text
CLASH.DAT / CLIPS rules
        |
        | registered function calls
        v
Rules_Host* wrappers
        |
        v
recovered strategic/game engine
```

This also explains why strings such as `atakuj_oddzial`, `Buduj-Zamek`,
`maszeruj_do_swiatyni`, `kop_skarb`, `Znajdz_Najlepszy`, and the production/
economy helpers occur in the BSAVE function table: they are actual callable
symbols referenced by serialized expressions.

## Current limitations and next recovery target

High-confidence recovered data:

- BSAVE identification and section boundaries;
- atom tables and all 5237 expression records;
- rule/deffunction/defglobal names and expression roots;
- six global values;
- deffunction bodies with synthetic positional parameter names;
- rule RHS trees where primitive accessors are not required;
- rule salience and RETE terminal join indices;
- `PRIOR` parsing and its four type/weight entries.

Still incomplete:

- original `defrule` LHS syntax;
- original variable names for compiled pattern accesses;
- semantic decoding of all CLIPS primitive bitmap payloads;
- full `deftemplate` slot definitions and class/object-pattern constraints;
- reconstruction of the 295-join RETE network into canonical source patterns;
- proof of the exact target-selection formula combining `PRIOR` and other
  weights.

The next useful reverse-engineering batch is to decode `object patterns`,
`deftemplate`, and `defrule` join records together with primitive access bitmap
formats, then map terminal joins back into pattern chains. That should eliminate
most `?prim*` placeholders and recover a source-like LHS for the strategic AI.
