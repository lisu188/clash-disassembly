/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004D35E0) --------------------------------------------------------
signed int  Rules_ParseDefclass(char *readSource, double a2)
{
  int *slots; // edi
  int classNameSymbol; // ecx
  int v6; // ecx
  unsigned __int16 *parsedSuperclasses; // eax
  unsigned __int16 *v8; // ecx
  int precedenceList; // ebp
  char abstractByte; // dl
  char reactiveByte; // dl
  int classRecord; // eax
  int v13; // edx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int cls; // [esp+0h] [ebp-38h] BYREF
  int roleSpecified; // [esp+4h] [ebp-34h] BYREF
  int abstract; // [esp+8h] [ebp-30h] BYREF
  int matchSpecified; // [esp+Ch] [ebp-2Ch] BYREF
  int reactive; // [esp+10h] [ebp-28h] BYREF
  int className; // [esp+14h] [ebp-24h]
  unsigned __int16 *superclasses; // [esp+18h] [ebp-20h]
  int parseError; // [esp+1Ch] [ebp-1Ch]

  slots = 0;
  roleSpecified = 0;
  abstract = 0;
  matchSpecified = 0;
  reactive = 1;
  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  IO_OutWriteToken(aDefclass_3);
  if ( Rules_IsBloaded() )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  classNameSymbol = Rules_GetConstructNameAndComment((int)readSource, (int)&g_ParserCurrentTokenType, (int (*)(void))Class_LookupCurrentScopedName, aDefclass_4, 0, asc_50C9A0, 1, 1, 1);
  className = classNameSymbol;
  if ( !classNameSymbol )
    return 1;
  if ( !Rules_ValidateClassRedefinition(classNameSymbol, &cls) )
    return 1;
  parsedSuperclasses = (unsigned __int16 *)Class_ParseSuperclasses((int)readSource, v6);
  superclasses = parsedSuperclasses;
  if ( !parsedSuperclasses )
    return 1;
  precedenceList = Class_BuildPrecedenceList(cls, parsedSuperclasses);
  if ( !precedenceList )
  {
    Class_FreeOrRecycleArray(v8, 1);
    return 1;
  }
  Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
  parseError = 0;
  if ( g_ParserCurrentTokenType == 101 )
    goto LABEL_11;
  while ( 1 )
  {
    if ( g_ParserCurrentTokenType != 100
      || (IO_OutNewline(),
          AST_Append(v14, v13),
          IO_OutWriteToken(asc_50C9A4),
          Parser_NextToken((int)readSource, v15),
          g_ParserCurrentTokenType != 2) )
    {
      Parser_ReportSyntaxError();
      parseError = 1;
      goto LABEL_11;
    }
    if ( !strcmp_(v16, aRole) )
    {
      if ( !Rules_ParseClassAttributeFlag((int)readSource, (int)aRole, (int)aConcrete, &roleSpecified, &abstract) )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v17, aPatternMatch) )
    {
      if ( !Rules_ParseClassAttributeFlag((int)readSource, (int)aPatternMatch, (int)aNonReactive, &matchSpecified, &reactive) )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v18, aSlot_6) )
    {
      slots = Class_ParseSlot(readSource, slots, 0, (unsigned __int16 *)precedenceList, a2, 0);
      if ( !slots )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v19, aSingleSlot) )
    {
      slots = Class_ParseSlot(readSource, slots, 0, (unsigned __int16 *)precedenceList, a2, 1);
      if ( !slots )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( !strcmp_(v20, aMultislot_0) )
    {
      slots = Class_ParseSlot(readSource, slots, 1, (unsigned __int16 *)precedenceList, a2, 1);
      if ( !slots )
      {
        parseError = 1;
        goto LABEL_11;
      }
      goto LABEL_44;
    }
    if ( strcmp_(v21, aMessageHandl_6) )
      break;
    if ( !Rules_SkipMessageHandlerBody((int)readSource) )
    {
      parseError = 1;
      goto LABEL_11;
    }
LABEL_44:
    Parser_NextToken((int)readSource, (int)&g_ParserCurrentTokenType);
    if ( g_ParserCurrentTokenType == 101 )
      goto LABEL_11;
  }
  Parser_ReportSyntaxError();
  parseError = v22;
