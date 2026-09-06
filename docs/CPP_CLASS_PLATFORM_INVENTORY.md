# Application and SDL support ownership inventory

Date: 2026-09-06. Track: Win95 reconstruction. Frontier: the requested class migration's application/SDL stage. This is a read-only architecture and boundary audit; no implementation, build, route, visual or recovery milestone advances.

## The 4,157-identity registry does not cover the full requested scope

The four production support translation units contain **457 definitions with zero name overlaps** with data/recovered_sources.json. Three additional inline definitions live in the reviewed support headers. The current 4,157-identity registry therefore cannot establish completion of Application/SDL migration, even after all its intended game methods move.

| Source | Lines | Definitions | Runtime class candidates | Diagnostic candidates | Procedural boundaries |
|---|---:|---:|---:|---:|---:|
| src/platform/platform_sdl_runtime.cpp | 3,602 | 185 | 140 | 10 | 35 |
| src/bootstrap/bootstrap_main.cpp | 1,443 | 30 | 10 | 15 | 5 |
| src/instrumentation/runtime_mission_trace.cpp | 552 | 15 | 0 | 14 | 1 |
| src/compatibility/decomp_runtime_stubs.cpp | 3,547 | 227 | 5 | 0 | 222 |
| **Translation-unit total** | **9,144** | **457** | **155** | **39** | **263** |
| platform_sdl.h / compatibility/defs.h | 584 / 213 | 1 / 2 | 0 | 0 | 3 |

Counts are source definitions from split_source_index.scan_definitions(text, None), not linked symbols, active preprocessor branches, historical addresses or newly proven original functions. They exclude declarations and macros. Some support code contains historical thunks or quarantined original helpers; absence from the manifest does not prove that all 457 bodies are newly invented support behavior.

The 155 runtime candidates are a concrete minimum for the application's and SDL layer's behavioral class ownership. The 39 diagnostic candidates have proposed separate owners below; the coordinator must either include them in the support migration or explicitly retain them as diagnostic infrastructure. They must not enter gameplay classes or disappear from the completion denominator.

CMakeLists.txt:76-86 creates three separate support object targets; :139-151 links them after the recovered object groups and compiles bootstrap_main.cpp directly into the executable. src/sources.cmake and the recovered identity manifest alone do not inventory these sources.

## SDL runtime: 150 proposed bodies and 35 retained boundaries

All source locations in this section refer to src/platform/platform_sdl_runtime.cpp. Candidate classes are behavioral views over the existing state/records, with real out-of-line methods. They are not claims about the original game's object model.

