#!/usr/bin/env python3
"""Verify the actual radix helpers against original-assembly output contracts.

clash95.asm:183479-183549 stores a zero before the reversed digits, uses the
37-byte table at 0x519f20, wraps NEG EAX, and returns the original destination.
The private PE-byte execution proof is supplementary; this test needs no assets.
"""

from pathlib import Path
import platform
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from split_source_index import scan_definitions


HARNESS = r"""
int main(int argc, char **argv) {
  if (argc != 2) return 2;
  FILE *input = fopen(argv[1], "rb");
  if (!input) return 3;
  unsigned int row[3];
  unsigned char expected[64];
  static unsigned char output[64];
  if ((uintptr_t)(output + sizeof(output)) > UINT32_MAX) return 4;
  unsigned int index = 0;
  while (fread(row, sizeof(row), 1, input) == 1) {
    if (fread(expected, sizeof(expected), 1, input) != 1) return 5;
    memset(output, 0xa5, sizeof(output));
    char *buffer = (char *)output + 8;
    uint32_t result = row[2]
        ? (uint32_t)Str_FormatSignedRadixDigits((int)row[0], buffer, row[1])
        : (uint32_t)(uintptr_t)Str_FormatUnsignedRadixDigits(row[0], buffer, row[1]);
    result -= (uint32_t)(uintptr_t)buffer;
    memcpy(output, &result, sizeof(result));
    if (memcmp(output, expected, sizeof(output))) {
      fprintf(stderr, "case %u value=%u radix=%u signed=%u differs\n",
              index, row[0], row[1], row[2]);
      return 6;
    }
    ++index;
  }
  int failed = ferror(input);
  fclose(input);
  return failed ? 7 : 0;
}
"""


def expected_record(value, radix, signed):
    negative = signed and radix == 10 and value & 0x80000000
    if negative:
        value = (-value) & 0xffffffff
    digits = "0123456789abcdefghijklmnopqrstuvwxyz"
    answer = ""
    while True:
        answer = digits[value % radix] + answer
        value //= radix
        if not value:
            break
    output = (("-" if negative else "") + answer).encode() + b"\0"
    result = bytearray(b"\xa5" * 64)
    result[:4] = b"\0" * 4
    result[8:8 + len(output)] = output
    return result


class RadixFormatterTests(unittest.TestCase):
    @unittest.skipUnless(sys.platform == "linux" and platform.machine() == "x86_64",
                         "the recovered low32 ABI requires a Linux x86_64 non-PIE fixture")
    def test_original_digits_termination_return_and_bounds(self):
        source = (ROOT / "src/media/004753E0_00477CC0_media_010.cpp").read_text()
        names = {"Str_FormatUnsignedRadixDigits", "Str_FormatSignedRadixDigits"}
        definitions = list(scan_definitions(source, names))
        self.assertEqual({definition.name for definition in definitions}, names)
        state = (ROOT / "src/state/00000000_0054FFFF_recovered_state.cpp").read_text()
        table = re.findall(r"^char g_Str_RadixDigitCharacters\[[^\]]*\]\s*=\s*[^;]+;",
                           state, re.MULTILINE)
        self.assertEqual(len(table), 1)
        fixture = "#include <stdint.h>\n#include <stdio.h>\n#include <string.h>\n"
        fixture += table[0] + "\n"
        fixture += "\n".join(source[d.start:d.end] for d in definitions) + HARNESS
        values = [0, 1, 2, 9, 10, 15, 16, 35, 36, 99, 100, 255, 256,
                  0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff]
        seed = 0x4761ef
        for _ in range(128):
            seed = (1664525 * seed + 1013904223) & 0xffffffff
            values.append(seed)
        cases = bytearray()
        for value in values:
            for radix in range(2, 37):
                for signed in (0, 1):
                    cases += struct.pack("<III", value, radix, signed)
                    cases += expected_record(value, radix, signed)
        compilers = [c for c in ("g++-13", "clang++-18") if shutil.which(c)]
        if not compilers:
            self.skipTest("no supported C++ compiler installed")
        with tempfile.TemporaryDirectory(prefix="clash95-radix-") as directory:
            work = Path(directory)
            probe = work / "probe.cpp"
            probe.write_text(fixture)
            inputs = work / "cases.bin"
            inputs.write_bytes(cases)
            for compiler in compilers:
                for optimization in ("-O0", "-O2"):
                    for checked in (False, True):
                        with self.subTest(compiler=compiler, optimization=optimization,
                                          undefined_behavior_checks=checked):
                            binary = work / "probe"
                            command = [compiler, "-std=gnu++20", optimization, "-fno-pie",
                                       "-no-pie", "-Wall", "-Wextra", "-Werror"]
                            if checked:
                                command += ["-fsanitize=undefined",
                                            "-fsanitize-undefined-trap-on-error"]
                            command += [str(probe), "-o", str(binary)]
                            compiled = subprocess.run(command, text=True, capture_output=True,
                                                      timeout=30)
                            self.assertEqual(compiled.returncode, 0, compiled.stderr)
                            result = subprocess.run([str(binary), str(inputs)], text=True,
                                                    capture_output=True, timeout=10)
                            self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main()
