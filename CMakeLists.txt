cmake_minimum_required(VERSION 3.28)

project(clash95_recovered LANGUAGES C)

add_library(clash95_recovered STATIC
  clash95.c
  platform_sdl_runtime.c
  compat/decomp_runtime_stubs.c
)

target_include_directories(clash95_recovered
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/compat
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(clash95_recovered PRIVATE -std=gnu89 -w)
endif()

set_target_properties(clash95_recovered PROPERTIES
  OUTPUT_NAME clash95_recovered
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
