#ifndef BASE256_H
#define BASE256_H

template <typename B = unsigned char, typename T, size_t Bits = 6, size_t Offset = 32>
inline void n_to_base(B (&array)[(sizeof(T) * 8) / Bits], const T& object) {
    constexpr B mask = (1 << Bits) - 1;
    for(size_t i = 0; i < (sizeof(T)*8)/Bits; i++) 
        array[i] = Offset + static_cast<B>((object >> (Bits * i)) & mask);
}

#endif