#!/usr/bin/env python3
"""Validate support definitions without adding identities to the recovered 4,157.

The scope is the four audited support translation units and two inline headers.
Every disposition is explicit data. This module never assigns ownership from a
name prefix or directory. Counts describe source definitions in all branches,
not linked symbols, active code, recovered addresses, or behavioral readiness.

Direct state references are lexical uses of declared global names, excluding
obvious parameters/member selections. They do not describe receiver fields,
macro expansion, transitive effects, or ownership/lifetime proof.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path, PurePosixPath
import re

from split_source_index import TOKEN_RE, body_sha256, mask_c, scan_definitions
from recovered_implementation import ImplementationError, manifest_targets


ROOT = Path(__file__).resolve().parents[1]
INVENTORY = ROOT / "data/support_class_inventory.json"
SCOPE_SOURCES = (
    "src/platform/platform_sdl_runtime.cpp",
    "src/bootstrap/bootstrap_main.cpp",
    "src/instrumentation/runtime_mission_trace.cpp",
    "src/compatibility/decomp_runtime_stubs.cpp",
    "src/platform/platform_sdl.h",
    "src/compatibility/defs.h",
)
IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")
QUALIFIED = re.compile(r"[A-Za-z_][A-Za-z_0-9]*(?:::[A-Za-z_][A-Za-z_0-9]*)*\Z")
SHA256 = re.compile(r"[0-9a-f]{64}\Z")
TOKENS = re.compile(r"\b[A-Za-z_][A-Za-z_0-9]*\b")
REQUIRED_FIELDS = {
    "id", "identity_kind", "origin_source", "name", "source", "qualified_name", "body_sha256", "signature_sha256",
    "origin_body_sha256", "origin_signature_sha256",
    "surface", "disposition", "owner", "logical_subsystem", "migration", "boundary_roles",
    "binding_role", "direct_state_references", "constraints", "blockers", "rationale", "evidence",
}
OPTIONAL_FIELDS = {"final_header", "final_source", "adapter"}
BOUNDARY_ROLES = {
    "internal-support", "public-c-abi", "function-table-callback", "raw-thread-callback",
    "signal-callback", "constructor-entry", "header-inline", "diagnostic-infrastructure",
    "low32-allocator", "os-error-accessor", "rectangle-utility", "compatibility-token",
    "inert-import", "diagnostic-output", "drive-query", "process-entry", "crt-quarantine",
    "memory-compatibility", "file-stream-compatibility", "value-string-compatibility",
    "thread-signal-compatibility", "compiler-runtime", "clips-forwarder", "codec-quarantine",
    "inert-callback", "game-forwarder", "abi-dispatch-adapter",
}


def _safe_path(value: object, suffixes=(".cpp", ".h", ".hpp")) -> bool:
    if not isinstance(value, str) or re.search(r"[\\:\x00-\x20#;$()]+", value):
        return False
    path = PurePosixPath(value)
    return (not path.is_absolute() and len(path.parts) >= 3 and path.parts[0] == "src"
            and ".." not in path.parts and str(path) == value and path.suffix in suffixes)


def _string_list(value: object, *, allow_empty=True) -> bool:
    return (isinstance(value, list) and (allow_empty or bool(value))
            and all(isinstance(item, str) and bool(item.strip()) for item in value)
            and len(value) == len(set(value)))


def inventory_summary(document: dict) -> dict:
    definitions = document.get("definitions", [])
    return {
        "definitions": len(definitions),
        "surfaces": dict(Counter(item["surface"] for item in definitions)),
        "dispositions": dict(Counter(item["disposition"] for item in definitions)),
        "retained_diagnostic_definitions": sum("diagnostic-infrastructure" in item["boundary_roles"] for item in definitions),
        "runtime_class_owners": dict(sorted(Counter(item["owner"] for item in definitions
                                                   if item["disposition"] == "runtime-method").items())),
    }


def signature_sha256(text: str, definition) -> str:
    tokens = TOKEN_RE.findall(text[definition.start:definition.opening_brace])
    return hashlib.sha256("\n".join(tokens).encode("utf-8")).hexdigest()


def origin_inventory_sha256(definitions: list[dict]) -> str:
    """Fingerprint immutable origin keys and first-audited bodies separately."""
    rows = [[item.get(key) for key in ("id", "origin_source", "name", "origin_body_sha256", "origin_signature_sha256")]
            for item in definitions if isinstance(item, dict)]
    payload = json.dumps(sorted(rows, key=lambda row: str(row[0])), separators=(",", ":"), ensure_ascii=True)
    return hashlib.sha256(payload.encode("ascii")).hexdigest()


def validate_inventory_metadata(document: dict, recovered_manifest: dict | None = None) -> list[str]:
    """Validate explicit dispositions, stable support keys and separate counts."""
    if not isinstance(document, dict):
        return ["support inventory must be an object"]
    errors = []
    if document.get("schema_version") != 1:
        errors.append("support inventory schema_version must be 1")
    if document.get("scope_sources") != list(SCOPE_SOURCES):
        errors.append("scope_sources must retain all six explicitly audited support files in order")
    definitions = document.get("definitions")
    if not isinstance(definitions, list):
        return errors + ["support definitions must be a separate array"]
    if document.get("definition_count") != len(definitions):
        errors.append("support definition_count differs from the explicit inventory")
    if document.get("origin_inventory_sha256") != origin_inventory_sha256(definitions):
        errors.append("immutable support origin inventory fingerprint differs")
    commit = document.get("source_reference_commit")
    if not isinstance(commit, str) or not re.fullmatch(r"[0-9a-f]{40}", commit):
        errors.append("source_reference_commit must identify the frozen source snapshot")
    references = document.get("source_reference_files")
    if (not isinstance(references, list) or len(references) != len(SCOPE_SOURCES)
            or any(not isinstance(item, dict) for item in references)):
        errors.append("source_reference_files must retain all six frozen source hashes")
    else:
        origin_counts = Counter(item.get("origin_source") for item in definitions
                                if isinstance(item, dict) and isinstance(item.get("origin_source"), str))
        for source, reference in zip(SCOPE_SOURCES, references):
            if (set(reference) != {"source", "sha256", "definition_count"} or reference.get("source") != source
                    or not isinstance(reference.get("sha256"), str) or not SHA256.fullmatch(reference["sha256"])
                    or reference.get("definition_count") != origin_counts[source]):
                errors.append(f"{source}: invalid frozen source hash/count record")
    recovered_names = set()
    if recovered_manifest is not None:
        functions = recovered_manifest.get("functions") if isinstance(recovered_manifest, dict) else None
        if not isinstance(functions, list):
            errors.append("recovered manifest functions must be an array")
        else:
            recovered_names = {item["name"] for item in functions if isinstance(item, dict) and isinstance(item.get("name"), str)}
    seen_ids, seen_targets = set(), set()
    owner_paths = {}
    for index, item in enumerate(definitions):
        if not isinstance(item, dict):
            errors.append(f"support definition {index} must be an object")
            continue
        label = f"support definition {item.get('id', index)}"
        if not REQUIRED_FIELDS <= item.keys() or item.keys() - REQUIRED_FIELDS - OPTIONAL_FIELDS:
            errors.append(f"{label}: missing/unknown fields; original identity fields are forbidden")
        if item.get("identity_kind") != "support-definition":
            errors.append(f"{label}: identity_kind must be support-definition")
        name, origin, source, qualified = (item.get(key) for key in ("name", "origin_source", "source", "qualified_name"))
        if not isinstance(name, str) or not QUALIFIED.fullmatch(name):
            errors.append(f"{label}: invalid original support name")
            continue
        if origin not in SCOPE_SOURCES or item.get("id") != f"{origin}::{name}":
            errors.append(f"{label}: id must retain the audited origin_source::name")
        if isinstance(item.get("id"), str) and item["id"] in seen_ids:
            errors.append(f"{label}: duplicate support identity")
        if isinstance(item.get("id"), str):
            seen_ids.add(item["id"])
        if name in recovered_names:
            errors.append(f"{label}: support name overlaps a recovered identity")
        if not _safe_path(source) or not isinstance(qualified, str) or not QUALIFIED.fullmatch(qualified):
            errors.append(f"{label}: invalid canonical source or qualified name")
            continue
        target = source, qualified
        if target in seen_targets:
            errors.append(f"{label}: duplicate canonical definition target")
        seen_targets.add(target)
        for key in ("body_sha256", "signature_sha256", "origin_body_sha256", "origin_signature_sha256"):
            if not isinstance(item.get(key), str) or not SHA256.fullmatch(item[key]):
                errors.append(f"{label}: {key} must be a lowercase SHA-256 digest")
        surface = "header-inline" if isinstance(origin, str) and origin.endswith(".h") else "translation-unit"
        if item.get("surface") != surface:
            errors.append(f"{label}: surface differs from the original support source")
        disposition, owner, logical = (item.get(key) for key in ("disposition", "owner", "logical_subsystem"))
        if not isinstance(owner, str) or not IDENTIFIER.fullmatch(owner):
            errors.append(f"{label}: explicit valid owner is required")
        if not isinstance(logical, str) or not IDENTIFIER.fullmatch(logical):
            errors.append(f"{label}: logical_subsystem is required")
        migration = item.get("migration")
        if not isinstance(migration, dict) or set(migration) != {"extraction", "relocation"}:
            errors.append(f"{label}: separate extraction and relocation statuses are required")
            migration = {}
        if disposition == "runtime-method":
            header, final = item.get("final_header"), item.get("final_source")
            if header != f"src/{logical}/{owner}.hpp" or final != f"src/{logical}/{owner}.cpp":
                errors.append(f"{label}: runtime owner requires exact class-named destinations")
            if isinstance(owner, str):
                if owner in owner_paths and owner_paths[owner] != (header, final):
                    errors.append(f"{label}: runtime owner has inconsistent destinations")
                owner_paths[owner] = header, final
            if item.get("binding_role") != "borrow-existing-state":
                errors.append(f"{label}: runtime methods must borrow existing state")
            if migration.get("extraction") == "planned":
                if migration.get("relocation") != "pending" or source != origin or qualified != name or "adapter" in item:
                    errors.append(f"{label}: planned body must remain at its unchanged free boundary")
            elif migration.get("extraction") == "extracted":
                if qualified != f"clash95::{owner}::{name.rsplit('::', 1)[-1]}":
                    errors.append(f"{label}: extracted canonical method differs from owner/name")
                wanted = origin if migration.get("relocation") == "pending" else final
                if migration.get("relocation") not in ("pending", "relocated") or source != wanted:
                    errors.append(f"{label}: relocated implementation must use its assigned class source")
            else:
                errors.append(f"{label}: runtime extraction must be planned or extracted")
        elif disposition == "procedural-boundary":
            if (migration != {"extraction": "retained", "relocation": "not-applicable"}
                    or source != origin or qualified != name or set(item) & OPTIONAL_FIELDS):
                errors.append(f"{label}: retained procedural boundary cannot claim class migration")
            if item.get("binding_role") != "retain-existing-storage":
                errors.append(f"{label}: procedural boundary must retain existing storage")
        else:
            errors.append(f"{label}: missing or unclassified disposition")
        for key in ("boundary_roles", "constraints", "blockers", "evidence", "direct_state_references"):
            if not _string_list(item.get(key), allow_empty=key in {"blockers", "direct_state_references"}):
                errors.append(f"{label}: {key} must contain explicit unique strings")
        roles = item.get("boundary_roles", [])
        if isinstance(roles, list) and all(isinstance(role, str) for role in roles):
            if set(roles) - BOUNDARY_ROLES:
                errors.append(f"{label}: unknown boundary role")
            if "diagnostic-infrastructure" in roles and disposition != "procedural-boundary":
                errors.append(f"{label}: diagnostics are explicitly retained procedural infrastructure")
        references = item.get("direct_state_references")
        if isinstance(references, list) and all(isinstance(value, str) for value in references):
            if references != sorted(references) or any(not IDENTIFIER.fullmatch(value) for value in references):
                errors.append(f"{label}: direct state references require sorted canonical identifier spellings")
        if not isinstance(item.get("rationale"), str) or len(item["rationale"].strip()) < 32:
            errors.append(f"{label}: a concrete disposition rationale is required")
        if "adapter" in item:
            adapter = item["adapter"]
            if (not isinstance(adapter, dict) or set(adapter) != {"source", "qualified_name", "body_sha256", "signature_sha256"}
                    or adapter.get("source") != origin or adapter.get("qualified_name") != name
                    or any(not isinstance(adapter.get(key), str) or not SHA256.fullmatch(adapter[key])
                           for key in ("body_sha256", "signature_sha256"))):
                errors.append(f"{label}: adapter must retain the original source/name and exact body hash")
            elif (adapter["source"], adapter["qualified_name"]) in seen_targets:
                errors.append(f"{label}: duplicate adapter definition target")
            else:
                seen_targets.add((adapter["source"], adapter["qualified_name"]))
        if (migration.get("extraction") == "extracted" and isinstance(roles, list) and all(isinstance(role, str) for role in roles)
                and set(roles) & {"public-c-abi", "function-table-callback", "raw-thread-callback", "signal-callback"}
                and "adapter" not in item):
            errors.append(f"{label}: exposed callable identity requires an explicit adapter")
    return errors


def declared_state_names(texts: dict[str, str], declarations: dict | None = None) -> set[str]:
    """Find direct global spellings, keeping local-static objects in constraints."""
    names = set(declarations.get("globals", {})) if isinstance(declarations, dict) else set()
    pattern = re.compile(r"(?m)^(?:static\s+|extern\s+)?(?:[A-Za-z_]\w*[ \t*]+)+([A-Za-z_]\w*)\s*(?:\[[^\n;]*\])?\s*[=;]")
    for text in texts.values():
        code = list(mask_c(text))
        for definition in scan_definitions(text, None):
            code[definition.start:definition.end] = " " * (definition.end - definition.start)
        names.update(match[1] for match in pattern.finditer("".join(code)))
    return names


def direct_state_references(text: str, definition, state_names: set[str]) -> list[str]:
    body = mask_c(text[definition.opening_brace:definition.end])
    signature = mask_c(text[definition.start:definition.opening_brace])
    references = set()
    for match in TOKENS.finditer(body):
        name = match[0]
        if name not in state_names or body[:match.start()].rstrip().endswith((".", "->")):
            continue
        # A same-named formal argument is direct receiver/input evidence, not
        # evidence that this body reads the global of that name.
        if re.search(r"[\s*]" + re.escape(name) + r"\s*(?:\[[^]]*\]\s*)?[,)]", signature):
            continue
        references.add(name)
    return sorted(references)


def validate_inventory_sources(document: dict, root: Path, recovered_manifest: dict | None = None,
                               declarations: dict | None = None) -> list[str]:
    errors = validate_inventory_metadata(document, recovered_manifest)
    if errors:
        return errors
    try:
        recovered_targets = {(target.source, target.name) for target in manifest_targets(recovered_manifest)} if recovered_manifest else set()
    except (ImplementationError, KeyError, TypeError, AttributeError) as error:
        return [f"invalid recovered implementation inventory: {error}"]
    root = Path(root).resolve()
    expected = {}
    sources = set(SCOPE_SOURCES)
    for item in document["definitions"]:
        expected[item["source"], item["qualified_name"]] = item, "canonical"
        sources.add(item["source"])
        if "adapter" in item:
            adapter = item["adapter"]
            expected[adapter["source"], adapter["qualified_name"]] = item, "adapter"
            sources.add(adapter["source"])
    texts, found = {}, defaultdict(list)
    for source in sorted(sources):
        try:
            path = (root / source).resolve()
            if not path.is_relative_to(root):
                errors.append(f"support source resolves outside repository: {source}")
                continue
            text = path.read_text(encoding="utf-8")
            definitions = scan_definitions(text, None)
        except (OSError, ValueError, UnicodeError, RuntimeError) as error:
            errors.append(f"cannot read/index support source {source}: {error}")
            continue
        texts[source] = text
        for definition in definitions:
            key = source, definition.name
            # A support method can join an existing class file containing
            # separately inventoried recovered methods. Their own audit owns
            # those bodies; this exemption never applies to the six anchors.
            if source not in SCOPE_SOURCES and key in recovered_targets and key not in expected:
                continue
            found[key].append(definition)
            if key not in expected:
                errors.append(f"unclassified support definition {source}::{definition.name}")
    state_names = declared_state_names(texts, declarations)
    for key in sorted(set(expected) | set(found)):
        definitions = found.get(key, [])
        if len(definitions) != 1:
            errors.append(f"{key[0]}::{key[1]}: expected one definition, found {len(definitions)}")
            continue
        if key not in expected:
            continue
        item, role = expected[key]
        definition, text = definitions[0], texts[key[0]]
        wanted = item if role == "canonical" else item["adapter"]
        if body_sha256(text, definition) != wanted["body_sha256"]:
            errors.append(f"{item['id']}: {role} body hash is stale")
        if signature_sha256(text, definition) != wanted["signature_sha256"]:
            errors.append(f"{item['id']}: {role} signature hash is stale")
        if role == "canonical":
            if direct_state_references(text, definition, state_names) != item["direct_state_references"]:
                errors.append(f"{item['id']}: direct state reference evidence differs from the canonical body")
            body = mask_c(text[definition.opening_brace:definition.end])
            if re.search(r"\bstatic\b", body) and "preserve-local-static-storage" not in item["constraints"]:
                errors.append(f"{item['id']}: local-static storage constraint is missing")
    return errors


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--inventory", type=Path)
    args = parser.parse_args(argv)
    try:
        inventory = json.loads((args.inventory or args.root / "data/support_class_inventory.json").read_text(encoding="utf-8"))
        manifest = json.loads((args.root / "data/recovered_sources.json").read_text(encoding="utf-8"))
        declarations = json.loads((args.root / "data/recovered_decls.json").read_text(encoding="utf-8"))
        errors = validate_inventory_sources(inventory, args.root, manifest, declarations)
    except (OSError, ValueError, TypeError) as error:
        errors = [str(error)]
    print(json.dumps({"ok": not errors, "errors": errors,
                      "summary": inventory_summary(inventory) if not errors else None,
                      "written": False}, indent=2))
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
