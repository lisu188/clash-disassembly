# Runtime wrapper status

This file classifies the current runtime/quarantine surface for executable regeneration.

## Status classes

- `forwarding_wrapper`: low-risk adapter around host libc or already-isolated compatibility behavior
- `behavioral_stub`: placeholder behavior that keeps the code moving but does not yet prove original semantics
- `recovered_impl`: good-enough recovered implementation rooted in code evidence
- `unknown_runtime`: still needs tighter binary corroboration before it should move out of quarantine

## Current classification

| Symbol or family | Status | Evidence | Notes |
|---|---|---|---|
| `Compat_WcppCtorArrayStorage1m` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.c` callers | Already isolated behind a named compatibility helper rather than pretending to be the original runtime entry. |
| `Compat_WcppCtorArrayStorage1s` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.c` callers | Same family as above; safe to keep quarantined until the deeper WCpp startup band is re-emitted. |
| `CRT_GetBootstrapThreadData` | `behavioral_stub` | `compat/decomp_runtime_stubs.c`, `bootstrap_main.c`, `clash95.c` weak accessor | Good enough for the bootstrap wedge, not yet a faithful final CRT thread-data recovery. |
| `CRT_RegisterFinalizableObject` | `behavioral_stub` | `compat/decomp_runtime_stubs.c`, broad `clash95.c` call surface | Used widely enough that it needs a documented quarantine label rather than a semantic upgrade. |
| `fread_` / `fwrite_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c` | Host libc forwarding wrappers around the current file-handle translation layer. |
| filesystem/string CRT wrappers (`strcmp`, `strlen`, `strrchr`, etc.) | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, unresolved audit | Broad but understandable compatibility wrappers; still not proof of original runtime structure. |
| `Render_LoadResourceSprite_v4` compat export | `recovered_impl` | `compat/decomp_runtime_stubs.c`, `clash95.asm:18215-18324`, live contained row-draw probes | Now matches the cache-query gate, companion `.pfn` palette load, and recolor contract closely enough to carry the authentic load-menu row-resource lane. |
| `Render_LoadResourceSprite_v3` compat export | `recovered_impl` | `compat/decomp_runtime_stubs.c`, `clash95.asm:17529-17576`, gdb SIGINT in contained row draw | The missing non-newline cursor advance was restored from asm, removing the row-draw hang. |
| `CreateProcessA` / `CreateThread` / `WaitForSingleObject` family | `unknown_runtime` | unresolved audit, `clash95.c` thread/process call sites | These are deeper runtime/process helpers and should not be silently normalized into the SDL seam. |
| `_wcpp_4_static_init__` / `_wcpp_4_copy_array__` | `unknown_runtime` | raw link failures, `clash95.map`, `clash95.c` | Still part of the true startup/runtime reconstruction frontier. |
| `JUMPOUT` sites | `unknown_runtime` | `clash95.c` control-flow scars | These remain explicit recovery blockers, not wrappers. |

## What moved this batch

- The wrapper surface is now explicit in the executable-regeneration docs.
- The first C++ executable target is being built around the current bootstrap wedge instead of pretending the deeper WCpp/runtime layer is already solved.
- The text-resource/runtime quarantine layer now carries enough recovered behavior to get through the authentic load-menu row-resource preload and the first contained row-draw pass.
- The contained load-menu wedge now also reaches the authentic slot-strip click plus bottom-row load confirm proof with `selected_slot = 0` and `confirm = 1`.
- The next blocker is no longer the click/confirm proof or the first `sub_444490` save-load crash; the contained post-confirm lane now reaches `load-menu-post-confirm-after-save` and returns to `main-after-menu-probe`.
- The fixes that moved this batch were recovered-C repairs, not new quarantine shims:
  - `sub_4163F0` now matches the asm-backed finite loop
  - `sub_4443C0` / `sub_4443D0` now take real `char *` buffers instead of truncated low32 stack addresses

## What should not move yet

- `_wcpp_*` startup helpers
- thread/process runtime helpers
- control-flow scars
- the parser/output/runtime helpers newly exposed by a direct `sub_444490` pull (`Lexer_OutputFieldRange`, `IO_OutWriteToken`, `IO_OutNewline`, `Module_AllocList`, `strtod_`, `unknown_libname_2`)
- any helper whose only current proof is “the code links if we stub it”
