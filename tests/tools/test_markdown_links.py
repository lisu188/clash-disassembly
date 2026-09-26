#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tests"))
import check_markdown_links as links


class MarkdownLinkTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        patch = mock.patch.object(links, "REPO_ROOT", self.root)
        patch.start()
        self.addCleanup(patch.stop)

    def write(self, relative: str, text: str) -> Path:
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")
        return path

    def test_private_artifact_backtick_reference_is_allowed(self):
        path = self.write("docs/status.md", "`artifacts/private/report.md`\n")
        self.assertEqual(links.check_file(path), [])

    def test_private_artifact_markdown_link_is_still_checked(self):
        path = self.write("docs/status.md", "[report](artifacts/private/report.md)\n")
        self.assertEqual(
            links.check_file(path),
            ["docs/status.md: missing Markdown link target: artifacts/private/report.md"],
        )

    def test_missing_tracked_style_backtick_reference_still_fails(self):
        path = self.write("docs/status.md", "`docs/missing.md`\n")
        self.assertEqual(
            links.check_file(path),
            ["docs/status.md: missing referenced path: docs/missing.md"],
        )


if __name__ == "__main__":
    unittest.main()
