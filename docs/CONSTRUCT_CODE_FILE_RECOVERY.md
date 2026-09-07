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

## Array-open wrapper follow-up, 2026-09-07

Track: Win95 reconstruction. Base `f12a97c`. The bounded follow-up at
`0x004A79F0`, `Rules_ConstructCodeFileOpen`, restores complete structure-name
pointers, the original 12-byte descriptor layout, output arguments and stable
stream returns. It is not a retail construct-compiler or gameplay validation.

### Interface and memory evidence

The original procedure receives a structure-name pointer through stack argument
`arg_C`. All 34 original callers supply full string addresses. The recovered
`char` parameter and caller-side pointer-to-char casts discarded that evidence.
The parameter is now `const char *`, and only the corresponding argument changes
at those 34 call sites. The canonical declaration and generated API agree.
The 15 existing exploratory test calls retain their identities and assertions,
using string arguments and packed descriptor initialization for the corrected
interface instead of character literals and native-pointer-stride arrays.

Original descriptor accesses are at offsets zero, four and eight. Fresh opens
store version, filename address and file identifier, in that order, before the
existing-stream test. Reopens read these three original-width fields even on a
64-bit host. The legacy `const char **` public parameter remains to avoid a wider
caller-storage rewrite; it represents opaque 12-byte storage here, not a native
pointer array. Byte copies preserve these exact widths without aliasing through
incompatible typed lvalues. No public structure or data-table size changes.

Existing streams receive only the comma/newline separator and return the same
stream. Failed opens return zero without incrementing the file count. Successful
reopens receive only the separator. Fresh opens increment the live count, format
the array name, write the definition to the opened stream and the declaration
to `headerFP`, then return the opened stream independently of formatting results.
The increment explicitly reproduces 32-bit wraparound, including `INT_MAX`.
Error 5 receives `CONSCOMP` before the original exit callback. A callback returning
with null metadata remains an invalid path; no guessed recovery is added.

Only 22 current recovered body hashes change (the wrapper and its 21 caller
functions). All 4,157 identities, historical hashes and warning/link/header/
coverage baselines remain unchanged. No campaign fixture is promoted.

### Executable checks and limitations

[The new regression](../tests/tools/test_construct_code_file_open.py) executes
2,032 returning cases and two terminating-error cases against the extracted
production body and a hash-pinned reassembly of the original listing. The
matrix includes all 256 structure-pointer low bytes, six signed reopen modes,
existing/missing streams, successful/failed opens, absent/present descriptors,
count wraparound, and observable dependency mutations. Guard words after the
12-byte descriptor detect accidental native-pointer-width stores. Dependency
mutations check live count reads, descriptor persistence, second-output string
reads and independence from helper return values. Nine negative mutations
reintroduce wrong streams, offsets, pointer narrowing, mode, count and errors.

The 198,674-byte expected returning trace is frozen with SHA-256:

```
2e9ccce3f5ab3a53589e8472775dfebca87aed71ef73924d3d7c788f1a9a93ff
```

