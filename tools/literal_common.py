#!/usr/bin/env python3
"""Shared numeric-literal lexing/classification for the magic-number campaign.

Single source of truth used by literal_inventory.py, apply_literal_names.py,
naming_audit.py --literals, and the substitution verifiers. String literals,
char literals, and comments are never scanned, and preprocessor lines are
skipped so the recovered foundation constant block can never be rewritten
into itself.

Classification model (see docs/archive/REVERSE_ENGINEERING_RENAME_LOG.md,
magic-number campaign sections): each numeric token is located inside its
maximal additive expression (terms joined by binary `+` at the token's own
paren depth). Classes:

  mul_adjacent            literal is a factor in a multiplicative chain
  additive_anchored       additive group references an anchor global
  mul_adjacent_anchored   both of the above
  call_arg                literal is a whole size argument of a whitelisted
                          copy/fill call (qmemcpy/memcpy/memset/memmove)
  increment_rhs           literal is the whole RHS of a `+=` step; only
                          eligible when the enclosing function independently
                          uses the same value in an anchored/mul context
  forbidden               additive group references a forbid_anchor
  unsafe                  `-`, unary sign, `++`/`--`, or assignment inside
                          the additive span (never auto-replaced)
  bare                    none of the above (never auto-replaced)

Self-test: python3 tools/literal_common.py --selftest
"""
import bisect
import json
import os
import re
import sys

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(TOOLS_DIR)
sys.path.insert(0, TOOLS_DIR)
from global_inventory import (  # noqa: E402
    find_defs,
    load_source_manifest,
    recovered_source_files,
)
from split_source_index import body_sha256, scan_definitions  # noqa: E402

PRELUDE_REL = "src/recovered_foundation.h"
MANIFEST_REL = "tools/constants_manifest.json"
SOURCE_MANIFEST_REL = "data/recovered_sources.json"

CALL_ARG_WHITELIST = {"qmemcpy", "memcpy", "memset", "memmove"}

def apply_files():
    """Canonical independently compiled recovered implementation files."""
    return recovered_source_files()


def split_code_and_literals(text):
    """Yield ``(is_code, segment)`` pairs without parsing C semantics."""
    out = []
    index = 0
    length = len(text)
    start = 0
    while index < length:
        char = text[index]
        following = text[index + 1] if index + 1 < length else ""
        if char in ('"', "'"):
            out.append((True, text[start:index]))
            quote = char
            cursor = index + 1
            while cursor < length:
                if text[cursor] == "\\":
                    cursor += 2
                    continue
                if text[cursor] == quote:
                    cursor += 1
                    break
                cursor += 1
            out.append((False, text[index:cursor]))
            index = cursor
            start = index
        elif char == "/" and following == "/":
            out.append((True, text[start:index]))
            cursor = text.find("\n", index)
            cursor = length if cursor == -1 else cursor
            out.append((False, text[index:cursor]))
            index = cursor
            start = index
        elif char == "/" and following == "*":
            out.append((True, text[start:index]))
            cursor = text.find("*/", index + 2)
            cursor = length if cursor == -1 else cursor + 2
            out.append((False, text[index:cursor]))
            index = cursor
            start = index
        else:
            index += 1
    out.append((True, text[start:]))
    return out


def refresh_source_manifest_body_hashes(relative_files):
    """Refresh canonical body hashes after an approved source rewrite.

    Legacy/oracle hashes remain immutable evidence. Every manifest function in
    a touched file must still be found exactly once before the manifest is
    rewritten.
    """
    touched = set(relative_files)
    if not touched:
        return 0
    document = load_source_manifest()
    records = document["functions"]
    by_source = {}
    for record in records:
        by_source.setdefault(record["source"], []).append(record)
    unknown = sorted(touched - set(by_source))
    # The state owner contains no indexed recovered function bodies.
    unknown = [path for path in unknown if path != document.get("state_owner")]
    if unknown:
        raise ValueError("touched files are absent from source manifest: %s"
                         % ", ".join(unknown))

    updated = 0
    for relative in sorted(touched & set(by_source)):
        path = os.path.join(REPO, relative)
        with open(path, errors="replace") as stream:
            text = stream.read()
        source_records = by_source[relative]
        wanted = {record["name"] for record in source_records}
        definitions = scan_definitions(text, wanted)
        indexed = {definition.name: definition for definition in definitions}
        if set(indexed) != wanted or len(definitions) != len(wanted):
            missing = sorted(wanted - set(indexed))
            extra = sorted(set(indexed) - wanted)
            raise ValueError(
                "%s no longer matches manifest identities (missing=%r extra=%r)"
                % (relative, missing, extra)
            )
        for record in source_records:
            digest = body_sha256(text, indexed[record["name"]])
            if record.get("body_sha256") != digest:
                record["body_sha256"] = digest
                updated += 1

    manifest_path = os.path.join(REPO, SOURCE_MANIFEST_REL)
    temporary = manifest_path + ".tmp"
    with open(temporary, "w", newline="\n", encoding="utf-8") as stream:
        json.dump(document, stream, indent=2)
        stream.write("\n")
    os.replace(temporary, manifest_path)
    return updated


