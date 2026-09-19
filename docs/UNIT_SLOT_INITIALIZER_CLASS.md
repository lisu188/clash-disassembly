# UnitSlot explicit initializer class migration

Track: Win95 reconstruction; frontier: migrate `UnitSlot_InitFromType`
(`0x0040F440`) without changing record initialization or object lifetime.

The initializer is an explicitly called `UnitSlot` method. Constructing its
non-owning object only binds the existing address. The original-signature free
function remains at its world translation-unit anchor and calls the method;
no callback table receives a member pointer. The method preserves the exact
`unit_type` and owner-byte parameters, -1 sentinel, conditional AP/morale writes,
unknown bytes, flag operations and returned legacy address. Packed word/dword
access uses the existing alignment-one types. The immutable metadata table stays
in its original state source behind the existing `UnitSlot_BorrowTypeMetadata`
accessor. No new helper, class, storage, TU or historical identity is introduced.

## Extraction evidence

The actual-source differential fixture compiles the canonical method, adapter,
unchanged frozen production body, actual immutable table and borrowing accessor.
Each GCC 13 / Clang 18 O0/O2 profile passes 2,863,104 scenarios, including
1,060,864 exact-sentinel scenarios, all 16 record alignments, owner and AP bytes,
and selected flag combinations. Comparisons include returns, all 256 arena bytes,
surrounding guards, table bytes, accessor calls and zero constructor effects.
Alignment instrumentation remains enabled on the method and adapter; only the
unchanged reference's historical unaligned accesses are exempted.

Fourteen deliberate negative controls reject wrong health, preserved stance,
sentinel AP/morale retention, unknown-byte writes, metadata flag selection and
return values. Thirty-six full-TU preparation compiles preserve named storage,
its bytes and relative order, and static initialization. Existing optimized
caller text changes caused by inlining are retained in the object comparison.

The production extraction passes both supported builds, strict migration
symbol/storage/initialization comparisons and all eight asset-free gates.
Canonical and adapter hashes are respectively:

- `09346d53e35f63f848447b6d7edfeaebd695e0d15aee9bf321e89f74511a3fd2`
- `2c36e33a68789cb55c75c76b90a48e9a02791bdd0d4219c2efb18682fa40897c`

All 4,157 historical identities and the 147-TU inventory remain. There are 24
canonical methods at extraction: 23 in six class-named sources and this method
temporarily in its existing world source. The world subsystem no longer imports
the metadata global directly, reducing shared declaration visibility from
12,100 to 12,096. Frozen ratchet baselines are unchanged. The initializer remains
in the same 718-function coverage inventory; preparation measures its executable
lines changing from 26 to 27, explicitly +1 rather than resetting the denominator.

## Relocation and limits

Relocation into `src/units/UnitSlot.cpp` is the next separately validated step.
Its prepared canonical body hash is identical. Preparation records the exact
GCC O2 anonymous two-byte constant `80 f0` moving with the method; that compiler
constant is not an allowance to alter named game storage.

The fixture covers the 40 observed metadata rows and exact `0xffffffff` sentinel.
It preserves the original low32 int-address contract, using mapped addresses
below `0x7ffff000`; it does not establish additional high-bit/native64 behavior
or invent guards for invalid table indices. Existing address-arithmetic debt in
other families is separate. No new original-game runtime, route promotion or
visual equivalence follows from these unit comparisons. The 23-method integrated
runtime and native evidence remain pinned to their earlier revision.

## Reproduction

Run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_class_unit_slot_init.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py unit-slot-init-extraction \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260919/unit-slot-init-integration \
  --allowances data/class_migration_september_main_text_additions.json
```

The stage driver refuses existing log destinations. Completed outputs are under
`artifacts/cpp-classes/20260919/unit-slot-init-integration/`; the separately sealed
preparation is under `unit-package-continuation/exact-d3d89b5/` in the same dated
directory. The earlier mixed working-tree preparation remains retained and is
not the authority. Public source fixtures retain historical hashes and contain
no retail assets.