The original assembly is not changed. Its reassembly only translates listing
syntax and explicitly spells the DWORD operand size already given by the
original stack-argument declaration. GNU assembler's
[Intel syntax documentation](https://sourceware.org/binutils/docs/as/i386_002dVariations.html)
is secondary syntax guidance, not the behavioral authority.

Tests exercise GCC/Clang O0/O2, 32/64-bit and signed/unsigned-char builds, with
undefined-behavior traps. Local GCC 14.2/Clang 17 64-bit profiles pass; this
container cannot execute 32-bit ELF, so those profiles and the original oracle
are explicitly skipped locally. On GitHub Actions these cases must execute or
fail rather than skip. Full supported-compiler and original-instruction results
must come from the retained Actions run, not the local result.

The output seam still transports arguments as 32-bit words. On a 64-bit host,
the tests validate the low-32-bit identity of the stack-resident array-name
buffer and the actual text captured by the formatting hook, without
pretending that an arbitrary truncated stack pointer can be dereferenced by
the real output dependency. General high-pointer support, unbounded long-name
formatting, real filesystem I/O and dependency correctness remain separate work.
The error callback is tested for terminating null-metadata inputs only.

```sh
python3 -m unittest discover -s tests/tools -p test_construct_code_file_open.py -v
python3 -m unittest discover -s tests/tools -p 'test_construct_code_file*.py' -v
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
python3 tests/check_markdown_links.py
git diff --check
```

No mission-05 bridge continuation, valid arrival save, tactical or visual
milestone is established by this recovery.

## Error-reporting follow-up, 2026-09-07

Track: Win95 reconstruction; base `7745ab1`. This batch recovers the two error
reporters reached by the construct-file wrappers, without changing their API,
callers, message data or lower-level router implementations.

`Rules_OpenFileErrorMessage` (`0x004818C0`) now retains the function-name argument
across error-prefix output and writes that name rather than an undefined local.
`Rules_ReportSystemError` (`0x00485C80`) similarly retains the module argument
and sends the signed numeric error ID to the current error logical name, rather
than an undefined destination. Both helpers preserve the final output result,
message order, newlines and a fresh read of the error logical name before each
output. The unused register-derived output context is now a defined value.

The original procedures save incoming EAX in ECX and the second argument in ESI.
Their callees preserve ECX: `sub_4859A0`, `sub_485770` and `Output_Write` save and
restore it. The retained identifier is therefore the original parameter, not
an inferred initializer. Only these two recovered bodies and their current
manifest hashes change. All 4,157 identities, historical hashes, declarations,
shared data and warning/link/header/coverage baselines remain untouched.

### Composed message regression

[The new regression](../tests/tools/test_construct_error_reporting.py) extracts
both repaired bodies and the unchanged `Rules_PrintErrorID` and
`Rules_PrintLongInteger` implementations. It uses the actual message constants
from recovered state. An independent executable reassembles all four original
procedures, each hash-pinned to the protected listing; it does not substitute a
handwritten prefix or number helper for the original instructions. Only the
final output sink and decimal formatter are controlled dependencies. Message
text, write boundaries, logical-name routing, formatting calls and final returns
are compared with explicit expected transcripts.

The 4,608 scenarios cover both reporters, every identifier-address low byte,
every filename-address low byte, signed error-number boundaries, empty and
percent-containing names, three output-result schedules, and three callback
modes. The callback modes leave state unchanged, switch the error destination
after each write, or mutate the identifier/filename text during prefix output.
These cases reject cached destinations or prematurely copied input text, and
check that failed output results do not silently short-circuit later writes.
Null strings and inaccessible/high 64-bit pointers are not valid test inputs.

The complete expected trace is 1,165,323 bytes with SHA-256:

```
10441056a6f01f73150715715e4fa6b5a97a6ba795917ac9bbc6a299fe7b082e
```

Seven test methods cover the pinned original procedures, actual constants,
manifest-backed body identities, scenario matrix, composed original execution,
all production profiles, and eight independently rejected mutations. Mutations
reintroduce wrong identifiers, wrong filenames, wrong integer destinations,
pointer narrowing, missing output, an incorrect return value or a cached route.
The native matrix is GCC/Clang, O0/O2, 32/64-bit and signed/unsigned plain char,
with warnings as errors and undefined-behavior traps on production fixtures.

```sh
python3 -m unittest discover -s tests/tools -p test_construct_error_reporting.py -v
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
git diff --check
```

Local validation passes all seven methods, including eight 64-bit profiles and
the mutation checks, with nine explicit skips for the original and eight
production 32-bit executions unsupported by this kernel. GCC 14.2 and Clang 17
are the available local compilers. CI must execute the original and all 16
supported-compiler profiles; an execution failure there is an error, not a skip.
The initial local harness needed a freestanding memcpy implementation for Clang
and a corrected unused-parameter mutation fixture. Those failed attempts are
retained; neither required weakening recovered-code checks. Local source and
generated-header audits pass.

### Remaining boundaries

This proves bounded message construction to a controlled sink, not full router
correctness, real file-error handling or a retail executable replay. Existing
integer pointer arguments still require valid low-address input storage on a
64-bit host; in particular this does not repair a truncated high-stack filename
passed by an upstream caller. Other callers may still pass lost or incorrect
identifiers. The existing static numeric buffer and its concurrency/reentrancy
limitations are unchanged. No image, filesystem, native crash-count or campaign
milestone is promoted. Mission-05 turn refresh and Road continuation remain the
active gameplay frontier.
