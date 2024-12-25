

#include "stack.hpp"


#include "item.hpp"
#include "message.h"

#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

#include "string.h"


#include "stack_except.h"

#include <vector>
#include <bitset>

#include <exception>

struct vector_exception: public std::exception {
    
    explicit 
    vector_exception(const char* msg): err_msg_(msg) { }

    explicit 
    vector_exception(std::string& msg): err_msg_(std::move(msg)) { }

    explicit 
    vector_exception(std::string&& msg): err_msg_(std::move(msg)) { }

    const char* what() const noexcept override { return err_msg_.c_str(); }

private:
    std::string err_msg_;
};


#include <optional>

void test_std() {
    std::optional<int> opt_1(1);
    std::cout << opt_1.has_value() << '\n'
              << opt_1.value()     << '\n'
              << opt_1.value_or(0) << '\n';

    std::optional<int> opt_2(std::nullopt);
    std::cout << opt_2.has_value() << '\n';
    try {
        std::ignore = opt_2.value();
    } catch (const std::bad_optional_access& ex) {
        std::cerr << ex.what() << '\n';
    }
    std::cout << opt_2.value_or(0) << '\n';

    opt_2 = 42;
    std::cout << opt_2.has_value() << '\n'
              << opt_2.value()     << '\n'
              << opt_2.value_or(0) << '\n';

}

int main() {
    test_std();
}