LABEL_11:
  if ( g_ParserCurrentTokenType != 101 || parseError == 1 )
  {
    Class_FreeOrRecycleArray(superclasses, 1);
    Class_FreeOrRecycleArray((unsigned __int16 *)precedenceList, 1);
    Class_DeleteSlotList((int)slots);
    return 1;
  }
  else
  {
    IO_OutWriteToken(asc_50CA24);
    if ( !roleSpecified )
      abstract = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(precedenceList + 2) + 4) + 20) << 29 >> 31;
    if ( !matchSpecified )
      reactive = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(precedenceList + 2) + 4) + 20) << 28 >> 31;
    if ( abstract && reactive )
    {
      Rules_PrintErrorID((int)aClasspsr, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAnAbstractClas, v23);
      Class_FreeOrRecycleArray(superclasses, 1);
      Class_FreeOrRecycleArray((unsigned __int16 *)precedenceList, 1);
      Class_DeleteSlotList((int)slots);
      return 1;
    }
    else
    {
      cls = Class_AllocateRecord(className);
      abstractByte = abstract;
      *(_BYTE *)(cls + 20) &= ~4u;
      *(_DWORD *)(cls + 20) |= 4 * (abstractByte & 1);
      reactiveByte = reactive;
      *(_BYTE *)(cls + 20) &= ~8u;
      *(_DWORD *)(cls + 20) |= 8 * (reactiveByte & 1);
      *(_WORD *)(cls + 34) = *superclasses;
      *(_DWORD *)(cls + 36) = *(_DWORD *)(superclasses + 1);
      classRecord = cls;
      **(_DWORD **)(precedenceList + 2) = cls;
      *(_WORD *)(classRecord + 46) = *(_WORD *)precedenceList;
      *(_DWORD *)(cls + 48) = *(_DWORD *)(precedenceList + 2);
      g_ClipsMemFreeListTemp = (int)superclasses;
      *(_DWORD *)superclasses = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
      g_ClipsMemFreeListTemp = precedenceList;
      *(_DWORD *)precedenceList = *(_DWORD *)(g_ClipsMemoryTable + 24);
      *(_DWORD *)(g_ClipsMemoryTable + 24) = g_ClipsMemFreeListTemp;
      if ( slots )
        Class_FlattenSlotLinksToArray(cls, slots);
      Rules_InstallDefclass(cls);
      return 0;
    }
  }
}
// 4D367E: variable 'v6' is possibly undefined
// 4D382E: variable 'v8' is possibly undefined
// 4D3847: variable 'v14' is possibly undefined
// 4D3847: variable 'v13' is possibly undefined
// 4D385D: variable 'v15' is possibly undefined
// 4D3878: variable 'v16' is possibly undefined
// 4D38DB: variable 'v17' is possibly undefined
// 4D3926: variable 'v18' is possibly undefined
// 4D3961: variable 'v19' is possibly undefined
// 4D399D: variable 'v20' is possibly undefined
// 4D39D8: variable 'v21' is possibly undefined
// 4D3A0D: variable 'v22' is possibly undefined
// 4D3A7F: variable 'v23' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004D3AC0) --------------------------------------------------------
signed int __fastcall Rules_ValidateClassRedefinition(int a1, int *existingClass)
{
  int v2; // eax
  int v4; // ecx
  int *v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // ecx

  v2 = Class_LookupCurrentScopedName();
  *existingClass = v2;
  if ( !v2 )
    return 1;
  if ( (*(_BYTE *)(v2 + 20) & 2) != 0 )
  {
    Rules_PrintErrorID((int)aClasspsr, 2, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotRedefi_0, v4);
    return 0;
  }
  else
  {
    if ( Class_IsDeletable() )
      return 1;
    Rules_PrintErrorID((int)aClasspsr, 3, 0);
    v6 = Rules_GetConstructNameString(*v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], v6, (int)g_IO_LogicalNameTable_WError[0]);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClassCannotBeR, v7);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOutstandingRef, v8);
    return 0;
  }
}
// 4D3B01: variable 'v4' is possibly undefined
// 4D3B1C: variable 'v5' is possibly undefined
// 4D3B3C: variable 'v7' is possibly undefined
// 4D3B4B: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004D3B60) --------------------------------------------------------
signed int  Rules_ParseClassAttributeFlag(int readSource, int qualifierName, int clearRelation, _DWORD *alreadyTestedFlag, _DWORD *binaryFlag)
{
  int v7; // edx
  int v8; // ecx
  int v9; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  if ( *alreadyTestedFlag )
  {
    Rules_PrintErrorID((int)aClasspsr, 4, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aClass_2, v11);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], qualifierName, v12);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAlreadyDeclare, v13);
    return 0;
  }
  IO_OutWriteToken(asc_50CAF8);
  Parser_NextToken(readSource, v7);
  if ( g_ParserCurrentTokenType == 2 )
  {
    if ( !strcmp_(v8, v8) )
    {
      *binaryFlag = 1;
      goto LABEL_5;
    }
    if ( !strcmp_(v9, clearRelation) )
    {
      *binaryFlag = 0;
LABEL_5:
      Parser_NextToken(readSource, (int)&g_ParserCurrentTokenType);
      if ( g_ParserCurrentTokenType == 101 )
      {
        *alreadyTestedFlag = 1;
        return 1;
      }
    }
  }
  Parser_ReportSyntaxError();
  return 0;
}
// 4D3B80: variable 'v7' is possibly undefined
// 4D3B9C: variable 'v8' is possibly undefined
// 4D3BF3: variable 'v11' is possibly undefined
// 4D3BFF: variable 'v12' is possibly undefined
// 4D3C0E: variable 'v13' is possibly undefined
// 4D3C24: variable 'v9' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 54E8FC: using guessed type int dword_54E8FC;
// 54E900: using guessed type int dword_54E900;

//----- (004D3C50) --------------------------------------------------------
signed int  Rules_SkipMessageHandlerBody(int readSource)
{
  int parenDepth; // ebx
  int justOpenedParen; // esi
  int *tokenPtr; // ecx
  int tokenType; // edx

  parenDepth = 1;
  justOpenedParen = 0;
LABEL_2:
  IO_OutWriteToken(asc_50CAF8);
  while ( 1 )
  {
    Parser_NextToken(readSource, (int)tokenPtr);
    tokenType = *tokenPtr;
    if ( *tokenPtr == 102 )
    {
      Parser_ReportSyntaxError();
      return 0;
    }
    if ( tokenType == 100 )
    {
      justOpenedParen = 1;
      ++parenDepth;
    }
    else
    {
      if ( tokenType == 101 )
      {
        --parenDepth;
        if ( !justOpenedParen )
        {
          IO_OutNewline();
          IO_OutNewline();
          IO_OutWriteToken(asc_50CB18);
        }
      }
      justOpenedParen = 0;
    }
    if ( parenDepth <= 0 )
      return 1;
    if ( !justOpenedParen )
      goto LABEL_2;
  }
}
// 4D3C70: variable 'v4' is possibly undefined

