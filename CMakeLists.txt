cmake_minimum_required(VERSION 3.28)

project(clash95_recovered LANGUAGES C CXX)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

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

add_library(clash95_cpp_core STATIC
  src_cpp/dlx_sprite_set.cpp
  src_cpp/cavi_decompressor.cpp
  src_cpp/csync_object.cpp
)

add_executable(clash95_cpp_regen
  bootstrap_main.c
  src_cpp/startup/cpp_regen_link_anchor.cpp
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

target_include_directories(clash95_cpp_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
)

target_include_directories(clash95_cpp_regen
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(clash95_cpp_regen
  PRIVATE
    clash95_cpp_core
)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(clash95_recovered PRIVATE -std=gnu89 -w)
  target_compile_options(clash95_bootstrap_objects PRIVATE -std=gnu89 -w -ffunction-sections -fdata-sections -fno-pie)
  target_compile_options(clash95_bootstrap PRIVATE -std=gnu89 -w -ffunction-sections -fdata-sections -fno-pie)
  target_link_options(clash95_bootstrap PRIVATE -Wl,--gc-sections -no-pie)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(clash95_cpp_core PRIVATE -std=c++17 -Wall -Wextra -pedantic)
  target_compile_options(clash95_cpp_regen PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-std=gnu89;-w;-ffunction-sections;-fdata-sections;-fno-pie>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
  )
  target_link_options(clash95_cpp_regen PRIVATE -Wl,--gc-sections -no-pie)
endif()

target_link_libraries(clash95_recovered PUBLIC PkgConfig::SDL2)
target_link_libraries(clash95_bootstrap PRIVATE PkgConfig::SDL2 m)
target_link_libraries(clash95_cpp_regen PRIVATE PkgConfig::SDL2 m)

set_target_properties(clash95_recovered PROPERTIES
  OUTPUT_NAME clash95_recovered
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(clash95_bootstrap PROPERTIES
  OUTPUT_NAME clash95_bootstrap
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
set_target_properties(clash95_cpp_core PROPERTIES
  OUTPUT_NAME clash95_cpp_core
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(clash95_cpp_regen PROPERTIES
  OUTPUT_NAME clash95_cpp_regen
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
  NAME clash95_cpp_regen_direct_a_route_smoke
  COMMAND bash
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/verify_direct_a_route_smoke.sh
    $<TARGET_FILE:clash95_cpp_regen>
)
set_tests_properties(clash95_cpp_regen_direct_a_route_smoke PROPERTIES TIMEOUT 10)
