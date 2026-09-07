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
from split_source_index import body_sha256, mask_c, scan_definitions
from test_construct_code_file_close import ENTRY32, ENTRY64

NAME = 'Rules_ConstructCodeFileOpen'
SOURCE = ROOT / 'src/clips/004A6C40_004A8520_clips_005.cpp'
MODES = [0, 1, -1, 256, -2147483648, 2147483647]
STYLES = [('fresh', 'struct item', 'item_', 0, 0),
          ('with.space', 'unsigned long', 'x', -1, 17),
          ('', 'struct other', '', 2147483647, -2147483648)]
CASES = [(mode, info, stream, opened, count, style, effects, low)
         for mode, info, stream, opened, count, style, effects, low in itertools.product(
             MODES, [0, 1], [0, 7, 0x12345678], [0, 0x345678],
             [-2147483648, -1, 0, 2147483647], range(3), [0, 1], [128])
         if not (mode and not info)]
CASES += [(mode, 1, stream, 0x345678, 8, low % 3, 0, low)
          for low, mode, stream in itertools.product(range(256), [0, 1], [0, 7])]
FATAL_CASES = [(1, 0, 0, 1, 0, 0, 0, 0), (-1, 0, 7, 1, 1, 1, 0, 255)]


def signed(value):
    return ((value + 2147483648) & 0xffffffff) - 2147483648


def expected(case, terminal=False):
    mode, info, stream, opened, count, style, effects, low = case
    base, structure, prefix, image, array = STYLES[style]
    ident = [3, -1, -2147483648][style]
    descriptor = ['remembered', -7, 99]
    out = []

    def snapshot():
        return f'{count}|{descriptor[0]}|{descriptor[1]}|{descriptor[2]}'

    def output(handle, message):
        nonlocal count, structure
        out.append(f'W|{handle}|{message}|{snapshot()}\n')
        if effects:
            count = signed(count + 5)
            structure = 'X' + structure[1:]
            descriptor[2] = signed(descriptor[2] + 11)

    if mode:
        if not info:
            out.extend([f'E|CONSCOMP|5|{snapshot()}\n', 'X|2\n'])
            if terminal:
                out.append(f'Z|{snapshot()}\n')
                return ''.join(out).encode()
            raise ValueError('null metadata after returning exit callback is not a supported input')
        selected_base, selected_id, selected_version = descriptor
    else:
        selected_base, selected_id, selected_version = base, ident, count
        if info:
            descriptor = [base, ident, count]
    if stream:
        output(stream, ',\n')
        result = stream
    else:
        out.append(f'O|{selected_base}|{selected_id}|{selected_version}|base-context|{mode}|{snapshot()}\n')
        if effects:
            count = signed(count + 7)
            descriptor[2] = signed(descriptor[2] + 13)
        result = opened
        if result:
            if mode:
                output(result, ',\n')
            else:
                count = signed(count + 1)
                array_name = f'{prefix}{image}_{array}'
                out.append(f'F|{array_name}|{snapshot()}\n')
                if effects:
                    count = signed(count + 3)
                output(result, f'{structure} {array_name}[] = {{\n')
                output(23, f'extern {structure} {array_name}[];\n')
    out.append(f'R|{result}|{snapshot()}\n')
    return ''.join(out).encode()


