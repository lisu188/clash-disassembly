# GameRandom: defined logging context and unsigned range result

Track: Win95 reconstruction. Frontier: two separately reviewed behavior repairs
before GameRandom class extraction. No class implementation is introduced by
this batch, and no campaign or visual milestone is advanced.

## Initial seed logging context

initRandomSeed at 0x415DD0 assigned time_() into g_RngState and then evaluated an
uninitialized C++ local v2 as Debug_Log argument one. Its current callee ignores
that context under all four combinations of logEnabled / battleLogEnabled. The
repair passes 0 and removes only the unused local. Time acquisition, state store,
logging call order, existing remaining arguments and the 29-byte format string
remain unchanged.

Original initRandomSeed at clash95.asm:34490 zeroes EAX for time_, pushes the
returned seed and format pointer, stores g_RngState at 0x525578, and calls log.
The original log at 0x419120 / clash95.asm:38977 saves incoming ECX before its
active logging path but overwrites ECX with the opened stream before using it.
There is no receiver or RNG state supplied in incoming ECX. The current
Debug_Log at src/units/00416850_00419120_units_005.cpp:1177 has a quarantined
formatter and discards all arguments. Zero defines unused compatibility context;
it does not invent a recovered seed argument. Restoring the original formatter,
clock/stream calls and stack-based variadic seed transport remains separate
logging compatibility work.

## Random range result wrapping

Rng_RandRange at 0x415DF0 used:

    result = (int)(seed % range) + minValue;
    return (unsigned int)result;

The signed addition can overflow even for an ordered inclusive interval. For
example min = INT_MIN, max = INT_MAX-1 and seed = 0xFFFFFFFE produce signed -2 + INT_MIN
in the old C++, although the original 32-bit LEA returns 0x7FFFFFFE. The repair is:

    return seed % range + (unsigned int)minValue;

This preserves unsigned 32-bit wrapping. Original instructions at 0x415E25 zero
EDX, at 0x415E29 perform unsigned DIV, and at 0x415E31 compute LEA EAX,[EDX+ECX].
The two Time_Now calls, the intermediate XOR-state store, mixing constants,
range computation, final state assignment and all storage remain unchanged.
No minimum/maximum reordering or clamping is introduced.

The existing reconstruction's zero-range return remains deliberately unchanged.
The original executes DIV-by-zero for range 0 and stores its final state only
after DIV; current reconstruction already stores the final state and returns
the minimum. This batch does not change that compatibility contract or claim
whole original-RNG equivalence for zero ranges. It also does not change the
existing clock implementation or recover broader logging.

## Source and instruction provenance

Both current unrepaired functions match e13abc0266707de6291be39fdea28dca4f3e7e2b,
and were rechecked unchanged through origin 1b8b4b8. Their original spellings are
in clash95.map at segment 1 offsets 0x14DD0 and 0x14DF0. The original listings are
clash95.asm:34490 and34508. Frozen source and provenance are in
../tests/tools/fixtures/game_random/.

| Function | Before body SHA256 | Repaired body SHA256 |
| --- | --- | --- |
| initRandomSeed | 0a79a04517f8c901ed065e84194b780efe135128583073c16de8e0064a86c899 | 08286e807206fdfd0add87ec49105a0d9d28c1b9454db17ceb37ef459abc4c26 |
| Rng_RandRange | 2ead959e141293c39027aeaaa14912d3230e2049d2b37cd179430fc3d30430a2 | 28ea29d3f46173c6612037b7c3e74498aa9322addf4539f84687dec2efb5d1cb |

The installed and repository executables have different whole-file hashes but
identical bytes in all four reviewed ranges (initializer, RNG, logger, clock).
The 32-byte initializer range 0x415DD0..0x415DF0 hashes
4b51d97bc3e9b60cd251791c9f6abfc3b445641485b83f19fb4ef731af172811;
the 80-byte RNG range 0x415DF0..0x415E40 hashes
e78ef4bec341c0c51580a70c534d8adab16ec4136d41e117ab34c8ef882590e7.
The original executables were read/disassembled headlessly, not launched.

