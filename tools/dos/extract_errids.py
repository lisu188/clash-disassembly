import re, json, collections
src = r"C:\Users\andrz\git\clash-disassembly\clash.c"
lines = open(src, encoding='latin-1').readlines()
strpat = re.compile(r'^char (a[A-Za-z0-9_]+)\[\d+\] = "((?:[^"\\]|\\.)*)";')
strings = {}
for ln in lines:
    m = strpat.match(ln)
    if m:
        strings[m.group(1)] = m.group(2)
callpat = re.compile(r'sub_DA560\(\(int\)(a[A-Za-z0-9_]+), (\d+),')
inv = collections.defaultdict(set)
nsites = 0
for ln in lines:
    for m in callpat.finditer(ln):
        val = strings.get(m.group(1))
        if val:
            inv[val].add(int(m.group(2)))
            nsites += 1
inv = {k: sorted(v) for k, v in sorted(inv.items())}
json.dump(inv, open('dos_printerrorid_inventory.json', 'w'), indent=1)
print("PrintErrorID call sites:", nsites)
print("distinct modules:", len(inv))
print("distinct (module,id) pairs:", sum(len(v) for v in inv.values()))
for k in list(inv)[:14]:
    ids = inv[k]
    print(" ", k.ljust(10), "ids", ids[:14], "..." if len(ids) > 14 else "")
