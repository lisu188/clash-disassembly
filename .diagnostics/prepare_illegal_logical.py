from pathlib import Path
import json
import shutil
import subprocess

p1 = Path('src/clips/0049CE10_0049E8D0_clips_005.cpp')
p2 = Path('src/clips/0049E930_0049FF80_clips_006.cpp')
manifest = Path('data/recovered_sources.json')
decl_path = Path('data/recovered_decls.json')
before = json.loads(manifest.read_text())

def replace_in_function(path, name, old, new):
    text = path.read_text()
    sig = text.index(name + '(')
    end = text.find('\n//----- (', sig)
    if end < 0:
        end = len(text)
    body = text[sig:end]
    if body.count(old) != 1:
        raise SystemExit(f'{name}: expected one {old!r}, got {body.count(old)}')
    path.write_text(text[:sig] + body.replace(old, new) + text[end:])

for path, fn, symbol in [
    (p1, 'Rules_HostPrintout', 'aPrintout'),
    (p1, 'Rules_HostRead', 'aRead'),
    (p1, 'Rules_HostOpen', 'aOpen'),
    (p1, 'Rules_HostClose', 'aClose'),
    (p2, 'Rules_HostFormat', 'aFormat'),
    (p2, 'Rules_HostReadline', 'aReadline'),
]:
    replace_in_function(path, fn, 'Rules_ReportIllegalLogicalName();',
                        f'Rules_ReportIllegalLogicalName((int)(intptr_t){symbol});')

old = '''signed int Rules_ReportIllegalLogicalName(void)\n{\n  int v0; // ecx\n  int v1; // ecx\n  int v2; // ecx\n\n  Rules_PrintErrorID((int)(intptr_t)aIofun, 1, 0);\n  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalLogical, v0);\n  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);\n  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_, v2);\n}\n// 49F330: variable 'v0' is possibly undefined\n// 49F33C: variable 'v1' is possibly undefined\n// 49F34B: variable 'v2' is possibly undefined\n'''
new = '''signed int Rules_ReportIllegalLogicalName(int functionName)\n{\n  Rules_PrintErrorID((int)(intptr_t)aIofun, 1, 0);\n  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalLogical, functionName);\n  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, functionName);\n  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_, functionName);\n}\n'''
text = p2.read_text()
if text.count(old) != 1:
    raise SystemExit('target body mismatch')
p2.write_text(text.replace(old, new))

decls = json.loads(decl_path.read_text())
rec = decls['functions']['Rules_ReportIllegalLogicalName']
old_decl = 'signed int Rules_ReportIllegalLogicalName(void);'
new_decl = 'signed int Rules_ReportIllegalLogicalName(int functionName);'
if rec.get('decl') != old_decl:
    raise SystemExit(f'unexpected canonical declaration: {rec.get("decl")!r}')
rec['decl'] = new_decl
decl_path.write_text(json.dumps(decls, indent=2) + '\n')
subprocess.run(['python3', 'tools/gen_subsystem_headers.py', '--write'], check=True)

shutil.copyfile('../preparation/.diagnostics/test_illegal_logical_name.py', 'tests/tools/test_illegal_logical_name.py')
shutil.copyfile('../preparation/.diagnostics/IO_LOGICAL_NAME_RECOVERY.md', 'docs/IO_LOGICAL_NAME_RECOVERY.md')

status = Path('docs/STATUS.md')
s = status.read_text()
anchor = 'Last consolidated: 2026-09-07.\n\n'
section = '''## Illegal Logical-Name Reporter\n\nTrack: Win95 reconstruction, reached CLIPS I/O error handling.\n`Rules_ReportIllegalLogicalName` now retains the function-name token supplied in\noriginal EAX and all six callers pass the exact `printout`, `read`, `open`,\n`close`, `format`, or `readline` identifier. The three undefined output values\nare removed while preserving fresh `werror` reads, message order and final\nreturn. Seven current body hashes change; all 4157 identities and frozen\nbaselines remain. Evidence and limits: [IO_LOGICAL_NAME_RECOVERY.md](IO_LOGICAL_NAME_RECOVERY.md).\nNo campaign milestone advances; mission-05 turn refresh and Road continuation\nremain the gameplay target.\n\n'''
if anchor not in s:
    raise SystemExit('status anchor missing')
status.write_text(s.replace(anchor, anchor + section, 1))

subprocess.run(['python3', 'tools/update_split_manifest_hashes.py', '--update'], check=True)
after = json.loads(manifest.read_text())
expected = {
    'Rules_HostPrintout', 'Rules_HostRead', 'Rules_HostOpen', 'Rules_HostClose',
    'Rules_HostFormat', 'Rules_HostReadline', 'Rules_ReportIllegalLogicalName'
}
changed = {o['name'] for o,n in zip(before['functions'], after['functions'], strict=True)
           if o.get('body_sha256') != n.get('body_sha256')}
assert changed == expected, (changed, expected)
for o,n in zip(before['functions'], after['functions'], strict=True):
    if o['name'] not in expected:
        assert o == n, o['name']
    else:
        assert {k:v for k,v in o.items() if k != 'body_sha256'} == {k:v for k,v in n.items() if k != 'body_sha256'}
print('Changed current body hashes:', sorted(changed))
print('Canonical declaration:', rec['decl'])
