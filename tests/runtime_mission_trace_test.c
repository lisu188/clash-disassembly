#include "runtime_mission_trace.h"

#include <stdio.h>
#include <string.h>

#define TEST_DATA_SIZE 600000
#define ACTIVE_MISSION_OFFSET 140017
#define GAME_TURN_OFFSET 140022
#define TURN_OWNER_OFFSET 147139
#define STACK_TABLE_OFFSET 147174
#define STACK_STRIDE 725
#define STACK_SLOT_BASE_OFFSET 6
#define STACK_SLOT_STRIDE 31
#define BUILDING_TABLE_OFFSET 509674
#define BUILDING_STRIDE 467
#define BUILDING_CONSTRUCTION_OFFSET 16
#define BUILDING_GARRISON_BASE_OFFSET 18
#define BUILDING_GARRISON_STRIDE 31

unsigned char gameData[TEST_DATA_SIZE];

static void WriteU16(unsigned char *data, unsigned int value)
{
  data[0] = (unsigned char)(value & 0xFFu);
  data[1] = (unsigned char)((value >> 8) & 0xFFu);
}

static void WriteI32(unsigned char *data, int value)
{
  unsigned int bits;

  bits = (unsigned int)value;
  data[0] = (unsigned char)(bits & 0xFFu);
  data[1] = (unsigned char)((bits >> 8) & 0xFFu);
  data[2] = (unsigned char)((bits >> 16) & 0xFFu);
  data[3] = (unsigned char)((bits >> 24) & 0xFFu);
}

static int Require(int condition, const char *message)
{
  if ( condition )
    return 1;
  fprintf(stderr, "runtime_mission_trace_test: %s\n", message);
  return 0;
}

int main(void)
{
  RuntimeMissionTraceSummary first;
  RuntimeMissionTraceSummary second;
  unsigned char *building;
  unsigned char *stack;
  int slot_index;

  memset(gameData, 0, sizeof(gameData));
  WriteI32(gameData + ACTIVE_MISSION_OFFSET, 5);
  WriteU16(gameData + GAME_TURN_OFFSET, 7);
  WriteI32(gameData + TURN_OWNER_OFFSET, 1);

  building = gameData + BUILDING_TABLE_OFFSET + BUILDING_STRIDE * 4;
  building[0] = 44;
  building[1] = 28;
  building[2] = 3;
  WriteU16(building + BUILDING_CONSTRUCTION_OFFSET, 0);
  for ( slot_index = 0; slot_index < 12; ++slot_index )
    WriteU16(building + BUILDING_GARRISON_BASE_OFFSET + BUILDING_GARRISON_STRIDE * slot_index, 0xFFFFu);
  WriteU16(building + BUILDING_GARRISON_BASE_OFFSET, 1);
  WriteU16(building + BUILDING_GARRISON_BASE_OFFSET + BUILDING_GARRISON_STRIDE * 4, 2);

  stack = gameData + STACK_TABLE_OFFSET + STACK_STRIDE * 6;
  WriteU16(stack, 87);
  WriteU16(stack + 2, 66);
  stack[4] = 3;
  for ( slot_index = 0; slot_index < 10; ++slot_index )
    WriteU16(stack + STACK_SLOT_BASE_OFFSET + STACK_SLOT_STRIDE * slot_index, 0xFFFFu);
  WriteU16(stack + STACK_SLOT_BASE_OFFSET, 3);
  WriteU16(stack + STACK_SLOT_BASE_OFFSET + STACK_SLOT_STRIDE, 4);
  WriteU16(stack + STACK_SLOT_BASE_OFFSET + STACK_SLOT_STRIDE * 9, 5);

  if ( !Require(RuntimeMissionTrace_CollectSummary(gameData, 3, &first), "collection failed") )
    return 1;
  if ( !Require(first.mission_index == 5, "mission index mismatch") )
    return 1;
  if ( !Require(first.game_turn == 7, "turn mismatch") )
    return 1;
  if ( !Require(first.turn_owner_player_index == 1, "turn owner mismatch") )
    return 1;
  if ( !Require(first.target_building_count == 1, "building count mismatch") )
    return 1;
  if ( !Require(first.target_stack_count == 1, "stack count mismatch") )
    return 1;
  if ( !Require(first.target_garrison_unit_count == 2, "garrison count mismatch") )
    return 1;
  if ( !Require(first.target_world_unit_count == 3, "world unit count mismatch") )
    return 1;

  stack[0] = 88;
  if ( !Require(RuntimeMissionTrace_CollectSummary(gameData, 3, &second), "second collection failed") )
    return 1;
  if ( !Require(first.fingerprint != second.fingerprint, "fingerprint did not change") )
    return 1;
  if ( !Require(!RuntimeMissionTrace_CollectSummary(gameData, -1, &second), "invalid player accepted") )
    return 1;

  return 0;
}
