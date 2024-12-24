#ifndef MAX_HPP
#define MAX_HPP

#include <string>

namespace test{
    template<class T>
    inline T max(const T& a, const T& b) {
        return a > b ? a : b;
    }    
}

#endif