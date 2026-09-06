# F5 final numeric census and remaining evidence queue

Track: Win95 reconstruction, behavior-preserving constant naming. This record accounts for all 140 canonical translation units after F1/F2/F3/F4 application and the separate F6 supplement. It does not certify semantic recovery of every residual token or advance campaign validation.

## Before/after results

Frozen source: commit `227ae3435b46f96ac0533692bd8dbb1f241271a0`, retained in `artifacts/magic-numbers-20260906/production-before.tar`. Both censuses use the final conservative F0 lexer/classifier, including the initializer-expression correction. Final source includes 1,988 named occurrences in 62 TUs (1,815 macro substitutions and 173 reviewed existing-enum substitutions); all 4,157 manifest function identities remain.

| Count | Before | After | Change |
|---|---:|---:|---:|
| Numeric code tokens | 81,247 | 79,259 | -1,988 |
| Integer tokens | 81,069 | 79,081 | -1,988 |
| Float tokens | 178 | 178 | 0 |
| Integer tokens below 10 | 51,163 | 50,936 | -227 |
| Legacy filter eligible candidates | 42 | 3 | -39 |
| Canonical translation units covered | 140 | 140 | 0 |

The three remaining legacy candidates are all explicitly rejected/deferred below. After the six F5 dispositions, the census classifications are 0 replaceable candidates, 5,244 legitimate data/arithmetic occurrences and 74,015 unresolved occurrences. The before census has 42 candidates, 5,241 legitimate and 75,964 unresolved. The class-count comparison includes three new scalar-definition data justifications; the raw-token reduction is unaffected.

`unresolved` means no automatic or explicit disposition was established. It includes routine zeros/ones, selectors, numeric definitions and meaningful values needing more evidence; it is not proof that every occurrence is a magic number or inherently ambiguous. The per-site queue retains exact path/function/line/column/lexeme/context and the reason for deferral. The three specifically reviewed unresolved sites carry their candidate-domain rejection and missing evidence; other sites inherit the conservative requirement for assembly/data-flow review, with subsystem/function-family evidence queues below and in F1/F2. Every remaining token has a disposition, but generic unresolved entries do not establish individually recovered meanings or prove that every potentially nameable value has exhausted further investigation. No blanket semantic approval is used.

## Explicit reviewed residuals

The optional checked-in `F5_remaining_dispositions.json` contains six disjoint rules with one expected match each. It classifies only these current locations and does not authorize replacement.

- `UnitBattle_DrawTileContents:943`, `wallSpriteChar += 404`: a wall-sprite range with sibling bases 412 and 420, consumed by `DLX_GetSpriteForChar`. Reject `UNIT_STACK_PATH_BYTES`; the full theme/resource mapping remains deferred.
- `Cheat_ClearSelectedSquadDamageFlags:840`, additive 31 with 147161, and `Cheat_HealSelectedSquadAndClearDamage:874`, additive 31 with 147158: effective offsets 147192/147189 are consistent with existing fields, but naming 31 as a forward slot stride would assert an unproven address decomposition. Preserve the expressions and defer whole-expression recovery.
- State definitions `g_CAviDecompressor_MillisecondsPerSecond`, `g_AviPlayer_MillisecondsPerSecond` and `g_Rules_MillisecondsPerSecond`: preserve their existing names and exact 1000.0 literal initialization. The AviPlayer definition deliberately retains a double literal initializing float storage. Consumers are `CAviDecompressor_RenderLoop`, `AviPlayer_UpdateTargetFrameFromClock` and `Rules_TimeCommand`.

The final legacy filter reports only those three rejected sites. The 168 derived-candidate groups are arithmetic-window suggestions, not semantic matches or additional approved replacements. Residual inspection identified four further direct stack-slot base/count uses; the bounded adjacent selection family supplied nine more independently proven uses. The coordinator applied those 13 sites through the separate `F6_stack_helpers.json` reviewed plan against post-F1/F2/F3/F4 source. The final census includes both the initial 1,975-site batch and that 13-site supplement. `F6_stack_helpers_findings.md` records the exact baseline, original instructions, stack-pointer producer, helper count and ten-element slot/flag layout evidence.

## Remaining domains

