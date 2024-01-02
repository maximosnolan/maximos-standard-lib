#include "../src/tuple.hpp"
#include <string>
#include <iostream>
int main() {
    std::string a{"maximos"};
    int b = 73;
    tuple t{5.0, 6, a};
    std::cout << get<2>(t) << "\n";

}
