#!/usr/bin/env python3
"""Source identity and hash regressions for out-of-line recovered classes."""

from __future__ import annotations

import contextlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import global_inventory
import literal_common
import update_split_manifest_hashes as refresh
from recovered_implementation import (
    ImplementationError, definition_targets, implementation_name,
    index_manifest_definitions, manifest_sources, manifest_targets,
    resolve_source_definitions,
)
from split_source_index import body_sha256, scan_definitions


def method_record(source="src/world/WorldMap.cpp", adapter_source="src/world/legacy.cpp"):
    return {
        "name": "WorldMap_Refresh", "source": source,
        "body_sha256": "0" * 64, "legacy_body_sha256": "a" * 64,
        "implementation": {"kind": "method", "qualified_name": "clash95::WorldMap::WorldMap_Refresh"},
        "adapter": {"source": adapter_source, "body_sha256": "0" * 64},
    }


class QualifiedDefinitionTests(unittest.TestCase):
    def test_free_leaf_and_method_are_distinct_targets(self):
        text = ("int WorldMap_Refresh() { return 1; }\n"
                "int clash95::WorldMap::WorldMap_Refresh() { return 2; }\n")
        self.assertEqual([d.name for d in scan_definitions(text, {"WorldMap_Refresh"})],
                         ["WorldMap_Refresh"])
        method = "clash95::WorldMap::WorldMap_Refresh"
        definitions = scan_definitions(text, {method})
        self.assertEqual([d.name for d in definitions], [method])
        self.assertIn("return 2", text[definitions[0].opening_brace:definitions[0].end])

    def test_namespace_spellings_retain_exact_qualified_name(self):
        body = "int WorldMap::WorldMap_Refresh() const noexcept { return 7; }"
        for text in ("namespace clash95 {\n" + body + "\n}",
                     "namespace outer { namespace clash95 {\n" + body + "\n}}",
                     "namespace outer::clash95 {\n" + body + "\n}"):
            with self.subTest(text=text):
                name = ("outer::" if "outer" in text else "") + "clash95::WorldMap::WorldMap_Refresh"
                found = scan_definitions(text, {name})
                self.assertEqual([d.name for d in found], [name])
                self.assertEqual(found[0].line, 2)

    def test_namespace_method_hash_matches_free_body(self):
        old = "int WorldMap_Refresh() { return 3; }"
        new = "namespace clash95 { int WorldMap::WorldMap_Refresh() noexcept { return 3; } }"
        before = scan_definitions(old, {"WorldMap_Refresh"})[0]
        after = scan_definitions(new, {"clash95::WorldMap::WorldMap_Refresh"})[0]
        self.assertEqual(body_sha256(old, before), body_sha256(new, after))

    def test_prototypes_with_qualifiers_do_not_capture_later_bodies(self):
        text = ("int clash95::WorldMap::WorldMap_Refresh() const noexcept;\n"
                "int WorldMap_Refresh() __attribute__((used));\n"
                "int other() { return 1; }\n"
                "int WorldMap_Refresh() { return 2; }\n"
                "int clash95::WorldMap::WorldMap_Refresh() const noexcept { return 3; }\n")
        definitions = scan_definitions(text, {"WorldMap_Refresh", "clash95::WorldMap::WorldMap_Refresh"})
        self.assertEqual([d.line for d in definitions], [4, 5])

    def test_nested_noexcept_expression_and_returned_callback(self):
        text = ("int clash95::WorldMap::WorldMap_Refresh() noexcept(noexcept(other())) { return 3; }\n"
                "void (*callback(void))(int) { return 0; }\n")
        definitions = scan_definitions(text, {"clash95::WorldMap::WorldMap_Refresh", "callback"})
        self.assertEqual([d.line for d in definitions], [1, 2])

    def test_knr_definition_still_resolves(self):
        text = "int old(a, b)\nint a;\nchar *b;\n{ return a + *b; }\n"
        self.assertEqual([d.name for d in scan_definitions(text, {"old"})], ["old"])

    def test_inline_class_body_and_method_calls_are_not_definitions(self):
        text = ("namespace clash95 { class WorldMap {\n"
                "int WorldMap_Refresh() { return 1; }\n}; }\n"
                "int helper() { WorldMap_Refresh(); return 0; }\n")
        self.assertEqual(scan_definitions(text, {"WorldMap_Refresh", "clash95::WorldMap::WorldMap_Refresh"}), [])

    def test_unbalanced_namespace_fails(self):
        with self.assertRaisesRegex(ValueError, "unbalanced"):
            scan_definitions("namespace clash95 {", {"clash95::WorldMap::WorldMap_Refresh"})

    def test_inventory_names_namespace_methods_and_helpers(self):
        text = ("namespace clash95 {\nint WorldMap::WorldMap_Refresh() { return 1; }\n}\n"
                "static int helper() { return 2; }\n")
        self.assertEqual(global_inventory.find_defs(text.splitlines(keepends=True)),
                         [("clash95::WorldMap::WorldMap_Refresh", 1), ("helper", 3)])


