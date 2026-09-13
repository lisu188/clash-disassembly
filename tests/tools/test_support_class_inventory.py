"""Support behavior is explicitly inventoried outside the recovered identities."""
import contextlib
import copy
import io
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from support_class_inventory import (SCOPE_SOURCES, declared_state_names, direct_state_references,
                                     inventory_summary, main, origin_inventory_sha256, signature_sha256,
                                     validate_inventory_metadata, validate_inventory_sources)
from split_source_index import body_sha256, scan_definitions


OLD, OTHER, _, _, HEADER, _ = SCOPE_SOURCES
CLASS = "src/platform/Probe.cpp"
BODY = "int Probe_Run(int value) { return shared_state + value; }\n"
BOUNDARY = "int Probe_Boundary() { return 0; }\n"
INLINE = "static inline int Probe_Header() { return 1; }\n"


def definition(text, name):
    matches = scan_definitions(text, {name})
    if len(matches) != 1:
        raise AssertionError((name, matches))
    return matches[0]


def record(source, name, text, *, runtime=False):
    d = definition(text, name)
    body, signature = body_sha256(text, d), signature_sha256(text, d)
    result = {
        "id": source + "::" + name, "identity_kind": "support-definition",
        "origin_source": source, "name": name, "source": source, "qualified_name": name,
        "body_sha256": body, "signature_sha256": signature,
        "origin_body_sha256": body, "origin_signature_sha256": signature,
        "surface": "header-inline" if source.endswith(".h") else "translation-unit",
        "disposition": "runtime-method" if runtime else "procedural-boundary",
        "owner": "Probe" if runtime else "CompatibilityUtilities", "logical_subsystem": "platform",
        "migration": {"extraction": "planned" if runtime else "retained",
                      "relocation": "pending" if runtime else "not-applicable"},
        "boundary_roles": ["public-c-abi" if runtime else "internal-support"],
        "binding_role": "borrow-existing-state" if runtime else "retain-existing-storage",
        "direct_state_references": ["shared_state"] if runtime else [],
        "constraints": ["preserve-current-storage-and-linkage", "no-new-dynamic-initialization"],
        "blockers": [], "rationale": "This exact fixture definition retains its existing storage and callable contract.",
        "evidence": [source + "::" + name],
    }
    if runtime:
        result.update(final_header="src/platform/Probe.hpp", final_source=CLASS)
    return result


