# Construct-code file opener recovery

Track: Win95 reconstruction; base `e81f17e`. This batch repairs the bounded
`Rules_OpenConstructCodeFile` contract at `0x004A7140` and transports its lost
ECX input through all 26 canonical call sites. It does not validate the complete
construct compiler, an actual filesystem session, or a campaign route.

## Original instruction evidence

The protected `clash95.asm` procedure `sub_4A7140` retains the basename in ESI,
formats the filename pattern "%s%d_%d.c", and tests ECX to choose append (`a`) or
fresh-file (`w`) mode. After the open it tests the preserved ECX again. Only a successful fresh
open emits `#include "<basename>.h"` followed by a blank line, to the returned
stream. Open failure reports `constructs-to-c` and the generated filename,
then returns zero. Formatting return values do not replace the stream result.

The previous reconstruction narrowed the basename pointer to `char`, lost both
ECX tests into uninitialized locals, lost the stream used for the blank line,
and lost the error function name. The repair uses the full existing 32-bit
printf argument representation and explicit stream/mode values. It neither
adds header output to append opens nor changes the filename pattern.

The fourth existing argument was the EBP value forwarded into the recovered
I/O helper, not ECX. It remains a separate `allocContext` argument. A required
fifth integer carries `reopenOldFile`; reusing the fourth argument as that flag
would misinterpret unrelated caller state. The original listing gives 24 zero
ECX call sites, one explicit `1` in `Rules_ConstructCodeFileClose`, and one
forwarded stack argument in `Rules_ConstructCodeFileOpen`. All are explicit in
the new source. No default argument conceals missing callers.

The source test checks every call against its original caller procedure. For
the module-table caller the zero ECX passes through the preceding formatted
write. The original `sub_476301`/`sub_488DF2` path preserves that register;
`sprintf_`/`vsprintf_` and `sub_475CC8`/`sub_475C84` likewise preserve the ECX
needed inside this opener. The printf wrapper preserves EDX, which carries the
opened stream to the second output call.

## Changes and boundaries

One function body is recovered, and 14 caller bodies gain the explicit mode
argument. The manifest keeps all 4,157 identities and historical hashes; only
those 15 current body hashes change. The canonical declaration and generated
CLIPS API header are updated together. No warning, link, header or coverage
baseline changes.

The existing 84-byte reconstructed filename buffer is retained. The original
reserves 80 local bytes; this batch does not resolve that pre-existing extent
difference or add speculative length/error policy. Tests use names fitting
both extents. The original unbounded formatter is not made generally safe for
arbitrarily long basenames.

The runtime still transports some pointers through 32-bit integers. The
basename tests deliberately use low-address storage and cover every possible
low byte, including zero and values that formerly sign-extended. This is not
support for arbitrary high 64-bit basename pointers. The failure regression
checks the error helper's arguments and low-32-bit buffer identity, not its
existing internally broken rendering or a dereference of a truncated 64-bit
stack pointer. That helper and the surrounding construct-file open/close
wrappers retain independent decompiler debt.

## Differential test

[The focused regression](../tests/tools/test_construct_code_file.py) extracts
the actual production body and reassembles the protected original procedure
into a freestanding 32-bit ELF. Only listing syntax is normalized (hexadecimal
literals, `short`, `retn` and the local offset); no original branch is rewritten.
The original instruction sequence is hash-pinned. This is execution of the
reassembled listing, not retail PE-byte execution and not a Wine game replay.

Both sides use controlled formatting, open, output and error hooks. The hooks
record call order, filenames, append modes, context, output stream/text, error
arguments and returns. They do not certify the recovered implementations of
those dependencies. Hook return values intentionally differ from stream handles.

There are 3,072 cases: all 256 basename-address low bytes, six signed mode values
(including zero, negative values and integer limits), and open success/failure.
Names include empty, dotted, relative-path and space-containing basenames;
file IDs and versions include negative values and integer limits. The compared
trace is 269,594 bytes with SHA-256:

```
b7944e6d4936f058ccc0f5b8dfbc422bc09496efdb5a64704ef3ece6787a4121
```

The test requires the original 32-bit execution to reproduce that trace hash,
then checks GCC/Clang O0/O2, 32/64-bit and signed/unsigned-char production
profiles with undefined-behavior traps. Three negative mutations independently
reintroduce basename truncation, inverted mode selection and wrong output
streams and must be detected.

```sh
python3 -m unittest discover -s tests/tools -p test_construct_code_file.py -v
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
python3 -m unittest discover -s tests/tools -p 'test_*.py' -v
git diff --check
```

