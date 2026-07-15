/* Generated from src/recovered/units/0040F510_units.inc.c; original address order retained. */
#include "../recovered_internal.h"

CLASH95_TEST_VISIBLE const char *UnitType_GetResourceKey (int unit_type);

//----- (00412C00) --------------------------------------------------------
int  Building_CalcGarrisonStrength(int buildingRecord, signed int playerIndex)
{
  int wallDefenseBonus; // ebx
  int v3; // edx
  int garrisonCount; // eax
  char *garrisonSlots; // ecx

  wallDefenseBonus = Building_CalcWallDefenseBonus(buildingRecord, playerIndex);
  garrisonCount = Building_CountGarrison(v3);
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck(garrisonSlots, garrisonCount, wallDefenseBonus);
}
// 412C11: variable 'v3' is possibly undefined
// 412C1A: variable 'v5' is possibly undefined

//----- (00412C30) --------------------------------------------------------
int  Player_CalcMilitaryStrength(signed int playerIndex)
{
  int totalStrength; // ecx
  int buildingIndex; // edx
  int v4; // eax
  int buildingStrength; // eax
  int v6; // ecx
  int i; // ebx
  int stackRecordBase; // edx
  int stackStrength; // eax
  int v10; // ecx

  totalStrength = 0;
  buildingIndex = 0;
LABEL_2:
  v4 = UNIT_RECORD(buildingIndex);
  if ( (unsigned int)*(char *)(v4 + 4) < 4
    && *(__int16 *)(v4 + 16) != -1
    && *(unsigned __int8 *)(gameData + BUILDING_RECORD_SIZE * buildingIndex + 509676) == playerIndex )
  {
    buildingStrength = Building_CalcGarrisonStrength(UNIT_RECORD(buildingIndex), playerIndex);
    totalStrength = buildingStrength + v6;
  }
  while ( ++buildingIndex < 100 )
  {
    if ( buildingIndex >= 0 )
      goto LABEL_2;
  }
  for ( i = 0; i < 500; ++i )
  {
    stackRecordBase = gameData + UNIT_STACK_STRIDE * i;
    if ( playerIndex == *(unsigned __int8 *)(stackRecordBase + 147178) && *(__int16 *)(stackRecordBase + 147180) != -1 )
    {
      stackStrength = UnitStack_CalcMilitaryStrength(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * i);
      totalStrength = stackStrength + v10;
    }
  }
  return totalStrength;
}
// 412C9C: conditional instruction was optimized away because edx.4<64u
// 412C56: simplified comparisons for 'ebx.4': <0 || >=4 became >=4u
// 412C8D: variable 'v6' is possibly undefined
// 412C8F: variable 'v3' is possibly undefined
// 412CE8: variable 'v10' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (00412D00) --------------------------------------------------------
_DWORD * UnitTrackElementStack_BuildBlank(_DWORD *result)
{
  *result = 0;
  return result;
}

//----- (00412D20) --------------------------------------------------------
int  UnitStack_CopyFromTemplate(int destStack, int srcStack, int a3)
{
  int v4; // eax
  int result; // eax
  int v7; // [esp-8h] [ebp-Ch]

  *(_WORD *)destStack = *(_WORD *)srcStack;
  *(_WORD *)(destStack + 2) = *(_WORD *)(srcStack + 2);
  *(_BYTE *)(destStack + 4) = *(_BYTE *)(srcStack + 4);
  *(_BYTE *)(destStack + 5) = *(_BYTE *)(srcStack + 5);
  *(_DWORD *)(_wcpp_4_copy_array__(a3) + 310) = *(_DWORD *)(srcStack + 316);
  v4 = _wcpp_4_copy_array__(v7);
  *(_BYTE *)(v4 + 400) = *(_BYTE *)(srcStack + 720);
  result = v4 - 320;
  *(_DWORD *)(result + 721) = *(_DWORD *)(srcStack + 721);
  return result;
}
// 412D20: could not find valid save-restore pair for esi
// 412D74: variable 'v7' is possibly undefined
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00412DA0) --------------------------------------------------------
int  BattleUnitEntry_CopyMergingPackedFlags(int result, int srcEntry)
{
  char dstByte12Base; // bl
  char srcField12Low; // cl
  char byte12Merged; // bh
  char srcField12Mid; // cl
  char byte12Merged2; // bl
  char srcField12High; // cl
  char byte12Final; // ch
  char dstByte13Base; // bl
  int srcFlags13; // ecx
  int srcFlags13b; // ecx
  int srcFlags13c; // ecx
  int v13; // ecx
  char dstByte17Base; // bl
  char dstByte22Base; // bh

  *(_WORD *)result = *(_WORD *)srcEntry;
  *(_BYTE *)(result + 2) = *(_BYTE *)(srcEntry + 2);
  *(_BYTE *)(result + 3) = *(_BYTE *)(srcEntry + 3);
  *(_WORD *)(result + 4) = *(_WORD *)(srcEntry + 4);
  *(_WORD *)(result + 6) = *(_WORD *)(srcEntry + 6);
  *(_BYTE *)(result + 8) = *(_BYTE *)(srcEntry + 8);
  *(_BYTE *)(result + 9) = *(_BYTE *)(srcEntry + 9);
  *(_BYTE *)(result + 10) = *(_BYTE *)(srcEntry + 10);
  *(_BYTE *)(result + 11) = *(_BYTE *)(srcEntry + 11);
  dstByte12Base = *(_BYTE *)(result + 12) & 0xFC;
  srcField12Low = *(_BYTE *)(srcEntry + 12) & 3;
  *(_BYTE *)(result + 12) = dstByte12Base;
  byte12Merged = srcField12Low | dstByte12Base;
  *(_BYTE *)(result + 12) = srcField12Low | dstByte12Base;
  srcField12Mid = *(_BYTE *)(srcEntry + 12) & 0xC;
  *(_BYTE *)(result + 12) = byte12Merged & 0xF3;
  byte12Merged2 = srcField12Mid | byte12Merged & 0xF3;
  *(_BYTE *)(result + 12) = byte12Merged2;
  srcField12High = *(_BYTE *)(srcEntry + 12) & 0x70;
  *(_BYTE *)(result + 12) = byte12Merged2 & 0x8F;
  byte12Final = srcField12High | byte12Merged2 & 0x8F;
  dstByte13Base = *(_BYTE *)(result + 13);
  *(_BYTE *)(result + 12) = byte12Final;
  srcFlags13 = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) = dstByte13Base & 0xFE;
  *(_DWORD *)(result + 13) |= srcFlags13 & 1;
  srcFlags13b = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) &= ~2u;
  *(_DWORD *)(result + 13) |= srcFlags13b & 2;
  srcFlags13c = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) &= ~4u;
  *(_DWORD *)(result + 13) |= srcFlags13c & 4;
  v13 = *(_DWORD *)(srcEntry + 13);
  *(_BYTE *)(result + 13) &= ~8u;
  *(_DWORD *)(result + 13) |= v13 & 8;
  LOBYTE(v13) = *(_BYTE *)(srcEntry + 17) & 7;
  dstByte17Base = *(_BYTE *)(result + 17) & 0xF8;
  *(_BYTE *)(result + 17) = dstByte17Base;
  *(_BYTE *)(result + 17) = v13 | dstByte17Base;
  *(_DWORD *)(result + 18) = *(_DWORD *)(srcEntry + 18);
  dstByte22Base = *(_BYTE *)(result + 22) & 0xFE;
  LOBYTE(v13) = *(_BYTE *)(srcEntry + 22) & 1;
  *(_BYTE *)(result + 22) = dstByte22Base;
  *(_BYTE *)(result + 22) = v13 | dstByte22Base;
  *(_DWORD *)(result + 23) = *(_DWORD *)(srcEntry + 23);
  *(_DWORD *)(result + 27) = *(_DWORD *)(srcEntry + 27);
  return result;
}

