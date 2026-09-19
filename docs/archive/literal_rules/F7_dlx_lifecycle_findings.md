# F7 DLX sprite lifecycle constants

Track: Win95 reconstruction. Frontier: behavior-preserving numeric naming in
the existing DLX sprite lifecycle and its direct serialized-size/payload
consumers. This batch does not change rendering behavior, object layout,
allocation, ownership, file I/O or campaign status.

## Frozen scope and reviewed rules

The rules target canonical source at
`02c00bf77087457bdd01bbde3fd4020ffa499286`:
`src/render/00405DB0_00407D20_render_004.cpp`. They are prospective rules for
that source, not a replay of the original F1/F2 census. Historical F1 through
F6 rules and findings remain untouched.

`F7_dlx_lifecycle.json` contains 23 nonoverlapping rules. Each identifies the
canonical path, exact enclosing function and complete containing expression;
only its named `lit` capture is replaced. All source spellings are unsuffixed
decimal integers. There are no enum substitutions, suffix changes, arithmetic
rewrites, cast changes or pointer-scaling changes.

| Macro | Exact replacement body | Sites | Established role |
|---|---:|---:|---|
| `DLX_SPRITE_SERIALIZED_HEADER_BYTES` | `10` | 6 | Header extent in serialized entry bytes |
| `DLX_SPRITE_PAYLOAD_HANDLE_BYTE_OFFSET` | `10` | 8 | Byte offset of the stored 32-bit payload handle |
| `DLX_SPRITE_SERIALIZED_SIZE_BYTE_OFFSET` | `14` | 6 | Byte offset of the complete serialized entry size |
| `DLX_SPRITE_OWNS_PAYLOAD_BYTE_OFFSET` | `18` | 3 | Byte offset of the dword controlling payload release |

The existing private `DLXSpriteView` names already establish these concepts:
`kSerializedHeaderSize`, `kPayloadHandleOffset`, `kSerializedSizeOffset` and
`kOwnsPayloadOffset` in `src/render/dlx_sprite_view.h:15-18`. Those constants
have type `std::size_t`; directly substituting them into the remaining raw
expressions would change tokens and potentially arithmetic types. The four
macros retain those naming domains while expanding to the original literal
tokens. No new view conversion is part of F7. The existing view definitions,
their tests and previously migrated loader remain unchanged.

## Independent evidence

Confidence is high. Original producer and consumer instructions agree; the
current private view is additional corroboration, not the sole proof.

- **Serialized header size:** the borrowed constructor `sub_406260` loads
  `ecx = 0Ah`, copies that many bytes and advances the source by `0Ah`
  (`clash95.asm:9376-9391`). Independently, the serializer `sub_406460` writes
  `0Ah` bytes from the object followed by `size - 0Ah` bytes from the payload
  (`clash95.asm:9624-9631`). The owning copy has the same initial copy count and
  later subtraction (`clash95.asm:9533-9544`, `9550-9554`, `9568-9578`).
- **Payload-handle field:** the borrowed constructor stores `source + 0Ah`
  at object offset `0Ah` (`clash95.asm:9389-9391`). Independently, destruction
  loads that field and passes it to `j__nfree_` (`clash95.asm:9494-9508`);
  owning copy stores the allocator result there (`clash95.asm:9551-9564`),
  and serialization uses it as the write source (`clash95.asm:9629`).
  Palette remapping loads the same field into its byte-stream cursor
  (`clash95.asm:9657-9660`). These are field displacements, distinct from the
  equal-valued serialized header extent.
- **Serialized-size field:** the borrowed constructor stores its entry-size
  argument at object offset `0Eh` (`clash95.asm:9380`). Independently,
  `DLXSpriteSet::save` accumulates each such value into the next directory
  offset (`clash95.asm:8917-8921`), and sprite serialization subtracts the
  header extent before writing the payload (`clash95.asm:9628-9631`). The
  field is the complete serialized entry size, not payload-only size.
