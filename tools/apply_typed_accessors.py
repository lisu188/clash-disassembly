#!/usr/bin/env python3
"""C-C Rung-1 accessor rewriter: turn raw-offset cast sites into existing
accessor MACROS from src/recovered_types.h, staying BYTE-IDENTICAL.

Design (proof-centered — the proof, not the matcher, is the safety net):

  * Parse every candidate accessor MACRO BODY and every SITE with the SAME
    cast parser into (width-token-tuple, has-(uintptr_t), base, offset-K).
  * Index macros by key = (width, uintptr, K). A site matches iff its key hits
    exactly one macro (ambiguity -> refuse & report).
  * base_text is the EXACT source substring of the site's base sub-expression
    (internal parens preserved), so the rewrite MACRO(base_text) only ADDS the
    macro's wrapping parens -> parse tree unchanged -> -O0 codegen identical.
  * PROOF before any accept: expand the macro body with param:=base tokens,
    strip ALL parens and canonicalize numbers/offset-#defines on BOTH the
    expansion and the site, and require TOKEN EQUALITY. Anything else refuses.

Why this refuses the folded-absolute sites automatically: a site written
`gameData + UNIT_STACK_STRIDE*idx + 147176` parses to K=147176, which matches no
macro (macros carry small relative K like 0/2/4/6/8) -> skipped. Only
bare-pointer + small-relative-K sites (`slotPtr + 8`) match and rewrite cleanly.

Usage:
  apply_typed_accessors.py --family UNIT_SLOT [--family ...]
      [--only src/units/foo.c ...] [--exclude src/strategic/]
      [--plan] [--plan-out plan.json] [--apply]
"""
import argparse
import json
import os
import re
import sys
from collections import Counter, defaultdict

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import literal_common as lc
import pp_token_diff as ppd

TYPES_H = os.path.join(lc.REPO, "src/recovered_types.h")

# object-like type #defines gcc expands during preprocessing (src/compatibility/
# defs.h) -> the pp_allow hunks must match the expanded form, not the idiom.
PP_TYPE_MACROS = {
    "__int8": ["char"], "__int16": ["short"], "__int32": ["int"],
    "__int64": ["long", "long"],
}


def pp_lex_expand(text, objvals):
    """Lex `text` the way pp_token_diff lexes a preprocessed file, expanding the
    object-like macros gcc would expand (type idioms + numeric offset #defines)."""
    out = []
    for t in ppd.TOK_RE.findall(text):
        if t in PP_TYPE_MACROS:
            out.extend(PP_TYPE_MACROS[t])
        elif t in objvals:
            out.append(str(objvals[t]))
        else:
            out.append(t)
    return out


def pp_hunk(site_text, body, param, base_text, objvals):
    """(before_tokens, after_tokens) for one rewrite, as pp_token_diff sees them."""
    before = pp_lex_expand(site_text, objvals)
    expanded = re.sub(r"\b" + re.escape(param) + r"\b",
                      lambda _m: base_text, body)
    after = pp_lex_expand(expanded, objvals)
    return before, after


# ---- numeric normalization ------------------------------------------------
def obj_macro_values():
    vals = {}
    for name, macro in lc.parse_prelude_macros().items():
        v = lc.numeric_macro_value(macro)
        if v is not None:
            vals[name] = v
    return vals


def canon_num(t):
    try:
        return int(t, 0)
    except (ValueError, TypeError):
        return None


def resolve_int(tok, objvals):
    """A single token -> its integer value, else None."""
    if tok in objvals:
        return objvals[tok]
    return canon_num(tok)


def norm(text_tokens, objvals):
    """Strip parens; map offset macros + numeric literals to canonical ints
    (as 'i<n>' strings so they never collide with identifiers)."""
    out = []
    for t in text_tokens:
        if t in ("(", ")"):
            continue
        if t in objvals:
            out.append("i%d" % objvals[t])
            continue
        n = canon_num(t)
        out.append("i%d" % n if n is not None else t)
    return tuple(out)


# ---- token utilities on literal_common tokenize ---------------------------
def code_tokens(text):
    return [t for t in lc.tokenize(text) if t.kind not in ("skip", "pp")]


def match_paren(ct, open_i):
    depth = 0
    for j in range(open_i, len(ct)):
        if ct[j].text == "(":
            depth += 1
        elif ct[j].text == ")":
            depth -= 1
            if depth == 0:
                return j
    return None


def top_level_depths(toks):
    """Paren depth BEFORE each token (0 = top level)."""
    depths, d = [], 0
    for t in toks:
        depths.append(d)
        if t.text == "(":
            d += 1
        elif t.text == ")":
            d -= 1
    return depths


def split_base_k(operand, objvals):
    """operand code-tokens -> (base_tokens, K_int). Trailing top-level `+ NUM`
    (or `+ OFFSET_MACRO`) becomes K; otherwise K=0 and base=operand."""
    if len(operand) >= 2 and operand[-2].text == "+":
        depths = top_level_depths(operand)
        if depths[-2] == 0:
            k = resolve_int(operand[-1].text, objvals)
            if k is not None:
                return operand[:-2], k
    return operand, 0


