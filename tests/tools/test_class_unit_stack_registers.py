#!/usr/bin/env python3
"""Compare c65e476 bodies with actual UnitStack methods and original ABI adapters.

The AP query is the actual production canonical method plus adapter. Remaining
dependencies are explicit spies: they capture full callback-time backing bytes
and exercise mutations, without claiming original compaction/fact equivalence.
"""
from pathlib import Path
import hashlib,importlib.util,json,os,platform,re,shutil,subprocess,sys,tempfile,unittest
ROOT=Path(os.environ.get('CLASH95_SOURCE_ROOT',Path(__file__).resolve().parents[2])).resolve()
HERE=Path(__file__).resolve().parent
FIXTURE=HERE/'fixtures/class_unit_stack_registers/references'
sys.path.insert(0,str(ROOT/'tools'))
from recovered_implementation import index_manifest_definitions
from split_source_index import scan_definitions,body_sha256

def corpus_module():
 spec=importlib.util.spec_from_file_location('register_corpus',HERE/'test_unit_stack_register_contracts.py')
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module

def source_fixture():
 corpus=corpus_module()
 names=['UnitStack_CalcMilitaryStrength','UnitStack_NormalizePeasantCargo','UnitStack_GetMinCurrentActionPoints']
 manifest=json.loads((ROOT/'data/recovered_sources.json').read_text())
 records={r['name']:r for r in manifest['functions']}
 sources={records[n]['source'] for n in names}|{records[n]['adapter']['source'] for n in names}
 resolved=index_manifest_definitions(manifest,ROOT,sources)
 snippets=[]
 for name in names:
  record=records[name]
  assert record['implementation']['qualified_name']=='clash95::UnitStack::'+name
  for role in ('canonical','adapter'):
   item=resolved[(name,role)]
   expected=record['body_sha256'] if role=='canonical' else record['adapter']['body_sha256']
   assert item.body_sha256==expected,name+': '+role+' body hash drift'
   text=(ROOT/item.target.source).read_text();d=item.definition
   if name=='UnitStack_NormalizePeasantCargo' and role=='canonical':
    assert text[d.start:d.end].count('this->UnitStack_GetMinCurrentActionPoints()')==1, (
     'Migrated cargo behavior must call its actual AP member directly')
   snippets.append(text[d.start:d.end])
 provenance=json.loads((FIXTURE/'provenance.json').read_text())
 assert provenance['reference_commit']=='c65e476273c96fe86b2e4a308798cea89c8696bc'
 dependency=provenance['ap_dependency']
 assert records[dependency['name']]['original_address']==dependency['original_address']
 header=FIXTURE/dependency['header']['fixture']
 assert hashlib.sha256(header.read_bytes()).hexdigest()==dependency['header']['file_sha256']
 reference_binding=re.sub(r'\bUnitStack\b','ReferenceUnitStack',header.read_text())
 reference_binding=reference_binding.replace('#pragma once\n','').replace('../recovered_types.h','recovered_types.h')
 reference_ap=[reference_binding]
 for member in dependency['members']:
  path=FIXTURE/member['fixture'];text=path.read_text()
  assert hashlib.sha256(path.read_bytes()).hexdigest()==member['file_sha256']
  definitions=list(scan_definitions(text,{member['qualified_name']}));assert len(definitions)==1
  assert body_sha256(text,definitions[0])==member['body_sha256']
  text=re.sub(r'\bUnitStack\b','ReferenceUnitStack',text)
  if member['role']=='adapter':
   text,count=re.subn(r'\bUnitStack_GetMinCurrentActionPoints(?=\s*\()',
    'Reference_UnitStack_GetMinCurrentActionPoints',text,count=1);assert count==1
  reference_ap.append(text)
 snippets+=reference_ap
 for record in provenance['functions']:
  name=record['name'];path=FIXTURE/record['fixture'];text=path.read_text()
  assert hashlib.sha256(path.read_bytes()).hexdigest()==record['file_sha256']
  definitions=list(scan_definitions(text,{name}));assert len(definitions)==1
  assert body_sha256(text,definitions[0])==record['body_sha256']
  assert records[name]['original_address']==record['original_address']
  text,count=re.subn(r'\b'+name+r'(?=\s*\()','Reference_'+name,text,count=1);assert count==1
  text=text.replace('UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr)',
                    'Reference_UnitStack_GetMinCurrentActionPoints((intptr_t)stackPtr)')
  snippets.append(text)
 harness=corpus.HARNESS
 start=harness.index('signed int UnitStack_GetMinCurrentActionPoints(intptr_t value)')
 end=harness.index('signed int Unit_CompactSquad',start)
 harness=harness[:start]+'signed int UnitStack_GetMinCurrentActionPoints(intptr_t value);\n'+harness[end:]
 harness=harness.replace('static uint32_t trace[4][8], trace_count;',
  'static uint32_t trace[4][8], trace_count;\nstatic unsigned char snapshots[4][800];')
 harness=harness.replace('  uint32_t *out=trace[trace_count++];',
  '  memcpy(snapshots[trace_count],actual,sizeof(actual));\n  uint32_t *out=trace[trace_count++];')
 harness=harness.replace('  return 0x31415926;',
  '  actual[760]^=uint8_t(row[3]); actual[761]=uint8_t(row[2]);\n  return 0x31415926;')
 harness=harness.replace('event(5,uint32_t(uintptr_t(value)),count,bonus);return int(row[4]);',
  'event(5,uint32_t(uintptr_t(value)),count,bonus);actual[763]=uint8_t(count+bonus);return int(row[4]);')
 harness=harness.replace('  return int(row[4]);',
  '  actual[762]^=uint8_t(row[5]);\n  return int(row[4]);')
 harness=harness[:harness.index('int main(')]+r"""
struct Observation {
 uint32_t returned,count;
 uint32_t calls[4][8];
 unsigned char callback_bytes[4][800], final_bytes[800];
};
int main(int argc,char **argv) {
 if(argc!=2)return 2;
 FILE *cases=fopen(argv[1],"rb");if(!cases)return 3;
 unsigned index=0;
 while(fread(row,sizeof(row),1,cases)==1) {
  if(fread(input,sizeof(input),1,cases)!=1)return 4;
  Observation reference{};
  for(int route=0;route<3;++route) {
   memcpy(actual,input,sizeof(actual));memset(trace,0,sizeof(trace));trace_count=0;
   memset(snapshots,0,sizeof(snapshots));
   stack_address=actual+32+(row[0]?row[1]:0);
   if(uintptr_t(actual)+sizeof(actual)>INT32_MAX)return 5;
   double time;memcpy(&time,row+6,8);
   const clash95::UnitStack record(row[0]?intptr_t(stack_address):intptr_t(int(row[1])));
   if(memcmp(actual,input,sizeof(actual))||trace_count)return 6;
   int result;
   if(route==0) result=row[0]?Reference_UnitStack_NormalizePeasantCargo((__int16*)stack_address,row[5],time)
                           :Reference_UnitStack_CalcMilitaryStrength(int(row[1]));
   else if(route==1) result=row[0]?record.UnitStack_NormalizePeasantCargo(row[5],time)
                                :record.UnitStack_CalcMilitaryStrength();
   else result=row[0]?UnitStack_NormalizePeasantCargo((__int16*)stack_address,row[5],time)
                    :UnitStack_CalcMilitaryStrength(int(row[1]));
   Observation actual_observation{};
   actual_observation.returned=uint32_t(result);actual_observation.count=trace_count;
   memcpy(actual_observation.calls,trace,sizeof(trace));
   memcpy(actual_observation.callback_bytes,snapshots,sizeof(snapshots));
   memcpy(actual_observation.final_bytes,actual,sizeof(actual));
   if(route==0)reference=actual_observation;
   else if(memcmp(&reference,&actual_observation,sizeof(reference))) {
    const auto *want=reinterpret_cast<const unsigned char*>(&reference);
    const auto *got=reinterpret_cast<const unsigned char*>(&actual_observation);
    for(unsigned offset=0;offset<sizeof(reference);++offset)if(want[offset]!=got[offset]) {
     fprintf(stderr,"case=%u mode=%u route=%d byte=%u actual=%u expected=%u\n",index,row[0],route,offset,got[offset],want[offset]);break;
    }
    return 7;
   }
  }
  ++index;
 }
 if(ferror(cases))return 8;
 fclose(cases);printf("PASS cases=%u reference,direct,adapter actual_AP full_bytes=exact callback_bytes=exact calls=exact\n",index);
 return 0;
}
"""
 return harness.replace('__TARGETS__','\n'.join(snippets)).replace(', expected[936]','')

