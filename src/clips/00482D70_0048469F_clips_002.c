/* Generated from src/recovered/rules/clips/00481720_language_part2.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00482D70) --------------------------------------------------------
int  Rules_SetAtomicValueIndices(int setAll)
{
  int symbolIndex; // ecx
  int **symbolBucket; // esi
  int symbolTableEnd; // edi
  int *i; // eax
  int symbolFlags; // ebp
  int floatIndex; // ecx
  int **floatBucket; // esi
  int floatTableEnd; // edi
  int *j; // eax
  int floatFlags; // ebp
  int integerIndex; // ecx
  int **integerBucket; // esi
  int integerTableEnd; // edi
  int *k; // eax
  int integerFlags; // ebp
  int bitmapIndex; // ecx
  int *bitmapBucket; // esi
  int bitmapTableEnd; // edi
  int result; // eax
  int bitmapFlags; // ebp

  symbolIndex = 0;
  symbolBucket = (int **)(uintptr_t)g_Clips_SymbolHashTable;
  symbolTableEnd = g_Clips_SymbolHashTable + 4052;
  do
  {
    for ( i = *symbolBucket; i; i = (int *)(uintptr_t)*i )
    {
      if ( (i[3] & 2) != 0 || setAll )
      {
        *((_BYTE *)i + 13) = 0;
        *((_BYTE *)i + 12) &= 3u;
        symbolFlags = (4 * (symbolIndex++ & 0x3FFF)) | i[3];
        i[3] = symbolFlags;
      }
    }
    ++symbolBucket;
  }
  while ( symbolBucket != (int **)(uintptr_t)symbolTableEnd );
  floatIndex = 0;
  floatBucket = (int **)(uintptr_t)g_ClipsFloatHashTable;
  floatTableEnd = g_ClipsFloatHashTable + 2012;
  do
  {
    for ( j = *floatBucket; j; j = (int *)(uintptr_t)*j )
    {
      if ( (j[3] & 2) != 0 || setAll )
      {
        *((_BYTE *)j + 13) = 0;
        *((_BYTE *)j + 12) &= 3u;
        floatFlags = (4 * (floatIndex++ & 0x3FFF)) | j[3];
        j[3] = floatFlags;
      }
    }
    ++floatBucket;
  }
  while ( floatBucket != (int **)(uintptr_t)floatTableEnd );
  integerIndex = 0;
  integerBucket = (int **)(uintptr_t)g_ClipsIntegerHashTable;
  integerTableEnd = g_ClipsIntegerHashTable + 668;
  do
  {
    for ( k = *integerBucket; k; k = (int *)(uintptr_t)*k )
    {
      if ( (k[3] & 2) != 0 || setAll )
      {
        *((_BYTE *)k + 13) = 0;
        *((_BYTE *)k + 12) &= 3u;
        integerFlags = (4 * (integerIndex++ & 0x3FFF)) | k[3];
        k[3] = integerFlags;
      }
    }
    ++integerBucket;
  }
  while ( integerBucket != (int **)(uintptr_t)integerTableEnd );
  bitmapIndex = 0;
  bitmapBucket = (int *)(uintptr_t)g_ClipsBitmapHashTable;
  bitmapTableEnd = g_ClipsBitmapHashTable + 668;
  do
  {
    for ( result = *bitmapBucket; result; result = *(_DWORD *)(uintptr_t)result )
    {
      if ( (*(_BYTE *)(uintptr_t)(result + 12) & 2) != 0 || setAll )
      {
        *(_BYTE *)(uintptr_t)(result + 13) = 0;
        *(_BYTE *)(uintptr_t)(result + 12) &= 3u;
        bitmapFlags = (4 * (bitmapIndex++ & 0x3FFF)) | *(_DWORD *)(uintptr_t)(result + 12);
        *(_DWORD *)(uintptr_t)(result + 12) = bitmapFlags;
      }
    }
    ++bitmapBucket;
  }
  while ( bitmapBucket != (int *)(uintptr_t)bitmapTableEnd );
  return result;
}
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00482EF0) --------------------------------------------------------
int *Rules_RestoreAtomicValueBuckets(void)
{
  _DWORD *symbolBucket; // ebx
  int i; // ecx
  _DWORD *symbolNode; // eax
  unsigned int symbolFlags; // ebp
  _DWORD *floatBucket; // ebx
  int j; // ecx
  _DWORD *floatNode; // eax
  unsigned int floatFlags; // ebp
  _DWORD *integerBucket; // ebx
  int k; // ecx
  _DWORD *integerNode; // eax
  unsigned int integerFlags; // ebp
  int *bitmapBucket; // ebx
  int m; // ecx
  int *result; // eax
  unsigned int bitmapFlags; // ebp

  symbolBucket = (_DWORD *)(uintptr_t)g_Clips_SymbolHashTable;
  for ( i = 0; i < 1013; ++i )
  {
    symbolNode = (_DWORD *)(uintptr_t)*symbolBucket;
    if ( *symbolBucket )
    {
      do
      {
        symbolFlags = symbolNode[3] & 0xFFFF0003;
        symbolNode[3] = symbolFlags;
        symbolNode[3] = (4 * (i & 0x3FFF)) | symbolFlags;
        symbolNode = (_DWORD *)(uintptr_t)*symbolNode;
      }
      while ( symbolNode );
    }
    ++symbolBucket;
  }
  floatBucket = (_DWORD *)(uintptr_t)g_ClipsFloatHashTable;
  for ( j = 0; j < 503; ++j )
  {
    floatNode = (_DWORD *)(uintptr_t)*floatBucket;
    if ( *floatBucket )
    {
      do
      {
        floatFlags = floatNode[3] & 0xFFFF0003;
        floatNode[3] = floatFlags;
        floatNode[3] = (4 * (j & 0x3FFF)) | floatFlags;
        floatNode = (_DWORD *)(uintptr_t)*floatNode;
      }
      while ( floatNode );
    }
    ++floatBucket;
  }
  integerBucket = (_DWORD *)(uintptr_t)g_ClipsIntegerHashTable;
  for ( k = 0; k < 167; ++k )
  {
    integerNode = (_DWORD *)(uintptr_t)*integerBucket;
    if ( *integerBucket )
    {
      do
      {
        integerFlags = integerNode[3] & 0xFFFF0003;
        integerNode[3] = integerFlags;
        integerNode[3] = (4 * (k & 0x3FFF)) | integerFlags;
        integerNode = (_DWORD *)(uintptr_t)*integerNode;
      }
      while ( integerNode );
    }
    ++integerBucket;
  }
  bitmapBucket = (int *)(uintptr_t)g_ClipsBitmapHashTable;
  for ( m = 0; m < 167; ++m )
  {
    result = (int *)(uintptr_t)*bitmapBucket;
    if ( *bitmapBucket )
    {
      do
      {
        bitmapFlags = result[3] & 0xFFFF0003;
        result[3] = bitmapFlags;
        result[3] = (4 * (m & 0x3FFF)) | bitmapFlags;
        result = (int *)(uintptr_t)*result;
      }
      while ( result );
    }
    ++bitmapBucket;
  }
  return result;
}
// 54DD50: using guessed type int dword_54DD50;
// 54DD54: using guessed type int dword_54DD54;
// 54DD58: using guessed type int dword_54DD58;
// 54DD5C: using guessed type int dword_54DD5C;

//----- (00483040) --------------------------------------------------------
int  Rules_IncrementRefCountField40(int result)
{
  ++*(_DWORD *)(uintptr_t)(result + 40);
  return result;
}

//----- (00483050) --------------------------------------------------------
int  Instance_DecrementBusyCount(int result)
{
  --*(_DWORD *)(uintptr_t)(result + 40);
  return result;
}

//----- (00483060) --------------------------------------------------------
int Instance_InitHashTable(void)
{
  int result; // eax

  g_Instance_HashTableBase = (int)(intptr_t)Mem_SmallBlockAlloc(0xAACu);
  for ( result = 0; result != 2732; result += 4 )
    *(_DWORD *)(uintptr_t)(g_Instance_HashTableBase + result) = 0;
  return result;
}
// 51A278: using guessed type int dword_51A278;

//----- (004830A0) --------------------------------------------------------
void Instance_PurgeDeletedInstances(void)
{
  int current_node; // edx
  int previous_node; // ecx
  int object_record; // eax
  int next_node; // eax

  if ( !g_Instance_PurgeInProgress )
  {
    current_node = g_Instance_DeletedListHead;
    previous_node = 0;
    while ( current_node )
    {
      object_record = *(_DWORD *)(uintptr_t)(unsigned int)current_node;
      if ( *(_DWORD *)(uintptr_t)(object_record + 40)
        || g_ClipsCurrentEvaluationDepth >= *(_DWORD *)(uintptr_t)(object_record + 32)
        || *(_DWORD *)(uintptr_t)(object_record + 8) )
      {
        previous_node = current_node;
        current_node = *(_DWORD *)(uintptr_t)(unsigned int)(current_node + 4);
        continue;
      }

      g_ClipsEphemeralItemCount -= 2;
      g_ClipsEphemeralItemBytes -= 88;
      Rules_DecrementSymbolCount(*(_DWORD *)(uintptr_t)(object_record + 28), previous_node);

      g_ClipsMemFreeListTemp = object_record;
      *(_DWORD *)(uintptr_t)(unsigned int)object_record = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 320) = g_ClipsMemFreeListTemp;

      next_node = *(_DWORD *)(uintptr_t)(unsigned int)(current_node + 4);
      if ( previous_node )
        *(_DWORD *)(uintptr_t)(unsigned int)(previous_node + 4) = next_node;
      else
        g_Instance_DeletedListHead = next_node;

      g_ClipsMemFreeListTemp = current_node;
      *(_DWORD *)(uintptr_t)(unsigned int)current_node = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      current_node = next_node;
    }
  }
}
// 51A280: using guessed type int dword_51A280;
// 51A28C: using guessed type int dword_51A28C;
// 51A934: using guessed type int dword_51A934;
// 51A938: using guessed type int dword_51A938;
// 51A96C: using guessed type int dword_51A96C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00483190) --------------------------------------------------------
unsigned int  Instance_HashNameToBucket(int instanceName)
{
  return 11329 * (*(_DWORD *)(uintptr_t)(instanceName + 12) << 16 >> 18) % 0x2ABu;
}

//----- (004831B0) --------------------------------------------------------
int  Instance_PrintClassInstanceSummary(double a1)
{
  int savedPurgeFlag; // edi
  _DWORD *i; // esi
  int v3; // edx
  int v4; // ecx

  Module_BeginEnum();
  savedPurgeFlag = g_Instance_PurgeInProgress;
  i = (_DWORD *)(uintptr_t)g_Clips_InstanceListHead;
  g_Instance_PurgeInProgress = 1;
  if ( g_Clips_InstanceListHead )
  {
    do
    {
      Module_SetCurrent(*(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(i[11] + 8));
      MessageHandler_SendToInstanceAddress(g_ClipsDeleteMessageSymbol, v3, v4, 0, a1);
      for ( i = (_DWORD *)(uintptr_t)i[17]; i; i = (_DWORD *)(uintptr_t)i[17] )
      {
        if ( (i[6] & 2) == 0 )
          break;
      }
    }
    while ( i );
  }
  g_Instance_PurgeInProgress = savedPurgeFlag;
  return Module_EndEnum();
}
// 4831F0: variable 'v3' is possibly undefined
// 4831F0: variable 'v4' is possibly undefined
// 51A280: using guessed type int dword_51A280;
// 51AD0C: using guessed type int dword_51AD0C;
// 51AD38: using guessed type int dword_51AD38;

//----- (00483230) --------------------------------------------------------
signed int  Instance_ReleaseSlotValues(int theInstance)
{
  uintptr_t instance; // edi
  uintptr_t class_record; // eax
  unsigned int slot_index; // ebx
  unsigned int slot_offset; // esi
  signed int result; // eax
  unsigned int slot_count; // edx
  uintptr_t slot_value; // ecx
  uintptr_t slot_descriptor; // eax
  int shared_ref_count; // ebp
  unsigned int local_slot_count; // ebx

  instance = (uintptr_t)(unsigned int)theInstance;
  class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
  Class_ReleaseBusyReference((int)class_record);
  slot_index = 0;
  slot_offset = 0;
  while ( 1 )
  {
    class_record = (uintptr_t)(unsigned int)*(_DWORD *)(instance + 44);
    slot_count = *(_DWORD *)(class_record + 72);
    if ( slot_index >= slot_count )
      break;
    slot_value = (uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(instance + 72) + slot_offset);
    slot_descriptor = (uintptr_t)(unsigned int)*(_DWORD *)slot_value;
    if ( slot_value == slot_descriptor + 32 )
    {
      shared_ref_count = *(_DWORD *)(slot_descriptor + 24) - 1;
      *(_DWORD *)(slot_descriptor + 24) = shared_ref_count;
      if ( shared_ref_count )
        goto next_slot;
    }
    if ( (*(_BYTE *)slot_descriptor & 2) != 0 )
    {
      Rules_DeinstallMultifield((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot_value + 8));
      Rules_RegisterEphemeralMultifield(*(_DWORD *)(slot_value + 8));
    }
    else
    {
      Rules_AtomDeinstall(*(_DWORD *)(slot_value + 4) << 24 >> 26, (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot_value + 8), (int)slot_value);
    }
    *(_DWORD *)(slot_value + 8) = 0;
next_slot:
    slot_offset += 4;
    ++slot_index;
  }
  result = 0;
  if ( slot_count )
  {
    result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(instance + 72), 4 * slot_count);
    local_slot_count = *(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(instance + 44) + 68);
    if ( local_slot_count )
      result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(instance + 76), 12 * local_slot_count);
  }
  *(_DWORD *)(instance + 76) = 0;
  *(_DWORD *)(instance + 72) = 0;
  return result;
}

//----- (00483300) --------------------------------------------------------
_DWORD * Instance_FindByName(int instanceName)
{
  int current_module; // ebp
  signed int qualifier_length; // eax
  int name_text; // edx
  int local_symbol; // eax
  signed int *module_symbol; // eax
  int module_record; // esi

  current_module = Module_GetCurrent();
  name_text = *(_DWORD *)((uintptr_t)(unsigned int)instanceName + 16);
  if ( getenv("CLASH95_TRACE_PARSER_QUALIFIER_SCAN") )
  {
    fprintf(
      stderr,
      "[parser] fact-lookup symbol=%08x tag=%04x flags=%04x name=%08x caller=%p\n",
      instanceName,
      *(unsigned short *)(uintptr_t)(unsigned int)instanceName,
      *(unsigned short *)((uintptr_t)(unsigned int)instanceName + 12),
      name_text,
      __builtin_return_address(0));
    fflush(stderr);
  }
  qualifier_length = Rules_FindModuleSeparator((_BYTE *)(uintptr_t)(unsigned int)name_text);
  if ( !qualifier_length )
    return Instance_LookupInHashBucket(instanceName, current_module, 0, current_module);
  if ( qualifier_length == 1 )
  {
    local_symbol = (int)(uintptr_t)Rules_ExtractConstructName(1, (char *)(uintptr_t)(unsigned int)name_text, 1);
    return Instance_LookupInHashBucket(local_symbol, current_module, (_DWORD *)1, current_module);
  }
  else
  {
    module_symbol = Rules_ExtractModuleName(qualifier_length);
    module_record = module_symbol
                  ? (int)(uintptr_t)Module_FindByName((_BYTE *)(uintptr_t)(unsigned int)module_symbol[4])
                  : 0;
    local_symbol = (int)(uintptr_t)Rules_ExtractConstructName(
                                      qualifier_length,
                                      (char *)(uintptr_t)(unsigned int)name_text,
                                      qualifier_length);
    if ( module_record )
      return Instance_LookupInHashBucket(local_symbol, module_record, 0, current_module);
    else
      return 0;
  }
}

//----- (00483390) --------------------------------------------------------
_DWORD * Instance_LookupInHashBucket(int instanceName, int theModule, _DWORD *searchImports, int currentModule)
{
  int instance; // ebx
  int current; // ecx
  int class_record; // eax
  unsigned int bucket_index; // edx

  bucket_index = 11329 * ((unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)instanceName + 12) << 16 >> 18) % 0x2ABu;
  instance = *(_DWORD *)((uintptr_t)(unsigned int)g_Instance_HashTableBase + 4 * bucket_index);
  while ( instance )
  {
    if ( instanceName == *(_DWORD *)((uintptr_t)(unsigned int)instance + 28) )
      break;
    instance = *(_DWORD *)((uintptr_t)(unsigned int)instance + 60);
  }
  if ( !instance )
    return 0;
  current = instance;
  do
  {
    if ( *(_DWORD *)((uintptr_t)(unsigned int)current + 28) != *(_DWORD *)((uintptr_t)(unsigned int)instance + 28) )
      break;
    class_record = *(_DWORD *)((uintptr_t)(unsigned int)current + 44);
    if ( theModule == *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)class_record + 8)
      && Class_IsInScope(class_record, currentModule) )
      return (_DWORD *)(uintptr_t)(unsigned int)current;
    current = *(_DWORD *)((uintptr_t)(unsigned int)current + 60);
  }
  while ( current );
  if ( searchImports )
  {
    Rules_ClearModuleSearchMarkers();
    return Instance_FindInSubclasses(theModule, (_DWORD *)(uintptr_t)(unsigned int)instance);
  }
  return 0;
}
// 51A278: using guessed type int dword_51A278;

//----- (00483440) --------------------------------------------------------
int  Instance_GetSlotValueBySymbol(int theInstance, int slotName)
{
  unsigned int slot_index; // eax
  int class_record; // eax
  int slot_value_table; // eax

  class_record = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 44);
  slot_index = Instance_ResolveSlotIndex(class_record, slotName);
  if ( slot_index == (unsigned int)-1 )
    return 0;
  slot_value_table = *(_DWORD *)((uintptr_t)(unsigned int)theInstance + 72);
  return *(_DWORD *)((uintptr_t)(unsigned int)slot_value_table + 4 * slot_index);
}

//----- (00483470) --------------------------------------------------------
unsigned int __fastcall Instance_ResolveSlotIndex(int theClass, int slotName)
{
  unsigned int slot_id; // eax
  int slot_index_table; // eax

  slot_id = Class_FindSlotNameID(slotName);
  if ( slot_id == (unsigned int)-1 )
    return slot_id;
  if ( slot_id > *(_DWORD *)((uintptr_t)(unsigned int)theClass + 76) )
    return (unsigned int)-1;
  slot_index_table = *(_DWORD *)((uintptr_t)(unsigned int)theClass + 60);
  return *(_DWORD *)((uintptr_t)(unsigned int)slot_index_table + 4 * slot_id) - 1;
}

//----- (004834A0) --------------------------------------------------------
BOOL  Parser_ParseSlotDefaultOrRestriction(int mfp, int theExp, _DWORD *val, double a4)
{
  val[1] = 4;
  val[3] = 0;
  val[4] = -1;
  if ( theExp )
  {
    if ( mfp || *(_DWORD *)(uintptr_t)(theExp + 10) )
    {
      Rules_StoreEvaluatedNodesAsMultifield(val, theExp, 1, a4);
      return g_ClipsEvaluationError == 0;
    }
    else
    {
      Parser_ParseForm((__int16 *)(uintptr_t)theExp, val, (int)(intptr_t)val, a4);
      return g_ClipsEvaluationError == 0;
    }
  }
  else
  {
    val[2] = Rules_CreateEphemeralMultifield(0);
    return 1;
  }
}
// 51A964: using guessed type int dword_51A964;

//----- (00483520) --------------------------------------------------------
signed int  Instance_PutSlotValue(_DWORD *ins, int *sp, _DWORD *val, double a4)
{
  signed int result; // eax

  result = Instance_ValidateSlotValueConstraints(val, *sp, (int)(intptr_t)ins);
  if ( result )
    return Instance_StoreSlotValueAndMatch(ins, sp, 0, (uintptr_t)val, a4);
  return result;
}

//----- (00483550) --------------------------------------------------------
signed int  Instance_StoreSlotValueAndMatch(_DWORD *ins, int *sp, __int16 a3, uintptr_t val, double a5)
{
  int savedSlotEntry; // eax
  int sourceSlotFlags; // edx
  __int16 v8; // cx
  int valueType; // eax
  int valueField; // eax
  int v11; // ecx
  char *slotScopeText; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int slotDesc; // eax
  signed int traversalID; // eax
  int v21; // ecx
  int v22; // ecx
  char flagBits; // dh
  int fieldIndex; // edi
  int destOffset; // eax
  int srcOffset; // edx
  int fieldValue; // ecx
  _DWORD *newSegment; // eax
  int v29; // ecx
  int v30; // ecx
  int v31; // ecx
  int classNameText; // eax
  int v33; // ecx
  int srcFieldIndex; // [esp+Ch] [ebp-Ch]

  if ( !val )
  {
    Rules_ReportSystemError(a3, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( g_Rules_JoinOperationInProgress
    && (*(_BYTE *)(uintptr_t)(*sp + 1) & 2) != 0
    && ((*(_BYTE *)(uintptr_t)(ins[11] + 20) & 8) != 0 || (*(_BYTE *)(uintptr_t)*sp & 1) != 0) )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsfun, 5, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aCannotModifyRe, v21);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aPatternMatchin, v22);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
    if ( ins[5] )
    {
      savedSlotEntry = ins[5]
         + 12 * ((4 * (*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(ins[11] + 60) + 4 * *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*sp + 8) + 8)) - 1)) >> 2);
      if ( !*(_DWORD *)(uintptr_t)(savedSlotEntry + 8) )
      {
        LOBYTE(a3) = *(_BYTE *)(uintptr_t)(savedSlotEntry + 4) & 3;
        sourceSlotFlags = sp[1];
        *(_BYTE *)(uintptr_t)(savedSlotEntry + 4) = a3;
        *(_DWORD *)(uintptr_t)(savedSlotEntry + 4) |= sourceSlotFlags & 0xFC;
        *(_DWORD *)(uintptr_t)(savedSlotEntry + 8) = sp[2];
        if ( (*(_BYTE *)(uintptr_t)*sp & 2) != 0 )
          Rules_InstallMultifield((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(savedSlotEntry + 8));
        else
          Rules_AtomInstall(*(_DWORD *)(uintptr_t)(savedSlotEntry + 4) << 24 >> 26, *(_DWORD *)(uintptr_t)(savedSlotEntry + 8), a3);
      }
    }
    if ( (*(_BYTE *)(uintptr_t)*sp & 2) != 0 )
    {
      Rules_DeinstallMultifield((__int16 *)(uintptr_t)sp[2]);
      Rules_RegisterEphemeralMultifield(sp[2]);
      flagBits = sp[1] & 3;
      *((_BYTE *)sp + 4) = flagBits;
      *((_BYTE *)sp + 4) = flagBits | 0x10;
      if ( *(_DWORD *)(val + 4) == 4 )
      {
        sp[2] = (int)(intptr_t)Rules_CreateMultifield(*(_DWORD *)(val + 16) - *(_DWORD *)(val + 12) + 1);
        fieldIndex = 1;
        srcFieldIndex = *(_DWORD *)(val + 12) + 1;
        destOffset = 0;
        srcOffset = 6 * srcFieldIndex - 6;
        while ( fieldIndex <= *(_DWORD *)(val + 16) - *(_DWORD *)(val + 12) + 1 )
        {
          *(_WORD *)(uintptr_t)(destOffset + sp[2] + 14) = *(_WORD *)(uintptr_t)(srcOffset + *(_DWORD *)(val + 8) + 14);
          ++fieldIndex;
          fieldValue = *(_DWORD *)(uintptr_t)(*(_DWORD *)(val + 8) + srcOffset + 16);
          srcOffset += 6;
          *(_DWORD *)(uintptr_t)(destOffset + sp[2] + 16) = fieldValue;
          destOffset += 6;
          ++srcFieldIndex;
        }
      }
      else
      {
        newSegment = Rules_CreateMultifield(1);
        sp[2] = (int)(intptr_t)newSegment;
        *((_WORD *)newSegment + 7) = *(_WORD *)(val + 4);
        *(_DWORD *)(uintptr_t)(sp[2] + 16) = *(_DWORD *)(val + 8);
      }
      Rules_InstallMultifield((__int16 *)(uintptr_t)sp[2]);
    }
    else
    {
      Rules_AtomDeinstall((unsigned int)(sp[1] << 24) >> 26, (__int16 *)(uintptr_t)sp[2], a3);
      HIBYTE(v8) = sp[1] & 3;
      valueType = *(_DWORD *)(val + 4) & 0x3F;
      *((_BYTE *)sp + 4) = HIBYTE(v8);
      sp[1] |= 4 * valueType;
      valueField = *(_DWORD *)(val + 8);
      sp[2] = valueField;
      Rules_AtomInstall((unsigned int)(sp[1] << 24) >> 26, valueField, v8);
    }
    if ( (*(_BYTE *)(uintptr_t)(ins[11] + 20) & 0x20) != 0 )
    {
      if ( (*(_BYTE *)(uintptr_t)*sp & 1) != 0 )
        slotScopeText = aSharedSlot;
      else
        slotScopeText = aLocalSlot;
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)slotScopeText, v11);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*sp + 8) + 12) + 16), v13);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)aInInstance, v14);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], *(_DWORD *)(uintptr_t)(ins[7] + 16), v15);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_503AF0, v16);
      if ( (sp[1] & 0xFC) == 0x10 )
        Lexer_OutputFieldRange((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], sp[2], *(_DWORD *)(uintptr_t)(sp[2] + 6) - 1, 0, 1);
      else
        Rules_PrintAtomValue((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (unsigned int)(sp[1] << 24) >> 26, (int *)(uintptr_t)sp[2]);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WTrace[0], (int)(intptr_t)asc_503AF8, v17);
    }
    g_Instance_InstancesChangedFlag = 1;
    if ( (*(_BYTE *)(uintptr_t)(ins[11] + 20) & 8) == 0 )
      return 1;
    slotDesc = *sp;
    if ( (*(_BYTE *)(uintptr_t)(*sp + 1) & 2) == 0 )
      return 1;
    if ( (*(_BYTE *)(uintptr_t)slotDesc & 1) != 0 )
    {
      traversalID = Class_NewTraversalID();
      if ( traversalID != -1 )
      {
        Rules_MarkObjectPatternNetworkTraversal(traversalID, *(_DWORD *)(uintptr_t)(*sp + 4), *sp, a5);
        Class_ReleaseTraversalID();
        return 1;
      }
      Rules_PrintErrorID((int)(intptr_t)aInsfun, 6, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aUnableToPatter, v29);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*sp + 8) + 12) + 16), v30);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInClass, v31);
      classNameText = Rules_GetConstructNameString(*(_DWORD *)(uintptr_t)(*sp + 4));
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], classNameText, (int)(intptr_t)g_IO_LogicalNameTable_WError[0]);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v33);
      return 1;
    }
    else
    {
      Rules_ObjectMatchAction((unsigned __int16 *)3, ins, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 8) + 8), a5);
      return 1;
    }
  }
}
// 483628: variable 'a3' is possibly undefined
// 483657: variable 'v8' is possibly undefined
// 483682: variable 'v11' is possibly undefined
// 483697: variable 'v13' is possibly undefined
// 4836A6: variable 'v14' is possibly undefined
// 4836BA: variable 'v15' is possibly undefined
// 4836C9: variable 'v16' is possibly undefined
// 4836FF: variable 'v17' is possibly undefined
// 48378F: variable 'v21' is possibly undefined
// 48379E: variable 'v22' is possibly undefined
// 4838E3: variable 'v29' is possibly undefined
// 4838F8: variable 'v30' is possibly undefined
// 483907: variable 'v31' is possibly undefined
// 48392F: variable 'v33' is possibly undefined
// 51A288: using guessed type int dword_51A288;
// 51A614: using guessed type char *off_51A614[5];
// 51A618: using guessed type char *off_51A618[4];
// 51A954: using guessed type int dword_51A954;

//----- (00483960) --------------------------------------------------------
signed int  Instance_ValidateSlotValueConstraints(_DWORD *val, int sd, int ins)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  signed int violationCode; // [esp+0h] [ebp-10h]

  if ( (*(_BYTE *)(uintptr_t)sd & 2) == 0 && val[1] == 4 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsfun, 7, 0);
    Rules_PrintDataObject((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)val);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aIllegalForSing, v6);
    Instance_PrintSlotErrorContext((int)(intptr_t)g_IO_LogicalNameTable_WError[0], sd, v7, ins);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v8);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else if ( val[1] == 105 )
  {
    Rules_PrintErrorID((int)(intptr_t)aInsfun, 8, 0);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aVoidFunctionIl, v9);
    Instance_PrintSlotErrorContext((int)(intptr_t)g_IO_LogicalNameTable_WError[0], sd, v10, ins);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v11);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else if ( Rules_DynamicConstraintCheckingEnabled() && (violationCode = Rules_CheckFieldAgainstConstraint(val, *(_DWORD *)(uintptr_t)(sd + 20))) != 0 )
  {
    Rules_PrintErrorID((int)(intptr_t)aCstrnchk, 1, 0);
    Rules_PrintDataObject((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)val);
    Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aFor, v12);
    Instance_PrintSlotErrorContext((int)(intptr_t)g_IO_LogicalNameTable_WError[0], sd, v13, ins);
    Rules_PrintConstraintViolationMessage(0, 0, 0, 0, 0, 0, violationCode, *(_DWORD *)(uintptr_t)(sd + 20), 0);
    Lexer_ErrorRecover(1);
    return 0;
  }
  else
  {
    return 1;
  }
}
// 4839D4: variable 'v6' is possibly undefined
// 4839E0: variable 'v7' is possibly undefined
// 4839EF: variable 'v8' is possibly undefined
// 483A22: variable 'v9' is possibly undefined
// 483A30: variable 'v10' is possibly undefined
// 483A3F: variable 'v11' is possibly undefined
// 483A80: variable 'v12' is possibly undefined
// 483A8C: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483AC0) --------------------------------------------------------
_DWORD * Instance_ResolveArgumentToInstance(int a1, int functionName, double a3)
{
  _DWORD *ins; // edx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  _DWORD valueBuffer[6]; // [esp-4h] [ebp-20h] BYREF
  /* stack alias of valueBuffer[1] */
  /* stack alias of valueBuffer[2]: the DATA_OBJECT value slot */
  int v13 CLASH95_UNUSED; // [esp+18h] [ebp-4h]

  v13 = functionName;
  Parser_ParseForm((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsCurrentExpression + 6), valueBuffer, a1, a3);
  if ( valueBuffer[1] == 7 )
  {
    ins = (_DWORD *)(uintptr_t)valueBuffer[2];
    if ( (*(_BYTE *)(uintptr_t)(valueBuffer[2] + 24) & 2) != 0 )
    {
      Instance_ReportInvalidInstanceAddressError();
      Lexer_ErrorRecover(1);
      return 0;
    }
  }
  else
  {
    if ( valueBuffer[1] != 8 && valueBuffer[1] != 2 )
    {
      Rules_PrintErrorID((int)(intptr_t)aInsfun, 1, 0);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aExpectedAVal_1, v7);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v8, v8);
      Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v9);
      Lexer_ErrorRecover(1);
      return 0;
    }
    ins = Instance_FindByName(valueBuffer[2]);
    if ( !ins )
    {
      Instance_ReportNoSuchInstanceError(v6, v6);
      return 0;
    }
  }
  return ins;
}
// 483B28: variable 'v6' is possibly undefined
// 483B51: variable 'v7' is possibly undefined
// 483B5D: variable 'v8' is possibly undefined
// 483B6C: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51A960: using guessed type int dword_51A960;

