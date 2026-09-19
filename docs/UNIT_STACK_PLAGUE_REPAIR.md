# Plague setter address repair before class extraction

Track: Win95 reconstruction. `UnitStack_SetPlagueFlag` remains procedural in
this separately validated behavioral repair. Its original int argument and
return, sentinel scan, ten-slot limit and flag stores remain unchanged.

The original instructions at `0x00412A90` treat the incoming handle as a 32-bit
address and return that address plus 31 bytes for each processed slot. The old
reconstruction sign-extended negative incoming handles on the 64-bit host and
returned a cursor six bytes too far forward. The repair explicitly zero-extends
the incoming low32 bits and subtracts the slot-base offset in unsigned 32-bit
arithmetic before returning the original int representation. The earlier
September 13 return-only proposal and its evidence remain intact; that proposal
did not cover negative incoming handles and was not applied separately.

Fresh unchanged-original instruction execution establishes 36,344 cases,
including high-bit incoming addresses, all 256 flag bytes, every sentinel
prefix, signed type extremes, 16 alignments, return cursors crossing `INT_MAX`
and complete 800-byte arenas. The earlier 8,448-case corpus also replays
identically. All eight GCC 13 / Clang 18 O0/O2 signed/unsigned-char profiles
pass with fatal UBSan. Eight mutation controls reject; 96 individual failures
from the old and return-only bodies remain recorded. The fresh original output
SHA256 is `425e66cc4b7de614f04ad05ffb437c9faad49c753765809a90e219dc53d04ca0`.

Four full-translation-unit comparisons preserve storage bytes and order,
initialization and symbol inventory. Only the repaired function changes machine
text. Both integrated production builds, strict symbol/storage comparisons and
all eight asset-free gates pass. The integrated actual-source regression also
passes all eight profiles. Preparation disk-reserve stops and the unchanged
passing resumes remain individually retained; no historical baseline changes.

All 4,157 identities, 147 translation units and 27 previously migrated methods
remain. Only this function's current canonical body hash changes. Its nine
executable lines are unchanged and it remains outside the frozen 718-function
coverage set. The fixture contains no retail executable bytes. These checks do
not establish a mapped allocation wrapping through address zero, live-game
equivalence or fresh full native coverage.

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_unit_stack_set_plague_low32.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py plague-low32-repair \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260919/plague-integration \
  --allowances data/class_migration_september_main_text_additions.json
```

The indicated integration directory retains both compiler step records and
logs. Sealed original measurements, profile results, controls and object
comparisons are under
`artifacts/cpp-classes/20260919/plague-low32-entry-repair/`. The combined source
patch SHA256 is
`f7f4b31a2eb53df8f3ac475ca02a6cadaf02de8e41c0a20ee7d537df14485148`.
Class extraction and relocation follow as separate stages.
