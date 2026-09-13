#!/usr/bin/env python3
"""Validate old ABI spellings without creating another recovered identity.

An alias forwards to the current recovered name, which remains the ABI adapter
when the canonical implementation becomes a method. Metadata validation is pure;
source validation reads the closed source inventory and never updates hashes.
Only fixed, named scalar/pointer parameters are currently supported. Other
declarators need a separately proved forwarding contract, not guessed parsing.
"""
from __future__ import annotations

from collections import defaultdict
from pathlib import Path, PurePosixPath
import re

from recovered_implementation import ImplementationError, manifest_sources, manifest_targets
from split_source_index import TOKEN_RE, body_sha256, mask_c, scan_definitions


IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")
SHA256 = re.compile(r"[0-9a-f]{64}\Z")
ALIAS_FIELDS = {"name", "source", "body_sha256", "reason"}
COMMENTS = re.compile(r"//[^\r\n]*|/\*.*?\*/", re.S)
TYPE_WORDS = {"void", "bool", "char", "short", "int", "long", "signed", "unsigned",
              "float", "double", "const", "volatile"}


def _source(value: object) -> bool:
    if not isinstance(value, str) or "\\" in value or ":" in value:
        return False
    path = PurePosixPath(value)
    return (not path.is_absolute() and ".." not in path.parts and len(path.parts) >= 3
            and path.parts[0] == "src" and str(path) == value
            and not re.search(r"[\x00-\x20#();$]", value)
            and path.suffix in {".c", ".cpp", ".cc", ".cxx"})


def _signature(text: str, name: str) -> tuple[tuple[str, ...], tuple[tuple[str, ...], ...], tuple[str, ...]]:
    """Keep type spelling and calling convention; discard only parameter names."""
    text = COMMENTS.sub(" ", text).strip().removesuffix(";").strip()
    # These exact attributes keep ABI exports alive; no other attribute is waived.
    text = re.sub(r"__attribute__\s*\(\(\s*(?:used\s*,\s*retain|retain\s*,\s*used)\s*\)\)", " ", text)
    text = re.sub(r'^extern\s+"C"\s+', "", text)
    text = re.sub(r"^extern\s+", "", text)
    match = re.fullmatch(r"(.+?)\b" + re.escape(name) + r"\s*\((.*?)\)\s*", text, re.S)
    if not match:
        raise ValueError(f"{name}: unsupported fixed ABI signature")
    result, parameters = match.groups()
    if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9\s:*&]*", result.strip()):
        raise ValueError(f"{name}: unsupported result type or signature attribute")
    result_tokens = tuple(TOKEN_RE.findall(result))
    if set(result_tokens) & {"static", "inline", "constexpr", "consteval", "CLASH95_LOCAL", "CLASH95_INTERNAL"}:
        raise ValueError(f"{name}: alias must preserve external ABI linkage")
    types, names = [], []
    if parameters.strip() not in ("", "void"):
        for parameter in parameters.split(","):
            part = re.fullmatch(r"\s*([A-Za-z_][A-Za-z_0-9\s:*&]*?)([A-Za-z_][A-Za-z_0-9]*)\s*", parameter)
            if not part or not part[1].strip() or part[2] in TYPE_WORDS:
                raise ValueError(f"{name}: fixed named scalar/pointer parameters are required")
            # A separator must distinguish the name from the preceding type token.
            if not (part[1][-1].isspace() or part[1][-1] in "*&"):
                raise ValueError(f"{name}: parameter name is not separated from its type")
            types.append(tuple(TOKEN_RE.findall(part[1])))
            names.append(part[2])
    if len(names) != len(set(names)):
        raise ValueError(f"{name}: duplicate parameter names")
    return result_tokens, tuple(types), tuple(names)


def _new_identity_fields(record: dict) -> bool:
    return any(not isinstance(key, str) or key.startswith("original_") or key in {"address", "legacy_body_sha256"}
               for key in record) or record.get("identity_kind") == "original"


