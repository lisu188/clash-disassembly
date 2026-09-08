from pathlib import Path
import errno
import hashlib
import itertools
import json
import os
import platform
import re
import subprocess
import sys
import tempfile
import unittest

from test_construct_code_file import ENTRY32, ENTRY64, compilers

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from split_source_index import body_sha256, scan_definitions

SOURCE_A = ROOT / 'src/clips/00481720_00482D40_clips_001.cpp'
SOURCE_B = ROOT / 'src/clips/004849EE_0048667D_clips_003.cpp'
NAMES = ['Rules_PrintLongInteger', 'Rules_PrintErrorID',
         'Rules_OpenFileErrorMessage', 'Rules_ReportSystemError']
HASHES = {
    'sub_4818C0': '7d838993a1fc80c10972ce7809a3c61cbf299860795a641c4bab73847515e5c0',
    'sub_485C80': 'b1f782c854d0952ddd8f2c7fde8975f210fb8df6cece64972c0f1fb05f894077',
    'sub_4859A0': '431c324120c99c245e704d04c01e4dd7dc97845e06df77fe8cdfec3eef3c5251',
    'sub_485770': '142510c48ccb152a44806cd31b4ac74bccf8fc758b30910c84c165b46e734291',
}
STRINGS = {
    'aArgacces': 'ARGACCES', 'aPrntutil': 'PRNTUTIL', 'aFunction': 'Function ',
    'aWasUnableToOpe': ' was unable to open file ', 'aDotNewline_FileError': '.\n',
    'asc_503EBC': '[', 'asc_503EF0': '\n', 'asc_503EF4': '] ',
    'aClipsSystemErr': '\n*** CLIPS SYSTEM ERROR ***\n', 'aId': 'ID = ',
    'aClipsDataStruc': 'CLIPS data structures are in an inconsistent or corrupted state.\n',
    'aThisErrorMayHa': 'This error may have occurred from errors in user defined code.\n',
    'asc_504060': '**************************\n',
}
INPUTS = ['', 'constructs-to-c', 'CONSCOMP', 'name with spaces', '%s%ld', 'x' * 80]
FILES = ['', 'output.c', '../path with spaces/unit.c', '%s_%d.c', 'z' * 100]
IDS = [-2147483648, -1, 0, 1, 3, 5, 2147483647]
CASES = list(itertools.product(range(256), range(2), range(3), range(3)))


def expected(case):
    index, kind, effects, result_mode = case
    name = INPUTS[index % len(INPUTS)]
    filename = FILES[index % len(FILES)]
    route = index & 1
    count = 0
    lines = []

    def write(value):
        nonlocal route, count, name, filename
        lines.append(f'W|{route}|{len(value)}:{value}\n')
        count += 1
        if effects == 1:
            route ^= 1
        if effects == 2 and count == 1:
            name, filename = 'changed-name', 'changed-file.c'

    def number(value):
        lines.append(f'F|{value}\n')
        write(str(value))

    if kind:
        write('\n')
    write('[')
    write('PRNTUTIL' if kind else 'ARGACCES')
    number(3 if kind else 2)
    write('] ')
    if kind:
        write(STRINGS['aClipsSystemErr'])
        write('ID = ')
        write(name)
        number(IDS[index % len(IDS)])
        write('\n')
        write(STRINGS['aClipsDataStruc'])
        write(STRINGS['aThisErrorMayHa'])
        write(STRINGS['asc_504060'])
    else:
        write('Function ')
        write(name)
        write(' was unable to open file ')
        write(filename)
        write('.\n')
    lines.append(f'R|{(result_mode + count - 1) % 3}|{count}|{route}\n')
    return ''.join(lines).encode()


EXPECTED = b''.join(map(expected, CASES))
EXPECTED_SHA256 = '10441056a6f01f73150715715e4fa6b5a97a6ba795917ac9bbc6a299fe7b082e'


def procedures():
    text = (ROOT / 'clash95.asm').read_text()
    return {name: re.search(r'^' + name + r'\s+proc\b.*?^' + name + r'\s+endp',
                           text, re.M | re.S).group() for name in HASHES}


def production():
    sources = {SOURCE_A: SOURCE_A.read_text(), SOURCE_B: SOURCE_B.read_text()}
    bodies = []
    for name in NAMES:
        text = sources[SOURCE_A if name == 'Rules_OpenFileErrorMessage' else SOURCE_B]
        definition, = scan_definitions(text, {name})
        bodies.append(text[definition.start:definition.end])
    return '\n'.join(bodies)


