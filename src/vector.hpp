#pragma once
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>

template <typename T>
class vector {
    static_assert(std::is_trivially_constructible_v<T>);
    static_assert(std::is_trivially_destructible_v<T>);
    T * buffer;
    std::size_t buffCap;
    std::size_t numElts;

    public:

    constexpr vector() {
        buffer = reinterpret_cast<T *>(malloc(sizeof(T)));
        buffCap = 1;
        numElts = 0;
    }

    ~ vector() {
        free(buffer);
    }



    constexpr vector(std::initializer_list<T> const args) : buffCap(1), numElts(0) {
        buffer = reinterpret_cast<T *>(malloc(sizeof(T)));
        for (auto & v : args) {
            push(std::remove_cv_t<T>(v));
        }
    }

    void push(T datum) {
        if (numElts == buffCap) {
            T * tmp = reinterpret_cast<T *>(malloc(sizeof(T) * buffCap << 1));
            std::memcpy(tmp, buffer, sizeof(T) * buffCap);
            free(buffer);
            buffer = tmp;
            buffCap <<= 2;

        }

        buffer[numElts++] = datum;

    }

    void push(T datum, std::size_t _idx) {
        if (_idx >= buffCap) throw std::runtime_error("Inserting past range of vector\n");
        (buffer + _idx) = datum;
    }

    [[nodiscard]] inline auto get(std::size_t _idx) -> T {
        if (_idx >= buffCap) throw std::runtime_error("Accessing out of bounds of vector\n");
        return *(buffer + _idx);
    }

    //default construct type. Behavior is non standard compient.
    inline void pop() {
        (buffer + numElts--);
    }

    [[nodiscard]] auto inline size() noexcept -> std::size_t  {
        return numElts;
    }

    [[nodiscard]] auto inline getCapacity() noexcept -> std::size_t  {
        return buffCap;
    }

    [[nodiscard]] inline auto operator[] (std::size_t _idx) -> T & {
        return buffer[_idx];
    }

    constexpr vector(const vector<T> & vec) {
        buffer = reinterpret_cast<T *>(malloc(vec.buffCap * sizeof(T)));
        buffCap = vec.buffCap;
        for (const auto & val : vec) {
            push(val);
        }

    }

    [[nodiscard]] inline auto empty() noexcept -> bool {
        return size() == 0;
    }

    [[nodiscard]] inline constexpr T *begin() {return buffer; }
    [[nodiscard]] inline constexpr T *end() {return buffer + numElts;}
    [[nodiscard]] inline constexpr const T *begin() const {return buffer; }
    [[nodiscard]] inline constexpr const T *end() const { return buffer + numElts; }
    [[nodiscard]] inline constexpr const T *cbegin() const {return buffer; }
    [[nodiscard]] inline constexpr const T *cend() const {return buffer + numElts; }
    [[nodiscard]] inline constexpr T &front() {return *buffer; }
    [[nodiscard]] inline constexpr const T &front() const {return *buffer; }

};
