#!/usr/bin/env python3
"""Exercise the real route pan helper with controlled input, logs, and time.

No game, display server, or host input tool is launched. The helper, its route
command, and its input lifecycle are extracted from the canonical shell script.
"""

from __future__ import annotations

import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
DRIVER = ROOT / "tests/run_campaign_route_script_smoke.sh"


def shell_function(source: str, name: str) -> str:
    match = re.search(rf"^{re.escape(name)}\(\) \{{\n.*?^\}}$", source, re.M | re.S)
    if match is None:
        raise AssertionError(f"driver is missing {name}()")
    return match.group(0)


HARNESS = r'''
set -eu
log_path="$CASE_DIR/game.log"
world_input_script="$CASE_DIR/world-input.txt"
events="$CASE_DIR/events.log"
: >"$events"
: >"$world_input_script"
model_left="$INITIAL_LEFT"; model_top="$INITIAL_TOP"
cursor_x="$INITIAL_CURSOR"; cursor_y=239
held=''; step_pending=0; step_index=0; consumed=0; delayed=0
pid=12345; window=123; SECONDS=0
read -ra steps <<<"$STEPS"
printf '[world_input] command=move target=328,239 cursor=312,239\n' >"$log_path"
printf '[world_cursor] cursor=328,239 left=%s top=%s\n' "$STALE_LEFT" "$STALE_TOP" >>"$log_path"
snapshot() {
  printf 'left=%s top=%s held=%s steps=%s\n' "$model_left" "$model_top" "$held" "$step_index" >"$CASE_DIR/state.txt"
}
trap snapshot EXIT
fail_smoke() { printf 'FAIL %s\n' "$*" >>"$events"; exit 1; }
refresh_route_window() { if [ "$MODE" = no_window ]; then window=''; fi; }
log_route_input_step() {
  printf 'INPUT %s %s %s held=%s\n' "$1" "$2" "$3" "$held" >>"$events"
}
kill() { printf 'LIVENESS\n' >>"$events"; [ "$MODE" != process_death ]; }
xdotool() {
  printf 'HOST %s\n' "$*" >>"$events"
  case "$1" in
    keydown) held="${@: -1}"; step_pending=1 ;;
    keyup)
      if [ "$MODE" = keyup_failure ]; then return 1; fi
      held=''
      ;;
  esac
}
emit_cursor() {
  printf '[world_cursor] cursor=%s,239 left=%s top=%s\n' "$cursor_x" "$model_left" "${1:-$model_top}" >>"$log_path"
}
emit_ack() {
  printf '[world_input] command=move target=%s,239 cursor=312,239 delta=16,0\n' "$1" >>"$log_path"
}
sleep() {
  # Advance the shell's actual deadline variable without wall-clock sleeps.
  SECONDS=$((SECONDS + 1))
  printf 'SLEEP %s held=%s\n' "$1" "$held" >>"$events"
  if [ "$step_pending" = 1 ]; then
    magnitude="${steps[$step_index]:-1}"
    step_index=$((step_index + 1)); step_pending=0
    case "$held" in
      Left) model_left=$((model_left - magnitude)) ;;
      Right) model_left=$((model_left + magnitude)) ;;
      Up) model_top=$((model_top - magnitude)) ;;
      Down) model_top=$((model_top + magnitude)) ;;
    esac
    if [ "$model_left" -lt 0 ]; then model_left=0; fi
    if [ "$model_top" -lt 0 ]; then model_top=0; fi
    if [ "$model_left" -gt "$MAX_LEFT" ]; then model_left="$MAX_LEFT"; fi
    if [ "$model_top" -gt "$MAX_TOP" ]; then model_top="$MAX_TOP"; fi
  fi
  if [ "$delayed" = 1 ]; then
    emit_ack 328; emit_cursor; delayed=0
  fi
  mapfile -t commands <"$world_input_script"
  while [ "$consumed" -lt "${#commands[@]}" ]; do
    read -r operation next_x next_y <<<"${commands[$consumed]}"
    consumed=$((consumed + 1))
    if [ "$operation" != move ]; then fail_smoke "unexpected scripted $operation"; fi
    if [ -n "$held" ]; then fail_smoke "cursor probe submitted before keyup"; fi
    changed=0
    if [ "$cursor_x" != "$next_x" ] || [ "$cursor_y" != "$next_y" ]; then changed=1; fi
    cursor_x="$next_x"; cursor_y="$next_y"
    if [ "$next_x" = 312 ]; then
      emit_ack "$next_x"
      if [ "$changed" = 1 ]; then emit_cursor; fi
      continue
    fi
    case "$MODE" in
      missing_ack|process_death) emit_cursor ;;
      missing_cursor) emit_ack 328 ;;
      cursor_before_ack) emit_cursor; emit_ack 328 ;;
      wrong_ack) emit_ack 327; emit_cursor ;;
      route_only)
        emit_ack 328
        printf '[campaign-route] copied [world_cursor] left=%s top=%s\n' "$TARGET_LEFT" "$TARGET_TOP" >>"$log_path"
        ;;
      delayed)
        emit_cursor "$TARGET_TOP"
        printf '[campaign-route] copied [world_input] command=move target=328,239 \n' >>"$log_path"
        delayed=1
        ;;
      invalid_viewport) emit_ack 328; emit_cursor bogus ;;
      *) emit_ack 328; if [ "$changed" = 1 ]; then emit_cursor; fi ;;
    esac
  done
}
'''