NUM_TOKEN_RE = re.compile(
    r"(?<![A-Za-z0-9_.])(0[xX][0-9A-Fa-f]+|[0-9]+)([uUlL]{0,3})(?![A-Za-z0-9_.])"
)

TOKEN_RE = re.compile(
    r"""
    (?P<ident>[A-Za-z_][A-Za-z0-9_]*)
  | (?P<float>(?:\d+\.\d*|\.\d+)(?:[eE][+-]?\d+)?[fFlL]?|\d+[eE][+-]?\d+[fFlL]?)
  | (?P<num>(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]{0,3})
  | (?P<op><<=|>>=|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|/=|%=|&=|\|=|\^=
      |[-+*/%&|^!~<>=?:;,.(){}\[\]#\\])
""",
    re.VERBOSE,
)

CAST_TYPE_WORDS = {
    "signed", "unsigned", "int", "char", "short", "long", "float", "double",
    "void", "const", "_BYTE", "_WORD", "_DWORD", "_QWORD", "_UNKNOWN",
    "__int8", "__int16", "__int32", "__int64", "size_t", "wchar_t", "bool",
}

UNARY_PREFIX = {"*", "&", "~", "!"}
BINARY_MUL = {"*", "/", "%"}
OPERAND_END_KINDS = {"ident", "num", "float"}


class Tok(object):
    __slots__ = ("kind", "start", "end", "text")

    def __init__(self, kind, start, end, text):
        self.kind = kind
        self.start = start
        self.end = end
        self.text = text

    def __repr__(self):
        return "Tok(%s,%r)" % (self.kind, self.text)


def line_starts(text):
    starts = [0]
    idx = text.find("\n")
    while idx != -1:
        starts.append(idx + 1)
        idx = text.find("\n", idx + 1)
    return starts


def preproc_line_mask(text):
    """True per line when the line belongs to a preprocessor directive
    (including backslash continuations)."""
    lines = text.split("\n")
    mask = [False] * len(lines)
    cont = False
    for i, ln in enumerate(lines):
        if cont:
            mask[i] = True
            cont = ln.rstrip().endswith("\\")
            continue
        if ln.lstrip().startswith("#"):
            mask[i] = True
            cont = ln.rstrip().endswith("\\")
    return mask


def tokenize(text):
    """Tokenize code segments; strings/comments become kind='skip' tokens,
    tokens on preprocessor lines become kind='pp'."""
    starts = line_starts(text)
    mask = preproc_line_mask(text)
    toks = []
    pos = 0
    for is_code, seg in split_code_and_literals(text):
        if not is_code:
            if seg:
                toks.append(Tok("skip", pos, pos + len(seg), seg))
        else:
            for m in TOKEN_RE.finditer(seg):
                a = pos + m.start()
                li = bisect.bisect_right(starts, a) - 1
                kind = m.lastgroup
                if mask[li]:
                    kind = "pp"
                toks.append(Tok(kind, a, pos + m.end(), m.group()))
        pos += len(seg)
    return toks


