"""Consolidate all DOS name sources into one master {ea -> name} map with
provenance + confidence, resolving conflicts (evidence-based CLIPS names win over
stale existing labels; all conflicts logged for review)."""
import json, os
SCR = os.path.dirname(__file__)
REPO = r"C:\Users\andrz\git\clash-disassembly"

existing = {int(e['ea'],16): e for e in json.load(open(os.path.join(REPO,"tools/dos/dos_existing_names.json")))}
anchors  = {int(a['ea'],16): a for a in json.load(open(os.path.join(REPO,"tools/dos/dos_clips_anchors.json")))}
strmatch = json.load(open(os.path.join(SCR,"clips_string_matches.json")))
registered = {int(k,16):v for k,v in json.load(open(os.path.join(SCR,"dos_registered_groundtruth.json"))).items()}

def norm(n): return n[3:] if n.startswith('Env') and len(n)>3 and n[3].isupper() else n

master = {}   # ea -> {name, confidence, source, evidence}
conflicts = []
dropped_false = []

# 0. drop anchors/string-matches that contradict a REGISTERED ground-truth name (false positives)
for ea in list(anchors):
    if ea in registered and norm(anchors[ea]['name'])!=norm(registered[ea]) and registered[ea]!=anchors[ea]['name']:
        dropped_false.append({"ea":hex(ea),"registered":registered[ea],"dropped_anchor":anchors[ea]['name'],"kind":"errid"})
        del anchors[ea]
for ea_s in list(strmatch):
    ea=int(ea_s,16)
    if ea in registered and norm(strmatch[ea_s]['name'])!=norm(registered[ea]) and registered[ea]!=strmatch[ea_s]['name']:
        dropped_false.append({"ea":ea_s,"registered":registered[ea],"dropped_anchor":strmatch[ea_s]['name'],"kind":"string"})
        del strmatch[ea_s]

# 1. existing names (baseline, lowest precedence for CLIPS-region conflicts)
for ea,e in existing.items():
    master[ea] = {"name":e['name'], "confidence":e.get('confidence','high'),
                  "source":"existing", "evidence":e.get('evidence','in original clash.c')}

# 2. error-id anchors (high-confidence CLIPS evidence) — override stale existing on conflict
for ea,a in anchors.items():
    nm = a['name']
    if ea in master and norm(master[ea]['name']) != norm(nm) and master[ea]['source']=="existing":
        conflicts.append({"ea":hex(ea),"existing":master[ea]['name'],"clips":nm,"via":"errid-anchor"})
    master[ea] = {"name":nm,"confidence":"high","source":"clips-errid",
                  "evidence":a.get('evidence','')}

# 3. string-anchor matches (high-confidence) — override stale existing, must agree with errid anchor
for ea_s,info in strmatch.items():
    ea=int(ea_s,16); nm=norm(info['name'])
    if ea in master:
        cur=master[ea]
        if norm(cur['name'])==nm:
            continue  # agrees, keep
        if cur['source']=="clips-errid":
            # both CLIPS-evidence disagree -> should not happen; flag, keep errid
            conflicts.append({"ea":ea_s,"errid":cur['name'],"string":info['name'],"via":"str-vs-errid"})
            continue
        if cur['source']=="existing":
            conflicts.append({"ea":ea_s,"existing":cur['name'],"clips":info['name'],"via":"string-anchor"})
    master[ea]={"name":nm,"confidence":"high","source":"clips-string",
                "evidence":"unique shared literal: "+info['evidence'][:60]}

# coverage
CLIPS_LO,CLIPS_HI=0x89860,0xEB580
clips_named=sum(1 for ea in master if CLIPS_LO<=ea<CLIPS_HI)
by_src={}
for v in master.values(): by_src[v['source']]=by_src.get(v['source'],0)+1
print(f"master map total names: {len(master)}")
print(f"  by source: {by_src}")
print(f"  in CLIPS region [0x89860,0xEB580): {clips_named}")
print(f"conflicts logged (CLIPS evidence overrides stale hand-label): {len(conflicts)}")
for c in conflicts: print("   ",c)
print(f"FALSE anchors dropped (contradicted registered ground truth): {len(dropped_false)}")
for c in dropped_false: print("   ",c)
json.dump([{"ea":hex(ea),**v} for ea,v in sorted(master.items())],
          open(os.path.join(SCR,"dos_master_map.json"),"w"), indent=1)
json.dump(conflicts, open(os.path.join(SCR,"dos_name_conflicts.json"),"w"), indent=1)
json.dump(dropped_false, open(os.path.join(SCR,"dos_dropped_false_anchors.json"),"w"), indent=1)
