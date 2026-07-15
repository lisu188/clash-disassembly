cmake_minimum_required(VERSION 3.28)

project(clash95_recovered LANGUAGES C)

enable_testing()

find_package(PkgConfig REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

set(CLASH95_PRIVATE_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/platform
  ${CMAKE_CURRENT_SOURCE_DIR}/src/compatibility
  ${CMAKE_CURRENT_SOURCE_DIR}/src/instrumentation
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}
)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/sources.cmake)

# The recovered implementation is compiled as subsystem object libraries. The
# checked-in split source list is the single source of truth for this graph.
set(CLASH95_SPLIT_SUBSYSTEMS
  core
  render
  world
  units
  buildings
  battle
  persistence
  strategic
  clips
  media
  runtime
  state
)

set(CLASH95_SPLIT_OBJECT_TARGETS)
set(CLASH95_SPLIT_OBJECTS)
set(CLASH95_SPLIT_ALL_SOURCES)
foreach(subsystem IN LISTS CLASH95_SPLIT_SUBSYSTEMS)
  string(TOUPPER "${subsystem}" subsystem_upper)
  set(source_variable "CLASH95_SPLIT_${subsystem_upper}_SOURCES")
  set(object_target "clash95_recovered_${subsystem}_objects")

  if(NOT DEFINED ${source_variable})
    message(FATAL_ERROR "Generated split source group ${source_variable} is undefined")
  endif()
  if("${${source_variable}}" STREQUAL "")
    message(FATAL_ERROR "Generated split source group ${source_variable} is empty")
  endif()

  add_library(${object_target} OBJECT ${${source_variable}})
  list(APPEND CLASH95_SPLIT_OBJECT_TARGETS ${object_target})
  list(APPEND CLASH95_SPLIT_OBJECTS $<TARGET_OBJECTS:${object_target}>)
  list(APPEND CLASH95_SPLIT_ALL_SOURCES ${${source_variable}})
endforeach()

add_library(clash95_platform_objects OBJECT
  src/platform/platform_sdl_runtime.c
)

add_library(clash95_instrumentation_objects OBJECT
  src/instrumentation/runtime_mission_trace.c
)

add_library(clash95_compatibility_objects OBJECT
  src/compatibility/decomp_runtime_stubs.c
)

set(CLASH95_SUPPORT_OBJECT_TARGETS
  clash95_platform_objects
  clash95_instrumentation_objects
  clash95_compatibility_objects
)

foreach(target IN LISTS CLASH95_SPLIT_OBJECT_TARGETS)
  target_include_directories(${target} PRIVATE ${CLASH95_PRIVATE_INCLUDE_DIRS})
  target_link_libraries(${target} PRIVATE PkgConfig::SDL2 X11::X11 Threads::Threads)
  set_target_properties(${target} PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
  )
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE
      -Wall
      -Wextra
      -Wformat=2
      -Wstrict-prototypes
      -Wmissing-prototypes
      -Werror=implicit-function-declaration
      -Werror=implicit-int
      -Werror=return-type
      -ffunction-sections
      -fdata-sections
      -fno-pie
    )
  endif()
  if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${target} PRIVATE -Wno-error=int-conversion)
  endif()
endforeach()

foreach(target IN LISTS CLASH95_SUPPORT_OBJECT_TARGETS)
  target_include_directories(${target} PRIVATE ${CLASH95_PRIVATE_INCLUDE_DIRS})
  target_link_libraries(${target} PRIVATE PkgConfig::SDL2 X11::X11 Threads::Threads)
  set_target_properties(${target} PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
  )
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Werror
      -ffunction-sections
      -fdata-sections
      -fno-pie
    )
  endif()
endforeach()

add_library(clash95_recovered STATIC
  ${CLASH95_SPLIT_OBJECTS}
  $<TARGET_OBJECTS:clash95_platform_objects>
  $<TARGET_OBJECTS:clash95_instrumentation_objects>
  $<TARGET_OBJECTS:clash95_compatibility_objects>
)

add_executable(clash95_bootstrap
  src/bootstrap/bootstrap_main.c
  ${CLASH95_SPLIT_OBJECTS}
  $<TARGET_OBJECTS:clash95_platform_objects>
  $<TARGET_OBJECTS:clash95_instrumentation_objects>
  $<TARGET_OBJECTS:clash95_compatibility_objects>
)

