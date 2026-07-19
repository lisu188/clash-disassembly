# Magic-Number Batch Runbook

How to run one batch of the magic-number naming campaign (replacing raw numeric
literals in the recovered C with named constants) so that the change is provably
value-identical.

Every command below was executed end-to-end during the W5 smoke batch
(commit `0b9d11a`); the timings are measured, not estimated. Background on the
campaign's rules is in `REVERSE_ENGINEERING.md` §3.5; the narrative ledger is
`archive/REVERSE_ENGINEERING_RENAME_LOG.md`.

## 0. Environment

**Pin one Python interpreter for the whole campaign: WSL `python3`.** Run every
tool as:

```
wsl -e bash -lc 'cd /mnt/c/Users/andrz/git/<worktree> && python3 tools/...'
```

`tools/apply_literal_names.py` reads and writes source in text mode with no
`newline=""`, so each touched file's line endings flip to the host's
`os.linesep` — Windows `python` gives CRLF, WSL `python3` gives LF. Mixing the
two churns files pointlessly. Within one interpreter the byte offsets stay
internally consistent, so there is no corruption either way.

**The line-ending flip is invisible to git.** Measured on W5: WSL `python3`
rewrote two CRLF files to pure LF, and `git diff --numstat` still reported only
`1 1` and `2 2` — the real content changes. `core.autocrlf=true` normalizes on
commit, and git re-normalizes to CRLF on the next checkout.

**Use `git diff --numstat`, never `git status`.** Because C sources and headers are
unpinned in `.gitattributes` while many generated headers are stored LF, `git
status` reports dozens of files as modified when almost none have content
changes. Measured: 32 porcelain entries, 2 real content diffs.

**git does not work from WSL in a worktree.** A linked worktree's `.git` file
holds an absolute Windows path (`gitdir: C:/...`), which WSL git cannot resolve.
Consequences: run all git from Windows git-bash, and note that the tools'
internal `git_head()` returns `"unknown"`, so the commit hash must be written
into the batch log by hand.

Gates need WSL: `gcc` 13.3.0, `objdump` 2.42, `python3` 3.12. The object gate
compiles into a `mktemp -d` and needs no `build/` tree.

## 1. Preconditions

```
git diff --numstat                                  # confirm a clean surface
python3 tools/literal_common.py --selftest          # expect 19/19 passed
```

## 2. Census

```
python3 tools/literal_inventory.py > /tmp/mn/inv.json          # ~4s over 140 files
python3 tools/literal_inventory.py --unmapped 60
```

> **Do not size a batch from `derived_candidates[].count`.** That field is
> incremented once per matching (offset, stride) window, not once per site, so a
> family with three strides inflates every site threefold. Count sites with a
> direct grep instead.

## 3. Mint (only when a batch introduces new constants)

A mint is a **separate commit with a different gate** from the substitution that
uses it.

1. Add `#define NAME <dominant call-site lexeme>` to `src/recovered_types.h`.
   The body must be a **single numeric token** — `tools/apply_literal_names.py`
   rejects composites like `(BASE + 2)`, and `apply_plan` can only write a bare
   identifier, never an expression.
2. Add the matching entry to `tools/constants_manifest.json`. `tier` must be a
   key of `literal_common.TIER_CLASSES` (currently 1 and 3 only).
3. Regenerate and verify the guard, then gate:

```
python3 tools/gen_constant_guard.py
python3 tools/gen_constant_guard.py --check
bash tools/obj_diff_gate.sh /tmp/mn/before.asm      # MUST be 0 diff, full corpus
```

**The mint is gated by `obj_diff`, not by the token gate.**
The guard generator emits one `_Static_assert` per numeric `#define` into
`src/recovered_layout.h`, which every TU includes, so a mint *does* add tokens to
the compared stream and the strict pp gate would fail by construction. The
asserts emit no code, so the object gate is 0-diff and is the real proof. Record
the expected token delta (N asserts, nothing else) in the batch log.

Then **re-snapshot the pp baseline from the mint commit** — every later batch in
the wave compares against that new baseline.

Adding manifest entries alone (no new `#define`) touches no compiled output and
needs no gate — but do verify it did not perturb existing gating, by diffing
`literal_inventory`'s per-constant `eligible` counts before and after. Adding an
entry to an *existing* family enlarges that family's name set and can silently
change tier-3 co-occurrence eligibility for constants already in the campaign;
using a fresh family name avoids this.

## 4. Baseline snapshots

Take these from the tree state you are about to change, after every generated
artifact is regenerated.

```
bash tools/pp_token_gate.sh  --snapshot /tmp/mn/before.i     #  2.6s / 170833 lines
bash tools/obj_diff_gate.sh  --snapshot /tmp/mn/before.asm   # 73s / 487249 lines
```

Snapshot mode is the concurrency-safe workflow — it is the only correct choice
when another session is committing to the same repo. **Never use the positional
git-ref form concurrently**: it runs `git worktree add` into the shared repo.

Both gates accept `--manifest <subset.json>` to scope to a subset of TUs
(schema: `{"functions":[{"source":"src/..."}]}`; omit `source_file_count` or set
it exactly). Use an **absolute** path for an uncommitted subset. Scoping the obj
gate is the biggest throughput lever — full corpus is ~40-73s, scoped is
~0.55s/TU.