- **Ownership field:** the borrowed constructor stores zero at object offset
  `12h` (`clash95.asm:9378`), whereas the owning constructor and owning copy
  store one (`clash95.asm:9476`, `9553`). Independently, destruction tests this
  dword and frees the nonnull payload only when it is nonzero
  (`clash95.asm:9494-9508`). This supports the established ownership name
  without extending the meaning of unrelated zero/one values.

`clash95.map:38` independently preserves the public `DLXSpriteSet::save`
spelling for the set serializer. The remaining historical function identities
and original addresses stay unchanged.

The older `DLXSpriteGlyphRecord` entry in `RECOVERED_STRUCTURES.json` contains
historical width/height terminology and calls offset 14
`compressed_stream_size_bytes`. F7 does not depend on those older dimensional
labels or silently rewrite that record. The original constructor/serializer
pair and current `DLXSpriteView` establish the narrower meanings used here.
The separate `DLXSpritePackedPayloadPointer` record corroborates the payload
field's original 32-bit width and documents why native pointer reads need
their own behavioral recovery.

## Exact occurrence ledger

Line numbers below refer to the frozen canonical source. Column-level byte
positions and raw spellings are retained by the generated reviewed plan.

| Function | Source lines | Replacements |
|---|---|---|
| `DLXSpriteSet_Save` | 78 | Serialized-size field, 1 site |
| `DLXSprite_ConstructFromBuffer` | 261 | Serialized-header source advance, 1 site |
| `DLXSprite_ConstructOwningCopy` | 270, 271 | Payload-handle and ownership fields, 2 sites |
| `DLXSprite_Destroy` | 282, 284 | Payload-handle and ownership fields, 2 sites |
| `DLXSprite_CopyFrom` | 303, 304 (twice), 305, 314 (twice), 315, 316, 321 (four times) | Header extent 3, payload field 4, size field 4, ownership field 1: 12 sites |
| `DLXSprite_Save` | 329, 330 (three times) | Header extent 2, payload field 1, size field 1: 4 sites |
| `DLXSprite_RemapPalette` | 343 | Payload-handle field, 1 site |

The copy's allocation expression remains `DWORD size - int header`, with the
same unsigned arithmetic and assignment behavior. Existing native-pointer
loads in the final copy and serializer remain native-pointer loads. No
expression is regrouped, widened, narrowed or converted to an accessor.

## Preserved boundaries and deferred findings

- `DLXSprite_LoadCachedEntry:243` passes `10` to `Debug_Log`. That argument is
  not proven to represent a serialized-header extent or field displacement;
  F7 leaves it raw.
  Its argument/register provenance belongs to the separately documented
  cached-loader error-path debt.
- `DLXSprite_CopyFrom:315` retains its four-byte payload-handle transfer count,
  and the constructor/copy retain their zero/one values and local array
  extents. Original instructions support the DWORD transfer, but a handle
  width/flag-value naming pass is separate from this four-offset/extent batch.
- The undefined recovered `v2` returns in `ConstructOwningCopy` and `Destroy`,
  and `v20` in `DLXSpriteSet_Save`, are unchanged. Original saved-register
  behavior is evidence for later repairs, not authorization to alter it here.
- The raw `void **` / `const void **` reads in `CopyFrom` and `Save` may read
  beyond the original 32-bit field in the native build. This known access-width
  debt is preserved; exact macro substitution does not certify those paths
  as original-equivalent.
- `Render_BlitCompressedSpriteRLE` in
  `src/render/00402E80_00404660_render_002.cpp:197` is another payload-field
  consumer. Its native-pointer read and adjacent clipping/codec fields are
  outside this lifecycle batch. In the same function, numerous equal-valued
  offsets address `clip_bounds`; they must not inherit DLX field names.
- PCX height parsing at
  `src/render/00401A40_00402BB0_render_001.cpp:422`, tile animation fields at
  render 004 lines 916/926, dimensions, codec tags, palette strides, allocation
  counts and all other numeric domains remain unchanged. These are distinct
  format/state roles even when their tokens equal 10, 14 or 18.
