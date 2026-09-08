"""Borrowing glue cannot become an untracked replacement for recovered code."""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from class_binding_inventory import validate_binding_metadata, validate_binding_sources
from split_source_index import body_sha256, scan_definitions


OLD = "src/units/old.cpp"
CLASS = "src/units/Probe.cpp"
OTHER = "src/units/other.cpp"
STATE = "src/state/state.cpp"
QUALIFIED = "clash95::Probe::borrow"
FACTORY = """clash95::Probe clash95::Probe::borrow() noexcept
{
  return Probe(::counter, ::values);
}
"""
METHOD = "int clash95::Probe::Probe_Read() { return 1; }\n"
ADAPTER = "int Probe_Read() { return clash95::Probe::borrow().Probe_Read(); }\n"


def digest(text, name):
    definitions = scan_definitions(text, {name})
    if len(definitions) != 1:
        raise AssertionError(f"fixture expected one {name}, found {len(definitions)}")
    return body_sha256(text, definitions[0])


class BindingFixture(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="class-binding-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.registry = {
            "identities": [{"name": "Probe_Read", "classification": "game-method",
                            "class_owner": "Probe", "legacy_source": OLD}],
            "helpers": [],
            "class_bindings": [{"class_owner": "Probe", "qualified_name": QUALIFIED,
                                "source": OLD, "referenced_globals": ["counter", "values"],
                                "body_sha256": digest(FACTORY, QUALIFIED)}],
        }
        self.manifest = {
            "schema_version": 3, "state_owner": STATE,
            "functions": [
                {"name": "Probe_Read", "source": CLASS, "body_sha256": digest(METHOD, "clash95::Probe::Probe_Read"),
                 "implementation": {"kind": "method", "qualified_name": "clash95::Probe::Probe_Read"},
                 "adapter": {"source": OLD, "body_sha256": digest(ADAPTER, "Probe_Read")}},
                {"name": "Other_Read", "source": OTHER},
            ],
        }
        self.declarations = {
            "globals": {
                "counter": {"decl": "extern int counter;", "owner": "src/state/state.c"},
                "values": {"decl": "extern int values[3];", "owner": "src/state/state.c"},
            },
            "functions": {},
        }
        self.write(OLD, ADAPTER + FACTORY)
        self.write(CLASS, METHOD)
        self.write(OTHER, "int Other_Read() { return 0; }\n")
        self.write(STATE, "int counter; int values[3];\n")

    @property
    def binding(self):
        return self.registry["class_bindings"][0]

    def write(self, source, text):
        path = self.root / source
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def metadata(self):
        return validate_binding_metadata(self.registry, self.manifest, self.declarations)

    def sources(self):
        return validate_binding_sources(self.registry, self.manifest, self.declarations, self.root)

    def assert_error(self, errors, part):
        self.assertTrue(any(part in error for error in errors), errors)

    def factory(self, text, *, refresh_hash=True):
        self.write(self.binding["source"], ADAPTER + text)
        if refresh_hash:
            self.binding["body_sha256"] = digest(text, QUALIFIED)

    def helper(self, *, source=CLASS, name="Probe_Ensure"):
        self.registry["helpers"].append({"name": name, "classification": "game-method",
                                         "class_owner": "Probe", "method": name, "source": OLD})
        self.declarations["functions"][name] = {"class": "helper", "source": source}

    def test_valid_factory_metadata_and_full_surface_are_read_only(self):
        before = copy.deepcopy((self.registry, self.manifest, self.declarations))
        files = {path: path.read_bytes() for path in self.root.rglob("*.cpp")}
        self.assertEqual(self.metadata(), [])
        self.assertEqual(self.sources(), [])
        self.assertEqual((self.registry, self.manifest, self.declarations), before)
        self.assertEqual({path: path.read_bytes() for path in files}, files)

    def test_factory_remains_at_adapter_anchor_after_method_relocation(self):
        self.binding["source"] = CLASS
        self.assert_error(self.metadata(), "original adapter/storage anchor")
        self.binding["source"] = OTHER
        self.assert_error(self.metadata(), "original adapter/storage anchor")
        self.binding["source"] = OLD
        self.assertEqual(self.metadata(), [])

    def test_factory_can_borrow_from_canonical_storage_anchor(self):
        self.write(OLD, ADAPTER)
        self.binding["source"] = STATE
        self.write(STATE, "int counter; int values[3];\n" + FACTORY)
        self.assertEqual(self.sources(), [])
        self.declarations["globals"]["counter"]["owner"] = OTHER
        self.declarations["globals"]["values"]["owner"] = OTHER
        self.assert_error(self.metadata(), "original adapter/storage anchor")

    def test_stateless_factory_still_uses_own_original_adapter_anchor(self):
        self.binding["referenced_globals"] = []
        self.factory(FACTORY.replace("::counter, ::values", ""))
        self.assertEqual(self.sources(), [])
        self.binding["source"] = STATE
        self.assert_error(self.metadata(), "original adapter/storage anchor")

    def test_duplicate_registration_and_invented_original_fields_rejected(self):
        self.registry["class_bindings"].append(copy.deepcopy(self.binding))
        self.assert_error(self.metadata(), "duplicate class owner")
        self.assert_error(self.metadata(), "duplicate qualified factory name")
        self.registry["class_bindings"].pop()
        for key in ("original_address", "name", "original_source", "identity_kind"):
            with self.subTest(key=key):
                self.binding[key] = "invented"
                self.assert_error(self.metadata(), "address-free binding fields")
                del self.binding[key]

    def test_only_known_owner_and_exact_borrow_name_are_accepted(self):
        self.binding["class_owner"] = "Imagined"
        self.assert_error(self.metadata(), "unknown or invalid class owner")
        self.binding["class_owner"] = "Probe"
        self.binding["qualified_name"] = "clash95::Probe::Probe_Read"
        self.assert_error(self.metadata(), "qualified_name must be")
        self.assert_error(self.metadata(), "must not replace a recovered identity")

    def test_malformed_metadata_fails_without_exceptions(self):
        for value in (None, {}, "bindings"):
            with self.subTest(value=value):
                self.registry["class_bindings"] = value
                self.assert_error(self.metadata(), "must be a separate list")
        self.registry["class_bindings"] = [None]
        self.assert_error(self.metadata(), "must be an object")
        self.assertTrue(validate_binding_metadata([], self.manifest, self.declarations))

    def test_schema_and_hash_contract(self):
        self.manifest["schema_version"] = 2
        self.assert_error(self.metadata(), "require manifest schema 3")
        self.manifest["schema_version"] = 3
        for value in (None, "a" * 63, "A" * 64, 1):
            with self.subTest(value=value):
                self.binding["body_sha256"] = value
                self.assert_error(self.metadata(), "lowercase SHA-256")

    def test_globals_are_canonical_unique_and_in_exact_order(self):
        for names, error in [(["unknown"], "undeclared canonical global"),
                             (["counter", "counter"], "duplicate referenced global"),
                             (["values", "counter"], "required canonical name order"),
                             (["counter[0]"], "ordered array of canonical names"),
                             ("counter", "ordered array of canonical names")]:
            with self.subTest(names=names):
                self.binding["referenced_globals"] = names
                self.assert_error(self.metadata(), error)

    def test_reordered_constructor_arguments_fail_even_with_updated_hash(self):
        self.factory(FACTORY.replace("::counter, ::values", "::values, ::counter"))
        self.assert_error(self.sources(), "factory must only return")
        self.assertFalse(any("hash is stale" in error for error in self.sources()))

    def test_safe_inventory_paths_and_original_source_anchor_are_required(self):
        for source in ("../escape.cpp", "src/units/../other.cpp", "/tmp/escape.cpp",
                       "C:/escape.cpp", "src\\units\\old.cpp", "src/units/new.cpp", "src/units/x\x00.cpp"):
            with self.subTest(source=source):
                self.binding["source"] = source
                self.assert_error(self.metadata(), "safe path in the recovered inventory")
        self.binding["source"] = OLD
        self.registry["identities"][0]["legacy_source"] = OTHER
        self.assert_error(self.metadata(), "original adapter/storage anchor")

    def test_inventory_symlink_may_not_escape_repository(self):
        with tempfile.TemporaryDirectory(prefix="outside-binding-") as directory:
            outside = Path(directory) / "outside.cpp"
            outside.write_text(ADAPTER + FACTORY, encoding="utf-8")
            (self.root / OLD).unlink()
            (self.root / OLD).symlink_to(outside)
            self.assert_error(self.sources(), "resolves outside root")

    def test_stale_factory_hash_is_not_accepted(self):
        self.factory(FACTORY.replace("return Probe", "/* changed */ return Probe"), refresh_hash=False)
        self.assert_error(self.sources(), "body hash is stale")

    def test_duplicate_factory_elsewhere_in_inventory_is_not_hidden(self):
        self.write(OTHER, "int Other_Read() { return 0; }\n" + FACTORY)
        self.assert_error(self.sources(), "outside its registered source")
        self.assert_error(self.sources(), "expected one qualified definition, found 2")

    def test_missing_factory_and_unregistered_qualified_definitions_fail(self):
        self.write(OLD, ADAPTER)
        self.assert_error(self.sources(), "clash95::Probe::borrow: expected one qualified definition, found 0")
        self.write(OLD, ADAPTER + FACTORY + "int clash95::Probe::Untracked() { return 8; }\n")
        self.assert_error(self.sources(), "unregistered qualified definition clash95::Probe::Untracked")
        self.registry["class_bindings"] = []
        self.assert_error(self.sources(), "unregistered qualified definition clash95::Probe::borrow")

    def test_recovered_method_cannot_hide_under_registered_borrow_name(self):
        self.write(CLASS, "int clash95::Probe::borrow() { return 42; }\n")
        self.assert_error(self.sources(), "clash95::Probe::Probe_Read: expected one qualified definition, found 0")
        self.assert_error(self.sources(), "clash95::Probe::borrow: expected one qualified definition, found 2")

    def test_effects_values_and_calls_cannot_hide_inside_rehashed_factory(self):
        for body in ("int cached = ::counter; return Probe(::counter, ::values);",
                     "static int cache; return Probe(::counter, ::values);",
                     "return Probe(::counter++, ::values);",
                     "return Probe(identity(::counter), ::values);",
                     "return Probe(42, ::values);", "return Probe(\"counter\", ::values);",
                     "return Probe('x', ::values);", "return Probe(::counter, ::values[0]);",
                     "return Probe(::counter, ::values); extra();",
                     "#if 1\nreturn Probe(::counter, ::values);\n#endif"):
            with self.subTest(body=body):
                self.factory("clash95::Probe clash95::Probe::borrow() noexcept\n{\n" + body + "\n}\n")
                self.assert_error(self.sources(), "factory must only return")

    def test_wrong_signature_is_rejected_without_relying_on_body_hash(self):
        for signature in ("clash95::Probe clash95::Probe::borrow(int ignored) noexcept",
                          "clash95::Probe clash95::Probe::borrow()",
                          "int clash95::Probe::borrow() noexcept",
                          "clash95::Probe clash95::Probe::borrow() const noexcept"):
            with self.subTest(signature=signature):
                self.factory(FACTORY.replace(FACTORY.splitlines()[0], signature))
                self.assert_error(self.sources(), "factory must only return")

    def test_comments_preserve_factory_shape_and_namespace_scan_finds_unknown_method(self):
        self.factory(FACTORY.replace("return Probe", '/* "ignored" extra(); */ return /* x */ Probe'))
        self.assertEqual(self.sources(), [])
        self.write(OTHER, "namespace clash95 { int Probe::Extra() const noexcept { return 0; } }\n")
        self.assert_error(self.sources(), "unregistered qualified definition clash95::Probe::Extra")

    def test_registered_helper_uses_current_declaration_source(self):
        self.helper()
        self.write(CLASS, METHOD + "void clash95::Probe::Probe_Ensure() {}\n")
        self.assertEqual(self.sources(), [])
        self.declarations["functions"]["Probe_Ensure"]["source"] = OLD
        self.assert_error(self.sources(), "outside its registered source")

    def test_unextracted_helper_assignment_does_not_require_qualified_body(self):
        self.helper(source=OLD)
        self.write(OLD, ADAPTER + FACTORY + "void Probe_Ensure() {}\n")
        self.assertEqual(self.sources(), [])

    def test_moved_helper_declaration_requires_one_qualified_body(self):
        self.helper()
        self.assert_error(self.sources(), "clash95::Probe::Probe_Ensure: expected one qualified definition, found 0")
        helper = "void clash95::Probe::Probe_Ensure() {}\n"
        self.write(CLASS, METHOD + helper + helper)
        self.assert_error(self.sources(), "clash95::Probe::Probe_Ensure: expected one qualified definition, found 2")

    def test_helper_cannot_be_authorized_outside_closed_inventory(self):
        self.helper(source="src/units/Untracked.cpp")
        self.assert_error(self.sources(), "helper declaration source is outside the recovered inventory")

    def test_duplicate_or_unregistered_helper_cannot_authorize_unknown_method(self):
        self.helper()
        self.registry["helpers"].append(copy.deepcopy(self.registry["helpers"][0]))
        self.assert_error(self.metadata(), "duplicate helper method registration")
        self.registry["helpers"].pop()
        self.declarations["functions"]["Probe_Ensure"]["class"] = "original"
        self.assert_error(self.metadata(), "canonical helper declaration")

    def test_helper_cannot_register_replacement_borrow_factory(self):
        self.helper(name="borrow")
        self.assert_error(self.metadata(), "separate class_bindings registration")
        self.assert_error(self.metadata(), "factory must not replace")

    def test_malformed_helper_metadata_does_not_crash_source_audit(self):
        self.registry["helpers"] = None
        self.assert_error(self.sources(), "helper array")
        self.registry["helpers"] = []
        self.declarations["functions"] = None
        self.assert_error(self.sources(), "function declaration object")

    def test_legacy_free_only_inventory_needs_no_binding_declarations(self):
        self.assertEqual(validate_binding_metadata({}, {"schema_version": 2, "functions": []}), [])
        self.assertEqual(validate_binding_sources({}, {"schema_version": 2, "functions": []}, {}, self.root), [])

    def test_unbalanced_source_reports_error_instead_of_crashing(self):
        self.write(CLASS, "int clash95::Probe::Probe_Read() { return 1;\n")
        self.assert_error(self.sources(), "unbalanced definition")


class CheckedInBindingInventoryTests(unittest.TestCase):
    def test_current_registry_and_complete_source_inventory(self):
        registry, manifest, declarations = [json.loads((ROOT / "data" / name).read_text(encoding="utf-8"))
                                            for name in ("game_class_registry.json", "recovered_sources.json", "recovered_decls.json")]
        self.assertEqual(validate_binding_metadata(registry, manifest, declarations), [])
        self.assertEqual(validate_binding_sources(registry, manifest, declarations, ROOT), [])


if __name__ == "__main__":
    unittest.main()
