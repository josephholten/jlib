# jassert
find_package(cpptrace REQUIRED)
add_library(jassert jassert.cpp)
target_link_libraries(jassert PUBLIC jlib_include cpptrace::cpptrace)

# big int
add_library(bigint BigInt.cpp)
target_link_libraries(bigint PRIVATE jlib_flags)
target_link_libraries(bigint PUBLIC fmt::fmt jlib_include)

#add_library(jlib )
#target_link_libraries(jlib PRIVATE jlib_base cpptrace::cpptrace)