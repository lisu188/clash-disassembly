# GNU++20 migration

Track: Win95 reconstruction. The staged migration is complete: the maintained
runtime and native test harness use GNU++20. All 4,157 recovered identities
remain in 140 independently compiled translation units across the same 12
subsystems. The SDL seam, packed layouts, low32 storage model, address order,
and historical source/hash provenance remain intact. Campaign-route status is
independent of this work.

The subsequent 2026-09-06 radix-formatter, fog-classifier, reveal-propagation,
nation-score, manual-crossing and builder-Road recoveries are
recorded in [STATUS.md](STATUS.md). They restore original behavior after the
cutover; validation below remains the historical language-migration gate.

## Completed stages

1. Declaration/tooling foundation, validated in C against the frozen reference.
2. Support and recovered-family C++ pilot.
3. Core, render, units, and world.
4. Buildings, battle, persistence, and strategic.
5. CLIPS, media, and runtime.
6. Shared-state storage, all 62 native unit sources, and the C++-only cutover.

Each stage retains compiler, identity, boundary-probe, and runtime evidence.
The foundation's 199 reserved-identifier replacements change `this` to `this_`
in 93 bodies. Later stages make pointer and enum conversions, argument
promotions, callbacks, C linkage, and packed access alignment explicit.
No recovered function identities or native test registrations were removed.

## Final build contract

CMake enables only CXX. Every recovered source, support source, native test
runner, and case is a `.cpp` translation unit. GCC 13 uses `CXX=g++-13`;
Clang 18 uses `CXX=clang++-18`. Use fresh build directories when changing
compilers or migrating an old mixed-language build. No maintained C runtime
target or alternate C build configuration remains.

GNU extensions remain enabled; exceptions and RTTI are disabled.
`-U_GNU_SOURCE` retains the frozen C reference's libc feature profile.
Support and test sources retain warnings as errors; recovered-code warning
ratchets remain unchanged. There is no permissive C++ compilation.

The declaration, source-index, and preprocessing tools still understand
historical `.c` snapshots. C fixtures check that compatibility and exported C
linkage; they do not introduce a C runtime target. Generated interfaces retain
11,965 shared declaration exposures and 241 shared globals. State storage
retains the original bytes, including nonterminated strings and one-element
tentative arrays, with no added dynamic initialization.

## Evidence-backed repairs

Conversion exposed malformed recovered boundaries. Original assembly and
caller evidence support repairs to castle/army argument passing, replay reads,
CLIPS string/parser/router arguments, and runtime prefix checks. The pool
unlink path now frees the removed pool, as the original EAX value requires;
it previously freed a linked neighbor and could corrupt the renderer. The
actual-function allocator regression covers head, middle, tail, and sole pool
behavior on both compilers.

These repairs deliberately differ from erroneous frozen C behavior. Their
assembly locations, before/after hashes, rejected alternatives, and focused
probes are recorded separately from mechanical parity results. Packed army
fact helpers use alignment-one 16/32-bit views without changing offsets or
strides. Their complete objects match the preceding implementation on both
compilers, and all 256 typed-entry alignment cases pass.

Raw recovered names are pinned where C++ would otherwise rename local
functions or storage. All 140 final object pairs have complete storage
accounting against frozen C on both compilers. All 5,321 non-private objects
retain names, sizes, offsets, alignment, initializers, relocations, and relative
order. Three bounded private-order differences remain on GCC and none on Clang.
Linked profiles also retain two previously reviewed support-storage moves and
four explicit render-hook adapters. This is not a claim of whole-program
instruction identity or original-executable equivalence.

## Final validation and limits

Fresh GCC 13 and Clang 18 builds compile/link and pass all four asset-free gates
each. All 81 tooling tests and metadata/generator checks pass. Unchanged
warning ratchets pass with 6,637 GCC and 6,648 Clang warnings.
Coverage passes the unchanged 89.7% floor at 6,157/6,661 lines (92.43%) over all
718 frozen functions, with none uncovered. All 1,588 native cases remain:
1,056 pass, zero assertions fail, and 532 isolated cases crash. The CTest
wrapper tolerates isolated crashes; its pass is not a crash-free result.
Two existing CRT thread cases exchange crash status versus frozen C;
matched-harness and debugger evidence retains the existing formatter/ASLR debt.

The default runtime suite retains the first-mission playability and attack
failures at `next_unit_selected selected=1 a=31 b=44`. An initial final run also
missed the menu Exit input; all three isolated repeats pass on both C and C++.
The full repeat reports 11 passes, those two failures, and eight skips. The
failed first run remains recorded. The header ratchet retains nine differences.
The raw link ratchet remains failing: GCC has 341 differences versus frozen C's
205, and Clang has 593 versus 111. The increase accounts for reviewed private
support names and four adapters; separate full profiles prove no lost recovered
symbols or data and enumerate every remaining storage-order difference.
Both raw archives pass all 4,157 identity checks. No warning, header, link, or
coverage baseline was raised to pass the migration.

Fresh headless C and final C++ settled-menu frames are pixel-identical. The
fresh original Wine frame retains palette and cursor differences: mean
absolute RGB difference 1.560641276/255, with 290,923/307,200 pixels differing.
Full frames are compared without masking, cropping, or palette correction.
Both show the English menu, CLASH title, shield, and six matching buttons;
the reconstruction also passes authentic Exit input and the nonblank check.
No broader visual, route, or campaign milestone advances.

Original equivalence remains unproven. Unrecovered native/import contracts,
other CRT formatting and timezone storage, uninitialized decompiler values,
`CSS_Init`, campaign-menu entry, and automatic advancement remain separate
recovery work. Existing native callback behavior is preserved where original
register/context mapping is uncertain; no missing provider is invented.

## Reproduction and retained evidence

The frozen C source commit is `d6cdb39d153d230494c70e345c4781b97e0dfca9`.
Public commands are in [BUILD_AND_TEST.md](BUILD_AND_TEST.md); unit semantics
are in [UNIT_TESTING.md](UNIT_TESTING.md). Exact local commands, source
snapshots, compiler logs, comparisons, integration ledgers, and frames are
under `artifacts/cpp-migration/20260905-a/`. That private evidence directory
is absent from clean checkouts; public CI has no retail-asset requirement.

The final record is artifacts/cpp-migration/20260905-a/final-validation.md.
Commands include `build_pilot.sh gcc13 final2` and the Clang equivalent,
artifacts/cpp-migration/20260905-a/check_final2.sh,
artifacts/cpp-migration/20260905-a/final2_metadata_checks.py,
artifacts/cpp-migration/20260905-a/check_final2_warnings.py,
`audit_stage4_storage.py --stage final2`, and
`compare_stage4_storage_link.py --stage final2`. Fresh frame commands are in
artifacts/cpp-migration/20260905-a/support/capture_final_original.sh and
artifacts/cpp-migration/20260905-a/capture_final2_menu.sh; metrics and
the side-by-side image are artifacts/cpp-migration/20260905-a/final2-frame-metrics.json and
`final2-original-vs-cpp.png`. The Linux-native validation path is recorded in
`native-workspace.txt`; installed executable and save bytes remain unchanged.
Earlier candidate READMEs describe pre-integration snapshots; final integration
ledgers and this record define the completed cutover.
