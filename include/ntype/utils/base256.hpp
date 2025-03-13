#ifndef BASE256_HPP
#define BASE256_HPP

#include <string>

template <typename T>
inline void to_base256(std::string &str, const T& object) {
    for(size_t i = 0; i < sizeof(T); i++) str.push_back(object<<(8*i));
}

template <typename T>
inline void to_base128(std::string &str, const T& object) {
    for(size_t i = 0; i < sizeof(T); i++) str.push_back(object<<(7*i));
}

template <typename T>
inline void to_base64(std::string &str, const T& object) {
    for(size_t i = 0; i < sizeof(T); i++) str.push_back(object<<(6*i));
}


#endif