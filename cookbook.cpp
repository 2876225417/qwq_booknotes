

#include "message.h"

#include <cstdlib>
#include <iostream>

template <typename T>
inline const T& max(const T& a, const T& b) {
    std::cout << "Template deduction!\n";
    return a > b ? a : b;
}

inline const int& max(const int&, const int&);

template <typename T>
inline const T& max(const T& a, const T& b, const T& c) {
    std::cout << "Check before deduce!\n";
    return max(max(a, b), c);
}

inline const int& max(const int& a, const int& b) {
    std::cout << "Specified for int!\n";
    return a > b ? a : b;
}

int main() {
    auto t = max(3, 2, 1);
}




