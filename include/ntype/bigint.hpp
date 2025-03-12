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
private:  
    
    size_t capacity;
    size_t cursor = 1;
    bool sign = 0;

    void reallocate();
public:
uint32_t *ints;

    bigint() : ints(new uint32_t[2]{}), capacity(2) {}

    bigint(const uint32_t &size) : ints(new uint32_t[size]{}), capacity(size) {}

    bigint(const std::string &string);

    bigint(const bigint &other);

    ~bigint();

    std::string str();

    inline const uint32_t* blocks()  {return ints;}
    inline const std::size_t& size() {return capacity;}

    bigint operator+(const int64_t &other);
    bigint operator-(const int64_t &other);
    bigint operator*(const int64_t &other);
    bigint operator/(const int64_t &other);

    bigint operator+(const bigint &other) noexcept;
    bigint operator-(const bigint &other) noexcept;
    bigint operator*(const bigint &other) noexcept;
    bigint operator/(const bigint &other) noexcept;
    
    void operator+=(const int64_t &other) noexcept;
    void operator-=(const int64_t &other) noexcept;
    void operator*=(const int64_t &other) noexcept;
    void operator/=(const int64_t &other) noexcept;
    void operator%=(const int64_t &other) noexcept;

    void operator+=(const bigint & other) noexcept;
    void operator-=(const bigint & other) noexcept;
    void operator*=(const bigint & other) noexcept;
    void operator/=(const bigint &other)  noexcept;
    void operator%=(const bigint &other) noexcept;

    bool operator==(const int64_t &other) noexcept;
    bool operator!=(const int64_t &other) noexcept;
    bool operator< (const int64_t &other) noexcept;
    bool operator> (const int64_t &other) noexcept;
    bool operator>=(const int64_t &other) noexcept;
    bool operator<=(const int64_t &other) noexcept;

    bool operator==(const bigint &other) noexcept;
    bool operator!=(const bigint &other) noexcept;
    bool operator< (const bigint &other) noexcept;
    bool operator> (const bigint &other) noexcept;
    bool operator>=(const bigint &other) noexcept;
    bool operator<=(const bigint &other) noexcept;

    /* binary operators */
    bigint operator>>(const int64_t &other) noexcept;
    bigint operator<<(const int64_t &other) noexcept;
    bigint operator| (const int64_t &other) noexcept;
    bigint operator^ (const int64_t &other) noexcept;
    bigint operator& (const int64_t &other) noexcept;
    bigint operator% (const int64_t &other) noexcept;

    void operator>>= (const int64_t &other) noexcept;
    void operator<<= (const int64_t &other) noexcept;
    void operator&=  (const int64_t &other) noexcept;
    void operator|=  (const int64_t &other) noexcept;
    void operator^=  (const int64_t &other) noexcept;

    bigint operator>>(const bigint &other) noexcept;
    bigint operator<<(const bigint &other) noexcept;
    bigint operator| (const bigint &other) noexcept;
    bigint operator^ (const bigint &other) noexcept;
    bigint operator& (const bigint &other) noexcept;
    bigint operator% (const bigint &other) noexcept;
    
    void operator>>= (const bigint &other) noexcept;
    void operator<<= (const bigint &other) noexcept;
    void operator&=  (const bigint &other) noexcept;
    void operator|=  (const bigint &other) noexcept;
    void operator^=  (const bigint &other) noexcept;

    bigint pow(uint64_t exp);
    bigint sqrt();

    inline void negate() {this->sign = !sign;}
    uint64_t bit_length();

    // gcd(const bigint& a, const bigint& b);
    // lcm(const bigint& a, const bigint& b)
};

}

#endif