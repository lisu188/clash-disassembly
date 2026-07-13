#ifndef CLASH95_RUNTIME_MISSION_TRACE_H
#define CLASH95_RUNTIME_MISSION_TRACE_H

typedef struct RuntimeMissionTraceSummary
{
  int mission_index;
  unsigned int game_turn;
  int turn_owner_player_index;
  int target_player_index;
  int target_building_count;
  int target_stack_count;
  int target_garrison_unit_count;
  int target_world_unit_count;
  unsigned int fingerprint;
} RuntimeMissionTraceSummary;

int RuntimeMissionTrace_CollectSummary(
  const unsigned char *data,
  int target_player_index,
  RuntimeMissionTraceSummary *summary);

#endif
