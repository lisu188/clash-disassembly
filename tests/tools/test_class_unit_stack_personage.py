#!/usr/bin/env python3
"""Compile actual class queries and adapters against pinned original instruction output."""
from pathlib import Path
import hashlib,json,os,platform,shutil,struct,subprocess,sys,tempfile,unittest
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
FIXTURE=ROOT/'tests/tools/fixtures/class_unit_stack_personage'
NAMES=('UnitStack_GetMaxOrderTier','UnitStack_HasNormalCombatUnits','UnitStack_HasSpecialPersonageUnits')
BASE_IMAGES=tuple(bytes((i*37+seed*13)&255 for i in range(800)) for seed in range(256))

def row(base,prefix,kind,mark,seed,orders):
 image=bytearray(BASE_IMAGES[seed&255])
 for i in range(10):
  struct.pack_into('<h',image,38+31*i,31 if i<prefix else -1)
  image[50+31*i]=(orders+17*i)&255
 if mark<prefix:struct.pack_into('<h',image,38+31*mark,kind)
 return struct.pack('<II',0,base)+image

def cases():
 for word in range(65536):
  signed=word if word<32768 else word-65536
  yield row(0x30000020+(word&15),1,signed,0,word,word>>8)
 types=(-32768,-2,0,1,30,31,32,33,34,35,255,32767)
 for alignment in range(16):
  for prefix in range(11):
   for marker in range(10):
    for kind in types:
     yield row(0x30000020+alignment,prefix,kind,marker,prefix*23+marker,kind&255)
 for alignment in range(16):
  for prefix in range(11):
   for kind in (31,33,34):
    yield row(0x7ffffef0+alignment,prefix,kind,9,prefix,255)

def expected(data):
 image=data[8:];types=[];tiers=[]
 for i in range(10):
  kind=struct.unpack_from('<h',image,38+31*i)[0]
  if kind==-1:break
  types.append(kind);tiers.append(image[50+31*i]&3)
 special=int(any(t in (33,34) for t in types))
 normal=int(any(t not in (31,32,33,34) for t in types))
 tier=3 if special else max(tiers,default=0)
 return struct.pack('<III',tier,normal,special)+image

def streams():
 inputs=b''.join(cases());output=b''.join(expected(inputs[i:i+808]) for i in range(0,len(inputs),808))
 proof=json.loads((FIXTURE/'original_measurement.json').read_text())['measured_streams']
 assert len(inputs)//808==proof['case_count']==87184
 for data,key in ((inputs,'input'),(output,'output')):
  assert len(data)==proof[key+'_bytes']
  assert hashlib.sha256(data).hexdigest()==proof[key+'_sha256'],key+' does not match the original measured stream'
 return inputs,output

