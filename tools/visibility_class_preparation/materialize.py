#!/usr/bin/env python3
"""Materialize pinned visibility candidates on hosted CI; never compile anything."""
from pathlib import Path
import argparse
import copy
import json
import os
import shutil
import subprocess
import sys
import tarfile
import traceback

sys.dont_write_bytecode = True
from packet_common import (PACKET, PIN, append_allowances, compare_tree, copy_candidates,
                           hosted_only, load_inputs, new_output, no_links,
                           relative_path, require, run_metadata)


def archive_baseline(repo, destination):
    destination.mkdir()
    command = ['git', '-C', str(repo), 'archive', PIN, 'src', 'tools', 'data',
               'tests/tools', 'tests/unit/pure_set.json']
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    seen, total = set(), 0
    try:
        with tarfile.open(fileobj=process.stdout, mode='r|') as archive:
            for member in archive:
                relative = relative_path(member.name)
                require(member.isdir() or member.isfile(), 'Archive link or special file rejected')
                target = destination / relative
                if member.isdir():
                    target.mkdir(parents=True, exist_ok=True)
                    continue
                require(member.name not in seen and member.size <= 16 * 1024**2, 'Duplicate or oversized source member')
                require(member.name.startswith(('src/', 'tools/', 'data/', 'tests/tools/')) or member.name == 'tests/unit/pure_set.json', 'Unexpected source member')
                seen.add(member.name)
                total += member.size
                require(total <= 256 * 1024**2, 'Source archive exceeds bounded size')
                target.parent.mkdir(parents=True, exist_ok=True)
                target.write_bytes(archive.extractfile(member).read())
        error = process.communicate(timeout=30)[1]
        require(process.returncode == 0, 'git archive failed: ' + error.decode(errors='replace'))
    finally:
        if process.poll() is None:
            process.kill()
            process.wait()


def prepare_stage(baseline, destination, stage):
    shutil.copytree(baseline, destination)
    sys.path.insert(0, str(baseline / 'tools'))
    from split_source_index import scan_definitions, body_sha256
    recipe = json.loads((PACKET / 'inputs/metadata-recipe.json').read_text())
    manifest = json.loads((baseline / 'data/recovered_sources.json').read_text())
    rows = {row['name']: row for row in manifest['functions']}
    require(len(rows) == 4157, 'Historical identity count changed')
    original = (baseline / recipe['source']).read_text()
    source = original
    methods = []
    for name, states in recipe['identities'].items():
        row = rows[name]
        for key, value in states['baseline'].items():
            require(row[key] == value, 'Frozen identity mismatch: ' + name + ' ' + key)
        definition, = scan_definitions(source, {name})
        require(body_sha256(source, definition) == row['body_sha256'], 'Frozen body changed: ' + name)
        method = (PACKET / 'inputs/canonical' / (name + '.cpp')).read_text().rstrip('\n')
        adapter = (PACKET / 'inputs/adapters' / (name + '.cpp')).read_text().rstrip('\n')
        methods.append(method)
        source = source[:definition.start] + adapter + ('\n\n' + method if stage == 'extraction' else '') + source[definition.end:]
        row.update(copy.deepcopy(states[stage]))
    marker = '/* CLASH95_GENERATED_INCLUDES_END */'
    require(source.count(marker) == 1, 'Generated include anchor changed')
    source = source.replace(marker, '#include "../world/WorldMap.hpp"\n' + marker)
    source = source.rstrip() + '\n\n// Borrowing glue remains at the original adapter anchor.\n' + (PACKET / 'inputs/WorldMap-borrow.cpp').read_text()
    (destination / recipe['source']).write_text(source)
    (destination / recipe['header']).write_bytes((PACKET / 'inputs/WorldMap.hpp').read_bytes())
    registry = json.loads((baseline / 'data/game_class_registry.json').read_text())
    require(not any(row['class_owner'] == 'WorldMap' for row in registry['class_bindings']), 'Binding already exists')
    registry['class_bindings'].append(copy.deepcopy(recipe['binding']))
    (destination / 'data/game_class_registry.json').write_text(json.dumps(registry, indent=2) + '\n')
    if stage == 'relocation':
        preamble = original[:original.index(marker) + len(marker)]
        preamble = preamble.replace(marker, '#include "../world/WorldMap.hpp"\n' + marker)
        (destination / recipe['class_source']).write_text('// Relocated recovered methods; ABI adapters and storage remain at their original anchor.\n' + preamble + '\n\n' + '\n\n'.join(methods) + '\n')
        group, = [group for group in manifest['source_inventory'] if group['group'] == 'world']
        require(recipe['class_source'] not in group['sources'], 'Class source already present')
        group['sources'].append(recipe['class_source'])
        manifest['source_file_count'] = sum(len(group['sources']) for group in manifest['source_inventory'])
        cmake = destination / 'src/sources.cmake'
        text = cmake.read_text()
        needle = '  ${CMAKE_CURRENT_SOURCE_DIR}/src/world/WorldGeometry.cpp\n'
        require(text.count(needle) == 1, 'Pinned CMake anchor changed')
        cmake.write_text(text.replace(needle, needle + '  ${CMAKE_CURRENT_SOURCE_DIR}/' + recipe['class_source'] + '\n'))
    (destination / 'data/recovered_sources.json').write_text(json.dumps(manifest, indent=2) + '\n')
    append_allowances(destination, recipe)
    copy_candidates(destination, check_baseline=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repo', type=Path)
    parser.add_argument('--output', type=Path)
    parser.add_argument('--audit-inputs', action='store_true')
    args = parser.parse_args()
    receipt, expected = load_inputs()
    if args.audit_inputs:
        require(args.repo is None and args.output is None, 'Audit mode takes no tree paths')
        print(json.dumps({'pass': True, 'reference_commit': PIN, 'candidate_inputs': len(receipt['files']), 'compilation': 'not performed'}))
        return 0
    require(args.repo is not None and args.output is not None, '--repo and --output are required')
    hosted_only()
    repo = no_links(args.repo).resolve()
    pin = subprocess.check_output(['git', '-C', str(repo), 'rev-parse', PIN + '^{commit}'], text=True).strip()
    require(pin == PIN, 'Frozen commit unavailable; fetch explicit history')
    output = new_output(args.output, [repo, PACKET])
    summary = {'pass': False, 'reference_commit': PIN, 'stages': {}}
    try:
        archive_baseline(repo, output / 'baseline')
        summary['stages']['baseline'] = compare_tree(output / 'baseline', expected['baseline'])
        require(summary['stages']['baseline']['pass'], 'Pinned baseline differs from retained freeze')
        for stage in ('extraction', 'relocation'):
            prepare_stage(output / 'baseline', output / stage, stage)
            run_metadata(output / stage, output / 'metadata-logs' / stage)
            summary['stages'][stage] = compare_tree(output / stage, expected[stage])
            require(summary['stages'][stage]['pass'], 'Prepared stage differs; inspect summary before changing expected hashes')
        summary['pass'] = True
    except BaseException:
        summary['failure'] = traceback.format_exc()
        raise
    finally:
        (output / 'materialization-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
        print(json.dumps(summary, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
