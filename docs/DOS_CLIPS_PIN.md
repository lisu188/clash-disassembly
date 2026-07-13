# DOS Clash — embedded CLIPS version

The DOS build (`clash.c`, decompiled from `CLASH.EXE`) embeds the CLIPS rule
engine as ~48% of its code (see `MODULES.md`, address range `0x89860`–`0xEB580`).
This pins the CLIPS version, which is required before naming CLIPS functions
because CLIPS renamed/added functions across the 6.x line.

## Method

CLIPS emits diagnostics via `PrintErrorID("MODULE", id, …)` (in the DOS binary,
the function at `0xDA560`). The set of `(module, id)` pairs is a stable,
high-discrimination fingerprint of a specific release. We extracted the DOS
binary's 195 distinct `(module, id)` pairs (63 modules) and scored them against
CLIPS reference source trees from SourceForge `clipsrules`.

| CLIPS reference | source `(module,id)` pairs | DOS pairs matched |
|---|---:|---:|
| 6.24 (`clips_core_source_624.zip`) | 231 | **192 / 195 (98.5%)** |
| 6.30 (`clips_core_source_630.zip`) | 234 | 191 / 195 (97.9%) |

**Pinned: the CLIPS 6.2x family, with 6.24 as the closest available source proxy.**

### Pre-environment caveat (important for naming)

The DOS binary contains **zero `Env`-prefixed strings** and registers its
builtins under un-prefixed names (`AgendaCommand`, `FactsCommand`, …). The CLIPS
*environment API* (the `EnvXxx(theEnv, …)` split) arrived in 6.2/6.3, so the DOS
build predates it — it is effectively a **6.0/6.1-era** engine whose error-id
*layout* already matches 6.24. Consequently, when a recovered name comes back as
`EnvArgRangeCheck` from the 6.24 source, the DOS-era identifier is the
**un-prefixed** `ArgRangeCheck`. Our tooling strips a leading `Env` from
6.24-sourced names for DOS use, recording the source name alongside as evidence.

## String-anchor matching + calibration (Stage-0)

A general **string-anchor matcher** (`tools/dos/clips_match.py`) generalizes the
error-id method to *all* string literals: a literal referenced by exactly one CLIPS
source function and exactly one DOS function is a definitive name match.

**Calibration gate — passed.** The 394 functions the DOS binary registers by name
via `DefineFunction2`/`registerClipsCallback` are ground truth
(`tools/dos/dos_registered_groundtruth.json`). Auditing the anchors against them:

- String-anchor: **0 contradictions / 394 (100% precision)**.
- Error-id anchor: **1 contradiction / 130 (99.2%)** — `0xE7E50`, where the error
  moved from `FetchCommand` (DOS) into the `TextLookupFetch` helper by 6.24 (version
  skew). The false anchor was **dropped** (`tools/dos/dos_dropped_false_anchors.json`);
  registered names always win.

The matcher also **caught a pre-existing mislabel**: `0xAA6B0`, hand-labeled
`addClipsFact`, is actually `Retract` (its body is the exact `EnvRetract` logic —
join-in-progress guard, then fact-list unlink + free-list push). Corrected via the
master map (`tools/dos/dos_name_conflicts.json`).

**Precedence:** registered ground-truth (immutable) > string-anchor / error-id
evidence (override stale hand-labels, dropped where they contradict ground truth) >
hand-labels. Consolidated into `tools/dos/dos_master_map.json` (built by
`tools/dos/build_master_map.py`).

**Coverage so far:** **782 / 4,219 named (19%)**, of which **600 / 2,015 in the CLIPS
region (30%)** — before the sequence-alignment extension.

## Reproduction

- Sources: `https://sourceforge.net/projects/clipsrules/files/CLIPS/6.24/clips_core_source_624.zip`
  (sha256 `07b981cd186a62af10a2f3bef67be7c99e9a2d3951f851e84c6de1ad3e17d990`) and
  `.../6.30/clips_core_source_630.zip`
  (sha256 `01555b257efae281199b82621ad5cc1106a395acc095b9ba66f40fe50fe3ef1c`),
  unpacked under `C:\Clash\ref\clips\{624,630}\` (outside the repo).
- Tooling: `tools/dos/clips_xref.py` (fingerprint scoring + `(module,id)` →
  CLIPS-function anchoring).
