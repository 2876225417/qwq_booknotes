

#include "stack.hpp"


#include "item.hpp"
#include "message.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>


#include "stack_except.h"

template <typename T, int VAL>
T add(const T& val) {
    return val + VAL;
}

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




int main() {


}