//----- (00483B90) --------------------------------------------------------
int __fastcall Instance_ReportNoSuchInstanceError(int instanceName CLASH95_UNUSED, int functionName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aInsfun, 2, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoSuchInstance, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v7);
  return Lexer_ErrorRecover(1);
}
// 483BB2: variable 'v3' is possibly undefined
// 483BBE: variable 'v4' is possibly undefined
// 483BCD: variable 'v5' is possibly undefined
// 483BD9: variable 'v6' is possibly undefined
// 483BE8: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483C00) --------------------------------------------------------
int __fastcall Instance_ReportNoSuchSlotError(int slotName CLASH95_UNUSED, int functionName)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  Rules_PrintErrorID((int)(intptr_t)aInsfun, 3, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aNoSuchSlot, v3);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInFunction, v5);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], functionName, v6);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v7);
  return Lexer_ErrorRecover(1);
}
// 483C22: variable 'v3' is possibly undefined
// 483C2E: variable 'v4' is possibly undefined
// 483C3D: variable 'v5' is possibly undefined
// 483C49: variable 'v6' is possibly undefined
// 483C58: variable 'v7' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483C70) --------------------------------------------------------
signed int Instance_ReportInvalidInstanceAddressError(void)
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)(intptr_t)aInsfun, 4, 0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aInvalidInstanc, v0);
  Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)(intptr_t)g_IO_LogicalNameTable_WError[0], (int)(intptr_t)aDotNewline_InstanceError, v2);
}
// 483C90: variable 'v0' is possibly undefined
// 483C9C: variable 'v1' is possibly undefined
// 483CAB: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00483CD0) --------------------------------------------------------
int  Instance_SetModifiedFlag(int result)
{
  g_Instance_InstancesChangedFlag = result;
  return result;
}
// 51A288: using guessed type int dword_51A288;

