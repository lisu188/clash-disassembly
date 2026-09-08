from pathlib import Path
import hashlib
import errno
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
from split_source_index import scan_definitions

ORACLE_SHA256 = 'b7944e6d4936f058ccc0f5b8dfbc422bc09496efdb5a64704ef3ece6787a4121'
NAME = 'Rules_OpenConstructCodeFile'
SOURCE = ROOT / 'src/clips/004A6C40_004A8520_clips_005.cpp'

PRELUDE = r'''
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef unsigned int DWORD;
typedef char CHAR;
#define __int8 char
extern "C" {
void *memcpy(void *destination, const void *source, __SIZE_TYPE__ size) {
  volatile unsigned char *out = (volatile unsigned char *)destination;
  const volatile unsigned char *in = (const volatile unsigned char *)source;
  for (__SIZE_TYPE__ i = 0; i < size; ++i) out[i] = in[i];
  return destination;
}
char aA_0[] = "a";
char aSD_D_c[] = "%s%d_%d.c";
char aW_2[] = "w";
char aIncludeS_h[] = "#include \"%s.h\"\n";
char asc_507D2C[] = "\n";
char aConstructsToC[] = "constructs-to-c";
}
static char record[2048];
static unsigned int used;
static const char *last_buffer;
static char last_name[84];
static int open_result;
alignas(256) static char names[512];

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
static void put(char c) {
  if (used == sizeof(record)) __builtin_trap();
  record[used++] = c;
}
static void text(const char *s) { while (*s) put(*s++); }
static void number(int value) {
  unsigned int n = (unsigned int)value;
  if (value < 0) { put('-'); n = 0u - n; }
  char digits[11]; unsigned int count = 0;
  do { digits[count++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (count) put(digits[--count]);
}
static bool equal(const char *a, const char *b) {
  while (*a && *a == *b) { ++a; ++b; }
  return *a == *b;
}
static char *copy(char *out, const char *in) {
  while (*in) *out++ = *in++;
  *out = 0;
  return out;
}
static char *decimal(char *out, int value) {
  unsigned int n = (unsigned int)value;
  if (value < 0) { *out++ = '-'; n = 0u - n; }
  char digits[11]; unsigned int count = 0;
  do { digits[count++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (count) *out++ = digits[--count];
  *out = 0;
  return out;
}
extern "C" int hook_sprintf(char *out, const char *format, const char *base, int id, int version) {
  if (!equal(format, "%s%d_%d.c")) __builtin_trap();
  char *cursor = copy(out, base);
  cursor = decimal(cursor, id); *cursor++ = '_';
  cursor = decimal(cursor, version); cursor = copy(cursor, ".c");
  text("F|"); text(out); put('\n');
  return (int)(cursor - out);
}
extern "C" int hook_open(const char *file, unsigned char *mode, int incoming_mode, DWORD context) {
  last_buffer = file;
  copy(last_name, file);
  text("O|"); text(file); put('|'); text((char *)mode); put('|');
  number(incoming_mode); put('|'); number((int)context); put('\n');
  return open_result;
}
extern "C" int hook_output(int stream, const char *format, const char *argument) {
  text("W|"); number(stream); put('|');
  if (equal(format, aIncludeS_h)) {
    text("#include \""); text(argument); text(".h\"\n");
  } else if (equal(format, "\n")) {
    put('\n');
  } else {
    __builtin_trap();
  }
  return -7;
}
extern "C" int hook_error(int function, int filename) {
  text("E|"); text((const char *)(uintptr_t)(unsigned int)function); put('|');
  if ((unsigned int)filename != (unsigned int)(uintptr_t)last_buffer) __builtin_trap();
  text(last_name); put('\n');
  return 99;
}
#ifndef ORIGINAL
static int sprintf_(char *out, const char *format, ...) {
  __builtin_va_list args;
  __builtin_va_start(args, format);
  const char *base = __builtin_va_arg(args, const char *);
  int id = __builtin_va_arg(args, int);
  int version = __builtin_va_arg(args, int);
  __builtin_va_end(args);
  return hook_sprintf(out, format, base, id, version);
}
static int IO_FOpen(const char *file, unsigned char *mode, int incoming_mode, DWORD context) {
  return hook_open(file, mode, incoming_mode, context);
}
static int Output_WriteFormatted(int, int, int stream, int format, ...) {
  const char *fmt = (const char *)(uintptr_t)(unsigned int)format;
  const char *argument = 0;
  __builtin_va_list args;
  __builtin_va_start(args, format);
  if (equal(fmt, aIncludeS_h)) argument = (const char *)(uintptr_t)(unsigned int)__builtin_va_arg(args, int);
  __builtin_va_end(args);
  return hook_output(stream, fmt, argument);
}
static int Rules_OpenFileErrorMessage(int function, int file) { return hook_error(function, file); }
#endif
'''

