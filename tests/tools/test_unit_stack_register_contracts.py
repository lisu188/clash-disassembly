#!/usr/bin/env python3
"""Actual target bodies, original-register contracts, and explicit callback seams.

Public provenance pins the original-measured input and output streams before
this model can supply expectations. The private oracle is supplementary.
Dependencies are spies; this does not claim full fact/compaction equivalence.
"""
from pathlib import Path
import hashlib,json,os,platform,random,shutil,struct,subprocess,sys,tempfile,unittest
ROOT=Path(os.environ.get('CLASH95_SOURCE_ROOT',Path(__file__).resolve().parents[2]))
sys.path.insert(0,str(ROOT/'tools'))
from split_source_index import scan_definitions
from recovered_implementation import index_manifest_definitions
override=os.environ.get('CLASH95_REGISTER_CONTRACT_SOURCE')
SOURCE=Path(override) if override else None
PROVENANCE=Path(__file__).resolve().parent/'fixtures/unit_stack_register_contracts/provenance.json'
NAMES={'UnitStack_CalcMilitaryStrength','UnitStack_NormalizePeasantCargo'}
PAYLOAD=800
MASK=0xffffffff
EVENTS=4
INPUT_SIZE=32+PAYLOAD
OUTPUT_SIZE=8+EVENTS*32+PAYLOAD

def fnv(data):
 value=2166136261
 for byte in data:value=((value^byte)*16777619)&MASK
 return value

def contract_output(row,payload):
 mode,token,count,ap,result,context,lo,hi=row
 data=bytearray(payload);events=[]
 def event(kind,a=0,b=0,c=0,double=False):
  events.append([kind,a&MASK,b&MASK,c&MASK,fnv(data),lo if double else 0,hi if double else 0,0])
 if mode==0:
  event(3,token,count)
  event(5,(token+6)&MASK,count,0)
 else:
  start=32+token
  types=[struct.unpack_from('<h',data,start+6+31*i)[0] for i in range(10)]
  prefix=next((i for i,t in enumerate(types) if t==-1),10)
  cargo=[i for i in range(prefix) if types[i]==32]
  quantity=sum(struct.unpack_from('<b',data,start+6+31*i+9)[0] for i in cargo)
  rebuild=100*(len(cargo)-1)>quantity
  event(1)
  if rebuild:
   for i in cargo:struct.pack_into('<h',data,start+6+31*i,-1)
   event(2,0,prefix*31,double=True)
   event(3,0,count)
   full=max(0,int(quantity/100))
   assert count+full<10
   remainder=quantity-int(quantity/100)*100
   for n,value in enumerate([100]*full+[remainder]):
    base=start+6+31*(count+n)
    struct.pack_into('<h',data,base,32)
    data[base+8:base+12]=bytes([ap,value&255,0,10])
   struct.pack_into('<h',data,start+6+31*(count+full+1),-1)
   event(4,0,100,31*(count+full+1),double=True)
  else:
   event(4,0,prefix,context,double=True)
 assert len(events)<=EVENTS
 return struct.pack('<II',result,len(events))+b''.join(struct.pack('<8I',*e) for e in events)+bytes((EVENTS-len(events))*32)+data

def cases():
 seed=random.Random(0x4121d0412be0)
 result_values=[0,0x87654321,0x7fffffff]
 for count in range(11):
  for pointer in [0,1,0x10000001,0x7ffffff9,0x7ffffffc,0x80000000,0xfffffff9,0xfffffffa,0xffffffff]:
   for result in result_values:
    yield (0,pointer,count,0,result,0,0,0),bytes(seed.randrange(256) for _ in range(PAYLOAD))
 # Explicit boundary rows plus deterministic broad mixtures, including opaque
 # occupied slots after a sentinel (the target must stop scanning at sentinel).
 patterns=[[],[(2,0)],[(32,0)],[(32,-1)],[(32,-128)],[(32,127)],
   [(32,49),(32,50)],[(32,50),(32,50)],[(32,50),(32,51)],
   [(32,100),(32,0),(32,0)],[(32,100)]*10,[(32,0)]*10,
   [(32,-128)]*10,[(32,127)]*10,[(2,0),(32,50),(3,0),(32,49)],
   [(32,0),(-1,0),(32,-128)]]
 for n in range(180):
  patterns.append([(seed.choice([2,17,32,32]),seed.choice([-128,-101,-100,-99,-1,0,1,49,50,99,100,101,127])) for _ in range(seed.randrange(11))])
 doubles=[(0,0),(0,0x80000000),(0,0x7ff00000),(0x12345678,0x7ff81234)]
 for pattern_index,pattern in enumerate(patterns):
  for alignment in range(8):
   for ap in (0,128,255):
    data=bytearray(seed.randrange(256) for _ in range(PAYLOAD));start=32+alignment
    for i in range(10):
     unit,quantity=pattern[i] if i<len(pattern) else (-1,0)
     struct.pack_into('<h',data,start+6+31*i,unit)
     data[start+6+31*i+9]=quantity&255
    prefix=next((i for i,item in enumerate(pattern) if item[0]==-1),len(pattern))
    cargo=[q for t,q in pattern[:prefix] if t==32]
    total=sum(cargo);full=max(0,int(total/100))
    count=seed.randrange(max(1,10-full))
    lo,hi=doubles[(pattern_index+alignment)%len(doubles)]
    yield (1,alignment,count,ap,result_values[pattern_index%3],0x12345678,lo,hi),bytes(data)