//----- (00412EB0) --------------------------------------------------------
int  UnitTrackElementStack_CopyFromTemplate(_DWORD *destStack, _DWORD *srcStack, int a3)
{
  *destStack = *srcStack;
  return _wcpp_4_copy_array__(a3) - 4;
}
// 475A45: using guessed type int __cdecl _wcpp_4_copy_array__(_DWORD);

//----- (00412EE0) --------------------------------------------------------
int  UnitTrackElement_CopyFromTemplate(int result, int srcElement)
{
  *(_BYTE *)result = *(_BYTE *)srcElement;
  *(_BYTE *)(result + 1) = *(_BYTE *)(srcElement + 1);
  *(_WORD *)(result + 2) = *(_WORD *)(srcElement + 2);
  return result;
}

//----- (00412F00) --------------------------------------------------------
int UnitSpriteCache_ClearAllEntries()
{
  int result; // eax

  for ( result = 0; result != UNIT_SPRITE_CACHE_BYTES; result += UNIT_SPRITE_CACHE_RECORD_STRIDE )
    *(int *)(void *)(g_UnitSpriteCacheRecords + result) = -1;
  return result;
}
// 523F78: using guessed type int dword_523F78;

//----- (00412F30) --------------------------------------------------------
int  UnitSpriteCache_GetOrLoadEntry(
        unsigned __int16 unitType,
        char ownerColor,
        unsigned __int8 animFrame,
        unsigned __int8 facing,
        DWORD a5,
        signed int a6)
{
  int record_index;
  int record_offset;
  int sprite_record;
  unsigned int oldest_tick;
  int oldest_index;
  char path[100]; // [esp+0h] [ebp-78h] BYREF

  (void)a5;
  (void)a6;

  record_index = 0;
  while ( record_index < UNIT_SPRITE_CACHE_RECORD_COUNT
       && *(int *)(void *)(g_UnitSpriteCacheRecords + record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE) != -1 )
    ++record_index;

  if ( record_index == UNIT_SPRITE_CACHE_RECORD_COUNT )
  {
    oldest_tick = 0xFFFFFFFFu;
    oldest_index = 0;
    for ( record_index = 0; record_index < UNIT_SPRITE_CACHE_RECORD_COUNT; ++record_index )
    {
      record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
      if ( oldest_tick > *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) )
      {
        oldest_tick = *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11);
        oldest_index = record_index;
      }
    }
    record_index = oldest_index;
    record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
    sprite_record = *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7);
    if ( sprite_record )
      nfree_(sprite_record);
    *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7) = 0;
  }

  record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
  *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset) = (unsigned __int16)unitType;
  g_UnitSpriteCacheRecords[record_offset + 4] = ownerColor;
  g_UnitSpriteCacheRecords[record_offset + 5] = facing;
  g_UnitSpriteCacheRecords[record_offset + 6] = animFrame;
  *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) = Time_Now(0, 0);

  Unit_BuildGoSpriteFilePath(path, (unsigned __int8)unitType, ownerColor);
  sprite_record = Mem_Alloc(22, 0, 0, 0);
  if ( sprite_record )
    sprite_record = DLXSprite_LoadCachedEntry(sprite_record, path, animFrame + 8 * facing);
  *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7) = sprite_record;
  return sprite_record;
}

int  Unit_SetFlag(unsigned __int16 unitType, char ownerColor, unsigned __int8 animFrame, unsigned __int8 facing, DWORD a5, signed int a6)
{
  return UnitSpriteCache_GetOrLoadEntry(unitType, ownerColor, animFrame, facing, a5, a6);
}
// 412FB8: variable 'v11' is possibly undefined
// 412FDB: variable 'v7' is possibly undefined
// 41300C: variable 'v15' is possibly undefined
// 413024: variable 'v16' is possibly undefined
// 413041: variable 'v18' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 523F88: using guessed type int dword_523F88;
// 523F8F: using guessed type int dword_523F8F;
// 523F93: using guessed type int dword_523F93;

//----- (00413080) --------------------------------------------------------
int  UnitSpriteCache_FindEntryOrLoad(signed int unitType, char ownerColor, unsigned __int8 animFrame, unsigned __int8 facing)
{
  int record_index;
  int record_offset;

  for ( record_index = 0; record_index < UNIT_SPRITE_CACHE_RECORD_COUNT; ++record_index )
  {
    record_offset = record_index * UNIT_SPRITE_CACHE_RECORD_STRIDE;
    if ( *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset) == (unsigned __int16)unitType
      && g_UnitSpriteCacheRecords[record_offset + 4] == (unsigned char)ownerColor
      && g_UnitSpriteCacheRecords[record_offset + 5] == facing
      && g_UnitSpriteCacheRecords[record_offset + 6] == animFrame )
    {
      *(unsigned int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 11) = Time_Now(0, 0);
      return *(int *)(void *)(g_UnitSpriteCacheRecords + record_offset + 7);
    }
  }
  return Unit_SetFlag(unitType, ownerColor, animFrame, facing, 0, 0);
}
// 4130CF: variable 'v12' is possibly undefined
// 523F88: using guessed type int dword_523F88;
// 523F8F: using guessed type int dword_523F8F;
// 523F93: using guessed type int dword_523F93;

