#!/usr/bin/env python3
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

import apply_diag_respells as resp

REPO = Path(__file__).resolve().parents[1]

NEW_UNUSED = {
    "src/persistence/004479C0_0044AE10_persistence_004.c": {"v112", "v9", "v13", "v4", "v2"},
    "src/clips/0048D570_0048ED00_clips_008.c": {"v7"},
    "src/clips/0048ED60_00490430_clips_009.c": {"v2"},
    "src/clips/004943E0_00495930_clips_001.c": {"v4", "v5", "v2"},
    "src/clips/00496000_00497BD0_clips_001.c": {"currentItem"},
    "src/clips/004A6C40_004A8520_clips_005.c": {"v5"},
    "src/clips/004B1860_004B2E40_clips_004.c": {"v8"},
    "src/clips/004B8EC0_004BA500_clips_008.c": {"v3"},
    "src/clips/004BA5F0_004BBF90_clips_009.c": {"v7", "v5"},
    "src/clips/004BBFE0_004BD710_clips_010.c": {"v4", "v7"},
    "src/clips/004C0620_004C1B80_clips_013.c": {"v24"},
    "src/clips/004C1BB0_004C33E0_clips_014.c": {"v17"},
    "src/media/0047AA90_0047C760_media_013.c": {"v6"},
    "src/media/0047DFE0_0047F7F0_media_015.c": {"callbackNode", "v16", "v5", "v50"},
    "src/runtime/004D1F50_004D35A0_runtime_002.c": {"v3"},
    "src/runtime/004E1A90_004E3400_runtime_012.c": {"v11"},
}

NEW_INT_TO_POINTER = {
    "src/strategic/00456706_00457789_strategic_008.c",
    "src/units/00414390_00416750_units_004.c",
}

DIAG = re.compile(
    r"^(?P<full>(?P<file>[^:\n]+):(?P<line>\d+):(?P<col>\d+):\s+warning:\s+(?P<msg>.*)\[-W(?P<cat>[a-z0-9-]+)\]\s*)$",
    re.M,
)
VAR = re.compile(r"(?:unused variable|variable) [‘']([^’']+)[’']")

MANUAL_REPLACEMENTS = {
    "src/clips/0049B530_0049CD60_clips_004.c": [
        ("theResult[2] != g_ClipsFalseSymbol", "(int)theResult[2] != g_ClipsFalseSymbol"),
    ],
    "src/clips/004A0080_004A1CF0_clips_001.c": [
        ("fieldIndex <= value[4] + 1", "fieldIndex <= (int)value[4] + 1"),
        ("value[4] + 1 < fieldPos", "(int)value[4] + 1 < fieldPos"),
        ("n <= value2[4] - value2[3] + 1", "n <= (int)value2[4] - (int)value2[3] + 1"),
        ("fieldIndex <= item1[4] + 1", "fieldIndex <= (int)item1[4] + 1"),
    ],
    "src/clips/004B1860_004B2E40_clips_004.c": [
        ("evalResult[2] == g_ClipsFalseSymbol", "(int)evalResult[2] == g_ClipsFalseSymbol"),
    ],
    "src/clips/004CCEC0_004CEAC0_clips_004.c": [
        ("v19 != v20[1]", "v19 != (int)v20[1]"),
    ],
    "src/clips/00496000_00497BD0_clips_001.c": [
        ("g_CLIPS_DynamicConstraintCheckingFlag = argData[2] != __PAIR64__(g_ClipsFalseSymbol, 2);", "g_CLIPS_DynamicConstraintCheckingFlag = argData[0] != __PAIR64__(g_ClipsFalseSymbol, 2);"),
        ("g_CLIPS_StaticConstraintCheckingFlag = argData[2] != __PAIR64__(g_ClipsFalseSymbol, 2);", "g_CLIPS_StaticConstraintCheckingFlag = argData[0] != __PAIR64__(g_ClipsFalseSymbol, 2);"),
    ],
    "src/units/004191F0_0041A690_units_006.c": [
        ("if ( g_RenderDevice == &g_MainRenderDevice && cursorOverlayPresented )", "if ( g_RenderDevice == (_UNKNOWN *)&g_MainRenderDevice && cursorOverlayPresented )"),
    ],
    "src/state/00000000_0054FFFF_recovered_state.c": [
        ("_UNKNOWN g_InGameSettingsButtonWidgetsTemplate;", "_UNKNOWN g_InGameSettingsButtonWidgetsTemplate[1];"),
    ],
    "data/recovered_decls.json": [
        ("extern _UNKNOWN g_InGameSettingsButtonWidgetsTemplate;", "extern _UNKNOWN g_InGameSettingsButtonWidgetsTemplate[];"),
    ],
}


def relative_file(path: str) -> str | None:
    normalized = path.replace("\\", "/")
    index = normalized.find("src/")
    return normalized[index:] if index >= 0 else None


def filtered_diagnostics(text: str) -> str:
    selected = []
    for match in DIAG.finditer(text):
        rel = relative_file(match.group("file"))
        if rel is None:
            continue
        category = match.group("cat")
        if category == "int-to-pointer-cast" and rel in NEW_INT_TO_POINTER:
            selected.append(match.group("full"))
            continue
        if category not in {"unused-variable", "unused-but-set-variable"}:
            continue
        variable = VAR.search(match.group("msg"))
        if variable and variable.group(1) in NEW_UNUSED.get(rel, set()):
            selected.append(match.group("full"))
    return "\n".join(selected) + ("\n" if selected else "")


def replace_exact(path: str, old: str, new: str) -> bool:
    target = REPO / path
    raw = target.read_bytes()
    text = raw.decode("latin-1")
    if new in text:
        return False
    count = text.count(old)
    if count != 1:
        raise RuntimeError(f"{path}: expected one occurrence of {old!r}, found {count}")
    target.write_bytes(text.replace(old, new, 1).encode("latin-1"))
    return True


def run(*args: str) -> None:
    subprocess.run(args, cwd=REPO, check=True)


def main() -> int:
    if len(sys.argv) != 2:
        raise SystemExit("usage: repair_ci_regressions.py compiler.log")
    log = Path(sys.argv[1]).read_text(encoding="utf-8", errors="replace")
    selected = filtered_diagnostics(log)
    sites = resp.collect_sites(selected, {"int-to-pointer-cast", "unused-variable", "unused-but-set-variable"}, None)
    touched = set()
    review = {}
    applied = 0
    for rel in sorted(sites):
        count, pending = resp.apply_file(rel, sites[rel])
        applied += count
        if count:
            touched.add(rel)
        if pending:
            review[rel] = pending
    if review:
        raise RuntimeError(f"targeted diagnostic repair left review sites: {review}")
    bad = resp.syntax_check(sorted(sites))
    if bad:
        raise RuntimeError("syntax failures after diagnostic repair: " + "; ".join(bad))
    for path, replacements in MANUAL_REPLACEMENTS.items():
        for old, new in replacements:
            if replace_exact(path, old, new) and path.endswith(".c"):
                touched.add(path)
    run(sys.executable, "tools/update_split_manifest_hashes.py", "--update")
    run(sys.executable, "tools/gen_subsystem_headers.py", "--write")
    run(sys.executable, "tools/gen_subsystem_headers.py", "--check")
    print(f"targeted respells={applied} touched-c={len(touched)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
