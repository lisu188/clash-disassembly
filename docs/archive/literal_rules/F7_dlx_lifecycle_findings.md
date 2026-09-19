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

A read-only WSL prospective resolution against the frozen source passed with
the four proposed definitions supplied only in memory: 23 rules, 23 sites,
seven functions, no rejected sites and no respellings. Counts were header 6,
payload field 8, size field 6 and ownership field 3. This checked
`apply_literal_names.validate_rules` and `resolve`; it did not apply a plan or
write source, generated files or provenance. The check used this worktree's
translated `GIT_DIR`, `GIT_COMMON_DIR` and `GIT_WORK_TREE`, with
`PYTHONDONTWRITEBYTECODE=1`.
