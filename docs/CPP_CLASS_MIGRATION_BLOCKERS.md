# UnitStack class-migration blockers

Track: Win95 reconstruction. Frontier: deciding whether the remaining UnitStack
behavior can move into classes without disguising a behavior repair. This is a
read-only evidence audit dated 2026-09-06; no production source, test, manifest,
baseline or campaign status is changed. See [CPP_CLASS_MIGRATION.md](CPP_CLASS_MIGRATION.md)
for the separate migration and validated four-method pilot.

## Decision

The four reported routines contain real reconstruction defects. Their original
machine code initializes the values that the C++ reconstruction reads as
indeterminate. CopyFromTemplate additionally substitutes a no-op compatibility
stub for two array-copy operations. These findings have **high confidence** from
matching current source, original instructions and callee contracts. They are
not limitations of the class extractor or evidence of undefined original game
behavior.

| Recovered identity | Original address | Behavior-bearing defect | Other reported value |
| --- | --- | --- | --- |
| `UnitStack_CopyFromTemplate` | `0x412D20` | Missing register-ABI array copies; wrong first destination and indeterminate second destination | Incoming inferred third argument is not an original input |
| `UnitStack_CalcMilitaryStrength` | `0x412BE0` | Indeterminate `v2` supplies the slot-array address | Original EDX holds the input stack across the count call |
| `UnitStack_NormalizePeasantCargo` | `0x4121D0` | Indeterminate `v8` replaces the cargo consolidation threshold | Final `j` and `v8` context arguments have no logical use in the traced callees, but evaluating indeterminate C++ arguments is still invalid |
| `UnitStack_RegroupWithOtherStackByHealth` | `0x4582B0` | Indeterminate `stack_index_reg` selects the first stack for the initial distance check | `v6` is passed to an explicitly unused parameter; its indeterminate evaluation still needs removal |

Do not declare the whole UnitStack family parity-ready by mechanically moving
these bodies. Separate assembly-backed repairs, focused behavioral fixtures and
relevant runtime evidence should precede their class-body parity gate. Preserve
the old evidence and identify intended behavior deltas explicitly; a new crash
allowlist or blanket baseline reset is not a repair. This bounded audit does not
certify every other UnitStack routine. It does not invalidate the independently
validated query pilot or prevent other coherent, reviewed families progressing.

## Evidence identity and interpretation

The reference commit is `6f7537268e784c538133b714e3ccb77cf54052e4`.
Current-source locations below refer to the migration worktree, not the old
unified source. The four private routines have no public name entry at their
addresses in `clash95.map`; their recovered names are not asserted to be original
public spellings. The corresponding `sub_...` labels and address markers in
`clash95.asm` establish identity. Its `__usercall` signatures are decompiler
annotations, which must be checked against instructions rather than treated as
authoritative C++ prototypes.

Public map corroboration: `Unit_GetSquadCount` is at segment-1 offset `0x21B80`
(`clash95.map:123`), `Rules_RetractArmyFact` at `0x51250` (line 192), and
`__wcpp_4_copy_array__` at `0x74A45` (line 370). Segment 1 starts at `0x401000`,
giving absolute addresses `0x422B80`, `0x452250` and `0x475A45` respectively.
The last helper is collapsed in the assembly listing, so its instructions and
descriptor bytes were also read directly from the installed original executable
with `objdump`; the original was not executed during this audit.

SHA-256 of read inputs (whole files at audit time; concurrent unrelated edits can
change later whole-file hashes):

| Input | SHA-256 |
| --- | --- |
| `clash95.asm` | `b298e8c85086f542ebc8b02c26904019aa8278d531cbf02a88d785170cbb4436` |
| `clash95.map` | `cd7975cb6ba8aad4505739a8d747891cb35a8cd67fb865e04d8786561af8ca1a` |
| Installed `/mnt/c/clash/clash95.exe` | `500055d77d03d514e8d3168506bd10f67cd8569bcc450604ff8192f46cdaf3ae` |
| `src/units/004115E0_00412BE0_units_002.cpp` | `2fc377eb7e0807c5a8b050bd9cf3496d76b537f4605eef4a0815869026bfbf97` |
| `src/units/00412C00_00414350_units_003.cpp` | `d0a72357c7d2e4748919bb67dca8d2ac0cfef3b1cd899ddbfe34772add14480e` |
| `src/units/00414390_00416750_units_004.cpp` | `af08700ad820eb987a116f103aba890827001476509fb96780cad50c32cb9834` |
| `src/strategic/00455740_004582B0_strategic_003.cpp` | `6b2f63c2d2dc0bbe6b54f0cf46e7125c8952d85aa7a30ea96312b2e22cceba06` |
| `src/strategic/00453110_00455720_strategic_002.cpp` | `e02c2c62bf730842439fe7e269b1843226ee2f532071dbb8d80346e6e3746e2e` |
| `src/strategic/004506B0_004530D0_strategic_001.cpp` | `ede3688f27e0431f2c0e9590c061e899e33ae5ec6e971d44c319470a43598b1b` |
| `src/strategic/00456706_00457789_strategic_008.cpp` | `fff36c2468b7b8e86a053d6ec152ebe1c7c836d2eb4da13e3bd681cf9975cbd3` |
| `src/compatibility/decomp_runtime_stubs.cpp` | `7915f5466a744ac56b0509a63c0731c0661a5eda113eb3f210bdbb72a826f74d` |

