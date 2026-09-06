#!/usr/bin/env python3
"""Validate the explicit game-class migration inventory without rewriting it.

The registry is a reviewed assignment of identities, not a prefix classifier.
New recovered functions and new support helpers require explicit registration.
An ownership assignment records migration intent; it does not assert that a
class body has already been extracted or that behavior has been validated.
"""

from __future__ import annotations

import argparse
from collections import Counter
import json
from pathlib import Path, PurePosixPath
import re
import sys

from class_binding_inventory import validate_binding_metadata, validate_binding_sources


REPO = Path(__file__).resolve().parents[1]
REGISTRY = REPO / "data/game_class_registry.json"
MANIFEST = REPO / "data/recovered_sources.json"
DECLARATIONS = REPO / "data/recovered_decls.json"
CLASSIFICATIONS = {"game-method", "retained-boundary", "excluded-library"}
IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")
ADDRESS = re.compile(r"0x[0-9A-Fa-f]{8}\Z")
FORBIDDEN_OWNER = re.compile(r"(?:Misc|Unclassified|Unknown|SubsystemOperations|RecoveredOperations)", re.I)
SURFACE_EXCEPTIONS = frozenset({
    "Surface_DDCopyBitmapToNewSurface", "Surface_DDCopyBitmapFromFile",
    "Surface_DDCopyBitmap", "Surface_BuildPaletteFromBitmap",
    "Surface_MatchColorToNativePixel",
})


def _safe_source_path(value: object, suffix: str) -> bool:
    if not isinstance(value, str) or "\\" in value:
        return False
    path = PurePosixPath(value)
    return (not path.is_absolute() and ".." not in path.parts
            and len(path.parts) >= 3 and path.parts[0] == "src"
            and path.suffix == suffix)