EXPECTED = b''.join(expected(case) for case in CASES)
EXPECTED_SHA256 = hashlib.sha256(EXPECTED).hexdigest()
PRELUDE = r'''
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef unsigned int DWORD;
typedef unsigned int _DWORD;
extern "C" {
void *memcpy(void *destination, const void *source, __SIZE_TYPE__ size) {
  volatile unsigned char *out = (volatile unsigned char *)destination;
  const volatile unsigned char *in = (const volatile unsigned char *)source;
  for (__SIZE_TYPE__ i = 0; i < size; ++i) out[i] = in[i];
  return destination;
}
char aConscomp[] = "CONSCOMP";
char asc_508250[] = ",\n";
char aSD_D[] = "%s%d_%d";
char aSS_0[] = "%s %s[] = {\n";
char aExternSS[] = "extern %s %s[];\n";
}
struct Case { int mode, info, stream, opened, count, style, effects, low; };
static int counter, open_result, side_effects, terminal_exit;
static unsigned metadata[6];
alignas(256) static char structures[512];
static char remembered[] = "remembered";
static const char *bases[] = {"fresh", "with.space", ""};
static const char *types[] = {"struct item", "unsigned long", "struct other"};
static const char *prefixes[] = {"item_", "x", ""};
static const char *active_base;
static char *active_type;
static char *last_buffer;
static char last_array[80];
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
static void number(int value) {
  unsigned n = (unsigned)value;
  if (value < 0) { put('-'); n = 0u - n; }
  char digits[10]; unsigned size = 0;
  do { digits[size++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (size) put(digits[--size]);
}
static char *copy(char *out, const char *in) {
  while (*in) *out++ = *in++;
  *out = 0;
  return out;
}
static char *decimal(char *out, int value) {
  unsigned n = (unsigned)value;
  if (value < 0) { *out++ = '-'; n = 0u - n; }
  char digits[10]; unsigned size = 0;
  do { digits[size++] = (char)('0' + n % 10); n /= 10; } while (n);
  while (size) *out++ = digits[--size];
  *out = 0;
  return out;
}
static bool equal(const char *a, const char *b) {
  while (*a && *a == *b) { ++a; ++b; }
  return *a == *b;
}
static void snapshot() {
  number(counter); put('|');
  unsigned name = metadata[1];
  if (name == (unsigned)(uintptr_t)remembered) text(remembered);
  else if (name == (unsigned)(uintptr_t)active_base) text(active_base);
  else text("BAD_NAME");
  put('|'); number((int)metadata[2]); put('|'); number((int)metadata[3]);
}
extern "C" int hook_error(int module, int code) {
  text("E|"); text((unsigned)module == (unsigned)(uintptr_t)aConscomp ? "CONSCOMP" : "BAD_MODULE");
  put('|'); number(code); put('|'); snapshot(); put('\n'); return 66;
}
extern "C" int hook_exit(int code) {
  text("X|"); number(code); put('\n');
  if (terminal_exit) { text("Z|"); snapshot(); put('\n'); write_record(); finish(code); }
  return 77;
}
extern "C" int hook_open(const char *base, int id, int version, DWORD context, int mode) {
  if (base != active_base && base != remembered) __builtin_trap();
  text("O|"); text(base); put('|'); number(id); put('|'); number(version); put('|');
  text(context == (DWORD)(uintptr_t)active_base ? "base-context" : "BAD_CONTEXT");
  put('|'); number(mode); put('|'); snapshot(); put('\n');
  if (side_effects) { counter = (int)((unsigned)counter + 7u); metadata[3] += 13; }
  return open_result;
}
extern "C" int hook_sprintf(char *out, const char *format, const char *prefix, int image, int version) {
  if (!equal(format, aSD_D)) __builtin_trap();
  char *cursor = copy(out, prefix);
  cursor = decimal(cursor, image); *cursor++ = '_'; cursor = decimal(cursor, version);
  last_buffer = out; copy(last_array, out);
  text("F|"); text(out); put('|'); snapshot(); put('\n');
  if (side_effects) counter = (int)((unsigned)counter + 3u);
  return -45;
}
extern "C" int hook_output(int stream, const char *format, unsigned structure, unsigned array) {
  text("W|"); number(stream); put('|');
  if (format == asc_508250) text(format);
  else {
    if (structure != (unsigned)(uintptr_t)active_type || array != (unsigned)(uintptr_t)last_buffer) __builtin_trap();
    if (format == aExternSS) text("extern ");
    else if (format != aSS_0) __builtin_trap();
    text(active_type); put(' '); text(last_array);
    text(format == aSS_0 ? "[] = {\n" : "[];\n");
  }
  put('|'); snapshot(); put('\n');
  if (side_effects) {
    counter = (int)((unsigned)counter + 5u); active_type[0] = 'X'; metadata[3] += 11;
  }
  return -27;
}
#ifndef ORIGINAL
static int Rules_ReportSystemError(int module, int code) { return hook_error(module, code); }
static int IO_RunRouterExitCallbacks(int code) { return hook_exit(code); }
static int Rules_OpenConstructCodeFile(const char *base, int id, int version, DWORD context, int mode) {
  return hook_open(base, id, version, context, mode);
}
static int sprintf_(char *out, const char *format, ...) {
  __builtin_va_list args; __builtin_va_start(args, format);
  const char *prefix = __builtin_va_arg(args, const char *);
  int image = __builtin_va_arg(args, int); int version = __builtin_va_arg(args, int);
  __builtin_va_end(args); return hook_sprintf(out, format, prefix, image, version);
}
static int Output_WriteFormatted(int, int, int stream, int format, ...) {
  const char *fmt = (const char *)(uintptr_t)(unsigned)format;
  unsigned structure = 0, array = 0;
  if (fmt != asc_508250) {
    __builtin_va_list args; __builtin_va_start(args, format);
    structure = (unsigned)__builtin_va_arg(args, int); array = (unsigned)__builtin_va_arg(args, int);
    __builtin_va_end(args);
  }
  return hook_output(stream, fmt, structure, array);
}
#endif
'''
MAIN = r'''
#ifdef ORIGINAL
extern "C" int original_call(int, const char *, int, const char *, int *, int, int, const char *, const char *, int, const char **);
#define CALL original_call
#else
#define CALL Rules_ConstructCodeFileOpen
#endif
static void run(const Case &c) {
  const int ids[] = {3, -1, (-2147483647 - 1)};
  const int images[] = {0, -1, 2147483647};
  const int arrays[] = {0, 17, (-2147483647 - 1)};
  counter = c.count; side_effects = c.effects; open_result = c.opened;
  active_base = bases[c.style]; active_type = structures + c.low;
  copy(active_type, types[c.style]);
  metadata[0] = 0x12481248; metadata[4] = 0x87654321; metadata[5] = 0x98765432;
  metadata[1] = (unsigned)(uintptr_t)remembered; metadata[2] = (unsigned)-7; metadata[3] = 99;
  if ((uintptr_t)active_type > 0x7fffffffu || ((uintptr_t)active_type & 255) != (unsigned)c.low) __builtin_trap();
  last_buffer = 0;
  int result = CALL(c.stream, active_base, images[c.style], (const char *)(uintptr_t)(unsigned)ids[c.style],
                    &counter, arrays[c.style], 23, active_type, prefixes[c.style], c.mode,
                    c.info ? (const char **)(metadata + 1) : 0);
  if (metadata[0] != 0x12481248 || metadata[4] != 0x87654321 || metadata[5] != 0x98765432) __builtin_trap();
  text("R|"); number(result); put('|'); snapshot(); put('\n'); write_record();
}
extern "C" int fixture_main(int argc, char **argv) {
  if (argc == 2) {
    unsigned index = (unsigned)(argv[1][0] - '0');
    if (index >= sizeof(fatal_cases) / sizeof(fatal_cases[0])) return 5;
    terminal_exit = 1; run(fatal_cases[index]); return 6;
  }
  for (unsigned i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) run(cases[i]);
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
  mov eax, [esp+20]
  mov edx, [esp+24]
  mov ecx, [esp+28]
  mov ebx, [esp+32]
  .rept 7
  push DWORD PTR [esp+60]
  .endr
  call sub_4A79F0
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
sprintf_:
  preserve
  mov ebp, esp
  push DWORD PTR [ebp+44]
  push DWORD PTR [ebp+40]
  push DWORD PTR [ebp+36]
  push DWORD PTR [ebp+32]
  push DWORD PTR [ebp+28]
  call hook_sprintf
  add esp, 20
  restore
sub_476301:
  preserve
  mov ebp, esp
  xor eax, eax
  xor ebx, ebx
  cmp DWORD PTR [ebp+32], offset asc_508250
  je output_args
  mov eax, [ebp+36]
  mov ebx, [ebp+40]
output_args:
  push ebx
  push eax
  push DWORD PTR [ebp+32]
  push DWORD PTR [ebp+28]
  call hook_output
  add esp, 16
  restore
.section .note.GNU-stack,"",@progbits
'''


