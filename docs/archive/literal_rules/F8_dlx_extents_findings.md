# F8 DLX physical extents

Track: Win95 reconstruction, behavior-preserving numeric naming.
Frontier: existing DLX sprite object allocations and original payload-handle copy.
Source: `35f3adb6e60798db83521faca3711e8c7935fed8`.
Confidence: high for the seven approved sites and both physical meanings.

The independently reviewed scope is **seven literal substitutions, two names,
four canonical TUs and five function bodies**. This expands the earlier three-site
prospect by four allocations of the same proven DLX object. It introduces no new
domain and does not authorize arithmetic, pointer, control-flow or layout changes.

## Exact sites

All file/line locations below refer to the bound source commit above.

| Canonical source | Function | Complete expression (only marked literal changes) |
|---|---|---|
| `src/render/004046D0_00405D20_render_003.cpp:1330` | `DLXSpriteSet_Load` | `sprite_set[entry_index] = Mem_Alloc(22, entry_index, entry_size, (DWORD)(intptr_t)sprite_set);` |
| Same file `:1417` | `DLXSpriteSet_CopyEntriesFrom` | `new_sprite = Mem_Alloc(22, entry_index, (char)(intptr_t)source_set, entry_count);` |
| `src/units/00412C00_00414350_units_003.cpp:257` | `UnitSpriteCache_GetOrLoadEntry` | `sprite_record = Mem_Alloc(22, 0, 0, 0);` |
| `src/buildings/0043E500_0043FDE0_buildings_006.cpp:1058` | `BuildingSpriteCache_LoadEntry` | `spriteHandleTheme0 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);` |
| Same file `:1066` | `BuildingSpriteCache_LoadEntry` | `spriteHandleTheme1 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);` |
| Same file `:1074` | `BuildingSpriteCache_LoadEntry` | `spriteHandleTheme2 = Mem_Alloc(22, entry_index, spriteAssetIndex, allocContext);` |
| `src/render/00405DB0_00407D20_render_004.cpp:315` | `DLXSprite_CopyFrom` | `qmemcpy((void *)(uintptr_t)(sprite + DLX_SPRITE_PAYLOAD_HANDLE_BYTE_OFFSET), alloc_buffer, 4);` |

The first six sites use `DLX_SPRITE_OBJECT_BYTES`, with an exact single-token macro
body `22`. The final site uses `DLX_SPRITE_PAYLOAD_HANDLE_BYTES`, body `4`.
Neither spelling has a suffix. No casts, argument values, or other tokens change.

## Two independent physical-layout signals per name

**Object extent, 22 bytes.**

1. Independent original borrowed and owning set paths load `eax = 16h`, call
   `Mem_Alloc`, test the result and pass it to `sub_406260` or `sub_406350`
   (`clash95.asm:8641-8648`, `8841-8846`). Those addresses are the manifest-backed
   `DLXSprite_ConstructFromBuffer` and `DLXSprite_ConstructOwningCopy` bodies.
2. The borrowed constructor writes a dword at object + `12h` (`9378`); the owning
   constructor writes the same last dword (`9476`), and the independent destructor
   tests it (`9497`). The last four-byte field therefore ends at byte 22. The copy
   producer independently writes it at `9553`. This is a physical object extent,
   not the ten-byte serialized header or serialized payload size.

The additional four allocation sites have their own primary caller evidence:

- Original `Unit_SetFlag` allocates `16h` (`29726-29729`) and on the nonnull branch
  passes that same `eax` to `sub_4060E0` (`29751-29759`). The recovered body lives
  in `UnitSpriteCache_GetOrLoadEntry` and its retained adapter, with the same
  immediate `DLXSprite_LoadCachedEntry` call at source line 259.
- Original `sub_43F630` has three independently checked allocation/callee paths:
  `96621-96626` (theme 0), `96639-96656` (theme 1), `96661-96678` (theme 2). Each
  allocates `16h` and calls `sub_4060E0` with its matching `buildin[123].s32` path.
  Current lines 1060/1068/1076 retain the same DLX loader calls.
