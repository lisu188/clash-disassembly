# Spent-turn low32 address repair

Track: Win95 reconstruction; frontier: repair the original address contract
before extracting `UnitStack_SetSpentTurnFlag` and
`UnitStack_ClearSpentTurnFlag` into methods. Both remain procedural here.

The reconstruction sign-extended negative `int` handles when converting them
to native pointers, and its signed return addition overflowed when a valid
record's cursor crossed `INT_MAX`. The unchanged original instructions use
32-bit address arithmetic and return `(base + 6 + 31 * processed_slots) mod 2^32`.
Four casts now interpret the input and return arithmetic as unsigned 32-bit
values before zero-extending the resulting native pointers. Signatures, packed
slot traversal, exact -1 sentinel, flag writes and all other bytes are unchanged.

Fresh unchanged original instructions at `0x00412A30` and `0x00412A60` establish
72,688 complete 800-byte images and EAX results. Cases cover all slot prefixes,
all flag bytes, 16 alignments, signed type extremes, `INT_MAX` crossings and
mapped starts above `INT_MAX`. For example, ten slots at base `0x7ffffef0`
return `0x8000002c`; one slot at `0x90000020` returns `0x90000045`.

All eight GCC 13 / Clang 18 O0/O2 signed/unsigned-char profiles pass with fatal
UBSan, both in preparation and against the actual integrated definitions.
The fixture compares the entire native pointer, so truncation cannot conceal
sign extension. Sixteen negative controls reject arithmetic, entry/return,
flag, sentinel and loop-limit defects. Eight full-TU preparation compiles show
only the two expected text changes: symbol inventory, named storage, bytes,
relative order and initialization remain identical. The 32 historical overflow
outcomes and 32 fresh failing baseline cases are retained individually.

Both integrated production builds and strict migration comparisons pass.
Clang's four asset-free gates and three GCC gates pass initially. GCC's source
audit reaches its existing 60-second timeout; the unchanged single-gate retry
passes in 52.02 seconds. Both outcomes remain recorded, and all eight gates have
passing results. No timeout or baseline is relaxed.

All 4,157 identities, 27 existing canonical methods and 147 TUs remain. These
two free functions keep nine executable lines each and are outside the frozen
718-function coverage set. Historical hashes, coverage requirements and ratchet
baselines are unchanged. This isolated proof does not establish a mapped record
crossing the 4GiB boundary, live-game behavior or campaign completion. The
23-method native/runtime checkpoint remains a separate earlier result.

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_spent_turn_repair.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py spent-turn-low32-repair \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260919/spent-turn-integration \
  --allowances data/class_migration_september_main_text_additions.json
```

The stage logs, including the initial timeout, remain in the indicated evidence
directory. The sealed preparation is in
`artifacts/cpp-classes/20260919/spent-turn-repair/`: 375 exact inputs from `33a5959`,
original provenance, complete compiler outcomes, negative controls and object
comparisons. The patch SHA256 is
`9847e7d4107064a018a22479d41c73d3840bb64d5299f7e0cf09003c5763a668`.
Public fixtures contain generated cases and provenance hashes, not retail bytes.
