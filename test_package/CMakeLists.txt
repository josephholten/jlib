cmake_minimum_required(VERSION 3.23)
project(test_package CXX)

find_package(jlib CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_executable(test_bigint test_bigint.cpp)
target_link_libraries(test_bigint jlib::bigint fmt::fmt)