# F6 remaining stack helper and selection-slot constants

Track: Win95 reconstruction. Frontier: behavior-preserving reuse of established stack-slot layout constants after the final residual census. This supplement adds 13 exact-token rules in four related functions, all in `src/buildings/00422B50_004254E0_buildings_005.cpp`. It adds no constants. Eight `6` tokens reuse `UNIT_STACK_SLOT_BASE_OFFSET`; five `10` tokens reuse `UNIT_STACK_SLOT_COUNT`.

## Baseline and evidence

**These rules target the current post-F1/F2/F3/F4 source, after 1,975 substitutions, not the original HEAD source.** The source file's pre-F6 SHA-256 is `33d752fa7446cd4dc5a9b7cf0a0b4a512984fbcba539c2727d961d6c892dda15`. They must be resolved and applied as a separate reviewed plan after that batch. Historical rules and original body hashes remain untouched.

The existing macro bodies in `src/recovered_types.h:103` and `:105` are the exact unsuffixed decimal tokens `6` and `10`. The independently recovered `UnitStackRecord` layout in `RECOVERED_STRUCTURES.json:495` and `src/recovered_structs.h:180` contains ten 31-byte `UnitSlotRecord` entries starting at byte offset six; the header checks the offset explicitly at line 195. The original machine instructions and each local producer/consumer establish that the following occurrences use this same domain. Confidence is high.

| Function | Source lines: macro role | Independent machine/data-flow evidence |
|---|---|---|
| `Unit_CountSelectedGroupMembers` | 42: slot base; 43: slot count | Original `Unit_GetSquadCount` at 0x422B80, `clash95.asm:53545` uses `lea edx,[eax+6]`; :53553 steps by `1Fh`, and :53554 compares against `0Ah`. The first word is the occupied unit-type test. |
| `UnitStack_HasOnlyFlyingUnits` | 59: slot base; 70: slot count | Original `sub_422BA0`, `clash95.asm:53573` uses the same base; :53584 steps by `1Fh`, and :53585 compares against `0Ah`. Each first word selects unit metadata before the flying-flag test. |
| `UnitStackSelection_RedrawPanel` | 356,374: slot count; 358,376,378: slot base | Original `sub_423420`, `clash95.asm:54441` passes `0Ah` to `sub_412B20`; :54446 reads the first slot at +6. The drawing loop is bounded by `0Ah` at :54521 and accesses type words at `31*j+6` at :54527/:54532. Source line 353 constructs `g_SelectedUnitStackRecordPtr` from the stack-table base and 725-byte record expression. |
| `UnitStackSelection_HandleInput` | 478,481,484: slot base; 548: slot count | Original `sub_423860`, `clash95.asm:54824`, :54831 and :54850 read or pass the selected unit slot at stack base plus `31*slot_index+6`; :54923 passes `0Ah` to the selection-list helper. The global stack pointer is established by the panel function above. |

The selection-list capacity is corroborated independently by `UnitStackSelection_BuildSelectedSlotIndexList` at `src/units/004115E0_00412BE0_units_002.cpp:1397`: its second argument bounds the loop reading DWORD selection flags, and it appends a -1 terminator after the selected indices. `g_UnitStackSlotSelectedFlags` has ten elements (`src/buildings/buildings_shared_state.h:88`, state definition at `src/state/00000000_0054FFFF_recovered_state.cpp:13787`). The local output buffers have eleven or twelve entries; those declaration lengths are not replaced by the ten-slot count.

The immediately adjacent `Unit_AddToGroup`, `Unit_CanMoveSelectionFromGroupToTile` and `Unit_MoveSelectionFromGroupToTile` already use the established slot-base/count names where applicable. The selection begin/end/clear/query family has no additional raw 6 or 10 in the same domain. The 40-byte selection-mask loops, local array lengths, 12-neighbor loops, screen coordinates, unit-type thresholds and `slot_index <= 9` are retained. Converting nine to a derived count-minus-one expression would change preprocessed tokens and is outside this supplement.

## Validation

Each rule is anchored to one complete source line and restricted to the exact canonical file and function, with only the intended numeric token in the `lit` capture. No pointer arithmetic, casts, grouping, type suffixes, comparison boundaries or stored data are changed. The rules were authored and dry-resolved only; source application, regeneration, object/link gates and the refreshed F5 census belong to the coordinator's integration step.

Executed from the worktree root through `wsl.exe --cd /mnt/c/Users/andrz/.codex/worktrees/62e9/clash-disassembly -e python3 -`:

```python
import json, os, sys
from pathlib import Path
os.environ.update(
    GIT_DIR="/mnt/c/Users/andrz/git/clash-disassembly/.git/worktrees/clash-disassembly1",
    GIT_COMMON_DIR="/mnt/c/Users/andrz/git/clash-disassembly/.git",
    GIT_WORK_TREE=str(Path.cwd()),
)
sys.path.insert(0, "tools")
import literal_common as lc
import apply_literal_names as a
rules = json.loads(Path("docs/archive/literal_rules/F6_stack_helpers.json").read_text())
entries, families = lc.load_manifest()
by_name = {entry["name"]: entry for entry in entries}
enums = lc.parse_prelude_enums()
assert not a.validate_rules(rules, by_name, lc.parse_prelude_macros(), enums)
plan = a.resolve(rules, by_name, families, "F6-stack-helpers", enums)
assert len(plan["entries"]) == 13
assert not plan["rejected"]
assert not any(site.get("respell") for site in plan["entries"])
```

Result: 13 rules, 13 unique sites, zero validation errors, zero rejected sites and zero respellings. This is naming evidence and dry-plan validation, not a new runtime or campaign milestone.
