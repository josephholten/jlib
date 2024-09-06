#include <string>
#include <sstream>
#include "util.hpp"
#include <gtest/gtest.h>
#include <random>

TEST(fast_pow, unit) {
    for (size_t k = 0; k < 100; k++)
        EXPECT_EQ(fast_pow(1, k), 1);
}

TEST(fast_pow, human) {
    EXPECT_EQ(fast_pow(2, 2), 4);
    EXPECT_EQ(fast_pow(2, 3), 8);
    EXPECT_EQ(fast_pow(2, 5), 32);
    EXPECT_EQ(fast_pow(2, 10), 1024);
    EXPECT_EQ(fast_pow(10, 4), 10000);
    EXPECT_EQ(fast_pow(10, 5), 100000);
}

TEST(fast_pow, large) {
    for (size_t a = 0; a < 10; a++) {
        for (size_t b = 0; b < 10; b++) {
            EXPECT_EQ(fast_pow(a, b), (size_t)std::pow(a, b));
        }
    }
}