| Proposed owner | Count | Exact family / additional definitions | Evidence and boundary |
|---|---:|---|---|
| SdlDrawDevice | 24 | All 23 CompatDirectDraw_* definitions, plus DirectDrawCreate | :1090-1326, :3089. Existing CompatDirectDraw receiver owns display/cooperative-window settings and a reference count. Keep explicit create/release operations and original ABI thunks. |
| SdlDrawSurface | 42 | All 36 CompatDirectDrawSurface_* definitions; CompatSurfaceBytesPerPixel, CompatDirectDrawSurfaceEnsurePixels, CompatSurfaceReadPixelValue, CompatDirectDrawSurfaceFillRect, CompatDirectDrawSurfaceCopyRect, CompatDirectDrawSurfaceCreate | :262, :269, :425, :656, :729, :1065, :1410-1836. Borrow the current record, pixel allocation, owner, attachment, palette and clipping state. |
| SdlPalette | 10 | All seven CompatDirectDrawPalette_* definitions; CompatDirectDrawPaletteCreate, CompatPaletteIndexToArgb32, CompatPaletteIndexToRgb565 | :390, :411, :1047, :1334-1399. Preserve the 256-entry palette, flags, owner and AddRef/Release sequence. |
| SdlClipper | 9 | All CompatDirectDrawClipper_* definitions | :1844-1913. Borrow its HWND/reference count. Keep inert operations inert. |
| SdlPresenter | 4 | PlatformDac6Channel, PlatformConvertSurfacePixelsToArgb32, PlatformPresentDirectDrawSurface, Platform_PresentRecoveredIndexedSurfaceHandle | :297, :302, :531, :577. Final palette conversion, SDL surface blit/presentation and recovered indexed-surface interpretation. |
| SdlDibRenderer | 3 | PlatformConvertDibToArgb32, StretchBlt, StretchDIBits | :2027, :2906, :2929. DIB orientation/pitch/palette conversion and blits; do not fold these into recovered sprite semantics. |
| SdlDeviceContext | 15 | PlatformSurfaceIsWindowDeviceContext, PlatformSurfaceIsBuiltin, PlatformGetWindowFromHdc, PlatformEnsureWindowDeviceContext; GetDC, GetDeviceCaps, GetPixel, SetPixel, ReleaseDC, CreateCompatibleDC, DeleteDC, DeleteObject, GetObjectA, SelectObject, LoadImageA | :1983-2025, :2638-2674, :2821-2905, :2992. Preserve built-in surface identity and lazy window device-context allocation. |
| SdlHostWindow | 8 | PlatformEnsureSdlVideo, PlatformFindWindowByHostId, RegisterClassA, CreateWindowExA, GetClientRect, GetForegroundWindow, ShowWindow, ClientToScreen | :2149, :2165, :2513, :2522, :2610, :2737, :3009, :3313. Own SDL initialization/window coordination while borrowing the existing flags, WNDCLASSA and foreground pointer. |
| SdlMessageQueue | 10 | PlatformQueueIsEmpty, PlatformFillQuitMessage, PlatformQueuePush, PlatformQueuePeek, DispatchMessageA, GetMessageA, PeekMessageA, PostQuitMessage, UpdateWindow, WaitMessage | :2105-2147, :2581, :2742, :2797, :2815, :3286, :3299. Preserve capacity 32, head/tail, quit state, event-pump ordering and paint enqueue behavior. |
| SdlInput | 9 | PlatformMapSdlKeyToInputScan, PlatformSetKeyboardScan, PlatformHandleHostEvent, PlatformQueryX11PointerState, PlatformSyncPolledMouseState, PlatformPumpHostEvents, Platform_ResetInputFallbackState, Platform_ReadInputFallbackState, PlatformTraceHostClickPulses | :454, :2179-2509, :3328, :3495. Host events and polled/X11 input share live keyboard/mouse/pulse state; keep that order and unit conversion. |
| SdlClock | 5 | timeGetTime, GetTickCount, QueryPerformanceCounter, QueryPerformanceFrequency, Sleep | :3035-3072, :3307. Preserve current clock domains, truncation, frequency and sleep units; class migration is not a timer repair. |
| PlatformRuntimeSettings | 1 | PlatformReadNonNegativeIntEnv | :439. Shared presentation/input configuration parser; explicit utility owner avoids duplicating semantics between those classes. |
| PresentedFrameCapture (diagnostic) | 2 | PlatformMaybeDumpPresentedFrame, Platform_ResetPresentedFrameDump | :492, :525. Separate capture counters/configuration from game rendering. Preserve lazy getenv and reset-only-counter behavior. |
| PlatformInputScript (diagnostic) | 8 | Platform_ShouldSuppressPolledMouseSyncForScript; four Platform_DebugPrimeInputFallback* definitions; Platform_RunInputScriptStep, PlatformTraceInputScript, PlatformTraceInputScriptCommand | :462, :470, :1967, :3345-3493. Preserve command/read-count semantics and input ordering; this is route-driver infrastructure. |

These names supplement the three original identities already assigned to SdlPlatform: Platform_MainWindowProc, Platform_CreateMainWindow and Platform_PumpMessagesAndBlitFrame. Do not place all 185 bodies into that existing class merely because their physical file is shared. New class files should use src/platform/<Class>.hpp/.cpp and remain behind platform_sdl.h.

The **35 retained SDL definitions** are an exact partition of the remaining bodies:

