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
