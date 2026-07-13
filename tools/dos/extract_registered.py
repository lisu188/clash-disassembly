"""Extract the DefineFunction2/registerClipsCallback ground-truth set: the address
and registered C-name of every function the binary registers by name. These are the
highest-precedence names and are used to audit error-id/string anchors for
version-skew false positives."""
import re, json, os
DOS_C = r"C:\Users\andrz\git\clash-disassembly\clash.c"
lines = open(DOS_C, encoding='latin-1').readlines()

# name -> definition address (from //----- (ADDR) marker + next signature line)
sep = re.compile(r'^//----- \(([0-9A-Fa-f]{8})\) -')
name_addr = {}
for i,ln in enumerate(lines):
    m = sep.match(ln)
    if not m: continue
    j=i+1
    while j<len(lines) and lines[j].strip()=='': j+=1
    sig=lines[j]; p=sig.find('(')
    if p<0: continue
    before=re.sub(r'@<[^>]*>','',sig[:p])
    ids=re.findall(r'[A-Za-z_]\w*',before)
    if ids: name_addr[ids[-1]] = int(m.group(1),16)

# string table for the actualName arg
strpat = re.compile(r'^(?:const )?char (a[A-Za-z0-9_]+)\[\d+\] = "((?:[^"\\]|\\.)*)";')
sym2lit = {m.group(1):m.group(2) for ln in lines for m in [strpat.match(ln)] if m}

# registerClipsCallback((int)aName, TYPE, (int)FUNC, (int)aCName, ...)
reg = re.compile(r'registerClipsCallback\(\(int\)(a[A-Za-z0-9_]+), *(-?\d+), *\(int\)([A-Za-z_]\w*), *\(int\)(a[A-Za-z0-9_]+)')
registered = {}   # ea -> cname
for ln in lines:
    for m in reg.finditer(ln):
        func = m.group(3); cname = sym2lit.get(m.group(4))
        ea = name_addr.get(func)
        if ea is not None and cname and re.fullmatch(r'[A-Za-z_]\w*', cname):
            registered[ea] = cname

json.dump({hex(k):v for k,v in registered.items()},
          open(os.path.join(os.path.dirname(__file__),"dos_registered_groundtruth.json"),"w"), indent=1)
print("registered ground-truth functions:", len(registered))

# audit: which error-id / string anchors conflict with a registered name?
def norm(n): return n[3:] if n.startswith('Env') and len(n)>3 and n[3].isupper() else n
anchors = {int(a['ea'],16):a['name'] for a in json.load(open(r"C:\Users\andrz\git\clash-disassembly\tools\dos\dos_clips_anchors.json"))}
strm = json.load(open(os.path.join(os.path.dirname(__file__),"clips_string_matches.json")))
false_errid=[]; false_str=[]
for ea,nm in anchors.items():
    if ea in registered and norm(nm)!=norm(registered[ea]) and registered[ea]!=nm:
        false_errid.append((hex(ea), registered[ea], nm))
for ea_s,info in strm.items():
    ea=int(ea_s,16)
    if ea in registered and norm(info['name'])!=norm(registered[ea]) and registered[ea]!=info['name']:
        false_str.append((ea_s, registered[ea], info['name']))
print(f"\nerror-id anchors contradicting a registered name (FALSE POSITIVES): {len(false_errid)}")
for x in false_errid: print("   ",x)
print(f"string anchors contradicting a registered name (FALSE POSITIVES): {len(false_str)}")
for x in false_str: print("   ",x)
