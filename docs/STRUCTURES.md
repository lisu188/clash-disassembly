# Structures And Data Recovery

## Canonical Metadata

- `RECOVERED_STRUCTURES.json` - recovered structures, fields, offsets, and
  confidence notes.
- `UNIT_TYPES_AND_STATS.json` - unit type/stat metadata and relationship notes.
- `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md` - human-readable unit/stat
  recovery report.
- `docs/archive/STRUCT_RECOVERY_NOTES.md` - historical structure-recovery notes.

Validate JSON metadata with:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
```

## Policy

- Treat `clash95.asm`, `clash95.map`, the manifest-backed sources under
  `src/recovered/split/`, and the original binary as higher authority than
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
