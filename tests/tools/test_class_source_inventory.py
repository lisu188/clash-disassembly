"""Recovered link order is explicit, including historical nonlexical areas."""
import contextlib
import copy
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from class_source_inventory import (
    SourceInventoryError, main, parse_cmake_inventory,
    resolve_source_inventory, synchronize_source_inventory,
)


MEDIA_FIRST = "src/media/004811C0_004814A0_media_017.cpp"
MEDIA_LAST = "src/media/00472B00_00472B00_media_001.cpp"
STATE_FIRST = "src/state/00000000_0054FFFF_recovered_state.cpp"
STATE_LAST = "src/state/00000000_00000000_prelude_helpers.cpp"
UNIT_OLD = "src/units/0040F510_00411560_units_001.cpp"
UNIT_NEW = "src/units/UnitStack.cpp"
PATH_NEW = "src/units/QueuedPath.cpp"


def cmake(groups):
    text = "# Preserve recovered translation-unit link order.\n\n"
    for group, sources in groups:
        text += f"set(CLASH95_SPLIT_{group.upper()}_SOURCES\n"
        text += "".join("  ${CMAKE_CURRENT_SOURCE_DIR}/" + source + "\n" for source in sources)
        text += ")\n\n"
    return text


def fixture():
    groups = [("media", [MEDIA_FIRST, MEDIA_LAST]),
              ("state", [STATE_FIRST, STATE_LAST]), ("units", [UNIT_OLD])]
    sources = [source for _, entries in groups for source in entries]
    manifest = {"schema_version": 3, "state_owner": STATE_FIRST,
                "source_file_count": len(sources), "functions": [
                    {"name": "Free_" + str(index), "source": source}
                    for index, source in enumerate(sources) if source != STATE_FIRST]}
    return manifest, cmake(groups)


def add_method(manifest, source=UNIT_NEW, name="UnitStack_HasReadyUnits"):
    manifest["functions"].append({
        "name": name, "source": source,
        "implementation": {"kind": "method", "qualified_name": "clash95::UnitStack::" + name},
        "adapter": {"source": UNIT_OLD},
    })