class UnitStackRegisterClassTests(unittest.TestCase):
 @unittest.skipUnless(sys.platform=='linux' and platform.machine()=='x86_64','requires Linux low32 non-PIE addresses')
 def test_repaired_production_reference_direct_methods_and_adapters(self):
  evidence=os.environ.get('CLASH95_UNIT_STACK_CLASS_EVIDENCE')
  with tempfile.TemporaryDirectory(prefix='clash95-unit-stack-class-') as temporary:
   work=Path(evidence).resolve() if evidence else Path(temporary)
   if evidence:work.mkdir(parents=True,exist_ok=False)
   corpus=corpus_module();count=corpus.write_inputs(work);self.assertEqual(count,5001)
   source=source_fixture();(work/'probe.cpp').write_text(source)
   rows=[]
   for compiler in ('g++-13','clang++-18'):
    self.assertIsNotNone(shutil.which(compiler))
    for optimization in ('-O0','-O2'):
     for unsigned_char in (False,True):
      label=compiler+optimization+('-unsigned' if unsigned_char else '-signed')
      with self.subTest(profile=label):
       command=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-I',str(ROOT/'src'),optimization,
        '-fno-pie','-no-pie','-fno-exceptions','-fno-rtti','-Wall','-Wextra','-Werror',
        '-fsanitize=undefined','-fsanitize-undefined-trap-on-error']
       if unsigned_char:command+=['-funsigned-char']
       command+=[str(work/'probe.cpp'),'-o',str(work/label)]
       built=subprocess.run(command,capture_output=True,text=True,timeout=60)
       (work/(label+'.build.log')).write_text(built.stdout+built.stderr)
       row={'profile':label,'command':command,'build':built.returncode};rows.append(row)
       self.assertEqual(built.returncode,0,built.stdout+built.stderr)
       ran=subprocess.run([str(work/label),str(work/'cases.bin')],capture_output=True,text=True,timeout=30)
       (work/(label+'.run.log')).write_text(ran.stdout+ran.stderr)
       row.update(run=ran.returncode,stdout=ran.stdout,stderr=ran.stderr)
       self.assertEqual(ran.returncode,0,ran.stdout+ran.stderr)
   (work/'summary.json').write_text(json.dumps({'reference_commit':'c65e476273c96fe86b2e4a308798cea89c8696bc',
    'case_count':count,'profiles':rows,'scope':'Actual canonical target and AP methods plus original-signature adapters; controlled scoring, count, compaction and fact dependencies.'},indent=2)+'\n')

if __name__=='__main__':unittest.main()
