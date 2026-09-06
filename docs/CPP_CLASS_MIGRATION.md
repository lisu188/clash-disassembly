# Game-system class migration

Track: Win95 reconstruction. This commit establishes the class-migration
foundation from `6f7537268e784c538133b714e3ccb77cf54052e4`; it does not migrate
game behavior or advance campaign/visual acceptance.

All 4,157 identities have explicit dispositions: 1,849 intended game methods
across 116 classes, 22 retained utilities/boundaries and 2,286 excluded library
implementations. Four declaration-database helpers remain separately accounted
without invented addresses. Class ownership describes the reconstruction's
organization, not original object layout proof.

The schema-3 manifest records canonical definitions separately from future ABI
adapters and pins the ordered 140-source CMake inventory. Historical names,
addresses, linkage and body hashes are unchanged. Shared indexing, hash,
declaration, source audit and coverage tooling resolve qualified out-of-line
methods without counting adapters as implementations. Coverage retains the
718-function set, 89.7% floor and zero-uncovered requirement, and rejects a
required identity with no executable lines. Class headers cannot hide behavior
or canonical dependencies in inline helpers, macros or initializers.

The new migration surface comparator pins legacy archive identities, linked
symbols, named storage bytes/relocations/order and initialization profiles.
Only explicit reviewed method/accessor/adapter text additions may be allowed.
Existing warning, header, link and coverage baselines are not reset.

Frozen GCC 13 and Clang 18 production builds and all eight asset-free gates pass.
GCC native: 1,059 passes, zero assertions and 530 isolated crashes; coverage is
6,169/6,662 (92.60%). Clang native: 1,059 passes, one existing assertion and 529
crashes. The existing assertion is
`cov5_01_getallowedattrtoken.allowed_symbols` (returns -1, expected 2).
Historical link differences remain 427/679 and header differences remain 14.

Private logs, exact commands, immutable hashes, snapshots and failed attempts
are under `artifacts/cpp-classes/20260906/baseline/` and `baseline-rebuild/`.
The WSL restart cleared temporary builds; both reference profiles were rebuilt
from all 693 unchanged source files in persistent `/var/tmp`, and match their
saved surface snapshots without allowances. Retail assets are never committed.

The next stage is the four-query UnitStack/QueuedPath extraction, followed by
separate class-file relocation, differential gates and headless route evidence.
Remaining stages cover world/construction, buildings/battle, strategic and
persistence, rendering/media, application/SDL, then the full integration matrix.

## Four-query extraction

Four canonical implementations now belong to borrowing UnitStack and QueuedPath
classes, defined out of line in their original translation units. Original ABI
adapters retain their names/signatures and explicit retention. These are the
current-AP minimum, readiness, builder and first-waypoint queries. Original
algorithm order, sentinel behavior and unknown bytes remain intact. Constructors
only bind addresses. Local alignment-one alias views preserve packed word loads.

Production-source differential tests compile the frozen before bodies, actual
canonical methods and ABI adapters under GCC13/Clang18 at O0/O2. Each profile
checks 6,176 stack and 38,928 path cases across 16 alignments, complete 725-byte
records and guards. Alignment trapping applies to the canonical methods and
adapters; the historical reference retains its original x86 access contract.
The next separately reviewable step relocates these unchanged methods into
class-named files while retaining their adapter/storage anchors and source order.
