# Clash — Disassembly Status

Honest completeness report for `clash.c`, the Hex-Rays decompilation of the
**Clash** binary (a Polish turn-based strategy game; Watcom C++, ~1997).

## What "complete" means here

`clash.c` is a decompiler artifact. There are two independent axes of completeness:

1. **Decompilation coverage** — does every function have valid C?
2. **Analysis / naming** — is every function understood and named (not `sub_XXXX`)?

## 1. Decompilation coverage: 99.88% (4214 / 4219)

Hex-Rays produced a C body for every function **except 5**, which it could not
decompile. These remain as `#error` directives (and make the file uncompilable
as-is). They are the literal, irreducible gaps in the disassembly:

| Address | Failure reason | funcsize |
|---|---|---:|
| `0x179AE` (fn `0x17938`) | positive sp value has been found | 33 |
| `0x22388` (fn `0x22317`) | positive sp value has been found | 0 |
| `0x8F325` (fn `0x8F29E`) | positive sp value has been found | 0 |
| `0xFDFC3` (fn `0xFDF26`) | call analysis failed | 50 |
| `0x1208EB` (fn `0x1208EA`) | positive sp value has been found | 0 |

"Positive sp value" means Hex-Rays could not balance the stack (non-standard
stack manipulation / non-returning code / mis-identified function boundary);
"call analysis failed" is an indirect-call/jump-table it could not resolve
(`0xFE03E`, adjacent, is a bare `JUMPOUT` jump-table dispatch — a clue).

**These 5 cannot be fixed from `clash.c` alone.** Resolving them requires the
original binary + IDA/Hex-Rays: fix the stack-pointer delta or function bounds,
define the jump table, and re-decompile. They are inherent decompiler limits,
not missing analysis.

## 2. Naming / analysis: 468 / 4219 named (11.1%)

Up from 48 at the previous commit — **412 names recovered this session**, all
derived from evidence embedded in the binary (no guessing):

| Method | Names | Confidence |
|---|---:|---|
| Function-entry debug-log traces (`log(aName())` as first statement) | 15 | exact — original names |
| CLIPS `DefineFunction2` registration tables (`registerClipsCallback`, `sub_A58F0`) — the `actualName` argument is each handler's C name | 397 | exact — recovered from binary |

Examples of exact recovered names: `Building_NewTurn`, `Queen_NewTurn`,
`Battle_NewTurn`, `GodAnger`, `Port_GetSupply`, `Prisoner_SetInCastles`,
`UnitsCache_Clear`; plus 394 CLIPS handlers — the game's Polish AI predicates
(`swiatynia00` = temple, `jest_droga00` = is-road, `kop_skarb00` = dig-treasure,
`odleglosc_od_obiektu00` = distance-from-object) and CLIPS builtins
(`AgendaCommand`, `FactsCommand`, `AssertCommand`, …).

## Structure of the binary (see `MODULES.md`)

The single biggest finding: **CLIPS is ~48% of the binary.** Clash is a
comparatively thin game layer on top of NASA's [CLIPS](https://en.wikipedia.org/wiki/CLIPS)
expert-system engine, which drives the computer opponent via rules over Polish
game predicates.

| Region | Range | Funcs | Named-ability |
|---|---|---:|---|
| Watcom C/C++ runtime & startup | `010000`–`012C6E` | 81 | CRT — identifiable by signature |
| Game logic (25 `.cpp` modules) | `012C6E`–`0654D5` | 958 | manual RE; module-anchored |
| Game engine (gfx/sound/AI glue) | `0654D5`–`089860` | 695 | manual RE |
| CLIPS 6.x expert system (73 modules) | `089860`–`0EB580` | 2015 | matchable to CLIPS source |
| Trailing library / math / DPMI | `0EB580`–`1208EB` | 470 | CRT/library |

## Why 100% naming is not an automated result

The remaining 3751 `sub_XXXX` functions have **no name embedded in the binary**
(unlike the CLIPS handlers, whose names were stored as data). Naming them
requires one of:

- **CLIPS region (2015 funcs):** diff against a specific CLIPS 6.x release's
  source, function by function — semi-mechanical *with the exact source in hand*,
  but version-sensitive and error-prone; not reliably automatable here.
- **CRT/library (~550 funcs):** identify Watcom runtime routines by signature
  (`strlen`, `memcpy`, integer/FP helpers). A few dozen are high-confidence;
  most need FLIRT signatures.
- **Game code (~1650 funcs):** genuine manual reverse engineering — read the
  code, cross-reference strings and callers, infer behavior. No shortcut.

Fabricating names for these would actively mislead. This session deliberately
applied only names that are *recovered evidence*, and stopped there.

## Reproducible method (for continuing)

All analysis scripts live in the session scratchpad; the reusable core is a
function-map + string-table parser (`refe.py`) and a word-boundary batch
renamer (`apply.py`). To extend naming:

1. Find a new name→pointer association in the binary (registration table,
   vtable, self-referential error string).
2. Extract `sub_XXXX → Name` pairs; validate no collisions.
3. Apply with `\bsub_XXXX\b` word-boundary replacement across decl + def + calls.

Anchors and ranges in `MODULES.md` tell you which module any address belongs to.
