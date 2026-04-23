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
