"""Small local read-only audit. No compilation, imports of fixtures, or tree writes."""
from pathlib import Path
import ast
import json
import sys

sys.dont_write_bytecode = True
from packet_common import PACKET, load_inputs, relative_path, require


def main():
    receipt, expected = load_inputs()
    python_files = list(PACKET.glob('*.py')) + list((PACKET / 'candidate').rglob('*.py'))
    for path in python_files:
        ast.parse(path.read_text(), filename=str(path))
    for unsafe in ('../escape', '/absolute', 'C:/escape', 'dir\\escape', ''):
        try:
            relative_path(unsafe)
        except ValueError:
            continue
        raise ValueError('Unsafe path accepted: ' + unsafe)
    recipe = json.loads((PACKET / 'inputs/metadata-recipe.json').read_text())
    fixture = PACKET / 'candidate/tests/tools/fixtures/class_world_visibility'
    provenance = json.loads((fixture / 'references/provenance.json').read_text())
    require(provenance['reference_commit'] == receipt['reference_commit'], 'Reference pin mismatch')
    for row in provenance['functions']:
        require(row['body_sha256'] == recipe['identities'][row['name']]['baseline']['body_sha256'], 'Frozen identity body mismatch')
    binding = (fixture / 'binding.cpp').read_text()
    for assertion in ('frozen query signed bounds', 'adapter query signed bounds', 'direct query signed bounds',
                      'held object cached arena', 'callback rebinding differs from frozen source'):
        require(assertion in binding, 'Required final binding assertion missing')
    require(len(receipt['expected_overrides']) == 2, 'Only exact final runner refresh is expected')
    for stage in ('extraction', 'relocation'):
        require(set(expected['baseline']).issubset(expected[stage]), 'Lost historical input path')
    print(json.dumps({'pass': True, 'python_files_parsed': len(python_files),
                      'input_files_verified': len(receipt['files']),
                      'stage_file_counts': {stage: len(rows) for stage, rows in expected.items()},
                      'compiler_runs': 0, 'tree_expansions': 0}))


if __name__ == '__main__':
    main()
