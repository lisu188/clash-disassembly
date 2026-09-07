#!/usr/bin/env python3

from pathlib import Path
import sys
import tempfile
import unittest

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO / "tools"))

import audit_cpp_class_candidates as audit


class CppClassCandidateAuditTests(unittest.TestCase):
    def test_class_evidence_scores_vtable_lifecycle_and_thiscall(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "media" / "candidate.cpp"
            source.parent.mkdir(parents=True)
            source.write_text(
                "int g_CAviDecompressor_Vtable;\n"
                "int __thiscall CAviDecompressor_Frames(void *self) { return 0; }\n"
                "int CAviDecompressor_ConstructEmpty(void) { return 0; }\n"
                "int CAviDecompressor_dtor(void) { return 0; }\n",
                encoding="utf-8",
            )
            candidates = audit.collect_candidates(root)
            candidate = next(item for item in candidates
                             if item["family"] == "CAviDecompressor")
            self.assertGreaterEqual(candidate["vtable_mentions"], 1)
            self.assertGreaterEqual(candidate["constructor_mentions"], 1)
            self.assertGreaterEqual(candidate["destructor_mentions"], 1)
            self.assertGreaterEqual(candidate["thiscall_mentions"], 1)
            self.assertGreater(candidate["score"], candidate["symbol_count"])

    def test_plain_function_family_without_class_signals_is_omitted(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "units" / "plain.cpp"
            source.parent.mkdir(parents=True)
            source.write_text(
                "int Unit_Move(void) { return 0; }\n"
                "int Unit_Stop(void) { return 0; }\n",
                encoding="utf-8",
            )
            families = {item["family"] for item in audit.collect_candidates(root)}
            self.assertNotIn("Unit", families)

    def test_array_runtime_signal_is_bound_to_named_family_on_same_line(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source = root / "src" / "core" / "array.cpp"
            source.parent.mkdir(parents=True)
            source.write_text(
                "int PathEntryArray_Construct(void *self) { "
                "return _wcpp_4_ctor_array__(self, 256); }\n",
                encoding="utf-8",
            )
            candidate = next(item for item in audit.collect_candidates(root)
                             if item["family"] == "PathEntryArray")
            self.assertGreaterEqual(candidate["array_runtime_mentions"], 1)


if __name__ == "__main__":
    unittest.main()
