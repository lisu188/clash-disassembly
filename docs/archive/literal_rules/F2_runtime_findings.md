# F2 recovered runtime constant evidence

Track: Win95 reconstruction. Frontier: behavior-preserving naming in canonical CLIPS, media, render, runtime and state code.

Inspected integer/float inventories for all 92 assigned TUs. Targeted expression review supports 226 scoped rules covering 233 original sites, using 31 proposed macros plus existing screen dimensions. Rules fix whole source expressions and functions; globals use exact declarations. Macro rules preserve exact tokens. Existing-enum substitutions are separately tagged kind=enum and require object parity; no new enum type, numeric respelling, suffix dropping, pointer rewrite or payload changes.

## Confirmed families

- Palette: Palette_BuildGrayscaleIdentityTable (0x401D10) constructs and iterates 256 four-byte entries; Palette_ExpandRGBTripletsToTable (0x401B20) expands 768 RGB bytes into 1024 table bytes; Palette_ApplyWithBrightnessOffset (0x404C80) independently copies 0x400u bytes and submits 256 entries. Original sub_401AB0 (clash95.asm:1215) advances four-byte entries to base+400h.
- DLX: DLXSpriteSet_Load (0x405AA0) writes DWORD-indexed data pointer[1024], loaded entry count[1025], queried file byte size[1026] and vtable[1027]; Destroy (0x405C60), CopyEntriesFrom (0x405D20) and Save (0x405DB0) independently consume these slots. Save writes a 4096-byte offset directory and starts data there; Load reads/subtracts 4096. GetLastCharIndex (0x405ED0) reads count at byte offset 4100, distinct from DWORD index 1025.
- CLIPS atoms: Rules_InitAtomTables (0x482260; clash95.asm:206479-206528) allocates and clears symbol/float/integer/bitmap tables of 4052/2012/668/668 bytes in four-byte steps. Rules_RestoreAtomicValueBuckets (0x482EF0) and Rules_ClearAtomInUseMarks (0x4949E0) independently traverse 1013/503/167/167 typed buckets. Str_Intern, Rules_AddDoubleValue, Rules_AddIntegerValue and Rules_AddBitmapValue use corresponding hash ranges. Integer and bitmap are separate domains despite equal counts.
- Screen pixel count: independent fullscreen allocation dimensions and both transition directions.

The constants JSON contains exact replacement definitions and manifest metadata for coordinator integration. Count versus byte extent versus DWORD index remain distinct. Allocation and copy/read sizes have separate names where exact original hex/unsigned spelling differs; no signedness inference is added.

## Deferred and rejected interpretations

- CLIPS expression, constraint, class and slot-name tables reuse 503/167/2012/668 independently. Do not reuse atom-table names for Rules_InitExpressionHashTable, Rules_RegisterConstraintCheckingCommands, Class_InitHashTables or ObjectsCompiler_WriteClassHashTable.
- CLIPS parser opcodes, packed node flags and record offsets need record-specific proof. ClipsType covers only 0..8; internal grammar tags 10,13,14,15,16,98,110,117 are not automatically primitive types.
- AVI event offset +167 in CAviDecompressor_InitCommon / AviPlayer_GetBufferedVideoFrame is unrelated to bucket counts. AVI object offsets, COM ordinals and error values such as -2005532222 remain deferred to object/vtable or exact API proof.
- Animation 0xFFFF/0xFFFE and decimal 65534 stay deferred by storage domain. Palette_BuildNearestColorLUT multiplier 1024 is not a palette-table byte extent. DLX DWORD index 1024 is not a palette size.
- Runtime color-format masks and compiler packed fields stay deferred. GetVersion and window styles give 0x80000000 different meanings.
- All floating literals remain inventoried, including CLIPS trigonometric thresholds/polynomials, numeric conversion identities and state values. This integer substitution batch does not claim to recover them.
- Raw state treasure outcomes, frame/dispatch/resource sequences and retained byte images stay literal. Only proven palette declaration extents change. Numeric definitions, ordinary arithmetic identities and string/address comments remain intentional literals.

## Complete assigned-TU inspection ledger

Counts are token census results, not semantic completion claims. Residual samples require a record/family interpretation or an explicit data classification. No inferred semantics are silently promoted.