//----- (004D3CE0) --------------------------------------------------------
_DWORD * Rules_InstallDefclass(int theDefclass)
{
  int classNameSymbol; // eax
  unsigned int nameHash; // eax
  unsigned int watchInstances; // ebx
  int classPtr; // ecx
  unsigned int watchSlots; // esi
  int oldDefclass; // eax
  int v7; // ecx
  int v8; // ecx
  __int16 *v9; // ecx
  int v10; // ecx
  int v11; // ecx
  _DWORD *v12; // ecx
  int v13; // ecx
  int v14; // ecx
  char classFlags; // ah
  _DWORD *v16; // ecx
  _DWORD *v17; // ecx
  int oldFlags; // ebx
  int savedFlags; // esi
  char *ppForm; // eax
  signed int v22; // ecx

  classNameSymbol = Rules_GetConstructNameSymbol(theDefclass);
  nameHash = Class_HashClassName(classNameSymbol);
  watchInstances = 0;
  *(_DWORD *)(classPtr + 30) = nameHash;
  watchSlots = 0;
  Rules_GetConstructNameString(classPtr);
  oldDefclass = Class_LookupCurrentScopedName();
  if ( oldDefclass )
  {
    oldFlags = *(_DWORD *)(oldDefclass + 20);
    savedFlags = oldFlags;
    Class_DeleteRecursive(oldDefclass);
    watchInstances = (unsigned int)(oldFlags << 27) >> 31;
    watchSlots = (unsigned int)(savedFlags << 26) >> 31;
  }
  Class_AddToHashTable(v7);
  Rules_LinkClassToSuperclasses(v8);
  Class_SetInstallState(v9, 1);
  Rules_AppendConstructToModuleList(v10);
  Rules_BuildInheritedSlotArray(v11);
  Class_BuildSlotIndexMap(v12);
  Class_AssignID(v13);
  classFlags = *(_BYTE *)(v14 + 20);
  if ( (classFlags & 4) != 0 )
  {
    *(_BYTE *)(v14 + 20) = classFlags & 0xCF;
  }
  else
  {
    if ( watchInstances )
      *(_BYTE *)(v14 + 20) = classFlags | 0x10;
    if ( watchSlots )
      *(_BYTE *)(v14 + 20) |= 0x20u;
  }
  if ( !Mem_GetAllocFlag() )
  {
    ppForm = Rules_CopyPPBuffer();
    Rules_ReplaceConstructPPForm(v22, (int)ppForm);
  }
  Class_BuildModuleScopeBitmap(v16);
  return Class_GenerateDefaultSlotHandlersAndFlag(v17);
}
// 4D3CF2: variable 'v4' is possibly undefined
// 4D3D09: variable 'v7' is possibly undefined
// 4D3D15: variable 'v8' is possibly undefined
// 4D3D1C: variable 'v9' is possibly undefined
// 4D3D23: variable 'v10' is possibly undefined
// 4D3D2A: variable 'v11' is possibly undefined
// 4D3D31: variable 'v12' is possibly undefined
// 4D3D38: variable 'v13' is possibly undefined
// 4D3D3D: variable 'v14' is possibly undefined
// 4D3DA1: variable 'v22' is possibly undefined
// 4D3D58: variable 'v16' is possibly undefined
// 4D3D5F: variable 'v17' is possibly undefined

//----- (004D3DC0) --------------------------------------------------------
unsigned __int16  Rules_LinkClassToSuperclasses(int theDefclass)
{
  int v1; // ecx
  unsigned int superclassIndex; // esi
  int linkOffset; // edi
  unsigned __int16 result; // ax
  int theSuperclass; // eax

  v1 = theDefclass;
  superclassIndex = 0;
  linkOffset = 0;
  result = *(_WORD *)(theDefclass + 34);
  if ( result )
  {
    do
    {
      theSuperclass = *(_DWORD *)(linkOffset + *(_DWORD *)(v1 + 36));
      linkOffset += 4;
      ++superclassIndex;
      Class_InsertLinkEntry((unsigned __int16 *)(theSuperclass + 40), v1, -1);
      result = *(_WORD *)(v1 + 34);
    }
    while ( superclassIndex < result );
  }
  return result;
}
// 4D3DDB: variable 'v1' is possibly undefined

//----- (004D3E10) --------------------------------------------------------
_DWORD * Rules_BuildInheritedSlotArray(int theDefclass)
{
  unsigned int precedenceIndex; // ebp
  int *slotLinks; // esi
  _DWORD *result; // eax
  unsigned int slotIndex; // edx
  int templateOffset; // ebp
  int *curLink; // eax
  _BYTE *theSlot; // ebx
  unsigned int slotCount; // [esp+0h] [ebp-24h] BYREF
  _DWORD *templateSlotPtr; // [esp+4h] [ebp-20h]
  int precedenceOffset; // [esp+8h] [ebp-1Ch]

  slotCount = 0;
  precedenceIndex = 1;
  slotLinks = Class_AppendNonPrivateSlotLinks(0, theDefclass, 0, &slotCount);
  precedenceOffset = 4;
  while ( precedenceIndex < *(unsigned __int16 *)(theDefclass + 46) )
  {
    ++precedenceIndex;
    slotLinks = Class_AppendNonPrivateSlotLinks(slotLinks, *(_DWORD *)(precedenceOffset + *(_DWORD *)(theDefclass + 48)), 1, &slotCount);
    precedenceOffset += 4;
  }
  result = (_DWORD *)slotCount;
  *(_DWORD *)(theDefclass + 68) = 0;
  *(_DWORD *)(theDefclass + 72) = result;
  if ( slotCount )
  {
    result = Mem_SmallBlockAlloc(4 * slotCount);
    *(_DWORD *)(theDefclass + 56) = result;
  }
  slotIndex = 0;
  if ( slotCount )
  {
    templateOffset = 0;
    do
    {
      templateSlotPtr = (_DWORD *)(templateOffset + *(_DWORD *)(theDefclass + 56));
      curLink = slotLinks;
      theSlot = (_BYTE *)*slotLinks;
      slotLinks = (int *)slotLinks[1];
      *templateSlotPtr = theSlot;
      if ( (*theSlot & 1) == 0 )
        ++*(_DWORD *)(theDefclass + 68);
      g_ClipsMemFreeListTemp = (int)curLink;
      *curLink = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = (_DWORD *)g_ClipsMemoryTable;
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      ++slotIndex;
      templateOffset += 4;
    }
    while ( slotIndex < slotCount );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D3F00) --------------------------------------------------------
_DWORD * Class_BuildSlotIndexMap(_DWORD *result)
{
  _DWORD *theDefclass; // edx
  int v2; // ecx
  unsigned int slotIndex; // ecx
  int templateOffset; // eax
  unsigned int slotNameID; // esi
  _DWORD *v6; // eax
  _DWORD *v7; // edx
  unsigned int mapIndex; // ecx
  int mapOffset; // eax
  int slotOffset; // ecx

  theDefclass = result;
  result[19] = 0;
  v2 = result[18];
  result[15] = 0;
  if ( v2 )
  {
    slotIndex = 0;
    if ( result[18] )
    {
      templateOffset = 0;
      do
      {
        slotNameID = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theDefclass[14] + templateOffset) + 8) + 8);
        if ( slotNameID > theDefclass[19] )
          theDefclass[19] = slotNameID;
        ++slotIndex;
        templateOffset += 4;
      }
      while ( slotIndex < theDefclass[18] );
    }
    v6 = Mem_SmallBlockAlloc(4 * (theDefclass[19] + 1));
    v7[15] = v6;
    mapIndex = 0;
    mapOffset = 0;
    do
    {
      *(_DWORD *)(v7[15] + mapOffset) = 0;
      ++mapIndex;
      mapOffset += 4;
    }
    while ( mapIndex <= v7[19] );
    result = 0;
    if ( v7[18] )
    {
      slotOffset = 0;
      do
      {
        result = (_DWORD *)((char *)result + 1);
        *(_DWORD *)(v7[15] + 4 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(slotOffset + v7[14]) + 8) + 8)) = result;
        slotOffset += 4;
      }
      while ( (unsigned int)result < v7[18] );
    }
  }
  return result;
}
// 4D3F5D: variable 'v7' is possibly undefined

