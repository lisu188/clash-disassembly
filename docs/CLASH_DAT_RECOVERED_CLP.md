# Unified `CLASH_recovered.clp`

## Purpose

`tools/generate_clash_recovered_clp.py` combines the independently recovered
parts of the retail `CLASH.DAT` CLIPS 6.00 BSAVE image into one normalized,
source-like program.

The generator consumes only the checked-in retail binary and the evidence-backed
parsers already used by CI. It does not treat a hand-edited `.clp` file as a new
source of truth.

```sh
python3 tools/generate_clash_recovered_clp.py CLASH.DAT \
  --clp /tmp/CLASH_recovered.clp \
  --manifest /tmp/CLASH_recovered_manifest.json
python3 tools/check_clash_recovered_clp.py
```

## What is combined

The generated file contains, in one artifact:

- the six recovered `defglobal` values;
- the seven recovered `deffunction` bodies;
- recovered game `defclass` names, direct inheritance, and declared slot names;
- all 95 BSAVE rule/disjunct records;
- all 425 recovered LHS condition occurrences in RETE source order;
- `not` conditions recovered from join flags;
- the RHS action expression trees already reconstructed by
  `tools/decompile_clash_dat.py`;
- comments containing the decoded alpha-network and join-network tests for every
  condition where those compiled tests exist.

The rule records are deliberately kept one-for-one with the binary image. CLIPS
can serialize multiple disjunct records with the same source rule name. A source
file cannot safely contain duplicate construct names, so the first record keeps
the recovered name and later records receive deterministic suffixes such as
`__disjunct2`. The manifest records every such synthetic rename.

## Synthetic variables

Original pattern-variable spellings are not stored by BSAVE. The generator
therefore uses deterministic names that describe their recovered role rather
than pretending to know the original source text.

For ordered facts:

```clips
?f3 <- (swiatynia $?f3_fields)
```

For object patterns:

```clips
?o2 <- (object (is-a oddzial) (x ?o2_x) (y ?o2_y))
```

Negative patterns are rendered without exporting an address binding:

```clips
(not (budowanie $?f4_fields))
```

These names are stable across runs as long as the BSAVE rule condition order is
unchanged. `CLASH_recovered_manifest.json` records the binding chosen for every
condition.

## Recompilation status

The current artifact is a **recompilation-oriented source scaffold**, not yet a
semantic round-trip replacement for `CLASH.DAT`.

The important remaining boundary is the translation of compiled alpha/join
primitive expressions back into source constraints. Those expressions are now
decoded and readable, but the generator keeps them as evidence comments instead
of inventing source syntax. This avoids silently changing AI behavior.

For example, a condition may be emitted as a broad pattern followed by comments
such as:

```clips
?f2 <- (gracz $?f2_fields)
  ;;; recovered alpha-test: ...
  ;;; recovered join-test: ...
```

The next recovery stage should translate those accessor expressions to actual
CLIPS constraints using the synthetic bindings. For ordered facts that means
mapping recovered field offsets to operations over `$?fN_fields`; for object
patterns it means substituting the recovered named slot bindings such as
`?oN_x`, `?oN_gracz`, and `?oN_PA`.

## Validation contract

`tools/check_clash_recovered_clp.py` is run by CI and currently locks:

- CLIPS binary version `V6.00`;
- 95 generated `defrule` constructs;
- 425 LHS condition occurrences;
- 6 `defglobal` values and 7 `deffunction` bodies;
- 7 recovered game `defclass` constructs;
- unique generated rule names even when BSAVE contains several disjunct records
  with the same original name;
- preservation of known recovered RHS calls such as `Buduj-Zamek`;
- absence of the old `LHS unavailable` placeholder;
- balanced source-level parentheses outside comments and strings.

## Evidence policy

`CLASH_recovered.clp` is generated output. The authoritative evidence remains:

1. `CLASH.DAT`;
2. exact BSAVE record parsers;
3. decoded expression/RETE/class IR;
4. recovered Win95 CLIPS loader/evaluator behavior;
5. CI contracts over the retail image.

Do not manually edit a generated recovered program and then use the edit as
proof of the original AI logic. Improvements belong in the decoder/generator and
must remain reproducible from `CLASH.DAT`.