| TU | Integer tokens | Float tokens | Replacement sites | Residual frequent lexeme/sample |
|---|---:|---:|---:|---|
| src/clips/00481550_00481550_clips_001.cpp | 55 | 0 | 0 | 111 at line 31, Lexer_ParseValueList |
| src/clips/00481720_00482D40_clips_001.cpp | 433 | 0 | 25 | 16 at line 40, Rules_CoerceFormToNumericArg |
| src/clips/00482D70_0048469F_clips_002.cpp | 701 | 0 | 8 | 12 at line 45, Rules_SetAtomicValueIndices |
| src/clips/004849EE_0048667D_clips_003.cpp | 354 | 0 | 0 | 32 at line 446, Rules_PrintLongInteger |
| src/clips/004866CC_004876E4_clips_004.cpp | 413 | 0 | 3 | 30 at line 696, CRT_ParseWidthPrecisionSpec |
| src/clips/0048773C_0048A4A0_clips_005.cpp | 606 | 0 | 0 | 64 at line 1148, Rules_ParseDeftemplateSlotList |
| src/clips/0048A670_0048BD30_clips_006.cpp | 428 | 0 | 0 | 16 at line 42, Rules_CreateDeftemplateSlot |
| src/clips/0048BD50_0048D520_clips_007.cpp | 535 | 0 | 0 | 16 at line 31, Lexer_ParseSlotConstraint |
| src/clips/0048D570_0048ED00_clips_008.cpp | 649 | 0 | 0 | 16 at line 31, Rules_ReportMultifieldAssertIntoSingleSlotError |
| src/clips/0048ED60_00490430_clips_009.cpp | 510 | 0 | 0 | 16 at line 326, Rules_ResolveFactOrInstanceArg |
| src/clips/00490530_00491530_clips_010.cpp | 281 | 1 | 0 | 10 at line 76, Lexer_IsCommandTextComplete |
| src/clips/00491580_00492BA0_clips_001.cpp | 400 | 0 | 0 | 16 at line 111, Module_CreateMainModule |
| src/clips/00492BE0_004942C0_clips_002.cpp | 549 | 0 | 0 | 80 at line 122, Rules_FreeTemplateSlotList |
| src/clips/00494330_004943A0_clips_003.cpp | 20 | 0 | 0 | 10 at line 30, AST_TreeContainsSpecialTag |
| src/clips/004943E0_00495930_clips_001.cpp | 401 | 0 | 13 | 14 at line 75, Rules_PrintFieldExprList |
| src/clips/00495A20_00495E80_clips_002.cpp | 188 | 0 | 0 | 31 at line 61, Rules_PackConstraintRecord |
| src/clips/00496000_00497BD0_clips_001.cpp | 516 | 0 | 0 | 31 at line 509, AST_HashNodeChildren |
| src/clips/00497C80_004995B0_clips_002.cpp | 414 | 0 | 0 | 16 at line 24, Defgeneric_ListDefmethodsCommand |
| src/clips/004996D0_0049B490_clips_003.cpp | 567 | 0 | 0 | 16 at line 312, Class_RefreshWatchExpressions |
| src/clips/0049B530_0049CD60_clips_004.cpp | 427 | 0 | 0 | 16 at line 22, Dribble_PrintRouter |
| src/clips/0049CE10_0049E8D0_clips_005.cpp | 432 | 0 | 0 | 10 at line 44, Rules_BindFunction |
| src/clips/0049E930_0049FF80_clips_006.cpp | 467 | 1 | 0 | 98 at line 542, Rules_RegisterPredicateHostFunctions |
| src/clips/004A0080_004A1CF0_clips_001.cpp | 718 | 11 | 27 | 16 at line 54, Rules_OddpFunction |
| src/clips/004A1D40_004A36B0_clips_002.cpp | 603 | 0 | 0 | 16 at line 53, Rules_ParsePrognMultifieldForm |
| src/clips/004A3790_004A5610_clips_003.cpp | 327 | 105 | 0 | 100 at line 14, Rules_RegisterMathBuiltins |
| src/clips/004A57D0_004A6B10_clips_004.cpp | 330 | 0 | 0 | 84 at line 116, Help_FindOrAdvanceTopicEntry |
| src/clips/004A6C40_004A8520_clips_005.cpp | 384 | 0 | 0 | 17 at line 88, Rules_WriteFunctionDefinitionRecordsToCode |
| src/clips/004A8570_004A9970_clips_006.cpp | 346 | 0 | 0 | 16 at line 23, Rules_CountJoinNetworkEntryNodes |
| src/clips/004A9A20_004AB4E0_clips_007.cpp | 688 | 0 | 0 | 10 at line 52, Instance_BuildInstance |
| src/clips/004AB610_004ACA00_clips_008.cpp | 375 | 0 | 0 | 16 at line 32, Instance_ActiveMessageDuplicateInstanceFunction |
| src/clips/004ACB00_004AE690_clips_001.cpp | 614 | 0 | 0 | 24 at line 55, Compiler_MarkAndEmit |
| src/clips/004AE6D0_004B0030_clips_002.cpp | 605 | 0 | 0 | 24 at line 28, MessageHandler_RemoveByNameAndType |
| src/clips/004B00A0_004B1820_clips_003.cpp | 559 | 0 | 0 | 20 at line 163, Class_LookupCurrentScopedName |
| src/clips/004B1860_004B2E40_clips_004.cpp | 530 | 0 | 0 | 16 at line 464, Rules_MarkDependentRulesForSlotChange |
| src/clips/004B2EB0_004B50D6_clips_005.cpp | 589 | 0 | 0 | 16 at line 142, IO_ScanfParseFormat |
| src/clips/004B529A_004B75B0_clips_006.cpp | 725 | 0 | 0 | 10 at line 848, CRT_ParseTzDecimalDigits |
| src/clips/004B76F0_004B8D90_clips_007.cpp | 705 | 0 | 0 | 16 at line 79, PP_MakeConst28 |
| src/clips/004B8EC0_004BA500_clips_008.cpp | 713 | 0 | 0 | 68 at line 65, Rules_NormalizeNestedConnectives |
| src/clips/004BA5F0_004BBF90_clips_009.cpp | 618 | 0 | 0 | 12 at line 36, Rules_DeftemplateBloadRefreshSlot |
| src/clips/004BBFE0_004BD710_clips_010.cpp | 670 | 0 | 0 | 16 at line 61, Rules_ParseTemplateSlotList |
| src/clips/004BD750_004BEEF0_clips_011.cpp | 433 | 0 | 0 | 10 at line 84, Parser_ValidateFunctionCallArgs |
| src/clips/004BEF30_004C0550_clips_012.cpp | 472 | 0 | 0 | 20 at line 607, Rules_AllocDefruleDisjunct |
| src/clips/004C0620_004C1B80_clips_013.cpp | 518 | 0 | 0 | 16 at line 37, Rules_SetLHSParseNodeDefaultFlags |
| src/clips/004C1BB0_004C33E0_clips_014.cpp | 623 | 0 | 0 | 10 at line 213, Rules_ParseAssertTemplate |
| src/clips/004C3430_004C4F90_clips_015.cpp | 612 | 0 | 0 | 12 at line 100, Rules_UnionConstraints |
| src/clips/004C4FB0_004C6950_clips_016.cpp | 657 | 0 | 0 | 12 at line 90, Deffunction_BsaveWriteConstructs |
| src/clips/004C6990_004C8290_clips_017.cpp | 503 | 1 | 0 | 12 at line 77, Class_BloadRefreshHandlerRecord |
| src/clips/004C82D0_004C9DB0_clips_001.cpp | 392 | 0 | 0 | 40 at line 307, Defgeneric_PrintApplicableMethods |
| src/clips/004C9E20_004CB620_clips_002.cpp | 477 | 0 | 0 | 10 at line 268, Method_ParseParameterRestriction |
| src/clips/004CB630_004CCE70_clips_003.cpp | 365 | 0 | 0 | 20 at line 64, Deffunction_WriteConstructCodeFiles |
| src/clips/004CCEC0_004CEAC0_clips_004.cpp | 462 | 0 | 0 | 16 at line 94, MessageHandler_SetWatchFlagField |
| src/clips/004CEC60_004CFFC0_clips_005.cpp | 471 | 0 | 0 | 128 at line 35, InstanceQuery_FindAllInstances |
| src/media/004637B0_00465D30_media_001.cpp | 650 | 0 | 0 | 151 at line 179, CAviDecompressor_Header |
| src/media/00465DD0_00466C60_media_002.cpp | 489 | 0 | 0 | 2034 at line 333, CAviDecompressor_BeginPlayback |
| src/media/004674A0_00469590_media_003.cpp | 879 | 0 | 0 | 1964 at line 125, AviPlayer_Flip |
| src/media/00469680_0046B200_media_004.cpp | 497 | 0 | 2 | 2058 at line 32, AviPlayer_AllocDecodedBitmapInfo |
| src/media/0046B610_0046E5D0_media_005.cpp | 467 | 0 | 2 | 16 at line 49, Audio_MixResampledVoice |
| src/media/0046E870_004701E0_media_006.cpp | 461 | 0 | 1 | 52 at line 28, CSS_EmptySampleCache |
| src/media/00470220_00471C40_media_007.cpp | 558 | 0 | 0 | 108 at line 543, CSS_InitMixChannels |
| src/media/00471C60_00473570_media_008.cpp | 483 | 0 | 4 | 164 at line 1267, Surface_Destruct |
| src/media/00472B00_00472B00_media_001.cpp | 0 | 0 | 0 | none >=10 |
| src/media/004735F0_00475080_media_009.cpp | 474 | 0 | 0 | 164 at line 27, Surface_BltToWindowClient |
| src/media/004753E0_00477CC0_media_010.cpp | 418 | 0 | 2 | 16 at line 40, Render_SetPaletteEntryColor |
| src/media/00477CE0_00479020_media_011.cpp | 472 | 0 | 14 | 12 at line 152, Compat_FileStreamIsReady |
| src/media/004790E0_0047AA80_media_012.cpp | 503 | 0 | 6 | 12 at line 37, File_SourceScalarDtor |
| src/media/0047AA90_0047C760_media_013.cpp | 613 | 0 | 0 | 16 at line 106, Rules_AssertCommand |
| src/media/0047C7A0_0047DF90_media_014.cpp | 402 | 0 | 6 | 12 at line 53, Rules_RegisterConstructType |
| src/media/0047DFE0_0047F7F0_media_015.cpp | 435 | 1 | 0 | 16 at line 29, Rules_GetActivationRuleName |
| src/media/0047F820_00481100_media_016.cpp | 518 | 0 | 0 | 24 at line 144, Rules_UnmakeInstance |
| src/media/004811C0_004814A0_media_017.cpp | 75 | 1 | 0 | 16 at line 30, Rules_RtnDouble |
| src/render/00401A40_00402BB0_render_001.cpp | 336 | 0 | 15 | 12 at line 283, Render_FillClippedScanlines |
| src/render/00402E80_00404660_render_002.cpp | 454 | 0 | 6 | 12 at line 402, Render_BlitCompressedSpriteRLE |
| src/render/004046D0_00405D20_render_003.cpp | 419 | 0 | 60 | 188 at line 49, Render_SetPixelFormat |
| src/render/00405DB0_00407D20_render_004.cpp | 538 | 0 | 12 | 10 at line 207, DLXSprite_LoadCachedEntry |
| src/runtime/00461520_00463070_runtime_001.cpp | 454 | 0 | 5 | 16 at line 87, Input_KeyToChar |
| src/runtime/00463220_004635A0_runtime_002.cpp | 91 | 0 | 0 | 16 at line 32, CAviDecompressor_SetupBlitFormat |
| src/runtime/004D0560_004D1B00_runtime_001.cpp | 429 | 0 | 0 | 20 at line 44, ObjectsCompiler_WriteClassPointerArray |
| src/runtime/004D1F50_004D35A0_runtime_002.cpp | 583 | 0 | 0 | 64 at line 37, Rules_AddObjectPatternNode |
| src/runtime/004D35E0_004D4D50_runtime_003.cpp | 486 | 0 | 0 | 16 at line 712, Class_BuildModuleScopeBitmap |
| src/runtime/004D4DA0_004D6090_runtime_004.cpp | 497 | 0 | 0 | 16 at line 116, Class_PrintSlotBasicInfoTable |
| src/runtime/004D6210_004D80F0_runtime_005.cpp | 449 | 0 | 14 | 16 at line 81, Class_SlotTypesQuery |
| src/runtime/004D8120_004D9F20_runtime_006.cpp | 670 | 0 | 0 | 16 at line 425, Module_NextPortItemEnum |
| src/runtime/004D9FD0_004DB8D0_runtime_007.cpp | 547 | 0 | 0 | 16 at line 144, Lexer_ParseSalienceOption |
| src/runtime/004DB9A0_004DD330_runtime_008.cpp | 598 | 0 | 0 | 10 at line 137, Rules_OverlayConstraint |
| src/runtime/004DD3F0_004DE9B0_runtime_009.cpp | 487 | 0 | 0 | 16 at line 41, Rules_CEFindBoundVariableOccurrence |
| src/runtime/004DEA00_004E03B0_runtime_010.cpp | 519 | 0 | 0 | 10 at line 146, Method_ParseWildcardRestrictionString |
| src/runtime/004E03F0_004E1A40_runtime_011.cpp | 467 | 0 | 0 | 10 at line 127, Parser_ParseInstanceQueryAction |
| src/runtime/004E1A90_004E3400_runtime_012.cpp | 676 | 0 | 0 | 40 at line 88, Rules_BuildDualSlotConstraintBitmapTestNode |
| src/runtime/004E3440_004E56D0_runtime_013.cpp | 596 | 0 | 0 | 10 at line 162, Class_ParseSlot |
| src/runtime/004E5760_004E7F70_runtime_014.cpp | 238 | 0 | 0 | 24 at line 49, AST_CloneFieldAccessSubtreeJN |
| src/state/00000000_00000000_prelude_helpers.cpp | 164 | 0 | 0 | 12 at line 80, Render_InitRecoveredVtableStorage |
| src/state/00000000_0054FFFF_recovered_state.cpp | 9811 | 35 | 8 | 10 at line 303, global storage |

