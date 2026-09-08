# DLX cached-entry view migration

Track: Win95 reconstruction, bounded render-storage readability. On 2026-09-08,
`DLXSprite_LoadCachedEntry` at `0x004060E0` adopts the existing non-owning
`DLXSpriteMutableView` and `DLXSpriteView`. The baseline is commit
`5376757fe8cefd1af5eab0907601fab3ab9bc121`, including the earlier DLX accessor
and buffer-constructor migration. No behavioral blocker is removed and no
campaign or visual milestone is promoted.

## Change and evidence

The [reviewed migration](../data/readability_migrations/dlx_cached_entry_v1.json)
changes one canonical body in
[the render translation unit](../src/render/00405DB0_00407D20_render_004.cpp).
Five raw field accesses become named payload-handle/serialized-size operations;
the two header-length literals reuse `DLXSpriteView::kSerializedHeaderSize`.
No new constants, types, public symbols or ownership operations are introduced.
The existing view header and all caller signatures remain unchanged.

Original `sub_4060E0`, `clash95.asm:9229..9361`, corroborates the DWORD payload
handle at `+10`, DWORD serialized size at `+14`, and ten-byte header read. The
existing byte-safe view and its independently exercised layout tests provide
the second signal. No instruction in this routine writes the ownership DWORD
at `+18`. Confidence is high for these fields and this bounded migration.

The original signed entry-index and entry-length expressions remain intact.
The header constant is cast to `int` for the read and to `DWORD` **before**
subtraction, preserving the unsigned 32-bit arithmetic before assignment to
the existing signed payload-size local. The source still reads size after the
header callback, stores and tests the allocated payload handle, and uses the
cached payload arguments for the final read. The allocator argument `4` and
unrelated debug-log argument `10` are unchanged.

The current body hash changes from
`2e82235ac16edff0b170e3e6a721afb573ca85ba6f2bcd07df448436954d344a` to
`133ed67aff8d37b4d8e43e483419c741e68e9efc7fdfa1dc00edf39805983668`.
The scoped manifest update preserves all 4,157 ordered function identities,
140 canonical translation-unit paths and historical metadata/hashes. All 15
readability specifications replay as already applied without source/include
edits. Inverting just the approved substitutions reproduces the baseline body
token stream exactly; direct token or machine-code equality is not claimed
for this accessor migration.

## Executed contract and limits

The [public fixture](../tests/tools/fixtures/dlx_cached_entry/README.md) extracts
the actual production function and compares it with the hash-pinned baseline
body. Eighteen scenarios each run with aligned and deliberately unaligned
storage: 36 paired cases on GCC 13 and Clang 18 at both O0 and O2, or 144 paired
cases in total. It compares callback traces and complete canaried sprite,
payload and directory bytes, with separate assertions for the assembly-supported
common successful contract. Two negative controls demonstrate rejection of
ownership changes and stale size reads before the header callback.

This executes the current C++ bodies, not original x86 instructions. The
common assembly-supported path and canonical-only compatibility paths are
explicitly distinguished. Existing differences remain deferred:

- The canonical null-query return has no corresponding original guard.
- The canonical start offset is cached before the EOF callback; the original
  reads it afterward and again for seek.
- The canonical final payload read uses cached handle/size values; the original
  reloads the fields.
- Original allocation-failure reporting reloads size, has different variadic
  arguments and invokes the apparently nonreturning `sub_472558(10)`. Synthetic
  returning-quit hooks pin only the current compatibility behavior.
- The canonical `strcpy` prefix handling replaces the original 255-byte copy.

These are separate behavioral-recovery candidates, not repairs made by this
batch. Tests use valid low32 backing, padded signed-index cases and inert
callbacks for huge or negative read counts. They do not prove malformed-asset
safety, overflowing address/entry arithmetic, real allocation/filesystem
behavior, ownership correctness or whole-original-loader equivalence.

## Validation results

| Check | Fresh baseline | Final migration |
| --- | --- | --- |
| GCC 13 / Clang 18 Debug builds | Both pass | Both pass |
| Four public asset-free gates per compiler | 8/8 pass | 8/8 pass |
| Recovered warnings, GCC / Clang | 6582 / 6591; ratchets pass | Unchanged; ratchets pass |
| Linked symbol/data ratchet differences, GCC / Clang | 428 / 680; both fail | Unchanged; zero library crosscheck errors |
| Header-surface ratchet | 14 failures | Identical 14 failures and output |
| Full tooling suite | Not repeated as a baseline suite | 258 tests pass, zero skips |
| Generator, split-source, pure metadata and save-format checks | Baseline inputs retained | All pass |
| Readability-spec replay | 14 already-applied specs | 15 already-applied specs, zero edits |
| Native wrapper | 1087 passed, 0 failed, 527 isolated crashes / 1614 | Same totals and exact crash identities on the final repeat |
| Frozen coverage | 6158/6651 lines, 92.59%; all 718 functions reached | 6160/6651 lines, 92.62%; all 718 reached |