- **14 ABI-only dispatch adapters**, :3112-3217: all Compat_DirectDraw_* and Compat_DirectDrawSurface_* definitions. They preserve low32 output slots and function-table calls; retain their exported callable identities after their target behavior moves.
- **Two low32 allocator adapters**, PlatformAllocLow32 and PlatformFreeLow32 (:244, :256). They preserve signed-32 address limits and forward to the compatibility allocator; they must not become new/delete or hidden lifetime work.
- **Two OS-error accessors**, GetLastError and SetLastError (:2628, :2633), retaining the existing process-global compatibility error slot.
- **Four stateless Win32 rectangle helpers**, SetRect, EqualRect, IsRectEmpty, IntersectRect (:2687-2735). These are import-contract utilities, not recovered world geometry.
- **Five compatibility token/version accessors**, GetStockObject, LoadCursorA, LoadIconA, GetVersion, GetModuleHandleA (:2769-2787, :3074-3087). Preserve the static token addresses and current reported version.
- **Two explicitly inert legacy-device imports**, DirectSoundCreate and DirectInputCreateA (:3218-3247). They deliberately fail rather than initializing legacy device slots. Their retention does not establish audio recovery.
- **Two diagnostic output imports**, MessageBoxA and OutputDebugStringA (:2789, :3274).
- **One drive-query import**, GetDriveTypeA (:3249), preserving its compatibility path/drive query behavior.
- **Three inert import-contract stubs**, DefWindowProcA, TranslateMessage and ValidateRect (:2572, :3280, :3292). UpdateWindow is not in this group: it enqueues a paint message.

The C-callable entry names of classed imports must also survive as adapters. The count above classifies current behavior definitions, not future adapter definitions.

## Application startup and diagnostic bootstrap

The ten runtime candidates extend the existing GameApplication owner, whose final files are src/core/GameApplication.hpp/.cpp. They are Bootstrap_BuildCommandLineFromArgv (:334), Bootstrap_ParseIntroMissionIndex (:357), Bootstrap_RunRecoveredStartupPrelude (:369), Bootstrap_RunRecoveredRuntimeAndRenderInit (:391), Bootstrap_RunRecoveredEarlyStartupPrelude (:438), Bootstrap_RunRecoveredGameEntry (:1304), App_WinMain (:1391), Bootstrap_ResetRecoveredParserAllocatorForDirectRoute (:192), Bootstrap_RunMessageLoop (:1415) and Bootstrap_RunPlatformWindowLoop (:1426). Locations here refer to src/bootstrap/bootstrap_main.cpp.

Keep alternate/unused startup helpers explicitly inventoried rather than deleting them during migration. Preserve the full mixed command-route bodies first; the direct-route branches are not campaign-menu completion.

The 15 separate BootstrapRouteProbes candidates are the two Bootstrap_Trace* helpers (:179, :184), the three Bootstrap_Get*Auto* selectors (:202-212), four Bootstrap_Should* selectors (:217-232), Bootstrap_GetMenuProbeWidgetClickCandidate (:259), Bootstrap_SurfaceRendererLoadGfx (:322), Bootstrap_SurfaceRendererDrawStage (:327), and the three Bootstrap_RunRecovered*Probe bodies (:468, :487, :856). A diagnostic owner belongs under src/bootstrap, not inside gameplay/menu classes. Stable no-op selectors retain their current results.

Retain five procedural boundaries: main (:1434), _no_support_loaded (:164), j___NTAddFileHandle_ (:169), Bootstrap_CrashBacktraceHandler (:238) and Bootstrap_InstallCrashBacktraceHandler (:249). main remains the process ABI adapter. The latter pair handles environment-gated OS signal registration/backtrace/_exit, with raw callback addresses and crash-path constraints; class migration must not introduce construction or destruction there.

Startup ordering is a behavioral contract:

