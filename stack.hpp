#ifndef STACK_HPP_
#define STACK_HPP_


#include <cstdarg>
#include <stdexcept>
#include <vector>
#include "item.hpp"

#include "stack_except.h"

namespace qwq_stack {

    template <typename T>
    class stack {
    public:
        stack(const std::vector<T>&);
        void push(const T&);
        void pop();
        T top() const;
        size_t size() const;

        bool empty() const {
            return elems.empty();
        }

        friend inline std::ostream& operator<<(std::ostream& os, const stack<T>& obj) {
            for (auto i: obj.elems) std::cout << i << ' ';
            return os;
        }
        
        // stack(stack<T> const&);
        
        template <typename T2>
        stack<T>& operator=(const stack<T2>&);

        T& operator[](size_t i) {
            return elems[i];
        }

    private:
        std::vector<T> elems;
    };


    template <typename T>
    stack<T>::stack(const std::vector<T>& rhs): elems(std::move(rhs)) { }

    template <typename T>
    void stack<T>::push(const T& elem) {
        elems.emplace_back(elem);
    }

    template <typename T>
    size_t stack<T>::size() const {
        if (empty()){
            std::cerr << "Stack<>::size(): empty stack!";
            return 0;
        }
        return elems.size();
    }


    template <typename T>
    template <typename T2>
    stack<T>& stack<T>::operator=(const stack<T2>& obj) {
        if((void*)this == (void*)&obj)
            return *this;

        elems.clear();
        stack<T2> tmp(obj);
        while (!tmp.empty()) {
            elems.push_back(tmp.top());
            tmp.pop();
        }
        return *this;
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
            for (auto i: obj.ptr_elems) os << *i << ' ';
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

    template <typename T1, typename T2>
    class unique_stack {
    public:
    private:
    };

    template <typename T>
    class unique_stack<T, T> {
    public:
        unique_stack(){ std::cout << "(T, T)\n"; }
    private:
    };

    template <typename T>
    class unique_stack<point<double*>, T> {
    public:
        unique_stack() { std::cout << "(double*, T)\n"; }
    private:
    };

    template <typename T>
    class unique_stack<T, point<T>*> {
    public:
        unique_stack() { std::cout << "(T, pointer<T>*)\n"; }
    private:
    };

    template <typename T>
    class unique_stack<T, T*> {
    public:
        unique_stack() { std::cout << "(T, T*)\n"; }
    private:  
    };

    template <typename T>
    class unique_stack<T*, T*> {
    public:
        unique_stack() { std::cout << "(T*, T*)\n"; }
    private:
    };

    template <typename T, typename CONT = std::vector<T>>
    class default_stack {
    public:
        default_stack();
        void push(const T&);
        void pop();
        T top() const;

        friend inline std::ostream& operator<<(std::ostream& os, const default_stack<T, CONT>& obj) {
            for (auto i: obj.elems) os << i << ' ';
            return os;
        }


        bool empty() const {
            return elems.empty();
        }
    private:
        CONT elems;
    };

    template <typename T, typename CONT>
    default_stack<T, CONT>::default_stack() { }

    template <typename T, typename CONT>
    void default_stack<T, CONT>::push(const T& elem) {
        elems.push_back(elem);
    }

    template <typename T, typename CONT>
    void default_stack<T, CONT>::pop() {
        if (!elems.empty())
            throw std::out_of_range("Stack<T, CONT>::pop(): empty stack!");
        elems.pop();
    }

    template <typename T, typename CONT>
    T default_stack<T, CONT>::top() const {
        if (!elems.empty())
            throw std::out_of_range("Stack<T, CONT>::top(): empty stack!");
        return elems.top();
    }


    /** sized_stack     
     *  T for type of element in stack
     *  MAXSIZE for capacity of stack
     */
    using qwq_stack::stack_exception;
    template <typename T, int MAXSIZE>
    class sized_stack {
    public:
        sized_stack();
        void push(const T&);
        void pop();
        T top() const;
        bool empty() const {
            return num_elems <= 0 ? true : false;
        }
        bool full() const {
            return num_elems >= MAXSIZE ? true : false;
        }

        friend inline
        std::ostream& operator<<(std::ostream& os, const sized_stack<T, MAXSIZE>& obj) {
            for (int i = 0; i < MAXSIZE; i++) os << obj.elems[i] << ' ';
            return os;
        }


    private:
        T elems[MAXSIZE];
        int num_elems;
    };
    
    template <typename T, int MAXSIZE>
    sized_stack<T, MAXSIZE>::sized_stack(): num_elems(0) { }

    template <typename T, int MAXSIZE>
    void sized_stack<T, MAXSIZE>::push(const T& elem) {
        if (full())
            throw std::out_of_range("sized_stack<>::push(): full stack!");
        elems[num_elems++] = std::move(elem);
    }

    template <typename T, int MAXSIZE>
    void sized_stack<T, MAXSIZE>::pop() {
        if (empty())
            throw std::out_of_range("sized_stack<>::pop(): empty stack!");
        num_elems--;
    }

    template <typename T, int MAXSIZE>
    T sized_stack<T, MAXSIZE>::top() const {
        if (empty())
            throw stack_exception("sized_stack<>::top(): empty stack!");         
        return elems[num_elems - 1];
    }


    /** specified template overload
     *  T -> std::string
     *  MAXSIZE -> 5
     */
    template<>
    class sized_stack<std::string, 5> {
    public:
        sized_stack() { std::cout << "sized_stack<std::string 5>"; }
    private:
    };


    namespace modifiers {
        /** transform for qwq_stack 
         *  @prams 
         *  only support two params functions
         *  available for current stack implementation
         */
        template <typename T1, typename T2>
        void transform( T1& CONT__1
                      , T1& CONT__2
                      , T2 (*__op__)(const T2&)
                      ) {
            if (CONT__1.size() != CONT__2.size())
                throw stack_exception("Not compatible stack!");

            for (size_t i = 0; i < CONT__1.size(); i++) 
                CONT__2[i] = __op__(CONT__1[i]);
        }
    }

}
#endif // STACK_HPP_