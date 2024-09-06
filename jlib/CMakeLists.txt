# jassert
find_package(cpptrace REQUIRED)
add_library(jassert jassert.cpp)
target_link_libraries(jassert PUBLIC cpptrace::cpptrace)

# bigint
add_library(bigint BigInt.cpp)
target_link_libraries(bigint PRIVATE jlib_flags PUBLIC fmt::fmt)
