#include "runtime_mission_trace.h"

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RUNTIME_MISSION_TRACE_ACTIVE_MISSION_OFFSET 140017
#define RUNTIME_MISSION_TRACE_GAME_TURN_OFFSET 140022
#define RUNTIME_MISSION_TRACE_TURN_OWNER_OFFSET 147139
#define RUNTIME_MISSION_TRACE_STACK_TABLE_OFFSET 147174
#define RUNTIME_MISSION_TRACE_STACK_STRIDE 725
#define RUNTIME_MISSION_TRACE_STACK_COUNT 500
#define RUNTIME_MISSION_TRACE_STACK_OWNER_OFFSET 4
#define RUNTIME_MISSION_TRACE_STACK_SLOT_BASE_OFFSET 6
#define RUNTIME_MISSION_TRACE_STACK_SLOT_STRIDE 31
#define RUNTIME_MISSION_TRACE_STACK_SLOT_COUNT 10
#define RUNTIME_MISSION_TRACE_BUILDING_TABLE_OFFSET 509674
#define RUNTIME_MISSION_TRACE_BUILDING_STRIDE 467
#define RUNTIME_MISSION_TRACE_BUILDING_COUNT 100
#define RUNTIME_MISSION_TRACE_BUILDING_OWNER_OFFSET 2
#define RUNTIME_MISSION_TRACE_BUILDING_CONSTRUCTION_OFFSET 16
#define RUNTIME_MISSION_TRACE_BUILDING_GARRISON_BASE_OFFSET 18
#define RUNTIME_MISSION_TRACE_BUILDING_GARRISON_STRIDE 31
#define RUNTIME_MISSION_TRACE_BUILDING_GARRISON_COUNT 12
#define RUNTIME_MISSION_TRACE_PLAYER_TABLE_OFFSET 140024
#define RUNTIME_MISSION_TRACE_PLAYER_STRIDE 1423
#define RUNTIME_MISSION_TRACE_STACK_SLOT_AP_OFFSET 8
#define RUNTIME_MISSION_TRACE_DEFAULT_MISSION 5
#define RUNTIME_MISSION_TRACE_DEFAULT_TARGET_PLAYER 3
#define RUNTIME_MISSION_TRACE_DEFAULT_INTERVAL_MS 250

typedef struct RuntimeMissionTraceBuilding
{
  int index;
  int row;
  int column;
  int construction_turns_remaining;
  int garrison_units;
} RuntimeMissionTraceBuilding;

typedef struct RuntimeMissionTraceStack
{
  int index;
  int row;
  int column;
  int units;
  int min_action_points;
} RuntimeMissionTraceStack;

typedef struct RuntimeMissionTraceSnapshot
{
  RuntimeMissionTraceSummary summary;
  RuntimeMissionTraceBuilding buildings[RUNTIME_MISSION_TRACE_BUILDING_COUNT];
  RuntimeMissionTraceStack stacks[RUNTIME_MISSION_TRACE_STACK_COUNT];
  RuntimeMissionTraceStack ap_stacks[RUNTIME_MISSION_TRACE_STACK_COUNT];
} RuntimeMissionTraceSnapshot;

static unsigned int RuntimeMissionTrace_ReadU16(const volatile unsigned char *data)
{
  return (unsigned int)data[0] | ((unsigned int)data[1] << 8);
}

static int RuntimeMissionTrace_ReadI16(const volatile unsigned char *data)
{
  return (int)(int16_t)RuntimeMissionTrace_ReadU16(data);
}

static int RuntimeMissionTrace_ReadI32(const volatile unsigned char *data)
{
  uint32_t value;

  value = (uint32_t)data[0]
        | ((uint32_t)data[1] << 8)
        | ((uint32_t)data[2] << 16)
        | ((uint32_t)data[3] << 24);
  return (int)(int32_t)value;
}

static unsigned int RuntimeMissionTrace_HashU32(unsigned int hash, unsigned int value)
{
  int byte_index;

  for ( byte_index = 0; byte_index < 4; ++byte_index )
  {
    hash ^= (value >> (8 * byte_index)) & 0xFFu;
    hash *= 16777619u;
  }
  return hash;
}

static int RuntimeMissionTrace_CountOccupiedSlots(
  const volatile unsigned char *record,
  int slot_base_offset,
  int slot_stride,
  int slot_count)
{
  int slot_index;
  int occupied_count;

  occupied_count = 0;
  for ( slot_index = 0; slot_index < slot_count; ++slot_index )
  {
    if ( RuntimeMissionTrace_ReadI16(record + slot_base_offset + slot_stride * slot_index) != -1 )
      ++occupied_count;
  }
  return occupied_count;
}

