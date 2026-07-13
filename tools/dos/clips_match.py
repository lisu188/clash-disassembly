"""String-anchor matcher: DOS clash.c function -> CLIPS 6.24 source function,
via string literals that are unique on BOTH sides (one DOS fn, one CLIPS fn).

Also runs the Stage-0 calibration: re-derive the known in-CLIPS-region existing
names blind (they are NOT used as input) and report agreement."""
import re, json, os, glob, collections

DOS_C   = r"C:\Users\andrz\git\clash-disassembly\clash.c"
CLIPS   = r"C:\Clash\ref\clips\624\CLIPSSrc\CLIPSSrc"
EXISTING= r"C:\Users\andrz\git\clash-disassembly\tools\dos\dos_existing_names.json"
CLIPS_LO, CLIPS_HI = 0x89860, 0xEB580

STR = re.compile(r'"((?:[^"\\]|\\.)*)"')

def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    text = re.sub(r'//[^\n]*', ' ', text)
    return text

# ---------- DOS side ----------
def dos_side():
    lines = open(DOS_C, encoding='latin-1').readlines()
    strpat = re.compile(r'^(?:const )?char (a[A-Za-z0-9_]+)\[\d+\] = "((?:[^"\\]|\\.)*)";')
    sym2lit = {}
    for ln in lines:
        m = strpat.match(ln)
        if m: sym2lit[m.group(1)] = m.group(2)
    # function ranges
    sep = re.compile(r'^//----- \(([0-9A-Fa-f]{8})\) -')
    seps = [(i, int(m.group(1),16)) for i,ln in enumerate(lines) for m in [sep.match(ln)] if m]
    func_strs = collections.defaultdict(set)   # ea -> set(literal)
    symref = re.compile(r'\b(a[A-Za-z0-9_]+)\b')
    for k,(li,ea) in enumerate(seps):
        nxt = seps[k+1][0] if k+1 < len(seps) else len(lines)
        for i in range(li+1, nxt):
            for m in symref.finditer(lines[i]):
                lit = sym2lit.get(m.group(1))
                if lit is not None:
                    func_strs[ea].add(lit)
    return func_strs, {ea for _,ea in seps}

# ---------- CLIPS source side ----------
DEF = re.compile(r'^(?:globle|static)\b[^\n;=]*?\b([A-Za-z_]\w*)\s*\(')
def clips_side():
    func_strs = collections.defaultdict(set)   # (file,name) -> set(literal)
    for path in glob.glob(os.path.join(CLIPS, "*.c")):
        fname = os.path.basename(path)
        raw = open(path, encoding='latin-1', errors='replace').read()
        raw = strip_comments(raw)
        lines = raw.splitlines()
        cur = None; depth = 0; opened = False
        for ln in lines:
            if depth == 0:
                m = DEF.match(ln)
                if m:
                    cur = (fname, m.group(1)); opened = False
            if cur:
                for sm in STR.finditer(ln):
                    func_strs[cur].add(sm.group(1))
            o = ln.count('{'); c = ln.count('}')
            if o: opened = True
            depth += o - c
            if opened and depth <= 0:
                cur = None; depth = 0; opened = False
    return func_strs

def main():
    dos_fs, dos_eas = dos_side()
    clips_fs = clips_side()
    print(f"DOS functions with >=1 string: {len(dos_fs)}")
    print(f"CLIPS source functions with >=1 string: {len(clips_fs)}")

    # inverted indices
    dos_by_str = collections.defaultdict(set)
    for ea, lits in dos_fs.items():
        for l in lits: dos_by_str[l].add(ea)
    clips_by_str = collections.defaultdict(set)
    for fn, lits in clips_fs.items():
        for l in lits: clips_by_str[l].add(fn)

    # unique-both-sides votes: ea -> Counter(clips_fn_name)
    votes = collections.defaultdict(collections.Counter)
    vote_evidence = collections.defaultdict(dict)
    for lit, eas in dos_by_str.items():
        cf = clips_by_str.get(lit)
        if not cf: continue
        if len(eas) == 1 and len(cf) == 1 and len(lit) >= 5:
            ea = next(iter(eas)); fn = next(iter(cf))
            votes[ea][fn[1]] += 1
            vote_evidence[ea].setdefault(fn[1], lit)

    matches = {}
    conflicts = {}
    for ea, c in votes.items():
        if len(c) == 1:
            name = next(iter(c))
            matches[ea] = (name, vote_evidence[ea][name])
        else:
            conflicts[ea] = dict(c)
    print(f"\nString-anchor matches (unique, agreeing): {len(matches)}")
    print(f"vote conflicts (ea votes multiple CLIPS fns): {len(conflicts)}")

    # ---- calibration against in-region existing names ----
    existing = {int(e['ea'],16): e['name'] for e in json.load(open(EXISTING))}
    in_region = {ea:nm for ea,nm in existing.items() if CLIPS_LO <= ea < CLIPS_HI}
    print(f"\nExisting names in CLIPS region (holdout): {len(in_region)}")
    # of those, how many did the blind matcher propose, and agree?
    def norm(n):  # strip Env prefix for comparison
        return n[3:] if n.startswith('Env') and len(n)>3 and n[3].isupper() else n
    scored = agree = contra = 0
    contra_list=[]
    for ea, known in in_region.items():
        if ea in matches:
            scored += 1
            prop = matches[ea][0]
            if norm(prop) == norm(known) or prop == known:
                agree += 1
            else:
                contra += 1
                contra_list.append((hex(ea), known, prop))
    print(f"  matcher proposed on holdout: {scored}/{len(in_region)}")
    print(f"  agreements: {agree}   contradictions: {contra}")
    if scored: print(f"  precision on holdout: {100*agree/scored:.1f}%")
    for c in contra_list[:15]: print("   CONTRA", c)

    json.dump({hex(k):{"name":v[0],"evidence":v[1]} for k,v in matches.items()},
              open(os.path.join(os.path.dirname(__file__),"clips_string_matches.json"),"w"), indent=1)

main()
