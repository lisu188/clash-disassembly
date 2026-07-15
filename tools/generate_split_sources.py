#!/usr/bin/env python3
"""Generate independently compiled recovered-C translation units.

The recovered implementation is currently represented by one ordered include
manifest (clash95.c).  This tool keeps that file as the migration oracle while
materialising real C translation units under src/recovered/split/.

Function boundaries come from the original-address marker comments rather than
from a C parser.  That is deliberate: the recovered source still contains K&R
definitions and compiler-shaped declarations which generic C parsers reject.
GCC's ``-aux-info`` output supplies the normalized function declarations used
by the private split-build header.
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import shutil
import subprocess
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ORACLE_MANIFEST = ROOT / "clash95.c"
SPLIT_ROOT = ROOT / "src" / "recovered" / "split"
MANIFEST_PATH = ROOT / "data" / "recovered_sources.json"
PATH_MAP_PATH = ROOT / "docs" / "SOURCE_PATH_MAP.csv"
PURE_SET_PATH = ROOT / "tests" / "unit" / "pure_set.json"
CANONICAL_API_HEADERS = (
    ROOT / "src" / "platform" / "platform_sdl.h",
    ROOT / "src" / "compatibility" / "defs.h",
    ROOT / "src" / "instrumentation" / "runtime_mission_trace.h",
)

INCLUDE_RE = re.compile(r'^#include\s+"([^"]+)"\s*$', re.MULTILINE)
MARKER_RE = re.compile(
    r"(?m)^//----- \(([0-9A-Fa-f]{8})\) [-]+\r?$"
)
AUX_RECORD_RE = re.compile(r"(?m)^/\* ([^:]+(?:/[^:]+)*):(\d+):(NF|OF) \*/ ")
TYPEDEF_STRUCT_RE = re.compile(
    r"(?ms)^typedef\s+struct\s+[A-Za-z_][A-Za-z0-9_]*\s*\{.*?^\}\s*"
    r"[A-Za-z_][A-Za-z0-9_]*\s*;"
)


@dataclass(frozen=True)
class FunctionDecl:
    source: str
    line: int
    storage: str
    name: str
    declaration: str


@dataclass
class TopLevelItem:
    kind: str
    raw: str
    start_line: int


@dataclass
class MarkerChunk:
    address: str
    raw: str
    start_line: int
    end_line: int


def repo_rel(path: Path) -> str:
    return path.resolve().relative_to(ROOT).as_posix()


def ordered_oracle_sources() -> list[Path]:
    text = ORACLE_MANIFEST.read_text(encoding="utf-8")
    sources = [ROOT / match for match in INCLUDE_RE.findall(text)]
    if not sources:
        raise SystemExit("clash95.c contains no recovered source includes")
    for source in sources:
        if not source.is_file():
            raise SystemExit(f"oracle source is missing: {source}")
    return sources


def mask_c(text: str) -> str:
    """Blank comments, literals, and preprocessor lines without moving offsets."""
    chars = list(text)
    i = 0
    state = "code"
    quote = ""
    while i < len(chars):
        ch = chars[i]
        nxt = chars[i + 1] if i + 1 < len(chars) else ""
        if state == "code":
            if ch == "/" and nxt == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "line_comment"
                continue
            if ch == "/" and nxt == "*":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "block_comment"
                continue
            if ch in ('"', "'"):
                quote = ch
                chars[i] = " "
                i += 1
                state = "literal"
                continue
        elif state == "line_comment":
            if ch == "\n":
                state = "code"
            else:
                chars[i] = " "
            i += 1
            continue
        elif state == "block_comment":
            if ch == "*" and nxt == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "code"
                continue
            if ch != "\n":
                chars[i] = " "
            i += 1
            continue
        elif state == "literal":
            if ch == "\\":
                chars[i] = " "
                if i + 1 < len(chars):
                    if chars[i + 1] != "\n":
                        chars[i + 1] = " "
                    i += 2
                    continue
            if ch == quote:
                chars[i] = " "
                state = "code"
            elif ch != "\n":
                chars[i] = " "
            i += 1
            continue
        i += 1

    # A directive can contain braces, semicolons, or continuations.  It is
    # declaration context, never a top-level C item by itself for our inputs.
    lines = "".join(chars).splitlines(keepends=True)
    in_directive = False
    offset = 0
    for original_line, masked_line in zip(text.splitlines(keepends=True), lines):
        stripped = original_line.lstrip()
        if not in_directive and stripped.startswith("#"):
            in_directive = True
        if in_directive:
            for j, value in enumerate(masked_line):
                if value != "\n" and value != "\r":
                    chars[offset + j] = " "
            in_directive = original_line.rstrip("\r\n").endswith("\\")
        offset += len(masked_line)
    return "".join(chars)


def looks_like_function(prefix: str) -> bool:
    stripped = prefix.strip()
    if not stripped or stripped.startswith(("typedef", "struct", "union", "enum")):
        return False
    if "=" in stripped:
        return False
    return bool(re.search(r"[A-Za-z_][A-Za-z0-9_]*\s*\([^{}]*\)\s*$", stripped, re.S))


def split_top_level(text: str) -> list[TopLevelItem]:
    masked = mask_c(text)
    items: list[TopLevelItem] = []
    start = 0
    i = 0
    brace = paren = bracket = 0
    while i < len(masked):
        ch = masked[i]
        if ch == "(" and brace == 0:
            paren += 1
        elif ch == ")" and brace == 0 and paren:
            paren -= 1
        elif ch == "[" and brace == 0:
            bracket += 1
        elif ch == "]" and brace == 0 and bracket:
            bracket -= 1
        elif ch == "{" and brace == 0 and paren == 0 and bracket == 0:
            if looks_like_function(masked[start:i]):
                depth = 1
                j = i + 1
                while j < len(masked) and depth:
                    if masked[j] == "{":
                        depth += 1
                    elif masked[j] == "}":
                        depth -= 1
                    j += 1
                if depth:
                    raise SystemExit("unterminated top-level function body in prelude")
                raw = text[start:j]
                items.append(
                    TopLevelItem("function", raw, text.count("\n", 0, start) + 1)
                )
                start = j
                i = j
                brace = paren = bracket = 0
                continue
            brace = 1
        elif ch == "{" and brace:
            brace += 1
        elif ch == "}" and brace:
            brace -= 1
        elif ch == ";" and brace == 0 and paren == 0 and bracket == 0:
            end = i + 1
            raw = text[start:end]
            items.append(
                TopLevelItem("declaration", raw, text.count("\n", 0, start) + 1)
            )
            start = end
        i += 1
    if text[start:].strip():
        items.append(TopLevelItem("trivia", text[start:], text.count("\n", 0, start) + 1))
    return items


def core_offset(raw: str) -> int:
    masked = mask_c(raw)
    match = re.search(r"\S", masked)
    return match.start() if match else len(raw)


def declaration_core(raw: str) -> tuple[str, str]:
    offset = core_offset(raw)
    return raw[:offset], raw[offset:]


def is_type_declaration(core: str) -> bool:
    stripped = core.lstrip()
    if stripped.startswith("typedef"):
        return True
    if stripped.startswith("enum") and "{" in stripped:
        tail = stripped.rsplit("}", 1)[-1].strip() if "}" in stripped else ""
        return tail == ";"
    if stripped.startswith(("struct", "union")) and "{" in stripped:
        tail = stripped.rsplit("}", 1)[-1].strip() if "}" in stripped else ""
        return tail == ";"
    return False


def is_function_declaration(core: str) -> bool:
    masked = mask_c(core).strip()
    if not masked.endswith(";") or masked.startswith("typedef"):
        return False
    masked = masked[:-1].rstrip()
    if top_level_equal(masked) is not None:
        return False
    depth = 0
    for i, ch in enumerate(masked):
        if ch == "(":
            if depth == 0:
                if masked[i + 1 :].lstrip().startswith("*"):
                    return False
                name = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*$", masked[:i])
                if not name or name.group(1) in {
                    "if", "for", "while", "switch", "sizeof", "int", "char",
                    "short", "long", "void", "float", "double", "unsigned",
                    "signed", "struct", "union", "enum",
                    "__attribute__",
                }:
                    return False
                return True
            depth += 1
        elif ch == ")" and depth:
            depth -= 1
    return False


def top_level_equal(text: str) -> int | None:
    masked = mask_c(text)
    paren = bracket = brace = 0
    for i, ch in enumerate(masked):
        if ch == "(":
            paren += 1
        elif ch == ")" and paren:
            paren -= 1
        elif ch == "[":
            bracket += 1
        elif ch == "]" and bracket:
            bracket -= 1
        elif ch == "{":
            brace += 1
        elif ch == "}" and brace:
            brace -= 1
        elif ch == "=" and paren == 0 and bracket == 0 and brace == 0:
            return i
    return None


def promote_static(core: str) -> str:
    return re.sub(r"^\s*static\s+", "CLASH95_INTERNAL ", core, count=1)


def extern_variable(prefix: str, core: str) -> str:
    core = core.strip()
    internal = bool(re.match(r"^static\s+", core))
    equal = top_level_equal(core)
    if equal is not None:
        declaration = core[:equal].rstrip()
        extent = proven_initializer_extent(core[equal + 1 :])
        if extent is not None:
            declaration = re.sub(
                r"\[\s*\]", f"[{extent}]", declaration, count=1
            )
        core = declaration + ";"
    core = re.sub(r"^static\s+", "", core, count=1)
    if not core.startswith("extern "):
        core = ("extern CLASH95_INTERNAL " if internal else "extern ") + core
    return prefix + core + "\n"


def proven_initializer_extent(initializer: str) -> int | None:
    """Return the element count proven by a top-level brace initializer."""
    masked = mask_c(initializer)
    start = masked.find("{")
    if start < 0:
        return None
    brace = paren = bracket = 0
    commas = 0
    end = None
    for position in range(start, len(masked)):
        character = masked[position]
        if character == "{" and paren == 0 and bracket == 0:
            brace += 1
        elif character == "}" and paren == 0 and bracket == 0:
            brace -= 1
            if brace == 0:
                end = position
                break
        elif character == "(" and brace:
            paren += 1
        elif character == ")" and paren:
            paren -= 1
        elif character == "[" and brace:
            bracket += 1
        elif character == "]" and bracket:
            bracket -= 1
        elif character == "," and brace == 1 and paren == 0 and bracket == 0:
            commas += 1
    if end is None:
        return None
    # mask_c deliberately blanks literals, so use the same-position original
    # slice to distinguish an empty initializer from a one-element character
    # or string initializer. Comma counting remains based on masked C syntax.
    contents = initializer[start + 1 : end].strip()
    if not contents:
        return 0
    masked_contents = masked[start + 1 : end]
    return commas if masked_contents.rstrip().endswith(",") else commas + 1


def state_variable(core: str) -> str:
    core = core.strip()
    internal = bool(re.match(r"^static\s+", core))
    core = re.sub(r"^static\s+", "", core, count=1)
    return ("CLASH95_INTERNAL " if internal else "") + core + "\n"


def function_prototype(raw: str) -> str:
    prefix, core = declaration_core(raw)
    brace = mask_c(core).find("{")
    if brace < 0:
        raise SystemExit("could not locate function body opening")
    signature = promote_static(core[:brace].rstrip())
    return prefix + signature + ";\n"


def function_name_and_opening(declaration: str) -> tuple[str, int, bool] | None:
    masked = mask_c(declaration)
    pointer_return = re.search(
        r"\(\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\(", masked
    )
    if pointer_return:
        return pointer_return.group(1), pointer_return.end() - 1, True
    opening = masked.find("(")
    if opening < 0:
        return None
    match = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*$", masked[:opening])
    if not match:
        return None
    return match.group(1), opening, False


def declared_function_name(core: str) -> str | None:
    parsed = function_name_and_opening(core)
    return parsed[0] if parsed else None


def build_prelude_outputs(
    prelude: Path,
) -> tuple[str, str, list[tuple[int, str]], set[str]]:
    text = prelude.read_text(encoding="utf-8")
    # Keep source line numbers stable so GCC -aux-info records continue to map
    # exactly to the extracted helper definitions.
    text = re.sub(
        r"(?m)^#include[^\n]*(?:\n|$)",
        lambda match: "\n" * match.group(0).count("\n"),
        text,
    )
    header: list[str] = []
    state: list[str] = []
    helpers: list[tuple[int, str]] = []
    declared_functions: set[str] = set()
    for item in split_top_level(text):
        if item.kind == "function":
            header.append(function_prototype(item.raw))
            definition_line = item.start_line + item.raw[
                : core_offset(item.raw)
            ].count("\n")
            helpers.append(
                (
                    definition_line,
                    re.sub(
                        r"(?m)^static\s+",
                        "CLASH95_INTERNAL ",
                        item.raw,
                        count=1,
                    ),
                )
            )
            name = declared_function_name(declaration_core(item.raw)[1])
            if name:
                declared_functions.add(name)
            continue
        if item.kind != "declaration":
            header.append(item.raw)
            continue
        prefix, core = declaration_core(item.raw)
        stripped = core.lstrip()
        if is_type_declaration(core):
            header.append(item.raw)
        elif is_function_declaration(core):
            header.append(prefix + promote_static(core))
            name = declared_function_name(core)
            if name:
                declared_functions.add(name)
        elif stripped.startswith("extern "):
            header.append(item.raw)
        else:
            header.append(extern_variable(prefix, core))
            state.append(state_variable(core))
    return "".join(header), "\n".join(state), helpers, declared_functions


def parse_aux(path: Path) -> list[FunctionDecl]:
    text = path.read_text(encoding="utf-8", errors="replace")
    starts = list(AUX_RECORD_RE.finditer(text))
    records: list[FunctionDecl] = []
    for index, match in enumerate(starts):
        end = starts[index + 1].start() if index + 1 < len(starts) else len(text)
        block = text[match.end() : end]
        semicolon = block.find(";")
        if semicolon < 0:
            continue
        declaration = block[: semicolon + 1].strip()
        parsed_name = function_name_and_opening(declaration)
        if not parsed_name:
            continue
        name, opening, returns_function_pointer = parsed_name
        source = match.group(1).replace("\\", "/")
        if not source.startswith("src/recovered/"):
            continue
        # The mechanical split must preserve the unified translation unit's
        # unspecified-parameter call semantics.  GCC's aux-info spelling is a
        # useful return-type oracle, but turning every K&R definition into a
        # full prototype here would change default argument promotion and can
        # reject historically accepted call sites.  Prototypes are recovered
        # later, one evidence-backed family at a time.
        if match.group(3) == "OF" and not returns_function_pointer:
            declaration = declaration[:opening].rstrip() + "();"
        declaration = re.sub(r"^static\s+", "CLASH95_INTERNAL ", declaration)
        records.append(
            FunctionDecl(source, int(match.group(2)), match.group(3), name, declaration)
        )
    return records


def commented_external_declarations(
    prelude: Path,
    declared_functions: set[str],
    aux_decls: list[FunctionDecl],
) -> list[str]:
    """Recover return types for commented legacy-import declarations.

    Parameter lists intentionally remain unspecified during the mechanical
    split.  Several Hex-Rays comments omit register arguments, so promoting
    those guesses to C17 prototypes would change accepted call shapes.
    """
    reserved = set(declared_functions)
    reserved.update(record.name for record in aux_decls)
    for header in CANONICAL_API_HEADERS:
        text = header.read_text(encoding="utf-8")
        reserved.update(
            re.findall(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", text)
        )

    result: list[str] = []
    seen: set[str] = set()
    text = prelude.read_text(encoding="utf-8")
    for match in re.finditer(
        r"(?m)^//\s*([^\n;`]+\([^;\n]*\)\s*;)(?:\s*weak)?\s*$", text
    ):
        declaration = match.group(1).strip()
        parsed = function_name_and_opening(declaration)
        if not parsed:
            continue
        name, opening, returns_function_pointer = parsed
        if "." in declaration[:opening] or "::" in declaration:
            continue
        if re.search(r"\(\s*\*", declaration) and not returns_function_pointer:
            continue
        if name in reserved or name in seen:
            continue
        if not returns_function_pointer:
            declaration = declaration[:opening].rstrip() + "();"
        result.append(declaration)
        seen.add(name)
    return result


def marker_chunks(path: Path) -> list[MarkerChunk]:
    text = path.read_text(encoding="utf-8")
    matches = list(MARKER_RE.finditer(text))
    chunks: list[MarkerChunk] = []
    for index, match in enumerate(matches):
        end = matches[index + 1].start() if index + 1 < len(matches) else len(text)
        raw = text[match.start() : end]
        start_line = text.count("\n", 0, match.start()) + 1
        end_line = text.count("\n", 0, end) + 1
        chunks.append(MarkerChunk(match.group(1).upper(), raw, start_line, end_line))
    return chunks


def subsystem_for(path: Path) -> str:
    parts = path.relative_to(ROOT / "src" / "recovered").parts
    if parts[0] == "rules":
        return "strategic" if parts[1] == "strategic" else "clips"
    if parts[0] == "world_and_persistence":
        return "persistence"
    if parts[0] == "prelude":
        return "state"
    return parts[0]


def promote_file_scope_static(text: str) -> str:
    # Recovered file-scope declarations are column-zero. Function-local static
    # declarations retain indentation and therefore remain local.
    return re.sub(r"(?m)^static\s+", "CLASH95_INTERNAL ", text)


def extract_fragment_types(sources: list[Path]) -> tuple[str, dict[Path, str]]:
    declarations: list[str] = []
    rewritten: dict[Path, str] = {}
    for source in sources:
        text = source.read_text(encoding="utf-8")
        if source.name == "00000000_clash95_prelude.inc.c":
            rewritten[source] = text
            continue
        matches = list(TYPEDEF_STRUCT_RE.finditer(text))
        for match in matches:
            declarations.append(match.group(0).strip() + "\n")
        for match in reversed(matches):
            replacement = (
                "/* Type declaration moved to recovered_internal.h. */"
                + "\n" * match.group(0).count("\n")
            )
            text = text[: match.start()] + replacement + text[match.end() :]
        rewritten[source] = text
    return "\n".join(declarations), rewritten


def fragment_static_variable_decls(sources: list[Path]) -> list[str]:
    declarations: list[str] = []
    pattern = re.compile(
        r"(?m)^static\s+(?!.*\()([^;\n]+[A-Za-z_][A-Za-z0-9_]*"
        r"(?:\[[^;\n]*\])?)\s*;\s*(?://[^\n]*)?$"
    )
    for source in sources:
        if source.name == "00000000_clash95_prelude.inc.c":
            continue
        for match in pattern.finditer(source.read_text(encoding="utf-8")):
            declarations.append(
                "extern CLASH95_INTERNAL " + match.group(1).strip() + ";"
            )
    return declarations


def safe_reset_split_root() -> None:
    resolved = SPLIT_ROOT.resolve()
    expected_parent = (ROOT / "src" / "recovered").resolve()
    if resolved.parent != expected_parent or resolved.name != "split":
        raise SystemExit(f"refusing to reset unexpected split path: {resolved}")
    if resolved.exists():
        shutil.rmtree(resolved)
    resolved.mkdir(parents=True)


def group_chunks(chunks: list[MarkerChunk], max_lines: int) -> list[list[MarkerChunk]]:
    groups: list[list[MarkerChunk]] = []
    current: list[MarkerChunk] = []
    current_lines = 0
    conditional_depth = 0
    for chunk in chunks:
        lines = chunk.raw.count("\n") + 1
        if current and current_lines + lines > max_lines and conditional_depth == 0:
            groups.append(current)
            current = []
            current_lines = 0
        current.append(chunk)
        current_lines += lines
        for directive in re.finditer(
            r"(?m)^\s*#\s*(if|ifdef|ifndef|endif)\b", chunk.raw
        ):
            if directive.group(1) == "endif":
                conditional_depth -= 1
                if conditional_depth < 0:
                    raise SystemExit("unbalanced #endif in recovered fragment")
            else:
                conditional_depth += 1
    if current:
        groups.append(current)
    if conditional_depth:
        raise SystemExit("unterminated conditional in recovered fragment")
    return groups


def body_hash(text: str) -> str:
    masked = mask_c(text)
    brace = masked.find("{")
    body = text[brace:] if brace >= 0 else text
    tokens = re.findall(
        r"[A-Za-z_][A-Za-z0-9_]*|0[xX][0-9A-Fa-f]+|\d+(?:\.\d+)?|"
        r"==|!=|<=|>=|->|<<|>>|&&|\|\||\+\+|--|[^\s]",
        body,
    )
    return hashlib.sha256("\n".join(tokens).encode("utf-8")).hexdigest()


def write_generated_header(
    prelude_header: str,
    fragment_types: str,
    aux_decls: list[FunctionDecl],
    static_variables: list[str],
    constant_guard: str,
    declared_functions: set[str],
    commented_externals: list[str],
    local_functions: set[str],
) -> None:
    pure_document = json.loads(PURE_SET_PATH.read_text(encoding="utf-8"))
    pure_names = {record["name"] for record in pure_document["functions"]}
    test_visible_functions = local_functions & pure_names
    prelude_header = prelude_header.replace(
        "Included by clash95.c; not a standalone translation unit.",
        "Private recovered declarations shared by split translation units.",
    )
    declarations = "\n".join(
        record.declaration
        for record in aux_decls
        if record.name not in declared_functions and record.name not in local_functions
    )
    test_declarations = "\n".join(
        re.sub(
            r"^CLASH95_INTERNAL\s+",
            "CLASH95_TEST_VISIBLE ",
            record.declaration,
        )
        for record in aux_decls
        if record.name in test_visible_functions
    )
    filtered_prelude: list[str] = []
    for item in split_top_level(prelude_header):
        if item.kind == "declaration":
            _, core = declaration_core(item.raw)
            if is_function_declaration(core):
                name = declared_function_name(core)
                if name in local_functions:
                    continue
        filtered_prelude.append(item.raw)
    prelude_header = "".join(filtered_prelude)
    generated_notice = "/* Generated by tools/generate_split_sources.py; do not edit. */"
    abi_text = f"""{generated_notice}