static int RuntimeMissionTrace_MinSlotActionPoints(
  const volatile unsigned char *record,
  int slot_base_offset,
  int slot_stride,
  int slot_count)
{
  int slot_index;
  int min_action_points;

  min_action_points = -1;
  for ( slot_index = 0; slot_index < slot_count; ++slot_index )
  {
    const volatile unsigned char *slot;
    int action_points;

    slot = record + slot_base_offset + slot_stride * slot_index;
    if ( RuntimeMissionTrace_ReadI16(slot) == -1 )
      continue;
    action_points = slot[RUNTIME_MISSION_TRACE_STACK_SLOT_AP_OFFSET];
    if ( min_action_points < 0 || action_points < min_action_points )
      min_action_points = action_points;
  }
  return min_action_points;
}

static int RuntimeMissionTrace_CollectStacksForPlayer(
  const volatile unsigned char *volatile_data,
  int player_index,
  RuntimeMissionTraceStack *stacks,
  int *world_unit_count,
  unsigned int *fingerprint,
  unsigned int fingerprint_tag)
{
  int stack_index;
  int collected;

  collected = 0;
  for ( stack_index = 0; stack_index < RUNTIME_MISSION_TRACE_STACK_COUNT; ++stack_index )
  {
    const volatile unsigned char *stack;
    RuntimeMissionTraceStack *trace_stack;
    int units;

    stack = volatile_data
          + RUNTIME_MISSION_TRACE_STACK_TABLE_OFFSET
          + RUNTIME_MISSION_TRACE_STACK_STRIDE * stack_index;
    units = RuntimeMissionTrace_CountOccupiedSlots(
      stack,
      RUNTIME_MISSION_TRACE_STACK_SLOT_BASE_OFFSET,
      RUNTIME_MISSION_TRACE_STACK_SLOT_STRIDE,
      RUNTIME_MISSION_TRACE_STACK_SLOT_COUNT);
    if ( !units || stack[RUNTIME_MISSION_TRACE_STACK_OWNER_OFFSET] != player_index )
      continue;

    trace_stack = &stacks[collected++];
    trace_stack->index = stack_index;
    trace_stack->row = RuntimeMissionTrace_ReadI16(stack);
    trace_stack->column = RuntimeMissionTrace_ReadI16(stack + 2);
    trace_stack->units = units;
    trace_stack->min_action_points = RuntimeMissionTrace_MinSlotActionPoints(
      stack,
      RUNTIME_MISSION_TRACE_STACK_SLOT_BASE_OFFSET,
      RUNTIME_MISSION_TRACE_STACK_SLOT_STRIDE,
      RUNTIME_MISSION_TRACE_STACK_SLOT_COUNT);
    if ( world_unit_count )
      *world_unit_count += units;

    *fingerprint = RuntimeMissionTrace_HashU32(
      *fingerprint,
      fingerprint_tag | (unsigned int)stack_index);
    *fingerprint = RuntimeMissionTrace_HashU32(*fingerprint, (unsigned int)trace_stack->row);
    *fingerprint = RuntimeMissionTrace_HashU32(*fingerprint, (unsigned int)trace_stack->column);
    *fingerprint = RuntimeMissionTrace_HashU32(*fingerprint, (unsigned int)units);
    *fingerprint = RuntimeMissionTrace_HashU32(
      *fingerprint,
      (unsigned int)trace_stack->min_action_points);
  }
  return collected;
}