HARNESS=r"""
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "units/UnitStack.hpp"
#include "units/units_internal.h"
#include "strategic/strategic_api.h"
#include "recovered_legacy_imports.h"
static uint32_t row[8];
static unsigned char input[800], actual[800], expected[936];
static unsigned char *stack_address;
static uint32_t trace[4][8], trace_count;
static uint32_t bits(double value,int word) {
  uint32_t raw[2]; memcpy(raw,&value,8); return raw[word];
}
static uint32_t fnv() {
  uint32_t hash=2166136261u;
  for(unsigned char byte:actual)hash=(hash^byte)*16777619u;
  return hash;
}
static void event(uint32_t kind,uint32_t a=0,uint32_t b=0,uint32_t c=0,
                  double value=0.0,bool with_double=false) {
  if(trace_count>=4)abort();
  uint32_t *out=trace[trace_count++];
  out[0]=kind;out[1]=a;out[2]=b;out[3]=c;out[4]=fnv();
  out[5]=with_double?bits(value,0):0;
  out[6]=with_double?bits(value,1):0;out[7]=0;
}
static uint32_t offset(uintptr_t value) {
  return uint32_t(value)-uint32_t(uintptr_t(stack_address));
}
signed int Unit_GetSquadCount(intptr_t value) {
  event(3,row[0]?offset(value):uint32_t(value),row[2]);return row[2];
}
signed int UnitStack_GetMinCurrentActionPoints(intptr_t value) {
  event(1,offset(value));return row[3];
}
// Original-stream dependency seam. The separate class differential executes
// the actual AP canonical method; this pinned corpus controls its return value.
signed int clash95::UnitStack::UnitStack_GetMinCurrentActionPoints() const {
  event(1,offset(address_));return row[3];
}
signed int Unit_CompactSquad(__int16 *value,int context,double time) {
  event(2,offset(uintptr_t(value)),offset(uint32_t(context)),0,time,true);
  return 0x31415926;
}
int UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(char *value,int count,int bonus) {
  event(5,uint32_t(uintptr_t(value)),count,bonus);return int(row[4]);
}
signed int Rules_SyncArmyFactStrength(__int16 *value,int unused_id,int unused_context,
                                     char scan_count,DWORD context,double time) {
  (void)unused_id; (void)unused_context;
  const uint32_t normalized=context==row[5]?context:offset(context);
  event(4,offset(uintptr_t(value)),uint8_t(scan_count),normalized,time,true);
  return int(row[4]);
}
__TARGETS__
int main(int argc,char **argv) {
  if(argc!=3)return 2;
  FILE *cases=fopen(argv[1],"rb"),*expect=fopen(argv[2],"rb");
  if(!cases||!expect)return 3;
  unsigned index=0;
  while(fread(row,sizeof(row),1,cases)==1) {
    if(fread(input,sizeof(input),1,cases)!=1||fread(expected,sizeof(expected),1,expect)!=1)return 4;
    for(int route=0;route<__ROUTES__;++route) {
    memcpy(actual,input,sizeof(actual));memset(trace,0,sizeof(trace));trace_count=0;
    stack_address=actual+32+(row[0]?row[1]:0);
    if(uintptr_t(actual)+sizeof(actual)>INT32_MAX)return 5;
    double time;memcpy(&time,row+6,8);
    int result=__INVOKE__;
    unsigned char output[936];
    const uint32_t returned=uint32_t(result);
    memcpy(output,&returned,4);memcpy(output+4,&trace_count,4);
    memcpy(output+8,trace,sizeof(trace));memcpy(output+136,actual,sizeof(actual));
    if(memcmp(output,expected,sizeof(output))) {
      for(unsigned i=0;i<sizeof(output);++i)if(output[i]!=expected[i]) {
        fprintf(stderr,"case=%u mode=%u alignment_or_pointer=%u output_offset=%u actual=%u expected=%u\n",
                index,row[0],row[1],i,output[i],expected[i]);break;
      }
      return 6;
    }
    }
    ++index;
  }
  if(ferror(cases)||ferror(expect)||fgetc(expect)!=EOF)return 7;
  fclose(cases);fclose(expect);printf("%u cases pass\n",index);return 0;
}
"""