Local validation used GCC 14.2 and Clang 17: eight 64-bit compiler profiles,
the negative mutations and both source checks pass. The local kernel rejects
32-bit ELF execution, so the original-execution test and eight 32-bit production
profiles explicitly skip locally. On GitHub Actions those execution failures
are errors, not skips. No retail assets are required by this test.

The exact patch was then validated in the isolated preparation run
[34056545731](https://github.com/lisu188/clash-disassembly/actions/runs/34056545731).
All seven focused tests pass without skips, including the original 32-bit
instruction execution and all 16 supported GCC 13/Clang 18 production profiles.
The split-source and generated-header audits also pass. The ten published
Git blobs match the local patch exactly. The diagnostic workflow and compressed
transport files are not included in the implementation tree.

The first normal PR run
[34056654565](https://github.com/lisu188/clash-disassembly/actions/runs/34056654565)
passes all 204 tooling tests. Its Markdown checker misclassified the filename
format as a repository path; this documentation-only follow-up distinguishes
that pattern without changing the checker. Build/coverage results and the
remaining link/header failures must be read from the final PR run; no runtime
or campaign result follows from these tests.

## Close-wrapper follow-up, 2026-09-07

Base: `5f30061`. The next bounded repair is
`Rules_ConstructCodeFileClose` at `0x004A7920`. Its signature and all callers
remain unchanged. The protected assembly identifies the stream in ESI:
`fclose_` receives ESI both when temporarily closing a partial array and after
writing the closing array delimiter. The previous reconstruction instead
passed the metadata pointer on the first path and an undefined local on the
second. Both calls now receive `curFile`. The formatter no longer reads an
uninitialized, unnecessary variadic argument, and the two system-error calls
receive the original `CONSCOMP` module name rather than metadata addresses.
Only this function's current manifest body hash changes; all 4,157 identities,
historical hashes, declarations, packed records and acceptance baselines remain.

| Original condition | Preserved behavior |
| --- | --- |
| Count below the signed limit, no reopen flag pointer | Return the supplied stream unchanged, without I/O |
| Count below limit, reopen flag present | Set reopen flag to one, close the supplied stream, return zero |
| Count at or above limit | Clear a supplied reopen flag before further work |
| No stream, missing reopen metadata or flag | Report `CONSCOMP` error 3, invoke router exit with status 2 |
| Reopen metadata has no basename | Return zero without resetting count or incrementing array version |
| Reopen required | Use metadata basename/file ID/version, the existing array-version context, and append mode 1 |
| Reopen fails | Report `CONSCOMP` error 4, invoke router exit with status 2 |
| Finalize array | Write its delimiter to the live stream, close that same stream, reset count, increment the current unsigned version |

[The close-wrapper regression](../tests/tools/test_construct_code_file_close.py)
extracts the actual production body and reassembles the hash-pinned original
procedure. Its 2,656 bounded returning cases cover signed limits, equality,
null/non-null metadata and flag pointers, missing basenames, open failures,
zero/nonzero stream tokens, unsigned version wraparound, and dependency hooks
that modify counters during output/close. Four separate process runs exercise
terminating error callbacks. Seven mutations must detect wrong close handles,
wrong module names, threshold equality errors, non-append reopening, incorrect
version increments and incorrect reopen flags. Guard words and metadata remain
checked. The returning trace is 146,850 bytes with SHA-256:

```
2b36d1ded43d1413e5a9586ec8d2dd29d0931c6e6eb7d89d60c148e1d82f401d
```

The expected trace is generated by an explicit branch/state model. Independent
original-listing execution must reproduce it; the expected hash alone does not
establish equivalence. The compiler matrix compares full trace bytes rather
than just the digest: GCC/Clang, O0/O2, 32/64-bit, signed/unsigned-char, with
undefined-behavior traps. Local GCC 14/Clang 17 pass all eight 64-bit profiles,
source checks and mutations. Nine 32-bit test/profile executions skip locally
because this kernel rejects 32-bit ELF. On GitHub Actions they must execute;
a kernel execution error there is a failure, not a skip.

```sh
python3 -m unittest discover -s tests/tools -p test_construct_code_file_close.py -v
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
git diff --check
```

This is a controlled-dependency contract test, not validation of real file
streams, router internals, retail PE execution, or the complete construct
compiler. Deliberately returning exit hooks preserve the original fall-through
on valid metadata; null metadata with a returning exit hook remains an invalid
path and is not silently made successful. The original close-on-null behavior
is retained where reached, not declared safe for real I/O. All metadata pointers
in the fixture use low-address storage. High 64-bit pointer transport and the
neighboring open-array wrapper remain separate recovery work. No mission-05,
full-gameplay or visual milestone advances.
