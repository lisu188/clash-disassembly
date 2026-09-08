#!/usr/bin/env python3
"""Compile current manifest-resolved UnitTurn bodies against repaired frozen references.

Writes only --output, never --root. External game services are instrumented
boundaries; this is focused extraction parity, not full runtime validation.
"""
from pathlib import Path
import argparse,hashlib,json,shutil,subprocess,sys
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve().parent

def main():
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--root',type=Path,required=True)
 parser.add_argument('--output',type=Path,required=True)
 args=parser.parse_args(); root=args.root.resolve(); output=args.output.resolve()
 if output==root or output.is_relative_to(root): raise ValueError('output must be outside the source root')
 output.mkdir(parents=True,exist_ok=False)
 sys.path.insert(0,str(root/'tools'))
 from recovered_implementation import index_manifest_definitions
 from split_source_index import scan_definitions,body_sha256
 provenance=json.loads((HERE/'references/provenance.json').read_text())
 manifest=json.loads((root/'data/recovered_sources.json').read_text()); records={x['name']:x for x in manifest['functions']}
 registry=json.loads((root/'data/game_class_registry.json').read_text())
 bindings=[x for x in registry.get('class_bindings',[]) if x['class_owner']=='UnitTurn']
 assert len(bindings)==1
 binding=bindings[0]
 declarations=json.loads((root/'data/recovered_decls.json').read_text())
 parts=['#include "units/units_internal.h"','#include "buildings/buildings_internal.h"','#include "units/units_state.h"','#include "units/units_shared_state.h"','#include "strategic/strategic_api.h"','#include "units/UnitTurn.hpp"','#include "units/UnitStack.hpp"','#include "recovered_structs.h"','#include <sys/mman.h>','#include <vector>','#include <array>','#include <string>','#include <limits.h>']
 # GameRandom remains an instrumented external boundary in this UnitTurn gate.
 # Its own gate compiles both actual methods, the actual factory and ABI adapters.
 random_bindings=[x for x in registry.get('class_bindings',[]) if x['class_owner']=='GameRandom']
 if random_bindings:
  assert len(random_bindings)==1
  random_binding=random_bindings[0]
  parts.extend(['#include "core/GameRandom.hpp"','#define UNIT_TURN_CLASS_RANDOM_BOUNDARY 1'])
  parts.extend(declarations['globals'][name]['decl'] for name in random_binding['referenced_globals'])
  random_text=(root/random_binding['source']).read_text()
  random_defs=scan_definitions(random_text,{random_binding['qualified_name']})
  assert len(random_defs)==1
  random_definition=random_defs[0]
  assert body_sha256(random_text,random_definition)==random_binding['body_sha256']
  parts.append(random_text[random_definition.start:random_definition.end])
 # The production factory retains exact declarations at its original anchor;
 # generated consumer headers can legitimately stop exposing these globals.
 parts.extend(declarations['globals'][name]['decl'] for name in binding['referenced_globals'])
 import re
 names=set()
 inputs={}
 sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
 for record in provenance['functions']:
  name=record['name']; names.add(name); path=HERE/'references'/record['fixture']; text=path.read_text(); inputs[str(path)]=sha(path)
  assert sha(path)==record['file_sha256'],name+' reference file hash'
  definitions=scan_definitions(text,{name}); assert len(definitions)==1
  assert body_sha256(text,definitions[0])==record['body_sha256'],name+' reference body hash'
  assert records[name]['original_address']==record['original_address'],name+' original identity'
  parts.append('__attribute__((no_sanitize("alignment")))\n'+re.sub(r'\b'+name+r'(?=\s*\()','Reference_'+name,text,count=1))
 sources=set()
 dependencies={'UnitStack_HasReadyUnits'}
 for dependency in dependencies:
  sources.update([records[dependency]['source'],records[dependency]['adapter']['source']])
 for name in names:
  record=records[name]
  assert record['implementation']['qualified_name']=='clash95::UnitTurn::'+name
  sources.update([record['source'],record['adapter']['source']])
 resolved=index_manifest_definitions(manifest,root,sources)
 for name in sorted(names | dependencies):
  for role in ['canonical','adapter']:
   item=resolved[(name,role)]
   expected=records[name]['body_sha256'] if role=='canonical' else records[name]['adapter']['body_sha256']
   assert item.body_sha256==expected,name+' '+role+' manifest hash'
   path=root/item.target.source; text=path.read_text(); d=item.definition
   inputs[str(path)]=sha(path); parts.append(text[d.start:d.end])
 path=root/binding['source']; text=path.read_text(); definitions=scan_definitions(text,{binding['qualified_name']})
 assert len(definitions)==1
 d=definitions[0]; assert body_sha256(text,d)==binding['body_sha256']; parts.append(text[d.start:d.end]); inputs[str(path)]=sha(path)
 for path in [root/'data/recovered_sources.json',root/'data/game_class_registry.json',root/'data/recovered_decls.json',root/'src/units/UnitTurn.hpp',root/'src/units/UnitStack.hpp',HERE/'harness.cpp',HERE/'references/provenance.json']:
  inputs[str(path)]=sha(path)
 if random_bindings:
  for path in [root/random_binding['source'],root/'src/core/GameRandom.hpp']:
   inputs[str(path)]=sha(path)
 (output/'production-reference.inc').write_text('\n\n'.join(parts)+'\n')
 shutil.copy2(HERE/'harness.cpp',output/'harness.cpp')
 results=[]
 for compiler in ['g++-13','clang++-18']:
  if not shutil.which(compiler): raise ValueError('required compiler missing: '+compiler)
  for opt in ['-O0','-O2']:
   label=compiler+opt; binary=output/label
   command=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-fno-exceptions','-fno-rtti','-fno-pie','-no-pie',opt,'-fsanitize=alignment','-fsanitize-undefined-trap-on-error','-Wall','-Wextra','-I',str(root/'src'),str(output/'harness.cpp'),'-o',str(binary)]
   built=subprocess.run(command,text=True,capture_output=True,timeout=60); (output/(label+'.build.log')).write_text(built.stdout+built.stderr)
   item={'profile':label,'command':command,'build':built.returncode}
   if built.returncode: item['build_output']=built.stdout+built.stderr
   if built.returncode==0:
    executed=subprocess.run([str(binary)],text=True,capture_output=True,timeout=45); (output/(label+'.run.log')).write_text(executed.stdout+executed.stderr)
    item.update(run=executed.returncode,stdout=executed.stdout,stderr=executed.stderr,binary_sha256=sha(binary))
   results.append(item); print(json.dumps(item),flush=True)
 unchanged=all(Path(p).exists() and sha(Path(p))==v for p,v in inputs.items())
 report={'root':str(root),'inputs_unchanged':unchanged,'input_sha256':inputs,'profiles':results,'expected_cases_per_profile':{'regen':4096,'damage':6144,'turn':336},'limitations':['instrumented external service boundaries, not full game runtime','zero max HP and invalid building type are outside source preconditions','frozen references retain original x86 unaligned loads and are exempt from alignment sanitizer; methods/adapters are trapped']}
 (output/'summary.json').write_text(json.dumps(report,indent=2)+'\n')
 return 0 if unchanged and all(x.get('build')==0 and x.get('run')==0 for x in results) else 1
if __name__=='__main__': raise SystemExit(main())