MAIN = r'''
#ifdef ORIGINAL
extern "C" int original_call(const char *, int, int, DWORD, int);
#define CALL original_call
#else
#define CALL Rules_OpenConstructCodeFile
#endif
extern "C" int fixture_main() {
  const int modes[] = {0, 1, -1, 256, (-2147483647 - 1), 2147483647};
  const int ids[] = {0, 1, -1, (-2147483647 - 1), 2147483647};
  const char *bases[] = {"", "x", "case.name", "dir/file", "with space"};
  for (unsigned int index = 0; index < 256; ++index) {
    char *base = names + index;
    if ((uintptr_t)base > 0xffffffffu || ((uintptr_t)base & 255) != index) __builtin_trap();
    copy(base, bases[index % 5]);
    for (unsigned int mode = 0; mode < 6; ++mode) {
      for (int success = 0; success != 2; ++success) {
        open_result = success ? 0x12345678 : 0;
        DWORD context = (index & 1) ? 0xf1234567u : 0;
        int result = CALL(base, ids[index % 5], ids[(index + 2) % 5], context, modes[mode]);
        text("R|"); number(result); put('\n');
        write_record();
      }
    }
  }
  return 0;
}
'''

ENTRY32 = r'''
.intel_syntax noprefix
.text
.global _start
_start:
  and esp, -16
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
  mov ebx, [esp+28]
  mov ebp, [esp+32]
  mov ecx, [esp+36]
  call sub_4A7140
  pop edi
  pop esi
  pop ebx
  pop ebp
  ret

sprintf_:
  push ecx
  push edx
  push ebx
  push esi
  push edi
  push ebp
  mov ebp, esp
  push DWORD PTR [ebp+44]
  push DWORD PTR [ebp+40]
  push DWORD PTR [ebp+36]
  push DWORD PTR [ebp+32]
  push DWORD PTR [ebp+28]
  call hook_sprintf
  add esp, 20
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret

sub_475CC8:
  push ecx
  push edx
  push ebx
  push esi
  push edi
  push ebp
  push ebp
  push ecx
  push edx
  push eax
  call hook_open
  add esp, 16
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret

sub_476301:
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
  call hook_output
  add esp, 12
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret

sub_4818C0:
  push ecx
  push edx
  push ebx
  push esi
  push edi
  push ebp
  push edx
  push eax
  call hook_error
  add esp, 8
  pop ebp
  pop edi
  pop esi
  pop ebx
  pop edx
  pop ecx
  ret
'''


def original_procedure():
    assembly = (ROOT / 'clash95.asm').read_text(encoding='utf-8')
    return re.search(r'^sub_4A7140\s+proc\b.*?^sub_4A7140\s+endp', assembly, re.M | re.S).group()


def assemble_listing(procedure):
    result = ['.intel_syntax noprefix', '.text', 'sub_4A7140:', '.equ var_54, -0x54']
    for line in procedure.splitlines():
        code = line.split(';', 1)[0].strip()
        if not code or '=' in code or re.search(r'\b(proc|endp)\b', code):
            continue
        code = re.sub(r'\b([0-9][0-9A-Fa-f]*)h\b', lambda m: '0x' + m[1], code)
        code = code.replace('short ', '').replace('retn', 'ret')
        result.append(code)
    return '\n'.join(result) + '\n' + HOOKS + '\n.section .note.GNU-stack,"",@progbits\n'


def production_body():
    text = SOURCE.read_text(encoding='utf-8')
    definition, = scan_definitions(text, {NAME})
    return text[definition.start:definition.end]


def compilers():
    requested = os.environ.get('CLASH95_CONSTRUCT_TEST_CXX')
    if requested:
        compiler = shutil.which(requested)
        if not compiler:
            raise RuntimeError('Requested C++ compiler unavailable: ' + requested)
        return [compiler]
    return list(dict.fromkeys(filter(None, [shutil.which('g++-13') or shutil.which('g++'),
                                           shutil.which('clang++-18') or shutil.which('clang++')])) )