//----- (00483CE0) --------------------------------------------------------
signed int  Instance_PrintSlotErrorContext(int logicalName, int sd, int a3, int ins)
{
  int v6; // ecx
  int v7; // ecx
  char *contextText; // edx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx

  Output_Write(logicalName, (int)(intptr_t)aSlot, a3);
  Output_Write(logicalName, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(sd + 8) + 12) + 16), v6);
  if ( ins )
  {
    Output_Write(logicalName, (int)(intptr_t)aOfInstance, v7);
    Output_Write(logicalName, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(ins + 28) + 16), v12);
    contextText = asc_503C24;
  }
  else
  {
    if ( !*(_DWORD *)(uintptr_t)(sd + 4) )
      goto LABEL_5;
    Output_Write(logicalName, (int)(intptr_t)aOfClass, v7);
    contextText = (char *)(uintptr_t)Rules_GetConstructNameString(*(_DWORD *)(uintptr_t)(sd + 4));
  }
  Output_Write(logicalName, (int)(intptr_t)contextText, v9);
LABEL_5:
  Output_Write(logicalName, (int)(intptr_t)aFoundIn, v7);
  if ( v10 )
    return Output_Write(logicalName, v10, v10);
  else
    return MessageHandler_PrintNameTypeAndClass(logicalName, (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)g_ClipsCurrentHandlerCore, 0);
}
// 483CFB: variable 'v6' is possibly undefined
// 483D11: variable 'v7' is possibly undefined
// 483D22: variable 'v9' is possibly undefined
// 483D35: variable 'v10' is possibly undefined
// 483D57: variable 'v12' is possibly undefined
// 51AD58: using guessed type int dword_51AD58;