def constants():
    text = (ROOT / 'src/state/00000000_0054FFFF_recovered_state.cpp').read_text()
    return '\n'.join(re.search(r'^char ' + name + r'\[\d+\] = .*?;$', text, re.M).group()
                     for name in STRINGS)


PRELUDE = r'''
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef unsigned char _BYTE;
#define __fastcall
#define CLASH95_CLIPS_LOCAL_DATA_SYMBOL(a,b)
#define CLASH95_UNUSED __attribute__((unused))
extern "C" {
void *memcpy(void *destination, const void *source, __SIZE_TYPE__ size) {
  volatile unsigned char *out = (volatile unsigned char *)destination;
  const volatile unsigned char *in = (const volatile unsigned char *)source;
  for (__SIZE_TYPE__ i = 0; i < size; ++i) out[i] = in[i];
  return destination;
}
char route_a[] = "werror";
char route_b[] = "werror-alt";
char *g_IO_LogicalNameTable_WError[5] = {route_a};
char aLd_0[] = "%ld";
CONSTANTS
}
alignas(256) static char name_storage[512];
alignas(256) static char file_storage[512];
static char *current_name;
static char *current_file;
static int effects, result_mode, write_count, route;
static char buffer[4096];
static unsigned int used;
static void put(char c) {
  if (used == sizeof(buffer)) __builtin_trap();
  buffer[used++] = c;
}
static void text(const char *s) { while (*s) put(*s++); }
static char *copy(char *out, const char *s) {
  while (*s) *out++ = *s++;
  *out = 0;
  return out;
}
static void number(int value) {
  unsigned int n = (unsigned int)value;
  if (value < 0) { put('-'); n = 0u - n; }
  char digits[11]; unsigned int count = 0;
  do { digits[count++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (count) put(digits[--count]);
}
static void flush() {
  long result;
#if __SIZEOF_POINTER__ == 8
  asm volatile("syscall" : "=a"(result) : "0"(1L), "D"(1L), "S"(buffer), "d"((long)used) : "rcx", "r11", "memory", "cc");
#else
  asm volatile("int $0x80" : "=a"(result) : "0"(4), "b"(1), "c"(buffer), "d"(used) : "memory", "cc");
#endif
  if (result != (long)used) __builtin_trap();
  used = 0;
}
extern "C" int hook_output(int logical, int string) {
  const char *s = (const char *)(uintptr_t)(unsigned int)string;
  int destination = logical == (int)(intptr_t)route_a ? 0 : logical == (int)(intptr_t)route_b ? 1 : -1;
  if (destination < 0 || !s) __builtin_trap();
  int size = 0;
  while (s[size]) ++size;
  text("W|"); number(destination); put('|'); number(size); put(':'); text(s); put('\n');
  int result = (result_mode + write_count++) % 3;
  if (effects == 1) {
    route ^= 1;
    g_IO_LogicalNameTable_WError[0] = route ? route_b : route_a;
  }
  if (effects == 2 && write_count == 1) {
    copy(current_name, "changed-name"); copy(current_file, "changed-file.c");
  }
  return result;
}
extern "C" int hook_sprintf(char *out, const char *format, int value) {
  if (format[0] != '%' || format[1] != 'l' || format[2] != 'd' || format[3]) __builtin_trap();
  text("F|"); number(value); put('\n');
  char *begin = out;
  unsigned int n = (unsigned int)value;
  if (value < 0) { *out++ = '-'; n = 0u - n; }
  char digits[11]; unsigned int count = 0;
  do { digits[count++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (count) *out++ = digits[--count];
  *out = 0;
  return (int)(out - begin);
}
#ifndef ORIGINAL
static int sprintf_(char *out, const char *format, int value) { return hook_sprintf(out, format, value); }
static int Output_Write(int logical, int string, int) { return hook_output(logical, string); }
#endif
'''

