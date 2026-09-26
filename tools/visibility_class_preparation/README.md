# Provisional WorldMap visibility hosted preparation packet

This is a reviewable source-only preparation packet, not a completed migration or
acceptance seal. It prepares exactly three WorldMap identities against frozen
reconstruction commit `705fc0fe9b01b7587a7a6290f15379dbd8a1d264`:
`Map_RevealTileWithPropagation`, `Map_IsTileVisibleToPlayer`, and
`Map_ClassifyFogOfWarOverlayForPlayer`.

No compiler, native test, runtime capture, or full source-tree expansion was run
locally to create this packet. Initial intake occurred while Windows C exceeded
the project's 90%-used threshold. Before dispatch, root reported a fresh sample
at 2026-09-26T19:47:08.668Z of 114,400,567,296 bytes free out of 999,595,962,368
(about 88.55% used), with
Ubuntu writable at 19% used and 24.4 GB available RAM. That later capacity change
does not alter the historical hold receipts or this packet's hosted-only scope.
All tree-producing commands require Linux with `GITHUB_ACTIONS=true`;
write-mode recipe application additionally requires a private `RUNNER_TEMP`
child outside `GITHUB_WORKSPACE`. Source and packet paths reject symlinks and
junctions. Output directories must not exist, must not overlap protected trees,
and must have an existing parent below 90% usage with at least 1 GiB free.

## Exact retained inputs

`input-provenance.json` lists every candidate/input file and its origin hash.
`expected-stages.json` maps every regular file in all three historical stages:
582 baseline, 593 extraction, 594 relocation. The retained source archive was
10,369,157 bytes, SHA256
`673b0a678a4e55e79425861511ec85e74acce2ffa118f936b67aa911fa174887`.
Only selected small members were copied; all 1,769 regular members were hashed
while streaming. No tree was extracted. Its baseline map exactly matches the
original `input-freeze.json`.

The only deliberate expected-stage override is the latest loose
`verify_world_visibility.py` in both candidate stages. It adds optional local
resource guards and durable per-profile progress to the archived runner. The
archive already contains the corrected public-wrapper dispatch, absolute
compiler-path handling, and final explicit frozen/adapter/direct signed-query
extreme assertions. Those assertions have not yet received a completed fresh
compiler run. The archived positive receipts predate them.

The nine final fixture files occupy 34,234 bytes. Three public test wrappers,
three canonical bodies, three adapters, header, binding, narrow metadata recipe,
measured allowance additions, frozen input map and separately retained relocated
class source are also included. They are reconstruction source and existing
observed expectation tables. Original executable/resource/save/media bytes,
private captures, object evidence, and the complete three-tree archive are not
included in the publication allowlist.

`assemble_packet.py` and `finalize_input_receipt.py` are retained local intake
history and are excluded from publication. Use `publication.json` as an exact
allowlist; do not copy the entire historical preparation directory. A public
checkout must include the frozen commit in Git history: use a full checkout or
an explicit fetch of that commit. Ordinary fixture execution does not use Git.

## Hosted command sequence

The coordinating task owns the diagnostic branch and workflow. In the examples,
`PACKET` is the copied packet directory; outputs are absent sibling directories
under `RUNNER_TEMP`. Both GCC 13 and Clang 18 are mandatory. The standard Python
library, Git, GNU linker and selected compiler suffice for the focused runner;
the focused header-policy tooling also requires a `g++` executable. No retail
install, SDL runtime, Wine, display, CMake build or capture is needed here.

```bash
python3 "$PACKET/materialize.py" --audit-inputs
python3 "$PACKET/materialize.py" --repo "$GITHUB_WORKSPACE" \
  --output "$RUNNER_TEMP/visibility-stages"
python3 "$PACKET/verify_recipe.py" \
  --work-root "$RUNNER_TEMP/visibility-stages" \
  --output "$RUNNER_TEMP/visibility-recipe"
```

Materialization obtains only `src`, `tools`, `data`, `tests/tools` and
`tests/unit/pure_set.json` from the pinned tracked source. It generates the two
stages independently, regenerates metadata, and requires every file hash to
match the retained expected map. `materialization-summary.json` and metadata
logs remain outside the source trees. A mismatch is a failure to inspect, not
permission to update the expected hashes.

Recipe verification begins from a fresh baseline copy and applies extraction
then relocation using the separate narrow recipe. It checks every generated
file, including unexpected extras, against the independently materialized
stages. `recipe-summary.json` retains success or failure. This avoids the older
recipe's dependency on the not-yet-created `complete-stages.tar.gz`.

For each compiler matrix entry set `CXX` to exactly `g++-13` or `clang++-18`:

```bash
command -v "$CXX"
"$CXX" --version
for stage in extraction relocation; do
  root="$RUNNER_TEMP/visibility-stages/$stage"
  python3 "$root/tests/tools/fixtures/class_world_visibility/verify_world_visibility.py" \
    --root "$root" --output "$RUNNER_TEMP/visibility-$stage-$CXX" \
    --kind all --compiler "$CXX" --optimization O0 --optimization O2 \
    --char-mode signed --char-mode unsigned
done
python3 "$PACKET/validate_tooling.py" \
  --root "$RUNNER_TEMP/visibility-stages/extraction" \
  --output "$RUNNER_TEMP/visibility-extraction-tooling-$CXX" \
  --compiler "$CXX" --metadata-only
python3 "$PACKET/validate_tooling.py" \
  --root "$RUNNER_TEMP/visibility-stages/relocation" \
  --output "$RUNNER_TEMP/visibility-relocation-tooling-$CXX" --compiler "$CXX"
```

The workflow should run stages as independent steps or explicitly preserve both
outcomes; the example loop alone stops on the first failure under `set -e`.
Require exactly four unique O0/O2 × signed/unsigned profiles per compiler per
stage: 16 profiles and 48 binaries/runs overall. Each profile has three lanes,
2,034 reveal cases, 33,792 fog cases, one binding corpus, exact expected stdout,
zero run/build codes, and unchanged source-input hashes. Preserve compiler
versions, checkout SHA, workflow/run identifiers, complete output trees and
outer logs through success-or-failure uploads. Missing summaries/profiles are
failures, not skips. `validate_tooling.py` rejects required-compiler absence and
reported unittest skips while preserving all command outcomes.

Do not enable `CLASH95_WORLD_VISIBILITY_RESOURCE_GUARD=1` in hosted CI: it is the
old workstation-specific 12-GiB disk/8-GiB RAM check. This is not a relaxation of
the local 90% guard; hosted outputs receive their own entry capacity check.

## Evidence still required

Hosted materialization, recipe equality, final profiles, corrected public
wrappers and focused tooling remain unexecuted at packet creation. After these
pass, root may test the narrow recipe against a separate hosted copy of the
current checkout. That compatibility check must preserve all unrelated class
work and cannot replace exact-pin proof. Do not apply write mode to the workflow
checkout or the shared local tree.

Existing original failure/resource-held receipts and the invalid old
`source-stages.tar.gz` remain untouched in their original location. This packet
does not create or rename a historical archive as complete. Full production
build/link/storage, native outcomes, 718-function coverage at the unchanged
89.7% floor with zero uncovered identities, route gates and any required fresh
frame pairs remain separate integration requirements. Classifier arithmetic
extremes remain outside the proven domain. Full WorldMap, Road continuation,
campaign completion and whole-game equivalence are not claimed.
