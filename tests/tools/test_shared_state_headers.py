#!/usr/bin/env python3
"""Shared-state declaration visibility and include-selection regressions.

Run from the repository root in Linux/WSL:
  python3 -m unittest discover -s tests/tools -p 'test_shared_state_headers.py'

Temporary fixtures mock the preprocessed usage scan and expanded declaration
names. The tests need neither retail assets nor a compiler.
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
    "gen_shared_state_headers", REPO / "tools" / "gen_subsystem_headers.py")
assert SPEC is not None and SPEC.loader is not None
GEN = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(GEN)


class SharedStateHeadersTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.repo = Path(self.temp.name)
        self.sources = {
            "core": "src/core/entry.c",
            "core_second": "src/core/second.c",
            "core_no_shared": "src/core/no_shared.c",
            "battle": "src/battle/entry.c",
            "units": "src/units/entry.c",
            "state": "src/state/storage.c",
        }
        functions = [
            ("Core_Entry", "core", "core"),
            ("Core_Second", "core", "core_second"),
            ("Core_NoShared", "core", "core_no_shared"),
            ("Battle_Entry", "battle", "battle"),
            ("Units_Entry", "units", "units"),
        ]
        self.manifest = {
            "functions": [
                {"name": name, "subsystem": sub,
                 "source": self.sources[source]}
                for name, sub, source in functions
            ],
            "state_owner": self.sources["state"],
        }
        self.decls = {
            "schema_version": 1,
            "shared_state_layout": "consumer",
            "functions": {
                name: {"class": "manifest", "home": sub,
                       "decl": f"void {name}(void);"}
                for name, sub, _ in functions
            },
            # Deliberately unordered; the suffixed DB key expands to a
            # different identifier in the usage scan.
            "globals": {
                "g_Zeta": {"decl": "extern int g_Zeta;"},
                "g_StateOnly": {"decl": "extern int g_StateOnly;"},
                "g_Metadata_100": {
                    "decl": "extern volatile unsigned char g_Metadata_100[8];"},
                "g_CoreOnly": {"decl": "extern int g_CoreOnly;"},
                "g_Alpha": {"decl": "extern int g_Alpha;"},
                "g_NeverRead": {"decl": "extern int g_NeverRead;"},
            },
        }
        bodies = {
            "core": "void Core_Entry(void) { g_Alpha = g_Metadata[0]; }\n",
            "core_second": "void Core_Second(void) { g_Zeta = 1; }\n",
            "core_no_shared": "void Core_NoShared(void) { g_CoreOnly = 2; }\n",
            "battle": "void Battle_Entry(void) { Core_Entry(); g_Alpha = 3; }\n",
            "units": "void Units_Entry(void) { g_Zeta = g_Metadata[0]; }\n",
            "state": "int g_Alpha, g_Zeta, g_CoreOnly, g_StateOnly;\n"
                     "volatile unsigned char g_Metadata_100[8];\n",
        }
        self.original_bodies = {}
        for key, rel in self.sources.items():
            path = self.repo / rel
            path.parent.mkdir(parents=True, exist_ok=True)
            self.original_bodies[rel] = "\n\n/* fixture body */\n" + bodies[key]
            block = "\n".join([
                GEN.MARK_BEGIN, '#include "../recovered_internal.h"',
                GEN.MARK_END])
            path.write_text(block + self.original_bodies[rel],
                            encoding="latin-1", newline="")
        self.tokens = {
            self.sources["core"]: {"Core_Entry", "g_Alpha", "g_Metadata"},
            self.sources["core_second"]: {"Core_Second", "g_Zeta"},
            self.sources["core_no_shared"]: {"Core_NoShared", "g_CoreOnly"},
            self.sources["battle"]: {"Battle_Entry", "Core_Entry", "g_Alpha"},
            self.sources["units"]: {"Units_Entry", "g_Zeta", "g_Metadata"},
            self.sources["state"]: {
                "g_Alpha", "g_Zeta", "g_Metadata", "g_CoreOnly", "g_StateOnly"},
        }
        self.expanded = {
            ("fn", name): name for name in self.decls["functions"]
        }
        self.expanded.update({
            ("gl", name): "g_Metadata" if name == "g_Metadata_100" else name
            for name in self.decls["globals"]
        })
        self.decls_path = self.repo / "data/recovered_decls.json"
        self.manifest_path = self.repo / "data/recovered_sources.json"
        self.surface_path = self.repo / "data/subsystem_api.json"
        self.decls_path.parent.mkdir(parents=True)
        patcher = mock.patch.multiple(
            GEN, REPO=self.repo, DECLS=self.decls_path,
            MANIFEST=self.manifest_path, SURFACE_OUT=self.surface_path)
        patcher.start()
        self.addCleanup(patcher.stop)
        self.write_metadata()

    def write_metadata(self):
        self.decls_path.write_text(json.dumps(self.decls), encoding="utf-8")
        self.manifest_path.write_text(
            json.dumps(self.manifest), encoding="utf-8")

    def generate(self, *args):
        with mock.patch.object(GEN, "scan_usage", return_value=self.tokens), \
                mock.patch.object(GEN, "expanded_names",
                                  return_value=self.expanded), \
                mock.patch("sys.argv", ["gen_subsystem_headers.py", *args]), \
                contextlib.redirect_stdout(io.StringIO()):
            return GEN.main()

    def write_all(self):
        self.assertEqual(self.generate("--write"), 0)
        for sub in ("core", "battle", "units", "state"):
            self.assertEqual(self.generate("--write-tu-includes", sub), 0)

    def read(self, rel):
        return (self.repo / rel).read_text(encoding="latin-1")

    def surface(self):
        return json.loads(self.surface_path.read_text(encoding="utf-8"))

    def generated_snapshot(self):
        paths = sorted((self.repo / "src").rglob("*"))
        paths.append(self.surface_path)
        return {str(path.relative_to(self.repo)): path.read_bytes()
                for path in paths if path.is_file()}

    def test_consumer_headers_isolate_subsets_and_preserve_declarations(self):
        self.assertEqual(self.generate("--write"), 0)
        expected = {
            "core": ["g_Alpha", "g_Metadata_100", "g_Zeta"],
            "battle": ["g_Alpha"],
            "units": ["g_Metadata_100", "g_Zeta"],
        }
        for sub in GEN.SUBSYSTEMS:
            if sub == "state":
                continue
            header = self.read(f"src/{sub}/{sub}_shared_state.h")
            with self.subTest(subsystem=sub):
                declarations = [line for line in header.splitlines()
                                if line.startswith("extern ")]
                self.assertEqual(declarations, [self.decls["globals"][name]["decl"]
                                               for name in expected.get(sub, [])])
                self.assertNotIn("state_shared.h", header)

    def test_surface_separates_references_from_visible_consumer_slice(self):
        self.assertEqual(self.generate("--write"), 0)
        surface = self.surface()
        shared = ["g_Alpha", "g_Metadata_100", "g_Zeta"]
        consumers = {sub: [] for sub in GEN.SUBSYSTEMS if sub != "state"}
        consumers.update({"core": shared, "battle": ["g_Alpha"],
                          "units": ["g_Metadata_100", "g_Zeta"]})
        self.assertEqual(surface["shared_state_consumers"], consumers)
        self.assertEqual(surface["tu_shared_state_visibility"], {
            self.sources["core"]: {
                "referenced": ["g_Alpha", "g_Metadata_100"], "visible": shared},
            self.sources["core_second"]: {
                "referenced": ["g_Zeta"], "visible": shared},
            self.sources["core_no_shared"]: {"referenced": [], "visible": []},
            self.sources["battle"]: {
                "referenced": ["g_Alpha"], "visible": ["g_Alpha"]},
            self.sources["units"]: {
                "referenced": ["g_Metadata_100", "g_Zeta"],
                "visible": ["g_Metadata_100", "g_Zeta"]},
        })
        self.assertEqual(surface["shared_globals"], shared)
        self.assertEqual(surface["peer_edges"], {"battle->core": 1})
        self.assertEqual(surface["legacy_import_count"], 0)
        self.assertEqual(surface["state_local_global_count"], 2)
        self.assertEqual(surface["subsystems"]["core"], {
            "api_functions": ["Core_Entry"],
            "internal_function_count": 2, "state_globals": 1})
        self.assertEqual(surface["subsystems"]["battle"], {
            "api_functions": [], "internal_function_count": 1,
            "state_globals": 0})

    def test_tus_include_own_shared_slice_only_when_used(self):
        self.write_all()
        for key, rel in self.sources.items():
            if key == "state":
                continue
            text = self.read(rel)
            sub = rel.split("/")[1]
            with self.subTest(source=rel):
                self.assertNotIn("state/state_shared.h", text)
                own_include = f'#include "{sub}_shared_state.h"'
                if key == "core_no_shared":
                    self.assertNotIn("_shared_state.h", text)
                else:
                    self.assertEqual(text.count(own_include), 1)
                self.assertTrue(text.endswith(self.original_bodies[rel]))
        self.assertEqual(self.generate("--check-tu-includes"), 0)

    def test_state_and_test_aggregate_retain_complete_shared_declarations(self):
        self.write_all()
        aggregate = self.read("src/state/state_shared.h")
        for name in ("g_Alpha", "g_Metadata_100", "g_Zeta"):
            self.assertEqual(aggregate.count(self.decls["globals"][name]["decl"]), 1)
        for name in ("g_CoreOnly", "g_StateOnly", "g_NeverRead"):
            self.assertNotIn(name, aggregate)
        state = self.read(self.sources["state"])
        self.assertIn('#include "state_shared.h"', state)
        self.assertIn('#include "state_local.h"', state)
        self.assertIn('#include "../core/core_state.h"', state)
        self.assertNotIn("state_shared_state.h", state)
        self.assertTrue(state.endswith(self.original_bodies[self.sources["state"]]))
        self.assertIn('#include "state/state_shared.h"',
                      self.read("src/recovered_all.h"))
        self.assertFalse((self.repo / "src/state/state_shared_state.h").exists())

    def test_generation_is_stable_under_metadata_and_scan_reordering(self):
        self.write_all()
        before = self.generated_snapshot()
        self.decls["functions"] = dict(reversed(list(self.decls["functions"].items())))
        self.decls["globals"] = dict(reversed(list(self.decls["globals"].items())))
        self.tokens = dict(reversed(list(self.tokens.items())))
        self.expanded = dict(reversed(list(self.expanded.items())))
        self.write_metadata()
        self.assertEqual(self.generate("--check"), 0)
        self.assertEqual(self.generate("--check-tu-includes"), 0)
        self.write_all()
        self.assertEqual(self.generated_snapshot(), before)

    def test_freshness_checks_detect_and_repair_broadened_header_and_include(self):
        self.write_all()
        before = self.generated_snapshot()
        header = self.repo / "src/battle/battle_shared_state.h"
        header.write_text(header.read_text(encoding="latin-1") +
                          "extern int g_Zeta;\n", encoding="latin-1")
        self.assertEqual(self.generate("--check"), 1)
        self.assertEqual(self.generate("--write"), 0)
        self.assertEqual(self.generate("--check"), 0)
        source = self.repo / self.sources["battle"]
        source.write_text(source.read_text(encoding="latin-1").replace(
            '#include "battle_shared_state.h"',
            '#include "../state/state_shared.h"'), encoding="latin-1")
        self.assertEqual(self.generate("--check-tu-includes"), 1)
        self.assertEqual(self.generate("--write-tu-includes", "battle"), 0)
        self.assertEqual(self.generate("--check-tu-includes"), 0)
        self.assertEqual(self.generated_snapshot(), before)

    def test_default_and_explicit_aggregate_layout_preserve_legacy_output(self):
        del self.decls["shared_state_layout"]
        self.write_metadata()
        self.write_all()
        before = self.generated_snapshot()
        surface = self.surface()
        self.assertEqual(set(surface), {
            "schema_version", "subsystems", "shared_globals",
            "state_local_global_count", "legacy_import_count", "peer_edges"})
        self.assertEqual(list((self.repo / "src").rglob("*_shared_state.h")), [])
        for key, rel in self.sources.items():
            if key == "state":
                continue
            text = self.read(rel)
            with self.subTest(source=rel):
                if key == "core_no_shared":
                    self.assertNotIn("state_shared.h", text)
                else:
                    self.assertIn('#include "../state/state_shared.h"', text)
                self.assertNotIn("_shared_state.h", text)
        self.decls["shared_state_layout"] = "aggregate"
        self.write_metadata()
        self.assertEqual(self.generate("--check"), 0)
        self.assertEqual(self.generate("--check-tu-includes"), 0)
        self.write_all()
        self.assertEqual(self.generated_snapshot(), before)

    def test_invalid_shared_state_layout_is_rejected(self):
        self.decls["shared_state_layout"] = "consumers"
        self.write_metadata()
        with contextlib.redirect_stdout(io.StringIO()):
            with self.assertRaises(SystemExit):
                GEN.load()

    def test_combined_write_generates_headers_and_includes_from_one_scan(self):
        with mock.patch.object(GEN, "scan_usage", return_value=self.tokens) as scan, \
                mock.patch.object(GEN, "expanded_names",
                                  return_value=self.expanded) as expanded, \
                mock.patch("sys.argv", ["gen_subsystem_headers.py", "--write",
                                        "--write-tu-includes", "all"]), \
                contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(GEN.main(), 0)
        scan.assert_called_once_with(self.manifest)
        expanded.assert_called_once_with(
            self.decls["functions"], self.decls["globals"])
        self.assertEqual(self.generate("--check"), 0)
        self.assertEqual(self.generate("--check-tu-includes"), 0)
        for rel in self.sources.values():
            self.assertTrue(self.read(rel).endswith(self.original_bodies[rel]))

    def test_all_tu_write_rejects_invalid_block_before_modifying_files(self):
        invalid = self.repo / self.sources["units"]
        invalid.write_bytes(b"/* missing generated include block */\n")
        before = {rel: (self.repo / rel).read_bytes()
                  for rel in self.sources.values()}
        self.assertEqual(self.generate("--write", "--write-tu-includes", "all"), 1)
        self.assertEqual({rel: (self.repo / rel).read_bytes()
                          for rel in self.sources.values()}, before)
        self.assertFalse(self.surface_path.exists())


class IncludeBlockPreservationTest(unittest.TestCase):
    def test_replacement_preserves_lf_and_crlf_surrounding_bytes(self):
        replacement_lines = [
            GEN.MARK_BEGIN, '#include "core_shared_state.h"', GEN.MARK_END]
        for newline in ("\n", "\r\n"):
            with self.subTest(newline=repr(newline)):
                old = newline.join([
                    GEN.MARK_BEGIN, '#include "../state/state_shared.h"',
                    GEN.MARK_END])
                # Mixed endings and non-ASCII bytes outside the block must
                # survive without universal-newline or encoding conversion.
                prefix = "/* \xff prefix */\r\n\n"
                suffix = "\n/* \xe9 body */\r\nint keep_me;\n"
                text = prefix + old + suffix
                result = GEN.replace_tu_include_block(
                    text, "\n".join(replacement_lines))
                self.assertEqual(result.encode("latin-1"),
                                 (prefix + newline.join(replacement_lines) +
                                  suffix).encode("latin-1"))

    def test_missing_and_duplicate_blocks_are_rejected(self):
        block = "\n".join([GEN.MARK_BEGIN, GEN.MARK_END])
        for text in ("/* no block */\n", GEN.MARK_BEGIN, block + "\n" + block,
                     GEN.MARK_BEGIN + "\nint keep_me;\n" + block,
                     block + "\nint keep_me;\n" + GEN.MARK_END,
                     GEN.MARK_END + "\n" + GEN.MARK_BEGIN):
            with self.subTest(source=text):
                with self.assertRaises(ValueError):
                    GEN.replace_tu_include_block(text, block)


if __name__ == "__main__":
    unittest.main()
