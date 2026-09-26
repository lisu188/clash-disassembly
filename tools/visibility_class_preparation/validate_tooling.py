#!/usr/bin/env python3
"""Run corrected public wrappers and focused metadata gates on hosted candidates."""
from pathlib import Path
import argparse
import json
import os
import re
import shutil
import subprocess
import sys

sys.dont_write_bytecode = True
from packet_common import PACKET, hosted_only, load_inputs, new_output, no_links, require


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--compiler', choices=('g++-13', 'clang++-18'), required=True)
    parser.add_argument('--metadata-only', action='store_true')
    args = parser.parse_args()
    hosted_only()
    load_inputs()
    root = no_links(args.root).resolve()
    require(shutil.which(args.compiler) is not None, 'Required compiler missing: ' + args.compiler)
    require(shutil.which('g++') is not None, 'Focused header-policy gate requires g++ preprocessing')
    output = new_output(args.output, [root, PACKET, Path(os.environ['GITHUB_WORKSPACE'])])
    compiler = 'gcc' if args.compiler == 'g++-13' else 'clang'
    commands = []
    if not args.metadata_only:
        selectors = [
            'test_reveal_propagation.RevealPropagationTest.test_' + compiler + '_actual_propagation',
            'test_fog_overlay.FogOverlayTest.test_' + compiler + '_truth_table_and_visibility_order',
            'test_class_world_visibility.WorldVisibilityBindingTest.test_' + compiler + '_binding_lifecycle',
        ]
        for selector in selectors:
            commands.append((selector, root / 'tests/tools', ['-m', 'unittest', selector, '-v']))
    for tool in (
        ['tools/class_source_inventory.py'],
        ['tools/gen_subsystem_headers.py', '--check', '--check-tu-includes'],
        ['tools/migrate_pure_coverage_metadata.py', '--check'],
        ['tools/game_class_catalog.py', '--check'],
        ['tools/audit_split_sources.py'],
    ):
        commands.append((Path(tool[0]).stem, root, tool))
    focused = ['test_class_source_index', 'test_class_source_inventory', 'test_class_manifest_integration',
               'test_class_binding_inventory', 'test_class_coverage', 'test_class_header_policy',
               'test_gen_subsystem_headers', 'test_scoped_manifest_hash_update', 'test_game_class_catalog']
    commands.append(('focused-tooling', root / 'tests/tools', ['-m', 'unittest', *focused, '-v']))
    summary = {'pass': False, 'root': str(root), 'compiler': args.compiler, 'commands': []}
    for index, (label, cwd, arguments) in enumerate(commands):
        command = [sys.executable, *arguments]
        log = output / (str(index) + '-' + label + '.log')
        try:
            result = subprocess.run(command, cwd=cwd, capture_output=True, text=True,
                                    env=dict(os.environ, PYTHONDONTWRITEBYTECODE='1', TMPDIR=str(output)), timeout=600)
            text = result.stdout + result.stderr
            log.write_text(json.dumps(command) + '\n' + text)
            skipped = bool(re.search(r'^.+ \.\.\. skipped\b|^(?:OK|FAILED) \([^\n)]*\bskipped=[1-9][0-9]*', text, re.MULTILINE))
            row = {'label': label, 'command': command, 'exit': result.returncode,
                   'unexpected_skip': skipped, 'log': log.name}
        except subprocess.TimeoutExpired as error:
            def decode(value):
                return value.decode(errors='replace') if isinstance(value, bytes) else (value or '')
            log.write_text(json.dumps(command) + '\n' + decode(error.stdout) + decode(error.stderr))
            row = {'label': label, 'command': command, 'exit': None, 'timeout': True, 'log': log.name}
        summary['commands'].append(row)
        (output / 'tooling-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    summary['pass'] = all(row['exit'] == 0 and not row.get('unexpected_skip', False) for row in summary['commands'])
    (output / 'tooling-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary, indent=2))
    return 0 if summary['pass'] else 1


if __name__ == '__main__':
    raise SystemExit(main())