MAIN = r'''
#ifdef ORIGINAL
extern "C" int original_call(int, int, int);
#else
static int original_call(int kind, int name, int value) {
  return kind ? Rules_ReportSystemError(name, value) : Rules_OpenFileErrorMessage(name, value);
}
#endif
extern "C" int fixture_main() {
  const char *inputs[] = INPUTS;
  const char *files[] = FILES;
  const int ids[] = {-2147483647-1, -1, 0, 1, 3, 5, 2147483647};
  for (int index = 0; index < 256; ++index)
    for (int kind = 0; kind < 2; ++kind)
      for (effects = 0; effects < 3; ++effects)
        for (result_mode = 0; result_mode < 3; ++result_mode) {
          current_name = name_storage + index;
          current_file = file_storage + ((index * 73) & 255);
          if ((uintptr_t)current_name > 0x7fffffff || (uintptr_t)current_file > 0x7fffffff) __builtin_trap();
          copy(current_name, inputs[index % 6]); copy(current_file, files[index % 5]);
          write_count = 0; route = index & 1;
          g_IO_LogicalNameTable_WError[0] = route ? route_b : route_a;
          int result = original_call(kind, (int)(intptr_t)current_name, kind ? ids[index % 7] : (int)(intptr_t)current_file);
          text("R|"); number(result); put('|'); number(write_count); put('|'); number(route); put('\n');
          flush();
        }
  return 0;
}
'''

HOOKS = r'''
.global original_call
original_call:
  push ebp
  push ebx
  push esi
  push edi
  mov eax, [esp+24]
  mov edx, [esp+28]
  mov ecx, 0x76543210
  cmp DWORD PTR [esp+20], 0
  jne system_call
  call sub_4818C0
  jmp end_call
system_call:
  call sub_485C80
end_call:
  pop edi
  pop esi
  pop ebx
  pop ebp
  ret
Output_Write:
  push ecx
  push edx
  push ebx
  push esi
  push edi
  push ebp
  push edx
  push eax
  call hook_output
  add esp, 8
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret
sprintf_:
  push ecx
  push edx
  push ebx
  push esi
  push edi
  push ebp
  mov ebp, esp
  push DWORD PTR [ebp+36]
  push DWORD PTR [ebp+32]
  push DWORD PTR [ebp+28]
  call hook_sprintf
  add esp, 12
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret
'''


def original_assembly():
    result = ['.intel_syntax noprefix', '.text', '.set off_51A614, g_IO_LogicalNameTable_WError',
              '.set a__4, aDotNewline_FileError', '.equ var_24, -0x24']
    for name, procedure in procedures().items():
        result.append(name + ':')
        for line in procedure.splitlines():
            code = line.split(';', 1)[0].strip()
            if not code or '=' in code or re.search(r'\b(proc|endp)\b', code):
                continue
            code = re.sub(r'\b([0-9][0-9A-Fa-f]*)h\b', lambda m: '0x' + m[1], code)
            result.append(code.replace('short ', '').replace('retn', 'ret'))
    return '\n'.join(result) + '\n' + HOOKS + '\n.section .note.GNU-stack,"",@progbits\n'


class ErrorReportingSourceTests(unittest.TestCase):
    def test_original_procedures_are_pinned(self):
        for name, text in procedures().items():
            with self.subTest(procedure=name):
                self.assertEqual(hashlib.sha256(text.encode()).hexdigest(), HASHES[name])

    def test_actual_message_constants(self):
        values = constants()
        for name, expected_value in STRINGS.items():
            match = re.search(r'^char ' + name + r'\[\d+\] = (".*");$', values, re.M)
            self.assertEqual(json.loads(match[1]), expected_value, name)

    def test_all_extracted_bodies_match_manifest(self):
        manifest = json.loads((ROOT / 'data/recovered_sources.json').read_text())
        for name in NAMES:
            entry, = [e for e in manifest['functions'] if e['name'] == name]
            text = (ROOT / entry['source']).read_text()
            definition, = scan_definitions(text, {name})
            self.assertEqual(body_sha256(text, definition), entry['body_sha256'], name)

    def test_case_matrix_and_literal_messages(self):
        self.assertEqual(len(CASES), 4608)
        self.assertEqual(hashlib.sha256(EXPECTED).hexdigest(), EXPECTED_SHA256)
        self.assertIn(b'was unable to open file ', expected((1, 0, 0, 0)))
        self.assertIn(b'-2147483648', expected((0, 1, 0, 0)))
        self.assertIn(b'2147483647', expected((6, 1, 0, 0)))
        self.assertIn(b'changed-name', expected((1, 0, 2, 0)))
        self.assertNotEqual(expected((1, 0, 0, 0)), expected((1, 0, 1, 0)))


