#!/usr/bin/env python3
"""Compile manifest-resolved visibility methods, adapters and frozen references.

Separate translation units preserve observable query boundaries for the fog
fixture. Linker wrappers record arguments and always call the actual query.
This focused gate writes only --output and contains no retail data.
"""
from pathlib import Path
import argparse,hashlib,json,os,re,shutil,subprocess,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent
NAMES=['Map_RevealTileWithPropagation','Map_IsTileVisibleToPlayer','Map_ClassifyFogOfWarOverlayForPlayer']
QUERY='_ZNK7clash958WorldMap25Map_IsTileVisibleToPlayerEiii'
EXPECTED={'reveal':'reveal cases=2034 lanes=3 recursive_order=exact complete_bytes=151552\n','fog':'fog cases=33792 lanes=3 actual_query_order=exact complete_bytes=151552\n','binding':'binding lanes=3 held_rebinding=exact callback_rebinding=exact constructor_destructor=pass complete_bytes=303104\n'}
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def resource_guard():
 if os.environ.get('CLASH95_WORLD_VISIBILITY_RESOURCE_GUARD')!='1':return {'resource_guard':'not_requested'}
 host=shutil.disk_usage('/mnt/c' if Path('/mnt/c').is_dir() else HERE).free
 available=int(next(line.split()[1] for line in Path('/proc/meminfo').read_text().splitlines() if line.startswith('MemAvailable:')))*1024
 snapshot={'host_free':host,'mem_available':available,'shm_free':shutil.disk_usage('/dev/shm').free}
 assert host>=12*1024**3 and available>=8*1024**3 and snapshot['shm_free']>=2*1024**3,('visibility resource hold',snapshot)
 return snapshot
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--kind',choices=['all',*EXPECTED],default='all');p.add_argument('--compiler',action='append');p.add_argument('--optimization',action='append',choices=['O0','O2']);p.add_argument('--char-mode',action='append',choices=['signed','unsigned']);a=p.parse_args()
 root=a.root.resolve();out=a.output.resolve();assert out!=root and not out.is_relative_to(root),'output must be outside source root';out.mkdir(parents=True,exist_ok=False)
 sys.path.insert(0,str(root/'tools'))
 from recovered_implementation import index_manifest_definitions
 from split_source_index import scan_definitions,body_sha256
 fixture=root/'tests/tools/fixtures/class_world_visibility';proof=json.loads((fixture/'references/provenance.json').read_text());manifest=json.loads((root/'data/recovered_sources.json').read_text());rows={x['name']:x for x in manifest['functions']};registry=json.loads((root/'data/game_class_registry.json').read_text());binding,=[x for x in registry['class_bindings'] if x['class_owner']=='WorldMap']
 inputs={};sources=set();units=[]
 for n in NAMES:
  r=rows[n];assert r['implementation']['qualified_name']=='clash95::WorldMap::'+n;sources.update([r['source'],r['adapter']['source']])
 resolved=index_manifest_definitions(manifest,root,sources)
 for n in NAMES:
  parts=['#include "common.hpp"']
  for role in ['canonical','adapter']:
   item=resolved[(n,role)];expected=rows[n]['body_sha256'] if role=='canonical' else rows[n]['adapter']['body_sha256'];assert item.body_sha256==expected,n+' '+role+' hash';path=root/item.target.source;text=path.read_text();inputs[str(path)]=sha(path);d=item.definition;parts.append(text[d.start:d.end])
  path=out/('actual_'+n+'.cpp');path.write_text('\n\n'.join(parts)+'\n');units.append(path)
  row=next(x for x in proof['functions'] if x['name']==n);path=fixture/'references'/row['fixture'];text=path.read_text();d,=scan_definitions(text,{n});assert sha(path)==row['file_sha256'] and body_sha256(text,d)==row['body_sha256'] and rows[n]['original_address']==row['original_address'];inputs[str(path)]=sha(path)
  for other in NAMES:text=re.sub(r'\b'+other+r'(?=\s*\()','Reference_'+other,text)
  path=out/('reference_'+n+'.cpp');path.write_text('#include "common.hpp"\n'+text);units.append(path)
 path=root/binding['source'];text=path.read_text();d,=scan_definitions(text,{binding['qualified_name']});assert body_sha256(text,d)==binding['body_sha256'];inputs[str(path)]=sha(path);path2=out/'factory.cpp';path2.write_text('#include "common.hpp"\n'+text[d.start:d.end]+'\n');units.append(path2)
 kinds=list(EXPECTED) if a.kind=='all' else [a.kind]
 for file in ['common.hpp',*[k+'.cpp' for k in kinds]]:shutil.copy2(fixture/file,out/file);inputs[str(fixture/file)]=sha(fixture/file)
 for rel in ['data/recovered_sources.json','data/game_class_registry.json','src/world/WorldMap.hpp','tests/tools/fixtures/class_world_visibility/references/provenance.json','tests/tools/fixtures/class_world_visibility/verify_world_visibility.py']:inputs[str(root/rel)]=sha(root/rel)
 results=[]
 for compiler in a.compiler or ['g++-13','clang++-18']:
  assert shutil.which(compiler),'missing required compiler '+compiler
  for opt in a.optimization or ['O0','O2']:
   for chars in a.char_mode or ['signed','unsigned']:
    resources=resource_guard()
    label=Path(compiler).name+'-'+opt+'-'+chars;dest=out/label;dest.mkdir();flags=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-fno-exceptions','-fno-rtti','-fno-pie','-'+opt,'-f'+chars+'-char','-Wall','-Wextra','-Werror','-Wno-error=sign-compare','-fsanitize=undefined','-fsanitize-undefined-trap-on-error','-I',str(root/'src'),'-I',str(out)];commands=[];objects=[];item={'profile':label,'cases_per_lane':{'reveal':2034,'fog':33792,'binding':1},'lanes':['frozen','adapter','direct'],'build':0,'runs':{}}
    for source in units:
     obj=dest/(source.stem+'.o');command=flags+['-c',str(source),'-o',str(obj)];commands.append(command);r=subprocess.run(command,capture_output=True,text=True,timeout=60);(dest/(source.stem+'.build.log')).write_text(r.stdout+r.stderr)
     if r.returncode:item.update(build=r.returncode,failure_source=source.name);break
     objects.append(obj)
    if item['build']==0:
     for kind in kinds:
      binary=dest/kind;command=flags+['-no-pie',str(out/(kind+'.cpp')),*map(str,objects),'-o',str(binary)]
      if kind=='fog':command+=['-Wl,--wrap=Reference_Map_IsTileVisibleToPlayer','-Wl,--wrap='+QUERY]
      commands.append(command);r=subprocess.run(command,capture_output=True,text=True,timeout=60);(dest/(kind+'.build.log')).write_text(r.stdout+r.stderr)
      if r.returncode:item['runs'][kind]={'build':r.returncode};continue
      run=subprocess.run([str(binary)],capture_output=True,text=True,timeout=120);(dest/(kind+'.run.log')).write_text(run.stdout+run.stderr);item['runs'][kind]={'build':0,'run':run.returncode,'stdout':run.stdout,'stderr':run.stderr,'expected_output':run.stdout==EXPECTED[kind] and not run.stderr,'binary_sha256':sha(binary)}
    item['resources_before']=resources;item['resources_after']=resource_guard();(dest/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');results.append(item);(out/'progress.json').write_text(json.dumps({'source_inputs':inputs,'profiles':results},indent=2)+'\n');print(json.dumps(item),flush=True)
 unchanged=all(sha(Path(path))==value for path,value in inputs.items());passed=unchanged and all(x['build']==0 and set(x['runs'])==set(kinds) and all(y.get('build')==0 and y.get('run')==0 and y.get('expected_output') for y in x['runs'].values()) for x in results)
 report={'pass':passed,'root':str(root),'reference_commit':proof['reference_commit'],'source_inputs_unchanged':unchanged,'source_inputs':inputs,'profiles':results,'limitations':['Focused actual-source behavior comparison with instrumented MiniMap and style boundaries; not full runtime acceptance.','The original endpoint and overlay tables are preexisting measured observations; frozen references are reconstruction source, not retail code.','Valid player indices 0..5. Signed coordinate extremes are tested for query and reveal; classifier arithmetic extremes remain outside the proven domain.']};(out/'summary.json').write_text(json.dumps(report,indent=2)+'\n');return 0 if passed else 1
if __name__=='__main__':raise SystemExit(main())
