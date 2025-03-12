#ifndef INTS_HPP
#define INTS_HPP

#include <string>

namespace ntp {

template <size_t Integers, bool Signed>
struct int_struct {
    const std::string str();

    int_struct operator-(const int_struct &other) noexcept {};
    int_struct operator+(const int_struct &other) noexcept {};
    int_struct operator*(const int_struct &other) noexcept {};
    int_struct operator/(const int_struct &other) noexcept {};

    void operator+=(const int_struct &other) noexcept {};
    void operator-=(const int_struct &other) noexcept {};
    void operator*=(const int_struct &other) noexcept {};
    void operator/=(const int_struct &other) noexcept {};

    int_struct operator+(const int64_t &other) {};
    int_struct operator-(const int64_t &other) {};
    int_struct operator*(const int64_t &other) {};
    int_struct operator/(const int64_t &other) {};

    void operator+=(const int64_t &other) noexcept {};
    void operator-=(const int64_t &other) noexcept {};
    void operator*=(const int64_t &other) noexcept {};
    void operator/=(const int64_t &other) noexcept {};
private:
    uint32_t ints[Integers];
    bool sign = Signed;
    bool overflowed = 0;
};

using int128_t = int_struct<4, true>;
using int256_t = int_struct<8, true>;
using int512_t = int_struct<16,true>;

using uint128_t = int_struct<4, false>;
using uint256_t = int_struct<8, false>;
using uint512_t = int_struct<16,false>;

}

#endif