- F5's wall-sprite range, compensating cheat addresses, scalar timebase
  definitions and wider runtime/parser evidence queue remain as documented.
  F6's stack-slot supplement is independent. This bounded batch does not
  claim that every remaining numeric token has an established meaning.

The next bounded naming family is three physical extents: the two unsuffixed
`22` allocation arguments in `DLXSpriteSet_Load` and
`DLXSpriteSet_CopyEntriesFrom` (render 003 lines 1330 and 1417 at F7), and the
unsuffixed `4` payload-handle transfer in `DLXSprite_CopyFrom` (render 004 line
315). Independent borrowed/owning original allocations request `16h`
(`clash95.asm:8641-8648`, `8841-8846`); the final dword at offset `12h` ends at
byte 22. The original copy explicitly transfers four bytes into offset `0Ah`
(`9547-9564`), independently corroborated by constructor/destructor/serializer
dword accesses to that field. Existing view definitions agree. These sites
are candidates for a subsequent reviewed plan, not applied F7 replacements.
The equal-valued set-entry stride and allocator arguments remain separate
domains; native pointer size must not replace the original handle width.

## Review and validation mechanism

Resolve these rules with `tools/apply_literal_names.py` after adding the four
single-token macros and matching `tools/constants_manifest.json` entries.
Require exactly 23 entries, zero rejections, zero respellings and the counts
above. Keep `kind: regex`, function scoping and exact canonical paths; do not
enable value-only matching for these small domain-colliding integers.

Apply only against the reviewed plan with `--expect`, preserving the existing
append-only `docs/archive/win95_constants_rename_accum.jsonl` provenance.
Regenerate the constant guard, current canonical body hashes and affected
usage catalogs without changing original identities or historical hashes.
The coordinating batch records final commands, token/object/data comparisons,
generator checks, build/gate outcomes and durable evidence below after they
complete. No final validation result is implied by this prospective audit.

## Applied naming and census, 2026-09-19

The coordinator applied all 23 reviewed occurrences against the frozen
`02c00bf77087457bdd01bbde3fd4020ffa499286` source using `--expect`.
The plan has zero rejected sites and zero respellings. Four provenance rows
were appended to the existing accumulator, and only the seven listed current
function body hashes changed. The original identities, historical hashes and
class metadata remain unchanged. `F7_constants.json` retains the four exact
definition records supplied to the existing constant manifest.

Both full canonical preprocessor comparisons pass with **zero allowed
differences**: 1,447,745 GCC tokens and 1,450,917 Clang tokens. The comparisons
ran after substitution and before regenerating the guard header. Guard
regeneration then added exactly four compile-time assertions (326 total);
those additions are accounted for separately from source substitution.
Usage regeneration changes no TU include blocks or catalog contents.

The fresh census covers all 145 canonical TUs. Numeric code tokens decrease
from **79,160 to 79,137**, and integers from 78,982 to 78,959. All 178 floats
and 50,910 small-integer occurrences remain. The only changed TU is render 004.
This is a new baseline after the intervening recovery work; it is not directly
subtracted from F5's historical 140-TU census. The unfiltered legacy heuristic
still reports four candidates, with 5,243 data/arithmetic classifications and
73,890 unresolved occurrences. Those automatic classes do not expand F7's
approved scope or establish the meaning of residual values.

Historical readability specifications, including `dlx_entry_buffer_v1.json`,
remain byte-for-byte intact. F7 follows that specification's accepted view
body with the single header-length naming change. Its old exact-body pin is
historical; replaying it against the later F7 body must reject rather than
overwrite the named expression. The reviewed F7 plan and unchanged-token
comparison record this subsequent transformation.

Private evidence is retained under artifacts/magic-numbers-dlx-20260919/:
reviewed-plan.json, applied-plan.json, both census files, pp-gcc-13.log,
pp-clang-18.log and usage-regeneration.log. Compiler evidence is under
validation/baseline and validation/after. Commands execute from this worktree
in WSL with translated `GIT_DIR`, `GIT_COMMON_DIR` and `GIT_WORK_TREE`, not the
separate main checkout.

