/* Generated from src/recovered/rules/clips/00496000_events.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004996D0) --------------------------------------------------------
signed int __thiscall Rules_InitObjectSystem(void *this)
{
  (void)this;
  g_Symbol_IsA = (int)(intptr_t)Str_Intern(aIsA, 0);
  ++*(_DWORD *)(uintptr_t)(g_Symbol_IsA + 4);
  g_Clips_NameSymbol = (int)(intptr_t)Str_Intern(aName, 0);
  ++*(_DWORD *)(uintptr_t)(g_Clips_NameSymbol + 4);
  g_Rules_InitialObjectSymbol = (int)(intptr_t)Str_Intern(aInitialObject, 0);
  ++*(_DWORD *)(uintptr_t)(g_Rules_InitialObjectSymbol + 4);
  Rules_RegisterDefclassConstruct();
  Rules_RegisterInstanceFunctions();
  MessageHandler_RegisterCommands();
  Definstances_SetupConstruct();
  InstanceQuery_SetupFunctions(0);
  Class_RegisterBinaryItem();
  ObjectsCompiler_RegisterCodeGenerator();
  return Rules_RegisterObjectPatternType(0);
}
// 54E6F4: using guessed type int dword_54E6F4;
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (00499730) --------------------------------------------------------
int Class_CreateSystemClasses(void)
{
  int primitive_class; // ecx
  int number_class; // ebp
  int lexeme_class; // [esp+8h] [ebp-20h]
  int address_class; // esi
  int instance_class; // [esp+4h] [ebp-24h]
  int user_class; // [esp+0h] [ebp-28h]
  int initial_object_class; // edi
  char initial_object_flags; // ah
  int result; // eax
  int object_class; // [esp+Ch] [ebp-1Ch]

  Class_InternSlotName((_DWORD *)(uintptr_t)g_Symbol_IsA, 0, 1);
  Class_InternSlotName((_DWORD *)(uintptr_t)g_Clips_NameSymbol, 1, 1);
  object_class = Class_CreateSystemClass(aObject_0, 0, 0);
  primitive_class = Class_CreateSystemClass(aPrimitive, object_class, 0);
  user_class = Class_CreateSystemClass(aUser, object_class, 0);
  number_class = Class_CreateSystemClass(aNumber_1, primitive_class, 0);
  g_ClipsIntegerClass = Class_CreateSystemClass(aInteger_2, number_class, 0);
  g_ClipsPrimitiveTypeClassMap[0] = Class_CreateSystemClass(aFloat_2, number_class, 0);
  lexeme_class = Class_CreateSystemClass(aLexeme_0, primitive_class, 0);
  g_ClipsSymbolClass = Class_CreateSystemClass(aSymbol_3, lexeme_class, 0);
  g_ClipsStringClass = Class_CreateSystemClass(aString_2, lexeme_class, 0);
  g_ClipsMultifieldClass = Class_CreateSystemClass(aMultifield_1, primitive_class, 0);
  address_class = Class_CreateSystemClass(aAddress_0, primitive_class, 0);
  g_ClipsExternalAddressClass = Class_CreateSystemClass(aExternalAddr_0, address_class, 0);
  g_ClipsFactAddressClass = Class_CreateSystemClass(aFactAddress_1, address_class, 0);
  instance_class = Class_CreateSystemClass(aInstance_3, primitive_class, 0);
  g_Class_InstanceAddress = Class_CreateSystemClass(aInstanceAddr_7, instance_class, 0);
  g_Class_InstanceName = Class_CreateSystemClass(aInstanceName_2, instance_class, 0);
  initial_object_class = Class_CreateSystemClass(aInitialObjec_0, user_class, 0);
  initial_object_flags = *(_BYTE *)(uintptr_t)(initial_object_class + 20) & 0xFB;
  *(_BYTE *)(uintptr_t)(initial_object_class + 20) = initial_object_flags;
  *(_BYTE *)(uintptr_t)(initial_object_class + 20) = initial_object_flags | 8;
  Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(g_Class_InstanceAddress + 34), address_class, -1);
  Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(g_Class_InstanceAddress + 46), address_class, 2);
  Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(address_class + 40), g_Class_InstanceAddress, -1);
  Rules_AppendConstructToModuleList(g_ClipsPrimitiveTypeClassMap[0]);
  Rules_AppendConstructToModuleList(g_ClipsIntegerClass);
  Rules_AppendConstructToModuleList(g_ClipsSymbolClass);
  Rules_AppendConstructToModuleList(g_ClipsStringClass);
  Rules_AppendConstructToModuleList(g_ClipsMultifieldClass);
  Rules_AppendConstructToModuleList(g_ClipsExternalAddressClass);
  Rules_AppendConstructToModuleList(g_ClipsFactAddressClass);
  Rules_AppendConstructToModuleList(g_Class_InstanceAddress);
  Rules_AppendConstructToModuleList(g_Class_InstanceName);
  Rules_AppendConstructToModuleList(object_class);
  Rules_AppendConstructToModuleList(primitive_class);
  Rules_AppendConstructToModuleList(number_class);
  Rules_AppendConstructToModuleList(lexeme_class);
  Rules_AppendConstructToModuleList(address_class);
  Rules_AppendConstructToModuleList(instance_class);
  Rules_AppendConstructToModuleList(user_class);
  Rules_AppendConstructToModuleList(initial_object_class);
  result = Class_GetNextRecord(0);
  while ( result )
  {
    Class_AssignID(result);
    result = Class_GetNextRecord(result);
  }
  return result;
}
// 51AD7C: using guessed type int dword_51AD7C[];
// 51AD80: using guessed type int dword_51AD80;
// 51AD84: using guessed type int dword_51AD84;
// 51AD88: using guessed type int dword_51AD88;
// 51AD8C: using guessed type int dword_51AD8C;
// 51AD90: using guessed type int dword_51AD90;
// 51AD94: using guessed type int dword_51AD94;
// 51AD98: using guessed type int dword_51AD98;
// 51AD9C: using guessed type int dword_51AD9C;
// 54E6F8: using guessed type int dword_54E6F8;
// 54E6FC: using guessed type int dword_54E6FC;

//----- (00499990) --------------------------------------------------------
int Rules_RegisterDefclassConstruct(void)
{
  int v0; // ecx
  int v1; // ecx

  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_Defclass, 57);
  g_CLIPS_DefclassModuleItemIndex = Module_RegisterItem(
                   (int)(intptr_t)aDefclass,
                   (int)(intptr_t)Class_AllocRecord,
                   (int)(intptr_t)Class_RecordAtIndex,
                   (int)(intptr_t)Class_FreeRecord,
                   (int)(intptr_t)ObjectsCompiler_WriteModuleItemHeaderRef,
                   (int)(intptr_t)Class_LookupCurrentScopedName);
  g_ClipsDefclassConstructType = (int)(intptr_t)Rules_RegisterConstructType(
                        (int)(intptr_t)aDefclass,
                        (int)(intptr_t)aDefclasses,
                        (int)(intptr_t)Class_LookupCurrentScopedName,
                        (int)(intptr_t)Rules_ParseDefclass,
                        (int)(intptr_t)Rules_GetConstructNameSymbol,
                        (int)(intptr_t)Rules_GetModuleConstructListHead,
                        (int)(intptr_t)Rules_GetConstructOwnerModule,
                        (int)(intptr_t)Class_GetNextRecord,
                        (int)(intptr_t)Rules_SetConstructNextInModule,
                        (int)(intptr_t)Class_IsDeletable,
                        (int)(intptr_t)Class_IsDeletableAlt,
                        (int)(intptr_t)Class_DestroyRecord);
  Rules_AddClearReadyFunction((int)(intptr_t)aDefclass, (int)(intptr_t)Class_PrepareUndefineCheck, 0);
  Rules_AddClearFunction((int)(intptr_t)aDefclass, (int)(intptr_t)Class_CreateSystemClasses, 0);
  Class_InitHashTables();
  Module_RegisterImportExportConstructType((int)(intptr_t)aDefclass, 2);
  Module_AddAfterModuleDefinedCallback((int)(intptr_t)aDefclass, (int)(intptr_t)Class_RefreshWatchExpressions, 0);
  Rules_RegisterHostFunction(aUndefclass, 118, v0, (int)(intptr_t)Class_UndefineCommand, (int)(intptr_t)a11w_5);
  Rules_AddSaveFunction((int)(intptr_t)aDefclass, (int)(intptr_t)Class_ListAllConstructs, 10);
  Rules_RegisterHostFunction(aListDefclasses, 118, v1, (int)(intptr_t)Class_ListConstructsCommand, (int)(intptr_t)a01_1);
  Rules_RegisterHostFunction(aPpdefclass, 118, (int)(intptr_t)aPpdefclasscomm, (int)(intptr_t)Class_PrettyPrintCommand, (int)(intptr_t)a11w_5);
  Rules_RegisterHostFunction(aDescribeClass, 118, (int)(intptr_t)aDescribeclassc, (int)(intptr_t)Class_DescribeClassCommand, (int)(intptr_t)a11w_5);
  Rules_RegisterHostFunction(aBrowseClasses, 118, (int)(intptr_t)aBrowseclassesc, (int)(intptr_t)Class_BrowseClassesCommand, (int)(intptr_t)a01w_3);
  Rules_RegisterHostFunction(aGetDefclassLis, 109, (int)(intptr_t)aGetdefclasslis, (int)(intptr_t)Class_GetConstructListCommand, (int)(intptr_t)a01_1);
  Rules_RegisterHostFunction(aSuperclassp, 98, (int)(intptr_t)aSuperclasspcom, (int)(intptr_t)Class_SuperclassPCommand, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSubclassp, 98, (int)(intptr_t)aSubclasspcomma, (int)(intptr_t)Class_SubclassPCommand, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aClassExistp, 98, (int)(intptr_t)aClassexistpcom, (int)(intptr_t)Class_ClassExistPCommand, (int)(intptr_t)a11w_5);
  Rules_RegisterHostFunction(aMessageHandler, 98, (int)(intptr_t)aMessagehandler, (int)(intptr_t)Class_MessageHandlerExistPCommand, (int)(intptr_t)a23w);
  Rules_RegisterHostFunction(aClassAbstractp, 98, (int)(intptr_t)aClassabstractp, (int)(intptr_t)Class_ClassAbstractPCommand, (int)(intptr_t)a11w_5);
  Rules_RegisterHostFunction(aClassReactivep, 98, (int)(intptr_t)aClassreactivep, (int)(intptr_t)Class_ClassReactivePCommand, (int)(intptr_t)a11w_5);
  Rules_RegisterHostFunction(aClassSlots, 109, (int)(intptr_t)aClassslotscomm, (int)(intptr_t)Class_ClassSlotsCommand, (int)(intptr_t)a12w);
  Rules_RegisterHostFunction(aClassSuperclas, 109, (int)(intptr_t)aClasssuperclas, (int)(intptr_t)Class_ClassSuperclassesCommand, (int)(intptr_t)a12w);
  Rules_RegisterHostFunction(aClassSubclasse, 109, (int)(intptr_t)aClasssubclasse, (int)(intptr_t)Class_ClassSubclassesCommand, (int)(intptr_t)a12w);
  Rules_RegisterHostFunction(aGetDefmessageH, 109, (int)(intptr_t)aGetdefmessageh, (int)(intptr_t)Class_GetDefmessageHandlerListCommand, (int)(intptr_t)a02w);
  Rules_RegisterHostFunction(aSlotExistp, 98, (int)(intptr_t)aSlotexistpcomm, (int)(intptr_t)Class_SlotExistPCommand, (int)(intptr_t)a23w);
  Rules_RegisterHostFunction(aSlotFacets, 109, (int)(intptr_t)aSlotfacetscomm, (int)(intptr_t)Class_SlotFacetsCommand, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSlotSources, 109, (int)(intptr_t)aSlotsourcescom, (int)(intptr_t)Class_SlotSourcesCommand, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSlotTypes, 109, (int)(intptr_t)aSlottypescomma, (int)(intptr_t)Class_SlotTypesCommand, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSlotAllowedVal, 109, (int)(intptr_t)aSlotallowedval, (int)(intptr_t)Class_SlotAllowedValuesFunction, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSlotRange, 109, (int)(intptr_t)aSlotrangecomma, (int)(intptr_t)Class_SlotRangeFunction, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSlotCardinalit, 109, (int)(intptr_t)aSlotcardinalit, (int)(intptr_t)Class_SlotCardinalityFunction, (int)(intptr_t)a22w);
  Rules_RegisterHostFunction(aSlotWritablep, 98, (int)(intptr_t)aSlotwritablepc, (int)(intptr_t)Class_SlotWritablePCommand, (int)(intptr_t)a22we);
  Rules_RegisterHostFunction(aSlotInitablep, 98, (int)(intptr_t)aSlotinitablepc, (int)(intptr_t)Class_SlotInitablePCommand, (int)(intptr_t)a22we);
  Rules_RegisterHostFunction(aSlotPublicp, 98, (int)(intptr_t)aSlotpublicpcom, (int)(intptr_t)Class_SlotPublicPCommand, (int)(intptr_t)a22we);
  Rules_RegisterHostFunction(aSlotDirectAcce, 98, (int)(intptr_t)aSlotdirectacce, (int)(intptr_t)Class_SlotDirectAccessPCommand, (int)(intptr_t)a22we);
  Rules_RegisterHostFunction(aDefclassModule, 119, (int)(intptr_t)aGetdefclassmod, (int)(intptr_t)Class_DefclassModuleCommand, (int)(intptr_t)a11w_5);
  Rules_AddWatchItem((int)(intptr_t)aInstances_0, 0, 75, (int)(intptr_t)&g_Rules_WatchInstances, (int)(intptr_t)Class_SetWatchFlagCommand, (int)(intptr_t)Class_SetWatchFlagForModuleCommand);
  return Rules_AddWatchItem((int)(intptr_t)aSlots, 1, 74, (int)(intptr_t)g_Class_WatchSlots, (int)(intptr_t)Class_SetWatchFlagCommand, (int)(intptr_t)Class_SetWatchFlagForModuleCommand);
}
// 499A70: variable 'v0' is possibly undefined
// 499AA2: variable 'v1' is possibly undefined
// 51AD74: using guessed type int dword_51AD74;
// 51AD78: using guessed type int dword_51AD78[];
// 54E6B8: using guessed type int dword_54E6B8;
// 54E6BC: using guessed type int dword_54E6BC;

//----- (00499E00) --------------------------------------------------------
int  Class_CreateSystemClass(char *className, int superclass, int a3)
{
  signed int *class_symbol; // eax
  char class_flags; // dl
  int symbol; // eax
  unsigned int bucket_index; // eax
  int expression; // eax
  unsigned int inherited_index; // esi
  int inherited_class; // edx
  int class_record; // [esp+0h] [ebp-1Ch]
  _BYTE *class_bitmap; // [esp+4h] [ebp-18h]

  (void)a3;
  class_symbol = Str_Intern(className, superclass);
  class_record = Class_AllocateRecord((int)(intptr_t)class_symbol);
  class_flags = *(_BYTE *)(uintptr_t)(class_record + 20) | 4;
  *(_BYTE *)(uintptr_t)(class_record + 20) = class_flags;
  symbol = *(_DWORD *)(uintptr_t)class_record;
  *(_BYTE *)(uintptr_t)(class_record + 20) = class_flags & 0xF7;
  ++*(_DWORD *)(uintptr_t)(symbol + 4);
  symbol = *(_DWORD *)(uintptr_t)class_record;
  *(_BYTE *)(uintptr_t)(class_record + 20) |= 3u;
  bucket_index = Class_HashClassName(symbol);
  *(_DWORD *)(uintptr_t)(class_record + 30) = bucket_index;
  Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(class_record + 46), class_record, -1);
  if ( superclass )
  {
    Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(class_record + 34), superclass, -1);
    Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(superclass + 40), class_record, -1);
    inherited_index = 1;
    inherited_class = superclass;
    while ( 1 )
    {
      Class_InsertLinkEntry((unsigned __int16 *)(uintptr_t)(class_record + 46), inherited_class, -1);
      if ( inherited_index >= *(unsigned __int16 *)(uintptr_t)(superclass + 46) )
        break;
      inherited_class = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(superclass + 48) + 4 * inherited_index);
      ++inherited_index;
    }
  }
  *(_DWORD *)(uintptr_t)(class_record + 100) = *(_DWORD *)(uintptr_t)(g_DefclassHashTable + 4 * *(_DWORD *)(uintptr_t)(class_record + 30));
  *(_DWORD *)(uintptr_t)(g_DefclassHashTable + 4 * *(_DWORD *)(uintptr_t)(class_record + 30)) = class_record;
  class_bitmap = Mem_SmallBlockAlloc(1);
  Mem_AllocArray(class_bitmap, 1);
  class_bitmap[0] |= 1u;
  expression = Rules_AddBitmapValue(class_bitmap, 1);
  Mem_SmallBlockFree((_DWORD *)class_bitmap, 1);
  *(_DWORD *)(uintptr_t)(class_record + 104) = expression;
  ++*(_DWORD *)(uintptr_t)(expression + 4);
  return class_record;
}
// 51AD68: using guessed type int dword_51AD68;

//----- (00499F20) --------------------------------------------------------
signed int Class_AllocRecord(void)
{
  _DWORD *freeListHead; // edx

  freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 48);
  if ( !freeListHead )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = *freeListHead;
  return g_ClipsMemFreeListTemp;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00499F50) --------------------------------------------------------
int  Class_FreeRecord(int theModuleItem)
{
  _DWORD *isaSlotName; // eax
  _DWORD *nameSlotName; // eax
  _DWORD *freed_node; // ecx
  int result; // eax

  Rules_ClearModuleConstructList(theModuleItem, g_ClipsDefclassConstructType, theModuleItem);
  isaSlotName = (_DWORD *)(uintptr_t)Class_FindSlotNameEntryByID(0);
  Class_ReleaseSlotName(isaSlotName);
  nameSlotName = (_DWORD *)(uintptr_t)Class_FindSlotNameEntryByID(1);
  Class_ReleaseSlotName(nameSlotName);
  freed_node = (_DWORD *)(uintptr_t)theModuleItem;
  g_ClipsMemFreeListTemp = theModuleItem;
  *freed_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 48) = g_ClipsMemFreeListTemp;
  return result;
}
// 499F7F: variable 'v3' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E6B8: using guessed type int dword_54E6B8;

//----- (00499FA0) --------------------------------------------------------
signed int Class_RefreshWatchExpressions(void)
{
  int moduleCount; // eax
  int v1; // edx
  int v2; // ecx
  int *theClass; // ebp
  _BYTE *v4; // edi
  int v5; // ebx
  _BYTE *className; // ebx
  int newBitmap; // eax
  int v9; // [esp+0h] [ebp-34h] BYREF
  _BYTE *scopeBytePtr; // [esp+4h] [ebp-30h]
  int bucketOffset; // [esp+8h] [ebp-2Ch]
  int v12 CLASH95_UNUSED; // [esp+Ch] [ebp-28h]
  int scopeBitMask; // [esp+10h] [ebp-24h]
  int bitmapSize; // [esp+14h] [ebp-20h]
  _BYTE *bitmapBuffer; // [esp+18h] [ebp-1Ch]

  Module_GetCurrent();
  moduleCount = Module_GetModuleCount();
  bitmapSize = ((moduleCount - (__CFSHL__(moduleCount >> 31, 3) + 8 * (moduleCount >> 31))) >> 3) + 1;
  bitmapBuffer = Mem_SmallBlockAlloc(bitmapSize);
  bucketOffset = 0;
  scopeBytePtr = &bitmapBuffer[(v2 - (__CFSHL__(v1 >> 31, 3) + 8 * (v1 >> 31))) >> 3];
  scopeBitMask = 1 << (v2 % 8);
  do
  {
    theClass = *(int **)(uintptr_t)(bucketOffset + g_DefclassHashTable);
    if ( theClass )
    {
      v4 = bitmapBuffer;
      do
      {
        v5 = *theClass;
        v12 = *(_DWORD *)(uintptr_t)theClass[2];
        className = *(_BYTE **)(uintptr_t)(v5 + 16);
        Mem_AllocArray(bitmapBuffer, bitmapSize);
        qmemcpy(v4, *(const void **)(uintptr_t)(theClass[26] + 16), *(unsigned __int16 *)(uintptr_t)(theClass[26] + 20));
        Rules_DecrementBitmapCount(theClass[26], 0);
        if ( (theClass[5] & 2) != 0 || Rules_FindImportExportConstruct(aDefclass, &v9, className, 1, 0) )
          *scopeBytePtr |= scopeBitMask;
        newBitmap = Rules_AddBitmapValue(bitmapBuffer, bitmapSize);
        theClass[26] = newBitmap;
        ++*(_DWORD *)(uintptr_t)(newBitmap + 4);
        theClass = (int *)(uintptr_t)theClass[25];
      }
      while ( theClass );
    }
    bucketOffset += 4;
  }
  while ( bucketOffset != 668 );
  return Mem_SmallBlockFree(bitmapBuffer, bitmapSize);
}
// 499FDD: variable 'v2' is possibly undefined
// 499FCF: variable 'v1' is possibly undefined
// 51AD68: using guessed type int dword_51AD68;

//----- (0049A0E0) --------------------------------------------------------
int __cdecl ProcParam_RegisterPrimitiveTypes(void)
{
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_ProcArgument, 65);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_ProcWildcardArgument, 66);
  Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_ProcBoundVariable, 67);
  return Rules_RegisterEvaluationHandler((int)(intptr_t)&g_EvalDescriptor_ProcBindLocalVariable, 68);
}

//----- (0049A120) --------------------------------------------------------
int  Parser_ParseProcParameters(
        int readSource,
        _DWORD *theToken,
        _DWORD *wildcardSymbol,
        int parameterList,
        _DWORD *minParamsOut,
        _DWORD *maxParamsOut,
        _DWORD *errorFlag,
        int (*checkfunc)(void))
{
  _DWORD *tokenPtr; // esi
  int paramListHead; // edi
  int i; // eax
  int j; // eax
  _DWORD *v13; // ecx
  int tokenType; // edx
  int duplicateCursor; // eax
  signed int newParamNode; // eax
  _DWORD *v17; // ecx
  int v19; // ecx
  int v20; // ecx
  int paramPrinted; // [esp+4h] [ebp-10h]

  tokenPtr = theToken;
  paramListHead = parameterList;
  *wildcardSymbol = 0;
  *minParamsOut = 0;
  paramPrinted = 0;
  *errorFlag = 1;
  for ( i = parameterList; i; i = *(_DWORD *)(uintptr_t)(i + 10) )
  {
    ++*minParamsOut;
    parameterList = i;
  }
  if ( *theToken == 100 )
  {
    for ( j = readSource; ; j = readSource )
    {
      Parser_NextToken(j, (int)(intptr_t)theToken);
      tokenType = *tokenPtr;
      if ( *tokenPtr != 15 && tokenType != 16 )
        break;
      duplicateCursor = paramListHead;
      if ( paramListHead )
      {
        while ( *(_DWORD *)(uintptr_t)(duplicateCursor + 2) != tokenPtr[1] )
        {
          duplicateCursor = *(_DWORD *)(uintptr_t)(duplicateCursor + 10);
          if ( !duplicateCursor )
            goto LABEL_9;
        }
        Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 7, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDuplicatePar_0, v19);
        AST_Free(paramListHead);
        return 0;
      }
LABEL_9:
      if ( *wildcardSymbol )
      {
        Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 8, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoParameters_0, v20);
        AST_Free(paramListHead);
        return 0;
      }
      if ( checkfunc && checkfunc() )
        goto LABEL_18;
      newParamNode = AST_NewNode(*tokenPtr, tokenPtr[1]);
      if ( *tokenPtr == 16 )
        *wildcardSymbol = tokenPtr[1];
      else
        ++*v17;
      if ( parameterList )
        *(_DWORD *)(uintptr_t)(parameterList + 10) = newParamNode;
      else
        paramListHead = newParamNode;
      parameterList = newParamNode;
      IO_OutWriteToken(asc_505C54);
      theToken = tokenPtr;
      paramPrinted = 1;
    }
    if ( tokenType != 101 )
      goto LABEL_17;
    if ( paramPrinted )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_505C58);
    }
    *errorFlag = 0;
    if ( *wildcardSymbol )
      *maxParamsOut = -1;
    else
      *maxParamsOut = *v13;
    return paramListHead;
  }
  else
  {
LABEL_17:
    Parser_ReportSyntaxError();
LABEL_18:
    AST_Free(paramListHead);
    return 0;
  }
}
// 49A282: variable 'v19' is possibly undefined
// 49A2B4: variable 'v20' is possibly undefined
// 49A2CB: variable 'v17' is possibly undefined
// 49A2DA: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (0049A2F0) --------------------------------------------------------
_DWORD * Parser_ParseProcActions(
        int bodyType,
        int readSource,
        int parameterList,
        int wildcardSymbol,
        int (*altVarFunc)(void),
        int (*altBindFunc)(void),
        int *localVarCountOut,
        int userBuffer)
{
  unsigned int *v11; // edx
  _DWORD *result; // eax
  _DWORD *actions; // esi
  int v14; // eax
  int v15; // ecx
  _DWORD *unwrappedActions; // eax
  int v17; // ecx
  int v18; // edx

  Parser_FreeLoopContextStack();
  result = (_DWORD *)(uintptr_t)Parser_ParseProgram(readSource, v11, 1);
  actions = result;
  if ( result )
  {
    if ( altBindFunc && Parser_ScanBindStatementsForSymbol((int)(intptr_t)result, altBindFunc, userBuffer) )
    {
      Parser_FreeLoopContextStack();
      v14 = v15;
    }
    else
    {
      *localVarCountOut = Rules_CountNamedContextEntries();
      if ( !Parser_ReplaceProcVars(bodyType, (int)(intptr_t)actions, wildcardSymbol, parameterList, altVarFunc, userBuffer) )
      {
        unwrappedActions = AST_UnwrapActionListWrapper(actions);
        AST_PackNodeChain(unwrappedActions);
        AST_Free(v17);
        Parser_FreeLoopContextStack();
        return (_DWORD *)(uintptr_t)v18;
      }
      Parser_FreeLoopContextStack();
      v14 = (int)(intptr_t)actions;
    }
    AST_Free(v14);
    return 0;
  }
  return result;
}
// 49A309: variable 'v11' is possibly undefined
// 49A36C: variable 'v15' is possibly undefined
// 49A382: variable 'v17' is possibly undefined
// 49A38C: variable 'v18' is possibly undefined

//----- (0049A3A0) --------------------------------------------------------
signed int  Parser_ReplaceProcVars(
        int bodyType,
        int actions,
        int wildcardSymbol,
        int parameterList,
        int (*altVarFunc)(void),
        int specData)
{
  int actionExpr; // esi
  int v8; // ecx
  signed int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  signed int v18; // eax
  _DWORD *v19; // edx
  _DWORD *varNode; // ebx
  int varFuncResult; // eax
  int bindExpr; // eax
  signed int v23; // edx
  _DWORD *v24; // eax
  signed int paramIndex; // [esp+0h] [ebp-28h] BYREF
  signed int bindIndex; // [esp+4h] [ebp-24h] BYREF
  int bitmapData; // [esp+8h] [ebp-20h] BYREF
  int savedParamList; // [esp+Ch] [ebp-1Ch]
  int savedWildcard; // [esp+10h] [ebp-18h]
  _DWORD *savedVarNode; // [esp+14h] [ebp-14h]
  int savedBodyType; // [esp+18h] [ebp-10h]

  savedBodyType = bodyType;
  actionExpr = actions;
  savedParamList = parameterList;
  savedWildcard = wildcardSymbol;
  if ( !actions )
    return 0;
  while ( 1 )
  {
    if ( *(_WORD *)(uintptr_t)actionExpr == 15 )
    {
      paramIndex = Parser_FindProcParamIndex(*(_DWORD *)(uintptr_t)(actionExpr + 2), savedParamList, savedWildcard);
      v9 = Rules_FindNamedContextDepth(v8);
      bindIndex = v9;
      if ( paramIndex || v9 )
      {
        if ( paramIndex <= 0 || bindIndex )
        {
          if ( altVarFunc )
          {
            varNode = (_DWORD *)(uintptr_t)AST_NewNode(*(_WORD *)(uintptr_t)actionExpr, *(_DWORD *)(uintptr_t)(actionExpr + 2));
            savedVarNode = varNode;
            varFuncResult = altVarFunc();
            if ( varFuncResult )
            {
              if ( varFuncResult == -1 )
              {
                g_ClipsMemFreeListTemp = (int)(intptr_t)varNode;
                *varNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
                *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
                return 1;
              }
            }
            else
            {
              g_ClipsMemFreeListTemp = (int)(intptr_t)varNode;
              *varNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
              savedVarNode = 0;
              *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
            }
          }
          else
          {
            savedVarNode = 0;
          }
          *(_WORD *)(uintptr_t)actionExpr = 67;
          Mem_AllocArray(&bitmapData, 4);
          LOWORD(bitmapData) = bitmapData & 1;
          bitmapData |= 2 * (bindIndex & 0x7FFF);
          HIWORD(bitmapData) = BYTE2(bitmapData) & 1;
          bitmapData |= (paramIndex & 0x7FFF) << 17;
          BYTE2(bitmapData) &= ~1u;
          bitmapData |= (v16 == savedWildcard) << 16;
          *(_DWORD *)(uintptr_t)(actionExpr + 2) = Rules_AddBitmapValue(&bitmapData, 4);
          v18 = AST_NewNode(2, v17);
          v19 = savedVarNode;
          *(_DWORD *)(uintptr_t)(actionExpr + 6) = v18;
          *(_DWORD *)(uintptr_t)(v18 + 10) = v19;
        }
        else
        {
          *(_WORD *)(uintptr_t)actionExpr = (v10 == savedWildcard) + 65;
          *(_DWORD *)(uintptr_t)(actionExpr + 2) = Rules_AddBitmapValue(&paramIndex, 4);
        }
      }
      else if ( !altVarFunc || altVarFunc() != 1 )
      {
        Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 3, 1);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUndefinedVaria, v11);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(v12 + 16), v12);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aReferencedIn, v13);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], savedBodyType, v14);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_ExpressionError, v15);
        return 1;
      }
    }
    else if ( *(_WORD *)(uintptr_t)actionExpr == 13 && !Defglobal_ResolveGlobalVariableReference(actionExpr, wildcardSymbol) )
    {
      return -1;
    }
    if ( altVarFunc && ((int (__fastcall *)(int, int))altVarFunc)(wildcardSymbol, specData) == -1 )
      return 1;
    wildcardSymbol = *(_DWORD *)(uintptr_t)(actionExpr + 6);
    if ( wildcardSymbol )
      break;
LABEL_6:
    actionExpr = *(_DWORD *)(uintptr_t)(actionExpr + 10);
    if ( !actionExpr )
      return 0;
  }
  if ( !Parser_ReplaceProcVars(savedBodyType, wildcardSymbol, savedWildcard, savedParamList, (int (__fastcall *)(_DWORD, _DWORD))altVarFunc, specData) )
  {
    if ( Rules_MakeSymbol(aBind_1) == *(int ***)(uintptr_t)(actionExpr + 2) && **(_WORD **)(uintptr_t)(actionExpr + 6) == 2 )
    {
      bindExpr = *(_DWORD *)(uintptr_t)(actionExpr + 6);
      *(_WORD *)(uintptr_t)actionExpr = 68;
      bindIndex = Rules_FindNamedContextDepth(*(_DWORD *)(uintptr_t)(bindExpr + 2));
      *(_DWORD *)(uintptr_t)(actionExpr + 2) = Rules_AddBitmapValue(&bindIndex, v23);
      v24 = *(_DWORD **)(uintptr_t)(actionExpr + 6);
      wildcardSymbol = *(_DWORD *)((char *)v24 + 10);
      g_ClipsMemFreeListTemp = (int)(intptr_t)v24;
      *v24 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
      *(_DWORD *)(uintptr_t)(actionExpr + 6) = wildcardSymbol;
    }
    goto LABEL_6;
  }
  return 1;
}
// 49A40F: variable 'v8' is possibly undefined
// 49A460: variable 'v11' is possibly undefined
// 49A46A: variable 'v12' is possibly undefined
// 49A47C: variable 'v13' is possibly undefined
// 49A48A: variable 'v14' is possibly undefined
// 49A499: variable 'v15' is possibly undefined
// 49A531: variable 'v16' is possibly undefined
// 49A55D: variable 'v17' is possibly undefined
// 49A578: variable 'v10' is possibly undefined
// 49A610: variable 'a3' is possibly undefined
// 49A6B4: variable 'v23' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049A6F0) --------------------------------------------------------
signed int  AST_NewProcParamNode(int paramIndex)
{
  int bitmapValue; // eax
  int bitmapData; // [esp+0h] [ebp-8h] BYREF

  bitmapData = paramIndex;
  bitmapValue = Rules_AddBitmapValue(&bitmapData, 4);
  return AST_NewNode(66, bitmapValue);
}

//----- (0049A720) --------------------------------------------------------
int (* ProcParam_PushEvaluatedArgumentFrame(
        _DWORD *a1,
        int a2,
        int a3,
        int a4,
        double a5,
        int (*a6)(void)))(void)
{
  _DWORD *v7; // ebp
  _DWORD *v8; // esi
  _DWORD *v9; // esi
  int (*result)(void); // eax

  v7 = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 96);
  if ( v7 )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *v7;
    v8 = (_DWORD *)(uintptr_t)g_ClipsMemFreeListTemp;
  }
  else
  {
    v8 = (_DWORD *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  *v8 = g_ClipsProcParamArray;
  v8[2] = g_ClipsProcParamCount;
  v8[4] = g_ProcParam_ErrorContextCallback;
  v8[5] = g_ProcParamSavedFrameStack;
  g_ProcParamSavedFrameStack = (int)(intptr_t)v8;
  ProcParam_EvaluateArgumentExpressions(a1, a2, a3, a4, a5);
  if ( g_ClipsEvaluationError )
  {
    v9 = (_DWORD *)(uintptr_t)g_ProcParamSavedFrameStack;
    g_ProcParamSavedFrameStack = *(_DWORD *)(uintptr_t)(g_ProcParamSavedFrameStack + 20);
    g_ClipsMemFreeListTemp = (int)(intptr_t)v9;
    *v9 = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    result = (int (*)(void))(uintptr_t)g_ClipsMemFreeListTemp;
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  }
  else
  {
    v8[1] = g_Clips_ProcParamArgChain;
    g_Clips_ProcParamArgChain = 0;
    v8[3] = g_ClipsProcParamWildcardValue;
    result = a6;
    g_ClipsProcParamWildcardValue = 0;
    g_ProcParam_ErrorContextCallback = a6;
  }
  return result;
}
// 49A76B: variable 'a3' is possibly undefined
// 51A964: using guessed type int dword_51A964;
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;
// 51ABC4: using guessed type int dword_51ABC4;
// 51ABC8: using guessed type int dword_51ABC8;
// 51ABD0: using guessed type int (*dword_51ABD0)(void);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049A7F0) --------------------------------------------------------
int ProcParam_PopFrame(void)
{
  int *frameNode; // edx
  int result; // eax

  if ( g_ClipsProcParamArray )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_ClipsProcParamArray, 24 * g_ClipsProcParamCount);
  if ( g_Clips_ProcParamArgChain )
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_Clips_ProcParamArgChain, 14 * g_ClipsProcParamCount);
  frameNode = (int *)(uintptr_t)g_ProcParamSavedFrameStack;
  g_ProcParamSavedFrameStack = *(_DWORD *)(uintptr_t)(g_ProcParamSavedFrameStack + 20);
  g_ClipsProcParamArray = *frameNode;
  g_ClipsProcParamCount = frameNode[2];
  g_Clips_ProcParamArgChain = frameNode[1];
  if ( g_ClipsProcParamWildcardValue )
  {
    Rules_DeinstallMultifield(*(__int16 **)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
    g_ClipsMemFreeListTemp = g_ClipsProcParamWildcardValue;
    *(_DWORD *)(uintptr_t)g_ClipsProcParamWildcardValue = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  }
  g_ClipsProcParamWildcardValue = frameNode[3];
  g_ProcParam_ErrorContextCallback = (int (*)(void))(uintptr_t)frameNode[4];
  g_ClipsMemFreeListTemp = (int)(intptr_t)frameNode;
  *frameNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
  result = g_ClipsMemoryTable;
  *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
  return result;
}
// 49A853: variable 'v0' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;
// 51ABC4: using guessed type int dword_51ABC4;
// 51ABC8: using guessed type int dword_51ABC8;
// 51ABD0: using guessed type int (*dword_51ABD0)(void);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049A8F0) --------------------------------------------------------
int ProcParam_BuildArgumentExpressionChain(void)
{
  int srcParamOffset; // ecx
  int paramIndex; // edx
  int chainOffset; // eax
  int valueSlot; // ebx
  int nextIndex; // ebx
  int nextLink; // ebx

  if ( !g_ClipsProcParamArray || g_Clips_ProcParamArgChain )
    return g_Clips_ProcParamArgChain;
  g_Clips_ProcParamArgChain = (int)(intptr_t)Mem_SmallBlockAlloc(14 * g_ClipsProcParamCount);
  paramIndex = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    chainOffset = 0;
    do
    {
      *(_WORD *)(uintptr_t)(g_Clips_ProcParamArgChain + chainOffset) = *(_WORD *)(uintptr_t)(g_ClipsProcParamArray + srcParamOffset + 4);
      valueSlot = srcParamOffset + g_ClipsProcParamArray;
      if ( *(_DWORD *)(uintptr_t)(srcParamOffset + g_ClipsProcParamArray + 4) != 4 )
        valueSlot = *(_DWORD *)(uintptr_t)(valueSlot + 8);
      *(_DWORD *)(uintptr_t)(g_Clips_ProcParamArgChain + chainOffset + 2) = valueSlot;
      *(_DWORD *)(uintptr_t)(g_Clips_ProcParamArgChain + chainOffset + 6) = 0;
      nextIndex = paramIndex + 1;
      if ( paramIndex + 1 == g_ClipsProcParamCount )
        nextLink = g_ClipsProcParamCount ^ nextIndex;
      else
        nextLink = g_Clips_ProcParamArgChain + 14 * nextIndex;
      srcParamOffset += 24;
      *(_DWORD *)(uintptr_t)(g_Clips_ProcParamArgChain + chainOffset + 10) = nextLink;
      ++paramIndex;
      chainOffset += 14;
    }
    while ( paramIndex < g_ClipsProcParamCount );
  }
  return g_Clips_ProcParamArgChain;
}
// 49A949: variable 'v1' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC0: using guessed type int dword_51ABC0;

//----- (0049A9E0) --------------------------------------------------------
int  Rules_ExecuteRuleActions(
        int theModule,
        __int16 *actions,
        _DWORD *returnValue,
        int localVarCount,
        double context,
        void (*crtproc)(void))
{
  _DWORD *localVarArray; // eax
  int slotOffset; // eax
  int arrayByteSize; // ebx
  _DWORD *varSlot; // ecx
  int saved_module; // ecx
  int currentModule; // eax
  int v16; // ecx
  int wildcardValue; // ecx
  int varOffset; // edx
  int result; // eax
  int savedLocalVarArray; // [esp+0h] [ebp-14h]

  savedLocalVarArray = g_ClipsProcFrameDataObjectArray;
  if ( localVarCount )
    localVarArray = Mem_SmallBlockAlloc(24 * localVarCount);
  else
    localVarArray = 0;
  g_ClipsProcFrameDataObjectArray = (int)(intptr_t)localVarArray;
  if ( localVarCount > 0 )
  {
    slotOffset = 0;
    arrayByteSize = 24 * localVarCount;
    do
    {
      varSlot = (_DWORD *)(uintptr_t)(g_ClipsProcFrameDataObjectArray + slotOffset);
      slotOffset += 24;
      *varSlot = g_ClipsFalseSymbol;
    }
    while ( slotOffset < arrayByteSize );
  }
  saved_module = Module_GetCurrent();
  if ( saved_module != theModule )
    Module_SetCurrent(theModule);
  if ( Parser_ParseForm(actions, returnValue, saved_module, context) )
  {
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
  }
  currentModule = Module_GetCurrent();
  if ( saved_module != currentModule )
    Module_SetCurrent(saved_module);
  if ( crtproc && g_ClipsHaltExecution )
  {
    Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 4, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExecutionHal_0, v16);
    crtproc();
  }
  wildcardValue = g_ClipsProcParamWildcardValue;
  if ( g_ClipsProcParamWildcardValue && returnValue[2] == *(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 8) )
  {
    Rules_DeinstallMultifield(*(__int16 **)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
    g_ClipsMemFreeListTemp = g_ClipsProcParamWildcardValue;
    *(_DWORD *)(uintptr_t)g_ClipsProcParamWildcardValue = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
    *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = g_ClipsMemFreeListTemp;
    g_ClipsProcParamWildcardValue = 0;
  }
  if ( localVarCount )
  {
    if ( localVarCount > 0 )
    {
      varOffset = 0;
      do
      {
        if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(varOffset + g_ClipsProcFrameDataObjectArray) )
          Rules_ValueDeinstall(varOffset + g_ClipsProcFrameDataObjectArray, wildcardValue);
        varOffset += 24;
      }
      while ( varOffset < 24 * localVarCount );
    }
    Mem_SmallBlockFree((_DWORD *)(uintptr_t)g_ClipsProcFrameDataObjectArray, 24 * localVarCount);
  }
  result = savedLocalVarArray;
  g_ClipsProcFrameDataObjectArray = savedLocalVarArray;
  return result;
}
// 49AAAB: variable 'v16' is possibly undefined
// 49AB3B: variable 'v17' is possibly undefined
// 49AB40: variable 'v18' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A968: using guessed type int dword_51A968;
// 51ABC8: using guessed type int dword_51ABC8;
// 51ABCC: using guessed type int dword_51ABCC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049AB90) --------------------------------------------------------
signed int  ProcParam_PrintArguments(int logicalName)
{
  int v1; // ecx
  int paramIndex; // ebx
  int paramOffset; // esi

  Output_Write(logicalName, (int)(intptr_t)asc_505CB4, logicalName);
  paramIndex = 0;
  if ( g_ClipsProcParamCount > 0 )
  {
    paramOffset = 0;
    do
    {
      Rules_PrintDataObject(v1, paramOffset + g_ClipsProcParamArray);
      if ( paramIndex != g_ClipsProcParamCount - 1 )
        Output_Write(v1, (int)(intptr_t)asc_505C54, v1);
      ++paramIndex;
      paramOffset += 24;
    }
    while ( paramIndex < g_ClipsProcParamCount );
  }
  return Output_Write(v1, (int)(intptr_t)asc_505CB8, v1);
}
// 49ABB9: variable 'v1' is possibly undefined
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;

//----- (0049AC00) --------------------------------------------------------
__int16 * ProcParam_BuildWildcardMultifield(_DWORD *returnValue, int theIndex)
{
  _DWORD *freeListHead; // ebx
  signed int newWildcardRec; // eax
  signed int size; // esi
  int startIndex; // ebx
  int paramByteOffset; // eax
  _DWORD *theMultifield; // eax
  int destFieldIndex; // esi
  int srcRecord; // eax
  int paramRecord; // ebx
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  __int16 *result; // eax
  int wildcardRec; // eax
  _DWORD *emptyMultifield; // eax
  int fieldByteOffset; // edx
  int paramIndex; // [esp+0h] [ebp-18h]
  int paramOffset; // [esp+4h] [ebp-14h]

  returnValue[1] = 4;
  returnValue[3] = 0;
  if ( g_ClipsProcParamWildcardValue )
  {
    if ( theIndex == g_ProcParamCachedWildcardArgIndex )
    {
      returnValue[4] = *(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 16);
      result = *(__int16 **)(uintptr_t)(g_ClipsProcParamWildcardValue + 8);
      returnValue[2] = result;
      return result;
    }
    Rules_DeinstallMultifield(*(__int16 **)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
    Rules_RegisterEphemeralMultifield(*(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
  }
  else
  {
    freeListHead = *(_DWORD **)(uintptr_t)(g_ClipsMemoryTable + 96);
    if ( freeListHead )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 96) = *freeListHead;
      newWildcardRec = g_ClipsMemFreeListTemp;
    }
    else
    {
      newWildcardRec = Mem_HeapAllocWithRetry((_DWORD *)0x18);
    }
    g_ClipsProcParamWildcardValue = newWildcardRec;
    *(_DWORD *)(uintptr_t)(newWildcardRec + 12) = 0;
  }
  size = g_ClipsProcParamCount - theIndex + 1;
  g_ProcParamCachedWildcardArgIndex = theIndex;
  if ( size <= 0 )
  {
    wildcardRec = g_ClipsProcParamWildcardValue;
    *(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 16) = -1;
    returnValue[4] = *(_DWORD *)(uintptr_t)(wildcardRec + 16);
    emptyMultifield = Rules_CreateMultifield(0);
    *(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 8) = emptyMultifield;
    returnValue[2] = emptyMultifield;
    return Rules_InstallMultifield(*(__int16 **)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
  }
  else
  {
    startIndex = theIndex - 1;
    if ( theIndex - 1 < g_ClipsProcParamCount )
    {
      paramByteOffset = 24 * startIndex;
      do
      {
        if ( *(_DWORD *)(uintptr_t)(paramByteOffset + g_ClipsProcParamArray + 4) == 4 )
          size += *(_DWORD *)(uintptr_t)(paramByteOffset + g_ClipsProcParamArray + 16) - *(_DWORD *)(uintptr_t)(paramByteOffset + g_ClipsProcParamArray + 12);
        paramByteOffset += 24;
        ++startIndex;
      }
      while ( paramByteOffset < 24 * g_ClipsProcParamCount );
    }
    *(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 16) = size - 1;
    returnValue[4] = size - 1;
    theMultifield = Rules_CreateMultifield(size);
    *(_DWORD *)(uintptr_t)(g_ClipsProcParamWildcardValue + 8) = theMultifield;
    paramIndex = theIndex - 1;
    returnValue[2] = theMultifield;
    destFieldIndex = 1;
    if ( theIndex - 1 < g_ClipsProcParamCount )
    {
      paramOffset = 24 * (theIndex - 1);
      do
      {
        srcRecord = paramOffset + g_ClipsProcParamArray;
        if ( *(_DWORD *)(uintptr_t)(paramOffset + g_ClipsProcParamArray + 4) == 4 )
        {
          paramRecord = paramOffset + g_ClipsProcParamArray;
          v12 = *(_DWORD *)(uintptr_t)(srcRecord + 12) + 1;
          v13 = 6 * destFieldIndex - 6;
          v14 = 6 * v12 - 6;
          while ( v12 <= *(_DWORD *)(uintptr_t)(paramRecord + 16) + 1 )
          {
            v14 += 6;
            ++v12;
            *(_WORD *)(uintptr_t)(v13 + returnValue[2] + 14) = *(_WORD *)(uintptr_t)(v14 + *(_DWORD *)(uintptr_t)(paramRecord + 8) + 8);
            v13 += 6;
            ++destFieldIndex;
            *(_DWORD *)(uintptr_t)(v13 + returnValue[2] + 10) = *(_DWORD *)(uintptr_t)(v14 + *(_DWORD *)(uintptr_t)(paramRecord + 8) + 10);
          }
        }
        else
        {
          fieldByteOffset = 6 * (destFieldIndex - 1);
          *(_WORD *)(uintptr_t)(returnValue[2] + fieldByteOffset + 14) = *(_WORD *)(uintptr_t)(srcRecord + 4);
          ++destFieldIndex;
          *(_DWORD *)(uintptr_t)(returnValue[2] + fieldByteOffset + 16) = *(_DWORD *)(uintptr_t)(g_ClipsProcParamArray + paramOffset + 8);
        }
        paramOffset += 24;
        ++paramIndex;
      }
      while ( paramIndex < g_ClipsProcParamCount );
    }
    return Rules_InstallMultifield(*(__int16 **)(uintptr_t)(g_ClipsProcParamWildcardValue + 8));
  }
}
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;
// 51ABC8: using guessed type int dword_51ABC8;
// 51AC94: using guessed type int dword_51AC94;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (0049AE70) --------------------------------------------------------
_DWORD * ProcParam_EvaluateArgumentExpressions(uintptr_t result, int numberOfParameters, int functionName, int bodyType, double context)
{
  uintptr_t expression; // esi
  _DWORD *argument_values; // eax
  _DWORD *argument_slot; // ecx
  _DWORD parsed[6]; // [esp+0h] [ebp-2Ch] BYREF

  expression = result;
  if ( numberOfParameters )
  {
    argument_values = Mem_SmallBlockAlloc(24 * numberOfParameters);
    if ( expression )
    {
      argument_slot = argument_values;
      while ( Parser_ParseForm((__int16 *)expression, parsed, (int)(uintptr_t)argument_slot, context) != 1 && parsed[1] != 105 )
      {
        argument_slot[1] = parsed[1];
        argument_slot[2] = parsed[2];
        argument_slot[3] = parsed[3];
        argument_slot[4] = parsed[4];
        expression = (uintptr_t)(unsigned int)*(_DWORD *)(expression + 10);
        argument_slot += 6;
        if ( !expression )
          goto LABEL_11;
      }
      if ( parsed[1] == 105 )
      {
        Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 2, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFunctionsWitho, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, 0);
        Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aArguments__0, 0);
        Lexer_ErrorRecover(1);
      }
      Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 6, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aThisErrorOcc_3, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aForThe, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)asc_505C54, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], bodyType, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_ExpressionError, 0);
      return (_DWORD *)(uintptr_t)Mem_SmallBlockFree(argument_values, 24 * numberOfParameters);
    }
    else
    {
LABEL_11:
      result = (uintptr_t)argument_values;
      g_ClipsProcParamCount = numberOfParameters;
      g_ClipsProcParamArray = (int)(uintptr_t)argument_values;
    }
  }
  else
  {
    g_ClipsProcParamArray = 0;
    g_ClipsProcParamCount = 0;
  }
  return (_DWORD *)result;
}
// 49AEEE: variable 'v11' is possibly undefined
// 49AEFA: variable 'v12' is possibly undefined
// 49AF09: variable 'v13' is possibly undefined
// 49AF33: variable 'v14' is possibly undefined
// 49AF42: variable 'v15' is possibly undefined
// 49AF4E: variable 'v16' is possibly undefined
// 49AF5D: variable 'v17' is possibly undefined
// 49AF6B: variable 'v18' is possibly undefined
// 49AF7A: variable 'v19' is possibly undefined
// 49AFB6: variable 'v10' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABBC: using guessed type int dword_51ABBC;

//----- (0049B000) --------------------------------------------------------
signed int  ProcParam_GetArgumentValue(int theValue, _DWORD *returnValue)
{
  int payload; // eax
  int record; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  record = g_ClipsProcParamArray + 24 * (*(_DWORD *)(uintptr_t)(unsigned int)payload - 1);
  returnValue[1] = *(_DWORD *)((uintptr_t)(unsigned int)record + 4);
  returnValue[2] = *(_DWORD *)((uintptr_t)(unsigned int)record + 8);
  returnValue[3] = *(_DWORD *)((uintptr_t)(unsigned int)record + 12);
  returnValue[4] = *(_DWORD *)((uintptr_t)(unsigned int)record + 16);
  return 1;
}
// 51ABB8: using guessed type int dword_51ABB8;

//----- (0049B040) --------------------------------------------------------
signed int  ProcParam_GetBoundVariableValue(int theValue, _DWORD *returnValue, double context)
{
  int payload; // edx
  int record; // eax
  int expression; // eax
  unsigned int raw_index; // eax

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  raw_index = *(_DWORD *)(uintptr_t)(unsigned int)payload;
  record = g_ClipsProcFrameDataObjectArray + 24 * ((((unsigned int)raw_index << 16) >> 17) - 1);
  if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(unsigned int)record )
    goto LABEL_6;
  expression = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( *(_DWORD *)((uintptr_t)(unsigned int)expression + 10) )
  {
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)expression + 10), returnValue, (int)(uintptr_t)returnValue, context);
    return 1;
  }
  if ( (*(_WORD *)((uintptr_t)(unsigned int)payload + 2) & 0xFFFE) != 0 )
  {
    if ( (*(_BYTE *)((uintptr_t)(unsigned int)payload + 2) & 1) == 0 )
    {
      record = 24 * ((raw_index >> 17) - 1) + g_ClipsProcParamArray;
LABEL_6:
      returnValue[1] = *(_DWORD *)((uintptr_t)(unsigned int)record + 4);
      returnValue[2] = *(_DWORD *)((uintptr_t)(unsigned int)record + 8);
      returnValue[3] = *(_DWORD *)((uintptr_t)(unsigned int)record + 12);
      returnValue[4] = *(_DWORD *)((uintptr_t)(unsigned int)record + 16);
      return 1;
    }
    ProcParam_BuildWildcardMultifield(returnValue, raw_index >> 17);
    return 1;
  }
  else
  {
    Rules_PrintErrorID((int)(intptr_t)aPrccode_0, 5, 0);
    Lexer_ErrorRecover(1);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aVariable, 0);
    Output_Write(
      (int)(intptr_t)g_IO_LogicalNameTable_WError[0],
      *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)expression + 2) + 16),
      0);
    if ( g_ProcParam_ErrorContextCallback )
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnboundIn, 0);
      g_ProcParam_ErrorContextCallback();
    }
    else
    {
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnbound_, 0);
    }
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return 1;
  }
}
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;
// 51ABB8: using guessed type int dword_51ABB8;
// 51ABCC: using guessed type int dword_51ABCC;
// 51ABD0: using guessed type int (*dword_51ABD0)(void);
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B190) --------------------------------------------------------
signed int  ProcParam_BindLocalVariable(int theValue, _DWORD *returnValue, double context)
{
  int payload; // eax
  int record; // ecx
  int expression; // edx

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  record = g_ClipsProcFrameDataObjectArray + 24 * (*(_DWORD *)(uintptr_t)(unsigned int)payload - 1);
  expression = *(_DWORD *)((uintptr_t)(unsigned int)g_ClipsCurrentExpression + 6);
  if ( !expression )
  {
    if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(unsigned int)record )
      Rules_ValueDeinstall(record, record);
    *(_DWORD *)(uintptr_t)(unsigned int)record = g_ClipsFalseSymbol;
    returnValue[1] = 2;
    returnValue[2] = g_ClipsFalseSymbol;
    return 1;
  }
  if ( *(_DWORD *)((uintptr_t)(unsigned int)expression + 10) )
    Rules_StoreEvaluatedNodesAsMultifield(returnValue, expression, 1, context);
  else
    Parser_ParseForm((__int16 *)(uintptr_t)(unsigned int)expression, returnValue, record, context);
  if ( g_ClipsTrueSymbol == *(_DWORD *)(uintptr_t)(unsigned int)record )
    Rules_ValueDeinstall(record, record);
  *(_DWORD *)(uintptr_t)(unsigned int)record = g_ClipsTrueSymbol;
  *(_DWORD *)((uintptr_t)(unsigned int)record + 4) = returnValue[1];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 8) = returnValue[2];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 12) = returnValue[3];
  *(_DWORD *)((uintptr_t)(unsigned int)record + 16) = returnValue[4];
  Rules_ValueInstall(record, record);
  return 1;
}
// 51A960: using guessed type int dword_51A960;
// 51ABCC: using guessed type int dword_51ABCC;
// 54DD64: using guessed type int dword_54DD64;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B250) --------------------------------------------------------
signed int  ProcParam_GetWildcardArgumentValue(int theValue, _DWORD *returnValue)
{
  int payload; // edx

  payload = *(_DWORD *)((uintptr_t)(unsigned int)theValue + 16);
  ProcParam_BuildWildcardMultifield(returnValue, *(_DWORD *)(uintptr_t)(unsigned int)payload);
  return 1;
}

//----- (0049B270) --------------------------------------------------------
signed int  Parser_FindProcParamIndex(int variableSymbol, int parameterList, int wildcardSymbol)
{
  signed int result; // eax

  result = 1;
  if ( parameterList )
  {
    while ( variableSymbol != *(_DWORD *)(uintptr_t)(parameterList + 2) )
    {
      parameterList = *(_DWORD *)(uintptr_t)(parameterList + 10);
      ++result;
      if ( !parameterList )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    if ( variableSymbol != wildcardSymbol )
      return 0;
  }
  return result;
}

//----- (0049B2A0) --------------------------------------------------------
signed int  Parser_ScanBindStatementsForSymbol(int actions, int (*altBindFunc)(void), int userBuffer)
{
  int exprCursor; // ecx
  int **Symbol; // eax
  int bindArgs; // eax
  int bindSymbol; // ebx
  int bindCode; // eax
  int v11; // ecx

  exprCursor = actions;
  if ( !actions )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( *(_DWORD *)(uintptr_t)(exprCursor + 6) )
      {
        if ( Parser_ScanBindStatementsForSymbol(*(_DWORD *)(uintptr_t)(exprCursor + 6), (int (__fastcall *)(_DWORD, _DWORD))altBindFunc, userBuffer) )
          return 1;
        Symbol = Rules_MakeSymbol(aBind_1);
        if ( Symbol == *(int ***)(uintptr_t)(exprCursor + 2) )
        {
          bindArgs = *(_DWORD *)(uintptr_t)(exprCursor + 6);
          if ( *(_WORD *)(uintptr_t)bindArgs == 2 )
          {
            bindSymbol = *(_DWORD *)(uintptr_t)(bindArgs + 2);
            bindCode = altBindFunc();
            if ( bindCode == -1 )
              return 1;
            if ( bindCode == 1 )
              break;
          }
        }
      }
      exprCursor = *(_DWORD *)(uintptr_t)(exprCursor + 10);
      if ( !exprCursor )
        return 0;
    }
    Rules_RemoveNamedContextEntry(bindSymbol);
    exprCursor = *(_DWORD *)(uintptr_t)(v11 + 10);
  }
  while ( exprCursor );
  return 0;
}
// 49B2B4: variable 'v3' is possibly undefined
// 49B30B: variable 'v11' is possibly undefined

//----- (0049B320) --------------------------------------------------------
_DWORD * AST_UnwrapActionListWrapper(_DWORD *result)
{
  int childExpr; // edx
  _DWORD *wrapperNode; // ecx

  childExpr = *(_DWORD *)((char *)result + 6);
  if ( childExpr )
  {
    if ( !*(_DWORD *)(uintptr_t)(childExpr + 10) )
    {
      wrapperNode = result;
      result = *(_DWORD **)((char *)result + 6);
      g_ClipsMemFreeListTemp = (int)(intptr_t)wrapperNode;
      *wrapperNode = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 56) = g_ClipsMemFreeListTemp;
    }
  }
  else
  {
    *(_WORD *)result = 2;
    *(_DWORD *)((char *)result + 2) = g_ClipsFalseSymbol;
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54DD70: using guessed type int dword_54DD70;

//----- (0049B370) --------------------------------------------------------
signed int Rules_RegisterFileIOCommands(void)
{
  Rules_RegisterHostFunction(aBatch, 98, (int)(intptr_t)aBatchcommand, (int)(intptr_t)Rules_BatchCommand, (int)(intptr_t)a11k_4);
  Rules_RegisterHostFunction(aBatch_0, 98, (int)(intptr_t)aBatchstarcomma, (int)(intptr_t)Rules_BatchStarCommand, (int)(intptr_t)a11k_4);
  Rules_RegisterHostFunction(aDribbleOn, 98, (int)(intptr_t)aDribbleoncomma, (int)(intptr_t)Rules_DribbleOnCommand, (int)(intptr_t)a11k_4);
  Rules_RegisterHostFunction(aDribbleOff, 98, (int)(intptr_t)aDribbleoffcomm, (int)(intptr_t)Rules_DribbleOffCommand, (int)(intptr_t)a00_4);
  Rules_RegisterHostFunction(aSave, 98, (int)(intptr_t)aSavecommand, (int)(intptr_t)Rules_SaveCommand, (int)(intptr_t)a11k_4);
  Rules_RegisterHostFunction(aLoad, 98, (int)(intptr_t)aLoadcommand, (int)(intptr_t)Rules_LoadCommand, (int)(intptr_t)a11k_4);
  Rules_RegisterHostFunction(aLoad_0, 98, (int)(intptr_t)aLoadstarcomman, (int)(intptr_t)Rules_LoadStarCommand, (int)(intptr_t)a11k_4);
  Rules_RegisterHostFunction(aBsave, 98, (int)(intptr_t)aBsavecommand, (int)(intptr_t)Rules_BsaveCommand, (int)(intptr_t)a11k_4);
  return Rules_RegisterHostFunction(aBload_1, 98, (int)(intptr_t)aBloadcommand, (int)(intptr_t)Rules_BloadCommand, (int)(intptr_t)a11k_4);
}

//----- (0049B490) --------------------------------------------------------
BOOL  Dribble_QueryRouter(int logicalName)
{
  int v1; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  return !strcmp_(logicalName, aStdout_2)
      || !strcmp_(v1, aStdin_2)
      || !strcmp_(v3, g_IO_LogicalNameTable_WClips[0])
      || !strcmp_(v4, g_IO_LogicalNameTable_WTrace[0])
      || !strcmp_(v5, g_IO_LogicalNameTable_WError[0])
      || !strcmp_(v6, g_IO_LogicalNameTable_WWarning[0])
      || !strcmp_(v7, g_IO_LogicalName_WDisplay)
      || !strcmp_(v8, g_IO_LogicalNameTable_WDialog[0]);
}
// 49B4B1: variable 'v1' is possibly undefined
// 49B4C2: variable 'v3' is possibly undefined
// 49B4D3: variable 'v4' is possibly undefined
// 49B4E4: variable 'v5' is possibly undefined
// 49B4F5: variable 'v6' is possibly undefined
// 49B506: variable 'v7' is possibly undefined
// 49B517: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A620: using guessed type char *off_51A620[2];
// 51A624: using guessed type char *off_51A624;
