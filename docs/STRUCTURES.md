# Structures And Data Recovery

This project promotes structures, unit types, stats, and table semantics only
when implementation evidence supports them.

## Canonical Metadata

- `RECOVERED_STRUCTURES.json` - structured offsets, records, globals, and table
  evidence.
- `UNIT_TYPES_AND_STATS.json` - recovered unit roster, categories, stats, and
  relationships.
- [docs/archive/UNIT_TYPES_AND_STATS_REPORT.md](archive/UNIT_TYPES_AND_STATS_REPORT.md)
  - human-readable report backing the unit/stat JSON.
- [docs/archive/STRUCT_RECOVERY_NOTES.md](archive/STRUCT_RECOVERY_NOTES.md) -
  historical structure recovery notes.

Validate JSON metadata with:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
```

## Promotion Rules

- Prefer `clash95.asm`, `clash95.c`, `clash95.map`, and `clash95.exe` over
  external terminology.
- Use fixed offsets, repeated stride math, table xrefs, switch dispatch, strings,
  and caller neighborhoods as evidence.
- Mark ambiguous findings explicitly and keep them out of stable enums/structs
  until corroborated.
- Do not rename or restructure only because a guessed abstraction looks cleaner.
- Keep route/runtime validation close to any structure change that affects
  gameplay, save/load, rendering, input, or mission logic.

## Related Docs

- [docs/REVERSE_ENGINEERING.md](REVERSE_ENGINEERING.md) for source-of-truth and
  naming policy.
- [docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md](archive/REVERSE_ENGINEERING_RENAME_LOG.md)
  for confirmed rename/history entries.
- [docs/archive/COMPILATION_PROGRESS.md](archive/COMPILATION_PROGRESS.md) for
  batch validation and route evidence.
