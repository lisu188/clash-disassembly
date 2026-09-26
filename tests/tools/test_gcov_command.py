"""Exercise reader selection without compiling or running recovered code."""

from __future__ import annotations

import contextlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import coverage_source_manifest as coverage
import measure_pure_coverage as measure


class GcovCommandTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.sources = {"src/units/UnitStack.cpp", "src/units/UnitSlot.cpp"}

    def build(self, sharded):
        build = self.root / ("sharded" if sharded else "single")
        relative = Path("CMakeFiles/clash95_recovered_coverage_objects.dir/src/units")
        for source in sorted(self.sources):
            note = build / relative / (Path(source).name + ".gcno")
            note.parent.mkdir(parents=True, exist_ok=True)
            note.write_text(source)
            if sharded:
                for worker, hits in enumerate(([True, False], [False, True])):
                    data = (build / "coverage-shards" / f"worker-{worker}"
                            / relative / note.with_suffix(".gcda").name)
                    data.parent.mkdir(parents=True, exist_ok=True)
                    data.write_text(json.dumps(hits))
            else:
                note.with_suffix(".gcda").write_text(json.dumps([True, False]))
        return build

    def reader(self, text=None):
        # A space in this script's path also detects accidental shell splitting.
        script = self.root / "reader stub.py"
        script.write_text(text if text is not None else '''\
import json
from pathlib import Path
import sys

assert sys.argv[1:5] == ["gcov", "-p", "-l", "-o"], sys.argv
notes = Path(sys.argv[5])
for name in sys.argv[6:]:
    note = notes / name
    source = note.read_text()
    hits = json.loads(note.with_suffix(".gcda").read_text())
    lines = [f"        -:    0:Source:{source}\\n"]
    for line, covered in enumerate(hits, 5):
        count = "1" if covered else "#####"
        lines.append(f"{count}: {line}: recovered statement\\n")
    Path(name + ".gcov").write_text("".join(lines))
''')
        return [sys.executable, str(script), "gcov"]

    def test_multitoken_reader_preserves_source_resolution_and_shard_union(self):
        command = self.reader()
        for sharded in (False, True):
            with self.subTest(sharded=sharded):
                actual = coverage.collect_split_gcov(
                    self.build(sharded), self.sources, gcov_command=command)
                self.assertEqual(actual, {
                    source: {5: True, 6: sharded} for source in self.sources})

    def test_default_reader_keeps_existing_arguments_and_options(self):
        for sharded in (False, True):
            with self.subTest(sharded=sharded):
                build = self.build(sharded)

                def reader_stub(command, **options):
                    self.assertEqual(command[:4], ["gcov", "-p", "-l", "-o"])
                    self.assertEqual(set(options), {"cwd", "stdout", "stderr", "text"})
                    self.assertEqual(options["stdout"], subprocess.PIPE)
                    self.assertEqual(options["stderr"], subprocess.PIPE)
                    self.assertIs(options["text"], True)
                    notes = Path(command[4])
                    if not sharded:
                        self.assertTrue(notes.is_relative_to(build))
                    for name in command[5:]:
                        note = notes / name
                        self.assertTrue(note.with_suffix(".gcda").is_file())
                        (options["cwd"] / (name + ".gcov")).write_text(
                            f"-:0:Source:{note.read_text()}\n1:5:statement\n")
                    return subprocess.CompletedProcess(command, 0, "", "")

                with mock.patch.object(coverage.subprocess, "run", side_effect=reader_stub) as run:
                    self.assertEqual(coverage.collect_split_gcov(build, self.sources),
                                     {source: {5: True} for source in self.sources})
                self.assertEqual(run.call_count, 2)

    def test_nonzero_multitoken_reader_is_fatal_in_both_modes(self):
        command = self.reader('import sys\nsys.stderr.write("wrong profile format")\n'
                              'raise SystemExit(7)\n')
        for sharded in (False, True):
            with self.subTest(sharded=sharded):
                with self.assertRaisesRegex(coverage.CoverageMetadataError,
                                            "failed for .*wrong profile format") as caught:
                    coverage.collect_split_gcov(
                        self.build(sharded), self.sources, gcov_command=command)
                self.assertIn(" ".join(command), str(caught.exception))

    def test_missing_reader_is_fatal_in_both_modes(self):
        command = [str(self.root / "missing reader"), "gcov"]
        for sharded in (False, True):
            with self.subTest(sharded=sharded):
                with self.assertRaises(coverage.CoverageMetadataError) as caught:
                    coverage.collect_split_gcov(
                        self.build(sharded), self.sources, gcov_command=command)
                self.assertEqual(str(caught.exception),
                                 " ".join(command) + " is required to measure coverage")

    def test_successful_reader_without_source_output_is_rejected(self):
        command = self.reader("raise SystemExit(0)\n")
        for sharded in (False, True):
            with self.subTest(sharded=sharded):
                with self.assertRaisesRegex(coverage.CoverageMetadataError,
                                            "gcov did not emit recovered"):
                    coverage.collect_split_gcov(
                        self.build(sharded), self.sources, gcov_command=command)

    def test_invalid_command_is_rejected_before_collecting_profiles(self):
        for command in ([], "gcov", [""], ["gcov", 1]):
            with self.subTest(command=command):
                with self.assertRaisesRegex(coverage.CoverageMetadataError,
                                            "nonempty argument sequence"):
                    coverage.collect_split_gcov(self.root, self.sources,
                                                gcov_command=command)


class GcovCommandCliTests(unittest.TestCase):
    def arguments(self, *arguments):
        with mock.patch.object(sys, "argv", ["measure_pure_coverage.py", "build", *arguments]):
            return measure.parse_args()

    def test_default_and_multiple_command_arguments(self):
        self.assertEqual(self.arguments().gcov_command, ["gcov"])
        args = self.arguments("--minimum", "89.7", "--require-functions", "718",
                              "--require-zero-uncovered", "--gcov-command", "llvm-cov-18", "gcov")
        self.assertEqual(args.gcov_command, ["llvm-cov-18", "gcov"])
        self.assertEqual(args.minimum, 89.7)
        self.assertEqual(args.require_functions, 718)
        self.assertTrue(args.require_zero_uncovered)

    def test_empty_command_is_a_cli_error(self):
        with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as caught:
            self.arguments("--gcov-command")
        self.assertEqual(caught.exception.code, 2)

    def test_main_forwards_reader_without_weakening_denominator_gate(self):
        args = self.arguments("--require-functions", "718", "--gcov-command", "llvm-cov-18", "gcov")
        source = "src/units/UnitStack.cpp"
        functions = [{"name": "UnitStack_HasReadyUnits", "source": source}]
        with mock.patch.object(measure, "parse_args", return_value=args), \
             mock.patch.object(measure, "load_pure_set", return_value=({}, functions)), \
             mock.patch.object(measure, "split_ranges", return_value={functions[0]["name"]: (source, 5, 7)}), \
             mock.patch.object(measure, "collect_split_gcov", return_value={source: {5: True}}) as collect, \
             contextlib.redirect_stdout(io.StringIO()) as output:
            self.assertEqual(measure.main(), 1)
        collect.assert_called_once_with(args.build_dir.resolve(), {source},
                                        gcov_command=["llvm-cov-18", "gcov"])
        self.assertIn("function denominator 1 is not required 718", output.getvalue())


if __name__ == "__main__":
    unittest.main()