## CopyFromTemplate: two missing array copies

Current definition: `src/units/00412C00_00414350_units_003.cpp:88`,
`int UnitStack_CopyFromTemplate(int destStack, int srcStack, int a3)`.
Lines 98-102 call `_wcpp_4_copy_array__(a3)`, then
`_wcpp_4_copy_array__(v7)` with an uninitialized local, and use the returned
integers as destinations. The compatibility implementation at
`src/compatibility/decomp_runtime_stubs.cpp:2362` is exactly `return a1;`.
Consequently even the first destination is not reconstructed correctly: it is
`a3 + 310`, whereas the original writes `destStack + 316`.

The original annotation at `clash95.asm:29421` claims EAX, EDX and ESI inputs.
Instructions at `0x412D22-0x412D23` save ESI and overwrite it with EDX before
reading it. The operative inputs are EAX destination and EDX source; the
inferred incoming ESI argument is not read. The assembly lists a data reference
at `0x50ED38` (`clash95.asm:400743`) rather than a direct code caller. No current
production text call to this recovered function was found; direct native test
calls do exist. That does not prove the descriptor callback is unreachable.

| Original instructions | Proven operation |
| --- | --- |
| `0x412D25-0x412D49` | Copy the two coordinate words and bytes 4/5; set destination to `dest + 6` |
| `0x412D36 mov ecx,0x50F090`; `0x412D44 mov ebx,10`; `0x412D4C lea edx,[esi+6]`; `0x412D4F call 0x475A45` | Copy ten slot elements using the descriptor |
| `0x412D54 add eax,310`; `0x412D64 add eax,4`; `0x412D67 mov ecx,[edx]`; `0x412D6C mov [eax-4],ecx` | Copy the path count from source +316 to destination +316; prepare destination +320 |
| `0x412D5F mov ebx,100`; `0x412D6F mov ecx,0x50F0B0`; `0x412D74 call 0x475A45` | Copy 100 waypoint elements from source +320 |
| `0x412D79-0x412D90` | Copy byte 720 and dword 721; return the original destination |

The helper at `0x475A45` takes EAX destination, EDX source, EBX count and ECX
descriptor. At `0x475A5E` it loads the callback from descriptor +8; at
`0x475A61` it loads the stride from +16. Its forward loop calls the callback at
`0x475A7B`, advances both cursors, and finally returns the original destination
saved at `0x475A5A` (return load at `0x475A68`). The descriptors contain:

| Descriptor | Callback at +8 | Stride at +16 | Current corresponding callback |
| --- | --- | --- | --- |
| `0x50F090` | `0x412DA0` | 31 | `BattleUnitEntry_CopyMergingPackedFlags`, units_003.cpp:110 |
| `0x50F0B0` | `0x412EE0` | 4 | `UnitTrackElement_CopyFromTemplate`, units_003.cpp:185 |

The slot callback deliberately preserves destination bits: bit 7 at offset 12,
bits 4-7 at offset 13, bits 3-7 at offset 17, and bits 1-7 at offset 22. It also
leaves slot bytes 14-16 unchanged. Original instructions `0x412DDC-0x412E93`
corroborate the current packed-flag merges. This is not a 725-byte record memcpy.
The waypoint callback copies bytes 0/1 and the word at 2 (`0x412EE0-0x412EF4`).

