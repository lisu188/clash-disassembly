#!/usr/bin/env python3
"""Shared manifest-backed source/coverage helpers for recovered unit tests.

The frozen unit denominator is keyed by function identity. Source line ranges
are derived from the canonical split sources at measurement time.
"""

from __future__ import annotations

import json
import os
import re
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "data" / "recovered_sources.json"
PURE_SET = ROOT / "tests" / "unit" / "pure_set.json"
PURE_ALIASES = ROOT / "tests" / "unit" / "pure_function_aliases.json"


class CoverageMetadataError(RuntimeError):
    """Raised when coverage identities cannot be resolved unambiguously."""


def load_json(path: Path) -> dict:
    with path.open(encoding="utf-8") as stream:
        return json.load(stream)


def load_manifest(path: Path = MANIFEST) -> tuple[dict, dict[str, dict]]:
    document = load_json(path)
    by_name: dict[str, dict] = {}
    duplicates: list[str] = []
    for function in document.get("functions", []):
        name = function["name"]
        if name in by_name:
            duplicates.append(name)
        by_name[name] = function
    if duplicates:
        raise CoverageMetadataError(
            "duplicate recovered function identities in source manifest: "
            + ", ".join(sorted(set(duplicates)))
        )
    return document, by_name


def load_aliases(path: Path = PURE_ALIASES) -> dict[str, str]:
    if not path.exists():
        return {}
    document = load_json(path)
    aliases = document.get("aliases", {})
    if len(set(aliases.values())) != len(aliases):
        raise CoverageMetadataError("multiple frozen names resolve to one canonical function")
    return aliases


def enrich_pure_set(pure: dict, manifest_by_name: dict[str, dict]) -> dict:
    """Return schema-v2 frozen metadata resolved through the source manifest."""
    functions = []
    missing = []
    aliases = load_aliases()
    for frozen in pure.get("functions", []):
        frozen_name = frozen.get("legacy_name", frozen["name"])
        name = aliases.get(frozen_name, frozen["name"])
        recovered = manifest_by_name.get(name)
        if recovered is None:
            missing.append(name)
            continue
        item = {
            "name": name,
            "original_address": recovered.get("original_address"),
            "original_source": recovered["original_source"],
            "original_line": recovered.get("original_line"),
            "source": recovered["source"],
        }
        if frozen_name != name:
            item["legacy_name"] = frozen_name
        functions.append(item)
    if missing:
        raise CoverageMetadataError(
            f"{len(missing)} frozen functions are absent from {MANIFEST.relative_to(ROOT)}: "
            + ", ".join(missing)
        )
    return {
        "schema_version": 2,
        "identity_source": str(MANIFEST.relative_to(ROOT)).replace("\\", "/"),
        "denominator": "frozen",
        "functions": functions,
        "count": len(functions),
    }


def load_pure_set(
    path: Path = PURE_SET, *, require_manifest: bool = True
) -> tuple[dict, list[dict]]:
    pure = load_json(path)
    if require_manifest or pure.get("schema_version", 1) >= 2:
        _, by_name = load_manifest()
        pure = enrich_pure_set(pure, by_name)
    functions = pure.get("functions", [])
    if pure.get("count") != len(functions):
        raise CoverageMetadataError(
            f"pure-set count is {pure.get('count')}, but contains {len(functions)} identities"
        )
    return pure, functions


def _mask_non_code(text: str) -> str:
    """Mask comments and literals while retaining newlines and punctuation."""
    chars = list(text)
    i = 0
    state = "code"
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
            if ch == '"':
                chars[i] = " "
                state = "string"
            elif ch == "'":
                chars[i] = " "
                state = "char"
        elif state == "line_comment":
            if ch == "\n":
                state = "code"
            else:
                chars[i] = " "
        elif state == "block_comment":
            if ch == "*" and nxt == "/":
                chars[i] = chars[i + 1] = " "
                i += 2
                state = "code"
                continue
            if ch != "\n":
                chars[i] = " "
        elif state in ("string", "char"):
            quote = '"' if state == "string" else "'"
            if ch == "\\":
                chars[i] = " "
                if i + 1 < len(chars) and chars[i + 1] != "\n":
                    chars[i + 1] = " "
                    i += 2
                    continue
            elif ch == quote:
                chars[i] = " "
                state = "code"
            elif ch != "\n":
                chars[i] = " "
        i += 1
    return "".join(chars)


