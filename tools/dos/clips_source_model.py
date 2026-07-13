"""Ordered per-file CLIPS 6.24 source function model: name, order_index within file,
static/globle, string literals, callee names. Shared input for segment alignment."""
import re, os, glob, json, collections

CLIPS = r"C:\Clash\ref\clips\624\CLIPSSrc\CLIPSSrc"
STR = re.compile(r'"((?:[^"\\]|\\.)*)"')
DEF = re.compile(r'^(?:globle|static)\b[^\n;=]*?\b([A-Za-z_]\w*)\s*\(')
IDENT = re.compile(r'\b([A-Za-z_]\w*)\s*\(')

def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', ' ', t, flags=re.S)
    t = re.sub(r'//[^\n]*', ' ', t)
    return t

def build():
    model = {}   # file -> ordered list of {name, order, kind, strings[], callees[]}
    all_func_names = set()
    for path in sorted(glob.glob(os.path.join(CLIPS, "*.c"))):
        fname = os.path.basename(path)
        raw = strip_comments(open(path, encoding='latin-1', errors='replace').read())
        lines = raw.splitlines()
        funcs = []
        cur = None; depth = 0; opened = False
        for ln in lines:
            if depth == 0:
                m = DEF.match(ln)
                if m:
                    kind = 'static' if ln.lstrip().startswith('static') else 'globle'
                    cur = {"name": m.group(1), "order": len(funcs), "kind": kind,
                           "file": fname, "strings": set(), "callees": set()}
                    funcs.append(cur); opened = False
            if cur:
                for sm in STR.finditer(ln):
                    cur["strings"].add(sm.group(1))
                for im in IDENT.finditer(ln):
                    cur["callees"].add(im.group(1))
            o = ln.count('{'); c = ln.count('}')
            if o: opened = True
            depth += o - c
            if opened and depth <= 0:
                cur = None; depth = 0; opened = False
        for f in funcs:
            f["strings"] = sorted(f["strings"]); f["callees"] = sorted(f["callees"])
            all_func_names.add(f["name"])
        model[fname] = funcs
    return model, all_func_names

if __name__ == "__main__":
    model, names = build()
    tot = sum(len(v) for v in model.values())
    json.dump(model, open(os.path.join(os.path.dirname(__file__), "clips_source_model.json"), "w"))
    print(f"CLIPS files: {len(model)}, total functions: {tot}, distinct names: {len(names)}")
    # sanity: show a file
    for f in ["factmngr.c","retract.c","drive.c"]:
        if f in model: print(f"  {f}: {len(model[f])} functions, first: {[x['name'] for x in model[f][:5]]}")