@unittest.skipUnless(shutil.which("bash") and shutil.which("awk"), "requires Linux shell tools")
class RouteViewportTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.source = DRIVER.read_text()
        cls.functions = "\n".join(shell_function(cls.source, name) for name in
                                  ("is_unsigned_integer", "key_at", "write_world_script",
                                   "pan_world_viewport"))
        match = re.search(r"^      world_pan_viewport\)\n(.*?)^        ;;", cls.source, re.M | re.S)
        if match is None:
            raise AssertionError("driver is missing the world_pan_viewport route command")
        cls.caller = match.group(1)

    def run_case(self, *, initial=(63, 43), target=(63, 44), stale=None,
                 attempts=3, steps="1", mode="normal", cursor=328,
                 bounds=(100, 100), route_args=None, hold=None, gap=None):
        stale = stale or initial
        with tempfile.TemporaryDirectory(prefix="clash95-pan-test-") as directory:
            env = os.environ.copy()
            env.update({"CASE_DIR": directory, "INITIAL_LEFT": str(initial[0]),
                        "INITIAL_TOP": str(initial[1]), "STALE_LEFT": str(stale[0]),
                        "STALE_TOP": str(stale[1]), "INITIAL_CURSOR": str(cursor),
                        "TARGET_LEFT": str(target[0]), "TARGET_TOP": str(target[1]),
                        "ATTEMPTS": str(attempts), "STEPS": steps, "MODE": mode,
                        "MAX_LEFT": str(bounds[0]), "MAX_TOP": str(bounds[1])})
            for name, value in (("CLASH95_PAN_KEY_HOLD", hold), ("CLASH95_PAN_KEY_GAP", gap)):
                env.pop(name, None)
                if value is not None:
                    env[name] = value
            invocation = 'pan_world_viewport "$TARGET_LEFT" "$TARGET_TOP" "$ATTEMPTS" 8\n'
            if route_args is not None:
                env["ROUTE_ARGS"] = route_args
                invocation = 'args="$ROUTE_ARGS"; line_number=8\n' + self.caller
            result = subprocess.run(["bash", "-c", HARNESS + self.functions + "\n" + invocation],
                                    env=env, text=True, capture_output=True, timeout=5)
            files = {name: (Path(directory) / name).read_text()
                     for name in ("events.log", "game.log", "world-input.txt", "state.txt")}
        self.assertEqual(result.stderr, "", result.stderr)
        return result.returncode, files

    def assert_succeeded(self, result, *, position, attempts):
        code, files = result
        self.assertEqual(code, 0, files["events.log"])
        self.assertIn(f"left={position[0]} top={position[1]} held= steps={attempts}", files["state.txt"])
        self.assertIn(f"left={position[0]} top={position[1]} attempts={attempts}", files["game.log"])
        self.assertNotIn("key ", files["world-input.txt"])
        return files

    def assert_failed(self, result, message):
        code, files = result
        self.assertNotEqual(code, 0, files["game.log"])
        self.assertIn(message, files["events.log"])
        self.assertNotIn("world-pan-viewport-done", files["game.log"])
        return files

    def test_fresh_entry_rejects_old_target_and_old_matching_ack(self):
        self.assert_succeeded(self.run_case(initial=(63, 42), stale=(63, 44), steps="1 1"),
                              position=(63, 44), attempts=2)

    def test_initial_target_is_probed_without_pressing_a_key(self):
        files = self.assert_succeeded(self.run_case(initial=(63, 44)), position=(63, 44), attempts=0)
        self.assertEqual(files["world-input.txt"], "move 312 239\nmove 328 239\n")
        self.assertNotIn("HOST key", files["events.log"])

    def test_probe_changes_cursor_even_when_it_starts_at_either_probe_position(self):
        for cursor in (312, 328):
            with self.subTest(cursor=cursor):
                self.assert_succeeded(self.run_case(initial=(63, 44), cursor=cursor),
                                      position=(63, 44), attempts=0)

    def test_keyup_and_gap_precede_following_probe(self):
        files = self.assert_succeeded(self.run_case(hold="0.07", gap="0.09"), position=(63, 44), attempts=1)
        events = files["events.log"]
        down = events.index("HOST keydown --clearmodifiers Down")
        hold = events.index("SLEEP 0.07 held=Down", down)
        up = events.index("HOST keyup Down", hold)
        gap = events.index("SLEEP 0.09 held=\n", up)
        probe = events.index("INPUT world move", gap)
        self.assertLess(down, hold)
        self.assertLess(hold, up)
        self.assertLess(up, gap)
        self.assertLess(gap, probe)

    def test_success_on_final_allowed_key_is_accepted(self):
        self.assert_succeeded(self.run_case(attempts=1), position=(63, 44), attempts=1)

    def test_overshoot_reverses_direction_after_release(self):
        files = self.assert_succeeded(self.run_case(steps="2 1", attempts=2), position=(63, 44), attempts=2)
        self.assertIn("HOST keydown --clearmodifiers Down", files["events.log"])
        self.assertIn("HOST keydown --clearmodifiers Up", files["events.log"])

    def test_horizontal_then_vertical_motion_uses_all_four_host_keys(self):
        for initial in ((62, 43), (64, 45)):
            with self.subTest(initial=initial):
                files = self.assert_succeeded(self.run_case(initial=initial, steps="1 1"),
                                              position=(63, 44), attempts=2)
                horizontal, vertical = ("Right", "Down") if initial == (62, 43) else ("Left", "Up")
                self.assertLess(files["events.log"].index(f"HOST keyup {horizontal}"),
                                files["events.log"].index(f"HOST keydown --clearmodifiers {vertical}"))

    def test_unreachable_boundary_exhausts_with_fresh_final_position(self):
        files = self.assert_failed(self.run_case(initial=(63, 43), bounds=(100, 43), attempts=2),
                                   "exhausted 2 attempts at left=63 top=43")
        self.assertEqual(files["events.log"].count("HOST keyup Down"), 2)
        self.assertEqual(files["world-input.txt"].count("move 328 239"), 3)

    def test_delayed_ack_ignores_pre_ack_cursor_and_echoed_route_lines(self):
        self.assert_succeeded(self.run_case(mode="delayed"), position=(63, 44), attempts=1)

    def test_only_own_ack_followed_by_real_cursor_can_succeed(self):
        for mode in ("missing_ack", "missing_cursor", "cursor_before_ack", "wrong_ack", "route_only"):
            with self.subTest(mode=mode):
                files = self.assert_failed(self.run_case(initial=(63, 44), mode=mode),
                                           "timed out waiting for its acknowledged cursor probe")
                self.assertNotIn("HOST key", files["events.log"])
                self.assertLessEqual(files["events.log"].count("SLEEP"), 7)

    def test_invalid_fresh_viewport_fails_before_key_input(self):
        files = self.assert_failed(self.run_case(mode="invalid_viewport"), "parsed invalid viewport")
        self.assertNotIn("HOST key", files["events.log"])

    def test_process_death_fails_without_waiting_for_timeout(self):
        files = self.assert_failed(self.run_case(mode="process_death"), "process exited during world_pan_viewport")
        self.assertEqual(files["events.log"].count("SLEEP"), 2)

    def test_missing_window_cannot_report_pan_success(self):
        self.assert_failed(self.run_case(mode="no_window"), "no SDL window was acquired")

    def test_failed_keyup_cannot_submit_a_probe_or_report_success(self):
        code, files = self.run_case(mode="keyup_failure")
        self.assertNotEqual(code, 0)
        self.assertNotIn("world-pan-viewport-done", files["game.log"])
        self.assertEqual(files["world-input.txt"].count("move 328 239"), 1)

    def test_route_command_forwards_arguments_and_final_attempt(self):
        self.assert_succeeded(self.run_case(route_args="63 44 1"), position=(63, 44), attempts=1)

    def test_route_command_preserves_default_attempt_limit(self):
        files = self.assert_failed(self.run_case(route_args="63 44", bounds=(100, 43)), "exhausted 160 attempts")
        self.assertEqual(files["events.log"].count("HOST keyup Down"), 160)

    def test_route_command_rejects_missing_or_invalid_arguments(self):
        for args in ("", "63", "-1 44", "63 bad", "63 44 0", "63 44 -2"):
            with self.subTest(args=args):
                files = self.assert_failed(self.run_case(route_args=args), "requires")
                self.assertEqual(files["world-input.txt"], "")


if __name__ == "__main__":
    unittest.main()
