# Builder-menu instruction fixture

`contract.py` defines 62 scripted scenarios and a fixed-width recording format.
Its expected outputs were measured from unchanged original menu instructions
and the original six-entry absolute jump table, under explicit recording
boundaries. `provenance.json` retains the input, per-case output and complete
output hashes, both local PE range identities, exact original code/table ranges,
and the separate 16-case execution of the original animation, HasBuilder and
button-sound callees establishing preserved ECX on the no-builder path.

Public CI runs `tests/tools/test_builder_menu.py` without a retail executable or
game assets. It extracts the actual canonical menu, selector and initializer
bodies and checks GCC 13 and Clang 18 at O0/O2 with strict warnings and UBSan.
Packed alignment is excluded, matching the existing recovered-layout tests.
The common trace contains 743 callback events, complete recorded argument words,
live selected/action/arena/render state, raw handler return and bounded arena and
render fingerprints. Expected event bytes are never constructed from a second
implementation of the menu.

The native template additionally checks both real reconstruction initializers,
cold independently poisoned backings, nonzero warm guards 1 and -7, warm live
mutations, first-use timing, rejected-entry preservation, table sentinels,
callback/text identities and the native diagnostic. Original static tables and
rejected native cold buffers are intentionally not compared as equal initial
states. The existing original Builder/Road fixtures establish the 322/706-byte
templates and the physical selector order 0,2,1,3,4,5. The main-table reference is
captured from its unchanged real initializer with independently checked callback
and sentinel identities; this is a menu-seam regression, not a new claim of full
original main-table byte parity.

All pointer normalization validates the observed address before assigning an
identity. The render backing retains and verifies original low byte 0xD8 for
the Dig boundary. The recovered integer ABI truncates the local no-builder copy
pointer; the native fixture reconstructs it only inside the actual stack's
high32 window and checks all three copied DWORDs and the precise global-array
end. The unused Trap ECX-shaped slot must be explicitly zero in native code;
original ECX is not fabricated as zero. Signed minimap coordinates retain their
low32 sign-extended values.

The original instruction oracle covers 48 scenarios whose parent C execution is
defined. Of those, 42 match the untouched parent; six noncanonical constructor
return cases expose the original exact-1 predicate versus parent truthiness.
The other 14 cases exercise no-builder/Trap undefined arguments or wrapped
address arithmetic repaired in the current function and are excluded from
parent execution. The six noncanonical BOOL scenarios are boundary-domain
probes: they do not establish that a real constructor returns those values.

These are controlled callee-boundary observations. Actual child building/dig
gameplay, mouse interaction, rendered-menu parity and campaign progress require
their separate runtime and original-frame gates.
