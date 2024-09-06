#include <benchmark/benchmark.h>
#include <jlib/util.hpp>

volatile size_t sum = 0;

static void BM_fast_pow(benchmark::State& state) {
    for (auto _ : state)
        sum += fast_pow(state.range(0), state.range(1));
}

static void BM_linear_pow(benchmark::State& state) {
    for (auto _ : state)
        sum += linear_pow(state.range(0), state.range(1));
}

static void BM_recursive_pow(benchmark::State& state) {
    for (auto _ : state)
        sum += recursive_pow(state.range(0), state.range(1));
}

static void BM_std_pow(benchmark::State& state) {
    for (auto _ : state)
        sum += std::pow(state.range(0), state.range(1));
}

static void BM_square(benchmark::State& state) {
    for (auto _ : state)
        sum += state.range(0) * state.range(0);
}

static void BM_cube(benchmark::State& state) {
    volatile size_t sum = 0;
    for (auto _ : state)
        sum += state.range(0) * state.range(0) * state.range(0);
}

BENCHMARK(BM_square)->Range(1, 64);
BENCHMARK(BM_cube)->Range(1, 64);

BENCHMARK(BM_fast_pow)->ArgsProduct({
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
});

BENCHMARK(BM_fast_pow)->ArgsProduct({
    {2, 3},
    {0, 1, 2, 3, 4, 5, 6, 8, 13, 16, 25, 32, 64}
});

BENCHMARK(BM_linear_pow)->ArgsProduct({
    {2, 3},
    {0, 1, 2, 3, 4, 5, 6, 8, 13, 16, 25, 32, 64}
});

BENCHMARK(BM_recursive_pow)->ArgsProduct({
    {2, 3},
    {0, 1, 2, 3, 4, 5, 6, 8, 13, 16, 25, 32, 64}
});