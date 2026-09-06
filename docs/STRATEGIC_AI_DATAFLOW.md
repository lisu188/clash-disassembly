# Strategic AI dataflow and matcher completeness

Evidence reviewed on 2026-09-05 against baseline `d6cdb39d153d230494c70e345c4781b97e0dfca9`.

## Strategic target priority: reconnect the actual return value

The canonical implementation is in [strategic_004.cpp](../src/strategic/004589C0_004602F0_strategic_004.cpp). The independent instruction evidence is in [clash95.asm](../clash95.asm), procedure `sub_4592E0`, label `loc_459517`.

The retail instruction sequence calls `sub_459230` to produce the priority in the x87 stack, calls `__CHP`, stores a signed 32-bit integer with `fistp`, reloads that integer with `fild`, compares against the previous best, and writes a float when strictly greater. The original `jbe loc_459443` preserves the existing candidate on a tie.

The previous recovered C discarded `AI_CalcStrategicPriorityScore`'s return and instead consumed `_CHP(v16, filter_type)`, including an uninitialized local. The recovery now connects the producer to the integer conversion:

```cpp
score = (double)(int)AI_CalcStrategicPriorityScore(target_type, tile_x, origin_x, tile_y, origin_y);
```

This deliberately preserves truncation rather than comparing fractional priorities directly. It does not globally redefine `_CHP`, modify filtering, change argument order, or alter the ring scan. The uninitialized local and its obsolete decompiler warning were removed.

The numeric recovery and fixtures cover finite priorities whose truncated result is representable as a 32-bit signed integer. They do not emulate or certify x87 exception behavior for NaN, infinity, out-of-range conversion, or all possible extended-precision boundary cases. The file-backed weight reader and full search/host-call coordinate ABI still need independent retail execution fixtures.

## Regrouping: preserve the retail partial ordering

An initial source-only review identified that the regrouping loop does not generally sort its records. Assembly inspection changes the interpretation: the retail instruction listing contains the same repeated-pair loop.

In `sub_4589C0`, `loc_459138` initializes the compared positions from the outer-loop state. At `loc_4591F1`, only `ebp`, the inner counter, advances before returning to `loc_45916B`. The compared record index and byte offset do not advance there. `loc_459104` advances them between outer iterations, while the existing early-exit flag can stop further processing.

Consequently, replacing this with a complete sort would change retail gameplay behavior. The recovered implementation retains the original partial ordering and early exit. Examples locked into regression tests are:

| Input offset-9 values | Retail-loop result |
| --- | --- |
| `9, 1, 8, 2` | `1, 8, 2, 9` |
| `1, 2, 0` | `1, 2, 0` |

There was a separate signedness mismatch worth correcting. The original byte comparison branches with signed `jle` at `loc_45916B`; the threshold scan sign-extends the byte before comparing it with eight. Both recovered comparisons now explicitly use `signed char`, independent of the compiler's default plain-char signedness.

The tests preserve each complete 31-byte record, cover negative keys, ties, empty and single-record inputs, and exercise the maximum combined count of 22 with an army limit of ten. They extract the ordering/count block from production source. They do not claim that the entire approach-path, regrouping, and writeback function has been behaviorally validated.

Only the two changed canonical function body hashes were updated in [recovered_sources.json](../data/recovered_sources.json). Original assembly and legacy evidence remain unchanged.

## Typed unresolved matcher inventory

[check_clash_dat_unresolved.py](../tools/check_clash_dat_unresolved.py) emits schema version 2. Existing aggregate keys remain, and parenthesized expressions no longer receive an empty primitive-family name.

Each unresolved occurrence now retains the exact expression root, rule/disjunct identity, condition ordinal, join index, depth, alpha-versus-join phase, and negation flag. Descendant expression records include type IDs, value/argument/sibling indices, function names where applicable, and decoded primitive payloads with bitmap identity and raw bytes.

Expression roots are recorded by [clash_dat_lhs.py](../tools/clash_dat_lhs.py) during recovery, not inferred by matching printed strings. The traversal follows the root's arguments but does not mistake the root's next sibling for part of the test. Invalid indices and cycles fail explicitly. Repeated shared nodes are counted once per unresolved test occurrence.