def extracted_fixture():
 if SOURCE is not None:
  # Explicit scratch-only candidate/negative-control override. Normal production
  # resolution below never searches a presumed adapter source by free name.
  source=SOURCE.read_text()
  definitions=list(scan_definitions(source,NAMES))
  assert {d.name for d in definitions}==NAMES and len(definitions)==2
  snippets=[source[d.start:d.end] for d in definitions]
 else:
  manifest=json.loads((ROOT/'data/recovered_sources.json').read_text())
  records={r['name']:r for r in manifest['functions'] if r['name'] in NAMES}
  assert set(records)==NAMES, 'register-contract identity missing from manifest'
  originals={r['name']:r for r in json.loads(PROVENANCE.read_text())['functions']}
  assert set(originals)==NAMES
  for name,record in records.items():
   assert int(record['original_address'],16)==int(originals[name]['address'],16), name+': original identity changed'
  sources={r['source'] for r in records.values()}
  sources.update(r['adapter']['source'] for r in records.values() if r.get('adapter'))
  indexed=index_manifest_definitions(manifest,ROOT,sources)
  snippets=[]
  for name in sorted(NAMES):
   record=records[name]
   for role in ('canonical','adapter') if record.get('adapter') else ('canonical',):
    resolved=indexed[(name,role)]
    expected=record['body_sha256'] if role=='canonical' else record['adapter']['body_sha256']
    assert resolved.body_sha256==expected, name+': manifest body hash drift'
    expected_name=record['implementation']['qualified_name'] if role=='canonical' else name
    assert resolved.target.name==expected_name
    source=(ROOT/resolved.target.source).read_text();d=resolved.definition
    snippets.append(source[d.start:d.end])
 free='row[0]?UnitStack_NormalizePeasantCargo((__int16 *)stack_address,row[5],time):UnitStack_CalcMilitaryStrength(int(row[1]))'
 classed=SOURCE is None and all(records[n].get('adapter') for n in NAMES)
 direct='row[0]?clash95::UnitStack((intptr_t)stack_address).UnitStack_NormalizePeasantCargo(row[5],time):clash95::UnitStack(int(row[1])).UnitStack_CalcMilitaryStrength()'
 invoke='route?('+direct+'):('+free+')' if classed else free
 return HARNESS.replace('__TARGETS__','\n'.join(snippets)).replace('__ROUTES__','2' if classed else '1').replace('__INVOKE__',invoke)

def verify_original_streams(inputs,expected,count):
 provenance=json.loads(PROVENANCE.read_text())
 assert provenance['schema_version']==1
 streams=provenance['measured_streams']
 assert count==streams['case_count']==5001, 'original corpus count changed'
 assert len(inputs)==streams['input_bytes'], 'original input stream length changed'
 assert len(expected)==streams['output_bytes'], 'original output stream length changed'
 assert hashlib.sha256(inputs).hexdigest()==streams['input_sha256'], (
  'input corpus differs from original-measured stream; new original evidence is required')
 assert hashlib.sha256(expected).hexdigest()==streams['output_sha256'], (
  'contract model differs from original-measured output stream; new original evidence is required')

def write_inputs(work):
 inputs=bytearray();expected=bytearray();count=0
 for row,payload in cases():
  inputs+=struct.pack('<8I',*row)+payload
  expected+=contract_output(row,payload);count+=1
 verify_original_streams(inputs,expected,count)
 (work/'cases.bin').write_bytes(inputs);(work/'expected.bin').write_bytes(expected)
 return count

class RegisterContractTests(unittest.TestCase):
 @unittest.skipUnless(sys.platform=='linux' and platform.machine()=='x86_64','requires Linux low32 non-PIE test addresses')
 def test_original_register_contracts_and_full_bytes(self):
  compilers=('g++-13','clang++-18')
  for compiler in compilers:
   self.assertIsNotNone(shutil.which(compiler),'required supported compiler missing: '+compiler)
  with tempfile.TemporaryDirectory(prefix='clash95-register-contracts-') as temporary:
   work=Path(temporary);write_inputs(work);(work/'probe.cpp').write_text(extracted_fixture())
   for compiler in compilers:
    for optimization in ('-O0','-O2'):
     for unsigned_char in (False,True):
      with self.subTest(compiler=compiler,optimization=optimization,unsigned_char=unsigned_char):
       cmd=[compiler,'-std=gnu++20','-U_GNU_SOURCE','-I',str(ROOT/'src'),optimization,'-fno-pie','-no-pie','-Wall','-Wextra','-Werror',
         '-fsanitize=undefined','-fsanitize-undefined-trap-on-error']
       if unsigned_char:cmd+=['-funsigned-char']
       cmd+=[str(work/'probe.cpp'),'-o',str(work/'probe')]
       built=subprocess.run(cmd,text=True,capture_output=True,timeout=60)
       self.assertEqual(built.returncode,0,built.stderr)
       run=subprocess.run([str(work/'probe'),str(work/'cases.bin'),str(work/'expected.bin')],
         text=True,capture_output=True,timeout=20)
       self.assertEqual(run.returncode,0,run.stdout+run.stderr)

if __name__=='__main__':unittest.main()