def original_procedure():
    assembly = (ROOT / 'clash95.asm').read_text()
    return re.search(r'^sub_4A79F0\s+proc\b.*?^sub_4A79F0\s+endp', assembly, re.M | re.S).group()


def assemble_listing(procedure):
    result = ['.intel_syntax noprefix', '.text', 'sub_4A79F0:', '.equ var_60, -0x60', '.equ var_10, -0x10']
    result += [f'.equ arg_{offset:X}, {offset + 4}' for offset in range(0, 28, 4)]
    for line in procedure.splitlines():
        code = line.split(';', 1)[0].strip()
        if not code or '=' in code or re.search(r'\b(proc|endp)\b', code):
            continue
        code = re.sub(r'\b([0-9][0-9A-Fa-f]*)h\b', lambda m: '0x' + m[1], code)
        code = re.sub(r'^cmp\s+\[', 'cmp DWORD PTR [', code)
        result.append(code.replace('short ', '').replace('retn', 'ret'))
    return '\n'.join(result) + '\n' + HOOKS


def calls_in(text):
    masked = mask_c(text)
    for match in re.finditer(NAME + r'\s*\(', masked):
        depth = 1
        end = match.end()
        positions = [end]
        while depth:
            if masked[end] == ',' and depth == 1:
                positions.append(end + 1)
            depth += (masked[end] == '(') - (masked[end] == ')')
            end += 1
        positions.append(end)
        yield [text[a:b - 1].strip() for a, b in zip(positions, positions[1:])]