//----- (004D3FC0) --------------------------------------------------------
int * Class_AppendNonPrivateSlotLinks(int *linkList, int theDefclass, int inherited, _DWORD *slotCount)
{
  int slotIndex; // ebp
  int slotOffset; // edi
  int slotDesc; // ebx
  int *i; // eax
  _DWORD *v9; // edx
  int *newLink; // eax
  bool notInherited; // [esp+8h] [ebp-10h]

  slotIndex = *(_DWORD *)(theDefclass + 64) - 1;
  if ( slotIndex >= 0 )
  {
    notInherited = inherited == 0;
    slotOffset = 44 * slotIndex;
    do
    {
      slotDesc = slotOffset + *(_DWORD *)(theDefclass + 52);
      if ( (*(_BYTE *)slotDesc & 8) == 0 || notInherited )
      {
        for ( i = linkList; i; i = (int *)i[1] )
        {
          if ( *(_DWORD *)(slotDesc + 8) == *(_DWORD *)(*i + 8) )
            break;
        }
        if ( !i )
        {
          v9 = *(_DWORD **)(g_ClipsMemoryTable + 32);
          if ( v9 )
          {
            g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 32);
            *(_DWORD *)(g_ClipsMemoryTable + 32) = *v9;
            newLink = (int *)g_ClipsMemFreeListTemp;
          }
          else
          {
            newLink = (int *)Mem_HeapAllocWithRetry((_DWORD *)8);
          }
          *newLink = slotDesc;
          newLink[1] = (int)linkList;
          linkList = newLink;
          ++*slotCount;
        }
      }
      slotOffset -= 44;
      --slotIndex;
    }
    while ( slotOffset >= 0 );
  }
  return linkList;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D4070) --------------------------------------------------------
_DWORD * Class_FlattenSlotLinksToArray(int theDefclass, int *slotLinks)
{
  int *i; // edi
  _DWORD *result; // eax
  int v5; // ebp
  int arrayOffset; // edx
  int *linkEntry; // ebp
  const void *srcSlot; // esi
  _DWORD *slotIndex; // [esp+0h] [ebp-1Ch]
  int *curLink; // [esp+4h] [ebp-18h]

  for ( i = slotLinks; slotLinks; slotLinks = (int *)slotLinks[1] )
  {
    *(_DWORD *)(*slotLinks + 4) = theDefclass;
    ++*(_DWORD *)(theDefclass + 64);
  }
  curLink = i;
  slotIndex = 0;
  result = Mem_SmallBlockAlloc(44 * *(_DWORD *)(theDefclass + 64));
  v5 = *(_DWORD *)(theDefclass + 64);
  *(_DWORD *)(theDefclass + 52) = result;
  if ( v5 )
  {
    arrayOffset = 0;
    do
    {
      linkEntry = curLink;
      srcSlot = (const void *)*curLink;
      curLink = (int *)curLink[1];
      qmemcpy((void *)(arrayOffset + *(_DWORD *)(theDefclass + 52)), srcSlot, 0x2Cu);
      *(_DWORD *)(arrayOffset + *(_DWORD *)(theDefclass + 52) + 32) = arrayOffset + *(_DWORD *)(theDefclass + 52);
      *(_DWORD *)(arrayOffset + *(_DWORD *)(theDefclass + 52) + 40) = 0;
      g_ClipsMemFreeListTemp = *linkEntry;
      *(_DWORD *)g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 176);
      *(_DWORD *)(g_ClipsMemoryTable + 176) = g_ClipsMemFreeListTemp;
      g_ClipsMemFreeListTemp = (int)linkEntry;
      *linkEntry = *(_DWORD *)(g_ClipsMemoryTable + 32);
      result = (_DWORD *)((char *)slotIndex + 1);
      *(_DWORD *)(g_ClipsMemoryTable + 32) = g_ClipsMemFreeListTemp;
      arrayOffset += 44;
      slotIndex = result;
    }
    while ( (unsigned int)result < *(_DWORD *)(theDefclass + 64) );
  }
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004D4170) --------------------------------------------------------
signed int  Class_BuildModuleScopeBitmap(_DWORD *theDefclass)
{
  int moduleCount; // eax
  int i; // edi
  int moduleID; // esi
  _DWORD *v4; // ecx
  _BYTE *bytePtr; // ebx
  int bitmapValue; // eax
  int bitmapSize; // [esp+4h] [ebp-28h]
  _BYTE *className; // [esp+Ch] [ebp-20h]
  _BYTE *scopeMap; // [esp+10h] [ebp-1Ch]

  className = *(_BYTE **)(*theDefclass + 16);
  moduleCount = Module_GetModuleCount();
  bitmapSize = ((moduleCount - (__CFSHL__(moduleCount >> 31, 3) + 8 * (moduleCount >> 31))) >> 3) + 1;
  scopeMap = Mem_SmallBlockAlloc(bitmapSize);
  Mem_AllocArray(scopeMap, bitmapSize);
  Module_BeginEnum();
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(i) )
  {
    Module_SetCurrent(i);
    moduleID = *(_DWORD *)(i + 24);
    if ( Rules_FindImportExportConstruct(aDefclass_4, v4, className, 1, 0) )
    {
      bytePtr = &scopeMap[(moduleID - (__CFSHL__(moduleID >> 31, 3) + 8 * (moduleID >> 31))) >> 3];
      *bytePtr |= 1 << (moduleID % 8);
    }
  }
  Module_EndEnum();
  bitmapValue = Rules_AddBitmapValue(scopeMap, bitmapSize);
  theDefclass[26] = bitmapValue;
  ++*(_DWORD *)(bitmapValue + 4);
  return Mem_SmallBlockFree(scopeMap, bitmapSize);
}
// 4D41E6: variable 'v4' is possibly undefined

