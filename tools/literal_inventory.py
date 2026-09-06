#!/usr/bin/env python3
"""Inventory magic-number literals against tools/constants_manifest.json.

For each manifest constant: count call sites of its value across the canonical
independently compiled sources listed by ``data/recovered_sources.json``,
classified by expression shape (see tools/literal_common.py), with eligibility
per the manifest tier gating. Also reports derived-candidate literals
(base < v <= base + stride for offset/stride pairs) and frequent unmapped
values.

Usage:
  python3 tools/literal_inventory.py                > literal_inventory.json
  python3 tools/literal_inventory.py --full         # include every site
  python3 tools/literal_inventory.py --unmapped 40  # top-N unmapped values
  python3 tools/literal_inventory.py --census-sites  # all integers and floats
  python3 tools/literal_inventory.py --dispositions reviewed.json
"""
import argparse
import bisect
from collections import Counter
import fnmatch
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc
from split_source_index import scan_definitions


# Keep the historical integer classifier untouched. This broader lexer is for
# accounting only: notably, float tokens must never be matched to integer names.
CENSUS_TOKEN_RE = re.compile(
    r'(?P<skip>//(?:\\\r?\n|[^\n])*|/\*[\s\S]*?\*/'
    r'|(?:u8|u|U|L)?R"(?P<delimiter>[^\s()\\]{0,16})\([\s\S]*?\)(?P=delimiter)"'
    r'|(?:u8|u|U|L)?"(?:\\[\s\S]|[^"\\])*"'
    r"|(?:u8|u|U|L)?'(?:\\[\s\S]|[^'\\])*')"
    r'|(?P<ident>[A-Za-z_][A-Za-z0-9_]*)'
    r"|(?P<number>(?:[0-9]|\.[0-9])(?:[eEpP][+-]|[A-Za-z0-9_.'])*)"
    r'|(?P<op><<=|>>=|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\|'
    r'|\+=|-=|\*=|/=|%=|&=|\|=|\^=|[^\s])'
)
DIGITS = r"[0-9](?:'?[0-9])*"
HEX_DIGITS = r"[0-9a-fA-F](?:'?[0-9a-fA-F])*"
FLOAT_RE = re.compile(
    r'(?P<body>(?:'
    r'0[xX](?:' + HEX_DIGITS + r'(?:\.(?:' + HEX_DIGITS + r')?)?'
    r'|\.' + HEX_DIGITS + r')[pP][+-]?' + DIGITS + r'|'
    r'(?:' + DIGITS + r'\.(?:' + DIGITS + r')?|\.' + DIGITS + r')'
    r'(?:[eE][+-]?' + DIGITS + r')?|'
    + DIGITS + r'[eE][+-]?' + DIGITS + r'))(?P<suffix>[fFlL]?)\Z'
)
INTEGER_RE = re.compile(
    r'(?P<body>0[xX]' + HEX_DIGITS + r'|0[bB][01](?:\'?[01])*|'
    + DIGITS + r')(?P<suffix>[uUlLzZ]{0,3})\Z'
)
CLASSIFICATIONS = ("replaceable", "legitimate", "unresolved")
MATCH_FIELDS = {"file", "fn", "raw", "kind", "context", "line", "column",
                "fn_regex", "expr_regex"}


def census_tokens(text):
    """Lex code without splitting float, radix, suffix or digit-separator tokens."""
    starts = lc.line_starts(text)
    mask = lc.preproc_line_mask(text)
    return [lc.Tok(match.lastgroup, match.start(), match.end(), match.group())
            for match in CENSUS_TOKEN_RE.finditer(text)
            if match.lastgroup != "skip"
            and not mask[bisect.bisect_right(starts, match.start()) - 1]]


def definition_text(text):
    """Protect the shared definition scanner from C++ lexical extensions."""
    chars = list(text)
    for match in CENSUS_TOKEN_RE.finditer(text):
        if match.lastgroup == "number":
            for offset in range(match.start(), match.end()):
                if chars[offset] == "'":
                    chars[offset] = "0"
        elif match.lastgroup == "skip" and re.match(r'(?:u8|u|U|L)?R"', match.group()):
            for offset in range(match.start(), match.end()):
                if chars[offset] not in "\r\n":
                    chars[offset] = " "
    return "".join(chars)


