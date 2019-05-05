cmake_minimum_required(VERSION 3.13)

project(pixel-change)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wendif-labels -W -Werror -Wextra -Wpedantic -Wunused-parameter")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(node_modules/node-addon-api)
include_directories(node_modules/node-addon-api/src)
include_directories(node_modules/node-addon-api/external-napi)

#file(GLOB SOURCES "src/*.cc")

# use pattern matching to include files
#file(GLOB SOURCES "src/*.cc" "src/*.c")

# use specific list of files
set(SOURCES src/pixel_change.cc src/ccl.cc src/engine.cc src/object.cc src/results.cc src/worker.cc)

add_executable(pixel-change ${SOURCES})