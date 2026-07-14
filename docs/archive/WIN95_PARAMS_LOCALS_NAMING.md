# Win95 parameter / local naming campaign

Companion to `win95_locals_rename_accum.jsonl` and `win95_globals_rename_accum.jsonl`.
Records how the recovered Win95 sources (`clash95.c` aggregator + `src/**/*.inc.c`)
were driven from machine-generated identifiers toward evidence-backed, human-readable
names, and — honestly — what remains and why.

## Scope

Text-based renaming on the split fragments (there is no DOS track; it was deleted).
Function names and file-scope globals were already recovered in earlier work; this
campaign targeted **positional parameters (`a1`, `a2`, …)** and **generated locals
(`v1`, `v37`, …, plus `i`/`result`/`Symbol` decompiler placeholders)**, plus the
last tail of machine globals.

## Tooling

- `tools/naming_audit.py` — reproducible census of opaque/generated identifiers
  (functions, globals by class, `aN`/`vN` occurrences); `--json` for machine diff.
- `tools/apply_local_renames.py` — **function-scoped** renamer. `a1`/`v37` are
  per-function, so it renames only within one function's byte range, token-aware
  (skips strings/comments so Hex-Rays `// reg@n` anchors survive). Hardened mid-
  campaign to **drop a proposed name that already exists as a distinct identifier
  in the same function** (prevents `redeclared as different kind of symbol` breaks
  when a proposal collides with a local like `result`).
- `tools/apply_renames.py` — file/global-scope renamer (auto-suffixes collisions).
- Provenance ledgers (`docs/archive/win95_{locals,globals}_rename_accum.jsonl`) —
  one row per accepted rename with `{old, new, confidence, evidence}`.

Every batch was proposed and **adversarially verified by fresh-context agents**
(proposer ≠ skeptic), then applied, then gated: `ninja -C build` must stay green
and the opt-in unit harness must stay within its (nondeterministic) baseline band.

## What the old names still tell you

Original identifiers are preserved as searchable anchors: Hex-Rays emits
`// ADDR: variable 'v37' is possibly undefined` and `// reg@n` trailing comments
that name the register/spill, and every rename is in the JSONL ledgers keyed by the
old name. Nothing is lost; grep for the old `vN` in comments or the ledger.

## Globals: reduced to zero (all classes)

| class | start | end |
|---|---|---|
| opaque functions (`sub_`) | 0 | 0 |
| `dword_`/`word_`/`byte_`/`off_`/`unk_`/… | 832 + 2 | **0** |
| `loc_` code-address labels | 103 | **0** |
| `unknown_libname_*` (opaque function names) | 8 | **0** |

Highlights of the tail cleared this campaign:
- **87 `loc_` labels → `Rules_Host<English>`** CLIPS host functions, recovered from
  the Polish rule-vocabulary name each label is registered under via
  `Rules_RegisterHostFunction` / `DefineFunction2` (Polish string preserved at every
  call site; e.g. `loc_45279F` → `Rules_HostDigTreasure` from `"kop_skarb"`).
- 12 `loc_` audio-mixer dispatch labels → `Audio_*Dispatch` (matching their
  already-named `g_Audio_*DispatchBase` alias pointers); `loc_48672B` → `CRT_FreeTlsIndex`.
- 8 `unknown_libname_*` → `atoi_`, `Mem_SetAllocFlag`, `Mem_SetOutOfMemoryHandler`,
  four CLIPS `Set*` setters paired with their getters, and the WCIsvList vtable pair.
- Last two `dword_` → `g_CSS_InitializedFlag`, `g_App_CommandModeRFlag` (write-once
  WinMain flags, asm-confirmed single xref).

## Parameters / locals: named where determinable

Occurrence counts (from `naming_audit.py`):

| identifier | campaign start | after round 5 |
|---|---|---|
| positional params `aN` | ~37,600 | **13,628** |
| generated locals `vN` | ~85,000 | **26,240** |

**16,750 identifier renames across 3,768 functions** are recorded in the local
ledger (2,977 inferred, 407 behaviour-confirmed, 384 conservative-mechanical).

Rounds (each = propose + adversarial-verify workflow → collision-guarded apply →
build/test gate → commit):

1. **Game fragments** (world-map/units/buildings/battle/building-ui/savegame) — 2,079.
2. **Non-game fragments** (CLIPS engine, media/audio, render, platform, runtime),
   giant files range-split — ~9,700 across 2,113 functions.
3. **Small fragments** (bootstrap/utilities/lexer) — 69.
4. **`190_clips_methods`** (defgeneric/defmethod object system) — 586.
5. **Round 4** — every fragment's remaining dense ranges — 3,428 across 952 functions.
6. **Round 5** — one dedicated high-effort agent per each of the 72 largest remaining
   functions — ~1,000 (incl. the 196-variable AI battle scorer
   `UnitBattle_ScoreAiActionGridForUnit`).

CLIPS code uses upstream CLIPS 6.0 parameter names where matched (`theInstance`,
`theDefclass`, `readSource`, `theToken`, `ppForm`, bsave/bload record fields). Game
code uses the recovered record layout as evidence (unit record `+852`=type, `+854`=side,
`+856`=row, `+858`=col; track-step byte packing; sprite/sound table strides).

## What remains, and why it is the floor

After five rounds the residual `aN`/`vN` are **not** un-attempted — every function was
covered and agents were instructed to *omit any identifier they could not justify*:

- **~7,700 of the 13,628 `aN`** are parameter names in **forward-declaration
  prototypes** in `clash95_prelude.inc.c`. These are cosmetic (C ignores declaration
  parameter names); the authoritative names live on the definitions. *(A deterministic
  propagation of definition names onto prototypes is available in tooling.)*
- **955 distinct locals are Hex-Rays `'possibly undefined'`** decompiler artifacts.
- The rest are register-spill intermediates and single-use temporaries spread thin
  across ~1,650 functions (a handful each), where no role is determinable from usage.

Structures: `RECOVERED_STRUCTURES.json` — **0 unnamed / offset-only fields**.

## Verification

Behaviour-neutrality was confirmed by comparing the opt-in unit harness to its
baseline after each major batch. The harness is **nondeterministic** (game-state /
ordering dependent): repeated runs of the *same* binary span ~997–1005 passed /
546–554 crashed / 25 failed. All rename batches landed inside that band — renames are
pure token substitution and cannot change behaviour once the build is green.

**Fresh-context accuracy audit.** Independent adversarial reviewers (no memory of the
proposing runs) sampled 43 renamed functions across game / CLIPS / render+runtime and
checked every name against actual usage (struct offsets, API argument positions, RLE
semantics, CLIPS record layouts). The sample was overwhelmingly accurate; the only
defects were **reversed name pairs**, all corrected:
- `savedCol`/`savedRow` in `UnitBattle_EstimateDamageScoreAgainstUnit` and
  `UnitBattle_MoveShootingUnit` (the unit-record base is `g_MapData+852`, so `+4`=row,
  `+6`=col — the saves were labelled backwards; symmetric save/restore, so harmless).
- `minRestrictions`/`maxRestrictions` in `Method_FindInsertionIndex` and
  `Method_CompareRestrictionOrder` (the `-1` unlimited sentinel belongs to the MAX
  bound `methodSlot[4]`; equal in the non-wildcard path, so harmless).

No misleading or over-specific names survived; un-named leftover `vN` were not counted
(partial coverage is expected). The correcting commit is `b7ce44c`.