- This common loader `sub_4060E0` initializes the payload dword at +`0Ah` (`9246`),
  sets serialized size +`0Eh` (`9290`), and copies/consumes the payload handle at
  +`0Ah` (`9303-9325`). That matches the independent constructor/destructor/serializer
  layout (`9380`, `9391`, `9494-9508`, `9628-9631`). Equal allocation size alone was
  not used to establish the extra sites' identity.

**Stored payload-handle extent, four bytes.**

1. Original copy sets `ecx = 4`, sets destination to object + `0Ah`, stores the
   allocator return on the stack and performs the dword/tail copy
   (`clash95.asm:9547-9564`). This is the current `qmemcpy` size argument.
2. Independent borrowed construction writes a dword at +`0Ah` (`9391`), destruction
   loads that dword as the free argument (`9494-9508`), and serialization loads it
   as the source address (`9629`). The next dword starts at +`0Eh` (`9380`, `9628`).
   The established `DLXSpriteView` accesses the payload as `std::uint32_t`
   (`src/render/dlx_sprite_view.h:31-32`, mutable counterpart `77-78`).

The payload-handle extent is the original stored handle width. It is not native
pointer size, a sprite-set entry stride, an allocator flag or an alignment claim.

## Existing definitions and type preservation

`DLXSpriteView::kObjectSize = 22` exists at `src/render/dlx_sprite_view.h:12`, and
its tail static assertion (`103-104`) corroborates the physical extent. Its type,
like the view's other layout constants (`13-18`), is `std::size_t`. It is not an
exact raw-token/type substitute for the current unsuffixed `int` literal `22`.
There is no existing named payload-handle extent member; `kPayloadHandleOffset`
is an offset, not a width. `sizeof(std::uint32_t)` and native `sizeof(pointer)`
would also fail the exact-token requirement; the latter changes the domain.

Fresh manifest/prelude reads found neither proposed macro name already defined.
The four F7 macros in `src/recovered_types.h:266-269` and
`tools/constants_manifest.json:202-205` remain the established serialized-header,
payload-offset, size-offset and ownership-offset domains. Preserve and reuse them
where already present. No view, enum or native-layout conversion is proposed.

## Corpus audit and exclusions

The same source-binding pass visited all **147 canonical independently compiled
TUs**, counting **252 numeric tokens of value 22** and **4,043 of value 4**.
Comments, strings and preprocessor directives are excluded. The full value-22
candidate enumeration and the 28 four-valued sites in sprite/DLX-named functions
are retained in the batch's private `audit/canonical-candidates.json`.

The private `audit/call-contexts.json` supplements the initial same-line query with token-aware
enclosing calls, including multiline arguments. It finds seven allocation-call
tokens of value 22: the six accepted DLX allocations plus the excluded CLIPS
bitmap node allocation below. Of 21 four-valued copy/fill call tokens, the only
standalone literal size argument classified as `call_arg` is the accepted DLX
handle copy. Other occurrences are sizes multiplied by counts or unrelated
offsets. No additional same-domain literal site was established.

Specific excluded or deferred candidates:

- `Rules_AddBitmapValue`, `src/clips/00481720_00482D40_clips_001.cpp:711`, allocates
  `(_DWORD *)0x16` via `Mem_HeapAllocWithRetry`. Its bitmap/hash-node consumers
  (`:739`, `:1051`, `:1140`) establish a different object family; decimal value
  22 does not justify a DLX name or respelling hexadecimal `0x16`.
- A seventh *original* DLX allocation occurs in the region represented by
  `Input_Flush`, at `clash95.asm:147570-147615`. Current canonical
  `src/strategic/00460950_004612E0_strategic_006.cpp:482-485` only resets
  `g_CursorOverlayPresented`; there is no allocation literal to rename. Restoring
  original code would be a separate behavioral-recovery task.
- `DLXSpriteSet_Save`, render004 `:79`, `entry_cursor += 4`, is a set-entry handle
  stride, proven by original save loop `clash95.asm:8917-8924` and independently
  by the set-load indexing at `8631`, `8646`, `8651-8653`. It needs its own domain;
  do not use the payload-handle width merely because both equal four.