#ifndef CLASH95_RECOVERED_ABI_H
#define CLASH95_RECOVERED_ABI_H

#include "../../platform/platform_sdl.h"
#include "../../compatibility/defs.h"
#include "../../instrumentation/runtime_mission_trace.h"
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__GNUC__) || defined(__clang__)
#define CLASH95_INTERNAL __attribute__((visibility("hidden")))
#define CLASH95_UNUSED __attribute__((unused))
#else
#define CLASH95_INTERNAL
#define CLASH95_UNUSED
#endif
#ifdef CLASH95_TESTING
#define CLASH95_TEST_VISIBLE
#else
#define CLASH95_TEST_VISIBLE static CLASH95_UNUSED
#endif
#define CLASH95_LOCAL static CLASH95_UNUSED

#endif
"""
    foundation_text = f"""{generated_notice}
#ifndef CLASH95_RECOVERED_FOUNDATION_H
#define CLASH95_RECOVERED_FOUNDATION_H

#include "recovered_abi.h"

{prelude_header}

/* Types originally introduced inside recovered implementation fragments. */
{fragment_types}

/* File-local state promoted during translation-unit extraction. */
{chr(10).join(static_variables)}

#endif
"""
    functions_text = f"""{generated_notice}
#ifndef CLASH95_RECOVERED_FUNCTIONS_H
#define CLASH95_RECOVERED_FUNCTIONS_H

