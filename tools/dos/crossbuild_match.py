#!/usr/bin/env python3
import argparse
import ast
import json
import re
from collections import defaultdict
from pathlib import Path

MARKER_RE = re.compile(r"^//----- \(([0-9A-Fa-f]{8})\) -+", re.MULTILINE)
STRING_DECL_RE = re.compile(
    r"(?m)^(?:const\s+)?char\s+([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*=\s*"
    r'("(?:\\.|[^"\\])*")\s*;'
)
INLINE_STRING_RE = re.compile(r'("(?:\\.|[^"\\])*")')
IDENT_RE = re.compile(r"\b[A-Za-z_]\w*\b")
SUB_RE = re.compile(r"^sub_([0-9A-Fa-f]+)$")


def decode_c_string(token):
    try:
        value = ast.literal_eval(token)
    except (SyntaxError, ValueError):
        return None
    return value if isinstance(value, str) else None


def normalize_ea(value):
    if isinstance(value, int):
        return value
    return int(str(value), 0)


def ea_text(value):
    return f"0x{normalize_ea(value):x}"


def normalize_name(name):
    if name.startswith("Env") and len(name) > 3 and name[3].isupper():
        return name[3:]
    return name


def extract_function_name(signature):
    signature = re.sub(r"@<[^>]*>", " ", signature)
    signature = re.sub(r"__\w+", " ", signature)
    signature = re.sub(r"\s+", " ", signature)
    candidates = re.findall(r"([A-Za-z_]\w*)\s*\(", signature)
    return candidates[-1] if candidates else None


def parse_ida_c_text(text):
    symbols = {}
    for match in STRING_DECL_RE.finditer(text):
        value = decode_c_string(match.group(2))
        if value is not None:
            symbols[match.group(1)] = value

    markers = list(MARKER_RE.finditer(text))
    functions = {}
    for index, marker in enumerate(markers):
        ea = int(marker.group(1), 16)
        start = marker.end()
        end = markers[index + 1].start() if index + 1 < len(markers) else len(text)
        chunk = text[start:end]
        brace = chunk.find("{")
        signature = chunk[:brace if brace >= 0 else min(len(chunk), 4096)]
        name = extract_function_name(signature)
        identifiers = set(IDENT_RE.findall(chunk))
        literals = {symbols[symbol] for symbol in identifiers if symbol in symbols}
        for token in INLINE_STRING_RE.findall(chunk):
            value = decode_c_string(token)
            if value is not None:
                literals.add(value)
        functions[ea] = {
            "ea": ea,
            "name": name or f"sub_{ea:X}",
            "literals": sorted(literals),
            "body": chunk,
        }
    return functions


def parse_ida_c(path):
    return parse_ida_c_text(Path(path).read_text(encoding="latin-1", errors="replace"))


def load_feature_export(path):
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    rows = data.get("functions", data)
    if isinstance(rows, dict):
        iterator = []
        for key, value in rows.items():
            row = dict(value)
            row.setdefault("ea", key)
            iterator.append(row)
    else:
        iterator = rows
    result = {}
    for raw in iterator:
        row = dict(raw)
        ea = normalize_ea(row["ea"])
        row["ea"] = ea
        row["bb"] = int(row.get("bb", 0))
        row["size"] = int(row.get("size", 0))
        row["name"] = row.get("name") or f"sub_{ea:X}"
        row["literals"] = sorted(set(row.get("literals", [])))
        row["constants"] = sorted({ea_text(x) for x in row.get("constants", [])})
        row["edges"] = int(row.get("edges", 0))
        row["back_edges"] = int(row.get("back_edges", 0))
        row["callees"] = sorted(ea_text(x) for x in row.get("callees", []))
        row["data_refs"] = sorted(ea_text(x) for x in row.get("data_refs", []))
        result[ea] = row
    return result


def merge_c_metadata(features, parsed):
    for ea, function in parsed.items():
        row = features.setdefault(ea, {"ea": ea, "bb": 0, "size": 0, "callees": [], "data_refs": []})
        row["name"] = function["name"]
        row["literals"] = sorted(set(row.get("literals", [])) | set(function["literals"]))
    return features