| Subsystem | Remaining code tokens | Unresolved | Float tokens | Required evidence |
|---|---:|---:|---:|---|
| battle | 1,996 | 1,988 | 0 | Remaining battle state offsets, wall/occupancy grids, sprite-range selectors and draw coordinates require separate battle-layout or resource-table proof. Wall-sprite 404 is explicitly rejected as a path-size candidate. |
| buildings | 8,407 | 8,368 | 0 | Garrison/production records, UI selectors/coordinates, tactical locals and building/road resource IDs still share small value spaces. The Road timing/AP/mask supplement is bounded; arbitrary nearby flags and query modes remain a separate review queue. |
| clips | 25,473 | 25,458 | 119 | Parser/AST tags, packed node/constraint fields and record sizes require node-specific ownership. Integer/bitmap atom buckets stay separate from equal-valued expression, constraint and class tables; primitive ClipsType enums do not cover internal tags. Math coefficients and thresholds retain exact float lexemes. |
| core | 135 | 135 | 0 | Startup/helper record offsets and dispatch values need reached call-flow or structure evidence. Presence in this small subsystem does not authorize value-only substitution. |
| media | 8,359 | 8,355 | 2 | AVI object fields, vtable slots and codec/audio format values require object/API-specific evidence. File/destructor flag names cover only the reviewed deleting-destructor branches; arbitrary flags remain unresolved. |
| persistence | 3,573 | 3,558 | 0 | Save/mission/prisoner/economy fields, occupancy-address decompositions and UI dimensions need their owning format or domain. Mission literals are not route-completion markers. |
| render | 1,652 | 1,640 | 0 | Surface/vtable fields, pixel-format masks, compressed-sprite codes and clipping coordinates require layout/codec-specific proof. DLX DWORD indices remain distinct from byte extents and palette counts. |
| runtime | 7,768 | 7,764 | 0 | Recovered CRT/CLIPS instance, slot, compiler and parser fields require family-specific structure/ABI evidence. No Win32/CRT integer is blessed merely because a familiar value recurs. |
| state | 10,002 | 4,939 | 35 | Only literal-only array payloads and three already-named 1000.0 timebase definitions receive explicit data justification. Declaration extents, scalar initializers and mixed symbolic/expression payloads remain in the review queue; numeric data is preserved. |
| strategic | 5,241 | 5,201 | 20 | Scenario, objective, AI, queen/economy and rules-host selectors/thresholds need their individual consumer/producer evidence. The two compensating 31 cheat addresses are explicitly deferred; their current expression decomposition is retained. |
| units | 3,393 | 3,359 | 1 | Stack/path/member families now use reviewed names, but local record bases, health/AP thresholds, renderer sizes and tactical/temporary buffers still need specific ownership proof. Equal 404-byte buffers are not automatically the world queued-path domain. |
| world | 3,260 | 3,250 | 1 | World widget/query modes, viewport/input geometry, marker/tile IDs, raw builder images and map/session fields need matching UI/data-flow evidence. Census accounting does not promote Road continuation or campaign progress. |

All residual sites remain in the durable census. F1/F2 findings supply broader function/family review ledgers, and F3/F4/F6 record the accepted field/alias, Road-specific and stack-helper evidence. These domain notes deliberately retain missing evidence instead of converting frequent equal values into shared names.

## All 140 translation units

Counts below come from source tokens, including source-level numeric definitions and declaration extents. Preprocessor directives, comments, character/string literals and identifiers containing digits are excluded. `Named` is the before-minus-after token count. The final column is one representative unresolved numeric lexeme >=10 (or a smaller unresolved token when no such value remains), not a complete per-file semantic finding. Float counts are shown separately. The complete per-site census is authoritative.

