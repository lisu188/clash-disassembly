# CLIPS Engine Source Cross-Reference (6.0 engine, 6.30 source proxy)

The `clash95` (Win95) embedded rules engine is CLIPS 6.0 (see
`docs/REVERSE_ENGINEERING.md`, "Provenance: the rules engine is CLIPS 6.0").
The public 6.30 core source is used only as a stand-in because 6.0 source is not
distributed.
CLIPS 6.0 source is not distributed, but the diagnostic strings, format
strings, and internal function names of the CLIPS core are stable across the
6.x line. This table cross-references recovered Queue F (rules engine / COOL
object system / constructs-to-C compiler) function names against the public
**CLIPS 6.30 core source** (`clips_core_source_630`, SourceForge
`clipsrules`), used as a proxy for the 6.0 family.

## Method

Every function body in `clash95.c` that contains a high-value string literal
(format string, error message, or multi-word phrase) was matched against the
enclosing function of the same literal in the CLIPS 6.30 source. An entry is
**definitive** when a distinctive string is emitted from exactly one CLIPS
function, or when the recovered name already matches the CLIPS function name
verbatim; **corroborating** when the shared string is real but not unique.

Result: of the string-anchored Queue F functions, **zero were mis-named** -
every match agreed with the existing recovered name (one low-confidence name
was made more precise; see below). This is an independent accuracy check on the
`sub_` rename campaign for the CLIPS subsystem.

## Definitive matches

| Recovered name | CLIPS 6.30 source | Anchor |
| --- | --- | --- |
| `Defgeneric_CreateDefaultPPForm` | `genrcpsr.c:CreateDefaultGenericPPForm` | `"(defgeneric %s::%s)\n"` + identical `strlen+strlen+17` buffer, module-then-generic arg order, `SetDefgenericPPForm` tail, `newGeneric` call gate |
| `Rules_RunAgendaLoop` | `engine.c:EnvRun` | 4 shared run-statistics format strings (`"... rules per second.\n"`, `"%ld mean number of facts (%ld maximum).\n"`, activations, instances) |
| `Rules_ReportPatternNetworkError` | `factmch.c:PatternNetErrorMessage` | `"   Problem resides in field #%d\n"`, `"   Problem resides in slot %s\n"` |
| `Rules_ReportJoinNetworkError` | `drive.c:JoinNetErrorMessage` | `"   Problem resides in join #%d in rule(s):"` |
| `Rules_EvalStringCore` | `strngfun.c:EnvEval` | `"Eval-%d"` (the eval router name) |
| `Class_GeneratePublicSlotHandlers` | `msgpsr.c:CreateGetAndPutHandlers` | `"%s get-%s () ?self:%s)"` |
| `Rules_UndefconstructCommand` | `cstrccom.c:UndefconstructCommand` | recovered name matches CLIPS name verbatim |
| `Rules_PPConstructCommand` | `cstrccom.c:PPConstructCommand` | recovered name matches CLIPS name verbatim |
| `Rules_GetConstructModuleCommand` | `cstrccom.c:GetConstructModuleCommand` | recovered name matches CLIPS name verbatim |
| `Rules_ParseAllowedValuesAttribute` | `cstrnpsr.c:ParseAllowedValuesAttribute` | recovered name matches CLIPS name verbatim |
| `Rules_ParseRangeOrCardinalityAttribute` | `cstrnpsr.c:ParseRangeCardinalityAttribute` | recovered name matches CLIPS name (range/cardinality attribute parser) |

## Corroborating matches

| Recovered name | CLIPS 6.30 source | Anchor (non-unique) |
| --- | --- | --- |
| `Instance_GetQualifiedName` | `insmngr.c:GetFullInstanceName` | `"%s::%s"` module-qualified instance name |
| `Rules_ConstructCodeFileOpen` | `conscomp.c:OpenFileIfNeeded` | `"%s%d_%d"` construct-code partition filename |
| `MessageHandler_Send` | `msgpass.c:PerformMessage` | `"message"` (COOL message dispatch) |

## Change made this session

- `sub_4C9DB0`: `Defgeneric_EmitQualifiedNameBanner` (low, "mechanical
  banner/log builder") -> `Defgeneric_CreateDefaultPPForm` (high). The function
  is CLIPS's `CreateDefaultGenericPPForm`, which synthesizes the default
  pretty-print form for a generic that a `defmethod` implicitly creates.

## Reproduction

The reference source was obtained from SourceForge
(`clipsrules/CLIPS/6.30/clips_core_source_630.zip`). The string-anchoring can be
re-run against any local CLIPS 6.x core tree; low-confidence Queue F functions
that carry no string literals (trivial accessors, refcount helpers, vtable-slot
thunks, Watcom destructors) are not resolvable this way and correctly remain
honest mechanical descriptions per `docs/REVERSE_ENGINEERING.md` section 2.