def _function_line_range_in_text(
    source: Path, name: str, masked: str
) -> tuple[int, int]:
    # Definitions are emitted at file scope.  Requiring text before the name
    # prevents ordinary calls from becoming candidates while supporting GNU89
    # K&R definitions retained during the mechanical split.
    pattern = re.compile(
        rf"(?m)^[A-Za-z_][^;{{}}\n]*\b{re.escape(name)}\s*\("
    )
    candidates = []
    for match in pattern.finditer(masked):
        open_paren = masked.find("(", match.start(), match.end())
        paren_depth = 0
        close_paren = None
        for offset in range(open_paren, len(masked)):
            if masked[offset] == "(":
                paren_depth += 1
            elif masked[offset] == ")":
                paren_depth -= 1
                if paren_depth == 0:
                    close_paren = offset
                    break
        if close_paren is None:
            continue
        # A declaration ends immediately after its balanced parameter list.
        # K&R definitions instead place parameter declarations before `{`.
        if masked[close_paren + 1 :].lstrip().startswith(";"):
            continue
        brace = masked.find("{", match.end())
        if brace < 0:
            continue
        # A second file-scope candidate before the brace means this was a
        # prototype. K&R parameter declarations may contain semicolons, so a
        # semicolon alone is not a valid rejection signal.
        next_candidate = pattern.search(masked, match.end(), brace)
        if next_candidate:
            continue
        depth = 0
        end = None
        for offset in range(brace, len(masked)):
            ch = masked[offset]
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    end = offset + 1
                    break
        if end is not None:
            start_line = masked.count("\n", 0, match.start()) + 1
            end_line = masked.count("\n", 0, end) + 2
            candidates.append((start_line, end_line))
    if len(candidates) != 1:
        raise CoverageMetadataError(
            f"expected one definition of {name} in {source.relative_to(ROOT)}, "
            f"found {len(candidates)}"
        )
    return candidates[0]


def function_line_range(source: Path, name: str) -> tuple[int, int]:
    """Return the 1-based, end-exclusive body range for *name* in *source*."""
    text = source.read_text(encoding="utf-8", errors="replace")
    return _function_line_range_in_text(source, name, _mask_non_code(text))


def source_ranges(
    functions: list[dict], source_key: str
) -> dict[str, tuple[str, int, int]]:
    ranges = {}
    by_source: dict[str, list[dict]] = {}
    for function in functions:
        rel = function[source_key].replace("\\", "/")
        by_source.setdefault(rel, []).append(function)
    for rel, source_functions in by_source.items():
        source = ROOT / Path(rel)
        if not source.is_file():
            raise CoverageMetadataError(f"coverage source does not exist: {rel}")
        masked = _mask_non_code(
            source.read_text(encoding="utf-8", errors="replace")
        )
        for function in source_functions:
            start, end = _function_line_range_in_text(
                source, function["name"], masked
            )
            ranges[function["name"]] = (rel, start, end)
    return ranges


def split_ranges(functions: list[dict]) -> dict[str, tuple[str, int, int]]:
    return source_ranges(functions, "source")


def parse_gcov(path: Path) -> tuple[str | None, dict[int, bool]]:
    source = None
    executable = {}
    with path.open(encoding="utf-8", errors="replace") as stream:
        for line in stream:
            parts = line.split(":", 2)
            if len(parts) < 3:
                continue
            count = parts[0].strip()
            try:
                lineno = int(parts[1].strip())
            except ValueError:
                continue
            payload = parts[2].strip()
            if lineno == 0 and payload.startswith("Source:"):
                source = payload[len("Source:") :]
                continue
            if lineno == 0 or count == "-":
                continue
            executable[lineno] = count not in ("#####", "=====")
    return source, executable


def _canonical_source(source: str, expected: set[str]) -> str | None:
    normalized = source.replace("\\", "/").lower()
    for rel in expected:
        rel_norm = rel.lower()
        if normalized == rel_norm or normalized.endswith("/" + rel_norm):
            return rel
    return None


