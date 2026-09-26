"""Shared path, provenance and metadata helpers for the provisional packet."""
from pathlib import Path, PurePosixPath
import hashlib
import json
import os
import shutil
import subprocess
import sys

sys.dont_write_bytecode = True
PACKET = Path(__file__).resolve().parent
PIN = '705fc0fe9b01b7587a7a6290f15379dbd8a1d264'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def relative_path(value):
    path = PurePosixPath(value)
    require(not path.is_absolute() and path.parts and all(part not in ('.', '..') for part in path.parts), 'Unsafe relative path: ' + value)
    require('\\' not in value and ':' not in value, 'Nonportable path: ' + value)
    return path


def no_links(path):
    path = Path(os.path.abspath(path))
    for parent in (path, *path.parents):
        require(not parent.is_symlink(), 'Symlink path forbidden: ' + str(parent))
        if hasattr(parent, 'is_junction'):
            require(not parent.is_junction(), 'Junction path forbidden: ' + str(parent))
    return path


def load_inputs():
    receipt = json.loads((PACKET / 'input-provenance.json').read_text())
    require(receipt['reference_commit'] == PIN, 'Unexpected frozen source pin')
    for relative, item in receipt['files'].items():
        path = no_links(PACKET / relative_path(relative))
        require(path.is_file() and sha(path) == item['sha256'], 'Packet input mismatch: ' + relative)
    expected_path = PACKET / 'expected-stages.json'
    require(sha(expected_path) == receipt['expected_stages_sha256'], 'Expected-stage map changed')
    return receipt, json.loads(expected_path.read_text())


def hosted_only():
    require(sys.platform == 'linux' and os.environ.get('GITHUB_ACTIONS') == 'true', 'Tree materialization is hosted-only; local disk guard remains in force')


def new_output(value, protected):
    path = no_links(value)
    require(path.is_absolute() and path.parent.is_dir() and not path.exists(), 'Output must be absent with an existing parent')
    require(bool(os.environ.get('RUNNER_TEMP')), 'RUNNER_TEMP must be explicit')
    temporary = no_links(Path(os.environ['RUNNER_TEMP'])).resolve()
    require(path != temporary and path.is_relative_to(temporary), 'Output must be a private RUNNER_TEMP child')
    for root in protected:
        root = no_links(root).resolve()
        require(path != root and not path.is_relative_to(root) and not root.is_relative_to(path), 'Output overlaps a protected tree')
    usage = shutil.disk_usage(path.parent)
    require(usage.used / usage.total < 0.90 and usage.free >= 1024**3, 'Hosted output volume lacks required headroom')
    path.mkdir()
    return path


def tree_hashes(root):
    hashes = {}
    for path in sorted(root.rglob('*')):
        no_links(path)
        if path.is_file():
            hashes[path.relative_to(root).as_posix()] = sha(path)
    return hashes


def compare_tree(root, expected):
    actual = tree_hashes(root)
    differences = {relative: {'expected': expected.get(relative), 'actual': actual.get(relative)}
                   for relative in sorted(set(expected) | set(actual)) if expected.get(relative) != actual.get(relative)}
    return {'pass': not differences, 'file_count': len(actual), 'differences': differences}


def run_metadata(root, output):
    commands = [
        ['tools/gen_subsystem_headers.py', '--write', '--write-tu-includes', 'all'],
        ['tools/migrate_pure_coverage_metadata.py'],
        ['tools/update_split_manifest_hashes.py'],
        ['tools/class_source_inventory.py'],
    ]
    output.mkdir(parents=True, exist_ok=False)
    for index, arguments in enumerate(commands):
        command = [sys.executable, *arguments]
        log = output / f'{index}.log'
        try:
            result = subprocess.run(command, cwd=root, capture_output=True, text=True,
                                    env=dict(os.environ, PYTHONDONTWRITEBYTECODE='1'), timeout=180)
        except subprocess.TimeoutExpired as error:
            def decode(value):
                return value.decode(errors='replace') if isinstance(value, bytes) else (value or '')
            log.write_text(json.dumps(command) + '\nTIMEOUT\n' + decode(error.stdout) + decode(error.stderr))
            raise
        log.write_text(json.dumps(command) + '\n' + result.stdout + result.stderr)
        require(result.returncode == 0, 'Metadata command failed; retained log: ' + str(output / f'{index}.log'))


def copy_candidates(root, check_baseline=False):
    receipt, expected = load_inputs()
    for relative in receipt['files']:
        if not relative.startswith('candidate/'):
            continue
        target_relative = relative.removeprefix('candidate/')
        destination = root / relative_path(target_relative)
        if check_baseline:
            baseline_hash = expected['baseline'].get(target_relative)
            require((sha(destination) if destination.is_file() else None) == baseline_hash,
                    'Incoming fixture differs from pin: ' + target_relative)
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes((PACKET / relative).read_bytes())


def append_allowances(root, recipe):
    additions = json.loads((PACKET / 'inputs/object-audit/allowance-additions.json').read_text())
    for suffix in recipe['allowance_suffixes']:
        path = root / ('data/class_migration' + suffix + '_text_additions.json')
        document = json.loads(path.read_text())
        for profile, fields in additions['profiles'].items():
            for field, rows in fields.items():
                names = {row['name'] for row in rows}
                require(not any(row['name'] in names for row in document['profiles'][profile][field]), 'Allowance already present')
                document['profiles'][profile][field].extend(rows)
        path.write_text(json.dumps(document, indent=2) + '\n')
