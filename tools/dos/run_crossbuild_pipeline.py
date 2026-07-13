#!/usr/bin/env python3
import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class PipelinePaths:
    repo: Path
    work: Path
    dos_source: Path
    clash95_source: Path
    ida: Path

    @property
    def dos_feature_db(self):
        return self.work / "clash_features.i64"

    @property
    def clash95_feature_db(self):
        return self.work / "clash95_features.i64"

    @property
    def dos_features(self):
        return self.work / "dos_features.json"

    @property
    def clash95_features(self):
        return self.work / "clash95_features.json"

    @property
    def crossbuild_dir(self):
        return self.work / "crossbuild"

    @property
    def candidate_map(self):
        return self.work / "dos_master_map.json"

    @property
    def candidate_conflicts(self):
        return self.work / "dos_name_conflicts.json"

    @property
    def candidate_dropped(self):
        return self.work / "dos_dropped_false_anchors.json"

    @property
    def regen_db(self):
        return self.work / "clash_regen.i64"

    @property
    def seed_report(self):
        return self.work / "seed_report.json"

    @property
    def generated_c(self):
        return self.work / "clash_regen.c"

    @property
    def export_report(self):
        return self.work / "export_report.json"

    @property
    def verify_report(self):
        return self.work / "verify_report.json"

    @property
    def manifest(self):
        return self.work / "pipeline_manifest.json"


def resolved(path):
    return Path(path).expanduser().resolve()


def is_relative_to(path, parent):
    try:
        path.relative_to(parent)
        return True
    except ValueError:
        return False


def validate_layout(paths, dry_run=False):
    if paths.work == paths.repo or is_relative_to(paths.work, paths.repo):
        raise ValueError("work directory must be outside the repository")
    if paths.dos_feature_db == paths.dos_source or paths.regen_db == paths.dos_source:
        raise ValueError("temporary DOS databases must differ from the original")
    if paths.clash95_feature_db == paths.clash95_source:
        raise ValueError("temporary clash95 database must differ from the original")
    if dry_run:
        return
    if os.name != "nt":
        raise RuntimeError("non-dry-run execution requires Windows and IDA Pro")
    for path in (paths.dos_source, paths.clash95_source, paths.ida):
        if not path.is_file():
            raise FileNotFoundError(path)


def ida_script_arg(script, args):
    payload = subprocess.list2cmdline([str(script), *[str(value) for value in args]])
    return "-S" + payload


def ida_command(ida, script, args, database, log):
    return [
        str(ida),
        "-A",
        ida_script_arg(script, args),
        "-L" + str(log),
        str(database),
    ]


def matcher_command(paths, python_exe, reviews=None):
    command = [
        python_exe,
        str(paths.repo / "tools/dos/crossbuild_match.py"),
        "--dos-features",
        str(paths.dos_features),
        "--clash95-features",
        str(paths.clash95_features),
        "--dos-c",
        str(paths.repo / "clash.c"),
        "--clash95-c",
        str(paths.repo / "clash95.c"),
        "--master-map",
        str(paths.repo / "tools/dos/dos_master_map.json"),
        "--rename-index",
        str(paths.repo / "docs/archive/SUB_RENAME_INDEX.md"),
        "--output-dir",
        str(paths.crossbuild_dir),
    ]
    if reviews:
        command.extend(["--reviews", str(reviews)])
    return command


def map_command(paths, python_exe, check=False):
    command = [
        python_exe,
        str(paths.repo / "tools/dos/build_master_map.py"),
        "--transfers",
        str(paths.crossbuild_dir / "dos_crossbuild_confirmed.json"),
        "--output",
        str(paths.candidate_map),
        "--conflicts",
        str(paths.candidate_conflicts),
        "--dropped",
        str(paths.candidate_dropped),
    ]
    if check:
        command.append("--check")
    return command


