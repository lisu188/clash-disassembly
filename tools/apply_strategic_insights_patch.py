from pathlib import Path
import json
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_source_index import body_sha256, scan_definitions

changes = {}


def replace_once(text, old, new):
    if text.count(old) != 1:
        raise ValueError(f"expected one patch anchor: {old[:120]!r}")
    return text.replace(old, new, 1)


source = Path('src/strategic/004589C0_004602F0_strategic_004.c')
text = source.read_text()
expected = {
    'AI_EvaluateStrategicTargetAtTile': '0cc31bc22fc63c96a39f0491aeac9df07740a9b3c2a4ab43989434421eb01584',
    'UnitStack_RegroupWithBuildingGarrisonByHealth': 'bf311e4fc3be9c55f9a1af8bb74bbdeaa74e34f28886d1411e13628dfd69a4aa',
}
for definition in scan_definitions(text, set(expected)):
    if body_sha256(text, definition) != expected[definition.name]:
        raise ValueError(f"unexpected original body: {definition.name}")
text = replace_once(text, '      AI_CalcStrategicPriorityScore(target_type, tile_x, origin_x, tile_y, origin_y);\n      score = (double)(int)_CHP(v16, filter_type);', '      score = (double)(int)AI_CalcStrategicPriorityScore(target_type, tile_x, origin_x, tile_y, origin_y);')
text = replace_once(text, '  int v16; // [esp+0h] [ebp-20h]\n', '')
text = replace_once(text, '// 459529: variable \'v16\' is possibly undefined\n', '')
text = replace_once(text, 'if ( merged_units[31 * compare_index + 9] > merged_units[compare_offset + 9] )', 'if ( (signed char)merged_units[31 * compare_index + 9] > (signed char)merged_units[compare_offset + 9] )')
text = replace_once(text, 'if ( (char)merged_units[healthy_scan_offset + 9] >= 8 )', 'if ( (signed char)merged_units[healthy_scan_offset + 9] >= 8 )')
changes[source] = text
manifest_path = Path('data/recovered_sources.json')
manifest_text = manifest_path.read_text()
manifest = json.loads(manifest_text)
new_definitions = scan_definitions(text, set(expected))
if len(new_definitions) != len(expected):
    raise ValueError('missing changed function definition')
for definition in new_definitions:
    records = [row for row in manifest['functions'] if row['name'] == definition.name]
    if len(records) != 1 or records[0]['body_sha256'] != expected[definition.name]:
        raise ValueError(f"manifest mismatch: {definition.name}")
    new_hash = body_sha256(text, definition)
    manifest_text = replace_once(manifest_text, '"body_sha256": "' + expected[definition.name] + '"', '"body_sha256": "' + new_hash + '"')
    print('BODY HASH', definition.name, new_hash)
changes[manifest_path] = manifest_text

lhs_path = Path('tools/clash_dat_lhs.py')
text = lhs_path.read_text()
text = replace_once(text, '    tested_slots: tuple[str, ...] = ()\n', '    tested_slots: tuple[str, ...] = ()\n    alpha_test_indices: tuple[int, ...] = ()\n    join_test_index: int = -1\n')
text = replace_once(text, '            alpha_tests: list[str] = []\n', '            alpha_tests: list[str] = []\n            alpha_test_indices: list[int] = []\n')
text, count = re.subn(r'^( +)alpha_tests.append\(render_expression\(ir, expr_index, classes\)\)$', r'\1alpha_test_indices.append(expr_index)\n\g<0>', text, flags=re.M)
if count != 2:
    raise ValueError('expected fact and object alpha-test collection')
text = replace_once(text, '                    alpha_tests=tuple(alpha_tests),\n', '                    alpha_tests=tuple(alpha_tests),\n                    alpha_test_indices=tuple(alpha_test_indices),\n                    join_test_index=join["network_test"],\n')
changes[lhs_path] = text

generator_path = Path('tools/generate_clash_recovered_constraints.py')
text = generator_path.read_text()
text = replace_once(text, '        "condition": condition["order"],\n', '        "condition": condition["order"],\n        "join_index": condition.get("join_index"),\n        "depth": condition.get("depth"),\n        "negated": bool(condition["negated"]),\n        "alpha_test_indices": list(condition.get("alpha_test_indices", ())),\n        "join_test_index": condition.get("join_test_index", -1),\n')
text = replace_once(text, '        ";;; CLASH_recovered.clp",\n', '        ";;; CLASH_recovered.clp",\n        ";;; SOURCE PROJECTION: matcher completeness and gameplay equivalence are separate properties.",\n        ";;; Loading successfully does not establish equivalence; unresolved tests under NOT can suppress activations.",\n')
text = replace_once(text, '        "compiled_test_count": compiled,\n', '        "compiled_test_count": compiled,\n        "matcher_complete": unresolved == 0,\n        "fully_translated_rule_count": sum(item["unresolved_test_count"] == 0 for item in rule_manifest),\n        "unresolved_negated_test_count": sum(\n            condition["unresolved_test_count"]\n            for rule in rule_manifest\n            for condition in rule["conditions"]\n            if condition["negated"]\n        ),\n        "behavioral_equivalence_verified": False,\n')
helper = '''def require_complete_matchers(manifest: dict) -> None:
    unresolved = manifest["unresolved_test_count"]
    rule_total = sum(rule["unresolved_test_count"] for rule in manifest["rules_manifest"])
    if unresolved != rule_total or manifest["compiled_test_count"] != manifest["translated_test_count"] + unresolved:
        raise ValueError("inconsistent matcher completeness counts")
    if unresolved:
        raise ValueError(
            f"matcher completeness required: {unresolved} compiled tests remain unresolved; "
            "no output written. Use source-projection mode only for inspection, not a faithful AI replacement."
        )


'''
text = replace_once(text, 'def main() -> int:\n', helper + 'def main() -> int:\n')
text = replace_once(text, '    args = parser.parse_args()\n', '    parser.add_argument("--require-complete-matchers", action="store_true",\n                        help="refuse output while any compiled matcher test is unresolved; does not certify gameplay equivalence")\n    args = parser.parse_args()\n')
text = replace_once(text, '    program, manifest = render_recovered_program(source, ir)\n', '    program, manifest = render_recovered_program(source, ir)\n    if args.require_complete_matchers:\n        try:\n            require_complete_matchers(manifest)\n        except ValueError as exc:\n            parser.error(str(exc))\n')
changes[generator_path] = text

for path, contents in changes.items():
    if path.suffix == '.py':
        compile(contents, str(path), 'exec')
for path, contents in changes.items():
    path.write_text(contents)
    print('PATCHED', path)

assembly = Path('clash95.asm').read_text(errors='replace')
for first, last in (('loc_459104:', 'loc_459206:'), ('loc_459517:', 'sub_4592E0      endp')):
    begin = assembly.index(first)
    finish = assembly.index(last, begin)
    print('ASSEMBLY EVIDENCE\n' + assembly[begin:finish])
