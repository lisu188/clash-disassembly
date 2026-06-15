# clash-disassembly

Recovered C/SDL reconstruction of the original `clash95` game binary. The
project is intentionally evidence driven: `clash95.asm` is the behavioral
source of truth, while `clash95.c` is the recovered implementation under test.

## Quick Map

- `clash95.asm` - authoritative disassembly evidence. Do not edit.
- `clash95.c` - recovered game logic. Keep changes small and assembly-backed.
- `clash95.map`, `clash95.exe` - original symbol/binary corroboration.
- `bootstrap_main.c` - host executable entry that enters the recovered boot path.
- `platform_sdl.*` - SDL/X11 runtime bridge for presentation, timing, and input.
- `compat/`, `defs.h`, `windows.h` - Win32, Watcom, DirectDraw, and Hex-Rays
  compatibility shims used by the recovered C.
- `tests/` - smoke tests, route automation, frame metrics, and route scripts.
- `tools/` - host-side inspection utilities.
- `docs/source-map.md` - detailed source classification and compaction policy.
- `docs/milestone-index.md` - route milestones, validation commands, and gaps.

## Build And Test

Use an out-of-tree build so generated files stay out of the source checkout:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_bootstrap -j2
ctest --test-dir build --output-on-failure
```

Route regressions that require real SDL/X11 input are opt-in:

```sh
CLASH95_ENABLE_CAMPAIGN_ROUTE_REGRESSION=1 \
  ctest --test-dir build -R clash95_campaign_route_04_regression --output-on-failure
```

Metadata validation:

```sh
python3 -m json.tool RECOVERED_STRUCTURES.json >/tmp/recovered_structures.check
python3 -m json.tool UNIT_TYPES_AND_STATS.json >/tmp/unit_types_stats.check
git diff --check
```

## Artifact Policy

Generated build trees, frame dumps, route artifacts, screenshots, crash dumps,
and local agent scratch are ignored. Durable evidence stays tracked only when it
helps future reverse engineering: assembly, original binary/map data, recovered
metadata, route scripts, progress logs, and documented milestone artifacts.

If a compaction decision could remove behavior evidence, keep the file and note
the deferred decision in `docs/source-map.md` or `docs/milestone-index.md`.
