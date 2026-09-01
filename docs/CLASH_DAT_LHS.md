# `CLASH.DAT` class, RETE, and LHS recovery

## Current recovery level

The retail `CLASH.DAT` strategic-AI image is no longer limited to RHS/deffunction
recovery. The compiled CLIPS 6.00 pattern networks now expose the source-order
shape of every rule LHS.

Recovered and regression-checked:

- 95 `defrule` records;
- 295 typed `bsaveJoinNode` records;
- 64 fact-pattern nodes;
- 20 object alpha records;
- 14 object-pattern nodes;
- all 295 joins mapped to their RHS fact/object pattern;
- 24 `defclass` records;
- 17 object slot-name records;
- 23 class slot descriptors;
- 69 message-handler records;
- 425 rule-condition occurrences when each terminal rule is walked back to the
  RETE root.

The source-like renderer is `tools/analyze_clash_dat_lhs.py`. It intentionally
uses `...` for source fields and original variable names that the BSAVE image did
not preserve.

## Reproduction

```sh
python3 tools/check_clash_dat_classes.py
python3 tools/check_clash_dat_rete.py
python3 tools/check_clash_dat_lhs.py

python3 tools/analyze_clash_dat_lhs.py CLASH.DAT \
  --json /tmp/clash-lhs.json \
  --clp /tmp/clash-lhs.clp

python3 tools/analyze_clash_dat_lhs.py CLASH.DAT \
  --rule podejdz_do_swiatyni_najblizej_init \
  --rule postaw_zamek
```

## `defclass` binary layout

The recovered runtime proves the `defclass` BSAVE data sizes used by the retail
image. `Class_BsaveWriteData` writes:

- 12 bytes per module header;
- 76 bytes per class;
- 4 bytes per class-link entry;
- 16 bytes per slot-name record;
- 24 bytes per class slot descriptor;
- 4 bytes per instance-template slot link;
- 4 bytes per slot-name-map entry;
- 28 bytes per message-handler record;
- 4 bytes per handler dispatch-table entry.

The retail count header is:

```text
modules                 1
classes                24
class links           137
slot names             17
slot descriptors       23
instance slot links    43
slot-name map entries  80
message handlers       69
class-id table size    24
```

These sizes consume the complete 5,908-byte `defclass` data section exactly.

## Game classes

The final seven of the 24 CLIPS classes are game-specific:

```text
class id 17  clash-class
class id 18  gracz
class id 19  budowla
class id 20  straznica
class id 21  twierdza
class id 22  zamek
class id 23  oddzial
```

The other classes are CLIPS system classes such as `OBJECT`, `PRIMITIVE`,
`NUMBER`, `LEXEME`, `INSTANCE`, and `USER`.

## Recovered slot names

The 17 serialized slot-name records give the exact global object slot IDs used
by compiled object matcher primitives:

| Slot ID | Name |
| ---: | --- |
| 2 | `id` |
| 3 | `nazwa_gracza` |
| 4 | `religia` |
| 5 | `pieniadze` |
| 6 | `WN` |
| 7 | `gracz` |
| 8 | `x` |
| 9 | `y` |
| 10 | `moc` |
| 11 | `szpital` |
| 12 | `szkola` |
| 13 | `warsztat` |
| 14 | `kuznia` |
| 15 | `koszary` |
| 16 | `tiredness` |
| 17 | `PA` |
| 18 | `jednostki` |

Slot ID 0 occurs in object alpha bitmaps but is a CLIPS system slot and is kept
as `system-slot#0` rather than assigned a guessed source spelling.

Declared local slots are recovered as:

```text
gracz:
  id nazwa_gracza religia pieniadze WN

budowla:
  id gracz x y moc

twierdza:
  szpital szkola warsztat kuznia koszary

oddzial:
  id gracz x y tiredness PA moc jednostki
```

`straznica` and `zamek` declare no additional local slots in the binary; their
usable slots come from their superclass chain.

## Class and slot bitmaps

CLIPS object pattern class/slot restrictions use the same compact bitmap form:

```text
uint16 max_id
uint8  bits[(max_id / 8) + 1]
```

Therefore a retail class bitmap such as:

```text
17 00 00 00 80
```

means `max_id=23`, with class bit 23 set: `oddzial`.

The three important class restrictions seen in the object alpha network are:

```text
bitmap 185 -> oddzial
bitmap 101 -> zamek
bitmap 160 -> straznica | twierdza | zamek
```

The same decoding resolves slot restrictions. For example bitmap 99 selects:

```text
system-slot#0, id, gracz, x, y
```

This turns object patterns from opaque bitmap IDs into game-domain conditions.

## RETE -> rule LHS

`tools/clash_dat_rete.py` maps every join to the fact/object alpha node attached
to its right input. Walking `lastLevel` from each rule terminal back to the root
recovers source-order condition sequences and `patternIsNegated` recovers `not`.

Example shape for `podejdz_do_swiatyni_najblizej_init`:

```text
(gracz ...)
(object (is-a oddzial) ...)
(swiatynia ...)
(not (budowanie ...))
(not (najblizej ...))
(not (oddz ...))
```

The object condition is further known to test the slots:

```text
system-slot#0, id, gracz, x, y, PA
```

Example shape for `postaw_zamek`:

```text
(gracz ...)
(ilosc-zamkow ...)
(zamek_place ...)
(budowanie ...)
(maszeruj ...)
(object (is-a oddzial) ...)
```

For every condition the LHS report also retains:

- join index and depth;
- fact-pattern/object-pattern index;
- alpha-network test expression(s);
- join-network test expression;
- negation flag;
- object class restriction;
- object slot bitmap restriction.

## Semantic expression rendering

`tools/clash_dat_lhs.py` renders network tests using the primitive decoders from
`tools/clash_dat_primitives.py`. In particular, object accessor type 47 now uses
recovered slot names:

```text
object[pN].x
object[pN].gracz
object[pN].PA
```

rather than numeric `?prim47_*` forms. Fact accessors remain positional where
appropriate because the strategic `deftemplate` records are implied/ordered
facts and do not contain named slots.

## Remaining gap to a recompilable `CLASH.CLP`

The reconstructed LHS is semantically much closer to source but is deliberately
not advertised as byte-for-byte original CLIPS text. The remaining work is:

1. unify repeated fact/object accessors into stable synthetic variables;
2. turn alpha/join primitive expressions into ordinary CLIPS field constraints
   and `(test ...)` forms;
3. decode the 70 six-byte `HANDLER_GET`/`HANDLER_PUT` references;
4. combine the recovered LHS with the already reconstructed RHS/deffunction
   renderer in one generated source file;
5. load/compile that normalized source in a compatible CLIPS runtime and compare
   the resulting RETE topology and gameplay rule-firing traces.

Original source variable names should not be invented. A synthetic stable name
is preferable whenever BSAVE contains only the compiled binding location.
