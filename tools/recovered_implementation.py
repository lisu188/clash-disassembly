#!/usr/bin/env python3
"""Resolve historical recovered identities to canonical bodies and ABI adapters.

Schema 2 remains a free-function manifest. Schema 3 separates an immutable
historical identity from its current qualified implementation and optional
adapter. This module owns that interpretation for all source-based tools.
"""

from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path, PurePosixPath
import re

from split_source_index import Definition, body_sha256, scan_definitions


IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
QUALIFIED_NAME = re.compile(r"[A-Za-z_][A-Za-z0-9_]*(?:::[A-Za-z_][A-Za-z0-9_]*)*\Z")


class ImplementationError(ValueError):
    """An implementation mapping is missing, invalid, or ambiguous."""


@dataclass(frozen=True)
class DefinitionTarget:
    identity: str
    role: str
    name: str
    source: str

    @property
    def key(self) -> tuple[str, str]:
        return self.identity, self.role


@dataclass(frozen=True)
class ResolvedDefinition:
    target: DefinitionTarget
    definition: Definition
    body_sha256: str


def _source(value: object) -> str:
    if not isinstance(value, str) or "\\" in value:
        raise ImplementationError(f"invalid manifest source path: {value!r}")
    path = PurePosixPath(value)
    if (path.is_absolute() or ".." in path.parts or ":" in value
            or path.suffix not in (".c", ".cpp", ".cc", ".cxx")
            or str(path) != value):
        raise ImplementationError(f"invalid manifest source path: {value!r}")
    return value


def implementation_name(record: dict) -> str:
    identity = record.get("name")
    if not isinstance(identity, str) or not IDENTIFIER.fullmatch(identity):
        raise ImplementationError(f"invalid recovered identity: {identity!r}")
    implementation = record.get("implementation")
    if implementation is None:
        return identity
    if not isinstance(implementation, dict):
        raise ImplementationError(f"{identity}: implementation must be an object")
    name = implementation.get("qualified_name")
    kind = implementation.get("kind")
    if not isinstance(name, str) or not QUALIFIED_NAME.fullmatch(name):
        raise ImplementationError(f"{identity}: invalid qualified implementation name")
    if kind == "free":
        if name != identity:
            raise ImplementationError(f"{identity}: free implementation must retain its name")
    elif kind == "method":
        if "::" not in name or name.rsplit("::", 1)[-1] != identity:
            raise ImplementationError(f"{identity}: method must retain its unique historical leaf")
    else:
        raise ImplementationError(f"{identity}: invalid implementation kind {kind!r}")
    return name


def definition_targets(record: dict) -> tuple[DefinitionTarget, ...]:
    name = implementation_name(record)
    identity = record["name"]
    canonical = DefinitionTarget(identity, "canonical", name, _source(record.get("source")))
    adapter = record.get("adapter")
    if adapter is None:
        if name != identity:
            raise ImplementationError(f"{identity}: method requires a legacy adapter")
        return (canonical,)
    if name == identity or not isinstance(adapter, dict):
        raise ImplementationError(f"{identity}: only a method can have an adapter object")
    return canonical, DefinitionTarget(identity, "adapter", identity, _source(adapter.get("source")))


def manifest_targets(document: dict) -> tuple[DefinitionTarget, ...]:
    version = document.get("schema_version", 2)
    if version not in (2, 3):
        raise ImplementationError(f"unsupported recovered manifest schema {version!r}")
    functions = document.get("functions")
    if not isinstance(functions, list):
        raise ImplementationError("manifest functions must be an array")
    result = []
    identities = set()
    names = set()
    for record in functions:
        if not isinstance(record, dict):
            raise ImplementationError("manifest function must be an object")
        if version == 2 and ("implementation" in record or "adapter" in record):
            raise ImplementationError("implementation mappings require manifest schema 3")
        targets = definition_targets(record)
        identity = targets[0].identity
        if identity in identities:
            raise ImplementationError(f"duplicate recovered identity: {identity}")
        identities.add(identity)
        for target in targets:
            if target.name in names:
                raise ImplementationError(f"duplicate definition target: {target.name}")
            names.add(target.name)
            result.append(target)
    return tuple(result)


def manifest_sources(document: dict) -> list[str]:
    """Return the closed canonical/adapter/state source inventory in path order."""
    # Inventory consumers also use minimal records containing only a source.
    # Full semantic validation belongs to manifest_targets, not enumeration.
    sources = {_source(record.get("source")) for record in document["functions"]}
    for record in document["functions"]:
        if record.get("adapter") is not None:
            if not isinstance(record["adapter"], dict):
                raise ImplementationError("adapter must be an object")
            sources.add(_source(record["adapter"].get("source")))
    if document.get("state_owner"):
        sources.add(_source(document["state_owner"]))
    return sorted(sources)


def resolve_source_definitions(
    text: str, targets: tuple[DefinitionTarget, ...] | list[DefinitionTarget], *, source: str
) -> dict[tuple[str, str], Definition]:
    relevant = [target for target in targets if target.source == source]
    by_name: dict[str, list[Definition]] = {}
    for definition in scan_definitions(text, {target.name for target in relevant}):
        by_name.setdefault(definition.name, []).append(definition)
    resolved = {}
    for target in relevant:
        matches = by_name.get(target.name, [])
        if len(matches) != 1:
            raise ImplementationError(
                f"{target.identity}: expected one {target.role} definition of "
                f"{target.name} in {source}, found {len(matches)}")
        if target.key in resolved:
            raise ImplementationError(f"duplicate definition target: {target.key}")
        resolved[target.key] = matches[0]
    return resolved


def index_manifest_definitions(
    document: dict, root: Path, sources: set[str] | None = None
) -> dict[tuple[str, str], ResolvedDefinition]:
    targets = manifest_targets(document)
    inventory = manifest_sources(document)
    if sources is not None and sources - set(inventory):
        raise ImplementationError(f"sources absent from manifest: {sorted(sources - set(inventory))}")
    by_key = {target.key: target for target in targets}
    result = {}
    for source in inventory:
        if sources is not None and source not in sources:
            continue
        text = (root / source).read_text(encoding="utf-8")
        definitions = resolve_source_definitions(text, targets, source=source)
        for key, definition in definitions.items():
            result[key] = ResolvedDefinition(by_key[key], definition, body_sha256(text, definition))
    return result