def parse_rename_index_text(text):
    result = {}
    for line in text.splitlines():
        if "|" not in line or "sub_" not in line:
            continue
        cells = [cell.strip().strip("`") for cell in line.strip().strip("|").split("|")]
        address_index = None
        address = None
        for index, cell in enumerate(cells):
            match = re.search(r"\bsub_([0-9A-Fa-f]+)\b", cell)
            if match:
                address_index = index
                address = int(match.group(1), 16)
                break
        if address is None:
            continue
        name = None
        for cell in cells[address_index + 1:]:
            candidate = cell.strip().strip("`")
            if re.fullmatch(r"[A-Za-z_]\w*", candidate) and candidate.lower() not in {"high", "medium", "low"}:
                name = candidate
                break
        confidence = next((cell.lower() for cell in cells if cell.lower() in {"high", "medium", "low"}), None)
        if name and confidence:
            result[address] = {
                "ea": address,
                "name": name,
                "confidence": confidence,
                "row": line.strip(),
            }
    return result


def parse_rename_index(path):
    return parse_rename_index_text(Path(path).read_text(encoding="utf-8", errors="replace"))


def load_master_map(path):
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    rows = data.get("rows", data) if isinstance(data, dict) else data
    return {normalize_ea(row["ea"]): dict(row) for row in rows}


def load_reviews(path):
    if not path:
        return {"calibration": [], "game": []}
    return json.loads(Path(path).read_text(encoding="utf-8"))


def review_key(row):
    return normalize_ea(row["dos_ea"]), normalize_ea(row["clash95_ea"])


def literal_index(functions, minimum_length):
    index = defaultdict(set)
    for ea, row in functions.items():
        for literal in row.get("literals", []):
            if len(literal) >= minimum_length:
                index[literal].add(ea)
    return index


def unique_shared_pairs(dos_functions, clash95_functions, minimum_length=5):
    dos_index = literal_index(dos_functions, minimum_length)
    clash95_index = literal_index(clash95_functions, minimum_length)
    pairs = defaultdict(set)
    for literal in sorted(set(dos_index) & set(clash95_index)):
        if len(dos_index[literal]) == 1 and len(clash95_index[literal]) == 1:
            dos_ea = next(iter(dos_index[literal]))
            clash95_ea = next(iter(clash95_index[literal]))
            pairs[(dos_ea, clash95_ea)].add(literal)
    return pairs


def collapse_bijection(pairs):
    dos_targets = defaultdict(set)
    clash95_targets = defaultdict(set)
    for dos_ea, clash95_ea in pairs:
        dos_targets[dos_ea].add(clash95_ea)
        clash95_targets[clash95_ea].add(dos_ea)
    accepted = {}
    rejected = []
    for pair, literals in sorted(pairs.items()):
        dos_ea, clash95_ea = pair
        if len(dos_targets[dos_ea]) != 1 or len(clash95_targets[clash95_ea]) != 1:
            rejected.append({
                "dos_ea": ea_text(dos_ea),
                "clash95_ea": ea_text(clash95_ea),
                "literals": sorted(literals),
                "reason": "bijection-conflict",
            })
            continue
        accepted[pair] = sorted(literals)
    return accepted, rejected


def evenly_spaced(rows, limit):
    if len(rows) <= limit:
        return list(rows)
    if limit <= 1:
        return [rows[0]]
    indexes = []
    for index in range(limit):
        value = round(index * (len(rows) - 1) / (limit - 1))
        if value not in indexes:
            indexes.append(value)
    return [rows[index] for index in indexes]


def candidate_row(dos_ea, clash95_ea, literals, dos, clash95, rename):
    return {
        "dos_ea": ea_text(dos_ea),
        "clash95_ea": ea_text(clash95_ea),
        "proposed_name": rename["name"],
        "clash95_confidence": rename["confidence"],
        "dos_name": dos["name"],
        "dos_size": dos.get("size", 0),
        "clash95_size": clash95.get("size", 0),
        "dos_basic_blocks": dos.get("bb", 0),
        "clash95_basic_blocks": clash95.get("bb", 0),
        "dos_edges": dos.get("edges", 0),
        "clash95_edges": clash95.get("edges", 0),
        "dos_back_edges": dos.get("back_edges", 0),
        "clash95_back_edges": clash95.get("back_edges", 0),
        "dos_constants": dos.get("constants", []),
        "clash95_constants": clash95.get("constants", []),
        "shared_unique_literals": sorted(literals),
        "dos_callees": dos.get("callees", []),
        "clash95_callees": clash95.get("callees", []),
        "dos_data_refs": dos.get("data_refs", []),
        "clash95_data_refs": clash95.get("data_refs", []),
        "status": "pending-independent-review",
    }


