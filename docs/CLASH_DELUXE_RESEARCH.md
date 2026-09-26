# Clash Deluxe and clash.y0.pl research

Status: 2026-09-26.

## What is confirmed

`clash.y0.pl` is an unofficial Polish Clash site with a separate forum. Both the site and forum were reachable during the September 26 research; the tracked `research/clash_y0/live_status.json` also records HTTP 200 responses. Earlier access failures do not establish permanent unavailability. Boghute Ara advertised the site publicly in late 2015 and again in 2016. Community references identify pages for missions and gameplay mechanics, including the opening phase, queen, taxes, traps and ambushes.

Boghute Ara described a fan modification developed by changing values at specific addresses in `CLASH.EXE` with a hex editor. The stated changes included typo fixes, queen-request costs, workshop and forge prices, unit licence and production costs, combat-stat rebalancing, selected terrain bonuses, and setting initial unit morale to 10. The author said the rebalance also affects both campaigns.

The author's [release thread](http://forum.clash.y0.pl/viewtopic.php?p=1424#p1424) dates the first `Clash Deluxe 0.1` announcement to January 1, 2020; the January 3 announcement found in the earlier research is a later public reference. The dated December 26, 2021 update announces version **0.13** and the name **Clash De Luxe**. The [live download listing](http://clash.y0.pl/download/) still names 0.13 and describes replacing `CLASH.EXE`. No newer release or Win95 compatibility was verified. The current thread title must not be used to date 0.13 to January 2020.

## OpenClash and source-code leads

**OpenClash** is Griz's separate C#/Unity remake, announced on [August 9, 2016](http://forum.clash.y0.pl/viewtopic.php?p=150#p150). Its [January 24, 2018 update](http://forum.clash.y0.pl/viewtopic.php?p=496#p496) describes version 0.2.3 and says a public download still required separating original assets. A [May 2026 community report](http://forum.clash.y0.pl/viewtopic.php?p=1783#p1783) says development had stopped; this is second-hand correspondence, not a fresh public announcement by the developer.

Griz's [Resource Unpacker repository](https://github.com/Grizmu/ClashResUnpacker) is a distinct tool. Its public source does not establish that OpenClash, Clash De Luxe or the original game has released source code. A contributor identifying himself as Jacek discusses the [CLIPS integration](http://forum.clash.y0.pl/viewtopic.php?p=164#p164) and [finding scenario files in 2016](http://forum.clash.y0.pl/viewtopic.php?p=166#p166); the archive itself has not been inspected. These are follow-up leads, not recovered production artifacts.

The September 26 live research covered selected Clash forum topics and pagination, GOG, VOGONS, Old-Games.RU, PPA and GRYOnline, plus targeted searches of other communities. It did not cover every forum or every post. Contact correspondence and private outreach receipts remain outside the public source tree.

Primary external references used for this summary:

- https://www.gry-online.pl/gry/clash/komentarze/zd107e
- https://www.ppa.pl/forum/hyde-park/25727/leryx-longsoft-co-sie-z-nimi-stalo
- https://imperium.heroes.net.pl/post/48998
- https://www.filmweb.pl/videogame/Clash-1998-620720/discussion/Co%C5%9B%2Bpodobnego%2C2035773

## Repository artifacts

`tools/scrape_clash_y0.py` queries the Internet Archive CDX index for the entire `clash.y0.pl` domain, including subdomains. It normalizes session-id variants, records the first and latest capture for each unique URL, identifies high-value download candidates, probes the live roots, and can download the latest archived copy of every indexed URL into an untracked local mirror while recording SHA-256 hashes and fetch status.

Tracked generated metadata lives in `research/clash_y0/`:

- `research/clash_y0/inventory.csv`: one row per normalized archived URL.
- `research/clash_y0/download_candidates.csv`: URLs likely to be archives, executables, documents, patches, or download-related resources.
- `research/clash_y0/fetch_results.csv`: result and SHA-256 for each attempted archived download during the refresh job.
- `research/clash_y0/live_status.json`: current reachability of the historical site roots.
- `research/clash_y0/summary.json`: capture and fetch totals plus Deluxe/download-related URLs.

The raw mirror is intentionally not tracked. Use `artifacts/clash_y0_mirror/` or another ignored directory when reproducing it locally.

## Refresh and local recovery

From the repository root:

```bash
python3 tools/scrape_clash_y0.py \
  --output research/clash_y0 \
  --mirror-dir artifacts/clash_y0_mirror \
  --max-file-mib 128 \
  --max-total-mib 1024
```

The GitHub workflow `.github/workflows/clash-y0-research.yml` also refreshes the tracked metadata. The workflow mirrors archived bytes only into runner-temporary storage, computes hashes, commits metadata, and does not publish the raw mirror.

## How Clash Deluxe can help recovery

Treat Clash Deluxe as a differential oracle, not as authoritative original behavior.

1. Identify the recovered Deluxe archive or executable from `research/clash_y0/download_candidates.csv` and verify its SHA-256 from `research/clash_y0/fetch_results.csv` or a fresh local run.
2. Do not overwrite `clash95.exe`. Extract candidate files under `artifacts/` and record file type, size, hashes, embedded version strings and archive provenance.
3. Determine which original executable family the mod targets before comparing offsets. The author explicitly called the modified file `CLASH.EXE`; that does not prove it is byte-compatible with this repository's Win95 `clash95.exe`.
4. If a matching unmodified executable is available, byte-diff the pair. Coalesced changed spans are high-value candidates for gameplay constants or compact records.
5. Prioritize spans whose changed values can be correlated with the author's documented edits: unit stats, morale, terrain bonuses, queen-request costs, workshop/forge prices, unit licence costs, unit production costs and corrected strings.
6. Map candidate values back into assembly, recovered structures and call sites. A Deluxe diff can locate a value; original assembly/data-flow evidence is still required before naming a field or changing recovered behavior.
7. If Deluxe targets a DOS build rather than the Win95 build, use it semantically: identify table shape, ordering, value ranges and relationships, then search for the same patterns in `clash95.asm`, `UNIT_TYPES_AND_STATS.json`, `RECOVERED_STRUCTURES.json` and recovered source.
8. Record negative evidence. A value that differs in Deluxe but has no corresponding Win95 pattern is useful evidence that the executable families diverged.

## Evidence confidence

Public posts establish that the mod existed, that its author hex-edited `CLASH.EXE`, the broad categories of changes, the release date and the published download page. They do not establish the exact base executable revision, file name inside the archive, byte offsets, or compatibility with `clash95.exe`. Those details must come from recovered files and binary inspection.
