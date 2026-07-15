#!/usr/bin/env bash
# Compare recovered preprocessed token streams (tools/pp_token_diff.py).
#
# It preprocesses, in manifest order, each independently compiled GNU C17
# source named by data/recovered_sources.json.
#
# Usage:
#   bash tools/pp_token_gate.sh [--split] [BASE_REF] [--allow plan.json]
#   bash tools/pp_token_gate.sh --snapshot out.i
#   bash tools/pp_token_gate.sh out.i [--allow plan.json]
#   bash tools/pp_token_gate.sh --manifest path/to/manifest.json ...
#
# A snapshot is the concurrency-safe workflow. Historical positional
# snapshot/ref arguments remain accepted. --split remains a compatibility no-op.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
MANIFEST="data/recovered_sources.json"
SNAPSHOT=""
BASE_REF=""
DIFF_ARGS=()
PYTHON_BIN="${PYTHON:-python3}"
CC_BIN="${CC:-gcc}"

usage() {
  sed -n '2,14p' "$0" | sed 's/^# \{0,1\}//'
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --split)
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
    --allow)
      [ "$#" -ge 2 ] || { echo "--allow requires a plan path" >&2; exit 2; }
      DIFF_ARGS+=("--allow" "$2")
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
      if [ -n "$BASE_REF" ]; then
        echo "only one snapshot or git ref may be supplied" >&2
        exit 2
      fi
      BASE_REF="$1"
      shift
      ;;
  esac
done

if [ -n "$SNAPSHOT" ] && [ -n "$BASE_REF" ]; then
  echo "--snapshot does not accept a comparison snapshot/ref" >&2
  exit 2
fi

manifest_path() {
  local tree="$1"
  if [[ "$MANIFEST" = /* ]]; then
    printf '%s\n' "$MANIFEST"
  else
    printf '%s/%s\n' "$tree" "$MANIFEST"
  fi
}

split_sources() {
  local tree="$1"
  "$PYTHON_BIN" - "$(manifest_path "$tree")" <<'PY'
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

preprocess() {
  local tree="$1"
  local source
  local index=0
  local sources=()
  local flags=(
    -Isrc/platform -Isrc/compatibility -Isrc/instrumentation
    -Isrc/recovered/split -E -P
  )

  mapfile -t sources < <(split_sources "$tree")
  if [ "${#sources[@]}" -eq 0 ]; then
    echo "no recovered sources selected" >&2
    return 1
  fi
  # Feed one manifest-generated include stream to the preprocessor.  The split
  # internal header is consequently expanded once instead of 138 times, while
  # every recovered source body and translation-unit boundary remains present
  # in the compared token stream.  Nothing generated here is compiled or
  # written into the production source tree.
  {
    for source in "${sources[@]}"; do
      if [ ! -f "$tree/$source" ]; then
        echo "manifest source does not exist: $source" >&2
        return 1
      fi
      printf 'CLASH95_PP_TRANSLATION_UNIT_BOUNDARY_%04d "%s";\n' "$index" "$source"
      printf '#include "%s"\n' "$source"
      index=$((index + 1))
    done
  } | (cd "$tree" && "$CC_BIN" -std=gnu17 "${flags[@]}" -x c -)
}

if [ -n "$SNAPSHOT" ]; then
  preprocess "$ROOT" > "$SNAPSHOT"
  echo "split snapshot: $SNAPSHOT ($(wc -l < "$SNAPSHOT") lines)"
  exit 0
fi

BASE_REF="${BASE_REF:-HEAD}"
OUT="$(mktemp -d)"
TMP=""
cleanup() {
  if [ -n "$TMP" ]; then
    git -C "$ROOT" worktree remove --force "$TMP" >/dev/null 2>&1 || true
  fi
  rm -rf "$OUT"
}
trap cleanup EXIT

preprocess "$ROOT" > "$OUT/after.i"
if [ -f "$BASE_REF" ]; then
  cp "$BASE_REF" "$OUT/before.i"
else
  TMP="$(mktemp -d)"
  rmdir "$TMP"
  git -C "$ROOT" worktree add --detach --quiet "$TMP" "$BASE_REF"
  preprocess "$TMP" > "$OUT/before.i"
fi

"$PYTHON_BIN" "$ROOT/tools/pp_token_diff.py" \
  "$OUT/before.i" "$OUT/after.i" "${DIFF_ARGS[@]}"
