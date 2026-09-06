from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile
import textwrap
import unittest


ROOT = Path(__file__).resolve().parents[2]
WORKFLOW = ROOT / ".github/workflows/ci.yml"
REPO_READY = "${{ !cancelled() && steps.checkout.outcome == 'success' && steps.python.outcome == 'success' }}"
BUILD_READY = "${{ !cancelled() && steps.build.outcome == 'success' }}"


def steps_for(job):
    text = WORKFLOW.read_text(encoding="utf-8")
    body = text.split(f"  {job}:\n", 1)[1]
    body = re.split(r"\n  [a-z][a-z-]*:\n", body, maxsplit=1)[0]
    return dict(block.split("\n", 1) for block in body.split("      - name: ")[1:])


def field(step, name):
    match = re.search(rf"^        {re.escape(name)}: (.*)$", step, re.MULTILINE)
    if match is None:
        return None
    if match.group(1) != "|":
        return match.group(1)
    lines = []
    for line in step[match.end():].splitlines()[1:]:
        if line and not line.startswith("          "):
            break
        lines.append(line)
    return textwrap.dedent("\n".join(lines)).strip()


class CIWorkflowTests(unittest.TestCase):
    def test_native_guards_and_ctest_are_independent_after_build(self):
        steps = steps_for("linux-build")
        for name in ("Check recovered warning ratchet", "Check linked symbol surface and data layout",
                     "Run asset-free CTest gates"):
            with self.subTest(step=name):
                self.assertEqual(field(steps[name], "if"), BUILD_READY)

    def test_repo_checks_only_require_their_inputs(self):
        for name, step in steps_for("repo-checks").items():
            if field(step, "run") is None or name in (
                "Install CLIPS runtime", "Load unified recovered CLP in CLIPS", "Check whitespace errors"
            ):
                continue
            with self.subTest(step=name):
                self.assertEqual(field(step, "if"), REPO_READY)
        steps = steps_for("repo-checks")
        self.assertEqual(field(steps["Check out repository"], "id"), "checkout")
        self.assertEqual(field(steps["Set up Python"], "id"), "python")
        self.assertEqual(field(steps["Install CLIPS runtime"], "id"), "clips")
        self.assertEqual(field(steps["Check whitespace errors"], "if"),
                         "${{ !cancelled() && steps.checkout.outcome == 'success' }}")

    def test_clips_load_has_its_additional_runtime_prerequisite(self):
        step = steps_for("repo-checks")["Load unified recovered CLP in CLIPS"]
        self.assertEqual(field(step, "if"),
                         REPO_READY[:-3] + " && steps.clips.outcome == 'success' }}")

    def test_inventory_validation_and_upload_follow_generation(self):
        steps = steps_for("repo-checks")
        self.assertEqual(field(steps["Inventory unresolved strategic AI matcher tests"], "id"),
                         "matcher-inventory")
        self.assertIn("-m json.tool clash_dat_unresolved_inventory.json",
                      field(steps["Inventory unresolved strategic AI matcher tests"], "run"))
        self.assertNotIn("clash_dat_unresolved_inventory.json", field(steps["Validate JSON files"], "run"))
        self.assertEqual(field(steps["Upload unresolved matcher inventory"], "if"),
                         "${{ always() && steps.matcher-inventory.outcome == 'success' }}")

    def test_ctest_keeps_all_four_gates_and_rejects_empty_selection(self):
        command = field(steps_for("linux-build")["Run asset-free CTest gates"], "run")
        self.assertIn("-R '^(clash95_split_source_audit|clash95_pure_metadata_audit|"
                      "clash95_save_format_contract|runtime_mission_trace_tests)$'", command)
        self.assertIn("--no-tests=error", command)
        self.assertIn("--output-on-failure", command)

    def test_runner_contracts_run_for_each_requested_compiler(self):
        steps = steps_for("linux-build")
        step = steps["Test unit runner failure policy"]
        self.assertEqual(field(steps["Install build dependencies"], "id"), "dependencies")
        self.assertEqual(field(step, "if"),
                         "${{ !cancelled() && steps.dependencies.outcome == 'success' }}")
        self.assertIn("CLASH95_RUNNER_TEST_CXX: ${{ matrix.cxx }}", step)
        self.assertIn("test_unit_runner.py", field(step, "run"))

    def test_diagnostic_upload_is_not_blocked_by_failed_checks(self):
        step = steps_for("linux-build")["Upload compiler diagnostics"]
        self.assertEqual(field(step, "if"),
                         "${{ always() && (steps.build.outcome == 'success' || steps.build.outcome == 'failure') }}")
        for path in ("compiler.log", "warning-ratchet.log", "link-surface.log",
                     "asset-free-ctest.log", "build/Testing/Temporary/LastTest.log"):
            self.assertIn(path, step)
        step = steps_for("repo-checks")["Upload header-surface diagnostics"]
        self.assertIn("always()", field(step, "if"))
        self.assertIn("header-surface.log", step)

    def test_required_failures_and_frozen_thresholds_are_not_suppressed(self):
        text = WORKFLOW.read_text(encoding="utf-8")
        self.assertNotIn("continue-on-error", text)
        self.assertNotIn("--mode report", text)
        self.assertNotIn("--mode snapshot", text)
        self.assertIn("--minimum 89.7 --require-functions 718 --require-zero-uncovered", text)
        self.assertIn("cxx: g++-13", text)
        self.assertIn("cxx: clang++-18", text)
        self.assertEqual(text.count("warning_mode: check"), 2)

    @unittest.skipUnless(shutil.which("bash"), "bash is required for pipeline regression")
    def test_captured_diagnostics_preserve_real_exit_status(self):
        checks = (
            ("repo-checks", "Audit header surface and coupling ratchet", "audit_header_surface.py", "header-surface.log"),
            ("linux-build", "Check recovered warning ratchet", "check_recovered_warnings.py", "warning-ratchet.log"),
            ("linux-build", "Check linked symbol surface and data layout", "check_link_surface.py", "link-surface.log"),
            ("linux-build", "Run asset-free CTest gates", None, "asset-free-ctest.log"),
        )
        for job, name, tool, log in checks:
            for exit_code in (0, 7):
                with self.subTest(step=name, exit_code=exit_code), tempfile.TemporaryDirectory() as directory:
                    root = Path(directory)
                    (root / "tools").mkdir()
                    if tool:
                        (root / "tools" / tool).write_text(
                            f"import sys\nprint('fixture diagnostic')\nsys.exit({exit_code})\n", encoding="utf-8")
                    else:
                        fake_ctest = root / "ctest"
                        fake_ctest.write_text(
                            f"#!/bin/sh\nprintf 'fixture diagnostic\\n'\nexit {exit_code}\n", encoding="utf-8")
                        fake_ctest.chmod(0o755)
                    command = field(steps_for(job)[name], "run")
                    command = command.replace("${{ matrix.compiler_id }}", "gcc")
                    command = command.replace("${{ matrix.warning_mode }}", "check")
                    env = dict(os.environ, PATH=str(root) + os.pathsep + os.environ.get("PATH", ""))
                    result = subprocess.run(
                        ["bash", "--noprofile", "--norc", "-e", "-o", "pipefail", "-c", command],
                        cwd=root, env=env, capture_output=True, text=True, timeout=10,
                    )
                    self.assertEqual(result.returncode, exit_code, result.stdout + result.stderr)
                    self.assertIn("fixture diagnostic", (root / log).read_text(encoding="utf-8"))


if __name__ == "__main__":
    unittest.main()