```sh
python3 tools/apply_literal_names.py docs/archive/literal_rules/F7_dlx_lifecycle.json \
  --batch F7-dlx-lifecycle --plan artifacts/magic-numbers-dlx-20260919/reviewed-plan.json
python3 tools/apply_literal_names.py docs/archive/literal_rules/F7_dlx_lifecycle.json \
  --batch F7-dlx-lifecycle --expect artifacts/magic-numbers-dlx-20260919/reviewed-plan.json \
  --plan artifacts/magic-numbers-dlx-20260919/applied-plan.json --apply
CXX=g++-13 bash tools/pp_token_gate.sh artifacts/magic-numbers-dlx-20260919/validation/baseline/gcc-13/preprocessed.i
CXX=clang++-18 bash tools/pp_token_gate.sh artifacts/magic-numbers-dlx-20260919/validation/baseline/clang-18/preprocessed.i
python3 tools/gen_constant_guard.py
python3 tools/gen_subsystem_headers.py --write --write-tu-includes all
```

## Compiler and tooling validation

Fresh baseline and candidate Debug builds pass with GCC 13.3.0 and Clang
18.1.3, together with all four public asset-free gates in each profile.
All **151 objects per compiler** have identical bytes after removing debug
information, and all 151 normalized disassemblies match. Each complete linked
executable matches after removing only debug information and its build ID.
Strict symbol, named-storage, relocation and initializer comparisons pass
with **no allowances**. The final preprocessor streams add exactly the four
reviewed guard declarations; removing only those declarations makes the full
streams byte-identical to the originals.

Warnings remain 6,574 GCC / 6,576 Clang and pass their existing limits.
The fresh baseline's **20 header failures** (15 printed) and **439 / 691 raw
link differences** remain unchanged, with zero library crosscheck errors.
These checks use `--mode check`; the temporary incoming CI update mode is
not treated as ratchet acceptance, and no tracked baseline changes.
The full tooling suite passes **530 tests** in 216.432 seconds.

Generator, metadata, save-format and Markdown-link checks pass. The final
whitespace check initially flags CRLF endings on the five changed rows of
`tools/constants_manifest.json`; those row endings alone were changed to LF
and `git diff --check` then passes. All existing unchanged rows retain their
original bytes. The original tooling driver failure is preserved, rather
than rewritten as an entirely passing first attempt. The JSON value and
literal definitions are identical; manifest-format-review.json proves that
reinserting those five CR bytes exactly recovers the bound prior file hash.

The private validation runner initially looked for an obsolete combined-object
directory and recorded zero objects. It was corrected to use the actual
`compile_commands.json` outputs, assert the complete canonical source set,
and retain all 151 objects. That diagnostic is preserved; the accepted
comparisons use only the complete recapture. No production repair or rebuild
was needed to correct the evidence reader.

Commands and all input/output hashes are retained in validation/validate.py,
validation/compare.py, validation/baseline/artifact-provenance.json and
validation/after/comparison-summary.json. Full tooling and standalone checks
are driven by final_checks.py and recorded under tooling/.

## Native baseline limitation

The fresh native coverage build at `02c00bf`, before any F7 production edit,
fails in the newly added `tests/unit/cases/test_turn_refresh_ap.cpp`: lines 10
and 27 assign through the read-only `g_UnitTypeBaseActionPoints` table.
The failed baseline's complete compiler log and source hashes remain under
native/baseline/. No native cases ran in that attempt. This inherited fixture
failure was sent to the parallel Road task already validating that fixture;
F7 makes no unrelated test or gameplay repair. Subsequent integration results
must retain this baseline failure separately.

## First-Road replay

The first GCC replay reaches the unchanged route's expected turn-6 endpoint
in **207.334 seconds**: stack 4 at `(49,50)`, 2 AP, no queued path, Road words
867/879 and 228 visible tiles. It uses the existing calibrated pan hold
`0.005` and private periodic capture stride 128; actions and assertions are
unchanged. All raw files remain in persistent private Linux storage and in a
233-member hash-verified archive. No host game window was opened.