//----- (004D4260) --------------------------------------------------------
_DWORD * Class_GenerateDefaultSlotHandlersAndFlag(_DWORD *result)
{
  _DWORD *theDefclass; // edx
  int slotOffset; // ebx
  unsigned int slotIndex; // ecx
  unsigned int handlerIndex; // ebx
  int handlerOffset; // ecx

  theDefclass = result;
  if ( result[16] )
  {
    slotOffset = 0;
    do
    {
      result = (_DWORD *)Class_GeneratePublicSlotHandlers(slotOffset + theDefclass[13]);
      slotOffset += 44;
    }
    while ( slotIndex < theDefclass[16] );
  }
  handlerIndex = 0;
  if ( theDefclass[24] )
  {
    handlerOffset = 0;
    do
    {
      result = (_DWORD *)theDefclass[22];
      LOBYTE(result[handlerOffset]) |= 1u;
      ++handlerIndex;
      handlerOffset += 9;
    }
    while ( handlerIndex < theDefclass[24] );
  }
  return result;
}
// 4D4273: variable 'v1' is possibly undefined
// 4D4286: variable 'v3' is possibly undefined

//----- (004D42C0) --------------------------------------------------------
int  Class_BrowseClassesCommand(int a1, double a2)
{
  int *theDefclass; // eax
  int result; // eax
  int v4; // ecx
  int argValue; // [esp-8h] [ebp-24h] BYREF
  int v6; // [esp+0h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-8h]

  v7 = a1;
  if ( !Rules_RtnArgCount() )
  {
    theDefclass = Class_LookupByQualifiedName(aObject_1);
    return Class_PrintClassBrowse((int)g_IO_LogicalName_WDisplay, (int)theDefclass, 0);
  }
  result = Lexer_ParseValueList(1, &argValue, 2, a2);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(v6 + 16));
    if ( !theDefclass )
      return Class_ReportLookupError(v4, *(_DWORD *)(v6 + 16));
    return Class_PrintClassBrowse((int)g_IO_LogicalName_WDisplay, (int)theDefclass, 0);
  }
  return result;
}
// 4D4327: variable 'v4' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004D4350) --------------------------------------------------------
int * Class_DescribeClassCommand(int a1, double a2)
{
  int *result; // eax
  int v3; // ecx

  result = (int *)Class_ParseClassNameArg(a1, a2);
  if ( result )
  {
    result = Class_LookupClassOrReportError(v3, result);
    if ( result )
      return (int *)Class_PrintClassDescription((int)g_IO_LogicalName_WDisplay, (int)result);
  }
  return result;
}
// 4D4368: variable 'v3' is possibly undefined
// 51A624: using guessed type char *off_51A624;

