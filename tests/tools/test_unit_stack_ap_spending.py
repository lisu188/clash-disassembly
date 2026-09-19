#!/usr/bin/env python3
"""Actual AP-spending bodies against pinned original-instruction observations.

The original fact-link call is an explicitly controlled external boundary. This
checks its input registers, call count, callback-time bytes, return propagation,
and final bytes; it does not claim to validate the CLIPS implementation.
"""
from pathlib import Path
import hashlib,json,os,platform,random,shutil,struct,subprocess,sys,tempfile,unittest

ROOT=Path(os.environ.get('CLASH95_SOURCE_ROOT',Path(__file__).resolve().parents[2])).resolve()
PROVENANCE=Path(os.environ.get('CLASH95_AP_SPENDING_PROVENANCE',Path(__file__).parent/'fixtures/unit_stack_ap_spending/provenance.json'))
NAMES=('UnitStack_SpendActionPointsClamped','UnitStack_SubtractActionPointsFloorZero','UnitStack_SpendActionPointsUnchecked')
INPUT_BYTES=832
OUTPUT_BYTES=1636

def cases():
 rng=random.Random(0x4101304101704101a0)
 amounts=(-2147483648,-2147483647,-65537,-65536,-65535,-32769,-32768,-32767,-257,-256,-255,-129,-128,-127,-2,-1,0,1,2,127,128,129,254,255,256,257,32767,65535,2147483647)
 fpbits=(0,0x8000000000000000,0x3ff4000000000000,0xc00c000000000000,0x7ff0000000000000,0xfff0000000000000,0x7ff8000000001234)
 serial=0
 for mode in range(3):
  rows=[]
  # Every alignment and sentinel position, both sides of the signed-address
  # boundary, and full-width signed extremes. Other negative type words live.
  for alignment in range(16):
   for prefix in range(11):
    for amount in amounts:
     rows.append((alignment,prefix,amount,(serial+alignment+prefix)&1,None));serial+=1
  # Every AP byte against every subtraction low byte in full ten-slot stacks.
  # Interleaved AP ordering distinguishes running-min clamp from independent
  # floor zero and unchecked byte wrapping.
  for amount in range(256):
   for first in range(0,256,10):
    rows.append(((first+amount)%16,10,amount,amount&1,first))
  for alignment,prefix,amount,edge,first in rows:
   base=(0x7ffffef0 if edge else 0x30000020)+alignment
   data=bytearray(rng.randbytes(800))
   for slot in range(10):
    at=32+6+31*slot
    unit=(-32768,-2,0,1,32,32767)[(serial+slot)%6]
    struct.pack_into('<h',data,at,-1 if slot==prefix else unit)
    data[at+8]=rng.randrange(256) if first is None else (first+slot)&255
   bits=fpbits[serial%len(fpbits)]
   header=(mode,base,amount&0xffffffff,rng.getrandbits(32),bits&0xffffffff,bits>>32,rng.getrandbits(32),serial&1)
   yield struct.pack('<8I',*header)+data
   serial+=1

def signed(value):
 return value if value<0x80000000 else value-0x100000000

def address_cases():
 # Exercise initial address addition across INT_MAX, plus negative signed-int
 # representations of valid low32 handles. Record bytes stay mapped throughout.
 rng=random.Random(0x41017080000000);serial=0
 for mode in range(3):
  for start in (0x7ffffff0,0x80000020):
   for alignment in range(16):
    for prefix in (0,1,10):
     for amount in (-2147483648,-1,0,255):
      data=bytearray(rng.randbytes(800));base=start+alignment
      for slot in range(10):
       at=32+6+31*slot
       struct.pack_into('<h',data,at,-1 if slot==prefix else (-32768,-2,0,32767)[slot%4])
       data[at+8]=(serial+slot*73)&255
      yield struct.pack('<8I',mode,base,amount&0xffffffff,rng.getrandbits(32),0,0xbff00000,rng.getrandbits(32),serial&1)+data
      serial+=1

