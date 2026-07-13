# DOS CLIPS and clash95 Cross-Reference

This document records the reproducible naming state for the DOS `clash.c` artifact and the evidence boundary for cross-build name transfer.

## Baseline accounting

| Item | Count |
|---|---:|
| DOS function markers | 4,219 |
| DOS master-map rows / named addresses | 886 |
| Distinct semantic base names | 872 |
| Deterministic IDA address-suffixed collisions | 14 |
| Successfully decompiled functions | 4,218 |
| Failed functions | 1 (`0xFDF26`) |
| CLIPS-region functions | 2,015 |
| Named CLIPS-region functions | 704 |

The master map is address-oriented: each of its 886 rows requests one semantic name for one function address. IDA symbol uniqueness is a separate concern. Fourteen requested names collide with another database symbol and are therefore emitted as `<base_name>_<EA>`. Those deterministic suffixes explain the difference between 886 named addresses and 872 distinct base names. They are not additional semantic names.

## Source precedence

The reproducible map builder applies evidence in this order:

1. registered CLIPS ground truth;
2. direct CLIPS error-id and unique-string evidence;
3. existing embedded labels;
4. confirmed CLIPS alignment and confirmed clash95 transfer.

Direct evidence may correct a stale embedded label unless it contradicts registered ground truth. Alignment and transfer rows may only fill addresses not already present. A transfer is rejected when its base name already exists, so Batch 261 cannot increase the 14 baseline suffix collisions.

## Address boundaries

- Game and game-engine transfer search: `0x12C6E..0x8836F`.
- Confirmed CLIPS start used as the transfer boundary: `0x88370`.
- First exact CLIPS module anchor in the module map: `0x89860`.
- End of the embedded CLIPS region: `0xEB580`.

The gap between `0x88370` and the first exact module anchor is treated conservatively as CLIPS-side calibration territory, not as a game-transfer target.

## Batch history

### Batch 259 — mission-04 completion

The missing history entry corresponds to the completed mission-04 Hopenberg route and its retained runtime evidence. It changed clash95 runtime recovery and documentation, not the DOS name map. Batch 261 does not reopen mission 04 or advance mission 05.

### Batch 260 — IDA 9 regeneration

A temporary copy of the DOS database was seeded from the audited 886-row master map, the `GetToken` prototype was corrected at `0xE1E30`, and `clash.c` was regenerated with IDA Pro 9.0 / Hex-Rays 9.0. Verification established:

- all 4,219 marker addresses preserved;
- exactly one failed function at `0xFDF26`;
- 886 named addresses;
- 872 distinct base names;
- 14 deterministic suffixed symbols;
- no prior named function lost.

The stale 884-name description counted emitted spellings incorrectly and is superseded.

### Batch 261 — DOS cross-build transfer tooling

Batch 261 adds deterministic feature export, unique-literal pair generation, bijection checking, clash95 confidence and basic-block gates, CLIPS calibration, independent candidate review, master-map conflict rejection, and full regeneration verification.

A preliminary scan reported:

| Stage | Leads |
|---|---:|
| Bijective shared-literal pairs | 17 |
| Pairs passing the DOS three-basic-block gate | 10 |
| Independently confirmed transfers | 0 |

The repository does not contain the required fresh `clash95.i64` feature export or completed independent calibration/game reviews. Consequently calibration is incomplete, `dos_crossbuild_confirmed.json` is empty, and neither `dos_master_map.json` nor `clash.c` is changed.

## Candidate generation contract

A literal may propose a pair only when:

- its decoded length is at least five characters;
- exactly one DOS function references it;
- exactly one clash95 function references it;
- all literals for the two functions collapse to the same bijective pair;
- the DOS function lies before `0x88370`, remains `sub_<EA>`, and is absent from the master map;
- both functions have at least three basic blocks;
- the clash95 rename has high or medium confidence.

Multiple literals strengthen the proposal but do not confirm equivalence.

## Calibration contract

The matcher selects 40 evenly distributed eligible CLIPS pairs, or every eligible pair when fewer than 40 exist. An independent reviewer compares both function bodies and CLIPS 6.24 evidence. Missing, `REJECT`, and `UNCERTAIN` verdicts are failures. Calibration passes only when all selected rows are reviewed and at least 95% are confirmed.

No game transfer may be emitted before calibration passes.

## Game-candidate review contract

Every game candidate needs an independent review of:

- distinctive constants;
- branch, switch, and loop shape;
- callees;
- data accesses;
- the literal's complete use context.

Literal proximity alone is insufficient. Accepted confidence cannot exceed the clash95 confidence. Rejected and uncertain rows remain in `dos_crossbuild_review.json`.

## Generated artifacts

| File | Purpose | Batch 261 state |
|---|---|---|
| `tools/dos/dos_crossbuild_proposals.json` | Deterministic gated proposals | Deferred; preliminary counts only |
| `tools/dos/dos_crossbuild_calibration.json` | Selected CLIPS pairs and review summary | Incomplete, failed closed |
| `tools/dos/dos_crossbuild_confirmed.json` | Rows eligible for master-map merge | Empty |
| `tools/dos/dos_crossbuild_review.json` | Filtered, rejected, uncertain, and pending evidence | Deferred reason recorded |

## Regeneration invariants

`verify_regeneration.py` rejects a generated file unless:

- it has exactly 4,219 markers in the baseline order;
- the only failed function is `0xFDF26`;
- every master-map address emits its requested name or documented suffix;
- no prior named function becomes anonymous;
- the named count is exactly `886 + confirmed transfers`;
- the seed report has exactly 14 baseline collisions;
- no confirmed transfer creates a collision.

A separate Hex-Rays summary `#error` is allowed. A second failed function is not.

## Accepted and deferred mappings

### Accepted clash95 transfers

None in Batch 261.

### Deferred candidates

All preliminary candidates remain deferred pending fresh feature exports, complete CLIPS calibration, and independent body-level game review. The checked-in artifacts intentionally do not guess their names.

## Scope protection

This batch changes naming/reproducibility tooling and documentation only. Mission 05, `CSS_Init`, SDL runtime behavior, gameplay code, runtime APIs, save formats, unit semantics, and recovered structure metadata are unchanged.
