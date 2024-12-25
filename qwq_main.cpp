

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
T add(T a, T b) {
    return a + b;
}

template <typename T>
class test {
public:
    test(const T& t): val(std::move(t)) { }
private:
    T val;
};



int main() {
    test t(3);
    
    
}