def expected(row):
 mode,base,amount,context,lo,hi,callback_return,mutate=struct.unpack_from('<8I',row)
 data=bytearray(row[32:]);count=0;last=0;work=signed(amount)
 for slot in range(10):
  at=32+6+31*slot
  unit=struct.unpack_from('<h',data,at)[0]
  if unit==-1:last=255;break
  ap=data[at+8]
  if mode==0:
   if ap<work:work=ap
   last=(ap-work)&255;data[at+8]=last
  elif mode==1:
   if ap<=work:last=ap;data[at+8]=0
   else:last=(ap-work)&255;data[at+8]=last
  else:data[at+8]=(ap-(amount&255))&255
  count+=1
 if mode==2:
  observed=(base+6+31*count)&0xffffffff,0,0,0,0,0,0,0,0
  before=bytes(800)
 else:
  edx,ecx=((work&0xffffffff,count) if mode==0 else (count,amount))
  observed=callback_return,1,base,edx,ecx,last,context,lo,hi
  before=bytes(data)
  if mutate:data[777]^=0xa5
 return struct.pack('<9I',*observed)+before+data

def streams():
 proof=json.loads(PROVENANCE.read_text());all_inputs=[];all_outputs=[]
 for generator,key in ((cases,'measured_streams'),(address_cases,'address_boundary_streams')):
  rows=list(generator());inputs=b''.join(rows);output=b''.join(map(expected,rows));pin=proof[key]
  assert len(rows)==pin['case_count']
  for data,kind in ((inputs,'input'),(output,'output')):
   assert len(data)==pin[kind+'_bytes']
   assert hashlib.sha256(data).hexdigest()==pin[kind+'_sha256'],key+' '+kind+' differs from original measurement'
  all_inputs.append(inputs);all_outputs.append(output)
 return b''.join(all_inputs),b''.join(all_outputs)

HARNESS=r'''
#include "recovered_layout.h"
#include "units/units_api.h"
#include "strategic/strategic_api.h"
#include <sys/mman.h>
static uint32_t header[8], observed[9];
static unsigned char before[800];
signed int Rules_LinkArmyFact(clash95_unaligned_int16 *stack,int edx,int ecx,double value,char bl,DWORD context) {
 ++observed[1];observed[2]=uint32_t(uintptr_t(stack));observed[3]=uint32_t(edx);observed[4]=uint32_t(ecx);
 observed[5]=static_cast<unsigned char>(bl);observed[6]=uint32_t(context);memcpy(observed+7,&value,8);
 auto *image=(unsigned char*)uintptr_t(header[1]-32);memcpy(before,image,800);
 if(header[7])image[777]^=0xa5;
 return int(header[6]);
}
__TARGET__
int main() {
 void *normal=mmap((void*)uintptr_t(0x30000000),4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|0x100000,-1,0);
 void *edge=mmap((void*)uintptr_t(0x7ffff000),8192,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|0x100000,-1,0);
 if(normal!=(void*)uintptr_t(0x30000000)||edge!=(void*)uintptr_t(0x7ffff000))return 2;
 unsigned char input[800];
 while(fread(header,sizeof(header),1,stdin)==1) {
  if(header[0]>2||fread(input,800,1,stdin)!=1)return 3;
  auto *image=(unsigned char*)uintptr_t(header[1]-32);memcpy(image,input,800);
  memset(observed,0,sizeof(observed));memset(before,0,800);
  double value;memcpy(&value,header+4,8);int result;
  auto *stack=(__int16*)uintptr_t(header[1]);
  if(header[0]==0)result=UnitStack_SpendActionPointsClamped(stack,int(header[2]),header[3],value);
  else if(header[0]==1)result=UnitStack_SubtractActionPointsFloorZero(stack,int(header[2]),header[3],value);
  else result=UnitStack_SpendActionPointsUnchecked(int(header[1]),char(header[2]));
  observed[0]=uint32_t(result);
  if(fwrite(observed,sizeof(observed),1,stdout)!=1||fwrite(before,800,1,stdout)!=1||fwrite(image,800,1,stdout)!=1)return 4;
 }
 if(ferror(stdin)||fflush(stdout))return 5;
 return munmap(normal,4096)||munmap(edge,8192)?6:0;
}
'''

