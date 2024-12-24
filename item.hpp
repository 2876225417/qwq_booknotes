


#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>

template <typename T>
struct point {
    T width;
    T height;
    T length;

    friend std::ostream& operator<<(std::ostream& os, const point& obj) {
        os << "width: "  << obj.width 
           << "height: " << obj.height
           << "length: " << obj.length
           << '\n';
        return os;
    }
};

#endif