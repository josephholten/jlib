cmake_minimum_required(VERSION 3.23)
project(test_package CXX)

find_package(jlib CONFIG REQUIRED)

add_executable(test_bigint test_bigint.cpp)
target_link_libraries(test_bigint bigint)