def source_fixture():
 sys.path.insert(0,str(ROOT/'tools'))
 from recovered_implementation import index_manifest_definitions
 from split_source_index import scan_definitions
 override=os.environ.get('CLASH95_AP_SPENDING_SOURCE')
 if override:
  text=Path(override).read_text();found={d.name:d for d in scan_definitions(text,set(NAMES))}
  assert set(found)==set(NAMES)
  bodies=[text[found[n].start:found[n].end] for n in NAMES]
 else:
  manifest=json.loads((ROOT/'data/recovered_sources.json').read_text())
  records={r['name']:r for r in manifest['functions'] if r['name'] in NAMES}
  assert all(r['implementation']['kind']=='free' for r in records.values()), 'Adapt this fixture to canonical methods before migration'
  indexed=index_manifest_definitions(manifest,ROOT,{r['source'] for r in records.values()})
  bodies=[]
  for name in NAMES:
   item=indexed[(name,'canonical')]
   assert item.body_sha256==records[name]['body_sha256']
   text=(ROOT/item.target.source).read_text();d=item.definition;bodies.append(text[d.start:d.end])
 return HARNESS.replace('__TARGET__','\n\n'.join(bodies))

class APSpendingTests(unittest.TestCase):
 @unittest.skipUnless(sys.platform=='linux' and platform.machine()=='x86_64','requires Linux low32 mappings')
 def test_actual_bodies_match_original_bytes_and_callback_boundary(self):
  inputs,expected_output=streams()
  evidence=os.environ.get('CLASH95_AP_SPENDING_EVIDENCE')
  with tempfile.TemporaryDirectory(prefix='clash95-ap-spending-') as temporary:
   out=Path(evidence).resolve() if evidence else Path(temporary)
   if evidence:out.mkdir(parents=True,exist_ok=False)
   (out/'probe.cpp').write_text(source_fixture());rows=[]
   for compiler in ('g++-13','clang++-18'):
    self.assertIsNotNone(shutil.which(compiler))
    for opt in ('-O0','-O2'):
     for unsigned_char in (False,True):
      label=compiler+opt+('-unsigned' if unsigned_char else '-signed')
      with self.subTest(profile=label):
       command=[compiler,'-std=gnu++20','-U_GNU_SOURCE',opt,'-fno-pie','-no-pie','-fno-exceptions','-fno-rtti',
        '-Wall','-Wextra','-Werror','-fsanitize=undefined','-fno-sanitize-recover=all',
        '-I',str(ROOT/'src'),str(out/'probe.cpp'),'-o',str(out/label)]
       if unsigned_char:command+=['-funsigned-char']
       built=subprocess.run(command,capture_output=True,text=True,timeout=60)
       (out/(label+'.build.log')).write_text(built.stdout+built.stderr)
       row={'profile':label,'command':command,'build':built.returncode};rows.append(row)
       self.assertEqual(built.returncode,0,built.stdout+built.stderr)
       ran=subprocess.run([str(out/label)],input=inputs,capture_output=True,timeout=60)
       (out/(label+'.run.log')).write_bytes(ran.stderr)
       row.update(run=ran.returncode,output_sha256=hashlib.sha256(ran.stdout).hexdigest(),output_bytes=len(ran.stdout))
       (out/'summary.json').write_text(json.dumps({'case_count':len(inputs)//INPUT_BYTES,'profiles':rows},indent=2)+'\n')
       self.assertEqual(ran.returncode,0,ran.stderr.decode(errors='replace'))
       self.assertEqual(len(ran.stdout),len(expected_output))
       if ran.stdout!=expected_output:
        first=next(i for i,(a,b) in enumerate(zip(ran.stdout,expected_output)) if a!=b)
        self.fail(str({'first_case':first//OUTPUT_BYTES,'first_offset':first%OUTPUT_BYTES}))
       print(label+': PASS',flush=True)

if __name__=='__main__':unittest.main()