1. main installs the optional crash handler, builds the bounded 1,024-byte command line, then invokes App_WinMain.
2. Early prelude stores that live command-line address, creates the real platform window, acquires mouse input, sets the audio window, initializes the root filesystem, detects/mounts assets, then calls Game_Init.
3. Runtime/render init explicitly calls Render_LoadResourceBackbuffer before pixel-format setup because the original static-init band remains incomplete. Device setup, timer frequency, parser reserve slab, logging, rules compilation, purge hooks, pixel format, cursor resources, glyph fallback, options and RNG seeding retain their exact order (:391-435).
4. Current audio quarantine sets g_CSS_InitializedFlag rather than calling the unresolved CSS_Init table. Do not silently remove that debt.
5. Game entry precedes App_Shutdown; the unsafe original cleanup callback noted at :1404 remains unresolved. Do not introduce RAII cleanup to fill that gap.

The boot command buffer, flags, render callback pointer and all borrowed recovered globals remain at their present storage anchors. Parser allocator reset is an explicit direct-route action, never a class constructor.

## Instrumentation ownership is distinct from game state

src/instrumentation/runtime_mission_trace.cpp has 15 definitions. Ten diagnostic RuntimeMissionSnapshot candidates comprise ReadU16, ReadI16, ReadI32, HashU32, CountOccupiedSlots, MinSlotActionPoints, CollectStacksForPlayer, CollectSnapshot, CollectSummary and SnapshotsMatch (:65-359). Four RuntimeMissionSampler candidates are ParseBoundedInt (:331), EmitSnapshot (:359), ResolveGameData (:447) and Thread (:457).

Keep RuntimeMissionTrace_Start (:532) as the constructor-section entry adapter. It checks an environment flag, starts a detached pthread, and can execute before main. Keep the raw pthread callback adapter, the public CollectSummary C API and the RUNTIME_MISSION_TRACE_DISABLE_CONSTRUCTOR test guard. A classed sampler must resolve live gameData each iteration; it cannot cache the initial pointer, synthesize an owning world or gain a destructor/join at shutdown.

The sampler's two volatile snapshots and fingerprint filtering are observational behavior, not proof of synchronized access or objective completion. Existing runtime_mission_trace_tests use a standalone byte image and disable the constructor (CMakeLists.txt:394-419). They are relevant existing tests, but do not prove the detached live thread's lifetime contract.

## Gameplay behavior hidden in compatibility stubs

Only five bodies in src/compatibility/decomp_runtime_stubs.cpp are clear additional runtime class candidates in this bounded pass:

| Function | Source line | Existing owner | Evidence |
|---|---:|---|---|
| Render_SetResourceHandle | 2874 | SurfaceRenderer | Reads/writes the low32 record's +0xCC resource handle and returns the previous value. |
| Compat_LoadFontPaletteTable | 2888 | GameText | Resource-path/cache lookup, fixed palette-byte conversion and query release support the actual text-sprite loader. |
| Render_LoadResourceSprite_v3 | 2952 | GameText | Borrows the active text slot, scans newlines, and accumulates glyph spacing/width from its cached sprite set. |
| Render_LoadResourceSprite_v4 | 2979 | GameText | Frees/clears a cached sprite set, computes a cache key, probes/loads a font sprite set, resolves a palette and renders text. Preserve all allocation/query/cache order. |
| Unit_GetSquadCount | 3087 | UnitStack | Reads ten 31-byte slots starting at stack +6 and stops at the first signed-short -1 sentinel. Preserve intptr_t receiver and packed alignment until separately proven. |

These five are absent from the 4,157 registry despite implementing game behavior. The existing GameText, SurfaceRenderer and UnitStack families must not be marked complete without assigning or explicitly reviewing them.

The remaining 222 definitions are procedural compatibility candidates, not 222 newly recovered game methods. Their rationale is bounded by actual mechanisms:

- Low32 mapping/arena/free-list management and pointer/readable-range probes (:123-174, :324-491, :1108-1365); preserve allocation address domain, headers, reuse order and diagnostics.
- File/path/find/stream translation, formatting and standard C wrappers (:686-1106, :1367-1810, :1928-2138, :2539-2731, :3144-3167, :3184-3547). Keep 32-bit stream slots, descriptors, CR/LF translation, text formatting and error mapping at the compatibility seam. Do not give them FileSystem ownership merely because they perform I/O.
- TLS, signal, event, critical-section, thread and Watcom construction/finalization/exception helpers (:142-322, :493-593, :1812-1926, :2158-2375, :2443-2537, :2740-2758, and the late _wcpp_/CRT wrappers). These are compiler/OS infrastructure or explicit quarantine, not game state.
- Seven CLIPS procedural forwarding aliases (:651-684): Module_AllocList, Lexer_OutputFieldRange, Lexer_CheckValueList, Lexer_FindTemplateSlot, IO_OutWriteToken, IO_OutNewline and Lexer_WarnImpliedTemplate. Preserve the game's call boundary into excluded CLIPS internals.
- Codec/AVI imports (:2377-2417), CAviDecompressor_ApplyDecoderFormatParams (:2733), ExcString_AsCharPtr (:2432) and CSyncObject_Unlock (:3176) are explicit approximation/quarantine bodies. Their names do not establish a complete decoder/string/locking contract.
- Collapsed Noop_* callbacks (:2762-2864) retain identity and current inert results. The source says returning zero is a link quarantine choice, not a recovered non-void result contract.
- Pure game forwarding adapters remain procedural: Render_DrawSprite (:2883), Render_LoadResourceSprite_v2 (:2947), Render_CreateSprite (:3056), four Compat_*RenderHook adapters (:3061-3081), and j_Mem_Alloc (:2510). Their target class ownership is already meaningful; extra forwarding classes would add no behavior.
- The opaque sub_473ED5 (:2520) participates in Watcom registration-list bookkeeping: the original thunk reaches sub_48703D, which invokes off_51A568 and __lock operations around dword_51A648 (clash95.asm:214981-214993). sub_485374 (:2532) returns lpTlsValue, matching clash95.asm:211545-211548. Keep these compiler-runtime boundaries procedural; do not infer game classes from their rendering callers.
- abs32 (:2427) is a generic compatibility arithmetic helper. Its INT_MIN signed-negation issue is a separate reached-contract question, not permission to substitute WorldGeometry behavior during inventory work.

This group audit is not an exact future 222-entry exclusion registry. Materializing support metadata must assign every exact function with rationale and evidence, and fail on new/unclassified definitions. No existing directory-wide wildcard is sufficient as a final exclusion policy.

## Storage, ABI and readiness constraints

- Four static compatibility vtables live at platform_sdl_runtime.cpp:959-1045 with 23/36/7/9 function slots. Keep those table addresses, field order and plain function-pointer ABIs. Do not overlay native C++ virtual classes or substitute member-function pointers.
- CompatDirectDraw, Surface, Palette and Clipper records (:189-242) are already explicitly described host/low32 bridge records. Behavioral classes should borrow them. Create/Release remain explicit methods, not constructors/destructors or smart-pointer ownership inferred from their names.
- Surface Release (:1427) releases the attachment, pixels, palette, primary-surface link, self and owner in a specific order. SetPalette (:1794) increments the incoming palette before releasing the old one, stores it, then may present immediately.
- **Readiness blockers:** CompatDirectDraw_Release (:1107) calls PlatformFreeLow32(self) before reading self->ref_count for its return; CompatDirectDrawSurface_Unlock (:1809) evaluates self->owner before the later self guard. These are observed source-order hazards requiring caller/allocator contract evidence or separate recovery. This audit neither proves reachability nor fixes them.
- Presentation conversion precedes frame capture, SDL_UpdateWindowSurface and temporary-buffer release (:531-575). Current DAC conversion evidence is attached to the code (:284-295); class migration must preserve its bytes and timing.
- Platform_ReadInputFallbackState (:3495) pumps host events, then steps the script, then consumes pulse counters/deltas. Preserve polled/X11 suppression and host-pixel conversion. Reordering produces different route input.
- Globals at :77-95 and :1930-1965 hold built-in object addresses, frame state, window class, queue, initialization flags, keyboard/mouse state and the script FILE*. Borrow them without new lifetime work or eager initialization.
- Platform_ShouldSuppressPolledMouseSyncForScript has two local statics, checked/enabled (:1969-1970). Keep their lazy one-time read and storage anchor. Frame-dump settings use separate lazy globals; resetting captures does not reset settings.
- Compatibility has local statics CompatPageSize::page_size (:409) and ExcString_AsCharPtr::kCompatEmptyString (:2434), plus allocator/handle/range/signal tables. Preserve local/global symbol identity and initialization.
- platform_sdl.h:419 defines NtCurrentTeb with compiler-specific fake_teb asm labels. This is one header definition and potentially multiple TU-local storage instances, not a singleton class opportunity. compatibility/defs.h:204 and :208 contain two inline ExcString constructor stubs; retain as explicit compiler compatibility.
- Clang places __ES__, __DS__, unk_51A638 and g_Audio_DriverModuleTableBase at the end of decomp_runtime_stubs.cpp (:3538-3543), while GCC defines them near :100-113. This deliberate storage-order split must survive file extraction.
- Preserve the existing support object-link order and every original src/sources.cmake entry. Add class sources only after each extraction's parity gate. Constructor-section and local-static storage checks are required before relocation.