static int RuntimeMissionTrace_CollectSnapshot(
  const unsigned char *data,
  int target_player_index,
  int ap_player_index,
  RuntimeMissionTraceSnapshot *snapshot)
{
  const volatile unsigned char *volatile_data;
  unsigned int fingerprint;
  int building_index;
  int player_index;

  if ( !data || !snapshot || target_player_index < 0 || target_player_index > 4 )
    return 0;
  if ( ap_player_index < -1 || ap_player_index > 4 )
    return 0;

  memset(snapshot, 0, sizeof(*snapshot));
  volatile_data = (const volatile unsigned char *)data;
  snapshot->summary.mission_index = RuntimeMissionTrace_ReadI32(
    volatile_data + RUNTIME_MISSION_TRACE_ACTIVE_MISSION_OFFSET);
  snapshot->summary.game_turn = RuntimeMissionTrace_ReadU16(
    volatile_data + RUNTIME_MISSION_TRACE_GAME_TURN_OFFSET);
  snapshot->summary.turn_owner_player_index = RuntimeMissionTrace_ReadI32(
    volatile_data + RUNTIME_MISSION_TRACE_TURN_OWNER_OFFSET);
  snapshot->summary.target_player_index = target_player_index;
  snapshot->summary.ap_player_index = ap_player_index;

  fingerprint = 2166136261u;
  fingerprint = RuntimeMissionTrace_HashU32(fingerprint, (unsigned int)snapshot->summary.mission_index);
  fingerprint = RuntimeMissionTrace_HashU32(fingerprint, snapshot->summary.game_turn);
  fingerprint = RuntimeMissionTrace_HashU32(
    fingerprint,
    (unsigned int)snapshot->summary.turn_owner_player_index);
  fingerprint = RuntimeMissionTrace_HashU32(fingerprint, (unsigned int)target_player_index);

  for ( player_index = 0; player_index < RUNTIME_MISSION_TRACE_PLAYER_COUNT; ++player_index )
  {
    snapshot->summary.player_active[player_index] = RuntimeMissionTrace_ReadI32(
      volatile_data
      + RUNTIME_MISSION_TRACE_PLAYER_TABLE_OFFSET
      + RUNTIME_MISSION_TRACE_PLAYER_STRIDE * player_index);
    fingerprint = RuntimeMissionTrace_HashU32(
      fingerprint,
      0xAC000000u | (unsigned int)snapshot->summary.player_active[player_index]);
  }

  for ( building_index = 0; building_index < RUNTIME_MISSION_TRACE_BUILDING_COUNT; ++building_index )
  {
    const volatile unsigned char *building;
    RuntimeMissionTraceBuilding *trace_building;
    int construction_turns_remaining;
    int garrison_units;

    building = volatile_data
             + RUNTIME_MISSION_TRACE_BUILDING_TABLE_OFFSET
             + RUNTIME_MISSION_TRACE_BUILDING_STRIDE * building_index;
    construction_turns_remaining = RuntimeMissionTrace_ReadI16(
      building + RUNTIME_MISSION_TRACE_BUILDING_CONSTRUCTION_OFFSET);
    if ( construction_turns_remaining == -1
      || building[RUNTIME_MISSION_TRACE_BUILDING_OWNER_OFFSET] != target_player_index )
      continue;

    garrison_units = RuntimeMissionTrace_CountOccupiedSlots(
      building,
      RUNTIME_MISSION_TRACE_BUILDING_GARRISON_BASE_OFFSET,
      RUNTIME_MISSION_TRACE_BUILDING_GARRISON_STRIDE,
      RUNTIME_MISSION_TRACE_BUILDING_GARRISON_COUNT);
    trace_building = &snapshot->buildings[snapshot->summary.target_building_count++];
    trace_building->index = building_index;
    trace_building->row = building[0];
    trace_building->column = building[1];
    trace_building->construction_turns_remaining = construction_turns_remaining;
    trace_building->garrison_units = garrison_units;
    snapshot->summary.target_garrison_unit_count += garrison_units;

    fingerprint = RuntimeMissionTrace_HashU32(fingerprint, 0xB1000000u | (unsigned int)building_index);
    fingerprint = RuntimeMissionTrace_HashU32(fingerprint, (unsigned int)trace_building->row);
    fingerprint = RuntimeMissionTrace_HashU32(fingerprint, (unsigned int)trace_building->column);
    fingerprint = RuntimeMissionTrace_HashU32(
      fingerprint,
      (unsigned int)construction_turns_remaining);
    fingerprint = RuntimeMissionTrace_HashU32(fingerprint, (unsigned int)garrison_units);
  }

  snapshot->summary.target_stack_count = RuntimeMissionTrace_CollectStacksForPlayer(
    volatile_data,
    target_player_index,
    snapshot->stacks,
    &snapshot->summary.target_world_unit_count,
    &fingerprint,
    0x5A000000u);

  if ( ap_player_index >= 0 )
  {
    snapshot->summary.ap_stack_count = RuntimeMissionTrace_CollectStacksForPlayer(
      volatile_data,
      ap_player_index,
      snapshot->ap_stacks,
      0,
      &fingerprint,
      0xA9000000u);
  }

  fingerprint = RuntimeMissionTrace_HashU32(
    fingerprint,
    (unsigned int)snapshot->summary.target_building_count);
  fingerprint = RuntimeMissionTrace_HashU32(
    fingerprint,
    (unsigned int)snapshot->summary.target_stack_count);
  fingerprint = RuntimeMissionTrace_HashU32(
    fingerprint,
    (unsigned int)snapshot->summary.target_garrison_unit_count);
  fingerprint = RuntimeMissionTrace_HashU32(
    fingerprint,
    (unsigned int)snapshot->summary.target_world_unit_count);
  snapshot->summary.fingerprint = fingerprint;
  return 1;
}

