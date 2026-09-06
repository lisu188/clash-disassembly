# Recovered numeric constants: 2026-09-06

Track: Win95 reconstruction, behavior-preserving constant naming across all
140 canonical recovered translation units. Campaign status remains unchanged.
The naming-only batch below is frozen in commit `5e64be0`; the separate main
integration is recorded at the end.

## Change and evidence

The completed batch replaces 1,988 numeric occurrences in 62 TUs: 1,815 exact-spelling
macro substitutions and 173 uses of existing enums. It adds 90 private constants
and their generated compile-time guards. All 4,157 manifest identities, function
signatures and legacy hashes remain unchanged; 395 current body hashes change.
The existing menu-template helper also retains its signature. No public API,
record layout, raw table payload or original assembly changes.

The reviewed families cover stack/garrison/tactical record sizes and bounds,
metadata byte versus DWORD strides, folded game-state field offsets, Road AP and
animation values, palette/DLX geometry, CLIPS atom tables/types/strategies,
deleting-destructor flags and audio time scaling. Names preserve original numeric
spelling, suffixes, casts, access widths, expression grouping and comparisons.

Evidence and exact function/expression-scoped rules are retained in
[F1 gameplay](archive/literal_rules/F1_gameplay_findings.md),
[F2 runtime](archive/literal_rules/F2_runtime_findings.md),
[F3 field offsets](archive/literal_rules/F3_fields_findings.md), and
[F4 Road](archive/literal_rules/F4_road_findings.md), with a separate
[F6 stack-helper supplement](archive/literal_rules/F6_stack_helpers_findings.md).
The constants manifest is
additive; prior entries and historic provenance remain intact.

The [complete census and evidence queue](archive/literal_rules/F5_remaining_findings.md)
account for every canonical TU. Numeric data and arithmetic remain literal where
justified; unresolved fields/selectors remain an evidence queue, not invented
semantic names. The original integer classifier's three remaining candidates
are explicitly rejected: two compensating cheat-address additions and a wall
sprite increment of 404. None is automatically approved by its numeric value.

The census falls from 81,247 to 79,259 numeric code tokens. All 178 floating
literals retain their exact spelling; 227 small integers below ten gain names.
The remaining census contains 5,244 justified data/arithmetic occurrences and
74,015 unresolved entries. Those conservative entries retain locations and
context with domain-specific missing evidence; they are not individually proven
semantic recoveries or a claim that further nameable values cannot exist.

## Tooling

[F0](archive/literal_rules/F0_inventory_notes.md) documents the additive census
interface: small integers, floats, exact suffix/radix context, function locations,
and optional evidence-bearing dispositions. Executable initializer expressions
and lambdas are excluded from automatic raw-data exemptions. Scope resolution now
reads the source inventory once per application and records function identities
in regex plans. The provenance ledger groups site totals once per constant rather
than repeating the aggregate for every scoped rule.

The extracted strategic fixture imports the four newly referenced definitions
from the canonical header; its independent raw input states and expected results
are unchanged. Focused regressions cover the census boundaries and application
scope/ledger accounting.

## Validation

Baseline: `227ae3435b46f96ac0533692bd8dbb1f241271a0`. Commands ran in WSL from
the current worktree, with the Windows Git administration paths translated to
Linux paths. Private local evidence is under `artifacts/magic-numbers-20260906/`
and is absent from clean checkouts.
The reconciled result index is
artifacts/magic-numbers-20260906/final-validation.json.

| Gate | GCC 13 | Clang 18 |
| --- | --- | --- |
| Full recovered object disassembly | identical, 496,474 normalized lines | identical, 426,774 lines |
| Source preprocessing after additive definitions | exactly 173 reviewed enum-token changes | exactly 173 reviewed enum-token changes |
| Linked symbol/data profile | identical | identical |
| Linked `.text`, `.rodata`, `.data` bytes | identical | identical |
| Compile/link and four public asset-free gates | pass | pass |
| Warning ratchet | pass, 6,618 warnings | pass, 6,628 warnings |
| Existing raw link ratchet | unchanged: 427 differences | unchanged: 679 differences |

The header ratchet retains its existing 14 differences; generated subsystem
headers, API catalog and TU include blocks are unchanged. No warning, link,
header or coverage baseline was raised.
The header result was also reproduced from a fresh extraction of the original
commit's source/data/tools; its 14 differences match the final result exactly.
Final raw link and warning-category reports also match their retained baselines.

All 135 tooling tests and generator freshness checks pass. Subsystem usage
catalog regeneration reports no changed TU include blocks. The final F6
supplement passes preprocessing, all 140 object comparisons, incremental builds,
linked profile/data parity and all four public gates under both compilers.

The native wrapper passes with the same 1,059 passes, zero assertion failures
and the same 530 isolated crash cases among 1,589 cases. Final measured coverage is
6,169/6,662 lines (92.60%), covering all 718 frozen functions; the pre-change
measurement was 6,171 lines. These measurements do not turn the retained native
crashes into passing cases.

