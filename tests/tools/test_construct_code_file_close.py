from pathlib import Path
import errno
import hashlib
import itertools
import json
import os
import platform
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from split_source_index import body_sha256, scan_definitions

NAME = 'Rules_ConstructCodeFileClose'
SOURCE = ROOT / 'src/clips/004A6C40_004A8520_clips_005.cpp'
PAIRS = [(-2147483648, 2147483647), (2147483647, -2147483648),
         (-1, 0), (0, -1), (0, 0), (9, 10), (10, 10), (11, 10),
         (-2147483648, -2147483648), (2147483647, 2147483647)]
CASES = [(count, limit, version, handle, flag, info, opened, effects)
         for (count, limit), version, handle, flag, info, opened, effects in itertools.product(
             PAIRS, [0, 1, 0x7fffffff, 0xffffffff], [0, 7, 0x12345678],
             [0, 1], [0, 1, 2], [0, 0x76543210], [0, 1])
         if not (count >= limit and handle == 0 and info == 0)]
FATAL_CASES = [(10, 10, 17, 0, 0, 0, 7, 0),
               (10, 10, 17, 0, 1, 0, 7, 0),
               (10, 10, 17, 0, 0, 2, 7, 0),
               (10, 10, 17, 0, 1, 2, 0, 0)]


def expected(case, terminal=False):
    count, limit, version, handle, has_flag, info, opened, effects = case
    flag = 0x55
    out = []

    def state():
        return f'{count}|{version}|{flag}'

    def close(stream):
        nonlocal count, version, flag
        out.append(f'C|{stream}|{state()}\n')
        if effects:
            count = 23
            version = (version + 7) & 0xffffffff
            flag ^= 4

    def error(code):
        out.extend([f'E|CONSCOMP|{code}|{state()}\n', 'X|2\n'])
        if terminal:
            out.append(f'Z|{state()}\n')
            return True
        return False

    if limit > count:
        if not has_flag:
            out.append(f'R|{handle}|{state()}\n')
            return ''.join(out).encode()
        flag = 1
        close(handle)
    else:
        if has_flag:
            flag = 0
        if not handle:
            if not has_flag or not info:
                if error(3):
                    return ''.join(out).encode()
            if not info:
                raise ValueError('returning exit callback would dereference null metadata')
            if info == 1:
                out.append(f'R|0|{state()}\n')
                return ''.join(out).encode()
            out.append(f'O|sample|3|17|version-context|1|{state()}\n')
            handle = opened
            if not handle and error(4):
                return ''.join(out).encode()
        out.append(f'W|{handle}|}};\n|{state()}\n')
        if effects:
            count = -3
            version = (version + 5) & 0xffffffff
            flag ^= 2
        close(handle)
        count = 0
        version = (version + 1) & 0xffffffff
    out.append(f'R|0|{state()}\n')
    return ''.join(out).encode()


EXPECTED = b''.join(expected(case) for case in CASES)
EXPECTED_SHA256 = hashlib.sha256(EXPECTED).hexdigest()