class ConstructOpenSourceTests(unittest.TestCase):
    def test_original_procedure_is_pinned(self):
        self.assertEqual(hashlib.sha256(original_procedure().encode()).hexdigest(),
                         '22cc745fdd09bc30193a077d1b2fa17edbff2ca0574f02e3159db3c3879952fb')

    def test_manifest_and_declaration_follow_production(self):
        source = SOURCE.read_text()
        definition, = scan_definitions(source, {NAME})
        manifest = json.loads((ROOT / 'data/recovered_sources.json').read_text())
        entry, = [e for e in manifest['functions'] if e['name'] == NAME]
        self.assertEqual(entry['body_sha256'], body_sha256(source, definition))
        self.assertEqual(entry['original_address'], '0x004A79F0')
        self.assertIn('const char *structureName', source[definition.start:definition.opening_brace])
        self.assertIn('const char *structureName', (ROOT / 'src/clips/clips_api.h').read_text())

    def test_all_callers_preserve_original_structure_name_pointers(self):
        assembly = (ROOT / 'clash95.asm').read_text()
        manifest = json.loads((ROOT / 'data/recovered_sources.json').read_text())
        total = 0
        for match in re.finditer(r'^(sub_[0-9A-F]+)\s+proc\b.*?^\1\s+endp', assembly, re.M | re.S):
            procedure = match.group()
            original_calls = list(re.finditer(r'\bcall\s+sub_4A79F0\b', procedure))
            if not original_calls:
                continue
            address = '0x00' + match[1][4:]
            entry, = [e for e in manifest['functions'] if e['original_address'] == address]
            source = (ROOT / entry['source']).read_text()
            definition, = scan_definitions(source, {entry['name']})
            actual = list(calls_in(source[definition.opening_brace:definition.end]))
            self.assertEqual(len(actual), len(original_calls), entry['name'])
            for call, args in zip(original_calls, actual):
                self.assertEqual(len(args), 11)
                self.assertRegex(args[7], r'^a[A-Za-z0-9_]+$')
                window = procedure[:call.start()].splitlines()[-45:]
                self.assertTrue(any(re.search(r'\b(?:push|mov)\s+(?:\w+, )?offset ' + args[7] + r'\b', line)
                                    for line in window), (entry['name'], args[7]))
            total += len(actual)
        self.assertEqual(total, 34)

    def test_matrix_covers_every_structure_pointer_low_byte(self):
        self.assertEqual({case[-1] for case in CASES}, set(range(256)))
        self.assertEqual({case[0] for case in CASES}, set(MODES))
        self.assertEqual(EXPECTED.count(b'R|'), len(CASES))
        self.assertEqual(len(CASES), 2032)
        self.assertEqual(EXPECTED_SHA256, '2e9ccce3f5ab3a53589e8472775dfebca87aed71ef73924d3d7c788f1a9a93ff')


