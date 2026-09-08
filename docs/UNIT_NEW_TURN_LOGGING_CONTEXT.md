# Unit_NewTurn: define the enemy-exit logging context

Track: Win95 reconstruction. Frontier: a separate portability
repair before UnitTurn class extraction. Date: 2026-09-06. The independent repair
was committed as `356a9ad14e37e4325dec056348aae52f5edb7e18`; subsequent class
parity uses that repaired reference. This change does not advance a campaign
endpoint or visual-fidelity claim.

`Unit_NewTurn` could reach enemy building contact while processing stack zero
and pass an uninitialized `nextStackOffset` to `LogAllUnits`. The variable is
assigned only after an iteration reaches `LABEL_16`; the enemy-contact branch
breaks before that assignment. Later-index exits usually inherit a prior loop
value. An unused callee parameter still does not make evaluating an
indeterminate C++ local valid.

The repair changes only the first argument in the enemy-contact return:

```diff
-  return LogAllUnits(nextStackOffset, slotIndex, 0xFFFFFFFF);
+  return LogAllUnits(0, slotIndex, 0xFFFFFFFF);
```

The normal 500-stack exit, game state, callback order and other arguments remain
unchanged. This removes an invalid evaluation of discarded compatibility
context; it does not invent a missing stack index or move behavior into a class.

## Original and current callee evidence

The public map identifies `Unit_NewTurn` at segment-1 offset `0x108E0`
(`clash95.map:77`), `LogAllUnits` at `0x10460` (line 75), and `log` at `0x18120`
(line 98). With segment base `0x401000`, these are `0x4118E0`, `0x411460` and
`0x419120`. `clash95.asm` defines Unit_NewTurn at line 26836 and LogAllUnits at
line 26271.

- Original enemy contact: `0x411A9A mov eax,esi`, `0x411A9C call 0x40FA20`
  (clear ready flags), then `0x411AA1 jmp 0x411A67`. The shared return calls
  `LogAllUnits` at `0x411A67`. The original uses defined register contents;
  there is no original uninitialized C++ local to preserve.
- `LogAllUnits` starts by pushing the fixed `LogAllUnits` string at `0x411462`
  and calling log at `0x411467`. The string contains no format conversions
  (`clash95.asm:385051`). It then sets its own scan state with
  `0x41146C xor ecx,ecx` and `0x41146E mov edx,[0x5202E4]`. Its game-state scan
  does not obtain a receiver/index from the caller's argument one.
- Current `LogAllUnits`, `src/units/0040F510_00411560_units_001.cpp:1320`, uses
  argument one only in `Debug_Log`; its 500-stack scan starts from live
  `gameData + UNIT_STACK_TABLE_OFFSET`. `Debug_Log`,
  `src/units/00416850_00419120_units_005.cpp:1177`, marks all arguments unused
  and returns without executing its quarantined formatter/stream path, whether
  either logging flag is disabled or both are enabled.

Confidence is high for the argument's lack of game-state effect in this traced
contract. Restoring the wider logging implementation is separate compatibility
work; it must preserve this discarded context boundary.

Original executable SHA-256:
`500055d77d03d514e8d3168506bd10f67cd8569bcc450604ff8192f46cdaf3ae`.
Pre-repair Unit_NewTurn body SHA-256:
`f1821d340262ff83997e65f63c2ef364f323b59d3614ec529637583ee1883da3`.
Repaired body SHA-256:
`0a7fc74f0159f79e7a35b97785cf8d87f554cc0ac1b22ae3e91d111290212ad2`.

## Independent recovery regression

`tests/tools/test_unit_new_turn_logging_context.py` resolves actual production
Unit_NewTurn, LogAllUnits, Debug_Log and UnitStack_HasReadyUnits definitions
through the source manifest and verifies their hashes. It compiles those
families in separate translation units, including the actual canonical
readiness method and its actual free ABI adapter. It also resolves the
UnitTurn method/adapter and registered borrow factory after extraction.
Linker `--wrap=LogAllUnits` observes the boundary without rewriting the recovered
body; the wrapper forwards into the actual logging implementation. Other turn
services are explicit instrumented boundaries, not claimed recovered behavior.
Readiness is not stubbed: the first-stack case sets the actual ready flag at
stack offset 19 and the actual query scans packed unit slots. The callback
trace records only real side-effect boundaries; it does not invent a readiness
callback to make the before/after traces agree.

Each GCC 13 / Clang 18 profile at O0 and O2 checks:

- First-stack enemy contact under all four combinations of the logging flags;
  the deterministic zero context, original return value, exact callback order,
  skipped queued-path execution, and all 589,824 world bytes are asserted.
- Seven extreme logging-context values across all four logging configurations
  (28 cases) have identical return values, callback order and complete world
  state through the actual LogAllUnits and Debug_Log bodies.
- `-ftrivial-auto-var-init=pattern` exposes a missing assignment deterministically.
  A separate frozen unrepaired control fails all four profiles at the expected
  first-stack logging-context assertion. The repaired production source and
  subsequent scratch class/adapter implementation pass all four profiles.

This is 32 cases per profile, without retail assets. It does not substitute for
production link/storage gates, full native outcomes or an authentic game route.
The original binary was read with objdump, not executed, for this audit.

Reproduce the maintained recovery test after integration:

```sh
python3 -m unittest discover -s tests/tools -p test_unit_new_turn_logging_context.py -v
```

Fresh GCC 13 and Clang 18 production builds, both exact migration surface
comparisons and all eight asset-free gates pass. No symbol, storage,
initialization or data-order allowance changes are needed. Commands and logs
are `artifacts/cpp-classes/20260906/pilot/*unit-turn-logging-recovery*`.
The full native and route matrix for subsequent class integration remains
separate. No historical ratchet is reset by this repair.

## Private preparation evidence

Durable preparation archive:
`artifacts/cpp-classes/20260906/unit-turn/preparation.tar.gz`, with sibling
`summary.json`, `README.md` and `preparation.tar.gz.sha256`. Archive SHA-256:
`ba9176c6a9853bc9c552f3fac90a60cf6b9b694dd64d6df16078e433d73d091a`.
The original scratch root was `/var/tmp/clash95-class-unit-turn-20260906/`;
use the archive if that working directory has been reclaimed.

Within the archive, `recovery/` holds the separate source patch, body hashes,
production-resolving regression and fixture. The final, stronger runs are
`evidence/recovery-real-ready-production/summary.json`,
`evidence/recovery-real-ready-class/summary.json` and
`evidence/recovery-real-ready-negative/summary.json`. They compile the actual
readiness method and free adapter. Production and scratch class runs pass all
four compiler/optimization profiles; every frozen unrepaired control fails at
the expected first-stack zero-context assertion. These final runs supersede
the earlier stubbed-readiness recovery fixture without deleting its evidence.

Older `recovery-production-first`, `recovery-relocated-class` and
`recovery-true-negative-control` runs remain historical preparation evidence.
The initial missing-include failure and its corrected fixture also remain in
`repair-contract-first-matrix.json` and `repair-contract-matrix.json`. The
separate [UnitTurn class migration](UNIT_TURN_CLASS_MIGRATION.md) compares against
the repaired body; its extraction and relocation gates are recorded separately.

Original instruction captures are `evidence/original-newturn.asm`,
`original-logall.asm` and `original-debuglog.asm`, generated with `objdump -d
-Mintel --start-address=... --stop-address=... /mnt/c/clash/clash95.exe` for
`0x4118E0..0x411AB0`, `0x411460..0x4114B0` and `0x419120..0x4191E9` respectively.
