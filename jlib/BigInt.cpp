#include <jlib/BigInt.hpp>
#include <fmt/core.h>
#include <string_view>
#include <util.hpp>

namespace jlib {

using u64 = BigInt::u64;
using u128 = BigInt::u128;

static u64 high(u128 x) {
    return x >> 64;
}

static u64 low(u128 x) {
    return (u64)x;
}

BigInt operator ""_BigInt(const char* in) {
    std::stringstream ss(in);
    return BigInt::parse(ss);
}

BigInt& BigInt::operator=(const BigInt& other) {
    // copy
    m_data = other.m_data;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const {
    u64 m = std::min(m_data.size(), other.m_data.size());
    for (u64 i = 0; i < m; i++)
        if (m_data[i] != other.m_data[i])
            return false;
    for (size_t i = m; i < m_data.size(); i++)
        if (m_data[i] != 0)
            return false;
    for (size_t i = m; i < other.m_data.size(); i++)
        if (other.m_data[i] != 0)
            return false;
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !BigInt::operator==(other);
}

BigInt& BigInt::operator+=(u64 a) {
    /*

        [a4 a3 a2 a1 a0]
      + [00 00 00 00  a]

    =>

        [a4 a3 a2 a1  l]
      + [00 00 00  c 00]

    */

    u64 carry = a;
    for (u64 i = 0; i < m_data.size() && carry > 0; i++) {
        u128 result = (u128)m_data[i] + (u128)carry;
        m_data[i] = low(result);
        carry = high(result);
    }

    if (carry > 0)
        m_data.push_back(carry);

    return *this;
}


BigInt& BigInt::operator*=(u64 a) {
    /*
        computing a0 * a results in

            [00 00|Hh Hl|00 00]
            [00 00|00 Mh|Ml 00]
            [00 00|00 00|Lh Ll]

        computing a1 * a results in

            [Hh Hl|00 00|00 00]
            [00 Mh|Ml 00|00 00]
            [00 00|Lh Ll|00 00]

        overlapping nicely
    */

    u64 carry = 0;

    for (u64 i = 0; i < m_data.size(); i++) {
        u128 mul = (u128)m_data[i] * (u128)a;
        u128 add = (u128)low(mul) + (u128)carry; // is high(add) ever non zero?
        m_data[i] = low(add);
        carry = high(mul) + high(add); // this should not overflow
    }

    if (carry > 0)
        m_data.push_back(carry);

    return *this;
}


BigInt& BigInt::operator+=(BigInt a) {
    u64 carry = 0;
    u64 m = std::min(m_data.size(), a.m_data.size());

    for (u64 i = 0; i < m; i++) {
        u128 addition = (u128)m_data[i] + (u128)a.m_data[i] + (u128)carry;
        m_data[i] = low(addition);
        carry = high(addition);
    }

    for (u64 i = m; i < m_data.size(); i++) {
        u128 addition = (u128)m_data[i] + (u128)carry;
        m_data[i] = low(addition);
        carry = high(addition);
    }

    for (u64 i = m; i < a.m_data.size(); i++) {
        u128 addition = (u128)a.m_data[i] + (u128)carry;
        m_data.push_back(low(addition));
        carry = high(addition);
    }

    if (carry > 0)
        m_data.push_back(carry);

    return *this;
}


BigInt BigInt::operator+(BigInt a) const {
    BigInt copy = *this;
    copy += a;
    return copy;
}


BigInt& BigInt::operator++() {
    return *this += 1;
}


bool BigInt::operator<(BigInt a) const {
    int64_t m = std::min(m_data.size(), a.m_data.size());

    for (int64_t i = m_data.size()-1; i >= m; i--)
        if (m_data[i] > 0)
            return false;
    for (int64_t i = a.m_data.size()-1; i >= m; i--)
        if (a.m_data[i] > 0)
            return true;

    for (int64_t i = m-1; i >= 1; i--)
        if (m_data[i] > a.m_data[i])
            return false;

    return m_data[0] < a.m_data[0];
}

bool BigInt::operator<=(BigInt a) const {
    int64_t m = std::min(m_data.size(), a.m_data.size());

    for (int64_t i = m_data.size()-1; i >= m; i--)
        if (m_data[i] > 0)
            return false;
    for (int64_t i = a.m_data.size()-1; i >= m; i--)
        if (a.m_data[i] > 0)
            return true;

    for (int64_t i = m-1; i >= 1; i--)
        if (m_data[i] > a.m_data[i])
            return false;

    return m_data[0] <= a.m_data[0];
}

bool BigInt::operator>(BigInt a) const {
    return !(*this <= a);
}
bool BigInt::operator>=(BigInt a) const {
    return !(*this < a);
}
bool BigInt::operator<(size_t a) const {
    return *this < BigInt(a);
};
bool BigInt::operator<=(size_t a) const {
    return *this <= BigInt(a);
};
bool BigInt::operator>(size_t a) const {
    return *this > BigInt(a);
};
bool BigInt::operator>=(size_t a) const {
    return *this >= BigInt(a);
};

BigInt::u64 BigInt::divide(u64 x) {
    u128 remainder = 0;

    for (size_t i = m_data.size()-1; i+1>0; i--) {
        remainder = (remainder << 64) | m_data[i];

        u64 r = remainder % x; // as x is u64, the remainder is less than x, hence also u64
        u64 q = remainder / x; // if q were u128, then x would have fit into the upper u64-nibble of current, which can't be as that is the remainder from last cycle

        remainder = r;
        m_data[i] = q;
    }

    return remainder;
}


BigInt BigInt::random(size_t length) {
    std::random_device rng;
    std::default_random_engine engine{rng()};
    std::uniform_int_distribution<size_t> digit(0, 9);
    std::uniform_int_distribution<size_t> first_digit(1, 9); // first digit can't be zero

    std::stringstream ss;
    ss.put(first_digit(engine));

    for (size_t i = 1; i < length; i++)
        ss.put(digit(engine));

    return BigInt::parse(ss);
}


BigInt BigInt::parse(const std::string& s) {
    std::stringstream in(s);
    BigInt big;

    for (int8_t c = in.peek() - '0'; c >= 0 && c <= 9; in.get(), c = in.peek() - '0') {
        big *= 10;
        big += c;
    }

    return big;
}


BigInt BigInt::parse(std::istream& in) {
    BigInt big;

    for (int8_t c = in.peek() - '0'; c >= 0 && c <= 9; in.get(), c = in.peek() - '0') {
        big *= 10;
        big += c;
    }

    return big;
}

std::vector<uint8_t> BigInt::digits(uint8_t base /* = 10 */) const {
    if (*this == 0_BigInt)
        return {0};
    std::vector<uint8_t> ds;
    BigInt quotient = *this;
    BigInt zero;
    while(quotient != zero) {
        u64 remainder = quotient.divide(base);
        ds.push_back(remainder);
    }
    return ds;
}

std::string BigInt::to_string() const {
    if (*this == 0_BigInt)
        return "0";
    std::stringstream ss;
    std::vector<uint8_t> ds = digits((uint8_t)10);
    for (uint8_t c : ds)
        ss.put('0' + c);
    std::string s = ss.str();
    std::reverse(s.begin(), s.end());
    return s;
}

size_t BigInt::hash() const {
    size_t h = 0;
    for (size_t section : m_data)
        hash_combine(h, section);
    return h;
}

}

template<>
struct std::hash<jlib::BigInt> {
    size_t operator()(const jlib::BigInt& I) const noexcept {
        return I.hash();
    }
};

template<>
struct fmt::formatter<jlib::BigInt> : fmt::formatter<string_view> {
    template<typename FormatContext>
    auto format(jlib::BigInt& I, FormatContext& ctx) const {
        return fmt::formatter<string_view>::format(I.to_string(), ctx);
    }
};
