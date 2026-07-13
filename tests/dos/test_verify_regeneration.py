import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "dos"))

import verify_regeneration as verifier


class VerifyRegenerationTests(unittest.TestCase):
    def test_marker_parser_is_order_sensitive(self):
        text = '''//----- (00000010) --------------------------------------------------------
int sub_10(void) { return 0; }
//----- (00000020) --------------------------------------------------------
int sub_20(void) { return 0; }
'''
        self.assertEqual(verifier.marker_addresses(text), [0x10, 0x20])

    def test_function_error_is_associated_with_marker(self):
        text = '''//----- (000FDF26) --------------------------------------------------------
#error "call analysis failed"
//----- (00100000) --------------------------------------------------------
int sub_100000(void) { return 0; }
#error "There were failures during decompilation"
'''
        failures, summary = verifier.failed_function_addresses(text)
        self.assertEqual(failures, [0xFDF26])
        self.assertEqual(len(summary), 1)


if __name__ == "__main__":
    unittest.main()
