#!/usr/bin/env python3
import argparse
import json
import sys
from pathlib import Path


def normalize_ea(value):
    return value if isinstance(value, int) else int(str(value), 0)


def normalize_name(name):
    if name.startswith("Env") and len(name) > 3 and name[3].isupper():
        return name[3:]
    return name


def load_json(path, default):
    file_path = Path(path)
    if not file_path.exists():
        return default
    return json.loads(file_path.read_text(encoding="utf-8"))


def rows_by_ea(data):
    if isinstance(data, dict) and "rows" in data:
        data = data["rows"]
    if isinstance(data, dict):
        result = {}
        for key, value in data.items():
            if isinstance(value, str):
                row = {"name": value}
            else:
                row = dict(value)
            row.setdefault("ea", key)
            result[normalize_ea(row["ea"])] = row
        return result
    return {normalize_ea(row["ea"]): dict(row) for row in data}


def canonical_rows(master):
    return [
        {
            "ea": hex(ea),
            "name": row["name"],
            "confidence": row.get("confidence", "high"),
            "source": row["source"],
            "evidence": row.get("evidence", ""),
        }
        for ea, row in sorted(master.items())
    ]


def json_text(data):
    return json.dumps(data, indent=1, ensure_ascii=False) + "\n"


def merge_sources(existing, registered, anchors, string_matches, alignments, transfers):
    master = {}
    conflicts = []
    dropped_false = []

    for ea, row in sorted(existing.items()):
        master[ea] = {
            "name": row["name"],
            "confidence": row.get("confidence", "high"),
            "source": row.get("source", "existing"),
            "evidence": row.get("evidence", "in original clash.c"),
        }

    for ea, row in sorted(registered.items()):
        registered_name = row["name"]
        current = master.get(ea)
        if current is None:
            master[ea] = {
                "name": registered_name,
                "confidence": "high",
                "source": "clips-registered",
                "evidence": row.get("evidence", "registered CLIPS function ground truth"),
            }
        elif normalize_name(current["name"]) != normalize_name(registered_name):
            conflicts.append({
                "ea": hex(ea),
                "kind": "registered-vs-existing",
                "registered": registered_name,
                "existing": current["name"],
                "resolution": "registered-ground-truth",
            })
            master[ea] = {
                "name": registered_name,
                "confidence": "high",
                "source": "clips-registered",
                "evidence": row.get("evidence", "registered CLIPS function ground truth"),
            }

    def merge_direct(source_rows, source_name, evidence_builder):
        for ea, row in sorted(source_rows.items()):
            name = normalize_name(row["name"])
            registered_row = registered.get(ea)
            if registered_row and normalize_name(registered_row["name"]) != name:
                dropped_false.append({
                    "ea": hex(ea),
                    "registered": registered_row["name"],
                    "dropped_anchor": row["name"],
                    "kind": source_name,
                })
                continue
            current = master.get(ea)
            if current and normalize_name(current["name"]) != name:
                conflicts.append({
                    "ea": hex(ea),
                    "kind": f"{source_name}-vs-{current['source']}",
                    "current": current["name"],
                    "incoming": row["name"],
                    "resolution": source_name,
                })
            master[ea] = {
                "name": name,
                "confidence": "high",
                "source": source_name,
                "evidence": evidence_builder(row),
            }

    merge_direct(
        anchors,
        "clips-errid",
        lambda row: row.get("evidence", "direct CLIPS error-id evidence"),
    )
    merge_direct(
        string_matches,
        "clips-string",
        lambda row: "unique shared literal: " + row.get("evidence", "")[:60],
    )

    def fill_unnamed(source_rows, expected_source):
        used_names = {}
        for ea, row in master.items():
            used_names.setdefault(normalize_name(row["name"]), set()).add(ea)
        for ea, row in sorted(source_rows.items()):
            if ea in master:
                existing_row = master[ea]
                if normalize_name(existing_row["name"]) != normalize_name(row["name"]):
                    conflicts.append({
                        "ea": hex(ea),
                        "kind": f"{expected_source}-cannot-overwrite",
                        "current": existing_row["name"],
                        "incoming": row["name"],
                        "resolution": existing_row["source"],
                    })
                continue
            name = normalize_name(row["name"])
            if expected_source == "clash95-transfer" and name in used_names:
                conflicts.append({
                    "ea": hex(ea),
                    "kind": "clash95-transfer-name-collision",
                    "incoming": name,
                    "existing_addresses": [hex(value) for value in sorted(used_names[name])],
                    "resolution": "rejected",
                })
                continue
            master[ea] = {
                "name": name,
                "confidence": row.get("confidence", "medium"),
                "source": expected_source,
                "evidence": row.get("evidence", ""),
            }
            used_names.setdefault(name, set()).add(ea)

    fill_unnamed(alignments, "clips-align")
    fill_unnamed(transfers, "clash95-transfer")
    return master, conflicts, dropped_false