@unittest.skipUnless(sys.platform.startswith('linux') and platform.machine() in ('x86_64', 'amd64'), 'requires x86 Linux')
class ErrorReportingNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.compilers = compilers()
        if not cls.compilers:
            raise unittest.SkipTest('C++ compiler required')
        cls.directory = tempfile.TemporaryDirectory(prefix='clash-error-reporting-')
        cls.addClassCleanup(cls.directory.cleanup)
        cls.work = Path(cls.directory.name)
        (cls.work / 'entry32.s').write_text(ENTRY32)
        (cls.work / 'entry64.s').write_text(ENTRY64)
        (cls.work / 'original.s').write_text(original_assembly())
        cls.body = production()

    @classmethod
    def build(cls, compiler, optimization, bits, signed=True, original=False, body=None):
        source = cls.work / 'fixture.cpp'
        main = MAIN.replace('INPUTS', '{' + ','.join(map(json.dumps, INPUTS)) + '}')
        main = main.replace('FILES', '{' + ','.join(map(json.dumps, FILES)) + '}')
        source.write_text(PRELUDE.replace('CONSTANTS', constants()) +
                          ('\n' if original else cls.body if body is None else body) + main)
        binary = cls.work / 'fixture'
        command = [compiler, '-std=gnu++20', optimization, '-m' + str(bits), '-ffreestanding',
                   '-fno-builtin', '-fno-pie', '-fno-exceptions', '-fno-rtti', '-fno-stack-protector',
                   '-nostdlib', '-static', '-Wl,-no-pie', '-Wl,--build-id=none',
                   '-Wall', '-Wextra', '-Wpedantic', '-Werror',
                   '-fsigned-char' if signed else '-funsigned-char', str(source), str(cls.work / f'entry{bits}.s')]
        command += ['-DORIGINAL', str(cls.work / 'original.s')] if original else [
            '-fsanitize=undefined', '-fsanitize-undefined-trap-on-error']
        command += ['-o', str(binary)]
        result = subprocess.run(command, capture_output=True, text=True, timeout=30)
        if result.returncode:
            raise RuntimeError(' '.join(command) + '\n' + result.stderr)
        return binary

    def execute(self, binary, bits):
        try:
            return subprocess.run([str(binary)], cwd=self.work, capture_output=True, timeout=15)
        except OSError as exc:
            if bits == 32 and exc.errno == errno.ENOEXEC and os.environ.get('GITHUB_ACTIONS') != 'true':
                raise unittest.SkipTest('Host cannot execute 32-bit ELF; CI must execute this profile') from exc
            raise

    def test_original_composed_message_trace(self):
        result = self.execute(self.build(self.compilers[0], '-O0', 32, original=True), 32)
        self.assertEqual(result.returncode, 0, result.stderr.decode())
        self.assertEqual(result.stdout, EXPECTED)

    def test_production_messages_all_profiles(self):
        for compiler, optimization, bits, signed in itertools.product(
                self.compilers, ['-O0', '-O2'], [32, 64], [True, False]):
            with self.subTest(compiler=compiler, optimization=optimization, bits=bits, signed=signed):
                result = self.execute(self.build(compiler, optimization, bits, signed), bits)
                self.assertEqual(result.returncode, 0, result.stderr.decode())
                self.assertEqual(result.stdout, EXPECTED)

    def test_mutations_are_detected(self):
        mutations = {
            'wrong function name': self.body.replace('functionName, functionName);', 'fileName, functionName);', 1),
            'wrong filename': self.body.replace('fileName, functionName);', 'functionName, fileName);'),
            'wrong module': self.body.replace('module, module);', '(int)(intptr_t)aPrntutil, module);'),
            'wrong integer route': self.body.replace('g_IO_LogicalNameTable_WError[0], errorID);', 'aPrntutil, errorID);'),
            'narrowed identifier': self.body.replace('module, module);', '(int)(unsigned char)module, module);'),
            'missing output': self.body.replace('  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aId, module);', ''),
            'constant return': self.body.replace('return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504060, module);', 'Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_504060, module);\n  return 1;'),
            'cached destination': self.body.replace('Rules_PrintErrorID((int)(intptr_t)aArgacces, 2, 0);',
                'int saved = (int)(intptr_t)g_IO_LogicalNameTable_WError[0];\n  Rules_PrintErrorID((int)(intptr_t)aArgacces, 2, 0);').replace(
                '(int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, functionName);', 'saved, functionName, functionName);'),
        }
        for name, mutated in mutations.items():
            with self.subTest(mutation=name):
                self.assertNotEqual(mutated, self.body)
                result = self.execute(self.build(self.compilers[0], '-O0', 64, body=mutated), 64)
                self.assertTrue(result.returncode != 0 or result.stdout != EXPECTED)


if __name__ == '__main__':
    unittest.main()