def parse_cast(ct, i, objvals):
    """Parse `*(WIDTH *)[(uintptr_t)](operand)` starting at ct[i]=='*'.
    Returns (end_i, width_tuple, has_uintptr, base_tokens, K) or None."""
    if ct[i].text != "*":
        return None
    p = i - 1
    if p >= 0 and (ct[p].kind in ("ident", "num") or ct[p].text in (")", "]")):
        return None  # binary '*'
    if i + 1 >= len(ct) or ct[i + 1].text != "(":
        return None
    k = match_paren(ct, i + 1)
    if k is None:
        return None
    inner = ct[i + 2:k]
    if not inner or inner[-1].text != "*":
        return None
    width = tuple(t.text for t in inner[:-1])
    if not width:
        return None
    q = k + 1
    has_uintptr = False
    if (q + 2 < len(ct) and ct[q].text == "(" and ct[q + 1].text == "uintptr_t"
            and ct[q + 2].text == ")"):
        has_uintptr = True
        q += 3
    if q >= len(ct):
        return None
    if ct[q].text == "(":
        r = match_paren(ct, q)
        if r is None:
            return None
        operand = ct[q + 1:r]
        end = r
    elif ct[q].kind == "ident":
        operand = [ct[q]]
        end = q
    else:
        return None
    if not operand:
        return None
    base, K = split_base_k(operand, objvals)
    if not base:
        return None
    return end, width, has_uintptr, base, K


# ---- accessor-macro index -------------------------------------------------
def macro_body_code_tokens(body):
    """Tokenize a macro body string into literal_common Tok-likes (text/kind)."""
    return code_tokens(body)


def build_macro_index(families, objvals):
    """key (width_tuple, uintptr_bool, K_int) -> list of (name, family, param)."""
    idx = defaultdict(list)
    by_name = {}
    for name, macro in lc.parse_prelude_macros().items():
        fam = next((f for f in families if name.startswith(f + "_")), None)
        if fam is None:
            continue
        params = macro.get("params")
        if not params:  # object-like macro (no param list) -> not a field reader
            continue
        parts = [x.strip() for x in params.strip("() \t").split(",") if x.strip()]
        if len(parts) != 1:
            continue
        param = parts[0]
        ct = macro_body_code_tokens(macro["body"])
        # find the '*' that starts the cast-deref
        star = next((n for n, t in enumerate(ct)
                     if t.text == "*" and n + 1 < len(ct) and ct[n + 1].text == "("),
                    None)
        if star is None:
            continue
        parsed = parse_cast(ct, star, objvals)
        if parsed is None:
            continue
        _end, width, uintptr, base, K = parsed
        # body base must reduce to exactly the single param (pure field reader);
        # the body wraps it as `(param)`, so compare paren-stripped
        base_core = [t.text for t in base if t.text not in ("(", ")")]
        if base_core != [param]:
            continue
        key = (width, uintptr, K)
        idx[key].append((name, fam, param))
        by_name[name] = (macro["body"], param, width, uintptr, K)
    return idx, by_name


# ---- family-name hint (for disambiguation only, never for safety) ---------
FAMILY_HINT = {
    "UNIT_STACK": ("stack", "unit"),
    "UNIT_SLOT": ("slot",),
    "BUILDING": ("build", "castle", "town"),
    "PLAYER": ("player", "owner"),
    "TILE": ("tile", "map"),
}


def base_hint_family(base_text, families):
    low = base_text.lower()
    scored = []
    for fam in families:
        hints = FAMILY_HINT.get(fam, ())
        if any(h in low for h in hints):
            scored.append(fam)
    return scored


def all_hinted_families(base_text):
    """Every family whose name-hint appears in the base (across ALL families,
    not just requested), for cross-family mislabel detection."""
    low = base_text.lower()
    return {fam for fam, hints in FAMILY_HINT.items()
            if any(h in low for h in hints)}


