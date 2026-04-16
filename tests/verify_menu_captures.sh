#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 1 ]; then
  echo "usage: $0 /path/to/clash95_bootstrap" >&2
  exit 2
fi

bootstrap_bin="$1"
if [ ! -x "$bootstrap_bin" ]; then
  echo "bootstrap binary is not executable: $bootstrap_bin" >&2
  exit 2
fi

capture_root="${TMPDIR:-/tmp}/clash95-menu-capture-test-$$"
mkdir -p "$capture_root"
trap 'rm -rf "$capture_root"' EXIT

run_capture()
{
  local name="$1"
  local capture_phase="$2"
  shift
  shift
  local log_path="$capture_root/$name.log"
  local status

  set +e
  env \
    SDL_VIDEODRIVER=dummy \
    SDL_AUDIODRIVER=dummy \
    CLASH95_TRACE_MENU_PROBE=1 \
    CLASH95_SCREENSHOT_PREFIX="$capture_root/$name" \
    CLASH95_MENU_PROBE_EXIT_AFTER_CAPTURE="$capture_phase" \
    "$@" \
    timeout 3s "$bootstrap_bin" >"$log_path" 2>&1
  status=$?
  set -e

  if [ "$status" -ne 0 ]; then
    echo "$name capture exited with unexpected status $status" >&2
    cat "$log_path" >&2
    exit 1
  fi
  if grep -q "dumped core" "$log_path"; then
    echo "$name capture reported a core dump" >&2
    cat "$log_path" >&2
    exit 1
  fi
}

run_capture main-menu main-menu
grep -q "present-menu" "$capture_root/main-menu.log"
grep -q "main-menu-capture-exit" "$capture_root/main-menu.log"

run_capture load-menu load-menu \
  CLASH95_MENU_PROBE_AUTO_CLICK=load \
  CLASH95_LOAD_MENU_PROBE_AUTO_SLOT=0
grep -q "load-menu-row-draws-complete" "$capture_root/load-menu.log"
grep -q "load-auto-hover-selected" "$capture_root/load-menu.log"

python3 - "$capture_root/main-menu" "$capture_root/load-menu" <<'PY'
import glob
import os
import struct
import sys


def fail(message):
    print(message, file=sys.stderr)
    raise SystemExit(1)


def validate_prefix(prefix):
    paths = sorted(glob.glob(prefix + "-*.bmp"))
    if not paths:
        fail(f"no BMP screenshots generated for {prefix}")
    usable = []
    for path in paths:
        with open(path, "rb") as handle:
            data = handle.read()
        if len(data) < 54 or data[:2] != b"BM":
            continue
        pixel_offset = struct.unpack_from("<I", data, 10)[0]
        header_size = struct.unpack_from("<I", data, 14)[0]
        if header_size < 40 or len(data) <= pixel_offset:
            continue
        width = struct.unpack_from("<i", data, 18)[0]
        height = struct.unpack_from("<i", data, 22)[0]
        bits_per_pixel = struct.unpack_from("<H", data, 28)[0]
        if width <= 0 or height == 0 or bits_per_pixel not in (8, 16, 24, 32):
            continue
        pixels = data[pixel_offset:]
        if len(pixels) < max(64, abs(height) * 4):
            continue
        if len(set(pixels)) < 2:
            continue
        if not any(byte != 0 for byte in pixels):
            continue
        usable.append(path)
    if not usable:
        listed = ", ".join(os.path.basename(path) for path in paths)
        fail(f"BMP screenshots for {prefix} were blank or malformed: {listed}")
    return usable


main_paths = validate_prefix(sys.argv[1])
load_paths = validate_prefix(sys.argv[2])
print(f"validated {len(main_paths)} main-menu BMP(s) and {len(load_paths)} load-menu BMP(s)")
PY