## Coordinator validation

Resolve all families against the same frozen source. Require no conflicts or respellings, exact preprocessed-token parity, and normalized object parity for GCC 13 and Clang 18. Run generator freshness, constant guards, manifest/body hashes, tooling tests and the four public asset-free gates. Preserve original state bytes and linked symbol/data layout. Keep existing warning/link/header baselines unchanged. No runtime or visual-fidelity claim follows from naming.

## Extended review after the first census

- Existing ClipsType mapping is independently confirmed by Rules_ComputeFieldHashValue / Rules_HashFactFieldList. Here DATA_OBJECT type1 selects integer payload / Rules_AddIntegerValue, type0 selects double payload / Rules_AddDoubleValue. Logical-name/file types2/3/8 select textual interned payloads. No argument counts or array indexes are substituted.
- Rules_SetStrategyCommand compares matching breadth/lex/mea/complexity/simplicity/random strings before assigning newStrategy. Independently, Rules_GetStrategyName and Rules_InsertActivationSorted already dispatch CLIPS_STRATEGY members to those names/handlers (EC1 proof).
- Compat_FileStreamRelease (0x477D60) tests bit4 before _wcpp_4_dtor_array_store__ plus j_j__nfree_, and bit2 before j__nfree_; DLXSpriteSet_Destroy (0x405C60) independently uses the same paths. Every included function was checked for this array-helper/release family. These mechanical destructor bits are not ordinary file mode flags.
- CSS stream buffer length multiplies g_CSS_StreamBufferMs by bytes/second formatInfo[2] and divides1000 (media/0046E870...:190). Independently, two stream-service loops convert g_CSS_StreamServiceRateHz to Sleep milliseconds using1000/rate (media/0046B610...:1356,1438). Exact decimal int token retained.

