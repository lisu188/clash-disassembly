---
name: recover-unit-types-and-stats
description: Use this skill only when the task is to recover unit types, unit stats, or their relationships from decompiled C/C++ code. Do not use it for general refactoring.
---

- Focus exclusively on unit taxonomy/stat recovery in decompiled native code: enums, registries, factories/spawn logic, stat structs/tables, scaling/targeting/serialization paths.
- Let implementation evidence drive conclusions; treat external Clash terminology as secondary confirmation only.
- Log every confirmed or ambiguous finding in `docs/archive/UNIT_TYPES_AND_STATS_REPORT.md` and `UNIT_TYPES_AND_STATS.json`, keeping ambiguous entries clearly marked.
- Keep searching iteratively through evidence-rich clusters (type ids, tables, loaders, combat/stat math) until the task is canceled, safely exhausted, or blocked by tooling/repo limits.
