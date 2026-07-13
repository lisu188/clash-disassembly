# DOS Rename Log

Focused append-only log for DOS master-map and clash95 cross-build naming. The large repository-wide rename log remains preserved unchanged.

## Baseline entering Batch 261

- Master-map rows / named addresses: 886.
- Distinct semantic base names: 872.
- Deterministic address-suffixed emitted symbols: 14.
- CLIPS-region named functions: 704 / 2,015.
- Failed function: `0xFDF26` only.

## Accepted mappings

No Batch 261 clash95 transfer was accepted.

## Deferred mappings

All preliminary cross-build leads are deferred. The initial scan reported 17 bijective unique-literal pairs and 10 pairs passing the DOS three-basic-block gate, but the repository does not contain the fresh clash95 feature export and independent calibration/game reviews required to publish candidate addresses or names.

Deferred rows must remain in `dos_crossbuild_review.json` after a real matcher run. `REJECT`, `UNCERTAIN`, missing review, incomplete review evidence, failed calibration, existing-address conflict, and name collision all prevent promotion.

## Evidence required for a future accepted row

Each accepted row must record:

- DOS address;
- clash95 address;
- collision-free semantic name;
- high or medium clash95 confidence;
- one or more unique shared literals;
- distinctive constants;
- branch, switch, loop, edge, and back-edge agreement;
- callee and data-reference agreement;
- complete literal-context explanation;
- independent reviewer verdict and reason;
- `source: "clash95-transfer"`.

Transferred confidence may equal but never exceed the clash95 confidence.

## Protected prior names

Registered CLIPS ground truth has highest precedence. Direct CLIPS error-id and unique-string evidence follows. Existing embedded labels follow direct evidence. Confirmed alignment and transfer rows can only fill unnamed addresses. A later regeneration must retain every prior named function and keep the baseline 14 suffix collisions unchanged.
