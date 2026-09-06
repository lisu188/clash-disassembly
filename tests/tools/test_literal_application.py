"""Scoped literal plans retain site identity with one canonical source census."""
from pathlib import Path
import json
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import apply_literal_names as apply


class LiteralApplicationTests(unittest.TestCase):
    def test_ledger_does_not_repeat_aggregate_counts_for_scoped_rules(self):
        rules = [dict(name='SLOT_BYTES', value=31, kind='regex', evidence='read site'),
                 dict(name='SLOT_BYTES', value=31, kind='regex', evidence='write site')]
        plan = dict(rules=rules, batch='fixture', rejected=[], summary={
            'SLOT_BYTES': dict(sites=2, classes={'regex': 2}, files={'first.cpp': 2})})
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'ledger.jsonl'
            with patch.object(apply.lc, 'load_manifest', return_value=(
                    [dict(name='SLOT_BYTES', spelling='31')], {})):
                self.assertEqual(apply.append_accum(plan, str(path)), 1)
            rows = [json.loads(line) for line in path.read_text().splitlines()]
        self.assertEqual(sum(row['sites'] for row in rows), 2)
        self.assertEqual(rows[0]['rule_count'], 2)
        self.assertEqual(rows[0]['evidence'], 'read site\nwrite site')

    def test_source_and_function_scopes_share_one_inventory(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'first.cpp').write_text('int first(void)\n{\n  return 31;\n}\n'
                                          'int second(void)\n{\n  return 31;\n}\n')
            (root / 'second.cpp').write_text('int first(void)\n{\n  return 31;\n}\n')
            rules = [dict(kind='regex', name='SLOT_BYTES', value=31,
                          pattern=r'return (?P<lit>31);', files=['first.cpp'], func='first'),
                     dict(kind='regex', name='RECORD_BYTES', value=31,
                          pattern=r'return (?P<lit>31);', files=['second.cpp'], func='first')]
            entries = {r['name']: dict(value=31, spelling='31') for r in rules}
            with patch.object(apply.lc, 'REPO', directory), \
                 patch.object(apply.lc, 'apply_files', return_value=['first.cpp', 'second.cpp']) as files, \
                 patch.object(apply, 'git_head', return_value='fixture'):
                plan = apply.resolve(rules, entries, {}, 'fixture')
            self.assertEqual(files.call_count, 1)
            self.assertEqual([(s['file'], s['fn'], s['name'], s['raw']) for s in plan['entries']],
                             [('first.cpp', 'first', 'SLOT_BYTES', '31'),
                              ('second.cpp', 'first', 'RECORD_BYTES', '31')])
            self.assertEqual(plan['rejected'], [])
            self.assertIn('return 31;', (root / 'first.cpp').read_text())


if __name__ == '__main__':
    unittest.main()
