#!/usr/bin/env python3
"""Apply one fail-closed recovered function-identity migration."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path

from split_source_index import body_sha256, scan_definitions


ROOT = Path(__file__).resolve().parents[1]
MANIFEST_REL = Path("data/recovered_sources.json")
DECLS_REL = Path("data/recovered_decls.json")
IDENT_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
SHA_RE = re.compile(r"^[0-9a-f]{64}$")


def load_spec(root: Path, spec_path: Path) -> dict:
    if not spec_path.is_absolute():
        spec_path = root / spec_path
    payload = json.loads(spec_path.read_text(encoding="utf-8"))
    if payload.get("schema_version") != 1:
        raise ValueError("identity migration spec must use schema_version 1")
    for key in ("old_name", "new_name"):
        value = payload.get(key)
        if not isinstance(value, str) or not IDENT_RE.fullmatch(value):
            raise ValueError(f"{key} must be a C identifier")
    if payload["old_name"] == payload["new_name"]:
        raise ValueError("old_name and new_name must differ")
    for key in ("source", "compatibility_source"):
        value = payload.get(key)
        if not isinstance(value, str) or not value.startswith("src/"):
            raise ValueError(f"{key} must be a src/ path")
        path = (root / value).resolve()
        if not path.is_relative_to((root / "src").resolve()):
            raise ValueError(f"{key} escapes src/")
    address = payload.get("original_address")
    if not isinstance(address, str) or not re.fullmatch(r"0x[0-9A-Fa-f]{8}", address):
        raise ValueError("original_address must be 0x followed by eight hex digits")
    for key in ("expected_body_sha256", "expected_compat_body_sha256"):
        value = payload.get(key)
        if not isinstance(value, str) or not SHA_RE.fullmatch(value):
            raise ValueError(f"{key} must be a lowercase sha256")
    return payload


def manifest_address(record: dict) -> str | None:
    direct = record.get("original_address")
    if isinstance(direct, str):
        return direct
    address_range = record.get("original_address_range")
    if isinstance(address_range, dict):
        start = address_range.get("start")
        if isinstance(start, str):
            return start
    return None


def one_definition(text: str, name: str, label: str):
    definitions = scan_definitions(text, {name})
    if len(definitions) != 1:
        raise ValueError(f"{label}: expected one definition of {name}, found {len(definitions)}")
    return definitions[0]


def no_definition(text: str, name: str, label: str) -> None:
    definitions = scan_definitions(text, {name})
    if definitions:
        raise ValueError(f"{label}: unexpected definition of {name}")


def rename_definition(text: str, definition, old_name: str, new_name: str) -> str:
    prefix = text[definition.start:definition.opening_brace]
    replaced, count = re.subn(
        rf"\b{re.escape(old_name)}\b", new_name, prefix, count=1
    )
    if count != 1:
        raise ValueError(f"canonical definition signature does not contain {old_name} exactly once")
    return text[:definition.start] + replaced + text[definition.opening_brace:]


def remove_definition(text: str, definition) -> str:
    end = definition.end
    while end < len(text) and text[end] in " \t":
        end += 1
    if end < len(text) and text[end] == "\r":
        end += 1
    if end < len(text) and text[end] == "\n":
        end += 1
    if end < len(text) and text[end] == "\n":
        end += 1
    return text[:definition.start] + text[end:]


def replace_decl_identifier(decl: str, old_name: str, new_name: str) -> str:
    replaced, count = re.subn(rf"\b{re.escape(old_name)}\b", new_name, decl)
    if count != 1:
        raise ValueError(f"manifest declaration must contain {old_name} exactly once")
    return replaced


def rewrite_decl_db(decls: dict, old_name: str, new_name: str) -> dict:
    functions = decls.get("functions")
    if not isinstance(functions, dict):
        raise ValueError("declaration DB functions must be an object")
    old = functions.get(old_name)
    new = functions.get(new_name)
    if not isinstance(old, dict) or old.get("class") != "manifest":
        raise ValueError(f"{old_name}: expected manifest declaration record")
    if not isinstance(new, dict) or new.get("class") != "legacy-import":
        raise ValueError(f"{new_name}: expected legacy-import declaration record")
    migrated = dict(old)
    migrated["decl"] = replace_decl_identifier(old["decl"], old_name, new_name)

    rebuilt = {}
    for key, value in functions.items():
        if key == old_name:
            continue
        if key == new_name:
            rebuilt[new_name] = migrated
        else:
            rebuilt[key] = value
    decls["functions"] = rebuilt
    return decls


def validate_pre_state(root: Path, payload: dict, manifest: dict, decls: dict):
    old_name = payload["old_name"]
    new_name = payload["new_name"]
    records = manifest.get("functions")
    if not isinstance(records, list):
        raise ValueError("manifest functions must be an array")
    old_records = [record for record in records if record.get("name") == old_name]
    new_records = [record for record in records if record.get("name") == new_name]
    if len(old_records) != 1 or new_records:
        return None
    record = old_records[0]
    if record.get("source") != payload["source"]:
        raise ValueError(f"{old_name}: manifest source differs from spec")
    if manifest_address(record) != payload["original_address"]:
        raise ValueError(f"{old_name}: original address differs from spec")

    source_path = root / payload["source"]
    source_text = source_path.read_text(encoding="latin-1")
    old_definition = one_definition(source_text, old_name, payload["source"])
    no_definition(source_text, new_name, payload["source"])
    digest = body_sha256(source_text, old_definition)
    if digest != payload["expected_body_sha256"]:
        raise ValueError(f"{old_name}: canonical body hash {digest} differs from spec")

    compat_path = root / payload["compatibility_source"]
    compat_text = compat_path.read_text(encoding="latin-1")
    compat_definition = one_definition(compat_text, new_name, payload["compatibility_source"])
    compat_digest = body_sha256(compat_text, compat_definition)
    if compat_digest != payload["expected_compat_body_sha256"]:
        raise ValueError(f"{new_name}: compatibility body hash {compat_digest} differs from spec")

    functions = decls.get("functions", {})
    if functions.get(old_name, {}).get("class") != "manifest":
        raise ValueError(f"{old_name}: declaration is not manifest class")
    if functions.get(new_name, {}).get("class") != "legacy-import":
        raise ValueError(f"{new_name}: declaration is not legacy-import class")
    return record, source_path, source_text, old_definition, compat_path, compat_text, compat_definition


def validate_post_state(root: Path, payload: dict, manifest: dict, decls: dict) -> bool:
    old_name = payload["old_name"]
    new_name = payload["new_name"]
    records = manifest.get("functions", [])
    old_records = [record for record in records if record.get("name") == old_name]
    new_records = [record for record in records if record.get("name") == new_name]
    if old_records or len(new_records) != 1:
        return False
    record = new_records[0]
    if record.get("source") != payload["source"] or manifest_address(record) != payload["original_address"]:
        raise ValueError(f"{new_name}: post-migration manifest identity differs from spec")
    source_text = (root / payload["source"]).read_text(encoding="latin-1")
    no_definition(source_text, old_name, payload["source"])
    definition = one_definition(source_text, new_name, payload["source"])
    if body_sha256(source_text, definition) != payload["expected_body_sha256"]:
        raise ValueError(f"{new_name}: post-migration canonical body hash differs")
    compat_text = (root / payload["compatibility_source"]).read_text(encoding="latin-1")
    no_definition(compat_text, new_name, payload["compatibility_source"])
    functions = decls.get("functions", {})
    if old_name in functions:
        raise ValueError(f"{old_name}: old declaration remains after migration")
    if functions.get(new_name, {}).get("class") != "manifest":
        raise ValueError(f"{new_name}: post-migration declaration is not manifest class")
    return True


def apply_identity_migration(root: Path, spec_path: Path, write: bool) -> bool:
    payload = load_spec(root, spec_path)
    manifest_path = root / MANIFEST_REL
    decls_path = root / DECLS_REL
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    decls = json.loads(decls_path.read_text(encoding="utf-8"))

    pre = validate_pre_state(root, payload, manifest, decls)
    if pre is None:
        if validate_post_state(root, payload, manifest, decls):
            return False
        raise ValueError("repository is neither the exact pre-migration nor post-migration state")

    record, source_path, source_text, old_definition, compat_path, compat_text, compat_definition = pre
    old_name = payload["old_name"]
    new_name = payload["new_name"]

    source_text = rename_definition(source_text, old_definition, old_name, new_name)
    compat_text = remove_definition(compat_text, compat_definition)
    record["name"] = new_name
    decls = rewrite_decl_db(decls, old_name, new_name)

    if write:
        source_path.write_text(source_text, encoding="latin-1", newline="")
        compat_path.write_text(compat_text, encoding="latin-1", newline="")
        manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8", newline="\n")
        decls_path.write_text(json.dumps(decls, indent=2) + "\n", encoding="utf-8", newline="\n")

    if write:
        manifest_check = json.loads(manifest_path.read_text(encoding="utf-8"))
        decls_check = json.loads(decls_path.read_text(encoding="utf-8"))
        if not validate_post_state(root, payload, manifest_check, decls_check):
            raise ValueError("post-migration validation failed")
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("spec", type=Path)
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args()
    try:
        changed = apply_identity_migration(args.root.resolve(), args.spec, args.write)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"function identity migration: FAIL: {exc}")
        return 1
    mode = "APPLIED" if args.write else "PLAN"
    print(f"function identity migration: {mode}; state={'changed' if changed else 'already-applied'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
