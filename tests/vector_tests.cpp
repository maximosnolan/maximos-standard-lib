#include "../src/vector.hpp"
#include <iostream>

int main () {
    vector<int> x;
    x.push(5);
    x.push(4);
    x.push(7);
    x.push(22);
    x.push(43);
    vector<int> y = {1,2,3,4};
    for (const auto val : y) {
        std::cout << val << "\n";
    }
    for (auto val : x) {
        std::cout << val << "\n";
    }
    vector<int> z = x;
    for (auto val : z) {
        std::cout << val << "\n";
    }
}
