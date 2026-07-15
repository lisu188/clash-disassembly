#!/usr/bin/env python3
"""Check the asset-free save-image size contract across live recovery data."""

from __future__ import annotations

import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
EXPECTED_PAYLOAD = 0x8F29E
LABEL_BYTES = 16


def require_equal(label: str, actual: int, expected: int) -> None:
    if actual != expected:
        raise SystemExit(f"{label}: expected {expected}, found {actual}")


def source_define(path: Path) -> int:
    text = path.read_text(encoding="utf-8")
    match = re.search(
        r"(?m)^#define\s+GAMEDATA_SAVE_IMAGE_BYTES\s+(0[xX][0-9A-Fa-f]+|\d+)\s*$",
        text,
    )
    if match is None:
        raise SystemExit(f"missing GAMEDATA_SAVE_IMAGE_BYTES in {path}")
    return int(match.group(1), 0)


def main() -> int:
    constants = json.loads(
        (ROOT / "tools" / "constants_manifest.json").read_text(encoding="utf-8")
    )
    records = [
        record
        for record in constants["constants"]
        if record.get("name") == "GAMEDATA_SAVE_IMAGE_BYTES"
    ]
    if len(records) != 1:
        raise SystemExit(
            "constants manifest must contain exactly one GAMEDATA_SAVE_IMAGE_BYTES"
        )

    from dump_save_dat import GAME_DATA_SIZE

    require_equal("constants manifest", int(records[0]["value"]), EXPECTED_PAYLOAD)
    require_equal("save decoder", GAME_DATA_SIZE, EXPECTED_PAYLOAD)
    require_equal(
        "split foundation",
        source_define(ROOT / "src" / "recovered_foundation.h"),
        EXPECTED_PAYLOAD,
    )
    print(
        "save format contract: PASS "
        f"(label={LABEL_BYTES}, payload={EXPECTED_PAYLOAD}, dat={LABEL_BYTES + EXPECTED_PAYLOAD})"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
