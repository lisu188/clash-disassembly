#!/usr/bin/env python3
"""Header-surface audit and coupling ratchet (P3.7).

Keeps the narrowed per-subsystem header architecture honest after the umbrella
deletion. Three passes:

1. FRESHNESS — the generated headers, data/subsystem_api.json, and every TU's
   marker-delimited include block must match a clean regeneration
   (tools/gen_subsystem_headers.py --check / --check-tu-includes).
2. INCLUDE POLICY — production recovered TUs may include recovered headers
   only inside the generated block; no TU may include another subsystem's
   <S>_internal.h, <S>_state.h or <S>_shared_state.h. The shared-state aggregate
   stays within the state definition group and tests; src/recovered_all.h is
   tests-only; the deleted umbrella names must not return. Consumer and TU
   shared-state visibility records must agree with their measured references.
   Consumer-slice policy is enabled by recovered_decls.json's explicit
   shared_state_layout=consumer setting; the default aggregate layout retains
   its existing policy until a validated generator cutover.
3. COUPLING RATCHET — per-subsystem public-surface size (api function count),
   shared-global count, and peer edges are compared against
   data/header_surface_baseline.json: any INCREASE fails (decreases pass and
   are locked in with --mode update). This is the "new coupling is a
   deliberate choice" gate.

Usage:
  python3 tools/audit_header_surface.py --mode check    (CI)
  python3 tools/audit_header_surface.py --mode update   (conscious re-seed)
"""

from __future__ import annotations

import argparse
import json
import posixpath
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from recovered_implementation import manifest_sources
from split_source_index import mask_c

REPO = Path(__file__).resolve().parents[1]
SURFACE = REPO / "data" / "subsystem_api.json"
DECLS = REPO / "data" / "recovered_decls.json"
BASELINE = REPO / "data" / "header_surface_baseline.json"
GEN = REPO / "tools" / "gen_subsystem_headers.py"

MARK_BEGIN = "/* CLASH95_GENERATED_INCLUDES_BEGIN"
MARK_END = "/* CLASH95_GENERATED_INCLUDES_END */"
FORBIDDEN_UMBRELLA = ("recovered_internal.h", "recovered_functions.h",
                      "recovered_foundation.h")
CLASS_FOUNDATION_HEADERS = frozenset({
    "src/recovered_types.h", "src/recovered_abi.h", "src/recovered_layout.h",
    "src/platform/platform_sdl.h", "src/compatibility/defs.h",
    "src/instrumentation/runtime_mission_trace.h",
})
INCLUDE_LINE = re.compile(r'^\s*#\s*include\s+([^\n]+)', re.M)
LITERAL_INCLUDE = re.compile(r'^["<]([^">]+)[">]')


def _class_header_closure(header: str) -> tuple[list[str], list[str]]:
    """Resolve local includes without letting a binding header hide policy."""
    visited, errors = set(), []

    def visit(relative: str) -> None:
        if relative in visited:
            return
        visited.add(relative)
        path = REPO / relative
        if not path.is_file():
            errors.append(f"{header}: missing class header dependency: {relative}")
            return
        text = path.read_text(encoding="latin-1")
        # Strip comments/literals only when looking for directives? Include
        # filenames are literals, so retain them and strip comments separately.
        text = re.sub(r'/\*.*?\*/|//[^\n]*', ' ', text, flags=re.S)
        owner = header.split('/')[1]
        for match in INCLUDE_LINE.finditer(text):
            included = LITERAL_INCLUDE.match(match.group(1).strip())
            if included is None:
                errors.append(f"{relative}: computed include is forbidden in class-header closure")
                continue
            spelling = included.group(1).replace('\\', '/')
            basename = posixpath.basename(posixpath.normpath(spelling))
            if basename in FORBIDDEN_UMBRELLA or basename == 'recovered_all.h':
                errors.append(f"{relative}: forbidden aggregate in class-header closure: {spelling}")
                continue
            private = re.fullmatch(r'([a-z][a-z0-9_]*?)_(internal|shared_state|state)\.h', basename)
            if private and private.group(1) != owner:
                errors.append(f"{relative}: foreign {private.group(2)} header in {header}: {spelling}")
            if basename in ('state_shared.h', 'state_local.h'):
                errors.append(f"{relative}: state aggregate in class-header closure: {spelling}")
            if basename.endswith('_local.h'):
                errors.append(f"{relative}: TU-local header in class-header closure: {spelling}")
            candidates = (path.parent / spelling, REPO / 'src' / spelling, REPO / spelling)
            for candidate in candidates:
                if not candidate.is_file():
                    continue
                try:
                    child = candidate.resolve().relative_to(REPO.resolve()).as_posix()
                except ValueError:
                    errors.append(f"{relative}: class header escapes the repository: {spelling}")
                    break
                visit(child)
                break
    visit(header)
    return sorted(visited), errors