## Independent recovery regression

Run from the WSL repository root after applying the recovery:

    python3 -m unittest discover -s tests/tools -p test_game_random_recovery.py -v

The test resolves and hash-checks actual production initRandomSeed,
Rng_RandRange and Debug_Log. They compile in separate translation units, with
linker --wrap=Debug_Log recording the boundary and forwarding to the actual
logger. Frozen unrepaired bodies are controls. There are no duplicated repaired
reference algorithms. The overflow result is compared to executable x86 DIV/LEA
instructions, while the unchanged state-mixing arithmetic and two distinct
clock reads are checked against complete traces.

Each GCC 13 / Clang 18 O0/O2 profile passes 68,932 scenarios plus 4,096 sequential RNG
steps. The matrix includes all logging flags, signed extreme seed/min/max/tick
values, reversed and zero-width intervals, 65,536 generated combinations,
external state-word changes between draws, exact intermediate/final state,
callback order and all 64 bytes surrounding the RNG word. Defined-input behavior
also agrees with the frozen unrepaired RNG. No recovered allocation, release,
constructor or gameplay action is added.

Pattern local initialization exposes the unrepaired initializer's undefined
context; the unrepaired RNG overflow traps with SIGILL under UBSan. Independently
reverting either actual repair while updating the scratch manifest makes all
four profiles fail for that contract: the seed context assertion or the RNG
UBSan trap. Warnings are suppressed only on those deliberately unrepaired
negative-control translation units so failure reaches the behavior assertion.
Positive runs use -Wall -Wextra -Werror and trapping UBSan.

All eight before/after complete-source compilation checks pass across those
four compiler profiles. Existing object storage sections, their bytes/size/
alignment and data relocations match; no new initialization sections appear.
This is a bounded source/object and recovery-fixture gate. Production link,
full native outcomes, fixed 718-function coverage and headless runtime gates
remain the coordinator's integration work; their historical failures and
ratchet baselines must not be overwritten.

## Private preparation evidence

Prepared scratch: /var/tmp/clash95-game-random-recovery-7ufgn1dt/.
It contains source snapshots, exact commands, focused and negative-control logs,
original-range hashes/disassembly and object-storage comparison JSON. Preserve
it as a durable artifact before deleting temporary working data. The prior
incomplete scratch /var/tmp/game-random-class-20260906-ba21c1p3/ remains untouched;
its unintegrated extraction was not imported into this recovery patch.

## Integrated recovery gate

The coordinator applied only these two behavior changes after main integration
`9ec82b0`, updated only their current canonical hashes and reran the actual-body
fixture successfully in all four profiles. Both production builds, strict
symbol/storage/initialization comparisons and all eight asset-free gates pass.
No migration text allowance or frozen ratchet baseline changes. The canonical
count remains 4,157 and the class-method count remains eleven in this repair.

Commands from the WSL worktree root:

```sh
python3 tools/update_split_manifest_hashes.py --update \
  --only initRandomSeed --only Rng_RandRange
python3 -m unittest discover -s tests/tools -p test_game_random_recovery.py -v
python3 artifacts/cpp-classes/20260906/pilot/validate-stage.py game-random-recovery \
  --reference-dir artifacts/cpp-classes/20260908/origin-latest-reference \
  --evidence-dir artifacts/cpp-classes/20260908/game-random \
  --allowances data/class_migration_latest_origin_text_additions.json
```

Local evidence is under `artifacts/cpp-classes/20260908/game-random/`.
`recovery-preparation.tar.gz` preserves 449 preparation files, including first
failed fixture attempts, original evidence, negative controls and object checks;
every member was verified against its original SHA-256 and size. No source
scratch or older evidence was deleted. Full native/coverage/runtime acceptance
of the eventual class implementation remains separate from this repair gate.
