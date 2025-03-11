#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

#define STANDARD_SIZE 2
#define BLOCK_SIZE 20ULL
#define BASE 10'000'000'000'000'000'000ULL

#define ABS(i1) (i1 < 0 ? -i1 : i1)
#define MIN(i1, i2) (i1 < i2 ? i1 : i2)
#define MAX(i1, i2) (i1 > i2 ? i1 : i2)

namespace mtp {

class bigint {
public:  
    uint32_t *ints;
    size_t capacity;
    
    bool is_signed = false;

    bigint() : ints(new uint32_t[2]{}), capacity(2) {}

    bigint(const uint32_t &bits) : ints(new uint32_t[bits/64]{}), capacity(bits/64) {}

    bigint(const std::string &string) : ints(new uint32_t[STANDARD_SIZE]{}) {
        size_t str_size = string.size();
        if (!string.empty() && string[0] == '-') is_signed = true;

        uint32_t carry = 0;
        for(size_t i = is_signed; i < str_size; i+=BLOCK_SIZE) {
            const size_t &len = MIN(BLOCK_SIZE, str_size - i);

            uint64_t value = 0;
            for(size_t j = 0; j < len; j++) {
                value = value * 10 + (string[i+j]-'0');
            }

            uint64_t carry = 0;
            for (size_t j = 0; j < capacity; ++j) {
                uint64_t product = (uint64_t)ints[j] * BASE + carry;
                ints[j] = (uint32_t)product;
                carry   = product >> 32;
            }

            carry = value;
            for(size_t j = 0; j < capacity; ++j) { 
                uint64_t sum = (uint64_t)ints[j] + carry;
                ints[j] = sum & UINT_MAX;
                carry = sum >> 32;
                
                if(carry == 0) break;
            }
        }
    }

    ~bigint() {
        if(ints) delete[] ints;
    }
    
    const std::string str() {
        return {};
    }

    bigint operator+(const bigint &other) {

    }

    bigint operator-(const bigint &other) {

    }

    bigint operator*(const bigint &other) {

    }

    bigint operator/(const bigint &other) {
        if(other.is_signed && is_signed) is_signed = false;
    }

    void operator+=(const bigint & other) noexcept {
        bool carry = 0;
        for (size_t i = 0; i < capacity; ++i) { 
            uint32_t &a = ints[i];
            const uint32_t &b = other.ints[i];
            const uint32_t sum = a + b + carry;
            carry = sum < a;
            a = sum;
        }
    }

    void operator-=(const bigint & other) noexcept {
        bool carry = 0;
        for (size_t i = 0; i < capacity; ++i) { 
            uint32_t &a = ints[i];
            const uint32_t &b = other.ints[i];
            const uint32_t sub = a - b - carry;
            carry = a < b;
            a = sub;
        }
    }

    void operator*=(const bigint & other) noexcept {
        if(other.is_signed && is_signed) is_signed = false;
        uint32_t *res = new uint32_t[capacity]{};
        uint64_t carry = 0;
        for (size_t i = 0; i < other.capacity; i++) {
            carry = 0;
            for (size_t j = 0; j < capacity; j++) {
                uint64_t product = (uint64_t)ints[j] * other.ints[i] + carry;
                res[j]     += (uint32_t)product;
                carry = product >> 32;
            }
        }
        this->ints = res;
    }

    void operator/=(const bigint &other) noexcept {

    }

    bigint operator+(const int &other) {

    }

    bigint operator-(const int &other) {

    }

    bigint operator*(const int &other) {
        bigint result;

    }

    bigint operator/(const int &other) {
        bigint result;
    }

    void operator+=(const unsigned int &other) noexcept {

    }

    void operator-=(const int &other) noexcept {

    }

    void operator*=(const int &other) noexcept {

    }

    void operator/=(const int &other) noexcept {

    }
};

static bigint pow(bigint base, uint32_t exp) {
    bigint result;
    result.ints[0] = 1;
    while(exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

static bigint sqrt(const bigint& number) {
    
}


}

#endif