//----- (00483D80) --------------------------------------------------------
signed int  Instance_PrintNameOfClass(int logicalName, int theInstance, int a3)
{
  int class_name; // eax
  int v5; // ecx
  int v6; // ecx

  Output_Write(logicalName, (int)(intptr_t)asc_503C40, logicalName);
  class_name = Rules_GetInstanceClassName(theInstance);
  Output_Write(v5, class_name, v5);
  Output_Write(v6, (int)(intptr_t)aOf, v6);
  return Class_PrintName(*(_DWORD *)(uintptr_t)(theInstance + 44), a3);
}
// 483D9B: variable 'v5' is possibly undefined
// 483DA7: variable 'v6' is possibly undefined

//----- (00483DC0) --------------------------------------------------------
_DWORD * Instance_FindInSubclasses(int theModule, _DWORD *startInstance)
{
  _DWORD *importList; // ebp
  _DWORD *ins; // ebx
  int v5; // ecx
  int *importedModule; // edi
  int theClass; // eax
  _DWORD *result; // eax

  if ( *(_DWORD *)(uintptr_t)(theModule + 20) )
    return 0;
  importList = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theModule + 12);
  *(_DWORD *)(uintptr_t)(theModule + 20) = 1;
  if ( !importList )
  {
LABEL_10:
    for ( result = startInstance; result; result = (_DWORD *)(uintptr_t)result[15] )
    {
      if ( result[7] != startInstance[7] )
        break;
      if ( (*(_BYTE *)(uintptr_t)(result[11] + 20) & 2) != 0 )
        return result;
    }
    return 0;
  }
  while ( 1 )
  {
    ins = startInstance;
    importedModule = Module_FindByName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(*importList + 16));
    if ( startInstance )
    {
      while ( ins[7] == startInstance[7] )
      {
        theClass = ins[11];
        if ( importedModule == **(int ***)(uintptr_t)(theClass + 8) && Class_IsInScope(theClass, v5) )
          return ins;
        ins = (_DWORD *)(uintptr_t)ins[15];
        if ( !ins )
          break;
      }
    }
    result = (_DWORD *)Instance_FindInSubclasses((int)(intptr_t)importedModule, (int)(intptr_t)startInstance);
    if ( result )
      return result;
    importList = (_DWORD *)(uintptr_t)importList[3];
    if ( !importList )
      goto LABEL_10;
  }
}
// 483E0F: variable 'v5' is possibly undefined

