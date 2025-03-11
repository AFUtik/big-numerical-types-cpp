#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>

#define STANDARD_SIZE 2
#define BLOCK_SIZE 9ULL

#define ABS(i1) (i1 < 0 ? -i1 : i1)
#define MIN(i1, i2) (i1 < i2 ? i1 : i2)
#define MAX(i1, i2) (i1 > i2 ? i1 : i2)

namespace ntp {

class bigint {
public:  
    uint32_t *ints;
    size_t capacity;
    size_t cursor = 1;
    
    bool is_signed = false;

    bigint() : ints(new uint32_t[4]{}), capacity(4) {}

    bigint(const uint32_t &size) : ints(new uint32_t[size]{}), capacity(size) {}

    bigint(const std::string &string);

    ~bigint() {
        if(ints) delete[] ints;
    }
    
    const std::string str() {
        return {};
    }

    bigint operator+(const bigint &other) noexcept;
    bigint operator-(const bigint &other) noexcept;
    bigint operator*(const bigint &other) noexcept;
    bigint operator/(const bigint &other) noexcept;

    void operator+=(const bigint & other) noexcept;
    void operator-=(const bigint & other) noexcept;
    void operator*=(const bigint & other) noexcept;
    void operator/=(const bigint &other)  noexcept;

    bigint operator+(const int &other);
    bigint operator-(const int &other);
    bigint operator*(const int &other);
    bigint operator/(const int &other);

    void operator+=(const int &other) noexcept;
    void operator-=(const int &other) noexcept;
    void operator*=(const int &other) noexcept;
    void operator/=(const int &other) noexcept;
};

extern bigint pow(bigint base, uint32_t exp);

extern bigint sqrt(const bigint& number);

}

#endif