//----- (00413120) --------------------------------------------------------
void  UnitSpriteCache_FreeAllEntries(int a1, DWORD a2)
{
  int i; // edx
  int sprite_record; // ecx

  Debug_Log(a1, -1, a2, (int)aUnitscache_cle);
  for ( i = 0; i != UNIT_SPRITE_CACHE_BYTES; i += UNIT_SPRITE_CACHE_RECORD_STRIDE )
  {
    if ( *(int *)(void *)(g_UnitSpriteCacheRecords + i) == -1 )
      continue;
    sprite_record = *(int *)(void *)(g_UnitSpriteCacheRecords + i + 7);
    *(int *)(void *)(g_UnitSpriteCacheRecords + i) = -1;
    if ( sprite_record )
    {
      nfree_(sprite_record);
      *(int *)(void *)(g_UnitSpriteCacheRecords + i + 7) = 0;
    }
  }
}
// 413166: variable 'v3' is possibly undefined
// 41316B: variable 'v5' is possibly undefined
// 4740DD: using guessed type int __thiscall nfree_(_DWORD);
// 523F88: using guessed type int dword_523F88;
// 523F8F: using guessed type int dword_523F8F;

//----- (00413180) --------------------------------------------------------
int UnitSpriteCache_CountActiveEntries()
{
  int activeCount; // edx
  int i; // eax

  activeCount = 0;
  for ( i = 0; i != 1500; i += 15 )
  {
    if ( *(int *)((char *)&g_UnitSpriteCacheTableBase + i) != -1 )
      ++activeCount;
  }
  return activeCount;
}
// 523F88: using guessed type int dword_523F88;

CLASH95_TEST_VISIBLE const char *UnitType_GetResourceKey(int unit_type)
{
  static const char *resource_keys[35] = {
    "peon",
    "infl",
    "infh",
    "sprl",
    "sprh",
    "cavl",
    "cavh",
    "ryc",
    "drag",
    "arch",
    "kusza",
    "muszk",
    "katap",
    "taran",
    "armat",
    "lesn",
    "goral",
    "budow",
    "worm",
    "slon",
    "cykl",
    "trol",
    "scorp",
    "szk",
    "mag",
    "duch",
    "orzel",
    "pegaz",
    "skrz",
    "wazka",
    "smok",
    "gold",
    "peas",
    "specm",
    "speck"
  };

  if ( unit_type < 0 || unit_type >= (int)(sizeof(resource_keys) / sizeof(resource_keys[0])) )
    return "peon";
  return resource_keys[unit_type];
}

