# Resumed class checkpoint validation

Track: Win95 reconstruction; frontier: the requested behavior-class migration.
This report pins the 19-method checkpoint at `366278b`, after UnitSlot fatigue
and order-state relocation and UnitStack strength/cargo relocation. It does not
cover subsequent extractions. The ordered inventory contains 146 recovered TUs,
including six class-named sources, and retains all 4,157 historical identities.

The complete tooling suite passes **523 tests, with no skips** in 247.067 seconds.
The run used a frozen archive of 920 tracked source inputs. All 920 hashes still
match after testing; the log SHA-256 is
`3777539a8894dc6cd601f68608794c6fcf9dd945a0e5b516ec51b896eda3a4`.
The archive, individual test output and commands are retained under
`artifacts/cpp-classes/20260913/tooling-19-methods/`.

Eleven additional checks pass on that same frozen source: split-source audit,
canonical coverage metadata, save-format contract, constant guard, recovered
structures, unit metadata, game-class catalogue, support inventory, source
inventory, class-manifest synchronization and body hashes.
The metadata run also pins copies of both production executables and archives
against the hashes from the validated UnitStack relocation.

The historical numerical ratchets remain unchanged and visibly fail:

| Check | Current outcome |
| --- | --- |
| Header surface | 24 numeric differences; every difference is enumerated |
| GCC raw link baseline | 450 differences; zero archive cross-check errors |
| Clang raw link baseline | 702 differences; zero archive cross-check errors |
| Strict migration surface comparison | Both compilers pass against the verified published-main reference and exact added-text inventory |

These are distinct checks. Passing the migration comparison does not relabel
the historical ratchets as passing. Complete metrics, raw logs, commands and
hash-pinned binaries are under
`artifacts/cpp-classes/20260913/metadata-19-methods/`. That directory's
header-full-metrics.json retains all 24 numeric differences, including those
beyond the header check's shortened console output.

Commands from the repository root in WSL:

```sh
python3 artifacts/cpp-classes/20260913/run-frozen-tooling.py
python3 artifacts/cpp-classes/20260913/check-frozen-19-metadata.py
```

The tooling wrapper runs `python3 -m unittest discover -s tests/tools -p
'test_*.py' -v` in the frozen source directory. Existing production compiler,
storage, initialization and asset-free results are recorded in
[UNIT_STACK_REGISTER_CLASSES.md](UNIT_STACK_REGISTER_CLASSES.md) and
[UNIT_SLOT_CLASS_MIGRATION.md](UNIT_SLOT_CLASS_MIGRATION.md).

The initial metadata wrapper also reported a Markdown-link pass, but that
Git-based checker enumerated no tracked documents inside the extracted archive.
It was not a valid documentation gate. Running it in the actual worktree found
six earlier shorthand filenames and one newly introduced shorthand filename;
those references were corrected and the worktree check was repeated. The
original wrapper result remains retained and is excluded from the eleven
meaningful frozen checks above.

Native crash isolation and full coverage have not yet been rerun at this
19-method checkpoint. The earlier compiler-specific outcomes remain in
[CPP_CLASS_NATIVE_BASELINE.md](CPP_CLASS_NATIVE_BASELINE.md), including the
Clang assertion and eight uncovered procedural CLIPS identities. The frozen
718 identities, 89.7% floor and zero-uncovered requirement remain in force.
Current source-extraction measurements add three executable lines in that set
relative to the earlier baseline; this inventory is not a full coverage pass.

Fresh headless runtime comparisons are being retained separately under
`artifacts/cpp-classes/20260913/runtime-19-methods/`. A runtime checkpoint,
original frame comparison, campaign-route completion and full class-migration
acceptance remain separate claims.
