set pagination off
set confirm off
set breakpoint pending on
set logging file clash95-first-mission-turn-gdb.log
set logging overwrite on
set logging enabled on

break UI_CheckEndTurnHotkey
commands
  silent
  printf "[gdb] UI_CheckEndTurnHotkey pc=%p\n", $pc
  continue
end

break Game_AdvanceToNextPlayerTurn
commands
  silent
  printf "[gdb] Game_AdvanceToNextPlayerTurn pc=%p\n", $pc
  continue
end

break UI_LoadTurnBannerGfx
commands
  silent
  printf "[gdb] UI_LoadTurnBannerGfx pc=%p\n", $pc
  continue
end
