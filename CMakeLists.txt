cmake_minimum_required(VERSION 3.28)

project(clash95_recovered LANGUAGES C)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
find_package(X11 REQUIRED)

add_library(clash95_recovered STATIC
  clash95.c
  platform_sdl_runtime.c
  compat/decomp_runtime_stubs.c
)

add_library(clash95_bootstrap_objects OBJECT
  clash95.c
  platform_sdl_runtime.c
  compat/decomp_runtime_stubs.c
)

add_executable(clash95_bootstrap
  bootstrap_main.c
  $<TARGET_OBJECTS:clash95_bootstrap_objects>
)

target_include_directories(clash95_recovered
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
)

target_include_directories(clash95_bootstrap_objects
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
)

target_include_directories(clash95_bootstrap
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(clash95_recovered PRIVATE -std=gnu89 -w)
  target_compile_options(clash95_bootstrap_objects PRIVATE -std=gnu89 -w -ffunction-sections -fdata-sections -fno-pie)
  target_compile_options(clash95_bootstrap PRIVATE -std=gnu89 -w -ffunction-sections -fdata-sections -fno-pie)
  target_link_options(clash95_bootstrap PRIVATE -Wl,--gc-sections -no-pie)
endif()

target_link_libraries(clash95_recovered PUBLIC PkgConfig::SDL2 X11::X11)
target_link_libraries(clash95_bootstrap PRIVATE PkgConfig::SDL2 X11::X11 m)

set_target_properties(clash95_recovered PROPERTIES
  OUTPUT_NAME clash95_recovered
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(clash95_bootstrap PROPERTIES
  OUTPUT_NAME clash95_bootstrap
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_test(
  NAME clash95_full_route_smoke
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_full_route_smoke.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_full_route_smoke PROPERTIES TIMEOUT 10)

add_test(
  NAME clash95_r_command_shutdown_smoke
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_r_command_shutdown.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_r_command_shutdown_smoke PROPERTIES TIMEOUT 10)

add_test(
  NAME clash95_main_menu_exit_probe
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_main_menu_exit_probe.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_main_menu_exit_probe PROPERTIES
  TIMEOUT 45
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "real_input;main_menu"
)

add_test(
  NAME clash95_direct_a_route_smoke
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_direct_a_route_smoke.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_direct_a_route_smoke PROPERTIES TIMEOUT 10)

add_test(
  NAME clash95_direct_a0_route_smoke
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_direct_a0_route_smoke.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_direct_a0_route_smoke PROPERTIES TIMEOUT 10)

add_test(
  NAME clash95_first_mission_real_input_move_smoke
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_first_mission_real_input_move_smoke.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_first_mission_real_input_move_smoke PROPERTIES
  TIMEOUT 95
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "manual;real_input;first_mission"
)

add_test(
  NAME clash95_first_mission_playability_probe
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_first_mission_playability_probe.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_first_mission_playability_probe PROPERTIES
  TIMEOUT 95
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "manual;real_input;first_mission;first_mission_playability"
)

add_test(
  NAME clash95_first_mission_attack_probe
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_first_mission_attack_probe.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_first_mission_attack_probe PROPERTIES
  TIMEOUT 115
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "manual;real_input;first_mission;first_mission_attack"
)

add_test(
  NAME clash95_castle_economy_regression
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_castle_economy_probe.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_castle_economy_regression PROPERTIES
  TIMEOUT 110
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  ENVIRONMENT "CLASH95_ENABLE_CASTLE_ECONOMY_REGRESSION=1"
  LABELS "manual;real_input;first_mission;castle;economy"
)

add_test(NAME clash95_first_mission_turn_probe
  COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_first_mission_turn_probe.sh
  $<TARGET_FILE:clash95_bootstrap>)
set_tests_properties(clash95_first_mission_turn_probe PROPERTIES
  TIMEOUT 105
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "manual;real_input;first_mission;first_mission_turn"
)

add_test(
  NAME clash95_save_dat_format
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_save_dat_format.sh
)
set_tests_properties(clash95_save_dat_format PROPERTIES
  TIMEOUT 20
  SKIP_RETURN_CODE 77
  LABELS "save;format"
)

function(add_campaign_route_regression_test mission_id timeout_seconds)
  add_test(
    NAME clash95_campaign_route_${mission_id}_regression
    COMMAND bash
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_campaign_route_regression.sh
      $<TARGET_FILE:clash95_bootstrap>
      ${mission_id}
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/first_campaign_arc_routes/mission_${mission_id}.env
  )
  set_tests_properties(clash95_campaign_route_${mission_id}_regression PROPERTIES
    TIMEOUT ${timeout_seconds}
    SKIP_RETURN_CODE 77
    RUN_SERIAL TRUE
    LABELS "manual;real_input;campaign_route;mission_${mission_id}"
  )
endfunction()

add_campaign_route_regression_test(01 360)
add_campaign_route_regression_test(02 900)
add_campaign_route_regression_test(03 900)
add_campaign_route_regression_test(04 360)
