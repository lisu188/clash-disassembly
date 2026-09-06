# Original builder and bridge fixtures

These are recovered table bytes and measured predicate results, not retail game
assets. Public tests need only these files, canonical source and a C++ compiler.

- `cases.json`: 636 bridge predicate and 36 builder selector outcomes measured
  from unchanged original x86 instructions at `0x424020` and `0x40A0A0`.
- `original-road.bin`: all 706 bytes at `0x51420C..0x5144CE`.
- `original-builder.bin`: all 322 bytes at `0x511BC0..0x511D02`.
- `pointer-relocations.json`: original pointers, canonical callback identities and
  exact terminated text bytes for the 112 pointer fields in those two blocks.
- `main-callbacks.json`: the six callback fields from the original main action
  table at `0x511D40`; Building at `0x511E34` points to `0x40A0E0`.
- `provenance.json`: both original PE hashes, measured instruction/data hashes,
  output hash and exact local original-probe commands. Local executable paths
  record provenance; tests never read them.

The original gate scans 48 DWORDs from the same live Road backing. Its scan
overlaps packed words, bounce offsets and the first five north-marker fields;
those bytes must not become an independent constant list. Cases cover all 48
positions, ignored index 48, all 12 initial approach IDs, terrain boundaries,
both axis constraints, duplicate-first-match behavior and unsigned word input.
Selector inputs include values below 15, preserving signed truncation toward
zero, and remain within the signed subtraction domain.

The original probe replaces only selector animation at `0x419E60` with a
recording return. Tests therefore check that boundary call, return value, menu
write and absence of other writes; they do not prove the animation itself. The
canonical harness extracts five actual definitions and uses inert identities
for other callback bodies. It checks complete nonpointer bytes, relocated
pointers and text contents, physical aliases and initialization idempotence.
GCC 13 and Clang 18 run at `-O0` and `-O2` with UBSan, excluding packed alignment.
This is bounded logic and data evidence, not a construction or rendering claim.

Run from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_builder_road.py -v
```

The local reproduction adapter and retained runs are under
`artifacts/runtime-recovery/builder-road-menu-20260906/tests/`; they are not a
public-test dependency.
