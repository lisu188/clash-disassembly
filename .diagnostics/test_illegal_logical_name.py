import hashlib
import re
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM = (ROOT / 'clash95.asm').read_text(encoding='latin-1')
TARGET_PATH = ROOT / 'src/clips/0049E930_0049FF80_clips_006.cpp'
CALLER_PATH = ROOT / 'src/clips/0049CE10_0049E8D0_clips_005.cpp'
EXPECTED_INSN_SHA = '2acf6730a476c7155cf18a5e527b669b17e9a6a028f9c2b8b7ac19f26bb7ccee'
CALLERS = {
    'sub_49E250': ('Rules_HostPrintout', 'aPrintout'),
    'sub_49E3E0': ('Rules_HostRead', 'aRead'),
    'sub_49E650': ('Rules_HostOpen', 'aOpen'),
    'sub_49E820': ('Rules_HostClose', 'aClose'),
    'sub_49E930': ('Rules_HostFormat', 'aFormat'),
    'sub_49F120': ('Rules_HostReadline', 'aReadline'),
}

def procedure(name):
    m = re.search(rf'(?ms)^\s*{name}\s+proc\b.*?^\s*{name}\s+endp\b', ASM)
    if not m:
        raise AssertionError(name)
    return m.group(0)

def function(text, name):
    pattern = re.compile(
        rf'(?m)^[ \t]*[A-Za-z_][A-Za-z0-9_ \t:*&]*\b{re.escape(name)}\s*\([^;\n]*\)\s*$'
    )
    matches = list(pattern.finditer(text))
    if len(matches) != 1:
        raise AssertionError(f'{name}: expected one definition, found {len(matches)}')
    match = matches[0]
    line = match.start()
    brace = text.find('{', match.end())
    if brace < 0 or text[match.end():brace].strip():
        raise AssertionError(f'{name}: malformed definition')
    depth = 0
    for j in range(brace, len(text)):
        if text[j] == '{':
            depth += 1
        elif text[j] == '}':
            depth -= 1
            if depth == 0:
                return text[line:j+1]
    raise AssertionError(name)

def normalized_instructions(proc):
    out = []
    for line in proc.splitlines()[1:-1]:
        code = line.split(';', 1)[0].strip()
        if not code or code.endswith(':'):
            continue
        out.append(re.sub(r'\s+', ' ', code))
    return out

