#include <iostream>
#include "../src/array.hpp"


int main () {
    array<int, 5> x{1,2,3,4,5};
    for (const auto & v : x) {
        std::cout << v << "\n";
    }
}