//----- (004D4390) --------------------------------------------------------
signed int  Class_PrintClassDescription(int logicalName, int theDefclass)
{
  int v4; // ecx
  char *classTraitString; // edx
  int maxOverrideMessageLength; // ebp
  int slotCount; // edi
  unsigned int slotIndex; // ebx
  int slotOffset; // edx
  unsigned int slotNameLength; // kr04_4
  int slotDesc; // ecx
  unsigned int overrideMessageLength; // kr08_4
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int precedenceIndex; // ecx
  int precedenceOffset; // edx
  char buf[84]; // [esp+0h] [ebp-88h] BYREF
  char slotNamePrintFormat[12]; // [esp+54h] [ebp-34h] BYREF
  char overrideMessagePrintFormat[12]; // [esp+60h] [ebp-28h] BYREF
  int logicalOutName; // [esp+6Ch] [ebp-1Ch]
  int maxSlotNameLength; // [esp+70h] [ebp-18h]

  logicalOutName = logicalName;
  Class_PrintSeparatorLine(logicalName, (int)buf, 61, 82);
  Class_PrintSeparatorLine(logicalOutName, (int)buf, 42, 82);
  if ( (*(_BYTE *)(theDefclass + 20) & 4) != 0 )
  {
    classTraitString = aAbstractDirect;
  }
  else
  {
    Output_Write(logicalOutName, (int)aConcreteDirect, v4);
    if ( (*(_BYTE *)(theDefclass + 20) & 8) != 0 )
      classTraitString = aReactiveDirect;
    else
      classTraitString = aNonReactiveDir;
  }
  Output_Write(logicalOutName, (int)classTraitString, v4);
  Class_PrintNameList(logicalOutName, (int)aDirectSupercla, (unsigned __int16 *)(theDefclass + 34));
  Class_PrintNameList(logicalOutName, (int)aInheritancePre, (unsigned __int16 *)(theDefclass + 46));
  Class_PrintNameList(logicalOutName, (int)aDirectSubclass, (unsigned __int16 *)(theDefclass + 40));
  if ( *(_DWORD *)(theDefclass + 56) )
  {
    maxOverrideMessageLength = 8;
    Class_PrintSeparatorLine(logicalOutName, (int)buf, 45, 82);
    slotCount = *(_DWORD *)(theDefclass + 72);
    slotIndex = 0;
    maxSlotNameLength = 5;
    if ( slotCount )
    {
      slotOffset = 0;
      do
      {
        slotNameLength = strlen(*(const char **)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(theDefclass + 56) + slotOffset) + 8) + 12) + 16))
            + 1;
        if ( (int)(slotNameLength - 1) > maxSlotNameLength )
          maxSlotNameLength = slotNameLength - 1;
        slotDesc = *(_DWORD *)(*(_DWORD *)(theDefclass + 56) + slotOffset);
        if ( (*(_BYTE *)slotDesc & 0x10) == 0 )
        {
          overrideMessageLength = strlen(*(const char **)(*(_DWORD *)(slotDesc + 12) + 16)) + 1;
          if ( (int)(overrideMessageLength - 1) > maxOverrideMessageLength )
            maxOverrideMessageLength = overrideMessageLength - 1;
        }
        ++slotIndex;
        slotOffset += 4;
      }
      while ( slotIndex < *(_DWORD *)(theDefclass + 72) );
    }
    if ( maxSlotNameLength > 16 )
      maxSlotNameLength = 16;
    if ( maxOverrideMessageLength > 12 )
      maxOverrideMessageLength = 12;
    sprintf_(slotNamePrintFormat, "%%-%d.%ds : ", maxSlotNameLength, maxSlotNameLength);
    sprintf_(overrideMessagePrintFormat, "%%-%d.%ds ", maxOverrideMessageLength, maxOverrideMessageLength);
    Class_PrintSlotBasicInfoTable(logicalOutName, slotNamePrintFormat, buf, overrideMessagePrintFormat, theDefclass);
    Output_Write(logicalOutName, (int)aConstraintInfo, 82);
    Class_PrintSlotConstraintTable(logicalOutName, slotNamePrintFormat, v13, buf, theDefclass);
  }
  if ( *(_DWORD *)(theDefclass + 96) )
  {
LABEL_19:
    Class_PrintSeparatorLine(logicalOutName, (int)buf, 45, 82);
    Output_Write(logicalOutName, (int)aRecognizedMess, v14);
    MessageHandler_CountAndPrintHandlers(logicalOutName, (unsigned __int16 *)(theDefclass + 46), v15, 0);
  }
  else
  {
    precedenceIndex = 1;
    precedenceOffset = 4;
    while ( precedenceIndex < *(unsigned __int16 *)(theDefclass + 46) )
    {
      if ( *(_DWORD *)(*(_DWORD *)(precedenceOffset + *(_DWORD *)(theDefclass + 48)) + 96) )
        goto LABEL_19;
      precedenceOffset += 4;
      ++precedenceIndex;
    }
  }
  Class_PrintSeparatorLine(logicalOutName, (int)buf, 42, 82);
  return Class_PrintSeparatorLine(logicalOutName, (int)buf, 61, 82);
}
// 4D43D9: variable 'v4' is possibly undefined
// 4D4527: variable 'v13' is possibly undefined
// 4D4550: variable 'v14' is possibly undefined
// 4D455E: variable 'v15' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D45E0) --------------------------------------------------------
char * Class_SlotAccessModeString(int slotDesc)
{
  char accessFlags; // bl
  char accessFlags2; // cl

  accessFlags = *(_BYTE *)(slotDesc + 1);
  if ( (accessFlags & 8) != 0 && (accessFlags & 0x10) != 0 )
    return aRw_0;
  accessFlags2 = *(_BYTE *)(slotDesc + 1);
  if ( (accessFlags2 & 8) == 0 && (accessFlags2 & 0x10) == 0 )
    return aNil_6;
  if ( (*(_BYTE *)(slotDesc + 1) & 8) != 0 )
    return aR_6;
  return aW_6;
}

//----- (004D4630) --------------------------------------------------------
int __thiscall Class_DefclassModuleCommand(void *this)
{
  return Rules_GetConstructModuleCommand((int)this, (const char **)g_ClipsDefclassConstructType);
}
// 54E6B8: using guessed type int dword_54E6B8;

//----- (004D4650) --------------------------------------------------------
signed int  Class_SuperclassPCommand(double a1)
{
  signed int result; // eax
  int *c1; // [esp+0h] [ebp-10h] BYREF
  int *c2; // [esp+4h] [ebp-Ch] BYREF

  result = Class_ParseTwoClassNameArgs(&c1, &c2, a1);
  if ( result )
    return Class_HasSuperclass((int)c2, (int)c1);
  return result;
}

//----- (004D46A0) --------------------------------------------------------
signed int  Class_SubclassPCommand(double a1)
{
  signed int result; // eax
  int *c1; // [esp+0h] [ebp-10h] BYREF
  int *c2; // [esp+4h] [ebp-Ch] BYREF

  result = Class_ParseTwoClassNameArgs(&c1, &c2, a1);
  if ( result )
    return Class_HasSuperclass((int)c1, (int)c2);
  return result;
}