def verify_command(paths, python_exe):
    return [
        python_exe,
        str(paths.repo / "tools/dos/verify_regeneration.py"),
        str(paths.repo / "clash.c"),
        str(paths.generated_c),
        str(paths.candidate_map),
        str(paths.seed_report),
        str(paths.verify_report),
        "--confirmed-transfers",
        str(paths.crossbuild_dir / "dos_crossbuild_confirmed.json"),
    ]


def build_commands(paths, python_exe, reviews=None, regenerate=False):
    commands = [
        (
            "export-dos-features",
            ida_command(
                paths.ida,
                paths.repo / "tools/ida/export_features.py",
                [paths.dos_features],
                paths.dos_feature_db,
                paths.work / "dos_features.log",
            ),
        ),
        (
            "export-clash95-features",
            ida_command(
                paths.ida,
                paths.repo / "tools/ida/export_features.py",
                [paths.clash95_features],
                paths.clash95_feature_db,
                paths.work / "clash95_features.log",
            ),
        ),
        ("generate-crossbuild-artifacts", matcher_command(paths, python_exe, reviews)),
        ("build-candidate-map", map_command(paths, python_exe)),
        ("check-candidate-map", map_command(paths, python_exe, check=True)),
    ]
    if regenerate:
        commands.extend([
            (
                "seed-regeneration-database",
                ida_command(
                    paths.ida,
                    paths.repo / "tools/ida/seed_names.py",
                    [paths.candidate_map, paths.seed_report, "--fix-dos-gettoken"],
                    paths.regen_db,
                    paths.work / "seed.log",
                ),
            ),
            (
                "export-regenerated-clash-c",
                ida_command(
                    paths.ida,
                    paths.repo / "tools/ida/export_clash_c.py",
                    [paths.generated_c, paths.export_report],
                    paths.regen_db,
                    paths.work / "export.log",
                ),
            ),
            ("verify-regeneration", verify_command(paths, python_exe)),
        ])
    return commands


def command_text(command):
    return subprocess.list2cmdline([str(value) for value in command])


def run_command(name, command, repo, dry_run=False):
    print(f"[{name}] {command_text(command)}", flush=True)
    if dry_run:
        return
    subprocess.run(command, cwd=repo, check=True)


def copy_database(source, destination, resume=False, dry_run=False):
    print(f"[copy] {source} -> {destination}", flush=True)
    if dry_run:
        return
    if destination.exists():
        if resume:
            return
        raise FileExistsError(destination)
    shutil.copy2(source, destination)


def require_file(path, dry_run=False):
    if not dry_run and not path.is_file():
        raise RuntimeError(f"expected output was not created: {path}")


def load_json(path):
    return json.loads(path.read_text(encoding="utf-8"))


def require_review_gate(paths, reviews, dry_run=False):
    if dry_run:
        return
    calibration_path = paths.crossbuild_dir / "dos_crossbuild_calibration.json"
    confirmed_path = paths.crossbuild_dir / "dos_crossbuild_confirmed.json"
    calibration = load_json(calibration_path)
    confirmed = load_json(confirmed_path)
    if reviews is None:
        if confirmed.get("rows"):
            raise RuntimeError("unreviewed matcher run unexpectedly emitted confirmed transfers")
        return
    summary = calibration.get("summary", {})
    if not summary.get("complete") or not summary.get("passed"):
        raise RuntimeError("calibration is incomplete or below the 95% confirmation threshold")
    if not confirmed.get("calibration_passed"):
        raise RuntimeError("confirmed transfer artifact does not record a passed calibration")


def sha256(path):
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        while True:
            chunk = handle.read(1024 * 1024)
            if not chunk:
                break
            digest.update(chunk)
    return digest.hexdigest()


