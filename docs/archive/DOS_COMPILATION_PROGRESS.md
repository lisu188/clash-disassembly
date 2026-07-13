# DOS Compilation and Regeneration Progress

This focused log supplements the preserved repository-wide `COMPILATION_PROGRESS.md` history without rewriting its 9,000-line runtime record.

## Batch 259 — Mission-04 completion history reconciliation

- Scope: retained clash95 mission-04 route evidence and documentation.
- DOS `clash.c` impact: none.
- Runtime milestone: unchanged by the DOS naming work.
- Mission 05 and `CSS_Init`: outside this batch.

## Batch 260 — IDA 9 DOS regeneration

- Seeded a disposable DOS IDA database from 886 master-map rows.
- Applied the known `GetToken` prototype correction at `0xE1E30`.
- Regenerated `clash.c` with IDA Pro 9.0 / Hex-Rays 9.0.
- Preserved all 4,219 function markers.
- Reduced the failed-function set to `0xFDF26` only.
- Verified 886 named addresses, 872 distinct semantic base names, and 14 deterministic address-suffixed emitted symbols.
- Corrected the stale 884-name documentation.

## Batch 261 — Cross-build transfer and reproducibility tooling

### Implemented

- Parameterized all three IDA helpers.
- Added deterministic basic-block, edge, back-edge, immediate-constant, call, data-reference, and literal feature export.
- Added unique-shared-literal candidate generation with pair collapsing and bijection rejection.
- Added DOS address-range, existing-name, basic-block, clash95-confidence, and collision gates.
- Added 40-pair evenly distributed CLIPS calibration with complete-review and 95% confirmation requirements.
- Added independent game-review fields for constants, branch/loop shape, callees, data accesses, and literal context.
- Repaired master-map source precedence and added semantic `--check` mode.
- Added regeneration verification for markers, failures, name round-tripping, prior-name retention, exact name count, and collisions.
- Added deterministic proposal, calibration, confirmation, and review JSON artifacts.

### Transfer result

No transfer was accepted. The repository lacks a fresh clash95 feature export and completed independent reviews. The preliminary 17 bijective pairs and 10 DOS three-basic-block survivors remain unverified leads. `dos_master_map.json` and `clash.c` are unchanged.

### Validation performed

```text
python3 -m unittest discover -s tests/dos -p 'test_*.py' -v
20 tests passed

python3 -m py_compile tools/dos/*.py tests/dos/*.py
passed
```

The branch diff confirms that `clash.c`, `tools/dos/dos_master_map.json`, `RECOVERED_STRUCTURES.json`, and `UNIT_TYPES_AND_STATS.json` are not modified.

### Validation not performed in the connector environment

- IDA Pro feature export, seeding, or regeneration against the private `.i64` files.
- WSL `clash95_bootstrap` build/link.
- Default CTest suite in the LF-preserving WSL checkout.
- Real-input UI probe.

Those checks remain mandatory before a later batch can promote transfers or replace `clash.c`. Runtime milestones are recorded as unchanged.
