# D1 (PLAYER family) — census and adversarial-panel findings

Status: **no constants minted.** This records the census, the panel verdicts, and
the deferred candidates, per `AGENTS.md` §11 ("Record rejected and uncertain
candidates, not only confirmations").

## Census

Folded absolute offsets of the player record (base `PLAYER_RUNTIME_STATE_OFFSET`
= 140024, stride `PLAYER_DATA_STRIDE` = 1423, 5 players), excluding
`src/strategic/` which a concurrent session owns.

**115 sites / 16 distinct values.** Partitioned by the `delta < stride` predicate:

| population | values | sites | disposition |
|---|---|---|---|
| (a) delta < 1423 — genuine field offsets | 13 | 109 | candidate for this campaign |
| (b) delta >= 1423 — record addresses | 3 | 6 | carve-out, see below |

Per-value, population (a):

| value | delta | sites | already named as |
|---|---|---|---|
| 140028 | +4 | 3 | `PLAYER_DISPLAY_NAME_OFFSET` |
| 140039 | +15 | 1 | `PLAYER_CAMERA_LEFT_OFFSET` |
| 140043 | +19 | 1 | `PLAYER_CAMERA_TOP_OFFSET` |
| 140051 | +27 | 52 | `PLAYER_IS_HUMAN_OFFSET` |
| 140055 | +31 | 3 | `PLAYER_AI_INTELLIGENCE_OFFSET` |
| 140059 | +35 | 2 | *(none)* |
| 140063 | +39 | 13 | `PLAYER_RELIGION_FLAG_OFFSET` |
| 140067 | +43 | 4 | *(none)* |
| 140071 | +47 | 3 | `PLAYER_TECH_LEVEL_OFFSET` |
| 140073 | +49 | 7 | `PLAYER_BATTLE_IDLE_FLAG_OFFSET` |
| 140077 | +53 | 2 | `PLAYER_BATTLE_IDLE_TURN_COUNT_OFFSET` |
| 141441 | +1417 | 17 | *(none)* |
| 141443 | +1419 | 1 | `PLAYER_QUEEN_RELATIONSHIP_STATE_OFFSET` |

### Carve-out: population (b), delta >= stride

These fold a **non-zero player index** into the literal, so they are record
addresses, not field offsets. `141447` = `PLAYER_DATA(1)`; `141451` =
`PLAYER_DATA(1) + 4`; `141486` = `PLAYER_DATA(1) + 39`. Naming them as field
constants would be false. They want the accessor form and are out of scope for
`tools/apply_literal_names.py`, which can only emit a bare identifier.

Proof at `src/persistence/0044AE90_0044E850_persistence_005.c:258-263`, where
consecutive stores walk player 0, 1 and 2 of the same field:

```c
*(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) = 1;   /* PLAYER_DATA(0)     */
*(_DWORD *)(gameData + 141447) = 1;                        /* PLAYER_DATA(1)     */
*(_DWORD *)(gameData + 142870) = 1;                        /* PLAYER_DATA(2)     */
```

Note 142870 lies **outside** the one-stride window that `literal_inventory.py`'s
`derived_candidates` scans, so the census window must be the full table
(140024..147138) whenever population (b) is in scope.

### Census-tool caveat

`literal_inventory.py` reports `derived_candidates[].count` per matching
(offset, stride) window, not per site, inflating counts ~1.9x. Size batches from
a direct grep.

## Panel verdicts

Three blind adversarial verifiers per name, each given the sites and code but
never the proposer's rationale, each required to supply a non-empty
`alternative_interpretation`.

### +27 `PLAYER_IS_HUMAN_OFFSET` — CONFIRMED (52 sites)

Not refuted by any lens. The decisive evidence is the developer's own debug
string at `src/strategic/004506B0_004530D0_strategic_001.c:1228-1234`:

```c
"(gameinfo gracz %d komputer %d inteligencja %d chrzesc %d)",
    playerIndex,
    1 - *(_DWORD *)(playerRecord + 140051),   /* komputer   = computer */
    *(_DWORD *)(playerRecord + 140055),        /* inteligencja = AI level */
    *(_DWORD *)(playerRecord + 140063)         /* chrzesc    = christian */
```

Printing `1 - field` under the label *komputer* fixes both the meaning and the
polarity. Corroborated by the multiplayer slot switch
(`persistence_004.c:419-448`, which writes only 0 or 1), by the turn loop
(`world_003.c:339-350`), and by the missions-10/11 hang whose cause was a
missing `= 0` store for player 2. Width is `_DWORD` at all 58 occurrences.

Rejected alternatives, each with a distinct owner: "is alive/active" is delta
**+0**; "locally-viewed player" is *derived from* this flag at
`world_002.c:784-785`; the 3-way `controller_mode` reading was already retracted
in the rename log.

### +15 / +19 `PLAYER_CAMERA_LEFT` / `PLAYER_CAMERA_TOP` — CONFIRMED (1 site each)

A LEFT/TOP pair on two adjacent lines (`world_003.c:294-295`) is the most
swappable naming in the batch and the exact B5 shape, so this got a dedicated
axis check. The verifier deliberately refused to use `MAP_VIEW_LEFT_OFFSET` /
`MAP_VIEW_TOP_OFFSET` as evidence, since those are prior work that could itself
carry a transposition, and instead found arithmetic binding the axis **on the
player fields themselves**:

`src/persistence/0044AE90_0044E850_persistence_005.c:544-555` clamps +15 against
`MAP_WIDTH_TILES - 9` and +19 against `MAP_HEIGHT_TILES - 7`. Width bounds the
one, height bounds the other. The centering biases corroborate: `-4` on the axis
whose span is 9, `-3` on the axis whose span is 7.

Three further independent confirmations: the viewport tile loop is 9 wide x 6
tall stepping `screenX += 64` / `screenY += 64` (`units_005.c:668-690`), and
9 x 64 = 576 fits 640 horizontally but cannot fit 480 vertically; the minimap
click handler derives +15 from `g_MouseCursorRawX` and +19 from
`g_MouseCursorRawY` (`world_004.c:251-275`); and the asm pairing
`0x22307 <-> 0x222E8` / `0x2230B <-> 0x222EC` never crosses across all 22 sites.

Both are int32, matching `RECOVERED_STRUCTURES.json` and packing cleanly after
`display_name char[11]` at +4..+14.

**Precision nit, not an axis error:** these are *tile* coordinates, not pixels.
`PLAYER_VIEW_ORIGIN_COL` / `_ROW` would be strictly better than `CAMERA_*`.
Accept as-is if the batch keeps the established `camera_*` convention.

**Correction to the census:** only two *folded-literal* sites remain, but the
field already has ~20 accessor uses via the existing `PLAYER_CAMERA_LEFT_OFFSET`
/ `PLAYER_CAMERA_TOP_OFFSET` macros. The two lines under test are stragglers
being brought in line with established naming, which raises confidence rather
than lowering it.

### +1417 — REFUTED. Proposed `PLAYER_POPULATION`; do not use.

Two of three lenses refuted; the third confirmed the *structure* but dissented on
the *label*. Five independent disconfirmations:

1. **Signed.** Reads are `movsx`, not `movzx` (`clash95.asm` `loc_44F8F3`,
   `loc_4501CE`). A headcount is unsigned.
2. **Zero-init, never seeded.** `PlayerRuntimeState_ResetDefaults` sets it to 0
   (`persistence_004.c:1379`). A player starting with three castles and hundreds
   of peasants has this at 0.
3. **Strictly zero-sum +/-1.** Every one of the 16 mutation sites is `inc`/`dec`
   by exactly 1, always in matched pairs (one player up, another down). No store
   of a computed total exists anywhere in the image.
4. **Moves when nothing is transferred.** At `units_007.c:769-770` the attacker
   loses but its stack survives and no building changes hands — yet the counter
   still swings. This also refutes the fallback "count of holdings" reading.
5. **A real population field already exists elsewhere** — per *building*, 12-bit
   unsigned at building offset +430, grown by `Building_UpdatePopulationGrowth`,
   and labelled `populacja`/`population`/`Bevölkerung` on the castle screen
   (string table at `clash95.asm:417640`).

The display path confirms the field goes negative: `persistence_006.c:1094-1169`
tracks a minimum only for values below zero and rebases the bar over
`[min, max]`, whereas its two siblings (nation score, military strength) use
`123 * v / max` with no negative handling.

The only support for "population" was the local variable names in
`persistence_006.c`, which are themselves a prior naming guess over this same
literal — circular, not independent.

**Consensus reading:** a signed per-player zero-sum tally of engagements won
minus lost. **But the panel explicitly declined to endorse any replacement**
without further work, since "net holdings delta" also fits the mutation sites.
`RECOVERED_STRUCTURES.json` has no entry at +1417 at all.

**Action: DEFER.** Leave the raw literal. If a name is ever minted, rename the
misleading `population*` locals in `persistence_006.c:1066-1203` with it.

### +43 — REFUTED. Proposed `PLAYER_PRIMARY_CASTLE_INDEX`; do not use.

Both words of the label fail.

- **Not "castle".** `createCastle` places castles of type **1 and 2**
  (`strategic_005.c`: type 1 for "Ughuata" :159 and "Hopenberg" :215; type 2 for
  the rest). Types 1 and 2 are peers — same 300 max HP
  (`recovered_state.c:8980`), same 2x2 footprint (`buildings_001.c:449-458`).
  Type 2 is specifically the *peasant-founded, level-0* variant. A player whose
  only castle is type 1 leaves this field at -1 forever.
- **Not "primary".** The value has **zero readers in the entire binary** — 4
  writes, 0 reads (`22323h` appears exactly 4 times in `clash95.asm`). Nothing
  ever asks which castle is primary.
- **The clear path contradicts owner-tracking.** At `buildings_002.c:297` the
  building's owner byte is overwritten with the *capturer* before :311 reads it
  back to select the player record. So the clear targets the **capturer**, never
  the player who lost the castle — whose field is left dangling.

`Rules_SyncCastleFactOwner` three lines above the site is not corroboration: it
maintains a CLIPS handle in the *building* record at +463, and `Building_New`
asserts a castle fact for every building type unconditionally.

**Action: DEFER.** If minted, the honest spelling is
`PLAYER_FIRST_BASE_CASTLE_BUILDING_INDEX` with a comment recording: set only for
type 2, only while -1; cleared only on the capturer's record; no readers.

### +35 — DEFER LIFTED, writer found. Candidate `PLAYER_SHOW_EVENT_ANIMATIONS`, Medium.

The earlier defer was caused by a search-shape gap, not by absent evidence: the
writer uses a **base pointer**, not the folded literal, so a grep for `140059`
could never find it.

`PlayerRuntimeState_ResetDefaults` (`persistence_004.c:1372`, asm
`clash95.asm:114115` `mov dword ptr [eax+23h], 1`) sets it to **1**, and that is
the only write in the image.

Both readers gate **presentation only** — the state mutation happens either way:
the trap reveal at `buildings_009.c:976-990` (the mask clear and
`Rules_RetractTrapFact` sit outside the `if`), and the god-anger banner at
`buildings_009.c:1345` (the HP-damage loop runs on both branches).

Ruled out: "is human" is +27; "is alive" is +0; "locally-viewed" is never updated
on view change; religion is +39 and *is* cleared per scenario, whereas +35 never
is. Note `Rules_LogMissionSetupInfo` logs +27, +31 and +39 but deliberately skips
+35 — the developer's own config log does not treat it as configuration.

**Confidence is Medium and should stay there:** the field is provably constant
(1) in every reachable state, so execution cannot discriminate "animations
enabled" from any other always-true predicate. The name records what is proven,
not intent. The missing evidence is a store of 0, which — if it exists — lives in
scenario `.dat` data, not in the executable.

## Dynamic confirmation (2026-07-19, recovered binary under gdb)

The static panel verdicts above were re-tested by *running* the recovered engine
and sampling the player records live, which turned two of them from
argued-from-code into observed.

Method: `clash95_bootstrap /A5` (all-AI multiplayer map) under Xvfb, driven by
`gdb -batch` with a breakpoint on `Unit_NewTurn` printing the five player records
each turn. `gameData` is `int gameData;`
(`src/state/00000000_0054FFFF_recovered_state.c:12298`), so player *n*'s field at
delta D is `*(gameData + 140024 + n*1423 + D)`.

**Controls first** — without these, an all-zero reading could just mean the
address arithmetic is wrong:

| field | observed | expected |
|---|---|---|
| +15 camera left, p0 | **4** | tile column |
| +19 camera top, p0 | **22** | tile row |
| +27 is-human, p0..p4 | **0 0 0 0 0** | all-AI game, so every player AI |
| +39 religion, p0 | **1** | `ResetDefaults` default of 1 |

The camera pair is the strong one: **(4, 22)** matches exactly the camera
position independently recorded by the tile-comparison work in
`tools/vm/README.md` ("the recovered all-AI camera NEVER moves (230 frames at
(4,22))"). That is an independent measurement, taken for an unrelated purpose,
agreeing to the tile. It confirms both the address arithmetic **and** that +15 is
the column and +19 the row — the axis assignment the panel established statically.
The all-AI zeros likewise confirm +27 = is-human empirically.

**Result for +1417: `0` for all five players, on every one of 229 samples across
46 game turns.**

Since the controls read true, this is a real observation rather than an artifact,
and it independently refutes `PLAYER_POPULATION`: a population cannot be zero for
five players who are running castles and buildings for 46 turns.

**Honest limitation:** the run produced **zero battles**, so this *falsifies the
population reading* without *positively confirming* the win/loss-tally reading —
the +/-1 transfer was never exercised. Confirming the tally needs a run in which
`Unit_Attack` actually fires. Note the absence of battles across 46 all-AI turns
is itself consistent with the known "recovered all-AI AI path is not fully
executing" issue recorded in `tools/vm/README.md`, and is worth a look in its own
right.

Evidence: `/tmp/mn/gdb3.log` (229 turn samples), `/tmp/mn/gdb4.log` (controls),
scripts `/tmp/mn/p2.gdb` and `/tmp/mn/p3.gdb`.

## Save-data proof (2026-07-19) — +1417 is SETTLED

The strongest evidence needed no VM and no engine run at all: it was already on
disk in the shipped save games, from real 1997-era playthroughs.

`docs/SAVE_DAT_FORMAT.md` records that a `.dat` is a 16-byte label followed by a
**verbatim `gameData` image**, so a player field is simply
`0x10 + 140024 + 1423*n + delta`. For +1417 that is `0x10 + 141441 + 1423*n`,
read as `int16`. All six installed saves are exactly 586414 bytes and decode
cleanly.

| save | turn | +1417 p0..p4 | sum | active | human |
|---|---|---|---|---|---|
| 0, 1 | 1 | `0 0 0 0 0` | 0 | p0..p3 | p0, p4 |
| 2, 3 | 34 | `3 -3 0 0 0` | 0 | p0, p1 | p0 |
| 4 | 1 | `0 0 0 0 0` | 0 | all 5 | p0 |
| **5** | **69** | **`-1 0 1 0 0`** | **0** | **all 5** | **p0** |

Three independent properties fall out, and together they close the question:

1. **NEGATIVE.** In slot 5 the value is **-1 for player 0** — who is the *human*
   player (`+27 == 1`), still *active* (`+0 == 1`), 69 turns into the game with a
   castle and units. A population cannot be negative. This alone refutes
   `PLAYER_POPULATION`, and it is exactly what the `movsx` sign-extension and the
   negative-aware bar normalisation predicted.
2. **ZERO-SUM.** Every save sums to **exactly 0** across all five players — the
   conserved invariant implied by the 16 matched `++`/`--` mutation sites, now
   observed on real data rather than argued from code.
3. **ACCUMULATES.** Slots 2/3 show `+3 / -3` split between precisely the two
   active players, so the field tallies repeatedly rather than tracking a
   momentary state.

**Verdict: +1417 is a signed, zero-sum, accumulating per-player tally of battle
outcomes.** `PLAYER_POPULATION` is refuted three independent ways — the static
adversarial panel, the recovered-engine run, and now real save data. The real
population statistic is a separate per-*building* 12-bit unsigned field at
building offset +430.

**Still deliberately not minted.** The evidence fixes what the field *is not* and
its mechanical shape, but "battle tally" versus "net conquest/holdings tally"
remains open, and the panel declined to endorse a specific spelling. A name still
needs its own panel round. Recording the shape is more valuable than guessing the
label — and per §3.4 of the RE guide, conservative names beat wrong names.

Reproduce with: decode each `C:\clash\save\*.dat` at `0x10 + 141441 + 1423*n` as
`int16`, alongside `+0` (active), `+27` (is-human) and `140022` (turn, u16).

## Live confirmation in the ORIGINAL binary (2026-07-19)

Read out of the original `clash95.exe`'s own RAM, running under the headless QEMU
Win98 rig, via QMP `human-monitor-command`:

```
LIVE +1417 p0..p4 = 65535  0  1  0  0     (65535 = 0xFFFF = -1 as int16)
turn=69  owner=0  viewed=0
is_human p0..p4  = 1  0  0  0  0
```

The human player (`+27 == 1`), on their **own turn**, 69 turns into a live game,
holds **-1**. Same values as the on-disk save, now observed in the original
engine's live memory rather than inferred from a file or from the recovered
reimplementation.

`PLAYER_POPULATION` is therefore refuted **four independent ways**: the static
adversarial panel, the recovered-engine run, the save files, and the original
binary's live RAM.

**What is still NOT observed:** the +/-1 transfer itself. No battle was made to
occur, so the mutation was never caught in the act. The tally reading rests on
the code (16 matched `++`/`--` sites), the conserved zero-sum across all six
saves, and the `+3/-3` accumulation — all strong, but the live transfer remains
the one piece of evidence not yet collected. See `tools/vm/README.md` for how far
the VM route got and what blocked it.

## Consequences for the batch

**D1 must not mint yet.** The panel reviewed 4 of 13 values; the other 9 rest on
rank-5 manifest evidence alone, which the campaign rules do not accept as a
second signal. Each needs its own panel before minting.

The refutation rate is the headline: **2 of 3 proposed names were wrong,
including one rated High confidence.** Per the plan's own tripwire, a wave with
100% acceptance would indicate a broken adversarial lane; this wave went the
other way and the lane is working. Solo naming — even careful solo naming
reading the same code — is not sufficient for this campaign.

## Spun-off findings (outside this batch)

1. **An existing B5-shape mislabel in committed code.**
   `g_TempleGiftOutcomeTable_OwnCultActive` / `...Inactive`
   (`buildings_007.c:338-348`, local `cultActiveFlag` at :423) and
   `g_TreasureDigOutcomeTable_TempleActive` / `...Inactive`
   (`persistence_002.c:79-81`) switch on **140051 = IS_HUMAN**, not on any
   cult/temple-active state. The Active/Inactive axis in those names is the
   human/AI axis. Right field, wrong axis — the exact failure shape as B5.
2. **A suspicious duplicate store**, `persistence_005.c:261-262`, writes
   `*(_DWORD *)(gameData + 140051) = 0;` twice in succession. The surrounding
   pattern (`:263` clears player 2 at 142897) suggests one was meant to target
   player 1 at 141474. Check against `clash95.asm` before touching.
3. **An 18th site for +1417** at asm `loc_4501CE` (0x4501CE) has no recovered C
   counterpart: 0x44FE70..0x4506B0 is a gap between `persistence_006.c` and
   `strategic_001.c`. Any macro for this field must cover it, and
   `persistence_004.c:1379` writes the same field in unfolded form.
4. **Two undocumented player fields**: `RECOVERED_STRUCTURES.json` jumps
   1357 -> 1419 with nothing at +1417, and `recovered_types.h` jumps +31 -> +39
   with nothing at +35 or +43.
5. **A latent transposition trap.** At `src/units/00416850_00419120_units_005.c:681-682`,
   `TILE_TERRAIN_ROW_STRIDE` (1400) multiplies the **column** index while
   `TILE_TERRAIN_RECORD_STRIDE` (14) multiplies the **row** index — the terrain
   array is column-major, so `TILE_TERRAIN_ROW_STRIDE` is arguably misnamed (it
   is a per-*column* stride). Read naively, that line appears to prove
   `MAP_VIEW_LEFT` is a row, which would argue for transposing the camera pair.
   It does not — the `screenX += 64` / `colIndex < 9` loop structure settles the
   axis — but the trap is live and should be defused before someone "corrects" a
   correct pair.
