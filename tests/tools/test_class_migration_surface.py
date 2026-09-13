#!/usr/bin/env python3
"""Class migration surface gates reject behavior-independent ABI/storage drift."""

from __future__ import annotations

import copy
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import check_class_migration_surface as surface


def snapshot():
    return {"schema_version": 1, "compiler": "gcc", "legacy_identities": [{"name": "legacy", "linkage": "external", "original_address": "0x401000"}],
            "linked_text": [{"name": "legacy", "class": "T", "count": 1}],
            "archive_text": [{"name": "legacy", "class": "T", "count": 1}],
            "linked_data_ordered": [{"name": "state", "class": "D", "size": 4}],
            "archive_storage": [{"name": "state", "sha256": "frozen", "relocations": []}],
            "archive_initializers": [], "linked_initializers": [{"name": ".init_array", "entries": [["frame_dummy"]]}]}


class DeltaTests(unittest.TestCase):
    def test_unchanged_snapshot_passes(self):
        self.assertTrue(surface.compare_snapshots(snapshot(), snapshot())["ok"])

    def test_weak_method_requires_exact_enumeration(self):
        base, current = snapshot(), snapshot()
        row = {"name": "_ZN7clash954View3getEv", "class": "W", "count": 1}
        for field in ("archive_text", "linked_text"):
            current[field].append(row)
        self.assertFalse(surface.compare_snapshots(base, current)["ok"])
        allowed_row = dict(row, kind="accessor", reason="Reviewed view accessor")
        allowed = {"archive_text": [allowed_row], "linked_text": [allowed_row]}
        self.assertTrue(surface.compare_snapshots(base, current, allowed)["ok"])
        current["archive_text"][-1] = dict(row, count=2)
        self.assertFalse(surface.compare_snapshots(base, current, allowed)["ok"])

    def test_stale_allowance_fails(self):
        row = {"name": "unused", "class": "T", "count": 1, "kind": "method", "reason": "unused review"}
        self.assertFalse(surface.compare_snapshots(snapshot(), snapshot(), {"archive_text": [row]})["ok"])

    def test_removed_or_linkage_flipped_text_fails(self):
        for field in ("archive_text", "linked_text"):
            current = snapshot()
            current[field][0]["class"] = "t"
            self.assertFalse(surface.compare_snapshots(snapshot(), current)["ok"])

    def test_duplicate_local_multiplicity_is_pinned(self):
        base, current = snapshot(), snapshot()
        for document in (base, current):
            document["linked_text"].append({"name": "local", "class": "t", "count": 2})
        current["linked_text"][-1]["count"] = 1
        self.assertFalse(surface.compare_snapshots(base, current)["ok"])

    def test_legacy_identity_and_all_storage_components_are_pinned(self):
        for field in ("legacy_identities", "linked_data_ordered", "archive_storage", "archive_initializers", "linked_initializers"):
            with self.subTest(field=field):
                current = snapshot()
                current[field].append({"unexpected": True})
                self.assertFalse(surface.compare_snapshots(snapshot(), current)["ok"])

    def test_data_reordering_fails_even_with_identical_members(self):
        base = snapshot()
        base["linked_data_ordered"].append({"name": "other", "class": "D", "size": 4})
        current = copy.deepcopy(base)
        current["linked_data_ordered"].reverse()
        report = surface.compare_snapshots(base, current)
        self.assertFalse(report["ok"])
        self.assertTrue(report["differences"]["linked_data_ordered"]["order_changed"])

    def test_no_wildcard_or_data_allowances(self):
        with self.assertRaises(surface.SurfaceError):
            surface.compare_snapshots(snapshot(), snapshot(), {"archive_storage": []})
        with self.assertRaises(surface.SurfaceError):
            surface.allowed_text({"linked_text": [{"name": "_ZN*", "class": "T", "count": 1, "kind": "method", "reason": "blanket"}]}, "linked_text")

    def test_allowance_counts_and_duplicate_rows_rejected(self):
        row = {"name": "method", "class": "T", "count": 1}
        with self.assertRaises(surface.SurfaceError):
            surface.as_counter([row, row])
        for count in (0, -1, True, "1"):
            with self.assertRaises(surface.SurfaceError):
                surface.as_counter([dict(row, count=count)])

    def test_profiles_cannot_be_cross_compared(self):
        current = snapshot()
        current["compiler"] = "clang"
        with self.assertRaises(surface.SurfaceError):
            surface.compare_snapshots(snapshot(), current)

    def test_archive_requires_one_exact_strong_legacy_definition(self):
        identities = snapshot()["legacy_identities"]
        self.assertEqual(surface.archive_identity_errors(identities, [(0, 1, "T", "legacy")]), [])
        for rows in ([], [(0, 1, "W", "legacy")], [(0, 1, "t", "legacy")],
                     [(0, 1, "T", "legacy"), (1, 1, "t", "legacy")]):
            self.assertTrue(surface.archive_identity_errors(identities, rows))

    def test_manifest_requires_exact_count_and_unique_names(self):
        identity = snapshot()["legacy_identities"][0]
        self.assertEqual(surface.manifest_identities({"functions": [identity]}, 1), [identity])
        with self.assertRaises(surface.SurfaceError):
            surface.manifest_identities({"functions": [identity]})
        with self.assertRaises(surface.SurfaceError):
            surface.manifest_identities({"functions": [identity, identity]}, 2)

    def test_nm_weak_symbols_are_not_ignored(self):
        rows = list(surface.parse_nm("00000000 00000004 W accessor\n00000010 00000004 w weak_local\n"))
        self.assertEqual({row["class"] for row in surface.text_counts(rows)}, {"w", "W"})

    def test_snapshot_refuses_overwrite(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "frozen.json"
            path.write_text("original\n")
            args = ["gate", "snapshot", "binary", "--lib", "archive", "--compiler", "gcc", "--snapshot", str(path)]
            with mock.patch.object(sys, "argv", args), mock.patch.object(surface, "make_snapshot", return_value=snapshot()):
                self.assertEqual(surface.main(), 2)
            self.assertEqual(path.read_text(), "original\n")


@unittest.skipUnless(shutil.which("g++-13") and shutil.which("ar"), "GCC 13/binutils fixture requires Linux build dependencies")
class ObjectStorageTests(unittest.TestCase):
    def compile(self, directory: Path, name: str, source: str) -> Path:
        source_path = directory / (name + ".cpp")
        object_path = directory / (name + ".o")
        source_path.write_text(source)
        subprocess.run(["g++-13", "-std=gnu++20", "-fno-pie", "-ffunction-sections", "-fdata-sections", "-c", str(source_path), "-o", str(object_path)], check=True, capture_output=True)
        return object_path

    def test_object_data_initializers_and_callback_relocations(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            first = self.compile(directory, "first", 'extern "C" void legacy();\nint state = 7; void (*callback)() = legacy;\n')
            second = self.compile(directory, "renamed", 'extern "C" void legacy();\nint state = 7; void (*callback)() = legacy;\n')
            changed = self.compile(directory, "changed", 'extern "C" void other();\nint state = 8; void (*callback)() = other;\n')
            before = surface.Elf64(first.read_bytes()).named_storage()
            self.assertEqual(before, surface.Elf64(second.read_bytes()).named_storage())
            self.assertNotEqual(before, surface.Elf64(changed.read_bytes()).named_storage())
            callback = next(row for row in before if row["name"] == "callback")
            self.assertEqual(callback["relocations"][0]["target"], "legacy")
            self.assertEqual(callback["relocations"][0]["width"], 8)

    def test_cpp_dynamic_initialization_is_detected(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            plain = self.compile(directory, "plain", "int state = 7;\n")
            dynamic = self.compile(directory, "dynamic", "extern int init(); int state = init();\n")
            self.assertEqual(surface.Elf64(plain.read_bytes()).initializers(), [])
            rows = surface.Elf64(dynamic.read_bytes()).initializers()
            self.assertEqual(rows[0]["name"], ".init_array")
            self.assertTrue(rows[0]["relocations"])

    def test_object_filename_move_does_not_change_storage_identity(self):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            for name in ("AddressBacked", "ClassNamed"):
                obj = self.compile(directory, name, "int preserved_state[2] = {1, 2};\n")
                subprocess.run(["ar", "rcs", str(directory / (name + ".a")), str(obj)], check=True)
            self.assertEqual(surface.archive_storage(directory / "AddressBacked.a"),
                             surface.archive_storage(directory / "ClassNamed.a"))

    def test_non_elf_cannot_silently_pass(self):
        with self.assertRaises(surface.SurfaceError):
            surface.Elf64(b"not an ELF file")


if __name__ == "__main__":
    unittest.main()