PRELUDE = r'''
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef unsigned int DWORD;
typedef unsigned int _DWORD;
extern "C" {
char aConscomp[] = "CONSCOMP";
char asc_507DA0[] = "};\n";
}
struct Case { int count, limit; unsigned version; int handle, flag, info, opened, effects; };
struct State { unsigned guard1; int count; unsigned version, flag, guard2; };
static State state;
static unsigned metadata[5];
static char basename[] = "sample";
static int open_result, side_effects, terminal_exit;
static char record[2048];
static unsigned used;
static void write_record() {
  long result;
#if __SIZEOF_POINTER__ == 8
  asm volatile("syscall" : "=a"(result) : "0"(1L), "D"(1L), "S"(record), "d"((long)used) : "rcx", "r11", "memory", "cc");
#else
  asm volatile("int $0x80" : "=a"(result) : "0"(4), "b"(1), "c"(record), "d"(used) : "memory", "cc");
#endif
  if (result != (long)used) __builtin_trap();
  used = 0;
}
[[noreturn]] static void finish(int code) {
#if __SIZEOF_POINTER__ == 8
  asm volatile("syscall" : : "a"(60L), "D"((long)code) : "rcx", "r11", "memory", "cc");
#else
  asm volatile("int $0x80" : : "a"(1), "b"(code) : "memory", "cc");
#endif
  __builtin_unreachable();
}
static void put(char c) { if (used == sizeof(record)) __builtin_trap(); record[used++] = c; }
static void text(const char *s) { while (*s) put(*s++); }
static void unsigned_number(unsigned n) {
  char digits[10]; unsigned size = 0;
  do { digits[size++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (size) put(digits[--size]);
}
static void number(int n) {
  unsigned magnitude = (unsigned)n;
  if (n < 0) { put('-'); magnitude = 0u - magnitude; }
  unsigned_number(magnitude);
}
static void snapshot() {
  number(state.count); put('|'); unsigned_number(state.version); put('|'); unsigned_number(state.flag);
}
extern "C" int hook_close(int stream) {
  text("C|"); number(stream); put('|'); snapshot(); put('\n');
  if (side_effects) { state.count = 23; state.version += 7; state.flag ^= 4; }
  return -17;
}
extern "C" int hook_output(int stream, const char *format) {
  text("W|"); number(stream); put('|');
  if (format != asc_507DA0) __builtin_trap();
  text(format); put('|'); snapshot(); put('\n');
  if (side_effects) { state.count = -3; state.version += 5; state.flag ^= 2; }
  return 91;
}
extern "C" int hook_error(int module, int code) {
  text("E|");
  text((unsigned)module == (unsigned)(uintptr_t)aConscomp ? "CONSCOMP" : "BAD_MODULE");
  put('|'); number(code); put('|'); snapshot(); put('\n');
  return 66;
}
extern "C" int hook_exit(int code) {
  text("X|"); number(code); put('\n');
  if (terminal_exit) { text("Z|"); snapshot(); put('\n'); write_record(); finish(code); }
  return 77;
}
extern "C" int hook_open(const char *name, int id, int version, DWORD context, int mode) {
  if (name != basename) __builtin_trap();
  text("O|"); text(name); put('|'); number(id); put('|'); number(version); put('|');
  text(context == (DWORD)(uintptr_t)&state.version ? "version-context" : "BAD_CONTEXT");
  put('|'); number(mode); put('|'); snapshot(); put('\n');
  return open_result;
}
#ifndef ORIGINAL
static int fclose_(int stream) { return hook_close(stream); }
static int Output_WriteFormatted(int, int, int stream, int format, ...) {
  return hook_output(stream, (const char *)(uintptr_t)(unsigned)format);
}
static int Rules_ReportSystemError(int module, int code) { return hook_error(module, code); }
static int IO_RunRouterExitCallbacks(int code) { return hook_exit(code); }
static int Rules_OpenConstructCodeFile(const char *name, int id, int version, DWORD context, int mode) {
  return hook_open(name, id, version, context, mode);
}
#endif
'''

MAIN = r'''
#ifdef ORIGINAL
extern "C" int original_call(int, int *, int, unsigned *, unsigned *, int);
#define CALL original_call
#else
#define CALL Rules_ConstructCodeFileClose
#endif
static void run(const Case &c) {
  state.guard1 = 0x12481248u; state.guard2 = 0x87654321u;
  state.count = c.count; state.version = c.version; state.flag = 0x55;
  metadata[0] = 0x789abcdeu; metadata[4] = 0xfedcba98u;
  metadata[1] = c.info == 2 ? (unsigned)(uintptr_t)basename : 0;
  metadata[2] = 3; metadata[3] = 17;
  if ((uintptr_t)metadata > 0x7fffffffu || (uintptr_t)basename > 0x7fffffffu) __builtin_trap();
  open_result = c.opened; side_effects = c.effects;
  int result = CALL(c.handle, &state.count, c.limit, &state.version,
                    c.flag ? &state.flag : 0, c.info ? (int)(intptr_t)(metadata + 1) : 0);
  if (state.guard1 != 0x12481248u || state.guard2 != 0x87654321u ||
      metadata[0] != 0x789abcdeu || metadata[4] != 0xfedcba98u ||
      metadata[1] != (c.info == 2 ? (unsigned)(uintptr_t)basename : 0) ||
      metadata[2] != 3 || metadata[3] != 17) __builtin_trap();
  text("R|"); number(result); put('|'); snapshot(); put('\n'); write_record();
}
extern "C" int fixture_main(int argc, char **argv) {
  if (argc == 2) {
    unsigned index = (unsigned)(argv[1][0] - '0');
    if (index >= sizeof(fatal_cases) / sizeof(fatal_cases[0])) return 5;
    terminal_exit = 1;
    run(fatal_cases[index]);
    return 6;
  }
  for (unsigned i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) run(cases[i]);
  return 0;
}
'''

