#include "ntype/bigint.hpp"
#include <iostream>

const uint64_t base[] = {
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

bigint::bigint(const bigint &other) : 
    ints(new uint32_t[other.capacity]), 
    capacity(other.capacity), 
    cursor(other.cursor), 
    sign(other.sign) 
{
    memcpy(ints, other.ints, sizeof(uint32_t)*capacity);
}

bigint::bigint(const std::string &string) : ints(new uint32_t[4]{}), capacity(4) {
    size_t str_size = string.size();
    if (!string.empty() && string[0] == '-') sign = true;

    for(size_t i = sign; i < str_size; i+=BLOCK_SIZE) {
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
        if(carry) {
            size_t index = capacity;
            this->reallocate();

            ints[index] = carry;
        }

        for(size_t j = 0; j < capacity; ++j) { 
            uint32_t sum = ints[j] + value;
            ints[j] = sum;
            value   = sum < ints[j];

            if(value == 0) break;
        }
        if(value) {
            size_t index = capacity;
            this->reallocate();

            ints[index] = carry;
        }
    }
}

bigint::~bigint() {
    if(ints) {delete[] ints;}
}

void bigint::reallocate() {
    const size_t new_capacity = capacity*2;

    uint32_t *new_ints = new uint32_t[new_capacity]{};
    memcpy(new_ints, ints, sizeof(uint32_t) * capacity);
    capacity = new_capacity;

    delete[] ints;
    ints = new_ints;
}

bigint bigint::operator+(const bigint & other) noexcept {
    bigint result;
    bool carry = 0;
    for (size_t i = 0; i < capacity; ++i) { 
        const uint32_t &a = ints[i];
        const uint32_t &b = other.ints[i];
        const uint32_t sum = a + b + carry;
        carry = sum < a;

        result.ints[i] = sum;
    }
    return result;
}

bigint bigint::operator-(const bigint & other) noexcept {
    bigint result;
    bool carry = 0;
    for (size_t i = 0; i < capacity; ++i) { 
        const uint32_t &a = ints[i];
        const uint32_t &b = other.ints[i];
        const uint32_t sub = a - b - carry;
        carry = a < b;

        result.ints[i] = sub;
    }
    return result;
}

bigint bigint::operator*(const bigint &other) noexcept {
    bigint result;
    uint64_t carry = 0;
    for (size_t i = 0; i < capacity; ++i) {
        for (size_t j = 0; j < other.capacity; ++j) {
            if(capacity-1 < j+i) break;

            uint64_t product = static_cast<uint64_t>(ints[i]) * other.ints[j] + carry + result.ints[j+i];

            result.ints[j+i] = static_cast<uint32_t>(product);
            carry  = product >> 32;
        }
    }
    return result;
}

bigint bigint::operator/(const bigint &other) noexcept {
    //bigint result, remainder = *this;
    //for (size_t i = capacity; i-- > 0;) { 
    //    remainder <<= 1;
    //    remainder.ints[0] = ints[i];

    //    uint32_t q = 0;
    //    while (remainder >= other) {
    //        remainder -= other;
    //        ++q;
    //    }

    //    result.ints[i] = q;
    //}

    //return result;
    return {};
}

void bigint::operator+=(const bigint &other) noexcept {
    bool carry = 0;
    for (size_t i = 0; i < capacity; ++i) { 
        uint32_t &a = ints[i];
        const uint32_t &b = other.ints[i];
        const uint32_t sum = a + b + carry;
        carry = sum < a;
        a = sum;
    }
}

void bigint::operator-=(const bigint &other) noexcept {
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
    for (size_t i = 0; i < other.capacity; ++i) {
        for (size_t j = 0; j < capacity; ++j) {
            if(capacity-1 < j+i) break;

            uint64_t product = static_cast<uint64_t>(ints[i]) * other.ints[j] + carry + res[j];

            res[j] = static_cast<uint32_t>(product);
            carry  = product >> 32;
        }
        if(carry)
    }
    delete[] ints;
    this->ints = res;
}

void bigint::operator/=(const bigint &other) noexcept {
    
}



void bigint::operator%=(const int64_t &other) noexcept {}
void bigint::operator%=(const bigint &other) noexcept {}

bigint bigint::operator>>(const int64_t &other) noexcept {return {};};
bigint bigint::operator<<(const int64_t &other) noexcept {return {};};
bigint bigint::operator| (const int64_t &other) noexcept {return {};};
bigint bigint::operator^ (const int64_t &other) noexcept {return {};};
bigint bigint::operator& (const int64_t &other) noexcept {return {};};
bigint bigint::operator% (const int64_t &other) noexcept {return {};};
void bigint::operator>>= (const int64_t &other) noexcept {};
void bigint::operator<<= (const int64_t &other) noexcept {};

bigint bigint::operator>>(const bigint &other) noexcept {return {};};
bigint bigint::operator<<(const bigint &other) noexcept {return {};};
bigint bigint::operator| (const bigint &other) noexcept {return {};};
bigint bigint::operator^ (const bigint &other) noexcept {return {};};
bigint bigint::operator& (const bigint &other) noexcept {return {};};
bigint bigint::operator% (const bigint &other) noexcept {return {};};
void bigint::operator>>= (const bigint &other) noexcept {};
void bigint::operator<<= (const bigint &other) noexcept {};

bool bigint::operator!=(const int64_t &other) noexcept {return 0;};
bool bigint::operator==(const int64_t &other) noexcept {return 0;};
bool bigint::operator< (const int64_t &other) noexcept {return 0;};
bool bigint::operator> (const int64_t &other) noexcept {return 0;};
bool bigint::operator>=(const int64_t &other) noexcept {return 0;};
bool bigint::operator<=(const int64_t &other) noexcept {return 0;};

bool bigint::operator==(const bigint &other) noexcept {return 0;};
bool bigint::operator!=(const bigint &other) noexcept {return 0;};
bool bigint::operator< (const bigint &other) noexcept {return 0;};
bool bigint::operator> (const bigint &other) noexcept {return 0;};
bool bigint::operator>=(const bigint &other) noexcept {return 0;};
bool bigint::operator<=(const bigint &other) noexcept {return 0;};

std::string bigint::str() {
    return "";
}

bigint bigint::pow(uint64_t exp) {
    bigint result(capacity);
    bigint base = *this;
    
    result.ints[0] = 1;
    while(exp) {
        if (exp & 1) result *= base;

        exp >>= 1;
        base *= base;
    }
    return result;
}

bigint bigint::sqrt() {
    // if (x < 0) return -1; // Ошибка
    // if (x == 0 || x == 1) return x;

    //long long left = 1, right = x, ans = 0;
    //while (left <= right) {
    //    long long mid = left + (right - left) / 2;
    //    if (mid * mid == x) return mid;
    //    if (mid * mid < x) {
    //        left = mid + 1;
    //        ans = mid;
    //    } else {
    //        right = mid - 1;
    //    }
    //}
    //return ans;
    return {};
}