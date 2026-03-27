# AGENTS

## 1. Mission
- Reverse-engineer this decompiled Clash-like codebase.
- Primary goal: recover concrete unit types, categories, and stats.
- Secondary goal: recover relationships between unit types and their stats.

## 2. Scope
- **In scope:** enums, registries, factory/spawn logic, stat structs/tables, config loaders, scaling/targeting/serialization logic when it exposes types or stats.
- **Out of scope:** unrelated refactors, speculative rewrites, cosmetic cleanup, behavior changes.

## 3. Evidence order
1. Function bodies and direct data flow.
2. Struct layouts, lookup tables, arrays, enums, switch dispatch.
3. Call graph and shared state interactions.
4. Strings/config names.
5. External Clash terminology only as secondary confirmation.

## 4. Confidence rules
- **High:** multiple independent signals align.
- **Medium:** strongly suggested but not fully proven.
- **Low:** ambiguous/speculative—never present as fact.
- Mark every ambiguous finding explicitly as ambiguous.

## 5. Autonomous workflow
- Continue until canceled, safely exhausted, or blocked by tooling/repo limits.
- Revisit earlier conclusions when new evidence surfaces.
- Move automatically to the next evidence-rich cluster.

## 6. Focus order
1. Unit type registries and enums.
2. Spawn/factory logic.
3. Stat structs and balance tables.
4. Stat calculations and scaling logic.
5. Queen-specific code only when it informs generic hero/unit taxonomy or stat semantics.

## 7. Required outputs
- Maintain `UNIT_TYPES_AND_STATS_REPORT.md`.
- Maintain `UNIT_TYPES_AND_STATS.json`.
- Print checkpoint summaries after each analysis batch.
- Print a final summary covering recovered unit types, stats, relationships, and ambiguities.

## 8. Do-not rules
- Do not invent semantics absent code evidence.
- Do not let external terminology override implementation proof.
- Do not drift into unrelated systems unless they directly aid unit/type/stat recovery.