def numeric_details(raw):
    """Return lexical type information; never infer an expression's C++ type."""
    match = FLOAT_RE.fullmatch(raw)
    if match:
        suffix = match["suffix"]
        return {"kind": "float", "suffix": suffix,
                "literal_type": {"f": "float", "l": "long double"}.get(
                    suffix.lower(), "double"),
                "value": match["body"].replace("'", "")}
    match = INTEGER_RE.fullmatch(raw)
    if match:
        body = match["body"].replace("'", "")
        base = (16 if body.lower().startswith("0x") else
                2 if body.lower().startswith("0b") else
                8 if body.startswith("0") and len(body) > 1 else 10)
        try:
            value = int(body, base)
        except ValueError:
            return {"kind": "unrecognized_number", "value": raw,
                    "suffix": "", "literal_type": "unresolved"}
        return {"kind": "integer", "suffix": match["suffix"], "value": value,
                "literal_type": "integer (type depends on radix, value and suffix)"}
    return {"kind": "unrecognized_number", "value": raw,
            "suffix": "", "literal_type": "unresolved"}


def load_dispositions(path):
    """Read evidence-bearing review rules; rules classify, never rewrite code."""
    if not path:
        return []
    with open(path, encoding="utf-8") as stream:
        document = json.load(stream)
    if document.get("schema_version") != 1 or not isinstance(document.get("rules"), list):
        raise ValueError("dispositions require schema_version 1 and rules")
    rules, ids = [], set()
    for item in document["rules"]:
        rule = dict(item)
        identifier = rule.get("id")
        if not isinstance(identifier, str) or not identifier or identifier in ids:
            raise ValueError("disposition rule ids must be unique nonempty strings")
        ids.add(identifier)
        if rule.get("classification") not in ("legitimate", "unresolved"):
            raise ValueError("review dispositions may only be legitimate or unresolved")
        match = rule.get("match", {})
        if not isinstance(match, dict) or not match or set(match) - MATCH_FIELDS:
            raise ValueError("invalid disposition match for %s" % identifier)
        if not match.get("file"):
            raise ValueError("dispositions require an explicit file or file glob")
        if not isinstance(rule.get("reason"), str) or not rule["reason"].strip():
            raise ValueError("dispositions require a reason")
        evidence = rule.get("evidence")
        if not isinstance(evidence, list) or not evidence or not all(
                isinstance(value, str) and value.strip() for value in evidence):
            raise ValueError("dispositions require nonempty evidence references")
        for field in ("fn_regex", "expr_regex"):
            if field in match:
                re.compile(match[field])
        count = rule.get("expected_count")
        if count is not None and (type(count) is not int or count < 0):
            raise ValueError("expected_count must be a nonnegative integer")
        rules.append(rule)
    return rules


def disposition_matches(site, rule):
    for field, expected in rule["match"].items():
        if field == "file":
            if not fnmatch.fnmatchcase(site["file"], expected):
                return False
        elif field.endswith("_regex"):
            if not re.search(expected, site.get(field[:-6]) or ""):
                return False
        elif site.get(field) != expected:
            return False
    return True


def loop_induction_literals(tokens):
    """Prove only simple for-header induction origins and explicit unit steps.

    The same bare variable must have a zero initializer, a simple bound
    comparison and a unit increment/decrement in that header. Bounds, one-based
    origins, unary signed literals and standalone setters remain unclassified.
    """
    result = {}
    integer_types = lc.CAST_TYPE_WORDS - {"float", "double", "bool", "void"}
    for index, token in enumerate(tokens):
        if token.text != "for" or index + 1 >= len(tokens) or tokens[index + 1].text != "(":
            continue
        depth, separators, end = 1, [], None
        for cursor in range(index + 2, len(tokens)):
            text = tokens[cursor].text
            if text == "(":
                depth += 1
            elif text == ")":
                depth -= 1
                if depth == 0:
                    end = cursor
                    break
            elif text == ";" and depth == 1:
                separators.append(cursor)
        if end is None or len(separators) != 2:
            continue
        first, second = separators
        initial = tokens[index + 2:first]
        condition = tokens[first + 1:second]
        step = tokens[second + 1:end]
        if len(initial) < 3 or initial[-2].text != "=" or initial[-3].kind != "ident":
            continue
        if any(part.kind != "ident" or part.text not in integer_types for part in initial[:-3]):
            continue
        zero = numeric_details(initial[-1].text)
        if zero["kind"] != "integer" or zero["value"] != 0:
            continue
        name = initial[-3].text
        if len(condition) != 3 or condition[0].text != name or condition[1].text not in (
                "<", "<=", ">", ">=", "!=") or condition[2].kind not in ("ident", "number"):
            continue
        if condition[2].kind == "number" and numeric_details(condition[2].text)["kind"] != "integer":
            continue
        spelling = [part.text for part in step]
        unit = None
        if spelling in (["++", name], [name, "++"], ["--", name], [name, "--"]):
            pass
        elif len(step) == 3 and spelling[:2] in ([name, "+="], [name, "-="]):
            unit = step[2]
        elif len(step) == 5 and spelling[:3] == [name, "=", name] and spelling[3] in ("+", "-"):
            unit = step[4]
        else:
            continue
        if unit is not None:
            value = numeric_details(unit.text)
            if value["kind"] != "integer" or value["value"] != 1:
                continue
            result[unit.start] = "unit step of the same simple for-loop induction variable"
        result[initial[-1].start] = "zero origin of a simple for-loop induction variable with a unit step"
    return result