def build_candidates(dos_functions, clash95_functions, rename_index, master_map, game_start, clips_start, minimum_bb, minimum_literal_length):
    shared = unique_shared_pairs(dos_functions, clash95_functions, minimum_literal_length)
    bijective, review_rows = collapse_bijection(shared)
    master_names = defaultdict(set)
    for ea, row in master_map.items():
        master_names[normalize_name(row["name"])].add(ea)

    proposals = []
    calibration_pool = []
    proposed_names = defaultdict(list)
    for (dos_ea, clash95_ea), literals in sorted(bijective.items()):
        dos = dos_functions.get(dos_ea, {})
        clash95 = clash95_functions.get(clash95_ea, {})
        rename = rename_index.get(clash95_ea)
        if not rename or rename["confidence"] not in {"high", "medium"}:
            review_rows.append({"dos_ea": ea_text(dos_ea), "clash95_ea": ea_text(clash95_ea), "literals": literals, "reason": "clash95-confidence-gate"})
            continue
        if dos.get("bb", 0) < minimum_bb or clash95.get("bb", 0) < minimum_bb:
            review_rows.append({"dos_ea": ea_text(dos_ea), "clash95_ea": ea_text(clash95_ea), "literals": literals, "reason": "basic-block-gate"})
            continue

        if dos_ea >= clips_start:
            known = master_map.get(dos_ea)
            if known and normalize_name(known["name"]) == normalize_name(rename["name"]):
                calibration_pool.append(candidate_row(dos_ea, clash95_ea, literals, dos, clash95, rename))
            continue

        if dos_ea < game_start:
            review_rows.append({"dos_ea": ea_text(dos_ea), "clash95_ea": ea_text(clash95_ea), "literals": literals, "reason": "outside-game-range"})
            continue
        if dos_ea in master_map:
            review_rows.append({"dos_ea": ea_text(dos_ea), "clash95_ea": ea_text(clash95_ea), "literals": literals, "reason": "already-in-master-map"})
            continue
        if not SUB_RE.fullmatch(dos.get("name", "")):
            review_rows.append({"dos_ea": ea_text(dos_ea), "clash95_ea": ea_text(clash95_ea), "literals": literals, "reason": "dos-function-already-named"})
            continue
        semantic_name = normalize_name(rename["name"])
        if semantic_name in master_names:
            review_rows.append({"dos_ea": ea_text(dos_ea), "clash95_ea": ea_text(clash95_ea), "literals": literals, "reason": "would-create-name-collision", "name": semantic_name})
            continue
        row = candidate_row(dos_ea, clash95_ea, literals, dos, clash95, rename)
        proposals.append(row)
        proposed_names[semantic_name].append(row)

    unique_proposals = []
    for row in proposals:
        semantic_name = normalize_name(row["proposed_name"])
        if len(proposed_names[semantic_name]) > 1:
            rejected = dict(row)
            rejected["reason"] = "candidate-name-collision"
            review_rows.append(rejected)
        else:
            unique_proposals.append(row)
    return unique_proposals, calibration_pool, sorted(review_rows, key=lambda row: (normalize_ea(row["dos_ea"]), normalize_ea(row["clash95_ea"])))