@unittest.skipUnless(sys.platform.startswith('linux') and platform.machine() in ('x86_64', 'amd64'), 'requires x86 Linux')
class ConstructOpenNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        requested = os.environ.get('CLASH95_CONSTRUCT_TEST_CXX')
        if requested:
            compiler = shutil.which(requested)
            if compiler is None:
                raise RuntimeError('Requested compiler unavailable: ' + requested)
            cls.compilers = [compiler]
        else:
            cls.compilers = list(dict.fromkeys(filter(None, [shutil.which('g++-13') or shutil.which('g++'),
                                                           shutil.which('clang++-18') or shutil.which('clang++')])))
        if not cls.compilers:
            raise unittest.SkipTest('C++ compiler required')
        cls.directory = tempfile.TemporaryDirectory(prefix='clash-construct-open-')
        cls.addClassCleanup(cls.directory.cleanup)
        cls.work = Path(cls.directory.name)
        (cls.work / 'entry32.s').write_text(ENTRY32)
        (cls.work / 'entry64.s').write_text(ENTRY64)
        (cls.work / 'original.s').write_text(assemble_listing(original_procedure()))
        source = SOURCE.read_text()
        definition, = scan_definitions(source, {NAME})
        cls.body = source[definition.start:definition.end]
        cls.tables = ''
        for name, cases in [('cases', CASES), ('fatal_cases', FATAL_CASES)]:
            cls.tables += 'static const Case ' + name + '[] = {\n' + ',\n'.join(
                '{' + ','.join(str(v) for v in case) + '}' for case in cases) + '\n};\n'

    @classmethod
    def build(cls, compiler, optimization, bits, signed_char=True, original=False, body=None):
        source = cls.work / 'fixture.cpp'
        source.write_text(PRELUDE + ('\n' if original else cls.body if body is None else body) + cls.tables + MAIN)
        binary = cls.work / 'fixture'
        command = [compiler, '-std=gnu++20', optimization, '-m' + str(bits), '-ffreestanding',
                   '-fno-builtin', '-fno-pie', '-fno-exceptions', '-fno-rtti', '-fno-stack-protector',
                   '-nostdlib', '-static', '-Wl,-no-pie', '-Wl,--build-id=none',
                   '-Wall', '-Wextra', '-Wpedantic', '-Werror',
                   '-fsigned-char' if signed_char else '-funsigned-char', str(source), str(cls.work / f'entry{bits}.s')]
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
            return subprocess.run([str(binary), *arguments], capture_output=True, timeout=15, cwd=self.work)
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

    def test_original_instruction_trace_and_terminal_errors(self):
        self.check_trace(self.build(self.compilers[0], '-O0', 32, original=True), 32)

    def test_actual_production_across_all_compiler_profiles(self):
        for compiler, optimization, bits, char_signed in itertools.product(self.compilers, ['-O0', '-O2'], [32, 64], [True, False]):
            with self.subTest(compiler=compiler, optimization=optimization, bits=bits, char_signed=char_signed):
                self.check_trace(self.build(compiler, optimization, bits, char_signed), bits)

    def test_regression_mutations_are_detected(self):
        mutations = [
            self.body.replace('(int)(intptr_t)structureName', '(int)(char)(intptr_t)structureName'),
            self.body.replace('0, 0, result,', '0, 0, 7,'),
            self.body.replace('0, 0, headerFP,', '0, 0, headerFP + 1,'),
            self.body.replace('codeFileInfo + 4', 'codeFileInfo + 8'),
            self.body.replace('codeFileInfo + 8', 'codeFileInfo + 16'),
            self.body.replace('+ 1u', '+ 2u'),
            self.body.replace('return result;', 'return -27;'),
            self.body.replace('(DWORD)(intptr_t)fileName, reopenOldFile', '(DWORD)(intptr_t)fileName, 0'),
            self.body.replace('(int)(intptr_t)aConscomp', '0'),
        ]
        for index, body in enumerate(mutations):
            with self.subTest(mutation=index):
                self.assertNotEqual(body, self.body)
                binary = self.build(self.compilers[0], '-O0', 64, body=body)
                result = self.execute(binary, 64)
                differs = result.returncode != 0 or result.stdout != EXPECTED
                if not differs:
                    result = self.execute(binary, 64, ['0'])
                    differs = result.returncode != 2 or result.stdout != expected(FATAL_CASES[0], terminal=True)
                self.assertTrue(differs)


if __name__ == '__main__':
    unittest.main()
