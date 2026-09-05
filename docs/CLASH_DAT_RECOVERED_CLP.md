# Unified `CLASH_recovered.clp`

## Purpose

`tools/generate_clash_recovered_constraints.py` is the current source-projection
generator for the retail `CLASH.DAT` CLIPS 6.00 BSAVE image. It combines the
independently recovered construct, object, RETE, message-handler, slot-facet, and
expression evidence into one normalized CLIPS program.

The generator consumes only the checked-in retail binary and evidence-backed
parsers used by CI. Generated `.clp` output is never treated as a new source of
truth.

```sh
python3 tools/generate_clash_recovered_constraints.py CLASH.DAT \
  --clp /tmp/CLASH_recovered.clp \
  --manifest /tmp/CLASH_recovered_manifest.json
python3 tools/check_clash_recovered_clp.py
```

`tools/generate_clash_recovered_clp.py` remains the older, less-semantic scaffold
generator. New recovery work should target the constraint-aware generator above.

## What is combined

The generated file contains:

- 6 recovered `defglobal` values;
- 7 recovered `deffunction` bodies;
- 7 game `defclass` constructs with direct inheritance;
- all 23 serialized game slot descriptors rendered with recovered slot/multislot
  form, defaults, storage, access, propagation, source, pattern-match,
  visibility, create-accessor, and override-message facets;
- all 69 recovered `defmessage-handler` constructs;
- all 95 BSAVE rule/disjunct records;
- all 425 recovered LHS condition occurrences in RETE source order;
- `not` conditions recovered from join flags;
- translated alpha/join tests where compiled accessors are unambiguous;
- recovered RHS action expression trees.

The rule records remain one-for-one with the binary image. CLIPS can serialize
multiple disjunct records with the same source rule name. The first record keeps
the recovered name and later records receive deterministic suffixes such as
`__disjunct2`; the manifest records every synthetic rename.

## Defclass slots

Slot facets are recovered by `tools/clash_dat_slot_facets.py`. For example the
source projection now has the full normalized shape:

```clips
(slot x
  (default 0)
  (storage local)
  (access read-write)
  (propagation inherit)
  (source exclusive)
  (pattern-match reactive)
  (visibility private)
  (create-accessor NONE)
  (override-message DEFAULT)
)
```

The exact facet values come from the compact CLIPS BSAVE slot flag word and the
serialized default/override fields. See `CLASH_DAT_SLOT_FACETS.md`.

The retail image contains zero serialized constraint records, so original
`type`, allowed-value, `range`, and `cardinality` source restrictions are not in
`CLASH.DAT` and are deliberately not invented.

## Message handlers

All 69 serialized handlers are rendered as `defmessage-handler` constructs with
recovered class, message name, handler type, arity, local-variable count, and
action expression root. Direct slot operations are restored as source forms such
as:

```clips
?self:x
(bind ?self:x <value>)
```

Parameter spellings remain stable synthetic names because BSAVE preserves
positions/arity, not the original identifier text. See
`CLASH_DAT_MESSAGE_HANDLERS.md`.

## Synthetic pattern variables

Original rule pattern-variable spellings are not stored by BSAVE. The generator
uses deterministic names describing recovered roles.

For ordered facts:

```clips
?f3 <- (swiatynia $?f3_fields)
```

For object patterns:

```clips
?o2 <- (object (is-a oddzial) (x ?o2_x) (y ?o2_y))
```

Negative patterns do not export an address binding.

## Compiled matcher constraints

A growing subset of alpha/join primitive expressions is emitted as real CLIPS
`(test ...)` conditions. This includes fact field accessors and selected named
object slot comparisons/constants.

Operations that are still ambiguous remain explicit comments:

```clips
;;; unresolved compiled-test (...): ...
```

The manifest tracks `compiled_test_count`, `translated_test_count`, and
`unresolved_test_count`; CI requires translated + unresolved to equal the exact
compiled count.

## Validation contract

`tools/check_clash_recovered_clp.py` is run by CI and locks, among other things:

- CLIPS binary version `V6.00`;
- 95 `defrule` constructs and 425 LHS condition occurrences;
- 6 globals and 7 deffunctions;
- 7 recovered game classes and 23 recovered slot descriptors;
- all normalized slot facets and the zero-constraint boundary;
- 69 recovered message handlers;
- unique generated rule/disjunct names;
- preservation of known RHS calls such as `Buduj-Zamek`;
- exact accounting for translated/unresolved compiled matcher tests;
- balanced source-level parentheses outside comments and strings.

## Evidence policy

`CLASH_recovered.clp` is generated output. The authoritative evidence remains:

1. `CLASH.DAT`;
2. exact BSAVE record parsers;
3. decoded expression/RETE/class/slot/handler IR;
4. recovered Win95 CLIPS loader/evaluator behavior;
5. CI contracts over the retail image.

Do not manually edit generated source and use that edit as evidence of the
original AI logic. Improvements belong in the decoder/generator and must remain
reproducible from `CLASH.DAT`.
