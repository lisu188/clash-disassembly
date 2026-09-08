# F0: complete numeric census and review dispositions

Track: Win95 reconstruction, behavior-preserving constant naming. This tool
change does not advance a campaign route or establish semantic recovery.

`tools/literal_inventory.py` retains its historical `constants`,
`derived_candidates` and `unmapped_frequent` fields and integer eligibility
rules. A new `census` object accounts for each code numeric token once, including
small integers, floats and values which collide across constant domains.
`--census-sites` includes every census site; `--full` includes both legacy and
census sites. Both options leave raw source files untouched.

Each site records canonical file, one-based line and column, balanced enclosing
function (or null), raw lexeme, lexical numeric kind, suffix, radix-aware integer
value or exact float significand/exponent text, type context, nearby expression,
classification, reason and eligible constant candidates. Integer type is not
inferred from suffix alone: C++ also considers radix and value. Float values are
not rounded through Python binary floats. Array extents remain visible.

Comments, ordinary/raw strings, character literals and preprocessor directives
(including continuations) are excluded. The census recognizes decimal and hex
floats, decimal/hex/octal/binary integers, suffixes and C++ digit separators.
Unknown numeric spellings are retained as `unrecognized_number`, never dropped.

## Classification and limits

- `replaceable`: exactly one existing manifest constant passes the historical
  expression/family eligibility filter. This remains a **candidate**, not a
  reviewed semantic authorization. The known `wallSpriteChar += 404` collision
  with `UNIT_STACK_PATH_BYTES` illustrates why every application still needs its
  function/expression-scoped reviewed rule and independent evidence.
- `legitimate`: literal-only file-scope array initializer payload, or a narrowly proven simple
  `for` induction origin/unit step. The latter requires the same bare variable
  initialized to integer zero, compared with one integer literal/identifier bound,
  and incremented/decremented by one in the same header. Bounds remain unresolved.
  Explicit evidence-bearing review rules may justify additional data/arithmetic.
  Array initializer calls, arithmetic expressions, macros, casts and lambda
  bodies remain unresolved. Subscript assignments are not array declarators.
- `unresolved`: the remaining evidence queue. This default means the census has
  not established a disposition; it is **not** evidence that a value is inherently
  ambiguous. Small selectors, zero/one returns or setter arguments, standalone
  initialization, unary signed literals and other gameplay values are not blanket
  exempt. Multiple eligible names are also unresolved pending domain review.

The census does not infer field ownership, replace public types, create enums,
evaluate C++ expressions or approve new semantic constant names. Exact raw tokens
and function/context boundaries support the existing reviewed-plan mechanism.

## Optional checked-in dispositions

Pass `--dispositions PATH` to load a versioned JSON review file:

```json
{
  "schema_version": 1,
  "rules": [
    {
      "id": "example-selector-deferred",
      "classification": "unresolved",
      "match": {
        "file": "src/world/example.cpp",
        "fn": "ExampleFunction",
        "raw": "2",
        "context": "comparison"
      },
      "reason": "Selector domain requires an independent writer/read-site trace.",
      "evidence": ["path/to/review:line or original assembly label"],
      "expected_count": 1
    }
  ]
}
```

Rules accept only `legitimate` or `unresolved`; they cannot authorize replacement.
`match.file` is required and accepts a case-sensitive canonical-path glob.
Optional exact matches are `fn`, `raw`, `kind`, `context`, `line` and `column`;
`fn_regex` and `expr_regex` match the function or displayed source line. Rule IDs
must be unique; reason and a nonempty evidence list are required. Overlapping
rules fail, as do unknown match keys. Optional `expected_count` detects stale
rules after the complete source census; all rule match counts are reported.
The example above documents the schema and is not a production review finding.

## Validation and initial counts

Before the F1/F2 source changes, commit
`227ae3435b46f96ac0533692bd8dbb1f241271a0` yielded 81,247 code numeric sites in all
140 canonical translation units: 81,069 integers and 178 floats; 51,163 integer
sites have values below 10. With no review file: 42 legacy-eligible candidates,
5,241 legitimate sites (5,060 literal-only array payloads and 181 simple loop
arithmetic sites), and 75,964 unresolved sites. The array count was recomputed
against `artifacts/magic-numbers-20260906/production-before.tar` after independent
review rejected expression/lambda initializers. These are input counts, not
final campaign results.

The 13 focused tests pass. They cover small selectors, typed float/integer raw
spelling and suffixes, numeric domains with equal values, safe loop accounting,
comments/strings/directives, table boundaries after functions, scoped evidence
rules, stale/overlapping rules, deterministic counts, expression/lambda initializer
rejection, signed literal payloads and legacy CLI fields.
Run from this worktree's WSL root:

```sh
python3 -m unittest discover -s tests/tools -p test_literal_inventory.py -v
GIT_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git/worktrees/clash-disassembly1 \
GIT_COMMON_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git \
GIT_WORK_TREE=/mnt/c/Users/andrz/.codex/worktrees/62e9/clash-disassembly \
python3 tools/literal_inventory.py --census-sites > /tmp/clash-literal-census-inventory-agent.json
```

The temporary census was an implementation check. The coordinating batch owns
durable before/after snapshots and the final validation record under `artifacts/`.
