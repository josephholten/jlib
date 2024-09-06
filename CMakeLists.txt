cmake_minimum_required(VERSION 3.23)
project(jlib CXX)

set(JLIB_DEFAULT_BUILD_TYPE Release)

# build type
if(NOT CMAKE_BUILD_TYPE)
    message("project euler: default CMAKE_BUILD_TYPE=${JLIB_DEFAULT_BUILD_TYPE}")
    set(CMAKE_BUILD_TYPE ${JLIB_DEFAULT_BUILD_TYPE} CACHE STRING "Choose the type of build.")
endif()

# flags
set(JLIB_WARNING_FLAGS -Wall -Wpedantic -Wno-unused-function)
set(JLIB_GENERAL_FLAGS ${WARNING_FLAGS} -g)
set(JLIB_SANITIZE -fsanitize=address)
set(JLIB_PERFORMANCE_FLAGS -Ofast -march=native -flto -fomit-frame-pointer)

set(JLIB_DEBUG_FLAGS ${GENERAL_FLAGS} ${SANITIZE} -O0)
set(JLIB_RELEASE_FLAGS ${GENERAL_FLAGS} ${WARNING_FLAGS} ${PERFORMANCE_FLAGS})

# basic packages
find_package(fmt REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

# dummy interface library (no sources) to hide flag selection
add_library(jlib_flags INTERFACE)
target_compile_options(jlib_flags INTERFACE
    $<$<CONFIG:Debug>:${DEBUG_FLAGS}>
    $<$<CONFIG:Release>:${RELEASE_FLAGS}>
)
target_link_options(jlib_flags INTERFACE
    $<$<CONFIG:Debug>:${SANITIZE}>
)

# submodules
add_subdirectory(jlib)
add_subdirectory(bench)

# unit tests
find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

set(tests jlib/BigInt.test.cpp jlib/util.test.cpp)
foreach(testf ${tests})
  cmake_path(GET testf STEM LAST_ONLY test)
  add_executable(${test} ${testf})
  target_link_libraries(${test} PRIVATE gtest::gtest fmt::fmt)
  target_compile_options(${test} PRIVATE ${DEBUG_FLAGS})
  target_link_options(${test} PRIVATE ${SANITIZE})
  gtest_discover_tests(${test})
endforeach(testf ${testfiles})

target_link_libraries(BigInt.test PRIVATE bigint)