int RuntimeMissionTrace_CollectSummary(
  const unsigned char *data,
  int target_player_index,
  int ap_player_index,
  RuntimeMissionTraceSummary *summary)
{
  RuntimeMissionTraceSnapshot snapshot;

  if ( !summary
    || !RuntimeMissionTrace_CollectSnapshot(data, target_player_index, ap_player_index, &snapshot) )
    return 0;
  *summary = snapshot.summary;
  return 1;
}

#ifndef RUNTIME_MISSION_TRACE_DISABLE_CONSTRUCTOR
static int RuntimeMissionTrace_ParseBoundedInt(
  const char *value,
  int default_value,
  int minimum,
  int maximum)
{
  char *end;
  long parsed;

  if ( !value || !*value )
    return default_value;
  end = 0;
  parsed = strtol(value, &end, 10);
  if ( !end || *end || parsed < minimum || parsed > maximum )
    return default_value;
  return (int)parsed;
}

static int RuntimeMissionTrace_SnapshotsMatch(
  const RuntimeMissionTraceSnapshot *left,
  const RuntimeMissionTraceSnapshot *right)
{
  return left->summary.mission_index == right->summary.mission_index
      && left->summary.game_turn == right->summary.game_turn
      && left->summary.turn_owner_player_index == right->summary.turn_owner_player_index
      && left->summary.fingerprint == right->summary.fingerprint;
}

static void RuntimeMissionTrace_EmitSnapshot(const RuntimeMissionTraceSnapshot *snapshot)
{
  int building_index;
  int stack_index;
  int target_remaining;

  target_remaining = snapshot->summary.target_building_count
                   + snapshot->summary.target_stack_count;
  fprintf(
    stderr,
    "[mission-state] mission=%d turn=%u owner=%d target=%d buildings=%d stacks=%d garrison_units=%d world_units=%d target_remaining=%d\n",
    snapshot->summary.mission_index,
    snapshot->summary.game_turn,
    snapshot->summary.turn_owner_player_index,
    snapshot->summary.target_player_index,
    snapshot->summary.target_building_count,
    snapshot->summary.target_stack_count,
    snapshot->summary.target_garrison_unit_count,
    snapshot->summary.target_world_unit_count,
    target_remaining);

  fprintf(
    stderr,
    "[mission-state] players active=%d,%d,%d,%d,%d ap_player=%d ap_stacks=%d\n",
    snapshot->summary.player_active[0],
    snapshot->summary.player_active[1],
    snapshot->summary.player_active[2],
    snapshot->summary.player_active[3],
    snapshot->summary.player_active[4],
    snapshot->summary.ap_player_index,
    snapshot->summary.ap_stack_count);

  for ( building_index = 0; building_index < snapshot->summary.target_building_count; ++building_index )
  {
    const RuntimeMissionTraceBuilding *building;

    building = &snapshot->buildings[building_index];
    fprintf(
      stderr,
      "[mission-state] building index=%d owner=%d row=%d column=%d construction=%d garrison=%d\n",
      building->index,
      snapshot->summary.target_player_index,
      building->row,
      building->column,
      building->construction_turns_remaining,
      building->garrison_units);
  }

  for ( stack_index = 0; stack_index < snapshot->summary.target_stack_count; ++stack_index )
  {
    const RuntimeMissionTraceStack *stack;

    stack = &snapshot->stacks[stack_index];
    fprintf(
      stderr,
      "[mission-state] stack index=%d owner=%d row=%d column=%d units=%d min_ap=%d\n",
      stack->index,
      snapshot->summary.target_player_index,
      stack->row,
      stack->column,
      stack->units,
      stack->min_action_points);
  }

  for ( stack_index = 0; stack_index < snapshot->summary.ap_stack_count; ++stack_index )
  {
    const RuntimeMissionTraceStack *stack;

    stack = &snapshot->ap_stacks[stack_index];
    fprintf(
      stderr,
      "[mission-state] ap_stack index=%d owner=%d row=%d column=%d units=%d min_ap=%d\n",
      stack->index,
      snapshot->summary.ap_player_index,
      stack->row,
      stack->column,
      stack->units,
      stack->min_action_points);
  }
  fflush(stderr);
}

