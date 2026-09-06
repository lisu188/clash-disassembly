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


def scan_definitions(text: str, known_names: set[str]) -> list[Definition]:
    """Return file/linkage-scope definitions whose names are in known_names.

    C++ language-linkage blocks do not introduce a declaration scope. Mask
    only their braces so ordinary function and object bodies retain the
    existing balanced scanner's behavior and every source offset stays exact.
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
    segment_start = 0
    cursor = 0
    depth = 0
    while cursor < len(masked):
        char = masked[cursor]
        if char == "{" and depth == 0:
            prefix = masked[segment_start:cursor]
            candidates = [
                match for match in CALL_RE.finditer(prefix)
                if match.group(1) in known_names
            ]
            if candidates:
                match = candidates[0]
                start = segment_start + match.start()
                line_start = masked.rfind("\n", segment_start, start) + 1
                start = line_start
                end = _balanced_end(masked, cursor)
                if end is None:
                    raise ValueError(
                        f"unbalanced definition for {match.group(1)} at line "
                        f"{text.count(chr(10), 0, start) + 1}"
                    )
                definitions.append(
                    Definition(
                        name=match.group(1),
                        start=start,
                        opening_brace=cursor,
                        end=end,
                        line=text.count("\n", 0, start) + 1,
                    )
                )
                cursor = end
                segment_start = end
                continue
            depth = 1
        elif char == "{" and depth > 0:
            depth += 1
        elif char == "}" and depth > 0:
            depth -= 1
            if depth == 0:
                segment_start = cursor + 1
        elif char == ";" and depth == 0:
            segment = masked[segment_start:cursor]
            has_pending_definition = any(
                match.group(1) in known_names for match in CALL_RE.finditer(segment)
            )
            # K&R definitions place parameter declarations (and semicolons)
            # between Name(args) and the opening brace. A prototype or a
            # call-based initializer ends directly after its closing paren.
            if not has_pending_definition or segment.rstrip().endswith(")"):
                segment_start = cursor + 1
        cursor += 1
    return definitions


def body_sha256(text: str, definition: Definition) -> str:
    """Hash the balanced body token stream for a canonical definition."""
    body = text[definition.opening_brace:definition.end]
    tokens = TOKEN_RE.findall(body)
    return hashlib.sha256("\n".join(tokens).encode("utf-8")).hexdigest()
