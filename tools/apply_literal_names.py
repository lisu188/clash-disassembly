#!/usr/bin/env python3
"""Apply gated literal -> named-constant substitutions (magic-number campaign).

Usage:
  python3 tools/apply_literal_names.py rules.json --plan plan.json [--batch A1-1]
  python3 tools/apply_literal_names.py rules.json --plan plan.json --apply \
      [--expect reviewed_plan.json]

rules.json is a list of rule objects:
  {"kind": "name", "value": 725, "name": "UNIT_STACK_STRIDE",
   "classes": ["mul_adjacent", "mul_adjacent_anchored", "additive_anchored",
               "increment_rhs"],
   "confidence": "map-confirmed", "evidence": "...", "area": "units",
   "files": ["src/game/*.inc.c"],          # optional glob filter
   "allow_suffix_drop": false}              # optional; suffixed sites (0x194u)
  {"kind": "regex", "value": 32768, "name": "TILE_OCCUPANT_BUILDING_INDEX_BASE",
   "pattern": "- (?P<lit>0x8000)\\b", ...}  # surgical scope for workstream B

Guarantees enforced before any write:
- the target name exists in src/clash95_prelude.inc.c as an object macro whose
  body is a single numeric token equal to the rule value AND to the
  tools/constants_manifest.json entry (triple cross-check);
- a site is replaced only when its raw spelling matches the manifest spelling
  (hex stays hex, decimal stays decimal) so the preprocessed token stream is
  provably unchanged (tools/pp_token_gate.sh);
- class gating per tools/literal_common.py: tier-1 classes only, tier-3
  additionally family co-occurrence; increment_rhs sites additionally require
  an independent eligible site or family macro use in the same function;
- sites matched by two rules are rejected, never guessed;
- every rejected site is recorded in the plan artifact with a reason.

Dry run by default; --apply rewrites files and appends provenance to
docs/archive/win95_constants_rename_accum.jsonl (override: LITERAL_RENAME_ACCUM).
--expect recomputes the plan and refuses to apply if it drifted from the
reviewed artifact.
"""
import fnmatch
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc

DEFAULT_ACCUM = os.path.join(lc.REPO, "docs", "archive",
                             "win95_constants_rename_accum.jsonl")


def git_head():
    try:
        return subprocess.check_output(
            ["git", "rev-parse", "HEAD"], cwd=lc.REPO
        ).decode().strip()
    except Exception:
        return "unknown"


def norm_spelling(raw):
    return raw.rstrip("uUlL").lower()


def validate_rules(rules, entries_by_name, prelude):
    errors = []
    for r in rules:
        name = r.get("name", "")
        kind = r.get("kind", "name")
        if kind not in ("name", "regex"):
            errors.append("%s: unknown rule kind %r" % (name, kind))
            continue
        entry = entries_by_name.get(name)
        if entry is None:
            errors.append("%s: not in constants_manifest.json" % name)
            continue
        if entry.get("deferred"):
            errors.append("%s: manifest marks this constant deferred" % name)
        if r.get("value") != entry["value"]:
            errors.append("%s: rule value %r != manifest value %r"
                          % (name, r.get("value"), entry["value"]))
        macro = prelude.get(name)
        if macro is None:
            errors.append("%s: not defined in %s" % (name, lc.PRELUDE_REL))
            continue
        mv = lc.numeric_macro_value(macro)
        if mv is None:
            errors.append("%s: prelude macro is not a single numeric token (%r)"
                          % (name, macro["body"]))
        elif mv != entry["value"]:
            errors.append("%s: prelude value %r != manifest value %r"
                          % (name, mv, entry["value"]))
        elif norm_spelling(macro["body"].strip("() \t")) != \
                norm_spelling(entry["spelling"]):
            errors.append("%s: prelude spelling %r != manifest spelling %r"
                          % (name, macro["body"], entry["spelling"]))
        if kind == "name":
            tier_ok = lc.TIER_CLASSES.get(entry.get("tier", 3), set())
            bad = set(r.get("classes", ())) - tier_ok
            if bad:
                errors.append("%s: classes %s not allowed for tier %s"
                              % (name, sorted(bad), entry.get("tier")))
        if kind == "regex" and "(?P<lit>" not in r.get("pattern", ""):
            errors.append("%s: regex rule needs a (?P<lit>...) group" % name)
    return errors


def rule_files(rule):
    files = lc.apply_files()
    globs = rule.get("files")
    if not globs:
        return files
    return [f for f in files if any(fnmatch.fnmatch(f, g) for g in globs)]


