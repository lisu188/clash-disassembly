/* Generated from src/recovered/world_and_persistence/00441DC0_special_sites_savegame.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (0044AE90) --------------------------------------------------------
int  Map_LoadFromFile(uintptr_t mapName)
{
  int scratchAlloc; // rax
  __int16 *tileScratchBuffer; // ebp
  char *nameSrc; // esi
  char *pathDst; // edi
  char nameChar0; // al
  char nameChar1; // al
  int tileByteOffset; // edi
  __int16 *tileSrc; // ebx
  int i; // ecx
  __int16 tileValue; // ax
  __int16 *layerRow; // ebp
  int layerByteOffset; // edi
  __int16 *layerSrc; // ebx
  int j; // ecx
  __int16 layerValue; // ax
  __int16 *layer2Row; // ebp
  int layer2ByteOffset; // edi
  __int16 *layer2Src; // ebx
  int k; // ecx
  int layer2CellAddr; // eax
  _BYTE *trapRow; // edi
  int trapRowIndex; // esi
  _BYTE *trapCell; // ebx
  int m; // ecx
  int widthScanOffset; // edx
  int mapWidthTiles; // eax
  int mapHeightTiles; // eax
  int n; // edx
  int v35; // eax
  int ii; // edx
  int jj; // ecx
  int kk; // eax
  int tileInitRowOffset; // ebp
  int tileInitRowBase; // edi
  int tileInitColIndex; // ecx
  int tileInitColByteOffset; // ebx
  int optionsCopyDst; // edi
  int result; // eax
  char mapPathBuffer[100]; // [esp+0h] [ebp-90h] BYREF
  int readQueryHandle; // [esp+64h] [ebp-2Ch] BYREF
  _BYTE *trapScratchBuffer; // [esp+68h] [ebp-28h]
  uintptr_t mapFileName; // [esp+6Ch] [ebp-24h]
  __int16 *layerScratchBuffer; // [esp+70h] [ebp-20h]
  int tileInitByteRowOffset; // [esp+74h] [ebp-1Ch]

  mapFileName = mapName;
  memset((void *)(uintptr_t)(unsigned int)gameData, 0, GAMEDATA_SAVE_IMAGE_BYTES);
  scratchAlloc = (int)nmalloc_(0x13880, 1);
  tileScratchBuffer = (__int16 *)(uintptr_t)(unsigned int)scratchAlloc;
  if ( !tileScratchBuffer )
    return 0;
  strcpy(mapPathBuffer, aMapsDirectory);
  layerScratchBuffer = (__int16 *)(uintptr_t)(unsigned int)scratchAlloc;
  nameSrc = (char *)mapFileName;
  trapScratchBuffer = (_BYTE *)(uintptr_t)(unsigned int)scratchAlloc;
  pathDst = &mapPathBuffer[strlen(mapPathBuffer)];
  do
  {
    nameChar0 = *nameSrc;
    *pathDst = *nameSrc;
    if ( !nameChar0 )
      break;
    nameChar1 = nameSrc[1];
    nameSrc += 2;
    pathDst[1] = nameChar1;
    pathDst += 2;
  }
  while ( nameChar1 );
  readQueryHandle = FileSystem_ResolveReadPath(mapPathBuffer, 1);
  if ( !readQueryHandle )
  {
    Compat_FreeLow32Bytes(scratchAlloc);
    return 0;
  }
  tileByteOffset = 0;
  Compat_QueryRead(readQueryHandle, tileScratchBuffer, 0x13880);
  do
  {
    tileSrc = tileScratchBuffer;
    for ( i = 0; i != 1400; *(_WORD *)(i + tileByteOffset + gameData - 14) = tileValue )
    {
      i += 14;
      tileValue = *tileSrc++;
    }
    tileByteOffset += 1400;
    tileScratchBuffer += 200;
  }
  while ( tileByteOffset != 140000 );
  layerRow = layerScratchBuffer;
  layerByteOffset = 0;
  Compat_QueryRead(readQueryHandle, layerScratchBuffer, 0x13880);
  do
  {
    layerSrc = layerRow;
    for ( j = 0; j != 1400; *(_WORD *)(j + layerByteOffset + gameData - 12) = layerValue )
    {
      j += 14;
      layerValue = *layerSrc++;
    }
    layerByteOffset += 1400;
    layerRow += 200;
  }
  while ( layerByteOffset != 140000 );
  layer2Row = layerScratchBuffer;
  layer2ByteOffset = 0;
  Compat_QueryRead(readQueryHandle, layerScratchBuffer, 0x13880);
  do
  {
    layer2Src = layer2Row;
    for ( k = 0; k != 1400; k += 14 )
    {
      ++layer2Src;
      layer2CellAddr = layer2ByteOffset + gameData + k;
      *(_WORD *)(layer2CellAddr + 4) = *(layer2Src - 1);
    }
    layer2ByteOffset += 1400;
    layer2Row += 200;
  }
  while ( layer2ByteOffset != 140000 );
  Rules_ResetEngineOnLoad();
  trapRow = trapScratchBuffer;
  trapRowIndex = 0;
  Compat_QueryRead(readQueryHandle, trapScratchBuffer, 0x9C40);
  do
  {
    trapCell = trapRow;
    for ( m = 0; m < 100; ++m )
    {
      if ( *trapCell )
        Rules_LogTrapFact(trapRowIndex, m);
      ++trapCell;
    }
    ++trapRowIndex;
    trapRow += 200;
  }
  while ( trapRowIndex < 100 );
  Compat_QueryRead(readQueryHandle, (void *)(uintptr_t)(unsigned int)(gameData + MAP_THEME_INDEX_OFFSET), 1);
  Compat_FileSystemQueryRelease((int)&g_FileSystemMountTable, &readQueryHandle);
  Compat_FreeLow32Bytes(scratchAlloc);
  widthScanOffset = 0;
  mapWidthTiles = 0;
  do
  {
    if ( *(unsigned __int16 *)(gameData + widthScanOffset) == 0xFFFF )
      break;
    widthScanOffset += 1400;
    ++mapWidthTiles;
  }
  while ( widthScanOffset < 140000 );
  MAP_WIDTH_TILES = mapWidthTiles;
  mapHeightTiles = 0;
  for ( n = 0; n < 1400; n += 14 )
  {
    if ( *(unsigned __int16 *)(gameData + n) == 0xFFFF )
      break;
    ++mapHeightTiles;
  }
  MAP_HEIGHT_TILES = mapHeightTiles;
  Port_FindAndInit();
  Rules_RebuildTempleFacts();
  Rules_RebuildTreasureFacts();
  Rules_RebuildCastleSiteFacts();
  Render_CreateSprite();
  UI_ClearTileHighlight(0);
  *(_DWORD *)(gameData + 147147) = 1;
  *(_DWORD *)(gameData + 147151) = 0;
  *(_DWORD *)(gameData + 147155) = 0;
  *(_DWORD *)(gameData + 147159) = 0;
  MAP_VIEW_LEFT = 0;
  MAP_VIEW_TOP = 0;
  GAME_TURN_COUNTER = 1;
  v35 = gameData;
  VIEWED_PLAYER_INDEX = 0;
  TURN_OWNER_PLAYER_INDEX = VIEWED_PLAYER_INDEX;
  for ( ii = 0; ii != 362500; ii += 725 )
  {
    for ( jj = 0; jj != 310; *(_WORD *)(jj + ii + gameData + 147149) = -1 )
      jj += 31;
  }
  for ( kk = 0; kk != 46700; *(_BYTE *)(gameData + kk + 509211) = -1 )
    kk += 467;
  tileInitRowOffset = 0;
  tileInitByteRowOffset = 0;
  do
  {
    tileInitRowBase = tileInitByteRowOffset;
    tileInitColIndex = 0;
    tileInitColByteOffset = 0;
    do
    {
      *(_WORD *)(tileInitRowOffset + gameData + tileInitColByteOffset + TILE_MAP_OFFSET) = -1;
      ++tileInitColIndex;
      tileInitColByteOffset += 2;
      *(_BYTE *)(tileInitColIndex + tileInitRowBase + gameData + 576373) = 0;
    }
    while ( tileInitColIndex < 100 );
    tileInitRowOffset += 200;
    tileInitByteRowOffset += 100;
  }
  while ( tileInitRowOffset != 20000 );
  optionsCopyDst = gameData + 147147;
  qmemcpy((void *)(gameData + 147147), &g_OptionsConfigRecordBase, 0x18u);
  optionsCopyDst += 24;
  *(_WORD *)optionsCopyDst = *((_WORD *)&g_OptionsConfigRecordBase + 12);
  *(_BYTE *)(optionsCopyDst + 2) = *((_BYTE *)&g_OptionsConfigRecordBase + 26);
  ACTIVE_MISSION_INDEX = -1;
  result = gameData;
  *(_BYTE *)(gameData + MISSION_FAILURE_FLAG_OFFSET) = 0;
  return result;
}
// 44B059: variable 'm' is possibly undefined
// 473FF0: using guessed type __int64 __fastcall nmalloc_(_DWORD, _DWORD);
// 5188B0: using guessed type int dword_5188B0;
// 5202E4: using guessed type int gameData;

//----- (0044B2F0) --------------------------------------------------------
char Scenario_SetupSirArthurRosterVariantA()
{
  int i; // edx
  char *arthurNameSrc; // esi
  char *arthurNameDst; // edi
  char arthurChar0; // al
  char arthurChar1; // al
  char *lesterNameSrc; // esi
  char *lesterNameDst; // edi
  char lesterChar0; // al
  char lesterChar1; // al
  char *computerNameSrc; // esi
  char *computerNameDst; // edi
  char computerChar0; // al
  char computerChar1; // al
  char *tomekNameSrc; // esi
  char *tomekNameDst; // edi
  char result; // al

  for ( i = 0; i < 5; Game_ResetPlayerRuntimeStateByIndex(i) )
    ;
  *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) = 1;
  *(_DWORD *)(gameData + 141447) = 1;
  *(_DWORD *)(gameData + 142870) = 1;
  *(_DWORD *)(gameData + 140051) = 0;
  *(_DWORD *)(gameData + 140051) = 0;
  *(_DWORD *)(gameData + 142897) = 0;
  PLAYER_MINIMAP_VISIBLE(0) = 1;
  arthurNameSrc = aSirArthur;
  arthurNameDst = (char *)(gameData + 140028);
  do
  {
    arthurChar0 = *arthurNameSrc;
    *arthurNameDst = *arthurNameSrc;
    if ( !arthurChar0 )
      break;
    arthurChar1 = arthurNameSrc[1];
    arthurNameSrc += 2;
    arthurNameDst[1] = arthurChar1;
    arthurNameDst += 2;
  }
  while ( arthurChar1 );
  lesterNameSrc = aLester;
  lesterNameDst = (char *)(gameData + 141451);
  do
  {
    lesterChar0 = *lesterNameSrc;
    *lesterNameDst = *lesterNameSrc;
    if ( !lesterChar0 )
      break;
    lesterChar1 = lesterNameSrc[1];
    lesterNameSrc += 2;
    lesterNameDst[1] = lesterChar1;
    lesterNameDst += 2;
  }
  while ( lesterChar1 );
  computerNameSrc = aComputer;
  computerNameDst = (char *)(gameData + 142874);
  do
  {
    computerChar0 = *computerNameSrc;
    *computerNameDst = *computerNameSrc;
    if ( !computerChar0 )
      break;
    computerChar1 = computerNameSrc[1];
    computerNameSrc += 2;
    computerNameDst[1] = computerChar1;
    computerNameDst += 2;
  }
  while ( computerChar1 );
  tomekNameSrc = aTomek;
  tomekNameDst = (char *)(gameData + 144297);
  do
  {
    result = *tomekNameSrc;
    *tomekNameDst = *tomekNameSrc;
    if ( !result )
      break;
    result = tomekNameSrc[1];
    tomekNameSrc += 2;
    tomekNameDst[1] = result;
    tomekNameDst += 2;
  }
  while ( result );
  return result;
}
// 44B2F8: variable 'i' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044B430) --------------------------------------------------------
char Scenario_SetupSirArthurRosterVariantB()
{
  int i; // edx
  char *arthurNameSrc; // esi
  char *arthurNameDst; // edi
  char arthurChar0; // al
  char arthurChar1; // al
  char *lesterNameSrc; // esi
  char *lesterNameDst; // edi
  char lesterChar0; // al
  char lesterChar1; // al
  char *computerNameSrc; // esi
  char *computerNameDst; // edi
  char computerChar0; // al
  char computerChar1; // al
  char *tomekNameSrc; // esi
  char *tomekNameDst; // edi
  char result; // al

  for ( i = 0; i < 5; Game_ResetPlayerRuntimeStateByIndex(i) )
    ;
  *(_DWORD *)(gameData + PLAYER_RUNTIME_STATE_OFFSET) = 1;
  *(_DWORD *)(gameData + 142870) = 1;
  *(_DWORD *)(gameData + 140051) = 1;
  *(_DWORD *)(gameData + 142897) = 0;
  PLAYER_MINIMAP_VISIBLE(0) = 1;
  arthurNameSrc = aSirArthur_0;
  arthurNameDst = (char *)(gameData + 140028);
  do
  {
    arthurChar0 = *arthurNameSrc;
    *arthurNameDst = *arthurNameSrc;
    if ( !arthurChar0 )
      break;
    arthurChar1 = arthurNameSrc[1];
    arthurNameSrc += 2;
    arthurNameDst[1] = arthurChar1;
    arthurNameDst += 2;
  }
  while ( arthurChar1 );
  lesterNameSrc = aLester_0;
  lesterNameDst = (char *)(gameData + 141451);
  do
  {
    lesterChar0 = *lesterNameSrc;
    *lesterNameDst = *lesterNameSrc;
    if ( !lesterChar0 )
      break;
    lesterChar1 = lesterNameSrc[1];
    lesterNameSrc += 2;
    lesterNameDst[1] = lesterChar1;
    lesterNameDst += 2;
  }
  while ( lesterChar1 );
  computerNameSrc = aComputer_0;
  computerNameDst = (char *)(gameData + 142874);
  do
  {
    computerChar0 = *computerNameSrc;
    *computerNameDst = *computerNameSrc;
    if ( !computerChar0 )
      break;
    computerChar1 = computerNameSrc[1];
    computerNameSrc += 2;
    computerNameDst[1] = computerChar1;
    computerNameDst += 2;
  }
  while ( computerChar1 );
  tomekNameSrc = aTomek_0;
  tomekNameDst = (char *)(gameData + 144297);
  do
  {
    result = *tomekNameSrc;
    *tomekNameDst = *tomekNameSrc;
    if ( !result )
      break;
    result = tomekNameSrc[1];
    tomekNameSrc += 2;
    tomekNameDst[1] = result;
    tomekNameDst += 2;
  }
  while ( result );
  return result;
}
// 44B438: variable 'i' is possibly undefined
// 5202E4: using guessed type int gameData;

//----- (0044B550) --------------------------------------------------------
_DWORD * Scenario_SeedCantbellyAndKopegonCastles(int this, DWORD a2, double a3)
{
  int v3; // ecx
  int gameDataBase; // eax
  int buildingRecordOffset; // edx
  char buildingFlagsByte; // bl
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  _DWORD *result; // eax
  int v19; // edx

  Unit_Create(UNIT_TYPE_BUILDER, 0, 5, 0, 4);
  Unit_Create(UNIT_TYPE_RAM, 0, 5, 0, 5);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557384), *(unsigned __int16 *)(gameData + 557382), 0, a2, a3);
  Building_New(1, *(unsigned __int16 *)(gameData + 557382), a3, aCantbelly_3, 1);
  *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
  Unit_UpdatePerTurn(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET, v3);
  *(_DWORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510112) = 1000;
  gameDataBase = gameData;
  buildingRecordOffset = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
  buildingFlagsByte = *(_BYTE *)(buildingRecordOffset + gameData + 510118) & 0xF8;
  *(_BYTE *)(buildingRecordOffset + gameData + 510118) = buildingFlagsByte;
  *(_BYTE *)(buildingRecordOffset + gameDataBase + 510118) = buildingFlagsByte | 2;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 2u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 1u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 8u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 4u;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510090) |= 0x10u;
  *(_DWORD *)(gameData + 140063) = 0;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510119) = 33;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510120) = 2;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510125) = 34;
  *(_BYTE *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 510126) = 4;
  Building_LogBuiltCastleFacts(
    (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557382) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET));
  Unit_Create(UNIT_TYPE_BUILDER, 0, v7, 0, 6);
  Unit_Create(UNIT_TYPE_FLY, 0, 6, 0, 6);
  Unit_Create(UNIT_TYPE_ARCHER, 0, 7, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  Unit_Create(UNIT_TYPE_CYCLOP, 0, v8, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  Unit_Create(UNIT_TYPE_SPECIAL_MOUNTED_PERSONAGE, 0, v9, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  Unit_Create(UNIT_TYPE_HEAVY_SPEARMAN, 0, v10, 0, 7);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557788), *(unsigned __int16 *)(gameData + 557586), 0, a2, a3);
  *(_BYTE *)(gameData + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 557586) + 147189) = 1;
  Unit_Create(UNIT_TYPE_PEGASUS, 2, 10, 0, 7);
  Unit_Create(UNIT_TYPE_WINGER, 0, 10, 0, 8);
  Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, 0, 5, 0, 45);
  Unit_Create(UNIT_TYPE_BUILDER, 0, 5, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, 0, 5, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_EAGLE, 0, v11, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_RAM, 0, v12, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v13, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v14, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v15, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v16, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Unit_Create(UNIT_TYPE_PIKEMAN, 0, v17, 0, 46);
  Unit_AddToGroup(*(unsigned __int16 *)(gameData + 557466), *(unsigned __int16 *)(gameData + 557464), 0, a2, a3);
  Building_New(0, *(unsigned __int16 *)(gameData + 557464), a3, aKopegon, 1);
  *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557464) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
  Unit_UpdatePerTurn(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557464) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET, this);
  result = Building_LogBuiltCastleFacts(
             (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 557464) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET));
  g_CurrentPlayerIndex = v19;
  return result;
}
// 44B611: variable 'v3' is possibly undefined
// 44B7E9: variable 'v7' is possibly undefined
// 44B849: variable 'v8' is possibly undefined
// 44B87F: variable 'v9' is possibly undefined
// 44B8B5: variable 'v10' is possibly undefined
// 44B9C6: variable 'v11' is possibly undefined
// 44B9FC: variable 'v12' is possibly undefined
// 44BA32: variable 'v13' is possibly undefined
// 44BA68: variable 'v14' is possibly undefined
// 44BA9E: variable 'v15' is possibly undefined
// 44BAD4: variable 'v16' is possibly undefined
// 44BB0A: variable 'v17' is possibly undefined
// 44BBCF: variable 'v19' is possibly undefined
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044C2A0) --------------------------------------------------------
signed int Game_InitPlayerViewState()
{
  int playerIndex; // edi
  int playerRecordOffset; // ebp
  int castleIndex; // edx
  int castleRecordOffset; // eax
  int maxCameraLeft; // eax
  int maxCameraTop; // eax
  int humanPlayerIndex; // ecx
  int humanPlayerOffset; // eax
  int activePlayerIndex; // edx
  signed int result; // eax

  playerIndex = 0;
  playerRecordOffset = 0;
  do
  {
    if ( PLAYER_IS_ACTIVE(playerIndex) )
    {
      castleIndex = 0;
      castleRecordOffset = 0;
      while ( *(unsigned __int8 *)(gameData + castleRecordOffset + 509676) != playerIndex )
      {
        castleRecordOffset += BUILDING_RECORD_SIZE;
        ++castleIndex;
        if ( castleRecordOffset >= 46700 )
          goto LABEL_13;
      }
      PLAYER_CAMERA_LEFT(playerIndex) = *(unsigned __int8 *)(gameData + castleRecordOffset + BUILDING_TABLE_OFFSET) - 4;
      if ( PLAYER_CAMERA_LEFT(playerIndex) < 0 )
        PLAYER_CAMERA_LEFT(playerIndex) = 0;
      maxCameraLeft = MAP_WIDTH_TILES - 9;
      if ( maxCameraLeft < PLAYER_CAMERA_LEFT(playerIndex) )
        PLAYER_CAMERA_LEFT(playerIndex) = maxCameraLeft;
      PLAYER_CAMERA_TOP(playerIndex) = *(unsigned __int8 *)(BUILDING_RECORD_SIZE * castleIndex + gameData + 509675) - 3;
      if ( PLAYER_CAMERA_TOP(playerIndex) < 0 )
        PLAYER_CAMERA_TOP(playerIndex) = 0;
      maxCameraTop = MAP_HEIGHT_TILES - 7;
      if ( maxCameraTop < PLAYER_CAMERA_TOP(playerIndex) )
        PLAYER_CAMERA_TOP(playerIndex) = maxCameraTop;
    }
LABEL_13:
    ++playerIndex;
    playerRecordOffset += 1423;
  }
  while ( playerIndex < 5 );
  humanPlayerIndex = 0;
  VIEWED_PLAYER_INDEX = 0;
  humanPlayerOffset = 0;
  while ( !PLAYER_IS_ACTIVE(humanPlayerIndex) || !PLAYER_HAS_HUMAN_CONTROLLER(humanPlayerIndex) )
  {
    humanPlayerOffset += 1423;
    ++humanPlayerIndex;
    if ( humanPlayerOffset >= 7115 )
      goto LABEL_18;
  }
  VIEWED_PLAYER_INDEX = humanPlayerIndex;
LABEL_18:
  activePlayerIndex = 0;
  result = 0;
  while ( !PLAYER_IS_ACTIVE(activePlayerIndex) )
  {
    result += 1423;
    ++activePlayerIndex;
    if ( result >= 7115 )
      return result;
  }
  g_CurrentPlayerIndex = activePlayerIndex;
  TURN_OWNER_PLAYER_INDEX = activePlayerIndex;
  return result;
}
// 5202E4: using guessed type int gameData;
// 5202EC: using guessed type int g_CurrentPlayerIndex;

//----- (0044C400) --------------------------------------------------------
signed int  SaveSlot_LoadReservedSlot10(DWORD a1, double a2)
{
  return SaveSlot_LoadGame(10, a1, a2);
}

//----- (0044C410) --------------------------------------------------------
signed int  Scenario_LoadAllAiMultiplayerMapAndInitView(int mapIndex)
{
  int player_index; // ecx
  _BYTE player_states[PLAYER_DATA_STRIDE * 5]; // [esp+0h] [ebp-1BE4h] BYREF

  for ( player_index = 0; player_index < 5; ++player_index )
    PlayerRuntimeState_ResetDefaults((uintptr_t)&player_states[PLAYER_DATA_STRIDE * player_index]);
  for ( player_index = 0; player_index < 5; ++player_index )
  {
    *(_DWORD *)&player_states[PLAYER_DATA_STRIDE * player_index] = 1;
    *(_DWORD *)&player_states[PLAYER_DATA_STRIDE * player_index + PLAYER_IS_HUMAN_OFFSET] = 0;
  }
  *(_DWORD *)&player_states[PLAYER_DATA_STRIDE + PLAYER_AI_INTELLIGENCE_OFFSET] = 2;
  *(_DWORD *)&player_states[2 * PLAYER_DATA_STRIDE + PLAYER_AI_INTELLIGENCE_OFFSET] = 2;
  *(_DWORD *)&player_states[PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  *(_DWORD *)&player_states[PLAYER_DATA_STRIDE + PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  *(_DWORD *)&player_states[2 * PLAYER_DATA_STRIDE + PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  *(_DWORD *)&player_states[3 * PLAYER_DATA_STRIDE + PLAYER_MINIMAP_VISIBLE_OFFSET] = 1;
  Scenario_LoadMultiplayerMapAndSeedPlayers(mapIndex, (uintptr_t)player_states);
  return Game_InitPlayerViewState();
}

//----- (0044C7F0) --------------------------------------------------------
DWORD  Battle_RunPresetScenarioByIndex(int scenarioIndex, DWORD logCtx, double spawnArg)
{
  int unitStackTableBase; // ebx
  int attackerStackIndex; // edx
  __int16 *defenderStackPtr; // esi
  int attackerStackScaledIndex; // eax
  DWORD result; // eax
  int v8; // ecx
  int attackerFlagRecordOffset; // eax
  char attackerFlagByte; // dl
  int v11; // ecx
  int defenderFlagRecordOffset1; // eax
  char defenderFlagByte1; // bl
  int v14; // ecx
  int defenderFlagRecordOffset2; // eax
  char defenderFlagByte2; // dl
  int v17; // ecx
  int defenderFlagRecordOffset3; // eax
  char defenderFlagByte3; // bl

  switch ( scenarioIndex )
  {
    case 0:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 0;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, UNIT_TYPE_PEASANT, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 1:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_LIGHT_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 2:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 1;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_HEAVY_INFANTRY, UNIT_TYPE_ARCHER, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_PIKEMAN, UNIT_TYPE_PIKEMAN, UNIT_TYPE_ARCHER, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 3:
      *(_WORD *)gameData = 4;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 4;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 0;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, UNIT_TYPE_GORAL, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 4:
      *(_WORD *)gameData = 9;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 9;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_FORESTER, UNIT_TYPE_FORESTER, UNIT_TYPE_CROSSBOWER, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_MUSKETEER, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 5:
      *(_WORD *)gameData = 21;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 21;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 1;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_TROLL, UNIT_TYPE_CATAPULT, UNIT_TYPE_HEAVY_SPEARMAN, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_CATAPULT, UNIT_TYPE_CYCLOP, UNIT_TYPE_SKELETON, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 6:
      *(_WORD *)gameData = 9;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 9;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 0;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_SKELETON, UNIT_TYPE_WORM, UNIT_TYPE_KNIGHTS, -1);
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_SKELETON, UNIT_TYPE_WORM, UNIT_TYPE_KNIGHTS, -1);
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
      goto LABEL_3;
    case 7:
      *(_WORD *)gameData = 4;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 4;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_RAM, UNIT_TYPE_CROSSBOWER, UNIT_TYPE_LIGHT_CAVALRY, -1);
      createCastle(spawnArg, 1, 0, 1, 2, aZamek, UNIT_TYPE_CATAPULT, UNIT_TYPE_CANNON, UNIT_TYPE_CYCLOP, -1);
      return Battle_RunTacticalCombat(
               (__int16 *)(UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET) + gameData + UNIT_STACK_TABLE_OFFSET),
               0,
               0,
               (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 556574) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET),
               logCtx,
               0);
    case 8:
      *(_WORD *)gameData = 0;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 0;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 1;
      createUnit(spawnArg, 0, 0, 1, UNIT_TYPE_CANNON, UNIT_TYPE_GORAL, UNIT_TYPE_HEAVY_INFANTRY, -1);
      createCastle(spawnArg, 1, 0, 0, 2, aZamek_0, UNIT_TYPE_CANNON, UNIT_TYPE_WIZARD, UNIT_TYPE_LIGHT_CAVALRY, -1);
      return Battle_RunTacticalCombat(
               (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET)),
               0,
               0,
               (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + 556574) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET),
               logCtx,
               0);
    case 9:
      *(_WORD *)gameData = 28;
      *(_WORD *)(gameData + TILE_TERRAIN_ROW_STRIDE) = 28;
      *(_BYTE *)(gameData + MAP_THEME_INDEX_OFFSET) = 2;
      createUnit(spawnArg, 0, 0, 0, UNIT_TYPE_GHOST, UNIT_TYPE_WIZARD, UNIT_TYPE_WINGER, -1);
      v8 = gameData;
      attackerFlagRecordOffset = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      attackerFlagByte = *(_BYTE *)(gameData + attackerFlagRecordOffset + 147285) & 0xFC;
      *(_BYTE *)(gameData + attackerFlagRecordOffset + 147285) = attackerFlagByte;
      *(_BYTE *)(v8 + attackerFlagRecordOffset + 147285) = attackerFlagByte | 1;
      createUnit(spawnArg, 1, 0, 1, UNIT_TYPE_DRAGON, UNIT_TYPE_WIZARD, UNIT_TYPE_WIZARD, -1);
      v11 = gameData;
      defenderFlagRecordOffset1 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574);
      defenderFlagByte1 = *(_BYTE *)(gameData + defenderFlagRecordOffset1 + 147223) & 0xFC;
      *(_BYTE *)(gameData + defenderFlagRecordOffset1 + 147223) = defenderFlagByte1;
      *(_BYTE *)(v11 + defenderFlagRecordOffset1 + 147223) = defenderFlagByte1 | 1;
      v14 = gameData;
      defenderFlagRecordOffset2 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574);
      defenderFlagByte2 = *(_BYTE *)(gameData + defenderFlagRecordOffset2 + 147316) & 0xFC;
      *(_BYTE *)(gameData + defenderFlagRecordOffset2 + 147316) = defenderFlagByte2;
      *(_BYTE *)(v14 + defenderFlagRecordOffset2 + 147316) = defenderFlagByte2 | 1;
      v17 = gameData;
      defenderFlagRecordOffset3 = UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574);
      defenderFlagByte3 = *(_BYTE *)(gameData + defenderFlagRecordOffset3 + 147378) & 0xFC;
      *(_BYTE *)(gameData + defenderFlagRecordOffset3 + 147378) = defenderFlagByte3;
      *(_BYTE *)(v17 + defenderFlagRecordOffset3 + 147378) = defenderFlagByte3 | 1;
      unitStackTableBase = gameData + UNIT_STACK_TABLE_OFFSET;
      attackerStackIndex = *(unsigned __int16 *)(gameData + TILE_MAP_OFFSET);
      defenderStackPtr = (__int16 *)(gameData + UNIT_STACK_TABLE_OFFSET + UNIT_STACK_STRIDE * *(unsigned __int16 *)(gameData + 556574));
      attackerStackScaledIndex = 144 * (unsigned __int16)attackerStackIndex;
LABEL_3:
      result = Battle_RunTacticalCombat((__int16 *)(unitStackTableBase + 5 * (attackerStackIndex + attackerStackScaledIndex)), defenderStackPtr, 0, 0, logCtx, 0);
      break;
    default:
      result = 1;
      break;
  }
  return result;
}
// 5202E4: using guessed type int gameData;

//----- (0044D250) --------------------------------------------------------
signed int  Scenario_LoadMultiplayerMapAndSeedPlayers(int mapIndex, uintptr_t playerStatesSource)
{
  double v4; // st7
  int playerIndex; // esi
  int playerRecordPtr; // eax
  DWORD startRowPlus1; // ebp
  int startColumnDoubled; // edi
  int buildingRecordByteOffset; // edx
  int v13; // ecx
  int cavalryColumn; // ebx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int castleRecordByteOffset; // edx
  int v19; // ecx
  int cavalryColumn2; // ebx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int builderColumn; // [esp-4h] [ebp-B4h]
  _BYTE mapPathBuffer[100]; // [esp+0h] [ebp-B0h] BYREF
  int rowMinus1; // [esp+64h] [ebp-4Ch]
  int religionToggle; // [esp+68h] [ebp-48h]
  unsigned int startPosTableIndex; // [esp+6Ch] [ebp-44h]
  int playerRecordOffset; // [esp+70h] [ebp-40h]
  int colPlus3; // [esp+74h] [ebp-3Ch]
  int rowMinus1ByteOffset; // [esp+78h] [ebp-38h]
  int colPlus2; // [esp+7Ch] [ebp-34h]
  int rowPlus2; // [esp+80h] [ebp-30h]
  int startColumn; // [esp+84h] [ebp-2Ch]
  int startRow; // [esp+88h] [ebp-28h]
  int rowByteOffset; // [esp+8Ch] [ebp-24h]
  int rowPlus2ByteOffset; // [esp+90h] [ebp-20h]
  int colMinus1; // [esp+94h] [ebp-1Ch]
  int rowPlus1ByteOffset; // [esp+98h] [ebp-18h]

  v4 = sprintf_(mapPathBuffer, "multi%d.map", mapIndex + 1);
  Map_LoadFromFile((uintptr_t)mapPathBuffer);
  qmemcpy((void *)(gameData + PLAYER_RUNTIME_STATE_OFFSET), (const void *)playerStatesSource, PLAYER_DATA_STRIDE * 5);
  MiniMap_CreateSurface((DWORD)playerStatesSource);
  religionToggle = 1;
  playerIndex = 0;
  playerRecordOffset = 0;
  startPosTableIndex = 40 * mapIndex;
  do
  {
    playerRecordPtr = playerRecordOffset + gameData;
    if ( *(_DWORD *)(playerRecordOffset + gameData + PLAYER_RUNTIME_STATE_OFFSET) )
    {
      startRow = g_MultiplayerStartRows[startPosTableIndex / 4];
      startColumn = g_MultiplayerStartColumns[startPosTableIndex / 4];
      colMinus1 = startColumn - 1;
      colPlus3 = startColumn + 3;
      rowPlus2 = startRow + 2;
      colPlus2 = startColumn + 2;
      rowByteOffset = 200 * startRow;
      startRowPlus1 = startRow + 1;
      rowPlus2ByteOffset = 200 * (startRow + 2);
      rowPlus1ByteOffset = 200 * (startRow + 1);
      startColumnDoubled = 2 * startColumn;
      if ( *(_DWORD *)(playerRecordPtr + 140051) )
      {
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRow, 0, startColumn);
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Building_NewAt(startRow, startColumn, 2, *(unsigned __int16 *)(rowByteOffset + gameData + startColumnDoubled + TILE_MAP_OFFSET), v4, aCantbelly, 1);
        *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
        buildingRecordByteOffset = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
        *(_DWORD *)(buildingRecordByteOffset + gameData + 510112) += 50;
        Unit_UpdatePerTurn(
          BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET,
          v13);
        cavalryColumn = colPlus2;
        Building_LogBuiltCastleFacts(
          (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE)
                            + gameData
                            + BUILDING_TABLE_OFFSET));
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, playerIndex, startRow, 0, cavalryColumn);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colPlus2);
        Unit_Create(UNIT_TYPE_ARCHER, playerIndex, rowPlus2, 0, colPlus2);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556378),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, rowPlus2, 0, colPlus2);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556378),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, playerIndex, rowPlus2, 0, colPlus2);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556378),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRowPlus1, 0, colPlus3);
        Unit_Create(UNIT_TYPE_ARCHER, playerIndex, rowPlus2, 0, colPlus3);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556380),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556380),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, rowPlus2, 0, colMinus1);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
      }
      else
      {
        builderColumn = startColumn;
        *(_DWORD *)(playerRecordPtr + 140063) = religionToggle;
        LOBYTE(religionToggle) = religionToggle ^ 1;
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRow, 0, builderColumn);
        Unit_Create(UNIT_TYPE_PIKEMAN, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_HEAVY_SPEARMAN, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRowPlus1, 0, startColumn);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + TILE_MAP_OFFSET),
          *(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET),
          0,
          startRowPlus1,
          v4);
        Building_NewAt(startRow, startColumn, 2, *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + TILE_MAP_OFFSET), v4, aCantbelly_0, 1);
        *(_WORD *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + 509690) = 0;
        castleRecordByteOffset = BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE);
        *(_DWORD *)(castleRecordByteOffset + gameData + 510112) += 100;
        Unit_UpdatePerTurn(
          BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE) + gameData + BUILDING_TABLE_OFFSET,
          v19);
        cavalryColumn2 = colPlus2;
        Building_LogBuiltCastleFacts(
          (unsigned __int8 *)(BUILDING_RECORD_SIZE * (*(unsigned __int16 *)(gameData + rowByteOffset + startColumnDoubled + TILE_MAP_OFFSET) - TILE_OCCUPANT_BUILDING_INDEX_BASE)
                            + gameData
                            + BUILDING_TABLE_OFFSET));
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, playerIndex, startRow, 0, cavalryColumn2);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colPlus2);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, rowPlus2, 0, colPlus2);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556378),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_CAVALRY, playerIndex, rowPlus2, 0, colPlus2);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556378),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_FORESTER, playerIndex, rowPlus2, 0, colPlus2);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556378),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556378),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, startRowPlus1, 0, colPlus3);
        Unit_Create(UNIT_TYPE_BUILDER, playerIndex, rowPlus2, 0, colPlus3);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556380),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556380),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_ARCHER, playerIndex, rowPlus2, 0, colPlus3);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowPlus2ByteOffset + gameData + 556380),
          *(unsigned __int16 *)(gameData + rowPlus1ByteOffset + startColumnDoubled + 556380),
          0,
          startRowPlus1,
          v4);
        rowMinus1 = startRow - 1;
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRow - 1, 0, colMinus1);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRow, 0, colMinus1);
        rowMinus1ByteOffset = 200 * rowMinus1;
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + 200 * rowMinus1 + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PIKEMAN, playerIndex, startRow, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowMinus1ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PIKEMAN, playerIndex, startRow, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowMinus1ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_PEASANT, playerIndex, startRow, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowMinus1ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRow, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowMinus1ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRow, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowMinus1ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        Unit_Create(UNIT_TYPE_GORAL, playerIndex, startRow, 0, colMinus1);
        Unit_AddToGroup(
          *(unsigned __int16 *)(startColumnDoubled + rowByteOffset + gameData + 556372),
          *(unsigned __int16 *)(gameData + rowMinus1ByteOffset + startColumnDoubled + 556372),
          0,
          startRowPlus1,
          v4);
        if ( *(int *)(playerRecordOffset + gameData + 140055) > 0 )
        {
          Unit_Create(UNIT_TYPE_PEASANT, playerIndex, rowPlus2, 0, colMinus1);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_ARCHER, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_ARCHER, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
          Unit_Create(UNIT_TYPE_LIGHT_INFANTRY, playerIndex, startRowPlus1, 0, colMinus1);
          Unit_AddToGroup(
            *(unsigned __int16 *)(startColumnDoubled + rowPlus1ByteOffset + gameData + 556372),
            *(unsigned __int16 *)(gameData + rowPlus2ByteOffset + startColumnDoubled + 556372),
            0,
            startRowPlus1,
            v4);
        }
      }
    }
    ++playerIndex;
    playerRecordOffset += PLAYER_DATA_STRIDE;
    startPosTableIndex += 8;
  }
  while ( playerIndex < 5 );
  Rules_LogMissionSetupInfo();
  return Game_InitPlayerViewState();
}
// 44D4E8: variable 'v13' is possibly undefined
// 44D536: variable 'v15' is possibly undefined
// 44D607: variable 'v16' is possibly undefined
// 44D6C1: variable 'v17' is possibly undefined
// 44DB7B: variable 'v19' is possibly undefined
// 44DBC9: variable 'v21' is possibly undefined
// 44DC49: variable 'v22' is possibly undefined
// 44DC9A: variable 'v23' is possibly undefined
// 44DD51: variable 'v24' is possibly undefined
// 44DE25: variable 'v25' is possibly undefined
// 44DE76: variable 'v26' is possibly undefined
// 44DEC4: variable 'v27' is possibly undefined
// 44DF15: variable 'v28' is possibly undefined
// 44DFB7: variable 'v29' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 518938: using guessed type int g_MultiplayerStartRows[];
// 51893C: using guessed type int g_MultiplayerStartColumns[];
// 5202E4: using guessed type int gameData;

//----- (0044E2A0) --------------------------------------------------------
char  Player_AssignRandomUniqueRulerNames(int requestedNameCount, int *nameSlotPtrs)
{
  char result; // al
  int assignedCount; // ebp
  unsigned int candidateIndex; // ecx
  int historyScanCount; // edx
  int historyIndex; // eax
  char *candidateNameChars; // esi
  char *destNameChars; // edi
  char nameChar0; // al
  char nameChar1; // al
  int v11; // ecx
  int usedNameHistory[5]; // [esp+0h] [ebp-30h] BYREF
  int nameCount; // [esp+14h] [ebp-1Ch]
  int *slotCursor; // [esp+18h] [ebp-18h]

  nameCount = requestedNameCount;
  result = (char)nameSlotPtrs;
  assignedCount = 0;
  qmemcpy(usedNameHistory, &g_RulerNameHistorySeed, sizeof(usedNameHistory));
  if ( nameCount > 0 )
  {
    slotCursor = nameSlotPtrs;
    while ( 1 )
    {
      candidateIndex = Rng_RandRange(0, 38);
      historyScanCount = 0;
      historyIndex = 0;
      if ( candidateIndex != usedNameHistory[0] )
      {
        do
        {
          ++historyIndex;
          ++historyScanCount;
        }
        while ( historyIndex < 5 && candidateIndex != usedNameHistory[historyIndex] );
      }
      if ( historyScanCount == 5 )
      {
        candidateNameChars = g_RulerNameCandidatesTable[candidateIndex];
        destNameChars = (char *)*slotCursor;
        do
        {
          nameChar0 = *candidateNameChars;
          *destNameChars = *candidateNameChars;
          if ( !nameChar0 )
            break;
          nameChar1 = candidateNameChars[1];
          candidateNameChars += 2;
          destNameChars[1] = nameChar1;
          destNameChars += 2;
        }
        while ( nameChar1 );
        result = Str_TitleCase((_BYTE *)*slotCursor, 5, candidateIndex);
        usedNameHistory[assignedCount++] = v11;
        ++slotCursor;
        if ( assignedCount >= nameCount )
          break;
      }
    }
  }
  return result;
}
// 44E32E: variable 'v11' is possibly undefined
// 518C58: using guessed type char *off_518C58[39];

//----- (0044E350) --------------------------------------------------------
BOOL  UI_RunHoverTooltipZones(__int16 *tooltipZoneTable)
{
  BOOL result; // eax
  int zoneLeft; // edx
  signed int zoneBottom; // ebp
  int mouseY; // ebx
  int tooltipBaseLeft; // edx
  int clampedRight; // ecx
  int tooltipTextBottom; // ebx
  int cursorHeight; // edi
  DWORD v9; // ebp
  int rightOverflow; // eax
  int v11; // ebx
  _DWORD *Surface; // eax
  int v13; // ecx
  int savedBackgroundSurface; // esi
  _DWORD *tooltipSurfacePtr; // eax
  int tooltipSurface; // ebp
  int v17; // edx
  int v18; // ecx
  int v19; // ecx
  int v20; // edx
  int v21; // edx
  int fadeInNow; // eax
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int fadeOutNow; // eax
  int v30; // edx
  int fadeOutStartTime; // [esp+0h] [ebp-4Ch]
  int tooltipLeft; // [esp+4h] [ebp-48h]
  void *previousRenderDevice; // [esp+1Ch] [ebp-30h]
  int tooltipTop; // [esp+20h] [ebp-2Ch]
  int tooltipBottom; // [esp+24h] [ebp-28h]
  int tooltipRight; // [esp+28h] [ebp-24h]
  int fadeStartTime; // [esp+34h] [ebp-18h]
  unsigned __int16 fadeInHeight; // [esp+38h] [ebp-14h]
  unsigned __int16 fadeOutHeight; // [esp+3Ch] [ebp-10h]
  unsigned __int16 fadeOutWidth; // [esp+40h] [ebp-Ch]
  unsigned __int16 fadeInWidth; // [esp+44h] [ebp-8h]

  previousRenderDevice = g_RenderDevice;
  result = DD_IsLost((int)g_RenderState);
  if ( result )
  {
    while ( 1 )
    {
      zoneLeft = *tooltipZoneTable;
      if ( zoneLeft == -1 )
        break;
      zoneBottom = tooltipZoneTable[3];
      if ( g_MouseCursorRawX >> g_CursorCoordShift < zoneLeft
        || g_MouseCursorRawY >> g_CursorCoordShift < tooltipZoneTable[1]
        || g_MouseCursorRawX >> g_CursorCoordShift > tooltipZoneTable[2]
        || g_MouseCursorRawY >> g_CursorCoordShift > zoneBottom
        || !*(_DWORD *)&tooltipZoneTable[2 * (unsigned __int8)g_LanguageIndex + 4] )
      {
        goto LABEL_4;
      }
      Render_ReleaseSurface(8, zoneBottom);
      tooltipTop = g_MouseCursorRawY >> g_CursorCoordShift;
      tooltipRight = (unsigned __int16)Render_LoadResourceSprite_v3(*(_BYTE **)&tooltipZoneTable[2 * (unsigned __int8)g_LanguageIndex + 4])
          + (g_MouseCursorRawX >> g_CursorCoordShift);
      mouseY = g_MouseCursorRawY >> g_CursorCoordShift;
      tooltipTextBottom = UI_GetTextXOffset(g_ActiveTextSpriteSlot) + mouseY;
      tooltipLeft = tooltipBaseLeft;
      tooltipBottom = tooltipTextBottom;
      if ( tooltipBaseLeft + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12) > tooltipRight )
        tooltipRight = tooltipBaseLeft + *(_DWORD *)(g_ActiveCursorDescriptorPtr + 12);
      cursorHeight = *(_DWORD *)(g_ActiveCursorDescriptorPtr + 16);
      v9 = tooltipTextBottom;
      if ( tooltipTop + cursorHeight > tooltipTextBottom )
        tooltipBottom = tooltipTop + cursorHeight;
      if ( tooltipRight > 639 )
      {
        rightOverflow = tooltipRight - 639;
        clampedRight = 639;
        LOWORD(tooltipRight) = 639;
        tooltipLeft = tooltipBaseLeft - rightOverflow;
      }
      v11 = tooltipBottom;
      if ( tooltipBottom > 479 )
      {
        LOWORD(tooltipBottom) = 479;
        tooltipTop -= v11 - 479;
      }
      Surface = (_DWORD *)Mem_Alloc(188, clampedRight, v11, v9);
      if ( Surface )
      {
        LOWORD(v11) = tooltipBottom - tooltipTop + 1;
        Surface = Render_CreateSurface((int)Surface, tooltipRight - tooltipLeft + 1, v11);
      }
      savedBackgroundSurface = (int)Surface;
      tooltipSurfacePtr = (_DWORD *)Mem_Alloc(188, v13, v11, v9);
      if ( tooltipSurfacePtr )
        tooltipSurfacePtr = Render_CreateSurface((int)tooltipSurfacePtr, tooltipRight - tooltipLeft + 1, tooltipBottom - tooltipTop + 1);
      tooltipSurface = (int)tooltipSurfacePtr;
      Render_FillRect(0, (_DWORD *)savedBackgroundSurface, (unsigned __int16)tooltipTop, (unsigned __int16)tooltipLeft, tooltipRight, tooltipBottom, 0, 0);
      Render_SaveBackbuffer((int)&g_MainRenderDevice);
      Render_Pump();
      Render_FillRect(0, (_DWORD *)tooltipSurface, (unsigned __int16)tooltipTop, (unsigned __int16)tooltipLeft, tooltipRight, tooltipBottom, 0, 0);
      Render_Present((int)g_RenderState);
      g_RenderDevice = (_UNKNOWN *)tooltipSurface;
      UI_DrawText(0, 0, *(_DWORD *)&tooltipZoneTable[2 * (unsigned __int8)g_LanguageIndex + 4]);
      fadeStartTime = Time_Now(v18, v17);
      v20 = 30;
      fadeInWidth = tooltipRight - tooltipLeft;
      fadeInHeight = tooltipBottom - tooltipTop;
      while ( Time_Now(v19, v20) < (unsigned int)(fadeStartTime + 30) )
      {
        fadeInNow = Time_Now(fadeStartTime, v21);
        Render_BlendSurfaceRect(0, savedBackgroundSurface, 0, tooltipSurface, 0, fadeInWidth, fadeInHeight, tooltipLeft, tooltipTop, 255 * (fadeInNow - v23) / 0x1Eu);
      }
      Render_FillRect((_DWORD *)tooltipSurface, 0, 0, 0, fadeInWidth, fadeInHeight, tooltipLeft, tooltipTop);
      Render_FlipRect((int)g_RenderState, 0);
      fadeOutStartTime = Time_Now(v25, v24);
      v26 = tooltipLeft;
      v27 = tooltipTop;
      fadeOutWidth = tooltipRight - tooltipLeft;
      fadeOutHeight = tooltipBottom - tooltipTop;
      while ( Time_Now(v26, v27) < (unsigned int)(fadeOutStartTime + 30) )
      {
        fadeOutNow = Time_Now(v28, fadeOutStartTime);
        Render_BlendSurfaceRect(0, tooltipSurface, 0, savedBackgroundSurface, 0, fadeOutWidth, fadeOutHeight, tooltipLeft, tooltipTop, 255 * (fadeOutNow - v30) / 0x1Eu);
      }
      Render_FillRect((_DWORD *)savedBackgroundSurface, 0, 0, 0, fadeOutWidth, fadeOutHeight, tooltipLeft, tooltipTop);
      if ( savedBackgroundSurface )
        (**(void (***)(void))(savedBackgroundSurface + 184))();
      if ( tooltipSurface )
      {
        (**(void (***)(void))(tooltipSurface + 184))();
        tooltipZoneTable += 10;
      }
      else
      {
LABEL_4:
        tooltipZoneTable += 10;
      }
    }
    result = (BOOL)previousRenderDevice;
    g_RenderDevice = previousRenderDevice;
  }
  return result;
}
// 44E456: variable 'v5' is possibly undefined
// 44E4D7: variable 'v6' is possibly undefined
// 44E50B: variable 'v13' is possibly undefined
// 44E5E4: variable 'v18' is possibly undefined
// 44E5E4: variable 'v17' is possibly undefined
// 44E612: variable 'v19' is possibly undefined
// 44E612: variable 'v20' is possibly undefined
// 44E61F: variable 'v21' is possibly undefined
// 44E624: variable 'v23' is possibly undefined
// 44E69D: variable 'v25' is possibly undefined
// 44E69D: variable 'v24' is possibly undefined
// 44E6CD: variable 'v26' is possibly undefined
// 44E6CD: variable 'v27' is possibly undefined
// 44E6DA: variable 'v28' is possibly undefined
// 44E6DF: variable 'v30' is possibly undefined
// 511130: using guessed type char g_LanguageIndex;
// 511230: using guessed type _UNKNOWN *g_RenderDevice;
// 520728: using guessed type int dword_520728;
// 544CD8: using guessed type _DWORD g_RenderState[9];
// 544CFC: using guessed type int dword_544CFC;
// 544D00: using guessed type int dword_544D00;
// 544D14: using guessed type int dword_544D14;
// 54512C: using guessed type char byte_54512C;

//----- (0044E7A0) --------------------------------------------------------
signed int  Prisoner_QueueCapturedUnit(
        char capturedUnitType,
        int capturedUnitOwner,
        __int16 a3,
        int playerIndex,
        DWORD a5,
        __int16 a6)
{
  int playerRecordOffset; // ebx
  int prisonerQueueBase; // ebx
  int slotScanPtr; // edx
  signed int result; // eax
  char capturedOwner; // [esp+4h] [ebp-8h]

  capturedOwner = capturedUnitOwner;
  playerRecordOffset = PLAYER_DATA_STRIDE * playerIndex;
  Debug_Log(capturedUnitOwner, playerRecordOffset, a5, (int)aPrisoner_addto);
  prisonerQueueBase = gameData + PLAYER_RUNTIME_STATE_OFFSET + playerRecordOffset;
  slotScanPtr = prisonerQueueBase;
  result = 0;
  while ( *(char *)(slotScanPtr + 1357) != -1 )
  {
    ++result;
    slotScanPtr += 6;
    if ( result >= 10 )
    {
      if ( result == 10 )
        return result;
      break;
    }
  }
  result *= 3;
  *(_WORD *)(prisonerQueueBase + 2 * result + 1359) = a3;
  *(_BYTE *)(prisonerQueueBase + 2 * result + 1357) = capturedUnitType;
  *(_BYTE *)(prisonerQueueBase + 2 * result + 1358) = capturedOwner;
  *(_WORD *)(prisonerQueueBase + 2 * result + 1361) = a6;
  return result;
}
// 44E7EC: conditional instruction was optimized away because eax.4<A
// 5202E4: using guessed type int gameData;

//----- (0044E850) --------------------------------------------------------
signed int  Building_FindFreePrisonerSlot(int buildingRecord)
{
  signed int result; // eax

  result = 0;
  while ( BUILDING_PRISONER_TYPE(BUILDING_PRISONER_SLOT(buildingRecord, result)) != -1 )
  {
    ++result;
    if ( result >= BUILDING_PRISONER_SLOT_COUNT )
      return -1;
  }
  return result;
}
