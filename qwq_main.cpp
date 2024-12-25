

#include "stack.hpp"


#include "item.hpp"
#include "message.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

#include "string.h"


#include "stack_except.h"


#include <vector>

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


template <typename T>
class test {
public:
    test(const T& t): val(std::move(t)) { }
private:
    T val;
};


void bar(int a){ std::cout << a << "from bar\n"; }


template <const char* name>
class best { 
public:
    best();
};

template<typename T, int VAL>
T add_(const T& val) {
    return val + VAL;
}


int main() {
    qwq_stack::stack<int> s_int_1({1, 2, 3, 4, 5});
    qwq_stack::stack<int> s_int_2({0, 1, 2, 3, 4});

    qwq_stack::modifiers::transform(s_int_1, s_int_2, add_<int, 3>);
    
    std::cout << s_int_2;
        
}