def compare_or_write(path, data, check):
    expected = json_text(data)
    file_path = Path(path)
    if check:
        if not file_path.exists():
            print(f"missing generated file: {file_path}", file=sys.stderr)
            return False
        try:
            actual = json.loads(file_path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError):
            print(f"invalid generated file: {file_path}", file=sys.stderr)
            return False
        if actual != data:
            print(f"stale generated file: {file_path}", file=sys.stderr)
            return False
        return True
    file_path.write_text(expected, encoding="utf-8")
    return True


def main(argv=None):
    script_dir = Path(__file__).resolve().parent
    repo = script_dir.parents[1]
    parser = argparse.ArgumentParser()
    parser.add_argument("--existing", default=repo / "tools/dos/dos_existing_names.json")
    parser.add_argument("--registered", default=script_dir / "dos_registered_groundtruth.json")
    parser.add_argument("--anchors", default=repo / "tools/dos/dos_clips_anchors.json")
    parser.add_argument("--strings", default=script_dir / "clips_string_matches.json")
    parser.add_argument("--alignments", default=script_dir / "clips_align_confirmed.json")
    parser.add_argument("--transfers", default=script_dir / "dos_crossbuild_confirmed.json")
    parser.add_argument("--output", default=script_dir / "dos_master_map.json")
    parser.add_argument("--conflicts", default=script_dir / "dos_name_conflicts.json")
    parser.add_argument("--dropped", default=script_dir / "dos_dropped_false_anchors.json")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args(argv)

    existing = rows_by_ea(load_json(args.existing, []))
    registered = rows_by_ea(load_json(args.registered, {}))
    anchors = rows_by_ea(load_json(args.anchors, []))
    string_matches = rows_by_ea(load_json(args.strings, {}))
    alignments = rows_by_ea(load_json(args.alignments, {}))
    transfers_data = load_json(args.transfers, {"rows": []})
    transfers = rows_by_ea(transfers_data)

    master, conflicts, dropped = merge_sources(
        existing,
        registered,
        anchors,
        string_matches,
        alignments,
        transfers,
    )
    rows = canonical_rows(master)
    ok = True
    ok &= compare_or_write(args.output, rows, args.check)
    ok &= compare_or_write(args.conflicts, conflicts, args.check)
    ok &= compare_or_write(args.dropped, dropped, args.check)

    clips_named = sum(1 for ea in master if 0x89860 <= ea < 0xEB580)
    by_source = {}
    for row in master.values():
        by_source[row["source"]] = by_source.get(row["source"], 0) + 1
    print(json.dumps({
        "total": len(master),
        "distinct_base_names": len({normalize_name(row["name"]) for row in master.values()}),
        "clips_named": clips_named,
        "by_source": dict(sorted(by_source.items())),
        "conflicts": len(conflicts),
        "dropped_false": len(dropped),
        "check": args.check,
        "ok": bool(ok),
    }, sort_keys=True))
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