def build_fn_map(text):
    """offset -> enclosing function name, via global_inventory.find_defs."""
    lines = text.split("\n")
    lines_nl = [ln + "\n" for ln in lines]
    defs = find_defs(lines_nl)
    starts = line_starts(text)
    fn_at = [None] * len(lines)
    for k, (name, start) in enumerate(defs):
        end = defs[k + 1][1] if k + 1 < len(defs) else len(lines)
        for ln in range(start, end):
            fn_at[ln] = name

    def lookup(offset):
        li = bisect.bisect_right(starts, offset) - 1
        return fn_at[li] if li < len(fn_at) else None

    def line_of(offset):
        return bisect.bisect_right(starts, offset) - 1  # 0-based

    def fn_range(offset):
        """(start_off, end_off) of the enclosing function body, or None."""
        li = line_of(offset)
        if li >= len(fn_at) or fn_at[li] is None:
            return None
        name = fn_at[li]
        lo = li
        while lo > 0 and fn_at[lo - 1] == name:
            lo -= 1
        hi = li
        while hi + 1 < len(fn_at) and fn_at[hi + 1] == name:
            hi += 1
        end_off = starts[hi + 1] if hi + 1 < len(starts) else len(text)
        return (starts[lo], end_off)

    return lookup, line_of, fn_range


def _prev(toks, i):
    j = i - 1
    while j >= 0 and toks[j].kind in ("skip", "pp"):
        j -= 1
    return j if j >= 0 else None


def _next(toks, i):
    j = i + 1
    while j < len(toks) and toks[j].kind in ("skip", "pp"):
        j += 1
    return j if j < len(toks) else None


def _match_back(toks, i, close, opn):
    """i indexes a closing bracket; return index of its opener or None."""
    depth = 0
    j = i
    while j is not None:
        t = toks[j].text
        if toks[j].kind == "op":
            if t == close:
                depth += 1
            elif t == opn:
                depth -= 1
                if depth == 0:
                    return j
        j = _prev(toks, j)
    return None


def _match_fwd(toks, i, opn, close):
    depth = 0
    j = i
    while j is not None:
        t = toks[j].text
        if toks[j].kind == "op":
            if t == opn:
                depth += 1
            elif t == close:
                depth -= 1
                if depth == 0:
                    return j
        j = _next(toks, j)
    return None


def _is_cast_group(toks, open_idx, close_idx):
    """(unsigned __int16 *) style: only type-ish idents and '*' inside."""
    saw = False
    j = _next(toks, open_idx)
    while j is not None and j < close_idx:
        t = toks[j]
        if t.kind == "ident":
            if t.text not in CAST_TYPE_WORDS and not t.text.startswith("__"):
                return False
            saw = True
        elif t.kind == "op" and t.text == "*":
            pass
        else:
            return False
        j = _next(toks, j)
    return saw


def _ends_operand(tok):
    return tok is not None and (
        tok.kind in OPERAND_END_KINDS or (tok.kind == "op" and tok.text in (")", "]"))
    )


def consume_operand_left(toks, i):
    """i = index of the LAST token of an operand; return its first index,
    or None when the shape is unsupported/unsafe."""
    t = toks[i]
    if t.kind in OPERAND_END_KINDS:
        j = i
    elif t.kind == "op" and t.text == ")":
        j = _match_back(toks, i, ")", "(")
        if j is None:
            return None
        p = _prev(toks, j)
        if p is not None and toks[p].kind == "ident":
            j = p  # call: f(...)
    elif t.kind == "op" and t.text == "]":
        j = _match_back(toks, i, "]", "[")
        if j is None:
            return None
        p = _prev(toks, j)
        if p is None or not _ends_operand(toks[p]):
            return None
        j = consume_operand_left(toks, p)
        if j is None:
            return None
    else:
        return None
    # member chains: a.b / a->b to the left of the primary
    while True:
        p = _prev(toks, j)
        if p is not None and toks[p].kind == "op" and toks[p].text in (".", "->"):
            q = _prev(toks, p)
            if q is not None and _ends_operand(toks[q]):
                j2 = consume_operand_left(toks, q)
                if j2 is None:
                    return None
                j = j2
                continue
        break
    # prefix operators: derefs, address-of, casts
    while True:
        p = _prev(toks, j)
        if p is None:
            break
        pt = toks[p]
        if pt.kind == "op" and pt.text in UNARY_PREFIX:
            q = _prev(toks, p)
            if pt.text == "*" and _ends_operand(toks[q] if q is not None else None):
                break  # binary multiplication, not a deref
            j = p
            continue
        if pt.kind == "op" and pt.text == ")":
            o = _match_back(toks, p, ")", "(")
            if o is not None and _is_cast_group(toks, o, p):
                j = o
                continue
        break
    return j


