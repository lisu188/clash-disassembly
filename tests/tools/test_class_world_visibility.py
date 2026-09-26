"""Live arena binding and recursive callback rebinding on actual source."""
from pathlib import Path
import shutil,subprocess,sys,tempfile,unittest
ROOT=Path(__file__).resolve().parents[2]
class WorldVisibilityBindingTest(unittest.TestCase):
    def check_compiler(self,compiler):
        if shutil.which(compiler) is None:self.skipTest("required compiler unavailable: "+compiler)
        with tempfile.TemporaryDirectory(prefix="clash95-world-binding-") as temp:
            command=[sys.executable,str(ROOT/"tests/tools/fixtures/class_world_visibility/verify_world_visibility.py"),"--root",str(ROOT),"--output",str(Path(temp)/"result"),"--kind","binding","--compiler",compiler]
            result=subprocess.run(command,capture_output=True,text=True,timeout=240)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)
    def test_gcc_binding_lifecycle(self):self.check_compiler("g++-13")
    def test_clang_binding_lifecycle(self):self.check_compiler("clang++-18")
if __name__=="__main__":unittest.main()
