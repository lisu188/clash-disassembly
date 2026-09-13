# UnitStack strength and cargo class migration

Track: Win95 reconstruction, behavior-class migration. This batch extracts
`UnitStack_CalcMilitaryStrength` and `UnitStack_NormalizePeasantCargo` only after
their separately validated register recovery at `c65e476`. It extends the
existing non-owning `UnitStack` view, removes only the proven record receiver,
and preserves the cargo method's `DWORD` and `double` context arguments.
Original C-linkage functions remain retained ABI adapters. Construction and
destruction still have no gameplay actions.

The strength operation keeps the repaired low32 wrap. Cargo normalization keeps
signed quantities, packed accesses, sentinels, threshold, writes and calls in
their original order. Its AP query calls the existing canonical member directly.
Count, scoring, compaction and fact operations remain at their unmigrated
procedural boundaries. The original compaction discrepancy documented in
[UNIT_STACK_REGISTER_RECOVERY.md](UNIT_STACK_REGISTER_RECOVERY.md) is unchanged.

Two independent focused comparisons compile actual manifest-resolved method
bodies and adapters. The existing original-measured 5,001-case stream retains
its hashes and now exercises both call routes. A separate migration comparison
uses the exact repaired production definitions, including an independently
frozen AP method and adapter. It compares full final and callback-time backing,
returns, callback arguments/order and controlled callback mutations. Both pass
all eight GCC 13 / Clang 18 O0/O2, signed/unsigned-char profiles. The production
dependencies remain explicit controlled boundaries; this is not proof of their
own compaction, allocator or fact behavior.

The isolated preparation rejects 48 semantic mutation runs and an additional
behavior-equivalent adapter detour from the required direct member call. Its
24 before/extraction/relocation full-TU compiles preserve named storage bytes,
order, initialization and allocated non-text sections except text-derived
unwind records. Only two method text symbols are added; no constructor or
binding change is required.

Extraction places each method immediately after its ABI adapter in the original
units_002 TU. Relocation is a separate commit into existing `UnitStack.cpp` with
unchanged canonical body hashes. The integrated extraction contains 19 canonical
methods; 17 are already in six class-named sources and these two initially remain
in their original TU. The ordered inventory stays at 146 TUs and 4,157 identities.

The preserved parameter token `a2` is also an existing global name. The current
lexical dependency generator treats uses of that local parameter as global
uses when the cargo body relocates, adding 53 visible declarations through
`units_shared_state.h`. The method does not access that global. This expected
generated-header change is reported rather than raising a frozen baseline or
changing an uncertain parameter contract. Military strength is in the frozen
718 set; its new executable receiver-binding line must be counted by the fresh
native coverage comparison. Neither 718, 89.7% nor zero-uncovered is relaxed.

The public gates are:

```sh
python3 -m unittest discover -s tests/tools -p '*unit_stack*register*.py' -v
python3 tools/audit_split_sources.py
python3 tools/update_split_manifest_hashes.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
```

Root production comparison uses the established `validate-stage.py` wrapper with
the pinned published-main reference, explicit text additions and all four
asset-free gates per compiler. Exact stages, commands, exits and logs are under
`artifacts/cpp-classes/20260913/unit-stack-integration/`. Preparation hashes,
negative controls, object comparisons and initial corrected attempts are under
`artifacts/cpp-classes/20260913/unit-stack-classes-preparation/`. Earlier runtime
and native captures do not validate this later class stage; their source scope
remains explicitly dated. Campaign and visual completion are unchanged.

The integrated extraction passes both production builds, strict comparisons
against the pinned published-main snapshot and all eight asset-free gates.
The two focused public tests pass all eight compiler profiles against the
integrated tree. Method relocation follows in its own validation/commit stage.

Relocation after extraction commit `736ea90` moves the same two canonical bodies
into `UnitStack.cpp`. Method hashes remain unchanged. All focused profiles, both
production builds, strict current-main comparisons and eight asset-free gates
pass again. The predicted declaration visibility change is exactly 11,942 to
11,995; original storage and initialization checks still pass. All **19 methods
are now in six class-named sources**, with 146 ordered recovered TUs. Logs carry
the separate `unit-stack-relocation` stage name.
