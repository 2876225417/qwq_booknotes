

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

// from customized
#include "optional.hpp"
// from std
#include <optional>

struct C {
    C(int a, int b): m_a(a), m_b(b) { }

private:
    int m_a;
    int m_b;
};



void test_custom() {
    
    using qwq_optional::optional;
    using qwq_optional::nullopt;

    optional<C> opt_C_1(nullopt);
    std::cout << "opt_C_1:exception: Head!";
    opt_C_1.value();
    std::cout << "End!";

    std::cout << "customized optional test: \n";
    optional<int> opt_int_1(1);
    std::cout << opt_int_1.has_value() << '\n'
              << opt_int_1.value()     << '\n'
              << '\n';

    optional<double> opt_double_1(nullopt);
    opt_double_1.value();
}
 
void test_std() {
    std::cout << "standard optional test: \n";
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

/* use customized tag structures */

struct compute_cpu_kernel {
    compute_cpu_kernel() = default;
} cpu_kernel;

struct compute_gpu_kernel {
    compute_gpu_kernel() = default;
} gpu_kernel;

struct compute_kernel {
    /* restrict ctor params in tag structures */
    compute_kernel(compute_cpu_kernel) { }
    compute_kernel(compute_gpu_kernel) { }
};

compute_kernel ck_1(cpu_kernel);
compute_kernel ck_2(gpu_kernel);

#include <cstddef>

struct A { double x; };






void func(int a){ std::cout << "a"; }
int main() {
    char* str_ = "ppqwqqq";

    qwq_string::custom_string str("qwq");

    if (str) std::cout << "str: nullptr!";
 
    decltype(func)* k = func;

    k(3);

    auto t = k;

    t(4); 


    void (*m)(int) = func;
    m(5);

    // test_std();
}