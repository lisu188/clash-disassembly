# DLX cached-entry readability fixture

This asset-free fixture executes the actual `DLXSprite_LoadCachedEntry` definition
extracted from the current canonical source and the frozen pre-migration
definition from commit `5376757fe8cefd1af5eab0907601fab3ab9bc121`. The latter is
stored verbatim as `baseline.cpp`; `provenance.json` pins its bytes and body-token
hash. It is a compatibility-baseline oracle, not a new original-game oracle.

The independent contract comes from original `sub_4060E0` at `0x004060E0`,
`clash95.asm:9229..9361`, plus its retained canonical query/allocation adapters:

- the payload handle is cleared at `+10` before opening the file;
- start/next directory DWORDs describe the serialized entry extent; a zero next
  offset selects the stream-size fallback;
- the serialized extent is stored at `+14` before seeking and reading the
  ten-byte header;
- payload size is unsigned 32-bit serialized size minus ten, then assigned to
  the existing signed `int` local;
- allocation precedes storing its truncated low32 handle and testing failure;
- the payload read precedes query release and the return of the sprite handle;
- the ownership DWORD at `+18` and all unrelated bytes remain untouched.

Each callback records its arguments and a full 96-byte canaried sprite arena
snapshot. Both variants must have identical traces, final sprite arena, payload
bytes and directory backing. Independent assertions additionally check operation
order, read extents, query/handle identity, field widths, ownership and canaries;
the assertions are not a second implementation of the whole loader. Two negative
controls prove that changing ownership or caching the size before the header
callback fails the contract.

There are 18 scenarios, each run with aligned and deliberately unaligned sprite
storage under GCC 13 and Clang 18 at O0/O2: next-offset and EOF paths, null query,
signed index `-1` within padded backing, index `1023`, zero-length payload,
unsigned underflow/high-bit/all-ones sizes, mutations during EOF/seek/header/
allocation/payload callbacks, returning and terminal quit hooks, and truncating
64-bit allocator returns including a zero low32 result. A non-PIE executable
keeps the fixture objects in the signed-low32 address range.
The tests prefer those versioned compilers, fall back to the available compiler
of the same family, and skip a missing compiler family, following the existing
asset-free tooling tests. Acceptance evidence names the actual compiler versions.

Run from the repository root in Linux/WSL:

```sh
python3 -m unittest discover -s tests/tools -p test_dlx_cached_entry.py -v
```

## Limits and retained original differences

This fixture does **not** execute original x86 instructions. The original
instruction listing supplies the successful nonmutating-path layout/order
contract; callback mutations and compatibility failures instead pin the frozen
canonical implementation deliberately:

- the original dereferences the resolved query without the canonical null guard;
- the original rereads the directory start after the stream-size callback and
  for seek, whereas the canonical function caches it;
- the original final payload read reloads `+14` and `+10`, whereas the canonical
  function uses its cached payload size/handle;
- the original failure path reloads size for its varargs log/quit calls and
  additionally invokes `sub_472558(10)`, listed as noreturn. The canonical
  returning-quit continuation is tested as existing compatibility behavior.

These differences are not repaired by a view migration. The canonical loader
does freshly read serialized size **after** the header callback, and the fixture
specifically protects that read without incorrectly requiring original reloads
later in the function. The allocator's second argument `4` and the unrelated
`10` debug-log argument also remain unchanged.

Huge/negative sizes and the synthetic returning allocation-failure hook are
argument-trace probes: the inert read boundary never dereferences their null or
oversized payload range. They establish arithmetic/call behavior, not acceptance
of malformed assets, allocator success, actual filesystem behavior or bounds
safety. Padded signed-index cases do not introduce a new indexing policy.
No image/render fidelity or campaign milestone is claimed.