class ImplementationMappingTests(unittest.TestCase):
    def test_schema2_free_records_keep_original_target(self):
        record = {"name": "Old", "source": "src/world/old.c"}
        self.assertEqual(implementation_name(record), "Old")
        targets = manifest_targets({"schema_version": 2, "functions": [record]})
        self.assertEqual([(t.identity, t.role, t.name) for t in targets], [("Old", "canonical", "Old")])

    def test_inventory_includes_adapter_only_and_state_sources(self):
        document = {"schema_version": 3, "functions": [method_record()],
                    "state_owner": "src/state/storage.cpp"}
        self.assertEqual(manifest_sources(document), ["src/state/storage.cpp", "src/world/WorldMap.cpp", "src/world/legacy.cpp"])

    def test_invalid_mappings_fail_closed(self):
        for mutate in (
            lambda r: r["implementation"].update(kind="unknown"),
            lambda r: r["implementation"].update(qualified_name="WorldMap_Refresh"),
            lambda r: r["implementation"].update(qualified_name="clash95::WorldMap::renamed"),
            lambda r: r["implementation"].update(kind="free"),
            lambda r: r.pop("adapter"),
            lambda r: r.update(source="../escape.cpp"),
            lambda r: r["adapter"].update(source="C:/escape.cpp"),
        ):
            record = method_record()
            mutate(record)
            with self.subTest(record=record), self.assertRaises(ImplementationError):
                definition_targets(record)

    def test_schema2_cannot_silently_enable_method_mapping(self):
        with self.assertRaisesRegex(ImplementationError, "schema 3"):
            manifest_targets({"schema_version": 2, "functions": [method_record()]})

    def test_duplicate_identities_and_overloads_fail(self):
        record = method_record()
        with self.assertRaisesRegex(ImplementationError, "duplicate recovered identity"):
            manifest_targets({"schema_version": 3, "functions": [record, record]})
        text = ("int clash95::WorldMap::WorldMap_Refresh(int) { return 1; }\n"
                "int clash95::WorldMap::WorldMap_Refresh(double) { return 2; }\n")
        with self.assertRaisesRegex(ImplementationError, "found 2"):
            resolve_source_definitions(text, definition_targets(record), source=record["source"])

    def test_canonical_and_adapter_hashes_are_independent(self):
        record = method_record(source="src/world/both.cpp", adapter_source="src/world/both.cpp")
        text = ("int WorldMap_Refresh() { return binding().WorldMap_Refresh(); }\n"
                "int clash95::WorldMap::WorldMap_Refresh() { return 7; }\n")
        targets = definition_targets(record)
        resolved = resolve_source_definitions(text, targets, source=record["source"])
        changed = text.replace("return 7", "return 8")
        other = resolve_source_definitions(changed, targets, source=record["source"])
        self.assertEqual(body_sha256(text, resolved[(record["name"], "adapter")]),
                         body_sha256(changed, other[(record["name"], "adapter")]))
        self.assertNotEqual(body_sha256(text, resolved[(record["name"], "canonical")]),
                            body_sha256(changed, other[(record["name"], "canonical")]))


class HashRefreshTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        (self.root / "data").mkdir()
        (self.root / "src/world").mkdir(parents=True)
        self.record = method_record()
        self.document = {"schema_version": 3, "functions": [self.record], "address_marker_count": 0}
        (self.root / self.record["source"]).write_text(
            "int clash95::WorldMap::WorldMap_Refresh() { return 7; }\n")
        (self.root / self.record["adapter"]["source"]).write_text(
            "int WorldMap_Refresh() { return binding().WorldMap_Refresh(); }\n")
        self.path = self.root / "data/recovered_sources.json"
        self.path.write_text(json.dumps(self.document))

    def test_hash_tool_refreshes_both_roles_and_preserves_legacy_provenance(self):
        with mock.patch.object(refresh, "ROOT", self.root), \
                mock.patch.object(sys, "argv", ["refresh", "--manifest", str(self.path), "--update"]), \
                contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(refresh.main(), 0)
        document = json.loads(self.path.read_text())
        self.assertEqual(document["schema_version"], 3)
        self.assertEqual(document["functions"][0]["legacy_body_sha256"], "a" * 64)
        resolved = index_manifest_definitions(document, self.root)
        self.assertEqual(document["functions"][0]["body_sha256"], resolved[(self.record["name"], "canonical")].body_sha256)
        self.assertEqual(document["functions"][0]["adapter"]["body_sha256"], resolved[(self.record["name"], "adapter")].body_sha256)

    def test_literal_refresh_updates_only_touched_adapter(self):
        with mock.patch.object(literal_common, "REPO", str(self.root)), \
                mock.patch.object(literal_common, "load_source_manifest", return_value=self.document):
            self.assertEqual(literal_common.refresh_source_manifest_body_hashes(
                [self.record["adapter"]["source"]]), 1)
        record = json.loads(self.path.read_text())["functions"][0]
        self.assertEqual(record["body_sha256"], "0" * 64)
        self.assertNotEqual(record["adapter"]["body_sha256"], "0" * 64)
        self.assertEqual(record["legacy_body_sha256"], "a" * 64)

    def test_missing_definition_aborts_without_writing_hashes(self):
        (self.root / self.record["source"]).write_text("int unrelated() { return 1; }\n")
        before = self.path.read_bytes()
        with mock.patch.object(literal_common, "REPO", str(self.root)), \
                mock.patch.object(literal_common, "load_source_manifest", return_value=self.document), \
                self.assertRaises(ImplementationError):
            literal_common.refresh_source_manifest_body_hashes([self.record["source"]])
        self.assertEqual(self.path.read_bytes(), before)


if __name__ == "__main__":
    unittest.main()