/* The recovered state stores the game-state block as a 32-bit pointer
   (`int gameData;` in the state TU) into the low-32 allocation arena; the
   block itself is heap-allocated at boot. Resolve the stored pointer each
   sample: 0 means the block does not exist yet. */
extern int gameData;

static const unsigned char *RuntimeMissionTrace_ResolveGameData(void)
{
  unsigned int stored;

  stored = (unsigned int)gameData;
  if ( !stored )
    return 0;
  return (const unsigned char *)(uintptr_t)stored;
}

static void *RuntimeMissionTrace_Thread(void *unused)
{
  RuntimeMissionTraceSnapshot first_snapshot;
  RuntimeMissionTraceSnapshot second_snapshot;
  unsigned int previous_fingerprint;
  int have_previous_fingerprint;
  int mission_index;
  int target_player_index;
  int ap_player_index;
  int interval_ms;

  (void)unused;
  mission_index = RuntimeMissionTrace_ParseBoundedInt(
    getenv("CLASH95_TRACE_MISSION_ID"),
    RUNTIME_MISSION_TRACE_DEFAULT_MISSION,
    0,
    19);
  target_player_index = RuntimeMissionTrace_ParseBoundedInt(
    getenv("CLASH95_TRACE_MISSION_TARGET_PLAYER"),
    RUNTIME_MISSION_TRACE_DEFAULT_TARGET_PLAYER,
    0,
    4);
  /* Default AP player = the human controller: player 1 in the second
     campaign (missions 10..19), player 0 otherwise (Scenario_LoadMissionByIndex
     cases 10..19 set PLAYER_HAS_HUMAN_CONTROLLER(1)). -1 disables. */
  ap_player_index = RuntimeMissionTrace_ParseBoundedInt(
    getenv("CLASH95_TRACE_MISSION_AP_PLAYER"),
    mission_index >= 10 ? 1 : 0,
    -1,
    4);
  interval_ms = RuntimeMissionTrace_ParseBoundedInt(
    getenv("CLASH95_TRACE_MISSION_INTERVAL_MS"),
    RUNTIME_MISSION_TRACE_DEFAULT_INTERVAL_MS,
    20,
    10000);
  previous_fingerprint = 0;
  have_previous_fingerprint = 0;

  fprintf(
    stderr,
    "[mission-state] sampler_start mission=%d target=%d ap_player=%d interval_ms=%d\n",
    mission_index,
    target_player_index,
    ap_player_index,
    interval_ms);
  fflush(stderr);

  for ( ; ; )
  {
    const unsigned char *data;

    data = RuntimeMissionTrace_ResolveGameData();
    if ( data
      && RuntimeMissionTrace_CollectSnapshot(data, target_player_index, ap_player_index, &first_snapshot)
      && first_snapshot.summary.mission_index == mission_index
      && RuntimeMissionTrace_CollectSnapshot(data, target_player_index, ap_player_index, &second_snapshot)
      && RuntimeMissionTrace_SnapshotsMatch(&first_snapshot, &second_snapshot) )
    {
      if ( !have_previous_fingerprint
        || previous_fingerprint != second_snapshot.summary.fingerprint )
      {
        RuntimeMissionTrace_EmitSnapshot(&second_snapshot);
        previous_fingerprint = second_snapshot.summary.fingerprint;
        have_previous_fingerprint = 1;
      }
    }
    else
    {
      have_previous_fingerprint = 0;
    }
    usleep((useconds_t)interval_ms * 1000u);
  }
  return 0;
}

static void __attribute__((constructor)) RuntimeMissionTrace_Start(void)
{
  const char *enabled;
  pthread_t thread;

  enabled = getenv("CLASH95_TRACE_MISSION_STATE");
  if ( !enabled || !*enabled || strcmp(enabled, "0") == 0 )
    return;
  if ( pthread_create(&thread, 0, RuntimeMissionTrace_Thread, 0) != 0 )
  {
    fprintf(stderr, "[mission-state] sampler_start_failed\n");
    fflush(stderr);
    return;
  }
  pthread_detach(thread);
}
#endif