def consume_operand_right(toks, i):
    """i = index of the FIRST token of an operand; return its last index,
    or None when the shape is unsupported/unsafe."""
    n = len(toks)
    j = i
    # prefix operators / casts
    while j is not None and j < n:
        t = toks[j]
        if t.kind == "op" and t.text in UNARY_PREFIX:
            j = _next(toks, j)
            continue
        if t.kind == "op" and t.text == "(":
            c = _match_fwd(toks, j, "(", ")")
            if c is not None and _is_cast_group(toks, j, c):
                j = _next(toks, c)
                continue
        break
    if j is None or j >= n:
        return None
    t = toks[j]
    if t.kind in OPERAND_END_KINDS:
        e = j
    elif t.kind == "op" and t.text == "(":
        e = _match_fwd(toks, j, "(", ")")
        if e is None:
            return None
    else:
        return None
    # postfix: calls, subscripts, member chains
    while True:
        nx = _next(toks, e)
        if nx is None:
            break
        xt = toks[nx]
        if xt.kind == "op" and xt.text == "(" and toks[e].kind == "ident":
            c = _match_fwd(toks, nx, "(", ")")
            if c is None:
                return None
            e = c
            continue
        if xt.kind == "op" and xt.text == "[":
            c = _match_fwd(toks, nx, "[", "]")
            if c is None:
                return None
            e = c
            continue
        if xt.kind == "op" and xt.text in (".", "->"):
            m = _next(toks, nx)
            if m is not None and toks[m].kind == "ident":
                e = m
                continue
            return None
        break
    return e


def _consume_term_left(toks, end_idx):
    """Consume operand + its multiplicative chain leftwards; return start."""
    s = consume_operand_left(toks, end_idx)
    if s is None:
        return None
    while True:
        p = _prev(toks, s)
        if p is not None and toks[p].kind == "op" and toks[p].text in BINARY_MUL:
            q = _prev(toks, p)
            if q is None or not _ends_operand(toks[q]):
                return None
            s2 = consume_operand_left(toks, q)
            if s2 is None:
                return None
            s = s2
            continue
        break
    return s


def _consume_term_right(toks, start_idx):
    s = consume_operand_right(toks, start_idx)
    if s is None:
        return None
    while True:
        nx = _next(toks, s)
        if nx is not None and toks[nx].kind == "op" and toks[nx].text in BINARY_MUL:
            m = _next(toks, nx)
            if m is None:
                return None
            e2 = consume_operand_right(toks, m)
            if e2 is None:
                return None
            s = e2
            continue
        break
    return s


class Span(object):
    def __init__(self):
        self.terms = []          # list of (start_tok_idx, end_tok_idx)
        self.lit_term = -1       # index into terms of the literal's term
        self.left_boundary = ""  # token text (or "BOF")
        self.right_boundary = ""
        self.unsafe = False
        self.reason = ""


