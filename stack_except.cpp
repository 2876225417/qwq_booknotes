



#include "stack_except.h"


    qwq_stack::stack_exception::stack_exception(const char* msg): err_msg_(msg) { }

    qwq_stack::stack_exception::stack_exception(const std::string& msg): err_msg_(std::move(msg)) { }


    const char* qwq_stack::stack_exception::what() const noexcept {
        return err_msg_.c_str();
    }