//----- (004131B0) --------------------------------------------------------
char  Unit_BuildGoSpriteFilePath(char *destPath, unsigned __int8 unitType, char variantDigit)
{
  char *srcPrefix; // esi
  char *writePrefix; // edi
  char prefixChar; // al
  char prefixChar2; // al
  char *srcKey; // esi
  char *writeKey; // edi
  char keyChar; // al
  char keyChar2; // al
  char *srcVariant; // esi
  char *writeVariant; // edi
  char variantChar; // al
  char variantChar2; // al
  char *srcExt; // esi
  char *writeExt; // edi
  char result; // al
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  srcPrefix = aUnits_go;
  writePrefix = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
  do
  {
    prefixChar = *srcPrefix;
    *writePrefix = *srcPrefix;
    if ( !prefixChar )
      break;
    prefixChar2 = srcPrefix[1];
    srcPrefix += 2;
    writePrefix[1] = prefixChar2;
    writePrefix += 2;
  }
  while ( prefixChar2 );
  srcKey = (char *)UnitType_GetResourceKey(unitType);
  writeKey = &destPath[strlen(destPath)];
  do
  {
    keyChar = *srcKey;
    *writeKey = *srcKey;
    if ( !keyChar )
      break;
    keyChar2 = srcKey[1];
    srcKey += 2;
    writeKey[1] = keyChar2;
    writeKey += 2;
  }
  while ( keyChar2 );
  srcVariant = variantSuffix;
  writeVariant = &destPath[strlen(destPath)];
  do
  {
    variantChar = *srcVariant;
    *writeVariant = *srcVariant;
    if ( !variantChar )
      break;
    variantChar2 = srcVariant[1];
    srcVariant += 2;
    writeVariant[1] = variantChar2;
    writeVariant += 2;
  }
  while ( variantChar2 );
  srcExt = a_s32;
  writeExt = &destPath[strlen(destPath)];
  do
  {
    result = *srcExt;
    *writeExt = *srcExt;
    if ( !result )
      break;
    result = srcExt[1];
    srcExt += 2;
    writeExt[1] = result;
    writeExt += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413270) --------------------------------------------------------
char  UI_BeginUnitInfo(char *destPath, unsigned __int8 unitType, char variantDigit)
{
  char *srcPrefix; // esi
  char *writePrefix; // edi
  char prefixChar; // al
  char prefixChar2; // al
  char *srcKey; // esi
  char *writeKey; // edi
  char keyChar; // al
  char keyChar2; // al
  char *srcVariant; // esi
  char *writeVariant; // edi
  char variantChar; // al
  char variantChar2; // al
  char *srcInfix; // esi
  char *writeInfix; // edi
  char infixChar; // al
  char infixChar2; // al
  char *srcExt; // esi
  char *writeExt; // edi
  char result; // al
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  srcPrefix = aUnits_i;
  writePrefix = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
  do
  {
    prefixChar = *srcPrefix;
    *writePrefix = *srcPrefix;
    if ( !prefixChar )
      break;
    prefixChar2 = srcPrefix[1];
    srcPrefix += 2;
    writePrefix[1] = prefixChar2;
    writePrefix += 2;
  }
  while ( prefixChar2 );
  srcKey = (char *)UnitType_GetResourceKey(unitType);
  writeKey = &destPath[strlen(destPath)];
  do
  {
    keyChar = *srcKey;
    *writeKey = *srcKey;
    if ( !keyChar )
      break;
    keyChar2 = srcKey[1];
    srcKey += 2;
    writeKey[1] = keyChar2;
    writeKey += 2;
  }
  while ( keyChar2 );
  srcVariant = variantSuffix;
  writeVariant = &destPath[strlen(destPath)];
  do
  {
    variantChar = *srcVariant;
    *writeVariant = *srcVariant;
    if ( !variantChar )
      break;
    variantChar2 = srcVariant[1];
    srcVariant += 2;
    writeVariant[1] = variantChar2;
    writeVariant += 2;
  }
  while ( variantChar2 );
  srcInfix = a_i;
  writeInfix = &destPath[strlen(destPath)];
  do
  {
    infixChar = *srcInfix;
    *writeInfix = *srcInfix;
    if ( !infixChar )
      break;
    infixChar2 = srcInfix[1];
    srcInfix += 2;
    writeInfix[1] = infixChar2;
    writeInfix += 2;
  }
  while ( infixChar2 );
  srcExt = a_s32_0;
  writeExt = &destPath[strlen(destPath)];
  do
  {
    result = *srcExt;
    *writeExt = *srcExt;
    if ( !result )
      break;
    result = srcExt[1];
    srcExt += 2;
    writeExt[1] = result;
    writeExt += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413350) --------------------------------------------------------
char  Unit_BuildGarrisonSlotIconSpritePath(char *destPath, unsigned __int8 unitType, int a3)
{
  char *dirPrefixSrc; // esi
  char *prefixDst; // edi
  char prefixChar; // al
  char prefixChar2; // al
  char *resourceKey; // esi
  char *keyDst; // edi
  char keyChar; // al
  char keyChar2; // al
  char *tagSrc; // esi
  char *tagDst; // edi
  char tagChar; // al
  char tagChar2; // al
  char *suffixSrc; // esi
  char *suffixDst; // edi
  char suffixChar; // al
  char suffixChar2; // al
  char *extSrc; // esi
  char *extDst; // edi
  char result; // al
  char prefixBuffer[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  dirPrefixSrc = aUnits_i_0;
  prefixDst = destPath;
  strcpy(prefixBuffer, "g");
  do
  {
    prefixChar = *dirPrefixSrc;
    *prefixDst = *dirPrefixSrc;
    if ( !prefixChar )
      break;
    prefixChar2 = dirPrefixSrc[1];
    dirPrefixSrc += 2;
    prefixDst[1] = prefixChar2;
    prefixDst += 2;
  }
  while ( prefixChar2 );
  resourceKey = (char *)UnitType_GetResourceKey(unitType);
  keyDst = &destPath[strlen(destPath)];
  do
  {
    keyChar = *resourceKey;
    *keyDst = *resourceKey;
    if ( !keyChar )
      break;
    keyChar2 = resourceKey[1];
    resourceKey += 2;
    keyDst[1] = keyChar2;
    keyDst += 2;
  }
  while ( keyChar2 );
  tagSrc = prefixBuffer;
  tagDst = &destPath[strlen(destPath)];
  do
  {
    tagChar = *tagSrc;
    *tagDst = *tagSrc;
    if ( !tagChar )
      break;
    tagChar2 = tagSrc[1];
    tagSrc += 2;
    tagDst[1] = tagChar2;
    tagDst += 2;
  }
  while ( tagChar2 );
  suffixSrc = a_i_0;
  suffixDst = &destPath[strlen(destPath)];
  do
  {
    suffixChar = *suffixSrc;
    *suffixDst = *suffixSrc;
    if ( !suffixChar )
      break;
    suffixChar2 = suffixSrc[1];
    suffixSrc += 2;
    suffixDst[1] = suffixChar2;
    suffixDst += 2;
  }
  while ( suffixChar2 );
  extSrc = a_s32_4;
  extDst = &destPath[strlen(destPath)];
  do
  {
    result = *extSrc;
    *extDst = *extSrc;
    if ( !result )
      break;
    result = extSrc[1];
    extSrc += 2;
    extDst[1] = result;
    extDst += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413430) --------------------------------------------------------
char  Unit_BuildSelectedUnitPanelIconSpritePath(char *destPath, unsigned __int8 unitType, int a3)
{
  char *unitsDirSrc; // esi
  char *destWrite; // edi
  char dirCh; // al
  char dirChNext; // al
  char *resKeySrc; // esi
  char *resKeyDst; // edi
  char resKeyCh; // al
  char resKeyChNext; // al
  char *prefixSrc; // esi
  char *prefixDst; // edi
  char prefixCh; // al
  char prefixChNext; // al
  char *underscoreISrc; // esi
  char *underscoreIDst; // edi
  char underscoreICh; // al
  char underscoreIChNext; // al
  char *suffixSrc; // esi
  char *suffixDst; // edi
  char result; // al
  char prefixBuffer[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  unitsDirSrc = aUnits_i_1;
  destWrite = destPath;
  strcpy(prefixBuffer, "c");
  do
  {
    dirCh = *unitsDirSrc;
    *destWrite = *unitsDirSrc;
    if ( !dirCh )
      break;
    dirChNext = unitsDirSrc[1];
    unitsDirSrc += 2;
    destWrite[1] = dirChNext;
    destWrite += 2;
  }
  while ( dirChNext );
  resKeySrc = (char *)UnitType_GetResourceKey(unitType);
  resKeyDst = &destPath[strlen(destPath)];
  do
  {
    resKeyCh = *resKeySrc;
    *resKeyDst = *resKeySrc;
    if ( !resKeyCh )
      break;
    resKeyChNext = resKeySrc[1];
    resKeySrc += 2;
    resKeyDst[1] = resKeyChNext;
    resKeyDst += 2;
  }
  while ( resKeyChNext );
  prefixSrc = prefixBuffer;
  prefixDst = &destPath[strlen(destPath)];
  do
  {
    prefixCh = *prefixSrc;
    *prefixDst = *prefixSrc;
    if ( !prefixCh )
      break;
    prefixChNext = prefixSrc[1];
    prefixSrc += 2;
    prefixDst[1] = prefixChNext;
    prefixDst += 2;
  }
  while ( prefixChNext );
  underscoreISrc = a_i_1;
  underscoreIDst = &destPath[strlen(destPath)];
  do
  {
    underscoreICh = *underscoreISrc;
    *underscoreIDst = *underscoreISrc;
    if ( !underscoreICh )
      break;
    underscoreIChNext = underscoreISrc[1];
    underscoreISrc += 2;
    underscoreIDst[1] = underscoreIChNext;
    underscoreIDst += 2;
  }
  while ( underscoreIChNext );
  suffixSrc = a_s32_5;
  suffixDst = &destPath[strlen(destPath)];
  do
  {
    result = *suffixSrc;
    *suffixDst = *suffixSrc;
    if ( !result )
      break;
    result = suffixSrc[1];
    suffixSrc += 2;
    suffixDst[1] = result;
    suffixDst += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413510) --------------------------------------------------------
char  Unit_BuildSelectedUnitPanelIconPalettePath(char *destPath, unsigned __int8 unitType, int a3)
{
  char *dirPrefixSrc; // esi
  char *destWrite; // edi
  char dirPrefixCh; // al
  char dirPrefixNextCh; // al
  char *resourceKeySrc; // esi
  char *appendCursor1; // edi
  char resKeyCh; // al
  char resKeyNextCh; // al
  char *prefixSrc; // esi
  char *appendCursor2; // edi
  char prefixCh; // al
  char prefixNextCh; // al
  char *iSuffixSrc; // esi
  char *appendCursor3; // edi
  char iSuffixCh; // al
  char iSuffixNextCh; // al
  char *palExtSrc; // esi
  char *appendCursor4; // edi
  char result; // al
  char prefixBuffer[12]; // [esp+0h] [ebp-14h] BYREF
  int v24; // [esp+Ch] [ebp-8h]

  v24 = a3;
  dirPrefixSrc = aUnits_i_2;
  destWrite = destPath;
  strcpy(prefixBuffer, "c");
  do
  {
    dirPrefixCh = *dirPrefixSrc;
    *destWrite = *dirPrefixSrc;
    if ( !dirPrefixCh )
      break;
    dirPrefixNextCh = dirPrefixSrc[1];
    dirPrefixSrc += 2;
    destWrite[1] = dirPrefixNextCh;
    destWrite += 2;
  }
  while ( dirPrefixNextCh );
  resourceKeySrc = (char *)UnitType_GetResourceKey(unitType);
  appendCursor1 = &destPath[strlen(destPath)];
  do
  {
    resKeyCh = *resourceKeySrc;
    *appendCursor1 = *resourceKeySrc;
    if ( !resKeyCh )
      break;
    resKeyNextCh = resourceKeySrc[1];
    resourceKeySrc += 2;
    appendCursor1[1] = resKeyNextCh;
    appendCursor1 += 2;
  }
  while ( resKeyNextCh );
  prefixSrc = prefixBuffer;
  appendCursor2 = &destPath[strlen(destPath)];
  do
  {
    prefixCh = *prefixSrc;
    *appendCursor2 = *prefixSrc;
    if ( !prefixCh )
      break;
    prefixNextCh = prefixSrc[1];
    prefixSrc += 2;
    appendCursor2[1] = prefixNextCh;
    appendCursor2 += 2;
  }
  while ( prefixNextCh );
  iSuffixSrc = a_i_2;
  appendCursor3 = &destPath[strlen(destPath)];
  do
  {
    iSuffixCh = *iSuffixSrc;
    *appendCursor3 = *iSuffixSrc;
    if ( !iSuffixCh )
      break;
    iSuffixNextCh = iSuffixSrc[1];
    iSuffixSrc += 2;
    appendCursor3[1] = iSuffixNextCh;
    appendCursor3 += 2;
  }
  while ( iSuffixNextCh );
  palExtSrc = a_pal;
  appendCursor4 = &destPath[strlen(destPath)];
  do
  {
    result = *palExtSrc;
    *appendCursor4 = *palExtSrc;
    if ( !result )
      break;
    result = palExtSrc[1];
    palExtSrc += 2;
    appendCursor4[1] = result;
    appendCursor4 += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (004135F0) --------------------------------------------------------
char  Unit_BuildAttackAnimSpritePath(char *destPath, unsigned __int8 unitType, char variantDigit)
{
  char *dirPrefixSrc; // esi
  char *dirPrefixDst; // edi
  char prefixCh; // al
  char prefixNextCh; // al
  char *resKeySrc; // esi
  char *resKeyDst; // edi
  char resKeyCh; // al
  char resKeyNextCh; // al
  char *variantSrc; // esi
  char *variantDst; // edi
  char variantCh; // al
  char variantNextCh; // al
  char *attackTagSrc; // esi
  char *attackTagDst; // edi
  char attackTagCh; // al
  char attackTagNextCh; // al
  char *extSrc; // esi
  char *extDst; // edi
  char result; // al
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  dirPrefixSrc = aUnits_at_1;
  dirPrefixDst = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
  do
  {
    prefixCh = *dirPrefixSrc;
    *dirPrefixDst = *dirPrefixSrc;
    if ( !prefixCh )
      break;
    prefixNextCh = dirPrefixSrc[1];
    dirPrefixSrc += 2;
    dirPrefixDst[1] = prefixNextCh;
    dirPrefixDst += 2;
  }
  while ( prefixNextCh );
  resKeySrc = (char *)UnitType_GetResourceKey(unitType);
  resKeyDst = &destPath[strlen(destPath)];
  do
  {
    resKeyCh = *resKeySrc;
    *resKeyDst = *resKeySrc;
    if ( !resKeyCh )
      break;
    resKeyNextCh = resKeySrc[1];
    resKeySrc += 2;
    resKeyDst[1] = resKeyNextCh;
    resKeyDst += 2;
  }
  while ( resKeyNextCh );
  variantSrc = variantSuffix;
  variantDst = &destPath[strlen(destPath)];
  do
  {
    variantCh = *variantSrc;
    *variantDst = *variantSrc;
    if ( !variantCh )
      break;
    variantNextCh = variantSrc[1];
    variantSrc += 2;
    variantDst[1] = variantNextCh;
    variantDst += 2;
  }
  while ( variantNextCh );
  attackTagSrc = a_a;
  attackTagDst = &destPath[strlen(destPath)];
  do
  {
    attackTagCh = *attackTagSrc;
    *attackTagDst = *attackTagSrc;
    if ( !attackTagCh )
      break;
    attackTagNextCh = attackTagSrc[1];
    attackTagSrc += 2;
    attackTagDst[1] = attackTagNextCh;
    attackTagDst += 2;
  }
  while ( attackTagNextCh );
  extSrc = a_s32_3;
  extDst = &destPath[strlen(destPath)];
  do
  {
    result = *extSrc;
    *extDst = *extSrc;
    if ( !result )
      break;
    result = extSrc[1];
    extSrc += 2;
    extDst[1] = result;
    extDst += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (004136D0) --------------------------------------------------------
char  Unit_BuildShotAnimSpritePath(char *destPath, unsigned __int8 unitType, char variantDigit)
{
  char *prefixSrc; // esi
  char *prefixDst; // edi
  char prefixChar; // al
  char prefixNextChar; // al
  char *keySrc; // esi
  char *keyDst; // edi
  char keyChar; // al
  char keyNextChar; // al
  char *variantSrc; // esi
  char *variantDst; // edi
  char variantChar; // al
  char variantNextChar; // al
  char *sTagSrc; // esi
  char *sTagDst; // edi
  char sTagChar; // al
  char sTagNextChar; // al
  char *suffixSrc; // esi
  char *suffixDst; // edi
  char result; // al
  _BYTE variantSuffix[20]; // [esp+0h] [ebp-14h] BYREF

  prefixSrc = aUnits_at;
  prefixDst = destPath;
  variantSuffix[0] = variantDigit + 49;
  variantSuffix[1] = 0;
  do
  {
    prefixChar = *prefixSrc;
    *prefixDst = *prefixSrc;
    if ( !prefixChar )
      break;
    prefixNextChar = prefixSrc[1];
    prefixSrc += 2;
    prefixDst[1] = prefixNextChar;
    prefixDst += 2;
  }
  while ( prefixNextChar );
  keySrc = (char *)UnitType_GetResourceKey(unitType);
  keyDst = &destPath[strlen(destPath)];
  do
  {
    keyChar = *keySrc;
    *keyDst = *keySrc;
    if ( !keyChar )
      break;
    keyNextChar = keySrc[1];
    keySrc += 2;
    keyDst[1] = keyNextChar;
    keyDst += 2;
  }
  while ( keyNextChar );
  variantSrc = variantSuffix;
  variantDst = &destPath[strlen(destPath)];
  do
  {
    variantChar = *variantSrc;
    *variantDst = *variantSrc;
    if ( !variantChar )
      break;
    variantNextChar = variantSrc[1];
    variantSrc += 2;
    variantDst[1] = variantNextChar;
    variantDst += 2;
  }
  while ( variantNextChar );
  sTagSrc = a_s;
  sTagDst = &destPath[strlen(destPath)];
  do
  {
    sTagChar = *sTagSrc;
    *sTagDst = *sTagSrc;
    if ( !sTagChar )
      break;
    sTagNextChar = sTagSrc[1];
    sTagSrc += 2;
    sTagDst[1] = sTagNextChar;
    sTagDst += 2;
  }
  while ( sTagNextChar );
  suffixSrc = a_s32_1;
  suffixDst = &destPath[strlen(destPath)];
  do
  {
    result = *suffixSrc;
    *suffixDst = *suffixSrc;
    if ( !result )
      break;
    result = suffixSrc[1];
    suffixSrc += 2;
    suffixDst[1] = result;
    suffixDst += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (004137B0) --------------------------------------------------------
char  Unit_BuildShotAnimPaletteSpritePath(char *destPath, unsigned __int8 unitType)
{
  char *prefixSrc; // esi
  char *destCursor; // edi
  char prefixChar; // al
  char prefixCharNext; // al
  char *resourceKeySrc; // esi
  char *resourceKeyCursor; // edi
  char resourceKeyChar; // al
  char resourceKeyCharNext; // al
  char *paletteSuffixSrc; // esi
  char *paletteSuffixCursor; // edi
  char paletteSuffixChar; // al
  char paletteSuffixCharNext; // al
  char *extSuffixSrc; // esi
  char *extSuffixCursor; // edi
  char result; // al

  prefixSrc = aUnits_at_0;
  destCursor = destPath;
  do
  {
    prefixChar = *prefixSrc;
    *destCursor = *prefixSrc;
    if ( !prefixChar )
      break;
    prefixCharNext = prefixSrc[1];
    prefixSrc += 2;
    destCursor[1] = prefixCharNext;
    destCursor += 2;
  }
  while ( prefixCharNext );
  resourceKeySrc = (char *)UnitType_GetResourceKey(unitType);
  resourceKeyCursor = &destPath[strlen(destPath)];
  do
  {
    resourceKeyChar = *resourceKeySrc;
    *resourceKeyCursor = *resourceKeySrc;
    if ( !resourceKeyChar )
      break;
    resourceKeyCharNext = resourceKeySrc[1];
    resourceKeySrc += 2;
    resourceKeyCursor[1] = resourceKeyCharNext;
    resourceKeyCursor += 2;
  }
  while ( resourceKeyCharNext );
  paletteSuffixSrc = aUnitSpritePaletteSuffix;
  paletteSuffixCursor = &destPath[strlen(destPath)];
  do
  {
    paletteSuffixChar = *paletteSuffixSrc;
    *paletteSuffixCursor = *paletteSuffixSrc;
    if ( !paletteSuffixChar )
      break;
    paletteSuffixCharNext = paletteSuffixSrc[1];
    paletteSuffixSrc += 2;
    paletteSuffixCursor[1] = paletteSuffixCharNext;
    paletteSuffixCursor += 2;
  }
  while ( paletteSuffixCharNext );
  extSuffixSrc = a_s32_2;
  extSuffixCursor = &destPath[strlen(destPath)];
  do
  {
    result = *extSuffixSrc;
    *extSuffixCursor = *extSuffixSrc;
    if ( !result )
      break;
    result = extSuffixSrc[1];
    extSuffixSrc += 2;
    extSuffixCursor[1] = result;
    extSuffixCursor += 2;
  }
  while ( result );
  return result;
}
// 51256C: using guessed type char *g_UnitTypeResourceKeys;

//----- (00413860) --------------------------------------------------------
void  Unit_BuildBigInfoGraphicPath(char *destPath, unsigned __int8 unitType, int extraLanguageDirName)
{
  char *prefixSrc; // esi
  char *destCursor; // edi
  char prefixChar; // al
  char prefixCharNext; // al
  char *langDirSrc; // esi
  char *langDirCursor; // edi
  char langDirChar; // al
  char langDirCharNext; // al
  char *resourceKeySrc; // esi
  char *resourceKeyCursor; // edi
  char resourceKeyChar; // al
  char resourceKeyCharNext; // al
  char *suffixSrc; // esi
  char *suffixCursor; // edi
  char suffixChar; // al
  char suffixCharNext; // al
  int languageDirNames[7]; // [esp+0h] [ebp-1Ch]

  languageDirNames[5] = extraLanguageDirName;
  languageDirNames[0] = (int)g_LanguageDirectoryNames[0];
  languageDirNames[1] = (int)g_LanguageDirectoryNames[1];
  languageDirNames[2] = (int)g_LanguageDirectoryNames[2];
  prefixSrc = aBiginfo_;
  destCursor = destPath;
  do
  {
    prefixChar = *prefixSrc;
    *destCursor = *prefixSrc;
    if ( !prefixChar )
      break;
    prefixCharNext = prefixSrc[1];
    prefixSrc += 2;
    destCursor[1] = prefixCharNext;
    destCursor += 2;
  }
  while ( prefixCharNext );
  langDirSrc = (char *)languageDirNames[(unsigned __int8)g_LanguageIndex];
  langDirCursor = &destPath[strlen(destPath)];
  do
  {
    langDirChar = *langDirSrc;
    *langDirCursor = *langDirSrc;
    if ( !langDirChar )
      break;
    langDirCharNext = langDirSrc[1];
    langDirSrc += 2;
    langDirCursor[1] = langDirCharNext;
    langDirCursor += 2;
  }
  while ( langDirCharNext );
  resourceKeySrc = (char *)UnitType_GetResourceKey(unitType);
  resourceKeyCursor = &destPath[strlen(destPath)];
  do
  {
    resourceKeyChar = *resourceKeySrc;
    *resourceKeyCursor = *resourceKeySrc;
    if ( !resourceKeyChar )
      break;
    resourceKeyCharNext = resourceKeySrc[1];
    resourceKeySrc += 2;
    resourceKeyCursor[1] = resourceKeyCharNext;
    resourceKeyCursor += 2;
  }
  while ( resourceKeyCharNext );
  suffixSrc = a_gfx_1;
  suffixCursor = &destPath[strlen(destPath)];
  do
  {
    suffixChar = *suffixSrc;
    *suffixCursor = *suffixSrc;
    if ( !suffixChar )
      break;
    suffixCharNext = suffixSrc[1];
    suffixSrc += 2;
    suffixCursor[1] = suffixCharNext;
    suffixCursor += 2;
  }
  while ( suffixCharNext );
  // 413915: falls through to the shared register-restore epilogue at 413918
  // (pop edi/esi/ecx/ebx; retn) shared with sub_413920; in C this is the return.
  return;
}
// 413915: control flows out of bounds to 413918
// 511130: using guessed type char g_LanguageIndex;
// 51256C: using guessed type char *g_UnitTypeResourceKeys;
// 513328: using guessed type char *off_513328[3];

//----- (00413920) --------------------------------------------------------
signed int  UnitStack_BuildMergedTerrainMoveProfile(intptr_t profileRecord, intptr_t stackRecord)
{
  intptr_t slot_record; // esi
  signed int squad_count; // eax
  _BYTE *merged_profile; // ecx
  signed int slot_index; // edx
  int move_profile_offset; // ebx
  int unit_type_id; // eax
  unsigned char candidate_cost; // bl

  *(_DWORD *)(profileRecord + 4) = aUcatblad;
  memset((void *)(profileRecord + 29), 1, 9);
  merged_profile = (_BYTE *)profileRecord;
  slot_record = stackRecord;
  slot_index = 0;
  while ( 1 )
  {
    squad_count = Unit_GetSquadCount(stackRecord);
    if ( slot_index >= squad_count )
      break;
    unit_type_id = *(__int16 *)(slot_record + 6);
    for ( move_profile_offset = 29; move_profile_offset <= 37; ++move_profile_offset )
    {
      candidate_cost = move_profile_offset == 29
                     ? UnitType_GetRoadMoveCost(unit_type_id)
                     : UnitType_GetWorldMoveCost(unit_type_id, move_profile_offset - 30);
      if ( (merged_profile[move_profile_offset] < candidate_cost
         || !candidate_cost)
        && merged_profile[move_profile_offset] )
      {
        merged_profile[move_profile_offset] = candidate_cost;
      }
    }
    slot_record += UNIT_STACK_SLOT_STRIDE;
    ++slot_index;
  }
  return squad_count;
}
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);
// 512568: using guessed type char *(*g_UnitTypeMetadataRecords)[102];

//----- (00413B10) --------------------------------------------------------
signed int Map_InitTerrainMoveTableOffsets()
{
  int terrain_id;

  /*
   * `sub_413B10` writes `dword_524568[eax]` starting at offset `+4`, so the
   * 1024-entry terrain-id lookup table actually begins at `0x52456C`.
   */
  for ( terrain_id = 0; terrain_id <= 3; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 4; terrain_id <= 6; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  g_TerrainMoveProfileOffsets[7] = TERRAIN_MOVE_PROFILE_SWAMP;
  for ( terrain_id = 8; terrain_id <= 15; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 16; terrain_id <= 19; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 20; terrain_id <= 31; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_B;
  for ( terrain_id = 32; terrain_id <= 44; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 45; terrain_id <= 160; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_FOREST;
  for ( terrain_id = 161; terrain_id <= 185; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_HILLS;
  for ( terrain_id = 186; terrain_id <= 221; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_MOUNTAINS;
  for ( terrain_id = 222; terrain_id <= 706; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_WATER;
  for ( terrain_id = 707; terrain_id <= 710; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 711; terrain_id <= 714; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 715; terrain_id <= 745; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_WATER;
  for ( terrain_id = 746; terrain_id <= 750; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_MOUNTAINS;
  for ( terrain_id = 751; terrain_id <= 753; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_PLAIN_A;
  for ( terrain_id = 754; terrain_id <= 756; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  for ( terrain_id = 757; terrain_id <= 770; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_WATER;
  for ( terrain_id = 771; terrain_id < 1024; ++terrain_id )
    g_TerrainMoveProfileOffsets[terrain_id] = TERRAIN_MOVE_PROFILE_DESERT;
  return 1024;
}
// 524568: using guessed type int dword_524568;

//----- (00413DD0) --------------------------------------------------------
int  Map_GetUnitTileMoveCostOrZero(int playerIndex, int unitType, int tileColumn, int tileRow)
{
  unsigned int tileOccupant; // edx
  int occupantStackRecord; // eax
  int unitMetadataOffset; // edi
  unsigned __int16 *terrainRecord; // ecx
  unsigned __int16 *v12; // ecx

  tileOccupant = *(unsigned __int16 *)(2 * tileColumn + gameData + TILE_ROW_STRIDE * tileRow + TILE_MAP_OFFSET);
  if ( (unsigned __int16)tileOccupant != 0xFFFF )
  {
    if ( tileOccupant >= 0x8000 )
      return 0;
    occupantStackRecord = gameData + UNIT_STACK_STRIDE * tileOccupant;
    if ( !*(_BYTE *)(occupantStackRecord + 147894) || *(unsigned __int8 *)(occupantStackRecord + 147178) == playerIndex )
      return 0;
  }
  if ( ((1 << playerIndex) & TILE_TRAP_OWNER_MASK(tileRow, tileColumn)) == 1 << playerIndex || MapTile_GetReligiousSiteCategory(tileRow, tileColumn) )
    return 0;
  unitMetadataOffset = 88 * unitType;
  terrainRecord = TILE_TERRAIN_RECORD(tileRow, tileColumn);
  if ( terrainRecord[2] != 0xFFFF )
    return UnitType_GetRoadMoveCost(unitType);
  if ( !g_PathingAllowBridgeCrossings )
    return UnitType_GetWorldMoveCost(unitType, g_TerrainMoveProfileOffsets[*terrainRecord]);
  return Map_GetBridgeCrossingCostOrZero(tileRow, tileColumn)
      || UnitType_GetWorldMoveCost(unitType, g_TerrainMoveProfileOffsets[*terrainRecord]);
}
// 413E1D: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00413F50) --------------------------------------------------------
signed int  UnitStack_GetTileMoveCostFromMergedProfileOrZero(__int16 *stackPtr, intptr_t mergedProfile, int tileColumn, int tileRow)
{
  int tile_index_ptr; // eax
  unsigned int occupant_stack_index; // edx
  int occupant_stack; // eax
  signed int result; // eax
  unsigned __int16 *terrain_record; // edi

  tile_index_ptr = TILE_INDEX(tileRow, tileColumn);
  occupant_stack_index = *(unsigned __int16 *)tile_index_ptr;
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF
      || (occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index, !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720))
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
    {
      if ( *stackPtr != tileRow || stackPtr[1] != tileColumn )
        return 0;
    }
  }
  occupant_stack_index = *(unsigned __int16 *)TILE_INDEX(tileRow, tileColumn);
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index >= 0x8000 )
      return 0;
    occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index;
    if ( !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720)
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
      return 0;
  }
  if ( ((1 << *((_BYTE *)stackPtr + 4)) & TILE_TRAP_OWNER_MASK(tileRow, tileColumn)) == 1 << *((_BYTE *)stackPtr + 4)
    || MapTile_GetReligiousSiteCategory(tileRow, tileColumn) )
  {
    return 0;
  }
  terrain_record = TILE_TERRAIN_RECORD(tileRow, tileColumn);
  if ( terrain_record[2] != 0xFFFF )
    return *(unsigned __int8 *)(mergedProfile + 29);
  if ( !g_PathingAllowBridgeCrossings )
    return *(unsigned __int8 *)(g_TerrainMoveProfileOffsets[*terrain_record] + mergedProfile + 30);
  result = Map_GetBridgeCrossingCostOrZero(tileRow, tileColumn);
  if ( !result )
    return *(unsigned __int8 *)(g_TerrainMoveProfileOffsets[*terrain_record] + mergedProfile + 30);
  return result;
}
// 41402D: simplified comparisons for 'edx.4': <0 || >=8000 became >=8000u
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00414150) --------------------------------------------------------
signed int  UnitStack_GetTileMoveCostOrZero(__int16 *stackPtr, int tileRow, int a3, int tileColumn)
{
  unsigned int occupant_stack_index; // edx
  int occupant_stack; // eax
  int tile_index_ptr; // eax
  signed int result; // eax
  unsigned __int16 *terrain_record; // ecx
  _BYTE merged_profile[96]; // [esp-1Ch] [ebp-64h] BYREF
  int v16; // [esp+44h] [ebp-4h]

  v16 = a3;
  tile_index_ptr = TILE_INDEX(tileRow, tileColumn);
  occupant_stack_index = *(unsigned __int16 *)tile_index_ptr;
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF
      || (occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index, !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720))
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
    {
      if ( *stackPtr != tileRow || stackPtr[1] != tileColumn )
        return 0;
    }
  }
  UnitStack_BuildMergedTerrainMoveProfile((intptr_t)merged_profile, (intptr_t)stackPtr);
  occupant_stack_index = *(unsigned __int16 *)TILE_INDEX(tileRow, tileColumn);
  if ( occupant_stack_index != 0xFFFF )
  {
    if ( occupant_stack_index > 0x7FFF )
      return 0;
    occupant_stack = gameData + UNIT_STACK_STRIDE * occupant_stack_index;
    if ( !*(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 720)
      || *(_BYTE *)(occupant_stack + UNIT_STACK_TABLE_OFFSET + 4) == *((_BYTE *)stackPtr + 4) )
      return 0;
  }
  if ( ((1 << *((_BYTE *)stackPtr + 4)) & TILE_TRAP_OWNER_MASK(tileRow, tileColumn)) == 1 << *((_BYTE *)stackPtr + 4)
    || MapTile_GetReligiousSiteCategory(tileRow, tileColumn) )
  {
    return 0;
  }
  terrain_record = TILE_TERRAIN_RECORD(tileRow, tileColumn);
  if ( terrain_record[2] != 0xFFFF )
    return merged_profile[29];
  if ( !g_PathingAllowBridgeCrossings )
    return (unsigned __int8)merged_profile[g_TerrainMoveProfileOffsets[*terrain_record] + 30];
  result = Map_GetBridgeCrossingCostOrZero(tileRow, tileColumn);
  if ( !result )
    return (unsigned __int8)merged_profile[g_TerrainMoveProfileOffsets[*terrain_record] + 30];
  return result;
}
// 414194: conditional instruction was optimized away because edx.4<FFFFu
// 5202E4: using guessed type int gameData;
// 52456C: using guessed type int g_TerrainMoveProfileOffsets[1024];
// 52556C: using guessed type int g_PathingAllowBridgeCrossings;

//----- (00414350) --------------------------------------------------------
signed int  UnitStack_GetMoveCostToTile(int stackIndex, int tileRow, int tileColumn)
{
  return UnitStack_GetTileMoveCostOrZero((__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * stackIndex), tileRow, tileRow, tileColumn);
}
// 5202E4: using guessed type int gameData;