def _mask_class_method_declarators(text: str, function_names: set[str]) -> str:
    """Mask only class member declaration names, never call/default arguments.

    The header contract is intentionally narrow: ordinary class declarations,
    borrowing constructors, and trivial accessors. This is not a C++ parser;
    unusual declarator expressions fail closed as dependency references.
    """
    masked = mask_c(text)
    chars = list(masked)
    scopes: list[str] = []
    class_offsets = set()
    boundary = 0
    for match in re.finditer(r'[{};]|[A-Za-z_][A-Za-z0-9_]*', masked):
        token = match.group()
        if token == '{':
            prefix = masked[boundary:match.start()]
            scopes.append('class' if re.search(r'\b(?:class|struct)\b[^;{}]*$', prefix) else 'other')
            boundary = match.end()
        elif token == '}':
            if scopes:
                scopes.pop()
            boundary = match.end()
        elif token == ';':
            boundary = match.end()
        elif scopes and scopes[-1] == 'class' and token in function_names:
            class_offsets.add(match.start())
    for match in re.finditer(r'\b([A-Za-z_][A-Za-z0-9_]*)\s*\(', masked):
        if match.start() not in class_offsets:
            continue
        preceding = max(masked.rfind(';', 0, match.start()), masked.rfind('{', 0, match.start()), masked.rfind('}', 0, match.start()))
        prefix = masked[preceding + 1:match.start()].strip()
        prefix = re.sub(r'^(?:public|protected|private)\s*:\s*', '', prefix)
        if (not prefix or re.search(r'\b(?:return|throw|co_return|new|delete|decltype|sizeof|alignof)\b', prefix)
                or re.search(r'[=().{}?+\-/]', prefix)):
            continue
        for index in range(match.start(1), match.end(1)):
            chars[index] = ' '
    return ''.join(chars)


