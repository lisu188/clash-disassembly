# Current Status

Reviewed after integrating main `089b96f` on 2026-09-26. This page owns the current validated
frontier and next target. [Project tracks](PROJECT_TRACKS.md) defines acceptance;
[the documentation guide](README.md) routes detailed questions.

The former long status ledger is preserved in full as
[status history through 2026-09-26](archive/STATUS_20260926.md). Its individual
build, coverage, crash and ratchet counts belong to the stated commits, not to
every subsequent revision. The [class-branch status supplement](archive/CLASS_MIGRATION_STATUS_20260926.md)
preserves the additional migration entries. The documentation consolidation
itself does not establish runtime parity; later validation is identified below.

## Validated State

| Area | Retained baseline | Evidence and limit |
| --- | --- | --- |
| Implementation | GNU++20, 4,157 historical identities, 148 ordered translation units in 12 recovered subsystems | [Source layout](SOURCE_LAYOUT.md), source manifest and split audit. Language cutover is complete; full reimplementation is not. |
| Naming and control flow | 3,031 original placeholder names resolved; all 17 known `JUMPOUT` scars recovered | [Rename index](archive/SUB_RENAME_INDEX.md) and [recovery log](archive/REVERSE_ENGINEERING_RENAME_LOG.md). Naming does not certify behavior. |
| C++ classes | 36 historical identities have canonical methods in seven class-named sources | [Class migration](CPP_CLASS_MIGRATION.md). Architectural assignments in registries are broader than implemented migration. |
| Campaign routes | Missions `00..04` and `13` are route-complete (6/20); `05..12` and `14..19` remain partial | [Route env files](../tests/first_campaign_arc_routes/) are authoritative; direct boot does not prove menu progression. |
| Mission 05 | First Road construction at turn 6, stack 4 at `(49,50)`, 2 AP, empty active path, 228 visible tiles | [First-Road probe](../tests/first_campaign_arc_routes/mission_05_first_road_probe.env) and [bounded original comparison](archive/STATUS_20260926.md#builder-road-menu-original-matching-first-construction). |
| Runtime coverage | Authentic SDL menus and direct gameplay probes; all-AI multiplayer map IDs `0..10` have retained load/liveness/frame evidence | [Runtime milestones](RUNTIME_MILESTONES.md). Full-game, human multiplayer menu and visual equivalence remain unproven. |
| Strategic AI tooling | Recovered constraint projection covers 753 compiled matcher occurrences; stock-CLIPS load, RETE/agenda and activation witnesses are separate checks | [Recovered CLP](CLASH_DAT_RECOVERED_CLP.md) and [slot override repair](CLASH_DAT_SLOT_FACETS.md). Source generation and stock-CLIPS checks do not prove production strategic-AI parity. |

Refresh route metadata without launching a game:

```sh
bash tests/summarize_campaign_arc_routes.sh
```

## Current Class Checkpoint

The WorldMap visibility extraction and separate relocation pass both production
builds, warnings, strict symbol/storage comparisons, eight asset-free gates and
eight actual-source behavior profiles. Relocation `baa8c3e` preserves every
method body and requires no symbol/storage/initialization allowances. Hosted
extraction head `9123e70` passes all 602 tooling tests and retains
all 1,616 native outcomes per compiler. GCC records 1100/0/516 passes/assertion
failures/crashes with 6169/6659 covered/executable lines; Clang records 1097/1/518
and 6808/7348, including the same eight uncovered functions. Native outcome and
covered-line variations remain unresolved; the overall run fails. Historical
link failures remain explicit, and no baseline is reseeded.

The fresh original-paired first-Road replay validates the preceding 33-method
checkpoint. It matches the bounded endpoint, all 310 selected-slot bytes and all
1,300 visibility bytes, while retaining full-payload and visible differences.
It does not validate the new WorldMap class or promote a campaign milestone.
See [WorldMap evidence](WORLD_MAP_VISIBILITY_CLASSES.md),
[native comparison limits](CPP_CLASS_SEPTEMBER_INTEGRATION.md#integrated-worldmap-extraction-checkpoint)
and [the first-Road comparison](CPP_CLASS_FIRST_ROAD_REVALIDATION.md#september-26-33-method-checkpoint).

## Active Blocker

Mission `05` is the first incomplete campaign route. Its objective requires
eliminating every player-3 building and stack without attacking players `1` or
`2`. The valid approach follows revealed destinations, normal AP refresh, and
the actual Building → Road action. The first Road endpoint above is the retained
comparison frontier. Its original side uses real Load of an unchanged
engine-authored turn-6 checkpoint; continuous original turn-1 replay and complete
world-memory equality are not claimed.

The [September-26 bridge draft](../tests/first_campaign_arc_routes/mission_05_WORKLOG.md#unvalidated-bridge-draft-preserved-at-worktree-retirement-2026-09-26)
is blocked and unvalidated. Road mode does not emit the cursor observations
required by the guarded route input. Two C++ attempts were interrupted, and the
fresh original capture stopped on denied read-only process-memory access. The
draft is an opt-in diagnostic, not a registered regression or a replacement for
the canonical mission route. Investigate observation-only cursor reporting before
replay; keep input gates and gameplay dispatch intact.

The historical nine-turn march and earlier 255-AP tactical entry are superseded
as acceptance evidence: the original rejects their unrevealed starting waypoint,
and the authentic mixed-stack AP floor is 20. Removed manual water-crossing
exceptions and builder transfers must not return. Their reports remain in the
[history](archive/STATUS_20260926.md) and
[mission worklog](../tests/first_campaign_arc_routes/mission_05_WORKLOG.md).

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


## Validation Limits

- Compile/link, asset-free tests, native isolated-case results, runtime routes,
  presented frames and original parity are distinct claims. The native harness
  can tolerate isolated crashes; a passing coverage gate is not a crash-free
  game. See [unit testing](UNIT_TESTING.md).
- PR #145's retained closeout includes compiler/public-test/coverage passes and
  incomplete or failing local attempts. The final tree also includes a reviewed
  [header baseline synchronization](HEADER_SURFACE_BASELINE_20260924.md).
  The header-surface audit passes in this documentation review. Earlier
  header-failure counts are historical; linked-symbol baseline failures remain
  recorded in the last build receipts and were not rerun here. Read the
  [loader closeout](HUMAN_READABILITY.md#september-26-integration-and-worktree-closeout)
  and [DLX closeout](archive/literal_rules/F8_dlx_extents_findings.md#september-26-closeout)
  for exact revisions and limits.
- First-Road frame comparisons retain HUD, text, badge, fog and water differences.
  No visual-equivalence claim follows from matching route state.
- Full Campaign-menu entry, natural automatic advancement, the remaining
  campaigns, class/ownership migration and reached compatibility debt remain.
  `CSS_Init` and its legacy audio/device table remain broader startup work.

## Evidence Trail

The 2026-09-26 documentation review passes the local Markdown path check and its
three focused tests, split-source audit (4,157 canonical implementations, 147
translation units, 23 ABI adapters and 459 inventoried support definitions),
718-function pure-metadata check, save-format contract, header-surface audit and
recovered-CLP source contract. The current matcher inventory reports 753/753
translated tests, zero unresolved and 95 fully translated rule/disjunct records.
The route summary remains 6 complete and 14 partial. Heading targets and the
complete archived status ledger were also checked. These are static/tooling
results, not fresh compiler, native-unit, retail-runtime or original-parity runs.

- [Build, tests, probes and host prerequisites](BUILD_AND_TEST.md)
- [Runtime milestone and command index](RUNTIME_MILESTONES.md)
- [Class migration and provenance registries](CPP_CLASS_MIGRATION.md)
- [Readability batch evidence](HUMAN_READABILITY.md)
- [Historical status ledger](archive/STATUS_20260926.md)
- [Archive and older progress logs](archive/INDEX.md)

Paths under `artifacts/` identify private local evidence, usually absent from a
clean checkout. Preserve raw attempts and failures; their documented existence
is not a fresh replay. The [artifact policy](ARTIFACTS.md) and repository
[operating instructions](../AGENTS.md) govern retention.
