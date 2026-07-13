#!/usr/bin/env python3
import argparse
import json
import re
from pathlib import Path

from crossbuild_match import parse_ida_c_text, normalize_ea

MARKER_RE = re.compile(r"(?m)^//----- \(([0-9A-Fa-f]{8})\) -+")
ERROR_RE = re.compile(r"(?m)^#error\s+(.+)$")
SUB_RE = re.compile(r"^sub_[0-9A-Fa-f]+$")


def load_json(path, default):
    if not path:
        return default
    file_path = Path(path)
    if not file_path.exists():
        return default
    return json.loads(file_path.read_text(encoding="utf-8"))


def load_map(path):
    data = load_json(path, [])
    rows = data.get("rows", data) if isinstance(data, dict) else data
    return {normalize_ea(row["ea"]): row for row in rows}


def marker_addresses(text):
    return [int(value, 16) for value in MARKER_RE.findall(text)]


def failed_function_addresses(text):
    markers = list(MARKER_RE.finditer(text))
    failures = []
    summary_errors = []
    for error in ERROR_RE.finditer(text):
        message = error.group(1).strip()
        if "there were" in message.lower() or "failures during decompilation" in message.lower():
            summary_errors.append(message)
            continue
        previous = [marker for marker in markers if marker.start() < error.start()]
        if previous:
            failures.append(int(previous[-1].group(1), 16))
        else:
            summary_errors.append(message)
    return sorted(set(failures)), summary_errors


def collision_mapping(seed_report):
    result = {}
    for row in seed_report.get("collisions", []):
        result[normalize_ea(row["ea"])] = row["used"]
    return result


def expected_emitted_name(ea, requested, collisions):
    return collisions.get(ea, requested)


def verify(args):
    baseline_text = Path(args.baseline).read_text(encoding="latin-1", errors="replace")
    generated_text = Path(args.generated).read_text(encoding="latin-1", errors="replace")
    baseline_markers = marker_addresses(baseline_text)
    generated_markers = marker_addresses(generated_text)
    baseline_functions = parse_ida_c_text(baseline_text)
    generated_functions = parse_ida_c_text(generated_text)
    master = load_map(args.master_map)
    confirmed = load_json(args.confirmed_transfers, {"rows": []})
    confirmed_rows = confirmed.get("rows", confirmed) if isinstance(confirmed, dict) else confirmed
    seed_report = load_json(args.seed_report, {})
    collisions = collision_mapping(seed_report)
    failed, summary_errors = failed_function_addresses(generated_text)

    checks = {}
    checks["marker_count"] = {
        "ok": len(generated_markers) == args.expected_markers,
        "expected": args.expected_markers,
        "actual": len(generated_markers),
    }
    checks["marker_addresses_identical"] = {
        "ok": baseline_markers == generated_markers,
        "missing": [hex(value) for value in sorted(set(baseline_markers) - set(generated_markers))],
        "added": [hex(value) for value in sorted(set(generated_markers) - set(baseline_markers))],
    }
    checks["failed_functions"] = {
        "ok": failed == [args.allowed_failed_function],
        "expected": [hex(args.allowed_failed_function)],
        "actual": [hex(value) for value in failed],
        "summary_errors": summary_errors,
    }

    roundtrip_failures = []
    for ea, row in sorted(master.items()):
        generated = generated_functions.get(ea)
        requested = row["name"]
        expected = expected_emitted_name(ea, requested, collisions)
        if generated is None or generated["name"] != expected:
            roundtrip_failures.append({
                "ea": hex(ea),
                "requested": requested,
                "expected_emitted": expected,
                "actual": generated["name"] if generated else None,
            })
    checks["master_map_roundtrip"] = {
        "ok": not roundtrip_failures,
        "failures": roundtrip_failures,
    }

    lost_prior_names = []
    for ea, baseline in sorted(baseline_functions.items()):
        if SUB_RE.fullmatch(baseline["name"]):
            continue
        generated = generated_functions.get(ea)
        if generated is None or SUB_RE.fullmatch(generated["name"]):
            lost_prior_names.append({
                "ea": hex(ea),
                "before": baseline["name"],
                "after": generated["name"] if generated else None,
            })
    checks["prior_names_preserved"] = {
        "ok": not lost_prior_names,
        "lost": lost_prior_names,
    }

    named_functions = [row for row in generated_functions.values() if not SUB_RE.fullmatch(row["name"])]
    expected_named = args.baseline_named + len(confirmed_rows)
    checks["named_function_count"] = {
        "ok": len(named_functions) == expected_named,
        "expected": expected_named,
        "actual": len(named_functions),
        "baseline": args.baseline_named,
        "confirmed_transfers": len(confirmed_rows),
    }
    checks["collision_count"] = {
        "ok": len(collisions) == args.baseline_collisions,
        "expected": args.baseline_collisions,
        "actual": len(collisions),
    }
    transfer_eas = {normalize_ea(row["ea"]) for row in confirmed_rows}
    transfer_collisions = sorted(transfer_eas & set(collisions))
    checks["no_new_transfer_collisions"] = {
        "ok": not transfer_collisions,
        "addresses": [hex(value) for value in transfer_collisions],
    }

    ok = all(check["ok"] for check in checks.values())
    return {
        "schema": 1,
        "ok": ok,
        "checks": checks,
        "baseline_named": args.baseline_named,
        "baseline_distinct_base_names": args.baseline_distinct_base_names,
        "baseline_collisions": args.baseline_collisions,
    }


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("baseline")
    parser.add_argument("generated")
    parser.add_argument("master_map")
    parser.add_argument("seed_report")
    parser.add_argument("output_report")
    parser.add_argument("--confirmed-transfers")
    parser.add_argument("--expected-markers", type=int, default=4219)
    parser.add_argument("--allowed-failed-function", type=lambda value: int(value, 0), default=0xFDF26)
    parser.add_argument("--baseline-named", type=int, default=886)
    parser.add_argument("--baseline-distinct-base-names", type=int, default=872)
    parser.add_argument("--baseline-collisions", type=int, default=14)
    args = parser.parse_args(argv)
    report = verify(args)
    Path(args.output_report).write_text(json.dumps(report, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps({"ok": report["ok"], "checks": {key: value["ok"] for key, value in report["checks"].items()}}, sort_keys=True))
    return 0 if report["ok"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
