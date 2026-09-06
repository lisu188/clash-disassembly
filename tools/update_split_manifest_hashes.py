#!/usr/bin/env python3
"""Check or explicitly refresh canonical split-body hashes in the manifest."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

from recovered_implementation import (
    ImplementationError,
    index_manifest_definitions,
    manifest_sources,
)


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_MANIFEST = ROOT / "data" / "recovered_sources.json"
MARKER_RE = re.compile(r"(?m)^//----- \(([0-9A-Fa-f]{8})\) [-]+\r?$")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument(
        "--update",
        action="store_true",
        help="replace canonical hashes and migrate the manifest to schema 2",
    )
    args = parser.parse_args()
    manifest_path = args.manifest
    if not manifest_path.is_absolute():
        manifest_path = ROOT / manifest_path
    payload = json.loads(manifest_path.read_text(encoding="utf-8"))
    records = payload.get("functions", [])
    if not isinstance(records, list):
        raise SystemExit("manifest functions must be an array")

    try:
        sources = manifest_sources(payload)
        indexed = index_manifest_definitions(payload, ROOT)
    except ImplementationError as error:
        print(error)
        return 1
    marker_count = 0
    for source in sources:
        path = ROOT / source
        text = path.read_text(encoding="utf-8")
        marker_count += len(MARKER_RE.findall(text))

    errors: list[str] = []
    for record in records:
        name = record["name"]
        digest = indexed[(name, "canonical")].body_sha256
        if args.update:
            if "legacy_body_sha256" not in record:
                record["legacy_body_sha256"] = record.get("body_sha256")
            record["body_sha256"] = digest
        elif record.get("body_sha256") != digest:
            errors.append(f"{name}: canonical body hash differs")
        if "adapter" in record:
            adapter_digest = indexed[(name, "adapter")].body_sha256
            if args.update:
                record["adapter"]["body_sha256"] = adapter_digest
            elif record["adapter"].get("body_sha256") != adapter_digest:
                errors.append(f"{name}: adapter body hash differs")
    if errors:
        for error in errors[:50]:
            print(error)
        if len(errors) > 50:
            print(f"... {len(errors) - 50} more")
        return 1

    if args.update:
        payload["schema_version"] = 3 if payload.get("schema_version") == 3 else 2
        payload["cutover"] = "canonical-split"
        payload["legacy_manifest"] = payload.pop(
            "oracle_manifest", payload.get("legacy_manifest", "clash95.c")
        )
        payload["address_marker_count"] = marker_count
        manifest_path.write_text(
            json.dumps(payload, indent=2) + "\n", encoding="utf-8", newline="\n"
        )
        print(
            f"updated {len(records)} canonical body hashes; "
            f"preserved legacy hashes; markers={marker_count}"
        )
    else:
        if payload.get("schema_version") not in (2, 3):
            raise SystemExit("manifest is not canonical split schema 2 or 3")
        if payload.get("address_marker_count") != marker_count:
            raise SystemExit(
                f"address_marker_count differs: {payload.get('address_marker_count')} "
                f"!= {marker_count}"
            )
        print(
            f"canonical manifest hashes: PASS "
            f"(functions={len(records)}, markers={marker_count})"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