The route wrapper exits zero, but the runner's stricter provenance status is
retained as **failed**: the five manifest line endings described above changed
during execution. The entire compiled source, binary, route inputs and retail
configuration bindings remained equal. A separate reviewed-route-acceptance
record accepts the route result only after proving the metadata JSON was
unchanged and reconstructing its original byte hash exactly. It does not
retroactively claim that the original raw-input freeze passed. The original
failed record, formatting review, raw captures and archive remain available
under runtime/results/gcc-13/final-01.

The post-restart Clang replay passes in **192.433 seconds** with its rebound
source, route, configuration and executable hashes unchanged. All ten decoded
saved checkpoints match between compilers. Both final saves match the retained
original world/stack headers, all 310 unit-slot bytes, the 1,300-byte visibility
bitmap, active path count and six Road words. The original reference is the
unchanged 2026-09-06 Road capture; no new original process ran in this batch.

Both original/current frame pairs were inspected. Full-frame comparisons record
285,206 nonmatching pixels and RGB mean absolute difference 11.154106987847221
for GCC, and 287,763 pixels / 11.421130642361112 for Clang. The two current frames
differ in 16,840 pixels; 3,996 are outside the variation observed in the final
wait. Missing labels and unit/status panels, the displaced stack badge,
fog/water differences and lower-left map/text corruption remain visible.
Temporal sampling does not explain every difference. These replays establish
the existing partial route state, not visual parity or campaign advancement.

The exact commands, original reference hashes, compared byte ranges, frame
metrics and capture paths are retained in runtime/README.md and
runtime/results/final-summary.json. The GCC and Clang archives contain 233 and
218 verified members respectively; every raw capture remains retained. Their
SHA-256 values are
`093b939c4e26abff7d375832b6300fe8fd2e3fee4877c339b0e25fbec3e83723` and
`15950198529366fa6c275713ce025cc5d05b1b83ce70bef993286f401dae0662`.

A read-only WSL prospective resolution against the frozen source passed with
the four proposed definitions supplied only in memory: 23 rules, 23 sites,
seven functions, no rejected sites and no respellings. Counts were header 6,
payload field 8, size field 6 and ownership field 3. This checked
`apply_literal_names.validate_rules` and `resolve`; it did not apply a plan or
write source, generated files or provenance. The check used this worktree's
translated `GIT_DIR`, `GIT_COMMON_DIR` and `GIT_WORK_TREE`, with
`PYTHONDONTWRITEBYTECODE=1`.

## Integration with published main

The F7 branch integrates published main
`a0dc2f0e6b88b50d4a989a9a373ad783b67d8efd` at compiled source
`73db040f1c379e585dafdb03daaadb88ae9cc9c3`. The two additive documentation
conflicts retain both independent reports. The incoming class and selection
work remains intact: 147 canonical TUs, six class sources and all 4,157
historical identities. No campaign status changes.

The exact integration-delta audit reverses the original F7 changes and recovers
every incoming production byte and manifest value: 23 substitutions, four
definitions and guards, seven current body hashes, and the separately reviewed
five CR-byte normalization. Historical identities, hashes and rules remain.
The paired immutable-Git-blob census covers all 147 sources. Numeric tokens
decrease from **79,171 to 79,148**, and integers from **78,993 to 78,970**.
All **178 floats** and **50,920 small integers** remain. Only render 004 changes
its numeric count. These lexical counts do not assign semantics to unresolved
values. The script, command, per-file counts and source hashes are retained in
the private paired-census-147 directory.

Both fresh integrated production builds and all eight public asset-free CTests
pass. Warnings are **6,569 per compiler** and pass the unchanged limits.
The inherited raw link differences are **453 GCC / 705 Clang**, with zero
identity crosscheck errors. The incoming header reference contains 23 ratchet
rows and one `UnitStack.hpp` parameter-name policy finding (`a2`); no baseline
or policy is raised. Both compiler binaries, archives, compile commands and
verified bundles of all 153 stripped objects and their disassemblies are
retained under validation/integration/final.

