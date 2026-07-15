# Source organization

Production targets compile the canonical recovered implementation from 138 GNU
C17 translation units under `src/`.
`data/recovered_sources.json` is the authoritative function/source manifest.
Tests link independently compiled coverage objects and do not include recovered
implementation files directly.

## Canonical areas

- `src/` contains behavior attributable to the original
  executable, its private headers, and the exhaustive source list.
- `src/platform/` contains the separately compiled SDL/X11 host implementation.
- `src/compatibility/` contains decompiler support and quarantined runtime scaffolding.
- `src/instrumentation/` contains mission tracing and other observation-only support.
- `src/bootstrap/` contains the host executable entrypoint.

## Recovered subsystem groups

| Directory | Translation units | Functions | Purpose |
|---|---:|---:|---|
| `core/` | 2 | 16 | Bootstrap and shared utilities |
| `render/` | 4 | 132 | Core rendering, surfaces, sprites, palettes, and fonts |
| `world/` | 4 | 104 | Strategic map, minimap, camera, fog, roads, and map UI |
| `units/` | 7 | 186 | Strategic units, stacks, movement, fatigue, and morale |
| `buildings/` | 18 | 370 | Buildings, economy, production, garrisons, and modal UI |
| `battle/` | 3 | 50 | Tactical interaction, simulation, rendering, and outcomes |
| `persistence/` | 6 | 136 | Special sites, saves, and persistence helpers |
| `strategic/` | 6 | 204 | Campaign rules, strategic AI, and host functions |
| `clips/` | 52 | 1,706 | Embedded CLIPS language and object/compiler runtime |
| `media/` | 18 | 743 | Audio, music, AVI, and media support |
| `runtime/` | 16 | 403 | Input-facing behavior and recovered legacy runtime |
| `state/` | 2 | 20 | Prelude helpers and quarantined global-state ownership |

The cutover removed the unified aggregator, recovered include-C fragments, and
legacy path symlinks. `docs/SOURCE_PATH_MAP.csv` retains those historical paths
and their canonical replacements. Repeated or non-monotonic address families
remain separate where reordering could change recovered declaration or
definition order.

The canonical split has private headers, one-definition global ownership,
evidence-backed static-helper decisions, and an independently compiled unit
harness. Recovered non-ASCII byte literals use terminated two-digit hexadecimal
escapes so GCC and Clang preserve the same encoded bytes. Calls with decompiler-
shaped register arguments are normalized when random and API-string finalizer
compatibility shims have explicit argument-free contracts. Clang reports
recovered pointer/integer conversion debt as warnings, while implicit
declarations, implicit integers, and invalid return types remain hard errors.
Handwritten platform and compatibility functions retain explicit prototypes
under strict warning-as-error builds. See `docs/SOURCE_SPLIT.md` for the cutover
evidence and remaining warning and retail-route validation debt.

See `docs/SOURCE_LAYOUT.md` for path, regeneration, and validation rules.
