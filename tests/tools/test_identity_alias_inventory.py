"""Historical ABI aliases keep exactly one algorithm and their declared types."""
import copy
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from identity_alias_inventory import validate_alias_metadata, validate_alias_sources
from split_source_index import body_sha256, scan_definitions


OLD = "src/render/old.cpp"
OTHER = "src/units/other.cpp"
CLASS = "src/render/Surface.cpp"
CANONICAL = "int Render_SetResourceHandle(int surface, int new_flag) { return surface + new_flag; }\n"
ALIAS = "int Surface_SwapDirtyTrackingFlag(int surface, int new_flag) { return Render_SetResourceHandle(surface, new_flag); }\n"
NAME = "Surface_SwapDirtyTrackingFlag"
TARGET = "Render_SetResourceHandle"


def digest(text, name):
    matches = scan_definitions(text, {name})
    if len(matches) != 1:
        raise AssertionError((name, matches))
    return body_sha256(text, matches[0])


class AliasInventoryTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="identity-alias-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.alias = {"name": NAME, "source": OLD, "body_sha256": digest(ALIAS, NAME),
                      "reason": "Retain the exported historical name after proven identity migration."}
        self.record = {"name": TARGET, "source": OLD, "body_sha256": digest(CANONICAL, TARGET),
                       "original_address": "0x00404A40", "historical_names": [NAME],
                       "compatibility_aliases": [self.alias],
                       "implementation": {"kind": "free", "qualified_name": TARGET}}
        self.manifest = {"schema_version": 3, "functions": [self.record, {"name": "Other", "source": OTHER}]}
        self.helper = {"name": NAME, "source": OLD, "classification": "retained-boundary",
                       "rationale": "Preserve the historical exported ABI without duplicating its algorithm."}
        self.registry = {"identities": [{"name": TARGET}, {"name": "Other"}], "helpers": [self.helper]}
        self.declarations = {"functions": {
            TARGET: {"class": "manifest", "decl": "int Render_SetResourceHandle(int record, int value);"},
            NAME: {"class": "helper", "source": OLD,
                   "decl": "int Surface_SwapDirtyTrackingFlag(int surface, int new_flag);"},
        }}
        self.write(OLD, CANONICAL + ALIAS)
        self.write(OTHER, "int Other() { return 0; }\n")

    def write(self, source, text):
        path = self.root / source
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def metadata(self):
        return validate_alias_metadata(self.manifest, self.declarations, self.registry)

    def sources(self):
        return validate_alias_sources(self.manifest, self.root, self.declarations, self.registry)

    def assert_error(self, errors, part):
        self.assertTrue(any(part in error for error in errors), errors)

    def change_alias(self, text, *, refresh_hash=True):
        self.write(OLD, CANONICAL + text)
        if refresh_hash:
            self.alias["body_sha256"] = digest(text, NAME)

    def test_valid_forwarder_is_pure_and_read_only(self):
        before = copy.deepcopy((self.manifest, self.declarations, self.registry))
        files = {path: path.read_bytes() for path in self.root.rglob("*.cpp")}
        self.assertEqual(self.metadata(), [])
        self.assertEqual(self.sources(), [])
        self.assertEqual(before, (self.manifest, self.declarations, self.registry))
        self.assertEqual(files, {path: path.read_bytes() for path in files})

    def test_no_aliases_requires_no_alias_definitions(self):
        self.record.pop("historical_names")
        self.record.pop("compatibility_aliases")
        self.assertEqual(self.metadata(), [])
        self.assertEqual(self.sources(), [])

    def test_method_target_uses_original_adapter_after_relocation(self):
        method_name = "clash95::Surface::" + TARGET
        method = "int " + method_name + "(int surface, int new_flag) const { return surface + new_flag; }\n"
        adapter = "int Render_SetResourceHandle(int surface, int new_flag) { return clash95::Surface().Render_SetResourceHandle(surface, new_flag); }\n"
        self.record["source"] = CLASS
        self.record["implementation"] = {"kind": "method", "qualified_name": method_name}
        self.record["body_sha256"] = digest(method, method_name)
        self.record["adapter"] = {"source": OLD, "body_sha256": digest(adapter, TARGET)}
        self.write(CLASS, method)
        self.write(OLD, adapter + ALIAS)
        self.assertEqual(self.sources(), [])
        self.write(CLASS, "// lost canonical method\n")
        self.assert_error(self.sources(), "expected one definition")

    def test_explicit_null_adapter_is_valid_for_free_implementation(self):
        self.record["adapter"] = None
        self.assertEqual(self.sources(), [])

    def test_history_cannot_lose_or_invent_undocumented_names(self):
        for history in ([], [NAME, "Untracked"], [TARGET], [NAME, NAME]):
            with self.subTest(history=history):
                self.record["historical_names"] = history
                self.assertTrue(self.metadata())
        self.record["historical_names"] = [NAME]
        self.record["compatibility_aliases"] = []
        self.assert_error(self.metadata(), "no lost or undocumented spelling")

    def test_duplicate_alias_within_or_across_identities_is_rejected(self):
        self.record["compatibility_aliases"].append(copy.deepcopy(self.alias))
        self.assert_error(self.metadata(), "duplicate compatibility alias")
        self.record["compatibility_aliases"].pop()
        other = self.manifest["functions"][1]
        other.update(historical_names=[NAME], compatibility_aliases=[copy.deepcopy(self.alias)])
        self.assert_error(self.metadata(), "duplicate compatibility alias")

    def test_alias_cannot_be_a_canonical_identity_or_another_target(self):
        self.manifest["functions"].append({"name": NAME, "source": OTHER})
        self.assert_error(self.metadata(), "another canonical implementation or recovered identity")
        self.manifest["functions"].pop()
        self.registry["identities"].append({"name": NAME})
        self.assert_error(self.metadata(), "another canonical implementation or recovered identity")

    def test_alias_must_have_exact_address_free_fields(self):
        for key in ("original_address", "original_source", "qualified_name", "implementation"):
            with self.subTest(key=key):
                self.alias[key] = "invented"
                self.assert_error(self.metadata(), "exactly name/source/body_sha256/reason")
                del self.alias[key]

    def test_helper_registration_is_unique_retained_and_address_free(self):
        self.registry["helpers"] = []
        self.assert_error(self.metadata(), "one retained-boundary helper")
        self.registry["helpers"] = [self.helper, self.helper]
        self.assert_error(self.metadata(), "one retained-boundary helper")
        self.registry["helpers"] = [self.helper]
        for key, value in (("classification", "game-method"), ("source", OTHER),
                           ("original_address", "0x00404A40"), ("rationale", " ")):
            with self.subTest(key=key):
                old = copy.deepcopy(self.helper)
                self.helper[key] = value
                self.assert_error(self.metadata(), "address-free retained-boundary")
                self.helper.clear()
                self.helper.update(old)

    def test_alias_and_target_require_closed_canonical_declarations(self):
        self.declarations["functions"][NAME]["class"] = "manifest"
        self.assert_error(self.metadata(), "address-free helper declaration")
        self.declarations["functions"][NAME]["class"] = "helper"
        self.declarations["functions"][NAME]["source"] = OTHER
        self.assert_error(self.metadata(), "address-free helper declaration")
        self.declarations["functions"][NAME]["source"] = OLD
        self.declarations["functions"][TARGET]["class"] = "import"
        self.assert_error(self.metadata(), "canonical manifest declaration")

    def test_canonical_registry_name_must_exist_exactly_once(self):
        self.registry["identities"] = []
        self.assert_error(self.metadata(), "one canonical identity registration")
        self.registry["identities"] = [{"name": TARGET}, {"name": TARGET}]
        self.assert_error(self.metadata(), "one canonical identity registration")

    def test_safe_original_anchor_required(self):
        for source in (OTHER, "../escape.cpp", "/tmp/escape.cpp", "src/render/../old.cpp",
                       "src\\render\\old.cpp", "C:/old.cpp", "src/render/new.cpp", "src/render/x\x00.cpp"):
            with self.subTest(source=source):
                self.alias["source"] = source
                self.assert_error(self.metadata(), "safe original canonical/adapter anchor")

    def test_symlink_escape_in_any_inventory_source_is_rejected(self):
        with tempfile.TemporaryDirectory(prefix="outside-alias-") as directory:
            outside = Path(directory) / "outside.cpp"
            outside.write_text("int Other() { return 0; }\n", encoding="utf-8")
            (self.root / OTHER).unlink()
            (self.root / OTHER).symlink_to(outside)
            self.assert_error(self.sources(), "resolves outside root")

    def test_missing_duplicate_and_misplaced_definitions_are_rejected(self):
        self.write(OLD, CANONICAL)
        self.assert_error(self.sources(), "expected one definition")
        self.write(OTHER, ALIAS)
        self.assert_error(self.sources(), "outside its registered source")
        self.write(OLD, CANONICAL + ALIAS)
        self.assert_error(self.sources(), "expected one definition")

    def test_duplicate_or_missing_canonical_abi_target_is_rejected(self):
        self.write(OLD, ALIAS)
        self.assert_error(self.sources(), "expected one definition")
        self.write(OLD, CANONICAL + ALIAS)
        self.write(OTHER, CANONICAL)
        self.assert_error(self.sources(), "expected one definition")

    def test_stale_alias_hash_is_rejected(self):
        self.change_alias(ALIAS.replace("surface, new_flag);", "new_flag, surface);"), refresh_hash=False)
        self.assert_error(self.sources(), "body hash is stale")

    def test_algorithm_argument_changes_and_wrong_targets_cannot_hide_behind_new_hash(self):
        for body in ("return Render_SetResourceHandle(new_flag, surface);",
                     "return Render_SetResourceHandle(surface + 1, new_flag);",
                     "return Render_SetResourceHandle(surface, (int)new_flag);",
                     "return Surface_SwapDirtyTrackingFlag(surface, new_flag);",
                     "return AnotherTarget(surface, new_flag);",
                     "int copy = surface; return Render_SetResourceHandle(copy, new_flag);",
                     "return Render_SetResourceHandle(surface, new_flag) + 0;",
                     "Render_SetResourceHandle(surface, new_flag); return 0;",
                     "return (Render_SetResourceHandle)(surface, new_flag);",
                     "return Render_SetResourceHandle(surface, new_flag); ;"):
            with self.subTest(body=body):
                self.change_alias("int " + NAME + "(int surface, int new_flag) { " + body + " }\n")
                errors = self.sources()
                self.assert_error(errors, "alias must only return")
                self.assertFalse(any("hash is stale" in error for error in errors), errors)

    def test_comments_and_explicit_global_qualification_do_not_add_behavior(self):
        self.change_alias(ALIAS.replace("return Render", "/* ABI */ return ::Render"))
        self.assertEqual(self.sources(), [])

    def test_known_retention_attributes_do_not_change_abi(self):
        self.change_alias("__attribute__((used, retain)) " + ALIAS)
        self.assertEqual(self.sources(), [])
        self.change_alias("__attribute__((used, retain))\n" + ALIAS)
        self.assertEqual(self.sources(), [])
        for spacing in (" ", "\n"):
            self.change_alias("__attribute__((weak))" + spacing + ALIAS)
            self.assert_error(self.sources(), "unsupported result type or signature attribute")

    def test_return_types_width_signedness_pointers_and_calling_convention_are_exact(self):
        original = self.declarations["functions"][NAME]["decl"]
        for declaration in (original.replace("int Surface", "long Surface"),
                            original.replace("int surface", "unsigned int surface"),
                            original.replace("int surface", "int *surface"),
                            original.replace("int new_flag", "short new_flag"),
                            original.replace("Surface_", "__stdcall Surface_")):
            with self.subTest(declaration=declaration):
                self.declarations["functions"][NAME]["decl"] = declaration
                self.assert_error(self.metadata(), "declared ABI types differ")

    def test_actual_alias_and_canonical_signatures_must_match_their_declarations(self):
        self.change_alias(ALIAS.replace("int surface", "unsigned int surface"))
        self.assert_error(self.sources(), "does not preserve its declared ABI types")
        self.write(OLD, CANONICAL.replace("int new_flag", "short new_flag") + ALIAS)
        self.assert_error(self.sources(), "does not preserve its declared ABI types")

    def test_parameter_names_may_differ_but_forward_the_actual_names_in_order(self):
        self.change_alias(ALIAS.replace("surface", "record").replace("new_flag", "value"))
        self.assertEqual(self.sources(), [])

    def test_void_and_pointer_returns_can_forward_without_conversion(self):
        for result in ("void", "unsigned __int8 *"):
            with self.subTest(result=result):
                for name in (NAME, TARGET):
                    self.declarations["functions"][name]["decl"] = result + " " + name + "(int surface, int new_flag);"
                self.change_alias(result + ALIAS[3:])
                body = "return;" if result == "void" else "return 0;"
                canonical = result + " " + TARGET + "(int surface, int new_flag) { " + body + " }\n"
                self.write(OLD, canonical + result + ALIAS[3:])
                self.assertEqual(self.sources(), [])

    def test_no_parameter_forwarding_preserves_void_or_empty_spelling(self):
        canonical = "int Render_SetResourceHandle(void) { return 1; }\n"
        alias = "int Surface_SwapDirtyTrackingFlag() { return Render_SetResourceHandle(); }\n"
        self.write(OLD, canonical + alias)
        self.alias["body_sha256"] = digest(alias, NAME)
        self.declarations["functions"][TARGET]["decl"] = "int Render_SetResourceHandle();"
        self.declarations["functions"][NAME]["decl"] = "int Surface_SwapDirtyTrackingFlag(void);"
        self.assertEqual(self.sources(), [])

    def test_variadic_default_and_complex_declarators_fail_closed(self):
        for parameters in ("int value, ...", "int value = 0", "int values[3]", "int (*callback)(int)", "int, int"):
            with self.subTest(parameters=parameters):
                self.declarations["functions"][NAME]["decl"] = "int " + NAME + "(" + parameters + ");"
                self.assert_error(self.metadata(), "invalid ABI declaration")

    def test_static_alias_is_not_an_exported_compatibility_symbol(self):
        for spacing in (" ", "\n"):
            self.change_alias("static" + spacing + ALIAS)
            self.assert_error(self.sources(), "preserve external ABI linkage")

    def test_anonymous_namespace_cannot_hide_an_exported_alias_or_target(self):
        self.write(OLD, CANONICAL + "namespace {\n" + ALIAS + "}\n")
        self.assert_error(self.sources(), "must be at global scope")
        self.write(OLD, "namespace {\n" + CANONICAL + "}\n" + ALIAS)
        self.assert_error(self.sources(), "must be at global scope")

    def test_macro_rewriting_of_forwarder_is_rejected(self):
        for name in (NAME, TARGET, "surface", "new_flag"):
            with self.subTest(name=name):
                self.write(OLD, "#define " + name + " Replacement\n" + CANONICAL + ALIAS)
                self.assert_error(self.sources(), "macro rewriting")

    def test_schema_hash_reason_and_metadata_container_errors(self):
        self.manifest["schema_version"] = 2
        self.assertTrue(self.metadata())
        self.manifest["schema_version"] = 3
        for digest_value in (None, "A" * 64, "a" * 63, 7):
            self.alias["body_sha256"] = digest_value
            self.assert_error(self.metadata(), "lowercase SHA-256")
        self.alias["body_sha256"] = digest(ALIAS, NAME)
        self.alias["reason"] = " "
        self.assert_error(self.metadata(), "compatibility reason")
        self.alias["reason"] = "Preserve ABI."
        for history in (None, "old", [1], ["bad::name"]):
            self.record["historical_names"] = history
            self.assert_error(self.metadata(), "array of identifiers")
        self.record["historical_names"] = [NAME]
        self.record["compatibility_aliases"] = [None]
        self.assert_error(self.metadata(), "alias must be an object")
        self.record["compatibility_aliases"] = None
        self.assert_error(self.metadata(), "aliases must be an array")
        self.assertTrue(validate_alias_metadata([], self.declarations, self.registry))
        self.assertTrue(validate_alias_metadata(self.manifest, {}, self.registry))


if __name__ == "__main__":
    unittest.main()
