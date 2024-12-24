




#include <cstddef>
#include <iostream>
#include <string>


template <class T>
const char* func(){
    return __PRETTY_FUNCTION__;
}

template <typename T, T N>
std::string get_param_value() {
    std::string str = __PRETTY_FUNCTION__;
    std::endl(std::cout << "original str: " << str);
    auto pos = str.find("N = ") + 4;
    auto pos2 = str.find_first_of(";]", pos);
    return str.substr(pos, pos2 - pos);
}

enum color {
    RED = 1, BLUE = 2, YELLOW = 3, GREEN = 4,
};

template <size_t N>
struct integral_constant {
    static constexpr int value = N;
};

template <size_t beg, size_t end, class F>
void static_for(const F& func) {
    if constexpr (beg == end) return;
    else {
        func(integral_constant<beg>());
        static_for<beg + 1, end>(func);
    }
}

template <typename T>
std::string get_enum_val_dynamic(T n) {
    std::string ret;
    static_for<0, 3>([&] (auto ic) {
        constexpr auto i = ic.value;
        if (n == T(i)) ret =  get_param_value<T, (T)i>();
    });
    return ret;
}

int main() {
    color color_ = RED;
    std::cout << get_enum_val_dynamic<color>(color_);
}



/*template <class T>
std::string get_type_name() {
    std::string str = __PRETTY_FUNCTION__;
    std::cout << "original str: " << str << '\n';
    auto pos = str.find("T = ") + 4;
    std::cout << "pos: " << pos << '\n';
    auto pos2 = str.find_first_of(";]", pos);
    std::cout << "pos2: " << pos2 << '\n';
    return str.substr(pos, pos2 - pos);
}*/