The immutable incoming reference binds all 249 production inputs to compiled
`26c86a9b07e746e3f2a377be003fd137b7aa1a6c` and published `a0dc2f0`; the
publication difference is exactly three documentation files. An initial
comparison correctly rejects a subsequently changed live object in the other
task's build directory. Its continuation uses the published archive's 150
members, checks every member against the original receipt and requires frozen
raw references for the three non-archive objects. It does not accept the other
task's unpublished changes as a baseline.

That final comparison **passes for both compilers**: all 153 objects have exact
stripped bytes and normalized disassembly; strict symbol, storage, relocation
and initializer surfaces match with **zero allowances**. Each complete linked
executable is byte-identical to the incoming reference after removing only
debug information and the build ID. The final receipt is
validation/integration/final/incoming-reference-comparison-ram-summary.json,
SHA-256 `62e385c77a6bc03c4e69d652c188a7202a6ba51fa7c417d3da2869731ba0a1b1`.

The complete integrated tooling suite passes **542 tests in 261.254 seconds**
on its third attempt. Its guarded command takes 265.228 seconds and does not
breach the physical reserve. The two earlier resource interruptions remain
separate failures to complete, without being relabeled as passing runs.
The unchanged inventory regressions include small selectors, floating literals,
exact suffix/spelling preservation, comment/string exclusions and equal-valued
constants from different domains. Full output and exact commands are retained
under validation/tooling-integrated-retry02.

Split-source, pure metadata, save-format, constant/structure/unit-metadata
generators, subsystem headers, TU includes and whitespace checks also pass.
All **802 production/tooling inputs** remain unchanged. The header gate retains
exit 1 and byte-identical output against the incoming reference. The Markdown
checker also retains exit 1 for two absent private historical paths:
`artifacts/cpp-classes/20260913/native-baseline/README.md` referenced by
`docs/CPP_CLASS_NATIVE_BASELINE.md`, and
`artifacts/cpp-classes/20260913/validate-stage.py` referenced by
`docs/CPP_CLASS_ORIGIN_REFRESH.md`. A fresh check using the immutable incoming
checker and all 71 incoming active Markdown blobs produces exactly the same
two-line error output as the candidate under the same path-existence view.
The checker and both implicated documents are unchanged, and neither private
target is tracked in incoming main. The original overall runner failure remains;
separate inherited-header and inherited-markdown comparison receipts establish
unchanged findings without suppressing either gate.

## Integrated native coverage and outcome limits

The integrated native build and canonical headless CTest wrapper pass. The
executed binary reports **1,090 passes, zero assertion failures and 526 isolated
crashes among 1,616 registered cases**. GCC coverage is **6,165 / 6,656 lines
(92.623197%)**, with all **718 selected functions covered and none uncovered**.
There are no gcov profiling diagnostics. The 456 bound inputs and binary hash
remain unchanged throughout execution and completion.

All 1,616 registered identities match the retained class reference at
`33a5959820dfcb70902183d9c094221c547b05fc`. All 524 reference crash identities
remain; `cov2_01_savereservedslot10.basic` and
`cov2_06_rules.show_banner_strategic_clash` change from pass to crash. The entire
718-function coverage JSON is byte-identical to that reference. The compared
revisions, build roots and explicit game-root environments differ; the cause
of these two outcome changes is not established. This is not a paired F7
behavior-regression claim. The earlier `02c00bf` baseline failed compilation
before any case, as recorded above. Incoming-main CI logs contain only the
successful CTest wrapper and coverage totals, not individual case outcomes.

An initial private completion driver used unsupported `--jsonout`; its error
is retained separately. The corrected command uses the public `--json`
argument against the same executed binary and profiles, without rerunning
CTest. Resource-stopped measurement attempts are also retained. Successful
completion stages all derived files in RAM, then verifies the durable copy.
The profile archive contains **6,366 verified members** and has SHA-256
`263ca25731df959d6f22ad08580194be5c23f9ffc17993619334af52e11f79b4`.
The complete added durable evidence is 7,393,137 bytes. See the private
native/integrated-completion-ram-final/summary.json and
native/class-reference-comparison.json records.