def additive_span(toks, li):
    """Maximal additive expression around the literal token at index li."""
    span = Span()
    # the literal's own term (multiplicative chain both directions)
    s = li
    e = li
    while True:
        p = _prev(toks, s)
        if p is not None and toks[p].kind == "op" and toks[p].text in BINARY_MUL:
            q = _prev(toks, p)
            if q is None or not _ends_operand(toks[q]):
                # unary '*' deref cannot precede a literal; treat as boundary
                break
            s2 = consume_operand_left(toks, q)
            if s2 is None:
                span.unsafe, span.reason = True, "unparsed-left-operand"
                return span
            s = s2
            continue
        break
    while True:
        nx = _next(toks, e)
        if nx is not None and toks[nx].kind == "op" and toks[nx].text in BINARY_MUL:
            m = _next(toks, nx)
            if m is None:
                span.unsafe, span.reason = True, "eof-in-term"
                return span
            e2 = consume_operand_right(toks, m)
            if e2 is None:
                span.unsafe, span.reason = True, "unparsed-right-operand"
                return span
            e = e2
            continue
        break
    terms = [(s, e)]
    # walk additive siblings to the left
    cur = s
    while True:
        p = _prev(toks, cur)
        if p is None:
            span.left_boundary = "BOF"
            break
        pt = toks[p]
        if pt.kind == "op" and pt.text == "+":
            q = _prev(toks, p)
            if q is None or not _ends_operand(toks[q]):
                # unary plus
                span.unsafe, span.reason = True, "unary-plus"
                return span
            ts = _consume_term_left(toks, q)
            if ts is None:
                span.unsafe, span.reason = True, "unparsed-left-term"
                return span
            terms.insert(0, (ts, q))
            cur = ts
            continue
        if pt.kind == "op" and pt.text in ("-", "++", "--"):
            span.unsafe, span.reason = True, "minus-or-incdec-left"
            return span
        span.left_boundary = pt.text
        break
    lit_term_idx = len(terms) - 1
    # walk additive siblings to the right
    cur = e
    while True:
        nx = _next(toks, cur)
        if nx is None:
            span.right_boundary = "EOF"
            break
        xt = toks[nx]
        if xt.kind == "op" and xt.text == "+":
            m = _next(toks, nx)
            if m is None:
                span.unsafe, span.reason = True, "eof-after-plus"
                return span
            te = _consume_term_right(toks, m)
            if te is None:
                span.unsafe, span.reason = True, "unparsed-right-term"
                return span
            terms.append((m, te))
            cur = te
            continue
        if xt.kind == "op" and xt.text in ("-", "++", "--"):
            span.unsafe, span.reason = True, "minus-or-incdec-right"
            return span
        span.right_boundary = xt.text
        break
    span.terms = terms
    span.lit_term = lit_term_idx
    return span


def enclosing_call(toks, li, limit=400):
    """Name of the function whose argument list encloses token li, or None."""
    depth = 0
    j = li
    steps = 0
    while j is not None and steps < limit:
        j = _prev(toks, j)
        steps += 1
        if j is None:
            return None
        t = toks[j]
        if t.kind != "op":
            continue
        if t.text in (")", "]"):
            depth += 1
        elif t.text == "]":
            depth += 1
        elif t.text == "[":
            depth -= 1
        elif t.text == "(":
            if depth == 0:
                p = _prev(toks, j)
                if p is not None and toks[p].kind == "ident":
                    return toks[p].text
                return None
            depth -= 1
        elif t.text in (";", "{", "}"):
            return None
    return None


def group_idents_and_values(toks, span):
    idents = set()
    values = set()
    for (s, e) in span.terms:
        j = s
        while j is not None and j <= e:
            t = toks[j]
            if t.kind == "ident":
                idents.add(t.text)
            elif t.kind == "num":
                values.add(parse_num(t.text))
            j = _next(toks, j)
            if j is not None and j > e:
                break
    return idents, values


def parse_num(raw):
    body = raw.rstrip("uUlL")
    return int(body, 16) if body.lower().startswith("0x") else int(body)


def span_text(text, toks, span):
    s = toks[span.terms[0][0]].start
    e = toks[span.terms[-1][1]].end
    return re.sub(r"\s+", " ", text[s:e]).strip()


def classify_site(text, toks, li, entry, family_names):
    """Classify the numeric token at index li against a manifest entry.
    Returns (cls, info dict)."""
    span = additive_span(toks, li)
    info = {"span": None, "callee": None, "boundaries": None, "reason": span.reason}
    if span.unsafe:
        return "unsafe", info
    info["span"] = span_text(text, toks, span)
    info["boundaries"] = (span.left_boundary, span.right_boundary)
    idents, values = group_idents_and_values(toks, span)
    values.discard(entry["value"])
    if set(entry.get("forbid_anchors", ())) & idents:
        return "forbidden", info
    lit_s, lit_e = span.terms[span.lit_term]
    mul = lit_s != lit_e
    anchored = bool(set(entry.get("anchors", ())) & idents)
    cooccur = bool(set(entry.get("cooccur_values", ())) & values) or bool(
        family_names & idents
    )
    info["anchored"] = anchored
    info["cooccur"] = cooccur
    if mul and anchored:
        return "mul_adjacent_anchored", info
    if mul:
        return "mul_adjacent", info
    if anchored:
        return "additive_anchored", info
    single = len(span.terms) == 1 and lit_s == lit_e
    if single and span.left_boundary in ("(", ",") and span.right_boundary in (")", ","):
        callee = enclosing_call(toks, li)
        info["callee"] = callee
        if callee in CALL_ARG_WHITELIST:
            return "call_arg", info
    if single and span.left_boundary == "+=" and span.right_boundary in (";", ")"):
        return "increment_rhs", info
    return "bare", info


