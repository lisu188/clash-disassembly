"""Guard the source-derived Clang storage order without relaxing layout pins."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "tools"))
from gen_subsystem_headers import TENTATIVE_BEGIN, TENTATIVE_END, refresh_tentative_state


class TentativeStateTests(unittest.TestCase):
    def test_order_and_declarators_are_retained(self):
        prefix = "CLASH95_TENTATIVE int z[1];\nCLASH95_TENTATIVE void (*a)(int);\n"
        source = prefix + TENTATIVE_BEGIN + "\nold\n" + TENTATIVE_END + "\n"
        result = refresh_tentative_state(source)
        self.assertIn("int z[1];\nvoid (*a)(int);", result)
        self.assertEqual(refresh_tentative_state(result), result)
        self.assertTrue(result.startswith(prefix))

    def test_missing_marker_rejected(self):
        with self.assertRaisesRegex(ValueError, "exactly one"):
            refresh_tentative_state("CLASH95_TENTATIVE int z;\n")

    def test_duplicate_declaration_rejected(self):
        with self.assertRaisesRegex(ValueError, "duplicate"):
            refresh_tentative_state("CLASH95_TENTATIVE int z;\n" * 2
                                    + TENTATIVE_BEGIN + "\n" + TENTATIVE_END)

    def test_initialized_storage_rejected(self):
        with self.assertRaisesRegex(ValueError, "initialized"):
            refresh_tentative_state("CLASH95_TENTATIVE int z = 0;\n"
                                    + TENTATIVE_BEGIN + "\n" + TENTATIVE_END)