def validate_alias_metadata(manifest: dict, declarations: dict, registry: dict) -> list[str]:
    """Require one documented, address-free helper for every historical spelling."""
    if not all(isinstance(value, dict) for value in (manifest, declarations, registry)):
        return ["alias manifest, declarations and registry must be objects"]
    try:
        targets = manifest_targets(manifest)
        inventory = set(manifest_sources(manifest))
    except (ImplementationError, KeyError, TypeError, AttributeError) as error:
        return [f"alias manifest is invalid: {error}"]
    functions = declarations.get("functions")
    helpers, identities = registry.get("helpers"), registry.get("identities")
    if not isinstance(functions, dict) or not isinstance(helpers, list) or not isinstance(identities, list):
        return ["alias validation requires function declarations and helper/identity arrays"]
    errors = []
    occupied = {target.name for target in targets}
    helpers_by_name, identities_by_name = defaultdict(list), defaultdict(list)
    for entry in helpers:
        if isinstance(entry, dict) and isinstance(entry.get("name"), str):
            helpers_by_name[entry["name"]].append(entry)
    for entry in identities:
        if isinstance(entry, dict) and isinstance(entry.get("name"), str):
            identities_by_name[entry["name"]].append(entry)
    seen = set()
    for record in manifest["functions"]:
        name = record["name"]
        history, aliases = record.get("historical_names", []), record.get("compatibility_aliases", [])
        if not isinstance(history, list) or not all(isinstance(old, str) and IDENTIFIER.fullmatch(old) for old in history):
            errors.append(f"{name}: historical_names must be an array of identifiers")
            history = []
        elif len(history) != len(set(history)):
            errors.append(f"{name}: duplicate historical name")
        if not isinstance(aliases, list):
            errors.append(f"{name}: compatibility_aliases must be an array")
            continue
        valid_aliases = []
        for alias in aliases:
            if not isinstance(alias, dict):
                errors.append(f"{name}: compatibility alias must be an object")
                continue
            old = alias.get("name")
            if set(alias) != ALIAS_FIELDS:
                errors.append(f"{name}: alias requires exactly name/source/body_sha256/reason, without original identity fields")
            if not isinstance(old, str) or not IDENTIFIER.fullmatch(old):
                errors.append(f"{name}: invalid alias name")
                continue
            valid_aliases.append(old)
            if old in seen:
                errors.append(f"{old}: duplicate compatibility alias")
            seen.add(old)
            if old in occupied or old in identities_by_name:
                errors.append(f"{old}: alias must not be another canonical implementation or recovered identity")
            digest = alias.get("body_sha256")
            if not isinstance(digest, str) or not SHA256.fullmatch(digest):
                errors.append(f"{old}: alias body_sha256 must be a lowercase SHA-256 digest")
            if not isinstance(alias.get("reason"), str) or not alias["reason"].strip():
                errors.append(f"{old}: compatibility reason is required")
            source = alias.get("source")
            adapter = record.get("adapter")
            anchor = adapter["source"] if isinstance(adapter, dict) else record["source"]
            if not _source(source) or source not in inventory or source != anchor:
                errors.append(f"{old}: source must be the safe original canonical/adapter anchor in the recovered inventory")
            registrations = helpers_by_name[old]
            if len(registrations) != 1:
                errors.append(f"{old}: expected one retained-boundary helper registration")
            else:
                helper = registrations[0]
                if (helper.get("classification") != "retained-boundary" or helper.get("source") != source
                        or not isinstance(helper.get("rationale"), str) or not helper["rationale"].strip()
                        or _new_identity_fields(helper)):
                    errors.append(f"{old}: helper must be an address-free retained-boundary at the alias source with rationale")
            declaration, canonical = functions.get(old), functions.get(name)
            if (not isinstance(declaration, dict) or declaration.get("class") != "helper"
                    or declaration.get("source") != source or _new_identity_fields(declaration)):
                errors.append(f"{old}: alias requires an address-free helper declaration at its source")
                continue
            if not isinstance(canonical, dict) or canonical.get("class") != "manifest":
                errors.append(f"{name}: alias target requires a canonical manifest declaration")
                continue
            try:
                if _signature(declaration["decl"], old)[:2] != _signature(canonical["decl"], name)[:2]:
                    errors.append(f"{old}: alias and canonical declared ABI types differ")
            except (KeyError, TypeError, ValueError) as error:
                errors.append(f"{old}: invalid ABI declaration: {error}")
        if set(history) != set(valid_aliases):
            errors.append(f"{name}: historical names and compatibility aliases must match exactly; no lost or undocumented spelling")
        if history or aliases:
            if manifest.get("schema_version") != 3:
                errors.append(f"{name}: compatibility aliases require manifest schema 3")
            if len(identities_by_name[name]) != 1:
                errors.append(f"{name}: expected one canonical identity registration")
    return errors