class ClassSourceInventoryTests(unittest.TestCase):
    def test_initial_capture_preserves_historical_media_and_state_order(self):
        manifest, text = fixture()
        result, output = synchronize_source_inventory(manifest, text)
        self.assertEqual(output, text)
        self.assertEqual(result["source_inventory"], [
            {"group": "media", "sources": [MEDIA_FIRST, MEDIA_LAST]},
            {"group": "state", "sources": [STATE_FIRST, STATE_LAST]},
            {"group": "units", "sources": [UNIT_OLD]},
        ])
        self.assertNotIn("source_inventory", manifest)

    def test_checked_in_legacy_order_still_has_both_nonlexical_sequences(self):
        inventory = parse_cmake_inventory((ROOT / "src/sources.cmake").read_text())
        groups = {entry["group"]: entry["sources"] for entry in inventory}
        self.assertLess(groups["media"].index(MEDIA_FIRST), groups["media"].index(MEDIA_LAST))
        self.assertLess(groups["state"].index(STATE_FIRST), groups["state"].index(STATE_LAST))

    def test_unchanged_sync_preserves_crlf_comments_and_formatting(self):
        manifest, text = fixture()
        text = text.replace("  ${", "\t${").replace(")\n", ") # group remains in place\n").replace("\n", "\r\n")
        result, output = synchronize_source_inventory(manifest, text)
        self.assertEqual(output, text)
        again, output = synchronize_source_inventory(result, output)
        self.assertEqual(again, result)
        self.assertEqual(output, text)
        self.assertEqual(resolve_source_inventory(result, text), result["source_inventory"])

    def test_new_canonical_sources_append_in_manifest_encounter_order(self):
        manifest, text = fixture()
        manifest, text = synchronize_source_inventory(manifest, text)
        add_method(manifest)
        add_method(manifest, PATH_NEW, "QueuedPath_StartsAtTile")
        before = copy.deepcopy(manifest)
        result, output = synchronize_source_inventory(manifest, text)
        self.assertEqual(manifest, before)
        self.assertEqual(result["source_inventory"][-1]["sources"], [UNIT_OLD, UNIT_NEW, PATH_NEW])
        self.assertEqual(result["source_file_count"], 7)
        self.assertEqual(output.replace("  ${CMAKE_CURRENT_SOURCE_DIR}/" + UNIT_NEW + "\n", "").replace(
            "  ${CMAKE_CURRENT_SOURCE_DIR}/" + PATH_NEW + "\n", ""), text)
        self.assertEqual(resolve_source_inventory(result, output), result["source_inventory"])

    def test_existing_cmake_class_order_is_captured_without_resorting(self):
        manifest, text = fixture()
        add_method(manifest)
        add_method(manifest, PATH_NEW, "QueuedPath_StartsAtTile")
        text = text.replace("  ${CMAKE_CURRENT_SOURCE_DIR}/" + UNIT_OLD + "\n",
                            "".join("  ${CMAKE_CURRENT_SOURCE_DIR}/" + source + "\n"
                                    for source in [UNIT_OLD, PATH_NEW, UNIT_NEW]))
        result, output = synchronize_source_inventory(manifest, text)
        self.assertEqual(output, text)
        self.assertEqual(result["source_inventory"][-1]["sources"], [UNIT_OLD, PATH_NEW, UNIT_NEW])

    def test_strict_resolution_requires_explicit_complete_inventory(self):
        manifest, text = fixture()
        with self.assertRaisesRegex(SourceInventoryError, "source_inventory is missing"):
            resolve_source_inventory(manifest, text)
        manifest, text = synchronize_source_inventory(manifest, text)
        add_method(manifest)
        with self.assertRaisesRegex(SourceInventoryError, "missing source inventory"):
            resolve_source_inventory(manifest, text)

    def test_reordering_existing_sources_or_groups_is_rejected(self):
        manifest, text = fixture()
        manifest, _ = synchronize_source_inventory(manifest, text)
        for changed in [text.replace(MEDIA_FIRST, "PLACEHOLDER").replace(MEDIA_LAST, MEDIA_FIRST).replace("PLACEHOLDER", MEDIA_LAST),
                        cmake([("state", [STATE_FIRST, STATE_LAST]), ("media", [MEDIA_FIRST, MEDIA_LAST]), ("units", [UNIT_OLD])])]:
            with self.subTest(changed=changed), self.assertRaisesRegex(SourceInventoryError, "order"):
                synchronize_source_inventory(manifest, changed)

    def test_missing_adapter_state_or_free_source_cannot_be_reintroduced_at_end(self):
        manifest, text = fixture()
        add_method(manifest)
        for missing in [UNIT_OLD, STATE_FIRST, MEDIA_FIRST]:
            changed = text.replace("  ${CMAKE_CURRENT_SOURCE_DIR}/" + missing + "\n", "")
            # Keep the units block nonempty to isolate missing adapter handling.
            if missing == UNIT_OLD:
                changed = changed.replace("set(CLASH95_SPLIT_UNITS_SOURCES\n", "set(CLASH95_SPLIT_UNITS_SOURCES\n  ${CMAKE_CURRENT_SOURCE_DIR}/" + UNIT_NEW + "\n")
            with self.subTest(missing=missing), self.assertRaisesRegex(SourceInventoryError, "missing source inventory"):
                synchronize_source_inventory(manifest, changed)

    def test_duplicate_paths_groups_and_wrong_group_are_rejected(self):
        _, text = fixture()
        variants = [text.replace(MEDIA_LAST, MEDIA_FIRST),
                    text + "set(CLASH95_SPLIT_MEDIA_SOURCES\n  " + MEDIA_FIRST + "\n)\n",
                    text.replace(MEDIA_LAST, "src/units/Foreign.cpp")]
        for changed in variants:
            with self.subTest(changed=changed), self.assertRaises(SourceInventoryError):
                parse_cmake_inventory(changed)

    def test_foreign_paths_groups_and_executable_cmake_statements_are_rejected(self):
        manifest, text = fixture()
        variants = [text.replace(MEDIA_LAST, "src/media/Foreign.cpp"),
                    text.replace("SPLIT_MEDIA_SOURCES", "SPLIT_FOREIGN_SOURCES"),
                    text + "list(REVERSE CLASH95_SPLIT_MEDIA_SOURCES)\n",
                    text.replace(MEDIA_LAST, "src/media/../units/Foreign.cpp")]
        for changed in variants:
            with self.subTest(changed=changed), self.assertRaises(SourceInventoryError):
                synchronize_source_inventory(manifest, changed)

    def test_new_method_cannot_create_a_missing_subsystem_group(self):
        manifest, text = fixture()
        add_method(manifest, "src/world/WorldMap.cpp")
        with self.assertRaisesRegex(SourceInventoryError, "missing existing subsystem group world"):
            synchronize_source_inventory(manifest, text)

    def test_malformed_explicit_inventory_is_rejected(self):
        manifest, text = fixture()
        manifest, _ = synchronize_source_inventory(manifest, text)
        for inventory in [[], {}, manifest["source_inventory"] * 2,
                          [{"group": "media", "sources": []}],
                          [{"group": "media", "sources": [MEDIA_FIRST], "extra": True}]]:
            with self.subTest(inventory=inventory), self.assertRaises(SourceInventoryError):
                resolve_source_inventory({**manifest, "source_inventory": inventory}, text)

    def test_schema_two_is_not_silently_promoted(self):
        manifest, text = fixture()
        manifest["schema_version"] = 2
        with self.assertRaisesRegex(SourceInventoryError, "schema 3"):
            synchronize_source_inventory(manifest, text)

    def test_cli_is_read_only_by_default_and_write_is_idempotent(self):
        manifest, text = fixture()
        with tempfile.TemporaryDirectory(prefix="clash95-source-inventory-") as directory:
            root = Path(directory)
            (root / "data").mkdir()
            (root / "src").mkdir()
            manifest_path = root / "data/recovered_sources.json"
            cmake_path = root / "src/sources.cmake"
            manifest_path.write_bytes((json.dumps(manifest, indent=2) + "\r\n").encode())
            cmake_path.write_bytes(text.replace("\n", "\r\n").encode())
            before = manifest_path.read_bytes(), cmake_path.read_bytes()
            with contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(main(["--root", str(root)]), 1)
                self.assertEqual(before, (manifest_path.read_bytes(), cmake_path.read_bytes()))
                self.assertEqual(main(["--root", str(root), "--write"]), 0)
                after = manifest_path.read_bytes(), cmake_path.read_bytes()
                self.assertEqual(main(["--root", str(root)]), 0)
                self.assertEqual(main(["--root", str(root), "--write"]), 0)
                self.assertEqual(after, (manifest_path.read_bytes(), cmake_path.read_bytes()))
            self.assertEqual(cmake_path.read_bytes(), before[1])


if __name__ == "__main__":
    unittest.main()
