#include "ntype/bigint.hpp"
#include <iostream>

static const uint64_t base[] = {
    1, 
    1'0,
    1'00,
    1'000,
    1'000'0,
    1'000'00,
    1'000'000,
    1'000'000'0,
    1'000'000'00,
    1'000'000'000,
}; /* predefined bases */

using namespace ntp;

bigint::bigint(const std::string &string) : ints(new uint32_t[32]{}), capacity(32) {
    size_t str_size = string.size();
    if (!string.empty() && string[0] == '-') is_signed = true;

    for(size_t i = is_signed; i < str_size; i+=BLOCK_SIZE) {
        const size_t &len = MIN(BLOCK_SIZE, str_size - i);

        uint64_t value = 0;
        for(size_t j = 0; j < len; j++) {
            value = value * 10 + (string[i+j]-'0');
        } /* value parsing */
         
        uint64_t carry = 0;
        for (size_t j = 0; j < capacity; ++j) {
            uint64_t product = static_cast<uint64_t>(ints[j]) * base[len] + carry;

            ints[j] = static_cast<uint32_t>(product);
            carry   = product >> 32;
        }

        for(size_t j = 0; j < capacity; ++j) { 
            uint32_t sum = ints[j] + value;
            ints[j] = sum;
            value   = sum < ints[j];

            if(value == 0) break;
        }
    }
}

bigint bigint::operator+(const bigint & other) noexcept {
    return {};
}

bigint bigint::operator-(const bigint & other) noexcept {
    return {};
}

bigint bigint::operator*(const bigint & other) noexcept {
    return {};
}

bigint bigint::operator/(const bigint & other) noexcept {
    return {};
}

void bigint::operator+=(const bigint & other) noexcept {
    bool carry = 0;
    for (size_t i = 0; i < capacity; ++i) { 
        uint32_t &a = ints[i];
        const uint32_t &b = other.ints[i];
        const uint32_t sum = a + b + carry;
        carry = sum < a;
        a = sum;
    }
}

void bigint::operator-=(const bigint & other) noexcept {
    bool carry = 0;
    for (size_t i = 0; i < capacity; ++i) { 
        uint32_t &a = ints[i];
        const uint32_t &b = other.ints[i];
        const uint32_t sub = a - b - carry;
        carry = a < b;
        a = sub;
    }
}

void bigint::operator*=(const bigint &other) noexcept {
    uint32_t *res = new uint32_t[capacity]{};

    uint64_t carry = 0;
    for (size_t i = 0; i < other.capacity; i++) {
        for (size_t j = 0; j < capacity; j++) {
            uint64_t product = static_cast<uint64_t>(ints[j]) * other.ints[i] + carry;

            res[j] += static_cast<uint32_t>(product);
            carry  = product >> 32;
        }
    }

    delete[] ints;
    this->ints = res;
}

void bigint::operator/=(const bigint & other) noexcept {

}

namespace ntp {

bigint pow(bigint base, uint64_t exp) {
    bigint result = base.capacity;
    result.ints[0] = 1;
    while(exp) {
        if (exp & 1) result *= base;

        exp >>= 1;
        base *= base;
    }
    return result;
}

bigint sqrt(const bigint& number) {
    return {};
}

}