//----- (00483E70) --------------------------------------------------------
signed int  Instance_PrintStaleOrClassLabel(int logicalName, int theInstance)
{
  int v3; // ecx
  int v4; // ecx
  int v6; // ecx
  signed int *qualifiedName; // eax
  int v8; // ecx
  int v9; // ecx

  if ( (*(_BYTE *)(uintptr_t)(theInstance + 24) & 2) != 0 )
  {
    Output_Write(logicalName, (int)(intptr_t)aStaleInstance, logicalName);
    Output_Write(v3, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 28) + 16), v3);
    return Output_Write(v4, (int)(intptr_t)asc_503C60, v4);
  }
  else
  {
    Output_Write(logicalName, (int)(intptr_t)asc_503C40, logicalName);
    qualifiedName = Instance_GetQualifiedName(theInstance, v6);
    Output_Write(v8, qualifiedName[4], v8);
    return Output_Write(v9, (int)(intptr_t)asc_503C24, v9);
  }
}
// 483E90: variable 'v3' is possibly undefined
// 483E9C: variable 'v4' is possibly undefined
// 483EB2: variable 'v6' is possibly undefined
// 483EBC: variable 'v8' is possibly undefined
// 483EC8: variable 'v9' is possibly undefined

//----- (00483ED0) --------------------------------------------------------
signed int  Instance_PrintNameOrDummyLabel(int logicalName, void **theInstance)
{
  int v2; // ecx
  char *labelText; // edx
  signed int result; // eax
  int v7; // ecx
  signed int *qualifiedName; // eax
  int v9; // ecx
  char *suffixText; // edx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  signed int *fullName; // eax
  int v15; // ecx

  v2 = logicalName;
  if ( g_Print_InstanceAddressesToNamesFlag )
  {
    if ( theInstance == &g_Instance_DummyInstanceRecord )
    {
      labelText = aDummyInstanc_0;
    }
    else
    {
      Output_Write(logicalName, (int)(intptr_t)asc_503C40, logicalName);
      qualifiedName = Instance_GetQualifiedName((int)(intptr_t)theInstance, v7);
      Output_Write(v9, qualifiedName[4], v9);
      labelText = asc_503C24;
      logicalName = v2;
    }
    return Output_Write(logicalName, (int)(intptr_t)labelText, v2);
  }
  else
  {
    if ( g_Print_AddressesToStringsFlag )
      Output_Write(logicalName, (int)(intptr_t)asc_503C78, logicalName);
    if ( theInstance == &g_Instance_DummyInstanceRecord )
    {
      suffixText = aDummyInstanc_1;
    }
    else
    {
      if ( ((_BYTE)(intptr_t)theInstance[6] & 2) != 0 )
      {
        Output_Write(v2, (int)(intptr_t)aStaleInstanc_0, v2);
        Output_Write(v12, *((_DWORD *)theInstance[7] + 4), v12);
      }
      else
      {
        Output_Write(v2, (int)(intptr_t)aInstance_7, v2);
        fullName = Instance_GetQualifiedName((int)(intptr_t)theInstance, v13);
        Output_Write(v15, fullName[4], v15);
      }
      suffixText = asc_503CA4;
    }
    result = Output_Write(v2, (int)(intptr_t)suffixText, v2);
    if ( g_Print_AddressesToStringsFlag )
      return Output_Write(v11, (int)(intptr_t)asc_503C78, v11);
  }
  return result;
}
// 483EEF: variable 'v2' is possibly undefined
// 483F04: variable 'v7' is possibly undefined
// 483F0E: variable 'v9' is possibly undefined
// 483F53: variable 'v11' is possibly undefined
// 483F76: variable 'v12' is possibly undefined
// 483F90: variable 'v13' is possibly undefined
// 483F9A: variable 'v15' is possibly undefined
// 51A214: using guessed type void *off_51A214;
// 51A5FC: using guessed type int dword_51A5FC;
// 51A600: using guessed type int dword_51A600;

