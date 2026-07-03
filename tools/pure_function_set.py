#!/usr/bin/env python3
"""Define the deterministic "pure testable" function set for coverage.

A function is in the unit-test coverage denominator when its body:
  - references no global/gameData symbol (dword_/byte_/word_/off_/unk_/flt_/dbl_
    or the literal gameData),
  - calls no impure/IO/render/alloc/platform helper,
  - performs no indirect/vtable/function-pointer call `(*...)(`  (those are COM/
    dispatch trampolines that need a live object graph, not unit-testable),
  - contains no JUMPOUT/__asm control-flow scar,
  - is an actual definition in clash95.c.

Emits JSON: {"functions":[{"name","start_line","end_line"}], "count":N}.
Line numbers are 1-based; end_line is exclusive (next definition / EOF).
This list is the frozen denominator for coverage measurement.
"""
import json
import re
import sys

SRC = "clash95.c"

GLOBAL = re.compile(
    r"\b(gameData|dword_[0-9A-F]+|byte_[0-9A-F]+|word_[0-9A-F]+|"
    r"off_[0-9A-F]+|unk_[0-9A-F]+|flt_[0-9A-F]+|dbl_[0-9A-F]+|"
    r"qword_[0-9A-F]+|xmmword_[0-9A-F]+)\b"
)
IMPURE_CALL = re.compile(
    r"\b(Render_|Surface_|CSS_|Audio_|Music_|Sound_|Video_|Avi|AviPlayer_|DLX"
    r"|Platform_|Input_|InputBackend_|File_|FileSystem_|IO_F?Open|IO_Open"
    r"|IO_Close|fopen|fread|fwrite|fclose|malloc|calloc|realloc|free|Mem_"
    r"|nmalloc|nfree|GetTimeZone|timeGetTime|CreateWindow|DirectDraw|Debug_Log"
    r"|MiniMap_|Cursor_|Font_|Dialog_|Menu_)\w*\s*\("
)
INDIRECT_CALL = re.compile(r"\(\s*\*")  # (*fn)(...) / (*(T**)x)(...)
SCAR = re.compile(r"\bJUMPOUT\b|\b__asm\b|__debugbreak")


def find_defs(lines):
    defs = []
    for i, ln in enumerate(lines):
        m = re.match(r"^[A-Za-z_][A-Za-z0-9_ *]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\(", ln)
        if not m:
            continue
        name = m.group(1)
        if name in ("if", "while", "for", "switch", "return", "sizeof"):
            continue
        j = i
        depth = 0
        isdef = False
        sc = 0
        while j < len(lines) and sc < 60:
            done = False
            for ch in lines[j]:
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                elif ch == ";" and depth <= 0:
                    done = True
                    break
                elif ch == "{" and depth <= 0:
                    isdef = True
                    done = True
                    break
            if done:
                break
            j += 1
            sc += 1
        if isdef:
            defs.append((name, i))
    return defs


def main():
    lines = open(SRC, errors="replace").readlines()
    defs = find_defs(lines)
    ends = [defs[k + 1][1] for k in range(len(defs) - 1)] + [len(lines)]
    out = []
    seen = set()
    for (name, start), end in zip(defs, ends):
        if name in seen:
            continue
        body = "".join(lines[start:end])
        # strip the signature line's own parens noise by scanning whole body
        if GLOBAL.search(body):
            continue
        if IMPURE_CALL.search(body):
            continue
        if INDIRECT_CALL.search(body):
            continue
        if SCAR.search(body):
            continue
        seen.add(name)
        out.append({"name": name, "start_line": start + 1, "end_line": end + 1})
    json.dump({"functions": out, "count": len(out)}, sys.stdout, indent=1)


if __name__ == "__main__":
    main()