Smallest proven repair: retain the legacy signature/adapter while independently
auditing callback references; express the same field-copy sequence and two
forward callback loops with explicit source, destination, count and stride.
Use alignment-safe record access. Leave the inferred third argument inert.
Initializing `v7` alone, inventing a use for `a3`, replacing the whole record by
memcpy, or globally changing the CRT helper without auditing its other callers
are rejected alternatives. A neighboring path-stack copier also uses the stub
(units_003.cpp:177); this audit does not authorize a global helper replacement.

## CalcMilitaryStrength: lost preserved stack pointer

Current definition: `src/units/004115E0_00412BE0_units_002.cpp:1451`,
`int UnitStack_CalcMilitaryStrength(int stackPtr)`. The return at line 1457
passes `(char *)(uintptr_t)(v2 + 6)` with no assignment to `v2`.

`clash95.asm:29263` annotates only EAX input and EAX result. The original is
unambiguous:

```text
412BE3  mov edx,eax          ; input stack retained in EDX
412BE5  call 422B80          ; Unit_GetSquadCount
412BEA  lea ecx,[edx+6]      ; slot array
412BED  xor ebx,ebx          ; wall-defense bonus = 0
412BEF  mov edx,eax          ; squad count
412BF1  mov eax,ecx
412BF3  call 412B90          ; score with special-personage check
```

The original count helper pushes EDX at `0x422B81` and restores it at
`0x422B98`. It counts up to ten 31-byte slots starting at stack +6, stopping at
type -1. The current helper (`decomp_runtime_stubs.cpp:3087`) implements that
count, but a C++ return value cannot initialize a caller's unrelated local.
The score wrapper at units_002.cpp:1422 reads the supplied array for positive
counts and forwards it to the scoring function. Zero count does not legitimize
evaluating an indeterminate pointer expression in the caller.

Smallest proven repair: replace `v2 + 6` by the explicit input stack plus six
bytes, preserving the count call and zero bonus. No guessed register output or
arbitrary zero initialization is needed. The current production caller is
`Player_CalcMilitaryStrength`, units_003.cpp:67 (original call `0x412CE3`,
`clash95.asm:29383`). That caller has separate indeterminate locals, including
`v10`; repairing this callee alone does not establish correct player totals.

## NormalizePeasantCargo: lost threshold, unused bridge context

Current definition: units_002.cpp:748,
`signed int UnitStack_NormalizePeasantCargo(__int16 *stackPtr, DWORD a2, double a3)`.
After counting type-32 slots and summing their signed quantity bytes, line 784
compares an uninitialized pointer local, `(int)(intptr_t)v8`, with the total.
This controls clearing, compaction and reconstruction of the peasant cargo slots.

The original annotation at `clash95.asm:27912` describes EAX stack, EBP context
and ST0 context; EDX is an internal integer, not an incoming pointer:

```text
4121E0  xor edx,edx          ; number of peasant slots
4121F1  movsx eax,BYTE PTR [ecx+9]
4121F5  inc edx
4121F6  add esi,eax          ; signed total quantity
412201  dec edx
412202  imul edx,edx,100     ; threshold = (slot count - 1) * 100
412208  call 410010          ; minimum current AP
412211  cmp edx,esi
412213  jle 4122E0           ; skip consolidation unless threshold > total
```

The AP helper pushes EDX at `0x410012` and restores it at `0x41003E`, preserving
the computed threshold. The C++ local `peasantSlotCount` is already available;
the missing arithmetic, not an unknown pointer, is the source of this defect.

Two final-call arguments need a different classification. At units_002.cpp:826,
`v8` and `j` are passed to `Rules_SyncArmyFactStrength`. In the original,
EDX/ECX hold defined carried values; in the current C++, `j` is assigned only in
the consolidation branch and `v8` only near its end. The traced contract is:

- `Rules_SyncArmyFactStrength`, strategic_002.cpp:990, explicitly ignores its
  third argument (`j`) at line 1005. Original `0x455076 mov ecx,eax` overwrites
  incoming ECX before the ensure call.
- Its second argument reaches `Rules_EnsureArmyFactForStack`,
  strategic_002.cpp:911. That function forwards it only to
  `Rules_RetractArmyFact`; the create branch obtains an army ID independently
  from the stack's tile at line 924.
- `Rules_RetractArmyFact`, strategic_001.cpp:1393, assigns those context values
  only to unused locals. Its actual retraction and log derive from the explicit
  stack and tile. Original `0x452258 mov edx,eax` likewise overwrites incoming
  EDX; its saved incoming ECX/EDX are only restored. Original ensure creates its
  own ID at `0x454F05-0x454F3C`.

