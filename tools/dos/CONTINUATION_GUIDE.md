# DOS `clash.c` naming campaign — continuation guide

Read `tools/dos/README.md`, `docs/DOS_CLIPS_PIN.md`, and `docs/archive/DOS_CLIPS_CROSSREF.md` first. This file is the active runbook.

## Non-negotiable rule

Never invent a name. A DOS rename requires registered ground truth, direct CLIPS evidence, independently confirmed alignment, or independently confirmed cross-build equivalence. When evidence is incomplete, retain `sub_<EA>`.

## Current baseline

- 886 named addresses in `tools/dos/dos_master_map.json`.
- 872 distinct semantic base names.
- 14 deterministic emitted `_EA` collision symbols.
- 4,219 marker addresses.
- One failed function at `0xFDF26`.
- No Batch 261 clash95 transfer has been accepted.

## 1. Create disposable IDA copies

Never open the original databases for write access.

```powershell
Copy-Item C:\Clash\clash.i64 C:\Clash\work\clash_crossbuild.i64
Copy-Item C:\Clash\clash95.i64 C:\Clash\work\clash95_crossbuild.i64
```

## 2. Export both feature sets

Run IDA Pro 9.0 headlessly against the temporary copies:

```text
idat.exe -A -S"tools/ida/export_features.py C:\Clash\work\dos_features.json" -L"C:\Clash\work\dos_features.log" C:\Clash\work\clash_crossbuild.i64
idat.exe -A -S"tools/ida/export_features.py C:\Clash\work\clash95_features.json" -L"C:\Clash\work\clash95_features.log" C:\Clash\work\clash95_crossbuild.i64
```

Confirm both reports contain function names, sizes, basic-block counts, calls, data references, and literals. Do not continue with a stale or partial export.

## 3. Generate proposals and calibration rows

```powershell
python tools\dos\crossbuild_match.py `
  --dos-features C:\Clash\work\dos_features.json `
  --clash95-features C:\Clash\work\clash95_features.json `
  --dos-c clash.c `
  --clash95-c clash95.c `
  --master-map tools\dos\dos_master_map.json `
  --rename-index docs\archive\SUB_RENAME_INDEX.md `
  --output-dir C:\Clash\work\crossbuild
```

The first run must leave confirmed rows empty because no independent review file was supplied. Inspect every rejected/filter reason; do not bypass uniqueness, bijection, confidence, address-range, basic-block, existing-name, or collision gates.

## 4. Independently review calibration

Review all selected CLIPS pairs, up to 40 evenly distributed rows. For each pair compare both bodies and CLIPS 6.24 evidence. Record `CONFIRM`, `REJECT`, or `UNCERTAIN` plus a concrete reason. Missing, rejected, and uncertain rows are failures. At least 95% of the complete set must confirm.

Re-run the matcher with `--reviews <review.json>`. Stop if `tools/dos/dos_crossbuild_calibration.json` reports `passed: false`.

## 5. Independently review every game candidate

For each proposal compare:

- distinctive constants;
- branch, switch, and loop shape;
- called functions;
- data accesses;
- complete literal context.

A shared literal only proposes the pair. It never confirms it. Transferred confidence cannot exceed the clash95 confidence. Record all rejected and uncertain candidates, not only confirmations.

## 6. Rebuild and check the master map

Only `tools/dos/dos_crossbuild_confirmed.json` may feed transfer rows into the map.

```powershell
python tools\dos\build_master_map.py
python tools\dos\build_master_map.py --check
```

Required properties:

- registered ground truth wins;
- direct CLIPS evidence wins over stale existing labels;
- existing labels cannot be overwritten by alignment or transfer;
- transfer rows use `source: "clash95-transfer"`;
- no new semantic name collision exists;
- baseline remains 886 rows when no transfer is confirmed.

## 7. Seed and regenerate from a fresh DOS copy

```text
idat.exe -A -S"tools/ida/seed_names.py tools/dos/dos_master_map.json C:\Clash\work\seed_report.json --fix-dos-gettoken" -L"C:\Clash\work\seed.log" C:\Clash\work\clash_regen.i64
idat.exe -A -S"tools/ida/export_clash_c.py C:\Clash\work\clash_regen.c C:\Clash\work\export_report.json" -L"C:\Clash\work\export.log" C:\Clash\work\clash_regen.i64
```

Then run:

```powershell
python tools\dos\verify_regeneration.py clash.c C:\Clash\work\clash_regen.c tools\dos\dos_master_map.json C:\Clash\work\seed_report.json C:\Clash\work\verify_report.json --confirmed-transfers tools\dos\dos_crossbuild_confirmed.json
```

Do not replace `clash.c` unless the report is fully green. The separate Hex-Rays summary `#error` is allowed, but the only failed function must be `0xFDF26`.

## 8. Static and WSL validation

```bash
python3 -m unittest discover -s tests/dos -p 'test_*.py' -v
python3 -m py_compile tools/dos/*.py tests/dos/*.py
python3 -m json.tool RECOVERED_STRUCTURES.json >/dev/null
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/dev/null
python3 tests/check_markdown_links.py
git diff --check
cmake --build build --target clash95_bootstrap -j2
ctest --test-dir build --output-on-failure
```

The DOS naming batch changes no runtime behavior. Mission 05, `CSS_Init`, gameplay, SDL APIs, save formats, and recovered structures remain outside scope. Record retained runtime milestones as unchanged.
