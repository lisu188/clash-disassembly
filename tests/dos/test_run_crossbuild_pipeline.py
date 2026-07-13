import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "dos"))

import run_crossbuild_pipeline as runner


class CrossBuildPipelineRunnerTests(unittest.TestCase):
    def make_paths(self, root):
        root = Path(root)
        return runner.PipelinePaths(
            repo=ROOT,
            work=root / "work",
            dos_source=root / "original" / "clash.i64",
            clash95_source=root / "original" / "clash95.i64",
            ida=root / "ida" / "idat.exe",
        )

    def test_work_directory_inside_repository_is_rejected(self):
        paths = runner.PipelinePaths(
            repo=ROOT,
            work=ROOT / "generated-work",
            dos_source=Path("/original/clash.i64"),
            clash95_source=Path("/original/clash95.i64"),
            ida=Path("/ida/idat.exe"),
        )
        with self.assertRaisesRegex(ValueError, "outside the repository"):
            runner.validate_layout(paths, dry_run=True)

    def test_ida_commands_only_open_temporary_database_copies(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            commands = runner.build_commands(paths, "python", regenerate=True, reviews=Path(directory) / "reviews.json")
        command_by_name = dict(commands)
        self.assertEqual(command_by_name["export-dos-features"][-1], str(paths.dos_feature_db))
        self.assertEqual(command_by_name["export-clash95-features"][-1], str(paths.clash95_feature_db))
        self.assertEqual(command_by_name["seed-regeneration-database"][-1], str(paths.regen_db))
        self.assertEqual(command_by_name["export-regenerated-clash-c"][-1], str(paths.regen_db))
        for _, command in commands:
            self.assertNotIn(str(paths.dos_source), command)
            self.assertNotIn(str(paths.clash95_source), command)

    def test_unreviewed_plan_does_not_pass_reviews_to_matcher(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            command = runner.matcher_command(paths, "python")
        self.assertNotIn("--reviews", command)

    def test_reviewed_plan_passes_exact_review_file(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            reviews = Path(directory) / "reviews.json"
            command = runner.matcher_command(paths, "python", reviews)
        review_index = command.index("--reviews")
        self.assertEqual(command[review_index + 1], str(reviews))

    def test_regeneration_requires_reviews(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(ValueError, "requires --reviews"):
                runner.main([
                    "--repo",
                    str(ROOT),
                    "--work-dir",
                    str(Path(directory) / "work"),
                    "--regenerate",
                    "--dry-run",
                ])

    def test_candidate_map_is_built_outside_repository(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            command = runner.map_command(paths, "python")
        output_index = command.index("--output")
        self.assertEqual(command[output_index + 1], str(paths.candidate_map))
        self.assertFalse(runner.is_relative_to(paths.candidate_map, paths.repo))

    def test_ida_script_argument_keeps_script_and_arguments_together(self):
        value = runner.ida_script_arg(Path("C:/Program Files/test.py"), [Path("C:/work/output.json")])
        self.assertTrue(value.startswith("-S"))
        self.assertIn("test.py", value)
        self.assertIn("output.json", value)


if __name__ == "__main__":
    unittest.main()
