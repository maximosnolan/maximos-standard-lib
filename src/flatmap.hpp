#ifndef FLATMAP_HPP
#define FLATMAP_HPP

#include "vector.hpp"

template <typename KeyType, typename ValueType>
struct KeyValuePair {
    KeyType key;
    ValueType value;

    [[nodiscard]] constexpr inline bool operator<(const KeyValuePair & other) {
        return key < other.key;
    }
};


template <typename KeyType, typename ValueType>
class flatmap {
    public:

    private:
};


#endif //FLATMAP_HPP
