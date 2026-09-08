# Road build-mode timing recovery

Track: Win95 reconstruction. Base `d2b31c2`. This bounded repair removes three undefined decompiler temporaries from the reached mission-05 Road-build loop at `Builder_StartRoadBuildMode` (`0x00425540`). It does not change route state, movement cost, Road eligibility, marker cadence, input handling, or any campaign acceptance baseline.

## Original evidence

The protected `sub_425540` calls `Time_Now` exactly twice in the marker-animation path. Neither call is preceded by argument-register setup: the first follows `sub_40ADF0`; the second follows the unsigned ten-tick threshold comparison. The first timestamp is compared as `now - 10 > g_RoadBuildModeLastAnimationTick`. When that condition succeeds, the second timestamp is stored into `g_RoadBuildModeLastAnimationTick` before the animation frame is advanced and the four adjacent tiles are redrawn.

The protected `Time_Now` procedure has no stack arguments. It saves incoming ECX and EDX, calls `QueryPerformanceCounter`, overwrites EAX/EDX from the returned counter, overwrites EBX/ECX from `Frequency`, divides through `__I8D`, restores EDX/ECX and returns the computed timestamp in EAX. Its normalized listing is pinned by SHA-256:

```
7e0120ef65c18c2ef2117f1f8dc308d1a5073a0d9f3d2a5325f441d2fa037e9d
```

Therefore the recovered two-argument `Time_Now` declaration is a calling-convention/decompiler artifact for this use. Passing arbitrary uninitialized C locals is not original behavior; explicit zero placeholders preserve the current compatibility signature while making the actual no-input contract clear.

## Change

Only `Builder_StartRoadBuildMode` changes:

- `Time_Now(v8, v7)` becomes `Time_Now(0, 0)`;
- `Time_Now(v9, g_RoadBuildModeLastAnimationTick)` becomes `Time_Now(0, 0)`;
- the now-unused `v7`, `v8`, `v9` declarations and stale undefined-variable comments are removed.

The two timestamp calls, ten-tick comparison, second-call store, frame increment, modulo-8 masking and four redraws remain in original order. The `Time_Now` interface is deliberately not changed globally because many unrecovered callers still carry legacy register artifacts and a repository-wide signature rewrite would exceed this frontier.

Exactly one current manifest body hash changes. All 4,157 function identities, historical body hashes, warning/link/header/coverage baselines and campaign route fixtures remain unchanged.

## Validation

The focused regression pins the original `Time_Now` implementation, checks the two bare original Road calls, rejects any retained undefined timing locals and verifies the source still preserves the original threshold/store/frame order. Repository split-source and generated-header checks must pass before publication; normal PR CI remains the compiler/link/coverage gate.

This is not retail runtime proof and does not advance mission 05. The active campaign frontier remains normal turn-7 refresh followed by Road continuation west through `(48,50)`, `(47,50)`, `(46,50)`, `(45,50)`.
