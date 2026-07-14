#!/usr/bin/env bash
# Gate G3 for the magic-number campaign: prove a source change is
# object-code-identical (not merely value-identical) by compiling clash95.c to
# an object at a base state and in the working tree, then diffing normalized
# disassembly. Use for token-changing transforms (accessor-macro upgrades,
# enum substitutions) where the preprocessed-token gate cannot apply.
#
# Usage:
#   bash tools/obj_diff_gate.sh --snapshot out.txt    # capture pre-change asm
#   bash tools/obj_diff_gate.sh out.txt               # diff working tree vs snapshot
#
# Requires GNU/Clang toolchain + objdump (WSL/Linux). Flags mirror CMake's
# clash95 objects: -std=gnu89 -w -ffunction-sections -fdata-sections -fno-pie.
set -euo pipefail

CFLAGS="-std=gnu89 -w -ffunction-sections -fdata-sections -fno-pie -I. -Icompat -c"

disasm() {
  local obj="$1"
  gcc $CFLAGS clash95.c -o "$obj"
  # objdump disassembly, stripped of addresses/offsets/raw bytes so only the
  # instruction mnemonics+operands remain (symbol-relative, position-stable).
  objdump -d --no-show-raw-insn "$obj" \
    | sed -E 's/^[[:space:]]*[0-9a-f]+:[[:space:]]*//; s/<([^+>]*)(\+0x[0-9a-f]+)?>/<\1>/g; s/0x[0-9a-f]+/0xN/g' \
    | grep -vE '^$|file format|Disassembly of section'
}

if [ "${1:-}" = "--snapshot" ]; then
  OBJ="$(mktemp).o"
  disasm "$OBJ" > "$2"
  rm -f "$OBJ"
  echo "asm snapshot: $2 ($(wc -l < "$2") insns)"
  exit 0
fi

BASE="$1"
OBJ="$(mktemp).o"
AFTER="$(mktemp)"
disasm "$OBJ" > "$AFTER"
rm -f "$OBJ"

if diff -q "$BASE" "$AFTER" >/dev/null; then
  echo "{\"ok\": true, \"insns\": $(wc -l < "$AFTER")}"
  rm -f "$AFTER"
  exit 0
else
  echo "{\"ok\": false, \"diff\": ["
  diff "$BASE" "$AFTER" | head -40
  echo "]}"
  rm -f "$AFTER"
  exit 1
fi
