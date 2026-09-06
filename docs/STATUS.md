# Current Status

Last consolidated: 2026-09-06.

## Road Direction Dispatch Readability

Track: Win95 reconstruction, the reached Road handler family.
`RoadBuildMode_BuildInSelectedDirection` (`0x4254E0`) now uses the existing
widget record's named sprite field, preserving reads after animation and the
build/hook/redraw order. All 128 original valid-selector traces and 112 separate
canonical unsupported-selector traces match the before and after bodies in
four compiler profiles. The original unsupported-selector ambiguity remains.

Both builds, all eight public asset-free gates and 141 tooling tests pass; only
this handler's executable section changes. Warnings, all 4157 identities and data layouts
remain unchanged. The first-Road runtime baseline and turn-7 blocker remain;
no runtime or campaign milestone advances. Evidence, exact commands, confidence
and limits: [HUMAN_READABILITY.md](HUMAN_READABILITY.md#batch-8-roadbuildmode_buildinselecteddirection).

## Bare Bridge Candidate Readability

Track: Win95 reconstruction, the reached mission-05 Road helper family.
The ninth individually reviewed helper, `MapTile_IsBareBridgeCrossingRoadOverlayCandidate`
(`0x424120`), now uses named tile fields, single neighbor reads and explicit
border/terrain checks. Its exact `877..948` remainder rules and raw low-value
acceptance remain unchanged. Two signed-comparison warnings are removed per
compiler. All 1,677,926 original-instruction cases match both the frozen before
and actual after bodies across four compiler profiles.

Both builds, all eight public asset-free gates and 139 tooling tests pass; only
the reviewed function's executable section changes. All 4157 identities and data layouts
remain. Existing link/header ratchet failures are retained without baseline
changes. The first-Road runtime baseline and turn-7 continuation blocker remain
unchanged; no route or visual milestone is promoted. Exact commands, public
regression, confidence and limits:
[HUMAN_READABILITY.md](HUMAN_READABILITY.md#batch-7-maptile_isbarebridgecrossingroadoverlaycandidate).

## Road Normalization and Numeric Cleanup: Combined Validation

Integrated the shared Road lookup repair `8df94c4` with numeric cleanup merge
`431e4c5`, retaining both histories and every independently reviewed change.
Both final compiler builds, all eight public asset-free gates and 137 tooling
tests pass. All 4157 recovered identities, defined symbol addresses/layouts and
executable code/data match the repaired binaries used by the fresh first-Road
replays. Only build-id and ELF section-table metadata differ. Rebuilt-source
warning categories do not increase; raw link/header ratchets remain red without
baseline changes. Final native coverage passes at 6167/6662 lines (92.57%), all
718 required functions and zero uncovered functions.

The normalizer now matches every uint16 tile ID, including the former invalid
locale-array lookup range. Fresh original/GCC/Clang state and frame evidence
retains the existing turn-6 first-Road endpoint and known HUD/fog differences;
mission 05 remains partial. A disk-full/WSL interruption was recovered with
lossless evidence compression and a user-authorized Ubuntu restart. All frozen
runtime evidence was independently rechecked afterward. Exact commands, merge
audit, metrics and limitations are in
[HUMAN_READABILITY.md](HUMAN_READABILITY.md#batch-6-shared-road-normalization-backing).

## Numeric Cleanup Integration

Combined numeric cleanup `5e64be0` with main's eight Road readability helpers at
`bf15255`. Both histories and all other cleanup are preserved; three overlapping
stride substitutions are superseded by main's typed/named expressions. The
independent source review checks the combined code and all 4,157 manifest body
hashes. WSL was unresponsive during integration, so the Linux validation below
remains evidence for the separate parent batches, with no fresh merged build or
runtime claim. See [MAGIC_NUMBER_RECOVERY.md](MAGIC_NUMBER_RECOVERY.md#main-integration).

## Recovered Numeric Constants: All Canonical Subsystems Reviewed

Track: Win95 reconstruction, behavior-preserving numeric naming. Replaced 1,988
numeric occurrences in 62 TUs, adding 90 private constants and reusing existing
macros/enums. The complete census covers all 140 canonical TUs, including small
integers and floats; remaining data/arithmetic and evidence deferrals retain
locations and context. All 4,157 function identities and historical hashes remain.

Both GCC 13 and Clang 18 preserve normalized object code, linked symbol layouts
and `.text`/`.rodata`/`.data` bytes exactly. Macro expansions retain exact tokens;
173 reviewed existing-enum substitutions account for the token differences.
Both builds, four public asset-free gates, 135 tooling tests and generator checks
pass. Existing link/header ratchet differences and native isolated crashes remain
unchanged; no baseline is raised. Both headless first-Road replays reach the
accepted turn-6 endpoint, and the final stack-helper supplement retains identical
linked code and data to the route-tested binaries.

No campaign or behavioral frontier is advanced: normal turn refresh and Road
continuation remain next, mission 05 remains partial, and direct-route completion
stays 6/20. Evidence, before/after counts, confidence, rejected candidates and
exact validation commands: [MAGIC_NUMBER_RECOVERY.md](MAGIC_NUMBER_RECOVERY.md).

## Road Function Readability Review

Track: Win95 reconstruction, helpers reached by mission-05 Road construction.
Ten functions have been reviewed individually: bridge approach, crossing cost,
overlay normalization input, connection-mask rebuild, all four directional
Road queries, the bare bridge candidate and the direction-dispatch callback.
Reused pinned tile/widget fields and removed redundant decompiler state.
The separately identified `819..861` normalization defect is now repaired using
the original shared Road backing and guarded initialization. All 65,536 tile IDs
and previously excluded directional queries match original instructions in four
compiler profiles. Both builds/public gates and fresh first-Road state comparisons
pass. The known HUD/fog defects remain in fresh original frame pairs. Link/header
ratchets remain red; removing the false locale reference drops one unused
208-byte table, with no baseline increase. Runtime/campaign milestones and the
turn-7 frontier remain unchanged.
See [HUMAN_READABILITY.md](HUMAN_READABILITY.md#function-review-road-helpers-2026-09-06)
for per-function evidence, exact commands and validation limits.

## Main Integration: GNU++20 Recovery and Strategic AI

Track: Win95 reconstruction; frontier: integrate completed work into `main`.
The GNU++20 migration and first-Road recovery are committed together with
upstream PR #87's strategic-priority return-value repair, signed regrouping
comparisons and matcher-completeness tooling. The incoming production-body
regression now runs as GNU++20 on both supported compilers.

Fresh GCC 13 and Clang 18 builds and all eight asset-free gates pass. The final
tooling suite passes 120/120; coverage is 6169/6662 lines (92.60%) across all 718
required functions. The final native run has 1061 passes, zero assertion failures
and 528 isolated crashes out of 1589; the initial 1059/530 run is also retained,
without claiming new recovered contracts. Warning checks pass at 6618/6628; existing
raw link/header failures remain at 427/679 and 14 differences. No baseline is
raised, and full GitHub CI is not green. The load-sensitive first tooling
attempt and unfinished work are preserved.

The final default headless suite reports 11 passes, two existing first-mission
selection failures and eight skips. Menu Exit and castle economy pass in this
run; historical timing failures are not declared fixed. Restored-header
rebuilds reproduce both production executable/archive hashes exactly.

No campaign endpoint or visual-fidelity claim advances. The first-Road endpoint
below remains the highest compared C++ state. Integration commits, exact
commands, history audit, preserved worktrees and validation limits are recorded
in [INTEGRATION_20260906.md](INTEGRATION_20260906.md).

## Builder Road Menu: Original-Matching First Construction

Track: Win95 reconstruction, the actual Building → Road action reached by
mission 05. The main Building widget now calls its recovered handler. Restored
the original signed widget selector, action initialization, Road overlay hook,
movement-cost/AP comparison and refresh arguments. Recovered the complete
322-byte builder table and shared 706-byte Road region, including the 48-DWORD
scan's overlap with live marker data. The newly reachable Building family also
needed its missing packed table/strings and two original four-byte callback
stores. These defects predate the C++ cutover. Seven recovered bodies change;
all 4157 manifest identities remain, with two separate initialization helpers.

Both final GCC 13 and Clang 18 replays complete the seven-leg approach, open
Building → Road, build west and automatically move stack 4 to `(49,50)` on
turn 6. Origin/target roads are 867/879, minimum AP is 2, the active path is empty
and visibility is 228 tiles. All ten raw 31-byte unit slots, the checked stack
fields and every visibility byte match the original before/after this action.
Final visibility SHA256:
`6a3c5de203b5c40db4ab8c442f3a65017cd0eee2fb9971d727148d012a7fd4b0`.
Inactive path storage and other world-memory differences remain retained;
whole-stack and whole-memory equality are not claimed. The original uses real
Load of an unchanged engine-authored turn-6 checkpoint, not a continuous original
turn-1 replay. Both final runs retain 20 DAT/FAC files and 15 frame checkpoints.

Fresh full-frame pairs use viewport `(47,48)`, cursor `(192,176)` and selected
stack 4. Unmasked MAD is 11.223533/255 (GCC) and 11.181731/255 (Clang), with
286575/285835 differing pixels of 307200. Bridge placement aligns; missing
coordinate labels, displaced badges, missing squad/status panels, garbled lower
text and fog/water differences remain. No visual-equivalence claim follows.

Both clean builds and all four public asset-free gates pass. All 107 tooling
tests pass; the focused regression checks 672 original-measured cases in four
compiler profiles, complete data and callback relocations. Warnings are
6619/6629. Raw link/header ratchets remain red at 427/679 and 14 differences;
no baseline is raised. Common linked data retains name, class, size and relative
order; deliberate additions and removal of obsolete fragment storage are fully
enumerated. Native results remain 1059 passes, zero assertion failures and
530 isolated crashes out of 1589. Coverage is 6167/6662 (92.57%), all 718 frozen
functions covered. The default runtime suite retains the same 10 passes, three
first failure markers and eight skips. See [UNIT_TESTING.md](UNIT_TESTING.md).

The new [first-Road partial probe](../tests/first_campaign_arc_routes/mission_05_first_road_probe.env)
is the highest compared chronological C++ endpoint. Normal turn refresh and
the remaining bridge are next. A separate original-only run reaches `(47,58)`
on turn 10; C++ arrival, tactical entry, objective completion and automatic
campaign advancement remain unproven. Mission 05 remains partial; direct-route
completion is still 6/20. Confidence is high for the bounded original instruction,
data and first-construction comparisons. Exact commands, all attempts, source
freezes, independent reviews and paired frames:
`artifacts/runtime-recovery/builder-road-menu-20260906/`.

## Manual Water Crossing: Original Movement Restrictions Restored

Track: Win95 reconstruction, the crossing reached by mission 05. Removed three
unsupported builder exceptions: bridge-enable brackets around ordinary and shrine
path generation, and the queued-movement bypass of a zero terrain cost. Original
manual calls at `0x4090F6` and `0x409A6C` have no such brackets; execution at
`0x4109B6` tests the terrain cost and branches directly on zero. Both installed and
repository PE instruction ranges agree. Genuine strategic crossing toggles,
ordinary roads and the original clear/requeue branch remain intact. Two recovered
body hashes and their generated usage catalog change; no identities or layouts do.
The removed behavior predates this repair; it is not justified by the C++ cutover.

Both fresh GCC 13 and Clang 18 builds pass all four public asset-free gates and
retain all 4157 recovered symbols and the checked linked symbol/data profiles.
Warnings remain 6624/6635. All 105 tooling tests pass; generators are current.
Existing raw link ratchets remain red at 343/595 differences and the header ratchet
retains nine. No baseline is raised. The default runtime suite retains the same
10 passes, three failures and eight skips. Native results are unchanged: 1059
passes, zero assertion failures, 530 isolated crashes out of 1589; coverage is
6169/6662 (92.60%), with all 718 frozen functions covered. See
[UNIT_TESTING.md](UNIT_TESTING.md) for these limits.

Both repaired compiler routes replay the seven-leg prefix and reject ordinary
movement from `(50,50)` onto unbuilt water `(49,50)`, exactly as the original does.
The stack remains on turn 6 with 6 AP, no path and all 1300 visibility bytes
unchanged (222 visible tiles). Pre-action markers and observed saves establish
the rejected order; no confirmation or state shortcut follows. Fresh original
comparison uses the real Load restart described below. Full 640x480 rejection
frame pairs have unmasked MAD 11.940913/255 (GCC) and 11.933695/255 (Clang), with
285542 and 284573 differing pixels. Missing labels, damaged squad/status panels,
displaced badges and differing water/fog presentation remain unresolved.

The original's authentic Building → Road action subsequently installs road
overlays 867/879 and moves stack 4 automatically to `(49,50)`, spending four AP.
This original-only construction reaches 228 visible tiles and 2 AP. The next
unbuilt-water Road action requires normal turn refresh: its highlight gate needs
at least 6 AP. C++ construction parity and the rest of the crossing are unproven.
Historical builder-transfer crossing claims relied on the removed exceptions
and cannot establish authentic crossing behavior. Their evidence is retained.

Confidence is high for the bounded original instruction comparison, repaired
rejection and original Road action. Source snapshots, exact commands, all gates,
independent reviews and paired frames:
`artifacts/runtime-recovery/manual-crossing-20260906/`.

## Campaign March: Original-Matching Turn 6 Land Approach to (50,50)

Track: campaign validation. The new sixth and seventh partial probes extend the
chronological C++ prefix from `(55,53)` through `(52,53)` to `(50,50)`. Both
nation-score compiler builds pass, and the repaired builds repeat the endpoint.
The sixth path costs 14 AP and leaves 1 AP on turn 5 with 197 visible tiles.
After normal turn-6 refresh, the seventh path costs 14 AP and leaves 6 AP with
222 visible tiles. Named unit fields, complete paths and all 1300 visibility
bytes match the original. Final bitmap SHA256:
`9d4f099dc0ad7a6675e5fbf7d7510ac148ef70239edd829739031253d1b28284`.

For this batch the original restarts through its real Load menu using the
unchanged, engine-authored GCC turn-5 DAT/FAC. This is common-checkpoint evidence,
not a continuous original replay from turn 1. All 455 post-Load memory differences
are retained and classified as timers, water-animation words and rebuilt fact
pointers. Whole-memory and whole-world equivalence are not claimed.

The interrupted exploratory Clang run never reached its proposed water target;
its failure and all snapshots remain preserved. Final GCC/Clang seventh-endpoint
frame MAD is 11.636973/255 and 11.658742/255. HUD and fog defects remain. Three
successful route runs, both original sessions, frozen inputs, all observed saves,
105 passing tooling tests and independent state/frame audits are documented in
`artifacts/campaign-validation/mission05-arrival-20260906/`.
The highest chronological prefix is the
[visible-seventh-leg probe](../tests/first_campaign_arc_routes/mission_05_visible_seventh_leg_probe.env).
Mission 05 remains partial and direct-route completion stays 6/20. Full arrival,
stack 19 tactical entry, objective completion and menu advancement are unproven.

## Campaign March: Original-Matching Turn 5 Continuation to (55,53)

Track: campaign validation. Three new partial probes extend the two-leg prefix
through ordinary turn refresh and movement. Fresh original Wine and both
unchanged nation-score compiler builds agree on the new paths, checked fields
of all six occupied units and complete 1300-byte player-0 visibility bitmaps:

| Turn | Stack 4 endpoint | Minimum AP | Queued path | Visible tiles |
| --- | --- | --- | --- | --- |
| 3 | `(59,51)` | 0 | empty | 149 |
| 4 | `(56,52)` | 3 | `(55,53)`, cost 5 | 170 |
| 5 | `(55,53)` | 15 | empty | 179 |

The third path costs 20 AP. The next original path costs 22 AP, so normal AP
exhaustion stops before its final node. After turn 5 refresh restores 20 AP,
one own-stack click selects stack 4 and a second resumes its retained 5-AP node.
Final bitmap SHA256:
`1a32b78649b3827fba276530d427ff72b066fc7f36e86eaa2243658c05c21e4b`.
No AP, visibility, position, objective or save-state shortcuts are used.

Two longer replays exposed an input-order problem: the press was received
before top-menu entry, which requires a released button in the original.
The new shared End Turn fixture hovers, waits for fresh menu entry and a cursor
command acknowledgment from its input loop, then sends the ordinary host click.
Both final compiler replays pass all four turn transitions. Fresh banner counts,
the repeated third-leg event with 0 AP and the reused final save slot have
pre-action marks. Six recursive input files are frozen before/after each final
run. All 105 tooling tests pass. Game source, headers, manifest, driver and binaries remain
unchanged; prior nation-score build/native/runtime results remain their baseline.

The initial outer-wrapper editing failure, first-leg confirmation timeout and
both pre-handshake End Turn timeouts remain retained. A proposed 20-AP shortcut
was rejected: cult-place overlay 736 at `(56,53)` prevents ordinary traversal.
No pathfinding repair follows from that mistaken route proposal.

Fresh final original/Clang and original/GCC frames have unmasked RGB MAD
10.234354/255 and 10.230844/255, with 289562 and 289262 of 307200 pixels differing.
Missing labels, damaged squad panels and displaced badges remain. Other-stack
placement and fog appearance also differ; full-world state, RNG and animation
are not synchronized or proven equivalent. No whole-game visual claim follows.
The new highest route is
[visible-fifth-leg probe](../tests/first_campaign_arc_routes/mission_05_visible_fifth_leg_probe.env).
Mission 05 remains partial; direct-route completion stays 6/20. Full `(47,58)`
arrival, stack 19 tactical entry and objective completion remain unproven.

Confidence is high for these bounded path/state comparisons and the original
menu input order. Exact commands, all attempts, fresh original captures,
input hashes, audits and frame pairs:
`artifacts/campaign-validation/mission05-march-20260906/`.

## Nation Score: Original Accumulator Restored; Both Compilers Reach Second Leg

Track: Win95 reconstruction, the score calculation reached during mission05
turn processing. `AI_TickNationPostTurn` now accumulates each building value
instead of adding it to an uninitialized local. Original `0x43F3B5` adds to
ECX, which the actual building-value helper preserves. This defect predates
the C++ migration. Only this recovered body/hash changes; no symbols, layouts,
tables or public declarations change.

The actual original score and building helper execute together without
substitutions. All eight GCC/Clang O0/O2 profiles match 1020 cases, including
12 exact live input captures, on returns and unchanged game/metadata memory.
The repository PE and installed Wine executable have different full hashes;
both function ranges and all 40 licence costs are verified byte-identical.
The four unrepaired compiler profiles each disagree in 89 cases.

This is a bounded arithmetic repair. Existing packed-load alignment violations
are explicitly excluded from the sanitizer profiles. Three separate overflow
cases demonstrate original wrapping and remaining C++ signed-overflow traps;
full-range arithmetic and ISO-C++ portability are not claimed. The permanent
asset-free regression checks 308 measured cases across four compiler profiles.
One new native score registration preserves all 1588 previous identities.

The exact pre-repair Clang turn-2 input produces 510 in the original instructions
but returned 490186406 live, triggering the proposal. Every captured repaired
return matches the original on its own input. The fresh GCC and Clang turn-2
inputs both produce 508; population differs between runs, so full input/save
equality is not claimed. Both repaired builds bypass the spurious proposal
and complete the five-node, 18-AP second leg to `(63,49)`. Their checked fields
for the six occupied units and all 1300 visibility bytes match the original endpoint:
121 visible tiles, minimum 2 AP, turn 2, empty path.

Both builds, all four public asset-free gates and all 105 tooling tests pass.
Warnings are 6624 GCC/6635 Clang. All 4157 archive identities and complete
linked storage profiles pass against the prior reveal builds. Existing raw
link ratchets remain red at 343 GCC/595 Clang differences, and the header
ratchet retains nine. No baseline is raised. The full runtime suite retains
10 passes, the same three first failure markers and eight skips. Native
coverage/results and retained native failures are recorded in
[UNIT_TESTING.md](UNIT_TESTING.md). The native wrapper now defaults SDL video
and audio to dummy drivers for headless fixture execution.

Fresh endpoint pairs against the retained original frame have unmasked RGB
MAD 10.798779/255 (Clang) and 10.819302/255 (GCC), with 291961 and 292153 of
307200 pixels differing. Missing labels, corrupt squad strip and displaced
badges remain visible defects. No modal-rendering, full-march, tactical,
objective or whole-game equivalence milestone is promoted; direct routes
remain 6/20. Confidence is high for the bounded score correction and matched
second leg on both compilers.

Exact commands, original bytes, live inputs/returns, regression goldens, all
failures and paired frames: `artifacts/runtime-recovery/nation-score-20260906/`.

## Campaign Input: Second Mission05 Leg Matches the Original State

Track: campaign validation, the reached viewport driver failure. The pan helper
now releases each ordinary host arrow key before requesting and acknowledging
a fresh cursor/viewport sample. It also samples on entry and checks the final
allowed attempt. No game source, binary or SDL behavior changes in this batch.
The original repeats held keys; a read-only live trace proves the old driver
accepted an intermediate `(63,44)` sample while Up remained active. The camera
had already reached `(63,42)` and released Up before the driver's completion
line. The defect was stale evidence, not a key held at the next click.

All 17 new asset-free driver regressions pass against the actual canonical
helper; all 103 tooling tests and metadata/generator checks pass. The existing
header ratchet retains nine differences. The previous reveal batch supplies
the unchanged game's build/native/runtime baseline; those suites were not
rerun for this shell-only repair, and no baseline was raised.

Original Wine and the GCC build reach `(63,49)` in turn 2 through the same
five-node path, costing 18 AP. Four type-17 units finish with 8 AP and two
type-1 units with 2 AP; health, fatigue and morale match. All 1300 player-0
visibility bytes agree: 121 visible tiles. Two private candidate replays and
the canonical repeat pass. The first canonical attempt misses the initial
selection click before reaching the changed helper; it remains retained, so
complete input determinism is not claimed. The opt-in
[visible-second-leg probe](../tests/first_campaign_arc_routes/mission_05_visible_second_leg_probe.env)
retains partial mission status. No state shortcuts are used.

The original/GCC endpoint pair at viewport `(63,44)`, stack 4 selected, has
unmasked RGB MAD 10.701840/255 and 290967/307200 differing pixels. Missing
coordinate/index labels, damaged squad strip and displaced badges remain.
The original route includes a replaced, unexecuted path preview before the
intended second leg; the matched endpoint does not imply identical input count.
Full march, tactical entry, objective completion and visual equivalence remain
unproven. Direct-route completion remains 6/20.

The Clang candidate replay reaches a queen proposal instead of the human loop.
Source and both binaries contain an existing uninitialized accumulator in
`AI_TickNationPostTurn`; original `0x43F3B5` accumulates each building value.
The proposal threshold precedes portrait randomness. Its huge logged score
strongly supports this defect as the cause, but exact live turn-2 inputs were
not captured. Sparse frame dumps cannot establish missing modal rendering.
Recover that dataflow before continuing the march. Confidence is high for the
driver repair, matched second leg and assembly discrepancy; no game repair
for the score is included in this batch.

Exact commands, hashes, tests, original state/frame pair, all failed attempts
and audits: `artifacts/campaign-validation/mission05-input-20260906/`.

## Reveal Propagation: First Mission05 Leg Matches the Original State

Track: Win95 reconstruction, the reveal propagation reached by mission05's
first visible movement leg. `Map_RevealTileWithPropagation` now passes the
eight original midpoint coordinate pairs to recursive calls. Entry bounds,
mark-before-draw behavior, branch order and returns are preserved. The old
code passed uninitialized locals; a live trace catches parent `(65,46)`
calling `(66,3)` where original address `0x40EFCF` requires `(66,47)`.
Only one recovered body/hash changes. No names, storage or catalogs change.

Unchanged original PE instructions, including the real visibility helper,
validate 51,270 cases over six players, endpoint masks, edges and cascades.
All eight GCC/Clang O0/O2 profiles, with and without undefined-behavior traps,
match return values, entire bitmaps and successful-draw callback order.
The rendering boundary is substituted in that isolated probe; fresh original
and C++ game frames supply the separate runtime comparison. Permanent
asset-free tests exercise the actual canonical functions in four profiles,
and the existing native registration now checks eight-direction propagation.

Both fresh builds and all four public asset-free gates pass. All 86 tooling
tests and generator/metadata checks pass. Warnings fall to 6625 GCC/6636 Clang.
Coverage is 6171/6662 (92.63%) across all 718 frozen functions, none uncovered.
Native units retain 1588 identities: 1059 passed, zero assertion failures,
529 isolated crashes, with no new crashes. The sole case losing crash status
again survives filename-pointer truncation to null in the unrepaired CLIPS
file-output helper; two debugger calls confirm incorrect empty-name output.
That address-dependent survival is not a behavioral repair.

All 4157 raw archive identities pass, and both complete linked symbol/storage
profiles match the fog builds exactly. Existing public link ratchets remain
red at 343 GCC/595 Clang differences; the header ratchet retains nine. No
baseline changes. The full runtime suite retains the same 10 passes, three
failures and eight skips, with the same first failure markers.

Original and both C++ compiler builds take the same four-node, 20-AP path from
`(71,44)` to `(67,47)` in turn 1. The repaired 1300-byte player-0 visibility
bitmap matches the original exactly: 87 revealed tiles, including 15 newly
visible local tiles and no distant `(66,3)`. All occupied-slot AP, health,
fatigue and morale values agree; the final path is empty. The opt-in fixture
is [the visible-first-leg probe](../tests/first_campaign_arc_routes/mission_05_visible_first_leg_probe.env).

The same-state original/GCC frame comparison at viewport `(67,42)`, selected
stack 4, has unmasked RGB MAD 9.983345/255 and 289192/307200 differing pixels.
Small palette differences coexist with real squad-strip corruption, missing
coordinate/index labels and displaced badges. The coordinate-display setting
agrees, so missing labels are not a settings mismatch. No visual-equivalence
or mission-completion claim follows from the bitmap match.

Confidence is high for this bounded repair and first movement leg. Further
C++ route authoring reaches normal turn 2 and restored 20 AP, but camera drift
after the pan helper reports completion prevents the intended selection;
the second waypoint has not been ordered. Full march, tactical entry and
objective completion remain unproven. Exact commands, original bytes, tests,
debugger traces and integrity checks: `artifacts/runtime-recovery/reveal-20260906/`.
Fresh route, original and paired-frame evidence:
`artifacts/campaign-validation/mission05-frontier-20260906/`.

## Fog Classifier: Original Mask Restored; Mission05 Waypoint Rejected

Track: Win95 reconstruction, the reached fog gate exposed by mission05 replay.
`Map_ClassifyFogOfWarOverlayForPlayer` now constructs the original eight-bit
neighbor mask instead of discarding seven visibility results and reading
uninitialized locals. Original branch order, center shortcut and conditional
style write are preserved. This defect existed unchanged in frozen C. Only
one recovered body/hash changes; no names, storage or semantic catalogs change.

Unchanged original PE instructions, including the real visibility helper and
style setter, execute 67,584 cases covering every center/neighbor combination,
six players, eleven edge/interior positions and two incoming register values.
All eight C++ compiler/optimization/trap profiles match the original return and
style bytes exactly. The permanent asset-free test checks the actual canonical
classifier against the measured table and verifies call order. The existing
native registration now asserts exact results through actual visibility memory.

Fresh GCC13/Clang18 builds and all four public asset-free gates each pass.
All 84 tooling tests and generator/metadata checks pass. Warning ratchets pass
at 6633 GCC/6644 Clang warnings. Coverage is 6169/6662 (92.60%) over all 718
frozen functions, none uncovered. Native units report 1058 passed, zero
assertion failures and 530 isolated crashes, retaining all 1588 identities.
The only added crash versus the radix run is
`cov4_07_ccfo.a10_nonzero_open_success`. Paired debugger calls locate an existing
filename-pointer-to-char truncation in `Rules_OpenConstructCodeFile`: the old
address truncated to null and received the formatter's empty-string fallback;
the new address truncates to a non-null invalid pointer and faults in strlen.
The fog function is not reached. This remaining defect is recorded, not masked
by restoring a favorable allocation address or weakening the test.

Both linked symbol/storage profiles match pre-repair exactly; all 4157 raw
archive identities pass. Existing public link failures remain 343 GCC/595
Clang differences, and the header ratchet retains nine. No baseline was raised.
The complete runtime suite retains 10 passes, the same three failures and
eight skips. Fresh mission05 initial-save probes pass before and after.

The historical march does not pass: its first destination `(47,58)` and all
eight neighbors are hidden in fresh pre/post saves and the original's live
memory, whose player-0 visibility bitmaps match exactly. Original instructions
and the repaired C++ code correctly reject it. The original was loaded through
its real Load menu and panned with ordinary keys. Its current frame at mission5,
turn1, viewport `(67,42)`, selected stack4 at `(71,44)` is paired with C++ output.
Unmasked RGB MAD is 9.782720269/255, with 289047/307200 pixels differing.
Palette/capture timing differences remain; missing selected-unit strip,
misplaced labels and fog/terrain boundary differences are unresolved rendering
defects. No visual-equivalence or campaign milestone is promoted.

Confidence is high for this bounded classifier and the verified waypoint
rejection. Neighbor-reveal propagation, authentic march, tactical entry and
whole-game equivalence remain unresolved. Exact commands, original bytes,
frames, state observations, logs and integrity checks:
`artifacts/runtime-recovery/fog-20260906/`. Initial C++/frozen-C failures are
also retained in `artifacts/campaign-validation/mission05-cpp-20260906/`.
The "Next Target" below supersedes the old arrival-based route assumption.

## CRT Radix Formatter: Original Behavior Recovered

Track: Win95 reconstruction, the reached unsigned/signed radix formatter
family after the C++ cutover. Original assembly and unchanged PE bytes restore
the complete 37-byte digit table, the scratch region and its zero sentinel,
32-bit negation for negative decimal values including INT_MIN, and the saved
destination return. Two recovered bodies change; no symbols are renamed or
removed. The table intentionally grows from the erroneous one-byte recovery
to its original 37 bytes. This is behavioral recovery, not migration parity.

Direct execution of the original x86 instruction bytes validates 10,220 cases
across both entry points and bases 2..36. All output bytes, return pointers
and guards match the C++ candidate with GCC/Clang at O0/O2. A permanent
asset-free regression extracts the actual canonical functions and table;
all eight compiler/optimization/undefined-behavior-check profiles pass.
The existing native formatter case now checks exact strings and pointers.
All 4,157 recovered identities and 1,588 native registrations remain.

Fresh builds and all four public asset-free gates pass on both compilers.
All 82 tooling tests and metadata/generator checks pass. Warning ratchets pass
at 6636 GCC/6647 Clang warnings. Coverage is 6163/6663 (92.50%) over all 718
frozen functions, with none uncovered. Native units report 1059 passed, zero
assertion failures and 529 isolated crashes. Compared with the fresh pre-repair
C++ run, three cases lose crash status and none gain it; other CRT behavior
remains unresolved. Full linked name/order comparisons differ only in the
proven table size restoration. The unchanged raw link ratchet remains red at
343 GCC/595 Clang differences, and the header ratchet retains nine differences.
No baseline was raised.

Fresh pre/post runtime suites both report 10 passes, the same three timeouts
and eight skips: playability/attack at next-unit selection and castle economy
before the human turn. The latter has varied in older runs; it is not a new
formatter regression in this comparison. Fresh original Wine and C++ menu
frames retain the documented palette/cursor differences (RGB mean absolute
difference 1.560641276/255, 290923/307200 nonmatching pixels). Before/after C++
frames are exactly equal. An initial original capture under a leading-dot
directory faults in path normalization; a plain directory succeeds. Both
attempts are retained, and no platform palette or path behavior was changed.

Evidence, exact commands, original-byte probes, hashes, full logs and frames:
`artifacts/runtime-recovery/radix-20260906/`. Confidence is high for this
bounded formatter contract. No campaign or broader visual milestone advances;
whole-game original equivalence remains unproven. Earlier migration results
below describe the completed language cutover before this recovery.

## GNU++20 Migration: Completed

Track: Win95 reconstruction, the user-requested staged C++ migration. The
maintained build now enables only GNU++20: all 140 recovered TUs, support
sources, and 62 native unit TUs use `.cpp`. All 4,157 recovered identities and
1,588 native cases remain, with historical source/hash provenance preserved.
Generated headers, source inventories, CI, and coverage tools follow the
cutover. The 199 keyword replacements affect 93 bodies; no broad semantic
rename campaign or new unit/structure catalog entries accompany this work.

Both final compiler builds and all four asset-free gates each pass. All 81
tooling tests and generator/metadata checks pass. Warning ratchets pass at
6,637 GCC and 6,648 Clang warnings. Coverage passes at 6157/6661 lines (92.43%)
over all 718 frozen functions, with none uncovered. The native harness reports
1056 passed, zero assertion failures and 532 isolated crashes. Two existing CRT
thread cases exchange crash status versus frozen C; intermittent successes
are not claimed as repairs. The final default runtime repeat has 11 passes,
the same two playability/attack failures and eight skips. Its preceding run
also missed menu Exit input; three isolated C/C++ repeats and the complete
repeat pass that probe. Both attempts remain recorded.

Both archives pass all 4,157 raw symbol checks. All 5,321 non-private objects
retain their frozen C names, sizes, offsets, alignment, initializers,
relocations and relative order. Private storage moves, support aliases, and
four render-hook adapters are individually accounted for. The unchanged raw
link ratchet still fails (341 GCC/593 Clang differences versus frozen C's
205/111); the header ratchet retains nine differences. No baseline was raised.
Original assembly supports the accompanying malformed-argument repairs and
the pool unlink correction that frees the removed pool rather than a live
neighbor. These are deliberate corrections to erroneous C behavior, distinct
from mechanical conversion parity.

Fresh settled C and C++ menu frames are pixel-identical. The original Wine
comparison retains palette/cursor differences: RGB mean absolute difference
1.560641276/255 and 290923/307200 nonmatching pixels, without masking. Original
equivalence, broader visual fidelity, and campaign completion remain unproven.
See [the migration record](CPP_MIGRATION.md) for exact scope, repairs, gates,
and local evidence under `artifacts/cpp-migration/20260905-a/`.

## Modularization And Branch Integration

Track: Win95 reconstruction, integration of the consumer shared-state headers
with current upstream recovery. Local recovery and tooling are retained in
`c7eb39d`; `9854c0c` merges upstream `870caee`, and `a2be4b7` merges the remaining
human/AI outcome-table naming correction. All 14 local branch tips are now
ancestors of main. The classifier and render repair history merges add no tree
changes because their implementations were already present.

The combined vision-radius function keeps upstream typed stack traversal and
the recovered full unit metadata reads. Independent actual-parent source and
assembly review confirms that composition. Eight other manifest mismatches
were stale upstream hashes from the packed-pointer alignment repair; their
bodies match upstream exactly. Only those nine reviewed canonical hashes were
refreshed during upstream integration. Naming then changes six outcome-table
globals and the `isHumanPlayer` local without changing storage or control flow;
the link baseline changes symbol identities only. The religion-axis labels
remain tentative. No warning, header or coverage limit was raised.

Generated interfaces cover 4,157 functions in 140 TUs. Shared declaration
exposure is now 11,965, with the same 241 shared globals. The small change from
the rollout's 11,994 follows upstream strategic-local renaming that removes a
false shared-name match. Generated headers, TU includes, ownership and visibility
checks pass; the same two API and seven peer-edge ratchet failures remain.
All 45 tooling tests and metadata/generator checks pass. Fresh GCC 13 and
Clang 18 builds compile/link and pass all four asset-free gates each. Both
warning ratchets now pass (9,345 GCC warnings; 9,387 Clang warnings). The link
ratchets retain exactly the prior 205 GCC and 111 Clang differences, with zero
manifest cross-check errors. Both complete linked profiles match the previous
rollout after normalizing the six approved symbol renames; this comparison
does not imply instruction parity with upstream recovery.

The default headless GCC suite reports 10 passed, 3 failed and 8 skipped.
Playability and attack again stop at `next_unit_selected selected=1 a=31 b=44`;
castle economy stops at `human_turn_enter idx=1 owner=0 tile=31,44`. These exact
first failure markers match retained pre-rollout logs; no additional parent
runtime rerun was made in this integration. No new full-suite pass is claimed.
The fresh unit harness reports 1,058 passed, zero assertion failures and 530
isolated crashes. Its crash set is a subset of the rollout's 532: padded-hex
formatting and the CRT thread case pass in this run. This is not evidence that
their unresolved CRT behavior was repaired. The known timezone case still
crashes, and the CTest wrapper's pass tolerates isolated crashes.
Coverage passes the unchanged floor at 6,145/6,650 lines (92.41%) across all
718 frozen functions, with zero uncovered functions. The unit registry still
contains all 1,588 cases; the upstream extra index-222 assertion is retained.

The incoming CLASH.DAT checks pass, including stock CLIPS loading of the
recovered program: 95 rules, 6 globals, 89 deffunctions and 24 classes, with 82
host stubs. The LHS recovery translates 420 of 753 matcher tests; 333 remain
unresolved. These are decode/load checks, not gameplay-equivalence evidence.
The existing upstream fixture is unchanged. Clean-checkout documentation links
were repaired without weakening the checker or discarding private evidence.

Campaign work remains separate: `1789aa5` retains the partial mission-11 probes
and the mission-05 tactical boundary correction recovered from the unique
stash. The old exchange choreography stays opt-in pending fresh validation.
No route, campaign or visual-fidelity milestone advances in this integration.
All stashes and secondary worktrees are preserved, including the unfinished
HD/resizable-window feature and older diagnostic drafts. The retained campaign
frontier remains the mission-05 route in "Next Target" below.

Exact commands, conflict decisions, actual-parent body comparisons, naming
proof and branch/worktree inventory are local evidence under
`artifacts/integration/merge-all-20260905/`. Earlier batch results below remain
historical; their object-parity claim does not extend to the incoming upstream
recovery changes.

## Structure Recovery: Tactical Slot Consumers

Track: Win95 reconstruction, the 31-byte unit record used by mission-05
tactical panels. `BattleUnitEntry` now names fatigue at +10 and morale at +11.
Both 31-byte transfer directions and independent panel assembly loads confirm
these fields. Storage stays unsigned; signed numeric consumers retain explicit
casts. The generated catalog remains 21 structures, now with 181 layout pins.

Typed fields repair five stance-related reads in three functions: the selected
battle panel and the melee/defence icon helpers. The previous short-pointer
arithmetic read byte +24 instead of the original +12. A regression varies the
unrelated tail byte and tests the original signed morale arithmetic. No
function, enum or unit type was renamed; remaining opaque spans are preserved.

The recorded GCC 13 and Clang 18 builds compile/link and pass all four
asset-free gates. Generated structures, metadata, subsystem headers and all
140 TU include blocks passed freshness checks at that gate. A concurrent
consumer shared-state header rollout appeared afterward; these results do not
validate that separate rollout. The unit harness reports 1058 passed, zero assertion failures and 530
isolated crashes; both added cases pass. Coverage is 6144/6649 lines (92.40%)
across all 718 frozen functions, with none uncovered. The crash count matches
the prior run but one existing CRT thread case replaces one timezone case in
the crash set; this is recorded, not treated as unchanged test behavior.
The first test build caught a packed
fixture alignment error, corrected by aligning its backing storage without
changing gameplay code.

An optional `CLASH95_GAME_ROOT` now permits private engine-authored saves.
The initial mission-05 snapshot and a fresh current-binary world probe pass.
The original loads that exact DAT/FAC pair through its real Load menu and
reaches the mission banner. Installed saves, executable bytes, staged work and
all warning/header/link/coverage baselines remain unchanged.

Fresh tactical entry remains unproven: the sparse-capture replay passes the
earlier viewport step but stops on turn 2 after a Next Unit click is missed.
No campaign route or tactical visual milestone is promoted. Evidence, exact
commands, failed attempts and next comparison state are under
`artifacts/structure-recovery/tactical-validation-20260905/`. Continue from
that evidence with observed input acknowledgements and the verified original
save; the popup pointer/render defects and metadata +38..+69 remain deferred.
Three attempts to capture the reconstruction's matching opening banner
produced no presented frames within their checkpoints, including after the
later cursor-bounds marker. A matching original/reconstruction pair remains
unavailable; the initial world frames must not be substituted for the modal.
That batch's final Markdown path check flagged a placeholder header filename
in the concurrently edited `docs/SOURCE_LAYOUT.md`; the shared-state rollout
below subsequently replaced it with an existing example path.

## Shared-State Modularization: Consumer Headers Active

Track: Win95 reconstruction, generated shared-state interface boundaries.
Eleven generated consumer headers now expose only each subsystem's referenced
shared declarations. Across 136 consumer TUs, declaration exposure fell from
32,776 to 11,994 (63.41%); the same 241 shared globals remain. The state
definition group and unit-test aggregate retain the complete shared header.
The measured surface records referenced versus visible DB identities, and the
audit checks slice ownership and consistency. The generator validates every
selected include block before writing and preserves surrounding source bytes.

After Ubuntu became available, all 45 tooling tests passed and regenerated
headers plus all 140 TU include blocks passed freshness checks. GCC 13 and
Clang 18 clean builds and all four asset-free gates pass. All 140 normalized
recovered object disassemblies and linked symbol addresses, sizes and order
match each compiler's pre-rollout baseline. All 1,180,500 preprocessed body
tokens match. Full-stream differences are limited to unchanged shared
declarations and their balanced generated strict-prototype warning wrappers.

The default headless GCC suite reports 10 passed, 3 failed and 8 skipped.
Main-menu Exit, boot/direct routes, shutdown and save-DAT checks pass. The
playability, attack and castle-economy probes time out on the same markers
with both the new and preserved pre-rollout executables. These existing probe
blockers keep the full default suite red; opt-in skips are not passes.

Coverage passes at 6144/6649 lines (92.40%) across all 718 frozen functions,
with zero uncovered functions. The unit harness reports 1056 passed, zero
assertion failures and 532 isolated crashes. All 530 prior crash names remain;
two additional cases crash in this run. The CTest wrapper tolerates isolated
crashes, so its pass is not a claim that every unit case succeeds.
Focused probes show the timezone case already varies in the earlier binary.
The padded-hex case reproducibly differs between the two coverage binaries
even with matched paths and environment, despite identical instructions in
the relevant helpers. Its fault reaches an existing one-byte formatter buffer
overrun. This difference remains explicit validation debt; the unit comparison
uses the preceding tactical batch, not a dedicated pre-rollout coverage build.
CRT recovery is deferred, and unchanged unit-harness behavior is not claimed.

Confidence is high in mechanical preservation: recovered source bytes outside
the generated blocks, storage, old headers, manifest and staged work match the
refreshed dirty baseline. Concurrent tactical-structure edits were preserved
and incorporated into that baseline before cutover. No functions, globals,
structures or fields were renamed. The two API and seven peer-edge ratchet
failures, plus each compiler's warning/link ratchet failures, are unchanged;
no saved limit was raised. Campaign status and visual-fidelity claims do not
advance in this header-only batch.

Evidence, failed attempts and exact commands are under
`artifacts/modularization/shared-state-20260905/rollout/`; the earlier WSL
access failure remains recorded in its parent directory. See the
[shared-state validation procedure](BUILD_AND_TEST.md#shared-state-header-rollout).

## Structure Recovery: Linux Validation

Track: Win95 reconstruction, validation of the recovered unit metadata and
its consumers. WSL execution returned for this batch. Fresh GCC 13 and Clang 18
builds compile and link, and both pass all four asset-free CTest gates. Full
subsystem header regeneration and TU include checks now pass. The earlier
WSL/header-pending notes below describe the preceding batches.

Regeneration exposed three false slider globals. Their values now alias the
original 112-byte backing at +12/+48/+84, preserving three 36-byte records and
the final sentinel. Assembly corroborates the layout. Four metadata indices
now explicitly retain the original signed-byte extension, removing the four
warnings introduced by this recovery. No unrelated function names changed.

The corrected unit harness reports 1056 passed, zero assertion failures, and
530 isolated crashes; the crash names exactly match the prior readiness run.
All nine added cases pass. Coverage is 6144/6647 lines (92.43%) across all 718
frozen functions, with zero uncovered functions. Both original PE copies still
match the recovered metadata; generated structs/constants and the split audit
pass. There are 21 generated packed structures and 179 size/offset assertions.

The headless reconstruction reaches a nonblank main menu and exits through
the real button. Original Wine debugging proved that the sampled entry code
mapped as zeros from the Windows-backed filesystem. A byte-identical copy on
Linux-native storage executes the correct startup jump. A Wine virtual desktop
then resolves the observed `DDERR_UNSUPPORTED` display-mode failure and reaches
the original English main menu. The fresh 640x480 comparison has mean absolute
RGB difference 1.560641/255 and 290923 nonmatching pixels (94.70%), including
widespread small color differences outside the cursor positions. No full
visual-equivalence claim is made. Tactical panels and gameplay fidelity are
not established by this menu checkpoint.
The existing `PlatformDac6Channel` conversion explains every sampled non-cursor
color difference; its QEMU Win98 reference and the current Wine palette output
remain distinct comparison environments. No platform palette code was changed.

Header-surface limits still reject two API count increases and seven dependency
edge increases. Warning-category and linked-layout ratchets also remain red;
the four newly introduced warnings were repaired, while the other increases
already existed in readiness evidence. No warning/header/link/coverage baseline
or staged work was changed. No campaign route was promoted. Exact commands,
failed attempts, final results, and captures are retained under
`artifacts/structure-recovery/linux-validation-20260905/`.

Next structure/runtime frontier: validate mission-05 tactical panels against
the now-running headless original, while keeping the
opaque metadata +38..+69 and type-40 scoring boundary explicitly unresolved.

## Unit Metadata Pointer Recovery

Track: Win95 reconstruction, unit metadata for mission-05 tactical panels.
Recovered the 12-byte localized-name triplet structure: 34 triplets contain
102 original strings, with types 33/34 sharing one triplet. Both PE copies
agree on every pointer target. A native pointer companion now resolves all
name, resource-key and movement-stem targets; original 88-byte records remain
unchanged. All 35 unit types use the selected language and exact original font
bytes. Four English helper labels were corrected: Taran, Highlander, Cyklop,
and Pegaz.

Sixteen functions changed in this batch. Four obsolete pointer globals were
removed, 28 missing panel format arguments were recovered from assembly, and
the unit-info morale branch's lost slot pointer was repaired. Generated struct
overlays now contain 21 structures and 179 size/offset assertions. Regression
assertions cover language selection, byte encoding, shared names, distinct
keys, and reserved null pointers.

Static checks pass: both original pointer sets and independently decoded C
strings agree, the split-source audit passes, and only the 16 reviewed function
hashes changed. The 28 repaired format calls now contain their numeric argument.

At the end of this pointer batch, WSL returned `E_ACCESSDENIED`, leaving
compilation, tests and subsystem regeneration pending. The later Linux
validation above resolves those execution items; fresh matching original
frames remain required. No campaign route or visual milestone is promoted. Evidence and
commands are under `artifacts/structure-recovery/unit-metadata-pointers-20260905/`.

Next: validate the retained mission-05 tactical entry and panel output.
Existing panel coordinates/render calls and the
battle blend omission still need original-frame evidence. The opaque +38..+69
metadata span and type-40 combat-score boundary remain unresolved.

## Unit Metadata Structure Recovery

Track: Win95 reconstruction, unit metadata used by the mission-05 tactical path.
The backing now preserves all 40 physical 88-byte records: 35 initialized unit
types and five zero reserved records. Both original PE copies agree on all
3,520 bytes. The C layout now names vision radius (+70), corpse sprite base
(+78), and auto-resolve casualty weight (+87), and retains +38..+69 as opaque
initialized bytes. The public map symbol `unit_stats` identifies +87; the old
alias to the corpse byte was incorrect. The tactical-role parser claim was
also rejected because its evidence belonged to CLIPS class parsing.

Twenty-two functions now use the typed backing for tail scalars, movement
stems, combat-strength scoring and production roster presence. Thirteen false
standalone globals and the obsolete `unit_stats` declaration were removed.
The original 35-type roster and five reserved slots remain distinct.

Static verification reconstructs the C initializer bytes and matches both
originals; struct/constant headers are current, the split-source audit passes,
and only the 22 reviewed function body hashes changed. New regression assertions
cover original values, reserved roster slots, vision, corpse frames and
production gates. Linux builds,
tests and frame/route verification have not run: WSL still returns
`E_ACCESSDENIED`. Full subsystem usage/header generation is also pending;
only the required declaration text was synchronized. No ratchet was relaxed.

The localized-name/resource-key pointer frontier left by this batch is resolved
above. Fresh mission-05 tactical evidence is still needed. The combat-score
predicate's acceptance of type 40 remains
unresolved; the physical table ends at index 39. See
[the unit/stat recovery report](archive/UNIT_TYPES_AND_STATS_REPORT.md) and
`artifacts/structure-recovery/unit-metadata-20260905/` for evidence and commands.

## Astra Readiness Audit

The repository now has a tracked Astra configuration and Linux/WSL onboarding.
The failed autostash reapplication is repaired: 77 line-ending-only conflicts
and 58 staged line-ending-only changes were removed. All four mission-11 work
files retain their original SHA256 hashes; all stashes and worktree references
are unchanged. Production source and canonical metadata remain identical to
the starting HEAD after the conflict repair.

Fresh GCC 13 and Clang 18 builds compile and link; both pass the four explicit
asset-free CTest gates. The recovered main-menu exit probe passes, and the
existing mission-13 direct route passed twice, including a replay with fresh
late-route frames. Campaign completion remains 6/20; no route was promoted.
The repaired unit-test callers build and pass; measured coverage is 92.36%
across all 718 frozen functions, with zero uncovered functions.

The continuation synchronized 31 stale declaration records with the existing
source/header contracts and represented two existing initialization helpers
with explicit source ownership. The generator now retains those helpers;
nine focused tests were added to CI. This follow-up initially had only static
checks because WSL returned `Wsl/Service/CreateInstance/E_ACCESSDENIED`.
The later structure-validation batch above runs the new tests, regeneration
and Linux build gates. The declaration-only step had left production C and
generated headers unchanged; later structure recovery is recorded above.

Full readiness remains blocked by header-surface/link ratchets,
per-category warning increases and two mission-00 probe expectation failures.
The original Wine startup and display-mode blockers were subsequently resolved
for the fresh menu capture above. No warning, link, header, or coverage baseline
has been relaxed; the menu evidence does not establish gameplay fidelity.
See [the readiness record](ASTRA_READINESS.md) for commands, evidence,
coverage results, the declaration follow-up, and deferred repairs.

## Disassembly Control-Flow Recovery: Complete

All 17 `JUMPOUT(...)` "control flows out of bounds" decompiler scars in
the manifest-backed recovered subsystem sources directly under `src/` are recovered into
authentic structured C backed by `clash95.asm`. The canonical recovered C has
zero `JUMPOUT` code markers and no remaining out-of-bounds control-flow
artifacts. The full per-address table (register-restore epilogues and voice-mix
format-select thunks) is in
`docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`.

## Validated State

- The `sub_XXXXXX` placeholder-rename campaign is complete: all 3031 distinct
  `sub_` symbols carry evidence-based semantic names. Zero `sub_` identifiers
  remain as code symbols; the surviving `sub_` spellings are IDA address-anchor
  comments and trace strings only (per `docs/REVERSE_ENGINEERING.md` 3.1). The
  full old->new mapping lives in `docs/archive/SUB_RENAME_INDEX.md`.
- The embedded rules engine is identified as CLIPS 6.0 (see
  `docs/REVERSE_ENGINEERING.md` Queue F provenance). A CLIPS 6.30-source
  cross-reference of the string-anchored Queue F functions found zero
  mis-namings (`docs/archive/CLIPS_SOURCE_CROSSREF.md`), and the game's
  strategic-AI host-function API - the commands `strateg\clash.dat` rules call
  into the engine - is decoded from the binary's own registration table in
  `docs/AI_SCRIPTING_API.md`.
- `clash95_bootstrap` is the current SDL-backed executable target.
- The recovered implementation behind `clash95_recovered` and
  `clash95_bootstrap` now compiles as 140 GNU++20 translation units: 138
  address-ordered function-family files plus prelude/helper and quarantined
  state files. `data/recovered_sources.json` accounts for 4157 functions, and
  the split audit accounts for 4007 original address-marker chunks across 12
  subsystem object libraries. The split-only cutover removed the unified GNU89
  source, oracle targets, recovered include-C fragments, and compatibility
  symlinks; their old-to-new identities remain in `docs/SOURCE_PATH_MAP.csv`
  (see `docs/SOURCE_SPLIT.md`).
- The unit harness now compiles every case independently against instrumented
  split objects, with runner and compatibility stubs in dedicated files. Its
  manifest-backed, per-worker shard measurement currently covers 6163/6663
  executable lines (92.50%) across all 718 frozen pure functions, with zero
  functions uncovered (see `docs/UNIT_TESTING.md`).
- Before cutover, the final GCC split/oracle object gate resolved all 4070
  manifest functions and the complete default-visible symbol surface. It
  reported 4051 normalized-identical functions and 19 exact-hash reviewed
  cross-TU code-generation exceptions, with no missing, unexpected, or
  symbol-only entries. The recovered warning ratchet was originally seeded at
  146171 GCC / 147027 Clang 18 diagnostics; the P2 `(void)`-prototype wave and
  later reviewed cleanups reduced the saved baseline to 9763 GCC diagnostics
  and 9809 Clang 18 diagnostics (`data/recovered_warning_baseline.json` is
  authoritative). The fresh readiness audit above still fails category limits
  despite lower total warning counts. This is
  explicit cleanup debt, not a zero-warning result. Both compiler profiles
  reject category increases. Support code is compiled separately with warnings
  as errors.
- The first post-cutover Clang 18 cleanup wave now uses explicit 32-bit
  pointer-storage casts, standard no-argument `rand` calls, and assembly-backed
  source-pointer contracts for the CRT ANSI/wide string-copy helpers. The call
  sequences at `0x485453..0x485480`, `0x4854D5..0x485548`, and
  `0x485570..0x485598` preserve the EAX source plus EDX/EBX wide-buffer inputs
  shown in `clash95.asm`. Recovered byte
  strings now terminate two-digit `\xHH` escapes before following hexadecimal
  text, preventing the C lexer from consuming original character bytes. Clean
  GCC 13 and Clang 18 builds and the four asset-free CI CTest gates pass.
- Startup now initializes the assembly-backed 100 Hz performance-counter
  timebase; UI animation and timeout helpers run in recovered centiseconds.
- `UnitStack_ExecuteQueuedPath` now compares elapsed animation time against the
  unit-type interval byte preserved at `0x410DF5..0x410E0F`, rather than an
  uninitialized decompiler temporary. Repeated-turn queued marches no longer
  stall in the reached Mission `00` attack route.
- The validated executable-backed core of all 35 `UnitTypeMetadataRecord` entries
  restored offsets `+8..+37` at the original 88-byte stride. This replaced the
  false one-element animation/combat/AP globals that made nonzero unit types
  read unrelated host memory. The new full-table/tail recovery above now has
  compiler and unit evidence; tactical panel/frame validation remains pending.
- Default CTest smoke routes cover menu liveness, direct route startup, save DAT
  format checks, and opt-in real-input probes.
- Campaign route env files are the canonical machine-readable status source.
  `tests/summarize_campaign_arc_routes.sh` currently reports:
  - missions `00..04` and `13`: `complete` (6/20)
  - missions `05..12` and `14..19`: `partial` direct-load evidence probes

## Highest Runtime Milestone

The validated multiplayer-map frontier now covers direct all-AI map loading for
map IDs `0..10` (`multi1.map` through `multi11.map`) via the recovered `/A#`
route. Each map reaches the bootstrap load marker, enters `PlayGame`, remains
live through the 5-second probe window, and captures nonblank SDL frame
evidence. Map ID `0` also passed a 30-second no-trace `multiplayer-map` soak.

The canonical campaign-route frontier is now a complete direct-boot mission
`04` route. It breaches Hopenberg, clears the castle over three authentic
tactical assaults, and records successive battle returns with six, three, and
zero defenders. The empty-garrison return enters `Unit_CaptureBuilding`; the
world loop then logs `mission_objective_complete selected=-1 a=4 b=0 c=0`.
The definitive replay routed 347 inputs, retained all 61 checkpoints, and
recorded one objective completion. Its final objective checkpoint is current,
nonblank (`294268` nonblack pixels, `204` colors), and differs from the last
tactical checkpoint by a mean absolute pixel delta of `68.345217`. Durable
evidence is at
`artifacts/campaign-routes/mission-04/20260711T202215Z-195443/summary.txt`.

Earlier validated milestones include first-mission completion, mission `01`
shrine completion, mission `02` Treg Rock capture, and mission `03` survival
completion through route gates. Mission `13` (second campaign) is also
route-complete via authentic top-menu turn advancement to its recovered
survival objective (`GAME_TURN_COUNTER > 10`, case `0xD`).

## Environment Requirement (runtime work)

Any runtime, boot, menu, or gameplay-route work requires the installed retail
Clash game data. The SDL platform layer (`src/platform/platform_sdl_runtime.cpp`
`GetDriveTypeA`) resolves the game's CD/install root to `/mnt/<drive>/clash`
(or `/mnt/<drive>/CLASH`); `DetectGameCDPath` scans drive letters `C..Z` for a
directory there. With no such directory, boot aborts immediately with the
recovered `"Clash CD not found!"` message box and the process exits before any
menu or mission code runs.

Consequently, in an environment without the game data mounted (e.g. a fresh
web/CI container with no `/mnt/c/clash`):

- the `clash95_bootstrap` executable cannot boot, so the three route smokes
  `clash95_r_command_shutdown_smoke`, `clash95_direct_a_route_smoke`, and
  `clash95_direct_a0_route_smoke` fail by design (missing assets, not a
  regression); the rest of the default CTest suite still passes;
- only static work is possible: compilation/link, the unit-test coverage
  target (`-DCLASH95_COVERAGE=ON`, see `docs/UNIT_TESTING.md`), and
  asm-grounded (`clash95.asm`) source-fidelity edits.

To unblock runtime/gameplay work, mount a copy of the installed game at
`/mnt/c/clash` (or symlink a real install there), then the boot path and the
campaign-route probes can run and validate as documented in
`docs/RUNTIME_MILESTONES.md`.

Empirically, boot requires the data at three levels (verified by running
`clash95_bootstrap` headless):
1. `/mnt/<drive>/clash` must exist (else `DetectGameCDPath` -> "Clash CD not
   found!" at once);
2. the startup resource archives must mount from it (`data\music.res`,
   `gfx\*.res`, `sfx\*.res`, ... via `FileSystem_MountArchiveAtIndex`);
3. specific resources must resolve from those archives -- the title path
   `FileSystem_ResolveReadPath("gfx\backgr1.s32")` gates boot: if it is not
   found, `ResourceArchives_MountStartupArchives` calls `App_RequestQuit` with
   "Clash CD not found!"
   (`src/persistence/00441DC0_00443B60_persistence_001.cpp`).
An empty `/mnt/c/clash` directory passes level 1 but still fails at level 3, so
a real install (not just the directory) is required.

## Active Blocker

Mission `05` is the first incomplete campaign route. In the active
nonzero-language branch, `Mission_CheckObjectiveComplete` requires every
building and stack owned by player `3` (Agordeh) to be eliminated. The retained
direct-load trace stops on player-3 building index `4`; scenario setup also
creates six player-3 stacks, including one remote stack at `(87,66)`.
`Mission_CheckFailureCondition` reads the mission failure flag set by
`Mission05_MarkFailureOnFriendlyAttack` when player `0` attacks players `1` or
`2`. With authentic metadata, player-0 stack `4` has a 20-point mixed-stack AP
floor rather than the former host-memory artifact `255`. Fresh 2026-09-06
evidence moves the blocker back to the first order: `(47,58)` and its eight
neighbors are unrevealed in both the engine-authored turn-1 save and the
original's live memory. The original fog classifier rejects that destination;
the repaired C++ code does too. The current and frozen-C replays cannot create
the historical 33-node path.

The July nine-turn arrival and its referenced evidence at
`artifacts/campaign-routes/mission-05/20260714T155159Z-98803/summary.txt` remain
historical, but do not establish a valid route from the currently verified
starting state. The old C classifier discarded seven visibility results and
used uninitialized masks; it is not a reliable behavior oracle. Its repair
does not reveal tiles or change movement/AP rules. The earlier one-turn
tactical entry also remains quarantined for invalid 255-AP state. An authentic
arrival save, stack-19 tactical entry, the first exchange and remaining owner-3
elimination are still unproven. Full-menu automatic advancement remains
separate. Fresh evidence is in `artifacts/runtime-recovery/fog-20260906/` and
`artifacts/campaign-validation/mission05-cpp-20260906/`.

## Next Target

Continue mission `05` from the original-matching first Road endpoint `(49,50)`,
turn 6, selected stack 4, 2 AP, no active path and 228 visible tiles. Use
`tests/first_campaign_arc_routes/mission_05_first_road_probe.env`; both supported
compiler builds pass. The seven-leg land approach and rejection of ordinary
unbuilt-water movement remain prerequisites. Do not restore historical builder
crossing exceptions or transfer shortcuts.

Use normal End Turn/menu readiness to refresh turn 7 before the next Road action;
the original water highlight requires at least 6 AP. Fresh original-only evidence
continues Road west through `(48,50)`, `(47,50)`, `(46,50)`, `(45,50)`, leaving
16/12/8/3 AP. Road mode stays active between these four actions. Compare the
actual C++ action results, visibility and frames before extending the probe.
Original road words at x=50..45, y=50 are `867,879,878,878,877,65535`.

The original then uses accepted land orders and normal fatigue/AP refresh to
reach `(47,58)` on turn 10 with 6 AP and 305 visible tiles. Its route, full raw
snapshots and valid arrival capture are retained under
`artifacts/campaign-validation/mission05-bridge-20260906/original/`. This uses a
real Load restart from an unchanged turn-6 save. A later failed Save-menu cursor
step issued an unintended movement order; it is separate from the earlier valid
arrival capture, and no engine-authored arrival save exists. Stop dependent
clicks when a cursor gate fails. Do not turn memory snapshots into saves.

C++ full arrival remains unproven. After comparing that route, validate manual
tactical entry against stack `19`, the first exchange and elimination of owner 3
without attacking owners 1/2. Full-menu entry and natural automatic advancement
remain separate gates. The next broader startup debt is `CSS_Init`.

## Evidence Trail

- Current milestone table: `docs/RUNTIME_MILESTONES.md`
- Full historical progress: `docs/archive/COMPILATION_PROGRESS.md`
- Rename/recovery log: `docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- Pre-cutover normalized-disassembly exceptions:
  `docs/archive/SPLIT_DISASSEMBLY_EXCEPTIONS.json`
- CLIPS engine provenance + source cross-reference:
  `docs/archive/CLIPS_SOURCE_CROSSREF.md`
- Strategic-AI host-function API: `docs/AI_SCRIPTING_API.md`
- Route/probe notes: `docs/probes/`
