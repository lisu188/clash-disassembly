#!/usr/bin/env python3
"""Compare two preprocessed C files as token streams (gate G1/G2).

Usage:
  python3 tools/pp_token_diff.py before.i after.i [--allow plan.json]

Strict mode: exit 0 iff both files lex to the identical token sequence.
Because a #define-name substitution expands back to the exact original
literal token, a clean strict diff PROVES a substitution batch is
value-identical (stronger than the binary diff this repo does not have).

--allow plan.json: tolerate exactly the token hunks the plan artifact
declares (entries' "pp_allow": [[before...], [after...]] pairs, e.g. the
0x194u -> 0x194 suffix drops). Any other divergence still fails.
"""
import json
import re
import sys

TOK_RE = re.compile(
    r'"(?:[^"\\]|\\.)*"'
    r"|'(?:[^'\\]|\\.)*'"
    r"|[A-Za-z_][A-Za-z0-9_]*"
    r"|0[xX][0-9a-fA-F]+[uUlL]*"
    r"|(?:\d+\.\d*|\.\d+)(?:[eE][+-]?\d+)?[fFlL]?"
    r"|\d+(?:[eE][+-]?\d+)?[uUlLfF]*"
    r"|\S"
)


def lex(path):
    with open(path, errors="replace") as f:
        return TOK_RE.findall(f.read())


def context(toks, i, n=8):
    return " ".join(toks[max(0, i - n):i + n])


def main():
    args = sys.argv[1:]
    if len(args) < 2:
        print(__doc__)
        return 2
    before = lex(args[0])
    after = lex(args[1])
    allow = []
    if "--allow" in args:
        with open(args[args.index("--allow") + 1]) as f:
            plan = json.load(f)
        for e in plan.get("entries", []):
            if e.get("pp_allow"):
                allow.append((tuple(e["pp_allow"][0]), tuple(e["pp_allow"][1])))

    if before == after:
        print(json.dumps({"ok": True, "tokens": len(after), "hunks": 0}))
        return 0

    # greedy two-pointer walk consuming allowed local hunks
    budget = {}
    for pair in allow:
        budget[pair] = budget.get(pair, 0) + 1
    i = j = 0
    used = 0
    while i < len(before) and j < len(after):
        if before[i] == after[j]:
            i += 1
            j += 1
            continue
        matched = False
        for (b, a), left in sorted(budget.items(), key=lambda kv: -len(kv[0][0])):
            if left <= 0:
                continue
            if tuple(before[i:i + len(b)]) == b and tuple(after[j:j + len(a)]) == a:
                budget[(b, a)] -= 1
                i += len(b)
                j += len(a)
                used += 1
                matched = True
                break
        if not matched:
            print(json.dumps({
                "ok": False,
                "first_divergence": {
                    "before_index": i, "after_index": j,
                    "before": context(before, i),
                    "after": context(after, j),
                },
                "allowed_hunks_used": used,
            }, indent=1))
            return 1
    if i != len(before) or j != len(after):
        print(json.dumps({"ok": False,
                          "error": "length mismatch at tail",
                          "before_left": len(before) - i,
                          "after_left": len(after) - j}, indent=1))
        return 1
    print(json.dumps({"ok": True, "tokens": len(after), "hunks": used}))
    return 0


if __name__ == "__main__":
    sys.exit(main())