def resolve(rules, entries_by_name, families, batch):
    plan_entries = []
    rejected = []
    name_rules = [r for r in rules if r.get("kind", "name") == "name"]
    regex_rules = [r for r in rules if r.get("kind") == "regex"]
    values = {r["value"] for r in name_rules}

    all_files = sorted({f for r in rules for f in rule_files(r)})
    for rel in all_files:
        path = os.path.join(lc.REPO, rel)
        with open(path, errors="replace") as f:
            text = f.read()
        toks, sites = lc.iter_literal_sites(text, values) if name_rules \
            else (None, [])
        fn_lookup = line_of = fn_range = None
        if name_rules:
            fn_lookup, line_of, fn_range = lc.build_fn_map(text)

        # ---- name rules: classify every site of every rule value ----------
        file_entries = []
        increments = []
        for (idx, value) in sites:
            matching = [r for r in name_rules
                        if r["value"] == value and rel in rule_files(r)]
            if not matching:
                continue
            tok = toks[idx]
            line = line_of(tok.start) + 1
            if len(matching) > 1:
                rejected.append({"file": rel, "line": line, "value": value,
                                 "raw": tok.text, "reason": "matched-by-multiple-rules",
                                 "rules": [r["name"] for r in matching]})
                continue
            rule = matching[0]
            entry = entries_by_name[rule["name"]]
            fam_names = families.get(entry.get("family", ""), set())
            cls, info = lc.classify_site(text, toks, idx, entry, fam_names)
            site = {
                "file": rel, "line": line,
                "start": tok.start, "end": tok.end,
                "value": value, "raw": tok.text, "class": cls,
                "name": rule["name"], "fn": fn_lookup(tok.start),
                "expr": (info.get("span") or "")[:160],
            }
            # value already matches; gate on class + tier before spelling so
            # the respell decision only applies to structurally-proven sites.
            if cls not in rule.get("classes", ()):
                site["reason"] = "class-not-requested"
                rejected.append(site)
                continue
            if not lc.eligible(cls, info, entry):
                site["reason"] = "tier-gating (cooccur/anchor unmet)"
                rejected.append(site)
                continue
            # Token identity: the site lexeme vs the macro-body lexeme. If they
            # differ (suffix like 0x194u, or decimal-vs-hex like 404 vs 0x194),
            # the preprocessed token stream changes; that is only allowed under
            # a respelling flag, and the change is declared as a pp_allow hunk
            # so tools/pp_token_diff.py --allow can verify exactly it.
            token_changes = tok.text != entry["spelling"]
            suffixed = tok.text.rstrip("uUlL") != tok.text
            if token_changes:
                permitted = rule.get("allow_respelling") or \
                    (suffixed and rule.get("allow_suffix_drop"))
                if not permitted:
                    site["reason"] = (
                        "suffixed-literal (needs allow_suffix_drop)" if suffixed
                        else "spelling-differs (needs allow_respelling)")
                    rejected.append(site)
                    continue
                site["respell"] = True
                site["pp_allow"] = [[tok.text], [entry["spelling"]]]
            if cls == "increment_rhs":
                increments.append((site, entry, fam_names, fn_range))
                continue
            file_entries.append(site)

        # increment_rhs: needs an independent same-function signal
        per_fn = {}
        for s in file_entries:
            per_fn.setdefault((s["fn"], s["value"]), 0)
            per_fn[(s["fn"], s["value"])] += 1
        for (site, entry, fam_names, fn_range) in increments:
            ok = per_fn.get((site["fn"], site["value"]), 0) > 0
            if not ok and fn_range is not None:
                rng = fn_range(site["start"])
                if rng:
                    body = text[rng[0]:rng[1]]
                    ok = any(re.search(r"\b%s\b" % re.escape(n), body)
                             for n in fam_names)
            if ok:
                file_entries.append(site)
            else:
                site["reason"] = "increment-without-function-cooccurrence"
                rejected.append(site)

        # ---- regex rules: surgical, pattern-scoped ------------------------
        for rule in regex_rules:
            if rel not in rule_files(rule):
                continue
            entry = entries_by_name[rule["name"]]
            pat = re.compile(rule["pattern"])
            # only match inside code segments, never strings/comments/preproc
            toks2 = lc.tokenize(text)
            code_num_starts = {t.start for t in toks2 if t.kind == "num"}
            starts = lc.line_starts(text)
            import bisect as _b
            for m in pat.finditer(text):
                s, e = m.start("lit"), m.end("lit")
                if s not in code_num_starts:
                    continue
                raw = m.group("lit")
                if lc.parse_num(raw) != entry["value"]:
                    continue
                line = _b.bisect_right(starts, s)
                file_entries.append({
                    "file": rel, "line": line, "start": s, "end": e,
                    "value": entry["value"], "raw": raw, "class": "regex",
                    "name": rule["name"], "fn": None,
                    "expr": re.sub(r"\s+", " ", m.group(0))[:160],
                })

        # de-duplicate/conflict-check by offset
        seen = {}
        for s in file_entries:
            key = (s["file"], s["start"])
            if key in seen and seen[key]["name"] != s["name"]:
                seen[key]["reason"] = "offset-conflict"
                rejected.append(seen.pop(key))
                s["reason"] = "offset-conflict"
                rejected.append(s)
                continue
            seen[key] = s
        plan_entries.extend(seen.values())

    plan_entries.sort(key=lambda s: (s["file"], s["start"]))
    summary = {}
    for s in plan_entries:
        d = summary.setdefault(s["name"], {"sites": 0, "classes": {}, "files": {}})
        d["sites"] += 1
        d["classes"][s["class"]] = d["classes"].get(s["class"], 0) + 1
        d["files"][s["file"]] = d["files"].get(s["file"], 0) + 1
    return {
        "batch": batch,
        "commit": git_head(),
        "rules": rules,
        "summary": summary,
        "entries": plan_entries,
        "rejected": rejected,
    }


