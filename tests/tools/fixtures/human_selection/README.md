# Human-player selection cleanup fixture

This small fixture executes the actual `WorldMap_SyncSelectionForHumanPlayer`
body under two explicit boundaries: action-bar refresh and selection sync.
Expected traces were measured from unchanged original instructions, with the
linked code bytes checked against both local PE copies. Public CI needs only
these compact stimuli/provenance files and the recovered source; no game assets
or retail executable are required.

The public stimulus module has readable formatting with an identical Python AST,
case records and wire bytes to the measured private module. Provenance retains
the original contract hash and separately binds the formatted public file; all
original input and output hashes remain unchanged.

There are 22 scenarios and 28 recorded boundary events. Each event records its
actual validated arena argument, applicable context and live state. Final output
contains state and two bounded arena fingerprints. The function is void: neither
the original recorder nor the native test invents an integer return value.

The cases distinguish full controller DWORD truthiness (including 0x100), the
first signed unit-type WORD's exact -1 sentinel, contrasting later-slot values,
nonhuman short circuit, clear-before-refresh order, entry context, and saved
arena arguments versus live globals mutated by callbacks. The native fixture
uses the existing packed PlayerRuntimeState, UnitStackRecord and UnitSlotRecord
layouts. Reserved PROT_NONE pages make the specifically invalid selected-stack
reads deterministic failures if the nonhuman short circuit is broken.

The refactored body matches all 22 original cases under GCC 13 and Clang 18 at
O0/O2, with strict warnings and UBSan; packed alignment is excluded under the
existing project policy. The untouched parent matches 18 defined cases. One
additional case uses in-range signed arithmetic but exposes its defined
negative-int-to-uintptr conversion: the opaque callback pointer is sign-extended
instead of preserving the original low32 value. No pointer is dereferenced on
that mismatching callback boundary. Three paired high-index/arena cases are
excluded from parent execution for signed stride overflow. Some also carry the
separate opaque-pointer adaptation difference; those reasons are not conflated.

The saved-arena interpretation is corroborated by eight original refresh/UI
wrapper experiments, including callbacks that clobber ECX and mutate live
gameData. Their measured provenance is recorded separately from the enclosing
function oracle. The native test does not claim real child selection or rendering
behavior from its boundary stubs. Mouse interaction, rendering fidelity and
campaign milestones remain separate runtime gates.