| Canonical TU | Before ints/floats | After ints/floats | Named | Unresolved | Residual example |
|---|---:|---:|---:|---:|---|
| `src/battle/0042CB50_0042E8B0_battle_001.cpp` | 647/0 | 535/0 | 112 | 531 | `100` at line 67 in `UnitBattle_HandleBattlefieldInteraction` |
| `src/battle/0042E9E0_00430C20_battle_002.cpp` | 792/0 | 749/0 | 43 | 749 | `40` at line 258 in `Battle_RunTacticalCombat` |
| `src/battle/00430F80_00433820_battle_003.cpp` | 754/0 | 712/0 | 42 | 708 | `18` at line 893 in `BuildingGarrisonDialog_DrawSlotGrid` |
| `src/buildings/0041D030_0041F0C0_buildings_001.cpp` | 616/0 | 574/0 | 42 | 573 | `420` at line 145 in `Building_New` |
| `src/buildings/0041F1A0_00421010_buildings_002.cpp` | 674/0 | 647/0 | 27 | 644 | `100` at line 95 in `Building_Transfer` |
| `src/buildings/00421240_00422020_buildings_003.cpp` | 300/0 | 300/0 | 0 | 300 | `20` at line 407 in `Castle_DrawAmbientAnimationLayer` |
| `src/buildings/00422100_00422AC0_buildings_004.cpp` | 413/0 | 395/0 | 18 | 386 | `20` at line 81 in `BuildingGarrisonDialog_WriteActionWidgetRecord` |
| `src/buildings/00422B50_004254E0_buildings_005.cpp` | 571/0 | 505/0 | 66 | 500 | `720` at line 128 in `Unit_AddToGroup` |
| `src/buildings/00425540_00426FC0_buildings_006.cpp` | 567/0 | 498/0 | 69 | 497 | `40` at line 211 in `UnitBattle_InitPathingTables` |
| `src/buildings/004272A0_00428850_buildings_007.cpp` | 512/0 | 394/0 | 118 | 394 | `40` at line 621 in `UnitBattle_PlayDeathAnimation` |
| `src/buildings/00428880_0042A890_buildings_008.cpp` | 1027/0 | 975/0 | 52 | 975 | `0x4e` at line 1115 in `BuildCursor_EnsureWidgetTable` |
| `src/buildings/0042A910_0042C4E0_buildings_009.cpp` | 591/0 | 558/0 | 33 | 555 | `436` at line 326 in `BuildingEconomyDialog_DecreaseTaxRate` |
| `src/buildings/0042C560_0042C840_buildings_010.cpp` | 147/0 | 127/0 | 20 | 127 | `808` at line 191 in `UnitBattle_UpdateViewportFromInputAndGetHoveredSlot` |
| `src/buildings/004338C0_00436100_buildings_001.cpp` | 580/0 | 579/0 | 1 | 576 | `20` at line 47 in `BuildingGarrisonDialog_ShowProductionDialog` |
| `src/buildings/00436180_00437A90_buildings_002.cpp` | 520/0 | 421/0 | 99 | 421 | `23` at line 590 in `UnitBattle_RetreatUnit` |
| `src/buildings/004382E0_0043A880_buildings_003.cpp` | 666/0 | 525/0 | 141 | 525 | `864` at line 278 in `UnitBattle_ScoreAiActionGridForUnit` |
| `src/buildings/0043A8B0_0043CC50_buildings_004.cpp` | 714/0 | 587/0 | 127 | 587 | `40` at line 120 in `UnitBattle_SelectAiActionForUnit` |
| `src/buildings/0043CD00_0043E4B0_buildings_005.cpp` | 382/0 | 370/0 | 12 | 368 | `10` at line 727 in `Battle_BuildRoleDeploymentBuckets` |
| `src/buildings/0043E500_0043FDE0_buildings_006.cpp` | 509/0 | 448/0 | 61 | 437 | `100` at line 57 in `Building_UnitGetInto` |
| `src/buildings/0043FEF0_00441BE0_buildings_007.cpp` | 494/0 | 480/0 | 14 | 479 | `100` at line 203 in `Temple_ProcessGift` |
| `src/buildings/00441C80_00441D20_buildings_008.cpp` | 24/0 | 24/0 | 0 | 24 | `100` at line 21 in `Audio_PlayUnitHitSound` |
| `src/clips/00481550_00481550_clips_001.cpp` | 55/0 | 55/0 | 0 | 55 | `111` at line 31 in `Lexer_ParseValueList` |
| `src/clips/00481720_00482D40_clips_001.cpp` | 433/0 | 408/0 | 25 | 408 | `16` at line 40 in `Rules_CoerceFormToNumericArg` |
| `src/clips/00482D70_0048469F_clips_002.cpp` | 701/0 | 693/0 | 8 | 689 | `12` at line 45 in `Rules_SetAtomicValueIndices` |
| `src/clips/004849EE_0048667D_clips_003.cpp` | 354/0 | 354/0 | 0 | 354 | `32` at line 446 in `Rules_PrintLongInteger` |
| `src/clips/004866CC_004876E4_clips_004.cpp` | 413/0 | 410/0 | 3 | 410 | `30` at line 696 in `CRT_ParseWidthPrecisionSpec` |
| `src/clips/0048773C_0048A4A0_clips_005.cpp` | 606/0 | 606/0 | 0 | 606 | `64` at line 1148 in `Rules_ParseDeftemplateSlotList` |
| `src/clips/0048A670_0048BD30_clips_006.cpp` | 428/0 | 428/0 | 0 | 428 | `12` at line 67 in `Rules_CreateDeftemplateSlot` |
| `src/clips/0048BD50_0048D520_clips_007.cpp` | 535/0 | 535/0 | 0 | 531 | `16` at line 31 in `Lexer_ParseSlotConstraint` |
| `src/clips/0048D570_0048ED00_clips_008.cpp` | 649/0 | 649/0 | 0 | 649 | `16` at line 31 in `Rules_ReportMultifieldAssertIntoSingleSlotError` |
| `src/clips/0048ED60_00490430_clips_009.cpp` | 510/0 | 510/0 | 0 | 510 | `16` at line 326 in `Rules_ResolveFactOrInstanceArg` |
| `src/clips/00490530_00491530_clips_010.cpp` | 281/1 | 281/1 | 0 | 282 | `10` at line 76 in `Lexer_IsCommandTextComplete` |
| `src/clips/00491580_00492BA0_clips_001.cpp` | 400/0 | 400/0 | 0 | 400 | `16` at line 111 in `Module_CreateMainModule` |
| `src/clips/00492BE0_004942C0_clips_002.cpp` | 549/0 | 549/0 | 0 | 549 | `80` at line 122 in `Rules_FreeTemplateSlotList` |
| `src/clips/00494330_004943A0_clips_003.cpp` | 20/0 | 20/0 | 0 | 20 | `10` at line 30 in `AST_TreeContainsSpecialTag` |
| `src/clips/004943E0_00495930_clips_001.cpp` | 401/0 | 388/0 | 13 | 384 | `14` at line 75 in `Rules_PrintFieldExprList` |
| `src/clips/00495A20_00495E80_clips_002.cpp` | 188/0 | 188/0 | 0 | 188 | `14` at line 84 in `Rules_PackConstraintRecord` |
| `src/clips/00496000_00497BD0_clips_001.cpp` | 516/0 | 516/0 | 0 | 516 | `31` at line 509 in `AST_HashNodeChildren` |
| `src/clips/00497C80_004995B0_clips_002.cpp` | 414/0 | 414/0 | 0 | 414 | `16` at line 24 in `Defgeneric_ListDefmethodsCommand` |
| `src/clips/004996D0_0049B490_clips_003.cpp` | 567/0 | 567/0 | 0 | 567 | `16` at line 312 in `Class_RefreshWatchExpressions` |
| `src/clips/0049B530_0049CD60_clips_004.cpp` | 427/0 | 427/0 | 0 | 427 | `16` at line 22 in `Dribble_PrintRouter` |
| `src/clips/0049CE10_0049E8D0_clips_005.cpp` | 432/0 | 432/0 | 0 | 432 | `10` at line 44 in `Rules_BindFunction` |
| `src/clips/0049E930_0049FF80_clips_006.cpp` | 467/1 | 467/1 | 0 | 468 | `98` at line 542 in `Rules_RegisterPredicateHostFunctions` |
| `src/clips/004A0080_004A1CF0_clips_001.cpp` | 718/11 | 691/11 | 27 | 702 | `16` at line 54 in `Rules_OddpFunction` |
| `src/clips/004A1D40_004A36B0_clips_002.cpp` | 603/0 | 603/0 | 0 | 603 | `16` at line 53 in `Rules_ParsePrognMultifieldForm` |
| `src/clips/004A3790_004A5610_clips_003.cpp` | 327/105 | 327/105 | 0 | 432 | `100` at line 14 in `Rules_RegisterMathBuiltins` |
| `src/clips/004A57D0_004A6B10_clips_004.cpp` | 330/0 | 330/0 | 0 | 330 | `84` at line 116 in `Help_FindOrAdvanceTopicEntry` |
| `src/clips/004A6C40_004A8520_clips_005.cpp` | 384/0 | 384/0 | 0 | 384 | `17` at line 88 in `Rules_WriteFunctionDefinitionRecordsToCode` |
| `src/clips/004A8570_004A9970_clips_006.cpp` | 346/0 | 346/0 | 0 | 346 | `16` at line 23 in `Rules_CountJoinNetworkEntryNodes` |
| `src/clips/004A9A20_004AB4E0_clips_007.cpp` | 688/0 | 688/0 | 0 | 687 | `10` at line 52 in `Instance_BuildInstance` |
| `src/clips/004AB610_004ACA00_clips_008.cpp` | 375/0 | 375/0 | 0 | 375 | `16` at line 32 in `Instance_ActiveMessageDuplicateInstanceFunction` |
| `src/clips/004ACB00_004AE690_clips_001.cpp` | 614/0 | 614/0 | 0 | 614 | `24` at line 55 in `Compiler_MarkAndEmit` |
| `src/clips/004AE6D0_004B0030_clips_002.cpp` | 605/0 | 605/0 | 0 | 605 | `24` at line 28 in `MessageHandler_RemoveByNameAndType` |
| `src/clips/004B00A0_004B1820_clips_003.cpp` | 559/0 | 559/0 | 0 | 559 | `20` at line 163 in `Class_LookupCurrentScopedName` |
| `src/clips/004B1860_004B2E40_clips_004.cpp` | 530/0 | 530/0 | 0 | 530 | `16` at line 464 in `Rules_MarkDependentRulesForSlotChange` |
| `src/clips/004B2EB0_004B50D6_clips_005.cpp` | 589/0 | 589/0 | 0 | 589 | `16` at line 142 in `IO_ScanfParseFormat` |
| `src/clips/004B529A_004B75B0_clips_006.cpp` | 725/0 | 725/0 | 0 | 725 | `10` at line 848 in `CRT_ParseTzDecimalDigits` |
| `src/clips/004B76F0_004B8D90_clips_007.cpp` | 705/0 | 705/0 | 0 | 705 | `16` at line 79 in `PP_MakeConst28` |
| `src/clips/004B8EC0_004BA500_clips_008.cpp` | 713/0 | 713/0 | 0 | 713 | `68` at line 65 in `Rules_NormalizeNestedConnectives` |
| `src/clips/004BA5F0_004BBF90_clips_009.cpp` | 618/0 | 618/0 | 0 | 616 | `12` at line 36 in `Rules_DeftemplateBloadRefreshSlot` |
| `src/clips/004BBFE0_004BD710_clips_010.cpp` | 670/0 | 670/0 | 0 | 670 | `16` at line 61 in `Rules_ParseTemplateSlotList` |
| `src/clips/004BD750_004BEEF0_clips_011.cpp` | 433/0 | 433/0 | 0 | 433 | `10` at line 84 in `Parser_ValidateFunctionCallArgs` |
| `src/clips/004BEF30_004C0550_clips_012.cpp` | 472/0 | 472/0 | 0 | 472 | `20` at line 607 in `Rules_AllocDefruleDisjunct` |
| `src/clips/004C0620_004C1B80_clips_013.cpp` | 518/0 | 518/0 | 0 | 518 | `16` at line 37 in `Rules_SetLHSParseNodeDefaultFlags` |
| `src/clips/004C1BB0_004C33E0_clips_014.cpp` | 623/0 | 623/0 | 0 | 623 | `10` at line 213 in `Rules_ParseAssertTemplate` |
| `src/clips/004C3430_004C4F90_clips_015.cpp` | 612/0 | 612/0 | 0 | 612 | `12` at line 100 in `Rules_UnionConstraints` |
| `src/clips/004C4FB0_004C6950_clips_016.cpp` | 657/0 | 657/0 | 0 | 657 | `12` at line 90 in `Deffunction_BsaveWriteConstructs` |
| `src/clips/004C6990_004C8290_clips_017.cpp` | 503/1 | 503/1 | 0 | 504 | `12` at line 77 in `Class_BloadRefreshHandlerRecord` |
| `src/clips/004C82D0_004C9DB0_clips_001.cpp` | 392/0 | 392/0 | 0 | 392 | `40` at line 307 in `Defgeneric_PrintApplicableMethods` |
| `src/clips/004C9E20_004CB620_clips_002.cpp` | 477/0 | 477/0 | 0 | 477 | `10` at line 268 in `Method_ParseParameterRestriction` |
| `src/clips/004CB630_004CCE70_clips_003.cpp` | 365/0 | 365/0 | 0 | 365 | `20` at line 64 in `Deffunction_WriteConstructCodeFiles` |
| `src/clips/004CCEC0_004CEAC0_clips_004.cpp` | 462/0 | 462/0 | 0 | 462 | `16` at line 94 in `MessageHandler_SetWatchFlagField` |
| `src/clips/004CEC60_004CFFC0_clips_005.cpp` | 471/0 | 471/0 | 0 | 471 | `128` at line 35 in `InstanceQuery_FindAllInstances` |
| `src/core/00401020_004011F0_core_001.cpp` | 15/0 | 14/0 | 1 | 14 | `0x1Eu` at line 66 in `DetectGameCDPath` |
| `src/core/004015A0_00401A00_core_001.cpp` | 121/0 | 121/0 | 0 | 121 | `16` at line 81 in `PathEntryArray_CopyConstruct` |
| `src/media/004637B0_00465D30_media_001.cpp` | 650/0 | 650/0 | 0 | 650 | `151` at line 179 in `CAviDecompressor_Header` |
| `src/media/00465DD0_00466C60_media_002.cpp` | 489/0 | 489/0 | 0 | 489 | `108` at line 397 in `AviPlayer_ShutdownDecodeState` |
| `src/media/004674A0_00469590_media_003.cpp` | 879/0 | 879/0 | 0 | 879 | `1964` at line 125 in `AviPlayer_Flip` |
| `src/media/00469680_0046B200_media_004.cpp` | 497/0 | 495/0 | 2 | 495 | `16` at line 39 in `AviPlayer_AllocDecodedBitmapInfo` |
| `src/media/0046B610_0046E5D0_media_005.cpp` | 467/0 | 465/0 | 2 | 465 | `16` at line 49 in `Audio_MixResampledVoice` |
| `src/media/0046E870_004701E0_media_006.cpp` | 461/0 | 460/0 | 1 | 460 | `52` at line 28 in `CSS_EmptySampleCache` |
| `src/media/00470220_00471C40_media_007.cpp` | 558/0 | 558/0 | 0 | 557 | `108` at line 543 in `CSS_InitMixChannels` |
| `src/media/00471C60_00473570_media_008.cpp` | 483/0 | 479/0 | 4 | 479 | `164` at line 1267 in `Surface_Destruct` |
| `src/media/00472B00_00472B00_media_001.cpp` | 0/0 | 0/0 | 0 | 0 | none |
| `src/media/004735F0_00475080_media_009.cpp` | 474/0 | 474/0 | 0 | 474 | `164` at line 27 in `Surface_BltToWindowClient` |
| `src/media/004753E0_00477CC0_media_010.cpp` | 418/0 | 416/0 | 2 | 415 | `16` at line 40 in `Render_SetPaletteEntryColor` |
| `src/media/00477CE0_00479020_media_011.cpp` | 472/0 | 458/0 | 14 | 458 | `12` at line 152 in `Compat_FileStreamIsReady` |
| `src/media/004790E0_0047AA80_media_012.cpp` | 503/0 | 497/0 | 6 | 497 | `12` at line 37 in `File_SourceScalarDtor` |
| `src/media/0047AA90_0047C760_media_013.cpp` | 613/0 | 613/0 | 0 | 613 | `16` at line 106 in `Rules_AssertCommand` |
| `src/media/0047C7A0_0047DF90_media_014.cpp` | 402/0 | 396/0 | 6 | 394 | `12` at line 53 in `Rules_RegisterConstructType` |
| `src/media/0047DFE0_0047F7F0_media_015.cpp` | 435/1 | 435/1 | 0 | 436 | `16` at line 29 in `Rules_GetActivationRuleName` |
| `src/media/0047F820_00481100_media_016.cpp` | 518/0 | 518/0 | 0 | 518 | `24` at line 144 in `Rules_UnmakeInstance` |
| `src/media/004811C0_004814A0_media_017.cpp` | 75/1 | 75/1 | 0 | 76 | `16` at line 30 in `Rules_RtnDouble` |
| `src/persistence/00441DC0_00443B60_persistence_001.cpp` | 455/0 | 448/0 | 7 | 447 | `100` at line 29 in `Audio_PlayUnitMeleeAttackSound` |
| `src/persistence/00443BB0_00445CE0_persistence_002.cpp` | 584/0 | 567/0 | 17 | 564 | `22` at line 604 in `SaveSlotDialog_RepaintRow` |
| `src/persistence/00446230_00447840_persistence_003.cpp` | 613/0 | 592/0 | 21 | 592 | `17` at line 252 in `Queen_ShowWhimDecisionDialog` |
| `src/persistence/004479C0_0044AE10_persistence_004.cpp` | 635/0 | 633/0 | 2 | 628 | `11` at line 331 in `PlayGame_Dispatch` |
| `src/persistence/0044AE90_0044E850_persistence_005.cpp` | 838/0 | 789/0 | 49 | 786 | `556372` at line 910 in `Scenario_LoadMultiplayerMapAndSeedPlayers` |
| `src/persistence/0044E880_0044FE70_persistence_006.cpp` | 573/0 | 544/0 | 29 | 541 | `52` at line 796 in `Building_DrawPrisonerRows` |
| `src/render/00401A40_00402BB0_render_001.cpp` | 336/0 | 321/0 | 15 | 316 | `12` at line 283 in `Render_FillClippedScanlines` |
| `src/render/00402E80_00404660_render_002.cpp` | 454/0 | 448/0 | 6 | 448 | `12` at line 402 in `Render_BlitCompressedSpriteRLE` |
| `src/render/004046D0_00405D20_render_003.cpp` | 419/0 | 359/0 | 60 | 354 | `188` at line 49 in `Render_SetPixelFormat` |
| `src/render/00405DB0_00407D20_render_004.cpp` | 538/0 | 524/0 | 14 | 522 | `10` at line 207 in `DLXSprite_LoadCachedEntry` |
| `src/runtime/00461520_00463070_runtime_001.cpp` | 454/0 | 449/0 | 5 | 449 | `16` at line 87 in `Input_KeyToChar` |
| `src/runtime/00463220_004635A0_runtime_002.cpp` | 91/0 | 91/0 | 0 | 91 | `16` at line 32 in `CAviDecompressor_SetupBlitFormat` |
| `src/runtime/004D0560_004D1B00_runtime_001.cpp` | 429/0 | 429/0 | 0 | 429 | `20` at line 44 in `ObjectsCompiler_WriteClassPointerArray` |
| `src/runtime/004D1F50_004D35A0_runtime_002.cpp` | 583/0 | 583/0 | 0 | 583 | `64` at line 37 in `Rules_AddObjectPatternNode` |
| `src/runtime/004D35E0_004D4D50_runtime_003.cpp` | 486/0 | 486/0 | 0 | 485 | `16` at line 712 in `Class_BuildModuleScopeBitmap` |
| `src/runtime/004D4DA0_004D6090_runtime_004.cpp` | 497/0 | 497/0 | 0 | 497 | `16` at line 116 in `Class_PrintSlotBasicInfoTable` |
| `src/runtime/004D6210_004D80F0_runtime_005.cpp` | 449/0 | 435/0 | 14 | 432 | `16` at line 81 in `Class_SlotTypesQuery` |
| `src/runtime/004D8120_004D9F20_runtime_006.cpp` | 670/0 | 670/0 | 0 | 670 | `16` at line 425 in `Module_NextPortItemEnum` |
| `src/runtime/004D9FD0_004DB8D0_runtime_007.cpp` | 547/0 | 547/0 | 0 | 547 | `16` at line 144 in `Lexer_ParseSalienceOption` |
| `src/runtime/004DB9A0_004DD330_runtime_008.cpp` | 598/0 | 598/0 | 0 | 598 | `10` at line 137 in `Rules_OverlayConstraint` |
| `src/runtime/004DD3F0_004DE9B0_runtime_009.cpp` | 487/0 | 487/0 | 0 | 487 | `16` at line 41 in `Rules_CEFindBoundVariableOccurrence` |
| `src/runtime/004DEA00_004E03B0_runtime_010.cpp` | 519/0 | 519/0 | 0 | 519 | `10` at line 146 in `Method_ParseWildcardRestrictionString` |
| `src/runtime/004E03F0_004E1A40_runtime_011.cpp` | 467/0 | 467/0 | 0 | 467 | `10` at line 127 in `Parser_ParseInstanceQueryAction` |
| `src/runtime/004E1A90_004E3400_runtime_012.cpp` | 676/0 | 676/0 | 0 | 676 | `40` at line 88 in `Rules_BuildDualSlotConstraintBitmapTestNode` |
| `src/runtime/004E3440_004E56D0_runtime_013.cpp` | 596/0 | 596/0 | 0 | 596 | `10` at line 162 in `Class_ParseSlot` |
| `src/runtime/004E5760_004E7F70_runtime_014.cpp` | 238/0 | 238/0 | 0 | 238 | `24` at line 49 in `AST_CloneFieldAccessSubtreeJN` |
| `src/state/00000000_00000000_prelude_helpers.cpp` | 164/0 | 164/0 | 0 | 164 | `12` at line 80 in `Render_InitRecoveredVtableStorage` |
| `src/state/00000000_0054FFFF_recovered_state.cpp` | 9811/35 | 9803/35 | 8 | 4775 | `13` at line 217 in `file-scope storage` |
| `src/strategic/004506B0_004530D0_strategic_001.cpp` | 596/8 | 556/8 | 40 | 562 | `31` at line 578 in `Options_ApplyInGameSliders` |
| `src/strategic/00452753_0045303F_strategic_007.cpp` | 155/0 | 155/0 | 0 | 153 | `12` at line 44 in `Rules_HostDigTreasure` |
| `src/strategic/00453110_00455720_strategic_002.cpp` | 341/1 | 241/1 | 100 | 242 | `320` at line 32 in `Rules_QueuePathToTile` |
| `src/strategic/00455740_004582B0_strategic_003.cpp` | 497/10 | 430/10 | 67 | 437 | `98` at line 613 in `Rules_RegisterBuildingHostFunctions` |
| `src/strategic/00456706_00457789_strategic_008.cpp` | 225/0 | 225/0 | 0 | 225 | `0` at line 14 in `Rules_HostHealing` |
| `src/strategic/004589C0_004602F0_strategic_004.cpp` | 680/1 | 562/1 | 118 | 559 | `16` at line 332 in `AI_EvaluateStrategicTargetAtTile` |
| `src/strategic/00460360_00460910_strategic_005.cpp` | 2787/0 | 2782/0 | 5 | 2754 | `12` at line 64 in `Scenario_LoadMissionByIndex` |
| `src/strategic/00460950_004612E0_strategic_006.cpp` | 270/0 | 270/0 | 0 | 269 | `64` at line 202 in `RenderState_LoadDefaultCursorSprite` |
| `src/units/0040F510_00411560_units_001.cpp` | 427/0 | 400/0 | 27 | 392 | `100` at line 371 in `UnitSlot_CalcActionPointsFromFatigue` |
| `src/units/004115E0_00412BE0_units_002.cpp` | 454/0 | 394/0 | 60 | 382 | `100` at line 45 in `Unit_CheckLowMorale` |
| `src/units/00412C00_00414350_units_003.cpp` | 425/0 | 417/0 | 8 | 413 | `0xFFFF` at line 1308 in `Map_GetUnitTileMoveCostOrZero` |
| `src/units/00414390_00416750_units_004.cpp` | 510/0 | 488/0 | 22 | 488 | `100` at line 59 in `Path_InsertBridgeCornerWaypoints` |
| `src/units/00416850_00419120_units_005.cpp` | 518/0 | 512/0 | 6 | 512 | `0xFFFF` at line 146 in `WorldMap_DrawMapTile` |
| `src/units/004191F0_0041A690_units_006.cpp` | 599/1 | 592/1 | 7 | 589 | `20` at line 46 in `UI_DrawWidgetIcon` |
| `src/units/0041A960_0041C8B0_units_007.cpp` | 610/0 | 589/0 | 21 | 583 | `141441` at line 407 in `Unit_Attack` |
| `src/world/00408030_0040A0A0_world_001.cpp` | 333/0 | 289/0 | 44 | 288 | `16` at line 27 in `UI_TrySelectFriendlyStackUnderCursor` |
| `src/world/0040A0E0_0040B020_world_002.cpp` | 1694/1 | 1692/1 | 2 | 1692 | `0x4e` at line 298 in `WorldMap_EnsureBuilderWidgetTables` |
| `src/world/0040B0A0_0040D560_world_003.cpp` | 760/0 | 758/0 | 2 | 753 | `10` at line 572 in `TextSprite_MeasureStringExtent` |
| `src/world/0040D6D0_0040F4D0_world_004.cpp` | 521/0 | 520/0 | 1 | 517 | `20` at line 399 in `UI_MenuHitTestEntry` |

