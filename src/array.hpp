#pragma once

#include <cstdlib>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include "tuple.hpp"

template<typename T, std::size_t SIZE>
class array {

    static_assert(std::is_trivially_destructible_v<T>);
    static_assert(std::is_trivially_constructible_v<T>);

    T * __buffer;
    public:
    constexpr array() {
        __buffer = reinterpret_cast<T *>(malloc(sizeof(T) * SIZE));
    }

    constexpr array(std::initializer_list<T> const args) : __buffer(nullptr) {
        if (sizeof(args) > SIZE * sizeof(T)) throw std::runtime_error("Accessing out of bounds of array buffer");
        __buffer = reinterpret_cast<T *>(malloc(sizeof(T) * SIZE));
        std::size_t _idx = 0;
        for (auto & v : args) {
            __buffer[_idx++] = v;
        }
    }

    ~array() {
        free(__buffer);
    }

    constexpr T &operator[](std::size_t _idx) {
        if (_idx >= SIZE) throw std::runtime_error("Accessing out of bounds of array buffer");
        return __buffer[_idx];
    }

    [[nodiscard]] constexpr inline auto begin() -> T *{return __buffer; }
    [[nodiscard]] constexpr inline auto end() -> T * {return __buffer + SIZE; }
    [[nodiscard]] constexpr inline auto begin() const -> const  T * {return __buffer; }
    [[nodiscard]] constexpr inline auto end() const -> const T * {return __buffer + SIZE; }
    [[nodiscard]] constexpr inline auto cbegin() const -> const T * {return __buffer; }
    [[nodiscard]] constexpr inline auto cend() const -> const T * {return __buffer + SIZE; }
    [[nodiscard]] constexpr inline auto front()-> T & {return *__buffer; }
    [[nodiscard]] constexpr inline auto front() const -> const T & {return *__buffer; }

};
template<std::size_t _idx, typename T, std::size_t SIZE>
[[nodiscard]] constexpr inline auto get(const array<T,SIZE> &buffer) {
    return buffer[_idx];
}
