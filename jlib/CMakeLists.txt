# jassert
find_package(cpptrace REQUIRED)
add_library(jassert jassert.cpp) # jassert.cpp is just dummy code to force the following link
target_link_libraries(jassert cpptrace::cpptrace)

add_library(bigint BigInt.cpp)

add_library(jlib )
target_link_libraries(jlib PRIVATE jlib_base cpptrace::cpptrace)