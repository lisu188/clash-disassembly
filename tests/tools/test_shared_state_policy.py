#!/usr/bin/env python3
"""Consumer shared-state include and surface-policy regressions.

Run from the repository root in Linux/WSL:
  python3 -m unittest discover -s tests/tools -p 'test_shared_state_policy.py'

Fixtures need no compiler, game assets, or generated repository changes.
"""

from __future__ import annotations

import contextlib
import importlib.util
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest import mock


REPO = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location(
    "audit_header_surface", REPO / "tools" / "audit_header_surface.py")
assert SPEC is not None and SPEC.loader is not None
AUDIT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(AUDIT)


class SharedStatePolicyTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.repo = Path(self.temp.name)
        self.units = "src/units/units.c"
        self.units_second = "src/units/second.c"
        self.units_empty = "src/units/empty.c"
        self.world = "src/world/world.c"
        self.state = "src/state/definitions.c"
        self.sources = [self.units, self.units_second, self.units_empty,
                        self.world, self.state]
        manifest = {
            "functions": [
                {"source": rel, "subsystem": rel.split("/")[1],
                 "name": f"Fixture_{index}"}
                for index, rel in enumerate(self.sources)
            ],
            "state_owner": self.state,
        }
        data = self.repo / "data"
        data.mkdir()
        (data / "recovered_sources.json").write_text(
            json.dumps(manifest), encoding="utf-8")
        self.surface_path = data / "subsystem_api.json"
        self.decls_path = data / "recovered_decls.json"
        self.decls_path.write_text(
            json.dumps({"shared_state_layout": "consumer"}), encoding="utf-8")
        self.baseline_path = data / "header_surface_baseline.json"
        self.surface = {
            "subsystems": {sub: {"api_functions": []}
                           for sub in ("units", "world", "state")},
            "shared_globals": ["Alpha", "Beta"],
            "peer_edges": {},
            "shared_state_consumers": {
                "units": ["Alpha", "Beta"], "world": ["Alpha", "Beta"],
            },
            "tu_shared_state_visibility": {
                self.units: {"referenced": ["Alpha"],
                             "visible": ["Alpha", "Beta"]},
                self.units_second: {"referenced": ["Beta"],
                                    "visible": ["Alpha", "Beta"]},
                self.units_empty: {"referenced": [], "visible": []},
                self.world: {"referenced": ["Alpha", "Beta"],
                             "visible": ["Alpha", "Beta"]},
            },
        }
        for rel in self.sources:
            self.write_source(rel)
        self.write_surface()
        patch = mock.patch.multiple(
            AUDIT, REPO=self.repo, SURFACE=self.surface_path, DECLS=self.decls_path,
            BASELINE=self.baseline_path)
        patch.start()
        self.addCleanup(patch.stop)

    def write_source(self, rel, includes=(), outside=()):
        path = self.repo / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        lines = [AUDIT.MARK_BEGIN + " */"]
        lines += [f'#include "{header}"' for header in includes]
        lines += [AUDIT.MARK_END]
        lines += [f'#include "{header}"' for header in outside]
        path.write_text("\n".join(lines) + "\n", encoding="latin-1")

    def write_surface(self):
        self.surface_path.write_text(json.dumps(self.surface), encoding="utf-8")

    def surface_errors(self):
        self.write_surface()
        return AUDIT.shared_state_surface_errors()

    def assert_surface_error(self, text):
        self.assertTrue(any(text in error for error in self.surface_errors()), text)

    def test_own_consumer_slice_is_allowed_in_generated_block(self):
        for header in ("units_shared_state.h", "units/units_shared_state.h",
                       "src/units/units_shared_state.h",
                       "../units/./units_shared_state.h"):
            with self.subTest(header=header):
                self.write_source(self.units, includes=[header])
                self.assertEqual(AUDIT.include_policy_errors(), [])

    def test_aggregate_layout_preserves_existing_contract_until_cutover(self):
        for decls in ({}, {"shared_state_layout": "aggregate"}):
            with self.subTest(decls=decls):
                self.decls_path.write_text(json.dumps(decls), encoding="utf-8")
                self.write_source(self.units, includes=["../state/state_shared.h"])
                self.surface.pop("shared_state_consumers", None)
                self.surface.pop("tu_shared_state_visibility", None)
                self.assertEqual(AUDIT.include_policy_errors(), [])
                self.assertEqual(self.surface_errors(), [])

    def test_aggregate_layout_still_rejects_foreign_private_headers(self):
        self.decls_path.write_text("{}", encoding="utf-8")
        self.write_source(self.units, includes=["../world/world_state.h"])
        self.assertTrue(any("foreign state header" in error
                            for error in AUDIT.include_policy_errors()))

    def test_foreign_consumer_slice_is_rejected_for_all_path_spellings(self):
        for header in ("world_shared_state.h", "world/world_shared_state.h",
                       "src/world/world_shared_state.h",
                       "../world/world_shared_state.h",
                       "../../src/world/./world_shared_state.h",
                       r"..\world\world_shared_state.h"):
            with self.subTest(header=header):
                self.write_source(self.units, includes=[header])
                self.assertTrue(any("foreign shared_state header" in error
                                    for error in AUDIT.include_policy_errors()))

    def test_consumer_slice_must_be_inside_generated_block(self):
        self.write_source(self.units, outside=["units_shared_state.h"])
        self.assertTrue(any("outside generated block" in error
                            for error in AUDIT.include_policy_errors()))

    def test_angle_bracket_includes_follow_consumer_policy(self):
        self.write_source(self.units, includes=["../world/world_shared_state.h"])
        source = self.repo / self.units
        source.write_text(source.read_text(encoding="latin-1").replace(
            '"../world/world_shared_state.h"', '<../world/world_shared_state.h>'),
            encoding="latin-1")
        self.assertTrue(any("foreign shared_state header" in error
                            for error in AUDIT.include_policy_errors()))

    def test_aggregate_is_rejected_outside_state_group(self):
        for header in ("state_shared.h", "state/state_shared.h",
                       "src/state/state_shared.h", "../state/state_shared.h",
                       "../../src/state/./state_shared.h"):
            with self.subTest(header=header):
                self.write_source(self.units, includes=[header])
                self.assertTrue(any("aggregate outside state group" in error
                                    for error in AUDIT.include_policy_errors()))

    def test_state_definition_group_retains_aggregate_and_private_state_slices(self):
        self.write_source(self.state, includes=[
            "state_shared.h", "../units/units_state.h", "world/world_state.h"])
        self.assertEqual(AUDIT.include_policy_errors(), [])

    def test_state_group_cannot_include_consumer_or_foreign_internal_headers(self):
        for header in ("../units/units_shared_state.h", "units/units_internal.h"):
            with self.subTest(header=header):
                self.write_source(self.state, includes=[header])
                self.assertTrue(any("foreign" in error
                                    for error in AUDIT.include_policy_errors()))

    def test_foreign_private_header_policy_handles_root_and_bare_paths(self):
        for suffix in ("internal", "state"):
            for header in (f"world_{suffix}.h", f"src/world/world_{suffix}.h",
                           f"../world/./world_{suffix}.h"):
                with self.subTest(header=header):
                    self.write_source(self.units, includes=[header])
                    self.assertTrue(any(f"foreign {suffix} header" in error
                                        for error in AUDIT.include_policy_errors()))

    def test_tests_and_support_keep_the_existing_exemptions(self):
        self.write_source("tests/unit/fixture.c", outside=["recovered_all.h"])
        self.write_source("src/compatibility/support.c", outside=[
            "../state/state_shared.h", "../units/units_shared_state.h"])
        self.assertEqual(AUDIT.include_policy_errors(), [])

    def test_support_still_obeys_hard_bans(self):
        self.write_source("src/compatibility/support.c", outside=[
            "recovered_all.h", "recovered_internal.h"])
        errors = AUDIT.include_policy_errors()
        self.assertTrue(any("tests-only aggregate" in error for error in errors))
        self.assertTrue(any("deleted umbrella" in error for error in errors))

    def test_valid_visibility_keeps_references_distinct_from_exposure(self):
        self.assertEqual(self.surface_errors(), [])

    def test_subsystem_without_shared_references_has_an_empty_slice(self):
        self.surface["subsystems"]["core"] = {"api_functions": []}
        self.surface["shared_state_consumers"]["core"] = []
        self.assertEqual(self.surface_errors(), [])

    def test_both_visibility_fields_are_required(self):
        for field in ("shared_state_consumers", "tu_shared_state_visibility"):
            with self.subTest(field=field):
                value = self.surface.pop(field)
                self.assert_surface_error(f"{field}: required object")
                self.surface[field] = value

    def test_surface_maps_cover_exactly_the_non_state_consumers_and_sources(self):
        consumers = self.surface["shared_state_consumers"]
        consumers["state"] = []
        del consumers["world"]
        visibility = self.surface["tu_shared_state_visibility"]
        visibility[self.state] = {"referenced": [], "visible": []}
        del visibility[self.world]
        errors = self.surface_errors()
        for field in ("shared_state_consumers", "tu_shared_state_visibility"):
            self.assertTrue(any(f"{field}: missing entries" in e for e in errors))
            self.assertTrue(any(f"{field}: unexpected entries" in e for e in errors))

    def test_each_key_list_is_sorted_unique_and_shared(self):
        locations = [self.surface["shared_state_consumers"],
                     self.surface["tu_shared_state_visibility"][self.units]]
        for mapping, key in ((locations[0], "units"),
                             (locations[1], "referenced"),
                             (locations[1], "visible")):
            original = mapping[key]
            for value, message in ((["Beta", "Alpha"], "sorted and unique"),
                                   (["Alpha", "Alpha"], "sorted and unique"),
                                   (["Unknown"], "not shared globals"),
                                   (None, "sorted list"),
                                   ([3], "sorted list")):
                with self.subTest(key=key, value=value):
                    mapping[key] = value
                    self.assert_surface_error(message)
            mapping[key] = original

    def test_referenced_globals_must_be_visible(self):
        self.surface["tu_shared_state_visibility"][self.units]["visible"] = ["Beta"]
        self.assert_surface_error("referenced globals are not visible")

    def test_visibility_must_match_whole_consumer_slice(self):
        self.surface["tu_shared_state_visibility"][self.units]["visible"] = ["Alpha"]
        self.assert_surface_error("visible globals must equal the consumer slice")

    def test_unused_tu_exposes_no_shared_declarations(self):
        self.surface["tu_shared_state_visibility"][self.units_empty]["visible"] = ["Alpha"]
        self.assert_surface_error("otherwise be empty")

    def test_consumer_slice_matches_its_union_of_references(self):
        visibility = self.surface["tu_shared_state_visibility"]
        visibility[self.units_second]["referenced"] = ["Alpha"]
        self.assert_surface_error("slice differs from the union of TU references")

    def test_tu_record_requires_both_fields(self):
        del self.surface["tu_shared_state_visibility"][self.units]["referenced"]
        self.assert_surface_error("expected referenced and visible fields")

    def test_visibility_fields_do_not_change_legacy_ratchet_metrics(self):
        self.assertEqual(AUDIT.surface_metrics(), {
            "api_counts": {"units": 0, "world": 0, "state": 0},
            "shared_global_count": 2,
            "peer_edges": {},
        })

    def test_existing_ratchet_failures_remain_visible(self):
        self.surface["subsystems"]["units"]["api_functions"] = ["Function"]
        self.surface["peer_edges"] = {"units->world": 1}
        self.write_surface()
        self.baseline_path.write_text(json.dumps({
            "schema_version": 1,
            "api_counts": {"units": 0, "world": 0, "state": 0},
            "shared_global_count": 2, "peer_edges": {},
        }), encoding="utf-8")
        before = self.baseline_path.read_bytes()
        output = io.StringIO()
        with mock.patch.object(AUDIT, "run_gen", return_value=0), \
                mock.patch("sys.argv", ["audit_header_surface.py", "--mode", "check"]), \
                contextlib.redirect_stdout(output):
            self.assertEqual(AUDIT.main(), 1)
        self.assertIn("RATCHET: api surface of units grew 0 -> 1", output.getvalue())
        self.assertIn("RATCHET: peer edge units->world grew 0 -> 1", output.getvalue())
        self.assertEqual(self.baseline_path.read_bytes(), before)


if __name__ == "__main__":
    unittest.main()