#include "recovered_foundation.h"

/* Legacy imports whose return types are retained from decompiler comments. */
{chr(10).join(commented_externals)}

/* Normalized declarations for every recovered function definition. */
{declarations}

#ifdef CLASH95_TESTING
/* Frozen pure helpers exported only by coverage/test builds. */
{test_declarations}
#endif

#endif
"""
    layout_text = f"""{generated_notice}
#ifndef CLASH95_RECOVERED_LAYOUT_H
#define CLASH95_RECOVERED_LAYOUT_H

#include "recovered_foundation.h"

/* Compile-time guards generated from recovered constants. */
{constant_guard}

#endif
"""
    internal_text = f"""{generated_notice}
#ifndef CLASH95_RECOVERED_INTERNAL_H
#define CLASH95_RECOVERED_INTERNAL_H

/* Temporary migration umbrella. Domain translation units include this until
 * their private declarations can be narrowed without changing recovered ABI. */
#include "recovered_functions.h"
#include "recovered_layout.h"

#endif
"""
    generated_headers = {
        "recovered_abi.h": abi_text,
        "recovered_foundation.h": foundation_text,
        "recovered_functions.h": functions_text,
        "recovered_layout.h": layout_text,
        "recovered_internal.h": internal_text,
    }
    for name, text in generated_headers.items():
        (SPLIT_ROOT / name).write_text(text, encoding="utf-8", newline="\n")


def write_state_source(state_text: str) -> Path:
    directory = SPLIT_ROOT / "state"
    directory.mkdir(parents=True, exist_ok=True)
    path = directory / "00000000_0054FFFF_recovered_state.c"
    path.write_text(
        "/* Generated recovered global-state owner. */\n"
        '#include "../recovered_internal.h"\n\n'
        + state_text,
        encoding="utf-8",
        newline="\n",
    )
    return path


def write_helper_source(helpers: list[tuple[int, str]], aux: list[FunctionDecl]) -> tuple[Path, list[dict]]:
    directory = SPLIT_ROOT / "state"
    directory.mkdir(parents=True, exist_ok=True)
    path = directory / "00000000_00000000_prelude_helpers.c"
    body = "\n\n".join(raw.strip() for _, raw in helpers) + "\n"
    path.write_text(
        "/* Generated recovered prelude helpers. */\n"
        '#include "../recovered_internal.h"\n\n'
        + body,
        encoding="utf-8",
        newline="\n",
    )
    helper_lines = {line for line, _ in helpers}
    records = []
    for declaration in aux:
        if declaration.source.endswith("00000000_clash95_prelude.inc.c") and declaration.line in helper_lines:
            records.append(
                {
                    "name": declaration.name,
                    "original_address": None,
                    "original_source": declaration.source,
                    "original_line": declaration.line,
                    "source": repo_rel(path),
                    "linkage": "internal",
                    "body_sha256": body_hash(next(raw for line, raw in helpers if line == declaration.line)),
                }
            )
    return path, records


def localize_internal_functions(
    functions: list[dict],
    generated_sources: list[Path],
    aux_decls: list[FunctionDecl],
    prelude_header: str,
) -> set[str]:
    """Keep truly file-local recovered helpers static in production.

    Frozen pure helpers use CLASH95_TEST_VISIBLE so only coverage builds export
    them. Helpers referenced from another generated source (or a shared prelude
    macro) retain hidden cross-translation-unit linkage.
    """
    pure_document = json.loads(PURE_SET_PATH.read_text(encoding="utf-8"))
    pure_names = {record["name"] for record in pure_document["functions"]}
    source_text = {
        path.resolve(): path.read_text(encoding="utf-8") for path in generated_sources
    }
    masked_text = {path: mask_c(text) for path, text in source_text.items()}
    aux_by_name = {record.name: record for record in aux_decls}
    local_records: list[dict] = []
    for record in functions:
        if record["linkage"] != "internal":
            continue
        name = record["name"]
        defining_path = (ROOT / record["source"]).resolve()
        reference = re.compile(rf"\b{re.escape(name)}\b")
        if any(
            path != defining_path and reference.search(text)
            for path, text in masked_text.items()
        ):
            continue
        # A second prelude occurrence can be a shared macro use rather than the
        # declaration itself, so retain hidden linkage in that ambiguous case.
        if len(reference.findall(prelude_header)) > 1:
            continue
        local_records.append(record)

    prototypes: dict[Path, list[str]] = {}
    for record in local_records:
        name = record["name"]
        path = (ROOT / record["source"]).resolve()
        macro = "CLASH95_TEST_VISIBLE" if name in pure_names else "CLASH95_LOCAL"
        pattern = re.compile(
            rf"\bCLASH95_INTERNAL\b(?=[^;{{}}]*\b{re.escape(name)}\b)"
        )
        definition_match = pattern.search(masked_text[path])
        if definition_match is None:
            raise SystemExit(f"could not locate generated definition: {name}")
        updated, replacements = pattern.subn(macro, source_text[path], count=1)
        if replacements != 1:
            raise SystemExit(f"could not localize generated definition: {name}")
        source_text[path] = updated
        declaration = aux_by_name[name].declaration
        declaration = re.sub(r"^CLASH95_INTERNAL\s+", macro + " ", declaration)
        prototypes.setdefault(path, []).append(declaration)
        record["linkage"] = (
            "test-visible-static" if name in pure_names else "static"
        )

    include_line = '#include "../recovered_internal.h"\n'
    for path, declarations in prototypes.items():
        insertion = "\n" + "\n".join(declarations) + "\n"
        if source_text[path].count(include_line) != 1:
            raise SystemExit(f"unexpected generated include layout: {repo_rel(path)}")
        source_text[path] = source_text[path].replace(
            include_line, include_line + insertion, 1
        )
    for path, text in source_text.items():
        path.write_text(text, encoding="utf-8", newline="\n")
    return {record["name"] for record in local_records}


def write_function_groups(
    sources: list[Path],
    rewritten: dict[Path, str],
    aux: list[FunctionDecl],
    max_lines: int,
) -> tuple[dict[str, list[Path]], list[dict]]:
    by_subsystem: dict[str, list[Path]] = {}
    manifest_functions: list[dict] = []
    aux_by_source: dict[str, list[FunctionDecl]] = {}
    for record in aux:
        aux_by_source.setdefault(record.source, []).append(record)

    for source in sources:
        if source.name in {
            "00000000_clash95_prelude.inc.c",
            "005_constant_guard.inc.c",
        }:
            continue
        relative = repo_rel(source)
        text = rewritten[source]
        original_lines = source.read_text(encoding="utf-8").splitlines(
            keepends=True
        )
        source_records = sorted(
            aux_by_source.get(relative, []), key=lambda record: record.line
        )
        next_definition_line = {
            record.line: (
                source_records[index + 1].line
                if index + 1 < len(source_records)
                else len(original_lines) + 1
            )
            for index, record in enumerate(source_records)
        }
        matches = list(MARKER_RE.finditer(text))
        chunks: list[MarkerChunk] = []
        for index, match in enumerate(matches):
            end = matches[index + 1].start() if index + 1 < len(matches) else len(text)
            chunks.append(
                MarkerChunk(
                    match.group(1).upper(),
                    text[match.start() : end],
                    text.count("\n", 0, match.start()) + 1,
                    text.count("\n", 0, end) + 1,
                )
            )
        if not chunks:
            continue
        subsystem = subsystem_for(source)
        directory = SPLIT_ROOT / subsystem
        directory.mkdir(parents=True, exist_ok=True)
        for sequence, group in enumerate(group_chunks(chunks, max_lines), 1):
            first = group[0].address
            last = group[-1].address
            output = directory / f"{first}_{last}_{subsystem}_{sequence:03d}.c"
            raw = promote_file_scope_static("".join(chunk.raw for chunk in group))
            output.write_text(
                f"/* Generated from {relative}; original address order retained. */\n"
                '#include "../recovered_internal.h"\n\n'
                + raw.rstrip()
                + "\n",
                encoding="utf-8",
                newline="\n",
            )
            by_subsystem.setdefault(subsystem, []).append(output)
            start_line = group[0].start_line
            end_line = group[-1].end_line
            group_records = [
                record
                for record in aux_by_source.get(relative, [])
                if start_line <= record.line < end_line
            ]
            for record in group_records:
                address = None
                for chunk in group:
                    if chunk.start_line <= record.line < chunk.end_line:
                        address = chunk.address
                        break
                manifest_functions.append(
                    {
                        "name": record.name,
                        "original_address": f"0x{address}" if address else None,
                        "original_source": relative,
                        "original_line": record.line,
                        "source": repo_rel(output),
                        "linkage": "internal" if record.declaration.startswith("CLASH95_INTERNAL") else "external",
                        "body_sha256": body_hash(
                            "".join(
                                original_lines[
                                    record.line - 1 : next_definition_line[
                                        record.line
                                    ]
                                    - 1
                                ]
                            )
                        ),
                    }
                )
    return by_subsystem, manifest_functions


def write_cmake_sources(by_subsystem: dict[str, list[Path]], state_sources: list[Path]) -> None:
    lines = ["# Generated by tools/generate_split_sources.py; do not edit.", ""]
    all_groups = {"state": state_sources, **by_subsystem}
    for subsystem, paths in sorted(all_groups.items()):
        variable = f"CLASH95_SPLIT_{subsystem.upper()}_SOURCES"
        lines.append(f"set({variable}")
        for path in paths:
            lines.append(f"  ${{CMAKE_CURRENT_SOURCE_DIR}}/{repo_rel(path)}")
        lines.append(")")
        lines.append("")
    (SPLIT_ROOT / "sources.cmake").write_text("\n".join(lines), encoding="utf-8", newline="\n")


def write_manifest(functions: list[dict], state_source: Path, source_files: list[Path]) -> None:
    functions.sort(key=lambda item: (item["original_source"], item["original_line"], item["name"]))
    ordered_addresses = sorted(
        {
            int(item["original_address"], 16)
            for item in functions
            if item["original_address"] is not None
        }
    )
    address_ends = {
        address: (
            ordered_addresses[index + 1]
            if index + 1 < len(ordered_addresses)
            else None
        )
        for index, address in enumerate(ordered_addresses)
    }
    state_owner = repo_rel(state_source)
    for item in functions:
        start = (
            int(item["original_address"], 16)
            if item["original_address"] is not None
            else None
        )
        item["original_address_range"] = {
            "start": f"0x{start:08X}" if start is not None else None,
            "end_exclusive": (
                f"0x{address_ends[start]:08X}"
                if start is not None and address_ends[start] is not None
                else None
            ),
        }
        item["subsystem"] = Path(item["source"]).parent.name
        item["state_owner"] = state_owner
        item["legacy_path"] = item["original_source"]
    payload = {
        "schema_version": 1,
        "language": "GNU C17",
        "oracle_manifest": "clash95.c",
        "state_owner": state_owner,
        "source_file_count": len(source_files),
        "function_count": len(functions),
        "functions": functions,
    }
    MANIFEST_PATH.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8", newline="\n")


def write_path_map(sources: list[Path], generated: list[Path]) -> None:
    rows: list[tuple[str, str, str]] = []
    generated_by_subsystem: dict[str, list[str]] = {}
    for path in generated:
        generated_by_subsystem.setdefault(path.parent.name, []).append(repo_rel(path))
    for source in sources:
        subsystem = subsystem_for(source)
        replacements = generated_by_subsystem.get(subsystem, [])
        rows.append((repo_rel(source), " ".join(replacements), "oracle_fragment"))
    tracked = subprocess.run(
        ["git", "ls-files", "-s", "-z"],
        cwd=ROOT,
        check=True,
        capture_output=True,
    ).stdout.decode("utf-8", errors="surrogateescape")
    for record in tracked.split("\0"):
        if not record.startswith("120000 "):
            continue
        legacy = record.split("\t", 1)[1]
        legacy_path = ROOT / legacy
        if legacy_path.is_symlink():
            target_text = str(legacy_path.readlink())
        else:
            target_text = legacy_path.read_text(encoding="utf-8").strip()
        canonical = (legacy_path.parent / target_text).resolve()
        canonical_relative = repo_rel(canonical)
        source_match = next(
            (source for source in sources if source.resolve() == canonical), None
        )
        if source_match is not None:
            replacements = generated_by_subsystem.get(
                subsystem_for(source_match), []
            )
        else:
            replacements = [canonical_relative]
        rows.append((legacy, " ".join(replacements), "compatibility_symlink"))
    with PATH_MAP_PATH.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.writer(handle, lineterminator="\n")
        writer.writerow(["legacy_path", "replacement_paths", "status"])
        writer.writerows(rows)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--aux", required=True, type=Path, help="GCC -aux-info output for the unified oracle")
    parser.add_argument("--max-lines", type=int, default=1500)
    args = parser.parse_args()
    if args.max_lines < 200:
        raise SystemExit("--max-lines must be at least 200")

    sources = ordered_oracle_sources()
    prelude = next(path for path in sources if path.name == "00000000_clash95_prelude.inc.c")
    constant_guard_path = next(path for path in sources if path.name == "005_constant_guard.inc.c")
    aux = parse_aux(args.aux)
    if len(aux) < 3000:
        raise SystemExit(f"aux-info produced too few recovered definitions: {len(aux)}")

    prelude_header, state_text, helpers, declared_functions = build_prelude_outputs(prelude)
    fragment_types, rewritten = extract_fragment_types(sources)
    static_variables = fragment_static_variable_decls(sources)
    constant_guard = constant_guard_path.read_text(encoding="utf-8")
    commented_externals = commented_external_declarations(
        prelude, declared_functions, aux
    )

    safe_reset_split_root()
    state_source = write_state_source(state_text)
    helper_source, helper_functions = write_helper_source(helpers, aux)
    by_subsystem, functions = write_function_groups(sources, rewritten, aux, args.max_lines)
    functions.extend(helper_functions)
    generated_sources = [state_source, helper_source]
    for paths in by_subsystem.values():
        generated_sources.extend(paths)
    local_functions = localize_internal_functions(
        functions,
        generated_sources,
        aux,
        prelude_header,
    )
    write_generated_header(
        prelude_header,
        fragment_types,
        aux,
        static_variables,
        constant_guard,
        declared_functions,
        commented_externals,
        local_functions,
    )
    write_cmake_sources(by_subsystem, [state_source, helper_source])
    write_manifest(functions, state_source, generated_sources)
    write_path_map(sources, generated_sources)
    print(
        json.dumps(
            {
                "functions": len(functions),
                "translation_units": len(generated_sources),
                "subsystems": {name: len(paths) for name, paths in sorted(by_subsystem.items())},
            },
            indent=2,
        )
    )


if __name__ == "__main__":
    main()
