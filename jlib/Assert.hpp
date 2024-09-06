#ifndef ASSERT_HPP
#include "fmt/core.h"
#include <cstdlib>
#include <string>
#include "cpptrace/cpptrace.hpp"
#include <stacktrace>

#ifndef NDEBUG
#define JDEBUG(code) code
#else
#define JDEBUG(code)
#endif

#define JASSERT(condition) {\
const auto jassert_raw_trace = cpptrace::generate_raw_trace(); \
const auto jassert_c = condition; \
if (!jassert_c) { \
    jassert_raw_trace.resolve().print(); \
    fmt::println("assertion failed: expected the condition to be true");\
    fmt::println("    {}", #condition);\
    exit(1); \
} \
}

#define JASSERT_EQ(A, B) {\
const auto jassert_eq_raw_trace = cpptrace::generate_raw_trace(); \
const auto jassert_eq_A = A; const auto jassert_eq_B = B; \
if (jassert_eq_A != j_assert_eq_B) {\
    jassert_eq_raw_trace.resolve().print(); \
    fmt::println("assertion failed: expected equality of"); \
    fmt::println("    (LHS) {} = {}", #A, jassert_eq_A); \
    fmt::println("    (RHS) {} = {}", #B, jassert_eq_B); \
    exit(1); \
} \
}

#define JASSERT_LT(A, B, message) {\
const auto jassert_lt_raw_trace = cpptrace::generate_raw_trace(); \
auto jassert_eq_A = A; auto jassert_eq_B = B; \
if (jassert_eq_A >= j_assert_eq_B) {\
    jassert_lt_raw_trace.resolve().print(); \
    fmt::println("assertion failed: expected equality of"); \
    fmt::println("    (LHS) {} = {}", #A, jassert_eq_A); \
    fmt::println("    (RHS) {} = {}", #B, jassert_eq_B); \
    exit(1); \
} \
}

#endif