def _inline_header_behavior_errors(text: str) -> list[str]:
    """Only empty bodies or a direct field/address return belong in headers."""
    code = mask_c(text)
    problems = []
    control = sorted(set(re.findall(r'\b(?:if|for|while|switch|do|goto|throw|try|catch)\b|\?', code)))
    if control:
        problems.append('inline control flow must be out of line: ' + ', '.join(control))
    # Inspect function bodies (class/namespace braces do not end a parameter
    # list). Casts, calls, comparisons, assignments and multi-statement helpers
    # go out of line as well; otherwise they escape canonical body coverage.
    direct_return = re.compile(
        r'return\s+(?:[*&]\s*)?(?:this\s*->\s*)?[A-Za-z_][A-Za-z0-9_]*'
        r'(?:(?:\s*(?:\.|->)\s*[A-Za-z_][A-Za-z0-9_]*)|'
        r'(?:\s*\[\s*(?:[A-Za-z_][A-Za-z0-9_]*|[0-9]+)\s*\]))*\s*;\s*\Z')
    simple_binding = r'[A-Za-z_][A-Za-z0-9_]*\s*\(\s*(?:[*&]\s*)?(?:[A-Za-z_][A-Za-z0-9_]*|[0-9]+)(?:\s*(?:\.|->)\s*[A-Za-z_][A-Za-z0-9_]*)*\s*\)'
    for assignment in re.finditer(r'=\s*([^;{}]+)', code):
        if re.search(r'\busing\s+[A-Za-z_][A-Za-z0-9_]*\s*$', code[:assignment.start()]):
            # A type alias has no runtime initialization. Its canonical name
            # dependencies are still inspected by the separate token pass.
            continue
        expression = assignment.group(1).strip()
        if re.search(r'\b[A-Za-z_][A-Za-z0-9_]*\s*\(', expression):
            problems.append('function calls in header initializers must be out of line')
        # A default member initializer executes during construction too. Do
        # not let arithmetic/comparisons hide behind an otherwise empty ctor.
        # Permit a direct borrowed field/address or scalar constant only.
        unwrapped = expression.strip('() \t\r\n')
        trivial_initializer = re.fullmatch(
            r'(?:[*&]\s*)?(?:this\s*->\s*)?[A-Za-z_][A-Za-z0-9_]*'
            r'(?:\s*(?:\.|->)\s*[A-Za-z_][A-Za-z0-9_]*)*'
            r'|[-+]?(?:0[xX][0-9A-Fa-f]+|[0-9]+)(?:[uUlL]*)', unwrapped)
        if unwrapped and not trivial_initializer:
            problems.append('nontrivial header initializers must be out of line')
    boundary = 0
    for match in re.finditer(r'[{};]', code):
        token = match.group()
        if token == '{':
            prefix = code[boundary:match.start()]
            if ')' in prefix and not re.search(r'\b(?:class|struct|namespace)\b', prefix):
                prefix = re.sub(r'^\s*(?:public|protected|private)\s*:\s*', '', prefix)
                initializers = re.search(r'(?<!:):(?!:)\s*([A-Za-z_][A-Za-z0-9_]*\s*\(.*)$', prefix, re.S)
                if initializers and not re.fullmatch(simple_binding + r'(?:\s*,\s*' + simple_binding + r')*\s*', initializers.group(1)):
                    problems.append('constructor header initializers must only borrow passed fields')
                depth, end = 1, match.end()
                while end < len(code) and depth:
                    depth += (code[end] == '{') - (code[end] == '}')
                    end += 1
                if depth:
                    problems.append('unbalanced inline header body')
                else:
                    body = code[match.end():end - 1].strip()
                    if body and not direct_return.fullmatch(body):
                        problems.append('nontrivial inline helper must be out of line')
        boundary = match.end()
    return sorted(set(problems))


