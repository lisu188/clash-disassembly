#!/usr/bin/env bash
# Compare normalized recovered-code disassembly against a snapshot.
#
# Compiles every GNU C17 / GNU C++20 translation unit named by
# data/recovered_sources.json.
#
# Usage:
#   bash tools/obj_diff_gate.sh --snapshot out.asm
#   bash tools/obj_diff_gate.sh out.asm
#   bash tools/obj_diff_gate.sh --manifest path/to/manifest.json ...
#
# The historical positional snapshot workflow remains valid. --split remains
# a compatibility no-op. CC, CXX, OBJDUMP, and PYTHON may be set in the environment.
# --normalize-cpp-paths approves only .cpp -> .c TU-label normalization.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MANIFEST="data/recovered_sources.json"
SNAPSHOT=""
POSITIONAL=()
NORMALIZE_CPP_PATHS=0

usage() {
  sed -n '2,13p' "$0" | sed 's/^# \{0,1\}//'
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --split)
      shift
      ;;
    --normalize-cpp-paths)
      NORMALIZE_CPP_PATHS=1
      shift
      ;;
    --manifest)
      [ "$#" -ge 2 ] || { echo "--manifest requires a path" >&2; exit 2; }
      MANIFEST="$2"
      shift 2
      ;;
    --snapshot)
      [ "$#" -ge 2 ] || { echo "--snapshot requires an output path" >&2; exit 2; }
      SNAPSHOT="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    --*)
      echo "unknown option: $1" >&2
      usage >&2
      exit 2
      ;;
    *)
      POSITIONAL+=("$1")
      shift
      ;;
  esac
done

if [ -n "$SNAPSHOT" ] && [ "${#POSITIONAL[@]}" -ne 0 ]; then
  echo "--snapshot does not accept a comparison snapshot" >&2
  exit 2
fi
if [ -z "$SNAPSHOT" ] && [ "${#POSITIONAL[@]}" -ne 1 ]; then
  usage >&2
  exit 2
fi

CC_BIN="${CC:-gcc}"
CXX_BIN="${CXX:-g++}"
OBJDUMP_BIN="${OBJDUMP:-objdump}"
PYTHON_BIN="${PYTHON:-python3}"
COMMON_FLAGS=(
  -ffunction-sections -fdata-sections -fno-pie
  -Isrc/platform -Isrc/compatibility -Isrc/instrumentation
  -Isrc -c
)

manifest_path() {
  if [[ "$MANIFEST" = /* ]]; then
    printf '%s\n' "$MANIFEST"
  else
    printf '%s/%s\n' "$ROOT" "$MANIFEST"
  fi
}

split_sources() {
  "$PYTHON_BIN" - "$(manifest_path)" <<'PY'
import json
import pathlib
import sys

manifest_path = pathlib.Path(sys.argv[1])
payload = json.loads(manifest_path.read_text(encoding="utf-8"))
sources = {entry["source"] for entry in payload.get("functions", [])}
owner = payload.get("state_owner")
if owner:
    sources.add(owner)
expected = payload.get("source_file_count")
if expected is not None and len(sources) != expected:
    raise SystemExit(
        f"manifest names {len(sources)} source files, expected {expected}"
    )
for source in sorted(sources):
    print(source)
PY
}

normalize_object() {
  "$OBJDUMP_BIN" -dr --no-show-raw-insn "$1" \
    | sed -E \
        -e 's/^[[:space:]]*[0-9a-f]+:[[:space:]]*//' \
        -e 's/<([^+>]*)(\+0x[0-9a-f]+)?>/<\1>/g' \
    | awk '!/^$/ && !/file format/ && !/^Disassembly of section/'
}

capture() {
  local output="$1"
  local source
  local object
  local compiler
  local standard
  local label
  local language_flags=()
  local index=0
  local sources=()
  : > "$output"

  mapfile -t sources < <(split_sources)
  if [ "${#sources[@]}" -eq 0 ]; then
    echo "no recovered sources selected" >&2
    return 1
  fi

  for source in "${sources[@]}"; do
    if [ ! -f "$ROOT/$source" ]; then
      echo "manifest source does not exist: $source" >&2
      return 1
    fi
    object="$(printf '%s/%04d.o' "$OBJECT_DIR" "$index")"
    case "$source" in
      *.c) compiler="$CC_BIN"; standard=gnu17; language_flags=(-w) ;;
      *.cpp)
        compiler="$CXX_BIN"; standard=gnu++20
        language_flags=(-U_GNU_SOURCE -fno-exceptions -fno-rtti -Werror=write-strings)
        ;;
      *) echo "unsupported source language: $source" >&2; return 1 ;;
    esac
    (cd "$ROOT" && "$compiler" "-std=$standard" "${language_flags[@]}" "${COMMON_FLAGS[@]}" "$source" -o "$object")
    label="$source"
    if [ "$NORMALIZE_CPP_PATHS" -eq 1 ] && [[ "$label" == *.cpp ]]; then
      label="${label%.cpp}.c"
    fi
    printf 'translation-unit %s\n' "$label" >> "$output"
    normalize_object "$object" >> "$output"
    index=$((index + 1))
  done
}

OBJECT_DIR="$(mktemp -d)"
cleanup() {
  rm -rf "$OBJECT_DIR"
  if [ -n "${AFTER:-}" ]; then
    rm -f "$AFTER"
  fi
}
trap cleanup EXIT

if [ -n "$SNAPSHOT" ]; then
  capture "$SNAPSHOT"
  echo "split asm snapshot: $SNAPSHOT ($(wc -l < "$SNAPSHOT") normalized lines)"
  exit 0
fi

BASE="${POSITIONAL[0]}"
if [ ! -f "$BASE" ]; then
  echo "snapshot does not exist: $BASE" >&2
  exit 2
fi
AFTER="$(mktemp)"
capture "$AFTER"

if diff -q "$BASE" "$AFTER" >/dev/null; then
  printf '{"ok": true, "mode": "split", "normalized_lines": %s}\n' \
    "$(wc -l < "$AFTER")"
  exit 0
fi

echo "object disassembly differs (split mode):" >&2
diff -u "$BASE" "$AFTER" | head -80 || true
exit 1
