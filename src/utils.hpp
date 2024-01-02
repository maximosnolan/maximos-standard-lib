#include <cstdlib>

void * operator new(std::size_t n) {
    void * const p = std::malloc(n);
    if (p == nullptr) {
        return nullptr;
    }
    return p;
}

void operator delete(void * p) {
    std::free(p);
}