def collect_split_gcov(build_dir: Path, sources: set[str]) -> dict[str, dict[int, bool]]:
    """Run gcov for independently compiled recovered sources."""
    notes_by_name: dict[str, list[Path]] = {}
    for note in build_dir.rglob("*.gcno"):
        if "coverage-shards" in note.parts:
            continue
        notes_by_name.setdefault(note.name, []).append(note)

    missing_notes = []
    selected = {}
    for source in sorted(sources):
        candidates = notes_by_name.get(Path(source).name + ".gcno", [])
        candidates = [
            path
            for path in candidates
            if "clash95_recovered_coverage_objects.dir" in path.parts
        ]
        if len(candidates) != 1:
            if not candidates:
                missing_notes.append(source)
                continue
            raise CoverageMetadataError(
                f"multiple executed coverage objects found for {source}: "
                + ", ".join(str(path) for path in candidates)
            )
        selected[source] = candidates[0]
    if missing_notes:
        raise CoverageMetadataError(
            f"no executed split coverage object for {len(missing_notes)} sources; "
            "build and run the coverage-instrumented split object library first"
        )

    shard_root = build_dir / "coverage-shards"
    shard_workers = sorted(path for path in shard_root.glob("worker-*") if path.is_dir())
    if shard_workers:
        coverage: dict[str, dict[int, bool]] = {}
        with tempfile.TemporaryDirectory(prefix="clash95-gcov-shards-") as temp_dir:
            temp = Path(temp_dir)
            grouped: dict[Path, list[tuple[str, Path]]] = {}
            for source, note in selected.items():
                grouped.setdefault(note.parent.relative_to(build_dir), []).append(
                    (source, note)
                )
            for worker_index, worker_root in enumerate(shard_workers):
                for group_index, (relative_parent, group) in enumerate(
                    sorted(grouped.items(), key=lambda item: str(item[0]))
                ):
                    scratch = temp / f"notes-{worker_index}-{group_index}"
                    output = temp / f"output-{worker_index}-{group_index}"
                    scratch.mkdir()
                    output.mkdir()
                    names = []
                    for _, note in group:
                        data = worker_root / note.relative_to(build_dir).with_suffix(
                            ".gcda"
                        )
                        if not data.exists():
                            raise CoverageMetadataError(
                                f"missing shard profile for {note}: {data}"
                            )
                        (scratch / note.name).symlink_to(note)
                        (scratch / data.name).symlink_to(data)
                        names.append(note.name)
                    try:
                        result = subprocess.run(
                            ["gcov", "-p", "-l", "-o", str(scratch), *names],
                            cwd=output,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            text=True,
                        )
                    except FileNotFoundError as error:
                        raise CoverageMetadataError(
                            "gcov is required to measure coverage"
                        ) from error
                    if result.returncode:
                        raise CoverageMetadataError(
                            f"gcov failed for {relative_parent}: {result.stderr.strip()}"
                        )
                    for gcov_file in output.glob("*.gcov"):
                        emitted_source, lines = parse_gcov(gcov_file)
                        if emitted_source is None:
                            continue
                        canonical = _canonical_source(emitted_source, sources)
                        if canonical is None:
                            continue
                        accumulated = coverage.setdefault(canonical, {})
                        for line, covered in lines.items():
                            accumulated[line] = accumulated.get(line, False) or covered
        missing_output = sources - coverage.keys()
        if missing_output:
            raise CoverageMetadataError(
                "gcov did not emit recovered shard data for: "
                + ", ".join(sorted(missing_output))
            )
        return coverage

    # Backward-compatible single-profile mode used by older local builds.
    selected = {
        source: note
        for source, note in selected.items()
        if note.with_suffix(".gcda").exists()
    }
    if len(selected) != len(sources):
        raise CoverageMetadataError(
            "no executed split coverage profiles; run clash95_unit_tests first"
        )
    coverage: dict[str, dict[int, bool]] = {}
    with tempfile.TemporaryDirectory(prefix="clash95-gcov-") as output_dir:
        output = Path(output_dir)
        for note in selected.values():
            try:
                result = subprocess.run(
                    ["gcov", "-p", "-l", "-o", str(note.parent), note.name],
                    cwd=output,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    text=True,
                )
            except FileNotFoundError as error:
                raise CoverageMetadataError(
                    "gcov is required to measure coverage"
                ) from error
            if result.returncode:
                raise CoverageMetadataError(
                    f"gcov failed for {note}: {result.stderr.strip()}"
                )
        for gcov_file in output.glob("*.gcov"):
            source, lines = parse_gcov(gcov_file)
            if source is None:
                continue
            canonical = _canonical_source(source, sources)
            if canonical is not None:
                coverage[canonical] = lines
    missing_output = sources - coverage.keys()
    if missing_output:
        raise CoverageMetadataError(
            "gcov did not emit recovered source data for: "
            + ", ".join(sorted(missing_output))
        )
    return coverage
