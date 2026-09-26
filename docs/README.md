# Documentation guide

Start with [current status](STATUS.md) and its Next Target before resuming work.
The [Clash project overview](CLASH_PROJECTS.md) explains how this reconstruction
relates to the HD runtime, save editor and shared asset/manual repository.

## Canonical ownership

| Question | Authoritative document or data |
| --- | --- |
| What is the project trying to finish? | [AGENTS.md](../AGENTS.md): mission, definition of done, evidence and operating rules |
| What is proved now, blocked, or next? | [STATUS.md](STATUS.md): concise current ledger; linked reports retain exact receipts |
| How are tracks prioritized and accepted? | [PROJECT_TRACKS.md](PROJECT_TRACKS.md); [ROADMAP.md](ROADMAP.md) for long-term goals |
| How do I build or validate a change? | [BUILD_AND_TEST.md](BUILD_AND_TEST.md); [public CI](../.github/workflows/ci.yml) is the executable matrix |
| Where does code belong? | [SOURCE_LAYOUT.md](SOURCE_LAYOUT.md), [subsystem map](../src/README.md), [ordered manifest](../data/recovered_sources.json) |
| Which missions are complete? | [Route env files](../tests/first_campaign_arc_routes/), summarized by `tests/summarize_campaign_arc_routes.sh` |
| What may be retained or pruned? | [ARTIFACTS.md](ARTIFACTS.md) and the disk/evidence rules in the working checkout's AGENTS.md |

Current navigation summarizes and links to evidence; it does not duplicate whole
batch reports. A dated report, commit-specific measurement or local artifact path
is historical evidence until a new check establishes the claim for a newer tree.

## Runtime, campaigns and persistence

- [Runtime milestones](RUNTIME_MILESTONES.md): test-to-evidence map and open proof gaps.
- [Campaign runner](probes/README_campaign_arc_probe.md) and
  [first-campaign runner](probes/README_first_campaign_arc_probe.md).
- [Mission-00 gate](probes/README_first_campaign_mission00_gate_probe.md),
  [historical stack-6 probe](probes/README_first_mission_stack6_probe.md),
  [mission-state traces](probes/README_mission_state_trace.md) and
  [multiplayer map probes](probes/README_multiplayer_map_probe.md).
- [Mission-05 worklog](../tests/first_campaign_arc_routes/mission_05_WORKLOG.md)
  and [mission completion notes](../tests/first_campaign_arc_routes/MISSION_COMPLETION_NOTES.md).
- [Save DAT format](SAVE_DAT_FORMAT.md): recovered persistence evidence.
- [Original VM setup](../tools/vm/README.md): comparison environment notes.

## Source recovery and C++ migration

- [Reverse-engineering policy](REVERSE_ENGINEERING.md) and
  [structure recovery policy](STRUCTURES.md).
- [Unit testing](UNIT_TESTING.md): frozen function set, coverage, isolated crashes
  and the distinction between test passage and complete behavior.
- [GNU++20 language cutover](CPP_MIGRATION.md) and
  [historical source split](SOURCE_SPLIT.md); [old source paths](SOURCE_PATH_MAP.csv)
  preserve provenance, while SOURCE_LAYOUT.md owns current organization.
- [Game-system class migration](CPP_CLASS_MIGRATION.md),
  [extraction design](CPP_CLASS_EXTRACTION.md),
  [blockers](CPP_CLASS_MIGRATION_BLOCKERS.md) and
  [platform inventory](CPP_CLASS_PLATFORM_INVENTORY.md).
- [UnitStack register recovery](UNIT_STACK_REGISTER_RECOVERY.md),
  [register classes](UNIT_STACK_REGISTER_CLASSES.md),
  [query classes](UNIT_STACK_QUERY_CLASSES.md),
  [UnitSlot migration](UNIT_SLOT_CLASS_MIGRATION.md),
  [UnitSlot AP classes](UNIT_SLOT_AP_CLASSES.md),
  [unit-turn migration](UNIT_TURN_CLASS_MIGRATION.md),
  [logging context](UNIT_NEW_TURN_LOGGING_CONTEXT.md) and
  [regroup recovery](UNIT_REGROUP_RECOVERY.md).
