



#include "stack_except.h"


namespace qwq_stack {
    
    stack_exception::stack_exception(const char* msg): err_msg_(msg) { }

    stack_exception::stack_exception(const std::string& msg): err_msg_(std::move(msg)) { }

    
    stack_exception::~stack_exception() {}

    const char* stack_exception::what() const noexcept {
        return err_msg_.c_str();
    }


}