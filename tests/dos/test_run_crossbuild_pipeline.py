import json
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

    def write_review_artifacts(self, paths, proposal=None, review=None):
        paths.crossbuild_dir.mkdir(parents=True, exist_ok=True)
        (paths.crossbuild_dir / "dos_crossbuild_calibration.json").write_text(json.dumps({
            "summary": {"complete": True, "passed": True}
        }), encoding="utf-8")
        (paths.crossbuild_dir / "dos_crossbuild_confirmed.json").write_text(json.dumps({
            "calibration_passed": True,
            "rows": [],
        }), encoding="utf-8")
        proposals = [proposal] if proposal else []
        reviews = [review] if review else []
        (paths.crossbuild_dir / "dos_crossbuild_proposals.json").write_text(json.dumps({
            "candidate_count": len(proposals),
            "candidates": proposals,
        }), encoding="utf-8")
        (paths.crossbuild_dir / "dos_crossbuild_review.json").write_text(json.dumps({
            "candidate_reviews": reviews,
        }), encoding="utf-8")

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

    def test_review_gate_rejects_missing_game_verdict(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            proposal = {"dos_ea": "0x20000", "clash95_ea": "0x400000"}
            review = {
                "dos_ea": "0x20000",
                "clash95_ea": "0x400000",
                "verdict": "PENDING",
                "review_reason": "",
            }
            self.write_review_artifacts(paths, proposal, review)
            with self.assertRaisesRegex(RuntimeError, "verdict and concrete review reason"):
                runner.require_review_gate(paths, Path(directory) / "reviews.json")

    def test_review_gate_accepts_explicit_rejection(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            proposal = {"dos_ea": "0x20000", "clash95_ea": "0x400000"}
            review = {
                "dos_ea": "0x20000",
                "clash95_ea": "0x400000",
                "verdict": "REJECT",
                "review_reason": "control-flow shape is incompatible",
                "evidence_complete": False,
            }
            self.write_review_artifacts(paths, proposal, review)
            runner.require_review_gate(paths, Path(directory) / "reviews.json")

    def test_review_gate_rejects_incomplete_confirmation(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            proposal = {"dos_ea": "0x20000", "clash95_ea": "0x400000"}
            review = {
                "dos_ea": "0x20000",
                "clash95_ea": "0x400000",
                "verdict": "CONFIRM",
                "review_reason": "literal matches",
                "evidence_complete": False,
            }
            self.write_review_artifacts(paths, proposal, review)
            with self.assertRaisesRegex(RuntimeError, "complete structural evidence"):
                runner.require_review_gate(paths, Path(directory) / "reviews.json")

    def test_original_database_hash_change_is_detected(self):
        with tempfile.TemporaryDirectory() as directory:
            paths = self.make_paths(directory)
            paths.dos_source.parent.mkdir(parents=True)
            paths.clash95_source.parent.mkdir(parents=True, exist_ok=True)
            paths.dos_source.write_bytes(b"dos")
            paths.clash95_source.write_bytes(b"clash95")
            hashes = runner.snapshot_originals(paths)
            paths.dos_source.write_bytes(b"changed")
            with self.assertRaisesRegex(RuntimeError, "original IDA database changed"):
                runner.verify_originals_unchanged(paths, hashes)


if __name__ == "__main__":
    unittest.main()