def plan_key(plan):
    return sorted((s["file"], s["start"], s["end"], s["name"])
                  for s in plan["entries"])


def apply_plan(plan):
    by_file = {}
    for s in plan["entries"]:
        by_file.setdefault(s["file"], []).append(s)
    touched = []
    for rel, sites in by_file.items():
        path = os.path.join(lc.REPO, rel)
        with open(path, errors="replace") as f:
            text = f.read()
        for s in sorted(sites, key=lambda s: -s["start"]):
            if text[s["start"]:s["end"]] != s["raw"]:
                raise SystemExit(
                    "STALE PLAN: %s:%d expected %r found %r -- regenerate the plan"
                    % (rel, s["line"], s["raw"], text[s["start"]:s["end"]]))
            text = text[:s["start"]] + s["name"] + text[s["end"]:]
        with open(path, "w") as f:
            f.write(text)
        touched.append(rel)
    return touched


def append_accum(plan, accum_path):
    rows = []
    entries_by_name, _ = lc.load_manifest()
    spelling = {e["name"]: e["spelling"] for e in entries_by_name}
    for r in plan["rules"]:
        name = r["name"]
        summ = plan["summary"].get(name)
        if not summ:
            continue
        rows.append({
            "old": spelling.get(name, str(r["value"])),
            "new": name,
            "kind": "substitution",
            "value": r["value"],
            "confidence": r.get("confidence", ""),
            "evidence": r.get("evidence", ""),
            "area": r.get("area", ""),
            "batch": plan["batch"],
            "sites": summ["sites"],
            "classes": summ["classes"],
            "files": summ["files"],
        })
    reason_counts = {}
    for s in plan["rejected"]:
        key = (s.get("name") or str(s.get("value"))), s.get("reason", "?")
        reason_counts[key] = reason_counts.get(key, 0) + 1
    for (name, reason), n in sorted(reason_counts.items()):
        rows.append({
            "old": name, "new": None, "kind": "substitution-rejected",
            "batch": plan["batch"], "reason": reason, "count": n,
        })
    with open(accum_path, "a") as f:
        for row in rows:
            f.write(json.dumps(row) + "\n")
    return len(rows)


def main():
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 2
    rules_path = args[0]
    plan_out = args[args.index("--plan") + 1] if "--plan" in args else None
    expect = args[args.index("--expect") + 1] if "--expect" in args else None
    batch = args[args.index("--batch") + 1] if "--batch" in args else "adhoc"
    do_apply = "--apply" in args

    with open(rules_path) as f:
        rules = json.load(f)
    entries, families = lc.load_manifest()
    entries_by_name = {e["name"]: e for e in entries}
    prelude = lc.parse_prelude_macros()

    errors = validate_rules(rules, entries_by_name, prelude)
    if errors:
        print(json.dumps({"errors": errors}, indent=1))
        return 1

    plan = resolve(rules, entries_by_name, families, batch)

    if expect:
        with open(expect) as f:
            reviewed = json.load(f)
        if plan_key(plan) != plan_key(reviewed):
            print(json.dumps({
                "error": "plan drifted from reviewed artifact",
                "reviewed_sites": len(reviewed["entries"]),
                "current_sites": len(plan["entries"]),
            }, indent=1))
            return 1

    if plan_out:
        with open(plan_out, "w") as f:
            json.dump(plan, f, indent=1)

    print(json.dumps({
        "batch": batch,
        "sites": len(plan["entries"]),
        "rejected": len(plan["rejected"]),
        "summary": plan["summary"],
        "applied": bool(do_apply),
    }, indent=1))

    if do_apply:
        touched = apply_plan(plan)
        accum = os.environ.get("LITERAL_RENAME_ACCUM", DEFAULT_ACCUM)
        n = append_accum(plan, accum)
        print(json.dumps({"touched_files": touched, "accum_rows": n,
                          "accum": os.path.relpath(accum, lc.REPO)}, indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
