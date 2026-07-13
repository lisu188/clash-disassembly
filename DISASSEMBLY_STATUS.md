# Clash — Disassembly Status

Honest completeness report for `clash.c`, the IDA Pro 9.0 / Hex-Rays 9.0 decompilation of the DOS/Watcom Clash binary.

## Verified DOS baseline

| Measure | Current value |
|---|---:|
| Function markers | 4,219 |
| Successfully decompiled functions | 4,218 / 4,219 (99.98%) |
| Failed function | `0xFDF26` only |
| Named function addresses | 886 / 4,219 (21.0%) |
| Distinct semantic base names | 872 |
| Deterministic address-suffixed emitted symbols | 14 |
| Named CLIPS-region functions | 704 / 2,015 (34.9%) |

The older 884-name figure was an emitted-symbol counting error. `tools/dos/dos_master_map.json` contains 886 requested address/name rows. Fourteen requested base names collide with an existing IDA symbol and are emitted deterministically as `<name>_<EA>`, leaving 872 distinct semantic base names while still naming all 886 addresses.

## Decompilation coverage

The current generated file preserves all 4,219 `//----- (ADDR)` markers and their address order. Hex-Rays 9.0 resolves the four earlier positive-stack-pointer failures. Applying the known `GetToken` prototype at `0xE1E30` resolves the three call-analysis regressions that depended on that function.

The sole remaining failed function is `0xFDF26`, a coroutine/jump-table dispatcher. A separate generated summary `#error` is metadata and is allowed; no second function failure is allowed.

## Naming evidence

Every accepted name must trace to one of these sources:

1. registered CLIPS function ground truth;
2. direct CLIPS error-id or unique-string evidence;
3. an existing embedded label;
4. independently confirmed CLIPS alignment;
5. independently confirmed clash95 cross-build transfer.

The master-map precedence and fail-closed behavior are implemented by `tools/dos/build_master_map.py`. Alignment and cross-build rows may only fill unnamed addresses. They cannot replace existing rows.

## Batch history reconciliation

- **Batch 259:** mission-04 completion and associated repository history. It did not alter the DOS name map.
- **Batch 260:** IDA 9 regeneration with 886 master-map rows, 872 semantic base names, 14 deterministic suffix collisions, 4,219 preserved markers, and one failed function at `0xFDF26`.
- **Batch 261:** deterministic clash95-to-DOS proposal, calibration, review, master-map, and regeneration tooling. No transfer was promoted because the repository lacks a fresh clash95 feature export and completed independent reviews.

The preliminary Batch 261 scan reported 17 bijective literal pairs and 10 pairs passing the DOS three-basic-block gate. These numbers are leads, not accepted mappings.

## Reproducible regeneration

The current pipeline is documented in `tools/dos/README.md` and `tools/dos/CONTINUATION_GUIDE.md`:

1. copy `C:\Clash\clash.i64` and `C:\Clash\clash95.i64` to temporary databases;
2. export deterministic features from both copies;
3. generate unique-literal proposals and a 40-pair CLIPS calibration set;
4. independently review all calibration and game candidates;
5. require complete calibration with at least 95% confirmation;
6. rebuild and check the master map;
7. seed a fresh DOS copy with the `GetToken` fix;
8. regenerate to scratch;
9. verify markers, failed-function set, name round-tripping, prior-name preservation, exact name count, and collision invariants.

`clash.c` may be replaced only after every regeneration check passes. Batch 261 intentionally leaves both `tools/dos/dos_master_map.json` and `clash.c` unchanged.

## Binary regions

See `MODULES.md` for the region and module map. The embedded CLIPS engine occupies 2,015 of 4,219 functions. The clash95 transfer search is deliberately restricted to DOS game/game-engine functions before `0x88370`; the confirmed CLIPS module region is used only for calibration.

## Out of scope for this batch

Mission 05 routing, `CSS_Init`, SDL runtime behavior, gameplay logic, save formats, runtime APIs, and recovered structures are unchanged. `RECOVERED_STRUCTURES.json` must remain byte-for-byte outside the Batch 261 change set.