class IllegalLogicalNameRecoveryTests(unittest.TestCase):
    def test_original_target_contract_is_pinned(self):
        insn = normalized_instructions(procedure('sub_49F310'))
        self.assertEqual(hashlib.sha256('\n'.join(insn).encode()).hexdigest(), EXPECTED_INSN_SHA)
        self.assertEqual(insn, [
            'push ebx','push ecx','push edx','mov ecx, eax','mov edx, 1',
            'mov eax, offset aIofun','xor ebx, ebx','call sub_4859A0',
            'mov edx, offset aIllegalLogical','mov eax, ds:off_51A614','call Output_Write',
            'mov eax, ds:off_51A614','mov edx, ecx','call Output_Write',
            'mov edx, offset aFunction_','mov eax, ds:off_51A614','call Output_Write',
            'pop edx','pop ecx','pop ebx','retn'])

    def test_original_callers_supply_exact_function_names(self):
        for proc, (_, symbol) in CALLERS.items():
            with self.subTest(proc=proc):
                body = procedure(proc)
                self.assertRegex(body, rf'mov\s+eax,\s+offset\s+{symbol}\b[^\n]*\n\s*call\s+sub_49F310\b')

    def test_production_signature_body_and_callers_match_evidence(self):
        target = TARGET_PATH.read_text()
        callers = CALLER_PATH.read_text()
        body = function(target, 'Rules_ReportIllegalLogicalName')
        self.assertIn('Rules_ReportIllegalLogicalName(int functionName)', body)
        self.assertNotRegex(body, r'\bv[012]\b')
        self.assertEqual(body.count('functionName'), 5)
        for _, (fn, symbol) in CALLERS.items():
            source = target if fn in {'Rules_HostFormat','Rules_HostReadline'} else callers
            fbody = function(source, fn)
            self.assertIn(f'Rules_ReportIllegalLogicalName((int)(intptr_t){symbol});', fbody)
            self.assertEqual(fbody.count('Rules_ReportIllegalLogicalName('), 1)

    def _compile_and_run(self, compiler, opt, char_mode, body):
        harness = r'''
#include <cstdint>
#include <climits>
char aIofun[] = "IOFUN";
char aIllegalLogical[] = "Illegal logical name used for ";
char aFunction_[] = " function.\n";
char route0[] = "r0", route1[] = "r1", route2[] = "r2", route3[] = "r3";
char *g_IO_LogicalNameTable_WError[5] = {route0, 0, 0, 0, 0};
static int currentName, writes, failed;
static int low(const void *p) { return (int)(intptr_t)p; }
signed int Rules_PrintErrorID(int module, int code, int newline) {
  if (module != low(aIofun) || code != 1 || newline != 0 || writes != 0) failed = 1;
  g_IO_LogicalNameTable_WError[0] = route1;
  return -17;
}
int Output_Write(int logical, int text, int context) {
  int expectedRoute = 0;
  if (writes == 0) expectedRoute = low(route1);
  else if (writes == 1) expectedRoute = low(route2);
  else if (writes == 2) expectedRoute = low(route3);
  else failed = 1;
  if (logical != expectedRoute || context != currentName) failed = 1;
  if (writes == 0 && text != low(aIllegalLogical)) failed = 1;
  if (writes == 1 && text != currentName) failed = 1;
  if (writes == 2 && text != low(aFunction_)) failed = 1;
  ++writes;
  g_IO_LogicalNameTable_WError[0] = writes == 1 ? route2 : route3;
  return 700 + writes;
}
''' + body + r'''
int main() {
  const int cases[] = {0,1,-1,127,128,-128,255,256,INT_MAX,INT_MIN,0x12345678};
  for (int value : cases) {
    currentName = value; writes = 0; failed = 0; g_IO_LogicalNameTable_WError[0] = route0;
    int result = Rules_ReportIllegalLogicalName(value);
    if (failed || writes != 3 || result != 703) return 10;
  }
  for (int value = -128; value <= 127; ++value) {
    currentName = value; writes = 0; failed = 0; g_IO_LogicalNameTable_WError[0] = route0;
    if (Rules_ReportIllegalLogicalName(value) != 703 || failed || writes != 3) return 11;
  }
  return 0;
}
'''
        with tempfile.TemporaryDirectory() as td:
            src = Path(td) / 'fixture.cpp'
            exe = Path(td) / 'fixture'
            src.write_text(harness)
            cmd = [compiler, '-std=gnu++20', opt, char_mode, '-Wall','-Wextra','-Wpedantic','-Werror',
                   '-fno-exceptions','-fno-rtti','-fsanitize=undefined','-fno-sanitize-recover=all',str(src),'-o',str(exe)]
            built = subprocess.run(cmd, capture_output=True, text=True)
            self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
            ran = subprocess.run([str(exe)], capture_output=True, text=True)
            return ran.returncode, ran.stdout + ran.stderr

    def test_actual_body_runs_in_supported_compiler_profiles(self):
        body = function(TARGET_PATH.read_text(), 'Rules_ReportIllegalLogicalName')
        compilers = [c for c in (shutil.which('g++-13') or shutil.which('g++'), shutil.which('clang++-18') or shutil.which('clang++')) if c]
        compilers = list(dict.fromkeys(compilers))
        self.assertTrue(compilers)
        for compiler in compilers:
            for opt in ('-O0','-O2'):
                for char_mode in ('-fsigned-char','-funsigned-char'):
                    with self.subTest(compiler=compiler,opt=opt,char_mode=char_mode):
                        rc, out = self._compile_and_run(compiler,opt,char_mode,body)
                        self.assertEqual(rc, 0, out)

    def test_runtime_fixture_rejects_semantic_mutations(self):
        body = function(TARGET_PATH.read_text(), 'Rules_ReportIllegalLogicalName')
        compiler = shutil.which('g++-13') or shutil.which('g++') or shutil.which('clang++-18') or shutil.which('clang++')
        mutations = [
            body.replace('Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, functionName);',
                         'Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalLogical, functionName);'),
            body.replace('(int)(intptr_t)aIllegalLogical, functionName);', '(int)(intptr_t)aIllegalLogical, 0);', 1),
            body.replace('return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_, functionName);',
                         'Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunction_, functionName); return 0;'),
        ]
        self.assertEqual(len(set(mutations)), 3)
        for i, mutated in enumerate(mutations):
            with self.subTest(mutation=i):
                rc, _ = self._compile_and_run(compiler,'-O0','-fsigned-char',mutated)
                self.assertNotEqual(rc, 0)

if __name__ == '__main__':
    unittest.main()
