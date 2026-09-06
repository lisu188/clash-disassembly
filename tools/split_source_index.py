#!/usr/bin/env python3
"""Index balanced recovered function definitions in the canonical split tree."""

from __future__ import annotations

import hashlib
import re
from dataclasses import dataclass


TOKEN_RE = re.compile(
    r"[A-Za-z_][A-Za-z0-9_]*|0[xX][0-9A-Fa-f]+|\d+(?:\.\d+)?|"
    r"==|!=|<=|>=|->|<<|>>|&&|\|\||\+\+|--|[^\s]"
)
CALL_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")
QUALIFIED_CALL_RE = re.compile(
    r"(?<![A-Za-z0-9_:])((?:::)?[A-Za-z_][A-Za-z0-9_]*"
    r"(?:\s*::\s*[A-Za-z_][A-Za-z0-9_]*)*)\s*\("
)
NAMESPACE_RE = re.compile(
    r"\s*(?:inline\s+)?namespace(?:\s+"
    r"([A-Za-z_][A-Za-z0-9_]*(?:\s*::\s*[A-Za-z_][A-Za-z0-9_]*)*))?\s*\Z"
)


@dataclass(frozen=True)
class Definition:
    name: str
    start: int
    opening_brace: int
    end: int
    line: int


def mask_c(text: str) -> str:
    """Blank comments, literals, and directives without changing offsets."""
    chars = list(text)
    index = 0
    state = "code"
    quote = ""
    while index < len(chars):
        char = chars[index]
        following = chars[index + 1] if index + 1 < len(chars) else ""
        if state == "code":
            if char == "/" and following == "/":
                chars[index] = chars[index + 1] = " "
                index += 2
                state = "line-comment"
                continue
            if char == "/" and following == "*":
                chars[index] = chars[index + 1] = " "
                index += 2
                state = "block-comment"
                continue
            if char in ('"', "'"):
                quote = char
                chars[index] = " "
                index += 1
                state = "literal"
                continue
        elif state == "line-comment":
            if char == "\n":
                state = "code"
            else:
                chars[index] = " "
            index += 1
            continue
        elif state == "block-comment":
            if char == "*" and following == "/":
                chars[index] = chars[index + 1] = " "
                index += 2
                state = "code"
                continue
            if char not in "\r\n":
                chars[index] = " "
            index += 1
            continue
        elif state == "literal":
            if char == "\\":
                chars[index] = " "
                if index + 1 < len(chars):
                    if chars[index + 1] not in "\r\n":
                        chars[index + 1] = " "
                    index += 2
                    continue
            if char == quote:
                chars[index] = " "
                state = "code"
            elif char not in "\r\n":
                chars[index] = " "
            index += 1
            continue
        index += 1

    offset = 0
    in_directive = False
    for original in text.splitlines(keepends=True):
        if not in_directive and original.lstrip().startswith("#"):
            in_directive = True
        if in_directive:
            for local_index in range(len(original)):
                if chars[offset + local_index] not in "\r\n":
                    chars[offset + local_index] = " "
            in_directive = original.rstrip("\r\n").endswith("\\")
        offset += len(original)
    return "".join(chars)


def _balanced_end(masked: str, opening: int) -> int | None:
    depth = 1
    cursor = opening + 1
    while cursor < len(masked) and depth:
        if masked[cursor] == "{":
            depth += 1
        elif masked[cursor] == "}":
            depth -= 1
        cursor += 1
    return cursor if depth == 0 else None


