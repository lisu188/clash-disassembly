#!/usr/bin/env python3
"""Plan or explicitly apply one complete, mechanically supported class batch.

The default is read-only. First extract into the existing translation units,
validate parity, then explicitly relocate into class-named files. Unsupported
contracts reject the entire class; this tool never guesses an ABI, ownership,
variadic forwarding rule, or storage lifetime. Builds and behavioral gates are
separate from this mechanical transformation.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass, field
import difflib
import json
import os
from pathlib import Path, PurePosixPath
import re
import shlex
import shutil
import subprocess
import tempfile

from recovered_implementation import (ImplementationError, implementation_name,
                                      manifest_sources, manifest_targets,
                                      resolve_source_definitions)
from split_source_index import body_sha256, mask_c, scan_definitions


ROOT = Path(__file__).resolve().parents[1]
IDENTIFIER = re.compile(r"[A-Za-z_][A-Za-z_0-9]*\Z")
IDENTIFIERS = re.compile(r"\b[A-Za-z_][A-Za-z_0-9]*\b")
MAX_LINES = 1500
INCLUDES_BEGIN = "/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */"
INCLUDES_END = "/* CLASH95_GENERATED_INCLUDES_END */"
FORBIDDEN = re.compile(r"\b(?:static|thread_local|__thread|asm|__asm__?|setjmp|longjmp|"
                       r"decltype|typeof|__typeof__?|__builtin_(?:apply|frame_address|return_address))\b")
REGISTER_CALL = re.compile(r"\b(?:__thiscall|__fastcall|__stdcall|__usercall|__userpurge|__vectorcall|register)\b")
VARARG_TOKENS = {"va_list", "va_start", "va_arg", "va_end", "va_copy",
                 "__builtin_va_start", "__builtin_va_arg", "__builtin_va_end", "__builtin_va_copy"}
QUALIFIERS = {"void", "char", "int", "short", "long", "float", "double", "bool",
              "signed", "unsigned", "const", "volatile", "auto"}
PP_TOKENS = re.compile(
    r'(?:u8|u|U|L)?"(?:\\.|[^"\\])*"[A-Za-z_0-9]*|(?:u8|u|U|L)?\'(?:\\.|[^\'\\])*\'[A-Za-z_0-9]*|'
    r"[A-Za-z_][A-Za-z_0-9]*|(?:\d|\.\d)(?:[eEpP][+-]|[A-Za-z_0-9.])*|"
    r"%:%:|<=>|>>=|<<=|->\*|\.\.\.|::|\.\*|->|\+\+|--|<<|>>|<=|>=|==|!=|"
    r"&&|\|\||\*=|/=|%=|\+=|-=|&=|\^=|\|=|##|<:|:>|<%|%>|%:|[^\s]", re.S)
CONTEXT_MACROS = {"__LINE__", "__FILE__", "__COUNTER__", "__DATE__", "__TIME__",
                  "__TIMESTAMP__", "__INCLUDE_LEVEL__", "__BASE_FILE__", "__func__",
                  "__FUNCTION__", "__PRETTY_FUNCTION__", "_Pragma"}


class MigrationError(ValueError):
    """A complete class cannot be migrated without an explicit manual repair."""


@dataclass
class Plan:
    root: Path
    owner: str
    stage: str
    identities: list[str]
    bindings: list[str]
    changes: dict[str, str] = field(default_factory=dict)
    snapshots: dict[str, bytes | None] = field(default_factory=dict)
    macro_expansions: list[dict] = field(default_factory=list)
    call_boundaries: list[dict] = field(default_factory=list)
    type_proofs: list[dict] = field(default_factory=list)

    def summary(self) -> dict:
        return {"class": self.owner, "stage": self.stage, "identities": self.identities,
                "borrowed_globals": self.bindings, "files": sorted(self.changes),
                "macro_expansions": self.macro_expansions,
                "retained_same_class_boundaries": self.call_boundaries,
                "binding_type_proofs": self.type_proofs,
                "source_inventory_policy": "preserve existing order; append new class sources explicitly after parity",
                "written": False, "requires": "compiler, identity, storage and behavioral parity gates"}

    def apply(self) -> None:
        """Check every input first, stage outputs, then replace with rollback."""
        for relative, expected in self.snapshots.items():
            path = _inside(self.root, relative)
            actual = path.read_bytes() if path.exists() else None
            if actual != expected:
                raise MigrationError(f"input changed since planning: {relative}")
        staged: dict[str, Path] = {}
        replaced: list[str] = []
        made_dirs: list[Path] = []
        try:
            for relative, text in self.changes.items():
                path = _inside(self.root, relative)
                missing = []
                parent = path.parent
                while not parent.exists():
                    missing.append(parent)
                    parent = parent.parent
                for directory in reversed(missing):
                    directory.mkdir()
                    made_dirs.append(directory)
                original = self.snapshots.get(relative)
                encoded = text.replace("\n", "\r\n").encode() if original and b"\r\n" in original else text.encode()
                with tempfile.NamedTemporaryFile(prefix=".class-migration-", dir=path.parent, delete=False) as stream:
                    stream.write(encoded)
                    staged[relative] = Path(stream.name)
                if path.exists():
                    os.chmod(staged[relative], path.stat().st_mode)
            # Recheck after staging so concurrent source/index work is not overwritten.
            for relative, expected in self.snapshots.items():
                path = _inside(self.root, relative)
                if (path.read_bytes() if path.exists() else None) != expected:
                    raise MigrationError(f"input changed while staging: {relative}")
            for relative, temporary in staged.items():
                temporary.replace(_inside(self.root, relative))
                replaced.append(relative)
        except BaseException:
            for relative in reversed(replaced):
                path = _inside(self.root, relative)
                original = self.snapshots.get(relative)
                if original is None:
                    path.unlink(missing_ok=True)
                else:
                    path.write_bytes(original)
            raise
        finally:
            for temporary in staged.values():
                temporary.unlink(missing_ok=True)
            for directory in reversed(made_dirs):
                try:
                    directory.rmdir()
                except OSError:
                    pass


def _inside(root: Path, relative: str) -> Path:
    if not isinstance(relative, str) or "\\" in relative:
        raise MigrationError(f"invalid relative path: {relative!r}")
    pure = PurePosixPath(relative)
    if pure.is_absolute() or ".." in pure.parts or ":" in relative:
        raise MigrationError(f"path escapes workspace: {relative}")
    path = (root / relative).resolve()
    if not path.is_relative_to(root.resolve()):
        raise MigrationError(f"resolved path escapes workspace: {relative}")
    return path


def _read(plan: Plan, relative: str) -> str:
    path = _inside(plan.root, relative)
    data = path.read_bytes()
    if relative in plan.snapshots and plan.snapshots[relative] != data:
        raise MigrationError(f"input changed while planning: {relative}")
    plan.snapshots[relative] = data
    return data.decode("utf-8").replace("\r\n", "\n")


def _new_output(plan: Plan, relative: str, text: str) -> None:
    path = _inside(plan.root, relative)
    if path.exists():
        raise MigrationError(f"refusing to overwrite existing class file: {relative}")
    plan.snapshots[relative] = None
    plan.changes[relative] = text


def _parts(parameters: str) -> list[str]:
    if not parameters.strip() or parameters.strip() == "void":
        return []
    if any(character in parameters for character in "(){}<>="):
        raise MigrationError("function-pointer/template/default parameters require a manual contract")
    return [part.strip() for part in parameters.split(",")]


def _signature(signature: str, name: str) -> tuple[str, str, list[str], list[str]]:
    plain = re.sub(r"\b(?:CLASH95_UNUSED)\b", "", signature).strip()
    if REGISTER_CALL.search(plain):
        raise MigrationError(f"{name}: register/calling-convention contract requires a manual adapter")
    if re.search(r"\b(?:static|CLASH95_LOCAL)\b", plain):
        raise MigrationError(f"{name}: file-local function identity requires a manual class boundary")
    match = re.fullmatch(r"(.+?)\b" + re.escape(name) + r"\s*\((.*)\)\s*", plain, re.S)
    if not match:
        raise MigrationError(f"{name}: unsupported function signature")
    prefix, parameters = match.groups()
    prefix = re.sub(r'extern\s+"C"\s*', "", prefix)
    prefix = re.sub(r"\b(?:CLASH95_INTERNAL|CLASH95_TEST_VISIBLE|__cdecl)\b", "", prefix).strip()
    if not prefix or any(character in prefix for character in "(){}[]=<>;"):
        raise MigrationError(f"{name}: unsupported result type or signature attribute")
    names, types = [], []
    for parameter in _parts(parameters):
        if parameter == "...":
            types.append("...")
            continue
        argument = re.fullmatch(r"(.+?)([A-Za-z_][A-Za-z_0-9]*)\s*((?:\[[^\]]*\])*)", parameter)
        if not argument or not argument[1].strip() or argument[2] in QUALIFIERS:
            raise MigrationError(f"{name}: every fixed definition parameter must have a name")
        names.append(argument[2])
        types.append(re.sub(r"\s+", "", argument[1] + argument[3]))
    original_match = re.fullmatch(r"(.+?)\b" + re.escape(name) + r"\s*\((.*)\)\s*", signature.strip(), re.S)
    # Keep parameter annotations (notably CLASH95_UNUSED) in the actual method;
    # the normalized copy above is only used for type and name inspection.
    return prefix, original_match[2] if original_match else parameters, names, types


def _verify_declaration(name: str, declaration: str, types: list[str]) -> None:
    match = re.search(r"\b" + re.escape(name) + r"\s*\((.*)\)\s*;\s*$", declaration, re.S)
    if not match:
        raise MigrationError(f"{name}: canonical declaration is unsupported")
    parameters = _parts(re.sub(r"\bCLASH95_UNUSED\b", "", match[1]))
    if len(parameters) != len(types):
        raise MigrationError(f"{name}: definition/canonical declaration arity differs")
    for parameter, wanted in zip(parameters, types):
        compact = re.sub(r"\s+", "", parameter)
        named = re.fullmatch(r"(.+?)([A-Za-z_][A-Za-z_0-9]*)\s*((?:\[[^\]]*\])*)", parameter)
        without_name = re.sub(r"\s+", "", named[1] + named[3]) if named else None
        if wanted not in (compact, without_name):
            raise MigrationError(f"{name}: definition/canonical parameter type differs: {parameter}")


def _positive_integer(text: str) -> int | None:
    text = text.strip()
    while text.startswith("(") and text.endswith(")"):
        text = text[1:-1].strip()
    if not re.fullmatch(r"(?:0[xX][0-9A-Fa-f]+|0[0-7]*|[1-9][0-9]*)(?:[uU](?:ll|LL|[lL])?|(?:ll|LL|[lL])[uU]?)?", text):
        return None
    literal = re.sub(r"[uUlL]+$", "", text)
    base = 16 if literal.lower().startswith("0x") else 8 if literal.startswith("0") else 10
    value = int(literal, base)
    return value if value > 0 else None


def _shared_enum_value(plan: Plan, name: str) -> int | None:
    text = mask_c(_read(plan, "src/recovered_types.h"))
    values = [match[1].strip() for enum in re.finditer(r"\benum(?:\s+[A-Za-z_]\w*)?\s*\{([^{}]*)\}", text)
              for match in re.finditer(r"(?:^|,)\s*" + re.escape(name) + r"\s*=\s*([^,]+)", enum[1])]
    return _positive_integer(values[0]) if len(values) == 1 else None


def _shared_bound(plan: Plan, name: str, seen: set[str] | None = None) -> int:
    """Admit literal object macros and explicit literal shared enumerators."""
    seen = set() if seen is None else seen
    if name in seen:
        raise MigrationError(f"{name}: cyclic shared array capacity")
    seen.add(name)
    text = _read(plan, "src/recovered_types.h")
    values = {value.strip() for value in re.findall(
        r"(?m)^\s*#\s*define[ \t]+" + re.escape(name) + r"[ \t]+([^\n]+)", text)}
    if not values and (value := _shared_enum_value(plan, name)) is not None:
        return value
    if len(values) != 1:
        raise MigrationError(f"{name}: array capacity requires one shared literal macro or explicit enumerator")
    value = re.sub(r"/\*.*?\*/|//[^\n]*", " ", values.pop(), flags=re.S).strip()
    result = _positive_integer(value)
    if result is not None:
        return result
    if IDENTIFIER.fullmatch(value):
        return _shared_bound(plan, value, seen)
    raise MigrationError(f"{name}: shared array capacity must resolve to a positive integer literal, not an expression or call")


def _global_type(name: str, declaration: str, plan: Plan | None = None) -> str:
    # This one known visibility annotation is not part of an object type. Its
    # exact original declaration remains at the factory/storage anchor.
    plain = re.sub(r"\bCLASH95_INTERNAL\b", "", declaration)
    bound = r"(?:0[xX][0-9A-Fa-f]+|[0-9]+|[A-Za-z_][A-Za-z_0-9]*)"
    match = re.fullmatch(r"extern\s+(.+?)\b" + re.escape(name) + r"\s*((?:\[\s*" + bound + r"\s*\])*)\s*;", plain.strip())
    if not match:
        raise MigrationError(f"{name}: unsupported global declaration (need external scalar/pointer/fixed literal or shared-capacity array)")
    base, dimensions = match.groups()
    if (any(character in base for character in "(){}[]=<>;&,")
            or re.search(r"\b(?:static|thread_local|auto|decltype)\b", base)):
        raise MigrationError(f"{name}: unsupported global binding type")
    for capacity in re.findall(r"\[\s*([^\]]+?)\s*\]", dimensions):
        if IDENTIFIER.fullmatch(capacity):
            if plan is None:
                raise MigrationError(f"{name}: named array capacity requires shared declaration proof")
            _shared_bound(plan, capacity)
        elif _positive_integer(capacity) is None:
            raise MigrationError(f"{name}: array capacity must be positive and fixed")
    return base.strip() + dimensions


def _compiler_profiles() -> list[tuple[str, str, bool]]:
    compilers = [shutil.which(name) for name in ("g++-13", "clang++-18")]
    if not all(compilers):
        raise MigrationError("binding type proof requires both g++-13 and clang++-18")
    return [(compiler, optimization, testing) for compiler in compilers
            for optimization in ("-O0", "-O2") for testing in (False, True)]


def _syntax_check(plan: Plan, source: str, text: str, compiler: str, optimization: str, testing: bool) -> None:
    """Compile probes without producing or linking any executable/storage."""
    with tempfile.TemporaryDirectory(prefix="clash-class-type-proof-") as temporary:
        dependencies = Path(temporary) / "dependencies.d"
        command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions", "-fno-rtti",
                   "-fno-pie", "-D_REENTRANT", optimization, "-fsyntax-only", "-x", "c++",
                   "-MMD", "-MF", str(dependencies), "-iquote", str((plan.root / source).parent)]
        for include in ("src/platform", "src/compatibility", "src/instrumentation", "src", "."):
            command += ["-I", str(plan.root / include)]
        if testing:
            command.append("-DCLASH95_TESTING=1")
        command.append("-")
        try:
            process = subprocess.run(command, input=text, cwd=plan.root, capture_output=True, text=True, timeout=45)
        except subprocess.TimeoutExpired as error:
            raise MigrationError(f"{source}: binding type proof timed out for {compiler}") from error
        if dependencies.exists():
            for dependency in shlex.split(dependencies.read_text().replace("\\\n", " ").partition(":")[2]):
                path = Path(dependency).resolve()
                if path.is_relative_to(plan.root) and path.is_file():
                    _read(plan, path.relative_to(plan.root).as_posix())
        if process.returncode:
            raise MigrationError(f"{source}: binding type proof failed for {Path(compiler).name}{optimization}: {process.stderr[-2500:]}")


def _prove_binding_types(plan: Plan, globals_: dict[str, str], declarations: dict,
                         uses: dict[str, set[str]], foundation: str) -> None:
    extended = {name for name, type_ in globals_.items()
                if re.search(r"\b(?:CLASH95_INTERNAL|_UNKNOWN)\b", declarations[name]["decl"])
                or any(IDENTIFIER.fullmatch(bound.strip()) for bound in re.findall(r"\[([^]]+)\]", type_))}
    if not extended:
        return
    capacities = {bound.strip(): _shared_bound(plan, bound.strip()) for name in extended
                  for bound in re.findall(r"\[([^]]+)\]", globals_[name]) if IDENTIFIER.fullmatch(bound.strip())}
    profiles = _compiler_profiles()
    contexts = {"src/__binding_shared_proof.cpp": (f'#include "{PurePosixPath(foundation).name}"\n', set(extended))}
    for name in sorted(extended):
        owner = declarations[name].get("owner")
        sources = set(uses[name])
        if not isinstance(owner, str) or not owner:
            raise MigrationError(f"{name}: binding type proof requires a canonical storage owner")
        owner = str(PurePosixPath(owner).with_suffix(".cpp")) if owner.endswith(".c") else owner
        if not _inside(plan.root, owner).is_file():
            raise MigrationError(f"{name}: binding type proof requires the canonical storage owner {owner}")
        sources.add(owner)
        for source in sources:
            if source not in contexts:
                contexts[source] = (_read(plan, source), set())
            contexts[source][1].add(name)
    marker = "CLASH95_MIGRATION_TYPE_PROOF"
    for source, (original, names) in contexts.items():
        if marker in original:
            raise MigrationError(f"{source}: reserved binding type evidence marker already exists")
        proof, captures = [], {}
        for index, name in enumerate(sorted(names)):
            type_ = globals_[name]
            numeric_type = re.sub(r"\[\s*([A-Za-z_][A-Za-z_0-9]*)\s*\]",
                                  lambda match: f"[{capacities[match[1]]}]", type_)
            alias = marker + "_type_" + str(index)
            proof += [declarations[name]["decl"], f"using {alias} = {numeric_type};",
                      f'static_assert(__is_same(decltype(::{name}), {alias}), "original binding type changed");',
                      f'static_assert(__is_same(decltype((::{name})), {alias}&), "binding must be an exact reference");',
                      f'static_assert(sizeof(::{name}) == sizeof({alias}), "binding extent changed");',
                      f'static_assert(__alignof__(::{name}) == __alignof__({alias}), "binding alignment changed");']
            if "_UNKNOWN" in IDENTIFIERS.findall(type_):
                proof.append('static_assert(__is_same(_UNKNOWN, unsigned char), "opaque type must retain its existing byte typedef");')
            for capacity in re.findall(r"\[\s*([A-Za-z_][A-Za-z_0-9]*)\s*\]", type_):
                captures[capacity] = capacities[capacity]
                proof.append(f'static_assert(({capacity}) == {capacities[capacity]}, "shared array capacity changed");')
            if "CLASH95_INTERNAL" in declarations[name]["decl"]:
                captures["CLASH95_INTERNAL"] = None
        candidate = original + "\n" + "\n".join(proof) + "\n"
        compile_text = candidate
        for index, token in enumerate(captures):
            candidate += f"{marker}_{index}_BEGIN {token} {marker}_{index}_END\n"
        for compiler, optimization, testing in profiles:
            expanded = _preprocess(plan, source, candidate, compiler, optimization, testing)
            for index, (token, value) in enumerate(captures.items()):
                tag = marker + "_" + str(index)
                actual = _marked_capture(expanded, tag)
                if value is None:
                    if re.sub(r"\s+", "", actual) not in {"", '__attribute__((visibility("hidden")))'}:
                        raise MigrationError(f"{source}: CLASH95_INTERNAL is not the known visibility-only attribute")
                elif (_positive_integer(actual) != value
                      and not (actual == token and _shared_enum_value(plan, token) == value)):
                    raise MigrationError(f"{source}: {token} capacity expansion differs from its shared literal declaration")
            # Compile original includes, retaining system-header treatment;
            # feeding flattened -P output back to Clang changes diagnostics.
            _syntax_check(plan, source, compile_text, compiler, optimization, testing)
        plan.type_proofs.append({"source": source, "globals": sorted(names), "shared_header": foundation,
                                 "capacities": capacities,
                                 "verified_profiles": [Path(compiler).name + optimization + ("-testing" if testing else "-runtime")
                                                       for compiler, optimization, testing in profiles]})


def _macro_inventory(plan: Plan, sources: list[str]) -> dict[str, set[str]]:
    """Follow local includes and collect transitive macro identifier dependencies."""
    pending, visited, macros = list(sources), set(), {}
    while pending:
        relative = pending.pop()
        if relative in visited:
            continue
        visited.add(relative)
        text = _read(plan, relative)
        folded = text.replace("\\\n", " ")
        for match in re.finditer(r"(?m)^\s*#\s*define\s+([A-Za-z_]\w*)([^\n]*)", folded):
            name, value = match.groups()
            if value.startswith("("):
                # No whitespace separates function-like macro names from their
                # parameter list; a replacement need not have leading space.
                closing = value.find(")")
                value = value[closing + 1:] if closing >= 0 else value
            dependencies = set(IDENTIFIERS.findall(mask_c(value)))
            if "##" in value:
                dependencies.add("__MIGRATION_TOKEN_PASTE")
            if name in macros and macros[name] != dependencies:
                dependencies |= macros[name] | {"__MIGRATION_AMBIGUOUS_" + name}
            macros[name] = dependencies
        for include in re.finditer(r'(?m)^\s*#\s*include\s+([<"])([^>"\n]+)[>"]', text):
            directories = [(plan.root / relative).parent] if include[1] == '"' else []
            directories += [plan.root / entry for entry in
                            ("src/platform", "src/compatibility", "src/instrumentation", "src", ".")]
            for directory in directories:
                target = directory / include[2]
                if target.is_file() and target.resolve().is_relative_to(plan.root.resolve()):
                    pending.append(target.resolve().relative_to(plan.root.resolve()).as_posix())
                    break
    return macros


def _expand_tokens(tokens: set[str], macros: dict[str, set[str]]) -> set[str]:
    result, pending = set(tokens), list(tokens)
    while pending:
        for token in macros.get(pending.pop(), set()):
            if token not in result:
                result.add(token)
                pending.append(token)
    return result


def _macro_spans(body: str, macros: dict[str, set[str]]) -> list[tuple[int, int, str]]:
    """Choose complete outer invocation spans; real preprocessing verifies them."""
    code, consumed, result = mask_c(body), 0, []
    for match in IDENTIFIERS.finditer(code):
        if match.start() < consumed or match[0] not in macros:
            continue
        end = match.end()
        cursor = end
        while cursor < len(code) and code[cursor].isspace():
            cursor += 1
        if cursor < len(code) and code[cursor] == "(":
            depth = 1
            cursor += 1
            while cursor < len(code) and depth:
                depth += (code[cursor] == "(") - (code[cursor] == ")")
                cursor += 1
            if depth:
                raise MigrationError(f"macro {match[0]} has an unbalanced invocation")
            end = cursor
        result.append((match.start(), end, match[0]))
        consumed = end
    return result


def _preprocess(plan: Plan, source: str, text: str, compiler: str, optimization: str, testing: bool) -> str:
    """Use the supported GNU++20 profile and retain local dependency snapshots."""
    with tempfile.TemporaryDirectory(prefix="clash-class-preprocess-") as directory:
        dependencies = Path(directory) / "dependencies.d"
        command = [compiler, "-std=gnu++20", "-U_GNU_SOURCE", "-fno-exceptions", "-fno-rtti",
                   "-fno-pie", "-D_REENTRANT",
                   optimization, "-E", "-P", "-MMD", "-MF", str(dependencies), "-x", "c++",
                   "-iquote", str((plan.root / source).parent)]
        for include in ["src/platform", "src/compatibility", "src/instrumentation", "src", "."]:
            command += ["-I", str(plan.root / include)]
        if testing:
            command.append("-DCLASH95_TESTING=1")
        command.append("-")
        try:
            process = subprocess.run(command, input="#line 1 " + json.dumps(str(plan.root / source)) + "\n" + text,
                                     cwd=plan.root, capture_output=True, text=True, timeout=30)
        except subprocess.TimeoutExpired as error:
            raise MigrationError(f"{source}: preprocessing timed out for {compiler}") from error
        if process.returncode:
            raise MigrationError(f"{source}: preprocessing failed for {compiler}: {process.stderr[-3000:]}")
        if not dependencies.exists():
            raise MigrationError(f"{source}: preprocessor omitted dependency evidence")
        for dependency in shlex.split(dependencies.read_text().replace("\\\n", " ").split(":", 1)[1]):
            path = Path(dependency).resolve()
            if path.is_relative_to(plan.root) and path.is_file():
                _read(plan, path.relative_to(plan.root).as_posix())
        return process.stdout


def _marked_capture(text: str, marker: str) -> str:
    matches = re.findall(r"\b" + marker + r"_BEGIN\b(.*?)\b" + marker + r"_END\b", text, re.S)
    if len(matches) != 1:
        raise MigrationError("macro preprocessing did not preserve unique invocation boundaries")
    return matches[0].strip()


def _replace_spans(text: str, replacements: list[tuple[int, int, str]]) -> str:
    for start, end, replacement in sorted(replacements, reverse=True):
        text = text[:start] + replacement + text[end:]
    return text


def _expand_bound_macros(
    plan: Plan, source: str, text: str, definition, name: str,
    macros: dict[str, set[str]], globals_: set[str], callbacks: set[str], arguments: list[str],
) -> tuple[str, set[str]]:
    """Expand only state/callback-bearing invocations, with compiler token proof.

    The original complete method is preprocessed for dependency discovery and
    equivalence checks only. Generated source replaces individual invocation
    spans; unrelated expressions, comments, macros and formatting remain intact.
    No macro is redefined and no global cell or pointed-to record is copied.
    """
    body = text[definition.opening_brace:definition.end]
    spans = _macro_spans(body, macros)
    if not spans:
        return body, set(IDENTIFIERS.findall(mask_c(body)))
    dependencies = _expand_tokens(set(IDENTIFIERS.findall(mask_c(body))), macros)
    if dependencies & CONTEXT_MACROS or re.search(r'\b(?:u8|u|U|L)?R"', body):
        raise MigrationError(f"{name}: context-sensitive macros or raw strings require a manual binding")
    # A replacement without token pasting can only introduce identifiers
    # already present in its replacement/argument dependency closure. Numeric
    # constants and ordinary type macros need no expansion or compiler work.
    if not any(_expand_tokens(set(IDENTIFIERS.findall(mask_c(body[start:end]))), macros)
               & (globals_ | callbacks | {"__MIGRATION_TOKEN_PASTE"}) for start, end, _ in spans):
        return body, dependencies
    compilers = [shutil.which(compiler) for compiler in ("g++-13", "clang++-18")]
    if not all(compilers):
        raise MigrationError(f"{name}: macro binding requires both g++-13 and clang++-18 preprocessors")
    marker = "CLASH95_MIGRATION_MACRO_PROOF"
    if marker in text or any(token.startswith(marker) for token in macros):
        raise MigrationError(f"{name}: reserved preprocessing evidence marker already exists")
    markers = [marker + "_" + str(index) for index in range(len(spans))]
    annotated = _replace_spans(body, [
        (start, end, f" {tag}_BEGIN " + body[start:end] + f" {tag}_END ")
        for (start, end, _), tag in zip(spans, markers)])

    def materialize(candidate):
        return (text[:definition.opening_brace] + f" {marker}_BEGIN " + candidate
                + f" {marker}_END " + text[definition.end:])

    expansions, proofs, expanded_tokens = None, [], set()
    profiles = [(compiler, optimization, testing) for compiler in compilers
                for optimization in ("-O0", "-O2") for testing in (False, True)]
    for compiler, optimization, testing in profiles:
        original = _marked_capture(_preprocess(plan, source, materialize(body), compiler, optimization, testing), marker)
        instrumented = _marked_capture(_preprocess(plan, source, materialize(annotated), compiler, optimization, testing), marker)
        pieces = [_marked_capture(instrumented, tag) for tag in markers]
        stripped = instrumented
        for tag in markers:
            stripped = re.sub(r"\b" + tag + r"_(?:BEGIN|END)\b", "", stripped)
        if PP_TOKENS.findall(original) != PP_TOKENS.findall(stripped):
            raise MigrationError(f"{name}: macro invocation boundaries changed preprocessing semantics")
        expanded_tokens.update(IDENTIFIERS.findall(mask_c(original)))
        selected = []
        for (start, end, _), piece in zip(spans, pieces):
            code = mask_c(piece)
            hidden_globals = _direct_globals(code, globals_, arguments)
            hidden_callbacks = _direct_globals(code, callbacks, arguments)
            # Stringification/token pasting can consume a canonical spelling
            # without reading its value. Freeze that invocation before the
            # later identifier binding pass, so qualification cannot change it.
            consumed_names = _direct_globals(mask_c(body[start:end]), globals_ | callbacks, arguments)
            selected.append(piece if hidden_globals or hidden_callbacks or consumed_names else None)
        if expansions is None:
            expansions = selected
        elif [None if item is None else PP_TOKENS.findall(item) for item in expansions] != [
                None if item is None else PP_TOKENS.findall(item) for item in selected]:
            raise MigrationError(f"{name}: bound macro expansion differs across compiler/build profiles")
        proofs.append((compiler, optimization, testing, PP_TOKENS.findall(original)))
    replacements = [(start, end, expansion) for (start, end, _), expansion in zip(spans, expansions)
                    if expansion is not None]
    rewritten = _replace_spans(body, replacements)
    if replacements:
        for compiler, optimization, testing, wanted in proofs:
            actual = _marked_capture(_preprocess(plan, source, materialize(rewritten), compiler, optimization, testing), marker)
            if PP_TOKENS.findall(actual) != wanted:
                raise MigrationError(f"{name}: selective macro expansion changed the preprocessed body")
        for (start, end, macro), expansion in zip(spans, expansions):
            if expansion is not None:
                plan.macro_expansions.append({"identity": name, "macro": macro,
                    "invocation": body[start:end], "expanded": expansion,
                    "verified_profiles": [Path(compiler).name + optimization + ("-testing" if testing else "-runtime")
                                          for compiler, optimization, testing, _ in proofs]})
    return rewritten, expanded_tokens


def _qualify_functions(
    body: str, function_names: set[str], parameters: list[str], *,
    same_class: set[str] | None = None, direct_methods: set[str] | None = None,
    caller: str = "", boundaries: list[dict] | None = None,
) -> str:
    """Use proved fixed-signature methods for direct calls; keep ABI values.

    Function addresses, stored function values and indirect syntactic forms
    still name the historical free function. Variadic callees retain that same
    boundary so every supplied expression is evaluated by the original call.
    """
    same_class = same_class or set()
    direct_methods = direct_methods or set()
    masked = mask_c(body)
    replacements = []
    for match in IDENTIFIERS.finditer(masked):
        name = match[0]
        if name not in function_names:
            continue
        before = masked[:match.start()].rstrip()
        if before.endswith((".", "->")):
            continue
        start, global_qualification = match.start(), before.endswith("::")
        if global_qualification:
            start = len(before) - 2
            qualifier = re.search(r"([A-Za-z_][A-Za-z_0-9]*)\s*$", before[:start])
            if qualifier and qualifier[1] not in {"return", "co_return", "throw", "delete", "sizeof", "alignof"}:
                # A namespace-qualified leaf is not proof of the global target.
                continue
        elif name in parameters:
            continue
        # A definition-local variable hiding a known function is not a call boundary.
        if re.search(r"\b(?:int|char|long|short|float|double|auto|_DWORD|_BYTE)\s*[*&]?\s*$", before):
            raise MigrationError(f"local variable shadows function identity {name}")
        direct_call = masked[match.end():].lstrip().startswith("(")
        if direct_call and name in direct_methods:
            replacements.append((start, match.end(), "this->" + name))
            continue
        if name in same_class and boundaries is not None:
            address_prefix = before[:start].rstrip() if global_qualification else before
            if direct_call:
                kind = "variadic-callee"
            elif address_prefix.endswith("&"):
                kind = "function-address"
            else:
                kind = "function-value-or-indirect-call"
            boundaries.append({"caller": caller, "callee": name, "kind": kind})
        if not global_qualification:
            replacements.append((match.start(), match.end(), "::" + name))
    return _replace_spans(body, replacements)


def _include_for(source: str, header: str) -> str:
    return '#include "' + os.path.relpath(header, str(PurePosixPath(source).parent)).replace("\\", "/") + '"\n'


def _local_context(text: str) -> tuple[set[str], set[str], set[str]]:
    """Names whose source-local visibility cannot be reproduced by includes."""
    definitions = scan_definitions(text, None)
    masked = list(mask_c(text))
    for definition in definitions:
        masked[definition.start:definition.end] = " " * (definition.end - definition.start)
    outside = "".join(masked)
    local_types = set(re.findall(r"\b(?:struct|class|enum|using)\s+([A-Za-z_]\w*)", outside))
    for declaration in re.findall(r"\btypedef\s+([^;]+);", outside):
        names = IDENTIFIERS.findall(declaration)
        if names:
            local_types.add(names[-1])
    local_storage = set()
    for declaration in re.findall(r"\bstatic\s+([^;]+);", outside):
        # A full C++ declarator parser would be needed to move this storage.
        # Conservatively retain every identifier in a source-local declaration.
        local_storage.update(IDENTIFIERS.findall(declaration))
    local_macros = set(re.findall(r"(?m)^\s*#\s*define\s+([A-Za-z_]\w*)", text))
    return local_types, local_storage, local_macros


def _bind_globals(body: str, globals_: dict[str, str], parameters: list[str]) -> str:
    """Replace direct state references, without touching literals or fields.

    Canonical storage names stay in the anchor's out-of-line borrow factory;
    headers expose only private reference types. State-bearing macro invocations
    have already been selectively expanded and checked by both preprocessors.
    """
    fields = {name: f"state_field_{index}_" for index, name in enumerate(globals_)}
    masked, replacements = mask_c(body), []
    for match in IDENTIFIERS.finditer(masked):
        if match[0] not in fields:
            continue
        before = masked[:match.start()].rstrip()
        if before.endswith((".", "->")):
            continue
        start = match.start()
        if before.endswith("::"):
            start = len(before) - 2
            qualifier = re.search(r"([A-Za-z_][A-Za-z_0-9]*)\s*$", before[:start])
            if qualifier and qualifier[1] not in {"return", "co_return", "throw", "delete", "sizeof", "alignof", "decltype"}:
                raise MigrationError(f"qualified state {match[0]} requires a manual binding")
        elif match[0] in parameters:
            continue
        replacements.append((start, match.end(), "this->" + fields[match[0]]))
    for start, end, replacement in reversed(replacements):
        body = body[:start] + replacement + body[end:]
    return body


def _direct_globals(code: str, candidates: set[str], parameters: list[str]) -> set[str]:
    result = set()
    for match in IDENTIFIERS.finditer(code):
        if match[0] not in candidates:
            continue
        before = code[:match.start()].rstrip()
        if before.endswith((".", "->")):
            continue
        if match[0] not in parameters or before.endswith("::"):
            result.add(match[0])
    return result


def _header(owner: str, relative: str, methods: list[tuple], globals_: dict[str, str],
            foundation: str = "src/recovered_types.h") -> str:
    lines = ["// Generated by tools/migrate_game_class_bodies.py; borrowed state only.\n", "#pragma once\n",
             _include_for(relative, foundation), "\n"]
    lines += ["namespace clash95 {\n", f"class CLASH95_INTERNAL {owner} final {{\n"]
    for index, type_ in enumerate(globals_.values()):
        lines.append(f"  using state_type_{index} = {type_};\n")
    lines += [" public:\n", f"  static {owner} borrow() noexcept;\n"]
    for name, result, parameters in methods:
        header_parameters = []
        for index, parameter in enumerate(_parts(parameters)):
            if parameter == "...":
                header_parameters.append(parameter)
            else:
                named = re.fullmatch(r"(.+?)([A-Za-z_][A-Za-z_0-9]*)\s*((?:\[[^\]]*\])*)", parameter)
                if not named:
                    raise MigrationError(f"{name}: unsupported header parameter")
                header_parameters.append(named[1] + f"arg_{index}" + named[3])
        lines.append(f"  {result} {name}(" + ", ".join(header_parameters) + ");\n")
    lines.append(" private:\n")
    parameters = ", ".join(f"state_type_{index} &arg_{index}" for index in range(len(globals_)))
    initializers = ", ".join(f"state_field_{index}_(arg_{index})" for index in range(len(globals_)))
    lines.append(f"  explicit {owner}({parameters}) noexcept" + (" : " + initializers if initializers else "") + " {}\n")
    for index in range(len(globals_)):
        lines.append(f"  state_type_{index} &state_field_{index}_;\n")
    lines += ["};\n", "} // namespace clash95\n"]
    return "".join(lines)


def _proven_header(plan: Plan, relative: str, methods: list[tuple], globals_: dict[str, str]) -> tuple[str, str]:
    # Most game records already live in recovered_types.h. Pull in layout and
    # the larger struct surface only when the actual public types require it.
    profiles = [(compiler, optimization, testing) for compiler, optimization, testing in _compiler_profiles()
                if optimization == "-O0" and not testing]
    errors = []
    for foundation in ("src/recovered_types.h", "src/recovered_layout.h"):
        text = _header(plan.owner, relative, methods, globals_, foundation)
        try:
            for compiler, optimization, testing in profiles:
                _syntax_check(plan, relative, text, compiler, optimization, testing)
            return text, foundation
        except MigrationError as error:
            errors.append(str(error))
    raise MigrationError("generated class header lacks a proven shared type context:\n" + "\n".join(errors))


def make_plan(root: Path, owner: str, stage: str = "extract", max_lines: int = MAX_LINES) -> Plan:
    if not IDENTIFIER.fullmatch(owner) or stage not in {"extract", "relocate"}:
        raise MigrationError("select one concrete class and extract or relocate stage")
    if max_lines < 20 or max_lines > MAX_LINES:
        raise MigrationError(f"shard limit must be between 20 and {MAX_LINES} lines")
    plan = Plan(root.resolve(), owner, stage, [], [])
    manifest = json.loads(_read(plan, "data/recovered_sources.json"))
    registry = json.loads(_read(plan, "data/game_class_registry.json"))
    declarations = json.loads(_read(plan, "data/recovered_decls.json"))
    if manifest.get("schema_version") != 3:
        raise MigrationError("mechanical class migration requires source manifest schema 3")
    targets = manifest_targets(manifest)
    by_name = {record["name"]: record for record in manifest["functions"]}
    selected = [item for item in registry["identities"] if item.get("class_owner") == owner and item.get("classification") == "game-method"]
    if not selected:
        raise MigrationError(f"no explicitly registered game identities for {owner}")
    if any(helper.get("class_owner") == owner for helper in registry.get("helpers", [])):
        raise MigrationError(f"{owner}: separate support helpers require manual registration-aware extraction")
    names = [item["name"] for item in selected]
    if len(set(names)) != len(names) or any(name not in by_name for name in names):
        raise MigrationError("selected registry identities are duplicate or absent from the source manifest")
    paths = {(item["final_header"], item["final_source"]) for item in selected}
    if len(paths) != 1:
        raise MigrationError("all class members must declare the same primary class-named files")
    header, primary = paths.pop()
    if PurePosixPath(header).name != owner + ".hpp" or PurePosixPath(primary).name != owner + ".cpp":
        raise MigrationError("class destinations must retain the exact class name")
    _inside(plan.root, header)
    _inside(plan.root, primary)
    sources = sorted({by_name[name]["source"] for name in names})
    texts = {source: _read(plan, source) for source in sources}
    bindings = registry.setdefault("class_bindings", [])
    if not isinstance(bindings, list):
        raise MigrationError("class_bindings must be a separate list of address-free glue records")
    selected_bindings = [binding for binding in bindings if binding.get("class_owner") == owner]
    if stage == "extract" and selected_bindings:
        raise MigrationError(f"{owner}: borrowing glue is already registered; refuse duplicate extraction")
    for binding in selected_bindings:
        source = binding["source"]
        if source not in texts:
            texts[source] = _read(plan, source)
        definitions = scan_definitions(texts[source], {binding["qualified_name"]})
        if (len(definitions) != 1 or "original_address" in binding
                or body_sha256(texts[source], definitions[0]) != binding.get("body_sha256")):
            raise MigrationError(f"{owner}: borrowing glue source/hash changed or registration is invalid")
    resolved = {}
    for source, text in texts.items():
        resolved.update(resolve_source_definitions(text, targets, source=source))
    plan.identities = names
    all_functions = set(declarations["functions"])
    global_db = declarations.get("globals", {})
    macros = _macro_inventory(plan, sources) if stage == "extract" else {}
    local_context = {source: _local_context(text) for source, text in texts.items()}
    replacements: dict[str, list[tuple[int, int, str]]] = {source: [] for source in sources}
    methods, bodies, globals_ = [], [], {}
    global_uses: dict[str, set[str]] = {}
    extracted = []
    failure_list = []
    for item in selected:
        name = item["name"]
        record = by_name[name]
        source, text = record["source"], texts[record["source"]]
        definition = resolved[(name, "canonical")]
        if body_sha256(text, definition) != record.get("body_sha256"):
            failure_list.append(f"{name}: source/hash changed; refresh evidence before extraction")
            continue
        signature = text[definition.start:definition.opening_brace].strip()
        body = text[definition.opening_brace:definition.end]
        try:
            if stage == "extract":
                if implementation_name(record) != name or "adapter" in record:
                    raise MigrationError(f"{name}: class is already partially extracted; use a manual integration batch")
                if record.get("linkage") == "static":
                    raise MigrationError(f"{name}: preserve file-local identity with a manual adapter")
                result, parameters, arguments, types = _signature(signature, name)
                _verify_declaration(name, declarations["functions"][name]["decl"], types)
                code = mask_c(body)
                if FORBIDDEN.search(code) or REGISTER_CALL.search(code) or re.search(r"(?m)^\s*#", body):
                    raise MigrationError(f"{name}: local static/thread storage, type introspection, assembly/register contract or body preprocessor directive")
                body, expanded = _expand_bound_macros(
                    plan, source, text, definition, name, macros, set(global_db), set(names), arguments)
                code = mask_c(body)
                tokens = set(IDENTIFIERS.findall(code))
                if FORBIDDEN.search(" ".join(expanded)) or REGISTER_CALL.search(" ".join(expanded)):
                    raise MigrationError(f"{name}: macro-expanded storage, type introspection or register contract needs a manual binding")
                local_types, local_storage, _ = local_context[source]
                signature_tokens = set(IDENTIFIERS.findall(signature))
                if (tokens | expanded | signature_tokens) & local_types or expanded & local_storage:
                    raise MigrationError(f"{name}: source-local type or static storage requires a manual binding")
                local_calls = {token for token in expanded if declarations["functions"].get(token, {}).get("class") == "tu-local"}
                if local_calls:
                    raise MigrationError(f"{name}: file-local callable dependency: {', '.join(sorted(local_calls))}")
                if (expanded & VARARG_TOKENS or any("va_list" in type_ for type_ in types)
                        or ("..." in types and any(re.search(r"&\s*" + re.escape(arg) + r"\b", code) for arg in arguments))):
                    raise MigrationError(f"{name}: active variadic state needs an explicit va_list adapter")
                for global_name in sorted(_direct_globals(code, set(global_db) - set(macros), arguments)):
                    if re.search(r"\b(?:int|char|long|short|float|double|auto|_DWORD|_BYTE)\s*[*&]?\s*" + re.escape(global_name) + r"\b", code):
                        raise MigrationError(f"{name}: local declaration shadows global {global_name}")
                    storage_owner = global_db[global_name].get("owner", "")
                    normalized_owner = str(PurePosixPath(storage_owner).with_suffix(".cpp")) if storage_owner else ""
                    if normalized_owner in sources:
                        raise MigrationError(f"{name}: {global_name} has TU-owned storage; its linkage needs a manual binding")
                    globals_[global_name] = _global_type(global_name, global_db[global_name]["decl"], plan)
                    global_uses.setdefault(global_name, set()).add(source)
                unknown_state = {token for token in expanded if token.startswith("g_")} - set(global_db) - set(macros) - set(arguments)
                if unknown_state:
                    raise MigrationError(f"{name}: state lacks canonical declarations: {', '.join(sorted(unknown_state))}")
                extracted.append((source, definition, signature, body, name, result, parameters, arguments))
                # Only the legacy adapter keeps an unused ellipsis. Genuine
                # variadic bodies were refused above pending a va_list bridge.
                method_parameters = ", ".join(part for part in _parts(parameters) if part != "...")
                methods.append((name, result, method_parameters))
                record["implementation"] = {"kind": "method", "qualified_name": f"clash95::{owner}::{name}", "header": header}
                record["class_owner"] = "clash95::" + owner
                record["adapter"] = {"source": source}
            else:
                if implementation_name(record) != f"clash95::{owner}::{name}" or "adapter" not in record:
                    raise MigrationError(f"{name}: relocation requires every class body to be extracted and validated first")
                if record["source"] == primary or PurePosixPath(record["source"]).stem.startswith(owner + ".part"):
                    raise MigrationError(f"{name}: already relocated; no implicit re-sharding")
                if FORBIDDEN.search(mask_c(body)):
                    raise MigrationError(f"{name}: local storage or assembly makes relocation a manual operation")
                local_types, local_storage, local_macros = local_context[source]
                tokens = set(IDENTIFIERS.findall(mask_c(signature + body)))
                if tokens & (local_types | local_storage | local_macros):
                    raise MigrationError(f"{name}: source-local types, storage or macros cannot silently relocate")
                replacements[source].append((definition.start, definition.end, ""))
                bodies.append((name, signature + "\n" + body + "\n"))
        except (MigrationError, KeyError) as error:
            failure_list.append(str(error))
    if failure_list:
        raise MigrationError("whole class refused:\n" + "\n".join(failure_list))
    if stage == "extract":
        globals_ = dict(sorted(globals_.items()))
        plan.bindings = list(globals_)
        direct_methods = {name for _, _, _, _, name, _, parameters, _ in extracted
                          if "..." not in _parts(parameters)}
        for source, definition, signature, body, name, result, parameters, arguments in extracted:
            rewritten = _bind_globals(_qualify_functions(
                body, all_functions, arguments, same_class=set(names), direct_methods=direct_methods,
                caller=name, boundaries=plan.call_boundaries), globals_, arguments)
            call = f"clash95::{owner}::borrow().{name}(" + ", ".join(arguments) + ")"
            adapter_body = "{\n  " + ("" if result == "void" else "return ") + call + ";\n}"
            method_parameters = ", ".join(part for part in _parts(parameters) if part != "...")
            method = f"{result} clash95::{owner}::{name}({method_parameters})\n{rewritten}"
            replacements[source].append((definition.start, definition.end, signature + "\n" + adapter_body + "\n\n" + method))
        generated_header, foundation = _proven_header(plan, header, methods, globals_)
        _prove_binding_types(plan, globals_, global_db, global_uses, foundation)
        _new_output(plan, header, generated_header)
    for source, edits in replacements.items():
        text = texts[source]
        for start, end, replacement in sorted(edits, reverse=True):
            text = text[:start] + replacement + text[end:]
        include = _include_for(source, header)
        if stage == "extract" and include.strip() not in text:
            if INCLUDES_END in text:
                if text.count(INCLUDES_END) != 1 or text.count("/* CLASH95_GENERATED_INCLUDES_BEGIN") != 1:
                    raise MigrationError(f"{source}: generated include markers must resolve uniquely")
                text = text.replace(INCLUDES_END, include + INCLUDES_END)
            else:
                text = include + text
        plan.changes[source] = text
    if stage == "extract":
        anchor = sources[0]
        factory = "\n// Borrowing glue stays at this original adapter/storage anchor.\n"
        factory += "\n".join(global_db[name]["decl"] for name in globals_) + "\n"
        factory += f"clash95::{owner} clash95::{owner}::borrow() noexcept\n{{\n"
        factory += f"  return {owner}(" + ", ".join("::" + name for name in globals_) + ");\n}\n"
        plan.changes[anchor] = plan.changes[anchor].rstrip() + "\n" + factory
        qualified_factory = f"clash95::{owner}::borrow"
        definitions = scan_definitions(plan.changes[anchor], {qualified_factory})
        if len(definitions) != 1:
            raise MigrationError(f"{owner}: generated borrowing glue does not resolve uniquely")
        bindings.append({"class_owner": owner, "qualified_name": qualified_factory, "source": anchor,
                         "referenced_globals": list(globals_),
                         "body_sha256": body_sha256(plan.changes[anchor], definitions[0])})
    if stage == "relocate":
        _read(plan, header)
        includes: list[str] = []
        for source, text in texts.items():
            if re.search(r"(?m)^\s*#\s*(?:if|ifdef|ifndef|elif|else|endif|undef|pragma)\b", text):
                raise MigrationError(f"{source}: conditional/pragma source context requires a manual relocation")
            source_includes = []
            for match in re.finditer(r'(?m)^\s*#\s*include\s+([<"][^\n]+[>"])\s*$', text):
                include = match[1]
                if include.startswith('"'):
                    target = ((plan.root / source).parent / include[1:-1]).resolve()
                    if not target.is_relative_to(plan.root):
                        raise MigrationError(f"{source}: local include escapes workspace")
                    include = '"' + os.path.relpath(target, (plan.root / primary).parent).replace("\\", "/") + '"'
                directive = "#include " + include + "\n"
                if directive not in source_includes:
                    source_includes.append(directive)
            common = [item for item in includes if item in source_includes]
            if common != [item for item in source_includes if item in includes]:
                raise MigrationError(f"{source}: incompatible include ordering requires a manual relocation")
            includes.extend(item for item in source_includes if item not in includes)
        preamble = ("// Relocated recovered methods; ABI adapters and storage remain in their original translation units.\n"
                    + INCLUDES_BEGIN + "\n" + "".join(includes) + INCLUDES_END + "\n\n")
        shards: list[tuple[str, list[str]]] = []
        current, shard_names = preamble, []
        for name, body in bodies:
            if len((preamble + body).splitlines()) > max_lines:
                raise MigrationError(f"{name}: one complete method exceeds the {max_lines}-line shard cap")
            if len((current + body + "\n").splitlines()) > max_lines and shard_names:
                shards.append((current, shard_names))
                current, shard_names = preamble, []
            current += body + "\n"
            shard_names.append(name)
        if shard_names:
            shards.append((current, shard_names))
        shard_paths = []
        for index, (text, shard_names) in enumerate(shards, 1):
            destination = primary if index == 1 else str(PurePosixPath(primary).with_name(f"{owner}.part{index:02}.cpp"))
            _new_output(plan, destination, text)
            shard_paths.append(destination)
            for name in shard_names:
                by_name[name]["source"] = destination
        for item in selected:
            if len(shard_paths) > 1:
                item["additional_sources"] = shard_paths[1:]
    plan.changes["data/game_class_registry.json"] = json.dumps(registry, indent=2) + "\n"
    # Resolve every affected canonical body and adapter in the planned bytes.
    updated_targets = manifest_targets(manifest)
    affected = {target.source for target in updated_targets if target.identity in names}
    for source in affected:
        text = plan.changes.get(source)
        if text is None:
            text = _read(plan, source)
        for key, definition in resolve_source_definitions(text, updated_targets, source=source).items():
            name, role = key
            if name in names:
                destination = by_name[name] if role == "canonical" else by_name[name]["adapter"]
                destination["body_sha256"] = body_sha256(text, definition)
    manifest["source_file_count"] = len(manifest_sources(manifest))
    plan.changes["data/recovered_sources.json"] = json.dumps(manifest, indent=2) + "\n"
    return plan


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--class", dest="owner", required=True)
    parser.add_argument("--stage", choices=("extract", "relocate"), default="extract")
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--max-lines", type=int, default=MAX_LINES)
    parser.add_argument("--write", action="store_true", help="explicitly apply the complete supported class batch")
    parser.add_argument("--diff", action="store_true", help="print the reviewable patch without writing unless --write is also given")
    args = parser.parse_args(argv)
    try:
        plan = make_plan(args.root, args.owner, args.stage, args.max_lines)
        if args.diff:
            for relative, proposed in sorted(plan.changes.items()):
                before = (plan.snapshots.get(relative) or b"").decode().replace("\r\n", "\n")
                print("".join(difflib.unified_diff(before.splitlines(True), proposed.splitlines(True), fromfile=relative, tofile=relative)), end="")
        result = plan.summary()
        if args.write:
            plan.apply()
            result["written"] = True
        print(json.dumps(result, sort_keys=True))
        return 0
    except (MigrationError, ImplementationError, OSError, ValueError, KeyError) as error:
        print(json.dumps({"error": str(error), "written": False}, sort_keys=True))
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