Thus `j` and the final `v8` argument do not carry a missing army ID or game-state
input along this call path. Their indeterminate evaluation remains a C++ defect;
an unused callee parameter does not make that evaluation valid. Do not mistake
the genuinely used army ID of `Rules_CreateArmyFact` for this discarded context.

Smallest proven repair: compute `(peasantSlotCount - 1) * 100` as a separate
integer for the comparison, and pass defined values for reviewed unused bridge
slots (for example zero), or eliminate them inside a separately reviewed bridge
while retaining the legacy ABI. Keep signed quantity interpretation, AP capture,
compaction order, full-100 entries, remainder entry even when zero, sentinel and
fact synchronization. The production caller is `UnitStack_CaptureDefeatedStack`
at units_002.cpp:921; original `0x4123D7` calls `0x4121D0`
(`clash95.asm:28142`). This audit has no trace proving that a validated gameplay
route executes this function or its consolidation branch.

## RegroupWithOtherStackByHealth: lost first stack index

Current definition: `src/strategic/00455740_004582B0_strategic_003.cpp:1150`,
`int UnitStack_RegroupWithOtherStackByHealth(int a1, int a2, char a3, DWORD a4, double a5)`.
It saves `stack_index = a1`, but its first coordinate read at line 1197 uses the
uninitialized `stack_index_reg`; line 1199 repeats that error for the other
coordinate. These are actual stack-table dereferences before any movement
decision. Later distance checks use the defined `stack_index`.

The original annotation at `clash95.asm:134276` describes EAX first index, EDX
second index, BL/EBP/ST0 context. Its first-index data flow is explicit:

```text
4582BB  mov [esp+28Ch],eax   ; first index saved
4582C2  mov [esp+290h],edx   ; second index saved
4582CB  mov ecx,eax
4582D2  mov edx,ecx          ; EDX now holds the first index
4582D4  call 419120          ; log preserves ECX and EDX
4582D9  lea eax,[edx*8]
4582E0  add eax,edx
4582E2  shl eax,4
4582E5  add eax,edx          ; 145 * first index
```

The following arithmetic multiplies by five, yielding the 725-byte stack
stride. The first coordinate load is at `0x45831A`. The original log function
either returns before touching ECX/EDX, or saves them at `0x41913D-0x41913E`
and restores them at `0x4191D4-0x4191D5`. The current no-op `Debug_Log`
(`src/units/00416850_00419120_units_005.cpp:1177`)
cannot give a caller-local variable the value of an original preserved register.

The separate `v6` argument at lines 1205/1222 is only passed as argument three
to `Unit_MoveTrackNearTile`. That callee, units_004.cpp:630, explicitly has
`(void)a3` at line 641 and builds the path from its other arguments. Therefore
this is discarded context, not another missing movement input. Replace its
indeterminate evaluation with a defined reviewed placeholder or internal bridge
cleanup; do not invent a new receiver from it.

Smallest proven behavior repair: use the already saved first `stack_index` for
the first distance check and remove the unused indeterminate `v6` argument
evaluations. Preserve subsequent moves, rechecks and health regrouping. This
does not certify the remainder of the large function or path/allocation
compatibility helpers. A class adapter must retain both distinct stack indices
and resolve live records across operations that may move or replace game data.

This is a game operation exposed to CLIPS, not a CLIPS engine implementation.
`Rules_HostRegroupTroops`, strategic_008.cpp:414, obtains arguments 2 and 1 and
calls this function at line 422; it is registered in strategic_003.cpp:656.
The original reads the same two arguments at `0x4573ED-0x4573FE` and calls
`0x4582B0` at `0x457403`. No direct native test for this routine or reached
gameplay trace was found in this audit. Registration demonstrates a callable
boundary, not actual execution in a retained route.

## Existing native evidence and repair gates

The frozen baseline's private durable logs are under
`artifacts/cpp-classes/20260906/baseline/coverage-gcc13/native-full.log` and
`coverage-clang18-final/native-full.log`. All six direct tests below report
`CRASH` in both profiles:

| Native identity | Current test source | GCC / Clang log lines |
| --- | --- | --- |
| `cov02_stack.copy_from_template` | `tests/unit/cases/test_cov02.cpp:217` | 23 / 24 |
| `cov2_00_unitstack.copy_from_template` | `tests/unit/cases/test_cov2_00.cpp:196` | 244 / 264 |
| `cov3_02_unitstack.copy_from_template_fresh_stack_context` | `tests/unit/cases/test_cov3_02.cpp:518` | 6048 / 6042 |
| `cov4_03_unitstack.copy_from_template_attempt` | `tests/unit/cases/test_cov4_03.cpp:404` | 5991 / 5896 |
| `cov02_military.calc_strength_zero_squads` | `tests/unit/cases/test_cov02.cpp:189` | 24 / 30 |
| `cov2_06_unit.calc_military_strength_nonzero_squad` | `tests/unit/cases/test_cov2_06.cpp:457` | 1065 / 261 |