def scan_definitions(text: str, known_names: set[str] | None) -> list[Definition]:
    """Return exact free or qualified out-of-line definitions in known_names.

    C++ language-linkage blocks do not introduce a declaration scope. Mask
    their braces while visiting named namespace scopes explicitly. A leaf
    target never matches a qualified method with the same leaf: callers must
    request the method's qualified name. Class bodies (including inline member
    definitions) are deliberately not indexed. Recovered methods are unique,
    non-overloaded, out-of-line definitions; consumers reject duplicate matches.
    """
    masked = mask_c(text)
    linkage_braces = []
    for match in re.finditer(r'\bextern\s+"C(?:\+\+)?"\s*\{', text):
        if masked[match.start():match.start() + 6] != "extern":
            continue  # text in a comment, literal or preprocessor directive
        opening = match.end() - 1
        end = _balanced_end(masked, opening)
        if end is None:
            raise ValueError("unbalanced language-linkage block")
        linkage_braces.extend((opening, end - 1))
    if linkage_braces:
        chars = list(masked)
        for offset in linkage_braces:
            chars[offset] = " "
        masked = "".join(chars)
    definitions: list[Definition] = []

    def candidates(prefix: str, scope: str):
        for match in QUALIFIED_CALL_RE.finditer(prefix):
            spelling = re.sub(r"\s+", "", match.group(1))
            name = spelling[2:] if spelling.startswith("::") else scope + spelling
            if known_names is None:
                # General inventories include reconstruction helpers too.
                # These are ordinary definitions, not constructors, lambdas,
                # initializer calls or compiler annotation expressions.
                before = prefix[:match.start()]
                if (not before.strip() or "=" in before
                        or spelling in {"__attribute__", "__declspec", "alignas",
                                        "decltype", "noexcept", "static_assert"}
                        or spelling.startswith("CLASH95_")):
                    continue
            if known_names is None or name in known_names:
                yield match, name

    def visit(begin: int, limit: int, scope: str) -> None:
        segment_start = begin
        cursor = begin
        while cursor < limit:
            char = masked[cursor]
            if char == "{":
                prefix = masked[segment_start:cursor]
                end = _balanced_end(masked, cursor)
                namespace = NAMESPACE_RE.fullmatch(prefix)
                matches = list(candidates(prefix, scope))
                if end is None:
                    if namespace or matches:
                        raise ValueError("unbalanced definition or namespace at line "
                                         f"{text.count(chr(10), 0, cursor) + 1}")
                    return
                if namespace:
                    component = re.sub(r"\s+", "", namespace.group(1) or "")
                    child_scope = scope + (component + "::" if component else "")
                    visit(cursor + 1, end - 1, child_scope)
                elif matches:
                    match, name = matches[0]
                    start = segment_start + match.start()
                    start = max(segment_start, masked.rfind("\n", segment_start, start) + 1)
                    definitions.append(Definition(
                        name=name, start=start, opening_brace=cursor, end=end,
                        line=text.count("\n", 0, start) + 1))
                cursor = end
                segment_start = end
                continue
            if char == ";":
                segment = masked[segment_start:cursor]
                # K&R definitions retain parameter declarations between the
                # parameter list and `{`. C++ trailing qualifiers/attributes
                # must not make an ordinary prototype consume the next body.
                pending_knr = False
                for match, _ in candidates(segment, scope):
                    opening = segment.find("(", match.start(), match.end())
                    closing = segment.find(")", opening)
                    parameters = segment[opening + 1:closing].strip()
                    identifiers = re.fullmatch(
                        r"[A-Za-z_][A-Za-z0-9_]*(?:\s*,\s*[A-Za-z_][A-Za-z0-9_]*)*",
                        parameters)
                    parameter_names = {part.strip() for part in parameters.split(",")}
                    tail = segment[closing + 1:].strip()
                    if (closing >= 0 and identifiers and tail
                            and not parameter_names.intersection({"void", "int", "char", "long",
                                                                 "short", "float", "double",
                                                                 "unsigned", "signed", "bool"})
                            and not tail.startswith(("const", "noexcept", "volatile", "__asm__",
                                                     "__attribute__", "CLASH95_", "&", ")"))):
                        pending_knr = True
                if not pending_knr:
                    segment_start = cursor + 1
            cursor += 1

    visit(0, len(masked), "")
    return definitions


def body_sha256(text: str, definition: Definition) -> str:
    """Hash the balanced body token stream for a canonical definition."""
    body = text[definition.opening_brace:definition.end]
    tokens = TOKEN_RE.findall(body)
    return hashlib.sha256("\n".join(tokens).encode("utf-8")).hexdigest()
