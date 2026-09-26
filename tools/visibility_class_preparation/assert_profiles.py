#!/usr/bin/env python3
"""Require every explicit hosted visibility profile and comparison lane."""
import argparse
import json
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--summary", type=Path, required=True)
    parser.add_argument("--compiler", required=True)
    args = parser.parse_args()
    report = json.loads(args.summary.read_text())
    expected_profiles = {
        f"{Path(args.compiler).name}-{optimization}-{chars}"
        for optimization in ("O0", "O2")
        for chars in ("signed", "unsigned")
    }
    profiles = report["profiles"]
    assert report["pass"] is True and report["source_inputs_unchanged"] is True
    assert len(profiles) == 4
    assert {item["profile"] for item in profiles} == expected_profiles
    for item in profiles:
        assert item["lanes"] == ["frozen", "adapter", "direct"]
        assert item["cases_per_lane"] == {"reveal": 2034, "fog": 33792, "binding": 1}
        assert item["build"] == 0 and set(item["runs"]) == {"reveal", "fog", "binding"}
        for result in item["runs"].values():
            assert result["build"] == 0 and result["run"] == 0
            assert result["expected_output"] is True
    print("Four required profiles, three comparison lanes, and all three fixture kinds passed.")


if __name__ == "__main__":
    main()
