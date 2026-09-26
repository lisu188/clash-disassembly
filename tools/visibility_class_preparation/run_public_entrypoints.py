#!/usr/bin/env python3
"""Run all three public wrappers for a required compiler; reject skips."""
import argparse
import json
from pathlib import Path
import shutil
import sys
import unittest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, required=True)
    parser.add_argument("--compiler", choices=("g++-13", "clang++-18"), required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if not shutil.which(args.compiler):
        raise RuntimeError("Required compiler unavailable: " + args.compiler)
    if args.output.exists():
        raise FileExistsError(args.output)
    root = args.root.resolve(strict=True)
    sys.path.insert(0, str(root / "tests/tools"))
    prefix = "gcc" if args.compiler == "g++-13" else "clang"
    names = [
        f"test_reveal_propagation.RevealPropagationTest.test_{prefix}_actual_propagation",
        f"test_fog_overlay.FogOverlayTest.test_{prefix}_truth_table_and_visibility_order",
        f"test_class_world_visibility.WorldVisibilityBindingTest.test_{prefix}_binding_lifecycle",
    ]
    suite = unittest.defaultTestLoader.loadTestsFromNames(names)
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    passed = result.wasSuccessful() and result.testsRun == 3 and not result.skipped
    report = {
        "pass": passed,
        "compiler": args.compiler,
        "root": str(root),
        "requested_tests": names,
        "tests_run": result.testsRun,
        "skipped": [(test.id(), reason) for test, reason in result.skipped],
        "failures": [(test.id(), trace) for test, trace in result.failures],
        "errors": [(test.id(), trace) for test, trace in result.errors],
    }
    with args.output.open("x") as stream:
        json.dump(report, stream, indent=2)
        stream.write("\n")
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())
