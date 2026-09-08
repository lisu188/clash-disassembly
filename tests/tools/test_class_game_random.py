#!/usr/bin/env python3
"""Actual GameRandom extraction, retained bindings and composed UnitTurn parity."""
from pathlib import Path
import json
import os
import platform
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(os.environ.get("CLASH95_SOURCE_ROOT", Path(__file__).resolve().parents[2])).resolve()
FIXTURE = Path(__file__).parent / "fixtures/class_game_random"

class GameRandomClassTests(unittest.TestCase):
    def test_actual_methods_adapters_factory_and_unit_turn_match_repaired_reference(self):
        if platform.system() != "Linux" or platform.machine() not in ("x86_64", "amd64"):
            self.skipTest("requires Linux x86-64 for the low32 composed UnitTurn fixture")
        evidence = os.environ.get("CLASH95_CLASS_GAME_RANDOM_EVIDENCE")
        with tempfile.TemporaryDirectory(prefix="clash95-class-game-random-") as temporary:
            output = Path(evidence).resolve() if evidence else Path(temporary) / "results"
            result = subprocess.run([sys.executable, str(FIXTURE / "verify_game_random.py"),
                                     "--root", str(ROOT), "--output", str(output)],
                                    capture_output=True, text=True, timeout=240)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            summary = json.loads((output / "summary.json").read_text())
            self.assertTrue(summary["inputs_unchanged"])
            self.assertEqual(len(summary["profiles"]), 4)
            for profile in summary["profiles"]:
                self.assertEqual(profile.get("run"), 0)
                self.assertIn("PASS cases=69737 ", profile["stdout"])
                self.assertIn("direct,borrow,adapter returns=exact full_bytes=exact callbacks=exact", profile["stdout"])

if __name__ == "__main__":
    unittest.main()
