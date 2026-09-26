# Project Tracks

The two tracks below support the full C++ reimplementation mission in
[AGENTS.md](../AGENTS.md). Progress in one does not complete the other.
[STATUS.md](STATUS.md) owns current counts, the validated endpoint and Next Target;
this page owns scope, acceptance language and priority order.

## 1. Win95 reconstruction and SDL runtime

Recover original game behavior into maintainable GNU++20 under `src/`, preserving
identity and evidence in `data/recovered_sources.json`, `clash95.map` and
`clash95.asm`. The maintained runtime is C++ only; the completed language cutover
does not complete class/type/ownership migration or original-game parity.

Recovered subsystem sources own gameplay. `src/platform/` owns host adaptation,
`src/compatibility/` quarantines temporary support, and `src/instrumentation/`
observes execution. Instrumentation and platform glue must not become alternate
implementations of game behavior. See [source layout](SOURCE_LAYOUT.md),
[class migration](CPP_CLASS_MIGRATION.md) and [recovery policy](REVERSE_ENGINEERING.md).

## 2. Campaign-route validation

Route env files under [tests/first_campaign_arc_routes/](../tests/first_campaign_arc_routes/)
are the machine-readable status for all 20 missions. The
[runtime milestone index](RUNTIME_MILESTONES.md) maps probes to retained evidence.
Mission `05` is the active incomplete route; use [STATUS.md](STATUS.md#next-target)
and its current worklog links rather than an older march or draft.

A route may become `complete` only after natural objective completion, no
mission-failure marker, current nonblank frame evidence, deterministic retained
checkpoints and repeatable regression success. Direct mission boot is diagnostic.
Final campaign acceptance requires real Campaign-menu entry, natural objectives,
persistence and automatic advancement.

## Immediate priority sequence

1. Keep both compiler builds and applicable public gates under review; retain and
   compare unresolved failures without changing baselines to hide them.
2. Advance the Mission-05 frontier in [STATUS.md](STATUS.md#next-target), including
   the blocked Road-mode observation prerequisite, using original-accepted input.
3. Prove Campaign-menu entry and at least one natural automatic mission advance.
4. Recover `CSS_Init` and reached compatibility behavior behind the SDL seam.
5. Continue evidence-backed class, type and ownership migration and close the
   remaining subsystem gaps toward the full definition of done.

[ROADMAP.md](ROADMAP.md) holds long-term goals;
[BUILD_AND_TEST.md](BUILD_AND_TEST.md) holds executable validation commands.

## Completion language

| Term | Required claim |
| --- | --- |
| decompiled | A decompiler emitted a body. |
| named | An original identity has an evidence-backed semantic name. |
| buildable | The reconstructed target compiles and links. |
| runnable | The executable reaches a verified authentic runtime state. |
| typed | A family/state block has evidence-backed C++ types and ownership. |
| reimplemented | Production C++ expresses that behavior without reachable decompiler/compatibility placeholders, with provenance retained. |
| parity-validated | The claimed path has relevant original-vs-reimplementation evidence. |
| route-complete | A mission meets the direct-route gates above. |
| campaign-complete | The campaign runs from the real menu through natural completion and automatic advancement. |

No earlier term implies a later one. Whole-game completion also requires every
item in the [definition of done](../AGENTS.md#1a-definition-of-done).