The first post-edit native run had 1088 passes and 526 isolated crashes. Its
only difference in crash identities was the existing
`cov20_crt.tz_year_starts_label6_a1_flag_set` probe, whose fixture explicitly
documents an uninitialized-pointer path. A repeat of the unchanged final binary
reproduced all 527 baseline crashes. The initial post-edit run also retained an
unsharded gcov checksum diagnostic; the coverage reader uses the wrapper's fresh
16 worker shards, and the final repeat had no profiling diagnostic.
`DLXSprite_LoadCachedEntry` is outside the frozen coverage set. These measurements
do not establish a native-crash repair or coverage improvement from this change.
No warning, header, link or coverage ratchet is raised.

Of 143 archive objects, 142 are byte-identical. In the changed render object,
only the loader's existing executable section changes: GCC 558 to 641 bytes,
Clang 402 to 459. Five existing view helpers are newly emitted in this object;
all other existing executable sections and their relocations are identical.
Stored object data is identical. Linked symbol profiles have zero differences,
including data classes, sizes and order, with no game-data address changes.

The initial strict linked-data comparison rejected byte differences; those
failed attempts remain as evidence. A subsequent ELF relocation audit accounts
for every differing stored byte: 604 GCC / 561 Clang read-only pointer slots,
197 writable pointer slots per compiler, and one initializer pointer all still
resolve to the same function and offset after code movement. Linked text grows
by 358 GCC / 240 Clang bytes, with corresponding unwind metadata changes.
No blanket machine-code or linked-byte identity claim replaces this explicit
review. The audit-compiled evidence directory retains the section, symbol and
relocation reconstruction details.

The existing headless [first-Road probe](../tests/first_campaign_arc_routes/mission_05_first_road_probe.env)
passes with both final binaries: GCC in 257.464 seconds and Clang in 246.713 seconds. All ten decoded
save checkpoints match across compilers. Both retain stack 4 at `(49,50)` on
turn 6, 2 AP, no active path, roads 867/879 and the same 228-tile visibility
state. The endpoint also matches the historical first-Road state, including
raw occupied-slot bytes. No route env or script changes, direct-route promotion,
turn-7 continuation or campaign advancement follow. Runtime evidence includes
the exact commands/environment, binary/input hashes, decoded saves, full logs,
15 checkpoints and 24 sampled frames per compiler; unsampled raw frames remain
in the recorded native temporary roots, with pruning disabled.

The final cross-compiler frames differ by mean absolute RGB error 1.223/255
and 16,254 pixels. The required original/reconstruction comparison uses the
retained original capture from **2026-09-06 07:22:11 UTC**, not a new original
execution. Its state evidence matches both current saves: world/viewport and
stack headers, all 310 unit-slot bytes, active-path count, complete visibility
bitmap and six Road words. The original frame, state, driver and launch command
are copied with SHA-256 provenance into runtime/original-reference under this
batch's artifact root.

| Full unmasked 640 x 480 frame pair | Mean absolute RGB error /255 | Nonmatching pixels |
| --- | --- | --- |
| Historical original / current GCC | 11.268319 | 286966 |
| Historical original / current Clang | 11.280944 | 287024 |

Both side-by-side PNGs, exact frame paths, commands and full/cropped metrics are
retained in the runtime directory and its original-comparison record. Missing
coordinate labels, displaced stack badge, absent unit/status panels, lower-left
map/text corruption and fog/water differences remain visible. The historical
reconstruction frame at
artifacts/magic-numbers-20260906/routes/clang-18/final-01/durable/route/checkpoint-mission05-first-road-built.bmp
already shows the duplicated map and missing lower-left unit HUD.
Of the 16,254 cross-compiler changed pixels, 11,155 occur at locations observed
varying during the final wait; the other 5,099 remain unresolved in the lower-left
area. Only five fall in the cursor-local crop. Location overlap does not prove
an animation cause, and those differences are not attributed to this migration.
No visual parity, repaired HUD or fresh original execution is claimed.

## Validation commands and retained evidence

All checks run in Linux/WSL against this worktree, not the separate main
checkout. The local shell environment translates the inherited Windows Git
paths explicitly:

```sh
cd /mnt/c/Users/andrz/.codex/worktrees/62e9/clash-disassembly
export GIT_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git/worktrees/clash-disassembly1
export GIT_COMMON_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git
export GIT_WORK_TREE="$PWD" PYTHONDONTWRITEBYTECODE=1
python3 tools/apply_readability_migration.py data/readability_migrations/dlx_cached_entry_v1.json
python3 tools/apply_readability_migration.py data/readability_migrations/dlx_cached_entry_v1.json --write
python3 tools/update_split_manifest_hashes.py --update --only DLXSprite_LoadCachedEntry
python3 -m unittest discover -s tests/tools -p test_dlx_cached_entry.py -v
```

Private commands, before/after source and manifest snapshots, compiler binaries
and archives, object disassembly, audits, individual check outputs and runtime
records are retained under artifacts/readability/dlx-cached-entry-20260908/.
The build.sh script records each compiler's clean Debug build, warnings and
link checks, and the four explicit public asset-free gates. The coverage.sh
script records the native wrapper and frozen 89.7% / 718-function coverage gate.
These private scripts are not prerequisites for the public focused fixture.
