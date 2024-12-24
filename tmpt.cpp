


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "max.hpp"
#include "qwq_sort.hpp"
#include "qwq_big_num.hpp"

struct Base { virtual void f() {} };

struct Derived: Base {};

int main() {
    std::string str_2 = "2323123123123222";
    std::string str_1 = "1231200000232312323";

    std::cout << qwq_big_num::big_int_substract(str_1, str_2);
}