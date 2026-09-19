#!/usr/bin/env python3
"""Actual spent-turn functions against original-measured low32 return/full-byte cases."""
from pathlib import Path
import hashlib,importlib.util,json,os,platform,shutil,subprocess,sys,tempfile,unittest
sys.dont_write_bytecode=True
ROOT=Path(__file__).resolve().parents[2];FIXTURE=ROOT/'tests/tools/fixtures/spent_turn_repair';sys.path.insert(0,str(ROOT/'tools'))
from split_source_index import scan_definitions,body_sha256
from recovered_implementation import index_manifest_definitions
spec=importlib.util.spec_from_file_location('spent_contract',FIXTURE/'contract.py');contract=importlib.util.module_from_spec(spec);spec.loader.exec_module(contract)
class SpentTurnRepairTests(unittest.TestCase):
 @unittest.skipUnless(sys.platform=='linux' and platform.machine()=='x86_64','requires Linux low32 mappings')
 def test_actual_bodies_original_pointer_and_complete_bytes(self):
  proof=json.loads((FIXTURE/'provenance.json').read_text());measured=json.loads((FIXTURE/'original_measurement.json').read_text());manifest=json.loads((ROOT/'data/recovered_sources.json').read_text());rows={x['name']:x for x in manifest['functions']};bodies=[]
  sources={rows[item['name']]['source'] for item in proof['functions']}|{rows[item['name']]['adapter']['source'] for item in proof['functions'] if 'adapter' in rows[item['name']]};indexed=index_manifest_definitions(manifest,ROOT,sources)
  for item in proof['functions']:
   row=rows[item['name']];self.assertEqual(row['original_address'],item['original_address'])
   if row['implementation']['kind']=='free':self.assertEqual(row['body_sha256'],item['after_body_sha256'])
   for role in ['canonical']+(['adapter'] if 'adapter' in row else []):
    resolved=indexed[item['name'],role];text=(ROOT/resolved.target.source).read_text();d=resolved.definition;self.assertEqual(resolved.body_sha256,row['body_sha256'] if role=='canonical' else row['adapter']['body_sha256']);bodies.append(text[d.start:d.end])
   reference=(FIXTURE/'references'/(item['name']+'.cpp')).read_bytes();self.assertEqual(hashlib.sha256(reference).hexdigest(),item['reference_file_sha256'])
  inputs=b''.join(contract.cases());original=b''.join(contract.expected(inputs[i:i+808]) for i in range(0,len(inputs),808));expected=b''.join(contract.expected(inputs[i:i+808],8) for i in range(0,len(inputs),808))
  streams=measured['measured_streams'];self.assertEqual(len(inputs)//808,streams['case_count']);self.assertEqual(hashlib.sha256(inputs).hexdigest(),streams['input_sha256']);self.assertEqual(hashlib.sha256(original).hexdigest(),streams['output_sha256'])
  evidence=os.environ.get('CLASH95_SPENT_TURN_EVIDENCE')
  with tempfile.TemporaryDirectory(prefix='clash95-spent-turn-') as temporary:
   out=Path(evidence).resolve() if evidence else Path(temporary)
   if evidence:out.mkdir(parents=True,exist_ok=False)
   source=out/'probe.cpp';source.write_text((FIXTURE/'harness.cpp').read_text().replace('__BODIES__','\n'.join(bodies)));results=[]
   try:
    for compiler in ['g++-13','clang++-18']:
     self.assertIsNotNone(shutil.which(compiler))
     for opt in ['-O0','-O2']:
      for unsigned in [False,True]:
       label=compiler+opt+('-unsigned' if unsigned else '-signed');binary=out/label
       command=[compiler,'-std=gnu++20','-U_GNU_SOURCE',opt,'-fno-pie','-no-pie','-fno-exceptions','-fno-rtti','-Wall','-Wextra','-Werror','-fsanitize=undefined','-fno-sanitize-recover=all','-I',str(ROOT/'src'),str(source),'-o',str(binary)]
       if unsigned:command+=['-funsigned-char']
       built=subprocess.run(command,capture_output=True,text=True,timeout=90);(out/(label+'.build.log')).write_text(built.stdout+built.stderr);result={'profile':label,'command':command,'build':built.returncode};results.append(result);self.assertEqual(built.returncode,0,built.stderr)
       ran=subprocess.run([str(binary)],input=inputs,capture_output=True,timeout=90);result.update(exit=ran.returncode,output_sha256=hashlib.sha256(ran.stdout).hexdigest(),stderr=ran.stderr.decode(errors='replace'));self.assertEqual(ran.returncode,0,result['stderr']);self.assertEqual(len(ran.stdout),len(expected));self.assertEqual(hashlib.sha256(ran.stdout).digest(),hashlib.sha256(expected).digest())
   finally:(out/'summary.json').write_text(json.dumps({'case_count':streams['case_count'],'native_pointer_width':8,'profiles':results},indent=2)+'\n')
if __name__=='__main__':unittest.main()