Both headless first-Road replays passed on their first attempts. Each reaches
turn 6, stack 4 at `(49,50)`, 2 AP, an empty queued path, 228 visible tiles and
roads 867/879. Every decoded unit-slot byte and the full visibility hash agree
between profiles; the visibility hash matches the previously accepted original
checkpoint. Each run retains 20 saves and nonblank presented frames. Exact
commands, private asset-root isolation, before/after states and frame metrics
are in artifacts/magic-numbers-20260906/routes/README.md and
artifacts/magic-numbers-20260906/routes/verification.json.
The replays precede the 13-site F6 supplement. Final linked executable code and
stored data are separately compared byte for byte with both those route-tested
binaries and the original pre-cleanup binaries in each profile's
supplement parity records under
artifacts/magic-numbers-20260906/gcc-13/supplement-parity.json and
artifacts/magic-numbers-20260906/clang-18/supplement-parity.json.
This does not promote mission 05 or claim whole-frame visual equivalence.

An independent reconstruction audit verifies that the original sources plus
the reviewed substitutions reproduce every current canonical TU byte for byte.
It separately checks all signatures, manifest history, 90 constant definitions,
341 untouched aggregate initializer regions and eight palette declaration-bound
edits. See artifacts/magic-numbers-20260906/source-review.json and
artifacts/magic-numbers-20260906/source-review.md.

## Commands and retained attempts

The executable evidence scripts retain the exact commands and output files:

```sh
export GIT_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git/worktrees/clash-disassembly1
export GIT_COMMON_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git
export GIT_WORK_TREE="$PWD"
evidence=artifacts/magic-numbers-20260906

# Executed before source application, then after the reviewed replacement plan.
bash "$evidence/baseline.sh" gcc-13
bash "$evidence/baseline.sh" clang-18
python3 "$evidence/prepare_batch.py"
python3 tools/apply_literal_names.py "$evidence/combined-rules.json" \
  --batch F-all-recovered-20260906 --expect "$evidence/reviewed-plan.json" --apply
python3 tools/gen_constant_guard.py
python3 tools/gen_subsystem_headers.py --write --write-tu-includes all
bash "$evidence/validate.sh" gcc-13
bash "$evidence/validate.sh" clang-18
bash "$evidence/coverage.sh" before-corrected
bash "$evidence/coverage.sh" after
python3 tools/apply_literal_names.py docs/archive/literal_rules/F6_stack_helpers.json \
  --batch F6-stack-helpers --plan "$evidence/F6-reviewed-plan.json"
python3 tools/apply_literal_names.py docs/archive/literal_rules/F6_stack_helpers.json \
  --batch F6-stack-helpers --expect "$evidence/F6-reviewed-plan.json" --apply
python3 tools/gen_subsystem_headers.py --write --write-tu-includes all
bash "$evidence/validate-supplement.sh" gcc-13
bash "$evidence/validate-supplement.sh" clang-18
bash "$evidence/coverage.sh" supplement
bash "$evidence/final-ratchets.sh"
python3 -m unittest discover -s tests/tools -p 'test_*.py'
bash "$evidence/static_checks.sh" final
python3 tests/check_markdown_links.py
python3 tools/literal_inventory.py --census-sites \
  --dispositions docs/archive/literal_rules/F5_remaining_dispositions.json
python3 "$evidence/final_evidence.py"
```

These are a chronological record, not a command to reapply the frozen plan to
already edited sources. The definitions-only preprocessing snapshots separate
the reviewed additive guards from substitutions; the original object and linked
byte baselines cover the entire change.

Retained failed attempts include the initial coverage build-directory rejection
(corrected using the wrapper's supported path shape), strategic fixture missing
definitions in eight compiler profiles (corrected without changing its oracle),
and the initial duplicated ledger append. Git-dependent checks require the
translated environment above; an initial Markdown check and F6 dry plan omitted
it. The F6 application used it and verified the same reviewed sites. Whitespace
validation uses `git -c core.whitespace=cr-at-eol diff --check` to preserve the
constants manifest's pre-existing CRLF format instead of rewriting historical
lines. The historical ledger prefix is
byte-identical; the new batch's corrected aggregate has 125 rows totaling exactly
1,975 sites, followed by two F6 rows totaling 13 sites. Earlier invalid attempts
and reviews remain in the evidence directory.

## Main integration

Integrated cleanup commit `5e64be0425f3578c6c109fbb4db6a922e657a286` with main
revision `bf152559fa07368e011e6feabd38dc6533c188ea`. Main had independently
refactored eight Road helpers in the buildings TU. Those eight bodies and their
trailing diagnostic-comment removal are retained exactly from main. The other
139 canonical TUs and the remaining 27 bodies in that buildings TU retain the
cleanup version. Three cleanup stride substitutions are superseded by main's
already-named or typed expressions. Both documentation histories are retained.

The merge review checks all 4,157 current body hashes and historical identities,
and private/public headers remain identical to the validated cleanup. Its
local report is artifacts/magic-numbers-20260906/merge-review.json. The separate
inventory at artifacts/magic-numbers-20260906/census-merge.json contains 79,241
numeric tokens; the frozen naming-batch census and evidence remain unchanged.

WSL stopped responding during integration, including process launches and
distribution status queries. The conflict resolution and independent source
composition review ran through Windows Python and Git. Fresh merged Linux
builds, object comparisons and runtime replays were not run. The successful
Linux gates above belong to the frozen cleanup batch, and main's separate
Road-helper validation remains recorded in [HUMAN_READABILITY.md](HUMAN_READABILITY.md).
No claim of a fresh merged executable or runtime validation follows from the
source review, and no ratchet or campaign status is changed.
