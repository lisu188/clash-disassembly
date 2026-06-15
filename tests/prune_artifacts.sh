#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
artifact_root="${CLASH95_ARTIFACT_PRUNE_ROOT:-$repo_root/artifacts}"
keep_runs="${CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP:-12}"
min_runs_for_size_cap="${CLASH95_ARTIFACT_PRUNE_MIN_RUNS_PER_GROUP:-1}"
max_bytes="${CLASH95_ARTIFACT_PRUNE_MAX_BYTES:-0}"
apply=0
quiet=0
deleted_count=0
deleted_bytes=0
declare -A planned_candidates=()

usage() {
  cat <<USAGE
usage: $0 [--dry-run] [--apply] [--quiet] [--keep N] [--min-keep N] [--max-bytes N]

Prunes durable probe run directories under repo-owned artifacts roots.

Defaults are conservative:
  --dry-run          print what would be removed
  --keep 12         keep newest 12 runs per known mission artifact group
  --min-keep 1      keep at least one newest run per group when enforcing --max-bytes
  --max-bytes 0     disable whole-artifacts size-cap pruning

Environment knobs:
  CLASH95_ARTIFACT_PRUNE_KEEP_RUNS_PER_GROUP
  CLASH95_ARTIFACT_PRUNE_MIN_RUNS_PER_GROUP
  CLASH95_ARTIFACT_PRUNE_MAX_BYTES
  CLASH95_ARTIFACT_PRUNE_GROUP_ROOTS       colon-separated override
  CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS colon-separated additions
USAGE
}

is_unsigned_integer() {
  case "${1:-}" in
    ""|*[!0-9]*) return 1 ;;
    *) return 0 ;;
  esac
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    --dry-run)
      apply=0
      ;;
    --apply)
      apply=1
      ;;
    --quiet)
      quiet=1
      ;;
    --keep)
      shift
      keep_runs="${1:-}"
      ;;
    --min-keep)
      shift
      min_runs_for_size_cap="${1:-}"
      ;;
    --max-bytes)
      shift
      max_bytes="${1:-}"
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown artifact prune argument: $1" >&2
      usage >&2
      exit 2
      ;;
  esac
  shift
done

if ! is_unsigned_integer "$keep_runs"; then
  echo "artifact prune --keep must be an unsigned integer, got: $keep_runs" >&2
  exit 2
fi
if ! is_unsigned_integer "$min_runs_for_size_cap"; then
  echo "artifact prune --min-keep must be an unsigned integer, got: $min_runs_for_size_cap" >&2
  exit 2
fi
if ! is_unsigned_integer "$max_bytes"; then
  echo "artifact prune --max-bytes must be an unsigned integer, got: $max_bytes" >&2
  exit 2
fi

mkdir -p "$artifact_root"
artifacts_real="$(cd "$artifact_root" && pwd -P)"

path_size_bytes() {
  du -sb "$1" 2>/dev/null | awk '{ print $1 + 0 }'
}

artifact_total_bytes() {
  path_size_bytes "$artifacts_real"
}

print_status() {
  if [ "$quiet" != "1" ]; then
    printf '%s\n' "$*"
  fi
}

