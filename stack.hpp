#ifndef STACK_HPP_
#define STACK_HPP_


#include <cstdarg>
#include <stdexcept>
#include <vector>
#include "item.hpp"

namespace qwq_stack {
    template <typename T>
    class stack {
    public:
        stack();
        void push(const T&);
        void pop();
        T top() const;
        bool empty() const {
            return elems.empty();
        }

        friend inline std::ostream& operator<<(std::ostream& os, const stack<T>& obj) {
            for (auto i: obj.elems) std::cout << i << ' ';
            return os;
        }
        
        stack(stack<T> const&);
        stack<T>& operator=(const stack<T>&);

    private:
        std::vector<T> elems;
    };


    template <typename T>
    stack<T>::stack() {}

    template <typename T>
    void stack<T>::push(const T& elem) {
        elems.emplace_back(elem);
    }

    template <typename T>
    void stack<T>::pop() {
        if (elems.empty()) 
            throw std::out_of_range("stack<>::pop(): empty stack!");
        /* if need return
         * T tmp = elems.back();
         * elems.pop_back();
         * return tmp;
         */
        elems.pop_back();
    }

    template <typename T>
    T stack<T>::top() const {
        if (elems.empty())
            throw std::out_of_range("stack<>::top(): empty stack!");
        return elems.back();
    }


    template<>
    class stack<float*> {
    public:
        inline explicit stack();
        inline void push(const float*);
        inline void pop();
        inline float* top() const;
        
        friend inline std::ostream& operator<<(std::ostream& os, const stack<float*> obj) {
            for (auto i: obj.ptr_elems) std::cout << *i << ' ';
            return os;
        }

        bool empty() const {
            return ptr_elems.empty();
        }
    private:
        std::vector<float*> ptr_elems;
    };

    stack<float*>::stack(){ }

    void stack<float*>::push(const float* elem) {
        ptr_elems.push_back(const_cast<float*>(elem));
    }

    void stack<float*>::pop() {
        if (ptr_elems.empty()) 
            throw std::out_of_range("stack<float*>::pop(): empty stack!");
        ptr_elems.pop_back();
    }

    float* stack<float*>::top() const {
        if (ptr_elems.empty())
            throw std::out_of_range("stack<float*>::pop(): empty stack!");
        return ptr_elems.back();
    }
}
#endif // STACK_HPP_