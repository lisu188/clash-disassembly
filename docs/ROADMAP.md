# Roadmap

## Near Term

- Keep default build/tests fast and reliable.
- Keep route and soak probes opt-in unless they are short and stable enough for
  default CTest.
- Continue mission `04` from gate breach to castle capture and objective
  completion through authentic tactical/world input.
- Harden durability coverage around:
  - main menu idle and exit,
  - world-map panning and repeated input,
  - starting castle economy/barracks enter/exit,
  - first-mission movement and attack/autoresolve,
  - tactical battle enter/return,
  - campaign route replay,
  - artifact pruning and nonblank frame evidence.

## Campaign Recovery

- Preserve direct mission boot as a quarantined repair path only.
- Prove real menu entry and natural auto-advance before treating a campaign arc
  as accepted.
- Maintain route env status accurately: do not mark a route `complete` without
  objective-complete evidence or the exact intended milestone.
- Extend route coverage from missions `00..03` to `04..19` without objective
  mutation, mission skipping, forced AI no-op shortcuts, or fake demo loops.

## Runtime Durability

- Grow opt-in soak tiers from 2 minutes to 10 minutes, 30 minutes, then 2 hours
  or more after shorter tiers are stable.
- Track crashes, hangs, final markers, frame count, nonblank pixels, mean
  luminance, unique colors, frame progression, input responsiveness, artifact
  size, log truncation, and memory growth where available.
- Add save/load roundtrip and longer AI-turn scenarios only after the relevant
  route surfaces are stable.

## Long Term

- Complete a behaviorally faithful recovered loop for menu-driven campaign
  progression, world movement, castle screens, production/economy/cure/training,
  tactical battles, autoresolve, AI turns, mission objectives, save/load, and
  extended play sessions.
- Continue semantic structure, unit, and stat recovery only when evidence is
  strong enough and the change helps the recovered build remain faithful.
