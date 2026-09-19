#!/usr/bin/env python3
"""Actual UnitStack query methods and adapters against frozen production bodies."""
from pathlib import Path
import hashlib,json,os,platform,re,shutil,subprocess,sys,tempfile,unittest
ROOT=Path(os.environ.get('CLASH95_SOURCE_ROOT',Path(__file__).resolve().parents[2])).resolve()
FIXTURE=Path(__file__).parent/'fixtures/class_unit_stack_flags'
sys.path.insert(0,str(ROOT/'tools'))
from recovered_implementation import index_manifest_definitions
from split_source_index import scan_definitions,body_sha256
NAMES=['UnitStack_HasPlague','UnitStack_HasLowMoraleUnit']

def source_fixture():
 manifest=json.loads((ROOT/'data/recovered_sources.json').read_text());records={r['name']:r for r in manifest['functions']}
 sources={records[n]['source'] for n in NAMES}|{records[n]['adapter']['source'] for n in NAMES}
 indexed=index_manifest_definitions(manifest,ROOT,sources)
 snippets=['#include "recovered_layout.h"\n#include "units/UnitStack.hpp"\n#include "units/units_internal.h"\n']
 for name in NAMES:
  record=records[name];assert record['implementation']['qualified_name']=='clash95::UnitStack::'+name
  for role in ('canonical','adapter'):
   item=indexed[(name,role)];expected=record['body_sha256'] if role=='canonical' else record['adapter']['body_sha256']
   assert item.body_sha256==expected,name+': '+role+' body drift'
   text=(ROOT/item.target.source).read_text();d=item.definition;snippets.append(text[d.start:d.end])
 provenance=json.loads((FIXTURE/'references/provenance.json').read_text())
 assert provenance['reference_commit']=='f6849c64710fcc150a6be652a098cb5f9f9564bd'
 for record in provenance['functions']:
  name=record['name'];p=FIXTURE/'references'/record['fixture'];text=p.read_text()
  assert hashlib.sha256(p.read_bytes()).hexdigest()==record['file_sha256']
  defs=list(scan_definitions(text,{name}));assert len(defs)==1
  assert body_sha256(text,defs[0])==record['body_sha256']
  assert records[name]['original_address']==record['original_address']
  text,count=re.subn(r'\b'+name+r'(?=\s*\()','Reference_'+name,text,count=1);assert count==1
  snippets.append(text)
 snippets.append((FIXTURE/'harness.cpp').read_text())
 return '\n'.join(snippets)

class UnitStackFlagQueryTests(unittest.TestCase):
 @unittest.skipUnless(sys.platform=='linux' and platform.machine()=='x86_64','requires Linux signed-low32 mappings')
 def test_actual_methods_adapters_and_guarded_reads(self):
  evidence=os.environ.get('CLASH95_UNIT_STACK_FLAGS_EVIDENCE')
  with tempfile.TemporaryDirectory(prefix='clash95-unit-stack-flags-') as temporary:
   out=Path(evidence).resolve() if evidence else Path(temporary)
   if evidence:out.mkdir(parents=True,exist_ok=False)
   (out/'probe.cpp').write_text(source_fixture());rows=[]
   for compiler in ('g++-13','clang++-18'):
    self.assertIsNotNone(shutil.which(compiler))
    for optimization in ('-O0','-O2'):
     for unsigned_char in (False,True):
      label=compiler+optimization+('-unsigned' if unsigned_char else '-signed')
      with self.subTest(profile=label):
       command=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-fno-exceptions','-fno-rtti',optimization,
        '-fno-pie','-no-pie','-Wall','-Wextra','-Werror','-fsanitize=undefined','-fsanitize-undefined-trap-on-error',
        '-I',str(ROOT/'src'),str(out/'probe.cpp'),'-o',str(out/label)]
       if unsigned_char:command+=['-funsigned-char']
       built=subprocess.run(command,capture_output=True,text=True,timeout=60)
       (out/(label+'.build.log')).write_text(built.stdout+built.stderr)
       row={'profile':label,'command':command,'build':built.returncode};rows.append(row)
       self.assertEqual(built.returncode,0,built.stdout+built.stderr)
       ran=subprocess.run([str(out/label)],capture_output=True,text=True,timeout=90)
       (out/(label+'.run.log')).write_text(ran.stdout+ran.stderr)
       row.update(run=ran.returncode,stdout=ran.stdout,stderr=ran.stderr)
       self.assertEqual(ran.returncode,0,ran.stdout+ran.stderr)
       self.assertIn('PASS cases=62140 ',ran.stdout)
   (out/'summary.json').write_text(json.dumps({'reference_commit':'f6849c64710fcc150a6be652a098cb5f9f9564bd',
    'profiles':rows,'case_count':62140},indent=2)+'\n')

if __name__=='__main__':unittest.main()