//----- (004D46F0) --------------------------------------------------------
signed int  Class_SlotExistPCommand(int *a1, double a2)
{
  signed int result; // eax
  int inheritFlag; // esi
  signed int slotDesc; // edi
  int v5; // ecx
  int argValue; // [esp-8h] [ebp-30h] BYREF
  int *v7[6]; // [esp+10h] [ebp-18h] BYREF

  v7[4] = a1;
  result = Class_CheckSlotExists((int)aSlotExistp_0, v7, 1, 0, a2);
  inheritFlag = 0;
  slotDesc = result;
  if ( result )
  {
    if ( Rules_RtnArgCount() == 3 )
    {
      result = Lexer_ParseValueList(3, &argValue, 2, a2);
      if ( !result )
        return result;
      if ( strcmp_(v5, aInherit_0) )
      {
        Parser_ReportError(3, (int)aKeywordInher_0);
        Lexer_ErrorRecover(1);
        return 0;
      }
      inheritFlag = 1;
    }
    if ( v7[0] == *(int **)(slotDesc + 4) )
      return 1;
    else
      return inheritFlag;
  }
  return result;
}
// 4D4762: variable 'v5' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D47C0) --------------------------------------------------------
signed int  Class_MessageHandlerExistPCommand(double a1)
{
  signed int handlerType; // esi
  signed int result; // eax
  int v3; // ecx
  int *theDefclass; // edi
  int handlerName; // ebp
  _DWORD argValue[2]; // [esp+0h] [ebp-30h] BYREF
  int v7; // [esp+8h] [ebp-28h]

  handlerType = 2;
  result = Lexer_ParseValueList(1, argValue, 2, a1);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName(*(_BYTE **)(v7 + 16));
    if ( !theDefclass )
    {
      Class_ReportLookupError(v3, *(_DWORD *)(v7 + 16));
      return 0;
    }
    result = Lexer_ParseValueList(2, argValue, 2, a1);
    if ( result )
    {
      handlerName = v7;
      if ( Rules_RtnArgCount() == 3 )
      {
        result = Lexer_ParseValueList(3, argValue, 2, a1);
        if ( !result )
          return result;
        handlerType = MessageHandler_TypeIndexFromKeyword((int)aMessageHandl_8);
        if ( handlerType == 4 )
        {
          Lexer_ErrorRecover(1);
          return 0;
        }
      }
      result = (signed int)Class_FindMessageHandler(theDefclass, handlerName, handlerType);
      if ( result )
        return 1;
    }
  }
  return result;
}
// 4D482B: variable 'v3' is possibly undefined

//----- (004D48B0) --------------------------------------------------------
_BYTE * Class_SlotWritablePCommand(int *a1, double a2)
{
  _BYTE *result; // eax
  int *classBuffer[4]; // [esp-Ch] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = (_BYTE *)Class_CheckSlotExists((int)aSlotWritable_0, classBuffer, 1, 1, a2);
  if ( result )
    return (_BYTE *)((*result & 0x10) == 0);
  return result;
}

//----- (004D4910) --------------------------------------------------------
_BYTE * Class_SlotInitablePCommand(int *a1, double a2)
{
  _BYTE *result; // eax
  int *classBuffer[4]; // [esp-Ch] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = (_BYTE *)Class_CheckSlotExists((int)aSlotInitable_0, classBuffer, 1, 1, a2);
  if ( result )
    return (_BYTE *)((*result & 0x10) == 0 || (*result & 0x20) != 0);
  return result;
}

//----- (004D4980) --------------------------------------------------------
signed int  Class_SlotPublicPCommand(int *a1, double a2)
{
  signed int result; // eax
  int *classBuffer[4]; // [esp-Ch] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = Class_CheckSlotExists((int)aSlotPublicp_0, classBuffer, 0, 1, a2);
  if ( result )
    return (*(_BYTE *)(result + 1) & 4) != 0;
  return result;
}

//----- (004D49E0) --------------------------------------------------------
signed int  Class_SlotDirectAccessPCommand(int *a1, double a2)
{
  signed int result; // eax
  int *classBuffer[4]; // [esp+0h] [ebp-10h] BYREF

  classBuffer[2] = a1;
  result = Class_CheckSlotExists((int)aSlotDirectAc_0, classBuffer, 1, 1, a2);
  if ( result )
    return (*(_BYTE *)(result + 1) & 4) != 0 || classBuffer[0] == *(int **)(result + 4);
  return result;
}

//----- (004D4A50) --------------------------------------------------------
signed int  Class_ClassExistPCommand(int a1, double a2)
{
  signed int result; // eax
  _DWORD argValue[9]; // [esp-8h] [ebp-24h] BYREF

  argValue[7] = a1;
  result = Lexer_ParseValueList(1, argValue, 2, a2);
  if ( result )
    return Class_LookupByQualifiedName(*(_BYTE **)(argValue[2] + 16)) != 0;
  return result;
}

//----- (004D4AA0) --------------------------------------------------------
signed int  Class_ParseTwoClassNameArgs(int **c1, int **c2, double a3)
{
  signed int result; // eax
  int *firstClass; // eax
  int v6; // ecx
  int *secondClass; // eax
  _DWORD argValue[2]; // [esp+0h] [ebp-28h] BYREF
  int v9; // [esp+8h] [ebp-20h]

  result = Lexer_ParseValueList(1, argValue, 2, a3);
  if ( result )
  {
    firstClass = Class_LookupByQualifiedName(*(_BYTE **)(v9 + 16));
    *c1 = firstClass;
    if ( firstClass )
    {
      result = Lexer_ParseValueList(2, argValue, 2, a3);
      if ( !result )
        return result;
      secondClass = Class_LookupByQualifiedName(*(_BYTE **)(v9 + 16));
      *c2 = secondClass;
      if ( secondClass )
        return 1;
    }
    Class_ReportLookupError(v6, *(_DWORD *)(v9 + 16));
    return 0;
  }
  return result;
}
// 4D4B02: variable 'v6' is possibly undefined

