from pathlib import Path
import json
import shutil
import subprocess

source = Path('src/buildings/00425540_00426FC0_buildings_006.cpp')
manifest = Path('data/recovered_sources.json')
before = json.loads(manifest.read_text())
text = source.read_text()

old_decl = '''  int v6; // ecx\n  int v7; // edx\n  int v8; // ecx\n  int v9; // ecx\n  int unitStackRecordBase; // esi\n'''
new_decl = '''  int v6; // ecx\n  int unitStackRecordBase; // esi\n'''
if text.count(old_decl) != 1:
    raise SystemExit('Road timing local declaration block mismatch')
text = text.replace(old_decl, new_decl)

old_first = 'if ( Time_Now(v8, v7) - ROAD_BUILD_MARKER_ANIMATION_INTERVAL_TICKS > (unsigned int)g_RoadBuildModeLastAnimationTick )'
new_first = 'if ( Time_Now(0, 0) - ROAD_BUILD_MARKER_ANIMATION_INTERVAL_TICKS > (unsigned int)g_RoadBuildModeLastAnimationTick )'
if text.count(old_first) != 1:
    raise SystemExit('first Time_Now call mismatch')
text = text.replace(old_first, new_first)

old_second = 'g_RoadBuildModeLastAnimationTick = Time_Now(v9, g_RoadBuildModeLastAnimationTick);'
new_second = 'g_RoadBuildModeLastAnimationTick = Time_Now(0, 0);'
if text.count(old_second) != 1:
    raise SystemExit('second Time_Now call mismatch')
text = text.replace(old_second, new_second)

for line in [
    "// 4255E9: variable 'v8' is possibly undefined\n",
    "// 4255E9: variable 'v7' is possibly undefined\n",
    "// 4255FF: variable 'v9' is possibly undefined\n",
]:
    if text.count(line) != 1:
        raise SystemExit(f'missing stale diagnostic: {line.strip()}')
    text = text.replace(line, '')
source.write_text(text)

shutil.copyfile('../preparation/.diagnostics/test_road_mode_timing.py', 'tests/tools/test_road_mode_timing.py')
shutil.copyfile('../preparation/.diagnostics/ROAD_MODE_TIMING_RECOVERY.md', 'docs/ROAD_MODE_TIMING_RECOVERY.md')

status = Path('docs/STATUS.md')
s = status.read_text()
anchor = 'Last consolidated: 2026-09-07.\n\n'
section = '''## Road Build-Mode Timing Register Cleanup\n\nTrack: Win95 reconstruction, reached mission-05 Road mode. The marker-animation\nloop in `Builder_StartRoadBuildMode` now calls `Time_Now(0, 0)` at both original\ntimestamp sites instead of passing three undefined decompiler temporaries. The\nprotected Road procedure performs both calls without setting argument registers,\nand the protected `Time_Now` implementation saves/restores incoming ECX/EDX but\noverwrites them before computing its timestamp, so these values are not inputs.\nOnly this function's current manifest hash changes; all 4157 identities and\nfrozen baselines remain. Evidence: [ROAD_MODE_TIMING_RECOVERY.md](ROAD_MODE_TIMING_RECOVERY.md).\nNo campaign milestone advances; normal turn-7 refresh and Road continuation remain next.\n\n'''
if anchor not in s:
    raise SystemExit('STATUS anchor missing')
status.write_text(s.replace(anchor, anchor + section, 1))

subprocess.run(['python3', 'tools/update_split_manifest_hashes.py', '--update'], check=True)
after = json.loads(manifest.read_text())
changed = [o['name'] for o,n in zip(before['functions'], after['functions'], strict=True)
           if o.get('body_sha256') != n.get('body_sha256')]
assert changed == ['Builder_StartRoadBuildMode'], changed
for o,n in zip(before['functions'], after['functions'], strict=True):
    if o['name'] == 'Builder_StartRoadBuildMode':
        assert {k:v for k,v in o.items() if k != 'body_sha256'} == {k:v for k,v in n.items() if k != 'body_sha256'}
    else:
        assert o == n, o['name']
print('Changed current body hashes:', changed)