target_include_directories(clash95_bootstrap PRIVATE ${CLASH95_PRIVATE_INCLUDE_DIRS})
set_target_properties(clash95_bootstrap PROPERTIES
  C_STANDARD 17
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS YES
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(clash95_bootstrap PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -ffunction-sections
    -fdata-sections
    -fno-pie
  )
  target_link_options(clash95_bootstrap PRIVATE -Wl,--gc-sections -no-pie)
endif()

target_link_libraries(clash95_recovered PUBLIC PkgConfig::SDL2 X11::X11 Threads::Threads)
target_link_libraries(clash95_bootstrap PRIVATE PkgConfig::SDL2 X11::X11 Threads::Threads m)

set_target_properties(clash95_recovered PROPERTIES
  OUTPUT_NAME clash95_recovered
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(clash95_bootstrap PROPERTIES
  OUTPUT_NAME clash95_bootstrap
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_target(clash95_split_audit
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/audit_split_sources.py
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/migrate_pure_coverage_metadata.py --check
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_save_format_contract.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Auditing recovered split identities, tokens, ordering, and frozen coverage metadata"
  VERBATIM
)

add_test(
  NAME clash95_split_source_audit
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/audit_split_sources.py
)
set_tests_properties(clash95_split_source_audit PROPERTIES
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  TIMEOUT 60
  LABELS "asset_free;split;metadata"
)

add_test(
  NAME clash95_pure_metadata_audit
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/migrate_pure_coverage_metadata.py --check
)
set_tests_properties(clash95_pure_metadata_audit PROPERTIES
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  TIMEOUT 30
  LABELS "asset_free;split;metadata;unit"
)

add_test(
  NAME clash95_save_format_contract
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/check_save_format_contract.py
)
set_tests_properties(clash95_save_format_contract PROPERTIES
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  TIMEOUT 30
  LABELS "asset_free;save;format;metadata"
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

add_test(
  NAME clash95_soak_probe
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_clash95_soak_probe.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_soak_probe PROPERTIES
  TIMEOUT 3900
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "manual;real_input;soak"
)

add_test(
  NAME clash95_multiplayer_map_probe
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/run_multiplayer_map_probe.sh
    $<TARGET_FILE:clash95_bootstrap>
)
set_tests_properties(clash95_multiplayer_map_probe PROPERTIES
  TIMEOUT 900
  SKIP_RETURN_CODE 77
  RUN_SERIAL TRUE
  LABELS "manual;real_input;multiplayer;map"
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
# Leave CTest headroom above mission_04.env's 3600-second route timeout.
add_campaign_route_regression_test(04 3900)

add_executable(runtime_mission_trace_tests
  tests/runtime_mission_trace_test.c
  src/instrumentation/runtime_mission_trace.c
)
target_include_directories(runtime_mission_trace_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/instrumentation
)
target_compile_definitions(runtime_mission_trace_tests PRIVATE
  RUNTIME_MISSION_TRACE_DISABLE_CONSTRUCTOR=1
)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(runtime_mission_trace_tests PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
endif()
target_link_libraries(runtime_mission_trace_tests PRIVATE Threads::Threads)
set_target_properties(runtime_mission_trace_tests PROPERTIES
  C_STANDARD 17
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS YES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
add_test(
  NAME runtime_mission_trace_tests
  COMMAND $<TARGET_FILE:runtime_mission_trace_tests>
)
set_tests_properties(runtime_mission_trace_tests PROPERTIES
  TIMEOUT 10
  LABELS "unit;mission_state"
)

# ---------------------------------------------------------------------------
# Unit-test / coverage target (opt-in: -DCLASH95_COVERAGE=ON). Recovered
# sources, compatibility support, the runner, and every test case are compiled
# independently. Coverage identities come from data/recovered_sources.json.
# ---------------------------------------------------------------------------
option(CLASH95_COVERAGE "Build instrumented clash95 unit tests" OFF)

if(CLASH95_COVERAGE)
  file(GLOB CLASH95_UNIT_CASE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/cases/test_*.c)

  add_library(clash95_recovered_coverage_objects OBJECT
    ${CLASH95_SPLIT_ALL_SOURCES})
  target_include_directories(clash95_recovered_coverage_objects PRIVATE
    ${CLASH95_PRIVATE_INCLUDE_DIRS})
  target_compile_definitions(clash95_recovered_coverage_objects PRIVATE
    CLASH95_TESTING=1)
  set_target_properties(clash95_recovered_coverage_objects PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(clash95_recovered_coverage_objects PRIVATE
      -Wall -Wextra -Wformat=2 -Wstrict-prototypes -Wmissing-prototypes
      -Werror=implicit-function-declaration -Werror=implicit-int
      -Werror=return-type -g -O0 --coverage -fprofile-abs-path
      -ffunction-sections -fdata-sections -fno-pie)
  endif()

  add_executable(clash95_unit_tests
    tests/unit/test_runner.c
    tests/unit/test_compat_stubs.c
    ${CLASH95_UNIT_CASE_SOURCES}
    src/platform/platform_sdl_runtime.c
    src/instrumentation/runtime_mission_trace.c
    src/compatibility/decomp_runtime_stubs.c
    $<TARGET_OBJECTS:clash95_recovered_coverage_objects>
  )
  target_include_directories(clash95_unit_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compatibility
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instrumentation
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit
  )
  # Test code is pedantic-clean; the generated recovered declarations remain a
  # system include because they intentionally retain GNU ABI types and
  # quarantined zero-length legacy arrays.
  target_include_directories(clash95_unit_tests SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)
  set_source_files_properties(${CLASH95_UNIT_CASE_SOURCES} PROPERTIES
    COMPILE_OPTIONS
      "-include;${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/case_prelude.h")
  target_compile_definitions(clash95_unit_tests PRIVATE
    CLASH95_TESTING=1
    RUNTIME_MISSION_TRACE_DISABLE_CONSTRUCTOR=1)
  set_target_properties(clash95_unit_tests PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS YES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  target_compile_options(clash95_unit_tests PRIVATE
    -Wall -Wextra -Wpedantic -Werror -g -O0 --coverage -fprofile-abs-path
    -ffunction-sections -fdata-sections -fno-pie)
  target_link_options(clash95_unit_tests PRIVATE --coverage -Wl,--gc-sections -no-pie)
  target_link_libraries(clash95_unit_tests PRIVATE PkgConfig::SDL2 X11::X11 Threads::Threads m)
  add_test(NAME clash95_unit_tests
    COMMAND bash
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/unit/run_split_coverage.sh
      $<TARGET_FILE:clash95_unit_tests>
      ${CMAKE_BINARY_DIR})
  set_tests_properties(clash95_unit_tests PROPERTIES
    TIMEOUT 240 LABELS "unit")
endif()
