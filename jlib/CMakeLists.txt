# jassert
find_package(cpptrace REQUIRED)
add_library(jassert jassert.cpp)
target_link_libraries(jassert PUBLIC jlib_include cpptrace::cpptrace)
install(TARGETS jassert DESTINATION lib)
install(FILES jassert.hpp DESTINATION include)

# bigint
add_library(bigint BigInt.cpp)
target_link_libraries(bigint PUBLIC fmt::fmt jlib_include)
target_link_libraries(bigint PRIVATE jlib_flags)
install(TARGETS bigint DESTINATION lib)
install(FILES BigInt.hpp DESTINATION include)