//----- (004D4B30) --------------------------------------------------------
signed int  Class_CheckSlotExists(int functionName, int **classBuffer, int inheritFlag, int reportError, double a5)
{
  signed int result; // eax
  unsigned int slotIndex; // eax
  int v11; // ecx
  int *cls; // edx
  int slotDesc; // edi
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx

  result = Class_ParseClassReference(classBuffer, inheritFlag, a5);
  if ( result )
  {
    slotIndex = Instance_ResolveSlotIndex(result, result);
    if ( slotIndex == -1 )
    {
      if ( reportError )
      {
        Instance_ReportNoSuchSlotError(v11, functionName);
        Lexer_ErrorRecover(1);
      }
      return 0;
    }
    else
    {
      cls = *classBuffer;
      slotDesc = *(_DWORD *)((*classBuffer)[14] + 4 * slotIndex);
      if ( cls == *(int **)(slotDesc + 4) || inheritFlag )
      {
        return slotDesc;
      }
      else
      {
        Rules_PrintErrorID((int)aClassexm, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInheritedSlot, v14);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v15 + 16), v15);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFromClass, v16);
        Class_PrintName(*(_DWORD *)(slotDesc + 4), 0);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsNotValidForF, v17);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], functionName, v18);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50CE14, v19);
        Lexer_ErrorRecover(1);
        return 0;
      }
    }
  }
  return result;
}
// 4D4B61: variable 'v11' is possibly undefined
// 4D4BA6: variable 'v14' is possibly undefined
// 4D4BB0: variable 'v15' is possibly undefined
// 4D4BC4: variable 'v16' is possibly undefined
// 4D4BE0: variable 'v17' is possibly undefined
// 4D4BEC: variable 'v18' is possibly undefined
// 4D4BFB: variable 'v19' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004D4C10) --------------------------------------------------------
int * Class_ResolveSlotBySymbolName(_BYTE *slotName, int inheritFlag)
{
  int *result; // eax
  int v3; // ecx
  unsigned int slotIndex; // eax
  int v5; // ecx

  result = Rules_FindSymbolEntry(slotName);
  if ( result )
  {
    slotIndex = Instance_ResolveSlotIndex(v3, (int)result);
    if ( slotIndex == -1 )
      return 0;
    result = *(int **)(*(_DWORD *)(v5 + 56) + 4 * slotIndex);
    if ( v5 != result[1] && !inheritFlag )
      return 0;
  }
  return result;
}
// 4D4C24: variable 'v3' is possibly undefined
// 4D4C2E: variable 'v5' is possibly undefined

//----- (004D4C50) --------------------------------------------------------
int *__fastcall Class_LookupClassOrReportError(int a1, _BYTE *className)
{
  int *result; // eax
  int v3; // ecx

  result = Class_LookupByQualifiedName(className);
  if ( !result )
  {
    Class_ReportLookupError(v3, (int)className);
    return 0;
  }
  return result;
}
// 4D4C68: variable 'v3' is possibly undefined

//----- (004D4C80) --------------------------------------------------------
signed int  Class_ParseClassNameArg(int functionName, double a2)
{
  signed int result; // eax
  _DWORD argValue[9]; // [esp-8h] [ebp-24h] BYREF

  argValue[7] = functionName;
  result = Lexer_ParseValueList(1, argValue, 2, a2);
  if ( result )
    return *(_DWORD *)(argValue[2] + 16);
  return result;
}

//----- (004D4CB0) --------------------------------------------------------
signed int  Class_PrintClassBrowse(int logicalName, int theDefclass, unsigned int depth)
{
  int v3; // ecx
  unsigned int i; // esi
  int v6; // eax
  int v7; // ecx
  int v8; // ecx
  signed int result; // eax
  int v10; // ecx
  unsigned int subclassIndex; // edi
  int subclassOffset; // esi

  v3 = logicalName;
  for ( i = 0; i < depth; ++i )
    Output_Write(v3, (int)asc_50CE18, v3);
  v6 = Rules_GetConstructNameString(theDefclass);
  Output_Write(v7, v6, v7);
  if ( *(_WORD *)(theDefclass + 34) > 1u )
    Output_Write(v8, (int)asc_50CE1C, v8);
  result = Output_Write(v8, (int)asc_50CE14, v8);
  subclassIndex = 0;
  subclassOffset = 0;
  while ( subclassIndex < *(unsigned __int16 *)(theDefclass + 40) )
  {
    subclassOffset += 4;
    ++subclassIndex;
    result = Class_PrintClassBrowse(v10, *(_DWORD *)(*(_DWORD *)(theDefclass + 42) + subclassOffset - 4), depth + 1);
  }
  return result;
}
// 4D4CCB: variable 'v3' is possibly undefined
// 4D4CEB: variable 'v7' is possibly undefined
// 4D4D24: variable 'v8' is possibly undefined
// 4D4D3B: variable 'v10' is possibly undefined

//----- (004D4D50) --------------------------------------------------------
signed int  Class_PrintSeparatorLine(int logicalName, int buf, char sepChar, int lineWidth)
{
  int bufBase; // esi
  int fillCount; // ecx
  int i; // eax

  bufBase = buf;
  fillCount = lineWidth - 2;
  for ( i = 0; i < fillCount; *(_BYTE *)(buf - 1) = sepChar )
  {
    ++buf;
    ++i;
  }
  *(_BYTE *)(i + bufBase) = 10;
  *(_BYTE *)(bufBase + i + 1) = 0;
  return Output_Write(logicalName, bufBase, fillCount);
}
