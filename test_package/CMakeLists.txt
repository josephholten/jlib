cmake_minimum_required(VERSION 3.23)
project(test_package CXX)

# Include Conan build helper
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(test_bigint test_bigint.cpp)
target_link_libraries(test_bigint ${CONAN_LIBS})