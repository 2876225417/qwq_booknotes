#ifndef STACK_EXCEPT_H_
#define STACK_EXCEPT_H_


#include <exception>

#include <iostream>

namespace qwq_stack {

    class stack_exception: public std::exception {
    public:
        explicit
        stack_exception(const char*);

        explicit
        stack_exception(const std::string&);

        virtual
        ~stack_exception() noexcept = default;

        virtual
        const char* what() const noexcept override;

    protected:
        std::string err_msg_;
    private:
        
    };




}

#endif