# ---- site scan + proof ----------------------------------------------------
def scan_file(path, mac_idx, by_name, families, objvals):
    # newline="" keeps bytes faithful (files are CRLF in-tree) so char offsets
    # match --apply's read/write exactly and line endings survive the rewrite.
    text = open(path, encoding="utf-8", errors="surrogateescape", newline="").read()
    ct = code_tokens(text)
    accepted, refused = [], []
    i = 0
    n = len(ct)
    while i < n:
        if ct[i].text != "*":
            i += 1
            continue
        parsed = parse_cast(ct, i, objvals)
        if parsed is None:
            i += 1
            continue
        end, width, uintptr, base, K = parsed
        site_start = ct[i].start
        site_end = ct[end].end
        site_txt = text[site_start:site_end]
        key = (width, uintptr, K)
        cands = mac_idx.get(key, [])
        if not cands:
            i = end + 1
            continue
        base_text = text[base[0].start:base[-1].end]
        # disambiguation
        chosen = cands
        if len(cands) > 1:
            hinted = [c for c in cands if c[1] in base_hint_family(base_text, families)]
            chosen = hinted if len(hinted) == 1 else cands
        if len(chosen) != 1:
            refused.append({
                "file": os.path.relpath(path, lc.REPO), "line": text[:site_start].count("\n") + 1,
                "site": site_txt, "reason": "ambiguous",
                "candidates": [c[0] for c in chosen]})
            i = end + 1
            continue
        name, fam, param = chosen[0]
        # cross-family mislabel guard: base name hints a DIFFERENT record family
        hinted = all_hinted_families(base_text)
        if hinted and fam not in hinted:
            refused.append({
                "file": os.path.relpath(path, lc.REPO), "line": text[:site_start].count("\n") + 1,
                "site": site_txt, "reason": "cross_family", "macro": name,
                "base": base_text, "hints": sorted(hinted)})
            i = end + 1
            continue
        body, mparam, mwidth, muintptr, mK = by_name[name]
        # PROOF: expand macro body with param := base code tokens, compare norm
        body_ct = macro_body_code_tokens(body)
        expanded = []
        for t in body_ct:
            if t.text == mparam:
                expanded.extend(bt.text for bt in base)
            else:
                expanded.append(t.text)
        site_ct = ct[i:end + 1]
        if norm(expanded, objvals) != norm([t.text for t in site_ct], objvals):
            refused.append({
                "file": os.path.relpath(path, lc.REPO), "line": text[:site_start].count("\n") + 1,
                "site": site_txt, "reason": "proof_mismatch", "macro": name})
            i = end + 1
            continue
        before_toks, after_toks = pp_hunk(site_txt, body, param, base_text, objvals)
        accepted.append({
            "file": os.path.relpath(path, lc.REPO),
            "line": text[:site_start].count("\n") + 1,
            "start": site_start, "end": site_end,
            "site": site_txt, "macro": name, "family": fam,
            "base": base_text, "new": "%s(%s)" % (name, base_text),
            "pp_allow": [before_toks, after_toks]})
        i = end + 1
    return accepted, refused


# ---- driver ---------------------------------------------------------------
def iter_source_files(only, exclude):
    if only:
        for p in only:
            yield os.path.join(lc.REPO, p) if not os.path.isabs(p) else p
        return
    src = os.path.join(lc.REPO, "src")
    for root, _dirs, files in os.walk(src):
        rel = os.path.relpath(root, lc.REPO).replace("\\", "/")
        if any(rel.startswith(x.rstrip("/")) for x in exclude):
            continue
        if "/clips" in "/" + rel:
            continue
        for f in files:
            if f.endswith(".c"):
                yield os.path.join(root, f)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--family", action="append", required=True)
    ap.add_argument("--only", nargs="*", default=None)
    ap.add_argument("--exclude", action="append", default=["src/strategic/", "src/clips/"])
    ap.add_argument("--plan", action="store_true")
    ap.add_argument("--plan-out", default=None)
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()

    objvals = obj_macro_values()
    mac_idx, by_name = build_macro_index(args.family, objvals)
    if not by_name:
        print("no accessor macros for families %s" % args.family, file=sys.stderr)
        return 2
    print("macro index: %d field-reader macros across %d keys"
          % (len(by_name), len(mac_idx)), file=sys.stderr)

    all_acc, all_ref = [], []
    for path in iter_source_files(args.only, args.exclude):
        acc, ref = scan_file(path, mac_idx, by_name, args.family, objvals)
        all_acc.extend(acc)
        all_ref.extend(ref)

    by_file = Counter(a["file"] for a in all_acc)
    by_macro = Counter(a["macro"] for a in all_acc)
    ref_reason = Counter(r["reason"] for r in all_ref)
    print("\n=== ACCEPTED %d sites ===" % len(all_acc))
    for f, c in by_file.most_common():
        print("  %4d  %s" % (c, f))
    print("--- by macro ---")
    for m, c in by_macro.most_common():
        print("  %4d  %s" % (c, m))
    print("=== REFUSED %d (%s) ===" % (len(all_ref), dict(ref_reason)))

    if args.plan_out:
        # directly consumable by pp_token_gate.sh --allow (reads plan["entries"])
        json.dump({"entries": all_acc, "refused": all_ref},
                  open(args.plan_out, "w"), indent=1)
        print("wrote plan -> %s" % args.plan_out)

    if args.apply:
        per_file = defaultdict(list)
        for a in all_acc:
            per_file[a["file"]].append(a)
        for rel, sites in per_file.items():
            path = os.path.join(lc.REPO, rel)
            # newline="" MUST match scan_file's read, or offsets drift by one per
            # CRLF line ending before each site.
            text = open(path, encoding="utf-8", errors="surrogateescape", newline="").read()
            for a in sorted(sites, key=lambda s: s["start"], reverse=True):
                got = text[a["start"]:a["end"]]
                if got != a["site"]:
                    raise SystemExit("offset self-check FAILED in %s at %d:\n"
                                     "  expected %r\n  found    %r"
                                     % (rel, a["start"], a["site"], got))
                text = text[:a["start"]] + a["new"] + text[a["end"]:]
            open(path, "w", encoding="utf-8", errors="surrogateescape", newline="").write(text)
            print("rewrote %d sites in %s" % (len(sites), rel))
    return 0


if __name__ == "__main__":
    sys.exit(main())