Legacy EC1/EC2 dispatch sites are already named in their current TUs; new enum rules cover proven producers/additional consumers. Parser restriction codes such as110 stay distinct from primitive type tags. Header regeneration can shift census line samples; function identities and exact expressions remain authoritative.

## Prospective rule validation

The final WSL validation below passed: 226 rules, 233 unique sites in 20 TUs,
43 existing-enum sites, 190 exact-macro sites, 31 proposed macros, zero rejected
sites and zero numeric respellings. Definitions were supplied only in memory;
this check did not apply source replacements. An earlier pre-optimization
resolver run was interrupted after repeatedly rereading the manifest. The
coordinator's cached source inventory resolved the final rules in about one
second. The WSL worktree Git indirection emits a path diagnostic unless the
coordinator supplies its resolved Git environment; that affects the recorded
commit lookup, not the rule checks.

From the worktree root in WSL:

```sh
python3 - <<'PY'
import sys, json
sys.path.insert(0, 'tools')
import literal_common as lc
import apply_literal_names as aln
rules = json.load(open('docs/archive/literal_rules/F2_runtime.json'))
proposed = json.load(open('docs/archive/literal_rules/F2_constants.json'))
entries, families = lc.load_manifest()
by = {e['name']: e for e in entries}
prelude = lc.parse_prelude_macros()
enums = lc.parse_prelude_enums()
for entry in proposed:
    by[entry['name']] = entry
    prelude[entry['name']] = {'body': entry['spelling'], 'params': None}
    families.setdefault(entry['family'], set()).add(entry['name'])
assert not aln.validate_rules(rules, by, prelude, enums)
plan = aln.resolve(rules, by, families, 'F2-review', enums)
assert not plan['rejected']
assert not any(site.get('respell') for site in plan['entries'])
assert len(plan['entries']) == 233
assert sum(site['class'] == 'enum' for site in plan['entries']) == 43
print('F2 prospective rules: PASS')
PY
```