//----- (00483FB0) --------------------------------------------------------
signed int  Rules_MarkObjectPatternNetworkTraversal(signed int traversalID, signed int theClass, int sd, double a4)
{
  int traversalRecord; // ebx
  signed int result; // eax
  unsigned int slotNameID; // edx
  unsigned int subclassIndex; // ecx
  int j; // edi
  int slotIndex; // edi
  _DWORD *i; // ecx
  int v13; // ecx

  traversalRecord = ((traversalID - (__CFSHL__(traversalID >> 31, 3) + 8 * (traversalID >> 31))) >> 3) + theClass;
  result = 1 << (traversalID % 8);
  if ( ((unsigned __int8)result & *(_BYTE *)(uintptr_t)(traversalRecord + 108)) == 0 )
  {
    *(_BYTE *)(uintptr_t)(traversalRecord + 108) |= result;
    slotNameID = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(sd + 8) + 8);
    if ( slotNameID <= *(_DWORD *)(uintptr_t)(theClass + 76) )
    {
      slotIndex = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 60) + 4 * slotNameID);
      if ( slotIndex )
      {
        if ( sd == *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 56) + 4 * slotIndex - 4) )
        {
          for ( i = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theClass + 80); i; i = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(v13 + 52) )
            Rules_ObjectMatchAction((unsigned __int16 *)3, i, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(sd + 8) + 8), a4);
        }
      }
    }
    subclassIndex = 0;
    for ( j = 0; ; Rules_MarkObjectPatternNetworkTraversal(traversalID, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theClass + 42) + j - 4), sd, a4) )
    {
      result = theClass;
      if ( subclassIndex >= *(unsigned __int16 *)(uintptr_t)(theClass + 40) )
        break;
      j += 4;
    }
  }
  return result;
}
// 48401F: variable 'v9' is possibly undefined
// 48406C: variable 'v13' is possibly undefined

//----- (00484090) --------------------------------------------------------
int  Instance_ReleaseSlotValueContainer(int result)
{
  int theInstance; // esi
  int newRefCount; // edx
  unsigned int slotIndex; // ebx
  int i; // ecx
  unsigned int slotCount; // edi
  int slotEntry; // eax
  __int16 *slotValue; // ebp

  theInstance = result;
  newRefCount = *(_DWORD *)(uintptr_t)(result + 8) - 1;
  *(_DWORD *)(uintptr_t)(result + 8) = newRefCount;
  if ( !newRefCount )
  {
    if ( (*(_BYTE *)(uintptr_t)(result + 24) & 2) != 0 )
      Instance_ReleaseSlotValues(result);
    result = *(_DWORD *)(uintptr_t)(theInstance + 44);
    if ( *(_DWORD *)(uintptr_t)(result + 72) )
    {
      slotIndex = 0;
      for ( i = 0; ; i += 12 )
      {
        slotCount = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(theInstance + 44) + 72);
        if ( slotIndex >= slotCount )
          break;
        slotEntry = i + *(_DWORD *)(uintptr_t)(theInstance + 20);
        slotValue = (__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotEntry + 8);
        if ( slotValue )
        {
          if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)slotEntry & 2) != 0 )
            Rules_DeinstallMultifield((__int16 *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotEntry + 8));
          else
            Rules_AtomDeinstall(*(_DWORD *)(uintptr_t)(slotEntry + 4) << 24 >> 26, slotValue, i);
        }
        ++slotIndex;
      }
      result = Mem_SmallBlockFree((_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theInstance + 20), 12 * slotCount);
      *(_DWORD *)(uintptr_t)(theInstance + 20) = 0;
    }
  }
  return result;
}
// 4840D2: variable 'i' is possibly undefined