The `by_nested_primitive` and `by_primitive_payload` summaries show contained primitives, not isolated causes of translation failure. A resolved primitive can occur inside an unresolved compound expression. The existing reason field still represents the translator's reported reason, not an exhaustive diagnosis of every descendant.

The validation snapshot for the unchanged retail image is:

| Measure | Count |
| --- | ---: |
| Rule/disjunct records | 95 |
| Compiled matcher test occurrences | 753 |
| Translated occurrences | 420 |
| Unresolved occurrences | 333 |
| Rules with all matcher tests translated | 13 |
| Unresolved occurrences in negated conditions | 198 |

No new binding semantics are guessed by this change; the 333 unresolved occurrences remain unresolved. The inventory now exposes their provenance and repeated payloads for subsequent recovery.

## Strict matcher-completeness gate

The default output from [generate_clash_recovered_constraints.py](../tools/generate_clash_recovered_constraints.py) remains a readable source projection. Its header and manifest explicitly distinguish matcher completeness from behavioral equivalence.

Use the opt-in gate when a downstream operation requires all compiled matcher predicates to have source forms:

```sh
python3 tools/generate_clash_recovered_constraints.py CLASH.DAT --clp /tmp/CLASH_recovered.clp --manifest /tmp/CLASH_recovered_manifest.json --require-complete-matchers
```

With the current retail image this exits with status 2 because 333 tests are unresolved. Neither output is created or overwritten on that refusal. Existing files are left untouched, so callers must honor the failure status rather than reusing stale output.

The gate checks both positive and negated conditions. Dropping a positive predicate can add activations, while dropping a predicate inside `not` can suppress activations. Comment-only evidence is not an executable approximation with a single predictable direction of error.

The manifest includes `matcher_complete`, `fully_translated_rule_count`, `unresolved_negated_test_count`, and `behavioral_equivalence_verified`. The last value remains `false`: even complete matcher translation would not establish RHS, native-host, agenda, or engine-version equivalence.

## Regression commands and evidence limits

[The strategic regression module](../tests/tools/test_strategic_insights.py) adds 13 tests. Its native fixture extracts the actual production evaluator and regrouping block rather than keeping a separately rewritten implementation. A controlled score provider checks dataflow and asymmetric coordinates. It covers target ranking, integer boundaries, negative and zero scores, ties, wildcard filters, owner/type rejection, map bounds, and treasure/religious-site targets.

The native fixture extracts the canonical `.cpp` source and compiles as GNU++20, with the runtime's libc feature profile, exceptions and RTTI settings. It runs at `-O0` and `-O2` with both signed and unsigned plain-char defaults on each available GCC and Clang C++ compiler (preferring `g++-13` and `clang++-18`). Undefined-behavior and float-cast-overflow sanitizers are enabled and trap on any detected error, without requiring a separate sanitizer runtime. Only the existing recovered-code parentheses style warning is disabled; other enabled warnings remain errors. Native compilation requires a Linux host with a C++ compiler and is explicitly skipped otherwise.

```sh
python3 -m unittest discover -s tests/tools -p 'test_strategic_insights.py' -v
python3 -m unittest discover -s tests/tools -p 'test_*.py' -v
python3 tools/audit_split_sources.py
python3 tools/check_clash_recovered_clp.py
python3 tools/check_clash_dat_unresolved.py --json /tmp/strategic-matcher-inventory.json
```

The original C implementation validation passed all 58 tooling tests, including the 13 new tests and all four native configurations, plus the split-source audit and recovered-source contract.

The 2026-09-06 GNU++20 integration repeat passes all 13 focused tests and all eight native configurations across GCC 13 and Clang 18. The production evaluator and regrouping block remain extracted without rewriting their bodies, and every prior assertion remains. The final focused log is retained at `artifacts/integration/merge-main-20260906/strategic-insights-cpp-final.log`. The initial log in the same directory, `strategic-insights-cpp.log`, retains Clang's missing sanitizer-runtime link failure; the final fixture uses the same trap-on-error sanitizer policy as the other C++ recovery fixtures.

This is not a completed retail-executable/native-runtime/generated-CLP differential oracle. That next stage needs independent traces of input facts, activations, native call arguments, return values, and state changes. Successful source loading, complete record conservation, and matcher translation percentages must not be reported as percentages of gameplay correctness.
