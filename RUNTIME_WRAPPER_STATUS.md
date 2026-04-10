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
| `unknown_libname_4` | `recovered_impl` | `clash95.asm` use under `sub_47CBF0`, `clash95.c` | Recovered as the allocator-failure callback swap used by the binary-loader retry helper. |
| `unknown_libname_7` / `unknown_libname_8` | `recovered_impl` | `clash95.exe` objdump at `0x47E7B0` / `0x48AC80`, `clash95.map`, `clash95.c` | Exact setter-swaps for `dword_51A1EC` / `dword_51A928`; these are runtime helpers, not startup `.fn_init` bodies. |
| `AST_FreeNode` | `recovered_impl` | `clash95.asm:303859`, `clash95.c` | Exact recursive free-list unwind recovered in-tree; no longer a retained startup blocker. |
| `mblen_` / `mblen__0` / `sub_4D88F0` | `recovered_impl` | `clash95.exe` objdump, `clash95.c` callers | Narrow object-pattern trampolines and token-table registration slice recovered directly from the binary. |
| `sub_496643` | `recovered_impl` | `clash95.exe` objdump at `0x496643`, `clash95.map`, `compat/decomp_runtime_stubs.c` | Kept quarantined in the compat seam, but the signal-table update and ctrl-handler gating now match the original helper closely enough to remove it from the retained startup-prelude blocker list. |
| `ftime_` / `system_` | `forwarding_wrapper` | `clash95.exe` objdump at `0x47D360` / `0x47D3D0`, `clash95.c`, `compat/decomp_runtime_stubs.c` | The callsites are now reconstructed with the correct arguments; the host-backed implementations remain deliberately quarantined as CRT wrappers. |
| `fread_` / `fwrite_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c` | Host libc forwarding wrappers around the current file-handle translation layer. |
| `MoveFileA` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.c:130558`, retained `sub_451E46` probe | Narrow host wrapper over translated WSL paths plus `rename()`; intentionally quarantined as compatibility glue rather than gameplay semantics. |
| `sscanf_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.asm` callsites at `0x459272`, `0x4720F8`, `0x4A5657` | Host `vsscanf` bridge matching the currently reached text-parse callsites. |
| `fgets_` | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, `clash95.asm` callsites at `0x459265`, `0x4A50A0`, `0x4A545A` | Narrow registered-stream line reader; the active recovered callsites now pass the real buffer/size/stream arguments. |
| `unknown_libname_2` | `recovered_impl` | `clash95.exe`/asm at `0x48523F`, `compat/decomp_runtime_stubs.c`, `clash95.c` callsites | Exact signed decimal parser recovered from the binary; no longer an `atoi` placeholder. |
| filesystem/string CRT wrappers (`strcmp`, `strlen`, `strrchr`, etc.) | `forwarding_wrapper` | `compat/decomp_runtime_stubs.c`, unresolved audit | Broad but understandable compatibility wrappers; still not proof of original runtime structure. |
| `Render_LoadResourceSprite_v4` compat export | `recovered_impl` | `compat/decomp_runtime_stubs.c`, `clash95.asm:18215-18324`, live contained row-draw probes | Now matches the cache-query gate, companion `.pfn` palette load, and recolor contract closely enough to carry the authentic load-menu row-resource lane. |
| `Render_LoadResourceSprite_v3` compat export | `recovered_impl` | `compat/decomp_runtime_stubs.c`, `clash95.asm:17529-17576`, gdb SIGINT in contained row draw | The missing non-newline cursor advance was restored from asm, removing the row-draw hang. |
| `CSyncObject_Unlock` | `recovered_impl` | `src_cpp/csync_object.cpp`, `clash95.c` retained probes | Published through the conservative C++ seam as the original lock ABI rather than a new compat stub. |
| `CreateProcessA` / `CreateThread` / `WaitForSingleObject` family | `unknown_runtime` | unresolved audit, `clash95.c` thread/process call sites | These are deeper runtime/process helpers and should not be silently normalized into the SDL seam. |
| `_wcpp_4_static_init__` / `_wcpp_4_copy_array__` | `unknown_runtime` | raw link failures, `clash95.map`, `clash95.c` | Still part of the true startup/runtime reconstruction frontier. |
| `JUMPOUT` sites | `unknown_runtime` | `clash95.c` control-flow scars | These remain explicit recovery blockers, not wrappers. |

## What moved this batch

- The wrapper surface is now explicit in the executable-regeneration docs.
- The first C++ executable target is being built around the current bootstrap wedge instead of pretending the deeper WCpp/runtime layer is already solved.
- The text-resource/runtime quarantine layer still carries the contained pre-confirm load-menu wedge cleanly through row-resource load, row draws, slot-strip selection, and bottom-row confirm.
- The latest guarded traces show the next blocker is still below the quarantine seam:
  - with the current broader-rules bootstrap, the post-confirm save replay reaches `parse-make-instance-before-class-lookup` and then dies because `sub_4B0480` reports `class-lookup-no-table name=oddzial`
  - with `CLASH95_LOAD_MENU_PROBE_BROADER_RULES=0`, it dies earlier on `symbol-lookup-missing-table MAIN`
  - the live evidence still points at missing startup-prelude class/bload recovery, not an SDL or wrapper seam change
- The retained executable-regeneration surface was also reduced without changing wrapper policy:
  - the exact retained data/helper slice `aJ_0`, `unknown_libname_13`, `ismbdprint_`, `sub_4B6DD0`, and `sub_4BDD40` now exists in recovered C
  - the exported parser names `Lexer_ParseSlotConstraint`, `Lexer_ParseFieldSpec`, `Lexer_ValidateMessageHandler`, `Lexer_ParseDefglobal`, `Lexer_ParseRuleRHS`, and `Lexer_ParseDeclareOptions` are now rebound onto their already-recovered bodies
  - the remaining slot/parser exports `Lexer_EmitSlotBinding`, `Lexer_BuildSlotNode`, and `Lexer_FindSymbolIndex` are now also rebound onto their already-recovered bodies
  - the low-risk file/runtime wrapper band (`unknown_libname_2`, `MoveFileA`, `sscanf_`, `fgets_`) is now settled enough that it no longer appears on the retained `sub_451E46` unresolved list
  - retained `sub_4996D0` still links cleanly
  - the broader retained `sub_451E46` slice is now exposed honestly as the remaining x87-heavy math/runtime problem rather than a runtime-wrapper or parser-export problem

## What should not move yet

- `_wcpp_*` startup helpers
- thread/process runtime helpers
- control-flow scars
- the parser/output/runtime helpers newly exposed by a direct `sub_444490` pull (`Lexer_OutputFieldRange`, `IO_OutWriteToken`, `IO_OutNewline`, `Module_AllocList`, `strtod_`)
- any helper whose only current proof is “the code links if we stub it”