## Reproduction and validation

- Durable complete inputs/results: `artifacts/magic-numbers-20260906/census-before.json`, `census-after.json`, `production-before.tar`, `reviewed-plan.json`, `F6-reviewed-plan.json` and the application ledger. The after census includes the checked-in F5 dispositions.
- Verified all 140 canonical file paths are present in both summaries, including the one TU with zero numeric tokens; integer/float totals sum to total code occurrences; the reduction is exactly 1,988 across 62 TUs; all six F5 rules match one site; no new unrecognized numeric spellings appear.
- This pass ran no compiler or runtime binary. The coordinating batch owns both compiler token/object/layout gates, generator checks, public/native gates and the first-Road probe.

From this worktree root under WSL:

```sh
GIT_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git/worktrees/clash-disassembly1 \
GIT_COMMON_DIR=/mnt/c/Users/andrz/git/clash-disassembly/.git \
GIT_WORK_TREE=/mnt/c/Users/andrz/.codex/worktrees/62e9/clash-disassembly \
python3 tools/literal_inventory.py --census-sites \
  --dispositions docs/archive/literal_rules/F5_remaining_dispositions.json \
  > artifacts/magic-numbers-20260906/census-after.json
python3 -m unittest discover -s tests/tools -p test_literal_inventory.py -v
```