## Completion and next bounded work

Add a separate support-definition inventory keyed by source plus qualified name and current body hash. Use an explicit support/reconstruction identity kind; do not manufacture original addresses or inflate the 4,157 historical count. Record owner, logical subsystem, final class files, adapter/binding roles, reason for retained boundaries, state references, callback/static constraints and separate extraction/relocation status.

This report covers only the four named support TUs and their relevant headers. Other non-manifest helpers inside recovered subsystem/state files, future class bindings and macro-generated/header behavior need the same closed inventory audit; this report does not claim those are absent. Existing tests/unit/test_compat_stubs.cpp explicitly says it supplies coverage-only substitutes, so its mere presence cannot establish production-shim parity.

Recommended order is GameApplication's non-diagnostic flow first, then bounded SDL palette/pixel helpers, device/surface behavior only after the lifetime/null contracts are resolved, followed by event/input coordination and any elected diagnostic classes. The compatibility text-sprite and unit-slot bodies belong to their existing family gates; they must not wait until a supposed all-game-method completion check discovers them.

Relevant existing gates are the dual-compiler build/storage comparisons; CMake runtime_mission_trace_tests; r-command shutdown, full-route/main-menu exit and real-input movement probes; current mission-05 first-Road and water-rejection routes; and original-matching frame evidence whenever presented output is claimed. Those gates were identified, not executed, in this read-only audit. Focused actual-body differential tests are still needed for each extracted support family, especially callback order, queue overflow/quit, input pulses, palette conversion, create/release and startup/shutdown sequence.

Confidence is high for definition counts, missing-registry coverage, five compatibility game bodies, static/ABI boundaries and observed source hazards; medium for the proposed fine-grained SDL class split and diagnostic ownership policy. No family is declared extraction-ready by this document.

## Reproducibility

Read-only commands: git status --short --branch; git diff --stat; rg --files over the four support directories; source reads and the existing scan_definitions(text, None) parser. No compiler, tests, assets or Git-index operation was run.

Audited source-file SHA256 values (raw bytes):

- src/platform/platform_sdl_runtime.cpp: 2c0b9b00fd8dacbd1d118da3952acdcb774f30d120231feb6764e71b420d7897
- src/bootstrap/bootstrap_main.cpp: 37358a642c65b8bf336b72803d99e3529a962b77685341d853d30d1c6095b178
- src/instrumentation/runtime_mission_trace.cpp: d843b82bc4a7492b775eb7d82b99063599278ea3714948a35fbcc0ee5a7e0f6e
- src/compatibility/decomp_runtime_stubs.cpp: 7915f5466a744ac56b0509a63c0731c0661a5eda113eb3f210bdbb72a826f74d