- `nmalloc_(payload_size, 4)` in cached loading (render004 `:239`) and the set
  payload allocation's second argument (render003 `:1315`) are recovered call
  plumbing, not an explicit copy width or proven alignment. Preserve both.
- Render004 `:344` and render002 `:198` read a format word at sprite + 4; this is
  a header-field offset. Render004 `:408`, `:460`, `:542` and units006 `:398`
  advance codec streams over back-reference data, not over payload-handle fields.
- Palette advances at render004 `:167`, `:181`, `:184`, unit sprite cache key
  offsets, theme/frame-index arithmetic, vtable offsets and scratch-array indices
  remain different domains.
- DLX character selectors `22`/`0x16u` in battle/building/info popups, menu row
  extents, raw packed tables, string-array extents, CLIPS offsets/bit shifts,
  mission coordinates and audio status values are not DLX object extents.
- Dimension naming, ownership boolean values, RLE masks, the cached-loader logging
  `10`, the six-element local `alloc_buffer`, saved-register locals and native
  `void **` payload access remain deferred exactly as in the earlier boundary.

## Reviewed application and paired census

The independent private `audit/prepare.py` supplies both definitions only in memory to the existing
`apply_literal_names.validate_rules` and `resolve` APIs. It writes `definitions.json`,
`rules.json`, `reviewed-plan.json` and `result.json` under this audit directory;
it never calls apply or updates tracked constants, source, guards or manifests.
Here "audit directory" means the private batch's `audit/` directory, not this
tracked rules directory. The published inputs are `F8_constants.json` and
`F8_dlx_extents.json` beside this report.

Result: seven rules resolved to seven sites; six exact `22` and one exact `4`;
zero rejected sites and zero respellings. All 147 canonical source hashes and
the primary source/assembly/tool inputs are unchanged across the run; HEAD is
unchanged. The complete source-hash binding is in `result.json`. The exact WSL
invocation is in `command.sh`; `check_call_contexts.py` uses the same environment
and binds each scanned file to that receipt (falling back to the immutable Git
blob only if another agent subsequently edits a source file).

The coordinating review applies the same seven sites through the existing
reviewed-plan mechanism as batch `F8-dlx-extents`. There are zero rejections or
respellings. Two provenance rows aggregate the six object allocations and one
payload-handle copy; five current body hashes change. An independent structural
comparison confirms every other manifest field, all 4,157 historical identities,
historical hashes and class metadata are unchanged. The constants installer
preserves all untouched bytes of the prelude and constants manifest.

Both complete preprocessor streams are byte-identical to their fresh baselines
before guard regeneration. All 147 independently preprocessed TUs per compiler
also match exactly, with zero differences. Regeneration adds exactly two constant
assertions (328 total). A separate focused comparison removes only those two
fully reviewed assertion declarations from each final stream and requires exact
byte equality for everything else; both comparisons pass. Regenerating subsystem
headers, TU includes and usage catalogs produces no further tracked change.
The independent source review also reconstructs each edited TU from the frozen
plan and verifies all other 143 canonical source hashes remain unchanged.

The paired lexical census visits every one of the 147 canonical sources:

| Numeric code tokens | Before F8 | After F8 | Decrease |
|---|---:|---:|---:|
| All numeric literals | 79,148 | 79,141 | 7 |
| Integers | 78,970 | 78,963 | 7 |
| Small integers below 10 | 50,920 | 50,919 | 1 |
| Floating literals | 178 | 178 | 0 |

The per-file decreases are buildings 006: three, render 003: two, render 004:
one and units 003: one. These counts describe lexical numeric tokens, not a claim
that every remaining value has a known semantic name. Numeric definitions,
packed data, ordinary arithmetic and the deferred candidates above remain.

Durable private evidence is rooted at
`artifacts/magic-numbers-dlx-extents-20260924/`. The independent prospective plan
is in `audit/`; the applied coordinator plans, installation and application
receipts are at the root; `census/comparison.json` binds both full source censuses.
Historical F1-F7 rules, findings and evidence remain untouched.

Commands run from this worktree in WSL, with translated Git environment paths:

```sh
export GIT_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git/worktrees/clash-disassembly1
export GIT_COMMON_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git
export GIT_WORK_TREE=/mnt/c/Users/andrz/.codex/worktrees/62e9/clash-disassembly
export PYTHONDONTWRITEBYTECODE=1
cd "$GIT_WORK_TREE"
python3 artifacts/magic-numbers-dlx-extents-20260924/census/census.py baseline
python3 artifacts/magic-numbers-dlx-extents-20260924/install_definitions.py
python3 tools/apply_literal_names.py docs/archive/literal_rules/F8_dlx_extents.json --batch F8-dlx-extents --plan artifacts/magic-numbers-dlx-extents-20260924/reviewed-plan.json
python3 tools/apply_literal_names.py docs/archive/literal_rules/F8_dlx_extents.json --batch F8-dlx-extents --expect artifacts/magic-numbers-dlx-extents-20260924/reviewed-plan.json --plan artifacts/magic-numbers-dlx-extents-20260924/applied-plan.json --apply
python3 artifacts/magic-numbers-dlx-extents-20260924/verify_application.py
python3 artifacts/magic-numbers-dlx-extents-20260924/census/census.py candidate
python3 artifacts/magic-numbers-dlx-extents-20260924/validation/preguard_capture.py 35f3adb6e60798db83521faca3711e8c7935fed8
python3 artifacts/magic-numbers-dlx-extents-20260924/validation/compare.py preguard --pp-only
python3 tools/gen_constant_guard.py
python3 tools/gen_subsystem_headers.py --write --write-tu-includes all
python3 artifacts/magic-numbers-dlx-extents-20260924/validation/guard_pp.py 35f3adb6e60798db83521faca3711e8c7935fed8
```

## Validation baseline

Fresh GCC 13 and Clang 18 builds at `35f3adb` pass, as do all eight public
asset-free gates and both warning checks. Each compiler reference retains all
153 raw objects, stripped objects and normalized disassemblies, full linked
surface snapshots, both executables, the raw archive and exact build recipes.
Both the combined 147-boundary preprocessing stream and 147 independent TU
streams are captured per compiler. The 811 production/tooling inputs remain
unchanged throughout baseline capture.

The fresh raw link checks retain 453 GCC / 705 Clang differences with zero
identity crosscheck errors. The header check retains 23 ratchet rows and one
`UnitStack.hpp` parameter-name policy finding. The Markdown checker retains two
absent private historical references in `CPP_CLASS_NATIVE_BASELINE.md` and
`CPP_CLASS_ORIGIN_REFRESH.md`. Complete findings are retained, including rows
truncated by the normal CLI. A supplemental capture's initial missing required
Python argument is retained as an unsuccessful attempt; the corrected read-only
capture completes without rerunning either compiler build.

Fresh native GCC CTest reports 1,092 passes, zero assertion failures and 524
isolated harness crashes among 1,616 registered cases. Coverage passes at
6,165 / 6,656 lines (92.623197%) with all 718 selected functions covered and none
uncovered. All 462 native input hashes remain unchanged. The binary and all
6,366 coverage-profile archive members are durably retained and verified.
These are pre-change measurements; later integration and candidate validation
must be recorded separately. No runtime, visual or campaign milestone advances.

Both Linux build trees and evidence copies use persistent storage. Every
validation command retains the unchanged five-GiB physical backing-volume
reserve; no global cleanup, WSL restart or ratchet increase is used.

## Subsequent naming frontier

The remaining `DLXSpriteSet_Save` expression `entry_cursor += 4` has a separately
confirmed entry-handle stride domain. Original save-loop instructions at
`clash95.asm:8914-8925`, getter indexing at `8974-8978` and destructor stepping at
`8710-8725` independently support a future exact-int
`DLX_SPRITE_SET_ENTRY_HANDLE_BYTES` name. Other entry walks already use typed
indexing or pointer increments. This single-site follow-up requires a fresh
reviewed plan after F8; it must not reuse the sprite object's payload-field width.
The popup's `spriteSetOffset += 4` walks an array of whole sprite sets and stays
in a different domain. The bounded follow-up audit is retained in
`audit/next-family-entry-stride.md`.