## 5. Plan, review, apply

```
python3 tools/apply_literal_names.py <rules>.json --plan /tmp/mn/<ID>_reviewed.json --batch <ID>
```

The rules path must be `argv[1]`; there is no argparse and unknown flags are
silently ignored.

**Review `entries[]` and `rejected[]` before applying.** A high reject ratio is
normal and healthy (A1-4 rejected 1167 to accept 257). Read the actual code at
every accepted site — the gates prove *value*, never *meaning*, and this review
is the only thing standing between the campaign and a mislabel. Keep rule count
per batch low (≤15): `rule_files()` re-parses the 3.1 MB source manifest once per
candidate site per rule, uncached.

```
LITERAL_RENAME_ACCUM=/tmp/mn/<ID>_accum.jsonl \
python3 tools/apply_literal_names.py <rules>.json \
        --plan /tmp/mn/<ID>_applied.json \
        --expect /tmp/mn/<ID>_reviewed.json \
        --batch <ID> --apply
```

`--expect` recomputes the plan and refuses on drift; `apply_plan` aborts with
`STALE PLAN` if any byte moved. Together they make concurrent interference a
detected failure rather than a silent one — if another session commits mid-batch,
**abort and re-plan; never reconcile by hand.** The `LITERAL_RENAME_ACCUM` shard
keeps the append-only ledger from tearing; concatenate it at commit time.

`--apply` also refreshes `data/recovered_sources.json` body hashes in place. That
file is a whole-document read-modify-write through a fixed temp path, so
**only one agent may ever run `--apply` at a time.**

## 6. Gates

```
bash tools/pp_token_gate.sh /tmp/mn/before.i              # expect hunks: 0
python3 tools/gen_constant_guard.py --check              # expect PASS
bash tools/obj_diff_gate.sh /tmp/mn/before.asm           # expect ok: true  (41s)
python3 tools/update_split_manifest_hashes.py            # verifier, no --update
python3 tools/audit_split_sources.py
```

W5 results: `{"ok": true, "tokens": 1282944, "hunks": 0}` and
`{"ok": true, "normalized_lines": 487249}`.

A correctly-spelled substitution is token-identical, so **`hunks: 0` with no
`--allow` is the expected result.** Reaching for `--allow` is a smell: it means
the macro body does not match the call-site lexeme. Legitimate uses are declared
respellings only (a suffix drop such as `0x194u` → `0x194`, or a hex/decimal
change), and every hunk must be declared in the plan artifact.

`kind: enum` rules are the exception — an enum member is not a macro, so the
token stream genuinely changes and `obj_diff` is the only available proof.

## 7. Build and ratchet

```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target clash95_recovered clash95_bootstrap -j4 > /tmp/mn/compiler.log 2>&1
python3 tools/check_recovered_warnings.py /tmp/mn/compiler.log --compiler gcc
```

Every category must be `delta +0`.

## 8. Record

Per `AGENTS.md` §11, each batch records: track and frontier; evidence and
confidence per name; the exact validation commands and their output; durable
evidence paths; and an explicit **Deferred / Ambiguous** section — rejected and
uncertain candidates, not only confirmations.

- rules → a new per-batch JSON file under `archive/literal_rules/`, named for
  the batch id and family
- narrative → `archive/REVERSE_ENGINEERING_RENAME_LOG.md`
- provenance → concatenate the accum shard into
  `archive/win95_constants_rename_accum.jsonl`
- the commit hash, by hand (see §0)

## Known traps

- **Mint before plan.** `validate_rules` returns before `resolve()` if a name is
  missing from either the manifest or the types header, so a plan cannot be
  generated against an unminted constant.
- **Batch order matters.** Once a family member is substituted, its macro name
  itself satisfies tier-3 co-occurrence for later sites. A1-5 only succeeded
  because it matched names placed by A1-1. Split families: tier-1/anchored
  first, tier-3 co-occurrence harvest second.
- **Archived rule files are historical records, not replayable inputs.** Every
  rule carrying a `files:[...]` glob names pre-split paths (`src/game/*`,
  `src/rules/*`) that no longer exist, and resolves to zero sites today. Only
  rules with no `files` key still apply.
- **A value that also appears as a coordinate or bound needs an anchor.** B5
  named `0x1DF` `SCREEN_MAX_Y` from a bare-value rule; 4 battlefield sites used
  479 as an X extent. Right value, wrong axis — it passed every mechanical gate
  and was caught only by adversarial review. Anchor regex rules to a sibling
  token, a variable-name shape, or a callee.
- **Low offsets that coincide with a common record header** (row@0, col@1,
  owner@2) are inherently unreliable for shape-only matching. The
  BUILDING_PRISONER family was investigated and dropped for exactly this.
- **A delta ≥ the record stride is a record address, not a field.** In the
  PLAYER family, `140024 + 1423` is `PLAYER_DATA(1)`, not a field at +1423.
- **Accessor-macro upgrades are settled closed.** Rewriting arithmetic to use an
  existing accessor changes term order, and `obj_diff` shows a real -O0 object
  difference (`imul`-then-`add` → `lea`-then-`imul`). Value-identical but
  unprovable; do not reopen without a build change.
