#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cassert>
#include <istream>
#include <algorithm>
#include <random>
#include <sstream>

#include "fmt/core.h"

// TODO:
//  - make arbitrary base and storage type! (compile time or runtime?)
//  - make big endian / little endian compile time flag?
//  - implement long division by big endian
//  - implemnet bigfloat

namespace jlib {

// little endian
class BigInt {
public:
    using u128 = __uint128_t;
    using u64 = uint64_t;
    using u32 = uint32_t;

    // constructor
    BigInt(u64 x = 0) : m_data{x} {};

    // factory methods
    static BigInt random(u64 length);
    static BigInt parse(std::istream& in);
    static BigInt parse(const std::string& s);

    // getters
    std::vector<uint8_t> digits(uint8_t base = 10) const;
    std::string to_string() const;
    size_t hash() const;

    // operations and operators
    // assignment

    BigInt& operator=(const BigInt& other);
    BigInt& operator+=(u64 a);
    BigInt& operator*=(u64 a);
    BigInt& operator+=(BigInt a);
    BigInt& operator<<=(size_t shift);
    BigInt& operator>>=(size_t shift);

    // arithmetic operations

    u64 divide(u64 a);
    BigInt& operator++();

    BigInt operator+(BigInt a) const;
    BigInt operator<<(size_t shift) const;
    BigInt operator>>(size_t shift) const;

    // comparision

    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(BigInt a) const;
    bool operator<=(BigInt a) const;
    bool operator>(BigInt a) const;
    bool operator>=(BigInt a) const;
    bool operator<(size_t a) const;
    bool operator<=(size_t a) const;
    bool operator>(size_t a) const;
    bool operator>=(size_t a) const;

private:
    std::vector<u64> m_data {0};
};

}

#endif