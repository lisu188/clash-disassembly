#!/usr/bin/env python3

from pathlib import Path
import re
import unittest

REPO = Path(__file__).resolve().parents[2]
HEADER = REPO / "src" / "render" / "render_surface_view.h"


class RenderSurfaceViewContractTests(unittest.TestCase):
    def test_only_promoted_offsets_are_exposed(self):
        text = HEADER.read_text(encoding="utf-8")
        offsets = {
            name: int(value)
            for name, value in re.findall(
                r"k(Width|Height|PixelBufferHandle|MethodTableHandle)Offset\s*=\s*(\d+)",
                text,
            )
        }
        self.assertEqual(
            offsets,
            {
                "Width": 0,
                "Height": 2,
                "PixelBufferHandle": 4,
                "MethodTableHandle": 184,
            },
        )
        self.assertIn(
            "kRowStrideOffset = RenderSurfaceView::kObjectSize;",
            text,
        )
        self.assertIn(
            "static_assert(RenderSurfaceWithStrideView::kRowStrideOffset == 188);",
            text,
        )

    def test_storage_sizes_remain_188_and_192(self):
        text = HEADER.read_text(encoding="utf-8")
        self.assertIn("static constexpr std::size_t kObjectSize = 188;", text)
        self.assertIn("static_assert(sizeof(RenderSurfaceStorage) == 192);", text)
        self.assertNotIn("virtual ", text)


if __name__ == "__main__":
    unittest.main()
