"""Anchor-bounded segment alignment. Between two consecutive anchors in the SAME
CLIPS source file, DOS functions (by ea) align in order to CLIPS source functions
(by order_index). Where the gap has equal counts on both sides, propose the 1:1
order-locked alignment; upgrade to high confidence when a shared string or a named
callee corroborates."""
import re, json, os, collections

REPO = r"C:\Users\andrz\git\clash-disassembly"
SCR  = os.path.dirname(__file__)
DOS_C = os.path.join(REPO, "clash.c")
CLIPS_LO, CLIPS_HI = 0x89860, 0xEB580

model = json.load(open(os.path.join(SCR, "clips_source_model.json")))
# name -> list of (file, order); many statics share names, so keep all
name_locs = collections.defaultdict(list)
for fname, funcs in model.items():
    for f in funcs:
        name_locs[f["name"]].append((fname, f["order"]))
def norm(n): return n[3:] if n.startswith('Env') and len(n)>3 and n[3].isupper() else n

# ---- DOS side: ordered functions in CLIPS region with name, strings, callees ----
lines = open(DOS_C, encoding='latin-1').readlines()
strpat = re.compile(r'^(?:const )?char (a[A-Za-z0-9_]+)\[\d+\] = "((?:[^"\\]|\\.)*)";')
sym2lit = {m.group(1):m.group(2) for ln in lines for m in [strpat.match(ln)] if m}
sep = re.compile(r'^//----- \(([0-9A-Fa-f]{8})\) -')
seps = [(i,int(m.group(1),16)) for i,ln in enumerate(lines) for m in [sep.match(ln)] if m]
def fname_of(sig):
    p=sig.find('(');
    if p<0: return None
    ids=re.findall(r'[A-Za-z_]\w*', re.sub(r'@<[^>]*>','',sig[:p]))
    return ids[-1] if ids else None
name_addr={}
dos=[]  # ordered list of {ea, name, strings:set, callee_names:set}
symref=re.compile(r'\b(a[A-Za-z0-9_]+)\b')
callref=re.compile(r'\b([A-Za-z_]\w*)\(')
for k,(li,ea) in enumerate(seps):
    j=li+1
    while j<len(lines) and lines[j].strip()=='': j+=1
    nm=fname_of(lines[j]); name_addr[nm]=ea
    nxt=seps[k+1][0] if k+1<len(seps) else len(lines)
    strs=set(); calls=set()
    for i in range(li+1,nxt):
        for m in symref.finditer(lines[i]):
            lit=sym2lit.get(m.group(1))
            if lit: strs.add(lit)
        for m in callref.finditer(lines[i]):
            calls.add(m.group(1))
    if CLIPS_LO<=ea<CLIPS_HI:
        dos.append({"ea":ea,"name":nm,"strings":strs,"calls":calls})
dos.sort(key=lambda d:d["ea"])

# ---- anchors: ea -> clips fn name, resolve to (file, order) ----
anchors_raw = {int(a['ea'],16):a['name'] for a in json.load(open(os.path.join(REPO,"tools/dos/dos_clips_anchors.json")))}
strm = {int(k,16):v['name'] for k,v in json.load(open(os.path.join(SCR,"clips_string_matches.json"))).items()}
master = {int(x['ea'],16):x['name'] for x in json.load(open(os.path.join(REPO,"tools/dos/dos_master_map.json")))}
registered = {int(k,16):v for k,v in json.load(open(os.path.join(SCR,"dos_registered_groundtruth.json"))).items()}

anchor_loc={}   # ea -> (file, order, name)  for anchors whose clips name is in exactly one file
for ea,nm in {**anchors_raw, **strm}.items():
    locs=name_locs.get(nm) or name_locs.get('Env'+nm)
    if locs and len(set(f for f,_ in locs))==1:
        f,o=locs[0]
        anchor_loc[ea]=(f,o,nm)

anchor_eas=sorted(anchor_loc)
proposals=[]; residual_segments=0; aligned_segments=0
for i in range(len(anchor_eas)-1):
    ea_a, ea_b = anchor_eas[i], anchor_eas[i+1]
    fa,oa,_ = anchor_loc[ea_a]; fb,ob,_ = anchor_loc[ea_b]
    if fa!=fb or ob<=oa+1:   # same file, real gap in source order
        continue
    # DOS funcs strictly between
    dgap=[d for d in dos if ea_a<d["ea"]<ea_b and (d["ea"] not in master)]  # only unnamed
    dgap_all=[d for d in dos if ea_a<d["ea"]<ea_b]
    # CLIPS funcs strictly between oa and ob in file fa
    cgap=[f for f in model[fa] if oa<f["order"]<ob]
    # require equal counts on the FULL gap (named+unnamed) vs source gap for order-lock
    if len(dgap_all)!=len(cgap) or not cgap:
        residual_segments+=1
        continue
    aligned_segments+=1
    for d,c in zip(dgap_all, cgap):
        if d["ea"] in master:   # already named; skip (but position consumed)
            continue
        nm=norm(c["name"])
        if not re.fullmatch(r'[A-Za-z_]\w*',nm): continue
        if d["ea"] in registered: continue
        # corroboration
        shared_str=[s for s in d["strings"] if s in set(c["strings"]) and len(s)>=5]
        named_callee_agree=[cn for cn in d["calls"] if cn in set(c["callees"])]
        conf="high" if (shared_str or len(named_callee_agree)>=2) else "medium"
        ev = ("shared string: "+shared_str[0][:50]) if shared_str else \
             ("callee agree: "+",".join(named_callee_agree[:3])) if named_callee_agree else \
             f"order-locked in {fa} (seg {oa}->{ob}, {len(cgap)} fns)"
        proposals.append({"ea":hex(d["ea"]),"name":nm,"clips_file":fa,
                          "confidence":conf,"evidence":ev,"source":"clips-align"})

# dedupe: one ea, and no name collision with existing master
seen=set(); final=[]
mnames={norm(v) for v in master.values()}
for p in proposals:
    if p["ea"] in seen: continue
    seen.add(p["ea"]); final.append(p)
by_conf=collections.Counter(p["confidence"] for p in final)
print(f"DOS CLIPS-region functions: {len(dos)}")
print(f"anchors resolved to a single file: {len(anchor_loc)}")
print(f"aligned (count-matched) segments: {aligned_segments}; residual segments: {residual_segments}")
print(f"NEW alignment proposals: {len(final)}  by confidence: {dict(by_conf)}")
json.dump(final, open(os.path.join(SCR,"clips_align_proposals.json"),"w"), indent=1)
for p in final[:20]: print(f"  {p['ea']} -> {p['name']:32} [{p['confidence']}] {p['evidence'][:45]}")
