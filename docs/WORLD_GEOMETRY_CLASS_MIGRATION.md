# WorldGeometry: separate sine recovery and class extraction

Track: Win95 runtime reconstruction. Frontier: game-system class migration, with a separately authorized assembly-backed sine recovery before this family advances. No campaign-route promotion or visual-fidelity claim is made.

Preparation used source base `f7d0f262dc36934e938c4cfcb20902ed14df026e` in
`/var/tmp/world-geometry-class-20260906-nqdw0mct`. Its immutable archive, hashes,
patches, mappings and evidence are retained under
`artifacts/cpp-classes/20260906/world-geometry/`.

The separate sine recovery is now integrated. Its 82,669-case test passes all
four compiler/optimization profiles on the actual production body. GCC 13 and
Clang 18 production builds, exact symbol/storage/initialization comparisons and
all eight asset-free gates pass without new allowances. Commands and logs are
`artifacts/cpp-classes/20260906/pilot/*sine-recovery*`. The initial test invocation
selected the wrong filename and correctly reported zero tests; the corrected
[test_math_sin_degrees_q16.py](../tests/tools/test_math_sin_degrees_q16.py)
run is recorded separately. Class extraction and relocation now also pass their
separate production gates below. No native or
runtime outcome is inferred from the focused arithmetic fixture.

Production extraction now passes all four differential profiles, both compiler
builds, both exact migration surface comparisons and all eight asset-free
gates before source relocation. Only their three method symbols and the trivial
table-borrowing constructor are added; all legacy identities, named storage,
data order and initialization profiles are unchanged. Evidence is in
`world-geometry/extraction-*` and `pilot/*world-geometry-extraction*` beneath
the private artifact root. The class fixture now pins the actual separate
recovery commit `dd54ee075b2b16b174eef0f910a23ccd81400bca`.

The unchanged methods are now in `src/world/WorldGeometry.cpp`; relocation
repeats all four differential profiles, both production builds, both exact
surface comparisons and all eight asset-free gates successfully. The ordered
source inventory grows from 142 to 143 by appending this class source to the
world group. No original source is reordered. Evidence is in
`world-geometry/relocation-*` and `pilot/*world-geometry-relocation*`.
Fresh native and headless route validation of the expanded class build remain
integration gates; the frozen eight-method runtime replay is tracked separately.

## Review order

1. 01-sine-recovery.patch changes exactly the INT_MIN case in the existing free Math_SinDegreesQ16 body and adds its focused test, frozen original, exact table and shared compiler plumbing.
2. After the recovery commit and required gates, 02-world-geometry-extraction.patch places the three actual bodies in nonvirtual, out-of-line clash95::WorldGeometry methods at the original TUs. It adds original-signature ABI adapters and a declaration-only header with a simple borrowing constructor.
3. After extraction parity, 03-world-geometry-relocation.patch moves only the method definitions into src/world/WorldGeometry.cpp (97 lines). Original anchors keep the adapters; global storage remains unchanged. Append the new class source without reordering any existing src/sources.cmake entry.

integration.json gives exact canonical/adapter mappings and hashes for coordinator integration. All patches apply sequentially in the disposable patch-check fixture.

The sine class fixture truthfully labels its repaired stage over the real pre-recovery commit. Update its reference_commit to the actual recovery commit before accepting extraction; do not invent a commit.

## Sine assembly and storage evidence

Original identity: Math_SinDegreesQ16, address 0x00415D80, in src/units/00414390_00416750_units_004.cpp.

clash95.asm:34444-34481 executes NEG on EDX for negative inputs, compares it against 360 using signed ordering, then reads dword_513434[edx*4]. At INT_MIN, NEG retains 0x80000000, the signed comparison skips division, and the original 32-bit scaled address wraps 0x80000000 * 4 to zero. The routine negates table[0], whose immutable value is zero.

The C++ signed negation is undefined and may form an invalid wide LP64 index. The minimal repair handles exactly degrees == INT32_MIN by returning -g_MathSinTableQ16[0]. Other operations remain unchanged.

Frozen original body SHA256:
035e909953f9b915e9c16b6b863b43a66a85bf37604b96bc3799aca6f0d26a41

Repaired free body SHA256:
5e336b247d2ba8b79e744e0d9df0c018089b871b33a7fa5b2b48646f0ed3735a

The table remains int g_MathSinTableQ16[363] at src/state/00000000_0054FFFF_recovered_state.cpp:8642. All 363 words are preserved, first=0, range -65536..65536. Source references and original assembly DATA XREFs show only its definition/declaration and the two sine reads, no stores or address escapes. Tests compare frozen words to the current production initializer. The class uses a const reference view; original global symbol, type, storage and lifetime remain unchanged.

For every negative input except INT_MIN, negation is representable; modulo reduces indices to 0..359. Nonnegative inputs also index 0..359. Negating every observed table word is defined. Tail words 360..362 are retained although unused by this routine.

## Caller contract audit

The production inventory has five direct calls, no address-taking, table entries or indirect uses. Original assembly has exactly five call sub_415D80 instructions at lines 34782, 72821, 72916, 136769 and 141725.

