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
DEFAULT_MANIFEST = Path("data/recovered_sources.json")
MARKER_RE = re.compile(r"(?m)^//----- \(([0-9A-Fa-f]{8})\) [-]+\r?$")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT,
                        help="repository root (mainly useful for isolated tooling tests)")
    parser.add_argument("--manifest", type=Path, default=DEFAULT_MANIFEST)
    parser.add_argument(
        "--update",
        action="store_true",
        help="replace canonical/adapter hashes while preserving manifest schema 3",
    )
    parser.add_argument(
        "--only", action="append", default=[], metavar="FUNCTION",
        help=("with --update, refresh only this historical identity's canonical "
              "and adapter hashes; any changed unselected body fails"),
    )
    args = parser.parse_args()
    root = args.root.resolve()
    selected = set(args.only)
    if selected and not args.update:
        parser.error("--only requires --update")
    manifest_path = args.manifest
    if not manifest_path.is_absolute():
        manifest_path = root / manifest_path
    payload = json.loads(manifest_path.read_text(encoding="utf-8"))
    records = payload.get("functions", [])
    if not isinstance(records, list):
        raise SystemExit("manifest functions must be an array")

    resolved_selection: set[str] = set()
    selection_errors = []
    for name in sorted(selected):
        matches = [record for record in records
                   if record["name"] == name or name in record.get("historical_names", [])]
        if not matches:
            selection_errors.append(f"{name}: not present in manifest")
        elif len(matches) != 1:
            selection_errors.append(f"{name}: ambiguous historical identity in manifest")
        else:
            resolved_selection.add(matches[0]["name"])
    if selection_errors:
        for error in selection_errors:
            print(error)
        return 1
    selected = resolved_selection

    try:
        sources = manifest_sources(payload)
        indexed = index_manifest_definitions(payload, root)
    except ImplementationError as error:
        print(error)
        return 1
    marker_count = 0
    for source in sources:
        path = root / source
        text = path.read_text(encoding="utf-8")
        marker_count += len(MARKER_RE.findall(text))

    errors: list[str] = []
    changed_names: set[str] = set()
    for record in records:
        name = record["name"]
        roles = [("canonical", record)]
        if "adapter" in record:
            roles.append(("adapter", record["adapter"]))
        for role, metadata in roles:
            digest = indexed[(name, role)].body_sha256
            old_digest = metadata.get("body_sha256")
            if not args.update:
                if old_digest != digest:
                    errors.append(f"{name}: {role} body hash differs")
                continue
            if selected:
                if old_digest != digest and name not in selected:
                    errors.append(
                        f"{name}: {role} body hash differs outside --only selection")
                if name not in selected or old_digest == digest:
                    continue
            if role == "canonical" and "legacy_body_sha256" not in record:
                record["legacy_body_sha256"] = old_digest
            metadata["body_sha256"] = digest
            if old_digest != digest:
                changed_names.add(name)
    if errors:
        for error in errors[:50]:
            print(error)
        if len(errors) > 50:
            print(f"... {len(errors) - 50} more")
        return 1

    if args.update:
        if selected and not changed_names:
            print("selected canonical and adapter body hashes already match; "
                  f"functions={len(selected)} markers={marker_count}")
            return 0
        payload["schema_version"] = 3 if payload.get("schema_version") == 3 else 2
        payload["cutover"] = "canonical-split"
        payload["legacy_manifest"] = payload.pop(
            "oracle_manifest", payload.get("legacy_manifest", "clash95.c")
        )
        payload["address_marker_count"] = marker_count
        manifest_path.write_text(
            json.dumps(payload, indent=2) + "\n", encoding="utf-8", newline="\n"
        )
        if selected:
            print(f"updated {len(changed_names)} selected canonical body hashes; "
                  "including adapters; "
                  f"functions={','.join(sorted(changed_names))}; markers={marker_count}")
        else:
            print(f"updated {len(records)} canonical body hashes; "
                  f"preserved legacy hashes; markers={marker_count}")
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
