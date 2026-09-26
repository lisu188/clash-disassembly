#!/usr/bin/env python3
"""Recreate both stages with the narrow recipe and compare every source byte."""
from pathlib import Path
import argparse
import json
import os
import shutil
import subprocess
import sys
import traceback

sys.dont_write_bytecode = True
from packet_common import (PACKET, PIN, compare_tree, hosted_only, load_inputs,
                           new_output, no_links, require, run_metadata, tree_hashes)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--work-root', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    hosted_only()
    _, expected = load_inputs()
    work = no_links(args.work_root).resolve()
    receipt = json.loads((work / 'materialization-summary.json').read_text())
    require(receipt['pass'] and receipt['reference_commit'] == PIN, 'Materialization has not passed')
    for stage in ('baseline', 'extraction', 'relocation'):
        require(compare_tree(work / stage, expected[stage])['pass'], 'Prepared source changed: ' + stage)
    output = new_output(args.output, [work, PACKET, Path(os.environ['GITHUB_WORKSPACE'])])
    tree = output / 'tree'
    shutil.copytree(work / 'baseline', tree)
    summary = {'pass': False, 'reference_commit': PIN, 'stages': {}}
    try:
        for stage in ('extraction', 'relocation'):
            command = [sys.executable, str(PACKET / 'apply_stage.py'), '--root', str(tree), '--stage', stage, '--write']
            log = output / (stage + '-apply.log')
            try:
                result = subprocess.run(command, capture_output=True, text=True,
                                        env=dict(os.environ, PYTHONDONTWRITEBYTECODE='1'), timeout=180)
            except subprocess.TimeoutExpired as error:
                def decode(value):
                    return value.decode(errors='replace') if isinstance(value, bytes) else (value or '')
                log.write_text(json.dumps(command) + '\nTIMEOUT\n' + decode(error.stdout) + decode(error.stderr))
                raise
            log.write_text(json.dumps(command) + '\n' + result.stdout + result.stderr)
            require(result.returncode == 0, 'Recipe application failed: ' + stage)
            run_metadata(tree, output / (stage + '-metadata'))
            summary['stages'][stage] = compare_tree(tree, tree_hashes(work / stage))
            require(summary['stages'][stage]['pass'], 'Recipe differs from independently prepared stage: ' + stage)
        summary['pass'] = True
    except BaseException:
        summary['failure'] = traceback.format_exc()
        raise
    finally:
        (output / 'recipe-summary.json').write_text(json.dumps(summary, indent=2) + '\n')
        print(json.dumps(summary, indent=2))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
