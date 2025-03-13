#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>

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
    
    static size_t default_size;
public:
    uint32_t *ints;
    
    bigint(const uint32_t &size) : ints(new uint32_t[size]{}), capacity(size) {}
    
    /* Converts std::string to big-integer. */
    bigint(const std::string &string);
    
    /* Copies Object. */
    bigint(const bigint &other);

    bigint();

    ~bigint();
    
    /* Converts big-integer to string that contains the decimal value. */
    std::string str();
    std::string poly_str(); // Returns polynomial of big integer in string
    
    // Transforms Bigint into base64 string. Can be used for compessing big-integer.
    std::string base64(); // Compress data in 2.5 times

    void extract64(const std::string &str); // Extracts BASE256 symbols and converts to big-integer.

    inline const std::size_t& size() {return capacity;}
    inline const uint32_t*  blocks() {return ints;}
    void reallocate(const size_t &new_capacity);

    // Default operators

    bigint operator+(const uint32_t &other) const noexcept;
    bigint operator-(const uint32_t &other) const noexcept;
    bigint operator*(const uint32_t &other) const noexcept;
    bigint operator/(const uint32_t &other) const noexcept;

    bigint operator+(const bigint &other) const noexcept ;
    bigint operator-(const bigint &other) const noexcept;
    bigint operator*(const bigint &other) const noexcept;
    bigint operator/(const bigint &other) const noexcept;
    
    void operator+=(const int32_t &other) noexcept;
    void operator-=(const int32_t &other) noexcept;
    void operator*=(const int32_t &other) noexcept;
    void operator/=(const int32_t &other) noexcept;
    void operator%=(const int32_t &other) noexcept;

    void operator+=(const bigint & other) noexcept;
    void operator-=(const bigint & other) noexcept;
    void operator*=(const bigint & other) noexcept;
    void operator/=(const bigint &other)  noexcept;
    void operator%=(const bigint &other)  noexcept;

    bool operator==(const int32_t &other) const noexcept;
    bool operator!=(const int32_t &other) const noexcept;
    bool operator< (const int32_t &other) const noexcept;
    bool operator> (const int32_t &other) const noexcept;
    bool operator>=(const int32_t &other) const noexcept;
    bool operator<=(const int32_t &other) const noexcept;

    bool operator==(const bigint &other) const noexcept;
    bool operator!=(const bigint &other) const noexcept;
    bool operator< (const bigint &other) const noexcept;
    bool operator> (const bigint &other) const noexcept;
    bool operator>=(const bigint &other) const noexcept;
    bool operator<=(const bigint &other) const noexcept;

    // Binary operators

    bigint operator>>(const int32_t &other) const noexcept;
    bigint operator<<(const int32_t &other) const noexcept;
    bigint operator| (const int32_t &other) const noexcept;
    bigint operator^ (const int32_t &other) const noexcept;
    bigint operator& (const int32_t &other) const noexcept;
    bigint operator% (const int32_t &other) const noexcept;

    bigint operator>>(const bigint &other) const noexcept;
    bigint operator<<(const bigint &other) const noexcept;
    bigint operator| (const bigint &other) const noexcept;
    bigint operator^ (const bigint &other) const noexcept;
    bigint operator& (const bigint &other) const noexcept;
    bigint operator% (const bigint &other) const noexcept;

    void operator>>= (const int32_t &other) noexcept;
    void operator<<= (const int32_t &other) noexcept;
    void operator&=  (const int32_t &other) noexcept;
    void operator|=  (const int32_t &other) noexcept;
    void operator^=  (const int32_t &other) noexcept;
    
    void operator>>= (const bigint &other) noexcept;
    void operator<<= (const bigint &other) noexcept;
    void operator&=  (const bigint &other) noexcept;
    void operator|=  (const bigint &other) noexcept;
    void operator^=  (const bigint &other) noexcept;

    // Other operations

    bigint pow(uint64_t exp) const;
    bigint pow(double exp)   const;

    bigint sqrt() const;

    uint32_t log10() const;
    uint32_t log2()  const;
    uint32_t log(uint32_t base) const;

    void reverse();     // Reverses bits in big integer.
    void shift_left();  // Makes fast 32bit shift to the left.
    void shift_right(); // Makes fast 32bit shift to the right.

    inline void negate() {this->sign = !sign;}
    inline size_t bit_length() const {return capacity*32;};

    // gcd(const bigint& a, const bigint& b);
    // lcm(const bigint& a, const bigint& b)

    static void set_default_size(const size_t &new_size); 
};

}

#endif