def validate_registry(registry: dict, manifest: dict, declarations: dict | None = None) -> list[str]:
    """Return all inventory errors; never infer ownership for missing entries."""
    errors: list[str] = []
    if not isinstance(registry, dict) or not isinstance(manifest, dict):
        return ["registry and manifest must be objects"]
    if registry.get("schema_version") != 1:
        errors.append("registry schema_version must be 1")
    identities = registry.get("identities")
    if not isinstance(identities, list):
        return errors + ["registry identities must be a list"]
    functions = manifest.get("functions", [])
    expected: dict[str, dict] = {}
    for item in functions:
        name = item.get("name")
        if name in expected:
            errors.append(f"manifest contains duplicate identity {name}")
        expected[name] = item
    seen: set[str] = set()
    owner_paths: dict[str, tuple] = {}
    method_owners: set[tuple[str, str]] = set()
    for item in identities:
        if not isinstance(item, dict):
            errors.append("identity must be an object")
            continue
        name = item.get("name")
        label = str(name)
        if not isinstance(name, str) or not IDENTIFIER.fullmatch(name):
            errors.append(f"invalid identity name {label}")
            continue
        if name in seen:
            errors.append(f"duplicate registry identity {name}")
        seen.add(name)
        original = expected.get(name)
        if original is None:
            errors.append(f"unknown registry identity {name}")
        classification = item.get("classification")
        if classification not in CLASSIFICATIONS:
            errors.append(f"{name}: invalid classification {classification}")
        if original:
            implementation = original.get("implementation", {"kind": "free"})
            if implementation.get("kind") == "method":
                if classification != "game-method":
                    errors.append(f"{name}: procedural disposition cannot own a method")
                expected_name = "clash95::" + str(item.get("class_owner")) + "::" + name
                if implementation.get("qualified_name") != expected_name:
                    errors.append(f"{name}: implementation owner differs from registry")
                if implementation.get("header") != item.get("final_header"):
                    errors.append(f"{name}: implementation header differs from registry")
        rationale = item.get("rationale")
        if not isinstance(rationale, str) or len(rationale.strip()) < 24:
            errors.append(f"{name}: evidence-backed rationale is required")
        evidence = item.get("evidence")
        if (not isinstance(evidence, list) or not evidence
                or any(not isinstance(value, str) or not value.strip() for value in evidence)):
            errors.append(f"{name}: evidence references are required")
        if original:
            address = original.get("original_address")
            kind = "original" if address else "support-helper"
            if item.get("identity_kind") != kind:
                errors.append(f"{name}: identity_kind must be {kind}")
            if address:
                actual = item.get("original_address")
                if (not isinstance(actual, str) or not ADDRESS.fullmatch(actual)
                        or actual.lower() != address.lower()):
                    errors.append(f"{name}: original address differs from manifest")
            elif "original_address" in item:
                errors.append(f"{name}: support helper must not invent an original address")
            if item.get("legacy_subsystem") != original.get("subsystem"):
                errors.append(f"{name}: legacy subsystem differs from manifest")
            if item.get("original_source") != original.get("original_source"):
                errors.append(f"{name}: historical original source differs from manifest")
            if not _safe_source_path(item.get("legacy_source"), ".cpp"):
                errors.append(f"{name}: invalid legacy source path")
            # Current source may change after the class's parity gate. Large
            # classes can explicitly register class-named implementation shards.
            destinations = item.get("additional_sources", [])
            if not isinstance(destinations, list):
                errors.append(f"{name}: additional_sources must be a list")
                destinations = []
            if original.get("source") not in [item.get("legacy_source"), item.get("final_source"), *destinations]:
                errors.append(f"{name}: source is neither legacy nor assigned class destination")
            if original.get("subsystem") == "clips":
                wanted = "game-method" if name in SURFACE_EXCEPTIONS else "excluded-library"
                if classification != wanted:
                    errors.append(f"{name}: CLIPS boundary requires {wanted}")
            if original.get("subsystem") == "runtime" and address:
                in_game_prefix = 0x00461520 <= int(address, 16) <= 0x004635A0
                if in_game_prefix and classification != "game-method":
                    errors.append(f"{name}: audited runtime game prefix must have a class owner")
                elif not in_game_prefix and classification != "excluded-library":
                    errors.append(f"{name}: runtime CLIPS/CRT tail must remain excluded")
        if classification == "game-method":
            owner = item.get("class_owner")
            method = item.get("method")
            logical = item.get("logical_subsystem")
            if not isinstance(owner, str) or not IDENTIFIER.fullmatch(owner) or FORBIDDEN_OWNER.search(owner):
                errors.append(f"{name}: concrete class_owner is required")
                continue
            if not isinstance(method, str) or not IDENTIFIER.fullmatch(method):
                errors.append(f"{name}: valid method name is required")
            if not isinstance(logical, str) or not re.fullmatch(r"[a-z][a-z0-9_]*", logical):
                errors.append(f"{name}: logical_subsystem is required")
            header, source = item.get("final_header"), item.get("final_source")
            if not _safe_source_path(header, ".hpp") or PurePosixPath(header).stem != owner:
                errors.append(f"{name}: final header must be a class-named src header")
            if not _safe_source_path(source, ".cpp") or PurePosixPath(source).stem != owner:
                errors.append(f"{name}: final source must be a class-named src translation unit")
            for shard in item.get("additional_sources", []) if isinstance(item.get("additional_sources", []), list) else []:
                if (not _safe_source_path(shard, ".cpp")
                        or not re.fullmatch(re.escape(owner) + r"\.part[0-9]+", PurePosixPath(shard).stem)):
                    errors.append(f"{name}: implementation shard must retain its class name")
            paths = (logical, header, source)
            if owner in owner_paths and owner_paths[owner] != paths:
                errors.append(f"{name}: conflicting paths or subsystem for class {owner}")
            owner_paths[owner] = paths
            key = (owner, method)
            if key in method_owners:
                errors.append(f"{name}: duplicate class method {owner}::{method}")
            method_owners.add(key)
        elif any(key in item for key in ("class_owner", "method", "final_header", "final_source")):
            errors.append(f"{name}: procedural boundary must not claim a class implementation")
    for name in sorted(set(expected) - seen):
        errors.append(f"unclassified manifest identity {name}")
    helpers = registry.get("helpers")
    if not isinstance(helpers, list):
        errors.append("helpers must be a separate list")
    else:
        helper_seen: set[str] = set()
        expected_helpers = ({name: item for name, item in declarations.get("functions", {}).items()
                             if item.get("class") == "helper"} if declarations is not None else None)
        for helper in helpers:
            name = helper.get("name") if isinstance(helper, dict) else None
            if not isinstance(name, str) or not IDENTIFIER.fullmatch(name):
                errors.append("support helper requires a valid name")
                continue
            if name in seen or name in helper_seen:
                errors.append(f"support helper duplicates registered identity {name}")
            helper_seen.add(name)
            if "original_address" in helper:
                errors.append(f"{name}: support helper must not invent an original address")
            if (not isinstance(helper.get("rationale"), str) or len(helper["rationale"].strip()) < 24
                    or not _safe_source_path(helper.get("source"), ".cpp")):
                errors.append(f"{name}: support helper requires source and rationale")
            if helper.get("classification") not in CLASSIFICATIONS or not helper.get("evidence"):
                errors.append(f"{name}: support helper requires classification and evidence")
            if helper.get("classification") == "game-method":
                owner, logical = helper.get("class_owner"), helper.get("logical_subsystem")
                if not isinstance(owner, str) or not IDENTIFIER.fullmatch(owner) or FORBIDDEN_OWNER.search(owner):
                    errors.append(f"{name}: support helper requires a concrete class owner")
                elif (helper.get("final_header") != f"src/{logical}/{owner}.hpp"
                      or helper.get("final_source") != f"src/{logical}/{owner}.cpp"
                      or not IDENTIFIER.fullmatch(helper.get("method", ""))):
                    errors.append(f"{name}: support helper requires class-named destinations and method")
                elif owner not in owner_paths or owner_paths[owner] != (logical, helper["final_header"], helper["final_source"]):
                    errors.append(f"{name}: support helper owner disagrees with identity catalog")
                key = (owner, helper.get("method"))
                if key in method_owners:
                    errors.append(f"{name}: support helper duplicates a class method")
                method_owners.add(key)
            elif any(key in helper for key in ("class_owner", "method", "final_header", "final_source")):
                errors.append(f"{name}: procedural support helper must not claim a class implementation")
            if expected_helpers is not None:
                if name not in expected_helpers:
                    errors.append(f"unknown support helper {name}")
                elif expected_helpers[name].get("source") not in (helper.get("source"), helper.get("final_source")):
                    errors.append(f"{name}: support helper source differs from declarations")
        if expected_helpers is not None:
            for name in sorted(set(expected_helpers) - helper_seen):
                errors.append(f"unclassified support helper {name}")
    errors.extend(validate_binding_metadata(registry, manifest, declarations))
    return errors


def summary(registry: dict) -> dict:
    entries = registry["identities"]
    return {
        "identities": len(entries),
        "classifications": dict(sorted(Counter(item["classification"] for item in entries).items())),
        "classes": len({item["class_owner"] for item in entries if item["classification"] == "game-method"}),
        "support_helpers": len(registry["helpers"]),
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="check explicit inventory (read-only; default)")
    parser.add_argument("--registry", type=Path, default=REGISTRY)
    parser.add_argument("--manifest", type=Path, default=MANIFEST)
    parser.add_argument("--declarations", type=Path, default=DECLARATIONS)
    args = parser.parse_args(argv)
    try:
        registry = json.loads(args.registry.read_text(encoding="utf-8"))
        manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
        declarations = json.loads(args.declarations.read_text(encoding="utf-8"))
        errors = validate_registry(registry, manifest, declarations)
        if not errors:
            errors.extend(validate_binding_sources(registry, manifest, declarations, REPO))
    except (OSError, ValueError, TypeError, KeyError) as exc:
        print(f"game class catalog: {exc}", file=sys.stderr)
        return 1
    if errors:
        for error in errors:
            print(f"game class catalog: {error}", file=sys.stderr)
        return 1
    print(json.dumps(summary(registry), sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
