#!/usr/bin/env python3
"""Compile the actual explicit initializer and legacy adapter against frozen source."""
from pathlib import Path
import hashlib,json,platform,shutil,subprocess,sys,tempfile,unittest
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[2];FIXTURE=Path(__file__).parent/'fixtures/class_unit_slot_init';sys.path.insert(0,str(ROOT/'tools'))
from split_source_index import scan_definitions,body_sha256,mask_c
from recovered_implementation import index_manifest_definitions

class UnitSlotInitializerTests(unittest.TestCase):
 def test_actual_explicit_initializer_and_adapter(self):
  if platform.system()!='Linux' or platform.machine() not in ('x86_64','amd64'):self.skipTest('Linux low32 packed fixture required')
  provenance=json.loads((FIXTURE/'provenance.json').read_text());name=provenance['name'];raw=(FIXTURE/(name+'.cpp')).read_bytes();reference=raw.decode()
  self.assertEqual(hashlib.sha256(raw).hexdigest(),provenance['file_sha256']);self.assertEqual(body_sha256(reference,scan_definitions(reference,{name})[0]),provenance['body_sha256'])
  manifest=json.loads((ROOT/'data/recovered_sources.json').read_text());row=next(x for x in manifest['functions'] if x['name']==name);self.assertEqual(row['original_address'],provenance['original_address']);self.assertEqual(row['implementation']['kind'],'method')
  resolved=index_manifest_definitions(manifest,ROOT,{row['source'],row['adapter']['source']})
  prefix='#include "units/UnitSlot.hpp"\n#include "world/world_api.h"\n#include "world/world_shared_state.h"\n#include "state/state_api.h"\n#include "recovered_structs.h"\n'
  # The frozen reference and real table definition need the original external
  # declaration even if later consumer-header narrowing hides it from world.
  declarations=json.loads((ROOT/'data/recovered_decls.json').read_text())
  prefix+='extern "C" {\n'+declarations['globals']['g_UnitTypeRuntimeCoreMetadata']['decl']+'\n}\n'
  parts={'canonical':[prefix],'adapter':[prefix],'reference':[prefix,'extern const UnitTypeRuntimeCoreMetadataRecord *fixtureMetadata;\n#undef g_UnitTypeFlags\n#undef g_UnitTypeBaseActionPoints\n#define g_UnitTypeFlags ((const _DWORD *)&fixtureMetadata[0].flags)\n#define g_UnitTypeBaseActionPoints ((const unsigned char *)&fixtureMetadata[0].base_action_points)','__attribute__((no_sanitize("alignment")))\n'+reference.replace(name+'(', 'Reference_'+name+'(',1)]}
  for role in ['canonical','adapter']:
   item=resolved[name,role];self.assertEqual(item.body_sha256,row['body_sha256'] if role=='canonical' else row['adapter']['body_sha256']);text=(ROOT/item.target.source).read_text();parts[role].append(text[item.definition.start:item.definition.end])
  ap_path=FIXTURE.parent/'class_unit_slot_ap/provenance.json';self.assertEqual(hashlib.sha256(ap_path.read_bytes()).hexdigest(),provenance['prior_ap_table_provenance_sha256']);ap=json.loads(ap_path.read_text());binding=ap['binding']
  state=(ROOT/binding['source']).read_text();found=scan_definitions(state,{binding['name']});self.assertEqual(len(found),1);self.assertEqual(body_sha256(state,found[0]),binding['body_sha256'])
  start=state.index('const UnitTypeRuntimeCoreMetadataRecord g_UnitTypeRuntimeCoreMetadata[');masked=mask_c(state);opening=masked.index('{',start);depth=1;end=opening+1
  while depth:depth+=(masked[end]=='{')-(masked[end]=='}');end+=1
  end=masked.index(';',end)+1;table=state[start:end]+'\n';self.assertEqual(hashlib.sha256(table.encode()).hexdigest(),ap['table_file_sha256'])
  parts['binding']=[prefix,state[found[0].start:found[0].end],table]
  with tempfile.TemporaryDirectory(prefix='clash95-unit-slot-init-') as temporary:
   directory=Path(temporary);files=[]
   for role,source in parts.items():
    path=directory/(role+'.cpp');path.write_text('\n'.join(source));files.append(str(path))
   harness=directory/'harness.cpp';harness.write_bytes((FIXTURE/'harness.cpp').read_bytes());files.append(str(harness))
   for compiler in ['g++-13','clang++-18']:
    for opt in ['-O0','-O2']:
     with self.subTest(compiler=compiler,optimization=opt):
      self.assertIsNotNone(shutil.which(compiler));binary=directory/(compiler+opt)
      # Retain and report the original unsigned-enum sentinel comparisons and
      # frozen reference's int-address macro warning; do not repair them here.
      command=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-fno-exceptions','-fno-rtti','-fno-pie','-no-pie',opt,'-fsanitize=undefined','-fsanitize-undefined-trap-on-error','-Wall','-Wextra','-Werror','-Wno-error=sign-compare','-Wno-error=int-to-pointer-cast','-I'+str(ROOT/'src'),*files,'-Wl,--wrap=UnitSlot_BorrowTypeMetadata','-o',str(binary)]
      built=subprocess.run(command,capture_output=True,text=True,timeout=90);self.assertEqual(built.returncode,0,built.stdout+built.stderr)
      executed=subprocess.run([str(binary)],capture_output=True,text=True,timeout=150);self.assertEqual(executed.returncode,0,executed.stdout+executed.stderr);self.assertIn('cases=2863104',executed.stdout);self.assertIn('explicit_initializer=pass',executed.stdout)
if __name__=='__main__':unittest.main()