def apply_reviews(proposals, calibration, reviews):
    calibration_reviews = {review_key(row): row for row in reviews.get("calibration", [])}
    game_reviews = {review_key(row): row for row in reviews.get("game", [])}

    calibration_results = []
    valid_verdicts = {"CONFIRM", "REJECT", "UNCERTAIN"}
    for row in calibration:
        key = review_key(row)
        review = calibration_reviews.get(key)
        result = dict(row)
        verdict = review.get("verdict", "PENDING") if review else "PENDING"
        reason = review.get("reason", "") if review else ""
        result["verdict"] = verdict if verdict in valid_verdicts and reason.strip() else "PENDING"
        result["review_reason"] = reason
        calibration_results.append(result)
    reviewed = [row for row in calibration_results if row["verdict"] in valid_verdicts]
    confirmed = [row for row in calibration_results if row["verdict"] == "CONFIRM"]
    complete = len(reviewed) == len(calibration_results) and bool(calibration_results)
    ratio = len(confirmed) / len(calibration_results) if calibration_results else 0.0
    calibration_passed = complete and ratio >= 0.95

    confirmed_transfers = []
    candidate_reviews = []
    for row in proposals:
        key = review_key(row)
        review = game_reviews.get(key)
        reviewed_row = dict(row)
        reviewed_row["verdict"] = review.get("verdict", "PENDING") if review else "PENDING"
        reviewed_row["review_reason"] = review.get("reason", "") if review else ""
        reviewed_row["distinctive_constants"] = review.get("distinctive_constants", []) if review else []
        reviewed_row["branch_loop_shape"] = review.get("branch_loop_shape", "") if review else ""
        reviewed_row["callee_data_evidence"] = review.get("callee_data_evidence", "") if review else ""
        reviewed_row["literal_context"] = review.get("literal_context", "") if review else ""
        evidence_complete = bool(
            reviewed_row["review_reason"].strip()
            and reviewed_row["distinctive_constants"]
            and reviewed_row["branch_loop_shape"].strip()
            and reviewed_row["callee_data_evidence"].strip()
            and reviewed_row["literal_context"].strip()
        )
        reviewed_row["evidence_complete"] = evidence_complete
        candidate_reviews.append(reviewed_row)
        if not calibration_passed or reviewed_row["verdict"] != "CONFIRM" or not evidence_complete:
            continue
        confirmed_transfers.append({
            "ea": row["dos_ea"],
            "name": normalize_name(row["proposed_name"]),
            "confidence": row["clash95_confidence"],
            "source": "clash95-transfer",
            "evidence": reviewed_row["review_reason"],
            "clash95_ea": row["clash95_ea"],
            "shared_unique_literals": row["shared_unique_literals"],
        })

    summary = {
        "selected": len(calibration_results),
        "reviewed": len(reviewed),
        "confirmed": len(confirmed),
        "failure_count": len(calibration_results) - len(confirmed),
        "confirmation_ratio": ratio,
        "threshold": 0.95,
        "complete": complete,
        "passed": calibration_passed,
    }
    return calibration_results, candidate_reviews, confirmed_transfers, summary


def write_json(path, data):
    Path(path).write_text(json.dumps(data, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--dos-features", required=True)
    parser.add_argument("--clash95-features", required=True)
    parser.add_argument("--dos-c")
    parser.add_argument("--clash95-c")
    parser.add_argument("--master-map", required=True)
    parser.add_argument("--rename-index", required=True)
    parser.add_argument("--reviews")
    parser.add_argument("--output-dir", required=True)
    parser.add_argument("--game-start", type=lambda value: int(value, 0), default=0x12C6E)
    parser.add_argument("--clips-start", type=lambda value: int(value, 0), default=0x88370)
    parser.add_argument("--minimum-basic-blocks", type=int, default=3)
    parser.add_argument("--minimum-literal-length", type=int, default=5)
    parser.add_argument("--calibration-size", type=int, default=40)
    args = parser.parse_args(argv)

    dos = load_feature_export(args.dos_features)
    clash95 = load_feature_export(args.clash95_features)
    if args.dos_c:
        merge_c_metadata(dos, parse_ida_c(args.dos_c))
    if args.clash95_c:
        merge_c_metadata(clash95, parse_ida_c(args.clash95_c))
    master = load_master_map(args.master_map)
    rename_index = parse_rename_index(args.rename_index)
    proposals, calibration_pool, rejected = build_candidates(
        dos,
        clash95,
        rename_index,
        master,
        args.game_start,
        args.clips_start,
        args.minimum_basic_blocks,
        args.minimum_literal_length,
    )
    calibration = evenly_spaced(sorted(calibration_pool, key=lambda row: normalize_ea(row["dos_ea"])), args.calibration_size)
    calibration_results, candidate_reviews, confirmed, calibration_summary = apply_reviews(proposals, calibration, load_reviews(args.reviews))

    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    write_json(output_dir / "dos_crossbuild_proposals.json", {
        "schema": 1,
        "candidate_count": len(proposals),
        "candidates": proposals,
    })
    write_json(output_dir / "dos_crossbuild_calibration.json", {
        "schema": 1,
        "summary": calibration_summary,
        "pairs": calibration_results,
    })
    write_json(output_dir / "dos_crossbuild_confirmed.json", {
        "schema": 1,
        "calibration_passed": calibration_summary["passed"],
        "rows": confirmed,
    })
    write_json(output_dir / "dos_crossbuild_review.json", {
        "schema": 1,
        "rejected_or_filtered": rejected,
        "candidate_reviews": candidate_reviews,
    })
    print(json.dumps({
        "proposals": len(proposals),
        "calibration_pairs": len(calibration),
        "calibration_passed": calibration_summary["passed"],
        "confirmed_transfers": len(confirmed),
        "review_rows": len(rejected) + len(candidate_reviews),
    }, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
