# jassert
find_package(cpptrace REQUIRED)
add_library(jassert jassert.hpp jassert.cpp)
target_link_libraries(jassert PUBLIC jlib_include cpptrace::cpptrace)
install(
    TARGETS jassert
    EXPORT jlib_targets
    LIBRARY DESTINATION "${LIBRARY_DEST}"
    ARCHIVE DESTINATION "${LIBRARY_DEST}"
    INCLUDES DESTINATION "${INCLUDE_DEST}"
)
install(FILES jassert.hpp DESTINATION "${INCLUDE_DEST}")

# bigint
add_library(bigint bigint.hpp bigint.cpp)
target_link_libraries(bigint PRIVATE jlib_flags PUBLIC jlib_include fmt::fmt)
install(
    TARGETS bigint
    EXPORT jlib_targets
    LIBRARY DESTINATION "${LIBRARY_DEST}"
    ARCHIVE DESTINATION "${LIBRARY_DEST}"
    INCLUDES DESTINATION "${INCLUDE_DEST}"
)
install(FILES bigint.hpp DESTINATION "${INCLUDE_DEST}")