- [GameRandom recovery](GAME_RANDOM_RECOVERY.md),
  [GameRandom classes](GAME_RANDOM_CLASSES.md) and
  [world geometry migration](WORLD_GEOMETRY_CLASS_MIGRATION.md).
- [Readability batch ledger](HUMAN_READABILITY.md),
  [Road readiness](ROAD_CONSTRUCTION_CLASS_READINESS.md),
  [Road timing recovery](ROAD_MODE_TIMING_RECOVERY.md),
  [DLX cached entries](DLX_CACHED_ENTRY_RECOVERY.md),
  [construct-file recovery](CONSTRUCT_CODE_FILE_RECOVERY.md) and
  [logical-name recovery](IO_LOGICAL_NAME_RECOVERY.md).
- [Numeric recovery](MAGIC_NUMBER_RECOVERY.md) and
  [numeric naming runbook](MAGIC_NUMBER_RUNBOOK.md).
- [Clash Deluxe and historical-site research](CLASH_DELUXE_RESEARCH.md): secondary
  corroboration, archive metadata and executable-lineage limits; a fan rebalance
  is not the specification for original Win95 behavior.

## Strategic AI and CLASH.DAT

[AI host API](AI_SCRIPTING_API.md) and [host recovery specification](AI_HOST_RECOVERY_SPEC.md)
describe the game/CLIPS boundary. Follow the evidence chain through:

1. [BSAVE layout](CLASH_DAT_BSAVE.md) and [compiled primitives](CLASH_DAT_PRIMITIVES.md).
2. [Classes, RETE and LHS](CLASH_DAT_LHS.md),
   [slot facets](CLASH_DAT_SLOT_FACETS.md),
   [message handlers](CLASH_DAT_MESSAGE_HANDLERS.md) and
   [object/handler semantics](CLASH_DAT_OBJECT_AND_HANDLER_SEMANTICS.md).
3. [Constraint-aware recovered CLP](CLASH_DAT_RECOVERED_CLP.md), the current
   generator entrypoint and validation boundary. It supersedes the older scaffold
   generator for new recovery work.
4. [Strategic dataflow report](STRATEGIC_AI_DATAFLOW.md), a dated recovery snapshot;
   its unresolved-matcher counts must not override later generator results.

Generate output from the binary evidence; never edit generated CLP into a new
oracle. Translation completeness, stock-CLIPS checks, production C++ execution
and original-engine equivalence are separate gates.

## Historical evidence and integration reports

[The archive index](archive/INDEX.md) and
[status history through 2026-09-26](archive/STATUS_20260926.md) preserve prior
commands, successes, failures and superseded route assumptions. Stable paths are
retained for these dated reports:

- [Native class baseline](CPP_CLASS_NATIVE_BASELINE.md),
  [first-Road revalidation](CPP_CLASS_FIRST_ROAD_REVALIDATION.md),
  [resumed validation](CPP_CLASS_RESUMED_VALIDATION.md),
  [origin refresh](CPP_CLASS_ORIGIN_REFRESH.md) and
  [September integration](CPP_CLASS_SEPTEMBER_INTEGRATION.md).
- [September-6 integration](INTEGRATION_20260906.md),
  [validation gates](VALIDATION_GATES_20260906.md),
  [Astra readiness audit](ASTRA_READINESS.md) and
  [September-24 header baseline review](HEADER_SURFACE_BASELINE_20260924.md).

Private `artifacts/` receipts may be absent from a clone. Their absence does not
invalidate the retained report or turn its result into a new local verification.

## Maintaining the documentation

Update the owning page when facts change. Keep README short, put detailed commands
in BUILD_AND_TEST.md, current state in STATUS.md, acceptance in PROJECT_TRACKS.md,
and batch measurements in the relevant evidence report. Link new topic guides
here. Preserve historical hashes, original attempts, failures and uncertainty.

For documentation-only work use the [focused validation commands](BUILD_AND_TEST.md#documentation-only-changes).
Check Markdown fragments as well as file paths when renaming headings: the current
repository link checker validates local paths but skips fragment and remote-URL
resolution. No fresh game build is required merely to reorganize prose.
