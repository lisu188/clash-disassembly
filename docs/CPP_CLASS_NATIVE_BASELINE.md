# Resumed native baseline at be837d1

This is the frozen migration reference at
`be837d13515b351057d5dad7633d7f2462d3bb62`: 13 class methods, 145 recovered TUs and
4,157 identities. Later regroup, published-main DLX integration and unit class
batches are outside its scope. The source archive pins all 885 Git files; both
post-run hash checks pass. Both stock Debug coverage builds pass with GCC 13.3
and Clang 18.1.3. This is a measured baseline with failures, not final acceptance.

| Native observation | Pass | Assertion/error | Crash | Total | Exit |
| --- | ---: | ---: | ---: | ---: | ---: |
| GCC default | 1,090 | 0 | 524 | 1,614 | 0 |
| GCC strict | 1,090 | 0 | 524 | 1,614 | 1 |
| Clang default | 1,086 | 1 | 527 | 1,614 | 1 |
| Clang strict | 1,090 | 1 | 523 | 1,614 | 1 |

Every actual registered case is reconciled with its raw outcome. Default exit
zero does not erase crashes. Clang's assertion is
`cov5_01_getallowedattrtoken.allowed_symbols`; four cases vary between its two
runs and remain separately recorded. GCC changes three earlier crash outcomes
to pass. Only `cov2_06_unit.calc_military_strength_nonzero_squad` has a matching
integrated register repair; saved-slot and banner changes have no proven cause.

Coverage uses the actual frozen manifest-aware tool and default worker shards
with unchanged `--minimum 89.7 --require-functions 718 --require-zero-uncovered`.

| Coverage profile | Covered / executable | Percentage | Zero-covered | Gate |
| --- | ---: | ---: | ---: | --- |
| GCC / gcov 13 | 6,161 / 6,652 | 92.618761% | 0 | PASS |
| Clang / LLVM gcov 18 | 6,799 / 7,341 | 92.616810% | 8 | FAIL |

GCC's entire per-function inventory matches the earlier e13 class checkpoint:
zero executable-line and covered-line change. The Clang inventory differs from
GCC by +689 executable/+638 covered lines; that is a compiler comparison, not a
migration source delta. The earlier report did not contain a Clang percentage.
The eight zero-covered procedural functions are
`Rules_ExpressionConstraintsCompatible`, `Method_PrintWatchStatusLine`,
`Rules_WriteConstructHeaderToCode`, `Parser_CollectFunctionArguments`,
`Rules_ParseDefruleRHS`, `Rules_ApplyPatternKeywordFlags`,
`Class_ClassSuperclassesCommand` and `Class_ClassSubclassesCommand`.
No zero-covered result is waived or combined with strict shards to pass.

The initial GCC attempt writing coverage directly on the Windows filesystem
timed out before complete totals; its partial 46.33%/334-zero result is retained.
The complete runs use the unchanged 16-worker runner and one-second case watchdog
with monitored RAM-backed worker profiles, copied and hash-verified into durable
workspace archives before removal. Private empty game roots and dummy SDL
drivers keep retail assets and saves untouched. No compiler launcher was needed.

Stock GCC gcov cannot read Clang's `408*` format. Its failure remains. A private
copy of matching Ubuntu LLVM 18.1.3 supplies `llvm-cov gcov`; all 192 original
reader argument lists are preserved unchanged. No system package was installed.
Clang strict additionally reports 220 parent-path profiler mapping I/O errors;
the independently archived worker shards do not establish successful parent
profile flushing. These limitations are recorded without a filesystem diagnosis.

The durable local report and exact commands are in
`artifacts/cpp-classes/20260913/native-baseline/README.md`. Authoritative completed
results are `gcc13/complete/` and `clang18/complete/`, with actual registrations,
per-case comparisons, full coverage JSON, separate default/strict profile
archives and verified binaries. The evidence-freeze.json receipt seals 330 output files;
the source and build artifacts remain separately pinned. No presented frames or
campaign progress are established by these asset-free native tests.
