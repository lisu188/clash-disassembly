"""Native evidence rejects partial or ambiguous runs without invoking compilers."""

import argparse
import contextlib
import importlib.util
import io
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location(
    "native_evidence", ROOT / "tools/collect_native_test_evidence.py")
evidence = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(evidence)
HEAD = "a" * 40


def last_test(output, binary="/tmp/native binary", result="Passed"):
    return (
        "Start testing: synthetic\n"
        "1/22 Testing: clash95_unit_tests\n"
        "1/22 Test: clash95_unit_tests\n"
        f'Command: "/usr/bin/bash" "/repo/tests/unit/run_split_coverage.sh" "{binary}" "/repo/build/coverage"\n'
        "Directory: /repo/build/coverage\n"
        "Output:\n----------------------------------------------------------\n"
        f"{output}\n<end of output>\nTest time = 0.01 sec\n"
        f"----------------------------------------------------------\nTest {result}.\n"
        "End testing: synthetic\n"
    )


class NativeEvidenceParserTests(unittest.TestCase):
    def test_registry_order_and_raw_details_survive_reconciliation(self):
        registry = {"count": 4, "names": ["z.pass", "a.fail", "b.crash", "c.error"]}
        raw = ("  CHECK failed: sentinels (fixture.cpp:3)\n"
               "CRASH b.crash: reported signal=11\n"
               "ERROR c.error: test isolation failed\n"
               "FAIL  a.fail\n== 1 passed, 2 failed, 1 crashed, 4 total ==\n")
        result = evidence.reconcile_output(registry, raw)
        self.assertEqual([r["name"] for r in result["cases"]], registry["names"])
        self.assertEqual([r["outcome"] for r in result["cases"]], ["PASS", "FAIL", "CRASH", "ERROR"])
        self.assertFalse(result["runner_policy_would_succeed"])
        self.assertEqual(result["cases"][2]["exception"]["reported_detail"], ": reported signal=11")
        self.assertEqual(result["unattributed_diagnostics"][0]["raw"], raw.splitlines()[0])

    def test_default_and_strict_crash_policy_remain_distinct(self):
        registry = {"count": 1, "names": ["a.crash"]}
        raw = "CRASH a.crash\n== 0 passed, 0 failed, 1 crashed, 1 total =="
        self.assertTrue(evidence.reconcile_output(registry, raw)["runner_policy_would_succeed"])
        self.assertFalse(evidence.reconcile_output(registry, raw, "strict")["runner_policy_would_succeed"])

    def test_malformed_or_ambiguous_registries_fail(self):
        for registry in (None, {}, {"count": True, "names": ["a.b"]},
                         {"count": 0, "names": []}, {"count": 2, "names": ["a.b"]},
                         {"count": 2, "names": ["a.b", "a.b"]},
                         {"count": 1, "names": [None]}, {"count": 1, "names": ["a.b extra"]}):
            with self.subTest(registry=registry), self.assertRaises(ValueError):
                evidence.registry_names(registry)

    def test_partial_duplicate_foreign_and_mismatched_runs_fail(self):
        summary = "== 1 passed, 0 failed, 1 crashed, 2 total =="
        registry = {"count": 2, "names": ["a.pass", "a.crash"]}
        invalid = {
            "no summary": "CRASH a.crash",
            "partial summary": "CRASH a.crash\n== 1 passed, 0 failed",
            "two summaries": f"CRASH a.crash\n{summary}\n{summary}",
            "duplicate crash": f"CRASH a.crash\nCRASH a.crash\n{summary}",
            "conflicting exception": f"CRASH a.crash\nFAIL  a.crash\n{summary}",
            "foreign crash": f"CRASH another.case\n{summary}",
            "missing crash": summary,
            "bad name": f"CRASH a.crash!\n{summary}",
            "malformed status": f"FAIL a.crash\n{summary}",
            "smaller total": "== 1 passed, 0 failed, 0 crashed, 1 total ==",
            "inconsistent sum": "CRASH a.crash\n== 2 passed, 0 failed, 1 crashed, 2 total ==",
            "late exception": f"{summary}\nCRASH a.crash",
        }
        for label, raw in invalid.items():
            with self.subTest(label=label), self.assertRaises(ValueError):
                evidence.reconcile_output(registry, raw)

    def test_ctest_requires_complete_unique_native_record_and_binary(self):
        complete = last_test("== 1 passed, 0 failed, 0 crashed, 1 total ==")
        output, result, command = evidence.ctest_output(complete, "/tmp/native binary")
        self.assertIn("== 1 passed", output)
        self.assertEqual(result, "Passed")
        self.assertIn("/tmp/native binary", command)
        for broken in (complete + complete, complete.replace("<end of output>", ""),
                       complete.replace("Test Passed.", ""),
                       complete.replace("/tmp/native binary", "/tmp/other binary"),
                       complete.replace("clash95_unit_tests", "unrelated_test")):
            with self.subTest(log=broken), self.assertRaises(ValueError):
                evidence.ctest_output(broken, "/tmp/native binary")


class NativeEvidenceCollectionTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="native-evidence-test-")
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.binary = self.root / "native binary"
        self.binary.write_bytes(b"synthetic nonexecutable fixture")
        self.directory = self.root / "evidence"
        self.head = mock.patch.object(evidence, "git_head", return_value=HEAD)
        self.head.start()
        self.addCleanup(self.head.stop)
        self.output = contextlib.redirect_stdout(io.StringIO())
        self.output.__enter__()
        self.addCleanup(self.output.__exit__, None, None, None)

    def seed_capture(self):
        self.directory.mkdir()
        evidence.write_json(self.directory / "registry.json", {"count": 1, "names": ["one.case"]})
        capture = {"complete": True, "root": str(self.root), "binary": str(self.binary),
                   "collection_started_unix_ns": 0,
                   "git_head": HEAD, "binary_sha256": evidence.sha256(self.binary),
                   "registry_sha256": evidence.sha256(self.directory / "registry.json")}
        evidence.write_json(self.directory / "capture.json", capture)

    def reconcile(self, raw, exit_code=0):
        log = self.root / "source LastTest.log"
        log.write_bytes(raw)
        return evidence.reconcile_run(argparse.Namespace(
            evidence=self.directory, log=log, ctest_exit_code=exit_code, mode="default"))

    def test_complete_failing_run_is_successful_collection_not_native_pass(self):
        self.seed_capture()
        raw = last_test("FAIL  one.case\n== 0 passed, 1 failed, 0 crashed, 1 total ==",
                        str(self.binary), "Failed").encode()
        self.assertEqual(self.reconcile(raw, 8), 0)
        result = json.loads((self.directory / "cases.json").read_text())
        self.assertFalse(result["runner_policy_would_succeed"])
        self.assertEqual(result["ctest_exit_code"], 8)
        self.assertEqual(result["git_head"], HEAD)
        self.assertEqual(result["binary_sha256"], evidence.sha256(self.binary))
        self.assertEqual((self.directory / "LastTest.log").read_bytes(), raw)

    def test_incomplete_log_is_copied_byte_exact_before_failure(self):
        self.seed_capture()
        raw = b"CRASH one.case\r\npartial invalid utf8: \xff\n"
        self.assertEqual(self.reconcile(raw, 8), 1)
        self.assertEqual((self.directory / "LastTest.log").read_bytes(), raw)
        receipt = json.loads((self.directory / "reconciliation.json").read_text())
        self.assertFalse(receipt["complete"])
        self.assertIn("ValueError", receipt["error"])
        self.assertFalse((self.directory / "cases.json").exists())

    def test_binary_change_is_rejected_with_raw_log_preserved(self):
        self.seed_capture()
        self.binary.write_bytes(b"changed")
        raw = last_test("== 1 passed, 0 failed, 0 crashed, 1 total ==", str(self.binary)).encode()
        self.assertEqual(self.reconcile(raw), 1)
        self.assertEqual((self.directory / "LastTest.log").read_bytes(), raw)
        self.assertIn("differs from registry", (self.directory / "reconciliation.json").read_text())

    def test_registry_tampering_is_rejected(self):
        self.seed_capture()
        (self.directory / "registry.json").write_text('{"count":1,"names":["other.case"]}')
        raw = last_test("== 1 passed, 0 failed, 0 crashed, 1 total ==", str(self.binary)).encode()
        self.assertEqual(self.reconcile(raw), 1)
        self.assertIn("registry bytes changed", (self.directory / "reconciliation.json").read_text())

    def test_git_head_change_is_rejected(self):
        self.seed_capture()
        raw = last_test("== 1 passed, 0 failed, 0 crashed, 1 total ==", str(self.binary)).encode()
        with mock.patch.object(evidence, "git_head", return_value="b" * 40):
            self.assertEqual(self.reconcile(raw), 1)
        self.assertIn("differs from registry", (self.directory / "reconciliation.json").read_text())

    def test_stale_ctest_log_is_preserved_and_rejected(self):
        self.seed_capture()
        capture_path = self.directory / "capture.json"
        capture = json.loads(capture_path.read_text())
        capture["collection_started_unix_ns"] = 2_000_000_000
        capture_path.write_text(json.dumps(capture))
        source = self.root / "old LastTest.log"
        raw = last_test("== 1 passed, 0 failed, 0 crashed, 1 total ==", str(self.binary)).encode()
        source.write_bytes(raw)
        os.utime(source, ns=(1_000_000_000, 1_000_000_000))
        self.assertEqual(evidence.reconcile_run(argparse.Namespace(
            evidence=self.directory, log=source, ctest_exit_code=0, mode="default")), 1)
        self.assertEqual((self.directory / "LastTest.log").read_bytes(), raw)
        self.assertIn("predates registry capture", (self.directory / "reconciliation.json").read_text())

    def test_ctest_exit_contradiction_is_rejected(self):
        self.seed_capture()
        raw = last_test("FAIL  one.case\n== 0 passed, 1 failed, 0 crashed, 1 total ==",
                        str(self.binary), "Failed").encode()
        self.assertEqual(self.reconcile(raw, 0), 1)
        self.assertIn("exit zero contradicts", (self.directory / "reconciliation.json").read_text())

    def test_existing_failed_attempt_is_never_overwritten(self):
        self.seed_capture()
        self.assertEqual(self.reconcile(b"incomplete", 8), 1)
        before = {p.name: p.read_bytes() for p in self.directory.iterdir()}
        with self.assertRaises(ValueError):
            self.reconcile(b"replacement", 8)
        self.assertEqual(before, {p.name: p.read_bytes() for p in self.directory.iterdir()})

    def capture_args(self):
        return argparse.Namespace(output=self.directory, root=self.root, binary=self.binary,
                                  gdb="gdb-fixture", timeout=5)

    def test_capture_pins_registry_order_and_binary_without_running_tests(self):
        def gdb(command, **kwargs):
            script = Path(command[4]).read_text()
            self.assertIn("break main\nrun --help", script)
            self.assertNotIn("continue\n", script)
            evidence.write_json(Path(kwargs["env"]["CLASH95_REF_REGISTRY"]),
                                {"count": 2, "names": ["z.first", "a.second"]})
            return subprocess.CompletedProcess(command, 0, b"capture output\n", b"")
        with mock.patch.object(evidence.subprocess, "run", side_effect=gdb):
            self.assertEqual(evidence.capture_registry(self.capture_args()), 0)
        capture = json.loads((self.directory / "capture.json").read_text())
        self.assertTrue(capture["complete"])
        self.assertEqual(capture["git_head"], HEAD)
        self.assertEqual(capture["binary_sha256"], evidence.sha256(self.binary))
        self.assertEqual(json.loads((self.directory / "registry.json").read_text())["names"],
                         ["z.first", "a.second"])

    def test_capture_failure_retains_gdb_stdout_and_stderr(self):
        failure = subprocess.CompletedProcess([], 1, b"partial capture\n", b"failure detail\n")
        with mock.patch.object(evidence.subprocess, "run", return_value=failure):
            self.assertEqual(evidence.capture_registry(self.capture_args()), 1)
        self.assertEqual((self.directory / "registry.stdout.log").read_bytes(), failure.stdout)
        self.assertEqual((self.directory / "registry.stderr.log").read_bytes(), failure.stderr)
        self.assertFalse(json.loads((self.directory / "capture.json").read_text())["complete"])

    def test_capture_timeout_retains_partial_output(self):
        failure = subprocess.TimeoutExpired("gdb", 5, output=b"partial", stderr=b"details")
        with mock.patch.object(evidence.subprocess, "run", side_effect=failure):
            self.assertEqual(evidence.capture_registry(self.capture_args()), 1)
        self.assertEqual((self.directory / "registry.stdout.log").read_bytes(), b"partial")
        self.assertIn("TimeoutExpired", (self.directory / "capture.json").read_text())


if __name__ == "__main__":
    unittest.main()