def raw_array_literals(text, tokens):
    """Recognize only file-scope literal-only array initializer payloads.

    Calls, lambdas, arithmetic expressions, macros, casts and assignments make
    the whole initializer unresolved. In particular, an array subscript on an
    assignment's LHS is not an array declarator.
    """
    result, braces, statement_start = set(), [], 0

    def array_declaration(prefix):
        if not prefix or prefix[-1].text != "=":
            return False
        first = next((i for i, part in enumerate(prefix) if part.text == "["), None)
        if first is None or first < 2 or prefix[first - 1].kind != "ident":
            return False
        if any(part.kind != "ident" and part.text != "*" for part in prefix[:first]):
            return False
        depth = 0
        for part in prefix[first:-1]:
            if part.text == "[":
                depth += 1
            elif part.text == "]":
                depth -= 1
            elif depth != 1 or part.text in ("=", ";", "{", "}", "(", ")", ","):
                return False
            if depth < 0 or depth > 1:
                return False
        return depth == 0

    def payload(opening):
        stack, found = [True], set()
        cursor = opening + 1
        while cursor < len(tokens):
            token = tokens[cursor]
            if token.text == "}":
                stack.pop()
                if not stack:
                    return found
                stack[-1] = False
            elif token.text == "{" and stack[-1]:
                stack.append(True)
            elif token.text == "," and not stack[-1]:
                stack[-1] = True
            elif stack[-1] and token.text in ("+", "-"):
                cursor += 1
                if cursor >= len(tokens) or tokens[cursor].kind != "number":
                    return set()
                if numeric_details(tokens[cursor].text)["kind"] == "unrecognized_number":
                    return set()
                found.add(tokens[cursor].start)
                stack[-1] = False
            elif stack[-1] and token.kind == "number":
                if numeric_details(token.text)["kind"] == "unrecognized_number":
                    return set()
                found.add(token.start)
                stack[-1] = False
            else:
                return set()
            cursor += 1
        return set()

    for index, token in enumerate(tokens):
        if token.text == "{":
            prefix = tokens[statement_start:index]
            linkage = bool(prefix and prefix[-1].text == "extern" and re.fullmatch(
                r'extern\s+"C(?:\+\+)?"\s*', text[prefix[-1].start:token.start]))
            if all(brace == "linkage" for brace in braces) and array_declaration(prefix):
                result.update(payload(index))
            braces.append("linkage" if linkage else "block")
            statement_start = index + 1
        elif token.text == "}":
            if braces:
                braces.pop()
            statement_start = index + 1
        elif token.text == ";":
            statement_start = index + 1
    return result


