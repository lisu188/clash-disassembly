# Structures And Data Recovery

## Canonical Metadata

- `RECOVERED_STRUCTURES.json` - recovered structures, fields, offsets, and
  confidence notes.
- `UNIT_TYPES_AND_STATS.json` - unit type/stat metadata and relationship notes.
- `data/unit_type_runtime_metadata.json` - original bytes for all 40 physical
  88-byte unit metadata records and exact localized names/resource/audio stems.
  A native pointer companion preserves original font bytes and shared name
  triplets; `UnitTypeLocalizedNameTable` pins the original 12-byte layout. Regenerate
  their C storage with `python3 tools/gen_unit_type_runtime_metadata.py --write`.
- `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md` - human-readable unit/stat
  recovery report.
- `docs/archive/STRUCT_RECOVERY_NOTES.md` - historical structure-recovery notes.

Validate JSON metadata with:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
python3 tools/gen_unit_type_runtime_metadata.py --check
python3 tools/gen_recovered_structs.py --check
```

## Policy

The current tactical slot recovery names `BattleUnitEntry.fatigue` at +10 and
`morale` at +11, preserving its 31-byte size. The generated catalog has 21
structures and 181 size/offset assertions. Typed consumers also fix five
stance-related reads that previously scaled a byte offset through a short
pointer. Evidence and remaining opaque spans are recorded in
`artifacts/structure-recovery/tactical-validation-20260905/` and the unit/stat
report.

- Treat `clash95.asm`, `clash95.map`, the manifest-backed recovered subsystem
  sources directly under `src/`, and the original binary as higher authority than
  external terminology.
- Promote a field or structure name only when multiple callsites or direct data
  flow support it.
- Preserve byte-offset macros until a typed structure is safer than the raw
  offset.
- Record ambiguous candidates explicitly instead of hiding uncertainty behind a
  confident name.
- Keep JSON and report updates scoped to the semantic evidence recovered in the
  same batch.

## Protected Data

Do not delete or rewrite metadata, route scripts, or historical reports unless a
file is clearly duplicated, stale, or generated and the replacement evidence is
documented. If unsure, keep the file and add a deferred cleanup note.
