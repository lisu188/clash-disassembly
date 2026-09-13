# Road construction: class-extraction readiness

Track: Win95 reconstruction; frontier: the requested behavior-class migration.
The ten `RoadConstruction` identities remain procedural because `Road_Build`
exposes an unresolved original-state contract. No algorithm or backing bytes were
changed. The first-Road endpoint remains valid for its mapped approach overlay.

## Unassigned approach overlay

In `src/buildings/00422B50_004254E0_buildings_005.cpp`, `Road_Build` declares
`bridgeApproachOverlayId` at line 890, assigns it for twelve values at lines
1051–1115 and reads it at lines 1119–1120. The preceding
`MapTile_HasAlignedBridgeApproachRoadOverlay` predicate deliberately scans 48 live
DWORDs from the 706-byte Road backing. That scan overlaps other lookup values,
bounce offsets and the north marker. Its accepted domain is wider than the
twelve assignments.

The first twelve values are 544, 549, 564, 569, 576, 581, 546, 547, 566, 567, 578
and 579. Other accepted values include 872 at index 33; 0, 4 and 8 in bounce
storage; initial marker coordinates 416 and 400; 1 and 27; and later live marker
coordinates. The actual predicate accepts these when terrain and direction match.
The Road body then reads its unassigned local. Truncating the scan to twelve
entries would violate the established overlapping-storage contract.

The original procedure at `0x00424400` confirms the unresolved path
(`clash95.asm:55951`, through line 57068). Its `var_1C` stack slot has no initial
write. Twelve branches at `0x424A04..0x424A93` assign the supported approach
overlays. Unmatched values reach `loc_4245DE`, which reads that slot and stores
its low word at target tile +4. This evidence does not justify a zero fallback.
The public map spelling is `Road_Build`, segment offset `0001:00023400`.

## Bounded proof and limits

The WSL reproducer compiles all ten actual Road bodies, the actual lazy
`WorldMap_EnsureBuilderWidgetTables` initializer and actual `Debug_Log`. Movement
cost records the provisional overlay then returns zero; any later movement,
AP or UI boundary aborts if reached. Callback addresses remain ordinary four-byte
table entries. The probe retains the 53-byte widgets and complete 706-byte region.

Twenty-one scenarios run under GCC 13 and Clang 18 at O0/O2, with default, zero
and pattern local initialization: 252 case executions. All twelve assigned
controls produce their expected overlays in every profile. For nine unsupported
accepted values, zero initialization produces 0; GCC pattern initialization
produces 65278 and Clang produces 43690. Default observations vary. These are
diagnostic undefined-value observations, not assertions about original output.

Every call checks the full 800,000-byte game image, all Road bytes, 322 builder
widget bytes, selected index, callback count and move-cost observation. After
cancellation only the existing target turn stamp changes to 6; the target Road
word is restored. No RNG, allocation, release or movement is reached.

Confidence is high for the missing assignment, accepted live-table values and
controlled execution path. Authentic map/UI reachability of the unsupported
terrain/overlay combinations remains unknown. The established first-Road route
uses mapped overlay 567 and is not invalidated by these probes. Origin
`1b8b4b8e25558a5b0494c2889f11a1368b65eeef` preserves all ten body hashes; its
separate Road modal-loop changes do not resolve this contract.

The later `55872f9` Road-body readability/AP-arithmetic recovery changes its body
hash and source locations; the locations above refer to the frozen `1b8b4b8`
version. The revised body explicitly retains the uninitialized local for other
true predicate results. Its independent original probes likewise observe stack
dependence for unsupported mapping values. See
[the upstream recovery](HUMAN_READABILITY.md#batch-12-road_build). The class
readiness blocker remains; no zero fallback or narrowed scan was introduced.

Before this family advances, establish either an authentic-state invariant that
excludes these combinations or evidence for the original fallback stack value.
Do not initialize the local, clear live markers, narrow the scan or move lazy
initialization as part of architectural migration. Any repair needs its own
assembly-backed batch.

## Evidence

Local evidence: `artifacts/cpp-classes/20260908/road-readiness/`. The complete
archive includes exact canonical bodies/hashes, seven-header closure, original
assembly, commands, all initial and final probe outcomes, and the later origin
recheck. The private archive-verification.json verifies every archive member
against its source hash. No scratch files or historical evidence were removed.

The frozen original scratch can be rerun in WSL:

```sh
cd /var/tmp/clash95-road-class-readiness-b1fnuqwo
python3 run.py
```

This is a readiness audit, not a class extraction or gameplay recovery gate.
