"""CLIPS cross-reference engine for the DOS binary.

1. Version-pin: score DOS PrintErrorID (module,id) fingerprint vs each CLIPS ref tree.
2. Build (module,id) -> CLIPS source function name from the ref tree (definitive when
   the pair occurs in exactly one CLIPS function).
3. Join with the DOS side: each DOS function that emits sub_DA560((int)aModule, id)
   -> proposed CLIPS name.  Definitive when the (module,id) is unique in BOTH the
   source (one CLIPS fn) and the DOS binary (one DOS fn)."""
import re, json, os, glob, collections

SCR = r"C:\Users\andrz\AppData\Local\Temp\claude\C--Users-andrz-git-clash-disassembly\d39f28bf-ad2c-497f-ab63-cd555e5653d7\scratchpad"
DOS_C = r"C:\Users\andrz\git\clash-disassembly\clash.c"

# ---- source side: map (module,id) -> set(clips function names), per version ----
FUNC_DEF = re.compile(r'^(?:globle\s+|static\s+|)[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)\s*\([^;]*$')
ERRID = re.compile(r'(?:Print|Divide|Print)?ErrorID\s*\(\s*(?:[A-Za-z_]\w*\s*,\s*)?"([A-Z0-9]+)"\s*,\s*(\d+)')

def source_pairs(root):
    """Return (all_pairs, pair->set(funcnames)) by scanning each .c file's functions."""
    pair_fns = collections.defaultdict(set)
    all_pairs = set()
    for path in glob.glob(os.path.join(root, "**", "*.c"), recursive=True):
        lines = open(path, encoding="latin-1", errors="replace").read().splitlines()
        cur = None; depth = 0; started = False
        for ln in lines:
            # crude function tracking: a def line at column 0 whose next real char isn't ';'
            m = FUNC_DEF.match(ln)
            if m and depth == 0 and not ln.rstrip().endswith(';') and '(' in ln:
                cur = m.group(1); started = False
            depth += ln.count('{') - ln.count('}')
            if '{' in ln: started = True
            for em in ERRID.finditer(ln):
                key = (em.group(1), int(em.group(2)))
                all_pairs.add(key)
                if cur:
                    pair_fns[key].add(cur)
    return all_pairs, pair_fns

# ---- DOS side ----
def dos_side():
    lines = open(DOS_C, encoding="latin-1").readlines()
    strpat = re.compile(r'^char (a[A-Za-z0-9_]+)\[\d+\] = "((?:[^"\\]|\\.)*)";')
    strings = {}
    for ln in lines:
        m = strpat.match(ln)
        if m: strings[m.group(1)] = m.group(2)
    # function ranges
    sep = re.compile(r'^//----- \(([0-9A-Fa-f]{8})\) -')
    funcs = []
    for i, ln in enumerate(lines):
        m = sep.match(ln)
        if m: funcs.append((i, int(m.group(1), 16)))
    def encl(i):
        lo, hi = 0, len(funcs)-1; ans=None
        for k,(li,addr) in enumerate(funcs):
            nxt = funcs[k+1][0] if k+1<len(funcs) else len(lines)
            if li <= i < nxt: return addr
        return None
    call = re.compile(r'sub_DA560\(\(int\)(a[A-Za-z0-9_]+), (\d+),')
    pair_dosfn = collections.defaultdict(set)
    for i, ln in enumerate(lines):
        for m in call.finditer(ln):
            val = strings.get(m.group(1))
            if val:
                a = encl(i)
                if a is not None:
                    pair_dosfn[(val, int(m.group(2)))].add(a)
    return pair_dosfn

def main():
    dos_pd = dos_side()
    dos_pairs = set(dos_pd)
    print("DOS (module,id) pairs:", len(dos_pairs))
    best=None
    results={}
    for ver, root in [("6.24", r"C:\Clash\ref\clips\624"), ("6.30", r"C:\Clash\ref\clips\630")]:
        sp, pf = source_pairs(root)
        inter = dos_pairs & sp
        results[ver]=(sp,pf)
        print(f"CLIPS {ver}: source pairs={len(sp)}  DOS matched={len(inter)}/{len(dos_pairs)} ({100*len(inter)/len(dos_pairs):.1f}%)")
    # Use 6.24 (closer to 6.0 era) as primary; build definitive anchors
    sp, pf = results["6.24"]
    anchors=[]
    for pair, dosfns in dos_pd.items():
        clips_fns = pf.get(pair, set())
        if len(dosfns)==1 and len(clips_fns)==1:
            anchors.append({"ea":hex(next(iter(dosfns))),
                            "module":pair[0],"id":pair[1],
                            "clips_fn":next(iter(clips_fns))})
    # dedupe: a DOS fn may emit several unique ids -> collapse, must agree
    byea=collections.defaultdict(set)
    for a in anchors: byea[a["ea"]].add(a["clips_fn"])
    clean=[{"ea":ea,"clips_fn":next(iter(v))} for ea,v in byea.items() if len(v)==1]
    conflict={ea:sorted(v) for ea,v in byea.items() if len(v)>1}
    json.dump(clean, open(os.path.join(SCR,"clips_definitive_anchors.json"),"w"), indent=1)
    print(f"\nDefinitive anchors (unique pair both sides, DOS fn agrees): {len(clean)}")
    print(f"conflicting DOS fns (emit ids from >1 CLIPS fn): {len(conflict)} {list(conflict.items())[:3]}")
    for a in clean[:15]:
        print(f"  {a['ea']} -> {a['clips_fn']}")

main()