validate_candidate_dir() {
  local candidate="$1"
  local candidate_real

  if [ ! -d "$candidate" ]; then
    return 1
  fi
  candidate_real="$(cd "$candidate" && pwd -P 2>/dev/null)" || return 1
  case "$candidate_real" in
    "$artifacts_real"/*)
      printf '%s' "$candidate_real"
      return 0
      ;;
    *)
      echo "artifact prune skipped path outside artifacts: $candidate_real" >&2
      return 1
      ;;
  esac
}

prune_candidate() {
  local reason="$1"
  local candidate="$2"
  local candidate_real
  local bytes

  candidate_real="$(validate_candidate_dir "$candidate")" || return 0
  if [ -n "${planned_candidates[$candidate_real]+x}" ]; then
    return 0
  fi
  planned_candidates[$candidate_real]=1
  bytes="$(path_size_bytes "$candidate_real")"
  if [ "$apply" = "1" ]; then
    rm -rf -- "$candidate_real"
    print_status "pruned reason=$reason bytes=$bytes path=$candidate_real"
  else
    print_status "would_prune reason=$reason bytes=$bytes path=$candidate_real"
  fi
  deleted_count=$((deleted_count + 1))
  deleted_bytes=$((deleted_bytes + bytes))
}

add_group_root() {
  local root="$1"
  local root_real

  if [ ! -d "$root" ]; then
    return 0
  fi
  root_real="$(cd "$root" && pwd -P 2>/dev/null)" || return 0
  case "$root_real" in
    "$artifacts_real"/*)
      group_roots+=( "$root_real" )
      ;;
    *)
      echo "artifact prune skipped group root outside artifacts: $root_real" >&2
      ;;
  esac
}

add_colon_separated_group_roots() {
  local value="$1"
  local old_ifs="$IFS"
  local root

  IFS=':'
  for root in $value; do
    if [ -n "$root" ]; then
      case "$root" in
        /*) add_group_root "$root" ;;
        *) add_group_root "$repo_root/$root" ;;
      esac
    fi
  done
  IFS="$old_ifs"
}

group_roots=()
if [ -n "${CLASH95_ARTIFACT_PRUNE_GROUP_ROOTS:-}" ]; then
  add_colon_separated_group_roots "$CLASH95_ARTIFACT_PRUNE_GROUP_ROOTS"
else
  for root in "$artifacts_real"/campaign-routes/mission-* "$artifacts_real"/first-campaign/mission-* "$artifacts_real"/soak/*; do
    add_group_root "$root"
  done
fi
if [ -n "${CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS:-}" ]; then
  add_colon_separated_group_roots "$CLASH95_ARTIFACT_PRUNE_EXTRA_GROUP_ROOTS"
fi

before_bytes="$(artifact_total_bytes)"
print_status "artifact_root=$artifacts_real"
print_status "mode=$([ "$apply" = "1" ] && echo apply || echo dry-run)"
print_status "before_bytes=$before_bytes"
print_status "group_root_count=${#group_roots[@]}"

if [ "$keep_runs" != "0" ]; then
  for root in "${group_roots[@]}"; do
    while IFS= read -r candidate; do
      prune_candidate "per-group-count" "$candidate"
    done < <(
      find "$root" -mindepth 1 -maxdepth 1 -type d -printf '%T@ %p\n' 2>/dev/null \
        | sort -rn \
        | awk -v keep="$keep_runs" 'NR > keep { first = index($0, " "); if (first > 0) print substr($0, first + 1) }'
    )
  done
fi

if [ "$max_bytes" != "0" ]; then
  current_bytes="$(artifact_total_bytes)"
  if [ "$apply" != "1" ]; then
    current_bytes=$((before_bytes - deleted_bytes))
  fi
  if [ "$current_bytes" -gt "$max_bytes" ]; then
    while IFS= read -r line; do
      if [ "$current_bytes" -le "$max_bytes" ]; then
        break
      fi
      candidate="${line#* }"
      candidate_real="$(validate_candidate_dir "$candidate")" || continue
      if [ -n "${planned_candidates[$candidate_real]+x}" ]; then
        continue
      fi
      bytes="$(path_size_bytes "$candidate_real")"
      prune_candidate "global-size-cap" "$candidate"
      if [ "$apply" = "1" ]; then
        current_bytes="$(artifact_total_bytes)"
      else
        current_bytes=$((current_bytes - bytes))
      fi
    done < <(
      for root in "${group_roots[@]}"; do
        find "$root" -mindepth 1 -maxdepth 1 -type d -printf '%T@ %p\n' 2>/dev/null \
          | sort -rn \
          | awk -v min_keep="$min_runs_for_size_cap" 'NR > min_keep { print }'
      done | sort -n
    )
  fi
fi

after_bytes="$(artifact_total_bytes)"
if [ "$apply" != "1" ]; then
  after_bytes=$((before_bytes - deleted_bytes))
  if [ "$after_bytes" -lt 0 ]; then
    after_bytes=0
  fi
fi

print_status "prune_candidate_count=$deleted_count"
print_status "prune_candidate_bytes=$deleted_bytes"
print_status "after_bytes=$after_bytes"