def class_header_policy_errors(manifest: dict | None = None) -> list[str]:
    """Class headers cannot bypass declaration ownership or coupling scans."""
    if manifest is None:
        manifest = json.loads((REPO / 'data/recovered_sources.json').read_text(encoding='utf-8'))
    headers = {path.relative_to(REPO).as_posix() for path in (REPO / 'src').rglob('*.hpp')}
    headers.update(record.get('implementation', {}).get('header')
                   for record in manifest['functions']
                   if record.get('implementation', {}).get('kind') == 'method')
    headers.discard(None)
    if not headers:
        return []
    declarations = json.loads(DECLS.read_text(encoding='utf-8'))
    functions = declarations.get('functions', {})
    globals_ = declarations.get('globals', {})
    # Reuse declaration macro expansion, not the header usage scanner: the
    # latter deliberately excludes inline headers and is what this gate guards.
    from gen_subsystem_headers import expanded_names
    expanded = None
    function_names, global_names = set(functions), set(globals_)
    errors = []
    for header in sorted(headers):
        path = Path(header)
        if path.is_absolute() or '..' in path.parts or not header.startswith('src/'):
            errors.append(f'invalid class header path: {header}')
            continue
        closure, policy = _class_header_closure(header)
        errors.extend(policy)
        if policy:
            continue
        if expanded is None:
            try:
                expanded = expanded_names(functions, globals_, cpp=True) if functions or globals_ else {}
            except SystemExit as exception:
                errors.append(f'class header declaration preprocessing failed: {exception}')
                continue
            function_names.update(name for (kind, _), name in expanded.items() if kind == 'fn')
            global_names.update(name for (kind, _), name in expanded.items() if kind == 'gl')
        custom = [name for name in closure if name not in CLASS_FOUNDATION_HEADERS and (REPO / name).is_file()]
        # Each closure gets its own macro environment so aliases defined by a
        # parent binding header are visible in included inline accessors.
        macro_probes = []
        for relative in custom:
            text = (REPO / relative).read_text(encoding='latin-1')
            text = INCLUDE_LINE.sub('', text)
            joined = re.sub(r'\\\r?\n', '', text)
            for macro in re.finditer(r'^\s*#\s*define\s+[A-Za-z_][A-Za-z0-9_]*(?:\([^\n)]*\))?\s+([^\n]+)', joined, re.M):
                macro_probes.append('int ClassHeaderMacroProbe = (' + macro.group(1) + ');')
        marker = 'CLASH95_CLASS_HEADER_POLICY_MARKER_98127'
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'class-header.cpp'
            # Include the real root after the marker, preserving actual include
            # order and macro state. The reviewed foundation is loaded before
            # it so its guarded declarations never pollute header usage.
            source.write_text('#include "recovered_types.h"\nint ' + marker + ';\n#include "' + header + '"\n' + '\n'.join(macro_probes), encoding='latin-1')
            process = subprocess.run(['g++', '-std=gnu++20', '-U_GNU_SOURCE', '-E', '-I', str(REPO / 'src'), '-I', str(REPO), str(source)],
                                     capture_output=True, text=True, encoding='latin-1')
        if process.returncode:
            errors.append(f'{header}: class header dependency preprocessing failed: {process.stderr.strip()[:500]}')
            continue
        # System-library inline implementations are not game class behavior.
        # Preserve line directives to retain only our custom closure and the
        # explicit macro probes while still using their real macro expansion.
        accepted_files = {str((REPO / name).resolve()) for name in custom} | {str(source)}
        current_file, started, selected = '', False, []
        for line in process.stdout.splitlines():
            directive = re.match(r'^#\s+\d+\s+"([^"]+)"', line)
            if directive:
                current_file = directive.group(1)
                continue
            if marker in line:
                started = True
                line = line.split(marker, 1)[1]
            if started and current_file in accepted_files:
                selected.append(line)
        processed = '\n'.join(selected)
        errors.extend(f'{header}: {problem}' for problem in _inline_header_behavior_errors(processed))
        processed = _mask_class_method_declarators(processed, function_names)
        tokens = set(re.findall(r'[A-Za-z_][A-Za-z0-9_]*', processed))
        references = tokens & (function_names | global_names)
        if references:
            errors.append(f'{header}: canonical dependencies hidden in class-header code; move bindings/behavior out of line: ' + ', '.join(sorted(references)))
    return sorted(set(errors))


def run_gen(*flags: str) -> int:
    proc = subprocess.run([sys.executable, str(GEN), *flags],
                          capture_output=True, text=True)
    if proc.returncode != 0:
        print(proc.stdout.strip())
        print(proc.stderr.strip())
    return proc.returncode


def consumer_shared_state_enabled() -> bool:
    decls = json.loads(DECLS.read_text(encoding="utf-8"))
    return decls.get("shared_state_layout", "aggregate") == "consumer"


