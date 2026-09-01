# CLASH.DAT defclass slot facets and defaults

The retail `CLASH.DAT` defclass section contains 23 serialized CLIPS 6.00 slot
descriptors. `tools/clash_dat_slot_facets.py` turns their compact BSAVE flags,
default expression/value roots, override-message symbols, and constraint indices
into source-level slot declarations for `CLASH_recovered.clp`.

## 24-byte slot descriptor

The existing defclass parser recovers each serialized descriptor as:

```text
+00 uint32 flags
+04 int32  definingClassIndex
+08 int32  slotNameRecordIndex
+0C int32  defaultExpressionIndex
+10 int32  constraintIndex
+14 int32  overrideMessageSymbolIndex
```

The recovered `Class_BsaveWriteHandlerRecords` and
`Class_BloadRefreshHandlerRecord` routines prove how the live CLIPS
`slotDescriptor` flags are compacted for BSAVE.

## BSAVE flag mapping

Only the semantic low 12 bits are consumed by the loader:

| BSAVE bit | Recovered facet |
|---:|---|
| 0 | `storage shared` when set, otherwise `local` |
| 1 | `multislot` when set, otherwise `slot` |
| 2 | `source composite` when set, otherwise `exclusive` |
| 3 | `propagation no-inherit` when set, otherwise `inherit` |
| 4 | `access read-only` |
| 5 | `access initialize-only` |
| 6 | serialized default is dynamic (`default-dynamic`) |
| 7 | `default ?NONE` / no default |
| 8 | `pattern-match reactive` when set, otherwise `non-reactive` |
| 9 | `visibility public` when set, otherwise `private` |
| 10 | create read accessor |
| 11 | create write accessor |

Bits 10 and 11 combine into `create-accessor NONE`, `read`, `write`, or
`read-write`.

Two live parser flags are intentionally not serialized as flags:

- `defaultSpecified` — the final default/no-default state and serialized default
  value already contain the runtime-relevant information;
- `overrideMessageSpecified` — the actual override-message symbol is stored in
  the descriptor.

Therefore the recovered source is semantically normalized rather than a claim
about the exact original pretty-print form.

## Defaults

For each slot, the BSAVE descriptor points to the expression array used to rebuild
its runtime default.

The generator emits:

```clips
(default <serialized-static-value>)
(default-dynamic <serialized-expression>)
(default ?NONE)
```

as appropriate. Static derived defaults cannot be distinguished from an
explicit static default after BSAVE has materialized the value; emitting the
materialized value is source-equivalent for the recovered runtime state.

If an unusual image had neither a serialized value nor `noDefault`, the recovery
layer uses `(default ?DERIVE)` rather than inventing a value.

## Other facets

Every recovered game slot now emits explicit normalized facets:

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

`override-message DEFAULT` is emitted when the descriptor's override symbol is
the slot-name table's ordinary `put-<slot>` message. A different recovered
symbol is emitted by name.

## Constraint boundary

Immediately after the 5237 packed expressions, CLIPS stores a 32-bit constraint
record count followed by 24-byte constraint records. The recovered constraint
loader confirms this record shape and the usual type/restriction/range/cardinality
fields.

For the retail `CLASH.DAT`, the count is **zero** and all 23 slot descriptors have
`constraintIndex == -1`.

This is meaningful rather than a parser gap: CLIPS BSAVE does not write constraint
records when dynamic constraint checking is disabled at save time. Consequently,
original source facets such as:

- `type`;
- `allowed-values` / typed allowed-value restrictions;
- `range`;
- `cardinality`;

are not present in this binary image and cannot be recovered honestly from
`CLASH.DAT` alone. The generated source therefore omits them instead of guessing.
This matches the bloaded image, which also has no serialized slot constraints.

## Validation

`tools/check_clash_dat_slot_facets.py` locks the retail-image contract:

- exactly 23 serialized slot descriptors;
- every descriptor is owned by exactly one recovered class slot range;
- the known slot lists for `gracz`, `budowla`, `twierdza`, and `oddzial` are
  preserved;
- all slot flags decode into the twelve known semantic facets;
- every default root is either valid, `?NONE`, or conservatively `?DERIVE`;
- all 23 constraint indices are `-1` because the image contains zero constraint
  records;
- all rendered slots contain storage/access/propagation/source/pattern-match/
  visibility/create-accessor/override-message facets.

The same report is embedded in `CLASH_recovered_manifest.json` by
`tools/generate_clash_recovered_constraints.py`.
