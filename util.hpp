#ifndef UTIL_PROJECT_EULER_HPP
#define UTIL_PROJECT_EULER_HPP

#include <cstdint>
#include <vector>
#include <cmath>
#include "fmt/core.h"
#include <algorithm>

template<typename T>
T factorial(T n) {
    T res = 1;
    for (T i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

// computes x^m
template<typename T>
static T fast_pow(T x, size_t m) {
    // special cases
    if (m == 0)
        return 1;
    if (x == 0)
        return 0;
    if (m == 1)
        return x;
    if (x == 1)
        return 1;

    if (m < 10) {
        size_t result = x;
        for (size_t k = 1; k < m; k++)
            result *= x;
        return result;
    }

    if (m % 2 == 0) {
        return fast_pow(x, m/2) * fast_pow(x, m/2);
    } else {
        return fast_pow(x, m-1) * x;
    }
}

template<typename T>
static T linear_pow(T x, size_t m) {
    // special cases
    if (m == 0)
        return 1;
    if (x == 0)
        return 0;
    if (m == 1)
        return x;
    if (x == 1)
        return 1;

    size_t result = x;
    for (size_t k = 1; k < m; k++)
        result *= x;
    return result;
}

template<typename T>
static T recursive_pow(T x, size_t m) {
    // special cases
    if (m == 0)
        return 1;
    if (x == 0)
        return 0;
    if (m == 1)
        return x;
    if (x == 1)
        return 1;

    if (m % 2 == 0) {
        return fast_pow(x, m/2) * fast_pow(x, m/2);
    } else {
        return fast_pow(x, m-1) * x;
    }
}



template<typename T>
static void prime_sieve(std::vector<T>& prime) {
    std::fill(prime.begin(), prime.end(), 1);

    prime[0] = 0;
    prime[1] = 0;

    for (size_t i = 2; i <= std::ceil(std::sqrt(prime.size())); i++) {
        if (prime[i]) {
            for (size_t j = 2*i; j < prime.size(); j += i) {
                prime[j] = 0;
            }
        }
    }
}

void divisors(size_t n, const std::vector<size_t>& primes) {
    size_t divisors = 1;
    for (size_t p : primes) {
        if (n % p == 0) {
            size_t power = 1;
            size_t remainder = n / p;
            while (remainder % p == 0) {
                remainder /= p;
                power += 1;
            }
            divisors *= power + 1;
        }
        if (p > n)
            break;
    }
}

uint32_t sum_of_divisors(uint32_t n) {
    uint32_t sum = 1;
    for (uint32_t i = 2; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

template<typename T>
bool permute(T* begin, T* end) {
    if (end - begin == 0)
        return false;

    // if we have only two items (a, b)
    if (end - begin == 1) {
        // if they are in final permutation
        if (*begin > *end) {
            // can't permute
            return false;
        }

        // else we permute
        std::swap(*begin, *end);
        return true;
    }

    // if we have more than two, we try to permute suffix
    bool could_permute = permute(begin+1, end);

    // if the suffix could be permuted, we are done
    if (could_permute)
        return true;

    // if the suffix can't be permuted,
    // then it is sorted in reverse

    // if begin[0] is greater than begin[1]
    if (begin[0] > begin[1])
        // begin[0] is greater than all elements in suffix (as suffix sorted)
        // hence we cannot permute anymore
        return false;

    // now at least one element, namely begin[1] is greater than begin[0]
    // we find the smallest element in the suffix that is still greater than begin[1]
    // TODO: by binary search?
    ptrdiff_t i = 0;
    do {
        i++;
    } while(i < end - begin && begin[i+1] > begin[0]);

    // now we need to swap begin[0] and begin[i] and reverse suffix
    std::swap(begin[0], begin[i]);
    // TODO: for longer suffixes this sort is not needed as we can simply reverse the sequence
    std::sort(begin+1, end+1);

    return true;
}

template<typename T>
bool permute(std::vector<T>& v) {
    return permute(&v[0], &v[v.size()-1]);
}


void digits(size_t x, uint8_t* out) {
    while (x > 0) {
        *out = x % 10;
        out++;
        x /= 10;
    }
}

template<typename T>
void print_digits(const std::vector<T>& digits) {
    for (auto d : digits)
        fmt::print("{}", d);
    fmt::println("");
}


#endif