def include_policy_errors() -> list[str]:
    errors = []
    consumer_layout = consumer_shared_state_enabled()
    manifest = json.loads(
        (REPO / "data" / "recovered_sources.json").read_text(encoding="utf-8"))
    sources = manifest_sources(manifest)
    tu_local_basenames = {Path(source).stem + "_local.h" for source in sources}
    # Support files keep hand-maintained includes, but the hard bans (deleted
    # umbrella must not return; tests-only aggregate stays out of production)
    # apply to every production C/C++ source under src/.
    support = sorted(
        str(p.relative_to(REPO)).replace("\\", "/")
        for p in (REPO / "src").rglob("*")
        if p.suffix in {".c", ".cpp"}
        if str(p.relative_to(REPO)).replace("\\", "/") not in sources)
    # both quoted and angle-bracket forms resolve via -I flags; lint both
    inc_re = re.compile(r'^\s*#\s*include\s+["<]([^">]+)[">]', re.M)
    generated_basenames = re.compile(
        r"(recovered_|_api\.h$|_internal\.h$|_state\.h$|_local\.h$|"
        r"^state_shared\.h$|^state_local\.h$)")
    for rel in sources + support:
        text = (REPO / rel).read_text(encoding="latin-1")
        parts = rel.split("/")
        sub = parts[1] if len(parts) > 2 else ""
        is_recovered_tu = rel in sources
        m = re.search(re.escape(MARK_BEGIN) + r".*?" + re.escape(MARK_END),
                      text, flags=re.DOTALL)
        block_span = m.span() if m else (0, 0)
        for im in inc_re.finditer(text):
            inc = im.group(1)
            inside = block_span[0] <= im.start() < block_span[1]
            # Treat source-relative, -I src, repository-root, and normalized
            # ../ spellings alike. Header ownership is encoded in its basename,
            # so a foreign slice cannot bypass policy by changing its path.
            base = posixpath.basename(posixpath.normpath(inc.replace("\\", "/")))
            if base in FORBIDDEN_UMBRELLA:
                errors.append(f"{rel}: deleted umbrella include returned: {inc}")
            if base == "recovered_all.h":
                errors.append(f"{rel}: tests-only aggregate included in production")
            if base in tu_local_basenames:
                expected = posixpath.splitext(rel)[0] + "_local.h"
                normalized = inc.replace("\\", "/")
                resolved = {
                    posixpath.normpath(posixpath.join(posixpath.dirname(rel), normalized)),
                    posixpath.normpath(posixpath.join("src", normalized)),
                    posixpath.normpath(normalized),
                }
                if not is_recovered_tu or expected not in resolved:
                    errors.append(f"{rel}: foreign TU-local header: {inc}")
            if not is_recovered_tu:
                continue  # support files: hard bans only
            if not inside and generated_basenames.search(base):
                errors.append(f"{rel}: recovered include outside generated block: {inc}")
            if consumer_layout and base == "state_shared.h" and sub != "state":
                errors.append(f"{rel}: shared-state aggregate outside state group: {inc}")
            if consumer_layout:
                fm = re.fullmatch(
                    r"([a-z][a-z0-9_]*?)_(internal|shared_state|state)\.h", base)
            else:
                fm = re.match(r"(?:\.\./)?([a-z]+)/\1_(internal|state)\.h$", inc)
            if fm and fm.group(1) != sub:
                # the state group is the definition site of every global and
                # includes ALL *_state.h slices so definitions stay decl-checked
                if not (sub == "state" and fm.group(2) == "state"):
                    errors.append(f"{rel}: foreign {fm.group(2)} header: {inc}")
    errors.extend(class_header_policy_errors(manifest))
    return errors