ENTRY32 = r'''
.intel_syntax noprefix
.text
.global _start
_start:
  mov ecx, [esp]
  lea edx, [esp+4]
  and esp, -16
  push edx
  push ecx
  call fixture_main
  mov ebx, eax
  mov eax, 1
  int 0x80
.section .note.GNU-stack,"",@progbits
'''
ENTRY64 = r'''
.intel_syntax noprefix
.text
.global _start
_start:
  mov rdi, [rsp]
  lea rsi, [rsp+8]
  and rsp, -16
  call fixture_main
  mov edi, eax
  mov eax, 60
  syscall
.section .note.GNU-stack,"",@progbits
'''
HOOKS = r'''
.global original_call
original_call:
  push ebp
  push ebx
  push esi
  push edi
  mov eax, [esp+20]
  mov edx, [esp+24]
  mov ecx, [esp+28]
  mov ebx, [esp+32]
  push DWORD PTR [esp+40]
  push DWORD PTR [esp+40]
  call sub_4A7920
  pop edi
  pop esi
  pop ebx
  pop ebp
  ret

.macro preserve
  push ecx
  push edx
  push ebx
  push esi
  push edi
  push ebp
.endm
.macro restore
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret
.endm
fclose_:
  preserve
  push eax
  call hook_close
  add esp, 4
  restore
sub_485C80:
  preserve
  push edx
  push eax
  call hook_error
  add esp, 8
  restore
sub_486020:
  preserve
  push eax
  call hook_exit
  add esp, 4
  restore
sub_4A7140:
  preserve
  push ecx
  push ebp
  push ebx
  push edx
  push eax
  call hook_open
  add esp, 20
  restore
sub_476301:
  preserve
  mov ebp, esp
  push DWORD PTR [ebp+32]
  push DWORD PTR [ebp+28]
  call hook_output
  add esp, 8
  restore
.section .note.GNU-stack,"",@progbits
'''


def original_procedure():
    assembly = (ROOT / 'clash95.asm').read_text(encoding='utf-8')
    return re.search(r'^sub_4A7920\s+proc\b.*?^sub_4A7920\s+endp', assembly, re.M | re.S).group()


def assemble_listing(procedure):
    result = ['.intel_syntax noprefix', '.text', 'sub_4A7920:', '.equ arg_0, 4', '.equ arg_4, 8']
    for line in procedure.splitlines():
        code = line.split(';', 1)[0].strip()
        if not code or '=' in code or re.search(r'\b(proc|endp)\b', code):
            continue
        code = re.sub(r'\b([0-9][0-9A-Fa-f]*)h\b', lambda m: '0x' + m[1], code)
        result.append(code.replace('short ', '').replace('retn', 'ret'))
    return '\n'.join(result) + '\n' + HOOKS


def input_table(name, cases):
    rows = ['{' + ','.join(str(value) + ('u' if index == 2 else '')
                         for index, value in enumerate(case)) + '}' for case in cases]
    return 'static const Case ' + name + '[] = {\n' + ',\n'.join(rows) + '\n};\n'


class ConstructCloseSourceTests(unittest.TestCase):
    def test_protected_original_instructions_are_pinned(self):
        self.assertEqual(hashlib.sha256(original_procedure().encode()).hexdigest(),
                         'cb51c0388603dc30816f704d5ac8ba2705910d7f69255034244fb26f2c197f05')

    def test_manifest_matches_the_actual_production_body(self):
        source = SOURCE.read_text()
        definition, = scan_definitions(source, {NAME})
        manifest = json.loads((ROOT / 'data/recovered_sources.json').read_text())
        entry, = [entry for entry in manifest['functions'] if entry['name'] == NAME]
        self.assertEqual(entry['original_address'], '0x004A7920')
        self.assertEqual(entry['body_sha256'], body_sha256(source, definition))
        self.assertEqual(entry['legacy_body_sha256'],
                         'a471712164b8ecd311739a60e92897e3bf5dd542f3751e736f930ebf598f3cde')

    def test_case_matrix_covers_boundaries_and_side_effects(self):
        self.assertEqual(len(CASES), 2656)
        self.assertEqual(EXPECTED.count(b'R|'), len(CASES))
        for marker in (b'E|CONSCOMP|3|', b'E|CONSCOMP|4|', b'C|0|', b'W|0|', b'O|sample|'):
            self.assertIn(marker, EXPECTED)
        self.assertEqual(hashlib.sha256(EXPECTED).hexdigest(), '2b36d1ded43d1413e5a9586ec8d2dd29d0931c6e6eb7d89d60c148e1d82f401d')


@unittest.skipUnless(sys.platform.startswith('linux') and platform.machine() in ('x86_64', 'amd64'),
                     'requires x86 Linux')
class ConstructCloseNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        requested = os.environ.get('CLASH95_CONSTRUCT_TEST_CXX')
        if requested:
            compiler = shutil.which(requested)
            if compiler is None:
                raise RuntimeError('Requested compiler unavailable: ' + requested)
            cls.compilers = [compiler]
        else:
            cls.compilers = list(dict.fromkeys(filter(None, [
                shutil.which('g++-13') or shutil.which('g++'),
                shutil.which('clang++-18') or shutil.which('clang++')])))
        if not cls.compilers:
            raise unittest.SkipTest('C++ compiler required')
        cls.directory = tempfile.TemporaryDirectory(prefix='clash-construct-close-')
        cls.addClassCleanup(cls.directory.cleanup)
        cls.work = Path(cls.directory.name)
        (cls.work / 'entry32.s').write_text(ENTRY32)
        (cls.work / 'entry64.s').write_text(ENTRY64)
        (cls.work / 'original.s').write_text(assemble_listing(original_procedure()))
        source = SOURCE.read_text()
        definition, = scan_definitions(source, {NAME})
        cls.body = source[definition.start:definition.end]
        cls.tables = input_table('cases', CASES) + input_table('fatal_cases', FATAL_CASES)

    @classmethod
    def build(cls, compiler, optimization, bits, signed=True, original=False, body=None):
        source = cls.work / 'fixture.cpp'
        source.write_text(PRELUDE + ('\n' if original else cls.body if body is None else body) + cls.tables + MAIN)
        binary = cls.work / 'fixture'
        command = [compiler, '-std=gnu++20', optimization, '-m' + str(bits), '-ffreestanding',
                   '-fno-builtin', '-fno-pie', '-fno-exceptions', '-fno-rtti', '-fno-stack-protector',
                   '-nostdlib', '-static', '-Wl,-no-pie', '-Wl,--build-id=none',
                   '-Wall', '-Wextra', '-Wpedantic', '-Werror',
                   '-fsigned-char' if signed else '-funsigned-char', str(source), str(cls.work / f'entry{bits}.s')]
        if original:
            command += ['-DORIGINAL', str(cls.work / 'original.s')]
        else:
            command += ['-fsanitize=undefined', '-fsanitize-undefined-trap-on-error']
        command += ['-o', str(binary)]
        built = subprocess.run(command, capture_output=True, timeout=30)
        if built.returncode:
            raise RuntimeError(' '.join(command) + '\n' + built.stderr.decode())
        return binary

    def execute(self, binary, bits, arguments=()):
        try:
            return subprocess.run([str(binary), *arguments], capture_output=True, timeout=10, cwd=self.work)
        except OSError as exc:
            if bits == 32 and exc.errno == errno.ENOEXEC and os.environ.get('GITHUB_ACTIONS') != 'true':
                raise unittest.SkipTest('Host cannot execute 32-bit ELF; CI must execute this profile') from exc
            raise

    def check_trace(self, binary, bits):
        result = self.execute(binary, bits)
        self.assertEqual(result.returncode, 0, result.stderr.decode())
        self.assertEqual(result.stdout, EXPECTED)
        for index, case in enumerate(FATAL_CASES):
            result = self.execute(binary, bits, [str(index)])
            self.assertEqual(result.returncode, 2, result.stderr.decode())
            self.assertEqual(result.stdout, expected(case, terminal=True))

    def test_original_instruction_trace_and_terminating_errors(self):
        binary = self.build(self.compilers[0], '-O0', 32, original=True)
        self.check_trace(binary, 32)

    def test_actual_production_across_all_compiler_profiles(self):
        for compiler, optimization, bits, signed in itertools.product(
                self.compilers, ['-O0', '-O2'], [32, 64], [True, False]):
            with self.subTest(compiler=compiler, optimization=optimization, bits=bits, signed=signed):
                self.check_trace(self.build(compiler, optimization, bits, signed), bits)

    def test_regression_mutations_are_detected(self):
        mutations = [
            self.body.replace('fclose_(curFile);', 'fclose_(codeFile);', 1),
            self.body.replace('  fclose_(curFile);\n  *theCount', '  fclose_(7);\n  *theCount'),
            self.body.replace('(int)(intptr_t)aConscomp', 'codeFileInfo'),
            self.body.replace('if ( v8 > *theCount )', 'if ( v8 >= *theCount )'),
            self.body.replace('(DWORD)(intptr_t)arrayVersion, 1)', '(DWORD)(intptr_t)arrayVersion, 0)'),
            self.body.replace('++*arrayVersion;', '*arrayVersion += 2;'),
            self.body.replace('    *canBeReopened = 1;', '    *canBeReopened = 0;'),
        ]
        for index, body in enumerate(mutations):
            with self.subTest(mutation=index):
                self.assertNotEqual(body, self.body)
                binary = self.build(self.compilers[0], '-O0', 64, body=body)
                result = self.execute(binary, 64)
                self.assertTrue(result.returncode != 0 or result.stdout != EXPECTED)


if __name__ == '__main__':
    unittest.main()