After the RAM build directory disappearance described below, an unchanged-binary
repeat restores the sealed binary and 223 hash-verified gcno notes to the original
build path. The original configure command regenerates CTest metadata without
compiling source. `ctest -N -V` verifies the resolved canonical wrapper command
against the first run's log. The missing-directory startup error and an initial
private preflight assertion about `bash` versus `/usr/bin/bash` remain separate;
neither attempt executed native cases.

The restored canonical CTest passes in **2.618 seconds**. All **1,616 case
outcomes exactly reproduce the first integrated run**, including both additional
crashes versus the older class reference. They are stable across these two runs;
their cause remains unproven. The coverage JSON is again byte-identical, and all
456 inputs and the binary hash remain unchanged. The repeat has its own fully
verified 6,366-member archive, SHA-256
`facdfc79e0f1c51d5fb781a66dfa52b634bfb3f402963413f47d9266c24a2a08`.
See native/unchanged-repeat/summary.json. No native source rebuild, test repair,
floor change or replacement of the first run's evidence is involved.

## Resource interruptions and evidence storage

The two integrated full-tooling attempts stopped at the unchanged 5 GiB
physical backing-volume reserve after 167.340 and 171.108 seconds. Neither
interruption is a completed-suite pass or a test assertion failure. All logs,
runners and source bindings remain. The Linux filesystem's much larger free
space is not treated as available host capacity. This task issues no WSL
restart or global core-dump policy change to finish this evidence.

Storage consolidation preserves recoverable evidence. The two original census
JSONs are now lossless `.json.gz` archives, with decompressed byte counts and
SHA-256 values checked before removing the duplicate raw JSONs. Restore them
with `gzip -dk census-before.json.gz census-after.json.gz`. Transparent NTFS
compression preserves paths and bytes for the historical object and compiler
snapshot files and the final immutable binaries/archives; separate receipts
record every hash.

After checking both runtime archive hashes and every selected archive member
and source file, 409 duplicate periodic `frame-N.bmp` files are consolidated
into the existing archives. This dated note supersedes the earlier statements
that every raw periodic frame remains as a loose file. Checkpoint BMPs, logs,
saves, PNG comparison pairs, indexes and both full archives remain. The separate
periodic-frame-consolidation-receipt.json records all exact paths, sizes,
hashes and restore commands. It accounts for 502,629,098 logical bytes and
504,254,464 native allocated bytes. A subsequent `fstrim` of already-free ext4
blocks returns 106,233,856 allocated VHDX bytes in the measured interval;
its reported virtual trim extent is not counted as host storage recovered.
No unrelated files or retained historical reports are removed.

After the final comparisons and native archival completed, the original owned
RAM build directories were observed missing. The cause is not established;
this task did not remove those directories. The durable compiler binaries,
150-member raw archives, all 153 stripped objects per compiler, native binary
and verified profile archive remain. The three raw non-archive debug objects
per compiler and original mission-trace test executable were not copied before
that disappearance and are explicitly unavailable. Publication references use
the sealed stripped objects rather than claiming recovery of the missing raw
bytes. Original passed CTest receipts and completed comparison receipts remain
unchanged.

For the next integration, the publication reference binds the preserved 150 raw
archive members and all 153 stripped objects per compiler, both binaries,
compile commands, source inputs and GNU ar 2.42. The two mission-trace test
executables are separately relinked from the sealed stripped test objects;
both derived executables pass. They are explicitly distinguished from the
missing originals. The bootstrap link recipe is reconstructed from the frozen
object order and observed Ninja flags/libraries; the original generated recipe
was not durably captured. Exact derived link commands and hashes are in the
private publication-reference/provenance.json, SHA-256
`286b968706c26561ed2d9df3090c3bfd59f10afdd71be980aef3a085c6774016`.