def write_manifest(paths, reviews, regenerate, dry_run=False):
    if dry_run:
        return
    outputs = [
        paths.dos_features,
        paths.clash95_features,
        paths.crossbuild_dir / "dos_crossbuild_proposals.json",
        paths.crossbuild_dir / "dos_crossbuild_calibration.json",
        paths.crossbuild_dir / "dos_crossbuild_confirmed.json",
        paths.crossbuild_dir / "dos_crossbuild_review.json",
        paths.candidate_map,
        paths.candidate_conflicts,
        paths.candidate_dropped,
    ]
    if regenerate:
        outputs.extend([paths.seed_report, paths.generated_c, paths.export_report, paths.verify_report])
    manifest = {
        "schema": 1,
        "repo": str(paths.repo),
        "work": str(paths.work),
        "reviews": str(reviews) if reviews else None,
        "regenerated": regenerate,
        "inputs": {
            str(paths.dos_source): sha256(paths.dos_source),
            str(paths.clash95_source): sha256(paths.clash95_source),
            str(paths.repo / "clash.c"): sha256(paths.repo / "clash.c"),
            str(paths.repo / "clash95.c"): sha256(paths.repo / "clash95.c"),
            str(paths.repo / "tools/dos/dos_master_map.json"): sha256(paths.repo / "tools/dos/dos_master_map.json"),
        },
        "outputs": {str(path): sha256(path) for path in outputs if path.is_file()},
    }
    paths.manifest.write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def prepare_workdir(paths, resume=False, dry_run=False):
    if dry_run:
        return
    if paths.work.exists() and any(paths.work.iterdir()) and not resume:
        raise RuntimeError("work directory is not empty; use --resume or choose a new directory")
    paths.work.mkdir(parents=True, exist_ok=True)
    paths.crossbuild_dir.mkdir(parents=True, exist_ok=True)


def parse_args(argv=None):
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo", default=repo)
    parser.add_argument("--work-dir", required=True)
    parser.add_argument("--dos-idb", default=r"C:\Clash\clash.i64")
    parser.add_argument("--clash95-idb", default=r"C:\Clash\clash95.i64")
    parser.add_argument("--ida", default=r"C:\Program Files\IDA Professional 9.0\idat.exe")
    parser.add_argument("--python", default=sys.executable)
    parser.add_argument("--reviews")
    parser.add_argument("--regenerate", action="store_true")
    parser.add_argument("--resume", action="store_true")
    parser.add_argument("--dry-run", action="store_true")
    return parser.parse_args(argv)


def main(argv=None):
    args = parse_args(argv)
    paths = PipelinePaths(
        repo=resolved(args.repo),
        work=resolved(args.work_dir),
        dos_source=resolved(args.dos_idb),
        clash95_source=resolved(args.clash95_idb),
        ida=resolved(args.ida),
    )
    reviews = resolved(args.reviews) if args.reviews else None
    if args.regenerate and reviews is None:
        raise ValueError("--regenerate requires --reviews")
    validate_layout(paths, args.dry_run)
    prepare_workdir(paths, args.resume, args.dry_run)
    copy_database(paths.dos_source, paths.dos_feature_db, args.resume, args.dry_run)
    copy_database(paths.clash95_source, paths.clash95_feature_db, args.resume, args.dry_run)
    if args.regenerate:
        copy_database(paths.dos_source, paths.regen_db, args.resume, args.dry_run)
    commands = build_commands(paths, args.python, reviews, args.regenerate)
    for name, command in commands:
        run_command(name, command, paths.repo, args.dry_run)
        if name == "export-dos-features":
            require_file(paths.dos_features, args.dry_run)
        elif name == "export-clash95-features":
            require_file(paths.clash95_features, args.dry_run)
        elif name == "generate-crossbuild-artifacts":
            require_review_gate(paths, reviews, args.dry_run)
        elif name == "seed-regeneration-database":
            require_file(paths.seed_report, args.dry_run)
        elif name == "export-regenerated-clash-c":
            require_file(paths.generated_c, args.dry_run)
            require_file(paths.export_report, args.dry_run)
        elif name == "verify-regeneration":
            require_file(paths.verify_report, args.dry_run)
    write_manifest(paths, reviews, args.regenerate, args.dry_run)
    print(f"pipeline complete: {paths.work}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