# Classes a rule may auto-apply, by manifest tier. Tier-3 additionally
# requires anchored-or-cooccur (checked in eligibility below).
TIER_CLASSES = {
    1: {"mul_adjacent", "mul_adjacent_anchored", "additive_anchored",
        "increment_rhs", "call_arg"},
    3: {"mul_adjacent", "mul_adjacent_anchored", "additive_anchored"},
}


def eligible(cls, info, entry):
    if entry.get("deferred"):
        return False
    tier = entry.get("tier", 3)
    if cls not in TIER_CLASSES.get(tier, set()):
        return False
    if tier == 3 and not info.get("cooccur"):
        return False
    return True


def load_manifest(path=None):
    path = path or os.path.join(REPO, MANIFEST_REL)
    with open(path) as f:
        data = json.load(f)
    entries = data["constants"]
    families = {}
    for e in entries:
        families.setdefault(e.get("family", ""), set()).add(e["name"])
    return entries, families


DEFINE_RE = re.compile(
    r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_][A-Za-z0-9_]*)(\([^)]*\))?[ \t]+(.*?)[ \t]*$"
)


def parse_prelude_macros(path=None):
    """name -> {'params': str|None, 'body': str} for prelude #defines."""
    path = path or os.path.join(REPO, PRELUDE_REL)
    with open(path, errors="replace") as f:
        raw = f.read()
    macros = {}
    lines = raw.split("\n")
    i = 0
    while i < len(lines):
        ln = lines[i]
        full = ln
        while full.rstrip().endswith("\\") and i + 1 < len(lines):
            i += 1
            full = full.rstrip()[:-1] + " " + lines[i]
        m = DEFINE_RE.match(full)
        if m:
            body = full[m.end(2) if m.group(2) else m.end(1):].strip()
            macros[m.group(1)] = {"params": m.group(2), "body": body}
        i += 1
    return macros


ENUM_HEAD_RE = re.compile(r"\benum\b(?:\s+[A-Za-z_]\w*)?\s*\{")


def parse_prelude_enums(path=None):
    """Parse `enum {...}` / `typedef enum X {...} X;` blocks in the prelude.
    Returns name -> value for every enumerator (explicit `= value` or the
    implicit previous+1, starting at 0). Only decimal/hex integer initializers
    are resolved; a member with an unparseable initializer stops that block."""
    path = path or os.path.join(REPO, PRELUDE_REL)
    with open(path, errors="replace") as f:
        raw = f.read()
    # strip block comments so `/* ... */` inside an enum body is ignored
    text = re.sub(r"/\*.*?\*/", " ", raw, flags=re.DOTALL)
    members = {}
    for hm in ENUM_HEAD_RE.finditer(text):
        # find the matching close brace of this enum body
        depth = 0
        j = text.index("{", hm.start())
        k = j
        while k < len(text):
            if text[k] == "{":
                depth += 1
            elif text[k] == "}":
                depth -= 1
                if depth == 0:
                    break
            k += 1
        body = text[j + 1:k]
        # drop // comments per line, then split on commas
        body = re.sub(r"//[^\n]*", " ", body)
        nxt = 0
        for part in body.split(","):
            part = part.strip()
            if not part:
                continue
            mm = re.match(r"([A-Za-z_]\w*)\s*(?:=\s*(.+))?$", part)
            if not mm:
                break
            name = mm.group(1)
            if mm.group(2) is not None:
                vm = re.fullmatch(r"(0[xX][0-9A-Fa-f]+|[0-9]+)[uUlL]*",
                                  mm.group(2).strip())
                if not vm:
                    break  # non-literal initializer; stop this block
                nxt = parse_num(vm.group(1))
            members[name] = nxt
            nxt += 1
    return members


