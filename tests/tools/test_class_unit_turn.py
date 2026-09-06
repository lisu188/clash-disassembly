#!/usr/bin/env python3
"""Differential gate for actual UnitTurn methods and their legacy adapters."""
from pathlib import Path
import json,os,platform,subprocess,sys,tempfile,unittest
ROOT=Path(os.environ.get('CLASH95_SOURCE_ROOT',Path(__file__).resolve().parents[2])).resolve()
FIXTURE=Path(__file__).resolve().parent/'fixtures/class_unit_turn'

class UnitTurnClassDifferentialTests(unittest.TestCase):
 def test_current_methods_and_adapters_match_repaired_reference(self):
  if platform.system()!='Linux' or platform.machine() not in ('x86_64','amd64'):
   self.skipTest('supported low32 LP64 fixture requires Linux x86-64')
  evidence=os.environ.get('CLASH95_CLASS_UNIT_TURN_EVIDENCE')
  temporary=tempfile.TemporaryDirectory(prefix='clash95-class-unit-turn-') if not evidence else None
  output=Path(temporary.name)/'results' if temporary else Path(evidence).resolve()
  try:
   result=subprocess.run([sys.executable,str(FIXTURE/'verify_unit_turn.py'),'--root',str(ROOT),'--output',str(output)],capture_output=True,text=True,timeout=240)
   self.assertEqual(result.returncode,0,result.stdout+result.stderr)
   summary=json.loads((output/'summary.json').read_text())
   self.assertTrue(summary['inputs_unchanged'])
   self.assertEqual(len(summary['profiles']),4)
   self.assertEqual(summary['expected_cases_per_profile'],{'regen':4096,'damage':6144,'turn':336})
   for profile in summary['profiles']:
    self.assertEqual(profile['run'],0)
    self.assertIn('entry_paths=method,adapter callback_and_rng_order=exact complete_bytes=exact',profile['stdout'])
  finally:
   if temporary: temporary.cleanup()
if __name__=='__main__': unittest.main()
