# DOS `clash.c` naming pipeline

This directory contains the evidence-gated naming and regeneration pipeline for the DOS/Watcom build. DOS names are applied to a temporary IDA database copy by integer address and `clash.c` is regenerated from Hex-Rays; the generated file is never text-patched.

## Verified baseline

- 4,219 function markers.
- 886 master-map rows.
- 872 distinct semantic base names.
- 14 deterministic address-suffixed IDA collision names.
- One failed decompilation, function `0xFDF26`.
- 704 of 2,015 functions named in the embedded CLIPS region.

A map row is a requested semantic name for one address. When IDA cannot emit that name uniquely, `tools/ida/seed_names.py` records the deterministic `<name>_<EA>` symbol. This is why 886 named addresses correspond to 872 distinct base names and 14 suffixed emitted symbols.

## External assets

Work only on temporary copies of:

- `C:\Clash\clash.i64`
- `C:\Clash\clash95.i64`

IDA Pro 9.0 headless executable:

- `C:\Program Files\IDA Professional 9.0\idat.exe`

CLIPS reference source remains pinned as documented in `docs/DOS_CLIPS_PIN.md`.

## IDA helpers

```text
tools/ida/export_features.py <output.json>
tools/ida/seed_names.py <map.json> <report.json> --fix-dos-gettoken
tools/ida/export_clash_c.py <output.c> <report.json>
```

`tools/ida/export_features.py` records function names, sizes, basic-block/edge/back-edge counts, immediate constants, callers, callees, data references, and decoded literals. `tools/ida/seed_names.py` applies the master map, reports every collision, and optionally applies the known `GetToken` prototype at `0xE1E30`. `tools/ida/export_clash_c.py` writes the generated C file and a machine-readable marker/decompilation report.

## Master-map precedence

`tools/dos/build_master_map.py` uses this order:

1. registered CLIPS ground truth;
2. direct CLIPS error-id and unique-string evidence;
3. existing embedded labels;
4. independently confirmed CLIPS alignment and clash95 transfer rows.

Alignment and transfer rows only fill unnamed addresses. A clash95 transfer is rejected if its semantic name already exists. `python tools/dos/build_master_map.py --check` verifies that the checked-in generated map and reports match the source artifacts.

## Cross-build transfer

`tools/dos/crossbuild_match.py` consumes feature exports for both databases, the generated C files, the DOS master map, `docs/archive/SUB_RENAME_INDEX.md`, and an independent review JSON. It deterministically produces:

- `tools/dos/dos_crossbuild_proposals.json`
- `tools/dos/dos_crossbuild_calibration.json`
- `tools/dos/dos_crossbuild_confirmed.json`
- `tools/dos/dos_crossbuild_review.json`

A candidate must use literals of at least five characters that are unique to exactly one function in each build. Multiple literals may corroborate one pair, but all mappings must remain bijective. Game candidates must be in `0x12C6E..0x8836F`, remain `sub_<EA>`, be absent from the master map, have at least three basic blocks in both builds, and map to a high- or medium-confidence clash95 name.

Calibration selects 40 evenly distributed eligible CLIPS pairs, or all pairs when fewer exist. Every selected pair must receive an independent verdict; `REJECT`, `UNCERTAIN`, and missing reviews are failures. Transfers remain blocked unless at least 95% confirm equivalence. A game candidate then needs a separate review covering distinctive constants, branch/loop shape, callees, data accesses, and literal context. Literal proximity alone is never sufficient.

The checked-in Batch 261 artifacts are intentionally empty: the repository does not contain a fresh clash95 feature export or completed independent reviews. The preliminary scan reported 17 bijective pairs and 10 that passed the DOS three-basic-block gate, but no name was promoted.

## Regeneration gate

After calibration and candidate review pass:

1. copy both original `.i64` files to scratch locations;
2. export features from the copies;
3. run the matcher and inspect all review artifacts;
4. run `tools/dos/build_master_map.py --check`, then rebuild the map only when confirmed rows exist;
5. seed a fresh DOS copy with `--fix-dos-gettoken`;
6. regenerate into scratch;
7. run `tools/dos/verify_regeneration.py`.

The verifier requires all 4,219 marker addresses in the same order, exactly one failed function at `0xFDF26`, complete master-map round-tripping including documented suffixes, no lost prior name, exactly `886 + confirmed transfers` named functions, exactly 14 existing collisions, and no new transfer collision. Replace repository `clash.c` only when every check passes.

## Tests

```bash
python3 -m unittest discover -s tests/dos -p 'test_*.py' -v
python3 -m py_compile tools/dos/*.py tests/dos/*.py
```

The tests cover multiline IDA signatures, literal uniqueness, pair collapsing, bijection conflicts, confidence/basic-block gates, deterministic calibration selection, master-map precedence and overwrite rejection, name-collision rejection, and regeneration marker/error parsing.
