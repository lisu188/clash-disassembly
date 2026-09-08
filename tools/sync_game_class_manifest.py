#!/usr/bin/env python3
"""Synchronize explicit class dispositions without changing recovered bodies."""
from __future__ import annotations

import argparse
import json
from pathlib import Path

from game_class_catalog import validate_registry
from recovered_implementation import implementation_name, manifest_sources

ROOT = Path(__file__).resolve().parents[1]


def synchronize(manifest: dict, registry: dict, declarations: dict | None = None) -> dict:
    errors = validate_registry(registry, manifest, declarations)
    if errors:
        raise ValueError("\n".join(errors))
    result = json.loads(json.dumps(manifest))
    result["schema_version"] = 3
    result["class_registry"] = "data/game_class_registry.json"
    assignments = {record["name"]: record for record in registry["identities"]}
    for record in result["functions"]:
        assignment = assignments[record["name"]]
        record["disposition"] = assignment["classification"]
        record["disposition_reason"] = assignment["rationale"]
        record.setdefault("implementation", {"kind": "free", "qualified_name": record["name"]})
        if assignment["classification"] == "game-method":
            owner = "clash95::" + assignment["class_owner"]
            record["class_owner"] = owner
            if record["implementation"]["kind"] == "method":
                if implementation_name(record) != owner + "::" + record["name"]:
                    raise ValueError(f"{record['name']}: method owner differs from registry")
                if record["implementation"]["header"] != assignment["final_header"]:
                    raise ValueError(f"{record['name']}: class header differs from registry")
        else:
            record.pop("class_owner", None)
            if record["implementation"]["kind"] != "free":
                raise ValueError(f"{record['name']}: procedural disposition has a method")
    result["source_file_count"] = len(manifest_sources(result))
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args()
    path = ROOT / "data/recovered_sources.json"
    manifest = json.loads(path.read_text())
    registry = json.loads((ROOT / "data/game_class_registry.json").read_text())
    declarations = json.loads((ROOT / "data/recovered_decls.json").read_text())
    result = synchronize(manifest, registry, declarations)
    if args.write:
        path.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    elif manifest != result:
        raise SystemExit("class dispositions are stale; rerun with --write")
    count = sum(record["implementation"]["kind"] == "method" for record in result["functions"])
    print(f"class manifest: 4157 dispositions, {count} canonical methods")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
