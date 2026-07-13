# DOS `clash.c` naming campaign — continuation guide

Written for whoever (any model tier) picks this up. Follow it literally; every step
has a concrete command and a check. The **plan of record** is
`~/.claude/plans/plan-disassembly-next-steps-virtual-moon.md`; this file is the
operational how-to. Read `docs/DOS_CLIPS_PIN.md` and `tools/dos/README.md` first.

## The one rule that matters
**Never invent a name.** Every name applied to a DOS function must trace to evidence:
a registered `DefineFunction2` string (ground truth), a string literal unique to one
CLIPS source function AND one DOS function, or an adversarially-CONFIRMED alignment.
When unsure, leave it `sub_XXXXX`. A wrong name is worse than no name.

## Where things are
- Repo: `C:\Users\andrz\git\clash-disassembly` (GitHub `lisu188/clash-disassembly`, branch `main`).
  Push after every committed step (`git push origin main`).
- DOS IDA database (READ-ONLY original): `C:\Clash\clash.i64`. **Always work on a copy**
  `scratchpad/clash_work.i64`. Headless IDA: `"/c/Program Files/IDA Professional 9.0/idat.exe" -A -S"script.py" -L"log" clash_work.i64`.
- CLIPS 6.24 source (the pin): `C:\Clash\ref\clips\624\CLIPSSrc\CLIPSSrc\*.c` (169 files).
- clash95 database for cross-build transfer: `C:\Clash\clash95.i64` (48 MB, IDA-9).
- Master name map (the accumulator): `tools/dos/dos_master_map.json`, rows
  `{ea:"0x...", name, confidence, source, evidence}`. **This is the single source of truth
  for what gets applied.** Everything below adds rows to it.

## Data model / precedence (already implemented in `build_master_map.py`)
Precedence when two sources name the same ea:
`registered ground-truth` (immutable, `dos_registered_groundtruth.json`, 394 names)
> `clips-string` / `clips-errid` (evidence; override stale hand-labels; DROP if they
contradict ground truth) > `clips-align` (CONFIRMED only) > `existing` hand-labels.
`Env`-prefix is stripped for DOS (pre-environment binary) — keep `clips_source_name` as evidence.

## Status at last checkpoint (commit f828623, then alignment WIP)
- 782 names committed (existing 465, clips-errid 129, clips-string 188). 30% of CLIPS region.
- 109 alignment proposals generated (`clips_align_proposals.json`); pilot 10 modules
  verified = **20/20 CONFIRM, 0 reject**; remaining 24 modules (84 proposals) verifying.

## Pipeline to finish (in order)

### Step 1 — Collect all CONFIRMED alignment names into the master map
Both verify workflows return `{confirmed:[{ea,proposed_name,...}], rejected, uncertain, corrections}`.
Their task-output JSON files are under `scratchpad/` (task ids in the transcript). For each
CONFIRM verdict, add a row `{ea, name:proposed_name, confidence:"high", source:"clips-align",
evidence:reason}`. For any `corrected_name`, use that instead. Discard REJECT/UNCERTAIN.
Re-run `python tools/dos/build_master_map.py` (extend it to also read the confirmed-align file).
Check: master-map count grew; no ea has two names; no name collides (the builder logs conflicts).

### Step 2 — (optional, more yield) more alignment rounds
`align_segments.py` only proposed on count-matched segments. To go further: handle
unequal segments with Needleman-Wunsch using signals {unique-shared-string, callee-name
agreement (using names already in the master map), size/bb ratio from `dos_features.json`}.
ALWAYS route new proposals through the same adversarial verify workflow
(`verify-clips-alignment` script) before adding to the map. Target: 1,000+ CLIPS names.

### Step 3 — Cross-build transfer (game-logic region, NOT CLIPS)
clash95 has 3,031 named funcs (`docs/archive/SUB_RENAME_INDEX.md`, `sub_<ADDR>|Name|Conf|Area|Evidence`).
Match by **shared unique string literal**: a literal referenced by exactly one function in
regenerated `clash.c` AND one in `clash95.c` → candidate. Join clash95 side via SUB_RENAME_INDEX.
Gates: ≥3 basic blocks both sides (`dos_features.json` for DOS side); 1:1 only; only transfer
clash95 names with high/medium confidence (skip the 325 `low`); CLIPS-region agreement ≥95%
as a self-check. Verify adversarially. Tag `source:"clash95-transfer"`. Diaphora on the two
i64s is the structural fallback (needs user download approval; Ghidra VT does NOT work — DOS4GW
LE loader is too weak).

### Step 4 — Seed the database and regenerate clash.c (ONE regen)
1. Copy: `cp C:\Clash\clash.i64 scratchpad/clash_work.i64`.
2. `seed_names.py` (in `tools/ida/`) applies the master map via `set_name(ea, name, SN_FORCE)`,
   logging collisions. **Also fix `sub_E1E30`**: set its prototype so the 3 "call analysis failed"
   regressions resolve (see `export_clash_c.py` notes / baseline log — it is the callee whose
   missing type breaks callers 0x90D2A, 0xAC29C, 0xD1914). Save DB.
3. `export_clash_c.py` runs `ida_hexrays.decompile_many` over the whole DB → scratch `.c`.
4. GATE before replacing `clash.c` (all must hold): exactly **4,219** `//----- (` markers;
   marker address set **identical** to current `clash.c` (compare with the marker-diff snippet
   in this repo's history / `clips_match.py` has the parser); **≤1** `#error` (only 0xFDF26
   allowed); every master-map name present in the output (grep a sample). Only then copy over `clash.c`.

### Step 5 — Verify, commit, document, push
- `python scratchpad/final_verify.sh`-style checks; confirm clash95 WSL build still green
  (`wsl -e bash -lc 'cd /mnt/c/Users/andrz/git/clash-disassembly && ninja -C build'`) — clash.c is
  NOT in that build so it must be unaffected.
- ONE commit "Regenerate clash.c from IDA 9.0 with recovered names (NNNN named, N% )".
  Large diff is expected and fine (old file in git history). Update `DISASSEMBLY_STATUS.md`
  (decompilation now 99.98%, new naming %), `MODULES.md`, add `docs/archive/DOS_CLIPS_CROSSREF.md`
  generated from the master map. `git push origin main`.

## Verifying a single proposed name by hand (the core skill)
1. DOS body: in `clash.c`, find `//----- (00<EA>) ---` (EA = 8 hex digits, upper), read to next marker.
2. CLIPS body: in `C:\Clash\ref\clips\624\CLIPSSrc\CLIPSSrc\<file>.c`, find `globle`/`static ... <Name>(`.
3. CONFIRM only if distinctive structure agrees: magic constants, loop/branch shape, switch arms,
   referenced string literals, and callee pattern. Position/order alone is NOT proof.

## Guardrails
- Don't touch the 300 registered names or the 129 errid anchors (they're validated).
- Don't text-patch `clash.c` for names — name the i64 and regenerate (5-digit-addr regex in
  `tools/apply_sub_renames.py` would corrupt DOS names; it's for clash95 only).
- clash95 runtime work (mission-04) is a SEPARATE effort (`AGENTS.md`), needs the retail CD at
  `/mnt/c/clash`; do not conflate with DOS naming.
- Commit + push frequently (user preference). Keep clash95 build green.
