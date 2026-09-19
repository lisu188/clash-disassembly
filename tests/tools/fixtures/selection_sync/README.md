# Current-selection synchronization fixture

This fixture extracts and executes the actual
`UnitStackSelection_SyncForCurrentSelection` body. Its four boundaries are
Count, End, Begin and Refresh. The compact public provenance supplies aggregate
and per-case output hashes measured from unchanged original instructions, whose
linked bytes are checked against both local PE copies. Public CI needs no retail
executable or game assets. The readable public contract is an exact copy of the
module used for those measurements.

The 28 scenarios distinguish zero calls for absent/inactive selection, the
absent-selection End pointer, singleton End's saved table-base pointer, all three
count queries, live state mutations around their gates, signed `> 1`, conditional
third-query execution and exact DWORD context forwarding. Terminal mutations
remain visible in final state. The recorder observes each boundary before
applying its scripted changes and returns the scripted result afterward.

Every event has seven DWORDs: call ID, two argument words, scripted result and
three live-state words (arena, selected index and active index). Final output
has only those three state words. The enclosing function is void; its final
record does not invent an EAX result. The event's scripted result belongs to
that called boundary and is retained even when the caller ignores it.

Count validates its full native `intptr_t` argument against declared zero-extended
low32 stack addresses before converting it to canonical arena/slot identities.
End similarly checks full pointer bits. Its tag zero means the exact entry
pointer; tags one through four mean the distinct declared arena table bases.
Entry/table aliases are rejected. Paired high-bit arena/index values may wrap to
a backed low arena; live state still records the original high identities and
indices. No unexpected high native pointer bits are silently discarded.

The untouched parent's singleton End argument differs from the original: it
forwards the entry pointer where the original retains the first query's table
base. This is a defined argument-fidelity correction, without demonstrated
child-state effects: the original reached highlight helper does not consume
the receiver. A separate high count-address case diagnoses defined native
sign extension from `int` to `intptr_t`; its unbacked pointer is observed only
at the recording boundary. Three high-index cases are excluded from parent
execution for signed stride overflow at the first, second and third query,
respectively. These classifications are retained individually in the contract.

Negative count results and boundary mutations are synthetic caller tests. Real
Count is a pure leaf returning 0..10 from contiguous occupied unit slots; it does
not make those global mutations. A separate original leaf supplement records
its actual slot scan and ECX/EDX preservation. The public harness uses the
existing stack constants/layout assertions but does not dereference Count's
scripted address or replace the real callee with an inferred implementation.

The two public unittest methods cover GCC 13 and Clang 18 at O0/O2, with strict
warnings and UBSan under the existing packed-alignment exclusion. They compare
all measured trace hashes. This caller fixture does not establish real panel
rendering, mouse interaction, arbitrary child behavior or campaign progress.
