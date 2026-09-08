# Illegal logical-name reporter recovery

Track: Win95 reconstruction. Base `abed998`. The helper at `0x0049F310`
now carries the function-name value that the original receives in EAX,
instead of consuming three undefined decompiler temporaries.

The protected procedure saves ECX/EDX/EBX, copies incoming EAX to ECX,
emits `IOFUN` error 1, then writes `Illegal logical name used for `, the
retained function name, and ` function.\n`. It reloads `werror` before
each output. The final `Output_Write` result remains the function result.
This matches the documented CLIPS IOFUN1 message shape, but the binary
instruction sequence remains the behavioral authority.

Six original callers load a literal function name into EAX immediately
before the call: `printout`, `read`, `open`, `close`, `format`, and
`readline`. The recovered declaration now takes one integer pointer token,
and those six callers pass their exact recovered string addresses through
the existing 32-bit transport. This batch does not widen that transport.

Seven current function-body hashes change: the reporter and six callers.
All 4,157 identities and historical hashes remain, with no warning/link/
header/coverage baseline update.

`tests/tools/test_illegal_logical_name.py` pins the original 21-instruction
body (normalized SHA-256
`2acf6730a476c7155cf18a5e527b669b17e9a6a028f9c2b8b7ac19f26bb7ccee`),
verifies all six original caller constants, inspects the production callers,
and executes the actual repaired body across GCC/Clang O0/O2 and
signed/unsigned-char profiles. The runtime fixture mutates `werror`
between writes, checks all retained contexts and the final return, and
rejects three independently reintroduced defects.

```sh
python3 -m unittest discover -s tests/tools -p test_illegal_logical_name.py -v
python3 tools/audit_split_sources.py
python3 tools/gen_subsystem_headers.py --check
python3 tools/gen_subsystem_headers.py --check-tu-includes
git diff --check
```

This is an asset-free bounded contract. It does not prove arbitrary
high-64-bit pointer support, router implementations, retail PE execution,
or campaign behavior. Mission 05 remains at the first-Road checkpoint.