- src/units/00414390_00416750_units_004.cpp, WorldMap_DrawUnitStackWithOverlays: 30 * (g_WorldMapAttentionFlashStartTick - nowTick). The updater redraws before expiration at src/units/00416850_00419120_units_005.cpp:897-900, so no universal clock-jump bound is established. A defined product by 30 cannot equal INT_MIN, but other callers can.
- src/battle/0042E9E0_00430C20_battle_002.cpp:677: 2 * (currentTime - g_UnitBattleChargeModeStartTick_532074) - 90. No universal elapsed-time cap is established.
- Same battle TU:720: adjacentEnemies * pulseTime, with multiplier 3..6. Multiplier 4 and tick -536870912 produce INT_MIN through defined signed arithmetic.
- src/strategic/004589C0_004602F0_strategic_004.cpp:554, WorldMap_DrawMission01ShrineMarker: 2 * now - 90.
- Same strategic TU:632, WorldMap_DrawMission11ShrineMarker: the same expression. Tick -1073741779 produces INT_MIN with both operations defined.

Time_Now (0x004207B0), src/buildings/0041F1A0_00421010_buildings_002.cpp:858-866, narrows the divided performance counter to int. Initialization divides frequency by 100. SDL src/platform/platform_sdl_runtime.cpp:3049-3072 derives the counter from gettimeofday microseconds and reports frequency 1000000. No positive-only or small-tick contract excludes these values. INT_MIN is a genuine reconstruction loss.

The test executes both safe INT_MIN-producing expressions. No speculative input cap or broad timer rewrite is introduced. Other caller overflow questions are outside this isolated callee recovery; the repaired callee itself is defined for every int32 input over the observed immutable table.

## Class boundary

- Facing_DirectionFromDelta8 (0x0040FA80): two scalar deltas, comparisons only, no receiver or global dependency. Preserve every direction constant, including (0,0) -> DIRECTION8_EAST.
- Math_SinDegreesQ16 (0x00415D80): preserve degree argument; borrow the existing table by const int (&state_)[363] through each ABI adapter.
- Math_CeilSqrt (0x00415E40): preserve the signed value and integer iteration, including value < 4 -> 1. Its name does not justify substituting mathematical ceil-sqrt.

No receiver argument is guessed or removed. Full original leaf names and argument types remain. All methods are const and nonvirtual, with actual bodies out of line. Original ABI functions remain retained forwarding adapters with their existing function-address identities. No allocation, RNG, callbacks or mutable records occur here.

For sqrt value >=4, both positive iterates remain between 2 and floor(value/2), so their sum is <= value and fits int32; divisions have positive denominators and subtractions fit. Negative inputs return before arithmetic. No additional full-range arithmetic blocker was found in these bodies.

The header exposes only the reviewed recovered-types foundation, declarations, a direct borrowing constructor and private reference. It contains no canonical global dependency or hidden behavior. No factory/helper binding identity or invented original address is needed.

## Validation

Commands from this scratch root:

~~~sh
(cd recovery-stage && python3 -m unittest discover -s tests/tools -p test_math_sin_degrees_q16.py -v)
python3 -m unittest discover -s tests/tools -p test_class_world_geometry.py -v
(cd relocation-stage && python3 -m unittest discover -s tests/tools -p test_class_world_geometry.py -v)
~~~

Each compiles GCC 13.3 and Clang 18.1 at O0 and O2, GNU++20, no PIE, warnings as errors and undefined-behavior sanitizer traps. Only the unrepaired reference disables UBSan. Its INT_MIN probe runs in a child with core dumps disabled and a two-second alarm.

The oracle executes the original EAX/EDX/ECX NEG/compare/IDIV operations and explicit 32-bit LEA/load. The table lies below 4 GiB in a read-only 4096-byte image between inaccessible guard pages. Table and suffix guard bytes are compared after every input.

Per profile:
- Recovery: 82,669 sine inputs, including signed extremes, residues near int32 bounds, dense -8192..8192, 65,536 deterministic full-width bit patterns and the caller expressions.
- Class extraction and relocation: 169 facing pairs, 82,669 sine inputs and 220,954 sqrt inputs. Sqrt covers every square boundary through 46340 squared, dense small values and full-width samples.
- Actual ABI adapters and direct methods both match frozen repaired references.
- Actual canonical/adapter definitions and hashes are resolved through manifest schema 3, including relocated sources.

Observed unrepaired INT_MIN outcomes: GCC/Clang O0 both SIGSEGV; GCC/Clang O2 both returned -51643. These are observations of undefined behavior, not a portable contract. The x86 oracle and repaired body return zero in all profiles.

All recovery, extraction and relocation profiles passed. The actual 97-line class TU also compiled separately under all four profiles. The class-header dependency policy passed.

Logs: sine-recovery.log, world-geometry-extraction.log, world-geometry-relocation.log, world-geometry-standalone-compile.log (full standalone commands), header-policy.log, patch-application.log.

Confidence: high for the repair, immutable table, class boundary and focused parity. Production linking, linked-data/native checks and runtime routes remain coordinator work; scratch success is not their acceptance.
