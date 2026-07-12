# DOS `clash.c` naming pipeline

Tooling to name the DOS/Watcom build (`clash.c`, 4,219 functions) and regenerate
it from IDA Pro 9.0. Unlike the `clash95` side (which text-patches `sub_XXXXXX`
via `tools/apply_sub_renames.py`), the DOS build is named **by integer address in
the IDA database, then re-exported** — the `apply_sub_renames.py` regex assumes
6-digit hex names, but DOS addresses are mostly 5 digits and would be corrupted.

## Assets (outside the repo)
- `C:\Clash\clash.i64` — the IDA database `clash.c` was decompiled from. Work on a
  **copy**, never the original.
- `C:\Program Files\IDA Professional 9.0\idat.exe` — headless decompiler
  (`idat -A -S"script.py args" -Llog db.i64`).
- `C:\Clash\ref\clips\{624,630}\` — CLIPS reference source (see `docs/DOS_CLIPS_PIN.md`).

## Name sources → one master `{ea → name}` map
1. **`dos_existing_names.json`** (470) — the names already in `clash.c` (recovered
   this project from embedded evidence: CLIPS `DefineFunction2` tables, function-entry
   debug traces, TPalette hooks). Extracted by parsing `//----- (ADDR)` markers.
2. **`dos_clips_anchors.json`** (130, high-confidence) — CLIPS functions uniquely
   identified by their `PrintErrorID(module,id)` fingerprint, matched to CLIPS 6.24
   source function names (`Env` prefix stripped for the pre-environment DOS era).
   Produced by `clips_xref.py`. This is the **Stage-1 definitive-anchor** subset; the
   full campaign extends it via per-module sequence-alignment + call-graph propagation
   with adversarial verification (see `docs/DOS_CLIPS_PIN.md` and the project plan).
3. (later) cross-build transfer from `clash95` via binary diffing (`clash95.i64` exists).

## Scripts
- `extract_errids.py` — DOS `(module,id)` PrintErrorID inventory from `clash.c`.
- `clips_xref.py` — version-pin scoring + `(module,id)` → CLIPS-function anchoring.
- `../ida/seed_names.py` — apply a `{ea,name}` map into an i64 copy (`set_name`,
  collision-suffix with hex address, saves DB).
- `../ida/export_clash_c.py` — `decompile_many` the whole DB to one C file
  (reproduces the `//----- (ADDR)` marker format).

Paths in the scripts point at the out-of-repo assets above — adjust for your machine.

## Regeneration (validated 2026-07-12)
IDA-9 `decompile_many` reproduces the exact marker format and **all 4,219 original
function addresses (zero set difference)** with strictly better types. It fixes the
4 "positive sp value" decompile failures; 3 "call analysis failed" regressions all
trace to one callee (`sub_E1E30`) whose prototype must be set, leaving a **single
residual** `#error` (`0xFDF26`, a genuine coroutine/jump-table dispatcher). Order:
seed all names + fix `sub_E1E30` in the i64 copy → regenerate once → verify (4,219
markers, ≤1 `#error`, names round-trip) → replace `clash.c` in one commit.