//----- (00484130) --------------------------------------------------------
_DWORD * Instance_AcquireLocalSlotArray(_DWORD *result)
{
  _DWORD *theInstance; // edx
  int sharedSlotCount; // esi
  int srcOffset; // ebx
  int slotArray; // eax
  unsigned int slotIndex; // ecx
  int dstOffset; // eax

  /* sub_484130: `mov [ecx+14h], eax` stores the freshly allocated array into
     theInstance[5] (ecx is the instance); IDA emitted an undefined `v6` there and
     folded the destination byte offset into the returned pointer. */
  theInstance = result;
  if ( !result[2] )
  {
    sharedSlotCount = *(_DWORD *)(uintptr_t)(result[11] + 72);
    if ( sharedSlotCount )
    {
      srcOffset = 0;
      slotArray = (int)(uintptr_t)Mem_SmallBlockAlloc(12 * sharedSlotCount);
      theInstance[5] = slotArray;
      slotIndex = 0;
      dstOffset = 0;
      while ( slotIndex < *(_DWORD *)(uintptr_t)(theInstance[11] + 72) )
      {
        /* loc_484173: `mov esi,[edx+48h]; mov esi,[esi+ebx]; mov esi,[esi];
                        mov edi,[edx+14h]; mov [edi+eax], esi` */
        *(_DWORD *)(uintptr_t)((unsigned int)theInstance[5] + dstOffset) =
            *(_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(theInstance[18] + srcOffset);
        dstOffset += 12;
        srcOffset += 4;
        ++slotIndex;
        *(_DWORD *)(uintptr_t)((unsigned int)theInstance[5] + dstOffset - 4) = 0;
      }
    }
  }
  ++theInstance[2];
  return result;
}

//----- (004841A0) --------------------------------------------------------
void  Instance_NotifyCreated(_DWORD *theInstance, double a2)
{
  Rules_ObjectMatchAction((unsigned __int16 *)1, theInstance, -1, a2);
}

//----- (004842DF) --------------------------------------------------------
#if 0
void  __noreturn CRT_WatcomEHHandleNestedException(int a1, int a2)
{
  int *currentExc; // edi
  int *nestedExc; // ebp
  char savedState; // al
  int *fnexcThis; // eax
  int v7; // edx
  int v8; // ecx
  _DWORD *nestedThrowRec; // eax
  int *fnexcThis2; // eax
  int *dtorThis; // eax
  int v12; // ecx
  _EXC_PR_FNEXC *strExcBuf[26]; // [esp+0h] [ebp-14Ch] BYREF
  char v14; // [esp+D8h] [ebp-74h]
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // [esp+110h] [ebp-3Ch]
  tagRECT *fsHandlerRtn; // [esp+114h] [ebp-38h]
  void *scopeTable; // [esp+118h] [ebp-34h]
  int ehState; // [esp+11Ch] [ebp-30h]
  _EXC_PR_FNEXC **excCleanup; // [esp+124h] [ebp-28h]
  char v20; // [esp+128h] [ebp-24h]
  int pgmThread; // [esp+130h] [ebp-1Ch]

  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  fsHandlerRtn = &j____wcpp_4_fs_handler_rtn_;
  scopeTable = &g_CRTWatcomEHHandleNestedException_ScopeTable;
  ehState = 0;
  pgmThread = **(_DWORD **)(a1 + 8);
  currentExc = *(int **)(pgmThread + 8);
  *(_DWORD *)(pgmThread + 12) = aViolationOfFun;
  nestedExc = currentExc;
  currentExc[7] = a1;
  while ( 1 )
  {
    if ( !nestedExc )
    {
      currentExc[7] = a1;
      savedState = *((_BYTE *)currentExc + 12);
      *((_BYTE *)currentExc + 12) = 2;
      *((_BYTE *)currentExc + 13) = savedState;
      if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
        fnexcThis = 0;
      else
        fnexcThis = currentExc;
      _EXC_PR_FNEXC::_EXC_PR_FNEXC(fnexcThis);
      ehState = 1;
      unexpected();
      v14 = 3;
      _wcpp_4_call_terminate__(v8, v7);
      ehState = 0;
      _EXC_PR_FNEXC::~_EXC_PR_FNEXC(strExcBuf[0]);
    }
    nestedThrowRec = (_DWORD *)nestedExc[7];
    if ( nestedThrowRec && *(_DWORD *)a1 == *nestedThrowRec && *(_DWORD *)(a1 + 32) == nestedThrowRec[8] )
    {
      if ( *((_BYTE *)nestedExc + 12) == 2 )
      {
        *((_BYTE *)currentExc + 12) = 7;
        if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
          fnexcThis2 = 0;
        else
          fnexcThis2 = currentExc;
        _EXC_PR_FNEXC::_EXC_PR_FNEXC(fnexcThis2);
        v20 = 0;
        excCleanup = strExcBuf;
        ehState = 4;
        ExcString_Ctor();
        ehState = 5;
        ExcString_Ctor();
        strExcBuf[25] = (_EXC_PR_FNEXC *)&g_BadException_VTable;
        ehState = 7;
        CRT_ThrowExcStringException();
        excCleanup = strExcBuf;
        v20 = 0;
        ehState = 0;
        _EXC_PR_FNEXC::~_EXC_PR_FNEXC(strExcBuf[0]);
      }
      if ( *((_BYTE *)nestedExc + 12) == 7 )
      {
        if ( (*(_BYTE *)(a1 + 37) & 2) != 0 )
          dtorThis = 0;
        else
          dtorThis = currentExc;
        _EXC_PR_DTOR::_EXC_PR_DTOR(dtorThis);
        ehState = 14;
        _wcpp_4_call_terminate__(v12, pgmThread);
        ehState = 0;
        _EXC_PR_DTOR::~_EXC_PR_DTOR(strExcBuf[0]);
      }
      if ( nestedExc != currentExc )
        _wcpp_4_corrupted_stack__(a2);
    }
    nestedExc = (int *)*nestedExc;
    if ( currentExc == nestedExc )
      _wcpp_4_corrupted_stack__(a2);
  }
}
// 484394: variable 'v8' is possibly undefined
// 484394: variable 'v7' is possibly undefined
// 4844C5: variable 'v12' is possibly undefined
// 4844E7: variable 'a2' is possibly undefined
// 4B403E: using guessed type _DWORD __stdcall _EXC_PR_DTOR::_EXC_PR_DTOR(_DWORD);
// 4B404D: using guessed type _DWORD __stdcall _EXC_PR_FNEXC::_EXC_PR_FNEXC(_DWORD);
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B40FF: using guessed type int __fastcall _wcpp_4_call_terminate__(_DWORD, _DWORD);
// 510F44: using guessed type _DWORD (__cdecl *off_510F44)(bad_exception *this);

//----- (0048469F) --------------------------------------------------------
// local variable allocation has failed, the output may be wrong!
// positive sp value has been detected, the output may be wrong!
int  CRT_WatcomEHFrameHandler(
        int a1,
        int a2,
        int a3,
        __int128 a4,
        int ExceptionRecord_6,
        __int128 ExceptionRecord_10,
        int ExceptionRecord_26,
        int ExceptionRecord_30,
        int ExceptionRecord_34,
        int ExceptionRecord_38,
        int ExceptionRecord_42,
        __int128 ExceptionRecord_46,
        int ExceptionRecord_62,
        int ExceptionRecord_66,
        int ExceptionRecord_70,
        int ExceptionRecord_74,
        int ExceptionRecord_78,
        __int64 a18,
        int a19,
        __int64 a20)
{
  int v21; // ecx
  int v22; // ecx
  void *v24; // esp
  int v25; // eax
  int v26; // ecx
  int v27; // ebx
  int allocatedExc; // eax
  int v29; // ecx
  _EXC_PR_FREE *v30; // [esp-92h] [ebp-12Eh]
  _EXC_PR *v31; // [esp-82h] [ebp-11Eh]
  PVOID TargetFrame; // [esp+82h] [ebp-1Ah] BYREF
  int excObject; // [esp+8Eh] [ebp-Eh]
  int var2; // [esp+9Ah] [ebp-2h]
  int vars6; // [esp+A2h] [ebp+6h]
  char varsA; // [esp+A6h] [ebp+Ah]
  char varsB; // [esp+A7h] [ebp+Bh]

  *(_DWORD *)((char *)&ExceptionRecord_46 + 2) = NtCurrentTeb()->NtTib.ExceptionList;
  *(_DWORD *)((char *)&ExceptionRecord_46 + 6) = &j____wcpp_4_fs_handler_rtn_;
  *(_DWORD *)((char *)&ExceptionRecord_46 + 10) = &g_CRTWatcomEHFrameHandler_ScopeTable;
  *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 0;
  *(_DWORD *)((char *)&a18 + 2) = _wcpp_4_pgm_thread__(a2);
  *(_DWORD *)(*(_DWORD *)((char *)&a18 + 2) + 12) = 0;
  _wcpp_4_exc_setup__(a1, (char *)&a4 + 10);
  if ( (unsigned int)stackavail_(v21) > 0x10 )
  {
    CRT_ProbeStackForAlloca(16);
    v24 = alloca(16);
  }
  *(_DWORD *)((char *)&a20 + 2) = 0;
  if ( !*(_DWORD *)((char *)&a4 + 2) )
  {
    varsA = 3;
    goto LABEL_5;
  }
  RaiseException(
    *(DWORD *)((char *)&a4 + 10),
    *(DWORD *)((char *)&a4 + 14),
    *(DWORD *)((char *)&ExceptionRecord_10 + 6),
    (const ULONG_PTR *)((char *)&ExceptionRecord_10 + 10));
  if ( (unsigned __int8)varsA >= 2u )
  {
    if ( (unsigned __int8)varsA > 2u )
    {
      if ( varsA != 4 )
        goto LABEL_20;
      if ( !*(_DWORD *)((char *)&a4 + 6) )
        _wcpp_4_corrupted_stack__(v22);
      switch ( *(_BYTE *)(*(_DWORD *)((char *)&a4 + 6) + 12) )
      {
        case 0:
          if ( (varsB & 2) != 0 )
            v25 = 0;
          else
            v25 = *(_DWORD *)(*(_DWORD *)((char *)&a18 + 2) + 8);
          _EXC_PR_FREE::_EXC_PR_FREE(v25);
          *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 1;
          _wcpp_4_call_terminate__(v26, *(_DWORD *)((char *)&a18 + 2));
          *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 0;
          _EXC_PR_FREE::~_EXC_PR_FREE(v30);
          goto LABEL_14;
        case 3:
LABEL_14:
          _wcpp_4_fatal_runtime_error__(v22, 1);
          goto LABEL_15;
        case 5:
LABEL_15:
          _wcpp_4_fatal_runtime_error__(v22, 1);
          goto LABEL_16;
        case 6:
LABEL_16:
          _wcpp_4_fatal_runtime_error__(v22, 1);
          break;
        default:
          break;
      }
      _wcpp_4_corrupted_stack__(v22);
    }
  }
  else if ( varsA != 1 )
  {
    goto LABEL_20;
  }
  if ( *(_DWORD *)((char *)&a20 + 2) )
  {
LABEL_19:
    CRT_WatcomEHUnwindThreadToState(vars6, v22);
    goto LABEL_20;
  }
  *(_DWORD *)((char *)&a20 + 2) = 1;
  if ( (varsB & 2) != 0 )
  {
    *(_BYTE *)(excObject + 13) = *(_BYTE *)(excObject + 12);
    if ( (varsB & 4) != 0 )
    {
      v27 = excObject;
      *(_DWORD *)(excObject + 24) = var2;
      *(_DWORD *)(v27 + 32) = TargetFrame;
    }
  }
  else
  {
    allocatedExc = ((int (*)(void))_wcpp_4_alloc_exc__)();
    excObject = allocatedExc;
    *(_DWORD *)(allocatedExc + 24) = var2;
    *(_DWORD *)(allocatedExc + 32) = TargetFrame;
  }
  if ( varsA != 2 )
  {
    *(_BYTE *)(excObject + 12) = 0;
    RtlUnwind(TargetFrame, *(PVOID *)((char *)&ExceptionRecord_10 + 2), (PEXCEPTION_RECORD)((char *)&a4 + 10), 0);
    goto LABEL_19;
  }
  if ( (varsB & 2) != 0 )
    *(_BYTE *)(excObject + 12) = *(_BYTE *)(excObject + 13);
LABEL_20:
  if ( (unsigned __int8)varsA < 2u )
  {
    if ( varsA != 1 )
      return _wcpp_4_corrupted_stack__(v22);
    CRT_WatcomEHResetStateOnUnwind();
    goto LABEL_5;
  }
  if ( (unsigned __int8)varsA <= 2u )
    CRT_WatcomEHHandleNestedException((int)&TargetFrame, v22);
  if ( varsA == 3 )
  {
LABEL_5:
    if ( (varsB & 2) != 0 )
    {
      _wcpp_4_fatal_runtime_error__(v22, 1);
    }
    else
    {
      ((void (__fastcall *)(int, char *))_EXC_PR::_EXC_PR)(3, (char *)&a18 + 2);
      *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 3;
      _wcpp_4_call_terminate__(v29, *(_DWORD *)((char *)&a18 + 2));
      *(_DWORD *)((char *)&ExceptionRecord_46 + 14) = 0;
      _EXC_PR::~_EXC_PR(v31);
    }
  }
  return _wcpp_4_corrupted_stack__(v22);
}
// 484747: positive sp value 82 has been found
// 4848B6: inconsistent variable size for '^154.16'
// 4846D2: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 48479E: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 4847AF: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 48490E: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 48491F: inconsistent variable size for '^18C.16(ExceptionRecord_46)'
// 47C1C0: using guessed type _DWORD __stdcall sub_47C1C0(_DWORD);
// 48455B: using guessed type _DWORD sub_48455B();
// 486342: using guessed type int __fastcall _wcpp_4_fatal_runtime_error__(_DWORD, _DWORD);
// 4B3FC7: using guessed type _DWORD _EXC_PR::_EXC_PR();
// 4B4001: using guessed type _DWORD __stdcall _EXC_PR_FREE::_EXC_PR_FREE(_DWORD);
// 4B40EB: using guessed type int __thiscall _wcpp_4_corrupted_stack__(_DWORD);
// 4B40FF: using guessed type int __fastcall _wcpp_4_call_terminate__(_DWORD, _DWORD);
// 4B42EA: using guessed type __int64 __thiscall _wcpp_4_pgm_thread__(_DWORD);
// 4B431A: using guessed type _DWORD __stdcall _wcpp_4_exc_setup__(_DWORD, _DWORD);
// 4B43B3: using guessed type int __thiscall stackavail_(_DWORD);
#endif
