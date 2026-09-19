#!/usr/bin/env python3
"""Actual plague setter versus original-measured high-bit pointers and full bytes."""
from pathlib import Path
import hashlib
import importlib.util
import json
import os
import platform
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.dont_write_bytecode = True
ROOT = Path(os.environ.get('CLASH95_SOURCE_ROOT', Path(__file__).resolve().parents[2])).resolve()
FIXTURE = Path(__file__).parent / 'fixtures/unit_stack_set_plague_low32'
sys.path.insert(0, str(ROOT / 'tools'))
from recovered_implementation import index_manifest_definitions

spec = importlib.util.spec_from_file_location('plague_low32_contract', FIXTURE / 'contract.py')
contract = importlib.util.module_from_spec(spec)
spec.loader.exec_module(contract)


class PlagueLow32RepairTests(unittest.TestCase):
    @unittest.skipUnless(sys.platform == 'linux' and platform.machine() == 'x86_64',
                         'requires Linux low32 mappings')
    def test_actual_canonical_implementation_matches_original(self):
        name = 'UnitStack_SetPlagueFlag'
        proof = json.loads((FIXTURE / 'provenance.json').read_text())
        manifest = json.loads((ROOT / 'data/recovered_sources.json').read_text())
        row = next(r for r in manifest['functions'] if r['name'] == name)
        self.assertEqual(row['original_address'], '0x00412A90')
        if row['implementation']['kind'] == 'free':
            self.assertEqual(row['body_sha256'], proof['after_body_sha256'])
        sources = {row['source']}
        if 'adapter' in row:
            sources.add(row['adapter']['source'])
        definitions = index_manifest_definitions(manifest, ROOT, sources)
        bodies = []
        for role in ['canonical'] + (['adapter'] if 'adapter' in row else []):
            resolved = definitions[name, role]
            expected_hash = row['body_sha256'] if role == 'canonical' else row['adapter']['body_sha256']
            self.assertEqual(resolved.body_sha256, expected_hash)
            source = (ROOT / resolved.target.source).read_text()
            definition = resolved.definition
            bodies.append(source[definition.start:definition.end])
        inputs = b''.join(contract.cases())
        expected = b''.join(contract.expected(inputs[i:i+808]) for i in range(0, len(inputs), 808))
        self.assertEqual(len(inputs) // 808, proof['case_count'])
        self.assertEqual(hashlib.sha256(inputs).hexdigest(), proof['input_sha256'])
        self.assertEqual(hashlib.sha256(expected).hexdigest(), proof['output_sha256'])
        results = []
        with tempfile.TemporaryDirectory(prefix='clash95-plague-low32-') as temporary:
            directory = Path(temporary)
            source = directory / 'probe.cpp'
            source.write_text((FIXTURE / 'harness.cpp').read_text().replace('__TARGET__', '\n'.join(bodies)))
            for compiler in ['g++-13', 'clang++-18']:
                self.assertIsNotNone(shutil.which(compiler))
                for optimization in ['-O0', '-O2']:
                    for unsigned_char in [False, True]:
                        label = compiler + optimization + ('-unsigned' if unsigned_char else '-signed')
                        binary = directory / label
                        command = [compiler, '-std=gnu++20', '-U_GNU_SOURCE', optimization,
                                   '-fno-pie', '-no-pie', '-fno-exceptions', '-fno-rtti',
                                   '-Wall', '-Wextra', '-Werror', '-fsanitize=undefined',
                                   '-fno-sanitize-recover=all', '-I', str(ROOT / 'src'),
                                   str(source), '-o', str(binary)]
                        if unsigned_char:
                            command.append('-funsigned-char')
                        built = subprocess.run(command, capture_output=True, text=True, timeout=90)
                        self.assertEqual(built.returncode, 0, built.stderr)
                        # Works with a noexec RAM-backed TMPDIR as well as /tmp.
                        image = binary.read_bytes()
                        descriptor = os.memfd_create('clash95-plague-low32', 0)
                        try:
                            os.write(descriptor, image)
                            ran = subprocess.run(['/proc/self/fd/' + str(descriptor)],
                                                 pass_fds=(descriptor,), input=inputs,
                                                 capture_output=True, timeout=90)
                        finally:
                            os.close(descriptor)
                        result = {'profile': label, 'command': command, 'exit': ran.returncode,
                                  'binary_sha256': hashlib.sha256(image).hexdigest(),
                                  'output_sha256': hashlib.sha256(ran.stdout).hexdigest(),
                                  'stderr': ran.stderr.decode(errors='replace')}
                        results.append(result)
                        self.assertEqual(ran.returncode, 0, result['stderr'])
                        self.assertEqual(len(ran.stdout), len(expected))
                        self.assertEqual(hashlib.sha256(ran.stdout).digest(), hashlib.sha256(expected).digest())
        print(json.dumps({'case_count': proof['case_count'], 'profiles': results}))


if __name__ == '__main__':
    unittest.main()
