# jassert
find_package(cpptrace REQUIRED)
add_library(jassert jassert.hpp jassert.cpp)
target_link_libraries(jassert PUBLIC jlib_include cpptrace::cpptrace)
install(TARGETS jassert EXPORT jassert DESTINATION "${LIBRARY_DEST}")
install(FILES jassert.hpp EXPORT jassert DESTINATION "${INCLUDE_DEST}")
install(EXPORT jassert DESTINATION "${INCLUDE_DEST}")

# bigint
add_library(bigint BigInt.hpp BigInt.cpp)
target_link_libraries(bigint PRIVATE jlib_flags PUBLIC jlib_include fmt::fmt)
install(TARGETS bigint EXPORT bigint DESTINATION "${LIBRARY_DEST}")
install(FILES BigInt.hpp EXPORT bigint DESTINATION "${INCLUDE_DEST}")
install(EXPORT bigint DESTINATION "${INCLUDE_DEST}")