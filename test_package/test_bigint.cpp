#include <jlib/BigInt.hpp>
#include <fmt/core.h>

int main() {
    static constexpr size_t N = 1000;

    jlib::BigInt Prev = 1;
    jlib::BigInt F = 1;

    size_t i = 2;
    for(; F.digits().size() < N; i++) {
        jlib::BigInt Next = F + Prev;
        Prev = F;
        F = Next;
    }

    fmt::println("{}", i);
}