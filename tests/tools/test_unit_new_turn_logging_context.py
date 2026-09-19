#!/usr/bin/env python3
"""Production-resolving regression for Unit_NewTurn's first-stack enemy exit.

Actual Unit_NewTurn, LogAllUnits, Debug_Log and the migrated readiness/AP queries
are compiled separately; the immutable AP-table accessor remains an observed seam;
linker wrapping observes the boundary without rewriting the recovered body.
Poisoned automatic locals make an omitted assignment fail deterministically.
"""
from pathlib import Path
import hashlib,json,os,platform,shutil,subprocess,sys,tempfile,unittest
sys.dont_write_bytecode=True
ROOT=Path(os.environ.get('CLASH95_SOURCE_ROOT',Path(__file__).resolve().parents[2])).resolve()
FIXTURE=Path(__file__).resolve().parent/'fixtures/unit_new_turn_logging_context/harness.cpp'
sys.path.insert(0,str(ROOT/'tools'))
from recovered_implementation import index_manifest_definitions
from split_source_index import scan_definitions,body_sha256

class UnitNewTurnLoggingContextTests(unittest.TestCase):
 def test_first_stack_enemy_exit_and_actual_logging_contract(self):
  if platform.system()!='Linux' or platform.machine() not in ('x86_64','amd64'):
   self.skipTest('supported low32 fixture requires Linux x86-64')
  manifest=json.loads((ROOT/'data/recovered_sources.json').read_text()); records={x['name']:x for x in manifest['functions']}
  names={'Unit_NewTurn','LogAllUnits','Debug_Log','UnitStack_HasReadyUnits','UnitSlot_CalcActionPointsFromFatigue'}
  sources=set()
  for name in names:
   sources.add(records[name]['source'])
   if 'adapter' in records[name]: sources.add(records[name]['adapter']['source'])
  indexed=index_manifest_definitions(manifest,ROOT,sources)
  includes=['#include "units/units_internal.h"','#include "units/units_state.h"','#include "units/units_shared_state.h"','#include "buildings/buildings_api.h"','#include "strategic/strategic_api.h"','#include "units/UnitStack.hpp"','#include "units/UnitSlot.hpp"','#include "state/state_api.h"','#include "recovered_structs.h"']
  registry=json.loads((ROOT/'data/game_class_registry.json').read_text())
  declarations=json.loads((ROOT/'data/recovered_decls.json').read_text())
  parts={}; inputs={}; sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
  for name in sorted(names):
   record=records[name]; content=list(includes)
   if record.get('implementation',{}).get('kind')=='method':
    content.append('#include "'+record['implementation']['header'].removeprefix('src/')+'"')
    owner=record['implementation']['qualified_name'].split('::')[-2]
    for binding in registry.get('class_bindings',[]):
     if binding['class_owner']==owner:
      content.extend(declarations['globals'][global_name]['decl'] for global_name in binding['referenced_globals'])
   for role in ['canonical']+(['adapter'] if 'adapter' in record else []):
    item=indexed[(name,role)]; expected=record['body_sha256'] if role=='canonical' else record['adapter']['body_sha256']
    self.assertEqual(item.body_sha256,expected,f'{name} {role} recorded body')
    p=ROOT/item.target.source; text=p.read_text(); d=item.definition; content.append(text[d.start:d.end]); inputs[str(p)]=sha(p)
   if record.get('implementation',{}).get('kind')=='method':
    owner=record['implementation']['qualified_name'].split('::')[-2]
    bindings=[x for x in registry.get('class_bindings',[]) if x['class_owner']==owner]
    self.assertLessEqual(len(bindings),1)
    if bindings:
     binding=bindings[0]; p=ROOT/binding['source']; text=p.read_text(); defs=scan_definitions(text,{binding['qualified_name']}); self.assertEqual(len(defs),1)
     d=defs[0]; self.assertEqual(body_sha256(text,d),binding['body_sha256']); content.append(text[d.start:d.end]); inputs[str(p)]=sha(p)
   parts[name]='\n\n'.join(content)+'\n'
  evidence=os.environ.get('CLASH95_RECOVERY_EVIDENCE')
  owner=tempfile.TemporaryDirectory(prefix='clash95-unit-turn-recovery-') if not evidence else None
  directory=Path(owner.name) if owner else Path(evidence).resolve()
  if evidence: directory.mkdir(parents=True,exist_ok=False)
  results=[]
  try:
   for name,text in parts.items(): (directory/(name+'.cpp')).write_text(text)
   shutil.copy2(FIXTURE,directory/'harness.cpp')
   for compiler in ['g++-13','clang++-18']:
    self.assertIsNotNone(shutil.which(compiler),'required supported compiler '+compiler)
    for opt in ['-O0','-O2']:
     with self.subTest(compiler=compiler,optimization=opt):
      label=compiler+opt; binary=directory/label
      command=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-fno-exceptions','-fno-rtti','-fno-pie','-no-pie',opt,'-ftrivial-auto-var-init=pattern','-Wall','-Wextra','-I',str(ROOT/'src')]
      command += [str(directory/(name+'.cpp')) for name in sorted(names)]+[str(directory/'harness.cpp'),'-Wl,--wrap=LogAllUnits','-o',str(binary)]
      built=subprocess.run(command,text=True,capture_output=True,timeout=60); (directory/(label+'.build.log')).write_text(built.stdout+built.stderr)
      result={'profile':label,'command':command,'build':built.returncode}; results.append(result)
      self.assertEqual(built.returncode,0,built.stdout+built.stderr)
      run=subprocess.run([str(binary)],text=True,capture_output=True,timeout=30); (directory/(label+'.run.log')).write_text(run.stdout+run.stderr)
      result.update(run=run.returncode,stdout=run.stdout,stderr=run.stderr)
      self.assertEqual(run.returncode,0,run.stdout+run.stderr)
      self.assertIn('PASS recovery_cases=32 first_stack_enemy_exits=4 logging_context_extremes=28',run.stdout)
   self.assertTrue(all(sha(Path(p))==value for p,value in inputs.items()),'production inputs changed during test')
  finally:
   (directory/'summary.json').write_text(json.dumps({'source_root':str(ROOT),'input_sha256':inputs,'profiles':results,'fixture_sha256':sha(FIXTURE)},indent=2)+'\n')
   if owner: owner.cleanup()
if __name__=='__main__': unittest.main()