def census_source(text, relative, entries=(), families=None, dispositions=(),
                  known_names=None):
    """Account for every code number, with conservative default dispositions.

    Only a literal inside a recognized array initializer is automatically raw
    data. Array dimensions, small selectors and 0/1 assignments remain visible
    and unresolved: syntax alone cannot establish their gameplay meaning.
    """
    families = families or {}
    definition_source = definition_text(text)
    if known_names is None:
        known_names = {name for name, _line in lc.find_defs(definition_source.splitlines(True))}
    definitions = scan_definitions(definition_source, known_names)
    # Helpers outside the recovered function manifest still own their literals.
    extra_names = {name for name, _line in lc.find_defs(definition_source.splitlines(True))}
    if extra_names - known_names:
        definitions = scan_definitions(definition_source, known_names | extra_names)
    starts = lc.line_starts(text)
    definition_starts = [definition.start for definition in definitions]
    toks = census_tokens(text)
    induction_literals = loop_induction_literals(toks)
    raw_payload_literals = raw_array_literals(text, toks)
    legacy_toks, _ = lc.iter_literal_sites(text)
    legacy_at = {token.start: index for index, token in enumerate(legacy_toks)
                 if token.kind == "num"}
    by_value = {}
    for entry in entries:
        if not entry.get("regex_only"):
            by_value.setdefault(entry["value"], []).append(entry)
    out = []
    brackets = []
    for index, token in enumerate(toks):
        previous = toks[index - 1].text if index else ""
        following = toks[index + 1].text if index + 1 < len(toks) else ""
        if token.text == "[":
            brackets.append(index)
        elif token.text == "]" and brackets:
            brackets.pop()
        if token.kind != "number":
            continue
        info = numeric_details(token.text)
        di = bisect.bisect_right(definition_starts, token.start) - 1
        definition = definitions[di] if di >= 0 else None
        fn = definition.name if definition and token.start < definition.end else None
        line_index = bisect.bisect_right(starts, token.start) - 1
        line_end = text.find("\n", token.end)
        expr = text[starts[line_index]:line_end if line_end >= 0 else len(text)].strip()
        context = ("raw_array_initializer" if token.start in raw_payload_literals else
                   "case_label" if previous == "case" else
                   "comparison" if previous in ("==", "!=", "<", ">", "<=", ">=")
                   or following in ("==", "!=", "<", ">", "<=", ">=") else
                   "subscript_or_extent" if brackets else
                   "assignment_or_initializer" if previous == "=" else
                   "arithmetic_or_mask" if previous in ("+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>", "+=", "-=")
                   or following in ("+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>") else
                   "expression")
        candidates = []
        if info["kind"] == "integer" and token.start in legacy_at:
            legacy_index = legacy_at[token.start]
            # The legacy lexer does not recognize every C++ numeric spelling.
            if legacy_toks[legacy_index].text == token.text:
                for entry in by_value.get(info["value"], ()):
                    cls, detail = lc.classify_site(text, legacy_toks, legacy_index, entry,
                                                  families.get(entry.get("family", ""), set()))
                    if lc.eligible(cls, detail, entry):
                        candidates.append(entry["name"])
        classification = "unresolved"
        reason = "meaning requires assembly/data-flow review; value alone is insufficient"
        if context == "raw_array_initializer" and fn is None:
            classification, reason = "legitimate", "file-scope array initializer payload; preserve stored data"
        elif token.start in induction_literals:
            classification, reason = "legitimate", induction_literals[token.start]
        elif len(candidates) == 1:
            classification, reason = "replaceable", "one existing manifest constant passes expression/family eligibility"
        elif len(candidates) > 1:
            reason = "multiple manifest constants pass eligibility; domain requires review"
        site = {"file": relative, "line": line_index + 1,
                "column": token.start - starts[line_index] + 1,
                "fn": fn, "raw": token.text, **info, "context": context,
                "classification": classification, "reason": reason,
                "candidate_constants": sorted(candidates), "expr": expr}
        matches = [rule for rule in dispositions if disposition_matches(site, rule)]
        if len(matches) > 1:
            raise ValueError("overlapping dispositions at %s:%d:%d: %s" % (
                relative, site["line"], site["column"], ", ".join(r["id"] for r in matches)))
        if matches:
            rule = matches[0]
            site.update(classification=rule["classification"], reason=rule["reason"],
                        review_rule=rule["id"], evidence=rule["evidence"])
        out.append(site)
    return out


def summarize_census(sites, files, dispositions=(), include_sites=False):
    """Deterministic totals count occurrences once, regardless of name collisions."""
    by_file = {}
    for relative in sorted(files):
        local = [site for site in sites if site["file"] == relative]
        by_file[relative] = {"total": len(local), **{
            category: sum(site["classification"] == category for site in local)
            for category in CLASSIFICATIONS}}
    counts = Counter(site.get("review_rule") for site in sites)
    for rule in dispositions:
        if rule.get("expected_count") is not None and counts[rule["id"]] != rule["expected_count"]:
            raise ValueError("disposition %s expected %d sites, found %d" % (
                rule["id"], rule["expected_count"], counts[rule["id"]]))
    result = {"schema_version": 1, "total": len(sites), "file_count": len(files),
              "by_classification": {category: sum(site["classification"] == category for site in sites)
                                    for category in CLASSIFICATIONS},
              "by_kind": dict(sorted(Counter(site["kind"] for site in sites).items())),
              "small_integer_sites": sum(site["kind"] == "integer" and site["value"] < 10 for site in sites),
              "outside_function_sites": sum(site["fn"] is None for site in sites),
              "by_file": by_file,
              "review_rules": [{"id": rule["id"], "matched": counts[rule["id"]]}
                               for rule in dispositions]}
    if include_sites:
        result["sites"] = sites
    return result