class ConstructFileSourceTests(unittest.TestCase):
    def test_protected_instruction_contract(self):
        procedure = original_procedure()
        self.assertEqual(hashlib.sha256(procedure.encode()).hexdigest(), '2feb389deb52dabec8dae5ff66b0f2a5fe53a4d85f4c6b12cd39958e3d956dde')
        self.assertIn('push    esi\n', procedure)
        self.assertRegex(procedure, r'mov\s+esi, eax')
        self.assertEqual(len(re.findall(r'test\s+ecx, ecx', procedure)), 2)
        self.assertRegex(procedure, r'push\s+esi\s*\n\s*push\s+offset aIncludeS_h')
        self.assertRegex(procedure, r'mov\s+eax, offset aConstructsToC')

    def test_all_26_callers_supply_the_original_mode(self):
        manifest = json.loads((ROOT / 'data/recovered_sources.json').read_text())
        definitions = {r['name']: r for r in manifest['functions']}
        asm = (ROOT / 'clash95.asm').read_text()
        total = 0
        for match in re.finditer(r'^(sub_[0-9A-F]+)\s+proc\b.*?^\1\s+endp', asm, re.M | re.S):
            procedure = match.group()
            calls = list(re.finditer(r'\bcall\s+sub_4A7140\b', procedure))
            if not calls:
                continue
            address = '0x00' + match[1][4:]
            entry, = [r for r in definitions.values() if (r['original_address'] or '').lower() == address.lower()]
            text = (ROOT / entry['source']).read_text()
            function, = scan_definitions(text, {entry['name']})
            body = text[function.opening_brace:function.end]
            actual = re.findall(NAME + r'\([^;\n]*, (0|1|reopenOldFile)\);', body)
            self.assertEqual(len(actual), len(calls), entry['name'])
            for call, mode in zip(calls, actual):
                prior = re.findall(r'^\s*((?:mov|xor)\s+ecx, [^\n;]+)', procedure[:call.start()], re.M)[-1]
                expected = '0' if re.fullmatch(r'xor\s+ecx, ecx\s*', prior) else '1' if re.fullmatch(r'mov\s+ecx, 1\s*', prior) else 'reopenOldFile'
                if expected == 'reopenOldFile':
                    self.assertEqual(match[1], 'sub_4A79F0')
                    self.assertRegex(prior, r'mov\s+ecx, \[esp\+60h\+arg_14\]')
                self.assertEqual(mode, expected, entry['name'])
            total += len(calls)
        self.assertEqual(total, 26)


@unittest.skipUnless(sys.platform.startswith('linux') and platform.machine() in ('x86_64', 'amd64'), 'requires x86 Linux')
class ConstructFileNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.compilers = compilers()
        if not cls.compilers:
            raise unittest.SkipTest('C++ compiler required')
        cls.directory = tempfile.TemporaryDirectory(prefix='clash-construct-')
        cls.addClassCleanup(cls.directory.cleanup)
        cls.work = Path(cls.directory.name)
        (cls.work / 'entry32.s').write_text(ENTRY32)
        (cls.work / 'entry64.s').write_text(ENTRY64)
        (cls.work / 'original.s').write_text(assemble_listing(original_procedure()))
        cls.body = production_body()

    @classmethod
    def compile_and_run(cls, compiler, optimization, bits, original=False, body=None, signed=True):
        source = cls.work / 'fixture.cpp'
        source.write_text(PRELUDE + ('\n' if original else (cls.body if body is None else body)) + MAIN)
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
        try:
            result = subprocess.run([str(binary)], cwd=cls.work, capture_output=True, timeout=10)
        except OSError as exc:
            if bits == 32 and exc.errno == errno.ENOEXEC and os.environ.get('GITHUB_ACTIONS') != 'true':
                raise unittest.SkipTest('Host kernel cannot execute 32-bit ELF; CI must execute this profile') from exc
            raise
        if original and result.returncode:
            raise RuntimeError('Original instruction fixture failed: ' + str(result.returncode))
        return result

    def test_original_instruction_trace_matches_frozen_digest(self):
        result = self.compile_and_run(self.compilers[0], '-O0', 32, True)
        self.assertEqual(result.stdout.count(b'R|'), 3072)
        self.assertEqual(hashlib.sha256(result.stdout).hexdigest(), ORACLE_SHA256)

    def test_production_matches_original_instructions_in_all_profiles(self):
        for compiler in self.compilers:
            for optimization in ('-O0', '-O2'):
                for bits in (32, 64):
                    for signed in (True, False):
                        with self.subTest(compiler=compiler, optimization=optimization, bits=bits, signed=signed):
                            result = self.compile_and_run(compiler, optimization, bits, signed=signed)
                            self.assertEqual(result.returncode, 0, result.stderr.decode())
                            self.assertEqual(result.stdout.count(b'R|'), 3072)
                            self.assertEqual(hashlib.sha256(result.stdout).hexdigest(), ORACLE_SHA256)

    def test_mutated_filename_truncation_is_detected(self):
        body = self.body.replace('(int)(intptr_t)fileName);', '(int)(char)(intptr_t)fileName);')
        self.assertNotEqual(body, self.body)
        result = self.compile_and_run(self.compilers[0], '-O0', 64, body=body)
        self.assertTrue(result.returncode != 0 or hashlib.sha256(result.stdout).hexdigest() != ORACLE_SHA256)

    def test_mutated_append_mode_is_detected(self):
        body = self.body.replace('reopenOldFile ? aA_0 : aW_2', 'reopenOldFile ? aW_2 : aA_0')
        self.assertNotEqual(body, self.body)
        result = self.compile_and_run(self.compilers[0], '-O0', 64, body=body)
        self.assertNotEqual(hashlib.sha256(result.stdout).hexdigest(), ORACLE_SHA256)

    def test_mutated_output_stream_is_detected(self):
        body = self.body.replace('0, fp, fp,', '0, fp, 7,')
        self.assertNotEqual(body, self.body)
        result = self.compile_and_run(self.compilers[0], '-O0', 64, body=body)
        self.assertNotEqual(hashlib.sha256(result.stdout).hexdigest(), ORACLE_SHA256)


if __name__ == '__main__':
    unittest.main()
