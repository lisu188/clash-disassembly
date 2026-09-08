#!/usr/bin/env python3
"""Audit address-free class borrowing glue separately from recovered identities.

Metadata validation is pure. Source validation reads the closed recovered source
inventory, validates the exact borrowing factory, and rejects unregistered or
duplicate qualified definitions. Constructor layout is audited separately.
"""
from __future__ import annotations

from collections import defaultdict
from pathlib import Path, PurePosixPath
import re

from recovered_implementation import ImplementationError, manifest_sources, manifest_targets
from split_source_index import body_sha256, scan_definitions


IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")
SHA256 = re.compile(r"[0-9a-f]{64}\Z")
BINDING_FIELDS = {"class_owner", "qualified_name", "source", "referenced_globals", "body_sha256"}
COMMENTS_AND_LITERALS = re.compile(r'//[^\r\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)


def _source(value: object) -> bool:
    if not isinstance(value, str) or "\\" in value or ":" in value:
        return False
    path = PurePosixPath(value)
    return (not path.is_absolute() and ".." not in path.parts and len(path.parts) >= 3
            and path.parts[0] == "src" and str(path) == value
            and not re.search(r"[\x00-\x20#();$]", value)
            and path.suffix in {".c", ".cpp", ".cc", ".cxx"})


def _storage_source(record: dict) -> str | None:
    owner = record.get("owner")
    if not _source(owner):
        return None
    return str(PurePosixPath(owner).with_suffix(".cpp")) if owner.endswith(".c") else owner


def _helper_methods(registry: dict, declarations: dict) -> tuple[dict[str, str], list[str]]:
    result = {}
    errors = []
    helpers, functions = registry.get("helpers", []), declarations.get("functions", {})
    if not isinstance(helpers, list) or not isinstance(functions, dict):
        return {}, ["qualified helper validation requires helper array and function declaration object"]
    for helper in helpers:
        if not isinstance(helper, dict) or helper.get("classification") != "game-method":
            continue
        owner, method = helper.get("class_owner"), helper.get("method")
        if not all(isinstance(value, str) and IDENTIFIER.fullmatch(value) for value in (owner, method)):
            errors.append("registered helper method requires valid class owner and method names")
            continue
        name = helper.get("name")
        declaration = functions.get(name, {}) if isinstance(name, str) else {}
        if not isinstance(declaration, dict):
            declaration = {}
        source = declaration.get("source", helper.get("source"))
        if declaration.get("class") != "helper" or not _source(source):
            errors.append(f"{name}: qualified helper requires a canonical helper declaration and source")
            continue
        qualified = f"clash95::{owner}::{method}"
        if qualified in result:
            errors.append(f"{qualified}: duplicate helper method registration")
        if method == "borrow":
            errors.append(f"{qualified}: borrowing factories require separate class_bindings registration")
        result[qualified] = source
    return result, errors


def validate_binding_metadata(registry: dict, manifest: dict, declarations: dict | None = None) -> list[str]:
    """Validate registration, sorted canonical-global order, and source anchors."""
    if not isinstance(registry, dict) or not isinstance(manifest, dict):
        return ["binding registry and manifest must be objects"]
    bindings = registry.get("class_bindings", [])
    if not isinstance(bindings, list):
        return ["class_bindings must be a separate list"]
    if not bindings:
        return []
    errors = []
    if manifest.get("schema_version") != 3:
        errors.append("class bindings require manifest schema 3")
    if not isinstance(declarations, dict) or not isinstance(declarations.get("globals"), dict):
        return errors + ["class bindings require canonical global declarations"]
    identities, functions = registry.get("identities"), manifest.get("functions")
    if not isinstance(identities, list) or not isinstance(functions, list):
        return errors + ["class bindings require identity and function arrays"]
    try:
        inventory = set(manifest_sources(manifest))
        targets = manifest_targets(manifest)
    except (ImplementationError, KeyError, TypeError, AttributeError) as error:
        return errors + [f"class binding manifest is invalid: {error}"]
    records = {item["name"]: item for item in functions}
    owners = defaultdict(list)
    for identity in identities:
        if isinstance(identity, dict) and identity.get("classification") == "game-method":
            owner = identity.get("class_owner")
            if isinstance(owner, str):
                owners[owner].append(identity)
    canonical_names = {target.name for target in targets}
    helpers, helper_errors = _helper_methods(registry, declarations)
    helper_names = set(helpers)
    errors.extend(helper_errors)
    global_db = declarations["globals"]
    seen_owners, seen_names = set(), set()
    for index, binding in enumerate(bindings):
        if not isinstance(binding, dict):
            errors.append(f"class_bindings[{index}] must be an object")
            continue
        owner = binding.get("class_owner")
        label = f"class binding {owner!r}"
        if set(binding) != BINDING_FIELDS:
            errors.append(f"{label}: requires exactly the address-free binding fields; no original identity fields")
        if not isinstance(owner, str) or not IDENTIFIER.fullmatch(owner) or owner not in owners:
            errors.append(f"{label}: unknown or invalid class owner")
            continue
        if owner in seen_owners:
            errors.append(f"{label}: duplicate class owner")
        seen_owners.add(owner)
        qualified = binding.get("qualified_name")
        expected_name = f"clash95::{owner}::borrow"
        if qualified != expected_name:
            errors.append(f"{label}: qualified_name must be {expected_name}")
        if isinstance(qualified, str):
            if qualified in seen_names:
                errors.append(f"{label}: duplicate qualified factory name")
            seen_names.add(qualified)
            if qualified in canonical_names or qualified in helper_names:
                errors.append(f"{label}: factory must not replace a recovered identity or helper method")
        value = binding.get("body_sha256")
        if not isinstance(value, str) or not SHA256.fullmatch(value):
            errors.append(f"{label}: body_sha256 must be a lowercase SHA-256 digest")
        globals_ = binding.get("referenced_globals")
        valid_globals = isinstance(globals_, list) and all(
            isinstance(name, str) and IDENTIFIER.fullmatch(name) for name in globals_)
        if not valid_globals:
            errors.append(f"{label}: referenced_globals must be an ordered array of canonical names")
            globals_ = []
        else:
            if len(set(globals_)) != len(globals_):
                errors.append(f"{label}: duplicate referenced global")
            if globals_ != sorted(globals_):
                errors.append(f"{label}: referenced globals differ from the required canonical name order")
            for name in globals_:
                declaration = global_db.get(name)
                if not isinstance(declaration, dict) or not isinstance(declaration.get("decl"), str):
                    errors.append(f"{label}: undeclared canonical global {name}")
        source = binding.get("source")
        if not _source(source) or source not in inventory:
            errors.append(f"{label}: source must be a safe path in the recovered inventory")
            continue
        anchors = set()
        for identity in owners[owner]:
            name = identity.get("name")
            record = records.get(name, {}) if isinstance(name, str) else {}
            adapter = record.get("adapter")
            candidate = adapter.get("source") if isinstance(adapter, dict) else record.get("source")
            legacy = identity.get("legacy_source")
            if candidate and (legacy is None or candidate == legacy):
                anchors.add(candidate)
        anchors.update(owner_source for name in globals_ if isinstance(global_db.get(name), dict)
                       and (owner_source := _storage_source(global_db[name])) in inventory)
        if source not in anchors:
            errors.append(f"{label}: source is not an owning original adapter/storage anchor")
    return errors


def _without_comments(text: str) -> str:
    def replace(match):
        value = match[0]
        if value.startswith(("//", "/*")):
            return " "
        raise ValueError("literals are not allowed in borrowing factories")
    return COMMENTS_AND_LITERALS.sub(replace, text)


def _factory_shape(text: str, definition, binding: dict) -> bool:
    owner = re.escape(binding["class_owner"])
    try:
        signature = _without_comments(text[definition.start:definition.opening_brace]).strip()
        body = _without_comments(text[definition.opening_brace:definition.end])
    except ValueError:
        return False
    # Fully qualified out-of-line spelling is the generated factory contract.
    # No overload, default argument, extra specifier or return-type alias can
    # turn a different method into a registered zero-argument borrow factory.
    wanted_signature = rf"clash95\s*::\s*{owner}\s+clash95\s*::\s*{owner}\s*::\s*borrow\s*\(\s*\)\s+noexcept"
    if not re.fullmatch(wanted_signature, signature):
        return False
    arguments = r"\s*,\s*".join(r"::\s*" + re.escape(name) for name in binding["referenced_globals"])
    return re.fullmatch(r"\{\s*return\s+" + owner + r"\s*\(\s*" + arguments + r"\s*\)\s*;\s*\}", body) is not None


def validate_binding_sources(
    registry: dict, manifest: dict, declarations: dict, root: Path,
) -> list[str]:
    """Read and validate registered factories and the complete qualified surface."""
    errors = validate_binding_metadata(registry, manifest, declarations)
    if errors:
        return errors
    if not isinstance(declarations, dict):
        return ["class source validation requires canonical declarations"]
    try:
        inventory = manifest_sources(manifest)
        targets = manifest_targets(manifest)
    except (ImplementationError, KeyError, TypeError, AttributeError) as error:
        return [f"class binding manifest is invalid: {error}"]
    root = Path(root).resolve()
    expected = {target.name: target.source for target in targets if target.name.startswith("clash95::")}
    helpers, helper_errors = _helper_methods(registry, declarations)
    errors.extend(helper_errors)
    for name, source in helpers.items():
        if name in expected:
            errors.append(f"{name}: helper duplicates a canonical method registration")
        if source not in inventory:
            errors.append(f"{name}: helper declaration source is outside the recovered inventory")
        expected[name] = source
    bindings = {binding["qualified_name"]: binding for binding in registry.get("class_bindings", [])}
    for name, binding in bindings.items():
        expected[name] = binding["source"]
    found = defaultdict(list)
    for source in inventory:
        if not _source(source):
            errors.append(f"unsafe recovered source path: {source}")
            continue
        try:
            path = (root / source).resolve()
            if not path.is_relative_to(root):
                errors.append(f"recovered source resolves outside root: {source}")
                continue
            text = path.read_text(encoding="utf-8")
            definitions = scan_definitions(text, None)
        except (OSError, UnicodeError, ValueError, RuntimeError) as error:
            errors.append(f"cannot read recovered source {source}: {error}")
            continue
        for definition in definitions:
            name = definition.name
            if not name.startswith("clash95::"):
                continue
            found[name].append((source, text, definition))
            if name not in expected or (name.endswith("::borrow") and name not in bindings):
                errors.append(f"unregistered qualified definition {name} in {source}:{definition.line}")
            elif source != expected[name]:
                errors.append(f"{name}: definition is outside its registered source {expected[name]}")
    # Planned helper assignments may still have procedural bodies. A helper
    # whose declaration has moved away from its original source is migrated
    # and must have a qualified definition, even if that definition is absent.
    required = (set(expected) - set(helpers)) | set(bindings)
    for helper in registry.get("helpers", []) if isinstance(registry.get("helpers", []), list) else []:
        if not isinstance(helper, dict):
            continue
        name = f"clash95::{helper.get('class_owner')}::{helper.get('method')}"
        if name in helpers and helpers[name] != helper.get("source"):
            required.add(name)
    for name in sorted(set(found) | required):
        definitions = found.get(name, [])
        if len(definitions) != 1:
            errors.append(f"{name}: expected one qualified definition, found {len(definitions)}")
            continue
        if name not in bindings:
            continue
        source, text, definition = definitions[0]
        binding = bindings[name]
        if body_sha256(text, definition) != binding["body_sha256"]:
            errors.append(f"{name}: borrowing factory body hash is stale")
        if not _factory_shape(text, definition, binding):
            errors.append(f"{name}: factory must only return {binding['class_owner']}(::globals...) in registered order")
    return errors
