#include <string>
#include <sstream>
#include "BigInt.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(BigInt, basic) {
    for (size_t i = 0; i < 10; i++) {
        std::string s = std::to_string(i);
        BigInt I = BigInt::parse(s);
        EXPECT_EQ(s, I.to_string());
    }
}

TEST(BigInt, parse_very_long) {
    constexpr size_t N = 2000;
    constexpr size_t K = 20;
    std::random_device rng;
    std::default_random_engine engine{rng()};
    std::uniform_int_distribution<size_t> length(1, N);
    std::uniform_int_distribution<size_t> digit(0, 9);
    std::uniform_int_distribution<size_t> first_digit(1, 9); // first digit can't be zero

    for (size_t k1 = 0; k1 < K; k1++) {
        size_t l = length(engine);
        for (size_t k2 = 0; k2 < K; k2++) {
            std::stringstream ss;
            ss.put('0' + first_digit(engine));
            for (size_t i = 1; i < l; i++)
                ss.put('0' + digit(engine));

            EXPECT_EQ(ss.str(), BigInt::parse(ss).to_string());
        }
    }
}

TEST(BigInt, addition) {
    constexpr size_t N = 2000;
    constexpr size_t K = 20;
    std::random_device rng;
    std::default_random_engine engine{rng()};
    std::uniform_int_distribution<size_t> length(1, N);

    for (size_t k1 = 0; k1 < K; k1++) {
        size_t l = length(engine);
        for (size_t k2 = 0; k2 < K; k2++) {
            BigInt zero;
            BigInt random = BigInt::random(l);
            EXPECT_EQ(random+zero, random);
        }
    }
}

TEST(BigInt, literals) {
    BigInt zero;
    EXPECT_EQ(zero, 0_BigInt);
}
