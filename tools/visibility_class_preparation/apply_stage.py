#!/usr/bin/env python3
"""Apply the narrow reviewed recipe to an explicitly selected private tree.

Dry run is the default. Writes require a hosted RUNNER_TEMP tree and never
target the workflow checkout. This is separate from stage materialization.
"""
from pathlib import Path
import argparse
import copy
import hashlib
import json
import os
import sys

sys.dont_write_bytecode = True
from packet_common import (PACKET, hosted_only, load_inputs, no_links,
                           relative_path, require)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, required=True)
    parser.add_argument('--stage', choices=('extraction', 'relocation'), required=True)
    parser.add_argument('--write', action='store_true')
    args = parser.parse_args()
    receipt, expected_stages = load_inputs()
    root = no_links(args.root).resolve()
    require(root.is_dir(), 'Recipe root is missing')
    if args.write:
        hosted_only()
        temporary = no_links(Path(os.environ['RUNNER_TEMP'])).resolve()
        workspace = no_links(Path(os.environ['GITHUB_WORKSPACE'])).resolve()
        require(root != temporary and root.is_relative_to(temporary), 'Writes require a private RUNNER_TEMP child')
        require(root != workspace and not root.is_relative_to(workspace) and not root.is_relative_to(PACKET), 'Protected source tree')
    sys.path.insert(0, str(root / 'tools'))
    from split_source_index import scan_definitions, body_sha256
    recipe = json.loads((PACKET / 'inputs/metadata-recipe.json').read_text())
    changes = {}

    def read(relative):
        relative_path(relative)
        path = no_links(root / relative)
        return changes.get(relative, path.read_text() if path.exists() else '')

    def put(relative, text):
        relative_path(relative)
        no_links(root / relative)
        changes[relative] = text

    def definition(text, name):
        found, = scan_definitions(text, {name})
        return found

    manifest = json.loads(read('data/recovered_sources.json'))
    rows = {row['name']: row for row in manifest['functions']}
    require(len(rows) == 4157, 'Historical identity count changed')
    prior = 'baseline' if args.stage == 'extraction' else 'extraction'
    for name, states in recipe['identities'].items():
        row = rows[name]
        for key, value in states[prior].items():
            require(row[key] == value, 'Incoming identity mismatch: ' + name + ' ' + key)
        source = read(recipe['source'])
        current = definition(source, row['implementation']['qualified_name'])
        require(body_sha256(source, current) == row['body_sha256'], 'Incoming body changed')
        if args.stage == 'extraction':
            method = (PACKET / 'inputs/canonical' / (name + '.cpp')).read_text().strip()
            adapter = (PACKET / 'inputs/adapters' / (name + '.cpp')).read_text().strip()
            source = source[:current.start] + adapter + '\n\n' + method + source[current.end:]
        else:
            require(source[current.start - 2:current.start] == '\n\n', 'Method separator changed')
            source = source[:current.start - 2] + source[current.end:]
        put(recipe['source'], source)
        row.update(copy.deepcopy(states[args.stage]))

    if args.stage == 'extraction':
        require(not read(recipe['header']), 'WorldMap header already exists')
        put(recipe['header'], (PACKET / 'inputs/WorldMap.hpp').read_text())
        source = read(recipe['source'])
        marker = '/* CLASH95_GENERATED_INCLUDES_END */'
        require(source.count(marker) == 1, 'Include anchor changed')
        source = source.replace(marker, '#include "../world/WorldMap.hpp"\n' + marker)
        require(not scan_definitions(source, {'clash95::WorldMap::borrow'}), 'Factory already exists')
        source = source.rstrip() + '\n\n// Borrowing glue remains at the original adapter anchor.\n' + (PACKET / 'inputs/WorldMap-borrow.cpp').read_text()
        put(recipe['source'], source)
        registry = json.loads(read('data/game_class_registry.json'))
        require(not any(row['class_owner'] == 'WorldMap' for row in registry['class_bindings']), 'Binding already exists')
        registry['class_bindings'].append(copy.deepcopy(recipe['binding']))
        put('data/game_class_registry.json', json.dumps(registry, indent=2) + '\n')
        additions = json.loads((PACKET / 'inputs/object-audit/allowance-additions.json').read_text())
        for suffix in recipe['allowance_suffixes']:
            relative = 'data/class_migration' + suffix + '_text_additions.json'
            document = json.loads(read(relative))
            for profile, fields in additions['profiles'].items():
                for field, new_rows in fields.items():
                    names = {row['name'] for row in new_rows}
                    require(not any(row['name'] in names for row in document['profiles'][profile][field]), 'Allowance already exists')
                    document['profiles'][profile][field].extend(copy.deepcopy(new_rows))
            put(relative, json.dumps(document, indent=2) + '\n')
        for candidate in receipt['files']:
            if not candidate.startswith('candidate/'):
                continue
            relative = candidate.removeprefix('candidate/')
            # Only the three existing wrapper files have baseline content.
            expected_hash = expected_stages['baseline'].get(relative)
            actual_hash = hashlib.sha256(read(relative).encode()).hexdigest() if (root / relative).exists() else None
            require(actual_hash == expected_hash, 'Incoming fixture changed: ' + relative)
            put(relative, (PACKET / candidate).read_text())
    else:
        require(not read(recipe['class_source']), 'Class source already exists')
        put(recipe['class_source'], (PACKET / 'inputs/relocation-WorldMap.cpp').read_text())
        group, = [group for group in manifest['source_inventory'] if group['group'] == 'world']
        require(recipe['class_source'] not in group['sources'], 'Inventory entry exists')
        group['sources'].append(recipe['class_source'])
        manifest['source_file_count'] = sum(len(group['sources']) for group in manifest['source_inventory'])
        cmake = read('src/sources.cmake')
        begin = cmake.index('set(CLASH95_SPLIT_WORLD_SOURCES')
        end = cmake.index('\n)', begin)
        require(recipe['class_source'] not in cmake, 'CMake source entry exists')
        put('src/sources.cmake', cmake[:end] + '\n  ${CMAKE_CURRENT_SOURCE_DIR}/' + recipe['class_source'] + cmake[end:])
    put('data/recovered_sources.json', json.dumps(manifest, indent=2) + '\n')
    for name in recipe['identities']:
        row = rows[name]
        text = read(row['source'])
        require(body_sha256(text, definition(text, row['implementation']['qualified_name'])) == row['body_sha256'], 'Canonical recipe mismatch')
        text = read(recipe['source'])
        require(body_sha256(text, definition(text, name)) == row['adapter']['body_sha256'], 'Adapter recipe mismatch')
    text = read(recipe['source'])
    require(body_sha256(text, definition(text, recipe['binding']['qualified_name'])) == recipe['binding']['body_sha256'], 'Binding recipe mismatch')
    changed = {relative: text for relative, text in changes.items()
               if not (root / relative).exists() or (root / relative).read_text() != text}
    if args.write:
        for relative, text in changed.items():
            path = root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
    print(json.dumps({'stage': args.stage, 'write': args.write, 'changed_files': {
        relative: hashlib.sha256(text.encode()).hexdigest() for relative, text in changed.items()}}, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
