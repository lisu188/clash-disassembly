# Conversation findings gap audit for `lisu188/clash-disassembly`

This note is meant to sit next to `DISASSEMBLY_GUIDE.md` and future Codex prompts.

It reflects the gap snapshot captured at the start of this integration wave, before the guide, audit, and crosswalk files were added.

## What the repo already absorbed

### Rename families already landed

The current `REVERSE_ENGINEERING_RENAME_LOG.md` already contains the biggest conversation-driven rename families, including:

- platform loop aliases (`Platform_MainWindowProc`, `Platform_CreateMainWindow`, `Platform_PumpMessagesAndBlitFrame`)
- port reinforcement semantics (`Port_CollectReinforcementShipment`)
- battle interaction (`UnitBattle_HandleBattlefieldInteraction`)
- stack-selection helpers (`UnitStackSelection_BuildSelectedSlotIndexList`)
- the `BuildingGarrisonDialog_*` callback family
- the `CastleProduction_*` action family

This means a follow-up Codex pass should **not** spend its budget re-deriving those names unless it is tightening evidence text or repairing a nearby inconsistency.

### Structure/state recovery already landed

The current `RECOVERED_STRUCTURES.json` already contains substantial conversation-aligned state recovery, including:

- `UnitStackSelectionState`
- `MergedTerrainMoveProfile`
- `MiniMapState`
- `TooltipBackdropState`
- `BuildingGarrisonDialogState`
- `BuildingGarrisonDialogActionsTable`
- `CastleManagementScreenState`
- `InputBackendState`
- `CastleProductionPanelState`
- `PortSpawnOffset`
- `BattleRuntimeState`
- `BattlePathingTables`

These are now canonical enough that a follow-up pass should focus on:

- cross-linking
- small field-description improvements
- missing adjacent records
- keeping conservative names conservative

### Unit roster / taxonomy already landed

The current unit report already aligns strongly with the conversation findings:

- 35-entry recovered roster
- cargo-style types `31` and `32`
- conservative `SpecialPersonageCategory` treatment for types `33` and `34`

A follow-up pass should preserve that stability and avoid gratuitous renaming.

## What still appears missing or worth adding

### 1. The guide itself

The repo root did not yet contain `DISASSEMBLY_GUIDE.md`.

That is the cleanest remaining high-value import.

### 2. A machine-readable crosswalk

There is still value in adding a compact crosswalk CSV that answers:

- which conversation findings are already canonical
- which are missing
- which file owns each fact
- whether the item is rename-only, struct-only, or docs-only

This reduces repeated Codex work.

### 3. A short maintainer-facing gap audit

A small markdown audit was still missing and helps future passes avoid redoing the rename families that are already merged.

### 4. Compilation-progress note for this integration wave

If the guide, crosswalk, and audit are added, `COMPILATION_PROGRESS.md` should get a short new batch documenting that this was a documentation/canonical-sync wave rather than a gameplay-semantics wave.

## What should remain conservative

The following areas should stay conservative unless re-proven directly from `clash95.asm` / `clash95.c`:

- unit types `33` and `34` beyond the current special-personage framing
- soft field names like `aux_context`, `visual_class_index`, `pending_exit_countdown`
- the exact semantic boundary of `AST_Append`
- any attempt to turn the current C recovery into a class-based source port

## Best next Codex move

The best next Codex patch is:

1. add `DISASSEMBLY_GUIDE.md`
2. add `data/conversation_findings_crosswalk.csv`
3. add `docs/CONVERSATION_FINDINGS_GAP_AUDIT.md`
4. append a short `COMPILATION_PROGRESS.md` batch
5. touch canonical rename/structure artifacts only if the audit proves an actual gap

## What not to do next

Do not:

- reopen the already-landed rename families
- inject the pass-based class-façade scaffolds
- mass-edit `clash95.c` for style
- broaden `AGENTS.md` into a generic reverse-engineering manifesto

The current repo is already beyond the stage where a second big naming pass is the best use of effort.
