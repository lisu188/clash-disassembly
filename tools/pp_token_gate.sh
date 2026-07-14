#!/usr/bin/env bash
# Gate G1/G2 for the magic-number campaign: preprocess clash95.c at a base
# state and in the working tree, then require identical token streams
# (tools/pp_token_diff.py). Run from the repo root inside WSL/Linux.
#
# Usage:
#   bash tools/pp_token_gate.sh [BASE_REF] [--allow plan.json]
#   bash tools/pp_token_gate.sh --snapshot out.i     # capture pre-apply state
#   bash tools/pp_token_gate.sh out.i [--allow ...]  # compare vs a snapshot
#
# The snapshot form is the concurrency-safe workflow: snapshot immediately
# before applying a substitution batch, apply, then gate against the
# snapshot file -- unrelated commits landing on main meanwhile cannot
# pollute the comparison.
set -euo pipefail

PP() { gcc -std=gnu89 -I. -Icompat -E -P clash95.c; }

if [ "${1:-}" = "--snapshot" ]; then
  PP > "$2"
  echo "snapshot: $2 ($(wc -l < "$2") lines)"
  exit 0
fi

BASE_REF="${1:-HEAD}"
if [ "$#" -gt 0 ]; then shift; fi

OUT="$(mktemp -d)"
TMP=""
cleanup() {
  if [ -n "$TMP" ]; then git worktree remove --force "$TMP" >/dev/null 2>&1 || true; fi
  rm -rf "$OUT" ${TMP:+"$TMP"}
}
trap cleanup EXIT

PP > "$OUT/after.i"
if [ -f "$BASE_REF" ]; then
  cp "$BASE_REF" "$OUT/before.i"
else
  TMP="$(mktemp -d)"
  git worktree add --detach --quiet "$TMP" "$BASE_REF"
  (cd "$TMP" && gcc -std=gnu89 -I. -Icompat -E -P clash95.c) > "$OUT/before.i"
fi

python3 tools/pp_token_diff.py "$OUT/before.i" "$OUT/after.i" "$@"