def validate_alias_sources(manifest: dict, root: Path, declarations: dict, registry: dict) -> list[str]:
    """Check one thin definition per alias, exact forwarding and declared ABI."""
    errors = validate_alias_metadata(manifest, declarations, registry)
    if errors:
        return errors
    records = [record for record in manifest["functions"] if record.get("compatibility_aliases")]
    if not records:
        return []
    expected, aliases = {}, {}
    for record in records:
        for target in manifest_targets({"schema_version": 3, "functions": [record]}):
            expected[target.name] = target.source
        for alias in record["compatibility_aliases"]:
            expected[alias["name"]] = alias["source"]
            aliases[alias["name"]] = (record["name"], alias)
    root = Path(root).resolve()
    found = defaultdict(list)
    for source in manifest_sources(manifest):
        if not _source(source):
            errors.append(f"unsafe recovered source path: {source}")
            continue
        try:
            path = (root / source).resolve()
            if not path.is_relative_to(root):
                errors.append(f"recovered source resolves outside root: {source}")
                continue
            text = path.read_text(encoding="utf-8")
            definitions = scan_definitions(text, set(expected))
        except (OSError, UnicodeError, ValueError, RuntimeError) as error:
            errors.append(f"cannot read recovered source {source}: {error}")
            continue
        for definition in definitions:
            found[definition.name].append((source, text, definition))
    for name, source in expected.items():
        matches = found[name]
        if len(matches) != 1:
            errors.append(f"{name}: expected one definition in the closed source inventory, found {len(matches)}")
            continue
        actual_source, text, definition = matches[0]
        if actual_source != source:
            errors.append(f"{name}: definition is outside its registered source {source}")
        if name not in aliases and "::" in name:
            continue  # The normal implementation validator owns the method signature.
        masked = mask_c(text)
        preceding = masked[:definition.start]
        if preceding.count("{") != preceding.count("}"):
            errors.append(f"{name}: ABI definition must be at global scope, outside anonymous namespaces")
        try:
            # The shared index starts at the name's line. Include preceding
            # specifier lines so a split-line static/weak attribute cannot hide.
            signature_start = max(preceding.rfind(token) for token in ";{}") + 1
            actual_signature = _signature(masked[signature_start:definition.opening_brace], name)
            declared_signature = _signature(declarations["functions"][name]["decl"], name)
            if actual_signature[:2] != declared_signature[:2]:
                errors.append(f"{name}: definition does not preserve its declared ABI types")
        except (KeyError, TypeError, ValueError) as error:
            errors.append(f"{name}: invalid definition signature: {error}")
            continue
        if name not in aliases:
            continue
        canonical, alias = aliases[name]
        if body_sha256(text, definition) != alias["body_sha256"]:
            errors.append(f"{name}: alias body hash is stale")
        body = COMMENTS.sub(" ", text[definition.opening_brace:definition.end])
        arguments = r"\s*,\s*".join(map(re.escape, actual_signature[2]))
        wanted = (r"\{\s*return\s+(?:::\s*)?" + re.escape(canonical)
                  + r"\s*\(\s*" + arguments + r"\s*\)\s*;\s*\}")
        if not re.fullmatch(wanted, body):
            errors.append(f"{name}: alias must only return {canonical}(parameters...) in original order")
        protected = {name, canonical, *actual_signature[2]}
        macros = set(re.findall(r"^\s*#\s*(?:define|undef)\s+([A-Za-z_][A-Za-z_0-9]*)", text, re.M))
        if macros & protected:
            errors.append(f"{name}: macro rewriting of the alias, target or parameters is not allowed")
    return errors