class SupportInventoryTest(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="support-inventory-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        for source in SCOPE_SOURCES:
            self.write(source, "// explicitly empty fixture support surface\n")
        self.write(OLD, "int shared_state;\n" + BODY)
        self.write(OTHER, BOUNDARY)
        self.write(HEADER, INLINE)
        self.runtime = record(OLD, "Probe_Run", BODY, runtime=True)
        self.retained = record(OTHER, "Probe_Boundary", BOUNDARY)
        self.header = record(HEADER, "Probe_Header", INLINE)
        self.document = {"schema_version": 1, "scope_sources": list(SCOPE_SOURCES), "definition_count": 3,
                         "definitions": [self.runtime, self.retained, self.header],
                         "source_reference_commit": "a" * 40,
                         "source_reference_files": [{"source": source,
                             "sha256": hashlib.sha256((self.root / source).read_bytes()).hexdigest(),
                             "definition_count": int(source in {OLD, OTHER, HEADER})} for source in SCOPE_SOURCES]}
        self.refresh_origin()
        self.manifest = {"functions": [{"name": "Recovered_Only", "source": "src/units/recovered.cpp"}]}
        self.declarations = {"globals": {"shared_state": {"decl": "extern int shared_state;"}}}

    def write(self, source, text):
        path = self.root / source
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")

    def refresh_origin(self):
        self.document["origin_inventory_sha256"] = origin_inventory_sha256(self.document["definitions"])

    def metadata(self):
        return validate_inventory_metadata(self.document, self.manifest)

    def sources(self):
        return validate_inventory_sources(self.document, self.root, self.manifest, self.declarations)

    def assert_error(self, errors, part):
        self.assertTrue(any(part in error for error in errors), errors)

    def update_body(self, item, text, *, name=None, source=None):
        d = definition(text, name or item["qualified_name"])
        item["body_sha256"] = body_sha256(text, d)
        item["signature_sha256"] = signature_sha256(text, d)
        self.write(source or item["source"], text)

    def extract(self, *, relocate=False, adapter=True):
        method_name = "clash95::Probe::Probe_Run"
        method = "int " + method_name + "(int value) const { return shared_state + value; }\n"
        self.runtime["migration"] = {"extraction": "extracted", "relocation": "relocated" if relocate else "pending"}
        self.runtime["qualified_name"] = method_name
        self.runtime["source"] = CLASS if relocate else OLD
        self.update_body(self.runtime, method)
        wrapper = "int Probe_Run(int value) { return clash95::Probe().Probe_Run(value); }\n" if adapter else ""
        if adapter:
            d = definition(wrapper, "Probe_Run")
            self.runtime["adapter"] = {"source": OLD, "qualified_name": "Probe_Run",
                                       "body_sha256": body_sha256(wrapper, d), "signature_sha256": signature_sha256(wrapper, d)}
        self.write(OLD, "int shared_state;\n" + wrapper + ("" if relocate else method))

    def test_metadata_and_source_validation_are_read_only(self):
        before = copy.deepcopy((self.document, self.manifest, self.declarations))
        files = {source: (self.root / source).read_bytes() for source in SCOPE_SOURCES}
        self.assertEqual(self.metadata(), [])
        self.assertEqual(self.sources(), [])
        self.assertEqual(before, (self.document, self.manifest, self.declarations))
        self.assertEqual(files, {source: (self.root / source).read_bytes() for source in files})

    def test_summary_keeps_support_and_diagnostic_counts_separate(self):
        self.retained["boundary_roles"] = ["diagnostic-infrastructure"]
        self.assertEqual(inventory_summary(self.document), {
            "definitions": 3, "surfaces": {"translation-unit": 2, "header-inline": 1},
            "dispositions": {"runtime-method": 1, "procedural-boundary": 2},
            "retained_diagnostic_definitions": 1, "runtime_class_owners": {"Probe": 1}})

    def test_unclassified_new_definition_in_any_audited_file_is_rejected(self):
        self.write(SCOPE_SOURCES[-1], "int Unclassified() { return 0; }\n")
        self.assert_error(self.sources(), "unclassified support definition")

    def test_lost_definition_is_rejected(self):
        self.write(OTHER, "// removed boundary\n")
        self.assert_error(self.sources(), "expected one definition, found 0")

    def test_duplicate_definition_is_rejected(self):
        self.write(OTHER, BOUNDARY + BOUNDARY)
        self.assert_error(self.sources(), "expected one definition, found 2")

    def test_removing_record_and_source_cannot_erase_frozen_origin(self):
        self.document["definitions"].remove(self.retained)
        self.document["definition_count"] -= 1
        self.write(OTHER, "// removed body and metadata\n")
        self.assert_error(self.sources(), "immutable support origin inventory fingerprint differs")

    def test_ids_and_original_hashes_are_frozen_independently_of_current_hashes(self):
        for field, value in (("id", "invented"), ("name", "Changed"), ("origin_source", OTHER),
                             ("origin_body_sha256", "f" * 64), ("origin_signature_sha256", "f" * 64)):
            with self.subTest(field=field):
                old = self.runtime[field]
                self.runtime[field] = value
                self.assert_error(self.metadata(), "immutable support origin inventory fingerprint differs")
                self.runtime[field] = old
        self.runtime["body_sha256"] = "f" * 64
        self.assertEqual(self.metadata(), [])
        self.assert_error(self.sources(), "canonical body hash is stale")

    def test_body_and_signature_drift_are_independent_failures(self):
        self.write(OLD, "int shared_state;\n" + BODY.replace("+ value", "- value"))
        errors = self.sources()
        self.assert_error(errors, "canonical body hash is stale")
        self.assertFalse(any("signature hash is stale" in error for error in errors), errors)
        self.write(OLD, "int shared_state;\n" + BODY.replace("int value", "long value"))
        errors = self.sources()
        self.assert_error(errors, "canonical signature hash is stale")
        self.assertFalse(any("body hash is stale" in error for error in errors), errors)

    def test_support_cannot_inflate_recovered_identity_count_or_invent_addresses(self):
        self.manifest["functions"].append({"name": "Probe_Run"})
        self.assert_error(self.metadata(), "overlaps a recovered identity")
        self.manifest["functions"].pop()
        self.runtime["original_address"] = "0x00400000"
        self.assert_error(self.metadata(), "original identity fields are forbidden")
        del self.runtime["original_address"]
        self.runtime["identity_kind"] = "original"
        self.assert_error(self.metadata(), "identity_kind must be support-definition")

    def test_duplicate_ids_and_targets_are_rejected(self):
        self.document["definitions"].append(copy.deepcopy(self.runtime))
        self.document["definition_count"] += 1
        self.refresh_origin()
        self.assert_error(self.metadata(), "duplicate support identity")
        self.assert_error(self.metadata(), "duplicate canonical definition target")

    def test_frozen_source_context_has_exact_scope_and_historical_counts(self):
        self.document["source_reference_commit"] = "current"
        self.assert_error(self.metadata(), "frozen source snapshot")
        self.document["source_reference_commit"] = "a" * 40
        self.document["source_reference_files"][0]["sha256"] = "a" * 63
        self.assert_error(self.metadata(), "invalid frozen source hash/count")
        self.document["source_reference_files"] = []
        self.assert_error(self.metadata(), "all six frozen source hashes")

    def test_exact_six_file_scope_and_source_surface_are_required(self):
        self.document["scope_sources"] = list(reversed(SCOPE_SOURCES))
        self.assert_error(self.metadata(), "all six explicitly audited support files in order")
        self.document["scope_sources"] = list(SCOPE_SOURCES)
        self.header["surface"] = "translation-unit"
        self.assert_error(self.metadata(), "surface differs from the original support source")

    def test_path_escape_and_symlink_escape_are_rejected(self):
        for path in ("/tmp/Probe.cpp", "../Probe.cpp", "src/platform/../Probe.cpp", "src\\platform\\Probe.cpp", "C:/Probe.cpp"):
            self.runtime["source"] = path
            self.assert_error(self.metadata(), "invalid canonical source")
        self.runtime["source"] = OLD
        with tempfile.TemporaryDirectory(prefix="outside-support-") as outside:
            target = Path(outside) / "outside.cpp"
            target.write_text(BODY, encoding="utf-8")
            (self.root / OLD).unlink()
            (self.root / OLD).symlink_to(target)
            self.assert_error(self.sources(), "resolves outside repository")

    def test_missing_support_source_is_not_silently_skipped(self):
        (self.root / SCOPE_SOURCES[-1]).unlink()
        self.assert_error(self.sources(), "cannot read/index support source")

    def test_runtime_disposition_needs_explicit_owner_and_class_destinations(self):
        for key, value, error in (("disposition", "unclassified", "unclassified disposition"),
                                  ("owner", "", "explicit valid owner"),
                                  ("logical_subsystem", "", "logical_subsystem is required"),
                                  ("final_header", "src/platform/Other.hpp", "exact class-named destinations"),
                                  ("binding_role", "own-state", "borrow existing state")):
            old = self.runtime[key]
            self.runtime[key] = value
            self.assert_error(self.metadata(), error)
            self.runtime[key] = old

    def test_retained_boundaries_cannot_claim_class_extraction_or_destinations(self):
        self.retained["final_source"] = CLASS
        self.assert_error(self.metadata(), "cannot claim class migration")
        del self.retained["final_source"]
        self.retained["migration"]["extraction"] = "extracted"
        self.assert_error(self.metadata(), "cannot claim class migration")

    def test_diagnostics_remain_elected_procedural_utilities(self):
        self.runtime["boundary_roles"].append("diagnostic-infrastructure")
        self.assert_error(self.metadata(), "diagnostics are explicitly retained procedural infrastructure")

    def test_extraction_and_relocation_are_separately_audited(self):
        self.extract()
        self.assertEqual(self.sources(), [])
        origin = self.runtime["id"]
        self.extract(relocate=True)
        self.assertEqual(self.sources(), [])
        self.assertEqual(self.runtime["id"], origin)
        self.runtime["source"] = OLD
        self.assert_error(self.metadata(), "relocated implementation must use its assigned class source")

    def test_exposed_extraction_requires_an_original_abi_adapter(self):
        self.extract(adapter=False)
        self.assert_error(self.metadata(), "exposed callable identity requires an explicit adapter")

    def test_adapter_is_a_separate_exact_target_with_separate_hashes(self):
        self.extract(relocate=True)
        self.runtime["adapter"]["body_sha256"] = "f" * 64
        self.assert_error(self.sources(), "adapter body hash is stale")
        self.runtime["adapter"]["signature_sha256"] = "f" * 64
        self.assert_error(self.sources(), "adapter signature hash is stale")
        self.runtime["adapter"]["source"] = CLASS
        self.assert_error(self.metadata(), "adapter must retain the original source/name")

    def test_unregistered_helpers_in_new_class_source_are_rejected(self):
        self.extract(relocate=True)
        with (self.root / CLASS).open("a") as output:
            output.write("int Untracked_Helper() { return 0; }\n")
        self.assert_error(self.sources(), "unclassified support definition")

    def test_shared_class_source_may_contain_explicit_recovered_methods(self):
        self.extract(relocate=True)
        qualified = "clash95::Probe::Recovered_Only"
        self.manifest = {"schema_version": 3, "functions": [
            {"name": "Recovered_Only", "source": CLASS,
             "implementation": {"kind": "method", "qualified_name": qualified},
             "adapter": {"source": "src/units/recovered.cpp", "body_sha256": "a" * 64}}]}
        with (self.root / CLASS).open("a") as output:
            output.write("int " + qualified + "() { return 1; }\n")
        self.assertEqual(self.sources(), [])
        self.manifest["functions"][0]["source"] = "src/units/recovered.cpp"
        self.assert_error(self.sources(), "unclassified support definition")

    def test_recovered_registration_cannot_hide_an_extra_original_support_body(self):
        self.manifest["functions"][0]["source"] = OLD
        with (self.root / OLD).open("a") as output:
            output.write("int Recovered_Only() { return 0; }\n")
        self.assert_error(self.sources(), "unclassified support definition")

    def test_local_static_storage_requires_explicit_constraint(self):
        body = BODY.replace("return shared_state", "static int lazy; return lazy + shared_state")
        self.update_body(self.runtime, body)
        self.assert_error(self.sources(), "local-static storage constraint is missing")
        self.runtime["constraints"].append("preserve-local-static-storage")
        self.assertEqual(self.sources(), [])

    def test_direct_state_reference_drift_is_not_silently_accepted(self):
        self.runtime["direct_state_references"] = []
        self.assert_error(self.sources(), "direct state reference evidence differs")

    def test_direct_state_scan_excludes_formals_members_comments_and_literals(self):
        text = '''int Probe_Run(int shared_state) {
            // other_state is not an access
            const char *label = "other_state";
            return shared_state + obj.other_state + ptr->other_state + global_value;
        }'''
        d = definition(text, "Probe_Run")
        self.assertEqual(direct_state_references(text, d, {"shared_state", "other_state", "global_value"}), ["global_value"])
        globals_ = declared_state_names({OLD: "static int one;\nextern int two[3];\n" + text})
        self.assertTrue({"one", "two"} <= globals_, globals_)
        self.assertNotIn("label", globals_)

    def test_assembler_labels_preserve_scalar_and_array_state_names(self):
        for spelling in ("asm", "__asm", "__asm__"):
            for declaration, name in (
                    ('static char command_line[1024] @ASM@("linked_buffer");', "command_line"),
                    ('int count @ASM@("linked_count") = 7;', "count"),
                    ('extern unsigned long flags @ASM@("linked_flags");', "flags"),
                    ('static int matrix[2][3] @ASM@("linked_" "matrix");', "matrix"),
                    ('static int escaped @ASM@("linked\\\"name");', "escaped"),
                    ('static int multiline @ASM@\n(\n"linked_name"\n);', "multiline")):
                with self.subTest(spelling=spelling, name=name):
                    source = declaration.replace("@ASM@", spelling)
                    self.assertEqual(declared_state_names({OLD: source}), {name})

    def test_assembler_label_scan_excludes_prototypes_locals_and_nonliteral_clauses(self):
        source = r'''
static int plain;
static const char *message = "int string_state __asm__(\"string_label\");";
int function(void) __asm__("function_label");
extern int other_function(int value) asm("other_label");
int third_function() __asm("third_label");
int expression_label __asm__(get_label());
int macro_label __asm__(LABEL);
int character_label __asm__('x');
int missing_label __asm__();
// static int comment_state asm("comment_label");
/*
static int block_comment_state __asm__("block_label");
*/
int Probe_Function() {
static int local_state __asm__("local_label");
return local_state;
}
'''
        self.assertEqual(declared_state_names({OLD: source}, {"globals": {"seeded": {}}}),
                         {"plain", "message", "seeded"})

    def test_assembler_label_preserves_recorded_direct_state_evidence(self):
        self.declarations = {"globals": {}}
        self.write(OLD, 'static int shared_state __asm__("linked_state");\n' + BODY)
        self.assertEqual(self.sources(), [])
        self.runtime["direct_state_references"] = []
        self.assert_error(self.sources(), "direct state reference evidence differs")

    def test_local_static_assembler_label_still_requires_storage_constraint(self):
        body = BODY.replace("return shared_state",
                            'static int lazy __asm__("local_storage"); return lazy + shared_state')
        self.update_body(self.runtime, body)
        self.assertNotIn("lazy", declared_state_names({OLD: body}))
        self.assert_error(self.sources(), "local-static storage constraint is missing")
        self.runtime["constraints"].append("preserve-local-static-storage")
        self.assertEqual(self.sources(), [])

    def test_missing_reason_or_unknown_constraints_metadata_is_rejected(self):
        for key, value, error in (("rationale", "too short", "concrete disposition rationale"),
                                  ("boundary_roles", ["inferred-from-folder"], "unknown boundary role"),
                                  ("constraints", [], "constraints must contain"),
                                  ("blockers", ["same", "same"], "blockers must contain"),
                                  ("direct_state_references", ["z", "a"], "sorted canonical identifier")):
            old = self.runtime[key]
            self.runtime[key] = value
            self.assert_error(self.metadata(), error)
            self.runtime[key] = old

    def test_malformed_documents_and_statuses_fail_without_exceptions(self):
        self.assertTrue(validate_inventory_metadata([]))
        for key, value in (("schema_version", 2), ("definitions", None), ("definition_count", 100),
                           ("origin_inventory_sha256", "bad")):
            old = self.document[key]
            self.document[key] = value
            self.assertTrue(self.metadata())
            self.document[key] = old
        for value in (None, {}, [], "bad"):
            old = self.runtime["migration"]
            self.runtime["migration"] = value
            self.assertTrue(self.metadata())
            self.runtime["migration"] = old

    def test_cli_reports_read_only_result_and_errors(self):
        data = self.root / "data"
        data.mkdir()
        for name, value in (("support_class_inventory.json", self.document), ("recovered_sources.json", self.manifest),
                             ("recovered_decls.json", self.declarations)):
            (data / name).write_text(json.dumps(value), encoding="utf-8")
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            result = main(["--root", str(self.root)])
        self.assertEqual(result, 0)
        payload = json.loads(output.getvalue())
        self.assertTrue(payload["ok"])
        self.assertFalse(payload["written"])
        self.write(OTHER, BOUNDARY + BOUNDARY)
        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(main(["--root", str(self.root)]), 1)


class ProductionSupportInventoryTest(unittest.TestCase):
    def test_complete_explicit_current_inventory_and_immutable_origins(self):
        document = json.loads((ROOT / "data/support_class_inventory.json").read_text())
        manifest = json.loads((ROOT / "data/recovered_sources.json").read_text())
        declarations = json.loads((ROOT / "data/recovered_decls.json").read_text())
        self.assertEqual(validate_inventory_sources(document, ROOT, manifest, declarations), [])
        self.assertEqual(document["origin_inventory_sha256"], "83c8871224429bd75d7d717f4a3d474e83d5900bb02ac69b353c9a474e81a498")
        summary = inventory_summary(document)
        self.assertEqual(summary["definitions"], 459)
        self.assertEqual(summary["surfaces"], {"translation-unit": 456, "header-inline": 3})
        self.assertEqual(summary["dispositions"], {"procedural-boundary": 305, "runtime-method": 154})
        self.assertEqual(summary["retained_diagnostic_definitions"], 39)
        records = {record["name"]: record for record in document["definitions"]}
        self.assertNotIn("Render_SetResourceHandle", records)
        for name in ("Compat_LoadFontPaletteTable", "Render_LoadResourceSprite_v3", "Render_LoadResourceSprite_v4"):
            self.assertEqual(records[name]["owner"], "GameText")
            self.assertEqual(records[name]["disposition"], "runtime-method")
        self.assertEqual(records["Unit_GetSquadCount"]["owner"], "UnitStack")
        self.assertEqual(records["IO_RemoveFileByPath"]["owner"], "CompatPathAndFind")
        self.assertTrue(records["CompatDirectDraw_Release"]["blockers"])
        self.assertTrue(records["CompatDirectDrawSurface_Unlock"]["blockers"])


if __name__ == "__main__":
    unittest.main()