def shared_state_surface_errors() -> list[str]:
    """Check declaration visibility without changing the coupling ratchet.

    References measure dependencies; visible declarations measure exposure.
    Fresh generation checks the source evidence, while this check enforces the
    relationship between those two explicitly separate sets.
    """
    if not consumer_shared_state_enabled():
        return []
    surface = json.loads(SURFACE.read_text(encoding="utf-8"))
    manifest = json.loads(
        (REPO / "data" / "recovered_sources.json").read_text(encoding="utf-8"))
    errors = []
    shared = set(surface["shared_globals"])
    expected_consumers = set(surface["subsystems"]) - {"state"}
    sources = set(manifest_sources(manifest))
    expected_sources = {rel for rel in sources if rel.split("/")[1] != "state"}

    def mapping(field: str, expected: set[str]) -> dict:
        value = surface.get(field)
        if not isinstance(value, dict):
            errors.append(f"{field}: required object missing or invalid")
            return {}
        missing, extra = expected - value.keys(), value.keys() - expected
        if missing:
            errors.append(f"{field}: missing entries: {', '.join(sorted(missing))}")
        if extra:
            errors.append(f"{field}: unexpected entries: {', '.join(sorted(extra))}")
        return value

    def names(value, label: str) -> set[str] | None:
        if not isinstance(value, list) or not all(isinstance(n, str) for n in value):
            errors.append(f"{label}: expected a sorted list of shared-global DB keys")
            return None
        result = set(value)
        if value != sorted(result):
            errors.append(f"{label}: keys must be sorted and unique")
        if result - shared:
            errors.append(f"{label}: keys are not shared globals: "
                          f"{', '.join(sorted(result - shared))}")
        return result

    consumers = mapping("shared_state_consumers", expected_consumers)
    visibility = mapping("tu_shared_state_visibility", expected_sources)
    slices = {sub: names(value, f"shared_state_consumers.{sub}")
              for sub, value in consumers.items()}
    references = {sub: set() for sub in expected_consumers}
    for rel, record in visibility.items():
        label = f"tu_shared_state_visibility.{rel}"
        if not isinstance(record, dict) or set(record) != {"referenced", "visible"}:
            errors.append(f"{label}: expected referenced and visible fields")
            continue
        referenced = names(record["referenced"], f"{label}.referenced")
        visible = names(record["visible"], f"{label}.visible")
        if referenced is None or visible is None or rel not in expected_sources:
            continue
        sub = rel.split("/")[1]
        if sub not in references:
            errors.append(f"{label}: subsystem {sub!r} missing from surface")
            continue
        references[sub].update(referenced)
        if referenced - visible:
            errors.append(f"{label}: referenced globals are not visible")
        consumer_slice = slices.get(sub)
        if consumer_slice is not None:
            expected_visible = consumer_slice if referenced else set()
            if visible != expected_visible:
                errors.append(f"{label}: visible globals must equal the consumer "
                              "slice when referenced, otherwise be empty")
    for sub, referenced in references.items():
        if slices.get(sub) is not None and slices[sub] != referenced:
            errors.append(f"shared_state_consumers.{sub}: slice differs from "
                          "the union of TU references")
    return errors


def surface_metrics() -> dict:
    s = json.loads(SURFACE.read_text(encoding="utf-8"))
    return {
        "api_counts": {k: len(v["api_functions"])
                       for k, v in s["subsystems"].items()},
        "shared_global_count": len(s["shared_globals"]),
        "peer_edges": s["peer_edges"],
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--mode", choices=("check", "update"), default="check")
    args = ap.parse_args()

    ok = True
    if run_gen("--check") != 0:
        print("FRESHNESS: generated headers/surface stale"); ok = False
    if run_gen("--check-tu-includes") != 0:
        print("FRESHNESS: TU include blocks stale"); ok = False

    errors = include_policy_errors()
    for e in errors[:15]:
        print("POLICY:", e)
    if errors:
        ok = False

    errors = shared_state_surface_errors()
    for e in errors[:15]:
        print("VISIBILITY:", e)
    if errors:
        ok = False

    cur = surface_metrics()
    if args.mode == "update":
        if not ok:
            print("refusing to update baseline with failures present")
            return 1
        BASELINE.write_text(json.dumps(
            {"schema_version": 1, **cur}, indent=1, sort_keys=True) + "\n",
            encoding="utf-8")
        print(f"updated header-surface baseline -> {BASELINE.relative_to(REPO)}")
        return 0

    if BASELINE.exists():
        base = json.loads(BASELINE.read_text(encoding="utf-8"))
        regressions = []
        for s_, n in cur["api_counts"].items():
            b = base.get("api_counts", {}).get(s_, 0)
            if n > b:
                regressions.append(f"api surface of {s_} grew {b} -> {n}")
        if cur["shared_global_count"] > base.get("shared_global_count", 0):
            regressions.append(
                f"shared globals grew {base.get('shared_global_count')} -> "
                f"{cur['shared_global_count']}")
        for edge, n in cur["peer_edges"].items():
            b = base.get("peer_edges", {}).get(edge, 0)
            if n > b:
                regressions.append(f"peer edge {edge} grew {b} -> {n}")
        for r in regressions[:15]:
            print("RATCHET:", r)
        if regressions:
            print("(a deliberate surface increase re-seeds with --mode update)")
            ok = False
    else:
        print("note: no header-surface baseline; seed with --mode update")

    print(f"header-surface audit: {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