These are isolated, best-effort coverage probes, not semantic assertions. Their
comments sometimes explicitly rely on stack garbage or a zero-count branch.
Automatic buffers cast through `int`, zero third arguments, other compatibility
state and the indeterminate locals can all affect where a probe faults. No new
debugger backtrace was collected, so the precise fault site is **unproven**.
The source/assembly proof above establishes the defects independently of those
crashes. The frozen GCC report even records 3/3 executable lines covered for
CalcMilitaryStrength despite its crashes; coverage is not behavior parity.
NormalizePeasantCargo and RegroupWithOtherStackByHealth have no direct case in
the searched native test sources and are not in the selected pure-function set.

Proposed focused gates for a separately authorized repair:

- Copy: distinct nonzero source/destination patterns, all ten 31-byte slots and
  100 four-byte waypoints, every preserved destination bit/byte, path count,
  offsets 720/721, return address and guards. Include self-copy and investigate
  overlap with the original forward callback sequence before assuming memcpy
  or memmove semantics.
- Strength: valid low32 guarded records with zero, one and ten slots, the -1
  sentinel and special-personage cases. Assert the intended array/count/bonus
  contract and resulting score; a touch-only crash probe is insufficient.
- Cargo: zero/one/multiple peasant slots, totals below/equal/above the exact
  threshold, signed quantity extremes, exact hundreds and zero remainder,
  retained AP, compaction, sentinel/capacity and each fact-sync branch. Compare
  complete record changes and rule-state effects against assembly-backed
  expectations; do not redesign cargo semantics.
- Regroup: different first/second indices, adjacent and distant pairs, failed
  and successful paths, both movement attempts, full 31-byte slot payloads,
  health partition boundaries and capacity. Validate live-record resolution
  after moves and retain original-route evidence for any gameplay claim.

Run appropriate GCC/Clang production and native checks after those repairs,
record exact changed outcomes without erasing the frozen failures, then perform
class extraction differential checks against the repaired canonical bodies.
Fresh original/reconstruction frame pairs are required for any new visual claim;
this audit makes none and advances no campaign milestone.

## Reproduction commands and validation limits

The reads ran from the WSL migration worktree. The command families below
reproduce the decisive evidence without executing either game binary:

```sh
rg -n 'UnitStack_(CopyFromTemplate|CalcMilitaryStrength|NormalizePeasantCargo|RegroupWithOtherStackByHealth)' src tests/unit/cases
rg -n 'sub_(412D20|412BE0|4121D0|4582B0)' clash95.asm
rg -n 'Unit_GetSquadCount|Rules_RetractArmyFact|__wcpp_4_copy_array__' clash95.map
objdump -d -Mintel --start-address=0x412d20 --stop-address=0x412da0 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x475a45 --stop-address=0x475a83 /mnt/c/clash/clash95.exe
objdump -s --start-address=0x50f090 --stop-address=0x50f0d0 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x412da0 --stop-address=0x412f00 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x412be0 --stop-address=0x412c00 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x422b80 --stop-address=0x422ba0 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x4121d0 --stop-address=0x412300 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x410010 --stop-address=0x410050 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x454ed0 --stop-address=0x454f50 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x455070 --stop-address=0x455110 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x452250 --stop-address=0x4522e0 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x4582b0 --stop-address=0x4583a5 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x419120 --stop-address=0x4191e9 /mnt/c/clash/clash95.exe
objdump -d -Mintel --start-address=0x4573d5 --stop-address=0x457417 /mnt/c/clash/clash95.exe
rg -n 'copy_from_template|calc_strength_zero|calc_military_strength_nonzero' artifacts/cpp-classes/20260906/baseline --glob 'native-full.log' --no-ignore
```

Only this report was added. No compiler, runtime, native-suite, coverage or
regeneration gate was rerun for this source audit. Existing crash identities
remain historical evidence rather than fresh results. Receiver and bridge
classifications are established for the traced paths; wider callback reachability,
full-family behavior and the proposed repairs remain unvalidated.
