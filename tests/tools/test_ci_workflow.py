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
CLIPS_STEPS = (
    "Load unified recovered CLP in CLIPS",
    "Validate recompiled strategic AI RETE path depth",
    "Validate reset-time strategic AI agenda",
    "Validate strategic AI activation witnesses",
)
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
                "Install CLIPS runtime", "Check whitespace errors", *CLIPS_STEPS
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

    def test_clips_checks_have_their_additional_runtime_prerequisite(self):
        steps = steps_for("repo-checks")
        for name in CLIPS_STEPS:
            with self.subTest(step=name):
                self.assertEqual(field(steps[name], "if"),
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

    def test_native_evidence_keeps_both_compilers_and_failed_outcomes(self):
        text = WORKFLOW.read_text(encoding="utf-8").split("  unit-coverage:\n", 1)[1]
        self.assertIn("fail-fast: false", text)
        for setting in ("cxx: g++-13", "cxx: clang++-18", "gcov_command: gcov-13",
                        "gcov_command: llvm-cov-18 gcov"):
            self.assertIn(setting, text)
        steps = steps_for("unit-coverage")
        build_ready = "${{ !cancelled() && steps.unit-build.outcome == 'success' }}"
        run_finished = "${{ !cancelled() && (steps.unit-run.outcome == 'success' || steps.unit-run.outcome == 'failure') }}"
        for name in ("Capture native registry and provenance", "Run split unit suite"):
            self.assertEqual(field(steps[name], "if"), build_ready)
        for name in ("Reconcile individual native outcomes", "Enforce frozen coverage floor"):
            self.assertEqual(field(steps[name], "if"), run_finished)
        native = field(steps["Run split unit suite"], "run")
        self.assertIn("--no-tests=error", native)
        self.assertIn('pipeline_status=("${PIPESTATUS[@]}")', native)
        self.assertIn("test_status=${pipeline_status[0]}", native)
        self.assertIn('exit "$log_status"', native)
        self.assertIn('exit "$test_status"', native)
        reconcile = field(steps["Reconcile individual native outcomes"], "run")
        self.assertIn('--ctest-exit-code "$(cat native-ctest-exit.txt)"', reconcile)
        coverage = field(steps["Enforce frozen coverage floor"], "run")
        self.assertIn("--json coverage.json", coverage)
        self.assertIn("--gcov-command ${{ matrix.gcov_command }}", coverage)
        upload = steps["Upload native and coverage evidence"]
        self.assertIn("always()", field(upload, "if"))
        for path in ("native-evidence/", "native-revision.txt", "native-compiler-version.txt",
                     "native-reader-version.txt", "native-ctest.log", "native-ctest-exit.txt", "native-tee-exit.txt",
                     "coverage.json", "coverage.log", "build/coverage/Testing/Temporary/LastTest.log"):
            self.assertIn(path, upload)
        self.assertIn("${{ matrix.compiler_id }}-${{ github.sha }}", upload)

    @unittest.skipUnless(shutil.which("bash"), "bash is required for pipeline regression")
    def test_captured_diagnostics_preserve_real_exit_status(self):
        checks = (
            ("repo-checks", "Audit header surface and coupling ratchet", "audit_header_surface.py", "header-surface.log"),
            ("linux-build", "Check recovered warning ratchet", "check_recovered_warnings.py", "warning-ratchet.log"),
            ("linux-build", "Check linked symbol surface and data layout", "check_link_surface.py", "link-surface.log"),
            ("linux-build", "Run asset-free CTest gates", None, "asset-free-ctest.log"),
            ("unit-coverage", "Run split unit suite", None, "native-ctest.log"),
            ("unit-coverage", "Enforce frozen coverage floor", "measure_pure_coverage.py", "coverage.log"),
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
                    command = command.replace("${{ matrix.gcov_command }}", "gcov-13")
                    env = dict(os.environ, PATH=str(root) + os.pathsep + os.environ.get("PATH", ""))
                    result = subprocess.run(
                        ["bash", "--noprofile", "--norc", "-e", "-o", "pipefail", "-c", command],
                        cwd=root, env=env, capture_output=True, text=True, timeout=10,
                    )
                    self.assertEqual(result.returncode, exit_code, result.stdout + result.stderr)
                    self.assertIn("fixture diagnostic", (root / log).read_text(encoding="utf-8"))
                    if job == "unit-coverage" and tool is None:
                        self.assertEqual((root / "native-ctest-exit.txt").read_text().strip(), str(exit_code))
                        self.assertEqual((root / "native-tee-exit.txt").read_text().strip(), "0")

    @unittest.skipUnless(shutil.which("bash"), "bash is required for pipeline regression")
    def test_native_log_write_failure_does_not_hide_ctest_status(self):
        command = field(steps_for("unit-coverage")["Run split unit suite"], "run")
        for ctest_status in (0, 7):
            with self.subTest(ctest_status=ctest_status), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                for name, content in {
                    "ctest": f"#!/bin/sh\nprintf 'native diagnostic\\n'\nexit {ctest_status}\n",
                    "tee": '#!/bin/sh\ncat > "$1"\ncat "$1"\nexit 9\n',
                }.items():
                    path = root / name
                    path.write_text(content, encoding="utf-8")
                    path.chmod(0o755)
                env = dict(os.environ, PATH=str(root) + os.pathsep + os.environ.get("PATH", ""))
                result = subprocess.run(
                    ["bash", "--noprofile", "--norc", "-e", "-o", "pipefail", "-c", command],
                    cwd=root, env=env, capture_output=True, text=True, timeout=10)
                self.assertEqual(result.returncode, ctest_status or 9, result.stdout + result.stderr)
                self.assertEqual((root / "native-ctest-exit.txt").read_text().strip(), str(ctest_status))
                self.assertEqual((root / "native-tee-exit.txt").read_text().strip(), "9")
                self.assertIn("native diagnostic", (root / "native-ctest.log").read_text())


if __name__ == "__main__":
    unittest.main()