def git_head():
    try:
        return subprocess.check_output(
            ["git", "rev-parse", "HEAD"], cwd=lc.REPO
        ).decode().strip()
    except Exception:
        return "unknown"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--full", action="store_true", help="include legacy and census sites")
    parser.add_argument("--unmapped", type=int, default=40, help="top-N legacy unmapped values")
    parser.add_argument("--census-sites", action="store_true", help="include every numeric code occurrence")
    parser.add_argument("--dispositions", help="optional schema-v1 evidence-bearing review JSON")
    args = parser.parse_args()
    full = args.full
    unmapped_top = args.unmapped
    dispositions = load_dispositions(args.dispositions)

    entries, families = lc.load_manifest()
    by_value = {}
    for e in entries:
        if e.get("regex_only"):
            continue  # bit flags etc. are bound to a field, not value-counted
        by_value.setdefault(e["value"], []).append(e)

    # derived-candidate windows: (table offset, record size) per family
    derived_windows = []
    for fam in set(e.get("family") for e in entries):
        fam_entries = [e for e in entries if e.get("family") == fam]
        offsets = [e for e in fam_entries if e.get("kind") == "offset" and e["value"] > 10000]
        strides = [e for e in fam_entries if e.get("kind") == "stride"]
        for off in offsets:
            for st in strides:
                derived_windows.append((off["value"], st["value"], off["name"], st["name"]))

    stats = {
        e["name"]: {
            "name": e["name"], "value": e["value"], "spelling": e["spelling"],
            "tier": e.get("tier"), "family": e.get("family"),
            "deferred": bool(e.get("deferred")), "total": 0,
            "eligible": 0,
            "by_class": {}, "files": {}, "samples": [], "sites": [],
        }
        for e in entries
    }
    wanted = set(by_value)
    derived_hits = {}
    unmapped_counts = {}
    census_sites = []
    source_files = lc.apply_files()
    names_by_source = {}
    for record in lc.load_source_manifest()["functions"]:
        names_by_source.setdefault(record["source"], set()).add(record["name"])

    for rel in source_files:
        path = os.path.join(lc.REPO, rel)
        with open(path, errors="replace") as f:
            text = f.read()
        census_sites.extend(census_source(
            text, rel, entries, families, dispositions, names_by_source.get(rel, set())))
        toks, sites = lc.iter_literal_sites(text)
        fn_lookup, line_of, _fn_range = lc.build_fn_map(text)
        for (idx, value) in sites:
            if value not in wanted:
                if value >= 10:
                    unmapped_counts[value] = unmapped_counts.get(value, 0) + 1
                for (base, stride, bname, sname) in derived_windows:
                    if base < value <= base + stride:
                        key = (value, bname)
                        d = derived_hits.setdefault(
                            key, {"value": value, "base": bname,
                                  "delta": value - base, "count": 0, "samples": []})
                        d["count"] += 1
                        if len(d["samples"]) < 4:
                            d["samples"].append(
                                "%s:%d" % (rel, line_of(toks[idx].start) + 1))
                continue
            for entry in by_value[value]:
                fam_names = families.get(entry.get("family", ""), set())
                cls, info = lc.classify_site(text, toks, idx, entry, fam_names)
                st = stats[entry["name"]]
                st["total"] += 1
                st["by_class"][cls] = st["by_class"].get(cls, 0) + 1
                st["files"][rel] = st["files"].get(rel, 0) + 1
                ok = lc.eligible(cls, info, entry)
                if ok:
                    st["eligible"] += 1
                line = line_of(toks[idx].start) + 1
                site = {
                    "file": rel, "line": line,
                    "fn": fn_lookup(toks[idx].start),
                    "class": cls, "eligible": ok,
                    "raw": toks[idx].text,
                    "expr": (info.get("span") or "")[:160],
                }
                if len(st["samples"]) < 6:
                    st["samples"].append(site)
                if full:
                    st["sites"].append(site)

    out_stats = []
    for e in entries:
        st = stats[e["name"]]
        if not full:
            st.pop("sites")
        out_stats.append(st)
    out_stats.sort(key=lambda s: (-s["total"], s["name"]))

    unmapped = sorted(
        ({"value": v, "count": c} for v, c in unmapped_counts.items() if c >= 8),
        key=lambda d: -d["count"],
    )[:unmapped_top]

    json.dump(
        {
            "commit": git_head(),
            "files": source_files,
            "constants": out_stats,
            "derived_candidates": sorted(
                derived_hits.values(), key=lambda d: -d["count"]),
            "unmapped_frequent": unmapped,
            "census": summarize_census(census_sites, source_files, dispositions,
                                       include_sites=full or args.census_sites),
        },
        sys.stdout, indent=1,
    )
    sys.stdout.write("\n")


if __name__ == "__main__":
    main()
