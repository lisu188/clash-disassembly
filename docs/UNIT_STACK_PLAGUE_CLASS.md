# UnitStack plague setter extraction and relocation

Track: Win95 reconstruction. The separately original-backed
[address repair](UNIT_STACK_PLAGUE_REPAIR.md) is now an explicit
`clash95::UnitStack::UnitStack_SetPlagueFlag()` operation. Construction only
binds the existing packed record. The original int-signature function remains
a thin adapter, and the canonical method initially stays in the original
translation unit for extraction validation.

The method removes only the proven record receiver and binds its original int
representation locally. It preserves both low32 casts, the sentinel scan,
ten-slot limit, every flag store and the original return cursor. It adds no
storage, initialization, destructor action or native virtual layout. There are
no calls to this setter from already migrated methods that need conversion.

The actual method, original adapter and frozen repaired procedural definition
each match all 36,344 original-measured cases in eight GCC 13 / Clang 18
O0/O2 signed/unsigned-char UBSan profiles. Each lane starts with identical bytes
and compares the full 800-byte arena and returned bits. The direct lane also
checks that constructing the borrowed record object changes no bytes. The
frozen definition is hash-pinned to repair commit `e1b3b50`; it is test evidence,
not a second production implementation.

Both production builds, strict symbol/storage/initialization comparisons and
all eight asset-free gates pass. All five comparison inventories enumerate
exactly the new method symbol. The 4,157 recovered identities, 147 translation
units and six class sources remain; there are now 28 canonical methods.
No historical ratchet baseline changes.

GCC executable-line measurement reports nine lines for the frozen repaired
function, ten for the canonical method and two for the adapter. The one-line
canonical increase is the receiver binding. This identity remains outside the
unchanged 718-function coverage set, so its selected coverage denominator does
not change. These focused measurements do not replace full native coverage or
runtime validation of the integrated checkpoint.

Commands run from the repository root in WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_unit_stack_set_plague_low32.py -v
python3 artifacts/cpp-classes/20260919/validate-incremental.py plague-extraction \
  --reference-dir artifacts/cpp-classes/20260919/published-main-reference \
  --evidence-dir artifacts/cpp-classes/20260919/plague-class-integration \
  --allowances data/class_migration_september_main_text_additions.json
python3 artifacts/cpp-classes/20260919/plague-class-integration/measure-lines.py
```

The indicated artifact directory retains focused results, compiler logs,
strict comparison reports, all gate outcomes, exact manifest entries and line
measurement reports. The initial line-measurement command was not executed
because automatic approval review hit a usage limit on September 19; the
unchanged command passed on September 24. Existing runtime and campaign
milestones remain unchanged.

The separately validated relocation moves only the canonical body into
`src/units/UnitStack.cpp`, in manifest order. Its body hash remains
`5283767eb76452f7a3b716feb1a19c956d67a300b1121e4bda22b859d8530e2c`, and the
original adapter remains in its storage-anchor TU. The same eight focused
profiles, both production builds, strict comparisons and all eight asset-free
gates pass after the move. Run the validation command above with stage
`plague-relocation`; its separate logs and step records are retained alongside
the extraction evidence. All 28 methods now reside in six class-named sources.