def source_fixture():
 from split_source_index import scan_definitions,body_sha256
 from recovered_implementation import index_manifest_definitions
 manifest=json.loads((ROOT/'data/recovered_sources.json').read_text());records={r['name']:r for r in manifest['functions']}
 proof=json.loads((FIXTURE/'references/provenance.json').read_text())
 targets=[];references=[];adapters=[]
 sources={records[n]['source'] for n in NAMES}|{records[n]['adapter']['source'] for n in NAMES}
 indexed=index_manifest_definitions(manifest,ROOT,sources)
 for name in NAMES:
  record=records[name];assert record['implementation']['kind']=='method'
  original=next(r for r in proof['functions'] if r['name']==name)
  assert record['original_address']==original['original_address']
  frozen=(FIXTURE/'references'/original['fixture']).read_text()
  assert hashlib.sha256(frozen.encode()).hexdigest()==original['file_sha256']
  fd,=scan_definitions(frozen,{name});assert body_sha256(frozen,fd)==original['body_sha256']
  frozen=frozen.replace(name+'(', 'Reference_'+name+'(',1)
  if name=='UnitStack_GetMaxOrderTier':
   frozen=frozen.replace('UnitStack_HasSpecialPersonageUnits(stackPtr)','Reference_UnitStack_HasSpecialPersonageUnits(stackPtr)',1)
  references.append('__attribute__((no_sanitize("alignment")))\n'+frozen)
  for role,destination in (('canonical',targets),('adapter',adapters)):
   item=indexed[(name,role)];text=(ROOT/item.target.source).read_text();body=text[item.definition.start:item.definition.end]
   assert item.body_sha256==(record['body_sha256'] if role=='canonical' else record['adapter']['body_sha256'])
   if role=='adapter' and name=='UnitStack_HasSpecialPersonageUnits':
    body=body.replace(name+'(', 'Actual_'+name+'(',1)
   destination.append(body)
 helper_proof=proof['procedural_dependency'];helper=(ROOT/helper_proof['source']).read_text()
 hd,=scan_definitions(helper,{'Unit_GetSquadCount'});assert body_sha256(helper,hd)==helper_proof['body_sha256']
 helper=helper[hd.start:hd.end].replace('Unit_GetSquadCount(', 'Actual_Unit_GetSquadCount(',1)
 helper='__attribute__((no_sanitize("alignment")))\n'+helper
 header=(ROOT/'src/units/UnitStack.hpp').read_text()
 header=header.replace('#pragma once','').replace('#include "../recovered_types.h"','')
 prelude='\n'.join('signed int Reference_'+n+'(intptr_t);' for n in NAMES)
 return (FIXTURE/'harness.cpp').read_text().replace('__HEADER__',header).replace('__HELPER__',helper).replace('__REFERENCES__',prelude+'\n'+'\n'.join(references)).replace('__METHODS__','\n'.join(targets)).replace('__ADAPTERS__','\n'.join(adapters))

class UnitStackPersonageTests(unittest.TestCase):
 @unittest.skipUnless(sys.platform=='linux' and platform.machine()=='x86_64','requires Linux address mappings')
 def test_actual_methods_adapters_and_original_output(self):
  inputs,expected_output=streams();evidence=os.environ.get('CLASH95_UNIT_STACK_PERSONAGE_EVIDENCE')
  with tempfile.TemporaryDirectory(prefix='clash95-unit-stack-personage-') as temporary:
   out=Path(evidence).resolve() if evidence else Path(temporary)
   if evidence:out.mkdir(parents=True,exist_ok=False)
   (out/'probe.cpp').write_text(source_fixture());rows=[]
   for compiler in ('g++-13','clang++-18'):
    self.assertIsNotNone(shutil.which(compiler))
    for opt in ('-O0','-O2'):
     for unsigned in (False,True):
      label=compiler+opt+('-unsigned' if unsigned else '-signed')
      with self.subTest(profile=label):
       command=[compiler,'-std=gnu++20','-U_GNU_SOURCE',opt,'-fno-pie','-no-pie','-fno-exceptions','-fno-rtti','-Wall','-Wextra','-Werror','-fsanitize=undefined','-fsanitize-undefined-trap-on-error','-I',str(ROOT/'src'),str(out/'probe.cpp'),'-o',str(out/label)]
       if unsigned:command+=['-funsigned-char']
       built=subprocess.run(command,capture_output=True,text=True,timeout=60)
       (out/(label+'.build.log')).write_text(built.stdout+built.stderr)
       result={'profile':label,'command':command,'build':built.returncode};rows.append(result)
       self.assertEqual(built.returncode,0,built.stdout+built.stderr)
       ran=subprocess.run([str(out/label)],input=inputs,capture_output=True,timeout=90)
       result.update(run=ran.returncode,output_sha256=hashlib.sha256(ran.stdout).hexdigest(),stderr=ran.stderr.decode(errors='replace'))
       self.assertEqual(ran.returncode,0,result['stderr'])
       self.assertEqual(len(ran.stdout),len(expected_output))
       self.assertEqual(hashlib.sha256(ran.stdout).digest(),hashlib.sha256(expected_output).digest())
   (out/'summary.json').write_text(json.dumps({'case_count':87184,'profiles':rows},indent=2)+'\n')

if __name__=='__main__':unittest.main()