def numeric_macro_value(macro):
    """Numeric value of a single-token object-like macro body, else None."""
    if macro["params"] is not None:
        return None
    body = macro["body"].strip("() \t")
    m = re.fullmatch(r"(0[xX][0-9A-Fa-f]+|[0-9]+)[uUlL]{0,3}", body)
    if not m:
        return None
    return parse_num(m.group(0))


def iter_literal_sites(text, wanted_values=None):
    """Yield (tok_index, value) over 'num' tokens (code only, no preproc)."""
    toks = tokenize(text)
    out = []
    for i, t in enumerate(toks):
        if t.kind != "num":
            continue
        v = parse_num(t.text)
        if wanted_values is not None and v not in wanted_values:
            continue
        out.append((i, v))
    return toks, out


# ---------------------------------------------------------------------------

SELFTEST_CASES = [
    # (code, value, expected_class, entry_overrides)
    ("x = *(__int16 *)(gameData + 725 * a1 + 147174);", 725,
     "mul_adjacent_anchored", {}),
    ("x = *(__int16 *)(gameData + 725 * a1 + 147174);", 147174,
     "additive_anchored", {}),
    ("qmemcpy((void *)(725 * g_SelectedUnitIndex + gameData + 147174 + 316), p, 0x194u);",
     316, "additive_anchored", {"cooccur_values": [725, 147174]}),
    ("qmemcpy((void *)(725 * i + gameData + 147174 + 316), p, 0x194u);",
     404, "call_arg", {}),
    ("y = *(__int16 *)(31 * v5 + g_MapData + 852);", 31,
     "forbidden", {"forbid_anchors": ["g_MapData"]}),
    ("case 725:", 725, "bare", {}),
    ("rowOffset += 1400;", 1400, "increment_rhs", {}),
    ("for ( i = 1400 * v1; ; i += 1400 )", 1400, "mul_adjacent", {}),
    ("if (v3 == 147174)", 147174, "bare", {}),
    ("z = a - 725;", 725, "unsafe", {}),
    ("z = arr[725];", 725, "bare", {}),
    ("w = *(_DWORD *)(725 * g_SelectedUnitIndex + gameData + 147174 + 320);",
     320, "additive_anchored", {"cooccur_values": [725]}),
    ("v9 = 467 * idx + gameData + 509674;", 467, "mul_adjacent_anchored", {}),
    ("p = (char *)(v3 + 6 + 31 * v5);", 31,
     "mul_adjacent", {"cooccur_values": [6]}),
    ("f(716, 725);", 725, "bare", {}),
    ("s = \"case 725\";", 725, None, {}),          # inside a string: no token
    ("d = 725.0;", 725, None, {}),                  # float: no integer token
    ("sub_402725(1);", 725, None, {}),              # ident substring: no token
    ("#define UNIT_STACK_STRIDE 725", 725, None, {}),  # preproc: masked
]


def selftest():
    fails = 0
    for code, value, expected, overrides in SELFTEST_CASES:
        entry = {"value": value, "tier": 1, "anchors": ["gameData"],
                 "forbid_anchors": [], "cooccur_values": []}
        entry.update(overrides)
        toks, sites = iter_literal_sites(code, {value})
        got = None
        for (idx, v) in sites:
            got, _info = classify_site(code, toks, idx, entry, set())
            break
        ok = got == expected
        # cooccur expectations: recheck info for the cooccur cases
        if ok and expected in ("additive_anchored", "mul_adjacent") and \
                overrides.get("cooccur_values"):
            _cls, info = classify_site(code, toks, sites[0][0], entry, set())
            ok = info.get("cooccur") is True
        print("%s  %-24s -> %-22s (want %s)" % (
            "ok " if ok else "FAIL", repr(value), got, expected))
        if not ok:
            print("      code: %s" % code)
            fails += 1
    print("%d/%d passed" % (len(SELFTEST_CASES) - fails, len(SELFTEST_CASES)))
    return 1 if fails else 0


if __name__ == "__main__":
    if "--selftest" in sys.argv:
        sys.exit(selftest())
    print(__doc__)
